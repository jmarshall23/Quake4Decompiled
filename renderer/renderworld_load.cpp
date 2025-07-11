
// FUNC: public: void __thiscall idRenderWorldLocal::SetupAreaRefs(void)
void __thiscall idRenderWorldLocal::SetupAreaRefs(idRenderWorldLocal *this)
{
  int v1; // edx
  bool v2; // zf
  bool v3; // sf
  int v4; // eax

  v1 = 0;
  v2 = this->numPortalAreas == 0;
  v3 = this->numPortalAreas < 0;
  this->connectedAreaNum = 0;
  if ( !v3 && !v2 )
  {
    v4 = 0;
    do
    {
      this->portalAreas[v4].areaNum = v1;
      this->portalAreas[v4].lightRefs.areaPrev = &this->portalAreas[v4].lightRefs;
      this->portalAreas[v4].lightRefs.areaNext = this->portalAreas[v4].lightRefs.areaPrev;
      this->portalAreas[v4].entityRefs.areaPrev = &this->portalAreas[v4].entityRefs;
      this->portalAreas[v4].entityRefs.areaNext = this->portalAreas[v4].entityRefs.areaPrev;
      this->portalAreas[v4].effectRefs.areaPrev = &this->portalAreas[v4].effectRefs;
      ++v1;
      this->portalAreas[v4].effectRefs.areaNext = this->portalAreas[v4].effectRefs.areaPrev;
      ++v4;
    }
    while ( v1 < this->numPortalAreas );
  }
}

// FUNC: public: int __thiscall idRenderWorldLocal::CommonChildrenArea_r(struct areaNode_t *)
int __thiscall idRenderWorldLocal::CommonChildrenArea_r(idRenderWorldLocal *this, areaNode_t *node)
{
  int v3; // esi
  int *children; // edi
  int v5; // eax
  int result; // eax
  int nums[2]; // [esp+10h] [ebp-8h]

  v3 = 0;
  children = node->children;
  do
  {
    v5 = *children;
    if ( *children > 0 )
      nums[v3] = idRenderWorldLocal::CommonChildrenArea_r(this, &this->areaNodes[v5]);
    else
      nums[v3] = -1 - v5;
    ++v3;
    ++children;
  }
  while ( v3 < 2 );
  result = nums[0];
  if ( nums[0] == -1 )
    result = nums[1];
  if ( nums[1] != -1 && result != nums[1] )
    result = -2;
  node->commonChildrenArea = result;
  return result;
}

// FUNC: public: void __thiscall idRenderWorldLocal::ClearPortalStates(void)
void __thiscall idRenderWorldLocal::ClearPortalStates(idRenderWorldLocal *this)
{
  int v2; // ebx
  int v3; // eax
  int v4; // ecx
  int i; // ebp
  int j; // edi
  portalArea_s *portalAreas; // eax

  v2 = 0;
  v3 = 0;
  if ( this->numInterAreaPortals > 0 )
  {
    v4 = 0;
    do
    {
      this->doublePortals[v4].blockingBits = 0;
      ++v3;
      ++v4;
    }
    while ( v3 < this->numInterAreaPortals );
  }
  for ( i = 0; i < this->numPortalAreas; ++v2 )
  {
    for ( j = 0; j < 4; ++j )
    {
      portalAreas = this->portalAreas;
      ++this->connectedAreaNum;
      idRenderWorldLocal::FloodConnectedAreas(this, &portalAreas[v2], j);
    }
    ++i;
  }
}

// FUNC: private: void __thiscall idRenderWorldLocal::ParseVertexBuffers(class Lexer &)
void __thiscall idRenderWorldLocal::ParseVertexBuffers(idRenderWorldLocal *this, Lexer *lex)
{
  int m_numVertexBuffers; // ebx
  int *v4; // eax
  rvVertexBuffer *v5; // ebp
  int v6; // ebx
  int v7; // ebp

  Lexer::ExpectTokenString(lex, "[");
  this->m_numVertexBuffers = Lexer::ParseInt(lex);
  Lexer::ExpectTokenString(lex, "]");
  Lexer::ExpectTokenString(lex, "{");
  m_numVertexBuffers = this->m_numVertexBuffers;
  v4 = (int *)Memory::Allocate(472 * m_numVertexBuffers + 4);
  v5 = 0;
  if ( v4 )
  {
    v5 = (rvVertexBuffer *)(v4 + 1);
    *v4 = m_numVertexBuffers;
    `eh vector constructor iterator'(
      v4 + 1,
      0x1D8u,
      m_numVertexBuffers,
      (void (__thiscall *)(void *))rvVertexBuffer::rvVertexBuffer,
      (void (__thiscall *)(void *))rvVertexBuffer::~rvVertexBuffer);
  }
  this->m_vertexBuffers = v5;
  if ( !v5 )
    Lexer::Error(lex, "Out of memory");
  session->PacifierUpdate(session);
  v6 = 0;
  if ( this->m_numVertexBuffers > 0 )
  {
    v7 = 0;
    do
    {
      Lexer::ExpectTokenString(lex, "VertexBuffer");
      rvVertexBuffer::Init(&this->m_vertexBuffers[v7], lex);
      ++v6;
      ++v7;
    }
    while ( v6 < this->m_numVertexBuffers );
  }
  Lexer::ExpectTokenString(lex, "}");
}

// FUNC: private: void __thiscall idRenderWorldLocal::ParseIndexBuffers(class Lexer &)
void __thiscall idRenderWorldLocal::ParseIndexBuffers(idRenderWorldLocal *this, Lexer *lex)
{
  int m_numIndexBuffers; // ebx
  int *v4; // eax
  rvIndexBuffer *v5; // ebp
  int v6; // ebx
  int v7; // ebp

  Lexer::ExpectTokenString(lex, "[");
  this->m_numIndexBuffers = Lexer::ParseInt(lex);
  Lexer::ExpectTokenString(lex, "]");
  Lexer::ExpectTokenString(lex, "{");
  m_numIndexBuffers = this->m_numIndexBuffers;
  v4 = (int *)Memory::Allocate(36 * m_numIndexBuffers + 4);
  v5 = 0;
  if ( v4 )
  {
    v5 = (rvIndexBuffer *)(v4 + 1);
    *v4 = m_numIndexBuffers;
    `eh vector constructor iterator'(
      v4 + 1,
      0x24u,
      m_numIndexBuffers,
      (void (__thiscall *)(void *))rvIndexBuffer::rvIndexBuffer,
      (void (__thiscall *)(void *))rvIndexBuffer::~rvIndexBuffer);
  }
  this->m_indexBuffers = v5;
  if ( !v5 )
    Lexer::Error(lex, "Out of memory");
  session->PacifierUpdate(session);
  v6 = 0;
  if ( this->m_numIndexBuffers > 0 )
  {
    v7 = 0;
    do
    {
      Lexer::ExpectTokenString(lex, "IndexBuffer");
      rvIndexBuffer::Init(&this->m_indexBuffers[v7], lex);
      ++v6;
      ++v7;
    }
    while ( v6 < this->m_numIndexBuffers );
  }
  Lexer::ExpectTokenString(lex, "}");
}

// FUNC: private: void __thiscall idRenderWorldLocal::ParseSilhouetteEdges(class Lexer &)
void __thiscall idRenderWorldLocal::ParseSilhouetteEdges(idRenderWorldLocal *this, Lexer *lex)
{
  silEdge_t *v3; // eax
  int v4; // ebp
  int v5; // ebx

  Lexer::ExpectTokenString(lex, "[");
  this->m_numSilEdges = Lexer::ParseInt(lex);
  Lexer::ExpectTokenString(lex, "]");
  Lexer::ExpectTokenString(lex, "{");
  v3 = (silEdge_t *)Memory::Allocate(16 * this->m_numSilEdges);
  this->m_silEdges = v3;
  if ( !v3 )
    Lexer::Error(lex, "Out of memory");
  session->PacifierUpdate(session);
  v4 = 0;
  if ( this->m_numSilEdges > 0 )
  {
    v5 = 0;
    do
    {
      this->m_silEdges[v5].p1 = Lexer::ParseInt(lex);
      this->m_silEdges[v5].p2 = Lexer::ParseInt(lex);
      this->m_silEdges[v5].v1 = Lexer::ParseInt(lex);
      this->m_silEdges[v5].v2 = Lexer::ParseInt(lex);
      ++v4;
      ++v5;
    }
    while ( v4 < this->m_numSilEdges );
  }
  Lexer::ExpectTokenString(lex, "}");
}

// FUNC: private: void __thiscall idRenderWorldLocal::WriteVertexBuffers(class idFile &,bool)
void __thiscall idRenderWorldLocal::WriteVertexBuffers(idRenderWorldLocal *this, idFile *outFile, bool compressed)
{
  int m_numVertexBuffers; // eax
  idFile *v5; // ebp
  int v6; // ebx
  int v7; // edi
  rvVertexBuffer *m_vertexBuffers; // edx
  unsigned int m_flags; // eax
  const rvVertexFormat *p_m_format; // ebp
  rvVertexFormat compressedFormat; // [esp+4h] [ebp-C4h] BYREF
  int v12; // [esp+C4h] [ebp-4h]

  m_numVertexBuffers = this->m_numVertexBuffers;
  if ( m_numVertexBuffers )
  {
    v5 = outFile;
    outFile->WriteFloatString(outFile, "VertexBuffer[ %d ]\n{\n", m_numVertexBuffers);
    v6 = 0;
    if ( this->m_numVertexBuffers > 0 )
    {
      v7 = 0;
      do
      {
        if ( compressed )
        {
          m_vertexBuffers = this->m_vertexBuffers;
          m_flags = m_vertexBuffers[v7].m_flags;
          p_m_format = &m_vertexBuffers[v7].m_format;
          if ( (m_flags & 0x80) != 0 || (m_flags & 0x200) != 0 )
          {
            rvVertexFormat::rvVertexFormat(&compressedFormat);
            v12 = 0;
            rvRenderModelMD5R::CompressVertexFormat(&compressedFormat, p_m_format);
            rvVertexBuffer::SetLoadFormat(&this->m_vertexBuffers[v7], &compressedFormat);
            this->m_vertexBuffers[v7].m_flags |= 0x20u;
            v12 = -1;
            rvVertexFormat::Shutdown(&compressedFormat);
            v5 = outFile;
          }
          else
          {
            p_m_format[2].m_flags |= 0x10u;
            v5 = outFile;
          }
        }
        else
        {
          this->m_vertexBuffers[v7].m_flags &= ~0x10u;
          this->m_vertexBuffers[v7].m_flags &= ~0x20u;
        }
        rvVertexBuffer::Write(&this->m_vertexBuffers[v7], v5, "\t");
        ++v6;
        ++v7;
      }
      while ( v6 < this->m_numVertexBuffers );
    }
    v5->WriteFloatString(v5, "}\n");
  }
}

// FUNC: private: void __thiscall idRenderWorldLocal::WriteIndexBuffers(class idFile &)
void __thiscall idRenderWorldLocal::WriteIndexBuffers(idRenderWorldLocal *this, idFile *outFile)
{
  int m_numIndexBuffers; // eax
  int v4; // edi
  int v5; // ebx

  m_numIndexBuffers = this->m_numIndexBuffers;
  if ( m_numIndexBuffers )
  {
    outFile->WriteFloatString(outFile, "IndexBuffer[ %d ]\n{\n", m_numIndexBuffers);
    v4 = 0;
    if ( this->m_numIndexBuffers > 0 )
    {
      v5 = 0;
      do
      {
        rvIndexBuffer::Write(&this->m_indexBuffers[v5], outFile, "\t");
        ++v4;
        ++v5;
      }
      while ( v4 < this->m_numIndexBuffers );
    }
    outFile->WriteFloatString(outFile, "}\n");
  }
}

