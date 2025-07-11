
// FUNC: public: int __thiscall idSoundSample::LengthIn44kHzSamples(void)const
int __thiscall idSoundSample::LengthIn44kHzSamples(idSoundSample *this)
{
  int nSamplesPerSec; // eax
  int result; // eax
  bool v3; // zf

  nSamplesPerSec = this->nSamplesPerSec;
  if ( nSamplesPerSec == 11025 )
    return 4 * this->objectSize;
  v3 = nSamplesPerSec == 22050;
  result = this->objectSize;
  if ( v3 )
    result *= 2;
  return result;
}

// FUNC: public: virtual void __thiscall idSoundSample::PurgeSoundSample(void)
void __thiscall idSoundSample::PurgeSoundSample(idSoundSample *this)
{
  bool v2; // zf

  v2 = !this->hardwareBuffer;
  this->purged = 1;
  if ( !v2 && idSoundSystemLocal::useOpenAL )
  {
    Sys_EnterCriticalSection(0);
    qalGetError();
    qalDeleteBuffers(1u, &this->openalBuffer);
    if ( qalGetError() )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "idSoundCache: error unloading data from OpenAL hardware buffer");
    }
    else
    {
      this->openalBuffer = 0;
      this->hardwareBuffer = 0;
    }
    Sys_LeaveCriticalSection(0);
  }
  if ( this->nonCacheData )
  {
    soundSystem->FreeSoundSample(soundSystem, this->nonCacheData);
    this->nonCacheData = 0;
  }
}

// FUNC: public: bool __thiscall idSoundSample::FetchFromCache(int,unsigned char const * *,int *,int *,bool)
char __thiscall idSoundSample::FetchFromCache(
        idSoundSample *this,
        int offset,
        const unsigned __int8 **output,
        int *position,
        int *size,
        bool allowIO)
{
  int objectSize; // eax
  signed int v7; // edx
  unsigned __int8 *nonCacheData; // eax
  int v9; // eax

  objectSize = this->objectSize;
  v7 = offset & 0xFFFFFFFE;
  if ( !objectSize )
    return 0;
  if ( offset < 0 )
    return 0;
  if ( v7 > 2 * objectSize )
    return 0;
  nonCacheData = this->nonCacheData;
  if ( !nonCacheData )
    return 0;
  if ( output )
    *output = &nonCacheData[v7];
  if ( position )
    *position = 0;
  if ( size )
  {
    v9 = 2 * this->objectSize - v7;
    *size = v9;
    if ( v9 > 81920 )
      *size = 81920;
  }
  return 1;
}

// FUNC: public: virtual __thiscall idSoundSample::~idSoundSample(void)
void __thiscall idSoundSample::~idSoundSample(idSoundSample *this)
{
  this->__vftable = (idSoundSample_vtbl *)&idSoundSample::`vftable';
  idSoundSample::PurgeSoundSample(this);
  this->__vftable = (idSoundSample_vtbl *)&rvCommonSample::`vftable';
  idStr::FreeData(&this->name);
}

// FUNC: public: void __thiscall idSoundSample::MakeDefault(void)
void __thiscall idSoundSample::MakeDefault(idSoundSample *this)
{
  unsigned __int8 *v2; // edx
  int v3; // ecx
  int v4; // eax
  unsigned int *p_openalBuffer; // edi
  int i; // [esp+8h] [ebp-8h]

  this->wFormatTag = 1;
  this->nChannels = 1;
  this->wBitsPerSample = 16;
  this->nSamplesPerSec = 44100;
  this->objectSize = 0x2000;
  this->objectMemSize = 0x4000;
  v2 = (unsigned __int8 *)soundSystem->AllocSoundSample(soundSystem, 0x4000);
  v3 = 0;
  this->nonCacheData = v2;
  i = 0;
  do
  {
    v4 = (int)(sin((double)i * 3.1415927 * 0.03125) * 16384.0);
    *(_WORD *)&v2[4 * v3] = v4;
    *(_WORD *)&v2[4 * v3++ + 2] = v4;
    i = v3;
  }
  while ( v3 < 4096 );
  if ( idSoundSystemLocal::useOpenAL )
  {
    Sys_EnterCriticalSection(0);
    qalGetError();
    p_openalBuffer = &this->openalBuffer;
    qalGenBuffers(1u, &this->openalBuffer);
    if ( qalGetError() )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "idSoundCache: error generating OpenAL hardware buffer");
    if ( qalIsBuffer(*p_openalBuffer) )
    {
      qalGetError();
      qalBufferData(
        *p_openalBuffer,
        2 * (this->nChannels != 1) + 4353,
        this->nonCacheData,
        this->objectMemSize,
        this->nSamplesPerSec);
      if ( qalGetError() )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
          common.type,
          "idSoundCache: error loading data into OpenAL hardware buffer");
        Sys_LeaveCriticalSection(0);
        this->defaultSound = 1;
        return;
      }
      soundSystem->FreeSoundSample(soundSystem, this->nonCacheData);
      this->hardwareBuffer = 1;
      this->nonCacheData = 0;
    }
    Sys_LeaveCriticalSection(0);
  }
  this->defaultSound = 1;
}

