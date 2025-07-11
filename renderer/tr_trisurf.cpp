
// FUNC: int __cdecl R_TriSurfMemory(struct srfTriangles_s const *)
int __cdecl R_TriSurfMemory(const srfTriangles_s *tri)
{
  int v1; // esi
  idDrawVert *verts; // edx
  srfTriangles_s *ambientSurface; // eax
  int *indexes; // edx
  srfTriangles_s *v6; // eax

  v1 = 0;
  if ( !tri || tri == (const srfTriangles_s *)-1 )
    return 0;
  if ( tri->shadowVertexes )
  {
    v1 = 16 * tri->numVerts;
  }
  else
  {
    verts = tri->verts;
    if ( verts )
    {
      ambientSurface = tri->ambientSurface;
      if ( !ambientSurface || verts != ambientSurface->verts )
        v1 = tri->numVerts << 6;
    }
  }
  if ( tri->facePlanes )
    v1 += 16 * (tri->numIndexes / 3);
  indexes = tri->indexes;
  if ( indexes )
  {
    v6 = tri->ambientSurface;
    if ( !v6 || indexes != v6->indexes )
      v1 += 4 * tri->numIndexes;
  }
  if ( tri->silIndexes )
    v1 += 4 * tri->numIndexes;
  if ( tri->silEdges )
    v1 += 16 * tri->numSilEdges;
  if ( tri->dominantTris )
    v1 += 20 * tri->numVerts;
  if ( tri->mirroredVerts )
    v1 += 4 * tri->numMirroredVerts;
  if ( tri->dupVerts )
    v1 += 4 * tri->numDupVerts;
  return v1 + 180;
}

// FUNC: void __cdecl R_FreeStaticTriSurfVertexCaches(struct srfTriangles_s *)
void __cdecl R_FreeStaticTriSurfVertexCaches(srfTriangles_s *tri)
{
  if ( tri->primBatchMesh )
  {
    tri->primBatchMesh = 0;
    tri->silEdges = 0;
  }
  else if ( tri->ambientSurface )
  {
    idVertexCache::Free(&vertexCache, tri->lightingCache);
    tri->lightingCache = 0;
  }
  else
  {
    idVertexCache::Free(&vertexCache, tri->ambientCache);
    tri->ambientCache = 0;
  }
  if ( tri->indexCache )
  {
    idVertexCache::Free(&vertexCache, tri->indexCache);
    tri->indexCache = 0;
  }
  if ( tri->shadowCache && (tri->shadowVertexes || tri->verts) )
  {
    idVertexCache::Free(&vertexCache, tri->shadowCache);
    tri->shadowCache = 0;
  }
}

// FUNC: void __cdecl R_ReferenceStaticTriSurfVerts(struct srfTriangles_s *,struct srfTriangles_s const *)
void __cdecl R_ReferenceStaticTriSurfVerts(srfTriangles_s *tri, srfTriangles_s *reference)
{
  srfTriangles_s *topAmbientSurface; // edx
  int v3; // ecx

  tri->verts = reference->verts;
  topAmbientSurface = reference->topAmbientSurface;
  if ( topAmbientSurface )
    tri->topAmbientSurface = topAmbientSurface;
  else
    tri->topAmbientSurface = reference;
  v3 = ID + 1;
  tri->myID = ID + 1;
  ++tri->topAmbientSurface->referenceCount;
  ID = v3;
}

// FUNC: void __cdecl R_ReferenceStaticTriSurfIndexes(struct srfTriangles_s *,struct srfTriangles_s const *)
void __cdecl R_ReferenceStaticTriSurfIndexes(srfTriangles_s *tri, const srfTriangles_s *reference)
{
  tri->indexes = reference->indexes;
}

// FUNC: void __cdecl R_RangeCheckIndexes(struct srfTriangles_s const *)
void __cdecl R_RangeCheckIndexes(const srfTriangles_s *tri)
{
  int i; // edi
  int v2; // eax

  if ( tri->numIndexes < 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_RangeCheckIndexes: numIndexes < 0");
  if ( tri->numVerts < 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_RangeCheckIndexes: numVerts < 0");
  if ( tri->numIndexes % 3 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_RangeCheckIndexes: numIndexes %% 3");
  for ( i = 0; i < tri->numIndexes; ++i )
  {
    v2 = tri->indexes[i];
    if ( v2 < 0 || v2 >= tri->numVerts )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "R_RangeCheckIndexes: index out of range");
  }
}

// FUNC: void __cdecl R_RemoveDegenerateTriangles(struct srfTriangles_s *)
void __cdecl R_RemoveDegenerateTriangles(srfTriangles_s *tri)
{
  int v1; // esi
  int v2; // ebp
  int v3; // ebx
  int *silIndexes; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int *v8; // eax

  v1 = 0;
  v2 = 0;
  if ( tri->numIndexes > 0 )
  {
    v3 = 2;
    do
    {
      silIndexes = tri->silIndexes;
      v5 = silIndexes[v1];
      v6 = silIndexes[v1 + 1];
      v7 = silIndexes[v3];
      if ( v5 == v6 || v5 == v7 || v6 == v7 )
      {
        ++v2;
        memmove(
          (unsigned __int8 *)&tri->indexes[v1],
          (unsigned __int8 *)&tri->indexes[v1 + 3],
          4 * (tri->numIndexes - v1) - 12);
        v8 = tri->silIndexes;
        if ( v8 )
          memmove((unsigned __int8 *)&v8[v1], (unsigned __int8 *)&v8[v1 + 3], 4 * (tri->numIndexes - v1) - 12);
        tri->numIndexes -= 3;
        v1 -= 3;
        v3 -= 3;
      }
      v1 += 3;
      v3 += 3;
    }
    while ( v1 < tri->numIndexes );
    if ( v2 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "removed %i degenerate triangles\n",
        v2);
  }
}

// FUNC: void __cdecl R_ReverseTriangles(struct srfTriangles_s *)
void __cdecl R_ReverseTriangles(srfTriangles_s *tri)
{
  int v1; // edx
  int v2; // esi
  idDrawVert *verts; // eax
  double v4; // st7
  float *p_x; // eax
  double v6; // st6
  double v7; // st7
  int i; // eax
  int *indexes; // edx
  int v10; // esi
  float v11; // [esp+10h] [ebp-4h]

  v1 = 0;
  if ( tri->numVerts > 0 )
  {
    v2 = 0;
    do
    {
      verts = tri->verts;
      v4 = vec3_origin.x - verts[v2].normal.x;
      p_x = &verts[v2].normal.x;
      ++v1;
      ++v2;
      v11 = vec3_origin.z - p_x[2];
      v6 = v4;
      v7 = vec3_origin.y - p_x[1];
      p_x[2] = v11;
      *p_x = v6;
      p_x[1] = v7;
    }
    while ( v1 < tri->numVerts );
  }
  for ( i = 0; i < tri->numIndexes; i += 3 )
  {
    indexes = tri->indexes;
    v10 = indexes[i];
    indexes[i] = indexes[i + 1];
    tri->indexes[i + 1] = v10;
  }
}

// FUNC: int __cdecl R_DeformInfoMemoryUsed(struct deformInfo_s *)
int __cdecl R_DeformInfoMemoryUsed(deformInfo_s *deformInfo)
{
  int v1; // ecx

  v1 = 0;
  if ( deformInfo->indexes )
    v1 = 4 * deformInfo->numIndexes;
  if ( deformInfo->silIndexes )
    v1 += 4 * deformInfo->numIndexes;
  if ( deformInfo->silEdges )
    v1 += 16 * deformInfo->numSilEdges;
  if ( deformInfo->dominantTris )
    v1 += 20 * deformInfo->numSourceVerts;
  if ( deformInfo->mirroredVerts )
    v1 += 4 * deformInfo->numMirroredVerts;
  if ( deformInfo->dupVerts )
    return v1 + 4 * deformInfo->numDupVerts + 48;
  else
    return v1 + 48;
}

// FUNC: void __cdecl R_BoundTriSurf(struct srfTriangles_s *)
void __cdecl R_BoundTriSurf(srfTriangles_s *tri)
{
  (*(void (__thiscall **)(idSIMDProcessor *, idVec3 *, idDrawVert *, int))&SIMDProcessor->gap7C[12])(
    SIMDProcessor,
    &tri->bounds.b[1],
    tri->verts,
    tri->numVerts);
}

// FUNC: int * __cdecl R_CreateSilRemap(struct srfTriangles_s const *)
int *__cdecl R_CreateSilRemap(const srfTriangles_s *tri)
{
  const srfTriangles_s *v1; // edi
  int v2; // ebp
  int *v3; // esi
  int v4; // eax
  int v6; // ebx
  bool v7; // cc
  idDrawVert *verts; // edx
  int v9; // esi
  int v10; // ecx
  float *p_x; // edi
  int indexSize; // eax
  int v13; // eax
  int *remap; // [esp+10h] [ebp-30h]
  idHashIndex hash; // [esp+18h] [ebp-28h] BYREF
  int v16; // [esp+3Ch] [ebp-4h]

  v1 = tri;
  v2 = 0;
  v3 = (int *)R_ClearedStaticAlloc(4 * tri->numVerts);
  remap = v3;
  if ( r_useSilRemap.internalVar->integerValue )
  {
    idHashIndex::Init(&hash, 1024, tri->numVerts);
    v6 = 0;
    v7 = tri->numVerts <= 0;
    v16 = 0;
    if ( !v7 )
    {
      do
      {
        verts = v1->verts;
        v9 = hash.hashMask & ((int)verts[v2].xyz.x + (int)verts[v2].xyz.y + (int)verts[v2].xyz.z);
        v10 = hash.hash[v9 & hash.hashMask & hash.lookupMask];
        if ( v10 < 0 )
        {
LABEL_13:
          remap[v6] = v6;
          if ( hash.hash == idHashIndex::INVALID_INDEX )
          {
            indexSize = hash.indexSize;
            if ( v6 >= hash.indexSize )
              indexSize = v6 + 1;
            idHashIndex::Allocate(&hash, hash.hashSize, indexSize);
          }
          else if ( v6 >= hash.indexSize )
          {
            idHashIndex::ResizeIndex(&hash, v6 + 1);
          }
          v13 = v9 & hash.hashMask;
          hash.indexChain[v6] = hash.hash[v9 & hash.hashMask];
          hash.hash[v13] = v6;
        }
        else
        {
          while ( 1 )
          {
            p_x = &verts[v10].xyz.x;
            if ( *p_x == verts[v2].xyz.x && p_x[1] == verts[v2].xyz.y && p_x[2] == verts[v2].xyz.z )
              break;
            v10 = hash.indexChain[v10 & hash.lookupMask];
            if ( v10 < 0 )
            {
              v1 = tri;
              goto LABEL_13;
            }
          }
          remap[v6] = v10;
          v1 = tri;
        }
        ++v6;
        ++v2;
      }
      while ( v6 < v1->numVerts );
      v3 = remap;
    }
    v16 = -1;
    idHashIndex::Free(&hash);
    return v3;
  }
  v4 = 0;
  if ( tri->numVerts <= 0 )
    return v3;
  do
  {
    v3[v4] = v4;
    ++v4;
  }
  while ( v4 < tri->numVerts );
  return v3;
}

// FUNC: R_DefineEdge
void __usercall R_DefineEdge(int v1@<ebx>, int v2, int planeNum)
{
  int hashMask; // edx
  int v4; // esi
  int v5; // eax
  silEdge_t *v6; // ecx
  int v7; // edi
  int v8; // ecx
  int v9; // edi
  int indexSize; // ecx
  int v11; // edx
  silEdge_t *v12; // eax

  if ( v1 != v2 )
  {
    hashMask = silEdgeHash.hashMask;
    v4 = silEdgeHash.hashMask & (v1 + v2);
    v5 = silEdgeHash.hash[v4 & silEdgeHash.hashMask & silEdgeHash.lookupMask];
    if ( v5 >= 0 )
    {
      while ( v5 < 0x10000 )
      {
        v6 = &silEdges[v5];
        v7 = v6->v1;
        if ( (v7 != v1 || v6->v2 != v2) && v6->v2 == v1 && v7 == v2 && v6->p2 == numPlanes )
        {
          silEdges[v5].p2 = planeNum;
          return;
        }
        v5 = silEdgeHash.indexChain[v5 & silEdgeHash.lookupMask];
        if ( v5 < 0 )
          break;
      }
    }
    v8 = numSilEdges;
    if ( numSilEdges == 0x10000 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 140))(common.type, "MAX_SIL_EDGES");
      return;
    }
    v9 = numSilEdges;
    if ( silEdgeHash.hash == idHashIndex::INVALID_INDEX )
    {
      if ( numSilEdges < silEdgeHash.indexSize )
        indexSize = silEdgeHash.indexSize;
      else
        indexSize = numSilEdges + 1;
      idHashIndex::Allocate(&silEdgeHash, silEdgeHash.hashSize, indexSize);
    }
    else
    {
      if ( numSilEdges < silEdgeHash.indexSize )
      {
LABEL_21:
        v11 = v4 & hashMask;
        silEdgeHash.indexChain[v9] = silEdgeHash.hash[v11];
        silEdgeHash.hash[v11] = v9;
        v12 = &silEdges[v8];
        v12->p1 = planeNum;
        v12->p2 = numPlanes;
        v12->v1 = v1;
        v12->v2 = v2;
        numSilEdges = v8 + 1;
        return;
      }
      idHashIndex::ResizeIndex(&silEdgeHash, numSilEdges + 1);
    }
    hashMask = silEdgeHash.hashMask;
    v8 = numSilEdges;
    goto LABEL_21;
  }
}

