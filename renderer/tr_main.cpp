
// FUNC: public: void __thiscall idScreenRect::Clear(void)
void __thiscall idScreenRect::Clear(idScreenRect *this)
{
  this->y1 = 32000;
  this->x1 = 32000;
  this->y2 = -32000;
  this->x2 = -32000;
  this->zmin = 0.0;
  this->zmax = 1.0;
}

// FUNC: public: void __thiscall idScreenRect::Expand(void)
void __thiscall idScreenRect::Expand(idScreenRect *this)
{
  --this->x1;
  --this->y1;
  ++this->x2;
  ++this->y2;
}

// FUNC: public: void __thiscall idScreenRect::Intersect(class idScreenRect const &)
void __thiscall idScreenRect::Intersect(idScreenRect *this, const idScreenRect *rect)
{
  __int16 x2; // dx
  __int16 y1; // dx
  __int16 y2; // ax

  if ( rect->x1 > this->x1 )
    this->x1 = rect->x1;
  x2 = rect->x2;
  if ( x2 < this->x2 )
    this->x2 = x2;
  y1 = rect->y1;
  if ( y1 > this->y1 )
    this->y1 = y1;
  y2 = rect->y2;
  if ( y2 < this->y2 )
    this->y2 = y2;
}

// FUNC: public: void __thiscall idScreenRect::Union(class idScreenRect const &)
void __thiscall idScreenRect::Union(idScreenRect *this, const idScreenRect *rect)
{
  __int16 x2; // dx
  __int16 y1; // dx
  __int16 y2; // ax

  if ( rect->x1 < this->x1 )
    this->x1 = rect->x1;
  x2 = rect->x2;
  if ( x2 > this->x2 )
    this->x2 = x2;
  y1 = rect->y1;
  if ( y1 < this->y1 )
    this->y1 = y1;
  y2 = rect->y2;
  if ( y2 > this->y2 )
    this->y2 = y2;
}

// FUNC: public: bool __thiscall idScreenRect::Equals(class idScreenRect const &)const
BOOL __thiscall idScreenRect::Equals(idScreenRect *this, const idScreenRect *rect)
{
  return this->x1 == rect->x1 && this->x2 == rect->x2 && this->y1 == rect->y1 && this->y2 == rect->y2;
}

// FUNC: public: bool __thiscall idScreenRect::IsEmpty(void)const
BOOL __thiscall idScreenRect::IsEmpty(idScreenRect *this)
{
  return this->x1 > this->x2 || this->y1 > this->y2;
}

// FUNC: void __cdecl R_ShowColoredScreenRect(class idScreenRect const &,int)
void __cdecl R_ShowColoredScreenRect(const idScreenRect *rect, char colorIndex)
{
  if ( rect->x1 <= rect->x2 && rect->y1 <= rect->y2 )
  {
    if ( (_S3_1 & 1) == 0 )
    {
      _S3_1 |= 1u;
      colors_3[0] = colorRed;
      xmmword_110DEC48 = (__int128)colorGreen;
      xmmword_110DEC58 = (__int128)colorBlue;
      xmmword_110DEC68 = (__int128)colorYellow;
      xmmword_110DEC78 = (__int128)colorMagenta;
      xmmword_110DEC88 = (__int128)colorCyan;
      xmmword_110DEC98 = (__int128)colorWhite;
      xmmword_110DECA8 = (__int128)colorPurple;
    }
    idRenderWorldLocal::DebugScreenRect(tr.viewDef->renderWorld, &colors_3[colorIndex & 7], rect, tr.viewDef, 0);
  }
}

// FUNC: void __cdecl R_ShutdownFrameData(void)
void __cdecl R_ShutdownFrameData()
{
  frameData_t *v0; // edi
  frameMemoryBlock_s *memory; // eax
  frameMemoryBlock_s *next; // esi

  v0 = frameData[0];
  if ( frameData[0] )
  {
    R_FreeDeferredTriSurfs(frameData[0]);
    memory = v0->memory;
    if ( v0->memory )
    {
      do
      {
        next = memory->next;
        Mem_Free16(memory);
        memory = next;
      }
      while ( next );
    }
    Mem_Free(v0);
    frameData[0] = 0;
  }
}

// FUNC: void __cdecl R_InitFrameData(void)
void __cdecl R_InitFrameData()
{
  frameData_t *v0; // edi
  frameMemoryBlock_s *v1; // esi

  R_ShutdownFrameData();
  tr.smpFrame = 0;
  v0 = (frameData_t *)Mem_ClearedAlloc(256, 0x10u);
  frameData[0] = v0;
  v1 = (frameMemoryBlock_s *)Mem_Alloc16(1049620, 0x10u);
  if ( !v1 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "R_InitFrameData: Mem_Alloc16() failed");
  v1->size = 1049600;
  v1->used = 0;
  v1->next = 0;
  v0->memory = v1;
  v0->memoryHighwater = 0;
  renderSystem->ToggleSmpFrame(renderSystem);
}

// FUNC: int __cdecl R_CountFrameData(void)
int __cdecl R_CountFrameData()
{
  frameData_t *v0; // edx
  frameMemoryBlock_s *memory; // ecx
  int result; // eax

  v0 = frameData[tr.smpFrame];
  memory = v0->memory;
  for ( result = 0; memory; memory = memory->next )
  {
    result += memory->used;
    if ( memory == v0->alloc )
      break;
  }
  if ( result > v0->memoryHighwater )
    v0->memoryHighwater = result;
  return result;
}

// FUNC: void * __cdecl R_StaticAlloc(int)
void *__cdecl R_StaticAlloc(int bytes)
{
  void *v1; // edi

  ++tr.pc.c_alloc;
  tr.staticAllocCount += bytes;
  v1 = Mem_Alloc16(bytes, 0x10u);
  if ( !v1 && bytes )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "R_StaticAlloc failed on %i bytes",
      bytes);
  return v1;
}

// FUNC: void * __cdecl R_ClearedStaticAlloc(int)
void *__cdecl R_ClearedStaticAlloc(int bytes)
{
  void *v1; // edi

  ++tr.pc.c_alloc;
  tr.staticAllocCount += bytes;
  v1 = Mem_Alloc16(bytes, 0x10u);
  if ( !v1 && bytes )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "R_StaticAlloc failed on %i bytes",
      bytes);
  SIMDProcessor->Memset(SIMDProcessor, v1, 0, bytes);
  return v1;
}

