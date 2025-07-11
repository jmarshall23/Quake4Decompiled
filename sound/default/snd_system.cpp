
// FUNC: public: virtual bool __thiscall idSoundSystemLocal::ShutdownHW(void)
char __thiscall idSoundSystemLocal::ShutdownHW(idSoundSystemLocal *this)
{
  unsigned int v3; // ebp
  bool v4; // zf
  idAudioSource *openalSources; // esi
  idSoundChannel *chan; // ecx
  idAudioHardware *snd_audio_hw; // ecx
  unsigned int *graph; // eax

  if ( !this->isInitialized )
    return 0;
  this->shutdown = 1;
  Sys_Sleep(100);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Shutting down sound hardware\n");
  this->ShutdownVoiceComms(this);
  if ( idSoundSystemLocal::useOpenAL )
  {
    Sys_EnterCriticalSection(0);
    v3 = 0;
    v4 = this->openalSourceCount == 0;
    this->efxloaded = 0;
    if ( !v4 )
    {
      openalSources = this->openalSources;
      do
      {
        chan = openalSources->chan;
        if ( chan )
        {
          idSoundChannel::ALStop(chan);
        }
        else
        {
          qalSourceStop(openalSources->handle);
          qalSourcei(openalSources->handle, 4105, 0);
        }
        qalDeleteSources(1u, &openalSources->handle);
        openalSources->handle = 0;
        openalSources->startTime = 0;
        openalSources->chan = 0;
        openalSources->inUse = 0;
        openalSources->looping = 0;
        ++v3;
        ++openalSources;
      }
      while ( v3 < this->openalSourceCount );
    }
    idSoundCache::PurgeSounds(this->soundCache, 1);
    if ( this->openalContext )
    {
      qalcDestroyContext(this->openalContext);
      this->openalContext = 0;
    }
    if ( this->openalDevice )
    {
      qalcCloseDevice(this->openalDevice);
      this->openalDevice = 0;
    }
    idSoundSystemLocal::useOpenAL = 0;
    idSoundSystemLocal::useEAXReverb = 0;
    idSoundSystemLocal::useEAXOcclusion = 0;
    FreeOpenAL();
    Sys_LeaveCriticalSection(0);
  }
  snd_audio_hw = this->snd_audio_hw;
  if ( snd_audio_hw )
    ((void (__thiscall *)(idAudioHardware *, int))snd_audio_hw->~idAudioHardware)(snd_audio_hw, 1);
  graph = this->graph;
  this->snd_audio_hw = 0;
  this->isInitialized = 0;
  if ( graph )
  {
    Mem_Free(graph);
    this->graph = 0;
  }
  return 1;
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::ClearBuffer(void)
void __thiscall idSoundSystemLocal::ClearBuffer(idSoundSystemLocal *this)
{
  unsigned int fBlockLen; // [esp+10h] [ebp-8h] BYREF
  __int16 *fBlock; // [esp+14h] [ebp-4h] BYREF

  if ( this->snd_audio_hw && this->snd_audio_hw->Lock(this->snd_audio_hw, (void **)&fBlock, &fBlockLen) )
  {
    if ( fBlock )
    {
      ((void (__thiscall *)(idSIMDProcessor *, _DWORD, unsigned int))SIMDProcessor->Memset)(SIMDProcessor, 0, fBlockLen);
      this->snd_audio_hw->Unlock(this->snd_audio_hw, fBlock, fBlockLen);
    }
  }
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::AsyncMix(int,float *)
int __thiscall idSoundSystemLocal::AsyncMix(idSoundSystemLocal *this, int soundTime, float *mixBuffer)
{
  int v4; // edi
  int v5; // eax
  int activeSoundWorld; // ecx

  if ( !this->isInitialized || this->shutdown || !this->snd_audio_hw )
    return 0;
  v4 = Sys_Milliseconds();
  v5 = this->snd_audio_hw->GetNumberOfSpeakers(this->snd_audio_hw);
  if ( !this->muted )
  {
    activeSoundWorld = this->activeSoundWorld;
    if ( activeSoundWorld )
      idSoundSystemLocal::MixLoop(this, activeSoundWorld, soundTime, v5, mixBuffer);
  }
  this->CurrentSoundTime = soundTime;
  return Sys_Milliseconds() - v4;
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::SamplesToMilliseconds(int)const
int __thiscall idSoundSystemLocal::SamplesToMilliseconds(idSoundSystemLocal *this, int samples)
{
  return samples / 44;
}

// FUNC: public: int __thiscall idSoundSystemLocal::MillisecondsToSamples(int)const
int __thiscall idSoundSystemLocal::MillisecondsToSamples(idSoundSystemLocal *this, int ms)
{
  return 44 * ms;
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::PlayShaderDirectly(int,char const *,int)
void __thiscall idSoundSystemLocal::PlayShaderDirectly(
        idSoundSystemLocal *this,
        int worldId,
        const char *shaderName,
        int channel)
{
  idSoundEmitterLocal *v6; // ecx
  const idSoundShader *v7; // edi
  int seed; // eax
  int v9; // eax
  float worldIda; // [esp+Ch] [ebp+4h]

  if ( this->isInitialized )
  {
    v6 = this->localSound[worldId];
    if ( v6 )
    {
      if ( channel == -1 )
        v6->StopSound(v6, 0);
      else
        v6->StopSound(v6, channel);
    }
    if ( shaderName )
    {
      if ( *shaderName )
      {
        v7 = declManager->FindSound(declManager, shaderName, 1);
        if ( v7 )
        {
          if ( !this->localSound[worldId] )
            this->localSound[worldId] = idSoundSystemLocal::AllocLocalSoundEmitter(this, worldId, -1);
          if ( (_S78_0 & 1) != 0 )
          {
            seed = rnd.seed;
          }
          else
          {
            _S78_0 |= 1u;
            seed = 0;
          }
          rnd.seed = 69069 * seed + 1;
          v9 = 1;
          if ( channel != -1 )
            v9 = channel;
          worldIda = (double)(rnd.seed & 0x7FFF) * 0.000030517578;
          ((void (__thiscall *)(idSoundEmitterLocal *, const idSoundShader *, int, _DWORD, int))this->localSound[worldId]->StartSound)(
            this->localSound[worldId],
            v7,
            v9,
            LODWORD(worldIda),
            8);
          this->ForegroundUpdate(this);
        }
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::BeginLevelLoad(char const *)
void __thiscall idSoundSystemLocal::BeginLevelLoad(idSoundSystemLocal *this, const char *mapName)
{
  if ( this->isInitialized )
  {
    idSoundCache::BeginLevelLoad(this->soundCache, mapName);
    if ( this->efxloaded )
    {
      idEFXFile::UnloadFile(&this->EFXDatabase);
      this->efxloaded = 0;
    }
  }
}

// FUNC: public: unsigned int __thiscall idSoundSystemLocal::AllocOpenALSource(class idSoundChannel *,bool,bool)
unsigned int __thiscall idSoundSystemLocal::AllocOpenALSource(
        idSoundSystemLocal *this,
        idSoundChannel *chan,
        bool looping,
        bool stereo)
{
  idSoundSystemLocal *v4; // ebx
  int v5; // ebp
  int v6; // edi
  int v7; // eax
  unsigned int openalSourceCount; // esi
  unsigned int v9; // edx
  idSoundChannel **p_chan; // ecx
  int v11; // edi
  char *v12; // esi
  idSoundChannel *v13; // ecx
  unsigned int result; // eax
  int timeOldestZeroVolSingleShot; // [esp+10h] [ebp-18h]
  int iOldestZeroVolSingleShot; // [esp+18h] [ebp-10h]
  int iOldestZeroVolLooping; // [esp+1Ch] [ebp-Ch]
  int iOldestSingle; // [esp+20h] [ebp-8h]
  int time; // [esp+24h] [ebp-4h]

  v4 = this;
  timeOldestZeroVolSingleShot = Sys_Milliseconds();
  v5 = Sys_Milliseconds();
  v6 = Sys_Milliseconds();
  iOldestZeroVolSingleShot = -1;
  iOldestZeroVolLooping = -1;
  iOldestSingle = -1;
  v7 = Sys_Milliseconds();
  openalSourceCount = v4->openalSourceCount;
  v9 = 0;
  time = v7;
  if ( !openalSourceCount )
    return -1;
  p_chan = &v4->openalSources[0].chan;
  while ( *((_BYTE *)p_chan + 6) != stereo )
  {
LABEL_18:
    v4 = this;
    ++v9;
    p_chan += 4;
    if ( v9 >= openalSourceCount )
      goto LABEL_19;
  }
  if ( *((_BYTE *)p_chan + 4) )
  {
    if ( *((_BYTE *)p_chan + 5) )
    {
      if ( *p_chan && (*p_chan)->lastVolume < 0.0009765625 && (int)*(p_chan - 1) < v5 )
      {
        v5 = (int)*(p_chan - 1);
        iOldestZeroVolLooping = v9;
      }
    }
    else if ( *p_chan && (*p_chan)->lastVolume < 0.0009765625 )
    {
      if ( (int)*(p_chan - 1) < timeOldestZeroVolSingleShot )
      {
        timeOldestZeroVolSingleShot = (int)*(p_chan - 1);
        iOldestZeroVolSingleShot = v9;
      }
    }
    else if ( (int)*(p_chan - 1) < v6 )
    {
      v6 = (int)*(p_chan - 1);
      iOldestSingle = v9;
    }
    goto LABEL_18;
  }
  if ( v9 != -1 )
  {
    v11 = v9;
    goto LABEL_22;
  }
LABEL_19:
  v11 = iOldestZeroVolSingleShot;
  if ( iOldestZeroVolSingleShot != -1 )
    goto LABEL_23;
  v11 = iOldestZeroVolLooping;
  if ( iOldestZeroVolLooping != -1 )
    goto LABEL_23;
  v11 = iOldestSingle;
  if ( iOldestSingle == -1 )
    return -1;
LABEL_22:
  if ( v11 == -1 )
    return -1;
LABEL_23:
  v12 = (char *)v4 + 16 * v11;
  v13 = (idSoundChannel *)*((_DWORD *)v12 + 25230);
  if ( v13 )
  {
    if ( v12[100925] )
      v13->triggered = 1;
    else
      idSoundChannel::Stop(v13);
    idSoundChannel::ALStop(*((idSoundChannel **)v12 + 25230));
  }
  *((_DWORD *)v12 + 25230) = chan;
  result = v4->openalSources[v11].handle;
  *((_DWORD *)v12 + 25229) = time;
  v12[100924] = 1;
  v12[100925] = looping;
  return result;
}

// FUNC: public: void __thiscall idSoundSystemLocal::FreeOpenALSource(unsigned int)
void __thiscall idSoundSystemLocal::FreeOpenALSource(idSoundSystemLocal *this, idSoundChannel *handle)
{
  unsigned int v2; // esi
  idSoundChannel **p_chan; // eax

  v2 = 0;
  if ( this->openalSourceCount )
  {
    p_chan = &this->openalSources[0].chan;
    do
    {
      if ( *(p_chan - 2) == handle )
      {
        if ( *p_chan )
          (*p_chan)->openalSource = -1;
        *(p_chan - 1) = 0;
        *p_chan = 0;
        *((_BYTE *)p_chan + 4) = 0;
        *((_BYTE *)p_chan + 5) = 0;
      }
      ++v2;
      p_chan += 4;
    }
    while ( v2 < this->openalSourceCount );
  }
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::IsEAXAvailable(void)
int __thiscall idSoundSystemLocal::IsEAXAvailable(idSoundSystemLocal *this)
{
  struct ALCdevice_struct *v2; // eax
  struct ALCdevice_struct *v3; // edi
  struct ALCcontext_struct *Context; // eax
  struct ALCcontext_struct *v5; // esi
  char IsExtensionPresent; // al

  if ( LoadOpenAL() )
  {
    v2 = qalcOpenDevice(0);
    v3 = v2;
    if ( v2 )
    {
      Context = qalcCreateContext(v2, 0);
      v5 = Context;
      if ( Context )
      {
        qalcMakeContextCurrent(Context);
        if ( qalIsExtensionPresent("EAX4.0") == 1
          || (IsExtensionPresent = qalIsExtensionPresent("EAX5.0"),
              idSoundSystemLocal::EAXAvailable = 0,
              IsExtensionPresent == 1) )
        {
          idSoundSystemLocal::EAXAvailable = 1;
        }
        qalcDestroyContext(v5);
      }
      qalcCloseDevice(v3);
    }
    if ( !idSoundSystemLocal::EAXAvailable )
      FreeOpenAL();
    return idSoundSystemLocal::EAXAvailable;
  }
  else
  {
    idSoundSystemLocal::EAXAvailable = 0;
    return 0;
  }
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::PrintMemInfo(class MemInfo *)
void __thiscall idSoundSystemLocal::PrintMemInfo(idSoundSystemLocal *this, MemInfo *mi)
{
  idSoundCache *soundCache; // ecx

  soundCache = this->soundCache;
  if ( soundCache )
    idSoundCache::PrintMemInfo(soundCache, mi);
}

// FUNC: public: virtual unsigned int __thiscall idSoundSystemLocal::ListSoundSummary(void)
int __thiscall idSoundSystemLocal::ListSoundSummary(idSoundSystemLocal *this)
{
  idSoundCache *soundCache; // ecx

  soundCache = this->soundCache;
  if ( soundCache )
    return idSoundCache::ListSoundSummary(soundCache);
  else
    return 0;
}

// FUNC: public: virtual bool __thiscall idSoundSystemLocal::GetInsideLevelLoad(void)const
BOOL __thiscall idSoundSystemLocal::GetInsideLevelLoad(idSoundSystemLocal *this)
{
  idSoundCache *soundCache; // eax

  soundCache = this->soundCache;
  return soundCache && soundCache->insideLevelLoad;
}

// FUNC: public: virtual class idSoundSample * __thiscall idSoundSystemLocal::FindSample(class idStr const &)
idSoundSample *__thiscall idSoundSystemLocal::FindSample(idSoundSystemLocal *this, const idStr *filename)
{
  return idSoundCache::FindSample(this->soundCache, filename);
}

// FUNC: void __cdecl S_InitDefault(void)
void __cdecl S_InitDefault()
{
  soundSystem = &soundSystemLocal;
}

// FUNC: SoundReloadSounds_f
void __cdecl SoundReloadSounds_f(const idCmdArgs *args, _DWORD *a2)
{
  int v2; // ecx
  void *retaddr; // [esp+Ch] [ebp+0h]

  if ( soundSystemLocal.soundCache )
  {
    ((void (__thiscall *)(idFileSystem *, int, int))fileSystem->SetIsFileLoadingAllowed)(fileSystem, 1, v2);
    LOBYTE(retaddr) = *a2 == 2;
    ((void (__thiscall *)(idSoundSystem *))soundSystem->SetMute)(soundSystem);
    idSoundCache::ReloadSounds(soundSystemLocal.soundCache, 1);
    soundSystem->SetMute(soundSystem, 0);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "sound: changed sounds reloaded\n");
    fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
  }
}

// FUNC: void __cdecl ListSounds_f(class idCmdArgs const &)
void __cdecl ListSounds_f(const idCmdArgs *args)
{
  const char *v1; // ebx
  idSoundCache *soundCache; // ecx
  int v3; // esi
  int v4; // ebp
  int v5; // edi
  idSoundSample *ObjectA; // esi
  const char *v7; // edi
  const char *v8; // edx
  const char *v9; // ecx
  int v10; // ebx
  idSoundSystem_vtbl *v11; // ebp
  int v12; // eax
  int v13; // eax
  unsigned int v14; // edx
  int wFormatTag; // eax
  int v16; // esi
  int EnumValue; // eax
  int Integer; // edi
  int v19; // eax
  int v20; // eax
  int v21; // [esp-18h] [ebp-3Ch]
  const char *v22; // [esp-14h] [ebp-38h]
  char *data; // [esp-10h] [ebp-34h]
  const char *v24; // [esp-Ch] [ebp-30h]
  int totalMemory; // [esp+8h] [ebp-1Ch]
  int totalSounds; // [esp+Ch] [ebp-18h]
  int totalSamples; // [esp+10h] [ebp-14h]
  int totalOGGMemory; // [esp+14h] [ebp-10h]
  int totalPCMMemory; // [esp+18h] [ebp-Ch]
  const char *snd; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]
  const idCmdArgs *argsa; // [esp+28h] [ebp+4h]

  if ( args->argc <= 1 )
    v1 = &entityFilter;
  else
    v1 = args->argv[1];
  soundCache = soundSystemLocal.soundCache;
  v3 = 0;
  snd = v1;
  if ( soundSystemLocal.soundCache )
  {
    v4 = 0;
    v5 = 0;
    totalSounds = 0;
    totalSamples = 0;
    totalMemory = 0;
    argsa = 0;
    totalPCMMemory = 0;
    totalOGGMemory = 0;
    i = 0;
    if ( soundSystemLocal.soundCache->listCache.num > 0 )
    {
      do
      {
        ObjectA = (idSoundSample *)idSoundCache::GetObjectA(soundCache, v5);
        if ( ObjectA && (!v1 || idStr::FindText(ObjectA->name.data, v1, 0, 0, ObjectA->name.len) >= 0) )
        {
          v7 = "ST";
          if ( ObjectA->nChannels != 2 )
            v7 = "  ";
          v8 = "OGG";
          if ( ObjectA->wFormatTag != 2 )
            v8 = "WAV";
          if ( ObjectA->defaultSound )
          {
            v9 = "(DEFAULTED)";
          }
          else
          {
            v9 = "(PURGED)";
            if ( !ObjectA->purged )
              v9 = &entityFilter;
          }
          v10 = *(_DWORD *)common.type;
          v24 = v9;
          v11 = soundSystem->__vftable;
          data = ObjectA->name.data;
          v22 = v8;
          v21 = ObjectA->objectMemSize >> 10;
          v12 = idSoundSample::LengthIn44kHzSamples(ObjectA);
          v13 = v11->SamplesToMilliseconds(soundSystem, v12);
          v14 = (int)((unsigned __int64)(ObjectA->nSamplesPerSec
                                       * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6;
          (*(void (**)(netadrtype_t, const char *, ...))(v10 + 124))(
            common.type,
            "%s %dkHz %6dms %5dkB %4s %s%s\n",
            v7,
            v14 + (v14 >> 31),
            v13,
            v21,
            v22,
            data,
            v24);
          if ( !ObjectA->purged )
          {
            totalSamples += ObjectA->objectSize;
            if ( ObjectA->nonCacheData )
            {
              wFormatTag = ObjectA->wFormatTag;
              if ( wFormatTag == 2 )
                totalOGGMemory += ObjectA->objectMemSize;
              if ( wFormatTag == 1 )
                totalPCMMemory += ObjectA->objectMemSize;
              totalMemory += ObjectA->objectMemSize;
            }
            if ( ObjectA->hardwareBuffer )
              argsa = (const idCmdArgs *)((char *)argsa + ObjectA->objectMemSize);
          }
          ++totalSounds;
          v5 = i;
          v1 = snd;
          v4 = (int)argsa;
        }
        soundCache = soundSystemLocal.soundCache;
        i = ++v5;
      }
      while ( v5 < soundSystemLocal.soundCache->listCache.num );
      v3 = totalMemory;
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%8d total sounds\n",
      totalSounds);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%8d total samples loaded\n",
      totalSamples);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%8d kB OGG samples loaded\n",
      totalOGGMemory >> 10);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%8d kB PCM samples loaded\n",
      totalPCMMemory >> 10);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%8d kB total system memory used\n",
      v3 >> 10);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%8d kB total openal memory used\n",
      v4 >> 10);
    v16 = *(_DWORD *)common.type;
    EnumValue = qalGetEnumValue("AL_EAX_RAM_FREE");
    Integer = qalGetInteger(EnumValue);
    v19 = qalGetEnumValue("AL_EAX_RAM_SIZE");
    v20 = qalGetInteger(v19);
    (*(void (**)(netadrtype_t, const char *, ...))(v16 + 124))(
      common.type,
      "%8d kB total onboard memory used\n",
      (v20 - Integer) >> 10);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "No sound.\n");
  }
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::Shutdown(void)
void __thiscall idSoundSystemLocal::Shutdown(idSoundSystemLocal *this)
{
  idSoundCache *soundCache; // edi

  idSoundSystemLocal::ClearAllSoundEmitters(this);
  this->ShutdownHW(this);
  idEFXFile::Clear(&this->EFXDatabase);
  soundCache = this->soundCache;
  if ( soundCache )
  {
    idSoundCache::~idSoundCache(this->soundCache);
    Memory::Free(soundCache);
  }
  this->soundCache = 0;
  idSampleDecoder::Shutdown();
}

// FUNC: public: int __thiscall idSoundSystemLocal::GetCurrent44kHzTime(void)const
int __thiscall idSoundSystemLocal::GetCurrent44kHzTime(idSoundSystemLocal *this)
{
  if ( this->snd_audio_hw )
    return this->CurrentSoundTime;
  return (int)(float)((double)Sys_Milliseconds() * 176.39999);
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::AsyncUpdate(int)
int __userpurge idSoundSystemLocal::AsyncUpdate@<eax>(
        idSoundSystemLocal *this@<ecx>,
        int a2@<ebp>,
        int a3@<edi>,
        int inTime)
{
  unsigned int v5; // eax
  unsigned int v6; // eax
  idAudioHardware *snd_audio_hw; // ecx
  int v8; // eax
  int v9; // ebp
  unsigned int v10; // edx
  int v11; // edx
  int buffers; // ebx
  unsigned int nextWriteBlock; // edi
  unsigned int v14; // edi
  int v15; // ebx
  int activeSoundWorld; // eax
  __int16 *v17; // edi
  int i; // eax
  __int16 v19; // cx
  int result; // eax
  __int16 *fBlock; // [esp+20h] [ebp-14h] BYREF
  unsigned int dwCurrentWritePos; // [esp+24h] [ebp-10h] BYREF
  unsigned int fBlockLen; // [esp+28h] [ebp-Ch] BYREF
  float v26; // [esp+2Ch] [ebp-8h]
  unsigned int v27; // [esp+30h] [ebp-4h]

  if ( !this->isInitialized
    || this->shutdown
    || !this->snd_audio_hw
    || cvarSystem->GetCVarBool(cvarSystem, "g_stoptime") )
  {
    return 0;
  }
  if ( idSoundSystemLocal::useOpenAL )
  {
    v26 = (double)Sys_Milliseconds() * 44.099998;
    v27 = (int)v26;
    dwCurrentWritePos = (int)v26 % (ROOM_SLICES_IN_BUFFER << 12);
    v5 = dwCurrentWritePos >> 12;
    goto LABEL_9;
  }
  if ( !this->snd_audio_hw->GetCurrentPosition(this->snd_audio_hw, &dwCurrentWritePos) )
    return 0;
  v6 = this->snd_audio_hw->GetMixBufferSize(this->snd_audio_hw);
  v5 = dwCurrentWritePos / v6;
LABEL_9:
  if ( this->nextWriteBlock == -1 )
    this->nextWriteBlock = v5;
  if ( v5 != this->nextWriteBlock )
    return 0;
  fBlock = 0;
  fBlockLen = 0;
  if ( !idSoundSystemLocal::useOpenAL )
  {
    this->snd_audio_hw->Lock(this->snd_audio_hw, (void **)&fBlock, &fBlockLen);
    if ( !fBlock )
      return 0;
  }
  snd_audio_hw = this->snd_audio_hw;
  ++this->soundStats.runs;
  this->soundStats.activeSounds = 0;
  v8 = snd_audio_hw->GetNumberOfSpeakers(snd_audio_hw);
  ++this->nextWriteBlock;
  v9 = v8;
  v10 = this->nextWriteBlock % ROOM_SLICES_IN_BUFFER;
  this->nextWriteBlock = v10;
  v11 = v10 << 12;
  if ( v11 < this->olddwCurrentWritePos )
    ++this->buffers;
  buffers = this->buffers;
  nextWriteBlock = this->nextWriteBlock;
  this->olddwCurrentWritePos = v11;
  v14 = nextWriteBlock << 12;
  v15 = v14 + ((ROOM_SLICES_IN_BUFFER * buffers) << 12);
  if ( v15 > 1879048191 )
    this->buffers = 0;
  if ( v15 - this->CurrentSoundTime > 4096 )
    ++this->soundStats.missedWindow;
  if ( idSoundSystemLocal::useOpenAL )
  {
    if ( idSoundSystemLocal::s_useDeferredSettings.internalVar->integerValue )
      qalcSuspendContext(this->openalContext);
  }
  else
  {
    SIMDProcessor->Memset(SIMDProcessor, this->finalMixBuffer, 0, v8 << 14);
  }
  if ( !this->muted )
  {
    activeSoundWorld = this->activeSoundWorld;
    if ( activeSoundWorld )
      idSoundSystemLocal::MixLoop(this, activeSoundWorld, v15, v9, this->finalMixBuffer);
  }
  if ( idSoundSystemLocal::useOpenAL )
  {
    if ( idSoundSystemLocal::s_useDeferredSettings.internalVar->integerValue )
      qalcProcessContext(this->openalContext);
  }
  else
  {
    v17 = &fBlock[v9 * v14];
    ((void (__fastcall *)(idSIMDProcessor *, __int16 *, float *, int, int, int))SIMDProcessor->MixedSoundToSamples)(
      SIMDProcessor,
      v17,
      this->finalMixBuffer,
      v9 << 12,
      a3,
      a2);
    if ( v9 == 2 && idSoundSystemLocal::s_reverse.internalVar->integerValue )
    {
      for ( i = 0; i < 4096; ++i )
      {
        v19 = v17[2 * i];
        v17[2 * i] = v17[2 * i + 1];
        v17[2 * i + 1] = v19;
      }
    }
    this->snd_audio_hw->Unlock(this->snd_audio_hw, (void *)fBlockLen, v27);
  }
  this->CurrentSoundTime = v15;
  result = Sys_Milliseconds() - inTime;
  this->soundStats.timeinprocess = result;
  return result;
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::AsyncUpdateWrite(int)
int __userpurge idSoundSystemLocal::AsyncUpdateWrite@<eax>(idSoundSystemLocal *this@<ecx>, int a2@<ebp>, int inTime)
{
  idAudioHardware *snd_audio_hw; // ecx
  unsigned int v5; // edi
  unsigned int nextWriteBlock; // eax
  int v8; // ebp
  int v9; // ebx
  int activeSoundWorld; // eax
  __int16 *v11; // edi
  int i; // eax
  __int16 v13; // cx

  if ( !this->isInitialized )
    return 0;
  if ( this->shutdown )
    return 0;
  snd_audio_hw = this->snd_audio_hw;
  if ( !snd_audio_hw )
    return 0;
  if ( !idSoundSystemLocal::useOpenAL )
    snd_audio_hw->Flush(snd_audio_hw);
  v5 = (int)((double)inTime * 0.010766601);
  if ( this->nextWriteBlock == -1 )
    this->nextWriteBlock = v5;
  nextWriteBlock = this->nextWriteBlock;
  if ( nextWriteBlock > v5 )
    return 0;
  if ( nextWriteBlock != v5 )
    Sys_Printf("missed %d sound updates\n", v5 - nextWriteBlock);
  v8 = v5 << 12;
  v9 = this->snd_audio_hw->GetNumberOfSpeakers(this->snd_audio_hw);
  if ( idSoundSystemLocal::useOpenAL )
  {
    if ( idSoundSystemLocal::s_useDeferredSettings.internalVar->integerValue )
      qalcSuspendContext(this->openalContext);
  }
  else
  {
    SIMDProcessor->Memset(SIMDProcessor, this->finalMixBuffer, 0, v9 << 14);
  }
  if ( !this->muted )
  {
    activeSoundWorld = this->activeSoundWorld;
    if ( activeSoundWorld )
      idSoundSystemLocal::MixLoop(this, activeSoundWorld, v5 << 12, v9, this->finalMixBuffer);
  }
  if ( idSoundSystemLocal::useOpenAL )
  {
    if ( idSoundSystemLocal::s_useDeferredSettings.internalVar->integerValue )
      qalcProcessContext(this->openalContext);
  }
  else
  {
    v11 = (__int16 *)((int (__thiscall *)(idAudioHardware *, int))this->snd_audio_hw->GetMixBuffer)(
                       this->snd_audio_hw,
                       a2);
    SIMDProcessor->MixedSoundToSamples(SIMDProcessor, v11, this->finalMixBuffer, v9 << 12);
    if ( v9 == 2 && idSoundSystemLocal::s_reverse.internalVar->integerValue )
    {
      for ( i = 0; i < 4096; ++i )
      {
        v13 = v11[2 * i];
        v11[2 * i] = v11[2 * i + 1];
        v11[2 * i + 1] = v13;
      }
    }
    this->snd_audio_hw->Write(this->snd_audio_hw, 0);
    v5 = (int)((double)inTime * 0.010766601);
  }
  this->nextWriteBlock = v5 + 1;
  this->CurrentSoundTime = v8;
  return Sys_Milliseconds() - inTime;
}

// FUNC: public: virtual struct cinData_t __thiscall idSoundSystemLocal::ImageForTime(int,bool)
cinData_t *__thiscall idSoundSystemLocal::ImageForTime(
        idSoundSystemLocal *this,
        cinData_t *result,
        int milliseconds,
        bool waveform)
{
  idSoundSystemLocal *v4; // ebx
  int v5; // ebp
  float *finalMixBuffer; // esi
  int v7; // eax
  int v8; // edi
  float *v9; // ecx
  int v10; // ebx
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // esi
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  bool v18; // zf
  int v19; // ecx
  int v20; // eax
  int v21; // edx
  int v22; // ebp
  int v23; // esi
  int v24; // ebx
  int v25; // ecx
  int v26; // eax
  int v27; // edx
  float *v28; // ebp
  int v29; // ecx
  int v30; // edx
  float *v31; // eax
  char *v32; // ebx
  unsigned int v33; // esi
  float *v34; // edi
  float *v35; // ebx
  float *v36; // esi
  double v37; // st7
  float *v38; // ebp
  double v39; // st6
  double v40; // st7
  double v41; // st6
  double v42; // st7
  double v43; // st6
  double v44; // st7
  double v45; // st6
  double v46; // st7
  double v47; // st6
  float *v48; // ebp
  double v49; // st7
  double v50; // st6
  float *v51; // ebp
  double v52; // st7
  double v53; // st6
  float *v54; // ebp
  double v55; // st7
  int v56; // esi
  int v57; // edi
  int v58; // edi
  int *v59; // ebx
  unsigned int v60; // esi
  int v61; // eax
  int v62; // ecx
  const unsigned __int8 *graph; // ebx
  cinData_t *v64; // eax
  int v65; // edx
  int meter; // [esp+10h] [ebp-90h]
  int metera; // [esp+10h] [ebp-90h]
  int meterb; // [esp+10h] [ebp-90h]
  int meterc; // [esp+10h] [ebp-90h]
  int v70; // [esp+14h] [ebp-8Ch]
  int *v71; // [esp+14h] [ebp-8Ch]
  float *v72; // [esp+14h] [ebp-8Ch]
  int v73; // [esp+18h] [ebp-88h]
  int v74; // [esp+18h] [ebp-88h]
  float *v75; // [esp+18h] [ebp-88h]
  int xsize; // [esp+1Ch] [ebp-84h]
  int xsizea; // [esp+1Ch] [ebp-84h]
  int xsizeb; // [esp+1Ch] [ebp-84h]
  float *v79; // [esp+20h] [ebp-80h]
  int v81; // [esp+28h] [ebp-78h]
  int v82; // [esp+28h] [ebp-78h]
  float *v83; // [esp+2Ch] [ebp-74h]
  float *v84; // [esp+2Ch] [ebp-74h]
  int v85; // [esp+30h] [ebp-70h]
  float *v86; // [esp+30h] [ebp-70h]
  int *v87; // [esp+34h] [ebp-6Ch]
  float *v88; // [esp+34h] [ebp-6Ch]
  int v89; // [esp+38h] [ebp-68h]
  int time; // [esp+3Ch] [ebp-64h]
  float *v91; // [esp+40h] [ebp-60h]
  float *v92; // [esp+44h] [ebp-5Ch]
  float *v93; // [esp+48h] [ebp-58h]
  int xx; // [esp+4Ch] [ebp-54h]
  float *v95; // [esp+50h] [ebp-50h]
  float *v96; // [esp+54h] [ebp-4Ch]
  int v97; // [esp+58h] [ebp-48h]
  float *v98; // [esp+5Ch] [ebp-44h]
  int *meterTops; // [esp+60h] [ebp-40h]
  float *v100; // [esp+64h] [ebp-3Ch]
  float *v101; // [esp+68h] [ebp-38h]
  float *v102; // [esp+6Ch] [ebp-34h]
  float *v103; // [esp+70h] [ebp-30h]
  int v104; // [esp+74h] [ebp-2Ch]
  float *v105; // [esp+78h] [ebp-28h]
  float *v106; // [esp+7Ch] [ebp-24h]
  char *v107; // [esp+80h] [ebp-20h]
  unsigned int v108; // [esp+84h] [ebp-1Ch]
  unsigned int colors[6]; // [esp+88h] [ebp-18h] BYREF

  v4 = this;
  if ( this->isInitialized )
  {
    v5 = 0;
    if ( this->snd_audio_hw )
    {
      Sys_EnterCriticalSection(0);
      if ( !v4->graph )
        v4->graph = (unsigned int *)Mem_Alloc(0x20000, 0x12u);
      memset(v4->graph, 0, 0x20000u);
      finalMixBuffer = v4->finalMixBuffer;
      time = Sys_Milliseconds();
      v7 = v4->snd_audio_hw->GetNumberOfSpeakers(v4->snd_audio_hw);
      v8 = v7;
      if ( waveform )
      {
        colors[0] = -16744704;
        colors[1] = -16744577;
        colors[2] = -16777089;
        colors[3] = -16711936;
        colors[4] = -16711681;
        colors[5] = -16776961;
        if ( v7 > 0 )
        {
          xsizeb = (int)&finalMixBuffer[7 * v7];
          v88 = &finalMixBuffer[6 * v7];
          v86 = &finalMixBuffer[5 * v7];
          v91 = &finalMixBuffer[3 * v7];
          v93 = &finalMixBuffer[2 * v7];
          v96 = &finalMixBuffer[v7];
          v28 = &finalMixBuffer[4 * v7];
          v29 = 32 * v7;
          v30 = v7 << 6;
          v31 = finalMixBuffer;
          v32 = (char *)((char *)colors - (char *)finalMixBuffer);
          v100 = finalMixBuffer;
          v101 = &finalMixBuffer[4 * v8];
          v107 = (char *)((char *)colors - (char *)finalMixBuffer);
          v82 = v8;
          meterc = v8;
          while ( 1 )
          {
            v33 = *(_DWORD *)((char *)v31 + (_DWORD)v32);
            v34 = v93;
            v35 = v91;
            v92 = v28;
            v108 = v33;
            v95 = v86;
            meterTops = this->meterTops;
            v36 = v96;
            v98 = v88;
            xx = 0;
            v105 = v31;
            v102 = v96;
            v106 = v93;
            v103 = v91;
            v97 = xsizeb;
            v104 = 256;
            do
            {
              v37 = 0.0;
              v79 = (float *)v97;
              v84 = v98;
              v75 = v95;
              v72 = v92;
              v89 = 2;
              do
              {
                v38 = v72;
                v39 = *v31 * 0.000030517578;
                v72 = (float *)((char *)v72 + v29);
                v31 = (float *)((char *)v31 + v29);
                v40 = v37 + v39;
                v41 = *v36;
                v36 = (float *)((char *)v36 + v29);
                v42 = v40 + v41 * 0.000030517578;
                v43 = *v34;
                v34 = (float *)((char *)v34 + v29);
                v44 = v42 + v43 * 0.000030517578;
                v45 = *v35;
                v35 = (float *)((char *)v35 + v29);
                v46 = v44 + v45 * 0.000030517578;
                v47 = *v38;
                v48 = v75;
                v75 = (float *)((char *)v75 + v29);
                v49 = v46 + v47 * 0.000030517578;
                v50 = *v48;
                v51 = v84;
                v84 = (float *)((char *)v84 + v29);
                v52 = v49 + v50 * 0.000030517578;
                v53 = *v51;
                v54 = v79;
                v79 = (float *)((char *)v79 + v29);
                v18 = v89-- == 1;
                v37 = v52 + v53 * 0.000030517578 + *v54 * 0.000030517578;
              }
              while ( !v18 );
              v55 = v37 * 0.25;
              if ( v55 >= -1.0 )
              {
                if ( v55 > 1.0 )
                  v55 = 1.0;
              }
              else
              {
                v55 = -1.0;
              }
              v56 = (int)(63.0 * v55);
              this->graph[256 * v56 + 0x4000 + xx] = v108;
              if ( v56 < 0 )
                v56 = -v56;
              v57 = *meterTops;
              if ( v56 <= *meterTops )
              {
                if ( time > meterTops[256] && v57 > 0 )
                {
                  *meterTops = v57 - 1;
                  if ( v57 != 1 )
                    *meterTops = v57 - 2;
                }
              }
              else
              {
                *meterTops = v56;
                meterTops[256] = time + 100;
              }
              ++xx;
              v97 += v30;
              v98 = (float *)((char *)v98 + v30);
              v95 = (float *)((char *)v95 + v30);
              v92 = (float *)((char *)v92 + v30);
              ++meterTops;
              v35 = (float *)((char *)v103 + v30);
              v34 = (float *)((char *)v106 + v30);
              v36 = (float *)((char *)v102 + v30);
              v31 = (float *)((char *)v105 + v30);
              v18 = v104-- == 1;
              v103 = (float *)((char *)v103 + v30);
              v106 = (float *)((char *)v106 + v30);
              v102 = (float *)((char *)v102 + v30);
              v105 = (float *)((char *)v105 + v30);
            }
            while ( !v18 );
            ++v96;
            ++v93;
            ++v91;
            ++v86;
            ++v88;
            xsizeb += 4;
            v31 = v100 + 1;
            v28 = v101 + 1;
            v18 = v82-- == 1;
            ++v100;
            ++v101;
            if ( v18 )
              break;
            v32 = v107;
          }
          v5 = meterc;
          v4 = this;
        }
        v58 = 0;
        v59 = v4->meterTops;
        do
        {
          if ( -*v59 < *v59 )
          {
            v60 = colors[v5];
            v61 = v58 + ((64 - *v59) << 8);
            v62 = 2 * *v59;
            do
            {
              this->graph[v61] = v60;
              v61 += 256;
              --v62;
            }
            while ( v62 );
          }
          ++v58;
          ++v59;
        }
        while ( v58 < 256 );
      }
      else
      {
        if ( v7 > 0 )
        {
          v70 = 0;
          v73 = 0;
          v83 = finalMixBuffer;
          v87 = v4->meterTops;
          v85 = v7;
          do
          {
            v9 = v83;
            v10 = 0;
            meter = 0;
            v11 = 4096;
            do
            {
              xsize = *(_DWORD *)v9 & 0x7FFFFFFF;
              if ( (double)meter < *(float *)&xsize )
                meter = (int)*(float *)&xsize;
              v9 += v8;
              --v11;
            }
            while ( v11 );
            metera = meter / 256;
            if ( metera > 128 )
              metera = 128;
            if ( v8 == 6 )
            {
              v12 = v73;
              v13 = 20;
            }
            else
            {
              v12 = v70;
              v13 = 63;
            }
            v14 = v12 + 130048;
            do
            {
              v15 = v14;
              v16 = v13;
              do
              {
                *(unsigned int *)((char *)this->graph + v15) = -16711936;
                v15 += 4;
                --v16;
              }
              while ( v16 );
              if ( v10 > metera )
                break;
              ++v10;
              v14 -= 1024;
            }
            while ( v10 < 128 );
            v17 = *v87;
            if ( metera <= *v87 )
            {
              if ( time > v87[256] && v17 > 0 )
              {
                *v87 = v17 - 1;
                if ( v17 != 1 )
                  *v87 = v17 - 2;
              }
            }
            else
            {
              *v87 = metera;
              v87[256] = time + idSoundSystemLocal::s_meterTopTime.internalVar->integerValue;
            }
            ++v83;
            v73 += 160;
            v70 += 512;
            v18 = v85-- == 1;
            ++v87;
          }
          while ( !v18 );
          v4 = this;
        }
        v19 = 0;
        meterb = 0;
        if ( v8 <= 0 )
          goto LABEL_74;
        v74 = 0;
        v71 = v4->meterTops;
        do
        {
          v20 = *v71;
          if ( v8 == 6 )
          {
            v21 = v74;
            v22 = 20;
          }
          else
          {
            v21 = v19 << 7;
            v22 = 63;
          }
          xsizea = v22;
          if ( v20 > 80 )
            v23 = v20 > 112 ? -16777089 : -16744577;
          else
            v23 = -16744704;
          v24 = *v71;
          if ( v20 < 128 )
          {
            v81 = v20 + 4;
            v25 = 4 * (v21 + ((127 - v20) << 8));
            do
            {
              if ( v24 >= v81 )
                break;
              v26 = v25;
              v27 = v22;
              do
              {
                *(unsigned int *)((char *)this->graph + v26) = v23;
                v26 += 4;
                --v27;
              }
              while ( v27 );
              v22 = xsizea;
              ++v24;
              v25 -= 1024;
            }
            while ( v24 < 128 );
            v19 = meterb;
          }
          ++v71;
          v74 += 40;
          meterb = ++v19;
        }
        while ( v19 < v8 );
      }
      v4 = this;
LABEL_74:
      graph = (const unsigned __int8 *)v4->graph;
      Sys_LeaveCriticalSection(0);
      v64 = result;
      v65 = colors[3];
      result->imageWidth = 256;
      result->imageHeight = 128;
      result->image = graph;
      result->status = v65;
      return v64;
    }
  }
  v64 = result;
  result->imageWidth = 0;
  result->imageHeight = 0;
  result->image = 0;
  result->status = 0;
  return v64;
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::FreeSoundEmitter(int,int,bool)
void __thiscall idSoundSystemLocal::FreeSoundEmitter(idSoundSystemLocal *this, int worldId, int index, BOOL immediate)
{
  idSoundEmitter *v4; // eax
  idSoundEmitter *v5; // edi

  v4 = idSoundSystemLocal::EmitterForIndex(&soundSystemLocal, worldId, index);
  v5 = v4;
  if ( v4 && !v4[3].__vftable )
  {
    if ( s_showStartSound.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "FreeSound (%i,%i)\n",
        index,
        immediate);
    if ( worldId && soundSystemLocal.writeDemo )
    {
      soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 2);
      soundSystemLocal.writeDemo->WriteChar(soundSystemLocal.writeDemo, 3);
      soundSystemLocal.writeDemo->WriteInt(soundSystemLocal.writeDemo, index);
      soundSystemLocal.writeDemo->WriteBool(soundSystemLocal.writeDemo, immediate);
    }
    Sys_EnterCriticalSection(0);
    if ( immediate )
      idSoundEmitterLocal::Clear((idSoundEmitterLocal *)v5);
    else
      v5[3].__vftable = (idSoundEmitter_vtbl *)1;
    Sys_LeaveCriticalSection(0);
  }
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::SetMute(bool)
void __thiscall idSoundSystemLocal::SetMute(idSoundSystemLocal *this, bool muteOn)
{
  int CurrentSoundTime; // eax
  int i; // ebx
  idSoundEmitterLocal *v5; // eax
  idSoundChannel *channels; // esi
  int v7; // edi
  int v8; // eax
  int j; // ebx
  idSoundEmitterLocal *v10; // eax
  idSoundChannel *v11; // esi
  int v12; // edi
  float muteOna; // [esp+10h] [ebp+4h]
  float muteOnb; // [esp+10h] [ebp+4h]

  if ( muteOn != this->muted )
  {
    this->muted = muteOn;
    Sys_EnterCriticalSection(0);
    if ( muteOn )
    {
      if ( this->pause44kHz >= 0 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
          common.type,
          "idSoundSystemLocal::SetMute: already paused");
      if ( soundSystemLocal.snd_audio_hw )
      {
        CurrentSoundTime = soundSystemLocal.CurrentSoundTime;
      }
      else
      {
        muteOna = (double)Sys_Milliseconds() * 176.39999;
        CurrentSoundTime = (int)muteOna;
      }
      this->pause44kHz = CurrentSoundTime;
      if ( idSoundSystemLocal::useOpenAL )
      {
        for ( i = 1; i < this->emitters.num; ++i )
        {
          v5 = this->emitters.list[i];
          if ( v5 && v5->playing )
          {
            channels = v5->channels;
            v7 = 8;
            do
            {
              if ( channels->triggerState )
                qalSourcePause(channels->openalSource);
              ++channels;
              --v7;
            }
            while ( v7 );
          }
        }
      }
    }
    else
    {
      if ( this->pause44kHz < 0 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
          common.type,
          "idSoundSystemLocal::SetMute: not paused");
      if ( soundSystemLocal.snd_audio_hw )
      {
        v8 = soundSystemLocal.CurrentSoundTime;
      }
      else
      {
        muteOnb = (double)Sys_Milliseconds() * 176.39999;
        v8 = (int)muteOnb;
      }
      idSoundSystemLocal::OffsetSoundTime(this, v8 - this->pause44kHz);
      this->pause44kHz = -1;
      if ( idSoundSystemLocal::useOpenAL )
      {
        for ( j = 1; j < this->emitters.num; ++j )
        {
          v10 = this->emitters.list[j];
          if ( v10 && v10->playing )
          {
            v11 = v10->channels;
            v12 = 8;
            do
            {
              if ( v11->triggerState )
                qalSourcePlay(v11->openalSource);
              ++v11;
              --v12;
            }
            while ( v12 );
          }
        }
      }
    }
    Sys_LeaveCriticalSection(0);
  }
}

// FUNC: public: virtual char const * __thiscall idSoundSystemLocal::GetDeviceName(int)
const char *__thiscall idSoundSystemLocal::GetDeviceName(idSoundSystemLocal *this, int index)
{
  int v2; // eax
  unsigned __int8 *String; // ebp
  int v5; // ebx
  char *v6; // edi
  int v7; // eax
  const char *v8; // eax
  struct ALCdevice_struct *v9; // esi
  struct ALCcontext_struct *Context; // edi
  int v11; // edx
  const char *v12; // eax
  const char *v13; // eax
  int v14; // eax

  v2 = 0;
  if ( idSoundSystemLocal::defaultDeviceName[0] )
  {
    do
      ++v2;
    while ( idSoundSystemLocal::defaultDeviceName[v2] );
    if ( v2 )
      goto LABEL_29;
  }
  if ( !LoadOpenAL() )
    return (const char *)idSoundSystemLocal::deviceName;
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "...checking for ALC_ENUMERATION_EXT: ");
  if ( qalcIsExtensionPresent && qalcIsExtensionPresent(0, "ALC_ENUMERATION_EXT") == 1 )
  {
    String = qalcGetString(0, 4101);
    v5 = 0;
    v6 = (char *)idSoundSystemLocal::deviceName;
    do
    {
      idStr::Copynz(v6, (const char *)&String[v5], 128);
      if ( String[v5] )
      {
        v7 = 0;
        do
          ++v7;
        while ( String[v5 + v7] );
        v5 += v7 + 1;
      }
      v6 += 128;
    }
    while ( (int)v6 < (int)idSoundSystemLocal::deviceName[6] );
    v8 = (const char *)qalcGetString(0, 4100);
    idStr::Copynz((char *)idSoundSystemLocal::defaultDeviceName, v8, 128);
    goto LABEL_28;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "failed\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "...creating AL device: ");
  v9 = qalcOpenDevice(0);
  if ( !v9 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "failed\n");
    goto LABEL_28;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "...creating AL context: ");
  Context = qalcCreateContext(v9, 0);
  v11 = *(_DWORD *)common.type;
  if ( !Context )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(v11 + 124))(common.type, "failed\n");
    qalcCloseDevice(v9);
    goto LABEL_28;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(v11 + 124))(common.type, "succeeded\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "...making context current: ");
  if ( qalcMakeContextCurrent(Context) != 1 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "failed\n");
LABEL_25:
    qalcDestroyContext(Context);
    qalcCloseDevice(v9);
    goto LABEL_28;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
  v12 = (const char *)qalcGetString(v9, 4101);
  idStr::Copynz((char *)idSoundSystemLocal::deviceName, v12, 128);
  v13 = (const char *)qalcGetString(v9, 4101);
  idStr::Copynz((char *)idSoundSystemLocal::defaultDeviceName, v13, 128);
  if ( !idStr::Icmp((const char *)idSoundSystemLocal::deviceName, "SoundBlaster Audigy")
    && !qalIsExtensionPresent("EAX3.0") )
  {
    idStr::Copynz((char *)idSoundSystemLocal::deviceName, "SB Live Audio", 128);
  }
  if ( idStr::Icmp((const char *)idSoundSystemLocal::defaultDeviceName, "SoundBlaster Audigy")
    || qalIsExtensionPresent("EAX3.0") )
  {
    goto LABEL_25;
  }
  idStr::Copynz((char *)idSoundSystemLocal::defaultDeviceName, "SB Live Audio", 128);
  qalcDestroyContext(Context);
  qalcCloseDevice(v9);
LABEL_28:
  FreeOpenAL();
LABEL_29:
  v14 = index;
  if ( index >= 7 )
    v14 = 7;
  return (const char *)idSoundSystemLocal::deviceName[v14];
}

// FUNC: public: virtual char const * __thiscall idSoundSystemLocal::GetDefaultDeviceName(void)
const char *__thiscall idSoundSystemLocal::GetDefaultDeviceName(idSoundSystemLocal *this)
{
  int v1; // eax
  unsigned __int8 *String; // ebp
  int v3; // ebx
  char *v4; // edi
  int v5; // eax
  const char *v6; // eax
  struct ALCdevice_struct *v8; // esi
  struct ALCcontext_struct *Context; // edi
  int v10; // ecx
  const char *v11; // eax
  const char *v12; // eax

  v1 = 0;
  if ( idSoundSystemLocal::defaultDeviceName[0] )
  {
    do
      ++v1;
    while ( idSoundSystemLocal::defaultDeviceName[v1] );
    if ( v1 )
      return (const char *)idSoundSystemLocal::defaultDeviceName;
  }
  if ( !LoadOpenAL() )
    return (const char *)idSoundSystemLocal::defaultDeviceName;
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "...checking for ALC_ENUMERATION_EXT: ");
  if ( qalcIsExtensionPresent && qalcIsExtensionPresent(0, "ALC_ENUMERATION_EXT") == 1 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
    String = qalcGetString(0, 4101);
    v3 = 0;
    v4 = (char *)idSoundSystemLocal::deviceName;
    do
    {
      idStr::Copynz(v4, (const char *)&String[v3], 128);
      if ( String[v3] )
      {
        v5 = 0;
        do
          ++v5;
        while ( String[v3 + v5] );
        v3 += v5 + 1;
      }
      v4 += 128;
    }
    while ( (int)v4 < (int)idSoundSystemLocal::deviceName[6] );
    v6 = (const char *)qalcGetString(0, 4100);
    idStr::Copynz((char *)idSoundSystemLocal::defaultDeviceName, v6, 128);
    FreeOpenAL();
    return (const char *)idSoundSystemLocal::defaultDeviceName;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "failed\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "...creating AL device: ");
  v8 = qalcOpenDevice(0);
  if ( !v8 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "failed\n");
    FreeOpenAL();
    return (const char *)idSoundSystemLocal::defaultDeviceName;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "...creating AL context: ");
  Context = qalcCreateContext(v8, 0);
  v10 = *(_DWORD *)common.type;
  if ( Context )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(v10 + 124))(common.type, "succeeded\n");
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "...making context current: ");
    if ( qalcMakeContextCurrent(Context) == 1 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
      v11 = (const char *)qalcGetString(v8, 4101);
      idStr::Copynz((char *)idSoundSystemLocal::deviceName, v11, 128);
      v12 = (const char *)qalcGetString(v8, 4101);
      idStr::Copynz((char *)idSoundSystemLocal::defaultDeviceName, v12, 128);
      if ( !idStr::Icmp((const char *)idSoundSystemLocal::deviceName, "SoundBlaster Audigy")
        && !qalIsExtensionPresent("EAX3.0") )
      {
        idStr::Copynz((char *)idSoundSystemLocal::deviceName, "SB Live Audio", 128);
      }
      if ( !idStr::Icmp((const char *)idSoundSystemLocal::defaultDeviceName, "SoundBlaster Audigy")
        && !qalIsExtensionPresent("EAX3.0") )
      {
        idStr::Copynz((char *)idSoundSystemLocal::defaultDeviceName, "SB Live Audio", 128);
        qalcDestroyContext(Context);
        qalcCloseDevice(v8);
        FreeOpenAL();
        return (const char *)idSoundSystemLocal::defaultDeviceName;
      }
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "failed\n");
    }
    qalcDestroyContext(Context);
    qalcCloseDevice(v8);
    FreeOpenAL();
    return (const char *)idSoundSystemLocal::defaultDeviceName;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(v10 + 124))(common.type, "failed\n");
    qalcCloseDevice(v8);
    FreeOpenAL();
    return (const char *)idSoundSystemLocal::defaultDeviceName;
  }
}

