
// FUNC: void __cdecl R_CreatePrivateShadowCache(struct srfTriangles_s *)
void __cdecl R_CreatePrivateShadowCache(srfTriangles_s *tri)
{
  shadowCache_s *shadowVertexes; // ecx

  shadowVertexes = tri->shadowVertexes;
  if ( shadowVertexes )
    idVertexCache::Alloc(&vertexCache, shadowVertexes, 16 * tri->numVerts, &tri->shadowCache, 0);
}

// FUNC: void __cdecl R_CreateVertexProgramShadowCache(struct srfTriangles_s *)
void __cdecl R_CreateVertexProgramShadowCache(srfTriangles_s *tri)
{
  int v2; // eax
  void *v3; // esp
  _BYTE v4[12]; // [esp+0h] [ebp-Ch] BYREF
  idDrawVert *tria; // [esp+14h] [ebp+8h]

  tria = tri->verts;
  if ( tria )
  {
    v2 = 32 * tri->numVerts + 18;
    LOBYTE(v2) = v2 & 0xFC;
    v3 = alloca(v2);
    SIMDProcessor->CreateVertexProgramShadowCache(SIMDProcessor, (idVec4 *)v4, tria, tri->numVerts);
    idVertexCache::Alloc(&vertexCache, v4, 32 * tri->numVerts, &tri->shadowCache, 0);
  }
}

// FUNC: void __cdecl R_SkyboxTexGen(struct drawSurf_s *,class idVec3 const &)
void __cdecl R_SkyboxTexGen(drawSurf_s *surf, const idVec3 *viewOrg)
{
  float *v3; // eax
  int numVerts; // esi
  int v5; // ebx
  int v6; // eax
  void *v7; // esp
  idVec3 *v8; // edx
  int v9; // eax
  idVec3 *p_localViewOrigin; // ecx
  float *p_z; // eax
  unsigned int v12; // edx
  double v13; // st7
  int v14; // esi
  int v15; // ecx
  float *v16; // eax
  double v17; // st7
  _BYTE v18[8]; // [esp+4h] [ebp-20h] BYREF
  idVec3 localViewOrigin; // [esp+Ch] [ebp-18h] BYREF
  idVec3 *texCoords; // [esp+18h] [ebp-Ch]
  int size; // [esp+1Ch] [ebp-8h]
  const idDrawVert *verts; // [esp+20h] [ebp-4h]
  int i; // [esp+2Ch] [ebp+8h]

  R_GlobalPointToLocal(surf->space->modelMatrix, viewOrg, &localViewOrigin);
  if ( surf->geo->primBatchMesh )
  {
    surf->dynamicTexCoords = 0;
    v3 = (float *)R_FrameAlloc(64);
    surf->texGenTransformAndViewOrg = v3;
    *v3 = 1.0;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 1) = 0;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 2) = 0;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 3) = 0;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 4) = 0;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 5) = 1065353216;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 6) = 0;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 7) = 0;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 8) = 0;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 9) = 0;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 10) = 1065353216;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 11) = 0;
    *((idVec3 *)surf->texGenTransformAndViewOrg + 4) = localViewOrigin;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 15) = 1065353216;
  }
  else
  {
    numVerts = surf->geo->numVerts;
    v5 = 12 * numVerts;
    v6 = 12 * numVerts + 18;
    LOBYTE(v6) = v6 & 0xFC;
    size = 12 * numVerts;
    v7 = alloca(v6);
    v8 = (idVec3 *)v18;
    verts = surf->geo->verts;
    v9 = 0;
    texCoords = (idVec3 *)v18;
    i = 0;
    if ( numVerts >= 4 )
    {
      p_localViewOrigin = &localViewOrigin;
      p_z = &verts->xyz.z;
      v12 = ((unsigned int)(numVerts - 4) >> 2) + 1;
      i = 4 * v12;
      do
      {
        v13 = *(p_z - 2);
        p_z += 64;
        p_localViewOrigin += 4;
        --v12;
        p_localViewOrigin[-5].y = v13 - localViewOrigin.x;
        p_localViewOrigin[-5].z = *(p_z - 65) - localViewOrigin.y;
        p_localViewOrigin[-4].x = *(p_z - 64) - localViewOrigin.z;
        p_localViewOrigin[-4].y = *(p_z - 50) - localViewOrigin.x;
        p_localViewOrigin[-4].z = *(p_z - 49) - localViewOrigin.y;
        p_localViewOrigin[-3].x = *(p_z - 48) - localViewOrigin.z;
        p_localViewOrigin[-3].y = *(p_z - 34) - localViewOrigin.x;
        p_localViewOrigin[-3].z = *(p_z - 33) - localViewOrigin.y;
        p_localViewOrigin[-2].x = *(p_z - 32) - localViewOrigin.z;
        p_localViewOrigin[-2].y = *(p_z - 18) - localViewOrigin.x;
        p_localViewOrigin[-2].z = *(p_z - 17) - localViewOrigin.y;
        p_localViewOrigin[-1].x = *(p_z - 16) - localViewOrigin.z;
      }
      while ( v12 );
      v5 = size;
      v8 = texCoords;
      v9 = i;
    }
    if ( v9 < numVerts )
    {
      v14 = numVerts - i;
      v15 = (int)&v8[v9].z;
      v16 = &verts[v9].xyz.z;
      do
      {
        v17 = *(v16 - 2);
        v16 += 16;
        v15 += 12;
        --v14;
        *(float *)(v15 - 20) = v17 - localViewOrigin.x;
        *(float *)(v15 - 16) = *(v16 - 17) - localViewOrigin.y;
        *(float *)(v15 - 12) = *(v16 - 16) - localViewOrigin.z;
      }
      while ( v14 );
      v5 = size;
    }
    surf->dynamicTexCoords = idVertexCache::AllocFrameTemp(&vertexCache, v8, v5, 0);
  }
}

// FUNC: R_SpecularTexGen
void __cdecl R_SpecularTexGen(drawSurf_s *surf, const idVec3 *viewOrg)
{
  const idVec3 *globalLightOrigin; // ecx
  const srfTriangles_s *geo; // esi
  int v4; // edi
  int v5; // eax
  void *v6; // esp
  idVec3 localLightOrigin; // [esp+Ch] [ebp-1Ch] BYREF
  idVec3 localViewOrigin; // [esp+18h] [ebp-10h] BYREF
  int numVerts; // [esp+24h] [ebp-4h]

  R_GlobalPointToLocal(surf->space->modelMatrix, globalLightOrigin, &localLightOrigin);
  R_GlobalPointToLocal(surf->space->modelMatrix, viewOrg, &localViewOrigin);
  geo = surf->geo;
  numVerts = surf->geo->numVerts;
  v4 = 16 * numVerts;
  v5 = 16 * numVerts + 18;
  LOBYTE(v5) = v5 & 0xFC;
  v6 = alloca(v5);
  SIMDProcessor->CreateSpecularTextureCoords(
    SIMDProcessor,
    (idVec4 *)&localLightOrigin,
    &localLightOrigin,
    &localViewOrigin,
    geo->verts,
    numVerts,
    geo->indexes,
    geo->numIndexes);
  surf->dynamicTexCoords = idVertexCache::AllocFrameTemp(&vertexCache, &localLightOrigin, v4, 0);
}

// FUNC: struct viewEntity_s * __cdecl R_SetEntityDefViewEntity(class idRenderEntityLocal *)
viewEntity_s *__cdecl R_SetEntityDefViewEntity(idRenderEntityLocal *def)
{
  viewEntity_s *v2; // esi
  float *entityDef; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5

  if ( def->viewCount == tr.viewCount )
    return def->viewEntity;
  def->viewCount = tr.viewCount;
  v2 = (viewEntity_s *)R_ClearedFrameAlloc(168);
  v2->entityDef = def;
  idScreenRect::Clear(&v2->scissorRect);
  v2->modelDepthHack = def->parms.modelDepthHack;
  v2->weaponDepthHackInViewID = def->parms.weaponDepthHackInViewID;
  R_AxisToModelMatrix(&def->parms.axis, &def->parms.origin, v2->modelMatrix);
  if ( tr.viewDef )
  {
    myGlMultMatrix(v2->modelMatrix, tr.viewDef->worldSpace.modelViewMatrix, v2->modelViewMatrix);
    entityDef = (float *)v2->entityDef;
    v4 = entityDef[17] - tr.viewDef->renderView.vieworg.x;
    entityDef += 17;
    v5 = entityDef[1] - tr.viewDef->renderView.vieworg.y;
    v6 = entityDef[2] - tr.viewDef->renderView.vieworg.z;
    v2->distanceToCamera = v6 * v6 + v4 * v4 + v5 * v5;
    v2->next = tr.viewDef->viewEntitys;
    tr.viewDef->viewEntitys = v2;
  }
  def->viewEntity = v2;
  return v2;
}

// FUNC: struct viewEffect_s * __cdecl R_SetEffectDefViewEntity(class rvRenderEffectLocal *)
viewEffect_s *__cdecl R_SetEffectDefViewEntity(rvRenderEffectLocal *def)
{
  viewEffect_s *v2; // esi
  float *effectDef; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5

  if ( def->viewCount == tr.viewCount )
    return def->viewEffect;
  def->viewCount = tr.viewCount;
  v2 = (viewEffect_s *)R_ClearedFrameAlloc(164);
  v2->effectDef = def;
  idScreenRect::Clear(&v2->scissorRect);
  v2->modelDepthHack = def->parms.modelDepthHack;
  v2->weaponDepthHackInViewID = def->parms.weaponDepthHackInViewID;
  R_AxisToModelMatrix(&def->parms.axis, &def->parms.origin, v2->modelMatrix);
  if ( tr.viewDef )
  {
    myGlMultMatrix(v2->modelMatrix, tr.viewDef->worldSpace.modelViewMatrix, v2->modelViewMatrix);
    effectDef = (float *)v2->effectDef;
    v4 = effectDef[6] - tr.viewDef->renderView.vieworg.x;
    effectDef += 6;
    v5 = effectDef[1] - tr.viewDef->renderView.vieworg.y;
    v6 = effectDef[2] - tr.viewDef->renderView.vieworg.z;
    v2->distanceToCamera = v6 * v6 + v4 * v4 + v5 * v5;
    v2->next = tr.viewDef->viewEffects;
    tr.viewDef->viewEffects = v2;
  }
  def->viewEffect = v2;
  return v2;
}

