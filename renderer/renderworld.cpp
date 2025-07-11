
// FUNC: public: virtual bool __thiscall idRenderWorldLocal::EffectDefHasSound(struct renderEffect_s const *)
bool __thiscall idRenderWorldLocal::EffectDefHasSound(idRenderWorldLocal *this, const renderEffect_s *reffect)
{
  return reffect && bse->CheckDefForSound(bse, reffect);
}

// FUNC: public: virtual int __thiscall idRenderWorldLocal::NumPortalsInArea(int)
int __thiscall idRenderWorldLocal::NumPortalsInArea(idRenderWorldLocal *this, int areaNum)
{
  int numPortalAreas; // edx

  numPortalAreas = this->numPortalAreas;
  if ( areaNum < numPortalAreas && areaNum >= 0 )
    return this->portalAreas[areaNum].numPortals;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
    common.type,
    "idRenderWorld::NumPortalsInArea: bad areanum %i (min: 0, max: %d)",
    areaNum,
    numPortalAreas - 1);
  return 0;
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::GetPortals(int,struct exitPortal_t *,int)
void __thiscall idRenderWorldLocal::GetPortals(idRenderWorldLocal *this, int areaNum, exitPortal_t *ret, int size)
{
  int v4; // ebx
  portal_s *i; // esi

  v4 = 0;
  for ( i = this->portalAreas[areaNum].portals; v4 < size; ++ret )
  {
    if ( !i )
      break;
    ret->areas[0] = areaNum;
    ret->areas[1] = i->intoArea;
    ret->w = i->w;
    ret->blockingBits = i->doublePortal->blockingBits;
    ret->portalHandle = i->doublePortal - this->doublePortals + 1;
    i = i->next;
    ++v4;
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::GetPortal(int,int,struct exitPortal_t *)
void __thiscall idRenderWorldLocal::GetPortal(idRenderWorldLocal *this, int areaNum, int portalNum, exitPortal_t *ret)
{
  portal_s *next; // eax
  int v6; // ecx

  if ( !ret )
  {
    lastAreaNum = -1;
    lastPortalNum = -1;
    return;
  }
  if ( areaNum > this->numPortalAreas )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorld::GetPortal: areaNum > numAreas");
  if ( lastAreaNum == areaNum && lastPortalNum == portalNum - 1 && lastPortal )
  {
    next = lastPortal->next;
    lastPortalNum = portalNum;
  }
  else
  {
    next = this->portalAreas[areaNum].portals;
    v6 = 0;
    lastAreaNum = areaNum;
    lastPortalNum = portalNum;
    lastPortal = next;
    if ( !next )
      goto LABEL_15;
    while ( v6 != portalNum )
    {
      next = next->next;
      ++v6;
      if ( !next )
      {
        lastPortal = 0;
        goto LABEL_15;
      }
    }
  }
  lastPortal = next;
  if ( next )
  {
    ret->areas[0] = areaNum;
    ret->areas[1] = next->intoArea;
    ret->w = next->w;
    ret->blockingBits = next->doublePortal->blockingBits;
    ret->portalHandle = next->doublePortal - this->doublePortals + 1;
    return;
  }
LABEL_15:
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
    common.type,
    "idRenderWorld::GetPortal: portalNum > numPortals");
}

// FUNC: public: virtual struct exitPortal_t __thiscall idRenderWorldLocal::GetPortal(int,int)
exitPortal_t *__thiscall idRenderWorldLocal::GetPortal(
        idRenderWorldLocal *this,
        exitPortal_t *result,
        int areaNum,
        int portalNum)
{
  portal_s *portals; // eax
  int v6; // ecx
  exitPortal_t *v7; // eax
  const idWinding *w; // esi
  int intoArea; // ecx
  doublePortal_s *doublePortal; // eax
  int blockingBits; // edi
  int v12; // edx

  if ( areaNum > this->numPortalAreas )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorld::GetPortal: areaNum > numAreas");
  portals = this->portalAreas[areaNum].portals;
  v6 = 0;
  if ( portals )
  {
    while ( v6 != portalNum )
    {
      portals = portals->next;
      ++v6;
      if ( !portals )
        goto LABEL_6;
    }
    w = portals->w;
    intoArea = portals->intoArea;
    doublePortal = portals->doublePortal;
    blockingBits = doublePortal->blockingBits;
    v12 = doublePortal - this->doublePortals + 1;
    v7 = result;
    result->areas[0] = areaNum;
    result->areas[1] = intoArea;
    result->w = w;
    result->blockingBits = blockingBits;
    result->portalHandle = v12;
  }
  else
  {
LABEL_6:
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorld::GetPortal: portalNum > numPortals");
    v7 = result;
    result->areas[0] = 0;
    result->areas[1] = 0;
    result->w = 0;
    result->blockingBits = 0;
    result->portalHandle = 0;
  }
  return v7;
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugCircle(class idVec4 const &,class idVec3 const &,class idVec3 const &,float,int,int,bool)
void __thiscall idRenderWorldLocal::DebugCircle(
        idRenderWorldLocal *this,
        const idVec4 *color,
        const idVec3 *origin,
        const idVec3 *dir,
        float radius,
        int numSteps,
        int lifetime,
        BOOL depthTest)
{
  long double v10; // st7
  long double v11; // st6
  long double v12; // st7
  double v13; // st6
  long double v14; // st7
  int v16; // edi
  double v17; // st7
  double v18; // st7
  double v19; // st6
  idRenderWorldLocal_vtbl *v20; // edx
  long double v21; // st7
  long double v22; // st6
  long double v23; // st7
  long double v24; // st7
  float v25; // [esp+4h] [ebp-64h]
  float up; // [esp+8h] [ebp-60h]
  float upa; // [esp+8h] [ebp-60h]
  float upb; // [esp+8h] [ebp-60h]
  float up_4; // [esp+Ch] [ebp-5Ch]
  float up_4a; // [esp+Ch] [ebp-5Ch]
  float up_4b; // [esp+Ch] [ebp-5Ch]
  float up_8; // [esp+10h] [ebp-58h]
  float up_8a; // [esp+10h] [ebp-58h]
  float up_8b; // [esp+10h] [ebp-58h]
  float left; // [esp+14h] [ebp-54h]
  float lefta; // [esp+14h] [ebp-54h]
  float left_4; // [esp+18h] [ebp-50h]
  float left_4a; // [esp+18h] [ebp-50h]
  float left_8; // [esp+1Ch] [ebp-4Ch]
  float left_8a; // [esp+1Ch] [ebp-4Ch]
  float left_8b; // [esp+1Ch] [ebp-4Ch]
  idVec3 point; // [esp+20h] [ebp-48h] BYREF
  idVec3 lastPoint; // [esp+2Ch] [ebp-3Ch] BYREF
  float v44; // [esp+38h] [ebp-30h]
  float v45; // [esp+3Ch] [ebp-2Ch]
  float v46; // [esp+40h] [ebp-28h]
  float v47; // [esp+48h] [ebp-20h]
  float v48; // [esp+4Ch] [ebp-1Ch]
  float v49; // [esp+54h] [ebp-14h]
  float v50; // [esp+58h] [ebp-10h]
  float v51; // [esp+64h] [ebp-4h]
  float dira; // [esp+74h] [ebp+Ch]
  float dirb; // [esp+74h] [ebp+Ch]
  int radiusa; // [esp+78h] [ebp+10h]
  float i; // [esp+7Ch] [ebp+14h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    dira = dir->z;
    HIBYTE(dira) &= ~0x80u;
    if ( dira <= 0.69999999 )
    {
      left_8 = 0.0;
      v25 = dir->y * dir->y + dir->x * dir->x;
      v14 = 1.0 / sqrt(v25);
      dirb = v14;
      v12 = -(v14 * dir->y);
      v13 = dirb * dir->x;
      up = -(v13 * dir->z);
      up_4 = v12 * dir->z;
      up_8 = dirb * v25;
    }
    else
    {
      up = 0.0;
      v10 = dir->y * dir->y + dir->z * dir->z;
      v11 = 1.0 / sqrt(v10);
      up_4 = v11 * dir->z;
      up_8 = -(v11 * dir->y);
      v12 = v10 * v11;
      v13 = -(up_8 * dir->x);
      left_8 = up_4 * dir->x;
    }
    left = v12 * radius;
    v16 = 1;
    left_4 = v13 * radius;
    left_8a = left_8 * radius;
    upa = up * radius;
    up_4a = up_4 * radius;
    v17 = up_8 * radius;
    radiusa = 1;
    up_8a = v17;
    v18 = upa + origin->x;
    v19 = up_4a + origin->y;
    v50 = up_8a + origin->z;
    lastPoint.z = v50;
    lastPoint.x = v18;
    lastPoint.y = v19;
    if ( numSteps >= 1 )
    {
      v44 = upa;
      i = (float)numSteps;
      v45 = up_4a;
      v46 = up_8a;
      upb = left;
      up_4b = left_4;
      up_8b = left_8a;
      do
      {
        v20 = this->__vftable;
        v21 = (double)radiusa * idMath::TWO_PI / i;
        v22 = cos(v21);
        lefta = v44 * v22;
        left_4a = v45 * v22;
        left_8b = v46 * v22;
        v23 = sin(v21);
        v47 = up_4b * v23;
        v48 = up_8b * v23;
        v24 = upb * v23 + origin->x;
        v49 = v47 + origin->y;
        v50 = v48 + origin->z;
        v51 = v50 + left_8b;
        point.z = v51;
        point.x = v24 + lefta;
        point.y = v49 + left_4a;
        v20->DebugLine(this, color, &lastPoint, &point, lifetime, depthTest);
        ++v16;
        lastPoint = point;
        radiusa = v16;
      }
      while ( v16 <= numSteps );
    }
  }
}

// FUNC: public: virtual bool __thiscall idRenderWorldLocal::HasSkybox(int)
bool __thiscall idRenderWorldLocal::HasSkybox(idRenderWorldLocal *this, int areaNum)
{
  return this->portalAreas[areaNum].hasSkybox;
}

// FUNC: public: virtual class idVec3 __thiscall idRenderWorldLocal::WorldToScreen(struct renderView_s *,class idVec3)
idVec3 *__thiscall idRenderWorldLocal::WorldToScreen(
        idRenderWorldLocal *this,
        idVec3 *result,
        renderView_s *view,
        idVec3 point)
{
  bool cramZNear; // cl
  float fov_y; // eax
  idVec3 *v6; // eax
  int v7; // ecx
  double y; // st5
  int y2; // [esp+8h] [ebp-A0h]
  idScreenRect viewport; // [esp+Ch] [ebp-9Ch] BYREF
  idVec3 ndc; // [esp+1Ch] [ebp-8Ch] BYREF
  float projectionMatrix[16]; // [esp+28h] [ebp-80h] BYREF
  float modelViewMatrix[16]; // [esp+68h] [ebp-40h] BYREF

  memset(modelViewMatrix, 0, sizeof(modelViewMatrix));
  memset(projectionMatrix, 0, sizeof(projectionMatrix));
  R_SetViewMatrix(view, 0, modelViewMatrix);
  cramZNear = view->cramZNear;
  fov_y = view->fov_y;
  viewport.x1 = 0;
  viewport.x2 = 640;
  viewport.y1 = 0;
  viewport.y2 = 480;
  R_SetupProjection(projectionMatrix, view->fov_x, fov_y, &viewport, cramZNear);
  R_GlobalToNormalizedDeviceCoordinates(modelViewMatrix, projectionMatrix, &point, &ndc);
  v6 = result;
  y2 = viewport.y2;
  v7 = viewport.y2 - viewport.y1;
  result->x = (double)(viewport.x2 - viewport.x1) * (ndc.x + 1.0) * 0.5;
  y = ndc.y;
  result->z = ndc.z;
  result->y = (double)y2 - (double)v7 * (y + 1.0) * 0.5;
  return v6;
}

// FUNC: void __cdecl R_ListRenderLightDefs_f(class idCmdArgs const &)
void __cdecl R_ListRenderLightDefs_f()
{
  idRenderWorldLocal *primaryWorld; // eax
  int v1; // ebx
  _DWORD *v2; // ecx
  int v3; // eax
  int i; // edi
  int v5; // eax
  int j; // esi
  int v7; // ebp
  int v8; // eax
  int totalRef; // [esp+4h] [ebp-Ch]
  int totalIntr; // [esp+8h] [ebp-8h]
  int active; // [esp+Ch] [ebp-4h]

  primaryWorld = tr.primaryWorld;
  v1 = 0;
  if ( tr.primaryWorld )
  {
    active = 0;
    totalRef = 0;
    totalIntr = 0;
    if ( tr.primaryWorld->lightDefs.num > 0 )
    {
      do
      {
        v2 = &primaryWorld->lightDefs.list[v1]->__vftable;
        if ( v2 )
        {
          v3 = v2[289];
          for ( i = 0; v3; ++i )
            v3 = *(_DWORD *)(v3 + 16);
          v5 = v2[288];
          totalIntr += i;
          for ( j = 0; v5; ++j )
            v5 = *(_DWORD *)(v5 + 8);
          totalRef += j;
          v7 = *(_DWORD *)common.type;
          v8 = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v2[93] + 4) + 4))(*(_DWORD *)(v2[93] + 4));
          (*(void (**)(netadrtype_t, const char *, ...))(v7 + 124))(
            common.type,
            "%4i: %3i intr %2i refs %s\n",
            v1,
            i,
            j,
            v8);
          ++active;
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%4i: FREED\n", v1);
        }
        primaryWorld = tr.primaryWorld;
        ++v1;
      }
      while ( v1 < tr.primaryWorld->lightDefs.num );
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%i lightDefs, %i interactions, %i areaRefs\n",
      active,
      totalIntr,
      totalRef);
  }
}

// FUNC: void __cdecl R_ListRenderEntityDefs_f(class idCmdArgs const &)
void __cdecl R_ListRenderEntityDefs_f()
{
  idRenderWorldLocal *primaryWorld; // eax
  int v1; // ebx
  idRenderEntityLocal *v2; // ecx
  idInteraction *firstInteraction; // eax
  int i; // edi
  areaReference_s *entityRefs; // eax
  int j; // esi
  int v7; // ebp
  int v8; // eax
  int active; // [esp+4h] [ebp-4h]

  primaryWorld = tr.primaryWorld;
  v1 = 0;
  if ( tr.primaryWorld )
  {
    active = 0;
    if ( tr.primaryWorld->entityDefs.num > 0 )
    {
      do
      {
        v2 = primaryWorld->entityDefs.list[v1];
        if ( v2 )
        {
          firstInteraction = v2->firstInteraction;
          for ( i = 0; firstInteraction; ++i )
            firstInteraction = firstInteraction->entityNext;
          entityRefs = v2->entityRefs;
          for ( j = 0; entityRefs; ++j )
            entityRefs = entityRefs->ownerNext;
          v7 = *(_DWORD *)common.type;
          v8 = (int)v2->parms.hModel->Name(v2->parms.hModel);
          (*(void (**)(netadrtype_t, const char *, ...))(v7 + 124))(
            common.type,
            "%4i: %3i intr %2i refs %s\n",
            v1,
            i,
            j,
            v8);
          ++active;
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%4i: FREED\n", v1);
        }
        primaryWorld = tr.primaryWorld;
        ++v1;
      }
      while ( v1 < tr.primaryWorld->entityDefs.num );
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "total active: %i\n",
      active);
  }
}