// FUNC: public: virtual bool __thiscall idSoundSystemLocal::ValidateSoundShader(class idSoundShader *)
char __thiscall idSoundSystemLocal::ValidateSoundShader(idSoundSystemLocal *this, idSoundShader *shader)
{
  int v3; // edi
  const char *v4; // eax
  float shadera; // [esp+8h] [ebp+4h]

  shadera = shader->GetMaxDistance(shader);
  if ( ((double (__thiscall *)(idSoundShader *))shader->GetMinDistance)(shader) <= shadera )
    return 1;
  v3 = *(_DWORD *)common.type;
  v4 = shader->base->GetName(shader->base);
  (*(void (**)(netadrtype_t, const char *, ...))(v3 + 136))(
    common.type,
    "max distance less than min distance for '%s'",
    v4);
  shader->base->MakeDefault(shader->base);
  return 0;
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::SetActiveSoundWorld(bool)
int __thiscall idSoundSystemLocal::SetActiveSoundWorld(idSoundSystemLocal *this, BOOL on)
{
  int activeSoundWorld; // esi
  idSession_vtbl *v4; // eax
  int v5; // eax
  idSoundEmitterLocal *v6; // edi
  unsigned int *p_openalSource; // esi
  int v8; // ebp
  bool soundPaused; // [esp+Bh] [ebp-5h] BYREF
  int old; // [esp+Ch] [ebp-4h]
  int ona; // [esp+14h] [ebp+4h]

  activeSoundWorld = this->activeSoundWorld;
  soundPaused = 0;
  v4 = session->__vftable;
  old = activeSoundWorld;
  this->activeSoundWorld = v4->GetDesiredSoundWorld(session, on, &soundPaused);
  if ( idSoundSystemLocal::useOpenAL )
  {
    v5 = 1;
    ona = 1;
    if ( this->emitters.num > 1 )
    {
      do
      {
        v6 = this->emitters.list[v5];
        if ( v6 && v6->playing )
        {
          p_openalSource = &v6->channels[0].openalSource;
          v8 = 8;
          do
          {
            if ( *((_BYTE *)p_openalSource - 120) )
            {
              if ( v6->AttachedToWorld(v6, this->activeSoundWorld) )
                qalSourcePlay(*p_openalSource);
              else
                qalSourcePause(*p_openalSource);
            }
            p_openalSource += 41;
            --v8;
          }
          while ( v8 );
          v5 = ona;
        }
        ona = ++v5;
      }
      while ( v5 < this->emitters.num );
      activeSoundWorld = old;
    }
  }
  if ( s_showStartSound.internalVar->integerValue > 0 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Make sound world %d active\n",
      this->activeSoundWorld);
  return activeSoundWorld;
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::Frame(void)
void __thiscall idSoundSystemLocal::Frame(idSoundSystemLocal *this)
{
  idSoundSystemLocal_vtbl *v2; // edi
  float v3; // [esp+0h] [ebp-14h]

  if ( (s_musicVolume.internalVar->flags & 0x40000) != 0 )
  {
    v2 = this->__vftable;
    v3 = idMath::ScaleToDb(s_musicVolume.internalVar->floatValue);
    ((void (__thiscall *)(idSoundSystemLocal *, int, int, _DWORD, _DWORD))v2->FadeSoundClasses)(
      this,
      -1,
      3,
      LODWORD(v3),
      0);
    BYTE2(s_musicVolume.internalVar->flags) &= ~4u;
  }
}

// FUNC: public: void __thiscall idSoundSystemLocal::ListSoundDecoders(class idCmdArgs const &)
void __thiscall idSoundSystemLocal::ListSoundDecoders(idSoundSystemLocal *this, const idCmdArgs *args)
{
  idSoundSystemLocal *v2; // ebx
  int v3; // esi
  int v4; // edi
  int v5; // eax
  _DWORD *v6; // esi
  int v7; // edx
  const char *v8; // ecx
  int v9; // esi
  int v10; // eax
  _DWORD *v11; // ebp
  int v12; // eax
  idSoundSample *v13; // edi
  const char *v14; // ebx
  int CurrentSoundTime; // esi
  int v16; // esi
  int v17; // ecx
  int v18; // eax
  int v19; // eax
  int v20; // esi
  int UsedBlockMemory; // eax
  int NumUsedBlocks; // [esp-4h] [ebp-30h]
  int i; // [esp+10h] [ebp-1Ch]
  int ia; // [esp+10h] [ebp-1Ch]
  int numWaitingDecoders; // [esp+14h] [ebp-18h]
  int numWaitingDecodersa; // [esp+14h] [ebp-18h]
  int numActiveDecoders; // [esp+18h] [ebp-14h]
  int v28; // [esp+1Ch] [ebp-10h]
  float v29; // [esp+20h] [ebp-Ch]

  v2 = this;
  v3 = 0;
  v4 = 0;
  numWaitingDecoders = 0;
  numActiveDecoders = 0;
  i = 0;
  if ( ((int (__fastcall *)(idSoundSystemLocal *))this->GetNumEmitters)(this) > 0 )
  {
    do
    {
      v5 = (int)v2->EmitterForIndex(v2, -1, v3);
      if ( v5 )
      {
        v6 = (_DWORD *)(v5 + 172);
        numWaitingDecodersa = 8;
        do
        {
          if ( *v6 && !(*(int (__thiscall **)(_DWORD))(*(_DWORD *)*v6 + 12))(*v6) )
          {
            v7 = *(v6 - 4);
            v8 = "OGG";
            if ( *(_DWORD *)(v7 + 72) != 2 )
              v8 = "WAV";
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "%3d waiting %s: %s\n",
              v4++,
              v8,
              *(_DWORD *)(v7 + 8));
          }
          v6 += 41;
          --numWaitingDecodersa;
        }
        while ( numWaitingDecodersa );
        v3 = i;
      }
      i = ++v3;
    }
    while ( v3 < v2->GetNumEmitters(v2) );
    numWaitingDecoders = v4;
  }
  v9 = 0;
  ia = 0;
  if ( v2->GetNumEmitters(v2) <= 0 )
    goto LABEL_34;
  do
  {
    v10 = (int)v2->EmitterForIndex(v2, -1, v9);
    if ( !v10 )
      goto LABEL_33;
    v11 = (_DWORD *)(v10 + 172);
    v28 = 8;
    do
    {
      if ( !*v11 )
        goto LABEL_31;
      v12 = (*(int (__thiscall **)(_DWORD))(*(_DWORD *)*v11 + 12))(*v11);
      v13 = (idSoundSample *)v12;
      if ( v12 )
      {
        v14 = "OGG";
        if ( *(_DWORD *)(v12 + 72) != 2 )
          v14 = "WAV";
        if ( soundSystemLocal.snd_audio_hw )
        {
          CurrentSoundTime = soundSystemLocal.CurrentSoundTime;
        }
        else
        {
          v29 = (double)Sys_Milliseconds() * 176.39999;
          CurrentSoundTime = (int)v29;
        }
        v16 = CurrentSoundTime - *(v11 - 15);
        v17 = v13->nChannels * idSoundSample::LengthIn44kHzSamples(v13);
        if ( v16 <= v17 )
        {
          v18 = 25 * v16;
LABEL_28:
          v19 = 4 * v18 / v17;
        }
        else
        {
          if ( (*(_BYTE *)(v11 - 9) & 0x20) != 0 )
          {
            v18 = 25 * (v16 % v17);
            goto LABEL_28;
          }
          v19 = 100;
        }
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%3d decoding %3d%% %s: %s\n",
          numActiveDecoders,
          v19,
          v14,
          v13->name.data);
        v2 = this;
        ++numActiveDecoders;
      }
      v4 = numWaitingDecoders;
LABEL_31:
      v11 += 41;
      --v28;
    }
    while ( v28 );
    v9 = ia;
LABEL_33:
    ia = ++v9;
  }
  while ( v9 < v2->GetNumEmitters(v2) );
LABEL_34:
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%d decoders\n",
    v4 + numActiveDecoders);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%d waiting decoders\n",
    v4);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%d active decoders\n",
    numActiveDecoders);
  v20 = *(_DWORD *)common.type;
  NumUsedBlocks = idSampleDecoder::GetNumUsedBlocks();
  UsedBlockMemory = idSampleDecoder::GetUsedBlockMemory();
  (*(void (**)(netadrtype_t, const char *, ...))(v20 + 124))(
    common.type,
    "%d kB decoder memory in %d blocks\n",
    UsedBlockMemory >> 10,
    NumUsedBlocks);
}