// FUNC: int __cdecl R_SortViewEntities(struct viewEntity_s * * *)
unsigned int __cdecl R_SortViewEntities(viewEntity_s ***array)
{
  viewEntity_s *viewEntitys; // eax
  unsigned int i; // esi
  viewEntity_s **v3; // eax
  viewEntity_s **v4; // ecx
  viewEntity_s *j; // eax

  viewEntitys = tr.viewDef->viewEntitys;
  for ( i = 0; viewEntitys; ++i )
    viewEntitys = viewEntitys->next;
  v3 = (viewEntity_s **)R_FrameAlloc(4 * i);
  *array = v3;
  v4 = v3;
  for ( j = tr.viewDef->viewEntitys; j; ++v4 )
  {
    *v4 = j;
    j = j->next;
  }
  qsort(*array, i, 4u, compareEffect);
  return i;
}

// FUNC: int __cdecl R_SortViewEffects(struct viewEffect_s * * *)
unsigned int __cdecl R_SortViewEffects(viewEffect_s ***array)
{
  viewEffect_s *viewEffects; // eax
  unsigned int i; // esi
  viewEffect_s **v3; // eax
  viewEffect_s **v4; // ecx
  viewEffect_s *j; // eax

  viewEffects = tr.viewDef->viewEffects;
  for ( i = 0; viewEffects; ++i )
    viewEffects = viewEffects->next;
  v3 = (viewEffect_s **)R_FrameAlloc(4 * i);
  *array = v3;
  v4 = v3;
  for ( j = tr.viewDef->viewEffects; j; ++v4 )
  {
    *v4 = j;
    j = j->next;
  }
  qsort(*array, i, 4u, compareEffect);
  return i;
}

// FUNC: bool __cdecl R_CreateAmbientCache(struct srfTriangles_s *,bool)
bool __cdecl R_CreateAmbientCache(srfTriangles_s *tri, bool needsLighting)
{
  vertCache_s **p_ambientCache; // edi

  p_ambientCache = &tri->ambientCache;
  if ( tri->ambientCache )
    return 1;
  if ( needsLighting && !tri->tangentsCalculated )
    R_DeriveTangents(tri, 1);
  idVertexCache::Alloc(&vertexCache, tri->verts, tri->numVerts << 6, p_ambientCache, 0);
  return *p_ambientCache != 0;
}

// FUNC: bool __cdecl R_CreateLightingCache(class idRenderEntityLocal const *,class idRenderLightLocal const *,struct srfTriangles_s *)
bool __cdecl R_CreateLightingCache(
        const idRenderEntityLocal *ent,
        const idRenderLightLocal *light,
        srfTriangles_s *tri)
{
  const idMaterial *lightShader; // ecx
  int v4; // edi
  int v5; // eax
  void *v6; // esp
  idVec3 localLightOrigin; // [esp+Ch] [ebp-Ch] BYREF

  lightShader = light->lightShader;
  if ( lightShader->fogLight || lightShader->blendLight || tr.backEndRendererHasVertexPrograms )
    return 1;
  R_GlobalPointToLocal(ent->modelMatrix, &light->globalLightOrigin, &localLightOrigin);
  v4 = 12 * tri->ambientSurface->numVerts;
  v5 = v4 + 18;
  LOBYTE(v5) = (v4 + 18) & 0xFC;
  v6 = alloca(v5);
  SIMDProcessor->CreateTextureSpaceLightVectors(
    SIMDProcessor,
    &localLightOrigin,
    &localLightOrigin,
    tri->ambientSurface->verts,
    tri->ambientSurface->numVerts,
    tri->indexes,
    tri->numIndexes);
  idVertexCache::Alloc(&vertexCache, &localLightOrigin, v4, &tri->lightingCache, 0);
  return tri->lightingCache != 0;
}

// FUNC: void __cdecl R_WobbleskyTexGen(struct drawSurf_s *,class idVec3 const &)
void __cdecl R_WobbleskyTexGen(drawSurf_s *surf, const idVec3 *viewOrg)
{
  const idMaterial *material; // eax
  const float *shaderRegisters; // ecx
  double v5; // st7
  int v6; // edx
  int v7; // eax
  long double v8; // st7
  long double v9; // st7
  double v10; // st6
  long double v11; // st5
  double v12; // st4
  long double v13; // st4
  long double v14; // st5
  double v15; // st4
  long double v16; // st3
  long double v17; // rt0
  long double v18; // st3
  long double v19; // st2
  const viewEntity_s *space; // ecx
  long double v21; // st2
  float *texGenTransformAndViewOrg; // edx
  float v23; // eax
  int numVerts; // ebx
  int v25; // esi
  int v26; // eax
  void *v27; // esp
  idDrawVert *verts; // ecx
  float v29; // eax
  float *p_z; // esi
  float transform[16]; // [esp+Ch] [ebp-1Ch] BYREF
  idVec3 v; // [esp+4Ch] [ebp+24h] BYREF
  idVec3 axis[3]; // [esp+58h] [ebp+30h]
  float rotateSpeed; // [esp+7Ch] [ebp+54h]
  idVec3 localViewOrigin; // [esp+80h] [ebp+58h] BYREF
  float a; // [esp+8Ch] [ebp+64h]
  float v37; // [esp+90h] [ebp+68h]
  float c; // [esp+94h] [ebp+6Ch]
  float s; // [esp+A0h] [ebp+78h]
  float sb; // [esp+A0h] [ebp+78h]
  idVec3 *sa; // [esp+A0h] [ebp+78h]

  material = surf->material;
  shaderRegisters = surf->shaderRegisters;
  v5 = 3.1415927 * shaderRegisters[material->texGenRegisters[0]];
  v6 = material->texGenRegisters[2];
  v7 = material->texGenRegisters[1];
  v8 = v5 * 0.0055555557;
  rotateSpeed = 3.1415927 * shaderRegisters[v6] * 0.033333335;
  a = 3.1415927 * shaderRegisters[v7] * 0.033333335 * tr.viewDef->floatTime;
  v37 = sin(v8);
  s = sin(a) * v37;
  axis[2].y = s;
  localViewOrigin.y = s;
  c = cos(a) * v37;
  v9 = cos(v8);
  v10 = c;
  axis[2].x = c;
  axis[2].z = v9;
  localViewOrigin.x = c;
  localViewOrigin.z = axis[2].z;
  v11 = -(sin(a + a) * v37);
  v12 = -(v37 * s);
  axis[1].z = v12;
  axis[1].y = sqrt(1.0 - (v12 * axis[1].z + v11 * v11));
  v13 = axis[1].z * v9 + axis[1].y * s + v11 * c;
  v.x = c * v13;
  v.y = s * v13;
  v.z = axis[2].z * v13;
  v14 = v11 - v.x;
  v15 = axis[1].y - v.y;
  axis[1].z = axis[1].z - v.z;
  v16 = v15 * v15 + axis[1].z * axis[1].z + v14 * v14;
  if ( v16 != 0.0 )
  {
    v17 = 1.0 / sqrt(v16);
    v14 = v14 * v17;
    v15 = v15 * v17;
    axis[1].z = axis[1].z * v17;
  }
  v18 = v15 * v9 - axis[1].z * s;
  axis[0].y = axis[1].z * c - v14 * v9;
  axis[0].z = v14 * s - v15 * c;
  v19 = rotateSpeed * tr.viewDef->floatTime;
  transform[6] = axis[2].y;
  space = surf->space;
  memset(&transform[11], 0, 16);
  transform[7] = 0.0;
  transform[3] = 0.0;
  sb = sin(v19);
  v21 = cos(v19);
  c = v21;
  transform[0] = v21 * v18 + v14 * sb;
  transform[4] = axis[0].y * c + v15 * sb;
  transform[8] = axis[0].z * c + axis[1].z * sb;
  transform[1] = v14 * c - v18 * sb;
  transform[5] = v15 * c - axis[0].y * sb;
  transform[9] = axis[1].z * c - axis[0].z * sb;
  transform[2] = v10;
  transform[10] = v9;
  R_GlobalPointToLocal(space->modelMatrix, viewOrg, &localViewOrigin);
  if ( surf->geo->primBatchMesh )
  {
    texGenTransformAndViewOrg = surf->texGenTransformAndViewOrg;
    v23 = transform[0];
    surf->dynamicTexCoords = 0;
    *texGenTransformAndViewOrg = v23;
    surf->texGenTransformAndViewOrg[1] = transform[4];
    surf->texGenTransformAndViewOrg[2] = transform[8];
    surf->texGenTransformAndViewOrg[3] = transform[12];
    surf->texGenTransformAndViewOrg[4] = transform[1];
    surf->texGenTransformAndViewOrg[5] = transform[5];
    surf->texGenTransformAndViewOrg[6] = transform[9];
    surf->texGenTransformAndViewOrg[7] = transform[13];
    surf->texGenTransformAndViewOrg[8] = transform[2];
    surf->texGenTransformAndViewOrg[9] = transform[6];
    surf->texGenTransformAndViewOrg[10] = transform[10];
    surf->texGenTransformAndViewOrg[11] = transform[14];
    *((idVec3 *)surf->texGenTransformAndViewOrg + 4) = localViewOrigin;
    *((_DWORD *)surf->texGenTransformAndViewOrg + 15) = 1065353216;
  }
  else
  {
    numVerts = surf->geo->numVerts;
    v25 = 12 * numVerts;
    v26 = 12 * numVerts + 18;
    LOBYTE(v26) = v26 & 0xFC;
    LODWORD(a) = 12 * numVerts;
    v27 = alloca(v26);
    verts = surf->geo->verts;
    v29 = COERCE_FLOAT((float *)((char *)transform + 3));
    LOBYTE(v29) = ((unsigned __int8)transform + 3) & 0xF0;
    rotateSpeed = v29;
    if ( numVerts > 0 )
    {
      sa = (idVec3 *)LODWORD(v29);
      p_z = &verts->xyz.z;
      do
      {
        v.x = *(p_z - 2) - localViewOrigin.x;
        v.y = *(p_z - 1) - localViewOrigin.y;
        v.z = *p_z - localViewOrigin.z;
        R_LocalPointToGlobal(transform, &v, sa++);
        p_z += 16;
        --numVerts;
      }
      while ( numVerts );
      v29 = rotateSpeed;
      v25 = LODWORD(a);
    }
    surf->dynamicTexCoords = idVertexCache::AllocFrameTemp(&vertexCache, (void *)LODWORD(v29), v25, 0);
  }
}

