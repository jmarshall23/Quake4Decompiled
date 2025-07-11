
// FUNC: public: virtual __thiscall idAudioHardware::~idAudioHardware(void)
void __thiscall idAudioHardware::~idAudioHardware(idAudioHardware *this)
{
  this->__vftable = (idAudioHardware_vtbl *)&idAudioHardware::`vftable';
}

// FUNC: private: int __thiscall idAudioBufferWIN32::RestoreBuffer(struct IDirectSoundBuffer *,bool *)
HRESULT __userpurge idAudioBufferWIN32::RestoreBuffer@<eax>(
        idAudioBufferWIN32 *this@<ecx>,
        IDirectSoundBuffer *a2@<edi>,
        IDirectSoundBuffer *pDSB,
        bool *pbWasRestored)
{
  IDirectSoundBuffer *v4; // esi
  HRESULT result; // eax
  bool *v6; // ebx

  v4 = pDSB;
  if ( !pDSB )
    return -1;
  v6 = pbWasRestored;
  if ( pbWasRestored )
    *pbWasRestored = 0;
  result = v4->GetStatus(v4, (unsigned int *)&pDSB);
  if ( result >= 0 )
  {
    if ( ((unsigned __int8)pDSB & 2) != 0 )
    {
      do
      {
        if ( ((int (__stdcall *)(IDirectSoundBuffer *, IDirectSoundBuffer *))v4->Restore)(v4, a2) == -2005401450 )
          Sleep(0xAu);
        a2 = v4;
      }
      while ( ((int (*)(void))v4->Restore)() );
      if ( v6 )
        *v6 = 1;
      return 0;
    }
    else
    {
      return 1;
    }
  }
  return result;
}

// FUNC: public: virtual int __thiscall idAudioBufferWIN32::Stop(void)
int __thiscall idAudioBufferWIN32::Stop(idAudioBufferWIN32 *this)
{
  if ( !this || !this->m_apDSBuffer )
    return -1;
  this->m_apDSBuffer->Stop(this->m_apDSBuffer);
  return 0;
}

// FUNC: public: virtual int __thiscall idAudioBufferWIN32::Reset(void)
int __thiscall idAudioBufferWIN32::Reset(idAudioBufferWIN32 *this)
{
  if ( !this->m_apDSBuffer )
    return -1;
  this->m_apDSBuffer->SetCurrentPosition(this->m_apDSBuffer, 0);
  return 0;
}

// FUNC: public: virtual bool __thiscall idAudioBufferWIN32::IsSoundPlaying(void)
bool __thiscall idAudioBufferWIN32::IsSoundPlaying(idAudioBufferWIN32 *this)
{
  IDirectSoundBuffer *m_apDSBuffer; // eax
  unsigned int dwStatus; // [esp+8h] [ebp-4h] BYREF

  dwStatus = (unsigned int)this;
  if ( !this->m_apDSBuffer )
    return 0;
  m_apDSBuffer = this->m_apDSBuffer;
  dwStatus = 0;
  m_apDSBuffer->GetStatus(m_apDSBuffer, &dwStatus);
  return dwStatus & 1;
}

// FUNC: public: bool __thiscall idAudioBufferWIN32::Lock(void * *,unsigned long *)
bool __thiscall idAudioBufferWIN32::Lock(
        idAudioBufferWIN32 *this,
        void **pDSLockedBuffer,
        unsigned int *dwDSLockedBufferSize)
{
  bool bRestored; // [esp+7h] [ebp-1h] BYREF

  return idAudioBufferWIN32::RestoreBuffer(this, this->m_apDSBuffer, &bRestored) >= 0
      && this->m_apDSBuffer->Lock(
           this->m_apDSBuffer,
           0,
           this->m_dwDSBufferSize,
           pDSLockedBuffer,
           dwDSLockedBufferSize,
           0,
           0,
           0) >= 0;
}

// FUNC: public: bool __thiscall idAudioBufferWIN32::GetCurrentPosition(unsigned long *)
bool __userpurge idAudioBufferWIN32::GetCurrentPosition@<al>(
        idAudioBufferWIN32 *this@<ecx>,
        IDirectSoundBuffer *a2@<edi>,
        unsigned int *pdwCurrentWriteCursor)
{
  IDirectSoundBuffer *m_apDSBuffer; // esi
  unsigned int v7; // [esp+8h] [ebp-4h] BYREF

  m_apDSBuffer = this->m_apDSBuffer;
  if ( !m_apDSBuffer || m_apDSBuffer->GetStatus(m_apDSBuffer, &v7) < 0 )
    return 0;
  if ( (v7 & 2) != 0 )
  {
    do
    {
      if ( ((int (__stdcall *)(IDirectSoundBuffer *, IDirectSoundBuffer *))m_apDSBuffer->Restore)(m_apDSBuffer, a2) == -2005401450 )
        Sleep(0xAu);
      a2 = m_apDSBuffer;
    }
    while ( ((int (*)(void))m_apDSBuffer->Restore)() );
  }
  return this->m_apDSBuffer->GetCurrentPosition(this->m_apDSBuffer, 0, pdwCurrentWriteCursor) >= 0;
}

// FUNC: public: virtual void __thiscall idAudioBufferWIN32::SetVolume(float)
void __thiscall idAudioBufferWIN32::SetVolume(idAudioBufferWIN32 *this, float x)
{
  if ( this->m_apDSBuffer )
    this->m_apDSBuffer->SetVolume(this->m_apDSBuffer, (int)x);
}

// FUNC: public: virtual int __thiscall idAudioHardwareWIN32::GetNumberOfSpeakers(void)
int __thiscall idAudioHardwareWIN32::GetNumberOfSpeakers(idAudioHardwareWIN32 *this)
{
  return this->numSpeakers;
}

// FUNC: public: virtual int __thiscall idAudioHardwareWIN32::GetMixBufferSize(void)
int __thiscall idAudioHardwareWIN32::GetMixBufferSize(idAudioHardwareWIN32 *this)
{
  return this->blockAlign << 12;
}

// FUNC: unsigned char __cdecl empty_output_buffer(struct jpeg_compress_struct *)
char __thiscall empty_output_buffer(idRenderModelBeam *this)
{
  return 1;
}

// FUNC: public: virtual bool __thiscall idAudioHardwareWIN32::Lock(void * *,unsigned long *)
bool __thiscall idAudioHardwareWIN32::Lock(
        idAudioHardwareWIN32 *this,
        void **pDSLockedBuffer,
        unsigned int *dwDSLockedBufferSize)
{
  idAudioBufferWIN32 *speakers; // ecx

  speakers = this->speakers;
  return speakers && idAudioBufferWIN32::Lock(speakers, pDSLockedBuffer, dwDSLockedBufferSize);
}

// FUNC: public: virtual bool __thiscall idAudioHardwareWIN32::Unlock(void *,unsigned int)
char __thiscall idAudioHardwareWIN32::Unlock(
        idAudioHardwareWIN32 *this,
        void *pDSLockedBuffer,
        unsigned int dwDSLockedBufferSize)
{
  idAudioBufferWIN32 *speakers; // eax

  speakers = this->speakers;
  if ( !speakers )
    return 0;
  speakers->m_apDSBuffer->Unlock(speakers->m_apDSBuffer, pDSLockedBuffer, dwDSLockedBufferSize, 0, 0);
  return 1;
}

// FUNC: public: virtual bool __thiscall idAudioHardwareWIN32::GetCurrentPosition(unsigned long *)
bool __userpurge idAudioHardwareWIN32::GetCurrentPosition@<al>(
        idAudioHardwareWIN32 *this@<ecx>,
        IDirectSoundBuffer *a2@<edi>,
        unsigned int *pdwCurrentWriteCursor)
{
  idAudioBufferWIN32 *speakers; // ecx

  speakers = this->speakers;
  return speakers && idAudioBufferWIN32::GetCurrentPosition(speakers, a2, pdwCurrentWriteCursor);
}

// FUNC: public: int __thiscall idAudioBufferWIN32::FillBufferWithSound(struct IDirectSoundBuffer *,bool)
int __userpurge idAudioBufferWIN32::FillBufferWithSound@<eax>(
        idAudioBufferWIN32 *this@<ecx>,
        IDirectSoundBuffer *a2@<edi>,
        IDirectSoundBuffer *pDSB,
        bool bRepeatWavIfBufferLarger)
{
  int v4; // ebx
  int result; // eax
  unsigned int v7; // ecx
  int v8; // edi
  char *v9; // edi
  int v10; // eax
  char v11; // dl
  unsigned int v12; // ecx
  unsigned int dwDSLockedBufferSize; // [esp+20h] [ebp-Ch] BYREF
  void *pDSLockedBuffer; // [esp+24h] [ebp-8h] BYREF
  int dwWavDataRead; // [esp+28h] [ebp-4h] BYREF

  HIWORD(v4) = 0;
  pDSLockedBuffer = 0;
  dwDSLockedBufferSize = 0;
  dwWavDataRead = 0;
  if ( !pDSB
    || !this->m_pWaveFile
    || idAudioBufferWIN32::RestoreBuffer(this, a2, pDSB, 0) < 0
    || pDSB->Lock(pDSB, 0, this->m_dwDSBufferSize, &pDSLockedBuffer, &dwDSLockedBufferSize, 0, 0, 0) < 0 )
  {
    return -1;
  }
  idWaveFile::ResetFile(this->m_pWaveFile);
  result = idWaveFile::Read(this->m_pWaveFile, (unsigned __int8 *)pDSLockedBuffer, dwDSLockedBufferSize, &dwWavDataRead);
  if ( result >= 0 )
  {
    v7 = dwDSLockedBufferSize;
    v8 = dwWavDataRead;
    if ( !dwWavDataRead )
    {
      v9 = (char *)pDSLockedBuffer;
      LOBYTE(v4) = this->m_pWaveFile->mpwfx.Format.wBitsPerSample != 8 ? 0 : 0x80;
      BYTE1(v4) = v4;
      v10 = v4 << 16;
      LOWORD(v10) = v4;
LABEL_16:
      v11 = v7;
      v12 = v7 >> 2;
      memset32(v9, v10, v12);
      memset(&v9[4 * v12], v10, v11 & 3);
      goto LABEL_17;
    }
    if ( dwWavDataRead >= (int)dwDSLockedBufferSize )
    {
LABEL_17:
      pDSB->Unlock(pDSB, pDSLockedBuffer, dwDSLockedBufferSize, 0, 0);
      return 0;
    }
    if ( !bRepeatWavIfBufferLarger )
    {
      v7 = dwDSLockedBufferSize - dwWavDataRead;
      v9 = (char *)pDSLockedBuffer + dwWavDataRead;
      LOBYTE(v4) = this->m_pWaveFile->mpwfx.Format.wBitsPerSample != 8 ? 0 : 0x80;
      BYTE1(v4) = v4;
      v10 = v4 << 16;
      LOWORD(v10) = v4;
      goto LABEL_16;
    }
    while ( 1 )
    {
      result = idWaveFile::ResetFile(this->m_pWaveFile);
      if ( result < 0 )
        break;
      result = idWaveFile::Read(
                 this->m_pWaveFile,
                 (unsigned __int8 *)pDSLockedBuffer + v8,
                 dwDSLockedBufferSize - v8,
                 &dwWavDataRead);
      if ( result < 0 )
        break;
      v8 += dwWavDataRead;
      if ( v8 >= (int)dwDSLockedBufferSize )
        goto LABEL_17;
    }
  }
  return result;
}

// FUNC: public: virtual int __thiscall idAudioBufferWIN32::Play(unsigned int,unsigned int)
int __thiscall idAudioBufferWIN32::Play(idAudioBufferWIN32 *this, unsigned int dwPriority, unsigned int dwFlags)
{
  IDirectSoundBuffer *m_apDSBuffer; // eax
  int v6; // eax
  int v7; // eax
  bool bRestored; // [esp+7h] [ebp-1h] BYREF

  m_apDSBuffer = this->m_apDSBuffer;
  if ( !m_apDSBuffer )
    return -1;
  v6 = idAudioBufferWIN32::RestoreBuffer(this, m_apDSBuffer, &bRestored);
  if ( v6 < 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 152))(
      common.type,
      "RestoreBuffer",
      v6);
  if ( bRestored )
  {
    v7 = idAudioBufferWIN32::FillBufferWithSound(this, this->m_apDSBuffer, 0);
    if ( v7 < 0 )
      (*(void (__cdecl **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 152))(
        common.type,
        "FillBufferWithSound",
        v7);
    this->Reset(this);
  }
  this->m_apDSBuffer->Play(this->m_apDSBuffer, 0, dwPriority, dwFlags);
  return 0;
}

// FUNC: public: static class idAudioHardware * __cdecl idAudioHardware::Alloc(void)
idAudioHardware *__cdecl idAudioHardware::Alloc()
{
  idAudioHardware *result; // eax

  result = (idAudioHardware *)Memory::Allocate(0x20u);
  if ( !result )
    return 0;
  result->__vftable = (idAudioHardware_vtbl *)&idAudioHardwareWIN32::`vftable';
  result[1].__vftable = 0;
  result[2].__vftable = 0;
  result[3].__vftable = 0;
  return result;
}

