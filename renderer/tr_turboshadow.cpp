
// FUNC: struct srfTriangles_s * __cdecl R_CreateVertexBufferTurboShadowVolume(class idRenderEntityLocal const *,struct srfTriangles_s const *,class idRenderLightLocal const *,struct srfCullInfo_s &)
srfTriangles_s *__cdecl R_CreateVertexBufferTurboShadowVolume(
        const idRenderEntityLocal *ent,
        srfTriangles_s *tri,
        const idRenderLightLocal *light,
        srfCullInfo_s *cullInfo)
{
  rvMesh *primBatchMesh; // edi
  int m_numSilTracePrimitives; // esi
  unsigned __int8 *v6; // ebp
  int i; // eax
  srfTriangles_s *result; // eax
  srfTriangles_s *v9; // esi
  int v10; // ebx
  int *v11; // eax
  int SilShadowVolTris; // ebp
  int FrontBackShadowVolTris; // eax
  int v14; // ecx
  int v15; // ecx
  int v16; // eax
  int numIndexes; // eax
  int numShadowingFaces; // [esp+10h] [ebp-10h]
  srfCullInfo_s *numShadowingFacesa; // [esp+10h] [ebp-10h]
  int numShadowingFacesb; // [esp+10h] [ebp-10h]
  unsigned __int8 *facing; // [esp+14h] [ebp-Ch]
  int *indexes; // [esp+18h] [ebp-8h]
  const unsigned __int8 *tria; // [esp+28h] [ebp+8h]
  int *cullInfoa; // [esp+30h] [ebp+10h]
  int *cullInfob; // [esp+30h] [ebp+10h]

  primBatchMesh = tri->primBatchMesh;
  m_numSilTracePrimitives = primBatchMesh->m_numSilTracePrimitives;
  numShadowingFaces = 0;
  R_CalcInteractionFacing(ent, tri, light, cullInfo);
  if ( r_useShadowProjectedCull.internalVar->integerValue )
    R_CalcInteractionCullBits(ent, tri, light, cullInfo);
  v6 = cullInfo->facing;
  facing = cullInfo->facing;
  if ( cullInfo->cullBits == (unsigned __int8 *)-1 || !r_useShadowProjectedCull.internalVar->integerValue )
  {
    for ( i = 0; i < m_numSilTracePrimitives; ++i )
      numShadowingFaces += v6[i];
    numShadowingFacesa = (srfCullInfo_s *)(m_numSilTracePrimitives - numShadowingFaces);
  }
  else
  {
    numShadowingFacesa = rvMesh::FlipOutsideBackFaces(primBatchMesh, cullInfo);
  }
  if ( !numShadowingFacesa )
    return 0;
  v9 = R_AllocStaticTriSurf();
  v9->numVerts = 2 * primBatchMesh->m_numSilTraceVertices;
  v9->primBatchMesh = tri->primBatchMesh;
  v9->skinToModelTransforms = tri->skinToModelTransforms;
  v9->skinToModelTransformsAlloc = 0;
  v9->numSkinToModelTransforms = tri->numSkinToModelTransforms;
  R_AllocStaticTriSurfIndexes(
    v9,
    2 * (primBatchMesh->m_numPrimBatches + 3 * ((_DWORD)numShadowingFacesa + primBatchMesh->m_numSilEdges)));
  v10 = 0;
  indexes = v9->indexes;
  v11 = &indexes[2 * primBatchMesh->m_numPrimBatches];
  v9->numIndexes = 0;
  v9->numShadowIndexesNoCaps = 0;
  cullInfoa = v11;
  tria = v6;
  if ( primBatchMesh->m_numPrimBatches > 0 )
  {
    numShadowingFacesb = 0;
    while ( 1 )
    {
      SilShadowVolTris = rvMesh::CreateSilShadowVolTris(primBatchMesh, v10, cullInfoa, v6);
      cullInfob = &cullInfoa[SilShadowVolTris];
      FrontBackShadowVolTris = rvMesh::CreateFrontBackShadowVolTris(primBatchMesh, v10, cullInfob, tria);
      v14 = numShadowingFacesb;
      numShadowingFacesb += 72;
      cullInfoa = &cullInfob[FrontBackShadowVolTris];
      tria += *(int *)((char *)&primBatchMesh->m_primBatches->m_silTraceGeoSpec.m_primitiveCount + v14);
      v15 = FrontBackShadowVolTris + SilShadowVolTris;
      v16 = 2 * v10;
      indexes[v16] = SilShadowVolTris;
      indexes[v16 + 1] = v15;
      v9->numIndexes += v15;
      v9->numShadowIndexesNoCaps += SilShadowVolTris;
      if ( ++v10 >= primBatchMesh->m_numPrimBatches )
        break;
      v6 = facing;
    }
  }
  numIndexes = v9->numIndexes;
  v9->numShadowIndexesNoFrontCaps = numIndexes;
  v9->shadowCapPlaneBits = 64;
  R_ResizeStaticTriSurfIndexes(v9, numIndexes + 2 * primBatchMesh->m_numPrimBatches);
  v9->bounds.b[0].z = idMath::INFINITY;
  v9->bounds.b[0].y = idMath::INFINITY;
  v9->bounds.b[0].x = idMath::INFINITY;
  v9->bounds.b[1].z = -1.0e30;
  result = v9;
  v9->bounds.b[1].y = -1.0e30;
  v9->bounds.b[1].x = -1.0e30;
  return result;
}

