
// FUNC: R_CalcPointCull
void __usercall R_CalcPointCull(const srfTriangles_s *tri@<esi>, const idPlane *frustum, unsigned __int16 *pointCull)
{
  const idPlane *v3; // ebx
  int v4; // edi
  int j; // eax
  int numVerts; // ebx
  int v7; // eax
  void *v8; // esp
  int v9; // eax
  void *v10; // esp
  int v11; // eax
  unsigned __int8 *v12; // ebx
  void *v13; // esp
  unsigned __int8 *v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // edx
  __int16 v18; // di
  __int16 v19; // cx
  _BYTE v20[8]; // [esp+0h] [ebp-18h] BYREF
  unsigned __int8 *side2; // [esp+8h] [ebp-10h]
  const idPlane *v22; // [esp+Ch] [ebp-Ch] BYREF
  int i; // [esp+10h] [ebp-8h]
  int frontBits; // [esp+14h] [ebp-4h]

  ((void (__stdcall *)(int, int))SIMDProcessor->Memset)(-1, 4 * tri->numVerts);
  v3 = frustum;
  v4 = 0;
  frontBits = 0;
  do
  {
    if ( idBounds::PlaneDistance(&tri->bounds, v3) >= 0.1 )
      frontBits |= 1 << (v4 + 6);
    ++v4;
    ++v3;
  }
  while ( v4 < 6 );
  for ( j = 0; j < tri->numVerts; ++j )
    pointCull[j] = frontBits;
  if ( frontBits != 4032 )
  {
    numVerts = tri->numVerts;
    v7 = 4 * numVerts + 18;
    LOBYTE(v7) = v7 & 0xFC;
    v22 = (const idPlane *)numVerts;
    v8 = alloca(v7);
    v9 = numVerts + 18;
    LOBYTE(v9) = (numVerts + 18) & 0xFC;
    v10 = alloca(v9);
    v11 = numVerts + 18;
    LOBYTE(v11) = (numVerts + 18) & 0xFC;
    v12 = v20;
    v13 = alloca(v11);
    v14 = (unsigned __int8 *)&v22 + 3;
    LOBYTE(v14) = ((unsigned __int8)&v22 + 3) & 0xF0;
    side2 = v14;
    SIMDProcessor->Memset(SIMDProcessor, v20, 0, (const int)v22);
    SIMDProcessor->Memset(SIMDProcessor, side2, 0, tri->numVerts);
    v15 = 0;
    i = 0;
    v22 = frustum;
    do
    {
      if ( ((1 << (v15 + 6)) & frontBits) == 0 )
      {
        (*(void (__fastcall **)(idSIMDProcessor *, _BYTE *, const idPlane *, idDrawVert *, int))&SIMDProcessor->gap34[16])(
          SIMDProcessor,
          v20,
          v22,
          tri->verts,
          tri->numVerts);
        (*((void (__fastcall **)(idSIMDProcessor *, _BYTE *, int, _BYTE *, int, int))&SIMDProcessor->CmpGE + 1))(
          SIMDProcessor,
          v20,
          i,
          v20,
          1036831949,
          tri->numVerts);
        (*((void (__fastcall **)(idSIMDProcessor *, unsigned __int8 *, int, _BYTE *, int, int))&SIMDProcessor->Dot + 1))(
          SIMDProcessor,
          side2,
          i,
          v20,
          -1110651699,
          tri->numVerts);
        v15 = i;
      }
      ++v22;
      i = ++v15;
    }
    while ( v15 < 6 );
    v16 = 0;
    if ( tri->numVerts > 0 )
    {
      v17 = side2 - v20;
      do
      {
        v18 = v12[v17];
        v19 = *v12;
        ++v16;
        ++v12;
        pointCull[v16 - 1] |= v19 | (unsigned __int16)(v18 << 6);
      }
      while ( v16 < tri->numVerts );
    }
  }
}

