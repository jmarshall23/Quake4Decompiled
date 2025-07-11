
// FUNC: public: virtual void __thiscall idRenderModelStatic::List(void)const
void __usercall idRenderModelStatic::List(idRenderModelStatic *this@<ecx>, int a2@<edi>, int a3@<esi>)
{
  int v4; // ebx
  int v5; // edi
  int i; // ebp
  const modelSurface_s *v7; // eax
  srfTriangles_s *geometry; // ecx
  srfTriangles_s *v9; // ecx
  int v10; // ebp
  const char *v11; // eax
  int v12; // eax
  char v15; // [esp+7h] [ebp-9h]
  int v16; // [esp+8h] [ebp-8h]

  v4 = 0;
  v5 = 0;
  ((void (__thiscall *)(idRenderModelStatic *, int, int))this->Memory)(this, a2, a3);
  HIBYTE(v16) = 67;
  for ( i = 0; i < this->NumSurfaces(this); ++i )
  {
    v7 = this->Surface(this, i);
    geometry = v7->geometry;
    if ( geometry )
    {
      if ( !geometry->perfectHull )
        v15 = 32;
      v9 = v7->geometry;
      v4 += v9->numIndexes / 3;
      v5 += v9->numVerts;
    }
  }
  v10 = *(_DWORD *)common.type;
  v11 = this->Name(this);
  v12 = ((int (__thiscall *)(idRenderModelStatic *, int, int, const char *))this->NumSurfaces)(this, v5, v4, v11);
  (*(void (**)(netadrtype_t, const char *, ...))(v10 + 124))(common.type, "%c%4ik %3i %4i %4i %s", v15, v16 / 1024, v12);
  if ( this->IsDynamicModel(this) == DM_CACHED )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " (DM_CACHED)");
  if ( this->IsDynamicModel(this) == DM_CONTINUOUS )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " (DM_CONTINUOUS)");
  if ( this->defaulted )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " (DEFAULTED)");
  if ( this->bounds.b[0].x >= (double)this->bounds.b[1].x )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " (EMPTY BOUNDS)");
  if ( this->bounds.b[1].x - this->bounds.b[0].x > 100000.0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " (HUGE BOUNDS)");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
}

// FUNC: public: void __thiscall idVertexCache::UnbindIndex(void)
void __thiscall idVertexCache::UnbindIndex(idVertexCache *this)
{
  qglBindBufferARB(0x8893u, 0);
}

// FUNC: private: void __thiscall idVertexCache::ActuallyFree(struct vertCache_s *)
void __thiscall idVertexCache::ActuallyFree(idVertexCache *this, vertCache_s *block)
{
  vertCache_s **user; // eax
  vertCache_s *next; // eax
  vertCache_s *prev; // ecx
  vertCache_s *v6; // ecx

  if ( !block )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idVertexCache Free: NULL pointer");
  user = block->user;
  if ( user )
  {
    *user = 0;
    block->user = 0;
  }
  if ( block->tag != 3 )
  {
    this->staticAllocTotal -= block->size;
    --this->staticCountTotal;
    if ( !block->vbo )
    {
      if ( block->virtMem )
      {
        Mem_Free(block->virtMem);
        block->virtMem = 0;
      }
    }
  }
  next = block->next;
  prev = block->prev;
  block->tag = 0;
  next->prev = prev;
  block->prev->next = block->next;
  v6 = this->freeStaticHeaders.next;
  block->prev = &this->freeStaticHeaders;
  block->next = v6;
  v6->prev = block;
  block->prev->next = block;
}