// FUNC: void __cdecl R_POTCorrectionTexGen(struct drawSurf_s *)
void __cdecl R_POTCorrectionTexGen(drawSurf_s *surf)
{
  const idMaterial *material; // eax
  int numStages; // edx
  int v3; // ecx
  shaderStage_t *i; // eax
  idImage *image; // ecx
  newShaderStage_t *newStage; // edx
  rvNewShaderStage *newShaderStage; // eax
  int numVerts; // edi
  int v9; // ebx
  int v10; // eax
  void *v11; // esp
  double v12; // st7
  const idDrawVert *v13; // eax
  int v14; // edx
  float *p_y; // eax
  unsigned int v16; // ebx
  idVec2 *p_correctionFactor; // ecx
  int v18; // eax
  double v19; // st7
  int v20; // [esp-8h] [ebp-28h]
  _BYTE v21[8]; // [esp+4h] [ebp-1Ch] BYREF
  idVec2 correctionFactor; // [esp+Ch] [ebp-14h] BYREF
  int size; // [esp+14h] [ebp-Ch]
  const idDrawVert *verts; // [esp+18h] [ebp-8h]
  int res; // [esp+1Ch] [ebp-4h]

  material = surf->material;
  numStages = material->numStages;
  v3 = 0;
  if ( numStages > 0 )
  {
    for ( i = material->stages; i->texture.texgen != TG_POT_CORRECTION; ++i )
    {
      if ( ++v3 >= numStages )
        return;
    }
    image = i->texture.image;
    if ( image )
      goto LABEL_12;
    newStage = i->newStage;
    if ( newStage )
    {
      image = newStage->fragmentProgramImages[0];
    }
    else
    {
      newShaderStage = i->newShaderStage;
      if ( newShaderStage )
        image = newShaderStage->textureParmImages[0];
    }
    if ( image )
    {
LABEL_12:
      numVerts = surf->geo->numVerts;
      v9 = 8 * numVerts;
      v10 = 8 * numVerts + 18;
      LOBYTE(v10) = v10 & 0xFC;
      size = 8 * numVerts;
      v11 = alloca(v10);
      res = tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1 + 1;
      *(float *)&verts = (float)res;
      *(float *)&res = COERCE_FLOAT(MakePowerOfTwo(res));
      v20 = tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1 + 1;
      correctionFactor.x = *(float *)&verts / (double)res;
      *(float *)&res = (float)v20;
      *(float *)&verts = COERCE_FLOAT(MakePowerOfTwo(v20));
      v12 = (double)(int)verts;
      v13 = surf->geo->verts;
      v14 = 0;
      verts = v13;
      correctionFactor.y = *(float *)&res / v12;
      if ( numVerts >= 4 )
      {
        p_y = &v13->st.y;
        v16 = ((unsigned int)(numVerts - 4) >> 2) + 1;
        p_correctionFactor = &correctionFactor;
        v14 = 4 * v16;
        do
        {
          p_y += 64;
          p_correctionFactor += 4;
          --v16;
          p_correctionFactor[-5].x = correctionFactor.x * *(p_y - 65);
          p_correctionFactor[-5].y = correctionFactor.y * *(p_y - 64);
          p_correctionFactor[-4].x = correctionFactor.x * *(p_y - 49);
          p_correctionFactor[-4].y = correctionFactor.y * *(p_y - 48);
          p_correctionFactor[-3].x = correctionFactor.x * *(p_y - 33);
          p_correctionFactor[-3].y = correctionFactor.y * *(p_y - 32);
          p_correctionFactor[-2].x = correctionFactor.x * *(p_y - 17);
          p_correctionFactor[-2].y = correctionFactor.y * *(p_y - 16);
        }
        while ( v16 );
        v9 = size;
        v13 = verts;
      }
      if ( v14 < numVerts )
      {
        v18 = (int)&v13[v14].st.y;
        do
        {
          ++v14;
          v19 = correctionFactor.x * *(float *)(v18 - 4);
          v18 += 64;
          *(float *)&v21[8 * v14 - 8] = v19;
          *(float *)&v21[8 * v14 - 4] = correctionFactor.y * *(float *)(v18 - 64);
        }
        while ( v14 < numVerts );
      }
      surf->dynamicTexCoords = idVertexCache::AllocFrameTemp(&vertexCache, v21, v9, 0);
    }
  }
}

// FUNC: R_TestPointInViewLight
char __usercall R_TestPointInViewLight@<al>(const idVec3 *org@<esi>, const idRenderLightLocal *light@<ecx>)
{
  int v2; // edx
  float *i; // ecx

  v2 = 0;
  for ( i = &light->frustum[0].b; *(i - 1) * org->x + i[1] * org->z + org->y * *i + i[2] <= 32.0; i += 4 )
  {
    if ( ++v2 >= 6 )
      return 1;
  }
  return 0;
}

// FUNC: struct viewLight_s * __cdecl R_SetLightDefViewLight(class idRenderLightLocal *)
viewLight_s *__cdecl R_SetLightDefViewLight(idRenderLightLocal *light)
{
  viewLight_s *v2; // edi
  char v3; // al
  viewDef_s *viewDef; // ebp
  int v5; // ecx
  float *p_b; // esi
  int v7; // esi
  float *v8; // ecx
  char v9; // al

  if ( light->viewCount == tr.viewCount )
    return light->viewLight;
  light->viewCount = tr.viewCount;
  v2 = (viewLight_s *)R_ClearedFrameAlloc(160);
  v2->lightDef = light;
  idScreenRect::Clear(&v2->scissorRect);
  v3 = R_TestPointInViewLight(&tr.viewDef->renderView.vieworg, light);
  v2->viewInsideLight = v3;
  if ( v3 )
  {
    v2->viewSeesShadowPlaneBits = 63;
    viewDef = tr.viewDef;
  }
  else
  {
    v2->viewSeesShadowPlaneBits = 0;
    viewDef = tr.viewDef;
    v5 = 0;
    if ( light->numShadowFrustums > 0 )
    {
      p_b = &light->shadowFrustums[0].planes[5].b;
      do
      {
        if ( p_b[1] * viewDef->renderView.vieworg.z
           + *(p_b - 1) * viewDef->renderView.vieworg.x
           + viewDef->renderView.vieworg.y * *p_b
           + p_b[2] < 32.0 )
        {
          v2->viewSeesShadowPlaneBits |= 1 << v5;
          viewDef = tr.viewDef;
        }
        ++v5;
        p_b += 26;
      }
      while ( v5 < light->numShadowFrustums );
    }
  }
  v7 = 0;
  v8 = &viewDef->frustum[0].b;
  while ( *(v8 - 1) * light->globalLightOrigin.x
        + v8[1] * light->globalLightOrigin.z
        + light->globalLightOrigin.y * *v8
        + v8[2] <= 0.0 )
  {
    ++v7;
    v8 += 4;
    if ( v7 >= 4 )
    {
      v9 = 1;
      goto LABEL_15;
    }
  }
  v9 = 0;
LABEL_15:
  v2->viewSeesGlobalLightOrigin = v9;
  v2->globalLightOrigin = light->globalLightOrigin;
  v2->lightProject[0].a = light->lightProject[0].a;
  v2->lightProject[0].b = light->lightProject[0].b;
  v2->lightProject[0].c = light->lightProject[0].c;
  v2->lightProject[0].d = light->lightProject[0].d;
  v2->lightProject[1] = light->lightProject[1];
  v2->lightProject[2] = light->lightProject[2];
  v2->lightProject[3] = light->lightProject[3];
  v2->fogPlane = light->frustum[5];
  v2->frustumTris = light->frustumTris;
  v2->falloffImage = light->falloffImage;
  v2->lightShader = light->lightShader;
  v2->shaderRegisters = 0;
  v2->next = tr.viewDef->viewLights;
  tr.viewDef->viewLights = v2;
  light->viewLight = v2;
  return v2;
}

// FUNC: void __cdecl R_LinkLightSurf(struct drawSurf_s const * *,struct srfTriangles_s const *,struct viewEntity_s const *,class idRenderLightLocal const *,class idMaterial const *,class idScreenRect const &,int)
void __cdecl R_LinkLightSurf(
        const drawSurf_s **link,
        const srfTriangles_s *tri,
        viewEntity_s *space,
        const idRenderLightLocal *light,
        idMaterial *shader,
        const idScreenRect *scissor,
        int dsFlags)
{
  int integerValue; // eax
  viewEntity_s *p_worldSpace; // ebx
  drawSurf_s *v9; // esi
  float *v10; // eax
  float *v11; // eax

  integerValue = r_limitBatchSize.internalVar->integerValue;
  if ( integerValue <= 0 || tri->numIndexes > integerValue )
  {
    p_worldSpace = space;
    if ( !space )
      p_worldSpace = &tr.viewDef->worldSpace;
    v9 = (drawSurf_s *)R_FrameAlloc(56);
    v9->geo = tri;
    v9->space = p_worldSpace;
    v9->material = shader;
    v9->scissorRect = *scissor;
    v9->dsFlags = dsFlags;
    if ( shader )
    {
      v10 = idMaterial::ConstantRegisters(shader);
      if ( v10 )
      {
        v9->shaderRegisters = v10;
      }
      else
      {
        v11 = (float *)R_FrameAlloc(4 * shader->numRegisters);
        v9->shaderRegisters = v11;
        idMaterial::EvaluateRegisters(
          shader,
          v11,
          p_worldSpace->entityDef->parms.shaderParms,
          tr.viewDef,
          p_worldSpace->entityDef->parms.referenceSoundHandle,
          0);
      }
      if ( tr.backEndRendererHasVertexPrograms
        || r_skipSpecular.internalVar->integerValue
        || tr.backEndRenderer == BE_ARB
        || (R_SpecularTexGen(v9, &tr.viewDef->renderView.vieworg), v9->dynamicTexCoords) )
      {
        v9->nextOnLight = *link;
        *link = v9;
      }
    }
    else
    {
      v9->shaderRegisters = 0;
      v9->nextOnLight = *link;
      *link = v9;
    }
  }
}

