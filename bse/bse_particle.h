
// FUNC: public: __thiscall rvParticleTemplate::~rvParticleTemplate(void)
void __thiscall rvParticleTemplate::~rvParticleTemplate(rvParticleTemplate *this)
{
  idStr::FreeData(&this->mTrailMaterialName);
  idStr::FreeData(&this->mTrailTypeName);
  idStr::FreeData(&this->mEntityDefName);
  idStr::FreeData(&this->mModelName);
  idStr::FreeData(&this->mMaterialName);
}

// FUNC: public: __thiscall rvParticleTemplate::rvParticleTemplate(void)
void __thiscall rvParticleTemplate::rvParticleTemplate(rvParticleTemplate *this)
{
  char *baseBuffer; // ecx

  this->mMaterialName.alloced = 20;
  this->mMaterialName.len = 0;
  baseBuffer = this->mMaterialName.baseBuffer;
  this->mMaterialName.data = baseBuffer;
  *baseBuffer = 0;
  this->mModelName.len = 0;
  this->mModelName.alloced = 20;
  this->mModelName.data = this->mModelName.baseBuffer;
  this->mModelName.baseBuffer[0] = 0;
  this->mEntityDefName.len = 0;
  this->mEntityDefName.alloced = 20;
  this->mEntityDefName.data = this->mEntityDefName.baseBuffer;
  this->mEntityDefName.baseBuffer[0] = 0;
  this->mTrailTypeName.len = 0;
  this->mTrailTypeName.alloced = 20;
  this->mTrailTypeName.data = this->mTrailTypeName.baseBuffer;
  this->mTrailTypeName.baseBuffer[0] = 0;
  this->mTrailMaterialName.len = 0;
  this->mTrailMaterialName.alloced = 20;
  this->mTrailMaterialName.data = this->mTrailMaterialName.baseBuffer;
  this->mTrailMaterialName.baseBuffer[0] = 0;
}

// FUNC: public: int __thiscall rvParticleTemplate::GetMaxTrailCount(void)const
int __thiscall rvParticleTemplate::GetMaxTrailCount(rvParticleTemplate *this)
{
  return (int)ceil(this->mTrailCount.y) + 1;
}

// FUNC: public: void __thiscall rvParticle::ScaleAngle(float)
void __thiscall rvParticle::ScaleAngle(rvParticle *this, float constant)
{
  this->mAngleEnv.mStart.x = constant * this->mAngleEnv.mStart.x;
  this->mAngleEnv.mStart.y = constant * this->mAngleEnv.mStart.y;
  this->mAngleEnv.mStart.z = constant * this->mAngleEnv.mStart.z;
  this->mAngleEnv.mEnd.x = constant * this->mAngleEnv.mEnd.x;
  this->mAngleEnv.mEnd.y = constant * this->mAngleEnv.mEnd.y;
  this->mAngleEnv.mEnd.z = constant * this->mAngleEnv.mEnd.z;
}

// FUNC: public: void __thiscall rvParticle::AttenuateFade(float,class rvParticleParms &)
void __thiscall rvParticle::AttenuateFade(rvParticle *this, float atten, rvParticleParms *parms)
{
  int mFlags; // eax
  double v4; // st7

  mFlags = parms->mFlags;
  if ( (mFlags & 0x20) != 0 )
  {
    if ( (mFlags & 0x40) != 0 )
    {
      v4 = 1.0 - atten;
      this->mFadeEnv.mStart = v4 * this->mFadeEnv.mStart;
      this->mFadeEnv.mEnd = v4 * this->mFadeEnv.mEnd;
    }
    else
    {
      this->mFadeEnv.mStart = atten * this->mFadeEnv.mStart;
      this->mFadeEnv.mEnd = atten * this->mFadeEnv.mEnd;
    }
  }
}

// FUNC: public: virtual int __thiscall rvParticle::Update(float)
int __thiscall rvParticle::Update(rvParticle *this, float time)
{
  return 1;
}

// FUNC: public: virtual bool __thiscall rvParticle::Render(class rvBSE const *,class idMat3 const &,struct srfTriangles_s *,float,float)
bool __thiscall rvParticle::Render(
        rvParticle *this,
        const rvBSE *effect,
        const idMat3 *view,
        srfTriangles_s *tri,
        float time,
        float override)
{
  return 0;
}

// FUNC: public: virtual void __thiscall ROQCinematic::GetScreenRect(int &,int &,int &,int &)
void __thiscall ROQCinematic::GetScreenRect(ROQCinematic *this, int *left, int *right, int *bottom, int *top)
{
  ;
}

