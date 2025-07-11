
// FUNC: unsigned int __cdecl FS_ReadOGG(void *,unsigned int,unsigned int,void *)
int __cdecl FS_ReadOGG(void *dest, unsigned int size1, unsigned int size2, void *fh)
{
  return (*(int (__thiscall **)(void *, void *, unsigned int))(*(_DWORD *)fh + 12))(fh, dest, size2 * size1);
}

// FUNC: int __cdecl FS_SeekOGG(void *,__int64,int)
int __cdecl FS_SeekOGG(void *fh, __int64 to, int type)
{
  if ( type == 1 )
    return (*(int (__thiscall **)(void *, _DWORD, _DWORD))(*(_DWORD *)fh + 40))(fh, to, 0);
  if ( type == 2 )
    return (*(int (__thiscall **)(void *, _DWORD, int))(*(_DWORD *)fh + 40))(fh, to, 1);
  if ( type )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "fs_seekOGG: seek without type\n");
  return (*(int (__thiscall **)(void *, _DWORD, int))(*(_DWORD *)fh + 40))(fh, to, 2);
}

// FUNC: public: virtual unsigned int __thiscall idFile_Common::Timestamp(void)
int __thiscall idFile_Common::Timestamp(idFile_Common *this)
{
  return 0;
}

// FUNC: long __cdecl FS_TellOGG(void *)
int __cdecl FS_TellOGG(void *fh)
{
  return (*(int (__thiscall **)(void *))(*(_DWORD *)fh + 28))(fh);
}

// FUNC: int __cdecl ov_openFile(class idFile *,struct OggVorbis_File *)
int __cdecl ov_openFile(idFile *f, OggVorbis_File *vf)
{
  ov_callbacks v3; // [esp+0h] [ebp-1Ch]

  memset(vf, 0, sizeof(OggVorbis_File));
  v3.read_func = (unsigned int (__cdecl *)(void *, unsigned int, unsigned int, void *))FS_ReadOGG;
  v3.seek_func = FS_SeekOGG;
  v3.close_func = (int (__cdecl *)(void *))idFile_Common::Timestamp;
  v3.tell_func = FS_TellOGG;
  return ov_open_callbacks(f, vf, 0, -1, v3);
}

// FUNC: private: int __thiscall idWaveFile::ReadOGG(unsigned char *,int,int *)
int __thiscall idWaveFile::ReadOGG(idWaveFile *this, unsigned __int8 *pBuffer, int dwSizeToRead, int *pdwSizeRead)
{
  OggVorbis_File *ogg; // ebp
  char *v6; // esi
  int v7; // edi
  bool IsBigEndian; // al
  int v9; // eax
  int v10; // esi

  ogg = (OggVorbis_File *)this->ogg;
  v6 = (char *)pBuffer;
  do
  {
    v7 = 4096;
    if ( dwSizeToRead < 4096 )
      v7 = dwSizeToRead;
    IsBigEndian = Swap_IsBigEndian();
    v9 = ov_read(ogg, v6, v7, IsBigEndian, 2, 1, &ogg->stream);
    if ( !v9 )
      break;
    if ( v9 < 0 )
      return -1;
    dwSizeToRead -= v9;
    v6 += v9;
  }
  while ( dwSizeToRead > 0 );
  v10 = v6 - (char *)pBuffer;
  if ( pdwSizeRead )
    *pdwSizeRead = v10;
  return v10;
}

// FUNC: private: int __thiscall idWaveFile::CloseOGG(void)
int __thiscall idWaveFile::CloseOGG(idWaveFile *this)
{
  OggVorbis_File *ogg; // edi

  ogg = (OggVorbis_File *)this->ogg;
  if ( !ogg )
    return -1;
  Sys_EnterCriticalSection(1);
  ov_clear(ogg);
  Memory::Free(ogg);
  Sys_LeaveCriticalSection(1);
  fileSystem->CloseFile(fileSystem, this->mhmmio);
  this->mhmmio = 0;
  this->ogg = 0;
  return 0;
}

// FUNC: public: virtual void __thiscall idSampleDecoderLocal::ClearDecoder(void)
void __thiscall idSampleDecoderLocal::ClearDecoder(idSampleDecoderLocal *this)
{
  Sys_EnterCriticalSection(1);
  if ( this->lastFormat == 2 )
  {
    ov_clear(&this->ogg);
    memset(&this->ogg, 0, sizeof(this->ogg));
  }
  this->failed = 0;
  this->lastFormat = 1;
  this->lastSample = 0;
  this->lastSampleOffset = 0;
  this->lastDecodeTime = 0;
  Sys_LeaveCriticalSection(1);
}