// FUNC: bool __cdecl R_FaceNegativePolarity(struct srfTriangles_s const *,int)
bool __cdecl R_FaceNegativePolarity(const srfTriangles_s *tri, int firstIndex)
{
  int *indexes; // edx
  idDrawVert *verts; // esi
  int v4; // ecx
  int v5; // eax
  idDrawVert *v6; // edx

  indexes = tri->indexes;
  verts = tri->verts;
  v4 = indexes[firstIndex + 1] << 6;
  v5 = indexes[firstIndex] << 6;
  v6 = &verts[indexes[firstIndex + 2]];
  return (v6->st.y - *(float *)((char *)&verts->st.y + v5))
       * (*(float *)((char *)&verts->st.x + v4) - *(float *)((char *)&verts->st.x + v5))
       - (v6->st.x - *(float *)((char *)&verts->st.x + v5))
       * (*(float *)((char *)&verts->st.y + v4) - *(float *)((char *)&verts->st.y + v5)) < 0.0;
}

// FUNC: R_DeriveFaceTangents
void __usercall R_DeriveFaceTangents(const srfTriangles_s *tri@<ebx>, faceTangents_t *faceTangents)
{
  int i; // esi
  idDrawVert *verts; // edi
  faceTangents_t *v4; // ebp
  int *indexes; // edx
  float *p_x; // ecx
  float *v7; // eax
  float *v8; // edx
  double v9; // st7
  double v10; // st6
  double v11; // st5
  long double v12; // st5
  double v13; // st5
  double v14; // st4
  double v15; // st3
  long double v16; // st3
  long double v17; // rt0
  double v18; // st7
  double v19; // st6
  double v20; // st5
  long double v21; // st5
  long double v22; // st4
  int inva; // [esp+4h] [ebp-38h]
  float invaa; // [esp+4h] [ebp-38h]
  float temp_8; // [esp+10h] [ebp-2Ch]
  float temp_8a; // [esp+10h] [ebp-2Ch]
  float d1_4; // [esp+18h] [ebp-24h]
  float d1_8; // [esp+1Ch] [ebp-20h]
  float d1_12; // [esp+20h] [ebp-1Ch]
  float d1_16; // [esp+24h] [ebp-18h]
  float d0_4; // [esp+2Ch] [ebp-10h]
  float d0_8; // [esp+30h] [ebp-Ch]
  float d0_12; // [esp+34h] [ebp-8h]
  float d0_16; // [esp+38h] [ebp-4h]

  for ( i = 0; i < tri->numIndexes; i += 3 )
  {
    verts = tri->verts;
    v4 = &faceTangents[i / 3];
    indexes = tri->indexes;
    p_x = &verts[indexes[i + 1]].xyz.x;
    v7 = &verts[indexes[i]].xyz.x;
    v8 = &verts[indexes[i + 2]].xyz.x;
    v9 = *p_x - *v7;
    d0_4 = p_x[1] - v7[1];
    d0_8 = p_x[2] - v7[2];
    d0_12 = p_x[14] - v7[14];
    d0_16 = p_x[15] - v7[15];
    v10 = *v8 - *v7;
    d1_4 = v8[1] - v7[1];
    d1_8 = v8[2] - v7[2];
    d1_12 = v8[14] - v7[14];
    v11 = v8[15] - v7[15];
    d1_16 = v11;
    v12 = v11 * d0_12 - d1_12 * d0_16;
    if ( fabs(v12) >= 9.9999997e-21 )
    {
      v4->negativePolarity = v12 <= 0.0;
      v4->degenerate = 0;
      inva = -1;
      if ( v12 >= 0.0 )
        inva = 1;
      invaa = (float)inva;
      v13 = (d1_16 * v9 - v10 * d0_16) * invaa;
      v14 = (d1_16 * d0_4 - d1_4 * d0_16) * invaa;
      v15 = (d1_16 * d0_8 - d1_8 * d0_16) * invaa;
      temp_8 = v15;
      v16 = v15 * temp_8 + v14 * v14 + v13 * v13;
      if ( v16 != 0.0 )
      {
        v17 = 1.0 / sqrt(v16);
        v13 = v13 * v17;
        v14 = v14 * v17;
        temp_8 = temp_8 * v17;
      }
      v4->tangents[0].z = temp_8;
      v4->tangents[0].x = v13;
      v4->tangents[0].y = v14;
      v18 = (v10 * d0_12 - d1_12 * v9) * invaa;
      v19 = (d1_4 * d0_12 - d1_12 * d0_4) * invaa;
      v20 = (d1_8 * d0_12 - d1_12 * d0_8) * invaa;
      temp_8a = v20;
      v21 = v20 * temp_8a + v19 * v19 + v18 * v18;
      if ( v21 != 0.0 )
      {
        v22 = 1.0 / sqrt(v21);
        v18 = v18 * v22;
        v19 = v19 * v22;
        temp_8a = temp_8a * v22;
      }
      v4->tangents[1].z = temp_8a;
      v4->tangents[1].x = v18;
      v4->tangents[1].y = v19;
    }
    else
    {
      v4->negativePolarity = 0;
      v4->degenerate = 1;
      v4->tangents[0].z = 0.0;
      v4->tangents[0].y = 0.0;
      v4->tangents[0].x = 0.0;
      v4->tangents[1].z = 0.0;
      v4->tangents[1].y = 0.0;
      v4->tangents[1].x = 0.0;
    }
  }
}

// FUNC: void __cdecl R_DeriveTangentsWithoutNormals(struct srfTriangles_s *)
void __cdecl R_DeriveTangentsWithoutNormals(srfTriangles_s *tri)
{
  int v2; // eax
  void *v3; // esp
  int v4; // ebx
  int v5; // edx
  int v6; // ecx
  idVec3 *tangents; // eax
  idVec3 *v8; // eax
  float *v9; // eax
  float *p_x; // ecx
  float *v11; // ecx
  float *v12; // ecx
  char *v13; // eax
  char *v14; // edx
  float *v15; // ecx
  int v16; // edi
  double v17; // st7
  double v18; // st6
  double v19; // st6
  float v20; // eax
  double v21; // st7
  double v22; // st6
  double v23; // st5
  long double v24; // st4
  long double v25; // st7
  bool v26; // cc
  faceTangents_t v27; // [esp+Ch] [ebp-28h] BYREF
  float v28; // [esp+28h] [ebp-Ch]
  float v29; // [esp+2Ch] [ebp-8h]
  int v30; // [esp+30h] [ebp-4h]
  int i; // [esp+3Ch] [ebp+8h]

  v2 = 28 * tri->numIndexes / 3u + 18;
  LOBYTE(v2) = v2 & 0xFC;
  v3 = alloca(v2);
  R_DeriveFaceTangents(tri, &v27);
  v4 = 0;
  v5 = 0;
  if ( tri->numVerts > 0 )
  {
    v6 = 0;
    do
    {
      tangents = tri->verts[v6].tangents;
      tangents->z = 0.0;
      tangents->y = 0.0;
      tangents->x = 0.0;
      v8 = &tri->verts[v6].tangents[1];
      ++v5;
      v8->z = 0.0;
      v8->y = 0.0;
      v8->x = 0.0;
      ++v6;
    }
    while ( v5 < tri->numVerts );
  }
  if ( tri->numIndexes > 0 )
  {
    do
    {
      v9 = (float *)(&v27 + v4 / 3);
      p_x = &tri->verts[tri->indexes[v4]].xyz.x;
      v4 += 3;
      p_x[8] = p_x[8] + *v9;
      p_x[9] = p_x[9] + v9[1];
      p_x[10] = p_x[10] + v9[2];
      p_x[11] = v9[3] + p_x[11];
      p_x[12] = v9[4] + p_x[12];
      p_x[13] = v9[5] + p_x[13];
      v11 = &tri->verts[tri->indexes[v4 - 2]].xyz.x;
      v11[8] = v11[8] + *v9;
      v11[9] = v11[9] + v9[1];
      v11[10] = v11[10] + v9[2];
      v11[11] = v9[3] + v11[11];
      v11[12] = v9[4] + v11[12];
      v11[13] = v9[5] + v11[13];
      v12 = &tri->verts[tri->indexes[v4 - 1]].xyz.x;
      v12[8] = v12[8] + *v9;
      v12[9] = v12[9] + v9[1];
      v12[10] = v12[10] + v9[2];
      v12[11] = v9[3] + v12[11];
      v12[12] = v9[4] + v12[12];
      v12[13] = v9[5] + v12[13];
    }
    while ( v4 < tri->numIndexes );
    v4 = 0;
  }
  i = 0;
  if ( tri->numVerts > 0 )
  {
    v30 = 0;
    do
    {
      v13 = (char *)tri->verts + v4;
      v14 = v13 + 16;
      v15 = (float *)(v13 + 40);
      v16 = 2;
      do
      {
        v17 = *((float *)v14 + 2) * *v15;
        v18 = *((float *)v14 + 1);
        *(_DWORD *)&v27.negativePolarity = *(_DWORD *)v14;
        v19 = v18 * *(v15 - 1);
        v20 = *((float *)v14 + 2);
        v28 = *((float *)v14 + 1);
        v29 = v20;
        v21 = v17 + v19 + *(v15 - 2) * *(float *)v14;
        v27.tangents[1].x = *(float *)&v27.negativePolarity * v21;
        v27.tangents[1].y = v28 * v21;
        v22 = *(v15 - 2) - v27.tangents[1].x;
        v23 = *(v15 - 1) - v27.tangents[1].y;
        v27.tangents[0].z = *v15 - v21 * v20;
        *v15 = v27.tangents[0].z;
        *(v15 - 2) = v22;
        *(v15 - 1) = v23;
        v24 = *(v15 - 2) * *(v15 - 2) + *(v15 - 1) * *(v15 - 1) + *v15 * *v15;
        if ( v24 != 0.0 )
        {
          v25 = 1.0 / sqrt(v24);
          *(v15 - 2) = v25 * *(v15 - 2);
          *(v15 - 1) = v25 * *(v15 - 1);
          *v15 = v25 * *v15;
        }
        v15 += 3;
        --v16;
      }
      while ( v16 );
      v4 = v30 + 64;
      v26 = ++i < tri->numVerts;
      v30 += 64;
    }
    while ( v26 );
  }
  tri->tangentsCalculated = 1;
}

// FUNC: unsigned int __cdecl R_AllocatedMemoryTriSurfs(void)
int __cdecl R_AllocatedMemoryTriSurfs()
{
  return triVertexAllocator.baseBlockMemory
       + triIndexAllocator.baseBlockMemory
       + triShadowVertexAllocator.baseBlockMemory
       + triPlaneAllocator.baseBlockMemory
       + triSilIndexAllocator.baseBlockMemory
       + triSilEdgeAllocator.baseBlockMemory
       + triDominantTrisAllocator.baseBlockMemory
       + triMirroredVertAllocator.baseBlockMemory
       + triDupVertAllocator.baseBlockMemory
       + 180 * srfTrianglesAllocator.total;
}

