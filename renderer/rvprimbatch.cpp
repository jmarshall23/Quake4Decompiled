
// FUNC: public: void __thiscall rvPrimBatch::LoadMatrixPaletteIntoVPParams(float const *)
void __thiscall rvPrimBatch::LoadMatrixPaletteIntoVPParams(rvPrimBatch *this, const float *skinToModelTransforms)
{
  int v3; // ebx
  unsigned int v4; // esi
  const float *v5; // edi
  unsigned int v6; // esi

  if ( this->m_transformPalette )
  {
    v3 = 0;
    v4 = 0;
    if ( this->m_numTransforms > 0 )
    {
      v5 = skinToModelTransforms + 8;
      do
      {
        qglProgramEnvParameter4fvARB(0x8620u, v4, v5 - 8);
        v6 = v4 + 1;
        qglProgramEnvParameter4fvARB(0x8620u, v6++, v5 - 4);
        qglProgramEnvParameter4fvARB(0x8620u, v6, v5);
        ++v3;
        v4 = v6 + 1;
        v5 += 16;
      }
      while ( v3 < this->m_numTransforms );
    }
  }
}

// FUNC: public: int __thiscall rvPrimBatch::FlipOutsideBackFaces(unsigned char *,unsigned char const *,class rvIndexBuffer &)
int __thiscall rvPrimBatch::FlipOutsideBackFaces(
        rvPrimBatch *this,
        unsigned __int8 *facing,
        const unsigned __int8 *cullBits,
        rvIndexBuffer *indexBuffer)
{
  int v4; // esi
  int v5; // ebp
  unsigned __int16 *v6; // eax
  unsigned __int16 *v7; // esi
  unsigned __int8 *v8; // ecx
  unsigned __int16 *v9; // esi
  unsigned __int8 *v10; // ecx
  void *indexMemPtr; // [esp+10h] [ebp-4h] BYREF

  v4 = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  v5 = 0;
  rvIndexBuffer::Lock(indexBuffer, this->m_silTraceGeoSpec.m_indexStart, v4, 1u, &indexMemPtr);
  v6 = (unsigned __int16 *)indexMemPtr;
  if ( (indexBuffer->m_flags & 4) != 0 )
  {
    v7 = (unsigned __int16 *)((char *)indexMemPtr + 2 * v4);
    if ( indexMemPtr < v7 )
    {
      v8 = facing;
      do
      {
        if ( !*v8 )
        {
          if ( ((unsigned __int8)(cullBits[v6[1]] & cullBits[v6[2]]) & cullBits[*v6]) != 0 )
            *v8 = 1;
          else
            ++v5;
        }
        v6 += 3;
        ++v8;
      }
      while ( v6 < v7 );
    }
  }
  else
  {
    v9 = (unsigned __int16 *)((char *)indexMemPtr + 4 * v4);
    if ( indexMemPtr < v9 )
    {
      v10 = facing;
      do
      {
        if ( !*v10 )
        {
          if ( ((unsigned __int8)(cullBits[*(_DWORD *)v6] & cullBits[*((_DWORD *)v6 + 2)]) & cullBits[*((_DWORD *)v6 + 1)]) != 0 )
            *v10 = 1;
          else
            ++v5;
        }
        v6 += 6;
        ++v10;
      }
      while ( v6 < v9 );
    }
  }
  rvIndexBuffer::Unlock(indexBuffer);
  return v5;
}

// FUNC: public: int __thiscall rvPrimBatch::CreateSilShadowVolTris(int *,unsigned char const *,struct silEdge_t *)
int __thiscall rvPrimBatch::CreateSilShadowVolTris(
        rvPrimBatch *this,
        int *shadowIndices,
        const unsigned __int8 *facing,
        silEdge_t *silEdgeBuffer)
{
  int *v4; // eax
  int m_vertexStart; // edi
  silEdge_t *v6; // esi
  silEdge_t *v7; // ecx
  const unsigned __int8 *v8; // ebp
  unsigned int v9; // ebx
  int v10; // edx
  int v11; // ecx
  silEdge_t *endSil; // [esp+Ch] [ebp-4h]
  unsigned int silEdgeBuffera; // [esp+1Ch] [ebp+Ch]

  v4 = shadowIndices;
  m_vertexStart = this->m_shadowVolGeoSpec.m_vertexStart;
  v6 = &silEdgeBuffer[this->m_silEdgeStart];
  v7 = &v6[this->m_silEdgeCount];
  endSil = v7;
  if ( v6 < v7 )
  {
    v8 = facing;
    do
    {
      v9 = v8[v6->p1];
      silEdgeBuffera = v8[v6->p2];
      if ( v9 != silEdgeBuffera )
      {
        v10 = v6->v2;
        v11 = 2 * v6->v1;
        *v4 = v11 + m_vertexStart;
        v10 *= 2;
        v4[1] = m_vertexStart + (v9 ^ v10);
        v4[2] = m_vertexStart + (silEdgeBuffera ^ v10);
        v4[3] = m_vertexStart + (silEdgeBuffera ^ v11);
        v8 = facing;
        v4[4] = m_vertexStart + (v9 ^ v11);
        v7 = endSil;
        v4[5] = m_vertexStart + (v10 ^ 1);
        v4 += 6;
      }
      ++v6;
    }
    while ( v6 < v7 );
  }
  return v4 - shadowIndices;
}

// FUNC: public: int __thiscall rvPrimBatch::CreateFrontBackShadowVolTris(int *,unsigned char const *,class rvIndexBuffer &)
int __thiscall rvPrimBatch::CreateFrontBackShadowVolTris(
        rvPrimBatch *this,
        int *shadowIndices,
        const unsigned __int8 *facing,
        rvIndexBuffer *indexBuffer)
{
  int m_vertexStart; // edi
  int v5; // ebp
  int *v6; // esi
  unsigned __int16 *v7; // ebx
  unsigned int *v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // ebp
  int v12; // ecx
  unsigned int *v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // ebp
  int v17; // ecx
  void *indexMemPtr; // [esp+10h] [ebp-8h] BYREF
  unsigned int *endIndex32; // [esp+14h] [ebp-4h]

  m_vertexStart = this->m_shadowVolGeoSpec.m_vertexStart;
  v5 = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  rvIndexBuffer::Lock(indexBuffer, this->m_silTraceGeoSpec.m_indexStart, v5, 1u, &indexMemPtr);
  v6 = shadowIndices;
  v7 = (unsigned __int16 *)indexMemPtr;
  if ( (indexBuffer->m_flags & 4) != 0 )
  {
    v8 = (unsigned int *)((char *)indexMemPtr + 2 * v5);
    endIndex32 = v8;
    if ( indexMemPtr < v8 )
    {
      do
      {
        if ( !*facing )
        {
          v9 = v7[2];
          v10 = 2 * *v7;
          v11 = v10 + m_vertexStart;
          v12 = 2 * v7[1];
          v6[3] = m_vertexStart + (v10 ^ 1);
          v9 *= 2;
          v6[4] = m_vertexStart + (v12 ^ 1);
          v6[1] = v12 + m_vertexStart;
          v8 = endIndex32;
          v6[2] = v11;
          *v6 = v9 + m_vertexStart;
          v6[5] = m_vertexStart + (v9 ^ 1);
          v6 += 6;
        }
        ++facing;
        v7 += 3;
      }
      while ( v7 < (unsigned __int16 *)v8 );
    }
  }
  else
  {
    v13 = (unsigned int *)((char *)indexMemPtr + 4 * v5);
    endIndex32 = v13;
    if ( indexMemPtr < v13 )
    {
      do
      {
        if ( !*facing )
        {
          v14 = *((_DWORD *)v7 + 2);
          v15 = 2 * *(_DWORD *)v7;
          v16 = v15 + m_vertexStart;
          v17 = 2 * *((_DWORD *)v7 + 1);
          v6[3] = m_vertexStart + (v15 ^ 1);
          v14 *= 2;
          v6[4] = m_vertexStart + (v17 ^ 1);
          v6[1] = v17 + m_vertexStart;
          v13 = endIndex32;
          v6[2] = v16;
          *v6 = v14 + m_vertexStart;
          v6[5] = m_vertexStart + (v14 ^ 1);
          v6 += 6;
        }
        ++facing;
        v7 += 6;
      }
      while ( v7 < (unsigned __int16 *)v13 );
    }
  }
  rvIndexBuffer::Unlock(indexBuffer);
  return v6 - shadowIndices;
}

// FUNC: public: void __thiscall rvPrimBatch::FindOverlayTriangles(struct overlayVertex_t *,int &,int *,int &,unsigned char const *,class idVec2 const *,int,class rvIndexBuffer &)
void __thiscall rvPrimBatch::FindOverlayTriangles(
        rvPrimBatch *this,
        overlayVertex_t *overlayVerts,
        int *numVerts,
        int *overlayIndexes,
        int *numIndices,
        const unsigned __int8 *cullBits,
        const idVec2 *texCoords,
        int vertexBase,
        rvIndexBuffer *rfSilTraceIB)
{
  int m_vertexCount; // edi
  int v11; // eax
  void *v12; // esp
  int v13; // edi
  unsigned int *v14; // edx
  bool v15; // zf
  const unsigned __int8 *v16; // ebx
  int v19; // edi
  unsigned __int8 v20; // dl
  int *v21; // edi
  int v22; // edx
  int *v23; // edi
  const unsigned __int8 *v24; // ebx
  int v27; // edi
  unsigned __int8 v28; // dl
  int *v29; // edi
  int v30; // edx
  int *v31; // edi
  _DWORD v32[3]; // [esp+0h] [ebp-1Ch] BYREF
  unsigned int *endIndex32; // [esp+Ch] [ebp-10h]
  void *indexMemPtr; // [esp+10h] [ebp-Ch] BYREF
  int numSilTraceIndices; // [esp+14h] [ebp-8h]
  unsigned int *index32; // [esp+18h] [ebp-4h]
  int v1; // [esp+24h] [ebp+8h]
  int v1a; // [esp+24h] [ebp+8h]
  int v3; // [esp+28h] [ebp+Ch]
  int v3a; // [esp+28h] [ebp+Ch]

  m_vertexCount = this->m_silTraceGeoSpec.m_vertexCount;
  numSilTraceIndices = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  m_vertexCount *= 4;
  v11 = m_vertexCount + 18;
  LOBYTE(v11) = (m_vertexCount + 18) & 0xFC;
  v12 = alloca(v11);
  SIMDProcessor->Memset(SIMDProcessor, v32, -1, m_vertexCount);
  v13 = numSilTraceIndices;
  rvIndexBuffer::Lock(rfSilTraceIB, this->m_silTraceGeoSpec.m_indexStart, numSilTraceIndices, 1u, &indexMemPtr);
  v14 = (unsigned int *)indexMemPtr;
  v15 = (rfSilTraceIB->m_flags & 4) == 0;
  index32 = (unsigned int *)indexMemPtr;
  if ( v15 )
  {
    endIndex32 = (unsigned int *)((char *)indexMemPtr + 4 * v13);
    if ( indexMemPtr < endIndex32 )
    {
      v24 = cullBits;
      do
      {
        v1a = *v14;
        v27 = v14[1];
        v3a = v14[2];
        v28 = v24[v27] & v24[v3a];
        numSilTraceIndices = v27;
        if ( (v28 & v24[v1a]) == 0 )
        {
          if ( v32[v1a] == -1 )
          {
            v32[v1a] = *numVerts;
            overlayVerts[*numVerts].vertexNum = v1a + vertexBase;
            *(idVec2 *)overlayVerts[(*numVerts)++].st = texCoords[v1a];
          }
          overlayIndexes[*numIndices] = v32[v1a];
          v29 = numIndices;
          v30 = numSilTraceIndices;
          ++*numIndices;
          if ( v32[v30] == -1 )
          {
            v32[v30] = *numVerts;
            overlayVerts[*numVerts].vertexNum = v30 + vertexBase;
            *(idVec2 *)overlayVerts[(*numVerts)++].st = texCoords[v30];
            v29 = numIndices;
          }
          overlayIndexes[*v29] = v32[v30];
          v31 = numIndices;
          ++*numIndices;
          if ( v32[v3a] == -1 )
          {
            v32[v3a] = *numVerts;
            overlayVerts[*numVerts].vertexNum = v3a + vertexBase;
            *(idVec2 *)overlayVerts[(*numVerts)++].st = texCoords[v3a];
            v31 = numIndices;
          }
          overlayIndexes[*v31] = v32[v3a];
          ++*numIndices;
          v24 = cullBits;
        }
        v14 = index32 + 3;
        index32 += 3;
      }
      while ( index32 < endIndex32 );
    }
  }
  else
  {
    endIndex32 = (unsigned int *)((char *)indexMemPtr + 2 * v13);
    if ( indexMemPtr < endIndex32 )
    {
      v16 = cullBits;
      do
      {
        v1 = *(unsigned __int16 *)v14;
        v19 = *((unsigned __int16 *)v14 + 1);
        v3 = *((unsigned __int16 *)v14 + 2);
        v20 = v16[v19] & v16[v3];
        numSilTraceIndices = v19;
        if ( (v20 & v16[v1]) == 0 )
        {
          if ( v32[v1] == -1 )
          {
            v32[v1] = *numVerts;
            overlayVerts[*numVerts].vertexNum = v1 + vertexBase;
            *(idVec2 *)overlayVerts[(*numVerts)++].st = texCoords[v1];
          }
          overlayIndexes[*numIndices] = v32[v1];
          v21 = numIndices;
          v22 = numSilTraceIndices;
          ++*numIndices;
          if ( v32[v22] == -1 )
          {
            v32[v22] = *numVerts;
            overlayVerts[*numVerts].vertexNum = v22 + vertexBase;
            *(idVec2 *)overlayVerts[(*numVerts)++].st = texCoords[v22];
            v21 = numIndices;
          }
          overlayIndexes[*v21] = v32[v22];
          v23 = numIndices;
          ++*numIndices;
          if ( v32[v3] == -1 )
          {
            v32[v3] = *numVerts;
            overlayVerts[*numVerts].vertexNum = v3 + vertexBase;
            *(idVec2 *)overlayVerts[(*numVerts)++].st = texCoords[v3];
            v23 = numIndices;
          }
          overlayIndexes[*v23] = v32[v3];
          ++*numIndices;
          v16 = cullBits;
        }
        v14 = (unsigned int *)((char *)index32 + 6);
        index32 = (unsigned int *)((char *)index32 + 6);
      }
      while ( index32 < endIndex32 );
    }
  }
  rvIndexBuffer::Unlock(rfSilTraceIB);
}

// FUNC: public: void __thiscall rvPrimBatch::GetTextureBounds(float (* const)[2],class rvVertexBuffer &)
void __thiscall rvPrimBatch::GetTextureBounds(rvPrimBatch *this, float (*bounds)[2], rvVertexBuffer *drawVertexBuffer)
{
  rvVertexBuffer *v3; // ebp
  int v5; // edi
  rvVertexBuffer *v6; // ecx
  int v7; // ebx
  bool v8; // cc
  int srcStride; // [esp+Ch] [ebp-4h] BYREF

  v3 = drawVertexBuffer;
  rvVertexBuffer::LockTextureCoordinate(
    drawVertexBuffer,
    0,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&drawVertexBuffer,
    &srcStride);
  v5 = 0;
  if ( this->m_drawGeoSpec.m_vertexCount > 0 )
  {
    v6 = drawVertexBuffer;
    v7 = srcStride;
    do
    {
      if ( *(float *)&v6->m_format.m_flags < (double)(*bounds)[0] )
        LODWORD((*bounds)[0]) = v6->m_format.m_flags;
      if ( *(float *)&v6->m_format.m_flags > (double)(*bounds)[2] )
        LODWORD((*bounds)[2]) = v6->m_format.m_flags;
      if ( *(float *)&v6->m_format.m_dimensions < (double)(*bounds)[1] )
        LODWORD((*bounds)[1]) = v6->m_format.m_dimensions;
      if ( *(float *)&v6->m_format.m_dimensions > (double)(*bounds)[3] )
        LODWORD((*bounds)[3]) = v6->m_format.m_dimensions;
      v6 = (rvVertexBuffer *)((char *)v6 + v7);
      v8 = ++v5 < this->m_drawGeoSpec.m_vertexCount;
      drawVertexBuffer = v6;
    }
    while ( v8 );
  }
  rvVertexBuffer::Unlock(v3);
}