// FUNC: public: void * __thiscall idVertexCache::Position(struct vertCache_s *)
char *__thiscall idVertexCache::Position(idVertexCache *this, vertCache_s *buffer)
{
  unsigned int vbo; // eax
  int v3; // edx
  int size; // [esp-8h] [ebp-Ch]

  if ( !buffer || !buffer->tag )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "idVertexCache::Position: bad vertCache_t");
  vbo = buffer->vbo;
  if ( !buffer->vbo )
    return (char *)buffer->virtMem + buffer->offset;
  if ( idVertexCache::r_showVertexCache.internalVar->integerValue == 2 )
  {
    v3 = *(_DWORD *)common.type;
    size = buffer->size;
    if ( buffer->tag == 3 )
      (*(void (**)(netadrtype_t, const char *, ...))(v3 + 124))(
        common.type,
        "GL_ARRAY_BUFFER_ARB = %i + %i (%i bytes)\n",
        vbo,
        buffer->offset,
        size);
    else
      (*(void (**)(netadrtype_t, const char *, ...))(v3 + 124))(
        common.type,
        "GL_ARRAY_BUFFER_ARB = %i (%i bytes)\n",
        vbo,
        size);
  }
  if ( buffer->indexBuffer )
    qglBindBufferARB(0x8893u, buffer->vbo);
  else
    qglBindBufferARB(0x8892u, buffer->vbo);
  return (char *)buffer->offset;
}

// FUNC: public: void __thiscall idVertexCache::PurgeAll(void)
void __thiscall idVertexCache::PurgeAll(idVertexCache *this)
{
  vertCache_s *next; // eax
  vertCache_s *i; // edi

  next = this->staticHeaders.next;
  for ( i = &this->staticHeaders; next != i; next = this->staticHeaders.next )
    idVertexCache::ActuallyFree(this, next);
}

// FUNC: public: void __thiscall idVertexCache::Alloc(void *,int,struct vertCache_s * *,unsigned int)
void __thiscall idVertexCache::Alloc(idVertexCache *this, void *data, int size, vertCache_s **buffer, char flags)
{
  vertCache_s *v7; // eax
  vertCache_s *next; // edx
  vertCache_s *v9; // esi
  vertCache_s *v10; // ecx
  int currentFrame; // edx
  unsigned int vbo; // edi
  bool v13; // zf
  unsigned int v14; // esi
  void *v15; // eax
  int sizea; // [esp+18h] [ebp+8h]

  if ( size <= 0 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idVertexCache::Alloc: size = %i\n",
      size);
  *buffer = 0;
  if ( this->freeStaticHeaders.next == &this->freeStaticHeaders )
  {
    sizea = 1024;
    do
    {
      v7 = idBlockAlloc<vertCache_s,1024,16>::Alloc(&this->headerAllocator);
      next = this->freeStaticHeaders.next;
      v7->next = next;
      v7->prev = &this->freeStaticHeaders;
      next->prev = v7;
      v7->prev->next = v7;
      v7->vbo = 0;
      v7->virtMem = 0;
      if ( !this->virtualMemory )
        qglGenBuffersARB(1, &v7->vbo);
      --sizea;
    }
    while ( sizea );
  }
  v9 = this->freeStaticHeaders.next;
  v9->next->prev = v9->prev;
  v9->prev->next = v9->next;
  v10 = this->staticHeaders.next;
  v9->prev = &this->staticHeaders;
  v9->next = v10;
  v10->prev = v9;
  v9->prev->next = v9;
  v9->size = size;
  v9->offset = 0;
  v9->tag = 1;
  ++this->staticCountThisFrame;
  ++this->staticCountTotal;
  this->staticAllocThisFrame += size;
  this->staticAllocTotal += v9->size;
  v9->user = buffer;
  *buffer = v9;
  v9->indexBuffer = flags & 1;
  currentFrame = this->currentFrame;
  vbo = v9->vbo;
  v13 = v9->vbo == 0;
  v9->frameUsed = currentFrame - 2;
  if ( v13 )
  {
    v15 = Mem_Alloc(size, 0x11u);
    v9->virtMem = v15;
    SIMDProcessor->Memcpy(SIMDProcessor, v15, data, size);
  }
  else
  {
    v14 = ((flags & 1) != 0) + 34962;
    qglBindBufferARB(v14, vbo);
    qglBufferDataARB(v14, size, data, ~flags & 4 | 0x88E0);
  }
}

