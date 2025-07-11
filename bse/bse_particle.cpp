
// FUNC: public: void __thiscall rvParticle::Attenuate(float,class rvParticleParms &,class rvEnvParms1 &)
void __thiscall rvParticle::Attenuate(rvParticle *this, float atten, rvParticleParms *parms, rvEnvParms1 *result)
{
  int mFlags; // eax
  double v5; // st7

  mFlags = parms->mFlags;
  if ( (mFlags & 0x20) != 0 )
  {
    if ( (mFlags & 0x40) != 0 )
    {
      v5 = 1.0 - atten;
      result->mStart = v5 * result->mStart;
      result->mEnd = v5 * result->mEnd;
    }
    else
    {
      result->mStart = atten * result->mStart;
      result->mEnd = atten * result->mEnd;
    }
  }
}

// FUNC: public: virtual void __thiscall rvLineParticle::HandleTiling(class rvParticleTemplate *)
void __thiscall rvLineParticle::HandleTiling(rvLineParticle *this, rvParticleTemplate *pt)
{
  float *v3; // eax

  if ( (this->mFlags & 0x100000) != 0 )
  {
    v3 = this->GetInitLength(this);
    this->mTextureScale = sqrt(v3[2] * v3[2] + v3[1] * v3[1] + *v3 * *v3) / pt->mTiling;
  }
}

// FUNC: public: virtual void __thiscall rvLinkedParticle::HandleTiling(class rvParticleTemplate *)
void __thiscall rvLinkedParticle::HandleTiling(rvLinkedParticle *this, rvParticleTemplate *pt)
{
  if ( (this->mFlags & 0x100000) != 0 )
    this->mTextureScale = pt->mTiling;
}

// FUNC: public: virtual class rvParticle * __thiscall rvDecalParticle::GetArrayEntry(int)const
rvDecalParticle *__thiscall rvDecalParticle::GetArrayEntry(rvDecalParticle *this, int i)
{
  if ( i < 0 )
    return 0;
  else
    return &this[i];
}

// FUNC: public: virtual class rvParticle * __thiscall rvLineParticle::GetArrayEntry(int)const
rvLineParticle *__thiscall rvLineParticle::GetArrayEntry(rvLineParticle *this, int i)
{
  if ( i < 0 )
    return 0;
  else
    return &this[i];
}

// FUNC: public: virtual int __thiscall rvLineParticle::GetArrayIndex(class rvParticle *)const
unsigned int __thiscall rvLineParticle::GetArrayIndex(rvLineParticle *this, rvParticle *p)
{
  if ( p )
    return ((char *)p - (char *)this) / 0x1A0u;
  else
    return -1;
}

// FUNC: public: virtual int __thiscall rvOrientedParticle::GetArrayIndex(class rvParticle *)const
unsigned int __thiscall rvOrientedParticle::GetArrayIndex(rvModelParticle *this, rvParticle *p)
{
  if ( p )
    return ((char *)p - (char *)this) / 0x1C8u;
  else
    return -1;
}

// FUNC: public: virtual class rvParticle * __thiscall rvElectricityParticle::GetArrayEntry(int)const
rvElectricityParticle *__thiscall rvElectricityParticle::GetArrayEntry(rvElectricityParticle *this, int i)
{
  if ( i < 0 )
    return 0;
  else
    return &this[i];
}

// FUNC: public: virtual int __thiscall rvElectricityParticle::GetArrayIndex(class rvParticle *)const
unsigned int __thiscall rvElectricityParticle::GetArrayIndex(rvElectricityParticle *this, rvParticle *p)
{
  if ( p )
    return ((char *)p - (char *)this) / 0x1DCu;
  else
    return -1;
}

// FUNC: public: virtual int __thiscall rvDecalParticle::GetArrayIndex(class rvParticle *)const
unsigned int __thiscall rvDecalParticle::GetArrayIndex(rvDecalParticle *this, rvParticle *p)
{
  if ( p )
    return ((char *)p - (char *)this) / 0x190u;
  else
    return -1;
}

// FUNC: public: virtual class rvParticle * __thiscall rvOrientedParticle::GetArrayEntry(int)const
rvModelParticle *__thiscall rvOrientedParticle::GetArrayEntry(rvModelParticle *this, int i)
{
  if ( i < 0 )
    return 0;
  else
    return &this[i];
}

// FUNC: public: virtual class rvParticle * __thiscall rvLightParticle::GetArrayEntry(int)const
rvLightParticle *__thiscall rvLightParticle::GetArrayEntry(rvLightParticle *this, int i)
{
  if ( i < 0 )
    return 0;
  else
    return &this[i];
}

// FUNC: public: virtual int __thiscall rvLightParticle::GetArrayIndex(class rvParticle *)const
unsigned int __thiscall rvLightParticle::GetArrayIndex(rvLightParticle *this, rvParticle *p)
{
  if ( p )
    return ((char *)p - (char *)this) / 0x268u;
  else
    return -1;
}

// FUNC: public: virtual class rvParticle * __thiscall rvLinkedParticle::GetArrayEntry(int)const
rvLinkedParticle *__thiscall rvLinkedParticle::GetArrayEntry(rvLinkedParticle *this, int i)
{
  if ( i < 0 )
    return 0;
  else
    return &this[i];
}

// FUNC: public: virtual int __thiscall rvLinkedParticle::GetArrayIndex(class rvParticle *)const
unsigned int __thiscall rvLinkedParticle::GetArrayIndex(rvLinkedParticle *this, rvParticle *p)
{
  if ( p )
    return ((char *)p - (char *)this) / 0x168u;
  else
    return -1;
}

// FUNC: public: virtual class rvParticle * __thiscall rvDebrisParticle::GetArrayEntry(int)const
rvDebrisParticle *__thiscall rvDebrisParticle::GetArrayEntry(rvDebrisParticle *this, int i)
{
  if ( i < 0 )
    return 0;
  else
    return &this[i];
}

// FUNC: public: virtual int __thiscall rvDebrisParticle::GetArrayIndex(class rvParticle *)const
unsigned int __thiscall rvDebrisParticle::GetArrayIndex(rvDebrisParticle *this, rvParticle *p)
{
  if ( p )
    return ((char *)p - (char *)this) / 0x18Cu;
  else
    return -1;
}

// FUNC: public: void __thiscall rvParticle::EvaluateVelocity(class rvBSE const *,class idVec3 &,float)
void __thiscall rvParticle::EvaluateVelocity(rvParticle *this, const rvBSE *effect, idVec3 *velocity, float time)
{
  double v4; // st7
  double v5; // st6
  long double v8; // st7

  if ( (this->mFlags & 1) != 0 )
  {
    velocity->x = 1.0;
    velocity->y = 0.0;
    velocity->z = 0.0;
  }
  else
  {
    velocity->x = time * this->mAcceleration.x + this->mVelocity.x;
    velocity->y = time * this->mAcceleration.y + this->mVelocity.y;
    velocity->z = time * this->mAcceleration.z + this->mVelocity.z;
    v4 = this->mEndTime - this->mStartTime;
    v5 = (v4 - time) / v4 * 1.442695040888963387;
    _ST5 = v5;
    __asm { frndint }
    v8 = (__FSCALE__(__F2XM1__(v5 - _ST5) + 1.0, _ST5) * (1.0 - time * 0.33333334) + 1.0) * time * time * 0.5;
    velocity->x = v8 * this->mFriction.x + velocity->x;
    velocity->y = v8 * this->mFriction.y + velocity->y;
    velocity->z = v8 * this->mFriction.z + velocity->z;
  }
}

// FUNC: public: void __thiscall rvParticle::SetOriginUsingEndOrigin(class rvBSE *,class rvParticleTemplate *,class idVec3 *,class idVec3 *)
void __thiscall rvParticle::SetOriginUsingEndOrigin(
        rvParticle *this,
        rvBSE *effect,
        rvParticleTemplate *pt,
        idVec3 *normal,
        idVec3 *centre)
{
  idCmdArgs *p_mInitPos; // edi
  int mSpawnType; // eax

  p_mInitPos = (idCmdArgs *)&this->mInitPos;
  ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[pt->mSpawnPosition.mSpawnType])((const idCmdArgs *)&this->mInitPos);
  mSpawnType = pt->mSpawnPosition.mSpawnType;
  p_mInitPos->argc = LODWORD(this->mFraction);
  ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[mSpawnType])(p_mInitPos);
}

// FUNC: public: void __thiscall rvParticle::HandleEndOrigin(class rvBSE *,class rvParticleTemplate *,class idVec3 *,class idVec3 *)
void __thiscall rvParticle::HandleEndOrigin(
        rvParticle *this,
        rvBSE *effect,
        rvParticleTemplate *pt,
        idVec3 *normal,
        idVec3 *centre)
{
  this->mInitPos.x = this->mFraction;
  if ( (effect->mFlags & 2) != 0 && (pt->mSpawnPosition.mFlags & 2) != 0 )
    rvParticle::SetOriginUsingEndOrigin(this, effect, pt, normal, centre);
  else
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[pt->mSpawnPosition.mSpawnType])((const idCmdArgs *)&this->mInitPos);
}

// FUNC: public: void __thiscall rvParticle::SetLengthUsingEndOrigin(class rvBSE *,class rvParticleParms &,float *)
void __thiscall rvParticle::SetLengthUsingEndOrigin(
        rvParticle *this,
        rvBSE *effect,
        rvParticleParms *parms,
        float *length)
{
  ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[parms->mSpawnType])((const idCmdArgs *)length);
}