// FUNC: private: void __thiscall idRenderWorldLocal::WriteSilhouetteEdges(class idFile &)
void __thiscall idRenderWorldLocal::WriteSilhouetteEdges(idRenderWorldLocal *this, idFile *outFile)
{
  int m_numSilEdges; // eax
  int v4; // ebx
  int v5; // ebp

  m_numSilEdges = this->m_numSilEdges;
  if ( m_numSilEdges )
  {
    outFile->WriteFloatString(outFile, "SilhouetteEdge[ %d ]\n{\n", m_numSilEdges);
    v4 = 0;
    if ( this->m_numSilEdges > 0 )
    {
      v5 = 0;
      do
      {
        outFile->WriteFloatString(
          outFile,
          "\t%d %d %d %d\n",
          this->m_silEdges[v5].p1,
          this->m_silEdges[v5].p2,
          this->m_silEdges[v5].v1,
          this->m_silEdges[v5].v2);
        ++v4;
        ++v5;
      }
      while ( v4 < this->m_numSilEdges );
    }
    outFile->WriteFloatString(outFile, "}\n");
  }
}

// FUNC: private: void __thiscall idRenderWorldLocal::WriteModels(class idFile &)
void __thiscall idRenderWorldLocal::WriteModels(idRenderWorldLocal *this, idFile *outFile)
{
  int m_numModels; // eax
  int v4; // ebx
  idFile_vtbl *v6; // ebp
  const char *v7; // eax
  idFile *outFilea; // [esp+Ch] [ebp+4h]

  m_numModels = this->m_numModels;
  v4 = 0;
  if ( m_numModels )
  {
    outFile->WriteFloatString(outFile, "Model[ %d ]\n{\n", m_numModels);
    for ( outFilea = 0; (int)outFilea < this->m_numModels; outFilea = (idFile *)((char *)outFilea + 1) )
    {
      v6 = outFile->__vftable;
      v7 = this->m_models[v4].Name(&this->m_models[v4]);
      v6->WriteFloatString(outFile, "\tModel \"%s\"\n\t{\n", v7);
      rvRenderModelMD5R::WriteSansBuffers(&this->m_models[v4], outFile, "\t\t");
      outFile->WriteFloatString(outFile, "\t}\n");
      ++v4;
    }
    outFile->WriteFloatString(outFile, "}\n");
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::FreeWorld(void)
void __thiscall idRenderWorldLocal::FreeWorld(idRenderWorldLocal *this)
{
  portalArea_s *areaPrev; // ebp
  portalArea_s *v3; // ebx
  portalArea_s *portals; // edi
  void (__thiscall ***v5)(_DWORD, int); // ecx
  rvVertexBuffer *m_vertexBuffers; // eax
  float **v7; // edi
  rvIndexBuffer *m_indexBuffers; // eax
  int *p_m_numIndicesWritten; // edi
  int v10; // edi
  rvRenderModelMD5R *m_models; // ecx
  int v12; // edi
  bool v13; // cc
  idRenderModel *v14; // ecx
  idScreenRect *areaScreenRect; // [esp-8h] [ebp-1Ch]
  idBlockAlloc<areaReference_s,1024,16>::block_s *blocks; // [esp-4h] [ebp-18h]
  idBlockAlloc<idInteraction,256,16>::block_s *v17; // [esp-4h] [ebp-18h]
  idBlockAlloc<areaNumRef_s,1024,16>::block_s *v18; // [esp-4h] [ebp-18h]
  int v19; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  this->FreeDefs(this);
  areaPrev = 0;
  i = 0;
  if ( this->numPortalAreas > 0 )
  {
    v19 = 0;
    do
    {
      v3 = &this->portalAreas[v19];
      portals = (portalArea_s *)v3->portals;
      if ( portals != areaPrev )
      {
        do
        {
          v5 = (void (__thiscall ***)(_DWORD, int))portals->connectedAreaNum[3];
          areaPrev = (portalArea_s *)portals->entityRefs.areaPrev;
          if ( v5 )
            (**v5)(v5, 1);
          R_StaticFree(portals);
          portals = areaPrev;
        }
        while ( areaPrev );
      }
      if ( v3->lightRefs.areaNext != &v3->lightRefs )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "FreeWorld: unexpected remaining lightRefs");
      if ( v3->entityRefs.areaNext != &v3->entityRefs )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "FreeWorld: unexpected remaining entityRefs");
      if ( v3->effectRefs.areaNext != &v3->effectRefs )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "FreeWorld: unexpected remaining effectRefs");
      ++v19;
      ++i;
    }
    while ( i < this->numPortalAreas );
  }
  if ( this->portalAreas != areaPrev )
  {
    R_StaticFree(this->portalAreas);
    areaScreenRect = this->areaScreenRect;
    this->portalAreas = areaPrev;
    this->numPortalAreas = (int)areaPrev;
    R_StaticFree(areaScreenRect);
    this->areaScreenRect = (idScreenRect *)areaPrev;
  }
  if ( (portalArea_s *)this->doublePortals != areaPrev )
  {
    R_StaticFree(this->doublePortals);
    this->doublePortals = (doublePortal_s *)areaPrev;
    this->numInterAreaPortals = (int)areaPrev;
  }
  if ( (portalArea_s *)this->areaNodes != areaPrev )
  {
    R_StaticFree(this->areaNodes);
    this->areaNodes = (areaNode_t *)areaPrev;
  }
  m_vertexBuffers = this->m_vertexBuffers;
  if ( m_vertexBuffers != (rvVertexBuffer *)areaPrev )
  {
    v7 = &m_vertexBuffers[-1].m_texCoordArrays[6];
    `eh vector destructor iterator'(
      m_vertexBuffers,
      0x1D8u,
      (int)m_vertexBuffers[-1].m_texCoordArrays[6],
      (void (__thiscall *)(void *))rvVertexBuffer::~rvVertexBuffer);
    Memory::Free(v7);
    this->m_vertexBuffers = (rvVertexBuffer *)areaPrev;
    this->m_numVertexBuffers = (int)areaPrev;
  }
  m_indexBuffers = this->m_indexBuffers;
  if ( m_indexBuffers != (rvIndexBuffer *)areaPrev )
  {
    p_m_numIndicesWritten = &m_indexBuffers[-1].m_numIndicesWritten;
    `eh vector destructor iterator'(
      m_indexBuffers,
      0x24u,
      m_indexBuffers[-1].m_numIndicesWritten,
      (void (__thiscall *)(void *))rvIndexBuffer::~rvIndexBuffer);
    Memory::Free(p_m_numIndicesWritten);
    this->m_indexBuffers = (rvIndexBuffer *)areaPrev;
    this->m_numIndexBuffers = (int)areaPrev;
  }
  if ( (portalArea_s *)this->m_silEdges != areaPrev )
  {
    Memory::Free(this->m_silEdges);
    this->m_silEdges = (silEdge_t *)areaPrev;
    this->m_numSilEdges = (int)areaPrev;
  }
  if ( (portalArea_s *)this->m_models != areaPrev )
  {
    v10 = 0;
    if ( this->localModels.num > (int)areaPrev )
    {
      do
        renderModelManager->RemoveModel(renderModelManager, this->localModels.list[v10++]);
      while ( v10 < this->localModels.num );
    }
    if ( (portalArea_s *)this->localModels.list != areaPrev )
      Memory::Free(this->localModels.list);
    this->localModels.list = (idRenderModel **)areaPrev;
    this->localModels.num = (int)areaPrev;
    this->localModels.size = (int)areaPrev;
    m_models = this->m_models;
    if ( m_models != (rvRenderModelMD5R *)areaPrev )
    {
      if ( (portalArea_s *)m_models[-1].m_next == areaPrev )
        Memory::Free(&m_models[-1].m_next);
      else
        ((void (__thiscall *)(rvRenderModelMD5R *, int))m_models->~rvRenderModelMD5R)(m_models, 3);
    }
    this->m_models = (rvRenderModelMD5R *)areaPrev;
    this->m_numModels = (int)areaPrev;
  }
  v12 = 0;
  v13 = this->localModels.num <= (int)areaPrev;
  this->m_convertedMD5R = 0;
  if ( !v13 )
  {
    do
    {
      renderModelManager->RemoveModel(renderModelManager, this->localModels.list[v12]);
      v14 = this->localModels.list[v12];
      if ( v14 != (idRenderModel *)areaPrev )
        ((void (__thiscall *)(idRenderModel *, int))v14->~idRenderModel)(v14, 1);
      ++v12;
    }
    while ( v12 < this->localModels.num );
  }
  if ( (portalArea_s *)this->localModels.list != areaPrev )
    Memory::Free(this->localModels.list);
  this->localModels.list = (idRenderModel **)areaPrev;
  this->localModels.num = (int)areaPrev;
  this->localModels.size = (int)areaPrev;
  while ( (portalArea_s *)this->areaReferenceAllocator.blocks != areaPrev )
  {
    blocks = this->areaReferenceAllocator.blocks;
    this->areaReferenceAllocator.blocks = blocks->next;
    Memory::Free(blocks);
  }
  this->areaReferenceAllocator.blocks = (idBlockAlloc<areaReference_s,1024,16>::block_s *)areaPrev;
  this->areaReferenceAllocator.free = (idBlockAlloc<areaReference_s,1024,16>::element_s *)areaPrev;
  this->areaReferenceAllocator.active = (int)areaPrev;
  this->areaReferenceAllocator.total = (int)areaPrev;
  while ( (portalArea_s *)this->interactionAllocator.blocks != areaPrev )
  {
    v17 = this->interactionAllocator.blocks;
    this->interactionAllocator.blocks = v17->next;
    Memory::Free(v17);
  }
  this->interactionAllocator.blocks = (idBlockAlloc<idInteraction,256,16>::block_s *)areaPrev;
  this->interactionAllocator.free = (idBlockAlloc<idInteraction,256,16>::element_s *)areaPrev;
  this->interactionAllocator.active = (int)areaPrev;
  this->interactionAllocator.total = (int)areaPrev;
  while ( (portalArea_s *)this->areaNumRefAllocator.blocks != areaPrev )
  {
    v18 = this->areaNumRefAllocator.blocks;
    this->areaNumRefAllocator.blocks = v18->next;
    Memory::Free(v18);
  }
  this->areaNumRefAllocator.blocks = (idBlockAlloc<areaNumRef_s,1024,16>::block_s *)areaPrev;
  this->areaNumRefAllocator.free = (idBlockAlloc<areaNumRef_s,1024,16>::element_s *)areaPrev;
  this->areaNumRefAllocator.active = (int)areaPrev;
  this->areaNumRefAllocator.total = (int)areaPrev;
  idStr::operator=(&this->mapName, "<FREED>");
}

// FUNC: public: void __thiscall idRenderWorldLocal::TouchWorldModels(void)
void __thiscall idRenderWorldLocal::TouchWorldModels(idRenderWorldLocal *this)
{
  int i; // esi
  idRenderModel *v3; // ecx
  idRenderModelManager_vtbl *v4; // ebx
  int v5; // eax

  for ( i = 0; i < this->localModels.num; ++i )
  {
    v3 = this->localModels.list[i];
    v4 = renderModelManager->__vftable;
    v5 = (int)v3->Name(v3);
    v4->CheckModel(renderModelManager, (const char *)v5);
  }
}

