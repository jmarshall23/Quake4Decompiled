
// FUNC: int __cdecl R_WindingFromTriangles(struct srfTriangles_s const *,int * const)
int __cdecl R_WindingFromTriangles(const srfTriangles_s *tri, int *indexes)
{
  int *v2; // esi
  int v3; // ebp
  int v4; // ecx
  int v5; // edi
  int *v6; // eax
  int v7; // edx
  int k; // eax
  int v9; // ebx
  int v10; // edi
  int *v11; // esi
  int m; // ecx
  bool v13; // zf
  int v15; // [esp+10h] [ebp-28h]
  int i; // [esp+14h] [ebp-24h]
  int *v17; // [esp+18h] [ebp-20h]
  int *v18; // [esp+1Ch] [ebp-1Ch]
  int numIndexes; // [esp+20h] [ebp-18h]
  int j; // [esp+24h] [ebp-14h]
  int v21; // [esp+28h] [ebp-10h]
  int next; // [esp+2Ch] [ebp-Ch]
  int numTris; // [esp+30h] [ebp-8h]
  int *v24; // [esp+34h] [ebp-4h]

  v2 = indexes;
  *indexes = *tri->indexes;
  v3 = 1;
  v4 = tri->numIndexes / 3;
  numIndexes = 1;
  numTris = v4;
  do
  {
    i = 0;
    if ( v4 <= 0 )
      continue;
    v15 = 0;
    do
    {
      v21 = v2[v3 - 1];
      v17 = tri->indexes;
      v5 = 0;
      v6 = &v17[v15];
      j = 0;
      v24 = v6;
      while ( 1 )
      {
        if ( *v6 != v21 )
          goto LABEL_22;
        v7 = v17[v15 + (v5 + 1) % 3];
        next = v7;
        if ( v3 != 1 )
          break;
        if ( v7 != *v2 )
          goto LABEL_13;
LABEL_22:
        ++v5;
        v6 = v24 + 1;
        j = v5;
        ++v24;
        if ( v5 >= 3 )
          goto LABEL_25;
      }
      for ( k = 1; k < v3; ++k )
      {
        if ( v2[k] == v7 )
          break;
      }
      if ( k != v3 )
        goto LABEL_22;
LABEL_13:
      v9 = 0;
      v10 = 0;
      v18 = tri->indexes;
      do
      {
        if ( v9 != i )
        {
          v11 = v18;
          for ( m = 0; m < 3; ++m )
          {
            if ( *v11 == v7 )
            {
              v7 = next;
              v3 = numIndexes;
              if ( v17[v10 + (m + 1) % 3] == v21 )
                break;
            }
            ++v11;
          }
          v2 = indexes;
          v13 = m == 3;
          v4 = numTris;
          if ( !v13 )
            break;
        }
        v18 += 3;
        ++v9;
        v10 += 3;
      }
      while ( v9 < v4 );
      v5 = j;
      if ( v9 != v4 )
        goto LABEL_22;
      v2[v3++] = v7;
      numIndexes = v3;
LABEL_25:
      if ( v5 != 3 )
        break;
      v15 += 3;
      ++i;
    }
    while ( i < v4 );
  }
  while ( v3 != tri->numVerts && i != v4 );
  return v3;
}

// FUNC: R_SpriteDeform
void __cdecl R_SpriteDeform(drawSurf_s *surf, bool radiusDimension)
{
  const srfTriangles_s *geo; // edi
  int numVerts; // eax
  srfTriangles_s *v4; // esi
  int numIndexes; // edi
  int v6; // eax
  void *v7; // esp
  int v8; // ebx
  idDrawVert *v9; // edi
  bool v10; // cc
  int v11; // edx
  int v12; // ecx
  float *p_z; // eax
  rvSilTraceVertT *silTraceVerts; // edi
  float *p_y; // ecx
  double v16; // st7
  float *v17; // ecx
  double v18; // st4
  long double v19; // st7
  double v20; // st7
  double v21; // st6
  double z; // st5
  double v23; // st6
  double v24; // st5
  long double v25; // st6
  float *v26; // edi
  double v27; // st6
  double v28; // st5
  double v29; // st3
  double v30; // st4
  double v31; // st3
  double v32; // st4
  double v33; // st3
  double v34; // st5
  double v35; // st4
  double v36; // st2
  double v37; // st7
  double v38; // st6
  double v39; // st5
  double v40; // st4
  double v41; // st3
  double v42; // st2
  double v43; // st4
  double x; // st4
  double v45; // st4
  double v46; // st3
  double v47; // st1
  double v48; // st2
  double v49; // st3
  double v50; // st4
  double v51; // st6
  double v52; // st5
  int v53; // ecx
  int v54; // edi
  vertCache_s *v55; // eax
  _BYTE v56[12]; // [esp+8h] [ebp-50h] BYREF
  float v57; // [esp+14h] [ebp-44h]
  float v58; // [esp+20h] [ebp-38h]
  float v59; // [esp+2Ch] [ebp-2Ch]
  float v60; // [esp+38h] [ebp-20h]
  float v61; // [esp+3Ch] [ebp-1Ch]
  float v62; // [esp+40h] [ebp-18h]
  idVec3 upDir; // [esp+48h] [ebp-10h] BYREF
  idDrawVert *ac; // [esp+54h] [ebp-4h]
  float v65; // [esp+58h] [ebp+0h]
  float v66; // [esp+5Ch] [ebp+4h]
  float v67; // [esp+60h] [ebp+8h]
  float v68; // [esp+64h] [ebp+Ch]
  float v69; // [esp+68h] [ebp+10h]
  float v70; // [esp+6Ch] [ebp+14h]
  int j; // [esp+70h] [ebp+18h]
  float v72; // [esp+74h] [ebp+1Ch]
  float v73; // [esp+78h] [ebp+20h]
  float v74; // [esp+7Ch] [ebp+24h]
  float v75; // [esp+80h] [ebp+28h]
  float v76; // [esp+84h] [ebp+2Ch]
  float v77; // [esp+88h] [ebp+30h]
  idVec3 leftDir; // [esp+8Ch] [ebp+34h] BYREF
  float v79; // [esp+98h] [ebp+40h]
  float v80; // [esp+9Ch] [ebp+44h]
  float xy[2]; // [esp+A4h] [ebp+4Ch]
  float v82; // [esp+ACh] [ebp+54h]
  const srfTriangles_s *tri; // [esp+B0h] [ebp+58h]
  int i; // [esp+B4h] [ebp+5Ch]
  idVec3 mid; // [esp+B8h] [ebp+60h]
  float v86; // [esp+C4h] [ebp+6Ch]

  geo = surf->geo;
  numVerts = surf->geo->numVerts;
  tri = surf->geo;
  if ( (numVerts & 3) != 0 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "R_AutospriteDeform: shader had odd vertex count");
    return;
  }
  if ( geo->numIndexes != 6 * (numVerts >> 2) )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "R_AutospriteDeform: autosprite had odd index count");
    return;
  }
  R_GlobalVectorToLocal(surf->space->modelMatrix, &tr.viewDef->renderView.viewaxis.mat[1], &leftDir);
  R_GlobalVectorToLocal(surf->space->modelMatrix, &tr.viewDef->renderView.viewaxis.mat[2], &upDir);
  if ( tr.viewDef->isMirror )
  {
    v67 = vec3_origin.z - leftDir.z;
    leftDir.z = v67;
    leftDir.x = vec3_origin.x - leftDir.x;
    leftDir.y = vec3_origin.y - leftDir.y;
  }
  v4 = (srfTriangles_s *)R_ClearedFrameAlloc(180);
  v4->numVerts = geo->numVerts;
  numIndexes = geo->numIndexes;
  v4->numIndexes = numIndexes;
  v4->indexes = (int *)R_FrameAlloc(4 * numIndexes);
  v6 = (v4->numVerts << 6) + 18;
  LOBYTE(v6) = v6 & 0xFC;
  v7 = alloca(v6);
  v8 = 0;
  v9 = (idDrawVert *)v56;
  v10 = tri->numVerts <= 0;
  ac = (idDrawVert *)v56;
  i = 0;
  if ( !v10 )
  {
    v11 = 0;
    v12 = -72 - (_DWORD)v56;
    p_z = &upDir.z;
    for ( j = -72 - (_DWORD)v56; ; v12 = j )
    {
      silTraceVerts = tri->silTraceVerts;
      if ( silTraceVerts )
      {
        p_y = &silTraceVerts[v11].xyzw.y;
        v86 = *(float *)&p_y;
        if ( radiusDimension )
        {
          mid.x = (silTraceVerts[v11 + 3].xyzw.x
                 + silTraceVerts[v11 + 2].xyzw.x
                 + silTraceVerts[v11 + 1].xyzw.x
                 + silTraceVerts[v11].xyzw.x)
                * 0.25;
          v16 = silTraceVerts[v11 + 3].xyzw.y + silTraceVerts[v11 + 2].xyzw.y + silTraceVerts[v11 + 1].xyzw.y + *p_y;
          v17 = &silTraceVerts[v11].xyzw.z;
          mid.y = v16 * 0.25;
          mid.z = (silTraceVerts[v11 + 3].xyzw.z + silTraceVerts[v11 + 2].xyzw.z + silTraceVerts[v11 + 1].xyzw.z + *v17)
                * 0.25;
          v18 = *v17 - mid.z;
          v19 = sqrt(
                  (silTraceVerts[v11].xyzw.x - mid.x) * (silTraceVerts[v11].xyzw.x - mid.x)
                + v18 * v18
                + (*(float *)LODWORD(v86) - mid.y) * (*(float *)LODWORD(v86) - mid.y))
              * 0.707;
          xy[1] = v19;
          goto LABEL_18;
        }
        v20 = silTraceVerts[v11 + 2].xyzw.x - silTraceVerts[v11].xyzw.x;
        v21 = silTraceVerts[v11 + 2].xyzw.y - *p_y;
        z = silTraceVerts[v11 + 2].xyzw.z;
        LODWORD(v82) = &silTraceVerts[v11].xyzw.z;
        v19 = sqrt(v20 * v20 + (z - *(float *)LODWORD(v82)) * (z - *(float *)LODWORD(v82)) + v21 * v21) * 0.5;
        v23 = silTraceVerts[v11 + 1].xyzw.x - silTraceVerts[v11].xyzw.x;
        v24 = silTraceVerts[v11 + 1].xyzw.y - *(float *)LODWORD(v86);
        v25 = sqrt(
                v23 * v23
              + (silTraceVerts[v11 + 1].xyzw.z - *(float *)LODWORD(v82))
              * (silTraceVerts[v11 + 1].xyzw.z - *(float *)LODWORD(v82))
              + v24 * v24);
      }
      else
      {
        v26 = (float *)((char *)p_z + (unsigned int)tri->verts + v12);
        if ( radiusDimension )
        {
          mid.x = (v26[48] + v26[32] + v26[16] + *v26) * 0.25;
          mid.y = (v26[49] + v26[33] + v26[17] + v26[1]) * 0.25;
          mid.z = (v26[50] + v26[34] + v26[18] + v26[2]) * 0.25;
          v27 = v26[1] - mid.y;
          v28 = v26[2] - mid.z;
          v29 = *v26 - mid.x;
          v19 = sqrt(v28 * v28 + v27 * v27 + v29 * v29) * 0.707;
          xy[1] = v19;
          goto LABEL_18;
        }
        v30 = v26[34] - v26[2];
        v31 = v26[33] - v26[1];
        v32 = v30 * v30 + v31 * v31;
        v33 = v26[32] - *v26;
        v19 = sqrt(v32 + v33 * v33) * 0.5;
        v34 = v26[17] - v26[1];
        v35 = v26[18] - v26[2];
        v36 = v26[16] - *v26;
        v25 = sqrt(v35 * v35 + v34 * v34 + v36 * v36);
      }
      xy[1] = v25 * 0.5;
LABEL_18:
      v75 = leftDir.x * v19;
      v76 = leftDir.y * v19;
      v77 = leftDir.z * v19;
      v79 = upDir.x * xy[1];
      v80 = upDir.y * xy[1];
      v37 = upDir.z * xy[1];
      v38 = v75 + mid.x;
      v61 = v38;
      v39 = v76 + mid.y;
      v62 = v39;
      v40 = v77 + mid.z;
      v86 = v40;
      v41 = v61 + v79;
      v42 = v40;
      v43 = v62 + v80;
      v58 = v42 + v37;
      *(p_z - 16) = v58;
      *(p_z - 18) = v41;
      *(p_z - 17) = v43;
      *(p_z - 4) = 0.0;
      x = mid.x;
      *(p_z - 3) = 0.0;
      v45 = x - v75;
      v72 = v45;
      v46 = mid.y - v76;
      v73 = v46;
      v82 = mid.z - v77;
      v74 = v82;
      v60 = v82 + v37;
      v47 = v72 + v79;
      v48 = v73 + v80;
      *p_z = v60;
      *(p_z - 2) = v47;
      *(p_z - 1) = v48;
      p_z[12] = 1.0;
      p_z[13] = 0.0;
      v65 = v45;
      v66 = v46;
      v49 = v65 - v79;
      v50 = v66 - v80;
      v59 = v82 - v37;
      p_z[16] = v59;
      p_z[14] = v49;
      p_z[15] = v50;
      p_z[28] = 1.0;
      p_z[29] = 1.0;
      v68 = v38;
      v69 = v39;
      v70 = v86;
      v11 += 4;
      v51 = v68 - v79;
      p_z += 64;
      v52 = v69 - v80;
      v57 = v86 - v37;
      *(p_z - 32) = v57;
      *(p_z - 34) = v51;
      *(p_z - 33) = v52;
      *(p_z - 20) = 0.0;
      *(p_z - 19) = 1.0;
      v53 = 6 * (v8 >> 2);
      v4->indexes[v53] = v8;
      v4->indexes[v53 + 1] = v8 + 1;
      v4->indexes[v53 + 2] = i + 2;
      v54 = i;
      v4->indexes[v53 + 3] = i;
      v54 += 2;
      v4->indexes[v53 + 4] = v54;
      v4->indexes[v53 + 5] = v54 + 1;
      v8 = i + 4;
      v10 = i + 4 < tri->numVerts;
      i += 4;
      if ( !v10 )
      {
        v9 = ac;
        break;
      }
    }
  }
  if ( surf->material->numAmbientStages != surf->material->numStages )
  {
    v4->verts = v9;
    R_DeriveTangents(v4, 0);
    v4->verts = 0;
  }
  v55 = idVertexCache::AllocFrameTemp(&vertexCache, v9, v4->numVerts << 6, 2u);
  v4->ambientCache = v55;
  if ( v55 )
    surf->geo = v4;
  if ( r_useIndexBuffers.internalVar->integerValue )
    v4->indexCache = idVertexCache::AllocFrameTemp(&vertexCache, v4->indexes, 4 * v4->numIndexes, 1u);
}

