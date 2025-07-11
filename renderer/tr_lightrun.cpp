
// FUNC: void __cdecl R_FreeLightDefFrustum(class idRenderLightLocal *)
void __cdecl R_FreeLightDefFrustum(idRenderLightLocal *ldef)
{
  idWinding **frustumWindings; // esi
  int v2; // edi

  if ( ldef->frustumTris )
  {
    R_FreeStaticTriSurf(ldef->frustumTris);
    ldef->frustumTris = 0;
  }
  frustumWindings = ldef->frustumWindings;
  v2 = 6;
  do
  {
    if ( *frustumWindings )
    {
      ((void (__thiscall *)(idWinding *, int))(*frustumWindings)->~idWinding)(*frustumWindings, 1);
      *frustumWindings = 0;
    }
    ++frustumWindings;
    --v2;
  }
  while ( v2 );
}

// FUNC: void __cdecl R_ClearEntityDefDynamicModel(class idRenderEntityLocal *)
void __cdecl R_ClearEntityDefDynamicModel(idRenderEntityLocal *def)
{
  idInteraction *i; // esi

  for ( i = def->firstInteraction; i; i = i->entityNext )
  {
    if ( !i->numSurfaces )
      break;
    idInteraction::FreeSurfaces(i);
  }
  if ( def->dynamicModel )
    def->dynamicModel = 0;
  if ( def->dynamicCollisionModel )
    def->dynamicCollisionModel = 0;
}

// FUNC: void __cdecl R_FreeEntityDefDecals(class idRenderEntityLocal *)
void __cdecl R_FreeEntityDefDecals(idRenderEntityLocal *def)
{
  idRenderModelDecal *nextDecal; // edi

  if ( def->decals )
  {
    do
    {
      nextDecal = def->decals->nextDecal;
      idRenderModelDecal::Free(def->decals);
      def->decals = nextDecal;
    }
    while ( nextDecal );
  }
}

// FUNC: void __cdecl R_FreeEntityDefFadedDecals(class idRenderEntityLocal *,int)
void __cdecl R_FreeEntityDefFadedDecals(idRenderEntityLocal *def, int time)
{
  def->decals = idRenderModelDecal::RemoveFadedDecals(def->decals, time);
}

// FUNC: void __cdecl R_FreeEntityDefOverlay(class idRenderEntityLocal *)
void __cdecl R_FreeEntityDefOverlay(idRenderEntityLocal *def)
{
  if ( def->overlay )
  {
    idRenderModelOverlay::Free(def->overlay);
    def->overlay = 0;
  }
}

// FUNC: void __cdecl R_ModulateLights_f(class idCmdArgs const &)
void __cdecl R_ModulateLights_f(const idCmdArgs *args)
{
  const idCmdArgs *v1; // eax
  int v2; // edi
  float *v3; // esi
  char **v4; // ebx
  int v5; // ebp
  const char *v6; // eax
  idRenderWorldLocal *primaryWorld; // edx
  int v8; // ecx
  int i; // esi
  float *v10; // eax
  float modulate[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( tr.primaryWorld )
  {
    v1 = args;
    if ( args->argc == 4 )
    {
      v2 = 1;
      v3 = modulate;
      v4 = &args->argv[1];
      v5 = 3;
      while ( 1 )
      {
        v6 = v2 < 0 || v2 >= v1->argc ? &entityFilter : *v4;
        *v3 = atof(v6);
        ++v2;
        ++v4;
        ++v3;
        if ( !--v5 )
          break;
        v1 = args;
      }
      primaryWorld = tr.primaryWorld;
      v8 = 0;
      for ( i = 0; v8 < primaryWorld->lightDefs.num; ++v8 )
      {
        v10 = (float *)primaryWorld->lightDefs.list[v8];
        if ( v10 )
        {
          ++i;
          v10[42] = modulate[0] * v10[42];
          v10[43] = modulate[1] * v10[43];
          v10[44] = modulate[2] * v10[44];
          primaryWorld = tr.primaryWorld;
        }
      }
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "modulated %i lights\n",
        i);
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "usage: modulateLights <redFloat> <greenFloat> <blueFloat>\n");
    }
  }
}