// FUNC: public: void __thiscall rvPrimBatch::CopyDrawVertices(class idDrawVert *,class rvVertexBuffer &)
void __thiscall rvPrimBatch::CopyDrawVertices(
        rvPrimBatch *this,
        idDrawVert *destDrawVerts,
        idDrawVert *drawVertexBuffer)
{
  idDrawVert *v4; // ebx
  unsigned __int8 *v5; // ecx
  float *v6; // ebp
  float *v7; // edi
  float *v8; // esi
  float *p_z; // eax
  double v10; // st7
  double v11; // st6
  float *v12; // esi
  double v13; // st7
  double v14; // st6
  float *v15; // edi
  double v16; // st7
  double v17; // st6
  float *v18; // edx
  float *v19; // ebp
  double v20; // st7
  double v21; // st6
  float *v22; // ebx
  float *v23; // edx
  unsigned __int8 *v24; // ecx
  double v25; // st7
  double v26; // st6
  double v27; // st7
  double v28; // st6
  double v29; // st7
  double v30; // st6
  float *v31; // edx
  double v32; // st7
  double v33; // st6
  float *v34; // ebx
  float *v35; // edx
  float *v36; // esi
  float *v37; // edi
  float *v38; // ebp
  unsigned __int8 *v39; // ecx
  double v40; // st7
  double v41; // st6
  float *v42; // esi
  double v43; // st7
  double v44; // st6
  float *v45; // edi
  double v46; // st7
  double v47; // st6
  float *v48; // edx
  float *v49; // ebp
  double v50; // st7
  double v51; // st6
  float *v52; // ebx
  float *v53; // edx
  unsigned __int8 *v54; // ecx
  double v55; // st7
  double v56; // st6
  double v57; // st7
  double v58; // st6
  double v59; // st7
  double v60; // st6
  float *v61; // edx
  double v62; // st7
  double v63; // st6
  float *v64; // ebx
  float *v65; // edx
  bool v66; // cc
  float *v67; // eax
  double v68; // st7
  double v69; // st6
  double v70; // st7
  double v71; // st6
  double v72; // st7
  double v73; // st6
  float *v74; // edx
  double v75; // st7
  double v76; // st6
  float *v77; // edx
  float *texCoordSrc; // [esp+10h] [ebp-34h] BYREF
  float *binormalSrc; // [esp+14h] [ebp-30h] BYREF
  float *positionSrc; // [esp+18h] [ebp-2Ch] BYREF
  float *normalSrc; // [esp+1Ch] [ebp-28h] BYREF
  float *tangentSrc; // [esp+20h] [ebp-24h] BYREF
  unsigned __int8 *diffuseColorSrc; // [esp+24h] [ebp-20h] BYREF
  int positionStride; // [esp+28h] [ebp-1Ch] BYREF
  int normalStride; // [esp+2Ch] [ebp-18h] BYREF
  int tangentStride; // [esp+30h] [ebp-14h] BYREF
  int binormalStride; // [esp+34h] [ebp-10h] BYREF
  int texCoordStride; // [esp+38h] [ebp-Ch] BYREF
  int diffuseColorStride; // [esp+3Ch] [ebp-8h] BYREF
  idDrawVert *destVert; // [esp+40h] [ebp-4h]
  idDrawVert *destDrawVertsa; // [esp+48h] [ebp+4h]

  rvVertexBuffer::LockPosition(
    (rvVertexBuffer *)drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&positionSrc,
    &positionStride);
  rvVertexBuffer::LockNormal(
    (rvVertexBuffer *)drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&normalSrc,
    &normalStride);
  rvVertexBuffer::LockBinormal(
    (rvVertexBuffer *)drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&binormalSrc,
    &binormalStride);
  rvVertexBuffer::LockTangent(
    (rvVertexBuffer *)drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&tangentSrc,
    &tangentStride);
  rvVertexBuffer::LockTextureCoordinate(
    (rvVertexBuffer *)drawVertexBuffer,
    0,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&texCoordSrc,
    &texCoordStride);
  rvVertexBuffer::LockDiffuseColor(
    (rvVertexBuffer *)drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    &diffuseColorSrc,
    &diffuseColorStride);
  v4 = destDrawVerts;
  destDrawVertsa = &destDrawVerts[this->m_drawGeoSpec.m_vertexCount];
  destVert = v4;
  v5 = diffuseColorSrc;
  v6 = tangentSrc;
  v7 = normalSrc;
  v8 = positionSrc;
  if ( ((char *)destDrawVertsa - (char *)v4 + 63) / 64 >= 4 )
  {
    p_z = &v4->normal.z;
    do
    {
      v10 = v8[2];
      v11 = v8[1];
      v4->xyz.x = *v8;
      *(p_z - 5) = v11;
      v12 = (float *)((char *)v8 + positionStride);
      *(p_z - 4) = v10;
      v13 = v7[2];
      v14 = v7[1];
      *(p_z - 2) = *v7;
      *(p_z - 1) = v14;
      v15 = (float *)((char *)v7 + normalStride);
      *p_z = v13;
      v16 = v6[2];
      v17 = v6[1];
      p_z[2] = *v6;
      p_z[3] = v17;
      v18 = binormalSrc;
      v19 = (float *)((char *)v6 + tangentStride);
      p_z[4] = v16;
      v20 = v18[2];
      v21 = v18[1];
      p_z[5] = *v18;
      p_z[6] = v21;
      v22 = texCoordSrc;
      v23 = (float *)((char *)v18 + binormalStride);
      p_z[7] = v20;
      p_z[8] = *v22;
      p_z[9] = texCoordSrc[1];
      *((_BYTE *)p_z - 12) = *v5;
      *((_BYTE *)p_z - 11) = v5[1];
      *((_BYTE *)p_z - 10) = v5[2];
      *((_BYTE *)p_z - 9) = v5[3];
      binormalSrc = v23;
      texCoordSrc = (float *)((char *)texCoordSrc + texCoordStride);
      v24 = &v5[diffuseColorStride];
      positionSrc = v12;
      normalSrc = v15;
      tangentSrc = v19;
      diffuseColorSrc = v24;
      v25 = v12[2];
      v26 = v12[1];
      p_z[10] = *v12;
      p_z[11] = v26;
      p_z[12] = v25;
      v27 = v15[2];
      v28 = v15[1];
      p_z[14] = *v15;
      p_z[15] = v28;
      p_z[16] = v27;
      v29 = v19[2];
      v30 = v19[1];
      p_z[18] = *v19;
      v31 = binormalSrc;
      p_z[19] = v30;
      p_z[20] = v29;
      v32 = v31[2];
      v33 = v31[1];
      p_z[21] = *v31;
      v34 = texCoordSrc;
      p_z[22] = v33;
      p_z[23] = v32;
      p_z[24] = *v34;
      p_z[25] = texCoordSrc[1];
      *((_BYTE *)p_z + 52) = *v24;
      *((_BYTE *)p_z + 53) = v24[1];
      v35 = (float *)((char *)v31 + binormalStride);
      *((_BYTE *)p_z + 54) = v24[2];
      LOBYTE(v34) = v24[3];
      v36 = (float *)((char *)v12 + positionStride);
      v37 = (float *)((char *)v15 + normalStride);
      v38 = (float *)((char *)v19 + tangentStride);
      v39 = &v24[diffuseColorStride];
      *((_BYTE *)p_z + 55) = (_BYTE)v34;
      binormalSrc = v35;
      texCoordSrc = (float *)((char *)texCoordSrc + texCoordStride);
      positionSrc = v36;
      normalSrc = v37;
      tangentSrc = v38;
      diffuseColorSrc = v39;
      v40 = v36[2];
      v41 = v36[1];
      p_z[26] = *v36;
      p_z[27] = v41;
      v42 = (float *)((char *)v36 + positionStride);
      p_z[28] = v40;
      v43 = v37[2];
      v44 = v37[1];
      p_z[30] = *v37;
      p_z[31] = v44;
      v45 = (float *)((char *)v37 + normalStride);
      p_z[32] = v43;
      v46 = v38[2];
      v47 = v38[1];
      p_z[34] = *v38;
      v48 = binormalSrc;
      p_z[35] = v47;
      v49 = (float *)((char *)v38 + tangentStride);
      p_z[36] = v46;
      v50 = v48[2];
      v51 = v48[1];
      p_z[37] = *v48;
      v52 = texCoordSrc;
      p_z[38] = v51;
      v53 = (float *)((char *)v48 + binormalStride);
      p_z[39] = v50;
      p_z[40] = *v52;
      p_z[41] = texCoordSrc[1];
      *((_BYTE *)p_z + 116) = *v39;
      *((_BYTE *)p_z + 117) = v39[1];
      *((_BYTE *)p_z + 118) = v39[2];
      LOBYTE(v52) = v39[3];
      binormalSrc = v53;
      texCoordSrc = (float *)((char *)texCoordSrc + texCoordStride);
      v54 = &v39[diffuseColorStride];
      *((_BYTE *)p_z + 119) = (_BYTE)v52;
      positionSrc = v42;
      normalSrc = v45;
      tangentSrc = v49;
      diffuseColorSrc = v54;
      v55 = v42[2];
      v56 = v42[1];
      p_z[42] = *v42;
      p_z[43] = v56;
      p_z[44] = v55;
      v57 = v45[2];
      v58 = v45[1];
      p_z[46] = *v45;
      p_z[47] = v58;
      v8 = (float *)((char *)v42 + positionStride);
      p_z[48] = v57;
      v59 = v49[2];
      v7 = (float *)((char *)v45 + normalStride);
      v60 = v49[1];
      p_z[50] = *v49;
      v61 = binormalSrc;
      p_z[51] = v60;
      v6 = (float *)((char *)v49 + tangentStride);
      p_z[52] = v59;
      v62 = v61[2];
      p_z += 64;
      v63 = v61[1];
      *(p_z - 11) = *v61;
      v64 = texCoordSrc;
      *(p_z - 10) = v63;
      v65 = (float *)((char *)v61 + binormalStride);
      *(p_z - 9) = v62;
      *(p_z - 8) = *v64;
      *(p_z - 7) = texCoordSrc[1];
      *((_BYTE *)p_z - 76) = *v54;
      *((_BYTE *)p_z - 75) = v54[1];
      *((_BYTE *)p_z - 74) = v54[2];
      LOBYTE(v64) = v54[3];
      v5 = &v54[diffuseColorStride];
      binormalSrc = v65;
      texCoordSrc = (float *)((char *)texCoordSrc + texCoordStride);
      *((_BYTE *)p_z - 73) = (_BYTE)v64;
      v4 = destVert + 4;
      v66 = (int)&destVert[4] < (int)&destDrawVertsa[-3];
      positionSrc = v8;
      normalSrc = v7;
      tangentSrc = v6;
      diffuseColorSrc = v5;
      destVert += 4;
    }
    while ( v66 );
  }
  if ( v4 < destDrawVertsa )
  {
    v67 = &v4->normal.z;
    do
    {
      v68 = v8[2];
      v69 = v8[1];
      v4->xyz.x = *v8;
      *(v67 - 5) = v69;
      v8 = (float *)((char *)v8 + positionStride);
      ++v4;
      *(v67 - 4) = v68;
      v70 = v7[2];
      v67 += 16;
      v71 = v7[1];
      *(v67 - 18) = *v7;
      *(v67 - 17) = v71;
      v7 = (float *)((char *)v7 + normalStride);
      *(v67 - 16) = v70;
      v72 = v6[2];
      v73 = v6[1];
      *(v67 - 14) = *v6;
      v74 = binormalSrc;
      *(v67 - 13) = v73;
      v6 = (float *)((char *)v6 + tangentStride);
      *(v67 - 12) = v72;
      v75 = v74[2];
      v76 = v74[1];
      *(v67 - 11) = *v74;
      *(v67 - 10) = v76;
      v77 = texCoordSrc;
      *(v67 - 9) = v75;
      *(v67 - 8) = *v77;
      *(v67 - 7) = texCoordSrc[1];
      *((_BYTE *)v67 - 76) = *v5;
      *((_BYTE *)v67 - 75) = v5[1];
      *((_BYTE *)v67 - 74) = v5[2];
      LOBYTE(v77) = v5[3];
      v5 += diffuseColorStride;
      *((_BYTE *)v67 - 73) = (_BYTE)v77;
      binormalSrc = (float *)((char *)binormalSrc + binormalStride);
      texCoordSrc = (float *)((char *)texCoordSrc + texCoordStride);
      positionSrc = v8;
      normalSrc = v7;
      tangentSrc = v6;
      diffuseColorSrc = v5;
    }
    while ( v4 < destDrawVertsa );
  }
  rvVertexBuffer::Unlock((rvVertexBuffer *)drawVertexBuffer);
}

// FUNC: public: void __thiscall rvPrimBatch::CopyDrawIndices(int *,class rvIndexBuffer &,int)
void __thiscall rvPrimBatch::CopyDrawIndices(
        rvPrimBatch *this,
        int *destIndices,
        rvIndexBuffer *drawIndexBuffer,
        unsigned int destBase)
{
  unsigned int v4; // esi
  int v5; // edi
  unsigned __int16 *v6; // eax
  unsigned int v7; // edx
  int *v8; // ecx
  unsigned int v9; // edx
  int *v10; // ecx

  v4 = destBase - this->m_drawGeoSpec.m_vertexStart;
  v5 = 3 * this->m_drawGeoSpec.m_primitiveCount;
  rvIndexBuffer::Lock(drawIndexBuffer, this->m_drawGeoSpec.m_indexStart, v5, 1u, (void **)&destBase);
  v6 = (unsigned __int16 *)destBase;
  if ( (drawIndexBuffer->m_flags & 4) != 0 )
  {
    v7 = destBase + 2 * v5;
    if ( destBase < v7 )
    {
      v8 = destIndices;
      do
      {
        *v8 = v4 + *v6;
        v8[1] = v4 + v6[1];
        v8[2] = v4 + v6[2];
        v6 += 3;
        v8 += 3;
      }
      while ( (unsigned int)v6 < v7 );
    }
  }
  else
  {
    v9 = destBase + 4 * v5;
    if ( destBase < v9 )
    {
      v10 = destIndices;
      do
      {
        *v10 = v4 + *(_DWORD *)v6;
        v10[1] = v4 + *((_DWORD *)v6 + 1);
        v10[2] = v4 + *((_DWORD *)v6 + 2);
        v6 += 6;
        v10 += 3;
      }
      while ( (unsigned int)v6 < v9 );
    }
  }
  rvIndexBuffer::Unlock(drawIndexBuffer);
}

// FUNC: public: void __thiscall rvPrimBatch::CopySilTraceVertices(class rvVertexBuffer &,class rvIndexBuffer &,class rvVertexBuffer &,class rvIndexBuffer &)
void __thiscall rvPrimBatch::CopySilTraceVertices(
        rvPrimBatch *this,
        rvVertexBuffer *silTraceVertexBuffer,
        rvIndexBuffer *silTraceIndexBuffer,
        rvVertexBuffer *drawVertexBuffer,
        rvIndexBuffer *drawIndexBuffer)
{
  int m_indexStart; // edx
  int v7; // edi
  int v8; // ecx
  int m_vertexCount; // edi
  int v10; // eax
  void *v11; // esp
  unsigned int v12; // ecx
  bool v13; // cl
  int v14; // eax
  int v15; // edi
  unsigned __int16 *v16; // ecx
  int v17; // edx
  unsigned int v18; // edx
  int v19; // ecx
  unsigned int v20; // ecx
  bool v21; // cc
  int v22; // edx
  rvVertexBuffer *v23; // esi
  unsigned int v24[3]; // [esp+0h] [ebp-68h] BYREF
  float srcTail[4]; // [esp+Ch] [ebp-5Ch] BYREF
  int v26; // [esp+1Ch] [ebp-4Ch]
  int v27; // [esp+20h] [ebp-48h]
  void *drawIndexMemPtr; // [esp+24h] [ebp-44h] BYREF
  void *silTraceIndexMemPtr; // [esp+28h] [ebp-40h] BYREF
  int numIndices; // [esp+2Ch] [ebp-3Ch]
  int sil2; // [esp+30h] [ebp-38h]
  int sil1; // [esp+34h] [ebp-34h]
  int draw1; // [esp+38h] [ebp-30h]
  unsigned int *drawIndex32; // [esp+3Ch] [ebp-2Ch]
  unsigned __int16 *drawIndex16; // [esp+40h] [ebp-28h]
  unsigned int *silIndex32; // [esp+44h] [ebp-24h]
  unsigned __int8 *silTraceVertex; // [esp+48h] [ebp-20h] BYREF
  int silTraceVertexStride; // [esp+4Ch] [ebp-1Ch] BYREF
  unsigned __int8 *drawVertex; // [esp+50h] [ebp-18h] BYREF
  int drawVertexStride; // [esp+54h] [ebp-14h] BYREF
  int base; // [esp+58h] [ebp-10h]
  int *v42; // [esp+5Ch] [ebp-Ch]
  unsigned __int16 *v43; // [esp+60h] [ebp-8h]
  bool drawIs16Bit; // [esp+66h] [ebp-2h]
  bool silTraceIs16Bit; // [esp+67h] [ebp-1h]

  m_indexStart = this->m_silTraceGeoSpec.m_indexStart;
  base = this->m_drawGeoSpec.m_vertexStart;
  v7 = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  memset(srcTail, 0, 12);
  srcTail[3] = 1.0;
  numIndices = v7;
  rvIndexBuffer::Lock(silTraceIndexBuffer, m_indexStart, v7, 1u, &silTraceIndexMemPtr);
  v8 = this->m_drawGeoSpec.m_indexStart;
  sil2 = (int)silTraceIndexMemPtr;
  silIndex32 = (unsigned int *)silTraceIndexMemPtr;
  rvIndexBuffer::Lock(drawIndexBuffer, v8, v7, 1u, &drawIndexMemPtr);
  m_vertexCount = this->m_drawGeoSpec.m_vertexCount;
  drawIndex16 = (unsigned __int16 *)drawIndexMemPtr;
  drawIndex32 = (unsigned int *)drawIndexMemPtr;
  m_vertexCount *= 4;
  v10 = m_vertexCount + 3;
  LOBYTE(v10) = (m_vertexCount + 3) & 0xFC;
  v11 = alloca(v10);
  memset(v24, 0, m_vertexCount);
  v12 = silTraceIndexBuffer->m_flags >> 2;
  drawIs16Bit = (drawIndexBuffer->m_flags & 4) != 0;
  v13 = v12 & 1;
  v14 = 0;
  silTraceIs16Bit = v13;
  if ( numIndices > 0 )
  {
    v42 = (int *)(silIndex32 + 2);
    v43 = (unsigned __int16 *)(sil2 + 4);
    v15 = (char *)drawIndex32 - (char *)silIndex32;
    v26 = (int)drawIndex16 - sil2;
    v27 = (char *)drawIndex32 - (char *)silIndex32;
    while ( 1 )
    {
      if ( v13 )
      {
        v16 = v43;
        silIndex32 = (unsigned int *)*(v43 - 2);
        sil1 = *(v43 - 1);
        sil2 = *v43;
      }
      else
      {
        silIndex32 = (unsigned int *)*(v42 - 2);
        v17 = *(v42 - 1);
        sil2 = *v42;
        v16 = v43;
        sil1 = v17;
      }
      if ( drawIs16Bit )
      {
        v18 = drawIndex16[v14];
        draw1 = drawIndex16[v14 + 1];
        v19 = *(unsigned __int16 *)((char *)v16 + v26);
      }
      else
      {
        v18 = drawIndex32[v14];
        draw1 = drawIndex32[v14 + 1];
        v19 = *(int *)((char *)v42 + v15);
      }
      v20 = v19 - base;
      v43 += 3;
      v42 += 3;
      v24[(_DWORD)silIndex32] = v18 - base;
      v24[sil1] = draw1 - base;
      v14 += 3;
      v21 = v14 < numIndices;
      v24[sil2] = v20;
      if ( !v21 )
        break;
      v15 = v27;
      v13 = silTraceIs16Bit;
    }
  }
  rvIndexBuffer::Unlock(drawIndexBuffer);
  rvIndexBuffer::Unlock(silTraceIndexBuffer);
  rvVertexBuffer::LockPosition(
    silTraceVertexBuffer,
    this->m_silTraceGeoSpec.m_vertexStart,
    this->m_silTraceGeoSpec.m_vertexCount,
    2u,
    &silTraceVertex,
    &silTraceVertexStride);
  rvVertexBuffer::LockPosition(
    drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    &drawVertex,
    &drawVertexStride);
  rvVertexBuffer::ComponentCopy(
    &silTraceVertex[silTraceVertexBuffer->m_format.m_byteOffset[0]],
    silTraceVertexStride,
    (Rv_Vertex_Data_Type_t)silTraceVertexBuffer->m_format.m_dataTypes[0],
    silTraceVertexBuffer->m_format.m_dimensions & 7,
    &drawVertex[drawVertexBuffer->m_format.m_byteOffset[0]],
    drawVertexStride,
    (Rv_Vertex_Data_Type_t)drawVertexBuffer->m_format.m_dataTypes[0],
    drawVertexBuffer->m_format.m_dimensions & 7,
    this->m_silTraceGeoSpec.m_vertexCount,
    v24,
    srcTail,
    0);
  if ( (drawVertexBuffer->m_format.m_flags & 4) != 0 )
    rvVertexBuffer::ComponentCopy(
      &silTraceVertex[silTraceVertexBuffer->m_format.m_byteOffset[2]],
      silTraceVertexStride,
      (Rv_Vertex_Data_Type_t)silTraceVertexBuffer->m_format.m_dataTypes[2],
      1,
      &drawVertex[drawVertexBuffer->m_format.m_byteOffset[2]],
      drawVertexStride,
      (Rv_Vertex_Data_Type_t)drawVertexBuffer->m_format.m_dataTypes[2],
      1,
      this->m_silTraceGeoSpec.m_vertexCount,
      v24,
      0,
      0);
  if ( (drawVertexBuffer->m_format.m_flags & 8) != 0 )
  {
    v22 = this->m_silTraceGeoSpec.m_vertexCount;
    v23 = silTraceVertexBuffer;
    rvVertexBuffer::ComponentCopy(
      &silTraceVertex[silTraceVertexBuffer->m_format.m_byteOffset[3]],
      silTraceVertexStride,
      (Rv_Vertex_Data_Type_t)silTraceVertexBuffer->m_format.m_dataTypes[3],
      (silTraceVertexBuffer->m_format.m_dimensions >> 3) & 7,
      &drawVertex[drawVertexBuffer->m_format.m_byteOffset[3]],
      drawVertexStride,
      (Rv_Vertex_Data_Type_t)drawVertexBuffer->m_format.m_dataTypes[3],
      (drawVertexBuffer->m_format.m_dimensions >> 3) & 7,
      v22,
      v24,
      0,
      1);
  }
  else
  {
    v23 = silTraceVertexBuffer;
  }
  rvVertexBuffer::Unlock(drawVertexBuffer);
  rvVertexBuffer::Unlock(v23);
}

// FUNC: public: void __thiscall rvPrimBatch::CopyShadowVertices(class rvVertexBuffer &,class rvVertexBuffer &)
void __thiscall rvPrimBatch::CopyShadowVertices(
        rvPrimBatch *this,
        rvVertexBuffer *shadowVertexBuffer,
        rvVertexBuffer *silTraceVertexBuffer)
{
  rvVertexBuffer *v3; // esi
  rvVertexBuffer *v5; // edi
  int m_vertexStart; // [esp-14h] [ebp-4Ch]
  int m_vertexCount; // [esp-10h] [ebp-48h]
  unsigned __int8 *silTraceVertex; // [esp+Ch] [ebp-2Ch] BYREF
  int shadowVertexStride; // [esp+10h] [ebp-28h] BYREF
  unsigned __int8 *shadowVertex; // [esp+14h] [ebp-24h] BYREF
  float srcTail1[4]; // [esp+18h] [ebp-20h] BYREF
  float srcTail0[4]; // [esp+28h] [ebp-10h] BYREF

  v3 = shadowVertexBuffer;
  m_vertexCount = this->m_shadowVolGeoSpec.m_vertexCount;
  m_vertexStart = this->m_shadowVolGeoSpec.m_vertexStart;
  memset(srcTail0, 0, sizeof(srcTail0));
  memset(srcTail1, 0, 12);
  srcTail1[3] = 1.0;
  rvVertexBuffer::LockPosition(shadowVertexBuffer, m_vertexStart, m_vertexCount, 2u, &shadowVertex, &shadowVertexStride);
  v5 = silTraceVertexBuffer;
  rvVertexBuffer::LockPosition(
    silTraceVertexBuffer,
    this->m_silTraceGeoSpec.m_vertexStart,
    this->m_silTraceGeoSpec.m_vertexCount,
    1u,
    &silTraceVertex,
    (int *)&shadowVertexBuffer);
  rvVertexBuffer::ComponentCopy(
    &shadowVertex[v3->m_format.m_byteOffset[0]],
    2 * shadowVertexStride,
    (Rv_Vertex_Data_Type_t)v3->m_format.m_dataTypes[0],
    v3->m_format.m_dimensions & 7,
    &silTraceVertex[v5->m_format.m_byteOffset[0]],
    (int)shadowVertexBuffer,
    (Rv_Vertex_Data_Type_t)v5->m_format.m_dataTypes[0],
    3,
    this->m_silTraceGeoSpec.m_vertexCount,
    0,
    srcTail1,
    0);
  rvVertexBuffer::ComponentCopy(
    &shadowVertex[v3->m_format.m_byteOffset[0] + shadowVertexStride],
    2 * shadowVertexStride,
    (Rv_Vertex_Data_Type_t)v3->m_format.m_dataTypes[0],
    v3->m_format.m_dimensions & 7,
    &silTraceVertex[v5->m_format.m_byteOffset[0]],
    (int)shadowVertexBuffer,
    (Rv_Vertex_Data_Type_t)v5->m_format.m_dataTypes[0],
    3,
    this->m_silTraceGeoSpec.m_vertexCount,
    0,
    srcTail0,
    0);
  if ( (v5->m_format.m_flags & 4) != 0 )
  {
    rvVertexBuffer::ComponentCopy(
      &shadowVertex[v3->m_format.m_byteOffset[2]],
      2 * shadowVertexStride,
      (Rv_Vertex_Data_Type_t)v3->m_format.m_dataTypes[2],
      1,
      &silTraceVertex[v5->m_format.m_byteOffset[2]],
      (int)shadowVertexBuffer,
      (Rv_Vertex_Data_Type_t)v5->m_format.m_dataTypes[2],
      1,
      this->m_silTraceGeoSpec.m_vertexCount,
      0,
      0,
      0);
    rvVertexBuffer::ComponentCopy(
      &shadowVertex[v3->m_format.m_byteOffset[2] + shadowVertexStride],
      2 * shadowVertexStride,
      (Rv_Vertex_Data_Type_t)v3->m_format.m_dataTypes[2],
      1,
      &silTraceVertex[v5->m_format.m_byteOffset[2]],
      (int)shadowVertexBuffer,
      (Rv_Vertex_Data_Type_t)v5->m_format.m_dataTypes[2],
      1,
      this->m_silTraceGeoSpec.m_vertexCount,
      0,
      0,
      0);
  }
  if ( (v5->m_format.m_flags & 8) != 0 )
  {
    rvVertexBuffer::ComponentCopy(
      &shadowVertex[v3->m_format.m_byteOffset[3]],
      2 * shadowVertexStride,
      (Rv_Vertex_Data_Type_t)v3->m_format.m_dataTypes[3],
      (v3->m_format.m_dimensions >> 3) & 7,
      &silTraceVertex[v5->m_format.m_byteOffset[3]],
      (int)shadowVertexBuffer,
      (Rv_Vertex_Data_Type_t)v5->m_format.m_dataTypes[3],
      (v5->m_format.m_dimensions >> 3) & 7,
      this->m_silTraceGeoSpec.m_vertexCount,
      0,
      0,
      1);
    rvVertexBuffer::ComponentCopy(
      &shadowVertex[shadowVertexStride + v3->m_format.m_byteOffset[3]],
      2 * shadowVertexStride,
      (Rv_Vertex_Data_Type_t)v3->m_format.m_dataTypes[3],
      (v3->m_format.m_dimensions >> 3) & 7,
      &silTraceVertex[v5->m_format.m_byteOffset[3]],
      (int)shadowVertexBuffer,
      (Rv_Vertex_Data_Type_t)v5->m_format.m_dataTypes[3],
      (v5->m_format.m_dimensions >> 3) & 7,
      this->m_silTraceGeoSpec.m_vertexCount,
      0,
      0,
      1);
  }
  rvVertexBuffer::Unlock(v5);
  rvVertexBuffer::Unlock(v3);
}