// FUNC: PointsOrdered
bool __usercall PointsOrdered@<al>(const idVec3 *a@<ecx>, const idVec3 *b@<eax>)
{
  return b->z * 1023.0 + b->y * 127.0 + b->x > a->z * 1023.0 + a->y * 127.0 + a->x;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::LightProjectionMatrix(class idVec3 const &,class idPlane const &,class idVec4 * const)
void __thiscall idRenderSystemLocal::LightProjectionMatrix(
        idRenderSystemLocal *this,
        const idVec3 *origin,
        const idPlane *rearPlane,
        idVec4 *mat)
{
  double x; // st7
  double y; // st6
  float lv_8; // [esp+8h] [ebp-8h]
  float origina; // [esp+14h] [ebp+4h]

  x = origin->x;
  y = origin->y;
  lv_8 = origin->z;
  origina = x * rearPlane->a + y * rearPlane->b + lv_8 * rearPlane->c + rearPlane->d;
  mat->x = origina - x * rearPlane->a;
  mat->y = -(x * rearPlane->b);
  mat->z = -(x * rearPlane->c);
  mat->w = -(x * rearPlane->d);
  mat[1].x = -(y * rearPlane->a);
  mat[1].y = origina - y * rearPlane->b;
  mat[1].z = -(y * rearPlane->c);
  mat[1].w = -(y * rearPlane->d);
  mat[2].x = -(lv_8 * rearPlane->a);
  mat[2].y = -(lv_8 * rearPlane->b);
  mat[2].z = origina - lv_8 * rearPlane->c;
  mat[2].w = -(lv_8 * rearPlane->d);
  mat[3].x = -rearPlane->a;
  mat[3].y = -rearPlane->b;
  mat[3].z = -rearPlane->c;
  mat[3].w = origina - rearPlane->d;
}

// FUNC: R_ProjectPointsToFarPlane
void __usercall R_ProjectPointsToFarPlane(
        const idRenderEntityLocal *ent@<edx>,
        const idRenderLightLocal *light@<ecx>,
        int numShadowVerts@<eax>,
        const idPlane *lightPlaneLocal,
        int firstShadowVert)
{
  idVec4 *v6; // ecx
  unsigned int v7; // esi
  double y; // st7
  double v9; // st7
  float w; // eax
  double v11; // st7
  idVec3 lv; // [esp+8h] [ebp-4Ch] BYREF
  idVec4 mat[4]; // [esp+14h] [ebp-40h] BYREF

  R_GlobalPointToLocal(ent->modelMatrix, &light->globalLightOrigin, &lv);
  renderSystem->LightProjectionMatrix(renderSystem, &lv, lightPlaneLocal, mat);
  v6 = &shadowVerts[firstShadowVert];
  if ( firstShadowVert < numShadowVerts )
  {
    v7 = ((unsigned int)(numShadowVerts - firstShadowVert - 1) >> 1) + 1;
    do
    {
      y = mat[3].y;
      v6->w = 1.0;
      v9 = y * v6->y + mat[3].z * v6->z + mat[3].x * v6->x + mat[3].w;
      if ( v9 == 0.0 )
      {
        v6[1].x = v6->x;
        v6[1].y = v6->y;
        w = v6->w;
        v6[1].z = v6->z;
        v6[1].w = w;
      }
      else
      {
        v11 = 1.0 / v9;
        v6[1].w = 1.0;
        v6[1].x = (mat[0].y * v6->y + mat[0].z * v6->z + mat[0].x * v6->x + mat[0].w) * v11;
        v6[1].y = (mat[1].y * v6->y + mat[1].z * v6->z + mat[1].x * v6->x + mat[1].w) * v11;
        v6[1].z = (mat[2].y * v6->y + mat[2].z * v6->z + mat[2].x * v6->x + mat[2].w) * v11;
      }
      v6 += 2;
      --v7;
    }
    while ( v7 );
  }
}

// FUNC: R_ClipLineToLight
char __usercall R_ClipLineToLight@<al>(
        const idVec3 *a@<edx>,
        const idVec3 *b@<eax>,
        idVec3 *p1@<ecx>,
        idVec3 *p2@<esi>,
        const idPlane *frustum)
{
  int v5; // edi
  float *i; // edx
  idVec3 *v7; // eax
  double v8; // st7
  float d1; // [esp+4h] [ebp-8h]
  float d2; // [esp+8h] [ebp-4h]

  *p1 = *a;
  *p2 = *b;
  v5 = 0;
  for ( i = &frustum->b; ; i += 4 )
  {
    d1 = i[1] * p1->z + *(i - 1) * p1->x + *i * p1->y + i[2];
    d2 = *(i - 1) * p2->x + p2->z * i[1] + *i * p2->y + i[2];
    if ( d1 <= -0.1 || d2 <= -0.1 )
      break;
LABEL_11:
    if ( ++v5 >= 6 )
      return 1;
  }
  if ( (d1 > -0.1 || d2 >= 0.1) && (d2 > -0.1 || d1 >= 0.1) )
  {
    v7 = p1;
    if ( d1 >= 0.0 )
      v7 = p2;
    v8 = d1 / (d1 - d2);
    v7->x = (p2->x - p1->x) * v8 + p1->x;
    v7->y = (p2->y - p1->y) * v8 + p1->y;
    v7->z = (p2->z - p1->z) * v8 + p1->z;
    goto LABEL_11;
  }
  return 0;
}

// FUNC: R_AddClipSilEdges
int R_AddClipSilEdges()
{
  int result; // eax
  int v1; // ecx
  int v2; // edx
  int v3; // edi
  int v4; // ebx
  idVec4 *v5; // esi
  double v6; // st7
  double v7; // st6
  int v8; // ecx
  int v9; // ecx
  int v10; // ebp
  int v11; // eax
  int v12; // ecx
  int v13; // edi
  int v14; // ebx
  idVec4 *v15; // esi
  double v16; // st7
  double y; // st6
  idVec4 *v18; // eax
  int v19; // ecx
  double v20; // st7
  double v21; // st6
  int v22; // ecx
  int v23; // ebp
  double v24; // st6
  int v25; // eax
  int v26; // ecx
  int v27; // edi
  int v28; // ebx
  idVec4 *v29; // esi
  double v30; // st7
  double v31; // st6
  idVec4 *v32; // eax
  int v33; // ecx
  double v34; // st7
  double v35; // st6
  int v36; // ecx
  int v37; // ebp
  double v38; // st6
  int v39; // eax
  int v40; // ecx
  int v41; // edi
  int v42; // ebx
  idVec4 *v43; // esi
  double v44; // st7
  double v45; // st6
  idVec4 *v46; // eax
  int v47; // ecx
  double v48; // st7
  double v49; // st6
  int v50; // ecx
  int v51; // ebp
  int v52; // ecx
  int v53; // ecx
  int v54; // eax
  int v55; // edi
  int v56; // ebx
  idVec4 *v57; // esi
  double v58; // st7
  double v59; // st6
  int v60; // ecx
  int v61; // ecx
  int v62; // ebp
  int v63; // ecx
  int v64; // ecx

  result = numClipSilEdges;
  v1 = numShadowIndexes;
  if ( numShadowIndexes + 6 * numClipSilEdges <= 98304 )
  {
    v2 = 0;
    if ( numClipSilEdges >= 4 )
    {
      do
      {
        v3 = clipSilEdges[v2][0];
        v4 = clipSilEdges[v2][1];
        v5 = &shadowVerts[v3];
        v6 = v5->z * 1023.0;
        v7 = v5->y * 127.0;
        shadowIndexes[v1] = v3;
        v8 = v1 + 1;
        shadowIndexes[v8] = v4;
        v9 = v8 + 1;
        v10 = v3 + 1;
        v11 = v4 + 1;
        if ( shadowVerts[v4].z * 1023.0 + shadowVerts[v4].y * 127.0 + shadowVerts[v4].x <= v6 + v7 + v5->x )
        {
          shadowIndexes[v9] = v4 + 1;
          v12 = v9 + 1;
          shadowIndexes[v12] = v3;
        }
        else
        {
          shadowIndexes[v9] = v10;
          v12 = v9 + 1;
          shadowIndexes[v12] = v4;
        }
        v13 = clipSilEdges[v2 + 1][0];
        v14 = clipSilEdges[v2 + 1][1];
        shadowIndexes[v12 + 1] = v11;
        v15 = &shadowVerts[v13];
        v16 = v15->z * 1023.0;
        y = v15->y;
        v18 = &shadowVerts[v14];
        v19 = v12 + 2;
        shadowIndexes[v19++] = v10;
        v20 = v16 + y * 127.0 + v15->x;
        shadowIndexes[v19++] = v13;
        v21 = v18->z * 1023.0;
        shadowIndexes[v19] = v14;
        v22 = v19 + 1;
        v23 = v13 + 1;
        v24 = v21 + v18->y * 127.0 + v18->x;
        v25 = v14 + 1;
        if ( v24 <= v20 )
        {
          shadowIndexes[v22] = v14 + 1;
          v26 = v22 + 1;
          shadowIndexes[v26] = v13;
        }
        else
        {
          shadowIndexes[v22] = v23;
          v26 = v22 + 1;
          shadowIndexes[v26] = v14;
        }
        v27 = clipSilEdges[v2 + 2][0];
        v28 = clipSilEdges[v2 + 2][1];
        shadowIndexes[v26 + 1] = v25;
        v29 = &shadowVerts[v27];
        v30 = v29->z * 1023.0;
        v31 = v29->y;
        v32 = &shadowVerts[v28];
        v33 = v26 + 2;
        shadowIndexes[v33++] = v23;
        v34 = v30 + v31 * 127.0 + v29->x;
        shadowIndexes[v33++] = v27;
        v35 = v32->z * 1023.0;
        shadowIndexes[v33] = v28;
        v36 = v33 + 1;
        v37 = v27 + 1;
        v38 = v35 + v32->y * 127.0 + v32->x;
        v39 = v28 + 1;
        if ( v38 <= v34 )
        {
          shadowIndexes[v36] = v28 + 1;
          v40 = v36 + 1;
          shadowIndexes[v40] = v27;
        }
        else
        {
          shadowIndexes[v36] = v37;
          v40 = v36 + 1;
          shadowIndexes[v40] = v28;
        }
        v41 = clipSilEdges[v2 + 3][0];
        v42 = clipSilEdges[v2 + 3][1];
        shadowIndexes[v40 + 1] = v39;
        v43 = &shadowVerts[v41];
        v44 = v43->z * 1023.0;
        v45 = v43->y;
        v46 = &shadowVerts[v42];
        v47 = v40 + 2;
        shadowIndexes[v47++] = v37;
        v48 = v44 + v45 * 127.0 + v43->x;
        shadowIndexes[v47++] = v41;
        v49 = v46->z * 1023.0;
        shadowIndexes[v47] = v42;
        v50 = v47 + 1;
        v51 = v41 + 1;
        if ( v49 + v46->y * 127.0 + v46->x <= v48 )
        {
          shadowIndexes[v50] = v42 + 1;
          v52 = v50 + 1;
          shadowIndexes[v52] = v41;
        }
        else
        {
          shadowIndexes[v50] = v51;
          v52 = v50 + 1;
          shadowIndexes[v52] = v42;
        }
        v53 = v52 + 1;
        shadowIndexes[v53] = v42 + 1;
        v54 = numClipSilEdges;
        shadowIndexes[++v53] = v51;
        v2 += 4;
        v1 = v53 + 1;
      }
      while ( v2 < v54 - 3 );
      result = numClipSilEdges;
      numShadowIndexes = v1;
    }
    if ( v2 < result )
    {
      do
      {
        v55 = clipSilEdges[v2][0];
        v56 = clipSilEdges[v2][1];
        v57 = &shadowVerts[v55];
        v58 = v57->z * 1023.0;
        v59 = v57->y * 127.0;
        shadowIndexes[v1] = v55;
        v60 = v1 + 1;
        shadowIndexes[v60] = v56;
        v61 = v60 + 1;
        v62 = v55 + 1;
        result = v56 + 1;
        if ( shadowVerts[v56].z * 1023.0 + shadowVerts[v56].y * 127.0 + shadowVerts[v56].x <= v58 + v59 + v57->x )
        {
          shadowIndexes[v61] = v56 + 1;
          v63 = v61 + 1;
          shadowIndexes[v63] = v55;
        }
        else
        {
          shadowIndexes[v61] = v62;
          v63 = v61 + 1;
          shadowIndexes[v63] = v56;
        }
        v64 = v63 + 1;
        shadowIndexes[v64++] = result;
        shadowIndexes[v64] = v62;
        ++v2;
        v1 = v64 + 1;
      }
      while ( v2 < numClipSilEdges );
      numShadowIndexes = v1;
    }
  }
  else
  {
    overflowed = 1;
  }
  return result;
}

// FUNC: R_AddSilEdges
void __cdecl R_AddSilEdges(const srfTriangles_s *tri, unsigned __int16 *pointCull, const idPlane *frustum)
{
  const srfTriangles_s *v3; // esi
  int v4; // ecx
  int v5; // edi
  int *p_p1; // ebx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // esi
  int v11; // ecx
  int v12; // ebp
  int v13; // esi
  bool v14; // al
  int v15; // edi
  int v16; // esi
  int v17; // edi
  int v18; // edi
  int v19; // edi
  int v20; // edi
  bool v21; // al
  int v22; // edi
  int v23; // edi
  int v24; // esi
  int v25; // edi
  int v26; // ebp
  int v27; // edi
  int j; // [esp+4h] [ebp-18h]
  int i; // [esp+8h] [ebp-14h]
  int numPlanes; // [esp+Ch] [ebp-10h]
  int v1; // [esp+10h] [ebp-Ch]

  v3 = tri;
  v4 = tri->numIndexes / 3;
  numPlanes = v4;
  i = 0;
  if ( tri->numSilEdges > 0 )
  {
    v5 = numShadowIndexes;
    for ( j = 0; ; ++j )
    {
      p_p1 = &v3->silEdges[j].p1;
      if ( *p_p1 < 0 || *p_p1 > v4 || (v7 = p_p1[1], v7 < 0) || v7 > v4 )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(common.type, "Bad sil planes");
        v5 = numShadowIndexes;
      }
      v8 = *p_p1;
      if ( faceCastsShadow[p_p1[1]] == faceCastsShadow[*p_p1] )
        goto LABEL_29;
      HIWORD(v11) = HIWORD(pointCull);
      v9 = p_p1[3];
      LOWORD(v8) = pointCull[v9];
      v10 = p_p1[2];
      LOWORD(v11) = pointCull[v10];
      if ( (~v8 & ~v11 & 0xFC0) != 0 )
        goto LABEL_29;
      if ( ((unsigned __int16)v8 & (unsigned __int16)v11 & 0xFC0) == 4032 )
      {
        v13 = remap_0[v10];
        v12 = remap_0[v9];
        if ( v13 < 0 || v12 < 0 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "R_AddSilEdges: bad remap[]");
          v5 = numShadowIndexes;
        }
      }
      else
      {
        if ( numShadowVerts + 4 > 98304 )
          goto LABEL_31;
        v12 = numShadowVerts + 2;
        v1 = numShadowVerts;
        if ( !R_ClipLineToLight(
                &tri->verts[p_p1[2]].xyz,
                &tri->verts[v9].xyz,
                (idVec3 *)&shadowVerts[numShadowVerts],
                (idVec3 *)&shadowVerts[numShadowVerts + 2],
                frustum) )
          goto LABEL_29;
        v13 = v1;
        numShadowVerts += 4;
      }
      if ( v5 + 6 > 98304 )
      {
LABEL_31:
        overflowed = 1;
        return;
      }
      if ( faceCastsShadow[p_p1[1]] )
      {
        v14 = PointsOrdered((const idVec3 *)&shadowVerts[v13], (const idVec3 *)&shadowVerts[v12]);
        shadowIndexes[v5] = v13;
        v15 = v5 + 1;
        if ( v14 )
        {
          v16 = v13 + 1;
          shadowIndexes[v15] = v16;
          v17 = v15 + 1;
          shadowIndexes[v17++] = v12;
          shadowIndexes[v17] = v12;
          v18 = v17 + 1;
          shadowIndexes[v18] = v16;
        }
        else
        {
          shadowIndexes[v15] = v12 + 1;
          v20 = v15 + 1;
          shadowIndexes[v20++] = v12;
          shadowIndexes[v20] = v13;
          v18 = v20 + 1;
          shadowIndexes[v18] = v13 + 1;
        }
        v19 = v18 + 1;
        shadowIndexes[v19] = v12 + 1;
      }
      else
      {
        v21 = PointsOrdered((const idVec3 *)&shadowVerts[v13], (const idVec3 *)&shadowVerts[v12]);
        shadowIndexes[v5] = v13;
        v22 = v5 + 1;
        shadowIndexes[v22] = v12;
        v23 = v22 + 1;
        if ( v21 )
        {
          v24 = v13 + 1;
          shadowIndexes[v23] = v24;
          v25 = v23 + 1;
          shadowIndexes[v25++] = v12;
          shadowIndexes[v25] = v12 + 1;
          v19 = v25 + 1;
        }
        else
        {
          v26 = v12 + 1;
          shadowIndexes[v23] = v26;
          v27 = v23 + 1;
          shadowIndexes[v27++] = v13;
          shadowIndexes[v27] = v26;
          v19 = v27 + 1;
          v24 = v13 + 1;
        }
        shadowIndexes[v19] = v24;
      }
      v5 = v19 + 1;
      numShadowIndexes = v5;
LABEL_29:
      v3 = tri;
      if ( ++i >= tri->numSilEdges )
        return;
      v4 = numPlanes;
    }
  }
}

