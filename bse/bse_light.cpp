
// FUNC: public: virtual bool __thiscall rvLightParticle::Destroy(void)
char __thiscall rvLightParticle::Destroy(rvLightParticle *this)
{
  int mLightDefHandle; // eax

  mLightDefHandle = this->mLightDefHandle;
  if ( mLightDefHandle != -1 )
  {
    session->rw->FreeLightDef(session->rw, mLightDefHandle);
    this->mLightDefHandle = -1;
  }
  return 1;
}

// FUNC: public: void __thiscall rvSegment::InitLight(class rvBSE *,class rvSegmentTemplate *,float)
void __thiscall rvSegment::InitLight(rvSegment *this, rvBSE *effect, rvSegmentTemplate *st, float time)
{
  if ( !this->mUsedHead )
  {
    rvSegment::SpawnParticle(this, effect, st, time, &vec3_origin, &mat3_identity);
    ((void (__thiscall *)(rvParticle *, rvBSE *, rvSegmentTemplate *, _DWORD))this->mUsedHead->InitLight)(
      this->mUsedHead,
      effect,
      st,
      LODWORD(time));
  }
}

// FUNC: public: bool __thiscall rvSegment::HandleLight(class rvBSE *,class rvSegmentTemplate *,float)
char __thiscall rvSegment::HandleLight(rvSegment *this, rvBSE *effect, rvSegmentTemplate *st, float time)
{
  rvParticle *mUsedHead; // ecx
  unsigned int v6; // edx
  rvParticle *v7; // ecx

  mUsedHead = this->mUsedHead;
  if ( !mUsedHead )
    return 0;
  v6 = (unsigned int)st->mFlags >> 5;
  LOBYTE(v6) = (st->mFlags & 0x20) != 0;
  ((void (__thiscall *)(rvParticle *, rvBSE *, _DWORD, unsigned int))mUsedHead->PresentLight)(
    mUsedHead,
    effect,
    LODWORD(time),
    v6);
  if ( (st->mFlags & 0x20) != 0 )
    return 0;
  v7 = this->mUsedHead;
  if ( v7->mEndTime - 0.0020000001 > time )
    return 0;
  v7->Destroy(v7);
  this->mFreeHead = this->mUsedHead;
  this->mUsedHead = 0;
  return 1;
}