// FUNC: void __cdecl R_ShowTriSurfMemory_f(class idCmdArgs const &)
void __cdecl R_ShowTriSurfMemory_f()
{
  idDynamicBlock<idDrawVert> *firstBlock; // eax
  int i; // edx
  idDynamicBlock<idDrawVert> *next; // ecx
  idDynamicBlock<int> *v3; // eax
  int j; // edx
  idDynamicBlock<int> *v5; // ecx
  idDynamicBlock<shadowCache_s> *v6; // eax
  int k; // edx
  idDynamicBlock<shadowCache_s> *v8; // ecx
  idDynamicBlock<idPlane> *v9; // eax
  int m; // edx
  idDynamicBlock<idPlane> *v11; // ecx
  idDynamicBlock<int> *v12; // eax
  int n; // edx
  idDynamicBlock<int> *v14; // ecx
  idDynamicBlock<silEdge_t> *v15; // eax
  int ii; // edx
  idDynamicBlock<silEdge_t> *v17; // ecx
  idDynamicBlock<dominantTri_s> *v18; // eax
  int jj; // edx
  idDynamicBlock<dominantTri_s> *v20; // ecx
  idDynamicBlock<int> *v21; // eax
  int kk; // edx
  idDynamicBlock<int> *v23; // ecx
  idDynamicBlock<int> *v24; // eax
  int mm; // edx
  idDynamicBlock<int> *v26; // ecx

  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB in %d triangle surfaces\n",
    (unsigned int)(180 * srfTrianglesAllocator.active) >> 10,
    srfTrianglesAllocator.active);
  firstBlock = triVertexAllocator.firstBlock;
  for ( i = 0; firstBlock; firstBlock = firstBlock->next )
  {
    if ( firstBlock->size < 0 )
    {
      if ( firstBlock->node )
      {
        next = firstBlock->next;
        if ( !next || next->size < 0 )
          ++i;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB vertex memory (%d kB free in %d blocks, %d empty base blocks)\n",
    triVertexAllocator.baseBlockMemory >> 10,
    triVertexAllocator.freeBlockMemory >> 10,
    triVertexAllocator.numFreeBlocks,
    i);
  v3 = triIndexAllocator.firstBlock;
  for ( j = 0; v3; v3 = v3->next )
  {
    if ( v3->size < 0 )
    {
      if ( v3->node )
      {
        v5 = v3->next;
        if ( !v5 || v5->size < 0 )
          ++j;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB index memory (%d kB free in %d blocks, %d empty base blocks)\n",
    triIndexAllocator.baseBlockMemory >> 10,
    triIndexAllocator.freeBlockMemory >> 10,
    triIndexAllocator.numFreeBlocks,
    j);
  v6 = triShadowVertexAllocator.firstBlock;
  for ( k = 0; v6; v6 = v6->next )
  {
    if ( v6->size < 0 )
    {
      if ( v6->node )
      {
        v8 = v6->next;
        if ( !v8 || v8->size < 0 )
          ++k;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB shadow vert memory (%d kB free in %d blocks, %d empty base blocks)\n",
    triShadowVertexAllocator.baseBlockMemory >> 10,
    triShadowVertexAllocator.freeBlockMemory >> 10,
    triShadowVertexAllocator.numFreeBlocks,
    k);
  v9 = triPlaneAllocator.firstBlock;
  for ( m = 0; v9; v9 = v9->next )
  {
    if ( v9->size < 0 )
    {
      if ( v9->node )
      {
        v11 = v9->next;
        if ( !v11 || v11->size < 0 )
          ++m;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB tri plane memory (%d kB free in %d blocks, %d empty base blocks)\n",
    triPlaneAllocator.baseBlockMemory >> 10,
    triPlaneAllocator.freeBlockMemory >> 10,
    triPlaneAllocator.numFreeBlocks,
    m);
  v12 = triSilIndexAllocator.firstBlock;
  for ( n = 0; v12; v12 = v12->next )
  {
    if ( v12->size < 0 )
    {
      if ( v12->node )
      {
        v14 = v12->next;
        if ( !v14 || v14->size < 0 )
          ++n;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB sil index memory (%d kB free in %d blocks, %d empty base blocks)\n",
    triSilIndexAllocator.baseBlockMemory >> 10,
    triSilIndexAllocator.freeBlockMemory >> 10,
    triSilIndexAllocator.numFreeBlocks,
    n);
  v15 = triSilEdgeAllocator.firstBlock;
  for ( ii = 0; v15; v15 = v15->next )
  {
    if ( v15->size < 0 )
    {
      if ( v15->node )
      {
        v17 = v15->next;
        if ( !v17 || v17->size < 0 )
          ++ii;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB sil edge memory (%d kB free in %d blocks, %d empty base blocks)\n",
    triSilEdgeAllocator.baseBlockMemory >> 10,
    triSilEdgeAllocator.freeBlockMemory >> 10,
    triSilEdgeAllocator.numFreeBlocks,
    ii);
  v18 = triDominantTrisAllocator.firstBlock;
  for ( jj = 0; v18; v18 = v18->next )
  {
    if ( v18->size < 0 )
    {
      if ( v18->node )
      {
        v20 = v18->next;
        if ( !v20 || v20->size < 0 )
          ++jj;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB dominant tri memory (%d kB free in %d blocks, %d empty base blocks)\n",
    triDominantTrisAllocator.baseBlockMemory >> 10,
    triDominantTrisAllocator.freeBlockMemory >> 10,
    triDominantTrisAllocator.numFreeBlocks,
    jj);
  v21 = triMirroredVertAllocator.firstBlock;
  for ( kk = 0; v21; v21 = v21->next )
  {
    if ( v21->size < 0 )
    {
      if ( v21->node )
      {
        v23 = v21->next;
        if ( !v23 || v23->size < 0 )
          ++kk;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB mirror vert memory (%d kB free in %d blocks, %d empty base blocks)\n",
    triMirroredVertAllocator.baseBlockMemory >> 10,
    triMirroredVertAllocator.freeBlockMemory >> 10,
    triMirroredVertAllocator.numFreeBlocks,
    kk);
  v24 = triDupVertAllocator.firstBlock;
  for ( mm = 0; v24; v24 = v24->next )
  {
    if ( v24->size < 0 )
    {
      if ( v24->node )
      {
        v26 = v24->next;
        if ( !v26 || v26->size < 0 )
          ++mm;
      }
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB dup vert memory (%d kB free in %d blocks, %d empty base blocks)\n",
    triDupVertAllocator.baseBlockMemory >> 10,
    triDupVertAllocator.freeBlockMemory >> 10,
    triDupVertAllocator.numFreeBlocks,
    mm);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d kB total triangle memory\n",
    (unsigned int)(triVertexAllocator.baseBlockMemory
                 + triIndexAllocator.baseBlockMemory
                 + triShadowVertexAllocator.baseBlockMemory
                 + triPlaneAllocator.baseBlockMemory
                 + triSilIndexAllocator.baseBlockMemory
                 + triSilEdgeAllocator.baseBlockMemory
                 + triDominantTrisAllocator.baseBlockMemory
                 + triMirroredVertAllocator.baseBlockMemory
                 + triDupVertAllocator.baseBlockMemory
                 + 180 * srfTrianglesAllocator.active) >> 10);
}

// FUNC: void __cdecl R_InitTriSurfData(void)
void __cdecl R_InitTriSurfData()
{
  idBTreeNode<idDynamicBlock<idDrawVert>,int> *v0; // eax
  idBTreeNode<idDynamicBlock<int>,int> *v1; // eax
  idBTreeNode<idDynamicBlock<shadowCache_s>,int> *v2; // eax
  idBTreeNode<idDynamicBlock<idPlane>,int> *v3; // eax
  idBTreeNode<idDynamicBlock<int>,int> *v4; // eax
  idBTreeNode<idDynamicBlock<silEdge_t>,int> *v5; // eax
  idBTreeNode<idDynamicBlock<dominantTri_s>,int> *v6; // eax
  idBTreeNode<idDynamicBlock<int>,int> *v7; // eax
  idBTreeNode<idDynamicBlock<int>,int> *v8; // eax
  idBTreeNode<idDynamicBlock<rvSilTraceVertT>,int> *v9; // eax
  idBTreeNode<idDynamicBlock<float>,int> *v10; // eax

  silEdges = (silEdge_t *)R_StaticAlloc(0x100000);
  v0 = (idBTreeNode<idDynamicBlock<idDrawVert>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&triVertexAllocator.freeTree.nodeAllocator);
  v0->key = 0;
  v0->parent = 0;
  v0->next = 0;
  v0->prev = 0;
  v0->numChildren = 0;
  v0->firstChild = 0;
  v0->lastChild = 0;
  v0->object = 0;
  triVertexAllocator.freeTree.root = v0;
  v1 = (idBTreeNode<idDynamicBlock<int>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&triIndexAllocator.freeTree.nodeAllocator);
  v1->key = 0;
  v1->parent = 0;
  v1->next = 0;
  v1->prev = 0;
  v1->numChildren = 0;
  v1->firstChild = 0;
  v1->lastChild = 0;
  v1->object = 0;
  triIndexAllocator.freeTree.root = v1;
  v2 = (idBTreeNode<idDynamicBlock<shadowCache_s>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&triShadowVertexAllocator.freeTree.nodeAllocator);
  v2->key = 0;
  v2->parent = 0;
  v2->next = 0;
  v2->prev = 0;
  v2->numChildren = 0;
  v2->firstChild = 0;
  v2->lastChild = 0;
  v2->object = 0;
  triShadowVertexAllocator.freeTree.root = v2;
  v3 = (idBTreeNode<idDynamicBlock<idPlane>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&triPlaneAllocator.freeTree.nodeAllocator);
  v3->key = 0;
  v3->parent = 0;
  v3->next = 0;
  v3->prev = 0;
  v3->numChildren = 0;
  v3->firstChild = 0;
  v3->lastChild = 0;
  v3->object = 0;
  triPlaneAllocator.freeTree.root = v3;
  v4 = (idBTreeNode<idDynamicBlock<int>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&triSilIndexAllocator.freeTree.nodeAllocator);
  v4->key = 0;
  v4->parent = 0;
  v4->next = 0;
  v4->prev = 0;
  v4->numChildren = 0;
  v4->firstChild = 0;
  v4->lastChild = 0;
  v4->object = 0;
  triSilIndexAllocator.freeTree.root = v4;
  v5 = (idBTreeNode<idDynamicBlock<silEdge_t>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&triSilEdgeAllocator.freeTree.nodeAllocator);
  v5->key = 0;
  v5->parent = 0;
  v5->next = 0;
  v5->prev = 0;
  v5->numChildren = 0;
  v5->firstChild = 0;
  v5->lastChild = 0;
  v5->object = 0;
  triSilEdgeAllocator.freeTree.root = v5;
  v6 = idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc(&triDominantTrisAllocator.freeTree.nodeAllocator);
  v6->key = 0;
  v6->parent = 0;
  v6->next = 0;
  v6->prev = 0;
  v6->numChildren = 0;
  v6->firstChild = 0;
  v6->lastChild = 0;
  v6->object = 0;
  triDominantTrisAllocator.freeTree.root = v6;
  v7 = (idBTreeNode<idDynamicBlock<int>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&triMirroredVertAllocator.freeTree.nodeAllocator);
  v7->key = 0;
  v7->parent = 0;
  v7->next = 0;
  v7->prev = 0;
  v7->numChildren = 0;
  v7->firstChild = 0;
  v7->lastChild = 0;
  v7->object = 0;
  triMirroredVertAllocator.freeTree.root = v7;
  v8 = (idBTreeNode<idDynamicBlock<int>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&triDupVertAllocator.freeTree.nodeAllocator);
  v8->key = 0;
  v8->parent = 0;
  v8->next = 0;
  v8->prev = 0;
  v8->numChildren = 0;
  v8->firstChild = 0;
  v8->lastChild = 0;
  v8->object = 0;
  triDupVertAllocator.freeTree.root = v8;
  v9 = (idBTreeNode<idDynamicBlock<rvSilTraceVertT>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&silTraceVertexAllocator.freeTree.nodeAllocator);
  v9->key = 0;
  v9->parent = 0;
  v9->next = 0;
  v9->prev = 0;
  v9->numChildren = 0;
  v9->firstChild = 0;
  v9->lastChild = 0;
  v9->object = 0;
  silTraceVertexAllocator.freeTree.root = v9;
  v10 = (idBTreeNode<idDynamicBlock<float>,int> *)idBlockAlloc<idBTreeNode<idDynamicBlock<silEdge_t>,int>,128,2>::Alloc((idBlockAlloc<idBTreeNode<idDynamicBlock<dominantTri_s>,int>,128,2> *)&skinToModelTransformAllocator.freeTree.nodeAllocator);
  v10->key = 0;
  v10->parent = 0;
  v10->next = 0;
  v10->prev = 0;
  v10->numChildren = 0;
  v10->firstChild = 0;
  v10->lastChild = 0;
  v10->object = 0;
  skinToModelTransformAllocator.freeTree.root = v10;
  triVertexAllocator.lockMemory = 1;
  triIndexAllocator.lockMemory = 1;
  triShadowVertexAllocator.lockMemory = 1;
  triPlaneAllocator.lockMemory = 1;
  triSilIndexAllocator.lockMemory = 1;
  triSilEdgeAllocator.lockMemory = 1;
  triDominantTrisAllocator.lockMemory = 1;
  triMirroredVertAllocator.lockMemory = 1;
  triDupVertAllocator.lockMemory = 1;
  silTraceVertexAllocator.lockMemory = 1;
  skinToModelTransformAllocator.lockMemory = 1;
}

// FUNC: struct srfTriangles_s * __cdecl R_AllocStaticTriSurf(void)
srfTriangles_s *__cdecl R_AllocStaticTriSurf()
{
  srfTriangles_s *v0; // edx

  v0 = idBlockAlloc<srfTriangles_s,256,17>::Alloc(&srfTrianglesAllocator);
  memset(v0, 0, sizeof(srfTriangles_s));
  return v0;
}

// FUNC: void __cdecl R_ShutdownTriSurfData(void)
void __cdecl R_ShutdownTriSurfData()
{
  R_StaticFree(silEdges);
  idHashIndex::Free(&silEdgeHash);
  idBlockAlloc<srfTriangles_s,256,17>::Shutdown(&srfTrianglesAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&triVertexAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&triIndexAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&triShadowVertexAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&triPlaneAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&triSilIndexAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&triSilEdgeAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&triDominantTrisAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown(&triMirroredVertAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown(&triDupVertAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&silTraceVertexAllocator);
  idDynamicBlockAlloc<unsigned char,1048576,1024,18>::Shutdown((idDynamicBlockAlloc<int,65536,1024,17> *)&skinToModelTransformAllocator);
}

// FUNC: void __cdecl R_ReallyFreeStaticTriSurf(struct srfTriangles_s *)
void __cdecl R_ReallyFreeStaticTriSurf(srfTriangles_s *tri)
{
  srfTriangles_s *topAmbientSurface; // eax
  idDrawVert *verts; // ecx
  srfTriangles_s *ambientSurface; // eax
  rvSilTraceVertT *silTraceVertsAlloc; // eax
  float *skinToModelTransformsAlloc; // eax
  int *indexes; // ecx
  srfTriangles_s *v7; // eax
  int *silIndexes; // eax
  dominantTri_s *dominantTris; // eax
  int *mirroredVerts; // eax
  int *dupVerts; // eax
  idPlane *facePlanes; // eax
  shadowCache_s *shadowVertexes; // eax

  if ( tri )
  {
    topAmbientSurface = tri->topAmbientSurface;
    if ( topAmbientSurface && tri->verts == topAmbientSurface->verts && topAmbientSurface->referenceCount )
    {
      --topAmbientSurface->referenceCount;
      tri->topAmbientSurface = 0;
    }
    R_FreeStaticTriSurfVertexCaches(tri);
    verts = tri->verts;
    if ( verts )
    {
      ambientSurface = tri->ambientSurface;
      if ( !ambientSurface || verts != ambientSurface->verts )
      {
        if ( tri->referenceCount )
          tri->verts = 0;
        else
          idDynamicBlockAlloc<silEdge_t,131072,1024,17>::Free(
            (idDynamicBlockAlloc<silEdge_t,131072,1024,17> *)&triVertexAllocator,
            (silEdge_t *)tri->verts);
      }
    }
    silTraceVertsAlloc = tri->silTraceVertsAlloc;
    if ( silTraceVertsAlloc )
    {
      ++silTraceVertexAllocator.numFrees;
      --silTraceVertexAllocator.numUsedBlocks;
      silTraceVertexAllocator.usedBlockMemory -= abs32(LODWORD(silTraceVertsAlloc[-1].xyzw.x));
      idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
        (idDynamicBlockAlloc<int,65536,1024,17> *)&silTraceVertexAllocator,
        (idDynamicBlock<int> *)&silTraceVertsAlloc[-2]);
    }
    skinToModelTransformsAlloc = tri->skinToModelTransformsAlloc;
    if ( skinToModelTransformsAlloc )
    {
      ++skinToModelTransformAllocator.numFrees;
      --skinToModelTransformAllocator.numUsedBlocks;
      skinToModelTransformAllocator.usedBlockMemory -= abs32(*((_DWORD *)skinToModelTransformsAlloc - 4));
      idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
        (idDynamicBlockAlloc<int,65536,1024,17> *)&skinToModelTransformAllocator,
        (idDynamicBlock<int> *)skinToModelTransformsAlloc - 1);
    }
    if ( !tri->deformedSurface )
    {
      indexes = tri->indexes;
      if ( indexes )
      {
        v7 = tri->ambientSurface;
        if ( !v7 || indexes != v7->indexes )
          idDynamicBlockAlloc<silEdge_t,131072,1024,17>::Free(
            (idDynamicBlockAlloc<silEdge_t,131072,1024,17> *)&triIndexAllocator,
            (silEdge_t *)tri->indexes);
      }
      silIndexes = tri->silIndexes;
      if ( silIndexes )
      {
        ++triSilIndexAllocator.numFrees;
        --triSilIndexAllocator.numUsedBlocks;
        triSilIndexAllocator.usedBlockMemory -= abs32(*(silIndexes - 4));
        idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
          (idDynamicBlockAlloc<int,65536,1024,17> *)&triSilIndexAllocator,
          (idDynamicBlock<int> *)silIndexes - 1);
      }
      if ( tri->silEdges && !tri->primBatchMesh )
        idDynamicBlockAlloc<silEdge_t,131072,1024,17>::Free(&triSilEdgeAllocator, tri->silEdges);
      dominantTris = tri->dominantTris;
      if ( dominantTris )
      {
        ++triDominantTrisAllocator.numFrees;
        --triDominantTrisAllocator.numUsedBlocks;
        triDominantTrisAllocator.usedBlockMemory -= abs32(dominantTris[-1].v3);
        idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
          (idDynamicBlockAlloc<int,65536,1024,17> *)&triDominantTrisAllocator,
          (idDynamicBlock<int> *)dominantTris[-2].normalizationScale);
      }
      mirroredVerts = tri->mirroredVerts;
      if ( mirroredVerts )
      {
        ++triMirroredVertAllocator.numFrees;
        --triMirroredVertAllocator.numUsedBlocks;
        triMirroredVertAllocator.usedBlockMemory -= abs32(*(mirroredVerts - 4));
        idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
          &triMirroredVertAllocator,
          (idDynamicBlock<int> *)mirroredVerts - 1);
      }
      dupVerts = tri->dupVerts;
      if ( dupVerts )
      {
        ++triDupVertAllocator.numFrees;
        --triDupVertAllocator.numUsedBlocks;
        triDupVertAllocator.usedBlockMemory -= abs32(*(dupVerts - 4));
        idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
          &triDupVertAllocator,
          (idDynamicBlock<int> *)dupVerts - 1);
      }
    }
    facePlanes = tri->facePlanes;
    if ( facePlanes )
    {
      ++triPlaneAllocator.numFrees;
      --triPlaneAllocator.numUsedBlocks;
      triPlaneAllocator.usedBlockMemory -= abs32(LODWORD(facePlanes[-1].a));
      idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
        (idDynamicBlockAlloc<int,65536,1024,17> *)&triPlaneAllocator,
        (idDynamicBlock<int> *)&facePlanes[-2]);
    }
    shadowVertexes = tri->shadowVertexes;
    if ( shadowVertexes )
    {
      ++triShadowVertexAllocator.numFrees;
      --triShadowVertexAllocator.numUsedBlocks;
      triShadowVertexAllocator.usedBlockMemory -= abs32(LODWORD(shadowVertexes[-1].xyz.x));
      idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
        (idDynamicBlockAlloc<int,65536,1024,17> *)&triShadowVertexAllocator,
        (idDynamicBlock<int> *)&shadowVertexes[-2]);
    }
    *(_DWORD *)&tri[-1].noAmbientSurfaces = srfTrianglesAllocator.free;
    --srfTrianglesAllocator.active;
    srfTrianglesAllocator.free = CONTAINING_RECORD(tri, idBlockAlloc<srfTriangles_s,256,17>::element_s, t);
  }
}

// FUNC: void __cdecl R_FreeDeferredTriSurfs(struct frameData_t *)
void __cdecl R_FreeDeferredTriSurfs(frameData_t *frame)
{
  srfTriangles_s *firstDeferredFreeTriSurf; // eax
  srfTriangles_s *nextDeferredFree; // edx
  srfTriangles_s *topAmbientSurface; // ecx
  srfTriangles_s *v4; // eax
  srfTriangles_s *v5; // esi

  if ( frame )
  {
    firstDeferredFreeTriSurf = frame->firstDeferredFreeTriSurf;
    if ( firstDeferredFreeTriSurf )
    {
      do
      {
        nextDeferredFree = firstDeferredFreeTriSurf->nextDeferredFree;
        if ( firstDeferredFreeTriSurf->ambientSurface )
        {
          topAmbientSurface = firstDeferredFreeTriSurf->topAmbientSurface;
          if ( topAmbientSurface )
          {
            if ( firstDeferredFreeTriSurf->verts == topAmbientSurface->verts && topAmbientSurface->referenceCount )
            {
              --topAmbientSurface->referenceCount;
              firstDeferredFreeTriSurf->topAmbientSurface = 0;
            }
          }
        }
        firstDeferredFreeTriSurf = nextDeferredFree;
      }
      while ( nextDeferredFree );
    }
    v4 = frame->firstDeferredFreeTriSurf;
    if ( v4 )
    {
      do
      {
        v5 = v4->nextDeferredFree;
        R_ReallyFreeStaticTriSurf(v4);
        v4 = v5;
      }
      while ( v5 );
    }
    frame->firstDeferredFreeTriSurf = 0;
    frame->lastDeferredFreeTriSurf = 0;
  }
}

// FUNC: void __cdecl R_FreeStaticTriSurf(struct srfTriangles_s *)
void __cdecl R_FreeStaticTriSurf(srfTriangles_s *tri)
{
  frameData_t *v1; // edi
  srfTriangles_s *lastDeferredFreeTriSurf; // eax

  if ( tri )
  {
    if ( tri->nextDeferredFree )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "R_FreeStaticTriSurf: freed a freed triangle");
    v1 = frameData[tr.smpFrame];
    if ( !v1 || (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 64))(common.type) )
    {
      R_ReallyFreeStaticTriSurf(tri);
    }
    else
    {
      tri->nextDeferredFree = 0;
      lastDeferredFreeTriSurf = v1->lastDeferredFreeTriSurf;
      if ( lastDeferredFreeTriSurf )
        lastDeferredFreeTriSurf->nextDeferredFree = tri;
      else
        v1->firstDeferredFreeTriSurf = tri;
      v1->lastDeferredFreeTriSurf = tri;
    }
  }
}

// FUNC: void __cdecl R_FreeDeformInfo(struct deformInfo_s *)
void __cdecl R_FreeDeformInfo(deformInfo_s *deformInfo)
{
  int *indexes; // eax
  int *silIndexes; // eax
  silEdge_t *silEdges; // eax
  dominantTri_s *dominantTris; // eax
  int *mirroredVerts; // eax
  int *dupVerts; // eax

  indexes = deformInfo->indexes;
  if ( indexes )
  {
    ++triIndexAllocator.numFrees;
    --triIndexAllocator.numUsedBlocks;
    triIndexAllocator.usedBlockMemory -= abs32(*(indexes - 4));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&triIndexAllocator,
      (idDynamicBlock<int> *)indexes - 1);
  }
  silIndexes = deformInfo->silIndexes;
  if ( silIndexes )
  {
    ++triSilIndexAllocator.numFrees;
    --triSilIndexAllocator.numUsedBlocks;
    triSilIndexAllocator.usedBlockMemory -= abs32(*(silIndexes - 4));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&triSilIndexAllocator,
      (idDynamicBlock<int> *)silIndexes - 1);
  }
  silEdges = deformInfo->silEdges;
  if ( silEdges )
  {
    ++triSilEdgeAllocator.numFrees;
    --triSilEdgeAllocator.numUsedBlocks;
    triSilEdgeAllocator.usedBlockMemory -= abs32(silEdges[-1].p1);
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&triSilEdgeAllocator,
      (idDynamicBlock<int> *)&silEdges[-2]);
  }
  dominantTris = deformInfo->dominantTris;
  if ( dominantTris )
  {
    ++triDominantTrisAllocator.numFrees;
    --triDominantTrisAllocator.numUsedBlocks;
    triDominantTrisAllocator.usedBlockMemory -= abs32(dominantTris[-1].v3);
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&triDominantTrisAllocator,
      (idDynamicBlock<int> *)dominantTris[-2].normalizationScale);
  }
  mirroredVerts = deformInfo->mirroredVerts;
  if ( mirroredVerts )
  {
    ++triMirroredVertAllocator.numFrees;
    --triMirroredVertAllocator.numUsedBlocks;
    triMirroredVertAllocator.usedBlockMemory -= abs32(*(mirroredVerts - 4));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      &triMirroredVertAllocator,
      (idDynamicBlock<int> *)mirroredVerts - 1);
  }
  dupVerts = deformInfo->dupVerts;
  if ( dupVerts )
  {
    ++triDupVertAllocator.numFrees;
    --triDupVertAllocator.numUsedBlocks;
    triDupVertAllocator.usedBlockMemory -= abs32(*(dupVerts - 4));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      &triDupVertAllocator,
      (idDynamicBlock<int> *)dupVerts - 1);
  }
  R_StaticFree(deformInfo);
}

// FUNC: void __cdecl R_PurgeTriSurfData(struct frameData_t *)
void __cdecl R_PurgeTriSurfData(frameData_t *frame)
{
  R_FreeDeferredTriSurfs(frame);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&triVertexAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&triIndexAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&triShadowVertexAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&triPlaneAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&triSilIndexAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&triSilEdgeAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&triDominantTrisAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks(&triMirroredVertAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks(&triDupVertAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&silTraceVertexAllocator);
  idDynamicBlockAlloc<int,262144,1024,17>::FreeEmptyBaseBlocks((idDynamicBlockAlloc<int,65536,1024,17> *)&skinToModelTransformAllocator);
}

// FUNC: void __cdecl R_AllocStaticTriSurfVerts(struct srfTriangles_s *,int)
void __cdecl R_AllocStaticTriSurfVerts(srfTriangles_s *tri, int numVerts)
{
  idDynamicBlock<idDrawVert> *v2; // eax
  idDynamicBlock<idDrawVert> *v3; // ecx

  ++triVertexAllocator.numAllocs;
  if ( numVerts > 0
    && (v2 = idDynamicBlockAlloc<idDrawVert,1048576,1024,17>::AllocInternal(&triVertexAllocator, numVerts)) != 0
    && (v3 = idDynamicBlockAlloc<idDrawVert,1048576,1024,17>::ResizeInternal(
               &triVertexAllocator,
               (idDynamicBlock<int> *)v2,
               numVerts)) != 0 )
  {
    ++triVertexAllocator.numUsedBlocks;
    triVertexAllocator.usedBlockMemory += abs32(v3->size);
    tri->numAllocedVerts = numVerts;
    tri->verts = (idDrawVert *)&v3[1];
  }
  else
  {
    tri->numAllocedVerts = numVerts;
    tri->verts = 0;
  }
}

// FUNC: void __cdecl R_AllocStaticTriSurfSilTraceVerts(struct srfTriangles_s *,int)
void __cdecl R_AllocStaticTriSurfSilTraceVerts(srfTriangles_s *tri, int numVerts)
{
  idDynamicBlock<int> *v2; // eax
  idDynamicBlock<shadowCache_s> *v3; // ecx

  ++silTraceVertexAllocator.numAllocs;
  if ( numVerts > 0
    && (v2 = (idDynamicBlock<int> *)idDynamicBlockAlloc<shadowCache_s,262144,1024,17>::AllocInternal(
                                      (idDynamicBlockAlloc<shadowCache_s,262144,1024,17> *)&silTraceVertexAllocator,
                                      numVerts)) != 0
    && (v3 = idDynamicBlockAlloc<shadowCache_s,262144,1024,17>::ResizeInternal(
               (idDynamicBlockAlloc<shadowCache_s,262144,1024,17> *)&silTraceVertexAllocator,
               v2,
               numVerts)) != 0 )
  {
    ++silTraceVertexAllocator.numUsedBlocks;
    silTraceVertexAllocator.usedBlockMemory += abs32(v3->size);
    tri->numAllocedVerts = numVerts;
    tri->silTraceVertsAlloc = (rvSilTraceVertT *)&v3[1];
    tri->silTraceVerts = (rvSilTraceVertT *)&v3[1];
  }
  else
  {
    tri->numAllocedVerts = numVerts;
    tri->silTraceVertsAlloc = 0;
    tri->silTraceVerts = 0;
  }
}

// FUNC: void __cdecl R_AllocStaticSkinToModelTransforms(struct srfTriangles_s *,int)
void __cdecl R_AllocStaticSkinToModelTransforms(srfTriangles_s *tri, int numTransforms)
{
  float *skinToModelTransformsAlloc; // eax
  idDynamicBlock<int> *v3; // eax
  idDynamicBlock<int> *v4; // ecx
  float *id; // eax

  skinToModelTransformsAlloc = tri->skinToModelTransformsAlloc;
  if ( skinToModelTransformsAlloc )
  {
    if ( tri->numSkinToModelTransforms >= numTransforms )
      return;
    ++skinToModelTransformAllocator.numFrees;
    --skinToModelTransformAllocator.numUsedBlocks;
    skinToModelTransformAllocator.usedBlockMemory -= abs32(*((_DWORD *)skinToModelTransformsAlloc - 4));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&skinToModelTransformAllocator,
      (idDynamicBlock<int> *)skinToModelTransformsAlloc - 1);
  }
  ++skinToModelTransformAllocator.numAllocs;
  if ( 16 * numTransforms > 0
    && (v3 = idDynamicBlockAlloc<float,65536,1024,17>::AllocInternal(
               (idDynamicBlockAlloc<int,65536,1024,17> *)&skinToModelTransformAllocator,
               16 * numTransforms)) != 0
    && (v4 = idDynamicBlockAlloc<int,65536,1024,17>::ResizeInternal(
               (idDynamicBlockAlloc<int,65536,1024,17> *)&skinToModelTransformAllocator,
               v3,
               16 * numTransforms)) != 0 )
  {
    ++skinToModelTransformAllocator.numUsedBlocks;
    skinToModelTransformAllocator.usedBlockMemory += abs32(v4->size);
    id = (float *)v4[1].id;
  }
  else
  {
    id = 0;
  }
  tri->skinToModelTransforms = id;
  tri->skinToModelTransformsAlloc = id;
  tri->numSkinToModelTransforms = numTransforms;
}

// FUNC: void __cdecl R_AllocStaticTriSurfIndexes(struct srfTriangles_s *,int)
void __cdecl R_AllocStaticTriSurfIndexes(srfTriangles_s *tri, int numIndexes)
{
  idDynamicBlock<int> *v2; // eax
  idDynamicBlock<int> *v3; // ecx

  ++triIndexAllocator.numAllocs;
  if ( numIndexes > 0
    && (v2 = idDynamicBlockAlloc<int,262144,1024,17>::AllocInternal(&triIndexAllocator, numIndexes)) != 0
    && (v3 = idDynamicBlockAlloc<int,262144,1024,17>::ResizeInternal(&triIndexAllocator, v2, numIndexes)) != 0 )
  {
    ++triIndexAllocator.numUsedBlocks;
    triIndexAllocator.usedBlockMemory += abs32(v3->size);
    tri->numAllocedIndices = numIndexes;
    tri->indexes = v3[1].id;
  }
  else
  {
    tri->numAllocedIndices = numIndexes;
    tri->indexes = 0;
  }
}

// FUNC: void __cdecl R_AllocStaticTriSurfShadowVerts(struct srfTriangles_s *,int)
void __cdecl R_AllocStaticTriSurfShadowVerts(srfTriangles_s *tri, int numVerts)
{
  idDynamicBlock<int> *v2; // eax
  idDynamicBlock<shadowCache_s> *v3; // eax

  ++triShadowVertexAllocator.numAllocs;
  if ( numVerts <= 0 )
    goto LABEL_5;
  v2 = (idDynamicBlock<int> *)idDynamicBlockAlloc<shadowCache_s,262144,1024,17>::AllocInternal(
                                &triShadowVertexAllocator,
                                numVerts);
  if ( !v2 )
  {
    tri->shadowVertexes = 0;
    return;
  }
  v3 = idDynamicBlockAlloc<shadowCache_s,262144,1024,17>::ResizeInternal(&triShadowVertexAllocator, v2, numVerts);
  if ( v3 )
  {
    ++triShadowVertexAllocator.numUsedBlocks;
    triShadowVertexAllocator.usedBlockMemory += abs32(v3->size);
    tri->shadowVertexes = (shadowCache_s *)&v3[1];
  }
  else
  {
LABEL_5:
    tri->shadowVertexes = 0;
  }
}

// FUNC: void __cdecl R_AllocStaticTriSurfPlanes(struct srfTriangles_s *,int)
void __cdecl R_AllocStaticTriSurfPlanes(srfTriangles_s *tri, int numIndexes)
{
  idPlane *facePlanes; // eax
  idDynamicBlock<int> *v3; // eax
  idDynamicBlock<silEdge_t> *v4; // ecx

  facePlanes = tri->facePlanes;
  if ( facePlanes )
  {
    ++triPlaneAllocator.numFrees;
    --triPlaneAllocator.numUsedBlocks;
    triPlaneAllocator.usedBlockMemory -= abs32(LODWORD(facePlanes[-1].a));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&triPlaneAllocator,
      (idDynamicBlock<int> *)&facePlanes[-2]);
  }
  ++triPlaneAllocator.numAllocs;
  if ( numIndexes / 3 > 0
    && (v3 = (idDynamicBlock<int> *)idDynamicBlockAlloc<silEdge_t,131072,1024,17>::AllocInternal(
                                      (idDynamicBlockAlloc<silEdge_t,131072,1024,17> *)&triPlaneAllocator,
                                      numIndexes / 3)) != 0
    && (v4 = idDynamicBlockAlloc<silEdge_t,131072,1024,17>::ResizeInternal(
               (idDynamicBlockAlloc<silEdge_t,131072,1024,17> *)&triPlaneAllocator,
               v3,
               numIndexes / 3)) != 0 )
  {
    ++triPlaneAllocator.numUsedBlocks;
    triPlaneAllocator.usedBlockMemory += abs32(v4->size);
    tri->facePlanes = (idPlane *)&v4[1];
  }
  else
  {
    tri->facePlanes = 0;
  }
}