// FUNC: R_ClipTriangleToLight
char __usercall R_ClipTriangleToLight@<al>(
        const idVec3 *a@<edx>,
        const idVec3 *b@<ecx>,
        const idVec3 *c@<eax>,
        int planeBits,
        const idPlane *frustum)
{
  float y; // edi
  float v6; // edx
  float z; // ecx
  float x; // edx
  int v9; // esi
  float v10; // ecx
  float v11; // edx
  int v13; // eax
  int v14; // edi
  clipTri_t *v15; // ebx
  int v16; // ebp
  int v18; // esi
  float *p_z; // eax
  unsigned int v20; // edx
  float *v21; // ecx
  float *v22; // ecx
  float *v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // ecx
  int v27; // edx
  int v28; // eax
  int v29; // eax
  int v30; // ecx
  int v31; // edx
  clipTri_t *v32; // ebx
  int v33; // esi
  int base; // [esp+Ch] [ebp-294h]
  clipTri_t *ct; // [esp+10h] [ebp-290h]
  int v36; // [esp+14h] [ebp-28Ch]
  clipTri_t pingPong[2]; // [esp+18h] [ebp-288h] BYREF

  pingPong[0].verts[0].x = a->x;
  y = a->y;
  pingPong[0].verts[0].z = a->z;
  pingPong[0].verts[1].x = b->x;
  v6 = b->y;
  z = b->z;
  pingPong[0].verts[1].y = v6;
  x = c->x;
  v9 = 0;
  pingPong[0].verts[1].z = z;
  v10 = c->y;
  pingPong[0].verts[2].x = x;
  v11 = c->z;
  pingPong[0].verts[0].y = y;
  pingPong[0].numVerts = 3;
  memset(&pingPong[1], 0, 12);
  pingPong[0].verts[2].y = v10;
  pingPong[0].verts[2].z = v11;
  v13 = 0;
  do
  {
    if ( ((1 << v9) & planeBits) != 0 )
    {
      v13 = R_ChopWinding_0(pingPong, v13, frustum);
      if ( *(&pingPong[0].numVerts + 81 * v13) < 1 )
        return 0;
    }
    ++v9;
    ++frustum;
  }
  while ( v9 < 6 );
  v14 = *(&pingPong[0].numVerts + 81 * v13);
  v15 = (clipTri_t *)((char *)pingPong + 324 * v13);
  v16 = numShadowVerts;
  ct = v15;
  v36 = numShadowVerts + 2 * v14;
  if ( v36 > 98304 )
    goto LABEL_6;
  v18 = 0;
  base = numShadowVerts;
  if ( v14 >= 4 )
  {
    p_z = &shadowVerts[numShadowVerts].z;
    v20 = ((unsigned int)(v14 - 4) >> 2) + 1;
    v21 = &v15->verts[0].z;
    v18 = 4 * v20;
    do
    {
      *(p_z - 2) = *(v21 - 2);
      *(p_z - 1) = *(v21 - 1);
      *p_z = *v21;
      p_z[6] = v21[1];
      p_z[7] = v21[2];
      p_z[8] = v21[3];
      p_z[14] = v21[4];
      p_z[15] = v21[5];
      p_z[16] = v21[6];
      p_z[22] = v21[7];
      p_z[23] = v21[8];
      p_z[24] = v21[9];
      v21 += 12;
      p_z += 32;
      --v20;
    }
    while ( v20 );
    v15 = ct;
  }
  if ( v18 < v14 )
  {
    v22 = &v15->verts[v18].z;
    v23 = &shadowVerts[2 * v18 + v16].z;
    v24 = v14 - v18;
    do
    {
      *(v23 - 2) = *(v22 - 2);
      *(v23 - 1) = *(v22 - 1);
      *v23 = *v22;
      v22 += 3;
      v23 += 8;
      --v24;
    }
    while ( v24 );
  }
  numShadowVerts = v36;
  v25 = numShadowIndexes;
  if ( v14 - 2 + numShadowIndexes + 2 * (v14 - 2) > 98304 )
  {
LABEL_6:
    overflowed = 1;
    return 0;
  }
  else
  {
    if ( v14 > 2 )
    {
      v26 = base + 4;
      v27 = v14 - 2;
      do
      {
        shadowIndexes[v25] = v26;
        v28 = v25 + 1;
        shadowIndexes[v28++] = v26 - 2;
        shadowIndexes[v28] = base;
        v25 = v28 + 1;
        v26 += 2;
        --v27;
      }
      while ( v27 );
      numShadowIndexes = v25;
    }
    v29 = 0;
    if ( v14 > 0 )
    {
      v30 = base;
      v31 = numClipSilEdges;
      v32 = v15 + 1;
      do
      {
        if ( v32->numVerts )
        {
          if ( v31 == 2048 )
            break;
          v33 = base;
          clipSilEdges[v31][0] = v30;
          if ( v29 != v14 - 1 )
            v33 = v30 + 2;
          clipSilEdges[v31++][1] = v33;
        }
        ++v29;
        v32 = (clipTri_t *)((char *)v32 + 4);
        v30 += 2;
      }
      while ( v29 < v14 );
      numClipSilEdges = v31;
    }
    return 1;
  }
}

