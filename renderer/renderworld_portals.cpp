
// FUNC: public: void __thiscall idRenderWorldLocal::BuildConnectedAreas_r(int)
void __thiscall idRenderWorldLocal::BuildConnectedAreas_r(idRenderWorldLocal *this, int areaNum)
{
  bool *v3; // ecx
  portal_s *i; // esi

  v3 = &tr.viewDef->connectedAreas[areaNum];
  if ( !*v3 )
  {
    *v3 = 1;
    for ( i = this->portalAreas[areaNum].portals; i; i = i->next )
    {
      if ( (i->doublePortal->blockingBits & 1) == 0 )
        idRenderWorldLocal::BuildConnectedAreas_r(this, i->intoArea);
    }
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::BuildConnectedAreas(void)
void __thiscall idRenderWorldLocal::BuildConnectedAreas(idRenderWorldLocal *this)
{
  viewDef_s *viewDef; // edx
  int v3; // eax

  tr.viewDef->connectedAreas = (bool *)R_FrameAlloc(this->numPortalAreas);
  viewDef = tr.viewDef;
  v3 = 0;
  if ( tr.viewDef->areaNum == -1 )
  {
    if ( this->numPortalAreas > 0 )
    {
      while ( 1 )
      {
        viewDef->connectedAreas[v3] = 1;
        if ( ++v3 >= this->numPortalAreas )
          break;
        viewDef = tr.viewDef;
      }
    }
  }
  else
  {
    memset(tr.viewDef->connectedAreas, 0, this->numPortalAreas);
    idRenderWorldLocal::BuildConnectedAreas_r(this, tr.viewDef->areaNum);
  }
}

// FUNC: public: virtual int __thiscall idRenderWorldLocal::NumPortals(void)const
char *__thiscall idRenderWorldLocal::NumPortals(idRenderModelStatic *this)
{
  return this->name.data;
}

// FUNC: public: void __thiscall idRenderWorldLocal::FloodConnectedAreas(struct portalArea_s *,int)
void __thiscall idRenderWorldLocal::FloodConnectedAreas(
        idRenderWorldLocal *this,
        portalArea_s *area,
        int portalAttributeIndex)
{
  int connectedAreaNum; // ecx
  portal_s *i; // esi

  connectedAreaNum = this->connectedAreaNum;
  if ( area->connectedAreaNum[portalAttributeIndex] != connectedAreaNum )
  {
    area->connectedAreaNum[portalAttributeIndex] = connectedAreaNum;
    for ( i = area->portals; i; i = i->next )
    {
      if ( ((1 << portalAttributeIndex) & i->doublePortal->blockingBits) == 0 )
        idRenderWorldLocal::FloodConnectedAreas(this, &this->portalAreas[i->intoArea], portalAttributeIndex);
    }
  }
}

// FUNC: public: virtual bool __thiscall idRenderWorldLocal::AreasAreConnected(int,int,enum portalConnection_t)
bool __thiscall idRenderWorldLocal::AreasAreConnected(
        idRenderWorldLocal *this,
        int areaNum1,
        int areaNum2,
        int connection)
{
  int numPortalAreas; // eax
  int v6; // esi
  int v7; // eax

  if ( areaNum1 == -1 || areaNum2 == -1 )
    return 0;
  numPortalAreas = this->numPortalAreas;
  if ( areaNum1 > numPortalAreas || areaNum2 > numPortalAreas || areaNum1 < 0 || areaNum2 < 0 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorldLocal::AreAreasConnected: bad parms: %i, %i",
      areaNum1,
      areaNum2);
  v6 = 0;
  v7 = connection;
  if ( connection > 1 )
  {
    do
    {
      v7 >>= 1;
      ++v6;
    }
    while ( v7 > 1 );
    if ( v6 >= 4 )
      goto LABEL_12;
  }
  if ( 1 << v6 != connection )
LABEL_12:
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idRenderWorldLocal::AreasAreConnected: bad connection number: %i\n",
      connection);
  return this->portalAreas[areaNum1].connectedAreaNum[v6] == this->portalAreas[areaNum2].connectedAreaNum[v6];
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::SetPortalState(int,int)
void __thiscall idRenderWorldLocal::SetPortalState(idRenderWorldLocal *this, int portal, int blockTypes)
{
  doublePortal_s *doublePortals; // edx
  int v5; // ebx
  int blockingBits; // ecx
  int v8; // edi
  int v9; // eax
  doublePortal_s *v10; // eax
  int blockTypesa; // [esp+10h] [ebp+8h]

  if ( portal )
  {
    if ( portal < 1 || portal > this->numInterAreaPortals )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "SetPortalState: bad portal number %i",
        portal);
    doublePortals = this->doublePortals;
    v5 = portal;
    blockingBits = doublePortals[portal - 1].blockingBits;
    if ( blockingBits != blockTypes )
    {
      doublePortals[v5 - 1].blockingBits = blockTypes;
      v8 = 0;
      v9 = blockTypes ^ blockingBits;
      blockTypesa = blockTypes ^ blockingBits;
      do
      {
        if ( ((1 << v8) & v9) != 0 )
        {
          v10 = this->doublePortals;
          ++this->connectedAreaNum;
          idRenderWorldLocal::FloodConnectedAreas(this, &this->portalAreas[v10[v5 - 1].portals[1]->intoArea], v8);
          v9 = blockTypesa;
        }
        ++v8;
      }
      while ( v8 < 4 );
      if ( session->writeDemo )
      {
        session->writeDemo->WriteChar(session->writeDemo, 1);
        session->writeDemo->WriteChar(session->writeDemo, 19);
        session->writeDemo->WriteInt(session->writeDemo, portal);
        session->writeDemo->WriteInt(session->writeDemo, blockTypes);
      }
    }
  }
}

// FUNC: public: virtual int __thiscall idRenderWorldLocal::GetPortalState(int)
int __thiscall idRenderWorldLocal::GetPortalState(idRenderWorldLocal *this, int portal)
{
  if ( !portal )
    return 0;
  if ( portal < 1 || portal > this->numInterAreaPortals )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "GetPortalState: bad portal number %i",
      portal);
  return this->doublePortals[portal - 1].blockingBits;
}

// FUNC: public: class idScreenRect __thiscall idRenderWorldLocal::ScreenRectFromWinding(class idWinding const *,struct viewEntity_s *)
idScreenRect *__thiscall idRenderWorldLocal::ScreenRectFromWinding(
        idRenderWorldLocal *this,
        idScreenRect *result,
        const idWinding *w,
        viewEntity_s *space)
{
  int v4; // edi
  int v5; // esi
  idScreenRect *v6; // eax
  float x; // [esp+0h] [ebp-40h]
  float y; // [esp+4h] [ebp-3Ch]
  idVec3 ndc; // [esp+18h] [ebp-28h] BYREF
  idVec3 v; // [esp+24h] [ebp-1Ch] BYREF
  idScreenRect r; // [esp+30h] [ebp-10h] BYREF

  idScreenRect::Clear(&r);
  v4 = 0;
  if ( w->numPoints > 0 )
  {
    v5 = 0;
    do
    {
      R_LocalPointToGlobal(space->modelMatrix, (const idVec3 *)&w->p[v5], &v);
      R_GlobalToNormalizedDeviceCoordinates(
        tr.viewDef->worldSpace.modelViewMatrix,
        tr.viewDef->projectionMatrix,
        &v,
        &ndc);
      y = (double)(tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1) * (ndc.y + 1.0) * 0.5;
      x = (double)(tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1) * (ndc.x + 1.0) * 0.5;
      idScreenRect::AddPoint(&r, x, y);
      ++v4;
      ++v5;
    }
    while ( v4 < w->numPoints );
  }
  idScreenRect::Expand(&r);
  v6 = result;
  *result = r;
  return v6;
}