// FUNC: public: virtual char const * __thiscall idWinStr::c_str(void)const
int __thiscall idWinStr::c_str(idSampleDecoderLocal *this)
{
  return this->lastDecodeTime;
}

// FUNC: public: int __thiscall idSampleDecoderLocal::DecodePCM(class idSoundSample *,int,int,float *)
int __thiscall idSampleDecoderLocal::DecodePCM(
        idSampleDecoderLocal *this,
        idSoundSample *sample,
        int sampleOffset44k,
        char *sampleCount44k,
        float *dest)
{
  idSoundSample *v5; // esi
  int v7; // ebx
  int v8; // edi

  v5 = sample;
  this->lastFormat = 1;
  this->lastSample = v5;
  v7 = 22050 / v5->nSamplesPerSec;
  v8 = (int)sampleCount44k >> v7;
  if ( v5->nonCacheData
    && idSoundSample::FetchFromCache(
         v5,
         2 * (sampleOffset44k >> v7),
         (const unsigned __int8 **)&sampleOffset44k,
         (int *)&sampleCount44k,
         (int *)&sample,
         0) )
  {
    if ( (char *)sample - sampleCount44k < (unsigned int)(2 * v8) )
      v8 = (unsigned int)((char *)sample - sampleCount44k) >> 1;
    SIMDProcessor->UpSamplePCMTo44kHz(
      SIMDProcessor,
      dest,
      (const __int16 *)&sampleCount44k[sampleOffset44k],
      v8,
      v5->nSamplesPerSec,
      v5->nChannels);
    return v8 << v7;
  }
  else
  {
    this->failed = 1;
    return 0;
  }
}

// FUNC: private: int __thiscall idWaveFile::OpenOGG(char const *,struct waveformatex_s *)
int __thiscall idWaveFile::OpenOGG(idWaveFile *this, const char *strFileName, waveformatex_s *pwfx)
{
  idFile *v4; // eax
  OggVorbis_File *v6; // edi
  vorbis_info *v7; // ebp
  idFile *v8; // eax
  unsigned int v9; // eax
  unsigned int mdwSize; // eax

  *(_DWORD *)&pwfx->wFormatTag = 0;
  pwfx->nSamplesPerSec = 0;
  pwfx->nAvgBytesPerSec = 0;
  *(_DWORD *)&pwfx->nBlockAlign = 0;
  pwfx->cbSize = 0;
  v4 = fileSystem->OpenFileRead(fileSystem, strFileName, 1, 0);
  this->mhmmio = v4;
  if ( !v4 )
    return -1;
  Sys_EnterCriticalSection(1);
  v6 = (OggVorbis_File *)Memory::Allocate(0x2D8u);
  if ( ov_openFile(this->mhmmio, v6) >= 0 )
  {
    this->mfileTime = this->mhmmio->Timestamp(this->mhmmio);
    v7 = ov_info(v6, -1);
    this->mpwfx.Format.nSamplesPerSec = v7->rate;
    this->mpwfx.Format.nChannels = v7->channels;
    this->mpwfx.Format.wBitsPerSample = 16;
    this->mdwSize = v7->channels * ov_pcm_total(v6, -1);
    this->mbIsReadingFromMemory = 0;
    if ( idSoundSystemLocal::s_realTimeDecoding.internalVar->integerValue )
    {
      ov_clear(v6);
      fileSystem->CloseFile(fileSystem, this->mhmmio);
      this->mhmmio = 0;
      Memory::Free(v6);
      this->mpwfx.Format.wFormatTag = 2;
      v8 = fileSystem->OpenFileRead(fileSystem, strFileName, 1, 0);
      this->mhmmio = v8;
      v9 = v8->Length(v8);
    }
    else
    {
      mdwSize = this->mdwSize;
      this->ogg = v6;
      this->mpwfx.Format.wFormatTag = 1;
      v9 = 2 * mdwSize;
    }
    this->mMemSize = v9;
    *pwfx = this->mpwfx.Format;
    Sys_LeaveCriticalSection(1);
    this->isOgg = 1;
    return 0;
  }
  else
  {
    Memory::Free(v6);
    Sys_LeaveCriticalSection(1);
    fileSystem->CloseFile(fileSystem, this->mhmmio);
    this->mhmmio = 0;
    return -1;
  }
}