// FUNC: public: void __thiscall idSoundSample::CheckForDownSample(void)
void __usercall idSoundSample::CheckForDownSample(idSoundSample *this@<ecx>, int a2@<edi>)
{
  int v3; // edi
  unsigned __int8 *v4; // ebx
  int v5; // eax

  if ( s_force22kHz.internalVar->integerValue && this->wFormatTag == 1 && this->nSamplesPerSec == 44100 )
  {
    v3 = this->objectSize >> 1;
    v4 = (unsigned __int8 *)((int (__thiscall *)(idSoundSystem *, int, int))soundSystem->AllocSoundSample)(
                              soundSystem,
                              2 * v3,
                              a2);
    v5 = 0;
    if ( this->nChannels == 1 )
    {
      if ( v3 > 0 )
      {
        do
        {
          *(_WORD *)&v4[2 * v5] = *(_WORD *)&this->nonCacheData[4 * v5];
          ++v5;
        }
        while ( v5 < v3 );
      }
    }
    else if ( v3 > 0 )
    {
      do
      {
        *(_WORD *)&v4[2 * v5] = *(_WORD *)&this->nonCacheData[4 * v5];
        *(_WORD *)&v4[2 * v5 + 2] = *(_WORD *)&this->nonCacheData[4 * v5 + 2];
        v5 += 2;
      }
      while ( v5 < v3 );
    }
    soundSystem->FreeSoundSample(soundSystem, this->nonCacheData);
    this->objectSize >>= 1;
    this->objectMemSize >>= 1;
    this->nAvgBytesPerSec >>= 1;
    this->nSamplesPerSec >>= 1;
    this->nonCacheData = v4;
  }
}

// FUNC: public: class idSoundSample const * __thiscall idSoundCache::GetObjectA(int)const
const idSoundSample *__thiscall idSoundCache::GetObjectA(idSoundCache *this, int index)
{
  if ( index < 0 || index > this->listCache.num )
    return 0;
  else
    return this->listCache.list[index];
}

// FUNC: public: void __thiscall idSoundCache::PurgeSounds(bool)
void __thiscall idSoundCache::PurgeSounds(idSoundCache *this, bool force)
{
  int i; // esi
  idSoundSample *v4; // ecx

  for ( i = 0; i < this->listCache.num; ++i )
  {
    v4 = this->listCache.list[i];
    if ( v4 )
      v4->PurgeSoundSample(v4);
  }
}

// FUNC: public: int __thiscall idSoundSystemLocal::GetCacheMemoryUsage(void)
int __thiscall idSoundSystemLocal::GetCacheMemoryUsage(idSoundSystemLocal *this)
{
  return soundCacheAllocator.usedBlockMemory;
}

// FUNC: public: void __thiscall idSoundCache::PrintMemInfo(class MemInfo *)
void __thiscall idSoundCache::PrintMemInfo(idSoundCache *this, MemInfo *mi)
{
  int v3; // ebx
  idStr *v4; // eax
  idFileSystem_vtbl *v5; // edx
  idFile *v6; // esi
  int v7; // ecx
  int v8; // eax
  idSoundSample **list; // edx
  int v10; // eax
  void *v11; // esp
  int *v12; // edx
  int v13; // eax
  int v14; // ecx
  int *v15; // edi
  int v16; // edx
  int v17; // esi
  bool v18; // zf
  int v19; // edi
  idSoundSample *v20; // esi
  int objectMemSize; // eax
  idStr *v22; // eax
  idFile_vtbl *v23; // edx
  idStr *v24; // edi
  idStr *v25; // eax
  idFile v26; // edx
  char *v27; // [esp-18h] [ebp-CCh]
  char *v28; // [esp-14h] [ebp-C8h]
  char *v29; // [esp-10h] [ebp-C4h]
  char *data; // [esp-Ch] [ebp-C0h]
  char *v31; // [esp-Ch] [ebp-C0h]
  _DWORD v32[3]; // [esp+0h] [ebp-B4h] BYREF
  idStr v33; // [esp+Ch] [ebp-A8h] BYREF
  idStr v34; // [esp+2Ch] [ebp-88h] BYREF
  idStr v35; // [esp+4Ch] [ebp-68h] BYREF
  idStr result; // [esp+6Ch] [ebp-48h] BYREF
  idSoundCache *v37; // [esp+8Ch] [ebp-28h]
  int v38; // [esp+90h] [ebp-24h]
  int v39; // [esp+94h] [ebp-20h]
  idFile *f; // [esp+98h] [ebp-1Ch]
  int num; // [esp+9Ch] [ebp-18h]
  int *sortIndex; // [esp+A0h] [ebp-14h]
  int total; // [esp+A4h] [ebp-10h]
  int v44; // [esp+B0h] [ebp-4h]

  v3 = 0;
  v37 = this;
  num = 0;
  total = 0;
  v4 = operator+(&result, &mi->filebase, "_sounds.txt");
  v5 = fileSystem->__vftable;
  data = v4->data;
  v44 = 0;
  v6 = v5->OpenFileWrite(fileSystem, data, "fs_savepath", 0);
  f = v6;
  v44 = -1;
  idStr::FreeData(&result);
  if ( v6 )
  {
    v7 = this->listCache.num;
    v8 = 0;
    if ( v7 > 0 )
    {
      list = this->listCache.list;
      do
      {
        if ( !*list )
          break;
        ++v8;
        ++list;
        ++v3;
      }
      while ( v8 < v7 );
      num = v3;
    }
    v10 = 4 * v3 + 3;
    LOBYTE(v10) = v10 & 0xFC;
    v11 = alloca(v10);
    v12 = v32;
    v13 = 0;
    for ( sortIndex = v32; v13 < v3; ++v13 )
      v32[v13] = v13;
    if ( v3 - 1 > 0 )
    {
      v14 = 1;
      v38 = 1;
      v15 = v32;
      v39 = v3 - 1;
      do
      {
        if ( v14 < v3 )
        {
          do
          {
            v16 = v12[v14];
            v17 = *v15;
            if ( v37->listCache.list[*v15]->objectMemSize < v37->listCache.list[v16]->objectMemSize )
            {
              *v15 = v16;
              sortIndex[v14] = v17;
            }
            v3 = num;
            v12 = sortIndex;
            ++v14;
          }
          while ( v14 < num );
          v14 = v38;
          v6 = f;
        }
        ++v14;
        ++v15;
        v18 = v39-- == 1;
        v38 = v14;
      }
      while ( !v18 );
    }
    v19 = 0;
    if ( v3 > 0 )
    {
      do
      {
        v20 = v37->listCache.list[v12[v19]];
        if ( v20 )
        {
          if ( !v20->purged )
          {
            objectMemSize = v20->objectMemSize;
            total += objectMemSize;
            v22 = idStr::FormatNumber(&v34, objectMemSize);
            v23 = f->__vftable;
            v31 = v20->name.data;
            v29 = v22->data;
            v44 = 1;
            v23->Printf(f, "%s %s\n", v29, v31);
            v44 = -1;
            idStr::FreeData(&v34);
            v12 = sortIndex;
          }
        }
        ++v19;
      }
      while ( v19 < v3 );
      v6 = f;
    }
    mi->soundAssetsTotal = total;
    mi->soundAssetsCount = v3;
    v24 = idStr::FormatNumber(&v33, v3);
    v44 = 2;
    v25 = idStr::FormatNumber(&v35, total);
    v26.__vftable = v6->__vftable;
    v28 = v24->data;
    v27 = v25->data;
    LOBYTE(v44) = 3;
    v26.Printf(v6, "\nTotal sound bytes allocated: %s (%s items)\n", v27, v28);
    LOBYTE(v44) = 2;
    idStr::FreeData(&v35);
    v44 = -1;
    idStr::FreeData(&v33);
    fileSystem->CloseFile(fileSystem, v6);
  }
}

