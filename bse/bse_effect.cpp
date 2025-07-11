
// FUNC: public: float __thiscall rvBSE::GetAttenuation(class rvSegmentTemplate *)const
double __thiscall rvBSE::GetAttenuation(rvBSE *this, rvSegmentTemplate *st)
{
  if ( st->mAttenuation.x <= 0.0 && st->mAttenuation.y <= 0.0
    || st->mAttenuation.x + 1.0 > this->mShortestDistanceToCamera )
  {
    return this->mAttenuation;
  }
  if ( st->mAttenuation.y - 1.0 >= this->mShortestDistanceToCamera )
    return (1.0 - (this->mShortestDistanceToCamera - st->mAttenuation.x) / (st->mAttenuation.y - st->mAttenuation.x))
         * this->mAttenuation;
  return 0.0;
}

// FUNC: public: float __thiscall rvBSE::GetOriginAttenuation(class rvSegmentTemplate *)const
double __thiscall rvBSE::GetOriginAttenuation(rvBSE *this, rvSegmentTemplate *st)
{
  if ( st->mAttenuation.x <= 0.0 && st->mAttenuation.y <= 0.0
    || st->mAttenuation.x + 1.0 > this->mOriginDistanceToCamera )
  {
    return st->mScale * this->mAttenuation;
  }
  if ( st->mAttenuation.y - 1.0 >= this->mOriginDistanceToCamera )
    return (1.0 - (this->mOriginDistanceToCamera - st->mAttenuation.x) / (st->mAttenuation.y - st->mAttenuation.x))
         * st->mScale
         * this->mAttenuation;
  return 0.0;
}

// FUNC: public: void __thiscall rvBSE::UpdateSoundEmitter(class rvSegmentTemplate *,class rvSegment *)
void __thiscall rvBSE::UpdateSoundEmitter(rvBSE *this, rvSegmentTemplate *st, rvSegment *seg)
{
  idSoundEmitter *v4; // eax
  idSoundEmitter *v5; // esi
  float mFreqShift; // edx
  int mReferenceSoundHandle; // [esp-4h] [ebp-34h]
  soundShaderParms_t parms; // [esp+8h] [ebp-28h] BYREF

  mReferenceSoundHandle = this->mReferenceSoundHandle;
  memset(&parms, 0, sizeof(parms));
  v4 = soundSystem->EmitterForIndex(soundSystem, 1, mReferenceSoundHandle);
  v5 = v4;
  if ( v4 )
  {
    if ( (this->mFlags & 8) != 0 )
    {
      if ( rvSegmentTemplate::GetSoundLooping(st) && (seg->mFlags & 2) != 0 )
        v5->StopSound(v5, seg->mSegmentTemplateHandle + 1);
    }
    else
    {
      mFreqShift = seg->mFreqShift;
      parms.volume = seg->mSoundVolume;
      parms.frequencyShift = mFreqShift;
      v4->UpdateEmitter(v4, &this->mCurrentOrigin, &this->mCurrentVelocity, 0, &parms);
    }
  }
}

// FUNC: public: class idVec3 const __thiscall rvBSE::GetInterpolatedOffset(float)const
const idVec3 *__thiscall rvBSE::GetInterpolatedOffset(rvBSE *this, idVec3 *result, float time)
{
  double v3; // st7
  double v4; // st7
  const idVec3 *v5; // eax
  idVec3 resulta; // [esp+0h] [ebp-24h] BYREF
  float v7; // [esp+Ch] [ebp-18h]
  float v8; // [esp+10h] [ebp-14h]
  float v9; // [esp+14h] [ebp-10h]
  float v10; // [esp+20h] [ebp-4h]

  v3 = this->mCurrentTime - this->mLastTime;
  memset(&resulta, 0, sizeof(resulta));
  if ( v3 >= 0.0020000001 )
  {
    v4 = 1.0 - (time - this->mLastTime) / v3;
    v7 = this->mCurrentOrigin.x - this->mLastOrigin.x;
    v8 = this->mCurrentOrigin.y - this->mLastOrigin.y;
    v9 = this->mCurrentOrigin.z - this->mLastOrigin.z;
    v10 = v9 * v4;
    resulta.z = v10;
    resulta.x = v7 * v4;
    resulta.y = v8 * v4;
  }
  v5 = result;
  *result = resulta;
  return v5;
}

// FUNC: public: void __thiscall rvBSE::SetDuration(float)
void __thiscall rvBSE::SetDuration(rvBSE *this, float time)
{
  if ( time > (double)this->mDuration )
    this->mDuration = time;
}

// FUNC: public: char const * __thiscall rvBSE::GetDeclName(void)
const char *__thiscall rvBSE::GetDeclName(rvBSE *this)
{
  return this->mDeclEffect->base->GetName(this->mDeclEffect->base);
}

