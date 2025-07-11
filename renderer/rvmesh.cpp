
// FUNC: public: int __thiscall rvMesh::FlipOutsideBackFaces(struct srfCullInfo_s &)
srfCullInfo_s *__thiscall rvMesh::FlipOutsideBackFaces(rvMesh *this, srfCullInfo_s *cullInfo)
{
  unsigned __int8 *cullBits; // ebx
  unsigned __int8 *facing; // edi
  srfCullInfo_s *result; // eax
  int v6; // ebp
  rvPrimBatch *m_primBatches; // eax
  int primBatch; // [esp+Ch] [ebp-8h]
  rvIndexBuffer *silTraceIndexBuffer; // [esp+10h] [ebp-4h]
  srfCullInfo_s *cullInfoa; // [esp+18h] [ebp+4h]

  cullBits = cullInfo->cullBits;
  facing = cullInfo->facing;
  result = 0;
  cullInfoa = 0;
  silTraceIndexBuffer = &this->m_renderModel->m_indexBuffers[this->m_silTraceIndexBuffer];
  primBatch = 0;
  if ( this->m_numPrimBatches > 0 )
  {
    v6 = 0;
    do
    {
      cullInfoa = (srfCullInfo_s *)((char *)cullInfoa
                                  + rvPrimBatch::FlipOutsideBackFaces(
                                      &this->m_primBatches[v6],
                                      facing,
                                      cullBits,
                                      silTraceIndexBuffer));
      m_primBatches = this->m_primBatches;
      facing += m_primBatches[v6].m_silTraceGeoSpec.m_primitiveCount;
      cullBits += m_primBatches[v6++].m_silTraceGeoSpec.m_vertexCount;
      ++primBatch;
    }
    while ( primBatch < this->m_numPrimBatches );
    return cullInfoa;
  }
  return result;
}

// FUNC: public: void __thiscall rvMesh::CalcGeometryProfile(void)
void __thiscall rvMesh::CalcGeometryProfile(rvMesh *this)
{
  int v1; // esi
  bool v2; // cc
  int *p_m_primitiveCount; // eax

  v1 = 0;
  v2 = this->m_numPrimBatches <= 0;
  this->m_numSilTraceVertices = 0;
  this->m_numSilTraceIndices = 0;
  this->m_numSilTracePrimitives = 0;
  this->m_numSilEdges = 0;
  this->m_numDrawVertices = 0;
  this->m_numDrawIndices = 0;
  this->m_numDrawPrimitives = 0;
  this->m_numTransforms = 0;
  if ( !v2 )
  {
    p_m_primitiveCount = &this->m_primBatches->m_silTraceGeoSpec.m_primitiveCount;
    do
    {
      this->m_numSilTraceVertices += *(p_m_primitiveCount - 2);
      this->m_numSilTraceIndices += 3 * *p_m_primitiveCount;
      this->m_numSilTracePrimitives += *p_m_primitiveCount;
      this->m_numSilEdges += *(p_m_primitiveCount - 4);
      this->m_numDrawVertices += p_m_primitiveCount[2];
      this->m_numDrawIndices += 3 * p_m_primitiveCount[4];
      this->m_numDrawPrimitives += p_m_primitiveCount[4];
      this->m_numTransforms += *((_WORD *)p_m_primitiveCount - 12);
      ++v1;
      p_m_primitiveCount += 18;
    }
    while ( v1 < this->m_numPrimBatches );
  }
}

// FUNC: public: void __thiscall rvMesh::Draw(float const *,class rvVertexFormat const *)
void __thiscall rvMesh::Draw(
        rvMesh *this,
        const float *skinToModelTransforms,
        const rvVertexFormat *vertexComponentsNeeded)
{
  int m_drawVertexBuffer; // eax
  rvRenderModelMD5R *m_renderModel; // ecx
  int v6; // ebp
  rvPrimBatch *m_primBatches; // eax
  int v9; // edi
  rvIndexBuffer *indexBuffer; // [esp+8h] [ebp-8h]
  rvVertexBuffer *vertexBuffer; // [esp+Ch] [ebp-4h]

  m_drawVertexBuffer = this->m_drawVertexBuffer;
  m_renderModel = this->m_renderModel;
  vertexBuffer = &m_renderModel->m_vertexBuffers[m_drawVertexBuffer];
  v6 = 0;
  indexBuffer = &m_renderModel->m_indexBuffers[this->m_drawIndexBuffer];
  if ( this->m_numPrimBatches > 0 )
  {
    m_primBatches = this->m_primBatches;
    v9 = 0;
    do
    {
      rvPrimBatch::LoadMatrixPaletteIntoVPParams(&m_primBatches[v9], skinToModelTransforms);
      rvPrimBatch::Draw(&this->m_primBatches[v9], vertexBuffer, indexBuffer, vertexComponentsNeeded);
      m_primBatches = this->m_primBatches;
      ++v6;
      skinToModelTransforms += 16 * m_primBatches[v9++].m_numTransforms;
    }
    while ( v6 < this->m_numPrimBatches );
  }
  this->m_drawSetUp = 0;
}

// FUNC: public: void __thiscall rvMesh::Draw(float const *,int *,int,class rvVertexFormat const *)
void __thiscall rvMesh::Draw(
        rvMesh *this,
        const float *skinToModelTransforms,
        int *indices,
        int numIndices,
        const rvVertexFormat *vertexComponentsNeeded)
{
  int m_numPrimBatches; // eax
  int v7; // edi
  int *v8; // ebx
  rvPrimBatch *m_primBatches; // eax
  int v10; // ebp
  int v11; // edx

  m_numPrimBatches = this->m_numPrimBatches;
  v7 = 0;
  v8 = &indices[m_numPrimBatches];
  if ( m_numPrimBatches > 0 )
  {
    m_primBatches = this->m_primBatches;
    v10 = 0;
    do
    {
      rvPrimBatch::LoadMatrixPaletteIntoVPParams(&m_primBatches[v10], skinToModelTransforms);
      rvPrimBatch::Draw(
        &this->m_primBatches[v10],
        &this->m_renderModel->m_vertexBuffers[this->m_drawVertexBuffer],
        v8,
        indices[v7],
        vertexComponentsNeeded);
      m_primBatches = this->m_primBatches;
      skinToModelTransforms += 16 * m_primBatches[v10].m_numTransforms;
      v11 = indices[v7++];
      ++v10;
      v8 += v11;
    }
    while ( v7 < this->m_numPrimBatches );
  }
  this->m_drawSetUp = 0;
}

// FUNC: public: void __thiscall rvMesh::DrawShadowVolume(float const *,int *,bool,class rvVertexFormat const *)
void __thiscall rvMesh::DrawShadowVolume(
        rvMesh *this,
        const float *skinToModelTransforms,
        int *indices,
        bool drawCaps,
        const rvVertexFormat *vertexComponentsNeeded)
{
  int m_shadowVolVertexBuffer; // eax
  rvRenderModelMD5R *m_renderModel; // ecx
  int v8; // edx
  int *v9; // eax
  int m_numPrimBatches; // ecx
  int v11; // ebp
  int *v12; // ebx
  int v13; // edi
  int v14; // ecx
  __int16 m_shadowVolIndexBuffer; // ax
  int v16; // ebx
  rvPrimBatch *m_primBatches; // eax
  const float *v18; // ebp
  int v19; // edi
  rvVertexBuffer *shadowVolVB; // [esp+10h] [ebp-8h]
  int *v21; // [esp+14h] [ebp-4h]
  rvIndexBuffer *indicesa; // [esp+20h] [ebp+8h]

  m_shadowVolVertexBuffer = this->m_shadowVolVertexBuffer;
  m_renderModel = this->m_renderModel;
  v8 = (int)&m_renderModel->m_vertexBuffers[m_shadowVolVertexBuffer];
  v9 = indices;
  shadowVolVB = (rvVertexBuffer *)v8;
  if ( !indices )
  {
    m_shadowVolIndexBuffer = this->m_shadowVolIndexBuffer;
    if ( m_shadowVolIndexBuffer < 0 )
      return;
    v16 = 0;
    indicesa = &m_renderModel->m_indexBuffers[m_shadowVolIndexBuffer];
    if ( this->m_numPrimBatches > 0 )
    {
      m_primBatches = this->m_primBatches;
      v18 = skinToModelTransforms;
      v19 = 0;
      do
      {
        rvPrimBatch::LoadMatrixPaletteIntoVPParams(&m_primBatches[v19], v18);
        rvPrimBatch::DrawShadowVolume(
          &this->m_primBatches[v19],
          shadowVolVB,
          indicesa,
          drawCaps,
          vertexComponentsNeeded);
        m_primBatches = this->m_primBatches;
        ++v16;
        v18 += 16 * m_primBatches[v19++].m_numTransforms;
      }
      while ( v16 < this->m_numPrimBatches );
    }
    goto LABEL_12;
  }
  m_numPrimBatches = this->m_numPrimBatches;
  v11 = 0;
  v12 = &indices[2 * m_numPrimBatches];
  if ( m_numPrimBatches <= 0 )
  {
LABEL_12:
    this->m_drawSetUp = 0;
    return;
  }
  v13 = 0;
  do
  {
    v21 = &v9[2 * v11 + drawCaps];
    if ( *v21 > 0 )
    {
      rvPrimBatch::LoadMatrixPaletteIntoVPParams(&this->m_primBatches[v13], skinToModelTransforms);
      rvPrimBatch::DrawShadowVolume(&this->m_primBatches[v13], shadowVolVB, v12, *v21, vertexComponentsNeeded);
      v9 = indices;
    }
    skinToModelTransforms += 16 * this->m_primBatches[v13].m_numTransforms;
    v14 = v9[2 * v11++ + 1];
    ++v13;
    v12 += v14;
  }
  while ( v11 < this->m_numPrimBatches );
  this->m_drawSetUp = 0;
}

// FUNC: public: void __thiscall rvMesh::DeriveTriPlanes(class idPlane *,class rvSilTraceVertT const *)
void __thiscall rvMesh::DeriveTriPlanes(rvMesh *this, idPlane *planes, const rvSilTraceVertT *silTraceVerts)
{
  int v4; // ebx
  int v6; // edi
  rvPrimBatch *m_primBatches; // eax
  rvIndexBuffer *silTraceIB; // [esp+8h] [ebp-4h]

  v4 = 0;
  silTraceIB = &this->m_renderModel->m_indexBuffers[this->m_silTraceIndexBuffer];
  if ( this->m_numPrimBatches > 0 )
  {
    v6 = 0;
    do
    {
      rvPrimBatch::DeriveTriPlanes(&this->m_primBatches[v6], planes, silTraceVerts, silTraceIB);
      m_primBatches = this->m_primBatches;
      silTraceVerts += m_primBatches[v6].m_silTraceGeoSpec.m_vertexCount;
      ++v4;
      planes += m_primBatches[v6++].m_silTraceGeoSpec.m_primitiveCount;
    }
    while ( v4 < this->m_numPrimBatches );
  }
}

// FUNC: public: bool __thiscall rvMesh::PreciseCullSurface(class idBounds &,class rvSilTraceVertT const *,class idVec3 const &,float const *)
char __thiscall rvMesh::PreciseCullSurface(
        rvMesh *this,
        idBounds *ndcBounds,
        const rvSilTraceVertT *silTraceVerts,
        const idVec3 *localView,
        const float *modelMatrix)
{
  int v6; // ebp
  int i; // edi
  rvIndexBuffer *silTraceIB; // [esp+10h] [ebp-4h]

  v6 = 0;
  silTraceIB = &this->m_renderModel->m_indexBuffers[this->m_silTraceIndexBuffer];
  if ( this->m_numPrimBatches <= 0 )
    return 0;
  for ( i = 0;
        !rvPrimBatch::PreciseCullSurface(
           &this->m_primBatches[i],
           ndcBounds,
           silTraceVerts,
           localView,
           modelMatrix,
           silTraceIB);
        ++i )
  {
    ++v6;
    silTraceVerts += this->m_primBatches[i].m_silTraceGeoSpec.m_vertexCount;
    if ( v6 >= this->m_numPrimBatches )
      return 0;
  }
  return 1;
}

// FUNC: public: int __thiscall rvMesh::CreateSilShadowVolTris(int,int *,unsigned char const *)
int __thiscall rvMesh::CreateSilShadowVolTris(
        rvMesh *this,
        int primBatch,
        int *shadowIndices,
        const unsigned __int8 *facing)
{
  return rvPrimBatch::CreateSilShadowVolTris(
           &this->m_primBatches[primBatch],
           shadowIndices,
           facing,
           this->m_renderModel->m_silEdges);
}

// FUNC: public: int __thiscall rvMesh::CreateFrontBackShadowVolTris(int,int *,unsigned char const *)
int __thiscall rvMesh::CreateFrontBackShadowVolTris(
        rvMesh *this,
        int primBatch,
        int *shadowIndices,
        const unsigned __int8 *facing)
{
  return rvPrimBatch::CreateFrontBackShadowVolTris(
           &this->m_primBatches[primBatch],
           shadowIndices,
           facing,
           &this->m_renderModel->m_indexBuffers[this->m_silTraceIndexBuffer]);
}

// FUNC: public: class rvVertexFormat const * __thiscall rvMesh::GetDrawVertexBufferFormat(void)const
rvVertexBuffer *__thiscall rvMesh::GetDrawVertexBufferFormat(rvMesh *this)
{
  __int16 m_drawVertexBuffer; // ax

  m_drawVertexBuffer = this->m_drawVertexBuffer;
  if ( m_drawVertexBuffer >= 0 )
    return &this->m_renderModel->m_vertexBuffers[m_drawVertexBuffer];
  else
    return 0;
}

// FUNC: public: class rvVertexFormat const * __thiscall rvMesh::GetShadowVolVertexBufferFormat(void)const
rvVertexBuffer *__thiscall rvMesh::GetShadowVolVertexBufferFormat(rvMesh *this)
{
  __int16 m_shadowVolVertexBuffer; // ax

  m_shadowVolVertexBuffer = this->m_shadowVolVertexBuffer;
  if ( m_shadowVolVertexBuffer >= 0 )
    return &this->m_renderModel->m_vertexBuffers[m_shadowVolVertexBuffer];
  else
    return 0;
}

