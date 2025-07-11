
// FUNC: public: __thiscall idWaveFile::idWaveFile(void)
void __thiscall idWaveFile::idWaveFile(idWaveFile *this)
{
  *(_DWORD *)&this->mpwfx.Format.wFormatTag = 0;
  this->mpwfx.Format.nSamplesPerSec = 0;
  this->mpwfx.Format.nAvgBytesPerSec = 0;
  *(_DWORD *)&this->mpwfx.Format.nBlockAlign = 0;
  *(_DWORD *)&this->mpwfx.Format.cbSize = 0;
  this->mpwfx.dwChannelMask = 0;
  this->mpwfx.SubFormat = 0;
  this->mhmmio = 0;
  this->mdwSize = 0;
  this->mseekBase = 0;
  this->mbIsReadingFromMemory = 0;
  this->mpbData = 0;
  this->ogg = 0;
  this->isOgg = 0;
}

// FUNC: public: int __thiscall idWaveFile::OpenFromMemory(short *,int,struct waveformatextensible_s *)
int __thiscall idWaveFile::OpenFromMemory(
        idWaveFile *this,
        __int16 *pbData,
        unsigned int ulDataSize,
        waveformatextensible_s *pwfx)
{
  qmemcpy(this, pwfx, 0x1Cu);
  this->mpbData = pbData;
  this->mpbDataCur = pbData;
  this->mulDataSize = ulDataSize;
  this->mdwSize = ulDataSize >> 1;
  this->mMemSize = ulDataSize;
  this->mbIsReadingFromMemory = 1;
  return 0;
}

// FUNC: private: int __thiscall idWaveFile::ReadMMIO(void)
int __thiscall idWaveFile::ReadMMIO(idWaveFile *this)
{
  mminfo_s *p_mckRiff; // edi
  int v3; // eax
  unsigned int v4; // eax
  unsigned int v5; // eax
  bool v6; // zf
  unsigned int v7; // eax
  unsigned int nSamplesPerSec; // eax
  unsigned int nAvgBytesPerSec; // edx
  int v10; // eax
  int fccType; // [esp-4h] [ebp-38h]
  int cksize; // [esp+0h] [ebp-34h]
  mminfo_s ckIn; // [esp+10h] [ebp-24h] BYREF
  pcmwaveformat_s pcmWaveFormat; // [esp+20h] [ebp-14h] BYREF

  *(_DWORD *)&this->mpwfx.Format.wFormatTag = 0;
  this->mpwfx.Format.nSamplesPerSec = 0;
  this->mpwfx.Format.nAvgBytesPerSec = 0;
  *(_DWORD *)&this->mpwfx.Format.nBlockAlign = 0;
  *(_DWORD *)&this->mpwfx.Format.cbSize = 0;
  this->mpwfx.dwChannelMask = 0;
  this->mpwfx.SubFormat = 0;
  p_mckRiff = &this->mckRiff;
  this->mhmmio->Read(this->mhmmio, &this->mckRiff, 12);
  v3 = LittleLong(p_mckRiff->ckid);
  cksize = this->mckRiff.cksize;
  p_mckRiff->ckid = v3;
  v4 = LittleLong(cksize);
  fccType = this->mckRiff.fccType;
  this->mckRiff.cksize = v4;
  v5 = LittleLong(fccType);
  v6 = p_mckRiff->ckid == 1179011410;
  this->mckRiff.fccType = v5;
  this->mckRiff.dwDataOffset = 12;
  if ( v6 && v5 == 1163280727 )
  {
    ckIn.dwDataOffset = 12;
    while ( this->mhmmio->Read(this->mhmmio, &ckIn, 8) == 8 )
    {
      ckIn.ckid = LittleLong(ckIn.ckid);
      v7 = LittleLong(ckIn.cksize);
      ckIn.cksize = v7;
      ckIn.dwDataOffset = ckIn.dwDataOffset + v7 - 8;
      if ( ckIn.ckid == 544501094 )
      {
        if ( v7 >= 0x10 && this->mhmmio->Read(this->mhmmio, &pcmWaveFormat, 16) == 16 )
        {
          pcmWaveFormat.wf.wFormatTag = LittleShort(pcmWaveFormat.wf.wFormatTag);
          pcmWaveFormat.wf.nChannels = LittleShort(pcmWaveFormat.wf.nChannels);
          pcmWaveFormat.wf.nSamplesPerSec = LittleLong(pcmWaveFormat.wf.nSamplesPerSec);
          pcmWaveFormat.wf.nAvgBytesPerSec = LittleLong(pcmWaveFormat.wf.nAvgBytesPerSec);
          pcmWaveFormat.wf.nBlockAlign = LittleShort(pcmWaveFormat.wf.nBlockAlign);
          pcmWaveFormat.wBitsPerSample = LittleShort(pcmWaveFormat.wBitsPerSample);
          nSamplesPerSec = pcmWaveFormat.wf.nSamplesPerSec;
          *(_DWORD *)&this->mpwfx.Format.wFormatTag = *(_DWORD *)&pcmWaveFormat.wf.wFormatTag;
          nAvgBytesPerSec = pcmWaveFormat.wf.nAvgBytesPerSec;
          this->mpwfx.Format.nSamplesPerSec = nSamplesPerSec;
          v10 = *(_DWORD *)&pcmWaveFormat.wf.nBlockAlign;
          v6 = pcmWaveFormat.wf.wFormatTag == 1;
          this->mpwfx.Format.nAvgBytesPerSec = nAvgBytesPerSec;
          *(_DWORD *)&this->mpwfx.Format.nBlockAlign = v10;
          if ( v6 )
          {
            this->mpwfx.Format.cbSize = 0;
            return 0;
          }
        }
        return -1;
      }
    }
  }
  return -1;
}

