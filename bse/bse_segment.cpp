
// FUNC: public: void __thiscall rvSegment::ValidateSpawnRates(void)
void __thiscall rvSegment::ValidateSpawnRates(rvSegment *this)
{
  double y; // st7
  float x; // [esp+0h] [ebp-4h]

  y = this->mSecondsPerParticle.y;
  if ( y >= 0.0020000001 )
  {
    if ( y > 300.0 )
      y = 300.0;
  }
  else
  {
    y = 0.0020000001;
  }
  this->mSecondsPerParticle.y = y;
  x = this->mSecondsPerParticle.x;
  if ( x >= y )
  {
    if ( x <= 300.0 )
      this->mSecondsPerParticle.x = x;
    else
      this->mSecondsPerParticle.x = 300.0;
  }
  else
  {
    this->mSecondsPerParticle.x = y;
  }
}

// FUNC: public: void __thiscall rvSegment::GetSecondsPerParticle(class rvBSE *,class rvSegmentTemplate *,class rvParticleTemplate *)
void __thiscall rvSegment::GetSecondsPerParticle(
        rvSegment *this,
        rvBSE *effect,
        rvSegmentTemplate *st,
        rvParticleTemplate *pt)
{
  double SpawnVolume; // st7
  double x; // st7
  double y; // st7
  int mSegType; // edi
  float sta; // [esp+10h] [ebp+8h]

  if ( st->mDensity.y == 0.0 )
  {
    this->mCount = st->mCount;
  }
  else
  {
    SpawnVolume = rvParticleTemplate::GetSpawnVolume(pt, effect);
    if ( SpawnVolume >= 0.0020000001 )
    {
      if ( SpawnVolume > 1000.0 )
        SpawnVolume = 1000.0;
    }
    else
    {
      SpawnVolume = 0.0020000001;
    }
    this->mCount.x = SpawnVolume * st->mDensity.x;
    this->mCount.y = SpawnVolume * st->mDensity.y;
    sta = st->mParticleCap;
    if ( sta != 0.0 )
    {
      x = this->mCount.x;
      if ( x >= 1.0 )
      {
        if ( x > sta )
          x = sta;
      }
      else
      {
        x = 1.0;
      }
      this->mCount.x = x;
      y = this->mCount.y;
      if ( y >= 1.0 )
      {
        if ( y > sta )
          y = sta;
        this->mCount.y = y;
      }
      else
      {
        this->mCount.y = 1.0;
      }
    }
  }
  mSegType = st->mSegType;
  if ( mSegType == 2 || mSegType == 4 )
  {
    if ( this->mCount.x != 0.0 )
      this->mSecondsPerParticle.x = 1.0 / this->mCount.x;
    if ( this->mCount.y != 0.0 )
      this->mSecondsPerParticle.y = 1.0 / this->mCount.y;
    rvSegment::ValidateSpawnRates(this);
  }
}

// FUNC: public: void __thiscall rvSegment::InitTime(class rvBSE *,class rvSegmentTemplate *,float)
void __thiscall rvSegment::InitTime(rvSegment *this, rvBSE *effect, rvSegmentTemplate *st, float time)
{
  float v5; // [esp+0h] [ebp-14h]

  this->mFlags &= ~1u;
  this->mSegStartTime = rvRandom::flrand(st->mLocalStartTime.x, st->mLocalStartTime.y) + time;
  this->mSegEndTime = rvRandom::flrand(st->mLocalDuration.x, st->mLocalDuration.y) + this->mSegStartTime;
  if ( (st->mFlags & 0x10) == 0 || (effect->mFlags & 1) == 0 && !rvSegmentTemplate::GetSoundLooping(st) )
  {
    v5 = this->mSegEndTime - time;
    rvBSE::SetDuration(effect, v5);
  }
}

// FUNC: public: class rvSegmentTemplate * __thiscall rvSegment::GetSegmentTemplate(void)
rvSegmentTemplate *__thiscall rvSegment::GetSegmentTemplate(rvSegment *this)
{
  return rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
}

// FUNC: public: bool __thiscall rvSegment::GetLocked(void)
bool __thiscall rvSegment::GetLocked(rvSegment *this)
{
  int v2; // eax

  if ( rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle) )
    return ((unsigned int)rvDeclEffect::GetSegmentTemplate(
                            (rvDeclEffect *)this->mEffectDecl,
                            this->mSegmentTemplateHandle)->mFlags >> 1) & 1;
  else
    LOBYTE(v2) = 0;
  return v2;
}

// FUNC: public: void __thiscall rvSegment::InsertParticle(class rvParticle *,class rvSegmentTemplate *)
void __thiscall rvSegment::InsertParticle(rvSegment *this, rvParticle *part, rvSegmentTemplate *st)
{
  rvParticle *mUsedHead; // ebx
  rvParticle *v5; // edx
  rvParticle *v6; // esi
  float parta; // [esp+4h] [ebp+4h]

  if ( (st->mFlags & 0x100) == 0 )
  {
    ++this->mActiveCount;
    if ( (st->mFlags & 0x200) != 0 )
    {
      part->mNext = this->mUsedHead;
      this->mUsedHead = part;
    }
    else
    {
      mUsedHead = this->mUsedHead;
      v5 = mUsedHead;
      v6 = 0;
      parta = part->mEndTime;
      if ( !mUsedHead )
        goto LABEL_8;
      do
      {
        if ( parta <= (double)v5->mEndTime )
          break;
        v6 = v5;
        v5 = v5->mNext;
      }
      while ( v5 );
      if ( v6 )
      {
        part->mNext = v5;
        v6->mNext = part;
      }
      else
      {
LABEL_8:
        part->mNext = mUsedHead;
        this->mUsedHead = part;
      }
    }
  }
}

// FUNC: public: class rvParticle * __thiscall rvSegment::SpawnParticle(class rvBSE *,class rvSegmentTemplate *,float,class idVec3 const &,class idMat3 const &)
rvSegmentTemplate *__thiscall rvSegment::SpawnParticle(
        rvSegment *this,
        rvBSE *effect,
        rvSegmentTemplate *st,
        float birthTime,
        const idVec3 *initOffset,
        const idMat3 *initAxis)
{
  rvSegmentTemplate *result; // eax
  rvParticle *mParticles; // esi

  result = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  if ( result )
  {
    if ( (result->mFlags & 0x100) != 0 )
    {
      mParticles = this->mParticles;
    }
    else
    {
      mParticles = this->mFreeHead;
      if ( !mParticles )
        return (rvSegmentTemplate *)mParticles;
      this->mFreeHead = mParticles->mNext;
    }
    if ( mParticles )
    {
      ((void (__thiscall *)(rvParticle *, rvBSE *, rvSegment *, _DWORD, _DWORD, const idVec3 *, const idMat3 *))mParticles->FinishSpawn)(
        mParticles,
        effect,
        this,
        LODWORD(birthTime),
        LODWORD(birthTime),
        initOffset,
        initAxis);
      rvSegment::InsertParticle(this, mParticles, st);
    }
    return (rvSegmentTemplate *)mParticles;
  }
  return result;
}

// FUNC: public: float __thiscall rvSegment::AttenuateDuration(class rvBSE *,class rvSegmentTemplate *)
double __thiscall rvSegment::AttenuateDuration(rvSegment *this, rvBSE *effect, rvSegmentTemplate *st)
{
  return rvBSE::GetAttenuation(effect, st) * (this->mSegEndTime - this->mSegStartTime);
}

// FUNC: public: void __thiscall rvSegment::PlayEffect(class rvBSE *,class rvSegmentTemplate *)
void __thiscall rvSegment::PlayEffect(rvSegment *this, rvBSE *effect, rvSegmentTemplate *st)
{
  int v3; // eax

  v3 = rvRandom::irand(0, st->mNumEffects - 1);
  game->PlayEffect(
    game,
    st->mEffects[v3],
    &effect->mCurrentOrigin,
    &effect->mCurrentAxis,
    0,
    &vec3_origin,
    0,
    EC_IGNORE,
    &vec4_one);
}

// FUNC: public: void __thiscall rvSegment::RefreshParticles(class rvBSE *,class rvSegmentTemplate *)
void __thiscall rvSegment::RefreshParticles(rvSegment *this, rvBSE *effect, rvSegmentTemplate *st)
{
  rvParticle *mUsedHead; // ecx
  rvParticle *mNext; // esi

  if ( rvParticleTemplate::UsesEndOrigin(&st->mParticleTemplate) )
  {
    mUsedHead = this->mUsedHead;
    if ( mUsedHead )
    {
      do
      {
        mNext = mUsedHead->mNext;
        mUsedHead->Refresh(mUsedHead, effect, st, &st->mParticleTemplate);
        mUsedHead = mNext;
      }
      while ( mNext );
    }
  }
}