// FUNC: public: static void __cdecl idSampleDecoder::Free(class idSampleDecoder *)
void __cdecl idSampleDecoder::Free(idSampleDecoder *decoder)
{
  decoder->ClearDecoder(decoder);
  decoder[-2].__vftable = (idSampleDecoder_vtbl *)sampleDecoderAllocator.free;
  --sampleDecoderAllocator.active;
  sampleDecoderAllocator.free = CONTAINING_RECORD(decoder, idBlockAlloc<idSampleDecoderLocal,64,18>::element_s, t);
}

// FUNC: public: static int __cdecl idSampleDecoder::GetNumUsedBlocks(void)
int __cdecl idSampleDecoder::GetNumUsedBlocks()
{
  return decoderMemoryAllocator.numUsedBlocks;
}

// FUNC: public: static int __cdecl idSampleDecoder::GetUsedBlockMemory(void)
int __cdecl idSampleDecoder::GetUsedBlockMemory()
{
  return decoderMemoryAllocator.usedBlockMemory;
}

// FUNC: public: int __thiscall idSampleDecoderLocal::DecodeOGG(class idSoundSample *,int,int,float *)
int __thiscall idSampleDecoderLocal::DecodeOGG(
        idSampleDecoderLocal *this,
        idSoundSample *sample,
        int sampleOffset44k,
        float **sampleCount44k,
        float *dest)
{
  idSampleDecoderLocal *v6; // esi
  int v7; // ecx
  int v8; // ebp
  int v9; // ebx
  unsigned __int8 *nonCacheData; // eax
  int v11; // ebp
  int v12; // eax
  int v13; // esi
  char samplea; // [esp+18h] [ebp+4h]

  v6 = this;
  v7 = 22050 / sample->nSamplesPerSec;
  v8 = sampleOffset44k >> v7;
  v9 = (int)sampleCount44k >> v7;
  samplea = v7;
  if ( !this->lastSample )
  {
    if ( decoderMemoryAllocator.freeBlockMemory < 786432 )
      return 0;
    nonCacheData = sample->nonCacheData;
    if ( !nonCacheData
      || (idFile_Memory::SetData(&v6->file, (char *)nonCacheData, sample->objectMemSize),
          ov_openFile(&v6->file, &v6->ogg) < 0) )
    {
LABEL_14:
      v6->failed = 1;
      return 0;
    }
    v6->lastFormat = 2;
    v6->lastSample = sample;
  }
  if ( v8 != v6->lastSampleOffset && ov_pcm_seek(&v6->ogg, v8 / sample->nChannels) )
    goto LABEL_14;
  v6->lastSampleOffset = v8;
  v11 = 0;
  while ( 1 )
  {
    v12 = ov_read_float(&v6->ogg, (float ***)&sampleOffset44k, v9 / sample->nChannels, &v6->ogg.stream);
    if ( !v12 )
      break;
    if ( v12 < 0 )
      goto LABEL_14;
    v13 = v12 * sample->nChannels;
    SIMDProcessor->UpSampleOGGTo44kHz(
      SIMDProcessor,
      &dest[v11 << samplea],
      (const float *const *)sampleOffset44k,
      v13,
      sample->nSamplesPerSec,
      sample->nChannels);
    v9 -= v13;
    v11 += v13;
    v6 = this;
    if ( v9 <= 0 )
    {
      this->lastSampleOffset += v11;
      return v11 << samplea;
    }
  }
  v6->lastSampleOffset += v11;
  v6->failed = 1;
  return v11 << samplea;
}