// FUNC: public: void __thiscall rvParticle::Attenuate(float,class rvParticleParms &,class rvEnvParms3 &)
void __thiscall rvParticle::Attenuate(rvParticle *this, float atten, rvParticleParms *parms, rvEnvParms3 *result)
{
  int mFlags; // eax
  double v5; // st7

  mFlags = parms->mFlags;
  if ( (mFlags & 0x20) != 0 )
  {
    if ( (mFlags & 0x40) != 0 )
    {
      v5 = 1.0 - atten;
      result->mStart.x = v5 * result->mStart.x;
      result->mStart.y = v5 * result->mStart.y;
      result->mStart.z = v5 * result->mStart.z;
      result->mEnd.x = v5 * result->mEnd.x;
      result->mEnd.y = v5 * result->mEnd.y;
      result->mEnd.z = v5 * result->mEnd.z;
    }
    else
    {
      result->mStart.x = atten * result->mStart.x;
      result->mStart.y = atten * result->mStart.y;
      result->mStart.z = atten * result->mStart.z;
      result->mEnd.x = atten * result->mEnd.x;
      result->mEnd.y = atten * result->mEnd.y;
      result->mEnd.z = atten * result->mEnd.z;
    }
  }
}

// FUNC: public: void __thiscall rvParticle::Attenuate(float,class rvParticleParms &,class rvEnvParms2 &)
void __thiscall rvParticle::Attenuate(rvParticle *this, float atten, rvParticleParms *parms, rvEnvParms2 *result)
{
  int mFlags; // eax
  double v5; // st7

  mFlags = parms->mFlags;
  if ( (mFlags & 0x20) != 0 )
  {
    if ( (mFlags & 0x40) != 0 )
    {
      v5 = 1.0 - atten;
      result->mStart.x = v5 * result->mStart.x;
      result->mStart.y = v5 * result->mStart.y;
      result->mEnd.x = v5 * result->mEnd.x;
      result->mEnd.y = v5 * result->mEnd.y;
    }
    else
    {
      result->mStart.x = atten * result->mStart.x;
      result->mStart.y = atten * result->mStart.y;
      result->mEnd.x = atten * result->mEnd.x;
      result->mEnd.y = atten * result->mEnd.y;
    }
  }
}