// FUNC: public: class idRenderModel * __thiscall idRenderWorldLocal::ParseModel(class Lexer *)
idRenderModel *__userpurge idRenderWorldLocal::ParseModel@<eax>(
        idRenderWorldLocal *this@<ecx>,
        srfTriangles_s *a2@<edi>,
        int a3@<esi>,
        Lexer *src)
{
  idRenderModel *v5; // ebx
  signed int v6; // esi
  idRenderModel_vtbl *v7; // edi
  BOOL v8; // eax
  srfTriangles_s *v9; // esi
  unsigned int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // ebx
  idDrawVert *verts; // eax
  int v15; // eax
  int i; // edi
  int numVerts; // [esp+10h] [ebp-D4h]
  signed int v21; // [esp+20h] [ebp-C4h]
  int v22; // [esp+24h] [ebp-C0h]
  idRenderModel *v23; // [esp+30h] [ebp-B4h]
  float vec4_8; // [esp+40h] [ebp-A4h]
  float vec4_12; // [esp+44h] [ebp-A0h]
  float vec[12]; // [esp+48h] [ebp-9Ch] BYREF
  modelSurface_s surf; // [esp+78h] [ebp-6Ch]
  idToken token; // [esp+88h] [ebp-5Ch] BYREF
  int v29; // [esp+E0h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v29 = 0;
  Lexer::ExpectTokenString(src, "{");
  Lexer::ExpectAnyToken(src, &token);
  v5 = renderModelManager->AllocModel(renderModelManager);
  v5->InitEmpty(v5, token.data);
  v6 = Lexer::ParseInt(src);
  if ( v6 < 0 )
    Lexer::Error(src, "R_ParseModel: bad numSurfaces");
  if ( this->procFileVersion > 1 && v5->IsStaticWorldModel(v5) )
  {
    v7 = v5->__vftable;
    LOBYTE(v8) = Lexer::ParseBool(src);
    v7->SetHasSky(v5, v8);
  }
  if ( v6 > 0 )
  {
    v21 = v6;
    do
    {
      Lexer::ExpectTokenString(src, "{");
      Lexer::ExpectAnyToken(src, &token);
      surf.mOriginalSurfaceName = (idStr *)((int (__thiscall *)(idDeclManager *, char *, int, srfTriangles_s *, int))declManager->FindMaterial)(
                                             declManager,
                                             token.data,
                                             1,
                                             a2,
                                             a3);
      idMaterial::AddReference((idMaterial *)surf.mOriginalSurfaceName);
      v9 = R_AllocStaticTriSurf();
      v9->numVerts = Lexer::ParseInt(src);
      v10 = Lexer::ParseInt(src);
      numVerts = v9->numVerts;
      v9->numIndexes = v10;
      R_AllocStaticTriSurfVerts(v9, numVerts);
      v11 = 0;
      v22 = 0;
      if ( v9->numVerts > 0 )
      {
        do
        {
          v12 = Lexer::Parse1DMatrixOpenEnded(src, 12, &vec[2]);
          v13 = v12;
          if ( v12 != 8 && v12 != 12 )
            Lexer::Error(src, "R_ParseModel: bad vertex read");
          v9->verts[v11].xyz.x = vec[2];
          v9->verts[v11].xyz.y = vec[3];
          v9->verts[v11].xyz.z = vec[4];
          v9->verts[v11].st.x = vec[5];
          v9->verts[v11].st.y = vec[6];
          v9->verts[v11].normal.x = vec[7];
          verts = v9->verts;
          verts[v11].normal.y = vec[8];
          v9->verts[v11].normal.z = vec[9];
          if ( v13 == 12 )
          {
            vec4_8 = vec[10] * 0.0039215689;
            vec4_12 = vec[11] * 0.0039215689;
            vec[0] = *(float *)&surf.id * 0.0039215689;
            vec[1] = *(float *)&surf.shader * 0.0039215689;
            BYTE1(verts) = (int)(vec[1] * 255.0);
            LOBYTE(verts) = (int)(vec[0] * 255.0);
            v15 = (_DWORD)verts << 16;
            BYTE1(v15) = (int)(vec4_12 * 255.0);
            LOBYTE(v15) = (int)(vec4_8 * 255.0);
            *(_DWORD *)v9->verts[v11].color = v15;
          }
          else
          {
            *(_DWORD *)v9->verts[v11].color = -16777216;
          }
          ++v11;
          ++v22;
        }
        while ( v22 < v9->numVerts );
        v5 = v23;
      }
      R_AllocStaticTriSurfIndexes(v9, v9->numIndexes);
      for ( i = 0; i < v9->numIndexes; ++i )
        v9->indexes[i] = Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, "}");
      a2 = v9;
      a3 = 0;
      ((void (__thiscall *)(idRenderModel *, srfTriangles_s *, idStr *))v5->AddSurface)(
        v5,
        surf.geometry,
        surf.mOriginalSurfaceName);
      --v21;
    }
    while ( v21 );
  }
  Lexer::ExpectTokenString(src, "}");
  v5->FinishSurfaces(v5);
  v29 = -1;
  idStr::FreeData(&token);
  return v5;
}

// FUNC: public: class idRenderModel * __thiscall idRenderWorldLocal::ParseShadowModel(class Lexer *)
idRenderModel *__userpurge idRenderWorldLocal::ParseShadowModel@<eax>(
        idRenderWorldLocal *this@<ecx>,
        int a2@<edi>,
        int a3@<esi>,
        Lexer *src)
{
  int v4; // ebx
  srfTriangles_s *v5; // esi
  int v6; // ebp
  shadowCache_s *shadowVertexes; // ecx
  double x; // st7
  float *p_x; // ecx
  int i; // ebp
  int surf_4; // [esp+10h] [ebp-88h]
  const idMaterial *surf_12; // [esp+18h] [ebp-80h]
  float vec[8]; // [esp+1Ch] [ebp-7Ch] BYREF
  idToken token; // [esp+3Ch] [ebp-5Ch] BYREF
  int v16; // [esp+94h] [ebp-4h]

  token.floatvalue = 0.0;
  v4 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v16 = 0;
  Lexer::ExpectTokenString(src, "{");
  Lexer::ExpectAnyToken(src, &token);
  surf_4 = ((int (__thiscall *)(idRenderModelManager *, int, int))renderModelManager->AllocModel)(
             renderModelManager,
             a2,
             a3);
  (*(void (__thiscall **)(int, _DWORD))(*(_DWORD *)surf_4 + 16))(surf_4, *(_DWORD *)token.baseBuffer);
  surf_12 = tr.defaultMaterial;
  v5 = R_AllocStaticTriSurf();
  v5->numVerts = Lexer::ParseInt(src);
  v5->numShadowIndexesNoCaps = Lexer::ParseInt(src);
  v5->numShadowIndexesNoFrontCaps = Lexer::ParseInt(src);
  v5->numIndexes = Lexer::ParseInt(src);
  v5->shadowCapPlaneBits = Lexer::ParseInt(src);
  R_AllocStaticTriSurfShadowVerts(v5, v5->numVerts);
  v5->bounds.b[0].z = idMath::INFINITY;
  v5->bounds.b[0].y = idMath::INFINITY;
  v5->bounds.b[0].x = idMath::INFINITY;
  v5->bounds.b[1].z = -1.0e30;
  v5->bounds.b[1].y = -1.0e30;
  v5->bounds.b[1].x = -1.0e30;
  if ( v5->numVerts > 0 )
  {
    v6 = 0;
    do
    {
      Lexer::Parse1DMatrix(src, 3, &vec[2]);
      v5->shadowVertexes[v6].xyz.x = vec[2];
      v5->shadowVertexes[v6].xyz.y = vec[3];
      v5->shadowVertexes[v6].xyz.z = vec[4];
      v5->shadowVertexes[v6].xyz.w = 1.0;
      shadowVertexes = v5->shadowVertexes;
      x = shadowVertexes[v6].xyz.x;
      p_x = &shadowVertexes[v6].xyz.x;
      if ( x < v5->bounds.b[0].x )
        v5->bounds.b[0].x = *p_x;
      if ( *p_x > (double)v5->bounds.b[1].x )
        v5->bounds.b[1].x = *p_x;
      if ( p_x[1] < (double)v5->bounds.b[0].y )
        v5->bounds.b[0].y = p_x[1];
      if ( p_x[1] > (double)v5->bounds.b[1].y )
        v5->bounds.b[1].y = p_x[1];
      if ( p_x[2] < (double)v5->bounds.b[0].z )
        v5->bounds.b[0].z = p_x[2];
      if ( p_x[2] > (double)v5->bounds.b[1].z )
        v5->bounds.b[1].z = p_x[2];
      ++v4;
      ++v6;
    }
    while ( v4 < v5->numVerts );
  }
  R_AllocStaticTriSurfIndexes(v5, v5->numIndexes);
  for ( i = 0; i < v5->numIndexes; ++i )
    v5->indexes[i] = Lexer::ParseInt(src);
  (*(void (__thiscall **)(int))(*(_DWORD *)surf_4 + 24))(surf_4);
  Lexer::ExpectTokenString(src, "}");
  v16 = -1;
  idStr::FreeData(&token);
  return (idRenderModel *)surf_4;
}

// FUNC: public: void __thiscall idRenderWorldLocal::ParseNodes(class Lexer *)
void __thiscall idRenderWorldLocal::ParseNodes(idRenderWorldLocal *this, Lexer *src)
{
  int v4; // eax
  int v5; // ebp
  areaNode_t *v6; // esi
  Lexer *srca; // [esp+10h] [ebp+4h]

  Lexer::ExpectTokenString(src, "{");
  v4 = Lexer::ParseInt(src);
  v5 = 0;
  this->numAreaNodes = v4;
  if ( v4 < 0 )
    Lexer::Error(src, "R_ParseNodes: bad numAreaNodes");
  this->areaNodes = (areaNode_t *)R_ClearedStaticAlloc(28 * this->numAreaNodes);
  session->PacifierUpdate(session);
  if ( this->numAreaNodes > 0 )
  {
    srca = 0;
    do
    {
      v6 = (areaNode_t *)((char *)srca + (unsigned int)this->areaNodes);
      Lexer::Parse1DMatrix(src, 4, &v6->plane.a);
      v6->children[0] = Lexer::ParseInt(src);
      srca = (Lexer *)((char *)srca + 28);
      ++v5;
      v6->children[1] = Lexer::ParseInt(src);
    }
    while ( v5 < this->numAreaNodes );
  }
  Lexer::ExpectTokenString(src, "}");
}