// FUNC: public: virtual __thiscall idAudioHardwareWIN32::~idAudioHardwareWIN32(void)
void __thiscall idAudioHardwareWIN32::~idAudioHardwareWIN32(idAudioHardwareWIN32 *this)
{
  idAudioBufferWIN32 *speakers; // esi
  idWaveFile *m_pWaveFile; // ebx
  IDirectSoundBuffer *m_apDSBuffer; // eax
  IDirectSoundBuffer *pDSBPrimary; // eax
  IDirectSound *m_pDS; // eax

  this->__vftable = (idAudioHardwareWIN32_vtbl *)&idAudioHardwareWIN32::`vftable';
  speakers = this->speakers;
  if ( speakers )
  {
    m_pWaveFile = speakers->m_pWaveFile;
    speakers->__vftable = (idAudioBufferWIN32_vtbl *)&idAudioBufferWIN32::`vftable';
    if ( m_pWaveFile )
    {
      idWaveFile::~idWaveFile(m_pWaveFile);
      Memory::Free(m_pWaveFile);
      speakers->m_pWaveFile = 0;
    }
    m_apDSBuffer = speakers->m_apDSBuffer;
    if ( m_apDSBuffer )
    {
      m_apDSBuffer->Release(speakers->m_apDSBuffer);
      speakers->m_apDSBuffer = 0;
    }
    speakers->m_pWaveFile = 0;
    speakers->m_apDSBuffer = 0;
    Memory::Free(speakers);
    this->speakers = 0;
  }
  pDSBPrimary = this->pDSBPrimary;
  if ( pDSBPrimary )
  {
    pDSBPrimary->Release(this->pDSBPrimary);
    this->pDSBPrimary = 0;
  }
  m_pDS = this->m_pDS;
  if ( m_pDS )
  {
    m_pDS->Release(this->m_pDS);
    this->m_pDS = 0;
  }
  this->__vftable = (idAudioHardwareWIN32_vtbl *)&idAudioHardware::`vftable';
}

// FUNC: public: __thiscall idAudioBufferWIN32::idAudioBufferWIN32(struct IDirectSoundBuffer *,unsigned int,class idWaveFile *)
void __userpurge idAudioBufferWIN32::idAudioBufferWIN32(
        idAudioBufferWIN32 *this@<ecx>,
        IDirectSoundBuffer *a2@<edi>,
        IDirectSoundBuffer *apDSBuffer,
        unsigned int dwDSBufferSize,
        idWaveFile *pWaveFile)
{
  this->m_dwDSBufferSize = dwDSBufferSize;
  this->__vftable = (idAudioBufferWIN32_vtbl *)&idAudioBufferWIN32::`vftable';
  this->m_apDSBuffer = apDSBuffer;
  this->m_pWaveFile = pWaveFile;
  if ( pWaveFile )
  {
    idAudioBufferWIN32::FillBufferWithSound(this, a2, apDSBuffer, 0);
    this->m_apDSBuffer->SetCurrentPosition(this->m_apDSBuffer, 0);
  }
}

