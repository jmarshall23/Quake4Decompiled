
// FUNC: private: void __thiscall idInteraction::Unlink(void)
void __thiscall idInteraction::Unlink(idInteraction *this)
{
  idInteraction *entityPrev; // eax
  idInteraction *entityNext; // esi
  idInteraction *v3; // eax
  idInteraction *v4; // esi
  idInteraction *lightPrev; // eax
  idInteraction *lightNext; // esi
  idInteraction *v7; // eax
  idInteraction *v8; // esi

  entityPrev = this->entityPrev;
  entityNext = this->entityNext;
  if ( entityPrev )
    entityPrev->entityNext = entityNext;
  else
    this->entityDef->firstInteraction = entityNext;
  v3 = this->entityNext;
  v4 = this->entityPrev;
  if ( v3 )
    v3->entityPrev = v4;
  else
    this->entityDef->lastInteraction = v4;
  lightPrev = this->lightPrev;
  lightNext = this->lightNext;
  this->entityPrev = 0;
  this->entityNext = 0;
  if ( lightPrev )
    lightPrev->lightNext = lightNext;
  else
    this->lightDef->firstInteraction = lightNext;
  v7 = this->lightNext;
  v8 = this->lightPrev;
  if ( v7 )
    v7->lightPrev = v8;
  else
    this->lightDef->lastInteraction = v8;
  this->lightPrev = 0;
  this->lightNext = 0;
}

// FUNC: public: int __thiscall idInteraction::MemoryUsed(void)
int __thiscall idInteraction::MemoryUsed(idInteraction *this)
{
  int v2; // ebp
  int v3; // ebx
  surfaceInteraction_t *v4; // esi
  int v5; // ebx
  int v7; // [esp+Ch] [ebp-4h]

  v2 = 0;
  v3 = 0;
  if ( this->numSurfaces > 0 )
  {
    v7 = 0;
    do
    {
      v4 = &this->surfaces[v7];
      v5 = R_TriSurfMemory(v4->lightTris) + v3;
      ++v7;
      ++v2;
      v3 = R_TriSurfMemory(v4->shadowTris) + v5;
    }
    while ( v2 < this->numSurfaces );
  }
  return v3;
}

// FUNC: void __cdecl R_CalcInteractionFacing(class idRenderEntityLocal const *,struct srfTriangles_s const *,class idRenderLightLocal const *,struct srfCullInfo_s &)
void __cdecl R_CalcInteractionFacing(
        const idRenderEntityLocal *ent,
        srfTriangles_s *tri,
        const idRenderLightLocal *light,
        srfCullInfo_s *cullInfo)
{
  int v4; // esi
  int v5; // eax
  void *v6; // esp
  _BYTE v7[8]; // [esp+4h] [ebp-14h] BYREF
  idVec3 localLightOrigin; // [esp+Ch] [ebp-Ch] BYREF

  if ( !cullInfo->facing )
  {
    R_GlobalPointToLocal(ent->modelMatrix, &light->globalLightOrigin, &localLightOrigin);
    v4 = tri->numIndexes / 3;
    if ( !tri->facePlanes || !tri->facePlanesCalculated )
      R_DeriveFacePlanes(tri);
    cullInfo->facing = (unsigned __int8 *)Mem_Alloc16(v4 + 1, 0x10u);
    v5 = 4 * v4 + 18;
    LOBYTE(v5) = v5 & 0xFC;
    v6 = alloca(v5);
    (*(void (__fastcall **)(idSIMDProcessor *, _BYTE *, idVec3 *, idPlane *, int))&SIMDProcessor->gap34[32])(
      SIMDProcessor,
      v7,
      &localLightOrigin,
      tri->facePlanes,
      v4);
    ((void (__fastcall *)(idSIMDProcessor *, unsigned __int8 *, _BYTE *, _DWORD, int))SIMDProcessor->CmpGE)(
      SIMDProcessor,
      cullInfo->facing,
      v7,
      0,
      v4);
    cullInfo->facing[v4] = 1;
  }
}

// FUNC: void __cdecl R_CalcInteractionCullBits(class idRenderEntityLocal const *,struct srfTriangles_s const *,class idRenderLightLocal const *,struct srfCullInfo_s &)
void __cdecl R_CalcInteractionCullBits(
        const idRenderEntityLocal *ent,
        const srfTriangles_s *tri,
        const idRenderLightLocal *light,
        srfCullInfo_s *cullInfo)
{
  int v4; // ebx
  float *p_c; // edi
  unsigned __int8 *v6; // eax
  int v7; // eax
  void *v8; // esp
  int v9; // ebx
  idPlane *localClipPlanes; // eax
  float *v11; // [esp-8h] [ebp-30h]
  idDrawVert *verts; // [esp-8h] [ebp-30h]
  int numVerts; // [esp-4h] [ebp-2Ch]
  _BYTE v14[12]; // [esp+0h] [ebp-28h] BYREF
  idPlane in; // [esp+Ch] [ebp-1Ch] BYREF
  float *modelMatrix; // [esp+1Ch] [ebp-Ch]
  int frontBits; // [esp+20h] [ebp-8h]
  idPlane *out; // [esp+24h] [ebp-4h]

  v4 = 0;
  if ( !cullInfo->cullBits )
  {
    frontBits = 0;
    modelMatrix = ent->modelMatrix;
    out = cullInfo->localClipPlanes;
    p_c = &light->frustum[0].c;
    do
    {
      in.a = -*(p_c - 2);
      in.b = -*(p_c - 1);
      in.c = -*p_c;
      in.d = -p_c[1];
      R_GlobalPlaneToLocal(modelMatrix, &in, out);
      if ( idBounds::PlaneDistance(&tri->bounds, out) >= 0.1 )
        frontBits |= 1 << v4;
      ++out;
      ++v4;
      p_c += 4;
    }
    while ( v4 < 6 );
    if ( frontBits == 63 )
    {
      cullInfo->cullBits = (unsigned __int8 *)-1;
    }
    else
    {
      v6 = (unsigned __int8 *)R_StaticAlloc(tri->numVerts);
      cullInfo->cullBits = v6;
      SIMDProcessor->Memset(SIMDProcessor, v6, 0, tri->numVerts);
      v7 = 4 * tri->numVerts + 18;
      LOBYTE(v7) = v7 & 0xFC;
      v8 = alloca(v7);
      v9 = 0;
      localClipPlanes = cullInfo->localClipPlanes;
      out = cullInfo->localClipPlanes;
      do
      {
        if ( ((1 << v9) & frontBits) == 0 )
        {
          modelMatrix = &tri->silTraceVerts->xyzw.x;
          numVerts = tri->numVerts;
          if ( modelMatrix )
          {
            v11 = modelMatrix;
            modelMatrix = (float *)SIMDProcessor->__vftable;
            (*((void (__fastcall **)(idSIMDProcessor *, _BYTE *, idPlane *, float *, int))modelMatrix + 13))(
              SIMDProcessor,
              v14,
              localClipPlanes,
              v11,
              numVerts);
          }
          else
          {
            verts = tri->verts;
            modelMatrix = (float *)SIMDProcessor->__vftable;
            (*((void (__fastcall **)(idSIMDProcessor *, _BYTE *, idPlane *, idDrawVert *, int))modelMatrix + 17))(
              SIMDProcessor,
              v14,
              localClipPlanes,
              verts,
              numVerts);
          }
          (*((void (__fastcall **)(idSIMDProcessor *, unsigned __int8 *, int, _BYTE *, int, int))&SIMDProcessor->CmpGE
           + 1))(
            SIMDProcessor,
            cullInfo->cullBits,
            v9,
            v14,
            1036831949,
            tri->numVerts);
          localClipPlanes = out;
        }
        ++v9;
        out = ++localClipPlanes;
      }
      while ( v9 < 6 );
    }
  }
}