// FUNC: public: void __thiscall idRenderWorldLocal::ClearWorld(void)
void __thiscall idRenderWorldLocal::ClearWorld(idRenderWorldLocal *this)
{
  areaNode_t *v2; // eax

  this->numPortalAreas = 1;
  this->portalAreas = (portalArea_s *)R_ClearedStaticAlloc(120);
  this->areaScreenRect = (idScreenRect *)R_ClearedStaticAlloc(16);
  idRenderWorldLocal::SetupAreaRefs(this);
  v2 = (areaNode_t *)R_ClearedStaticAlloc(28);
  this->areaNodes = v2;
  v2->plane.d = 1.0;
  this->areaNodes->children[0] = -1;
  this->areaNodes->children[1] = -1;
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::FreeDefs(void)
void __thiscall idRenderWorldLocal::FreeDefs(idRenderWorldLocal *this)
{
  int v2; // edi
  bool v3; // cc
  idRenderLightLocal *v4; // eax
  int i; // edi
  idRenderEntityLocal *v6; // eax
  int j; // edi
  rvRenderEffectLocal *v8; // eax

  v2 = 0;
  v3 = this->lightDefs.num <= 0;
  this->generateAllInteractionsCalled = 0;
  if ( !v3 )
  {
    do
    {
      v4 = this->lightDefs.list[v2];
      if ( v4 && v4->world == this )
      {
        this->FreeLightDef(this, v2);
        this->lightDefs.list[v2] = 0;
      }
      ++v2;
    }
    while ( v2 < this->lightDefs.num );
  }
  for ( i = 0; i < this->entityDefs.num; ++i )
  {
    v6 = this->entityDefs.list[i];
    if ( v6 && v6->world == this )
    {
      this->FreeEntityDef(this, i);
      this->entityDefs.list[i] = 0;
    }
  }
  for ( j = 0; j < this->effectDefs.num; ++j )
  {
    v8 = this->effectDefs.list[j];
    if ( v8 && v8->world == this )
    {
      this->FreeEffectDef(this, j);
      this->effectDefs.list[j] = 0;
    }
  }
  if ( this->markedEntityDefs.list )
    Memory::Free(this->markedEntityDefs.list);
  this->markedEntityDefs.list = 0;
  this->markedEntityDefs.num = 0;
  this->markedEntityDefs.size = 0;
  if ( this->markedLightDefs.list )
    Memory::Free(this->markedLightDefs.list);
  this->markedLightDefs.list = 0;
  this->markedLightDefs.num = 0;
  this->markedLightDefs.size = 0;
  if ( this->markedEffectDefs.list )
    Memory::Free(this->markedEffectDefs.list);
  this->markedEffectDefs.list = 0;
  this->markedEffectDefs.num = 0;
  this->markedEffectDefs.size = 0;
}

// FUNC: private: void __thiscall idRenderWorldLocal::ConvertProcToMD5R(void)
void __thiscall idRenderWorldLocal::ConvertProcToMD5R(idRenderWorldLocal *this)
{
  int num; // esi
  int *v3; // eax
  rvRenderModelMD5R *v4; // ebp
  rvRenderModelMD5R *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // esi
  int v8; // edx
  int v9; // ecx
  int v10; // ebx
  int v11; // ebp
  rvIndexBuffer *p_m_lockIndexOffset; // esi
  _DWORD *m_flags; // eax
  int v14; // edx
  bool v15; // cc
  int v16; // esi
  int v17; // ecx
  int v18; // eax
  int m_numVertexBuffers; // esi
  int *v20; // eax
  rvVertexBuffer *v21; // ebx
  rvVertexBuffer *v22; // eax
  int v23; // eax
  bool v24; // zf
  bool v25; // sf
  int m_numIndexBuffers; // esi
  int *v27; // eax
  rvIndexBuffer *v28; // ebx
  rvIndexBuffer *v29; // eax
  silEdge_t *v30; // eax
  int v31; // ebp
  int v32; // ebx
  _DWORD *v33; // eax
  _DWORD *v34; // esi
  int v35; // edx
  int v36; // ecx
  int v37; // ebp
  int v38; // ebx
  _DWORD *v39; // esi
  _DWORD *v40; // eax
  int v41; // edx
  int v42; // ecx
  int v43; // ebp
  int v44; // ebx
  int v45; // esi
  int v46; // eax
  int v47; // ebx
  idRenderModelStatic *v48; // eax
  rvRenderModelMD5R *v49; // esi
  idRenderModelStatic *v50; // ebp
  rvRenderModelMD5R_vtbl *v51; // ebp
  int v52; // eax
  rvIndexBuffer *v53; // esi
  int v54; // esi
  rvRenderModelMD5R *m_models; // ebx
  rvRenderModelMD5R_vtbl *v56; // edx
  rvRenderModelMD5R *v57; // ebx
  int numDrawVerts; // [esp+10h] [ebp-120h]
  int numDrawVertsa; // [esp+10h] [ebp-120h]
  int numModelShadowIndices; // [esp+14h] [ebp-11Ch]
  int numModelShadowIndicesa; // [esp+14h] [ebp-11Ch]
  int numModelShadowIndicesb; // [esp+14h] [ebp-11Ch]
  int shadowIndexArrayOffset; // [esp+18h] [ebp-118h]
  int shadowIndexArrayOffseta; // [esp+18h] [ebp-118h]
  int shadowIndexArrayOffsetb; // [esp+18h] [ebp-118h]
  int shadowIndexArrayOffsetc; // [esp+18h] [ebp-118h]
  int curModel; // [esp+1Ch] [ebp-114h]
  int curModela; // [esp+1Ch] [ebp-114h]
  idRenderModel *curModelb; // [esp+1Ch] [ebp-114h]
  int numShadowVerts; // [esp+20h] [ebp-110h]
  int numShadowVertsa; // [esp+20h] [ebp-110h]
  int shadowVertArrayOffset; // [esp+24h] [ebp-10Ch]
  int shadowVertArrayOffseta; // [esp+24h] [ebp-10Ch]
  int shadowVertArrayOffsetb; // [esp+24h] [ebp-10Ch]
  int numIndices; // [esp+28h] [ebp-108h]
  int numIndicesa; // [esp+28h] [ebp-108h]
  int numIndicesb; // [esp+28h] [ebp-108h]
  int curSurface; // [esp+2Ch] [ebp-104h]
  int curSurfacea; // [esp+2Ch] [ebp-104h]
  int curSurfaceb; // [esp+2Ch] [ebp-104h]
  int numShadowIndices; // [esp+30h] [ebp-100h]
  int numShadowIndicesa; // [esp+30h] [ebp-100h]
  int startModel; // [esp+34h] [ebp-FCh]
  int startModela; // [esp+34h] [ebp-FCh]
  rvIndexBuffer *indexBufferSet; // [esp+38h] [ebp-F8h]
  rvIndexBuffer *indexBufferSeta; // [esp+38h] [ebp-F8h]
  int endModel; // [esp+3Ch] [ebp-F4h]
  int indexBufferStart; // [esp+40h] [ebp-F0h]
  int vertexBufferStart; // [esp+44h] [ebp-ECh]
  rvVertexBuffer *vertexBufferSet; // [esp+48h] [ebp-E8h]
  int numSilEdgesAdded; // [esp+4Ch] [ebp-E4h]
  int texDimArray[7]; // [esp+50h] [ebp-E0h] BYREF
  rvVertexFormat vertexFormat; // [esp+6Ch] [ebp-C4h] BYREF
  int v94; // [esp+12Ch] [ebp-4h]

  rvVertexFormat::rvVertexFormat(&vertexFormat);
  num = this->localModels.num;
  v94 = 0;
  texDimArray[0] = 2;
  memset(&texDimArray[1], 0, 24);
  this->m_numVertexBuffers = 0;
  this->m_numIndexBuffers = 0;
  numDrawVerts = 0;
  numShadowVerts = 0;
  numIndices = 0;
  numShadowIndices = 0;
  startModel = 0;
  this->m_numModels = num;
  v3 = (int *)Memory::Allocate(196 * num + 4);
  LOBYTE(v94) = 1;
  if ( v3 )
  {
    v4 = (rvRenderModelMD5R *)(v3 + 1);
    *v3 = num;
    `eh vector constructor iterator'(
      v3 + 1,
      0xC4u,
      num,
      (void (__thiscall *)(void *))rvRenderModelMD5R::rvRenderModelMD5R,
      (void (__thiscall *)(void *))rvRenderModelMD5R::~rvRenderModelMD5R);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v94) = 0;
  this->m_models = v5;
  if ( !v5 )
    idLib::common->FatalError(idLib::common, "Out of memory");
  curModel = 0;
  if ( this->localModels.num <= 0 )
    goto LABEL_91;
  do
  {
    session->PacifierUpdate(session);
    v6 = __RTDynamicCast(
           this->localModels.list[curModel],
           0,
           &idRenderModel `RTTI Type Descriptor',
           &idRenderModelStatic `RTTI Type Descriptor',
           0);
    v7 = v6;
    if ( v6 && !(*(unsigned __int8 (__thiscall **)(_DWORD *))(*v6 + 120))(v6) )
    {
      v8 = v7[2];
      v9 = 0;
      v10 = 0;
      v11 = 0;
      numModelShadowIndices = 0;
      shadowVertArrayOffset = 0;
      curSurface = 0;
      shadowIndexArrayOffset = v8;
      if ( v8 <= 0 )
        goto LABEL_19;
      p_m_lockIndexOffset = (rvIndexBuffer *)(v7[5] + 8);
      indexBufferSet = p_m_lockIndexOffset;
      do
      {
        m_flags = (_DWORD *)p_m_lockIndexOffset->m_flags;
        if ( p_m_lockIndexOffset->m_flags )
        {
          if ( m_flags[27] )
          {
            v9 += m_flags[9];
            numModelShadowIndices += m_flags[13];
          }
          else
          {
            v14 = m_flags[9];
            shadowVertArrayOffset += v14;
            v10 += m_flags[20];
            v11 += m_flags[13];
            v9 += 2 * v14;
            v8 = shadowIndexArrayOffset;
          }
        }
        p_m_lockIndexOffset = (rvIndexBuffer *)&indexBufferSet->m_lockIndexOffset;
        v15 = ++curSurface < v8;
        indexBufferSet = (rvIndexBuffer *)((char *)indexBufferSet + 16);
      }
      while ( v15 );
      if ( !shadowVertArrayOffset && v9 && numDrawVerts )
      {
        v16 = numShadowVerts;
      }
      else
      {
LABEL_19:
        v16 = numShadowVerts;
        v17 = numShadowVerts + v9;
        if ( v17 <= 0x8000 || !numShadowVerts )
        {
          numDrawVerts += shadowVertArrayOffset;
          numIndices += v11;
          numShadowVerts = v17;
          numShadowIndices += numModelShadowIndices;
          startModel += v10;
          goto LABEL_22;
        }
      }
      numIndices = 0;
      v23 = numDrawVerts > 0;
      numShadowVerts = 0;
      numDrawVerts = 0;
      v23 *= 2;
      this->m_numVertexBuffers += v23 + (v16 > 0);
      v24 = numShadowIndices == 0;
      v25 = numShadowIndices < 0;
      numShadowIndices = 0;
      this->m_numIndexBuffers += v23 + (!v25 && !v24);
      --curModel;
    }
LABEL_22:
    ++curModel;
  }
  while ( curModel < this->localModels.num );
  if ( numDrawVerts || numShadowVerts )
  {
    v18 = 2 * (numDrawVerts > 0);
    this->m_numVertexBuffers += v18 + (numShadowVerts > 0);
    m_numVertexBuffers = this->m_numVertexBuffers;
    this->m_numIndexBuffers += v18 + (numShadowIndices > 0);
    v20 = (int *)Memory::Allocate(472 * m_numVertexBuffers + 4);
    LOBYTE(v94) = 2;
    if ( v20 )
    {
      v21 = (rvVertexBuffer *)(v20 + 1);
      *v20 = m_numVertexBuffers;
      `eh vector constructor iterator'(
        v20 + 1,
        0x1D8u,
        m_numVertexBuffers,
        (void (__thiscall *)(void *))rvVertexBuffer::rvVertexBuffer,
        (void (__thiscall *)(void *))rvVertexBuffer::~rvVertexBuffer);
      v22 = v21;
    }
    else
    {
      v22 = 0;
    }
    LOBYTE(v94) = 0;
    this->m_vertexBuffers = v22;
    if ( !v22 )
      idLib::common->FatalError(idLib::common, "Out of memory");
    m_numIndexBuffers = this->m_numIndexBuffers;
    vertexBufferStart = 0;
    v27 = (int *)Memory::Allocate(36 * m_numIndexBuffers + 4);
    LOBYTE(v94) = 3;
    if ( v27 )
    {
      v28 = (rvIndexBuffer *)(v27 + 1);
      *v27 = m_numIndexBuffers;
      `eh vector constructor iterator'(
        v27 + 1,
        0x24u,
        m_numIndexBuffers,
        (void (__thiscall *)(void *))rvIndexBuffer::rvIndexBuffer,
        (void (__thiscall *)(void *))rvIndexBuffer::~rvIndexBuffer);
      v29 = v28;
    }
    else
    {
      v29 = 0;
    }
    LOBYTE(v94) = 0;
    this->m_indexBuffers = v29;
    if ( !v29 )
      idLib::common->FatalError(idLib::common, "Out of memory");
    this->m_numSilEdges = startModel;
    indexBufferStart = 0;
    numSilEdgesAdded = 0;
    v30 = (silEdge_t *)Memory::Allocate(16 * startModel);
    this->m_silEdges = v30;
    if ( !v30 )
      idLib::common->FatalError(idLib::common, "Out of memory");
    vertexBufferSet = this->m_vertexBuffers;
    indexBufferSeta = this->m_indexBuffers;
    startModela = 0;
    if ( this->localModels.num <= 0 )
      goto LABEL_90;
    while ( 1 )
    {
      v31 = this->localModels.num;
      v32 = startModela;
      numDrawVertsa = 0;
      numShadowVertsa = 0;
      numIndicesa = 0;
      numShadowIndicesa = 0;
      endModel = v31;
      curModela = startModela;
      if ( startModela >= v31 )
        goto LABEL_59;
      while ( 1 )
      {
        v33 = __RTDynamicCast(
                this->localModels.list[v32],
                0,
                &idRenderModel `RTTI Type Descriptor',
                &idRenderModelStatic `RTTI Type Descriptor',
                0);
        v34 = v33;
        if ( !v33 || (*(unsigned __int8 (__thiscall **)(_DWORD *))(*v33 + 120))(v33) )
          goto LABEL_56;
        v35 = v34[2];
        v36 = 0;
        v37 = 0;
        v38 = 0;
        numModelShadowIndicesa = 0;
        shadowVertArrayOffseta = 0;
        curSurfacea = 0;
        shadowIndexArrayOffseta = v35;
        if ( v35 > 0 )
        {
          v39 = (_DWORD *)(v34[5] + 8);
          do
          {
            v40 = (_DWORD *)*v39;
            if ( *v39 )
            {
              if ( v40[27] )
              {
                v36 += v40[9];
                v37 += v40[13];
                numModelShadowIndicesa = v37;
              }
              else
              {
                v41 = v40[9];
                shadowVertArrayOffseta += v41;
                v38 += v40[13];
                v37 = numModelShadowIndicesa;
                v36 += 2 * v41;
                v35 = shadowIndexArrayOffseta;
              }
            }
            v39 += 4;
            ++curSurfacea;
          }
          while ( curSurfacea < v35 );
          if ( !shadowVertArrayOffseta && v36 && numDrawVertsa )
            break;
        }
        v42 = numShadowVertsa + v36;
        if ( v42 > 0x8000 )
        {
          if ( numShadowVertsa )
            break;
        }
        numIndicesa += v38;
        numDrawVertsa += shadowVertArrayOffseta;
        numShadowIndicesa += v37;
        v32 = curModela;
        v31 = endModel;
        numShadowVertsa = v42;
LABEL_56:
        curModela = ++v32;
        if ( v32 >= v31 )
          goto LABEL_59;
      }
      endModel = curModela;
LABEL_59:
      v43 = 0;
      curSurfaceb = 0;
      shadowVertArrayOffsetb = 0;
      if ( numDrawVertsa )
      {
        rvVertexFormat::Init(&vertexFormat, 1u, 4, 0, 1, 0, 0);
        v44 = vertexBufferStart;
        rvVertexBuffer::Init(&vertexBufferSet[vertexBufferStart], &vertexFormat, numDrawVertsa, 0x41u);
        rvVertexFormat::Init(&vertexFormat, 0x4F1u, 4, 0, 1, texDimArray, 0);
        rvVertexBuffer::Init(&vertexBufferSet[vertexBufferStart + 1], &vertexFormat, numDrawVertsa, 0x83u);
        v43 = 2;
        curSurfaceb = 2;
        shadowVertArrayOffsetb = 2;
        v45 = 256;
      }
      else
      {
        v44 = vertexBufferStart;
        v45 = 512;
      }
      if ( numShadowVertsa )
      {
        rvVertexFormat::Init(&vertexFormat, 1u, 4, 0, 1, 0, 0);
        rvVertexBuffer::Init(&vertexBufferSet[v44 + v43], &vertexFormat, numShadowVertsa, v45 | 2);
        ++curSurfaceb;
      }
      v46 = 0;
      numModelShadowIndicesb = 0;
      shadowIndexArrayOffsetb = 0;
      if ( numDrawVertsa )
      {
        rvIndexBuffer::Init(&indexBufferSeta[indexBufferStart], numIndicesa, 1u);
        rvIndexBuffer::Init(&indexBufferSeta[indexBufferStart + 1], numIndicesa, 3u);
        v46 = 2;
        numModelShadowIndicesb = 2;
        shadowIndexArrayOffsetb = 2;
      }
      if ( numShadowIndicesa )
      {
        rvIndexBuffer::Init(&indexBufferSeta[indexBufferStart + v46], numShadowIndicesa, 2u);
        ++numModelShadowIndicesb;
      }
      v47 = startModela;
      if ( startModela < endModel )
      {
        numIndicesb = startModela;
        do
        {
          curModelb = this->localModels.list[v47];
          v48 = (idRenderModelStatic *)__RTDynamicCast(
                                         curModelb,
                                         0,
                                         &idRenderModel `RTTI Type Descriptor',
                                         &idRenderModelStatic `RTTI Type Descriptor',
                                         0);
          v49 = &this->m_models[numIndicesb];
          v50 = v48;
          if ( !v48 || v48->IsDefaultModel(v48) )
          {
            v51 = v49->__vftable;
            v52 = (int)curModelb->Name(curModelb);
            v51->InitEmpty(v49, (const char *)v52);
          }
          else if ( rvRenderModelMD5R::Init(
                      v49,
                      v50,
                      vertexBufferSet,
                      vertexBufferStart,
                      curSurfaceb,
                      indexBufferSeta,
                      indexBufferStart,
                      numModelShadowIndicesb,
                      this->m_silEdges,
                      numSilEdgesAdded,
                      this->m_numSilEdges,
                      5) )
          {
            numSilEdgesAdded = v49->m_numSilEdgesAdded;
          }
          if ( curModelb )
            ((void (__thiscall *)(idRenderModel *, int))curModelb->~idRenderModel)(curModelb, 1);
          renderModelManager->AddModel(renderModelManager, v49);
          ++numIndicesb;
          this->localModels.list[v47++] = v49;
        }
        while ( v47 < endModel );
      }
      if ( numDrawVertsa )
      {
        rvVertexBuffer::Resize(
          &vertexBufferSet[vertexBufferStart],
          vertexBufferSet[vertexBufferStart].m_numVerticesWritten);
        rvVertexBuffer::Resize(
          &vertexBufferSet[vertexBufferStart + 1],
          vertexBufferSet[vertexBufferStart + 1].m_numVerticesWritten);
        v53 = &indexBufferSeta[indexBufferStart];
        rvIndexBuffer::Resize(v53, v53->m_numIndicesWritten);
        rvIndexBuffer::Resize(v53 + 1, v53[1].m_numIndicesWritten);
      }
      if ( numShadowVertsa )
        rvVertexBuffer::Resize(
          &vertexBufferSet[shadowVertArrayOffsetb + vertexBufferStart],
          vertexBufferSet[shadowVertArrayOffsetb + vertexBufferStart].m_numVerticesWritten);
      if ( numShadowIndicesa )
        rvIndexBuffer::Resize(
          &indexBufferSeta[indexBufferStart + shadowIndexArrayOffsetb],
          indexBufferSeta[indexBufferStart + shadowIndexArrayOffsetb].m_numIndicesWritten);
      if ( startModela < endModel )
      {
        v54 = startModela;
        shadowIndexArrayOffsetc = endModel - startModela;
        do
        {
          m_models = this->m_models;
          v56 = m_models[v54].__vftable;
          v57 = &m_models[v54];
          if ( !v56->IsDefaultModel(v57) )
            rvRenderModelMD5R::GenerateStaticSurfaces(v57);
          ++v54;
          --shadowIndexArrayOffsetc;
        }
        while ( shadowIndexArrayOffsetc );
      }
      indexBufferStart += numModelShadowIndicesb;
      vertexBufferStart += curSurfaceb;
      startModela = endModel;
      if ( endModel >= this->localModels.num )
      {
LABEL_90:
        this->m_convertedMD5R = 1;
        break;
      }
    }
  }
LABEL_91:
  v94 = -1;
  rvVertexFormat::Shutdown(&vertexFormat);
}

// FUNC: private: void __thiscall idRenderWorldLocal::WriteInterAreaPortals(class idFile &)
void __thiscall idRenderWorldLocal::WriteInterAreaPortals(idRenderWorldLocal *this, idFile *outFile)
{
  idRenderWorldLocal *v2; // edi
  int numInterAreaPortals; // eax
  doublePortal_s *v4; // eax
  idWinding *w; // edi
  int v6; // ebx
  idImage *image; // eax
  int v8; // [esp+24h] [ebp-14h]
  int curPortal; // [esp+28h] [ebp-10h]
  int v10; // [esp+2Ch] [ebp-Ch]
  portal_s *p0; // [esp+34h] [ebp-4h]

  v2 = this;
  numInterAreaPortals = this->numInterAreaPortals;
  if ( numInterAreaPortals )
  {
    outFile->WriteFloatString(
      outFile,
      "interAreaPortals { /* numAreas = */ %i /* numIAP = */ %i\r\n\r\n",
      this->numPortalAreas,
      numInterAreaPortals);
    outFile->WriteFloatString(
      outFile,
      "/* interAreaPortal format is: numPoints positiveSideArea negativeSideArea ( point ) ... ( point ) [( fadeImage dis"
      "tanceNear distanceFar )] */\n");
    curPortal = 0;
    if ( v2->numInterAreaPortals > 0 )
    {
      v10 = 0;
      while ( 1 )
      {
        v4 = &v2->doublePortals[v10];
        w = v4->portals[0]->w;
        p0 = v4->portals[0];
        outFile->WriteFloatString(
          outFile,
          "/* iap %i */ %i %i %i ",
          curPortal,
          w->numPoints,
          v4->portals[1]->intoArea,
          v4->portals[0]->intoArea);
        v6 = 0;
        if ( w->numPoints > 0 )
        {
          v8 = 0;
          do
          {
            outFile->WriteFloatString(outFile, "( %f %f %f ) ", w->p[v8].x, w->p[v8].y, w->p[v8].z);
            ++v8;
            ++v6;
          }
          while ( v6 < w->numPoints );
        }
        image = p0->image;
        if ( image )
        {
          outFile->WriteFloatString(outFile, "( \"%s\" ", image->imgName.data);
          outFile->WriteFloatString(outFile, "%.2f %.2f )", p0->cullNear, p0->cullFar);
        }
        outFile->WriteFloatString(outFile, "\n");
        ++v10;
        if ( ++curPortal >= this->numInterAreaPortals )
          break;
        v2 = this;
      }
    }
    outFile->WriteFloatString(outFile, "}\n\n");
  }
}

// FUNC: private: void __thiscall idRenderWorldLocal::WriteNodes(class idFile &)
void __thiscall idRenderWorldLocal::WriteNodes(idRenderWorldLocal *this, idFile *outFile)
{
  idRenderWorldLocal *v2; // esi
  int v4; // ebx
  areaNode_t *v5; // esi
  int v6; // [esp+30h] [ebp-8h]

  v2 = this;
  outFile->WriteFloatString(outFile, "nodes { /* numNodes = */ %i\n\n", this->numAreaNodes);
  outFile->WriteFloatString(outFile, "/* node format is: ( planeVector ) positiveChild negativeChild */\n");
  outFile->WriteFloatString(outFile, "/* a child number of 0 is an opaque, solid area */\n");
  outFile->WriteFloatString(outFile, "/* negative child numbers are areas: (-1-child) */\n");
  v4 = 0;
  if ( v2->numAreaNodes > 0 )
  {
    v6 = 0;
    while ( 1 )
    {
      v5 = &v2->areaNodes[v6];
      outFile->WriteFloatString(outFile, "/* node %i */ ", v4);
      outFile->WriteFloatString(outFile, "( %f %f %f %f ) ", v5->plane.a, v5->plane.b, v5->plane.c, v5->plane.d);
      outFile->WriteFloatString(outFile, "%i %i\n", v5->children[0], v5->children[1]);
      ++v6;
      if ( ++v4 >= this->numAreaNodes )
        break;
      v2 = this;
    }
  }
  outFile->WriteFloatString(outFile, "}");
}

// FUNC: public: void __thiscall idRenderWorldLocal::ParseInterAreaPortals(class Lexer *)
void __thiscall idRenderWorldLocal::ParseInterAreaPortals(idRenderWorldLocal *this, Lexer *src)
{
  int v4; // eax
  portalArea_s *v5; // eax
  int v6; // eax
  int v7; // esi
  idWinding *v8; // ebp
  bool v9; // cc
  int v10; // esi
  portal_s *v11; // esi
  int v12; // eax
  portal_s *v13; // esi
  idWinding *v14; // eax
  int v15; // eax
  int v16; // [esp+10h] [ebp-8Ch]
  float cullNear; // [esp+24h] [ebp-78h]
  float cullFar; // [esp+28h] [ebp-74h]
  int numPoints; // [esp+2Ch] [ebp-70h]
  idImage *numPointsa; // [esp+2Ch] [ebp-70h]
  int a1; // [esp+30h] [ebp-6Ch]
  int a2; // [esp+34h] [ebp-68h]
  int i; // [esp+38h] [ebp-64h]
  idToken token; // [esp+40h] [ebp-5Ch] BYREF
  int v25; // [esp+98h] [ebp-4h]
  Lexer *srca; // [esp+A0h] [ebp+4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v25 = 0;
  Lexer::ExpectTokenString(src, "{");
  v4 = Lexer::ParseInt(src);
  this->numPortalAreas = v4;
  if ( v4 >= 0 )
  {
    v5 = (portalArea_s *)R_ClearedStaticAlloc(120 * v4);
    v16 = 16 * this->numPortalAreas;
    this->portalAreas = v5;
    this->areaScreenRect = (idScreenRect *)R_ClearedStaticAlloc(v16);
    idRenderWorldLocal::SetupAreaRefs(this);
    v6 = Lexer::ParseInt(src);
    this->numInterAreaPortals = v6;
    if ( v6 >= 0 )
    {
      this->doublePortals = (doublePortal_s *)R_ClearedStaticAlloc(20 * v6);
      session->PacifierUpdate(session);
      i = 0;
      if ( this->numInterAreaPortals > 0 )
      {
        srca = 0;
        do
        {
          v7 = Lexer::ParseInt(src);
          numPoints = v7;
          a1 = Lexer::ParseInt(src);
          a2 = Lexer::ParseInt(src);
          v8 = (idWinding *)Memory::Allocate(0x10u);
          LOBYTE(v25) = 1;
          if ( v8 )
          {
            v8->__vftable = (idWinding_vtbl *)&idWinding::`vftable';
            v8->allocedSize = 0;
            v8->numPoints = 0;
            v8->p = 0;
            if ( v7 > 0 )
              idWinding::ReAllocate(v8, v7, 0);
          }
          else
          {
            v8 = 0;
          }
          v9 = v7 <= v8->allocedSize;
          LOBYTE(v25) = 0;
          if ( v9 || v8->ReAllocate(v8, v7, 1) )
            v8->numPoints = v7;
          if ( v7 > 0 )
          {
            v10 = 0;
            do
            {
              Lexer::Parse1DMatrix(src, 3, &v8->p[v10].x);
              v8->p[v10].s = 0.0;
              v8->p[v10++].t = 0.0;
              --numPoints;
            }
            while ( numPoints );
          }
          cullNear = 262144.0;
          cullFar = 262144.0;
          numPointsa = 0;
          if ( this->procFileVersion == 3 )
          {
            cullNear = Lexer::ParseFloat(src, 0);
            cullFar = Lexer::ParseFloat(src, 0);
          }
          if ( this->procFileVersion >= 4 )
          {
            Lexer::ReadToken(src, &token);
            if ( idStr::Icmp(token.data, "(") )
            {
              Lexer::UnreadToken(src, &token);
            }
            else
            {
              Lexer::ReadToken(src, &token);
              numPointsa = globalImages->ImageFromFile(globalImages, token.data, 2, 1, 1, 2, 0, 0);
              cullNear = Lexer::ParseFloat(src, 0);
              cullFar = Lexer::ParseFloat(src, 0);
              Lexer::ExpectTokenString(src, ")");
            }
          }
          v11 = (portal_s *)R_ClearedStaticAlloc(44);
          v11->intoArea = a2;
          v11->doublePortal = (doublePortal_s *)((char *)srca + (unsigned int)this->doublePortals);
          v11->w = v8;
          idWinding::GetPlane(v8, &v11->plane);
          v11->image = numPointsa;
          v11->cullNear = cullNear;
          v11->cullFar = cullFar;
          v12 = a1;
          v11->next = this->portalAreas[a1].portals;
          this->portalAreas[v12].portals = v11;
          ++this->portalAreas[v12].numPortals;
          *(idFile **)((char *)&srca->mFile + (unsigned int)this->doublePortals) = (idFile *)v11;
          v13 = (portal_s *)R_ClearedStaticAlloc(44);
          v13->intoArea = a1;
          v13->doublePortal = (doublePortal_s *)((char *)srca + (unsigned int)this->doublePortals);
          v14 = idWinding::Reverse(v8);
          v13->w = v14;
          idWinding::GetPlane(v14, &v13->plane);
          v13->cullFar = cullFar;
          v13->image = numPointsa;
          v13->cullNear = cullNear;
          v15 = a2;
          v13->next = this->portalAreas[a2].portals;
          this->portalAreas[v15].portals = v13;
          ++this->portalAreas[v15].numPortals;
          *(unsigned int *)((char *)&srca->offset + (unsigned int)this->doublePortals) = (unsigned int)v13;
          ++i;
          srca = (Lexer *)((char *)srca + 20);
        }
        while ( i < this->numInterAreaPortals );
      }
      Lexer::ExpectTokenString(src, "}");
    }
    else
    {
      Lexer::Error(src, "R_ParseInterAreaPortals: bad numInterAreaPortals");
    }
  }
  else
  {
    Lexer::Error(src, "R_ParseInterAreaPortals: bad numPortalAreas");
  }
  v25 = -1;
  idStr::FreeData(&token);
}