// FUNC: R_CreateShadowVolumeInFrustum
void __cdecl R_CreateShadowVolumeInFrustum(
        const idRenderEntityLocal *ent,
        const srfTriangles_s *tri,
        const idRenderLightLocal *light,
        const idVec3 lightOrigin,
        const idPlane *frustum,
        const idPlane *farPlane,
        bool makeClippedPlanes)
{
  int v7; // eax
  void *v8; // esp
  int v9; // edi
  int v10; // eax
  int v11; // ecx
  unsigned __int8 *v12; // edx
  int *silIndexes; // ecx
  int v14; // edx
  int v15; // esi
  char *v16; // eax
  int v17; // ecx
  int v18; // eax
  int *v19; // eax
  idDrawVert *v20; // eax
  idVec4 *v21; // ecx
  idDrawVert *v22; // eax
  idVec4 *v23; // ecx
  int y_low; // edx
  idDrawVert *v25; // eax
  idVec4 *v26; // ecx
  unsigned __int16 v27; // cx
  char v28; // al
  int v29; // ecx
  unsigned __int8 *v30; // edx
  int v31; // ecx
  int v32; // edx
  int v33; // esi
  int v34; // edi
  int *v35; // ecx
  int *v36; // edi
  unsigned int v37; // edx
  int v38; // ecx
  int v39; // edx
  int v40; // eax
  int v41; // esi
  int v42; // edx
  unsigned __int16 v43[4]; // [esp+4h] [ebp-48h] BYREF
  int v44[2]; // [esp+Ch] [ebp-40h] BYREF
  int v45; // [esp+14h] [ebp-38h]
  int v46; // [esp+18h] [ebp-34h]
  int v47; // [esp+1Ch] [ebp-30h]
  idVec4 *v48; // [esp+20h] [ebp-2Ch]
  int *v49; // [esp+24h] [ebp-28h]
  indexRef_s *v50; // [esp+28h] [ebp-24h]
  int v51; // [esp+2Ch] [ebp-20h]
  int v52; // [esp+30h] [ebp-1Ch]
  int v53; // [esp+34h] [ebp-18h]
  int firstShadowVert; // [esp+38h] [ebp-14h]
  int v55; // [esp+3Ch] [ebp-10h]
  int v56; // [esp+40h] [ebp-Ch]
  int v57; // [esp+44h] [ebp-8h]
  int v58; // [esp+48h] [ebp-4h]

  v7 = 2 * tri->numVerts + 18;
  LOBYTE(v7) = v7 & 0xFC;
  v8 = alloca(v7);
  R_CalcPointCull(tri, frustum, v43);
  v9 = numShadowVerts;
  v53 = numShadowIndexes;
  v10 = tri->numIndexes / 3;
  v11 = 0;
  firstShadowVert = numShadowVerts;
  numClipSilEdges = 0;
  v51 = v10;
  v56 = 0;
  if ( v10 > 0 )
  {
    v55 = 0;
    do
    {
      v12 = globalFacing;
      faceCastsShadow[v11] = 0;
      if ( !v12[v11] )
      {
        silIndexes = tri->silIndexes;
        HIWORD(v14) = HIWORD(v55);
        v15 = *(int *)((char *)silIndexes + v55 + 4);
        v16 = (char *)silIndexes + v55;
        v17 = *(int *)((char *)silIndexes + v55);
        LOWORD(v14) = v43[v17];
        v18 = *((_DWORD *)v16 + 2);
        v57 = v17;
        v58 = v18;
        v52 = v14;
        if ( (v43[v18] & (unsigned __int8)(LOBYTE(v43[v15]) & v14) & 0x3F) == 0 )
        {
          if ( v9 + 6 > 98304 )
            goto LABEL_29;
          v19 = remap_0;
          if ( (v52 & 0xFC0) == 4032 && remap_0[v17] == -1 )
          {
            remap_0[v17] = v9;
            v20 = &tri->verts[v17];
            v21 = &shadowVerts[v9];
            v21->x = v20->xyz.x;
            v21->y = v20->xyz.y;
            v21->z = v20->xyz.z;
            v19 = remap_0;
            v17 = v57;
            v9 += 2;
            numShadowVerts = v9;
          }
          if ( (v43[v15] & 0xFC0) == 4032 && v19[v15] == -1 )
          {
            v19[v15] = v9;
            v22 = &tri->verts[v15];
            v23 = &shadowVerts[v9];
            v23->x = v22->xyz.x;
            v23->y = v22->xyz.y;
            v23->z = v22->xyz.z;
            v19 = remap_0;
            v17 = v57;
            v9 += 2;
            numShadowVerts = v9;
          }
          y_low = v43[v58] & 0xFC0;
          if ( y_low == 4032 )
          {
            y_low = v58;
            if ( v19[v58] == -1 )
            {
              v19[v58] = v9;
              v25 = &tri->verts[y_low];
              v26 = &shadowVerts[v9];
              v26->x = v25->xyz.x;
              y_low = LODWORD(v25->xyz.y);
              LODWORD(v26->y) = y_low;
              v26->z = v25->xyz.z;
              v19 = remap_0;
              v17 = v57;
              v9 += 2;
              numShadowVerts = v9;
            }
          }
          LOWORD(y_low) = v43[v15];
          LOWORD(v17) = v43[v17];
          v52 = y_low & v17;
          v27 = v43[v58];
          if ( (v27 & (unsigned __int16)v52 & 0xFC0) == 4032 )
          {
            v29 = numShadowIndexes;
            if ( numShadowIndexes + 3 > 98304 )
              goto LABEL_29;
            if ( v19[v57] == -1 || v19[v15] == -1 || v19[v58] == -1 )
            {
              (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
                common.type,
                "R_CreateShadowVolumeInFrustum: bad remap[]");
              v9 = numShadowVerts;
              v19 = remap_0;
              v29 = numShadowIndexes;
            }
            shadowIndexes[v29] = v19[v58];
            shadowIndexes[v29 + 1] = v19[v15];
            v30 = faceCastsShadow;
            v31 = v29 + 2;
            shadowIndexes[v31] = v19[v57];
            numShadowIndexes = v31 + 1;
            v30[v56] = 1;
          }
          else
          {
            v28 = R_ClipTriangleToLight(
                    &tri->verts[v57].xyz,
                    &tri->verts[v15].xyz,
                    &tri->verts[v58].xyz,
                    (v27 ^ 0xFC0 | v43[v15] ^ 0xFC0 | v43[v57] ^ 0xFC0u) >> 6,
                    frustum);
            v9 = numShadowVerts;
            if ( v28 )
              faceCastsShadow[v56] = 1;
          }
        }
      }
      v10 = v51;
      v55 += 12;
      v11 = ++v56;
    }
    while ( v56 < v51 );
  }
  v32 = v53;
  v33 = numShadowIndexes - v53;
  if ( numShadowIndexes != v53 )
  {
    if ( callOptimizer )
    {
      v46 = firstShadowVert;
      v44[0] = numShadowIndexes;
      v47 = indexFrustumNumber;
      v44[1] = v53;
      v45 = v9;
      v48 = shadowVerts;
      v49 = shadowIndexes;
      v50 = indexRef;
      overflowed = (*(int (__thiscall **)(_DWORD, int *, idVec4 *, int *, int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))(**(_DWORD **)common.ip + 164))(
                     *(_DWORD *)common.ip,
                     v44,
                     shadowVerts,
                     &shadowIndexes[v53],
                     numShadowIndexes - v53,
                     LODWORD(farPlane->a),
                     LODWORD(farPlane->b),
                     LODWORD(farPlane->c),
                     LODWORD(farPlane->d),
                     LODWORD(lightOrigin.x),
                     LODWORD(lightOrigin.y),
                     LODWORD(lightOrigin.z));
      numShadowIndexes = v44[0];
      numShadowVerts = v45;
      indexFrustumNumber = v47;
    }
    else
    {
      faceCastsShadow[v10] = 0;
      v34 = numShadowIndexes + v33;
      v51 = numShadowIndexes + v33;
      if ( numShadowIndexes + v33 <= 98304 )
      {
        if ( v33 > 0 )
        {
          v35 = &shadowIndexes[v32 + 1];
          v36 = &shadowIndexes[numShadowIndexes + 1];
          v37 = (v33 - 1) / 3u + 1;
          do
          {
            *(v36 - 1) = v35[1] + 1;
            *v36 = *v35 + 1;
            v36[1] = *(v35 - 1) + 1;
            v35 += 3;
            v36 += 3;
            --v37;
          }
          while ( v37 );
          v34 = v51;
        }
        numShadowIndexes = v34;
        c_caps += 2 * v33;
        if ( makeClippedPlanes )
          R_AddClipSilEdges();
        R_AddSilEdges(tri, v43, frustum);
        c_sils += numShadowIndexes - v34;
        R_ProjectPointsToFarPlane(ent, light, numShadowVerts, farPlane, firstShadowVert);
        v38 = indexFrustumNumber;
        v39 = v53;
        v40 = indexFrustumNumber;
        indexRef[v40].frontCapStart = v53;
        v41 = v39 + v33;
        v42 = numShadowIndexes;
        indexRef[v40].rearCapStart = v41;
        indexRef[v40].silStart = v34;
        indexRef[v40].end = v42;
        indexFrustumNumber = v38 + 1;
      }
      else
      {
LABEL_29:
        overflowed = 1;
      }
    }
  }
}