// FUNC: void __cdecl R_FreeInteractionCullInfo(struct srfCullInfo_s &)
void __cdecl R_FreeInteractionCullInfo(srfCullInfo_s *cullInfo)
{
  unsigned __int8 *cullBits; // eax

  if ( cullInfo->facing )
  {
    Mem_Free16(cullInfo->facing);
    cullInfo->facing = 0;
  }
  cullBits = cullInfo->cullBits;
  if ( cullBits )
  {
    if ( cullBits != (unsigned __int8 *)-1 )
      R_StaticFree(cullInfo->cullBits);
    cullInfo->cullBits = 0;
  }
}

// FUNC: public: void __thiscall idInteraction::FreeSurfaces(void)
void __thiscall idInteraction::FreeSurfaces(idInteraction *this)
{
  int v2; // ebp
  int v3; // ebx
  surfaceInteraction_t *surfaces; // esi
  srfTriangles_s *lightTris; // eax
  surfaceInteraction_t *v6; // esi

  if ( this->surfaces )
  {
    v2 = 0;
    if ( this->numSurfaces > 0 )
    {
      v3 = 0;
      do
      {
        surfaces = this->surfaces;
        lightTris = surfaces[v3].lightTris;
        v6 = &surfaces[v3];
        if ( lightTris )
        {
          if ( lightTris != (srfTriangles_s *)-1 )
            R_FreeStaticTriSurf(lightTris);
          v6->lightTris = 0;
        }
        if ( v6->shadowTris && this->entityDef )
        {
          R_FreeStaticTriSurf(v6->shadowTris);
          v6->shadowTris = 0;
        }
        R_FreeInteractionCullInfo(&v6->cullInfo);
        ++v2;
        ++v3;
      }
      while ( v2 < this->numSurfaces );
    }
    R_StaticFree(this->surfaces);
    this->surfaces = 0;
  }
  this->numSurfaces = -1;
}

// FUNC: public: void __thiscall idInteraction::UnlinkAndFree(void)
void __thiscall idInteraction::UnlinkAndFree(idInteraction *this)
{
  int *world; // esi
  idInteraction *v3; // ecx
  areaNumRef_s *frustumAreas; // eax
  areaNumRef_s *next; // ecx
  int *p_areaNum; // eax

  world = (int *)this->lightDef->world;
  idInteraction::Unlink(this);
  idInteraction::FreeSurfaces(v3);
  frustumAreas = this->frustumAreas;
  if ( frustumAreas )
  {
    do
    {
      next = frustumAreas->next;
      p_areaNum = &frustumAreas[-1].areaNum;
      *p_areaNum = world[55];
      --world[57];
      world[55] = (int)p_areaNum;
      frustumAreas = next;
    }
    while ( next );
  }
  this[-1].dynamicModelFrameCount = world[51];
  --world[53];
  world[51] = (int)&this[-1].dynamicModelFrameCount;
}

// FUNC: public: void __thiscall idInteraction::MakeEmpty(void)
void __thiscall idInteraction::MakeEmpty(idInteraction *this)
{
  _DWORD *v1; // ecx
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax

  this->numSurfaces = 0;
  idInteraction::Unlink(this);
  v2 = v1[2];
  v1[6] = 0;
  v1[7] = *(_DWORD *)(v2 + 380);
  *(_DWORD *)(v2 + 380) = v1;
  v3 = v1[7];
  if ( v3 )
    *(_DWORD *)(v3 + 24) = v1;
  else
    *(_DWORD *)(v1[2] + 376) = v1;
  v4 = v1[3];
  v1[4] = 0;
  v1[5] = *(_DWORD *)(v4 + 1160);
  *(_DWORD *)(v4 + 1160) = v1;
  v5 = v1[5];
  if ( v5 )
    *(_DWORD *)(v5 + 16) = v1;
  else
    *(_DWORD *)(v1[3] + 1156) = v1;
}