// FUNC: class idScreenRect __cdecl R_ClippedLightScissorRectangle(struct viewLight_s *)
idScreenRect *__cdecl R_ClippedLightScissorRectangle(idScreenRect *result, viewLight_s *vLight)
{
  idRenderLightLocal *lightDef; // esi
  float *p_b; // ebp
  viewDef_s *viewDef; // edx
  idWinding *v5; // esi
  int numPoints; // eax
  bool v7; // al
  int v8; // esi
  int v9; // ecx
  int v10; // eax
  float *p_x; // edx
  idVec5 *v12; // edi
  double v13; // st7
  double v14; // st6
  double v15; // st5
  int v16; // edi
  int v17; // esi
  double x2; // st7
  double x1; // st7
  double y2; // st7
  double y1; // st7
  bool v22; // zf
  int v23; // esi
  int v24; // edi
  float zmin; // ebp
  float zmax; // ebx
  idScreenRect *v27; // eax
  float *windowX; // [esp+10h] [ebp-57Ch]
  float windowXa; // [esp+10h] [ebp-57Ch]
  float windowY; // [esp+18h] [ebp-574h]
  float windowYa; // [esp+18h] [ebp-574h]
  idWinding **frustumWindings; // [esp+1Ch] [ebp-570h]
  int v33; // [esp+20h] [ebp-56Ch]
  idScreenRect r; // [esp+24h] [ebp-568h] BYREF
  idPlane plane; // [esp+34h] [ebp-558h] BYREF
  idVec3 ndc; // [esp+44h] [ebp-548h] BYREF
  idPlane clip; // [esp+50h] [ebp-53Ch] BYREF
  idPlane eye; // [esp+60h] [ebp-52Ch] BYREF
  idFixedWinding w; // [esp+70h] [ebp-51Ch] BYREF
  int v40; // [esp+588h] [ebp-4h]

  lightDef = vLight->lightDef;
  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v40 = 0;
  idScreenRect::Clear(&r);
  p_b = &lightDef->frustum[0].b;
  frustumWindings = lightDef->frustumWindings;
  viewDef = tr.viewDef;
  windowX = &lightDef->frustum[0].b;
  v33 = 6;
  do
  {
    v5 = *frustumWindings;
    if ( *frustumWindings
      && p_b[1] * viewDef->renderView.vieworg.z
       + viewDef->renderView.vieworg.y * *p_b
       + *(p_b - 1) * viewDef->renderView.vieworg.x
       + p_b[2] < 0.0 )
    {
      numPoints = v5->numPoints;
      if ( numPoints <= w.allocedSize || (v7 = w.ReAllocate(&w, numPoints, 0), viewDef = tr.viewDef, v7) )
      {
        v9 = 0;
        if ( v5->numPoints > 0 )
        {
          v10 = 0;
          do
          {
            p_x = &v5->p[v10].x;
            v12 = &w.p[v10];
            v12->x = *p_x;
            v12->y = p_x[1];
            v12->z = p_x[2];
            v12->s = p_x[3];
            ++v9;
            v12->t = p_x[4];
            ++v10;
          }
          while ( v9 < v5->numPoints );
          viewDef = tr.viewDef;
          p_b = windowX;
        }
        w.numPoints = v5->numPoints;
        v8 = 480;
      }
      else
      {
        w.numPoints = 0;
        v8 = 480;
      }
      while ( 1 )
      {
        v13 = -*(float *)((char *)&viewDef->renderView.width + v8);
        v14 = -*(float *)((char *)&viewDef->renderView.y + v8);
        v15 = -*(float *)((char *)&viewDef->renderView.x + v8);
        plane.a = -*(float *)((char *)&viewDef->renderView.viewID + v8);
        plane.b = v15;
        plane.c = v14;
        plane.d = v13;
        if ( !idWinding::ClipInPlace(&w, &plane, 0.1, 0) )
          break;
        v8 += 16;
        if ( v8 >= 560 )
          break;
        viewDef = tr.viewDef;
      }
      v16 = 0;
      if ( w.numPoints > 0 )
      {
        v17 = 0;
        do
        {
          R_TransformModelToClip(
            (const idVec3 *)&w.p[v17],
            tr.viewDef->worldSpace.modelViewMatrix,
            tr.viewDef->projectionMatrix,
            &eye,
            &clip);
          if ( clip.d <= 0.0099999998 )
            clip.d = 0.0099999998;
          R_TransformClipToDevice(&clip, tr.viewDef, &ndc);
          windowXa = (double)(tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1) * (ndc.x + 1.0) * 0.5;
          windowY = (double)(tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1) * (ndc.y + 1.0) * 0.5;
          x2 = (double)tr.viewDef->scissor.x2;
          if ( windowXa <= x2 )
          {
            x1 = (double)tr.viewDef->scissor.x1;
            if ( windowXa < x1 )
              windowXa = x1;
          }
          else
          {
            windowXa = x2;
          }
          y2 = (double)tr.viewDef->scissor.y2;
          if ( windowY <= y2 )
          {
            y1 = (double)tr.viewDef->scissor.y1;
            if ( windowY < y1 )
              windowY = y1;
            idScreenRect::AddPoint(&r, windowXa, windowY);
          }
          else
          {
            windowYa = y2;
            idScreenRect::AddPoint(&r, windowXa, windowYa);
          }
          ++v16;
          ++v17;
        }
        while ( v16 < w.numPoints );
      }
      viewDef = tr.viewDef;
    }
    ++frustumWindings;
    p_b += 4;
    v22 = v33-- == 1;
    windowX = p_b;
  }
  while ( !v22 );
  idScreenRect::Expand(&r);
  v23 = *(_DWORD *)&r.x1;
  v24 = *(_DWORD *)&r.x2;
  zmin = r.zmin;
  zmax = r.zmax;
  v40 = -1;
  w.p = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
  v27 = result;
  *(_DWORD *)&result->x1 = v23;
  *(_DWORD *)&result->x2 = v24;
  result->zmin = zmin;
  result->zmax = zmax;
  return v27;
}

// FUNC: class idScreenRect __cdecl R_CalcLightScissorRectangle(struct viewLight_s *)
idScreenRect *__cdecl R_CalcLightScissorRectangle(idScreenRect *result, viewLight_s *vLight)
{
  idRenderLightLocal *lightDef; // eax
  float y; // edx
  float v4; // ecx
  float x; // edx
  float v6; // ecx
  float z; // edx
  float v8; // ecx
  float v9; // edx
  float v10; // ecx
  float v11; // edx
  float v12; // ecx
  float v13; // edx
  float v14; // edx
  float v15; // eax
  idScreenRect *v16; // eax
  idScreenRect *v17; // eax
  srfTriangles_s *frustumTris; // esi
  int v19; // edi
  int v20; // ebp
  double x2; // st7
  double x1; // st7
  double y2; // st7
  double y1; // st7
  float windowX; // [esp+8h] [ebp-ACh]
  float windowY; // [esp+Ch] [ebp-A8h]
  float windowYa; // [esp+Ch] [ebp-A8h]
  idScreenRect r; // [esp+14h] [ebp-A0h] BYREF
  idBox box; // [esp+24h] [ebp-90h] BYREF
  idVec3 ndc; // [esp+60h] [ebp-54h] BYREF
  idScreenRect v31; // [esp+6Ch] [ebp-48h] BYREF
  idPlane clip; // [esp+7Ch] [ebp-38h] BYREF
  idBounds bounds; // [esp+8Ch] [ebp-28h] BYREF
  idPlane eye; // [esp+A4h] [ebp-10h] BYREF

  lightDef = vLight->lightDef;
  if ( lightDef->parms.pointLight )
  {
    y = lightDef->parms.origin.y;
    box.center.x = lightDef->parms.origin.x;
    box.center.z = lightDef->parms.origin.z;
    v4 = lightDef->parms.lightRadius.y;
    box.center.y = y;
    x = lightDef->parms.lightRadius.x;
    box.extents.y = v4;
    v6 = lightDef->parms.axis.mat[0].x;
    box.extents.x = x;
    z = lightDef->parms.lightRadius.z;
    box.axis.mat[0].x = v6;
    v8 = lightDef->parms.axis.mat[0].z;
    box.extents.z = z;
    v9 = lightDef->parms.axis.mat[0].y;
    box.axis.mat[0].z = v8;
    v10 = lightDef->parms.axis.mat[1].y;
    box.axis.mat[0].y = v9;
    v11 = lightDef->parms.axis.mat[1].x;
    box.axis.mat[1].y = v10;
    v12 = lightDef->parms.axis.mat[2].x;
    box.axis.mat[1].x = v11;
    v13 = lightDef->parms.axis.mat[1].z;
    box.axis.mat[2].x = v12;
    box.axis.mat[1].z = v13;
    v14 = lightDef->parms.axis.mat[2].y;
    v15 = lightDef->parms.axis.mat[2].z;
    box.axis.mat[2].y = v14;
    box.axis.mat[2].z = v15;
    idFrustum::ProjectionBounds(&tr.viewDef->viewFrustum, &box, &bounds);
    v16 = R_ScreenRectFromViewFrustumBounds(&v31, &bounds);
LABEL_5:
    *result = *v16;
    return result;
  }
  if ( r_useClippedLightScissors.internalVar->integerValue == 2 )
  {
    v16 = R_ClippedLightScissorRectangle(&v31, vLight);
    goto LABEL_5;
  }
  idScreenRect::Clear(&r);
  frustumTris = vLight->lightDef->frustumTris;
  v19 = 0;
  if ( frustumTris->numVerts <= 0 )
  {
LABEL_19:
    idScreenRect::Expand(&r);
    ++c_unclippedLight;
LABEL_20:
    v17 = result;
    *result = r;
    return v17;
  }
  v20 = 0;
  while ( 1 )
  {
    R_TransformModelToClip(
      &frustumTris->verts[v20].xyz,
      tr.viewDef->worldSpace.modelViewMatrix,
      tr.viewDef->projectionMatrix,
      &eye,
      &clip);
    if ( clip.d <= 1.0 )
      break;
    R_TransformClipToDevice(&clip, tr.viewDef, &ndc);
    windowX = (double)(tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1) * (ndc.x + 1.0) * 0.5;
    windowY = (double)(tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1) * (ndc.y + 1.0) * 0.5;
    x2 = (double)tr.viewDef->scissor.x2;
    if ( windowX <= x2 )
    {
      x1 = (double)tr.viewDef->scissor.x1;
      if ( windowX < x1 )
        windowX = x1;
    }
    else
    {
      windowX = x2;
    }
    y2 = (double)tr.viewDef->scissor.y2;
    if ( windowY <= y2 )
    {
      y1 = (double)tr.viewDef->scissor.y1;
      if ( windowY < y1 )
        windowY = y1;
      idScreenRect::AddPoint(&r, windowX, windowY);
    }
    else
    {
      windowYa = y2;
      idScreenRect::AddPoint(&r, windowX, windowYa);
    }
    ++v19;
    ++v20;
    if ( v19 >= frustumTris->numVerts )
      goto LABEL_19;
  }
  ++c_clippedLight;
  if ( !r_useClippedLightScissors.internalVar->integerValue )
  {
    r.y1 = 0;
    r.x1 = 0;
    r.x2 = tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1 - 1;
    r.y2 = tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1 - 1;
    goto LABEL_20;
  }
  *result = *R_ClippedLightScissorRectangle(&v31, vLight);
  return result;
}

