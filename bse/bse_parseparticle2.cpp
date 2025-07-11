
// FUNC: public: bool __thiscall rvParticleTemplate::UsesEndOrigin(void)
bool __thiscall rvParticleTemplate::UsesEndOrigin(rvParticleTemplate *this)
{
  return (this->mSpawnPosition.mFlags & 2) != 0 || (this->mSpawnLength.mFlags & 2) != 0;
}

// FUNC: public: void __thiscall rvParticleTemplate::SetParameterCounts(void)
void __thiscall rvParticleTemplate::SetParameterCounts(rvParticleTemplate *this)
{
  int v1; // eax
  int v2; // edx

  switch ( this->mType )
  {
    case 1:
    case 4:
      this->mNumSizeParms = 2;
      v1 = 1;
      v2 = 6;
      goto LABEL_9;
    case 2:
    case 7:
    case 8:
      this->mNumSizeParms = 1;
      v1 = 0;
      v2 = 5;
      goto LABEL_9;
    case 3:
      this->mNumSizeParms = 2;
      v2 = 6;
      goto LABEL_8;
    case 5:
      v1 = 3;
      this->mNumSizeParms = 3;
      v2 = 7;
      goto LABEL_9;
    case 6:
      this->mNumSizeParms = 3;
      v1 = 0;
      v2 = 7;
      goto LABEL_9;
    case 9:
      this->mNumSizeParms = 0;
      v2 = 7;
LABEL_8:
      v1 = 3;
LABEL_9:
      this->mNumRotateParms = v1;
      this->mSpawnSize.mSpawnType = v2;
      this->mSpawnRotate.mSpawnType = v1;
      this->mDeathSize.mSpawnType = v2;
      this->mDeathRotate.mSpawnType = v1;
      break;
    default:
      return;
  }
}

// FUNC: public: float __thiscall rvParticleTemplate::GetSpawnVolume(class rvBSE *)
double __thiscall rvParticleTemplate::GetSpawnVolume(rvParticleTemplate *this, rvBSE *effect)
{
  double v2; // st5
  double v3; // st4
  double v4; // st2
  double v5; // st7
  float v7; // [esp+4h] [ebp-14h]
  float v8; // [esp+8h] [ebp-10h]

  if ( (this->mSpawnPosition.mFlags & 2) != 0 )
  {
    v2 = effect->mOriginalEndOrigin.y - effect->mOriginalOrigin.y;
    v3 = effect->mOriginalEndOrigin.z - effect->mOriginalOrigin.z;
    v4 = effect->mOriginalEndOrigin.x - effect->mOriginalOrigin.x;
    v5 = sqrt(v3 * v3 + v2 * v2 + v4 * v4) - this->mSpawnPosition.mMins.x;
  }
  else
  {
    v5 = this->mSpawnPosition.mMaxs.x - this->mSpawnPosition.mMins.x;
  }
  v7 = this->mSpawnPosition.mMaxs.y - this->mSpawnPosition.mMins.y;
  v8 = this->mSpawnPosition.mMaxs.z - this->mSpawnPosition.mMins.z;
  return (v5 + v8 + v7) * 0.0099999998;
}

// FUNC: public: float __thiscall rvParticleTemplate::CostTrail(float)
double __thiscall rvParticleTemplate::CostTrail(rvParticleTemplate *this, float cost)
{
  double v2; // st7
  double result; // st7

  switch ( this->mTrailType )
  {
    case 1:
      v2 = cost * this->mTrailCount.y;
      result = v2 + v2;
      break;
    case 2:
      result = cost * this->mTrailCount.y * 1.5 + 20.0;
      break;
    default:
      result = cost;
      break;
  }
  return result;
}

// FUNC: public: void __thiscall rvParticleTemplate::FixupParms(class rvParticleParms &)
void __thiscall rvParticleTemplate::FixupParms(rvParticleTemplate *this, rvParticleParms *parms)
{
  rvParticleParms *v2; // edi
  int mSpawnType; // ecx
  int v4; // esi
  int v5; // eax
  idVec3 *p_mMaxs; // ebx
  idVec3 *p_mMins; // ebp
  int v8; // ecx
  idVec3 *v9; // edx

  v2 = parms;
  mSpawnType = parms->mSpawnType;
  v4 = parms->mSpawnType & 3;
  v5 = 4 * (parms->mSpawnType >> 2);
  if ( !v5 || v5 == 4 || mSpawnType == 43 || mSpawnType == 47 )
    return;
  p_mMaxs = &parms->mMaxs;
  p_mMins = &parms->mMins;
  if ( ((parms->mSpawnType & 3u) < 2 || parms->mMins.y == p_mMins->x)
    && ((parms->mSpawnType & 3) != 3 || parms->mMins.z == p_mMins->x)
    && (v5 == 8
     || p_mMaxs->x == p_mMins->x
     && ((parms->mSpawnType & 3u) < 2 || parms->mMaxs.y == p_mMins->x)
     && ((parms->mSpawnType & 3) != 3 || parms->mMaxs.z == p_mMins->x)) )
  {
    if ( p_mMins->x == 0.0 )
    {
      parms->mSpawnType = v4;
    }
    else if ( LODWORD(p_mMins->x) == 1065353216 )
    {
      parms->mSpawnType = v4 + 4;
    }
    else
    {
      parms->mSpawnType = v4 + 8;
    }
  }
  else
  {
    if ( v5 == 8 )
      goto LABEL_30;
    v8 = 0;
    if ( (parms->mSpawnType & 3) == 0 )
      goto LABEL_23;
    v9 = &parms->mMaxs;
    while ( *(float *)((char *)&v9->x + (char *)p_mMins - (char *)p_mMaxs) == v9->x )
    {
      ++v8;
      v9 = (idVec3 *)((char *)v9 + 4);
      if ( v8 >= v4 )
      {
        v2 = parms;
        parms->mSpawnType = v4 + 8;
        goto LABEL_30;
      }
    }
    if ( v8 >= v4 )
    {
      v2 = parms;
LABEL_23:
      v2->mSpawnType = v4 + 8;
      goto LABEL_30;
    }
    v2 = parms;
  }
LABEL_30:
  if ( v2->mSpawnType >= 8 )
  {
    if ( v4 == 1 )
    {
      parms->mMins.y = 0.0;
      parms->mMaxs.y = 0.0;
    }
    else if ( v4 != 2 )
    {
      goto LABEL_36;
    }
    parms->mMins.z = 0.0;
    parms->mMaxs.z = 0.0;
    goto LABEL_36;
  }
  parms->mMins.z = 0.0;
  parms->mMins.y = 0.0;
  p_mMins->x = 0.0;
LABEL_36:
  if ( v2->mSpawnType <= 11 )
  {
    p_mMaxs->x = p_mMins->x;
    parms->mMaxs.y = parms->mMins.y;
    parms->mMaxs.z = parms->mMins.z;
  }
  if ( (v2->mFlags & 2) != 0 && v2->mSpawnType <= 12 )
    v2->mSpawnType = v4 + 12;
}