// FUNC: struct srfTriangles_s * __cdecl R_CreateVertexProgramTurboShadowVolume(class idRenderEntityLocal const *,struct srfTriangles_s const *,class idRenderLightLocal const *,struct srfCullInfo_s &)
srfTriangles_s *__cdecl R_CreateVertexProgramTurboShadowVolume(
        const idRenderEntityLocal *ent,
        srfTriangles_s *tri,
        const idRenderLightLocal *light,
        srfCullInfo_s *cullInfo)
{
  int v4; // esi
  int v5; // eax
  int v6; // ebp
  srfTriangles_s *v8; // esi
  int v9; // eax
  int v10; // ecx

  R_CalcInteractionFacing(ent, tri, light, cullInfo);
  if ( r_useShadowProjectedCull.internalVar->integerValue )
    R_CalcInteractionCullBits(ent, tri, light, cullInfo);
  v4 = tri->numIndexes / 3;
  if ( cullInfo->cullBits == (unsigned __int8 *)-1 || !r_useShadowProjectedCull.internalVar->integerValue )
    v5 = SIMDProcessor->ShadowVolume_CountFacing(SIMDProcessor, cullInfo->facing, v4);
  else
    v5 = SIMDProcessor->ShadowVolume_CountFacingCull(
           SIMDProcessor,
           cullInfo->facing,
           v4,
           tri->indexes,
           cullInfo->cullBits);
  v6 = v4 - v5;
  if ( v4 == v5 )
    return 0;
  v8 = R_AllocStaticTriSurf();
  v8->numVerts = 2 * tri->numVerts;
  R_AllocStaticTriSurfIndexes(v8, 6 * (tri->numSilEdges + v6 + 1));
  v9 = SIMDProcessor->ShadowVolume_CreateSilTriangles(
         SIMDProcessor,
         v8->indexes,
         cullInfo->facing,
         (const struct silEdge_s *)tri->silEdges,
         tri->numSilEdges);
  v10 = v9 + 6 * v6;
  v8->numShadowIndexesNoFrontCaps = v10;
  v8->numIndexes = v10;
  v8->numShadowIndexesNoCaps = v9;
  v8->shadowCapPlaneBits = 64;
  R_ResizeStaticTriSurfIndexes(v8, v10 + 6);
  v8->bounds.b[0].z = idMath::INFINITY;
  v8->bounds.b[0].y = idMath::INFINITY;
  v8->bounds.b[0].x = idMath::INFINITY;
  v8->bounds.b[1].z = -1.0e30;
  v8->bounds.b[1].y = -1.0e30;
  v8->bounds.b[1].x = -1.0e30;
  ((void (__stdcall *)(unsigned __int8 *, int *, int))SIMDProcessor->ShadowVolume_CreateCapTriangles)(
    cullInfo->facing,
    tri->indexes,
    tri->numIndexes);
  return v8;
}