// FUNC: public: void __thiscall idVertexCache::Touch(struct vertCache_s *)
void __thiscall idVertexCache::Touch(idVertexCache *this, vertCache_s *block)
{
  vertCache_s *next; // eax
  vertCache_s *prev; // ecx
  vertCache_s *v5; // ecx

  if ( !block )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idVertexCache Touch: NULL pointer");
  if ( !block->tag )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "idVertexCache Touch: freed pointer");
  if ( block->tag == 3 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "idVertexCache Touch: temporary pointer");
  next = block->next;
  prev = block->prev;
  block->frameUsed = this->currentFrame;
  next->prev = prev;
  block->prev->next = block->next;
  v5 = this->staticHeaders.next;
  block->prev = &this->staticHeaders;
  block->next = v5;
  v5->prev = block;
  block->prev->next = block;
}

// FUNC: public: void __thiscall idVertexCache::Free(struct vertCache_s *)
void __thiscall idVertexCache::Free(idVertexCache *this, vertCache_s *block)
{
  vertCache_s *next; // eax
  vertCache_s *prev; // ecx
  vertCache_s *v5; // ecx

  if ( block )
  {
    if ( !block->tag )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "idVertexCache Free: freed pointer");
    if ( block->tag == 3 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "idVertexCache Free: temporary pointer");
    next = block->next;
    prev = block->prev;
    block->user = 0;
    next->prev = prev;
    block->prev->next = block->next;
    v5 = this->deferredFreeList.next;
    block->prev = &this->deferredFreeList;
    block->next = v5;
    v5->prev = block;
    block->prev->next = block;
  }
}

// FUNC: public: struct vertCache_s * __thiscall idVertexCache::AllocFrameTemp(void *,int,unsigned int)
vertCache_s *__thiscall idVertexCache::AllocFrameTemp(idVertexCache *this, void *data, int size, char flags)
{
  int *dynamicIndexAllocThisFrame; // edi
  int *dynamicIndexCountThisFrame; // edx
  vertCache_s **tempIndexBuffers; // ecx
  int v9; // eax
  int listNum; // edx
  vertCache_s *v12; // eax
  bool v13; // zf
  vertCache_s *next; // edx
  vertCache_s *v15; // eax
  vertCache_s *v16; // ebp
  vertCache_s *v17; // eax
  vertCache_s **p_next; // edx
  vertCache_s *v19; // ecx
  vertCache_s *v20; // ebp
  vertCache_s **v21; // eax
  int v22; // ecx
  unsigned int v23; // esi
  vertCache_s *block; // [esp+10h] [ebp-10h] BYREF
  vertCache_s *dynamicHeaders; // [esp+14h] [ebp-Ch]
  int *dynamicCountThisFrame; // [esp+18h] [ebp-8h]
  vertCache_s **tempBuffers; // [esp+1Ch] [ebp-4h]
  unsigned int flagsa; // [esp+2Ch] [ebp+Ch]

  if ( size <= 0 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idVertexCache::AllocFrameTemp: size = %i\n",
      size);
  if ( (flags & 1) != 0 )
  {
    dynamicHeaders = this->dynamicIndexHeaders;
    dynamicIndexAllocThisFrame = this->dynamicIndexAllocThisFrame;
    dynamicIndexCountThisFrame = this->dynamicIndexCountThisFrame;
    tempIndexBuffers = this->tempIndexBuffers;
    v9 = 0;
  }
  else
  {
    dynamicHeaders = this->dynamicVertexHeaders;
    dynamicIndexAllocThisFrame = this->dynamicVertexAllocThisFrame;
    dynamicIndexCountThisFrame = this->dynamicVertexCountThisFrame;
    tempIndexBuffers = this->tempVertexBuffers;
    v9 = 5256000;
  }
  dynamicCountThisFrame = dynamicIndexCountThisFrame;
  listNum = this->listNum;
  tempBuffers = tempIndexBuffers;
  if ( size + dynamicIndexAllocThisFrame[listNum] <= v9 )
  {
    if ( this->freeDynamicHeaders.next == &this->freeDynamicHeaders )
    {
      flagsa = 1024;
      do
      {
        v12 = idBlockAlloc<vertCache_s,1024,16>::Alloc(&this->headerAllocator);
        v13 = flagsa-- == 1;
        next = this->freeDynamicHeaders.next;
        block = v12;
        v12->next = next;
        v12->prev = &this->freeDynamicHeaders;
        next->prev = v12;
        v12->prev->next = v12;
      }
      while ( !v13 );
    }
    v15 = this->freeDynamicHeaders.next;
    block = v15;
    v15->next->prev = v15->prev;
    v16 = dynamicHeaders;
    v15->prev->next = v15->next;
    v17 = block;
    p_next = &block->next;
    v19 = &v16[this->listNum];
    v20 = v19->next;
    block->prev = v19;
    *p_next = v20;
    v20->prev = v17;
    v17->prev->next = v17;
    block->size = size;
    block->tag = 3;
    block->indexBuffer = flags & 1;
    block->offset = dynamicIndexAllocThisFrame[this->listNum];
    dynamicIndexAllocThisFrame[this->listNum] += block->size;
    ++dynamicCountThisFrame[this->listNum];
    v21 = tempBuffers;
    v22 = 0;
    block->user = 0;
    block->virtMem = v21[this->listNum]->virtMem;
    block->vbo = v21[this->listNum]->vbo;
    block->frameUsed = 0;
    if ( block->vbo )
    {
      LOBYTE(v22) = block->indexBuffer;
      v23 = v22 + 34962;
      qglBindBufferARB(v22 + 34962, block->vbo);
      qglBufferSubDataARB(v23, block->offset, size, data);
    }
    else
    {
      ((void (__stdcall *)(void *, int))SIMDProcessor->Memcpy)(data, size);
    }
    return block;
  }
  else
  {
    this->tempOverflow = 1;
    idVertexCache::Alloc(this, data, size, &block, flags);
    idVertexCache::Free(this, block);
    return block;
  }
}