// FUNC: public: void __thiscall rvParticleTemplate::Init(void)
void __thiscall rvParticleTemplate::Init(rvParticleTemplate *this)
{
  double v2; // st7
  double y; // st6
  float v4; // [esp+14h] [ebp-4h]

  this->mFlags = 0;
  this->mType = 0;
  idStr::operator=(&this->mMaterialName, "_default");
  this->mMaterial = declManager->FindMaterial(declManager, "_default", 1);
  idStr::operator=(&this->mModelName, "_default");
  this->mTraceModelIndex = -1;
  this->mGravity.y = 0.0;
  this->mGravity.x = 0.0;
  this->mSoundVolume.y = 0.0;
  this->mSoundVolume.x = 0.0;
  this->mFreqShift.y = 0.0;
  this->mFreqShift.x = 0.0;
  this->mTiling = 8.0;
  this->mTrailType = 0;
  this->mTrailMaterial = declManager->FindMaterial(declManager, "gfx/effects/particles_shapes/motionblur", 1);
  this->mTrailTime.y = 0.0;
  this->mTrailTime.x = 0.0;
  this->mTrailCount.y = 0.0;
  this->mTrailCount.x = 0.0;
  this->mBounce = 0.0;
  this->mDuration.x = 0.0020000001;
  this->mDuration.y = 0.0020000001;
  this->mCentre.z = 0.0;
  this->mCentre.y = 0.0;
  this->mCentre.x = 0.0;
  this->mNumForks = 0;
  this->mForkSizeMins.x = -20.0;
  this->mForkSizeMins.y = -20.0;
  this->mForkSizeMins.z = -20.0;
  v2 = -this->mForkSizeMins.x;
  y = this->mForkSizeMins.y;
  v4 = -this->mForkSizeMins.z;
  this->mForkSizeMaxs.z = v4;
  this->mForkSizeMaxs.x = v2;
  this->mForkSizeMaxs.y = -y;
  this->mJitterSize.x = 3.0;
  this->mJitterSize.y = 7.0;
  this->mJitterSize.z = 7.0;
  this->mJitterRate = 0.0;
  this->mJitterTable = (const idDeclTable *)declManager->FindType(declManager, 0, "halfsintable", 1, 0);
  this->mNumSizeParms = 2;
  this->mNumRotateParms = 1;
  this->mVertexCount = 4;
  this->mIndexCount = 6;
  this->mSpawnPosition.mSpawnType = 3;
  this->mSpawnPosition.mFlags = 0;
  this->mSpawnPosition.mRange = 0.0;
  this->mSpawnPosition.mMisc = 0;
  this->mSpawnPosition.mMins.z = 0.0;
  this->mSpawnPosition.mMins.y = 0.0;
  this->mSpawnPosition.mMins.x = 0.0;
  this->mSpawnPosition.mMaxs.z = 0.0;
  this->mSpawnPosition.mMaxs.y = 0.0;
  this->mSpawnPosition.mMaxs.x = 0.0;
  this->mSpawnDirection.mSpawnType = 3;
  this->mSpawnDirection.mFlags = 0;
  this->mSpawnDirection.mRange = 0.0;
  this->mSpawnDirection.mMisc = 0;
  this->mSpawnDirection.mMins.z = 0.0;
  this->mSpawnDirection.mMins.y = 0.0;
  this->mSpawnDirection.mMins.x = 0.0;
  this->mSpawnDirection.mMaxs.z = 0.0;
  this->mSpawnDirection.mMaxs.y = 0.0;
  this->mSpawnDirection.mMaxs.x = 0.0;
  this->mSpawnVelocity.mSpawnType = 3;
  this->mSpawnVelocity.mFlags = 0;
  this->mSpawnVelocity.mRange = 0.0;
  this->mSpawnVelocity.mMisc = 0;
  this->mSpawnVelocity.mMins.z = 0.0;
  this->mSpawnVelocity.mMins.y = 0.0;
  this->mSpawnVelocity.mMins.x = 0.0;
  this->mSpawnVelocity.mMaxs.z = 0.0;
  this->mSpawnVelocity.mMaxs.y = 0.0;
  this->mSpawnVelocity.mMaxs.x = 0.0;
  this->mSpawnAcceleration.mSpawnType = 3;
  this->mSpawnAcceleration.mFlags = 0;
  this->mSpawnAcceleration.mRange = 0.0;
  this->mSpawnAcceleration.mMisc = 0;
  this->mSpawnAcceleration.mMins.z = 0.0;
  this->mSpawnAcceleration.mMins.y = 0.0;
  this->mSpawnAcceleration.mMins.x = 0.0;
  this->mSpawnAcceleration.mMaxs.z = 0.0;
  this->mSpawnAcceleration.mMaxs.y = 0.0;
  this->mSpawnAcceleration.mMaxs.x = 0.0;
  this->mSpawnFriction.mSpawnType = 3;
  this->mSpawnFriction.mFlags = 0;
  this->mSpawnFriction.mRange = 0.0;
  this->mSpawnFriction.mMisc = 0;
  this->mSpawnFriction.mMins.z = 0.0;
  this->mSpawnFriction.mMins.y = 0.0;
  this->mSpawnFriction.mMins.x = 0.0;
  this->mSpawnFriction.mMaxs.z = 0.0;
  this->mSpawnFriction.mMaxs.y = 0.0;
  this->mSpawnFriction.mMaxs.x = 0.0;
  this->mSpawnTint.mSpawnType = 7;
  this->mSpawnTint.mFlags = 0;
  this->mSpawnTint.mRange = 0.0;
  this->mSpawnTint.mMisc = 0;
  this->mSpawnTint.mMins.z = 0.0;
  this->mSpawnTint.mMins.y = 0.0;
  this->mSpawnTint.mMins.x = 0.0;
  this->mSpawnTint.mMaxs.z = 0.0;
  this->mSpawnTint.mMaxs.y = 0.0;
  this->mSpawnTint.mMaxs.x = 0.0;
  this->mSpawnFade.mSpawnType = 5;
  this->mSpawnFade.mFlags = 0;
  this->mSpawnFade.mRange = 0.0;
  this->mSpawnFade.mMisc = 0;
  this->mSpawnFade.mMins.z = 0.0;
  this->mSpawnFade.mMins.y = 0.0;
  this->mSpawnFade.mMins.x = 0.0;
  this->mSpawnFade.mMaxs.z = 0.0;
  this->mSpawnFade.mMaxs.y = 0.0;
  this->mSpawnFade.mMaxs.x = 0.0;
  this->mSpawnSize.mSpawnType = 7;
  this->mSpawnSize.mFlags = 0;
  this->mSpawnSize.mRange = 0.0;
  this->mSpawnSize.mMisc = 0;
  this->mSpawnSize.mMins.z = 0.0;
  this->mSpawnSize.mMins.y = 0.0;
  this->mSpawnSize.mMins.x = 0.0;
  this->mSpawnSize.mMaxs.z = 0.0;
  this->mSpawnSize.mMaxs.y = 0.0;
  this->mSpawnSize.mMaxs.x = 0.0;
  this->mSpawnRotate.mSpawnType = 3;
  this->mSpawnRotate.mFlags = 0;
  this->mSpawnRotate.mRange = 0.0;
  this->mSpawnRotate.mMisc = 0;
  this->mSpawnRotate.mMins.z = 0.0;
  this->mSpawnRotate.mMins.y = 0.0;
  this->mSpawnRotate.mMins.x = 0.0;
  this->mSpawnRotate.mMaxs.z = 0.0;
  this->mSpawnRotate.mMaxs.y = 0.0;
  this->mSpawnRotate.mMaxs.x = 0.0;
  this->mSpawnAngle.mSpawnType = 3;
  this->mSpawnAngle.mFlags = 0;
  this->mSpawnAngle.mRange = 0.0;
  this->mSpawnAngle.mMisc = 0;
  this->mSpawnAngle.mMins.z = 0.0;
  this->mSpawnAngle.mMins.y = 0.0;
  this->mSpawnAngle.mMins.x = 0.0;
  this->mSpawnAngle.mMaxs.z = 0.0;
  this->mSpawnAngle.mMaxs.y = 0.0;
  this->mSpawnAngle.mMaxs.x = 0.0;
  this->mSpawnOffset.mSpawnType = 3;
  this->mSpawnOffset.mFlags = 0;
  this->mSpawnOffset.mRange = 0.0;
  this->mSpawnOffset.mMisc = 0;
  this->mSpawnOffset.mMins.z = 0.0;
  this->mSpawnOffset.mMins.y = 0.0;
  this->mSpawnOffset.mMins.x = 0.0;
  this->mSpawnOffset.mMaxs.z = 0.0;
  this->mSpawnOffset.mMaxs.y = 0.0;
  this->mSpawnOffset.mMaxs.x = 0.0;
  this->mSpawnLength.mSpawnType = 3;
  this->mSpawnLength.mFlags = 0;
  this->mSpawnLength.mRange = 0.0;
  this->mSpawnLength.mMisc = 0;
  this->mSpawnLength.mMins.z = 0.0;
  this->mSpawnLength.mMins.y = 0.0;
  this->mSpawnLength.mMins.x = 0.0;
  this->mSpawnLength.mMaxs.z = 0.0;
  this->mSpawnLength.mMaxs.y = 0.0;
  this->mSpawnLength.mMaxs.x = 0.0;
  rvEnvParms::Init(&this->mTintEnvelope);
  rvEnvParms::Init(&this->mFadeEnvelope);
  rvEnvParms::Init(&this->mSizeEnvelope);
  rvEnvParms::Init(&this->mRotateEnvelope);
  rvEnvParms::Init(&this->mAngleEnvelope);
  rvEnvParms::Init(&this->mOffsetEnvelope);
  rvEnvParms::Init(&this->mLengthEnvelope);
  this->mDeathTint.mSpawnType = 3;
  this->mDeathTint.mFlags = 0;
  this->mDeathTint.mRange = 0.0;
  this->mDeathTint.mMisc = 0;
  this->mDeathTint.mMins.z = 0.0;
  this->mDeathTint.mMins.y = 0.0;
  this->mDeathTint.mMins.x = 0.0;
  this->mDeathTint.mMaxs.z = 0.0;
  this->mDeathTint.mMaxs.y = 0.0;
  this->mDeathTint.mMaxs.x = 0.0;
  this->mDeathFade.mSpawnType = 1;
  this->mDeathFade.mFlags = 0;
  this->mDeathFade.mRange = 0.0;
  this->mDeathFade.mMisc = 0;
  this->mDeathFade.mMins.z = 0.0;
  this->mDeathFade.mMins.y = 0.0;
  this->mDeathFade.mMins.x = 0.0;
  this->mDeathFade.mMaxs.z = 0.0;
  this->mDeathFade.mMaxs.y = 0.0;
  this->mDeathFade.mMaxs.x = 0.0;
  this->mDeathSize.mSpawnType = 7;
  this->mDeathSize.mFlags = 0;
  this->mDeathSize.mRange = 0.0;
  this->mDeathSize.mMisc = 0;
  this->mDeathSize.mMins.z = 0.0;
  this->mDeathSize.mMins.y = 0.0;
  this->mDeathSize.mMins.x = 0.0;
  this->mDeathSize.mMaxs.z = 0.0;
  this->mDeathSize.mMaxs.y = 0.0;
  this->mDeathSize.mMaxs.x = 0.0;
  this->mDeathRotate.mSpawnType = 3;
  this->mDeathRotate.mFlags = 0;
  this->mDeathRotate.mRange = 0.0;
  this->mDeathRotate.mMisc = 0;
  this->mDeathRotate.mMins.z = 0.0;
  this->mDeathRotate.mMins.y = 0.0;
  this->mDeathRotate.mMins.x = 0.0;
  this->mDeathRotate.mMaxs.z = 0.0;
  this->mDeathRotate.mMaxs.y = 0.0;
  this->mDeathRotate.mMaxs.x = 0.0;
  this->mDeathAngle.mSpawnType = 3;
  this->mDeathAngle.mFlags = 0;
  this->mDeathAngle.mRange = 0.0;
  this->mDeathAngle.mMisc = 0;
  this->mDeathAngle.mMins.z = 0.0;
  this->mDeathAngle.mMins.y = 0.0;
  this->mDeathAngle.mMins.x = 0.0;
  this->mDeathAngle.mMaxs.z = 0.0;
  this->mDeathAngle.mMaxs.y = 0.0;
  this->mDeathAngle.mMaxs.x = 0.0;
  this->mDeathOffset.mSpawnType = 3;
  this->mDeathOffset.mFlags = 0;
  this->mDeathOffset.mRange = 0.0;
  this->mDeathOffset.mMisc = 0;
  this->mDeathOffset.mMins.z = 0.0;
  this->mDeathOffset.mMins.y = 0.0;
  this->mDeathOffset.mMins.x = 0.0;
  this->mDeathOffset.mMaxs.z = 0.0;
  this->mDeathOffset.mMaxs.y = 0.0;
  this->mDeathOffset.mMaxs.x = 0.0;
  this->mDeathLength.mSpawnType = 3;
  this->mDeathLength.mFlags = 0;
  this->mDeathLength.mRange = 0.0;
  this->mDeathLength.mMisc = 0;
  this->mDeathLength.mMins.z = 0.0;
  this->mDeathLength.mMins.y = 0.0;
  this->mDeathLength.mMins.x = 0.0;
  this->mDeathLength.mMaxs.z = 0.0;
  this->mDeathLength.mMaxs.y = 0.0;
  this->mDeathLength.mMaxs.x = 0.0;
  this->mNumImpactEffects = 0;
  this->mNumTimeoutEffects = 0;
  this->mImpactEffects[0] = 0;
  this->mTimeoutEffects[0] = 0;
  this->mImpactEffects[1] = 0;
  this->mTimeoutEffects[1] = 0;
  this->mImpactEffects[2] = 0;
  this->mTimeoutEffects[2] = 0;
  this->mImpactEffects[3] = 0;
  this->mTimeoutEffects[3] = 0;
}