// FUNC: public: void __thiscall rvSegment::Handle(class rvBSE *,float)
void __thiscall rvSegment::Handle(rvSegment *this, rvBSE *effect, float time)
{
  rvSegmentTemplate *SegmentTemplate; // ecx

  SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  if ( SegmentTemplate && time >= (double)this->mSegStartTime )
  {
    switch ( SegmentTemplate->mSegType )
    {
      case 2:
      case 3:
        if ( (effect->mFlags & 4) != 0 )
          rvSegment::RefreshParticles(this, effect, SegmentTemplate);
        break;
      case 5:
        rvBSE::UpdateSoundEmitter(effect, SegmentTemplate, this);
        break;
      case 7:
        if ( (SegmentTemplate->mFlags & 1) != 0 )
          rvSegment::HandleLight(this, effect, SegmentTemplate, time);
        break;
      default:
        return;
    }
  }
}

// FUNC: public: float __thiscall rvSegment::EvaluateCost(void)
double __thiscall rvSegment::EvaluateCost(rvSegment *this)
{
  rvSegmentTemplate *SegmentTemplate; // eax
  double result; // st7
  int mSegType; // ecx
  rvParticleTemplate *p_mParticleTemplate; // edi
  float cost; // [esp+0h] [ebp-10h]
  float baseCost; // [esp+Ch] [ebp-4h]

  SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  if ( !SegmentTemplate || (SegmentTemplate->mFlags & 1) == 0 )
    return 0.0;
  mSegType = SegmentTemplate->mSegType;
  result = rvSegment::mSegmentBaseCosts[mSegType];
  p_mParticleTemplate = &SegmentTemplate->mParticleTemplate;
  if ( SegmentTemplate->mParticleTemplate.mType )
  {
    cost = (float)this->mActiveCount;
    baseCost = rvSegment::mSegmentBaseCosts[mSegType];
    result = rvParticleTemplate::CostTrail(&SegmentTemplate->mParticleTemplate, cost) + baseCost;
    if ( (p_mParticleTemplate->mFlags & 0x200) != 0 )
      return result + (double)this->mActiveCount * 80.0;
  }
  return result;
}

// FUNC: public: void __thiscall rvSegment::UpdateSimpleParticles(float)
void __thiscall rvSegment::UpdateSimpleParticles(rvSegment *this, float time)
{
  rvParticle *mUsedHead; // edx
  rvParticle *mNext; // eax
  rvParticle *mFreeHead; // edi

  mUsedHead = this->mUsedHead;
  if ( mUsedHead )
  {
    do
    {
      if ( mUsedHead->mEndTime - 0.0020000001 > time )
        break;
      mNext = mUsedHead->mNext;
      mFreeHead = this->mFreeHead;
      this->mUsedHead = mNext;
      mUsedHead->mNext = mFreeHead;
      --this->mActiveCount;
      this->mFreeHead = mUsedHead;
      mUsedHead = mNext;
    }
    while ( mNext );
  }
}

// FUNC: public: void __thiscall rvSegment::UpdateElectricityParticles(float)
void __thiscall rvSegment::UpdateElectricityParticles(rvSegment *this, float time)
{
  rvParticle *mUsedHead; // esi

  mUsedHead = this->mUsedHead;
  for ( this->mActiveCount = 0; mUsedHead; mUsedHead = mUsedHead->mNext )
    this->mActiveCount += ((int (__thiscall *)(rvParticle *, _DWORD))mUsedHead->Update)(mUsedHead, LODWORD(time));
}

// FUNC: public: void __thiscall rvSegment::Rewind(class rvBSE *)
void __thiscall rvSegment::Rewind(rvSegment *this, rvBSE *effect)
{
  double v2; // st7

  if ( effect->mDuration == this->mSegEndTime - this->mSegStartTime )
  {
    v2 = this->mSegStartTime - (effect->mDuration + effect->mDuration);
    this->mSegStartTime = v2;
    this->mLastTime = v2;
  }
}

// FUNC: public: void __thiscall rvSegment::Advance(class rvBSE *)
void __thiscall rvSegment::Advance(rvSegment *this, rvBSE *effect)
{
  double v2; // st7

  v2 = effect->mDuration + this->mSegStartTime;
  this->mSegStartTime = v2;
  this->mLastTime = v2;
}

// FUNC: public: bool __thiscall rvSegment::Active(void)
bool __thiscall rvSegment::Active(rvSegment *this)
{
  rvSegmentTemplate *SegmentTemplate; // eax

  SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  if ( SegmentTemplate && (SegmentTemplate->mFlags & 4) != 0 && this->mActiveCount )
    return SegmentTemplate->mFlags & 1;
  else
    return 0;
}

// FUNC: public: void __thiscall rvParticle::DoRenderBurnTrail(class rvBSE *,class idMat3 const &,struct srfTriangles_s *,float)
void __thiscall rvParticle::DoRenderBurnTrail(
        rvParticle *this,
        rvBSE *effect,
        const idMat3 *view,
        srfTriangles_s *tri,
        float time)
{
  int mTrailCount; // ecx
  int v7; // edi
  double v9; // st7
  float v10; // [esp+0h] [ebp-1Ch]
  int i; // [esp+14h] [ebp-8h]
  float delta; // [esp+18h] [ebp-4h]
  float tria; // [esp+28h] [ebp+Ch]

  mTrailCount = this->mTrailCount;
  if ( mTrailCount )
  {
    if ( this->mTrailTime != 0.0 )
    {
      v7 = 1;
      i = 1;
      delta = this->mTrailTime / (double)mTrailCount;
      if ( mTrailCount + 1 > 1 )
      {
        do
        {
          v9 = time - (double)i * delta;
          tria = v9;
          if ( v9 >= this->mStartTime && tria < (double)this->mEndTime )
          {
            v10 = (double)(this->mTrailCount - v7) / (double)this->mTrailCount;
            ((void (__thiscall *)(rvParticle *, rvBSE *, const idMat3 *, srfTriangles_s *, _DWORD, _DWORD))this->Render)(
              this,
              effect,
              view,
              tri,
              LODWORD(tria),
              LODWORD(v10));
          }
          i = ++v7;
        }
        while ( v7 < this->mTrailCount + 1 );
      }
    }
  }
}

// FUNC: public: void __thiscall rvSegment::RenderMotion(class rvBSE *,struct renderEffect_s const *,class rvRenderModelBSE *,class rvParticleTemplate *,float)
void __thiscall rvSegment::RenderMotion(
        rvSegment *this,
        rvBSE *effect,
        const renderEffect_s *owner,
        rvRenderModelBSE *model,
        rvParticleTemplate *pt,
        float time)
{
  int v7; // esi
  srfTriangles_s *v8; // edi
  rvParticle *mUsedHead; // esi
  const idMaterial *surf_4; // [esp+20h] [ebp-Ch]

  v7 = this->mActiveCount * ((int)ceil(pt->mTrailCount.y) + 1);
  v8 = R_AllocStaticTriSurf();
  R_AllocStaticTriSurfVerts(v8, 2 * v7 + 2);
  R_AllocStaticTriSurfIndexes(v8, 12 * v7);
  mUsedHead = this->mUsedHead;
  for ( surf_4 = pt->mTrailMaterial; mUsedHead; mUsedHead = mUsedHead->mNext )
    ((void (__thiscall *)(rvParticle *, rvBSE *, srfTriangles_s *, const renderEffect_s *, _DWORD))mUsedHead->RenderMotion)(
      mUsedHead,
      effect,
      v8,
      owner,
      LODWORD(time));
  R_BoundTriSurf(v8);
  ((void (__thiscall *)(rvRenderModelBSE *, _DWORD, const idMaterial *, srfTriangles_s *, _DWORD))model->AddSurface)(
    model,
    0,
    surf_4,
    v8,
    0);
}

// FUNC: public: void __thiscall rvSegment::RenderTrail(class rvBSE *,struct renderEffect_s const *,class rvRenderModelBSE *,float)
void __thiscall rvSegment::RenderTrail(
        rvSegment *this,
        rvBSE *effect,
        const renderEffect_s *owner,
        rvRenderModelBSE *model,
        float time)
{
  rvSegmentTemplate *SegmentTemplate; // eax
  rvParticleTemplate *p_mParticleTemplate; // esi

  SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  if ( SegmentTemplate )
  {
    p_mParticleTemplate = &SegmentTemplate->mParticleTemplate;
    if ( (int)ceil(SegmentTemplate->mParticleTemplate.mTrailCount.y) != -1
      && p_mParticleTemplate->mTrailTime.y >= 0.0020000001
      && p_mParticleTemplate->mTrailType == 2 )
    {
      rvSegment::RenderMotion(this, effect, owner, model, p_mParticleTemplate, time);
    }
  }
}