// FUNC: public: void __thiscall idVertexCache::EndFrame(void)
void __thiscall idVertexCache::EndFrame(idVertexCache *this)
{
  idVertexCache *next; // eax
  int v3; // edx
  vertCache_s *p_staticHeaders; // ecx
  int v5; // edi
  const char *v6; // ebp
  int listNum; // ecx
  bool v8; // sf
  int v9; // eax
  bool v10; // zf
  vertCache_s *v11; // eax
  vertCache_s *v12; // edx
  vertCache_s *p_freeDynamicHeaders; // ecx
  vertCache_s *v14; // edx
  vertCache_s *v15; // eax
  int staticUseCount; // [esp+Ch] [ebp-4h]

  if ( idVertexCache::r_showVertexCache.internalVar->integerValue )
  {
    next = (idVertexCache *)this->staticHeaders.next;
    v3 = 0;
    p_staticHeaders = &this->staticHeaders;
    v5 = 0;
    staticUseCount = 0;
    if ( next != (idVertexCache *)&this->staticHeaders )
    {
      do
      {
        if ( next->dynamicIndexAllocThisFrame[1] == this->currentFrame )
        {
          ++v3;
          v5 += next->dynamicVertexAllocThisFrame[0];
        }
        next = (idVertexCache *)next->dynamicVertexCountThisFrame[1];
      }
      while ( next != (idVertexCache *)p_staticHeaders );
      staticUseCount = v3;
    }
    v6 = "(OVERFLOW)";
    if ( !this->tempOverflow )
      v6 = &entityFilter;
    listNum = this->listNum;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "vertex dynamic:%i=%ik%s, index dynamic:%i=%ik%s, static alloc:%i=%ik used:%i=%ik total:%i=%ik\n",
      this->dynamicVertexCountThisFrame[listNum],
      this->dynamicVertexAllocThisFrame[listNum] / 1024,
      v6,
      this->dynamicIndexCountThisFrame[listNum],
      this->dynamicIndexAllocThisFrame[listNum] / 1024,
      v6,
      this->staticCountThisFrame,
      this->staticAllocThisFrame / 1024,
      staticUseCount,
      v5 / 1024,
      this->staticCountTotal,
      this->staticAllocTotal / 1024);
  }
  if ( !this->virtualMemory )
  {
    qglBindBufferARB(0x8892u, 0);
    qglBindBufferARB(0x8893u, 0);
  }
  v9 = tr.frameCount & 0x80000001;
  v8 = tr.frameCount < 0;
  this->currentFrame = tr.frameCount;
  if ( v8 )
    v9 = (((_BYTE)v9 - 1) | 0xFFFFFFFE) + 1;
  this->listNum = v9;
  this->dynamicVertexAllocThisFrame[v9] = 0;
  this->dynamicVertexCountThisFrame[this->listNum] = 0;
  this->dynamicIndexAllocThisFrame[this->listNum] = 0;
  this->dynamicIndexCountThisFrame[this->listNum] = 0;
  v10 = this->deferredFreeList.next == &this->deferredFreeList;
  this->staticAllocThisFrame = 0;
  this->staticCountThisFrame = 0;
  this->tempOverflow = 0;
  if ( !v10 )
  {
    do
      idVertexCache::ActuallyFree(this, this->deferredFreeList.next);
    while ( this->deferredFreeList.next != &this->deferredFreeList );
  }
  v11 = &this->dynamicVertexHeaders[this->listNum];
  v12 = this->dynamicVertexHeaders[this->listNum].next;
  p_freeDynamicHeaders = &this->freeDynamicHeaders;
  if ( v12 != v11 )
  {
    v12->prev = p_freeDynamicHeaders;
    v11->prev->next = this->freeDynamicHeaders.next;
    this->freeDynamicHeaders.next->prev = v11->prev;
    this->freeDynamicHeaders.next = v12;
    v11->prev = v11;
    v11->next = v11;
  }
  v14 = this->dynamicIndexHeaders[this->listNum].next;
  v15 = &this->dynamicIndexHeaders[this->listNum];
  if ( v14 != v15 )
  {
    v14->prev = p_freeDynamicHeaders;
    v15->prev->next = this->freeDynamicHeaders.next;
    this->freeDynamicHeaders.next->prev = v15->prev;
    this->freeDynamicHeaders.next = v14;
    v15->prev = v15;
    v15->next = v15;
  }
}