// FUNC: public: virtual __thiscall rvLightParticle::~rvLightParticle(void)
void __thiscall rvLightParticle::~rvLightParticle(rvLightParticle *this)
{
  this->__vftable = (rvLightParticle_vtbl *)&rvLightParticle::`vftable';
  rvLightParticle::Destroy(this);
  this->__vftable = (rvLightParticle_vtbl *)&rvParticle::`vftable';
}

// FUNC: public: virtual __thiscall rvLineParticle::~rvLineParticle(void)
void __thiscall rvLineParticle::~rvLineParticle(rvDebrisParticle *this)
{
  this->__vftable = (rvDebrisParticle_vtbl *)&rvParticle::`vftable';
}

// FUNC: public: virtual void __thiscall rvSpriteParticle::EvaluateSize(float,float *)
void __thiscall rvSpriteParticle::EvaluateSize(rvSpriteParticle *this, float time, float *dest)
{
  rvEnvParms2::Evaluate(&this->mSizeEnv, time, dest);
}

// FUNC: public: virtual void __thiscall rvSpriteParticle::EvaluateRotation(float,float *)
void __thiscall rvSpriteParticle::EvaluateRotation(rvSpriteParticle *this, float time, float *dest)
{
  rvEnvParms1::Evaluate(&this->mRotationEnv, time, dest);
}

// FUNC: public: virtual void __thiscall rvSpriteParticle::InitSizeEnv(class rvEnvParms &,float)
void __thiscall rvSpriteParticle::InitSizeEnv(rvSpriteParticle *this, rvEnvParms *env, float duration)
{
  rvEnvParms2::Init(&this->mSizeEnv, env, duration);
}

// FUNC: public: virtual void __thiscall rvSpriteParticle::InitRotationEnv(class rvEnvParms &,float)
void __thiscall rvSpriteParticle::InitRotationEnv(rvSpriteParticle *this, rvEnvParms *env, float duration)
{
  rvEnvParms1::Init(&this->mRotationEnv, env, duration);
}

// FUNC: public: virtual float * __thiscall rvSpriteParticle::GetInitRotation(void)
float *__thiscall rvSpriteParticle::GetInitRotation(rvSpriteParticle *this)
{
  return &this->mRotationEnv.mStart;
}

// FUNC: public: virtual float * __thiscall rvSpriteParticle::GetDestRotation(void)
float *__thiscall rvSpriteParticle::GetDestRotation(rvSpriteParticle *this)
{
  return &this->mRotationEnv.mEnd;
}

// FUNC: public: virtual void __thiscall rvSpriteParticle::ScaleRotation(float)
void __thiscall rvSpriteParticle::ScaleRotation(rvSpriteParticle *this, float constant)
{
  this->mRotationEnv.mStart = constant * this->mRotationEnv.mStart;
  this->mRotationEnv.mEnd = constant * this->mRotationEnv.mEnd;
}

// FUNC: public: virtual void __thiscall rvSpriteParticle::AttenuateSize(float,class rvParticleParms &)
void __thiscall rvSpriteParticle::AttenuateSize(rvSpriteParticle *this, float atten, rvParticleParms *parms)
{
  rvParticle::Attenuate(this, atten, parms, &this->mSizeEnv);
}

// FUNC: public: virtual float * __thiscall rvSpriteParticle::GetDestSize(void)
idVec2 *__thiscall rvSpriteParticle::GetDestSize(rvSpriteParticle *this)
{
  return &this->mSizeEnv.mEnd;
}

// FUNC: public: virtual void __thiscall rvLineParticle::EvaluateSize(float,float *)
void __thiscall rvLineParticle::EvaluateSize(rvLinkedParticle *this, float time, float *dest)
{
  rvEnvParms1::Evaluate(&this->mSizeEnv, time, dest);
}

// FUNC: public: virtual void __thiscall rvLinkedParticle::InitSizeEnv(class rvEnvParms &,float)
void __thiscall rvLinkedParticle::InitSizeEnv(rvLinkedParticle *this, rvEnvParms *env, float duration)
{
  rvEnvParms1::Init(&this->mSizeEnv, env, duration);
}

// FUNC: public: virtual void __thiscall rvLineParticle::InitLengthEnv(class rvEnvParms &,float)
void __thiscall rvLineParticle::InitLengthEnv(rvLineParticle *this, rvEnvParms *env, float duration)
{
  rvEnvParms3::Init(&this->mLengthEnv, env, duration);
}

// FUNC: public: virtual void __thiscall rvLineParticle::AttenuateLength(float,class rvParticleParms &)
void __thiscall rvLineParticle::AttenuateLength(rvLineParticle *this, float atten, rvParticleParms *parms)
{
  rvParticle::Attenuate(this, atten, parms, &this->mLengthEnv);
}

// FUNC: public: virtual void __thiscall rvLineParticle::EvaluateLength(float,class idVec3 &)
void __thiscall rvLineParticle::EvaluateLength(rvLineParticle *this, float time, idVec3 *dest)
{
  rvEnvParms3::Evaluate(&this->mLengthEnv, time, &dest->x);
}

// FUNC: public: virtual float * __thiscall rvLineParticle::GetInitLength(void)
idVec3 *__thiscall rvLineParticle::GetInitLength(rvLineParticle *this)
{
  return &this->mLengthEnv.mStart;
}

// FUNC: public: virtual float * __thiscall rvLineParticle::GetDestLength(void)
idVec3 *__thiscall rvLineParticle::GetDestLength(rvLineParticle *this)
{
  return &this->mLengthEnv.mEnd;
}

// FUNC: public: virtual void __thiscall rvLineParticle::TransformLength(class idVec3)
void __thiscall rvLineParticle::TransformLength(rvLineParticle *this, idVec3 normal)
{
  rvEnvParms3::Transform(&this->mLengthEnv, normal);
}

// FUNC: public: virtual void __thiscall rvLineParticle::ScaleLength(float)
void __thiscall rvLineParticle::ScaleLength(rvLineParticle *this, float constant)
{
  rvEnvParms3::Scale(&this->mLengthEnv, constant);
}

// FUNC: public: virtual void __thiscall rvLineParticle::RenderBurnTrail(class rvBSE *,class idMat3 const &,struct srfTriangles_s *,float)
// attributes: thunk
void __thiscall rvLineParticle::RenderBurnTrail(
        rvLineParticle *this,
        rvBSE *effect,
        const idMat3 *view,
        srfTriangles_s *tri,
        float time)
{
  rvParticle::DoRenderBurnTrail(this, effect, view, tri, time);
}

// FUNC: public: virtual void __thiscall rvOrientedParticle::EvaluateRotation(float,float *)
void __thiscall rvOrientedParticle::EvaluateRotation(rvOrientedParticle *this, float time, float *dest)
{
  rvEnvParms3::Evaluate(&this->mRotationEnv, time, dest);
}

// FUNC: public: virtual void __thiscall rvOrientedParticle::InitRotationEnv(class rvEnvParms &,float)
void __thiscall rvOrientedParticle::InitRotationEnv(rvOrientedParticle *this, rvEnvParms *env, float duration)
{
  rvEnvParms3::Init(&this->mRotationEnv, env, duration);
}

// FUNC: public: virtual void __thiscall rvOrientedParticle::HandleOrientation(class rvAngles &)
void __thiscall rvOrientedParticle::HandleOrientation(rvOrientedParticle *this, rvAngles *angles)
{
  rvEnvParms3::Rotate(&this->mRotationEnv, angles);
}

// FUNC: public: virtual float * __thiscall rvOrientedParticle::GetInitRotation(void)
idVec3 *__thiscall rvOrientedParticle::GetInitRotation(rvOrientedParticle *this)
{
  return &this->mRotationEnv.mStart;
}

// FUNC: public: virtual float * __thiscall rvOrientedParticle::GetDestRotation(void)
idVec3 *__thiscall rvOrientedParticle::GetDestRotation(rvOrientedParticle *this)
{
  return &this->mRotationEnv.mEnd;
}

// FUNC: public: virtual void __thiscall rvOrientedParticle::ScaleRotation(float)
void __thiscall rvOrientedParticle::ScaleRotation(rvOrientedParticle *this, float constant)
{
  this->mRotationEnv.mStart.x = constant * this->mRotationEnv.mStart.x;
  this->mRotationEnv.mStart.y = constant * this->mRotationEnv.mStart.y;
  this->mRotationEnv.mStart.z = constant * this->mRotationEnv.mStart.z;
  this->mRotationEnv.mEnd.x = constant * this->mRotationEnv.mEnd.x;
  this->mRotationEnv.mEnd.y = constant * this->mRotationEnv.mEnd.y;
  this->mRotationEnv.mEnd.z = constant * this->mRotationEnv.mEnd.z;
}

// FUNC: public: virtual void __thiscall rvModelParticle::EvaluateRotation(float,float *)
void __thiscall rvModelParticle::EvaluateRotation(rvModelParticle *this, float time, float *dest)
{
  rvEnvParms3::Evaluate(&this->mRotationEnv, time, dest);
}

// FUNC: public: virtual void __thiscall rvModelParticle::InitRotationEnv(class rvEnvParms &,float)
void __thiscall rvModelParticle::InitRotationEnv(rvModelParticle *this, rvEnvParms *env, float duration)
{
  rvEnvParms3::Init(&this->mRotationEnv, env, duration);
}

// FUNC: public: virtual void __thiscall rvModelParticle::SetModel(char const *)
void __thiscall rvModelParticle::SetModel(rvModelParticle *this, const char *model)
{
  this->mModel = renderModelManager->FindModel(renderModelManager, model);
}

// FUNC: public: virtual void __thiscall rvLightParticle::AttenuateSize(float,class rvParticleParms &)
void __thiscall rvLightParticle::AttenuateSize(rvModelParticle *this, float atten, rvParticleParms *parms)
{
  rvParticle::Attenuate(this, atten, parms, &this->mSizeEnv);
}

// FUNC: public: virtual float * __thiscall rvModelParticle::GetInitRotation(void)
idVec3 *__thiscall rvModelParticle::GetInitRotation(rvModelParticle *this)
{
  return &this->mRotationEnv.mStart;
}

// FUNC: public: virtual float * __thiscall rvModelParticle::GetDestRotation(void)
idVec3 *__thiscall rvModelParticle::GetDestRotation(rvModelParticle *this)
{
  return &this->mRotationEnv.mEnd;
}

// FUNC: public: virtual float * __thiscall rvLineParticle::GetInitSize(void)
float *__thiscall rvLineParticle::GetInitSize(rvLinkedParticle *this)
{
  return &this->mSizeEnv.mStart;
}

// FUNC: public: virtual float * __thiscall rvLineParticle::GetDestSize(void)
float *__thiscall rvLineParticle::GetDestSize(rvLinkedParticle *this)
{
  return &this->mSizeEnv.mEnd;
}

// FUNC: public: virtual void __thiscall rvLightParticle::EvaluateLength(float,class idVec3 &)
void __thiscall rvLightParticle::EvaluateLength(idFile_ASCII *this, const char *detail, const char *classname)
{
  ;
}

// FUNC: public: virtual void __thiscall rvLinkedParticle::AttenuateSize(float,class rvParticleParms &)
void __thiscall rvLinkedParticle::AttenuateSize(rvLinkedParticle *this, float atten, rvParticleParms *parms)
{
  rvParticle::Attenuate(this, atten, parms, &this->mSizeEnv);
}

// FUNC: public: virtual void __thiscall rvLinkedParticle::GetSpawnInfo(class idVec4 &,class idVec3 &,class idVec3 &)
void __thiscall rvLinkedParticle::GetSpawnInfo(idRenderModel *this, int iX, int iY, float fAmount)
{
  ;
}

// FUNC: public: virtual void __thiscall rvModelParticle::EvaluateSize(float,float *)
void __thiscall rvModelParticle::EvaluateSize(rvDebrisParticle *this, float time, float *dest)
{
  rvEnvParms3::Evaluate(&this->mRotationEnv, time, dest);
}

// FUNC: public: virtual void __thiscall rvDebrisParticle::InitRotationEnv(class rvEnvParms &,float)
void __thiscall rvDebrisParticle::InitRotationEnv(rvDebrisParticle *this, rvEnvParms *env, float duration)
{
  rvEnvParms3::Init(&this->mRotationEnv, env, duration);
}

// FUNC: public: virtual float * __thiscall rvModelParticle::GetInitSize(void)
idVec3 *__thiscall rvModelParticle::GetInitSize(rvDebrisParticle *this)
{
  return &this->mRotationEnv.mStart;
}

// FUNC: public: virtual float * __thiscall rvDebrisParticle::GetDestRotation(void)
idVec3 *__thiscall rvDebrisParticle::GetDestRotation(rvDebrisParticle *this)
{
  return &this->mRotationEnv.mEnd;
}

// FUNC: public: virtual void __thiscall rvDebrisParticle::ScaleRotation(float)
void __thiscall rvDebrisParticle::ScaleRotation(rvDebrisParticle *this, float constant)
{
  this->mRotationEnv.mStart.x = constant * this->mRotationEnv.mStart.x;
  this->mRotationEnv.mStart.y = constant * this->mRotationEnv.mStart.y;
  this->mRotationEnv.mStart.z = constant * this->mRotationEnv.mStart.z;
  this->mRotationEnv.mEnd.x = constant * this->mRotationEnv.mEnd.x;
  this->mRotationEnv.mEnd.y = constant * this->mRotationEnv.mEnd.y;
  this->mRotationEnv.mEnd.z = constant * this->mRotationEnv.mEnd.z;
}

// FUNC: public: __thiscall rvLightParticle::rvLightParticle(void)
void __thiscall rvLightParticle::rvLightParticle(rvLightParticle *this)
{
  this->__vftable = (rvLightParticle_vtbl *)&rvLightParticle::`vftable';
  this->mLightDefHandle = -1;
}