// FUNC: public: void __thiscall rvBSE::UpdateFromOwner(struct renderEffect_s *,float,bool)
void __thiscall rvBSE::UpdateFromOwner(rvBSE *this, renderEffect_s *parms, float time, bool init)
{
  idVec3 *p_mCurrentOrigin; // ebx
  float *p_z; // ecx
  float *v7; // eax
  int v8; // edx
  double z; // st7
  double v10; // st6
  float x; // eax
  double v12; // st5
  double y; // st4
  double v14; // st3
  double v15; // st2
  float *v16; // ecx
  float *p_y; // eax
  double v18; // st7
  double v19; // st6
  double v20; // st6
  double v21; // st7
  float v22; // edx
  long double v23; // st4
  long double v24; // st7
  double v25; // st7
  double v26; // st6
  double v27; // st7
  float v28; // eax
  float v29; // ecx
  double v30; // st7
  double v31; // st7
  double v32; // st7
  int v33; // ecx
  double v34; // st7
  double v35; // st6
  double v36; // st7
  double v37; // st6
  double v38; // st7
  int v39; // [esp+24h] [ebp-40h]
  idVec3 corner; // [esp+28h] [ebp-3Ch]
  float v41; // [esp+34h] [ebp-30h] BYREF
  float v42; // [esp+38h] [ebp-2Ch]
  float v43; // [esp+3Ch] [ebp-28h]
  float v44; // [esp+40h] [ebp-24h] BYREF
  int v45[8]; // [esp+44h] [ebp-20h] BYREF
  int timea; // [esp+6Ch] [ebp+8h]
  float timeb; // [esp+6Ch] [ebp+8h]

  this->mLastTime = this->mCurrentTime;
  this->mLastOrigin = this->mCurrentOrigin;
  p_mCurrentOrigin = &this->mCurrentOrigin;
  this->mCurrentTime = time;
  this->mCurrentOrigin = parms->origin;
  p_z = &this->mCurrentAxis.mat[0].z;
  v7 = &parms->axis.mat[0].z;
  v8 = 3;
  do
  {
    *(p_z - 2) = *(v7 - 2);
    *(p_z - 1) = *(v7 - 1);
    *p_z = *v7;
    v7 += 3;
    p_z += 3;
    --v8;
  }
  while ( v8 );
  z = this->mCurrentAxis.mat[2].z;
  v10 = this->mCurrentAxis.mat[1].z;
  x = this->mCurrentAxis.mat[1].x;
  v12 = this->mCurrentAxis.mat[0].z;
  y = this->mCurrentAxis.mat[2].y;
  v14 = this->mCurrentAxis.mat[1].y;
  v44 = this->mCurrentAxis.mat[0].x;
  v15 = this->mCurrentAxis.mat[0].y;
  v16 = &v44;
  v45[1] = SLODWORD(this->mCurrentAxis.mat[2].x);
  *(float *)&v45[2] = v15;
  *(float *)&v45[3] = v14;
  *(float *)v45 = x;
  *(float *)&v45[4] = y;
  p_y = &this->mCurrentAxisTransposed.mat[0].y;
  v39 = (char *)v45 - (char *)&this->mCurrentAxisTransposed;
  *(float *)&v45[5] = v12;
  timea = 3;
  *(float *)&v45[6] = v10;
  *(float *)&v45[7] = z;
  do
  {
    *(p_y - 1) = *v16;
    *p_y = *(float *)((char *)p_y + (char *)&v44 - (char *)&this->mCurrentAxisTransposed);
    p_y[1] = *(float *)((char *)p_y + v39);
    v16 += 3;
    p_y += 3;
    --timea;
  }
  while ( timea );
  v18 = this->mCurrentTime - this->mLastTime;
  if ( v18 > 0.0020000001 )
  {
    v19 = p_mCurrentOrigin->x - this->mLastOrigin.x;
    v42 = this->mCurrentOrigin.y - this->mLastOrigin.y;
    v43 = this->mCurrentOrigin.z - this->mLastOrigin.z;
    timeb = 1.0 / v18;
    v43 = v43 * timeb;
    v20 = 1.0 / v18 * v19;
    v21 = v42 * timeb;
    this->mCurrentVelocity.z = v43;
    this->mCurrentVelocity.x = v20;
    this->mCurrentVelocity.y = v21;
  }
  v22 = parms->gravity.x;
  this->mGravity.x = v22;
  this->mGravity.y = parms->gravity.y;
  this->mGravity.z = parms->gravity.z;
  this->mGravityDir.x = v22;
  this->mGravityDir.y = this->mGravity.y;
  this->mGravityDir.z = this->mGravity.z;
  v23 = this->mGravityDir.x * this->mGravityDir.x
      + this->mGravityDir.y * this->mGravityDir.y
      + this->mGravityDir.z * this->mGravityDir.z;
  if ( v23 != 0.0 )
  {
    v24 = 1.0 / sqrt(v23);
    this->mGravityDir.x = v24 * this->mGravityDir.x;
    this->mGravityDir.y = v24 * this->mGravityDir.y;
    this->mGravityDir.z = v24 * this->mGravityDir.z;
  }
  corner.x = this->mDeclEffect->mSize;
  v25 = corner.x + p_mCurrentOrigin->x;
  corner.y = corner.x;
  v26 = corner.x + this->mCurrentOrigin.y;
  corner.z = corner.x;
  v42 = v26;
  v43 = corner.x + this->mCurrentOrigin.z;
  if ( v25 < this->mCurrentWorldBounds.b[0].x )
    this->mCurrentWorldBounds.b[0].x = v25;
  if ( v25 > this->mCurrentWorldBounds.b[1].x )
    this->mCurrentWorldBounds.b[1].x = v25;
  if ( v42 < (double)this->mCurrentWorldBounds.b[0].y )
    this->mCurrentWorldBounds.b[0].y = v42;
  if ( v42 > (double)this->mCurrentWorldBounds.b[1].y )
    this->mCurrentWorldBounds.b[1].y = v42;
  if ( v43 < (double)this->mCurrentWorldBounds.b[0].z )
    this->mCurrentWorldBounds.b[0].z = v43;
  if ( v43 > (double)this->mCurrentWorldBounds.b[1].z )
    this->mCurrentWorldBounds.b[1].z = v43;
  v27 = p_mCurrentOrigin->x - corner.x;
  v42 = this->mCurrentOrigin.y - corner.y;
  v43 = this->mCurrentOrigin.z - corner.z;
  if ( v27 < this->mCurrentWorldBounds.b[0].x )
    this->mCurrentWorldBounds.b[0].x = v27;
  if ( v27 > this->mCurrentWorldBounds.b[1].x )
    this->mCurrentWorldBounds.b[1].x = v27;
  if ( v42 < (double)this->mCurrentWorldBounds.b[0].y )
    this->mCurrentWorldBounds.b[0].y = v42;
  if ( v42 > (double)this->mCurrentWorldBounds.b[1].y )
    this->mCurrentWorldBounds.b[1].y = v42;
  if ( v43 < (double)this->mCurrentWorldBounds.b[0].z )
    this->mCurrentWorldBounds.b[0].z = v43;
  if ( v43 > (double)this->mCurrentWorldBounds.b[1].z )
    this->mCurrentWorldBounds.b[1].z = v43;
  if ( bse_debug.internalVar->integerValue > 2 )
  {
    session->rw->DebugLine(session->rw, &colorWhite, &this->mCurrentOrigin, &this->mLastOrigin, 0, 0);
    v28 = p_mCurrentOrigin->x;
    v29 = this->mCurrentOrigin.y;
    v43 = this->mCurrentOrigin.z + 10.0;
    v41 = v28;
    v42 = v29;
    session->rw->DebugLine(session->rw, &colorGreen, &this->mCurrentOrigin, (const idVec3 *)&v41, 0, 0);
  }
  if ( (this->mFlags & 2) != 0
    && (this->mDeclEffect->mFlags & 2) != 0
    && (init
     || this->mCurrentEndOrigin.x != parms->endOrigin.x
     || this->mCurrentEndOrigin.y != parms->endOrigin.y
     || this->mCurrentEndOrigin.z != parms->endOrigin.z
     || p_mCurrentOrigin->x != this->mLastOrigin.x
     || this->mCurrentOrigin.y != this->mLastOrigin.y
     || this->mCurrentOrigin.z != this->mLastOrigin.z) )
  {
    v30 = corner.x;
    this->mCurrentEndOrigin = parms->endOrigin;
    v31 = v30 + this->mCurrentEndOrigin.x;
    v42 = corner.y + this->mCurrentEndOrigin.y;
    v43 = corner.z + this->mCurrentEndOrigin.z;
    if ( v31 < this->mCurrentWorldBounds.b[0].x )
      this->mCurrentWorldBounds.b[0].x = v31;
    if ( v31 > this->mCurrentWorldBounds.b[1].x )
      this->mCurrentWorldBounds.b[1].x = v31;
    if ( v42 < (double)this->mCurrentWorldBounds.b[0].y )
      this->mCurrentWorldBounds.b[0].y = v42;
    if ( v42 > (double)this->mCurrentWorldBounds.b[1].y )
      this->mCurrentWorldBounds.b[1].y = v42;
    if ( v43 < (double)this->mCurrentWorldBounds.b[0].z )
      this->mCurrentWorldBounds.b[0].z = v43;
    if ( v43 > (double)this->mCurrentWorldBounds.b[1].z )
      this->mCurrentWorldBounds.b[1].z = v43;
    v32 = this->mCurrentEndOrigin.x - corner.x;
    v42 = this->mCurrentEndOrigin.y - corner.y;
    v43 = this->mCurrentEndOrigin.z - corner.z;
    if ( v32 < this->mCurrentWorldBounds.b[0].x )
      this->mCurrentWorldBounds.b[0].x = v32;
    if ( v32 > this->mCurrentWorldBounds.b[1].x )
      this->mCurrentWorldBounds.b[1].x = v32;
    if ( v42 < (double)this->mCurrentWorldBounds.b[0].y )
      this->mCurrentWorldBounds.b[0].y = v42;
    if ( v42 > (double)this->mCurrentWorldBounds.b[1].y )
      this->mCurrentWorldBounds.b[1].y = v42;
    if ( v43 < (double)this->mCurrentWorldBounds.b[0].z )
      this->mCurrentWorldBounds.b[0].z = v43;
    if ( v43 > (double)this->mCurrentWorldBounds.b[1].z )
      this->mCurrentWorldBounds.b[1].z = v43;
    this->mFlags |= 4u;
  }
  this->mCurrentLocalBounds.b[0].z = idMath::INFINITY;
  this->mCurrentLocalBounds.b[0].y = idMath::INFINITY;
  this->mCurrentLocalBounds.b[0].x = idMath::INFINITY;
  v33 = 0;
  this->mCurrentLocalBounds.b[1].z = -1.0e30;
  this->mCurrentLocalBounds.b[1].y = -1.0e30;
  this->mCurrentLocalBounds.b[1].x = -1.0e30;
  do
  {
    v34 = this->mCurrentWorldBounds.b[v33 & 1].x;
    v35 = this->mCurrentWorldBounds.b[(v33 >> 1) & 1].y;
    corner.z = this->mCurrentWorldBounds.b[(v33 >> 2) & 1].z;
    corner.x = v34 - p_mCurrentOrigin->x;
    v36 = v35 - this->mCurrentOrigin.y;
    v37 = corner.z - this->mCurrentOrigin.z;
    v41 = corner.x * this->mCurrentAxisTransposed.mat[0].x
        + v37 * this->mCurrentAxisTransposed.mat[2].x
        + v36 * this->mCurrentAxisTransposed.mat[1].x;
    v42 = corner.x * this->mCurrentAxisTransposed.mat[0].y
        + v37 * this->mCurrentAxisTransposed.mat[2].y
        + v36 * this->mCurrentAxisTransposed.mat[1].y;
    v38 = v37 * this->mCurrentAxisTransposed.mat[2].z
        + v36 * this->mCurrentAxisTransposed.mat[1].z
        + corner.x * this->mCurrentAxisTransposed.mat[0].z;
    if ( v41 < (double)this->mCurrentLocalBounds.b[0].x )
      this->mCurrentLocalBounds.b[0].x = v41;
    if ( v41 > (double)this->mCurrentLocalBounds.b[1].x )
      this->mCurrentLocalBounds.b[1].x = v41;
    if ( v42 < (double)this->mCurrentLocalBounds.b[0].y )
      this->mCurrentLocalBounds.b[0].y = v42;
    if ( v42 > (double)this->mCurrentLocalBounds.b[1].y )
      this->mCurrentLocalBounds.b[1].y = v42;
    if ( v38 < this->mCurrentLocalBounds.b[0].z )
      this->mCurrentLocalBounds.b[0].z = v38;
    if ( v38 > this->mCurrentLocalBounds.b[1].z )
      this->mCurrentLocalBounds.b[1].z = v38;
    ++v33;
  }
  while ( v33 < 8 );
  this->mTint.x = parms->shaderParms[0];
  this->mTint.y = parms->shaderParms[1];
  this->mTint.z = parms->shaderParms[2];
  this->mTint.w = parms->shaderParms[3];
  this->mBrightness = parms->shaderParms[6];
  this->mSpriteSize.x = parms->shaderParms[8];
  this->mSpriteSize.y = parms->shaderParms[9];
  this->mAttenuation = parms->attenuation;
}