// FUNC: public: void __thiscall rvMesh::LocalTrace(struct localTrace_s &,int &,int &,int &,class idVec3 const &,class idVec3 const &,unsigned char const *,class idPlane const *,class rvSilTraceVertT const *,float,class idMaterial const *)
void __thiscall rvMesh::LocalTrace(
        rvMesh *this,
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
        idMaterial *shader)
{
  rvIndexBuffer *m_indexBuffers; // eax
  rvIndexBuffer *v14; // edx
  int v15; // edi
  const idPlane *v17; // ebp
  rvPrimBatch *v18; // ecx
  rvPrimBatch *m_primBatches; // edx
  int m_vertexCount; // eax
  int m_primitiveCount; // ecx
  int m_numPrimBatches; // edx
  int curBatch; // [esp+8h] [ebp-10h]
  int lastIntersectBatch; // [esp+Ch] [ebp-Ch]
  rvIndexBuffer *drawIB; // [esp+10h] [ebp-8h]
  rvIndexBuffer *silTraceIB; // [esp+14h] [ebp-4h]

  m_indexBuffers = this->m_renderModel->m_indexBuffers;
  silTraceIB = &m_indexBuffers[this->m_silTraceIndexBuffer];
  v14 = &m_indexBuffers[this->m_drawIndexBuffer];
  v15 = 0;
  *c_testPlanes = 0;
  drawIB = v14;
  *c_testEdges = 0;
  *c_intersect = 0;
  lastIntersectBatch = -1;
  curBatch = 0;
  if ( this->m_numPrimBatches > 0 )
  {
    v17 = facePlanes;
    do
    {
      v18 = &this->m_primBatches[v15];
      facePlanes = 0;
      rvPrimBatch::LocalTrace(
        v18,
        hit,
        c_testPlanes,
        c_testEdges,
        (int *)&facePlanes,
        start,
        end,
        cullBits,
        v17,
        silTraceVerts,
        radius,
        silTraceIB,
        drawIB);
      if ( facePlanes )
      {
        lastIntersectBatch = curBatch;
        *c_intersect += (int)facePlanes;
      }
      m_primBatches = this->m_primBatches;
      m_vertexCount = m_primBatches[v15].m_silTraceGeoSpec.m_vertexCount;
      m_primitiveCount = m_primBatches[v15].m_silTraceGeoSpec.m_primitiveCount;
      m_numPrimBatches = this->m_numPrimBatches;
      cullBits += m_vertexCount;
      silTraceVerts += m_vertexCount;
      v17 += m_primitiveCount;
      ++v15;
      ++curBatch;
    }
    while ( curBatch < m_numPrimBatches );
    if ( *c_intersect )
      hit->materialType = rvPrimBatch::GetMaterialType(
                            &this->m_primBatches[lastIntersectBatch],
                            shader,
                            hit,
                            &this->m_renderModel->m_vertexBuffers[this->m_drawVertexBuffer]);
  }
}

// FUNC: public: void __thiscall rvMesh::CreateOverlayTriangles(struct overlayVertex_t *,int &,int *,int &,class idPlane const *,class rvSilTraceVertT const *)
void __thiscall rvMesh::CreateOverlayTriangles(
        rvMesh *this,
        overlayVertex_t *overlayVerts,
        int *numVerts,
        int *overlayIndices,
        int *numIndices,
        const idPlane *planes,
        const rvSilTraceVertT *silTraceVerts)
{
  bool v7; // cc
  int v8; // esi
  int v9; // eax
  void *v10; // esp
  int v11; // eax
  void *v12; // esp
  rvMesh *v13; // ebx
  int v14; // edi
  idVec2 v15; // [esp+0h] [ebp-20h] BYREF
  rvIndexBuffer *silTraceIndexBuffer; // [esp+Ch] [ebp-14h]
  int primBatch; // [esp+10h] [ebp-10h]
  rvMesh *v18; // [esp+14h] [ebp-Ch]
  int v19; // [esp+18h] [ebp-8h]
  int vertexBase; // [esp+1Ch] [ebp-4h]

  silTraceIndexBuffer = &this->m_renderModel->m_indexBuffers[this->m_silTraceIndexBuffer];
  v7 = this->m_numPrimBatches <= 0;
  v18 = this;
  vertexBase = 0;
  primBatch = 0;
  if ( !v7 )
  {
    v19 = 0;
    while ( 1 )
    {
      v8 = *(int *)((char *)&this->m_primBatches->m_silTraceGeoSpec.m_vertexCount + v19);
      v9 = v8 + 18;
      LOBYTE(v9) = (v8 + 18) & 0xFC;
      v10 = alloca(v9);
      v11 = 8 * v8 + 18;
      LOBYTE(v11) = v11 & 0xFC;
      v12 = alloca(v11);
      (*(void (__fastcall **)(idSIMDProcessor *, idVec2 *, idVec2 *, const idPlane *, const rvSilTraceVertT *, int))SIMDProcessor->gap130)(
        SIMDProcessor,
        &v15,
        &v15,
        planes,
        silTraceVerts,
        v8);
      v13 = v18;
      v14 = v19;
      rvPrimBatch::FindOverlayTriangles(
        (rvPrimBatch *)((char *)v18->m_primBatches + v19),
        overlayVerts,
        numVerts,
        overlayIndices,
        numIndices,
        (const unsigned __int8 *)&v15,
        &v15,
        vertexBase,
        silTraceIndexBuffer);
      vertexBase += v8;
      silTraceVerts += v8;
      v7 = ++primBatch < v13->m_numPrimBatches;
      v19 = v14 + 72;
      if ( !v7 )
        break;
      this = v18;
    }
  }
}

// FUNC: public: void __thiscall rvMesh::CreateDecalTriangles(class idRenderModelDecal &,struct decalProjectionInfo_s const &,class idPlane const *,class rvSilTraceVertT const *)
void __thiscall rvMesh::CreateDecalTriangles(
        rvMesh *this,
        idRenderModelDecal *decalModel,
        const decalProjectionInfo_s *localInfo,
        const idPlane *facePlanes,
        const rvSilTraceVertT *silTraceVerts)
{
  int v6; // esi
  rvPrimBatch *m_primBatches; // eax
  int primBatch; // [esp+8h] [ebp-8h]
  rvIndexBuffer *silTraceIndexBuffer; // [esp+Ch] [ebp-4h]

  v6 = 0;
  silTraceIndexBuffer = &this->m_renderModel->m_indexBuffers[this->m_silTraceIndexBuffer];
  primBatch = 0;
  if ( this->m_numPrimBatches > 0 )
  {
    m_primBatches = this->m_primBatches;
    do
    {
      rvPrimBatch::FindDecalTriangles(
        &m_primBatches[v6],
        decalModel,
        localInfo,
        facePlanes,
        silTraceVerts,
        silTraceIndexBuffer);
      m_primBatches = this->m_primBatches;
      silTraceVerts += m_primBatches[v6].m_silTraceGeoSpec.m_vertexCount;
      if ( facePlanes )
        facePlanes += m_primBatches[v6].m_silTraceGeoSpec.m_primitiveCount;
      ++v6;
      ++primBatch;
    }
    while ( primBatch < this->m_numPrimBatches );
  }
}

// FUNC: public: void __thiscall rvMesh::GenerateCollisionPolys(class idCollisionModelManagerLocal &,class idCollisionModelLocal &)
void __thiscall rvMesh::GenerateCollisionPolys(
        rvMesh *this,
        idCollisionModelManagerLocal *modelManager,
        idCollisionModelLocal *collisionModel)
{
  rvRenderModelMD5R *m_renderModel; // ecx
  rvIndexBuffer *v5; // ebp
  int v6; // edi
  int v7; // ebx
  rvVertexBuffer *drawVertexBuffer; // [esp+Ch] [ebp-4h]

  m_renderModel = this->m_renderModel;
  v5 = &m_renderModel->m_indexBuffers[this->m_drawIndexBuffer];
  v6 = 0;
  drawVertexBuffer = &m_renderModel->m_vertexBuffers[this->m_drawVertexBuffer];
  if ( this->m_numPrimBatches > 0 )
  {
    v7 = 0;
    do
    {
      rvPrimBatch::GenerateCollisionPolys(
        &this->m_primBatches[v7],
        modelManager,
        collisionModel,
        this->m_material,
        drawVertexBuffer,
        v5);
      ++v6;
      ++v7;
    }
    while ( v6 < this->m_numPrimBatches );
  }
}

// FUNC: public: void __thiscall rvMesh::CopyTriangles(class idDrawVert *,int *,class rvSilTraceVertT const *)
void __thiscall rvMesh::CopyTriangles(
        rvMesh *this,
        idDrawVert *destDrawVerts,
        int *destIndices,
        const rvSilTraceVertT *silTraceVerts)
{
  rvRenderModelMD5R *m_renderModel; // ecx
  rvIndexBuffer *m_indexBuffers; // eax
  int v7; // ebp
  int v9; // ebx
  rvPrimBatch *m_primBatches; // ecx
  int m_vertexCount; // eax
  rvPrimBatch *v12; // ecx
  bool v13; // cc
  int primBatch; // [esp+8h] [ebp-10h]
  rvIndexBuffer *silTraceIndexBuffer; // [esp+Ch] [ebp-Ch]
  rvIndexBuffer *drawIndexBuffer; // [esp+10h] [ebp-8h]
  rvVertexBuffer *drawVertexBuffer; // [esp+14h] [ebp-4h]

  m_renderModel = this->m_renderModel;
  m_indexBuffers = m_renderModel->m_indexBuffers;
  drawIndexBuffer = &m_indexBuffers[this->m_drawIndexBuffer];
  silTraceIndexBuffer = &m_indexBuffers[this->m_silTraceIndexBuffer];
  v7 = 0;
  drawVertexBuffer = &m_renderModel->m_vertexBuffers[this->m_drawVertexBuffer];
  primBatch = 0;
  if ( this->m_numPrimBatches > 0 )
  {
    v9 = 0;
    do
    {
      rvPrimBatch::CopyTriangles(
        &this->m_primBatches[v9],
        destDrawVerts,
        destIndices,
        drawVertexBuffer,
        drawIndexBuffer,
        silTraceVerts,
        silTraceIndexBuffer,
        v7);
      m_primBatches = this->m_primBatches;
      m_vertexCount = m_primBatches[v9].m_drawGeoSpec.m_vertexCount;
      v12 = &m_primBatches[v9];
      v7 += m_vertexCount;
      destDrawVerts += m_vertexCount;
      silTraceVerts += v12->m_silTraceGeoSpec.m_vertexCount;
      ++v9;
      v13 = primBatch + 1 < this->m_numPrimBatches;
      destIndices += 3 * v12->m_drawGeoSpec.m_primitiveCount;
      ++primBatch;
    }
    while ( v13 );
  }
}

// FUNC: public: void __thiscall rvMesh::CopyTriangles(class idDrawVert *,int *,int)
void __thiscall rvMesh::CopyTriangles(rvMesh *this, idDrawVert *destDrawVerts, int *destIndices, int destBase)
{
  rvRenderModelMD5R *m_renderModel; // ecx
  int v6; // ebp
  int v8; // edi
  rvPrimBatch *v9; // ecx
  int m_vertexCount; // eax
  rvVertexBuffer *drawVertexBuffer; // [esp+8h] [ebp-8h]
  rvIndexBuffer *drawIndexBuffer; // [esp+Ch] [ebp-4h]

  m_renderModel = this->m_renderModel;
  drawIndexBuffer = &m_renderModel->m_indexBuffers[this->m_drawIndexBuffer];
  v6 = 0;
  drawVertexBuffer = &m_renderModel->m_vertexBuffers[this->m_drawVertexBuffer];
  if ( this->m_numPrimBatches > 0 )
  {
    v8 = 0;
    do
    {
      rvPrimBatch::CopyDrawVertices(&this->m_primBatches[v8], destDrawVerts, drawVertexBuffer);
      rvPrimBatch::CopyDrawIndices(&this->m_primBatches[v8], destIndices, drawIndexBuffer, destBase);
      v9 = &this->m_primBatches[v8];
      m_vertexCount = v9->m_drawGeoSpec.m_vertexCount;
      destBase += m_vertexCount;
      destDrawVerts += m_vertexCount;
      ++v6;
      ++v8;
      destIndices += 3 * v9->m_drawGeoSpec.m_primitiveCount;
    }
    while ( v6 < this->m_numPrimBatches );
  }
}

// FUNC: public: void __thiscall rvMesh::TransformTriangles(class idDrawVert *,int *,class idMat4 const &,int,unsigned char * const,int)
void __thiscall rvMesh::TransformTriangles(
        rvMesh *this,
        idDrawVert *destDrawVerts,
        int *destIndices,
        const idMat4 *transform,
        int colorShift,
        unsigned __int8 *colorAdd,
        int destBase)
{
  rvRenderModelMD5R *m_renderModel; // ecx
  int v9; // ebp
  int v11; // edi
  rvPrimBatch *v12; // ecx
  int m_vertexCount; // eax
  rvVertexBuffer *drawVertexBuffer; // [esp+8h] [ebp-8h]
  rvIndexBuffer *drawIndexBuffer; // [esp+Ch] [ebp-4h]

  m_renderModel = this->m_renderModel;
  drawIndexBuffer = &m_renderModel->m_indexBuffers[this->m_drawIndexBuffer];
  v9 = 0;
  drawVertexBuffer = &m_renderModel->m_vertexBuffers[this->m_drawVertexBuffer];
  if ( this->m_numPrimBatches > 0 )
  {
    v11 = 0;
    do
    {
      rvPrimBatch::TransformDrawVertices(
        &this->m_primBatches[v11],
        destDrawVerts,
        drawVertexBuffer,
        transform,
        colorShift,
        colorAdd);
      rvPrimBatch::CopyDrawIndices(&this->m_primBatches[v11], destIndices, drawIndexBuffer, destBase);
      v12 = &this->m_primBatches[v11];
      m_vertexCount = v12->m_drawGeoSpec.m_vertexCount;
      destBase += m_vertexCount;
      destDrawVerts += m_vertexCount;
      ++v9;
      ++v11;
      destIndices += 3 * v12->m_drawGeoSpec.m_primitiveCount;
    }
    while ( v9 < this->m_numPrimBatches );
  }
}

// FUNC: public: void __thiscall rvMesh::TubeDeform(class idDrawVert *,int *,class idVec3 const &,class rvSilTraceVertT const *)
void __thiscall rvMesh::TubeDeform(
        rvMesh *this,
        idDrawVert *destDrawVerts,
        int *destIndices,
        const idVec3 *localView,
        const rvSilTraceVertT *silTraceVerts)
{
  rvRenderModelMD5R *m_renderModel; // ecx
  rvIndexBuffer *m_indexBuffers; // eax
  int v8; // ebp
  int v10; // ebx
  rvPrimBatch *m_primBatches; // edx
  int m_vertexCount; // eax
  int v13; // edx
  rvIndexBuffer *silTraceIndexBuffer; // [esp+8h] [ebp-Ch]
  rvIndexBuffer *drawIndexBuffer; // [esp+Ch] [ebp-8h]
  rvVertexBuffer *drawVertexBuffer; // [esp+10h] [ebp-4h]

  m_renderModel = this->m_renderModel;
  m_indexBuffers = m_renderModel->m_indexBuffers;
  drawIndexBuffer = &m_indexBuffers[this->m_drawIndexBuffer];
  silTraceIndexBuffer = &m_indexBuffers[this->m_silTraceIndexBuffer];
  v8 = 0;
  drawVertexBuffer = &m_renderModel->m_vertexBuffers[this->m_drawVertexBuffer];
  if ( this->m_numPrimBatches > 0 )
  {
    v10 = 0;
    do
    {
      rvPrimBatch::TubeDeform(
        &this->m_primBatches[v10],
        destDrawVerts,
        destIndices,
        localView,
        drawVertexBuffer,
        drawIndexBuffer,
        silTraceVerts,
        silTraceIndexBuffer);
      m_primBatches = this->m_primBatches;
      destDrawVerts += m_primBatches[v10].m_drawGeoSpec.m_vertexCount;
      m_vertexCount = m_primBatches[v10].m_silTraceGeoSpec.m_vertexCount;
      v13 = 3 * m_primBatches[v10].m_drawGeoSpec.m_primitiveCount;
      silTraceVerts += m_vertexCount;
      ++v8;
      ++v10;
      destIndices += v13;
    }
    while ( v8 < this->m_numPrimBatches );
  }
}