// FUNC: public: virtual bool __thiscall rvLightParticle::InitLight(class rvBSE *,class rvSegmentTemplate *,float)
bool __userpurge rvLightParticle::InitLight@<al>(
        rvLightParticle *this@<ecx>,
        int a2@<edi>,
        rvBSE *effect,
        rvSegmentTemplate *st,
        float time,
        float a6)
{
  bool result; // al
  float v8; // edx
  float y; // ecx
  float z; // edx
  double v12; // st7
  double v13; // st7
  double v14; // st6
  float x; // eax
  float v16; // ecx
  float v17; // edx
  float v18; // [esp+Ch] [ebp-48h]
  float evalTime; // [esp+18h] [ebp-3Ch] BYREF
  float v20; // [esp+1Ch] [ebp-38h]
  idVec3 position; // [esp+20h] [ebp-34h] BYREF
  float v22; // [esp+2Ch] [ebp-28h]
  float v23; // [esp+34h] [ebp-20h]
  idVec3 size; // [esp+38h] [ebp-1Ch] BYREF
  idVec4 tint; // [esp+44h] [ebp-10h] BYREF

  result = rvParticle::GetEvaluationTime(this, time, &evalTime, 0);
  if ( result )
  {
    v8 = evalTime;
    memset(&this->mLight, 0, sizeof(this->mLight));
    v20 = v8;
    rvEnvParms3::Evaluate(&this->mTintEnv, v8, &tint.x);
    rvEnvParms1::Evaluate(&this->mFadeEnv, v20, &tint.w);
    ((void (__thiscall *)(rvLightParticle *, _DWORD, idVec3 *, int))this->EvaluateSize)(
      this,
      LODWORD(evalTime),
      &size,
      a2);
    v18 = a6 - this->mMotionStartTime;
    rvParticle::EvaluatePosition(this, (const rvBSE *)st, (idVec3 *)&position.y, v18);
    y = size.y;
    z = size.z;
    v12 = position.z * st->mLocalStartTime.x
        + v22 * st->mLocalDuration.y
        + position.y * *(float *)&st->mSegmentName.baseBuffer[16];
    v23 = position.z * st->mLocalStartTime.y + v22 * st->mAttenuation.x + position.y * *(float *)&st->mFlags;
    size.x = position.z * st->mLocalDuration.x + v22 * st->mAttenuation.y + position.y * *(float *)&st->mSegType;
    v13 = v12 + *(float *)&st->mSegmentName.data;
    v14 = v23 + *(float *)&st->mSegmentName.alloced;
    size.x = size.x + *(float *)st->mSegmentName.baseBuffer;
    this->mLight.origin.z = size.x;
    x = tint.x;
    this->mLight.origin.x = v13;
    this->mLight.origin.y = v14;
    this->mLight.lightRadius.x = y;
    this->mLight.lightRadius.y = z;
    this->mLight.lightRadius.z = x;
    if ( this->mLight.lightRadius.x < 1.0 )
      this->mLight.lightRadius.x = 1.0;
    if ( this->mLight.lightRadius.y < 1.0 )
      this->mLight.lightRadius.y = 1.0;
    if ( this->mLight.lightRadius.z < 1.0 )
      this->mLight.lightRadius.z = 1.0;
    this->mLight.axis.mat[0].x = *(float *)&st->mParticleTemplate.mTrailTypeName.baseBuffer[16];
    LODWORD(this->mLight.axis.mat[0].y) = st->mParticleTemplate.mTrailMaterial;
    LODWORD(this->mLight.axis.mat[0].z) = st->mParticleTemplate.mTrailMaterialName.len;
    LODWORD(this->mLight.axis.mat[1].x) = st->mParticleTemplate.mTrailMaterialName.data;
    LODWORD(this->mLight.axis.mat[1].y) = st->mParticleTemplate.mTrailMaterialName.alloced;
    this->mLight.axis.mat[1].z = *(float *)st->mParticleTemplate.mTrailMaterialName.baseBuffer;
    this->mLight.axis.mat[2].x = *(float *)&st->mParticleTemplate.mTrailMaterialName.baseBuffer[4];
    v16 = tint.y;
    this->mLight.axis.mat[2].y = *(float *)&st->mParticleTemplate.mTrailMaterialName.baseBuffer[8];
    v17 = tint.z;
    this->mLight.axis.mat[2].z = *(float *)&st->mParticleTemplate.mTrailMaterialName.baseBuffer[12];
    this->mLight.shaderParms[2] = tint.w;
    this->mLight.shaderParms[1] = v17;
    this->mLight.shaderParms[0] = v16;
    this->mLight.shader = *(const idMaterial **)(LODWORD(time) + 88);
    this->mLight.pointLight = 1;
    this->mLight.detailLevel = 10.0;
    this->mLight.noShadows = (*(_DWORD *)(LODWORD(time) + 80) & 0x20000) == 0;
    this->mLight.noSpecular = (*(_DWORD *)(LODWORD(time) + 80) & 0x40000) == 0;
    this->mLightDefHandle = session->rw->AddLightDef(session->rw, &this->mLight);
    return 1;
  }
  return result;
}