// FUNC: struct srfTriangles_s * __cdecl R_CreateTurboShadowVolume(class idRenderEntityLocal const *,struct srfTriangles_s const *,class idRenderLightLocal const *,struct srfCullInfo_s &)
srfTriangles_s *__cdecl R_CreateTurboShadowVolume(
        const idRenderEntityLocal *ent,
        srfTriangles_s *tri,
        const idRenderLightLocal *light,
        srfCullInfo_s *cullInfo)
{
  int numIndexes; // ecx
  unsigned __int8 *facing; // ebx
  unsigned __int8 *cullBits; // esi
  int v8; // eax
  int v9; // edx
  int *indexes; // eax
  int v11; // edx
  _DWORD *v12; // eax
  int i; // ecx
  int v14; // esi
  srfTriangles_s *v16; // esi
  int v17; // eax
  void *v18; // esp
  int v19; // eax
  unsigned __int8 *v20; // ecx
  int v21; // eax
  int v22; // ecx
  shadowCache_s *numSilEdges; // edx
  int *v24; // eax
  int v25; // edx
  int v26; // ecx
  int v27; // edx
  int v28; // ecx
  int v29; // eax
  int v30; // ecx
  int *v31; // eax
  int *v32; // edx
  int v33; // ecx
  int v34; // ecx
  int v35; // ecx
  int v36; // [esp-4h] [ebp-38h]
  idVec3 localLightOrigin; // [esp+Ch] [ebp-28h] BYREF
  int v38; // [esp+18h] [ebp-1Ch]
  int f2; // [esp+1Ch] [ebp-18h]
  shadowCache_s *shadowVerts; // [esp+20h] [ebp-14h]
  int v2; // [esp+24h] [ebp-10h]
  int v1; // [esp+28h] [ebp-Ch]
  unsigned __int8 *v43; // [esp+2Ch] [ebp-8h]
  int f1; // [esp+30h] [ebp-4h]
  unsigned __int8 *numShadowIndexes; // [esp+40h] [ebp+Ch]
  int numShadowIndexesc; // [esp+40h] [ebp+Ch]
  silEdge_t *numShadowIndexesa; // [esp+40h] [ebp+Ch]
  int numShadowIndexesd; // [esp+40h] [ebp+Ch]
  int numShadowIndexesb; // [esp+40h] [ebp+Ch]
  int numShadowingFaces; // [esp+48h] [ebp+14h]
  unsigned __int8 *numShadowingFacesa; // [esp+48h] [ebp+14h]

  R_CalcInteractionFacing(ent, tri, light, cullInfo);
  if ( r_useShadowProjectedCull.internalVar->integerValue )
    R_CalcInteractionCullBits(ent, tri, light, cullInfo);
  numIndexes = tri->numIndexes;
  facing = cullInfo->facing;
  cullBits = cullInfo->cullBits;
  v8 = numIndexes / 3;
  v9 = 0;
  numShadowingFaces = 0;
  v43 = facing;
  if ( cullBits == (unsigned __int8 *)-1 )
    goto LABEL_14;
  if ( !r_useShadowProjectedCull.internalVar->integerValue )
  {
    v9 = 0;
LABEL_14:
    for ( i = 0; i < v8; v9 += v14 )
      v14 = facing[i++];
    numShadowingFaces = v8 - v9;
    goto LABEL_17;
  }
  indexes = tri->indexes;
  v11 = 0;
  if ( numIndexes <= 0 )
    return 0;
  numShadowIndexes = facing;
  v12 = indexes + 1;
  do
  {
    if ( !*facing )
    {
      if ( ((unsigned __int8)(cullBits[v12[1]] & cullBits[*(v12 - 1)]) & cullBits[*v12]) != 0 )
        *numShadowIndexes = 1;
      else
        ++numShadowingFaces;
    }
    v11 += 3;
    facing = numShadowIndexes + 1;
    v12 += 3;
    ++numShadowIndexes;
  }
  while ( v11 < tri->numIndexes );
LABEL_17:
  if ( !numShadowingFaces )
    return 0;
  v16 = R_AllocStaticTriSurf();
  R_AllocStaticTriSurfShadowVerts(v16, 2 * tri->numVerts);
  shadowVerts = v16->shadowVertexes;
  R_GlobalPointToLocal(ent->modelMatrix, &light->globalLightOrigin, &localLightOrigin);
  numShadowIndexesc = 4 * tri->numVerts;
  v17 = numShadowIndexesc + 18;
  LOBYTE(v17) = (numShadowIndexesc + 18) & 0xFC;
  v18 = alloca(v17);
  SIMDProcessor->Memset(SIMDProcessor, &localLightOrigin, -1, numShadowIndexesc);
  v19 = 0;
  if ( tri->numIndexes > 0 )
  {
    v20 = v43;
    do
    {
      if ( !*v20 )
      {
        *((_DWORD *)&localLightOrigin.x + tri->silIndexes[v19]) = 0;
        *((_DWORD *)&localLightOrigin.x + tri->silIndexes[v19 + 1]) = 0;
        *((_DWORD *)&localLightOrigin.x + tri->silIndexes[v19 + 2]) = 0;
      }
      v19 += 3;
      ++v20;
    }
    while ( v19 < tri->numIndexes );
  }
  v21 = SIMDProcessor->CreateShadowCache(
          SIMDProcessor,
          (idVec4 *)shadowVerts,
          (int *)&localLightOrigin,
          &localLightOrigin,
          tri->verts,
          tri->numVerts);
  v16->numVerts = v21;
  c_turboUsedVerts += v21;
  c_turboUnusedVerts += 2 * tri->numVerts - v16->numVerts;
  R_ResizeStaticTriSurfShadowVerts(v16, v16->numVerts);
  R_AllocStaticTriSurfIndexes(v16, 6 * (numShadowingFaces + tri->numSilEdges));
  v22 = (int)v16->indexes;
  numShadowIndexesa = tri->silEdges;
  numSilEdges = (shadowCache_s *)tri->numSilEdges;
  v38 = v22;
  v24 = (int *)v22;
  if ( (int)numSilEdges > 0 )
  {
    shadowVerts = numSilEdges;
    do
    {
      f1 = v43[numShadowIndexesa->p1];
      f2 = v43[numShadowIndexesa->p2];
      if ( f1 != f2 )
      {
        v25 = *((_DWORD *)&localLightOrigin.x + numShadowIndexesa->v1);
        v2 = *((_DWORD *)&localLightOrigin.x + numShadowIndexesa->v2);
        v1 = v25;
        v24[1] = f1 ^ v2;
        v26 = f2;
        *v24 = v25;
        v24[2] = v26 ^ v2;
        v27 = v26 ^ v1;
        v28 = f1 ^ v1;
        v24[3] = v27;
        v24[4] = v28;
        v24[5] = v2 ^ 1;
        v24 += 6;
      }
      ++numShadowIndexesa;
      shadowVerts = (shadowCache_s *)((char *)shadowVerts - 1);
    }
    while ( shadowVerts );
    v22 = v38;
  }
  v29 = ((int)v24 - v22) >> 2;
  v36 = v29 + 6 * numShadowingFaces;
  numShadowIndexesd = v29;
  v16->numShadowIndexesNoFrontCaps = v36;
  v16->numIndexes = v36;
  v16->numShadowIndexesNoCaps = v29;
  v16->shadowCapPlaneBits = 64;
  R_ResizeStaticTriSurfIndexes(v16, v36);
  v16->bounds.b[0].z = idMath::INFINITY;
  v16->bounds.b[0].y = idMath::INFINITY;
  v16->bounds.b[0].x = idMath::INFINITY;
  v30 = numShadowIndexesd;
  v16->bounds.b[1].z = -1.0e30;
  v16->bounds.b[1].y = -1.0e30;
  numShadowIndexesb = 0;
  v16->bounds.b[1].x = -1.0e30;
  v31 = &v16->indexes[v30];
  if ( tri->numIndexes > 0 )
  {
    numShadowingFacesa = v43;
    v32 = tri->silIndexes + 2;
    do
    {
      if ( !*numShadowingFacesa )
      {
        v33 = *((_DWORD *)&localLightOrigin.x + *(v32 - 2));
        v31[2] = v33;
        v31[3] = v33 ^ 1;
        v34 = *((_DWORD *)&localLightOrigin.x + *(v32 - 1));
        v31[1] = v34;
        v31[4] = v34 ^ 1;
        v35 = *((_DWORD *)&localLightOrigin.x + *v32);
        *v31 = v35;
        v31[5] = v35 ^ 1;
        v31 += 6;
      }
      numShadowIndexesb += 3;
      ++numShadowingFacesa;
      v32 += 3;
    }
    while ( numShadowIndexesb < tri->numIndexes );
  }
  return v16;
}