// FUNC: void __cdecl ListSoundDecoders_f(class idCmdArgs const &)
void __cdecl ListSoundDecoders_f(const idCmdArgs *args)
{
  idSoundSystemLocal::ListSoundDecoders(&soundSystemLocal, args);
}

// FUNC: public: virtual bool __thiscall idSoundSystemLocal::InitHW(void)
// local variable allocation has failed, the output may be wrong!
char __thiscall idSoundSystemLocal::InitHW(idSoundSystemLocal *this)
{
  idAudioHardware *snd_audio_hw; // ecx
  idAudioHardware *v3; // eax
  const char *value; // ecx
  int v6; // eax
  struct ALCdevice_struct *v7; // eax
  struct ALCcontext_struct *Context; // eax
  const char *String; // eax
  const _GUID *v10; // ebx
  bool v11; // cl
  int v12; // eax
  _DWORD *v13; // edx
  int v14; // ecx
  unsigned int Data1; // ecx
  _GUID *v16; // ebx
  bool v17; // cl
  unsigned int v18; // eax
  unsigned int *v19; // edx
  unsigned int v20; // ecx
  unsigned int v21; // ecx
  int v22; // edi
  int EnumValue; // eax
  int v24; // eax
  int Integer; // eax
  int v26; // edi
  int v27; // eax
  bool *p_stereo; // ebx
  int v29; // ebx
  bool v30; // cl
  bool v31; // zf
  bool v32; // al
  idAudioHardware *v33; // ecx
  int v34; // eax
  idSoundFade *soundClassFade; // edi
  int v36; // ebx
  idSoundEmitterLocal *v37; // eax
  idSoundEmitterLocal *v38; // eax
  int granularity; // eax
  bool v40; // cc
  int i; // eax
  int size; // ecx
  int num; // ebx
  int v44; // ecx
  idSoundEmitterLocal **list; // edi
  int j; // eax
  int v47; // [esp+1Ch] [ebp-100h]
  int v48; // [esp+28h] [ebp-F4h]
  idSoundEmitterLocal *v49; // [esp+28h] [ebp-F4h]
  unsigned int stereoSourceCount; // [esp+30h] [ebp-ECh] BYREF
  _EAXFXSLOTPROPERTIES EffectSlotAll; // [esp+38h] [ebp-E4h] BYREF
  int v52; // [esp+5Ch] [ebp-C0h] BYREF
  int v53; // [esp+60h] [ebp-BCh] BYREF
  unsigned __int128 v54; // [esp+64h] [ebp-B8h] BYREF
  int v55; // [esp+74h] [ebp-A8h] BYREF
  int v56; // [esp+78h] [ebp-A4h] BYREF
  int v57; // [esp+7Ch] [ebp-A0h] BYREF
  unsigned int Environment; // [esp+80h] [ebp-9Ch]
  int v59; // [esp+84h] [ebp-98h]
  _EAXSESSIONPROPERTIES ContextSession; // [esp+88h] [ebp-94h] BYREF
  _BYTE efxSlot[72]; // [esp+90h] [ebp-8Ch] OVERLAPPED BYREF
  _GUID v62[4]; // [esp+D8h] [ebp-44h] BYREF
  int v63; // [esp+118h] [ebp-4h]

  if ( s_noSound.internalVar->integerValue )
    return 0;
  snd_audio_hw = this->snd_audio_hw;
  if ( snd_audio_hw )
    ((void (__thiscall *)(idAudioHardware *, int))snd_audio_hw->~idAudioHardware)(snd_audio_hw, 1);
  v3 = idAudioHardware::Alloc();
  this->snd_audio_hw = v3;
  if ( !v3 )
    return 0;
  if ( !LoadOpenAL() || !this->IsEAXAvailable(this) )
  {
    idSoundSystemLocal::s_loadOpenALFailed.internalVar->InternalSetBool(
      idSoundSystemLocal::s_loadOpenALFailed.internalVar,
      1);
    idSoundSystemLocal::s_useOpenAL.internalVar->InternalSetBool(idSoundSystemLocal::s_useOpenAL.internalVar, 0);
    idSoundSystemLocal::s_useEAXReverb.internalVar->InternalSetBool(idSoundSystemLocal::s_useEAXReverb.internalVar, 0);
    idSoundSystemLocal::s_useEAXOcclusion.internalVar->InternalSetBool(
      idSoundSystemLocal::s_useEAXOcclusion.internalVar,
      0);
  }
  if ( idSoundSystemLocal::s_useOpenAL.internalVar->integerValue )
  {
    if ( !this->openalDevice )
    {
      value = idSoundSystemLocal::s_deviceName.internalVar->value;
      v6 = 0;
      if ( *value )
      {
        do
          ++v6;
        while ( value[v6] );
        if ( v6 )
          this->openalDevice = qalcOpenDevice((unsigned __int8 *)idSoundSystemLocal::s_deviceName.internalVar->value);
      }
    }
    (*(void (__stdcall **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "...creating AL device: ");
    if ( !this->openalDevice )
    {
      v7 = qalcOpenDevice(0);
      this->openalDevice = v7;
      if ( !v7 )
        goto LABEL_53;
    }
    if ( (((*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n"),
           (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
             common.type,
             "...creating AL context: "),
           this->openalContext)
       || (Context = qalcCreateContext(this->openalDevice, 0), (this->openalContext = Context) != 0))
      && ((*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n"),
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "...making context current: "),
          qalcMakeContextCurrent(this->openalContext) == 1) )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
      String = (const char *)qalcGetString(this->openalDevice, 4101);
      idStr::Copynz((char *)this->openalDeviceName, String, 128);
      if ( !idStr::Icmp((const char *)this->openalDeviceName, "SoundBlaster Audigy") && !qalIsExtensionPresent("EAX3.0") )
        idStr::Copynz((char *)this->openalDeviceName, "SB Live Audio", 128);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "OpenAL: found %s\n",
        this->openalDeviceName);
      idSoundSystemLocal::s_deviceName.internalVar->InternalSetString(
        idSoundSystemLocal::s_deviceName.internalVar,
        (const char *)this->openalDeviceName);
      if ( idSoundSystemLocal::s_useEAXReverb.internalVar->integerValue && qalIsExtensionPresent("EAX5.0") )
      {
        idSoundSystemLocal::s_useEAXOcclusion.internalVar->InternalSetBool(
          idSoundSystemLocal::s_useEAXOcclusion.internalVar,
          1);
        this->alEAXSet = (int (__cdecl *)(const _GUID *, unsigned int, unsigned int, void *, unsigned int))qalGetProcAddress("EAXSet");
        this->alEAXGet = (int (__cdecl *)(const _GUID *, unsigned int, unsigned int, void *, unsigned int))qalGetProcAddress("EAXGet");
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "OpenAL: found EAX 5.0 extension\n");
        *(_DWORD *)efxSlot = 6;
        *(_DWORD *)&efxSlot[4] = 2;
        this->alEAXSet(&EAXPROPERTYID_EAX50_Context, 8u, 0, efxSlot, 8u);
        this->eaxVersion = 6;
        *(_DWORD *)&EffectSlotAll.guidLoadEffect.Data2 = 0;
        v10 = (const _GUID *)&efxSlot[8];
        EffectSlotAll.guidLoadEffect.Data1 = (unsigned int)this->efxSlotToArea;
        stereoSourceCount = (unsigned int)this->efxSlotId;
        do
        {
          *(_GUID *)&efxSlot[8] = EAXPROPERTYID_EAX50_FXSlot0;
          *(_GUID *)&efxSlot[24] = EAXPROPERTYID_EAX50_FXSlot1;
          *(_GUID *)&efxSlot[40] = EAXPROPERTYID_EAX50_FXSlot2;
          *(_GUID *)&efxSlot[56] = EAXPROPERTYID_EAX50_FXSlot3;
          *(_GUID *)EffectSlotAll.guidLoadEffect.Data4 = EAX_REVERB_EFFECT;
          EffectSlotAll.ulFlags = 0;
          EffectSlotAll.lOcclusion = 1;
          LODWORD(EffectSlotAll.flOcclusionLFRatio) = 1;
          v52 = 0;
          v53 = 1048576000;
          ContextSession.ulEAXVersion = 0;
          this->alEAXSet(v10, 65538u, 0, EffectSlotAll.guidLoadEffect.Data4, 16u);
          this->alEAXSet(v10, 65539u, 0, &EffectSlotAll.ulFlags, 4u);
          this->alEAXSet(v10, 65540u, 0, &EffectSlotAll.lOcclusion, 4u);
          this->alEAXSet(v10, 65541u, 0, &EffectSlotAll.flOcclusionLFRatio, 4u);
          this->alEAXSet(v10, 65542u, 0, &v52, 4u);
          this->alEAXSet(v10, 65543u, 0, &v53, 4u);
          this->alEAXSet(v10, 2u, 0, &ContextSession, 4u);
          memset(EffectSlotAll.guidLoadEffect.Data4, 0, 28);
          v52 = 0;
          v53 = 0;
          this->alEAXGet(v10, 65537u, 0, EffectSlotAll.guidLoadEffect.Data4, 36u);
          if ( memcmp(EffectSlotAll.guidLoadEffect.Data4, &EAX_REVERB_EFFECT, 0x10u)
            || (v11 = 1, EffectSlotAll.lOcclusion != 1) )
          {
            v11 = 0;
          }
          v12 = *(_DWORD *)&EffectSlotAll.guidLoadEffect.Data2;
          v13 = (_DWORD *)stereoSourceCount;
          this->efxSlotAvailable[*(_DWORD *)&EffectSlotAll.guidLoadEffect.Data2] = v11;
          *v13 = v10->Data1;
          v13[1] = *(_DWORD *)&v10->Data2;
          v14 = *(_DWORD *)&v10->Data4[4];
          v13[2] = *(_DWORD *)v10->Data4;
          v13[3] = v14;
          Data1 = EffectSlotAll.guidLoadEffect.Data1;
          *(_DWORD *)EffectSlotAll.guidLoadEffect.Data1 = -1;
          ++v10;
          *(_DWORD *)&EffectSlotAll.guidLoadEffect.Data2 = v12 + 1;
          EffectSlotAll.guidLoadEffect.Data1 = Data1 + 4;
          stereoSourceCount = (unsigned int)(v13 + 4);
        }
        while ( v12 + 1 < 4 );
      }
      else if ( idSoundSystemLocal::s_useEAXReverb.internalVar->integerValue && qalIsExtensionPresent("EAX4.0") )
      {
        idSoundSystemLocal::s_useEAXOcclusion.internalVar->InternalSetBool(
          idSoundSystemLocal::s_useEAXOcclusion.internalVar,
          1);
        this->alEAXSet = (int (__cdecl *)(const _GUID *, unsigned int, unsigned int, void *, unsigned int))qalGetProcAddress("EAXSet");
        this->alEAXGet = (int (__cdecl *)(const _GUID *, unsigned int, unsigned int, void *, unsigned int))qalGetProcAddress("EAXGet");
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "OpenAL: found EAX 4.0 extension\n");
        this->eaxVersion = 5;
        stereoSourceCount = 0;
        v16 = v62;
        EffectSlotAll.guidLoadEffect.Data1 = (unsigned int)this->efxSlotToArea;
        *(_DWORD *)&EffectSlotAll.guidLoadEffect.Data2 = this->efxSlotId;
        do
        {
          v62[0] = EAXPROPERTYID_EAX40_FXSlot0;
          v62[1] = EAXPROPERTYID_EAX40_FXSlot1;
          v62[2] = EAXPROPERTYID_EAX40_FXSlot2;
          v62[3] = EAXPROPERTYID_EAX40_FXSlot3;
          v54 = (unsigned __int128)EAX_REVERB_EFFECT;
          Environment = 0;
          v59 = 0;
          v55 = 0;
          v56 = 1;
          v57 = 1;
          ContextSession.ulMaxActiveSends = 0;
          this->alEAXSet(v16, 65538u, 0, &v54, 16u);
          this->alEAXSet(v16, 65539u, 0, &v55, 4u);
          this->alEAXSet(v16, 65540u, 0, &v56, 4u);
          this->alEAXSet(v16, 65541u, 0, &v57, 4u);
          this->alEAXSet(v16, 2u, 0, &ContextSession.ulMaxActiveSends, 4u);
          v54 = 0ui64;
          v55 = 0;
          v56 = 0;
          v57 = 0;
          Environment = 0;
          v59 = 0;
          this->alEAXGet(v16, 65537u, 0, &v54, 36u);
          if ( memcmp(&v54, &EAX_REVERB_EFFECT, 0x10u) || (v17 = 1, v56 != 1) )
            v17 = 0;
          v18 = stereoSourceCount;
          v19 = *(unsigned int **)&EffectSlotAll.guidLoadEffect.Data2;
          this->efxSlotAvailable[stereoSourceCount] = v17;
          *v19 = v16->Data1;
          v19[1] = *(_DWORD *)&v16->Data2;
          v20 = *(_DWORD *)&v16->Data4[4];
          v19[2] = *(_DWORD *)v16->Data4;
          v19[3] = v20;
          v21 = EffectSlotAll.guidLoadEffect.Data1;
          *(_DWORD *)EffectSlotAll.guidLoadEffect.Data1 = -1;
          ++v16;
          stereoSourceCount = v18 + 1;
          EffectSlotAll.guidLoadEffect.Data1 = v21 + 4;
          *(_DWORD *)&EffectSlotAll.guidLoadEffect.Data2 = v19 + 4;
        }
        while ( (int)(v18 + 1) < 4 );
      }
      else if ( idSoundSystemLocal::s_useEAXReverb.internalVar->integerValue )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "OpenAL: EAX 4.0 or 5.0 extension not found\n");
        idSoundSystemLocal::s_useEAXReverb.internalVar->InternalSetBool(
          idSoundSystemLocal::s_useEAXReverb.internalVar,
          0);
        idSoundSystemLocal::s_useEAXOcclusion.internalVar->InternalSetBool(
          idSoundSystemLocal::s_useEAXOcclusion.internalVar,
          0);
        this->alEAXSet = 0;
        this->alEAXGet = 0;
      }
      if ( qalIsExtensionPresent("EAX-RAM") == 1 )
      {
        this->alEAXSetBufferMode = (char (__cdecl *)(unsigned int, unsigned int *, int))qalGetProcAddress("EAXSetBufferMode");
        this->alEAXGetBufferMode = (int (__cdecl *)(unsigned int, int *))qalGetProcAddress("EAXGetBufferMode");
        v22 = *(_DWORD *)common.type;
        EnumValue = qalGetEnumValue("AL_EAX_RAM_SIZE");
        v47 = qalGetInteger(EnumValue) / 1024;
        v24 = qalGetEnumValue("AL_EAX_RAM_FREE");
        Integer = qalGetInteger(v24);
        (*(void (**)(netadrtype_t, const char *, ...))(v22 + 124))(
          common.type,
          "OpenAL: found EAX-RAM extension, %dkB\\%dkB\n",
          Integer / 1024,
          v47);
        s_decompressionLimit.internalVar->InternalSetInteger(s_decompressionLimit.internalVar, 4);
      }
      else
      {
        this->alEAXSetBufferMode = 0;
        this->alEAXGetBufferMode = 0;
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "OpenAL: EAX-RAM extension not found\n");
        s_decompressionLimit.internalVar->InternalSetInteger(s_decompressionLimit.internalVar, 2);
      }
      this->openalSourceCount = 0;
      v26 = 0;
      do
      {
        qalGetError();
        qalGenSources(1u, &stereoSourceCount);
        if ( qalGetError() )
          break;
        this->openalSources[this->openalSourceCount].handle = stereoSourceCount;
        this->openalSources[this->openalSourceCount].startTime = 0;
        this->openalSources[this->openalSourceCount].chan = 0;
        this->openalSources[this->openalSourceCount].inUse = 0;
        this->openalSources[this->openalSourceCount].looping = 0;
        this->openalSources[this->openalSourceCount].stereo = 0;
        qalSourcef(stereoSourceCount, 4129, 0.0);
        qalSourcef(stereoSourceCount, 4099, 1.0);
        qalSourcef(stereoSourceCount, 4106, 1.0);
        qalSourcef(stereoSourceCount, 4109, 0.0);
        qalSourcef(stereoSourceCount, 4110, 1.0);
        qalSourcei(stereoSourceCount, 4103, 0);
        qalSource3f(stereoSourceCount, 4102, 0.0, 0.0, 0.0);
        qalSource3f(stereoSourceCount, 4100, 0.0, 0.0, 0.0);
        qalSource3f(stereoSourceCount, 4101, 0.0, 0.0, 0.0);
        ++this->openalSourceCount;
        ++v26;
      }
      while ( this->openalSourceCount < 0x100 );
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "OpenAL: found %d hardware voices\n",
        this->openalSourceCount);
      s_maxChannelsMixed.internalVar->InternalSetInteger(s_maxChannelsMixed.internalVar, this->openalSourceCount);
      v27 = (signed int)(idSoundSystemLocal::s_minStereo.internalVar->integerValue * this->openalSourceCount) / 60;
      stereoSourceCount = v27;
      if ( v27 > 0 )
      {
        p_stereo = &this->openalSources[0].stereo;
        v48 = v27;
        do
        {
          qalDeleteSources(1u, (unsigned int *)&this->openalDeviceName[16 * this->openalSourceCount + 124]);
          *(_DWORD *)&this->openalDeviceName[16 * this->openalSourceCount + 124] = 0;
          *(_DWORD *)&this->openalDeviceName[16 * this->openalSourceCount + 128] = 0;
          *((_DWORD *)&this->openalContext + 4 * this->openalSourceCount) = 0;
          *((_BYTE *)&this->openalSourceCount + 16 * this->openalSourceCount) = 0;
          *((_BYTE *)&this->openalSourceCount + 16 * this->openalSourceCount + 1) = 0;
          *((_BYTE *)&this->openalSourceCount + 16 * this->openalSourceCount + 2) = 0;
          *p_stereo = 1;
          --this->openalSourceCount;
          v26 -= 2;
          p_stereo += 16;
          --v48;
        }
        while ( v48 );
      }
      v29 = 3;
      do
      {
        qalDeleteSources(1u, (unsigned int *)&this->openalDeviceName[16 * this->openalSourceCount + 124]);
        *(_DWORD *)&this->openalDeviceName[16 * this->openalSourceCount + 124] = 0;
        *(_DWORD *)&this->openalDeviceName[16 * this->openalSourceCount + 128] = 0;
        *((_DWORD *)&this->openalContext + 4 * this->openalSourceCount) = 0;
        *((_BYTE *)&this->openalSourceCount + 16 * this->openalSourceCount) = 0;
        *((_BYTE *)&this->openalSourceCount + 16 * this->openalSourceCount + 1) = 0;
        *((_BYTE *)&this->openalSourceCount + 16 * this->openalSourceCount-- + 2) = 0;
        --v26;
        --v29;
      }
      while ( v29 );
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "OpenAL: found %d mono voices\n",
        v26);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "OpenAL: found %d stereo voices\n",
        stereoSourceCount);
    }
    else
    {
LABEL_53:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "failed\n");
      idSoundSystemLocal::s_useOpenAL.internalVar->InternalSetBool(idSoundSystemLocal::s_useOpenAL.internalVar, 0);
      idSoundSystemLocal::s_useEAXReverb.internalVar->InternalSetBool(idSoundSystemLocal::s_useEAXReverb.internalVar, 0);
      idSoundSystemLocal::s_useEAXOcclusion.internalVar->InternalSetBool(
        idSoundSystemLocal::s_useEAXOcclusion.internalVar,
        0);
    }
  }
  v30 = idSoundSystemLocal::s_useOpenAL.internalVar->integerValue != 0;
  idSoundSystemLocal::useOpenAL = v30;
  v31 = idSoundSystemLocal::s_useEAXReverb.internalVar->integerValue == 0;
  idSoundSystemLocal::useEAXReverb = idSoundSystemLocal::s_useEAXReverb.internalVar->integerValue != 0;
  if ( v31
    || (v31 = idSoundSystemLocal::s_useEAXOcclusion.internalVar->integerValue == 0,
        idSoundSystemLocal::useEAXOcclusion = 1,
        v31) )
  {
    idSoundSystemLocal::useEAXOcclusion = 0;
  }
  if ( !v30 )
  {
    v32 = this->snd_audio_hw->Initialize(this->snd_audio_hw);
    v33 = this->snd_audio_hw;
    if ( !v32 )
    {
      if ( v33 )
        ((void (__thiscall *)(idAudioHardware *, int))v33->~idAudioHardware)(v33, 1);
      this->snd_audio_hw = 0;
      return 0;
    }
    if ( !v33->GetNumberOfSpeakers(v33) )
      return 0;
    v34 = this->snd_audio_hw->GetNumberOfSpeakers(this->snd_audio_hw);
    idSoundSystemLocal::s_numberOfSpeakers.internalVar->InternalSetInteger(
      idSoundSystemLocal::s_numberOfSpeakers.internalVar,
      v34);
  }
  if ( !idAsyncNetwork::serverDedicated.internalVar->integerValue )
    this->InitVoiceComms(this);
  this->writeDemo = 0;
  this->listenerAxis = mat3_identity;
  this->listenerPos.z = 0.0;
  this->listenerPos.y = 0.0;
  this->listenerPos.x = 0.0;
  this->listenerPrivateId = 0;
  this->lastListenerArea = -1;
  this->listenerArea = 0;
  this->gameMsec = 0;
  this->game44kHz = 0;
  this->pause44kHz = -1;
  this->lastAVI44kHz = 0;
  soundClassFade = this->soundClassFade;
  v36 = 4;
  do
  {
    idSoundFade::Clear(soundClassFade++);
    --v36;
  }
  while ( v36 );
  v37 = (idSoundEmitterLocal *)Memory::Allocate(0x5A0u);
  Environment = (unsigned int)v37;
  v63 = 0;
  if ( v37 )
  {
    idSoundEmitterLocal::idSoundEmitterLocal(v37);
    v49 = v38;
  }
  else
  {
    v49 = 0;
  }
  v31 = this->emitters.list == 0;
  v63 = -1;
  if ( v31 )
  {
    granularity = this->emitters.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->emitters.size )
      {
        v40 = granularity < this->emitters.num;
        this->emitters.size = granularity;
        if ( v40 )
          this->emitters.num = granularity;
        this->emitters.list = (idSoundEmitterLocal **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->emitters.num; ++i )
          this->emitters.list[i] = *(idSoundEmitterLocal **)(4 * i);
      }
    }
    else
    {
      this->emitters.list = 0;
      this->emitters.num = 0;
      this->emitters.size = 0;
    }
  }
  size = this->emitters.size;
  num = this->emitters.num;
  if ( num == size )
  {
    if ( !this->emitters.granularity )
      this->emitters.granularity = 16;
    v44 = this->emitters.granularity + size - (this->emitters.granularity + size) % this->emitters.granularity;
    if ( v44 > 0 )
    {
      if ( v44 != this->emitters.size )
      {
        list = this->emitters.list;
        this->emitters.size = v44;
        if ( v44 < num )
          this->emitters.num = v44;
        this->emitters.list = (idSoundEmitterLocal **)Memory::Allocate(4 * v44);
        for ( j = 0; j < this->emitters.num; ++j )
          this->emitters.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->emitters.list )
        Memory::Free(this->emitters.list);
      this->emitters.list = 0;
      this->emitters.num = 0;
      this->emitters.size = 0;
    }
  }
  this->emitters.list[this->emitters.num++] = v49;
  this->fpa[5] = 0;
  this->fpa[4] = 0;
  this->fpa[3] = 0;
  this->fpa[2] = 0;
  this->fpa[1] = 0;
  this->fpa[0] = 0;
  idStr::operator=(&this->aviDemoPath, (char *)&entityFilter);
  idStr::operator=(&this->aviDemoName, (char *)&entityFilter);
  this->isInitialized = 1;
  this->shutdown = 0;
  return 1;
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::GetSoundDecoderInfo(int,struct soundDecoderInfo_t &)
int __thiscall idSoundSystemLocal::GetSoundDecoderInfo(
        idSoundSystemLocal *this,
        int index,
        soundDecoderInfo_t *decoderInfo)
{
  idSoundSystemLocal *v3; // ebp
  int v5; // edi
  int v6; // esi
  int v7; // ebx
  idSoundEmitterLocal *v8; // eax
  int v9; // edi
  idSampleDecoder **p_decoder; // esi
  int v11; // eax
  idSoundSample *v12; // ebp
  unsigned int v13; // esi
  char *v14; // eax
  int j; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]
  int indexa; // [esp+14h] [ebp+4h]
  float indexb; // [esp+14h] [ebp+4h]

  v3 = this;
  if ( !this->activeSoundWorld )
    return -1;
  if ( index >= 0 )
  {
    v5 = index / 8;
    v6 = index % 8 + 1;
  }
  else
  {
    v5 = 0;
    v6 = 0;
  }
  v7 = v5;
  i = v5;
  if ( v5 >= this->GetNumEmitters(this) )
    return -1;
  while ( 1 )
  {
    v8 = v3->emitters.list[v7];
    if ( v8 )
      break;
LABEL_15:
    i = ++v7;
    if ( v7 >= v3->GetNumEmitters(v3) )
      return -1;
  }
  v9 = v6;
  j = v6;
  if ( v6 >= 8 )
  {
LABEL_14:
    v6 = 0;
    goto LABEL_15;
  }
  p_decoder = &v8->channels[v6].decoder;
  indexa = (int)p_decoder;
  while ( !*p_decoder )
  {
LABEL_13:
    ++v9;
    p_decoder += 41;
    j = v9;
    indexa = (int)p_decoder;
    if ( v9 >= 8 )
      goto LABEL_14;
  }
  v11 = (int)(*p_decoder)->GetSample(*p_decoder);
  v12 = (idSoundSample *)v11;
  if ( !v11 )
  {
    v3 = this;
    goto LABEL_13;
  }
  v13 = *(_DWORD *)(v11 + 4);
  if ( (signed int)(v13 + 1) > decoderInfo->name.alloced )
    idStr::ReAllocate(&decoderInfo->name, v13 + 1, 0);
  qmemcpy(decoderInfo->name.data, v12->name.data, v13);
  decoderInfo->name.data[v13] = 0;
  decoderInfo->name.len = v13;
  v14 = "OGG";
  if ( v12->wFormatTag != 2 )
    v14 = "WAV";
  idStr::operator=(&decoderInfo->format, v14);
  decoderInfo->numChannels = v12->nChannels;
  decoderInfo->numSamplesPerSecond = v12->nSamplesPerSec;
  decoderInfo->num44kHzSamples = idSoundSample::LengthIn44kHzSamples(v12);
  decoderInfo->numBytes = v12->objectMemSize;
  decoderInfo->looping = (*(_DWORD *)(indexa - 36) & 0x20) != 0;
  decoderInfo->lastVolume = *(float *)(indexa + 8);
  decoderInfo->start44kHzTime = *(_DWORD *)(indexa - 60);
  if ( soundSystemLocal.snd_audio_hw )
  {
    decoderInfo->current44kHzTime = soundSystemLocal.CurrentSoundTime;
  }
  else
  {
    indexb = (double)Sys_Milliseconds() * 176.39999;
    decoderInfo->current44kHzTime = (int)indexb;
  }
  return j + 8 * i;
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::EndLevelLoad(char const *)
void __thiscall idSoundSystemLocal::EndLevelLoad(idSoundSystemLocal *this, const char *mapName)
{
  const char *v3; // ebp
  int v4; // eax
  char v5; // cl
  const char *v6; // eax
  int v7; // esi
  int v8; // eax
  char *data; // edx
  const char *v10; // ecx
  char v11; // al
  int v12; // esi
  int v13; // eax
  char v14; // cl
  char *v15; // edx
  bool File; // al
  int v17; // eax
  char v18; // cl
  bool v19; // al
  char *v20; // edx
  int v21; // ecx
  idStr efxname; // [esp+8h] [ebp-6Ch] BYREF
  idStr mapname; // [esp+28h] [ebp-4Ch] BYREF
  idStr defaultefxname; // [esp+48h] [ebp-2Ch] BYREF
  int v25; // [esp+70h] [ebp-4h]

  if ( this->isInitialized )
  {
    v3 = mapName;
    idSoundCache::EndLevelLoad(this->soundCache, mapName);
    efxname.data = efxname.baseBuffer;
    efxname.alloced = 20;
    efxname.baseBuffer[0] = 0;
    v4 = 0;
    do
    {
      v5 = aEfxs[v4];
      efxname.baseBuffer[v4++] = v5;
    }
    while ( v5 );
    efxname.len = 5;
    v25 = 0;
    mapname.len = 0;
    mapname.alloced = 20;
    mapname.data = mapname.baseBuffer;
    mapname.baseBuffer[0] = 0;
    if ( mapName )
    {
      v6 = &mapName[strlen(mapName) + 1];
      v7 = v6 - (mapName + 1);
      v8 = v6 - mapName;
      if ( v8 > 20 )
        idStr::ReAllocate(&mapname, v8, 1);
      data = mapname.data;
      v10 = mapName;
      do
      {
        v11 = *v10;
        *data++ = *v10++;
      }
      while ( v11 );
      mapname.len = v7;
    }
    LOBYTE(v25) = 1;
    idStr::SetFileExtension(&mapname, ".efx");
    idStr::StripPath(&mapname);
    v12 = mapname.len + efxname.len;
    if ( mapname.len + efxname.len + 1 > efxname.alloced )
      idStr::ReAllocate(&efxname, mapname.len + efxname.len + 1, 1);
    v13 = 0;
    if ( mapname.len > 0 )
    {
      do
      {
        v14 = mapname.data[v13];
        v15 = &efxname.data[v13++];
        v15[efxname.len] = v14;
      }
      while ( v13 < mapname.len );
      v3 = mapName;
    }
    efxname.len = v12;
    efxname.data[v12] = 0;
    File = idEFXFile::LoadFile(&this->EFXDatabase, efxname.data, 0);
    this->efxloaded = File;
    if ( File )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "sound: found %s\n",
        efxname.data);
    }
    else
    {
      defaultefxname.alloced = 20;
      defaultefxname.data = defaultefxname.baseBuffer;
      defaultefxname.baseBuffer[0] = 0;
      v17 = 0;
      do
      {
        v18 = aEfxsDefaultEfx[v17];
        defaultefxname.baseBuffer[v17++] = v18;
      }
      while ( v18 );
      defaultefxname.len = 16;
      LOBYTE(v25) = 2;
      v19 = idEFXFile::LoadFile(&this->EFXDatabase, defaultefxname.data, 0);
      v20 = defaultefxname.data;
      this->efxloaded = v19;
      v21 = *(_DWORD *)common.type;
      if ( v19 )
        (*(void (**)(netadrtype_t, const char *, ...))(v21 + 124))(common.type, "sound: found %s\n", v20);
      else
        (*(void (**)(netadrtype_t, const char *, ...))(v21 + 124))(
          common.type,
          "sound: missing %s and %s\n",
          efxname.data,
          v20);
      LOBYTE(v25) = 1;
      idStr::FreeData(&defaultefxname);
    }
    idSoundSystemLocal::LoadReverbData(this, v3);
    LOBYTE(v25) = 0;
    idStr::FreeData(&mapname);
    v25 = -1;
    idStr::FreeData(&efxname);
  }
}