// FUNC: public: void __thiscall rvSegment::Init(class rvBSE *,class rvDeclEffect const *,int,float)
void __thiscall rvSegment::Init(
        rvSegment *this,
        rvBSE *effect,
        rvDeclEffect *effectDecl,
        int segmentTemplateHandle,
        float time)
{
  rvSegmentTemplate *SegmentTemplate; // edi

  this->mFlags = 0;
  this->mEffectDecl = effectDecl;
  this->mSegmentTemplateHandle = segmentTemplateHandle;
  SegmentTemplate = rvDeclEffect::GetSegmentTemplate(effectDecl, segmentTemplateHandle);
  if ( SegmentTemplate )
  {
    this->mLastTime = time;
    this->mActiveCount = 0;
    this->mSecondsPerParticle.y = 0.0;
    this->mSecondsPerParticle.x = 0.0;
    this->mCount.x = 1.0;
    this->mCount.y = 1.0;
    this->mSoundVolume = 0.0;
    this->mParticles = 0;
    this->mFreqShift = 1.0;
    rvSegment::InitTime(this, effect, SegmentTemplate, effect->mStartTime);
    rvSegment::GetSecondsPerParticle(this, effect, SegmentTemplate, &SegmentTemplate->mParticleTemplate);
    SegmentTemplate->mBSEEffect = effect;
  }
}

// FUNC: public: void __thiscall rvSegment::AddToParticleCount(class rvBSE *,int,int,float)
void __thiscall rvSegment::AddToParticleCount(rvSegment *this, rvBSE *effect, int count, int loopCount, float duration)
{
  rvSegmentTemplate *SegmentTemplate; // eax
  int v7; // [esp+Ch] [ebp-4h]

  SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  if ( SegmentTemplate )
  {
    if ( SegmentTemplate->mParticleTemplate.mDuration.y > (double)duration )
      duration = SegmentTemplate->mParticleTemplate.mDuration.y;
    v7 = (int)ceil((duration + 0.016000001) / this->mSecondsPerParticle.y);
    this->mParticleCount += count * (v7 + 1);
    this->mLoopParticleCount += loopCount * (v7 + 1);
  }
}

// FUNC: public: void __thiscall rvSegment::CalcTrailCounts(class rvBSE *,class rvSegmentTemplate *,class rvParticleTemplate *,float)
void __thiscall rvSegment::CalcTrailCounts(
        rvSegment *this,
        rvBSE *effect,
        rvSegmentTemplate *st,
        rvParticleTemplate *pt,
        float duration)
{
  int mTrailSegmentIndex; // eax

  mTrailSegmentIndex = st->mTrailSegmentIndex;
  if ( mTrailSegmentIndex >= 0 )
    rvSegment::AddToParticleCount(
      &effect->mSegments.list[mTrailSegmentIndex],
      effect,
      this->mParticleCount,
      this->mLoopParticleCount,
      duration);
}

// FUNC: public: void __thiscall rvSegment::CalcCounts(class rvBSE *,float)
void __thiscall rvSegment::CalcCounts(rvSegment *this, rvBSE *effect, float time)
{
  rvSegment *v3; // ebp
  rvSegmentTemplate *SegmentTemplate; // eax
  rvSegmentTemplate *v5; // ebx
  int mSegType; // eax
  int mType; // ecx
  int v8; // esi
  int v9; // edi
  double y; // st7
  double v11; // st7
  int v12; // ebp
  int v13; // eax
  int v14; // eax
  float _X; // [esp+0h] [ebp-30h]
  float _Xa; // [esp+0h] [ebp-30h]
  float _Xb; // [esp+0h] [ebp-30h]
  float _Xc; // [esp+0h] [ebp-30h]
  float particleMaxDuration; // [esp+18h] [ebp-18h]
  float effectMinDuration; // [esp+1Ch] [ebp-14h]
  float duration; // [esp+24h] [ebp-Ch]
  rvDeclEffect *mEffectDecl; // [esp+28h] [ebp-8h]

  v3 = this;
  mEffectDecl = (rvDeclEffect *)this->mEffectDecl;
  SegmentTemplate = rvDeclEffect::GetSegmentTemplate(mEffectDecl, this->mSegmentTemplateHandle);
  v5 = SegmentTemplate;
  if ( SegmentTemplate )
  {
    mSegType = SegmentTemplate->mSegType;
    if ( mSegType != 4 )
    {
      mType = v5->mParticleTemplate.mType;
      if ( mType )
      {
        v8 = 0;
        particleMaxDuration = v5->mParticleTemplate.mDuration.y + 0.016000001;
        v9 = 0;
        duration = 0.0;
        effectMinDuration = mEffectDecl->mMinDuration;
        switch ( mSegType )
        {
          case 2:
            if ( mType == 9 )
            {
              v8 = 1;
              v9 = 1;
            }
            else
            {
              y = particleMaxDuration;
              if ( particleMaxDuration > (double)v5->mLocalDuration.y )
                y = v5->mLocalDuration.y;
              v11 = y + 0.016000001;
              duration = v11;
              _X = v11 / v3->mSecondsPerParticle.y;
              v9 = (int)ceilf(_X) + 1;
              v8 = v9;
              if ( effectMinDuration < (double)particleMaxDuration )
              {
                _Xa = (double)v9 / effectMinDuration * particleMaxDuration;
                v8 = (int)ceilf(_Xa) + 1;
              }
            }
            break;
          case 3:
            if ( mType == 9 )
            {
              v8 = 1;
              v9 = 1;
            }
            else
            {
              v9 = (int)ceilf(v3->mCount.y);
              v8 = v9;
              if ( effectMinDuration != 0.0
                && (v5->mFlags & 0x20) == 0
                && effectMinDuration < (double)particleMaxDuration )
              {
                _Xb = particleMaxDuration / effectMinDuration;
                v8 = v9 * ((int)ceilf(_Xb) + 1) + 1;
              }
            }
            break;
          case 4:
            break;
          case 6:
          case 7:
            v9 = 1;
            v8 = 1;
            break;
          default:
            v9 = 0;
            v8 = 0;
            break;
        }
        if ( v5->mSegType != 4 )
        {
          v3->mParticleCount = v9;
          v3->mLoopParticleCount = v8;
          if ( (v5->mFlags & 4) != 0 )
          {
            if ( !v9 || !v8 )
            {
              v12 = *(_DWORD *)common.type;
              v13 = (int)mEffectDecl->base->GetName(mEffectDecl->base);
              (*(void (**)(netadrtype_t, const char *, ...))(v12 + 136))(
                common.type,
                "^4BSE:^1 '%s'\nSegment with no particles for effect",
                v13);
              v3 = this;
            }
            v14 = v5->mSegType;
            if ( v14 == 2 || v14 == 3 )
              rvSegment::CalcTrailCounts(v3, effect, v5, &v5->mParticleTemplate, duration);
          }
        }
        if ( (effect->mFlags & 1) == 0 )
        {
          _Xc = v3->mSegEndTime - time + v5->mParticleTemplate.mDuration.y;
          rvBSE::SetDuration(effect, _Xc);
        }
        if ( bse_debug.internalVar->integerValue == 2 )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "BSE: Segment %s: Count: %d Looping: %d\n",
            rvBSEManagerLocal::mSegmentNames[v5->mSegType],
            v9,
            v8);
      }
    }
  }
}

// FUNC: public: void __thiscall rvSegment::ResetTime(class rvBSE *,float)
void __thiscall rvSegment::ResetTime(rvSegment *this, rvBSE *effect, float time)
{
  rvSegmentTemplate *SegmentTemplate; // eax

  SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  if ( SegmentTemplate )
  {
    if ( (SegmentTemplate->mFlags & 0x20) == 0 )
      rvSegment::InitTime(this, effect, SegmentTemplate, time);
  }
}

// FUNC: public: __thiscall rvSegment::~rvSegment(void)
void __thiscall rvSegment::~rvSegment(rvSegment *this)
{
  rvSegmentTemplate *SegmentTemplate; // eax
  rvParticle *mParticles; // ecx
  float *p_z; // eax

  if ( this->mParticles )
  {
    SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
    if ( SegmentTemplate )
    {
      switch ( SegmentTemplate->mParticleTemplate.mType )
      {
        case 3:
        case 5:
        case 7:
        case 9:
          mParticles = this->mParticles;
          if ( !mParticles )
            goto LABEL_10;
          p_z = &mParticles[-1].mOffsetEnv.mEnd.z;
          if ( !LODWORD(mParticles[-1].mOffsetEnv.mEnd.z) )
            goto LABEL_9;
          goto LABEL_6;
        default:
          mParticles = this->mParticles;
          if ( !mParticles )
            goto LABEL_10;
          p_z = &mParticles[-1].mOffsetEnv.mEnd.z;
          if ( LODWORD(mParticles[-1].mOffsetEnv.mEnd.z) )
          {
LABEL_6:
            ((void (__thiscall *)(rvParticle *, int))mParticles->~rvParticle)(mParticles, 3);
            this->mParticles = 0;
          }
          else
          {
LABEL_9:
            Memory::Free(p_z);
LABEL_10:
            this->mParticles = 0;
          }
          break;
      }
    }
  }
}