// FUNC: public: virtual void __thiscall rvParticle::FinishSpawn(class rvBSE *,class rvSegment *,float,float,class idVec3 const &,class idMat3 const &)
void __thiscall rvParticle::FinishSpawn(
        rvParticle *this,
        rvBSE *effect,
        rvSegment *segment,
        float birthTime,
        float fraction,
        const idVec3 *initOffset,
        const idMat3 *initAxis)
{
  rvSegmentTemplate *SegmentTemplate; // eax
  rvParticleTemplate *p_mParticleTemplate; // edi
  idVec3 *p_mAcceleration; // ebx
  double v12; // st7
  double v13; // st6
  idVec3 *v14; // ebx
  long double v15; // st4
  long double v16; // st7
  float *v17; // eax
  double v18; // st7
  double v19; // st6
  unsigned __int8 v21; // c2
  unsigned __int8 v22; // c3
  long double v23; // st4
  long double v24; // st7
  float *v25; // eax
  double v26; // st7
  double v27; // st6
  unsigned __int8 v29; // c2
  unsigned __int8 v30; // c3
  long double v31; // st4
  long double v32; // st7
  float *v33; // eax
  double v34; // st7
  double v35; // st6
  float *p_z; // ecx
  float *v37; // eax
  const idVec3 *InterpolatedOffset; // eax
  double v39; // st7
  double v40; // st6
  const idCmdArgs *v41; // eax
  const idCmdArgs *v42; // eax
  const idCmdArgs *v43; // eax
  const idCmdArgs *v44; // eax
  float *v45; // eax
  float *v46; // eax
  float *v47; // eax
  double v48; // st7
  double v49; // st6
  double v50; // st5
  double v51; // st7
  double v52; // st5
  double v53; // st7
  idVec3 *p_mNormal; // [esp+8h] [ebp-6Ch]
  float *v55; // [esp+8h] [ebp-6Ch]
  idVec3 *p_mCentre; // [esp+Ch] [ebp-68h]
  int mNumSizeParms; // [esp+Ch] [ebp-68h]
  float *mNumRotateParms; // [esp+Ch] [ebp-68h]
  int v59; // [esp+10h] [ebp-64h]
  float v60; // [esp+20h] [ebp-54h]
  float v61; // [esp+24h] [ebp-50h]
  float y; // [esp+28h] [ebp-4Ch]
  float z; // [esp+2Ch] [ebp-48h]
  float x; // [esp+30h] [ebp-44h]
  rvSegmentTemplate *st; // [esp+34h] [ebp-40h]
  rvAngles angles; // [esp+38h] [ebp-3Ch] BYREF
  rvAngles result; // [esp+44h] [ebp-30h] BYREF
  idMat3 v68; // [esp+50h] [ebp-24h] BYREF
  int effecta; // [esp+78h] [ebp+4h]
  float effectb; // [esp+78h] [ebp+4h]
  float effectc; // [esp+78h] [ebp+4h]
  float effectd; // [esp+78h] [ebp+4h]
  bool atten; // [esp+7Ch] [ebp+8h]
  float attena; // [esp+7Ch] [ebp+8h]
  bool fractiona; // [esp+84h] [ebp+10h]
  float fractionb; // [esp+84h] [ebp+10h]
  float initAxisa; // [esp+8Ch] [ebp+18h]

  SegmentTemplate = rvSegment::GetSegmentTemplate(segment);
  st = SegmentTemplate;
  if ( SegmentTemplate )
  {
    p_mParticleTemplate = &SegmentTemplate->mParticleTemplate;
    this->mFlags = SegmentTemplate->mParticleTemplate.mFlags;
    if ( rvSegment::GetLocked(segment) )
      this->mFlags |= 2u;
    else
      this->mFlags &= ~2u;
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnVelocity.mSpawnType])((const idCmdArgs *)&this->mVelocity);
    p_mAcceleration = &this->mAcceleration;
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnAcceleration.mSpawnType])((const idCmdArgs *)&this->mAcceleration);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnFriction.mSpawnType])((const idCmdArgs *)&this->mFriction);
    this->mFraction = fraction;
    this->mTextureScale = 1.0;
    fractiona = (p_mParticleTemplate->mFlags & 0x1000) != 0;
    atten = (p_mParticleTemplate->mFlags & 0x800) != 0;
    if ( (p_mParticleTemplate->mFlags & 0x1000) != 0 )
    {
      p_mCentre = 0;
      p_mNormal = &this->mNormal;
    }
    else if ( (p_mParticleTemplate->mFlags & 0x800) != 0 )
    {
      p_mCentre = &p_mParticleTemplate->mCentre;
      p_mNormal = &this->mNormal;
    }
    else
    {
      p_mCentre = 0;
      p_mNormal = 0;
      if ( (p_mParticleTemplate->mFlags & 0x4000) != 0 )
      {
        ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnDirection.mSpawnType])((const idCmdArgs *)&this->mNormal);
        p_mCentre = 0;
        p_mNormal = 0;
      }
      else
      {
        this->mNormal.x = 1.0;
        this->mNormal.y = 0.0;
        this->mNormal.z = 0.0;
      }
    }
    rvParticle::HandleEndOrigin(this, effect, p_mParticleTemplate, p_mNormal, p_mCentre);
    if ( (p_mParticleTemplate->mFlags & 0x80000) != 0 )
    {
      v12 = initAxis->mat[2].x * this->mVelocity.z
          + initAxis->mat[1].x * this->mVelocity.y
          + initAxis->mat[0].x * this->mVelocity.x;
      v13 = initAxis->mat[2].y * this->mVelocity.z
          + initAxis->mat[1].y * this->mVelocity.y
          + initAxis->mat[0].y * this->mVelocity.x;
      this->mVelocity.z = initAxis->mat[2].z * this->mVelocity.z
                        + initAxis->mat[1].z * this->mVelocity.y
                        + initAxis->mat[0].z * this->mVelocity.x;
      this->mVelocity.x = v12;
      this->mVelocity.y = v13;
    }
    angles = *idVec3::ToRadians(&this->mNormal, &result);
    if ( atten || fractiona )
    {
      v14 = &this->mNormal;
      v15 = this->mNormal.x * this->mNormal.x + this->mNormal.y * this->mNormal.y + this->mNormal.z * this->mNormal.z;
      if ( v15 != 0.0 )
      {
        v16 = 1.0 / sqrt(v15);
        v14->x = v16 * v14->x;
        this->mNormal.y = v16 * this->mNormal.y;
        this->mNormal.z = v16 * this->mNormal.z;
      }
      v17 = (float *)idVec3::ToMat3(&this->mNormal, &v68);
      v18 = v17[6] * this->mVelocity.z + v17[3] * this->mVelocity.y + this->mVelocity.x * *v17;
      v19 = v17[7] * this->mVelocity.z + v17[4] * this->mVelocity.y + v17[1] * this->mVelocity.x;
      this->mVelocity.z = v17[8] * this->mVelocity.z + v17[5] * this->mVelocity.y + v17[2] * this->mVelocity.x;
      this->mVelocity.x = v18;
      this->mVelocity.y = v19;
      ((void (__thiscall *)(rvParticle *, _DWORD, _DWORD, _DWORD))this->TransformLength)(
        this,
        LODWORD(v14->x),
        LODWORD(this->mNormal.y),
        LODWORD(this->mNormal.z));
      p_mAcceleration = &this->mAcceleration;
    }
    if ( (p_mParticleTemplate->mFlags & 0x2000) != 0 )
    {
      this->mVelocity.x = this->mVelocity.x * -1.0;
      this->mVelocity.y = this->mVelocity.y * -1.0;
      this->mVelocity.z = this->mVelocity.z * -1.0;
      ((void (__thiscall *)(rvParticle *, int))this->ScaleLength)(this, -1082130432);
    }
    if ( !(v22 | v21) )
    {
      this->mNormal.x = this->mVelocity.x;
      this->mNormal.y = this->mVelocity.y;
      this->mNormal.z = this->mVelocity.z;
      v23 = this->mNormal.x * this->mNormal.x + this->mNormal.y * this->mNormal.y + this->mNormal.z * this->mNormal.z;
      if ( v23 != 0.0 )
      {
        v24 = 1.0 / sqrt(v23);
        this->mNormal.x = v24 * this->mNormal.x;
        this->mNormal.y = v24 * this->mNormal.y;
        this->mNormal.z = v24 * this->mNormal.z;
      }
    }
    v25 = (float *)idVec3::ToMat3(&this->mNormal, &v68);
    v26 = v25[6] * p_mAcceleration->z + v25[3] * p_mAcceleration->y + p_mAcceleration->x * *v25;
    v27 = v25[1] * p_mAcceleration->x + v25[7] * p_mAcceleration->z + v25[4] * p_mAcceleration->y;
    p_mAcceleration->z = v25[2] * p_mAcceleration->x + v25[8] * p_mAcceleration->z + v25[5] * p_mAcceleration->y;
    p_mAcceleration->x = v26;
    p_mAcceleration->y = v27;
    if ( !(v30 | v29) )
    {
      this->mNormal.x = p_mAcceleration->x;
      this->mNormal.y = p_mAcceleration->y;
      this->mNormal.z = p_mAcceleration->z;
      v31 = this->mNormal.x * this->mNormal.x + this->mNormal.y * this->mNormal.y + this->mNormal.z * this->mNormal.z;
      if ( v31 != 0.0 )
      {
        v32 = 1.0 / sqrt(v31);
        this->mNormal.x = v32 * this->mNormal.x;
        this->mNormal.y = v32 * this->mNormal.y;
        this->mNormal.z = v32 * this->mNormal.z;
      }
    }
    v33 = (float *)idVec3::ToMat3(&this->mNormal, &v68);
    v34 = v33[6] * this->mFriction.z + v33[3] * this->mFriction.y + this->mFriction.x * *v33;
    v35 = v33[7] * this->mFriction.z + v33[4] * this->mFriction.y + v33[1] * this->mFriction.x;
    this->mFriction.z = v33[8] * this->mFriction.z + v33[5] * this->mFriction.y + v33[2] * this->mFriction.x;
    this->mFriction.x = v34;
    this->mFriction.y = v35;
    if ( (this->mFlags & 2) == 0 )
    {
      p_z = &this->mInitAxis.mat[0].z;
      v37 = &effect->mCurrentAxis.mat[0].z;
      effecta = 3;
      do
      {
        *(p_z - 2) = *(v37 - 2);
        *(p_z - 1) = *(v37 - 1);
        *p_z = *v37;
        v37 += 3;
        p_z += 3;
        --effecta;
      }
      while ( effecta );
      this->mInitEffectPos.x = effect->mCurrentOrigin.x;
      this->mInitEffectPos.y = effect->mCurrentOrigin.y;
      this->mInitEffectPos.z = effect->mCurrentOrigin.z;
      z = this->mInitAxis.mat[2].z;
      v60 = this->mInitAxis.mat[1].z;
      y = this->mInitAxis.mat[2].y;
      initAxisa = this->mInitAxis.mat[1].y;
      attena = this->mInitAxis.mat[0].z;
      x = this->mInitAxis.mat[2].x;
      v61 = this->mInitAxis.mat[1].x;
      effectb = this->mInitAxis.mat[0].y;
      fractionb = this->mInitAxis.mat[0].x;
      InterpolatedOffset = rvBSE::GetInterpolatedOffset(effect, (const idVec3 *)&result, birthTime);
      v39 = effectb * InterpolatedOffset->y + attena * InterpolatedOffset->z + fractionb * InterpolatedOffset->x;
      v40 = initAxisa * InterpolatedOffset->y + v60 * InterpolatedOffset->z + v61 * InterpolatedOffset->x;
      result.roll = y * InterpolatedOffset->y + z * InterpolatedOffset->z + x * InterpolatedOffset->x;
      this->mInitPos.x = this->mInitPos.x - v39;
      this->mInitPos.y = this->mInitPos.y - v40;
      this->mInitPos.z = this->mInitPos.z - result.roll;
    }
    if ( (p_mParticleTemplate->mFlags & 0x80000) != 0 )
    {
      this->mInitPos.x = this->mInitPos.x + initOffset->x;
      this->mInitPos.y = initOffset->y + this->mInitPos.y;
      this->mInitPos.z = initOffset->z + this->mInitPos.z;
    }
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnTint.mSpawnType])((const idCmdArgs *)&this->mTintEnv.mStart);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnFade.mSpawnType])((const idCmdArgs *)&this->mFadeEnv.mStart);
    v41 = (const idCmdArgs *)this->GetInitSize(this);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnSize.mSpawnType])(v41);
    v42 = (const idCmdArgs *)this->GetInitRotation(this);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnRotate.mSpawnType])(v42);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnAngle.mSpawnType])((const idCmdArgs *)&this->mAngleEnv.mStart);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnOffset.mSpawnType])((const idCmdArgs *)&this->mOffsetEnv.mStart);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mDeathTint.mSpawnType])((const idCmdArgs *)&this->mTintEnv.mEnd);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mDeathFade.mSpawnType])((const idCmdArgs *)&this->mFadeEnv.mEnd);
    v43 = (const idCmdArgs *)this->GetDestSize(this);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mDeathSize.mSpawnType])(v43);
    v44 = (const idCmdArgs *)this->GetDestRotation(this);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mDeathRotate.mSpawnType])(v44);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mDeathAngle.mSpawnType])((const idCmdArgs *)&this->mAngleEnv.mEnd);
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mDeathOffset.mSpawnType])((const idCmdArgs *)&this->mOffsetEnv.mEnd);
    if ( p_mParticleTemplate->mSpawnOffset.mSpawnType != 3 || p_mParticleTemplate->mDeathOffset.mSpawnType != 3 )
      this->mFlags |= 4u;
    rvParticleParms::HandleRelativeParms(
      &p_mParticleTemplate->mDeathTint,
      &this->mTintEnv.mEnd.x,
      &this->mTintEnv.mStart.x,
      3);
    rvParticleParms::HandleRelativeParms(
      &p_mParticleTemplate->mDeathFade,
      &this->mFadeEnv.mEnd,
      &this->mFadeEnv.mStart,
      1);
    mNumSizeParms = p_mParticleTemplate->mNumSizeParms;
    v55 = this->GetInitSize(this);
    v45 = this->GetDestSize(this);
    rvParticleParms::HandleRelativeParms(&p_mParticleTemplate->mDeathSize, v45, v55, mNumSizeParms);
    mNumRotateParms = (float *)p_mParticleTemplate->mNumRotateParms;
    v46 = this->GetInitRotation(this);
    v47 = (float *)((int (__thiscall *)(rvParticle *, float *))this->GetDestRotation)(this, v46);
    rvParticleParms::HandleRelativeParms(&p_mParticleTemplate->mDeathRotate, v47, mNumRotateParms, v59);
    rvParticleParms::HandleRelativeParms(
      &p_mParticleTemplate->mDeathAngle,
      &this->mAngleEnv.mEnd.x,
      &this->mAngleEnv.mStart.x,
      3);
    rvParticleParms::HandleRelativeParms(
      &p_mParticleTemplate->mDeathOffset,
      &this->mOffsetEnv.mEnd.x,
      &this->mOffsetEnv.mStart.x,
      3);
    ((void (__thiscall *)(rvParticle *, _DWORD))this->ScaleRotation)(this, LODWORD(idMath::TWO_PI));
    rvParticle::ScaleAngle(this, idMath::TWO_PI);
    this->HandleOrientation(this, &angles);
    this->mTrailTime = rvRandom::flrand(p_mParticleTemplate->mTrailTime.x, p_mParticleTemplate->mTrailTime.y);
    this->mTrailCount = rvParticleTemplate::GetTrailCount(p_mParticleTemplate);
    this->SetModel(this, p_mParticleTemplate->mModelName.data);
    this->SetupElectricity(this, p_mParticleTemplate);
    effectc = rvBSE::GetAttenuation(effect, st);
    rvParticle::AttenuateFade(this, effectc, &p_mParticleTemplate->mSpawnFade);
    ((void (__thiscall *)(rvParticle *, _DWORD, rvParticleParms *))this->AttenuateSize)(
      this,
      LODWORD(effectc),
      &p_mParticleTemplate->mSpawnSize);
    effectd = rvRandom::flrand(p_mParticleTemplate->mDuration.x, p_mParticleTemplate->mDuration.y);
    this->mStartTime = birthTime;
    this->mEndTime = effectd + birthTime;
    this->mMotionStartTime = birthTime;
    this->mLastTrailTime = birthTime;
    rvEnvParms3::Init(&this->mTintEnv, &p_mParticleTemplate->mTintEnvelope, effectd);
    rvEnvParms1::Init(&this->mFadeEnv, &p_mParticleTemplate->mFadeEnvelope, effectd);
    ((void (__thiscall *)(rvParticle *, rvEnvParms *, _DWORD))this->InitSizeEnv)(
      this,
      &p_mParticleTemplate->mSizeEnvelope,
      LODWORD(effectd));
    ((void (__thiscall *)(rvParticle *, rvEnvParms *, _DWORD))this->InitRotationEnv)(
      this,
      &p_mParticleTemplate->mRotateEnvelope,
      LODWORD(effectd));
    rvEnvParms3::Init(&this->mAngleEnv, &p_mParticleTemplate->mAngleEnvelope, effectd);
    rvEnvParms3::Init(&this->mOffsetEnv, &p_mParticleTemplate->mOffsetEnvelope, effectd);
    v48 = rvRandom::flrand(p_mParticleTemplate->mGravity.x, p_mParticleTemplate->mGravity.y);
    v49 = v48 * effect->mGravity.x;
    v50 = v48;
    v51 = v48 * effect->mGravity.y;
    v52 = v50 * effect->mGravity.z;
    angles.pitch = v52 * effect->mCurrentAxisTransposed.mat[2].x
                 + v51 * effect->mCurrentAxisTransposed.mat[1].x
                 + v49 * effect->mCurrentAxisTransposed.mat[0].x;
    angles.yaw = v52 * effect->mCurrentAxisTransposed.mat[2].y
               + v51 * effect->mCurrentAxisTransposed.mat[1].y
               + v49 * effect->mCurrentAxisTransposed.mat[0].y;
    v53 = v52 * effect->mCurrentAxisTransposed.mat[2].z
        + v51 * effect->mCurrentAxisTransposed.mat[1].z
        + v49 * effect->mCurrentAxisTransposed.mat[0].z;
    p_mAcceleration->x = angles.pitch + p_mAcceleration->x;
    p_mAcceleration->y = angles.yaw + p_mAcceleration->y;
    p_mAcceleration->z = v53 + p_mAcceleration->z;
  }
}