// FUNC: public: void __thiscall idVertexCache::List(void)
void __thiscall idVertexCache::List(idVertexCache *this)
{
  vertCache_s *next; // eax
  int v3; // edx
  vertCache_s *p_staticHeaders; // ecx
  idVertexCache *v5; // eax
  int i; // ebx
  idVertexCache *v7; // eax
  int j; // edi
  int numActive; // [esp+10h] [ebp-4h]

  next = this->staticHeaders.next;
  v3 = 0;
  p_staticHeaders = &this->staticHeaders;
  numActive = 0;
  if ( next != p_staticHeaders )
  {
    do
    {
      next = next->next;
      ++v3;
    }
    while ( next != p_staticHeaders );
    numActive = v3;
  }
  v5 = (idVertexCache *)this->freeStaticHeaders.next;
  for ( i = 0; v5 != (idVertexCache *)&this->freeStaticHeaders; ++i )
    v5 = (idVertexCache *)v5->dynamicVertexCountThisFrame[1];
  v7 = (idVertexCache *)this->freeDynamicHeaders.next;
  for ( j = 0; v7 != (idVertexCache *)&this->freeDynamicHeaders; ++j )
    v7 = (idVertexCache *)v7->dynamicVertexCountThisFrame[1];
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%i dynamic vertex buffers of %ik\n",
    2,
    this->frameVertexBytes / 1024);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%i dynamic index buffers of %ik\n",
    2,
    this->frameIndexBytes / 1024);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%5i active static headers\n",
    numActive);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%5i free static headers\n",
    i);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%5i free dynamic headers\n",
    j);
  if ( this->virtualMemory )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Vertex cache is in virtual memory (SLOW)\n");
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Vertex cache is in ARB_vertex_buffer_object memory (FAST).\n");
  if ( r_useIndexBuffers.internalVar->integerValue )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Index buffers are accelerated.\n");
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Index buffers are not used.\n");
}

// FUNC: public: bool __thiscall idVertexCache::IsFast(void)
bool __thiscall idVertexCache::IsFast(idVertexCache *this)
{
  return !this->virtualMemory;
}