// FUNC: public: void __thiscall rvPrimBatch::Write(class idFile &,char const *)
void __thiscall rvPrimBatch::Write(rvPrimBatch *this, idFile *outFile, const char *prepend)
{
  int v4; // eax
  void *v5; // esp
  int v7; // eax
  char *v8; // eax
  bool v9; // zf
  int v10; // edx
  char *v11; // eax
  int m_primitiveCount; // eax
  char v13[12]; // [esp+0h] [ebp-14h] BYREF
  char *v14; // [esp+Ch] [ebp-8h]
  int prependLen; // [esp+10h] [ebp-4h]
  int curTransform; // [esp+1Ch] [ebp+8h]

  prependLen = strlen(prepend);
  v4 = prependLen + 6;
  LOBYTE(v4) = (prependLen + 6) & 0xFC;
  v5 = alloca(v4);
  outFile->WriteFloatString(outFile, "%sPrimBatch\n", prepend);
  outFile->WriteFloatString(outFile, "%s{\n", prepend);
  strcpy(v13, prepend);
  v7 = prependLen;
  v13[prependLen] = 9;
  v8 = &v13[v7 + 1];
  *v8 = 0;
  v9 = this->m_transformPalette == 0;
  v14 = v8;
  if ( !v9 )
  {
    outFile->WriteFloatString(outFile, "%sTransform[ %d ]\n", v13, this->m_numTransforms);
    outFile->WriteFloatString(outFile, "%s{\n", v13);
    v10 = prependLen;
    *v14 = 9;
    v13[v10 + 2] = 0;
    for ( curTransform = 0; curTransform < this->m_numTransforms; ++curTransform )
      outFile->WriteFloatString(outFile, "%s%d\n", v13, this->m_transformPalette[curTransform]);
    v11 = v14;
    v13[prependLen] = 9;
    *v11 = 0;
    outFile->WriteFloatString(outFile, "%s}\n", v13);
  }
  if ( this->m_silTraceGeoSpec.m_primitiveCount > 0 )
    outFile->WriteFloatString(
      outFile,
      "%sSilTraceIndexedTriList %d %d %d %d\n",
      v13,
      this->m_silTraceGeoSpec.m_vertexStart,
      this->m_silTraceGeoSpec.m_vertexCount,
      this->m_silTraceGeoSpec.m_indexStart,
      this->m_silTraceGeoSpec.m_primitiveCount);
  if ( this->m_drawGeoSpec.m_primitiveCount > 0 )
    outFile->WriteFloatString(
      outFile,
      "%sDrawIndexedTriList %d %d %d %d\n",
      v13,
      this->m_drawGeoSpec.m_vertexStart,
      this->m_drawGeoSpec.m_vertexCount,
      this->m_drawGeoSpec.m_indexStart,
      this->m_drawGeoSpec.m_primitiveCount);
  m_primitiveCount = this->m_shadowVolGeoSpec.m_primitiveCount;
  if ( m_primitiveCount <= 0 )
  {
    if ( this->m_shadowVolGeoSpec.m_vertexCount > 0 )
      outFile->WriteFloatString(outFile, "%sShadowVerts %d\n", v13, this->m_shadowVolGeoSpec.m_vertexStart);
  }
  else
  {
    outFile->WriteFloatString(
      outFile,
      "%sShadowIndexedTriList %d %d %d %d %d %d\n",
      v13,
      this->m_shadowVolGeoSpec.m_vertexStart,
      this->m_shadowVolGeoSpec.m_vertexCount,
      this->m_shadowVolGeoSpec.m_indexStart,
      m_primitiveCount,
      this->m_numShadowPrimitivesNoCaps,
      this->m_shadowCapPlaneBits);
  }
  if ( this->m_silEdgeCount > 0 )
    outFile->WriteFloatString(outFile, "%sSilhouetteEdge %d %d\n", v13, this->m_silEdgeStart, this->m_silEdgeCount);
  outFile->WriteFloatString(outFile, "%s}\n", prepend);
}

// FUNC: public: __thiscall rvPrimBatch::rvPrimBatch(void)
void __thiscall rvPrimBatch::rvPrimBatch(rvPrimBatch *this)
{
  this->m_transformPalette = 0;
  this->m_numTransforms = 0;
  this->m_silEdgeStart = 0;
  this->m_silEdgeCount = 0;
  this->m_silTraceGeoSpec.m_vertexStart = 0;
  this->m_silTraceGeoSpec.m_vertexCount = 0;
  this->m_silTraceGeoSpec.m_indexStart = 0;
  this->m_silTraceGeoSpec.m_primitiveCount = 0;
  this->m_silTraceGeoSpec.m_indexStart = -1;
  this->m_drawGeoSpec.m_vertexStart = 0;
  this->m_drawGeoSpec.m_vertexCount = 0;
  this->m_drawGeoSpec.m_indexStart = 0;
  this->m_drawGeoSpec.m_primitiveCount = 0;
  this->m_drawGeoSpec.m_indexStart = -1;
  this->m_shadowVolGeoSpec.m_vertexStart = 0;
  this->m_shadowVolGeoSpec.m_vertexCount = 0;
  this->m_shadowVolGeoSpec.m_indexStart = 0;
  this->m_shadowVolGeoSpec.m_primitiveCount = 0;
  this->m_shadowVolGeoSpec.m_indexStart = -1;
  this->m_numShadowPrimitivesNoCaps = 0;
  this->m_shadowCapPlaneBits = 0;
}

// FUNC: public: void __thiscall rvPrimBatch::Shutdown(void)
void __thiscall rvPrimBatch::Shutdown(rvPrimBatch *this)
{
  if ( this->m_transformPalette )
    Memory::Free(this->m_transformPalette);
  this->m_transformPalette = 0;
  this->m_numTransforms = 0;
  this->m_silEdgeStart = 0;
  this->m_silEdgeCount = 0;
  this->m_silTraceGeoSpec.m_vertexStart = 0;
  this->m_silTraceGeoSpec.m_vertexCount = 0;
  this->m_silTraceGeoSpec.m_indexStart = 0;
  this->m_silTraceGeoSpec.m_primitiveCount = 0;
  this->m_silTraceGeoSpec.m_indexStart = -1;
  this->m_drawGeoSpec.m_vertexStart = 0;
  this->m_drawGeoSpec.m_vertexCount = 0;
  this->m_drawGeoSpec.m_indexStart = 0;
  this->m_drawGeoSpec.m_primitiveCount = 0;
  this->m_drawGeoSpec.m_indexStart = -1;
  this->m_shadowVolGeoSpec.m_vertexStart = 0;
  this->m_shadowVolGeoSpec.m_vertexCount = 0;
  this->m_shadowVolGeoSpec.m_indexStart = 0;
  this->m_shadowVolGeoSpec.m_primitiveCount = 0;
  this->m_numShadowPrimitivesNoCaps = 0;
  this->m_shadowCapPlaneBits = 0;
  this->m_shadowVolGeoSpec.m_indexStart = -1;
}

// FUNC: public: void __thiscall rvPrimBatch::Draw(class rvVertexBuffer &,class rvIndexBuffer &,class rvVertexFormat const *)
void __thiscall rvPrimBatch::Draw(
        rvPrimBatch *this,
        rvVertexBuffer *vertexBuffer,
        rvIndexBuffer *indexBuffer,
        const rvVertexFormat *vertexComponentsNeeded)
{
  int m_primitiveCount; // eax
  int v5; // esi
  int v6; // ecx
  unsigned int v7; // eax
  int v8; // edx

  m_primitiveCount = this->m_drawGeoSpec.m_primitiveCount;
  ++backEnd.pc.c_drawElements;
  v5 = 3 * m_primitiveCount;
  backEnd.pc.c_drawIndexes += 3 * m_primitiveCount;
  backEnd.pc.c_drawVertexes += this->m_drawGeoSpec.m_vertexCount;
  v6 = 2 * this->m_drawGeoSpec.m_indexStart;
  if ( (indexBuffer->m_flags & 4) != 0 )
  {
    v7 = 5123;
  }
  else
  {
    v6 *= 2;
    v7 = 5125;
  }
  v8 = 3;
  if ( !r_singleTriangle.internalVar->integerValue )
    v8 = v5;
  qglDrawElements(4u, v8, v7, (const void *)v6);
  backEnd.pc.c_vboIndexes += v5;
}

// FUNC: public: void __thiscall rvPrimBatch::Draw(class rvVertexBuffer &,int *,int,class rvVertexFormat const *)
void __thiscall rvPrimBatch::Draw(
        rvPrimBatch *this,
        rvVertexBuffer *vertexBuffer,
        int *indices,
        int numIndices,
        const rvVertexFormat *vertexComponentsNeeded)
{
  int v5; // eax

  if ( numIndices )
  {
    ++backEnd.pc.c_drawElements;
    backEnd.pc.c_drawIndexes += numIndices;
    backEnd.pc.c_drawVertexes += this->m_drawGeoSpec.m_vertexCount;
    qglBindBufferARB(0x8893u, 0);
    v5 = 3;
    if ( !r_singleTriangle.internalVar->integerValue )
      v5 = numIndices;
    qglDrawElements(4u, v5, 0x1405u, indices);
    backEnd.pc.c_vboIndexes += numIndices;
  }
}

// FUNC: public: void __thiscall rvPrimBatch::DrawShadowVolume(class rvVertexBuffer &,int *,int,class rvVertexFormat const *)
void __thiscall rvPrimBatch::DrawShadowVolume(
        rvPrimBatch *this,
        rvVertexBuffer *vertexBuffer,
        int *indices,
        int numIndices,
        const rvVertexFormat *vertexComponentsNeeded)
{
  int v5; // esi

  v5 = numIndices;
  if ( numIndices )
  {
    ++backEnd.pc.c_shadowElements;
    backEnd.pc.c_shadowIndexes += numIndices;
    backEnd.pc.c_shadowVertexes += this->m_shadowVolGeoSpec.m_vertexCount;
    qglBindBufferARB(0x8893u, 0);
    if ( r_singleTriangle.internalVar->integerValue )
      v5 = 3;
    qglDrawElements(4u, v5, 0x1405u, indices);
  }
}

// FUNC: public: void __thiscall rvPrimBatch::DrawShadowVolume(class rvVertexBuffer &,class rvIndexBuffer &,bool,class rvVertexFormat const *)
void __thiscall rvPrimBatch::DrawShadowVolume(
        rvPrimBatch *this,
        rvVertexBuffer *vertexBuffer,
        rvIndexBuffer *indexBuffer,
        bool drawCaps,
        const rvVertexFormat *vertexComponentsNeeded)
{
  int m_primitiveCount; // eax
  int v6; // edx
  int m_indexStart; // eax
  unsigned int v8; // ecx
  const void *v9; // eax

  if ( drawCaps )
    m_primitiveCount = this->m_shadowVolGeoSpec.m_primitiveCount;
  else
    m_primitiveCount = this->m_numShadowPrimitivesNoCaps;
  v6 = 3 * m_primitiveCount;
  if ( 3 * m_primitiveCount > 0 )
  {
    ++backEnd.pc.c_shadowElements;
    backEnd.pc.c_shadowIndexes += v6;
    backEnd.pc.c_shadowVertexes += this->m_shadowVolGeoSpec.m_vertexCount;
    m_indexStart = this->m_shadowVolGeoSpec.m_indexStart;
    if ( (indexBuffer->m_flags & 4) != 0 )
    {
      v8 = 5123;
    }
    else
    {
      m_indexStart *= 2;
      v8 = 5125;
    }
    v9 = (const void *)(2 * m_indexStart);
    if ( r_singleTriangle.internalVar->integerValue )
      v6 = 3;
    qglDrawElements(4u, v6, v8, v9);
  }
}

// FUNC: public: void __thiscall rvPrimBatch::TransformVertsMinMax(class rvSilTraceVertT *,class idVec3 &,class idVec3 &,class rvVertexBuffer &,class idJointMat *,class idJointMat *,float *)
void __thiscall rvPrimBatch::TransformVertsMinMax(
        rvPrimBatch *this,
        rvSilTraceVertT *destSilTraceVerts,
        idVec3 *bndMin,
        idVec3 *bndMax,
        rvVertexBuffer *silTraceVB,
        idJointMat *skinSpaceToLocalMats,
        idJointMat *localToModelMats,
        float *skinToModelTransforms)
{
  float *v8; // edi

  v8 = skinToModelTransforms;
  SIMDProcessor->JointMat_MultiplyMats(
    SIMDProcessor,
    skinToModelTransforms,
    skinSpaceToLocalMats,
    localToModelMats,
    this->m_transformPalette,
    this->m_numTransforms);
  rvVertexBuffer::LockPosition(
    silTraceVB,
    this->m_silTraceGeoSpec.m_vertexStart,
    this->m_silTraceGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&skinSpaceToLocalMats,
    (int *)&localToModelMats);
  if ( (silTraceVB->m_format.m_flags & 8) != 0 && (silTraceVB->m_format.m_dimensions & 0x38) == 32 )
  {
    SIMDProcessor->TransformVertsMinMax4Bone(
      SIMDProcessor,
      destSilTraceVerts,
      bndMin,
      bndMax,
      (unsigned __int8 *)skinSpaceToLocalMats,
      (int)localToModelMats,
      this->m_silTraceGeoSpec.m_vertexCount,
      v8);
    rvVertexBuffer::Unlock(silTraceVB);
  }
  else
  {
    SIMDProcessor->TransformVertsMinMax1Bone(
      SIMDProcessor,
      destSilTraceVerts,
      bndMin,
      bndMax,
      (unsigned __int8 *)skinSpaceToLocalMats,
      (int)localToModelMats,
      this->m_silTraceGeoSpec.m_vertexCount,
      v8);
    rvVertexBuffer::Unlock(silTraceVB);
  }
}

// FUNC: public: void __thiscall rvPrimBatch::DeriveTriPlanes(class idPlane *,class rvSilTraceVertT const *,class rvIndexBuffer &)
void __thiscall rvPrimBatch::DeriveTriPlanes(
        rvPrimBatch *this,
        idPlane *planes,
        const rvSilTraceVertT *silTraceVerts,
        rvIndexBuffer *silTraceIB)
{
  rvIndexBuffer *v4; // ebx
  int v6; // edi
  idSIMDProcessor_vtbl *v7; // eax
  int m_vertexCount; // [esp-Ch] [ebp-18h]

  v4 = silTraceIB;
  v6 = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  rvIndexBuffer::Lock(silTraceIB, this->m_silTraceGeoSpec.m_indexStart, v6, 1u, (void **)&silTraceIB);
  v7 = SIMDProcessor->__vftable;
  m_vertexCount = this->m_silTraceGeoSpec.m_vertexCount;
  if ( (v4->m_flags & 4) != 0 )
    (*(void (__stdcall **)(const rvSilTraceVertT *, int, rvIndexBuffer *, int))v7->gap138)(
      silTraceVerts,
      m_vertexCount,
      silTraceIB,
      v6);
  else
    (*(void (__stdcall **)(const rvSilTraceVertT *, int, rvIndexBuffer *, int))&v7->gap138[4])(
      silTraceVerts,
      m_vertexCount,
      silTraceIB,
      v6);
  rvIndexBuffer::Unlock(v4);
}