// FUNC: public: void __thiscall rvSegment::SpawnParticles(class rvBSE *,class rvSegmentTemplate *,float,int)
void __thiscall rvSegment::SpawnParticles(
        rvSegment *this,
        rvBSE *effect,
        rvSegmentTemplate *st,
        float birthTime,
        int count)
{
  rvSegmentTemplate *SegmentTemplate; // eax
  rvParticle *mParticles; // esi
  float v8; // [esp+0h] [ebp-20h]
  int i; // [esp+1Ch] [ebp-4h]

  if ( count > bse_maxParticles.internalVar->integerValue )
    count = bse_maxParticles.internalVar->integerValue;
  for ( i = 0; i < count; ++i )
  {
    SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
    if ( SegmentTemplate )
    {
      if ( (SegmentTemplate->mFlags & 0x100) != 0 )
      {
        mParticles = this->mParticles;
        goto LABEL_9;
      }
      mParticles = this->mFreeHead;
      if ( mParticles )
      {
        this->mFreeHead = mParticles->mNext;
LABEL_9:
        if ( mParticles )
        {
          v8 = (double)i / (double)count;
          ((void (__thiscall *)(rvParticle *, rvBSE *, rvSegment *, _DWORD, _DWORD, idVec3 *, idMat3 *))mParticles->FinishSpawn)(
            mParticles,
            effect,
            this,
            LODWORD(birthTime),
            LODWORD(v8),
            &vec3_origin,
            &mat3_identity);
          rvSegment::InsertParticle(this, mParticles, st);
        }
      }
    }
  }
}

// FUNC: public: float __thiscall rvSegment::AttenuateInterval(class rvBSE *,class rvSegmentTemplate *)
double __thiscall rvSegment::AttenuateInterval(rvSegment *this, rvBSE *effect, rvSegmentTemplate *st)
{
  double Attenuation; // st7
  float rate; // [esp+0h] [ebp-8h]

  rate = (this->mSecondsPerParticle.y - this->mSecondsPerParticle.x) * bse_scale.internalVar->floatValue
       + this->mSecondsPerParticle.x;
  if ( rate >= (double)this->mSecondsPerParticle.y )
  {
    if ( rate > (double)this->mSecondsPerParticle.x )
      rate = this->mSecondsPerParticle.x;
  }
  else
  {
    rate = this->mSecondsPerParticle.y;
  }
  if ( (st->mFlags & 0x40) == 0 )
    return rate;
  Attenuation = rvBSE::GetAttenuation(effect, st);
  if ( (st->mFlags & 0x80) != 0 )
    Attenuation = 1.0 - Attenuation;
  if ( Attenuation >= 0.0020000001 )
    return rate / Attenuation;
  else
    return 1.0;
}

// FUNC: public: float __thiscall rvSegment::AttenuateCount(class rvBSE *,class rvSegmentTemplate *,float,float)
double __thiscall rvSegment::AttenuateCount(
        rvSegment *this,
        rvBSE *effect,
        rvSegmentTemplate *st,
        float min,
        float max)
{
  double v5; // st7
  double Attenuation; // st7
  float v8; // [esp+0h] [ebp-8h]
  float count; // [esp+4h] [ebp-4h]

  v8 = (max - min) * bse_scale.internalVar->floatValue + min;
  v5 = rvRandom::flrand(min, v8);
  count = v5;
  if ( v5 >= min )
  {
    if ( count > (double)max )
      count = max;
  }
  else
  {
    count = min;
  }
  if ( (st->mFlags & 0x40) == 0 )
    return count;
  Attenuation = rvBSE::GetAttenuation(effect, st);
  if ( (st->mFlags & 0x80) != 0 )
    Attenuation = 1.0 - Attenuation;
  return Attenuation * count;
}

// FUNC: public: void __thiscall rvSegment::UpdateGenericParticles(class rvBSE *,class rvSegmentTemplate *,float)
void __thiscall rvSegment::UpdateGenericParticles(rvSegment *this, rvBSE *effect, rvSegmentTemplate *st, float time)
{
  bool v6; // al
  rvParticle *mUsedHead; // esi
  bool v8; // al
  bool v10; // bl
  int mTrailSegmentIndex; // eax
  rvParticle_vtbl *v12; // edx
  bool smoker; // [esp+Bh] [ebp-9h]
  rvParticle *prev; // [esp+10h] [ebp-4h]
  rvBSE *effecta; // [esp+18h] [ebp+4h]
  bool next; // [esp+1Ch] [ebp+8h]

  v6 = rvSegmentTemplate::GetSmoker(st);
  mUsedHead = this->mUsedHead;
  smoker = v6;
  v8 = (st->mFlags & 0x20) != 0;
  next = v8;
  prev = 0;
  if ( mUsedHead )
  {
    while ( 1 )
    {
      v10 = 0;
      effecta = (rvBSE *)mUsedHead->mNext;
      if ( v8 )
      {
        rvParticle::RunPhysics(mUsedHead, effect, st, time);
        if ( (effect->mFlags & 8) != 0 )
          goto LABEL_9;
      }
      else
      {
        if ( mUsedHead->mEndTime - 0.0020000001 <= time )
        {
          rvParticle::CheckTimeoutEffect(mUsedHead, effect, st, time);
LABEL_9:
          v10 = 1;
          goto LABEL_10;
        }
        v10 = rvParticle::RunPhysics(mUsedHead, effect, st, time);
      }
LABEL_10:
      if ( (effect->mFlags & 8) != 0 && (mUsedHead->mFlags & 0x200000) == 0 )
        v10 = 1;
      if ( smoker )
      {
        mTrailSegmentIndex = st->mTrailSegmentIndex;
        if ( mTrailSegmentIndex >= 0 )
          rvParticle::EmitSmokeParticles(mUsedHead, effect, &effect->mSegments.list[mTrailSegmentIndex], time);
      }
      if ( v10 )
      {
        if ( prev )
          prev->mNext = (rvParticle *)effecta;
        else
          this->mUsedHead = (rvParticle *)effecta;
        --this->mActiveCount;
        v12 = mUsedHead->__vftable;
        mUsedHead->mNext = this->mFreeHead;
        v12->Destroy(mUsedHead);
        this->mFreeHead = mUsedHead;
      }
      else
      {
        prev = mUsedHead;
      }
      mUsedHead = (rvParticle *)effecta;
      if ( !effecta )
        return;
      v8 = next;
    }
  }
}

// FUNC: public: bool __thiscall rvSegment::UpdateParticles(class rvBSE *,float)
bool __thiscall rvSegment::UpdateParticles(rvSegment *this, rvBSE *effect, float time)
{
  rvSegmentTemplate *SegmentTemplate; // ebx

  SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  if ( !SegmentTemplate )
    return 0;
  rvSegment::Handle(this, effect, time);
  if ( (effect->mFlags & 8) != 0 || (SegmentTemplate->mFlags & 0x200) != 0 )
    rvSegment::UpdateGenericParticles(this, effect, SegmentTemplate, time);
  else
    rvSegment::UpdateSimpleParticles(this, time);
  if ( SegmentTemplate->mParticleTemplate.mType == 7 )
    rvSegment::UpdateElectricityParticles(this, time);
  if ( com_debugHudActive )
  {
    dword_1137DDB0 += this->mActiveCount;
    if ( this->mUsedHead )
      dword_1137DDB4 += rvSegmentTemplate::GetTexelCount(SegmentTemplate);
  }
  return this->mUsedHead != 0;
}