// FUNC: public: __thiscall idVertexCache::~idVertexCache(void)
void __thiscall idVertexCache::~idVertexCache(idVertexCache *this)
{
  idBlockAlloc<vertCache_s,1024,16>::Shutdown(&this->headerAllocator);
}

// FUNC: R_ListVertexCache_f
void __cdecl R_ListVertexCache_f()
{
  idVertexCache::List(&vertexCache);
}

// FUNC: public: void __thiscall idVertexCache::Init(void)
void __thiscall idVertexCache::Init(idVertexCache *this)
{
  void *v2; // ebx
  vertCache_s **tempIndexBuffers; // edi
  vertCache_s **v4; // ebp
  int frameIndexBytes; // eax
  vertCache_s *v6; // eax
  vertCache_s *v7; // eax
  int v8; // [esp+18h] [ebp-4h]

  cmdSystem->AddCommand(
    cmdSystem,
    "listVertexCache",
    (void (__cdecl *)(const idCmdArgs *))R_ListVertexCache_f,
    4,
    "lists vertex cache",
    0);
  this->virtualMemory = 0;
  if ( r_useVertexBuffers.internalVar->integerValue && glConfig.ARBVertexBufferObjectAvailable )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "using ARB_vertex_buffer_object memory\n");
  }
  else
  {
    this->virtualMemory = 1;
    r_useIndexBuffers.internalVar->InternalSetBool(r_useIndexBuffers.internalVar, 0);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "WARNING: vertex array range in virtual memory (SLOW)\n");
  }
  this->freeStaticHeaders.prev = &this->freeStaticHeaders;
  this->freeStaticHeaders.next = &this->freeStaticHeaders;
  this->staticHeaders.prev = &this->staticHeaders;
  this->staticHeaders.next = &this->staticHeaders;
  this->freeDynamicHeaders.prev = &this->freeDynamicHeaders;
  this->freeDynamicHeaders.next = &this->freeDynamicHeaders;
  this->deferredFreeList.prev = &this->deferredFreeList;
  this->deferredFreeList.next = &this->deferredFreeList;
  this->dynamicVertexHeaders[0].prev = this->dynamicVertexHeaders;
  this->dynamicVertexHeaders[0].next = this->dynamicVertexHeaders;
  this->dynamicIndexHeaders[0].prev = this->dynamicIndexHeaders;
  this->dynamicIndexHeaders[0].next = this->dynamicIndexHeaders;
  this->dynamicVertexHeaders[1].prev = &this->dynamicVertexHeaders[1];
  this->dynamicVertexHeaders[1].next = &this->dynamicVertexHeaders[1];
  this->dynamicIndexHeaders[1].prev = &this->dynamicIndexHeaders[1];
  this->dynamicIndexHeaders[1].next = &this->dynamicIndexHeaders[1];
  this->frameVertexBytes = 5256000;
  this->frameIndexBytes = 0;
  this->staticAllocTotal = 0;
  v2 = Mem_Alloc(5256000, 0x11u);
  tempIndexBuffers = this->tempIndexBuffers;
  v8 = 2;
  do
  {
    v4 = tempIndexBuffers - 2;
    idVertexCache::Alloc(this, v2, this->frameVertexBytes, tempIndexBuffers - 2, 4u);
    frameIndexBytes = this->frameIndexBytes;
    if ( frameIndexBytes )
      idVertexCache::Alloc(this, v2, frameIndexBytes, tempIndexBuffers, 5u);
    (*v4)->tag = 2;
    v6 = *v4;
    (*v4)->next->prev = (*v4)->prev;
    v6->prev->next = v6->next;
    if ( this->frameIndexBytes )
    {
      (*tempIndexBuffers)->tag = 2;
      v7 = *tempIndexBuffers;
      (*tempIndexBuffers)->next->prev = (*tempIndexBuffers)->prev;
      v7->prev->next = v7->next;
    }
    ++tempIndexBuffers;
    --v8;
  }
  while ( v8 );
  Mem_Free(v2);
  idVertexCache::EndFrame(this);
}