// FUNC: void __cdecl SoundSystemRestart_f(class idCmdArgs const &)
void __cdecl SoundSystemRestart_f()
{
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Sound System Restart...\n");
  soundSystem->SetMute(soundSystem, 1);
  idSoundSystemLocal::ShutdownHW(&soundSystemLocal);
  idSoundSystemLocal::InitHW(&soundSystemLocal);
  idSoundCache::ReloadSounds(soundSystemLocal.soundCache, 1);
  soundSystem->SetMute(soundSystem, 0);
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::Init(void)
void __thiscall idSoundSystemLocal::Init(idSoundSystemLocal *this)
{
  idSoundCache *v2; // eax
  idSoundCache *v3; // eax

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "-------- Initializing Sound System ----------\n");
  this->isInitialized = 0;
  this->muted = 0;
  this->shutdown = 0;
  this->voiceCommInit = 0;
  this->soundCache = 0;
  this->olddwCurrentWritePos = 0;
  this->buffers = 0;
  this->CurrentSoundTime = 0;
  this->nextWriteBlock = -1;
  memset(this->meterTops, 0, sizeof(this->meterTops));
  memset(this->meterTopsTime, 0, sizeof(this->meterTopsTime));
  this->finalMixBuffer = (float *)(((unsigned int)&this->realAccum[3] + 3) & 0xFFFFFFF0);
  this->graph = 0;
  if ( !s_noSound.internalVar->integerValue )
  {
    idSampleDecoder::Init();
    v2 = (idSoundCache *)Memory::Allocate(0x14u);
    if ( v2 )
      idSoundCache::idSoundCache(v2);
    else
      v3 = 0;
    this->soundCache = v3;
  }
  cmdSystem->AddCommand(cmdSystem, "listSounds", ListSounds_f, 8, "lists all sounds", 0);
  cmdSystem->AddCommand(cmdSystem, "listSoundDecoders", ListSoundDecoders_f, 8, "list active sound decoders", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "reloadSounds",
    (void (__cdecl *)(const idCmdArgs *))SoundReloadSounds_f,
    9,
    "reloads all sounds",
    0);
  cmdSystem->AddCommand(cmdSystem, "s_restart", SoundSystemRestart_f, 8, "restarts the sound system", 0);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "sound system initialized.\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
}