// FUNC: public: int __thiscall idAudioHardwareWIN32::CreateFromMemory(class idAudioBufferWIN32 * *,unsigned char *,unsigned long,struct waveformatextensible_s *,unsigned int)
int __thiscall idAudioHardwareWIN32::CreateFromMemory(
        idAudioHardwareWIN32 *this,
        idAudioBufferWIN32 **ppSound,
        unsigned __int8 *pbData,
        unsigned int ulDataSize,
        waveformatextensible_s *pwfx,
        unsigned int dwCreationFlags)
{
  idWaveFile *v6; // ebx
  bool v8; // zf
  IDirectSoundBuffer *v9; // eax
  idWaveFile *v10; // eax
  IDirectSound *m_pDS; // eax
  int result; // eax
  idAudioBufferWIN32 *v13; // eax
  idAudioBufferWIN32 *v14; // eax
  IDirectSoundBuffer *apDSBuffer[2]; // [esp+10h] [ebp-38h] BYREF
  _DSBUFFERDESC dsbd; // [esp+18h] [ebp-30h] BYREF
  int v17; // [esp+44h] [ebp-4h]

  v6 = 0;
  v8 = this->m_pDS == 0;
  apDSBuffer[0] = 0;
  if ( v8 || !pbData || !ppSound )
    return -1;
  v9 = (IDirectSoundBuffer *)Memory::Allocate(0x68u);
  apDSBuffer[1] = v9;
  v17 = 0;
  if ( v9 )
  {
    idWaveFile::idWaveFile((idWaveFile *)v9);
    v6 = v10;
  }
  v17 = -1;
  idWaveFile::OpenFromMemory(v6, (__int16 *)pbData, ulDataSize, pwfx);
  dsbd.dwSize = 0;
  memset(&dsbd.dwBufferBytes, 0, 28);
  dsbd.dwFlags = dwCreationFlags | 0x10000;
  m_pDS = this->m_pDS;
  dsbd.dwSize = 36;
  dsbd.dwBufferBytes = ulDataSize;
  *(_DWORD *)&dsbd.guid3DAlgorithm.Data2 = *(_DWORD *)&_GUID_00000000_0000_0000_0000_000000000000.Data2;
  dsbd.lpwfxFormat = (tWAVEFORMATEX *)pwfx;
  if ( m_pDS->CreateSoundBuffer(m_pDS, &dsbd, apDSBuffer, 0) < 0 )
    return -1;
  v13 = (idAudioBufferWIN32 *)Memory::Allocate(0x10u);
  v17 = 1;
  if ( v13 )
  {
    idAudioBufferWIN32::idAudioBufferWIN32(v13, (IDirectSoundBuffer *)pwfx, apDSBuffer[0], ulDataSize, v6);
    *ppSound = v14;
    return 0;
  }
  else
  {
    result = 0;
    *ppSound = 0;
  }
  return result;
}