// FUNC: public: void __thiscall rvPrimBatch::LocalTrace(struct localTrace_s &,int &,int &,int &,class idVec3 const &,class idVec3 const &,unsigned char const *,class idPlane const *,class rvSilTraceVertT const *,float,class rvIndexBuffer &,class rvIndexBuffer &)
void __thiscall rvPrimBatch::LocalTrace(
        rvPrimBatch *this,
        localTrace_s *hit,
        int *c_testPlanes,
        int *c_testEdges,
        int *c_intersect,
        const idVec3 *start,
        const idVec3 *end,
        const unsigned __int8 *cullBits,
        const idPlane *facePlanes,
        const rvSilTraceVertT *silTraceVerts,
        float radius,
        rvIndexBuffer *silTraceIB,
        rvIndexBuffer *drawIB)
{
  rvIndexBuffer *v13; // ebp
  int m_indexStart; // edx
  int v16; // edi
  int v17; // ebx
  double v18; // st7
  double v19; // st6
  bool v20; // al
  float *p_b; // edi
  unsigned __int8 *v22; // ebp
  unsigned __int8 *v23; // edx
  int v24; // esi
  int v25; // ebp
  unsigned int v26; // eax
  unsigned __int8 v27; // al
  double v28; // st7
  const rvSilTraceVertT *v29; // edx
  const rvSilTraceVertT *v30; // esi
  double v31; // st7
  double v32; // st7
  double v33; // st6
  double v34; // st5
  double v35; // st7
  double v36; // st7
  double v37; // st6
  const rvSilTraceVertT *v38; // ebp
  double v39; // st7
  double v40; // st7
  double v41; // st6
  double v42; // st5
  double v43; // st7
  double v44; // st7
  double v45; // st6
  double v46; // st7
  double v47; // st6
  double v48; // st5
  double v49; // st7
  double v50; // st7
  double v51; // st6
  int v52; // edx
  int v53; // esi
  int v54; // ebp
  int v55; // esi
  int v56; // ebp
  float d2; // [esp+10h] [ebp-ACh]
  float d2a; // [esp+10h] [ebp-ACh]
  float d2b; // [esp+10h] [ebp-ACh]
  float d2c; // [esp+10h] [ebp-ACh]
  float radiusSqr; // [esp+14h] [ebp-A8h]
  float f; // [esp+18h] [ebp-A4h]
  float fa; // [esp+18h] [ebp-A4h]
  float v64; // [esp+1Ch] [ebp-A0h]
  float v65; // [esp+20h] [ebp-9Ch]
  float v66; // [esp+24h] [ebp-98h]
  float v67; // [esp+28h] [ebp-94h]
  float v68; // [esp+2Ch] [ebp-90h]
  float v69; // [esp+30h] [ebp-8Ch]
  float v70; // [esp+34h] [ebp-88h]
  float v71; // [esp+38h] [ebp-84h]
  float v72; // [esp+3Ch] [ebp-80h]
  bool is16Bit; // [esp+43h] [ebp-79h]
  unsigned __int8 *v74; // [esp+44h] [ebp-78h]
  unsigned int i2; // [esp+48h] [ebp-74h]
  unsigned __int8 *v76; // [esp+4Ch] [ebp-70h]
  _BYTE v77[12]; // [esp+50h] [ebp-6Ch]
  void *drawIndexMemPtr; // [esp+5Ch] [ebp-60h] BYREF
  rvPrimBatch *v79; // [esp+60h] [ebp-5Ch]
  float v80; // [esp+64h] [ebp-58h]
  float v81; // [esp+68h] [ebp-54h]
  float v82; // [esp+6Ch] [ebp-50h]
  float v83; // [esp+70h] [ebp-4Ch]
  float v84; // [esp+74h] [ebp-48h]
  float v85; // [esp+78h] [ebp-44h]
  float v86; // [esp+7Ch] [ebp-40h]
  float v87; // [esp+80h] [ebp-3Ch]
  float v88; // [esp+84h] [ebp-38h]
  int v89; // [esp+88h] [ebp-34h]
  idVec3 v90; // [esp+8Ch] [ebp-30h]
  int base; // [esp+98h] [ebp-24h]
  idVec3 startDir; // [esp+9Ch] [ebp-20h]
  int numIndices; // [esp+A8h] [ebp-14h]
  unsigned __int8 *indexMemPtr; // [esp+ACh] [ebp-10h] BYREF
  float v95; // [esp+B8h] [ebp-4h]

  v13 = silTraceIB;
  m_indexStart = this->m_silTraceGeoSpec.m_indexStart;
  base = this->m_drawGeoSpec.m_vertexStart;
  v16 = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  v79 = this;
  numIndices = v16;
  rvIndexBuffer::Lock(silTraceIB, m_indexStart, v16, 1u, (void **)&indexMemPtr);
  rvIndexBuffer::Lock(drawIB, this->m_drawGeoSpec.m_indexStart, v16, 1u, &drawIndexMemPtr);
  v17 = 0;
  radiusSqr = radius * radius;
  v18 = end->x - start->x;
  v19 = end->y - start->y;
  v20 = (silTraceIB->m_flags & 4) != 0;
  v90.z = end->z - start->z;
  startDir.z = v90.z;
  startDir.x = v18;
  is16Bit = v20;
  startDir.y = v19;
  if ( v16 > 0 )
  {
    p_b = &facePlanes->b;
    v22 = indexMemPtr + 8;
    v23 = indexMemPtr + 4;
    v74 = indexMemPtr + 8;
    v76 = indexMemPtr + 4;
    v89 = (_BYTE *)drawIndexMemPtr - indexMemPtr;
    while ( 1 )
    {
      if ( v20 )
      {
        v24 = *((unsigned __int16 *)v23 - 2);
        v25 = *((unsigned __int16 *)v23 - 1);
        v26 = *(unsigned __int16 *)v23;
      }
      else
      {
        v24 = *((_DWORD *)v22 - 2);
        v25 = *((_DWORD *)v22 - 1);
        v26 = *(_DWORD *)v74;
      }
      i2 = v26;
      v27 = cullBits[v24] | cullBits[v25] | cullBits[v26];
      if ( ((v27 ^ (v27 >> 4)) & 3) == 0 && ((v27 ^ (v27 >> 1)) & 4) == 0 )
      {
        ++*c_testPlanes;
        f = start->y * *p_b + p_b[1] * start->z + start->x * *(p_b - 1) + p_b[2];
        d2 = p_b[1] * end->z + end->y * *p_b + *(p_b - 1) * end->x + p_b[2];
        if ( f > (double)d2 && f >= 0.0 && d2 <= 0.0 )
        {
          v28 = f / (f - d2);
          fa = v28;
          if ( v28 >= 0.0 && fa < (double)hit->fraction )
            break;
        }
      }
LABEL_48:
      v76 += 6;
      v74 += 12;
      v17 += 3;
      p_b += 4;
      if ( v17 >= numIndices )
      {
        v13 = silTraceIB;
        goto LABEL_50;
      }
      v20 = is16Bit;
      v23 = v76;
      v22 = v74;
    }
    ++*c_testEdges;
    v90 = startDir;
    v95 = startDir.z * fa;
    *(float *)v77 = startDir.x * fa + start->x;
    *(float *)&v77[4] = startDir.y * fa + start->y;
    v29 = &silTraceVerts[v24];
    v30 = &silTraceVerts[v25];
    *(float *)&v77[8] = v95 + start->z;
    v64 = v29->xyzw.x - *(float *)v77;
    v65 = v29->xyzw.y - *(float *)&v77[4];
    v66 = v29->xyzw.z - *(float *)&v77[8];
    v70 = v30->xyzw.x - *(float *)v77;
    v71 = v30->xyzw.y - *(float *)&v77[4];
    v31 = v30->xyzw.z - *(float *)&v77[8];
    v72 = v31;
    v86 = v31 * v65 - v71 * v66;
    v87 = v66 * v70 - v72 * v64;
    v88 = v71 * v64 - v65 * v70;
    if ( v87 * *p_b + v86 * *(p_b - 1) + v88 * p_b[1] > 0.0 )
    {
      if ( radiusSqr <= 0.0 )
        goto LABEL_48;
      v32 = v29->xyzw.x - v30->xyzw.x;
      v33 = v29->xyzw.y - v30->xyzw.y;
      v34 = v29->xyzw.z - v30->xyzw.z;
      d2a = v34 * v34 + v33 * v33 + v32 * v32;
      if ( d2a * radiusSqr < v88 * v88 + v87 * v87 + v86 * v86 )
        goto LABEL_48;
      v35 = v34 * v66 + v33 * v65 + v32 * v64;
      if ( v35 >= 0.0 )
      {
        if ( v35 <= d2a
          || v72 * (v30->xyzw.z - silTraceVerts[i2].xyzw.z)
           + (v30->xyzw.y - silTraceVerts[i2].xyzw.y) * v71
           + (v30->xyzw.x - silTraceVerts[i2].xyzw.x) * v70 >= 0.0 )
        {
          goto LABEL_24;
        }
        v36 = v72 * v72 + v71 * v71;
        v37 = v70 * v70;
      }
      else
      {
        if ( v66 * (v29->xyzw.z - silTraceVerts[i2].xyzw.z)
           + (v29->xyzw.y - silTraceVerts[i2].xyzw.y) * v65
           + (v29->xyzw.x - silTraceVerts[i2].xyzw.x) * v64 >= 0.0 )
          goto LABEL_24;
        v36 = v64 * v64 + v66 * v66;
        v37 = v65 * v65;
      }
      if ( v36 + v37 > radiusSqr )
        goto LABEL_48;
    }
LABEL_24:
    v38 = &silTraceVerts[i2];
    v67 = v38->xyzw.x - *(float *)v77;
    v68 = v38->xyzw.y - *(float *)&v77[4];
    v39 = v38->xyzw.z - *(float *)&v77[8];
    v69 = v39;
    v83 = v39 * v71 - v68 * v72;
    v84 = v72 * v67 - v69 * v70;
    v85 = v68 * v70 - v71 * v67;
    if ( v84 * *p_b + v83 * *(p_b - 1) + v85 * p_b[1] <= 0.0 )
      goto LABEL_34;
    if ( radiusSqr <= 0.0 )
      goto LABEL_48;
    v40 = v30->xyzw.x - v38->xyzw.x;
    v41 = v30->xyzw.y - v38->xyzw.y;
    v42 = v30->xyzw.z - v38->xyzw.z;
    d2b = v42 * v42 + v41 * v41 + v40 * v40;
    if ( d2b * radiusSqr < v85 * v85 + v84 * v84 + v83 * v83 )
      goto LABEL_48;
    v43 = v42 * v72 + v41 * v71 + v40 * v70;
    if ( v43 >= 0.0 )
    {
      if ( v43 <= d2b
        || v69 * (v38->xyzw.z - v29->xyzw.z) + (v38->xyzw.y - v29->xyzw.y) * v68 + (v38->xyzw.x - v29->xyzw.x) * v67 >= 0.0 )
      {
        goto LABEL_34;
      }
      v44 = v69 * v69 + v68 * v68;
      v45 = v67 * v67;
    }
    else
    {
      if ( v72 * (v30->xyzw.z - v29->xyzw.z) + (v30->xyzw.y - v29->xyzw.y) * v71 + (v30->xyzw.x - v29->xyzw.x) * v70 >= 0.0 )
        goto LABEL_34;
      v44 = v72 * v72 + v71 * v71;
      v45 = v70 * v70;
    }
    if ( v44 + v45 > radiusSqr )
      goto LABEL_48;
LABEL_34:
    v80 = v68 * v66 - v69 * v65;
    v81 = v69 * v64 - v66 * v67;
    v82 = v65 * v67 - v68 * v64;
    if ( v81 * *p_b + v80 * *(p_b - 1) + v82 * p_b[1] > 0.0 )
    {
      if ( radiusSqr <= 0.0 )
        goto LABEL_48;
      v46 = v38->xyzw.x - v29->xyzw.x;
      v47 = v38->xyzw.y - v29->xyzw.y;
      v48 = v38->xyzw.z - v29->xyzw.z;
      d2c = v48 * v48 + v47 * v47 + v46 * v46;
      if ( d2c * radiusSqr < v82 * v82 + v81 * v81 + v80 * v80 )
        goto LABEL_48;
      v49 = v48 * v69 + v47 * v68 + v46 * v67;
      if ( v49 >= 0.0 )
      {
        if ( v49 > d2c
          && v66 * (v29->xyzw.z - v30->xyzw.z) + (v29->xyzw.y - v30->xyzw.y) * v65 + (v29->xyzw.x - v30->xyzw.x) * v64 < 0.0 )
        {
          v50 = v64 * v64 + v66 * v66;
          v51 = v65 * v65;
LABEL_43:
          if ( v50 + v51 > radiusSqr )
            goto LABEL_48;
        }
      }
      else if ( v69 * (v38->xyzw.z - v30->xyzw.z)
              + (v38->xyzw.y - v30->xyzw.y) * v68
              + (v38->xyzw.x - v30->xyzw.x) * v67 < 0.0 )
      {
        v50 = v69 * v69 + v68 * v68;
        v51 = v67 * v67;
        goto LABEL_43;
      }
    }
    ++*c_intersect;
    hit->fraction = fa;
    hit->normal = *(idVec3 *)(p_b - 1);
    hit->point = *(idVec3 *)v77;
    hit->indexes[0] = v17 + v79->m_silTraceGeoSpec.m_indexStart;
    hit->indexes[1] = v79->m_silTraceGeoSpec.m_indexStart + v17 + 1;
    hit->indexes[2] = v79->m_silTraceGeoSpec.m_indexStart + v17 + 2;
    hit->vertices[0].x = v29->xyzw.x;
    hit->vertices[0].y = v29->xyzw.y;
    hit->vertices[0].z = v29->xyzw.z;
    hit->vertices[1] = *(idVec3 *)&v30->xyzw.x;
    hit->vertices[2] = *(idVec3 *)&v38->xyzw.x;
    if ( (drawIB->m_flags & 4) != 0 )
    {
      v52 = *((unsigned __int16 *)drawIndexMemPtr + v17);
      v53 = *((unsigned __int16 *)drawIndexMemPtr + v17 + 1);
      v54 = *(unsigned __int16 *)&v76[v89];
    }
    else
    {
      v52 = *((_DWORD *)drawIndexMemPtr + v17);
      v53 = *((_DWORD *)drawIndexMemPtr + v17 + 1);
      v54 = *(_DWORD *)&v74[v89];
    }
    v55 = v53 - base;
    v56 = v54 - base;
    hit->drawIndices[0] = v52 - base;
    hit->drawIndices[1] = v55;
    hit->drawIndices[2] = v56;
    goto LABEL_48;
  }
LABEL_50:
  rvIndexBuffer::Unlock(drawIB);
  rvIndexBuffer::Unlock(v13);
}

// FUNC: public: class rvDeclMatType const * __thiscall rvPrimBatch::GetMaterialType(class idMaterial const *,struct localTrace_s const &,class rvVertexBuffer &)
const rvDeclMatType *__thiscall rvPrimBatch::GetMaterialType(
        rvPrimBatch *this,
        idMaterial *shader,
        const localTrace_s *hit,
        rvVertexBuffer *drawVB)
{
  rvVertexBuffer *v5; // ebx
  float x; // ecx
  float y; // edx
  float z; // eax
  float v9; // ecx
  int v10; // eax
  float *v11; // eax
  double v12; // st7
  int v13; // eax
  double v14; // st7
  int v15; // eax
  int v16; // eax
  float v17; // ecx
  float *texCoordBasePtr; // [esp+10h] [ebp-48h] BYREF
  idVec2 result; // [esp+14h] [ebp-44h] BYREF
  idVec2 tc[3]; // [esp+1Ch] [ebp-3Ch] BYREF
  idVec3 t[3]; // [esp+34h] [ebp-24h] BYREF
  float shadera; // [esp+5Ch] [ebp+4h]

  if ( !shader->materialTypeArray )
    return shader->materialType;
  v5 = drawVB;
  if ( (drawVB->m_flags & 1) == 0 )
    return shader->materialType;
  if ( (drawVB->m_format.m_flags & 0x400) == 0 )
    return shader->materialType;
  rvVertexBuffer::LockTextureCoordinate(
    drawVB,
    0,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&texCoordBasePtr,
    (int *)&drawVB);
  x = hit->vertices[0].x;
  y = hit->vertices[0].y;
  t[0].z = hit->vertices[0].z;
  t[1].z = hit->vertices[1].z;
  z = hit->vertices[2].z;
  t[0].x = x;
  v9 = hit->vertices[1].x;
  t[2].z = z;
  v10 = hit->drawIndices[0];
  t[1].x = v9;
  t[2].x = hit->vertices[2].x;
  t[0].y = y;
  t[1].y = hit->vertices[1].y;
  t[2].y = hit->vertices[2].y;
  v11 = (float *)((char *)texCoordBasePtr + (_DWORD)drawVB * v10);
  v12 = v11[1];
  tc[0].x = *v11;
  tc[0].y = v12;
  v13 = (_DWORD)drawVB * hit->drawIndices[1];
  v14 = *(float *)((char *)texCoordBasePtr + v13 + 4);
  tc[1].x = *(float *)((char *)texCoordBasePtr + v13);
  v15 = hit->drawIndices[2];
  tc[1].y = v14;
  v16 = (_DWORD)drawVB * v15;
  v17 = *(float *)((char *)texCoordBasePtr + v16);
  tc[2].y = *(float *)((char *)texCoordBasePtr + v16 + 4);
  tc[2].x = v17;
  shadera = idMath::BarycentricTriangleArea(&hit->normal, t, &t[1], &t[2]);
  if ( shadera == 0.0 )
    return shader->materialType;
  idMath::BarycentricEvaluate(&result, &hit->point, &hit->normal, shadera, t, tc);
  rvVertexBuffer::Unlock(v5);
  return idMaterial::GetMaterialType(shader, &result);
}

// FUNC: public: void __thiscall rvPrimBatch::CreateLightTris(int *,int &,class idBounds &,int &,int &,unsigned char const *,unsigned char const *,class idPlane const * const,class rvSilTraceVertT const *,bool,class rvIndexBuffer &,class rvIndexBuffer &)
void __thiscall rvPrimBatch::CreateLightTris(
        rvPrimBatch *this,
        int *destDrawIndices,
        int *destIndexCount,
        idBounds *bounds,
        int *c_backfaced,
        int *c_distance,
        const unsigned __int8 *facing,
        const unsigned __int8 *cullBits,
        const idPlane *localClipPlanes,
        const rvSilTraceVertT *silTraceVerts,
        bool includeBackFaces,
        rvIndexBuffer *silTraceIB,
        rvIndexBuffer *drawIB)
{
  int v14; // esi
  int v15; // ebx
  int v16; // eax
  void *v17; // esp
  bool v18; // zf
  int *v19; // ecx
  const unsigned __int8 *v20; // edi
  unsigned int v21; // esi
  int v22; // edx
  int v23; // edx
  int v24; // eax
  int v25; // esi
  int v26; // edx
  int v27; // eax
  int *v28; // ecx
  int *v29; // edi
  unsigned int v30; // esi
  int v31; // edx
  int v32; // edx
  int v33; // eax
  int v34; // esi
  int v35; // edx
  int v36; // eax
  _BYTE v37[8]; // [esp+0h] [ebp-3Ch] BYREF
  int v38; // [esp+8h] [ebp-34h] BYREF
  int *destSilTraceIndices; // [esp+Ch] [ebp-30h]
  void *silTraceIndexMemPtr; // [esp+10h] [ebp-2Ch] BYREF
  void *drawIndexMemPtr; // [esp+14h] [ebp-28h] BYREF
  unsigned int v42; // [esp+18h] [ebp-24h]
  int v43; // [esp+1Ch] [ebp-20h]
  int i2; // [esp+20h] [ebp-1Ch]
  int i1; // [esp+24h] [ebp-18h]
  const unsigned __int8 *v46; // [esp+28h] [ebp-14h]
  int *v47; // [esp+2Ch] [ebp-10h]
  unsigned __int16 *v48; // [esp+30h] [ebp-Ch]
  const unsigned __int8 *v49; // [esp+34h] [ebp-8h]
  bool drawIBis16Bit; // [esp+3Bh] [ebp-1h]
  int i3; // [esp+58h] [ebp+1Ch]
  int i3a; // [esp+58h] [ebp+1Ch]

  v14 = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  v15 = 0;
  rvIndexBuffer::Lock(silTraceIB, this->m_silTraceGeoSpec.m_indexStart, v14, 1u, &silTraceIndexMemPtr);
  rvIndexBuffer::Lock(drawIB, this->m_drawGeoSpec.m_indexStart, v14, 1u, &drawIndexMemPtr);
  v16 = 4 * v14 + 3;
  LOBYTE(v16) = v16 & 0xFC;
  v17 = alloca(v16);
  drawIBis16Bit = (drawIB->m_flags & 4) != 0;
  v18 = (silTraceIB->m_flags & 4) == 0;
  destSilTraceIndices = (int *)v37;
  if ( v18 )
  {
    if ( v14 > 0 )
    {
      v49 = facing;
      v46 = (const unsigned __int8 *)drawIndexMemPtr + 4;
      v43 = (char *)destDrawIndices - v37;
      v48 = (unsigned __int16 *)((char *)drawIndexMemPtr + 8);
      v28 = &v38;
      v29 = (int *)((char *)silTraceIndexMemPtr + 8);
      v30 = (v14 - 1) / 3u + 1;
      v47 = (int *)((char *)silTraceIndexMemPtr + 8);
      v42 = v30;
      do
      {
        if ( includeBackFaces || *v49 )
        {
          v31 = *v29;
          i1 = *(v29 - 2);
          i3a = v31;
          LOBYTE(v31) = cullBits[*(v29 - 1)] & cullBits[v31];
          i2 = *(v29 - 1);
          if ( ((unsigned __int8)v31 & cullBits[i1]) != 0 )
          {
            ++*c_distance;
          }
          else
          {
            v18 = !drawIBis16Bit;
            v32 = i2;
            *(v28 - 2) = i1;
            *(v28 - 1) = v32;
            *v28 = i3a;
            if ( v18 )
            {
              v33 = *((_DWORD *)v48 - 2);
              v34 = *((_DWORD *)v48 - 1);
              v35 = *(_DWORD *)v48;
            }
            else
            {
              v33 = *((unsigned __int16 *)v46 - 2);
              v34 = *((unsigned __int16 *)v46 - 1);
              v35 = *(unsigned __int16 *)v46;
            }
            destDrawIndices[v15] = v33;
            v36 = v43;
            destDrawIndices[v15 + 1] = v34;
            v30 = v42;
            *(int *)((char *)v28 + v36) = v35;
            v15 += 3;
            v28 += 3;
          }
          v29 = v47;
        }
        else
        {
          ++*c_backfaced;
        }
        v46 += 6;
        v48 += 6;
        ++v49;
        v29 += 3;
        --v30;
        v47 = v29;
        v42 = v30;
      }
      while ( v30 );
    }
  }
  else if ( v14 > 0 )
  {
    v46 = facing;
    v48 = (unsigned __int16 *)((char *)drawIndexMemPtr + 4);
    v43 = (char *)destDrawIndices - v37;
    v47 = (int *)((char *)drawIndexMemPtr + 8);
    v19 = &v38;
    v20 = (const unsigned __int8 *)silTraceIndexMemPtr + 4;
    v21 = (v14 - 1) / 3u + 1;
    v49 = (const unsigned __int8 *)silTraceIndexMemPtr + 4;
    v42 = v21;
    do
    {
      if ( includeBackFaces || *v46 )
      {
        v22 = *(unsigned __int16 *)v20;
        i1 = *((unsigned __int16 *)v20 - 2);
        i3 = v22;
        LOBYTE(v22) = cullBits[*((unsigned __int16 *)v20 - 1)] & cullBits[v22];
        i2 = *((unsigned __int16 *)v20 - 1);
        if ( ((unsigned __int8)v22 & cullBits[i1]) != 0 )
        {
          ++*c_distance;
        }
        else
        {
          v18 = !drawIBis16Bit;
          v23 = i2;
          *(v19 - 2) = i1;
          *(v19 - 1) = v23;
          *v19 = i3;
          if ( v18 )
          {
            v24 = *(v47 - 2);
            v25 = *(v47 - 1);
            v26 = *v47;
          }
          else
          {
            v24 = *(v48 - 2);
            v25 = *(v48 - 1);
            v26 = *v48;
          }
          destDrawIndices[v15] = v24;
          v27 = v43;
          destDrawIndices[v15 + 1] = v25;
          v21 = v42;
          *(int *)((char *)v19 + v27) = v26;
          v15 += 3;
          v19 += 3;
        }
        v20 = v49;
      }
      else
      {
        ++*c_backfaced;
      }
      v48 += 3;
      v47 += 3;
      ++v46;
      v20 += 6;
      --v21;
      v49 = v20;
      v42 = v21;
    }
    while ( v21 );
  }
  *destIndexCount = v15;
  rvIndexBuffer::Unlock(drawIB);
  rvIndexBuffer::Unlock(silTraceIB);
  (*(void (__thiscall **)(idSIMDProcessor *, idVec3 *, const rvSilTraceVertT *, int *, _DWORD))SIMDProcessor->gap7C)(
    SIMDProcessor,
    &bounds->b[1],
    silTraceVerts,
    destSilTraceIndices,
    *destIndexCount);
}