// FUNC: public: void __thiscall rvBSE::UpdateAttenuation(void)
void __thiscall rvBSE::UpdateAttenuation(rvBSE *this)
{
  double v2; // st7
  double v3; // st7
  double v4; // st6
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double v8; // st7
  float v9; // [esp+8h] [ebp-44h]
  float v10; // [esp+Ch] [ebp-40h]
  float v11; // [esp+Ch] [ebp-40h]
  idVec3 origin; // [esp+10h] [ebp-3Ch] BYREF
  idVec3 localOrigin; // [esp+1Ch] [ebp-30h] BYREF
  idMat3 axis; // [esp+28h] [ebp-24h] BYREF

  if ( (this->mDeclEffect->mFlags & 4) != 0 )
  {
    game->GetPlayerView(game, &origin, &axis);
    v2 = idVec3::Dist(&this->mCurrentOrigin, &origin);
    if ( v2 >= 1.0 )
    {
      if ( v2 > 131072.0 )
        v2 = 131072.0;
    }
    else
    {
      v2 = 1.0;
    }
    this->mOriginDistanceToCamera = v2;
    v3 = origin.x - this->mCurrentOrigin.x;
    v9 = origin.y - this->mCurrentOrigin.y;
    v4 = origin.z - this->mCurrentOrigin.z;
    v10 = v4;
    v5 = v4 * this->mCurrentAxis.mat[2].x + v9 * this->mCurrentAxis.mat[1].x + v3 * this->mCurrentAxis.mat[0].x;
    v6 = v10 * this->mCurrentAxis.mat[2].z + v9 * this->mCurrentAxis.mat[1].z + v3 * this->mCurrentAxis.mat[0].z;
    v7 = v10 * this->mCurrentAxis.mat[2].y + v9 * this->mCurrentAxis.mat[1].y + v3 * this->mCurrentAxis.mat[0].y;
    v11 = v6;
    localOrigin.z = v11;
    localOrigin.x = v5;
    localOrigin.y = v7;
    v8 = idBounds::ShortestDistance(&this->mCurrentLocalBounds, &localOrigin);
    if ( v8 >= 1.0 )
    {
      if ( v8 > 131072.0 )
        v8 = 131072.0;
      this->mShortestDistanceToCamera = v8;
    }
    else
    {
      this->mShortestDistanceToCamera = 1.0;
    }
  }
}