// FUNC: public: void __thiscall rvSegment::Render(class rvBSE *,struct renderEffect_s const *,class rvRenderModelBSE *,float)
void __thiscall rvSegment::Render(
        rvSegment *this,
        rvBSE *effect,
        const renderEffect_s *owner,
        rvRenderModelBSE *model,
        float time)
{
  rvSegmentTemplate *SegmentTemplate; // eax
  rvSegmentTemplate *v7; // esi
  int v8; // esi
  const char *DeclName; // eax
  srfTriangles_s *v10; // edi
  double v11; // st7
  double v12; // st6
  double v13; // st5
  rvParticle *mUsedHead; // esi
  float v15; // [esp+14h] [ebp-9Ch]
  float v16; // [esp+18h] [ebp-98h]
  float v17; // [esp+18h] [ebp-98h]
  rvSegmentTemplate *st; // [esp+24h] [ebp-8Ch]
  idMat3 view; // [esp+3Ch] [ebp-74h] BYREF
  modelSurface_s surf; // [esp+60h] [ebp-50h]
  float modelMatrix[16]; // [esp+70h] [ebp-40h] BYREF

  SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  v7 = SegmentTemplate;
  st = SegmentTemplate;
  if ( SegmentTemplate )
  {
    if ( (unsigned int)((this->mActiveCount * SegmentTemplate->mParticleTemplate.mVertexCount) << 6) <= 0x100000 )
    {
      v10 = R_AllocStaticTriSurf();
      R_AllocStaticTriSurfVerts(v10, this->mActiveCount * v7->mParticleTemplate.mVertexCount);
      R_AllocStaticTriSurfIndexes(v10, v7->mParticleTemplate.mIndexCount * this->mActiveCount);
      surf.shader = v7->mParticleTemplate.mMaterial;
      R_AxisToModelMatrix(&owner->axis, &owner->origin, modelMatrix);
      R_GlobalVectorToLocal(modelMatrix, &effect->mViewAxis.mat[1], &view.mat[1]);
      R_GlobalVectorToLocal(modelMatrix, &effect->mViewAxis.mat[2], &view.mat[2]);
      v11 = effect->mViewOrg.x - owner->origin.x;
      v15 = effect->mViewOrg.y - owner->origin.y;
      v16 = effect->mViewOrg.z - owner->origin.z;
      v12 = v15 * owner->axis.mat[0].y + v16 * owner->axis.mat[0].z + owner->axis.mat[0].x * v11;
      v13 = v15 * owner->axis.mat[1].y + v16 * owner->axis.mat[1].z + owner->axis.mat[1].x * v11;
      mUsedHead = this->mUsedHead;
      v17 = v15 * owner->axis.mat[2].y + v16 * owner->axis.mat[2].z + owner->axis.mat[2].x * v11;
      view.mat[0].z = v17;
      view.mat[0].x = v12;
      for ( view.mat[0].y = v13; mUsedHead; mUsedHead = mUsedHead->mNext )
      {
        if ( (st->mFlags & 0x20) != 0 )
          mUsedHead->mEndTime = time + 1.0;
        if ( v10->numVerts + st->mParticleTemplate.mVertexCount > v10->numAllocedVerts
          || st->mParticleTemplate.mIndexCount + v10->numIndexes > v10->numAllocedIndices )
        {
          break;
        }
        if ( ((unsigned __int8 (__thiscall *)(rvParticle *, rvBSE *, idMat3 *, srfTriangles_s *, _DWORD, int))mUsedHead->Render)(
               mUsedHead,
               effect,
               &view,
               v10,
               LODWORD(time),
               1065353216) )
        {
          if ( st->mParticleTemplate.mTrailType == 1 )
            ((void (__thiscall *)(rvParticle *, rvBSE *, idMat3 *, srfTriangles_s *, _DWORD))mUsedHead->RenderBurnTrail)(
              mUsedHead,
              effect,
              &view,
              v10,
              LODWORD(time));
        }
      }
      R_BoundTriSurf(v10);
      ((void (__thiscall *)(rvRenderModelBSE *, _DWORD, const idMaterial *, srfTriangles_s *, _DWORD))model->AddSurface)(
        model,
        0,
        surf.shader,
        v10,
        0);
    }
    else
    {
      v8 = *(_DWORD *)common.type;
      DeclName = rvBSE::GetDeclName(effect);
      (*(void (**)(netadrtype_t, const char *, ...))(v8 + 124))(
        common.type,
        "^4BSE:^1 '%s'\nMore than a meg of vertex data needed",
        DeclName);
    }
  }
}