// FUNC: void __cdecl R_ResizeStaticTriSurfIndexes(struct srfTriangles_s *,int)
void __cdecl R_ResizeStaticTriSurfIndexes(srfTriangles_s *tri, int numIndexes)
{
  idDynamicBlock<int> *v2; // eax

  v2 = idDynamicBlockAlloc<int,262144,1024,17>::Resize(
         &triIndexAllocator,
         (idDynamicBlock<int> *)tri->indexes,
         numIndexes);
  tri->numAllocedIndices = numIndexes;
  tri->indexes = (int *)v2;
}

// FUNC: void __cdecl R_ResizeStaticTriSurfShadowVerts(struct srfTriangles_s *,int)
void __cdecl R_ResizeStaticTriSurfShadowVerts(srfTriangles_s *tri, int numVerts)
{
  tri->shadowVertexes = (shadowCache_s *)idDynamicBlockAlloc<shadowCache_s,262144,1024,17>::Resize(
                                           &triShadowVertexAllocator,
                                           tri->shadowVertexes,
                                           numVerts);
}

// FUNC: void __cdecl R_CreateSilIndexes(struct srfTriangles_s *)
void __cdecl R_CreateSilIndexes(srfTriangles_s *tri)
{
  int *silIndexes; // eax
  int *SilRemap; // eax
  int numIndexes; // edi
  int *v4; // ebx
  idDynamicBlock<int> *v5; // eax
  int i; // eax

  silIndexes = tri->silIndexes;
  if ( silIndexes )
  {
    ++triSilIndexAllocator.numFrees;
    --triSilIndexAllocator.numUsedBlocks;
    triSilIndexAllocator.usedBlockMemory -= abs32(*(silIndexes - 4));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&triSilIndexAllocator,
      (idDynamicBlock<int> *)silIndexes - 1);
    tri->silIndexes = 0;
  }
  SilRemap = R_CreateSilRemap(tri);
  numIndexes = tri->numIndexes;
  ++triSilIndexAllocator.numAllocs;
  v4 = SilRemap;
  if ( numIndexes > 0 )
  {
    v5 = idDynamicBlockAlloc<int,131072,1024,17>::AllocInternal(&triSilIndexAllocator, numIndexes);
    if ( v5 )
    {
      v5 = idDynamicBlockAlloc<int,131072,1024,17>::ResizeInternal(&triSilIndexAllocator, v5, numIndexes);
      if ( v5 )
      {
        ++triSilIndexAllocator.numUsedBlocks;
        triSilIndexAllocator.usedBlockMemory += abs32(v5->size);
        ++v5;
      }
    }
  }
  else
  {
    v5 = 0;
  }
  tri->silIndexes = (int *)v5;
  for ( i = 0; i < tri->numIndexes; ++i )
    tri->silIndexes[i] = v4[tri->indexes[i]];
  R_StaticFree(v4);
}