// FUNC: public: void __thiscall rvBSE::LoopInstant(float)
void __thiscall rvBSE::LoopInstant(rvBSE *this, float time)
{
  int v3; // edi
  bool v4; // cc
  int v5; // ebx

  if ( this->mDuration == 0.0 )
  {
    v3 = 0;
    v4 = this->mSegments.num <= 0;
    this->mStartTime = this->mDeclEffect->mMaxDuration + this->mStartTime + 0.5;
    if ( !v4 )
    {
      v5 = 0;
      do
      {
        rvSegment::ResetTime(&this->mSegments.list[v5], this, this->mStartTime);
        ++v3;
        ++v5;
      }
      while ( v3 < this->mSegments.num );
    }
    if ( bse_debug.internalVar->integerValue == 2 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "BSE: Looping duration: %g\n",
        this->mDeclEffect->mMaxDuration + 0.5);
    ++this->mDeclEffect->mLoopCount;
  }
}

// FUNC: public: void __thiscall rvBSE::LoopLooping(float)
void __thiscall rvBSE::LoopLooping(rvBSE *this, float time)
{
  int v3; // ebx
  int v4; // edi
  bool v5; // cc

  if ( this->mDuration != 0.0 )
  {
    v3 = 0;
    v4 = 0;
    v5 = this->mSegments.num <= 0;
    this->mStartTime = this->mDuration + this->mStartTime;
    this->mDuration = 0.0;
    if ( !v5 )
    {
      do
      {
        rvSegment::ResetTime(&this->mSegments.list[v3], this, this->mStartTime);
        ++v4;
        ++v3;
      }
      while ( v4 < this->mSegments.num );
    }
    if ( bse_debug.internalVar->integerValue == 2 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "BSE: Looping duration: %g\n",
        this->mDuration);
    ++this->mDeclEffect->mLoopCount;
  }
}