// FUNC: bool __cdecl R_IssueEntityDefCallback(class idRenderEntityLocal *)
bool __cdecl R_IssueEntityDefCallback(idRenderEntityLocal *def)
{
  bool v1; // al
  bool v2; // bl
  idBounds oldBounds; // [esp+Ch] [ebp-18h]

  if ( r_checkBounds.internalVar->integerValue )
    oldBounds = def->referenceBounds;
  def->writeToDemo = 1;
  ++tr.pc.c_entityDefCallbacks;
  if ( tr.viewDef )
    v1 = def->parms.callback(&def->parms, (const renderView_s *)tr.viewDef);
  else
    v1 = def->parms.callback(&def->parms, 0);
  v2 = v1;
  if ( !def->parms.hModel )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_IssueEntityDefCallback: dynamic entity callback didn't set model");
  if ( r_checkBounds.internalVar->integerValue
    && (def->referenceBounds.b[0].x + 1.0 < oldBounds.b[0].x
     || def->referenceBounds.b[0].y + 1.0 < oldBounds.b[0].y
     || def->referenceBounds.b[0].z + 1.0 < oldBounds.b[0].z
     || def->referenceBounds.b[1].x - 1.0 > oldBounds.b[1].x
     || def->referenceBounds.b[1].y - 1.0 > oldBounds.b[1].y
     || def->referenceBounds.b[1].z - 1.0 > oldBounds.b[1].z) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "entity %i callback extended reference bounds\n",
      def->index);
  }
  return v2;
}

// FUNC: class idRenderModel * __cdecl R_EntityDefDynamicModel(class idRenderEntityLocal *,bool)
idRenderModel *__cdecl R_EntityDefDynamicModel(idRenderEntityLocal *def, bool collisionOnly)
{
  bool v2; // bl
  idRenderModel *hModel; // edi
  idRenderModel *v5; // eax
  idRenderModel *v6; // eax
  viewEntity_s *viewEntity; // ecx
  idRenderModelOverlay *overlay; // ecx
  idRenderModel *cachedDynamicModel; // eax
  double v10; // st7
  idVec3 ndc; // [esp+1Ch] [ebp-34h] BYREF
  idPlane clip; // [esp+28h] [ebp-28h] BYREF
  idPlane eye; // [esp+38h] [ebp-18h] BYREF
  float v14; // [esp+48h] [ebp-8h]
  float v15; // [esp+4Ch] [ebp-4h]

  if ( def->parms.callback )
    v2 = R_IssueEntityDefCallback(def);
  else
    v2 = 0;
  hModel = def->parms.hModel;
  if ( !hModel )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_EntityDefDynamicModel: NULL model");
  if ( hModel->IsDynamicModel(hModel) )
  {
    if ( v2 || hModel->IsDynamicModel(hModel) == DM_CONTINUOUS && def->dynamicModelFrameCount != tr.frameCount )
      R_ClearEntityDefDynamicModel(def);
    if ( collisionOnly && hModel->HasCollisionSurface(hModel, &def->parms) )
    {
      if ( !def->dynamicCollisionModel )
      {
        v5 = hModel->InstantiateDynamicModel(hModel, &def->parms, tr.viewDef, def->cachedDynamicCollisionModel, 64u);
        def->cachedDynamicCollisionModel = v5;
        def->dynamicCollisionModel = v5;
      }
      return def->dynamicCollisionModel;
    }
    else
    {
      if ( def->dynamicModel )
        goto LABEL_33;
      v6 = hModel->InstantiateDynamicModel(hModel, &def->parms, tr.viewDef, def->cachedDynamicModel, -65u);
      viewEntity = def->viewEntity;
      def->cachedDynamicModel = v6;
      hModel->SetViewEntity(hModel, viewEntity);
      if ( def->cachedDynamicModel )
      {
        overlay = def->overlay;
        if ( !overlay || r_skipOverlays.internalVar->integerValue )
          idRenderModelOverlay::RemoveOverlaySurfacesFromModel((idRenderModelStatic *)def->cachedDynamicModel);
        else
          idRenderModelOverlay::AddOverlaySurfacesToModel(overlay, (idRenderModelStatic *)def->cachedDynamicModel);
        if ( r_checkBounds.internalVar->integerValue )
        {
          def->cachedDynamicModel->Bounds(def->cachedDynamicModel, (idBounds *)&eye, 0);
          if ( def->referenceBounds.b[0].x - 1.0 > eye.a
            || def->referenceBounds.b[0].y - 1.0 > eye.b
            || def->referenceBounds.b[0].z - 1.0 > eye.c
            || def->referenceBounds.b[1].x + 1.0 < eye.d
            || def->referenceBounds.b[1].y + 1.0 < v14
            || def->referenceBounds.b[1].z + 1.0 < v15 )
          {
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "entity %i dynamic model exceeded reference bounds\n",
              def->index);
          }
        }
      }
      cachedDynamicModel = def->cachedDynamicModel;
      def->dynamicModel = cachedDynamicModel;
      def->dynamicModelFrameCount = tr.frameCount;
      if ( cachedDynamicModel )
      {
LABEL_33:
        if ( 0.0 != ((double (__thiscall *)(idRenderModel *))hModel->DepthHack)(hModel) && tr.viewDef )
        {
          R_TransformModelToClip(
            &def->parms.origin,
            tr.viewDef->worldSpace.modelViewMatrix,
            tr.viewDef->projectionMatrix,
            &eye,
            &clip);
          R_TransformClipToDevice(&clip, tr.viewDef, &ndc);
          v10 = ((double (__thiscall *)(idRenderModel *))hModel->DepthHack)(hModel);
          def->parms.modelDepthHack = v10 * (1.0 - ndc.z);
        }
      }
      return def->dynamicModel;
    }
  }
  else
  {
    def->dynamicModel = 0;
    def->dynamicModelFrameCount = 0;
    def->dynamicCollisionModel = 0;
    return hModel;
  }
}

// FUNC: class idRenderModel * __cdecl R_EffectDefDynamicModel(class rvRenderEffectLocal *)
idRenderModel *__cdecl R_EffectDefDynamicModel(rvRenderEffectLocal *def)
{
  rvBSEManager_vtbl *v1; // ebx
  int v2; // eax
  idRenderModel *dynamicModel; // ecx
  idRenderModel *v5; // ecx
  double v6; // st7
  idVec3 ndc; // [esp+Ch] [ebp-2Ch] BYREF
  idPlane clip; // [esp+18h] [ebp-20h] BYREF
  idPlane eye; // [esp+28h] [ebp-10h] BYREF

  if ( !tr.viewDef || !def->effect )
    return 0;
  v1 = bse->__vftable;
  v2 = ((int (__thiscall *)(idDeclBase *, _DWORD))def->parms.declEffect->base->GetName)(def->parms.declEffect->base, 0);
  if ( ((unsigned __int8 (__thiscall *)(rvBSEManager *, int))v1->Filtered)(bse, v2) )
    return 0;
  if ( def->dynamicModelFrameCount != tr.frameCount )
  {
    dynamicModel = def->dynamicModel;
    if ( dynamicModel )
      ((void (__thiscall *)(idRenderModel *, int))dynamicModel->~idRenderModel)(dynamicModel, 1);
    def->dynamicModel = rvBSE::Render(def->effect, &def->parms, tr.viewDef);
    def->dynamicModelFrameCount = tr.frameCount;
  }
  v5 = def->dynamicModel;
  if ( v5 && 0.0 != ((double (__thiscall *)(idRenderModel *))v5->DepthHack)(v5) )
  {
    if ( tr.viewDef )
    {
      R_TransformModelToClip(
        &def->parms.origin,
        tr.viewDef->worldSpace.modelViewMatrix,
        tr.viewDef->projectionMatrix,
        &eye,
        &clip);
      R_TransformClipToDevice(&clip, tr.viewDef, &ndc);
      v6 = ((double (__thiscall *)(idRenderModel *))def->dynamicModel->DepthHack)(def->dynamicModel);
      def->parms.modelDepthHack = v6 * (1.0 - ndc.z);
    }
  }
  return def->dynamicModel;
}