// FUNC: R_PotentiallyInsideInfiniteShadow
char __usercall R_PotentiallyInsideInfiniteShadow@<al>(
        const srfTriangles_s *occluder@<eax>,
        const idVec3 *localView@<edx>,
        const idVec3 *localLight@<ecx>)
{
  double floatValue; // st7
  double v4; // st7
  int y_low; // ebx
  int v7; // edi
  int z_low; // ebp
  int v9; // esi
  float *v10; // edx
  double v11; // st7
  float v12; // edx
  double v13; // st7
  double v14; // st6
  double v15; // st5
  double v16; // st7
  float v17; // eax
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st5
  int v22; // [esp+4h] [ebp-7Ch]
  idVec3 hit; // [esp+8h] [ebp-78h]
  idVec3 ray; // [esp+14h] [ebp-6Ch]
  float x; // [esp+20h] [ebp-60h]
  int v26; // [esp+24h] [ebp-5Ch]
  int v27; // [esp+28h] [ebp-58h]
  float v28; // [esp+2Ch] [ebp-54h]
  int v29; // [esp+30h] [ebp-50h]
  int v30; // [esp+34h] [ebp-4Ch]
  float v31; // [esp+38h] [ebp-48h]
  float v32; // [esp+3Ch] [ebp-44h]
  float v33; // [esp+44h] [ebp-3Ch]
  float v34; // [esp+48h] [ebp-38h]
  float v35; // [esp+58h] [ebp-28h]
  float v36; // [esp+64h] [ebp-1Ch]
  idBounds exp; // [esp+68h] [ebp-18h] BYREF

  floatValue = r_znear.internalVar->floatValue;
  if ( tr.viewDef->renderView.cramZNear )
    floatValue = floatValue * 0.25;
  v4 = floatValue + floatValue;
  exp.b[0].x = occluder->bounds.b[0].x - v4;
  exp.b[0].y = occluder->bounds.b[0].y - v4;
  exp.b[0].z = occluder->bounds.b[0].z - v4;
  exp.b[1].x = v4 + occluder->bounds.b[1].x;
  exp.b[1].y = v4 + occluder->bounds.b[1].y;
  exp.b[1].z = v4 + occluder->bounds.b[1].z;
  if ( localView->x >= (double)exp.b[0].x
    && localView->y >= (double)exp.b[0].y
    && localView->z >= (double)exp.b[0].z
    && localView->x <= (double)exp.b[1].x
    && localView->y <= (double)exp.b[1].y
    && localView->z <= (double)exp.b[1].z
    || localLight->x >= (double)exp.b[0].x
    && localLight->y >= (double)exp.b[0].y
    && localLight->z >= (double)exp.b[0].z
    && localLight->x <= (double)exp.b[1].x
    && localLight->y <= (double)exp.b[1].y
    && localLight->z <= (double)exp.b[1].z )
  {
    return 1;
  }
  ray.x = localView->x - localLight->x;
  ray.y = localView->y - localLight->y;
  y_low = SLODWORD(ray.y);
  v22 = (char *)localView - (char *)&exp;
  v7 = (char *)localLight - (char *)&exp;
  ray.z = localView->z - localLight->z;
  z_low = SLODWORD(ray.z);
  v9 = 0;
  while ( 1 )
  {
    v10 = (float *)((char *)&exp + v9);
    if ( *(float *)((char *)&exp.b[0].x + v9 + v7) >= (double)*(float *)((char *)&exp.b[0].x + v9) )
      break;
    if ( *(float *)((char *)v10 + v22) >= (double)*v10 )
    {
      v11 = *v10 - *(float *)((char *)v10 + v7);
      x = ray.x;
      v12 = *v10;
      v26 = y_low;
      v13 = v11 / *(float *)((char *)&ray.x + v9);
      v27 = z_low;
      v31 = ray.x * v13;
      v32 = *(float *)&y_low * v13;
      v14 = v31 + localLight->x;
      v15 = v13 * *(float *)&z_low;
      v16 = v32 + localLight->y;
      v35 = v15 + localLight->z;
      v17 = v35;
      goto LABEL_23;
    }
LABEL_29:
    v9 += 4;
    if ( v9 >= 12 )
      return 0;
  }
  if ( *(float *)((char *)v10 + v7) <= (double)*(float *)((char *)&exp.b[1].x + v9)
    || *(float *)((char *)v10 + v22) > (double)*(float *)((char *)&exp.b[1].x + v9) )
  {
    goto LABEL_29;
  }
  v18 = *(float *)((char *)&exp.b[1].x + v9);
  v29 = y_low;
  v19 = v18 - *(float *)((char *)v10 + v7);
  v28 = ray.x;
  v12 = *(float *)((char *)&exp.b[1].x + v9);
  v20 = v19 / *(float *)((char *)&ray.x + v9);
  v30 = z_low;
  v33 = ray.x * v20;
  v34 = *(float *)&y_low * v20;
  v14 = v33 + localLight->x;
  v21 = v20 * *(float *)&z_low;
  v16 = v34 + localLight->y;
  v36 = v21 + localLight->z;
  v17 = v36;
LABEL_23:
  hit.x = v14;
  hit.z = v17;
  hit.y = v16;
  *(float *)((char *)&hit.x + v9) = v12;
  if ( hit.x < (double)exp.b[0].x
    || hit.y < (double)exp.b[0].y
    || hit.z < (double)exp.b[0].z
    || hit.x > (double)exp.b[1].x
    || hit.y > (double)exp.b[1].y
    || hit.z > (double)exp.b[1].z )
  {
    goto LABEL_29;
  }
  return 1;
}

// FUNC: void __cdecl R_ShowInteractionMemory_f(class idCmdArgs const &)
void __cdecl R_ShowInteractionMemory_f()
{
  idRenderWorldLocal *primaryWorld; // eax
  int v1; // edx
  int v2; // ebp
  int v3; // esi
  int v4; // edi
  idRenderEntityLocal *v5; // ecx
  idInteraction *firstInteraction; // ecx
  idInteraction *v7; // ebx
  int numSurfaces; // eax
  surfaceInteraction_t *surfaces; // ecx
  srfTriangles_s *v10; // eax
  srfTriangles_s *v11; // eax
  int total; // [esp+10h] [ebp-28h]
  int interactions; // [esp+14h] [ebp-24h]
  int entities; // [esp+18h] [ebp-20h]
  int emptyInteractions; // [esp+1Ch] [ebp-1Ch]
  int deferredInteractions; // [esp+20h] [ebp-18h]
  int lightTris; // [esp+24h] [ebp-14h]
  int lightTriIndexes; // [esp+28h] [ebp-10h]
  int shadowTris; // [esp+2Ch] [ebp-Ch]
  int v20; // [esp+30h] [ebp-8h]
  int i; // [esp+34h] [ebp-4h]

  primaryWorld = tr.primaryWorld;
  v1 = 0;
  v2 = 0;
  v3 = 0;
  v4 = 0;
  total = 0;
  entities = 0;
  interactions = 0;
  deferredInteractions = 0;
  emptyInteractions = 0;
  lightTris = 0;
  lightTriIndexes = 0;
  shadowTris = 0;
  for ( i = 0; v1 < primaryWorld->entityDefs.num; i = ++v1 )
  {
    v5 = primaryWorld->entityDefs.list[v1];
    if ( v5 )
    {
      firstInteraction = v5->firstInteraction;
      if ( firstInteraction )
      {
        ++entities;
        v7 = firstInteraction;
        do
        {
          ++interactions;
          total += idInteraction::MemoryUsed(v7);
          numSurfaces = v7->numSurfaces;
          if ( v7->numSurfaces == -1 )
          {
            ++deferredInteractions;
          }
          else if ( numSurfaces )
          {
            if ( numSurfaces > 0 )
            {
              surfaces = v7->surfaces;
              v20 = v7->numSurfaces;
              do
              {
                v10 = surfaces->lightTris;
                if ( surfaces->lightTris && v10 != (srfTriangles_s *)-1 )
                {
                  ++lightTris;
                  v2 += v10->numVerts;
                  lightTriIndexes += v10->numIndexes;
                }
                if ( surfaces->shadowTris )
                {
                  v11 = surfaces->shadowTris;
                  ++shadowTris;
                  v3 += v11->numVerts;
                  v4 += v11->numIndexes;
                }
                ++surfaces;
                --v20;
              }
              while ( v20 );
            }
          }
          else
          {
            ++emptyInteractions;
          }
          v7 = v7->entityNext;
        }
        while ( v7 );
        primaryWorld = tr.primaryWorld;
        v1 = i;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%i entities with %i total interactions totalling %ik\n",
    entities,
    interactions,
    total / 1024);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%i deferred interactions, %i empty interactions\n",
    deferredInteractions,
    emptyInteractions);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%5i indexes %5i verts in %5i light tris\n",
    lightTriIndexes,
    v2,
    lightTris);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%5i indexes %5i verts in %5i shadow tris\n",
    v4,
    v3,
    shadowTris);
}