// FUNC: R_ExpandDeform
void __cdecl R_ExpandDeform(drawSurf_s *surf)
{
  const srfTriangles_s *geo; // edi
  srfTriangles_s *v2; // eax
  srfTriangles_s *v3; // esi
  int m_numDrawIndices; // eax
  int v5; // eax
  void *v6; // esp
  idDrawVert *v7; // ebx
  drawSurf_s *v8; // edi
  int v9; // ecx
  float *v10; // eax
  double v11; // st7
  double v12; // st7
  double v13; // st6
  int numVerts; // eax
  int v15; // eax
  void *v16; // esp
  const float *shaderRegisters; // edx
  idDrawVert *v18; // eax
  bool v19; // cc
  idDrawVert *verts; // edx
  double v21; // st7
  float *p_x; // eax
  double v23; // st6
  double v24; // st7
  double v25; // st6
  int v26; // eax
  vertCache_s *v27; // eax
  _BYTE v28[11]; // [esp+4h] [ebp-30h] BYREF
  _BYTE v29[5]; // [esp+Fh] [ebp-25h] BYREF
  float v30; // [esp+14h] [ebp-20h]
  float v31; // [esp+1Ch] [ebp-18h] BYREF
  float v32; // [esp+20h] [ebp-14h]
  int i; // [esp+24h] [ebp-10h]
  idDrawVert *ac; // [esp+28h] [ebp-Ch]
  unsigned int v35; // [esp+2Ch] [ebp-8h]
  float v36; // [esp+30h] [ebp-4h]
  float dist; // [esp+3Ch] [ebp+8h]

  geo = surf->geo;
  v2 = (srfTriangles_s *)R_ClearedFrameAlloc(180);
  v3 = v2;
  if ( geo->primBatchMesh )
  {
    v2->numVerts = geo->primBatchMesh->m_numDrawVertices;
    m_numDrawIndices = geo->primBatchMesh->m_numDrawIndices;
    v3->numIndexes = m_numDrawIndices;
    i = (int)R_FrameAlloc(4 * m_numDrawIndices);
    v3->indexes = (int *)i;
    v5 = (v3->numVerts << 6) + 18;
    LOBYTE(v5) = v5 & 0xFC;
    v6 = alloca(v5);
    v7 = (idDrawVert *)v28;
    rvMesh::CopyTriangles(geo->primBatchMesh, (idDrawVert *)v28, (int *)i, geo->silTraceVerts);
    v3->verts = (idDrawVert *)v28;
    R_DeriveTangents(v3, 0);
    v8 = surf;
    v3->verts = 0;
    v9 = 0;
    dist = surf->shaderRegisters[surf->material->deformRegisters[0]];
    if ( v3->numVerts > 0 )
    {
      v10 = &v31;
      do
      {
        ++v9;
        v11 = dist * *(v10 - 2);
        v10 += 16;
        v31 = dist * *(v10 - 17);
        v32 = dist * *(v10 - 16);
        v12 = v11 + *(v10 - 22);
        v13 = v31 + *(v10 - 21);
        v30 = v32 + *(v10 - 20);
        *(v10 - 20) = v30;
        *(v10 - 22) = v12;
        *(v10 - 21) = v13;
      }
      while ( v9 < v3->numVerts );
    }
  }
  else
  {
    numVerts = geo->numVerts;
    v3->numVerts = numVerts;
    v15 = (numVerts << 6) + 18;
    LOBYTE(v15) = v15 & 0xFC;
    v3->numIndexes = geo->numIndexes;
    v3->indexes = geo->indexes;
    v16 = alloca(v15);
    shaderRegisters = surf->shaderRegisters;
    v18 = (idDrawVert *)v29;
    LOBYTE(v18) = (unsigned __int8)v29 & 0xF0;
    ac = v18;
    v7 = v18;
    v36 = shaderRegisters[surf->material->deformRegisters[0]];
    v19 = geo->numVerts <= 0;
    i = 0;
    if ( !v19 )
    {
      v35 = 0;
      do
      {
        idDrawVert::operator=(&geo->verts[v35 / 0x40]);
        verts = geo->verts;
        v21 = v36 * verts[v35 / 0x40].normal.x;
        p_x = &verts[v35 / 0x40].xyz.x;
        v23 = v36 * verts[v35 / 0x40].normal.y;
        ++v7;
        v35 += 64;
        v31 = v23;
        v32 = v36 * p_x[6];
        v24 = v21 + *p_x;
        v25 = v31 + p_x[1];
        v30 = v32 + p_x[2];
        v7[-1].xyz.z = v30;
        v26 = i;
        v7[-1].xyz.x = v24;
        ++v26;
        v7[-1].xyz.y = v25;
        v19 = v26 < geo->numVerts;
        i = v26;
      }
      while ( v19 );
      v7 = ac;
    }
    v8 = surf;
  }
  if ( v8->material->numAmbientStages != v8->material->numStages )
  {
    v3->verts = v7;
    R_DeriveTangents(v3, 0);
    v3->verts = 0;
  }
  v27 = idVertexCache::AllocFrameTemp(&vertexCache, v7, v3->numVerts << 6, 2u);
  v3->ambientCache = v27;
  if ( v27 )
    v8->geo = v3;
  if ( r_useIndexBuffers.internalVar->integerValue )
    v3->indexCache = idVertexCache::AllocFrameTemp(&vertexCache, v3->indexes, 4 * v3->numIndexes, 1u);
}

// FUNC: R_MoveDeform
void __cdecl R_MoveDeform(drawSurf_s *surf)
{
  const srfTriangles_s *geo; // esi
  srfTriangles_s *v2; // eax
  srfTriangles_s *v3; // edi
  int m_numDrawIndices; // eax
  int v5; // eax
  void *v6; // esp
  int v7; // ecx
  bool v8; // cc
  float *v9; // eax
  double v10; // st7
  int numVerts; // ecx
  int v12; // eax
  void *v13; // esp
  int v14; // eax
  double v15; // st7
  float v16; // ecx
  vertCache_s *v17; // eax
  _BYTE v18[8]; // [esp+4h] [ebp-18h] BYREF
  float v19; // [esp+Ch] [ebp-10h]
  float dist; // [esp+10h] [ebp-Ch]
  float *v21; // [esp+14h] [ebp-8h]
  unsigned int v22; // [esp+18h] [ebp-4h]

  geo = surf->geo;
  v2 = (srfTriangles_s *)R_ClearedFrameAlloc(180);
  v3 = v2;
  if ( geo->primBatchMesh )
  {
    v2->numVerts = geo->primBatchMesh->m_numDrawVertices;
    m_numDrawIndices = geo->primBatchMesh->m_numDrawIndices;
    v3->numIndexes = m_numDrawIndices;
    dist = COERCE_FLOAT(R_FrameAlloc(4 * m_numDrawIndices));
    *(float *)&v3->indexes = dist;
    v5 = (v3->numVerts << 6) + 18;
    LOBYTE(v5) = v5 & 0xFC;
    v6 = alloca(v5);
    rvMesh::CopyTriangles(geo->primBatchMesh, (idDrawVert *)v18, (int *)LODWORD(dist), geo->silTraceVerts);
    v7 = 0;
    v8 = geo->numVerts <= 0;
    dist = surf->shaderRegisters[surf->material->deformRegisters[0]];
    if ( !v8 )
    {
      v9 = (float *)v18;
      do
      {
        ++v7;
        v10 = dist + *v9;
        v9 += 16;
        *(v9 - 16) = v10;
      }
      while ( v7 < geo->numVerts );
    }
  }
  else
  {
    numVerts = geo->numVerts;
    v2->numVerts = numVerts;
    v2->numIndexes = geo->numIndexes;
    v2->indexes = geo->indexes;
    v12 = (numVerts << 6) + 18;
    LOBYTE(v12) = v12 & 0xFC;
    v13 = alloca(v12);
    v19 = surf->shaderRegisters[surf->material->deformRegisters[0]];
    v8 = geo->numVerts <= 0;
    dist = 0.0;
    if ( !v8 )
    {
      v22 = 0;
      v21 = (float *)v18;
      do
      {
        idDrawVert::operator=(&geo->verts[v22 / 0x40]);
        v14 = (int)v21;
        v15 = v19 + *v21;
        v22 += 64;
        LODWORD(v16) = LODWORD(dist) + 1;
        *v21 = v15;
        v8 = SLODWORD(v16) < geo->numVerts;
        dist = v16;
        v21 = (float *)(v14 + 64);
      }
      while ( v8 );
    }
  }
  if ( surf->material->numAmbientStages != surf->material->numStages )
  {
    v3->verts = (idDrawVert *)v18;
    R_DeriveTangents(v3, 0);
    v3->verts = 0;
  }
  v17 = idVertexCache::AllocFrameTemp(&vertexCache, v18, v3->numVerts << 6, 2u);
  v3->ambientCache = v17;
  if ( v17 )
    surf->geo = v3;
  if ( r_useIndexBuffers.internalVar->integerValue )
    v3->indexCache = idVertexCache::AllocFrameTemp(&vertexCache, v3->indexes, 4 * v3->numIndexes, 1u);
}