// FUNC: public: class idTraceModel * __thiscall rvParticleTemplate::GetTraceModel(void)const
idTraceModel *__thiscall rvParticleTemplate::GetTraceModel(rvParticleTemplate *this)
{
  int mTraceModelIndex; // eax

  mTraceModelIndex = this->mTraceModelIndex;
  if ( mTraceModelIndex >= 0 )
    return rvBSEManagerLocal::mTraceModels.list[mTraceModelIndex];
  else
    return 0;
}

// FUNC: public: int __thiscall rvParticleTemplate::GetTrailCount(void)const
int __thiscall rvParticleTemplate::GetTrailCount(rvParticleTemplate *this)
{
  int count; // [esp+4h] [ebp-4h]

  count = (int)rvRandom::flrand(this->mTrailCount.x, this->mTrailCount.y);
  return count < 0 ? 0 : count;
}

// FUNC: public: bool __thiscall rvParticleTemplate::GetVector(class idLexer *,int,class idVec3 &)
char __thiscall rvParticleTemplate::GetVector(rvParticleTemplate *this, idLexer *lexer, int count, idVec3 *result)
{
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v6; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v6 = 0;
  if ( count > 0 )
  {
    result->x = idLexer::ParseFloat(lexer, 0);
    if ( count > 1 )
    {
      if ( !idLexer::ExpectTokenString(lexer, ",") )
      {
LABEL_6:
        v6 = -1;
        idStr::FreeData(&token);
        return 0;
      }
      result->y = idLexer::ParseFloat(lexer, 0);
      if ( count > 2 )
      {
        if ( !idLexer::ExpectTokenString(lexer, ",") )
          goto LABEL_6;
        result->z = idLexer::ParseFloat(lexer, 0);
      }
    }
  }
  v6 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: bool __thiscall rvParticleTemplate::ParseMotionParms(class idLexer *,int,class rvEnvParms &)
char __thiscall rvParticleTemplate::ParseMotionParms(
        rvParticleTemplate *this,
        idLexer *lexer,
        int count,
        rvEnvParms *envelope)
{
  rvParticleTemplate *v4; // ebx
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v8; // [esp+60h] [ebp-4h]

  v4 = this;
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v8 = 0;
  if ( idLexer::ExpectTokenString(lexer, "{") && idLexer::ReadToken(lexer, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "envelope") )
      {
        if ( idStr::Icmp(token.data, "rate") )
        {
          if ( idStr::Icmp(token.data, "count") )
          {
            if ( idStr::Icmp(token.data, "offset") )
            {
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
                common.type,
                "^4BSE:^1 Invalid motion parameter '%s' (file: %s, line: %d)",
                token.data,
                lexer->filename.data,
                lexer->line);
              idLexer::SkipBracedSection(lexer, 1);
              v4 = this;
            }
            else
            {
              rvParticleTemplate::GetVector(v4, lexer, count, &envelope->mEnvOffset);
            }
          }
          else
          {
            rvParticleTemplate::GetVector(v4, lexer, count, &envelope->mRate);
            envelope->mIsCount = 1;
          }
        }
        else
        {
          rvParticleTemplate::GetVector(v4, lexer, count, &envelope->mRate);
          envelope->mIsCount = 0;
        }
      }
      else
      {
        idLexer::ReadToken(lexer, &token);
        envelope->mTable = (const idDeclTable *)declManager->FindType(declManager, 0, token.data, 1, 0);
      }
      if ( !idLexer::ReadToken(lexer, &token) )
        goto LABEL_2;
    }
    v8 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_2:
    v8 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: bool __thiscall rvParticleTemplate::ParseMotionDomains(class rvDeclEffect *,class idLexer *)
char __thiscall rvParticleTemplate::ParseMotionDomains(rvParticleTemplate *this, rvDeclEffect *effect, idLexer *lexer)
{
  char *data; // ebx
  int v6; // ebp
  int v7; // eax
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v9; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v9 = 0;
  if ( idLexer::ExpectTokenString(lexer, "{") && idLexer::ReadToken(lexer, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "tint") )
      {
        if ( idStr::Icmp(token.data, "fade") )
        {
          if ( idStr::Icmp(token.data, "size") )
          {
            if ( idStr::Icmp(token.data, "rotate") )
            {
              if ( idStr::Icmp(token.data, "angle") )
              {
                if ( idStr::Icmp(token.data, "offset") )
                {
                  if ( idStr::Icmp(token.data, "length") )
                  {
                    data = token.data;
                    v6 = *(_DWORD *)common.type;
                    v7 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                           effect->base,
                           lexer->filename.data,
                           lexer->line);
                    (*(void (**)(netadrtype_t, const char *, ...))(v6 + 136))(
                      common.type,
                      "^4BSE:^1 Invalid motion domain '%s' in %s (file: %s, line: %d)",
                      data,
                      v7);
                    idLexer::SkipBracedSection(lexer, 1);
                  }
                  else
                  {
                    rvParticleTemplate::ParseMotionParms(this, lexer, 3, &this->mLengthEnvelope);
                  }
                }
                else
                {
                  rvParticleTemplate::ParseMotionParms(this, lexer, 3, &this->mOffsetEnvelope);
                }
              }
              else
              {
                rvParticleTemplate::ParseMotionParms(this, lexer, 3, &this->mAngleEnvelope);
              }
            }
            else
            {
              rvParticleTemplate::ParseMotionParms(this, lexer, this->mNumRotateParms, &this->mRotateEnvelope);
            }
          }
          else
          {
            rvParticleTemplate::ParseMotionParms(this, lexer, this->mNumSizeParms, &this->mSizeEnvelope);
          }
        }
        else
        {
          rvParticleTemplate::ParseMotionParms(this, lexer, 1, &this->mFadeEnvelope);
        }
      }
      else
      {
        rvParticleTemplate::ParseMotionParms(this, lexer, 3, &this->mTintEnvelope);
      }
      if ( !idLexer::ReadToken(lexer, &token) )
        goto LABEL_2;
    }
    v9 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_2:
    v9 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: bool __thiscall rvParticleTemplate::CheckCommonParms(class idLexer *,class rvParticleParms &)
char __thiscall rvParticleTemplate::CheckCommonParms(rvParticleTemplate *this, idLexer *lexer, rvParticleParms *parms)
{
  idToken token; // [esp+0h] [ebp-5Ch] BYREF
  int v5; // [esp+58h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v5 = 0;
  if ( idLexer::ReadToken(lexer, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "surface") )
      {
        if ( idStr::Icmp(token.data, "useEndOrigin") )
        {
          if ( idStr::Icmp(token.data, "cone") )
          {
            if ( idStr::Icmp(token.data, "relative") )
            {
              if ( idStr::Icmp(token.data, "linearSpacing") )
              {
                if ( idStr::Icmp(token.data, "attenuate") )
                {
                  if ( !idStr::Icmp(token.data, "inverseAttenuate") )
                    parms->mFlags |= 0x40u;
                }
                else
                {
                  parms->mFlags |= 0x20u;
                }
              }
              else
              {
                parms->mFlags |= 0x10u;
              }
            }
            else
            {
              parms->mFlags |= 8u;
            }
          }
          else
          {
            parms->mFlags |= 4u;
          }
        }
        else
        {
          parms->mFlags |= 2u;
        }
      }
      else
      {
        parms->mFlags |= 1u;
      }
      if ( !idLexer::ReadToken(lexer, &token) )
        goto LABEL_18;
    }
    v5 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_18:
    v5 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: bool __thiscall rvParticleTemplate::ParseSpawnParms(class rvDeclEffect *,class idLexer *,class rvParticleParms &,int)