// FUNC: void __cdecl R_MakeShadowFrustums(class idRenderLightLocal *)
void __cdecl R_MakeShadowFrustums(idRenderLightLocal *light)
{
  int v1; // edi
  float *p_z; // edx
  int v3; // ecx
  idVec3 *p_lightRadius; // eax
  double v5; // st7
  double v6; // st7
  double v7; // st6
  int v8; // ebx
  shadowFrustum_t *v9; // edx
  idVec3 *v10; // eax
  double v11; // st7
  idVec3 *v12; // ecx
  idVec3 *v13; // edi
  double v14; // st6
  double v15; // st5
  double v16; // st4
  double v17; // st7
  long double v18; // st6
  long double v19; // st7
  long double v20; // st5
  unsigned __int8 v22; // c2
  unsigned __int8 v23; // c3
  int v24; // eax
  int v25; // edi
  float *p_b; // edx
  int v27; // ebx
  double v28; // st7
  double v29; // st6
  double v30; // st5
  idVec3 *v31; // ecx
  idVec3 *v32; // ebp
  double v33; // st4
  double v34; // st7
  long double v35; // st6
  long double v36; // st7
  long double v37; // st5
  double v39; // st5
  unsigned __int8 v40; // c2
  unsigned __int8 v41; // c3
  idVec3 *v42; // eax
  double v43; // st7
  double v44; // st6
  double v45; // st5
  double v46; // st4
  double v47; // st7
  long double v48; // st6
  long double v49; // st7
  long double v50; // st5
  unsigned __int8 v52; // c2
  unsigned __int8 v53; // c3
  float *p_c; // eax
  float *v55; // ecx
  int v56; // edx
  double v57; // st7
  double v58; // st6
  float v59; // [esp+Ch] [ebp-D8h]
  float v60; // [esp+Ch] [ebp-D8h]
  float sidePlane; // [esp+10h] [ebp-D4h]
  float sidePlane_4; // [esp+14h] [ebp-D0h]
  float sidePlane_8; // [esp+18h] [ebp-CCh]
  float sidePlane_12; // [esp+1Ch] [ebp-C8h]
  float backPlane; // [esp+20h] [ebp-C4h]
  float backPlane_4; // [esp+24h] [ebp-C0h]
  float backPlane_8; // [esp+28h] [ebp-BCh]
  float backPlane_12; // [esp+2Ch] [ebp-B8h]
  bool centerOutside; // [esp+33h] [ebp-B1h]
  idVec3 temp; // [esp+34h] [ebp-B0h]
  int side; // [esp+40h] [ebp-A4h]
  float v72; // [esp+44h] [ebp-A0h]
  float v73; // [esp+48h] [ebp-9Ch]
  float v74; // [esp+4Ch] [ebp-98h]
  float v75; // [esp+50h] [ebp-94h]
  float v76; // [esp+54h] [ebp-90h]
  float v77; // [esp+5Ch] [ebp-88h]
  float v78; // [esp+60h] [ebp-84h]
  float v79; // [esp+68h] [ebp-7Ch]
  float v80; // [esp+6Ch] [ebp-78h]
  float v81; // [esp+70h] [ebp-74h]
  float v82; // [esp+74h] [ebp-70h]
  float v83; // [esp+78h] [ebp-6Ch]
  float v84; // [esp+7Ch] [ebp-68h]
  idVec3 corners[8]; // [esp+84h] [ebp-60h] BYREF

  if ( light->parms.pointLight )
  {
    centerOutside = 0;
    if ( fabs(light->parms.lightCenter.x) > light->parms.lightRadius.x
      || fabs(light->parms.lightCenter.y) > light->parms.lightRadius.y
      || fabs(light->parms.lightCenter.z) > light->parms.lightRadius.z )
    {
      centerOutside = 1;
    }
    v1 = 0;
    p_z = &corners[0].z;
    do
    {
      v3 = 0;
      p_lightRadius = &light->parms.lightRadius;
      do
      {
        if ( ((1 << v3) & v1) != 0 )
          *((_DWORD *)&temp.x + v3) = LODWORD(p_lightRadius->x);
        else
          *(&temp.x + v3) = -p_lightRadius->x;
        ++v3;
        p_lightRadius = (idVec3 *)((char *)p_lightRadius + 4);
      }
      while ( v3 < 3 );
      ++v1;
      p_z += 3;
      v5 = temp.y * light->parms.axis.mat[1].x
         + temp.z * light->parms.axis.mat[2].x
         + temp.x * light->parms.axis.mat[0].x;
      v73 = temp.x * light->parms.axis.mat[0].y
          + temp.y * light->parms.axis.mat[1].y
          + temp.z * light->parms.axis.mat[2].y;
      v74 = temp.y * light->parms.axis.mat[1].z
          + temp.z * light->parms.axis.mat[2].z
          + temp.x * light->parms.axis.mat[0].z;
      v6 = v5 + light->parms.origin.x;
      v7 = v73 + light->parms.origin.y;
      v81 = v74 + light->parms.origin.z;
      *(p_z - 3) = v81;
      *(p_z - 5) = v6;
      *(p_z - 4) = v7;
    }
    while ( v1 < 8 );
    v8 = 0;
    light->numShadowFrustums = 0;
    side = 0;
    while ( 1 )
    {
      v9 = &light->shadowFrustums[light->numShadowFrustums];
      v10 = &corners[dword_102FD778[4 * v8]];
      v11 = v10->x - corners[dword_102FD774[4 * v8]].x;
      v12 = &corners[dword_102FD774[4 * v8]];
      v13 = &corners[faceCorners[v8][0]];
      v14 = v10->y - v12->y;
      v15 = v10->z - v12->z;
      v83 = v13->x - v12->x;
      v84 = v13->y - v12->y;
      v16 = v13->z - v12->z;
      temp.x = v84 * v15 - v16 * v14;
      backPlane = temp.x;
      temp.y = v16 * v11 - v15 * v83;
      backPlane_4 = temp.y;
      v17 = v14 * v83 - v84 * v11;
      backPlane_8 = v17;
      v18 = temp.x * temp.x + v17 * v17 + temp.y * temp.y;
      if ( v18 == 0.0 )
      {
        v19 = 0.0;
      }
      else
      {
        v20 = 1.0 / sqrt(v18);
        backPlane = temp.x * v20;
        backPlane_4 = temp.y * v20;
        backPlane_8 = v17 * v20;
        v19 = v20 * v18;
      }
      if ( v23 | v22 )
      {
        if ( backPlane_4 == 0.0 )
        {
          if ( backPlane_8 <= 0.0 )
          {
            if ( backPlane_8 != -1.0 )
              backPlane_8 = -1.0;
          }
          else if ( backPlane_8 != 1.0 )
          {
            backPlane_8 = 1.0;
          }
          goto LABEL_50;
        }
        if ( backPlane_8 == 0.0 )
        {
          if ( backPlane_4 <= 0.0 )
          {
            if ( backPlane_4 != -1.0 )
              backPlane_4 = -1.0;
          }
          else if ( backPlane_4 != 1.0 )
          {
            backPlane_4 = 1.0;
          }
          goto LABEL_50;
        }
      }
      else if ( backPlane_4 == 0.0 && backPlane_8 == 0.0 )
      {
        if ( backPlane <= 0.0 )
        {
          if ( backPlane != -1.0 )
            backPlane = -1.0;
        }
        else if ( backPlane != 1.0 )
        {
          backPlane = 1.0;
        }
        goto LABEL_50;
      }
      if ( COERCE_FLOAT(LODWORD(backPlane) & 0x7FFFFFFF) == 1.0 )
      {
        if ( backPlane_4 != 0.0 || backPlane_8 != 0.0 )
        {
          backPlane_8 = 0.0;
LABEL_49:
          backPlane_4 = 0.0;
        }
      }
      else if ( COERCE_FLOAT(LODWORD(backPlane_4) & 0x7FFFFFFF) == 1.0 )
      {
        if ( backPlane != 0.0 || backPlane_8 != 0.0 )
        {
          backPlane_8 = 0.0;
          backPlane = 0.0;
        }
      }
      else if ( COERCE_FLOAT(LODWORD(backPlane_8) & 0x7FFFFFFF) == 1.0 && (backPlane != 0.0 || backPlane_4 != 0.0) )
      {
        backPlane = 0.0;
        goto LABEL_49;
      }
LABEL_50:
      if ( v19 != 0.0 )
        backPlane_12 = -(backPlane * v12->x + backPlane_8 * v12->z + backPlane_4 * v12->y);
      if ( backPlane_8 * light->globalLightOrigin.z
         + backPlane_4 * light->globalLightOrigin.y
         + backPlane * light->globalLightOrigin.x
         + backPlane_12 >= 0.0 )
      {
        v9->planes[5].a = backPlane;
        v9->planes[5].b = backPlane_4;
        v9->planes[5].c = backPlane_8;
        v9->planes[5].d = backPlane_12;
        v9->planes[4].a = backPlane;
        v24 = side;
        v9->planes[4].b = backPlane_4;
        v9->planes[4].c = backPlane_8;
        v9->numPlanes = 6;
        v9->planes[4].d = backPlane_12;
        v25 = 0;
        p_b = &v9->planes[0].b;
        v27 = 4 * v24;
        while ( 1 )
        {
          v28 = light->globalLightOrigin.x - corners[faceCorners[0][v27]].x;
          v29 = light->globalLightOrigin.y - corners[faceCorners[0][v27]].y;
          ++v25;
          v30 = light->globalLightOrigin.z - corners[faceCorners[0][v27]].z;
          v31 = &corners[faceCorners[0][v27]];
          v32 = &corners[faceCorners[side][v25 & 3]];
          v82 = v32->x - v31->x;
          v79 = v82;
          v80 = v32->y - v31->y;
          v33 = v32->z - v31->z;
          v77 = v80 * v30 - v33 * v29;
          *(p_b - 1) = v77;
          v78 = v33 * v28 - v30 * v79;
          *p_b = v78;
          v34 = v29 * v79 - v80 * v28;
          p_b[1] = v34;
          v35 = v77 * v77 + v34 * v34 + v78 * v78;
          if ( v35 == 0.0 )
          {
            v36 = 0.0;
          }
          else
          {
            v37 = 1.0 / sqrt(v35);
            *(p_b - 1) = v77 * v37;
            *p_b = v78 * v37;
            p_b[1] = v34 * v37;
            v36 = v37 * v35;
          }
          v39 = *p_b;
          if ( v41 | v40 )
          {
            if ( v39 == 0.0 )
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
              goto LABEL_90;
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
              goto LABEL_90;
            }
          }
          else if ( v39 == 0.0 && p_b[1] == 0.0 )
          {
            if ( *(p_b - 1) <= 0.0 )
            {
              if ( *((_DWORD *)p_b - 1) != -1082130432 )
                *(p_b - 1) = -1.0;
            }
            else if ( *((_DWORD *)p_b - 1) != 1065353216 )
            {
              *(p_b - 1) = 1.0;
            }
            goto LABEL_90;
          }
          v59 = *(p_b - 1);
          HIBYTE(v59) &= ~0x80u;
          if ( v59 == 1.0 )
          {
            if ( *p_b != 0.0 || p_b[1] != 0.0 )
            {
              p_b[1] = 0.0;
LABEL_89:
              *p_b = 0.0;
            }
          }
          else if ( COERCE_FLOAT(*(_DWORD *)p_b & 0x7FFFFFFF) == 1.0 )
          {
            if ( *(p_b - 1) != 0.0 || p_b[1] != 0.0 )
            {
              p_b[1] = 0.0;
              *(p_b - 1) = 0.0;
            }
          }
          else
          {
            v60 = p_b[1];
            HIBYTE(v60) &= ~0x80u;
            if ( v60 == 1.0 && (*(p_b - 1) != 0.0 || *p_b != 0.0) )
            {
              *(p_b - 1) = 0.0;
              goto LABEL_89;
            }
          }
LABEL_90:
          if ( v36 != 0.0 )
            p_b[2] = -(v31->y * *p_b + v31->x * *(p_b - 1) + v31->z * p_b[1]);
          if ( !centerOutside )
            goto LABEL_134;
          v42 = &corners[faceEdgeAdjacent[0][v27]];
          v43 = v42->x - v31->x;
          v44 = v42->y - v31->y;
          v45 = v42->z - v31->z;
          v72 = v82;
          v73 = v32->y - v31->y;
          v46 = v32->z - v31->z;
          v75 = v73 * v45 - v46 * v44;
          sidePlane = v75;
          v76 = v46 * v43 - v45 * v82;
          sidePlane_4 = v76;
          v47 = v44 * v82 - v73 * v43;
          sidePlane_8 = v47;
          v48 = v47 * v47 + v76 * v76 + v75 * v75;
          if ( v48 == 0.0 )
          {
            v49 = 0.0;
          }
          else
          {
            v50 = 1.0 / sqrt(v48);
            sidePlane = v75 * v50;
            sidePlane_4 = v76 * v50;
            sidePlane_8 = v47 * v50;
            v49 = v50 * v48;
          }
          if ( v53 | v52 )
          {
            if ( sidePlane_4 == 0.0 )
            {
              if ( sidePlane_8 <= 0.0 )
              {
                if ( sidePlane_8 != -1.0 )
                  sidePlane_8 = -1.0;
              }
              else if ( sidePlane_8 != 1.0 )
              {
                sidePlane_8 = 1.0;
              }
              goto LABEL_129;
            }
            if ( sidePlane_8 == 0.0 )
            {
              if ( sidePlane_4 <= 0.0 )
              {
                if ( sidePlane_4 != -1.0 )
                  sidePlane_4 = -1.0;
              }
              else if ( sidePlane_4 != 1.0 )
              {
                sidePlane_4 = 1.0;
              }
              goto LABEL_129;
            }
          }
          else if ( sidePlane_4 == 0.0 && sidePlane_8 == 0.0 )
          {
            if ( sidePlane <= 0.0 )
            {
              if ( sidePlane != -1.0 )
                sidePlane = -1.0;
            }
            else if ( sidePlane != 1.0 )
            {
              sidePlane = 1.0;
            }
            goto LABEL_129;
          }
          if ( COERCE_FLOAT(LODWORD(sidePlane) & 0x7FFFFFFF) == 1.0 )
          {
            if ( sidePlane_4 == 0.0 && sidePlane_8 == 0.0 )
              goto LABEL_129;
            sidePlane_8 = 0.0;
            goto LABEL_128;
          }
          if ( COERCE_FLOAT(LODWORD(sidePlane_4) & 0x7FFFFFFF) == 1.0 )
          {
            if ( sidePlane != 0.0 || sidePlane_8 != 0.0 )
            {
              sidePlane_8 = 0.0;
              sidePlane = 0.0;
            }
            goto LABEL_129;
          }
          if ( COERCE_FLOAT(LODWORD(sidePlane_8) & 0x7FFFFFFF) == 1.0 && (sidePlane != 0.0 || sidePlane_4 != 0.0) )
          {
            sidePlane = 0.0;
LABEL_128:
            sidePlane_4 = 0.0;
          }
LABEL_129:
          if ( v49 != 0.0 )
            sidePlane_12 = -(sidePlane_8 * v31->z + sidePlane_4 * v31->y + sidePlane * v31->x);
          if ( sidePlane_8 * light->globalLightOrigin.z
             + sidePlane_4 * light->globalLightOrigin.y
             + sidePlane * light->globalLightOrigin.x
             + sidePlane_12 < 0.0 )
          {
            *(p_b - 1) = sidePlane;
            *p_b = sidePlane_4;
            p_b[1] = sidePlane_8;
            p_b[2] = sidePlane_12;
          }
          light->shadowFrustums[light->numShadowFrustums].makeClippedPlanes = 1;
LABEL_134:
          ++v27;
          p_b += 4;
          if ( v25 >= 4 )
          {
            ++light->numShadowFrustums;
            v8 = side;
            break;
          }
        }
      }
      side = ++v8;
      if ( v8 >= 6 )
        return;
    }
  }
  light->numShadowFrustums = 1;
  p_c = &light->shadowFrustums[0].planes[0].c;
  v55 = &light->frustum[0].c;
  v56 = 6;
  do
  {
    p_c += 4;
    v57 = -*(v55 - 2);
    v55 += 4;
    --v56;
    v58 = -*(v55 - 5);
    v74 = -*(v55 - 4);
    *(p_c - 4) = v74;
    *(p_c - 6) = v57;
    *(p_c - 5) = v58;
    *(p_c - 3) = -*(v55 - 3);
  }
  while ( v56 );
  light->shadowFrustums[0].makeClippedPlanes = 1;
  light->shadowFrustums[0].numPlanes = 6;
}