// FUNC: void __cdecl R_ListRenderEffectDefs_f(class idCmdArgs const &)
void __cdecl R_ListRenderEffectDefs_f()
{
  idRenderWorldLocal *primaryWorld; // eax
  int v1; // esi
  int i; // edi
  rvRenderEffectLocal *v3; // eax
  areaReference_s *effectRefs; // eax
  int j; // ecx

  primaryWorld = tr.primaryWorld;
  if ( tr.primaryWorld )
  {
    v1 = 0;
    for ( i = 0; v1 < tr.primaryWorld->effectDefs.num; ++v1 )
    {
      v3 = primaryWorld->effectDefs.list[v1];
      if ( v3 )
      {
        effectRefs = v3->effectRefs;
        for ( j = 0; effectRefs; ++j )
          effectRefs = effectRefs->ownerNext;
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%4i: %2i refs\n",
          v1,
          j);
        ++i;
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%4i: FREED\n", v1);
      }
      primaryWorld = tr.primaryWorld;
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "total active: %i\n", i);
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::RemoveAllModelReferences(class idRenderModel *)
void __thiscall idRenderWorldLocal::RemoveAllModelReferences(idRenderWorldLocal *this, idRenderModel *model)
{
  int i; // esi
  int num; // eax
  bool v4; // cc
  int v5; // eax
  idRenderModel **list; // edx
  idRenderModel *v7; // ebx
  idRenderModel **v8; // edx

  for ( i = 0; i < this->localModels.num; ++i )
  {
    if ( this->localModels.list[i] == model && i >= 0 )
    {
      num = this->localModels.num;
      if ( i < num )
      {
        v4 = i < num - 1;
        this->localModels.num = num - 1;
        v5 = i;
        if ( v4 )
        {
          do
          {
            list = this->localModels.list;
            v7 = list[v5 + 1];
            v8 = &list[v5++];
            *v8 = v7;
          }
          while ( v5 < this->localModels.num );
        }
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::ClearMarkedDefs(void)
void __thiscall idRenderWorldLocal::ClearMarkedDefs(idRenderWorldLocal *this)
{
  if ( this->markedEntityDefs.list )
    Memory::Free(this->markedEntityDefs.list);
  this->markedEntityDefs.list = 0;
  this->markedEntityDefs.num = 0;
  this->markedEntityDefs.size = 0;
  if ( this->markedLightDefs.list )
    Memory::Free(this->markedLightDefs.list);
  this->markedLightDefs.list = 0;
  this->markedLightDefs.num = 0;
  this->markedLightDefs.size = 0;
  if ( this->markedEffectDefs.list )
    Memory::Free(this->markedEffectDefs.list);
  this->markedEffectDefs.list = 0;
  this->markedEffectDefs.num = 0;
  this->markedEffectDefs.size = 0;
}

// FUNC: public: void __thiscall idRenderWorldLocal::PushEntityDef(int)
void __thiscall idRenderWorldLocal::PushEntityDef(idRenderWorldLocal *this, int entityHandle)
{
  int num; // edx
  idRenderEntityLocal *v3; // ecx

  if ( entityHandle < 0 || (num = this->entityDefs.num, entityHandle >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::PushEntityDef: handle %i >= %i\n",
      entityHandle,
      this->entityDefs.num);
  }
  else
  {
    v3 = this->entityDefs.list[entityHandle];
    if ( v3 )
      R_CreateEntityRefs(v3);
    else
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorld::PushEntityDef: handle %i [0, %i] is NULL\n",
        entityHandle,
        num);
  }
}

// FUNC: public: virtual struct renderEntity_s const * __thiscall idRenderWorldLocal::GetRenderEntity(int)const
const renderEntity_s *__thiscall idRenderWorldLocal::GetRenderEntity(idRenderWorldLocal *this, int entityHandle)
{
  int num; // edx
  idRenderEntityLocal *v3; // ecx

  if ( entityHandle < 0 || (num = this->entityDefs.num, entityHandle >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::GetRenderEntity: invalid handle %i >= %i\n",
      entityHandle,
      this->entityDefs.num);
    return 0;
  }
  else
  {
    v3 = this->entityDefs.list[entityHandle];
    if ( v3 )
    {
      return &v3->parms;
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorld::GetRenderEntity: handle %i [0, %i] is NULL\n",
        entityHandle,
        num);
      return 0;
    }
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::PushLightDef(int)
void __thiscall idRenderWorldLocal::PushLightDef(idRenderWorldLocal *this, int lightHandle)
{
  int num; // edx
  idRenderLightLocal **list; // ecx
  idRenderLightLocal *v4; // esi

  if ( lightHandle < 0 || (num = this->lightDefs.num, lightHandle >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::PushLightDef: invalid handle %i >= %i\n",
      lightHandle,
      this->lightDefs.num);
  }
  else
  {
    list = this->lightDefs.list;
    v4 = list[lightHandle];
    if ( v4 )
    {
      v4->DeriveLightData(list[lightHandle]);
      R_CreateLightRefs(v4);
      R_CreateLightDefFogPortals(v4);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorld::PushLightDef: handle %i [0, %i] is NULL\n",
        lightHandle,
        num);
    }
  }
}

// FUNC: public: virtual struct renderLight_s const * __thiscall idRenderWorldLocal::GetRenderLight(int)const
const renderLight_s *__thiscall idRenderWorldLocal::GetRenderLight(idRenderWorldLocal *this, int lightHandle)
{
  int num; // edx
  idRenderLightLocal *v3; // ecx

  if ( lightHandle < 0 || (num = this->lightDefs.num, lightHandle >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::GetRenderLight: handle %i >= %i\n",
      lightHandle,
      this->lightDefs.num);
    return 0;
  }
  else
  {
    v3 = this->lightDefs.list[lightHandle];
    if ( v3 )
    {
      return &v3->parms;
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorld::GetRenderLight: handle %i [0, %i] is NULL\n",
        lightHandle,
        num);
      return 0;
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::StopEffectDef(int)
void __thiscall idRenderWorldLocal::StopEffectDef(idRenderWorldLocal *this, int effectHandle)
{
  rvRenderEffectLocal *v2; // esi

  if ( effectHandle < 0 || effectHandle >= this->effectDefs.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::StopEffectDef: invalid handle %i >= %i\n",
      effectHandle,
      this->effectDefs.num);
  }
  else
  {
    v2 = this->effectDefs.list[effectHandle];
    if ( v2 )
    {
      if ( session->writeDemo )
      {
        idRenderWorldLocal::WriteStopEffectDef(this, effectHandle);
        v2->writeToDemo = 1;
      }
      bse->StopEffect(bse, v2);
    }
  }
}

// FUNC: public: virtual class rvRenderEffectLocal const * __thiscall idRenderWorldLocal::GetEffectDef(int)const
const rvRenderEffectLocal *__thiscall idRenderWorldLocal::GetEffectDef(idRenderWorldLocal *this, int effectHandle)
{
  int num; // esi
  const rvRenderEffectLocal *result; // eax

  if ( effectHandle < 0 || (num = this->effectDefs.num, effectHandle >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::GetEffectDef: invalid handle %i >= %i\n",
      effectHandle,
      this->effectDefs.num);
    return 0;
  }
  else
  {
    result = this->effectDefs.list[effectHandle];
    if ( !result )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorld::GetEffectDef: handle %i [0, %i] is NULL\n",
        effectHandle,
        num);
      return 0;
    }
  }
  return result;
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::ProjectDecal(int,class idFixedWinding const &,class idVec3 const &,bool,float,class idMaterial const *,int)
void __thiscall idRenderWorldLocal::ProjectDecal(
        idRenderWorldLocal *this,
        int entityHandle,
        const idFixedWinding *winding,
        const idVec3 *projectionOrigin,
        bool parallel,
        float fadeDepth,
        const idMaterial *material,
        int startTime)
{
  idRenderEntityLocal *v8; // esi
  idRenderModel *hModel; // edi
  const idBounds *v10; // eax
  idBounds bounds; // [esp+8h] [ebp-1E8h] BYREF
  idBounds v12; // [esp+20h] [ebp-1D0h] BYREF
  decalProjectionInfo_s info; // [esp+38h] [ebp-1B8h] BYREF
  decalProjectionInfo_s localInfo; // [esp+114h] [ebp-DCh] BYREF

  if ( entityHandle < 0 || entityHandle >= this->entityDefs.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorld::ProjectOverlay: index = %i",
      entityHandle);
  }
  else
  {
    v8 = this->entityDefs.list[entityHandle];
    if ( v8 )
    {
      hModel = v8->parms.hModel;
      if ( hModel )
      {
        if ( hModel->IsDynamicModel(v8->parms.hModel) == DM_STATIC
          && !v8->parms.callback
          && idRenderModelDecal::CreateProjectionInfo(
               &info,
               winding,
               projectionOrigin,
               parallel,
               fadeDepth,
               material,
               startTime) )
        {
          v10 = hModel->Bounds(hModel, &v12, &v8->parms);
          idBounds::FromTransformedBounds(&bounds, v10, &v8->parms.origin, &v8->parms.axis);
          if ( bounds.b[1].x >= (double)info.projectionBounds.b[0].x
            && bounds.b[1].y >= (double)info.projectionBounds.b[0].y
            && bounds.b[1].z >= (double)info.projectionBounds.b[0].z
            && bounds.b[0].x <= (double)info.projectionBounds.b[1].x
            && bounds.b[0].y <= (double)info.projectionBounds.b[1].y
            && bounds.b[0].z <= (double)info.projectionBounds.b[1].z )
          {
            idRenderModelDecal::GlobalProjectionInfoToLocal(&localInfo, &info, &v8->parms.origin, &v8->parms.axis);
            localInfo.force = v8->parms.customShader != 0;
            if ( !v8->decals )
              v8->decals = idRenderModelDecal::Alloc();
            idRenderModelDecal::CreateDecal(v8->decals, hModel, COERCE_FLOAT(&localInfo));
          }
        }
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::ProjectOverlay(int,class idPlane const * const,class idMaterial const *)
void __thiscall idRenderWorldLocal::ProjectOverlay(
        idRenderWorldLocal *this,
        int entityHandle,
        const idPlane *localTextureAxis,
        const idMaterial *material)
{
  idRenderEntityLocal *v4; // esi
  const idRenderModel *v5; // edi

  if ( entityHandle < 0 || entityHandle >= this->entityDefs.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorld::ProjectOverlay: index = %i",
      entityHandle);
  }
  else
  {
    v4 = this->entityDefs.list[entityHandle];
    if ( v4 && v4->parms.hModel->IsDynamicModel(v4->parms.hModel) == DM_CACHED )
    {
      v5 = R_EntityDefDynamicModel(v4, 0);
      if ( !v4->overlay )
        v4->overlay = idRenderModelOverlay::Alloc();
      idRenderModelOverlay::CreateOverlay(v4->overlay, v5, localTextureAxis, material);
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::RemoveDecals(int)
void __thiscall idRenderWorldLocal::RemoveDecals(idRenderWorldLocal *this, int entityHandle)
{
  idRenderEntityLocal **list; // ecx
  idRenderEntityLocal *v3; // esi

  if ( entityHandle < 0 || entityHandle >= this->entityDefs.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorld::ProjectOverlay: index = %i",
      entityHandle);
  }
  else
  {
    list = this->entityDefs.list;
    v3 = list[entityHandle];
    if ( v3 )
    {
      R_FreeEntityDefDecals(list[entityHandle]);
      R_FreeEntityDefOverlay(v3);
    }
  }
}

// FUNC: public: virtual int __thiscall idRenderWorldLocal::PointInArea(class idVec3 const &)const
int __thiscall idRenderWorldLocal::PointInArea(idRenderWorldLocal *this, const idVec3 *point)
{
  areaNode_t *areaNodes; // edx
  int v4; // edx
  int v5; // esi

  areaNodes = this->areaNodes;
  if ( !areaNodes )
    return -1;
  while ( 1 )
  {
    if ( areaNodes->plane.c * point->z
       + areaNodes->plane.b * point->y
       + areaNodes->plane.a * point->x
       + areaNodes->plane.d <= 0.0 )
      v4 = areaNodes->children[1];
    else
      v4 = areaNodes->children[0];
    if ( !v4 )
      return -1;
    if ( v4 < 0 )
      break;
    areaNodes = &this->areaNodes[v4];
  }
  v5 = -1 - v4;
  if ( -1 - v4 >= this->numPortalAreas )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorld::PointInArea: area out of range");
  return v5;
}

// FUNC: public: void __thiscall idRenderWorldLocal::AddEntityRefToArea(class idRenderEntityLocal *,struct portalArea_s *)
void __thiscall idRenderWorldLocal::AddEntityRefToArea(
        idRenderWorldLocal *this,
        idRenderEntityLocal *def,
        portalArea_s *area)
{
  areaReference_s *v4; // eax

  if ( !def )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorldLocal::AddEntityRefToArea: NULL def");
  v4 = idBlockAlloc<areaReference_s,1024,16>::Alloc(&this->areaReferenceAllocator);
  ++tr.pc.c_entityReferences;
  v4->entity = def;
  v4->light = 0;
  v4->effect = 0;
  v4->ownerNext = def->entityRefs;
  def->entityRefs = v4;
  v4->areaNext = &area->entityRefs;
  v4->area = area;
  v4->areaPrev = area->entityRefs.areaPrev;
  area->entityRefs.areaPrev = v4;
  v4->areaPrev->areaNext = v4;
}

// FUNC: public: void __thiscall idRenderWorldLocal::AddLightRefToArea(class idRenderLightLocal *,struct portalArea_s *)
void __thiscall idRenderWorldLocal::AddLightRefToArea(
        idRenderWorldLocal *this,
        idRenderLightLocal *light,
        portalArea_s *area)
{
  areaReference_s *v3; // eax

  v3 = idBlockAlloc<areaReference_s,1024,16>::Alloc(&this->areaReferenceAllocator);
  v3->entity = 0;
  v3->effect = 0;
  v3->light = light;
  v3->area = area;
  v3->ownerNext = light->references;
  light->references = v3;
  ++tr.pc.c_lightReferences;
  area->lightRefs.areaNext->areaPrev = v3;
  v3->areaNext = area->lightRefs.areaNext;
  v3->areaPrev = &area->lightRefs;
  area->lightRefs.areaNext = v3;
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::GenerateAllInteractions(void)
void __thiscall idRenderWorldLocal::GenerateAllInteractions(idRenderWorldLocal *this)
{
  int v2; // eax
  int v3; // edi
  int i; // ebp
  int v5; // eax

  if ( glConfig.isInitialized )
  {
    v2 = Sys_Milliseconds();
    this->generateAllInteractionsCalled = 0;
    v3 = 0;
    tr.staticAllocCount = 0;
    tr.viewDef = 0;
    for ( i = v2; v3 < this->lightDefs.num; ++v3 )
    {
      if ( this->lightDefs.list[v3] )
        idRenderWorldLocal::CreateLightDefInteractions(this, this->lightDefs.list[v3]);
    }
    v5 = Sys_Milliseconds();
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::GenerateAllInteractions, msec = %i, staticAllocCount = %i.\n",
      v5 - i,
      tr.staticAllocCount);
    this->generateAllInteractionsCalled = 1;
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::FreeInteractions(void)
void __thiscall idRenderWorldLocal::FreeInteractions(idRenderWorldLocal *this)
{
  int i; // edi
  idRenderEntityLocal *v3; // esi
  idInteraction *j; // ecx

  for ( i = 0; i < this->entityDefs.num; ++i )
  {
    v3 = this->entityDefs.list[i];
    if ( v3 )
    {
      for ( j = v3->firstInteraction; j; j = v3->firstInteraction )
        idInteraction::UnlinkAndFree(j);
    }
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::PushPolytopeIntoTree_r(class idRenderEntityLocal *,class idRenderLightLocal *,class rvRenderEffectLocal *,class idBox const &,class idVec3 const *,int,int)
void __thiscall idRenderWorldLocal::PushPolytopeIntoTree_r(
        idRenderWorldLocal *this,
        idRenderEntityLocal *def,
        idRenderLightLocal *light,
        rvRenderEffectLocal *reffect,
        const idBox *box,
        const idVec3 *points,
        int numPoints,
        int nodeNum)
{
  int v10; // esi
  idRenderWorldLocal *v11; // edi
  bool v12; // sf
  int v13; // esi
  int v14; // eax
  double v15; // st7
  double v16; // st6
  int v17; // eax
  char v18; // cl
  char v19; // dl
  float *p_y; // edi
  double v21; // st7
  bool v22; // zf
  double v23; // st7
  bool v24; // zf
  double v25; // st7
  bool v26; // zf
  double v27; // st7
  bool v28; // zf
  float *v29; // edi
  double v30; // st7
  bool v31; // zf
  portalArea_s *v32; // esi
  areaReference_s *v33; // eax
  areaReference_s *v34; // eax
  areaReference_s *areaNext; // edx
  areaReference_s *p_effectRefs; // esi
  float v37; // [esp+10h] [ebp-8h]
  float boxa; // [esp+28h] [ebp+10h]
  int numPointsa; // [esp+30h] [ebp+18h]
  float i; // [esp+34h] [ebp+1Ch]

  v10 = nodeNum;
  v11 = this;
  v12 = nodeNum < 0;
  while ( !v12 )
  {
    v13 = (int)&v11->areaNodes[v10];
    if ( r_useNodeCommonChildren.internalVar->integerValue )
    {
      v14 = *(_DWORD *)(v13 + 24);
      if ( v14 != -2 && v11->portalAreas[v14].viewCount == tr.viewCount )
        return;
    }
    v15 = box->center.z * *(float *)(v13 + 8)
        + box->center.y * *(float *)(v13 + 4)
        + box->center.x * *(float *)v13
        + *(float *)(v13 + 12);
    v37 = (box->axis.mat[0].z * *(float *)(v13 + 8)
         + box->axis.mat[0].y * *(float *)(v13 + 4)
         + box->axis.mat[0].x * *(float *)v13)
        * box->extents.x;
    i = (box->axis.mat[1].z * *(float *)(v13 + 8)
       + box->axis.mat[1].y * *(float *)(v13 + 4)
       + box->axis.mat[1].x * *(float *)v13)
      * box->extents.y;
    boxa = (box->axis.mat[2].z * *(float *)(v13 + 8)
          + box->axis.mat[2].y * *(float *)(v13 + 4)
          + *(float *)v13 * box->axis.mat[2].x)
         * box->extents.z;
    v16 = COERCE_FLOAT(LODWORD(boxa) & 0x7FFFFFFF)
        + COERCE_FLOAT(LODWORD(i) & 0x7FFFFFFF)
        + COERCE_FLOAT(LODWORD(v37) & 0x7FFFFFFF);
    if ( v15 - v16 < 0.0 )
    {
      if ( v16 + v15 > 0.0 )
      {
        if ( numPoints <= 0 )
          goto LABEL_60;
        v17 = 0;
        v18 = 0;
        v19 = 0;
        numPointsa = 0;
        if ( numPoints < 4 )
          goto LABEL_34;
        p_y = &points[1].y;
        while ( 2 )
        {
          v21 = *(p_y - 4) * *(float *)v13
              + *(p_y - 2) * *(float *)(v13 + 8)
              + *(p_y - 3) * *(float *)(v13 + 4)
              + *(float *)(v13 + 12);
          if ( v21 <= 0.0 )
          {
            if ( v21 < 0.0 )
            {
              v19 = 1;
              v22 = v18 == 0;
              goto LABEL_16;
            }
          }
          else
          {
            v18 = 1;
            v22 = v19 == 0;
LABEL_16:
            if ( !v22 )
              goto LABEL_42;
          }
          v23 = *(p_y - 1) * *(float *)v13
              + p_y[1] * *(float *)(v13 + 8)
              + *p_y * *(float *)(v13 + 4)
              + *(float *)(v13 + 12);
          if ( v23 <= 0.0 )
          {
            if ( v23 < 0.0 )
            {
              v19 = 1;
              v24 = v18 == 0;
              goto LABEL_21;
            }
          }
          else
          {
            v18 = 1;
            v24 = v19 == 0;
LABEL_21:
            if ( !v24 )
              goto LABEL_42;
          }
          v25 = p_y[2] * *(float *)v13
              + p_y[4] * *(float *)(v13 + 8)
              + p_y[3] * *(float *)(v13 + 4)
              + *(float *)(v13 + 12);
          if ( v25 <= 0.0 )
          {
            if ( v25 < 0.0 )
            {
              v19 = 1;
              v26 = v18 == 0;
              goto LABEL_26;
            }
          }
          else
          {
            v18 = 1;
            v26 = v19 == 0;
LABEL_26:
            if ( !v26 )
              goto LABEL_42;
          }
          v27 = p_y[5] * *(float *)v13
              + p_y[7] * *(float *)(v13 + 8)
              + p_y[6] * *(float *)(v13 + 4)
              + *(float *)(v13 + 12);
          if ( v27 > 0.0 )
          {
            v18 = 1;
            v28 = v19 == 0;
            goto LABEL_31;
          }
          if ( v27 >= 0.0 )
            goto LABEL_32;
          v19 = 1;
          v28 = v18 == 0;
LABEL_31:
          if ( v28 )
          {
LABEL_32:
            numPointsa += 4;
            p_y += 12;
            if ( numPointsa < numPoints - 3 )
              continue;
            v11 = this;
            v17 = numPointsa;
LABEL_34:
            if ( v17 < numPoints )
            {
              v29 = &points[v17].y;
              while ( 1 )
              {
                v30 = *(v29 - 1) * *(float *)v13
                    + v29[1] * *(float *)(v13 + 8)
                    + *v29 * *(float *)(v13 + 4)
                    + *(float *)(v13 + 12);
                if ( v30 > 0.0 )
                  break;
                if ( v30 < 0.0 )
                {
                  v19 = 1;
                  v31 = v18 == 0;
LABEL_40:
                  if ( !v31 )
                    goto LABEL_42;
                }
                ++numPointsa;
                v29 += 3;
                if ( numPointsa >= numPoints )
                  goto LABEL_42;
              }
              v18 = 1;
              v31 = v19 == 0;
              goto LABEL_40;
            }
          }
          else
          {
LABEL_42:
            v11 = this;
          }
          break;
        }
        if ( ((unsigned __int8)v18 & (unsigned __int8)v19) != 0 )
        {
LABEL_60:
          if ( *(_DWORD *)(v13 + 16) )
            idRenderWorldLocal::PushPolytopeIntoTree_r(
              v11,
              def,
              light,
              reffect,
              box,
              points,
              numPoints,
              *(_DWORD *)(v13 + 16));
        }
        else if ( v18 )
        {
          v10 = *(_DWORD *)(v13 + 16);
          goto LABEL_47;
        }
      }
      v10 = *(_DWORD *)(v13 + 20);
      goto LABEL_47;
    }
    v10 = *(_DWORD *)(v13 + 16);
LABEL_47:
    v12 = v10 < 0;
    if ( !v10 )
      return;
  }
  v32 = &v11->portalAreas[-v10 - 1];
  if ( v32->viewCount != tr.viewCount )
  {
    v32->viewCount = tr.viewCount;
    if ( def )
      idRenderWorldLocal::AddEntityRefToArea(v11, def, v32);
    if ( light )
    {
      v33 = idBlockAlloc<areaReference_s,1024,16>::Alloc(&v11->areaReferenceAllocator);
      v33->light = light;
      v33->entity = 0;
      v33->effect = 0;
      v33->area = v32;
      v33->ownerNext = light->references;
      light->references = v33;
      ++tr.pc.c_lightReferences;
      v32->lightRefs.areaNext->areaPrev = v33;
      v33->areaNext = v32->lightRefs.areaNext;
      v33->areaPrev = &v32->lightRefs;
      v32->lightRefs.areaNext = v33;
    }
    if ( reffect )
    {
      v34 = idBlockAlloc<areaReference_s,1024,16>::Alloc(&v11->areaReferenceAllocator);
      v34->area = v32;
      v34->effect = reffect;
      v34->entity = 0;
      v34->light = 0;
      v34->ownerNext = reffect->effectRefs;
      reffect->effectRefs = v34;
      ++tr.pc.c_effectReferences;
      areaNext = v32->effectRefs.areaNext;
      p_effectRefs = &v32->effectRefs;
      areaNext->areaPrev = v34;
      v34->areaNext = p_effectRefs->areaNext;
      v34->areaPrev = p_effectRefs;
      p_effectRefs->areaNext = v34;
    }
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::PushPolytopeIntoTree(class idRenderEntityLocal *,class idRenderLightLocal *,class rvRenderEffectLocal *,class idBox const &,class idVec3 const *,int)
void __thiscall idRenderWorldLocal::PushPolytopeIntoTree(
        idRenderWorldLocal *this,
        idRenderEntityLocal *def,
        idRenderLightLocal *light,
        rvRenderEffectLocal *reffect,
        const idBox *box,
        const idVec3 *points,
        int numPoints)
{
  int c_lightReferences; // edi

  if ( this->areaNodes )
  {
    c_lightReferences = tr.pc.c_lightReferences;
    idRenderWorldLocal::PushPolytopeIntoTree_r(this, def, light, reffect, box, points, numPoints, 0);
    if ( light )
      light->numPortalsCrossed = tr.pc.c_lightReferences - c_lightReferences;
    ++tr.pc.c_numVolumePushes;
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugArrow(class idVec4 const &,class idVec3 const &,class idVec3 const &,int,int)
void __thiscall idRenderWorldLocal::DebugArrow(
        idRenderWorldLocal *this,
        const idVec4 *color,
        const idVec3 *start,
        const idVec3 *end,
        int size,
        int lifetime)
{
  int integerValue; // eax
  double v8; // st7
  int v9; // ecx
  long double v10; // st5
  double v11; // st7
  double v12; // st6
  long double v13; // st5
  long double v14; // rt0
  long double v15; // st7
  long double v16; // st7
  double v17; // st7
  float v18; // eax
  int v19; // edi
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st6
  double v24; // st7
  double v25; // st6
  idRenderWorldLocal_vtbl *v26; // edx
  double v27; // st7
  double v28; // st6
  float forward; // [esp+14h] [ebp-F8h]
  float forwarda; // [esp+14h] [ebp-F8h]
  float forward_4; // [esp+18h] [ebp-F4h]
  float forward_4a; // [esp+18h] [ebp-F4h]
  float forward_8; // [esp+1Ch] [ebp-F0h]
  float right; // [esp+20h] [ebp-ECh]
  float righta; // [esp+20h] [ebp-ECh]
  float right_4; // [esp+24h] [ebp-E8h]
  float right_4a; // [esp+24h] [ebp-E8h]
  float right_8; // [esp+28h] [ebp-E4h]
  float v39; // [esp+2Ch] [ebp-E0h]
  float up; // [esp+30h] [ebp-DCh]
  float upa; // [esp+30h] [ebp-DCh]
  float up_4; // [esp+34h] [ebp-D8h]
  float up_4a; // [esp+34h] [ebp-D8h]
  float up_8; // [esp+38h] [ebp-D4h]
  float a; // [esp+3Ch] [ebp-D0h]
  float v46; // [esp+40h] [ebp-CCh]
  float v47; // [esp+44h] [ebp-C8h]
  float v48; // [esp+44h] [ebp-C8h]
  float v49; // [esp+48h] [ebp-C4h]
  float v50; // [esp+4Ch] [ebp-C0h]
  float v51; // [esp+50h] [ebp-BCh]
  float v52; // [esp+58h] [ebp-B4h]
  float v53; // [esp+5Ch] [ebp-B0h]
  float v54; // [esp+68h] [ebp-A4h]
  float v55; // [esp+6Ch] [ebp-A0h]
  float v56; // [esp+6Ch] [ebp-A0h]
  float v57; // [esp+70h] [ebp-9Ch]
  float v58; // [esp+74h] [ebp-98h]
  float v59; // [esp+7Ch] [ebp-90h]
  float v60; // [esp+80h] [ebp-8Ch]
  float v61; // [esp+84h] [ebp-88h]
  idVec3 v1; // [esp+88h] [ebp-84h] BYREF
  float v63; // [esp+98h] [ebp-74h]
  float v64; // [esp+9Ch] [ebp-70h]
  float v65; // [esp+A4h] [ebp-68h]
  float v66; // [esp+A8h] [ebp-64h]
  float v67; // [esp+B0h] [ebp-5Ch]
  float v68; // [esp+B4h] [ebp-58h]
  float v69; // [esp+BCh] [ebp-50h]
  float v70; // [esp+C0h] [ebp-4Ch]
  float v71; // [esp+C8h] [ebp-44h]
  float v72; // [esp+CCh] [ebp-40h]
  idVec3 v2; // [esp+D0h] [ebp-3Ch] BYREF
  float v74; // [esp+E0h] [ebp-2Ch]
  float v75; // [esp+E4h] [ebp-28h]
  float v76; // [esp+ECh] [ebp-20h]
  float v77; // [esp+F0h] [ebp-1Ch]
  float v78; // [esp+FCh] [ebp-10h]
  float v79; // [esp+108h] [ebp-4h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    this->DebugLine(this, color, start, end, lifetime, 0);
    integerValue = r_debugArrowStep.internalVar->integerValue;
    if ( integerValue > 10 )
    {
      if ( arrowStep != integerValue )
      {
        v8 = 0.0;
        arrowStep = r_debugArrowStep.internalVar->integerValue;
        v9 = 0;
        do
        {
          ++v9;
          v10 = idMath::M_DEG2RAD * v8;
          flt_110DA21C[v9] = cos(v10);
          flt_110DA17C[v9] = sin(v10);
          v8 = v8 + (double)integerValue;
        }
        while ( v8 < 360.0 );
        arrowCos[v9] = arrowCos[0];
        arrowSin[v9] = arrowSin[0];
      }
      v11 = end->x - start->x;
      v47 = end->y - start->y;
      forward_4 = v47;
      v12 = end->z - start->z;
      forward = v11;
      forward_8 = v12;
      v13 = v12 * v12 + v47 * v47 + v11 * v11;
      if ( v13 != 0.0 )
      {
        v14 = 1.0 / sqrt(v13);
        forward = v11 * v14;
        forward_4 = v47 * v14;
        forward_8 = v12 * v14;
      }
      v15 = forward_4 * forward_4 + forward * forward;
      if ( v15 == 0.0 )
      {
        right = 1.0;
        right_4 = 0.0;
      }
      else
      {
        v16 = 1.0 / sqrt(v15);
        right = -(forward_4 * v16);
        right_4 = v16 * forward;
      }
      v51 = forward_4;
      v58 = forward_4;
      v52 = right;
      v53 = right_4;
      a = 0.0;
      v55 = forward_4 * right - right_4 * forward;
      v17 = forward * 0.0 - forward_8 * right;
      v18 = forward;
      up = right_4 * forward_8 - forward_4 * 0.0;
      forwarda = right;
      up_4 = v17;
      forward_4a = right_4;
      v39 = (float)size;
      v59 = up;
      v60 = up_4;
      v50 = v18;
      v57 = v18;
      v61 = v55;
      right_8 = v55;
      righta = up;
      right_4a = up_4;
      v19 = 0;
      do
      {
        v20 = v39 * arrowCos[v19] * 0.5;
        v69 = v51 * v39;
        v70 = forward_8 * v39;
        v21 = end->x - v50 * v39;
        v67 = end->y - v69;
        v68 = end->z - v70;
        v76 = forward_4a * v20;
        v77 = 0.0 * v20;
        v22 = forwarda * v20 + v21;
        v74 = v76 + v67;
        v75 = v77 + v68;
        v23 = v39 * arrowSin[v19] * 0.5;
        upa = v59 * v23;
        up_4a = v60 * v23;
        up_8 = v61 * v23;
        v78 = up_8 + v75;
        v1.z = v78;
        v1.x = v22 + upa;
        v1.y = up_4a + v74;
        v24 = v39 * flt_110DA224[v19] * 0.5;
        v71 = v58 * v39;
        v72 = v70;
        v25 = end->x - v57 * v39;
        v65 = end->y - v71;
        v26 = this->__vftable;
        v66 = end->z - v70;
        v63 = v53 * v24;
        v64 = 0.0 * v24;
        v27 = v52 * v24 + v25;
        v54 = v63 + v65;
        v56 = v64 + v66;
        v28 = v39 * flt_110DA184[v19] * 0.5;
        v46 = righta * v28;
        v48 = right_4a * v28;
        v49 = right_8 * v28;
        v79 = v49 + v56;
        v2.z = v79;
        v2.x = v27 + v46;
        v2.y = v48 + v54;
        v26->DebugLine(this, color, &v1, end, lifetime, 0);
        this->DebugLine(this, color, &v1, &v2, lifetime, 0);
        ++v19;
        a = (double)arrowStep + a;
      }
      while ( a < 360.0 );
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugWinding(class idVec4 const &,class idWinding const &,class idVec3 const &,class idMat3 const &,int,bool)
void __thiscall idRenderWorldLocal::DebugWinding(
        idRenderWorldLocal *this,
        const idVec4 *color,
        const idWinding *w,
        const idVec3 *origin,
        const idMat3 *axis,
        int lifetime,
        BOOL depthTest)
{
  int numPoints; // ecx
  idVec5 *p; // eax
  double y; // st7
  float *p_x; // eax
  int v12; // ebp
  double v13; // st7
  double v14; // st7
  double v15; // st6
  idVec5 *v16; // eax
  idRenderWorldLocal_vtbl *v17; // edx
  double v18; // st7
  double v19; // st7
  double v20; // st6
  bool v21; // cc
  idVec3 point; // [esp+14h] [ebp-30h] BYREF
  idVec3 lastPoint; // [esp+20h] [ebp-24h] BYREF
  float v25; // [esp+30h] [ebp-14h]
  float v26; // [esp+34h] [ebp-10h]
  float v27; // [esp+40h] [ebp-4h]
  const idWinding *wa; // [esp+4Ch] [ebp+8h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    numPoints = w->numPoints;
    if ( numPoints >= 2 )
    {
      p = w->p;
      y = p[numPoints - 1].y;
      p_x = &p[numPoints - 1].x;
      v12 = 0;
      v13 = y * axis->mat[1].x + axis->mat[0].x * *p_x + axis->mat[2].x * p_x[2];
      v25 = axis->mat[0].y * *p_x + axis->mat[2].y * p_x[2] + p_x[1] * axis->mat[1].y;
      v26 = axis->mat[2].z * p_x[2] + *p_x * axis->mat[0].z + p_x[1] * axis->mat[1].z;
      v14 = v13 + origin->x;
      v15 = v25 + origin->y;
      v26 = v26 + origin->z;
      lastPoint.z = v26;
      lastPoint.x = v14;
      lastPoint.y = v15;
      wa = 0;
      do
      {
        v16 = (idVec5 *)((char *)wa + (unsigned int)w->p);
        v17 = this->__vftable;
        v18 = v16->y * axis->mat[1].x + axis->mat[0].x * v16->x + v16->z * axis->mat[2].x;
        v25 = axis->mat[0].y * v16->x + v16->z * axis->mat[2].y + v16->y * axis->mat[1].y;
        v26 = v16->z * axis->mat[2].z + v16->y * axis->mat[1].z + axis->mat[0].z * v16->x;
        v19 = v18 + origin->x;
        v20 = v25 + origin->y;
        v27 = v26 + origin->z;
        point.z = v27;
        point.x = v19;
        point.y = v20;
        v17->DebugLine(this, color, &lastPoint, &point, lifetime, depthTest);
        wa = (const idWinding *)((char *)wa + 20);
        v21 = ++v12 < w->numPoints;
        lastPoint = point;
      }
      while ( v21 );
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugBox(class idVec4 const &,class idBox const &,int)
void __thiscall idRenderWorldLocal::DebugBox(idRenderWorldLocal *this, const idVec4 *color, idBox *box, int lifetime)
{
  idVec3 *v5; // ebx
  int v6; // edi
  int v7; // [esp+3Ch] [ebp-64h]
  idVec3 v[8]; // [esp+40h] [ebp-60h] BYREF
  char boxa; // [esp+A8h] [ebp+8h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    idBox::ToPoints(box, v);
    boxa = 1;
    v5 = v;
    v7 = 4;
    do
    {
      v6 = boxa & 3;
      this->DebugLine(this, color, v5, &v[v6], lifetime, 0);
      this->DebugLine(this, color, &v5[4], &v[v6 + 4], lifetime, 0);
      this->DebugLine(this, color, v5, &v5[4], lifetime, 0);
      ++boxa;
      ++v5;
      --v7;
    }
    while ( v7 );
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugFrustum(class idVec4 const &,class idFrustum const &,bool,int)
void __thiscall idRenderWorldLocal::DebugFrustum(
        idRenderWorldLocal *this,
        const idVec4 *color,
        idFrustum *frustum,
        bool showFromOrigin,
        int lifetime)
{
  int v7; // eax
  int v8; // edi
  idVec3 *v9; // edi
  int v10; // eax
  const idVec3 *v11; // edi
  idVec3 v[8]; // [esp+14h] [ebp-60h] BYREF
  int showFromOrigina; // [esp+80h] [ebp+Ch]
  int showFromOriginb; // [esp+80h] [ebp+Ch]
  idVec3 *lifetimea; // [esp+84h] [ebp+10h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    idFrustum::ToPoints(frustum, v);
    if ( frustum->dNear > 0.0 )
    {
      v7 = 0;
      lifetimea = v;
      do
      {
        v8 = v7 + 1;
        this->DebugLine(this, color, lifetimea++, &v[((_BYTE)v7 + 1) & 3], lifetime, 0);
        v7 = v8;
      }
      while ( v8 < 4 );
      if ( showFromOrigin )
      {
        v9 = v;
        showFromOrigina = 4;
        do
        {
          this->DebugLine(this, color, (const idVec3 *)frustum, v9++, lifetime, 0);
          --showFromOrigina;
        }
        while ( showFromOrigina );
      }
    }
    v10 = 0;
    v11 = &v[4];
    do
    {
      showFromOriginb = v10 + 1;
      this->DebugLine(this, color, v11, &v[((v10 + 1) & 3) + 4], lifetime, 0);
      this->DebugLine(this, color, &v11[-4], v11, lifetime, 0);
      v10 = showFromOriginb;
      ++v11;
    }
    while ( showFromOriginb < 4 );
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugCone(class idVec4 const &,class idVec3 const &,class idVec3 const &,float,float,int)
void __thiscall idRenderWorldLocal::DebugCone(
        idRenderWorldLocal *this,
        const idVec4 *color,
        const idVec3 *apex,
        const idVec3 *dir,
        float radius1,
        float radius2,
        int lifetime)
{
  long double x; // st7
  long double y; // st6
  long double z; // st5
  long double v11; // st4
  long double v12; // rt0
  long double v13; // st4
  long double v14; // st4
  float v15; // ebp
  int v16; // ebx
  idRenderWorldLocal_vtbl *v17; // edx
  long double v18; // st7
  long double v19; // st6
  long double v20; // rt2
  long double v21; // st6
  double v22; // st7
  double v23; // st6
  idRenderWorldLocal_vtbl *v24; // eax
  long double v25; // st7
  long double v26; // st6
  long double v27; // rt1
  long double v28; // st6
  long double v29; // st7
  double v30; // st6
  double v31; // st5
  int i; // [esp+3Ch] [ebp-D0h]
  int ia; // [esp+3Ch] [ebp-D0h]
  float v34; // [esp+40h] [ebp-CCh]
  float v35; // [esp+40h] [ebp-CCh]
  float v36; // [esp+44h] [ebp-C8h]
  float v37; // [esp+44h] [ebp-C8h]
  float v38; // [esp+48h] [ebp-C4h]
  float v39; // [esp+4Ch] [ebp-C0h]
  float v40; // [esp+4Ch] [ebp-C0h]
  float v41; // [esp+4Ch] [ebp-C0h]
  float v42; // [esp+50h] [ebp-BCh]
  float v43; // [esp+50h] [ebp-BCh]
  float v44; // [esp+50h] [ebp-BCh]
  float v45; // [esp+50h] [ebp-BCh]
  float v46; // [esp+54h] [ebp-B8h]
  float v47; // [esp+58h] [ebp-B4h]
  float v48; // [esp+58h] [ebp-B4h]
  float v49; // [esp+5Ch] [ebp-B0h]
  float v50; // [esp+5Ch] [ebp-B0h]
  float v51; // [esp+60h] [ebp-ACh]
  idVec3 p2; // [esp+64h] [ebp-A8h] BYREF
  float v53; // [esp+70h] [ebp-9Ch]
  float v54; // [esp+74h] [ebp-98h]
  float v55; // [esp+78h] [ebp-94h]
  float v56; // [esp+7Ch] [ebp-90h]
  float v57; // [esp+80h] [ebp-8Ch]
  float v58; // [esp+84h] [ebp-88h]
  float v59; // [esp+88h] [ebp-84h]
  float v60; // [esp+8Ch] [ebp-80h]
  float v61; // [esp+90h] [ebp-7Ch]
  idVec3 lastp2; // [esp+94h] [ebp-78h] BYREF
  float v63; // [esp+A4h] [ebp-68h]
  float v64; // [esp+A8h] [ebp-64h]
  idVec3 p1; // [esp+ACh] [ebp-60h] BYREF
  float v66; // [esp+B8h] [ebp-54h]
  float v67; // [esp+BCh] [ebp-50h]
  float v68; // [esp+C0h] [ebp-4Ch]
  idMat3 axis; // [esp+C4h] [ebp-48h]
  idVec3 lastp1; // [esp+E8h] [ebp-24h] BYREF
  float v71; // [esp+FCh] [ebp-10h]
  float v72; // [esp+108h] [ebp-4h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    x = dir->x;
    y = dir->y;
    z = dir->z;
    v11 = z * z + y * y + x * x;
    if ( v11 != 0.0 )
    {
      v12 = 1.0 / sqrt(v11);
      x = x * v12;
      y = y * v12;
      z = z * v12;
    }
    axis.mat[0].z = 0.0;
    v13 = y * y + x * x;
    if ( v13 == 0.0 )
    {
      axis.mat[0].x = 1.0;
      axis.mat[0].y = 0.0;
    }
    else
    {
      v14 = 1.0 / sqrt(v13);
      axis.mat[0].x = -(y * v14);
      axis.mat[0].y = x * v14;
    }
    v39 = axis.mat[0].y * z - y * 0.0;
    v42 = x * 0.0 - axis.mat[0].x * z;
    v61 = -(axis.mat[0].x * y - axis.mat[0].y * x);
    axis.mat[1].z = v61;
    axis.mat[1].x = -v39;
    v15 = v61;
    axis.mat[1].y = -v42;
    v53 = apex->x + dir->x;
    v54 = apex->y + dir->y;
    v55 = apex->z + dir->z;
    v43 = axis.mat[1].y * radius2;
    v46 = v61 * radius2;
    v61 = v46 + v55;
    lastp2.z = v61;
    lastp2.x = axis.mat[1].x * radius2 + v53;
    lastp2.y = v43 + v54;
    if ( radius1 == 0.0 )
    {
      v47 = axis.mat[1].x;
      v49 = axis.mat[1].y;
      v16 = 20;
      i = 20;
      v34 = axis.mat[0].x;
      v36 = axis.mat[0].y;
      v38 = axis.mat[0].z;
      do
      {
        v17 = this->__vftable;
        v18 = (double)i * idMath::M_DEG2RAD;
        v19 = cos(v18);
        v40 = v47 * v19;
        v44 = v49 * v19;
        v20 = v19 * v15;
        v21 = sin(v18);
        v63 = v36 * v21;
        v64 = v38 * v21;
        v66 = v34 * v21 + v40;
        v67 = v63 + v44;
        v56 = v66 * radius2;
        v57 = v67 * radius2;
        v61 = (v20 + v64) * radius2 + v55;
        p2.z = v61;
        p2.x = v56 + v53;
        p2.y = v57 + v54;
        v17->DebugLine(this, color, &lastp2, &p2, lifetime, 0);
        this->DebugLine(this, color, &p2, apex, lifetime, 0);
        v16 += 20;
        lastp2 = p2;
        i = v16;
      }
      while ( v16 <= 360 );
    }
    else
    {
      v35 = axis.mat[1].x;
      v57 = axis.mat[1].y * radius1;
      v37 = axis.mat[1].y;
      ia = 20;
      v58 = v15 * radius1;
      v48 = axis.mat[0].x;
      v50 = axis.mat[0].y;
      v22 = axis.mat[1].x * radius1 + apex->x;
      v23 = v57 + apex->y;
      v61 = v58 + apex->z;
      lastp1.z = v61;
      lastp1.x = v22;
      v51 = axis.mat[0].z;
      lastp1.y = v23;
      do
      {
        v24 = this->__vftable;
        v25 = (double)ia * idMath::M_DEG2RAD;
        v26 = cos(v25);
        v56 = v35 * v26;
        v57 = v37 * v26;
        v27 = v26 * v15;
        v28 = sin(v25);
        v67 = v50 * v28;
        v68 = v51 * v28;
        v41 = v48 * v28 + v56;
        v45 = v67 + v57;
        v29 = v27 + v68;
        v63 = v45 * radius1;
        v64 = v29 * radius1;
        v30 = v41 * radius1 + apex->x;
        v31 = v63 + apex->y;
        v72 = v64 + apex->z;
        p1.z = v72;
        p1.x = v30;
        p1.y = v31;
        v59 = v41 * radius2;
        v60 = v45 * radius2;
        v71 = v29 * radius2 + v55;
        p2.z = v71;
        p2.x = v59 + v53;
        p2.y = v60 + v54;
        v24->DebugLine(this, color, &lastp1, &p1, lifetime, 0);
        this->DebugLine(this, color, &lastp2, &p2, lifetime, 0);
        this->DebugLine(this, color, &p1, &p2, lifetime, 0);
        lastp1 = p1;
        lastp2 = p2;
        ia += 20;
      }
      while ( ia <= 360 );
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugAxis(class idVec3 const &,class idMat3 const &)
void __thiscall idRenderWorldLocal::DebugAxis(idRenderWorldLocal *this, const idVec3 *origin, const idMat3 *axis)
{
  float y; // eax
  float z; // ecx
  double v6; // st7
  idRenderWorldLocal_vtbl *v7; // edx
  double v8; // st6
  double v9; // st5
  idRenderWorldLocal_vtbl *v10; // eax
  double v11; // st7
  double v12; // st7
  idRenderWorldLocal_vtbl *v13; // edx
  double v14; // st7
  idRenderWorldLocal_vtbl *v15; // eax
  double v16; // st7
  idRenderWorldLocal_vtbl *v17; // edx
  double v18; // st7
  idRenderWorldLocal_vtbl *v19; // eax
  idVec3 start; // [esp+64h] [ebp-24h] BYREF
  idVec3 end; // [esp+70h] [ebp-18h] BYREF
  float v22; // [esp+80h] [ebp-8h]
  float v23; // [esp+84h] [ebp-4h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    y = origin->y;
    z = origin->z;
    v6 = axis->mat[0].x * 20.0;
    start.x = origin->x;
    v7 = this->__vftable;
    v8 = axis->mat[0].y * 20.0;
    start.y = y;
    v9 = axis->mat[0].z;
    start.z = z;
    v23 = v9 * 20.0;
    end.x = start.x + v6;
    end.y = y + v8;
    end.z = z + v23;
    v7->DebugArrow(this, &colorWhite, &start, &end, 2, 0);
    v10 = this->__vftable;
    v11 = axis->mat[0].x * -20.0;
    v22 = axis->mat[0].y * -20.0;
    v23 = axis->mat[0].z * -20.0;
    v23 = v23 + start.z;
    end.z = v23;
    end.x = v11 + start.x;
    end.y = v22 + start.y;
    v10->DebugArrow(this, &colorWhite, &start, &end, 2, 0);
    v12 = axis->mat[1].x * 20.0;
    v22 = axis->mat[1].y * 20.0;
    v23 = axis->mat[1].z * 20.0;
    v23 = v23 + start.z;
    end.x = v12 + start.x;
    v13 = this->__vftable;
    end.y = v22 + start.y;
    end.z = v23;
    v13->DebugArrow(this, &colorGreen, &start, &end, 2, 0);
    v14 = axis->mat[1].x * -20.0;
    v15 = this->__vftable;
    v22 = axis->mat[1].y * -20.0;
    v23 = axis->mat[1].z * -20.0;
    v23 = v23 + start.z;
    end.z = v23;
    end.x = v14 + start.x;
    end.y = v22 + start.y;
    v15->DebugArrow(this, &colorGreen, &start, &end, 2, 0);
    v16 = axis->mat[2].x * 20.0;
    v17 = this->__vftable;
    v22 = axis->mat[2].y * 20.0;
    v23 = axis->mat[2].z * 20.0;
    v23 = v23 + start.z;
    end.z = v23;
    end.x = v16 + start.x;
    end.y = v22 + start.y;
    v17->DebugArrow(this, &colorBlue, &start, &end, 2, 0);
    v18 = axis->mat[2].x * -20.0;
    v22 = axis->mat[2].y * -20.0;
    v23 = axis->mat[2].z * -20.0;
    v19 = this->__vftable;
    v23 = v23 + start.z;
    end.z = v23;
    end.x = v18 + start.x;
    end.y = v22 + start.y;
    v19->DebugArrow(this, &colorBlue, &start, &end, 2, 0);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::DebugScreenRect(class idVec4 const &,class idScreenRect const &,struct viewDef_s const *,int)
void __thiscall idRenderWorldLocal::DebugScreenRect(
        idRenderWorldLocal *this,
        const idVec4 *color,
        const idScreenRect *rect,
        const viewDef_s *viewDef,
        const int lifetime)
{
  double v7; // st7
  double v8; // st6
  long double v9; // st5
  double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st6
  double v14; // st5
  idVec3 *v15; // edi
  double v16; // st6
  double v17; // st5
  double v18; // st6
  double v19; // st5
  double v20; // st7
  int v21; // eax
  int v22; // esi
  float vScale; // [esp+4h] [ebp-64h]
  float v24; // [esp+8h] [ebp-60h]
  float v25; // [esp+Ch] [ebp-5Ch]
  float v26; // [esp+Ch] [ebp-5Ch]
  float v27; // [esp+Ch] [ebp-5Ch]
  float v28; // [esp+Ch] [ebp-5Ch]
  float v29; // [esp+10h] [ebp-58h]
  float v30; // [esp+10h] [ebp-58h]
  float v31; // [esp+10h] [ebp-58h]
  float v32; // [esp+1Ch] [ebp-4Ch]
  float v33; // [esp+1Ch] [ebp-4Ch]
  float v34; // [esp+1Ch] [ebp-4Ch]
  float v35; // [esp+1Ch] [ebp-4Ch]
  float bounds_4; // [esp+24h] [ebp-44h]
  float bounds_8; // [esp+28h] [ebp-40h]
  float bounds_16; // [esp+30h] [ebp-38h]
  idVec3 p[4]; // [esp+38h] [ebp-30h] BYREF
  float viewDefa; // [esp+74h] [ebp+Ch]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    v7 = (double)(viewDef->viewport.x2 - viewDef->viewport.x1) * 0.5;
    v8 = (double)(viewDef->viewport.y2 - viewDef->viewport.y1) * 0.5;
    viewDefa = r_znear.internalVar->floatValue + 1.0;
    v9 = tan(viewDef->renderView.fov_x * 0.5 * idMath::M_DEG2RAD) * viewDefa;
    vScale = tan(viewDef->renderView.fov_y * 0.5 * idMath::M_DEG2RAD) * viewDefa;
    bounds_4 = ((double)rect->x1 - v7) * (-1.0 / v7) * v9;
    bounds_16 = ((double)rect->x2 - v7) * (-1.0 / v7) * v9;
    bounds_8 = ((double)rect->y1 - v8) * (1.0 / v8) * vScale;
    v10 = ((double)rect->y2 - v8) * (1.0 / v8) * vScale;
    v25 = bounds_8 * viewDef->renderView.viewaxis.mat[2].y
        + bounds_4 * viewDef->renderView.viewaxis.mat[1].y
        + viewDefa * viewDef->renderView.viewaxis.mat[0].y;
    v29 = bounds_8 * viewDef->renderView.viewaxis.mat[2].z
        + bounds_4 * viewDef->renderView.viewaxis.mat[1].z
        + viewDefa * viewDef->renderView.viewaxis.mat[0].z;
    v11 = bounds_8 * viewDef->renderView.viewaxis.mat[2].x
        + bounds_4 * viewDef->renderView.viewaxis.mat[1].x
        + viewDefa * viewDef->renderView.viewaxis.mat[0].x
        + viewDef->renderView.vieworg.x;
    v12 = v25 + viewDef->renderView.vieworg.y;
    v32 = v29 + viewDef->renderView.vieworg.z;
    p[0].z = v32;
    p[0].x = v11;
    p[0].y = v12;
    v26 = bounds_8 * viewDef->renderView.viewaxis.mat[2].y
        + bounds_16 * viewDef->renderView.viewaxis.mat[1].y
        + viewDefa * viewDef->renderView.viewaxis.mat[0].y;
    v30 = bounds_8 * viewDef->renderView.viewaxis.mat[2].z
        + bounds_16 * viewDef->renderView.viewaxis.mat[1].z
        + viewDefa * viewDef->renderView.viewaxis.mat[0].z;
    v13 = bounds_8 * viewDef->renderView.viewaxis.mat[2].x
        + bounds_16 * viewDef->renderView.viewaxis.mat[1].x
        + viewDefa * viewDef->renderView.viewaxis.mat[0].x
        + viewDef->renderView.vieworg.x;
    v14 = v26 + viewDef->renderView.vieworg.y;
    v33 = v30 + viewDef->renderView.vieworg.z;
    p[1].z = v33;
    p[1].x = v13;
    p[1].y = v14;
    v15 = p;
    v27 = v10 * viewDef->renderView.viewaxis.mat[2].y
        + bounds_16 * viewDef->renderView.viewaxis.mat[1].y
        + viewDefa * viewDef->renderView.viewaxis.mat[0].y;
    v31 = v10 * viewDef->renderView.viewaxis.mat[2].z
        + bounds_16 * viewDef->renderView.viewaxis.mat[1].z
        + viewDefa * viewDef->renderView.viewaxis.mat[0].z;
    v16 = v10 * viewDef->renderView.viewaxis.mat[2].x
        + bounds_16 * viewDef->renderView.viewaxis.mat[1].x
        + viewDefa * viewDef->renderView.viewaxis.mat[0].x
        + viewDef->renderView.vieworg.x;
    v17 = v27 + viewDef->renderView.vieworg.y;
    v34 = v31 + viewDef->renderView.vieworg.z;
    p[2].z = v34;
    p[2].x = v16;
    p[2].y = v17;
    v24 = v10 * viewDef->renderView.viewaxis.mat[2].x
        + bounds_4 * viewDef->renderView.viewaxis.mat[1].x
        + viewDefa * viewDef->renderView.viewaxis.mat[0].x;
    v28 = v10 * viewDef->renderView.viewaxis.mat[2].y
        + bounds_4 * viewDef->renderView.viewaxis.mat[1].y
        + viewDefa * viewDef->renderView.viewaxis.mat[0].y;
    v18 = v24 + viewDef->renderView.vieworg.x;
    v19 = v10 * viewDef->renderView.viewaxis.mat[2].z
        + bounds_4 * viewDef->renderView.viewaxis.mat[1].z
        + viewDefa * viewDef->renderView.viewaxis.mat[0].z;
    v20 = v28 + viewDef->renderView.vieworg.y;
    v35 = v19 + viewDef->renderView.vieworg.z;
    p[3].z = v35;
    p[3].x = v18;
    v21 = 0;
    p[3].y = v20;
    do
    {
      v22 = v21 + 1;
      this->DebugLine(this, color, v15, &p[((_BYTE)v21 + 1) & 3], 0, 0);
      v21 = v22;
      ++v15;
    }
    while ( v22 < 4 );
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::RegenerateWorld(void)
void __thiscall idRenderWorldLocal::RegenerateWorld(idRenderWorldLocal *this)
{
  idCmdArgs args; // [esp+0h] [ebp-904h] BYREF

  args.argc = 0;
  R_RegenerateWorld_f(&args);
}

// FUNC: public: virtual unsigned int __thiscall idRenderWorldLocal::MemorySummary(class idCmdArgs const &)
unsigned int __thiscall idRenderWorldLocal::MemorySummary(idRenderWorldLocal *this, const idCmdArgs *args)
{
  int v3; // esi
  unsigned int v4; // esi

  if ( !glConfig.isInitialized )
    return 0;
  v3 = 8 * this->areaNumRefAllocator.total
     + 28 * (this->areaReferenceAllocator.total + 4 * this->interactionAllocator.total);
  v4 = (frameData[tr.smpFrame]->memoryHighwater + R_AllocatedMemoryTriSurfs() + v3) >> 10;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "Renderer        - %dK\n",
    v4);
  return v4;
}

// FUNC: bool __cdecl R_GlobalShaderOverride(class idMaterial const * *)
char __cdecl R_GlobalShaderOverride(const idMaterial **shader)
{
  int v1; // eax
  const idMaterial *globalMaterial; // eax
  const char *value; // eax

  v1 = (int)*shader;
  if ( (*shader)->numStages > 0 || *(_DWORD *)(v1 + 76) || *(_DWORD *)(v1 + 80) )
  {
    globalMaterial = tr.primaryRenderView.globalMaterial;
    if ( tr.primaryRenderView.globalMaterial )
    {
LABEL_7:
      *shader = globalMaterial;
      return 1;
    }
    value = r_materialOverride.internalVar->value;
    if ( *value )
    {
      globalMaterial = declManager->FindMaterial(declManager, value, 1);
      goto LABEL_7;
    }
  }
  return 0;
}

// FUNC: class idMaterial const * __cdecl R_RemapShaderBySkin(class idMaterial const *,class idDeclSkin const *,class idMaterial const *)
const idMaterial *__cdecl R_RemapShaderBySkin(
        const idMaterial *shader,
        idDeclSkin *skin,
        const idMaterial *customShader)
{
  const idMaterial *result; // eax

  result = shader;
  if ( shader && (shader->numStages > 0 || shader->entityGui || shader->gui) )
  {
    if ( customShader )
    {
      return shader->deform == DFRM_NONE ? customShader : 0;
    }
    else if ( skin )
    {
      return idDeclSkin::RemapShaderBySkin(skin, shader);
    }
  }
  return result;
}

// FUNC: public: virtual class idBounds __thiscall idRenderWorldLocal::WorldToScreen(struct renderView_s *,class idBounds)
idBounds *__thiscall idRenderWorldLocal::WorldToScreen(
        idRenderWorldLocal *this,
        idBounds *result,
        renderView_s *view,
        idBounds bounds)
{
  bool cramZNear; // cl
  float fov_y; // eax
  double v6; // st7
  double y2; // st6
  double v8; // st5
  bool *v9; // esi
  int v10; // edi
  double z; // st7
  double y; // st6
  double x; // st5
  double v14; // st7
  idBounds *v15; // eax
  float v16; // edx
  float v17; // ecx
  float v18; // edx
  float v19; // edx
  float extremaWindowY; // [esp+Ch] [ebp-E8h]
  float maxsWindowY; // [esp+10h] [ebp-E4h]
  bool pairs[6][3]; // [esp+14h] [ebp-E0h] BYREF
  float maxsWindowX; // [esp+28h] [ebp-CCh]
  float minsWindowX; // [esp+2Ch] [ebp-C8h]
  float minsWindowY; // [esp+30h] [ebp-C4h]
  idScreenRect viewport; // [esp+34h] [ebp-C0h] BYREF
  idVec3 minsNDC; // [esp+44h] [ebp-B0h] BYREF
  idVec3 maxsNDC; // [esp+50h] [ebp-A4h] BYREF
  idVec3 extrema; // [esp+5Ch] [ebp-98h] BYREF
  idVec3 extremaNDC; // [esp+68h] [ebp-8Ch] BYREF
  float projectionMatrix[16]; // [esp+74h] [ebp-80h] BYREF
  float modelViewMatrix[16]; // [esp+B4h] [ebp-40h] BYREF

  memset(modelViewMatrix, 0, sizeof(modelViewMatrix));
  memset(projectionMatrix, 0, sizeof(projectionMatrix));
  R_SetViewMatrix(view, 0, modelViewMatrix);
  cramZNear = view->cramZNear;
  fov_y = view->fov_y;
  viewport.x1 = 0;
  viewport.x2 = 640;
  viewport.y1 = 0;
  viewport.y2 = 480;
  R_SetupProjection(projectionMatrix, view->fov_x, fov_y, &viewport, cramZNear);
  R_GlobalToNormalizedDeviceCoordinates(modelViewMatrix, projectionMatrix, bounds.b, &minsNDC);
  R_GlobalToNormalizedDeviceCoordinates(modelViewMatrix, projectionMatrix, &bounds.b[1], &maxsNDC);
  v6 = (double)(viewport.x2 - viewport.x1);
  minsWindowX = (minsNDC.x + 1.0) * v6 * 0.5;
  y2 = (double)viewport.y2;
  v8 = (double)(viewport.y2 - viewport.y1);
  minsWindowY = y2 - (minsNDC.y + 1.0) * v8 * 0.5;
  *(_WORD *)&pairs[0][0] = 0;
  pairs[0][2] = 1;
  maxsWindowX = (maxsNDC.x + 1.0) * v6 * 0.5;
  *(_WORD *)&pairs[1][0] = 256;
  pairs[1][2] = 0;
  *(_WORD *)&pairs[2][0] = 1;
  pairs[2][2] = 0;
  pairs[3][0] = 0;
  *(_WORD *)&pairs[3][1] = 257;
  *(_WORD *)&pairs[4][0] = 257;
  pairs[4][2] = 0;
  maxsWindowY = y2 - (maxsNDC.y + 1.0) * v8 * 0.5;
  *(_WORD *)&pairs[5][0] = 1;
  pairs[5][2] = 1;
  v9 = &pairs[0][1];
  v10 = 6;
  do
  {
    if ( v9[1] )
      z = bounds.b[1].z;
    else
      z = bounds.b[0].z;
    if ( *v9 )
      y = bounds.b[1].y;
    else
      y = bounds.b[0].y;
    if ( *(v9 - 1) )
      x = bounds.b[1].x;
    else
      x = bounds.b[0].x;
    extrema.x = x;
    extrema.y = y;
    extrema.z = z;
    R_GlobalToNormalizedDeviceCoordinates(modelViewMatrix, projectionMatrix, &extrema, &extremaNDC);
    v14 = (double)(viewport.x2 - viewport.x1) * (extremaNDC.x + 1.0) * 0.5;
    extremaWindowY = (double)viewport.y2 - (double)(viewport.y2 - viewport.y1) * (extremaNDC.y + 1.0) * 0.5;
    if ( v14 <= maxsWindowX )
    {
      if ( v14 < minsWindowX )
        minsWindowX = v14;
    }
    else
    {
      maxsWindowX = v14;
    }
    if ( extremaWindowY <= (double)maxsWindowY )
    {
      if ( extremaWindowY < (double)minsWindowY )
        minsWindowY = (double)viewport.y2 - (double)(viewport.y2 - viewport.y1) * (extremaNDC.y + 1.0) * 0.5;
    }
    else
    {
      maxsWindowY = (double)viewport.y2 - (double)(viewport.y2 - viewport.y1) * (extremaNDC.y + 1.0) * 0.5;
    }
    v9 += 3;
    --v10;
  }
  while ( v10 );
  v15 = result;
  v16 = minsWindowY;
  result->b[0].x = minsWindowX;
  v17 = minsNDC.z;
  result->b[0].y = v16;
  v18 = maxsWindowX;
  result->b[0].z = v17;
  result->b[1].x = v18;
  v19 = maxsNDC.z;
  result->b[1].y = maxsWindowY;
  result->b[1].z = v19;
  return v15;
}

// FUNC: public: void __thiscall idRenderWorldLocal::MarkEntityDef(int)
void __thiscall idRenderWorldLocal::MarkEntityDef(idRenderWorldLocal *this, int entityHandle)
{
  int num; // edi
  int v4; // eax
  int *v5; // edx
  int v6; // ebx
  int v7; // ecx
  int v8; // ecx
  int *v9; // ecx
  int v10; // edx
  int *v11; // ecx
  int granularity; // eax
  bool v13; // cc
  int i; // eax
  int v15; // ebx
  int size; // ecx
  int v17; // ecx
  int *list; // edi
  int j; // eax

  if ( r_suppressMultipleUpdates.internalVar->integerValue )
  {
    num = this->markedEntityDefs.num;
    v4 = 0;
    if ( num <= 0 )
    {
      v6 = entityHandle;
LABEL_15:
      if ( v6 >= 0 )
      {
        if ( !this->markedEntityDefs.list )
        {
          granularity = this->markedEntityDefs.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->markedEntityDefs.size )
            {
              v13 = granularity < this->markedEntityDefs.num;
              this->markedEntityDefs.size = granularity;
              if ( v13 )
                this->markedEntityDefs.num = granularity;
              this->markedEntityDefs.list = (int *)Memory::Allocate(4 * granularity);
              for ( i = 0; i < this->markedEntityDefs.num; ++i )
                this->markedEntityDefs.list[i] = *(_DWORD *)(4 * i);
            }
          }
          else
          {
            this->markedEntityDefs.list = 0;
            this->markedEntityDefs.num = 0;
            this->markedEntityDefs.size = 0;
          }
        }
        v15 = this->markedEntityDefs.num;
        size = this->markedEntityDefs.size;
        if ( v15 == size )
        {
          if ( !this->markedEntityDefs.granularity )
            this->markedEntityDefs.granularity = 16;
          v17 = this->markedEntityDefs.granularity
              + size
              - (this->markedEntityDefs.granularity + size) % this->markedEntityDefs.granularity;
          if ( v17 > 0 )
          {
            if ( v17 != this->markedEntityDefs.size )
            {
              list = this->markedEntityDefs.list;
              this->markedEntityDefs.size = v17;
              if ( v17 < v15 )
                this->markedEntityDefs.num = v17;
              this->markedEntityDefs.list = (int *)Memory::Allocate(4 * v17);
              for ( j = 0; j < this->markedEntityDefs.num; ++j )
                this->markedEntityDefs.list[j] = list[j];
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( this->markedEntityDefs.list )
              Memory::Free(this->markedEntityDefs.list);
            this->markedEntityDefs.list = 0;
            this->markedEntityDefs.num = 0;
            this->markedEntityDefs.size = 0;
          }
        }
        this->markedEntityDefs.list[this->markedEntityDefs.num++] = entityHandle;
      }
    }
    else
    {
      v5 = this->markedEntityDefs.list;
      while ( 1 )
      {
        v6 = entityHandle;
        if ( *v5 == entityHandle )
          break;
        if ( *v5 == -1 - entityHandle )
        {
          if ( v4 >= 0 )
          {
            v7 = this->markedEntityDefs.num;
            if ( v4 < v7 )
            {
              v8 = v7 - 1;
              for ( this->markedEntityDefs.num = v8; v4 < this->markedEntityDefs.num; *v11 = v10 )
              {
                v9 = this->markedEntityDefs.list;
                v10 = v9[v4 + 1];
                v11 = &v9[v4++];
              }
            }
          }
          break;
        }
        ++v4;
        ++v5;
        if ( v4 >= num )
          goto LABEL_15;
      }
      ++tr.pc.c_entityPushesSuppressed;
    }
  }
  else if ( entityHandle >= 0 )
  {
    idRenderWorldLocal::PushEntityDef(this, entityHandle);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::MarkLightDef(int)
void __thiscall idRenderWorldLocal::MarkLightDef(idRenderWorldLocal *this, int lightHandle)
{
  int num; // edi
  int v4; // eax
  int *v5; // edx
  int v6; // ebx
  int v7; // ecx
  int v8; // ecx
  int *v9; // ecx
  int v10; // edx
  int *v11; // ecx
  int granularity; // eax
  bool v13; // cc
  int i; // eax
  int v15; // ebx
  int size; // ecx
  int v17; // ecx
  int *list; // edi
  int j; // eax

  if ( r_suppressMultipleUpdates.internalVar->integerValue )
  {
    num = this->markedLightDefs.num;
    v4 = 0;
    if ( num <= 0 )
    {
      v6 = lightHandle;
LABEL_15:
      if ( v6 >= 0 )
      {
        if ( !this->markedLightDefs.list )
        {
          granularity = this->markedLightDefs.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->markedLightDefs.size )
            {
              v13 = granularity < this->markedLightDefs.num;
              this->markedLightDefs.size = granularity;
              if ( v13 )
                this->markedLightDefs.num = granularity;
              this->markedLightDefs.list = (int *)Memory::Allocate(4 * granularity);
              for ( i = 0; i < this->markedLightDefs.num; ++i )
                this->markedLightDefs.list[i] = *(_DWORD *)(4 * i);
            }
          }
          else
          {
            this->markedLightDefs.list = 0;
            this->markedLightDefs.num = 0;
            this->markedLightDefs.size = 0;
          }
        }
        v15 = this->markedLightDefs.num;
        size = this->markedLightDefs.size;
        if ( v15 == size )
        {
          if ( !this->markedLightDefs.granularity )
            this->markedLightDefs.granularity = 16;
          v17 = this->markedLightDefs.granularity
              + size
              - (this->markedLightDefs.granularity + size) % this->markedLightDefs.granularity;
          if ( v17 > 0 )
          {
            if ( v17 != this->markedLightDefs.size )
            {
              list = this->markedLightDefs.list;
              this->markedLightDefs.size = v17;
              if ( v17 < v15 )
                this->markedLightDefs.num = v17;
              this->markedLightDefs.list = (int *)Memory::Allocate(4 * v17);
              for ( j = 0; j < this->markedLightDefs.num; ++j )
                this->markedLightDefs.list[j] = list[j];
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( this->markedLightDefs.list )
              Memory::Free(this->markedLightDefs.list);
            this->markedLightDefs.list = 0;
            this->markedLightDefs.num = 0;
            this->markedLightDefs.size = 0;
          }
        }
        this->markedLightDefs.list[this->markedLightDefs.num++] = lightHandle;
      }
    }
    else
    {
      v5 = this->markedLightDefs.list;
      while ( 1 )
      {
        v6 = lightHandle;
        if ( *v5 == lightHandle )
          break;
        if ( *v5 == -1 - lightHandle )
        {
          if ( v4 >= 0 )
          {
            v7 = this->markedLightDefs.num;
            if ( v4 < v7 )
            {
              v8 = v7 - 1;
              for ( this->markedLightDefs.num = v8; v4 < this->markedLightDefs.num; *v11 = v10 )
              {
                v9 = this->markedLightDefs.list;
                v10 = v9[v4 + 1];
                v11 = &v9[v4++];
              }
            }
          }
          break;
        }
        ++v4;
        ++v5;
        if ( v4 >= num )
          goto LABEL_15;
      }
      ++tr.pc.c_lightPushesSuppressed;
    }
  }
  else if ( lightHandle >= 0 )
  {
    idRenderWorldLocal::PushLightDef(this, lightHandle);
  }
}

// FUNC: public: virtual int __thiscall idRenderWorldLocal::AddEntityDef(struct renderEntity_s const *)
int __thiscall idRenderWorldLocal::AddEntityDef(idRenderWorldLocal *this, const renderEntity_s *re)
{
  int num; // ecx
  int v4; // eax
  idRenderEntityLocal **list; // edx
  int v6; // edi
  int granularity; // eax
  bool v8; // cc
  int i; // eax
  int size; // eax
  int v11; // ebx
  int v12; // ecx
  idRenderEntityLocal **v13; // edi
  int j; // eax

  num = this->entityDefs.num;
  v4 = 0;
  if ( num <= 0 )
    goto LABEL_7;
  list = this->entityDefs.list;
  while ( *list )
  {
    ++v4;
    ++list;
    if ( v4 >= num )
      goto LABEL_7;
  }
  v6 = v4;
  if ( v4 == -1 )
  {
LABEL_7:
    if ( !this->entityDefs.list )
    {
      granularity = this->entityDefs.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->entityDefs.size )
        {
          v8 = granularity < this->entityDefs.num;
          this->entityDefs.size = granularity;
          if ( v8 )
            this->entityDefs.num = granularity;
          this->entityDefs.list = (idRenderEntityLocal **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->entityDefs.num; ++i )
            this->entityDefs.list[i] = *(idRenderEntityLocal **)(4 * i);
        }
      }
      else
      {
        this->entityDefs.list = 0;
        this->entityDefs.num = 0;
        this->entityDefs.size = 0;
      }
    }
    size = this->entityDefs.size;
    v11 = this->entityDefs.num;
    if ( v11 == size )
    {
      if ( !this->entityDefs.granularity )
        this->entityDefs.granularity = 16;
      v12 = size + this->entityDefs.granularity - (size + this->entityDefs.granularity) % this->entityDefs.granularity;
      if ( v12 > 0 )
      {
        if ( v12 != this->entityDefs.size )
        {
          v13 = this->entityDefs.list;
          this->entityDefs.size = v12;
          if ( v12 < v11 )
            this->entityDefs.num = v12;
          this->entityDefs.list = (idRenderEntityLocal **)Memory::Allocate(4 * v12);
          for ( j = 0; j < this->entityDefs.num; ++j )
            this->entityDefs.list[j] = v13[j];
          if ( v13 )
            Memory::Free(v13);
        }
      }
      else
      {
        if ( this->entityDefs.list )
          Memory::Free(this->entityDefs.list);
        this->entityDefs.list = 0;
        this->entityDefs.num = 0;
        this->entityDefs.size = 0;
      }
    }
    this->entityDefs.list[this->entityDefs.num++] = 0;
    v6 = this->entityDefs.num - 1;
  }
  this->UpdateEntityDef(this, v6, re);
  return v6;
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::UpdateEntityDef(int,struct renderEntity_s const *)
void __thiscall idRenderWorldLocal::UpdateEntityDef(
        idRenderWorldLocal *this,
        unsigned int entityHandle,
        const renderEntity_s *re)
{
  const renderEntity_s *v4; // esi
  int v5; // edi
  int v6; // ebx
  const char *v7; // eax
  int granularity; // eax
  bool v9; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v13; // ecx
  idRenderEntityLocal **list; // edi
  int j; // eax
  idRenderEntityLocal *v16; // ebx
  bool v17; // dl
  bool v18; // cl
  idRenderEntityLocal *v19; // eax
  idRenderEntityLocal *v20; // eax

  if ( !r_skipUpdates.internalVar->integerValue )
  {
    v4 = re;
    ++tr.pc.c_entityUpdates;
    if ( !re->hModel && !re->callback )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "idRenderWorld::UpdateEntityDef: NULL hModel");
    v5 = entityHandle;
    if ( entityHandle >= 0x2711 )
    {
      v6 = *(_DWORD *)common.type;
      v7 = re->hModel->Name(re->hModel);
      (*(void (**)(netadrtype_t, const char *, ...))(v6 + 152))(
        common.type,
        "idRenderWorld::UpdateEntityDef: index %i greater than %d for render model %s",
        entityHandle,
        10000,
        v7);
    }
    if ( (signed int)entityHandle >= this->entityDefs.num )
    {
      do
      {
        if ( !this->entityDefs.list )
        {
          granularity = this->entityDefs.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->entityDefs.size )
            {
              v9 = granularity < this->entityDefs.num;
              this->entityDefs.size = granularity;
              if ( v9 )
                this->entityDefs.num = granularity;
              this->entityDefs.list = (idRenderEntityLocal **)Memory::Allocate(4 * granularity);
              for ( i = 0; i < this->entityDefs.num; ++i )
                this->entityDefs.list[i] = *(idRenderEntityLocal **)(4 * i);
            }
          }
          else
          {
            this->entityDefs.list = 0;
            this->entityDefs.num = 0;
            this->entityDefs.size = 0;
          }
        }
        num = this->entityDefs.num;
        size = this->entityDefs.size;
        if ( num == size )
        {
          if ( !this->entityDefs.granularity )
            this->entityDefs.granularity = 16;
          v13 = size
              + this->entityDefs.granularity
              - (size + this->entityDefs.granularity) % this->entityDefs.granularity;
          if ( v13 > 0 )
          {
            if ( v13 != this->entityDefs.size )
            {
              list = this->entityDefs.list;
              this->entityDefs.size = v13;
              if ( v13 < num )
                this->entityDefs.num = v13;
              this->entityDefs.list = (idRenderEntityLocal **)Memory::Allocate(4 * v13);
              for ( j = 0; j < this->entityDefs.num; ++j )
                this->entityDefs.list[j] = list[j];
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( this->entityDefs.list )
              Memory::Free(this->entityDefs.list);
            this->entityDefs.list = 0;
            this->entityDefs.num = 0;
            this->entityDefs.size = 0;
          }
          v5 = entityHandle;
        }
        this->entityDefs.list[this->entityDefs.num++] = 0;
      }
      while ( v5 >= this->entityDefs.num );
    }
    v16 = this->entityDefs.list[v5];
    if ( v16 )
    {
      if ( !re->forceUpdate )
      {
        if ( !re->joints && !re->callbackData && !v16->dynamicModel )
        {
          if ( !memcmp(re, &v16->parms, 0xE0u) )
            return;
          v4 = re;
          v5 = entityHandle;
        }
        if ( v4->callback )
        {
          v17 = v4->axis.mat[0].x == v16->parms.axis.mat[0].x
             && v4->axis.mat[0].y == v16->parms.axis.mat[0].y
             && v4->axis.mat[0].z == v16->parms.axis.mat[0].z
             && v4->axis.mat[1].x == v16->parms.axis.mat[1].x
             && v4->axis.mat[1].y == v16->parms.axis.mat[1].y
             && v4->axis.mat[1].z == v16->parms.axis.mat[1].z
             && v4->axis.mat[2].x == v16->parms.axis.mat[2].x
             && v4->axis.mat[2].y == v16->parms.axis.mat[2].y
             && v4->axis.mat[2].z == v16->parms.axis.mat[2].z;
          v18 = v4->origin.x == v16->parms.origin.x
             && v4->origin.y == v16->parms.origin.y
             && v4->origin.z == v16->parms.origin.z;
          if ( v4->bounds.b[0].x == v16->referenceBounds.b[0].x
            && v4->bounds.b[0].y == v16->referenceBounds.b[0].y
            && v4->bounds.b[0].z == v16->referenceBounds.b[0].z
            && v4->bounds.b[1].x == v16->referenceBounds.b[1].x
            && v4->bounds.b[1].y == v16->referenceBounds.b[1].y
            && v4->bounds.b[1].z == v16->referenceBounds.b[1].z
            && v18
            && v17 )
          {
            if ( v4->hModel == v16->parms.hModel )
            {
              ++c_callbackUpdate;
              R_ClearEntityDefDynamicModel(v16);
              renderEntity_s::operator=(&v16->parms.hModel, (int)v4);
              return;
            }
            v5 = entityHandle;
          }
        }
      }
      if ( v16->parms.hModel == v4->hModel )
        R_FreeEntityDefDerivedData(v16, 1, 1, 0);
      else
        R_FreeEntityDefDerivedData(v16, 0, 0, 0);
    }
    else
    {
      v19 = (idRenderEntityLocal *)Memory::Allocate(0x184u);
      if ( v19 )
        idRenderEntityLocal::idRenderEntityLocal(v19);
      else
        v20 = 0;
      this->entityDefs.list[v5] = v20;
      v16 = v20;
      v20->world = this;
      v20->index = v5;
    }
    renderEntity_s::operator=(&v16->parms.hModel, (int)v4);
    R_AxisToModelMatrix(&v16->parms.axis, &v16->parms.origin, v16->modelMatrix);
    v16->lastModifiedFrameNum = tr.frameCount;
    if ( session->writeDemo )
    {
      idRenderWorldLocal::WriteUpdateEntityDef(this, v5);
      v16->writeToDemo = 1;
    }
    if ( !r_useEntityCallbacks.internalVar->integerValue )
    {
      if ( v16->parms.callback )
        R_IssueEntityDefCallback(v16);
    }
    idRenderWorldLocal::MarkEntityDef(this, v5);
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::FreeEntityDef(int)
void __thiscall idRenderWorldLocal::FreeEntityDef(idRenderWorldLocal *this, int entityHandle)
{
  int num; // eax
  idRenderEntityLocal *v4; // esi

  if ( entityHandle < 0 || (num = this->entityDefs.num, entityHandle >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::FreeEntityDef: handle %i >= %i\n",
      entityHandle,
      this->entityDefs.num);
  }
  else
  {
    v4 = this->entityDefs.list[entityHandle];
    if ( v4 )
    {
      R_FreeEntityDefDerivedData(v4, 0, 0, 0);
      if ( session->writeDemo )
      {
        if ( v4->archived )
        {
          idRenderWorldLocal::WriteFreeEntityDef(this, entityHandle);
          v4->writeToDemo = 0;
          v4->archived = 0;
        }
      }
      v4->parms.gui[0] = 0;
      v4->parms.gui[1] = 0;
      v4->parms.gui[2] = 0;
      ((void (__thiscall *)(idRenderEntityLocal *, int))v4->~idRenderEntityLocal)(v4, 1);
      this->entityDefs.list[entityHandle] = 0;
      idRenderWorldLocal::MarkEntityDef(this, -1 - entityHandle);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorld::FreeEntityDef: handle %i [0, %i] is NULL\n",
        entityHandle,
        num);
    }
  }
}

// FUNC: public: virtual int __thiscall idRenderWorldLocal::AddLightDef(struct renderLight_s const *)
int __thiscall idRenderWorldLocal::AddLightDef(idRenderWorldLocal *this, const renderLight_s *rlight)
{
  int num; // ecx
  int v4; // eax
  idRenderLightLocal **list; // edx
  int v6; // edi
  int granularity; // eax
  bool v8; // cc
  int i; // eax
  int size; // eax
  int v11; // ebx
  int v12; // ecx
  idRenderLightLocal **v13; // edi
  int j; // eax

  num = this->lightDefs.num;
  v4 = 0;
  if ( num <= 0 )
    goto LABEL_7;
  list = this->lightDefs.list;
  while ( *list )
  {
    ++v4;
    ++list;
    if ( v4 >= num )
      goto LABEL_7;
  }
  v6 = v4;
  if ( v4 == -1 )
  {
LABEL_7:
    if ( !this->lightDefs.list )
    {
      granularity = this->lightDefs.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->lightDefs.size )
        {
          v8 = granularity < this->lightDefs.num;
          this->lightDefs.size = granularity;
          if ( v8 )
            this->lightDefs.num = granularity;
          this->lightDefs.list = (idRenderLightLocal **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->lightDefs.num; ++i )
            this->lightDefs.list[i] = *(idRenderLightLocal **)(4 * i);
        }
      }
      else
      {
        this->lightDefs.list = 0;
        this->lightDefs.num = 0;
        this->lightDefs.size = 0;
      }
    }
    size = this->lightDefs.size;
    v11 = this->lightDefs.num;
    if ( v11 == size )
    {
      if ( !this->lightDefs.granularity )
        this->lightDefs.granularity = 16;
      v12 = size + this->lightDefs.granularity - (size + this->lightDefs.granularity) % this->lightDefs.granularity;
      if ( v12 > 0 )
      {
        if ( v12 != this->lightDefs.size )
        {
          v13 = this->lightDefs.list;
          this->lightDefs.size = v12;
          if ( v12 < v11 )
            this->lightDefs.num = v12;
          this->lightDefs.list = (idRenderLightLocal **)Memory::Allocate(4 * v12);
          for ( j = 0; j < this->lightDefs.num; ++j )
            this->lightDefs.list[j] = v13[j];
          if ( v13 )
            Memory::Free(v13);
        }
      }
      else
      {
        if ( this->lightDefs.list )
          Memory::Free(this->lightDefs.list);
        this->lightDefs.list = 0;
        this->lightDefs.num = 0;
        this->lightDefs.size = 0;
      }
    }
    this->lightDefs.list[this->lightDefs.num++] = 0;
    v6 = this->lightDefs.num - 1;
  }
  this->UpdateLightDef(this, v6, rlight);
  return v6;
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::UpdateLightDef(int,struct renderLight_s const *)
void __thiscall idRenderWorldLocal::UpdateLightDef(
        idRenderWorldLocal *this,
        unsigned int lightHandle,
        const renderLight_s *rlight)
{
  unsigned int v4; // edi
  int granularity; // eax
  bool v6; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v10; // ecx
  idRenderLightLocal **list; // edi
  int j; // eax
  idRenderLightLocal *v13; // edi
  char v14; // bl
  idRenderLightLocal_vtbl *v15; // eax
  idRenderLightLocal *v16; // eax
  idRenderLightLocal *v17; // eax

  if ( !r_skipUpdates.internalVar->integerValue )
  {
    v4 = lightHandle;
    ++tr.pc.c_lightUpdates;
    if ( lightHandle >= 0x2711 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "idRenderWorld::UpdateLightDef: index = %i",
        lightHandle);
    for ( ; (signed int)lightHandle >= this->lightDefs.num; ++this->lightDefs.num )
    {
      if ( !this->lightDefs.list )
      {
        granularity = this->lightDefs.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->lightDefs.size )
          {
            v6 = granularity < this->lightDefs.num;
            this->lightDefs.size = granularity;
            if ( v6 )
              this->lightDefs.num = granularity;
            this->lightDefs.list = (idRenderLightLocal **)Memory::Allocate(4 * granularity);
            for ( i = 0; i < this->lightDefs.num; ++i )
              this->lightDefs.list[i] = *(idRenderLightLocal **)(4 * i);
          }
        }
        else
        {
          this->lightDefs.list = 0;
          this->lightDefs.num = 0;
          this->lightDefs.size = 0;
        }
      }
      num = this->lightDefs.num;
      size = this->lightDefs.size;
      if ( num == size )
      {
        if ( !this->lightDefs.granularity )
          this->lightDefs.granularity = 16;
        v10 = size + this->lightDefs.granularity - (size + this->lightDefs.granularity) % this->lightDefs.granularity;
        if ( v10 > 0 )
        {
          if ( v10 != this->lightDefs.size )
          {
            list = this->lightDefs.list;
            this->lightDefs.size = v10;
            if ( v10 < num )
              this->lightDefs.num = v10;
            this->lightDefs.list = (idRenderLightLocal **)Memory::Allocate(4 * v10);
            for ( j = 0; j < this->lightDefs.num; ++j )
              this->lightDefs.list[j] = list[j];
            if ( list )
              Memory::Free(list);
          }
        }
        else
        {
          if ( this->lightDefs.list )
            Memory::Free(this->lightDefs.list);
          this->lightDefs.list = 0;
          this->lightDefs.num = 0;
          this->lightDefs.size = 0;
        }
      }
      v4 = lightHandle;
      this->lightDefs.list[this->lightDefs.num] = 0;
    }
    v13 = this->lightDefs.list[v4];
    v14 = 0;
    if ( v13 )
    {
      if ( rlight->axis.mat[0].x == v13->parms.axis.mat[0].x
        && rlight->axis.mat[0].y == v13->parms.axis.mat[0].y
        && rlight->axis.mat[0].z == v13->parms.axis.mat[0].z
        && rlight->axis.mat[1].x == v13->parms.axis.mat[1].x
        && rlight->axis.mat[1].y == v13->parms.axis.mat[1].y
        && rlight->axis.mat[1].z == v13->parms.axis.mat[1].z
        && rlight->axis.mat[2].x == v13->parms.axis.mat[2].x
        && rlight->axis.mat[2].y == v13->parms.axis.mat[2].y
        && rlight->axis.mat[2].z == v13->parms.axis.mat[2].z
        && rlight->end.x == v13->parms.end.x
        && rlight->end.y == v13->parms.end.y
        && rlight->end.z == v13->parms.end.z
        && rlight->lightCenter.x == v13->parms.lightCenter.x
        && rlight->lightCenter.y == v13->parms.lightCenter.y
        && rlight->lightCenter.z == v13->parms.lightCenter.z
        && rlight->lightRadius.x == v13->parms.lightRadius.x
        && rlight->lightRadius.y == v13->parms.lightRadius.y
        && rlight->lightRadius.z == v13->parms.lightRadius.z
        && rlight->noShadows == v13->parms.noShadows
        && rlight->origin.x == v13->parms.origin.x
        && rlight->origin.y == v13->parms.origin.y
        && rlight->origin.z == v13->parms.origin.z
        && rlight->noDynamicShadows == v13->parms.noDynamicShadows
        && rlight->origin.x == v13->parms.origin.x
        && rlight->origin.y == v13->parms.origin.y
        && rlight->origin.z == v13->parms.origin.z
        && rlight->parallel == v13->parms.parallel
        && rlight->pointLight == v13->parms.pointLight
        && rlight->right.x == v13->parms.right.x
        && rlight->right.y == v13->parms.right.y
        && rlight->right.z == v13->parms.right.z
        && rlight->start.x == v13->parms.start.x
        && rlight->start.y == v13->parms.start.y
        && rlight->start.z == v13->parms.start.z
        && rlight->target.x == v13->parms.target.x
        && rlight->target.y == v13->parms.target.y
        && rlight->target.z == v13->parms.target.z
        && rlight->up.x == v13->parms.up.x
        && rlight->up.y == v13->parms.up.y
        && rlight->up.z == v13->parms.up.z
        && rlight->shader == v13->lightShader
        && rlight->prelightModel == v13->parms.prelightModel )
      {
        v14 = 1;
      }
      else
      {
        v15 = v13->__vftable;
        v13->lightHasMoved = 1;
        v15->FreeLightDefDerivedData(v13, 0);
      }
    }
    else
    {
      v16 = (idRenderLightLocal *)Memory::Allocate(0x494u);
      if ( v16 )
        idRenderLightLocal::idRenderLightLocal(v16);
      else
        v17 = 0;
      this->lightDefs.list[lightHandle] = v17;
      v13 = v17;
      v17->world = this;
      v17->index = lightHandle;
    }
    renderLight_s::operator=(&v13->parms, (int)rlight);
    v13->lastModifiedFrameNum = tr.frameCount;
    if ( session->writeDemo )
    {
      idRenderWorldLocal::WriteUpdateLightDef(this, lightHandle);
      v13->writeToDemo = 1;
    }
    if ( v13->lightHasMoved )
      v13->parms.prelightModel = 0;
    if ( !v14 )
      idRenderWorldLocal::MarkLightDef(this, lightHandle);
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::FreeLightDef(int)
void __userpurge idRenderWorldLocal::FreeLightDef(idRenderWorldLocal *this@<ecx>, int a2@<esi>, int lightHandle)
{
  int num; // eax
  idRenderLightLocal *v5; // esi

  if ( lightHandle < 0 || (num = this->lightDefs.num, lightHandle >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::FreeLightDef: invalid handle %i >= %i\n",
      lightHandle,
      this->lightDefs.num);
  }
  else
  {
    v5 = this->lightDefs.list[lightHandle];
    if ( v5 )
    {
      ((void (__thiscall *)(idRenderLightLocal *, _DWORD, int))v5->FreeLightDefDerivedData)(v5, 0, a2);
      if ( session->writeDemo )
      {
        if ( v5->archived )
        {
          idRenderWorldLocal::WriteFreeLightDef(this, lightHandle);
          v5->writeToDemo = 0;
          v5->archived = 0;
        }
      }
      ((void (__thiscall *)(idRenderLightLocal *, int))v5->~idRenderLightLocal)(v5, 1);
      this->lightDefs.list[lightHandle] = 0;
      idRenderWorldLocal::MarkLightDef(this, -1 - lightHandle);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorld::FreeLightDef: handle %i [0, %i] is NULL\n",
        lightHandle,
        num);
    }
  }
}

// FUNC: public: virtual int __thiscall idRenderWorldLocal::AddEffectDef(struct renderEffect_s const *,int)
int __thiscall idRenderWorldLocal::AddEffectDef(idRenderWorldLocal *this, const renderEffect_s *reffect, int time)
{
  int num; // ecx
  int v6; // eax
  rvRenderEffectLocal **list; // edx
  int v8; // edi
  int granularity; // eax
  bool v10; // cc
  int i; // eax
  int size; // eax
  int v13; // ebx
  int v14; // ecx
  rvRenderEffectLocal **v15; // edi
  int j; // eax

  if ( !bse_enabled.internalVar->integerValue )
    return -1;
  num = this->effectDefs.num;
  v6 = 0;
  if ( num <= 0 )
    goto LABEL_9;
  list = this->effectDefs.list;
  while ( *list )
  {
    ++v6;
    ++list;
    if ( v6 >= num )
      goto LABEL_9;
  }
  v8 = v6;
  if ( v6 == -1 )
  {
LABEL_9:
    if ( !this->effectDefs.list )
    {
      granularity = this->effectDefs.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->effectDefs.size )
        {
          v10 = granularity < this->effectDefs.num;
          this->effectDefs.size = granularity;
          if ( v10 )
            this->effectDefs.num = granularity;
          this->effectDefs.list = (rvRenderEffectLocal **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->effectDefs.num; ++i )
            this->effectDefs.list[i] = *(rvRenderEffectLocal **)(4 * i);
        }
      }
      else
      {
        this->effectDefs.list = 0;
        this->effectDefs.num = 0;
        this->effectDefs.size = 0;
      }
    }
    size = this->effectDefs.size;
    v13 = this->effectDefs.num;
    if ( v13 == size )
    {
      if ( !this->effectDefs.granularity )
        this->effectDefs.granularity = 16;
      v14 = size + this->effectDefs.granularity - (size + this->effectDefs.granularity) % this->effectDefs.granularity;
      if ( v14 > 0 )
      {
        if ( v14 != this->effectDefs.size )
        {
          v15 = this->effectDefs.list;
          this->effectDefs.size = v14;
          if ( v14 < v13 )
            this->effectDefs.num = v14;
          this->effectDefs.list = (rvRenderEffectLocal **)Memory::Allocate(4 * v14);
          for ( j = 0; j < this->effectDefs.num; ++j )
            this->effectDefs.list[j] = v15[j];
          if ( v15 )
            Memory::Free(v15);
        }
      }
      else
      {
        if ( this->effectDefs.list )
          Memory::Free(this->effectDefs.list);
        this->effectDefs.list = 0;
        this->effectDefs.num = 0;
        this->effectDefs.size = 0;
      }
    }
    this->effectDefs.list[this->effectDefs.num++] = 0;
    v8 = this->effectDefs.num - 1;
  }
  if ( !this->UpdateEffectDef(this, v8, reffect, time) )
    return v8;
  this->FreeEffectDef(this, v8);
  return -1;
}

// FUNC: public: void __thiscall idRenderWorldLocal::PushEffectDef(int)
void __thiscall idRenderWorldLocal::PushEffectDef(idRenderWorldLocal *this, int effectHandle)
{
  int num; // edx
  rvRenderEffectLocal *v3; // edi
  double v4; // st7
  double y; // st6
  double v6; // st6
  double z; // st5
  double v8; // rt0
  double v9; // st6
  double v10; // st5
  double v11; // st4
  double v12; // st7
  double v13; // st6
  double v14; // st5
  double v15; // st7
  float v16; // edx
  float v17; // edx
  float x; // eax
  float v19; // ecx
  float v20; // edx
  idRenderWorldLocal *world; // ecx
  float v22; // [esp+4h] [ebp-54h]
  float v23; // [esp+10h] [ebp-48h]
  float v24; // [esp+14h] [ebp-44h]
  float v25; // [esp+18h] [ebp-40h]
  float v26; // [esp+18h] [ebp-40h]
  float v27; // [esp+18h] [ebp-40h]
  idBox box; // [esp+1Ch] [ebp-3Ch] BYREF

  if ( effectHandle < 0 || (num = this->effectDefs.num, effectHandle >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::PushEffectDef: invalid handle %i >= %i\n",
      effectHandle,
      this->effectDefs.num);
  }
  else
  {
    v3 = this->effectDefs.list[effectHandle];
    if ( v3 )
    {
      R_AxisToModelMatrix(&v3->parms.axis, &v3->parms.origin, v3->modelMatrix);
      v3->lastModifiedFrameNum = tr.frameCount;
      ++tr.viewCount;
      v4 = v3->referenceBounds.b[1].x + v3->referenceBounds.b[0].x;
      y = v3->referenceBounds.b[1].y;
      box.axis.mat[0].x = v3->parms.axis.mat[0].x;
      v6 = y + v3->referenceBounds.b[0].y;
      z = v3->referenceBounds.b[1].z;
      box.axis.mat[1].x = v3->parms.axis.mat[1].x;
      v25 = z + v3->referenceBounds.b[0].z;
      v8 = v6;
      v22 = v4 * 0.5;
      v9 = v25 * 0.5;
      v10 = v3->referenceBounds.b[1].x - v22;
      v11 = v3->referenceBounds.b[1].y - v8 * 0.5;
      v26 = v3->referenceBounds.b[1].z - v9;
      box.extents.z = v26;
      box.extents.x = v10;
      box.axis.mat[0].y = v3->parms.axis.mat[0].y;
      box.extents.y = v11;
      v23 = v9 * v3->parms.axis.mat[2].x + v8 * 0.5 * v3->parms.axis.mat[1].x + v22 * v3->parms.axis.mat[0].x;
      v24 = v9 * v3->parms.axis.mat[2].y + v8 * 0.5 * v3->parms.axis.mat[1].y + v22 * v3->parms.axis.mat[0].y;
      v12 = v9 * v3->parms.axis.mat[2].z + v8 * 0.5 * v3->parms.axis.mat[1].z + v22 * v3->parms.axis.mat[0].z;
      v13 = v23 + v3->parms.origin.x;
      v14 = v12;
      v15 = v24 + v3->parms.origin.y;
      v27 = v14 + v3->parms.origin.z;
      box.center.z = v27;
      v16 = v3->parms.axis.mat[0].z;
      box.center.x = v13;
      box.axis.mat[0].z = v16;
      box.center.y = v15;
      v17 = v3->parms.axis.mat[1].z;
      x = v3->parms.axis.mat[2].x;
      box.axis.mat[1].y = v3->parms.axis.mat[1].y;
      v19 = v3->parms.axis.mat[2].y;
      box.axis.mat[1].z = v17;
      v20 = v3->parms.axis.mat[2].z;
      box.axis.mat[2].y = v19;
      world = v3->world;
      box.axis.mat[2].x = x;
      box.axis.mat[2].z = v20;
      if ( world->areaNodes )
      {
        idRenderWorldLocal::PushPolytopeIntoTree_r(world, 0, 0, v3, &box, 0, 0, 0);
        ++tr.pc.c_numVolumePushes;
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorld::PushEffectDef: handle %i [0, %i] is NULL\n",
        effectHandle,
        num);
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::ProjectDecalOntoWorld(class idFixedWinding const &,class idVec3 const &,bool,float,class idMaterial const *,int)
void __thiscall idRenderWorldLocal::ProjectDecalOntoWorld(
        idRenderWorldLocal *this,
        const idFixedWinding *winding,
        const idVec3 *projectionOrigin,
        bool parallel,
        float fadeDepth,
        const idMaterial *material,
        int startTime)
{
  idRenderWorldLocal *v7; // esi
  int v8; // edi
  int v9; // ecx
  idRenderEntityLocal *entity; // esi
  idRenderModel *hModel; // edi
  const idMaterial *customShader; // eax
  const idBounds *v13; // eax
  const areaReference_s *ref; // [esp+14h] [ebp-224h]
  int i; // [esp+18h] [ebp-220h]
  const areaReference_s *p_entityRefs; // [esp+20h] [ebp-218h]
  int numAreas; // [esp+24h] [ebp-214h]
  idBounds bounds; // [esp+28h] [ebp-210h] BYREF
  int areas[10]; // [esp+40h] [ebp-1F8h] BYREF
  idBounds v21; // [esp+68h] [ebp-1D0h] BYREF
  decalProjectionInfo_s info; // [esp+80h] [ebp-1B8h] BYREF
  decalProjectionInfo_s localInfo; // [esp+15Ch] [ebp-DCh] BYREF

  v7 = this;
  if ( idRenderModelDecal::CreateProjectionInfo(
         &info,
         winding,
         projectionOrigin,
         parallel,
         fadeDepth,
         material,
         startTime) )
  {
    v8 = v7->BoundsInAreas(v7, &info.projectionBounds, areas, 10);
    v9 = 0;
    numAreas = v8;
    for ( i = 0; v9 < v8; i = v9 )
    {
      p_entityRefs = &v7->portalAreas[areas[v9]].entityRefs;
      ref = p_entityRefs->areaNext;
      if ( p_entityRefs->areaNext != p_entityRefs )
      {
        do
        {
          entity = ref->entity;
          hModel = entity->parms.hModel;
          if ( hModel )
          {
            if ( hModel->IsDynamicModel(entity->parms.hModel) == DM_STATIC && !entity->parms.callback )
            {
              customShader = entity->parms.customShader;
              if ( !customShader || customShader->allowOverlays )
              {
                v13 = hModel->Bounds(hModel, &v21, &entity->parms);
                idBounds::FromTransformedBounds(&bounds, v13, &entity->parms.origin, &entity->parms.axis);
                if ( bounds.b[1].x >= (double)info.projectionBounds.b[0].x
                  && bounds.b[1].y >= (double)info.projectionBounds.b[0].y
                  && bounds.b[1].z >= (double)info.projectionBounds.b[0].z
                  && bounds.b[0].x <= (double)info.projectionBounds.b[1].x
                  && bounds.b[0].y <= (double)info.projectionBounds.b[1].y
                  && bounds.b[0].z <= (double)info.projectionBounds.b[1].z )
                {
                  idRenderModelDecal::GlobalProjectionInfoToLocal(
                    &localInfo,
                    &info,
                    &entity->parms.origin,
                    &entity->parms.axis);
                  localInfo.force = entity->parms.customShader != 0;
                  if ( !entity->decals )
                    entity->decals = idRenderModelDecal::Alloc();
                  idRenderModelDecal::CreateDecal(entity->decals, hModel, COERCE_FLOAT(&localInfo));
                }
              }
            }
          }
          ref = ref->areaNext;
        }
        while ( ref != p_entityRefs );
        v8 = numAreas;
        v9 = i;
        v7 = this;
      }
      ++v9;
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::SetRenderView(struct renderView_s const *)
void __thiscall idRenderWorldLocal::SetRenderView(idRenderWorldLocal *this, const renderView_s *renderView)
{
  renderView_s::operator=(&tr.primaryRenderView.viewID, (int)renderView);
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::RenderScene(struct renderView_s const *,int)
void __thiscall idRenderWorldLocal::RenderScene(
        idRenderWorldLocal *this,
        const renderView_s *renderView,
        int renderFlags)
{
  viewDef_s *v4; // esi
  __int16 v5; // cx
  bool v6; // zf
  double time; // st7
  double v8; // st7
  int v9; // eax
  int num; // ecx
  int v11; // ebp
  idRenderEntityLocal *v12; // eax
  int count; // [esp+18h] [ebp-9Ch]
  int startTime; // [esp+1Ch] [ebp-98h]
  renderView_s copy; // [esp+20h] [ebp-94h] BYREF
  int v16; // [esp+B0h] [ebp-4h]

  if ( glConfig.isInitialized )
  {
    renderView_s::operator=(&copy, (int)renderView);
    if ( !r_skipFrontEnd.internalVar->integerValue )
    {
      if ( renderView->fov_x <= 0.0 || renderView->fov_y <= 0.0 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
          common.type,
          "idRenderWorld::RenderScene: bad FOVs: %f, %f",
          renderView->fov_x,
          renderView->fov_y);
      idGuiModel::EmitFullScreen(tr.guiModel);
      idGuiModel::Clear(tr.guiModel);
      startTime = Sys_Milliseconds();
      v4 = (viewDef_s *)R_ClearedFrameAlloc(636);
      renderView_s::operator=(v4, (int)renderView);
      if ( tr.takingScreenshot )
        v4->renderView.forceUpdate = 1;
      v4->renderFlags = renderFlags;
      idRenderSystemLocal::RenderViewToViewport(&tr, &v4->renderView, &v4->viewport);
      v5 = v4->viewport.y2 - v4->viewport.y1;
      v4->scissor.x2 = v4->viewport.x2 - v4->viewport.x1;
      v4->scissor.y2 = v5;
      v6 = (_S8_31 & 1) == 0;
      v4->scissor.x1 = 0;
      v4->scissor.y1 = 0;
      v4->isSubview = 0;
      v4->initialViewAreaOrigin = renderView->vieworg;
      time = (double)v4->renderView.time;
      v4->renderWorld = this;
      v8 = time * 0.001;
      v4->floatTime = v8;
      tr.frameShaderTime = v8;
      if ( v6 )
      {
        _S8_31 |= 1u;
        v16 = 0;
        v9 = Sys_Milliseconds();
        v16 = -1;
      }
      else
      {
        v9 = iLastTime;
      }
      iLastTime = startTime;
      tr.deltaTime = (double)(startTime - v9) * 0.001;
      v4->isMirror = (v4->renderView.viewaxis.mat[2].y * v4->renderView.viewaxis.mat[1].x
                    - v4->renderView.viewaxis.mat[1].y * v4->renderView.viewaxis.mat[2].x)
                   * v4->renderView.viewaxis.mat[0].z
                   + (v4->renderView.viewaxis.mat[1].z * v4->renderView.viewaxis.mat[2].x
                    - v4->renderView.viewaxis.mat[2].z * v4->renderView.viewaxis.mat[1].x)
                   * v4->renderView.viewaxis.mat[0].y
                   + (v4->renderView.viewaxis.mat[1].y * v4->renderView.viewaxis.mat[2].z
                    - v4->renderView.viewaxis.mat[1].z * v4->renderView.viewaxis.mat[2].y)
                   * v4->renderView.viewaxis.mat[0].x <= 0.0;
      if ( r_lockSurfaces.internalVar->integerValue )
      {
        R_LockSurfaceScene(v4);
      }
      else
      {
        tr.primaryWorld = this;
        renderView_s::operator=(&tr.primaryRenderView.viewID, (int)renderView);
        tr.primaryView = v4;
        num = this->entityDefs.num;
        v11 = 0;
        for ( count = num; v11 < num; ++v11 )
        {
          v12 = this->entityDefs.list[v11];
          if ( v12 )
          {
            R_FreeEntityDefFadedDecals(v12, renderView->time);
            num = count;
          }
        }
        R_RenderView(v4);
        if ( session->writeDemo )
        {
          if ( (renderFlags & 0x40) != 0 )
            idRenderWorldLocal::WriteRenderView(this, 2, renderView);
          else
            idRenderWorldLocal::WriteRenderView(this, 1, renderView);
        }
        tr.pc.frontEndMsec += Sys_Milliseconds() - startTime;
        idGuiModel::Clear(tr.guiModel);
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugLine(class idVec4 const &,class idVec3 const &,class idVec3 const &,int,bool)
void __thiscall idRenderWorldLocal::DebugLine(
        idRenderWorldLocal *this,
        const idVec4 *color,
        const idVec3 *start,
        const idVec3 *end,
        int lifeTime,
        bool depthTest)
{
  float x; // ebx
  int v8; // edi
  idList<debugLine_s> *p_debugLines; // esi
  int size; // ecx
  int v11; // eax
  float line_4; // [esp+8h] [ebp-2Ch]
  float line_8; // [esp+Ch] [ebp-28h]
  float line_12; // [esp+10h] [ebp-24h]
  idVec3 line_16; // [esp+14h] [ebp-20h]
  idVec3 line_28; // [esp+20h] [ebp-14h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    x = color->x;
    line_8 = color->z;
    line_4 = color->y;
    line_12 = color->w;
    line_16 = *start;
    v8 = lifeTime + this->debugLineTime;
    p_debugLines = &this->debugLines;
    line_28 = *end;
    if ( !p_debugLines->list )
      idList<debugLine_s>::Resize(p_debugLines, p_debugLines->granularity);
    size = p_debugLines->size;
    if ( p_debugLines->num == size )
    {
      if ( !p_debugLines->granularity )
        p_debugLines->granularity = 16;
      idList<debugLine_s>::Resize(
        p_debugLines,
        p_debugLines->granularity + size - (p_debugLines->granularity + size) % p_debugLines->granularity);
    }
    v11 = (int)&p_debugLines->list[p_debugLines->num];
    *(float *)v11 = x;
    *(float *)(v11 + 4) = line_4;
    *(float *)(v11 + 8) = line_8;
    *(float *)(v11 + 12) = line_12;
    *(idVec3 *)(v11 + 16) = line_16;
    *(idVec3 *)(v11 + 28) = line_28;
    *(_DWORD *)(v11 + 44) = v8;
    *(_BYTE *)(v11 + 40) = depthTest;
    ++p_debugLines->num;
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugSphere(class idVec4 const &,class idSphere const &,int,bool)
void __thiscall idRenderWorldLocal::DebugSphere(
        idRenderWorldLocal *this,
        const idVec4 *color,
        const idSphere *sphere,
        int lifetime,
        BOOL depthTest)
{
  triangle_s *list; // edx
  bool v7; // zf
  bool v8; // cc
  triangle_s *v9; // eax
  triangle_s *v10; // edi
  int v11; // ebp
  int v12; // edi
  float *p_z; // eax
  float *v14; // ecx
  int v15; // edx
  unsigned int v16; // eax
  int v17; // ecx
  int num; // eax
  int v19; // ebp
  triangle_s *v20; // ebx
  triangle_s *v21; // ecx
  _DWORD *v22; // eax
  int v23; // edi
  int v24; // ebx
  _DWORD *v25; // ecx
  int v26; // edx
  int v27; // edi
  triangle_s *v28; // ecx
  int v29; // edx
  triangle_s *v30; // eax
  double z; // st7
  float *v32; // eax
  double v33; // st7
  double v34; // st6
  double v35; // st7
  triangle_s *v36; // eax
  double v37; // st6
  float *v38; // eax
  double v39; // st6
  double v40; // st5
  float *v41; // eax
  double v42; // st6
  double v43; // st5
  long double v44; // st6
  long double v45; // st6
  long double v46; // st7
  long double v47; // st7
  long double v48; // st7
  long double v49; // st7
  triangle_s *v50; // eax
  triangle_s *v51; // eax
  triangle_s *v52; // ecx
  triangle_s *v53; // eax
  float x; // ebx
  int v55; // eax
  int size; // eax
  triangle_s *v57; // ebp
  triangle_s *v58; // edx
  _DWORD *p_y; // eax
  int v60; // edi
  triangle_s *v61; // ecx
  int v62; // edx
  int v63; // ebp
  int v64; // ebx
  double radius; // st7
  float *v66; // eax
  double v67; // st6
  double v68; // st5
  double v69; // st7
  double v70; // st7
  double v71; // st6
  double v72; // st5
  double v73; // st7
  idRenderWorldLocal_vtbl *v74; // edx
  double v75; // st7
  double v76; // st6
  double v77; // st5
  double v78; // st7
  triangle_s *ptr; // [esp+Ch] [ebp-A0h]
  triangle_s *ptra; // [esp+Ch] [ebp-A0h]
  float ptrb; // [esp+Ch] [ebp-A0h]
  char *ptrc; // [esp+Ch] [ebp-A0h]
  int v83; // [esp+10h] [ebp-9Ch]
  float v84; // [esp+10h] [ebp-9Ch]
  int v85; // [esp+10h] [ebp-9Ch]
  idVec3 b; // [esp+14h] [ebp-98h] BYREF
  idVec3 a; // [esp+20h] [ebp-8Ch] BYREF
  idVec3 c; // [esp+2Ch] [ebp-80h] BYREF
  idList<triangle_s> newObj; // [esp+38h] [ebp-74h]
  float v90; // [esp+48h] [ebp-64h]
  float v91; // [esp+4Ch] [ebp-60h]
  float v92; // [esp+50h] [ebp-5Ch]
  int level; // [esp+54h] [ebp-58h]
  float v94; // [esp+58h] [ebp-54h]
  float v95; // [esp+5Ch] [ebp-50h]
  float v96; // [esp+64h] [ebp-48h]
  float v97; // [esp+68h] [ebp-44h]
  float v98; // [esp+70h] [ebp-3Ch]
  float v99; // [esp+74h] [ebp-38h]
  float v100; // [esp+7Ch] [ebp-30h]
  float v101; // [esp+84h] [ebp-28h]
  float v102; // [esp+88h] [ebp-24h]
  float v103; // [esp+90h] [ebp-1Ch]
  float v104; // [esp+94h] [ebp-18h]
  float v105; // [esp+9Ch] [ebp-10h]
  int v106; // [esp+A8h] [ebp-4h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
  {
    list = 0;
    if ( !this->spherePolys.num )
    {
      newObj.granularity = 16;
      newObj.list = 0;
      newObj.num = 0;
      newObj.size = 0;
      v7 = this->spherePolys.size == 8;
      v106 = 0;
      if ( !v7 )
      {
        v8 = this->spherePolys.num <= 8;
        ptr = this->spherePolys.list;
        this->spherePolys.size = 8;
        if ( !v8 )
          this->spherePolys.num = 8;
        v9 = (triangle_s *)Memory::Allocate(0x120u);
        v10 = v9;
        level = (int)v9;
        LOBYTE(v106) = 1;
        if ( v9 )
          `vector constructor iterator'(v9, 0x24u, 8, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
        else
          v10 = 0;
        v11 = 0;
        v8 = this->spherePolys.num <= 0;
        LOBYTE(v106) = 0;
        this->spherePolys.list = v10;
        if ( !v8 )
        {
          v12 = 0;
          p_z = &ptr->pt[0].z;
          do
          {
            v14 = &this->spherePolys.list[v12].pt[0].z;
            v15 = 3;
            do
            {
              *(v14 - 2) = *(p_z - 2);
              *(v14 - 1) = *(p_z - 1);
              *v14 = *p_z;
              p_z += 3;
              v14 += 3;
              --v15;
            }
            while ( v15 );
            ++v11;
            ++v12;
          }
          while ( v11 < this->spherePolys.num );
        }
        if ( ptr )
          Memory::Free(ptr);
        list = newObj.list;
      }
      this->spherePolys.num = 8;
      v16 = 0;
      do
      {
        v17 = 3;
        do
        {
          this->spherePolys.list->pt[v16 / 0xC].x = octahedron[0][v16 / 0xC][0];
          LODWORD(this->spherePolys.list->pt[v16 / 0xC].y) = dword_102FCEFC[v16 / 4];
          LODWORD(this->spherePolys.list->pt[v16 / 0xC].z) = dword_102FCF00[v16 / 4];
          v16 += 12;
          --v17;
        }
        while ( v17 );
      }
      while ( (int)v16 < 288 );
      v8 = r_debugSphereSubdivision.internalVar->integerValue <= 1;
      level = 1;
      if ( !v8 )
      {
        do
        {
          num = this->spherePolys.num;
          v19 = 4 * num;
          v83 = 4 * num;
          if ( 4 * num > 0 )
          {
            if ( v19 != newObj.size )
            {
              v20 = list;
              ptra = list;
              newObj.size = 4 * num;
              if ( v19 < newObj.num )
                newObj.num = 4 * num;
              v21 = (triangle_s *)Memory::Allocate(144 * num);
              newObj.list = v21;
              if ( newObj.num > 0 )
              {
                v22 = (_DWORD *)&v20->pt[0].z;
                v23 = (char *)v21 - (char *)v20;
                v24 = newObj.num;
                do
                {
                  v25 = (_DWORD *)((char *)v22 + v23);
                  v26 = 3;
                  do
                  {
                    *(v25 - 2) = *(v22 - 2);
                    *(v25 - 1) = *(v22 - 1);
                    *v25 = *v22;
                    v22 += 3;
                    v25 += 3;
                    --v26;
                  }
                  while ( v26 );
                  --v24;
                }
                while ( v24 );
                v20 = ptra;
                v19 = v83;
              }
              if ( v20 )
                Memory::Free(v20);
            }
          }
          else
          {
            if ( list )
              Memory::Free(list);
            newObj.list = 0;
            newObj.size = 0;
          }
          v27 = 0;
          v8 = this->spherePolys.num <= 0;
          newObj.num = v19;
          if ( !v8 )
          {
            v28 = newObj.list;
            v29 = 0;
            do
            {
              v30 = this->spherePolys.list;
              z = v30[v29].pt[2].z;
              v32 = (float *)&v30[v29];
              v33 = z + v32[2];
              v34 = v32[7] + v32[1];
              v104 = *v32 + v32[6];
              v92 = v33 * 0.5;
              v35 = v34 * 0.5;
              v94 = v104 * 0.5;
              a.x = v94;
              a.y = v34 * 0.5;
              a.z = v92;
              v36 = this->spherePolys.list;
              v37 = v36[v29].pt[1].z;
              v38 = (float *)&v36[v29];
              v39 = v37 + v38[2];
              v40 = v38[4] + v38[1];
              v100 = v38[3] + *v38;
              v90 = v39 * 0.5;
              b.z = v90;
              v41 = (float *)&this->spherePolys.list[v29];
              v84 = v40 * 0.5;
              v96 = v100 * 0.5;
              b.x = v96;
              b.y = v84;
              v42 = v41[8] + v41[5];
              v43 = v41[7] + v41[4];
              v102 = v41[3] + v41[6];
              v91 = v42 * 0.5;
              c.z = v91;
              ptrb = v43 * 0.5;
              v98 = v102 * 0.5;
              c.x = v98;
              c.y = ptrb;
              v44 = v94 * v94 + v35 * v35 + v92 * v92;
              if ( v44 != 0.0 )
              {
                v45 = 1.0 / sqrt(v44);
                a.x = v94 * v45;
                a.y = v45 * v35;
                a.z = v45 * v92;
              }
              v46 = v96 * v96 + v84 * v84 + v90 * v90;
              if ( v46 != 0.0 )
              {
                v47 = 1.0 / sqrt(v46);
                b.x = v96 * v47;
                b.y = v84 * v47;
                b.z = v47 * v90;
              }
              v48 = v98 * v98 + ptrb * ptrb + v91 * v91;
              if ( v48 != 0.0 )
              {
                v49 = 1.0 / sqrt(v48);
                c.x = v98 * v49;
                c.y = ptrb * v49;
                c.z = v49 * v91;
              }
              v50 = this->spherePolys.list;
              v28->pt[0].x = v50[v29].pt[0].x;
              v28->pt[0].y = v50[v29].pt[0].y;
              v28->pt[0].z = v50[v29].pt[0].z;
              v28->pt[1] = b;
              v28->pt[2] = a;
              v28[1].pt[0] = b;
              v51 = this->spherePolys.list;
              v28[1].pt[1].x = v51[v29].pt[1].x;
              v28[1].pt[1].y = v51[v29].pt[1].y;
              v28[1].pt[1].z = v51[v29].pt[1].z;
              v28[1].pt[2].x = c.x;
              v28[1].pt[2].y = c.y;
              v52 = v28 + 1;
              v52->pt[2].z = c.z;
              v52[1].pt[0] = a;
              v52[1].pt[1].x = b.x;
              v52[1].pt[1].y = b.y;
              ++v52;
              v52->pt[1].z = b.z;
              v52->pt[2] = c;
              v52[1].pt[0].x = a.x;
              v52[1].pt[0].y = a.y;
              ++v52;
              v52->pt[0].z = a.z;
              v52->pt[1] = c;
              v53 = this->spherePolys.list;
              x = v53[v29].pt[2].x;
              v55 = (int)&v53[v29].pt[2];
              v52->pt[2].x = x;
              v52->pt[2].y = *(float *)(v55 + 4);
              v52->pt[2].z = *(float *)(v55 + 8);
              ++v27;
              v28 = v52 + 1;
              ++v29;
            }
            while ( v27 < this->spherePolys.num );
          }
          if ( this->spherePolys.list )
            Memory::Free(this->spherePolys.list);
          size = newObj.size;
          v7 = newObj.size == 0;
          this->spherePolys.list = 0;
          this->spherePolys.num = v19;
          this->spherePolys.size = size;
          this->spherePolys.granularity = 16;
          if ( !v7 )
          {
            this->spherePolys.list = (triangle_s *)Memory::Allocate(36 * size);
            v85 = 0;
            if ( this->spherePolys.num > 0 )
            {
              v57 = newObj.list;
              ptrc = 0;
              do
              {
                v58 = (triangle_s *)&ptrc[(unsigned int)this->spherePolys.list];
                p_y = (_DWORD *)&v58->pt[0].y;
                v60 = (char *)v57 - (char *)v58;
                v61 = v57;
                v62 = 3;
                do
                {
                  *(p_y - 1) = LODWORD(v61->pt[0].x);
                  *p_y = *(_DWORD *)((char *)p_y + v60);
                  p_y[1] = LODWORD(v61->pt[0].z);
                  v61 = (triangle_s *)((char *)v61 + 12);
                  p_y += 3;
                  --v62;
                }
                while ( v62 );
                ptrc += 36;
                ++v57;
                ++v85;
              }
              while ( v85 < this->spherePolys.num );
            }
          }
          v8 = level + 1 < r_debugSphereSubdivision.internalVar->integerValue;
          list = newObj.list;
          ++level;
        }
        while ( v8 );
      }
      v106 = -1;
      if ( list )
        Memory::Free(list);
    }
    v63 = 0;
    if ( this->spherePolys.num > 0 )
    {
      v64 = 0;
      do
      {
        radius = sphere->radius;
        v66 = (float *)&this->spherePolys.list[v64];
        v98 = radius * *v66;
        v99 = radius * v66[1];
        v67 = v98 + sphere->origin.x;
        v68 = radius * v66[2];
        v69 = v99 + sphere->origin.y;
        v103 = v68 + sphere->origin.z;
        a.z = v103;
        a.x = v67;
        a.y = v69;
        v70 = sphere->radius;
        v96 = v70 * v66[3];
        v97 = v70 * v66[4];
        v71 = v96 + sphere->origin.x;
        v72 = v70 * v66[5];
        v73 = v97 + sphere->origin.y;
        v101 = v72 + sphere->origin.z;
        b.z = v101;
        b.x = v71;
        v74 = this->__vftable;
        b.y = v73;
        v75 = sphere->radius;
        v94 = v75 * v66[6];
        v95 = v75 * v66[7];
        v76 = v94 + sphere->origin.x;
        v77 = v75 * v66[8];
        v78 = v95 + sphere->origin.y;
        v105 = v77 + sphere->origin.z;
        c.z = v105;
        c.x = v76;
        c.y = v78;
        v74->DebugLine(this, color, &a, &b, lifetime, depthTest);
        this->DebugLine(this, color, &b, &c, lifetime, depthTest);
        ++v63;
        ++v64;
      }
      while ( v63 < this->spherePolys.num );
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugBounds(class idVec4 const &,class idBounds const &,class idVec3 const &,int,bool)
void __thiscall idRenderWorldLocal::DebugBounds(
        idRenderWorldLocal *this,
        const idVec4 *color,
        const idBounds *bounds,
        const idVec3 *org,
        int lifetime,
        BOOL depthTest)
{
  double v7; // st5
  float z; // edx
  idVec3 *v9; // esi
  int v10; // ebp
  float *p_x; // ebx
  idRenderWorldLocal_vtbl *v12; // edx
  idRenderWorldLocal_vtbl *v13; // ebp
  const char *v14; // eax
  idRenderWorldLocal_vtbl *v15; // ebp
  const char *v16; // eax
  idRenderWorldLocal_vtbl *v17; // ebp
  double v18; // st7
  double v19; // st7
  char *v20; // eax
  double v21; // st7
  idRenderWorldLocal_vtbl *v22; // ebp
  double v23; // st7
  char *v24; // eax
  double v25; // st7
  idRenderWorldLocal_vtbl *v26; // ebp
  double v27; // st7
  char *v28; // eax
  float v29; // [esp+F0h] [ebp-E8h]
  char v30; // [esp+F0h] [ebp-E8h]
  float v31; // [esp+F4h] [ebp-E4h]
  int v32; // [esp+F4h] [ebp-E4h]
  float Pta; // [esp+F8h] [ebp-E0h]
  idVec3 *Pt; // [esp+F8h] [ebp-E0h]
  idVec3 v3Temp; // [esp+FCh] [ebp-DCh] BYREF
  idMat3 axis; // [esp+108h] [ebp-D0h] BYREF
  idVec3 *v37; // [esp+12Ch] [ebp-ACh]
  float v38; // [esp+134h] [ebp-A4h]
  float v39; // [esp+138h] [ebp-A0h]
  float v40; // [esp+140h] [ebp-98h]
  float v41; // [esp+144h] [ebp-94h]
  float v42; // [esp+14Ch] [ebp-8Ch]
  float v43; // [esp+150h] [ebp-88h]
  idVec3 v[8]; // [esp+154h] [ebp-84h] BYREF
  float v45; // [esp+1BCh] [ebp-1Ch]
  float v46; // [esp+1C8h] [ebp-10h]
  float v47; // [esp+1D4h] [ebp-4h]

  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type)
    && bounds->b[0].x <= (double)bounds->b[1].x )
  {
    v[0].x = bounds->b[0].x + org->x;
    v[0].y = bounds->b[0].y + org->y;
    v[0].z = bounds->b[0].z + org->z;
    Pta = bounds->b[1].x + org->x;
    v[1].x = Pta;
    v[1].y = v[0].y;
    v[1].z = v[0].z;
    v[2].x = Pta;
    v31 = bounds->b[1].y + org->y;
    v[2].y = v31;
    v[2].z = v[0].z;
    v[3].x = v[0].x;
    v[3].y = v31;
    v[3].z = v[0].z;
    v[4].x = v[0].x;
    v[4].y = v[0].y;
    v7 = bounds->b[1].z + org->z;
    v[5].x = Pta;
    v29 = v7;
    v[6].x = Pta;
    v[4].z = v7;
    v[7].y = v31;
    v[5].y = v[0].y;
    v[7].x = v[0].x;
    v[6].y = v31;
    v[5].z = v29;
    v[6].z = v29;
    v[7].z = v29;
    if ( tr.primaryView )
    {
      axis.mat[0].x = tr.primaryView->renderView.viewaxis.mat[0].x;
      axis.mat[0].y = tr.primaryView->renderView.viewaxis.mat[0].y;
      axis.mat[0].z = tr.primaryView->renderView.viewaxis.mat[0].z;
      axis.mat[1] = tr.primaryView->renderView.viewaxis.mat[1];
      axis.mat[2].x = tr.primaryView->renderView.viewaxis.mat[2].x;
      axis.mat[2].y = tr.primaryView->renderView.viewaxis.mat[2].y;
      z = tr.primaryView->renderView.viewaxis.mat[2].z;
    }
    else
    {
      axis.mat[0].x = mat3_identity.mat[0].x;
      axis.mat[0].y = mat3_identity.mat[0].y;
      axis.mat[0].z = mat3_identity.mat[0].z;
      axis.mat[1] = mat3_identity.mat[1];
      z = mat3_identity.mat[2].z;
      axis.mat[2].x = mat3_identity.mat[2].x;
      axis.mat[2].y = mat3_identity.mat[2].y;
    }
    axis.mat[2].z = z;
    v30 = 1;
    v9 = &v[4];
    v32 = 4;
    do
    {
      v10 = v30 & 3;
      Pt = &v[v10];
      p_x = &v9[-4].x;
      this->DebugLine(this, color, &v9[-4], &v[v10], lifetime, depthTest);
      v12 = this->__vftable;
      v37 = &v[v10 + 4];
      v12->DebugLine(this, color, v9, &v[v10 + 4], lifetime, depthTest);
      this->DebugLine(this, color, &v9[-4], v9, lifetime, depthTest);
      if ( r_drawBoundInfo.internalVar->integerValue )
      {
        v13 = this->__vftable;
        v14 = idVec3::ToString(v9 - 4, 2);
        ((void (__thiscall *)(idRenderWorldLocal *, const char *, idVec3 *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))v13->DrawTextA)(
          this,
          v14,
          &v9[-4],
          1028443341,
          &colorOrange,
          &axis,
          1,
          0,
          0);
        v15 = this->__vftable;
        v16 = idVec3::ToString(v9, 2);
        ((void (__thiscall *)(idRenderWorldLocal *, const char *, idVec3 *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))v15->DrawTextA)(
          this,
          v16,
          v9,
          1028443341,
          &colorOrange,
          &axis,
          1,
          0,
          0);
        v17 = this->__vftable;
        v18 = Pt->x + *p_x;
        v42 = Pt->y + v9[-4].y;
        v43 = Pt->z + v9[-4].z;
        v46 = v43 * 0.5;
        v3Temp.z = v46;
        v3Temp.x = v18 * 0.5;
        v3Temp.y = v42 * 0.5;
        v19 = idVec3::Dist(v9 - 4, Pt);
        v20 = va("%f", v19);
        ((void (__thiscall *)(idRenderWorldLocal *, char *, idVec3 *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))v17->DrawTextA)(
          this,
          v20,
          &v3Temp,
          1028443341,
          &colorPink,
          &axis,
          1,
          0,
          0);
        v21 = v9->x + v37->x;
        v38 = v37->y + v9->y;
        v39 = v37->z + v9->z;
        v22 = this->__vftable;
        v45 = v39 * 0.5;
        v3Temp.z = v45;
        v3Temp.x = v21 * 0.5;
        v3Temp.y = v38 * 0.5;
        v23 = idVec3::Dist(v9, v37);
        v24 = va("%f", v23);
        ((void (__thiscall *)(idRenderWorldLocal *, char *, idVec3 *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))v22->DrawTextA)(
          this,
          v24,
          &v3Temp,
          1028443341,
          &colorPink,
          &axis,
          1,
          0,
          0);
        v25 = *p_x + v9->x;
        v26 = this->__vftable;
        v40 = v9->y + v9[-4].y;
        v41 = v9->z + v9[-4].z;
        v47 = v41 * 0.5;
        v3Temp.z = v47;
        v3Temp.x = v25 * 0.5;
        v3Temp.y = v40 * 0.5;
        v27 = idVec3::Dist(v9 - 4, v9);
        v28 = va("%f", v27);
        ((void (__thiscall *)(idRenderWorldLocal *, char *, idVec3 *, int, idVec4 *, idMat3 *, int, _DWORD, _DWORD))v26->DrawTextA)(
          this,
          v28,
          &v3Temp,
          1028443341,
          &colorPink,
          &axis,
          1,
          0,
          0);
      }
      ++v30;
      ++v9;
      --v32;
    }
    while ( v32 );
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugFOV(class idVec4 const &,class idVec3 const &,class idVec3 const &,float,float,float,float,float,int)
void __userpurge idRenderWorldLocal::DebugFOV(
        idRenderWorldLocal *this@<ecx>,
        int a2@<edi>,
        int a3@<esi>,
        const idVec4 *color,
        const idVec3 *origin,
        idVec3 *dir,
        float farDot,
        float farDist,
        float nearDot,
        float nearDist,
        float alpha,
        int lifetime)
{
  unsigned int v12; // eax
  long double v14; // st7
  long double v15; // st7
  float y; // eax
  int numPoints; // eax
  idVec5 *v18; // eax
  idVec3 *v19; // eax
  double v20; // st7
  double v21; // st6
  int v22; // eax
  double v23; // st6
  double v24; // st7
  idVec5 *v25; // eax
  idVec3 *v26; // eax
  double v27; // st7
  double v28; // st6
  int v29; // eax
  idVec5 *v30; // eax
  int v31; // eax
  idVec5 *v32; // eax
  idVec3 *v33; // eax
  double v34; // st7
  double v35; // st6
  int v36; // eax
  double v37; // st7
  double v38; // st6
  idVec5 *v39; // eax
  idVec3 *v40; // eax
  double v41; // st7
  double v42; // st7
  double v43; // st6
  int v44; // eax
  idVec5 *v45; // eax
  int v46; // eax
  idVec5 *v47; // eax
  idAngles *v48; // eax
  float roll; // eax
  idVec3 *v50; // eax
  double v51; // st7
  double v52; // st6
  int v53; // eax
  double v54; // st7
  double v55; // st6
  idVec5 *v56; // eax
  idVec3 *v57; // eax
  double v58; // st7
  double v59; // st6
  int v60; // eax
  idVec5 *v61; // eax
  int v62; // eax
  idVec5 *v63; // eax
  idAngles *v64; // eax
  float v65; // eax
  idVec3 *v66; // eax
  double v67; // st7
  double v68; // st6
  int v69; // eax
  double v70; // st7
  double v71; // st6
  idVec5 *v72; // eax
  idVec3 *v73; // eax
  double v74; // st7
  double v75; // st7
  double v76; // st6
  int v77; // eax
  idVec5 *v78; // eax
  float v80; // [esp+98h] [ebp-20h]
  float v81; // [esp+98h] [ebp-20h]
  float v82; // [esp+98h] [ebp-20h]
  float v83; // [esp+98h] [ebp-20h]
  float v84; // [esp+9Ch] [ebp-1Ch]
  float v85; // [esp+9Ch] [ebp-1Ch]
  float v86; // [esp+9Ch] [ebp-1Ch]
  float v87; // [esp+9Ch] [ebp-1Ch]
  float v88; // [esp+9Ch] [ebp-1Ch]
  idAngles result; // [esp+A0h] [ebp-18h] BYREF
  idVec3 v90; // [esp+ACh] [ebp-Ch] BYREF

  v12 = _S12_3;
  if ( (_S12_3 & 1) == 0 )
  {
    LOBYTE(v12) = _S12_3 | 1;
    w.__vftable = (idWinding_vtbl *)&idWinding::`vftable';
    w.allocedSize = 0;
    w.numPoints = 0;
    w.p = 0;
    _S12_3 = v12;
    atexit(_E13_12);
    v12 = _S12_3;
  }
  if ( (v12 & 2) == 0 )
  {
    LOBYTE(v12) = v12 | 2;
    _S12_3 = v12;
  }
  if ( (v12 & 4) == 0 )
  {
    LOBYTE(v12) = v12 | 4;
    _S12_3 = v12;
  }
  if ( (v12 & 8) == 0 )
  {
    LOBYTE(v12) = v12 | 8;
    _S12_3 = v12;
  }
  if ( !(*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 48))(common.type) )
    return;
  if ( farDot > -1.0 )
  {
    if ( farDot < 1.0 )
      v14 = acos(farDot);
    else
      v14 = 0.0;
  }
  else
  {
    v14 = 3.1415927;
  }
  farYaw = v14 * idMath::M_RAD2DEG;
  if ( nearDot > -1.0 )
  {
    if ( nearDot < 1.0 )
      v15 = acos(nearDot);
    else
      v15 = 0.0;
  }
  else
  {
    v15 = 3.1415927;
  }
  c.x = color->x;
  y = color->y;
  nearYaw = v15 * idMath::M_RAD2DEG;
  c.y = y;
  c.z = color->z;
  c.w = color->w;
  if ( alpha < 1.0 )
    c.w = alpha;
  w.numPoints = 0;
  w.allocedSize = 0;
  Memory::Free(w.p);
  numPoints = w.numPoints;
  w.p = 0;
  if ( w.numPoints + 1 > w.allocedSize )
  {
    if ( !w.ReAllocate(&w, w.numPoints + 1, 1) )
      goto LABEL_26;
    numPoints = w.numPoints;
  }
  v18 = &w.p[numPoints];
  *(idVec3 *)&v18->x = *origin;
  v18->t = 0.0;
  v18->s = 0.0;
  ++w.numPoints;
LABEL_26:
  a = *idVec3::ToAngles(dir, &result);
  v19 = idAngles::ToForward(&a, (idVec3 *)&result);
  v20 = farDist * v19->x;
  v80 = farDist * v19->y;
  v21 = farDist * v19->z;
  v22 = w.numPoints;
  v84 = v21;
  v85 = v84 + origin->z;
  v23 = v20 + origin->x;
  v24 = v80 + origin->y;
  p.z = v85;
  p.x = v23;
  p.y = v24;
  if ( w.numPoints + 1 <= w.allocedSize )
  {
LABEL_29:
    v25 = &w.p[v22];
    *(idVec3 *)&v25->x = p;
    v25->t = 0.0;
    v25->s = 0.0;
    ++w.numPoints;
    goto LABEL_30;
  }
  if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
  {
    v22 = w.numPoints;
    goto LABEL_29;
  }
LABEL_30:
  radial = 0;
  do
  {
    a.yaw = a.yaw - farYaw * 0.2;
    v26 = idAngles::ToForward(&a, &v90);
    v81 = farDist * v26->y;
    v86 = farDist * v26->z;
    v27 = farDist * v26->x + origin->x;
    v28 = v81 + origin->y;
    result.roll = v86 + origin->z;
    p.z = result.roll;
    v29 = w.numPoints;
    p.x = v27;
    p.y = v28;
    if ( w.numPoints + 1 > w.allocedSize )
    {
      if ( !w.ReAllocate(&w, w.numPoints + 1, 1) )
        goto LABEL_35;
      v29 = w.numPoints;
    }
    v30 = &w.p[v29];
    *(idVec3 *)&v30->x = p;
    v30->t = 0.0;
    v30->s = 0.0;
    ++w.numPoints;
LABEL_35:
    ++radial;
  }
  while ( radial < 5 );
  ((void (__thiscall *)(idRenderWorldLocal *, idVec4 *, idWinding *, int, _DWORD, int, int))this->DebugPolygon)(
    this,
    &c,
    &w,
    lifetime,
    0,
    a2,
    a3);
  w.numPoints = 0;
  w.allocedSize = 0;
  Memory::Free(w.p);
  v31 = w.numPoints;
  w.p = 0;
  if ( w.numPoints + 1 <= w.allocedSize )
    goto LABEL_39;
  if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
  {
    v31 = w.numPoints;
LABEL_39:
    v32 = &w.p[v31];
    *(idVec3 *)&v32->x = *origin;
    v32->t = 0.0;
    v32->s = 0.0;
    ++w.numPoints;
  }
  a = *idVec3::ToAngles(dir, (idAngles *)&v90.z);
  v33 = idAngles::ToForward(&a, (idVec3 *)&v90.z);
  v34 = nearDist * v33->x;
  result.pitch = nearDist * v33->y;
  v35 = nearDist * v33->z;
  v36 = w.numPoints;
  result.yaw = v35;
  v37 = v34 + origin->x;
  v38 = result.pitch + origin->y;
  v90.y = result.yaw + origin->z;
  p.z = v90.y;
  p.x = v37;
  p.y = v38;
  if ( w.numPoints + 1 <= w.allocedSize )
  {
LABEL_43:
    v39 = &w.p[v36];
    *(idVec3 *)&v39->x = p;
    v39->t = 0.0;
    v39->s = 0.0;
    ++w.numPoints;
  }
  else if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
  {
    v36 = w.numPoints;
    goto LABEL_43;
  }
  radial = 0;
  while ( 2 )
  {
    a.yaw = farYaw * 0.2 + a.yaw;
    v40 = idAngles::ToForward(&a, (idVec3 *)&v90.z);
    v41 = nearDist * v40->x;
    result.pitch = nearDist * v40->y;
    result.yaw = nearDist * v40->z;
    v42 = v41 + origin->x;
    v43 = result.pitch + origin->y;
    v90.y = result.yaw + origin->z;
    p.z = v90.y;
    v44 = w.numPoints;
    p.x = v42;
    p.y = v43;
    if ( w.numPoints + 1 <= w.allocedSize )
    {
LABEL_48:
      v45 = &w.p[v44];
      *(idVec3 *)&v45->x = p;
      v45->t = 0.0;
      v45->s = 0.0;
      ++w.numPoints;
    }
    else if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
    {
      v44 = w.numPoints;
      goto LABEL_48;
    }
    if ( ++radial < 5 )
      continue;
    break;
  }
  (*(void (__thiscall **)(float, idVec4 *, idWinding *))(*(_DWORD *)LODWORD(v81) + 272))(
    COERCE_FLOAT(LODWORD(v81)),
    &c,
    &w);
  if ( nearDist != 0.0 && nearYaw > (double)farYaw )
  {
    w.numPoints = 0;
    w.allocedSize = 0;
    Memory::Free(w.p);
    v46 = w.numPoints;
    w.p = 0;
    if ( w.numPoints + 1 <= w.allocedSize )
      goto LABEL_55;
    if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
    {
      v46 = w.numPoints;
LABEL_55:
      v47 = &w.p[v46];
      *(idVec3 *)&v47->x = *origin;
      v47->t = 0.0;
      v47->s = 0.0;
      ++w.numPoints;
    }
    v48 = idVec3::ToAngles(dir, (idAngles *)&v90);
    a.pitch = v48->pitch;
    a.yaw = v48->yaw;
    roll = v48->roll;
    a.yaw = a.yaw + farYaw;
    a.roll = roll;
    v50 = idAngles::ToForward(&a, &v90);
    v51 = nearDist * v50->x;
    v82 = nearDist * v50->y;
    v52 = nearDist * v50->z;
    v53 = w.numPoints;
    v87 = v52;
    v54 = v51 + origin->x;
    v55 = v82 + origin->y;
    result.roll = v87 + origin->z;
    p.z = result.roll;
    p.x = v54;
    p.y = v55;
    if ( w.numPoints + 1 <= w.allocedSize )
    {
LABEL_59:
      v56 = &w.p[v53];
      *(idVec3 *)&v56->x = p;
      v56->t = 0.0;
      v56->s = 0.0;
      ++w.numPoints;
    }
    else if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
    {
      v53 = w.numPoints;
      goto LABEL_59;
    }
    radial = 0;
    while ( 2 )
    {
      a.yaw = (nearYaw - farYaw) * 0.11111111 + a.yaw;
      v57 = idAngles::ToForward(&a, &v90);
      v83 = nearDist * v57->y;
      v88 = nearDist * v57->z;
      v58 = nearDist * v57->x + origin->x;
      v59 = v83 + origin->y;
      result.roll = v88 + origin->z;
      p.z = result.roll;
      v60 = w.numPoints;
      p.x = v58;
      p.y = v59;
      if ( w.numPoints + 1 <= w.allocedSize )
      {
LABEL_64:
        v61 = &w.p[v60];
        *(idVec3 *)&v61->x = p;
        v61->t = 0.0;
        v61->s = 0.0;
        ++w.numPoints;
      }
      else if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
      {
        v60 = w.numPoints;
        goto LABEL_64;
      }
      if ( ++radial >= 9 )
      {
        ((void (__thiscall *)(idRenderWorldLocal *, idVec4 *, idWinding *, int, _DWORD, int, _DWORD))this->DebugPolygon)(
          this,
          &c,
          &w,
          lifetime,
          0,
          lifetime,
          0);
        w.numPoints = 0;
        w.allocedSize = 0;
        Memory::Free(w.p);
        v62 = w.numPoints;
        w.p = 0;
        if ( w.numPoints + 1 <= w.allocedSize )
          goto LABEL_69;
        if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
        {
          v62 = w.numPoints;
LABEL_69:
          v63 = &w.p[v62];
          *(idVec3 *)&v63->x = *origin;
          v63->t = 0.0;
          v63->s = 0.0;
          ++w.numPoints;
        }
        v64 = idVec3::ToAngles(dir, (idAngles *)&v90.z);
        a.pitch = v64->pitch;
        a.yaw = v64->yaw;
        v65 = v64->roll;
        a.yaw = a.yaw - farYaw;
        a.roll = v65;
        v66 = idAngles::ToForward(&a, (idVec3 *)&v90.z);
        v67 = *(float *)&lifetime * v66->x;
        result.pitch = *(float *)&lifetime * v66->y;
        v68 = *(float *)&lifetime * v66->z;
        v69 = w.numPoints;
        result.yaw = v68;
        v70 = v67 + origin->x;
        v71 = result.pitch + origin->y;
        v90.y = result.yaw + origin->z;
        p.z = v90.y;
        p.x = v70;
        p.y = v71;
        if ( w.numPoints + 1 <= w.allocedSize )
        {
LABEL_73:
          v72 = &w.p[v69];
          *(idVec3 *)&v72->x = p;
          v72->t = 0.0;
          v72->s = 0.0;
          ++w.numPoints;
        }
        else if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
        {
          v69 = w.numPoints;
          goto LABEL_73;
        }
        radial = 0;
        while ( 2 )
        {
          a.yaw = a.yaw - (nearYaw - farYaw) * 0.11111111;
          v73 = idAngles::ToForward(&a, (idVec3 *)&v90.z);
          v74 = *(float *)&lifetime * v73->x;
          result.pitch = *(float *)&lifetime * v73->y;
          result.yaw = *(float *)&lifetime * v73->z;
          v75 = v74 + origin->x;
          v76 = result.pitch + origin->y;
          v90.y = result.yaw + origin->z;
          p.z = v90.y;
          v77 = w.numPoints;
          p.x = v75;
          p.y = v76;
          if ( w.numPoints + 1 <= w.allocedSize )
          {
LABEL_78:
            v78 = &w.p[v77];
            *(idVec3 *)&v78->x = p;
            v78->t = 0.0;
            v78->s = 0.0;
            ++w.numPoints;
          }
          else if ( w.ReAllocate(&w, w.numPoints + 1, 1) )
          {
            v77 = w.numPoints;
            goto LABEL_78;
          }
          if ( ++radial >= 9 )
          {
            (*(void (__thiscall **)(float, idVec4 *, idWinding *))(*(_DWORD *)LODWORD(v83) + 272))(
              COERCE_FLOAT(LODWORD(v83)),
              &c,
              &w);
            return;
          }
          continue;
        }
      }
      continue;
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::PushMarkedDefs(void)
void __thiscall idRenderWorldLocal::PushMarkedDefs(idRenderWorldLocal *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // ebx
  int v5; // eax
  idRenderLightLocal **list; // ecx
  idRenderLightLocal *v7; // edi
  int v8; // edi

  if ( r_suppressMultipleUpdates.internalVar->integerValue )
  {
    v2 = 0;
    for ( tr.pc.c_entityPushes = this->markedEntityDefs.num; v2 < this->markedEntityDefs.num; ++v2 )
    {
      v3 = this->markedEntityDefs.list[v2];
      if ( v3 < 0 || v3 >= this->entityDefs.num )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "idRenderWorld::PushEntityDef: handle %i >= %i\n",
          v3,
          this->entityDefs.num);
      }
      else if ( this->entityDefs.list[v3] )
      {
        R_CreateEntityRefs(this->entityDefs.list[v3]);
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "idRenderWorld::PushEntityDef: handle %i [0, %i] is NULL\n",
          v3,
          this->entityDefs.num);
      }
    }
    v4 = 0;
    for ( tr.pc.c_lightPushes = this->markedLightDefs.num; v4 < this->markedLightDefs.num; ++v4 )
    {
      v5 = this->markedLightDefs.list[v4];
      if ( v5 < 0 || v5 >= this->lightDefs.num )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "idRenderWorld::PushLightDef: invalid handle %i >= %i\n",
          v5,
          this->lightDefs.num);
      }
      else
      {
        list = this->lightDefs.list;
        v7 = list[v5];
        if ( v7 )
        {
          v7->DeriveLightData(list[v5]);
          R_CreateLightRefs(v7);
          R_CreateLightDefFogPortals(v7);
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "idRenderWorld::PushLightDef: handle %i [0, %i] is NULL\n",
            v5,
            this->lightDefs.num);
        }
      }
    }
    v8 = 0;
    for ( tr.pc.c_effectPushes = this->markedEffectDefs.num; v8 < this->markedEffectDefs.num; ++v8 )
      idRenderWorldLocal::PushEffectDef(this, this->markedEffectDefs.list[v8]);
    this->ClearMarkedDefs(this);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::MarkEffectDef(int)
void __thiscall idRenderWorldLocal::MarkEffectDef(idRenderWorldLocal *this, int effectHandle)
{
  int num; // edi
  int v4; // eax
  int *v5; // edx
  int v6; // ebx
  int v7; // ecx
  int v8; // ecx
  int *v9; // ecx
  int v10; // edx
  int *v11; // ecx
  int granularity; // eax
  bool v13; // cc
  int i; // eax
  int v15; // ebx
  int size; // ecx
  int v17; // ecx
  int *list; // edi
  int j; // eax

  if ( r_suppressMultipleUpdates.internalVar->integerValue )
  {
    num = this->markedEffectDefs.num;
    v4 = 0;
    if ( num <= 0 )
    {
      v6 = effectHandle;
LABEL_15:
      if ( v6 >= 0 )
      {
        if ( !this->markedEffectDefs.list )
        {
          granularity = this->markedEffectDefs.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->markedEffectDefs.size )
            {
              v13 = granularity < this->markedEffectDefs.num;
              this->markedEffectDefs.size = granularity;
              if ( v13 )
                this->markedEffectDefs.num = granularity;
              this->markedEffectDefs.list = (int *)Memory::Allocate(4 * granularity);
              for ( i = 0; i < this->markedEffectDefs.num; ++i )
                this->markedEffectDefs.list[i] = *(_DWORD *)(4 * i);
            }
          }
          else
          {
            this->markedEffectDefs.list = 0;
            this->markedEffectDefs.num = 0;
            this->markedEffectDefs.size = 0;
          }
        }
        v15 = this->markedEffectDefs.num;
        size = this->markedEffectDefs.size;
        if ( v15 == size )
        {
          if ( !this->markedEffectDefs.granularity )
            this->markedEffectDefs.granularity = 16;
          v17 = this->markedEffectDefs.granularity
              + size
              - (this->markedEffectDefs.granularity + size) % this->markedEffectDefs.granularity;
          if ( v17 > 0 )
          {
            if ( v17 != this->markedEffectDefs.size )
            {
              list = this->markedEffectDefs.list;
              this->markedEffectDefs.size = v17;
              if ( v17 < v15 )
                this->markedEffectDefs.num = v17;
              this->markedEffectDefs.list = (int *)Memory::Allocate(4 * v17);
              for ( j = 0; j < this->markedEffectDefs.num; ++j )
                this->markedEffectDefs.list[j] = list[j];
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( this->markedEffectDefs.list )
              Memory::Free(this->markedEffectDefs.list);
            this->markedEffectDefs.list = 0;
            this->markedEffectDefs.num = 0;
            this->markedEffectDefs.size = 0;
          }
        }
        this->markedEffectDefs.list[this->markedEffectDefs.num++] = effectHandle;
      }
    }
    else
    {
      v5 = this->markedEffectDefs.list;
      while ( 1 )
      {
        v6 = effectHandle;
        if ( *v5 == effectHandle )
          break;
        if ( *v5 == -1 - effectHandle )
        {
          if ( v4 >= 0 )
          {
            v7 = this->markedEffectDefs.num;
            if ( v4 < v7 )
            {
              v8 = v7 - 1;
              for ( this->markedEffectDefs.num = v8; v4 < this->markedEffectDefs.num; *v11 = v10 )
              {
                v9 = this->markedEffectDefs.list;
                v10 = v9[v4 + 1];
                v11 = &v9[v4++];
              }
            }
          }
          break;
        }
        ++v4;
        ++v5;
        if ( v4 >= num )
          goto LABEL_15;
      }
      ++tr.pc.c_effectPushesSuppressed;
    }
  }
  else if ( effectHandle >= 0 )
  {
    idRenderWorldLocal::PushEffectDef(this, effectHandle);
  }
}

// FUNC: public: virtual bool __thiscall idRenderWorldLocal::UpdateEffectDef(int,struct renderEffect_s const *,int)
char __thiscall idRenderWorldLocal::UpdateEffectDef(
        idRenderWorldLocal *this,
        unsigned int effectHandle,
        const renderEffect_s *reffect,
        int time)
{
  unsigned int v6; // esi
  int granularity; // eax
  bool v8; // cc
  int i; // eax
  int num; // ebx
  int size; // ecx
  int v12; // ecx
  rvRenderEffectLocal **list; // esi
  int j; // eax
  rvRenderEffectLocal *v15; // ebx
  rvRenderEffectLocal *v16; // eax
  rvRenderEffectLocal *v17; // eax
  rvRenderEffectLocal *v18; // esi
  float v19; // [esp+0h] [ebp-28h]
  float v20; // [esp+0h] [ebp-28h]
  bool push; // [esp+17h] [ebp-11h]

  if ( r_skipUpdates.internalVar->integerValue )
    return 0;
  if ( !bse_enabled.internalVar->integerValue )
    return 1;
  ++tr.pc.c_effectUpdates;
  v6 = effectHandle;
  if ( effectHandle >= 0x2711 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorld::UpdateEffectDef: index = %i [0, %i]",
      effectHandle,
      this->effectDefs.num);
  for ( ; (signed int)effectHandle >= this->effectDefs.num; ++this->effectDefs.num )
  {
    if ( !this->effectDefs.list )
    {
      granularity = this->effectDefs.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->effectDefs.size )
        {
          v8 = granularity < this->effectDefs.num;
          this->effectDefs.size = granularity;
          if ( v8 )
            this->effectDefs.num = granularity;
          this->effectDefs.list = (rvRenderEffectLocal **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->effectDefs.num; ++i )
            this->effectDefs.list[i] = *(rvRenderEffectLocal **)(4 * i);
        }
      }
      else
      {
        this->effectDefs.list = 0;
        this->effectDefs.num = 0;
        this->effectDefs.size = 0;
      }
    }
    num = this->effectDefs.num;
    size = this->effectDefs.size;
    if ( num == size )
    {
      if ( !this->effectDefs.granularity )
        this->effectDefs.granularity = 16;
      v12 = this->effectDefs.granularity + size - (this->effectDefs.granularity + size) % this->effectDefs.granularity;
      if ( v12 > 0 )
      {
        if ( v12 != this->effectDefs.size )
        {
          list = this->effectDefs.list;
          this->effectDefs.size = v12;
          if ( v12 < num )
            this->effectDefs.num = v12;
          this->effectDefs.list = (rvRenderEffectLocal **)Memory::Allocate(4 * v12);
          for ( j = 0; j < this->effectDefs.num; ++j )
            this->effectDefs.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->effectDefs.list )
          Memory::Free(this->effectDefs.list);
        this->effectDefs.list = 0;
        this->effectDefs.num = 0;
        this->effectDefs.size = 0;
      }
    }
    v6 = effectHandle;
    this->effectDefs.list[this->effectDefs.num] = 0;
  }
  v15 = this->effectDefs.list[v6];
  if ( v15 )
  {
    push = 0;
    if ( memcmp(reffect, &v15->parms, 0x70u) )
    {
      R_FreeEffectDefDerivedData(v15);
      push = 1;
    }
    renderEffect_s::operator=(&v15->parms.declEffect, (int)reffect);
  }
  else
  {
    push = 1;
    v16 = (rvRenderEffectLocal *)Memory::Allocate(0x12Cu);
    if ( v16 )
    {
      rvRenderEffectLocal::rvRenderEffectLocal(v16);
      v18 = v17;
    }
    else
    {
      v18 = 0;
    }
    this->effectDefs.list[effectHandle] = v18;
    v18->index = effectHandle;
    v15 = v18;
    v18->world = this;
    renderEffect_s::operator=(&v18->parms.declEffect, (int)reffect);
    v20 = (double)time * 0.001;
    if ( !((unsigned __int8 (__stdcall *)(rvRenderEffectLocal *, _DWORD))bse->PlayEffect)(v18, LODWORD(v20)) )
      return 1;
  }
  if ( session->writeDemo )
  {
    idRenderWorldLocal::WriteUpdateEffectDef(this, effectHandle);
    v15->writeToDemo = 1;
  }
  v19 = (double)time * 0.001;
  if ( ((unsigned __int8 (__stdcall *)(rvRenderEffectLocal *, _DWORD))bse->ServiceEffect)(v15, LODWORD(v19)) )
    return 1;
  if ( push )
    idRenderWorldLocal::MarkEffectDef(this, effectHandle);
  return 0;
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::FreeEffectDef(int)
void __userpurge idRenderWorldLocal::FreeEffectDef(idRenderWorldLocal *this@<ecx>, int a2@<esi>, int effectHandle)
{
  int num; // eax
  rvRenderEffectLocal *v5; // esi

  if ( effectHandle < 0 || (num = this->effectDefs.num, effectHandle >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorld::FreeEffectDef: invalid handle %i >= %i\n",
      effectHandle,
      this->effectDefs.num);
  }
  else
  {
    v5 = this->effectDefs.list[effectHandle];
    if ( v5 )
    {
      ((void (__thiscall *)(rvBSEManager *, rvRenderEffectLocal *, int))bse->FreeEffect)(bse, v5, a2);
      R_FreeEffectDefDerivedData(v5);
      if ( session->writeDemo )
      {
        if ( v5->archived )
        {
          idRenderWorldLocal::WriteFreeEffectDef(this, effectHandle);
          v5->writeToDemo = 0;
          v5->archived = 0;
        }
      }
      ((void (__thiscall *)(rvRenderEffectLocal *, int))v5->~rvRenderEffectLocal)(v5, 1);
      this->effectDefs.list[effectHandle] = 0;
      idRenderWorldLocal::MarkEffectDef(this, -1 - effectHandle);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorld::FreeEffectDef: handle %i [0, %i] is NULL\n",
        effectHandle,
        num);
    }
  }
}

// FUNC: public: __thiscall idRenderWorldLocal::idRenderWorldLocal(void)
void __thiscall idRenderWorldLocal::idRenderWorldLocal(idRenderWorldLocal *this)
{
  idStr *p_mapName; // edi
  char *baseBuffer; // ecx

  p_mapName = &this->mapName;
  this->__vftable = (idRenderWorldLocal_vtbl *)&idRenderWorldLocal::`vftable';
  this->mapName.len = 0;
  this->mapName.alloced = 20;
  this->mapName.data = this->mapName.baseBuffer;
  this->mapName.baseBuffer[0] = 0;
  this->localModels.granularity = 16;
  this->localModels.list = 0;
  this->localModels.num = 0;
  this->localModels.size = 0;
  this->entityDefs.granularity = 16;
  this->entityDefs.list = 0;
  this->entityDefs.num = 0;
  this->entityDefs.size = 0;
  this->lightDefs.granularity = 16;
  this->lightDefs.list = 0;
  this->lightDefs.num = 0;
  this->lightDefs.size = 0;
  this->effectDefs.granularity = 16;
  this->effectDefs.list = 0;
  this->effectDefs.num = 0;
  this->effectDefs.size = 0;
  this->markedEntityDefs.granularity = 16;
  this->markedEntityDefs.list = 0;
  this->markedEntityDefs.num = 0;
  this->markedEntityDefs.size = 0;
  this->markedLightDefs.granularity = 16;
  this->markedLightDefs.list = 0;
  this->markedLightDefs.num = 0;
  this->markedLightDefs.size = 0;
  this->markedEffectDefs.granularity = 16;
  this->markedEffectDefs.list = 0;
  this->markedEffectDefs.num = 0;
  this->markedEffectDefs.size = 0;
  this->areaReferenceAllocator.blocks = 0;
  this->areaReferenceAllocator.free = 0;
  this->areaReferenceAllocator.active = 0;
  this->areaReferenceAllocator.total = 0;
  this->interactionAllocator.blocks = 0;
  this->interactionAllocator.free = 0;
  this->interactionAllocator.active = 0;
  this->interactionAllocator.total = 0;
  this->areaNumRefAllocator.blocks = 0;
  this->areaNumRefAllocator.free = 0;
  this->areaNumRefAllocator.active = 0;
  this->areaNumRefAllocator.total = 0;
  this->debugLines.granularity = 16;
  this->debugLines.list = 0;
  this->debugLines.num = 0;
  this->debugLines.size = 0;
  this->debugPolys.granularity = 16;
  this->debugPolys.list = 0;
  this->debugPolys.num = 0;
  this->debugPolys.size = 0;
  this->debugText.granularity = 16;
  this->debugText.list = 0;
  this->debugText.num = 0;
  this->debugText.size = 0;
  this->spherePolys.granularity = 16;
  this->spherePolys.list = 0;
  this->spherePolys.num = 0;
  this->spherePolys.size = 0;
  baseBuffer = this->m_filename.baseBuffer;
  this->m_filename.len = 0;
  this->m_filename.alloced = 20;
  this->m_filename.data = baseBuffer;
  *baseBuffer = 0;
  idStr::FreeData(p_mapName);
  p_mapName->len = 0;
  p_mapName->alloced = 20;
  p_mapName->data = p_mapName->baseBuffer;
  p_mapName->baseBuffer[0] = 0;
  this->generateAllInteractionsCalled = 0;
  this->areaNodes = 0;
  this->numAreaNodes = 0;
  this->portalAreas = 0;
  this->numPortalAreas = 0;
  this->doublePortals = 0;
  this->numInterAreaPortals = 0;
  this->m_vertexBuffers = 0;
  this->m_numVertexBuffers = 0;
  this->m_indexBuffers = 0;
  this->m_numIndexBuffers = 0;
  this->m_silEdges = 0;
  this->m_numSilEdges = 0;
  this->m_models = 0;
  this->m_numModels = 0;
  this->m_convertedMD5R = 0;
  this->mapTimeStamp = -1;
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugClear(int)
void __thiscall idRenderWorldLocal::DebugClear(idRenderWorldLocal *this, int time)
{
  int v2; // edx
  int v4; // ebx
  int v5; // edi
  int v6; // ebp
  debugPolygon_s *v7; // eax
  int *p_lifeTime; // edi
  int v9; // ebp
  debugText_s *v10; // edi
  debugText_s *v11; // eax
  bool *p_depthTest; // edi
  idList<debugLine_s> *p_debugLines; // edi
  int v14; // ebp
  debugLine_s *list; // eax
  int v16; // ebp
  idList<debugPolygon_s> *p_debugPolys; // edi
  int v18; // ebx
  debugPolygon_s *v19; // eax
  int v20; // ebx
  idList<debugText_s> *p_debugText; // ecx
  int v22; // ebp
  int v23; // ebx
  int v24; // edi
  debugText_s *v25; // eax
  int v26; // ebp
  debugText_s *v27; // edi
  int num; // [esp+10h] [ebp-Ch]
  int numa; // [esp+10h] [ebp-Ch]
  int numb; // [esp+10h] [ebp-Ch]
  idList<debugText_s> *v31; // [esp+14h] [ebp-8h]
  idList<debugText_s> *v32; // [esp+14h] [ebp-8h]
  idList<debugText_s> *v33; // [esp+14h] [ebp-8h]
  int v34; // [esp+18h] [ebp-4h]
  int v35; // [esp+18h] [ebp-4h]

  v2 = time;
  v4 = 0;
  this->debugLineTime = time;
  this->debugPolyTime = time;
  this->debugTextTime = time;
  if ( time )
  {
    p_debugLines = &this->debugLines;
    v14 = 0;
    if ( this->debugLines.num > 0 )
    {
      v31 = 0;
      num = 0;
      do
      {
        list = this->debugLines.list;
        if ( list[num].lifeTime > v2 )
        {
          if ( v4 != v14 )
          {
            debugLine_s::operator=((float *)((char *)&list->rgb.x + (_DWORD)v31), (int)&list[num]);
            v2 = time;
          }
          ++v14;
          v31 += 3;
        }
        ++num;
        ++v4;
      }
      while ( v4 < p_debugLines->num );
    }
    idList<debugLine_s>::Resize(&this->debugLines, v14);
    p_debugLines->num = v14;
    v16 = 0;
    p_debugPolys = &this->debugPolys;
    v18 = 0;
    numa = 0;
    if ( this->debugPolys.num > 0 )
    {
      v32 = 0;
      v34 = 0;
      do
      {
        v19 = this->debugPolys.list;
        if ( v19[v34].lifeTime > time )
        {
          if ( v16 != v18 )
          {
            debugPolygon_s::operator=((int *)((char *)&v32->num + (_DWORD)v19), (int)&v19[v34]);
            v16 = numa;
          }
          ++v16;
          v32 = (idList<debugText_s> *)((char *)v32 + 40);
          numa = v16;
        }
        ++v34;
        ++v18;
      }
      while ( v18 < p_debugPolys->num );
      if ( v16 < p_debugPolys->num )
      {
        v20 = v16;
        do
        {
          this->debugPolys.list[v20].winding.Clear(&this->debugPolys.list[v20].winding);
          ++v16;
          ++v20;
        }
        while ( v16 < p_debugPolys->num );
        v16 = numa;
      }
    }
    idList<debugPolygon_s>::Resize(&this->debugPolys, v16);
    p_debugPolys->num = numa;
    p_debugText = &this->debugText;
    v22 = 0;
    v23 = 0;
    v24 = 0;
    numb = 0;
    v33 = &this->debugText;
    if ( this->debugText.num > 0 )
    {
      v35 = 0;
      do
      {
        v25 = this->debugText.list;
        if ( v25[v22].lifeTime > time )
        {
          if ( v24 != v23 )
            debugText_s::operator=((int)&v25[v35], (int)&v25[v22]);
          ++v23;
          ++v35;
        }
        ++v24;
        ++v22;
      }
      while ( v24 < v33->num );
      numb = v23;
      p_debugText = &this->debugText;
    }
    if ( v23 < p_debugText->num )
    {
      v26 = v23;
      do
      {
        v27 = &this->debugText.list[v26];
        idStr::FreeData(&v27->text);
        v27->text.data = v27->text.baseBuffer;
        v27->text.len = 0;
        v27->text.alloced = 20;
        v27->text.baseBuffer[0] = 0;
        ++v23;
        ++v26;
      }
      while ( v23 < v33->num );
      v23 = numb;
      p_debugText = &this->debugText;
    }
    idList<debugText_s>::Resize(p_debugText, v23);
    v33->num = v23;
  }
  else
  {
    if ( this->debugLines.list )
      Memory::Free(this->debugLines.list);
    this->debugLines.list = 0;
    this->debugLines.num = 0;
    this->debugLines.size = 0;
    v5 = 0;
    if ( this->debugPolys.num > 0 )
    {
      v6 = 0;
      do
      {
        this->debugPolys.list[v6].winding.Clear(&this->debugPolys.list[v6].winding);
        ++v5;
        ++v6;
      }
      while ( v5 < this->debugPolys.num );
      v4 = 0;
    }
    v7 = this->debugPolys.list;
    if ( v7 )
    {
      p_lifeTime = &v7[-1].lifeTime;
      `eh vector destructor iterator'(
        v7,
        0x28u,
        v7[-1].lifeTime,
        (void (__thiscall *)(void *))debugPolygon_s::~debugPolygon_s);
      Memory::Free(p_lifeTime);
      v4 = 0;
    }
    v9 = 0;
    this->debugPolys.list = 0;
    this->debugPolys.num = 0;
    this->debugPolys.size = 0;
    if ( this->debugText.num > 0 )
    {
      do
      {
        v10 = &this->debugText.list[v9];
        idStr::FreeData(&v10->text);
        v10->text.len = 0;
        v10->text.alloced = 20;
        v10->text.data = v10->text.baseBuffer;
        ++v4;
        v10->text.baseBuffer[0] = 0;
        ++v9;
      }
      while ( v4 < this->debugText.num );
    }
    v11 = this->debugText.list;
    if ( v11 )
    {
      p_depthTest = &v11[-1].depthTest;
      `eh vector destructor iterator'(
        v11,
        0x70u,
        *(_DWORD *)&v11[-1].depthTest,
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(p_depthTest);
    }
    this->debugText.list = 0;
    this->debugText.num = 0;
    this->debugText.size = 0;
    if ( this->spherePolys.list )
      Memory::Free(this->spherePolys.list);
    this->spherePolys.list = 0;
    this->spherePolys.num = 0;
    this->spherePolys.size = 0;
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DebugPolygon(class idVec4 const &,class idWinding const &,int,bool)
void __thiscall idRenderWorldLocal::DebugPolygon(
        idRenderWorldLocal *this,
        const idVec4 *color,
        const idWinding *winding,
        int lifeTime,
        bool depthTest)
{
  int v6; // eax
  float y; // ecx
  int numPoints; // eax
  int v9; // ecx
  int v10; // eax
  idVec5 *v11; // edx
  idVec5 *v12; // ebx
  int v13; // edx
  bool v14; // zf
  int granularity; // edi
  bool v16; // cc
  int *v17; // eax
  debugPolygon_s *v18; // ebp
  int v19; // ebp
  int v20; // edi
  int num; // ebp
  int size; // edi
  int v23; // edi
  debugPolygon_s *v24; // eax
  int *p_lifeTime; // edi
  debugPolygon_s *list; // ebx
  int *v27; // eax
  debugPolygon_s *v28; // ebp
  int v29; // ebp
  int v30; // edi
  idVec5 *p; // ecx
  debugPolygon_s poly; // [esp+Ch] [ebp-34h] BYREF
  int v33; // [esp+3Ch] [ebp-4h]

  poly.winding.__vftable = (idWinding_vtbl *)&idWinding::`vftable';
  memset(&poly.winding.numPoints, 0, 12);
  v6 = *(_DWORD *)common.type;
  v33 = 0;
  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(v6 + 48))(common.type) )
  {
    y = color->y;
    poly.rgb.x = color->x;
    poly.rgb.z = color->z;
    numPoints = winding->numPoints;
    poly.rgb.y = y;
    poly.rgb.w = color->w;
    if ( numPoints <= poly.winding.allocedSize || poly.winding.ReAllocate(&poly.winding, numPoints, 0) )
    {
      v9 = 0;
      if ( winding->numPoints > 0 )
      {
        v10 = 0;
        do
        {
          v11 = &winding->p[v10];
          v12 = &poly.winding.p[v10];
          v12->x = v11->x;
          v12->y = v11->y;
          v12->z = v11->z;
          v12->s = v11->s;
          ++v9;
          v12->t = v11->t;
          ++v10;
        }
        while ( v9 < winding->numPoints );
      }
      poly.winding.numPoints = winding->numPoints;
    }
    else
    {
      poly.winding.numPoints = 0;
    }
    v13 = lifeTime + this->debugPolyTime;
    v14 = this->debugPolys.list == 0;
    poly.depthTest = depthTest;
    poly.lifeTime = v13;
    if ( v14 )
    {
      granularity = this->debugPolys.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->debugPolys.size )
        {
          v16 = granularity < this->debugPolys.num;
          this->debugPolys.size = granularity;
          if ( v16 )
            this->debugPolys.num = granularity;
          v17 = (int *)Memory::Allocate(40 * granularity + 4);
          LOBYTE(v33) = 1;
          if ( v17 )
          {
            v18 = (debugPolygon_s *)(v17 + 1);
            *v17 = granularity;
            `eh vector constructor iterator'(
              v17 + 1,
              0x28u,
              granularity,
              (void (__thiscall *)(void *))debugPolygon_s::debugPolygon_s,
              (void (__thiscall *)(void *))debugPolygon_s::~debugPolygon_s);
          }
          else
          {
            v18 = 0;
          }
          this->debugPolys.list = v18;
          v19 = 0;
          v16 = this->debugPolys.num <= 0;
          LOBYTE(v33) = 0;
          if ( !v16 )
          {
            v20 = 0;
            do
            {
              debugPolygon_s::operator=(&this->debugPolys.list[v20].rgb.x, v20 * 40);
              ++v19;
              ++v20;
            }
            while ( v19 < this->debugPolys.num );
          }
        }
      }
      else
      {
        this->debugPolys.list = 0;
        this->debugPolys.num = 0;
        this->debugPolys.size = 0;
      }
    }
    num = this->debugPolys.num;
    size = this->debugPolys.size;
    if ( num == size )
    {
      if ( !this->debugPolys.granularity )
        this->debugPolys.granularity = 16;
      v23 = this->debugPolys.granularity + size - (this->debugPolys.granularity + size) % this->debugPolys.granularity;
      if ( v23 > 0 )
      {
        if ( v23 != this->debugPolys.size )
        {
          list = this->debugPolys.list;
          this->debugPolys.size = v23;
          if ( v23 < num )
            this->debugPolys.num = v23;
          v27 = (int *)Memory::Allocate(40 * v23 + 4);
          LOBYTE(v33) = 2;
          if ( v27 )
          {
            v28 = (debugPolygon_s *)(v27 + 1);
            *v27 = v23;
            `eh vector constructor iterator'(
              v27 + 1,
              0x28u,
              v23,
              (void (__thiscall *)(void *))debugPolygon_s::debugPolygon_s,
              (void (__thiscall *)(void *))debugPolygon_s::~debugPolygon_s);
          }
          else
          {
            v28 = 0;
          }
          this->debugPolys.list = v28;
          v29 = 0;
          v16 = this->debugPolys.num <= 0;
          LOBYTE(v33) = 0;
          if ( !v16 )
          {
            v30 = 0;
            do
            {
              debugPolygon_s::operator=(&this->debugPolys.list[v30].rgb.x, (int)&list[v30]);
              ++v29;
              ++v30;
            }
            while ( v29 < this->debugPolys.num );
          }
          if ( list )
          {
            `eh vector destructor iterator'(
              list,
              0x28u,
              list[-1].lifeTime,
              (void (__thiscall *)(void *))debugPolygon_s::~debugPolygon_s);
            Memory::Free(&list[-1].lifeTime);
          }
        }
      }
      else
      {
        v24 = this->debugPolys.list;
        if ( v24 )
        {
          p_lifeTime = &v24[-1].lifeTime;
          `eh vector destructor iterator'(
            v24,
            0x28u,
            v24[-1].lifeTime,
            (void (__thiscall *)(void *))debugPolygon_s::~debugPolygon_s);
          Memory::Free(p_lifeTime);
        }
        this->debugPolys.list = 0;
        this->debugPolys.num = 0;
        this->debugPolys.size = 0;
      }
    }
    debugPolygon_s::operator=(&this->debugPolys.list[this->debugPolys.num].rgb.x, (int)&poly);
    p = poly.winding.p;
    ++this->debugPolys.num;
    v33 = -1;
    poly.winding.__vftable = (idWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(p);
  }
  else
  {
    v33 = -1;
    poly.winding.__vftable = (idWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(poly.winding.p);
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::DrawTextA(char const *,class idVec3 const &,float,class idVec4 const &,class idMat3 const &,int,int,bool)
void __thiscall idRenderWorldLocal::DrawTextA(
        idRenderWorldLocal *this,
        char *text,
        const idVec3 *origin,
        float scale,
        const idVec4 *color,
        const idMat3 *viewAxis,
        int align,
        int lifetime,
        bool depthTest)
{
  int v10; // edx
  float x; // ecx
  float z; // eax
  float v13; // eax
  float y; // ecx
  float v15; // eax
  const idMat3 *v16; // ecx
  float *p_y; // eax
  int v18; // edi
  int v19; // ecx
  bool v20; // zf
  int granularity; // edi
  bool v22; // cc
  int *v23; // eax
  debugText_s *v24; // ebp
  int v25; // ebp
  int v26; // edi
  int num; // ebp
  int size; // edi
  int v29; // edi
  debugText_s *v30; // eax
  bool *p_depthTest; // edi
  debugText_s *list; // ebx
  int *v33; // eax
  debugText_s *v34; // ebp
  int v35; // ebp
  int v36; // edi
  debugText_s dt; // [esp+Ch] [ebp-7Ch] BYREF
  int v38; // [esp+84h] [ebp-4h]

  dt.text.len = 0;
  dt.text.alloced = 20;
  dt.text.data = dt.text.baseBuffer;
  dt.text.baseBuffer[0] = 0;
  v10 = *(_DWORD *)common.type;
  v38 = 0;
  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(v10 + 48))(common.type) )
  {
    idStr::operator=(&dt.text, text);
    x = origin->x;
    z = origin->z;
    dt.origin.y = origin->y;
    dt.origin.x = x;
    dt.origin.z = z;
    v13 = color->x;
    dt.scale = scale;
    y = color->y;
    dt.color.x = v13;
    v15 = color->z;
    dt.color.y = y;
    dt.color.w = color->w;
    v16 = viewAxis;
    dt.color.z = v15;
    p_y = &dt.viewAxis.mat[0].y;
    v18 = 3;
    do
    {
      *(p_y - 1) = v16->mat[0].x;
      *p_y = *(float *)((char *)p_y + (char *)viewAxis - (char *)&dt.viewAxis);
      p_y[1] = v16->mat[0].z;
      v16 = (const idMat3 *)((char *)v16 + 12);
      p_y += 3;
      --v18;
    }
    while ( v18 );
    v19 = lifetime + this->debugTextTime;
    v20 = this->debugText.list == 0;
    dt.align = align;
    dt.depthTest = depthTest;
    dt.lifeTime = v19;
    if ( v20 )
    {
      granularity = this->debugText.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->debugText.size )
        {
          v22 = granularity < this->debugText.num;
          this->debugText.size = granularity;
          if ( v22 )
            this->debugText.num = granularity;
          v23 = (int *)Memory::Allocate(112 * granularity + 4);
          LOBYTE(v38) = 1;
          if ( v23 )
          {
            v24 = (debugText_s *)(v23 + 1);
            *v23 = granularity;
            `eh vector constructor iterator'(
              v23 + 1,
              0x70u,
              granularity,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v24 = 0;
          }
          this->debugText.list = v24;
          v25 = 0;
          v22 = this->debugText.num <= 0;
          LOBYTE(v38) = 0;
          if ( !v22 )
          {
            v26 = 0;
            do
            {
              debugText_s::operator=((int)&this->debugText.list[v26], v26 * 112);
              ++v25;
              ++v26;
            }
            while ( v25 < this->debugText.num );
          }
        }
      }
      else
      {
        this->debugText.list = 0;
        this->debugText.num = 0;
        this->debugText.size = 0;
      }
    }
    num = this->debugText.num;
    size = this->debugText.size;
    if ( num == size )
    {
      if ( !this->debugText.granularity )
        this->debugText.granularity = 16;
      v29 = this->debugText.granularity + size - (this->debugText.granularity + size) % this->debugText.granularity;
      if ( v29 > 0 )
      {
        if ( v29 != this->debugText.size )
        {
          list = this->debugText.list;
          this->debugText.size = v29;
          if ( v29 < num )
            this->debugText.num = v29;
          v33 = (int *)Memory::Allocate(112 * v29 + 4);
          LOBYTE(v38) = 2;
          if ( v33 )
          {
            v34 = (debugText_s *)(v33 + 1);
            *v33 = v29;
            `eh vector constructor iterator'(
              v33 + 1,
              0x70u,
              v29,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v34 = 0;
          }
          this->debugText.list = v34;
          v35 = 0;
          v22 = this->debugText.num <= 0;
          LOBYTE(v38) = 0;
          if ( !v22 )
          {
            v36 = 0;
            do
            {
              debugText_s::operator=((int)&this->debugText.list[v36], (int)&list[v36]);
              ++v35;
              ++v36;
            }
            while ( v35 < this->debugText.num );
          }
          if ( list )
          {
            `eh vector destructor iterator'(
              list,
              0x70u,
              *(_DWORD *)&list[-1].depthTest,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(&list[-1].depthTest);
          }
        }
      }
      else
      {
        v30 = this->debugText.list;
        if ( v30 )
        {
          p_depthTest = &v30[-1].depthTest;
          `eh vector destructor iterator'(
            v30,
            0x70u,
            *(_DWORD *)&v30[-1].depthTest,
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(p_depthTest);
        }
        this->debugText.list = 0;
        this->debugText.num = 0;
        this->debugText.size = 0;
      }
    }
    debugText_s::operator=((int)&this->debugText.list[this->debugText.num], (int)&dt);
    ++this->debugText.num;
    v38 = -1;
    idStr::FreeData(&dt.text);
  }
  else
  {
    v38 = -1;
    idStr::FreeData(&dt.text);
  }
}

// FUNC: public: virtual __thiscall idRenderWorldLocal::~idRenderWorldLocal(void)
void __thiscall idRenderWorldLocal::~idRenderWorldLocal(idRenderWorldLocal *this)
{
  triangle_s *list; // eax
  debugText_s *v3; // eax
  bool *p_depthTest; // edi
  debugPolygon_s *v5; // eax
  int *p_lifeTime; // edi
  debugLine_s *v7; // eax
  int *v8; // eax
  int *v9; // eax
  int *v10; // eax
  rvRenderEffectLocal **v11; // eax
  idRenderLightLocal **v12; // eax
  idRenderEntityLocal **v13; // eax
  idRenderModel **v14; // eax

  this->__vftable = (idRenderWorldLocal_vtbl *)&idRenderWorldLocal::`vftable';
  idRenderWorldLocal::FreeWorld(this);
  idRenderWorldLocal::DebugClear(this, 0);
  idStr::FreeData(&this->m_filename);
  list = this->spherePolys.list;
  if ( list )
    Memory::Free(list);
  this->spherePolys.list = 0;
  this->spherePolys.num = 0;
  this->spherePolys.size = 0;
  v3 = this->debugText.list;
  if ( v3 )
  {
    p_depthTest = &v3[-1].depthTest;
    `eh vector destructor iterator'(
      v3,
      0x70u,
      *(_DWORD *)&v3[-1].depthTest,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(p_depthTest);
  }
  this->debugText.list = 0;
  this->debugText.num = 0;
  this->debugText.size = 0;
  v5 = this->debugPolys.list;
  if ( v5 )
  {
    p_lifeTime = &v5[-1].lifeTime;
    `eh vector destructor iterator'(
      v5,
      0x28u,
      v5[-1].lifeTime,
      (void (__thiscall *)(void *))debugPolygon_s::~debugPolygon_s);
    Memory::Free(p_lifeTime);
  }
  this->debugPolys.list = 0;
  this->debugPolys.num = 0;
  this->debugPolys.size = 0;
  v7 = this->debugLines.list;
  if ( v7 )
    Memory::Free(v7);
  this->debugLines.list = 0;
  this->debugLines.num = 0;
  this->debugLines.size = 0;
  idBlockAlloc<areaNumRef_s,1024,16>::Shutdown(&this->areaNumRefAllocator);
  idBlockAlloc<idInteraction,256,16>::Shutdown(&this->interactionAllocator);
  idBlockAlloc<areaReference_s,1024,16>::Shutdown(&this->areaReferenceAllocator);
  v8 = this->markedEffectDefs.list;
  if ( v8 )
    Memory::Free(v8);
  this->markedEffectDefs.list = 0;
  this->markedEffectDefs.num = 0;
  this->markedEffectDefs.size = 0;
  v9 = this->markedLightDefs.list;
  if ( v9 )
    Memory::Free(v9);
  this->markedLightDefs.list = 0;
  this->markedLightDefs.num = 0;
  this->markedLightDefs.size = 0;
  v10 = this->markedEntityDefs.list;
  if ( v10 )
    Memory::Free(v10);
  this->markedEntityDefs.list = 0;
  this->markedEntityDefs.num = 0;
  this->markedEntityDefs.size = 0;
  v11 = this->effectDefs.list;
  if ( v11 )
    Memory::Free(v11);
  this->effectDefs.list = 0;
  this->effectDefs.num = 0;
  this->effectDefs.size = 0;
  v12 = this->lightDefs.list;
  if ( v12 )
    Memory::Free(v12);
  this->lightDefs.list = 0;
  this->lightDefs.num = 0;
  this->lightDefs.size = 0;
  v13 = this->entityDefs.list;
  if ( v13 )
    Memory::Free(v13);
  this->entityDefs.list = 0;
  this->entityDefs.num = 0;
  this->entityDefs.size = 0;
  v14 = this->localModels.list;
  if ( v14 )
    Memory::Free(v14);
  this->localModels.list = 0;
  this->localModels.num = 0;
  this->localModels.size = 0;
  idStr::FreeData(&this->mapName);
  this->__vftable = (idRenderWorldLocal_vtbl *)&idRenderWorld::`vftable';
}