// FUNC: public: bool __thiscall idRenderWorldLocal::PortalIsFoggedOut(struct portal_s const *)
char __thiscall idRenderWorldLocal::PortalIsFoggedOut(idRenderWorldLocal *this, const portal_s *p)
{
  idRenderLightLocal *fogLight; // esi
  idMaterial *lightShader; // edi
  int v4; // eax
  void *v5; // esp
  double v6; // st7
  double v7; // st7
  int v8; // ecx
  idWinding *w; // eax
  int numPoints; // edx
  float *i; // esi
  float v13[3]; // [esp+0h] [ebp-1Ch] BYREF
  idPlane forward; // [esp+Ch] [ebp-10h]

  fogLight = p->doublePortal->fogLight;
  if ( fogLight )
  {
    lightShader = (idMaterial *)fogLight->lightShader;
    v4 = 4 * lightShader->numRegisters + 3;
    LOBYTE(v4) = v4 & 0xFC;
    v5 = alloca(v4);
    idMaterial::EvaluateRegisters(
      lightShader,
      v13,
      fogLight->parms.shaderParms,
      tr.viewDef,
      fogLight->parms.referenceSoundHandle,
      0);
    v6 = v13[lightShader->stages->color.registers[3]];
    if ( v6 > 1.0 )
      v7 = -0.5 / v6;
    else
      v7 = -0.001;
    v8 = 0;
    forward.a = v7 * tr.viewDef->worldSpace.modelViewMatrix[2];
    forward.b = v7 * tr.viewDef->worldSpace.modelViewMatrix[6];
    forward.c = v7 * tr.viewDef->worldSpace.modelViewMatrix[10];
    w = p->w;
    numPoints = w->numPoints;
    forward.d = v7 * tr.viewDef->worldSpace.modelViewMatrix[14];
    if ( numPoints <= 0 )
      return 1;
    for ( i = &w->p->x; forward.c * i[2] + forward.b * i[1] + forward.a * *i + forward.d >= 0.5; i += 5 )
    {
      if ( ++v8 >= numPoints )
        return 1;
    }
  }
  return 0;
}

// FUNC: public: struct areaNumRef_s * __thiscall idRenderWorldLocal::FloodFrustumAreas_r(class idFrustum const &,int,class idBounds const &,struct areaNumRef_s *)
areaNumRef_s *__thiscall idRenderWorldLocal::FloodFrustumAreas_r(
        idRenderWorldLocal *this,
        idFrustum *frustum,
        int areaNum,
        const idBounds *bounds,
        areaNumRef_s *areas)
{
  portal_s *portals; // esi
  areaNumRef_s *v6; // ebp
  areaNumRef_s *v7; // eax
  double v8; // st7
  areaNumRef_s *v9; // eax
  idBounds newBounds; // [esp+8h] [ebp-18h] BYREF

  portals = this->portalAreas[areaNum].portals;
  if ( !portals )
    return areas;
  v6 = areas;
  do
  {
    v7 = v6;
    if ( v6 )
    {
      while ( v7->areaNum != portals->intoArea )
      {
        v7 = v7->next;
        if ( !v7 )
          goto LABEL_6;
      }
    }
    else
    {
LABEL_6:
      v8 = portals->plane.c * frustum->origin.z
         + portals->plane.b * frustum->origin.y
         + portals->plane.a * frustum->origin.x
         + portals->plane.d;
      if ( (v8 > 0.1 || v8 >= -0.1) && idFrustum::PlaneSide(frustum, &portals->plane, 0.0) == 3 )
      {
        idFrustum::ProjectionBounds(frustum, portals->w, &newBounds);
        if ( bounds->b[0].x > (double)newBounds.b[0].x )
          newBounds.b[0].x = bounds->b[0].x;
        if ( bounds->b[0].y > (double)newBounds.b[0].y )
          newBounds.b[0].y = bounds->b[0].y;
        if ( bounds->b[0].z > (double)newBounds.b[0].z )
          newBounds.b[0].z = bounds->b[0].z;
        if ( bounds->b[1].x < (double)newBounds.b[1].x )
          newBounds.b[1].x = bounds->b[1].x;
        if ( bounds->b[1].y < (double)newBounds.b[1].y )
          newBounds.b[1].y = bounds->b[1].y;
        if ( bounds->b[1].z < (double)newBounds.b[1].z )
          newBounds.b[1].z = bounds->b[1].z;
        if ( newBounds.b[0].x <= (double)newBounds.b[1].x
          && newBounds.b[0].y <= (double)newBounds.b[1].y
          && newBounds.b[0].z <= (double)newBounds.b[1].z )
        {
          newBounds.b[1].x = frustum->dFar;
          v9 = idBlockAlloc<areaNumRef_s,1024,16>::Alloc(&this->areaNumRefAllocator);
          v9->areaNum = portals->intoArea;
          v9->next = v6;
          v6 = idRenderWorldLocal::FloodFrustumAreas_r(this, frustum, portals->intoArea, &newBounds, v9);
        }
      }
    }
    portals = portals->next;
  }
  while ( portals );
  return v6;
}

// FUNC: public: struct areaNumRef_s * __thiscall idRenderWorldLocal::FloodFrustumAreas(class idFrustum const &,struct areaNumRef_s *)
areaNumRef_s *__thiscall idRenderWorldLocal::FloodFrustumAreas(
        idRenderWorldLocal *this,
        idFrustum *frustum,
        areaNumRef_s *areas)
{
  areaNumRef_s *result; // eax
  float dFar; // ecx
  areaNumRef_s *i; // esi
  idBounds bounds; // [esp+Ch] [ebp-18h] BYREF

  bounds.b[0].x = frustum->dNear;
  result = areas;
  dFar = frustum->dFar;
  bounds.b[0].y = -1.0;
  bounds.b[0].z = -1.0;
  bounds.b[1].x = dFar;
  bounds.b[1].y = 1.0;
  bounds.b[1].z = 1.0;
  for ( i = areas; i; i = i->next )
    result = idRenderWorldLocal::FloodFrustumAreas_r(this, frustum, i->areaNum, &bounds, result);
  return result;
}

// FUNC: public: void __thiscall idRenderWorldLocal::AddAreaEntityRefs(int,struct portalStack_s const *)
void __thiscall idRenderWorldLocal::AddAreaEntityRefs(idRenderWorldLocal *this, int areaNum, const portalStack_s *ps)
{
  areaReference_s *p_entityRefs; // ebp
  areaReference_s *i; // edi
  int integerValue; // eax
  idRenderEntityLocal *entity; // esi
  int suppressSurfaceInViewID; // eax
  int allowSurfaceInViewID; // eax
  viewEntity_s *v9; // eax

  p_entityRefs = &this->portalAreas[areaNum].entityRefs;
  for ( i = p_entityRefs->areaNext; i != p_entityRefs; i = i->areaNext )
  {
    integerValue = r_singleEntity.internalVar->integerValue;
    entity = i->entity;
    if ( (integerValue < 0 || integerValue == entity->index)
      && (r_skipSuppress.internalVar->integerValue
       || ((suppressSurfaceInViewID = entity->parms.suppressSurfaceInViewID) == 0
        || suppressSurfaceInViewID != tr.viewDef->renderView.viewID)
       && ((allowSurfaceInViewID = entity->parms.allowSurfaceInViewID) == 0
        || allowSurfaceInViewID == tr.viewDef->renderView.viewID))
      && (!r_useEntityCulling.internalVar->integerValue
       || !R_CullLocalBox(&entity->referenceBounds, entity->modelMatrix, ps->numPortalPlanes, ps->portalPlanes)) )
    {
      v9 = R_SetEntityDefViewEntity(entity);
      idScreenRect::Union(&v9->scissorRect, &ps->rect);
    }
  }
}