// FUNC: public: void __thiscall rvMesh::PlaneForSurface(class idPlane &,class rvSilTraceVertT const *)
void __thiscall rvMesh::PlaneForSurface(rvMesh *this, idPlane *destPlane, const rvSilTraceVertT *silTraceVerts)
{
  rvPrimBatch::PlaneForSurface(
    this->m_primBatches,
    destPlane,
    silTraceVerts,
    &this->m_renderModel->m_indexBuffers[this->m_silTraceIndexBuffer]);
}

// FUNC: public: void __thiscall rvMesh::SetupForDrawRender(class rvVertexFormat const *)
void __thiscall rvMesh::SetupForDrawRender(rvMesh *this, const rvVertexFormat *vertexComponentsNeeded)
{
  rvRenderModelMD5R *m_renderModel; // edx
  rvVertexBuffer *v4; // ecx
  rvIndexBuffer *v5; // edi
  const rvVertexFormat *p_m_format; // eax

  m_renderModel = this->m_renderModel;
  v4 = &m_renderModel->m_vertexBuffers[this->m_drawVertexBuffer];
  v5 = &m_renderModel->m_indexBuffers[this->m_drawIndexBuffer];
  p_m_format = vertexComponentsNeeded;
  if ( !vertexComponentsNeeded )
    p_m_format = &v4->m_format;
  rvVertexBuffer::SetupForRender(v4, 0, p_m_format);
  if ( (v5->m_flags & 2) != 0 )
    qglBindBufferARB(0x8893u, v5->m_ibID);
  this->m_drawSetUp = 1;
}

// FUNC: public: void __thiscall rvMesh::SetupForShadowVolRender(class rvVertexFormat const *)
void __thiscall rvMesh::SetupForShadowVolRender(rvMesh *this, const rvVertexFormat *vertexComponentsNeeded)
{
  rvVertexBuffer *v3; // ecx
  const rvVertexFormat *p_m_format; // eax
  __int16 m_shadowVolIndexBuffer; // ax
  rvIndexBuffer *v6; // eax

  v3 = &this->m_renderModel->m_vertexBuffers[this->m_shadowVolVertexBuffer];
  p_m_format = vertexComponentsNeeded;
  if ( !vertexComponentsNeeded )
    p_m_format = &v3->m_format;
  rvVertexBuffer::SetupForRender(v3, 0, p_m_format);
  m_shadowVolIndexBuffer = this->m_shadowVolIndexBuffer;
  if ( m_shadowVolIndexBuffer != -1 )
  {
    v6 = &this->m_renderModel->m_indexBuffers[m_shadowVolIndexBuffer];
    if ( (v6->m_flags & 2) != 0 )
      qglBindBufferARB(0x8893u, v6->m_ibID);
  }
}