char __thiscall rvParticleTemplate::ParseSpawnParms(
        rvParticleTemplate *this,
        rvDeclEffect *effect,
        idLexer *lexer,
        rvParticleParms *parms,
        int count)
{
  rvParticleParms *v8; // ebx
  char *v9; // ebp
  char *v10; // ebp
  int v12; // eax
  int v14; // eax
  int v16; // eax
  char *v18; // ebx
  int v19; // eax
  rvParticleParms *v20; // ebx
  idRenderModel *v21; // ebp
  idRenderModel *v22; // eax
  int v23; // ebx
  int v24; // eax
  char *data; // edi
  int v26; // ebx
  int v27; // eax
  int v28; // [esp-14h] [ebp-78h]
  int v29; // [esp-14h] [ebp-78h]
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v31; // [esp+60h] [ebp-4h]
  char *lexera; // [esp+6Ch] [ebp+8h]
  rvParticleParms *parmsa; // [esp+70h] [ebp+Ch]
  rvParticleParms *parmsb; // [esp+70h] [ebp+Ch]
  char *parmsc; // [esp+70h] [ebp+Ch]
  char *parmsd; // [esp+70h] [ebp+Ch]
  char *parmse; // [esp+70h] [ebp+Ch]
  rvParticleParms *parmsf; // [esp+70h] [ebp+Ch]
  int counta; // [esp+74h] [ebp+10h]
  int countb; // [esp+74h] [ebp+10h]
  int countc; // [esp+74h] [ebp+10h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v31 = 0;
  if ( !idLexer::ExpectTokenString(lexer, "{") || !idLexer::ReadToken(lexer, &token) )
  {
    v31 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  if ( idStr::Cmp(token.data, "}") )
  {
    if ( idStr::Icmp(token.data, "point") )
    {
      if ( idStr::Icmp(token.data, "line") )
      {
        if ( idStr::Icmp(token.data, "box") )
        {
          if ( idStr::Icmp(token.data, "sphere") )
          {
            if ( idStr::Icmp(token.data, "cylinder") )
            {
              if ( idStr::Icmp(token.data, "spiral") )
              {
                if ( !idStr::Icmp(token.data, "model") )
                {
                  v20 = parms;
                  parms->mSpawnType = count + 44;
                  idLexer::ReadToken(lexer, &token);
                  v21 = renderModelManager->FindModel(renderModelManager, token.data);
                  if ( !v21->NumSurfaces(v21) )
                  {
                    v22 = renderModelManager->FindModel(renderModelManager, "_default");
                    v23 = *(_DWORD *)common.type;
                    v21 = v22;
                    lexera = token.data;
                    v24 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                            effect->base,
                            lexer->filename.data,
                            lexer->line);
                    (*(void (**)(netadrtype_t, const char *, ...))(v23 + 136))(
                      common.type,
                      "^4BSE:^1 No surfaces defined in model '%s' in '%s' (file: %s, line: %d)",
                      lexera,
                      v24);
                    v20 = parms;
                  }
                  v20->mMisc = v21;
                  idLexer::ExpectTokenString(lexer, ",");
                  rvParticleTemplate::GetVector(this, lexer, count, &v20->mMins);
                  idLexer::ExpectTokenString(lexer, ",");
                  rvParticleTemplate::GetVector(this, lexer, count, &v20->mMaxs);
                  if ( !rvParticleTemplate::CheckCommonParms(this, lexer, v20) )
                  {
                    data = token.data;
                    v26 = *(_DWORD *)common.type;
                    v27 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                            effect->base,
                            lexer->filename.data,
                            lexer->line);
                    (*(void (**)(netadrtype_t, const char *, ...))(v26 + 136))(
                      common.type,
                      "^4BSE:^1 Invalid model parameter '%s' in '%s' (file: %s, line: %d)",
                      data,
                      v27);
                  }
                }
              }
              else
              {
                parms->mSpawnType = count + 40;
                rvParticleTemplate::GetVector(this, lexer, count, &parms->mMins);
                idLexer::ExpectTokenString(lexer, ",");
                rvParticleTemplate::GetVector(this, lexer, count, &parms->mMaxs);
                idLexer::ExpectTokenString(lexer, ",");
                parms->mRange = idLexer::ParseFloat(lexer, 0);
                if ( !rvParticleTemplate::CheckCommonParms(this, lexer, parms) )
                {
                  v18 = token.data;
                  parmsf = *(rvParticleParms **)common.type;
                  v19 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                          effect->base,
                          lexer->filename.data,
                          lexer->line);
                  ((void (*)(netadrtype_t, const char *, ...))LODWORD(parmsf[3].mMins.x))(
                    common.type,
                    "^4BSE:^1 Invalid spiral parameter '%s' in '%s' (file: %s, line: %d)",
                    v18,
                    v19);
                }
                rvParticleTemplate::FixupParms(this, parms);
              }
              goto LABEL_36;
            }
            v8 = parms;
            parms->mSpawnType = count + 32;
            rvParticleTemplate::GetVector(this, lexer, count, &parms->mMins);
            idLexer::ExpectTokenString(lexer, ",");
            rvParticleTemplate::GetVector(this, lexer, count, &parms->mMaxs);
            if ( !rvParticleTemplate::CheckCommonParms(this, lexer, parms) )
            {
              parmse = token.data;
              countc = *(_DWORD *)common.type;
              v16 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                      effect->base,
                      lexer->filename.data,
                      lexer->line);
              (*(void (**)(netadrtype_t, const char *, ...))(countc + 136))(
                common.type,
                "^4BSE:^1 Invalid cylinder parameter '%s' in '%s' (file: %s, line: %d)",
                parmse,
                v16);
            }
            if ( (v8->mFlags & 1) != 0 )
            {
              v8->mSpawnType = count + 36;
              rvParticleTemplate::FixupParms(this, v8);
              goto LABEL_36;
            }
          }
          else
          {
            v8 = parms;
            parms->mSpawnType = count + 24;
            rvParticleTemplate::GetVector(this, lexer, count, &parms->mMins);
            idLexer::ExpectTokenString(lexer, ",");
            rvParticleTemplate::GetVector(this, lexer, count, &parms->mMaxs);
            if ( !rvParticleTemplate::CheckCommonParms(this, lexer, parms) )
            {
              parmsd = token.data;
              countb = *(_DWORD *)common.type;
              v14 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                      effect->base,
                      lexer->filename.data,
                      lexer->line);
              (*(void (**)(netadrtype_t, const char *, ...))(countb + 136))(
                common.type,
                "^4BSE:^1 Invalid sphere parameter '%s' in '%s' (file: %s, line: %d)",
                parmsd,
                v14);
            }
            if ( (v8->mFlags & 1) != 0 )
            {
              v8->mSpawnType = count + 28;
              rvParticleTemplate::FixupParms(this, v8);
              goto LABEL_36;
            }
          }
        }
        else
        {
          v8 = parms;
          parms->mSpawnType = count + 16;
          rvParticleTemplate::GetVector(this, lexer, count, &parms->mMins);
          idLexer::ExpectTokenString(lexer, ",");
          rvParticleTemplate::GetVector(this, lexer, count, &parms->mMaxs);
          if ( !rvParticleTemplate::CheckCommonParms(this, lexer, parms) )
          {
            parmsc = token.data;
            counta = *(_DWORD *)common.type;
            v12 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                    effect->base,
                    lexer->filename.data,
                    lexer->line);
            (*(void (**)(netadrtype_t, const char *, ...))(counta + 136))(
              common.type,
              "^4BSE:^1 Invalid box parameter '%s' in '%s' (file: %s, line: %d)",
              parmsc,
              v12);
          }
          if ( (v8->mFlags & 1) != 0 )
          {
            v8->mSpawnType = count + 20;
            rvParticleTemplate::FixupParms(this, v8);
            goto LABEL_36;
          }
        }
      }
      else
      {
        v8 = parms;
        parms->mSpawnType = count + 12;
        rvParticleTemplate::GetVector(this, lexer, count, &parms->mMins);
        idLexer::ExpectTokenString(lexer, ",");
        rvParticleTemplate::GetVector(this, lexer, count, &parms->mMaxs);
        if ( !rvParticleTemplate::CheckCommonParms(this, lexer, parms) )
        {
          v10 = token.data;
          parmsb = *(rvParticleParms **)common.type;
          v29 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                  effect->base,
                  lexer->filename.data,
                  lexer->line);
          ((void (__cdecl *)(netadrtype_t, const char *, char *, int))LODWORD(parmsb[3].mMins.x))(
            common.type,
            "^4BSE:^1 Invalid line parameter '%s' in '%s' (file: %s, line: %d)",
            v10,
            v29);
        }
      }
    }
    else
    {
      v8 = parms;
      parms->mSpawnType = count + 8;
      rvParticleTemplate::GetVector(this, lexer, count, &parms->mMins);
      if ( !rvParticleTemplate::CheckCommonParms(this, lexer, parms) )
      {
        v9 = token.data;
        parmsa = *(rvParticleParms **)common.type;
        v28 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                effect->base,
                lexer->filename.data,
                lexer->line);
        ((void (__cdecl *)(netadrtype_t, const char *, char *, int))LODWORD(parmsa[3].mMins.x))(
          common.type,
          "^4BSE:^1 Invalid point parameter '%s' in '%s' (file: %s, line: %d)",
          v9,
          v28);
      }
    }
    rvParticleTemplate::FixupParms(this, v8);
  }
LABEL_36:
  v31 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: bool __thiscall rvParticleTemplate::ParseSpawnDomains(class rvDeclEffect *,class idLexer *)