// FUNC: public: bool __thiscall rvBSE::Service(struct renderEffect_s *,float)
bool __thiscall rvBSE::Service(rvBSE *this, renderEffect_s *parms, float time)
{
  renderEffect_s *v3; // ebx
  int v5; // edi
  int v6; // ebx
  int v7; // edi
  int v8; // ebx
  bool active; // [esp+13h] [ebp-1h]

  v3 = parms;
  rvBSE::UpdateFromOwner(this, parms, time, 0);
  rvBSE::UpdateAttenuation(this);
  dword_1137DDB8 += this->mSegments.num;
  v5 = 0;
  if ( this->mSegments.num > 0 )
  {
    v6 = 0;
    do
    {
      rvSegment::Check(&this->mSegments.list[v6], this, time);
      ++v5;
      ++v6;
    }
    while ( v5 < this->mSegments.num );
    v3 = parms;
  }
  if ( (this->mFlags & 8) == 0 && v3->loop && this->mDuration + this->mStartTime < time )
    rvBSE::LoopLooping(this, time);
  v7 = 0;
  active = 0;
  if ( this->mSegments.num > 0 )
  {
    v8 = 0;
    do
    {
      if ( rvSegment::UpdateParticles(&this->mSegments.list[v8], this, time) )
        active = 1;
      ++v7;
      ++v8;
    }
    while ( v7 < this->mSegments.num );
    v3 = parms;
  }
  this->mFlags &= ~4u;
  if ( (this->mFlags & 8) != 0 )
    return !active;
  if ( v3->loop )
  {
    if ( this->mDuration + this->mStartTime < time )
      rvBSE::LoopInstant(this, time);
    if ( v3->loop )
      return 0;
  }
  return this->mDuration + this->mStartTime < time;
}

// FUNC: public: float __thiscall rvBSE::EvaluateCost(int)
double __thiscall rvBSE::EvaluateCost(rvBSE *this, int segment)
{
  int v4; // ebx
  int v5; // edi
  bool v6; // cc
  double v7; // st7

  if ( segment != -1 )
    return rvSegment::EvaluateCost(this->mSegments.list);
  v4 = 0;
  v5 = 0;
  v6 = this->mSegments.num <= 0;
  this->mCost = 0.0;
  if ( !v6 )
  {
    do
    {
      v7 = rvSegment::EvaluateCost(&this->mSegments.list[v4]);
      ++v5;
      ++v4;
      this->mCost = v7 + this->mCost;
    }
    while ( v5 < this->mSegments.num );
  }
  return this->mCost;
}