// FUNC: public: virtual bool __thiscall rvLightParticle::PresentLight(class rvBSE *,float,bool)
bool __userpurge rvLightParticle::PresentLight@<al>(
        rvLightParticle *this@<ecx>,
        int a2@<esi>,
        rvBSE *effect,
        const rvBSE *time,
        float infinite)
{
  bool result; // al
  float y; // ecx
  float z; // edx
  double v10; // st7
  double v11; // st7
  double v12; // st6
  float x; // eax
  float v14; // edx
  float v15; // ecx
  float w; // edx
  float v17; // [esp+Ch] [ebp-40h]
  float v18; // [esp+14h] [ebp-38h]
  idVec3 position; // [esp+18h] [ebp-34h] BYREF
  float v20; // [esp+24h] [ebp-28h]
  float v21; // [esp+2Ch] [ebp-20h]
  idVec3 size; // [esp+30h] [ebp-1Ch] BYREF
  idVec4 tint; // [esp+3Ch] [ebp-10h] BYREF

  result = rvParticle::GetEvaluationTime(this, *(float *)&time, &infinite, SLOBYTE(infinite));
  if ( result )
  {
    v18 = infinite;
    rvEnvParms3::Evaluate(&this->mTintEnv, infinite, &tint.x);
    rvEnvParms1::Evaluate(&this->mFadeEnv, v18, &tint.w);
    ((void (__thiscall *)(rvLightParticle *, _DWORD, idVec3 *, int))this->EvaluateSize)(
      this,
      LODWORD(infinite),
      &size,
      a2);
    v17 = infinite - this->mMotionStartTime;
    rvParticle::EvaluatePosition(this, time, (idVec3 *)&position.y, v17);
    y = size.y;
    z = size.z;
    v10 = position.z * time->mCurrentAxis.mat[1].x
        + v20 * time->mCurrentAxis.mat[2].x
        + position.y * time->mCurrentAxis.mat[0].x;
    v21 = position.z * time->mCurrentAxis.mat[1].y
        + v20 * time->mCurrentAxis.mat[2].y
        + position.y * time->mCurrentAxis.mat[0].y;
    size.x = position.z * time->mCurrentAxis.mat[1].z
           + v20 * time->mCurrentAxis.mat[2].z
           + position.y * time->mCurrentAxis.mat[0].z;
    v11 = v10 + time->mCurrentOrigin.x;
    v12 = v21 + time->mCurrentOrigin.y;
    size.x = size.x + time->mCurrentOrigin.z;
    this->mLight.origin.z = size.x;
    x = tint.x;
    this->mLight.origin.x = v11;
    this->mLight.origin.y = v12;
    this->mLight.lightRadius.x = y;
    this->mLight.lightRadius.z = x;
    this->mLight.lightRadius.y = z;
    if ( this->mLight.lightRadius.x < 1.0 )
      this->mLight.lightRadius.x = 1.0;
    if ( this->mLight.lightRadius.y < 1.0 )
      this->mLight.lightRadius.y = 1.0;
    if ( this->mLight.lightRadius.z < 1.0 )
      this->mLight.lightRadius.z = 1.0;
    this->mLight.axis.mat[0].x = time->mCurrentAxis.mat[0].x;
    this->mLight.axis.mat[0].y = time->mCurrentAxis.mat[0].y;
    this->mLight.axis.mat[0].z = time->mCurrentAxis.mat[0].z;
    this->mLight.axis.mat[1].x = time->mCurrentAxis.mat[1].x;
    this->mLight.axis.mat[1].y = time->mCurrentAxis.mat[1].y;
    this->mLight.axis.mat[1].z = time->mCurrentAxis.mat[1].z;
    this->mLight.axis.mat[2].x = time->mCurrentAxis.mat[2].x;
    this->mLight.axis.mat[2].y = time->mCurrentAxis.mat[2].y;
    v14 = tint.y;
    this->mLight.axis.mat[2].z = time->mCurrentAxis.mat[2].z;
    v15 = tint.z;
    this->mLight.shaderParms[0] = v14;
    w = tint.w;
    this->mLight.shaderParms[1] = v15;
    this->mLight.shaderParms[2] = w;
    ((void (__thiscall *)(idRenderWorld *, int))session->rw->UpdateLightDef)(session->rw, this->mLightDefHandle);
    return 1;
  }
  return result;
}