// FUNC: public: void __thiscall rvPrimBatch::CreateFrontFaceTris(int *,int &,class idBounds &,int &,unsigned char const *,class rvSilTraceVertT const *,class rvIndexBuffer &,class rvIndexBuffer &)
void __thiscall rvPrimBatch::CreateFrontFaceTris(
        rvPrimBatch *this,
        int *destDrawIndices,
        int *destIndexCount,
        idBounds *bounds,
        int *c_backfaced,
        const unsigned __int8 *facing,
        const rvSilTraceVertT *silTraceVerts,
        rvIndexBuffer *silTraceIB,
        rvIndexBuffer *drawIB)
{
  int v10; // esi
  int v11; // edi
  int v12; // eax
  void *v13; // esp
  bool v14; // zf
  int *v15; // ebx
  int *v16; // eax
  int *v17; // ecx
  unsigned __int16 *v18; // ebx
  unsigned int v19; // edx
  int v20; // eax
  int v21; // esi
  int v22; // ebx
  int *v23; // eax
  int *v24; // ecx
  int *v25; // ebx
  unsigned int v26; // edx
  int v27; // eax
  int v28; // esi
  int v29; // ebx
  _BYTE v30[8]; // [esp+0h] [ebp-30h] BYREF
  int v31; // [esp+8h] [ebp-28h] BYREF
  void *silTraceIndexMemPtr; // [esp+Ch] [ebp-24h] BYREF
  void *drawIndexMemPtr; // [esp+10h] [ebp-20h] BYREF
  int *v34; // [esp+14h] [ebp-1Ch]
  int v35; // [esp+18h] [ebp-18h]
  const unsigned __int8 *v36; // [esp+1Ch] [ebp-14h]
  int *v37; // [esp+20h] [ebp-10h]
  const unsigned __int8 *v38; // [esp+24h] [ebp-Ch]
  int *destSilTraceIndices; // [esp+28h] [ebp-8h]
  bool drawIBIs16Bit; // [esp+2Fh] [ebp-1h]
  int i3; // [esp+48h] [ebp+18h]
  int i3a; // [esp+48h] [ebp+18h]

  v10 = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  v11 = 0;
  rvIndexBuffer::Lock(silTraceIB, this->m_silTraceGeoSpec.m_indexStart, v10, 1u, &silTraceIndexMemPtr);
  rvIndexBuffer::Lock(drawIB, this->m_drawGeoSpec.m_indexStart, v10, 1u, &drawIndexMemPtr);
  v12 = 4 * v10 + 3;
  LOBYTE(v12) = v12 & 0xFC;
  v13 = alloca(v12);
  drawIBIs16Bit = (drawIB->m_flags & 4) != 0;
  v14 = (silTraceIB->m_flags & 4) == 0;
  v15 = (int *)v30;
  destSilTraceIndices = (int *)v30;
  if ( v14 )
  {
    if ( v10 > 0 )
    {
      v36 = (const unsigned __int8 *)drawIndexMemPtr + 4;
      v37 = (int *)((char *)drawIndexMemPtr + 8);
      v35 = (char *)destDrawIndices - (char *)destSilTraceIndices;
      v23 = c_backfaced;
      v38 = facing;
      v24 = &v31;
      v25 = (int *)((char *)silTraceIndexMemPtr + 8);
      v34 = (int *)((char *)silTraceIndexMemPtr + 8);
      v26 = (v10 - 1) / 3u + 1;
      do
      {
        if ( *v38 )
        {
          v14 = !drawIBIs16Bit;
          *(v24 - 2) = *(v25 - 2);
          *(v24 - 1) = *(v25 - 1);
          *v24 = *v25;
          if ( v14 )
          {
            v27 = *(v37 - 2);
            v28 = *(v37 - 1);
            v29 = *v37;
          }
          else
          {
            v27 = *((unsigned __int16 *)v36 - 2);
            v28 = *((unsigned __int16 *)v36 - 1);
            v29 = *(unsigned __int16 *)v36;
          }
          i3a = v29;
          destDrawIndices[v11] = v27;
          destDrawIndices[v11 + 1] = v28;
          v25 = v34;
          *(int *)((char *)v24 + v35) = i3a;
          v23 = c_backfaced;
          v11 += 3;
          v24 += 3;
        }
        else
        {
          ++*v23;
        }
        v36 += 6;
        v37 += 3;
        ++v38;
        v25 += 3;
        --v26;
        v34 = v25;
      }
      while ( v26 );
      goto LABEL_21;
    }
  }
  else if ( v10 > 0 )
  {
    v38 = (const unsigned __int8 *)drawIndexMemPtr + 4;
    v35 = (char *)destDrawIndices - v30;
    v37 = (int *)((char *)drawIndexMemPtr + 8);
    v16 = c_backfaced;
    v36 = facing;
    v17 = &v31;
    v18 = (unsigned __int16 *)((char *)silTraceIndexMemPtr + 4);
    v34 = (int *)((char *)silTraceIndexMemPtr + 4);
    v19 = (v10 - 1) / 3u + 1;
    do
    {
      if ( *v36 )
      {
        v14 = !drawIBIs16Bit;
        *(v17 - 2) = *(v18 - 2);
        *(v17 - 1) = *(v18 - 1);
        *v17 = *v18;
        if ( v14 )
        {
          v20 = *(v37 - 2);
          v21 = *(v37 - 1);
          v22 = *v37;
        }
        else
        {
          v20 = *((unsigned __int16 *)v38 - 2);
          v21 = *((unsigned __int16 *)v38 - 1);
          v22 = *(unsigned __int16 *)v38;
        }
        i3 = v22;
        destDrawIndices[v11] = v20;
        destDrawIndices[v11 + 1] = v21;
        v18 = (unsigned __int16 *)v34;
        *(int *)((char *)v17 + v35) = i3;
        v16 = c_backfaced;
        v11 += 3;
        v17 += 3;
      }
      else
      {
        ++*v16;
      }
      v38 += 6;
      v37 += 3;
      ++v36;
      v18 += 3;
      --v19;
      v34 = (int *)v18;
    }
    while ( v19 );
LABEL_21:
    v15 = destSilTraceIndices;
  }
  *destIndexCount = v11;
  rvIndexBuffer::Unlock(drawIB);
  rvIndexBuffer::Unlock(silTraceIB);
  (*(void (__thiscall **)(idSIMDProcessor *, idVec3 *, const rvSilTraceVertT *, int *, _DWORD))SIMDProcessor->gap7C)(
    SIMDProcessor,
    &bounds->b[1],
    silTraceVerts,
    v15,
    *destIndexCount);
}

// FUNC: public: void __thiscall rvPrimBatch::GetTriangle(class idDrawVert &,class idDrawVert &,class idDrawVert &,int,class rvVertexBuffer &,class rvIndexBuffer &,class rvSilTraceVertT const *,class rvIndexBuffer &)
void __thiscall rvPrimBatch::GetTriangle(
        rvPrimBatch *this,
        idDrawVert *a,
        idDrawVert *b,
        idDrawVert *c,
        int triOffset,
        rvVertexBuffer *drawVertexBuffer,
        rvIndexBuffer *drawIndexBuffer,
        const rvSilTraceVertT *silTraceVerts,
        rvIndexBuffer *silTraceIndexBuffer)
{
  rvIndexBuffer *v9; // ebx
  int v10; // edi
  int m_vertexStart; // ebp
  int v13; // esi
  int v14; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // eax
  int v21; // edx
  const rvSilTraceVertT *v22; // esi
  float x; // ebp
  const rvSilTraceVertT *v24; // edi
  float *v25; // ebp
  float *v26; // eax
  const rvSilTraceVertT *v27; // ebx
  double v28; // st7
  int v29; // ecx
  int v30; // edx
  double v31; // st7
  rvVertexBuffer *v32; // ecx
  double v33; // st7
  void *indexMemPtr; // [esp+10h] [ebp-10h] BYREF
  const rvSilTraceVertT *v35; // [esp+14h] [ebp-Ch]
  int texCoordStride; // [esp+18h] [ebp-8h] BYREF
  float *texCoordSrc; // [esp+1Ch] [ebp-4h] BYREF

  v9 = silTraceIndexBuffer;
  v10 = 3 * triOffset;
  m_vertexStart = this->m_drawGeoSpec.m_vertexStart;
  rvIndexBuffer::Lock(
    silTraceIndexBuffer,
    3 * triOffset + this->m_silTraceGeoSpec.m_indexStart,
    3,
    1u,
    (void **)&triOffset);
  rvIndexBuffer::Lock(drawIndexBuffer, v10 + this->m_drawGeoSpec.m_indexStart, 3, 1u, &indexMemPtr);
  rvVertexBuffer::LockTextureCoordinate(
    drawVertexBuffer,
    0,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&texCoordSrc,
    &texCoordStride);
  if ( (v9->m_flags & 4) != 0 )
  {
    v13 = *(unsigned __int16 *)triOffset;
    v14 = *(unsigned __int16 *)(triOffset + 2);
    v15 = *(unsigned __int16 *)(triOffset + 4);
  }
  else
  {
    v13 = *(_DWORD *)triOffset;
    v14 = *(_DWORD *)(triOffset + 4);
    v15 = *(_DWORD *)(triOffset + 8);
  }
  if ( (drawIndexBuffer->m_flags & 4) != 0 )
  {
    v16 = *(unsigned __int16 *)indexMemPtr;
    v17 = *((unsigned __int16 *)indexMemPtr + 1);
    v18 = *((unsigned __int16 *)indexMemPtr + 2);
  }
  else
  {
    v16 = *(_DWORD *)indexMemPtr;
    v17 = *((_DWORD *)indexMemPtr + 1);
    v18 = *((_DWORD *)indexMemPtr + 2);
  }
  v19 = v17 - m_vertexStart;
  v20 = texCoordStride * (v16 - m_vertexStart);
  v21 = v18 - m_vertexStart;
  v22 = &silTraceVerts[v13];
  x = v22->xyzw.x;
  v24 = &silTraceVerts[v14];
  v35 = v22;
  a->xyz.x = x;
  a->xyz.y = v35->xyzw.y;
  a->xyz.z = v35->xyzw.z;
  v25 = texCoordSrc;
  v26 = (float *)((char *)texCoordSrc + v20);
  v27 = &silTraceVerts[v15];
  v28 = v26[1];
  a->st.x = *v26;
  a->st.y = v28;
  b->xyz.x = v24->xyzw.x;
  b->xyz.y = v24->xyzw.y;
  b->xyz.z = v24->xyzw.z;
  v29 = texCoordStride * v19;
  v30 = texCoordStride * v21;
  v31 = *(float *)((char *)v25 + v29 + 4);
  b->st.x = *(float *)((char *)v25 + v29);
  b->st.y = v31;
  c->xyz.x = v27->xyzw.x;
  c->xyz.y = v27->xyzw.y;
  c->xyz.z = v27->xyzw.z;
  v32 = drawVertexBuffer;
  v33 = *(float *)((char *)v25 + v30 + 4);
  c->st.x = *(float *)((char *)v25 + v30);
  c->st.y = v33;
  rvVertexBuffer::Unlock(v32);
  rvIndexBuffer::Unlock(drawIndexBuffer);
  rvIndexBuffer::Unlock(silTraceIndexBuffer);
}

// FUNC: public: void __thiscall rvPrimBatch::CopyTriangles(class idDrawVert *,int *,class rvVertexBuffer &,class rvIndexBuffer &,class rvSilTraceVertT const *,class rvIndexBuffer &,int)
void __thiscall rvPrimBatch::CopyTriangles(
        rvPrimBatch *this,
        idDrawVert *destDrawVerts,
        char *destIndices,
        rvVertexBuffer *drawVertexBuffer,
        rvIndexBuffer *drawIndexBuffer,
        const rvSilTraceVertT *silTraceVerts,
        rvIndexBuffer *silTraceIndexBuffer,
        int destBase)
{
  int m_vertexStart; // ebx
  int v10; // edi
  char *v11; // ebp
  int v12; // ecx
  bool v13; // dl
  int v14; // esi
  unsigned int *v15; // edi
  char *v16; // ecx
  int *v17; // eax
  int v18; // ebp
  int v19; // edx
  unsigned int v20; // edi
  int v21; // ebp
  int v22; // edx
  unsigned int v23; // edi
  int v24; // ebp
  int v25; // edx
  idDrawVert *v26; // eax
  idDrawVert *v27; // ecx
  idDrawVert *v28; // esi
  float *v29; // edi
  int v30; // eax
  unsigned __int8 *v31; // edi
  float *v32; // ebp
  int v33; // eax
  unsigned __int8 *v34; // eax
  float *v35; // edx
  int *v36; // eax
  bool v37; // cc
  int m_indexStart; // [esp-10h] [ebp-74h]
  int v39; // [esp-10h] [ebp-74h]
  bool silTraceIs16Bit; // [esp+12h] [ebp-52h]
  bool drawIBIs16Bit; // [esp+13h] [ebp-51h]
  int *v42; // [esp+14h] [ebp-50h]
  unsigned __int16 *v43; // [esp+18h] [ebp-4Ch]
  int diffuseColorStride; // [esp+1Ch] [ebp-48h] BYREF
  unsigned int *diffuseColorSrc; // [esp+20h] [ebp-44h] BYREF
  int texCoordStride; // [esp+24h] [ebp-40h] BYREF
  float *texCoordSrc; // [esp+28h] [ebp-3Ch] BYREF
  unsigned int *drawIndex32; // [esp+2Ch] [ebp-38h]
  unsigned __int16 *drawIndex16; // [esp+30h] [ebp-34h]
  int sil1; // [esp+34h] [ebp-30h]
  int sil2; // [esp+38h] [ebp-2Ch]
  int i; // [esp+3Ch] [ebp-28h]
  int *v53; // [esp+40h] [ebp-24h]
  void *silTraceIndexMemPtr; // [esp+44h] [ebp-20h] BYREF
  void *drawIndexMemPtr; // [esp+48h] [ebp-1Ch] BYREF
  int base; // [esp+4Ch] [ebp-18h]
  int v57; // [esp+50h] [ebp-14h]
  int v58; // [esp+54h] [ebp-10h]
  int v59; // [esp+58h] [ebp-Ch]
  char *v60; // [esp+5Ch] [ebp-8h]
  int numIndices; // [esp+60h] [ebp-4h]
  int *destIndicesa; // [esp+6Ch] [ebp+8h]
  int *destIndicesb; // [esp+6Ch] [ebp+8h]
  int *destIndicesc; // [esp+6Ch] [ebp+8h]

  m_vertexStart = this->m_drawGeoSpec.m_vertexStart;
  v10 = 3 * this->m_drawGeoSpec.m_primitiveCount;
  m_indexStart = this->m_silTraceGeoSpec.m_indexStart;
  base = m_vertexStart;
  numIndices = v10;
  rvIndexBuffer::Lock(silTraceIndexBuffer, m_indexStart, v10, 1u, &silTraceIndexMemPtr);
  v11 = (char *)silTraceIndexMemPtr;
  v39 = this->m_drawGeoSpec.m_indexStart;
  sil2 = (int)silTraceIndexMemPtr;
  rvIndexBuffer::Lock(drawIndexBuffer, v39, v10, 1u, &drawIndexMemPtr);
  v12 = this->m_drawGeoSpec.m_vertexStart;
  drawIndex16 = (unsigned __int16 *)drawIndexMemPtr;
  drawIndex32 = (unsigned int *)drawIndexMemPtr;
  rvVertexBuffer::LockTextureCoordinate(
    drawVertexBuffer,
    0,
    v12,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&texCoordSrc,
    &texCoordStride);
  rvVertexBuffer::LockDiffuseColor(
    drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&diffuseColorSrc,
    &diffuseColorStride);
  v13 = (silTraceIndexBuffer->m_flags & 4) != 0;
  v14 = 0;
  silTraceIs16Bit = v13;
  drawIBIs16Bit = (drawIndexBuffer->m_flags & 4) != 0;
  i = 0;
  if ( v10 > 0 )
  {
    v42 = (int *)(v11 + 8);
    v43 = (unsigned __int16 *)(v11 + 4);
    v15 = drawIndex32;
    v58 = (char *)drawIndex16 - v11;
    v59 = (char *)drawIndex32 - v11;
    v16 = (char *)(destIndices - v11);
    v17 = (int *)(destIndices + 4);
    v18 = (char *)drawIndex32 - destIndices;
    v53 = (int *)(destIndices + 4);
    v60 = v16;
    v57 = (char *)drawIndex32 - destIndices;
    while ( 1 )
    {
      if ( v13 )
      {
        destIndicesa = (int *)*(v43 - 2);
        sil1 = *(v43 - 1);
        v19 = *v43;
      }
      else
      {
        destIndicesa = (int *)*(v42 - 2);
        sil1 = *(v42 - 1);
        v19 = *v42;
      }
      sil2 = v19;
      if ( drawIBIs16Bit )
      {
        v20 = drawIndex16[v14];
        v21 = drawIndex16[v14 + 1];
        v22 = *(unsigned __int16 *)((char *)v43 + v58);
      }
      else
      {
        v20 = v15[v14];
        v21 = *(int *)((char *)v17 + v18);
        v22 = *(int *)((char *)v42 + v59);
      }
      v23 = v20 - m_vertexStart;
      v24 = v21 - m_vertexStart;
      v25 = v22 - m_vertexStart;
      *(v17 - 1) = v23 + destBase;
      *v17 = destBase + v24;
      *(int *)((char *)v42 + (_DWORD)v60) = v25 + destBase;
      v26 = &destDrawVerts[v23];
      v27 = &destDrawVerts[v24];
      v28 = &destDrawVerts[v25];
      destIndicesb = (int *)&silTraceVerts[(_DWORD)destIndicesa];
      LODWORD(v26->xyz.x) = *destIndicesb;
      LODWORD(v26->xyz.y) = destIndicesb[1];
      LODWORD(v26->xyz.z) = destIndicesb[2];
      destIndicesc = (int *)((char *)diffuseColorSrc + diffuseColorStride * v23);
      v26->color[0] = *(_BYTE *)destIndicesc;
      v26->color[1] = *((_BYTE *)destIndicesc + 1);
      v26->color[2] = *((_BYTE *)destIndicesc + 2);
      v26->color[3] = *((_BYTE *)destIndicesc + 3);
      v29 = (float *)((char *)texCoordSrc + texCoordStride * v23);
      v26->st.x = *v29;
      v26->st.y = v29[1];
      v30 = sil1;
      v27->xyz.x = silTraceVerts[sil1].xyzw.x;
      v27->xyz.y = silTraceVerts[v30].xyzw.y;
      v27->xyz.z = silTraceVerts[v30].xyzw.z;
      v31 = (unsigned __int8 *)diffuseColorSrc + diffuseColorStride * v24;
      v27->color[0] = *v31;
      v27->color[1] = v31[1];
      v27->color[2] = v31[2];
      v27->color[3] = v31[3];
      v32 = (float *)((char *)texCoordSrc + texCoordStride * v24);
      v27->st.x = *v32;
      v27->st.y = v32[1];
      v33 = sil2;
      v28->xyz.x = silTraceVerts[sil2].xyzw.x;
      v28->xyz.y = silTraceVerts[v33].xyzw.y;
      v28->xyz.z = silTraceVerts[v33].xyzw.z;
      v34 = (unsigned __int8 *)diffuseColorSrc + diffuseColorStride * v25;
      v43 += 3;
      v28->color[0] = *v34;
      v28->color[1] = v34[1];
      v28->color[2] = v34[2];
      v28->color[3] = v34[3];
      v35 = (float *)((char *)texCoordSrc + texCoordStride * v25);
      v36 = v53;
      v42 += 3;
      v28->st.x = *v35;
      v28->st.y = v35[1];
      v14 = i + 3;
      v17 = v36 + 3;
      v37 = i + 3 < numIndices;
      i += 3;
      v53 = v17;
      if ( !v37 )
        break;
      m_vertexStart = base;
      v13 = silTraceIs16Bit;
      v18 = v57;
      v15 = drawIndex32;
    }
  }
  rvVertexBuffer::Unlock(drawVertexBuffer);
  rvIndexBuffer::Unlock(drawIndexBuffer);
  rvIndexBuffer::Unlock(silTraceIndexBuffer);
}