// FUNC: R_AddAmbientDrawsurfs
void __cdecl R_AddAmbientDrawsurfs(viewEntity_s *vEntity)
{
  viewEntity_s *v1; // edi
  idRenderEntityLocal *entityDef; // ebx
  idRenderModel *dynamicModel; // eax
  idRenderModel *v4; // esi
  idRenderModel_vtbl *v5; // edx
  int v6; // ebp
  const modelSurface_s *v7; // edi
  int integerValue; // eax
  int v9; // esi
  int v10; // eax
  bool v11; // zf
  srfTriangles_s *geometry; // esi
  const idMaterial *v13; // ebp
  bool v14; // cc
  int v15; // edi
  float *p_x; // ecx
  float *p_referenceBounds; // edx
  idDeclBase *base; // ecx
  idRenderModel *hModel; // ebx
  int v20; // ebp
  int v21; // eax
  idDeclBase *v22; // ecx
  idRenderModel *v23; // ebx
  int v24; // ebp
  int v25; // eax
  idDeclBase *v26; // ecx
  int v27; // edi
  int v28; // eax
  const idMaterial *overlayShader; // eax
  idRenderModelDecal *k; // ebx
  int v31; // [esp-8h] [ebp-38h]
  int v32; // [esp-8h] [ebp-38h]
  const idMaterial *shader; // [esp+10h] [ebp-20h] BYREF
  idRenderModel *model; // [esp+14h] [ebp-1Ch]
  unsigned int v35; // [esp+18h] [ebp-18h]
  idRenderEntityLocal *def; // [esp+1Ch] [ebp-14h]
  int j; // [esp+20h] [ebp-10h]
  int i; // [esp+24h] [ebp-Ch]
  const modelSurface_s *surf; // [esp+28h] [ebp-8h]
  int total; // [esp+2Ch] [ebp-4h]

  v1 = vEntity;
  entityDef = vEntity->entityDef;
  dynamicModel = entityDef->dynamicModel;
  def = entityDef;
  if ( !dynamicModel )
    dynamicModel = entityDef->parms.hModel;
  v4 = dynamicModel;
  v5 = dynamicModel->__vftable;
  model = dynamicModel;
  v6 = 0;
  total = v5->NumSurfaces(dynamicModel);
  i = 0;
  if ( total > 0 )
  {
    while ( 1 )
    {
      v7 = v4->Surface(v4, v6);
      integerValue = r_singleSurface.internalVar->integerValue;
      surf = v7;
      if ( integerValue < 0 || v6 == integerValue )
      {
        if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 0x2000) )
        {
          v9 = **(_DWORD **)common.ip;
          v10 = (int)v7->shader->base->GetName(v7->shader->base);
          v11 = (*(unsigned __int8 (__thiscall **)(_DWORD, int))(v9 + 96))(*(_DWORD *)common.ip, v10) == 0;
        }
        else
        {
          v11 = ((1 << v7->id) & entityDef->parms.suppressSurfaceMask) == 0;
        }
        if ( v11 )
        {
          geometry = v7->geometry;
          if ( geometry )
          {
            if ( geometry->numIndexes )
            {
              shader = v7->shader;
              shader = R_RemapShaderBySkin(shader, entityDef->parms.customSkin, entityDef->parms.customShader);
              R_GlobalShaderOverride(&shader);
              v13 = shader;
              if ( shader )
              {
                if ( shader->numStages > 0 || shader->entityGui || shader->gui )
                {
                  if ( r_checkBounds.internalVar->integerValue )
                  {
                    v14 = geometry->numVerts <= 0;
                    j = 0;
                    if ( !v14 )
                    {
                      v35 = 0;
                      do
                      {
                        v15 = 0;
                        p_x = &geometry->verts[v35 / 0x40].xyz.x;
                        p_referenceBounds = (float *)&entityDef->referenceBounds;
                        while ( *(&geometry->bounds.b[1].x + v15) + 1.0 >= *p_x
                             && *(&geometry->bounds.b[0].x + v15) - 1.0 <= *p_x )
                        {
                          if ( p_referenceBounds[3] + 1.0 < *p_x || *p_referenceBounds - 1.0 > *p_x )
                          {
                            base = v13->base;
                            hModel = entityDef->parms.hModel;
                            v20 = *(_DWORD *)common.type;
                            v21 = (int)base->GetName(base);
                            v31 = ((int (__thiscall *)(idRenderModel *, int))hModel->Name)(hModel, v21);
                            (*(void (__cdecl **)(netadrtype_t, const char *, int))(v20 + 124))(
                              common.type,
                              "bad referenceBounds on %s:%s\n",
                              v31);
                            goto LABEL_30;
                          }
                          ++v15;
                          ++p_x;
                          ++p_referenceBounds;
                          if ( v15 >= 3 )
                            goto LABEL_31;
                        }
                        v22 = v13->base;
                        v23 = entityDef->parms.hModel;
                        v24 = *(_DWORD *)common.type;
                        v25 = (int)v22->GetName(v22);
                        v32 = ((int (__thiscall *)(idRenderModel *, int))v23->Name)(v23, v25);
                        (*(void (__cdecl **)(netadrtype_t, const char *, int))(v24 + 124))(
                          common.type,
                          "bad tri->bounds on %s:%s\n",
                          v32);
LABEL_30:
                        v13 = shader;
                        entityDef = def;
LABEL_31:
                        if ( v15 != 3 )
                          break;
                        v35 += 64;
                        v14 = ++j < geometry->numVerts;
                      }
                      while ( v14 );
                      v7 = surf;
                    }
                  }
                  if ( !R_CullLocalBox(&geometry->bounds, vEntity->modelMatrix, 5, tr.viewDef->frustum) )
                  {
                    entityDef->visibleCount = tr.viewCount;
                    if ( !geometry->primBatchMesh )
                    {
                      if ( !R_CreateAmbientCache(geometry, shader->numAmbientStages != shader->numStages) )
                        return;
                      idVertexCache::Touch(&vertexCache, geometry->ambientCache);
                      if ( r_useIndexBuffers.internalVar->integerValue && !geometry->indexCache )
                        idVertexCache::Alloc(
                          &vertexCache,
                          geometry->indexes,
                          4 * geometry->numIndexes,
                          &geometry->indexCache,
                          1u);
                      if ( geometry->indexCache )
                        idVertexCache::Touch(&vertexCache, geometry->indexCache);
                    }
                    if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(
                           *(_DWORD *)common.ip,
                           0x2000) )
                    {
                      v26 = v7->shader->base;
                      v27 = **(_DWORD **)common.ip;
                      v28 = (int)v26->GetName(v26);
                      geometry->modviewSelected = (*(int (__thiscall **)(_DWORD, int))(v27 + 92))(
                                                    *(_DWORD *)common.ip,
                                                    v28);
                    }
                    R_AddDrawSurf(geometry, vEntity, &vEntity->entityDef->parms, shader, &vEntity->scissorRect, 0);
                    geometry->ambientViewCount = tr.viewCount;
                    overlayShader = entityDef->parms.overlayShader;
                    if ( overlayShader && !shader->entityGui )
                    {
                      R_AddDrawSurf(
                        geometry,
                        vEntity,
                        &vEntity->entityDef->parms,
                        overlayShader,
                        &vEntity->scissorRect,
                        0);
                      geometry->ambientViewCount = tr.viewCount;
                    }
                  }
                }
              }
            }
          }
        }
      }
      v6 = ++i;
      if ( i >= total )
        break;
      v4 = model;
    }
    v1 = vEntity;
  }
  for ( k = entityDef->decals; k; k = k->nextDecal )
    idRenderModelDecal::AddDecalDrawSurf(k, v1);
}

// FUNC: R_AddAmbientEffectDrawsurfs
void __usercall R_AddAmbientEffectDrawsurfs(viewEffect_s *vEffect@<ebx>)
{
  idRenderModel *dynamicModel; // ebp
  int v2; // eax
  int v3; // edi
  srfTriangles_s *v4; // esi
  _DWORD *v5; // eax
  int i; // [esp+4h] [ebp-Ch]
  rvRenderEffectLocal *def; // [esp+8h] [ebp-8h]
  int total; // [esp+Ch] [ebp-4h]

  dynamicModel = vEffect->effectDef->dynamicModel;
  def = vEffect->effectDef;
  total = dynamicModel->NumSurfaces(dynamicModel);
  for ( i = 0; i < total; ++i )
  {
    v2 = (int)dynamicModel->Surface(dynamicModel, i);
    v3 = v2;
    v4 = *(srfTriangles_s **)(v2 + 8);
    if ( v4 )
    {
      if ( v4->numIndexes )
      {
        v5 = *(_DWORD **)(v2 + 4);
        if ( v5 )
        {
          if ( ((int)v5[66] > 0 || v5[19] || v5[20])
            && !R_CullLocalBox(&v4->bounds, vEffect->modelMatrix, 5, tr.viewDef->frustum) )
          {
            def->visibleCount = tr.viewCount;
            if ( !v4->primBatchMesh )
            {
              if ( !R_CreateAmbientCache(v4, 0) )
                return;
              idVertexCache::Touch(&vertexCache, v4->ambientCache);
              if ( r_useIndexBuffers.internalVar->integerValue && !v4->indexCache )
                idVertexCache::Alloc(&vertexCache, v4->indexes, 4 * v4->numIndexes, &v4->indexCache, 1u);
              if ( v4->indexCache )
                idVertexCache::Touch(&vertexCache, v4->indexCache);
            }
            R_AddDrawSurf(
              v4,
              vEffect,
              &vEffect->effectDef->parms,
              *(const idMaterial **)(v3 + 4),
              &vEffect->scissorRect,
              0);
            v4->ambientViewCount = tr.viewCount;
          }
        }
      }
    }
  }
}

// FUNC: bool __cdecl R_CalcEntityScissorRectangle(struct viewEntity_s *,class idScreenRect &)
char __cdecl R_CalcEntityScissorRectangle(viewEntity_s *vEntity, idScreenRect *rect)
{
  idRenderEntityLocal *entityDef; // eax
  double v3; // st7
  double v4; // st6
  double v5; // rt0
  double v6; // st6
  double v7; // st5
  double v8; // st4
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st7
  idBounds bounds; // [esp+0h] [ebp-64h] BYREF
  idScreenRect result; // [esp+18h] [ebp-4Ch] BYREF
  idBox box; // [esp+28h] [ebp-3Ch] BYREF

  entityDef = vEntity->entityDef;
  v3 = entityDef->referenceBounds.b[1].x + entityDef->referenceBounds.b[0].x;
  v4 = entityDef->referenceBounds.b[1].y + entityDef->referenceBounds.b[0].y;
  result.zmin = entityDef->referenceBounds.b[1].z + entityDef->referenceBounds.b[0].z;
  v5 = v4;
  bounds.b[0].x = v3 * 0.5;
  box.center.x = bounds.b[0].x;
  v6 = result.zmin * 0.5;
  box.center.y = v5 * 0.5;
  box.center.z = v6;
  v7 = entityDef->referenceBounds.b[1].x - bounds.b[0].x;
  v8 = entityDef->referenceBounds.b[1].y - v5 * 0.5;
  result.zmin = entityDef->referenceBounds.b[1].z - v6;
  box.extents.z = result.zmin;
  box.extents.x = v7;
  box.extents.y = v8;
  *(float *)&result.x1 = v6 * entityDef->parms.axis.mat[2].x
                       + v5 * 0.5 * entityDef->parms.axis.mat[1].x
                       + bounds.b[0].x * entityDef->parms.axis.mat[0].x;
  *(float *)&result.x2 = v6 * entityDef->parms.axis.mat[2].y
                       + v5 * 0.5 * entityDef->parms.axis.mat[1].y
                       + bounds.b[0].x * entityDef->parms.axis.mat[0].y;
  v9 = v6 * entityDef->parms.axis.mat[2].z
     + v5 * 0.5 * entityDef->parms.axis.mat[1].z
     + bounds.b[0].x * entityDef->parms.axis.mat[0].z;
  v10 = *(float *)&result.x1 + entityDef->parms.origin.x;
  v11 = v9;
  v12 = *(float *)&result.x2 + entityDef->parms.origin.y;
  result.zmin = v11 + entityDef->parms.origin.z;
  box.center.z = result.zmin;
  box.center.x = v10;
  box.center.y = v12;
  box.axis = entityDef->parms.axis;
  if ( !idFrustum::ProjectionBounds(&tr.viewDef->viewFrustum, &box, &bounds)
    || bounds.b[0].y >= (double)bounds.b[1].y
    || bounds.b[0].z >= (double)bounds.b[1].z )
  {
    return 0;
  }
  *rect = *R_ScreenRectFromViewFrustumBounds(&result, &bounds);
  return 1;
}

