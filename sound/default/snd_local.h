
// FUNC: public: virtual unsigned char const * __thiscall idSoundSample::GetSampleData(void)const
idImage *__thiscall idSoundSample::GetSampleData(idImageManagerLocal *this)
{
  return this->scratchImage2;
}

// FUNC: public: virtual float __thiscall idSoundSample::GetDuration(void)const
double __thiscall idSoundSample::GetDuration(idSoundSample *this)
{
  return (double)((int (__thiscall *)(idSoundSample *, idSoundSample *))this->GetDurationMS)(this, this) * 0.001;
}

// FUNC: public: virtual bool __thiscall idSoundSample::IsOgg(void)const
bool __thiscall idSoundSample::IsOgg(idSoundSample *this)
{
  return this->isOgg;
}

// FUNC: public: virtual int __thiscall idSoundSample::GetDurationMS(void)const
int __thiscall idSoundSample::GetDurationMS(idSoundSample *this)
{
  int nSamplesPerSec; // eax
  bool v3; // zf
  int objectSize; // eax

  nSamplesPerSec = this->nSamplesPerSec;
  if ( nSamplesPerSec == 11025 )
    return soundSystem->SamplesToMilliseconds(soundSystem, 4 * this->objectSize);
  v3 = nSamplesPerSec == 22050;
  objectSize = this->objectSize;
  if ( v3 )
    objectSize *= 2;
  return soundSystem->SamplesToMilliseconds(soundSystem, objectSize);
}

// FUNC: public: virtual __thiscall idSampleDecoder::~idSampleDecoder(void)
void __thiscall idSampleDecoder::~idSampleDecoder(idSampleDecoder *this)
{
  this->__vftable = (idSampleDecoder_vtbl *)&idSampleDecoder::`vftable';
}

// FUNC: public: virtual bool __thiscall idSoundEmitterLocal::AttachedToWorld(int)const
BOOL __thiscall idSoundEmitterLocal::AttachedToWorld(idSoundEmitterLocal *this, int id)
{
  return id == -1 || this->worldId == id;
}

// FUNC: public: virtual bool __thiscall idSoundSystemLocal::HasCache(void)const
BOOL __thiscall idSoundSystemLocal::HasCache(idSoundSystemLocal *this)
{
  return this->soundCache != 0;
}

// FUNC: public: virtual void __thiscall idSoundSystemLocal::SetRenderWorld(class idRenderWorld *)
void __thiscall idSoundSystemLocal::SetRenderWorld(idSoundSystemLocal *this, idRenderWorld *renderWorld)
{
  this->rw = renderWorld;
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::GetActiveSoundWorld(void)
int __thiscall idSoundSystemLocal::GetActiveSoundWorld(idEditField *this)
{
  return this->autoComplete.length;
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::GetNumAreas(void)
int __thiscall idSoundSystemLocal::GetNumAreas(idSoundSystemLocal *this)
{
  return this->areaReverbs.num;
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::GetNumEmitters(void)const
int __thiscall idSoundSystemLocal::GetNumEmitters(idSoundSystemLocal *this)
{
  return this->emitters.num;
}

// FUNC: public: virtual int __thiscall idAASFileLocal::GetNumAreas(void)const
int __thiscall idAASFileLocal::GetNumAreas(idAASFileLocal *this)
{
  return this->areas.num;
}