// FUNC: public: virtual void __thiscall rvLineParticle::FinishSpawn(class rvBSE *,class rvSegment *,float,float,class idVec3 const &,class idMat3 const &)
void __userpurge rvLineParticle::FinishSpawn(
        rvLineParticle *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        int a4@<edi>,
        rvBSE *effect,
        rvSegment *segment,
        float birthTime,
        rvBSE *fraction,
        rvSegment *initOffset,
        const idMat3 *initAxis,
        float a11,
        idVec3 *a12,
        idMat3 *a13)
{
  rvSegmentTemplate *SegmentTemplate; // eax
  rvParticleTemplate *p_mParticleTemplate; // edi
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  float duration; // [esp+Ch] [ebp-18h]
  float *v21; // [esp+14h] [ebp-10h]
  float fractiona; // [esp+34h] [ebp+10h]

  SegmentTemplate = rvSegment::GetSegmentTemplate(segment);
  if ( SegmentTemplate )
  {
    p_mParticleTemplate = &SegmentTemplate->mParticleTemplate;
    v16 = (float *)((int (__thiscall *)(rvLineParticle *, int, int, int))this->GetInitLength)(this, a4, a3, a2);
    if ( (fraction->mFlags & 2) != 0 && (p_mParticleTemplate->mSpawnLength.mFlags & 2) != 0 )
      rvParticle::SetLengthUsingEndOrigin(this, fraction, &p_mParticleTemplate->mSpawnLength, v16);
    else
      ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnLength.mSpawnType])((const idCmdArgs *)v16);
    v17 = this->GetDestLength(this);
    if ( (fraction->mFlags & 2) != 0 && (p_mParticleTemplate->mSpawnLength.mFlags & 2) != 0 )
      rvParticle::SetLengthUsingEndOrigin(this, fraction, &p_mParticleTemplate->mDeathLength, v17);
    else
      ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mDeathLength.mSpawnType])((const idCmdArgs *)v17);
    rvParticle::FinishSpawn(this, fraction, initOffset, *(float *)&initAxis, a11, a12, a13);
    v21 = this->GetInitLength(this);
    v18 = this->GetDestLength(this);
    rvParticleParms::HandleRelativeParms(&p_mParticleTemplate->mDeathLength, v18, v21, 3);
    this->HandleTiling(this, p_mParticleTemplate);
    fractiona = rvBSE::GetAttenuation(fraction, (rvSegmentTemplate *)effect);
    ((void (__thiscall *)(rvLineParticle *, _DWORD, rvParticleParms *))this->AttenuateLength)(
      this,
      LODWORD(fractiona),
      &p_mParticleTemplate->mSpawnLength);
    duration = this->mEndTime - this->mStartTime;
    rvEnvParms3::Init(&this->mLengthEnv, &p_mParticleTemplate->mLengthEnvelope, duration);
  }
}

// FUNC: public: virtual void __thiscall rvLinkedParticle::FinishSpawn(class rvBSE *,class rvSegment *,float,float,class idVec3 const &,class idMat3 const &)
void __thiscall rvLinkedParticle::FinishSpawn(
        rvLinkedParticle *this,
        rvBSE *effect,
        rvSegment *segment,
        float birthTime,
        float fraction,
        const idVec3 *initOffset,
        const idMat3 *initAxis)
{
  rvSegmentTemplate *SegmentTemplate; // edi

  SegmentTemplate = rvSegment::GetSegmentTemplate(segment);
  if ( SegmentTemplate )
  {
    rvParticle::FinishSpawn(this, effect, segment, birthTime, fraction, initOffset, initAxis);
    this->HandleTiling(this, &SegmentTemplate->mParticleTemplate);
  }
}