// FUNC: public: void __thiscall rvMesh::Init(class rvRenderModelMD5R &,struct modelSurface_s &,int *,int,int,int,int,int,int)
void __thiscall rvMesh::Init(
        rvMesh *this,
        silEdge_t *renderModel,
        modelSurface_s *srcSurface,
        int *silRemap,
        __int16 silTraceVB,
        __int16 drawVB,
        __int16 shadowVB,
        __int16 silTraceIB,
        __int16 drawIB,
        __int16 shadowIB)
{
  silEdge_t *v10; // ebx
  srfTriangles_s *geometry; // esi
  _DWORD *v13; // eax
  rvPrimBatch *v14; // eax
  rvRenderModelMD5R *m_renderModel; // ecx
  rvVertexBuffer *v17; // ebx
  int m_numIndicesWritten; // edx
  int v19; // eax
  void *v20; // esp
  rvPrimBatch *m_primBatches; // ecx
  int v22; // eax
  __int16 m_drawVertexBuffer; // ax
  rvRenderModelMD5R *v24; // edx
  __int16 m_drawIndexBuffer; // cx
  int v26; // ecx
  rvVertexBuffer *m_vertexBuffers; // eax
  unsigned int m_numVerticesWritten; // ebx
  rvPrimBatch *v29; // ecx
  int v30; // eax
  __int16 m_shadowVolVertexBuffer; // ax
  rvRenderModelMD5R *v32; // edx
  int v33; // ecx
  rvVertexBuffer *v34; // eax
  unsigned int v35; // ebx
  rvVertexBuffer *v36; // ecx
  rvPrimBatch *v37; // eax
  int m_vertexCount; // ecx
  int v39; // ecx
  int v40; // edx
  rvPrimBatch *v41; // eax
  int numSilEdges; // ecx
  unsigned int *v43; // edx
  silEdge_t *silEdges; // eax
  int *v45; // ecx
  int v46; // ecx
  rvPrimBatch *v47; // eax
  int numVerts; // [esp-Ch] [ebp-3Ch]
  const idDrawVert *verts; // [esp-4h] [ebp-34h]
  unsigned int v50[3]; // [esp+0h] [ebp-30h] BYREF
  silEdge_t newSilEdge; // [esp+Ch] [ebp-24h]
  void *ptr; // [esp+1Ch] [ebp-14h]
  unsigned int *silVertexMapOldToNew; // [esp+20h] [ebp-10h]
  int v54; // [esp+2Ch] [ebp-4h]
  silEdge_t *endSilEdge; // [esp+38h] [ebp+8h]
  int silTraceVertexStart; // [esp+3Ch] [ebp+Ch]
  int silTraceVertexStarta; // [esp+3Ch] [ebp+Ch]
  int silTraceVertexStartb; // [esp+3Ch] [ebp+Ch]
  int silTraceVertexStartc; // [esp+3Ch] [ebp+Ch]
  int shadowVolIndexStart; // [esp+40h] [ebp+10h]
  int silTraceIndexStart; // [esp+44h] [ebp+14h]
  int numBatchSilVerts; // [esp+48h] [ebp+18h]
  rvIndexBuffer *silEdgeStartb; // [esp+50h] [ebp+20h]
  int silEdgeStart; // [esp+50h] [ebp+20h]
  rvIndexBuffer *silEdgeStartc; // [esp+50h] [ebp+20h]
  rvIndexBuffer *silEdgeStartd; // [esp+50h] [ebp+20h]
  int silEdgeStarte; // [esp+50h] [ebp+20h]
  int silEdgeStarta; // [esp+50h] [ebp+20h]

  v10 = renderModel;
  this->m_renderModel = (rvRenderModelMD5R *)renderModel;
  this->m_material = srcSurface->shader;
  geometry = srcSurface->geometry;
  silVertexMapOldToNew = 0;
  this->m_numPrimBatches = 1;
  v13 = Memory::Allocate(0x4Cu);
  ptr = v13;
  v54 = 0;
  if ( v13 )
  {
    *v13 = 1;
    silTraceVertexStart = (int)(v13 + 1);
    `eh vector constructor iterator'(
      v13 + 1,
      0x48u,
      1,
      (void (__thiscall *)(void *))rvPrimBatch::rvPrimBatch,
      (void (__thiscall *)(void *))rvPrimBatch::~rvPrimBatch);
    v14 = (rvPrimBatch *)silTraceVertexStart;
  }
  else
  {
    v14 = 0;
  }
  v54 = -1;
  this->m_primBatches = v14;
  if ( !v14 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(common.type, "Out of memory");
  rvPrimBatch::Init(this->m_primBatches, 0, 1);
  this->m_silTraceIndexBuffer = silTraceIB;
  this->m_drawVertexBuffer = drawVB;
  this->m_silTraceVertexBuffer = silTraceVB;
  this->m_drawIndexBuffer = drawIB;
  this->m_shadowVolVertexBuffer = shadowVB;
  if ( !geometry->shadowVertexes )
    shadowIB = -1;
  this->m_shadowVolIndexBuffer = shadowIB;
  if ( geometry->numVerts && geometry->numIndexes )
  {
    if ( geometry->verts )
    {
      if ( silTraceVB >= 0 )
      {
        m_renderModel = this->m_renderModel;
        if ( silTraceVB < m_renderModel->m_numVertexBuffers
          && silTraceIB >= 0
          && silTraceIB < m_renderModel->m_numIndexBuffers )
        {
          v17 = &m_renderModel->m_vertexBuffers[silTraceVB];
          m_numIndicesWritten = m_renderModel->m_indexBuffers[silTraceIB].m_numIndicesWritten;
          silEdgeStartb = &m_renderModel->m_indexBuffers[silTraceIB];
          v19 = 4 * geometry->numVerts + 3;
          LOBYTE(v19) = v19 & 0xFC;
          silTraceVertexStarta = v17->m_numVerticesWritten;
          silTraceIndexStart = m_numIndicesWritten;
          v20 = alloca(v19);
          verts = geometry->verts;
          numVerts = geometry->numVerts;
          silVertexMapOldToNew = v50;
          numBatchSilVerts = rvVertexBuffer::CopySilTraceData(v17, v50, silTraceVertexStarta, numVerts, silRemap, verts);
          rvIndexBuffer::CopyRemappedData(
            silEdgeStartb,
            silTraceIndexStart,
            geometry->numIndexes,
            silVertexMapOldToNew,
            geometry->indexes,
            0);
          m_primBatches = this->m_primBatches;
          v22 = geometry->numIndexes / 3;
          m_primBatches->m_silTraceGeoSpec.m_vertexStart = silTraceVertexStarta;
          m_primBatches->m_silTraceGeoSpec.m_indexStart = silTraceIndexStart;
          v10 = renderModel;
          m_primBatches->m_silTraceGeoSpec.m_vertexCount = numBatchSilVerts;
          m_primBatches->m_silTraceGeoSpec.m_primitiveCount = v22;
        }
      }
      if ( geometry->verts )
      {
        m_drawVertexBuffer = this->m_drawVertexBuffer;
        if ( m_drawVertexBuffer >= 0 )
        {
          v24 = this->m_renderModel;
          if ( m_drawVertexBuffer < v24->m_numVertexBuffers )
          {
            m_drawIndexBuffer = this->m_drawIndexBuffer;
            if ( m_drawIndexBuffer >= 0 )
            {
              silEdgeStart = m_drawIndexBuffer;
              if ( m_drawIndexBuffer < v24->m_numIndexBuffers )
              {
                v26 = m_drawVertexBuffer;
                m_vertexBuffers = v24->m_vertexBuffers;
                m_numVerticesWritten = m_vertexBuffers[v26].m_numVerticesWritten;
                silEdgeStartc = &v24->m_indexBuffers[silEdgeStart];
                silTraceVertexStartb = silEdgeStartc->m_numIndicesWritten;
                rvVertexBuffer::CopyData(
                  &m_vertexBuffers[v26],
                  m_numVerticesWritten,
                  geometry->numVerts,
                  geometry->verts);
                rvIndexBuffer::CopyData(
                  silEdgeStartc,
                  silTraceVertexStartb,
                  geometry->numIndexes,
                  geometry->indexes,
                  m_numVerticesWritten);
                v29 = this->m_primBatches;
                v30 = geometry->numIndexes / 3;
                v29->m_drawGeoSpec.m_vertexCount = geometry->numVerts;
                v29->m_drawGeoSpec.m_vertexStart = m_numVerticesWritten;
                v10 = renderModel;
                v29->m_drawGeoSpec.m_indexStart = silTraceVertexStartb;
                v29->m_drawGeoSpec.m_primitiveCount = v30;
              }
            }
          }
        }
      }
    }
    m_shadowVolVertexBuffer = this->m_shadowVolVertexBuffer;
    if ( m_shadowVolVertexBuffer >= 0 )
    {
      v32 = this->m_renderModel;
      if ( m_shadowVolVertexBuffer < v32->m_numVertexBuffers )
      {
        v33 = m_shadowVolVertexBuffer;
        v34 = v32->m_vertexBuffers;
        v35 = v34[v33].m_numVerticesWritten;
        v36 = &v34[v33];
        if ( geometry->verts )
        {
          rvVertexBuffer::CopyRemappedShadowVolData(v36, v35, geometry->numVerts, silRemap, geometry->verts);
          v37 = this->m_primBatches;
          m_vertexCount = v37->m_silTraceGeoSpec.m_vertexCount;
          v37->m_shadowVolGeoSpec.m_vertexStart = v35;
          v37->m_shadowVolGeoSpec.m_vertexCount = 2 * m_vertexCount;
        }
        else
        {
          silEdgeStartd = &v32->m_indexBuffers[this->m_shadowVolIndexBuffer];
          shadowVolIndexStart = silEdgeStartd->m_numIndicesWritten;
          rvVertexBuffer::CopyShadowVolData(v36, v35, geometry->numVerts, geometry->shadowVertexes);
          rvIndexBuffer::CopyData(silEdgeStartd, shadowVolIndexStart, geometry->numIndexes, geometry->indexes, v35);
          silTraceVertexStartc = geometry->shadowCapPlaneBits;
          v39 = geometry->numShadowIndexesNoCaps / 3;
          v40 = geometry->numIndexes / 3;
          silEdgeStarte = geometry->numVerts;
          v41 = this->m_primBatches;
          v41->m_shadowVolGeoSpec.m_vertexStart = v35;
          v41->m_shadowVolGeoSpec.m_vertexCount = silEdgeStarte;
          v41->m_numShadowPrimitivesNoCaps = v39;
          v41->m_shadowVolGeoSpec.m_indexStart = shadowVolIndexStart;
          v41->m_shadowVolGeoSpec.m_primitiveCount = v40;
          v41->m_shadowCapPlaneBits = silTraceVertexStartc;
        }
        v10 = renderModel;
      }
    }
    if ( geometry->verts )
    {
      numSilEdges = geometry->numSilEdges;
      if ( numSilEdges )
      {
        v43 = silVertexMapOldToNew;
        if ( silVertexMapOldToNew )
        {
          silEdgeStarta = v10[10].p2;
          silEdges = geometry->silEdges;
          endSilEdge = &silEdges[numSilEdges];
          if ( silEdges < endSilEdge )
          {
            while ( 1 )
            {
              newSilEdge.p2 = silEdges->p2;
              newSilEdge.v1 = v43[silEdges->v1];
              v45 = (int *)(v10[9].v1 + 16 * v10[10].p2);
              newSilEdge.v2 = v43[silEdges->v2];
              *v45 = silEdges->p1;
              v45[1] = newSilEdge.p2;
              v45[2] = newSilEdge.v1;
              v45[3] = newSilEdge.v2;
              ++v10[10].p2;
              if ( ++silEdges >= endSilEdge )
                break;
              v43 = silVertexMapOldToNew;
            }
          }
          v46 = geometry->numSilEdges;
          v47 = this->m_primBatches;
          v47->m_silEdgeStart = silEdgeStarta;
          v47->m_silEdgeCount = v46;
        }
      }
    }
    rvMesh::CalcGeometryProfile(this);
    this->m_bounds.b[0].x = geometry->bounds.b[0].x;
    this->m_bounds.b[0].y = geometry->bounds.b[0].y;
    this->m_bounds.b[0].z = geometry->bounds.b[0].z;
    this->m_bounds.b[1].x = geometry->bounds.b[1].x;
    this->m_bounds.b[1].y = geometry->bounds.b[1].y;
    this->m_bounds.b[1].z = geometry->bounds.b[1].z;
  }
}

// FUNC: protected: void __thiscall rvMesh::ResetValues(void)
void __thiscall rvMesh::ResetValues(rvMesh *this)
{
  this->m_bounds.b[0].z = idMath::INFINITY;
  this->m_bounds.b[0].y = idMath::INFINITY;
  this->m_bounds.b[0].x = idMath::INFINITY;
  this->m_bounds.b[1].z = -1.0e30;
  this->m_bounds.b[1].y = -1.0e30;
  this->m_bounds.b[1].x = -1.0e30;
  this->m_renderModel = 0;
  this->m_material = 0;
  this->m_nextInLOD = 0;
  this->m_primBatches = 0;
  this->m_numPrimBatches = 0;
  this->m_levelOfDetail = -1;
  this->m_surfaceNum = -1;
  this->m_meshIdentifier = 0;
  this->m_silTraceVertexBuffer = -1;
  this->m_silTraceIndexBuffer = -1;
  this->m_drawVertexBuffer = -1;
  this->m_drawIndexBuffer = -1;
  this->m_shadowVolVertexBuffer = -1;
  this->m_shadowVolIndexBuffer = -1;
  this->m_numSilTraceVertices = 0;
  this->m_numSilTraceIndices = 0;
  this->m_numSilTracePrimitives = 0;
  this->m_numSilEdges = 0;
  this->m_numDrawVertices = 0;
  this->m_numDrawIndices = 0;
  this->m_numDrawPrimitives = 0;
  this->m_numTransforms = 0;
  this->m_drawSetUp = 0;
}

// FUNC: protected: void __thiscall rvMesh::UpdateSurface(struct modelSurface_s &,struct renderEntity_s const &,class idJointMat *)
void __thiscall rvMesh::UpdateSurface(
        rvMesh *this,
        modelSurface_s *surface,
        const renderEntity_s *entity,
        idJointMat *skinSpaceToLocalMats)
{
  srfTriangles_s *geometry; // eax
  srfTriangles_s *v6; // esi
  bool v7; // zf
  int m_silTraceVertexBuffer; // edx
  rvVertexBuffer *m_vertexBuffers; // ecx
  int v10; // ebp
  int v11; // ebx
  rvPrimBatch *m_primBatches; // edx
  int primBatch; // [esp+10h] [ebp-20h]
  rvVertexBuffer *silTraceVB; // [esp+14h] [ebp-1Ch]
  idVec3 min; // [esp+18h] [ebp-18h] BYREF
  idVec3 max; // [esp+24h] [ebp-Ch] BYREF
  modelSurface_s *surfacea; // [esp+34h] [ebp+4h]

  surface->shader = this->m_material;
  ++tr.pc.c_deformedSurfaces;
  tr.pc.c_deformedVerts += this->m_numSilTraceVertices;
  tr.pc.c_deformedIndexes += this->m_numSilTraceIndices;
  geometry = surface->geometry;
  if ( !geometry )
    goto LABEL_7;
  if ( !geometry->verts
    && (!geometry->silTraceVerts
     || geometry->numVerts != this->m_numSilTraceVertices
     || geometry->numIndexes != this->m_numSilTraceIndices) )
  {
    R_FreeStaticTriSurf(surface->geometry);
LABEL_7:
    surface->geometry = R_AllocStaticTriSurf();
    goto LABEL_8;
  }
  R_FreeStaticTriSurfVertexCaches(surface->geometry);
LABEL_8:
  v6 = surface->geometry;
  v6->deformedSurface = 1;
  v6->tangentsCalculated = 1;
  v6->facePlanesCalculated = 0;
  v6->numVerts = this->m_numSilTraceVertices;
  v6->numIndexes = this->m_numSilTraceIndices;
  v6->primBatchMesh = this;
  v6->numSilEdges = this->m_numSilEdges;
  v7 = v6->silTraceVerts == 0;
  v6->silEdges = &this->m_renderModel->m_silEdges[this->m_primBatches->m_silEdgeStart];
  if ( v7 )
    R_AllocStaticTriSurfSilTraceVerts(v6, this->m_numSilTraceVertices);
  R_AllocStaticSkinToModelTransforms(v6, this->m_numTransforms);
  m_silTraceVertexBuffer = this->m_silTraceVertexBuffer;
  m_vertexBuffers = this->m_renderModel->m_vertexBuffers;
  v6->bounds.b[0].z = idMath::INFINITY;
  v6->bounds.b[0].y = idMath::INFINITY;
  silTraceVB = &m_vertexBuffers[m_silTraceVertexBuffer];
  v6->bounds.b[0].x = idMath::INFINITY;
  v10 = 0;
  v6->bounds.b[1].z = -1.0e30;
  v11 = 0;
  v6->bounds.b[1].y = -1.0e30;
  primBatch = 0;
  v6->bounds.b[1].x = -1.0e30;
  if ( this->m_numPrimBatches > 0 )
  {
    surfacea = 0;
    do
    {
      rvPrimBatch::TransformVertsMinMax(
        (rvPrimBatch *)((char *)surfacea + (unsigned int)this->m_primBatches),
        &v6->silTraceVerts[v10],
        &min,
        &max,
        silTraceVB,
        skinSpaceToLocalMats,
        entity->joints,
        &v6->skinToModelTransforms[16 * v11]);
      if ( min.x < (double)v6->bounds.b[0].x )
        v6->bounds.b[0].x = min.x;
      if ( min.x > (double)v6->bounds.b[1].x )
        v6->bounds.b[1].x = min.x;
      if ( min.y < (double)v6->bounds.b[0].y )
        v6->bounds.b[0].y = min.y;
      if ( min.y > (double)v6->bounds.b[1].y )
        v6->bounds.b[1].y = min.y;
      if ( min.z < (double)v6->bounds.b[0].z )
        v6->bounds.b[0].z = min.z;
      if ( min.z > (double)v6->bounds.b[1].z )
        v6->bounds.b[1].z = min.z;
      if ( max.x < (double)v6->bounds.b[0].x )
        v6->bounds.b[0].x = max.x;
      if ( max.x > (double)v6->bounds.b[1].x )
        v6->bounds.b[1].x = max.x;
      if ( max.y < (double)v6->bounds.b[0].y )
        v6->bounds.b[0].y = max.y;
      if ( max.y > (double)v6->bounds.b[1].y )
        v6->bounds.b[1].y = max.y;
      if ( max.z < (double)v6->bounds.b[0].z )
        v6->bounds.b[0].z = max.z;
      if ( max.z > (double)v6->bounds.b[1].z )
        v6->bounds.b[1].z = max.z;
      m_primBatches = this->m_primBatches;
      v10 += *(int *)((char *)&surfacea[1].shader + (_DWORD)m_primBatches);
      v11 += *(int *)((char *)&surfacea->shader + (_DWORD)m_primBatches);
      surfacea = (modelSurface_s *)((char *)surfacea + 72);
      ++primBatch;
    }
    while ( primBatch < this->m_numPrimBatches );
  }
  this->m_drawSetUp = 0;
}

// FUNC: public: void __thiscall rvMesh::UpdateSurface(struct modelSurface_s &)
void __thiscall rvMesh::UpdateSurface(rvMesh *this, modelSurface_s *surface)
{
  srfTriangles_s *geometry; // eax
  int v4; // ebx
  srfTriangles_s *v5; // edi
  int m_numSilTraceVertices; // eax
  int v7; // edx
  int v8; // ebp
  int *p_m_primitiveCount; // eax
  int v10; // ecx
  bool v11; // zf
  rvSilTraceVertT *SilTraceVertexArray; // edx
  modelSurface_s *surfacea; // [esp+10h] [ebp+4h]

  surface->shader = this->m_material;
  geometry = surface->geometry;
  v4 = 0;
  if ( !geometry )
    goto LABEL_7;
  if ( !geometry->verts
    && (!geometry->silTraceVerts
     || geometry->numVerts != this->m_numSilTraceVertices
     || geometry->numIndexes != this->m_numSilTraceIndices) )
  {
    R_FreeStaticTriSurf(surface->geometry);
LABEL_7:
    surface->geometry = R_AllocStaticTriSurf();
    goto LABEL_8;
  }
  R_FreeStaticTriSurfVertexCaches(surface->geometry);
LABEL_8:
  v5 = surface->geometry;
  v5->deformedSurface = 0;
  v5->tangentsCalculated = 1;
  v5->facePlanesCalculated = 0;
  v5->primBatchMesh = this;
  m_numSilTraceVertices = this->m_numSilTraceVertices;
  if ( m_numSilTraceVertices )
  {
    v5->numVerts = m_numSilTraceVertices;
    v5->numIndexes = this->m_numSilTraceIndices;
    v5->numSilEdges = this->m_numSilEdges;
    v5->silEdges = &this->m_renderModel->m_silEdges[this->m_primBatches->m_silEdgeStart];
    SilTraceVertexArray = rvVertexBuffer::GetSilTraceVertexArray(
                            &this->m_renderModel->m_vertexBuffers[this->m_silTraceVertexBuffer],
                            this->m_primBatches->m_silTraceGeoSpec.m_vertexStart);
    v5->silTraceVerts = SilTraceVertexArray;
    if ( this->m_bounds.b[0].x <= (double)this->m_bounds.b[1].x )
    {
      v5->bounds.b[0].x = this->m_bounds.b[0].x;
      v5->bounds.b[0].y = this->m_bounds.b[0].y;
      v5->bounds.b[0].z = this->m_bounds.b[0].z;
      v5->bounds.b[1].x = this->m_bounds.b[1].x;
      v5->bounds.b[1].y = this->m_bounds.b[1].y;
      v5->bounds.b[1].z = this->m_bounds.b[1].z;
    }
    else
    {
      (*(void (__fastcall **)(idSIMDProcessor *, srfTriangles_s *, idVec3 *, rvSilTraceVertT *, int))&SIMDProcessor->gap7C[4])(
        SIMDProcessor,
        v5,
        &v5->bounds.b[1],
        SilTraceVertexArray,
        this->m_numSilTraceVertices);
    }
  }
  else
  {
    v7 = 0;
    v8 = 0;
    if ( this->m_numPrimBatches > 0 )
    {
      p_m_primitiveCount = &this->m_primBatches->m_shadowVolGeoSpec.m_primitiveCount;
      surfacea = (modelSurface_s *)this->m_numPrimBatches;
      do
      {
        v4 += *(p_m_primitiveCount - 2);
        v7 += *p_m_primitiveCount + 2 * *p_m_primitiveCount;
        v10 = p_m_primitiveCount[1];
        p_m_primitiveCount += 18;
        v11 = surfacea == (modelSurface_s *)1;
        surfacea = (modelSurface_s *)((char *)surfacea - 1);
        v8 += v10 + 2 * v10;
      }
      while ( !v11 );
    }
    v5->numVerts = v4;
    v5->numShadowIndexesNoCaps = v8;
    v5->numIndexes = v7;
    v5->numShadowIndexesNoFrontCaps = v7;
    v5->shadowCapPlaneBits = this->m_primBatches->m_shadowCapPlaneBits;
    v5->bounds.b[0].x = this->m_bounds.b[0].x;
    v5->bounds.b[0].y = this->m_bounds.b[0].y;
    v5->bounds.b[0].z = this->m_bounds.b[0].z;
    v5->bounds.b[1].x = this->m_bounds.b[1].x;
    v5->bounds.b[1].y = this->m_bounds.b[1].y;
    v5->bounds.b[1].z = this->m_bounds.b[1].z;
  }
}

// FUNC: public: void __thiscall rvMesh::CreateLightTris(struct srfTriangles_s &,int &,int &,struct srfCullInfo_s &,class rvSilTraceVertT const *,bool)
void __thiscall rvMesh::CreateLightTris(
        rvMesh *this,
        srfTriangles_s *newTri,
        int *c_backfaced,
        int *c_distance,
        srfCullInfo_s *cullInfo,
        const rvSilTraceVertT *silTraceVerts,
        bool includeBackFaces)
{
  srfCullInfo_s *v7; // ebx
  rvIndexBuffer *m_indexBuffers; // eax
  rvIndexBuffer *v10; // edx
  int m_drawIndexBuffer; // ecx
  int m_numPrimBatches; // eax
  int *v14; // ebp
  int v15; // ebx
  srfCullInfo_s *v16; // eax
  rvPrimBatch *m_primBatches; // ecx
  int v18; // [esp-4h] [ebp-50h]
  int numIndices; // [esp+10h] [ebp-3Ch]
  unsigned __int8 *facing; // [esp+14h] [ebp-38h]
  unsigned __int8 *cullBits; // [esp+18h] [ebp-34h]
  int batchBackFaced; // [esp+1Ch] [ebp-30h] BYREF
  int batchDistance; // [esp+20h] [ebp-2Ch] BYREF
  rvIndexBuffer *drawIB; // [esp+24h] [ebp-28h]
  rvIndexBuffer *silTraceIB; // [esp+28h] [ebp-24h]
  idPlane *localClipPlanes; // [esp+2Ch] [ebp-20h]
  int *indexes; // [esp+30h] [ebp-1Ch]
  idBounds batchBounds; // [esp+34h] [ebp-18h] BYREF
  srfTriangles_s *newTria; // [esp+50h] [ebp+4h]

  v7 = cullInfo;
  cullBits = cullInfo->cullBits;
  facing = cullInfo->facing;
  m_indexBuffers = this->m_renderModel->m_indexBuffers;
  v10 = &m_indexBuffers[this->m_silTraceIndexBuffer];
  m_drawIndexBuffer = this->m_drawIndexBuffer;
  silTraceIB = v10;
  v18 = this->m_numSilTraceIndices + this->m_numPrimBatches;
  numIndices = 0;
  drawIB = &m_indexBuffers[m_drawIndexBuffer];
  R_AllocStaticTriSurfIndexes(newTri, v18);
  newTri->bounds.b[0].z = idMath::INFINITY;
  newTri->bounds.b[0].y = idMath::INFINITY;
  newTri->bounds.b[0].x = idMath::INFINITY;
  newTria = 0;
  newTri->bounds.b[1].z = -1.0e30;
  newTri->bounds.b[1].y = -1.0e30;
  newTri->bounds.b[1].x = -1.0e30;
  m_numPrimBatches = this->m_numPrimBatches;
  indexes = newTri->indexes;
  v14 = &indexes[m_numPrimBatches];
  if ( m_numPrimBatches <= 0 )
    goto LABEL_31;
  localClipPlanes = v7->localClipPlanes;
  v15 = 0;
  do
  {
    cullInfo = 0;
    batchBackFaced = 0;
    batchDistance = 0;
    rvPrimBatch::CreateLightTris(
      &this->m_primBatches[v15],
      v14,
      (int *)&cullInfo,
      &batchBounds,
      &batchBackFaced,
      &batchDistance,
      facing,
      cullBits,
      localClipPlanes,
      silTraceVerts,
      includeBackFaces,
      silTraceIB,
      drawIB);
    indexes[(_DWORD)newTria] = (int)cullInfo;
    v16 = cullInfo;
    numIndices += (int)cullInfo;
    silTraceVerts += this->m_primBatches[v15].m_silTraceGeoSpec.m_vertexCount;
    *c_backfaced += batchBackFaced;
    *c_distance += batchDistance;
    m_primBatches = this->m_primBatches;
    facing += m_primBatches[v15].m_silTraceGeoSpec.m_primitiveCount;
    cullBits += m_primBatches[v15].m_silTraceGeoSpec.m_vertexCount;
    v14 += (int)v16;
    if ( v16 )
    {
      if ( batchBounds.b[0].x < (double)newTri->bounds.b[0].x )
        newTri->bounds.b[0].x = batchBounds.b[0].x;
      if ( batchBounds.b[0].x > (double)newTri->bounds.b[1].x )
        newTri->bounds.b[1].x = batchBounds.b[0].x;
      if ( batchBounds.b[0].y < (double)newTri->bounds.b[0].y )
        newTri->bounds.b[0].y = batchBounds.b[0].y;
      if ( batchBounds.b[0].y > (double)newTri->bounds.b[1].y )
        newTri->bounds.b[1].y = batchBounds.b[0].y;
      if ( batchBounds.b[0].z < (double)newTri->bounds.b[0].z )
        newTri->bounds.b[0].z = batchBounds.b[0].z;
      if ( batchBounds.b[0].z > (double)newTri->bounds.b[1].z )
        newTri->bounds.b[1].z = batchBounds.b[0].z;
      if ( batchBounds.b[1].x < (double)newTri->bounds.b[0].x )
        newTri->bounds.b[0].x = batchBounds.b[1].x;
      if ( batchBounds.b[1].x > (double)newTri->bounds.b[1].x )
        newTri->bounds.b[1].x = batchBounds.b[1].x;
      if ( batchBounds.b[1].y < (double)newTri->bounds.b[0].y )
        newTri->bounds.b[0].y = batchBounds.b[1].y;
      if ( batchBounds.b[1].y > (double)newTri->bounds.b[1].y )
        newTri->bounds.b[1].y = batchBounds.b[1].y;
      if ( batchBounds.b[1].z < (double)newTri->bounds.b[0].z )
        newTri->bounds.b[0].z = batchBounds.b[1].z;
      if ( batchBounds.b[1].z > (double)newTri->bounds.b[1].z )
        newTri->bounds.b[1].z = batchBounds.b[1].z;
    }
    ++v15;
    newTria = (srfTriangles_s *)((char *)newTria + 1);
  }
  while ( (int)newTria < this->m_numPrimBatches );
  if ( numIndices )
  {
    R_ResizeStaticTriSurfIndexes(newTri, numIndices + this->m_numPrimBatches);
    newTri->numIndexes = numIndices;
  }
  else
  {
LABEL_31:
    R_ResizeStaticTriSurfIndexes(newTri, 0);
    newTri->numIndexes = numIndices;
  }
}

// FUNC: public: void __thiscall rvMesh::CreateFrontFaceTris(struct srfTriangles_s &,int &,struct srfCullInfo_s &,class rvSilTraceVertT const *)
void __thiscall rvMesh::CreateFrontFaceTris(
        rvMesh *this,
        srfTriangles_s *newTri,
        int *c_backfaced,
        srfCullInfo_s *cullInfo,
        const rvSilTraceVertT *silTraceVerts)
{
  rvIndexBuffer *m_indexBuffers; // eax
  rvIndexBuffer *v7; // edx
  int m_drawIndexBuffer; // ecx
  int v10; // ebx
  int m_numPrimBatches; // eax
  int *v12; // ebp
  int m_vertexCount; // eax
  int v14; // [esp-4h] [ebp-44h]
  int numIndices; // [esp+10h] [ebp-30h]
  unsigned __int8 *facing; // [esp+14h] [ebp-2Ch]
  int batchBackFaced; // [esp+18h] [ebp-28h] BYREF
  rvIndexBuffer *drawIB; // [esp+1Ch] [ebp-24h]
  rvIndexBuffer *silTraceIB; // [esp+20h] [ebp-20h]
  int *indexes; // [esp+24h] [ebp-1Ch]
  idBounds batchBounds; // [esp+28h] [ebp-18h] BYREF
  srfTriangles_s *newTria; // [esp+44h] [ebp+4h]

  m_indexBuffers = this->m_renderModel->m_indexBuffers;
  facing = cullInfo->facing;
  v7 = &m_indexBuffers[this->m_silTraceIndexBuffer];
  m_drawIndexBuffer = this->m_drawIndexBuffer;
  silTraceIB = v7;
  v14 = this->m_numSilTraceIndices + this->m_numPrimBatches;
  v10 = 0;
  numIndices = 0;
  drawIB = &m_indexBuffers[m_drawIndexBuffer];
  R_AllocStaticTriSurfIndexes(newTri, v14);
  newTri->bounds.b[0].z = idMath::INFINITY;
  newTri->bounds.b[0].y = idMath::INFINITY;
  newTri->bounds.b[0].x = idMath::INFINITY;
  newTria = 0;
  newTri->bounds.b[1].z = -1.0e30;
  newTri->bounds.b[1].y = -1.0e30;
  newTri->bounds.b[1].x = -1.0e30;
  m_numPrimBatches = this->m_numPrimBatches;
  indexes = newTri->indexes;
  v12 = &indexes[m_numPrimBatches];
  if ( m_numPrimBatches <= 0 )
    goto LABEL_30;
  do
  {
    cullInfo = 0;
    batchBackFaced = 0;
    rvPrimBatch::CreateFrontFaceTris(
      &this->m_primBatches[v10],
      v12,
      (int *)&cullInfo,
      &batchBounds,
      &batchBackFaced,
      facing,
      silTraceVerts,
      silTraceIB,
      drawIB);
    indexes[(_DWORD)newTria] = (int)cullInfo;
    m_vertexCount = this->m_primBatches[v10].m_silTraceGeoSpec.m_vertexCount;
    *c_backfaced += batchBackFaced;
    facing += this->m_primBatches[v10].m_silTraceGeoSpec.m_primitiveCount;
    silTraceVerts += m_vertexCount;
    numIndices += (int)cullInfo;
    v12 += (int)cullInfo;
    if ( cullInfo )
    {
      if ( batchBounds.b[0].x < (double)newTri->bounds.b[0].x )
        newTri->bounds.b[0].x = batchBounds.b[0].x;
      if ( batchBounds.b[0].x > (double)newTri->bounds.b[1].x )
        newTri->bounds.b[1].x = batchBounds.b[0].x;
      if ( batchBounds.b[0].y < (double)newTri->bounds.b[0].y )
        newTri->bounds.b[0].y = batchBounds.b[0].y;
      if ( batchBounds.b[0].y > (double)newTri->bounds.b[1].y )
        newTri->bounds.b[1].y = batchBounds.b[0].y;
      if ( batchBounds.b[0].z < (double)newTri->bounds.b[0].z )
        newTri->bounds.b[0].z = batchBounds.b[0].z;
      if ( batchBounds.b[0].z > (double)newTri->bounds.b[1].z )
        newTri->bounds.b[1].z = batchBounds.b[0].z;
      if ( batchBounds.b[1].x < (double)newTri->bounds.b[0].x )
        newTri->bounds.b[0].x = batchBounds.b[1].x;
      if ( batchBounds.b[1].x > (double)newTri->bounds.b[1].x )
        newTri->bounds.b[1].x = batchBounds.b[1].x;
      if ( batchBounds.b[1].y < (double)newTri->bounds.b[0].y )
        newTri->bounds.b[0].y = batchBounds.b[1].y;
      if ( batchBounds.b[1].y > (double)newTri->bounds.b[1].y )
        newTri->bounds.b[1].y = batchBounds.b[1].y;
      if ( batchBounds.b[1].z < (double)newTri->bounds.b[0].z )
        newTri->bounds.b[0].z = batchBounds.b[1].z;
      if ( batchBounds.b[1].z > (double)newTri->bounds.b[1].z )
        newTri->bounds.b[1].z = batchBounds.b[1].z;
    }
    ++v10;
    newTria = (srfTriangles_s *)((char *)newTria + 1);
  }
  while ( (int)newTria < this->m_numPrimBatches );
  if ( numIndices )
  {
    R_ResizeStaticTriSurfIndexes(newTri, numIndices + this->m_numPrimBatches);
    newTri->numIndexes = numIndices;
  }
  else
  {
LABEL_30:
    R_ResizeStaticTriSurfIndexes(newTri, 0);
    newTri->numIndexes = numIndices;
  }
}

// FUNC: public: void __thiscall rvMesh::Write(class idFile &,char const *)
void __thiscall rvMesh::Write(rvMesh *this, idFile *outFile, const char *prepend)
{
  int v4; // eax
  void *v5; // esp
  idFile_vtbl *v7; // eax
  const char *v8; // ebx
  int v9; // eax
  __int16 m_levelOfDetail; // ax
  const idMaterial *m_material; // eax
  int v12; // eax
  __int16 v13; // ax
  __int16 m_silTraceVertexBuffer; // ax
  __int16 m_drawVertexBuffer; // ax
  __int16 m_shadowVolVertexBuffer; // ax
  int v17; // edx
  bool v18; // cc
  int m_numPrimBatches; // ecx
  char *v20; // eax
  char v21[12]; // [esp+30h] [ebp-18h] BYREF
  char *v22; // [esp+3Ch] [ebp-Ch]
  int curPrimBatch; // [esp+40h] [ebp-8h]
  int prependLen; // [esp+44h] [ebp-4h]
  idFile *outFileb; // [esp+50h] [ebp+8h]
  idFile *outFilea; // [esp+50h] [ebp+8h]

  prependLen = strlen(prepend);
  v4 = prependLen + 6;
  LOBYTE(v4) = (prependLen + 6) & 0xFC;
  v5 = alloca(v4);
  v7 = outFile->__vftable;
  v8 = v21;
  curPrimBatch = (int)v21;
  v7->WriteFloatString(outFile, "%sMesh\n", prepend);
  outFile->WriteFloatString(outFile, "%s{\n", prepend);
  strcpy(v21, prepend);
  v9 = prependLen;
  v21[prependLen] = 9;
  v22 = &v21[v9 + 1];
  *v22 = 0;
  m_levelOfDetail = this->m_levelOfDetail;
  if ( m_levelOfDetail != -1 )
    outFile->WriteFloatString(outFile, "%sLevelOfDetail %d\n", v21, m_levelOfDetail);
  m_material = this->m_material;
  if ( m_material )
  {
    outFileb = (idFile *)outFile->__vftable;
    v12 = (int)m_material->base->GetName(m_material->base);
    v8 = (const char *)curPrimBatch;
    ((void (*)(idFile *, const char *, ...))outFileb[14].__vftable)(outFile, "%sMaterial \"%s\"\n", curPrimBatch, v12);
  }
  v13 = this->m_levelOfDetail;
  if ( v13 >= 0 )
    outFile->WriteFloatString(outFile, "%sLevelOfDetail %d\n", v8, v13);
  m_silTraceVertexBuffer = this->m_silTraceVertexBuffer;
  if ( m_silTraceVertexBuffer >= 0 || this->m_silTraceIndexBuffer >= 0 )
    outFile->WriteFloatString(
      outFile,
      "%sSilTraceBuffers %d %d\n",
      v8,
      m_silTraceVertexBuffer,
      this->m_silTraceIndexBuffer);
  m_drawVertexBuffer = this->m_drawVertexBuffer;
  if ( m_drawVertexBuffer >= 0 || this->m_drawIndexBuffer >= 0 )
    outFile->WriteFloatString(outFile, "%sDrawBuffers %d %d\n", v8, m_drawVertexBuffer, this->m_drawIndexBuffer);
  m_shadowVolVertexBuffer = this->m_shadowVolVertexBuffer;
  if ( m_shadowVolVertexBuffer >= 0 || this->m_shadowVolIndexBuffer >= 0 )
    outFile->WriteFloatString(
      outFile,
      "%sShadowVolumeBuffers %d %d\n",
      v8,
      m_shadowVolVertexBuffer,
      this->m_shadowVolIndexBuffer);
  outFile->WriteFloatString(outFile, "%sPrimBatch[ %d ]\n", v8, this->m_numPrimBatches);
  outFile->WriteFloatString(outFile, "%s{\n", v8);
  v17 = prependLen;
  *v22 = 9;
  v8[v17 + 2] = 0;
  v18 = this->m_numPrimBatches <= 0;
  curPrimBatch = 0;
  if ( !v18 )
  {
    outFilea = 0;
    do
    {
      rvPrimBatch::Write((rvPrimBatch *)((char *)outFilea + (unsigned int)this->m_primBatches), outFile, v8);
      m_numPrimBatches = this->m_numPrimBatches;
      outFilea += 18;
      ++curPrimBatch;
    }
    while ( curPrimBatch < m_numPrimBatches );
  }
  v20 = v22;
  v8[prependLen] = 9;
  *v20 = 0;
  outFile->WriteFloatString(outFile, "%s}\n", v8);
  if ( this->m_bounds.b[0].x <= (double)this->m_bounds.b[1].x )
    outFile->WriteFloatString(
      outFile,
      "%sBounds %f %f %f  %f %f %f\n",
      v8,
      this->m_bounds.b[0].x,
      this->m_bounds.b[0].y,
      this->m_bounds.b[0].z,
      this->m_bounds.b[1].x,
      this->m_bounds.b[1].y,
      this->m_bounds.b[1].z);
  outFile->WriteFloatString(outFile, "%s}\n", prepend);
}

// FUNC: public: __thiscall rvMesh::rvMesh(void)
void __thiscall rvMesh::rvMesh(rvMesh *this)
{
  rvMesh::ResetValues(this);
}

// FUNC: public: void __thiscall rvMesh::SurfaceToTextureAxis(class idVec3 &,class idVec3 * const,class rvSilTraceVertT const *)
void __thiscall rvMesh::SurfaceToTextureAxis(
        rvMesh *this,
        idVec3 *origin,
        idVec3 *axis,
        const rvSilTraceVertT *silTraceVerts)
{
  int m_drawIndexBuffer; // edx
  rvRenderModelMD5R *m_renderModel; // ecx
  rvIndexBuffer *m_indexBuffers; // eax
  int v8; // edi
  bool v9; // cc
  rvVertexBuffer *v10; // ebx
  int v11; // ebp
  double v12; // st7
  double v13; // st6
  double v14; // st5
  double v15; // st4
  double v16; // st3
  double v17; // st2
  double v18; // st2
  double v19; // st2
  double v20; // st7
  double v21; // st6
  double v22; // st5
  double v23; // st4
  double v24; // st6
  double v25; // st7
  long double v26; // st7
  unsigned __int8 v28; // c2
  unsigned __int8 v29; // c3
  float v30; // eax
  double v31; // st7
  double v32; // st7
  double v33; // st7
  rvIndexBuffer *silTraceIndexBuffer; // [esp+14h] [ebp-F8h]
  float silTraceIndexBuffera; // [esp+14h] [ebp-F8h]
  float silTraceIndexBufferb; // [esp+14h] [ebp-F8h]
  float silTraceIndexBufferc; // [esp+14h] [ebp-F8h]
  float bounds[2][2]; // [esp+18h] [ebp-F4h] BYREF
  float v39; // [esp+28h] [ebp-E4h]
  float d0[5]; // [esp+2Ch] [ebp-E0h]
  rvIndexBuffer *drawIndexBuffer; // [esp+40h] [ebp-CCh]
  float boundsOrg[2]; // [esp+44h] [ebp-C8h]
  idDrawVert a; // [esp+4Ch] [ebp-C0h] BYREF
  idDrawVert b; // [esp+8Ch] [ebp-80h] BYREF
  idDrawVert c; // [esp+CCh] [ebp-40h] BYREF

  m_drawIndexBuffer = this->m_drawIndexBuffer;
  m_renderModel = this->m_renderModel;
  m_indexBuffers = m_renderModel->m_indexBuffers;
  drawIndexBuffer = &m_indexBuffers[m_drawIndexBuffer];
  silTraceIndexBuffer = &m_indexBuffers[this->m_silTraceIndexBuffer];
  v8 = 0;
  v9 = this->m_numPrimBatches <= 0;
  v10 = &m_renderModel->m_vertexBuffers[this->m_drawVertexBuffer];
  *(_QWORD *)&bounds[0][0] = 0x497423F0497423F0i64;
  *(_QWORD *)&bounds[1][0] = 0xC97423F0C97423F0ui64;
  if ( !v9 )
  {
    v11 = 0;
    do
    {
      rvPrimBatch::GetTextureBounds(&this->m_primBatches[v11], bounds, v10);
      ++v8;
      ++v11;
    }
    while ( v8 < this->m_numPrimBatches );
  }
  boundsOrg[0] = floor((bounds[1][0] + bounds[0][0]) * 0.5);
  boundsOrg[1] = floor((bounds[1][1] + bounds[0][1]) * 0.5);
  rvPrimBatch::GetTriangle(this->m_primBatches, &a, &b, &c, 0, v10, drawIndexBuffer, silTraceVerts, silTraceIndexBuffer);
  v12 = b.xyz.x - a.xyz.x;
  d0[1] = b.xyz.y - a.xyz.y;
  v13 = b.xyz.z - a.xyz.z;
  v14 = b.st.x - a.st.x;
  d0[4] = b.st.y - a.st.y;
  bounds[0][0] = c.xyz.x - a.xyz.x;
  bounds[0][1] = c.xyz.y - a.xyz.y;
  v15 = c.xyz.z - a.xyz.z;
  v16 = c.st.x - a.st.x;
  v17 = c.st.y - a.st.y;
  v39 = v17;
  v18 = v17 * v14 - v16 * d0[4];
  if ( 0.0 == v18 )
  {
    axis->z = 0.0;
    axis->y = 0.0;
    axis->x = 0.0;
    axis[1].z = 0.0;
    axis[1].y = 0.0;
    axis[1].x = 0.0;
    axis[2].z = 0.0;
    axis[2].y = 0.0;
    axis[2].x = 0.0;
    return;
  }
  v19 = 1.0 / v18;
  axis->x = (v39 * v12 - bounds[0][0] * d0[4]) * v19;
  axis->y = (v39 * d0[1] - bounds[0][1] * d0[4]) * v19;
  axis->z = (v39 * v13 - v15 * d0[4]) * v19;
  axis[1].x = (bounds[0][0] * v14 - v16 * v12) * v19;
  axis[1].y = (bounds[0][1] * v14 - v16 * d0[1]) * v19;
  axis[1].z = (v15 * v14 - v16 * v13) * v19;
  v20 = c.xyz.x - b.xyz.x;
  v21 = c.xyz.y - b.xyz.y;
  v22 = c.xyz.z - b.xyz.z;
  bounds[0][0] = a.xyz.x - b.xyz.x;
  bounds[0][1] = a.xyz.y - b.xyz.y;
  v23 = a.xyz.z - b.xyz.z;
  d0[0] = bounds[0][1] * v22 - v23 * v21;
  d0[1] = v23 * v20 - v22 * bounds[0][0];
  v24 = v21 * bounds[0][0];
  bounds[0][0] = d0[0];
  d0[2] = v24 - bounds[0][1] * v20;
  bounds[1][0] = d0[2];
  v25 = d0[1];
  silTraceIndexBuffera = d0[0] * d0[0] + d0[2] * d0[2] + d0[1] * d0[1];
  if ( silTraceIndexBuffera != 0.0 )
  {
    v26 = 1.0 / sqrt(silTraceIndexBuffera);
    silTraceIndexBufferb = v26;
    bounds[0][0] = v26 * d0[0];
    v25 = d0[1] * silTraceIndexBufferb;
    bounds[1][0] = d0[2] * silTraceIndexBufferb;
  }
  if ( v29 | v28 )
  {
    if ( v25 == 0.0 )
    {
      if ( bounds[1][0] <= 0.0 )
      {
        if ( bounds[1][0] != -1.0 )
          bounds[1][0] = -1.0;
      }
      else if ( bounds[1][0] != 1.0 )
      {
        bounds[1][0] = 1.0;
      }
      goto LABEL_41;
    }
    if ( bounds[1][0] == 0.0 )
    {
      if ( v25 <= 0.0 )
      {
        if ( v25 != -1.0 )
          v25 = -1.0;
      }
      else if ( v25 != 1.0 )
      {
        v25 = 1.0;
      }
      goto LABEL_41;
    }
  }
  else if ( v25 == 0.0 && bounds[1][0] == 0.0 )
  {
    if ( bounds[0][0] <= 0.0 )
    {
      if ( bounds[0][0] != -1.0 )
        bounds[0][0] = -1.0;
    }
    else if ( bounds[0][0] != 1.0 )
    {
      bounds[0][0] = 1.0;
    }
    goto LABEL_41;
  }
  if ( COERCE_FLOAT(LODWORD(bounds[0][0]) & 0x7FFFFFFF) == 1.0 )
  {
    if ( v25 == 0.0 && bounds[1][0] == 0.0 )
      goto LABEL_41;
    bounds[1][0] = 0.0;
    goto LABEL_40;
  }
  silTraceIndexBufferc = v25;
  if ( COERCE_FLOAT(LODWORD(silTraceIndexBufferc) & 0x7FFFFFFF) == 1.0 )
  {
    if ( bounds[0][0] != 0.0 || bounds[1][0] != 0.0 )
    {
      bounds[1][0] = 0.0;
      bounds[0][0] = 0.0;
    }
    goto LABEL_41;
  }
  if ( COERCE_FLOAT(LODWORD(bounds[1][0]) & 0x7FFFFFFF) == 1.0 && (bounds[0][0] != 0.0 || v25 != 0.0) )
  {
    bounds[0][0] = 0.0;
LABEL_40:
    v25 = 0.0;
  }
LABEL_41:
  v30 = bounds[1][0];
  axis[2].x = bounds[0][0];
  axis[2].y = v25;
  v31 = boundsOrg[0];
  axis[2].z = v30;
  v32 = v31 - a.st.x;
  origin->x = v32 * axis->x + a.xyz.x;
  origin->y = v32 * axis->y + a.xyz.y;
  origin->z = v32 * axis->z + a.xyz.z;
  v33 = boundsOrg[1] - a.st.y;
  origin->x = v33 * axis[1].x + origin->x;
  origin->y = v33 * axis[1].y + origin->y;
  origin->z = v33 * axis[1].z + origin->z;
}

// FUNC: public: __thiscall rvMesh::~rvMesh(void)
void __thiscall rvMesh::~rvMesh(rvMesh *this)
{
  rvPrimBatch *m_primBatches; // eax
  int *p_m_shadowCapPlaneBits; // esi

  m_primBatches = this->m_primBatches;
  if ( m_primBatches )
  {
    p_m_shadowCapPlaneBits = &m_primBatches[-1].m_shadowCapPlaneBits;
    `eh vector destructor iterator'(
      m_primBatches,
      0x48u,
      m_primBatches[-1].m_shadowCapPlaneBits,
      (void (__thiscall *)(void *))rvPrimBatch::~rvPrimBatch);
    Memory::Free(p_m_shadowCapPlaneBits);
  }
  rvMesh::ResetValues(this);
}