// FUNC: public: bool __thiscall idAudioHardwareWIN32::InitializeSpeakers(unsigned char *,int,unsigned int,unsigned int,unsigned int)
char __thiscall idAudioHardwareWIN32::InitializeSpeakers(
        idAudioHardwareWIN32 *this,
        unsigned __int8 *speakerData,
        int bufferSize,
        unsigned int dwPrimaryFreq,
        unsigned __int16 dwPrimaryBitRate,
        unsigned int dwSpeakers)
{
  idAudioBufferWIN32 **p_speakers; // esi
  WAVEFORMATEXTENSIBLE waveFormatPCMEx; // [esp+4h] [ebp-28h] BYREF

  *(_DWORD *)&waveFormatPCMEx.Format.wFormatTag = 0;
  memset(&waveFormatPCMEx.Format.nAvgBytesPerSec, 0, 32);
  waveFormatPCMEx.Format.nSamplesPerSec = dwPrimaryFreq;
  p_speakers = &this->speakers;
  if ( dwSpeakers == 2 )
  {
    waveFormatPCMEx.Format.nChannels = 2;
    waveFormatPCMEx.Format.wBitsPerSample = dwPrimaryBitRate;
    waveFormatPCMEx.Format.wFormatTag = 1;
    waveFormatPCMEx.Format.cbSize = 18;
    waveFormatPCMEx.Format.nBlockAlign = 2 * (dwPrimaryBitRate >> 3);
    waveFormatPCMEx.Format.nAvgBytesPerSec = dwPrimaryFreq * waveFormatPCMEx.Format.nBlockAlign;
    idAudioHardwareWIN32::CreateFromMemory(
      this,
      &this->speakers,
      speakerData,
      bufferSize,
      (waveformatextensible_s *)&waveFormatPCMEx,
      0);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "sound: STEREO\n");
  }
  else
  {
    waveFormatPCMEx.Format.wBitsPerSample = dwPrimaryBitRate;
    waveFormatPCMEx.Format.wFormatTag = -2;
    waveFormatPCMEx.Format.nChannels = 6;
    waveFormatPCMEx.dwChannelMask = 63;
    waveFormatPCMEx.Format.cbSize = 40;
    waveFormatPCMEx.Samples.wValidBitsPerSample = 16;
    waveFormatPCMEx.Format.nBlockAlign = 6 * (dwPrimaryBitRate >> 3);
    waveFormatPCMEx.Format.nAvgBytesPerSec = dwPrimaryFreq * waveFormatPCMEx.Format.nBlockAlign;
    waveFormatPCMEx.SubFormat = _GUID_00000001_0000_0010_8000_00aa00389b71;
    idAudioHardwareWIN32::CreateFromMemory(
      this,
      &this->speakers,
      speakerData,
      bufferSize,
      (waveformatextensible_s *)&waveFormatPCMEx,
      0);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "sound: MULTICHANNEL\n");
  }
  if ( !*p_speakers )
    return 0;
  (*p_speakers)->Play(*p_speakers, 0, 1u);
  return 1;
}