// FUNC: public: virtual void __thiscall rvDebrisParticle::FinishSpawn(class rvBSE *,class rvSegment *,float,float,class idVec3 const &,class idMat3 const &)
void __thiscall rvDebrisParticle::FinishSpawn(
        rvDebrisParticle *this,
        rvBSE *effect,
        rvSegment *segment,
        float birthTime,
        float fraction,
        const idVec3 *initOffset,
        const idMat3 *initAxis)
{
  rvSegmentTemplate *SegmentTemplate; // eax
  rvParticleTemplate *p_mParticleTemplate; // ebx
  idVec3 *p_mNormal; // ecx
  long double v11; // st4
  long double v12; // st7
  float *v13; // eax
  double v14; // st7
  double v15; // st6
  unsigned __int8 v17; // c2
  unsigned __int8 v18; // c3
  long double v19; // st4
  long double v20; // st7
  float z; // edx
  float y; // eax
  float v23; // ecx
  float x; // eax
  float v25; // ecx
  float v26; // edx
  const idVec3 *InterpolatedOffset; // eax
  double v28; // st7
  double v29; // st6
  const idCmdArgs *v30; // eax
  const idCmdArgs *v31; // eax
  double v32; // st7
  double v33; // st6
  double v34; // st5
  double v35; // st7
  double v36; // st5
  double v37; // st7
  double v38; // st7
  double v39; // st7
  double v40; // st6
  double v41; // st7
  float v42; // ecx
  double v43; // st6
  double v44; // st4
  float v45; // ecx
  float v46; // edx
  double v47; // st5
  idMat3 *v48; // [esp+8h] [ebp-B4h]
  float v49; // [esp+1Ch] [ebp-A0h]
  float v50; // [esp+1Ch] [ebp-A0h]
  idVec3 velocity; // [esp+20h] [ebp-9Ch] BYREF
  idVec3 v52; // [esp+2Ch] [ebp-90h] BYREF
  float v53; // [esp+38h] [ebp-84h]
  idMat3 *__that; // [esp+3Ch] [ebp-80h]
  float v55; // [esp+40h] [ebp-7Ch]
  float v56; // [esp+44h] [ebp-78h]
  idVec3 angularVel; // [esp+48h] [ebp-74h] BYREF
  float v58; // [esp+54h] [ebp-68h]
  idVec3 origin; // [esp+58h] [ebp-64h] BYREF
  float v60; // [esp+64h] [ebp-58h]
  float v61; // [esp+68h] [ebp-54h]
  float v62; // [esp+6Ch] [ebp-50h]
  float v63; // [esp+70h] [ebp-4Ch]
  idMat3 axis; // [esp+74h] [ebp-48h] BYREF
  idMat3 result; // [esp+98h] [ebp-24h] BYREF

  if ( bse_debris.internalVar->integerValue )
  {
    if ( !session->readDemo )
    {
      SegmentTemplate = rvSegment::GetSegmentTemplate(segment);
      if ( SegmentTemplate )
      {
        p_mParticleTemplate = &SegmentTemplate->mParticleTemplate;
        this->mFlags = SegmentTemplate->mParticleTemplate.mFlags;
        ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[SegmentTemplate->mParticleTemplate.mSpawnVelocity.mSpawnType])((const idCmdArgs *)&this->mVelocity);
        this->mFraction = fraction;
        this->mTextureScale = 1.0;
        if ( (p_mParticleTemplate->mFlags & 0x1000) != 0 )
        {
          rvParticle::HandleEndOrigin(this, effect, p_mParticleTemplate, &this->mNormal, 0);
        }
        else if ( (p_mParticleTemplate->mFlags & 0x800) != 0 )
        {
          rvParticle::HandleEndOrigin(this, effect, p_mParticleTemplate, &this->mNormal, &p_mParticleTemplate->mCentre);
        }
        else
        {
          rvParticle::HandleEndOrigin(this, effect, p_mParticleTemplate, 0, 0);
          this->mNormal.x = 1.0;
          this->mNormal.y = 0.0;
          this->mNormal.z = 0.0;
        }
        if ( (p_mParticleTemplate->mFlags & 0x800) != 0 || (p_mParticleTemplate->mFlags & 0x1000) != 0 )
        {
          p_mNormal = &this->mNormal;
          v11 = this->mNormal.x * this->mNormal.x
              + this->mNormal.y * this->mNormal.y
              + this->mNormal.z * this->mNormal.z;
          if ( v11 != 0.0 )
          {
            v12 = 1.0 / sqrt(v11);
            p_mNormal->x = v12 * p_mNormal->x;
            this->mNormal.y = v12 * this->mNormal.y;
            this->mNormal.z = v12 * this->mNormal.z;
          }
          v13 = (float *)idVec3::ToMat3(p_mNormal, &result);
          v14 = v13[6] * this->mVelocity.z + v13[3] * this->mVelocity.y + this->mVelocity.x * *v13;
          v15 = v13[1] * this->mVelocity.x + v13[7] * this->mVelocity.z + v13[4] * this->mVelocity.y;
          this->mVelocity.z = v13[2] * this->mVelocity.x + v13[8] * this->mVelocity.z + v13[5] * this->mVelocity.y;
          this->mVelocity.x = v14;
          this->mVelocity.y = v15;
          ((void (__thiscall *)(rvDebrisParticle *, _DWORD, _DWORD, _DWORD))this->TransformLength)(
            this,
            LODWORD(this->mNormal.x),
            LODWORD(this->mNormal.y),
            LODWORD(this->mNormal.z));
        }
        if ( (p_mParticleTemplate->mFlags & 0x2000) != 0 )
        {
          this->mVelocity.x = this->mVelocity.x * -1.0;
          this->mVelocity.y = this->mVelocity.y * -1.0;
          this->mVelocity.z = this->mVelocity.z * -1.0;
          ((void (__thiscall *)(rvDebrisParticle *, int))this->ScaleLength)(this, -1082130432);
        }
        if ( !(v18 | v17) )
        {
          this->mNormal.x = this->mVelocity.x;
          this->mNormal.y = this->mVelocity.y;
          this->mNormal.z = this->mVelocity.z;
          v19 = this->mNormal.x * this->mNormal.x
              + this->mNormal.y * this->mNormal.y
              + this->mNormal.z * this->mNormal.z;
          if ( v19 != 0.0 )
          {
            v20 = 1.0 / sqrt(v19);
            this->mNormal.x = v20 * this->mNormal.x;
            this->mNormal.y = v20 * this->mNormal.y;
            this->mNormal.z = v20 * this->mNormal.z;
          }
        }
        this->mFriction.z = 0.0;
        this->mFriction.y = 0.0;
        this->mFriction.x = 0.0;
        __that = &effect->mCurrentAxis;
        idMat3::operator=(&this->mInitAxis, &effect->mCurrentAxis);
        this->mInitEffectPos = effect->mCurrentOrigin;
        z = this->mInitAxis.mat[0].z;
        v49 = this->mInitAxis.mat[2].z;
        y = this->mInitAxis.mat[2].y;
        v56 = this->mInitAxis.mat[1].z;
        v23 = this->mInitAxis.mat[1].y;
        v53 = y;
        x = this->mInitAxis.mat[2].x;
        v60 = v23;
        v25 = this->mInitAxis.mat[1].x;
        v55 = z;
        v26 = this->mInitAxis.mat[0].y;
        v63 = x;
        v61 = v25;
        v62 = v26;
        v58 = this->mInitAxis.mat[0].x;
        InterpolatedOffset = rvBSE::GetInterpolatedOffset(effect, &v52, birthTime);
        v28 = v58 * InterpolatedOffset->x + v62 * InterpolatedOffset->y + v55 * InterpolatedOffset->z;
        v29 = v61 * InterpolatedOffset->x + v60 * InterpolatedOffset->y + v56 * InterpolatedOffset->z;
        v52.z = v63 * InterpolatedOffset->x + v53 * InterpolatedOffset->y + v49 * InterpolatedOffset->z;
        this->mInitPos.x = this->mInitPos.x - v28;
        this->mInitPos.y = this->mInitPos.y - v29;
        this->mInitPos.z = this->mInitPos.z - v52.z;
        v30 = (const idCmdArgs *)this->GetInitRotation(this);
        ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnRotate.mSpawnType])(v30);
        ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mSpawnAngle.mSpawnType])((const idCmdArgs *)&this->mAngleEnv.mStart);
        v31 = (const idCmdArgs *)this->GetDestRotation(this);
        ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[p_mParticleTemplate->mDeathRotate.mSpawnType])(v31);
        ((void (__thiscall *)(rvDebrisParticle *, _DWORD))this->ScaleRotation)(this, LODWORD(idMath::TWO_PI));
        rvParticle::ScaleAngle(this, idMath::TWO_PI);
        ((void (__thiscall *)(rvDebrisParticle *, rvEnvParms *, int))this->InitRotationEnv)(
          this,
          &p_mParticleTemplate->mRotateEnvelope,
          1065353216);
        rvEnvParms3::Init(&this->mAngleEnv, &p_mParticleTemplate->mAngleEnvelope, 1.0);
        this->mStartTime = birthTime;
        this->mMotionStartTime = birthTime;
        this->mEndTime = birthTime;
        this->mLastTrailTime = birthTime;
        this->mTrailTime = 0.0;
        this->mTrailCount = 0;
        v50 = p_mParticleTemplate->mGravity.y;
        v53 = p_mParticleTemplate->mGravity.x;
        v32 = rvRandom::flrand(v53, v50);
        v33 = v32 * effect->mGravity.x;
        v34 = v32;
        v35 = v32 * effect->mGravity.y;
        v36 = v34 * effect->mGravity.z;
        v52.x = v36 * effect->mCurrentAxisTransposed.mat[2].x
              + v35 * effect->mCurrentAxisTransposed.mat[1].x
              + v33 * effect->mCurrentAxisTransposed.mat[0].x;
        v48 = __that;
        v52.y = v33 * effect->mCurrentAxisTransposed.mat[0].y
              + v36 * effect->mCurrentAxisTransposed.mat[2].y
              + v35 * effect->mCurrentAxisTransposed.mat[1].y;
        v37 = v33 * effect->mCurrentAxisTransposed.mat[0].z
            + v36 * effect->mCurrentAxisTransposed.mat[2].z
            + v35 * effect->mCurrentAxisTransposed.mat[1].z;
        this->mAcceleration.x = v52.x + this->mAcceleration.x;
        this->mAcceleration.y = v52.y + this->mAcceleration.y;
        this->mAcceleration.z = v37 + this->mAcceleration.z;
        v38 = effect->mOriginalAxis.mat[1].x * this->mInitPos.y
            + effect->mOriginalAxis.mat[2].x * this->mInitPos.z
            + effect->mOriginalAxis.mat[0].x * this->mInitPos.x;
        v52.y = effect->mOriginalAxis.mat[1].y * this->mInitPos.y
              + effect->mOriginalAxis.mat[2].y * this->mInitPos.z
              + effect->mOriginalAxis.mat[0].y * this->mInitPos.x;
        v52.z = effect->mOriginalAxis.mat[1].z * this->mInitPos.y
              + effect->mOriginalAxis.mat[2].z * this->mInitPos.z
              + effect->mOriginalAxis.mat[0].z * this->mInitPos.x;
        v39 = v38 + effect->mOriginalOrigin.x;
        v40 = v52.y + effect->mOriginalOrigin.y;
        v52.z = v52.z + effect->mOriginalOrigin.z;
        origin.z = v52.z;
        origin.x = v39;
        origin.y = v40;
        idMat3::operator=(&axis, v48);
        v41 = this->mVelocity.x;
        v42 = this->mVelocity.y;
        velocity.z = this->mVelocity.z;
        velocity.y = v42;
        v43 = axis.mat[2].x * velocity.z + axis.mat[1].x * v42 + axis.mat[0].x * v41;
        v44 = axis.mat[1].y * v42;
        v45 = this->mRotationEnv.mEnd.y;
        v46 = this->mRotationEnv.mEnd.z;
        angularVel.x = this->mRotationEnv.mEnd.x;
        angularVel.y = v45;
        angularVel.z = v46;
        v47 = axis.mat[2].y * velocity.z + v44 + axis.mat[0].y * v41;
        velocity.z = axis.mat[2].z * velocity.z + axis.mat[1].z * velocity.y + axis.mat[0].z * v41;
        velocity.x = v43;
        velocity.y = v47;
        *(float *)&__that = (this->mEndTime - this->mStartTime) * 1000.0;
        game->SpawnClientMoveable(
          game,
          p_mParticleTemplate->mEntityDefName.data,
          (int)*(float *)&__that,
          &origin,
          &axis,
          &velocity,
          &angularVel);
      }
    }
  }
}

// FUNC: public: virtual void __thiscall rvLineParticle::Refresh(class rvBSE *,class rvSegmentTemplate *,class rvParticleTemplate *)
void __thiscall rvLineParticle::Refresh(
        rvLineParticle *this,
        rvBSE *effect,
        rvSegmentTemplate *st,
        rvParticleTemplate *pt)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float duration; // [esp+4h] [ebp-14h]
  int v10; // [esp+8h] [ebp-10h]

  v5 = this->GetInitLength(this);
  if ( (effect->mFlags & 2) != 0 && (pt->mSpawnLength.mFlags & 2) != 0 )
    rvParticle::SetLengthUsingEndOrigin(this, effect, &pt->mSpawnLength, v5);
  else
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[pt->mSpawnLength.mSpawnType])((const idCmdArgs *)v5);
  v6 = this->GetDestLength(this);
  if ( (effect->mFlags & 2) != 0 && (pt->mSpawnLength.mFlags & 2) != 0 )
    rvParticle::SetLengthUsingEndOrigin(this, effect, &pt->mDeathLength, v6);
  else
    ((void (__cdecl *)(const idCmdArgs *))rvParticleParms::spawnFunctions[pt->mDeathLength.mSpawnType])((const idCmdArgs *)v6);
  v7 = this->GetInitLength(this);
  v8 = (float *)((int (__thiscall *)(rvLineParticle *, float *))this->GetDestLength)(this, v7);
  rvParticleParms::HandleRelativeParms(&pt->mDeathLength, v8, (float *)3, v10);
  this->HandleTiling(this, pt);
  duration = this->mEndTime - this->mStartTime;
  rvEnvParms3::Init(&this->mLengthEnv, &pt->mLengthEnvelope, duration);
}