// FUNC: R_TurbulentDeform
void __cdecl R_TurbulentDeform(drawSurf_s *surf)
{
  const srfTriangles_s *geo; // esi
  srfTriangles_s *v2; // eax
  const float *shaderRegisters; // ecx
  srfTriangles_s *v4; // edi
  const idMaterial *material; // eax
  int v6; // edx
  const idDecl *deformDecl; // ebx
  int v8; // eax
  bool v9; // zf
  int m_numDrawIndices; // eax
  int v11; // eax
  void *v12; // esp
  idDrawVert *v13; // eax
  rvMesh *primBatchMesh; // ecx
  bool v15; // cc
  idVec2 *p_st; // edi
  idDecl_vtbl *v17; // edx
  double v18; // st7
  double v19; // st7
  int v20; // eax
  double v21; // st7
  int numVerts; // eax
  int v23; // eax
  void *v24; // esp
  idDrawVert *v25; // eax
  idDrawVert *v26; // ecx
  int v27; // eax
  float *p_y; // edi
  idDrawVert *verts; // ecx
  int v30; // eax
  double v31; // st7
  double v32; // st7
  int v33; // eax
  double v34; // st7
  vertCache_s *v35; // eax
  const rvSilTraceVertT *silTraceVerts; // [esp+4h] [ebp-30h]
  float v37; // [esp+4h] [ebp-30h]
  float v38; // [esp+4h] [ebp-30h]
  int j; // [esp+14h] [ebp-20h] BYREF
  srfTriangles_s *newTri; // [esp+18h] [ebp-1Ch]
  float domain; // [esp+1Ch] [ebp-18h]
  float f; // [esp+20h] [ebp-14h]
  float range; // [esp+24h] [ebp-10h]
  float timeOfs; // [esp+28h] [ebp-Ch]
  idDrawVert *ac; // [esp+2Ch] [ebp-8h]
  int i; // [esp+30h] [ebp-4h]

  geo = surf->geo;
  v2 = (srfTriangles_s *)R_ClearedFrameAlloc(180);
  shaderRegisters = surf->shaderRegisters;
  v4 = v2;
  material = surf->material;
  v6 = material->deformRegisters[1];
  deformDecl = material->deformDecl;
  range = shaderRegisters[material->deformRegisters[0]];
  v8 = material->deformRegisters[2];
  timeOfs = shaderRegisters[v6];
  v9 = geo->primBatchMesh == 0;
  domain = shaderRegisters[v8];
  newTri = v4;
  if ( v9 )
  {
    numVerts = geo->numVerts;
    v4->numVerts = numVerts;
    v23 = (numVerts << 6) + 18;
    LOBYTE(v23) = v23 & 0xFC;
    v4->numIndexes = geo->numIndexes;
    v4->indexes = geo->indexes;
    v24 = alloca(v23);
    v25 = (idDrawVert *)((char *)&j + 3);
    LOBYTE(v25) = ((unsigned __int8)&j + 3) & 0xF0;
    v15 = geo->numVerts <= 0;
    i = 0;
    ac = v25;
    if ( v15 )
      goto LABEL_11;
    v26 = v25;
    v27 = -60 - (_DWORD)v25;
    p_y = &v26->st.y;
    for ( j = v27; ; v27 = j )
    {
      verts = geo->verts;
      v30 = (int)p_y + v27;
      f = (*(float *)((char *)&verts->xyz.y + v30) * 0.007
         + *(float *)((char *)&verts->xyz.z + v30) * 0.011
         + *(float *)((char *)&verts->xyz.x + v30) * 0.003)
        * domain
        + timeOfs
        + timeOfs;
      idDrawVert::operator=((char *)verts + v30);
      v31 = ((double (__thiscall *)(const idDecl *, _DWORD))deformDecl->__vftable[1].~idDecl)(deformDecl, LODWORD(f));
      *(p_y - 1) = v31 * range + *(p_y - 1);
      v38 = f + 0.5;
      v32 = ((double (__thiscall *)(const idDecl *, _DWORD))deformDecl->__vftable[1].~idDecl)(deformDecl, LODWORD(v38));
      p_y += 16;
      v34 = v32 * range + *(p_y - 16);
      v33 = ++i;
      *(p_y - 16) = v34;
      if ( v33 >= geo->numVerts )
        break;
    }
  }
  else
  {
    v4->numVerts = geo->primBatchMesh->m_numDrawVertices;
    m_numDrawIndices = geo->primBatchMesh->m_numDrawIndices;
    v4->numIndexes = m_numDrawIndices;
    f = COERCE_FLOAT(R_FrameAlloc(4 * m_numDrawIndices));
    *(float *)&v4->indexes = f;
    v11 = (v4->numVerts << 6) + 18;
    LOBYTE(v11) = v11 & 0xFC;
    v12 = alloca(v11);
    v13 = (idDrawVert *)((char *)&j + 3);
    LOBYTE(v13) = ((unsigned __int8)&j + 3) & 0xF0;
    silTraceVerts = geo->silTraceVerts;
    primBatchMesh = geo->primBatchMesh;
    ac = v13;
    rvMesh::CopyTriangles(primBatchMesh, v13, (int *)LODWORD(f), silTraceVerts);
    v15 = geo->numVerts <= 0;
    i = 0;
    if ( v15 )
      goto LABEL_11;
    p_st = &ac->st;
    do
    {
      v17 = deformDecl->__vftable;
      f = (p_st[-7].x * 0.003 + p_st[-6].x * 0.011 + p_st[-7].y * 0.007) * domain + timeOfs + timeOfs;
      v18 = ((double (__thiscall *)(const idDecl *, _DWORD))v17[1].~idDecl)(deformDecl, LODWORD(f));
      p_st->x = v18 * range + p_st->x;
      v37 = f + 0.5;
      v19 = ((double (__thiscall *)(const idDecl *, _DWORD))deformDecl->__vftable[1].~idDecl)(deformDecl, LODWORD(v37));
      p_st += 8;
      v21 = v19 * range + p_st[-8].y;
      v20 = ++i;
      p_st[-8].y = v21;
    }
    while ( v20 < geo->numVerts );
  }
  v4 = newTri;
LABEL_11:
  if ( surf->material->numAmbientStages != surf->material->numStages )
  {
    v4->verts = ac;
    R_DeriveTangents(v4, 0);
    v4->verts = 0;
  }
  v35 = idVertexCache::AllocFrameTemp(&vertexCache, ac, v4->numVerts << 6, 2u);
  v4->ambientCache = v35;
  if ( v35 )
    surf->geo = v4;
  if ( r_useIndexBuffers.internalVar->integerValue )
    v4->indexCache = idVertexCache::AllocFrameTemp(&vertexCache, v4->indexes, 4 * v4->numIndexes, 1u);
}