// FUNC: public: int __thiscall idWaveFile::ResetFile(void)
int __thiscall idWaveFile::ResetFile(idWaveFile *this)
{
  idFile *mhmmio; // ecx
  unsigned int v4; // eax
  unsigned int v5; // eax
  idFile *v6; // ecx
  unsigned __int8 ioin; // [esp+11h] [ebp-1h] BYREF

  if ( this->mbIsReadingFromMemory )
  {
    this->mpbDataCur = this->mpbData;
    return 0;
  }
  else
  {
    mhmmio = this->mhmmio;
    if ( mhmmio && mhmmio->Seek(mhmmio, this->mckRiff.dwDataOffset + 4, FS_SEEK_SET) != -1 )
    {
      this->mck.ckid = 0;
      while ( this->mhmmio->Read(this->mhmmio, &ioin, 1) )
      {
        v4 = (this->mck.ckid >> 8) | (ioin << 24);
        this->mck.ckid = v4;
        if ( v4 == 1635017060 )
        {
          this->mhmmio->Read(this->mhmmio, &this->mck.cksize, 4);
          v5 = LittleLong(this->mck.cksize);
          v6 = this->mhmmio;
          this->mck.cksize = v5;
          this->mseekBase = v6->Tell(v6);
          return 0;
        }
      }
    }
    return -1;
  }
}

// FUNC: public: int __thiscall idWaveFile::Read(unsigned char *,int,int *)
int __thiscall idWaveFile::Read(idWaveFile *this, unsigned __int8 *pBuffer, int dwSizeToRead, int *pdwSizeRead)
{
  __int16 *mpbDataCur; // edx
  unsigned int mulDataSize; // eax
  __int16 *mpbData; // ecx
  int v9; // edi
  idFile *mhmmio; // ecx
  int v11; // eax

  if ( this->ogg )
    return idWaveFile::ReadOGG(this, pBuffer, dwSizeToRead, pdwSizeRead);
  if ( !this->mbIsReadingFromMemory )
  {
    mhmmio = this->mhmmio;
    if ( mhmmio && pBuffer )
    {
      v11 = mhmmio->Read(mhmmio, pBuffer, dwSizeToRead);
      v9 = v11;
      if ( !this->isOgg )
        LittleRevBytes(pBuffer, 2, v11 / 2);
      goto LABEL_13;
    }
    return -1;
  }
  mpbDataCur = this->mpbDataCur;
  if ( !mpbDataCur )
    return -1;
  mulDataSize = this->mulDataSize;
  mpbData = this->mpbData;
  v9 = dwSizeToRead;
  if ( &mpbDataCur[dwSizeToRead] > &mpbData[mulDataSize] )
    v9 = mulDataSize - (mpbDataCur - mpbData);
  SIMDProcessor->Memcpy(SIMDProcessor, pBuffer, mpbDataCur, v9);
  this->mpbDataCur += v9;
LABEL_13:
  if ( pdwSizeRead )
    *pdwSizeRead = v9;
  return v9;
}

// FUNC: public: int __thiscall idWaveFile::Close(void)
int __thiscall idWaveFile::Close(idWaveFile *this)
{
  if ( this->ogg )
    return idWaveFile::CloseOGG(this);
  if ( this->mhmmio )
  {
    fileSystem->CloseFile(fileSystem, this->mhmmio);
    this->mhmmio = 0;
  }
  return 0;
}