// FUNC: void __cdecl R_CreateDupVerts(struct srfTriangles_s *)
void __cdecl R_CreateDupVerts(srfTriangles_s *tri)
{
  int numVerts; // ebx
  int v2; // eax
  void *v3; // esp
  int v4; // eax
  int i; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // eax
  void *v9; // esp
  int v10; // eax
  bool v11; // cc
  int numDupVerts; // edi
  int v13; // edi
  idDynamicBlock<int> *v14; // eax
  idDynamicBlock<int> *v15; // eax
  int *id; // edx
  int v17; // [esp+8h] [ebp-4h] BYREF

  numVerts = tri->numVerts;
  v2 = 4 * numVerts + 18;
  LOBYTE(v2) = v2 & 0xFC;
  v3 = alloca(v2);
  v4 = 0;
  if ( numVerts > 0 )
  {
    do
    {
      *(&v17 + v4) = v4;
      ++v4;
    }
    while ( v4 < tri->numVerts );
  }
  for ( i = 0; i < tri->numIndexes; *(&v17 + v6) = v7 )
  {
    v6 = tri->indexes[i];
    v7 = tri->silIndexes[i++];
  }
  v8 = 8 * tri->numVerts + 18;
  LOBYTE(v8) = v8 & 0xFC;
  v9 = alloca(v8);
  v10 = 0;
  v11 = tri->numVerts <= 0;
  tri->numDupVerts = 0;
  if ( !v11 )
  {
    do
    {
      if ( *(&v17 + v10) != v10 )
      {
        *(&v17 + 2 * tri->numDupVerts) = v10;
        *(&v17 + 2 * tri->numDupVerts++ + 1) = *(&v17 + v10);
      }
      ++v10;
    }
    while ( v10 < tri->numVerts );
  }
  numDupVerts = tri->numDupVerts;
  ++triDupVertAllocator.numAllocs;
  v13 = 2 * numDupVerts;
  if ( v13 > 0
    && (v14 = idDynamicBlockAlloc<float,65536,1024,17>::AllocInternal(&triDupVertAllocator, v13)) != 0
    && (v15 = idDynamicBlockAlloc<int,65536,1024,17>::ResizeInternal(&triDupVertAllocator, v14, v13)) != 0 )
  {
    ++triDupVertAllocator.numUsedBlocks;
    triDupVertAllocator.usedBlockMemory += abs32(v15->size);
    id = v15[1].id;
  }
  else
  {
    id = 0;
  }
  tri->dupVerts = id;
  ((void (__stdcall *)(int *, int))SIMDProcessor->Memcpy)(&v17, 8 * tri->numDupVerts);
}