// FUNC: bool __cdecl R_IClipTriangleToLight(class idVec3 const &,class idVec3 const &,class idVec3 const &,int,class idPlane const * const)
char __cdecl R_IClipTriangleToLight(
        const idVec3 *a,
        const idVec3 *b,
        const idVec3 *c,
        int planeBits,
        const idPlane *frustum)
{
  float x; // ecx
  float y; // edx
  float v7; // ecx
  float v8; // edx
  float v9; // ecx
  float v10; // edx
  int v12; // eax
  int v13; // esi
  clipTri_t pingPong[2]; // [esp+Ch] [ebp-1E8h] BYREF

  x = a->x;
  y = a->y;
  pingPong[0].verts[0].z = a->z;
  pingPong[0].verts[0].x = x;
  v7 = b->x;
  pingPong[0].verts[0].y = y;
  v8 = b->y;
  pingPong[0].verts[1].z = b->z;
  pingPong[0].verts[1].x = v7;
  v9 = c->x;
  pingPong[0].verts[1].y = v8;
  v10 = c->y;
  pingPong[0].verts[2].z = c->z;
  v12 = 0;
  pingPong[0].numVerts = 3;
  pingPong[0].verts[2].x = v9;
  pingPong[0].verts[2].y = v10;
  v13 = 0;
  while ( 1 )
  {
    if ( ((1 << v13) & planeBits) != 0 )
    {
      v12 = R_ChopWinding(pingPong, v12, *frustum);
      if ( pingPong[v12].numVerts < 1 )
        break;
    }
    ++v13;
    ++frustum;
    if ( v13 >= 6 )
      return 1;
  }
  return 0;
}

// FUNC: private: class idScreenRect __thiscall idInteraction::CalcInteractionScissorRectangle(class idFrustum const &)
idScreenRect *__thiscall idInteraction::CalcInteractionScissorRectangle(
        idInteraction *this,
        idScreenRect *result,
        idFrustum *viewFrustum)
{
  int integerValue; // ecx
  idScreenRect *v5; // eax
  $648D560FF66DA77A7E41CA4D7573E7CD frustumState; // eax
  areaReference_s *i; // edi
  areaNumRef_s *v8; // eax
  areaNumRef_s *j; // edi
  idRenderLightLocal *lightDef; // eax
  float *frustumTris; // eax
  double v12; // st7
  double v13; // st6
  double v14; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st4
  idScreenRect portalRect; // [esp+4h] [ebp-90h] BYREF
  idScreenRect scissorRect; // [esp+14h] [ebp-80h] BYREF
  idBox clipBox; // [esp+24h] [ebp-70h] BYREF
  float v21; // [esp+60h] [ebp-34h]
  float v22; // [esp+64h] [ebp-30h]
  idScreenRect v23; // [esp+6Ch] [ebp-28h] BYREF
  idBounds projectionBounds; // [esp+7Ch] [ebp-18h] BYREF

  integerValue = r_useInteractionScissors.internalVar->integerValue;
  if ( integerValue )
  {
    if ( integerValue >= 0 )
    {
      frustumState = this->frustumState;
      if ( (unsigned int)frustumState < FRUSTUM_VALID )
      {
        v5 = result;
        *result = this->lightDef->viewLight->scissorRect;
      }
      else
      {
        if ( integerValue <= 1 )
        {
          portalRect = this->lightDef->viewLight->scissorRect;
        }
        else
        {
          if ( frustumState == FRUSTUM_VALID )
          {
            for ( i = this->entityDef->entityRefs; i; i = i->ownerNext )
            {
              v8 = idBlockAlloc<areaNumRef_s,1024,16>::Alloc(&this->entityDef->world->areaNumRefAllocator);
              v8->areaNum = i->area->areaNum;
              v8->next = this->frustumAreas;
              this->frustumAreas = v8;
            }
            this->frustumAreas = idRenderWorldLocal::FloodFrustumAreas(
                                   tr.viewDef->renderWorld,
                                   &this->frustum,
                                   this->frustumAreas);
            this->frustumState = FRUSTUM_VALIDAREAS;
          }
          idScreenRect::Clear(&portalRect);
          for ( j = this->frustumAreas; j; j = j->next )
            idScreenRect::Union(&portalRect, &this->entityDef->world->areaScreenRect[j->areaNum]);
          idScreenRect::Intersect(&portalRect, &this->lightDef->viewLight->scissorRect);
        }
        if ( idScreenRect::IsEmpty(&portalRect) )
        {
          v5 = result;
          *result = portalRect;
        }
        else
        {
          lightDef = this->lightDef;
          if ( lightDef->parms.pointLight )
          {
            clipBox.center.x = lightDef->parms.origin.x;
            clipBox.center.y = lightDef->parms.origin.y;
            clipBox.center.z = lightDef->parms.origin.z;
            clipBox.extents = lightDef->parms.lightRadius;
            clipBox.axis = lightDef->parms.axis;
          }
          else
          {
            frustumTris = (float *)lightDef->frustumTris;
            v12 = *frustumTris + frustumTris[3];
            v13 = frustumTris[4] + frustumTris[1];
            v23.zmin = frustumTris[5] + frustumTris[2];
            v21 = v12 * 0.5;
            clipBox.center.x = v21;
            v22 = v13 * 0.5;
            clipBox.center.y = v22;
            v14 = v23.zmin * 0.5;
            clipBox.center.z = v14;
            v15 = frustumTris[3] - v21;
            v16 = frustumTris[4] - v22;
            v17 = frustumTris[5];
            clipBox.axis = mat3_identity;
            v23.zmin = v17 - v14;
            clipBox.extents.z = v23.zmin;
            clipBox.extents.x = v15;
            clipBox.extents.y = v16;
          }
          idFrustum::ClippedProjectionBounds(viewFrustum, &this->frustum, &clipBox, &projectionBounds);
          if ( projectionBounds.b[0].x <= (double)projectionBounds.b[1].x )
          {
            scissorRect = *R_ScreenRectFromViewFrustumBounds(&v23, &projectionBounds);
            idScreenRect::Intersect(&scissorRect, &portalRect);
            if ( r_showInteractionScissors.internalVar->integerValue > 0 )
              R_ShowColoredScreenRect(&scissorRect, this->lightDef->index);
            v5 = result;
            *result = scissorRect;
          }
          else
          {
            v5 = result;
            *result = portalRect;
          }
        }
      }
    }
    else
    {
      *result = *R_CalcIntersectionScissor(&v23, this->lightDef, this->entityDef, tr.viewDef);
      return result;
    }
  }
  else
  {
    v5 = result;
    *result = this->lightDef->viewLight->scissorRect;
  }
  return v5;
}