// FUNC: public: unsigned int __thiscall idSoundCache::ListSoundSummary(void)
int __thiscall idSoundCache::ListSoundSummary(idSoundCache *this)
{
  int num; // eax
  int v3; // ebx
  int i; // esi
  idSoundSample *v5; // ecx

  num = this->listCache.num;
  v3 = 0;
  for ( i = 0; i < num; ++i )
  {
    if ( i >= 0 && i <= num )
    {
      v5 = this->listCache.list[i];
      if ( v5 )
      {
        if ( !v5->purged )
          v3 += v5->GetMemoryUsed(v5);
      }
    }
    num = this->listCache.num;
  }
  return v3;
}

// FUNC: public: unsigned int __thiscall idSoundSample::GetNewTimeStamp(void)const
unsigned int __thiscall idSoundSample::GetNewTimeStamp(idSoundSample *this)
{
  unsigned int result; // eax
  int len; // edi
  char *data; // ecx
  char *v5; // edx
  char v6; // al
  unsigned int timestamp; // [esp+18h] [ebp-30h] BYREF
  idStr oggName; // [esp+1Ch] [ebp-2Ch] BYREF
  int v9; // [esp+44h] [ebp-4h]

  fileSystem->ReadFile(fileSystem, this->name.data, 0, &timestamp);
  result = timestamp;
  if ( timestamp == -1 )
  {
    len = this->name.len;
    oggName.data = oggName.baseBuffer;
    oggName.len = 0;
    oggName.alloced = 20;
    oggName.baseBuffer[0] = 0;
    if ( len + 1 > 20 )
      idStr::ReAllocate(&oggName, len + 1, 1);
    data = this->name.data;
    v5 = oggName.data;
    do
    {
      v6 = *data;
      *v5++ = *data++;
    }
    while ( v6 );
    oggName.len = len;
    v9 = 0;
    idStr::SetFileExtension(&oggName, ".ogg");
    fileSystem->ReadFile(fileSystem, oggName.data, 0, &timestamp);
    v9 = -1;
    idStr::FreeData(&oggName);
    return timestamp;
  }
  return result;
}

// FUNC: public: virtual void __thiscall idSoundSample::Load(int)
void __userpurge idSoundSample::Load(idSoundSample *this@<ecx>, int a2@<edi>, int langIndex, int a4)
{
  int integerValue; // eax
  char *len; // ebx
  const char *v7; // eax
  char *v8; // eax
  idFile *v9; // eax
  unsigned int v10; // ecx
  bool v11; // zf
  unsigned int v12; // eax
  unsigned __int16 nChannels; // dx
  int nSamplesPerSec; // ecx
  int wFormatTag; // eax
  int mdwSize; // eax
  int nAvgBytesPerSec; // ecx
  int mMemSize; // eax
  unsigned __int8 *v19; // eax
  unsigned int *p_openalBuffer; // esi
  char *data; // [esp-4h] [ebp-CCh]
  int objectMemSize; // [esp+0h] [ebp-C8h]
  const char *v23; // [esp+4h] [ebp-C4h]
  unsigned int timestampOgg; // [esp+18h] [ebp-B0h] BYREF
  unsigned int timestampWav; // [esp+1Ch] [ebp-ACh] BYREF
  idStr temp; // [esp+20h] [ebp-A8h] BYREF
  waveformatex_s info; // [esp+40h] [ebp-88h] BYREF
  idWaveFile fh; // [esp+54h] [ebp-74h] BYREF
  int v29; // [esp+C4h] [ebp-4h]

  this->defaultSound = 0;
  this->purged = 0;
  this->hardwareBuffer = 0;
  integerValue = com_QuickLoad.internalVar->integerValue;
  if ( integerValue == 1 || integerValue == 3 )
  {
    idSoundSample::MakeDefault(this);
  }
  else
  {
    if ( !idStr::Cmpn(this->name.data, "sound/vo", 8) )
    {
      temp.len = 0;
      temp.alloced = 20;
      temp.data = temp.baseBuffer;
      temp.baseBuffer[0] = 0;
      v29 = 0;
      if ( langIndex > -1 )
      {
        this->PurgeSoundSample(this);
        this->purged = 0;
      }
      if ( !(*(unsigned __int8 (__thiscall **)(netadrtype_t, int, int))(*(_DWORD *)common.type + 184))(
              common.type,
              langIndex,
              a2) )
        a4 = 0;
      len = (char *)this->name.len;
      if ( (int)(len + 1) > *(int *)temp.baseBuffer )
        idStr::ReAllocate((idStr *)&temp.data, (int)(len + 1), 0);
      qmemcpy((void *)temp.alloced, this->name.data, (unsigned int)len);
      len[temp.alloced] = 0;
      temp.data = len;
      idStr::StripUntil((idStr *)&temp.data, 47);
      idStr::StripLeadingOnce((idStr *)&temp.data, "/");
      idStr::StripUntil((idStr *)&temp.data, 47);
      v7 = (const char *)(*(int (__thiscall **)(netadrtype_t, int, int))(*(_DWORD *)common.type + 180))(
                           common.type,
                           a4,
                           temp.alloced);
      v8 = va("sound/vo_%s%s", v7, v23);
      idStr::operator=(&this->name, v8);
      v29 = -1;
      idStr::FreeData(&temp);
    }
    idStr::SetFileExtension(&this->name, "wav");
    fileSystem->ReadFile(fileSystem, this->name.data, 0, &timestampWav);
    idStr::SetFileExtension(&this->name, "ogg");
    fileSystem->ReadFile(fileSystem, this->name.data, 0, &timestampOgg);
    if ( timestampWav == -1 && timestampOgg == -1 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "Couldn't load sound '%s' using default",
        this->name.data);
      idSoundSample::MakeDefault(this);
      return;
    }
    if ( com_makingBuild.internalVar->integerValue && com_Bundler.internalVar->integerValue )
    {
      idStr::SetFileExtension(&this->name, "xma");
      v9 = fileSystem->OpenFileRead(fileSystem, this->name.data, 1, 0);
      fileSystem->CloseFile(fileSystem, v9);
    }
    idStr::SetFileExtension(&this->name, "wav");
    v10 = timestampOgg;
    v11 = timestampOgg == -1;
    v12 = timestampWav;
    this->timestamp = timestampWav;
    if ( !v11 && (v12 == -1 || v12 < v10) )
    {
      idStr::SetFileExtension(&this->name, "ogg");
      this->timestamp = timestampOgg;
    }
    idWaveFile::idWaveFile(&fh);
    data = this->name.data;
    v29 = 1;
    if ( idWaveFile::Open(&fh, data, &info, 1) == -1 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "Couldn't load sound '%s' using default",
        this->name.data);
LABEL_23:
      idSoundSample::MakeDefault(this);
      v29 = -1;
      idWaveFile::~idWaveFile(&fh);
      return;
    }
    nChannels = info.nChannels;
    if ( info.nChannels != 1 && info.nChannels != 2 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *, char *, _DWORD))(*(_DWORD *)common.type + 136))(
        common.type,
        "idSoundSample: %s has %i channels, using default",
        this->name.data,
        info.nChannels);