// FUNC: private: void __thiscall idRenderWorldLocal::ParseModels(class Lexer &)
void __thiscall idRenderWorldLocal::ParseModels(idRenderWorldLocal *this, Lexer *lex)
{
  rvRenderModelMD5R *v2; // ebx
  int m_numModels; // ebp
  int *v6; // eax
  int v7; // ebp
  int granularity; // eax
  bool v9; // cc
  int i; // eax
  int size; // ecx
  int v12; // ecx
  idRenderModel **list; // ebx
  int j; // eax
  rvRenderModelMD5R *v15; // [esp+8h] [ebp-60h]
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v17; // [esp+64h] [ebp-4h]
  Lexer *lexa; // [esp+6Ch] [ebp+4h]

  token.floatvalue = 0.0;
  v2 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v17 = 0;
  Lexer::ExpectTokenString(lex, "[");
  this->m_numModels = Lexer::ParseInt(lex);
  Lexer::ExpectTokenString(lex, "]");
  Lexer::ExpectTokenString(lex, "{");
  m_numModels = this->m_numModels;
  v6 = (int *)Memory::Allocate(196 * m_numModels + 4);
  LOBYTE(v17) = 1;
  if ( v6 )
  {
    v2 = (rvRenderModelMD5R *)(v6 + 1);
    *v6 = m_numModels;
    `eh vector constructor iterator'(
      v6 + 1,
      0xC4u,
      m_numModels,
      (void (__thiscall *)(void *))rvRenderModelMD5R::rvRenderModelMD5R,
      (void (__thiscall *)(void *))rvRenderModelMD5R::~rvRenderModelMD5R);
  }
  v7 = 0;
  LOBYTE(v17) = 0;
  this->m_models = v2;
  if ( !v2 )
    Lexer::Error(lex, "Out of memory");
  session->PacifierUpdate(session);
  for ( lexa = 0; (int)lexa < this->m_numModels; lexa = (Lexer *)((char *)lexa + 1) )
  {
    Lexer::ExpectTokenString(lex, "Model");
    Lexer::ReadToken(lex, &token);
    this->m_models[v7].InitEmpty(&this->m_models[v7], token.data);
    Lexer::ExpectTokenString(lex, "{");
    rvRenderModelMD5R::Init(
      &this->m_models[v7],
      lex,
      this->m_vertexBuffers,
      this->m_numVertexBuffers,
      this->m_indexBuffers,
      this->m_numIndexBuffers,
      this->m_silEdges,
      this->m_numSilEdges,
      MD5R_SOURCE_FILE);
    Lexer::ExpectTokenString(lex, "}");
    renderModelManager->AddModel(renderModelManager, &this->m_models[v7]);
    v15 = &this->m_models[v7];
    if ( !this->localModels.list )
    {
      granularity = this->localModels.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->localModels.size )
        {
          v9 = granularity < this->localModels.num;
          this->localModels.size = granularity;
          if ( v9 )
            this->localModels.num = granularity;
          this->localModels.list = (idRenderModel **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->localModels.num; ++i )
            this->localModels.list[i] = *(idRenderModel **)(4 * i);
        }
      }
      else
      {
        this->localModels.list = 0;
        this->localModels.num = 0;
        this->localModels.size = 0;
      }
    }
    size = this->localModels.size;
    if ( this->localModels.num == size )
    {
      if ( !this->localModels.granularity )
        this->localModels.granularity = 16;
      v12 = this->localModels.granularity
          + size
          - (this->localModels.granularity + size) % this->localModels.granularity;
      if ( v12 > 0 )
      {
        if ( v12 != this->localModels.size )
        {
          v9 = v12 < this->localModels.num;
          list = this->localModels.list;
          this->localModels.size = v12;
          if ( v9 )
            this->localModels.num = v12;
          this->localModels.list = (idRenderModel **)Memory::Allocate(4 * v12);
          for ( j = 0; j < this->localModels.num; ++j )
            this->localModels.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->localModels.list )
          Memory::Free(this->localModels.list);
        this->localModels.list = 0;
        this->localModels.num = 0;
        this->localModels.size = 0;
      }
    }
    this->localModels.list[this->localModels.num++] = v15;
    ++v7;
  }
  Lexer::ExpectTokenString(lex, "}");
  v17 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: bool __thiscall idRenderWorldLocal::WriteMD5R(bool)
char __thiscall idRenderWorldLocal::WriteMD5R(idRenderWorldLocal *this, bool compressed)
{
  idFile *v3; // eax
  idFile *v4; // esi
  int v5; // edx
  _BYTE v7[32]; // [esp-20h] [ebp-28h] BYREF

  if ( !this->m_convertedMD5R || !idStr::Cmp(this->m_filename.data, &entityFilter) )
    return 0;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "writing %s\n",
    this->m_filename.data);
  v3 = fileSystem->OpenFileWrite(fileSystem, this->m_filename.data, "fs_devpath", 0);
  v4 = v3;
  if ( !v3 )
  {
    v5 = *(_DWORD *)common.type;
    qmemcpy(v7, &this->m_filename, sizeof(v7));
    (*(void (__cdecl **)(netadrtype_t, const char *))(v5 + 152))(common.type, "Error opening %s");
    return 0;
  }
  v3->WriteFloatString(v3, "%s %d\n", "MD5RProcVersion", 4);
  v4->WriteFloatString(v4, "%u\n\n", this->m_CRC);
  idRenderWorldLocal::WriteVertexBuffers(this, v4, compressed);
  idRenderWorldLocal::WriteIndexBuffers(this, v4);
  idRenderWorldLocal::WriteSilhouetteEdges(this, v4);
  idRenderWorldLocal::WriteModels(this, v4);
  idRenderWorldLocal::WriteInterAreaPortals(this, v4);
  idRenderWorldLocal::WriteNodes(this, v4);
  fileSystem->CloseFile(fileSystem, v4);
  idLexer::WriteBinaryFile(this->m_filename.data);
  return 1;
}

// FUNC: public: void __thiscall idRenderWorldLocal::AddWorldModelEntities(void)
void __usercall idRenderWorldLocal::AddWorldModelEntities(idRenderWorldLocal *this@<ecx>, int a2@<ebp>, char *a3@<esi>)
{
  idRenderEntityLocal *v4; // eax
  int v5; // eax
  int v6; // esi
  int num; // ecx
  int v8; // eax
  idRenderEntityLocal **list; // edx
  int granularity; // eax
  bool v11; // cc
  int j; // eax
  int size; // eax
  int v14; // ebp
  int v15; // ecx
  idRenderEntityLocal **v16; // ebx
  int k; // eax
  idRenderModelManager_vtbl *v18; // ebp
  char *v19; // eax
  int v20; // eax
  _DWORD *v21; // eax
  int v22; // ecx
  int i; // [esp+Ch] [ebp-30h]
  int v26; // [esp+10h] [ebp-2Ch]
  idRenderEntityLocal *v27; // [esp+14h] [ebp-28h]
  char v28; // [esp+20h] [ebp-1Ch] BYREF
  int v29; // [esp+38h] [ebp-4h]

  session->PacifierUpdate(session);
  i = 0;
  if ( this->numPortalAreas > 0 )
  {
    v26 = 0;
    do
    {
      v4 = (idRenderEntityLocal *)Memory::Allocate(0x184u);
      v27 = v4;
      v29 = 0;
      if ( v4 )
      {
        idRenderEntityLocal::idRenderEntityLocal(v4);
        v6 = v5;
      }
      else
      {
        v6 = 0;
      }
      num = this->entityDefs.num;
      v8 = 0;
      v29 = -1;
      if ( num <= 0 )
        goto LABEL_12;
      list = this->entityDefs.list;
      while ( *list )
      {
        ++v8;
        ++list;
        if ( v8 >= num )
          goto LABEL_12;
      }
      if ( v8 == -1 )
      {
LABEL_12:
        if ( !this->entityDefs.list )
        {
          granularity = this->entityDefs.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->entityDefs.size )
            {
              v11 = granularity < this->entityDefs.num;
              this->entityDefs.size = granularity;
              if ( v11 )
                this->entityDefs.num = granularity;
              this->entityDefs.list = (idRenderEntityLocal **)Memory::Allocate(4 * granularity);
              for ( j = 0; j < this->entityDefs.num; ++j )
                this->entityDefs.list[j] = *(idRenderEntityLocal **)(4 * j);
            }
          }
          else
          {
            this->entityDefs.list = 0;
            this->entityDefs.num = 0;
            this->entityDefs.size = 0;
          }
        }
        size = this->entityDefs.size;
        v14 = this->entityDefs.num;
        if ( v14 == size )
        {
          if ( !this->entityDefs.granularity )
            this->entityDefs.granularity = 16;
          v15 = size
              + this->entityDefs.granularity
              - (size + this->entityDefs.granularity) % this->entityDefs.granularity;
          if ( v15 > 0 )
          {
            if ( v15 != this->entityDefs.size )
            {
              v16 = this->entityDefs.list;
              this->entityDefs.size = v15;
              if ( v15 < v14 )
                this->entityDefs.num = v15;
              this->entityDefs.list = (idRenderEntityLocal **)Memory::Allocate(4 * v15);
              for ( k = 0; k < this->entityDefs.num; ++k )
                this->entityDefs.list[k] = v16[k];
              if ( v16 )
                Memory::Free(v16);
            }
          }
          else
          {
            if ( this->entityDefs.list )
              Memory::Free(this->entityDefs.list);
            this->entityDefs.list = 0;
            this->entityDefs.num = 0;
            this->entityDefs.size = 0;
          }
        }
        this->entityDefs.list[this->entityDefs.num++] = (idRenderEntityLocal *)v6;
        v8 = this->entityDefs.num - 1;
      }
      else
      {
        this->entityDefs.list[v8] = (idRenderEntityLocal *)v6;
      }
      *(_DWORD *)(v6 + 296) = v8;
      *(_DWORD *)(v6 + 292) = this;
      v18 = renderModelManager->__vftable;
      v19 = va("_area%i", i);
      v20 = ((int (__thiscall *)(idRenderModelManager *, char *, char *, int))v18->FindModel)(
              renderModelManager,
              v19,
              a3,
              a2);
      *(_DWORD *)(v6 + 4) = v20;
      if ( (*(unsigned __int8 (__thiscall **)(int))(*(_DWORD *)v20 + 120))(v20)
        || !(*(unsigned __int8 (__thiscall **)(_DWORD))(**(_DWORD **)(v6 + 4) + 108))(*(_DWORD *)(v6 + 4)) )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
          common.type,
          "idRenderWorldLocal::InitFromMap: bad area model lookup (_area%i)",
          v27);
      }
      a2 = 0;
      a3 = &v28;
      v21 = (_DWORD *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v6 + 4) + 124))(*(_DWORD *)(v6 + 4));
      *(_DWORD *)(v6 + 328) = *v21;
      *(_DWORD *)(v6 + 332) = v21[1];
      *(_DWORD *)(v6 + 336) = v21[2];
      *(_DWORD *)(v6 + 340) = v21[3];
      *(_DWORD *)(v6 + 344) = v21[4];
      *(_DWORD *)(v6 + 348) = v21[5];
      *(_DWORD *)(v6 + 80) = 1065353216;
      *(_DWORD *)(v6 + 96) = 1065353216;
      *(_DWORD *)(v6 + 112) = 1065353216;
      R_AxisToModelMatrix((const idMat3 *)(v6 + 80), (const idVec3 *)(v6 + 68), (float *)(v6 + 228));
      v22 = *(_DWORD *)(v6 + 4);
      *(_DWORD *)(v6 + 148) = 1065353216;
      *(_DWORD *)(v6 + 144) = 1065353216;
      *(_DWORD *)(v6 + 140) = 1065353216;
      *(_DWORD *)(v6 + 136) = 1065353216;
      this->portalAreas[v26].hasSkybox = (*(int (__thiscall **)(int))(*(_DWORD *)v22 + 180))(v22);
      idRenderWorldLocal::AddEntityRefToArea(this, (idRenderEntityLocal *)v6, &this->portalAreas[v26]);
      v11 = ++i < this->numPortalAreas;
      ++v26;
    }
    while ( v11 );
  }
}

// FUNC: private: bool __thiscall idRenderWorldLocal::InitFromMD5RProc(class Lexer *)
char __userpurge idRenderWorldLocal::InitFromMD5RProc@<al>(idRenderWorldLocal *this@<ecx>, int a2@<ebp>, Lexer *src)
{
  int v4; // eax
  unsigned int intvalue; // eax
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v8; // [esp+5Ch] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v8 = 0;
  if ( !Lexer::ReadToken(src, &token) || idStr::Icmp(token.data, "MD5RProcVersion") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorldLocal::InitFromMD5RProcFile: bad id '%s' instead of '%s'\n",
      token.data,
      "MD5RProcVersion");
    goto LABEL_32;
  }
  v4 = Lexer::ParseInt(src);
  this->procFileVersion = v4;
  if ( v4 != 4 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "%s is wrong version",
      this->m_filename.data);
LABEL_32:
    if ( src )
    {
      Lexer::~Lexer(src);
      Memory::Free(src);
    }
    v8 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  if ( !Lexer::ExpectTokenType(src, 3, 1, &token) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "%s has no map file CRC",
      this->m_filename.data);
    goto LABEL_32;
  }
  if ( token.type == 3 )
  {
    if ( (token.subtype & 0x10000) == 0 )
      idToken::NumberValue(&token);
    intvalue = token.intvalue;
  }
  else
  {
    intvalue = 0;
  }
  this->m_CRC = intvalue;
  Lexer::ReadToken(src, &token);
  if ( !idStr::Icmp(token.data, "VertexBuffer") )
  {
    idRenderWorldLocal::ParseVertexBuffers(this, src);
    Lexer::ReadToken(src, &token);
    if ( !idStr::Icmp(token.data, "IndexBuffer") )
    {
      idRenderWorldLocal::ParseIndexBuffers(this, src);
      Lexer::ReadToken(src, &token);
    }
    if ( !idStr::Icmp(token.data, "SilhouetteEdge") )
    {
      idRenderWorldLocal::ParseSilhouetteEdges(this, src);
      Lexer::ReadToken(src, &token);
    }
    if ( !idStr::Icmp(token.data, "Model") )
    {
      idRenderWorldLocal::ParseModels(this, src);
      Lexer::ReadToken(src, &token);
    }
  }
  Lexer::UnreadToken(src, &token);
  while ( Lexer::ReadToken(src, &token) )
  {
    if ( idStr::Cmp(token.data, "interAreaPortals") )
    {
      if ( idStr::Cmp(token.data, "nodes") )
        Lexer::Error(src, "idRenderWorldLocal::InitFromMap: bad token \"%s\"", token.data);
      else
        idRenderWorldLocal::ParseNodes(this, src);
    }
    else
    {
      idRenderWorldLocal::ParseInterAreaPortals(this, src);
    }
  }
  if ( src )
  {
    Lexer::~Lexer(src);
    Memory::Free(src);
  }
  if ( !this->numPortalAreas )
    idRenderWorldLocal::ClearWorld(this);
  idRenderWorldLocal::CommonChildrenArea_r(this, this->areaNodes);
  idRenderWorldLocal::AddWorldModelEntities(this, a2, (char *)src);
  idRenderWorldLocal::ClearPortalStates(this);
  v8 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: virtual bool __thiscall idRenderWorldLocal::InitFromMap(char const *)
char __thiscall idRenderWorldLocal::InitFromMap(idRenderWorldLocal *this, char *name)
{
  idStr *v3; // eax
  idFileSystem_vtbl *v4; // edx
  int len; // ebx
  bool v6; // zf
  bool v7; // bl
  idStr *v8; // eax
  idFileSystem_vtbl *v9; // edx
  int list; // esi
  Lexer *Lexer; // edi
  idSession *v12; // ecx
  char v13; // bl
  unsigned int intvalue; // eax
  idRenderModel *v16; // eax
  int v17; // eax
  bool v18; // cc
  int k; // eax
  int v20; // ebx
  int v21; // ecx
  int v22; // ecx
  int m; // eax
  idRenderModel *v24; // eax
  idRenderModel *v25; // edi
  int granularity; // eax
  int i; // eax
  int num; // ebx
  int size; // ecx
  int v30; // ecx
  int j; // eax
  int v32; // eax
  char *v33; // esi
  char *v34; // edi
  char v35; // dl
  unsigned int v36; // ecx
  char *v37; // edi
  char *v38; // esi
  int v39; // ecx
  char *data; // [esp+1Ch] [ebp-C4h]
  char *v41; // [esp+1Ch] [ebp-C4h]
  unsigned int currentTimeStamp; // [esp+38h] [ebp-A8h] BYREF
  idRenderModel *lastModel; // [esp+3Ch] [ebp-A4h]
  idStr filename; // [esp+40h] [ebp-A0h] BYREF
  Lexer *src; // [esp+60h] [ebp-80h]
  idToken token; // [esp+64h] [ebp-7Ch] BYREF
  idStr result; // [esp+B4h] [ebp-2Ch] BYREF
  int v48; // [esp+DCh] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v48 = 1;
  filename.len = 0;
  filename.alloced = 20;
  filename.data = filename.baseBuffer;
  filename.baseBuffer[0] = 0;
  if ( !name || !*name )
  {
    idRenderWorldLocal::FreeWorld(this);
    idStr::FreeData(&this->mapName);
    this->mapName.len = 0;
    this->mapName.alloced = 20;
    this->mapName.data = this->mapName.baseBuffer;
    this->mapName.baseBuffer[0] = 0;
    idRenderWorldLocal::ClearWorld(this);
    goto LABEL_110;
  }
  idStr::operator=(&filename, name);
  currentTimeStamp = -1;
  idStr::SetFileExtension(&filename, "MD5RProc");
  if ( !r_forceConvertMD5R.internalVar->integerValue )
  {
    session->PacifierUpdate(session);
    if ( cvarSystem->GetCVarBool(cvarSystem, "com_binaryRead") )
    {
      v3 = operator+(&result, &filename, "c");
      v4 = fileSystem->__vftable;
      data = v3->data;
      LOBYTE(v48) = 2;
      v4->ReadFile(fileSystem, data, 0, &currentTimeStamp);
      LOBYTE(v48) = 1;
      idStr::FreeData(&result);
    }
    if ( currentTimeStamp == -1 )
      fileSystem->ReadFile(fileSystem, filename.data, 0, &currentTimeStamp);
  }
  len = filename.len;
  if ( filename.len + 1 > this->m_filename.alloced )
    idStr::ReAllocate(&this->m_filename, filename.len + 1, 0);
  qmemcpy(this->m_filename.data, filename.data, len);
  this->m_filename.data[len] = 0;
  v6 = currentTimeStamp == -1;
  this->m_filename.len = len;
  v7 = !v6;
  if ( v6 )
  {
    idStr::SetFileExtension(&filename, "proc");
    if ( cvarSystem->GetCVarBool(cvarSystem, "com_binaryRead") )
    {
      v8 = operator+(&result, &filename, "c");
      v9 = fileSystem->__vftable;
      v41 = v8->data;
      LOBYTE(v48) = 3;
      v9->ReadFile(fileSystem, v41, 0, &currentTimeStamp);
      LOBYTE(v48) = 1;
      idStr::FreeData(&result);
    }
    if ( currentTimeStamp == -1 )
      fileSystem->ReadFile(fileSystem, filename.data, 0, &currentTimeStamp);
  }
  list = (int)name;
  if ( idStr::Cmp(name, this->mapName.data) )
  {
LABEL_20:
    idRenderWorldLocal::FreeWorld(this);
    Lexer = LexerFactory::MakeLexer(filename.data, 40, 0);
    src = Lexer;
    if ( Lexer::IsLoaded(Lexer) )
    {
      idStr::operator=(&this->mapName, name);
      this->mapTimeStamp = currentTimeStamp;
      v12 = session;
      if ( session->writeDemo )
      {
        idRenderWorldLocal::WriteLoadMap(this, (int)name);
        v12 = session;
      }
      if ( v7 )
      {
        v12->PacifierUpdate(v12);
        v13 = idRenderWorldLocal::InitFromMD5RProc(this, (int)this, Lexer);
        LOBYTE(v48) = 0;
        idStr::FreeData(&filename);
        v48 = -1;
        idStr::FreeData(&token);
        return v13;
      }
      if ( !Lexer::ReadToken(Lexer, &token) || idStr::Icmp(token.data, "PROC") )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "idRenderWorldLocal::InitFromMap: bad id '%s' instead of '%s'\n",
          token.data,
          "PROC");
      }
      else if ( Lexer::ReadToken(Lexer, &token) )
      {
        idStr::StripLeading(&token, 34);
        idStr::StripTrailing(&token, 34);
        this->procFileVersion = atol(token.data);
        if ( Lexer::ExpectTokenType(Lexer, 3, 1, &token) )
        {
          if ( token.type == 3 )
          {
            if ( (token.subtype & 0x10000) == 0 )
              idToken::NumberValue(&token);
            intvalue = token.intvalue;
          }
          else
          {
            intvalue = 0;
          }
          this->m_CRC = intvalue;
          session->PacifierUpdate(session);
          while ( Lexer::ReadToken(Lexer, &token) )
          {
            if ( idStr::Cmp(token.data, "model") )
            {
              if ( idStr::Cmp(token.data, "shadowModel") )
              {
                if ( idStr::Cmp(token.data, "interAreaPortals") )
                {
                  if ( idStr::Cmp(token.data, "nodes") )
                    Lexer::Error(Lexer, "idRenderWorldLocal::InitFromMap: bad token \"%s\"", token.data);
                  else
                    idRenderWorldLocal::ParseNodes(this, Lexer);
                }
                else
                {
                  idRenderWorldLocal::ParseInterAreaPortals(this, Lexer);
                }
              }
              else
              {
                v24 = idRenderWorldLocal::ParseShadowModel(this, (int)Lexer, list, src);
                list = 0;
                v25 = v24;
                if ( !r_convertProcToMD5R.internalVar->integerValue )
                  renderModelManager->AddModel(renderModelManager, v24);
                if ( !this->localModels.list )
                {
                  granularity = this->localModels.granularity;
                  if ( granularity > 0 )
                  {
                    if ( granularity != this->localModels.size )
                    {
                      v18 = granularity < this->localModels.num;
                      this->localModels.size = granularity;
                      if ( v18 )
                        this->localModels.num = granularity;
                      this->localModels.list = (idRenderModel **)Memory::Allocate(4 * granularity);
                      for ( i = 0; i < this->localModels.num; ++i )
                        this->localModels.list[i] = *(idRenderModel **)(4 * i);
                    }
                  }
                  else
                  {
                    this->localModels.list = 0;
                    this->localModels.num = 0;
                    this->localModels.size = 0;
                  }
                }
                num = this->localModels.num;
                size = this->localModels.size;
                if ( num == size )
                {
                  if ( !this->localModels.granularity )
                    this->localModels.granularity = 16;
                  list = this->localModels.granularity;
                  v30 = list + size - (list + size) % list;
                  if ( v30 > 0 )
                  {
                    if ( v30 != this->localModels.size )
                    {
                      list = (int)this->localModels.list;
                      this->localModels.size = v30;
                      if ( v30 < num )
                        this->localModels.num = v30;
                      this->localModels.list = (idRenderModel **)Memory::Allocate(4 * v30);
                      for ( j = 0; j < this->localModels.num; ++j )
                        this->localModels.list[j] = *(idRenderModel **)(list + 4 * j);
                      if ( list )
                        Memory::Free((void *)list);
                    }
                  }
                  else
                  {
                    list = 0;
                    if ( this->localModels.list )
                      Memory::Free(this->localModels.list);
                    this->localModels.list = 0;
                    this->localModels.num = 0;
                    this->localModels.size = 0;
                  }
                }
                this->localModels.list[this->localModels.num++] = v25;
                Lexer = src;
              }
            }
            else
            {
              v16 = idRenderWorldLocal::ParseModel(this, (srfTriangles_s *)Lexer, list, Lexer);
              list = 0;
              v6 = r_convertProcToMD5R.internalVar->integerValue == 0;
              lastModel = v16;
              if ( v6 )
                renderModelManager->AddModel(renderModelManager, v16);
              if ( !this->localModels.list )
              {
                v17 = this->localModels.granularity;
                if ( v17 > 0 )
                {
                  if ( v17 != this->localModels.size )
                  {
                    v18 = v17 < this->localModels.num;
                    this->localModels.size = v17;
                    if ( v18 )
                      this->localModels.num = v17;
                    this->localModels.list = (idRenderModel **)Memory::Allocate(4 * v17);
                    for ( k = 0; k < this->localModels.num; ++k )
                      this->localModels.list[k] = *(idRenderModel **)(4 * k);
                  }
                }
                else
                {
                  this->localModels.list = 0;
                  this->localModels.num = 0;
                  this->localModels.size = 0;
                }
              }
              v20 = this->localModels.num;
              v21 = this->localModels.size;
              if ( v20 == v21 )
              {
                if ( !this->localModels.granularity )
                  this->localModels.granularity = 16;
                list = this->localModels.granularity;
                v22 = list + v21 - (list + v21) % list;
                if ( v22 > 0 )
                {
                  if ( v22 != this->localModels.size )
                  {
                    list = (int)this->localModels.list;
                    this->localModels.size = v22;
                    if ( v22 < v20 )
                      this->localModels.num = v22;
                    this->localModels.list = (idRenderModel **)Memory::Allocate(4 * v22);
                    for ( m = 0; m < this->localModels.num; ++m )
                      this->localModels.list[m] = *(idRenderModel **)(list + 4 * m);
                    if ( list )
                      Memory::Free((void *)list);
                  }
                }
                else
                {
                  list = 0;
                  if ( this->localModels.list )
                    Memory::Free(this->localModels.list);
                  this->localModels.list = 0;
                  this->localModels.num = 0;
                  this->localModels.size = 0;
                }
              }
              this->localModels.list[this->localModels.num++] = lastModel;
            }
            session->PacifierUpdate(session);
          }
          if ( Lexer )
          {
            Lexer::~Lexer(Lexer);
            Memory::Free(Lexer);
          }
          if ( r_convertProcToMD5R.internalVar->integerValue )
          {
            lastModel = (idRenderModel *)filename.len;
            if ( filename.len + 1 > this->m_filename.alloced )
              idStr::ReAllocate(&this->m_filename, filename.len + 1, 0);
            v32 = (int)lastModel;
            v33 = filename.data;
            v34 = this->m_filename.data;
            v35 = (char)lastModel;
            v36 = (unsigned int)lastModel >> 2;
            qmemcpy(v34, filename.data, 4 * ((unsigned int)lastModel >> 2));
            v38 = &v33[4 * v36];
            v37 = &v34[4 * v36];
            v39 = v35 & 3;
            qmemcpy(v37, v38, v39);
            list = (int)&v38[v39];
            this->m_filename.data[v32] = 0;
            this->m_filename.len = v32;
            idStr::SetFileExtension(&this->m_filename, "MD5RProc");
            idRenderWorldLocal::ConvertProcToMD5R(this);
          }
          if ( !this->numPortalAreas )
            idRenderWorldLocal::ClearWorld(this);
          idRenderWorldLocal::CommonChildrenArea_r(this, this->areaNodes);
          idRenderWorldLocal::AddWorldModelEntities(this, (int)this, (char *)list);
          session->PacifierUpdate(session);
          idRenderWorldLocal::ClearPortalStates(this);
          session->PacifierUpdate(session);
          goto LABEL_110;
        }
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "%s has no map file CRC",
          filename.data);
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "%s is missing version",
          filename.data);
      }
      if ( Lexer )
      {
        Lexer::~Lexer(Lexer);
        Memory::Free(Lexer);
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idRenderWorldLocal::InitFromMap: %s not found\n",
        filename.data);
      idRenderWorldLocal::ClearWorld(this);
    }
    LOBYTE(v48) = 0;
    idStr::FreeData(&filename);
    v48 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  if ( currentTimeStamp == -1 || currentTimeStamp != this->mapTimeStamp )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderWorldLocal::InitFromMap: timestamp has changed, reloading.\n");
    goto LABEL_20;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "idRenderWorldLocal::InitFromMap: retaining existing map\n");
  this->FreeDefs(this);
  idRenderWorldLocal::TouchWorldModels(this);
  idRenderWorldLocal::AddWorldModelEntities(this, (int)this, name);
  idRenderWorldLocal::ClearPortalStates(this);
LABEL_110:
  LOBYTE(v48) = 0;
  idStr::FreeData(&filename);
  v48 = -1;
  idStr::FreeData(&token);
  return 1;
}