// FUNC: public: virtual void __thiscall rvSpriteParticle::GetSpawnInfo(class idVec4 &,class idVec3 &,class idVec3 &)
void __thiscall rvSpriteParticle::GetSpawnInfo(rvSpriteParticle *this, idVec4 *tint, idVec3 *size, idVec3 *rotate)
{
  tint->x = this->mTintEnv.mStart.x;
  tint->y = this->mTintEnv.mStart.y;
  tint->z = this->mTintEnv.mStart.z;
  tint->w = this->mTintEnv.mRate.x;
  size->x = this->mSizeEnv.mStart.x;
  size->y = this->mSizeEnv.mStart.y;
  size->z = 0.0;
  rotate->x = this->mRotationEnv.mStart;
  rotate->y = 0.0;
  rotate->z = 0.0;
}

// FUNC: public: virtual void __thiscall rvLineParticle::GetSpawnInfo(class idVec4 &,class idVec3 &,class idVec3 &)
void __thiscall rvLineParticle::GetSpawnInfo(rvLineParticle *this, idVec4 *tint, idVec3 *size, idVec3 *rotate)
{
  tint->x = this->mTintEnv.mStart.x;
  tint->y = this->mTintEnv.mStart.y;
  tint->z = this->mTintEnv.mStart.z;
  tint->w = this->mTintEnv.mRate.x;
  size->x = this->mSizeEnv.mStart;
  size->y = 0.0;
  size->z = 0.0;
  rotate->x = 0.0;
  rotate->y = 0.0;
  rotate->z = 0.0;
}

// FUNC: public: virtual void __thiscall rvOrientedParticle::GetSpawnInfo(class idVec4 &,class idVec3 &,class idVec3 &)
void __thiscall rvOrientedParticle::GetSpawnInfo(rvOrientedParticle *this, idVec4 *tint, idVec3 *size, idVec3 *rotate)
{
  size->z = 0.0;
  size->y = 0.0;
  size->x = 0.0;
  tint->x = this->mTintEnv.mStart.x;
  tint->y = this->mTintEnv.mStart.y;
  tint->z = this->mTintEnv.mStart.z;
  tint->w = this->mTintEnv.mRate.x;
  size->x = this->mSizeEnv.mStart.x;
  size->y = this->mSizeEnv.mStart.y;
  size->z = 0.0;
  *rotate = this->mRotationEnv.mStart;
}

// FUNC: public: virtual void __thiscall rvModelParticle::GetSpawnInfo(class idVec4 &,class idVec3 &,class idVec3 &)
void __thiscall rvModelParticle::GetSpawnInfo(rvModelParticle *this, idVec4 *tint, idVec3 *size, idVec3 *rotate)
{
  tint->x = this->mTintEnv.mStart.x;
  tint->y = this->mTintEnv.mStart.y;
  tint->z = this->mTintEnv.mStart.z;
  tint->w = this->mTintEnv.mRate.x;
  *size = this->mSizeEnv.mStart;
  *rotate = this->mRotationEnv.mStart;
}

// FUNC: public: virtual void __thiscall rvLightParticle::GetSpawnInfo(class idVec4 &,class idVec3 &,class idVec3 &)
void __thiscall rvLightParticle::GetSpawnInfo(rvLightParticle *this, idVec4 *tint, idVec3 *size, idVec3 *rotate)
{
  tint->x = this->mTintEnv.mStart.x;
  tint->y = this->mTintEnv.mStart.y;
  tint->z = this->mTintEnv.mStart.z;
  tint->w = this->mTintEnv.mRate.x;
  *size = this->mSizeEnv.mStart;
  rotate->x = 0.0;
  rotate->y = 0.0;
  rotate->z = 0.0;
}

// FUNC: public: void __thiscall rvParticle::Bounce(class rvBSE *,class rvParticleTemplate *,class idVec3,class idVec3,float)
void __thiscall rvParticle::Bounce(
        rvParticle *this,
        rvBSE *effect,
        rvParticleTemplate *pt,
        idVec3 endPos,
        idVec3 normal,
        float time)
{
  float *v7; // edx
  double v8; // st7
  double v9; // st6
  double v10; // st5
  double y; // st4
  double v12; // st5
  double x; // st4
  double v14; // st4
  double v15; // st5
  double v16; // st5
  double mBounce; // st5
  double v18; // st7
  double v19; // st6
  double v20; // st5
  double v21; // st7
  double v22; // st7
  double v23; // st6
  double v24; // st6
  double v25; // rt0
  unsigned __int8 v27; // c0
  unsigned __int8 v28; // c2
  float v29; // [esp+0h] [ebp-2Ch]
  idVec3 oldVelocity; // [esp+8h] [ebp-24h] BYREF
  float v31; // [esp+18h] [ebp-14h]
  float v32; // [esp+1Ch] [ebp-10h]
  float v33; // [esp+28h] [ebp-4h]
  float endPos_8; // [esp+40h] [ebp+14h]

  v29 = time - this->mMotionStartTime;
  rvParticle::EvaluateVelocity(this, effect, &oldVelocity, v29);
  v8 = oldVelocity.z * v7[69] + oldVelocity.y * v7[66] + oldVelocity.x * v7[63];
  v9 = oldVelocity.z * v7[70] + oldVelocity.y * v7[67] + oldVelocity.x * v7[64];
  v10 = oldVelocity.z * v7[71];
  y = oldVelocity.y;
  oldVelocity.y = normal.y;
  v12 = v10 + y * v7[68];
  x = oldVelocity.x;
  oldVelocity.x = normal.x;
  v14 = x * v7[65];
  oldVelocity.z = normal.z;
  v33 = v12 + v14;
  v15 = normal.z * v33 + normal.y * v9 + normal.x * v8;
  v16 = v15 + v15;
  v31 = normal.y * v16;
  v32 = normal.z * v16;
  oldVelocity.x = v8 - normal.x * v16;
  mBounce = pt->mBounce;
  oldVelocity.x = oldVelocity.x * mBounce;
  oldVelocity.y = (v9 - v31) * mBounce;
  v18 = mBounce * (v33 - v32);
  v19 = v18 * v7[78] + oldVelocity.y * v7[75] + oldVelocity.x * v7[72];
  v20 = v18;
  v21 = v18 * v7[79] + oldVelocity.y * v7[76] + oldVelocity.x * v7[73];
  v33 = v20 * v7[80] + oldVelocity.y * v7[77] + oldVelocity.x * v7[74];
  this->mVelocity.z = v33;
  this->mVelocity.x = v19;
  this->mVelocity.y = v21;
  this->mMotionStartTime = time;
  v22 = endPos.x - v7[54];
  oldVelocity.y = endPos.y - v7[55];
  v23 = endPos.z - v7[56];
  oldVelocity.z = v23;
  v24 = v23 * v7[78] + oldVelocity.y * v7[75] + v22 * v7[72];
  v25 = oldVelocity.z * v7[79] + oldVelocity.y * v7[76] + v22 * v7[73];
  endPos_8 = oldVelocity.z * v7[80] + oldVelocity.y * v7[77] + v22 * v7[74];
  this->mInitPos.z = endPos_8;
  this->mInitPos.x = v24;
  this->mInitPos.y = v25;
  if ( v27 | v28 )
  {
    if ( -1.0 / 1.4142135 > normal.z * v7[49] + normal.y * v7[48] + normal.x * v7[47] )
    {
      this->mFlags |= 1u;
      this->mVelocity.z = 0.0;
      this->mVelocity.y = 0.0;
      this->mVelocity.x = 0.0;
    }
  }
}