// FUNC: public: void __thiscall idAudioHardwareWIN32::SetPrimaryBufferFormat(unsigned int,unsigned int,unsigned int)
void __thiscall idAudioHardwareWIN32::SetPrimaryBufferFormat(
        idAudioHardwareWIN32 *this,
        unsigned int dwPrimaryFreq,
        unsigned __int16 dwPrimaryBitRate,
        unsigned int dwSpeakers)
{
  IDirectSound *m_pDS; // eax
  IDirectSound *v6; // eax
  IDirectSound *v7; // eax
  IDirectSoundBuffer **p_pDSBPrimary; // edi
  unsigned __int16 v9; // bp
  unsigned int v10; // ebx
  IDirectSoundBuffer *v11; // eax
  int nBlockAlign; // eax
  IDirectSoundBuffer *v13; // eax
  unsigned __int8 *v14; // eax
  unsigned int bufferSize; // edx
  unsigned __int8 *v16; // edi
  char v17; // cl
  unsigned __int8 *v18; // edx
  int v19; // [esp+14h] [ebp-E0h]
  unsigned int cfgSpeakers; // [esp+2Ch] [ebp-C8h] BYREF
  tWAVEFORMATEX wfx; // [esp+30h] [ebp-C4h] BYREF
  WAVEFORMATEXTENSIBLE waveFormatPCMEx; // [esp+44h] [ebp-B0h] BYREF
  unsigned __int8 *speakerData; // [esp+6Ch] [ebp-88h]
  _DSBUFFERDESC dsbd; // [esp+70h] [ebp-84h] BYREF
  _DSCAPS dscaps; // [esp+94h] [ebp-60h] BYREF

  m_pDS = this->m_pDS;
  if ( m_pDS )
  {
    m_pDS->GetSpeakerConfig(m_pDS, &cfgSpeakers);
    cfgSpeakers = (unsigned __int8)cfgSpeakers;
    v6 = this->m_pDS;
    dscaps.dwSize = 96;
    v6->GetCaps(v6, &dscaps);
    if ( (dscaps.dwFlags & 0x20) == 0 )
    {
      memset(&dsbd, 0, sizeof(dsbd));
      v7 = this->m_pDS;
      dsbd.dwSize = 36;
      dsbd.dwFlags = 1;
      dsbd.dwBufferBytes = 0;
      dsbd.lpwfxFormat = 0;
      if ( v7->SetCooperativeLevel(v7, win32.hWnd, 2u) >= 0 )
      {
        p_pDSBPrimary = &this->pDSBPrimary;
        if ( this->m_pDS->CreateSoundBuffer(this->m_pDS, &dsbd, &this->pDSBPrimary, 0) >= 0 )
        {
          if ( dwSpeakers == 6 )
          {
            if ( cfgSpeakers == 6 || cfgSpeakers == 5 )
            {
              v9 = dwPrimaryBitRate;
              v10 = dwPrimaryFreq;
              waveFormatPCMEx.Format.wFormatTag = 0;
              waveFormatPCMEx.Format.nChannels = 6;
              waveFormatPCMEx.Format.nSamplesPerSec = 0;
              memset(&waveFormatPCMEx.Format.wBitsPerSample, 0, 10);
              waveFormatPCMEx.Format.nBlockAlign = 6 * (dwPrimaryBitRate >> 3);
              *(_DWORD *)&waveFormatPCMEx.SubFormat.Data2 = 0;
              waveFormatPCMEx.Format.nAvgBytesPerSec = dwPrimaryFreq * waveFormatPCMEx.Format.nBlockAlign;
              waveFormatPCMEx.SubFormat.Data1 = _GUID_00000001_0000_0010_8000_00aa00389b71.Data1;
              *(_DWORD *)waveFormatPCMEx.SubFormat.Data4 = *(_DWORD *)_GUID_00000001_0000_0010_8000_00aa00389b71.Data4;
              *(_DWORD *)&waveFormatPCMEx.SubFormat.Data4[4] = *(_DWORD *)&_GUID_00000001_0000_0010_8000_00aa00389b71.Data4[4];
              v11 = *p_pDSBPrimary;
              waveFormatPCMEx.Format.wFormatTag = -2;
              waveFormatPCMEx.Format.nSamplesPerSec = dwPrimaryFreq;
              waveFormatPCMEx.Format.wBitsPerSample = dwPrimaryBitRate;
              waveFormatPCMEx.dwChannelMask = 63;
              *(_DWORD *)&waveFormatPCMEx.SubFormat.Data2 = *(_DWORD *)&_GUID_00000001_0000_0010_8000_00aa00389b71.Data2;
              waveFormatPCMEx.Format.cbSize = 40;
              waveFormatPCMEx.Samples.wValidBitsPerSample = 16;
              if ( v11->SetFormat(v11, &waveFormatPCMEx.Format) < 0 )
                return;
              nBlockAlign = waveFormatPCMEx.Format.nBlockAlign;
              this->numSpeakers = 6;
LABEL_13:
              this->blockAlign = nBlockAlign;
              v19 = (ROOM_SLICES_IN_BUFFER * this->numSpeakers) << 13;
              this->bufferSize = v19;
              v14 = (unsigned __int8 *)Mem_Alloc(v19, 0x12u);
              bufferSize = this->bufferSize;
              speakerData = v14;
              memset(v14, 0, 4 * (bufferSize >> 2));
              v16 = &v14[4 * (bufferSize >> 2)];
              v17 = bufferSize;
              v18 = speakerData;
              memset(v16, 0, v17 & 3);
              idAudioHardwareWIN32::InitializeSpeakers(this, v18, this->bufferSize, v10, v9, this->numSpeakers);
              return;
            }
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
              common.type,
              "sound: hardware reported unable to use multisound, defaulted to stereo\n");
          }
          v10 = dwPrimaryFreq;
          wfx.nChannels = 0;
          wfx.wFormatTag = 1;
          v9 = dwPrimaryBitRate;
          wfx.nSamplesPerSec = 0;
          wfx.wBitsPerSample = 0;
          wfx.cbSize = 0;
          wfx.nBlockAlign = 2 * (dwPrimaryBitRate >> 3);
          wfx.nAvgBytesPerSec = dwPrimaryFreq * wfx.nBlockAlign;
          v13 = *p_pDSBPrimary;
          wfx.nChannels = 2;
          wfx.nSamplesPerSec = dwPrimaryFreq;
          wfx.wBitsPerSample = dwPrimaryBitRate;
          wfx.cbSize = 18;
          if ( v13->SetFormat(v13, &wfx) < 0 )
            return;
          nBlockAlign = wfx.nBlockAlign;
          this->numSpeakers = 2;
          goto LABEL_13;
        }
      }
    }
  }
}

// FUNC: public: virtual bool __thiscall idAudioHardwareWIN32::Initialize(void)
char __thiscall idAudioHardwareWIN32::Initialize(idAudioHardwareWIN32 *this)
{
  IDirectSound *m_pDS; // eax
  IDirectSound **p_m_pDS; // edi

  m_pDS = this->m_pDS;
  p_m_pDS = &this->m_pDS;
  this->bufferSize = 0;
  this->numSpeakers = 0;
  this->blockAlign = 0;
  if ( m_pDS )
  {
    m_pDS->Release(m_pDS);
    *p_m_pDS = 0;
  }
  if ( DirectSoundCreate(0, p_m_pDS, 0) < 0 )
    return 0;
  idAudioHardwareWIN32::SetPrimaryBufferFormat(
    this,
    0xAC44u,
    0x10u,
    idSoundSystemLocal::s_numberOfSpeakers.internalVar->integerValue);
  return 1;
}