char __thiscall rvParticleTemplate::ParseSpawnDomains(rvParticleTemplate *this, rvDeclEffect *effect, idLexer *lexer)
{
  int v6; // ebp
  int v7; // eax
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v9; // [esp+5Ch] [ebp-4h]
  char *lexera; // [esp+68h] [ebp+8h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v9 = 0;
  if ( idLexer::ExpectTokenString(lexer, "{") && idLexer::ReadToken(lexer, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "position") )
      {
        if ( idStr::Icmp(token.data, "direction") )
        {
          if ( idStr::Icmp(token.data, "velocity") )
          {
            if ( idStr::Icmp(token.data, "acceleration") )
            {
              if ( idStr::Icmp(token.data, "friction") )
              {
                if ( idStr::Icmp(token.data, "tint") )
                {
                  if ( idStr::Icmp(token.data, "fade") )
                  {
                    if ( idStr::Icmp(token.data, "size") )
                    {
                      if ( idStr::Icmp(token.data, "rotate") )
                      {
                        if ( idStr::Icmp(token.data, "angle") )
                        {
                          if ( idStr::Icmp(token.data, "offset") )
                          {
                            if ( idStr::Icmp(token.data, "length") )
                            {
                              v6 = *(_DWORD *)common.type;
                              lexera = token.data;
                              v7 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                                     effect->base,
                                     lexer->filename.data,
                                     lexer->line);
                              (*(void (**)(netadrtype_t, const char *, ...))(v6 + 136))(
                                common.type,
                                "^4BSE:^1 Invalid spawn type '%s' in '%s' (file: %s, line: %d)",
                                lexera,
                                v7);
                            }
                            else
                            {
                              rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnLength, 3);
                            }
                          }
                          else
                          {
                            rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnOffset, 3);
                          }
                        }
                        else
                        {
                          rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnAngle, 3);
                        }
                      }
                      else
                      {
                        rvParticleTemplate::ParseSpawnParms(
                          this,
                          effect,
                          lexer,
                          &this->mSpawnRotate,
                          this->mNumRotateParms);
                      }
                    }
                    else
                    {
                      rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnSize, this->mNumSizeParms);
                    }
                  }
                  else
                  {
                    rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnFade, 1);
                  }
                }
                else
                {
                  rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnTint, 3);
                }
              }
              else
              {
                rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnFriction, 3);
              }
            }
            else
            {
              rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnAcceleration, 3);
            }
          }
          else
          {
            rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnVelocity, 3);
          }
        }
        else
        {
          rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnDirection, 3);
          BYTE1(this->mFlags) |= 0x40u;
        }
      }
      else
      {
        rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mSpawnPosition, 3);
      }
      if ( !idLexer::ReadToken(lexer, &token) )
        goto LABEL_2;
    }
    v9 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_2:
    v9 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: bool __thiscall rvParticleTemplate::ParseDeathDomains(class rvDeclEffect *,class idLexer *)
char __thiscall rvParticleTemplate::ParseDeathDomains(rvParticleTemplate *this, rvDeclEffect *effect, idLexer *lexer)
{
  int v6; // ebp
  int v7; // eax
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v9; // [esp+5Ch] [ebp-4h]
  char *lexera; // [esp+68h] [ebp+8h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v9 = 0;
  if ( idLexer::ExpectTokenString(lexer, "{") && idLexer::ReadToken(lexer, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "tint") )
      {
        if ( idStr::Icmp(token.data, "fade") )
        {
          if ( idStr::Icmp(token.data, "size") )
          {
            if ( idStr::Icmp(token.data, "rotate") )
            {
              if ( idStr::Icmp(token.data, "angle") )
              {
                if ( idStr::Icmp(token.data, "offset") )
                {
                  if ( idStr::Icmp(token.data, "length") )
                  {
                    v6 = *(_DWORD *)common.type;
                    lexera = token.data;
                    v7 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                           effect->base,
                           lexer->filename.data,
                           lexer->line);
                    (*(void (**)(netadrtype_t, const char *, ...))(v6 + 136))(
                      common.type,
                      "^4BSE:^1 Invalid end type '%s' in '%s' (file: %s, line: %d)",
                      lexera,
                      v7);
                  }
                  else
                  {
                    rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mDeathLength, 3);
                    rvEnvParms::SetDefaultType(&this->mLengthEnvelope);
                  }
                }
                else
                {
                  rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mDeathOffset, 3);
                  rvEnvParms::SetDefaultType(&this->mOffsetEnvelope);
                }
              }
              else
              {
                rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mDeathAngle, 3);
                rvEnvParms::SetDefaultType(&this->mAngleEnvelope);
              }
            }
            else
            {
              rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mDeathRotate, this->mNumRotateParms);
              rvEnvParms::SetDefaultType(&this->mRotateEnvelope);
            }
          }
          else
          {
            rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mDeathSize, this->mNumSizeParms);
            rvEnvParms::SetDefaultType(&this->mSizeEnvelope);
          }
        }
        else
        {
          rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mDeathFade, 1);
          rvEnvParms::SetDefaultType(&this->mFadeEnvelope);
        }
      }
      else
      {
        rvParticleTemplate::ParseSpawnParms(this, effect, lexer, &this->mDeathTint, 3);
        rvEnvParms::SetDefaultType(&this->mTintEnvelope);
      }
      if ( !idLexer::ReadToken(lexer, &token) )
        goto LABEL_2;
    }
    v9 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_2:
    v9 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: bool __thiscall rvParticleTemplate::ParseImpact(class rvDeclEffect *,class idLexer *)
char __thiscall rvParticleTemplate::ParseImpact(rvParticleTemplate *this, rvDeclEffect *effect, idLexer *lexer)
{
  char *v5; // ebp
  int v6; // ebx
  char *data; // ebp
  int v8; // ebx
  int v9; // [esp-14h] [ebp-78h]
  int v10; // [esp-14h] [ebp-78h]
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v12; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v12 = 0;
  if ( idLexer::ExpectTokenString(lexer, "{") && (BYTE1(this->mFlags) |= 2u, idLexer::ReadToken(lexer, &token)) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "effect") )
      {
        if ( idStr::Icmp(token.data, "remove") )
        {
          if ( idStr::Icmp(token.data, "bounce") )
          {
            data = token.data;
            v8 = *(_DWORD *)common.type;
            v10 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                    effect->base,
                    lexer->filename.data,
                    lexer->line);
            (*(void (__cdecl **)(netadrtype_t, const char *, char *, int))(v8 + 136))(
              common.type,
              "^4BSE:^1 Invalid impact parameter '%s' in '%s' (file: %s, line: %d)",
              data,
              v10);
          }
          else
          {
            this->mBounce = idLexer::ParseFloat(lexer, 0);
          }
        }
        else if ( idLexer::ParseInt(lexer) )
        {
          BYTE1(this->mFlags) |= 4u;
        }
        else
        {
          BYTE1(this->mFlags) &= ~4u;
        }
      }
      else
      {
        idLexer::ReadToken(lexer, &token);
        if ( this->mNumImpactEffects >= 4 )
        {
          v5 = token.data;
          v6 = *(_DWORD *)common.type;
          v9 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                 effect->base,
                 lexer->filename.data,
                 lexer->line);
          (*(void (__cdecl **)(netadrtype_t, const char *, char *, int))(v6 + 136))(
            common.type,
            "^4BSE:^1 too many impact effects '%s' in '%s' (file: %s, line: %d)",
            v5,
            v9);
        }
        else
        {
          this->mImpactEffects[this->mNumImpactEffects++] = declManager->FindEffect(declManager, token.data, 1);
        }
      }
      if ( !idLexer::ReadToken(lexer, &token) )
        goto LABEL_2;
    }
    v12 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_2:
    v12 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: bool __thiscall rvParticleTemplate::ParseTimeout(class rvDeclEffect *,class idLexer *)
char __thiscall rvParticleTemplate::ParseTimeout(rvParticleTemplate *this, rvDeclEffect *effect, idLexer *lexer)
{
  rvParticleTemplate *v3; // edi
  char *v5; // edi
  int v6; // ebx
  char *data; // edi
  int v8; // ebx
  int v9; // [esp-14h] [ebp-7Ch]
  int v10; // [esp-14h] [ebp-7Ch]
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v13; // [esp+64h] [ebp-4h]

  token.floatvalue = 0.0;
  v3 = this;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v13 = 0;
  if ( !idLexer::ExpectTokenString(lexer, "{") || !idLexer::ReadToken(lexer, &token) )
  {
LABEL_2:
    v13 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  while ( idStr::Cmp(token.data, "}") )
  {
    if ( idStr::Icmp(token.data, "effect") )
    {
      data = token.data;
      v8 = *(_DWORD *)common.type;
      v10 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
              effect->base,
              lexer->filename.data,
              lexer->line);
      (*(void (__cdecl **)(netadrtype_t, const char *, char *, int))(v8 + 136))(
        common.type,
        "^4BSE:^1 Invalid timeout parameter '%s' in '%s' (file: %s, line: %d)",
        data,
        v10);
      goto LABEL_10;
    }
    idLexer::ReadToken(lexer, &token);
    if ( v3->mNumTimeoutEffects >= 4 )
    {
      v5 = token.data;
      v6 = *(_DWORD *)common.type;
      v9 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
             effect->base,
             lexer->filename.data,
             lexer->line);
      (*(void (__cdecl **)(netadrtype_t, const char *, char *, int))(v6 + 136))(
        common.type,
        "^4BSE:^1 Too many timeout effects '%s' in '%s' (file: %s, line: %d)",
        v5,
        v9);
LABEL_10:
      v3 = this;
      goto LABEL_11;
    }
    v3->mTimeoutEffects[v3->mNumTimeoutEffects++] = declManager->FindEffect(declManager, token.data, 1);
LABEL_11:
    if ( !idLexer::ReadToken(lexer, &token) )
      goto LABEL_2;
  }
  v13 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: bool __thiscall rvParticleTemplate::ParseBlendParms(class rvDeclEffect *,class idLexer *)