// FUNC: void __cdecl R_CreateEntityRefs(class idRenderEntityLocal *)
void __cdecl R_CreateEntityRefs(idRenderEntityLocal *def)
{
  renderEntity_s *p_parms; // edi
  double v2; // st7
  double v3; // st7
  double y; // st6
  double v5; // st6
  double z; // st5
  double v7; // st5
  double v8; // rt0
  double v9; // st6
  double v10; // st5
  double v11; // st4
  double v12; // st5
  double v13; // st7
  double v14; // st6
  double v15; // st5
  double v16; // st7
  float v17; // eax
  float v18; // eax
  float v19; // [esp+20h] [ebp-60h]
  float v20; // [esp+2Ch] [ebp-54h] BYREF
  float v21; // [esp+30h] [ebp-50h]
  float v22; // [esp+34h] [ebp-4Ch]
  idBox box; // [esp+44h] [ebp-3Ch] BYREF

  p_parms = &def->parms;
  if ( !def->parms.hModel )
    p_parms->hModel = renderModelManager->DefaultModel(renderModelManager);
  if ( def->parms.callback )
    def->referenceBounds = def->parms.bounds;
  else
    def->referenceBounds = *(idBounds *)((int (__stdcall *)(float *, renderEntity_s *))p_parms->hModel->Bounds)(
                                          &v20,
                                          p_parms);
  if ( def->referenceBounds.b[0].x <= (double)def->referenceBounds.b[1].x )
  {
    if ( r_showUpdates.internalVar->integerValue )
    {
      v2 = def->referenceBounds.b[1].x - def->referenceBounds.b[0].x;
      if ( v2 > 1024.0 || def->referenceBounds.b[1].y - def->referenceBounds.b[0].y > 1024.0 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "big entityRef: %f,%f\n",
          v2,
          def->referenceBounds.b[1].y - def->referenceBounds.b[0].y);
    }
    ++tr.viewCount;
    v3 = def->referenceBounds.b[1].x + def->referenceBounds.b[0].x;
    y = def->referenceBounds.b[1].y;
    box.axis.mat[0].x = def->parms.axis.mat[0].x;
    v5 = y + def->referenceBounds.b[0].y;
    z = def->referenceBounds.b[1].z;
    box.axis.mat[1].x = def->parms.axis.mat[1].x;
    v7 = z + def->referenceBounds.b[0].z;
    box.axis.mat[2].x = def->parms.axis.mat[2].x;
    v22 = v7;
    v8 = v5;
    v19 = v3 * 0.5;
    v9 = v22 * 0.5;
    v10 = def->referenceBounds.b[1].x - v19;
    v11 = def->referenceBounds.b[1].y - v8 * 0.5;
    v22 = def->referenceBounds.b[1].z - v9;
    box.extents.z = v22;
    box.extents.x = v10;
    box.axis.mat[0].y = def->parms.axis.mat[0].y;
    box.extents.y = v11;
    box.axis.mat[1].y = def->parms.axis.mat[1].y;
    v12 = v9 * def->parms.axis.mat[2].x;
    box.axis.mat[2].y = def->parms.axis.mat[2].y;
    v20 = v12 + v8 * 0.5 * def->parms.axis.mat[1].x + v19 * def->parms.axis.mat[0].x;
    v21 = v9 * def->parms.axis.mat[2].y + v8 * 0.5 * def->parms.axis.mat[1].y + v19 * def->parms.axis.mat[0].y;
    v13 = v9 * def->parms.axis.mat[2].z + v8 * 0.5 * def->parms.axis.mat[1].z + v19 * def->parms.axis.mat[0].z;
    v14 = v20 + def->parms.origin.x;
    v15 = v13;
    v16 = v21 + def->parms.origin.y;
    v22 = v15 + def->parms.origin.z;
    box.center.z = v22;
    v17 = def->parms.axis.mat[0].z;
    box.center.x = v14;
    box.axis.mat[0].z = v17;
    v18 = def->parms.axis.mat[1].z;
    box.center.y = v16;
    box.axis.mat[1].z = v18;
    box.axis.mat[2].z = def->parms.axis.mat[2].z;
    idRenderWorldLocal::PushPolytopeIntoTree(def->world, def, 0, 0, &box, 0, 0);
  }
}