// FUNC: void __cdecl R_DeriveFacePlanes(struct srfTriangles_s *)
void __cdecl R_DeriveFacePlanes(srfTriangles_s *tri)
{
  rvMesh *primBatchMesh; // ecx
  idPlane *facePlanes; // edx

  if ( !tri->facePlanes )
    R_AllocStaticTriSurfPlanes(tri, tri->numIndexes);
  primBatchMesh = tri->primBatchMesh;
  facePlanes = tri->facePlanes;
  if ( primBatchMesh )
    rvMesh::DeriveTriPlanes(primBatchMesh, facePlanes, tri->silTraceVerts);
  else
    SIMDProcessor->DeriveTriPlanes(SIMDProcessor, facePlanes, tri->verts, tri->numVerts, tri->indexes, tri->numIndexes);
  tri->facePlanesCalculated = 1;
}

// FUNC: void __cdecl R_IdentifySilEdges(struct srfTriangles_s *,bool,bool)
void __cdecl R_IdentifySilEdges(srfTriangles_s *tri)
{
  srfTriangles_s *v1; // ebp
  int v2; // ebx
  unsigned int v3; // edx
  int v4; // esi
  int *silIndexes; // eax
  int v6; // edi
  int v7; // ebp
  int v8; // eax
  int v9; // esi
  int *p_p2; // ecx
  int v11; // edx
  int v12; // esi
  silEdge_t *v13; // edx
  idDynamicBlock<int> *v14; // eax
  idDynamicBlock<silEdge_t> *v15; // eax
  int v16; // [esp+10h] [ebp-Ch]
  int i3; // [esp+14h] [ebp-8h]

  v1 = tri;
  v2 = tri->numIndexes / 3;
  v3 = 0;
  numSilEdges = 0;
  if ( silEdgeHash.hash != idHashIndex::INVALID_INDEX )
    memset(silEdgeHash.hash, 0xFFu, 4 * silEdgeHash.hashSize);
  v4 = 0;
  numPlanes = v2;
  if ( v2 > 0 )
  {
    v16 = 0;
    do
    {
      silIndexes = v1->silIndexes;
      v6 = silIndexes[v16];
      v7 = silIndexes[v16 + 1];
      i3 = silIndexes[v16 + 2];
      R_DefineEdge(v6, v7, v4);
      R_DefineEdge(v7, i3, v4);
      R_DefineEdge(i3, v6, v4);
      v16 += 3;
      v1 = tri;
      ++v4;
    }
    while ( v4 < v2 );
    v3 = numSilEdges;
  }
  c_totalSilEdges += v3;
  qsort(silEdges, v3, 0x10u, (int (__cdecl *)(const void *, const void *))SilEdgeSort);
  v8 = numSilEdges;
  v9 = 0;
  if ( numSilEdges <= 0 )
    goto LABEL_13;
  p_p2 = &silEdges->p2;
  v11 = numSilEdges;
  do
  {
    if ( *p_p2 == numPlanes )
      ++v9;
    p_p2 += 4;
    --v11;
  }
  while ( v11 );
  if ( v9 )
    v1->perfectHull = 0;
  else
LABEL_13:
    v1->perfectHull = 1;
  v1->numSilEdges = v8;
  ++triSilEdgeAllocator.numAllocs;
  v12 = v8;
  if ( v8 > 0 )
  {
    v14 = (idDynamicBlock<int> *)idDynamicBlockAlloc<silEdge_t,131072,1024,17>::AllocInternal(&triSilEdgeAllocator, v8);
    if ( v14
      && (v15 = idDynamicBlockAlloc<silEdge_t,131072,1024,17>::ResizeInternal(&triSilEdgeAllocator, v14, v12)) != 0 )
    {
      ++triSilEdgeAllocator.numUsedBlocks;
      triSilEdgeAllocator.usedBlockMemory += abs32(v15->size);
      v13 = (silEdge_t *)&v15[1];
    }
    else
    {
      v13 = 0;
    }
    v8 = numSilEdges;
  }
  else
  {
    v13 = 0;
  }
  v1->silEdges = v13;
  ((void (__thiscall *)(idSIMDProcessor *, silEdge_t *, int))SIMDProcessor->Memcpy)(SIMDProcessor, silEdges, 16 * v8);
}

// FUNC: R_DuplicateMirroredVertexes
void __usercall R_DuplicateMirroredVertexes(srfTriangles_s *tri@<esi>)
{
  unsigned int v1; // edi
  int v2; // eax
  void *v3; // esp
  int *v4; // ebx
  int v5; // ecx
  bool v6; // cc
  int *indexes; // edi
  int v8; // eax
  int v9; // edx
  idDrawVert *verts; // ebx
  int v11; // edi
  int v12; // eax
  int v13; // ecx
  int v14; // edx
  _DWORD *v15; // eax
  int v16; // eax
  int v17; // edi
  idDynamicBlock<int> *v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // ecx
  int *v22; // edi
  idDrawVert *v23; // ebx
  int v24; // edx
  int v25; // eax
  idDrawVert *v26; // ecx
  idDrawVert *v27; // eax
  idDrawVert *v28; // edx
  double v29; // st7
  double y; // st6
  idDrawVert *v31; // [esp-8h] [ebp-24h]
  int v32; // [esp+8h] [ebp-14h] BYREF
  int *v33; // [esp+Ch] [ebp-10h]
  int v34; // [esp+10h] [ebp-Ch]
  _DWORD *v35; // [esp+14h] [ebp-8h]
  int numVerts; // [esp+18h] [ebp-4h]

  v1 = 8 * tri->numVerts;
  v2 = v1 + 18;
  LOBYTE(v2) = (v1 + 18) & 0xFC;
  v3 = alloca(v2);
  v4 = &v32;
  memset(&v32, 0, v1);
  v5 = 0;
  v6 = tri->numIndexes <= 0;
  v33 = &v32;
  if ( !v6 )
  {
    do
    {
      indexes = tri->indexes;
      v8 = indexes[v5];
      v9 = indexes[v5 + 1];
      verts = tri->verts;
      v11 = indexes[v5 + 2];
      v32 = v8;
      v8 <<= 6;
      LOBYTE(v8) = (verts[v11].st.y - *(float *)((char *)&verts->st.y + v8))
                 * (verts[v9].st.x - *(float *)((char *)&verts->st.x + v8))
                 - (verts[v11].st.x - *(float *)((char *)&verts->st.x + v8))
                 * (verts[v9].st.y - *(float *)((char *)&verts->st.y + v8)) < 0.0;
      v4 = v33;
      *((_BYTE *)&v33[2 * v32] + (unsigned __int8)v8) = 1;
      *((_BYTE *)&v4[2 * tri->indexes[v5 + 1]] + (unsigned __int8)v8) = 1;
      v12 = (unsigned __int8)v8 + 8 * tri->indexes[v5 + 2];
      v5 += 3;
      *((_BYTE *)v4 + v12) = 1;
    }
    while ( v5 < tri->numIndexes );
  }
  v14 = 0;
  numVerts = tri->numVerts;
  v13 = numVerts;
  if ( numVerts > 0 )
  {
    v15 = v4 + 1;
    do
    {
      if ( *((_BYTE *)v15 - 4) && *((_BYTE *)v15 - 3) )
        *v15 = v13++;
      ++v14;
      v15 += 2;
    }
    while ( v14 < tri->numVerts );
    numVerts = v13;
  }
  v16 = tri->numVerts;
  v17 = v13 - v16;
  tri->numMirroredVerts = v13 - v16;
  if ( v13 == v16 )
  {
    tri->mirroredVerts = 0;
  }
  else
  {
    ++triMirroredVertAllocator.numAllocs;
    if ( v17 > 0 )
    {
      v18 = idDynamicBlockAlloc<float,65536,1024,17>::AllocInternal(&triMirroredVertAllocator, v13 - v16);
      if ( v18 )
      {
        v18 = idDynamicBlockAlloc<int,65536,1024,17>::ResizeInternal(&triMirroredVertAllocator, v18, v17);
        if ( v18 )
        {
          ++triMirroredVertAllocator.numUsedBlocks;
          triMirroredVertAllocator.usedBlockMemory += abs32(v18->size);
          ++v18;
        }
      }
      v13 = numVerts;
    }
    else
    {
      v18 = 0;
    }
    v31 = tri->verts;
    tri->mirroredVerts = (int *)v18;
    tri->verts = idDynamicBlockAlloc<idDrawVert,1048576,1024,17>::Resize(&triVertexAllocator, v31, v13);
    v19 = 0;
    if ( tri->numVerts > 0 )
    {
      v32 = 0;
      v34 = 0;
      v35 = v4 + 1;
      do
      {
        if ( *v35 )
        {
          idDrawVert::operator=((char *)tri->verts + v34);
          v20 = v32;
          *(int *)((char *)tri->mirroredVerts + v32) = v19;
          v32 = v20 + 4;
        }
        v35 += 2;
        v34 += 64;
        ++v19;
      }
      while ( v19 < tri->numVerts );
    }
    v21 = 0;
    v6 = tri->numIndexes <= 0;
    tri->numVerts = numVerts;
    v34 = 0;
    if ( !v6 )
    {
      do
      {
        v22 = tri->indexes;
        if ( v4[2 * v22[v21] + 1] )
        {
          v23 = tri->verts;
          v24 = 3 * (v21 / 3);
          v25 = v22[3 * (v21 / 3)];
          v26 = &v23[v22[3 * (v21 / 3) + 1]];
          v27 = &v23[v25];
          v28 = &v23[v22[v24 + 2]];
          v29 = v26->st.x - v27->st.x;
          v4 = v33;
          y = v26->st.y;
          v21 = v34;
          if ( (v28->st.y - v27->st.y) * v29 - (v28->st.x - v27->st.x) * (y - v27->st.y) < 0.0 )
            v22[v34] = v33[2 * v22[v34] + 1];
        }
        v6 = ++v21 < tri->numIndexes;
        v34 = v21;
      }
      while ( v6 );
    }
    tri->numVerts = numVerts;
  }
}