char __thiscall rvParticleTemplate::ParseBlendParms(rvParticleTemplate *this, rvDeclEffect *effect, idLexer *lexer)
{
  char *data; // edi
  int v6; // ebx
  int v7; // eax
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v9; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v9 = 0;
  if ( idLexer::ReadToken(lexer, &token) )
  {
    if ( idStr::Icmp(token.data, "add") )
    {
      data = token.data;
      v6 = *(_DWORD *)common.type;
      v7 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
             effect->base,
             lexer->filename.data,
             lexer->line);
      (*(void (**)(netadrtype_t, const char *, ...))(v6 + 136))(
        common.type,
        "^4BSE:^1 Invalid blend type '%s' in '%s' (file: %s, line: %d)",
        data,
        v7);
    }
    else
    {
      BYTE1(this->mFlags) |= 0x80u;
    }
    v9 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
    v9 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: bool __thiscall rvParticleTemplate::Compare(class rvParticleTemplate const &)const
char __thiscall rvParticleTemplate::Compare(rvParticleTemplate *this, const rvParticleTemplate *a)
{
  int mNumImpactEffects; // edx
  int v4; // ecx
  const rvDeclEffect **mImpactEffects; // eax
  int mNumTimeoutEffects; // edx
  int v7; // ecx
  const rvDeclEffect **mTimeoutEffects; // eax
  int mTrailType; // eax

  if ( this->mFlags != a->mFlags
    || this->mType != a->mType
    || this->mDuration.x != a->mDuration.x
    || this->mDuration.y != a->mDuration.y
    || idStr::Cmp(this->mMaterialName.data, a->mMaterialName.data)
    || idStr::Cmp(this->mModelName.data, a->mModelName.data)
    || this->mGravity.x != a->mGravity.x
    || this->mGravity.y != a->mGravity.y
    || this->mBounce != a->mBounce
    || this->mNumSizeParms != a->mNumSizeParms
    || this->mNumRotateParms != a->mNumRotateParms
    || this->mVertexCount != a->mVertexCount
    || this->mIndexCount != a->mIndexCount
    || rvParticleParms::operator!=(&this->mSpawnPosition, &a->mSpawnPosition)
    || rvParticleParms::operator!=(&this->mSpawnVelocity, &a->mSpawnVelocity)
    || rvParticleParms::operator!=(&this->mSpawnAcceleration, &a->mSpawnAcceleration)
    || rvParticleParms::operator!=(&this->mSpawnFriction, &a->mSpawnFriction)
    || rvParticleParms::operator!=(&this->mSpawnDirection, &a->mSpawnDirection)
    || (int)(this->mSpawnTint.mMins.x * 255.0) != (int)(a->mSpawnTint.mMins.x * 255.0)
    || (int)(this->mSpawnTint.mMins.y * 255.0) != (int)(a->mSpawnTint.mMins.y * 255.0)
    || (int)(this->mSpawnTint.mMins.z * 255.0) != (int)(a->mSpawnTint.mMins.z * 255.0)
    || (int)(this->mSpawnTint.mMaxs.x * 255.0) != (int)(a->mSpawnTint.mMaxs.x * 255.0)
    || (int)(this->mSpawnTint.mMaxs.y * 255.0) != (int)(a->mSpawnTint.mMaxs.y * 255.0)
    || (int)(this->mSpawnTint.mMaxs.z * 255.0) != (int)(a->mSpawnTint.mMaxs.z * 255.0)
    || this->mSpawnTint.mSpawnType != a->mSpawnTint.mSpawnType
    || this->mSpawnTint.mFlags != a->mSpawnTint.mFlags
    || rvParticleParms::operator!=(&this->mSpawnFade, &a->mSpawnFade)
    || rvParticleParms::operator!=(&this->mSpawnSize, &a->mSpawnSize)
    || rvParticleParms::operator!=(&this->mSpawnRotate, &a->mSpawnRotate)
    || rvParticleParms::operator!=(&this->mSpawnAngle, &a->mSpawnAngle)
    || rvParticleParms::operator!=(&this->mSpawnOffset, &a->mSpawnOffset)
    || rvParticleParms::operator!=(&this->mSpawnLength, &a->mSpawnLength)
    || rvEnvParms::GetType(&this->mTintEnvelope) > 0
    && ((int)(this->mDeathTint.mMins.x * 255.0) != (int)(a->mDeathTint.mMins.x * 255.0)
     || (int)(this->mDeathTint.mMins.y * 255.0) != (int)(a->mDeathTint.mMins.y * 255.0)
     || (int)(this->mDeathTint.mMins.z * 255.0) != (int)(a->mDeathTint.mMins.z * 255.0)
     || (int)(this->mDeathTint.mMaxs.x * 255.0) != (int)(a->mDeathTint.mMaxs.x * 255.0)
     || (int)(this->mDeathTint.mMaxs.y * 255.0) != (int)(a->mDeathTint.mMaxs.y * 255.0)
     || (int)(this->mDeathTint.mMaxs.z * 255.0) != (int)(a->mDeathTint.mMaxs.z * 255.0)
     || this->mDeathTint.mSpawnType != a->mDeathTint.mSpawnType
     || this->mDeathTint.mFlags != a->mDeathTint.mFlags) )
  {
    return 0;
  }
  if ( rvEnvParms::GetType(&this->mFadeEnvelope) > 0 && rvParticleParms::operator!=(&this->mDeathFade, &a->mDeathFade) )
    return 0;
  if ( rvEnvParms::GetType(&this->mSizeEnvelope) > 0 && rvParticleParms::operator!=(&this->mDeathSize, &a->mDeathSize) )
    return 0;
  if ( rvEnvParms::GetType(&this->mRotateEnvelope) > 0
    && rvParticleParms::operator!=(&this->mDeathRotate, &a->mDeathRotate) )
  {
    return 0;
  }
  if ( rvEnvParms::GetType(&this->mAngleEnvelope) > 0
    && rvParticleParms::operator!=(&this->mDeathAngle, &a->mDeathAngle) )
  {
    return 0;
  }
  if ( rvEnvParms::GetType(&this->mOffsetEnvelope) > 0
    && rvParticleParms::operator!=(&this->mDeathOffset, &a->mDeathOffset) )
  {
    return 0;
  }
  if ( rvEnvParms::GetType(&this->mLengthEnvelope) > 0
    && rvParticleParms::operator!=(&this->mDeathLength, &a->mDeathLength) )
  {
    return 0;
  }
  mNumImpactEffects = this->mNumImpactEffects;
  if ( mNumImpactEffects != a->mNumImpactEffects || this->mNumTimeoutEffects != a->mNumTimeoutEffects )
    return 0;
  v4 = 0;
  if ( mNumImpactEffects > 0 )
  {
    mImpactEffects = this->mImpactEffects;
    while ( *mImpactEffects == *(const rvDeclEffect **)((char *)mImpactEffects + (char *)a - (char *)this) )
    {
      ++v4;
      ++mImpactEffects;
      if ( v4 >= mNumImpactEffects )
        goto LABEL_60;
    }
    return 0;
  }
LABEL_60:
  mNumTimeoutEffects = this->mNumTimeoutEffects;
  v7 = 0;
  if ( mNumTimeoutEffects > 0 )
  {
    mTimeoutEffects = this->mTimeoutEffects;
    while ( *mTimeoutEffects == *(const rvDeclEffect **)((char *)mTimeoutEffects + (char *)a - (char *)this) )
    {
      ++v7;
      ++mTimeoutEffects;
      if ( v7 >= mNumTimeoutEffects )
        goto LABEL_64;
    }
    return 0;
  }
LABEL_64:
  if ( rvEnvParms::operator!=(&this->mRotateEnvelope, &a->mRotateEnvelope) )
    return 0;
  if ( rvEnvParms::operator!=(&this->mSizeEnvelope, &a->mSizeEnvelope) )
    return 0;
  if ( rvEnvParms::operator!=(&this->mFadeEnvelope, &a->mFadeEnvelope) )
    return 0;
  if ( rvEnvParms::operator!=(&this->mTintEnvelope, &a->mTintEnvelope) )
    return 0;
  if ( rvEnvParms::operator!=(&this->mAngleEnvelope, &a->mAngleEnvelope) )
    return 0;
  if ( rvEnvParms::operator!=(&this->mOffsetEnvelope, &a->mOffsetEnvelope) )
    return 0;
  if ( rvEnvParms::operator!=(&this->mLengthEnvelope, &a->mLengthEnvelope) )
    return 0;
  mTrailType = this->mTrailType;
  if ( mTrailType != a->mTrailType )
    return 0;
  if ( mTrailType > 0 )
  {
    if ( mTrailType <= 2 )
    {
      if ( this->mTrailTime.x != a->mTrailTime.x
        || this->mTrailTime.y != a->mTrailTime.y
        || this->mTrailCount.x != a->mTrailCount.x
        || this->mTrailCount.y != a->mTrailCount.y )
      {
        return 0;
      }
    }
    else if ( mTrailType == 3 && idStr::Cmp(this->mTrailTypeName.data, a->mTrailTypeName.data) )
    {
      return 0;
    }
  }
  return 1;
}

// FUNC: public: void __thiscall rvParticleTemplate::Finish(void)
void __thiscall rvParticleTemplate::Finish(rvParticleTemplate *this)
{
  int mTrailType; // eax
  idRenderModel *v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  char *v7; // eax
  idTraceModel *v8; // eax
  idTraceModel *v9; // ebx
  const idBounds *v10; // edi
  idTraceModel **list; // ecx
  int granularity; // ebx
  int v13; // eax
  int v14; // edx
  int v15; // eax
  idTraceModel **v16; // edi
  int v17; // eax
  int mNumForks; // eax
  float y; // eax
  float v20; // ecx
  float v21; // edx
  float v22; // eax
  double v23; // st6
  idTraceModel *v24; // [esp+8h] [ebp-1Ch]
  float v25; // [esp+10h] [ebp-14h]
  float v26; // [esp+14h] [ebp-10h]
  float v27; // [esp+14h] [ebp-10h]

  mTrailType = this->mTrailType;
  BYTE1(this->mFlags) |= 1u;
  if ( !mTrailType || mTrailType == 3 )
  {
    this->mTrailTime.y = 0.0;
    this->mTrailTime.x = 0.0;
    this->mTrailCount.y = 0.0;
    this->mTrailCount.x = 0.0;
  }
  switch ( this->mType )
  {
    case 1:
    case 2:
      this->mVertexCount = 4;
      this->mIndexCount = 6;
      if ( this->mTrailCount.y != 0.0 && this->mTrailType == 1 )
      {
        this->mVertexCount *= rvParticleTemplate::GetMaxTrailCount(this);
        this->mIndexCount *= rvParticleTemplate::GetMaxTrailCount(this);
      }
      goto LABEL_42;
    case 4:
    case 6:
    case 8:
      this->mVertexCount = 4;
      this->mIndexCount = 6;
      goto LABEL_42;
    case 5:
      v3 = renderModelManager->FindModel(renderModelManager, this->mModelName.data);
      v4 = (int)v3->Surface(v3, 0);
      v5 = v4;
      if ( v4 )
      {
        v6 = *(_DWORD *)(*(_DWORD *)(v4 + 8) + 136);
        if ( v6 )
        {
          this->mVertexCount = *(_DWORD *)(v6 + 60);
          this->mIndexCount = *(_DWORD *)(v6 + 64);
        }
        else
        {
          this->mVertexCount = *(_DWORD *)(*(_DWORD *)(v5 + 8) + 36);
          this->mIndexCount = *(_DWORD *)(*(_DWORD *)(v5 + 8) + 52);
        }
      }
      this->mMaterial = *(const idMaterial **)(v5 + 4);
      v7 = (char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(*(_DWORD *)(v5 + 4) + 4) + 4))(*(_DWORD *)(*(_DWORD *)(v5 + 4) + 4));
      idStr::operator=(&this->mMaterialName, v7);
      v8 = (idTraceModel *)Memory::Allocate(0xB0Cu);
      v9 = v8;
      if ( v8 )
      {
        v10 = *(const idBounds **)(v5 + 8);
        idTraceModel::InitBox(v8);
        idTraceModel::SetupBox(v9, v10);
        v24 = v9;
      }
      else
      {
        v24 = 0;
      }
      list = rvBSEManagerLocal::mTraceModels.list;
      granularity = rvBSEManagerLocal::mTraceModels.granularity;
      if ( rvBSEManagerLocal::mTraceModels.list )
        goto LABEL_21;
      if ( rvBSEManagerLocal::mTraceModels.granularity > 0 )
      {
        if ( rvBSEManagerLocal::mTraceModels.granularity != rvBSEManagerLocal::mTraceModels.size )
        {
          rvBSEManagerLocal::mTraceModels.size = rvBSEManagerLocal::mTraceModels.granularity;
          if ( rvBSEManagerLocal::mTraceModels.granularity < rvBSEManagerLocal::mTraceModels.num )
            rvBSEManagerLocal::mTraceModels.num = rvBSEManagerLocal::mTraceModels.granularity;
          list = (idTraceModel **)Memory::Allocate(4 * rvBSEManagerLocal::mTraceModels.granularity);
          v13 = 0;
          for ( rvBSEManagerLocal::mTraceModels.list = list; v13 < rvBSEManagerLocal::mTraceModels.num; ++v13 )
          {
            list[v13] = *(idTraceModel **)(4 * v13);
            list = rvBSEManagerLocal::mTraceModels.list;
          }
          granularity = rvBSEManagerLocal::mTraceModels.granularity;
        }
LABEL_21:
        if ( rvBSEManagerLocal::mTraceModels.num != rvBSEManagerLocal::mTraceModels.size )
        {
LABEL_35:
          list[rvBSEManagerLocal::mTraceModels.num++] = v24;
          goto LABEL_42;
        }
      }
      else
      {
        list = 0;
        rvBSEManagerLocal::mTraceModels.list = 0;
        rvBSEManagerLocal::mTraceModels.num = 0;
        rvBSEManagerLocal::mTraceModels.size = 0;
      }
      if ( !granularity )
      {
        granularity = 16;
        rvBSEManagerLocal::mTraceModels.granularity = 16;
      }
      v14 = (rvBSEManagerLocal::mTraceModels.size + granularity) % granularity;
      v15 = rvBSEManagerLocal::mTraceModels.size + granularity - v14;
      if ( v15 > 0 )
      {
        if ( v15 != rvBSEManagerLocal::mTraceModels.size )
        {
          v16 = list;
          rvBSEManagerLocal::mTraceModels.size = rvBSEManagerLocal::mTraceModels.size + granularity - v14;
          if ( v15 < rvBSEManagerLocal::mTraceModels.num )
            rvBSEManagerLocal::mTraceModels.num = v15;
          list = (idTraceModel **)Memory::Allocate(4 * v15);
          v17 = 0;
          for ( rvBSEManagerLocal::mTraceModels.list = list; v17 < rvBSEManagerLocal::mTraceModels.num; ++v17 )
          {
            list[v17] = v16[v17];
            list = rvBSEManagerLocal::mTraceModels.list;
          }
          if ( v16 )
          {
            Memory::Free(v16);
            list = rvBSEManagerLocal::mTraceModels.list;
          }
        }
      }
      else
      {
        if ( list )
          Memory::Free(list);
        list = 0;
        rvBSEManagerLocal::mTraceModels.list = 0;
        rvBSEManagerLocal::mTraceModels.num = 0;
        rvBSEManagerLocal::mTraceModels.size = 0;
      }
      goto LABEL_35;
    case 7:
      mNumForks = this->mNumForks;
      this->mVertexCount = 4 * (5 * mNumForks + 5);
      this->mIndexCount = 60 * (mNumForks + 1);
      goto LABEL_42;
    case 9:
      this->mVertexCount = 0;
      this->mIndexCount = 0;
      goto LABEL_42;
    default:
LABEL_42:
      if ( this->mDuration.x >= (double)this->mDuration.y )
      {
        y = this->mDuration.y;
        this->mDuration.y = this->mDuration.x;
        this->mDuration.x = y;
      }
      if ( this->mGravity.x >= (double)this->mGravity.y )
      {
        v20 = this->mGravity.y;
        this->mGravity.y = this->mGravity.x;
        this->mGravity.x = v20;
      }
      if ( this->mTrailTime.x >= (double)this->mTrailTime.y )
      {
        v21 = this->mTrailTime.y;
        this->mTrailTime.y = this->mTrailTime.x;
        this->mTrailTime.x = v21;
      }
      if ( this->mTrailCount.x >= (double)this->mTrailCount.y )
      {
        v22 = this->mTrailCount.y;
        this->mTrailCount.y = this->mTrailCount.x;
        this->mTrailCount.x = v22;
      }
      this->mCentre.z = 0.0;
      this->mCentre.y = 0.0;
      this->mCentre.x = 0.0;
      if ( (this->mFlags & 0x1000) == 0 )
      {
        switch ( this->mSpawnPosition.mSpawnType )
        {
          case 0xB:
            this->mCentre.x = this->mSpawnPosition.mMins.x;
            this->mCentre.y = this->mSpawnPosition.mMins.y;
            this->mCentre.z = this->mSpawnPosition.mMins.z;
            break;
          case 0xF:
          case 0x13:
          case 0x17:
          case 0x1B:
          case 0x1F:
          case 0x23:
          case 0x27:
          case 0x2B:
          case 0x2F:
            v25 = this->mSpawnPosition.mMaxs.y + this->mSpawnPosition.mMins.y;
            v26 = this->mSpawnPosition.mMaxs.z + this->mSpawnPosition.mMins.z;
            v27 = v26 * 0.5;
            v23 = (this->mSpawnPosition.mMaxs.x + this->mSpawnPosition.mMins.x) * 0.5;
            this->mCentre.z = v27;
            this->mCentre.x = v23;
            this->mCentre.y = v25 * 0.5;
            break;
          default:
            return;
        }
      }
      return;
  }
}