// FUNC: public: class rvParticle * __thiscall rvSegment::InitParticleArray(class rvBSE *)
rvParticle *__thiscall rvSegment::InitParticleArray(rvSegment *this, rvBSE *effect)
{
  rvParticle *v3; // edi
  rvSegmentTemplate *SegmentTemplate; // ebx
  int mLoopParticleCount; // esi
  const char *DeclName; // eax
  int *v9; // eax
  int *v10; // eax
  int *v11; // eax
  int *v12; // eax
  int *v13; // eax
  int *v14; // eax
  int *v15; // eax
  int *v16; // eax
  int *v17; // eax
  int v18; // esi
  int i; // ebx
  int v20; // eax
  int integerValue; // [esp-8h] [ebp-28h]
  rvBSE *effecta; // [esp+24h] [ebp+4h]

  v3 = 0;
  SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
  if ( !SegmentTemplate )
    return 0;
  if ( (effect->mFlags & 1) != 0 )
    mLoopParticleCount = this->mLoopParticleCount;
  else
    mLoopParticleCount = this->mParticleCount;
  if ( mLoopParticleCount > bse_maxParticles.internalVar->integerValue )
  {
    integerValue = bse_maxParticles.internalVar->integerValue;
    effecta = *(rvBSE **)common.type;
    DeclName = rvBSE::GetDeclName(effect);
    ((void (*)(netadrtype_t, const char *, ...))LODWORD(effecta->mViewOrg.z))(
      common.type,
      "^4BSE:^1 '%s'\nMore than %d particles required (%d)",
      DeclName,
      integerValue,
      mLoopParticleCount);
    mLoopParticleCount = bse_maxParticles.internalVar->integerValue;
  }
  if ( mLoopParticleCount )
  {
    switch ( SegmentTemplate->mParticleTemplate.mType )
    {
      case 2:
        v9 = (int *)Memory::Allocate(416 * mLoopParticleCount + 4);
        if ( !v9 )
          goto LABEL_28;
        v3 = (rvParticle *)(v9 + 1);
        *v9 = mLoopParticleCount;
        `eh vector constructor iterator'(
          v9 + 1,
          0x1A0u,
          mLoopParticleCount,
          (void (__thiscall *)(void *))rvLineParticle::rvLineParticle,
          (void (__thiscall *)(void *))rvLineParticle::~rvLineParticle);
        break;
      case 3:
        v10 = (int *)Memory::Allocate(456 * mLoopParticleCount + 4);
        if ( !v10 )
          goto LABEL_28;
        v3 = (rvParticle *)(v10 + 1);
        *v10 = mLoopParticleCount;
        `eh vector constructor iterator'(
          v10 + 1,
          0x1C8u,
          mLoopParticleCount,
          (void (__thiscall *)(void *))rvOrientedParticle::rvOrientedParticle,
          (void (__thiscall *)(void *))rvLineParticle::~rvLineParticle);
        break;
      case 4:
        v11 = (int *)Memory::Allocate(400 * mLoopParticleCount + 4);
        if ( !v11 )
          goto LABEL_28;
        v3 = (rvParticle *)(v11 + 1);
        *v11 = mLoopParticleCount;
        `eh vector constructor iterator'(
          v11 + 1,
          0x190u,
          mLoopParticleCount,
          (void (__thiscall *)(void *))rvDecalParticle::rvDecalParticle,
          (void (__thiscall *)(void *))rvLineParticle::~rvLineParticle);
        break;
      case 5:
        v12 = (int *)Memory::Allocate(456 * mLoopParticleCount + 4);
        if ( !v12 )
          goto LABEL_28;
        v3 = (rvParticle *)(v12 + 1);
        *v12 = mLoopParticleCount;
        `eh vector constructor iterator'(
          v12 + 1,
          0x1C8u,
          mLoopParticleCount,
          (void (__thiscall *)(void *))rvModelParticle::rvModelParticle,
          (void (__thiscall *)(void *))rvLineParticle::~rvLineParticle);
        break;
      case 6:
        v13 = (int *)Memory::Allocate(616 * mLoopParticleCount + 4);
        if ( !v13 )
          goto LABEL_28;
        v3 = (rvParticle *)(v13 + 1);
        *v13 = mLoopParticleCount;
        `eh vector constructor iterator'(
          v13 + 1,
          0x268u,
          mLoopParticleCount,
          (void (__thiscall *)(void *))rvLightParticle::rvLightParticle,
          (void (__thiscall *)(void *))rvLightParticle::~rvLightParticle);
        break;
      case 7:
        v14 = (int *)Memory::Allocate(476 * mLoopParticleCount + 4);
        if ( !v14 )
          goto LABEL_28;
        v3 = (rvParticle *)(v14 + 1);
        *v14 = mLoopParticleCount;
        `eh vector constructor iterator'(
          v14 + 1,
          0x1DCu,
          mLoopParticleCount,
          (void (__thiscall *)(void *))rvElectricityParticle::rvElectricityParticle,
          (void (__thiscall *)(void *))rvLineParticle::~rvLineParticle);
        break;
      case 8:
        v15 = (int *)Memory::Allocate(360 * mLoopParticleCount + 4);
        if ( !v15 )
          goto LABEL_28;
        v3 = (rvParticle *)(v15 + 1);
        *v15 = mLoopParticleCount;
        `eh vector constructor iterator'(
          v15 + 1,
          0x168u,
          mLoopParticleCount,
          (void (__thiscall *)(void *))rvLinkedParticle::rvLinkedParticle,
          (void (__thiscall *)(void *))rvLineParticle::~rvLineParticle);
        break;
      case 9:
        v16 = (int *)Memory::Allocate(396 * mLoopParticleCount + 4);
        if ( !v16 )
          goto LABEL_28;
        v3 = (rvParticle *)(v16 + 1);
        *v16 = mLoopParticleCount;
        `eh vector constructor iterator'(
          v16 + 1,
          0x18Cu,
          mLoopParticleCount,
          (void (__thiscall *)(void *))rvDebrisParticle::rvDebrisParticle,
          (void (__thiscall *)(void *))rvLineParticle::~rvLineParticle);
        break;
      default:
        v17 = (int *)Memory::Allocate(400 * mLoopParticleCount + 4);
        if ( v17 )
        {
          v3 = (rvParticle *)(v17 + 1);
          *v17 = mLoopParticleCount;
          `eh vector constructor iterator'(
            v17 + 1,
            0x190u,
            mLoopParticleCount,
            (void (__thiscall *)(void *))rvSpriteParticle::rvSpriteParticle,
            (void (__thiscall *)(void *))rvLineParticle::~rvLineParticle);
        }
        else
        {
LABEL_28:
          v3 = 0;
        }
        break;
    }
    v18 = mLoopParticleCount - 1;
    for ( i = 0; i < v18; *(_DWORD *)(v20 + 4) = v3->GetArrayEntry(v3, i) )
      v20 = (int)v3->GetArrayEntry(v3, i++);
    v3->GetArrayEntry(v3, v18)->mNext = 0;
  }
  this->mFreeHead = v3;
  this->mUsedHead = 0;
  return v3;
}

// FUNC: public: void __thiscall rvSegment::InitParticles(class rvBSE *)
void __thiscall rvSegment::InitParticles(rvSegment *this, rvBSE *effect)
{
  if ( rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle) )
  {
    this->mParticles = rvSegment::InitParticleArray(this, effect);
    this->mActiveCount = 0;
  }
}

// FUNC: public: void __thiscall rvSegment::CreateDecal(class rvBSE *,float)
void __userpurge rvSegment::CreateDecal(rvSegment *this@<ecx>, int a2@<ebp>, int a3@<esi>, rvBSE *effect, float time)
{
  bool v6; // zf
  float z; // ecx
  float y; // eax
  float x; // edx
  float v10; // ecx
  float v11; // edx
  float v12; // eax
  float v13; // ecx
  int mSegmentTemplateHandle; // edx
  float v15; // eax
  rvDeclEffect *mEffectDecl; // ecx
  rvSegmentTemplate *SegmentTemplate; // ebp
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v19; // eax
  int v20; // ebx
  int v21; // eax
  rvSegmentTemplate *v22; // eax
  double v23; // st7
  long double v24; // st6
  long double v25; // st6
  long double v26; // st7
  double v27; // st7
  double v28; // st6
  double v29; // st5
  double v30; // st4
  int allocedSize; // eax
  int v32; // edx
  int v33; // edx
  int v34; // edx
  int v35; // edx
  float v37; // [esp+30h] [ebp-5E4h]
  float v38; // [esp+30h] [ebp-5E4h]
  float v39; // [esp+30h] [ebp-5E4h]
  float v40; // [esp+30h] [ebp-5E4h]
  float v41; // [esp+34h] [ebp-5E0h]
  float v42; // [esp+34h] [ebp-5E0h]
  float v43; // [esp+34h] [ebp-5E0h]
  float v44; // [esp+34h] [ebp-5E0h]
  float v45; // [esp+34h] [ebp-5E0h]
  float v46; // [esp+34h] [ebp-5E0h]
  float v47; // [esp+34h] [ebp-5E0h]
  float v48; // [esp+34h] [ebp-5E0h]
  float v49; // [esp+34h] [ebp-5E0h]
  float v50; // [esp+34h] [ebp-5E0h]
  float v51; // [esp+34h] [ebp-5E0h]
  float v52; // [esp+34h] [ebp-5E0h]
  float v53; // [esp+34h] [ebp-5E0h]
  float v54; // [esp+34h] [ebp-5E0h]
  float v55; // [esp+34h] [ebp-5E0h]
  float v56; // [esp+38h] [ebp-5DCh]
  float v57; // [esp+38h] [ebp-5DCh]
  float v58; // [esp+38h] [ebp-5DCh]
  float v59; // [esp+38h] [ebp-5DCh]
  float v60; // [esp+38h] [ebp-5DCh]
  float v61; // [esp+3Ch] [ebp-5D8h]
  float v62; // [esp+3Ch] [ebp-5D8h]
  float v63; // [esp+3Ch] [ebp-5D8h]
  float v64; // [esp+3Ch] [ebp-5D8h]
  float v65; // [esp+48h] [ebp-5CCh]
  float v66; // [esp+48h] [ebp-5CCh]
  float v67; // [esp+4Ch] [ebp-5C8h]
  float v68; // [esp+4Ch] [ebp-5C8h]
  float v69; // [esp+4Ch] [ebp-5C8h]
  float v70; // [esp+50h] [ebp-5C4h]
  float v71; // [esp+50h] [ebp-5C4h]
  float v72; // [esp+50h] [ebp-5C4h]
  float v73; // [esp+50h] [ebp-5C4h]
  float acosa; // [esp+54h] [ebp-5C0h]
  float acosb; // [esp+54h] [ebp-5C0h]
  float acos; // [esp+54h] [ebp-5C0h]
  float v77; // [esp+58h] [ebp-5BCh]
  float v78; // [esp+58h] [ebp-5BCh]
  float v79; // [esp+58h] [ebp-5BCh]
  float v80; // [esp+58h] [ebp-5BCh]
  float v81; // [esp+58h] [ebp-5BCh]
  float v82; // [esp+5Ch] [ebp-5B8h]
  float v83; // [esp+60h] [ebp-5B4h]
  float v84; // [esp+60h] [ebp-5B4h]
  float v85; // [esp+64h] [ebp-5B0h]
  idVec3 size; // [esp+68h] [ebp-5ACh] BYREF
  idMat3 axis; // [esp+78h] [ebp-59Ch]
  float asin; // [esp+9Ch] [ebp-578h]
  float v89; // [esp+A0h] [ebp-574h]
  float v90; // [esp+A4h] [ebp-570h]
  float v91; // [esp+A8h] [ebp-56Ch]
  idVec3 origin; // [esp+ACh] [ebp-568h]
  float v93; // [esp+B8h] [ebp-55Ch]
  float v94; // [esp+BCh] [ebp-558h]
  float v95; // [esp+C0h] [ebp-554h]
  idVec3 projectionOrigin; // [esp+C4h] [ebp-550h] BYREF
  float v97; // [esp+D0h] [ebp-544h]
  float v98; // [esp+D4h] [ebp-540h]
  float v99; // [esp+D8h] [ebp-53Ch]
  idVec3 rotation; // [esp+DCh] [ebp-538h] BYREF
  idVec4 tint; // [esp+E8h] [ebp-52Ch] BYREF
  idFixedWinding winding; // [esp+F8h] [ebp-51Ch] BYREF
  int v103; // [esp+610h] [ebp-4h]

  if ( (_S6_8 & 1) == 0 )
  {
    _S6_8 |= 1u;
    decalWinding[0].x = 1.0;
    dword_1137DDE0 = 1065353216;
    dword_1137DDE4 = 0;
    dword_1137DDE8 = -1082130432;
    dword_1137DDEC = 1065353216;
    dword_1137DDF0 = 0;
    dword_1137DDF4 = -1082130432;
    dword_1137DDF8 = -1082130432;
    dword_1137DDFC = 0;
    dword_1137DE00 = 1065353216;
    dword_1137DE04 = -1082130432;
    dword_1137DE08 = 0;
  }
  winding.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  winding.numPoints = 0;
  winding.p = winding.data;
  winding.allocedSize = 64;
  v6 = bse_render.internalVar->integerValue == 0;
  v103 = 0;
  if ( v6 )
  {
    v103 = -1;
    winding.p = 0;
    winding.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(0);
    return;
  }
  z = effect->mCurrentOrigin.z;
  y = effect->mCurrentOrigin.y;
  origin.x = effect->mCurrentOrigin.x;
  x = effect->mCurrentAxis.mat[0].x;
  origin.z = z;
  v10 = effect->mCurrentAxis.mat[0].z;
  axis.mat[0].x = x;
  v11 = effect->mCurrentAxis.mat[2].x;
  origin.y = y;
  v12 = effect->mCurrentAxis.mat[0].y;
  axis.mat[0].z = v10;
  v13 = effect->mCurrentAxis.mat[2].z;
  axis.mat[2].x = v11;
  mSegmentTemplateHandle = this->mSegmentTemplateHandle;
  axis.mat[0].y = v12;
  v15 = effect->mCurrentAxis.mat[2].y;
  axis.mat[2].z = v13;
  mEffectDecl = (rvDeclEffect *)this->mEffectDecl;
  axis.mat[2].y = v15;
  SegmentTemplate = rvDeclEffect::GetSegmentTemplate(mEffectDecl, mSegmentTemplateHandle);
  if ( SegmentTemplate )
  {
    if ( bse_debug.internalVar->integerValue )
    {
      base = SegmentTemplate->mParticleTemplate.mMaterial->base;
      v19 = base->__vftable;
      ++count_0;
      v20 = *(_DWORD *)common.type;
      v21 = (int)v19->GetName(base);
      (*(void (**)(netadrtype_t, const char *, ...))(v20 + 124))(common.type, "BSE: Decal %d: %s\n", count_0, v21);
    }
    v22 = rvSegment::SpawnParticle(this, effect, SegmentTemplate, time, &vec3_origin, &mat3_identity);
    ((void (__thiscall *)(rvSegmentTemplate *, idVec4 *, idVec3 *, idVec3 *, int, int))v22->mDeclEffect[1].mSegmentTemplates.size)(
      v22,
      &tint,
      &size,
      &rotation,
      a3,
      a2);
    v82 = cos(rotation.z);
    v90 = sin(rotation.z);
    v23 = -axis.mat[1].y;
    v65 = -axis.mat[1].x;
    asin = v65;
    v85 = -axis.mat[0].z;
    axis.mat[2].z = v85;
    v89 = v23;
    v24 = v85 * v85 + v65 * v65 + v23 * v23;
    if ( v24 != 0.0 )
    {
      v25 = 1.0 / sqrt(v24);
      axis.mat[2].z = v85 * v25;
      asin = v65 * v25;
      v89 = v25 * v23;
    }
    v26 = axis.mat[2].z * axis.mat[2].z + asin * asin;
    if ( v26 == 0.0 )
    {
      v27 = 1.0;
      v28 = 0.0;
    }
    else
    {
      v37 = 1.0 / sqrt(v26);
      v27 = -(asin * v37);
      v28 = axis.mat[2].z * v37;
    }
    size.x = asin;
    size.y = v89;
    v38 = v27 * asin - axis.mat[2].z * v28;
    v67 = axis.mat[2].z * 0.0 - v27 * v89;
    v41 = v89 * v28 - asin * 0.0;
    v29 = -v90;
    v83 = v67 * v29;
    v95 = v41 * v29;
    acosa = v28 * v82;
    v91 = v27 * v82;
    v66 = v82 * 0.0 + v38 * v29;
    v84 = acosa + v83;
    v99 = v91 + v95;
    v30 = -v82;
    acosb = v38 * v30;
    v77 = v67 * v30;
    v91 = v30 * v41;
    v39 = v29;
    v68 = v29 * 0.0;
    v42 = v27 * v39;
    axis.mat[0].y = v68 + acosb;
    acos = v28 * v39 + v77;
    v95 = v42 + v91;
    allocedSize = 0;
    winding.allocedSize = 0;
    v69 = v89 * 8.0 + v94;
    v40 = asin * 8.0 + v93;
    v91 = axis.mat[2].z * 8.0 + origin.z;
    v43 = axis.mat[2].z * 8.0;
    v56 = asin * 8.0;
    projectionOrigin.z = origin.z - v43;
    v97 = v93 - v56;
    v98 = v94 - v89 * 8.0;
    v44 = axis.mat[2].z * *(float *)&dword_1137DDE4 + v95 * *(float *)&dword_1137DDE0 + v99 * decalWinding[0].x;
    v78 = size.z
        * (v89 * *(float *)&dword_1137DDE4 + axis.mat[0].y * *(float *)&dword_1137DDE0 + v66 * decalWinding[0].x);
    v70 = size.z * (asin * *(float *)&dword_1137DDE4 + acos * *(float *)&dword_1137DDE0 + v84 * decalWinding[0].x);
    v45 = size.z * v44;
    v46 = v45 + v91;
    if ( SLODWORD(winding.data[0].y) < 1 )
    {
      if ( !((unsigned __int8 (__thiscall *)(idVec5 **, int, int))LODWORD(winding.p->z))(&winding.p, 1, 1) )
        goto LABEL_17;
      allocedSize = winding.allocedSize;
    }
    v32 = LODWORD(winding.data[0].x) + 20 * allocedSize;
    *(float *)v32 = v46;
    v57 = v70 + v40;
    *(float *)(v32 + 4) = v57;
    v61 = v78 + v69;
    *(float *)(v32 + 8) = v61;
    *(_DWORD *)(v32 + 12) = 1065353216;
    *(_DWORD *)(v32 + 16) = 1065353216;
    ++winding.allocedSize;
LABEL_17:
    v47 = axis.mat[2].z * *(float *)&dword_1137DDF0 + v99 * *(float *)&dword_1137DDE8 + *(float *)&dword_1137DDEC * v95;
    v71 = size.z
        * (v89 * *(float *)&dword_1137DDF0 + v66 * *(float *)&dword_1137DDE8 + *(float *)&dword_1137DDEC * axis.mat[0].y);
    v79 = size.z
        * (asin * *(float *)&dword_1137DDF0 + v84 * *(float *)&dword_1137DDE8 + *(float *)&dword_1137DDEC * acos);
    v48 = size.z * v47;
    v49 = v48 + v91;
    if ( winding.allocedSize + 1 <= SLODWORD(winding.data[0].y)
      || ((unsigned __int8 (__thiscall *)(idVec5 **, int, int))LODWORD(winding.p->z))(
           &winding.p,
           winding.allocedSize + 1,
           1) )
    {
      v33 = LODWORD(winding.data[0].x) + 20 * winding.allocedSize;
      *(float *)v33 = v49;
      v58 = v79 + v40;
      *(float *)(v33 + 4) = v58;
      v62 = v71 + v69;
      *(float *)(v33 + 8) = v62;
      *(_DWORD *)(v33 + 12) = 0;
      *(_DWORD *)(v33 + 16) = 1065353216;
      ++winding.allocedSize;
    }
    v50 = axis.mat[2].z * *(float *)&dword_1137DDFC + v99 * *(float *)&dword_1137DDF4 + *(float *)&dword_1137DDF8 * v95;
    v72 = size.z
        * (v89 * *(float *)&dword_1137DDFC + v66 * *(float *)&dword_1137DDF4 + *(float *)&dword_1137DDF8 * axis.mat[0].y);
    v80 = size.z
        * (asin * *(float *)&dword_1137DDFC + v84 * *(float *)&dword_1137DDF4 + *(float *)&dword_1137DDF8 * acos);
    v51 = size.z * v50;
    v52 = v51 + v91;
    if ( winding.allocedSize + 1 <= SLODWORD(winding.data[0].y)
      || ((unsigned __int8 (__thiscall *)(idVec5 **, int, int))LODWORD(winding.p->z))(
           &winding.p,
           winding.allocedSize + 1,
           1) )
    {
      v34 = LODWORD(winding.data[0].x) + 20 * winding.allocedSize;
      *(float *)v34 = v52;
      v59 = v80 + v40;
      *(float *)(v34 + 4) = v59;
      v63 = v72 + v69;
      *(float *)(v34 + 8) = v63;
      *(_DWORD *)(v34 + 12) = 0;
      *(_DWORD *)(v34 + 16) = 0;
      ++winding.allocedSize;
    }
    v53 = axis.mat[2].z * *(float *)&dword_1137DE08 + v99 * *(float *)&dword_1137DE00 + *(float *)&dword_1137DE04 * v95;
    v73 = size.z
        * (v89 * *(float *)&dword_1137DE08 + v66 * *(float *)&dword_1137DE00 + *(float *)&dword_1137DE04 * axis.mat[0].y);
    v81 = size.z
        * (asin * *(float *)&dword_1137DE08 + v84 * *(float *)&dword_1137DE00 + *(float *)&dword_1137DE04 * acos);
    v54 = size.z * v53;
    v55 = v54 + v91;
    if ( winding.allocedSize + 1 <= SLODWORD(winding.data[0].y)
      || ((unsigned __int8 (__thiscall *)(idVec5 **, int, int))LODWORD(winding.p->z))(
           &winding.p,
           winding.allocedSize + 1,
           1) )
    {
      v35 = LODWORD(winding.data[0].x) + 20 * winding.allocedSize;
      *(float *)v35 = v55;
      v60 = v81 + v40;
      *(float *)(v35 + 4) = v60;
      v64 = v73 + v69;
      *(float *)(v35 + 8) = v64;
      *(_DWORD *)(v35 + 12) = 1065353216;
      *(_DWORD *)(v35 + 16) = 0;
      ++winding.allocedSize;
    }
    ((void (__thiscall *)(idRenderWorld *, idVec5 **, float *, int, int))session->rw->ProjectDecalOntoWorld)(
      session->rw,
      &winding.p,
      &projectionOrigin.z,
      1,
      1090519040);
  }
  winding.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  winding.p = 0;
  v103 = -1;
  Memory::Free(0);
}

// FUNC: public: bool __thiscall rvSegment::Check(class rvBSE *,float)
bool __thiscall rvSegment::Check(rvSegment *this, rvBSE *effect, float time)
{
  bool v4; // zf
  int mFlags; // eax
  rvSegmentTemplate *SegmentTemplate; // eax
  rvSegmentTemplate *v8; // edi
  double v9; // st7
  unsigned __int8 v11; // c0
  unsigned __int8 v12; // c2
  idSoundEmitter *ReferenceSound; // ebx
  int v14; // eax
  idSoundEmitter_vtbl *v15; // ebp
  idSoundEmitter_vtbl *v16; // ebp
  float v18; // [esp+0h] [ebp-1Ch]
  float v19; // [esp+0h] [ebp-1Ch]
  float timea; // [esp+4h] [ebp-18h]
  float timeb; // [esp+4h] [ebp-18h]
  float timec; // [esp+4h] [ebp-18h]
  float scale; // [esp+8h] [ebp-14h]
  float scalea; // [esp+8h] [ebp-14h]
  float scaleb; // [esp+8h] [ebp-14h]
  float spawnTime; // [esp+18h] [ebp-4h]
  rvBSE *effecta; // [esp+20h] [ebp+4h]
  int count; // [esp+24h] [ebp+8h]
  int counta; // [esp+24h] [ebp+8h]
  int countb; // [esp+24h] [ebp+8h]

  v4 = (this->mFlags & 1) == 0;
  spawnTime = this->mLastTime;
  this->mLastTime = time;
  if ( !v4 || (effect->mFlags & 8) != 0 )
  {
    LOBYTE(mFlags) = 1;
  }
  else if ( time >= (double)this->mSegStartTime )
  {
    SegmentTemplate = rvDeclEffect::GetSegmentTemplate((rvDeclEffect *)this->mEffectDecl, this->mSegmentTemplateHandle);
    v8 = SegmentTemplate;
    if ( !SegmentTemplate || rvSegmentTemplate::DetailCull(SegmentTemplate) )
    {
      LOBYTE(mFlags) = 1;
    }
    else
    {
      switch ( v8->mSegType )
      {
        case 1:
          if ( (v8->mFlags & 1) == 0 )
            goto $L119003;
          rvSegment::PlayEffect(this, effect, v8);
          this->mFlags |= 1u;
          return this->mFlags & 1;
        case 2:
          if ( !rvBSE::CanInterpolate(effect) )
            return this->mFlags & 1;
          *(float *)&count = time + 0.016000001;
          if ( this->mSegEndTime - 0.0020000001 <= *(float *)&count )
            count = SLODWORD(this->mSegEndTime);
          v9 = spawnTime;
          if ( spawnTime < (double)*(float *)&count )
          {
            do
            {
              if ( v9 >= this->mSegStartTime )
                rvSegment::SpawnParticle(this, effect, v8, spawnTime, &vec3_origin, &mat3_identity);
              v9 = rvSegment::AttenuateInterval(this, effect, v8) + spawnTime;
              spawnTime = v9;
            }
            while ( v11 | v12 );
          }
          if ( this->mSegEndTime - 0.0020000001 <= *(float *)&count )
            this->mFlags |= 1u;
          mFlags = this->mFlags;
          this->mLastTime = v9;
          LOBYTE(mFlags) = mFlags & 1;
          return mFlags;
        case 3:
          effecta = (rvBSE *)(int)rvSegment::AttenuateCount(this, effect, v8, this->mCount.x, this->mCount.y);
          rvSegment::SpawnParticles(this, effect, v8, this->mSegStartTime, (int)effecta);
          this->mFlags |= 1u;
          return this->mFlags & 1;
        case 4:
        case 8:
          goto $L119003;
        case 5:
          if ( (v8->mFlags & 1) == 0 )
            goto $L119003;
          ReferenceSound = rvBSE::GetReferenceSound(effect, 1);
          if ( !ReferenceSound )
            goto LABEL_28;
          this->mSoundVolume = rvSegmentTemplate::GetSoundVolume(v8);
          this->mFreqShift = rvSegmentTemplate::GetFreqShift(v8);
          rvBSE::UpdateSoundEmitter(effect, v8, this);
          if ( rvSegmentTemplate::GetSoundLooping(v8) )
          {
            v14 = this->mFlags;
            if ( (v14 & 2) == 0 )
            {
              LOBYTE(v14) = v14 | 2;
              this->mFlags = v14;
              v15 = ReferenceSound->__vftable;
              counta = this->mSegmentTemplateHandle + 1;
              v18 = rvRandom::flrand(0.0, 1.0);
              ((void (__thiscall *)(idSoundEmitter *, const idSoundShader *, int, _DWORD, int))v15->StartSound)(
                ReferenceSound,
                v8->mSoundShader,
                counta,
                LODWORD(v18),
                32);
              this->mFlags |= 1u;
              return this->mFlags & 1;
            }
          }
          else
          {
            v16 = ReferenceSound->__vftable;
            countb = this->mSegmentTemplateHandle + 1;
            v19 = rvRandom::flrand(0.0, 1.0);
            ((void (__thiscall *)(idSoundEmitter *, const idSoundShader *, int, _DWORD, _DWORD))v16->StartSound)(
              ReferenceSound,
              v8->mSoundShader,
              countb,
              LODWORD(v19),
              0);
          }
LABEL_28:
          this->mFlags |= 1u;
          mFlags = this->mFlags & 1;
          break;
        case 6:
          if ( (v8->mFlags & 1) == 0 || !rvBSEManagerLocal::g_decals->internalVar->integerValue )
            goto $L119003;
          rvSegment::CreateDecal(this, (int)effect, (int)this, effect, this->mSegStartTime);
          this->mFlags |= 1u;
          return this->mFlags & 1;
        case 7:
          if ( (v8->mFlags & 1) == 0 )
            goto $L119003;
          rvSegment::InitLight(this, effect, v8, this->mSegStartTime);
          this->mFlags |= 1u;
          return this->mFlags & 1;
        case 9:
          if ( (v8->mFlags & 1) == 0 )
            goto $L119003;
          scale = rvBSE::GetOriginAttenuation(effect, v8);
          timea = rvSegment::AttenuateDuration(this, effect, v8) + this->mSegStartTime;
          rvBSEManagerLocal::SetDoubleVisionParms(&bseLocal, timea, scale);
          this->mFlags |= 1u;
          return this->mFlags & 1;
        case 0xA:
          if ( (v8->mFlags & 1) == 0 )
            goto $L119003;
          scalea = rvBSE::GetOriginAttenuation(effect, v8);
          timeb = rvSegment::AttenuateDuration(this, effect, v8) + this->mSegStartTime;
          rvBSEManagerLocal::SetShakeParms(&bseLocal, timeb, scalea);
          this->mFlags |= 1u;
          return this->mFlags & 1;
        case 0xB:
          if ( (v8->mFlags & 1) != 0 )
          {
            scaleb = rvBSE::GetOriginAttenuation(effect, v8);
            timec = rvSegment::AttenuateDuration(this, effect, v8) + this->mSegStartTime;
            rvBSEManagerLocal::SetTunnelParms(&bseLocal, timec, scaleb);
          }
$L119003:
          this->mFlags |= 1u;
          return this->mFlags & 1;
        default:
          return this->mFlags & 1;
      }
    }
  }
  else
  {
    LOBYTE(mFlags) = 0;
  }
  return mFlags;
}