// FUNC: public: __thiscall idWaveFile::~idWaveFile(void)
void __thiscall idWaveFile::~idWaveFile(idWaveFile *this)
{
  if ( this->ogg )
  {
    idWaveFile::CloseOGG(this);
  }
  else if ( this->mhmmio )
  {
    fileSystem->CloseFile(fileSystem, this->mhmmio);
    this->mhmmio = 0;
  }
  if ( this->mbIsReadingFromMemory && this->mpbData )
    Mem_Free(this->mpbData);
  *(_DWORD *)&this->mpwfx.Format.wFormatTag = 0;
  this->mpwfx.Format.nSamplesPerSec = 0;
  this->mpwfx.Format.nAvgBytesPerSec = 0;
  *(_DWORD *)&this->mpwfx.Format.nBlockAlign = 0;
  *(_DWORD *)&this->mpwfx.Format.cbSize = 0;
  this->mpwfx.dwChannelMask = 0;
  this->mpwfx.SubFormat = 0;
}

// FUNC: public: int __thiscall idWaveFile::Open(char const *,struct waveformatex_s *,bool)
int __thiscall idWaveFile::Open(idWaveFile *this, const char *strFileName, waveformatex_s *pwfx, bool allowOgg)
{
  const char *v6; // eax
  int v7; // edi
  int v8; // eax
  char *data; // edx
  const char *v10; // ecx
  char v11; // al
  int v12; // esi
  idFile *v13; // eax
  unsigned int cksize; // eax
  idStr name; // [esp+Ch] [ebp-4Ch] BYREF
  idStr ext; // [esp+2Ch] [ebp-2Ch] BYREF
  int v17; // [esp+54h] [ebp-4h]

  this->mbIsReadingFromMemory = 0;
  this->mpbData = 0;
  this->mpbDataCur = 0;
  if ( !strFileName )
    return -1;
  name.data = name.baseBuffer;
  name.len = 0;
  name.alloced = 20;
  name.baseBuffer[0] = 0;
  v6 = &strFileName[strlen(strFileName) + 1];
  v7 = v6 - (strFileName + 1);
  v8 = v6 - strFileName;
  if ( v8 > 20 )
    idStr::ReAllocate(&name, v8, 1);
  data = name.data;
  v10 = strFileName;
  do
  {
    v11 = *v10;
    *data++ = *v10++;
  }
  while ( v11 );
  name.len = v7;
  v17 = 1;
  ext.len = 0;
  ext.alloced = 20;
  ext.data = ext.baseBuffer;
  ext.baseBuffer[0] = 0;
  idStr::ExtractFileExtension(&name, &ext);
  if ( allowOgg && !idStr::Icmp(ext.data, "ogg") && fileSystem->ReadFile(fileSystem, name.data, 0, 0) != -1 )
  {
    v12 = idWaveFile::OpenOGG(this, name.data, pwfx);
    LOBYTE(v17) = 0;
    idStr::FreeData(&ext);
    v17 = -1;
    idStr::FreeData(&name);
    return v12;
  }
  idStr::SetFileExtension(&name, "wav");
  *(_DWORD *)&this->mpwfx.Format.wFormatTag = 0;
  this->mpwfx.Format.nSamplesPerSec = 0;
  this->mpwfx.Format.nAvgBytesPerSec = 0;
  *(_DWORD *)&this->mpwfx.Format.nBlockAlign = 0;
  *(_DWORD *)&this->mpwfx.Format.cbSize = 0;
  this->mpwfx.dwChannelMask = 0;
  this->mpwfx.SubFormat = 0;
  v13 = fileSystem->OpenFileRead(fileSystem, strFileName, 1, 0);
  this->mhmmio = v13;
  if ( !v13 )
  {
    this->mdwSize = 0;
LABEL_13:
    LOBYTE(v17) = 0;
    idStr::FreeData(&ext);
    v17 = -1;
    idStr::FreeData(&name);
    return -1;
  }
  if ( v13->Length(v13) <= 0 )
  {
    this->mhmmio = 0;
    goto LABEL_13;
  }
  if ( idWaveFile::ReadMMIO(this)
    || (this->mfileTime = this->mhmmio->Timestamp(this->mhmmio), idWaveFile::ResetFile(this)) )
  {
    idWaveFile::Close(this);
    goto LABEL_13;
  }
  cksize = this->mck.cksize;
  this->mdwSize = cksize >> 1;
  this->mMemSize = cksize;
  if ( cksize == -1 )
    goto LABEL_13;
  if ( pwfx )
    *pwfx = this->mpwfx.Format;
  LOBYTE(v17) = 0;
  idStr::FreeData(&ext);
  v17 = -1;
  idStr::FreeData(&name);
  return 0;
}
