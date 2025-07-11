
// FUNC: public: virtual int __thiscall idRenderEntityLocal::GetIndex(void)
int __thiscall idRenderEntityLocal::GetIndex(idRenderEntityLocal *this)
{
  return this->index;
}

// FUNC: public: virtual int __thiscall idRenderLightLocal::GetIndex(void)
int __thiscall idRenderLightLocal::GetIndex(idRenderLightLocal *this)
{
  return this->index;
}

// FUNC: public: virtual __thiscall rvRenderEffectLocal::~rvRenderEffectLocal(void)
void __thiscall rvRenderEffectLocal::~rvRenderEffectLocal(rvRenderEffectLocal *this)
{
  idRenderModel *dynamicModel; // ecx

  this->__vftable = (rvRenderEffectLocal_vtbl *)&rvRenderEffectLocal::`vftable';
  dynamicModel = this->dynamicModel;
  if ( dynamicModel )
    ((void (__thiscall *)(idRenderModel *, int))dynamicModel->~idRenderModel)(dynamicModel, 1);
  this->__vftable = (rvRenderEffectLocal_vtbl *)&rvRenderEffect::`vftable';
}

// FUNC: public: virtual int __thiscall rvRenderEffectLocal::GetIndex(void)
int __thiscall rvRenderEffectLocal::GetIndex(rvRenderEffectLocal *this)
{
  return this->index;
}

// FUNC: public: __thiscall idRenderEntityLocal::idRenderEntityLocal(void)
void __thiscall idRenderEntityLocal::idRenderEntityLocal(idRenderEntityLocal *this)
{
  this->__vftable = (idRenderEntityLocal_vtbl *)&idRenderEntityLocal::`vftable';
  memset(&this->parms, 0, sizeof(this->parms));
  memset(this->modelMatrix, 0, sizeof(this->modelMatrix));
  this->world = 0;
  this->index = 0;
  this->lastModifiedFrameNum = 0;
  this->writeToDemo = 0;
  this->archived = 0;
  this->dynamicModel = 0;
  this->dynamicModelFrameCount = 0;
  this->cachedDynamicModel = 0;
  this->dynamicCollisionModel = 0;
  this->cachedDynamicCollisionModel = 0;
  this->referenceBounds = bounds_zero;
  this->viewCount = 0;
  this->viewEntity = 0;
  this->visibleCount = 0;
  this->decals = 0;
  this->overlay = 0;
  this->entityRefs = 0;
  this->firstInteraction = 0;
  this->lastInteraction = 0;
}

// FUNC: public: __thiscall idRenderLightLocal::idRenderLightLocal(void)
void __thiscall idRenderLightLocal::idRenderLightLocal(idRenderLightLocal *this)
{
  this->__vftable = (idRenderLightLocal_vtbl *)&idRenderLightLocal::`vftable';
  memset(&this->parms, 0, sizeof(this->parms));
  this->parms.detailLevel = 10.0;
  memset(this->modelMatrix, 0, sizeof(this->modelMatrix));
  memset(this->shadowFrustums, 0, sizeof(this->shadowFrustums));
  memset(this->lightProject, 0, sizeof(this->lightProject));
  memset(this->frustum, 0, sizeof(this->frustum));
  this->frustumWindings[0] = 0;
  this->frustumWindings[1] = 0;
  this->frustumWindings[2] = 0;
  this->frustumWindings[3] = 0;
  this->frustumWindings[4] = 0;
  this->frustumWindings[5] = 0;
  this->lightHasMoved = 0;
  this->world = 0;
  this->index = 0;
  this->areaNum = 0;
  this->lastModifiedFrameNum = 0;
  this->writeToDemo = 0;
  this->archived = 0;
  this->lightShader = 0;
  this->falloffImage = 0;
  this->globalLightOrigin = vec3_origin;
  this->frustumTris = 0;
  this->numShadowFrustums = 0;
  this->viewCount = 0;
  this->viewLight = 0;
  this->references = 0;
  this->foggedPortals = 0;
  this->firstInteraction = 0;
  this->lastInteraction = 0;
  this->numPortalsCrossed = 0;
}

// FUNC: public: __thiscall rvRenderEffectLocal::rvRenderEffectLocal(void)
void __thiscall rvRenderEffectLocal::rvRenderEffectLocal(rvRenderEffectLocal *this)
{
  this->__vftable = (rvRenderEffectLocal_vtbl *)&rvRenderEffectLocal::`vftable';
  memset(&this->parms, 0, sizeof(this->parms));
  memset(this->modelMatrix, 0, sizeof(this->modelMatrix));
  this->model = (rvRenderModelBSE *)renderModelManager->FindModel(renderModelManager, "bse.bse");
  this->effect = 0;
  this->world = 0;
  this->lastModifiedFrameNum = 0;
  this->writeToDemo = 0;
  this->archived = 0;
  this->dynamicModel = 0;
  this->dynamicModelFrameCount = 0;
  this->viewCount = 0;
  this->viewEffect = 0;
  this->visibleCount = 0;
  this->effectRefs = 0;
  this->index = -1;
}