// FUNC: public: void __thiscall rvBSE::DisplayDebugInfo(struct renderEffect_s const *,struct viewDef_s const *,class idBounds &)
void __thiscall rvBSE::DisplayDebugInfo(
        rvBSE *this,
        const renderEffect_s *parms,
        const viewDef_s *view,
        idBounds *bounds)
{
  int integerValue; // eax
  rvBSE *v5; // ebx
  rvDeclEffect *mDeclEffect; // eax
  int mSize_low; // ecx
  idDeclBase *base; // eax
  idDeclBase_vtbl *v9; // edx
  const char *v10; // eax
  char *v11; // eax
  double v12; // st7
  double v13; // st6
  double v14; // st5
  double v15; // rt0
  double v16; // st6
  double v17; // st5
  double v18; // st4
  double v19; // st5
  double v20; // st7
  double v21; // st6
  double v22; // st5
  double v23; // st7
  float z; // edx
  float v25; // edx
  idRenderWorldLocal *renderWorld; // ecx
  int v27; // ecx
  int v28; // esi
  int v29; // ebp
  int v30; // ebx
  int v31; // ecx
  idVec3 transformed; // [esp+34h] [ebp-F8h] BYREF
  int i; // [esp+40h] [ebp-ECh]
  idVec3 v; // [esp+44h] [ebp-E8h] BYREF
  idBounds globalBounds; // [esp+50h] [ebp-DCh] BYREF
  idBounds modelBounds; // [esp+68h] [ebp-C4h] BYREF
  rvBSE *v37; // [esp+80h] [ebp-ACh]
  int v38[15]; // [esp+84h] [ebp-A8h] BYREF
  idStr work; // [esp+C0h] [ebp-6Ch] BYREF
  float modelMatrix[16]; // [esp+E0h] [ebp-4Ch] BYREF
  int v41; // [esp+128h] [ebp-4h]

  integerValue = bse_debug.internalVar->integerValue;
  v5 = this;
  v37 = this;
  if ( integerValue )
  {
    work.len = 0;
    work.alloced = 20;
    work.data = work.baseBuffer;
    work.baseBuffer[0] = 0;
    mDeclEffect = this->mDeclEffect;
    v41 = 0;
    mSize_low = SLODWORD(mDeclEffect->mSize);
    base = mDeclEffect->base;
    v9 = base->__vftable;
    i = mSize_low;
    v10 = v9->GetName(base);
    v11 = va("(%g) (%g) (%g)\n%s", v5->mCost, *(float *)&i, parms->shaderParms[6], v10);
    idStr::operator=(&work, v11);
    view->renderWorld->DebugAxis(view->renderWorld, &parms->origin, &parms->axis);
    ((void (__thiscall *)(idRenderWorldLocal *, char *, idVec3 *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))view->renderWorld->DrawTextA)(
      view->renderWorld,
      work.data,
      &parms->origin,
      1050253722,
      &colorCyan,
      &view->renderView.viewaxis,
      1,
      0,
      0);
    v41 = -1;
    idStr::FreeData(&work);
  }
  if ( bse_showBounds.internalVar->integerValue )
  {
    v12 = bounds->b[1].x + bounds->b[0].x;
    v38[6] = LODWORD(parms->axis.mat[0].x);
    v13 = bounds->b[1].y + bounds->b[0].y;
    v38[9] = LODWORD(parms->axis.mat[1].x);
    v14 = bounds->b[1].z + bounds->b[0].z;
    v38[12] = LODWORD(parms->axis.mat[2].x);
    transformed.z = v14;
    v15 = v13;
    v.x = v12 * 0.5;
    v16 = transformed.z * 0.5;
    v17 = bounds->b[1].x - v.x;
    v18 = bounds->b[1].y - v15 * 0.5;
    transformed.z = bounds->b[1].z - v16;
    v38[5] = LODWORD(transformed.z);
    *(float *)&v38[3] = v17;
    v38[7] = LODWORD(parms->axis.mat[0].y);
    *(float *)&v38[4] = v18;
    v38[10] = LODWORD(parms->axis.mat[1].y);
    v19 = v16 * parms->axis.mat[2].x;
    v38[13] = LODWORD(parms->axis.mat[2].y);
    transformed.x = v19 + v15 * 0.5 * parms->axis.mat[1].x + v.x * parms->axis.mat[0].x;
    transformed.y = v16 * parms->axis.mat[2].y + v15 * 0.5 * parms->axis.mat[1].y + v.x * parms->axis.mat[0].y;
    v20 = v16 * parms->axis.mat[2].z + v15 * 0.5 * parms->axis.mat[1].z + v.x * parms->axis.mat[0].z;
    v21 = transformed.x + parms->origin.x;
    v22 = v20;
    v23 = transformed.y + parms->origin.y;
    v.z = v22 + parms->origin.z;
    v38[2] = LODWORD(v.z);
    z = parms->axis.mat[0].z;
    *(float *)v38 = v21;
    *(float *)&v38[8] = z;
    v25 = parms->axis.mat[1].z;
    *(float *)&v38[1] = v23;
    *(float *)&v38[11] = v25;
    renderWorld = view->renderWorld;
    v38[14] = LODWORD(parms->axis.mat[2].z);
    renderWorld->DebugBox(renderWorld, &colorBlue, (const idBox *)v38, 0);
    R_AxisToModelMatrix(&parms->axis, &parms->origin, modelMatrix);
    globalBounds.b[1].z = -1.0e30;
    globalBounds.b[1].y = globalBounds.b[1].z;
    globalBounds.b[1].x = globalBounds.b[1].z;
    globalBounds.b[0].x = idMath::INFINITY;
    modelBounds.b[0].x = idMath::INFINITY;
    v27 = 0;
    modelBounds.b[1].z = globalBounds.b[1].z;
    modelBounds.b[1].y = globalBounds.b[1].z;
    globalBounds.b[0].z = idMath::INFINITY;
    modelBounds.b[1].x = globalBounds.b[1].z;
    globalBounds.b[0].y = idMath::INFINITY;
    modelBounds.b[0].z = idMath::INFINITY;
    modelBounds.b[0].y = idMath::INFINITY;
    *(float *)&i = 0.0;
    while ( 1 )
    {
      v28 = v27 & 1;
      v.x = v5->mCurrentLocalBounds.b[v28].x;
      v29 = (v27 >> 1) & 1;
      v.y = v5->mCurrentLocalBounds.b[v29].y;
      v30 = (v27 >> 2) & 1;
      v.z = v37->mCurrentLocalBounds.b[v30].z;
      R_LocalPointToGlobal(modelMatrix, &v, &transformed);
      if ( transformed.x < (double)globalBounds.b[0].x )
        globalBounds.b[0].x = transformed.x;
      if ( transformed.x > (double)globalBounds.b[1].x )
        globalBounds.b[1].x = transformed.x;
      if ( transformed.y < (double)globalBounds.b[0].y )
        globalBounds.b[0].y = transformed.y;
      if ( transformed.y > (double)globalBounds.b[1].y )
        globalBounds.b[1].y = transformed.y;
      if ( transformed.z < (double)globalBounds.b[0].z )
        globalBounds.b[0].z = transformed.z;
      if ( transformed.z > (double)globalBounds.b[1].z )
        globalBounds.b[1].z = transformed.z;
      v.x = bounds->b[v28].x;
      v.y = bounds->b[v29].y;
      v.z = bounds->b[v30].z;
      R_LocalPointToGlobal(modelMatrix, &v, &transformed);
      if ( transformed.x < (double)modelBounds.b[0].x )
        modelBounds.b[0].x = transformed.x;
      if ( transformed.x > (double)modelBounds.b[1].x )
        modelBounds.b[1].x = transformed.x;
      if ( transformed.y < (double)modelBounds.b[0].y )
        modelBounds.b[0].y = transformed.y;
      if ( transformed.y > (double)modelBounds.b[1].y )
        modelBounds.b[1].y = transformed.y;
      if ( transformed.z < (double)modelBounds.b[0].z )
        modelBounds.b[0].z = transformed.z;
      if ( transformed.z > (double)modelBounds.b[1].z )
        modelBounds.b[1].z = transformed.z;
      if ( ++i >= 8 )
        break;
      v5 = v37;
      v27 = i;
    }
    view->renderWorld->DebugBounds(view->renderWorld, &colorGreen, &globalBounds, &vec3_origin, 0, 0);
    v31 = 0;
    while ( *(float *)((char *)&modelBounds.b[1].x + v31) <= (double)*(float *)((char *)&globalBounds.b[1].x + v31)
         && *(float *)((char *)&modelBounds.b[0].x + v31) >= (double)*(float *)((char *)&globalBounds.b[0].x + v31) )
    {
      v31 += 4;
      if ( v31 >= 12 )
        return;
    }
    view->renderWorld->DebugBounds(view->renderWorld, &colorRed, &modelBounds, &vec3_origin, 0, 0);
  }
}