// FUNC: void __cdecl R_BuildDominantTris(struct srfTriangles_s *)
void __cdecl R_BuildDominantTris(srfTriangles_s *tri)
{
  indexSort_t *v2; // esi
  int v3; // ecx
  int numVerts; // edi
  idDynamicBlock<int> *v5; // eax
  idDynamicBlock<dominantTri_s> *v6; // ecx
  unsigned int v7; // edx
  int v8; // ecx
  int *p_faceNum; // eax
  int *indexes; // ecx
  idDrawVert *verts; // esi
  int v12; // eax
  int v13; // ebx
  int v14; // edx
  int v15; // edi
  float *p_x; // ecx
  float *v17; // eax
  float *v18; // edx
  double v19; // st7
  double v20; // st6
  double v21; // st4
  double v22; // st3
  double v23; // st1
  long double v24; // st5
  dominantTri_s *v25; // ecx
  double v26; // st5
  double v27; // st7
  double v28; // st5
  double v29; // st4
  double v30; // st2
  long double v31; // st6
  double v32; // st5
  float area; // [esp+10h] [ebp-4Ch]
  int *k; // [esp+14h] [ebp-48h]
  int j; // [esp+18h] [ebp-44h]
  int i; // [esp+1Ch] [ebp-40h]
  float maxArea; // [esp+20h] [ebp-3Ch]
  int vertNum; // [esp+24h] [ebp-38h]
  int i3; // [esp+28h] [ebp-34h]
  int i3a; // [esp+28h] [ebp-34h]
  int i3b; // [esp+28h] [ebp-34h]
  int v42; // [esp+2Ch] [ebp-30h]
  indexSort_t *ind; // [esp+30h] [ebp-2Ch]
  float d1; // [esp+34h] [ebp-28h]
  float d1_4; // [esp+38h] [ebp-24h]
  float d1_8; // [esp+3Ch] [ebp-20h]
  float d1_16; // [esp+44h] [ebp-18h]
  float d0; // [esp+48h] [ebp-14h]
  float d0_4; // [esp+4Ch] [ebp-10h]
  float d0_8; // [esp+50h] [ebp-Ch]
  float d0_16; // [esp+58h] [ebp-4h]
  dominantTri_s *tria; // [esp+60h] [ebp+4h]

  v2 = (indexSort_t *)R_StaticAlloc(8 * tri->numIndexes);
  v3 = 0;
  for ( ind = v2; v3 < tri->numIndexes; ++v3 )
  {
    v2[v3].vertexNum = tri->indexes[v3];
    v2[v3].faceNum = v3 / 3;
  }
  qsort(v2, tri->numIndexes, 8u, (int (__cdecl *)(const void *, const void *))IndexSort);
  numVerts = tri->numVerts;
  ++triDominantTrisAllocator.numAllocs;
  if ( numVerts > 0 )
  {
    v5 = (idDynamicBlock<int> *)idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::AllocInternal(
                                  &triDominantTrisAllocator,
                                  numVerts);
    if ( v5 )
    {
      v6 = idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::ResizeInternal(&triDominantTrisAllocator, v5, numVerts);
      if ( v6 )
      {
        ++triDominantTrisAllocator.numUsedBlocks;
        triDominantTrisAllocator.usedBlockMemory += abs32(v6->size);
        tria = (dominantTri_s *)&v6[1];
      }
      else
      {
        tria = 0;
      }
    }
    else
    {
      tria = 0;
    }
  }
  else
  {
    tria = 0;
  }
  v7 = 20 * tri->numVerts;
  tri->dominantTris = tria;
  memset(tria, 0, v7);
  v8 = 0;
  for ( i = 0; v8 < tri->numIndexes; i = v8 )
  {
    maxArea = 0.0;
    vertNum = v2[v8].vertexNum;
    j = 0;
    if ( v8 < tri->numIndexes )
    {
      p_faceNum = &v2[v8].faceNum;
      v42 = v8;
      for ( k = p_faceNum; *(p_faceNum - 1) == vertNum; p_faceNum = k )
      {
        indexes = tri->indexes;
        verts = tri->verts;
        v12 = 3 * *p_faceNum;
        v13 = indexes[v12 + 1];
        v14 = indexes[v12 + 2];
        v15 = indexes[v12];
        p_x = &verts[v13].xyz.x;
        v17 = &verts[v15].xyz.x;
        i3 = v14;
        d0 = *p_x - *v17;
        v18 = &verts[v14].xyz.x;
        d0_4 = p_x[1] - v17[1];
        d0_8 = p_x[2] - v17[2];
        v19 = p_x[14] - v17[14];
        d0_16 = p_x[15] - v17[15];
        d1 = *v18 - *v17;
        d1_4 = v18[1] - v17[1];
        d1_8 = v18[2] - v17[2];
        v20 = v18[14] - v17[14];
        d1_16 = v18[15] - v17[15];
        v21 = d1_8 * d0 - d1 * d0_8;
        v22 = d1 * d0_4 - d1_4 * d0;
        v23 = d1_4 * d0_8 - d1_8 * d0_4;
        v24 = sqrt(v22 * v22 + v21 * v21 + v23 * v23);
        area = v24;
        if ( v24 >= maxArea )
        {
          maxArea = v24;
          if ( v15 == vertNum )
          {
            v25 = &tria[vertNum];
            v25->v2 = v13;
            v25->v3 = i3;
          }
          else
          {
            v25 = &tria[vertNum];
            if ( v13 == vertNum )
            {
              v25->v2 = i3;
              v25->v3 = v15;
            }
            else
            {
              v25->v2 = v15;
              v25->v3 = v13;
            }
          }
          v26 = area;
          if ( area < 0.001 )
            v26 = 0.001;
          v25->normalizationScale[2] = 1.0 / v26;
          v27 = v19 * d1_16 - v20 * d0_16;
          v28 = d1_16 * d0_4 - d1_4 * d0_16;
          v29 = d1_16 * d0_8 - d1_8 * d0_16;
          v30 = d1_16 * d0 - d1 * d0_16;
          v31 = sqrt(v29 * v29 + v28 * v28 + v30 * v30);
          if ( v31 < 0.001 )
            v31 = 0.001;
          i3a = 1;
          if ( v27 <= 0.0 )
            i3a = -1;
          v32 = (double)i3a;
          i3b = 1;
          v25->normalizationScale[0] = v32 / v31;
          if ( v27 <= 0.0 )
            i3b = -1;
          v25->normalizationScale[1] = (float)i3b;
        }
        ++j;
        k += 2;
        v2 = ind;
        v8 = i;
        if ( ++v42 >= tri->numIndexes )
          break;
      }
    }
    v8 += j;
  }
  R_StaticFree(v2);
}

// FUNC: void __cdecl R_DeriveTangents(struct srfTriangles_s *,bool)
void __cdecl R_DeriveTangents(srfTriangles_s *tri, bool allocFacePlanes)
{
  dominantTri_s *dominantTris; // eax
  int v4; // eax
  void *v5; // esp
  int *dupVerts; // edx
  idDrawVert *verts; // edi
  int i; // ecx
  int v9; // eax
  double v10; // st7
  int v11; // ebx
  int v12; // eax
  double v13; // st7
  float *v14; // eax
  int j; // eax
  _DWORD *p_x; // ecx
  srfTriangles_s *tria; // [esp+14h] [ebp+8h]

  dominantTris = tri->dominantTris;
  if ( dominantTris )
  {
    if ( !tri->tangentsCalculated )
    {
      SIMDProcessor->DeriveUnsmoothedTangents(SIMDProcessor, tri->verts, dominantTris, tri->numVerts);
      tri->tangentsCalculated = 1;
    }
  }
  else if ( !tri->tangentsCalculated )
  {
    tr.pc.c_tangentIndexes += tri->numIndexes;
    if ( !tri->facePlanes && allocFacePlanes )
      R_AllocStaticTriSurfPlanes(tri, tri->numIndexes);
    if ( !tri->facePlanes )
    {
      v4 = 16 * (tri->numIndexes / 3) + 18;
      LOBYTE(v4) = v4 & 0xFC;
      v5 = alloca(v4);
    }
    ((void (__thiscall *)(idSIMDProcessor *, idDrawVert *, int, int *, int))SIMDProcessor->DeriveTangents)(
      SIMDProcessor,
      tri->verts,
      tri->numVerts,
      tri->indexes,
      tri->numIndexes);
    dupVerts = tri->dupVerts;
    verts = tri->verts;
    for ( i = 0; i < tri->numDupVerts; v14[2] = *(float *)(v11 + 8) + v14[2] )
    {
      v9 = dupVerts[2 * i + 1] << 6;
      v10 = *(float *)((char *)&verts->normal.x + v9);
      v11 = (int)&verts->normal + v9;
      v12 = dupVerts[2 * i] << 6;
      v13 = v10 + *(float *)((char *)&verts->normal.x + v12);
      v14 = (float *)((char *)&verts->normal.x + v12);
      ++i;
      *v14 = v13;
      v14[1] = *(float *)(v11 + 4) + v14[1];
    }
    for ( j = 0; j < tri->numDupVerts; p_x[2] = LODWORD(tria->bounds.b[0].z) )
    {
      tria = (srfTriangles_s *)&verts[dupVerts[2 * j]].normal;
      p_x = (_DWORD *)&verts[dupVerts[2 * j + 1]].normal.x;
      *p_x = LODWORD(tria->bounds.b[0].x);
      p_x[1] = LODWORD(tria->bounds.b[0].y);
      ++j;
    }
    SIMDProcessor->NormalizeTangents(SIMDProcessor, tri->verts, tri->numVerts);
    tri->facePlanesCalculated = 1;
    tri->tangentsCalculated = 1;
  }
}