// FUNC: private: bool __thiscall idInteraction::CullInteractionByViewFrustum(class idFrustum const &)
char __thiscall idInteraction::CullInteractionByViewFrustum(idInteraction *this, idFrustum *viewFrustum)
{
  $648D560FF66DA77A7E41CA4D7573E7CD frustumState; // eax
  float *entityDef; // eax
  double v6; // rt0
  double v7; // st6
  double v8; // st5
  double v9; // st4
  double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st7
  idRenderLightLocal *lightDef; // eax
  float *frustumTris; // eax
  double v16; // st6
  double v17; // st7
  double v18; // st6
  double v19; // st5
  double v20; // st4
  idCVar *internalVar; // eax
  idRenderEntityLocal *v22; // eax
  double v23; // rt2
  double v24; // st6
  double v25; // st5
  double v26; // st4
  double v27; // st7
  double v28; // st6
  double v29; // st5
  double v30; // st7
  idVec3 *p_globalLightOrigin; // [esp-4h] [ebp-68h]
  float v32; // [esp+10h] [ebp-54h]
  float v33; // [esp+10h] [ebp-54h]
  float v34; // [esp+10h] [ebp-54h]
  float v35; // [esp+14h] [ebp-50h]
  float v36; // [esp+1Ch] [ebp-48h]
  float v37; // [esp+1Ch] [ebp-48h]
  float v38; // [esp+20h] [ebp-44h]
  float v39; // [esp+20h] [ebp-44h]
  float v40; // [esp+24h] [ebp-40h]
  float v41; // [esp+24h] [ebp-40h]
  float v42; // [esp+24h] [ebp-40h]
  float v43; // [esp+24h] [ebp-40h]
  float v44; // [esp+24h] [ebp-40h]
  float v45; // [esp+24h] [ebp-40h]
  float v46; // [esp+24h] [ebp-40h]
  float v47; // [esp+24h] [ebp-40h]
  idBox box; // [esp+28h] [ebp-3Ch] BYREF

  if ( !r_useInteractionCulling.internalVar->integerValue )
    return 0;
  frustumState = this->frustumState;
  if ( frustumState == FRUSTUM_INVALID )
    return 0;
  if ( frustumState == FRUSTUM_UNINITIALIZED )
  {
    entityDef = (float *)this->entityDef;
    v40 = entityDef[87] + entityDef[84];
    v6 = entityDef[86] + entityDef[83];
    v32 = (entityDef[85] + entityDef[82]) * 0.5;
    box.center.x = v32;
    v7 = v40 * 0.5;
    box.center.y = v6 * 0.5;
    box.center.z = v7;
    v8 = entityDef[85] - v32;
    v9 = entityDef[86] - v6 * 0.5;
    v41 = entityDef[87] - v7;
    box.extents.z = v41;
    box.extents.x = v8;
    box.extents.y = v9;
    v36 = v7 * entityDef[26] + v6 * 0.5 * entityDef[23] + v32 * entityDef[20];
    v38 = v7 * entityDef[27] + v6 * 0.5 * entityDef[24] + v32 * entityDef[21];
    v10 = v7 * entityDef[28] + v6 * 0.5 * entityDef[25] + v32 * entityDef[22];
    v11 = v36 + entityDef[17];
    v12 = v10;
    v13 = v38 + entityDef[18];
    v42 = v12 + entityDef[19];
    box.center.z = v42;
    box.center.x = v11;
    box.center.y = v13;
    box.axis.mat[0].x = entityDef[20];
    box.axis.mat[0].y = entityDef[21];
    box.axis.mat[0].z = entityDef[22];
    box.axis.mat[1] = *(idVec3 *)(entityDef + 23);
    box.axis.mat[2].x = entityDef[26];
    box.axis.mat[2].y = entityDef[27];
    p_globalLightOrigin = &this->lightDef->globalLightOrigin;
    box.axis.mat[2].z = entityDef[28];
    idFrustum::FromProjection(&this->frustum, &box, p_globalLightOrigin, 262144.0);
    if ( this->frustum.dFar <= (double)this->frustum.dNear )
    {
      this->frustumState = FRUSTUM_INVALID;
      return 0;
    }
    lightDef = this->lightDef;
    if ( lightDef->parms.pointLight )
    {
      box.center.x = lightDef->parms.origin.x;
      box.center.y = lightDef->parms.origin.y;
      box.center.z = lightDef->parms.origin.z;
      box.extents = lightDef->parms.lightRadius;
      box.axis = lightDef->parms.axis;
    }
    else
    {
      frustumTris = (float *)lightDef->frustumTris;
      v16 = frustumTris[4] + frustumTris[1];
      v43 = frustumTris[5] + frustumTris[2];
      v33 = (*frustumTris + frustumTris[3]) * 0.5;
      box.center.x = v33;
      v35 = v16 * 0.5;
      box.center.y = v35;
      v17 = v43 * 0.5;
      box.center.z = v17;
      v18 = frustumTris[3] - v33;
      v19 = frustumTris[4] - v35;
      v20 = frustumTris[5];
      box.axis = mat3_identity;
      v44 = v20 - v17;
      box.extents.z = v44;
      box.extents.x = v18;
      box.extents.y = v19;
    }
    idFrustum::ConstrainToBox(&this->frustum, &box);
    this->frustumState = FRUSTUM_VALID;
  }
  if ( !idFrustum::IntersectsFrustum(viewFrustum, &this->frustum) )
    return 1;
  internalVar = r_showInteractionFrustums.internalVar;
  if ( r_showInteractionFrustums.internalVar->integerValue )
  {
    if ( (_S3_0 & 1) == 0 )
    {
      colors_2[0] = colorRed;
      xmmword_110C93E0 = (__int128)colorGreen;
      xmmword_110C93F0 = (__int128)colorBlue;
      xmmword_110C9400 = (__int128)colorYellow;
      _S3_0 |= 1u;
      xmmword_110C9410 = (__int128)colorMagenta;
      xmmword_110C9420 = (__int128)colorCyan;
      xmmword_110C9430 = (__int128)colorWhite;
      xmmword_110C9440 = (__int128)colorPurple;
    }
    LOBYTE(internalVar) = r_showInteractionFrustums.internalVar->integerValue > 1;
    tr.viewDef->renderWorld->DebugFrustum(
      tr.viewDef->renderWorld,
      &colors_2[this->lightDef->index & 7],
      &this->frustum,
      (const bool)internalVar,
      0);
    if ( r_showInteractionFrustums.internalVar->integerValue > 2 )
    {
      v22 = this->entityDef;
      v45 = v22->referenceBounds.b[1].z + v22->referenceBounds.b[0].z;
      v23 = v22->referenceBounds.b[1].y + v22->referenceBounds.b[0].y;
      v34 = (v22->referenceBounds.b[1].x + v22->referenceBounds.b[0].x) * 0.5;
      box.center.x = v34;
      v24 = v45 * 0.5;
      box.center.y = v23 * 0.5;
      box.center.z = v24;
      v25 = v22->referenceBounds.b[1].x - v34;
      v26 = v22->referenceBounds.b[1].y - v23 * 0.5;
      v46 = v22->referenceBounds.b[1].z - v24;
      box.extents.z = v46;
      box.extents.x = v25;
      box.extents.y = v26;
      v37 = v24 * v22->parms.axis.mat[2].x + v23 * 0.5 * v22->parms.axis.mat[1].x + v34 * v22->parms.axis.mat[0].x;
      v39 = v24 * v22->parms.axis.mat[2].y + v23 * 0.5 * v22->parms.axis.mat[1].y + v34 * v22->parms.axis.mat[0].y;
      v27 = v24 * v22->parms.axis.mat[2].z + v23 * 0.5 * v22->parms.axis.mat[1].z + v34 * v22->parms.axis.mat[0].z;
      v28 = v37 + v22->parms.origin.x;
      v29 = v27;
      v30 = v39 + v22->parms.origin.y;
      v47 = v29 + v22->parms.origin.z;
      box.center.z = v47;
      box.center.x = v28;
      box.center.y = v30;
      box.axis = v22->parms.axis;
      tr.viewDef->renderWorld->DebugBox(tr.viewDef->renderWorld, &colorWhite, &box, 0);
    }
  }
  return 0;
}