// FUNC: void __cdecl R_AddEffectSurfaces(void)
void __cdecl R_AddEffectSurfaces()
{
  unsigned int v0; // eax
  viewEffect_s **v1; // esi
  unsigned int v2; // edi
  viewEffect_s *v3; // ebx
  idScreenRect *p_scissorRect; // ecx
  idRenderModel *v5; // eax
  viewEffect_s **array; // [esp+4h] [ebp-4h] BYREF

  v0 = R_SortViewEffects(&array);
  v1 = array;
  if ( v0 )
  {
    v2 = v0;
    do
    {
      v3 = *v1;
      p_scissorRect = &(*v1++)->scissorRect;
      if ( idScreenRect::IsEmpty(p_scissorRect) )
      {
        ++tr.pc.c_culledViewEffects;
      }
      else
      {
        v5 = R_EffectDefDynamicModel(v3->effectDef);
        if ( v5 )
        {
          if ( v5->NumSurfaces(v5) > 0 )
          {
            R_AddAmbientEffectDrawsurfs(v3);
            ++tr.pc.c_visibleViewEffects;
          }
        }
      }
      --v2;
    }
    while ( v2 );
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::CreateLightDefInteractions(class idRenderLightLocal *)const
void __thiscall idRenderWorldLocal::CreateLightDefInteractions(idRenderWorldLocal *this, idRenderLightLocal *ldef)
{
  portalArea_s *area; // eax
  areaReference_s *areaNext; // ebp
  areaReference_s *i; // ebx
  idRenderEntityLocal *entity; // esi
  const idMaterial *lightShader; // eax
  int materialFlags; // ecx
  int suppressShadowInViewID; // eax
  int suppressShadowInLightID; // eax
  idInteraction *firstInteraction; // eax
  float *v12; // eax
  float modelMatrix[16]; // [esp+4h] [ebp-40h] BYREF
  areaReference_s *ldefa; // [esp+48h] [ebp+4h]

  for ( ldefa = ldef->references; ldefa; ldefa = ldefa->ownerNext )
  {
    area = ldefa->area;
    areaNext = area->entityRefs.areaNext;
    for ( i = &area->entityRefs; areaNext != i; areaNext = areaNext->areaNext )
    {
      entity = areaNext->entity;
      if ( tr.viewDef && entity->viewCount != tr.viewCount )
      {
        lightShader = ldef->lightShader;
        materialFlags = lightShader->materialFlags;
        if ( (materialFlags & 8) == 0
          && (lightShader->fogLight || lightShader->ambientLight || lightShader->blendLight || (materialFlags & 4) != 0) )
        {
          continue;
        }
        if ( !r_skipSuppress.internalVar->integerValue
          && ((suppressShadowInViewID = entity->parms.suppressShadowInViewID) != 0
           && suppressShadowInViewID == tr.viewDef->renderView.viewID
           || (suppressShadowInLightID = entity->parms.suppressShadowInLightID) != 0
           && suppressShadowInLightID == ldef->parms.lightId) )
        {
          continue;
        }
      }
      if ( !entity->parms.noDynamicInteractions || !entity->world->generateAllInteractionsCalled )
      {
        firstInteraction = entity->firstInteraction;
        if ( firstInteraction )
        {
          while ( firstInteraction->lightDef != ldef )
          {
            firstInteraction = firstInteraction->entityNext;
            if ( !firstInteraction )
              goto LABEL_20;
          }
          if ( firstInteraction->numSurfaces )
            R_SetEntityDefViewEntity(areaNext->entity);
        }
        else
        {
LABEL_20:
          if ( entity->viewCount == tr.viewCount )
          {
            v12 = entity->viewEntity->modelMatrix;
          }
          else
          {
            R_AxisToModelMatrix(&entity->parms.axis, &entity->parms.origin, modelMatrix);
            v12 = modelMatrix;
          }
          if ( !R_CullLocalBox(&entity->referenceBounds, v12, 6, ldef->frustum) )
          {
            idInteraction::AllocAndLink(entity, ldef);
            R_SetEntityDefViewEntity(entity);
          }
        }
      }
    }
  }
}

// FUNC: void __cdecl R_AddLightSurfaces(void)
void __usercall R_AddLightSurfaces(int a1@<edi>)
{
  viewLight_s **p_viewLights; // esi
  viewLight_s *v2; // edi
  idRenderLightLocal *lightDef; // ebp
  idMaterial *lightShader; // ebx
  int suppressLightInViewID; // eax
  int allowLightInViewID; // eax
  float *v7; // esi
  int v8; // edi
  shaderStage_t *v9; // ecx
  float *v10; // edx
  int v11; // edx
  double v12; // st7
  float *v13; // edx
  float *v14; // edx
  idVec3 *p_globalLightOrigin; // esi
  int v16; // edi
  srfTriangles_s *frustumTris; // eax
  idRenderModel *prelightModel; // ecx
  int v19; // esi
  int v20; // eax
  const srfTriangles_s *v21; // esi
  int v22; // ebx
  int v23; // eax
  vertCache_s *shadowCache; // eax
  vertCache_s **p_shadowCache; // edi
  shadowCache_s *shadowVertexes; // eax
  vertCache_s *indexCache; // edi
  viewLight_s **ptr; // [esp+4h] [ebp-30h]
  viewLight_s *vLight; // [esp+8h] [ebp-2Ch]
  int v31; // [esp+Ch] [ebp-28h]
  float floatValue; // [esp+10h] [ebp-24h]
  idScreenRect scissorRect; // [esp+14h] [ebp-20h] BYREF
  idScreenRect result; // [esp+24h] [ebp-10h] BYREF

  p_viewLights = &tr.viewDef->viewLights;
  ptr = &tr.viewDef->viewLights;
  if ( tr.viewDef->viewLights )
  {
    while ( 1 )
    {
      v2 = *p_viewLights;
      lightDef = (*p_viewLights)->lightDef;
      lightShader = (idMaterial *)lightDef->lightShader;
      vLight = *p_viewLights;
      if ( !lightShader )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "R_AddLightSurfaces: NULL lightShader");
      if ( r_skipSuppress.internalVar->integerValue )
        break;
      suppressLightInViewID = lightDef->parms.suppressLightInViewID;
      if ( suppressLightInViewID && suppressLightInViewID == tr.viewDef->renderView.viewID )
      {
        *p_viewLights = v2->next;
        lightDef->viewCount = -1;
      }
      else
      {
        allowLightInViewID = lightDef->parms.allowLightInViewID;
        if ( !allowLightInViewID || allowLightInViewID == tr.viewDef->renderView.viewID )
          break;
        *p_viewLights = v2->next;
        lightDef->viewCount = -1;
      }
LABEL_62:
      if ( !*p_viewLights )
        return;
    }
    v7 = (float *)R_FrameAlloc(4 * lightShader->numRegisters);
    v2->shaderRegisters = v7;
    idMaterial::EvaluateRegisters(
      lightShader,
      v7,
      lightDef->parms.shaderParms,
      tr.viewDef,
      lightDef->parms.referenceSoundHandle,
      0);
    if ( !lightShader->fogLight && !lightShader->blendLight )
    {
      v8 = 0;
      if ( lightShader->numStages > 0 )
      {
        v31 = 0;
        do
        {
          v9 = &lightShader->stages[v31];
          if ( v7[v9->conditionRegister] != 0.0 )
          {
            v10 = &v7[v9->color.registers[0]];
            if ( *v10 < 0.001 )
              *v10 = 0.0;
            v11 = v9->color.registers[1];
            v12 = v7[v11];
            v13 = &v7[v11];
            if ( v12 < 0.001 )
              *v13 = 0.0;
            v14 = &v7[v9->color.registers[2]];
            if ( *v14 < 0.001 )
              *v14 = 0.0;
            if ( v7[v9->color.registers[0]] > 0.0
              || v7[v9->color.registers[1]] > 0.0
              || v7[v9->color.registers[2]] > 0.0 )
            {
              break;
            }
          }
          ++v31;
          ++v8;
        }
        while ( v8 < lightShader->numStages );
      }
      if ( v8 == lightShader->numStages )
      {
        *ptr = vLight->next;
        lightDef->viewCount = -1;
        goto LABEL_61;
      }
      v2 = vLight;
    }
    if ( r_useLightScissors.internalVar->integerValue )
    {
      scissorRect = *R_CalcLightScissorRectangle(&result, v2);
      idScreenRect::Intersect(&v2->scissorRect, &scissorRect);
      if ( r_showLightScissors.internalVar->integerValue )
        R_ShowColoredScreenRect(&v2->scissorRect, lightDef->index);
    }
    ptr = &v2->next;
    if ( r_lightSourceRadius.internalVar->floatValue != 0.0 )
    {
      p_globalLightOrigin = &lightDef->globalLightOrigin;
      v16 = 3;
      do
      {
        floatValue = r_lightSourceRadius.internalVar->floatValue;
        p_globalLightOrigin = (idVec3 *)((char *)p_globalLightOrigin + 4);
        --v16;
        p_globalLightOrigin[-1].z = ((double)(2 * (rand() & 0xFFF)) * 0.00024420026 - 1.0) * floatValue
                                  + p_globalLightOrigin[-1].z;
      }
      while ( v16 );
      v2 = vLight;
    }
    idRenderWorldLocal::CreateLightDefInteractions(tr.viewDef->renderWorld, lightDef);
    ++tr.pc.c_viewLights;
    if ( lightShader->fogLight )
    {
      frustumTris = lightDef->frustumTris;
      if ( !frustumTris->ambientCache && !R_CreateAmbientCache(frustumTris, 0) )
        goto LABEL_61;
      idVertexCache::Touch(&vertexCache, lightDef->frustumTris->ambientCache);
    }
    prelightModel = lightDef->parms.prelightModel;
    if ( !prelightModel || !r_useOptimizedShadows.internalVar->integerValue )
      goto LABEL_61;
    if ( !((int (__thiscall *)(idRenderModel *, int))prelightModel->NumSurfaces)(prelightModel, a1) )
    {
      v19 = *(_DWORD *)common.type;
      v20 = (int)lightDef->parms.prelightModel->Name(lightDef->parms.prelightModel);
      (*(void (**)(netadrtype_t, const char *, ...))(v19 + 152))(common.type, "no surfs in prelight model '%s'", v20);
    }
    a1 = 0;
    v21 = *(const srfTriangles_s **)(((int (__thiscall *)(idRenderModel *))lightDef->parms.prelightModel->Surface)(lightDef->parms.prelightModel)
                                   + 8);
    if ( !v21->shadowVertexes && !v21->primBatchMesh )
    {
      v22 = *(_DWORD *)common.type;
      v23 = (int)lightDef->parms.prelightModel->Name(lightDef->parms.prelightModel);
      (*(void (**)(netadrtype_t, const char *, ...))(v22 + 152))(
        common.type,
        "R_AddLightSurfaces: prelight model '%s' without shadowVertexes",
        v23);
    }
    if ( r_useShadowCulling.internalVar->integerValue
      && R_CullLocalBox(&v21->bounds, tr.viewDef->worldSpace.modelMatrix, 5, tr.viewDef->frustum) )
    {
      goto LABEL_61;
    }
    if ( !v21->primBatchMesh )
    {
      shadowCache = v21->shadowCache;
      p_shadowCache = &v21->shadowCache;
      if ( !shadowCache )
      {
        shadowVertexes = v21->shadowVertexes;
        if ( shadowVertexes )
          idVertexCache::Alloc(&vertexCache, shadowVertexes, 16 * v21->numVerts, &v21->shadowCache, 0);
        shadowCache = *p_shadowCache;
        if ( !*p_shadowCache )
          goto LABEL_61;
      }
      idVertexCache::Touch(&vertexCache, shadowCache);
      if ( !v21->indexCache && r_useIndexBuffers.internalVar->integerValue )
        idVertexCache::Alloc(&vertexCache, v21->indexes, 4 * v21->numIndexes, &v21->indexCache, 1);
      indexCache = v21->indexCache;
      if ( indexCache )
        idVertexCache::Touch(&vertexCache, indexCache);
      v2 = vLight;
    }
    R_LinkLightSurf(&v2->globalShadows, v21, 0, lightDef, 0, &v2->scissorRect, 1);
LABEL_61:
    p_viewLights = ptr;
    goto LABEL_62;
  }
}

// FUNC: void __cdecl R_AddModelSurfaces(void)
void __cdecl R_AddModelSurfaces()
{
  unsigned int v0; // eax
  int v1; // eax
  viewEntity_s *v2; // ebp
  idScreenRect *p_scissorRect; // esi
  int v4; // edi
  int v5; // ebx
  float zmin; // ecx
  float zmax; // edx
  int v8; // eax
  float v9; // eax
  float v10; // ecx
  idRenderModel *v11; // eax
  idInteraction **v12; // esi
  int v13; // edi
  int size; // ebx
  idInteraction *firstInteraction; // ebp
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  idInteraction **v19; // ebp
  idInteraction **v20; // eax
  int v21; // ecx
  int v22; // edx
  idInteraction *v23; // eax
  int i; // ebp
  idInteraction *v25; // ecx
  bool useEntityScissors; // [esp+1h] [ebp-57h]
  bool showEntityScissors; // [esp+2h] [ebp-56h]
  bool lodEntities; // [esp+3h] [ebp-55h]
  float inter; // [esp+4h] [ebp-54h]
  idInteraction *intera; // [esp+4h] [ebp-54h]
  int count; // [esp+8h] [ebp-50h]
  viewEntity_s **array; // [esp+Ch] [ebp-4Ch] BYREF
  float sizeX; // [esp+10h] [ebp-48h]
  float lodEntitiesPercent; // [esp+14h] [ebp-44h]
  idInteraction *next; // [esp+18h] [ebp-40h]
  idList<idInteraction *> list; // [esp+1Ch] [ebp-3Ch]
  idScreenRect prevRect; // [esp+2Ch] [ebp-2Ch]
  idScreenRect scissorRect; // [esp+3Ch] [ebp-1Ch] BYREF
  int v39; // [esp+54h] [ebp-4h]

  v0 = R_SortViewEntities(&array);
  tr.viewDef->numDrawSurfs = 0;
  tr.viewDef->maxDrawSurfs = 0;
  useEntityScissors = r_useEntityScissors.internalVar->integerValue != 0;
  showEntityScissors = r_showEntityScissors.internalVar->integerValue != 0;
  lodEntities = r_lod_entities.internalVar->integerValue != 0;
  v1 = v0 - 1;
  lodEntitiesPercent = r_lod_entities_percent.internalVar->floatValue;
  count = v1;
  if ( v1 >= 0 )
  {
    while ( 1 )
    {
      v2 = array[v1];
      p_scissorRect = &v2->scissorRect;
      v4 = *(_DWORD *)&v2->scissorRect.x1;
      v5 = *(_DWORD *)&v2->scissorRect.x2;
      zmin = v2->scissorRect.zmin;
      next = (idInteraction *)v2->entityDef;
      zmax = v2->scissorRect.zmax;
      prevRect.zmin = zmin;
      prevRect.zmax = zmax;
      if ( useEntityScissors )
      {
        if ( R_CalcEntityScissorRectangle(v2, &scissorRect) )
          idScreenRect::Intersect(&v2->scissorRect, &scissorRect);
        else
          idScreenRect::Clear(&v2->scissorRect);
        if ( showEntityScissors )
          R_ShowColoredScreenRect(&v2->scissorRect, v2->entityDef->index);
      }
      v8 = v2->scissorRect.y2 - v2->scissorRect.y1;
      sizeX = (float)(v2->scissorRect.x2 - p_scissorRect->x1);
      inter = (float)v8;
      if ( idScreenRect::IsEmpty(&v2->scissorRect) )
        v2->screenCoverage = 0.0;
      else
        v2->screenCoverage = (inter / (double)glConfig.vidHeight + sizeX / (double)glConfig.vidWidth) * 0.5;
      if ( lodEntities && v2->screenCoverage > -0.000099999997 && v2->screenCoverage < (double)lodEntitiesPercent )
        idScreenRect::Clear(&v2->scissorRect);
      if ( useEntityScissors )
      {
        v9 = prevRect.zmin;
        v10 = prevRect.zmax;
        *(_DWORD *)&p_scissorRect->x1 = v4;
        *(_DWORD *)&v2->scissorRect.x2 = v5;
        v2->scissorRect.zmin = v9;
        v2->scissorRect.zmax = v10;
      }
      if ( idScreenRect::IsEmpty(&v2->scissorRect) )
      {
        ++tr.pc.c_shadowViewEntities;
      }
      else
      {
        v11 = R_EntityDefDynamicModel((idRenderEntityLocal *)next, 0);
        if ( !v11 || v11->NumSurfaces(v11) <= 0 )
          goto endLoop;
        R_AddAmbientDrawsurfs(v2);
        ++tr.pc.c_visibleViewEntities;
      }
      v12 = 0;
      v13 = 0;
      size = 0;
      list.granularity = 16;
      list.list = 0;
      list.num = 0;
      list.size = 0;
      firstInteraction = v2->entityDef->firstInteraction;
      v39 = 0;
      intera = firstInteraction;
      if ( firstInteraction )
      {
        while ( firstInteraction->numSurfaces )
        {
          next = firstInteraction->entityNext;
          if ( !v12 && size != 16 )
          {
            size = 16;
            list.size = 16;
            if ( v13 > 16 )
            {
              v13 = 16;
              list.num = 16;
            }
            v12 = (idInteraction **)Memory::Allocate(0x40u);
            v16 = 0;
            for ( list.list = v12; v16 < v13; ++v16 )
              v12[v16] = *(idInteraction **)(4 * v16);
          }
          if ( v13 == size )
          {
            v17 = (size + 16) % 16;
            v18 = size + 16 - v17;
            if ( v18 > 0 )
            {
              if ( v18 != size )
              {
                size = size + 16 - v17;
                v19 = v12;
                list.size = v18;
                if ( v18 < v13 )
                {
                  v13 = v18;
                  list.num = v18;
                }
                v20 = (idInteraction **)Memory::Allocate(4 * v18);
                v12 = v20;
                list.list = v20;
                if ( v13 > 0 )
                {
                  v21 = (char *)v19 - (char *)v20;
                  v22 = v13;
                  do
                  {
                    *v20 = *(idInteraction **)((char *)v20 + v21);
                    ++v20;
                    --v22;
                  }
                  while ( v22 );
                  size = list.size;
                }
                if ( v19 )
                  Memory::Free(v19);
                firstInteraction = intera;
              }
            }
            else
            {
              if ( v12 )
                Memory::Free(v12);
              v12 = 0;
              v13 = 0;
              size = 0;
              list.list = 0;
              list.size = 0;
            }
          }
          v23 = next;
          v12[v13++] = firstInteraction;
          list.num = v13;
          intera = v23;
          if ( !v23 )
            break;
          firstInteraction = v23;
        }
      }
      for ( i = 0; i < v13; ++i )
      {
        v25 = v12[i];
        if ( v25->lightDef->viewCount == tr.viewCount )
          idInteraction::AddActiveInteraction(v25);
      }
      v39 = -1;
      if ( v12 )
        Memory::Free(v12);
      list.list = 0;
      list.num = 0;
      list.size = 0;
endLoop:
      if ( --count < 0 )
        return;
      v1 = count;
    }
  }
}

// FUNC: void __cdecl R_RemoveUnecessaryViewLights(void)
void __cdecl R_RemoveUnecessaryViewLights()
{
  viewLight_s *i; // eax
  viewLight_s *j; // edi
  const idMaterial *lightShader; // eax
  const drawSurf_s *k; // esi
  const drawSurf_s *m; // esi
  const drawSurf_s *n; // esi
  const drawSurf_s *ii; // esi
  const drawSurf_s *jj; // esi
  idScreenRect surfRect; // [esp+4h] [ebp-10h] BYREF

  for ( i = tr.viewDef->viewLights; i; i = i->next )
  {
    if ( !i->localInteractions && !i->globalInteractions && !i->translucentInteractions )
    {
      i->localShadows = 0;
      i->globalShadows = 0;
    }
  }
  if ( r_useShadowSurfaceScissor.internalVar->integerValue )
  {
    for ( j = tr.viewDef->viewLights; j; j = j->next )
    {
      lightShader = j->lightShader;
      if ( (lightShader->materialFlags & 8) != 0
        || !lightShader->fogLight
        && !lightShader->ambientLight
        && !lightShader->blendLight
        && (lightShader->materialFlags & 4) == 0 )
      {
        idScreenRect::Clear(&surfRect);
        for ( k = j->globalInteractions; k; k = k->nextOnLight )
          idScreenRect::Union(&surfRect, &k->scissorRect);
        for ( m = j->localShadows; m; m = m->nextOnLight )
          idScreenRect::Intersect(&m->scissorRect, &surfRect);
        for ( n = j->localInteractions; n; n = n->nextOnLight )
          idScreenRect::Union(&surfRect, &n->scissorRect);
        for ( ii = j->globalShadows; ii; ii = ii->nextOnLight )
          idScreenRect::Intersect(&ii->scissorRect, &surfRect);
        for ( jj = j->translucentInteractions; jj; jj = jj->nextOnLight )
          idScreenRect::Union(&surfRect, &jj->scissorRect);
        idScreenRect::Intersect(&j->scissorRect, &surfRect);
      }
    }
  }
}
