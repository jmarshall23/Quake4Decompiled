
// FUNC: public: __thiscall rvSegmentTemplate::~rvSegmentTemplate(void)
void __thiscall rvSegmentTemplate::~rvSegmentTemplate(rvSegmentTemplate *this)
{
  rvParticleTemplate::~rvParticleTemplate(&this->mParticleTemplate);
  idStr::FreeData(&this->mSegmentName);
}

// FUNC: public: __thiscall rvDeclEffect::rvDeclEffect(void)
void __thiscall rvDeclEffect::rvDeclEffect(rvDeclEffect *this)
{
  this->base = 0;
  this->__vftable = (rvDeclEffect_vtbl *)&rvDeclEffect::`vftable';
  this->mSegmentTemplates.granularity = 16;
  this->mSegmentTemplates.list = 0;
  this->mSegmentTemplates.num = 0;
  this->mSegmentTemplates.size = 0;
  rvDeclEffect::Init(this);
}

// FUNC: public: virtual __thiscall rvDeclEffect::~rvDeclEffect(void)
void __thiscall rvDeclEffect::~rvDeclEffect(rvDeclEffect *this)
{
  rvSegmentTemplate *list; // eax
  rvBSE **p_mBSEEffect; // edi

  this->__vftable = (rvDeclEffect_vtbl *)&rvDeclEffect::`vftable';
  declEffectEdit->DeleteEditorOriginal(declEffectEdit, this->mEditorOriginal);
  list = this->mSegmentTemplates.list;
  if ( list )
  {
    p_mBSEEffect = &list[-1].mBSEEffect;
    `eh vector destructor iterator'(
      list,
      0x5CCu,
      (int)list[-1].mBSEEffect,
      (void (__thiscall *)(void *))rvSegmentTemplate::~rvSegmentTemplate);
    Memory::Free(p_mBSEEffect);
  }
  this->mSegmentTemplates.list = 0;
  this->mSegmentTemplates.num = 0;
  this->mSegmentTemplates.size = 0;
  this->__vftable = (rvDeclEffect_vtbl *)&idDecl::`vftable';
}

// FUNC: public: __thiscall rvSegment::rvSegment(void)
void __thiscall rvSegment::rvSegment(rvSegment *this)
{
  this->mFlags = 0;
  this->mParticles = 0;
  this->mUsedHead = 0;
  this->mFreeHead = 0;
  this->mParticleCount = 0;
  this->mLoopParticleCount = 0;
}

// FUNC: public: class idSoundEmitter * __thiscall rvBSE::GetReferenceSound(int)const
idSoundEmitter *__thiscall rvBSE::GetReferenceSound(rvBSE *this, int worldId)
{
  return soundSystem->EmitterForIndex(soundSystem, worldId, this->mReferenceSoundHandle);
}

// FUNC: public: __thiscall rvSegmentTemplate::rvSegmentTemplate(void)
void __thiscall rvSegmentTemplate::rvSegmentTemplate(rvSegmentTemplate *this)
{
  this->mSegmentName.len = 0;
  this->mSegmentName.alloced = 20;
  this->mSegmentName.data = this->mSegmentName.baseBuffer;
  this->mSegmentName.baseBuffer[0] = 0;
  rvParticleTemplate::rvParticleTemplate(&this->mParticleTemplate);
  declEffectEdit->Init(declEffectEdit, this, 0);
  this->mFlags |= 1u;
}

// FUNC: public: __thiscall rvDeclEffect::rvDeclEffect(class rvDeclEffect const &)
void __thiscall rvDeclEffect::rvDeclEffect(rvDeclEffect *this, const rvDeclEffect *copy)
{
  this->base = 0;
  this->__vftable = (rvDeclEffect_vtbl *)&rvDeclEffect::`vftable';
  this->mSegmentTemplates.granularity = 16;
  this->mSegmentTemplates.list = 0;
  this->mSegmentTemplates.num = 0;
  this->mSegmentTemplates.size = 0;
  rvDeclEffect::Init(this);
  rvDeclEffect::CopyData(this, copy);
}

// FUNC: public: __thiscall rvBSEManagerLocal::rvBSEManagerLocal(void)
void __thiscall rvBSEManagerLocal::rvBSEManagerLocal(rvBSEManagerLocal *this)
{
  this->__vftable = (rvBSEManagerLocal_vtbl *)&rvBSEManagerLocal::`vftable';
}

// FUNC: public: virtual __thiscall rvBSEManagerLocal::~rvBSEManagerLocal(void)
void __thiscall rvBSEManagerLocal::~rvBSEManagerLocal(rvBSEManagerLocal *this)
{
  this->__vftable = (rvBSEManagerLocal_vtbl *)&rvBSEManager::`vftable';
}

// FUNC: public: void __thiscall rvDeclEffect::DeleteSegment(int)
void __thiscall rvDeclEffect::DeleteSegment(rvDeclEffect *this, int index)
{
  int v2; // ebx
  int num; // eax
  int v5; // eax
  int v6; // esi

  v2 = index;
  if ( index >= 0 )
  {
    num = this->mSegmentTemplates.num;
    if ( index < num )
    {
      v5 = num - 1;
      this->mSegmentTemplates.num = v5;
      if ( index < v5 )
      {
        v6 = index;
        do
        {
          rvSegmentTemplate::operator=(
            (char *)&this->mSegmentTemplates.list[v6],
            (int)&this->mSegmentTemplates.list[v6 + 1]);
          ++v2;
          ++v6;
        }
        while ( v2 < this->mSegmentTemplates.num );
      }
    }
  }
}

// FUNC: public: int __thiscall rvDeclEffect::AddSegment(class rvSegmentTemplate &)
int __thiscall rvDeclEffect::AddSegment(rvDeclEffect *this, rvSegmentTemplate *st)
{
  idList<rvSegmentTemplate> *p_mSegmentTemplates; // esi
  int size; // eax

  p_mSegmentTemplates = &this->mSegmentTemplates;
  if ( !this->mSegmentTemplates.list )
    idList<rvSegmentTemplate>::Resize(&this->mSegmentTemplates, this->mSegmentTemplates.granularity);
  size = p_mSegmentTemplates->size;
  if ( p_mSegmentTemplates->num == size )
  {
    if ( !p_mSegmentTemplates->granularity )
      p_mSegmentTemplates->granularity = 16;
    idList<rvSegmentTemplate>::Resize(
      p_mSegmentTemplates,
      size
    + p_mSegmentTemplates->granularity
    - (size + p_mSegmentTemplates->granularity) % p_mSegmentTemplates->granularity);
  }
  rvSegmentTemplate::operator=((char *)&p_mSegmentTemplates->list[p_mSegmentTemplates->num], (int)st);
  return p_mSegmentTemplates->num++;
}

// FUNC: public: float __thiscall rvSegmentTemplate::GetSoundVolume(void)const
double __thiscall rvSegmentTemplate::GetSoundVolume(rvSegmentTemplate *this)
{
  return rvRandom::flrand(this->mSoundVolume.x, this->mSoundVolume.y);
}

// FUNC: public: float __thiscall rvSegmentTemplate::GetFreqShift(void)const
double __thiscall rvSegmentTemplate::GetFreqShift(rvSegmentTemplate *this)
{
  return rvRandom::flrand(this->mFreqShift.x, this->mFreqShift.y);
}

// FUNC: public: bool __thiscall rvBSE::CanInterpolate(void)
BOOL __thiscall rvBSE::CanInterpolate(rvBSE *this)
{
  return this->mCurrentTime - this->mLastTime > 0.0020000001;
}