// FUNC: private: void __thiscall idInteraction::CreateInteraction(class idRenderModel const *)
void __thiscall idInteraction::CreateInteraction(idInteraction *this, idRenderModel *model)
{
  idRenderModel *v2; // ebp
  const idMaterial *v4; // ecx
  float *v5; // eax
  idRenderLightLocal *lightDef; // ecx
  idRenderEntityLocal *entityDef; // edx
  int v8; // esi
  int v9; // eax
  int v10; // eax
  srfTriangles_s *v11; // ebx
  const idMaterial *v12; // esi
  surfaceInteraction_t *v13; // ebp
  idRenderLightLocal *v14; // eax
  idRenderEntityLocal *v15; // esi
  viewEntity_s *viewEntity; // ecx
  srfTriangles_s *ShadowVolume; // eax
  bool interactionGenerated; // [esp+Fh] [ebp-4Dh]
  int v19; // [esp+14h] [ebp-48h]
  int shadowGen; // [esp+18h] [ebp-44h]
  idMaterial *shader; // [esp+1Ch] [ebp-40h]
  int c; // [esp+20h] [ebp-3Ch]
  const idMaterial *lightShader; // [esp+24h] [ebp-38h]
  idBounds bounds; // [esp+2Ch] [ebp-30h] BYREF
  char v25[24]; // [esp+44h] [ebp-18h] BYREF

  v2 = model;
  v4 = this->lightDef->lightShader;
  ++tr.pc.c_createInteractions;
  lightShader = v4;
  v5 = (float *)model->Bounds(model, v25, &this->entityDef->parms);
  bounds.b[0].x = *v5;
  bounds.b[0].y = v5[1];
  bounds.b[0].z = v5[2];
  bounds.b[1].x = v5[3];
  lightDef = this->lightDef;
  bounds.b[1].y = v5[4];
  entityDef = this->entityDef;
  bounds.b[1].z = v5[5];
  if ( R_CullLocalBox(&bounds, entityDef->modelMatrix, 6, lightDef->frustum)
    || (v8 = 0,
        shadowGen = bounds.b[1].x - bounds.b[0].x > 3000.0,
        v9 = model->NumSurfaces(model),
        this->numSurfaces = v9,
        this->surfaces = (surfaceInteraction_t *)R_ClearedStaticAlloc(124 * v9),
        interactionGenerated = 0,
        c = 0,
        model->NumSurfaces(model) <= 0) )
  {
LABEL_42:
    idInteraction::MakeEmpty(this);
    return;
  }
  v19 = 0;
  do
  {
    v10 = (int)v2->Surface(v2, v8);
    v11 = *(srfTriangles_s **)(v10 + 8);
    if ( v11 )
    {
      v12 = R_RemapShaderBySkin(
              *(const idMaterial **)(v10 + 4),
              this->entityDef->parms.customSkin,
              this->entityDef->parms.customShader);
      shader = (idMaterial *)v12;
      if ( v12 )
      {
        if ( !R_CullLocalBox(&v11->bounds, this->entityDef->modelMatrix, 6, this->lightDef->frustum) )
        {
          v13 = &this->surfaces[v19];
          v13->shader = v12;
          v13->ambientTris = v11;
          if ( v12->spectrum != lightShader->spectrum )
          {
LABEL_39:
            v2 = model;
            goto LABEL_40;
          }
          if ( v12->numAmbientStages != v12->numStages )
          {
            if ( v11->ambientViewCount == tr.viewCount )
              v13->lightTris = R_CreateLightTris(v11, v12, this->entityDef, this->lightDef, &v13->cullInfo);
            else
              v13->lightTris = (srfTriangles_s *)-1;
            interactionGenerated = 1;
          }
          v14 = this->lightDef;
          if ( !v14->parms.noShadows && !v14->parms.noDynamicShadows )
          {
            v15 = this->entityDef;
            if ( !v15->parms.noShadow
              && idMaterial::LightCastsShadows((idMaterial *)v14->lightShader)
              && idMaterial::SurfaceCastsShadow(shader)
              && v11->silEdges )
            {
              if ( v15->parms.shadowLODDistance < 1.0 )
                goto LABEL_26;
              if ( !r_lod_shadows.internalVar->integerValue )
              {
LABEL_28:
                if ( !this->lightDef->parms.prelightModel
                  || !model->IsStaticWorldModel(model)
                  || !r_useOptimizedShadows.internalVar->integerValue )
                {
                  ShadowVolume = R_CreateShadowVolume(this->entityDef, v11, this->lightDef, shadowGen, &v13->cullInfo);
                  v13->shadowTris = ShadowVolume;
                  if ( ShadowVolume
                    && (shader->coverage != MC_OPAQUE
                     || !r_skipSuppress.internalVar->integerValue && this->entityDef->parms.suppressSurfaceInViewID) )
                  {
                    ShadowVolume->numShadowIndexesNoCaps = ShadowVolume->numIndexes;
                    v13->shadowTris->numShadowIndexesNoFrontCaps = v13->shadowTris->numIndexes;
                  }
                  interactionGenerated = 1;
                }
                goto LABEL_37;
              }
              if ( v15->parms.suppressLOD == 1
                || v15->LODModificationFrame > idLib::frameNumber
                || (viewEntity = v15->viewEntity,
                    viewEntity->screenCoverage >= (double)r_lod_shadows_percent.internalVar->floatValue)
                || viewEntity->distanceToCamera < (double)v15->parms.shadowLODDistance )
              {
LABEL_26:
                if ( r_lod_shadows.internalVar->integerValue && v15->LODModificationFrame < idLib::frameNumber )
                  this->entityDef->LODModificationFrame = idLib::frameNumber
                                                        - (int)((double)rand() * 0.000030518509 * -1000.0);
                goto LABEL_28;
              }
            }
          }
LABEL_37:
          if ( v13->lightTris != (srfTriangles_s *)-1 )
            R_FreeInteractionCullInfo(&v13->cullInfo);
          goto LABEL_39;
        }
      }
    }
LABEL_40:
    ++v19;
    v8 = ++c;
  }
  while ( c < v2->NumSurfaces(v2) );
  if ( !interactionGenerated )
    goto LABEL_42;
}