// FUNC: public: virtual void __thiscall idSampleDecoderLocal::Decode(class idSoundSample *,int,int,float *)
void __thiscall idSampleDecoderLocal::Decode(
        idSampleDecoderLocal *this,
        idSoundSample *sample,
        int sampleOffset44k,
        int sampleCount44k,
        float *dest)
{
  bool v6; // zf
  int v7; // esi
  int v8; // eax

  if ( sample->wFormatTag != this->lastFormat || sample != this->lastSample )
    this->ClearDecoder(this);
  v6 = !this->failed;
  this->lastDecodeTime = soundSystemLocal.CurrentSoundTime;
  if ( !v6 )
  {
    memset(dest, 0, 4 * sampleCount44k);
    return;
  }
  Sys_EnterCriticalSection(1);
  if ( sample->wFormatTag == 1 )
  {
    v8 = idSampleDecoderLocal::DecodePCM(this, sample, sampleOffset44k, sampleCount44k, dest);
  }
  else
  {
    if ( sample->wFormatTag != 2 )
    {
      v7 = 0;
      goto LABEL_12;
    }
    v8 = idSampleDecoderLocal::DecodeOGG(this, sample, sampleOffset44k, sampleCount44k, dest);
  }
  v7 = v8;
LABEL_12:
  Sys_LeaveCriticalSection(1);
  if ( v7 < sampleCount44k )
    memset(&dest[v7], 0, 4 * ((unsigned int)(4 * (sampleCount44k - v7)) >> 2));
}

// FUNC: public: static class idSampleDecoder * __cdecl idSampleDecoder::Alloc(void)
idSampleDecoderLocal *__cdecl idSampleDecoder::Alloc()
{
  idSampleDecoderLocal *result; // eax

  result = idBlockAlloc<idSampleDecoderLocal,64,18>::Alloc(&sampleDecoderAllocator);
  result->failed = 0;
  result->lastFormat = 1;
  result->lastSample = 0;
  result->lastSampleOffset = 0;
  result->lastDecodeTime = 0;
  return result;
}

// FUNC: __decoder_free
void __cdecl _decoder_free(idDynamicBlock<int> *memblock)
{
  ++decoderMemoryAllocator.numFrees;
  if ( memblock )
  {
    --decoderMemoryAllocator.numUsedBlocks;
    decoderMemoryAllocator.usedBlockMemory -= abs32(memblock[-1].size);
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&decoderMemoryAllocator,
      memblock - 1);
  }
}

// FUNC: __decoder_malloc
idDynamicBlock<unsigned char> *__cdecl _decoder_malloc(int size)
{
  idDynamicBlock<unsigned char> *v1; // eax
  idDynamicBlock<unsigned char> *v2; // ecx

  ++decoderMemoryAllocator.numAllocs;
  if ( size <= 0 )
    return 0;
  v1 = idDynamicBlockAlloc<unsigned char,1048576,1024,18>::AllocInternal(
         (idDynamicBlockAlloc<unsigned char,1048576,1024,18> *)&decoderMemoryAllocator,
         size);
  if ( !v1 )
    return 0;
  v2 = idDynamicBlockAlloc<unsigned char,1048576,128,18>::ResizeInternal(
         &decoderMemoryAllocator,
         (idDynamicBlock<int> *)v1,
         size);
  if ( !v2 )
    return 0;
  ++decoderMemoryAllocator.numUsedBlocks;
  decoderMemoryAllocator.usedBlockMemory += abs32(v2->size);
  return v2 + 1;
}

// FUNC: __decoder_calloc
idDynamicBlock<unsigned char> *__cdecl _decoder_calloc(unsigned int num, unsigned int size)
{
  unsigned int v2; // esi
  idDynamicBlock<unsigned char> *v3; // eax
  idDynamicBlock<unsigned char> *v4; // eax
  idDynamicBlock<unsigned char> *v5; // edx

  v2 = size * num;
  ++decoderMemoryAllocator.numAllocs;
  if ( (int)(size * num) > 0
    && (v3 = idDynamicBlockAlloc<unsigned char,1048576,1024,18>::AllocInternal(
               (idDynamicBlockAlloc<unsigned char,1048576,1024,18> *)&decoderMemoryAllocator,
               size * num)) != 0
    && (v4 = idDynamicBlockAlloc<unsigned char,1048576,128,18>::ResizeInternal(
               &decoderMemoryAllocator,
               (idDynamicBlock<int> *)v3,
               v2)) != 0 )
  {
    ++decoderMemoryAllocator.numUsedBlocks;
    decoderMemoryAllocator.usedBlockMemory += abs32(v4->size);
    v5 = v4 + 1;
  }
  else
  {
    v5 = 0;
  }
  memset(v5, 0, v2);
  return v5;
}

// FUNC: __decoder_realloc
idDynamicBlock<unsigned char> *__cdecl _decoder_realloc(idDynamicBlock<int> *memblock, int size)
{
  return idDynamicBlockAlloc<unsigned char,1048576,128,18>::Resize(&decoderMemoryAllocator, memblock, size);
}