// FUNC: public: bool __thiscall rvParticleTemplate::Parse(class rvDeclEffect *,class idLexer *)
char __thiscall rvParticleTemplate::Parse(rvParticleTemplate *this, rvDeclEffect *effect, idLexer *lexer)
{
  double v6; // st7
  double v7; // st7
  double v8; // st7
  int v9; // eax
  const idDecl *v10; // eax
  int v11; // eax
  const idDeclTable *v12; // esi
  idRenderModel *v13; // eax
  char *v14; // esi
  int v15; // edi
  int v16; // eax
  char *data; // edi
  int v18; // esi
  int v19; // eax
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v21; // [esp+60h] [ebp-4h]
  int lexera; // [esp+6Ch] [ebp+8h]
  int lexerb; // [esp+6Ch] [ebp+8h]
  int lexerc; // [esp+6Ch] [ebp+8h]
  int lexerd; // [esp+6Ch] [ebp+8h]
  int lexere; // [esp+6Ch] [ebp+8h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v21 = 0;
  if ( idLexer::ExpectTokenString(lexer, "{") && idLexer::ReadToken(lexer, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "start") )
      {
        if ( idStr::Icmp(token.data, "end") )
        {
          if ( idStr::Icmp(token.data, "motion") )
          {
            if ( idStr::Icmp(token.data, "generatedNormal") )
            {
              if ( idStr::Icmp(token.data, "generatedOriginNormal") )
              {
                if ( idStr::Icmp(token.data, "flipNormal") )
                {
                  if ( idStr::Icmp(token.data, "generatedLine") )
                  {
                    if ( idStr::Icmp(token.data, "persist") )
                    {
                      if ( idStr::Icmp(token.data, "tiling") )
                      {
                        if ( idStr::Icmp(token.data, "duration") )
                        {
                          if ( idStr::Icmp(token.data, "gravity") )
                          {
                            if ( idStr::Icmp(token.data, "trailType") )
                            {
                              if ( idStr::Icmp(token.data, "trailMaterial") )
                              {
                                if ( idStr::Icmp(token.data, "trailTime") )
                                {
                                  if ( idStr::Icmp(token.data, "trailCount") )
                                  {
                                    if ( idStr::Icmp(token.data, "material") )
                                    {
                                      if ( idStr::Icmp(token.data, "entityDef") )
                                      {
                                        if ( idStr::Icmp(token.data, "fork") )
                                        {
                                          if ( idStr::Icmp(token.data, "forkMins") )
                                          {
                                            if ( idStr::Icmp(token.data, "forkMaxs") )
                                            {
                                              if ( idStr::Icmp(token.data, "jitterSize") )
                                              {
                                                if ( idStr::Icmp(token.data, "jitterRate") )
                                                {
                                                  if ( idStr::Icmp(token.data, "jitterTable") )
                                                  {
                                                    if ( idStr::Icmp(token.data, "blend") )
                                                    {
                                                      if ( idStr::Icmp(token.data, "shadows") )
                                                      {
                                                        if ( idStr::Icmp(token.data, "specular") )
                                                        {
                                                          if ( idStr::Icmp(token.data, "model") )
                                                          {
                                                            if ( idStr::Icmp(token.data, "impact") )
                                                            {
                                                              if ( idStr::Icmp(token.data, "timeout") )
                                                              {
                                                                data = token.data;
                                                                v18 = *(_DWORD *)common.type;
                                                                v19 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                                                                        effect->base,
                                                                        lexer->filename.data,
                                                                        lexer->line);
                                                                (*(void (**)(netadrtype_t, const char *, ...))(v18 + 136))(
                                                                  common.type,
                                                                  "^4BSE:^1 Invalid particle keyword '%s' in '%s' (file: %s, line: %d)",
                                                                  data,
                                                                  v19);
                                                              }
                                                              else
                                                              {
                                                                rvParticleTemplate::ParseTimeout(this, effect, lexer);
                                                              }
                                                            }
                                                            else
                                                            {
                                                              rvParticleTemplate::ParseImpact(this, effect, lexer);
                                                            }
                                                          }
                                                          else
                                                          {
                                                            idLexer::ReadToken(lexer, &token);
                                                            lexere = token.len;
                                                            if ( token.len + 1 > this->mModelName.alloced )
                                                              idStr::ReAllocate(&this->mModelName, token.len + 1, 0);
                                                            qmemcpy(this->mModelName.data, token.data, lexere);
                                                            this->mModelName.data[lexere] = 0;
                                                            this->mModelName.len = lexere;
                                                            v13 = renderModelManager->FindModel(
                                                                    renderModelManager,
                                                                    this->mModelName.data);
                                                            if ( !v13->NumSurfaces(v13) )
                                                            {
                                                              idStr::operator=(&this->mModelName, "_default");
                                                              v14 = token.data;
                                                              v15 = *(_DWORD *)common.type;
                                                              v16 = ((int (__thiscall *)(idDeclBase *, char *, int))effect->base->GetName)(
                                                                      effect->base,
                                                                      lexer->filename.data,
                                                                      lexer->line);
                                                              (*(void (**)(netadrtype_t, const char *, ...))(v15 + 136))(
                                                                common.type,
                                                                "^4BSE:^1 No surfaces defined in model '%s' in '%s' (file: %s, line: %d)",
                                                                v14,
                                                                v16);
                                                            }
                                                          }
                                                        }
                                                        else
                                                        {
                                                          BYTE2(this->mFlags) |= 4u;
                                                        }
                                                      }
                                                      else
                                                      {
                                                        BYTE2(this->mFlags) |= 2u;
                                                      }
                                                    }
                                                    else
                                                    {
                                                      rvParticleTemplate::ParseBlendParms(this, effect, lexer);
                                                    }
                                                  }
                                                  else
                                                  {
                                                    idLexer::ReadToken(lexer, &token);
                                                    v12 = (const idDeclTable *)declManager->FindType(
                                                                                 declManager,
                                                                                 0,
                                                                                 token.data,
                                                                                 1,
                                                                                 0);
                                                    if ( !v12->base->IsImplicit(v12->base) )
                                                      this->mJitterTable = v12;
                                                  }
                                                }
                                                else
                                                {
                                                  this->mJitterRate = idLexer::ParseFloat(lexer, 0);
                                                }
                                              }
                                              else
                                              {
                                                rvParticleTemplate::GetVector(this, lexer, 3, &this->mJitterSize);
                                              }
                                            }
                                            else
                                            {
                                              rvParticleTemplate::GetVector(this, lexer, 3, &this->mForkSizeMaxs);
                                            }
                                          }
                                          else
                                          {
                                            rvParticleTemplate::GetVector(this, lexer, 3, &this->mForkSizeMins);
                                          }
                                        }
                                        else
                                        {
                                          v11 = idLexer::ParseInt(lexer);
                                          this->mNumForks = v11;
                                          if ( v11 > 16 )
                                            this->mNumForks = 16;
                                        }
                                      }
                                      else
                                      {
                                        idLexer::ReadToken(lexer, &token);
                                        lexerd = token.len;
                                        if ( token.len + 1 > this->mEntityDefName.alloced )
                                          idStr::ReAllocate(&this->mEntityDefName, token.len + 1, 0);
                                        qmemcpy(this->mEntityDefName.data, token.data, lexerd);
                                        this->mEntityDefName.data[lexerd] = 0;
                                        this->mEntityDefName.len = lexerd;
                                        v10 = declManager->FindType(declManager, 4, this->mEntityDefName.data, 0, 0);
                                        if ( v10 )
                                          game->CacheDictionaryMedia(game, (const idDict *)&v10[1]);
                                      }
                                    }
                                    else
                                    {
                                      idLexer::ReadToken(lexer, &token);
                                      this->mMaterial = declManager->FindMaterial(declManager, token.data, 1);
                                      lexerc = token.len;
                                      if ( token.len + 1 > this->mMaterialName.alloced )
                                        idStr::ReAllocate(&this->mMaterialName, token.len + 1, 0);
                                      qmemcpy(this->mMaterialName.data, token.data, lexerc);
                                      this->mMaterialName.data[lexerc] = 0;
                                      this->mMaterialName.len = lexerc;
                                      if ( idMaterial::HasDefaultedImage((idMaterial *)this->mMaterial)
                                        && idStr::Cmp(this->mMaterialName.data, "_default") )
                                      {
                                        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
                                          common.type,
                                          "^4BSE:^1 Defaulted image '%s'",
                                          this->mMaterialName.data);
                                      }
                                    }
                                  }
                                  else
                                  {
                                    this->mTrailCount.x = idLexer::ParseFloat(lexer, 0);
                                    idLexer::ExpectTokenString(lexer, ",");
                                    this->mTrailCount.y = idLexer::ParseFloat(lexer, 0);
                                  }
                                }
                                else
                                {
                                  this->mTrailTime.x = idLexer::ParseFloat(lexer, 0);
                                  idLexer::ExpectTokenString(lexer, ",");
                                  this->mTrailTime.y = idLexer::ParseFloat(lexer, 0);
                                }
                              }
                              else
                              {
                                idLexer::ReadToken(lexer, &token);
                                this->mTrailMaterial = declManager->FindMaterial(declManager, token.data, 1);
                                lexerb = token.len;
                                if ( token.len + 1 > this->mTrailMaterialName.alloced )
                                  idStr::ReAllocate(&this->mTrailMaterialName, token.len + 1, 0);
                                qmemcpy(this->mTrailMaterialName.data, token.data, lexerb);
                                this->mTrailMaterialName.data[lexerb] = 0;
                                this->mTrailMaterialName.len = lexerb;
                              }
                            }
                            else
                            {
                              idLexer::ReadToken(lexer, &token);
                              if ( idStr::Icmp(token.data, "burn") )
                              {
                                if ( idStr::Icmp(token.data, "motion") )
                                {
                                  lexera = token.len;
                                  v9 = token.len + 1;
                                  this->mTrailType = 3;
                                  if ( v9 > this->mTrailTypeName.alloced )
                                    idStr::ReAllocate(&this->mTrailTypeName, v9, 0);
                                  qmemcpy(this->mTrailTypeName.data, token.data, lexera);
                                  this->mTrailTypeName.data[lexera] = 0;
                                  this->mTrailTypeName.len = lexera;
                                }
                                else
                                {
                                  this->mTrailType = 2;
                                }
                              }
                              else
                              {
                                this->mTrailType = 1;
                              }
                            }
                          }
                          else
                          {
                            this->mGravity.x = idLexer::ParseFloat(lexer, 0);
                            idLexer::ExpectTokenString(lexer, ",");
                            this->mGravity.y = idLexer::ParseFloat(lexer, 0);
                          }
                        }
                        else
                        {
                          v7 = idLexer::ParseFloat(lexer, 0);
                          if ( v7 >= 0.0020000001 )
                          {
                            if ( v7 > 60.0 )
                              v7 = 60.0;
                          }
                          else
                          {
                            v7 = 0.0020000001;
                          }
                          this->mDuration.x = v7;
                          idLexer::ExpectTokenString(lexer, ",");
                          v8 = idLexer::ParseFloat(lexer, 0);
                          if ( v8 >= 0.0020000001 )
                          {
                            if ( v8 > 60.0 )
                              v8 = 60.0;
                            this->mDuration.y = v8;
                          }
                          else
                          {
                            this->mDuration.y = 0.0020000001;
                          }
                        }
                      }
                      else
                      {
                        BYTE2(this->mFlags) |= 0x10u;
                        v6 = idLexer::ParseFloat(lexer, 0);
                        if ( v6 >= 0.0020000001 )
                        {
                          if ( v6 > 1024.0 )
                            v6 = 1024.0;
                          this->mTiling = v6;
                        }
                        else
                        {
                          this->mTiling = 0.0020000001;
                        }
                      }
                    }
                    else
                    {
                      BYTE2(this->mFlags) |= 0x20u;
                    }
                  }
                  else
                  {
                    BYTE2(this->mFlags) |= 1u;
                  }
                }
                else
                {
                  BYTE1(this->mFlags) |= 0x20u;
                }
              }
              else
              {
                BYTE1(this->mFlags) |= 0x10u;
              }
            }
            else
            {
              BYTE1(this->mFlags) |= 8u;
            }
          }
          else
          {
            rvParticleTemplate::ParseMotionDomains(this, effect, lexer);
          }
        }
        else
        {
          rvParticleTemplate::ParseDeathDomains(this, effect, lexer);
        }
      }
      else
      {
        rvParticleTemplate::ParseSpawnDomains(this, effect, lexer);
      }
      if ( !idLexer::ReadToken(lexer, &token) )
        goto LABEL_2;
    }
    rvParticleTemplate::Finish(this);
    v21 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_2:
    v21 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}