// FUNC: public: bool __thiscall idRenderWorldLocal::CullLightByPortals(class idRenderLightLocal const *,struct portalStack_s const *)
char __thiscall idRenderWorldLocal::CullLightByPortals(
        idRenderWorldLocal *this,
        const idRenderLightLocal *light,
        const portalStack_s *ps)
{
  int v3; // edi
  int integerValue; // eax
  const portalStack_s *v6; // ebx
  float *p_b; // ebp
  idWinding *v8; // esi
  int numPoints; // eax
  int v10; // ecx
  int v11; // eax
  float *p_x; // edx
  idVec5 *v13; // ebx
  float *p_c; // esi
  double v15; // st7
  double v16; // st6
  double v17; // st5
  bool v18; // cc
  int v19; // ebx
  int v20; // ebp
  int numVerts; // edi
  float *v22; // esi
  int v23; // edx
  idDrawVert *verts; // ecx
  const srfTriangles_s *tri; // [esp+4h] [ebp-538h]
  idWinding **frustumWindings; // [esp+8h] [ebp-534h]
  int i; // [esp+Ch] [ebp-530h]
  idPlane plane; // [esp+10h] [ebp-52Ch] BYREF
  idFixedWinding w; // [esp+20h] [ebp-51Ch] BYREF
  int v30; // [esp+538h] [ebp-4h]

  v3 = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  integerValue = r_useLightCulling.internalVar->integerValue;
  v30 = 0;
  if ( integerValue )
  {
    if ( integerValue >= 2 )
    {
      v6 = ps;
      p_b = &light->frustum[0].b;
      i = 0;
      frustumWindings = light->frustumWindings;
      tri = (const srfTriangles_s *)&light->frustum[0].b;
      while ( 1 )
      {
        if ( p_b[1] * tr.viewDef->renderView.vieworg.z
           + *(p_b - 1) * tr.viewDef->renderView.vieworg.x
           + tr.viewDef->renderView.vieworg.y * *p_b
           + p_b[2] < 0.0 )
        {
          v8 = *frustumWindings;
          if ( *frustumWindings )
          {
            numPoints = v8->numPoints;
            if ( numPoints <= w.allocedSize || w.ReAllocate(&w, numPoints, 0) )
            {
              v10 = 0;
              if ( v8->numPoints > 0 )
              {
                v11 = 0;
                do
                {
                  p_x = &v8->p[v11].x;
                  v13 = &w.p[v11];
                  v13->x = *p_x;
                  v13->y = p_x[1];
                  v13->z = p_x[2];
                  v13->s = p_x[3];
                  ++v10;
                  v13->t = p_x[4];
                  ++v11;
                }
                while ( v10 < v8->numPoints );
                p_b = (float *)tri;
                v6 = ps;
              }
              w.numPoints = v8->numPoints;
            }
            else
            {
              w.numPoints = 0;
            }
            if ( v6->numPortalPlanes - 1 > 0 )
            {
              p_c = &v6->portalPlanes[0].c;
              do
              {
                v15 = -p_c[1];
                v16 = -*p_c;
                v17 = -*(p_c - 1);
                plane.a = -*(p_c - 2);
                plane.b = v17;
                plane.c = v16;
                plane.d = v15;
                if ( !idWinding::ClipInPlace(&w, &plane, 0.1, 0) )
                  break;
                ++v3;
                p_c += 4;
              }
              while ( v3 < v6->numPortalPlanes - 1 );
            }
            if ( w.numPoints )
            {
              w.p = 0;
              goto LABEL_33;
            }
            v3 = 0;
          }
        }
        ++frustumWindings;
        p_b += 4;
        v18 = ++i < 6;
        tri = (const srfTriangles_s *)p_b;
        if ( !v18 )
        {
          v30 = -1;
          w.p = 0;
          w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
          Memory::Free(0);
          return 1;
        }
      }
    }
    v19 = ps->numPortalPlanes - 1;
    v20 = 0;
    if ( v19 <= 0 )
    {
LABEL_32:
      w.p = 0;
LABEL_33:
      w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
      v30 = -1;
      Memory::Free(0);
      return 0;
    }
    else
    {
      numVerts = light->frustumTris->numVerts;
      v22 = &ps->portalPlanes[0].b;
      while ( 1 )
      {
        v23 = 0;
        if ( numVerts > 0 )
        {
          verts = light->frustumTris->verts;
          do
          {
            if ( verts->xyz.z * v22[1] + verts->xyz.y * *v22 + verts->xyz.x * *(v22 - 1) + v22[2] < 0.0 )
              break;
            ++v23;
            ++verts;
          }
          while ( v23 < numVerts );
        }
        if ( v23 == numVerts )
          break;
        ++v20;
        v22 += 4;
        if ( v20 >= v19 )
          goto LABEL_32;
      }
      ++tr.pc.c_box_cull_out;
      v30 = -1;
      Memory::Free(0);
      return 1;
    }
  }
  else
  {
    v30 = -1;
    w.p = 0;
    w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(0);
    return 0;
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::AddAreaEffectRefs(int,struct portalStack_s const *)
void __thiscall idRenderWorldLocal::AddAreaEffectRefs(idRenderWorldLocal *this, int areaNum, const portalStack_s *ps)
{
  areaReference_s *p_effectRefs; // ebp
  areaReference_s *i; // edi
  rvRenderEffectLocal *effect; // esi
  int suppressSurfaceInViewID; // eax
  int allowSurfaceInViewID; // eax
  viewEffect_s *v8; // eax

  p_effectRefs = &this->portalAreas[areaNum].effectRefs;
  for ( i = p_effectRefs->areaNext; i != p_effectRefs; i = i->areaNext )
  {
    effect = i->effect;
    if ( !r_skipSuppress.internalVar->integerValue )
    {
      suppressSurfaceInViewID = effect->parms.suppressSurfaceInViewID;
      if ( suppressSurfaceInViewID )
      {
        if ( suppressSurfaceInViewID == tr.viewDef->renderView.viewID )
          continue;
      }
      allowSurfaceInViewID = effect->parms.allowSurfaceInViewID;
      if ( allowSurfaceInViewID )
      {
        if ( allowSurfaceInViewID != tr.viewDef->renderView.viewID )
          continue;
      }
    }
    if ( !r_useEntityCulling.internalVar->integerValue
      || !R_CullLocalBox(&effect->referenceBounds, effect->modelMatrix, ps->numPortalPlanes, ps->portalPlanes) )
    {
      v8 = R_SetEffectDefViewEntity(effect);
      idScreenRect::Union(&v8->scissorRect, &ps->rect);
    }
  }
}

// FUNC: public: virtual int __thiscall idRenderWorldLocal::FindPortal(class idBounds const &)const
int __thiscall idRenderWorldLocal::FindPortal(idRenderWorldLocal *this, const idBounds *b)
{
  int v2; // esi
  double v3; // st7
  idWinding *w; // ebp
  int numPoints; // edi
  int v6; // ebx
  idVec5 *p; // eax
  unsigned int v8; // esi
  float *p_z; // ecx
  float *v10; // edx
  float *p_x; // ecx
  int v12; // edx
  doublePortal_s *j; // [esp+10h] [ebp-28h]
  int i; // [esp+14h] [ebp-24h]
  int numInterAreaPortals; // [esp+1Ch] [ebp-1Ch]
  float wb_4; // [esp+24h] [ebp-14h]
  float wb_8; // [esp+28h] [ebp-10h]
  float wb_12; // [esp+2Ch] [ebp-Ch]
  float wb_16; // [esp+30h] [ebp-8h]
  float wb_20; // [esp+34h] [ebp-4h]

  v2 = 0;
  i = 0;
  numInterAreaPortals = this->numInterAreaPortals;
  if ( numInterAreaPortals <= 0 )
    return 0;
  for ( j = this->doublePortals; ; ++j )
  {
    v3 = 1.0e30;
    w = j->portals[0]->w;
    numPoints = w->numPoints;
    wb_8 = idMath::INFINITY;
    wb_4 = idMath::INFINITY;
    v6 = 0;
    wb_20 = -1.0e30;
    wb_16 = wb_20;
    wb_12 = wb_20;
    if ( numPoints >= 4 )
    {
      p = w->p;
      v8 = ((unsigned int)(numPoints - 4) >> 2) + 1;
      p_z = &p->z;
      v10 = &p[1].z;
      v6 = 4 * v8;
      do
      {
        if ( v3 > *(p_z - 2) )
          v3 = *(p_z - 2);
        if ( *(p_z - 2) > (double)wb_12 )
          wb_12 = *(p_z - 2);
        if ( *(p_z - 1) < (double)wb_4 )
          wb_4 = *(p_z - 1);
        if ( *(p_z - 1) > (double)wb_16 )
          wb_16 = *(p_z - 1);
        if ( *p_z < (double)wb_8 )
          wb_8 = *p_z;
        if ( *p_z > (double)wb_20 )
          wb_20 = *p_z;
        if ( v3 > p_z[3] )
          v3 = p_z[3];
        if ( p_z[3] > (double)wb_12 )
          wb_12 = p_z[3];
        if ( *(v10 - 1) < (double)wb_4 )
          wb_4 = *(v10 - 1);
        if ( *(v10 - 1) > (double)wb_16 )
          wb_16 = *(v10 - 1);
        if ( *v10 < (double)wb_8 )
          wb_8 = *v10;
        if ( *v10 > (double)wb_20 )
          wb_20 = *v10;
        if ( v3 > p_z[8] )
          v3 = p_z[8];
        if ( p_z[8] > (double)wb_12 )
          wb_12 = p_z[8];
        if ( v10[4] < (double)wb_4 )
          wb_4 = v10[4];
        if ( v10[4] > (double)wb_16 )
          wb_16 = v10[4];
        if ( v10[5] < (double)wb_8 )
          wb_8 = v10[5];
        if ( v10[5] > (double)wb_20 )
          wb_20 = v10[5];
        if ( v3 > p_z[13] )
          v3 = p_z[13];
        if ( p_z[13] > (double)wb_12 )
          wb_12 = p_z[13];
        if ( v10[9] < (double)wb_4 )
          wb_4 = v10[9];
        if ( v10[9] > (double)wb_16 )
          wb_16 = v10[9];
        if ( v10[10] < (double)wb_8 )
          wb_8 = v10[10];
        if ( v10[10] > (double)wb_20 )
          wb_20 = v10[10];
        p_z += 20;
        v10 += 20;
        --v8;
      }
      while ( v8 );
      v2 = i;
    }
    if ( v6 < numPoints )
    {
      p_x = &w->p[v6].x;
      v12 = numPoints - v6;
      do
      {
        if ( v3 > *p_x )
          v3 = *p_x;
        if ( *p_x > (double)wb_12 )
          wb_12 = *p_x;
        if ( p_x[1] < (double)wb_4 )
          wb_4 = p_x[1];
        if ( p_x[1] > (double)wb_16 )
          wb_16 = p_x[1];
        if ( p_x[2] < (double)wb_8 )
          wb_8 = p_x[2];
        if ( p_x[2] > (double)wb_20 )
          wb_20 = p_x[2];
        p_x += 5;
        --v12;
      }
      while ( v12 );
    }
    if ( v3 <= b->b[1].x
      && b->b[1].y >= (double)wb_4
      && b->b[1].z >= (double)wb_8
      && b->b[0].x <= (double)wb_12
      && b->b[0].y <= (double)wb_16
      && b->b[0].z <= (double)wb_20 )
    {
      break;
    }
    i = ++v2;
    if ( v2 >= numInterAreaPortals )
      return 0;
  }
  return v2 + 1;
}

// FUNC: public: void __thiscall idRenderWorldLocal::ShowPortals(void)
void __thiscall idRenderWorldLocal::ShowPortals(idRenderWorldLocal *this)
{
  idRenderWorldLocal *v1; // ebx
  int viewCount; // ecx
  portalArea_s *v3; // eax
  portal_s *j; // ebp
  idWinding *w; // esi
  int v6; // edi
  int v7; // ebx
  int v8; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]

  v1 = this;
  i = 0;
  if ( this->numPortalAreas > 0 )
  {
    viewCount = tr.viewCount;
    v8 = 0;
    do
    {
      v3 = &v1->portalAreas[v8];
      if ( v3->viewCount == viewCount )
      {
        for ( j = v3->portals; j; j = j->next )
        {
          w = j->w;
          if ( w )
          {
            if ( v1->portalAreas[j->intoArea].viewCount == viewCount )
              qglColor3f(0.0, 1.0, 0.0);
            else
              qglColor3f(1.0, 0.0, 0.0);
            qglBegin(2u);
            v6 = 0;
            if ( w->numPoints > 0 )
            {
              v7 = 0;
              do
              {
                qglVertex3fv(&w->p[v7].x);
                ++v6;
                ++v7;
              }
              while ( v6 < w->numPoints );
              v1 = this;
            }
            qglEnd();
            viewCount = tr.viewCount;
          }
        }
      }
      ++v8;
      ++i;
    }
    while ( i < v1->numPortalAreas );
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::FindVisibleAreas_r(class idVec3,int,bool *)
void __thiscall idRenderWorldLocal::FindVisibleAreas_r(
        idRenderWorldLocal *this,
        idVec3 origin,
        int areaNum,
        bool *visibleAreas)
{
  portal_s *i; // esi

  visibleAreas[areaNum] = 1;
  for ( i = this->portalAreas[areaNum].portals; i; i = i->next )
  {
    if ( !visibleAreas[i->intoArea]
      && (i->doublePortal->blockingBits & 1) == 0
      && origin.y * i->plane.b + origin.z * i->plane.c + origin.x * i->plane.a + i->plane.d >= -0.1 )
    {
      idRenderWorldLocal::FindVisibleAreas_r(this, origin, i->intoArea, visibleAreas);
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::FindVisibleAreas(class idVec3,int,bool *)
void __thiscall idRenderWorldLocal::FindVisibleAreas(
        idRenderWorldLocal *this,
        idVec3 origin,
        int areaNum,
        bool *visibleAreas)
{
  int i; // eax

  if ( areaNum >= 0 )
  {
    idRenderWorldLocal::FindVisibleAreas_r(this, origin, areaNum, visibleAreas);
  }
  else
  {
    for ( i = 0; i < this->numPortalAreas; ++i )
      visibleAreas[i] = 1;
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::RenderPortalFades(void)
void __thiscall idRenderWorldLocal::RenderPortalFades(idRenderWorldLocal *this)
{
  idRenderWorldLocal *v1; // ebp
  const viewDef_s *viewDef; // ecx
  portalArea_s *v3; // eax
  portal_s *k; // ebx
  idWinding *w; // edi
  double v6; // st7
  float *p_x; // eax
  int numPoints; // ebp
  double v9; // st7
  int v10; // eax
  double v11; // st7
  float *v12; // edx
  unsigned int v13; // esi
  float *v14; // ecx
  double v15; // st6
  double v16; // st5
  double v17; // st4
  double v18; // st6
  double v19; // st6
  double v20; // st5
  double v21; // st4
  double v22; // st6
  double v23; // st6
  double v24; // st5
  double v25; // st4
  double v26; // st6
  double v27; // st6
  double v28; // st5
  double v29; // st4
  double v30; // st6
  float *v31; // edx
  float *v32; // ecx
  int v33; // ebp
  double v34; // st6
  double v35; // st5
  double v36; // st4
  double v37; // st6
  int v38; // ebp
  unsigned int v39; // esi
  float *v40; // eax
  double v41; // st7
  double v42; // st6
  double v43; // st5
  float v44; // [esp+0h] [ebp-58h]
  float v45; // [esp+4h] [ebp-54h]
  float u0; // [esp+18h] [ebp-40h]
  float u0a; // [esp+18h] [ebp-40h]
  float u0b; // [esp+18h] [ebp-40h]
  float u0c; // [esp+18h] [ebp-40h]
  float u0d; // [esp+18h] [ebp-40h]
  float minV; // [esp+1Ch] [ebp-3Ch]
  float minU; // [esp+20h] [ebp-38h]
  float maxU; // [esp+24h] [ebp-34h]
  float maxV; // [esp+28h] [ebp-30h]
  float maxVa; // [esp+28h] [ebp-30h]
  float maxVb; // [esp+28h] [ebp-30h]
  float maxVc; // [esp+28h] [ebp-30h]
  float maxVd; // [esp+28h] [ebp-30h]
  float maxVe; // [esp+28h] [ebp-30h]
  float maxVf; // [esp+28h] [ebp-30h]
  float maxVg; // [esp+28h] [ebp-30h]
  int v62; // [esp+2Ch] [ebp-2Ch]
  float ratio; // [esp+30h] [ebp-28h]
  int i; // [esp+34h] [ebp-24h]
  int j; // [esp+38h] [ebp-20h]
  int ja; // [esp+38h] [ebp-20h]
  float v68; // [esp+40h] [ebp-18h]
  float v69; // [esp+44h] [ebp-14h]
  float v70; // [esp+48h] [ebp-10h]
  float v71; // [esp+4Ch] [ebp-Ch]
  float v72; // [esp+50h] [ebp-8h]
  float v73; // [esp+54h] [ebp-4h]

  v1 = this;
  backEnd.currentSpace = &backEnd.viewDef->worldSpace;
  qglLoadMatrixf(backEnd.viewDef->worldSpace.modelViewMatrix);
  backEnd.currentScissor = backEnd.viewDef->scissor;
  qglScissor(
    backEnd.currentScissor.x1 + backEnd.viewDef->viewport.x1,
    (*(int *)&backEnd.currentScissor.x1 >> 16) + backEnd.viewDef->viewport.y1,
    backEnd.currentScissor.x2 - backEnd.currentScissor.x1 + 1,
    (*(int *)&backEnd.currentScissor.x2 >> 16) - (*(int *)&backEnd.currentScissor.x1 >> 16) + 1);
  GL_State(357);
  i = 0;
  if ( v1->numPortalAreas > 0 )
  {
    viewDef = backEnd.viewDef;
    v62 = 0;
    do
    {
      v3 = &v1->portalAreas[v62];
      if ( v3->viewCount == tr.viewCount )
      {
        for ( k = v3->portals; k; k = k->next )
        {
          w = k->w;
          if ( w )
          {
            if ( k->image )
            {
              v6 = viewDef->renderView.vieworg.z * k->plane.c
                 + viewDef->renderView.vieworg.y * k->plane.b
                 + viewDef->renderView.vieworg.x * k->plane.a
                 + k->plane.d;
              maxV = v6;
              if ( v6 > k->cullNear )
              {
                if ( maxV < (double)k->cullFar )
                {
                  ratio = 1.0 - (k->cullFar - maxV) / (k->cullFar - k->cullNear);
                  qglColor4f(1.0, 1.0, 1.0, ratio);
                }
                else
                {
                  qglColor4f(1.0, 1.0, 1.0, 1.0);
                }
                k->image->Bind(k->image);
                p_x = &w->p->x;
                numPoints = w->numPoints;
                v68 = p_x[15] - *p_x;
                v69 = p_x[16] - p_x[1];
                v9 = p_x[17] - p_x[2];
                minU = idMath::INFINITY;
                v70 = v9;
                v10 = 0;
                minV = idMath::INFINITY;
                v71 = v9 * k->plane.b - v69 * k->plane.c;
                v72 = v68 * k->plane.c - v70 * k->plane.a;
                v73 = v69 * k->plane.a - v68 * k->plane.b;
                v11 = -1.0e30;
                maxU = -1.0e30;
                maxVa = maxU;
                if ( numPoints >= 4 )
                {
                  v12 = &w->p->x;
                  v13 = ((unsigned int)(numPoints - 4) >> 2) + 1;
                  v14 = v12 + 7;
                  j = 4 * v13;
                  do
                  {
                    v15 = *(v14 - 7) - *v12;
                    v16 = *(v14 - 6) - v12[1];
                    v17 = *(v14 - 5) - v12[2];
                    u0 = v70 * v17 + v16 * v69 + v15 * v68;
                    v18 = v17 * v73 + v16 * v72 + v15 * v71;
                    if ( u0 < (double)minU )
                      minU = u0;
                    if ( u0 > (double)maxU )
                      maxU = u0;
                    if ( v18 < minV )
                      minV = v18;
                    if ( v18 > v11 )
                    {
                      maxVb = v18;
                      v11 = maxVb;
                    }
                    v19 = *(v14 - 2) - *v12;
                    v20 = *(v14 - 1) - v12[1];
                    v21 = *v14 - v12[2];
                    u0a = v70 * v21 + v20 * v69 + v19 * v68;
                    v22 = v21 * v73 + v20 * v72 + v19 * v71;
                    if ( u0a < (double)minU )
                      minU = u0a;
                    if ( u0a > (double)maxU )
                      maxU = u0a;
                    if ( v22 < minV )
                      minV = v22;
                    if ( v22 > v11 )
                    {
                      maxVc = v22;
                      v11 = maxVc;
                    }
                    v23 = v14[3] - *v12;
                    v24 = v14[4] - v12[1];
                    v25 = v14[5] - v12[2];
                    u0b = v70 * v25 + v24 * v69 + v23 * v68;
                    v26 = v25 * v73 + v24 * v72 + v23 * v71;
                    if ( u0b < (double)minU )
                      minU = u0b;
                    if ( u0b > (double)maxU )
                      maxU = u0b;
                    if ( v26 < minV )
                      minV = v26;
                    if ( v26 > v11 )
                    {
                      maxVd = v26;
                      v11 = maxVd;
                    }
                    v27 = v14[8] - *v12;
                    v28 = v14[9] - v12[1];
                    v29 = v14[10] - v12[2];
                    u0c = v70 * v29 + v28 * v69 + v27 * v68;
                    v30 = v29 * v73 + v28 * v72 + v27 * v71;
                    if ( u0c < (double)minU )
                      minU = u0c;
                    if ( u0c > (double)maxU )
                      maxU = u0c;
                    if ( v30 < minV )
                      minV = v30;
                    if ( v30 > v11 )
                    {
                      maxVe = v30;
                      v11 = maxVe;
                    }
                    v14 += 20;
                    --v13;
                  }
                  while ( v13 );
                  v10 = j;
                  maxVa = v11;
                }
                if ( v10 < numPoints )
                {
                  v31 = &w->p->x;
                  v32 = &v31[5 * v10 + 2];
                  v33 = numPoints - v10;
                  do
                  {
                    v34 = *(v32 - 2) - *v31;
                    v35 = *(v32 - 1) - v31[1];
                    v36 = *v32 - v31[2];
                    u0d = v70 * v36 + v35 * v69 + v34 * v68;
                    v37 = v36 * v73 + v35 * v72 + v34 * v71;
                    if ( u0d < (double)minU )
                      minU = u0d;
                    if ( u0d > (double)maxU )
                      maxU = u0d;
                    if ( v37 < minV )
                      minV = v37;
                    if ( v37 > v11 )
                    {
                      maxVf = v37;
                      v11 = maxVf;
                    }
                    v32 += 5;
                    --v33;
                  }
                  while ( v33 );
                  maxVa = v11;
                }
                qglBegin(9u);
                v38 = 0;
                if ( w->numPoints > 0 )
                {
                  v39 = 0;
                  *(float *)&ja = maxVa - minV;
                  do
                  {
                    v40 = &w->p->x;
                    v41 = v40[v39 / 4] - *v40;
                    v42 = v40[v39 / 4 + 1] - v40[1];
                    v43 = v40[v39 / 4 + 2] - v40[2];
                    v45 = 1.0 - (v73 * v43 + v42 * v72 + v41 * v71 - minV) / *(float *)&ja;
                    maxVg = maxU - minU;
                    v44 = (v43 * v70 + v42 * v69 + v41 * v68 - minU) / maxVg;
                    qglTexCoord2f(v44, v45);
                    qglVertex3f(w->p[v39 / 0x14].x, w->p[v39 / 0x14].y, w->p[v39 / 0x14].z);
                    ++v38;
                    v39 += 20;
                  }
                  while ( v38 < w->numPoints );
                }
                qglEnd();
                viewDef = backEnd.viewDef;
                v1 = this;
              }
            }
          }
        }
      }
      ++v62;
      ++i;
    }
    while ( i < v1->numPortalAreas );
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::FloodLightThroughArea_r(class idRenderLightLocal *,int,struct portalStack_s const *)
void __thiscall idRenderWorldLocal::FloodLightThroughArea_r(
        idRenderWorldLocal *this,
        idRenderLightLocal *light,
        int areaNum,
        const portalStack_s *ps)
{
  idRenderLightLocal *v4; // ebx
  portalArea_s *v5; // esi
  portal_s *portals; // ecx
  double v7; // st7
  const portalStack_s *v8; // edx
  const portalStack_s *v9; // eax
  idWinding *v10; // esi
  int numPoints; // eax
  bool v12; // al
  int v13; // ecx
  int v14; // eax
  float *p_x; // edx
  idVec5 *v16; // edi
  int v17; // edi
  float *p_c; // esi
  double v19; // st7
  double v20; // st6
  double v21; // st5
  int v22; // edi
  float *v23; // esi
  double v24; // st7
  double v25; // st6
  double v26; // st5
  int v27; // eax
  idVec5 *v28; // esi
  int v29; // edi
  float *p_y; // edx
  int v31; // eax
  double v32; // st7
  float *v33; // eax
  double v34; // st6
  double v35; // st5
  double v36; // st4
  double v37; // st3
  idPlane *v38; // eax
  idPlane *v39; // ecx
  long double v40; // st4
  long double v41; // st7
  long double v42; // st6
  unsigned __int8 v44; // c2
  unsigned __int8 v45; // c3
  const portalStack_s *firstPortalStack; // [esp+Ch] [ebp-6CCh]
  float firstPortalStacka; // [esp+Ch] [ebp-6CCh]
  float firstPortalStackb; // [esp+Ch] [ebp-6CCh]
  float firstPortalStackc; // [esp+Ch] [ebp-6CCh]
  portal_s *p; // [esp+10h] [ebp-6C8h]
  int v51; // [esp+14h] [ebp-6C4h]
  idPlane v53; // [esp+1Ch] [ebp-6BCh] BYREF
  idPlane plane; // [esp+2Ch] [ebp-6ACh] BYREF
  float v55; // [esp+3Ch] [ebp-69Ch]
  portalStack_s newStack; // [esp+48h] [ebp-690h] BYREF
  idFixedWinding w; // [esp+1B8h] [ebp-520h] BYREF
  int v58; // [esp+6D4h] [ebp-4h]

  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v4 = light;
  v5 = &this->portalAreas[areaNum];
  v58 = 0;
  idRenderWorldLocal::AddLightRefToArea(this, light, v5);
  portals = v5->portals;
  p = portals;
  if ( portals )
  {
    while ( 1 )
    {
      v7 = v4->globalLightOrigin.z * portals->plane.c
         + v4->globalLightOrigin.y * portals->plane.b
         + v4->globalLightOrigin.x * portals->plane.a
         + portals->plane.d;
      if ( v7 >= -0.1 )
      {
        v8 = ps;
        firstPortalStack = ps;
        v9 = ps;
        if ( !ps )
        {
LABEL_8:
          if ( v7 < 1.0 )
          {
            qmemcpy(&newStack, ps, sizeof(newStack));
            newStack.p = p;
            newStack.next = ps;
            idRenderWorldLocal::FloodLightThroughArea_r(this, v4, p->intoArea, &newStack);
LABEL_10:
            portals = p;
            goto LABEL_11;
          }
          v10 = portals->w;
          numPoints = v10->numPoints;
          if ( numPoints <= w.allocedSize || (v12 = w.ReAllocate(&w, numPoints, 0), v8 = ps, v12) )
          {
            v13 = 0;
            if ( v10->numPoints > 0 )
            {
              v14 = 0;
              do
              {
                p_x = &v10->p[v14].x;
                v16 = &w.p[v14];
                v16->x = *p_x;
                v16->y = p_x[1];
                v16->z = p_x[2];
                v16->s = p_x[3];
                ++v13;
                v16->t = p_x[4];
                ++v14;
              }
              while ( v13 < v10->numPoints );
              v4 = light;
              v8 = ps;
            }
            w.numPoints = v10->numPoints;
          }
          else
          {
            w.numPoints = 0;
          }
          v17 = 0;
          if ( v8->numPortalPlanes > 0 )
          {
            p_c = &v8->portalPlanes[0].c;
            do
            {
              v19 = -p_c[1];
              v20 = -*p_c;
              v21 = -*(p_c - 1);
              plane.a = -*(p_c - 2);
              plane.b = v21;
              plane.c = v20;
              plane.d = v19;
              if ( !idWinding::ClipInPlace(&w, &plane, 0.0, 0) )
                break;
              ++v17;
              p_c += 4;
            }
            while ( v17 < ps->numPortalPlanes );
            v8 = ps;
          }
          if ( !w.numPoints )
            goto LABEL_10;
          v22 = 0;
          if ( firstPortalStack->numPortalPlanes > 0 )
          {
            v23 = &firstPortalStack->portalPlanes[0].c;
            do
            {
              v24 = -v23[1];
              v25 = -*v23;
              v26 = -*(v23 - 1);
              v53.a = -*(v23 - 2);
              v53.b = v26;
              v53.c = v25;
              v53.d = v24;
              if ( !idWinding::ClipInPlace(&w, &v53, 0.0, 0) )
                break;
              ++v22;
              v23 += 4;
            }
            while ( v22 < firstPortalStack->numPortalPlanes );
            v8 = ps;
          }
          v27 = w.numPoints;
          if ( !w.numPoints )
            goto LABEL_10;
          newStack.p = p;
          newStack.next = v8;
          if ( w.numPoints > 20 )
          {
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
              common.type,
              "More than MAX_PORTAL_PLANES (%d) in winding; capping",
              20);
            v27 = 20;
          }
          newStack.numPortalPlanes = 0;
          if ( v27 <= 0 )
          {
LABEL_78:
            idRenderWorldLocal::FloodLightThroughArea_r(this, v4, p->intoArea, &newStack);
            goto LABEL_10;
          }
          v28 = w.p;
          v29 = 1;
          p_y = &w.p->y;
          v51 = v27;
          while ( 2 )
          {
            v31 = v29;
            if ( v29 == w.numPoints )
              v31 = 0;
            v32 = v4->globalLightOrigin.z - p_y[1];
            v33 = &v28[v31].x;
            v34 = v4->globalLightOrigin.y - *p_y;
            v35 = v4->globalLightOrigin.x - *(p_y - 1);
            v36 = v4->globalLightOrigin.z - v33[2];
            firstPortalStacka = v4->globalLightOrigin.y - v33[1];
            v37 = v4->globalLightOrigin.x - *v33;
            v38 = &newStack.portalPlanes[newStack.numPortalPlanes];
            v55 = v37;
            v38->a = firstPortalStacka * v32 - v36 * v34;
            v38->b = v36 * v35 - v55 * v32;
            v38->c = v55 * v34 - firstPortalStacka * v35;
            v39 = &newStack.portalPlanes[newStack.numPortalPlanes];
            v40 = v39->a * v39->a + v39->b * v39->b + v39->c * v39->c;
            if ( v40 == 0.0 )
            {
              v41 = 0.0;
            }
            else
            {
              v42 = 1.0 / sqrt(v40);
              v39->a = v42 * v39->a;
              v39->b = v42 * v39->b;
              v39->c = v42 * v39->c;
              v41 = v40 * v42;
            }
            if ( v45 | v44 )
            {
              if ( v39->b == 0.0 )
              {
                if ( v39->c <= 0.0 )
                {
                  if ( LODWORD(v39->c) != -1082130432 )
                    v39->c = -1.0;
                }
                else if ( LODWORD(v39->c) != 1065353216 )
                {
                  v39->c = 1.0;
                }
                goto LABEL_75;
              }
              if ( v39->c == 0.0 )
              {
                if ( v39->b <= 0.0 )
                {
                  if ( LODWORD(v39->b) != -1082130432 )
                    v39->b = -1.0;
                }
                else if ( LODWORD(v39->b) != 1065353216 )
                {
                  v39->b = 1.0;
                }
                goto LABEL_75;
              }
LABEL_62:
              if ( COERCE_FLOAT(LODWORD(v39->a) & 0x7FFFFFFF) != 1.0 )
              {
                firstPortalStackb = v39->b;
                HIBYTE(firstPortalStackb) &= ~0x80u;
                if ( firstPortalStackb == 1.0 )
                {
                  if ( v39->a == 0.0 && v39->c == 0.0 )
                    goto LABEL_75;
                  v39->c = 0.0;
                }
                else
                {
                  firstPortalStackc = v39->c;
                  HIBYTE(firstPortalStackc) &= ~0x80u;
                  if ( firstPortalStackc != 1.0 || v39->a == 0.0 && v39->b == 0.0 )
                    goto LABEL_75;
                  v39->b = 0.0;
                }
                v39->a = 0.0;
                goto LABEL_75;
              }
              if ( v39->b != 0.0 || v39->c != 0.0 )
              {
                v39->c = 0.0;
                v39->b = 0.0;
              }
            }
            else
            {
              if ( v39->b != 0.0 || v39->c != 0.0 )
                goto LABEL_62;
              if ( v39->a <= 0.0 )
              {
                if ( LODWORD(v39->a) != -1082130432 )
                  v39->a = -1.0;
              }
              else if ( LODWORD(v39->a) != 1065353216 )
              {
                v39->a = 1.0;
              }
            }
LABEL_75:
            if ( v41 >= 0.0099999998 )
            {
              newStack.portalPlanes[newStack.numPortalPlanes].d = -(v4->globalLightOrigin.z
                                                                  * newStack.portalPlanes[newStack.numPortalPlanes].c
                                                                  + v4->globalLightOrigin.y
                                                                  * newStack.portalPlanes[newStack.numPortalPlanes].b
                                                                  + newStack.portalPlanes[newStack.numPortalPlanes].a
                                                                  * v4->globalLightOrigin.x);
              ++newStack.numPortalPlanes;
            }
            ++v29;
            p_y += 5;
            if ( !--v51 )
              goto LABEL_78;
            continue;
          }
        }
        while ( 1 )
        {
          firstPortalStack = v9;
          if ( v9->p == portals )
            break;
          v9 = v9->next;
          if ( !v9 )
            goto LABEL_8;
        }
      }
LABEL_11:
      p = portals->next;
      if ( !p )
        break;
      portals = portals->next;
    }
  }
  v58 = -1;
  w.p = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
}

// FUNC: public: void __thiscall idRenderWorldLocal::FlowLightThroughPortals(class idRenderLightLocal *)
void __thiscall idRenderWorldLocal::FlowLightThroughPortals(idRenderWorldLocal *this, idRenderLightLocal *light)
{
  int areaNum; // esi
  float d; // eax
  float v5; // ecx
  float v6; // eax
  float v7; // ecx
  float v8; // eax
  float v9; // ecx
  portalStack_s ps; // [esp+10h] [ebp-170h] BYREF

  areaNum = light->areaNum;
  if ( areaNum != -1 )
  {
    memset(&ps, 0, sizeof(ps));
    ps.portalPlanes[0].a = light->frustum[0].a;
    ps.portalPlanes[0].b = light->frustum[0].b;
    d = light->frustum[0].d;
    ps.portalPlanes[0].c = light->frustum[0].c;
    ps.portalPlanes[0].d = d;
    ps.portalPlanes[1].a = light->frustum[1].a;
    ps.portalPlanes[1].b = light->frustum[1].b;
    v5 = light->frustum[1].d;
    ps.portalPlanes[1].c = light->frustum[1].c;
    ps.portalPlanes[1].d = v5;
    ps.portalPlanes[2].a = light->frustum[2].a;
    ps.portalPlanes[2].b = light->frustum[2].b;
    v6 = light->frustum[2].d;
    ps.portalPlanes[2].c = light->frustum[2].c;
    ps.portalPlanes[2].d = v6;
    ps.portalPlanes[3].a = light->frustum[3].a;
    ps.portalPlanes[3].b = light->frustum[3].b;
    v7 = light->frustum[3].d;
    ps.portalPlanes[3].c = light->frustum[3].c;
    ps.portalPlanes[3].d = v7;
    ps.portalPlanes[4].a = light->frustum[4].a;
    ps.portalPlanes[4].b = light->frustum[4].b;
    v8 = light->frustum[4].d;
    ps.portalPlanes[4].c = light->frustum[4].c;
    ps.portalPlanes[4].d = v8;
    ps.portalPlanes[5].a = light->frustum[5].a;
    ps.portalPlanes[5].b = light->frustum[5].b;
    v9 = light->frustum[5].d;
    ps.portalPlanes[5].c = light->frustum[5].c;
    ps.portalPlanes[5].d = v9;
    ps.numPortalPlanes = 6;
    idRenderWorldLocal::FloodLightThroughArea_r(this, light, areaNum, &ps);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::AddAreaLightRefs(int,struct portalStack_s const *)
void __thiscall idRenderWorldLocal::AddAreaLightRefs(idRenderWorldLocal *this, int areaNum, const portalStack_s *ps)
{
  areaReference_s *p_lightRefs; // ebx
  areaReference_s *i; // edi
  int integerValue; // eax
  idRenderLightLocal *light; // esi
  const idMaterial *lightShader; // eax
  int materialFlags; // ecx
  int v9; // eax
  viewLight_s *v10; // eax

  p_lightRefs = &this->portalAreas[areaNum].lightRefs;
  for ( i = p_lightRefs->areaNext; i != p_lightRefs; i = i->areaNext )
  {
    integerValue = r_singleLight.internalVar->integerValue;
    light = i->light;
    if ( (integerValue < 0 || integerValue == light->index)
      && light->parms.detailLevel >= (double)r_lightDetailLevel.internalVar->floatValue )
    {
      if ( r_useLightCulling.internalVar->integerValue < 3
        || light->parms.noShadows
        || (lightShader = light->lightShader, materialFlags = lightShader->materialFlags, (materialFlags & 8) == 0)
        && (lightShader->fogLight || lightShader->ambientLight || lightShader->blendLight || (materialFlags & 4) != 0)
        || (v9 = light->areaNum, v9 == -1)
        || tr.viewDef->connectedAreas[v9] )
      {
        if ( light->parms.globalLight || !idRenderWorldLocal::CullLightByPortals(this, light, ps) )
        {
          v10 = R_SetLightDefViewLight(light);
          idScreenRect::Union(&v10->scissorRect, &ps->rect);
        }
      }
    }
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::FloodViewThroughArea_r(class idVec3,int,struct portalStack_s const *)
void __thiscall idRenderWorldLocal::FloodViewThroughArea_r(
        idRenderWorldLocal *this,
        idVec3 origin,
        int areaNum,
        const portalStack_s *ps)
{
  portalArea_s *v5; // edi
  int v6; // esi
  portal_s *portals; // ebx
  double v8; // st7
  const portalStack_s *v9; // edx
  const portalStack_s *v10; // eax
  idWinding *v11; // esi
  int numPoints; // eax
  bool v13; // al
  int v14; // ecx
  int v15; // eax
  float *p_x; // edx
  idVec5 *v17; // edi
  int v18; // edi
  float *p_c; // esi
  double v20; // st7
  double v21; // st6
  double v22; // st5
  idRenderWorldLocal *v23; // edi
  int v24; // eax
  int numPortalPlanes; // ecx
  idVec5 *v26; // edi
  int v27; // esi
  float *p_y; // edx
  int v29; // eax
  double v30; // st7
  float *v31; // eax
  double v32; // st6
  double v33; // st5
  double v34; // st4
  double v35; // st3
  idPlane *v36; // eax
  idPlane *v37; // ecx
  long double v38; // st4
  long double v39; // st7
  long double v40; // st6
  unsigned __int8 v42; // c2
  unsigned __int8 v43; // c3
  idPlane *v44; // ecx
  float d; // [esp+10h] [ebp-6C8h]
  float da; // [esp+10h] [ebp-6C8h]
  float db; // [esp+10h] [ebp-6C8h]
  float dc; // [esp+10h] [ebp-6C8h]
  portal_s *p; // [esp+14h] [ebp-6C4h]
  portal_s *pa; // [esp+14h] [ebp-6C4h]
  idPlane plane; // [esp+1Ch] [ebp-6BCh] BYREF
  float v53; // [esp+2Ch] [ebp-6ACh]
  portalStack_s newStack; // [esp+38h] [ebp-6A0h] BYREF
  idScreenRect result; // [esp+1A8h] [ebp-530h] BYREF
  idFixedWinding w; // [esp+1B8h] [ebp-520h] BYREF
  int v57; // [esp+6D4h] [ebp-4h]

  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v57 = 0;
  v5 = &this->portalAreas[areaNum];
  v5->viewCount = tr.viewCount;
  idRenderWorldLocal::AddAreaEntityRefs(this, areaNum, ps);
  idRenderWorldLocal::AddAreaLightRefs(this, areaNum, ps);
  idRenderWorldLocal::AddAreaEffectRefs(this, areaNum, ps);
  v6 = areaNum;
  if ( idScreenRect::IsEmpty(&this->areaScreenRect[areaNum]) )
    this->areaScreenRect[v6] = ps->rect;
  else
    idScreenRect::Union(&this->areaScreenRect[v6], &ps->rect);
  portals = v5->portals;
  p = portals;
  if ( portals )
  {
    while ( 1 )
    {
      if ( (portals->doublePortal->blockingBits & 1) != 0 )
        goto LABEL_75;
      v8 = origin.y * portals->plane.b + origin.z * portals->plane.c + origin.x * portals->plane.a + portals->plane.d;
      d = v8;
      if ( v8 < 0.000099999997 )
        goto LABEL_75;
      v9 = ps;
      v10 = ps;
      if ( ps )
      {
        while ( v10->p != portals )
        {
          v10 = v10->next;
          if ( !v10 )
            goto LABEL_10;
        }
        goto LABEL_75;
      }
LABEL_10:
      if ( d >= 1.0 )
        break;
      qmemcpy(&newStack, ps, sizeof(newStack));
      newStack.next = ps;
      newStack.p = portals;
      idRenderWorldLocal::FloodViewThroughArea_r(this, origin, portals->intoArea, &newStack);
LABEL_75:
      portals = portals->next;
      p = portals;
      if ( !portals )
        goto LABEL_76;
    }
    v11 = portals->w;
    numPoints = v11->numPoints;
    if ( numPoints <= w.allocedSize || (v13 = w.ReAllocate(&w, numPoints, 0), v9 = ps, v13) )
    {
      v14 = 0;
      if ( v11->numPoints > 0 )
      {
        v15 = 0;
        do
        {
          p_x = &v11->p[v15].x;
          v17 = &w.p[v15];
          v17->x = *p_x;
          v17->y = p_x[1];
          v17->z = p_x[2];
          v17->s = p_x[3];
          ++v14;
          v17->t = p_x[4];
          ++v15;
        }
        while ( v14 < v11->numPoints );
        portals = p;
        v9 = ps;
      }
      w.numPoints = v11->numPoints;
    }
    else
    {
      w.numPoints = 0;
    }
    v18 = 0;
    if ( v9->numPortalPlanes > 0 )
    {
      p_c = &v9->portalPlanes[0].c;
      do
      {
        v20 = -p_c[1];
        v21 = -*p_c;
        v22 = -*(p_c - 1);
        plane.a = -*(p_c - 2);
        plane.b = v22;
        plane.c = v21;
        plane.d = v20;
        if ( !idWinding::ClipInPlace(&w, &plane, 0.0, 0) )
          break;
        ++v18;
        p_c += 4;
      }
      while ( v18 < ps->numPortalPlanes );
    }
    if ( !w.numPoints )
      goto LABEL_75;
    v23 = this;
    if ( idRenderWorldLocal::PortalIsFoggedOut(this, portals)
      || r_portalsDistanceCull.internalVar->integerValue && d > (double)portals->cullFar )
    {
      goto LABEL_75;
    }
    newStack.p = portals;
    newStack.next = ps;
    newStack.rect = *idRenderWorldLocal::ScreenRectFromWinding(this, &result, &w, &tr.identitySpace);
    idScreenRect::Intersect(&newStack.rect, &ps->rect);
    v24 = w.numPoints;
    if ( w.numPoints > 20 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "More than MAX_PORTAL_PLANES (%d) in winding; capping",
        20);
      v24 = 20;
    }
    numPortalPlanes = 0;
    newStack.numPortalPlanes = 0;
    if ( v24 <= 0 )
    {
LABEL_74:
      v44 = &newStack.portalPlanes[numPortalPlanes];
      v44->a = portals->plane.a;
      v44->b = portals->plane.b;
      v44->c = portals->plane.c;
      v44->d = portals->plane.d;
      ++newStack.numPortalPlanes;
      idRenderWorldLocal::FloodViewThroughArea_r(v23, origin, portals->intoArea, &newStack);
      goto LABEL_75;
    }
    v26 = w.p;
    v27 = 1;
    p_y = &w.p->y;
    pa = (portal_s *)v24;
    while ( 1 )
    {
      v29 = v27;
      if ( v27 == w.numPoints )
        v29 = 0;
      v30 = origin.z - p_y[1];
      v31 = &v26[v29].x;
      v32 = origin.y - *p_y;
      v33 = origin.x - *(p_y - 1);
      v34 = origin.z - v31[2];
      da = origin.y - v31[1];
      v35 = origin.x - *v31;
      v36 = &newStack.portalPlanes[newStack.numPortalPlanes];
      v53 = v35;
      v36->a = da * v30 - v34 * v32;
      v36->b = v34 * v33 - v53 * v30;
      v36->c = v53 * v32 - da * v33;
      v37 = &newStack.portalPlanes[newStack.numPortalPlanes];
      v38 = v37->a * v37->a + v37->b * v37->b + v37->c * v37->c;
      if ( v38 == 0.0 )
      {
        v39 = 0.0;
      }
      else
      {
        v40 = 1.0 / sqrt(v38);
        v37->a = v40 * v37->a;
        v37->b = v40 * v37->b;
        v37->c = v40 * v37->c;
        v39 = v38 * v40;
      }
      if ( v43 | v42 )
      {
        if ( v37->b == 0.0 )
        {
          if ( v37->c <= 0.0 )
          {
            if ( LODWORD(v37->c) != -1082130432 )
              v37->c = -1.0;
          }
          else if ( LODWORD(v37->c) != 1065353216 )
          {
            v37->c = 1.0;
          }
          goto LABEL_70;
        }
        if ( v37->c == 0.0 )
        {
          if ( v37->b <= 0.0 )
          {
            if ( LODWORD(v37->b) != -1082130432 )
              v37->b = -1.0;
          }
          else if ( LODWORD(v37->b) != 1065353216 )
          {
            v37->b = 1.0;
          }
          goto LABEL_70;
        }
      }
      else if ( v37->b == 0.0 && v37->c == 0.0 )
      {
        if ( v37->a <= 0.0 )
        {
          if ( LODWORD(v37->a) != -1082130432 )
            v37->a = -1.0;
        }
        else if ( LODWORD(v37->a) != 1065353216 )
        {
          v37->a = 1.0;
        }
        goto LABEL_70;
      }
      if ( COERCE_FLOAT(LODWORD(v37->a) & 0x7FFFFFFF) == 1.0 )
      {
        if ( v37->b != 0.0 || v37->c != 0.0 )
        {
          v37->c = 0.0;
          v37->b = 0.0;
        }
        goto LABEL_70;
      }
      db = v37->b;
      HIBYTE(db) &= ~0x80u;
      if ( db == 1.0 )
      {
        if ( v37->a == 0.0 && v37->c == 0.0 )
          goto LABEL_70;
        v37->c = 0.0;
      }
      else
      {
        dc = v37->c;
        HIBYTE(dc) &= ~0x80u;
        if ( dc != 1.0 || v37->a == 0.0 && v37->b == 0.0 )
          goto LABEL_70;
        v37->b = 0.0;
      }
      v37->a = 0.0;
LABEL_70:
      if ( v39 >= 0.0099999998 )
      {
        newStack.portalPlanes[newStack.numPortalPlanes].d = -(origin.y
                                                            * newStack.portalPlanes[newStack.numPortalPlanes].b
                                                            + origin.z
                                                            * newStack.portalPlanes[newStack.numPortalPlanes].c
                                                            + origin.x
                                                            * newStack.portalPlanes[newStack.numPortalPlanes].a);
        ++newStack.numPortalPlanes;
      }
      ++v27;
      p_y += 5;
      pa = (portal_s *)((char *)pa - 1);
      if ( !pa )
      {
        v23 = this;
        numPortalPlanes = newStack.numPortalPlanes;
        goto LABEL_74;
      }
    }
  }
LABEL_76:
  v57 = -1;
  w.p = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
}

// FUNC: public: void __thiscall idRenderWorldLocal::FlowViewThroughPortals(class idVec3,int,class idPlane const *)
void __thiscall idRenderWorldLocal::FlowViewThroughPortals(
        idRenderWorldLocal *this,
        idVec3 origin,
        int numPlanes,
        const idPlane *planes)
{
  viewDef_s *viewDef; // edx
  int v6; // eax
  int v7; // ecx
  idScreenRect *p_scissor; // edx
  idScreenRect *v9; // esi
  int v10; // esi
  int v11; // edi
  int v12; // esi
  int v13; // edi
  portalStack_s ps; // [esp+10h] [ebp-170h] BYREF

  ps.next = 0;
  ps.p = 0;
  if ( numPlanes > 0 )
    qmemcpy(ps.portalPlanes, planes, 16 * numPlanes);
  viewDef = tr.viewDef;
  ps.numPortalPlanes = numPlanes;
  ps.rect = tr.viewDef->scissor;
  if ( tr.viewDef->areaNum >= 0 )
  {
    v12 = 0;
    if ( this->numPortalAreas > 0 )
    {
      v13 = 0;
      do
      {
        idScreenRect::Clear(&this->areaScreenRect[v13]);
        ++v12;
        ++v13;
      }
      while ( v12 < this->numPortalAreas );
      viewDef = tr.viewDef;
    }
    idRenderWorldLocal::FloodViewThroughArea_r(this, origin, viewDef->areaNum, &ps);
  }
  else
  {
    v6 = 0;
    if ( this->numPortalAreas > 0 )
    {
      v7 = 0;
      while ( 1 )
      {
        p_scissor = &viewDef->scissor;
        v9 = &this->areaScreenRect[v7];
        *(_DWORD *)&v9->x1 = *(_DWORD *)&p_scissor->x1;
        *(_DWORD *)&v9->x2 = *(_DWORD *)&p_scissor->x2;
        v9->zmin = p_scissor->zmin;
        ++v6;
        v9->zmax = p_scissor->zmax;
        ++v7;
        if ( v6 >= this->numPortalAreas )
          break;
        viewDef = tr.viewDef;
      }
    }
    v10 = 0;
    if ( this->numPortalAreas > 0 )
    {
      v11 = 0;
      do
      {
        this->portalAreas[v11].viewCount = tr.viewCount;
        idRenderWorldLocal::AddAreaEntityRefs(this, v10, &ps);
        idRenderWorldLocal::AddAreaLightRefs(this, v10, &ps);
        idRenderWorldLocal::AddAreaEffectRefs(this, v10++, &ps);
        ++v11;
      }
      while ( v10 < this->numPortalAreas );
    }
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::FindViewLightsAndEntities(void)
void __thiscall idRenderWorldLocal::FindViewLightsAndEntities(idRenderWorldLocal *this)
{
  viewDef_s *viewDef; // eax
  int v3; // edx
  portalArea_s *portalAreas; // ecx
  int areaNum; // esi
  portalStack_s ps; // [esp+8h] [ebp-16Ch] BYREF

  tr.viewDef->viewLights = 0;
  tr.viewDef->viewEntitys = 0;
  if ( r_usePortals.internalVar->integerValue )
    tr.viewDef->areaNum = this->PointInArea(this, &tr.viewDef->initialViewAreaOrigin);
  else
    tr.viewDef->areaNum = -1;
  idRenderWorldLocal::BuildConnectedAreas(this);
  ++tr.viewCount;
  viewDef = tr.viewDef;
  if ( r_singleArea.internalVar->integerValue )
  {
    if ( tr.viewDef->areaNum >= 0 )
    {
      if ( tr.viewDef->areaNum != lastPrintedAreaNum )
      {
        v3 = *(_DWORD *)common.type;
        lastPrintedAreaNum = tr.viewDef->areaNum;
        (*(void (**)(netadrtype_t, const char *, ...))(v3 + 124))(
          common.type,
          "entering portal area %i\n",
          lastPrintedAreaNum);
        viewDef = tr.viewDef;
      }
      ps.portalPlanes[0] = viewDef->frustum[0];
      ps.portalPlanes[1] = viewDef->frustum[1];
      ps.portalPlanes[2] = viewDef->frustum[2];
      ps.portalPlanes[3] = viewDef->frustum[3];
      ps.portalPlanes[4] = viewDef->frustum[4];
      ps.numPortalPlanes = 5;
      *(_DWORD *)&ps.rect.x1 = *(_DWORD *)&viewDef->scissor.x1;
      *(_DWORD *)&ps.rect.x2 = *(_DWORD *)&viewDef->scissor.x2;
      ps.rect.zmin = viewDef->scissor.zmin;
      portalAreas = this->portalAreas;
      ps.rect.zmax = viewDef->scissor.zmax;
      areaNum = viewDef->areaNum;
      portalAreas[areaNum].viewCount = tr.viewCount;
      idRenderWorldLocal::AddAreaEntityRefs(this, areaNum, &ps);
      idRenderWorldLocal::AddAreaLightRefs(this, areaNum, &ps);
      idRenderWorldLocal::AddAreaEffectRefs(this, areaNum, &ps);
    }
  }
  else
  {
    idRenderWorldLocal::FlowViewThroughPortals(this, tr.viewDef->renderView.vieworg, 5, tr.viewDef->frustum);
  }
}