// FUNC: public: void __thiscall rvMesh::Init(class rvRenderModelMD5R &,class Lexer &)
void __thiscall rvMesh::Init(rvMesh *this, rvRenderModelMD5R *renderModel, Lexer *lex)
{
  bool v4; // zf
  rvPrimBatch *m_primBatches; // eax
  int *p_m_shadowCapPlaneBits; // esi
  int len; // esi
  __int16 v8; // ax
  rvRenderModelMD5R *v9; // edi
  int m_silTraceVertexBuffer; // edx
  __int16 v11; // ax
  int m_drawVertexBuffer; // edx
  __int16 v13; // ax
  int m_shadowVolVertexBuffer; // edx
  int m_numPrimBatches; // esi
  int *v16; // eax
  rvPrimBatch *v17; // eax
  int v18; // esi
  int v19; // edi
  float *v20; // ecx
  float *p_y; // eax
  __int16 v22; // ax
  __int16 m_drawIndexBuffer; // bx
  rvVertexBuffer *m_vertexBuffers; // ecx
  rvVertexBuffer *v25; // esi
  rvIndexBuffer *m_indexBuffers; // edx
  rvVertexBuffer *v27; // ecx
  int v28; // edi
  int v29; // ebx
  __int16 v30; // ax
  rvVertexBuffer *v31; // ecx
  rvVertexBuffer *v32; // ebx
  int v33; // esi
  int v34; // edi
  int srcVertexBuffer; // [esp+8h] [ebp-B8h]
  rvVertexBuffer *srcVertexBufferd; // [esp+8h] [ebp-B8h]
  int srcVertexBuffera; // [esp+8h] [ebp-B8h]
  rvVertexBuffer *srcVertexBufferb; // [esp+8h] [ebp-B8h]
  rvVertexBuffer *srcVertexBufferc; // [esp+8h] [ebp-B8h]
  rvIndexBuffer *destIndexBuffer; // [esp+Ch] [ebp-B4h]
  float min; // [esp+10h] [ebp-B0h]
  float min_4; // [esp+14h] [ebp-ACh]
  int min_8; // [esp+18h] [ebp-A8h]
  rvIndexBuffer *srcIndexBuffer; // [esp+1Ch] [ebp-A4h]
  idStr materialName; // [esp+20h] [ebp-A0h] BYREF
  float v46; // [esp+40h] [ebp-80h] BYREF
  int v47[5]; // [esp+44h] [ebp-7Ch] BYREF
  idToken token; // [esp+58h] [ebp-68h] BYREF
  idVec3 max; // [esp+A8h] [ebp-18h]
  int v50; // [esp+BCh] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v50 = 0;
  materialName.len = 0;
  materialName.alloced = 20;
  materialName.data = materialName.baseBuffer;
  materialName.baseBuffer[0] = 0;
  v4 = this->m_renderModel == 0;
  LOBYTE(v50) = 1;
  if ( !v4 )
  {
    m_primBatches = this->m_primBatches;
    if ( m_primBatches )
    {
      p_m_shadowCapPlaneBits = &m_primBatches[-1].m_shadowCapPlaneBits;
      `eh vector destructor iterator'(
        m_primBatches,
        0x48u,
        m_primBatches[-1].m_shadowCapPlaneBits,
        (void (__thiscall *)(void *))rvPrimBatch::~rvPrimBatch);
      Memory::Free(p_m_shadowCapPlaneBits);
    }
    rvMesh::ResetValues(this);
  }
  Lexer::ExpectTokenString(lex, "{");
  if ( !Lexer::ReadToken(lex, &token) )
    Lexer::Error(lex, "Expected keyword.");
  if ( !idStr::Icmp(token.data, "LevelOfDetail") )
  {
    this->m_levelOfDetail = Lexer::ParseInt(lex);
    Lexer::ReadToken(lex, &token);
  }
  if ( idStr::Icmp(token.data, "Material") )
    Lexer::Error(lex, "Expected Material keyword.");
  Lexer::ReadToken(lex, &token);
  len = token.len;
  srcVertexBuffer = token.len;
  if ( token.len + 1 > materialName.alloced )
    idStr::ReAllocate(&materialName, token.len + 1, 0);
  qmemcpy(materialName.data, token.data, len);
  materialName.data[srcVertexBuffer] = 0;
  materialName.len = srcVertexBuffer;
  this->m_material = declManager->FindMaterial(declManager, materialName.data, 1);
  if ( !Lexer::ReadToken(lex, &token) )
    Lexer::Error(lex, "Expected SilhouetteEdge, SilTracePrimBatch or DrawPrimBatch keyword.");
  if ( idStr::Icmp(token.data, "SilTraceBuffers") )
  {
    v9 = renderModel;
  }
  else
  {
    this->m_silTraceVertexBuffer = Lexer::ParseInt(lex);
    v8 = Lexer::ParseInt(lex);
    v9 = renderModel;
    m_silTraceVertexBuffer = this->m_silTraceVertexBuffer;
    this->m_silTraceIndexBuffer = v8;
    if ( m_silTraceVertexBuffer >= renderModel->m_numVertexBuffers || v8 >= renderModel->m_numIndexBuffers )
      Lexer::Error(lex, "Invalid buffer reference by SilTraceBuffers statement");
    Lexer::ReadToken(lex, &token);
  }
  if ( !idStr::Icmp(token.data, "DrawBuffers") )
  {
    this->m_drawVertexBuffer = Lexer::ParseInt(lex);
    v11 = Lexer::ParseInt(lex);
    m_drawVertexBuffer = this->m_drawVertexBuffer;
    this->m_drawIndexBuffer = v11;
    if ( m_drawVertexBuffer >= v9->m_numVertexBuffers || v11 >= v9->m_numIndexBuffers )
      Lexer::Error(lex, "Invalid buffer reference by DrawBuffers statement");
    Lexer::ReadToken(lex, &token);
  }
  if ( !idStr::Icmp(token.data, "ShadowVolumeBuffers") )
  {
    this->m_shadowVolVertexBuffer = Lexer::ParseInt(lex);
    v13 = Lexer::ParseInt(lex);
    m_shadowVolVertexBuffer = this->m_shadowVolVertexBuffer;
    this->m_shadowVolIndexBuffer = v13;
    if ( m_shadowVolVertexBuffer >= v9->m_numVertexBuffers || v13 >= v9->m_numIndexBuffers )
      Lexer::Error(lex, "Invalid buffer reference by ShadowVolumeBuffers statement");
    Lexer::ReadToken(lex, &token);
  }
  if ( idStr::Icmp(token.data, "PrimBatch") )
    Lexer::Error(lex, "Expected PrimBatch keyword.");
  Lexer::ExpectTokenString(lex, "[");
  this->m_numPrimBatches = Lexer::ParseInt(lex);
  Lexer::ExpectTokenString(lex, "]");
  Lexer::ExpectTokenString(lex, "{");
  m_numPrimBatches = this->m_numPrimBatches;
  v16 = (int *)Memory::Allocate(72 * m_numPrimBatches + 4);
  LOBYTE(v50) = 2;
  if ( v16 )
  {
    *v16 = m_numPrimBatches;
    srcVertexBufferd = (rvVertexBuffer *)(v16 + 1);
    `eh vector constructor iterator'(
      v16 + 1,
      0x48u,
      m_numPrimBatches,
      (void (__thiscall *)(void *))rvPrimBatch::rvPrimBatch,
      (void (__thiscall *)(void *))rvPrimBatch::~rvPrimBatch);
    v17 = (rvPrimBatch *)srcVertexBufferd;
  }
  else
  {
    v17 = 0;
  }
  LOBYTE(v50) = 1;
  this->m_primBatches = v17;
  if ( v17 )
  {
    v18 = 0;
    if ( this->m_numPrimBatches > 0 )
    {
      v19 = 0;
      do
      {
        Lexer::ExpectTokenString(lex, "PrimBatch");
        rvPrimBatch::Init(&this->m_primBatches[v19], lex);
        ++v18;
        ++v19;
      }
      while ( v18 < this->m_numPrimBatches );
      v9 = renderModel;
    }
    rvMesh::CalcGeometryProfile(this);
    Lexer::ExpectTokenString(lex, "}");
    Lexer::ReadToken(lex, &token);
    if ( !idStr::Icmp(token.data, "Bounds") )
    {
      min = Lexer::ParseFloat(lex, 0);
      min_4 = Lexer::ParseFloat(lex, 0);
      *(float *)&min_8 = Lexer::ParseFloat(lex, 0);
      max.x = Lexer::ParseFloat(lex, 0);
      max.y = Lexer::ParseFloat(lex, 0);
      *(float *)&v47[4] = Lexer::ParseFloat(lex, 0);
      v46 = min;
      v47[1] = min_8;
      *(float *)v47 = min_4;
      v47[2] = LODWORD(max.x);
      v20 = &v46;
      v47[3] = LODWORD(max.y);
      p_y = &this->m_bounds.b[0].y;
      srcVertexBuffera = 2;
      do
      {
        *(p_y - 1) = *v20;
        *p_y = *(float *)((char *)p_y + (char *)&v46 - (char *)this);
        p_y[1] = *(float *)((char *)p_y + (char *)v47 - (char *)this);
        v20 += 3;
        p_y += 3;
        --srcVertexBuffera;
      }
      while ( srcVertexBuffera );
      Lexer::ReadToken(lex, &token);
      v9 = renderModel;
    }
    if ( idStr::Icmp(token.data, "}") )
      Lexer::Error(lex, "couldn't find expected '}'");
    v22 = this->m_silTraceVertexBuffer;
    this->m_renderModel = v9;
    if ( v22 != -1 && this->m_silTraceIndexBuffer != -1 )
    {
      if ( this->m_drawVertexBuffer != -1 )
      {
        m_drawIndexBuffer = this->m_drawIndexBuffer;
        if ( m_drawIndexBuffer != -1 )
        {
          m_vertexBuffers = v9->m_vertexBuffers;
          v25 = &m_vertexBuffers[v22];
          m_indexBuffers = v9->m_indexBuffers;
          destIndexBuffer = &m_indexBuffers[this->m_silTraceIndexBuffer];
          v27 = &m_vertexBuffers[this->m_drawVertexBuffer];
          srcVertexBufferb = v27;
          srcIndexBuffer = &m_indexBuffers[m_drawIndexBuffer];
          if ( (v25->m_flags & 0x10) != 0 && (v27->m_flags & 0x10) == 0 )
          {
            v28 = 0;
            if ( this->m_numPrimBatches > 0 )
            {
              v29 = 0;
              while ( 1 )
              {
                rvPrimBatch::CopySilTraceVertices(&this->m_primBatches[v29], v25, destIndexBuffer, v27, srcIndexBuffer);
                ++v28;
                ++v29;
                if ( v28 >= this->m_numPrimBatches )
                  break;
                v27 = srcVertexBufferb;
              }
            }
          }
        }
      }
      v30 = this->m_shadowVolVertexBuffer;
      if ( v30 != -1 )
      {
        v31 = this->m_renderModel->m_vertexBuffers;
        v32 = &v31[v30];
        srcVertexBufferc = &v31[this->m_silTraceVertexBuffer];
        if ( (v32->m_flags & 0x10) != 0 )
        {
          v33 = 0;
          if ( this->m_numPrimBatches > 0 )
          {
            v34 = 0;
            do
            {
              rvPrimBatch::CopyShadowVertices(&this->m_primBatches[v34], v32, srcVertexBufferc);
              ++v33;
              ++v34;
            }
            while ( v33 < this->m_numPrimBatches );
          }
        }
      }
    }
  }
  else
  {
    Lexer::Error(lex, "Out of memory");
  }
  LOBYTE(v50) = 0;
  idStr::FreeData(&materialName);
  v50 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: void __thiscall rvMesh::Init(class rvRenderModelMD5R &,class idMaterial const *,int,class rvBlend4DrawVert *,int,int *,int,struct silEdge_t *,int,int *,int,int,int,int,int)
void __thiscall rvMesh::Init(
        rvMesh *this,
        rvRenderModelMD5R *renderModel,
        const idMaterial *material,
        int numTransforms,
        rvBlend4DrawVert *drawVertArray,
        int numDrawVerts,
        int *drawIndices,
        int numIndices,
        silEdge_t *silEdges,
        int numSilEdges,
        int *silRemap,
        __int16 silTraceVB,
        __int16 drawVB,
        __int16 shadowVB,
        __int16 silTraceIB,
        __int16 drawIB)
{
  bool v17; // zf
  rvPrimBatch *m_primBatches; // eax
  int *p_m_shadowCapPlaneBits; // edi
  int v20; // eax
  unsigned int v21; // edi
  int v22; // eax
  void *v23; // esp
  int v24; // eax
  void *v25; // esp
  int v26; // eax
  void *v27; // esp
  int v28; // eax
  void *v29; // esp
  int v30; // eax
  void *v31; // esp
  int v32; // eax
  void *v33; // esp
  int v34; // eax
  void *v35; // esp
  int v36; // eax
  void *v37; // esp
  int v38; // edi
  int v39; // ebx
  rvBlend4DrawVert *v40; // ecx
  int v41; // edx
  int v42; // edi
  int v43; // ebx
  rvBlend4DrawVert *v44; // ecx
  int v45; // edi
  int v46; // ebx
  rvBlend4DrawVert *v47; // ecx
  int v48; // edx
  rvMesh *v49; // ebx
  _DWORD *v50; // eax
  rvPrimBatch *v51; // ebx
  rvPrimBatch *v52; // eax
  unsigned int v53; // edx
  int *v54; // edi
  char v55; // cl
  int *v56; // edx
  int v57; // ecx
  int v58; // edi
  int *v59; // eax
  int v60; // edi
  int *v61; // edx
  unsigned int v62; // ecx
  int v63; // eax
  int v64; // eax
  int v65; // edi
  int v66; // ebx
  rvBlend4DrawVert *v67; // ecx
  int v68; // edi
  rvMesh *v69; // ebx
  int i; // eax
  __int16 m_silTraceVertexBuffer; // ax
  rvRenderModelMD5R *m_renderModel; // edx
  __int16 m_silTraceIndexBuffer; // cx
  int v74; // ebx
  rvVertexBuffer *v75; // ecx
  rvIndexBuffer *v76; // ebx
  rvPrimBatch *v77; // ecx
  rvMesh *v78; // ecx
  __int16 m_drawVertexBuffer; // ax
  rvRenderModelMD5R *v80; // edx
  __int16 m_drawIndexBuffer; // bx
  rvVertexBuffer *v82; // ecx
  int v83; // eax
  unsigned int m_numVerticesWritten; // ebx
  rvPrimBatch *v85; // ecx
  int v86; // edx
  __int16 m_shadowVolVertexBuffer; // ax
  rvRenderModelMD5R *v88; // edx
  rvVertexBuffer *m_vertexBuffers; // edx
  int v90; // edi
  rvPrimBatch *v91; // eax
  int m_vertexCount; // edx
  int m_numSilEdgesAdded; // ecx
  bool *v94; // edi
  int *v95; // ecx
  rvRenderModelMD5R *v96; // edx
  int v97; // eax
  silEdge_t *v98; // ebx
  rvPrimBatch *v99; // eax
  int v100; // edx
  int v101[3]; // [esp+0h] [ebp-48h] BYREF
  bool *silEdgeAdded; // [esp+Ch] [ebp-3Ch]
  int silEdgeStart; // [esp+10h] [ebp-38h]
  int i1; // [esp+14h] [ebp-34h]
  unsigned int v105; // [esp+18h] [ebp-30h]
  unsigned int *drawVertexMapNewToOld; // [esp+1Ch] [ebp-2Ch]
  int i0; // [esp+20h] [ebp-28h]
  unsigned int *silVertexMapNewToOld; // [esp+24h] [ebp-24h]
  int *endIndex; // [esp+28h] [ebp-20h]
  int numBatchDrawVerts; // [esp+2Ch] [ebp-1Ch]
  unsigned int *drawVertexMapOldToNew; // [esp+30h] [ebp-18h]
  int *primBatchStart; // [esp+34h] [ebp-14h]
  rvMesh *v113; // [esp+38h] [ebp-10h]
  int v114; // [esp+44h] [ebp-4h]
  int transformPaletteSize; // [esp+54h] [ebp+Ch]
  int transformPaletteSizea; // [esp+54h] [ebp+Ch]
  int transformPaletteSizec; // [esp+54h] [ebp+Ch]
  int transformPaletteSized; // [esp+54h] [ebp+Ch]
  bool *transformPaletteSizeb; // [esp+54h] [ebp+Ch]
  int numPrimBatches; // [esp+60h] [ebp+18h]
  int numPrimBatchesa; // [esp+60h] [ebp+18h]
  int numIndicesa; // [esp+68h] [ebp+20h]
  int silTraceVertexStart; // [esp+78h] [ebp+30h]
  int silTraceVertexStarta; // [esp+78h] [ebp+30h]
  int silTraceVertexStartb; // [esp+78h] [ebp+30h]
  int silTraceVertexStartd; // [esp+78h] [ebp+30h]
  rvIndexBuffer *silTraceVertexStarte; // [esp+78h] [ebp+30h]
  int silTraceVertexStartc; // [esp+78h] [ebp+30h]
  int *numBatchSilVerts; // [esp+7Ch] [ebp+34h]
  int numBatchSilVertsa; // [esp+7Ch] [ebp+34h]
  int numBatchSilVertsb; // [esp+7Ch] [ebp+34h]
  int i3; // [esp+84h] [ebp+3Ch]
  int i3a; // [esp+84h] [ebp+3Ch]
  int i3b; // [esp+84h] [ebp+3Ch]
  int i3c; // [esp+84h] [ebp+3Ch]
  int i3d; // [esp+84h] [ebp+3Ch]

  v17 = this->m_renderModel == 0;
  v113 = this;
  if ( !v17 )
  {
    m_primBatches = this->m_primBatches;
    if ( m_primBatches )
    {
      p_m_shadowCapPlaneBits = &m_primBatches[-1].m_shadowCapPlaneBits;
      `eh vector destructor iterator'(
        m_primBatches,
        0x48u,
        m_primBatches[-1].m_shadowCapPlaneBits,
        (void (__thiscall *)(void *))rvPrimBatch::~rvPrimBatch);
      Memory::Free(p_m_shadowCapPlaneBits);
    }
    rvMesh::ResetValues(this);
  }
  this->m_material = material;
  v20 = numTransforms;
  this->m_renderModel = renderModel;
  if ( numTransforms < 1 )
  {
    v20 = 1;
    numTransforms = 1;
  }
  v21 = 4 * v20;
  v22 = 4 * v20 + 7;
  this->m_silTraceVertexBuffer = silTraceVB;
  LOBYTE(v22) = v22 & 0xFC;
  this->m_silTraceIndexBuffer = silTraceIB;
  this->m_drawVertexBuffer = drawVB;
  this->m_drawIndexBuffer = drawIB;
  this->m_shadowVolVertexBuffer = shadowVB;
  this->m_shadowVolIndexBuffer = -1;
  v23 = alloca(v22);
  v24 = 4 * numDrawVerts + 3;
  LOBYTE(v24) = v24 & 0xFC;
  primBatchStart = v101;
  v105 = 4 * numDrawVerts;
  v25 = alloca(v24);
  v26 = 4 * numDrawVerts + 3;
  LOBYTE(v26) = (4 * numDrawVerts + 3) & 0xFC;
  drawVertexMapOldToNew = (unsigned int *)v101;
  v27 = alloca(v26);
  v28 = 4 * numDrawVerts + 3;
  LOBYTE(v28) = (4 * numDrawVerts + 3) & 0xFC;
  drawVertexMapNewToOld = (unsigned int *)v101;
  v29 = alloca(v28);
  v30 = 4 * numDrawVerts + 3;
  LOBYTE(v30) = (4 * numDrawVerts + 3) & 0xFC;
  v31 = alloca(v30);
  v32 = v21 + 3;
  LOBYTE(v32) = (v21 + 3) & 0xFC;
  silVertexMapNewToOld = (unsigned int *)v101;
  v33 = alloca(v32);
  v34 = v21 + 3;
  LOBYTE(v34) = (v21 + 3) & 0xFC;
  v35 = alloca(v34);
  memset(v101, 0, v21);
  v36 = numSilEdges + 3;
  LOBYTE(v36) = (numSilEdges + 3) & 0xFC;
  v37 = alloca(v36);
  silEdgeAdded = (bool *)v101;
  memset(v101, 0, numSilEdges);
  v101[0] = 0;
  numPrimBatches = 1;
  transformPaletteSize = 0;
  endIndex = &drawIndices[numIndices];
  if ( drawIndices < endIndex )
  {
    numBatchSilVerts = drawIndices + 2;
    i0 = -8 - (_DWORD)drawIndices;
    do
    {
      v38 = drawVertArray[*(numBatchSilVerts - 2)].blendIndex[0];
      v39 = drawVertArray[*(numBatchSilVerts - 2)].blendIndex[1];
      v40 = &drawVertArray[*(numBatchSilVerts - 2)];
      v41 = 0;
      silTraceVertexStart = v40->blendIndex[2];
      i3 = v40->blendIndex[3];
      if ( !v101[v38] && 0.0 != v40->blendWeight[0] )
      {
        v101[v38] = 1;
        v41 = 1;
      }
      if ( !v101[v39] && v40->blendWeight[1] > 0.0 )
      {
        v101[v39] = 1;
        ++v41;
      }
      if ( !v101[silTraceVertexStart] && v40->blendWeight[2] > 0.0 )
      {
        v101[silTraceVertexStart] = 1;
        ++v41;
      }
      if ( !v101[i3] && v40->blendWeight[3] > 0.0 )
      {
        v101[i3] = 1;
        ++v41;
      }
      v42 = drawVertArray[*(numBatchSilVerts - 1)].blendIndex[0];
      v43 = drawVertArray[*(numBatchSilVerts - 1)].blendIndex[1];
      v44 = &drawVertArray[*(numBatchSilVerts - 1)];
      silTraceVertexStarta = v44->blendIndex[2];
      i3a = v44->blendIndex[3];
      if ( !v101[v42] && 0.0 != v44->blendWeight[0] )
      {
        v101[v42] = 1;
        ++v41;
      }
      if ( !v101[v43] && v44->blendWeight[1] > 0.0 )
      {
        v101[v43] = 1;
        ++v41;
      }
      if ( !v101[silTraceVertexStarta] && v44->blendWeight[2] > 0.0 )
      {
        v101[silTraceVertexStarta] = 1;
        ++v41;
      }
      if ( !v101[i3a] && v44->blendWeight[3] > 0.0 )
      {
        v101[i3a] = 1;
        ++v41;
      }
      v45 = drawVertArray[*numBatchSilVerts].blendIndex[0];
      v46 = drawVertArray[*numBatchSilVerts].blendIndex[1];
      v47 = &drawVertArray[*numBatchSilVerts];
      silTraceVertexStartb = v47->blendIndex[2];
      i3b = v47->blendIndex[3];
      if ( !v101[v45] && 0.0 != v47->blendWeight[0] )
      {
        v101[v45] = 1;
        ++v41;
      }
      if ( !v101[v46] && v47->blendWeight[1] > 0.0 )
      {
        v101[v46] = 1;
        ++v41;
      }
      if ( !v101[silTraceVertexStartb] && v47->blendWeight[2] > 0.0 )
      {
        v101[silTraceVertexStartb] = 1;
        ++v41;
      }
      if ( !v101[i3b] && v47->blendWeight[3] > 0.0 )
      {
        v101[i3b] = 1;
        ++v41;
      }
      v48 = transformPaletteSize + v41;
      if ( v48 <= 25 )
      {
        numBatchSilVerts += 3;
        transformPaletteSize = v48;
      }
      else
      {
        primBatchStart[numPrimBatches++] = ((int)numBatchSilVerts + i0) >> 2;
        memset(v101, 0, 4 * ((unsigned int)(4 * numTransforms) >> 2));
        transformPaletteSize = 0;
      }
    }
    while ( numBatchSilVerts - 2 < endIndex );
  }
  v49 = v113;
  primBatchStart[numPrimBatches] = numIndices;
  v49->m_numPrimBatches = numPrimBatches;
  v50 = Memory::Allocate(72 * (__int16)numPrimBatches + 4);
  v114 = 0;
  if ( v50 )
  {
    v51 = (rvPrimBatch *)(v50 + 1);
    *v50 = (__int16)numPrimBatches;
    `eh vector constructor iterator'(
      v50 + 1,
      0x48u,
      (__int16)numPrimBatches,
      (void (__thiscall *)(void *))rvPrimBatch::rvPrimBatch,
      (void (__thiscall *)(void *))rvPrimBatch::~rvPrimBatch);
    v52 = v51;
    v49 = v113;
  }
  else
  {
    v52 = 0;
  }
  v114 = -1;
  v49->m_primBatches = v52;
  if ( !v52 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(common.type, "Out of memory");
  numPrimBatchesa = 0;
  if ( v49->m_numPrimBatches > 0 )
  {
    numIndicesa = 0;
    do
    {
      transformPaletteSizea = 0;
      numBatchDrawVerts = 0;
      numBatchSilVertsa = 0;
      memset(v101, 0xFFu, 4 * ((unsigned int)(4 * numTransforms) >> 2));
      v53 = v105;
      memset(drawVertexMapOldToNew, 0xFFu, v105);
      memset(v101, 0xFFu, 4 * (v53 >> 2));
      v54 = &v101[v53 >> 2];
      v55 = v53;
      v56 = primBatchStart;
      memset(v54, -1, v55 & 3);
      v57 = v56[numPrimBatchesa];
      v58 = v56[numPrimBatchesa + 1];
      v59 = &drawIndices[v58];
      v60 = v58 - v57;
      v61 = &drawIndices[v57];
      silEdgeStart = v60;
      for ( endIndex = v59; v61 < v59; ++v61 )
      {
        v62 = *v61;
        if ( drawVertexMapOldToNew[v62] == -1 )
        {
          v63 = silRemap[v62];
          if ( v101[v63] == -1 )
          {
            v101[v63] = numBatchSilVertsa;
            silVertexMapNewToOld[numBatchSilVertsa++] = v63;
          }
          v101[*v61] = v101[v63];
          v64 = numBatchDrawVerts;
          drawVertexMapOldToNew[*v61] = numBatchDrawVerts;
          drawVertexMapNewToOld[v64] = *v61;
          numBatchDrawVerts = v64 + 1;
          v65 = drawVertArray[*v61].blendIndex[1];
          v66 = drawVertArray[*v61].blendIndex[2];
          v67 = &drawVertArray[*v61];
          i0 = v67->blendIndex[0];
          i3c = v67->blendIndex[3];
          v17 = v101[i0] == -1;
          i1 = v65;
          if ( v17 && 0.0 != v67->blendWeight[0] )
          {
            v68 = i0;
            v101[transformPaletteSizea] = i0;
            v101[v68] = transformPaletteSizea;
            v65 = i1;
            ++transformPaletteSizea;
          }
          if ( v101[v65] == -1 && v67->blendWeight[1] > 0.0 )
          {
            v101[transformPaletteSizea] = v65;
            v101[v65] = transformPaletteSizea++;
          }
          if ( v101[v66] == -1 && v67->blendWeight[2] > 0.0 )
          {
            v101[transformPaletteSizea] = v66;
            v101[v66] = transformPaletteSizea++;
          }
          if ( v101[i3c] == -1 && v67->blendWeight[3] > 0.0 )
          {
            v101[transformPaletteSizea] = i3c;
            v101[i3c] = transformPaletteSizea++;
          }
          v59 = endIndex;
          v60 = silEdgeStart;
        }
      }
      v69 = v113;
      rvPrimBatch::Init(&v113->m_primBatches[numIndicesa], v101, transformPaletteSizea);
      for ( i = 0; i < numTransforms; ++i )
      {
        if ( v101[i] == -1 )
          v101[i] = 0;
      }
      m_silTraceVertexBuffer = v69->m_silTraceVertexBuffer;
      if ( m_silTraceVertexBuffer >= 0 )
      {
        m_renderModel = v113->m_renderModel;
        if ( m_silTraceVertexBuffer < m_renderModel->m_numVertexBuffers )
        {
          m_silTraceIndexBuffer = v113->m_silTraceIndexBuffer;
          if ( m_silTraceIndexBuffer >= 0 )
          {
            v74 = m_silTraceIndexBuffer;
            if ( m_silTraceIndexBuffer < m_renderModel->m_numIndexBuffers )
            {
              v75 = &m_renderModel->m_vertexBuffers[m_silTraceVertexBuffer];
              v76 = &m_renderModel->m_indexBuffers[v74];
              transformPaletteSizec = v76->m_numIndicesWritten;
              silTraceVertexStartd = v75->m_numVerticesWritten;
              rvVertexBuffer::CopyRemappedData(
                v75,
                silTraceVertexStartd,
                numBatchSilVertsa,
                silVertexMapNewToOld,
                (unsigned int *)v101,
                drawVertArray,
                1);
              rvIndexBuffer::CopyRemappedData(
                v76,
                transformPaletteSizec,
                v60,
                (unsigned int *)v101,
                &drawIndices[primBatchStart[numPrimBatchesa]],
                0);
              v77 = &v113->m_primBatches[numIndicesa];
              v77->m_silTraceGeoSpec.m_vertexCount = numBatchSilVertsa;
              v77->m_silTraceGeoSpec.m_vertexStart = silTraceVertexStartd;
              v77->m_silTraceGeoSpec.m_indexStart = transformPaletteSizec;
              v77->m_silTraceGeoSpec.m_primitiveCount = v60 / 3;
            }
          }
        }
      }
      v78 = v113;
      m_drawVertexBuffer = v113->m_drawVertexBuffer;
      if ( m_drawVertexBuffer >= 0 )
      {
        v80 = v113->m_renderModel;
        if ( m_drawVertexBuffer < v80->m_numVertexBuffers )
        {
          m_drawIndexBuffer = v113->m_drawIndexBuffer;
          if ( m_drawIndexBuffer >= 0 && m_drawIndexBuffer < v80->m_numIndexBuffers )
          {
            v82 = &v80->m_vertexBuffers[m_drawVertexBuffer];
            v83 = m_drawIndexBuffer;
            m_numVerticesWritten = v82->m_numVerticesWritten;
            silTraceVertexStarte = &v80->m_indexBuffers[v83];
            transformPaletteSized = silTraceVertexStarte->m_numIndicesWritten;
            rvVertexBuffer::CopyRemappedData(
              v82,
              m_numVerticesWritten,
              numBatchDrawVerts,
              drawVertexMapNewToOld,
              (unsigned int *)v101,
              drawVertArray,
              0);
            rvIndexBuffer::CopyRemappedData(
              silTraceVertexStarte,
              transformPaletteSized,
              v60,
              drawVertexMapOldToNew,
              &drawIndices[primBatchStart[numPrimBatchesa]],
              m_numVerticesWritten);
            v85 = &v113->m_primBatches[numIndicesa];
            v86 = numBatchDrawVerts;
            v85->m_drawGeoSpec.m_indexStart = transformPaletteSized;
            v85->m_drawGeoSpec.m_vertexCount = v86;
            v85->m_drawGeoSpec.m_vertexStart = m_numVerticesWritten;
            v85->m_drawGeoSpec.m_primitiveCount = v60 / 3;
            v78 = v113;
          }
        }
      }
      m_shadowVolVertexBuffer = v78->m_shadowVolVertexBuffer;
      if ( m_shadowVolVertexBuffer >= 0 )
      {
        v88 = v78->m_renderModel;
        if ( m_shadowVolVertexBuffer < v88->m_numVertexBuffers )
        {
          m_vertexBuffers = v88->m_vertexBuffers;
          v90 = m_vertexBuffers[m_shadowVolVertexBuffer].m_numVerticesWritten;
          rvVertexBuffer::CopyRemappedShadowVolData(
            &m_vertexBuffers[m_shadowVolVertexBuffer],
            v90,
            numBatchSilVertsa,
            silVertexMapNewToOld,
            (unsigned int *)v101,
            drawVertArray);
          v78 = v113;
          v91 = &v113->m_primBatches[numIndicesa];
          m_vertexCount = v91->m_silTraceGeoSpec.m_vertexCount;
          v91->m_shadowVolGeoSpec.m_vertexStart = v90;
          v91->m_shadowVolGeoSpec.m_vertexCount = 2 * m_vertexCount;
        }
      }
      if ( numSilEdges )
      {
        m_numSilEdgesAdded = renderModel->m_numSilEdgesAdded;
        v94 = silEdgeAdded;
        silEdgeStart = m_numSilEdgesAdded;
        transformPaletteSizeb = silEdgeAdded;
        if ( silEdges >= &silEdges[numSilEdges] )
        {
          v96 = renderModel;
        }
        else
        {
          v95 = &silEdges->v1;
          v96 = renderModel;
          silTraceVertexStartc = ((unsigned int)(16 * numSilEdges - 1) >> 4) + 1;
          do
          {
            if ( !*v94 )
            {
              i3d = v101[*v95];
              if ( i3d != -1 )
              {
                numBatchSilVertsb = v101[v95[1]];
                if ( numBatchSilVertsb != -1 )
                {
                  v97 = *(v95 - 1);
                  v98 = &renderModel->m_silEdges[renderModel->m_numSilEdgesAdded];
                  v98->p1 = *(v95 - 2);
                  v94 = transformPaletteSizeb;
                  v98->p2 = v97;
                  v98->v1 = i3d;
                  v98->v2 = numBatchSilVertsb;
                  ++renderModel->m_numSilEdgesAdded;
                  *transformPaletteSizeb = 1;
                }
              }
            }
            ++v94;
            v95 += 4;
            v17 = silTraceVertexStartc-- == 1;
            transformPaletteSizeb = v94;
          }
          while ( !v17 );
          m_numSilEdgesAdded = silEdgeStart;
        }
        v99 = &v113->m_primBatches[numIndicesa];
        v100 = v96->m_numSilEdgesAdded - m_numSilEdgesAdded;
        v99->m_silEdgeStart = m_numSilEdgesAdded;
        v78 = v113;
        v99->m_silEdgeCount = v100;
      }
      ++numIndicesa;
      ++numPrimBatchesa;
    }
    while ( numPrimBatchesa < v78->m_numPrimBatches );
  }
  rvMesh::CalcGeometryProfile(v113);
}