// FUNC: AddTriangleToIsland_r
void __cdecl AddTriangleToIsland_r(const srfTriangles_s *tri, int triangleNum, bool *usedList, eyeIsland_t *island)
{
  const srfTriangles_s *v5; // ebp
  int *indexes; // ecx
  int v7; // edx
  int v8; // edi
  idDrawVert *v9; // ecx
  idDrawVert *v10; // ecx
  idDrawVert *v11; // ecx
  int v12; // ebx
  int v13; // edi
  int *v14; // edx
  eyeIsland_t *v15; // ecx
  int *v16; // eax
  eyeIsland_t *v17; // edx
  eyeIsland_t *v18; // eax
  int b; // [esp+10h] [ebp-8h]
  int c; // [esp+14h] [ebp-4h]
  int triangleNuma; // [esp+20h] [ebp+8h]
  eyeIsland_t *islanda; // [esp+28h] [ebp+10h]

  usedList[triangleNum] = 1;
  if ( island->numTris == 10 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(common.type, "MAX_EYEBALL_TRIS");
  v5 = tri;
  island->tris[island->numTris++] = triangleNum;
  indexes = tri->indexes;
  v7 = indexes[3 * triangleNum + 1];
  v8 = indexes[3 * triangleNum + 2];
  islanda = (eyeIsland_t *)indexes[3 * triangleNum];
  v9 = &tri->verts[(_DWORD)islanda];
  b = v7;
  c = v8;
  if ( v9->xyz.x < (double)island->bounds.b[0].x )
    island->bounds.b[0].x = v9->xyz.x;
  if ( v9->xyz.x > (double)island->bounds.b[1].x )
    island->bounds.b[1].x = v9->xyz.x;
  if ( v9->xyz.y < (double)island->bounds.b[0].y )
    island->bounds.b[0].y = v9->xyz.y;
  if ( v9->xyz.y > (double)island->bounds.b[1].y )
    island->bounds.b[1].y = v9->xyz.y;
  if ( v9->xyz.z < (double)island->bounds.b[0].z )
    island->bounds.b[0].z = v9->xyz.z;
  if ( v9->xyz.z > (double)island->bounds.b[1].z )
    island->bounds.b[1].z = v9->xyz.z;
  v10 = &tri->verts[v7];
  if ( v10->xyz.x < (double)island->bounds.b[0].x )
    island->bounds.b[0].x = v10->xyz.x;
  if ( v10->xyz.x > (double)island->bounds.b[1].x )
    island->bounds.b[1].x = v10->xyz.x;
  if ( v10->xyz.y < (double)island->bounds.b[0].y )
    island->bounds.b[0].y = v10->xyz.y;
  if ( v10->xyz.y > (double)island->bounds.b[1].y )
    island->bounds.b[1].y = v10->xyz.y;
  if ( v10->xyz.z < (double)island->bounds.b[0].z )
    island->bounds.b[0].z = v10->xyz.z;
  if ( v10->xyz.z > (double)island->bounds.b[1].z )
    island->bounds.b[1].z = v10->xyz.z;
  v11 = &tri->verts[v8];
  if ( v11->xyz.x < (double)island->bounds.b[0].x )
    island->bounds.b[0].x = v11->xyz.x;
  if ( v11->xyz.x > (double)island->bounds.b[1].x )
    island->bounds.b[1].x = v11->xyz.x;
  if ( v11->xyz.y < (double)island->bounds.b[0].y )
    island->bounds.b[0].y = v11->xyz.y;
  if ( v11->xyz.y > (double)island->bounds.b[1].y )
    island->bounds.b[1].y = v11->xyz.y;
  if ( v11->xyz.z < (double)island->bounds.b[0].z )
    island->bounds.b[0].z = v11->xyz.z;
  if ( v11->xyz.z > (double)island->bounds.b[1].z )
    island->bounds.b[1].z = v11->xyz.z;
  v12 = tri->numIndexes / 3;
  v13 = 0;
  if ( v12 > 0 )
  {
    triangleNuma = 0;
    do
    {
      if ( !usedList[v13] )
      {
        v14 = v5->indexes;
        v15 = (eyeIsland_t *)v14[triangleNuma];
        v16 = &v14[triangleNuma];
        if ( v15 != islanda )
        {
          v17 = (eyeIsland_t *)v16[1];
          if ( v17 != islanda )
          {
            v18 = (eyeIsland_t *)v16[2];
            if ( v18 != islanda
              && v15 != (eyeIsland_t *)b
              && v17 != (eyeIsland_t *)b
              && v18 != (eyeIsland_t *)b
              && v15 != (eyeIsland_t *)c
              && v17 != (eyeIsland_t *)c
              && v18 != (eyeIsland_t *)c )
            {
              v5 = tri;
              goto LABEL_54;
            }
          }
          v5 = tri;
        }
        AddTriangleToIsland_r(v5, v13, usedList, island);
      }
LABEL_54:
      triangleNuma += 3;
      ++v13;
    }
    while ( v13 < v12 );
  }
}

// FUNC: R_TubeDeform
void __cdecl R_TubeDeform(drawSurf_s *surf)
{
  const srfTriangles_s *geo; // esi
  srfTriangles_s *v2; // eax
  bool v3; // zf
  srfTriangles_s *v4; // edi
  int m_numDrawIndices; // eax
  char *v6; // eax
  void *v7; // esp
  idDrawVert *v8; // ebx
  int numIndexes; // eax
  int *v10; // eax
  int v11; // edx
  int v12; // eax
  void *v13; // esp
  idDrawVert *v14; // eax
  int v15; // ecx
  idDrawVert *verts; // ebx
  int j; // edi
  int *indexes; // edx
  int v19; // eax
  double v20; // st7
  int v21; // eax
  int v22; // edx
  double v23; // st7
  int v24; // edx
  double v25; // st6
  double v26; // st5
  long double v27; // st4
  float v28; // eax
  int *v29; // edi
  idDrawVert *v30; // ebx
  int v31; // edx
  double v32; // st7
  int v33; // edx
  int v34; // eax
  double v35; // st7
  int v36; // eax
  double v37; // st7
  int v38; // eax
  float *p_x; // edx
  float *v40; // eax
  int v41; // edi
  int *v42; // ebx
  int v43; // eax
  int v44; // edx
  float *v45; // ebx
  idVec3 *v46; // ecx
  double v47; // st7
  double v48; // st6
  double v49; // st5
  long double v50; // st7
  long double v51; // st7
  double v52; // st7
  double v53; // st6
  float z; // edx
  double v55; // st7
  double v56; // st6
  float v57; // ecx
  double v58; // st6
  double v59; // st7
  idDrawVert *v60; // eax
  bool v61; // cc
  vertCache_s *v62; // eax
  char *v63; // [esp-4h] [ebp-8Ch]
  idDrawVert v64; // [esp+0h] [ebp-88h] BYREF
  float v65; // [esp+40h] [ebp-48h]
  float v66; // [esp+44h] [ebp-44h]
  float v67; // [esp+4Ch] [ebp-3Ch]
  float v68; // [esp+50h] [ebp-38h]
  float v69; // [esp+58h] [ebp-30h]
  float v70; // [esp+5Ch] [ebp-2Ch]
  float v71; // [esp+64h] [ebp-24h]
  float v72; // [esp+68h] [ebp-20h]
  idVec3 localView; // [esp+6Ch] [ebp-1Ch] BYREF
  srfTriangles_s *newTri; // [esp+78h] [ebp-10h]
  float x; // [esp+7Ch] [ebp-Ch]
  float y; // [esp+80h] [ebp-8h]
  float v77; // [esp+84h] [ebp-4h]
  idVec3 v78; // [esp+88h] [ebp+0h]
  idVec3 v79; // [esp+94h] [ebp+Ch]
  idVec3 v80; // [esp+A0h] [ebp+18h]
  float v81; // [esp+ACh] [ebp+24h]
  float v82; // [esp+B0h] [ebp+28h]
  float v83; // [esp+B4h] [ebp+2Ch]
  idVec3 mid[2]; // [esp+B8h] [ebp+30h] BYREF
  idDrawVert *av2; // [esp+D0h] [ebp+48h]
  float lengths[2]; // [esp+D4h] [ebp+4Ch]
  int nums[2]; // [esp+DCh] [ebp+54h]
  int i; // [esp+E4h] [ebp+5Ch]
  idDrawVert *ac; // [esp+E8h] [ebp+60h]
  idVec3 minor; // [esp+ECh] [ebp+64h]
  float l; // [esp+F8h] [ebp+70h]

  geo = surf->geo;
  if ( (surf->geo->numVerts & 3) != 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_AutospriteDeform: shader had odd vertex count");
  if ( geo->numIndexes != 6 * (geo->numVerts >> 2) )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_AutospriteDeform: autosprite had odd index count");
  R_GlobalPointToLocal(surf->space->modelMatrix, &tr.viewDef->renderView.vieworg, &localView);
  v2 = (srfTriangles_s *)R_ClearedFrameAlloc(180);
  v3 = geo->primBatchMesh == 0;
  v4 = v2;
  newTri = v2;
  if ( v3 )
  {
    v2->numVerts = geo->numVerts;
    numIndexes = geo->numIndexes;
    v4->numIndexes = numIndexes;
    v10 = (int *)R_FrameAlloc(4 * numIndexes);
    v11 = 4 * v4->numIndexes;
    v4->indexes = v10;
    SIMDProcessor->Memcpy(SIMDProcessor, v10, geo->indexes, v11);
    v12 = (v4->numVerts << 6) + 18;
    LOBYTE(v12) = v12 & 0xFC;
    v13 = alloca(v12);
    v14 = (idDrawVert *)&v64.color[3];
    LOBYTE(v14) = (unsigned __int8)&v64.color[3] & 0xF0;
    v15 = 0;
    i = 0;
    ac = v14;
    if ( geo->numVerts > 0 )
    {
      while ( 1 )
      {
        verts = geo->verts;
        nums[1] = 0;
        nums[0] = 0;
        lengths[1] = 999999.0;
        lengths[0] = 999999.0;
        for ( j = 0; j < 6; ++j )
        {
          indexes = geo->indexes;
          v19 = indexes[v15 + edgeVerts_0[j][0]] << 6;
          v20 = *(float *)((char *)&verts->xyz.x + v19);
          v21 = (int)verts + v19;
          verts = geo->verts;
          v22 = indexes[v15 + dword_102FD4D0[2 * j]] << 6;
          v23 = v20 - *(float *)((char *)&verts->xyz.x + v22);
          v24 = (int)verts + v22;
          v25 = *(float *)(v21 + 4) - *(float *)(v24 + 4);
          v26 = *(float *)(v21 + 8) - *(float *)(v24 + 8);
          v27 = sqrt(v26 * v26 + v25 * v25 + v23 * v23);
          if ( v27 >= lengths[0] )
          {
            if ( v27 < lengths[1] )
            {
              lengths[1] = v27;
              nums[1] = j;
            }
          }
          else
          {
            v28 = lengths[0];
            lengths[0] = v27;
            nums[1] = nums[0];
            lengths[1] = v28;
            nums[0] = j;
          }
        }
        v29 = geo->indexes;
        v30 = geo->verts;
        v31 = v29[v15 + dword_102FD4D0[2 * nums[0]]] << 6;
        v32 = *(float *)((char *)&v30->xyz.x + v31);
        v33 = (int)v30 + v31;
        v34 = v29[v15 + edgeVerts_0[nums[0]][0]] << 6;
        v35 = v32 + *(float *)((char *)&v30->xyz.x + v34);
        v36 = (int)v30 + v34;
        mid[0].x = v35 * 0.5;
        mid[0].y = (*(float *)(v33 + 4) + *(float *)(v36 + 4)) * 0.5;
        v37 = *(float *)(v33 + 8) + *(float *)(v36 + 8);
        v38 = v29[v15 + edgeVerts_0[nums[1]][0]];
        p_x = &v30[v29[v15 + dword_102FD4D0[2 * nums[1]]]].xyz.x;
        mid[0].z = v37 * 0.5;
        v40 = &v30[v38].xyz.x;
        v41 = 0;
        mid[1].x = (*p_x + *v40) * 0.5;
        mid[1].y = (p_x[1] + v40[1]) * 0.5;
        mid[1].z = (p_x[2] + v40[2]) * 0.5;
        v81 = mid[1].x - mid[0].x;
        v82 = mid[1].y - mid[0].y;
        v83 = mid[1].z - mid[0].z;
        while ( 1 )
        {
          v42 = geo->indexes;
          v43 = v42[v15 + dword_102FD4D0[2 * nums[v41]]];
          v44 = v42[v15 + edgeVerts_0[nums[v41]][0]] << 6;
          v45 = (float *)((char *)&ac->xyz.x + v44);
          LODWORD(l) = v43 << 6;
          v63 = (char *)geo->verts + v44;
          av2 = &ac[v43];
          idDrawVert::operator=(v63);
          idDrawVert::operator=((char *)geo->verts + LODWORD(l));
          v46 = &mid[v41];
          l = lengths[v41] * 0.5;
          v47 = v46->x - localView.x;
          v48 = v46->y - localView.y;
          v49 = v46->z - localView.z;
          minor.x = v82 * v49 - v48 * v83;
          minor.y = v83 * v47 - v49 * v81;
          minor.z = v48 * v81 - v82 * v47;
          v50 = minor.x * minor.x + minor.z * minor.z + minor.y * minor.y;
          if ( v50 != 0.0 )
          {
            v51 = 1.0 / sqrt(v50);
            minor.x = minor.x * v51;
            minor.y = minor.y * v51;
            minor.z = minor.z * v51;
          }
          if ( v41 )
          {
            v78 = minor;
            x = minor.x;
            v65 = minor.y * l;
            y = minor.y;
            v66 = minor.z * l;
            v52 = v46->x - minor.x * l;
            v53 = v46->y - v65;
            v64.normal.y = v46->z - v66;
            v45[2] = v64.normal.y;
            z = minor.z;
            *v45 = v52;
            v77 = z;
            v45[1] = v53;
            v67 = y * l;
            v68 = v77 * l;
            v55 = x * l + v46->x;
            v56 = v67 + v46->y;
            v64.st.x = v68 + v46->z;
            v57 = v64.st.x;
          }
          else
          {
            v80 = minor;
            v79 = minor;
            v71 = minor.y * l;
            v72 = minor.z * l;
            v64.tangents[0].x = v72 + mid[0].z;
            v58 = minor.x * l + mid[0].x;
            v59 = v71 + mid[0].y;
            v45[2] = v64.tangents[0].x;
            *v45 = v58;
            v45[1] = v59;
            v69 = v79.y * l;
            v70 = v79.z * l;
            v55 = mid[0].x - v79.x * l;
            v56 = mid[0].y - v69;
            v64.tangents[1].x = mid[0].z - v70;
            v57 = v64.tangents[1].x;
          }
          v60 = av2;
          av2->xyz.x = v55;
          ++v41;
          v60->xyz.y = v56;
          v60->xyz.z = v57;
          if ( v41 >= 2 )
            break;
          v15 = i;
        }
        v61 = i + 4 < geo->numVerts;
        i += 4;
        if ( !v61 )
          break;
        v15 = i;
      }
      v4 = newTri;
    }
    v8 = ac;
  }
  else
  {
    v2->numVerts = geo->primBatchMesh->m_numDrawVertices;
    m_numDrawIndices = geo->primBatchMesh->m_numDrawIndices;
    v4->numIndexes = m_numDrawIndices;
    v4->indexes = (int *)R_FrameAlloc(4 * m_numDrawIndices);
    ac = (idDrawVert *)(v4->numVerts << 6);
    v6 = (char *)&ac->normal.x + 2;
    LOBYTE(v6) = ((_BYTE)ac + 18) & 0xFC;
    v7 = alloca((int)v6);
    v8 = &v64;
    SIMDProcessor->Memset(SIMDProcessor, &v64, 0, (const int)ac);
    rvMesh::TubeDeform(geo->primBatchMesh, &v64, v4->indexes, &localView, geo->silTraceVerts);
  }
  if ( surf->material->numAmbientStages != surf->material->numStages )
  {
    v4->verts = v8;
    R_DeriveTangents(v4, 0);
    v4->verts = 0;
  }
  v62 = idVertexCache::AllocFrameTemp(&vertexCache, v8, v4->numVerts << 6, 2u);
  v4->ambientCache = v62;
  if ( v62 )
    surf->geo = v4;
  if ( r_useIndexBuffers.internalVar->integerValue )
    v4->indexCache = idVertexCache::AllocFrameTemp(&vertexCache, v4->indexes, 4 * v4->numIndexes, 1u);
}

// FUNC: R_FlareDeform
void __cdecl R_FlareDeform(drawSurf_s *surf)
{
  const srfTriangles_s *geo; // ebx
  void *v2; // esp
  int *v3; // edi
  int v4; // eax
  void *v5; // esp
  idDrawVert *v6; // eax
  srfTriangles_s *v7; // esi
  int v8; // eax
  void *v9; // esp
  int *v10; // edx
  idDrawVert *verts; // edi
  int v12; // eax
  double v13; // st7
  float *v14; // eax
  int v15; // ecx
  double v16; // st7
  float *v17; // ecx
  double v18; // st6
  float *p_x; // edx
  double v20; // st5
  double v21; // st4
  double v22; // st7
  long double v23; // st6
  long double v24; // st7
  long double v25; // st5
  unsigned __int8 v27; // c2
  unsigned __int8 v28; // c3
  double v29; // st7
  srfTriangles_s *v30; // eax
  float *v31; // eax
  double v32; // st7
  double v33; // st6
  double v34; // st5
  float *v35; // eax
  int v36; // ecx
  double v37; // st5
  double v38; // st7
  double v39; // st6
  double v40; // st5
  long double v41; // st4
  long double v42; // rtt
  char v43; // cl
  srfTriangles_s *v44; // edi
  int v45; // edx
  char *v46; // eax
  int v47; // edx
  float *p_y; // ecx
  _DWORD *v49; // edi
  int v50; // eax
  double v51; // st7
  double v52; // st7
  double v53; // st6
  double v54; // st5
  long double v55; // st5
  long double v56; // rt1
  int v57; // eax
  double v58; // st5
  int v59; // eax
  double v60; // st5
  double v61; // st4
  double v62; // st3
  long double v63; // st2
  long double v64; // rt1
  long double v65; // st2
  long double v66; // st5
  double v67; // st5
  double v68; // st4
  int v69; // eax
  int v70; // eax
  double v71; // st5
  int v72; // eax
  double v73; // st5
  double v74; // st4
  double v75; // st3
  long double v76; // st2
  long double v77; // rtt
  long double v78; // st4
  long double v79; // st7
  double v80; // st7
  double v81; // st6
  long double v82; // st4
  long double v83; // st7
  idDrawVert *v84; // ecx
  float *v85; // ecx
  double v86; // st7
  double v87; // st6
  idDrawVert *v88; // ecx
  float *v89; // ecx
  double v90; // st7
  double v91; // st6
  idDrawVert *v92; // ecx
  float *v93; // ecx
  double v94; // st7
  double v95; // st6
  double v96; // st5
  idDrawVert *v97; // ecx
  float *v98; // ecx
  double v99; // st7
  double v100; // st6
  idDrawVert *v101; // ecx
  float *v102; // ecx
  double v103; // st7
  double v104; // st6
  int v105; // ecx
  double v106; // st5
  idDrawVert *v107; // ecx
  idDrawVert *v108; // ecx
  int v109; // ecx
  double v110; // st6
  double v111; // st5
  float z; // ecx
  int v113; // eax
  double v114; // st7
  double v115; // st6
  float *v116; // ecx
  double v117; // st7
  double v118; // st6
  float x; // ecx
  float y; // ecx
  double v121; // st7
  double v122; // st6
  idDrawVert *v123; // ecx
  float *v124; // ecx
  double v125; // st7
  double v126; // st6
  int v127; // ecx
  float v128; // ecx
  idDrawVert *v129; // ebx
  double v130; // st6
  float *v131; // ebx
  int *v132; // ecx
  int v133; // edx
  double v134; // st7
  double v135; // st6
  double v136; // st7
  double v137; // st6
  long double v138; // st6
  long double v139; // st6
  long double v140; // st5
  double v141; // st5
  double v142; // st6
  double v143; // st7
  srfTriangles_s *v144; // ebx
  vertCache_s *v145; // eax
  _DWORD v146[52]; // [esp+18h] [ebp-188h] BYREF
  int indexes[16]; // [esp+E8h] [ebp-B8h] BYREF
  idVec3 edgeDir[4][3]; // [esp+128h] [ebp-78h] BYREF
  float distFromPlane; // [esp+1B8h] [ebp+18h]
  srfTriangles_s *newTri; // [esp+1BCh] [ebp+1Ch]
  int v151; // [esp+1C0h] [ebp+20h]
  int v152; // [esp+1C4h] [ebp+24h]
  int numVerts; // [esp+1C8h] [ebp+28h]
  idVec3 localViewer; // [esp+1CCh] [ebp+2Ch] BYREF
  float v155; // [esp+1D8h] [ebp+38h]
  float v156; // [esp+1DCh] [ebp+3Ch]
  int v157; // [esp+1E0h] [ebp+40h]
  idPlane plane; // [esp+1E4h] [ebp+44h]
  int v159; // [esp+1F4h] [ebp+54h]
  char v160[12]; // [esp+1F8h] [ebp+58h]
  idVec3 dir; // [esp+204h] [ebp+64h]
  float newLen; // [esp+210h] [ebp+70h]
  int savedregs; // [esp+214h] [ebp+74h]
  float retaddr; // [esp+218h] [ebp+78h]
  float surfa; // [esp+21Ch] [ebp+7Ch]

  geo = surf->geo;
  if ( surf->geo->primBatchMesh )
  {
    v2 = alloca(196);
    memset(v146, 0, 0xB4u);
    v146[9] = geo->primBatchMesh->m_numDrawVertices;
    v146[13] = geo->primBatchMesh->m_numDrawIndices;
    v3 = (int *)R_FrameAlloc(4 * v146[13]);
    v4 = (v146[9] << 6) + 18;
    LOBYTE(v4) = v4 & 0xFC;
    v146[14] = v3;
    v5 = alloca(v4);
    v6 = (idDrawVert *)((char *)&v146[3] + 3);
    LOBYTE(v6) = ((unsigned __int8)&v146[3] + 3) & 0xF0;
    v146[10] = v6;
    rvMesh::CopyTriangles(geo->primBatchMesh, v6, v3, geo->silTraceVerts);
    geo = (const srfTriangles_s *)v146;
  }
  if ( geo->numVerts == 4 && geo->numIndexes == 6 )
  {
    v7 = (srfTriangles_s *)R_ClearedFrameAlloc(180);
    newTri = v7;
    v7->numVerts = 16;
    v7->numIndexes = 54;
    v7->indexes = (int *)R_FrameAlloc(216);
    v8 = (v7->numVerts << 6) + 18;
    LOBYTE(v8) = v8 & 0xFC;
    v9 = alloca(v8);
    v10 = geo->indexes;
    verts = geo->verts;
    v12 = v10[2] << 6;
    v13 = *(float *)((char *)&verts->xyz.x + v12);
    v14 = (float *)((char *)&verts->xyz.x + v12);
    v15 = v10[1] << 6;
    v16 = v13 - *(float *)((char *)&verts->xyz.x + v15);
    v17 = (float *)((char *)&verts->xyz.x + v15);
    v18 = v14[1] - v17[1];
    p_x = &verts[*v10].xyz.x;
    v20 = v14[2] - v17[2];
    *(float *)v160 = *p_x - *v17;
    *(float *)&v160[4] = p_x[1] - v17[1];
    v21 = p_x[2] - v17[2];
    dir.x = *(float *)&v160[4] * v20 - v21 * v18;
    plane.a = dir.x;
    dir.y = v21 * v16 - v20 * *(float *)v160;
    plane.b = dir.y;
    v22 = v18 * *(float *)v160 - *(float *)&v160[4] * v16;
    plane.c = v22;
    v23 = v22 * v22 + dir.y * dir.y + dir.x * dir.x;
    if ( v23 == 0.0 )
    {
      v24 = 0.0;
    }
    else
    {
      v25 = 1.0 / sqrt(v23);
      plane.a = dir.x * v25;
      plane.b = dir.y * v25;
      plane.c = v22 * v25;
      v24 = v25 * v23;
    }
    if ( v28 | v27 )
    {
      if ( plane.b == 0.0 )
      {
        if ( plane.c <= 0.0 )
        {
          if ( plane.c != -1.0 )
            plane.c = -1.0;
        }
        else if ( plane.c != 1.0 )
        {
          plane.c = 1.0;
        }
        goto LABEL_41;
      }
      if ( plane.c == 0.0 )
      {
        if ( plane.b <= 0.0 )
        {
          if ( plane.b != -1.0 )
            plane.b = -1.0;
        }
        else if ( plane.b != 1.0 )
        {
          plane.b = 1.0;
        }
        goto LABEL_41;
      }
    }
    else if ( plane.b == 0.0 && plane.c == 0.0 )
    {
      if ( plane.a <= 0.0 )
      {
        if ( plane.a != -1.0 )
          plane.a = -1.0;
      }
      else if ( plane.a != 1.0 )
      {
        plane.a = 1.0;
      }
      goto LABEL_41;
    }
    v159 = LODWORD(plane.a) & 0x7FFFFFFF;
    if ( COERCE_FLOAT(LODWORD(plane.a) & 0x7FFFFFFF) == 1.0 )
    {
      if ( plane.b == 0.0 && plane.c == 0.0 )
        goto LABEL_41;
      plane.c = 0.0;
    }
    else
    {
      v159 = LODWORD(plane.b) & 0x7FFFFFFF;
      if ( COERCE_FLOAT(LODWORD(plane.b) & 0x7FFFFFFF) == 1.0 )
      {
        if ( plane.a != 0.0 || plane.c != 0.0 )
        {
          plane.c = 0.0;
          plane.a = 0.0;
        }
        goto LABEL_41;
      }
      v159 = LODWORD(plane.c) & 0x7FFFFFFF;
      if ( COERCE_FLOAT(LODWORD(plane.c) & 0x7FFFFFFF) != 1.0 || plane.a == 0.0 && plane.b == 0.0 )
      {
LABEL_41:
        if ( v24 != 0.0 )
          plane.d = -(plane.c * v17[2] + plane.a * *v17 + plane.b * v17[1]);
        R_GlobalPointToLocal(surf->space->modelMatrix, &tr.viewDef->renderView.vieworg, &localViewer);
        v29 = localViewer.z * plane.c + localViewer.y * plane.b + plane.a * localViewer.x + plane.d;
        distFromPlane = v29;
        if ( v29 > 0.0 )
        {
          v31 = &geo->verts->xyz.x;
          v32 = *v31;
          v33 = v31[1];
          v34 = v31[2];
          numVerts = geo->numVerts;
          dir.z = v34;
          if ( numVerts > 1 )
          {
            v35 = v31 + 16;
            v36 = numVerts - 1;
            do
            {
              v35 += 16;
              --v36;
              v32 = v32 + *(v35 - 16);
              v33 = v33 + *(v35 - 15);
              v34 = v34 + *(v35 - 14);
            }
            while ( v36 );
            dir.z = v34;
          }
          v37 = 1.0 / (double)numVerts;
          *(float *)&v159 = v37;
          dir.x = v37 * v32;
          dir.y = v33 * *(float *)&v159;
          dir.z = dir.z * *(float *)&v159;
          v38 = localViewer.x - dir.x;
          v39 = localViewer.y - dir.y;
          v40 = localViewer.z - dir.z;
          v41 = v40 * v40 + v38 * v38 + v39 * v39;
          if ( v41 != 0.0 )
          {
            v42 = 1.0 / sqrt(v41);
            v38 = v38 * v42;
            v39 = v39 * v42;
            v40 = v40 * v42;
          }
          *(float *)&numVerts = (v40 * plane.c + v39 * plane.b + v38 * plane.a) * 2048.0;
          v152 = (int)*(float *)&numVerts;
          v43 = v152;
          if ( v152 > 255 )
            v43 = -1;
          v44 = newTri;
          v45 = 0;
          if ( newTri->numVerts > 0 )
          {
            v46 = (char *)&v146[3] + 1;
            do
            {
              v46[1] = v43;
              *v46 = v43;
              *(v46 - 1) = v43;
              v46[2] = -1;
              ++v45;
              v46 += 64;
            }
            while ( v45 < v44->numVerts );
          }
          newLen = (float)surf->shaderRegisters[surf->material->deformRegisters[0]]
                 * r_flareSize.internalVar->floatValue;
          if ( R_WindingFromTriangles(geo, indexes) == 4 )
          {
            v47 = (int)geo->verts;
            v151 = v47;
            v159 = 3;
            v152 = (int)indexes;
            p_y = &edgeDir[0][1].y;
            v49 = &v146[2];
            numVerts = 4;
            do
            {
              v50 = *(_DWORD *)v152 << 6;
              *(v49 - 2) = *(_DWORD *)(v50 + v47);
              *(v49 - 1) = *(_DWORD *)(v50 + v151 + 4);
              *v49 = *(_DWORD *)(v50 + v151 + 8);
              v49[13] = 1056964608;
              v49[12] = 1056964608;
              v47 = (int)geo->verts;
              v51 = *(float *)(v50 + v47);
              v151 = v47;
              v52 = v51 - localViewer.x;
              v53 = *(float *)(v50 + v47 + 4) - localViewer.y;
              v54 = *(float *)(v50 + v47 + 8) - localViewer.z;
              dir.z = v54;
              v55 = v54 * dir.z + v53 * v53 + v52 * v52;
              if ( v55 != 0.0 )
              {
                v56 = 1.0 / sqrt(v55);
                v52 = v52 * v56;
                v53 = v53 * v56;
                dir.z = dir.z * v56;
              }
              v57 = indexes[(v159 - 2) % 4] << 6;
              v58 = *(float *)(v57 + v47);
              v59 = v47 + v57;
              v60 = v58 - localViewer.x;
              v61 = *(float *)(v59 + 4) - localViewer.y;
              v62 = *(float *)(v59 + 8) - localViewer.z;
              v63 = v62 * v62 + v61 * v61 + v60 * v60;
              if ( v63 != 0.0 )
              {
                v64 = 1.0 / sqrt(v63);
                v60 = v60 * v64;
                v61 = v61 * v64;
                v62 = v62 * v64;
              }
              *(p_y - 1) = v62 * v53 - v61 * dir.z;
              *p_y = dir.z * v60 - v62 * v52;
              p_y[1] = v61 * v52 - v53 * v60;
              v65 = *(p_y - 1) * *(p_y - 1) + p_y[1] * p_y[1] + *p_y * *p_y;
              if ( v65 != 0.0 )
              {
                v66 = 1.0 / sqrt(v65);
                *(p_y - 1) = v66 * *(p_y - 1);
                *p_y = v66 * *p_y;
                p_y[1] = v66 * p_y[1];
              }
              v67 = vec3_origin.x - *(p_y - 1);
              v68 = vec3_origin.y - *p_y;
              *(float *)&v160[8] = vec3_origin.z - p_y[1];
              p_y[1] = *(float *)&v160[8];
              v69 = v159;
              *(p_y - 1) = v67;
              *p_y = v68;
              v70 = indexes[v69 % 4] << 6;
              v71 = *(float *)(v70 + v47);
              v72 = v47 + v70;
              v73 = v71 - localViewer.x;
              v74 = *(float *)(v72 + 4) - localViewer.y;
              v75 = *(float *)(v72 + 8) - localViewer.z;
              v76 = v73 * v73 + v75 * v75 + v74 * v74;
              if ( v76 != 0.0 )
              {
                v77 = 1.0 / sqrt(v76);
                v73 = v73 * v77;
                v74 = v74 * v77;
                v75 = v75 * v77;
              }
              *(p_y - 4) = v75 * v53 - v74 * dir.z;
              *(p_y - 3) = dir.z * v73 - v75 * v52;
              *(p_y - 2) = v74 * v52 - v53 * v73;
              v78 = *(p_y - 4) * *(p_y - 4) + *(p_y - 2) * *(p_y - 2) + *(p_y - 3) * *(p_y - 3);
              if ( v78 != 0.0 )
              {
                v79 = 1.0 / sqrt(v78);
                *(p_y - 4) = v79 * *(p_y - 4);
                *(p_y - 3) = v79 * *(p_y - 3);
                *(p_y - 2) = v79 * *(p_y - 2);
              }
              v80 = *(p_y - 1) + *(p_y - 4);
              v81 = *(p_y - 3) + *p_y;
              *(float *)&v157 = p_y[1] + *(p_y - 2);
              p_y[4] = *(float *)&v157;
              p_y[2] = v80;
              p_y[3] = v81;
              v82 = p_y[2] * p_y[2] + p_y[4] * p_y[4] + p_y[3] * p_y[3];
              if ( v82 != 0.0 )
              {
                v83 = 1.0 / sqrt(v82);
                p_y[2] = v83 * p_y[2];
                p_y[3] = v83 * p_y[3];
                p_y[4] = v83 * p_y[4];
              }
              v152 += 4;
              ++v159;
              v49 += 16;
              p_y += 9;
              --numVerts;
            }
            while ( *(float *)&numVerts != 0.0 );
            *(_QWORD *)v160 = *(_QWORD *)&edgeDir[0][0].x;
            v84 = geo->verts;
            *(float *)&v160[8] = edgeDir[0][0].z;
            dir.y = edgeDir[0][0].y * newLen;
            v85 = &v84[indexes[0]].xyz.x;
            dir.z = edgeDir[0][0].z * newLen;
            v86 = edgeDir[0][0].x * newLen + *v85;
            v87 = dir.y + v85[1];
            *(float *)&v157 = dir.z + v85[2];
            indexes[14] = v157;
            *(float *)&indexes[12] = v86;
            *(float *)v160 = edgeDir[0][2].x;
            *(float *)&indexes[13] = v87;
            *(_QWORD *)&v160[4] = *(_QWORD *)&edgeDir[0][2].y;
            *(_QWORD *)&edgeDir[1][0].y = 0x3F00000000000000i64;
            v88 = geo->verts;
            dir.y = edgeDir[0][2].y * newLen;
            v89 = &v88[indexes[0]].xyz.x;
            dir.z = edgeDir[0][2].z * newLen;
            v90 = edgeDir[0][2].x * newLen + *v89;
            v91 = dir.y + v89[1];
            *(float *)&v157 = dir.z + v89[2];
            LODWORD(edgeDir[1][1].z) = v157;
            edgeDir[1][1].x = v90;
            *(float *)v160 = edgeDir[0][1].x;
            edgeDir[1][1].y = v91;
            *(_QWORD *)&v160[4] = *(_QWORD *)&edgeDir[0][1].y;
            edgeDir[2][2].z = 0.0;
            edgeDir[3][0].x = 0.0;
            v92 = geo->verts;
            dir.y = edgeDir[0][1].y * newLen;
            v93 = &v92[indexes[0]].xyz.x;
            dir.z = edgeDir[0][1].z * newLen;
            v94 = edgeDir[0][1].x * newLen + *v93;
            v95 = dir.y + v93[1];
            v96 = dir.z + v93[2];
            *(float *)v160 = edgeDir[1][0].x;
            *(float *)&v157 = v96;
            LODWORD(edgeDir[3][1].x) = v157;
            edgeDir[3][0].y = v94;
            *(_DWORD *)&v160[8] = 1056964608;
            edgeDir[3][0].z = v95;
            localViewer.y = 0.5;
            localViewer.z = 0.0;
            v97 = geo->verts;
            *(_DWORD *)&v160[4] = 0;
            v98 = &v97[indexes[1]].xyz.x;
            dir.y = 0.0 * newLen;
            dir.z = 0.5 * newLen;
            v99 = edgeDir[1][0].x * newLen + *v98;
            v100 = dir.y + v98[1];
            *(float *)&v157 = dir.z + v98[2];
            v155 = v99;
            v156 = v100;
            newLen = 0.5;
            *(_QWORD *)v160 = *(_QWORD *)&edgeDir[1][2].x;
            savedregs = 0;
            v101 = geo->verts;
            *(float *)&v160[8] = edgeDir[1][2].z;
            v102 = &v101[indexes[1]].xyz.x;
            dir.y = edgeDir[1][2].y * 0.5;
            dir.z = edgeDir[1][2].z * 0.5;
            v103 = edgeDir[1][2].x * 0.5 + *v102;
            v104 = dir.y + v102[1];
            *(float *)&v157 = dir.z + v102[2];
            retaddr = v103;
            *(_QWORD *)v160 = *(_QWORD *)&edgeDir[1][1].x;
            surfa = v104;
            *(float *)&v160[8] = edgeDir[1][1].z;
            dir.y = edgeDir[1][1].y * 0.5;
            v105 = (int)&geo->verts[indexes[1]];
            dir.z = edgeDir[1][1].z * 0.5;
            v106 = dir.z + *(float *)(v105 + 8);
            *(float *)v160 = edgeDir[2][0].x;
            *(float *)&v157 = v106;
            v107 = geo->verts;
            *(_QWORD *)&v160[4] = *(_QWORD *)&edgeDir[2][0].y;
            dir.y = edgeDir[2][0].y * 0.5;
            dir.z = edgeDir[2][0].z * 0.5;
            *(float *)&v157 = dir.z + v107[indexes[2]].xyz.z;
            *(_QWORD *)v160 = *(_QWORD *)&edgeDir[2][2].x;
            *(_DWORD *)&v160[8] = 0;
            v108 = geo->verts;
            dir.y = edgeDir[2][2].y * 0.5;
            dir.z = 0.0 * 0.5;
            *(float *)&v157 = dir.z + v108[indexes[2]].xyz.z;
            *(float *)v160 = edgeDir[2][1].x;
            *(_QWORD *)&v160[4] = *(_QWORD *)&edgeDir[2][1].y;
            v109 = (int)&geo->verts[indexes[2]];
            dir.y = edgeDir[2][1].y * 0.5;
            dir.z = edgeDir[2][1].z * 0.5;
            v110 = dir.y + *(float *)(v109 + 4);
            v111 = dir.z + *(float *)(v109 + 8);
            *(_DWORD *)v160 = 0;
            z = edgeDir[3][0].z;
            *(float *)&v157 = v111;
            STACK[0x320] = v157;
            *(float *)&v160[4] = edgeDir[3][0].y;
            *(float *)&STACK[0x31C] = v110;
            v113 = indexes[3];
            *(float *)&v160[8] = z;
            v114 = *(float *)v160 * newLen;
            STACK[0x350] = 1056964608;
            v115 = *(float *)&v160[4];
            STACK[0x354] = 1065353216;
            v113 <<= 6;
            v116 = (float *)((char *)&geo->verts->xyz.x + v113);
            dir.y = v115 * newLen;
            dir.z = *(float *)&v160[8] * newLen;
            v117 = v114 + *v116;
            v118 = dir.y + v116[1];
            *(float *)&v157 = dir.z + v116[2];
            STACK[0x360] = v157;
            x = edgeDir[3][2].x;
            *(float *)&STACK[0x358] = v117;
            *(float *)v160 = x;
            y = edgeDir[3][2].y;
            *(float *)&STACK[0x35C] = v118;
            *(_QWORD *)&v160[4] = __PAIR64__(LODWORD(edgeDir[3][2].z), LODWORD(y));
            v121 = *(float *)v160 * newLen;
            v122 = y * newLen;
            STACK[0x390] = 1056964608;
            STACK[0x394] = 1065353216;
            v123 = geo->verts;
            dir.y = v122;
            v124 = (float *)((char *)&v123->xyz.x + v113);
            dir.z = *(float *)&v160[8] * newLen;
            v125 = v121 + *v124;
            v126 = dir.y + v124[1];
            *(float *)&v157 = dir.z + v124[2];
            v127 = v157;
            *(float *)&STACK[0x398] = v125;
            STACK[0x3A0] = v127;
            v128 = edgeDir[3][1].y;
            *(float *)&STACK[0x39C] = v126;
            STACK[0x3D0] = 0;
            STACK[0x3D4] = 1065353216;
            v129 = geo->verts;
            *(float *)v160 = edgeDir[3][1].x;
            *(_QWORD *)&v160[4] = __PAIR64__(LODWORD(edgeDir[3][1].z), LODWORD(v128));
            v130 = v128 * newLen;
            v131 = (float *)((char *)&v129->xyz.x + v113);
            v132 = &indexes[14];
            dir.y = v130;
            v133 = 12;
            dir.z = edgeDir[3][1].z * newLen;
            v134 = edgeDir[3][1].x * newLen + *v131;
            v135 = dir.y + v131[1];
            *(float *)&v157 = dir.z + v131[2];
            STACK[0x3E0] = v157;
            *(float *)&STACK[0x3D8] = v134;
            *(float *)&STACK[0x3DC] = v135;
            STACK[0x410] = 0;
            STACK[0x414] = 1056964608;
            do
            {
              v136 = *((float *)v132 - 2) - localViewer.x;
              dir.y = *((float *)v132 - 1) - localViewer.y;
              v137 = *(float *)v132 - localViewer.z;
              dir.z = v137;
              v138 = v137 * dir.z + dir.y * dir.y + v136 * v136;
              if ( v138 == 0.0 )
              {
                v139 = 0.0;
              }
              else
              {
                v140 = 1.0 / sqrt(v138);
                v136 = v136 * v140;
                dir.y = dir.y * v140;
                dir.z = dir.z * v140;
                v139 = v138 * v140;
              }
              v141 = -(distFromPlane / (dir.z * plane.c + dir.y * plane.b + v136 * plane.a));
              newLen = v141;
              if ( v141 > 0.0 && newLen < v139 )
              {
                *(float *)&v160[4] = dir.y * newLen;
                *(float *)&v160[8] = dir.z * newLen;
                *(float *)&v157 = *(float *)&v160[8] + localViewer.z;
                v142 = v136 * newLen + localViewer.x;
                v143 = *(float *)&v160[4] + localViewer.y;
                *v132 = v157;
                *((float *)v132 - 2) = v142;
                *((float *)v132 - 1) = v143;
              }
              v132[12] = 0;
              v132[13] = 1056964608;
              v132 += 16;
              --v133;
            }
            while ( v133 );
            v144 = newTri;
            SIMDProcessor->Memcpy(SIMDProcessor, newTri->indexes, triIndexes, 216);
            if ( r_useIndexBuffers.internalVar->integerValue )
              v144->indexCache = idVertexCache::AllocFrameTemp(&vertexCache, v144->indexes, 216, 1u);
            if ( *(_DWORD *)(*(_DWORD *)(LODWORD(surfa) + 8) + 268) != *(_DWORD *)(*(_DWORD *)(LODWORD(surfa) + 8) + 264) )
            {
              v144->verts = (idDrawVert *)v146;
              R_DeriveTangents(v144, 0);
              v144->verts = 0;
            }
            v145 = idVertexCache::AllocFrameTemp(&vertexCache, v146, v144->numVerts << 6, 2u);
            v144->ambientCache = v145;
            if ( v145 )
              *(_DWORD *)LODWORD(surfa) = v144;
          }
        }
        else
        {
          v30 = newTri;
          newTri->numIndexes = 0;
          surf->geo = v30;
        }
        return;
      }
      plane.a = 0.0;
    }
    plane.b = 0.0;
    goto LABEL_41;
  }
  if ( !com_QuickLoad.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "R_FlareDeform: not a single quad at (%g, %g, %g)",
      geo->verts->xyz.x,
      geo->verts->xyz.y,
      geo->verts->xyz.z);
}

// FUNC: R_EyeballDeform
void __cdecl R_EyeballDeform(drawSurf_s *surf)
{
  const srfTriangles_s *geo; // esi
  bool v2; // zf
  void *v3; // esp
  int v4; // eax
  void *v5; // esp
  int v6; // eax
  void *v7; // esp
  idDrawVert *v8; // eax
  int v9; // edx
  int v10; // ecx
  float *p_y; // edi
  int v12; // ebx
  srfTriangles_s *v13; // ebx
  int v14; // eax
  void *v15; // esp
  float *v16; // eax
  int v17; // ecx
  double v18; // st7
  double v19; // st7
  double v20; // st6
  float *p_z; // edi
  int v22; // edx
  float *v23; // eax
  int v24; // ecx
  double v25; // st7
  double v26; // st6
  double v27; // st7
  int v28; // edi
  float v29; // eax
  float x; // edx
  double v31; // st7
  double v32; // st7
  idVec3 *p_mid; // eax
  float y; // edx
  float z; // eax
  long double v36; // st6
  long double v37; // st6
  int v38; // eax
  const srfTriangles_s *v39; // ecx
  int v40; // edx
  idDrawVert *verts; // edi
  float *p_x; // edx
  int *indexes; // edi
  double v44; // st6
  idDrawVert *v45; // edi
  double v46; // st5
  long double v47; // st4
  long double v48; // rt0
  double v49; // st4
  double v50; // st3
  double v51; // st2
  float *v52; // edx
  int v53; // edi
  double v54; // st6
  long double v55; // st3
  long double v56; // st6
  bool v57; // cc
  int v58; // eax
  idDrawVert *v59; // edx
  idDrawVert *v60; // edx
  double v61; // st7
  float *v62; // edx
  double v63; // st7
  double v64; // st6
  double v65; // st5
  int v66; // eax
  idDrawVert *v67; // edx
  int v68; // edi
  char *v69; // edx
  idDrawVert *v70; // edx
  double v71; // st7
  float *v72; // edx
  double v73; // st7
  double v74; // st6
  double v75; // st5
  int v76; // eax
  idDrawVert *v77; // edx
  int v78; // edi
  char *v79; // edx
  idDrawVert *v80; // edx
  double v81; // st7
  float *v82; // edx
  double v83; // st7
  double v84; // st6
  double v85; // st5
  float *v86; // edx
  double v87; // st5
  vertCache_s *v88; // eax
  int v89[52]; // [esp-C4h] [ebp-324h] BYREF
  eyeIsland_t islands[6]; // [esp+Ch] [ebp-254h] BYREF
  bool triUsed[60]; // [esp+1ECh] [ebp-74h] BYREF
  idVec3 focus; // [esp+228h] [ebp-38h]
  float v93; // [esp+238h] [ebp-28h]
  float v94; // [esp+23Ch] [ebp-24h]
  idVec3 v1; // [esp+240h] [ebp-20h]
  int sortOrder[6]; // [esp+24Ch] [ebp-14h]
  float dist[6]; // [esp+268h] [ebp+8h]
  const srfTriangles_s *tri; // [esp+284h] [ebp+24h]
  int v99; // [esp+288h] [ebp+28h]
  idVec3 origin; // [esp+28Ch] [ebp+2Ch]
  int numTri; // [esp+298h] [ebp+38h]
  idVec3 texVec[2]; // [esp+29Ch] [ebp+3Ch] BYREF
  int j; // [esp+2B4h] [ebp+54h]
  idVec3 dir; // [esp+2B8h] [ebp+58h]
  float *v105; // [esp+2C4h] [ebp+64h]
  const idVec3 *p2; // [esp+2C8h] [ebp+68h]
  int numIslands; // [esp+2CCh] [ebp+6Ch]
  int temp; // [esp+2D0h] [ebp+70h]

  geo = surf->geo;
  v2 = surf->geo->primBatchMesh == 0;
  tri = surf->geo;
  if ( !v2 )
  {
    v3 = alloca(196);
    memset(v89, 0, 0xB4u);
    v89[9] = geo->primBatchMesh->m_numDrawVertices;
    v89[13] = geo->primBatchMesh->m_numDrawIndices;
    v4 = 4 * v89[13] + 18;
    LOBYTE(v4) = v4 & 0xFC;
    v5 = alloca(v4);
    v6 = (v89[9] << 6) + 18;
    LOBYTE(v6) = v6 & 0xFC;
    v89[14] = (int)v89;
    v7 = alloca(v6);
    v8 = (idDrawVert *)((char *)&v89[3] + 3);
    LOBYTE(v8) = ((unsigned __int8)&v89[3] + 3) & 0xF0;
    v89[10] = (int)v8;
    rvMesh::CopyTriangles(geo->primBatchMesh, v8, v89, geo->silTraceVerts);
    tri = (const srfTriangles_s *)v89;
    geo = (const srfTriangles_s *)v89;
  }
  v9 = geo->numIndexes / 3;
  numTri = v9;
  if ( v9 <= 60 )
  {
    memset(triUsed, 0, sizeof(triUsed));
    *(float *)&v10 = 0.0;
    *(float *)&numIslands = 0.0;
    p_y = &islands[0].bounds.b[0].y;
    do
    {
      v12 = 0;
      *(p_y - 2) = 0.0;
      p_y[1] = idMath::INFINITY;
      *p_y = idMath::INFINITY;
      *(p_y - 1) = idMath::INFINITY;
      p_y[4] = -1.0e30;
      p_y[3] = -1.0e30;
      p_y[2] = -1.0e30;
      if ( v9 > 0 )
      {
        while ( triUsed[v12] )
        {
          if ( ++v12 >= v9 )
            goto LABEL_11;
        }
        AddTriangleToIsland_r(geo, v12, triUsed, (eyeIsland_t *)(p_y - 12));
        v9 = numTri;
        v10 = numIslands;
      }
LABEL_11:
      if ( v12 == v9 )
        break;
      ++v10;
      p_y += 20;
      numIslands = v10;
    }
    while ( v10 < 6 );
    if ( v10 == 3 )
    {
      v13 = (srfTriangles_s *)R_ClearedFrameAlloc(180);
      memset(v13, 0, sizeof(srfTriangles_s));
      v13->numVerts = geo->numVerts;
      v13->numIndexes = geo->numIndexes;
      v13->indexes = (int *)R_FrameAlloc(4 * geo->numIndexes);
      v14 = (geo->numVerts << 6) + 18;
      LOBYTE(v14) = v14 & 0xFC;
      v15 = alloca(v14);
      v13->numIndexes = 0;
      v16 = &islands[0].bounds.b[1].y;
      v17 = 3;
      do
      {
        v18 = *(v16 - 4);
        v16 += 20;
        --v17;
        v19 = (v18 + *(v16 - 21)) * 0.5;
        v20 = (*(v16 - 23) + *(v16 - 20)) * 0.5;
        v94 = (*(v16 - 22) + *(v16 - 19)) * 0.5;
        *(v16 - 16) = v94;
        *(v16 - 18) = v19;
        *(v16 - 17) = v20;
      }
      while ( v17 );
      p_z = &islands[0].mid.z;
      v105 = &islands[0].mid.z;
      numTri = 3;
      do
      {
        if ( *((_DWORD *)p_z - 9) != 1 )
        {
          v22 = 0;
          v23 = &islands[0].mid.z;
          j = 0;
          *(float *)&numIslands = COERCE_FLOAT((eyeIsland_t *)&islands[0].mid.z);
          while ( 1 )
          {
            v24 = v22 - 1;
            v25 = *(v23 - 2) - *(p_z - 2);
            sortOrder[v22] = v22;
            v26 = *(v23 - 1) - *(p_z - 1);
            for ( dist[v22] = sqrt(v25 * v25 + (*v23 - *p_z) * (*v23 - *p_z) + v26 * v26); v24 >= 0; --v24 )
            {
              if ( dist[v24] > (double)dist[v24 + 1] )
              {
                v27 = dist[v24];
                v28 = sortOrder[v24 + 1];
                sortOrder[v24 + 1] = sortOrder[v24];
                v29 = dist[v24 + 1];
                dist[v24 + 1] = v27;
                sortOrder[v24] = v28;
                p_z = v105;
                dist[v24] = v29;
              }
            }
            numIslands += 80;
            j = ++v22;
            if ( v22 >= 3 )
              break;
            v23 = (float *)numIslands;
          }
          x = islands[sortOrder[1]].mid.x;
          origin.y = islands[sortOrder[1]].mid.y;
          v31 = islands[sortOrder[2]].mid.x;
          origin.x = x;
          v32 = v31 - x;
          p_mid = &islands[sortOrder[2]].mid;
          origin.z = islands[sortOrder[1]].mid.z;
          y = p_mid->y;
          z = p_mid->z;
          focus.y = y;
          focus.z = z;
          dir.y = y - origin.y;
          dir.z = z - origin.z;
          v36 = v32 * v32 + dir.z * dir.z + dir.y * dir.y;
          if ( v36 != 0.0 )
          {
            v37 = 1.0 / sqrt(v36);
            v32 = v32 * v37;
            dir.y = dir.y * v37;
            dir.z = dir.z * v37;
          }
          v38 = islands[sortOrder[1]].tris[0];
          v39 = tri;
          v40 = tri->indexes[v38];
          verts = tri->verts;
          v99 = v38;
          p_x = &verts[v40].xyz.x;
          indexes = tri->indexes;
          p2 = &tri->verts[indexes[v38 + 1]].xyz;
          v44 = p2->x - *p_x;
          v45 = &tri->verts[indexes[v38 + 2]];
          v46 = p2->y - p_x[1];
          v1.z = p2->z - p_x[2];
          v47 = v44 * v44 + v1.z * v1.z + v46 * v46;
          if ( v47 != 0.0 )
          {
            v48 = 1.0 / sqrt(v47);
            v44 = v44 * v48;
            v46 = v46 * v48;
            v1.z = v1.z * v48;
          }
          v49 = v45->xyz.x - *p_x;
          v50 = v45->xyz.y - p_x[1];
          v51 = v45->xyz.z - p_x[2];
          *(float *)&p2 = v49 * v49 + v51 * v51 + v50 * v50;
          if ( *(float *)&p2 != 0.0 )
          {
            *(float *)&numIslands = 1.0 / sqrt(*(float *)&p2);
            v49 = v49 * *(float *)&numIslands;
            v50 = v50 * *(float *)&numIslands;
            v51 = v51 * *(float *)&numIslands;
          }
          v52 = &texVec[0].z;
          v53 = 2;
          texVec[0].x = v51 * v46 - v50 * v1.z;
          texVec[0].y = v1.z * v49 - v51 * v44;
          texVec[0].z = v50 * v44 - v46 * v49;
          texVec[1].x = texVec[0].y * dir.z - texVec[0].z * dir.y;
          texVec[1].y = texVec[0].z * v32 - dir.z * texVec[0].x;
          texVec[1].z = dir.y * texVec[0].x - texVec[0].y * v32;
          do
          {
            v54 = dir.z * *v52 + dir.y * *(v52 - 1) + v32 * *(v52 - 2);
            v93 = dir.y * v54;
            v94 = dir.z * v54;
            *(v52 - 2) = *(v52 - 2) - v54 * v32;
            *(v52 - 1) = *(v52 - 1) - v93;
            *v52 = *v52 - v94;
            v55 = *(v52 - 2) * *(v52 - 2) + *(v52 - 1) * *(v52 - 1) + *v52 * *v52;
            if ( v55 != 0.0 )
            {
              v56 = 1.0 / sqrt(v55);
              *(v52 - 2) = v56 * *(v52 - 2);
              *(v52 - 1) = v56 * *(v52 - 1);
              *v52 = v56 * *v52;
            }
            v52 += 3;
            --v53;
          }
          while ( v53 );
          p_z = v105;
          v57 = *((_DWORD *)v105 - 9) <= 0;
          j = 0;
          if ( !v57 )
          {
            temp = (int)(v105 - 19);
            do
            {
              v58 = v39->indexes[3 * *(_DWORD *)temp];
              v13->indexes[v13->numIndexes++] = v58;
              v59 = v39->verts;
              v58 <<= 6;
              *(int *)((char *)v89 + v58) = *(_DWORD *)((char *)&v59->xyz.x + v58);
              *(int *)((char *)&v89[1] + v58) = *(_DWORD *)((char *)&v59->xyz.y + v58);
              *(int *)((char *)&v89[2] + v58) = *(_DWORD *)((char *)&v59->xyz.z + v58);
              v60 = v39->verts;
              v61 = *(float *)((char *)&v60->xyz.x + v58);
              v62 = (float *)((char *)&v60->xyz.x + v58);
              v63 = v61 - origin.x;
              v64 = v62[1] - origin.y;
              v65 = v62[2] - origin.z;
              *(float *)((char *)&v89[14] + v58) = v63 * texVec[0].x + v65 * texVec[0].z + v64 * texVec[0].y + 0.5;
              *(float *)((char *)&v89[15] + v58) = v63 * texVec[1].x + v65 * texVec[1].z + v64 * texVec[1].y + 0.5;
              v66 = v39->indexes[3 * *(_DWORD *)temp + 1];
              v13->indexes[v13->numIndexes++] = v66;
              v67 = v39->verts;
              v66 <<= 6;
              v68 = *(_DWORD *)((char *)&v67->xyz.x + v66);
              v69 = (char *)v67 + v66;
              *(int *)((char *)v89 + v66) = v68;
              *(int *)((char *)&v89[1] + v66) = *((_DWORD *)v69 + 1);
              *(int *)((char *)&v89[2] + v66) = *((_DWORD *)v69 + 2);
              v70 = v39->verts;
              v71 = *(float *)((char *)&v70->xyz.x + v66);
              v72 = (float *)((char *)&v70->xyz.x + v66);
              v73 = v71 - origin.x;
              v74 = v72[1] - origin.y;
              v75 = v72[2] - origin.z;
              *(float *)((char *)&v89[14] + v66) = v73 * texVec[0].x + v75 * texVec[0].z + v74 * texVec[0].y + 0.5;
              *(float *)((char *)&v89[15] + v66) = v73 * texVec[1].x + v75 * texVec[1].z + v74 * texVec[1].y + 0.5;
              v76 = v39->indexes[3 * *(_DWORD *)temp + 2];
              v13->indexes[v13->numIndexes++] = v76;
              v77 = v39->verts;
              v76 <<= 6;
              v78 = *(_DWORD *)((char *)&v77->xyz.x + v76);
              v79 = (char *)v77 + v76;
              *(int *)((char *)v89 + v76) = v78;
              *(int *)((char *)&v89[1] + v76) = *((_DWORD *)v79 + 1);
              *(int *)((char *)&v89[2] + v76) = *((_DWORD *)v79 + 2);
              v80 = v39->verts;
              v81 = *(float *)((char *)&v80->xyz.x + v76);
              v82 = (float *)((char *)&v80->xyz.x + v76);
              v83 = v81 - origin.x;
              temp += 4;
              v84 = v82[1] - origin.y;
              v85 = v82[2];
              v86 = v105;
              v87 = v85 - origin.z;
              *(float *)((char *)&v89[14] + v76) = v83 * texVec[0].x + v87 * texVec[0].z + v84 * texVec[0].y + 0.5;
              *(float *)((char *)&v89[15] + v76) = v83 * texVec[1].x + v87 * texVec[1].z + v84 * texVec[1].y + 0.5;
              v57 = ++j < *((_DWORD *)v86 - 9);
            }
            while ( v57 );
            p_z = v86;
          }
        }
        p_z += 20;
        v2 = numTri-- == 1;
        v105 = p_z;
      }
      while ( !v2 );
      if ( surf->material->numAmbientStages != surf->material->numStages )
      {
        v13->verts = (idDrawVert *)v89;
        R_DeriveTangents(v13, 0);
        v13->verts = 0;
      }
      v88 = idVertexCache::AllocFrameTemp(&vertexCache, v89, v13->numVerts << 6, 2u);
      v13->ambientCache = v88;
      if ( v88 )
        surf->geo = v13;
      if ( r_useIndexBuffers.internalVar->integerValue )
        v13->indexCache = idVertexCache::AllocFrameTemp(&vertexCache, v13->indexes, 4 * v13->numIndexes, 1u);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "R_EyeballDeform: %i triangle islands\n",
        v10);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "R_EyeballDeform: too many triangles in surface");
  }
}

// FUNC: void __cdecl R_DeformDrawSurf(struct drawSurf_s *)
void __cdecl R_DeformDrawSurf(drawSurf_s *drawSurf)
{
  const idMaterial *material; // ecx

  material = drawSurf->material;
  if ( material && !r_skipDeforms.internalVar->integerValue )
  {
    switch ( material->deform )
    {
      case DFRM_SPRITE:
        R_SpriteDeform(drawSurf, 1);
        break;
      case DFRM_TUBE:
        R_TubeDeform(drawSurf);
        break;
      case DFRM_FLARE:
        R_FlareDeform(drawSurf);
        break;
      case DFRM_EXPAND:
        R_ExpandDeform(drawSurf);
        break;
      case DFRM_MOVE:
        R_MoveDeform(drawSurf);
        break;
      case DFRM_EYEBALL:
        R_EyeballDeform(drawSurf);
        break;
      case DFRM_RECTSPRITE:
        R_SpriteDeform(drawSurf, 0);
        break;
      case DFRM_TURB:
        R_TurbulentDeform(drawSurf);
        break;
      default:
        return;
    }
  }
}