// FUNC: public: void __thiscall rvParticle::EvaluatePosition(class rvBSE const *,class idVec3 &,float)
void __thiscall rvParticle::EvaluatePosition(rvParticle *this, const rvBSE *effect, idVec3 *pos, float time)
{
  float *v5; // eax
  double v6; // st7
  double v7; // st6
  double v8; // st7
  unsigned __int8 v10; // c2
  unsigned __int8 v11; // c3
  double v12; // st6
  double v13; // st5
  long double v16; // st7
  double v18; // st7
  double v19; // st6
  double v20; // st5
  double v21; // st4
  double v22; // st3
  idVec3 offset; // [esp+Ch] [ebp-60h] BYREF
  rvAngles angle; // [esp+18h] [ebp-54h] BYREF
  float v25[9]; // [esp+24h] [ebp-48h] BYREF
  idMat3 mat; // [esp+48h] [ebp-24h] BYREF

  if ( (this->mFlags & 1) != 0 )
  {
    *pos = this->mInitPos;
  }
  else
  {
    pos->x = time * this->mVelocity.x + this->mInitPos.x;
    pos->y = time * this->mVelocity.y + this->mInitPos.y;
    pos->z = time * this->mVelocity.z + this->mInitPos.z;
    if ( (this->mFlags & 4) != 0 )
    {
      rvEnvParms3::Evaluate(&this->mAngleEnv, time, &angle.pitch);
      rvEnvParms3::Evaluate(&this->mOffsetEnv, time, &offset.x);
      v5 = (float *)rvAngles::ToMat3(&angle, &mat);
      v6 = offset.y * v5[3] + offset.z * v5[6] + offset.x * *v5;
      v7 = offset.y * v5[4] + offset.z * v5[7] + offset.x * v5[1];
      offset.z = offset.y * v5[5] + offset.z * v5[8] + offset.x * v5[2];
      pos->x = v6 + pos->x;
      pos->y = v7 + pos->y;
      pos->z = offset.z + pos->z;
    }
    v8 = time * time * 0.5;
    pos->x = v8 * this->mAcceleration.x + pos->x;
    pos->y = v8 * this->mAcceleration.y + pos->y;
    pos->z = v8 * this->mAcceleration.z + pos->z;
    if ( !(v11 | v10) )
    {
      v12 = this->mEndTime - this->mStartTime;
      v13 = (v12 - v8) / v12 * 1.442695040888963387;
      _ST4 = v13;
      __asm { frndint }
      v16 = v8 * ((__FSCALE__(__F2XM1__(v13 - _ST4) + 1.0, _ST4) - 1.0) * v8) * 0.33333334;
      pos->x = v16 * this->mFriction.x + pos->x;
      pos->y = v16 * this->mFriction.y + pos->y;
      pos->z = v16 * this->mFriction.z + pos->z;
    }
  }
  if ( (this->mFlags & 2) == 0 )
  {
    v25[0] = this->mInitAxis.mat[0].y * effect->mCurrentAxis.mat[0].y
           + effect->mCurrentAxis.mat[0].z * this->mInitAxis.mat[0].z
           + this->mInitAxis.mat[0].x * effect->mCurrentAxis.mat[0].x;
    v25[1] = this->mInitAxis.mat[0].y * effect->mCurrentAxis.mat[1].y
           + effect->mCurrentAxis.mat[1].z * this->mInitAxis.mat[0].z
           + this->mInitAxis.mat[0].x * effect->mCurrentAxis.mat[1].x;
    v25[2] = this->mInitAxis.mat[0].y * effect->mCurrentAxis.mat[2].y
           + this->mInitAxis.mat[0].x * effect->mCurrentAxis.mat[2].x
           + effect->mCurrentAxis.mat[2].z * this->mInitAxis.mat[0].z;
    v25[3] = this->mInitAxis.mat[1].y * effect->mCurrentAxis.mat[0].y
           + this->mInitAxis.mat[1].z * effect->mCurrentAxis.mat[0].z
           + this->mInitAxis.mat[1].x * effect->mCurrentAxis.mat[0].x;
    v25[4] = effect->mCurrentAxis.mat[1].z * this->mInitAxis.mat[1].z
           + effect->mCurrentAxis.mat[1].y * this->mInitAxis.mat[1].y
           + effect->mCurrentAxis.mat[1].x * this->mInitAxis.mat[1].x;
    v25[5] = this->mInitAxis.mat[1].z * effect->mCurrentAxis.mat[2].z
           + this->mInitAxis.mat[1].y * effect->mCurrentAxis.mat[2].y
           + this->mInitAxis.mat[1].x * effect->mCurrentAxis.mat[2].x;
    v25[6] = this->mInitAxis.mat[2].y * effect->mCurrentAxis.mat[0].y
           + this->mInitAxis.mat[2].z * effect->mCurrentAxis.mat[0].z
           + this->mInitAxis.mat[2].x * effect->mCurrentAxis.mat[0].x;
    v25[7] = effect->mCurrentAxis.mat[1].z * this->mInitAxis.mat[2].z
           + effect->mCurrentAxis.mat[1].y * this->mInitAxis.mat[2].y
           + effect->mCurrentAxis.mat[1].x * this->mInitAxis.mat[2].x;
    v25[8] = this->mInitAxis.mat[2].z * effect->mCurrentAxis.mat[2].z
           + this->mInitAxis.mat[2].y * effect->mCurrentAxis.mat[2].y
           + this->mInitAxis.mat[2].x * effect->mCurrentAxis.mat[2].x;
    qmemcpy(&mat, v25, sizeof(mat));
    v18 = mat.mat[2].x * pos->z + mat.mat[1].x * pos->y + mat.mat[0].x * pos->x;
    v19 = mat.mat[2].y * pos->z + mat.mat[1].y * pos->y + mat.mat[0].y * pos->x;
    pos->z = mat.mat[2].z * pos->z + mat.mat[1].z * pos->y + mat.mat[0].z * pos->x;
    pos->x = v18;
    pos->y = v19;
    v20 = this->mInitEffectPos.x - effect->mCurrentOrigin.x;
    v21 = this->mInitEffectPos.y - effect->mCurrentOrigin.y;
    v22 = this->mInitEffectPos.z - effect->mCurrentOrigin.z;
    offset.x = v22 * effect->mCurrentAxisTransposed.mat[2].x
             + v21 * effect->mCurrentAxisTransposed.mat[1].x
             + v20 * effect->mCurrentAxisTransposed.mat[0].x;
    offset.y = v22 * effect->mCurrentAxisTransposed.mat[2].y
             + v21 * effect->mCurrentAxisTransposed.mat[1].y
             + v20 * effect->mCurrentAxisTransposed.mat[0].y;
    offset.z = v22 * effect->mCurrentAxisTransposed.mat[2].z
             + v21 * effect->mCurrentAxisTransposed.mat[1].z
             + v20 * effect->mCurrentAxisTransposed.mat[0].z;
    pos->x = offset.x + v18;
    pos->y = offset.y + v19;
    pos->z = offset.z + pos->z;
  }
}

// FUNC: public: void __thiscall rvParticle::CheckTimeoutEffect(class rvBSE *,class rvSegmentTemplate *,float)
void __thiscall rvParticle::CheckTimeoutEffect(rvParticle *this, rvBSE *effect, rvSegmentTemplate *st, float time)
{
  int mNumTimeoutEffects; // eax
  int v6; // ebx
  long double x; // st7
  long double y; // st6
  long double z; // st5
  long double v10; // st4
  long double v11; // rt0
  double v12; // st7
  double v13; // st6
  idGame_vtbl *v14; // esi
  idMat3 *v15; // eax
  float v16; // [esp+0h] [ebp-5Ch]
  float v17; // [esp+0h] [ebp-5Ch]
  idVec3 position; // [esp+14h] [ebp-48h] BYREF
  idVec3 velocity; // [esp+20h] [ebp-3Ch] BYREF
  float v20; // [esp+34h] [ebp-28h]
  idMat3 result; // [esp+38h] [ebp-24h] BYREF

  if ( (st->mFlags & 1) != 0 )
  {
    mNumTimeoutEffects = st->mParticleTemplate.mNumTimeoutEffects;
    if ( mNumTimeoutEffects )
    {
      v6 = rvRandom::irand(0, mNumTimeoutEffects - 1);
      v16 = time - this->mMotionStartTime;
      rvParticle::EvaluatePosition(this, effect, &position, v16);
      v17 = time - this->mMotionStartTime;
      rvParticle::EvaluateVelocity(this, effect, &velocity, v17);
      x = velocity.x;
      y = velocity.y;
      z = velocity.z;
      v10 = z * z + y * y + x * x;
      if ( v10 != 0.0 )
      {
        v11 = 1.0 / sqrt(v10);
        x = x * v11;
        y = y * v11;
        z = z * v11;
      }
      velocity.x = z * effect->mCurrentAxis.mat[2].x
                 + y * effect->mCurrentAxis.mat[1].x
                 + x * effect->mCurrentAxis.mat[0].x;
      velocity.y = z * effect->mCurrentAxis.mat[2].y
                 + y * effect->mCurrentAxis.mat[1].y
                 + x * effect->mCurrentAxis.mat[0].y;
      velocity.z = z * effect->mCurrentAxis.mat[2].z
                 + y * effect->mCurrentAxis.mat[1].z
                 + x * effect->mCurrentAxis.mat[0].z;
      v12 = position.y * effect->mCurrentAxis.mat[1].x
          + position.z * effect->mCurrentAxis.mat[2].x
          + position.x * effect->mCurrentAxis.mat[0].x;
      v13 = position.y * effect->mCurrentAxis.mat[1].y
          + position.z * effect->mCurrentAxis.mat[2].y
          + position.x * effect->mCurrentAxis.mat[0].y;
      v20 = position.y * effect->mCurrentAxis.mat[1].z
          + position.z * effect->mCurrentAxis.mat[2].z
          + position.x * effect->mCurrentAxis.mat[0].z;
      position.x = v12 + effect->mCurrentOrigin.x;
      position.y = v13 + effect->mCurrentOrigin.y;
      position.z = v20 + effect->mCurrentOrigin.z;
      v14 = game->__vftable;
      v15 = idVec3::ToMat3(&velocity, &result);
      v14->PlayEffect(
        game,
        st->mParticleTemplate.mTimeoutEffects[v6],
        &position,
        v15,
        0,
        &vec3_origin,
        0,
        EC_IGNORE,
        &vec4_one);
    }
  }
}