// FUNC: public: class idRenderModel * __thiscall rvBSE::Render(struct renderEffect_s const *,struct viewDef_s const *)
rvRenderModelBSE *__thiscall rvBSE::Render(rvBSE *this, const renderEffect_s *owner, const viewDef_s *view)
{
  int v3; // ebx
  rvRenderModelBSE *v6; // eax
  rvRenderModelBSE *v7; // eax
  rvRenderModelBSE *v8; // ebp
  const viewDef_s *viewa; // [esp+20h] [ebp+8h]

  v3 = 0;
  if ( !bse_render.internalVar->integerValue )
    return 0;
  v6 = (rvRenderModelBSE *)Memory::Allocate(0x70u);
  if ( v6 )
  {
    rvRenderModelBSE::rvRenderModelBSE(v6);
    v8 = v7;
  }
  else
  {
    v8 = 0;
  }
  this->mViewAxis = view->renderView.viewaxis;
  this->mViewOrg = view->renderView.vieworg;
  for ( viewa = 0; (int)viewa < this->mSegments.num; viewa = (const viewDef_s *)((char *)viewa + 1) )
  {
    if ( rvSegment::Active(&this->mSegments.list[v3]) )
    {
      rvSegment::Render(&this->mSegments.list[v3], this, owner, v8, view->floatTime);
      rvSegment::RenderTrail(&this->mSegments.list[v3], this, owner, v8, view->floatTime);
    }
    ++v3;
  }
  rvBSE::DisplayDebugInfo(this, owner, view, &v8->bounds);
  return v8;
}