// FUNC: struct srfTriangles_s * __cdecl R_MergeSurfaceList(struct srfTriangles_s const * *,int)
srfTriangles_s *__cdecl R_MergeSurfaceList(const srfTriangles_s **surfaces, int numSurfaces)
{
  int v2; // esi
  int v3; // ebp
  int j; // eax
  const srfTriangles_s *v5; // ecx
  srfTriangles_s *v6; // ebx
  idDrawVert *v7; // eax
  int v8; // ebp
  idDynamicBlock<idDrawVert> *v9; // eax
  idDynamicBlock<idDrawVert> *v10; // ecx
  int v11; // edi
  const srfTriangles_s *v12; // esi
  int v13; // eax
  int v14; // ecx
  int numIndexes; // [esp-4h] [ebp-1Ch]
  int totalIndexes; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  v2 = 0;
  v3 = 0;
  for ( j = 0; j < numSurfaces; ++j )
  {
    v5 = surfaces[j];
    v2 += v5->numVerts;
    v3 += v5->numIndexes;
  }
  v6 = idBlockAlloc<srfTriangles_s,256,17>::Alloc(&srfTrianglesAllocator);
  v7 = 0;
  memset(v6, 0, sizeof(srfTriangles_s));
  v6->numIndexes = v3;
  v6->numVerts = v2;
  ++triVertexAllocator.numAllocs;
  v8 = 0;
  if ( v2 > 0 )
  {
    v9 = idDynamicBlockAlloc<idDrawVert,1048576,1024,17>::AllocInternal(&triVertexAllocator, v2);
    if ( v9 )
    {
      v10 = idDynamicBlockAlloc<idDrawVert,1048576,1024,17>::ResizeInternal(
              &triVertexAllocator,
              (idDynamicBlock<int> *)v9,
              v2);
      if ( v10 )
      {
        ++triVertexAllocator.numUsedBlocks;
        triVertexAllocator.usedBlockMemory += abs32(v10->size);
        v7 = (idDrawVert *)&v10[1];
      }
      else
      {
        v7 = 0;
      }
    }
    else
    {
      v7 = 0;
    }
  }
  numIndexes = v6->numIndexes;
  v6->verts = v7;
  v6->numAllocedVerts = v2;
  R_AllocStaticTriSurfIndexes(v6, numIndexes);
  v11 = 0;
  totalIndexes = 0;
  i = 0;
  if ( numSurfaces > 0 )
  {
    do
    {
      v12 = surfaces[v8];
      ((void (__stdcall *)(idDrawVert *, int))SIMDProcessor->Memcpy)(v12->verts, v12->numVerts << 6);
      v13 = 0;
      if ( v12->numIndexes > 0 )
      {
        v14 = totalIndexes;
        do
          v6->indexes[v14++] = v11 + v12->indexes[v13++];
        while ( v13 < v12->numIndexes );
        v8 = i;
      }
      v11 += v12->numVerts;
      totalIndexes += v12->numIndexes;
      i = ++v8;
    }
    while ( v8 < numSurfaces );
  }
  return v6;
}

// FUNC: struct srfTriangles_s * __cdecl R_MergeTriangles(struct srfTriangles_s const *,struct srfTriangles_s const *)
srfTriangles_s *__cdecl R_MergeTriangles(const srfTriangles_s *tri1, const srfTriangles_s *tri2)
{
  const srfTriangles_s *tris[2]; // [esp+0h] [ebp-8h] BYREF

  tris[0] = tri1;
  tris[1] = tri2;
  return R_MergeSurfaceList(tris, 2);
}

// FUNC: void __cdecl R_CopyAndReverseTriangles(struct srfTriangles_s *,struct srfTriangles_s * &)
void __cdecl R_CopyAndReverseTriangles(srfTriangles_s *src, srfTriangles_s **dst)
{
  srfTriangles_s *v2; // eax
  srfTriangles_s *v3; // edx
  srfTriangles_s *v4; // eax
  int v5; // ecx
  int v6; // edx
  idDrawVert *verts; // eax
  double v8; // st7
  float *p_x; // eax
  double v10; // st6
  double v11; // st7
  int i; // eax
  float v13; // [esp+14h] [ebp-4h]

  v2 = *dst;
  if ( *dst )
  {
    if ( v2->numVerts == src->numVerts && v2->numIndexes == src->numIndexes )
    {
      R_FreeStaticTriSurfVertexCaches(*dst);
      if ( *dst )
        goto LABEL_6;
    }
    else
    {
      R_FreeStaticTriSurf(*dst);
      *dst = 0;
    }
  }
  v3 = idBlockAlloc<srfTriangles_s,256,17>::Alloc(&srfTrianglesAllocator);
  memset(v3, 0, sizeof(srfTriangles_s));
  *dst = v3;
  v3->verts = 0;
  (*dst)->indexes = 0;
  R_AllocStaticTriSurfVerts(*dst, src->numVerts);
  R_AllocStaticTriSurfIndexes(*dst, src->numIndexes);
  (*dst)->numVerts = src->numVerts;
  (*dst)->numIndexes = src->numIndexes;
LABEL_6:
  v4 = *dst;
  v4->bounds.b[0].x = src->bounds.b[0].x;
  v4->bounds.b[0].y = src->bounds.b[0].y;
  v4->bounds.b[0].z = src->bounds.b[0].z;
  v4->bounds.b[1] = src->bounds.b[1];
  SIMDProcessor->Memcpy(SIMDProcessor, (*dst)->verts, src->verts, src->numVerts << 6);
  v5 = 0;
  if ( (*dst)->numVerts > 0 )
  {
    v6 = 0;
    do
    {
      verts = (*dst)->verts;
      v8 = vec3_origin.x - verts[v6].normal.x;
      p_x = &verts[v6].normal.x;
      ++v5;
      ++v6;
      v13 = vec3_origin.z - p_x[2];
      v10 = v8;
      v11 = vec3_origin.y - p_x[1];
      p_x[2] = v13;
      *p_x = v10;
      p_x[1] = v11;
    }
    while ( v5 < (*dst)->numVerts );
  }
  for ( i = 0; i < (*dst)->numIndexes; i += 3 )
  {
    (*dst)->indexes[i] = src->indexes[i + 1];
    (*dst)->indexes[i + 1] = src->indexes[i];
    (*dst)->indexes[i + 2] = src->indexes[i + 2];
  }
}

// FUNC: void __cdecl R_CleanupTriangles(struct srfTriangles_s *,bool,bool,bool,bool)
void __cdecl R_CleanupTriangles(
        srfTriangles_s *tri,
        bool createNormals,
        bool identifySilEdges,
        bool useUnsmoothedTangents)
{
  int *indexes; // ecx
  unsigned int v5; // edx

  R_RangeCheckIndexes(tri);
  R_CreateSilIndexes(tri);
  R_RemoveDegenerateTriangles(tri);
  if ( tri->numIndexes > 0 )
  {
    indexes = tri->indexes;
    v5 = (tri->numIndexes - 1) / 3u + 1;
    do
    {
      indexes += 3;
      --v5;
    }
    while ( v5 );
  }
  if ( identifySilEdges )
    R_IdentifySilEdges(tri);
  R_DuplicateMirroredVertexes(tri);
  R_CreateDupVerts(tri);
  (*(void (__fastcall **)(idSIMDProcessor *, srfTriangles_s *, idVec3 *, idDrawVert *, int))&SIMDProcessor->gap7C[12])(
    SIMDProcessor,
    tri,
    &tri->bounds.b[1],
    tri->verts,
    tri->numVerts);
  if ( useUnsmoothedTangents )
  {
    R_BuildDominantTris(tri);
    if ( !tri->tangentsCalculated )
    {
      SIMDProcessor->DeriveUnsmoothedTangents(SIMDProcessor, tri->verts, tri->dominantTris, tri->numVerts);
      tri->tangentsCalculated = 1;
    }
  }
  else if ( createNormals )
  {
    R_DeriveTangents(tri, 1);
  }
  else
  {
    R_DeriveFacePlanes(tri);
    R_DeriveTangentsWithoutNormals(tri);
  }
}

// FUNC: struct deformInfo_s * __cdecl R_BuildDeformInfo(int,class idDrawVert const *,int,int const *,bool)
deformInfo_s *__cdecl R_BuildDeformInfo(
        int numVerts,
        const idDrawVert *verts,
        int numIndexes,
        char *indexes,
        bool useUnsmoothedTangents)
{
  int v5; // edx
  int *v6; // eax
  int v7; // ecx
  _DWORD *v8; // eax
  int *v9; // ecx
  int *silIndexes; // edx
  _DWORD *v11; // esi
  int *dupVerts; // eax
  silEdge_t *silEdges; // ecx
  dominantTri_s *dominantTris; // edx
  idDrawVert *v15; // eax
  int *mirroredVerts; // ecx
  int numDupVerts; // edx
  srfTriangles_s tri; // [esp+10h] [ebp-B8h] BYREF

  memset(&tri, 0, sizeof(tri));
  tri.numVerts = numVerts;
  R_AllocStaticTriSurfVerts(&tri, numVerts);
  SIMDProcessor->Memcpy(SIMDProcessor, tri.verts, verts, tri.numVerts << 6);
  tri.numIndexes = numIndexes;
  R_AllocStaticTriSurfIndexes(&tri, numIndexes);
  v5 = tri.numIndexes;
  if ( tri.numIndexes > 0 )
  {
    v6 = tri.indexes;
    v7 = indexes - (char *)tri.indexes;
    do
    {
      *v6 = *(int *)((char *)v6 + v7);
      ++v6;
      --v5;
    }
    while ( v5 );
  }
  R_RangeCheckIndexes(&tri);
  R_CreateSilIndexes(&tri);
  R_IdentifySilEdges(&tri);
  R_DuplicateMirroredVertexes(&tri);
  R_CreateDupVerts(&tri);
  if ( useUnsmoothedTangents )
    R_BuildDominantTris(&tri);
  v8 = R_ClearedStaticAlloc(48);
  v9 = tri.indexes;
  silIndexes = tri.silIndexes;
  v11 = v8;
  v8[1] = tri.numVerts;
  v8[9] = tri.numSilEdges;
  v8[2] = tri.numMirroredVerts;
  dupVerts = tri.dupVerts;
  v11[5] = v9;
  silEdges = tri.silEdges;
  v11[6] = silIndexes;
  dominantTris = tri.dominantTris;
  v11[8] = dupVerts;
  v15 = tri.verts;
  v11[10] = silEdges;
  mirroredVerts = tri.mirroredVerts;
  v11[11] = dominantTris;
  numDupVerts = tri.numDupVerts;
  *v11 = numVerts;
  v11[4] = numIndexes;
  v11[3] = mirroredVerts;
  v11[7] = numDupVerts;
  if ( v15 )
  {
    ++triVertexAllocator.numFrees;
    --triVertexAllocator.numUsedBlocks;
    triVertexAllocator.usedBlockMemory -= abs32(LODWORD(v15[-1].tangents[1].y));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&triVertexAllocator,
      (idDynamicBlock<int> *)v15[-1].tangents);
  }
  if ( tri.facePlanes )
  {
    ++triPlaneAllocator.numFrees;
    --triPlaneAllocator.numUsedBlocks;
    triPlaneAllocator.usedBlockMemory -= abs32(LODWORD(tri.facePlanes[-1].a));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&triPlaneAllocator,
      (idDynamicBlock<int> *)&tri.facePlanes[-2]);
  }
  return (deformInfo_s *)v11;
}

// FUNC: void __cdecl R_SimpleCleanupTriangles(struct srfTriangles_s *)
void __cdecl R_SimpleCleanupTriangles(srfTriangles_s *tri)
{
  int *silIndexes; // eax

  R_RangeCheckIndexes(tri);
  R_CreateSilIndexes(tri);
  R_RemoveDegenerateTriangles(tri);
  silIndexes = tri->silIndexes;
  ++triSilIndexAllocator.numFrees;
  if ( silIndexes )
  {
    --triSilIndexAllocator.numUsedBlocks;
    triSilIndexAllocator.usedBlockMemory -= abs32(*(silIndexes - 4));
    idDynamicBlockAlloc<dominantTri_s,65536,1024,17>::FreeInternal(
      (idDynamicBlockAlloc<int,65536,1024,17> *)&triSilIndexAllocator,
      (idDynamicBlock<int> *)silIndexes - 1);
  }
  tri->silIndexes = 0;
}

// FUNC: struct srfTriangles_s * __cdecl R_CopyStaticTriSurf(struct srfTriangles_s const *)
srfTriangles_s *__cdecl R_CopyStaticTriSurf(const srfTriangles_s *tri)
{
  srfTriangles_s *v1; // esi

  v1 = idBlockAlloc<srfTriangles_s,256,17>::Alloc(&srfTrianglesAllocator);
  memset(v1, 0, sizeof(srfTriangles_s));
  R_AllocStaticTriSurfVerts(v1, tri->numVerts);
  R_AllocStaticTriSurfIndexes(v1, tri->numIndexes);
  v1->numVerts = tri->numVerts;
  v1->numIndexes = tri->numIndexes;
  SIMDProcessor->Memcpy(SIMDProcessor, v1->verts, tri->verts, tri->numVerts << 6);
  SIMDProcessor->Memcpy(SIMDProcessor, v1->indexes, tri->indexes, 4 * tri->numIndexes);
  return v1;
}