LABEL_33:
      idWaveFile::Close(&fh);
      goto LABEL_23;
    }
    if ( info.wBitsPerSample != 16 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "idSoundSample: %s is %dbits, expected 16bits using default",
        this->name.data,
        info.wBitsPerSample);
      idWaveFile::Close(&fh);
      goto LABEL_23;
    }
    nSamplesPerSec = info.nSamplesPerSec;
    if ( info.nSamplesPerSec != 44100 && info.nSamplesPerSec != 22050 && info.nSamplesPerSec != 11025 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *, char *, unsigned int))(*(_DWORD *)common.type + 136))(
        common.type,
        "idSoundCache: %s is %dHz, expected 11025, 22050 or 44100 Hz. Using default",
        this->name.data,
        info.nSamplesPerSec);
      goto LABEL_33;
    }
    wFormatTag = info.wFormatTag;
    this->wFormatTag = info.wFormatTag;
    v11 = wFormatTag == 2;
    mdwSize = fh.mdwSize;
    this->nChannels = nChannels;
    this->nSamplesPerSec = nSamplesPerSec;
    nAvgBytesPerSec = info.nAvgBytesPerSec;
    this->objectSize = mdwSize;
    mMemSize = fh.mMemSize;
    this->wBitsPerSample = 16;
    this->nAvgBytesPerSec = nAvgBytesPerSec;
    this->isOgg = v11;
    this->objectMemSize = mMemSize;
    v19 = (unsigned __int8 *)soundSystem->AllocSoundSample(soundSystem, mMemSize);
    objectMemSize = this->objectMemSize;
    this->nonCacheData = v19;
    idWaveFile::Read(&fh, v19, objectMemSize, 0);
    idSoundSample::CheckForDownSample(this);
    if ( idSoundSystemLocal::useOpenAL )
    {
      Sys_EnterCriticalSection(0);
      if ( this->wFormatTag == 1 )
      {
        qalGetError();
        p_openalBuffer = &this->openalBuffer;
        qalGenBuffers(1u, &this->openalBuffer);
        if ( qalGetError() )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
            common.type,
            "idSoundCache: error generating OpenAL hardware buffer");
        if ( qalIsBuffer(*p_openalBuffer) )
        {
          qalGetError();
          qalBufferData(
            *p_openalBuffer,
            2 * (this->nChannels != 1) + 4353,
            this->nonCacheData,
            this->objectMemSize,
            this->nSamplesPerSec);
          if ( qalGetError() )
          {
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
              common.type,
              "idSoundCache: error loading data into OpenAL hardware buffer");
          }
          else
          {
            soundSystem->FreeSoundSample(soundSystem, this->nonCacheData);
            this->hardwareBuffer = 1;
            this->nonCacheData = 0;
          }
        }
      }
      Sys_LeaveCriticalSection(0);
    }
    idWaveFile::Close(&fh);
    v29 = -1;
    idWaveFile::~idWaveFile(&fh);
  }
}

// FUNC: public: void __thiscall idSoundSample::Reload(bool)
void __thiscall idSoundSample::Reload(idSoundSample *this, bool force)
{
  unsigned int NewTimeStamp; // eax

  if ( force )
  {
LABEL_6:
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "reloading %s\n",
      this->name.data);
    this->PurgeSoundSample(this);
    this->Load(this, -1);
    return;
  }
  NewTimeStamp = idSoundSample::GetNewTimeStamp(this);
  if ( NewTimeStamp != -1 )
  {
    if ( NewTimeStamp == this->timestamp )
      return;
    goto LABEL_6;
  }
  if ( !this->defaultSound )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Couldn't load sound '%s' using default",
      this->name.data);
    idSoundSample::MakeDefault(this);
  }
}