// FUNC: public: void __thiscall rvBSE::Destroy(void)
void __thiscall rvBSE::Destroy(rvBSE *this)
{
  idSoundEmitter *v2; // eax
  idSoundEmitter *v3; // esi
  idSoundSystem_vtbl *v4; // ebp
  int v5; // eax
  rvSegment *list; // eax
  rvParticle **p_mParticles; // esi

  v2 = soundSystem->EmitterForIndex(soundSystem, 1, this->mReferenceSoundHandle);
  v3 = v2;
  if ( v2 )
  {
    v2->StopSound(v2, 0);
    v4 = soundSystem->__vftable;
    v5 = ((int (__thiscall *)(idSoundEmitter *, int))v3->Handle)(v3, 1);
    ((void (__thiscall *)(idSoundSystem *, int, int))v4->FreeSoundEmitter)(soundSystem, 1, v5);
  }
  list = this->mSegments.list;
  if ( list )
  {
    p_mParticles = &list[-1].mParticles;
    `eh vector destructor iterator'(
      list,
      0x48u,
      (int)list[-1].mParticles,
      (void (__thiscall *)(void *))rvSegment::~rvSegment);
    Memory::Free(p_mParticles);
  }
  this->mSegments.list = 0;
  this->mSegments.num = 0;
  this->mSegments.size = 0;
}

// FUNC: public: void __thiscall rvBSE::UpdateSegments(float)
void __thiscall rvBSE::UpdateSegments(rvBSE *this, float time)
{
  int num; // ebx
  idList<rvSegment> *p_mSegments; // edi
  int v5; // ebx
  int v6; // ebp
  int v7; // ebx
  int v8; // ebp
  int v9; // ebx
  int v10; // ebp
  int v11; // ebx
  bool v12; // cc
  int v13; // ebp
  int v14; // ebx
  double v15; // st7
  int v16; // ebp

  num = this->mDeclEffect->mSegmentTemplates.num;
  p_mSegments = &this->mSegments;
  idList<rvSegment>::Resize(&this->mSegments, num);
  p_mSegments->num = num;
  v5 = 0;
  if ( p_mSegments->num > 0 )
  {
    v6 = 0;
    do
      rvSegment::Init(&this->mSegments.list[v6++], this, this->mDeclEffect, v5++, time);
    while ( v5 < p_mSegments->num );
  }
  v7 = 0;
  if ( p_mSegments->num > 0 )
  {
    v8 = 0;
    do
    {
      rvSegment::CalcCounts(&this->mSegments.list[v8], this, time);
      ++v7;
      ++v8;
    }
    while ( v7 < p_mSegments->num );
  }
  v9 = 0;
  if ( p_mSegments->num > 0 )
  {
    v10 = 0;
    do
    {
      rvSegment::InitParticles(&this->mSegments.list[v10], this);
      ++v9;
      ++v10;
    }
    while ( v9 < p_mSegments->num );
  }
  if ( (this->mFlags & 1) != 0 && (this->mFlags & 0x10) != 0 && this->mDuration != 0.0 )
  {
    while ( time - (this->mDuration + this->mDuration) > this->mStartTime )
    {
      v11 = 0;
      v12 = p_mSegments->num <= 0;
      this->mStartTime = this->mDuration + this->mStartTime;
      if ( !v12 )
      {
        v13 = 0;
        do
        {
          rvSegment::Advance(&this->mSegments.list[v13], this);
          ++v11;
          ++v13;
        }
        while ( v11 < p_mSegments->num );
      }
    }
    v14 = 0;
    v12 = p_mSegments->num <= 0;
    v15 = this->mDuration + this->mDuration;
    this->mCurrentTime = this->mCurrentTime - v15;
    this->mStartTime = this->mStartTime - v15;
    if ( !v12 )
    {
      v16 = 0;
      do
      {
        rvSegment::Rewind(&this->mSegments.list[v16], this);
        ++v14;
        ++v16;
      }
      while ( v14 < p_mSegments->num );
    }
  }
}

// FUNC: public: void __thiscall rvBSE::Init(class rvDeclEffect *,struct renderEffect_s *,float)
void __thiscall rvBSE::Init(rvBSE *this, rvDeclEffect *declEffect, renderEffect_s *parms, float time)
{
  double mSize; // st7
  float *p_z; // ecx
  float *v7; // eax
  int v8; // edx
  float *v9; // ecx
  double v10; // st7
  double v11; // st6
  double x; // st5
  double v13; // st5
  double v14; // st4
  float *p_y; // eax
  float z; // eax
  renderEffect_s *v17; // [esp-Ch] [ebp-4Ch]
  float v18; // [esp-8h] [ebp-48h]
  bool v19; // [esp-4h] [ebp-44h]
  float v20; // [esp+18h] [ebp-28h]
  float v21; // [esp+24h] [ebp-1Ch]
  float v22; // [esp+28h] [ebp-18h] BYREF
  float v23[5]; // [esp+2Ch] [ebp-14h] BYREF
  int declEffecta; // [esp+44h] [ebp+4h]

  this->mFlags = 0;
  this->mDeclEffect = declEffect;
  this->mStartTime = parms->startTime;
  this->mLastTime = time;
  this->mDuration = 0.0;
  this->mAttenuation = 1.0;
  this->mCost = 0.0;
  this->mFlags = parms->loop;
  if ( parms->ambient )
    this->mFlags |= 0x10u;
  else
    this->mFlags &= ~0x10u;
  this->mCurrentLocalBounds.b[1].z = 0.0;
  this->mCurrentLocalBounds.b[1].y = 0.0;
  this->mCurrentLocalBounds.b[1].x = 0.0;
  this->mCurrentLocalBounds.b[0].z = 0.0;
  this->mCurrentLocalBounds.b[0].y = 0.0;
  this->mCurrentLocalBounds.b[0].x = 0.0;
  mSize = declEffect->mSize;
  this->mCurrentLocalBounds.b[0].x = this->mCurrentLocalBounds.b[0].x - mSize;
  this->mCurrentLocalBounds.b[0].y = this->mCurrentLocalBounds.b[0].y - mSize;
  this->mCurrentLocalBounds.b[0].z = this->mCurrentLocalBounds.b[0].z - mSize;
  this->mCurrentLocalBounds.b[1].x = mSize + this->mCurrentLocalBounds.b[1].x;
  this->mCurrentLocalBounds.b[1].y = mSize + this->mCurrentLocalBounds.b[1].y;
  this->mCurrentLocalBounds.b[1].z = mSize + this->mCurrentLocalBounds.b[1].z;
  this->mOriginalOrigin = parms->origin;
  this->mOriginalEndOrigin.z = 0.0;
  this->mOriginalEndOrigin.y = 0.0;
  this->mOriginalEndOrigin.x = 0.0;
  p_z = &this->mOriginalAxis.mat[0].z;
  v7 = &parms->axis.mat[0].z;
  v8 = 3;
  do
  {
    *(p_z - 2) = *(v7 - 2);
    *(p_z - 1) = *(v7 - 1);
    *p_z = *v7;
    v7 += 3;
    p_z += 3;
    --v8;
  }
  while ( v8 );
  v9 = &v22;
  v10 = this->mCurrentLocalBounds.b[1].x + this->mOriginalOrigin.x;
  declEffecta = 2;
  v11 = this->mCurrentLocalBounds.b[1].y + this->mOriginalOrigin.y;
  v21 = this->mCurrentLocalBounds.b[1].z + this->mOriginalOrigin.z;
  x = this->mCurrentLocalBounds.b[0].x;
  v23[4] = v21;
  v13 = x + this->mOriginalOrigin.x;
  v14 = this->mCurrentLocalBounds.b[0].y + this->mOriginalOrigin.y;
  v20 = this->mCurrentLocalBounds.b[0].z + this->mOriginalOrigin.z;
  v23[1] = v20;
  v22 = v13;
  v23[0] = v14;
  v23[2] = v10;
  p_y = &this->mCurrentWorldBounds.b[0].y;
  v23[3] = v11;
  do
  {
    *(p_y - 1) = *v9;
    *p_y = *(float *)((char *)p_y + (char *)&v22 - (char *)&this->mCurrentWorldBounds);
    p_y[1] = *(float *)((char *)p_y + (char *)v23 - (char *)&this->mCurrentWorldBounds);
    v9 += 3;
    p_y += 3;
    --declEffecta;
  }
  while ( declEffecta );
  if ( parms->hasEndOrigin )
  {
    this->mFlags |= 2u;
    this->mOriginalEndOrigin = parms->endOrigin;
    this->mCurrentEndOrigin = parms->endOrigin;
  }
  this->mCurrentTime = time;
  this->mCurrentOrigin.x = this->mOriginalOrigin.x;
  this->mCurrentOrigin.y = this->mOriginalOrigin.y;
  z = this->mOriginalOrigin.z;
  v19 = 1;
  this->mCurrentOrigin.z = z;
  v18 = time;
  v17 = parms;
  this->mCurrentVelocity.z = 0.0;
  this->mCurrentVelocity.y = 0.0;
  this->mCurrentVelocity.x = 0.0;
  rvBSE::UpdateFromOwner(this, v17, v18, v19);
  this->mReferenceSoundHandle = parms->referenceSoundHandle;
  rvBSE::UpdateSegments(this, time);
  this->mOriginDistanceToCamera = 0.0;
  this->mShortestDistanceToCamera = 0.0;
  this->mSpriteSize.y = 0.0;
  this->mSpriteSize.x = 0.0;
}
