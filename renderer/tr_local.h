
// FUNC: public: virtual __thiscall rvRenderEffect::~rvRenderEffect(void)
void __thiscall rvRenderEffect::~rvRenderEffect(rvRenderEffect *this)
{
  this->__vftable = (rvRenderEffect_vtbl *)&rvRenderEffect::`vftable';
}

// FUNC: public: virtual struct renderLight_s * __thiscall idRenderLightLocal::GetParms(void)
renderLight_s *__thiscall idRenderLightLocal::GetParms(idRenderLightLocal *this)
{
  return &this->parms;
}

// FUNC: public: virtual class idPlane * __thiscall idRenderLightLocal::GetFrustum(void)
idPlane *__thiscall idRenderLightLocal::GetFrustum(idRenderLightLocal *this)
{
  return this->frustum;
}

// FUNC: public: virtual class idVec3 __thiscall idRenderLightLocal::GetGlobalLightOrigin(void)const
idVec3 *__thiscall idRenderLightLocal::GetGlobalLightOrigin(idRenderLightLocal *this, idVec3 *result)
{
  idVec3 *v2; // eax

  v2 = result;
  *result = this->globalLightOrigin;
  return v2;
}

// FUNC: public: virtual class idMaterial const * __thiscall idRenderLightLocal::GetLightShader(void)const
const idMaterial *__thiscall idRenderLightLocal::GetLightShader(idRenderLightLocal *this)
{
  return this->lightShader;
}

// FUNC: public: virtual struct srfTriangles_s * __thiscall idRenderLightLocal::GetFrustumTris(void)
srfTriangles_s *__thiscall idRenderLightLocal::GetFrustumTris(idRenderLightLocal *this)
{
  return this->frustumTris;
}