// FUNC: public: void __thiscall rvParticle::CalcImpactPoint(class idVec3 &,class idVec3 const &,class idVec3 const &,class idBounds const &,class idVec3 const &)
void __thiscall rvParticle::CalcImpactPoint(
        rvParticle *this,
        idVec3 *endPos,
        const idVec3 *origin,
        const idVec3 *motion,
        const idBounds *bounds,
        const idVec3 *normal)
{
  unsigned __int8 v9; // c2
  unsigned __int8 v10; // c3
  unsigned __int8 v12; // c2
  unsigned __int8 v13; // c3
  double x; // st7
  double y; // st6
  double v16; // st5
  double v17; // st7
  long double v18; // st7
  long double v19; // st7
  int v20; // eax
  long double v21; // st7
  double v22; // st6
  double v23; // st5
  double v24; // rt1
  double v25; // st5
  double v26; // st4
  double v27; // st5
  idVec3 work; // [esp+0h] [ebp-24h]
  float v29; // [esp+Ch] [ebp-18h]
  float v30; // [esp+10h] [ebp-14h]
  float v31; // [esp+14h] [ebp-10h]
  float v32; // [esp+20h] [ebp-4h]
  float endPosa; // [esp+28h] [ebp+4h]
  float origina; // [esp+2Ch] [ebp+8h]
  float boundsa; // [esp+34h] [ebp+10h]

  *endPos = *origin;
  if ( !(v10 | v9) && !(v13 | v12) )
  {
    x = motion->x;
    y = motion->y;
    work.z = motion->z;
    v16 = bounds->b[1].x - bounds->b[0].x;
    v30 = bounds->b[1].y - bounds->b[0].y;
    v31 = bounds->b[1].z - bounds->b[0].z;
    work.x = x / v16;
    work.y = y / v30;
    v17 = work.z / v31;
    work.z = v17;
    v18 = v17 * work.z + work.y * work.y + work.x * work.x;
    if ( v18 != 0.0 )
    {
      v19 = 1.0 / sqrt(v18);
      work.x = work.x * v19;
      work.y = work.y * v19;
      work.z = work.z * v19;
    }
    origina = fabs(work.x);
    boundsa = fabs(work.y);
    endPosa = fabs(work.z);
    if ( origina < (double)boundsa || origina < (double)endPosa )
    {
      if ( boundsa >= (double)origina && boundsa >= (double)endPosa )
      {
        v20 = 1;
LABEL_14:
        v21 = 0.5 / fabs(*(&work.x + v20));
        v22 = bounds->b[1].x - bounds->b[0].x;
        v23 = bounds->b[1].y - bounds->b[0].y;
        v32 = bounds->b[1].z - bounds->b[0].z;
        v24 = v23;
        v29 = v22 * v21;
        v31 = v32 * v21;
        work.x = v29 * work.x;
        v25 = normal->x + normal->x;
        v26 = normal->y + normal->y;
        v32 = normal->z + normal->z;
        v29 = v25 + work.x;
        v30 = v26 + v24 * v21 * work.y;
        v27 = v32 + v31 * work.z;
        endPos->x = v29 + endPos->x;
        endPos->y = v30 + endPos->y;
        endPos->z = v27 + endPos->z;
        return;
      }
      if ( endPosa >= (double)origina && endPosa >= (double)boundsa )
      {
        v20 = 2;
        goto LABEL_14;
      }
    }
    v20 = 0;
    goto LABEL_14;
  }
}

// FUNC: public: void __thiscall rvParticle::EmitSmokeParticles(class rvBSE *,class rvSegment *,float)
void __thiscall rvParticle::EmitSmokeParticles(rvParticle *this, rvBSE *effect, rvSegment *child, float time)
{
  rvSegmentTemplate *SegmentTemplate; // ebx
  long double v6; // st7
  long double v7; // st7
  const idMat3 *v8; // eax
  float v9; // [esp+0h] [ebp-50h]
  float v10; // [esp+0h] [ebp-50h]
  idVec3 velocity; // [esp+14h] [ebp-3Ch] BYREF
  idVec3 position; // [esp+20h] [ebp-30h] BYREF
  idMat3 result; // [esp+2Ch] [ebp-24h] BYREF
  float timea; // [esp+5Ch] [ebp+Ch]

  for ( timea = time + 0.016000001;
        this->mLastTrailTime < (double)timea;
        this->mLastTrailTime = rvSegment::AttenuateInterval(child, effect, SegmentTemplate) + this->mLastTrailTime )
  {
    SegmentTemplate = rvSegment::GetSegmentTemplate(child);
    if ( this->mLastTrailTime >= (double)this->mStartTime && this->mLastTrailTime < (double)this->mEndTime )
    {
      v9 = this->mLastTrailTime - this->mStartTime;
      rvParticle::EvaluatePosition(this, effect, &position, v9);
      v10 = this->mLastTrailTime - this->mStartTime;
      rvParticle::EvaluateVelocity(this, effect, &velocity, v10);
      v6 = velocity.z * velocity.z + velocity.y * velocity.y + velocity.x * velocity.x;
      if ( v6 != 0.0 )
      {
        v7 = 1.0 / sqrt(v6);
        velocity.x = velocity.x * v7;
        velocity.y = velocity.y * v7;
        velocity.z = velocity.z * v7;
      }
      v8 = idVec3::ToMat3(&velocity, &result);
      rvSegment::SpawnParticle(child, effect, SegmentTemplate, this->mLastTrailTime, &position, v8);
    }
  }
}

// FUNC: public: bool __thiscall rvParticle::RunPhysics(class rvBSE *,class rvSegmentTemplate *,float)
bool __thiscall rvParticle::RunPhysics(rvParticle *this, rvBSE *effect, rvSegmentTemplate *st, float time)
{
  rvParticleTemplate *p_mParticleTemplate; // edi
  float y; // ecx
  float z; // edx
  double v9; // st7
  double v10; // st7
  double v11; // st7
  idTraceModel *TraceModel; // ebx
  int v13; // eax
  idGame_vtbl *v14; // ebx
  idMat3 *v15; // eax
  int v16; // eax
  float v18; // [esp+4h] [ebp-ECh]
  float v19; // [esp+4h] [ebp-ECh]
  idVec3 dest; // [esp+18h] [ebp-D8h] BYREF
  idVec3 source; // [esp+24h] [ebp-CCh] BYREF
  idVec3 motion; // [esp+30h] [ebp-C0h] BYREF
  idVec3 endPos; // [esp+3Ch] [ebp-B4h] BYREF
  int random; // [esp+48h] [ebp-A8h]
  float v25; // [esp+54h] [ebp-9Ch]
  trace_t trace; // [esp+58h] [ebp-98h] BYREF
  idMat3 result; // [esp+CCh] [ebp-24h] BYREF

  if ( !bse_physics.internalVar->integerValue )
    goto LABEL_18;
  if ( session->readDemo )
    goto LABEL_18;
  if ( (this->mFlags & 1) != 0 )
    goto LABEL_18;
  if ( (st->mFlags & 1) == 0 )
    goto LABEL_18;
  p_mParticleTemplate = &st->mParticleTemplate;
  if ( (st->mParticleTemplate.mFlags & 0x200) == 0 || time - this->mMotionStartTime < 0.1 )
    goto LABEL_18;
  if ( com_debugHudActive )
    ++dword_1137DDAC;
  y = effect->mCurrentOrigin.y;
  z = effect->mCurrentOrigin.z;
  v9 = time - this->mMotionStartTime - 0.1;
  endPos.x = effect->mCurrentOrigin.x;
  v18 = v9;
  endPos.y = y;
  endPos.z = z;
  rvParticle::EvaluatePosition(this, effect, &source, v18);
  v10 = source.y * effect->mCurrentAxis.mat[1].x
      + source.z * effect->mCurrentAxis.mat[2].x
      + source.x * effect->mCurrentAxis.mat[0].x;
  motion.y = source.y * effect->mCurrentAxis.mat[1].y
           + source.z * effect->mCurrentAxis.mat[2].y
           + source.x * effect->mCurrentAxis.mat[0].y;
  motion.z = source.y * effect->mCurrentAxis.mat[1].z
           + source.z * effect->mCurrentAxis.mat[2].z
           + source.x * effect->mCurrentAxis.mat[0].z;
  motion.z = motion.z + endPos.z;
  source.x = v10 + endPos.x;
  source.z = motion.z;
  source.y = motion.y + endPos.y;
  v19 = time - this->mMotionStartTime;
  rvParticle::EvaluatePosition(this, effect, &dest, v19);
  v11 = dest.y * effect->mCurrentAxis.mat[1].x
      + dest.z * effect->mCurrentAxis.mat[2].x
      + dest.x * effect->mCurrentAxis.mat[0].x;
  motion.y = dest.y * effect->mCurrentAxis.mat[1].y
           + dest.z * effect->mCurrentAxis.mat[2].y
           + dest.x * effect->mCurrentAxis.mat[0].y;
  motion.z = dest.y * effect->mCurrentAxis.mat[1].z
           + dest.z * effect->mCurrentAxis.mat[2].z
           + dest.x * effect->mCurrentAxis.mat[0].z;
  motion.z = motion.z + endPos.z;
  dest.z = motion.z;
  dest.x = v11 + endPos.x;
  dest.y = motion.y + endPos.y;
  TraceModel = rvParticleTemplate::GetTraceModel(p_mParticleTemplate);
  game->Translation(game, &trace, &source, &dest, TraceModel, 2049);
  if ( trace.fraction < 1.0 )
  {
    if ( st->mParticleTemplate.mNumImpactEffects && bse->CanPlayRateLimited(bse, EC_IMPACT_PARTICLES) )
    {
      endPos = trace.endpos;
      if ( TraceModel )
      {
        v25 = dest.z - source.z;
        motion.x = (dest.x - source.x) * trace.fraction;
        motion.y = (dest.y - source.y) * trace.fraction;
        motion.z = v25 * trace.fraction;
        rvParticle::CalcImpactPoint(this, &endPos, &trace.endpos, &motion, &TraceModel->bounds, &trace.c.normal);
      }
      v13 = rvRandom::irand(0, st->mParticleTemplate.mNumImpactEffects - 1);
      v14 = game->__vftable;
      random = v13;
      v15 = idVec3::ToMat3(&trace.c.normal, &result);
      v14->PlayEffect(
        game,
        p_mParticleTemplate->mImpactEffects[random],
        &endPos,
        v15,
        0,
        &vec3_origin,
        0,
        EC_IGNORE,
        &vec4_one);
    }
    if ( st->mParticleTemplate.mBounce != 0.0 )
      rvParticle::Bounce(this, effect, p_mParticleTemplate, trace.endpos, trace.c.normal, time);
    return ((unsigned int)p_mParticleTemplate->mFlags >> 10) & 1;
  }
  else
  {
LABEL_18:
    LOBYTE(v16) = 0;
  }
  return v16;
}