// FUNC: void __cdecl R_SetLightProject(class idPlane * const,class idVec3,class idVec3,class idVec3,class idVec3,class idVec3,class idVec3)
void __cdecl R_SetLightProject(
        idPlane *lightProject,
        idVec3 origin,
        idVec3 target,
        idVec3 rightVector,
        idVec3 upVector,
        idVec3 start,
        idVec3 stop)
{
  long double v7; // st7
  long double v8; // st6
  long double v9; // st7
  long double v10; // st6
  double v11; // st7
  double v12; // st6
  double v13; // st6
  double v15; // st5
  double v16; // st6
  double v17; // st7
  double v18; // st6
  double v19; // st7
  double v20; // st6
  double v21; // st5
  double v22; // st4
  double v23; // st7
  double v24; // st7
  double v25; // st6
  float rLen; // [esp+0h] [ebp-3Ch]
  idVec3 right; // [esp+4h] [ebp-38h]
  idVec3 up; // [esp+10h] [ebp-2Ch]
  float up_4; // [esp+14h] [ebp-28h]
  float up_4a; // [esp+14h] [ebp-28h]
  float up_8; // [esp+18h] [ebp-24h]
  float up_8a; // [esp+18h] [ebp-24h]
  float v33; // [esp+1Ch] [ebp-20h]
  float v34; // [esp+1Ch] [ebp-20h]
  float normal_4; // [esp+24h] [ebp-18h]
  float normal_4a; // [esp+24h] [ebp-18h]
  float normal_8; // [esp+28h] [ebp-14h]
  float normal_8a; // [esp+28h] [ebp-14h]
  float v39; // [esp+2Ch] [ebp-10h]
  float v40; // [esp+30h] [ebp-Ch]
  float v41; // [esp+30h] [ebp-Ch]
  float v42; // [esp+34h] [ebp-8h]
  float v43; // [esp+34h] [ebp-8h]
  float lightProjecta; // [esp+40h] [ebp+4h]
  float lightProjectb; // [esp+40h] [ebp+4h]
  float dist; // [esp+5Ch] [ebp+20h]
  float distb; // [esp+5Ch] [ebp+20h]
  float distc; // [esp+5Ch] [ebp+20h]
  float dista; // [esp+5Ch] [ebp+20h]
  float v50; // [esp+64h] [ebp+28h]
  float uLen; // [esp+68h] [ebp+2Ch]
  float uLena; // [esp+68h] [ebp+2Ch]
  float v53; // [esp+6Ch] [ebp+30h]
  float v54; // [esp+70h] [ebp+34h]

  right = rightVector;
  v7 = rightVector.z * rightVector.z + rightVector.y * rightVector.y + rightVector.x * rightVector.x;
  if ( v7 == 0.0 )
  {
    rLen = 0.0;
  }
  else
  {
    v8 = 1.0 / sqrt(v7);
    right.x = rightVector.x * v8;
    right.y = rightVector.y * v8;
    right.z = rightVector.z * v8;
    rLen = v8 * v7;
  }
  up = upVector;
  v9 = upVector.z * upVector.z + upVector.y * upVector.y + upVector.x * upVector.x;
  if ( v9 == 0.0 )
  {
    uLen = 0.0;
  }
  else
  {
    v10 = 1.0 / sqrt(v9);
    up.x = upVector.x * v10;
    up.y = upVector.y * v10;
    up.z = upVector.z * v10;
    uLen = v10 * v9;
  }
  v11 = up.y * right.z - up.z * right.y;
  v39 = v11;
  v40 = up.z * right.x - right.z * up.x;
  normal_4 = v40;
  v42 = right.y * up.x - up.y * right.x;
  normal_8 = v42;
  dist = v42 * v42 + v40 * v40 + v39 * v39;
  if ( dist != 0.0 )
  {
    distb = 1.0 / sqrt(dist);
    v11 = v39 * distb;
    normal_4 = v40 * distb;
    normal_8 = v42 * distb;
  }
  v12 = target.y * normal_4 + target.x * v11 + target.z * normal_8;
  if ( v12 < 0.0 )
  {
    distc = -v12;
    v11 = -v11;
    v41 = -normal_4;
    normal_4 = v41;
    v43 = -normal_8;
    v12 = distc;
    normal_8 = v43;
  }
  v13 = v12 * 0.5;
  lightProject[2].b = normal_4;
  v15 = v13 / rLen;
  lightProject[2].c = normal_8;
  lightProject[2].d = 0.0;
  right.x = right.x * v15;
  right.y = right.y * v15;
  right.z = right.z * v15;
  v16 = -(v13 / uLen);
  up.x = up.x * v16;
  up.y = up.y * v16;
  up.z = up.z * v16;
  lightProject[2].a = v11;
  v17 = origin.y * lightProject[2].b + origin.z * lightProject[2].c;
  v18 = origin.x * lightProject[2].a;
  lightProject->a = right.x;
  lightProject->b = right.y;
  lightProject->c = right.z;
  lightProject[2].d = -(v17 + v18);
  lightProject->d = 0.0;
  lightProject->d = -(origin.z * right.z + origin.y * right.y + origin.x * right.x);
  lightProject[1].a = up.x;
  lightProject[1].b = up.y;
  lightProject[1].c = up.z;
  lightProject[1].d = 0.0;
  lightProject[1].d = -(origin.y * lightProject[1].b + origin.z * lightProject[1].c + origin.x * lightProject[1].a);
  v19 = origin.x + target.x;
  v20 = origin.y + target.y;
  v21 = origin.z + target.z;
  v22 = 0.5
      - (v20 * lightProject->b + v21 * lightProject->c + v19 * lightProject->a + lightProject->d)
      / (v21 * lightProject[2].c + v20 * lightProject[2].b + v19 * lightProject[2].a + lightProject[2].d);
  up_4 = lightProject[2].b * v22;
  up_8 = lightProject[2].c * v22;
  v33 = lightProject[2].d * v22;
  lightProject->a = lightProject[2].a * v22 + lightProject->a;
  lightProject->b = up_4 + lightProject->b;
  lightProject->c = up_8 + lightProject->c;
  lightProject->d = v33 + lightProject->d;
  v23 = 0.5
      - (v21 * lightProject[1].c + v20 * lightProject[1].b + v19 * lightProject[1].a + lightProject[1].d)
      / (v21 * lightProject[2].c + v20 * lightProject[2].b + v19 * lightProject[2].a + lightProject[2].d);
  up_4a = lightProject[2].b * v23;
  up_8a = lightProject[2].c * v23;
  v34 = lightProject[2].d * v23;
  lightProject[1].a = lightProject[2].a * v23 + lightProject[1].a;
  lightProject[1].b = up_4a + lightProject[1].b;
  lightProject[1].c = up_8a + lightProject[1].c;
  lightProject[1].d = v34 + lightProject[1].d;
  v24 = stop.x - start.x;
  uLena = v24;
  v53 = stop.y - start.y;
  normal_4a = v53;
  v54 = stop.z - start.z;
  normal_8a = v54;
  dista = uLena * uLena + v54 * v54 + v53 * v53;
  if ( dista == 0.0
    || (lightProjecta = 1.0 / sqrt(dista),
        v24 = uLena * lightProjecta,
        normal_4a = v53 * lightProjecta,
        normal_8a = v54 * lightProjecta,
        v25 = dista * lightProjecta,
        v25 <= 0.0) )
  {
    v25 = 1.0;
  }
  lightProject[3].d = 0.0;
  lightProjectb = 1.0 / v25;
  v50 = normal_8a * lightProjectb;
  lightProject[3].c = v50;
  lightProject[3].a = v24 * lightProjectb;
  lightProject[3].b = normal_4a * lightProjectb;
  lightProject[3].d = -((start.z + origin.z) * lightProject[3].c
                      + (start.y + origin.y) * lightProject[3].b
                      + (start.x + origin.x) * lightProject[3].a);
}

// FUNC: bool __cdecl WindingCompletelyInsideLight(class idWinding const *,class idRenderLightLocal const *)
char __cdecl WindingCompletelyInsideLight(const idWinding *w, const idRenderLightLocal *ldef)
{
  int numPoints; // ebp
  int v3; // ebx
  idVec5 *p; // edi
  float *p_y; // esi
  float *p_b; // ecx
  int i; // edx

  numPoints = w->numPoints;
  v3 = 0;
  if ( numPoints > 0 )
  {
    p = w->p;
    p_y = &p->y;
    while ( 2 )
    {
      p_b = &ldef->frustum[0].b;
      for ( i = 0; i < 6; ++i )
      {
        if ( *(p_b - 1) * p->x + p_b[1] * p_y[1] + *p_b * *p_y + p_b[2] > 0.0 )
          return 0;
        p_b += 4;
      }
      ++v3;
      ++p;
      p_y += 5;
      if ( v3 < numPoints )
        continue;
      break;
    }
  }
  return 1;
}