// FUNC: public: void __thiscall rvPrimBatch::TransformDrawVertices(class idDrawVert *,class rvVertexBuffer &,class idMat4 const &,int,unsigned char * const)
void __thiscall rvPrimBatch::TransformDrawVertices(
        rvPrimBatch *this,
        idDrawVert *destDrawVerts,
        rvVertexBuffer *drawVertexBuffer,
        const idMat4 *transform,
        char colorShift,
        unsigned __int8 *colorAdd)
{
  rvVertexBuffer *v6; // edi
  idDrawVert *v8; // esi
  float *v9; // edi
  float *v10; // ebx
  float *v11; // ebp
  unsigned __int8 *v12; // esi
  float *p_z; // edx
  float v14; // ecx
  double v15; // st7
  double v16; // st6
  double v17; // st5
  double v18; // st7
  double v19; // st6
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st6
  float *v24; // eax
  bool v25; // zf
  float v26; // [esp+8h] [ebp-48h]
  float v27; // [esp+Ch] [ebp-44h]
  float v28; // [esp+Ch] [ebp-44h]
  float *positionSrc; // [esp+10h] [ebp-40h] BYREF
  float *texCoordSrc; // [esp+14h] [ebp-3Ch] BYREF
  float *normalSrc; // [esp+18h] [ebp-38h] BYREF
  float *tangentSrc; // [esp+1Ch] [ebp-34h] BYREF
  float *binormalSrc; // [esp+20h] [ebp-30h] BYREF
  unsigned __int8 *diffuseColorSrc; // [esp+24h] [ebp-2Ch] BYREF
  unsigned int v35; // [esp+28h] [ebp-28h]
  int positionStride; // [esp+2Ch] [ebp-24h] BYREF
  int normalStride; // [esp+30h] [ebp-20h] BYREF
  int tangentStride; // [esp+34h] [ebp-1Ch] BYREF
  int binormalStride; // [esp+38h] [ebp-18h] BYREF
  int texCoordStride; // [esp+3Ch] [ebp-14h] BYREF
  int diffuseColorStride[3]; // [esp+40h] [ebp-10h] BYREF
  float v42; // [esp+4Ch] [ebp-4h]

  v6 = drawVertexBuffer;
  rvVertexBuffer::LockPosition(
    drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&positionSrc,
    &positionStride);
  rvVertexBuffer::LockNormal(
    drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&normalSrc,
    &normalStride);
  rvVertexBuffer::LockBinormal(
    drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&binormalSrc,
    &binormalStride);
  rvVertexBuffer::LockTangent(
    drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&tangentSrc,
    &tangentStride);
  rvVertexBuffer::LockTextureCoordinate(
    drawVertexBuffer,
    0,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&texCoordSrc,
    &texCoordStride);
  rvVertexBuffer::LockDiffuseColor(
    drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    &diffuseColorSrc,
    diffuseColorStride);
  v8 = &destDrawVerts[this->m_drawGeoSpec.m_vertexCount];
  if ( destDrawVerts < v8 )
  {
    v9 = normalSrc;
    v10 = binormalSrc;
    v11 = tangentSrc;
    v35 = ((unsigned int)((char *)v8 - (char *)destDrawVerts - 1) >> 6) + 1;
    v12 = diffuseColorSrc;
    p_z = &destDrawVerts->normal.z;
    do
    {
      v26 = positionSrc[2];
      v14 = positionSrc[1];
      *(p_z - 6) = *positionSrc;
      *(p_z - 5) = v14;
      *(p_z - 4) = v26;
      v27 = v14 * transform->mat[3].y
          + v26 * transform->mat[3].z
          + transform->mat[3].x * *(p_z - 6)
          + transform->mat[3].w;
      if ( v27 == 0.0 )
      {
        v15 = 0.0;
        v42 = 0.0;
        v16 = 0.0;
      }
      else
      {
        if ( v27 == 1.0 )
        {
          v15 = v14 * transform->mat[0].y
              + v26 * transform->mat[0].z
              + transform->mat[0].x * *(p_z - 6)
              + transform->mat[0].w;
          v16 = v14 * transform->mat[1].y
              + v26 * transform->mat[1].z
              + transform->mat[1].x * *(p_z - 6)
              + transform->mat[1].w;
          v17 = v14 * transform->mat[2].y
              + v26 * transform->mat[2].z
              + transform->mat[2].x * *(p_z - 6)
              + transform->mat[2].w;
        }
        else
        {
          v28 = 1.0 / v27;
          v15 = (v14 * transform->mat[0].y
               + v26 * transform->mat[0].z
               + transform->mat[0].x * *(p_z - 6)
               + transform->mat[0].w)
              * v28;
          v16 = (v14 * transform->mat[1].y
               + v26 * transform->mat[1].z
               + transform->mat[1].x * *(p_z - 6)
               + transform->mat[1].w)
              * v28;
          v17 = (v14 * transform->mat[2].y
               + v26 * transform->mat[2].z
               + transform->mat[2].x * *(p_z - 6)
               + transform->mat[2].w)
              * v28;
        }
        v42 = v17;
      }
      *(p_z - 4) = v42;
      *(p_z - 6) = v15;
      p_z += 16;
      *(p_z - 21) = v16;
      v18 = v9[2];
      v19 = v9[1];
      *(p_z - 18) = *v9;
      *(p_z - 17) = v19;
      v9 = (float *)((char *)v9 + normalStride);
      *(p_z - 16) = v18;
      v20 = v11[2];
      v21 = v11[1];
      *(p_z - 14) = *v11;
      *(p_z - 13) = v21;
      v11 = (float *)((char *)v11 + tangentStride);
      *(p_z - 12) = v20;
      v22 = v10[2];
      v23 = v10[1];
      *(p_z - 11) = *v10;
      v24 = texCoordSrc;
      *(p_z - 10) = v23;
      v10 = (float *)((char *)v10 + binormalStride);
      *(p_z - 9) = v22;
      *(p_z - 8) = *v24;
      *(p_z - 7) = v24[1];
      *((_BYTE *)p_z - 76) = *colorAdd + (*v12 >> colorShift);
      *((_BYTE *)p_z - 75) = colorAdd[1] + (v12[1] >> colorShift);
      *((_BYTE *)p_z - 74) = colorAdd[2] + (v12[2] >> colorShift);
      LOBYTE(v24) = v12[3];
      v12 += diffuseColorStride[0];
      normalSrc = v9;
      tangentSrc = v11;
      LOBYTE(v24) = colorAdd[3] + ((unsigned __int8)v24 >> colorShift);
      texCoordSrc = (float *)((char *)texCoordSrc + texCoordStride);
      *((_BYTE *)p_z - 73) = (_BYTE)v24;
      positionSrc = (float *)((char *)positionSrc + positionStride);
      v25 = v35-- == 1;
      binormalSrc = v10;
      diffuseColorSrc = v12;
    }
    while ( !v25 );
    v6 = drawVertexBuffer;
  }
  rvVertexBuffer::Unlock(v6);
}

// FUNC: public: void __thiscall rvPrimBatch::TubeDeform(class idDrawVert *,int *,class idVec3 const &,class rvVertexBuffer &,class rvIndexBuffer &,class rvSilTraceVertT const *,class rvIndexBuffer &)
void __thiscall rvPrimBatch::TubeDeform(
        rvPrimBatch *this,
        idDrawVert *destDrawVerts,
        int *destIndices,
        const idVec3 *localView,
        rvVertexBuffer *drawVertexBuffer,
        rvIndexBuffer *drawIndexBuffer,
        const rvSilTraceVertT *silTraceVerts,
        rvIndexBuffer *silTraceIndexBuffer)
{
  int m_vertexStart; // ebp
  int v10; // edi
  int v11; // ecx
  int m_vertexCount; // ecx
  int v13; // edx
  bool v14; // bl
  bool v15; // cl
  int v16; // edx
  int *v17; // eax
  int v18; // ebx
  int v19; // ecx
  bool v20; // cc
  int v21; // edi
  int v22; // ebp
  int v23; // eax
  int v24; // esi
  unsigned int v25; // eax
  unsigned int v26; // edx
  unsigned int v27; // eax
  double x; // st7
  const rvSilTraceVertT *v29; // eax
  unsigned int v30; // edx
  double v31; // st7
  const rvSilTraceVertT *v32; // edx
  double v33; // st6
  double v34; // st5
  long double v35; // st4
  float v36; // eax
  int v37; // eax
  int v38; // edx
  unsigned int v39; // eax
  unsigned int v40; // edx
  unsigned int v41; // edx
  double v42; // st7
  const rvSilTraceVertT *v43; // edx
  unsigned int v44; // eax
  double v45; // st7
  const rvSilTraceVertT *v46; // eax
  double v47; // st7
  int v48; // eax
  int v49; // esi
  unsigned int v50; // eax
  unsigned int v51; // esi
  unsigned int v52; // esi
  double v53; // st7
  const rvSilTraceVertT *v54; // esi
  unsigned int v55; // eax
  double v56; // st7
  const rvSilTraceVertT *v57; // eax
  int v58; // ebx
  double v59; // st7
  double v60; // st6
  double v61; // st5
  int v62; // edi
  int v63; // ebp
  unsigned __int8 *v64; // esi
  idDrawVert *v65; // ecx
  idDrawVert *v66; // edx
  float *v67; // edi
  unsigned __int8 *v68; // esi
  float *v69; // ebp
  double v70; // st4
  idVec3 *v71; // esi
  double v72; // st4
  double v73; // st3
  double v74; // st2
  long double v75; // st4
  long double v76; // st4
  double v77; // st4
  double v78; // st3
  double v79; // st4
  double v80; // st3
  double v81; // st3
  double v82; // st4
  int m_indexStart; // [esp-10h] [ebp-114h]
  int v84; // [esp-Ch] [ebp-110h]
  unsigned __int16 *l; // [esp+10h] [ebp-F4h]
  float la; // [esp+10h] [ebp-F4h]
  bool silTraceIs16Bit; // [esp+17h] [ebp-EDh]
  int minor; // [esp+18h] [ebp-ECh]
  int minor_4; // [esp+1Ch] [ebp-E8h]
  int minor_8; // [esp+20h] [ebp-E4h]
  float lengths[2]; // [esp+24h] [ebp-E0h]
  int i; // [esp+2Ch] [ebp-D8h]
  int nums[2]; // [esp+30h] [ebp-D4h]
  unsigned __int16 *silIndex16; // [esp+38h] [ebp-CCh]
  unsigned int *silIndex32; // [esp+3Ch] [ebp-C8h]
  idVec3 mid[2]; // [esp+40h] [ebp-C4h] BYREF
  unsigned int *diffuseColorSrc; // [esp+58h] [ebp-ACh] BYREF
  int diffuseColorStride; // [esp+5Ch] [ebp-A8h] BYREF
  float *texCoordSrc; // [esp+60h] [ebp-A4h] BYREF
  int texCoordStride; // [esp+64h] [ebp-A0h] BYREF
  rvPrimBatch *v101; // [esp+68h] [ebp-9Ch]
  float v102; // [esp+6Ch] [ebp-98h]
  float v103; // [esp+70h] [ebp-94h]
  int v104; // [esp+74h] [ebp-90h]
  int v105; // [esp+78h] [ebp-8Ch]
  int v106; // [esp+7Ch] [ebp-88h]
  int v107; // [esp+80h] [ebp-84h]
  int v108; // [esp+84h] [ebp-80h]
  int v109; // [esp+88h] [ebp-7Ch]
  int v110; // [esp+8Ch] [ebp-78h]
  float v111; // [esp+90h] [ebp-74h]
  float v112; // [esp+94h] [ebp-70h]
  float v113; // [esp+98h] [ebp-6Ch]
  void *silTraceIndexMemPtr; // [esp+9Ch] [ebp-68h] BYREF
  void *drawIndexMemPtr; // [esp+A0h] [ebp-64h] BYREF
  float v116; // [esp+A8h] [ebp-5Ch]
  float v117; // [esp+ACh] [ebp-58h]
  float v118; // [esp+B4h] [ebp-50h]
  float v119; // [esp+B8h] [ebp-4Ch]
  float v120; // [esp+C0h] [ebp-44h]
  float v121; // [esp+C4h] [ebp-40h]
  float v122; // [esp+CCh] [ebp-38h]
  float v123; // [esp+D0h] [ebp-34h]
  float v124; // [esp+DCh] [ebp-28h]
  float v125; // [esp+E8h] [ebp-1Ch]
  float v126; // [esp+F4h] [ebp-10h]
  float v127; // [esp+100h] [ebp-4h]

  m_vertexStart = this->m_drawGeoSpec.m_vertexStart;
  v10 = 3 * this->m_drawGeoSpec.m_primitiveCount;
  v84 = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  m_indexStart = this->m_silTraceGeoSpec.m_indexStart;
  v101 = this;
  rvIndexBuffer::Lock(silTraceIndexBuffer, m_indexStart, v84, 1u, &silTraceIndexMemPtr);
  v11 = this->m_drawGeoSpec.m_indexStart;
  silIndex16 = (unsigned __int16 *)silTraceIndexMemPtr;
  silIndex32 = (unsigned int *)silTraceIndexMemPtr;
  rvIndexBuffer::Lock(drawIndexBuffer, v11, v10, 1u, &drawIndexMemPtr);
  m_vertexCount = this->m_drawGeoSpec.m_vertexCount;
  v13 = this->m_drawGeoSpec.m_vertexStart;
  LODWORD(lengths[0]) = drawIndexMemPtr;
  nums[0] = (int)drawIndexMemPtr;
  rvVertexBuffer::LockTextureCoordinate(
    drawVertexBuffer,
    0,
    v13,
    m_vertexCount,
    1u,
    (unsigned __int8 **)&texCoordSrc,
    &texCoordStride);
  rvVertexBuffer::LockDiffuseColor(
    drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&diffuseColorSrc,
    &diffuseColorStride);
  v14 = (silTraceIndexBuffer->m_flags & 4) != 0;
  v15 = (drawIndexBuffer->m_flags & 4) != 0;
  silTraceIs16Bit = v14;
  i = 0;
  if ( v10 > 0 )
  {
    l = (unsigned __int16 *)(LODWORD(lengths[0]) + 4);
    LODWORD(lengths[0]) = nums[0] - (_DWORD)destIndices;
    v16 = i;
    v17 = destIndices + 2;
    do
    {
      if ( v15 )
      {
        *(v17 - 2) = *(l - 2);
        *(v17 - 1) = *(l - 1);
        v18 = *l;
      }
      else
      {
        *(v17 - 2) = *(_DWORD *)(nums[0] + 4 * v16);
        *(v17 - 1) = *(int *)((char *)v17 + LODWORD(lengths[0]) - 4);
        v18 = *(int *)((char *)v17 + LODWORD(lengths[0]));
      }
      *(v17 - 2) -= m_vertexStart;
      *(v17 - 1) -= m_vertexStart;
      l += 3;
      *v17 = v18;
      *v17 -= m_vertexStart;
      v16 += 3;
      v17 += 3;
    }
    while ( v16 < v10 );
    v14 = silTraceIs16Bit;
  }
  v19 = 0;
  v20 = this->m_drawGeoSpec.m_vertexCount <= 0;
  i = 0;
  if ( !v20 )
  {
    while ( 1 )
    {
      v21 = 0;
      v22 = 0;
      nums[1] = 0;
      nums[0] = 0;
      lengths[1] = 999999.0;
      lengths[0] = 999999.0;
      do
      {
        v23 = v19 + edgeVerts[v21][0];
        v24 = v19 + dword_102FD0D8[2 * v21];
        if ( v14 )
        {
          v25 = silIndex16[v23];
          v26 = silIndex16[v24];
        }
        else
        {
          v25 = silIndex32[v23];
          v26 = silIndex32[v24];
        }
        v27 = v25;
        x = silTraceVerts[v27].xyzw.x;
        v29 = &silTraceVerts[v27];
        v30 = v26;
        v31 = x - silTraceVerts[v30].xyzw.x;
        v32 = &silTraceVerts[v30];
        v33 = v29->xyzw.y - v32->xyzw.y;
        v34 = v29->xyzw.z - v32->xyzw.z;
        v35 = sqrt(v33 * v33 + v31 * v31 + v34 * v34);
        if ( v35 >= lengths[0] )
        {
          if ( v35 < lengths[1] )
          {
            lengths[1] = v35;
            nums[1] = v21;
          }
        }
        else
        {
          v36 = lengths[0];
          lengths[0] = v35;
          nums[1] = v22;
          lengths[1] = v36;
          v22 = v21;
        }
        ++v21;
      }
      while ( v21 < 6 );
      v37 = v19 + edgeVerts[v22][0];
      v38 = v19 + dword_102FD0D8[2 * v22];
      nums[0] = v22;
      if ( v14 )
      {
        v39 = silIndex16[v37];
        v40 = silIndex16[v38];
      }
      else
      {
        v39 = silIndex32[v37];
        v40 = silIndex32[v38];
      }
      v41 = v40;
      v42 = silTraceVerts[v41].xyzw.x;
      v43 = &silTraceVerts[v41];
      v44 = v39;
      v45 = v42 + silTraceVerts[v44].xyzw.x;
      v46 = &silTraceVerts[v44];
      mid[0].x = v45 * 0.5;
      mid[0].y = (v43->xyzw.y + v46->xyzw.y) * 0.5;
      v47 = v43->xyzw.z + v46->xyzw.z;
      v48 = v19 + edgeVerts[nums[1]][0];
      v49 = v19 + dword_102FD0D8[2 * nums[1]];
      mid[0].z = v47 * 0.5;
      if ( v14 )
      {
        v50 = silIndex16[v48];
        v51 = silIndex16[v49];
      }
      else
      {
        v50 = silIndex32[v48];
        v51 = silIndex32[v49];
      }
      v52 = v51;
      v53 = silTraceVerts[v52].xyzw.x;
      v54 = &silTraceVerts[v52];
      v55 = v50;
      v56 = v53 + silTraceVerts[v55].xyzw.x;
      v57 = &silTraceVerts[v55];
      v58 = 0;
      mid[1].x = v56 * 0.5;
      mid[1].y = (v54->xyzw.y + v57->xyzw.y) * 0.5;
      mid[1].z = (v54->xyzw.z + v57->xyzw.z) * 0.5;
      v59 = mid[1].x - mid[0].x;
      v60 = mid[1].y - mid[0].y;
      v61 = mid[1].z - mid[0].z;
      while ( 1 )
      {
        la = lengths[v58] * 0.5;
        v62 = destIndices[v19 + edgeVerts[nums[v58]][0]];
        v63 = destIndices[v19 + dword_102FD0D8[2 * nums[v58]]];
        v64 = (unsigned __int8 *)diffuseColorSrc + diffuseColorStride * v62;
        v65 = &destDrawVerts[v62];
        v66 = &destDrawVerts[v63];
        v65->color[0] = *v64;
        v65->color[1] = v64[1];
        v65->color[2] = v64[2];
        v65->color[3] = v64[3];
        v67 = (float *)((char *)texCoordSrc + texCoordStride * v62);
        v65->st.x = *v67;
        v65->st.y = v67[1];
        v68 = (unsigned __int8 *)diffuseColorSrc + diffuseColorStride * v63;
        v66->color[0] = *v68;
        v66->color[1] = v68[1];
        v66->color[2] = v68[2];
        v66->color[3] = v68[3];
        v69 = (float *)((char *)texCoordSrc + texCoordStride * v63);
        v66->st.x = *v69;
        v70 = mid[v58].x;
        v66->st.y = v69[1];
        v71 = &mid[v58];
        v72 = v70 - localView->x;
        v73 = v71->y - localView->y;
        v74 = v71->z - localView->z;
        *(float *)&minor = v74 * v60 - v73 * v61;
        *(float *)&minor_4 = v61 * v72 - v74 * v59;
        *(float *)&minor_8 = v73 * v59 - v60 * v72;
        v75 = *(float *)&minor * *(float *)&minor
            + *(float *)&minor_8 * *(float *)&minor_8
            + *(float *)&minor_4 * *(float *)&minor_4;
        if ( v75 != 0.0 )
        {
          v76 = 1.0 / sqrt(v75);
          *(float *)&minor = *(float *)&minor * v76;
          *(float *)&minor_4 = *(float *)&minor_4 * v76;
          *(float *)&minor_8 = *(float *)&minor_8 * v76;
        }
        if ( v58 )
        {
          v108 = minor;
          v109 = minor_4;
          v110 = minor_8;
          v102 = *(float *)&minor;
          v103 = *(float *)&minor_4;
          v120 = *(float *)&minor_4 * la;
          v121 = *(float *)&minor_8 * la;
          v77 = v71->x - *(float *)&minor * la;
          v78 = v71->y - v120;
          v127 = v71->z - v121;
          v65->xyz.z = v127;
          v65->xyz.x = v77;
          v65->xyz.y = v78;
          v104 = minor_8;
          v116 = v103 * la;
          v117 = *(float *)&minor_8 * la;
          v79 = v102 * la + v71->x;
          v80 = v116 + v71->y;
          v124 = v117 + v71->z;
          v66->xyz.z = v124;
        }
        else
        {
          v105 = minor;
          v106 = minor_4;
          v107 = minor_8;
          v111 = *(float *)&minor;
          v112 = *(float *)&minor_4;
          v113 = *(float *)&minor_8;
          v122 = *(float *)&minor_4 * la;
          v123 = *(float *)&minor_8 * la;
          v126 = v123 + mid[0].z;
          v81 = *(float *)&minor * la + mid[0].x;
          v82 = v122 + mid[0].y;
          v65->xyz.z = v126;
          v65->xyz.x = v81;
          v65->xyz.y = v82;
          v118 = v112 * la;
          v119 = v113 * la;
          v79 = mid[0].x - v111 * la;
          v80 = mid[0].y - v118;
          v125 = mid[0].z - v119;
          v66->xyz.z = v125;
        }
        ++v58;
        v66->xyz.x = v79;
        v66->xyz.y = v80;
        if ( v58 >= 2 )
          break;
        v19 = i;
      }
      v20 = i + 4 < v101->m_drawGeoSpec.m_vertexCount;
      i += 4;
      if ( !v20 )
        break;
      v19 = i;
      v14 = silTraceIs16Bit;
    }
  }
  rvVertexBuffer::Unlock(drawVertexBuffer);
  rvIndexBuffer::Unlock(drawIndexBuffer);
  rvIndexBuffer::Unlock(silTraceIndexBuffer);
}