// FUNC: void __cdecl R_StaticFree(void *)
void __cdecl R_StaticFree(void *data)
{
  ++tr.pc.c_free;
  Mem_Free16(data);
}

// FUNC: void * __cdecl R_FrameAlloc(int)
unsigned __int8 *__cdecl R_FrameAlloc(int bytes)
{
  frameData_t *v1; // ebx
  frameMemoryBlock_s *alloc; // ecx
  int used; // edx
  signed int v4; // edi
  unsigned __int8 *result; // eax
  frameMemoryBlock_s *next; // esi

  v1 = frameData[tr.smpFrame];
  alloc = v1->alloc;
  used = alloc->used;
  v4 = (bytes + 16) & 0xFFFFFFF0;
  if ( alloc->size - used < v4 )
  {
    next = alloc->next;
    if ( !alloc->next )
    {
      next = (frameMemoryBlock_s *)Mem_Alloc16(1049620, 0x10u);
      if ( !next )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
          common.type,
          "R_FrameAlloc: Mem_Alloc16() failed");
      next->size = 1049600;
      next->used = 0;
      next->next = 0;
      v1->alloc->next = next;
    }
    if ( v4 > next->size )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
        common.type,
        "R_FrameAlloc of %i exceeded MEMORY_BLOCK_SIZE",
        v4);
    v1->alloc = next;
    next->used = v4;
    return next->base;
  }
  else
  {
    result = &alloc->base[used];
    alloc->used = v4 + used;
  }
  return result;
}

// FUNC: void * __cdecl R_ClearedFrameAlloc(int)
unsigned __int8 *__cdecl R_ClearedFrameAlloc(int bytes)
{
  unsigned __int8 *v1; // esi

  v1 = R_FrameAlloc(bytes);
  SIMDProcessor->Memset(SIMDProcessor, v1, 0, bytes);
  return v1;
}

// FUNC: void __cdecl R_TransformEyeZToWin(float,float const *,float &)
void __cdecl R_TransformEyeZToWin(float src_z, const float *projectionMatrix, float *dst_z)
{
  double v3; // st6

  v3 = src_z * projectionMatrix[11] + projectionMatrix[15];
  if ( v3 > 0.0 )
    *dst_z = ((src_z * projectionMatrix[10] + projectionMatrix[14]) / v3 + 1.0) * 0.5;
  else
    *dst_z = 0.0;
}

// FUNC: void __cdecl myGlMultMatrix(float const *,float const *,float *)
void __cdecl myGlMultMatrix(const float *a, const float *b, float *out)
{
  *out = *a * *b + b[8] * a[2] + a[1] * b[4] + a[3] * b[12];
  out[1] = b[9] * a[2] + *a * b[1] + a[1] * b[5] + b[13] * a[3];
  out[2] = *a * b[2] + b[10] * a[2] + a[1] * b[6] + b[14] * a[3];
  out[3] = a[1] * b[7] + a[3] * b[15] + b[3] * *a + b[11] * a[2];
  out[4] = a[5] * b[4] + b[8] * a[6] + a[7] * b[12] + a[4] * *b;
  out[5] = a[4] * b[1] + b[5] * a[5] + b[9] * a[6] + b[13] * a[7];
  out[6] = a[5] * b[6] + b[10] * a[6] + b[14] * a[7] + a[4] * b[2];
  out[7] = a[4] * b[3] + a[7] * b[15] + a[6] * b[11] + a[5] * b[7];
  out[8] = a[9] * b[4] + b[8] * a[10] + a[11] * b[12] + a[8] * *b;
  out[9] = a[8] * b[1] + b[5] * a[9] + b[13] * a[11] + b[9] * a[10];
  out[10] = a[9] * b[6] + b[14] * a[11] + b[10] * a[10] + a[8] * b[2];
  out[11] = a[8] * b[3] + a[11] * b[15] + a[10] * b[11] + a[9] * b[7];
  out[12] = a[13] * b[4] + a[15] * b[12] + a[14] * b[8] + a[12] * *b;
  out[13] = a[14] * b[9] + a[12] * b[1] + b[5] * a[13] + b[13] * a[15];
  out[14] = a[13] * b[6] + b[14] * a[15] + a[14] * b[10] + a[12] * b[2];
  out[15] = a[14] * b[11] + a[12] * b[3] + a[15] * b[15] + a[13] * b[7];
}

// FUNC: void __cdecl R_TransposeGLMatrix(float const * const,float * const)
void __cdecl R_TransposeGLMatrix(const float *in, float *out)
{
  const float *v2; // ecx
  float *v3; // eax
  int v4; // edx

  v2 = in + 8;
  v3 = out + 2;
  v4 = 4;
  do
  {
    *(v3 - 2) = *(v2 - 8);
    *(v3 - 1) = *(v2 - 4);
    *v3 = *v2;
    v3[1] = v2[4];
    v3 += 4;
    ++v2;
    --v4;
  }
  while ( v4 );
}

// FUNC: public: void __thiscall idScreenRect::AddPoint(float,float)
void __thiscall idScreenRect::AddPoint(idScreenRect *this, float x, float y)
{
  int v3; // [esp+0h] [ebp-4h]
  int xa; // [esp+8h] [ebp+4h]

  v3 = (int)x;
  xa = (int)y;
  if ( v3 < this->x1 )
    this->x1 = v3;
  if ( v3 > this->x2 )
    this->x2 = v3;
  if ( xa < this->y1 )
    this->y1 = xa;
  if ( xa > this->y2 )
    this->y2 = xa;
}