// FUNC: public: void __thiscall idInteraction::AddActiveInteraction(void)
void __thiscall idInteraction::AddActiveInteraction(idInteraction *this)
{
  idRenderLightLocal *lightDef; // eax
  viewLight_s *viewLight; // ebp
  idRenderEntityLocal *entityDef; // esi
  viewEntity_s *viewEntity; // edi
  idScreenRect *p_scissorRect; // eax
  float zmin; // ecx
  idRenderModel *v8; // eax
  idRenderModel *v9; // esi
  bool v10; // zf
  bool v11; // cc
  surfaceInteraction_t *v12; // ebp
  srfTriangles_s *ambientTris; // esi
  srfTriangles_s *lightTris; // esi
  srfTriangles_s *v15; // edi
  vertCache_s *indexCache; // edi
  const idMaterial *v17; // edi
  idRenderLightLocal *v18; // eax
  srfTriangles_s *shadowTris; // esi
  idRenderEntityLocal *v20; // eax
  int suppressShadowInViewID; // ecx
  int suppressShadowInLightID; // eax
  shadowCache_s *shadowVertexes; // ecx
  vertCache_s *shadowCache; // eax
  vertCache_s *ambientCache; // [esp-4h] [ebp-74h]
  int v26; // [esp-4h] [ebp-74h]
  bool lightScissorsEmpty; // [esp+13h] [ebp-5Dh]
  viewEntity_s *vEntity; // [esp+14h] [ebp-5Ch]
  viewLight_s *vLight; // [esp+18h] [ebp-58h]
  const idMaterial *shader; // [esp+1Ch] [ebp-54h] BYREF
  unsigned int v31; // [esp+20h] [ebp-50h]
  int i; // [esp+24h] [ebp-4Ch]
  idVec3 localLightOrigin; // [esp+28h] [ebp-48h] BYREF
  idVec3 localViewOrigin; // [esp+34h] [ebp-3Ch] BYREF
  idScreenRect shadowScissor; // [esp+40h] [ebp-30h] BYREF
  idScreenRect lightScissor; // [esp+50h] [ebp-20h] BYREF
  idScreenRect result; // [esp+60h] [ebp-10h] BYREF

  lightDef = this->lightDef;
  viewLight = lightDef->viewLight;
  entityDef = this->entityDef;
  viewEntity = entityDef->viewEntity;
  vLight = viewLight;
  vEntity = viewEntity;
  if ( lightDef->parms.noShadows
    || lightDef->parms.noDynamicShadows
    || entityDef->parms.noShadow
    || !idMaterial::LightCastsShadows((idMaterial *)lightDef->lightShader) )
  {
    p_scissorRect = &viewEntity->scissorRect;
    *(_DWORD *)&shadowScissor.x1 = *(_DWORD *)&viewEntity->scissorRect.x1;
    *(_DWORD *)&shadowScissor.x2 = *(_DWORD *)&viewEntity->scissorRect.x2;
    zmin = viewEntity->scissorRect.zmin;
  }
  else
  {
    if ( entityDef->parms.hModel->IsStaticWorldModel(entityDef->parms.hModel) )
    {
      shadowScissor = viewLight->scissorRect;
      goto LABEL_11;
    }
    if ( idInteraction::CullInteractionByViewFrustum(this, &tr.viewDef->viewFrustum) )
      return;
    p_scissorRect = idInteraction::CalcInteractionScissorRectangle(this, &result, &tr.viewDef->viewFrustum);
    *(_DWORD *)&shadowScissor.x1 = *(_DWORD *)&p_scissorRect->x1;
    *(_DWORD *)&shadowScissor.x2 = *(_DWORD *)&p_scissorRect->x2;
    zmin = p_scissorRect->zmin;
  }
  shadowScissor.zmin = zmin;
  shadowScissor.zmax = p_scissorRect->zmax;
LABEL_11:
  if ( !idScreenRect::IsEmpty(&shadowScissor) )
  {
    v8 = R_EntityDefDynamicModel(this->entityDef, 0);
    v9 = v8;
    if ( v8 )
    {
      if ( v8->NumSurfaces(v8) > 0 )
      {
        if ( this->numSurfaces != -1 && this->entityDef->dynamicModelFrameCount != this->dynamicModelFrameCount )
          idInteraction::FreeSurfaces(this);
        v10 = this->numSurfaces == -1;
        this->dynamicModelFrameCount = this->entityDef->dynamicModelFrameCount;
        if ( v10 )
          idInteraction::CreateInteraction(this, v9);
        R_GlobalPointToLocal(viewEntity->modelMatrix, &this->lightDef->globalLightOrigin, &localLightOrigin);
        R_GlobalPointToLocal(viewEntity->modelMatrix, &tr.viewDef->renderView.vieworg, &localViewOrigin);
        lightScissor = viewLight->scissorRect;
        idScreenRect::Intersect(&lightScissor, &viewEntity->scissorRect);
        lightScissorsEmpty = idScreenRect::IsEmpty(&lightScissor);
        v11 = this->numSurfaces <= 0;
        i = 0;
        if ( !v11 )
        {
          v31 = 0;
          do
          {
            v12 = &this->surfaces[v31 / 0x7C];
            if ( !lightScissorsEmpty )
            {
              ambientTris = v12->ambientTris;
              if ( ambientTris )
              {
                if ( ambientTris->ambientViewCount == tr.viewCount )
                {
                  if ( v12->lightTris == (srfTriangles_s *)-1 )
                  {
                    v12->lightTris = R_CreateLightTris(
                                       ambientTris,
                                       v12->shader,
                                       vEntity->entityDef,
                                       vLight->lightDef,
                                       &v12->cullInfo);
                    R_FreeInteractionCullInfo(&v12->cullInfo);
                  }
                  lightTris = v12->lightTris;
                  if ( v12->lightTris )
                  {
                    if ( this->lightDef->parms.globalLight
                      || !R_CullLocalBox(&lightTris->bounds, vEntity->modelMatrix, 5, tr.viewDef->frustum) )
                    {
                      v15 = v12->ambientTris;
                      if ( !v15->primBatchMesh )
                      {
                        if ( !v15->ambientCache
                          && !R_CreateAmbientCache(v15, v12->shader->numAmbientStages != v12->shader->numStages) )
                        {
                          goto LABEL_70;
                        }
                        ambientCache = v15->ambientCache;
                        lightTris->ambientCache = ambientCache;
                        idVertexCache::Touch(&vertexCache, ambientCache);
                        if ( !lightTris->lightingCache
                          && !R_CreateLightingCache(this->entityDef, this->lightDef, lightTris) )
                        {
                          goto LABEL_70;
                        }
                        if ( lightTris->lightingCache )
                          idVertexCache::Touch(&vertexCache, lightTris->lightingCache);
                        if ( !lightTris->indexCache && r_useIndexBuffers.internalVar->integerValue )
                          idVertexCache::Alloc(
                            &vertexCache,
                            lightTris->indexes,
                            4 * lightTris->numIndexes,
                            &lightTris->indexCache,
                            3);
                        indexCache = lightTris->indexCache;
                        if ( indexCache )
                          idVertexCache::Touch(&vertexCache, indexCache);
                      }
                      shader = v12->shader;
                      R_GlobalShaderOverride(&shader);
                      v17 = v12->shader;
                      v18 = this->lightDef;
                      if ( v17->coverage == MC_TRANSLUCENT )
                      {
                        R_LinkLightSurf(
                          &vLight->translucentInteractions,
                          lightTris,
                          vEntity,
                          v18,
                          shader,
                          &lightScissor,
                          0);
                      }
                      else if ( v18->parms.noShadows || (v17->materialFlags & 0x10) == 0 )
                      {
                        R_LinkLightSurf(&vLight->globalInteractions, lightTris, vEntity, v18, shader, &lightScissor, 0);
                      }
                      else
                      {
                        R_LinkLightSurf(&vLight->localInteractions, lightTris, vEntity, v18, shader, &lightScissor, 0);
                      }
                    }
                  }
                }
              }
            }
            shadowTris = v12->shadowTris;
            if ( shadowTris )
            {
              if ( r_skipSuppress.internalVar->integerValue
                || ((v20 = this->entityDef, (suppressShadowInViewID = v20->parms.suppressShadowInViewID) == 0)
                 || suppressShadowInViewID != tr.viewDef->renderView.viewID)
                && ((suppressShadowInLightID = v20->parms.suppressShadowInLightID) == 0
                 || suppressShadowInLightID != this->lightDef->parms.lightId) )
              {
                if ( !r_useShadowCulling.internalVar->integerValue
                  || shadowTris->bounds.b[0].x > (double)shadowTris->bounds.b[1].x
                  || !R_CullLocalBox(&shadowTris->bounds, vEntity->modelMatrix, 5, tr.viewDef->frustum) )
                {
                  if ( !shadowTris->primBatchMesh )
                  {
                    shadowVertexes = shadowTris->shadowVertexes;
                    if ( !shadowVertexes )
                      shadowTris->shadowCache = v12->ambientTris->shadowCache;
                    shadowCache = shadowTris->shadowCache;
                    if ( !shadowCache )
                    {
                      if ( shadowVertexes )
                      {
                        R_CreatePrivateShadowCache(shadowTris);
                      }
                      else
                      {
                        R_CreateVertexProgramShadowCache(v12->ambientTris);
                        shadowTris->shadowCache = v12->ambientTris->shadowCache;
                      }
                      shadowCache = shadowTris->shadowCache;
                      if ( !shadowCache )
                        goto LABEL_70;
                    }
                    idVertexCache::Touch(&vertexCache, shadowCache);
                    if ( !shadowTris->indexCache && r_useIndexBuffers.internalVar->integerValue )
                    {
                      idVertexCache::Alloc(
                        &vertexCache,
                        shadowTris->indexes,
                        4 * shadowTris->numIndexes,
                        &shadowTris->indexCache,
                        1);
                      idVertexCache::Touch(&vertexCache, shadowTris->indexCache);
                    }
                  }
                  v26 = R_PotentiallyInsideInfiniteShadow(v12->ambientTris, &localViewOrigin, &localLightOrigin) != 0;
                  if ( (v12->shader->materialFlags & 0x10) != 0 )
                    R_LinkLightSurf(&vLight->localShadows, shadowTris, vEntity, this->lightDef, 0, &shadowScissor, v26);
                  else
                    R_LinkLightSurf(&vLight->globalShadows, shadowTris, vEntity, this->lightDef, 0, &shadowScissor, v26);
                }
              }
            }
LABEL_70:
            v31 += 124;
            v11 = ++i < this->numSurfaces;
          }
          while ( v11 );
        }
      }
    }
  }
}