// FUNC: public: __thiscall rvPrimBatch::~rvPrimBatch(void)
// attributes: thunk
void __thiscall rvPrimBatch::~rvPrimBatch(rvPrimBatch *this)
{
  rvPrimBatch::Shutdown(this);
}

// FUNC: public: void __thiscall rvPrimBatch::Init(int *,int)
void __thiscall rvPrimBatch::Init(rvPrimBatch *this, int *transformPalette, int numTransforms)
{
  int *v4; // eax
  int i; // eax

  if ( this->m_numTransforms )
    rvPrimBatch::Shutdown(this);
  if ( numTransforms > 25 )
  {
    idLib::common->FatalError(idLib::common, "Primitive batch initialization failed - too many transforms per batch");
    return;
  }
  if ( transformPalette )
  {
    v4 = (int *)Memory::Allocate(4 * numTransforms);
    this->m_transformPalette = v4;
    if ( !v4 )
    {
      idLib::common->FatalError(idLib::common, "Out of memory");
      return;
    }
    for ( i = 0; i < numTransforms; ++i )
      this->m_transformPalette[i] = transformPalette[i];
  }
  this->m_numTransforms = numTransforms;
}

// FUNC: public: void __thiscall rvPrimBatch::Init(class Lexer &)
void __thiscall rvPrimBatch::Init(rvPrimBatch *this, Lexer *lex)
{
  bool v3; // zf
  int m_numTransforms; // eax
  unsigned int v5; // ebp
  int *v6; // eax
  int *v7; // eax
  int i; // ebp
  int m_vertexCount; // eax
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v11; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v3 = this->m_numTransforms == 0;
  v11 = 0;
  if ( !v3 )
    rvPrimBatch::Shutdown(this);
  Lexer::ExpectTokenString(lex, "{");
  Lexer::ReadToken(lex, &token);
  if ( idStr::Icmp(token.data, "Transform") )
  {
    this->m_numTransforms = 1;
  }
  else
  {
    Lexer::ExpectTokenString(lex, "[");
    this->m_numTransforms = Lexer::ParseInt(lex);
    Lexer::ExpectTokenString(lex, "]");
    Lexer::ExpectTokenString(lex, "{");
    m_numTransforms = this->m_numTransforms;
    if ( m_numTransforms > 25 )
    {
      Lexer::Error(lex, "Primitive batch initialization failed - too many transforms per batch");
      goto LABEL_31;
    }
    if ( m_numTransforms == 1 )
    {
      v5 = Lexer::ParseInt(lex);
      if ( v5 )
      {
        v6 = (int *)Memory::Allocate(4u);
        this->m_transformPalette = v6;
        if ( !v6 )
        {
          Lexer::Error(lex, "Out of memory error");
          goto LABEL_31;
        }
        *v6 = v5;
      }
    }
    else
    {
      v7 = (int *)Memory::Allocate(4 * m_numTransforms);
      this->m_transformPalette = v7;
      if ( !v7 )
      {
        Lexer::Error(lex, "Out of memory");
        goto LABEL_31;
      }
      for ( i = 0; i < this->m_numTransforms; ++i )
        this->m_transformPalette[i] = Lexer::ParseInt(lex);
    }
    Lexer::ExpectTokenString(lex, "}");
    Lexer::ReadToken(lex, &token);
  }
  if ( !idStr::Icmp(token.data, "SilTraceIndexedTriList") )
  {
    this->m_silTraceGeoSpec.m_vertexStart = Lexer::ParseInt(lex);
    this->m_silTraceGeoSpec.m_vertexCount = Lexer::ParseInt(lex);
    this->m_silTraceGeoSpec.m_indexStart = Lexer::ParseInt(lex);
    this->m_silTraceGeoSpec.m_primitiveCount = Lexer::ParseInt(lex);
    Lexer::ReadToken(lex, &token);
  }
  if ( !idStr::Icmp(token.data, "DrawIndexedTriList") )
  {
    this->m_drawGeoSpec.m_vertexStart = Lexer::ParseInt(lex);
    this->m_drawGeoSpec.m_vertexCount = Lexer::ParseInt(lex);
    this->m_drawGeoSpec.m_indexStart = Lexer::ParseInt(lex);
    this->m_drawGeoSpec.m_primitiveCount = Lexer::ParseInt(lex);
    Lexer::ReadToken(lex, &token);
  }
  if ( idStr::Icmp(token.data, "ShadowVerts") )
  {
    if ( !idStr::Icmp(token.data, "ShadowIndexedTriList") )
    {
      this->m_shadowVolGeoSpec.m_vertexStart = Lexer::ParseInt(lex);
      this->m_shadowVolGeoSpec.m_vertexCount = Lexer::ParseInt(lex);
      this->m_shadowVolGeoSpec.m_indexStart = Lexer::ParseInt(lex);
      this->m_shadowVolGeoSpec.m_primitiveCount = Lexer::ParseInt(lex);
      this->m_numShadowPrimitivesNoCaps = Lexer::ParseInt(lex);
      this->m_shadowCapPlaneBits = Lexer::ParseInt(lex);
      Lexer::ReadToken(lex, &token);
    }
  }
  else
  {
    this->m_shadowVolGeoSpec.m_vertexStart = Lexer::ParseInt(lex);
    m_vertexCount = this->m_silTraceGeoSpec.m_vertexCount;
    this->m_shadowVolGeoSpec.m_vertexCount = 2 * m_vertexCount;
    if ( !m_vertexCount )
      Lexer::Error(lex, "Primitive batch initialization failed - expected SilTraceIndexedTriList statement");
    Lexer::ReadToken(lex, &token);
  }
  if ( !idStr::Icmp(token.data, "SilhouetteEdge") )
  {
    this->m_silEdgeStart = Lexer::ParseInt(lex);
    this->m_silEdgeCount = Lexer::ParseInt(lex);
    Lexer::ReadToken(lex, &token);
  }
  if ( idStr::Icmp(token.data, "}") )
    Lexer::Error(lex, "Expected }.");
LABEL_31:
  v11 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: bool __thiscall rvPrimBatch::PreciseCullSurface(class idBounds &,class rvSilTraceVertT const *,class idVec3 const &,float const *,class rvIndexBuffer &)
char __thiscall rvPrimBatch::PreciseCullSurface(
        rvPrimBatch *this,
        idBounds *ndcBounds,
        const rvSilTraceVertT *silTraceVerts,
        const idVec3 *localView,
        const float *modelMatrix,
        rvIndexBuffer *silTraceIB)
{
  int v6; // esi
  bool v7; // zf
  unsigned __int16 *v8; // ecx
  const idVec3 *v10; // esi
  const idVec3 *v11; // edi
  const idVec3 *v12; // ebp
  double v13; // st7
  double v14; // st6
  double v15; // st5
  double v16; // st4
  int j; // esi
  double v18; // st7
  double v19; // st6
  double v20; // st5
  int v21; // edi
  int v22; // esi
  const idVec3 *v23; // esi
  const idVec3 *v24; // edi
  const idVec3 *v25; // ebp
  double v26; // st7
  double v27; // st6
  double v28; // st5
  double v29; // st4
  int v30; // edi
  int i; // esi
  double v32; // st7
  double v33; // st6
  double v34; // st5
  int v35; // esi
  idVec3 screen; // [esp+10h] [ebp-554h] BYREF
  unsigned int *index32; // [esp+1Ch] [ebp-548h]
  float v38; // [esp+20h] [ebp-544h]
  float v39; // [esp+24h] [ebp-540h]
  unsigned int *endIndex32; // [esp+28h] [ebp-53Ch]
  float v41; // [esp+2Ch] [ebp-538h]
  unsigned __int16 *endIndex16; // [esp+30h] [ebp-534h]
  void *indexMemPtr; // [esp+34h] [ebp-530h] BYREF
  idPlane plane; // [esp+38h] [ebp-52Ch] BYREF
  idFixedWinding w; // [esp+48h] [ebp-51Ch] BYREF
  int v46; // [esp+560h] [ebp-4h]

  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v46 = 0;
  v6 = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  rvIndexBuffer::Lock(silTraceIB, this->m_silTraceGeoSpec.m_indexStart, v6, 1u, &indexMemPtr);
  v7 = (silTraceIB->m_flags & 4) == 0;
  v8 = (unsigned __int16 *)indexMemPtr;
  index32 = (unsigned int *)indexMemPtr;
  if ( v7 )
  {
    endIndex32 = (unsigned int *)((char *)indexMemPtr + 4 * v6);
    if ( indexMemPtr >= endIndex32 )
      goto LABEL_3;
    while ( 1 )
    {
      v23 = (const idVec3 *)&silTraceVerts[*(_DWORD *)v8];
      v24 = (const idVec3 *)&silTraceVerts[*((_DWORD *)v8 + 1)];
      v25 = (const idVec3 *)&silTraceVerts[*((_DWORD *)v8 + 2)];
      if ( !tr.guiRecursionLevel )
      {
        v26 = v24->z - v23->z;
        v27 = v24->y - v23->y;
        v28 = v24->x - v23->x;
        v38 = v25->z - v23->z;
        v39 = v25->y - v23->y;
        v29 = v25->x - v23->x;
        v41 = v29 * v27 - v39 * v28;
        *(float *)&endIndex16 = v38 * v28 - v29 * v26;
        if ( (v26 * v39 - v38 * v27) * (v23->x - localView->x)
           + (v23->y - localView->y) * *(float *)&endIndex16
           + (v23->z - localView->z) * v41 >= 0.0 )
          break;
      }
      if ( w.allocedSize >= 3 || w.ReAllocate(&w, 3, 1) )
        w.numPoints = 3;
      R_LocalPointToGlobal(modelMatrix, v23, (idVec3 *)w.p);
      R_LocalPointToGlobal(modelMatrix, v24, (idVec3 *)&w.p[1]);
      R_LocalPointToGlobal(modelMatrix, v25, (idVec3 *)&w.p[2]);
      v30 = 0;
      w.p[2].t = 0.0;
      w.p[2].s = 0.0;
      w.p[1].t = 0.0;
      w.p[1].s = 0.0;
      w.p->t = 0.0;
      w.p->s = 0.0;
      for ( i = 480; i < 544; i += 16 )
      {
        v32 = -*(float *)((char *)&tr.viewDef->renderView.width + i);
        v33 = -*(float *)((char *)&tr.viewDef->renderView.y + i);
        v34 = -*(float *)((char *)&tr.viewDef->renderView.x + i);
        plane.a = -*(float *)((char *)&tr.viewDef->renderView.viewID + i);
        plane.b = v34;
        plane.c = v33;
        plane.d = v32;
        if ( !idWinding::ClipInPlace(&w, &plane, 0.1, 0) )
          break;
      }
      if ( w.numPoints > 0 )
      {
        v35 = 0;
        do
        {
          R_GlobalToNormalizedDeviceCoordinates(
            tr.viewDef->worldSpace.modelViewMatrix,
            tr.viewDef->projectionMatrix,
            (const idVec3 *)&w.p[v35],
            &screen);
          if ( screen.x < (double)ndcBounds->b[0].x )
            ndcBounds->b[0].x = screen.x;
          if ( screen.x > (double)ndcBounds->b[1].x )
            ndcBounds->b[1].x = screen.x;
          if ( screen.y < (double)ndcBounds->b[0].y )
            ndcBounds->b[0].y = screen.y;
          if ( screen.y > (double)ndcBounds->b[1].y )
            ndcBounds->b[1].y = screen.y;
          if ( screen.z < (double)ndcBounds->b[0].z )
            ndcBounds->b[0].z = screen.z;
          if ( screen.z > (double)ndcBounds->b[1].z )
            ndcBounds->b[1].z = screen.z;
          ++v30;
          ++v35;
        }
        while ( v30 < w.numPoints );
      }
      index32 += 3;
      if ( index32 >= endIndex32 )
        goto LABEL_3;
      v8 = (unsigned __int16 *)index32;
    }
  }
  else
  {
    endIndex16 = (unsigned __int16 *)((char *)indexMemPtr + 2 * v6);
    if ( indexMemPtr >= endIndex16 )
    {
LABEL_3:
      rvIndexBuffer::Unlock(silTraceIB);
      v46 = -1;
      w.p = 0;
      w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
      Memory::Free(0);
      return 0;
    }
    while ( 1 )
    {
      v10 = (const idVec3 *)&silTraceVerts[*v8];
      v11 = (const idVec3 *)&silTraceVerts[v8[1]];
      v12 = (const idVec3 *)&silTraceVerts[v8[2]];
      if ( !tr.guiRecursionLevel )
      {
        v13 = v11->z - v10->z;
        v14 = v11->y - v10->y;
        v15 = v11->x - v10->x;
        v39 = v12->z - v10->z;
        v38 = v12->y - v10->y;
        v16 = v12->x - v10->x;
        v41 = v16 * v14 - v38 * v15;
        *(float *)&endIndex32 = v39 * v15 - v16 * v13;
        if ( (v13 * v38 - v39 * v14) * (v10->x - localView->x)
           + (v10->y - localView->y) * *(float *)&endIndex32
           + (v10->z - localView->z) * v41 >= 0.0 )
          break;
      }
      if ( w.allocedSize >= 3 || w.ReAllocate(&w, 3, 1) )
        w.numPoints = 3;
      R_LocalPointToGlobal(modelMatrix, v10, (idVec3 *)w.p);
      R_LocalPointToGlobal(modelMatrix, v11, (idVec3 *)&w.p[1]);
      R_LocalPointToGlobal(modelMatrix, v12, (idVec3 *)&w.p[2]);
      w.p[2].t = 0.0;
      w.p[2].s = 0.0;
      w.p[1].t = 0.0;
      w.p[1].s = 0.0;
      w.p->t = 0.0;
      w.p->s = 0.0;
      for ( j = 480; j < 544; j += 16 )
      {
        v18 = -*(float *)((char *)&tr.viewDef->renderView.width + j);
        v19 = -*(float *)((char *)&tr.viewDef->renderView.y + j);
        v20 = -*(float *)((char *)&tr.viewDef->renderView.x + j);
        plane.a = -*(float *)((char *)&tr.viewDef->renderView.viewID + j);
        plane.b = v20;
        plane.c = v19;
        plane.d = v18;
        if ( !idWinding::ClipInPlace(&w, &plane, 0.1, 0) )
          break;
      }
      v21 = 0;
      if ( w.numPoints > 0 )
      {
        v22 = 0;
        do
        {
          R_GlobalToNormalizedDeviceCoordinates(
            tr.viewDef->worldSpace.modelViewMatrix,
            tr.viewDef->projectionMatrix,
            (const idVec3 *)&w.p[v22],
            &screen);
          if ( screen.x < (double)ndcBounds->b[0].x )
            ndcBounds->b[0].x = screen.x;
          if ( screen.x > (double)ndcBounds->b[1].x )
            ndcBounds->b[1].x = screen.x;
          if ( screen.y < (double)ndcBounds->b[0].y )
            ndcBounds->b[0].y = screen.y;
          if ( screen.y > (double)ndcBounds->b[1].y )
            ndcBounds->b[1].y = screen.y;
          if ( screen.z < (double)ndcBounds->b[0].z )
            ndcBounds->b[0].z = screen.z;
          if ( screen.z > (double)ndcBounds->b[1].z )
            ndcBounds->b[1].z = screen.z;
          ++v21;
          ++v22;
        }
        while ( v21 < w.numPoints );
      }
      index32 = (unsigned int *)((char *)index32 + 6);
      if ( index32 >= (unsigned int *)endIndex16 )
        goto LABEL_3;
      v8 = (unsigned __int16 *)index32;
    }
  }
  v46 = -1;
  w.p = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
  return 1;
}

// FUNC: public: void __thiscall rvPrimBatch::FindDecalTriangles(class idRenderModelDecal &,struct decalProjectionInfo_s const &,class idPlane const *,class rvSilTraceVertT const *,class rvIndexBuffer &)
void __thiscall rvPrimBatch::FindDecalTriangles(
        rvPrimBatch *this,
        idRenderModelDecal *decalModel,
        const decalProjectionInfo_s *localInfo,
        const idPlane *facePlanes,
        const rvSilTraceVertT *silTraceVerts,
        rvIndexBuffer *rfSilTraceIB)
{
  int m_vertexCount; // esi
  int v7; // eax
  void *v8; // esp
  const rvSilTraceVertT *v9; // ebx
  idSIMDProcessor_vtbl *v10; // eax
  _BYTE *p_fw; // edi
  int v13; // eax
  unsigned __int16 *v14; // ecx
  int v15; // edx
  int v16; // eax
  int v17; // ecx
  unsigned __int8 v18; // cl
  bool v19; // zf
  int v20; // ecx
  float *p_x; // eax
  float *v22; // eax
  float *v23; // eax
  int *v24; // edi
  idVec5 *p; // edx
  const rvSilTraceVertT *v26; // eax
  idVec5 *v27; // edx
  double v28; // st7
  double v29; // st6
  double v30; // st5
  double v31; // st7
  double v32; // st6
  double v33; // rtt
  double v34; // st6
  int v35; // ebx
  int v36; // ecx
  float *p_c; // edi
  double v38; // st7
  double v39; // st6
  double v40; // st5
  int v41; // [esp-4h] [ebp-51Ch]
  idFixedWinding fw; // [esp+Ch] [ebp-50Ch] BYREF
  idPlane plane; // [esp+51Ch] [ebp+4h] BYREF
  idVec3 v44; // [esp+52Ch] [ebp+14h]
  void *indexMemPtr; // [esp+538h] [ebp+20h] BYREF
  idVec3 dir; // [esp+53Ch] [ebp+24h]
  int v47; // [esp+548h] [ebp+30h]
  int *v48; // [esp+54Ch] [ebp+34h]
  int v[3]; // [esp+550h] [ebp+38h] BYREF
  float scale; // [esp+55Ch] [ebp+44h]
  unsigned __int8 *cullBits; // [esp+560h] [ebp+48h]
  rvPrimBatch *v52; // [esp+564h] [ebp+4Ch]
  int numSilTraceIndices; // [esp+568h] [ebp+50h]
  int j; // [esp+56Ch] [ebp+54h]
  int v55; // [esp+578h] [ebp+60h]
  bool is16Bit_3; // [esp+58Bh] [ebp+73h]

  m_vertexCount = this->m_silTraceGeoSpec.m_vertexCount;
  numSilTraceIndices = 3 * this->m_silTraceGeoSpec.m_primitiveCount;
  v7 = m_vertexCount + 18;
  LOBYTE(v7) = (m_vertexCount + 18) & 0xFC;
  v52 = this;
  v8 = alloca(v7);
  v9 = silTraceVerts;
  v10 = SIMDProcessor->__vftable;
  v41 = m_vertexCount;
  p_fw = &fw;
  cullBits = (unsigned __int8 *)&fw;
  (*(void (__fastcall **)(idSIMDProcessor *, idFixedWinding *, idPlane *, const rvSilTraceVertT *, int))v10->gap128)(
    SIMDProcessor,
    &fw,
    localInfo->boundingPlanes,
    silTraceVerts,
    v41);
  rvIndexBuffer::Lock(rfSilTraceIB, v52->m_silTraceGeoSpec.m_indexStart, numSilTraceIndices, 1u, &indexMemPtr);
  is16Bit_3 = (rfSilTraceIB->m_flags & 4) != 0;
  v13 = numSilTraceIndices;
  if ( numSilTraceIndices > 0 )
  {
    numSilTraceIndices = (int)&facePlanes->b;
    v48 = (int *)((char *)indexMemPtr + 8);
    v14 = (unsigned __int16 *)((char *)indexMemPtr + 4);
    v47 = (int)indexMemPtr + 4;
    v52 = (rvPrimBatch *)((v13 - 1) / 3u + 1);
    do
    {
      if ( is16Bit_3 )
      {
        v15 = *(v14 - 2);
        v16 = *(v14 - 1);
        v17 = *v14;
      }
      else
      {
        v15 = *(v48 - 2);
        v16 = *(v48 - 1);
        v17 = *v48;
      }
      v[2] = v17;
      v18 = p_fw[v16] & p_fw[v17];
      v[0] = v15;
      v19 = (v18 & p_fw[v15]) == 0;
      v[1] = v16;
      if ( v19 )
      {
        v20 = 0;
        if ( !facePlanes
          || *(float *)(numSilTraceIndices + 4) * localInfo->boundingPlanes[4].c
           + localInfo->boundingPlanes[4].b * *(float *)numSilTraceIndices
           + *(float *)(numSilTraceIndices - 4) * localInfo->boundingPlanes[4].a >= -0.1 )
        {
          fw.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
          fw.p = fw.data;
          fw.allocedSize = 64;
          v19 = !localInfo->parallel;
          v55 = 0;
          fw.numPoints = 3;
          if ( v19 )
          {
            v24 = v;
            while ( 1 )
            {
              p = fw.p;
              v26 = &v9[*v24];
              fw.p[v20].x = v26->xyzw.x;
              p[v20].y = v26->xyzw.y;
              p[v20].z = v26->xyzw.z;
              v27 = &p[v20];
              v27->t = 0.0;
              v27->s = 0.0;
              v28 = fw.p[v20].z - localInfo->projectionOrigin.z;
              v29 = fw.p[v20].y - localInfo->projectionOrigin.y;
              v30 = fw.p[v20].x - localInfo->projectionOrigin.x;
              dir.x = v30;
              dir.y = v29;
              dir.z = v28;
              *(float *)&j = fw.p[v20].y * localInfo->boundingPlanes[5].b
                           + fw.p[v20].z * localInfo->boundingPlanes[5].c
                           + fw.p[v20].x * localInfo->boundingPlanes[5].a
                           + localInfo->boundingPlanes[5].d;
              v31 = v28 * localInfo->boundingPlanes[5].c
                  + v29 * localInfo->boundingPlanes[5].b
                  + v30 * localInfo->boundingPlanes[5].a;
              if ( v31 != 0.0 )
                scale = -(*(float *)&j / v31);
              v44 = dir;
              ++v20;
              ++v24;
              *(float *)&j = dir.z * scale + fw.p[v20 - 1].z;
              v32 = dir.y * scale + fw.p[v20 - 1].y;
              LODWORD(dir.z) = j;
              v33 = v32;
              v34 = dir.x * scale + fw.p[v20 - 1].x;
              dir.x = v34;
              dir.y = v33;
              fw.p[v20 - 1].s = v34 * localInfo->textureAxis[0].a
                              + v33 * localInfo->textureAxis[0].b
                              + *(float *)&j * localInfo->textureAxis[0].c
                              + localInfo->textureAxis[0].d;
              fw.p[v20 - 1].t = v34 * localInfo->textureAxis[1].a
                              + v33 * localInfo->textureAxis[1].b
                              + *(float *)&j * localInfo->textureAxis[1].c
                              + localInfo->textureAxis[1].d;
              if ( v20 >= 3 )
                break;
              v9 = silTraceVerts;
            }
            v15 = v[0];
            p_fw = cullBits;
          }
          else
          {
            p_x = &v9[v15].xyzw.x;
            fw.data[0].x = *p_x;
            fw.data[0].y = p_x[1];
            fw.data[0].z = p_x[2];
            v22 = &v9[v[1]].xyzw.x;
            fw.data[0].s = fw.data[0].z * localInfo->textureAxis[0].c
                         + fw.data[0].y * localInfo->textureAxis[0].b
                         + fw.data[0].x * localInfo->textureAxis[0].a
                         + localInfo->textureAxis[0].d;
            fw.data[0].t = fw.data[0].z * localInfo->textureAxis[1].c
                         + fw.data[0].y * localInfo->textureAxis[1].b
                         + fw.data[0].x * localInfo->textureAxis[1].a
                         + localInfo->textureAxis[1].d;
            fw.data[1].x = *v22;
            fw.data[1].y = v22[1];
            fw.data[1].z = v22[2];
            v23 = &v9[v[2]].xyzw.x;
            fw.data[1].s = fw.data[1].z * localInfo->textureAxis[0].c
                         + fw.data[1].y * localInfo->textureAxis[0].b
                         + fw.data[1].x * localInfo->textureAxis[0].a
                         + localInfo->textureAxis[0].d;
            fw.data[1].t = fw.data[1].z * localInfo->textureAxis[1].c
                         + fw.data[1].y * localInfo->textureAxis[1].b
                         + fw.data[1].x * localInfo->textureAxis[1].a
                         + localInfo->textureAxis[1].d;
            fw.data[2].x = *v23;
            fw.data[2].y = v23[1];
            fw.data[2].z = v23[2];
            fw.data[2].s = fw.data[2].z * localInfo->textureAxis[0].c
                         + fw.data[2].y * localInfo->textureAxis[0].b
                         + fw.data[2].x * localInfo->textureAxis[0].a
                         + localInfo->textureAxis[0].d;
            fw.data[2].t = fw.data[2].z * localInfo->textureAxis[1].c
                         + fw.data[2].y * localInfo->textureAxis[1].b
                         + fw.data[2].x * localInfo->textureAxis[1].a
                         + localInfo->textureAxis[1].d;
          }
          v35 = (unsigned __int8)p_fw[v[1]] | (unsigned __int8)p_fw[v15] | (unsigned __int8)p_fw[v[2]];
          v36 = 0;
          *(float *)&j = 0.0;
          p_c = &localInfo->boundingPlanes[0].c;
          do
          {
            if ( ((1 << v36) & v35) != 0 )
            {
              v38 = -p_c[1];
              v39 = -*p_c;
              v40 = -*(p_c - 1);
              plane.a = -*(p_c - 2);
              plane.b = v40;
              plane.c = v39;
              plane.d = v38;
              if ( !idWinding::ClipInPlace(&fw, &plane, 0.1, 0) )
                break;
              v36 = j;
            }
            ++v36;
            p_c += 4;
            j = v36;
          }
          while ( v36 < 6 );
          if ( fw.numPoints )
            idRenderModelDecal::AddDepthFadedWinding(
              decalModel,
              &fw,
              localInfo->material,
              localInfo->fadePlanes,
              localInfo->fadeDepth,
              localInfo->startTime);
          v55 = -1;
          fw.p = 0;
          fw.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
          Memory::Free(0);
          fw.p = 0;
          p_fw = cullBits;
          v9 = silTraceVerts;
        }
      }
      v48 += 3;
      numSilTraceIndices += 16;
      v14 = (unsigned __int16 *)(v47 + 6);
      v19 = v52 == (rvPrimBatch *)1;
      v52 = (rvPrimBatch *)((char *)v52 - 1);
      v47 += 6;
    }
    while ( !v19 );
  }
  rvIndexBuffer::Unlock(rfSilTraceIB);
}

// FUNC: public: void __thiscall rvPrimBatch::PlaneForSurface(class idPlane &,class rvSilTraceVertT const *,class rvIndexBuffer &)
void __thiscall rvPrimBatch::PlaneForSurface(
        rvPrimBatch *this,
        idPlane *destPlane,
        const rvSilTraceVertT *silTraceVerts,
        rvIndexBuffer *silTraceIndexBuffer)
{
  int v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // edx
  double x; // st7
  const rvSilTraceVertT *v9; // edx
  const rvSilTraceVertT *v10; // esi
  double v11; // st7
  const rvSilTraceVertT *v12; // eax
  double v13; // st6
  double v14; // st5
  double v15; // st4
  double v16; // st7
  long double v17; // st6
  long double v18; // st7
  long double v19; // st5
  unsigned __int8 v21; // c2
  unsigned __int8 v22; // c3
  float v23; // eax
  void *silTraceIndexMemPtr; // [esp+8h] [ebp-1Ch] BYREF
  float v25; // [esp+Ch] [ebp-18h]
  float v26; // [esp+10h] [ebp-14h]
  float v27; // [esp+18h] [ebp-Ch]
  float v28; // [esp+1Ch] [ebp-8h]

  rvIndexBuffer::Lock(silTraceIndexBuffer, this->m_silTraceGeoSpec.m_indexStart, 3, 1u, &silTraceIndexMemPtr);
  if ( (silTraceIndexBuffer->m_flags & 4) != 0 )
  {
    v4 = *(unsigned __int16 *)silTraceIndexMemPtr;
    v5 = *((unsigned __int16 *)silTraceIndexMemPtr + 1);
    v6 = *((unsigned __int16 *)silTraceIndexMemPtr + 2);
  }
  else
  {
    v4 = *(_DWORD *)silTraceIndexMemPtr;
    v5 = *((_DWORD *)silTraceIndexMemPtr + 1);
    v6 = *((_DWORD *)silTraceIndexMemPtr + 2);
  }
  v7 = v6;
  x = silTraceVerts[v7].xyzw.x;
  v9 = &silTraceVerts[v7];
  v10 = &silTraceVerts[v5];
  v11 = x - v10->xyzw.x;
  v12 = &silTraceVerts[v4];
  v13 = v9->xyzw.y - v10->xyzw.y;
  v14 = v9->xyzw.z - v10->xyzw.z;
  v27 = v12->xyzw.x - v10->xyzw.x;
  v28 = v12->xyzw.y - v10->xyzw.y;
  v15 = v12->xyzw.z - v10->xyzw.z;
  v25 = v28 * v14 - v15 * v13;
  v26 = v15 * v11 - v27 * v14;
  destPlane->b = v26;
  v16 = v27 * v13 - v28 * v11;
  destPlane->a = v25;
  destPlane->c = v16;
  v17 = v16 * v16 + v26 * v26 + v25 * v25;
  if ( v17 == 0.0 )
  {
    v18 = 0.0;
  }
  else
  {
    v19 = 1.0 / sqrt(v17);
    destPlane->a = v25 * v19;
    destPlane->b = v26 * v19;
    destPlane->c = v16 * v19;
    v18 = v19 * v17;
  }
  if ( v22 | v21 )
  {
    if ( destPlane->b == 0.0 )
    {
      if ( destPlane->c <= 0.0 )
      {
        if ( LODWORD(destPlane->c) != -1082130432 )
          destPlane->c = -1.0;
      }
      else if ( LODWORD(destPlane->c) != 1065353216 )
      {
        destPlane->c = 1.0;
      }
      goto LABEL_40;
    }
    if ( destPlane->c == 0.0 )
    {
      if ( destPlane->b <= 0.0 )
      {
        v23 = -1.0;
        if ( LODWORD(destPlane->b) == -1082130432 )
          goto LABEL_40;
      }
      else
      {
        v23 = 1.0;
        if ( LODWORD(destPlane->b) == 1065353216 )
          goto LABEL_40;
      }
      goto LABEL_39;
    }
  }
  else if ( destPlane->b == 0.0 && destPlane->c == 0.0 )
  {
    if ( destPlane->a <= 0.0 )
    {
      if ( LODWORD(destPlane->a) != -1082130432 )
        destPlane->a = -1.0;
    }
    else if ( LODWORD(destPlane->a) != 1065353216 )
    {
      destPlane->a = 1.0;
    }
    goto LABEL_40;
  }
  if ( COERCE_FLOAT(LODWORD(destPlane->a) & 0x7FFFFFFF) == 1.0 )
  {
    if ( destPlane->b == 0.0 && destPlane->c == 0.0 )
      goto LABEL_40;
    v23 = 0.0;
    destPlane->c = 0.0;
    goto LABEL_39;
  }
  if ( COERCE_FLOAT(LODWORD(destPlane->b) & 0x7FFFFFFF) != 1.0 )
  {
    if ( COERCE_FLOAT(LODWORD(destPlane->c) & 0x7FFFFFFF) != 1.0 || destPlane->a == 0.0 && destPlane->b == 0.0 )
      goto LABEL_40;
    v23 = 0.0;
    destPlane->a = 0.0;
LABEL_39:
    destPlane->b = v23;
    goto LABEL_40;
  }
  if ( destPlane->a != 0.0 || destPlane->c != 0.0 )
  {
    destPlane->c = 0.0;
    destPlane->a = 0.0;
  }
LABEL_40:
  if ( v18 != 0.0 )
    destPlane->d = -(v10->xyzw.y * destPlane->b + v10->xyzw.x * destPlane->a + destPlane->c * v10->xyzw.z);
  rvIndexBuffer::Unlock(silTraceIndexBuffer);
}

// FUNC: public: void __thiscall rvPrimBatch::GenerateCollisionPolys(class idCollisionModelManagerLocal &,class idCollisionModelLocal &,class idMaterial const &,class rvVertexBuffer &,class rvIndexBuffer &)
void __thiscall rvPrimBatch::GenerateCollisionPolys(
        rvPrimBatch *this,
        idCollisionModelManagerLocal *modelManager,
        idCollisionModelLocal *collisionModel,
        const idMaterial *material,
        rvVertexBuffer *drawVertexBuffer,
        rvIndexBuffer *drawIndexBuffer)
{
  int m_vertexStart; // ebx
  int v8; // edi
  unsigned __int16 *v9; // ebp
  int v10; // edi
  int v11; // esi
  int v12; // ecx
  int v13; // eax
  float *v14; // ecx
  float *v15; // eax
  int v16; // edi
  int v17; // esi
  idVec5 *v18; // edx
  float *v19; // eax
  float *v20; // esi
  idVec5 *v21; // eax
  float *v22; // eax
  float *v23; // edi
  idVec5 *v24; // edx
  int v25; // ecx
  int v26; // eax
  float *v27; // ecx
  float *v28; // eax
  int v29; // edi
  int v30; // esi
  int numPoints; // edx
  idVec5 *v32; // edx
  float *v33; // eax
  float *v34; // esi
  idVec5 *v35; // eax
  float *v36; // eax
  float *v37; // edi
  idVec5 *v38; // edx
  float vec5; // [esp+18h] [ebp-56Ch]
  float vec5a; // [esp+18h] [ebp-56Ch]
  float vec5b; // [esp+18h] [ebp-56Ch]
  float vec5c; // [esp+18h] [ebp-56Ch]
  float vec5d; // [esp+18h] [ebp-56Ch]
  float vec5e; // [esp+18h] [ebp-56Ch]
  float vec5_4; // [esp+1Ch] [ebp-568h]
  float vec5_4a; // [esp+1Ch] [ebp-568h]
  float vec5_4b; // [esp+1Ch] [ebp-568h]
  float vec5_4c; // [esp+1Ch] [ebp-568h]
  float vec5_4d; // [esp+1Ch] [ebp-568h]
  float vec5_4e; // [esp+1Ch] [ebp-568h]
  float vec5_8; // [esp+20h] [ebp-564h]
  float vec5_8a; // [esp+20h] [ebp-564h]
  float vec5_8b; // [esp+20h] [ebp-564h]
  float vec5_8c; // [esp+20h] [ebp-564h]
  float vec5_8d; // [esp+20h] [ebp-564h]
  float vec5_8e; // [esp+20h] [ebp-564h]
  float vec5_12; // [esp+24h] [ebp-560h]
  float vec5_12a; // [esp+24h] [ebp-560h]
  float vec5_12b; // [esp+24h] [ebp-560h]
  float vec5_12c; // [esp+24h] [ebp-560h]
  float vec5_12d; // [esp+24h] [ebp-560h]
  float vec5_12e; // [esp+24h] [ebp-560h]
  float vec5_16; // [esp+28h] [ebp-55Ch]
  float vec5_16a; // [esp+28h] [ebp-55Ch]
  float vec5_16b; // [esp+28h] [ebp-55Ch]
  float vec5_16c; // [esp+28h] [ebp-55Ch]
  float vec5_16d; // [esp+28h] [ebp-55Ch]
  float vec5_16e; // [esp+28h] [ebp-55Ch]
  int texCoordStride; // [esp+2Ch] [ebp-558h] BYREF
  float *texCoordSrc; // [esp+30h] [ebp-554h] BYREF
  int positionStride; // [esp+34h] [ebp-550h] BYREF
  float *positionSrc; // [esp+38h] [ebp-54Ch] BYREF
  idPlane plane; // [esp+3Ch] [ebp-548h] BYREF
  int base; // [esp+4Ch] [ebp-538h]
  idPlane v75; // [esp+50h] [ebp-534h]
  void *indexMemPtr; // [esp+60h] [ebp-524h] BYREF
  unsigned int *endIndex32; // [esp+64h] [ebp-520h]
  idFixedWinding w; // [esp+68h] [ebp-51Ch] BYREF
  int v79; // [esp+580h] [ebp-4h]

  m_vertexStart = this->m_drawGeoSpec.m_vertexStart;
  base = m_vertexStart;
  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v79 = 0;
  v8 = 3 * this->m_drawGeoSpec.m_primitiveCount;
  rvIndexBuffer::Lock(drawIndexBuffer, this->m_drawGeoSpec.m_indexStart, v8, 1u, &indexMemPtr);
  rvVertexBuffer::LockTextureCoordinate(
    drawVertexBuffer,
    0,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&texCoordSrc,
    &texCoordStride);
  rvVertexBuffer::LockPosition(
    drawVertexBuffer,
    this->m_drawGeoSpec.m_vertexStart,
    this->m_drawGeoSpec.m_vertexCount,
    1u,
    (unsigned __int8 **)&positionSrc,
    &positionStride);
  v9 = (unsigned __int16 *)indexMemPtr;
  if ( (drawIndexBuffer->m_flags & 4) == 0 )
  {
    endIndex32 = (unsigned int *)((char *)indexMemPtr + 4 * v8);
    if ( indexMemPtr >= endIndex32 )
      goto LABEL_28;
    while ( 1 )
    {
      v25 = *((_DWORD *)v9 + 2) - m_vertexStart;
      v26 = texCoordStride * v25;
      v27 = (float *)((char *)positionSrc + positionStride * v25);
      v28 = (float *)((char *)texCoordSrc + v26);
      v29 = *(_DWORD *)v9 - m_vertexStart;
      v30 = *((_DWORD *)v9 + 1) - m_vertexStart;
      numPoints = 0;
      w.numPoints = 0;
      vec5c = *v27;
      vec5_4c = v27[1];
      vec5_8c = v27[2];
      vec5_12c = *v28;
      vec5_16c = v28[1];
      if ( w.allocedSize >= 1 )
        goto LABEL_20;
      if ( w.ReAllocate(&w, 1, 1) )
        break;
LABEL_21:
      v33 = (float *)((char *)positionSrc + positionStride * v30);
      v34 = (float *)((char *)texCoordSrc + texCoordStride * v30);
      vec5_8d = v33[2];
      vec5d = *v33;
      vec5_4d = v33[1];
      vec5_12d = *v34;
      vec5_16d = v34[1];
      if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
      {
        v35 = &w.p[w.numPoints];
        v35->x = vec5d;
        v35->y = vec5_4d;
        v35->z = vec5_8d;
        v35->s = vec5_12d;
        v35->t = vec5_16d;
        ++w.numPoints;
      }
      v36 = (float *)((char *)positionSrc + positionStride * v29);
      v37 = (float *)((char *)texCoordSrc + texCoordStride * v29);
      vec5e = *v36;
      vec5_12e = *v37;
      vec5_4e = v36[1];
      vec5_8e = v36[2];
      vec5_16e = v37[1];
      if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
      {
        v38 = &w.p[w.numPoints];
        v38->x = vec5e;
        v38->y = vec5_4e;
        v38->z = vec5_8e;
        v38->s = vec5_12e;
        v38->t = vec5_16e;
        ++w.numPoints;
      }
      idWinding::GetPlane(&w, &plane);
      v75.a = -plane.a;
      v75.b = -plane.b;
      v75.c = -plane.c;
      v75.d = -plane.d;
      plane = v75;
      idCollisionModelManagerLocal::PolygonFromWinding(modelManager, collisionModel, &w, &plane, material, 1);
      v9 += 6;
      if ( v9 >= (unsigned __int16 *)endIndex32 )
        goto LABEL_28;
      m_vertexStart = base;
    }
    numPoints = w.numPoints;
LABEL_20:
    v32 = &w.p[numPoints];
    v32->x = vec5c;
    v32->y = vec5_4c;
    v32->z = vec5_8c;
    v32->s = vec5_12c;
    v32->t = vec5_16c;
    ++w.numPoints;
    goto LABEL_21;
  }
  base = (int)indexMemPtr + 2 * v8;
  if ( (unsigned int)indexMemPtr < base )
  {
    do
    {
      v10 = *v9;
      v11 = v9[1];
      v12 = v9[2] - m_vertexStart;
      v13 = texCoordStride * v12;
      v14 = (float *)((char *)positionSrc + positionStride * v12);
      v15 = (float *)((char *)texCoordSrc + v13);
      w.numPoints = 0;
      vec5 = *v14;
      vec5_4 = v14[1];
      v16 = v10 - m_vertexStart;
      v17 = v11 - m_vertexStart;
      vec5_8 = v14[2];
      vec5_12 = *v15;
      vec5_16 = v15[1];
      if ( w.allocedSize >= 1 || w.ReAllocate(&w, 1, 1) )
      {
        v18 = &w.p[w.numPoints];
        v18->x = vec5;
        v18->y = vec5_4;
        v18->z = vec5_8;
        v18->s = vec5_12;
        v18->t = vec5_16;
        ++w.numPoints;
      }
      v19 = (float *)((char *)positionSrc + positionStride * v17);
      v20 = (float *)((char *)texCoordSrc + texCoordStride * v17);
      vec5_8a = v19[2];
      vec5a = *v19;
      vec5_4a = v19[1];
      vec5_12a = *v20;
      vec5_16a = v20[1];
      if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
      {
        v21 = &w.p[w.numPoints];
        v21->x = vec5a;
        v21->y = vec5_4a;
        v21->z = vec5_8a;
        v21->s = vec5_12a;
        v21->t = vec5_16a;
        ++w.numPoints;
      }
      v22 = (float *)((char *)positionSrc + positionStride * v16);
      v23 = (float *)((char *)texCoordSrc + texCoordStride * v16);
      vec5b = *v22;
      vec5_12b = *v23;
      vec5_4b = v22[1];
      vec5_8b = v22[2];
      vec5_16b = v23[1];
      if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
      {
        v24 = &w.p[w.numPoints];
        v24->x = vec5b;
        v24->y = vec5_4b;
        v24->z = vec5_8b;
        v24->s = vec5_12b;
        v24->t = vec5_16b;
        ++w.numPoints;
      }
      idWinding::GetPlane(&w, &plane);
      v75.a = -plane.a;
      v75.b = -plane.b;
      v75.c = -plane.c;
      v75.d = -plane.d;
      plane = v75;
      idCollisionModelManagerLocal::PolygonFromWinding(modelManager, collisionModel, &w, &plane, material, 1);
      v9 += 3;
    }
    while ( (unsigned int)v9 < base );
  }
LABEL_28:
  rvVertexBuffer::Unlock(drawVertexBuffer);
  rvIndexBuffer::Unlock(drawIndexBuffer);
  v79 = -1;
  w.p = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
}