// FUNC: class idScreenRect __cdecl R_ScreenRectFromViewFrustumBounds(class idBounds const &)
idScreenRect *__cdecl R_ScreenRectFromViewFrustumBounds(idScreenRect *result, const idBounds *bounds)
{
  float *projectionMatrix; // esi
  int v4; // edx
  idScreenRect *v5; // eax
  float src_z; // [esp+0h] [ebp-24h]
  float src_za; // [esp+0h] [ebp-24h]
  idScreenRect screenRect; // [esp+14h] [ebp-10h] BYREF
  float boundsb; // [esp+2Ch] [ebp+8h]
  float boundsc; // [esp+2Ch] [ebp+8h]
  float boundsd; // [esp+2Ch] [ebp+8h]
  float boundsa; // [esp+2Ch] [ebp+8h]

  boundsb = (double)(tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1) * (1.0 - bounds->b[1].y) * 0.5;
  screenRect.x1 = (int)boundsb;
  boundsc = (double)(tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1) * (1.0 - bounds->b[0].y) * 0.5;
  screenRect.x2 = (int)boundsc;
  boundsd = (double)(tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1) * (bounds->b[0].z + 1.0) * 0.5;
  screenRect.y1 = (int)boundsd;
  boundsa = (double)(tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1) * (bounds->b[1].z + 1.0) * 0.5;
  if ( r_useDepthBoundsTest.internalVar->integerValue )
  {
    projectionMatrix = tr.viewDef->projectionMatrix;
    src_z = -bounds->b[0].x;
    R_TransformEyeZToWin(src_z, tr.viewDef->projectionMatrix, &screenRect.zmin);
    src_za = -*(float *)(v4 + 12);
    R_TransformEyeZToWin(src_za, projectionMatrix, &screenRect.zmax);
  }
  v5 = result;
  *(_DWORD *)&result->x1 = *(_DWORD *)&screenRect.x1;
  screenRect.y2 = (int)boundsa;
  *(_DWORD *)&result->x2 = *(_DWORD *)&screenRect.x2;
  result->zmin = screenRect.zmin;
  result->zmax = screenRect.zmax;
  return v5;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::ToggleSmpFrame(void)
void __thiscall idRenderSystemLocal::ToggleSmpFrame(idRenderSystemLocal *this)
{
  frameData_t *v1; // ecx
  frameMemoryBlock_s *memory; // eax
  bool v3; // zf

  if ( !r_lockSurfaces.internalVar->integerValue )
  {
    tr.smpFrame = 0;
    R_FreeDeferredTriSurfs(frameData[0]);
    R_CountFrameData();
    v1 = frameData[tr.smpFrame];
    memory = v1->memory;
    v3 = v1->memory == 0;
    v1->alloc = v1->memory;
    if ( !v3 )
    {
      do
      {
        memory->used = 0;
        memory = memory->next;
      }
      while ( memory );
    }
    R_ClearCommandChain();
  }
}

// FUNC: void __cdecl R_AxisToModelMatrix(class idMat3 const &,class idVec3 const &,float * const)
void __cdecl R_AxisToModelMatrix(const idMat3 *axis, const idVec3 *origin, float *modelMatrix)
{
  *modelMatrix = axis->mat[0].x;
  modelMatrix[4] = axis->mat[1].x;
  modelMatrix[8] = axis->mat[2].x;
  modelMatrix[12] = origin->x;
  modelMatrix[1] = axis->mat[0].y;
  modelMatrix[5] = axis->mat[1].y;
  modelMatrix[9] = axis->mat[2].y;
  modelMatrix[13] = origin->y;
  modelMatrix[2] = axis->mat[0].z;
  modelMatrix[6] = axis->mat[1].z;
  modelMatrix[10] = axis->mat[2].z;
  modelMatrix[14] = origin->z;
  modelMatrix[3] = 0.0;
  modelMatrix[7] = 0.0;
  modelMatrix[11] = 0.0;
  modelMatrix[15] = 1.0;
}

// FUNC: void __cdecl R_LocalPointToGlobal(float const * const,class idVec3 const &,class idVec3 &)
void __cdecl R_LocalPointToGlobal(const float *modelMatrix, const idVec3 *in, idVec3 *out)
{
  out->x = modelMatrix[8] * in->z + modelMatrix[4] * in->y + *modelMatrix * in->x + modelMatrix[12];
  out->y = modelMatrix[1] * in->x + modelMatrix[9] * in->z + modelMatrix[5] * in->y + modelMatrix[13];
  out->z = modelMatrix[2] * in->x + modelMatrix[10] * in->z + modelMatrix[6] * in->y + modelMatrix[14];
}

// FUNC: void __cdecl R_GlobalPointToLocal(float const * const,class idVec3 const &,class idVec3 &)
void __cdecl R_GlobalPointToLocal(const float *modelMatrix, const idVec3 *in, idVec3 *out)
{
  double v3; // st7
  double v4; // st6
  double v5; // st5

  v3 = in->x - modelMatrix[12];
  v4 = in->y - modelMatrix[13];
  v5 = in->z - modelMatrix[14];
  out->x = v5 * modelMatrix[2] + v4 * modelMatrix[1] + v3 * *modelMatrix;
  out->y = v5 * modelMatrix[6] + v4 * modelMatrix[5] + v3 * modelMatrix[4];
  out->z = v5 * modelMatrix[10] + v4 * modelMatrix[9] + v3 * modelMatrix[8];
}

// FUNC: void __cdecl R_GlobalVectorToLocal(float const * const,class idVec3 const &,class idVec3 &)
void __cdecl R_GlobalVectorToLocal(const float *modelMatrix, const idVec3 *in, idVec3 *out)
{
  out->x = modelMatrix[2] * in->z + modelMatrix[1] * in->y + *modelMatrix * in->x;
  out->y = modelMatrix[4] * in->x + modelMatrix[6] * in->z + modelMatrix[5] * in->y;
  out->z = modelMatrix[8] * in->x + modelMatrix[10] * in->z + modelMatrix[9] * in->y;
}

// FUNC: void __cdecl R_LocalPlaneToGlobal(float const * const,class idPlane const &,class idPlane &)
void __cdecl R_LocalPlaneToGlobal(const float *modelMatrix, const idPlane *in, idPlane *out)
{
  double v3; // st7

  out->a = modelMatrix[8] * in->c + modelMatrix[4] * in->b + *modelMatrix * in->a;
  out->b = modelMatrix[1] * in->a + modelMatrix[9] * in->c + modelMatrix[5] * in->b;
  v3 = modelMatrix[2] * in->a + modelMatrix[10] * in->c + modelMatrix[6] * in->b;
  out->c = v3;
  out->d = in->d - modelMatrix[12] * out->a - modelMatrix[13] * out->b - v3 * modelMatrix[14];
}

// FUNC: void __cdecl R_GlobalPlaneToLocal(float const * const,class idPlane const &,class idPlane &)
void __cdecl R_GlobalPlaneToLocal(const float *modelMatrix, const idPlane *in, idPlane *out)
{
  out->a = modelMatrix[2] * in->c + modelMatrix[1] * in->b + *modelMatrix * in->a;
  out->b = modelMatrix[4] * in->a + modelMatrix[6] * in->c + modelMatrix[5] * in->b;
  out->c = modelMatrix[8] * in->a + modelMatrix[10] * in->c + modelMatrix[9] * in->b;
  out->d = modelMatrix[12] * in->a + modelMatrix[14] * in->c + modelMatrix[13] * in->b + in->d;
}

// FUNC: bool __cdecl R_CullLocalBox(class idBounds const &,float const * const,int,class idPlane const *)
char __cdecl R_CullLocalBox(const idBounds *bounds, const float *modelMatrix, int numPlanes, const idPlane *planes)
{
  double v5; // st7
  double v6; // st6
  double v7; // rt0
  double v8; // st6
  int v9; // edx
  float *i; // ecx
  double v11; // st7
  float v12; // [esp+0h] [ebp-34h]
  float v13; // [esp+4h] [ebp-30h]
  float v14; // [esp+8h] [ebp-2Ch]
  float radiusSqr; // [esp+Ch] [ebp-28h]
  float v16; // [esp+10h] [ebp-24h]
  float v17; // [esp+14h] [ebp-20h]
  float v18; // [esp+18h] [ebp-1Ch]
  idVec3 localOrigin; // [esp+1Ch] [ebp-18h] BYREF
  idVec3 worldOrigin; // [esp+28h] [ebp-Ch] BYREF

  if ( !r_useCulling.internalVar->integerValue )
    return 0;
  v5 = bounds->b[1].x + bounds->b[0].x;
  v6 = bounds->b[1].y + bounds->b[0].y;
  localOrigin.z = bounds->b[1].z + bounds->b[0].z;
  v7 = v6;
  worldOrigin.x = v5 * 0.5;
  localOrigin.x = worldOrigin.x;
  v8 = localOrigin.z * 0.5;
  localOrigin.y = v7 * 0.5;
  localOrigin.z = v8;
  v16 = bounds->b[1].x - worldOrigin.x;
  v17 = bounds->b[1].y - v7 * 0.5;
  v18 = bounds->b[1].z - v8;
  R_LocalPointToGlobal(modelMatrix, &localOrigin, &worldOrigin);
  v9 = 0;
  if ( numPlanes <= 0 )
    return 0;
  for ( i = &planes->c; ; i += 4 )
  {
    v11 = worldOrigin.y * *(i - 1) + worldOrigin.z * *i + worldOrigin.x * *(i - 2) + i[1];
    if ( v11 > 0.0 )
    {
      radiusSqr = v18 * v18 + v17 * v17 + v16 * v16;
      if ( v11 * v11 > radiusSqr )
        break;
      v14 = (modelMatrix[1] * *(i - 1) + modelMatrix[2] * *i + *modelMatrix * *(i - 2)) * v16;
      v13 = (modelMatrix[5] * *(i - 1) + modelMatrix[6] * *i + modelMatrix[4] * *(i - 2)) * v17;
      v12 = (modelMatrix[9] * *(i - 1) + modelMatrix[10] * *i + modelMatrix[8] * *(i - 2)) * v18;
      if ( v11
         - (COERCE_FLOAT(LODWORD(v12) & 0x7FFFFFFF)
          + COERCE_FLOAT(LODWORD(v13) & 0x7FFFFFFF)
          + COERCE_FLOAT(LODWORD(v14) & 0x7FFFFFFF)) > 0.0 )
        break;
    }
    if ( ++v9 >= numPlanes )
      return 0;
  }
  return 1;
}

// FUNC: void __cdecl R_TransformModelToClip(class idVec3 const &,float const *,float const *,class idPlane &,class idPlane &)
void __cdecl R_TransformModelToClip(
        const idVec3 *src,
        const float *modelMatrix,
        const float *projectionMatrix,
        idPlane *eye,
        idPlane *dst)
{
  eye->a = modelMatrix[8] * src->z + modelMatrix[4] * src->y + src->x * *modelMatrix + modelMatrix[12];
  eye->b = modelMatrix[1] * src->x + modelMatrix[9] * src->z + modelMatrix[5] * src->y + modelMatrix[13];
  eye->c = modelMatrix[2] * src->x + modelMatrix[10] * src->z + modelMatrix[6] * src->y + modelMatrix[14];
  eye->d = modelMatrix[3] * src->x + modelMatrix[11] * src->z + modelMatrix[7] * src->y + modelMatrix[15];
  dst->a = projectionMatrix[8] * eye->c
         + projectionMatrix[4] * eye->b
         + projectionMatrix[12] * eye->d
         + *projectionMatrix * eye->a;
  dst->b = projectionMatrix[9] * eye->c
         + projectionMatrix[5] * eye->b
         + projectionMatrix[1] * eye->a
         + projectionMatrix[13] * eye->d;
  dst->c = projectionMatrix[10] * eye->c
         + projectionMatrix[6] * eye->b
         + projectionMatrix[2] * eye->a
         + projectionMatrix[14] * eye->d;
  dst->d = projectionMatrix[11] * eye->c
         + projectionMatrix[7] * eye->b
         + projectionMatrix[3] * eye->a
         + projectionMatrix[15] * eye->d;
}

// FUNC: void __cdecl R_GlobalToNormalizedDeviceCoordinates(float *,float *,class idVec3 const &,class idVec3 &)
void __cdecl R_GlobalToNormalizedDeviceCoordinates(
        float *modelViewMatrix,
        float *projectionMatrix,
        const idVec3 *global,
        idVec3 *ndc)
{
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st4
  double v8; // st7
  float clip; // [esp+0h] [ebp-10h]
  float clip_4; // [esp+4h] [ebp-Ch]
  float clip_8; // [esp+8h] [ebp-8h]

  v4 = modelViewMatrix[8] * global->z
     + modelViewMatrix[4] * global->y
     + *modelViewMatrix * global->x
     + modelViewMatrix[12];
  v5 = modelViewMatrix[1] * global->x
     + modelViewMatrix[9] * global->z
     + modelViewMatrix[5] * global->y
     + modelViewMatrix[13];
  v6 = modelViewMatrix[2] * global->x
     + modelViewMatrix[10] * global->z
     + modelViewMatrix[6] * global->y
     + modelViewMatrix[14];
  v7 = modelViewMatrix[3] * global->x
     + modelViewMatrix[11] * global->z
     + modelViewMatrix[7] * global->y
     + modelViewMatrix[15];
  clip = v5 * projectionMatrix[4] + v6 * projectionMatrix[8] + v7 * projectionMatrix[12] + v4 * *projectionMatrix;
  clip_4 = v4 * projectionMatrix[1] + v5 * projectionMatrix[5] + v6 * projectionMatrix[9] + v7 * projectionMatrix[13];
  clip_8 = v4 * projectionMatrix[2] + v5 * projectionMatrix[6] + v6 * projectionMatrix[10] + v7 * projectionMatrix[14];
  v8 = v4 * projectionMatrix[3] + v5 * projectionMatrix[7] + v6 * projectionMatrix[11] + v7 * projectionMatrix[15];
  ndc->x = clip * (1.0 / v8);
  ndc->y = 1.0 / v8 * clip_4;
  ndc->z = (clip_8 + v8) / (v8 + v8);
}

// FUNC: void __cdecl R_TransformClipToDevice(class idPlane const &,struct viewDef_s const *,class idVec3 &)
void __cdecl R_TransformClipToDevice(const idPlane *clip, const viewDef_s *view, idVec3 *normalized)
{
  normalized->x = clip->a / clip->d;
  normalized->y = clip->b / clip->d;
  normalized->z = clip->c / clip->d;
}

// FUNC: void __cdecl R_SetViewMatrix(struct renderView_s *,float *,float *)
void __cdecl R_SetViewMatrix(renderView_s *view, float *modelMatrix, float *modelViewMatrix)
{
  double x; // st7
  double y; // st6
  double z; // st5
  float v6; // edx
  float viewerMatrix[16]; // [esp+0h] [ebp-40h] BYREF

  if ( modelMatrix )
  {
    *modelMatrix = 1.0;
    modelMatrix[5] = 1.0;
    modelMatrix[10] = 1.0;
  }
  if ( modelViewMatrix )
  {
    x = view->vieworg.x;
    y = view->vieworg.y;
    viewerMatrix[0] = view->viewaxis.mat[0].x;
    z = view->vieworg.z;
    viewerMatrix[4] = view->viewaxis.mat[0].y;
    viewerMatrix[8] = view->viewaxis.mat[0].z;
    viewerMatrix[1] = view->viewaxis.mat[1].x;
    viewerMatrix[5] = view->viewaxis.mat[1].y;
    viewerMatrix[9] = view->viewaxis.mat[1].z;
    viewerMatrix[2] = view->viewaxis.mat[2].x;
    v6 = view->viewaxis.mat[2].y;
    viewerMatrix[10] = view->viewaxis.mat[2].z;
    viewerMatrix[6] = v6;
    viewerMatrix[12] = -(viewerMatrix[8] * z + y * viewerMatrix[4] + x * viewerMatrix[0]);
    viewerMatrix[3] = 0.0;
    viewerMatrix[7] = 0.0;
    viewerMatrix[11] = 0.0;
    viewerMatrix[15] = 1.0;
    viewerMatrix[13] = -(viewerMatrix[9] * z + y * viewerMatrix[5] + x * viewerMatrix[1]);
    viewerMatrix[14] = -(z * viewerMatrix[10] + y * v6 + x * viewerMatrix[2]);
    myGlMultMatrix(viewerMatrix, s_flipMatrix, modelViewMatrix);
  }
}

// FUNC: void __cdecl R_SetupProjection(float *,float,float,class idScreenRect const &,bool)
void __cdecl R_SetupProjection(
        float *projectionMatrix,
        float fov_x,
        float fov_y,
        const idScreenRect *viewport,
        bool cramZNear)
{
  int seed; // eax
  int v6; // eax
  double floatValue; // st7
  long double v8; // st6
  int v9; // esi
  long double v10; // st6
  long double v11; // st4
  long double v12; // st2
  long double v13; // st2
  double v14; // st4
  float jitterx; // [esp+0h] [ebp-8h]
  float jitterxa; // [esp+0h] [ebp-8h]
  float jittery; // [esp+4h] [ebp-4h]
  float jitterya; // [esp+4h] [ebp-4h]
  int fov_ya; // [esp+14h] [ebp+Ch]
  float fov_yb; // [esp+14h] [ebp+Ch]
  float cramZNeara; // [esp+1Ch] [ebp+14h]

  if ( (_S4_29 & 1) != 0 )
  {
    seed = random.seed;
  }
  else
  {
    _S4_29 |= 1u;
    seed = 0;
    random.seed = 0;
  }
  if ( r_jitter.internalVar->integerValue )
  {
    v6 = 69069 * seed + 1;
    random.seed = 69069 * v6 + 1;
    jitterx = (double)(v6 & 0x7FFF) * 0.000030517578;
    jittery = (double)(random.seed & 0x7FFF) * 0.000030517578;
  }
  else
  {
    jittery = 0.0;
    jitterx = 0.0;
  }
  floatValue = r_znear.internalVar->floatValue;
  if ( cramZNear )
    floatValue = floatValue * 0.25;
  v8 = tan(3.1415927 * fov_y * 0.0027777778);
  fov_ya = viewport->x2 - viewport->x1 + 1;
  v9 = viewport->y2 - viewport->y1;
  v10 = v8 * floatValue;
  projectionMatrix[4] = 0.0;
  projectionMatrix[12] = 0.0;
  projectionMatrix[1] = 0.0;
  v11 = tan(3.1415927 * fov_x * 0.0027777778) * floatValue;
  v12 = v11 - -v11;
  cramZNeara = v10 - -v10;
  jitterxa = jitterx * v12 / (double)fov_ya;
  jitterya = cramZNeara * jittery / (double)(v9 + 1);
  fov_yb = floatValue + floatValue;
  v13 = 1.0 / v12;
  *projectionMatrix = fov_yb * v13;
  projectionMatrix[8] = (jitterxa - v11 + v11 + jitterxa) * v13;
  v14 = 1.0 / cramZNeara;
  projectionMatrix[5] = fov_yb * v14;
  projectionMatrix[13] = 0.0;
  projectionMatrix[2] = 0.0;
  projectionMatrix[9] = (jitterya - v10 + v10 + jitterya) * v14;
  projectionMatrix[6] = 0.0;
  projectionMatrix[10] = -0.99900001;
  projectionMatrix[3] = 0.0;
  projectionMatrix[7] = 0.0;
  projectionMatrix[11] = -1.0;
  projectionMatrix[15] = 0.0;
  projectionMatrix[14] = floatValue * -2.0;
}

// FUNC: R_SetupViewFrustum
idFrustum *R_SetupViewFrustum()
{
  double v0; // st7
  double v1; // st7
  float z; // ecx
  float x; // ecx
  double v4; // st6
  float v5; // edx
  idPlane *frustum; // eax
  double v7; // st6
  double v8; // st5
  double v9; // st7
  double v10; // st6
  double v11; // st7
  float v12; // edx
  float v13; // edx
  double v14; // st6
  float v15; // ecx
  double v16; // st6
  idPlane *v17; // eax
  double v18; // st5
  double v19; // st6
  double v20; // st7
  long double v21; // st7
  float v22; // edx
  double v23; // st7
  float v24; // ecx
  float v25; // ecx
  double v26; // st6
  float v27; // edx
  idPlane *v28; // eax
  double v29; // st6
  double v30; // st5
  double v31; // st6
  double v32; // st7
  double v33; // st7
  float y; // edx
  float v35; // ecx
  double v36; // st6
  idPlane *v37; // eax
  double v38; // st6
  double v39; // st5
  double v40; // st7
  double v41; // st6
  viewDef_s *viewDef; // eax
  idPlane *v43; // eax
  double v44; // st7
  double v45; // st6
  double c; // st5
  idPlane *v47; // eax
  double v48; // st7
  double v49; // st6
  double v50; // st5
  idPlane *v51; // eax
  double v52; // st7
  double v53; // st6
  double v54; // st5
  idPlane *v55; // eax
  double v56; // st7
  double v57; // st6
  double v58; // st5
  idPlane *v59; // eax
  double v60; // st7
  double v61; // st6
  double v62; // st5
  double floatValue; // st7
  long double v64; // st6
  long double v65; // st5
  viewDef_s *v66; // ecx
  int y_low; // edx
  idMat3 *p_viewaxis; // eax
  idFrustum *result; // eax
  float xc; // [esp+4h] [ebp-38h] BYREF
  float xs; // [esp+8h] [ebp-34h] BYREF
  float ang; // [esp+Ch] [ebp-30h]
  float *p_xs; // [esp+10h] [ebp-2Ch]
  float dUp; // [esp+14h] [ebp-28h]
  idVec3 v75; // [esp+18h] [ebp-24h]
  float v76; // [esp+28h] [ebp-14h]
  float v77; // [esp+2Ch] [ebp-10h]
  float v78; // [esp+34h] [ebp-8h]
  float v79; // [esp+38h] [ebp-4h]

  v0 = idMath::M_DEG2RAD * tr.viewDef->renderView.fov_x * 0.5;
  dUp = COERCE_FLOAT(&xc);
  p_xs = &xs;
  ang = v0;
  xc = cos(ang);
  xs = sin(ang);
  v75.x = tr.viewDef->renderView.viewaxis.mat[1].x;
  v1 = v75.x * xc;
  z = tr.viewDef->renderView.viewaxis.mat[1].z;
  v75.y = tr.viewDef->renderView.viewaxis.mat[1].y;
  v75.z = z;
  x = tr.viewDef->renderView.viewaxis.mat[0].x;
  v78 = v75.y * xc;
  v75.x = x;
  v4 = v75.z * xc;
  v5 = tr.viewDef->renderView.viewaxis.mat[0].z;
  v75.y = tr.viewDef->renderView.viewaxis.mat[0].y;
  v75.z = v5;
  v79 = v4;
  frustum = tr.viewDef->frustum;
  v7 = x * xs;
  v76 = v75.y * xs;
  v8 = v5 * xs;
  tr.viewDef->frustum[0].d = 0.0;
  v77 = v8;
  v9 = v1 + v7;
  v10 = v76 + v78;
  v79 = v77 + v79;
  frustum->c = v79;
  frustum->a = v9;
  frustum->b = v10;
  v75.x = tr.viewDef->renderView.viewaxis.mat[1].x;
  v11 = v75.x * xc;
  v12 = tr.viewDef->renderView.viewaxis.mat[1].z;
  v75.y = tr.viewDef->renderView.viewaxis.mat[1].y;
  v75.z = v12;
  v13 = tr.viewDef->renderView.viewaxis.mat[0].x;
  v76 = v75.y * xc;
  v75.x = v13;
  v14 = v75.z * xc;
  v15 = tr.viewDef->renderView.viewaxis.mat[0].z;
  v75.y = tr.viewDef->renderView.viewaxis.mat[0].y;
  v75.z = v15;
  v77 = v14;
  v16 = v13 * xs;
  v17 = &tr.viewDef->frustum[1];
  p_xs = &xc;
  v78 = v75.y * xs;
  v18 = v15 * xs;
  tr.viewDef->frustum[1].d = 0.0;
  v79 = v18;
  v79 = v79 - v77;
  v19 = v16 - v11;
  v20 = v78 - v76;
  v17->c = v79;
  v17->a = v19;
  dUp = COERCE_FLOAT(&xs);
  v17->b = v20;
  ang = idMath::M_DEG2RAD * tr.viewDef->renderView.fov_y * 0.5;
  v21 = sin(ang);
  v22 = dUp;
  *p_xs = cos(ang);
  *(float *)LODWORD(v22) = v21;
  v75.x = tr.viewDef->renderView.viewaxis.mat[2].x;
  v23 = v75.x * xc;
  v24 = tr.viewDef->renderView.viewaxis.mat[2].z;
  v75.y = tr.viewDef->renderView.viewaxis.mat[2].y;
  v75.z = v24;
  v25 = tr.viewDef->renderView.viewaxis.mat[0].x;
  v76 = v75.y * xc;
  v75.x = v25;
  v26 = v75.z * xc;
  v27 = tr.viewDef->renderView.viewaxis.mat[0].z;
  v75.y = tr.viewDef->renderView.viewaxis.mat[0].y;
  v75.z = v27;
  v77 = v26;
  v28 = &tr.viewDef->frustum[2];
  v29 = v25 * xs;
  v78 = v75.y * xs;
  v30 = v27 * xs;
  tr.viewDef->frustum[2].d = 0.0;
  v79 = v30;
  v79 = v79 + v77;
  v31 = v23 + v29;
  v32 = v78 + v76;
  v28->c = v79;
  v28->a = v31;
  v28->b = v32;
  v75 = tr.viewDef->renderView.viewaxis.mat[2];
  v33 = v75.x * xc;
  v75.x = tr.viewDef->renderView.viewaxis.mat[0].x;
  y = tr.viewDef->renderView.viewaxis.mat[0].y;
  v76 = v75.y * xc;
  v35 = tr.viewDef->renderView.viewaxis.mat[0].z;
  v75.y = y;
  v36 = v75.z * xc;
  v75.z = v35;
  v37 = &tr.viewDef->frustum[3];
  v77 = v36;
  v38 = v75.x * xs;
  v78 = y * xs;
  v39 = v35 * xs;
  tr.viewDef->frustum[3].d = 0.0;
  v79 = v39;
  v40 = v38 - v33;
  v41 = v78 - v76;
  v79 = v79 - v77;
  v37->c = v79;
  v37->a = v40;
  v37->b = v41;
  viewDef = tr.viewDef;
  tr.viewDef->frustum[4].a = tr.viewDef->renderView.viewaxis.mat[0].x;
  viewDef->frustum[4].b = viewDef->renderView.viewaxis.mat[0].y;
  viewDef->frustum[4].c = viewDef->renderView.viewaxis.mat[0].z;
  viewDef->frustum[4].d = 0.0;
  v43 = tr.viewDef->frustum;
  v44 = -tr.viewDef->frustum[0].a;
  v45 = -tr.viewDef->frustum[0].b;
  c = tr.viewDef->frustum[0].c;
  tr.viewDef->frustum[0].d = 0.0;
  v75.z = -c;
  v43->c = v75.z;
  v43->a = v44;
  v43->b = v45;
  tr.viewDef->frustum[0].d = -(tr.viewDef->frustum[0].c * tr.viewDef->renderView.vieworg.z
                             + tr.viewDef->frustum[0].b * tr.viewDef->renderView.vieworg.y
                             + tr.viewDef->frustum[0].a * tr.viewDef->renderView.vieworg.x);
  v47 = &tr.viewDef->frustum[1];
  v48 = -tr.viewDef->frustum[1].a;
  v49 = -tr.viewDef->frustum[1].b;
  v50 = tr.viewDef->frustum[1].c;
  tr.viewDef->frustum[1].d = 0.0;
  v75.z = -v50;
  v47->c = v75.z;
  v47->a = v48;
  v47->b = v49;
  tr.viewDef->frustum[1].d = -(tr.viewDef->frustum[1].c * tr.viewDef->renderView.vieworg.z
                             + tr.viewDef->frustum[1].b * tr.viewDef->renderView.vieworg.y
                             + tr.viewDef->frustum[1].a * tr.viewDef->renderView.vieworg.x);
  v51 = &tr.viewDef->frustum[2];
  v52 = -tr.viewDef->frustum[2].a;
  v53 = -tr.viewDef->frustum[2].b;
  v54 = tr.viewDef->frustum[2].c;
  tr.viewDef->frustum[2].d = 0.0;
  v75.z = -v54;
  v51->c = v75.z;
  v51->a = v52;
  v51->b = v53;
  tr.viewDef->frustum[2].d = -(tr.viewDef->frustum[2].c * tr.viewDef->renderView.vieworg.z
                             + tr.viewDef->frustum[2].b * tr.viewDef->renderView.vieworg.y
                             + tr.viewDef->frustum[2].a * tr.viewDef->renderView.vieworg.x);
  v55 = &tr.viewDef->frustum[3];
  v56 = -tr.viewDef->frustum[3].a;
  v57 = -tr.viewDef->frustum[3].b;
  v58 = tr.viewDef->frustum[3].c;
  tr.viewDef->frustum[3].d = 0.0;
  v75.z = -v58;
  v55->c = v75.z;
  v55->a = v56;
  v55->b = v57;
  tr.viewDef->frustum[3].d = -(tr.viewDef->frustum[3].c * tr.viewDef->renderView.vieworg.z
                             + tr.viewDef->frustum[3].b * tr.viewDef->renderView.vieworg.y
                             + tr.viewDef->frustum[3].a * tr.viewDef->renderView.vieworg.x);
  v59 = &tr.viewDef->frustum[4];
  v60 = -tr.viewDef->frustum[4].a;
  v61 = -tr.viewDef->frustum[4].b;
  v62 = tr.viewDef->frustum[4].c;
  tr.viewDef->frustum[4].d = 0.0;
  v75.z = -v62;
  v59->c = v75.z;
  v59->a = v60;
  v59->b = v61;
  tr.viewDef->frustum[4].d = -(tr.viewDef->frustum[4].c * tr.viewDef->renderView.vieworg.z
                             + tr.viewDef->frustum[4].b * tr.viewDef->renderView.vieworg.y
                             + tr.viewDef->frustum[4].a * tr.viewDef->renderView.vieworg.x);
  floatValue = r_znear.internalVar->floatValue;
  if ( tr.viewDef->renderView.cramZNear )
    floatValue = floatValue * 0.25;
  v64 = tan(tr.viewDef->renderView.fov_x * 0.5 * idMath::M_DEG2RAD);
  v65 = tr.viewDef->renderView.fov_y * 0.5 * idMath::M_DEG2RAD;
  tr.viewDef->viewFrustum.origin = tr.viewDef->renderView.vieworg;
  v66 = tr.viewDef;
  tr.viewDef->viewFrustum.axis.mat[0].x = tr.viewDef->renderView.viewaxis.mat[0].x;
  y_low = LODWORD(v66->renderView.viewaxis.mat[0].y);
  p_viewaxis = &v66->renderView.viewaxis;
  v66 = (viewDef_s *)((char *)v66 + 572);
  v66->renderView.x = y_low;
  v66->renderView.y = LODWORD(p_viewaxis->mat[0].z);
  *(idVec3 *)&v66->renderView.width = p_viewaxis->mat[1];
  *(idVec3 *)&v66->renderView.fov_y = p_viewaxis->mat[2];
  result = &tr.viewDef->viewFrustum;
  tr.viewDef->viewFrustum.dFar = 262144.0;
  result->invFar = 0.0000038146973;
  dUp = tan(v65) * 262144.0;
  result->dUp = dUp;
  result->dNear = floatValue;
  result->dLeft = v64 * 262144.0;
  return result;
}

// FUNC: R_ConstrainViewFrustum
void R_ConstrainViewFrustum()
{
  viewLight_s *i; // edx
  float *frustumTris; // ecx
  viewEntity_s *j; // edx
  float *entityDef; // ecx
  double floatValue; // st7
  idFrustum *p_viewFrustum; // eax
  double v6; // st6
  idBounds bounds; // [esp+0h] [ebp-18h] BYREF

  bounds.b[1].z = -1.0e30;
  bounds.b[0].z = idMath::INFINITY;
  bounds.b[0].y = idMath::INFINITY;
  bounds.b[0].x = idMath::INFINITY;
  bounds.b[1].y = bounds.b[1].z;
  bounds.b[1].x = bounds.b[1].z;
  for ( i = tr.viewDef->viewLights; i; i = i->next )
  {
    frustumTris = (float *)i->lightDef->frustumTris;
    if ( *frustumTris < (double)bounds.b[0].x )
      bounds.b[0].x = *frustumTris;
    if ( frustumTris[1] < (double)bounds.b[0].y )
      bounds.b[0].y = frustumTris[1];
    if ( frustumTris[2] < (double)bounds.b[0].z )
      bounds.b[0].z = frustumTris[2];
    if ( frustumTris[3] > (double)bounds.b[1].x )
      bounds.b[1].x = frustumTris[3];
    if ( frustumTris[4] > (double)bounds.b[1].y )
      bounds.b[1].y = frustumTris[4];
    if ( frustumTris[5] > (double)bounds.b[1].z )
      bounds.b[1].z = frustumTris[5];
  }
  for ( j = tr.viewDef->viewEntitys; j; j = j->next )
  {
    entityDef = (float *)j->entityDef;
    if ( entityDef )
    {
      if ( entityDef[82] < (double)bounds.b[0].x )
        bounds.b[0].x = entityDef[82];
      if ( entityDef[83] < (double)bounds.b[0].y )
        bounds.b[0].y = entityDef[83];
      if ( entityDef[84] < (double)bounds.b[0].z )
        bounds.b[0].z = entityDef[84];
      if ( entityDef[85] > (double)bounds.b[1].x )
        bounds.b[1].x = entityDef[85];
      if ( entityDef[86] > (double)bounds.b[1].y )
        bounds.b[1].y = entityDef[86];
      if ( entityDef[87] > (double)bounds.b[1].z )
        bounds.b[1].z = entityDef[87];
    }
  }
  idFrustum::ConstrainToBounds(&tr.viewDef->viewFrustum, &bounds);
  if ( r_useFrustumFarDistance.internalVar->floatValue > 0.0 )
  {
    floatValue = r_useFrustumFarDistance.internalVar->floatValue;
    p_viewFrustum = &tr.viewDef->viewFrustum;
    v6 = floatValue / tr.viewDef->viewFrustum.dFar;
    tr.viewDef->viewFrustum.dFar = r_useFrustumFarDistance.internalVar->floatValue;
    p_viewFrustum->dLeft = v6 * p_viewFrustum->dLeft;
    p_viewFrustum->dUp = v6 * p_viewFrustum->dUp;
    p_viewFrustum->invFar = 1.0 / floatValue;
  }
}

// FUNC: void __cdecl R_RenderView(struct viewDef_s *)
void __cdecl R_RenderView(viewDef_s *parms)
{
  viewDef_s *viewDef; // ebx

  if ( parms->renderView.width > 0 && parms->renderView.height > 0 )
  {
    ++tr.viewCount;
    viewDef = tr.viewDef;
    tr.viewDef = parms;
    tr.sortOffset = 0.0;
    memset(&parms->worldSpace, 0, sizeof(parms->worldSpace));
    R_SetViewMatrix(&tr.viewDef->renderView, tr.viewDef->worldSpace.modelMatrix, tr.viewDef->worldSpace.modelViewMatrix);
    R_SetupViewFrustum();
    R_SetupProjection(
      tr.viewDef->projectionMatrix,
      tr.viewDef->renderView.fov_x,
      tr.viewDef->renderView.fov_y,
      &tr.viewDef->viewport,
      tr.viewDef->renderView.cramZNear);
    idRenderWorldLocal::FindViewLightsAndEntities(parms->renderWorld);
    R_ConstrainViewFrustum();
    R_AddLightSurfaces((int)&parms->renderWorld);
    R_AddModelSurfaces();
    R_AddEffectSurfaces();
    R_RemoveUnecessaryViewLights();
    qsort(tr.viewDef->drawSurfs, tr.viewDef->numDrawSurfs, 4u, R_QsortSurfaces);
    if ( !R_GenerateSubViews() || !r_subviewOnly.internalVar->integerValue )
    {
      if ( session->writeDemo )
        idRenderWorldLocal::WriteVisibleDefs(
          parms->renderWorld,
          (int)viewDef,
          (int)&parms->renderWorld,
          (int)parms,
          tr.viewDef);
      R_AddSpecialEffects(parms);
      R_AddDrawViewCmd(parms);
      tr.viewDef = viewDef;
    }
  }
}