// FUNC: struct srfTriangles_s * __cdecl R_CreateShadowVolume(class idRenderEntityLocal const *,struct srfTriangles_s const *,class idRenderLightLocal const *,int,struct srfCullInfo_s &)
srfTriangles_s *__usercall R_CreateShadowVolume@<eax>(
        int a1@<ebp>,
        int a2@<edi>,
        int a3@<esi>,
        const idRenderEntityLocal *ent,
        srfTriangles_s *tri,
        const idRenderLightLocal *light,
        int optimize,
        srfCullInfo_s *cullInfo)
{
  int numIndexes; // eax
  const idRenderLightLocal *v10; // esi
  int v11; // eax
  int v12; // ecx
  int v13; // edx
  int v14; // eax
  void *v15; // esp
  unsigned __int8 *v16; // eax
  int v17; // eax
  void *v18; // esp
  int *v19; // eax
  bool v20; // cc
  shadowFrustum_t *shadowFrustums; // edi
  idPlane *v22; // esi
  bool makeClippedPlanes; // cl
  srfTriangles_s *v24; // esi
  int v25; // edx
  int v26; // eax
  int v27; // eax
  int *p_silStart; // ecx
  int v29; // eax
  int v30; // edi
  idSIMDProcessor_vtbl *v31; // ecx
  int v32; // edi
  int numShadowIndexesNoCaps; // edx
  int *indexes; // eax
  const idPlane *v35; // ecx
  int *p_rearCapStart; // ecx
  int v37; // eax
  int v38; // edi
  idSIMDProcessor_vtbl *v39; // ecx
  int v40; // edi
  int numShadowIndexesNoFrontCaps; // edx
  int *v42; // eax
  const idPlane *v43; // ecx
  indexRef_s *v44; // ecx
  int frontCapStart; // eax
  int rearCapStart; // edi
  idSIMDProcessor_vtbl *v47; // ecx
  int v48; // edi
  int v49; // edx
  int *v50; // eax
  const idPlane *v51; // eax
  int v52; // edx
  char v55; // [esp-81h] [ebp-8Dh] BYREF
  idPlane v56[5]; // [esp-80h] [ebp-8Ch] BYREF
  idPlane v57; // [esp-30h] [ebp-3Ch] BYREF
  idVec3 v58; // [esp-1Ch] [ebp-28h] BYREF
  int i; // [esp-10h] [ebp-1Ch]
  idSIMDProcessor_vtbl *v60; // [esp-Ch] [ebp-18h]
  int *v61; // [esp-8h] [ebp-14h]
  const idPlane *planes; // [esp-4h] [ebp-10h]
  int frustumNum; // [esp+0h] [ebp-Ch]
  int oldFrustumNumber; // [esp+4h] [ebp-8h]
  int retaddr; // [esp+Ch] [ebp+0h]

  frustumNum = a1;
  oldFrustumNumber = retaddr;
  if ( !r_shadows.internalVar->integerValue )
    return 0;
  if ( !tri->numSilEdges )
    return 0;
  numIndexes = tri->numIndexes;
  if ( !numIndexes || !tri->numVerts )
    return 0;
  if ( numIndexes < 0 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_CreateShadowVolume: tri->numIndexes = %i",
      tri->numIndexes);
  if ( tri->numVerts < 0 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "R_CreateShadowVolume: tri->numVerts = %i",
      tri->numVerts);
  ++tr.pc.c_createShadowVolumes;
  if ( !optimize && r_useTurboShadow.internalVar->integerValue )
  {
    if ( tri->primBatchMesh )
      return R_CreateVertexBufferTurboShadowVolume(ent, tri, light, cullInfo);
    if ( tr.backEndRendererHasVertexPrograms && r_useShadowVertexProgram.internalVar->integerValue )
      return R_CreateVertexProgramTurboShadowVolume(ent, tri, light, cullInfo);
    return R_CreateTurboShadowVolume(ent, tri, light, cullInfo);
  }
  if ( tri->primBatchMesh )
    return 0;
  v10 = light;
  R_CalcInteractionFacing(ent, tri, light, cullInfo);
  v11 = tri->numIndexes / 3;
  v12 = 0;
  v13 = 1;
  i = 1;
  planes = 0;
  if ( v11 <= 0 )
    return 0;
  while ( v13 )
  {
    v13 = (unsigned __int8)(cullInfo->facing[v12] & i);
    v12 = (int)&planes->a + 1;
    i = v13;
    planes = (const idPlane *)v12;
    if ( v12 >= v11 )
    {
      if ( v13 )
        return 0;
      break;
    }
  }
  numShadowIndexes = 0;
  v14 = v11 + 19;
  LOBYTE(v14) = v14 & 0xFC;
  numShadowVerts = 0;
  overflowed = 0;
  indexFrustumNumber = 0;
  i = 0;
  callOptimizer = optimize == 2;
  globalFacing = cullInfo->facing;
  v15 = alloca(v14);
  v16 = (unsigned __int8 *)&v55;
  LOBYTE(v16) = (unsigned __int8)&v55 & 0xF0;
  faceCastsShadow = v16;
  v17 = 4 * tri->numVerts + 18;
  LOBYTE(v17) = v17 & 0xFC;
  v18 = alloca(v17);
  v19 = (int *)&v55;
  LOBYTE(v19) = (unsigned __int8)&v55 & 0xF0;
  remap_0 = v19;
  R_GlobalPointToLocal(ent->modelMatrix, &light->globalLightOrigin, &v58);
  v20 = light->numShadowFrustums <= 0;
  v60 = 0;
  if ( !v20 )
  {
    shadowFrustums = light->shadowFrustums;
    do
    {
      v20 = shadowFrustums->numPlanes <= 0;
      v61 = 0;
      if ( !v20 )
      {
        v22 = v56;
        planes = shadowFrustums->planes;
        do
        {
          R_GlobalPlaneToLocal(ent->modelMatrix, planes, v22);
          if ( idBounds::PlaneDistance(&tri->bounds, v22) < -0.1 )
            break;
          ++planes;
          ++v22;
          v20 = (int)v61 + 1 < shadowFrustums->numPlanes;
          v61 = (int *)((char *)v61 + 1);
        }
        while ( v20 );
        v10 = light;
      }
      if ( v61 == (int *)shadowFrustums->numPlanes )
      {
        makeClippedPlanes = shadowFrustums->makeClippedPlanes;
        v61 = (int *)indexFrustumNumber;
        R_CreateShadowVolumeInFrustum(ent, tri, v10, v58, v56, &v57, makeClippedPlanes);
        if ( overflowed )
          return 0;
        if ( (int *)indexFrustumNumber != v61 )
          i |= 1 << (char)v60;
      }
      ++shadowFrustums;
      v20 = (int)&v60->GetName + 1 < v10->numShadowFrustums;
      v60 = (idSIMDProcessor_vtbl *)((char *)v60 + 1);
    }
    while ( v20 );
  }
  if ( !numShadowIndexes )
    return 0;
  if ( numShadowVerts > 98304 || numShadowIndexes > 98304 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Shadow volume exceeded allocation");
  v24 = R_AllocStaticTriSurf();
  v24->bounds.b[0].z = idMath::INFINITY;
  v25 = numShadowIndexes;
  v24->bounds.b[0].y = idMath::INFINITY;
  v26 = numShadowVerts;
  v24->bounds.b[0].x = idMath::INFINITY;
  v24->bounds.b[1].z = -1.0e30;
  v24->bounds.b[1].y = -1.0e30;
  v24->bounds.b[1].x = -1.0e30;
  v24->numVerts = v26;
  v24->numIndexes = v25;
  R_AllocStaticTriSurfShadowVerts(v24, v26);
  ((void (__fastcall *)(idSIMDProcessor *, shadowCache_s *, idVec4 *, int, int, int))SIMDProcessor->Memcpy)(
    SIMDProcessor,
    v24->shadowVertexes,
    shadowVerts,
    16 * v24->numVerts,
    a2,
    a3);
  R_AllocStaticTriSurfIndexes(v24, v24->numIndexes);
  v27 = indexFrustumNumber;
  v24->shadowCapPlaneBits = i;
  v24->numShadowIndexesNoCaps = 0;
  planes = 0;
  if ( v27 > 0 )
  {
    p_silStart = &indexRef[0].silStart;
    for ( i = (int)&indexRef[0].silStart; ; p_silStart = (int *)i )
    {
      v29 = *p_silStart;
      v30 = p_silStart[1];
      v31 = SIMDProcessor->__vftable;
      v32 = v30 - v29;
      planes = (const idPlane *)(4 * v32);
      numShadowIndexesNoCaps = v24->numShadowIndexesNoCaps;
      v61 = &shadowIndexes[v29];
      indexes = v24->indexes;
      v60 = v31;
      v31->Memcpy(SIMDProcessor, &indexes[numShadowIndexesNoCaps], v61, 4 * v32);
      v35 = planes;
      v27 = indexFrustumNumber;
      v24->numShadowIndexesNoCaps += v32;
      i += 16;
      planes = (const idPlane *)((char *)&v35->a + 1);
      if ( (int)&v35->a + 1 >= v27 )
        break;
    }
  }
  v24->numShadowIndexesNoFrontCaps = v24->numShadowIndexesNoCaps;
  planes = 0;
  if ( v27 > 0 )
  {
    p_rearCapStart = &indexRef[0].rearCapStart;
    for ( i = (int)&indexRef[0].rearCapStart; ; p_rearCapStart = (int *)i )
    {
      v37 = *p_rearCapStart;
      v38 = p_rearCapStart[1];
      v39 = SIMDProcessor->__vftable;
      v40 = v38 - v37;
      planes = (const idPlane *)(4 * v40);
      numShadowIndexesNoFrontCaps = v24->numShadowIndexesNoFrontCaps;
      v61 = &shadowIndexes[v37];
      v42 = v24->indexes;
      v60 = v39;
      v39->Memcpy(SIMDProcessor, &v42[numShadowIndexesNoFrontCaps], v61, 4 * v40);
      v43 = planes;
      v27 = indexFrustumNumber;
      v24->numShadowIndexesNoFrontCaps += v40;
      i += 16;
      planes = (const idPlane *)((char *)&v43->a + 1);
      if ( (int)&v43->a + 1 >= v27 )
        break;
    }
  }
  v24->numIndexes = v24->numShadowIndexesNoFrontCaps;
  planes = 0;
  if ( v27 > 0 )
  {
    v44 = indexRef;
    for ( i = (int)indexRef; ; v44 = (indexRef_s *)i )
    {
      frontCapStart = v44->frontCapStart;
      rearCapStart = v44->rearCapStart;
      v47 = SIMDProcessor->__vftable;
      v48 = rearCapStart - frontCapStart;
      planes = (const idPlane *)(4 * v48);
      v49 = v24->numIndexes;
      v61 = &shadowIndexes[frontCapStart];
      v50 = v24->indexes;
      v60 = v47;
      v47->Memcpy(SIMDProcessor, &v50[v49], v61, 4 * v48);
      v51 = planes;
      v24->numIndexes += v48;
      i += 16;
      planes = (const idPlane *)((char *)&v51->a + 1);
      if ( (int)&v51->a + 1 >= indexFrustumNumber )
        break;
    }
  }
  v52 = **(_DWORD **)common.ip;
  planes = (const idPlane *)v24;
  (*(void (__thiscall **)(_DWORD, int))(v52 + 160))(*(_DWORD *)common.ip, optimize);
  return v24;
}