// FUNC: void __cdecl R_CreateLightDefFogPortals(class idRenderLightLocal *)
void __cdecl R_CreateLightDefFogPortals(idRenderLightLocal *ldef)
{
  const idMaterial *lightShader; // eax
  areaReference_s *i; // ebp
  portal_s *j; // esi
  doublePortal_s *doublePortal; // edi

  lightShader = ldef->lightShader;
  ldef->foggedPortals = 0;
  if ( lightShader->fogLight && (lightShader->materialFlags & 0x20) == 0 )
  {
    for ( i = ldef->references; i; i = i->ownerNext )
    {
      for ( j = i->area->portals; j; j = j->next )
      {
        doublePortal = j->doublePortal;
        if ( !doublePortal->fogLight )
        {
          if ( WindingCompletelyInsideLight(j->w, ldef) )
          {
            doublePortal->fogLight = ldef;
            doublePortal->nextFoggedPortal = ldef->foggedPortals;
            ldef->foggedPortals = doublePortal;
          }
        }
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderLightLocal::FreeLightDefDerivedData(bool)
void __thiscall idRenderLightLocal::FreeLightDefDerivedData(idRenderLightLocal *this, bool unstream)
{
  doublePortal_s *i; // eax
  areaReference_s *references; // eax
  areaReference_s *ownerNext; // edx
  idRenderWorldLocal *world; // ecx
  idBlockAlloc<areaReference_s,1024,16>::element_s *free; // ebp
  portalArea_s **p_area; // eax

  for ( i = this->foggedPortals; i; i = i->nextFoggedPortal )
    i->fogLight = 0;
  while ( this->firstInteraction )
    idInteraction::UnlinkAndFree(this->firstInteraction);
  if ( !unstream )
  {
    references = this->references;
    if ( references )
    {
      do
      {
        ownerNext = references->ownerNext;
        references->areaNext->areaPrev = references->areaPrev;
        references->areaPrev->areaNext = references->areaNext;
        world = this->world;
        free = world->areaReferenceAllocator.free;
        world = (idRenderWorldLocal *)((char *)world + 184);
        p_area = &references[-1].area;
        *p_area = (portalArea_s *)free;
        --world->mapName.alloced;
        world->mapName.len = (int)p_area;
        references = ownerNext;
      }
      while ( ownerNext );
    }
    this->references = 0;
    R_FreeLightDefFrustum(this);
  }
}

// FUNC: void __cdecl R_FreeEntityDefDerivedData(class idRenderEntityLocal *,bool,bool,bool)
void __cdecl R_FreeEntityDefDerivedData(
        idRenderEntityLocal *def,
        bool keepDecals,
        bool keepCachedDynamicModel,
        bool unstream)
{
  idUserInterface **gui; // edi
  int v5; // ebp
  idRenderModelDecal *nextDecal; // edi
  idRenderModel *cachedDynamicModel; // ecx
  idRenderModel *cachedDynamicCollisionModel; // ecx
  areaReference_s *entityRefs; // eax
  areaReference_s *ownerNext; // edx
  idRenderWorldLocal *world; // ecx
  idBlockAlloc<areaReference_s,1024,16>::element_s *free; // ebp
  portalArea_s **p_area; // eax

  if ( session->readDemo )
  {
    if ( def->parms.joints )
    {
      Mem_Free16(def->parms.joints);
      def->parms.joints = 0;
    }
    if ( def->parms.callbackData )
    {
      Mem_Free(def->parms.callbackData);
      def->parms.callbackData = 0;
    }
    gui = def->parms.gui;
    v5 = 3;
    do
    {
      if ( *gui )
      {
        ((void (__thiscall *)(idUserInterface *, int))(*gui)->~idUserInterface)(*gui, 1);
        *gui = 0;
      }
      ++gui;
      --v5;
    }
    while ( v5 );
  }
  while ( def->firstInteraction )
    idInteraction::UnlinkAndFree(def->firstInteraction);
  if ( def->dynamicModel )
    def->dynamicModel = 0;
  if ( def->dynamicCollisionModel )
    def->dynamicCollisionModel = 0;
  if ( !keepDecals )
  {
    if ( def->decals )
    {
      do
      {
        nextDecal = def->decals->nextDecal;
        idRenderModelDecal::Free(def->decals);
        def->decals = nextDecal;
      }
      while ( nextDecal );
    }
    if ( def->overlay )
    {
      idRenderModelOverlay::Free(def->overlay);
      def->overlay = 0;
    }
  }
  if ( !keepCachedDynamicModel )
  {
    cachedDynamicModel = def->cachedDynamicModel;
    if ( cachedDynamicModel )
    {
      ((void (__thiscall *)(idRenderModel *, int))cachedDynamicModel->~idRenderModel)(cachedDynamicModel, 1);
      def->cachedDynamicModel = 0;
    }
    cachedDynamicCollisionModel = def->cachedDynamicCollisionModel;
    if ( cachedDynamicCollisionModel )
    {
      ((void (__thiscall *)(idRenderModel *, int))cachedDynamicCollisionModel->~idRenderModel)(
        cachedDynamicCollisionModel,
        1);
      def->cachedDynamicCollisionModel = 0;
    }
  }
  if ( !unstream )
  {
    entityRefs = def->entityRefs;
    if ( entityRefs )
    {
      do
      {
        ownerNext = entityRefs->ownerNext;
        entityRefs->areaNext->areaPrev = entityRefs->areaPrev;
        entityRefs->areaPrev->areaNext = entityRefs->areaNext;
        world = def->world;
        free = world->areaReferenceAllocator.free;
        world = (idRenderWorldLocal *)((char *)world + 184);
        p_area = &entityRefs[-1].area;
        *p_area = (portalArea_s *)free;
        --world->mapName.alloced;
        world->mapName.len = (int)p_area;
        entityRefs = ownerNext;
      }
      while ( ownerNext );
    }
    def->entityRefs = 0;
  }
}

// FUNC: void __cdecl R_FreeEffectDefDerivedData(class rvRenderEffectLocal *)
void __cdecl R_FreeEffectDefDerivedData(rvRenderEffectLocal *def)
{
  areaReference_s *effectRefs; // eax
  areaReference_s *ownerNext; // edx
  idRenderWorldLocal *world; // ecx
  idBlockAlloc<areaReference_s,1024,16>::element_s *free; // ebp
  portalArea_s **p_area; // eax

  effectRefs = def->effectRefs;
  if ( effectRefs )
  {
    do
    {
      ownerNext = effectRefs->ownerNext;
      effectRefs->areaNext->areaPrev = effectRefs->areaPrev;
      effectRefs->areaPrev->areaNext = effectRefs->areaNext;
      world = def->world;
      free = world->areaReferenceAllocator.free;
      world = (idRenderWorldLocal *)((char *)world + 184);
      p_area = &effectRefs[-1].area;
      *p_area = (portalArea_s *)free;
      --world->mapName.alloced;
      world->mapName.len = (int)p_area;
      effectRefs = ownerNext;
    }
    while ( ownerNext );
  }
  def->effectRefs = 0;
}

// FUNC: void __cdecl R_FreeDerivedData(void)
void __cdecl R_FreeDerivedData()
{
  int i; // ebx
  idRenderWorldLocal *v1; // esi
  int j; // edi
  idRenderEntityLocal *v3; // eax
  int k; // edi
  idRenderLightLocal *v5; // ecx

  for ( i = 0; i < tr.worlds.num; ++i )
  {
    v1 = tr.worlds.list[i];
    for ( j = 0; j < v1->entityDefs.num; ++j )
    {
      v3 = v1->entityDefs.list[j];
      if ( v3 )
        R_FreeEntityDefDerivedData(v3, 0, 0, 0);
    }
    for ( k = 0; k < v1->lightDefs.num; ++k )
    {
      v5 = v1->lightDefs.list[k];
      if ( v5 )
        v5->FreeLightDefDerivedData(v5, 0);
    }
  }
}

// FUNC: void __cdecl R_CheckForEntityDefsUsingModel(class idRenderModel *)
void __cdecl R_CheckForEntityDefsUsingModel(idRenderModel *model)
{
  int i; // ebp
  idRenderWorldLocal *v2; // ebx
  int j; // edi
  idRenderEntityLocal *v4; // esi

  for ( i = 0; i < tr.worlds.num; ++i )
  {
    v2 = tr.worlds.list[i];
    for ( j = 0; j < v2->entityDefs.num; ++j )
    {
      v4 = v2->entityDefs.list[j];
      if ( v4 )
      {
        if ( v4->parms.hModel == model )
        {
          R_FreeEntityDefDerivedData(v4, 0, 0, 0);
          v4->parms.hModel = 0;
        }
      }
    }
  }
}

// FUNC: void __cdecl R_ReCreateWorldReferences(void)
void __cdecl R_ReCreateWorldReferences()
{
  int v0; // eax
  idRenderWorldLocal *v1; // ebx
  int v2; // esi
  int v3; // edi
  idRenderEntityLocal **list; // edx
  idRenderEntityLocal *v5; // eax
  int i; // ebp
  idRenderLightLocal *v7; // eax
  int j; // [esp+14h] [ebp-DCh]
  renderLight_s parms; // [esp+18h] [ebp-D8h] BYREF

  v0 = 0;
  tr.viewDef = 0;
  for ( j = 0; j < tr.worlds.num; ++j )
  {
    v1 = tr.worlds.list[v0];
    v2 = 0;
    if ( v1->entityDefs.num > 0 )
    {
      v3 = 0;
      do
      {
        list = v1->entityDefs.list;
        v5 = list[v2];
        if ( v5 )
        {
          if ( v2 >= v1->numPortalAreas )
            R_CreateEntityRefs(list[v2]);
          else
            idRenderWorldLocal::AddEntityRefToArea(v1, v5, &v1->portalAreas[v3]);
        }
        ++v2;
        ++v3;
      }
      while ( v2 < v1->entityDefs.num );
    }
    for ( i = 0; i < v1->lightDefs.num; ++i )
    {
      v7 = v1->lightDefs.list[i];
      if ( v7 )
      {
        qmemcpy(&parms, &v7->parms, sizeof(parms));
        v7->world->FreeLightDef(v7->world, i);
        v1->UpdateLightDef(v1, i, &parms);
      }
    }
    v0 = j + 1;
  }
}

// FUNC: void __cdecl R_RegenerateWorld_f(class idCmdArgs const &)
void __cdecl R_RegenerateWorld_f()
{
  R_FreeDerivedData();
  tr.staticAllocCount = 0;
  R_ReCreateWorldReferences();
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "Regenerated world, staticAllocCount = %i.\n",
    tr.staticAllocCount);
}

// FUNC: void __cdecl R_SetLightFrustum(class idPlane const * const,class idPlane * const)
void __cdecl R_SetLightFrustum(const idPlane *lightProject, idPlane *frustum)
{
  double v3; // st7
  double v4; // st7
  float *p_b; // ecx
  int v6; // esi
  float *v7; // edx
  double v8; // st7
  long double v9; // st4
  long double v10; // st7
  long double v11; // st6
  unsigned __int8 v13; // c2
  unsigned __int8 v14; // c3
  double v15; // st6
  idPlane v16; // [esp+10h] [ebp-10h]
  idPlane v17; // [esp+10h] [ebp-10h]
  float v18; // [esp+10h] [ebp-10h]
  float v19; // [esp+14h] [ebp-Ch]
  float v20; // [esp+18h] [ebp-8h]
  float v21; // [esp+1Ch] [ebp-4h]

  *frustum = *lightProject;
  frustum[1] = lightProject[1];
  v16.a = lightProject[2].a - lightProject->a;
  v16.b = lightProject[2].b - lightProject->b;
  v16.c = lightProject[2].c - lightProject->c;
  v3 = lightProject[2].d - lightProject->d;
  frustum[2] = v16;
  v17.d = v3;
  v17.a = lightProject[2].a - lightProject[1].a;
  v17.b = lightProject[2].b - lightProject[1].b;
  v17.c = lightProject[2].c - lightProject[1].c;
  v4 = lightProject[2].d - lightProject[1].d;
  frustum[3] = v17;
  v17.d = v4;
  frustum[4] = lightProject[3];
  frustum[5] = lightProject[3];
  p_b = &frustum->b;
  v6 = 6;
  frustum[5].d = frustum[5].d - 1.0;
  v17.a = -frustum[5].a;
  v17.b = -frustum[5].b;
  v17.c = -frustum[5].c;
  frustum[5] = v17;
  do
  {
    v7 = p_b - 1;
    v18 = -*(p_b - 1);
    v19 = -*p_b;
    v20 = -p_b[1];
    v8 = p_b[2];
    *(p_b - 1) = v18;
    v21 = -v8;
    *p_b = v19;
    p_b[1] = v20;
    p_b[2] = v21;
    v9 = *(p_b - 1) * *(p_b - 1) + p_b[1] * p_b[1] + *p_b * *p_b;
    if ( v9 == 0.0 )
    {
      v10 = 0.0;
    }
    else
    {
      v11 = 1.0 / sqrt(v9);
      *v7 = v11 * *v7;
      *p_b = v11 * *p_b;
      p_b[1] = v11 * p_b[1];
      v10 = v9 * v11;
    }
    if ( v14 | v13 )
    {
      if ( *p_b == 0.0 )
      {
        if ( p_b[1] <= 0.0 )
        {
          if ( *((_DWORD *)p_b + 1) != -1082130432 )
            p_b[1] = -1.0;
        }
        else if ( *((_DWORD *)p_b + 1) != 1065353216 )
        {
          p_b[1] = 1.0;
        }
        goto LABEL_38;
      }
      if ( p_b[1] == 0.0 )
      {
        if ( *p_b <= 0.0 )
        {
          if ( *(_DWORD *)p_b != -1082130432 )
            *p_b = -1.0;
        }
        else if ( *(_DWORD *)p_b != 1065353216 )
        {
          *p_b = 1.0;
        }
        goto LABEL_38;
      }
    }
    else if ( *p_b == 0.0 && p_b[1] == 0.0 )
    {
      if ( *v7 <= 0.0 )
      {
        if ( *(_DWORD *)v7 != -1082130432 )
          *v7 = -1.0;
      }
      else if ( *(_DWORD *)v7 != 1065353216 )
      {
        *v7 = 1.0;
      }
      goto LABEL_38;
    }
    if ( COERCE_FLOAT(*(_DWORD *)v7 & 0x7FFFFFFF) == 1.0 )
    {
      if ( *p_b != 0.0 || p_b[1] != 0.0 )
      {
        p_b[1] = 0.0;
LABEL_37:
        *p_b = 0.0;
      }
    }
    else if ( COERCE_FLOAT(*(_DWORD *)p_b & 0x7FFFFFFF) == 1.0 )
    {
      if ( *v7 != 0.0 || p_b[1] != 0.0 )
      {
        p_b[1] = 0.0;
        *v7 = 0.0;
      }
    }
    else if ( COERCE_FLOAT((_DWORD)p_b[1] & 0x7FFFFFFF) == 1.0 && (*v7 != 0.0 || *p_b != 0.0) )
    {
      *v7 = 0.0;
      goto LABEL_37;
    }
LABEL_38:
    v15 = p_b[2];
    p_b += 4;
    --v6;
    *(p_b - 2) = v15 / v10;
  }
  while ( v6 );
}

// FUNC: public: virtual void __thiscall idRenderLightLocal::DeriveLightData(void)
void __thiscall idRenderLightLocal::DeriveLightData(idRenderLightLocal *this)
{
  const idMaterial *shader; // eax
  const idMaterial *v3; // eax
  idImage *lightFalloffImage; // eax
  idDeclManager_vtbl *v5; // edx
  int v6; // eax
  idPlane *frustum; // edi
  float b; // ecx
  float c; // eax
  int d_low; // ecx
  idPlane *lightProject; // edi
  float v12; // edx
  float v13; // ecx
  int v14; // edx
  long double x; // st7
  long double y; // st6
  double z; // st5
  long double v18; // st4
  long double v19; // st2
  double v20; // st6
  double v21; // st7
  double v22; // st7
  double v23; // st6
  double v24; // rt2
  int v25; // [esp+10h] [ebp-20h]
  int v26; // [esp+10h] [ebp-20h]
  float v27; // [esp+14h] [ebp-1Ch]
  float v28; // [esp+18h] [ebp-18h]
  float v29; // [esp+18h] [ebp-18h]
  float v30; // [esp+1Ch] [ebp-14h]
  idVec3 dir; // [esp+20h] [ebp-10h] BYREF
  int v32; // [esp+2Ch] [ebp-4h]

  shader = this->parms.shader;
  if ( shader )
    this->lightShader = shader;
  if ( !this->lightShader )
  {
    if ( this->parms.pointLight )
      v3 = declManager->FindMaterial(declManager, "lights/defaultPointLight", 1);
    else
      v3 = declManager->FindMaterial(declManager, "lights/defaultProjectedLight", 1);
    this->lightShader = v3;
  }
  lightFalloffImage = this->lightShader->lightFalloffImage;
  this->falloffImage = lightFalloffImage;
  if ( !lightFalloffImage )
  {
    v5 = declManager->__vftable;
    if ( this->parms.pointLight )
      v6 = ((int (__stdcall *)(const char *, int))v5->FindMaterial)("lights/defaultPointLight", 1);
    else
      v6 = ((int (__stdcall *)(const char *, int))v5->FindMaterial)("lights/defaultProjectedLight", 1);
    this->falloffImage = *(idImage **)(v6 + 72);
  }
  if ( this->parms.pointLight )
  {
    memset(this->lightProject, 0, sizeof(this->lightProject));
    this->lightProject[0].a = 0.5 / this->parms.lightRadius.x;
    this->lightProject[1].b = 0.5 / this->parms.lightRadius.y;
    this->lightProject[3].c = 0.5 / this->parms.lightRadius.z;
    this->lightProject[0].d = 0.5;
    this->lightProject[1].d = 0.5;
    this->lightProject[2].d = 1.0;
    this->lightProject[3].d = 0.5;
  }
  else
  {
    R_SetLightProject(
      this->lightProject,
      vec3_origin,
      this->parms.target,
      this->parms.right,
      this->parms.up,
      this->parms.start,
      this->parms.end);
  }
  frustum = this->frustum;
  R_SetLightFrustum(this->lightProject, this->frustum);
  R_AxisToModelMatrix(&this->parms.axis, &this->parms.origin, this->modelMatrix);
  v25 = 6;
  do
  {
    b = frustum->b;
    dir.x = frustum->a;
    c = frustum->c;
    dir.y = b;
    d_low = LODWORD(frustum->d);
    dir.z = c;
    v32 = d_low;
    R_LocalPlaneToGlobal(this->modelMatrix, (const idPlane *)&dir, frustum++);
    --v25;
  }
  while ( v25 );
  lightProject = this->lightProject;
  v26 = 4;
  do
  {
    v12 = lightProject->b;
    dir.x = lightProject->a;
    v13 = lightProject->c;
    dir.y = v12;
    v14 = LODWORD(lightProject->d);
    dir.z = v13;
    v32 = v14;
    R_LocalPlaneToGlobal(this->modelMatrix, (const idPlane *)&dir, lightProject++);
    --v26;
  }
  while ( v26 );
  if ( this->parms.parallel )
  {
    x = this->parms.lightCenter.x;
    y = this->parms.lightCenter.y;
    z = this->parms.lightCenter.z;
    v18 = z * z + y * y + x * x;
    if ( v18 == 0.0 || (v19 = 1.0 / sqrt(v18), x = x * v19, y = y * v19, dir.z = z * v19, v19 * v18 == 0.0) )
      dir.z = 1.0;
    v27 = x * 100000.0;
    v28 = y * 100000.0;
    v20 = v27 + this->parms.origin.x;
    v21 = v28 + this->parms.origin.y;
    dir.z = dir.z * 100000.0 + this->parms.origin.z;
    this->globalLightOrigin.z = dir.z;
  }
  else
  {
    v29 = this->parms.axis.mat[2].y * this->parms.lightCenter.z
        + this->parms.axis.mat[1].y * this->parms.lightCenter.y
        + this->parms.axis.mat[0].y * this->parms.lightCenter.x;
    v30 = this->parms.axis.mat[2].z * this->parms.lightCenter.z
        + this->parms.axis.mat[1].z * this->parms.lightCenter.y
        + this->parms.axis.mat[0].z * this->parms.lightCenter.x;
    v22 = this->parms.axis.mat[2].x * this->parms.lightCenter.z
        + this->parms.axis.mat[1].x * this->parms.lightCenter.y
        + this->parms.lightCenter.x * this->parms.axis.mat[0].x
        + this->parms.origin.x;
    v23 = v29 + this->parms.origin.y;
    dir.z = v30 + this->parms.origin.z;
    v24 = v23;
    v20 = v22;
    v21 = v24;
    this->globalLightOrigin.z = dir.z;
  }
  this->globalLightOrigin.x = v20;
  this->globalLightOrigin.y = v21;
  R_FreeLightDefFrustum(this);
  this->frustumTris = R_PolytopeSurface(6, this->frustum, this->frustumWindings);
  R_MakeShadowFrustums(this);
}

// FUNC: void __cdecl R_CreateLightRefs(class idRenderLightLocal *)
void __cdecl R_CreateLightRefs(idRenderLightLocal *light)
{
  srfTriangles_s *frustumTris; // esi
  double v2; // st7
  int v3; // eax
  float y; // edx
  float z; // eax
  float x; // ecx
  float v7; // edx
  float v8; // eax
  float v9; // ecx
  float v10; // edx
  float v11; // eax
  idRenderWorldLocal *world; // ecx
  float v13; // edx
  float v14; // eax
  float v15; // edx
  float v16; // eax
  int v17; // ebx
  int v18; // edx
  float *p_z; // ecx
  idDrawVert *verts; // eax
  float v21; // ebp
  idDrawVert *v22; // eax
  double v23; // st7
  double v24; // st6
  double v25; // st7
  double v26; // st6
  double v27; // st5
  double v28; // st4
  idRenderWorldLocal *v29; // ecx
  int numVerts; // [esp+8h] [ebp-244h]
  idBox box; // [esp+18h] [ebp-234h] BYREF
  float v32; // [esp+54h] [ebp-1F8h]
  float v33; // [esp+58h] [ebp-1F4h]
  float v34; // [esp+68h] [ebp-1E4h]
  idVec3 points[40]; // [esp+6Ch] [ebp-1E0h] BYREF

  frustumTris = light->frustumTris;
  if ( frustumTris->numVerts > 40 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_CreateLightRefs: %i points in frustumTris!",
      frustumTris->numVerts);
  if ( !r_showUpdates.internalVar->integerValue
    || (v2 = frustumTris->bounds.b[1].x - frustumTris->bounds.b[0].x, v2 <= 1024.0)
    && frustumTris->bounds.b[1].y - frustumTris->bounds.b[0].y <= 1024.0
    || ((*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "big lightRef: %f,%f\n",
          v2,
          frustumTris->bounds.b[1].y - frustumTris->bounds.b[0].y),
        r_showUpdates.internalVar->integerValue != 2) )
  {
    v3 = light->world->PointInArea(light->world, &light->globalLightOrigin);
    light->areaNum = v3;
    if ( v3 == -1 )
      light->areaNum = light->world->PointInArea(light->world, &light->parms.origin);
    ++tr.viewCount;
    if ( light->parms.prelightModel
      && r_useLightPortalFlow.internalVar->integerValue
      && idMaterial::LightCastsShadows((idMaterial *)light->lightShader) )
    {
      idRenderWorldLocal::FlowLightThroughPortals(light->world, light);
    }
    else if ( light->parms.pointLight )
    {
      y = light->parms.origin.y;
      z = light->parms.origin.z;
      box.center.x = light->parms.origin.x;
      box.extents.x = light->parms.lightRadius.x;
      box.axis.mat[0].x = light->parms.axis.mat[0].x;
      x = light->parms.axis.mat[1].x;
      box.center.y = y;
      v7 = light->parms.lightRadius.y;
      box.center.z = z;
      v8 = light->parms.lightRadius.z;
      box.axis.mat[1].x = x;
      v9 = light->parms.axis.mat[2].x;
      box.extents.y = v7;
      v10 = light->parms.axis.mat[0].y;
      box.extents.z = v8;
      v11 = light->parms.axis.mat[0].z;
      box.axis.mat[2].x = v9;
      world = light->world;
      box.axis.mat[0].y = v10;
      v13 = light->parms.axis.mat[1].y;
      box.axis.mat[0].z = v11;
      v14 = light->parms.axis.mat[1].z;
      box.axis.mat[1].y = v13;
      v15 = light->parms.axis.mat[2].y;
      box.axis.mat[1].z = v14;
      v16 = light->parms.axis.mat[2].z;
      box.axis.mat[2].y = v15;
      box.axis.mat[2].z = v16;
      idRenderWorldLocal::PushPolytopeIntoTree(world, 0, light, 0, &box, 0, 0);
    }
    else
    {
      v17 = 0;
      if ( frustumTris->numVerts > 0 )
      {
        v18 = 0;
        p_z = &points[0].z;
        do
        {
          verts = frustumTris->verts;
          v21 = verts[v18].xyz.x;
          v22 = &verts[v18];
          *(p_z - 2) = v21;
          *(p_z - 1) = v22->xyz.y;
          *p_z = v22->xyz.z;
          ++v17;
          ++v18;
          p_z += 3;
        }
        while ( v17 < frustumTris->numVerts );
      }
      v23 = frustumTris->bounds.b[0].x + frustumTris->bounds.b[1].x;
      v24 = frustumTris->bounds.b[1].y + frustumTris->bounds.b[0].y;
      v34 = frustumTris->bounds.b[1].z + frustumTris->bounds.b[0].z;
      v32 = v23 * 0.5;
      box.center.x = v32;
      box.axis.mat[0].x = mat3_identity.mat[0].x;
      v33 = v24 * 0.5;
      box.center.y = v33;
      v25 = v34 * 0.5;
      box.axis.mat[0].y = mat3_identity.mat[0].y;
      box.center.z = v25;
      box.axis.mat[1].x = mat3_identity.mat[1].x;
      v26 = frustumTris->bounds.b[1].x - v32;
      box.axis.mat[1].y = mat3_identity.mat[1].y;
      v27 = frustumTris->bounds.b[1].y - v33;
      box.axis.mat[2].x = mat3_identity.mat[2].x;
      v28 = frustumTris->bounds.b[1].z - v25;
      numVerts = frustumTris->numVerts;
      v29 = light->world;
      box.axis.mat[2].y = mat3_identity.mat[2].y;
      v34 = v28;
      box.extents.z = v34;
      box.extents.x = v26;
      box.axis.mat[0].z = mat3_identity.mat[0].z;
      box.extents.y = v27;
      box.axis.mat[1].z = mat3_identity.mat[1].z;
      box.axis.mat[2].z = mat3_identity.mat[2].z;
      idRenderWorldLocal::PushPolytopeIntoTree(v29, 0, light, 0, &box, points, numVerts);
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::RenderLightFrustum(struct renderLight_s const &,class idPlane * const)
void __thiscall idRenderSystemLocal::RenderLightFrustum(
        idRenderSystemLocal *this,
        const renderLight_s *renderLight,
        idPlane *lightFrustum)
{
  float b; // ecx
  float c; // edx
  float d; // ecx
  int i; // esi
  idWinding *v7; // ecx
  idRenderLightLocal fakeLight; // [esp+4h] [ebp-4A0h] BYREF
  int v9; // [esp+4A0h] [ebp-4h]

  idRenderLightLocal::idRenderLightLocal(&fakeLight);
  v9 = 0;
  renderLight_s::operator=(&fakeLight.parms, (int)renderLight);
  idRenderLightLocal::DeriveLightData(&fakeLight);
  R_FreeStaticTriSurf(fakeLight.frustumTris);
  *lightFrustum = fakeLight.frustum[0];
  lightFrustum[1] = fakeLight.frustum[1];
  lightFrustum[2] = fakeLight.frustum[2];
  lightFrustum[3] = fakeLight.frustum[3];
  lightFrustum[4] = fakeLight.frustum[4];
  b = fakeLight.frustum[5].b;
  lightFrustum[5].a = fakeLight.frustum[5].a;
  c = fakeLight.frustum[5].c;
  lightFrustum[5].b = b;
  d = fakeLight.frustum[5].d;
  lightFrustum[5].c = c;
  lightFrustum[5].d = d;
  for ( i = 0; i < 6; ++i )
  {
    v7 = fakeLight.frustumWindings[i];
    if ( v7 )
    {
      ((void (__thiscall *)(idWinding *, int))v7->~idWinding)(v7, 1);
      fakeLight.frustumWindings[i] = 0;
    }
  }
}