// FUNC: public: class idSoundSample * __thiscall idSoundCache::FindSample(class idStr const &)
idSoundSample *__thiscall idSoundCache::FindSample(idSoundCache *this, const idStr *filename)
{
  int len; // ebx
  int v4; // eax
  bool v5; // sf
  char *data; // edx
  unsigned __int8 v7; // al
  int v8; // esi
  char *v9; // ecx
  int v10; // esi
  char *v11; // ecx
  char *v12; // edx
  char v13; // al
  int v14; // eax
  idSoundSample *v15; // ebx
  unsigned int v16; // esi
  rvCommonSample *v17; // eax
  idSoundSample *v18; // esi
  bool v19; // zf
  int num; // ecx
  int v22; // eax
  idSoundSample **list; // edx
  int granularity; // eax
  idSoundSample *v25; // ecx
  bool v26; // cc
  int i; // eax
  int v28; // esi
  int size; // ecx
  int v30; // ecx
  idSoundSample **v31; // ebx
  int j; // eax
  int v33; // ebx
  idStr *p_name; // ebp
  int k; // esi
  idStr fname; // [esp+14h] [ebp-6Ch] BYREF
  idStr tmpName; // [esp+34h] [ebp-4Ch] BYREF
  idStr strippedFname; // [esp+54h] [ebp-2Ch] BYREF
  int v39; // [esp+7Ch] [ebp-4h]
  const idStr *filenamea; // [esp+84h] [ebp+4h]
  idSoundSample *filenameb; // [esp+84h] [ebp+4h]

  fname.len = 0;
  fname.alloced = 20;
  fname.data = fname.baseBuffer;
  fname.baseBuffer[0] = 0;
  len = filename->len;
  v4 = filename->len + 1;
  v5 = filename->len - 19 < 0;
  v39 = 0;
  if ( !(v5 ^ __OFSUB__(v4, 20) | (v4 == 20)) )
    idStr::ReAllocate(&fname, v4, 0);
  qmemcpy(fname.data, filename->data, len);
  fname.data[len] = 0;
  fname.len = len;
  idStr::BackSlashesToSlashes(&fname);
  data = fname.data;
  v7 = *fname.data;
  v8 = 0;
  if ( *fname.data )
  {
    v9 = fname.data;
    do
    {
      if ( idStr::lowerCaseCharacter[v7] )
        v7 = idStr::lowerCaseCharacter[v7];
      *v9 = v7;
      data = fname.data;
      v7 = fname.data[++v8];
      v9 = &fname.data[v8];
    }
    while ( v7 );
  }
  declManager->MediaPrint(declManager, "%s\n", data);
  tmpName.len = 0;
  tmpName.alloced = 20;
  tmpName.data = tmpName.baseBuffer;
  tmpName.baseBuffer[0] = 0;
  strippedFname.data = strippedFname.baseBuffer;
  v10 = fname.len;
  LOBYTE(v39) = 1;
  strippedFname.len = 0;
  strippedFname.alloced = 20;
  strippedFname.baseBuffer[0] = 0;
  if ( fname.len + 1 > 20 )
    idStr::ReAllocate(&strippedFname, fname.len + 1, 1);
  v11 = fname.data;
  v12 = strippedFname.data;
  do
  {
    v13 = *v11;
    *v12++ = *v11++;
  }
  while ( v13 );
  strippedFname.len = v10;
  LOBYTE(v39) = 2;
  idStr::StripFileExtension(&strippedFname);
  v14 = 0;
  for ( filenamea = 0; v14 < this->listCache.num; filenamea = (const idStr *)++v14 )
  {
    v15 = this->listCache.list[v14];
    if ( v15 )
    {
      v16 = v15->name.len;
      if ( (int)(v16 + 1) > tmpName.alloced )
        idStr::ReAllocate(&tmpName, v16 + 1, 0);
      qmemcpy(tmpName.data, v15->name.data, v16);
      tmpName.data[v16] = 0;
      tmpName.len = v16;
      idStr::StripFileExtension(&tmpName);
      if ( !idStr::Icmp(tmpName.data, strippedFname.data) )
      {
        v19 = !v15->purged;
        v15->levelLoadReferenced = 1;
        if ( !v19 )
          v15->Load(v15, -1);
        LOBYTE(v39) = 1;
        idStr::FreeData(&strippedFname);
        LOBYTE(v39) = 0;
        idStr::FreeData(&tmpName);
        v39 = -1;
        idStr::FreeData(&fname);
        return v15;
      }
      v14 = (int)filenamea;
    }
  }
  v17 = (rvCommonSample *)Memory::Allocate(0x58u);
  v18 = (idSoundSample *)v17;
  LOBYTE(v39) = 3;
  if ( v17 )
  {
    rvCommonSample::rvCommonSample(v17);
    v18->__vftable = (idSoundSample_vtbl *)&idSoundSample::`vftable';
    v18->nChannels = 0;
    v18->nSamplesPerSec = 0;
    v18->objectSize = 0;
    v18->objectMemSize = 0;
    v18->nonCacheData = 0;
    v18->openalBuffer = 0;
    v18->hardwareBuffer = 0;
    v18->wFormatTag = 0;
    v18->wBitsPerSample = 0;
    v18->nAvgBytesPerSec = 0;
    v18->isOgg = 0;
    filenameb = v18;
  }
  else
  {
    filenameb = 0;
  }
  num = this->listCache.num;
  v22 = 0;
  LOBYTE(v39) = 2;
  if ( num <= 0 )
    goto LABEL_29;
  list = this->listCache.list;
  while ( *list )
  {
    ++v22;
    ++list;
    if ( v22 >= num )
      goto LABEL_29;
  }
  if ( v22 == -1 )
  {
LABEL_29:
    if ( !this->listCache.list )
    {
      granularity = this->listCache.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->listCache.size )
        {
          v26 = granularity < this->listCache.num;
          this->listCache.size = granularity;
          if ( v26 )
            this->listCache.num = granularity;
          this->listCache.list = (idSoundSample **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->listCache.num; ++i )
            this->listCache.list[i] = *(idSoundSample **)(4 * i);
        }
      }
      else
      {
        this->listCache.list = 0;
        this->listCache.num = 0;
        this->listCache.size = 0;
      }
    }
    v28 = this->listCache.num;
    size = this->listCache.size;
    if ( v28 == size )
    {
      if ( !this->listCache.granularity )
        this->listCache.granularity = 16;
      v30 = this->listCache.granularity + size - (this->listCache.granularity + size) % this->listCache.granularity;
      if ( v30 > 0 )
      {
        if ( v30 != this->listCache.size )
        {
          v31 = this->listCache.list;
          this->listCache.size = v30;
          if ( v30 < v28 )
            this->listCache.num = v30;
          this->listCache.list = (idSoundSample **)Memory::Allocate(4 * v30);
          for ( j = 0; j < this->listCache.num; ++j )
            this->listCache.list[j] = v31[j];
          if ( v31 )
            Memory::Free(v31);
        }
      }
      else
      {
        if ( this->listCache.list )
          Memory::Free(this->listCache.list);
        this->listCache.list = 0;
        this->listCache.num = 0;
        this->listCache.size = 0;
      }
    }
    v25 = filenameb;
    this->listCache.list[this->listCache.num++] = filenameb;
  }
  else
  {
    v25 = filenameb;
    this->listCache.list[v22] = filenameb;
  }
  v33 = fname.len;
  p_name = &v25->name;
  if ( fname.len + 1 > v25->name.alloced )
    idStr::ReAllocate(&v25->name, fname.len + 1, 0);
  qmemcpy(p_name->data, fname.data, v33);
  p_name->data[v33] = 0;
  p_name->len = v33;
  filenameb->levelLoadReferenced = 1;
  filenameb->purged = 1;
  if ( com_makingBuild.internalVar->integerValue && !idStr::Cmpn(p_name->data, "sound/vo", 8) )
  {
    for ( k = 0; k < (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 172))(common.type); ++k )
      filenameb->Load(filenameb, k);
    filenameb->PurgeSoundSample(filenameb);
  }
  filenameb->Load(filenameb, -1);
  LOBYTE(v39) = 1;
  idStr::FreeData(&strippedFname);
  LOBYTE(v39) = 0;
  idStr::FreeData(&tmpName);
  v39 = -1;
  idStr::FreeData(&fname);
  return filenameb;
}

// FUNC: public: void __thiscall idSoundCache::ReloadSounds(bool)
void __thiscall idSoundCache::ReloadSounds(idSoundCache *this, bool force)
{
  int i; // esi
  idSoundSample *v4; // ecx

  for ( i = 0; i < this->listCache.num; ++i )
  {
    v4 = this->listCache.list[i];
    if ( v4 )
      idSoundSample::Reload(v4, force);
  }
  S_ExpandOggFiles();
}

// FUNC: public: __thiscall idSoundCache::idSoundCache(void)
void __thiscall idSoundCache::idSoundCache(idSoundCache *this)
{
  idBTreeNode<idDynamicBlock<unsigned char>,int> *v2; // eax
  int granularity; // ecx
  int size; // eax
  int v5; // edi
  bool v6; // cc
  idSoundSample **list; // ebp
  int i; // eax
  int j; // eax
  idSoundSample **v10; // edi
  int num; // ecx
  int v12; // eax
  int k; // eax

  this->listCache.granularity = 16;
  this->listCache.list = 0;
  this->listCache.num = 0;
  this->listCache.size = 0;
  v2 = (idBTreeNode<idDynamicBlock<unsigned char>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&soundCacheAllocator.freeTree.nodeAllocator);
  v2->key = 0;
  v2->parent = 0;
  v2->next = 0;
  v2->prev = 0;
  v2->numChildren = 0;
  v2->firstChild = 0;
  v2->lastChild = 0;
  v2->object = 0;
  soundCacheAllocator.freeTree.root = v2;
  soundCacheAllocator.lockMemory = 1;
  if ( this->listCache.size < 1024 )
  {
    if ( !this->listCache.granularity )
      this->listCache.granularity = 16;
    granularity = this->listCache.granularity;
    size = this->listCache.size;
    this->listCache.num = size;
    v5 = granularity + 1023 - (granularity + 1023) % granularity;
    if ( v5 > 0 )
    {
      if ( v5 != size )
      {
        v6 = v5 < this->listCache.num;
        list = this->listCache.list;
        this->listCache.size = v5;
        if ( v6 )
          this->listCache.num = v5;
        this->listCache.list = (idSoundSample **)Memory::Allocate(4 * v5);
        for ( i = 0; i < this->listCache.num; ++i )
          this->listCache.list[i] = list[i];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->listCache.list )
        Memory::Free(this->listCache.list);
      this->listCache.list = 0;
      this->listCache.num = 0;
      this->listCache.size = 0;
    }
    for ( j = this->listCache.num; j < v5; ++j )
      this->listCache.list[j] = 0;
  }
  this->listCache.num = 1024;
  v10 = this->listCache.list;
  this->listCache.granularity = 256;
  if ( v10 )
  {
    num = this->listCache.num;
    v12 = num + 255 - (num + 255) % 256;
    if ( v12 != this->listCache.size )
    {
      if ( v12 > 0 )
      {
        this->listCache.size = v12;
        if ( v12 < num )
          this->listCache.num = v12;
        this->listCache.list = (idSoundSample **)Memory::Allocate(4 * v12);
        for ( k = 0; k < this->listCache.num; ++k )
          this->listCache.list[k] = v10[k];
        Memory::Free(v10);
      }
      else
      {
        Memory::Free(v10);
        this->listCache.list = 0;
        this->listCache.num = 0;
        this->listCache.size = 0;
      }
    }
  }
  this->insideLevelLoad = 0;
}

// FUNC: public: void __thiscall idSoundCache::BeginLevelLoad(char const *)
void __thiscall idSoundCache::BeginLevelLoad(idSoundCache *this, const char *mapName)
{
  int v3; // ebp
  bool v4; // cc
  idSoundSample **list; // eax
  idSoundSample *v6; // esi

  v3 = 0;
  v4 = this->listCache.num <= 0;
  this->insideLevelLoad = 1;
  if ( !v4 )
  {
    do
    {
      list = this->listCache.list;
      v6 = list[v3];
      if ( v6 )
      {
        if ( com_purgeAll.internalVar->integerValue )
          v6->PurgeSoundSample(list[v3]);
        v6->levelLoadReferenced = 0;
      }
      ++v3;
    }
    while ( v3 < this->listCache.num );
  }
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&soundCacheAllocator);
}

// FUNC: public: void __thiscall idSoundCache::EndLevelLoad(char const *)
void __thiscall idSoundCache::EndLevelLoad(idSoundCache *this, const char *mapName)
{
  int v3; // edi
  int v4; // ebx
  int v5; // ebp
  bool v6; // cc
  idSoundSample *v7; // ecx
  int v8; // esi
  int v9; // esi

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "-------- idSoundCache::EndLevelLoad ---------\n");
  v3 = 0;
  v4 = 0;
  v5 = 0;
  v6 = this->listCache.num <= 0;
  this->insideLevelLoad = 0;
  if ( !v6 )
  {
    do
    {
      v7 = this->listCache.list[v3];
      if ( v7 && !v7->purged )
      {
        if ( v7->levelLoadReferenced )
        {
          v4 += v7->objectMemSize;
        }
        else
        {
          v5 += v7->objectMemSize;
          ((void (*)(void))v7->PurgeSoundSample)();
        }
      }
      ++v3;
    }
    while ( v3 < this->listCache.num );
  }
  v8 = Sys_Milliseconds();
  S_ExpandOggFiles();
  v9 = v8 - Sys_Milliseconds();
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&soundCacheAllocator);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%.2f seconds to expand oggs\n",
    (double)-v9 * 0.001);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%5ik referenced\n",
    v4 / 1024);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%5ik purged\n", v5 / 1024);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::CleanCache(void)
void __thiscall idSoundSystemLocal::CleanCache(idSoundSystemLocal *this)
{
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&soundCacheAllocator);
}

// FUNC: public: __thiscall idSoundCache::~idSoundCache(void)
void __thiscall idSoundCache::~idSoundCache(idSoundCache *this)
{
  int i; // edi
  idSoundSample *v3; // ecx
  idSoundSample **list; // eax

  for ( i = 0; i < this->listCache.num; ++i )
  {
    v3 = this->listCache.list[i];
    if ( v3 )
      ((void (__thiscall *)(idSoundSample *, int))v3->~idSoundSample)(v3, 1);
    this->listCache.list[i] = 0;
  }
  if ( this->listCache.list )
    Memory::Free(this->listCache.list);
  this->listCache.list = 0;
  this->listCache.num = 0;
  this->listCache.size = 0;
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&soundCacheAllocator);
  list = this->listCache.list;
  if ( list )
    Memory::Free(list);
  this->listCache.list = 0;
  this->listCache.num = 0;
  this->listCache.size = 0;
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::FreeSoundSample(unsigned char const *)
void __thiscall idSoundSystemLocal::FreeSoundSample(idSoundSystemLocal *this, idDynamicBlock<int> *address)
{
  ++soundCacheAllocator.numFrees;
  if ( address )
  {
    --soundCacheAllocator.numUsedBlocks;
    soundCacheAllocator.usedBlockMemory -= abs32(address[-1].size);
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&soundCacheAllocator,
      address - 1);
  }
}

// FUNC: public: virtual void __thiscall idSoundSample::Expand(bool)
void __thiscall idSoundSample::Expand(idSoundSample *this, bool force)
{
  int nSamplesPerSec; // eax
  int objectSize; // eax
  bool v5; // zf
  int v6; // edi
  float *id; // ebp
  idDynamicBlock<unsigned char> *v8; // eax
  idDynamicBlock<unsigned char> *v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // edi
  unsigned __int8 *v13; // edi
  idDynamicBlock<unsigned char> *v14; // eax
  idDynamicBlock<unsigned char> *v15; // ecx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // ecx
  float *v20; // edx
  int v21; // eax
  unsigned int *p_openalBuffer; // edi
  idSampleDecoder *forcea; // [esp+1Ch] [ebp+4h]

  if ( !force && !idStr::Cmpn(this->name.data, "sound/vo", 8) )
    return;
  forcea = idSampleDecoder::Alloc();
  nSamplesPerSec = this->nSamplesPerSec;
  if ( nSamplesPerSec == 11025 )
  {
    objectSize = 2 * this->objectSize;
  }
  else
  {
    v5 = nSamplesPerSec == 22050;
    objectSize = this->objectSize;
    if ( !v5 )
      goto LABEL_7;
  }
  objectSize *= 2;
LABEL_7:
  ++soundCacheAllocator.numAllocs;
  v6 = 4 * objectSize + 4;
  if ( v6 > 0 )
  {
    v8 = idDynamicBlockAlloc<unsigned char,1048576,1024,18>::AllocInternal(&soundCacheAllocator, 4 * objectSize + 4);
    if ( v8 )
    {
      v9 = idDynamicBlockAlloc<unsigned char,1048576,1024,18>::ResizeInternal(&soundCacheAllocator, v8, v6);
      if ( v9 )
      {
        ++soundCacheAllocator.numUsedBlocks;
        soundCacheAllocator.usedBlockMemory += abs32(v9->size);
        id = (float *)v9[1].id;
      }
      else
      {
        id = 0;
      }
    }
    else
    {
      id = 0;
    }
  }
  else
  {
    id = 0;
  }
  v10 = this->nSamplesPerSec;
  if ( v10 == 11025 )
  {
    v11 = 2 * this->objectSize;
  }
  else
  {
    v5 = v10 == 22050;
    v11 = this->objectSize;
    if ( !v5 )
      goto LABEL_18;
  }
  v11 *= 2;
LABEL_18:
  ++soundCacheAllocator.numAllocs;
  v12 = 2 * v11 + 2;
  if ( v12 > 0 )
  {
    v14 = idDynamicBlockAlloc<unsigned char,1048576,1024,18>::AllocInternal(&soundCacheAllocator, 2 * v11 + 2);
    if ( v14 )
    {
      v15 = idDynamicBlockAlloc<unsigned char,1048576,1024,18>::ResizeInternal(&soundCacheAllocator, v14, v12);
      if ( v15 )
      {
        ++soundCacheAllocator.numUsedBlocks;
        soundCacheAllocator.usedBlockMemory += abs32(v15->size);
        v13 = (unsigned __int8 *)&v15[1];
      }
      else
      {
        v13 = 0;
      }
    }
    else
    {
      v13 = 0;
    }
  }
  else
  {
    v13 = 0;
  }
  v16 = this->nSamplesPerSec;
  if ( v16 == 11025 )
  {
    v17 = 2 * this->objectSize;
LABEL_28:
    v17 *= 2;
    goto LABEL_29;
  }
  v5 = v16 == 22050;
  v17 = this->objectSize;
  if ( v5 )
    goto LABEL_28;
LABEL_29:
  forcea->Decode(forcea, this, 0, v17, id);
  v18 = this->nSamplesPerSec;
  v19 = 0;
  if ( v18 == 11025 )
  {
    if ( this->objectSize > 0 )
    {
      v20 = id;
      do
      {
        if ( *v20 >= -32768.0 )
        {
          if ( *v20 <= 32767.0 )
            *(_WORD *)&v13[2 * v19] = (int)*v20;
          else
            *(_WORD *)&v13[2 * v19] = 0x7FFF;
        }
        else
        {
          *(_WORD *)&v13[2 * v19] = 0x8000;
        }
        ++v19;
        v20 += 4;
      }
      while ( v19 < this->objectSize );
    }
  }
  else if ( v18 == 22050 )
  {
    if ( this->objectSize > 0 )
    {
      do
      {
        if ( id[2 * v19] >= -32768.0 )
        {
          if ( id[2 * v19] <= 32767.0 )
            *(_WORD *)&v13[2 * v19] = (int)id[2 * v19];
          else
            *(_WORD *)&v13[2 * v19] = 0x7FFF;
        }
        else
        {
          *(_WORD *)&v13[2 * v19] = 0x8000;
        }
        ++v19;
      }
      while ( v19 < this->objectSize );
    }
  }
  else if ( this->objectSize > 0 )
  {
    do
    {
      if ( id[v19] >= -32768.0 )
      {
        if ( id[v19] <= 32767.0 )
          *(_WORD *)&v13[2 * v19] = (int)id[v19];
        else
          *(_WORD *)&v13[2 * v19] = 0x7FFF;
      }
      else
      {
        *(_WORD *)&v13[2 * v19] = 0x8000;
      }
      ++v19;
    }
    while ( v19 < this->objectSize );
  }
  this->PurgeSoundSample(this);
  v21 = 2 * this->objectSize;
  this->nonCacheData = v13;
  this->objectMemSize = v21;
  this->wFormatTag = 1;
  this->wBitsPerSample = 16;
  this->purged = 0;
  if ( idSoundSystemLocal::useOpenAL )
  {
    Sys_EnterCriticalSection(0);
    qalGetError();
    p_openalBuffer = &this->openalBuffer;
    qalGenBuffers(1u, &this->openalBuffer);
    if ( qalGetError() )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "idSoundCache: error generating OpenAL hardware buffer");
    if ( qalIsBuffer(*p_openalBuffer) )
    {
      qalGetError();
      qalBufferData(
        *p_openalBuffer,
        2 * (this->nChannels != 1) + 4353,
        this->nonCacheData,
        this->objectMemSize,
        this->nSamplesPerSec);
      if ( qalGetError() )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
          common.type,
          "idSoundCache: error loading data into OpenAL hardware buffer");
      }
      else
      {
        soundSystem->FreeSoundSample(soundSystem, this->nonCacheData);
        this->hardwareBuffer = 1;
        this->nonCacheData = 0;
      }
    }
    Sys_LeaveCriticalSection(0);
  }
  ++soundCacheAllocator.numFrees;
  if ( id )
  {
    --soundCacheAllocator.numUsedBlocks;
    soundCacheAllocator.usedBlockMemory -= abs32(*((_DWORD *)id - 4));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&soundCacheAllocator,
      (idDynamicBlock<int> *)id - 1);
  }
  idSampleDecoder::Free(forcea);
  this->isOgg = 0;
}

// FUNC: public: virtual void * __thiscall idSoundSystemLocal::AllocSoundSample(int)
idDynamicBlock<unsigned char> *__thiscall idSoundSystemLocal::AllocSoundSample(idSoundSystemLocal *this, int size)
{
  idDynamicBlock<unsigned char> *v2; // eax
  idDynamicBlock<unsigned char> *v3; // ecx

  ++soundCacheAllocator.numAllocs;
  if ( size <= 0 )
    return 0;
  v2 = idDynamicBlockAlloc<unsigned char,1048576,1024,18>::AllocInternal(&soundCacheAllocator, size);
  if ( !v2 )
    return 0;
  v3 = idDynamicBlockAlloc<unsigned char,1048576,1024,18>::ResizeInternal(
         &soundCacheAllocator,
         (idDynamicBlock<int> *)v2,
         size);
  if ( !v3 )
    return 0;
  ++soundCacheAllocator.numUsedBlocks;
  soundCacheAllocator.usedBlockMemory += abs32(v3->size);
  return v3 + 1;
}