// FUNC: public: static class idInteraction * __cdecl idInteraction::AllocAndLink(class idRenderEntityLocal *,class idRenderLightLocal *)
idInteraction *__cdecl idInteraction::AllocAndLink(idRenderEntityLocal *edef, idRenderLightLocal *ldef)
{
  idInteraction *result; // eax
  idInteraction *lightNext; // ecx
  idInteraction *entityNext; // ecx

  if ( !edef || !ldef )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idInteraction::AllocAndLink: NULL parm");
  result = idBlockAlloc<idInteraction,256,16>::Alloc(&edef->world->interactionAllocator);
  result->dynamicModelFrameCount = 0;
  result->lightDef = ldef;
  result->entityDef = edef;
  result->numSurfaces = -1;
  result->surfaces = 0;
  result->frustumState = FRUSTUM_UNINITIALIZED;
  result->frustumAreas = 0;
  result->lightNext = ldef->firstInteraction;
  result->lightPrev = 0;
  ldef->firstInteraction = result;
  lightNext = result->lightNext;
  if ( lightNext )
    lightNext->lightPrev = result;
  else
    ldef->lastInteraction = result;
  result->entityNext = edef->firstInteraction;
  result->entityPrev = 0;
  edef->firstInteraction = result;
  entityNext = result->entityNext;
  if ( entityNext )
    entityNext->entityPrev = result;
  else
    edef->lastInteraction = result;
  return result;
}
