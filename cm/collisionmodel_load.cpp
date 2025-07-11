
// FUNC: private: struct cm_node_t * __thiscall idCollisionModelManagerLocal::AllocNode(class idCollisionModelLocal *,int)
cm_node_t *__thiscall idCollisionModelManagerLocal::AllocNode(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        int blockSize)
{
  cm_nodeBlock_t *nodeBlocks; // eax
  cm_nodeBlock_t *v4; // eax
  cm_node_t *nextNode; // eax
  int v6; // edx
  cm_nodeBlock_t *v7; // ecx
  cm_node_t *result; // eax

  nodeBlocks = model->nodeBlocks;
  if ( !nodeBlocks || !nodeBlocks->nextNode )
  {
    v4 = (cm_nodeBlock_t *)Mem_ClearedAlloc(28 * blockSize + 8, 8u);
    v4->nextNode = (cm_node_t *)&v4[1];
    v4->next = model->nodeBlocks;
    model->nodeBlocks = v4;
    nextNode = v4->nextNode;
    if ( blockSize - 1 > 0 )
    {
      v6 = blockSize - 1;
      do
      {
        --v6;
        nextNode->parent = nextNode + 1;
        ++nextNode;
      }
      while ( v6 );
    }
    nextNode->parent = 0;
  }
  v7 = model->nodeBlocks;
  result = v7->nextNode;
  v7->nextNode = v7->nextNode->parent;
  result->parent = 0;
  return result;
}

// FUNC: private: struct cm_polygonRef_t * __thiscall idCollisionModelManagerLocal::AllocPolygonReference(class idCollisionModelLocal *,int)
cm_polygonRef_t *__thiscall idCollisionModelManagerLocal::AllocPolygonReference(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        int blockSize)
{
  cm_polygonRefBlock_t *polygonRefBlocks; // eax
  cm_polygonRefBlock_t *v4; // eax
  cm_polygonRef_t *nextRef; // eax
  int v6; // edx
  cm_polygonRefBlock_t *v7; // edi
  cm_polygonRef_t *result; // eax

  polygonRefBlocks = model->polygonRefBlocks;
  if ( !polygonRefBlocks || !polygonRefBlocks->nextRef )
  {
    v4 = (cm_polygonRefBlock_t *)Mem_Alloc(8 * blockSize + 8, 8u);
    v4->nextRef = (cm_polygonRef_t *)&v4[1];
    v4->next = model->polygonRefBlocks;
    model->polygonRefBlocks = v4;
    nextRef = v4->nextRef;
    if ( blockSize - 1 > 0 )
    {
      v6 = blockSize - 1;
      do
      {
        --v6;
        nextRef->next = nextRef + 1;
        ++nextRef;
      }
      while ( v6 );
    }
    nextRef->next = 0;
  }
  v7 = model->polygonRefBlocks;
  result = v7->nextRef;
  v7->nextRef = v7->nextRef->next;
  return result;
}

// FUNC: private: struct cm_brushRef_t * __thiscall idCollisionModelManagerLocal::AllocBrushReference(class idCollisionModelLocal *,int)
cm_brushRef_t *__thiscall idCollisionModelManagerLocal::AllocBrushReference(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        int blockSize)
{
  cm_brushRefBlock_t *brushRefBlocks; // eax
  cm_brushRefBlock_t *v4; // eax
  cm_brushRef_t *nextRef; // eax
  int v6; // edx
  cm_brushRefBlock_t *v7; // edi
  cm_brushRef_t *result; // eax

  brushRefBlocks = model->brushRefBlocks;
  if ( !brushRefBlocks || !brushRefBlocks->nextRef )
  {
    v4 = (cm_brushRefBlock_t *)Mem_Alloc(8 * blockSize + 8, 8u);
    v4->nextRef = (cm_brushRef_t *)&v4[1];
    v4->next = model->brushRefBlocks;
    model->brushRefBlocks = v4;
    nextRef = v4->nextRef;
    if ( blockSize - 1 > 0 )
    {
      v6 = blockSize - 1;
      do
      {
        --v6;
        nextRef->next = nextRef + 1;
        ++nextRef;
      }
      while ( v6 );
    }
    nextRef->next = 0;
  }
  v7 = model->brushRefBlocks;
  result = v7->nextRef;
  v7->nextRef = v7->nextRef->next;
  return result;
}

// FUNC: private: struct cm_polygon_t * __thiscall idCollisionModelManagerLocal::AllocPolygon(class idCollisionModelLocal *,int)
cm_polygon_t *__thiscall idCollisionModelManagerLocal::AllocPolygon(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        int numEdges)
{
  cm_polygon_t *polygons; // eax
  cm_polygon_t *result; // eax
  int numPolygons; // edx

  polygons = model->polygons;
  if ( polygons || model->polygonEdges )
  {
    numPolygons = model->numPolygons;
    result = &polygons[numPolygons];
    model->numPolygons = numPolygons + 1;
    result->numEdges = numEdges;
    result->edges = &model->polygonEdges[model->numPolygonEdges];
    model->numPolygonEdges += numEdges;
  }
  else
  {
    model->numPolygonEdges += numEdges;
    ++model->numPolygons;
    result = (cm_polygon_t *)Mem_Alloc(4 * numEdges + 88, 8u);
    result->edges = (int *)&result[1];
  }
  return result;
}

// FUNC: private: struct cm_brush_t * __thiscall idCollisionModelManagerLocal::AllocBrush(class idCollisionModelLocal *,int)
cm_brush_t *__thiscall idCollisionModelManagerLocal::AllocBrush(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        int numPlanes)
{
  cm_brush_t *brushes; // esi
  cm_brush_t *result; // eax
  int numBrushes; // edx

  brushes = model->brushes;
  if ( brushes || model->brushPlanes )
  {
    numBrushes = model->numBrushes;
    model->numBrushes = numBrushes + 1;
    result = &brushes[numBrushes];
    result->numPlanes = numPlanes;
    result->planes = &model->brushPlanes[model->numBrushPlanes];
    model->numBrushPlanes += numPlanes;
  }
  else
  {
    model->numBrushPlanes += numPlanes;
    ++model->numBrushes;
    result = (cm_brush_t *)Mem_Alloc(16 * (numPlanes + 3), 8u);
    result->planes = (idPlane *)&result[1];
  }
  return result;
}

// FUNC: int __cdecl CM_GetNodeContents(struct cm_node_t *)
int __cdecl CM_GetNodeContents(cm_node_t *node)
{
  int i; // esi
  cm_polygonRef_t *j; // eax
  cm_polygon_t *p; // ecx
  cm_brushRef_t *k; // eax
  cm_brush_t *b; // edx
  int NodeContents; // eax

  for ( i = 0; ; i |= NodeContents )
  {
    for ( j = node->polygons; j; i |= p->contents )
    {
      p = j->p;
      j = j->next;
    }
    for ( k = node->brushes; k; i |= b->contents )
    {
      b = k->b;
      k = k->next;
    }
    if ( node->planeType == -1 )
      break;
    NodeContents = CM_GetNodeContents(node->children[1]);
    node = node->children[0];
  }
  return i;
}

// FUNC: int __cdecl CM_GetModelMemory(class idCollisionModelLocal *)
int __cdecl CM_GetModelMemory(idCollisionModelLocal *model)
{
  return 4
       * (model->numPolygonEdges
        + 9 * model->numEdges
        + 7 * model->numNodes
        + 2
        * (model->numBrushRefs
         + model->numPolygonRefs
         + 11 * model->numPolygons
         + 3 * (model->numVertices + 2 * model->numBrushes)
         + 2 * model->numBrushPlanes));
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::RemapEdges(struct cm_node_t *,int *)
void __thiscall idCollisionModelManagerLocal::RemapEdges(
        idCollisionModelManagerLocal *this,
        cm_node_t *node,
        int *edgeRemap)
{
  cm_node_t *v3; // esi
  cm_polygonRef_t *polygons; // ebx
  cm_polygon_t *p; // esi
  int checkCount; // eax
  int v7; // edi
  bool v8; // cc
  int *edges; // ecx
  int v10; // eax
  int *v11; // ecx
  int v12; // edx

  while ( 1 )
  {
    v3 = node;
    polygons = node->polygons;
    if ( polygons )
    {
      do
      {
        p = polygons->p;
        checkCount = this->checkCount;
        if ( polygons->p->checkcount != checkCount )
        {
          v7 = 0;
          v8 = p->numEdges <= 0;
          p->checkcount = checkCount;
          if ( !v8 )
          {
            do
            {
              edges = p->edges;
              v10 = edges[v7];
              v11 = &edges[v7];
              if ( v10 >= 0 )
                v12 = edgeRemap[*v11];
              else
                v12 = -edgeRemap[abs32(v10)];
              ++v7;
              *v11 = v12;
            }
            while ( v7 < p->numEdges );
          }
        }
        polygons = polygons->next;
      }
      while ( polygons );
      v3 = node;
    }
    if ( v3->planeType == -1 )
      break;
    idCollisionModelManagerLocal::RemapEdges(this, v3->children[1], edgeRemap);
    node = v3->children[0];
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::PrintModelInfo(class idCollisionModelLocal const *)
void __thiscall idCollisionModelManagerLocal::PrintModelInfo(
        idCollisionModelManagerLocal *this,
        const idCollisionModelLocal *model)
{
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i vertices (%i KB)\n",
    model->numVertices,
    (unsigned int)(24 * model->numVertices) >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i edges (%i KB)\n",
    model->numEdges,
    (unsigned int)(36 * model->numEdges) >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i polygons (%i KB)\n",
    model->numPolygons,
    (unsigned int)(88 * model->numPolygons) >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i polygon edges (%i KB)\n",
    model->numPolygonEdges,
    (unsigned int)(4 * model->numPolygonEdges) >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i brushes (%i KB)\n",
    model->numBrushes,
    (unsigned int)(48 * model->numBrushes) >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i brush planes (%i KB)\n",
    model->numBrushPlanes,
    (unsigned int)(16 * model->numBrushPlanes) >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i nodes (%i KB)\n",
    model->numNodes,
    (unsigned int)(28 * model->numNodes) >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i polygon refs (%i KB)\n",
    model->numPolygonRefs,
    (unsigned int)(8 * model->numPolygonRefs) >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i brush refs (%i KB)\n",
    model->numBrushRefs,
    (unsigned int)(8 * model->numBrushRefs) >> 10);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i internal edges\n",
    model->numInternalEdges);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i sharp edges\n",
    model->numSharpEdges);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i contained polygons removed\n",
    model->numRemovedPolys);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i polygons merged\n",
    model->numMergedPolys);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i KB total memory used\n",
    model->usedMemory >> 10);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ParseProcNodes(class Lexer *)
void __thiscall idCollisionModelManagerLocal::ParseProcNodes(idCollisionModelManagerLocal *this, Lexer *src)
{
  int v4; // eax
  int v5; // ebp
  cm_procNode_s *v6; // eax
  bool v7; // cc
  cm_procNode_s *v8; // esi
  Lexer *srca; // [esp+10h] [ebp+4h]

  Lexer::ExpectTokenString(src, "{");
  v4 = Lexer::ParseInt(src);
  v5 = 0;
  this->numProcNodes = v4;
  if ( v4 < 0 )
    Lexer::Error(src, "ParseProcNodes: bad numProcNodes");
  v6 = (cm_procNode_s *)Mem_ClearedAlloc(24 * this->numProcNodes, 8u);
  v7 = this->numProcNodes <= 0;
  this->procNodes = v6;
  if ( !v7 )
  {
    srca = 0;
    do
    {
      v8 = (cm_procNode_s *)((char *)srca + (unsigned int)this->procNodes);
      Lexer::Parse1DMatrix(src, 4, &v8->plane.a);
      v8->children[0] = Lexer::ParseInt(src);
      srca = (Lexer *)((char *)srca + 24);
      ++v5;
      v8->children[1] = Lexer::ParseInt(src);
    }
    while ( v5 < this->numProcNodes );
  }
  Lexer::ExpectTokenString(src, "}");
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::LoadProcBSP(char const *,unsigned int)
char __thiscall idCollisionModelManagerLocal::LoadProcBSP(
        idCollisionModelManagerLocal *this,
        char *name,
        unsigned int mapFileCRC)
{
  Lexer *Lexer; // esi
  unsigned int intvalue; // ecx
  idStr filename; // [esp+Ch] [ebp-7Ch] BYREF
  idToken token; // [esp+2Ch] [ebp-5Ch] BYREF
  int v9; // [esp+84h] [ebp-4h]

  filename.len = 0;
  filename.alloced = 20;
  filename.data = filename.baseBuffer;
  filename.baseBuffer[0] = 0;
  token.floatvalue = 0.0;
  v9 = 1;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  idStr::operator=(&filename, name);
  idStr::SetFileExtension(&filename, "proc");
  Lexer = LexerFactory::MakeLexer(filename.data, 40, 0);
  if ( !Lexer::IsLoaded(Lexer) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idCollisionModelManagerLocal::LoadProcBSP: couldn't load %s",
      filename.data);
LABEL_32:
    if ( Lexer )
    {
      Lexer::~Lexer(Lexer);
      Memory::Free(Lexer);
    }
    LOBYTE(v9) = 0;
    idStr::FreeData(&token);
    v9 = -1;
    idStr::FreeData(&filename);
    return 0;
  }
  if ( !Lexer::ReadToken(Lexer, &token) || idStr::Icmp(token.data, "PROC") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idCollisionModelManagerLocal::LoadProcBSP: bad id '%s' instead of '%s'",
      token.data,
      "PROC");
    goto LABEL_32;
  }
  if ( !Lexer::ReadToken(Lexer, &token) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "%s is missing version",
      filename.data);
    goto LABEL_32;
  }
  if ( !Lexer::ExpectTokenType(Lexer, 3, 1, &token) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "%s has no map file CRC",
      filename.data);
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
  if ( mapFileCRC && intvalue != mapFileCRC )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "%s is out of date",
      filename.data);
    console->SetProcFileOutOfDate(console, 1);
    this->mapFileTime = -1;
  }
  while ( Lexer::ReadToken(Lexer, &token) )
  {
    if ( idStr::Cmp(token.data, "model")
      && idStr::Cmp(token.data, "shadowModel")
      && idStr::Cmp(token.data, "interAreaPortals") )
    {
      if ( !idStr::Cmp(token.data, "nodes") )
      {
        idCollisionModelManagerLocal::ParseProcNodes(this, Lexer);
        break;
      }
      Lexer::Error(Lexer, "idCollisionModelManagerLocal::LoadProcBSP: bad token \"%s\"", token.data);
    }
    else
    {
      Lexer::SkipBracedSection(Lexer, 1);
    }
  }
  if ( Lexer )
  {
    Lexer::~Lexer(Lexer);
    Memory::Free(Lexer);
  }
  LOBYTE(v9) = 0;
  idStr::FreeData(&token);
  v9 = -1;
  idStr::FreeData(&filename);
  return 1;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::RemapPolygonReferences_r(struct cm_node_t *,struct cm_polygon_t *,struct cm_polygon_t *)
void __thiscall idCollisionModelManagerLocal::RemapPolygonReferences_r(
        idCollisionModelManagerLocal *this,
        cm_node_t *node,
        cm_polygon_t *p,
        cm_polygon_t *newp)
{
  cm_node_t *v4; // esi
  cm_polygonRef_t *polygons; // eax
  int planeType; // ecx

  v4 = node;
  if ( node )
  {
    while ( 1 )
    {
      polygons = v4->polygons;
      if ( polygons )
      {
        while ( polygons->p != p )
        {
          polygons = polygons->next;
          if ( !polygons )
            goto LABEL_7;
        }
        polygons->p = newp;
      }
LABEL_7:
      planeType = v4->planeType;
      if ( v4->planeType == -1 )
        return;
      if ( *(&p->bounds.b[0].x + planeType) > (double)v4->planeDist )
        goto LABEL_12;
      if ( *(&p->bounds.b[1].x + planeType) >= (double)v4->planeDist )
        break;
      v4 = v4->children[1];
LABEL_13:
      if ( !v4 )
        return;
    }
    idCollisionModelManagerLocal::RemapPolygonReferences_r(this, v4->children[1], p, newp);
LABEL_12:
    v4 = v4->children[0];
    goto LABEL_13;
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::RemapBrushReferences_r(struct cm_node_t *,struct cm_brush_t *,struct cm_brush_t *)
void __thiscall idCollisionModelManagerLocal::RemapBrushReferences_r(
        idCollisionModelManagerLocal *this,
        cm_node_t *node,
        cm_brush_t *b,
        cm_brush_t *newb)
{
  cm_node_t *v4; // esi
  cm_brushRef_t *brushes; // eax
  int planeType; // ecx

  v4 = node;
  if ( node )
  {
    while ( 1 )
    {
      brushes = v4->brushes;
      if ( brushes )
      {
        while ( brushes->b != b )
        {
          brushes = brushes->next;
          if ( !brushes )
            goto LABEL_7;
        }
        brushes->b = newb;
      }
LABEL_7:
      planeType = v4->planeType;
      if ( v4->planeType == -1 )
        return;
      if ( *(&b->bounds.b[0].x + planeType) > (double)v4->planeDist )
        goto LABEL_12;
      if ( *(&b->bounds.b[1].x + planeType) >= (double)v4->planeDist )
        break;
      v4 = v4->children[1];
LABEL_13:
      if ( !v4 )
        return;
    }
    idCollisionModelManagerLocal::RemapBrushReferences_r(this, v4->children[1], b, newb);
LABEL_12:
    v4 = v4->children[0];
    goto LABEL_13;
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::RemovePolygonReferences_r(struct cm_node_t *,struct cm_polygon_t *)
void __thiscall idCollisionModelManagerLocal::RemovePolygonReferences_r(
        idCollisionModelManagerLocal *this,
        cm_node_t *node,
        cm_polygon_t *p)
{
  cm_node_t *v3; // esi
  cm_polygonRef_t *polygons; // eax
  int planeType; // ecx

  v3 = node;
  if ( node )
  {
    while ( 1 )
    {
      polygons = v3->polygons;
      if ( polygons )
      {
        while ( polygons->p != p )
        {
          polygons = polygons->next;
          if ( !polygons )
            goto LABEL_7;
        }
        polygons->p = 0;
      }
LABEL_7:
      planeType = v3->planeType;
      if ( v3->planeType == -1 )
        return;
      if ( *(&p->bounds.b[0].x + planeType) > (double)v3->planeDist )
        goto LABEL_12;
      if ( *(&p->bounds.b[1].x + planeType) >= (double)v3->planeDist )
        break;
      v3 = v3->children[1];
LABEL_13:
      if ( !v3 )
        return;
    }
    idCollisionModelManagerLocal::RemovePolygonReferences_r(this, v3->children[1], p);
LABEL_12:
    v3 = v3->children[0];
    goto LABEL_13;
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::RemoveBrushReferences_r(struct cm_node_t *,struct cm_brush_t *)
void __thiscall idCollisionModelManagerLocal::RemoveBrushReferences_r(
        idCollisionModelManagerLocal *this,
        cm_node_t *node,
        cm_brush_t *b)
{
  cm_node_t *v3; // esi
  cm_brushRef_t *brushes; // eax
  int planeType; // ecx

  v3 = node;
  if ( !node )
    return;
  while ( 1 )
  {
    brushes = v3->brushes;
    if ( brushes )
      break;
LABEL_5:
    planeType = v3->planeType;
    if ( v3->planeType == -1 )
      return;
    if ( *(&b->bounds.b[0].x + planeType) > (double)v3->planeDist )
      goto LABEL_10;
    if ( *(&b->bounds.b[1].x + planeType) >= (double)v3->planeDist )
    {
      idCollisionModelManagerLocal::RemoveBrushReferences_r(this, v3->children[1], b);
LABEL_10:
      v3 = v3->children[0];
      goto LABEL_11;
    }
    v3 = v3->children[1];
LABEL_11:
    if ( !v3 )
      return;
  }
  while ( brushes->b != b )
  {
    brushes = brushes->next;
    if ( !brushes )
      goto LABEL_5;
  }
  brushes->b = 0;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::FreeTree_r(class idCollisionModelLocal *,struct cm_node_t *,struct cm_node_t *)
void __thiscall idCollisionModelManagerLocal::FreeTree_r(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *headNode,
        cm_node_t *node)
{
  cm_polygonRef_t *i; // edi
  _DWORD *v6; // edx
  cm_brushRef_t *j; // edi
  _DWORD *v8; // edx
  cm_node_t *v9; // [esp-4h] [ebp-14h]

  for ( i = node->polygons; i; node->polygons = i )
  {
    if ( i->p )
    {
      idCollisionModelManagerLocal::RemovePolygonReferences_r(this, headNode, i->p);
      if ( !model->polygons && !model->polygonEdges )
      {
        --model->numPolygons;
        model->numPolygonEdges -= v6[20];
        Mem_Free(v6);
      }
    }
    i = i->next;
  }
  for ( j = node->brushes; j; node->brushes = j )
  {
    if ( j->b )
    {
      idCollisionModelManagerLocal::RemoveBrushReferences_r(this, headNode, j->b);
      if ( !model->brushes && !model->brushPlanes )
      {
        --model->numBrushes;
        model->numBrushPlanes -= v8[10];
        Mem_Free(v8);
      }
    }
    j = j->next;
  }
  if ( node->planeType != -1 )
  {
    idCollisionModelManagerLocal::FreeTree_r(this, model, headNode, node->children[0]);
    v9 = node->children[1];
    node->children[0] = 0;
    idCollisionModelManagerLocal::FreeTree_r(this, model, headNode, v9);
    node->children[1] = 0;
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::AddToMapModelReferenceCounts(char const *,int)
void __thiscall idCollisionModelManagerLocal::AddToMapModelReferenceCounts(
        idCollisionModelManagerLocal *this,
        const char *mapName,
        int add)
{
  const char *v4; // eax
  int v5; // ebp
  int v6; // eax
  char *data; // edx
  const char *v8; // ecx
  char v9; // al
  int i; // esi
  idCollisionModelLocal *v11; // eax
  idStr name; // [esp+Ch] [ebp-2Ch] BYREF
  int v13; // [esp+34h] [ebp-4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  if ( mapName )
  {
    v4 = &mapName[strlen(mapName) + 1];
    v5 = v4 - (mapName + 1);
    v6 = v4 - mapName;
    if ( v6 > 20 )
      idStr::ReAllocate(&name, v6, 1);
    data = name.data;
    v8 = mapName;
    do
    {
      v9 = *v8;
      *data++ = *v8++;
    }
    while ( v9 );
    name.len = v5;
  }
  v13 = 0;
  idStr::StripFileExtension(&name);
  if ( name.len )
  {
    for ( i = 0; i < this->models.num; ++i )
    {
      if ( !idStr::IcmpnPath(this->models.list[i]->name.data, name.data, name.len) )
      {
        v11 = this->models.list[i];
        v11->refCount += add;
      }
    }
  }
  v13 = -1;
  idStr::FreeData(&name);
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::FreeMap(char const *)
void __thiscall idCollisionModelManagerLocal::FreeMap(idCollisionModelManagerLocal *this, const char *mapName)
{
  idCollisionModelManagerLocal::AddToMapModelReferenceCounts(this, mapName, -1);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::CalculateEdgeNormals(class idCollisionModelLocal *,struct cm_node_t *)
void __thiscall idCollisionModelManagerLocal::CalculateEdgeNormals(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node)
{
  idCollisionModelManagerLocal *v4; // edi
  cm_node_t *v5; // ebx
  cm_polygonRef_t *polygons; // ecx
  cm_polygon_t *p; // esi
  int checkCount; // eax
  char *v9; // eax
  int v10; // edi
  cm_edge_t *v11; // ecx
  cm_vertex_t *vertices; // edx
  BOOL v13; // ebx
  float *p_x; // eax
  double x; // st7
  int p_p; // edx
  double v17; // st7
  double v18; // st6
  double v19; // st6
  double v20; // rt1
  long double v21; // st4
  long double v22; // st7
  double v23; // st7
  cm_vertex_t *v24; // edx
  BOOL v25; // ebx
  float *v26; // eax
  double v27; // st7
  int v28; // edx
  double v29; // st7
  double v30; // st6
  double v31; // st5
  long double v32; // st4
  double v33; // st7
  cm_polygonRef_t *pref; // [esp+10h] [ebp-68h]
  float v36; // [esp+1Ch] [ebp-5Ch]
  float v37; // [esp+20h] [ebp-58h]
  float v38; // [esp+24h] [ebp-54h]
  float v39; // [esp+28h] [ebp-50h]
  float v40; // [esp+2Ch] [ebp-4Ch]
  float v41; // [esp+30h] [ebp-48h]
  float v42; // [esp+34h] [ebp-44h]
  float v43; // [esp+38h] [ebp-40h]
  float v44; // [esp+48h] [ebp-30h]
  float v45; // [esp+4Ch] [ebp-2Ch]
  float v46; // [esp+5Ch] [ebp-1Ch]
  float v47; // [esp+68h] [ebp-10h]
  float v48; // [esp+74h] [ebp-4h]
  idCollisionModelLocal *modela; // [esp+7Ch] [ebp+4h]

  v4 = this;
  while ( 1 )
  {
    v5 = node;
    polygons = node->polygons;
    for ( pref = polygons; polygons; pref = polygons )
    {
      p = polygons->p;
      checkCount = v4->checkCount;
      if ( polygons->p->checkcount != checkCount )
      {
        p->checkcount = checkCount;
        v9 = 0;
        modela = 0;
        if ( p->numEdges > 0 )
        {
          do
          {
            v10 = p->edges[(_DWORD)v9];
            v11 = &model->edges[abs32(v10)];
            if ( v11->normal.x == 0.0 && v11->normal.y == 0.0 && v11->normal.z == 0.0 )
            {
              if ( v11->numUsers == 1 )
              {
                vertices = model->vertices;
                v13 = v10 < 0;
                p_x = &vertices[v11->vertexNum[v10 > 0]].p.x;
                x = vertices[v11->vertexNum[v13]].p.x;
                p_p = (int)&vertices[v11->vertexNum[v13]].p;
                v17 = x - *p_x;
                v36 = *(float *)(p_p + 4) - p_x[1];
                v18 = *(float *)(p_p + 8) - p_x[2];
                v37 = v18;
                v19 = v18 * p->plane.b - v36 * p->plane.c;
                v20 = v17 * p->plane.c - v37 * p->plane.a;
                v46 = v36 * p->plane.a - v17 * p->plane.b;
                v11->normal.z = v46;
                v11->normal.x = v19;
                v11->normal.y = v20;
                v21 = v11->normal.x * v11->normal.x + v11->normal.y * v11->normal.y + v11->normal.z * v11->normal.z;
                if ( v21 != 0.0 )
                {
                  v22 = 1.0 / sqrt(v21);
                  v11->normal.x = v22 * v11->normal.x;
                  v11->normal.y = v22 * v11->normal.y;
                  v11->normal.z = v22 * v11->normal.z;
                }
              }
              else
              {
                v11->normal.x = p->plane.a;
                v11->normal.y = p->plane.b;
                v11->normal.z = p->plane.c;
              }
            }
            else
            {
              v23 = p->plane.c * v11->normal.z + p->plane.b * v11->normal.y + v11->normal.x * p->plane.a;
              if ( v23 >= -0.69999999 )
              {
                v41 = p->plane.a + v11->normal.x;
                v42 = p->plane.b + v11->normal.y;
                v43 = p->plane.c + v11->normal.z;
                v33 = 1.0 / (v23 + 1.0);
                v48 = v43 * v33;
                v11->normal.z = v48;
                v11->normal.x = v41 * v33;
                v11->normal.y = v42 * v33;
              }
              else
              {
                v24 = model->vertices;
                v25 = v10 > 0;
                v26 = &v24[v11->vertexNum[v10 < 0]].p.x;
                v27 = v24[v11->vertexNum[v25]].p.x;
                v28 = (int)&v24[v11->vertexNum[v25]].p;
                v29 = v27 - *v26;
                v30 = *(float *)(v28 + 4) - v26[1];
                v31 = *(float *)(v28 + 8) - v26[2];
                v38 = -v31 * p->plane.b - -v30 * p->plane.c;
                v39 = -v29 * p->plane.c - -v31 * p->plane.a;
                v40 = -v30 * p->plane.a - -v29 * p->plane.b;
                v44 = v31 * v11->normal.y - v30 * v11->normal.z;
                v45 = v29 * v11->normal.z - v31 * v11->normal.x;
                v47 = v30 * v11->normal.x - v29 * v11->normal.y + v40;
                v11->normal.z = v47;
                v11->normal.x = v44 + v38;
                v11->normal.y = v45 + v39;
                v32 = sqrt(v11->normal.x * v11->normal.x + v11->normal.y * v11->normal.y + v11->normal.z * v11->normal.z);
                v11->normal.x = 3.3333333 / v32 * v11->normal.x;
                v11->normal.y = 3.3333333 / v32 * v11->normal.y;
                v11->normal.z = 3.3333333 / v32 * v11->normal.z;
                ++model->numSharpEdges;
              }
            }
            v9 = (char *)&modela->__vftable + 1;
            modela = (idCollisionModelLocal *)((char *)modela + 1);
          }
          while ( (int)modela < p->numEdges );
          polygons = pref;
          v5 = node;
          v4 = this;
        }
      }
      polygons = polygons->next;
    }
    if ( v5->planeType == -1 )
      break;
    idCollisionModelManagerLocal::CalculateEdgeNormals(v4, model, v5->children[1]);
    node = v5->children[0];
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ClearModel(class idCollisionModelLocal *)
void __thiscall idCollisionModelManagerLocal::ClearModel(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model)
{
  model->refCount = 0;
  model->fileTime = -1;
  model->bounds.b[0].z = idMath::INFINITY;
  model->bounds.b[0].y = idMath::INFINITY;
  model->bounds.b[0].x = idMath::INFINITY;
  model->bounds.b[1].z = -1.0e30;
  model->bounds.b[1].y = -1.0e30;
  model->bounds.b[1].x = -1.0e30;
  model->contents = 0;
  model->isTraceModel = 0;
  model->isConvex = 0;
  model->maxVertices = 0;
  model->numVertices = 0;
  model->vertices = 0;
  model->maxEdges = 0;
  model->numEdges = 0;
  model->edges = 0;
  model->maxPolygonEdges = 0;
  model->numPolygonEdges = 0;
  model->polygonEdges = 0;
  model->maxPolygons = 0;
  model->numPolygons = 0;
  model->polygons = 0;
  model->maxBrushPlanes = 0;
  model->numBrushPlanes = 0;
  model->brushPlanes = 0;
  model->maxBrushes = 0;
  model->numBrushes = 0;
  model->brushes = 0;
  model->numNodes = 0;
  model->node = 0;
  model->nodeBlocks = 0;
  model->polygonRefBlocks = 0;
  model->brushRefBlocks = 0;
  model->usedMemory = 0;
  model->numMergedPolys = 0;
  model->numRemovedPolys = 0;
  model->numSharpEdges = 0;
  model->numInternalEdges = 0;
  model->numPolygonRefs = 0;
  model->numBrushRefs = 0;
  model->numPrimitives = 0;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::CopyPolygon(struct cm_polygon_t *,struct cm_polygon_t *)
void __thiscall idCollisionModelManagerLocal::CopyPolygon(
        idCollisionModelManagerLocal *this,
        cm_polygon_t *dest,
        cm_polygon_t *src)
{
  int *edges; // edi

  dest->bounds.b[0].x = src->bounds.b[0].x;
  dest->bounds.b[0].y = src->bounds.b[0].y;
  dest->bounds.b[0].z = src->bounds.b[0].z;
  dest->bounds.b[1] = src->bounds.b[1];
  dest->checkcount = src->checkcount;
  dest->contents = src->contents;
  dest->material = src->material;
  dest->primitiveNum = src->primitiveNum;
  dest->plane = src->plane;
  dest->texBounds[0].x = src->texBounds[0].x;
  dest->texBounds[0].y = src->texBounds[0].y;
  edges = dest->edges;
  dest->texBounds[1] = src->texBounds[1];
  dest->texBounds[2] = src->texBounds[2];
  dest->numEdges = src->numEdges;
  qmemcpy(edges, src->edges, 4 * src->numEdges);
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::R_ChoppedAwayByProcBSP(int,class idFixedWinding *,class idVec3 const &,class idVec3 const &,float)
int __thiscall idCollisionModelManagerLocal::R_ChoppedAwayByProcBSP(
        idCollisionModelManagerLocal *this,
        int nodeNum,
        idFixedWinding *w,
        const idVec3 *normal,
        const idVec3 *origin,
        float radius)
{
  cm_procNode_s *procNodes; // eax
  double b; // st7
  cm_procNode_s *v10; // esi
  double v11; // st7
  int v12; // eax
  int v13; // eax
  idFixedWinding back; // [esp+10h] [ebp-51Ch] BYREF
  int v16; // [esp+528h] [ebp-4h]

  back.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  back.numPoints = 0;
  back.p = back.data;
  back.allocedSize = 64;
  v16 = 0;
  do
  {
    procNodes = this->procNodes;
    b = procNodes[nodeNum].plane.b;
    v10 = &procNodes[nodeNum];
    v11 = b * origin->y + origin->x * v10->plane.a + origin->z * v10->plane.c + v10->plane.d;
    if ( v11 <= radius )
    {
      if ( v11 < -radius )
        goto LABEL_6;
      v12 = idFixedWinding::Split(w, &back, &v10->plane, 0.1);
      if ( v12 )
      {
        if ( v12 == 1 )
        {
LABEL_6:
          nodeNum = v10->children[1];
          continue;
        }
        if ( v12 == 2 )
        {
          if ( normal->y * v10->plane.b + normal->z * v10->plane.c + normal->x * v10->plane.a <= 0.0 )
          {
            nodeNum = v10->children[1];
            continue;
          }
        }
        else if ( v10->children[0] < 0
               || (v13 = v10->children[1], v13 < 0)
               || v13 > 0
               && !idCollisionModelManagerLocal::R_ChoppedAwayByProcBSP(this, v13, &back, normal, origin, radius) )
        {
          back.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
          back.p = 0;
          v16 = -1;
          goto LABEL_20;
        }
      }
    }
    nodeNum = v10->children[0];
  }
  while ( nodeNum > 0 );
  back.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  back.p = 0;
  v16 = -1;
  if ( nodeNum >= 0 )
  {
    Memory::Free(0);
    return 1;
  }
LABEL_20:
  Memory::Free(0);
  return 0;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ReplacePolygons(class idCollisionModelLocal *,struct cm_node_t *,struct cm_polygon_t *,struct cm_polygon_t *,struct cm_polygon_t *)
void __thiscall idCollisionModelManagerLocal::ReplacePolygons(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node,
        cm_polygon_t *p1,
        cm_polygon_t *p2,
        cm_polygon_t *newp)
{
  cm_polygon_t *v6; // ebp
  cm_polygonRef_t *polygons; // eax
  char v9; // bl
  cm_polygonRef_t *v10; // edi
  cm_polygonRef_t *next; // edx
  int planeType; // ecx

  v6 = p1;
  while ( 1 )
  {
    polygons = node->polygons;
    v9 = 0;
    v10 = 0;
    if ( polygons )
    {
      do
      {
        next = polygons->next;
        if ( polygons->p == v6 || (v6 = p1, polygons->p == p2) )
        {
          if ( v9 )
          {
            if ( v10 )
              v10->next = next;
            else
              node->polygons = next;
            --model->numPolygonRefs;
            goto LABEL_12;
          }
          polygons->p = newp;
          v9 = 1;
        }
        v10 = polygons;
LABEL_12:
        polygons = next;
      }
      while ( next );
    }
    planeType = node->planeType;
    if ( node->planeType == -1 )
      break;
    if ( *(&v6->bounds.b[0].x + planeType) <= (double)node->planeDist
      || *(&p2->bounds.b[0].x + planeType) <= (double)node->planeDist )
    {
      if ( *(&v6->bounds.b[1].x + planeType) >= (double)node->planeDist
        || *(&p2->bounds.b[1].x + planeType) >= (double)node->planeDist )
      {
        idCollisionModelManagerLocal::ReplacePolygons(this, model, node->children[1], v6, p2, newp);
        node = node->children[0];
      }
      else
      {
        node = node->children[1];
      }
    }
    else
    {
      node = node->children[0];
    }
  }
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::PointInsidePolygon(class idCollisionModelLocal *,struct cm_polygon_t *,class idVec3 &)
char __thiscall idCollisionModelManagerLocal::PointInsidePolygon(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_polygon_t *p,
        idVec3 *v)
{
  cm_vertex_t *vertices; // ebx
  int *j; // ebp
  cm_edge_t *v6; // edx
  float *p_x; // eax
  double v8; // st7
  double v9; // st6
  double v10; // st5
  int i; // [esp+10h] [ebp-1Ch]
  float v13; // [esp+14h] [ebp-18h]
  float v14; // [esp+18h] [ebp-14h]
  float v15; // [esp+1Ch] [ebp-10h]
  float v16; // [esp+20h] [ebp-Ch]
  float v17; // [esp+24h] [ebp-8h]

  i = 0;
  if ( p->numEdges <= 0 )
    return 1;
  vertices = model->vertices;
  for ( j = p->edges; ; ++j )
  {
    v6 = &model->edges[abs32(*j)];
    p_x = &vertices[v6->vertexNum[(unsigned int)*j >> 31]].p.x;
    v8 = vertices[v6->vertexNum[*j >= 0]].p.x - *p_x;
    v9 = vertices[v6->vertexNum[*j >= 0]].p.y - vertices[v6->vertexNum[(unsigned int)*j >> 31]].p.y;
    v10 = vertices[v6->vertexNum[*j >= 0]].p.z - vertices[v6->vertexNum[(unsigned int)*j >> 31]].p.z;
    v13 = v->x - *p_x;
    v14 = v->y - vertices[v6->vertexNum[(unsigned int)*j >> 31]].p.y;
    v15 = v->z - vertices[v6->vertexNum[(unsigned int)*j >> 31]].p.z;
    v16 = v9 * p->plane.c - v10 * p->plane.b;
    v17 = v10 * p->plane.a - v8 * p->plane.c;
    if ( v15 * (v8 * p->plane.b - v9 * p->plane.a) + v17 * v14 + v16 * v13 > 0.1 )
      break;
    if ( ++i >= p->numEdges )
      return 1;
  }
  return 0;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::FindInternalEdgesOnPolygon(class idCollisionModelLocal *,struct cm_polygon_t *,struct cm_polygon_t *)
void __thiscall idCollisionModelManagerLocal::FindInternalEdgesOnPolygon(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_polygon_t *p1,
        cm_polygon_t *p2)
{
  cm_polygon_t *v4; // ebx
  int v6; // ecx
  idVec3 *v7; // edx
  int v8; // eax
  int v9; // edi
  cm_edge_t *v10; // edx
  cm_vertex_t *vertices; // eax
  idVec3 *p_p; // ecx
  float *p_x; // eax
  int v14; // edi
  char *v15; // ebx
  float *v16; // edx
  int v17; // ebp
  double v18; // st7
  double v19; // st7
  int numEdges; // ebp
  int v21; // ebx
  int *edges; // edi
  idVec3 *v23; // edi
  double v24; // st7
  double v25; // st6
  double v26; // st5
  float v27; // [esp+Ch] [ebp-28h]
  cm_edge_t *edge; // [esp+14h] [ebp-20h]
  int i; // [esp+18h] [ebp-1Ch]
  unsigned int v30; // [esp+1Ch] [ebp-18h]
  int edgeNum; // [esp+20h] [ebp-14h]
  float v33; // [esp+28h] [ebp-Ch]
  float v34; // [esp+2Ch] [ebp-8h]
  float p2a; // [esp+40h] [ebp+Ch]

  v4 = p1;
  v6 = 0;
  v7 = &p1->bounds.b[1];
  while ( v7[-1].x <= (double)*(float *)((char *)&v7->x + (char *)p2 - (char *)p1)
       && v7->x >= (double)*(&p2->bounds.b[0].x + v6) )
  {
    ++v6;
    v7 = (idVec3 *)((char *)v7 + 4);
    if ( v6 >= 3 )
    {
      v8 = 0;
      for ( i = 0; i < p1->numEdges; ++i )
      {
        v9 = v4->edges[v8];
        v30 = abs32(v9);
        v10 = &model->edges[v30];
        edgeNum = v9;
        edge = v10;
        if ( !v10->internal )
        {
          vertices = model->vertices;
          p_p = &vertices[v10->vertexNum[(unsigned int)v9 >> 31]].p;
          p_x = &vertices[v10->vertexNum[v9 >= 0]].p.x;
          v14 = 0;
          v15 = (char *)((char *)p2 - (char *)p_p);
          v16 = &p_p->x;
          v17 = (char *)p_x - (char *)p_p;
          while ( 1 )
          {
            v18 = *(float *)((char *)v16 + (_DWORD)v15 + 12) + 0.1;
            if ( v18 < *v16 )
              break;
            if ( v18 < *(float *)((char *)v16 + v17) )
              break;
            v19 = *(float *)((char *)v16 + (_DWORD)v15) - 0.1;
            if ( v19 > *v16 || v19 > *(float *)((char *)v16 + v17) )
              break;
            ++v14;
            ++v16;
            if ( v14 >= 3 )
            {
              numEdges = p2->numEdges;
              v21 = 0;
              if ( numEdges > 0 )
              {
                edges = p2->edges;
                do
                {
                  if ( v30 == abs32(*edges) )
                    break;
                  ++v21;
                  ++edges;
                }
                while ( v21 < numEdges );
              }
              if ( v21 >= numEdges )
              {
                p2a = p2->plane.c * p_p->z + p2->plane.b * p_p->y + p_p->x * p2->plane.a + p2->plane.d;
                if ( COERCE_FLOAT(LODWORD(p2a) & 0x7FFFFFFF) > 0.1 )
                  break;
                v23 = (idVec3 *)p_x;
                v27 = p2->plane.c * p_x[2] + p2->plane.b * p_x[1] + *p_x * p2->plane.a + p2->plane.d;
                if ( COERCE_FLOAT(LODWORD(v27) & 0x7FFFFFFF) > 0.1 )
                  break;
              }
              else
              {
                if ( edge->numUsers > 2u || edgeNum == p2->edges[v21] )
                  break;
                v23 = (idVec3 *)p_x;
              }
              v24 = v23->x - p_p->x;
              v25 = v23->y - p_p->y;
              v26 = v23->z - p_p->z;
              v33 = v26 * p1->plane.b - v25 * p1->plane.c;
              v34 = v24 * p1->plane.c - v26 * p1->plane.a;
              if ( (v25 * p1->plane.a - v24 * p1->plane.b) * p2->plane.c + v34 * p2->plane.b + v33 * p2->plane.a < 0.0 )
                return;
              if ( v21 < numEdges
                || idCollisionModelManagerLocal::PointInsidePolygon(this, model, p2, p_p)
                && idCollisionModelManagerLocal::PointInsidePolygon(this, model, p2, v23) )
              {
                edge->internal = 1;
                ++model->numInternalEdges;
              }
              break;
            }
          }
        }
        v4 = p1;
        v8 = i + 1;
      }
      return;
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::FindInternalPolygonEdges(class idCollisionModelLocal *,struct cm_node_t *,struct cm_polygon_t *)
void __thiscall idCollisionModelManagerLocal::FindInternalPolygonEdges(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node,
        cm_polygon_t *polygon)
{
  const idMaterial *material; // eax
  cm_polygonRef_t *i; // edi
  int planeType; // ecx

  material = polygon->material;
  if ( material->cullType != CT_TWO_SIDED && !material->shouldCreateBackSides )
  {
    while ( 1 )
    {
      for ( i = node->polygons; i; i = i->next )
      {
        if ( i->p->contents == polygon->contents && i->p != polygon )
          idCollisionModelManagerLocal::FindInternalEdgesOnPolygon(this, model, polygon, i->p);
      }
      planeType = node->planeType;
      if ( node->planeType == -1 )
        break;
      if ( *(&polygon->bounds.b[0].x + planeType) <= (double)node->planeDist )
      {
        if ( *(&polygon->bounds.b[1].x + planeType) >= (double)node->planeDist )
        {
          idCollisionModelManagerLocal::FindInternalPolygonEdges(this, model, node->children[1], polygon);
          node = node->children[0];
        }
        else
        {
          node = node->children[1];
        }
      }
      else
      {
        node = node->children[0];
      }
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::FindInternalEdges(class idCollisionModelLocal *,struct cm_node_t *)
void __thiscall idCollisionModelManagerLocal::FindInternalEdges(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node)
{
  cm_polygonRef_t *i; // esi
  int checkCount; // ecx
  cm_polygon_t *p; // [esp-4h] [ebp-14h]

  while ( 1 )
  {
    for ( i = node->polygons; i; i = i->next )
    {
      checkCount = this->checkCount;
      if ( i->p->checkcount != checkCount )
      {
        p = i->p;
        i->p->checkcount = checkCount;
        idCollisionModelManagerLocal::FindInternalPolygonEdges(this, model, model->node, p);
      }
    }
    if ( node->planeType == -1 )
      break;
    idCollisionModelManagerLocal::FindInternalEdges(this, model, node->children[1]);
    node = node->children[0];
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::R_FilterPolygonIntoTree(class idCollisionModelLocal *,struct cm_node_t *,struct cm_polygonRef_t *,struct cm_polygon_t *)
void __thiscall idCollisionModelManagerLocal::R_FilterPolygonIntoTree(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node,
        cm_polygonRef_t *pref,
        cm_polygon_t *p)
{
  cm_node_t *v5; // esi
  int planeType; // edx
  int v8; // edx
  cm_polygonRef_t *v9; // eax

  v5 = node;
  if ( node->planeType != -1 )
  {
    while ( 1 )
    {
      planeType = v5->planeType;
      if ( v5->planeType == -1
        || *(&p->bounds.b[0].x + planeType) < (double)v5->planeDist
        && *(&p->bounds.b[1].x + planeType) > (double)v5->planeDist
        && CM_R_InsideAllChildren(v5->children[0], &p->bounds)
        && CM_R_InsideAllChildren(v5->children[1], &p->bounds) )
      {
        goto LABEL_13;
      }
      if ( *(&p->bounds.b[0].x + planeType) >= (double)v5->planeDist )
        goto LABEL_11;
      if ( *(&p->bounds.b[1].x + planeType) > (double)v5->planeDist )
        break;
      v5 = v5->children[1];
LABEL_12:
      if ( v5->planeType == -1 )
        goto LABEL_13;
    }
    idCollisionModelManagerLocal::R_FilterPolygonIntoTree(this, model, v5->children[1], 0, p);
LABEL_11:
    v5 = v5->children[0];
    goto LABEL_12;
  }
LABEL_13:
  if ( pref )
  {
    pref->next = v5->polygons;
    v5->polygons = pref;
  }
  else
  {
    v8 = (model->numPolygonRefs >= 8) - 1;
    LOBYTE(v8) = v8 & 8;
    v9 = idCollisionModelManagerLocal::AllocPolygonReference(this, model, v8 + 256);
    v9->p = p;
    v9->next = v5->polygons;
    v5->polygons = v9;
    ++model->numPolygonRefs;
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::R_FilterBrushIntoTree(class idCollisionModelLocal *,struct cm_node_t *,struct cm_brushRef_t *,struct cm_brush_t *)
void __thiscall idCollisionModelManagerLocal::R_FilterBrushIntoTree(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node,
        cm_brushRef_t *pref,
        cm_brush_t *b)
{
  cm_node_t *v5; // esi
  int planeType; // edx
  int v8; // edx
  cm_brushRef_t *v9; // eax

  v5 = node;
  if ( node->planeType != -1 )
  {
    while ( 1 )
    {
      planeType = v5->planeType;
      if ( v5->planeType == -1
        || *(&b->bounds.b[0].x + planeType) < (double)v5->planeDist
        && *(&b->bounds.b[1].x + planeType) > (double)v5->planeDist
        && CM_R_InsideAllChildren(v5->children[0], &b->bounds)
        && CM_R_InsideAllChildren(v5->children[1], &b->bounds) )
      {
        goto LABEL_13;
      }
      if ( *(&b->bounds.b[0].x + planeType) >= (double)v5->planeDist )
        goto LABEL_11;
      if ( *(&b->bounds.b[1].x + planeType) > (double)v5->planeDist )
        break;
      v5 = v5->children[1];
LABEL_12:
      if ( v5->planeType == -1 )
        goto LABEL_13;
    }
    idCollisionModelManagerLocal::R_FilterBrushIntoTree(this, model, v5->children[1], 0, b);
LABEL_11:
    v5 = v5->children[0];
    goto LABEL_12;
  }
LABEL_13:
  if ( pref )
  {
    pref->next = v5->brushes;
    v5->brushes = pref;
  }
  else
  {
    v8 = (model->numBrushRefs >= 8) - 1;
    LOBYTE(v8) = v8 & 8;
    v9 = idCollisionModelManagerLocal::AllocBrushReference(this, model, v8 + 256);
    v9->b = b;
    v9->next = v5->brushes;
    v5->brushes = v9;
    ++model->numBrushRefs;
  }
}

// FUNC: private: struct cm_node_t * __thiscall idCollisionModelManagerLocal::R_CreateAxialBSPTree(class idCollisionModelLocal *,struct cm_node_t *,class idBounds const &)
cm_node_t *__thiscall idCollisionModelManagerLocal::R_CreateAxialBSPTree(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node,
        const idBounds *bounds)
{
  const idBounds *v4; // esi
  cm_node_t *v5; // edi
  cm_node_t *v7; // ebx
  cm_node_t *v8; // eax
  double v9; // st7
  cm_node_t *v10; // ecx
  float x; // eax
  float z; // edx
  float v13; // eax
  float v14; // edx
  float y; // eax
  float v16; // edx
  int v17; // eax
  cm_node_t *v18; // esi
  cm_polygonRef_t *polygons; // edx
  cm_polygonRef_t *v20; // ebp
  int v21; // ecx
  cm_polygonRef_t *next; // ebx
  cm_polygon_t *p; // edi
  cm_brushRef_t *brushes; // edx
  cm_brushRef_t *v25; // ebp
  int v26; // ecx
  cm_brushRef_t *v27; // ebx
  cm_brush_t *b; // edi
  cm_node_t *frontNode; // [esp+10h] [ebp-3Ch]
  int planeType; // [esp+14h] [ebp-38h] BYREF
  cm_node_t *backNode; // [esp+18h] [ebp-34h]
  idBounds frontBounds; // [esp+1Ch] [ebp-30h] BYREF
  idBounds backBounds; // [esp+34h] [ebp-18h] BYREF

  v4 = bounds;
  v5 = node;
  if ( CM_FindSplitter(bounds, &planeType, node, (float *)&bounds) )
  {
    v7 = idCollisionModelManagerLocal::AllocNode(this, model, 256);
    v7->planeType = 0;
    v7->planeDist = 0.0;
    v7->polygons = 0;
    v7->brushes = 0;
    v7->parent = 0;
    v7->children[0] = 0;
    v7->children[1] = 0;
    frontNode = v7;
    v7->parent = node;
    v7->planeType = -1;
    v8 = idCollisionModelManagerLocal::AllocNode(this, model, 256);
    v9 = *(float *)&bounds;
    v10 = v8;
    v8->planeType = 0;
    v8->planeDist = 0.0;
    v8->polygons = 0;
    v8->brushes = 0;
    v8->parent = 0;
    v8->children[0] = 0;
    v8->children[1] = 0;
    v8->parent = node;
    v8->planeType = -1;
    model->numNodes += 2;
    x = v4->b[0].x;
    frontBounds.b[0].y = v4->b[0].y;
    frontBounds.b[1].x = v4->b[1].x;
    frontBounds.b[1].z = v4->b[1].z;
    backBounds.b[0].x = v4->b[0].x;
    backBounds.b[0].y = v4->b[0].y;
    z = v4->b[0].z;
    frontBounds.b[0].x = x;
    v13 = v4->b[0].z;
    backBounds.b[0].z = z;
    v14 = v4->b[1].x;
    frontBounds.b[0].z = v13;
    y = v4->b[1].y;
    backBounds.b[1].x = v14;
    v16 = v4->b[1].y;
    frontBounds.b[1].y = y;
    v17 = planeType;
    *(&frontBounds.b[0].x + planeType) = v9;
    backBounds.b[1].y = v16;
    backBounds.b[1].z = v4->b[1].z;
    *(&backBounds.b[1].x + v17) = *(float *)&bounds;
    node->planeType = v17;
    backNode = v10;
    node->planeDist = *(float *)&bounds;
    node->children[0] = v7;
    node->children[1] = v10;
    v18 = node;
    do
    {
      polygons = v18->polygons;
      v20 = 0;
      if ( polygons )
      {
        do
        {
          v21 = v18->planeType;
          next = polygons->next;
          p = polygons->p;
          if ( v18->planeType == -1
            || *(&p->bounds.b[0].x + v21) < (double)v18->planeDist
            && *(&p->bounds.b[1].x + v21) > (double)v18->planeDist
            && CM_R_InsideAllChildren(v18->children[0], &polygons->p->bounds)
            && CM_R_InsideAllChildren(v18->children[1], &p->bounds) )
          {
            v20 = polygons;
          }
          else
          {
            idCollisionModelManagerLocal::R_FilterPolygonIntoTree(this, model, v18, polygons, p);
            if ( v20 )
              v20->next = next;
            else
              v18->polygons = next;
          }
          polygons = next;
        }
        while ( next );
        v7 = frontNode;
        v5 = node;
      }
      brushes = v18->brushes;
      v25 = 0;
      if ( brushes )
      {
        do
        {
          v26 = v18->planeType;
          v27 = brushes->next;
          b = brushes->b;
          if ( v18->planeType == -1
            || *(&b->bounds.b[0].x + v26) < (double)v18->planeDist
            && *(&b->bounds.b[1].x + v26) > (double)v18->planeDist
            && CM_R_InsideAllChildren(v18->children[0], &brushes->b->bounds)
            && CM_R_InsideAllChildren(v18->children[1], &b->bounds) )
          {
            v25 = brushes;
          }
          else
          {
            idCollisionModelManagerLocal::R_FilterBrushIntoTree(this, model, v18, brushes, b);
            if ( v25 )
              v25->next = v27;
            else
              v18->brushes = v27;
          }
          brushes = v27;
        }
        while ( v27 );
        v7 = frontNode;
        v5 = node;
      }
      v18 = v18->parent;
    }
    while ( v18 );
    idCollisionModelManagerLocal::R_CreateAxialBSPTree(this, model, v7, &frontBounds);
    idCollisionModelManagerLocal::R_CreateAxialBSPTree(this, model, backNode, &backBounds);
    return v5;
  }
  else
  {
    node->planeType = -1;
    return node;
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ClearHash(class idBounds &)
void __thiscall idCollisionModelManagerLocal::ClearHash(idCollisionModelManagerLocal *this, idBounds *bounds)
{
  idHashIndex *cm_vertexHash; // eax
  int *hash; // edi
  idHashIndex *cm_edgeHash; // eax
  int *v6; // edi
  double v8; // st7
  double v9; // st6
  unsigned __int64 v10; // rax
  int v11; // ecx
  float boundsa; // [esp+Ch] [ebp+4h]

  cm_vertexHash = this->cm_vertexHash;
  hash = cm_vertexHash->hash;
  if ( hash != idHashIndex::INVALID_INDEX )
    memset(hash, 0xFFu, 4 * cm_vertexHash->hashSize);
  cm_edgeHash = this->cm_edgeHash;
  v6 = cm_edgeHash->hash;
  if ( v6 != idHashIndex::INVALID_INDEX )
    memset(v6, 0xFFu, 4 * cm_edgeHash->hashSize);
  this->cm_modelBounds = *bounds;
  v8 = bounds->b[1].x - bounds->b[0].x;
  v9 = bounds->b[1].y - bounds->b[0].y;
  if ( v9 > v8 )
  {
    boundsa = v9;
    v8 = boundsa;
  }
  v10 = (unsigned __int64)(v8 * 0.015625);
  v11 = 0;
  this->cm_vertexShift = v10;
  if ( (int)v10 <= 1 )
    goto LABEL_10;
  do
    ++v11;
  while ( 1 << v11 < (int)v10 );
  if ( v11 )
    this->cm_vertexShift = v11;
  else
LABEL_10:
    this->cm_vertexShift = 1;
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::GetVertex(class idCollisionModelLocal *,class idVec3 const &,int *)
int __thiscall idCollisionModelManagerLocal::GetVertex(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        const idVec3 *v,
        int *vertexNum)
{
  const idVec3 *v4; // esi
  int v6; // ebx
  __int16 v7; // si
  double v8; // st7
  idHashIndex *cm_vertexHash; // edi
  int v10; // esi
  int v11; // ecx
  cm_vertex_t *v12; // edx
  double v13; // st7
  float *p_x; // edx
  unsigned __int64 v15; // rax
  cm_vertex_t *vertices; // esi
  cm_vertex_t *v17; // eax
  unsigned int v18; // edx
  cm_vertex_t *v19; // ecx
  int numVertices; // eax
  int p_p; // eax
  float y; // ecx
  idHashIndex *v23; // edi
  int v24; // ecx
  int indexSize; // eax
  int v27; // eax
  float v28; // [esp+18h] [ebp-28h]
  float v29; // [esp+18h] [ebp-28h]
  float x; // [esp+1Ch] [ebp-24h]
  float v31; // [esp+1Ch] [ebp-24h]
  int oldVertices; // [esp+20h] [ebp-20h]
  float oldVerticesb; // [esp+20h] [ebp-20h]
  cm_vertex_t *oldVerticesa; // [esp+20h] [ebp-20h]
  int hashKey; // [esp+28h] [ebp-18h]
  idVec3 vert; // [esp+34h] [ebp-Ch] BYREF

  v4 = v;
  v6 = (char *)&vert - (char *)v;
  oldVertices = 3;
  do
  {
    x = v4->x;
    v28 = x - floor(v4->x + 0.5);
    HIBYTE(v28) &= ~0x80u;
    if ( v28 >= 0.0099999998 )
      *(float *)((char *)&v4->x + v6) = v4->x;
    else
      *(float *)((char *)&v4->x + v6) = floor(v4->x + 0.5);
    v4 = (const idVec3 *)((char *)v4 + 4);
    --oldVertices;
  }
  while ( oldVertices );
  v7 = ((int)((__int64)(vert.z - this->cm_modelBounds.b[0].z + 0.5) + 2) >> 2)
     + ((unsigned __int16)((int)((__int64)(vert.y - this->cm_modelBounds.b[0].y + 0.5) + 2) >> 2) << 6);
  v8 = vert.x - this->cm_modelBounds.b[0].x;
  cm_vertexHash = this->cm_vertexHash;
  v10 = ((unsigned __int16)((int)((__int64)(v8 + 0.5) + 2) >> 2) + v7) & 0xFFF;
  v11 = cm_vertexHash->hash[v10 & cm_vertexHash->hashMask & cm_vertexHash->lookupMask];
  hashKey = v10;
  if ( v11 < 0 )
  {
LABEL_11:
    if ( model->numVertices >= model->maxVertices )
    {
      v15 = (unsigned __int64)((double)model->maxVertices * 1.5 + 1.0);
      vertices = model->vertices;
      model->maxVertices = v15;
      v17 = (cm_vertex_t *)Mem_ClearedAlloc(24 * v15, 8u);
      v18 = 24 * model->numVertices;
      model->vertices = v17;
      qmemcpy(v17, vertices, v18);
      Mem_Free(vertices);
      idHashIndex::ResizeIndex(this->cm_vertexHash, model->maxVertices);
      v10 = hashKey;
    }
    v19 = model->vertices;
    numVertices = model->numVertices;
    v19[numVertices].p.x = vert.x;
    p_p = (int)&v19[numVertices].p;
    y = vert.y;
    *(float *)(p_p + 8) = vert.z;
    *(float *)(p_p + 4) = y;
    model->vertices[model->numVertices].checkcount = 0;
    *vertexNum = model->numVertices;
    v23 = this->cm_vertexHash;
    v24 = model->numVertices;
    oldVerticesa = (cm_vertex_t *)v24;
    if ( v23->hash == idHashIndex::INVALID_INDEX )
    {
      indexSize = v23->indexSize;
      if ( v24 >= indexSize )
        indexSize = v24 + 1;
      idHashIndex::Allocate(v23, v23->hashSize, indexSize);
    }
    else
    {
      if ( v24 < v23->indexSize )
      {
LABEL_21:
        v27 = v10 & v23->hashMask;
        v23->indexChain[v24] = v23->hash[v27];
        v23->hash[v27] = v24;
        ++model->numVertices;
        return 0;
      }
      idHashIndex::ResizeIndex(v23, v24 + 1);
    }
    v24 = (int)oldVerticesa;
    goto LABEL_21;
  }
  while ( 1 )
  {
    v12 = model->vertices;
    v13 = vert.z - v12[v11].p.z;
    p_x = &v12[v11].p.x;
    v29 = v13;
    HIBYTE(v29) &= ~0x80u;
    if ( v29 < 0.1 )
    {
      v31 = vert.x - *p_x;
      HIBYTE(v31) &= ~0x80u;
      if ( v31 < 0.1 )
      {
        oldVerticesb = vert.y - p_x[1];
        HIBYTE(oldVerticesb) &= ~0x80u;
        if ( oldVerticesb < 0.1 )
          break;
      }
    }
    v11 = cm_vertexHash->indexChain[v11 & cm_vertexHash->lookupMask];
    if ( v11 < 0 )
      goto LABEL_11;
  }
  *vertexNum = v11;
  return 1;
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::GetEdge(class idCollisionModelLocal *,class idVec3 const &,class idVec3 const &,int *,int)
int __thiscall idCollisionModelManagerLocal::GetEdge(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        idVec3 *v1,
        unsigned int v2,
        int *edgeNum,
        idCollisionModelLocal *v1num)
{
  idCollisionModelLocal *v6; // ebx
  idCollisionModelLocal *v8; // edi
  int v9; // esi
  int Vertex; // eax
  int v11; // esi
  idHashIndex *cm_edgeHash; // ecx
  unsigned int v14; // eax
  int v15; // eax
  cm_edge_t *edges; // edx
  bool v17; // zf
  cm_edge_t *v18; // edx
  bool v19; // cc
  unsigned __int64 v20; // rax
  const idVec3 *v21; // esi
  cm_edge_t *v22; // eax
  unsigned int v23; // ecx
  idVec3 *p_normal; // eax
  int *v25; // edx
  idHashIndex *v26; // esi
  int numEdges; // edi
  int indexSize; // eax
  unsigned int v29; // eax

  v6 = model;
  if ( !model->numEdges )
    model->numEdges = 1;
  v8 = v1num;
  if ( v1num == (idCollisionModelLocal *)-1 )
  {
    Vertex = idCollisionModelManagerLocal::GetVertex(this, v6, v1, (int *)&v1num);
    v8 = v1num;
    v9 = Vertex;
  }
  else
  {
    v9 = 1;
  }
  v11 = idCollisionModelManagerLocal::GetVertex(this, v6, (const idVec3 *)v2, (int *)&model) & v9;
  if ( v8 == model )
  {
    *edgeNum = 0;
    return 1;
  }
  else
  {
    cm_edgeHash = this->cm_edgeHash;
    v14 = cm_edgeHash->hashMask & ((int)model + (_DWORD)v8);
    v2 = v14;
    if ( v11 && (v15 = cm_edgeHash->hash[v14 & cm_edgeHash->hashMask & cm_edgeHash->lookupMask], v15 >= 0) )
    {
      while ( 1 )
      {
        edges = v6->edges;
        v17 = edges[v15].numUsers == 1;
        v18 = &edges[v15];
        if ( v17
          && (idCollisionModelLocal *)v18->vertexNum[0] == model
          && (idCollisionModelLocal *)v18->vertexNum[1] == v8 )
        {
          break;
        }
        v15 = cm_edgeHash->indexChain[v15 & cm_edgeHash->lookupMask];
        if ( v15 < 0 )
          goto LABEL_14;
      }
      *edgeNum = -v15;
      ++v6->edges[v15].numUsers;
      return 1;
    }
    else
    {
LABEL_14:
      v19 = v6->numEdges < v6->maxEdges;
      v1 = (idVec3 *)v6->maxEdges;
      if ( !v19 )
      {
        v20 = (unsigned __int64)((double)(int)v1 * 1.5 + 1.0);
        v21 = (const idVec3 *)v6->edges;
        v6->maxEdges = v20;
        v1 = (idVec3 *)v21;
        v22 = (cm_edge_t *)Mem_ClearedAlloc(36 * v20, 8u);
        v23 = 36 * v6->numEdges;
        v6->edges = v22;
        qmemcpy(v22, v21, v23);
        Mem_Free(v1);
        idHashIndex::ResizeIndex(this->cm_edgeHash, v6->maxEdges);
        v8 = v1num;
      }
      v6->edges[v6->numEdges].vertexNum[0] = (int)v8;
      v6->edges[v6->numEdges].vertexNum[1] = (int)model;
      v6->edges[v6->numEdges].internal = 0;
      v6->edges[v6->numEdges].checkcount = 0;
      v6->edges[v6->numEdges].numUsers = 1;
      p_normal = &v6->edges[v6->numEdges].normal;
      v25 = edgeNum;
      p_normal->z = 0.0;
      p_normal->y = 0.0;
      p_normal->x = 0.0;
      *v25 = v6->numEdges;
      v26 = this->cm_edgeHash;
      numEdges = v6->numEdges;
      if ( v26->hash == idHashIndex::INVALID_INDEX )
      {
        indexSize = v26->indexSize;
        if ( numEdges >= indexSize )
          indexSize = numEdges + 1;
        idHashIndex::Allocate(v26, v26->hashSize, indexSize);
      }
      else if ( numEdges >= v26->indexSize )
      {
        idHashIndex::ResizeIndex(v26, numEdges + 1);
      }
      v29 = v2 & v26->hashMask;
      v26->indexChain[numEdges] = v26->hash[v29];
      v26->hash[v29] = numEdges;
      ++v6->numEdges;
      return 0;
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::CreatePolygon(class idCollisionModelLocal *,class idFixedWinding *,class idPlane const &,class idMaterial const *,int)
void __thiscall idCollisionModelManagerLocal::CreatePolygon(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        idFixedWinding *w,
        const idPlane *plane,
        const idMaterial *material,
        int primitiveNum)
{
  int numPoints; // eax
  int v7; // edi
  int v8; // esi
  int v9; // ecx
  int v10; // ecx
  int j; // eax
  int v12; // ebx
  int v13; // ecx
  unsigned int v14; // esi
  double v15; // st7
  int v16; // ecx
  cm_polygon_t *polygons; // esi
  cm_polygon_t *v18; // esi
  int numPolygons; // eax
  int contentFlags; // edx
  idVec5 *p; // edx
  idVec5 *v22; // eax
  idVec5 *v23; // ecx
  idVec5 *v24; // edx
  int k; // eax
  int i; // [esp+8h] [ebp-27Ch]
  float ia; // [esp+8h] [ebp-27Ch]
  int v28; // [esp+Ch] [ebp-278h]
  int v1num; // [esp+10h] [ebp-274h]
  idBounds bounds; // [esp+18h] [ebp-26Ch] BYREF
  float v32[2]; // [esp+30h] [ebp-254h]
  float v33; // [esp+38h] [ebp-24Ch]
  idVec3 point; // [esp+3Ch] [ebp-248h] BYREF
  idVec3 t[3]; // [esp+48h] [ebp-23Ch] BYREF
  idVec2 tc[3]; // [esp+6Ch] [ebp-218h] BYREF
  int windingIndices[64]; // [esp+84h] [ebp-200h]
  int polyEdges[64]; // [esp+184h] [ebp-100h] BYREF

  numPoints = w->numPoints;
  v7 = 0;
  v1num = -1;
  i = 0;
  v8 = 1;
  if ( numPoints > 0 )
  {
    v28 = 0;
    do
    {
      if ( v8 >= numPoints )
        v8 = 0;
      idCollisionModelManagerLocal::GetEdge(
        this,
        model,
        (const idVec3 *)&w->p[v28],
        (const idVec3 *)&w->p[v8],
        &polyEdges[v7],
        v1num);
      v9 = polyEdges[v7];
      if ( v9 )
      {
        v10 = model->edges[abs32(v9)].vertexNum[v9 >= 0];
        windingIndices[v7] = i;
        v1num = v10;
        ++v7;
      }
      numPoints = w->numPoints;
      ++v28;
      ++v8;
      ++i;
    }
    while ( i < numPoints );
    if ( v7 >= 3 )
    {
      for ( j = 0; ; ++j )
      {
        v12 = j + 1;
        v13 = j + 1;
        if ( j + 1 < v7 )
          break;
LABEL_14:
        if ( v12 >= v7 )
        {
          if ( v7 > 64 )
          {
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
              common.type,
              "idCollisionModelManagerLocal::CreatePolygon: polygon has more than %d edges",
              v7);
            v7 = 64;
          }
          idWinding::GetBounds(w, &bounds);
          v32[0] = bounds.b[1].x - bounds.b[0].x;
          point = bounds.b[0];
          v15 = bounds.b[1].y - bounds.b[0].y;
          v32[1] = v15;
          v33 = bounds.b[1].z - bounds.b[0].z;
          v16 = v15 > v32[0];
          if ( v33 > (double)v32[v16] )
            v16 = 2;
          polygons = model->polygons;
          *((_DWORD *)&point.x + v16) = *((_DWORD *)&bounds.b[1].x + v16);
          if ( polygons || model->polygonEdges )
          {
            numPolygons = model->numPolygons;
            v18 = &polygons[numPolygons];
            model->numPolygons = numPolygons + 1;
            v18->numEdges = v7;
            v18->edges = &model->polygonEdges[model->numPolygonEdges];
            model->numPolygonEdges += v7;
          }
          else
          {
            ++model->numPolygons;
            model->numPolygonEdges += v7;
            v18 = (cm_polygon_t *)Mem_Alloc(4 * v7 + 88, 8u);
            v18->edges = (int *)&v18[1];
          }
          v18->numEdges = v7;
          contentFlags = material->contentFlags;
          v18->material = material;
          v18->contents = contentFlags;
          v18->checkcount = 0;
          v18->primitiveNum = abs32(primitiveNum);
          v18->plane = *plane;
          v18->bounds = bounds;
          v18->texBounds[0].y = 0.0;
          v18->texBounds[0].x = 0.0;
          v18->texBounds[1].y = 0.0;
          v18->texBounds[1].x = 0.0;
          v18->texBounds[2].y = 0.0;
          v18->texBounds[2].x = 0.0;
          p = w->p;
          t[0].x = p[windingIndices[0]].x;
          t[0].y = p[windingIndices[0]].y;
          v22 = &p[windingIndices[0]];
          t[0].z = v22->z;
          t[1].x = p[windingIndices[1]].x;
          v23 = &p[windingIndices[1]];
          t[1].y = v23->y;
          t[1].z = v23->z;
          v24 = &p[windingIndices[2]];
          t[2] = *(idVec3 *)&v24->x;
          tc[0] = *(idVec2 *)&v22->s;
          tc[1] = *(idVec2 *)&v23->s;
          tc[2] = *(idVec2 *)&v24->s;
          ia = idMath::BarycentricTriangleArea((const idVec3 *)&v18->plane, t, &t[1], &t[2]);
          if ( ia != 0.0 )
          {
            idMath::BarycentricEvaluate(v18->texBounds, v18->bounds.b, (const idVec3 *)&v18->plane, ia, t, tc);
            idMath::BarycentricEvaluate(&v18->texBounds[1], &v18->bounds.b[1], (const idVec3 *)&v18->plane, ia, t, tc);
            idMath::BarycentricEvaluate(&v18->texBounds[2], &point, (const idVec3 *)&v18->plane, ia, t, tc);
          }
          for ( k = 0; k < v7; ++k )
            v18->edges[k] = polyEdges[k];
          idCollisionModelManagerLocal::R_FilterPolygonIntoTree(this, model, model->node, 0, v18);
          return;
        }
      }
      v14 = abs32(polyEdges[j]);
      while ( v14 != abs32(polyEdges[v13]) )
      {
        if ( ++v13 >= v7 )
          goto LABEL_14;
      }
    }
  }
}

// FUNC: CM_EstimateVertsAndEdges
void __usercall CM_EstimateVertsAndEdges(int *numVerts@<edi>, int *numEdges@<esi>, const idMapEntity *mapEnt)
{
  const idMapEntity *v3; // edx
  int v4; // ebp
  idMapPrimitive *v5; // eax
  int type; // ecx
  idKeyValue *list; // edx
  int granularity; // ecx

  v3 = mapEnt;
  *numVerts = 0;
  v4 = 0;
  for ( *numEdges = 0; v4 < v3->primitives.num; ++v4 )
  {
    v5 = v3->primitives.list[v4];
    type = v5->type;
    if ( type == 1 )
    {
      list = v5[2].epairs.args.list;
      granularity = v5[2].epairs.args.granularity;
      *numVerts += granularity * (_DWORD)list;
      *numEdges += granularity * ((_DWORD)list - 1) + (granularity - 1) * ((int)list + (_DWORD)list - 1);
      v3 = mapEnt;
    }
    else if ( !type )
    {
      *numVerts += 2 * (int)v5[1].__vftable - 4;
      *numEdges += 3 * ((int)&v5[1].__vftable[-1].AdjustOrigin + 2);
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ConvertBrush(class idCollisionModelLocal *,class idMapBrush const *,int)
void __thiscall idCollisionModelManagerLocal::ConvertBrush(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        const idMapBrush *mapBrush,
        int primitiveNum)
{
  const idMapBrush *v4; // edi
  int num; // esi
  int v6; // eax
  void *v7; // esp
  idPlane *v8; // eax
  int v9; // ecx
  float *p_b; // esi
  idPlane *p_plane; // eax
  float *v12; // ecx
  unsigned __int8 v14; // c2
  unsigned __int8 v15; // c3
  bool v16; // cc
  float *p_c; // ebx
  const idMaterial *v18; // eax
  double v19; // st7
  double v20; // st6
  double v21; // st5
  int v22; // esi
  float *v23; // edi
  double v24; // st7
  double v25; // st6
  double v26; // st5
  int numPoints; // edx
  float *p_z; // ecx
  int v29; // eax
  idCollisionModelLocal *v30; // ebx
  cm_brush_t *v31; // esi
  const idMaterial *v32; // eax
  float x; // eax
  float y; // edx
  int v35; // ecx
  float z; // eax
  float v37; // edx
  float v38; // eax
  float v39; // edx
  int v40; // eax
  idPlane *v41; // edx
  int v42; // edi
  cm_node_t *node; // edi
  int v44; // eax
  cm_brushRef_t *v45; // eax
  float X_4; // [esp+8h] [ebp-57Ch]
  idFixedWinding w; // [esp+18h] [ebp-56Ch] BYREF
  idVec3 normal; // [esp+528h] [ebp-5Ch] BYREF
  float v49; // [esp+534h] [ebp-50h]
  idPlane plane; // [esp+538h] [ebp-4Ch] BYREF
  idCollisionModelManagerLocal *v51; // [esp+548h] [ebp-3Ch]
  idBounds bounds; // [esp+54Ch] [ebp-38h]
  idPlane *planes; // [esp+564h] [ebp-20h]
  int contents; // [esp+568h] [ebp-1Ch]
  const idMaterial *material; // [esp+56Ch] [ebp-18h]
  int i; // [esp+570h] [ebp-14h]
  float v57; // [esp+574h] [ebp-10h]
  int v58; // [esp+580h] [ebp-4h]

  v51 = this;
  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v4 = mapBrush;
  bounds.b[1].z = -1.0e30;
  num = mapBrush->sides.num;
  bounds.b[1].y = bounds.b[1].z;
  bounds.b[1].x = bounds.b[1].z;
  bounds.b[0].x = idMath::INFINITY;
  v6 = 16 * num + 18;
  LOBYTE(v6) = v6 & 0xFC;
  v58 = 0;
  contents = 0;
  bounds.b[0].z = idMath::INFINITY;
  bounds.b[0].y = idMath::INFINITY;
  v7 = alloca(v6);
  v8 = (idPlane *)((char *)&w.__vftable + 3);
  LOBYTE(v8) = ((unsigned __int8)&w.__vftable + 3) & 0xF0;
  v9 = 0;
  i = 0;
  planes = v8;
  if ( num <= 0 )
    goto LABEL_40;
  p_b = &v8->b;
  do
  {
    p_plane = &mapBrush->sides.list[v9]->plane;
    v12 = p_b - 1;
    *(idPlane *)(p_b - 1) = *p_plane;
    if ( v15 | v14 )
    {
      if ( *p_b == 0.0 )
      {
        if ( p_b[1] <= 0.0 )
        {
          if ( *((_DWORD *)p_b + 1) == -1082130432 )
            goto LABEL_38;
          p_b[1] = -1.0;
        }
        else
        {
          if ( *((_DWORD *)p_b + 1) == 1065353216 )
            goto LABEL_38;
          p_b[1] = 1.0;
        }
        goto LABEL_36;
      }
      if ( p_b[1] == 0.0 )
      {
        if ( *p_b <= 0.0 )
        {
          if ( *(_DWORD *)p_b == -1082130432 )
            goto LABEL_38;
          *p_b = -1.0;
        }
        else
        {
          if ( *(_DWORD *)p_b == 1065353216 )
            goto LABEL_38;
          *p_b = 1.0;
        }
        goto LABEL_36;
      }
    }
    else if ( *p_b == 0.0 && p_b[1] == 0.0 )
    {
      if ( *v12 <= 0.0 )
      {
        if ( *(_DWORD *)v12 == -1082130432 )
          goto LABEL_38;
        *v12 = -1.0;
      }
      else
      {
        if ( *(_DWORD *)v12 == 1065353216 )
          goto LABEL_38;
        *v12 = 1.0;
      }
      goto LABEL_36;
    }
    v57 = *v12;
    LODWORD(v57) &= ~0x80000000;
    if ( v57 == 1.0 )
    {
      if ( *p_b == 0.0 && p_b[1] == 0.0 )
        goto LABEL_38;
      p_b[1] = 0.0;
    }
    else
    {
      v57 = *p_b;
      LODWORD(v57) &= ~0x80000000;
      if ( v57 == 1.0 )
      {
        if ( *v12 == 0.0 && p_b[1] == 0.0 )
          goto LABEL_38;
        p_b[1] = 0.0;
        *v12 = 0.0;
        goto LABEL_36;
      }
      v57 = p_b[1];
      LODWORD(v57) &= ~0x80000000;
      if ( v57 != 1.0 || *v12 == 0.0 && *p_b == 0.0 )
        goto LABEL_38;
      *v12 = 0.0;
    }
    *p_b = 0.0;
LABEL_36:
    *(float *)&material = p_b[2] - floor(p_b[2] + 0.5);
    HIBYTE(material) &= ~0x80u;
    if ( *(float *)&material < 0.000099999997 )
      p_b[2] = floor(p_b[2] + 0.5);
LABEL_38:
    v9 = i + 1;
    p_b += 4;
    v16 = ++i < mapBrush->sides.num;
  }
  while ( v16 );
  v8 = planes;
LABEL_40:
  v16 = mapBrush->sides.num - 1 <= 0;
  i = 0;
  if ( v16 )
    goto LABEL_66;
  p_c = &v8->c;
  do
  {
    *(float *)&v18 = COERCE_FLOAT((int)declManager->FindMaterial(declManager, v4->sides.list[i]->material.data, 1));
    v19 = -p_c[1];
    material = v18;
    v20 = -*p_c;
    v21 = *(p_c - 1);
    contents |= v18->contentFlags & 0xFFCFFFFF;
    normal.x = -*(p_c - 2);
    normal.y = -v21;
    normal.z = v20;
    v49 = v19;
    X_4 = -v19;
    idWinding::BaseForPlane(&w, &normal, X_4);
    v22 = 0;
    if ( v4->sides.num > 0 )
    {
      v23 = &planes->c;
      do
      {
        if ( !w.numPoints )
          break;
        if ( i != v22 )
        {
          v24 = -v23[1];
          v25 = -*v23;
          v26 = -*(v23 - 1);
          plane.a = -*(v23 - 2);
          plane.b = v26;
          plane.c = v25;
          plane.d = v24;
          idWinding::ClipInPlace(&w, &plane, 0.0, 0);
        }
        ++v22;
        v23 += 4;
      }
      while ( v22 < mapBrush->sides.num );
      v4 = mapBrush;
    }
    numPoints = w.numPoints;
    if ( w.numPoints > 0 )
    {
      p_z = &w.p->z;
      do
      {
        if ( *(p_z - 2) < (double)bounds.b[0].x )
          bounds.b[0].x = *(p_z - 2);
        if ( *(p_z - 2) > (double)bounds.b[1].x )
          bounds.b[1].x = *(p_z - 2);
        if ( *(p_z - 1) < (double)bounds.b[0].y )
          bounds.b[0].y = *(p_z - 1);
        if ( *(p_z - 1) > (double)bounds.b[1].y )
          bounds.b[1].y = *(p_z - 1);
        if ( *p_z < (double)bounds.b[0].z )
          bounds.b[0].z = *p_z;
        if ( *p_z > (double)bounds.b[1].z )
          bounds.b[1].z = *p_z;
        p_z += 5;
        --numPoints;
      }
      while ( numPoints );
    }
    v29 = v4->sides.num - 1;
    p_c += 4;
    ++i;
  }
  while ( i < v29 );
  if ( contents )
  {
    v30 = model;
    v31 = idCollisionModelManagerLocal::AllocBrush(v51, model, v4->sides.num);
    v32 = material;
    v31->contents = contents;
    v31->material = v32;
    x = bounds.b[0].x;
    v31->primitiveNum = primitiveNum;
    y = bounds.b[0].y;
    v35 = 0;
    v31->checkcount = 0;
    v31->bounds.b[0].x = x;
    z = bounds.b[0].z;
    v31->bounds.b[0].y = y;
    v37 = bounds.b[1].x;
    v31->bounds.b[0].z = z;
    v38 = bounds.b[1].y;
    v31->bounds.b[1].x = v37;
    v39 = bounds.b[1].z;
    v31->bounds.b[1].y = v38;
    v31->bounds.b[1].z = v39;
    v31->numPlanes = v4->sides.num;
    if ( v4->sides.num > 0 )
    {
      v40 = 0;
      do
      {
        v41 = &planes[v40];
        v42 = (int)&v31->planes[v40];
        *(float *)v42 = planes[v40].a;
        *(float *)(v42 + 4) = v41->b;
        *(float *)(v42 + 8) = v41->c;
        *(float *)(v42 + 12) = v41->d;
        ++v35;
        ++v40;
      }
      while ( v35 < mapBrush->sides.num );
      v30 = model;
    }
    node = v30->node;
    v44 = (v30->numBrushRefs >= 8) - 1;
    LOBYTE(v44) = v44 & 8;
    v45 = idCollisionModelManagerLocal::AllocBrushReference(v51, v30, v44 + 256);
    v45->b = v31;
    v45->next = node->brushes;
    node->brushes = v45;
    ++v30->numBrushRefs;
    w.p = 0;
  }
  else
  {
LABEL_66:
    w.p = 0;
  }
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  v58 = -1;
  Memory::Free(0);
}

// FUNC: CM_R_GetNodeBounds
void __cdecl CM_R_GetNodeBounds(idBounds *bounds, cm_node_t *node)
{
  cm_polygonRef_t *i; // edx
  float *p; // ecx
  float *p_x; // ecx
  cm_brushRef_t *j; // edx
  float *b; // ecx
  float *v8; // ecx

  while ( 1 )
  {
    for ( i = node->polygons; i; i = i->next )
    {
      p = (float *)i->p;
      if ( i->p->bounds.b[0].x < (double)bounds->b[0].x )
        bounds->b[0].x = *p;
      if ( *p > (double)bounds->b[1].x )
        bounds->b[1].x = *p;
      if ( p[1] < (double)bounds->b[0].y )
        bounds->b[0].y = p[1];
      if ( p[1] > (double)bounds->b[1].y )
        bounds->b[1].y = p[1];
      if ( p[2] < (double)bounds->b[0].z )
        bounds->b[0].z = p[2];
      if ( p[2] > (double)bounds->b[1].z )
        bounds->b[1].z = p[2];
      p_x = &i->p->bounds.b[1].x;
      if ( *p_x < (double)bounds->b[0].x )
        bounds->b[0].x = *p_x;
      if ( *p_x > (double)bounds->b[1].x )
        bounds->b[1].x = *p_x;
      if ( p_x[1] < (double)bounds->b[0].y )
        bounds->b[0].y = p_x[1];
      if ( p_x[1] > (double)bounds->b[1].y )
        bounds->b[1].y = p_x[1];
      if ( p_x[2] < (double)bounds->b[0].z )
        bounds->b[0].z = p_x[2];
      if ( p_x[2] > (double)bounds->b[1].z )
        bounds->b[1].z = p_x[2];
    }
    for ( j = node->brushes; j; j = j->next )
    {
      b = (float *)j->b;
      if ( j->b->bounds.b[0].x < (double)bounds->b[0].x )
        bounds->b[0].x = *b;
      if ( *b > (double)bounds->b[1].x )
        bounds->b[1].x = *b;
      if ( b[1] < (double)bounds->b[0].y )
        bounds->b[0].y = b[1];
      if ( b[1] > (double)bounds->b[1].y )
        bounds->b[1].y = b[1];
      if ( b[2] < (double)bounds->b[0].z )
        bounds->b[0].z = b[2];
      if ( b[2] > (double)bounds->b[1].z )
        bounds->b[1].z = b[2];
      v8 = &j->b->bounds.b[1].x;
      if ( *v8 < (double)bounds->b[0].x )
        bounds->b[0].x = *v8;
      if ( *v8 > (double)bounds->b[1].x )
        bounds->b[1].x = *v8;
      if ( v8[1] < (double)bounds->b[0].y )
        bounds->b[0].y = v8[1];
      if ( v8[1] > (double)bounds->b[1].y )
        bounds->b[1].y = v8[1];
      if ( v8[2] < (double)bounds->b[0].z )
        bounds->b[0].z = v8[2];
      if ( v8[2] > (double)bounds->b[1].z )
        bounds->b[1].z = v8[2];
    }
    if ( node->planeType == -1 )
      break;
    CM_R_GetNodeBounds(bounds, node->children[1]);
    node = node->children[0];
  }
}

// FUNC: void __cdecl CM_GetNodeBounds(class idBounds *,struct cm_node_t *)
void __cdecl CM_GetNodeBounds(idBounds *bounds, cm_node_t *node)
{
  bounds->b[0].z = idMath::INFINITY;
  bounds->b[0].y = idMath::INFINITY;
  bounds->b[0].x = idMath::INFINITY;
  bounds->b[1].z = -1.0e30;
  bounds->b[1].y = -1.0e30;
  bounds->b[1].x = -1.0e30;
  CM_R_GetNodeBounds(bounds, node);
  if ( bounds->b[0].x > (double)bounds->b[1].x )
  {
    bounds->b[1].z = 0.0;
    bounds->b[1].y = 0.0;
    bounds->b[1].x = 0.0;
    bounds->b[0].z = 0.0;
    bounds->b[0].y = 0.0;
    bounds->b[0].x = 0.0;
  }
}

// FUNC: private: class idCollisionModelLocal * __thiscall idCollisionModelManagerLocal::FindModel(char const *)
idCollisionModelLocal *__thiscall idCollisionModelManagerLocal::FindModel(
        idCollisionModelManagerLocal *this,
        const char *name)
{
  int i; // esi

  for ( i = 0; i < this->models.num; ++i )
  {
    if ( !idStr::Icmp(this->models.list[i]->name.data, name) )
      break;
  }
  if ( i >= this->models.num )
    return 0;
  else
    return this->models.list[i];
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::AccumulateModelInfo(class idCollisionModelLocal *)
void __thiscall idCollisionModelManagerLocal::AccumulateModelInfo(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model)
{
  int v2; // eax

  v2 = 0;
  memset(model, 0, sizeof(idCollisionModelLocal));
  if ( this->models.num > 0 )
  {
    do
    {
      model->numVertices += this->models.list[v2]->numVertices;
      model->numEdges += this->models.list[v2]->numEdges;
      model->numPolygonEdges += this->models.list[v2]->numPolygonEdges;
      model->numPolygons += this->models.list[v2]->numPolygons;
      model->numBrushes += this->models.list[v2]->numBrushes;
      model->numBrushPlanes += this->models.list[v2]->numBrushPlanes;
      model->numNodes += this->models.list[v2]->numNodes;
      model->numBrushRefs += this->models.list[v2]->numBrushRefs;
      model->numPolygonRefs += this->models.list[v2]->numPolygonRefs;
      model->numInternalEdges += this->models.list[v2]->numInternalEdges;
      model->numSharpEdges += this->models.list[v2]->numSharpEdges;
      model->numRemovedPolys += this->models.list[v2]->numRemovedPolys;
      model->numMergedPolys += this->models.list[v2]->numMergedPolys;
      model->usedMemory += this->models.list[v2++]->usedMemory;
    }
    while ( v2 < this->models.num );
  }
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::ModelInfo(int)
void __thiscall idCollisionModelManagerLocal::ModelInfo(idCollisionModelManagerLocal *this, int num)
{
  idCollisionModelLocal modelInfo; // [esp+4h] [ebp-D4h] BYREF
  int v4; // [esp+D4h] [ebp-4h]

  modelInfo.__vftable = (idCollisionModelLocal_vtbl *)&idCollisionModelLocal::`vftable';
  modelInfo.name.len = 0;
  modelInfo.name.alloced = 20;
  modelInfo.name.data = modelInfo.name.baseBuffer;
  modelInfo.name.baseBuffer[0] = 0;
  v4 = 0;
  if ( num >= 0 )
  {
    idCollisionModelManagerLocal::PrintModelInfo(this, this->models.list[num]);
    v4 = 2;
  }
  else
  {
    idCollisionModelManagerLocal::AccumulateModelInfo(this, &modelInfo);
    idCollisionModelManagerLocal::PrintModelInfo(this, &modelInfo);
    v4 = 1;
  }
  idStr::FreeData(&modelInfo.name);
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::ListModels(void)
void __thiscall idCollisionModelManagerLocal::ListModels(idCollisionModelManagerLocal *this)
{
  int v2; // esi
  int i; // ebx
  idCollisionModelLocal *v4; // eax

  v2 = 0;
  for ( i = 0; v2 < this->models.num; ++v2 )
  {
    v4 = this->models.list[v2];
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%4d: %5d KB   %s\n",
      v2,
      v4->usedMemory >> 10,
      v4->name.data);
    i += this->models.list[v2]->usedMemory;
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%4d KB in %d models\n",
    i >> 10,
    this->models.num);
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::IsRenderModelName(char const *)const
bool __thiscall idCollisionModelManagerLocal::IsRenderModelName(
        idCollisionModelManagerLocal *this,
        const char *modelName)
{
  int v2; // eax
  int v4; // eax

  v2 = 0;
  do
    ++v2;
  while ( aModels[v2] );
  if ( !idStr::IcmpnPath(modelName, "models/", v2) )
    return 1;
  v4 = 0;
  do
    ++v4;
  while ( aGfx[v4] );
  return idStr::IcmpnPath(modelName, "gfx/", v4) == 0;
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::PreCacheModel(char const *,char const *)
void __thiscall idCollisionModelManagerLocal::PreCacheModel(
        idCollisionModelManagerLocal *this,
        const char *mapName,
        const char *modelName)
{
  const char *FullModelName; // eax
  const char *v5; // esi
  int v6; // ebp
  char *data; // edx
  char *v8; // ecx
  char v9; // al
  idStr name; // [esp+8h] [ebp-2Ch] BYREF
  int v11; // [esp+30h] [ebp-4h]

  FullModelName = idCollisionModelManagerLocal::GetFullModelName(this, mapName, modelName);
  v5 = FullModelName;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  if ( FullModelName )
  {
    v6 = strlen(FullModelName);
    if ( v6 + 1 > 20 )
      idStr::ReAllocate(&name, v6 + 1, 1);
    data = name.data;
    v8 = (char *)v5;
    do
    {
      v9 = *v8;
      *data++ = *v8++;
    }
    while ( v9 );
    name.len = v6;
  }
  v11 = 0;
  if ( !idCollisionModelManagerLocal::FindModel(this, name.data)
    && this->LoadModel(this, mapName, name.data)
    && !idCollisionModelManagerLocal::FindModel(this, name.data) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idCollisionModelManagerLocal::PreCacheModel: collision file for '%s' contains different model",
      name.data);
  }
  v11 = -1;
  idStr::FreeData(&name);
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::TrmFromModel_r(class idTraceModel &,struct cm_node_t *,int)
char __thiscall idCollisionModelManagerLocal::TrmFromModel_r(
        idCollisionModelManagerLocal *this,
        idTraceModel *trm,
        cm_node_t *node,
        int primitiveNum)
{
  int v4; // ebx
  idCollisionModelManagerLocal *v5; // ebp
  cm_node_t *v6; // eax
  cm_polygonRef_t *polygons; // edi
  cm_polygon_t *p; // eax
  int checkCount; // ecx
  int numPolys; // ecx
  idBounds *p_bounds; // ecx
  traceModelPoly_t *v12; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ebp

  v4 = primitiveNum;
  v5 = this;
  while ( 1 )
  {
    v6 = node;
    polygons = node->polygons;
    if ( polygons )
    {
      do
      {
        p = polygons->p;
        checkCount = v5->checkCount;
        if ( polygons->p->checkcount != checkCount && (v4 < 0 || p->primitiveNum == v4) )
        {
          p->checkcount = checkCount;
          numPolys = trm->numPolys;
          if ( numPolys >= 16 )
            return 0;
          p_bounds = &trm->polys[numPolys].bounds;
          p_bounds->b[0].x = p->bounds.b[0].x;
          p_bounds->b[0].y = p->bounds.b[0].y;
          p_bounds->b[0].z = p->bounds.b[0].z;
          p_bounds->b[1].x = p->bounds.b[1].x;
          p_bounds->b[1].y = p->bounds.b[1].y;
          p_bounds->b[1].z = p->bounds.b[1].z;
          v12 = &trm->polys[trm->numPolys];
          v12->normal.x = p->plane.a;
          v12->normal.y = p->plane.b;
          v12->normal.z = p->plane.c;
          trm->polys[trm->numPolys].dist = -p->plane.d;
          trm->polys[trm->numPolys].numEdges = p->numEdges;
          v13 = 0;
          if ( p->numEdges > 0 )
          {
            do
            {
              v14 = p->edges[v13];
              v15 = v13 + 27 * trm->numPolys;
              ++v13;
              trm->polys[0].edges[v15] = v14;
            }
            while ( v13 < p->numEdges );
            v4 = primitiveNum;
            v5 = this;
          }
          ++trm->numPolys;
        }
        polygons = polygons->next;
      }
      while ( polygons );
      v6 = node;
    }
    if ( v6->planeType == -1 )
      return 1;
    if ( !idCollisionModelManagerLocal::TrmFromModel_r(v5, trm, v6->children[1], v4) )
      break;
    node = node->children[0];
  }
  return 0;
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::TrmFromModel(class idCollisionModelLocal const *,class idTraceModel &)
char __thiscall idCollisionModelManagerLocal::TrmFromModel(
        idCollisionModelManagerLocal *this,
        const idCollisionModelLocal *model,
        idTraceModel *trm)
{
  int numVertices; // eax
  idCollisionModelManagerLocal *v4; // ebx
  int v6; // ebp
  int v7; // edx
  float *p_z; // ecx
  cm_vertex_t *vertices; // eax
  float x; // ebx
  int p_p; // eax
  int v12; // edx
  int v13; // ecx
  int *v14; // eax
  double v15; // st6
  double v16; // st7
  float v18; // [esp+14h] [ebp-4h]

  numVertices = model->numVertices;
  v4 = this;
  if ( numVertices > 32 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *, char *, int))(*(_DWORD *)common.type + 124))(
      common.type,
      "idCollisionModelManagerLocal::TrmFromModel: model %s has too many vertices (%d).\n",
      model->name.data,
      numVertices);
LABEL_5:
    idCollisionModelManagerLocal::PrintModelInfo(v4, model);
    return 0;
  }
  if ( model->numEdges > 33 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *, char *, int))(*(_DWORD *)common.type + 124))(
      common.type,
      "idCollisionModelManagerLocal::TrmFromModel: model %s has too many edges (%d).\n",
      model->name.data,
      model->numEdges);
    goto LABEL_5;
  }
  trm->type = TRM_CUSTOM;
  trm->numEdges = 1;
  v6 = 0;
  trm->numVerts = 0;
  trm->numPolys = 0;
  trm->bounds.b[0].z = idMath::INFINITY;
  trm->bounds.b[0].y = idMath::INFINITY;
  trm->bounds.b[0].x = idMath::INFINITY;
  trm->bounds.b[1].z = -1.0e30;
  trm->bounds.b[1].y = -1.0e30;
  trm->bounds.b[1].x = -1.0e30;
  ++this->checkCount;
  if ( idCollisionModelManagerLocal::TrmFromModel_r(this, trm, model->node, -1) )
  {
    if ( model->numVertices > 0 )
    {
      v7 = 0;
      p_z = &trm->verts[0].z;
      do
      {
        vertices = model->vertices;
        x = vertices[v7].p.x;
        p_p = (int)&vertices[v7].p;
        *(p_z - 2) = x;
        *(p_z - 1) = *(float *)(p_p + 4);
        *p_z = *(float *)(p_p + 8);
        if ( *(p_z - 2) < (double)trm->bounds.b[0].x )
          trm->bounds.b[0].x = *(p_z - 2);
        if ( *(p_z - 2) > (double)trm->bounds.b[1].x )
          trm->bounds.b[1].x = *(p_z - 2);
        if ( *(p_z - 1) < (double)trm->bounds.b[0].y )
          trm->bounds.b[0].y = *(p_z - 1);
        if ( *(p_z - 1) > (double)trm->bounds.b[1].y )
          trm->bounds.b[1].y = *(p_z - 1);
        if ( *p_z < (double)trm->bounds.b[0].z )
          trm->bounds.b[0].z = *p_z;
        if ( *p_z > (double)trm->bounds.b[1].z )
          trm->bounds.b[1].z = *p_z;
        ++v6;
        ++v7;
        p_z += 3;
      }
      while ( v6 < model->numVertices );
      v4 = this;
    }
    v12 = 0;
    trm->numVerts = model->numVertices;
    if ( model->numEdges > 0 )
    {
      v13 = 0;
      v14 = &trm->edges[0].v[1];
      do
      {
        *(v14 - 1) = model->edges[v13].vertexNum[0];
        *v14 = model->edges[v13].vertexNum[1];
        ++v12;
        v14 += 5;
        ++v13;
      }
      while ( v12 < model->numEdges );
    }
    trm->numEdges = model->numEdges - 1;
    if ( idTraceModel::IsClosedSurface(trm) )
    {
      v18 = (trm->bounds.b[1].z + trm->bounds.b[0].z) * 0.5;
      v15 = (trm->bounds.b[1].x + trm->bounds.b[0].x) * 0.5;
      v16 = (trm->bounds.b[1].y + trm->bounds.b[0].y) * 0.5;
      trm->offset.z = v18;
      trm->offset.x = v15;
      trm->offset.y = v16;
      idTraceModel::GenerateEdgeNormals(trm);
      idTraceModel::TestConvexity(trm);
      idTraceModel::ClearUnused(trm);
      return 1;
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "idCollisionModelManagerLocal::TrmFromModel: model %s has dangling edges, the model has to be an enclosed hull.\n",
        model->name.data);
      idCollisionModelManagerLocal::PrintModelInfo(v4, model);
      return 0;
    }
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idCollisionModelManagerLocal::TrmFromModel: model %s has too many polygons.\n",
      model->name.data);
    idCollisionModelManagerLocal::PrintModelInfo(v4, model);
    return 0;
  }
}

// FUNC: public: virtual bool __thiscall idCollisionModelManagerLocal::TrmFromModel(char const *,char const *,class idTraceModel &)
char __thiscall idCollisionModelManagerLocal::TrmFromModel(
        idCollisionModelManagerLocal *this,
        const char *mapName,
        const char *modelName,
        idTraceModel *trm)
{
  const idCollisionModelLocal *v5; // eax

  v5 = (const idCollisionModelLocal *)this->LoadModel(this, mapName, modelName);
  if ( v5 )
    return idCollisionModelManagerLocal::TrmFromModel(this, v5, trm);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "idCollisionModelManagerLocal::TrmFromModel: model %s not found.\n",
    modelName);
  return 0;
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::CompoundTrmFromModel(class idCollisionModelLocal const *,class idTraceModel *,int)
int __thiscall idCollisionModelManagerLocal::CompoundTrmFromModel(
        idCollisionModelManagerLocal *this,
        const idCollisionModelLocal *model,
        idTraceModel *trms,
        int maxTrms)
{
  int numVertices; // eax
  int v5; // eax
  void *v6; // esp
  bool v7; // cc
  float *p_y; // edi
  float *v9; // esi
  int v10; // edx
  idCollisionModelManagerLocal *v11; // ecx
  idTraceModel *v12; // eax
  int *v13; // edi
  int v14; // ecx
  int *v15; // edi
  const idCollisionModelLocal *v16; // edi
  int v17; // ecx
  int v18; // edx
  int v19; // eax
  int *v20; // ecx
  int v21; // edi
  int *v22; // ecx
  int v23; // eax
  int *v24; // edx
  int v25; // ecx
  _DWORD *v26; // eax
  int v27; // edx
  int v28; // ecx
  idVec3 *p_p; // eax
  int *v30; // ecx
  int v31; // ecx
  _DWORD *v32; // eax
  int v33; // edx
  float *v34; // ecx
  double v35; // st7
  double v36; // st6
  _DWORD v38[4]; // [esp+4h] [ebp-2Ch] BYREF
  float v39; // [esp+14h] [ebp-1Ch]
  unsigned int v40; // [esp+18h] [ebp-18h]
  int i; // [esp+1Ch] [ebp-14h]
  int *v42; // [esp+20h] [ebp-10h]
  idCollisionModelManagerLocal *v43; // [esp+24h] [ebp-Ch]
  idTraceModel *v44; // [esp+28h] [ebp-8h]
  int numTrms; // [esp+2Ch] [ebp-4h]
  int j; // [esp+3Ch] [ebp+Ch]
  int ja; // [esp+3Ch] [ebp+Ch]
  int jb; // [esp+3Ch] [ebp+Ch]

  numVertices = model->numVertices;
  v43 = this;
  if ( model->numEdges > numVertices )
    numVertices = model->numEdges;
  v40 = 4 * numVertices;
  v5 = 4 * numVertices + 18;
  LOBYTE(v5) = v5 & 0xFC;
  v6 = alloca(v5);
  v7 = model->numPrimitives <= 0;
  numTrms = 0;
  i = 0;
  if ( v7 )
    return numTrms;
  p_y = &trms->bounds.b[0].y;
  v44 = (idTraceModel *)&trms->bounds.b[0].y;
  while ( 1 )
  {
    if ( numTrms >= maxTrms )
      return numTrms;
    *(p_y - 700) = 0.0;
    *(p_y - 437) = 0.0;
    *((_DWORD *)p_y - 701) = 9;
    *((_DWORD *)p_y - 603) = 1;
    p_y[1] = idMath::INFINITY;
    v9 = p_y - 701;
    *p_y = idMath::INFINITY;
    v10 = i;
    *(p_y - 1) = idMath::INFINITY;
    v11 = v43;
    p_y[4] = -1.0e30;
    p_y[3] = -1.0e30;
    p_y[2] = -1.0e30;
    ++v11->checkCount;
    if ( !idCollisionModelManagerLocal::TrmFromModel_r(v11, (idTraceModel *)(p_y - 701), model->node, v10) )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idCollisionModelManagerLocal::CompoundTrmFromModel: model %s has a primitive with too many polygons.\n",
        model->name.data);
      idCollisionModelManagerLocal::PrintModelInfo(v43, model);
      return numTrms;
    }
    if ( *((_DWORD *)p_y - 437) )
      break;
LABEL_60:
    v7 = ++i < model->numPrimitives;
    if ( !v7 )
      return numTrms;
  }
  memset(v38, 0, v40);
  v12 = v44;
  j = 0;
  if ( SLODWORD(v44[-1].polys[0].bounds.b[0].y) > 0 )
  {
    v13 = &v44[-1].polys[0].edges[5];
    v42 = &v44[-1].polys[0].edges[5];
    do
    {
      v14 = 0;
      if ( *v13 > 0 )
      {
        v15 = v13 + 1;
        do
        {
          v38[abs32(*v15)] = 1;
          ++v14;
          ++v15;
        }
        while ( v14 < *v42 );
        v13 = v42;
        v12 = v44;
      }
      v13 += 27;
      v7 = ++j < SLODWORD(v12[-1].polys[0].bounds.b[0].y);
      v42 = v13;
    }
    while ( v7 );
  }
  v16 = model;
  v17 = 0;
  if ( model->numEdges > 0 )
  {
    v18 = 0;
    do
    {
      if ( v38[v17] )
      {
        v19 = *((_DWORD *)v9 + 98);
        if ( v19 >= 33 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *, char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "idCollisionModelManagerLocal::CompoundTrmFromModel: model %s has a primitive with too many edges.\n",
            v16->name.data);
          goto LABEL_65;
        }
        v9[5 * v19 + 99] = *(float *)v16->edges[v18].vertexNum;
        v9[5 * *((_DWORD *)v9 + 98) + 100] = *(float *)&model->edges[v18].vertexNum[1];
        v16 = model;
        v38[v17] = (*((_DWORD *)v9 + 98))++;
      }
      ++v17;
      ++v18;
    }
    while ( v17 < v16->numEdges );
  }
  --*((_DWORD *)v9 + 98);
  ja = 0;
  if ( *((int *)v9 + 264) > 0 )
  {
    v20 = (int *)(v9 + 275);
    v42 = (int *)(v9 + 275);
    do
    {
      v21 = 0;
      if ( *v20 > 0 )
      {
        v22 = v20 + 1;
        do
        {
          if ( *v22 >= 0 )
            v23 = v38[abs32(*v22)];
          else
            v23 = -v38[abs32(*v22)];
          v24 = v42;
          *v22 = v23;
          ++v21;
          ++v22;
        }
        while ( v21 < *v24 );
        v20 = v24;
      }
      v20 += 27;
      v7 = ++ja < *((_DWORD *)v9 + 264);
      v42 = v20;
    }
    while ( v7 );
  }
  memset(v38, 0, v40);
  v25 = 1;
  if ( *((int *)v9 + 98) >= 1 )
  {
    v26 = v9 + 105;
    do
    {
      v38[*(v26 - 1)] = 1;
      ++v25;
      v38[*v26] = 1;
      v26 += 5;
    }
    while ( v25 <= *((_DWORD *)v9 + 98) );
  }
  v16 = model;
  v27 = 0;
  if ( model->numVertices <= 0 )
  {
LABEL_40:
    v31 = 1;
    if ( *((int *)v9 + 98) >= 1 )
    {
      v32 = v9 + 105;
      do
      {
        *(v32 - 1) = v38[*(v32 - 1)];
        *v32 = v38[*v32];
        ++v31;
        v32 += 5;
      }
      while ( v31 <= *((_DWORD *)v9 + 98) );
    }
    if ( !idTraceModel::IsClosedSurface((idTraceModel *)v9) )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idCollisionModelManagerLocal::CompoundTrmFromModel: model %s has a primitive with dangling edges, the primitives"
        " have to be an enclosed hulls.\n",
        v16->name.data);
      idCollisionModelManagerLocal::PrintModelInfo(v43, v16);
      return 0;
    }
    v33 = 0;
    if ( *((int *)v9 + 1) > 0 )
    {
      v34 = v9 + 4;
      do
      {
        if ( *(v34 - 2) < (double)v9[700] )
          v9[700] = *(v34 - 2);
        if ( *(v34 - 2) > (double)v9[703] )
          v9[703] = *(v34 - 2);
        if ( *(v34 - 1) < (double)v9[701] )
          v9[701] = *(v34 - 1);
        if ( *(v34 - 1) > (double)v9[704] )
          v9[704] = *(v34 - 1);
        if ( *v34 < (double)v9[702] )
          v9[702] = *v34;
        if ( *v34 > (double)v9[705] )
          v9[705] = *v34;
        ++v33;
        v34 += 3;
      }
      while ( v33 < *((_DWORD *)v9 + 1) );
    }
    v35 = (v9[703] + v9[700]) * 0.5;
    v36 = (v9[704] + v9[701]) * 0.5;
    v39 = (v9[705] + v9[702]) * 0.5;
    v9[699] = v39;
    v9[697] = v35;
    v9[698] = v36;
    idTraceModel::GenerateEdgeNormals((idTraceModel *)v9);
    idTraceModel::TestConvexity((idTraceModel *)v9);
    idTraceModel::ClearUnused((idTraceModel *)v9);
    ++numTrms;
    p_y = (float *)++v44;
    goto LABEL_60;
  }
  jb = 0;
  while ( !v38[v27] )
  {
LABEL_39:
    ++jb;
    if ( ++v27 >= v16->numVertices )
      goto LABEL_40;
  }
  v28 = *((_DWORD *)v9 + 1);
  if ( v28 < 32 )
  {
    p_p = &v16->vertices[jb].p;
    v30 = (int *)&v9[3 * v28 + 2];
    *v30 = LODWORD(p_p->x);
    v30[1] = LODWORD(p_p->y);
    v16 = model;
    v30[2] = LODWORD(p_p->z);
    v38[v27] = (*((_DWORD *)v9 + 1))++;
    goto LABEL_39;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *, char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "idCollisionModelManagerLocal::CompoundTrmFromModel: model %s has a primitive with too many vertices.\n",
    v16->name.data);
LABEL_65:
  idCollisionModelManagerLocal::PrintModelInfo(v43, v16);
  return numTrms;
}

// FUNC: public: virtual int __thiscall idCollisionModelManagerLocal::CompoundTrmFromModel(char const *,char const *,class idTraceModel *,int)
int __thiscall idCollisionModelManagerLocal::CompoundTrmFromModel(
        idCollisionModelManagerLocal *this,
        const char *mapName,
        const char *modelName,
        idTraceModel *trms,
        int maxTrms)
{
  const idCollisionModelLocal *v6; // eax

  v6 = (const idCollisionModelLocal *)this->LoadModel(this, mapName, modelName);
  if ( v6 )
    return idCollisionModelManagerLocal::CompoundTrmFromModel(this, v6, trms, maxTrms);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "idCollisionModelManagerLocal::CompoundTrmFromModel: model %s not found.\n",
    modelName);
  return 0;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::Clear(void)
void __thiscall idCollisionModelManagerLocal::Clear(idCollisionModelManagerLocal *this)
{
  idStr *p_mapName; // edi
  int i; // edi
  idCollisionModelLocal *v4; // ecx

  p_mapName = &this->mapName;
  idStr::FreeData(&this->mapName);
  p_mapName->len = 0;
  p_mapName->alloced = 20;
  p_mapName->data = p_mapName->baseBuffer;
  p_mapName->baseBuffer[0] = 0;
  this->mapFileTime = 0;
  this->loaded = 0;
  this->checkCount = 0;
  for ( i = 0; i < this->models.num; ++i )
  {
    v4 = this->models.list[i];
    if ( v4 )
      ((void (__thiscall *)(idCollisionModelLocal *, int))v4->~idCollisionModelLocal)(v4, 1);
    this->models.list[i] = 0;
  }
  if ( this->models.list )
    Memory::Free(this->models.list);
  this->models.list = 0;
  this->models.num = 0;
  this->models.size = 0;
  this->getContacts = 0;
  this->contacts = 0;
  this->maxContacts = 0;
  this->numContacts = 0;
  this->numProcNodes = 0;
  this->procNodes = 0;
  this->cm_windingList = 0;
  this->cm_outList = 0;
  this->cm_tmpList = 0;
  this->cm_vertexHash = 0;
  this->cm_edgeHash = 0;
  this->cm_modelBounds.b[0].z = idMath::INFINITY;
  this->cm_modelBounds.b[0].y = idMath::INFINITY;
  this->cm_modelBounds.b[0].x = idMath::INFINITY;
  this->cm_modelBounds.b[1].z = -1.0e30;
  this->cm_modelBounds.b[1].y = -1.0e30;
  this->cm_modelBounds.b[1].x = -1.0e30;
  this->cm_vertexShift = 0;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ReAllocPolygonsAndBrushes_r(class idCollisionModelLocal *,struct cm_node_t *)
void __thiscall idCollisionModelManagerLocal::ReAllocPolygonsAndBrushes_r(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_brushRef_t *node)
{
  cm_node_t *v4; // esi
  cm_polygonRef_t *b; // edi
  cm_polygon_t *p; // ebx
  cm_polygon_t *polygons; // edx
  int numEdges; // ecx
  cm_polygon_t *v9; // esi
  int numPolygons; // eax
  unsigned int *brushes; // edx
  unsigned int v12; // ebx
  cm_brush_t *v13; // ecx
  cm_brush_t *v14; // eax
  idPlane *planes; // edi
  idCollisionModelLocal *modela; // [esp+8h] [ebp+4h]

  for ( ; node; node = (cm_brushRef_t *)v4->children[1] )
  {
    v4 = (cm_node_t *)node;
    b = (cm_polygonRef_t *)node[1].b;
    if ( b )
    {
      do
      {
        p = b->p;
        polygons = model->polygons;
        if ( b->p < polygons || p > &polygons[model->maxPolygons] )
        {
          numEdges = p->numEdges;
          if ( polygons || model->polygonEdges )
          {
            numPolygons = model->numPolygons;
            v9 = &polygons[numPolygons];
            model->numPolygons = numPolygons + 1;
            v9->numEdges = numEdges;
            v9->edges = &model->polygonEdges[model->numPolygonEdges];
            model->numPolygonEdges += numEdges;
          }
          else
          {
            model->numPolygonEdges += numEdges;
            ++model->numPolygons;
            v9 = (cm_polygon_t *)Mem_Alloc(4 * numEdges + 88, 8u);
            v9->edges = (int *)&v9[1];
          }
          idCollisionModelManagerLocal::CopyPolygon(this, v9, p);
          idCollisionModelManagerLocal::RemapPolygonReferences_r(this, model->node, p, v9);
          Mem_Free(p);
        }
        b = b->next;
      }
      while ( b );
      v4 = (cm_node_t *)node;
    }
    brushes = (unsigned int *)v4->brushes;
    modela = (idCollisionModelLocal *)brushes;
    if ( brushes )
    {
      while ( 1 )
      {
        v12 = *brushes;
        v13 = model->brushes;
        if ( *brushes < (unsigned int)v13 || v12 > (unsigned int)&v13[model->maxBrushes] )
        {
          v14 = idCollisionModelManagerLocal::AllocBrush(this, model, *(_DWORD *)(v12 + 40));
          v14->bounds.b[0].x = *(float *)v12;
          v14->bounds.b[0].y = *(float *)(v12 + 4);
          v14->bounds.b[0].z = *(float *)(v12 + 8);
          v14->bounds.b[1] = *(idVec3 *)(v12 + 12);
          planes = v14->planes;
          v14->checkcount = *(_DWORD *)(v12 + 24);
          v14->contents = *(_DWORD *)(v12 + 28);
          v14->material = *(const idMaterial **)(v12 + 32);
          v14->primitiveNum = *(_DWORD *)(v12 + 36);
          v14->numPlanes = *(_DWORD *)(v12 + 40);
          qmemcpy(planes, *(const void **)(v12 + 44), 16 * *(_DWORD *)(v12 + 40));
          idCollisionModelManagerLocal::RemapBrushReferences_r(this, model->node, (cm_brush_t *)v12, v14);
          Mem_Free((void *)v12);
          brushes = (unsigned int *)modela;
        }
        modela = (idCollisionModelLocal *)brushes[1];
        if ( !modela )
          break;
        brushes = (unsigned int *)brushes[1];
      }
      v4 = (cm_node_t *)node;
    }
    if ( v4->planeType == -1 )
      break;
    idCollisionModelManagerLocal::ReAllocPolygonsAndBrushes_r(this, model, v4->children[0]);
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::FreeModelMemory(class idCollisionModelLocal *)
void __thiscall idCollisionModelManagerLocal::FreeModelMemory(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model)
{
  cm_polygonRefBlock_t *polygonRefBlocks; // eax
  cm_polygonRefBlock_t *next; // edi
  cm_brushRefBlock_t *brushRefBlocks; // eax
  cm_brushRefBlock_t *v6; // edi
  cm_nodeBlock_t *nodeBlocks; // eax
  cm_nodeBlock_t *v8; // edi

  if ( model->node )
    idCollisionModelManagerLocal::FreeTree_r(this, model, model->node, model->node);
  polygonRefBlocks = model->polygonRefBlocks;
  if ( polygonRefBlocks )
  {
    do
    {
      next = polygonRefBlocks->next;
      Mem_Free(polygonRefBlocks);
      polygonRefBlocks = next;
    }
    while ( next );
  }
  brushRefBlocks = model->brushRefBlocks;
  if ( brushRefBlocks )
  {
    do
    {
      v6 = brushRefBlocks->next;
      Mem_Free(brushRefBlocks);
      brushRefBlocks = v6;
    }
    while ( v6 );
  }
  nodeBlocks = model->nodeBlocks;
  if ( nodeBlocks )
  {
    do
    {
      v8 = nodeBlocks->next;
      Mem_Free(nodeBlocks);
      nodeBlocks = v8;
    }
    while ( v8 );
  }
  Mem_Free16(model->polygonEdges);
  Mem_Free16(model->polygons);
  Mem_Free16(model->brushPlanes);
  Mem_Free16(model->brushes);
  Mem_Free(model->edges);
  Mem_Free(model->vertices);
  idCollisionModelManagerLocal::ClearModel(this, model);
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::PurgeModels(void)
void __thiscall idCollisionModelManagerLocal::PurgeModels(idCollisionModelManagerLocal *this)
{
  int i; // edi

  for ( i = 0; i < this->models.num; ++i )
  {
    if ( this->models.list[i]->refCount <= 0 )
      idCollisionModelManagerLocal::FreeModelMemory(this, this->models.list[i]);
  }
}

// FUNC: private: class idCollisionModelLocal * __thiscall idCollisionModelManagerLocal::AllocModel(void)
idCollisionModelLocal *__thiscall idCollisionModelManagerLocal::AllocModel(idCollisionModelManagerLocal *this)
{
  idCollisionModelLocal *v2; // eax
  idCollisionModelLocal *v3; // esi

  v2 = (idCollisionModelLocal *)Memory::Allocate(0xC8u);
  if ( v2 )
  {
    v2->__vftable = (idCollisionModelLocal_vtbl *)&idCollisionModelLocal::`vftable';
    v2->name.data = v2->name.baseBuffer;
    v2->name.len = 0;
    v2->name.alloced = 20;
    v3 = v2;
    v2->name.baseBuffer[0] = 0;
    idCollisionModelManagerLocal::ClearModel(this, v2);
    return v3;
  }
  else
  {
    idCollisionModelManagerLocal::ClearModel(this, 0);
    return 0;
  }
}

// FUNC: public: virtual class idCollisionModel * __thiscall idCollisionModelManagerLocal::ModelFromTrm(char const *,char const *,class idTraceModel const &,class idMaterial const *)
idCollisionModelLocal *__thiscall idCollisionModelManagerLocal::ModelFromTrm(
        idCollisionModelManagerLocal *this,
        const char *mapName,
        const char *modelName,
        const idTraceModel *trm,
        cm_brushRef_t *material)
{
  idCollisionModelLocal *v6; // esi
  char *FullModelName; // eax
  cm_node_t *v8; // eax
  int v10; // ebx
  char *v11; // eax
  int v12; // edx
  idVec3 *verts; // ecx
  _DWORD *v14; // eax
  char *v15; // eax
  traceModelEdge_t *v16; // edx
  _DWORD *v17; // eax
  float *p_z; // ecx
  int v19; // eax
  int *p_numEdges; // ecx
  int numPolys; // ecx
  int v22; // eax
  traceModelPoly_t *polys; // edi
  cm_polygonRef_t *v24; // eax
  int numEdges; // ecx
  cm_polygon_t *polygons; // eax
  cm_polygon_t *v27; // eax
  int numPolygons; // ecx
  cm_polygonRef_t *v29; // ecx
  int v30; // ecx
  double v31; // st7
  cm_brushRef_t *v32; // edi
  cm_brush_t *v33; // eax
  const char *v34; // edi
  float *v35; // edx
  char *v36; // ecx
  bool v37; // cc
  int v39; // [esp-8h] [ebp-1Ch]
  int mapNamea; // [esp+18h] [ebp+4h]
  const char *mapNameb; // [esp+18h] [ebp+4h]
  const char *mapNamec; // [esp+18h] [ebp+4h]
  const char *modelNamea; // [esp+1Ch] [ebp+8h]
  const char *modelNameb; // [esp+1Ch] [ebp+8h]
  const char *modelNamec; // [esp+1Ch] [ebp+8h]
  cm_polygonRef_t *i; // [esp+20h] [ebp+Ch]
  int ia; // [esp+20h] [ebp+Ch]

  v6 = idCollisionModelManagerLocal::AllocModel(this);
  FullModelName = (char *)idCollisionModelManagerLocal::GetFullModelName(this, mapName, modelName);
  idStr::operator=(&v6->name, FullModelName);
  v6->isTraceModel = 1;
  v8 = idCollisionModelManagerLocal::AllocNode(this, v6, 1);
  v6->node = v8;
  v8->planeType = -1;
  v10 = 0;
  v6->node->brushes = 0;
  v6->node->polygons = 0;
  if ( trm->type && trm->numPolys )
  {
    if ( !material )
      material = (cm_brushRef_t *)declManager->FindMaterial(declManager, "_tracemodel", 0);
    v6->numVertices = trm->numVerts;
    v6->maxVertices = 32;
    v11 = (char *)Mem_ClearedAlloc(768, 8u);
    v6->vertices = (cm_vertex_t *)v11;
    v12 = 0;
    verts = trm->verts;
    if ( trm->numVerts > 0 )
    {
      v14 = v11 + 12;
      do
      {
        *(v14 - 2) = LODWORD(verts->x);
        *(v14 - 1) = LODWORD(verts->y);
        *v14 = LODWORD(verts->z);
        v14[2] = 0;
        ++v12;
        v14 += 6;
        ++verts;
      }
      while ( v12 < trm->numVerts );
    }
    v6->numEdges = trm->numEdges;
    v6->maxEdges = 33;
    v15 = (char *)Mem_ClearedAlloc(1188, 8u);
    v6->edges = (cm_edge_t *)v15;
    v16 = &trm->edges[1];
    modelNamea = 0;
    if ( trm->numEdges > 0 )
    {
      v17 = v15 + 68;
      p_z = &trm->edges[1].normal.z;
      do
      {
        *(v17 - 4) = v16->v[0];
        *(v17 - 3) = *((_DWORD *)p_z - 3);
        *(v17 - 2) = *((_DWORD *)p_z - 2);
        *(v17 - 1) = *((_DWORD *)p_z - 1);
        *v17 = *(_DWORD *)p_z;
        *((_WORD *)v17 - 14) = 0;
        *(v17 - 5) = 0;
        v17 += 9;
        ++v16;
        p_z += 5;
        ++modelNamea;
      }
      while ( (int)modelNamea < trm->numEdges );
    }
    v6->maxPolygonEdges = 0;
    v19 = 0;
    if ( trm->numPolys > 0 )
    {
      p_numEdges = &trm->polys[0].numEdges;
      do
      {
        v6->maxPolygonEdges += *p_numEdges;
        ++v19;
        p_numEdges += 27;
      }
      while ( v19 < trm->numPolys );
    }
    v39 = 4 * v6->maxPolygonEdges;
    v6->numPolygonEdges = 0;
    v6->polygonEdges = (int *)Mem_Alloc16(v39, 8u);
    numPolys = trm->numPolys;
    v6->maxPolygons = numPolys;
    v6->numPolygons = 0;
    v6->polygons = (cm_polygon_t *)Mem_Alloc16(88 * numPolys, 8u);
    v22 = trm->numPolys;
    polys = trm->polys;
    for ( modelNameb = 0; (int)modelNameb < v22; ++modelNameb )
    {
      v24 = idCollisionModelManagerLocal::AllocPolygonReference(this, v6, v22);
      numEdges = polys->numEdges;
      i = v24;
      polygons = v6->polygons;
      mapNamea = numEdges;
      if ( polygons || v6->polygonEdges )
      {
        numPolygons = v6->numPolygons;
        v6->numPolygons = numPolygons + 1;
        v27 = &polygons[numPolygons];
        v27->numEdges = mapNamea;
        v27->edges = &v6->polygonEdges[v6->numPolygonEdges];
        v6->numPolygonEdges += mapNamea;
      }
      else
      {
        ++v6->numPolygons;
        v6->numPolygonEdges += numEdges;
        v27 = (cm_polygon_t *)Mem_Alloc(4 * numEdges + 88, 8u);
        v27->edges = (int *)&v27[1];
      }
      v29 = i;
      i->p = v27;
      v27->numEdges = polys->numEdges;
      if ( polys->numEdges > 0 )
      {
        mapNameb = (const char *)polys->edges;
        do
        {
          v30 = *(_DWORD *)mapNameb;
          mapNameb += 4;
          v27->edges[v10++] = v30;
        }
        while ( v10 < polys->numEdges );
        v29 = i;
        v10 = 0;
      }
      v27->plane.a = polys->normal.x;
      v27->plane.b = polys->normal.y;
      v27->plane.c = polys->normal.z;
      v31 = -polys->dist;
      ++polys;
      v27->plane.d = v31;
      v27->bounds.b[0].x = polys[-1].bounds.b[0].x;
      v27->bounds.b[0].y = polys[-1].bounds.b[0].y;
      v27->bounds.b[0].z = polys[-1].bounds.b[0].z;
      v27->bounds.b[1].x = polys[-1].bounds.b[1].x;
      v27->bounds.b[1].y = polys[-1].bounds.b[1].y;
      v27->bounds.b[1].z = polys[-1].bounds.b[1].z;
      v27->material = (const idMaterial *)material;
      v27->contents = -1;
      v27->primitiveNum = 0;
      v27->checkcount = 0;
      v27->texBounds[0].y = 0.0;
      v27->texBounds[0].x = 0.0;
      v27->texBounds[1].y = 0.0;
      v27->texBounds[1].x = 0.0;
      v27->texBounds[2].y = 0.0;
      v27->texBounds[2].x = 0.0;
      v29->next = v6->node->polygons;
      v6->node->polygons = v29;
      v22 = trm->numPolys;
    }
    if ( trm->isConvex )
    {
      v32 = idCollisionModelManagerLocal::AllocBrushReference(this, v6, 1);
      ia = (int)v32;
      v33 = idCollisionModelManagerLocal::AllocBrush(this, v6, trm->numPolys);
      v32->b = v33;
      v33->numPlanes = trm->numPolys;
      modelNamec = 0;
      if ( trm->numPolys > 0 )
      {
        v34 = 0;
        mapNamec = 0;
        v35 = &trm->polys[0].normal.z;
        do
        {
          v36 = (char *)&v34[(unsigned int)v33->planes];
          *(float *)v36 = *(v35 - 2);
          *((float *)v36 + 1) = *(v35 - 1);
          *((float *)v36 + 2) = *v35;
          *(float *)&mapNamec[(unsigned int)v33->planes + 12] = -v35[1];
          v34 = mapNamec + 16;
          v35 += 27;
          v37 = (int)++modelNamec < trm->numPolys;
          mapNamec += 16;
        }
        while ( v37 );
        v32 = (cm_brushRef_t *)ia;
      }
      v33->bounds.b[0].x = trm->bounds.b[0].x;
      v33->bounds.b[0].y = trm->bounds.b[0].y;
      v33->bounds.b[0].z = trm->bounds.b[0].z;
      v33->bounds.b[1].x = trm->bounds.b[1].x;
      v33->bounds.b[1].y = trm->bounds.b[1].y;
      v33->bounds.b[1].z = trm->bounds.b[1].z;
      v33->material = (const idMaterial *)material;
      v33->contents = -1;
      v33->primitiveNum = 0;
      v33->checkcount = 0;
      v32->next = v6->node->brushes;
      v6->node->brushes = v32;
    }
    v6->bounds.b[0].x = trm->bounds.b[0].x;
    v6->bounds.b[0].y = trm->bounds.b[0].y;
    v6->bounds.b[0].z = trm->bounds.b[0].z;
    v6->bounds.b[1].x = trm->bounds.b[1].x;
    v6->bounds.b[1].y = trm->bounds.b[1].y;
    v6->bounds.b[1].z = trm->bounds.b[1].z;
    v6->isConvex = trm->isConvex;
  }
  return v6;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ChopWindingListWithBrush(struct cm_windingList_t *,struct cm_brush_t *)
void __thiscall idCollisionModelManagerLocal::ChopWindingListWithBrush(
        idCollisionModelManagerLocal *this,
        cm_windingList_t *list,
        cm_brush_t *b)
{
  int v4; // edi
  cm_brush_t *v5; // ebp
  int numPlanes; // eax
  int v7; // ebx
  idPlane *planes; // eax
  double d; // st7
  float *p_a; // eax
  double v11; // st6
  double v12; // st5
  cm_windingList_t *v13; // ecx
  double v14; // st7
  double v15; // st7
  int v16; // eax
  bool v17; // cc
  int v18; // edi
  int v19; // eax
  int v20; // ebx
  int v21; // eax
  float *v22; // eax
  cm_windingList_t *cm_tmpList; // edx
  cm_windingList_t *cm_outList; // edx
  cm_windingList_t *v25; // eax
  int numWindings; // ebx
  int v27; // edi
  int v28; // ebp
  cm_windingList_t *v29; // ecx
  cm_windingList_t *v30; // eax
  int v31; // ebx
  int v32; // edi
  _DWORD *v33; // ebp
  bool chopped; // [esp+Fh] [ebp-B5Dh]
  int bestNumWindings; // [esp+10h] [ebp-B5Ch]
  int w; // [esp+14h] [ebp-B58h]
  int startPlane; // [esp+18h] [ebp-B54h]
  float v38; // [esp+1Ch] [ebp-B50h]
  idPlane v39; // [esp+1Ch] [ebp-B50h]
  float v40; // [esp+20h] [ebp-B4Ch]
  float v41; // [esp+24h] [ebp-B48h]
  float v42; // [esp+28h] [ebp-B44h]
  idPlane plane; // [esp+2Ch] [ebp-B40h] BYREF
  int k; // [esp+3Ch] [ebp-B30h]
  int sidedness[64]; // [esp+40h] [ebp-B2Ch]
  idFixedWinding front; // [esp+140h] [ebp-A2Ch] BYREF
  idFixedWinding back; // [esp+650h] [ebp-51Ch] BYREF
  int v48; // [esp+B68h] [ebp-4h]

  back.p = back.data;
  v4 = 0;
  back.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  back.numPoints = 0;
  back.allocedSize = 64;
  v48 = 0;
  front.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  front.numPoints = 0;
  front.p = front.data;
  front.allocedSize = 64;
  v5 = b;
  numPlanes = b->numPlanes;
  LOBYTE(v48) = 1;
  if ( numPlanes > 64 )
  {
    LOBYTE(v48) = 0;
    front.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(0);
    front.p = 0;
    v48 = -1;
    back.p = 0;
    back.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(0);
    return;
  }
  if ( numPlanes <= 0 )
  {
    v13 = list;
  }
  else
  {
    v7 = 0;
    do
    {
      planes = b->planes;
      d = planes[v7].d;
      p_a = &planes[v7].a;
      v11 = -p_a[2];
      v12 = -p_a[1];
      v38 = -*p_a;
      plane.a = v38;
      v40 = v12;
      plane.b = v40;
      v13 = list;
      v41 = v11;
      v42 = -d;
      plane.c = v41;
      v14 = v38 * list->origin.x;
      plane.d = v42;
      v15 = v14 + v40 * list->origin.y + v41 * list->origin.z + v42;
      if ( v15 <= list->radius )
      {
        if ( v15 >= -list->radius )
        {
          v16 = idBounds::PlaneSide(&list->bounds, &plane, 0.1);
          sidedness[v4] = v16;
          if ( v16 )
            sidedness[v4] = 2 * (v16 != 1) + 1;
          else
            sidedness[v4] = 0;
          v13 = list;
        }
        else
        {
          sidedness[v4] = 1;
        }
      }
      else
      {
        sidedness[v4] = 0;
      }
      ++v4;
      ++v7;
    }
    while ( v4 < b->numPlanes );
  }
  this->cm_outList->numWindings = 0;
  v17 = v13->numWindings <= 0;
  k = 0;
  if ( v17 )
    goto LABEL_50;
  w = (int)v13->w;
  while ( 2 )
  {
    startPlane = 0;
    bestNumWindings = v5->numPlanes + 1;
    chopped = 0;
LABEL_19:
    idFixedWinding::operator=(&front, w);
    v18 = startPlane;
    this->cm_tmpList->numWindings = 0;
    v19 = v5->numPlanes;
    v20 = 0;
    if ( v19 <= 0 )
      goto LABEL_37;
    while ( 1 )
    {
      if ( v18 >= v19 )
        v18 = 0;
      v21 = sidedness[v18];
      if ( v21 == 3 )
      {
        v22 = &v5->planes[v18].a;
        v39.a = -*v22;
        v39.b = -v22[1];
        v39.c = -v22[2];
        v39.d = -v22[3];
        plane = v39;
        v21 = idFixedWinding::Split(&front, &back, &plane, 0.1);
      }
      if ( v21 != 2 )
        break;
      if ( list->primitiveNum >= 0
        && v5->planes[v18].c * list->normal.z + v5->planes[v18].b * list->normal.y + v5->planes[v18].a * list->normal.x > 0.0 )
      {
        goto LABEL_55;
      }
LABEL_32:
      if ( this->cm_tmpList->numWindings < bestNumWindings )
      {
        v19 = v5->numPlanes;
        ++v20;
        ++v18;
        if ( v20 < v19 )
          continue;
      }
      goto LABEL_37;
    }
    if ( v21 != 1 )
    {
      if ( v21 == 3 )
      {
        cm_tmpList = this->cm_tmpList;
        if ( cm_tmpList->numWindings >= 128 )
          goto LABEL_57;
        idFixedWinding::operator=(&this->cm_tmpList->w[cm_tmpList->numWindings].__vftable, (int)&back);
        ++this->cm_tmpList->numWindings;
        chopped = 1;
      }
      goto LABEL_32;
    }
    cm_outList = this->cm_outList;
    if ( cm_outList->numWindings >= 128 )
      goto LABEL_57;
    idFixedWinding::operator=(&this->cm_outList->w[cm_outList->numWindings].__vftable, w);
    ++this->cm_outList->numWindings;
    chopped = 0;
LABEL_37:
    v25 = this->cm_tmpList;
    if ( v25->numWindings >= bestNumWindings )
      goto LABEL_44;
    numWindings = v25->numWindings;
    v27 = 0;
    bestNumWindings = v25->numWindings;
    if ( v25->numWindings <= 0 )
    {
LABEL_43:
      if ( numWindings == 1 )
        goto LABEL_46;
LABEL_44:
      ++startPlane;
      if ( !chopped )
        goto LABEL_48;
      if ( startPlane >= v5->numPlanes )
      {
LABEL_46:
        if ( chopped )
          this->cm_outList->numWindings += bestNumWindings;
LABEL_48:
        w += 1296;
        v17 = ++k < list->numWindings;
        if ( !v17 )
        {
          v13 = list;
LABEL_50:
          v30 = this->cm_outList;
          v31 = 0;
          if ( v30->numWindings > 0 )
          {
            v32 = 0;
            v33 = &v13->w[0].__vftable;
            do
            {
              idFixedWinding::operator=(v33, (int)&v30->w[v32]);
              v30 = this->cm_outList;
              ++v31;
              ++v32;
              v33 += 324;
            }
            while ( v31 < v30->numWindings );
            v13 = list;
          }
          v13->numWindings = this->cm_outList->numWindings;
LABEL_55:
          front.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
          front.p = 0;
          LOBYTE(v48) = 0;
          Memory::Free(0);
          back.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
          back.p = 0;
          front.p = 0;
          v48 = -1;
          Memory::Free(0);
          return;
        }
        continue;
      }
      goto LABEL_19;
    }
    break;
  }
  v28 = 0;
  while ( 1 )
  {
    v29 = this->cm_outList;
    if ( v27 + v29->numWindings >= 128 )
      break;
    idFixedWinding::operator=(&v29->w[v27 + v29->numWindings].__vftable, (int)&v25->w[v28]);
    v25 = this->cm_tmpList;
    ++v27;
    ++v28;
    if ( v27 >= v25->numWindings )
    {
      v5 = b;
      goto LABEL_43;
    }
  }
LABEL_57:
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
    common.type,
    "idCollisionModelManagerLocal::ChopWindingWithBrush: primitive %d more than %d windings",
    list->primitiveNum,
    128);
  LOBYTE(v48) = 0;
  front.p = 0;
  front.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
  front.p = 0;
  v48 = -1;
  back.p = 0;
  back.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::R_ChopWindingListWithTreeBrushes(struct cm_windingList_t *,struct cm_node_t *)
void __thiscall idCollisionModelManagerLocal::R_ChopWindingListWithTreeBrushes(
        idCollisionModelManagerLocal *this,
        cm_windingList_t *list,
        cm_node_t *node)
{
  cm_brushRef_t *i; // ebx
  cm_brush_t *b; // esi
  int checkCount; // eax
  int primitiveNum; // ecx
  int v8; // ecx
  idVec3 *v9; // edx
  int planeType; // ecx

  while ( 1 )
  {
    for ( i = node->brushes; i; i = i->next )
    {
      b = i->b;
      checkCount = this->checkCount;
      if ( i->b->checkcount != checkCount )
      {
        primitiveNum = b->primitiveNum;
        b->checkcount = checkCount;
        if ( primitiveNum != list->primitiveNum && b->contents == list->contents )
        {
          v8 = 0;
          v9 = &list->bounds.b[1];
          while ( v9[-1].x <= (double)*(&b->bounds.b[1].x + v8) && v9->x >= (double)*(&b->bounds.b[0].x + v8) )
          {
            ++v8;
            v9 = (idVec3 *)((char *)v9 + 4);
            if ( v8 >= 3 )
            {
              idCollisionModelManagerLocal::ChopWindingListWithBrush(this, list, b);
              if ( !list->numWindings )
                return;
              break;
            }
          }
        }
      }
    }
    planeType = node->planeType;
    if ( node->planeType == -1 )
      break;
    if ( *(&list->bounds.b[0].x + planeType) <= (double)node->planeDist )
    {
      if ( *(&list->bounds.b[1].x + planeType) >= (double)node->planeDist )
      {
        idCollisionModelManagerLocal::R_ChopWindingListWithTreeBrushes(this, list, node->children[1]);
        if ( !list->numWindings )
          return;
        node = node->children[0];
      }
      else
      {
        node = node->children[1];
      }
    }
    else
    {
      node = node->children[0];
    }
  }
}

// FUNC: private: struct cm_polygon_t * __thiscall idCollisionModelManagerLocal::TryMergePolygons(class idCollisionModelLocal *,struct cm_polygon_t *,struct cm_polygon_t *)
cm_polygon_t *__thiscall idCollisionModelManagerLocal::TryMergePolygons(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_polygon_t *p1,
        cm_polygon_t *p2)
{
  bool v4; // zf
  int v6; // edx
  idPlane *p_plane; // ecx
  int numEdges; // esi
  int *v9; // ecx
  int v10; // ebx
  int v11; // eax
  int *edges; // ecx
  unsigned int v13; // edi
  int v14; // esi
  unsigned int v15; // ebx
  cm_edge_t *v16; // edi
  cm_vertex_t *vertices; // ecx
  cm_edge_t *v18; // edx
  int v19; // eax
  float *p_x; // edx
  float *v21; // eax
  double v22; // st7
  double v23; // st6
  double v24; // st5
  long double v25; // st7
  double v26; // st6
  double v27; // st5
  long double v28; // st7
  int v29; // esi
  cm_edge_t *v30; // edx
  int v31; // eax
  float *v32; // edx
  cm_edge_t *v33; // edx
  int v34; // edi
  double v35; // st7
  double v36; // st6
  double v37; // st5
  double v38; // st7
  double v39; // st6
  double v40; // st5
  __int64 v41; // rax
  int v42; // edi
  unsigned int v43; // esi
  int v44; // ecx
  int v45; // ebx
  int v46; // edi
  int v47; // esi
  int v48; // edx
  int v49; // esi
  BOOL v50; // edx
  int *v51; // ebp
  int v52; // eax
  int v53; // ecx
  int v54; // eax
  int *v55; // esi
  int v56; // eax
  int v57; // esi
  int v58; // eax
  int v59; // edx
  int v60; // esi
  int v61; // eax
  int *v62; // esi
  int v63; // eax
  int v64; // ecx
  int v65; // esi
  cm_polygon_t *polygons; // ebp
  cm_polygon_t *v67; // ebp
  int numPolygons; // ecx
  cm_polygon_t *v69; // eax
  int *v70; // edi
  float y; // edx
  int j; // ecx
  __int64 v73; // rax
  float v74; // edx
  double v75; // st7
  float v76; // edx
  float v77; // ecx
  float v78; // eax
  float v79; // edx
  float v80; // ecx
  bool keep1; // [esp+Ah] [ebp-162h]
  bool keep2; // [esp+Bh] [ebp-161h]
  int newEdgeNum2; // [esp+Ch] [ebp-160h] BYREF
  float dot; // [esp+10h] [ebp-15Ch] BYREF
  int p2BeforeShare; // [esp+14h] [ebp-158h]
  int p1AfterShare; // [esp+18h] [ebp-154h]
  float x; // [esp+1Ch] [ebp-150h]
  float v88; // [esp+20h] [ebp-14Ch]
  float z; // [esp+24h] [ebp-148h]
  float v90; // [esp+28h] [ebp-144h]
  float v91; // [esp+2Ch] [ebp-140h]
  float v92; // [esp+30h] [ebp-13Ch]
  int i; // [esp+34h] [ebp-138h]
  int p1BeforeShare; // [esp+38h] [ebp-134h]
  int p2AfterShare; // [esp+3Ch] [ebp-130h]
  int *v96; // [esp+40h] [ebp-12Ch]
  int v97; // [esp+44h] [ebp-128h]
  idCollisionModelManagerLocal *v98; // [esp+48h] [ebp-124h]
  int v99; // [esp+4Ch] [ebp-120h]
  float v100; // [esp+50h] [ebp-11Ch]
  float v101; // [esp+54h] [ebp-118h]
  float v102; // [esp+58h] [ebp-114h]
  float v103; // [esp+5Ch] [ebp-110h]
  float v104; // [esp+60h] [ebp-10Ch]
  float v105; // [esp+64h] [ebp-108h]
  int v106; // [esp+68h] [ebp-104h]
  int newEdges[64]; // [esp+6Ch] [ebp-100h] BYREF

  ++c_numTryMergePolygons;
  v4 = p1->material == p2->material;
  v98 = this;
  if ( !v4 )
    return 0;
  *(float *)&newEdgeNum2 = -p1->plane.d - -p2->plane.d;
  newEdgeNum2 &= ~0x80000000;
  if ( *(float *)&newEdgeNum2 > 0.0099999998 )
    return 0;
  v6 = 0;
  p_plane = &p2->plane;
  do
  {
    *(float *)&newEdgeNum2 = *(float *)((char *)&p_plane->a + (char *)p1 - (char *)p2) - p_plane->a;
    newEdgeNum2 &= ~0x80000000;
    if ( *(float *)&newEdgeNum2 > 0.0099999998
      || *(&p1->bounds.b[0].x + v6) > (double)p_plane[-4].d
      || *(&p1->bounds.b[1].x + v6) < (double)p_plane[-4].a )
    {
      return 0;
    }
    ++v6;
    p_plane = (idPlane *)((char *)p_plane + 4);
  }
  while ( v6 < 3 );
  numEdges = p1->numEdges;
  v9 = 0;
  p2AfterShare = -1;
  p2BeforeShare = -1;
  p1AfterShare = -1;
  p1BeforeShare = -1;
  *(float *)&i = 0.0;
  if ( numEdges <= 0 )
    return 0;
  v97 = p2->numEdges;
  do
  {
    v96 = (int *)((char *)v9 + 1);
    v10 = 0;
    LODWORD(dot) = ((int)v9 + 1) % numEdges;
    if ( v97 <= 0 )
      goto LABEL_24;
    v99 = p2->numEdges;
    v11 = p1->edges[(_DWORD)v9];
    edges = p2->edges;
    v106 = v11;
    *(float *)&v13 = COERCE_FLOAT(abs32(v11));
    newEdgeNum2 = v13;
    while ( 1 )
    {
      v14 = (v99 + v10 - 1) % v99;
      if ( v13 != abs32(edges[v10]) )
        break;
      if ( v106 != edges[v10] )
      {
        if ( abs32(p1->edges[LODWORD(dot)]) != abs32(edges[v14]) )
        {
          p1AfterShare = LODWORD(dot);
          p2BeforeShare = (v99 + v10 - 1) % v99;
          goto LABEL_24;
        }
        goto LABEL_20;
      }
LABEL_21:
      if ( ++v10 >= v97 )
        goto LABEL_24;
    }
    if ( abs32(p1->edges[LODWORD(dot)]) != abs32(edges[v14]) )
    {
LABEL_20:
      v13 = newEdgeNum2;
      goto LABEL_21;
    }
    if ( p1->edges[LODWORD(dot)] != edges[v14] )
    {
      p1BeforeShare = i;
      p2AfterShare = v10;
    }
LABEL_24:
    v9 = v96;
    numEdges = p1->numEdges;
    i = (int)v96;
  }
  while ( (int)v96 < numEdges );
  if ( p1BeforeShare < 0 || p1AfterShare < 0 || p2BeforeShare < 0 || p2AfterShare < 0 )
    return 0;
  v15 = p1->edges[p1BeforeShare];
  v16 = model->edges;
  vertices = model->vertices;
  v18 = &v16[abs32(v15)];
  v19 = v18->vertexNum[v15 >> 31];
  p_x = &vertices[v18->vertexNum[(v15 & 0x80000000) == 0]].p.x;
  v21 = &vertices[v19].p.x;
  v22 = *p_x - *v21;
  v23 = p_x[1] - v21[1];
  v24 = p_x[2] - v21[2];
  x = v24 * p1->plane.b - v23 * p1->plane.c;
  v88 = v22 * p1->plane.c - v24 * p1->plane.a;
  z = v23 * p1->plane.a - v22 * p1->plane.b;
  v25 = x;
  v26 = v88;
  v27 = z;
  *(float *)&i = x * x + z * z + v88 * v88;
  if ( *(float *)&i != 0.0 )
  {
    v28 = 1.0 / sqrt(*(float *)&i);
    *(float *)&newEdgeNum2 = v28;
    v25 = v28 * x;
    v26 = v88 * *(float *)&newEdgeNum2;
    v27 = z * *(float *)&newEdgeNum2;
  }
  v29 = p2->edges[p2AfterShare];
  v96 = p2->edges;
  v30 = &v16[abs32(v29)];
  v31 = v30->vertexNum[(unsigned int)v29 >> 31];
  v32 = &vertices[v30->vertexNum[v29 >= 0]].p.x;
  dot = (*v32 - vertices[v31].p.x) * v25 + (v32[2] - vertices[v31].p.z) * v27 + (v32[1] - vertices[v31].p.y) * v26;
  if ( dot < -0.0049999999 )
    return 0;
  keep1 = dot > 0.0049999999;
  v33 = &model->edges[abs32(v96[p2BeforeShare])];
  v34 = v33->vertexNum[v96[p2BeforeShare] >= 0];
  v35 = vertices[v34].p.x - vertices[v33->vertexNum[(unsigned int)v96[p2BeforeShare] >> 31]].p.x;
  v36 = vertices[v34].p.y - vertices[v33->vertexNum[(unsigned int)v96[p2BeforeShare] >> 31]].p.y;
  v37 = vertices[v34].p.z - vertices[v33->vertexNum[(unsigned int)v96[p2BeforeShare] >> 31]].p.z;
  x = v37 * p1->plane.b - v36 * p1->plane.c;
  v88 = v35 * p1->plane.c - v37 * p1->plane.a;
  z = v36 * p1->plane.a - v35 * p1->plane.b;
  v38 = x;
  v39 = v88;
  v40 = z;
  *(float *)&i = z * z + v88 * v88 + x * x;
  if ( *(float *)&i != 0.0 )
  {
    *(float *)&newEdgeNum2 = 1.0 / sqrt(*(float *)&i);
    v38 = x * *(float *)&newEdgeNum2;
    v39 = v88 * *(float *)&newEdgeNum2;
    v40 = z * *(float *)&newEdgeNum2;
  }
  v41 = p1->edges[p1AfterShare];
  HIDWORD(v41) = &model->edges[(HIDWORD(v41) ^ v41) - HIDWORD(v41)];
  LODWORD(v41) = *(_DWORD *)(HIDWORD(v41) + 4 * ((unsigned int)v41 >> 31) + 16);
  v42 = *(_DWORD *)(HIDWORD(v41) + 4 * (p1->edges[p1AfterShare] >= 0) + 16);
  dot = (vertices[v42].p.x - vertices[v41].p.x) * v38
      + (vertices[v42].p.z - vertices[v41].p.z) * v40
      + (vertices[v42].p.y - vertices[v41].p.y) * v39;
  if ( dot < -0.0049999999 )
    return 0;
  keep2 = dot > 0.0049999999;
  *(float *)&newEdgeNum2 = 0.0;
  dot = 0.0;
  if ( !keep1 )
  {
    idCollisionModelManagerLocal::GetEdge(
      v98,
      model,
      &vertices[model->edges[abs32(v15)].vertexNum[v15 >> 31]].p,
      &vertices[model->edges[abs32(v29)].vertexNum[v29 >= 0]].p,
      (int *)&dot,
      -1);
    keep1 = LODWORD(dot) == 0;
  }
  if ( !keep2 )
  {
    v43 = p2->edges[p2BeforeShare];
    v44 = p1->edges[p1AfterShare];
    idCollisionModelManagerLocal::GetEdge(
      v98,
      model,
      &model->vertices[model->edges[abs32(v43)].vertexNum[v43 >> 31]].p,
      &model->vertices[model->edges[abs32(v44)].vertexNum[v44 >= 0]].p,
      &newEdgeNum2,
      -1);
    keep2 = newEdgeNum2 == 0;
  }
  v45 = 0;
  if ( !keep2 )
  {
    newEdges[0] = newEdgeNum2;
    v45 = 1;
  }
  v46 = p1BeforeShare;
  v47 = p1AfterShare;
  v48 = 0;
  if ( p1AfterShare < p1BeforeShare )
  {
    LOBYTE(v48) = !keep2;
    v49 = v48 + p1AfterShare;
    p1AfterShare = v48;
    v50 = !keep1;
    if ( v49 <= p1BeforeShare - v50 )
    {
      v51 = &p1->edges[v49];
      v52 = p1BeforeShare - v50 - v49;
      goto LABEL_48;
    }
    goto LABEL_49;
  }
  v53 = p1->numEdges;
  LOBYTE(v48) = !keep2;
  p1AfterShare = v48;
  v54 = v47 + v48;
  if ( v47 + v48 < v53 )
  {
    v55 = &p1->edges[v54];
    v56 = v53 - v54;
    qmemcpy(&newEdges[v45], v55, 4 * v56);
    v46 = p1BeforeShare;
    v45 += v56;
  }
  v57 = p2BeforeShare;
  v50 = !keep1;
  v52 = v46 - v50;
  if ( v46 - v50 >= 0 )
  {
    v51 = p1->edges;
LABEL_48:
    v58 = v52 + 1;
    qmemcpy(&newEdges[v45], v51, 4 * v58);
    v45 += v58;
LABEL_49:
    v57 = p2BeforeShare;
  }
  if ( !keep1 )
    *(float *)&newEdges[v45++] = dot;
  v59 = p2AfterShare + v50;
  if ( p2AfterShare >= v57 )
  {
    v64 = p2->numEdges;
    if ( v59 < v64 )
    {
      qmemcpy(&newEdges[v45], &p2->edges[v59], 4 * (v64 - v59));
      v57 = p2BeforeShare;
      v45 += v64 - v59;
    }
    v65 = v57 - p1AfterShare;
    if ( v65 >= 0 )
    {
      v63 = v65 + 1;
      v62 = p2->edges;
LABEL_59:
      qmemcpy(&newEdges[v45], v62, 4 * v63);
      v45 += v63;
    }
  }
  else
  {
    v60 = v57 - p1AfterShare;
    if ( v59 <= v60 )
    {
      v61 = v60 - v59;
      v62 = &p2->edges[v59];
      v63 = v61 + 1;
      goto LABEL_59;
    }
  }
  polygons = model->polygons;
  if ( polygons || model->polygonEdges )
  {
    numPolygons = model->numPolygons;
    v67 = &polygons[numPolygons];
    model->numPolygons = numPolygons + 1;
    v67->numEdges = v45;
    v67->edges = &model->polygonEdges[model->numPolygonEdges];
    model->numPolygonEdges += v45;
  }
  else
  {
    ++model->numPolygons;
    model->numPolygonEdges += v45;
    v67 = (cm_polygon_t *)Mem_Alloc(4 * v45 + 88, 8u);
    v67->edges = (int *)&v67[1];
  }
  v69 = p1;
  v67->bounds.b[0].x = p1->bounds.b[0].x;
  v67->bounds.b[0].y = p1->bounds.b[0].y;
  v67->bounds.b[0].z = p1->bounds.b[0].z;
  v67->bounds.b[1] = p1->bounds.b[1];
  v67->checkcount = 0;
  v67->contents = p1->contents;
  v67->material = p1->material;
  v67->primitiveNum = p1->primitiveNum;
  v70 = v67->edges;
  v67->plane = p1->plane;
  v67->texBounds[0].x = p1->texBounds[0].x;
  v67->texBounds[0].y = p1->texBounds[0].y;
  v67->texBounds[1] = p1->texBounds[1];
  v67->texBounds[2].x = p1->texBounds[2].x;
  y = p1->texBounds[2].y;
  v67->numEdges = v45;
  v67->texBounds[2].y = y;
  qmemcpy(v70, newEdges, 4 * v45);
  for ( j = 0; j < v67->numEdges; ++j )
  {
    if ( (keep1 || v67->edges[j] != LODWORD(dot)) && (keep2 || v67->edges[j] != newEdgeNum2) )
    {
      v73 = v67->edges[j];
      ++model->edges[(HIDWORD(v73) ^ v73) - HIDWORD(v73)].numUsers;
      v69 = p1;
    }
  }
  v74 = v69->bounds.b[0].y;
  x = v69->bounds.b[0].x;
  z = v69->bounds.b[0].z;
  v91 = v69->bounds.b[1].y;
  v75 = p2->bounds.b[0].x;
  v88 = v74;
  v90 = v69->bounds.b[1].x;
  v92 = v69->bounds.b[1].z;
  if ( v75 < x )
    x = p2->bounds.b[0].x;
  if ( p2->bounds.b[0].y < (double)v88 )
    v88 = p2->bounds.b[0].y;
  if ( p2->bounds.b[0].z < (double)z )
    z = p2->bounds.b[0].z;
  if ( p2->bounds.b[1].x > (double)v90 )
    v90 = p2->bounds.b[1].x;
  if ( p2->bounds.b[1].y > (double)v91 )
    v91 = p2->bounds.b[1].y;
  if ( p2->bounds.b[1].z > (double)v92 )
    v92 = p2->bounds.b[1].z;
  v101 = v88;
  v100 = x;
  v102 = z;
  v104 = v91;
  v103 = v90;
  v76 = x;
  v105 = v92;
  v77 = z;
  v67->bounds.b[0].y = v88;
  v78 = v104;
  v67->bounds.b[0].x = v76;
  v79 = v103;
  v67->bounds.b[0].z = v77;
  v80 = v105;
  v67->bounds.b[1].y = v78;
  v67->bounds.b[1].x = v79;
  v67->bounds.b[1].z = v80;
  return v67;
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::MergePolygonWithTreePolygons(class idCollisionModelLocal *,struct cm_node_t *,struct cm_polygon_t *,bool)
char __thiscall idCollisionModelManagerLocal::MergePolygonWithTreePolygons(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node,
        cm_polygon_t *polygon,
        bool mergePrimitives)
{
  cm_node_t *v5; // edx
  cm_polygonRef_t *polygons; // ebx
  cm_polygon_t *p; // ebp
  cm_polygon_t *v8; // eax
  int planeType; // ecx
  cm_node_t *v10; // ecx
  int i; // ecx
  __int64 v12; // rax
  int j; // ecx
  __int64 v14; // rax

  while ( 1 )
  {
    v5 = node;
    polygons = node->polygons;
    if ( polygons )
      break;
LABEL_8:
    planeType = v5->planeType;
    if ( v5->planeType == -1 )
      return 0;
    if ( *(&polygon->bounds.b[0].x + planeType) <= (double)v5->planeDist )
    {
      if ( *(&polygon->bounds.b[1].x + planeType) >= (double)v5->planeDist )
      {
        if ( idCollisionModelManagerLocal::MergePolygonWithTreePolygons(
               this,
               model,
               v5->children[1],
               polygon,
               mergePrimitives) )
        {
          return 1;
        }
        node = node->children[0];
      }
      else
      {
        node = v5->children[1];
      }
    }
    else
    {
      node = v5->children[0];
    }
  }
  while ( 1 )
  {
    p = polygons->p;
    if ( polygons->p == polygon || !mergePrimitives && p->primitiveNum != polygon->primitiveNum )
      goto LABEL_7;
    v8 = idCollisionModelManagerLocal::TryMergePolygons(this, model, polygon, polygons->p);
    if ( v8 )
      break;
    v5 = node;
LABEL_7:
    polygons = polygons->next;
    if ( !polygons )
      goto LABEL_8;
  }
  v10 = model->node;
  ++model->numMergedPolys;
  idCollisionModelManagerLocal::ReplacePolygons(this, model, v10, polygon, p, v8);
  for ( i = 0; i < polygon->numEdges; ++i )
  {
    v12 = polygon->edges[i];
    --model->edges[(HIDWORD(v12) ^ v12) - HIDWORD(v12)].numUsers;
  }
  for ( j = 0; j < p->numEdges; ++j )
  {
    v14 = p->edges[j];
    --model->edges[(HIDWORD(v14) ^ v14) - HIDWORD(v14)].numUsers;
  }
  if ( !model->polygons )
  {
    if ( !model->polygonEdges )
    {
      --model->numPolygons;
      model->numPolygonEdges -= polygon->numEdges;
      Mem_Free(polygon);
    }
    if ( !model->polygons && !model->polygonEdges )
    {
      --model->numPolygons;
      model->numPolygonEdges -= p->numEdges;
      Mem_Free(p);
    }
  }
  return 1;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::MergeTreePolygons(class idCollisionModelLocal *,struct cm_node_t *,bool)
void __thiscall idCollisionModelManagerLocal::MergeTreePolygons(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node,
        bool mergePrimitives)
{
  cm_polygonRef_t *polygons; // esi
  cm_polygon_t *p; // eax
  int checkCount; // ecx

  while ( 1 )
  {
    while ( 1 )
    {
      polygons = node->polygons;
      if ( !polygons )
        break;
      while ( 1 )
      {
        p = polygons->p;
        checkCount = this->checkCount;
        if ( polygons->p->checkcount != checkCount )
        {
          p->checkcount = checkCount;
          if ( idCollisionModelManagerLocal::MergePolygonWithTreePolygons(this, model, model->node, p, mergePrimitives) )
            break;
        }
        polygons = polygons->next;
        if ( !polygons )
          goto LABEL_5;
      }
    }
LABEL_5:
    if ( node->planeType == -1 )
      break;
    idCollisionModelManagerLocal::MergeTreePolygons(this, model, node->children[1], mergePrimitives);
    node = node->children[0];
  }
}

// FUNC: private: struct cm_node_t * __thiscall idCollisionModelManagerLocal::CreateAxialBSPTree(class idCollisionModelLocal *,struct cm_node_t *)
cm_node_t *__thiscall idCollisionModelManagerLocal::CreateAxialBSPTree(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node)
{
  double v3; // st7
  cm_polygonRef_t *polygons; // esi
  float *p; // edx
  cm_brushRef_t *brushes; // esi
  float *b; // edx
  idBounds bounds; // [esp+8h] [ebp-18h] BYREF

  v3 = -1.0e30;
  bounds.b[1].z = -1.0e30;
  bounds.b[1].y = bounds.b[1].z;
  polygons = node->polygons;
  bounds.b[1].x = bounds.b[1].z;
  bounds.b[0].z = idMath::INFINITY;
  bounds.b[0].y = idMath::INFINITY;
  bounds.b[0].x = idMath::INFINITY;
  if ( polygons )
  {
    do
    {
      p = (float *)polygons->p;
      if ( polygons->p->bounds.b[0].x < (double)bounds.b[0].x )
        bounds.b[0].x = *p;
      if ( p[1] < (double)bounds.b[0].y )
        bounds.b[0].y = p[1];
      if ( p[2] < (double)bounds.b[0].z )
        bounds.b[0].z = p[2];
      if ( p[3] > (double)bounds.b[1].x )
        bounds.b[1].x = p[3];
      if ( p[4] > (double)bounds.b[1].y )
        bounds.b[1].y = p[4];
      if ( v3 < p[5] )
        v3 = p[5];
      polygons = polygons->next;
    }
    while ( polygons );
    bounds.b[1].z = v3;
  }
  brushes = node->brushes;
  if ( brushes )
  {
    do
    {
      b = (float *)brushes->b;
      if ( brushes->b->bounds.b[0].x < (double)bounds.b[0].x )
        bounds.b[0].x = *b;
      if ( b[1] < (double)bounds.b[0].y )
        bounds.b[0].y = b[1];
      if ( b[2] < (double)bounds.b[0].z )
        bounds.b[0].z = b[2];
      if ( b[3] > (double)bounds.b[1].x )
        bounds.b[1].x = b[3];
      if ( b[4] > (double)bounds.b[1].y )
        bounds.b[1].y = b[4];
      if ( v3 < b[5] )
        v3 = b[5];
      brushes = brushes->next;
    }
    while ( brushes );
    bounds.b[1].z = v3;
  }
  return idCollisionModelManagerLocal::R_CreateAxialBSPTree(this, model, node, &bounds);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::SetupHash(void)
void __thiscall idCollisionModelManagerLocal::SetupHash(idCollisionModelManagerLocal *this)
{
  idHashIndex *v2; // eax
  idHashIndex *v3; // esi
  idHashIndex *v4; // eax
  idHashIndex *v5; // esi
  cm_windingList_t *v6; // esi
  cm_windingList_t *v7; // eax
  cm_windingList_t *v8; // esi
  cm_windingList_t *v9; // eax
  cm_windingList_t *v10; // esi

  if ( !this->cm_vertexHash )
  {
    v2 = (idHashIndex *)Memory::Allocate(0x1Cu);
    v3 = v2;
    if ( v2 )
      idHashIndex::Init(v2, 4096, 1024);
    else
      v3 = 0;
    this->cm_vertexHash = v3;
  }
  if ( !this->cm_edgeHash )
  {
    v4 = (idHashIndex *)Memory::Allocate(0x1Cu);
    v5 = v4;
    if ( v4 )
      idHashIndex::Init(v4, 0x4000, 1024);
    else
      v5 = 0;
    this->cm_edgeHash = v5;
  }
  if ( !this->cm_windingList )
  {
    v6 = (cm_windingList_t *)Memory::Allocate(0x28840u);
    if ( v6 )
      `eh vector constructor iterator'(
        v6->w,
        0x510u,
        128,
        (void (__thiscall *)(void *))idFixedWinding::idFixedWinding,
        (void (__thiscall *)(void *))idFixedWinding::~idFixedWinding);
    else
      v6 = 0;
    this->cm_windingList = v6;
  }
  if ( !this->cm_outList )
  {
    v7 = (cm_windingList_t *)Memory::Allocate(0x28840u);
    v8 = v7;
    if ( v7 )
      `eh vector constructor iterator'(
        v7->w,
        0x510u,
        128,
        (void (__thiscall *)(void *))idFixedWinding::idFixedWinding,
        (void (__thiscall *)(void *))idFixedWinding::~idFixedWinding);
    else
      v8 = 0;
    this->cm_outList = v8;
  }
  if ( !this->cm_tmpList )
  {
    v9 = (cm_windingList_t *)Memory::Allocate(0x28840u);
    v10 = v9;
    if ( v9 )
    {
      `eh vector constructor iterator'(
        v9->w,
        0x510u,
        128,
        (void (__thiscall *)(void *))idFixedWinding::idFixedWinding,
        (void (__thiscall *)(void *))idFixedWinding::~idFixedWinding);
      this->cm_tmpList = v10;
    }
    else
    {
      this->cm_tmpList = 0;
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::OptimizeArrays(class idCollisionModelLocal *)
void __thiscall idCollisionModelManagerLocal::OptimizeArrays(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model)
{
  int numVertices; // ecx
  int numEdges; // edx
  int numPolygons; // eax
  int *v7; // esi
  int v8; // eax
  int v9; // edi
  int v10; // edx
  unsigned int v11; // ecx
  cm_edge_t *edges; // eax
  float x; // ebp
  int p_normal; // edi
  idVec3 *v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // edi
  int v20; // ecx
  int v21; // edx
  cm_vertex_t *vertices; // eax
  int v23; // ecx
  bool v24; // cc
  int v25; // edx
  cm_edge_t *v26; // eax
  int v27; // edi
  int *vertexNum; // eax
  cm_vertex_t *v29; // ebp
  cm_vertex_t *v30; // eax
  unsigned int v31; // edx
  cm_edge_t *v32; // ebp
  cm_edge_t *v33; // eax
  unsigned int v34; // edx
  int v35; // eax
  cm_polygon_t *v36; // eax
  int numPolygonEdges; // edx
  int *v38; // eax
  int numBrushes; // ecx
  idPlane *v40; // eax
  int v41; // [esp-28h] [ebp-3Ch]
  cm_brushRef_t *node; // [esp-Ch] [ebp-20h]
  int i; // [esp+8h] [ebp-Ch]
  idCollisionModelManagerLocal *v44; // [esp+Ch] [ebp-8h]
  unsigned int v45; // [esp+10h] [ebp-4h]
  int modela; // [esp+18h] [ebp+4h]
  idCollisionModelLocal *modelb; // [esp+18h] [ebp+4h]

  numVertices = model->numVertices;
  v44 = this;
  if ( numVertices > 0 )
  {
    numEdges = model->numEdges;
    numPolygons = model->numPolygons;
    if ( numVertices <= numEdges )
    {
      if ( numEdges > numPolygons )
        numPolygons = model->numEdges;
    }
    else if ( numVertices > numPolygons )
    {
      numPolygons = model->numVertices;
    }
    v45 = 4 * numPolygons;
    v7 = (int *)Mem_ClearedAlloc(4 * numPolygons, 8u);
    v8 = 1;
    v9 = 1;
    modela = 1;
    i = 1;
    if ( model->numEdges > 1 )
    {
      v10 = 1;
      v11 = 1;
      do
      {
        if ( model->edges[v11].numUsers )
        {
          v7[v8] = v9;
          edges = model->edges;
          edges[v10].checkcount = edges[v11].checkcount;
          edges[v10].internal = edges[v11].internal;
          edges[v10].numUsers = edges[v11].numUsers;
          edges[v10].side = edges[v11].side;
          edges[v10].sideSet = edges[v11].sideSet;
          edges[v10].vertexNum[0] = edges[v11].vertexNum[0];
          edges[v10].vertexNum[1] = edges[v11].vertexNum[1];
          x = edges[v11].normal.x;
          p_normal = (int)&edges[v11].normal;
          v15 = &edges[v10].normal;
          v15->x = x;
          v15->y = *(float *)(p_normal + 4);
          v15->z = *(float *)(p_normal + 8);
          v8 = i;
          v9 = ++modela;
          ++v10;
        }
        ++v8;
        ++v11;
        i = v8;
      }
      while ( v8 < model->numEdges );
      this = v44;
    }
    ++this->checkCount;
    idCollisionModelManagerLocal::RemapEdges(this, model->node, v7);
    model->numEdges = v9;
    memset(v7, 0, v45);
    v16 = 0;
    if ( model->numEdges > 0 )
    {
      v17 = 0;
      do
      {
        v7[model->edges[v17].vertexNum[0]] = 1;
        ++v16;
        v7[model->edges[v17++].vertexNum[1]] = 1;
      }
      while ( v16 < model->numEdges );
    }
    v18 = 0;
    v19 = 0;
    modelb = 0;
    if ( model->numVertices > 0 )
    {
      v20 = 0;
      v21 = 0;
      do
      {
        if ( v7[v19] )
        {
          v7[v19] = v18;
          vertices = model->vertices;
          vertices[v20].checkcount = vertices[v21].checkcount;
          vertices[v20].p.x = vertices[v21].p.x;
          vertices[v20].p.y = vertices[v21].p.y;
          vertices[v20].p.z = vertices[v21].p.z;
          vertices[v20].side = vertices[v21].side;
          vertices[v20].sideSet = vertices[v21].sideSet;
          v18 = (int)&modelb->__vftable + 1;
          modelb = (idCollisionModelLocal *)((char *)modelb + 1);
          ++v20;
        }
        ++v19;
        ++v21;
      }
      while ( v19 < model->numVertices );
    }
    v23 = 1;
    v24 = model->numEdges <= 1;
    model->numVertices = v18;
    if ( !v24 )
    {
      v25 = 1;
      do
      {
        v26 = model->edges;
        v27 = v7[v26[v25].vertexNum[0]];
        vertexNum = v26[v25].vertexNum;
        *vertexNum = v27;
        ++v23;
        vertexNum[1] = v7[vertexNum[1]];
        ++v25;
      }
      while ( v23 < model->numEdges );
    }
    Mem_Free(v7);
    v29 = model->vertices;
    if ( v29 )
    {
      v30 = (cm_vertex_t *)Mem_ClearedAlloc(24 * model->numVertices, 8u);
      v31 = 24 * model->numVertices;
      model->vertices = v30;
      qmemcpy(v30, v29, v31);
      Mem_Free(v29);
    }
    v32 = model->edges;
    if ( v32 )
    {
      v33 = (cm_edge_t *)Mem_ClearedAlloc(36 * model->numEdges, 8u);
      v34 = 36 * model->numEdges;
      model->edges = v33;
      qmemcpy(v33, v32, v34);
      Mem_Free(v32);
    }
    v35 = model->numPolygons;
    model->maxPolygons = v35;
    model->numPolygons = 0;
    v36 = (cm_polygon_t *)Mem_Alloc16(88 * v35, 8u);
    numPolygonEdges = model->numPolygonEdges;
    model->polygons = v36;
    model->maxPolygonEdges = numPolygonEdges;
    model->numPolygonEdges = 0;
    v38 = (int *)Mem_Alloc16(4 * numPolygonEdges, 8u);
    numBrushes = model->numBrushes;
    model->polygonEdges = v38;
    model->maxBrushes = numBrushes;
    model->numBrushes = 0;
    model->brushes = (cm_brush_t *)Mem_Alloc16(48 * numBrushes, 8u);
    v41 = 16 * model->numBrushPlanes;
    model->maxBrushPlanes = model->numBrushPlanes;
    model->numBrushPlanes = 0;
    v40 = (idPlane *)Mem_Alloc16(v41, 8u);
    node = (cm_brushRef_t *)model->node;
    model->brushPlanes = v40;
    idCollisionModelManagerLocal::ReAllocPolygonsAndBrushes_r(v44, model, node);
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::FinishModel(class idCollisionModelLocal *,bool)
void __thiscall idCollisionModelManagerLocal::FinishModel(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        bool mergePrimitives)
{
  ++this->checkCount;
  idCollisionModelManagerLocal::MergeTreePolygons(this, model, model->node, mergePrimitives);
  ++this->checkCount;
  idCollisionModelManagerLocal::FindInternalEdges(this, model, model->node);
  ++this->checkCount;
  idCollisionModelManagerLocal::CalculateEdgeNormals(this, model, model->node);
  idCollisionModelManagerLocal::OptimizeArrays(this, model);
  CM_GetNodeBounds(&model->bounds, model->node);
  model->contents = CM_GetNodeContents(model->node);
  model->usedMemory = CM_GetModelMemory(model);
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::PrintMemInfo(class MemInfo *)
void __thiscall idCollisionModelManagerLocal::PrintMemInfo(idCollisionModelManagerLocal *this, MemInfo *mi)
{
  idStr *v3; // eax
  idFileSystem_vtbl *v4; // edx
  int v5; // ebx
  idFile *v6; // esi
  int i; // ebp
  idCollisionModelLocal *v8; // eax
  idStr *v9; // edi
  idStr *v10; // eax
  idFile_vtbl *v11; // edx
  char *v12; // [esp-1Ch] [ebp-94h]
  char *v13; // [esp-18h] [ebp-90h]
  char *data; // [esp-Ch] [ebp-84h]
  int usedMemory; // [esp-Ch] [ebp-84h]
  idStr result; // [esp+Ch] [ebp-6Ch] BYREF
  idStr v17; // [esp+2Ch] [ebp-4Ch] BYREF
  idStr v18; // [esp+4Ch] [ebp-2Ch] BYREF
  int v19; // [esp+74h] [ebp-4h]

  v3 = operator+(&result, &mi->filebase, "_coll.txt");
  v4 = fileSystem->__vftable;
  v5 = 0;
  data = v3->data;
  v19 = 0;
  v6 = v4->OpenFileWrite(fileSystem, data, "fs_savepath", 0);
  v19 = -1;
  idStr::FreeData(&result);
  if ( v6 )
  {
    for ( i = 0; i < this->models.num; ++i )
    {
      v8 = this->models.list[i];
      usedMemory = v8->usedMemory;
      v5 += usedMemory;
      v6->Printf(v6, "%8d: %s\n", usedMemory, v8->name.data);
    }
    mi->collAssetsTotal = v5;
    mi->collAssetsCount = this->models.num;
    v9 = idStr::FormatNumber(&v18, this->models.num);
    v19 = 1;
    v10 = idStr::FormatNumber(&v17, v5);
    v11 = v6->__vftable;
    v13 = v9->data;
    v12 = v10->data;
    LOBYTE(v19) = 2;
    v11->Printf(v6, "\nTotal collision model bytes allocated: %s (%s items)\n", v12, v13);
    LOBYTE(v19) = 1;
    idStr::FreeData(&v17);
    v19 = -1;
    idStr::FreeData(&v18);
    fileSystem->CloseFile(fileSystem, v6);
  }
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::Init(void)
// attributes: thunk
void __thiscall idCollisionModelManagerLocal::Init(idCollisionModelManagerLocal *this)
{
  idCollisionModelManagerLocal::Clear(this);
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::FreeModel(class idCollisionModel *)
void __thiscall idCollisionModelManagerLocal::FreeModel(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model)
{
  idCollisionModel_vtbl *refCount; // eax

  if ( model )
  {
    if ( model->isTraceModel )
    {
      idCollisionModelManagerLocal::FreeModelMemory(this, model);
      ((void (__thiscall *)(idCollisionModelLocal *, int))model->~idCollisionModelLocal)(model, 1);
    }
    else if ( idCollisionModelManagerLocal::IsRenderModelName(this, model->name.data) )
    {
      refCount = (idCollisionModel_vtbl *)model->refCount;
      if ( (int)refCount > 0 )
        model->refCount = (int)&refCount[-1].GetPolygon + 3;
    }
  }
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::ChoppedAwayByProcBSP(class idFixedWinding const &,class idPlane const &,int)
int __thiscall idCollisionModelManagerLocal::ChoppedAwayByProcBSP(
        idCollisionModelManagerLocal *this,
        const idFixedWinding *w,
        const idPlane *plane,
        char contents)
{
  bool v5; // zf
  double v7; // st7
  int v8; // esi
  float v9; // [esp+8h] [ebp-558h]
  float v10; // [esp+Ch] [ebp-554h]
  float v11; // [esp+10h] [ebp-550h]
  float v12; // [esp+10h] [ebp-550h]
  float radius; // [esp+1Ch] [ebp-544h]
  idBounds bounds; // [esp+20h] [ebp-540h] BYREF
  idVec3 origin; // [esp+38h] [ebp-528h] BYREF
  idFixedWinding neww; // [esp+44h] [ebp-51Ch] BYREF
  int v17; // [esp+55Ch] [ebp-4h]

  neww.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  neww.numPoints = 0;
  neww.p = neww.data;
  neww.allocedSize = 64;
  v5 = this->procNodes == 0;
  v17 = 0;
  if ( !v5 && (contents & 1) != 0 )
  {
    idFixedWinding::operator=(&neww, (int)w);
    idWinding::GetBounds(&neww, &bounds);
    v11 = bounds.b[1].x - bounds.b[0].x;
    v9 = (bounds.b[1].z - bounds.b[0].z) * 0.5;
    v10 = (bounds.b[1].y - bounds.b[0].y) * 0.5;
    v7 = v11 * 0.5;
    v12 = v7;
    radius = sqrt(v7 * v12 + v10 * v10 + v9 * v9) + 0.1;
    origin.x = bounds.b[0].x + v12;
    origin.y = bounds.b[0].y + v10;
    origin.z = bounds.b[0].z + v9;
    v8 = idCollisionModelManagerLocal::R_ChoppedAwayByProcBSP(this, 0, &neww, (const idVec3 *)plane, &origin, radius);
    v17 = -1;
    neww.p = 0;
    neww.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(0);
    return v8;
  }
  else
  {
    v17 = -1;
    neww.p = 0;
    neww.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(0);
    return 0;
  }
}

// FUNC: private: class idFixedWinding * __thiscall idCollisionModelManagerLocal::WindingOutsideBrushes(class idCollisionModelLocal *,class idFixedWinding *,class idPlane const &,int,int)
idFixedWinding *__thiscall idCollisionModelManagerLocal::WindingOutsideBrushes(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        idFixedWinding *w,
        const idPlane *plane,
        int contents,
        int primitiveNum)
{
  float *p_bounds; // eax
  int v8; // ebx
  int v9; // edi
  idVec5 *p; // ecx
  cm_windingList_t *cm_windingList; // edx
  bool v12; // c0
  float *p_x; // ecx
  idBounds *v14; // edx
  float *p_numWindings; // eax
  double v16; // st7
  cm_windingList_t *v17; // eax
  cm_windingList_t *v18; // eax
  double v19; // st7
  double v20; // st6
  float *v21; // eax
  double v22; // st7
  float *v23; // eax
  double v24; // st7
  float *v26; // eax
  cm_windingList_t *v27; // ecx
  int v29; // ebx
  int v30; // ebp
  cm_windingList_t *v31; // ecx
  float v32; // [esp+14h] [ebp-8h]
  float v33; // [esp+18h] [ebp-4h]
  float v34; // [esp+18h] [ebp-4h]
  float v35; // [esp+18h] [ebp-4h]
  int planea; // [esp+28h] [ebp+Ch]

  p_bounds = (float *)&this->cm_windingList->bounds;
  p_bounds[2] = idMath::INFINITY;
  p_bounds[1] = idMath::INFINITY;
  *p_bounds = idMath::INFINITY;
  v8 = 0;
  p_bounds[5] = -1.0e30;
  p_bounds[4] = -1.0e30;
  p_bounds[3] = -1.0e30;
  if ( w->numPoints > 0 )
  {
    v9 = 0;
    do
    {
      p = w->p;
      cm_windingList = this->cm_windingList;
      v12 = p[v9].x < (double)cm_windingList->bounds.b[0].x;
      p_x = &p[v9].x;
      v14 = &cm_windingList->bounds;
      if ( v12 )
        v14->b[0].x = *p_x;
      if ( *p_x > (double)v14->b[1].x )
        v14->b[1].x = *p_x;
      if ( p_x[1] < (double)v14->b[0].y )
        v14->b[0].y = p_x[1];
      if ( p_x[1] > (double)v14->b[1].y )
        v14->b[1].y = p_x[1];
      if ( p_x[2] < (double)v14->b[0].z )
        v14->b[0].z = p_x[2];
      if ( p_x[2] > (double)v14->b[1].z )
        v14->b[1].z = p_x[2];
      ++v8;
      ++v9;
    }
    while ( v8 < w->numPoints );
  }
  p_numWindings = (float *)&this->cm_windingList->numWindings;
  v16 = p_numWindings[41479] - p_numWindings[41476];
  v32 = p_numWindings[41480] - p_numWindings[41477];
  v33 = p_numWindings[41481] - p_numWindings[41478];
  v34 = v33 * 0.5;
  p_numWindings[41484] = v34;
  p_numWindings[41482] = v16 * 0.5;
  p_numWindings[41483] = v32 * 0.5;
  v17 = this->cm_windingList;
  v17->radius = sqrt(v17->origin.x * v17->origin.x + v17->origin.y * v17->origin.y + v17->origin.z * v17->origin.z)
              + 0.1;
  v18 = this->cm_windingList;
  v19 = v18->origin.x + v18->bounds.b[0].x;
  v20 = v18->origin.y + v18->bounds.b[0].y;
  v35 = v18->origin.z + v18->bounds.b[0].z;
  v18->origin.z = v35;
  v18->origin.x = v19;
  v18->origin.y = v20;
  v21 = (float *)&this->cm_windingList->numWindings;
  v22 = v21[41476];
  v21 += 41476;
  *v21 = v22 - 0.1;
  v21[1] = v21[1] - 0.1;
  v21[2] = v21[2] - 0.1;
  v23 = (float *)&this->cm_windingList->numWindings;
  v24 = v23[41479];
  v23 += 41479;
  *v23 = v24 + 0.1;
  v23[1] = v23[1] + 0.1;
  v23[2] = v23[2] + 0.1;
  idFixedWinding::operator=(&this->cm_windingList->w[0].__vftable, (int)w);
  this->cm_windingList->numWindings = 1;
  v26 = (float *)&this->cm_windingList->numWindings;
  v26[41473] = plane->a;
  v26 += 41473;
  v26[1] = plane->b;
  v26[2] = plane->c;
  this->cm_windingList->contents = contents;
  this->cm_windingList->primitiveNum = primitiveNum;
  ++this->checkCount;
  idCollisionModelManagerLocal::R_ChopWindingListWithTreeBrushes(this, this->cm_windingList, model->node);
  v27 = this->cm_windingList;
  if ( !v27->numWindings )
    return 0;
  if ( v27->numWindings == 1 )
    return v27->w;
  if ( idStr::Cmp(model->name.data, "worldMap") )
    return w;
  v29 = 0;
  planea = -1;
  if ( this->cm_windingList->numWindings <= 0 )
    return 0;
  v30 = 0;
  do
  {
    if ( !idCollisionModelManagerLocal::ChoppedAwayByProcBSP(this, &this->cm_windingList->w[v30], plane, contents) )
    {
      if ( planea >= 0 )
        return w;
      planea = v29;
    }
    v31 = this->cm_windingList;
    ++v29;
    ++v30;
  }
  while ( v29 < v31->numWindings );
  if ( planea < 0 )
    return 0;
  return &v31->w[planea];
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ShutdownHash(void)
void __thiscall idCollisionModelManagerLocal::ShutdownHash(idCollisionModelManagerLocal *this)
{
  idHashIndex *cm_vertexHash; // edi
  idHashIndex *cm_edgeHash; // edi
  cm_windingList_t *cm_tmpList; // edi
  cm_windingList_t *cm_outList; // edi
  cm_windingList_t *cm_windingList; // edi

  cm_vertexHash = this->cm_vertexHash;
  if ( cm_vertexHash )
  {
    idHashIndex::Free(this->cm_vertexHash);
    Memory::Free(cm_vertexHash);
  }
  cm_edgeHash = this->cm_edgeHash;
  this->cm_vertexHash = 0;
  if ( cm_edgeHash )
  {
    idHashIndex::Free(cm_edgeHash);
    Memory::Free(cm_edgeHash);
  }
  cm_tmpList = this->cm_tmpList;
  this->cm_edgeHash = 0;
  if ( cm_tmpList )
  {
    cm_windingList_t::~cm_windingList_t(cm_tmpList);
    Memory::Free(cm_tmpList);
  }
  cm_outList = this->cm_outList;
  this->cm_tmpList = 0;
  if ( cm_outList )
  {
    cm_windingList_t::~cm_windingList_t(cm_outList);
    Memory::Free(cm_outList);
  }
  cm_windingList = this->cm_windingList;
  this->cm_outList = 0;
  if ( cm_windingList )
  {
    cm_windingList_t::~cm_windingList_t(cm_windingList);
    Memory::Free(cm_windingList);
  }
  this->cm_windingList = 0;
}

// FUNC: public: void __thiscall idCollisionModelManagerLocal::PolygonFromWinding(class idCollisionModelLocal *,class idFixedWinding *,class idPlane const &,class idMaterial const *,int)
void __thiscall idCollisionModelManagerLocal::PolygonFromWinding(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        idFixedWinding *w,
        const idPlane *plane,
        const idMaterial *material,
        int primitiveNum)
{
  int contentFlags; // edi
  idFixedWinding *v8; // eax
  idFixedWinding *v9; // edi
  idPlane v10; // [esp+10h] [ebp-10h] BYREF

  contentFlags = material->contentFlags;
  if ( (idStr::Icmp(model->name.data, "worldMap")
     || !idCollisionModelManagerLocal::ChoppedAwayByProcBSP(this, w, plane, contentFlags))
    && (v8 = idCollisionModelManagerLocal::WindingOutsideBrushes(this, model, w, plane, contentFlags, primitiveNum),
        (v9 = v8) != 0) )
  {
    if ( idWinding::IsHuge(v8) )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "idCollisionModelManagerLocal::PolygonFromWinding: model %s primitive %d is degenerate",
        model->name.data,
        abs32(primitiveNum));
    }
    else
    {
      idCollisionModelManagerLocal::CreatePolygon(this, model, v9, plane, material, primitiveNum);
      if ( material->cullType == CT_TWO_SIDED || material->shouldCreateBackSides )
      {
        idWinding::ReverseSelf(v9);
        v10.a = -plane->a;
        v10.b = -plane->b;
        v10.c = -plane->c;
        v10.d = -plane->d;
        idCollisionModelManagerLocal::CreatePolygon(this, model, v9, &v10, material, primitiveNum);
      }
    }
  }
  else
  {
    ++model->numRemovedPolys;
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::CreatePatchPolygons(class idCollisionModelLocal *,class idSurface_Patch &,class idMaterial const *,int)
void __thiscall idCollisionModelManagerLocal::CreatePatchPolygons(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        idSurface_Patch *mesh,
        const idMaterial *material,
        int primitiveNum)
{
  bool v5; // cc
  int width; // eax
  int v7; // esi
  int v8; // ecx
  int v9; // edx
  int v10; // edi
  idDrawVert *list; // eax
  int v12; // esi
  int v13; // ebp
  int v14; // edx
  double v15; // st7
  double y; // st6
  double v17; // st6
  double v18; // st5
  double v19; // st4
  double v20; // st7
  long double v21; // st6
  long double v22; // st7
  long double v23; // st5
  unsigned __int8 v25; // c2
  unsigned __int8 v26; // c3
  idDrawVert *v27; // edi
  double v28; // st7
  double v29; // st6
  int numPoints; // eax
  idVec5 *v31; // edx
  float v32; // ecx
  double v33; // st7
  float v34; // eax
  int v35; // ecx
  float v36; // eax
  int *v37; // esi
  int v38; // ecx
  int v39; // edx
  int v40; // eax
  int v41; // ecx
  idVec5 *v42; // ecx
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // edx
  int *v47; // esi
  int v48; // eax
  int v49; // edx
  int v50; // ecx
  int v51; // edx
  idVec5 *v52; // edx
  int v53; // ecx
  int v54; // eax
  int v55; // ecx
  int v56; // eax
  int *v57; // esi
  int v58; // ecx
  int v59; // edx
  int v60; // eax
  int v61; // ecx
  idVec5 *v62; // ecx
  int v63; // eax
  int v64; // edx
  int v65; // eax
  int v66; // edx
  int v67; // eax
  idVec5 *v68; // edx
  float v69; // ecx
  double v70; // st7
  int v71; // eax
  int v72; // ecx
  float v73; // eax
  int *v74; // edi
  int v75; // ecx
  int v76; // edx
  int v77; // eax
  int v78; // ecx
  idVec5 *v79; // ecx
  int v80; // eax
  int v81; // edx
  int v82; // eax
  int v83; // edx
  int *v84; // edi
  int v85; // eax
  int v86; // edx
  int v87; // ecx
  int v88; // edx
  idVec5 *v89; // edx
  int v90; // ecx
  int v91; // eax
  int v92; // ecx
  int v93; // eax
  idDrawVert *v94; // eax
  int v95; // edi
  double v96; // st7
  double v97; // st6
  double v98; // st5
  double v99; // st4
  double v100; // st7
  long double v101; // st6
  long double v102; // st7
  long double v103; // st5
  unsigned __int8 v105; // c2
  unsigned __int8 v106; // c3
  idDrawVert *v107; // eax
  double v108; // st7
  char *v109; // esi
  int v110; // eax
  double v111; // st7
  double v112; // st6
  int v113; // edx
  int v114; // ecx
  float v115; // edx
  float v116; // ecx
  idVec5 *v117; // ecx
  int v118; // eax
  int v119; // edx
  float v120; // eax
  float v121; // edx
  int *v122; // esi
  int v123; // eax
  int v124; // edx
  int v125; // ecx
  int v126; // edx
  idVec5 *v127; // edx
  int v128; // ecx
  int v129; // eax
  int v130; // ecx
  int v131; // eax
  int *v132; // esi
  int v133; // ecx
  int v134; // edx
  int v135; // eax
  int v136; // ecx
  idVec5 *v137; // ecx
  int v138; // eax
  int v139; // edx
  int v140; // eax
  int v141; // edx
  int v142; // eax
  int v143; // eax
  float v144; // [esp+2Ch] [ebp-61Ch]
  float v145; // [esp+2Ch] [ebp-61Ch]
  idPlane plane; // [esp+30h] [ebp-618h] BYREF
  float v147; // [esp+40h] [ebp-608h]
  int v148; // [esp+44h] [ebp-604h]
  int v4; // [esp+48h] [ebp-600h]
  int v150; // [esp+4Ch] [ebp-5FCh]
  int i; // [esp+50h] [ebp-5F8h]
  idCollisionModelManagerLocal *v152; // [esp+54h] [ebp-5F4h]
  int j; // [esp+58h] [ebp-5F0h]
  float v154; // [esp+5Ch] [ebp-5ECh]
  float v155; // [esp+60h] [ebp-5E8h]
  float v156; // [esp+64h] [ebp-5E4h]
  float v157; // [esp+68h] [ebp-5E0h]
  float v158; // [esp+6Ch] [ebp-5DCh]
  int v159; // [esp+70h] [ebp-5D8h]
  float v160; // [esp+74h] [ebp-5D4h]
  int v161; // [esp+78h] [ebp-5D0h]
  int v162; // [esp+7Ch] [ebp-5CCh]
  int v163; // [esp+80h] [ebp-5C8h]
  int v164; // [esp+84h] [ebp-5C4h]
  int v165; // [esp+88h] [ebp-5C0h]
  int v166; // [esp+8Ch] [ebp-5BCh]
  int v167; // [esp+90h] [ebp-5B8h]
  int v168; // [esp+94h] [ebp-5B4h]
  int v169; // [esp+98h] [ebp-5B0h]
  int v170; // [esp+9Ch] [ebp-5ACh]
  int v171; // [esp+A0h] [ebp-5A8h]
  int v172; // [esp+A4h] [ebp-5A4h]
  int v173; // [esp+A8h] [ebp-5A0h]
  int v174; // [esp+ACh] [ebp-59Ch]
  int v175; // [esp+B0h] [ebp-598h]
  float v176; // [esp+B4h] [ebp-594h]
  int v177; // [esp+B8h] [ebp-590h]
  int v178; // [esp+BCh] [ebp-58Ch]
  float v179; // [esp+C0h] [ebp-588h]
  float v180; // [esp+C4h] [ebp-584h]
  float v181; // [esp+C8h] [ebp-580h]
  float v182; // [esp+CCh] [ebp-57Ch]
  int v183; // [esp+D0h] [ebp-578h]
  int v184; // [esp+D4h] [ebp-574h]
  float v185; // [esp+D8h] [ebp-570h]
  int v186; // [esp+DCh] [ebp-56Ch]
  int v187; // [esp+E0h] [ebp-568h]
  int v188; // [esp+E4h] [ebp-564h]
  int v189; // [esp+E8h] [ebp-560h]
  int v190; // [esp+ECh] [ebp-55Ch]
  int v191; // [esp+F0h] [ebp-558h]
  int v192; // [esp+F4h] [ebp-554h]
  int v193; // [esp+F8h] [ebp-550h]
  int v194; // [esp+FCh] [ebp-54Ch]
  int v195; // [esp+100h] [ebp-548h]
  int v196; // [esp+104h] [ebp-544h]
  int v197; // [esp+108h] [ebp-540h]
  int v198; // [esp+10Ch] [ebp-53Ch]
  int v199; // [esp+110h] [ebp-538h]
  int v200; // [esp+114h] [ebp-534h]
  int v201; // [esp+118h] [ebp-530h]
  int v202; // [esp+11Ch] [ebp-52Ch]
  int v203; // [esp+120h] [ebp-528h]
  int v204; // [esp+124h] [ebp-524h]
  int v205; // [esp+128h] [ebp-520h]
  idFixedWinding w; // [esp+12Ch] [ebp-51Ch] BYREF
  int v207; // [esp+644h] [ebp-4h]

  v152 = this;
  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v207 = 0;
  i = 0;
  if ( mesh->width - 1 > 0 )
  {
    while ( 1 )
    {
      v5 = mesh->height - 1 <= 0;
      j = 0;
      if ( !v5 )
        break;
LABEL_114:
      v143 = mesh->width - 1;
      if ( ++i >= v143 )
        goto LABEL_115;
    }
    while ( 1 )
    {
      width = mesh->width;
      v7 = i + j * width;
      v8 = v7 + 1;
      v9 = width + v7 + 1;
      v10 = width + v7;
      list = mesh->verts.list;
      v12 = v7 << 6;
      v13 = v8 << 6;
      v14 = v9 << 6;
      v15 = list[v8].xyz.z - *(float *)((char *)&list->xyz.z + v12);
      v4 = v10;
      y = list[v8].xyz.y;
      v150 = v14;
      v17 = y - *(float *)((char *)&list->xyz.y + v12);
      v18 = list[v8].xyz.x - *(float *)((char *)&list->xyz.x + v12);
      v155 = *(float *)((char *)&list->xyz.z + v14) - *(float *)((char *)&list->xyz.z + v12);
      *(float *)&v148 = *(float *)((char *)&list->xyz.y + v14) - *(float *)((char *)&list->xyz.y + v12);
      v19 = *(float *)((char *)&list->xyz.x + v14) - *(float *)((char *)&list->xyz.x + v12);
      v144 = *(float *)&v148 * v18 - v19 * v17;
      plane.c = v144;
      v147 = v19 * v15 - v155 * v18;
      plane.b = v147;
      v20 = v155 * v17 - *(float *)&v148 * v15;
      plane.a = v20;
      v21 = v20 * v20 + v147 * v147 + v144 * v144;
      if ( v21 == 0.0 )
      {
        v22 = 0.0;
      }
      else
      {
        v23 = 1.0 / sqrt(v21);
        plane.a = v23 * v20;
        plane.b = v147 * v23;
        plane.c = v144 * v23;
        v22 = v23 * v21;
      }
      if ( v26 | v25 )
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
          goto LABEL_39;
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
          goto LABEL_39;
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
        goto LABEL_39;
      }
      if ( COERCE_FLOAT(LODWORD(plane.a) & 0x7FFFFFFF) == 1.0 )
      {
        if ( plane.b != 0.0 || plane.c != 0.0 )
        {
          plane.c = 0.0;
LABEL_38:
          plane.b = 0.0;
        }
      }
      else if ( COERCE_FLOAT(LODWORD(plane.b) & 0x7FFFFFFF) == 1.0 )
      {
        if ( plane.a != 0.0 || plane.c != 0.0 )
        {
          plane.c = 0.0;
          plane.a = 0.0;
        }
      }
      else if ( COERCE_FLOAT(LODWORD(plane.c) & 0x7FFFFFFF) == 1.0 && (plane.a != 0.0 || plane.b != 0.0) )
      {
        plane.a = 0.0;
        goto LABEL_38;
      }
LABEL_39:
      if ( v22 == 0.0 )
        goto LABEL_65;
      v27 = mesh->verts.list;
      v28 = plane.c * *(float *)((char *)&v27->xyz.z + v12);
      v29 = plane.b * *(float *)((char *)&v27->xyz.y + v12);
      v148 = v4 << 6;
      plane.d = -(v28 + v29 + plane.a * *(float *)((char *)&v27->xyz.x + v12));
      v154 = plane.c * v27[v4].xyz.z + plane.b * v27[v4].xyz.y + plane.a * v27[v4].xyz.x + plane.d;
      HIBYTE(v154) &= ~0x80u;
      if ( v154 < 0.1 )
      {
        numPoints = 0;
        w.numPoints = 0;
        if ( w.allocedSize >= 1 )
          goto LABEL_44;
        if ( w.ReAllocate(&w, 1, 1) )
        {
          numPoints = w.numPoints;
LABEL_44:
          v156 = *(float *)((char *)&v27->xyz.x + v12);
          v31 = &w.p[numPoints];
          v157 = *(float *)((char *)&v27->xyz.y + v12);
          v32 = v157;
          v158 = *(float *)((char *)&v27->xyz.z + v12);
          v159 = *(int *)((char *)&v27->st.x + v12);
          v33 = *(float *)((char *)&v27->st.y + v12);
          v31->x = v156;
          v34 = v158;
          v160 = v33;
          v31->y = v32;
          v35 = v159;
          v31->z = v34;
          v36 = v160;
          LODWORD(v31->s) = v35;
          v31->t = v36;
          ++w.numPoints;
        }
        v37 = (int *)((char *)mesh->verts.list + v13);
        if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
        {
          v38 = v37[1];
          v39 = v37[2];
          v201 = *v37;
          v40 = v37[14];
          v202 = v38;
          v41 = v37[15];
          v204 = v40;
          v203 = v39;
          v205 = v41;
          v42 = &w.p[w.numPoints];
          v43 = v202;
          LODWORD(v42->x) = v201;
          v44 = v203;
          LODWORD(v42->y) = v43;
          v45 = v204;
          LODWORD(v42->z) = v44;
          v46 = v205;
          LODWORD(v42->s) = v45;
          LODWORD(v42->t) = v46;
          ++w.numPoints;
        }
        v47 = (int *)((char *)mesh->verts.list + v150);
        if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
        {
          v48 = v47[2];
          v49 = v47[1];
          v171 = *v47;
          v50 = v47[14];
          v172 = v49;
          v51 = v47[15];
          v173 = v48;
          v175 = v51;
          v174 = v50;
          v52 = &w.p[w.numPoints];
          v53 = v172;
          LODWORD(v52->x) = v171;
          v54 = v173;
          LODWORD(v52->y) = v53;
          v55 = v174;
          LODWORD(v52->z) = v54;
          v56 = v175;
          LODWORD(v52->s) = v55;
          LODWORD(v52->t) = v56;
          ++w.numPoints;
        }
        v57 = (int *)((char *)mesh->verts.list + v148);
        if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
        {
          v58 = v57[1];
          v59 = v57[2];
          v191 = *v57;
          v60 = v57[14];
          v192 = v58;
          v61 = v57[15];
          v194 = v60;
          v193 = v59;
          v195 = v61;
          v62 = &w.p[w.numPoints];
          v63 = v192;
          LODWORD(v62->x) = v191;
          v64 = v193;
          LODWORD(v62->y) = v63;
          v65 = v194;
          LODWORD(v62->z) = v64;
          v66 = v195;
          LODWORD(v62->s) = v65;
          LODWORD(v62->t) = v66;
          ++w.numPoints;
        }
        goto LABEL_112;
      }
      v67 = 0;
      w.numPoints = 0;
      if ( w.allocedSize < 1 )
      {
        if ( !w.ReAllocate(&w, 1, 1) )
          goto LABEL_58;
        v67 = w.numPoints;
      }
      v181 = *(float *)((char *)&v27->xyz.x + v12);
      v68 = &w.p[v67];
      v182 = *(float *)((char *)&v27->xyz.y + v12);
      v69 = v182;
      v183 = *(int *)((char *)&v27->xyz.z + v12);
      v184 = *(int *)((char *)&v27->st.x + v12);
      v70 = *(float *)((char *)&v27->st.y + v12);
      v68->x = v181;
      v71 = v183;
      v185 = v70;
      v68->y = v69;
      v72 = v184;
      LODWORD(v68->z) = v71;
      v73 = v185;
      LODWORD(v68->s) = v72;
      v68->t = v73;
      ++w.numPoints;
LABEL_58:
      v74 = (int *)((char *)mesh->verts.list + v13);
      if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
      {
        v75 = v74[1];
        v76 = v74[2];
        v161 = *v74;
        v77 = v74[14];
        v162 = v75;
        v78 = v74[15];
        v164 = v77;
        v163 = v76;
        v165 = v78;
        v79 = &w.p[w.numPoints];
        v80 = v162;
        LODWORD(v79->x) = v161;
        v81 = v163;
        LODWORD(v79->y) = v80;
        v82 = v164;
        LODWORD(v79->z) = v81;
        v83 = v165;
        LODWORD(v79->s) = v82;
        LODWORD(v79->t) = v83;
        ++w.numPoints;
      }
      v84 = (int *)((char *)mesh->verts.list + v150);
      if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
      {
        v85 = v84[2];
        v86 = v84[1];
        v166 = *v84;
        v87 = v84[14];
        v167 = v86;
        v88 = v84[15];
        v168 = v85;
        v170 = v88;
        v169 = v87;
        v89 = &w.p[w.numPoints];
        v90 = v167;
        LODWORD(v89->x) = v166;
        v91 = v168;
        LODWORD(v89->y) = v90;
        v92 = v169;
        LODWORD(v89->z) = v91;
        v93 = v170;
        LODWORD(v89->s) = v92;
        LODWORD(v89->t) = v93;
        ++w.numPoints;
      }
      idCollisionModelManagerLocal::PolygonFromWinding(v152, model, &w, &plane, material, -primitiveNum);
      v10 = v4;
      v14 = v150;
LABEL_65:
      v94 = mesh->verts.list;
      v95 = v10 << 6;
      v96 = *(float *)((char *)&v94->xyz.z + v14) - *(float *)((char *)&v94->xyz.z + v12);
      v97 = *(float *)((char *)&v94->xyz.y + v14) - *(float *)((char *)&v94->xyz.y + v12);
      v98 = *(float *)((char *)&v94->xyz.x + v14) - *(float *)((char *)&v94->xyz.x + v12);
      *(float *)&v4 = *(float *)((char *)&v94->xyz.z + v95) - *(float *)((char *)&v94->xyz.z + v12);
      *(float *)&v148 = *(float *)((char *)&v94->xyz.y + v95) - *(float *)((char *)&v94->xyz.y + v12);
      v99 = *(float *)((char *)&v94->xyz.x + v95) - *(float *)((char *)&v94->xyz.x + v12);
      v147 = *(float *)&v148 * v98 - v99 * v97;
      plane.c = v147;
      v145 = v99 * v96 - *(float *)&v4 * v98;
      plane.b = v145;
      v100 = *(float *)&v4 * v97 - *(float *)&v148 * v96;
      plane.a = v100;
      v101 = v100 * v100 + v145 * v145 + v147 * v147;
      if ( v101 == 0.0 )
      {
        v102 = 0.0;
      }
      else
      {
        v103 = 1.0 / sqrt(v101);
        plane.a = v103 * v100;
        plane.b = v145 * v103;
        plane.c = v147 * v103;
        v102 = v103 * v101;
      }
      if ( v106 | v105 )
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
          goto LABEL_101;
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
          goto LABEL_101;
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
        goto LABEL_101;
      }
      if ( COERCE_FLOAT(LODWORD(plane.a) & 0x7FFFFFFF) == 1.0 )
      {
        if ( plane.b != 0.0 || plane.c != 0.0 )
        {
          plane.c = 0.0;
LABEL_100:
          plane.b = 0.0;
        }
      }
      else if ( COERCE_FLOAT(LODWORD(plane.b) & 0x7FFFFFFF) == 1.0 )
      {
        if ( plane.a != 0.0 || plane.c != 0.0 )
        {
          plane.c = 0.0;
          plane.a = 0.0;
        }
      }
      else if ( COERCE_FLOAT(LODWORD(plane.c) & 0x7FFFFFFF) == 1.0 && (plane.a != 0.0 || plane.b != 0.0) )
      {
        plane.a = 0.0;
        goto LABEL_100;
      }
LABEL_101:
      if ( v102 != 0.0 )
      {
        v107 = mesh->verts.list;
        v108 = plane.c * *(float *)((char *)&v107->xyz.z + v12);
        v109 = (char *)v107 + v12;
        v110 = 0;
        v111 = v108 + plane.b * *((float *)v109 + 1);
        v112 = plane.a * *(float *)v109;
        w.numPoints = 0;
        plane.d = -(v111 + v112);
        if ( w.allocedSize >= 1 )
          goto LABEL_105;
        if ( w.ReAllocate(&w, 1, 1) )
        {
          v110 = w.numPoints;
LABEL_105:
          v113 = *((_DWORD *)v109 + 1);
          v176 = *(float *)v109;
          v114 = *((_DWORD *)v109 + 2);
          v177 = v113;
          v115 = *((float *)v109 + 14);
          v178 = v114;
          v116 = *((float *)v109 + 15);
          v179 = v115;
          v180 = v116;
          v117 = &w.p[v110];
          v118 = v177;
          v117->x = v176;
          v119 = v178;
          LODWORD(v117->y) = v118;
          v120 = v179;
          LODWORD(v117->z) = v119;
          v121 = v180;
          v117->s = v120;
          v117->t = v121;
          ++w.numPoints;
        }
        v122 = (int *)((char *)mesh->verts.list + v150);
        if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
        {
          v123 = v122[2];
          v124 = v122[1];
          v186 = *v122;
          v125 = v122[14];
          v187 = v124;
          v126 = v122[15];
          v188 = v123;
          v190 = v126;
          v189 = v125;
          v127 = &w.p[w.numPoints];
          v128 = v187;
          LODWORD(v127->x) = v186;
          v129 = v188;
          LODWORD(v127->y) = v128;
          v130 = v189;
          LODWORD(v127->z) = v129;
          v131 = v190;
          LODWORD(v127->s) = v130;
          LODWORD(v127->t) = v131;
          ++w.numPoints;
        }
        v132 = (int *)((char *)mesh->verts.list + v95);
        if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
        {
          v133 = v132[1];
          v134 = v132[2];
          v196 = *v132;
          v135 = v132[14];
          v197 = v133;
          v136 = v132[15];
          v199 = v135;
          v198 = v134;
          v200 = v136;
          v137 = &w.p[w.numPoints];
          v138 = v197;
          LODWORD(v137->x) = v196;
          v139 = v198;
          LODWORD(v137->y) = v138;
          v140 = v199;
          LODWORD(v137->z) = v139;
          v141 = v200;
          LODWORD(v137->s) = v140;
          LODWORD(v137->t) = v141;
          ++w.numPoints;
        }
LABEL_112:
        idCollisionModelManagerLocal::PolygonFromWinding(v152, model, &w, &plane, material, -primitiveNum);
      }
      v142 = mesh->height - 1;
      if ( ++j >= v142 )
        goto LABEL_114;
    }
  }
LABEL_115:
  v207 = -1;
  w.p = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ConvertBrushSides(class idCollisionModelLocal *,class idMapBrush const *,int)
void __thiscall idCollisionModelManagerLocal::ConvertBrushSides(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        const idMapBrush *mapBrush,
        int primitiveNum)
{
  const idMapBrush *v4; // edi
  int num; // esi
  int v6; // eax
  void *v7; // esp
  idPlane *v8; // eax
  int v9; // ecx
  float *p_b; // esi
  idPlane *p_plane; // eax
  const idMaterial **v12; // ecx
  unsigned __int8 v14; // c2
  unsigned __int8 v15; // c3
  bool v16; // cc
  float v17; // esi
  idMapBrushSide *v18; // ebx
  const idMaterial *v19; // eax
  double v20; // st7
  double v21; // st6
  double v22; // st5
  int v23; // edi
  idPlane *v24; // esi
  double v25; // st7
  double v26; // st6
  double v27; // st5
  int v28; // edx
  bool v29; // zf
  int v30; // eax
  double v31; // st7
  float X_4; // [esp+8h] [ebp-580h]
  idFixedWinding w; // [esp+18h] [ebp-570h] BYREF
  idVec4 textureVecs[2]; // [esp+528h] [ebp-60h] BYREF
  idVec3 normal; // [esp+548h] [ebp-40h] BYREF
  float v36; // [esp+554h] [ebp-34h]
  idPlane plane; // [esp+558h] [ebp-30h] BYREF
  idCollisionModelManagerLocal *v38; // [esp+568h] [ebp-20h]
  idPlane *planes; // [esp+56Ch] [ebp-1Ch]
  float v40; // [esp+570h] [ebp-18h]
  int i; // [esp+574h] [ebp-14h]
  const idMaterial *material; // [esp+578h] [ebp-10h]
  int v43; // [esp+584h] [ebp-4h]

  v38 = this;
  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v4 = mapBrush;
  num = mapBrush->sides.num;
  v6 = 16 * num + 18;
  LOBYTE(v6) = v6 & 0xFC;
  v43 = 0;
  v7 = alloca(v6);
  v8 = (idPlane *)((char *)&w.__vftable + 3);
  LOBYTE(v8) = ((unsigned __int8)&w.__vftable + 3) & 0xF0;
  v9 = 0;
  i = 0;
  planes = v8;
  if ( num > 0 )
  {
    p_b = &v8->b;
    while ( 1 )
    {
      p_plane = &mapBrush->sides.list[v9]->plane;
      v12 = (const idMaterial **)(p_b - 1);
      *(idPlane *)(p_b - 1) = *p_plane;
      if ( v15 | v14 )
      {
        if ( *p_b == 0.0 )
        {
          if ( p_b[1] <= 0.0 )
          {
            if ( *((_DWORD *)p_b + 1) != -1082130432 )
            {
              p_b[1] = -1.0;
              goto LABEL_36;
            }
          }
          else if ( *((_DWORD *)p_b + 1) != 1065353216 )
          {
            p_b[1] = 1.0;
            goto LABEL_36;
          }
          goto LABEL_38;
        }
        if ( p_b[1] == 0.0 )
        {
          if ( *p_b <= 0.0 )
          {
            if ( *(_DWORD *)p_b != -1082130432 )
            {
              *p_b = -1.0;
              goto LABEL_36;
            }
          }
          else if ( *(_DWORD *)p_b != 1065353216 )
          {
            *p_b = 1.0;
            goto LABEL_36;
          }
          goto LABEL_38;
        }
      }
      else if ( *p_b == 0.0 && p_b[1] == 0.0 )
      {
        if ( *(float *)v12 <= 0.0 )
        {
          if ( *v12 != (const idMaterial *)-1082130432 )
          {
            *v12 = (const idMaterial *)-1082130432;
            goto LABEL_36;
          }
        }
        else if ( *v12 != (const idMaterial *)1065353216 )
        {
          *v12 = (const idMaterial *)1065353216;
          goto LABEL_36;
        }
        goto LABEL_38;
      }
      material = *v12;
      material = (const idMaterial *)((unsigned int)material & 0x7FFFFFFF);
      if ( *(float *)&material == 1.0 )
      {
        if ( *p_b != 0.0 || p_b[1] != 0.0 )
        {
          p_b[1] = 0.0;
          goto LABEL_35;
        }
      }
      else
      {
        material = *(const idMaterial **)p_b;
        material = (const idMaterial *)((unsigned int)material & 0x7FFFFFFF);
        if ( *(float *)&material == 1.0 )
        {
          if ( *(float *)v12 != 0.0 || p_b[1] != 0.0 )
          {
            p_b[1] = 0.0;
            *v12 = 0;
            goto LABEL_36;
          }
        }
        else
        {
          material = *((const idMaterial **)p_b + 1);
          material = (const idMaterial *)((unsigned int)material & 0x7FFFFFFF);
          if ( *(float *)&material == 1.0 && (*(float *)v12 != 0.0 || *p_b != 0.0) )
          {
            *v12 = 0;
LABEL_35:
            *p_b = 0.0;
LABEL_36:
            v40 = p_b[2] - floor(p_b[2] + 0.5);
            HIBYTE(v40) &= ~0x80u;
            if ( v40 < 0.000099999997 )
              p_b[2] = floor(p_b[2] + 0.5);
          }
        }
      }
LABEL_38:
      v9 = i + 1;
      p_b += 4;
      v16 = ++i < mapBrush->sides.num;
      if ( !v16 )
      {
        v8 = planes;
        break;
      }
    }
  }
  v16 = mapBrush->sides.num <= 0;
  i = 0;
  if ( !v16 )
  {
    LODWORD(v17) = &v8->c;
    planes = (idPlane *)&v8->c;
    LODWORD(v40) = &v8->c;
    do
    {
      v18 = v4->sides.list[i];
      *(float *)&v19 = COERCE_FLOAT((int)declManager->FindMaterial(declManager, v18->material.data, 1));
      v29 = (v19->contentFlags & 0xFFCFFFFF) == 0;
      material = v19;
      if ( !v29 )
      {
        v20 = -*(float *)(LODWORD(v17) + 4);
        v21 = -*(float *)LODWORD(v17);
        v22 = -*(float *)(LODWORD(v17) - 4);
        normal.x = -*(float *)(LODWORD(v17) - 8);
        normal.y = v22;
        normal.z = v21;
        v36 = v20;
        X_4 = -v20;
        idWinding::BaseForPlane(&w, &normal, X_4);
        v23 = 0;
        if ( mapBrush->sides.num > 0 )
        {
          v24 = planes;
          do
          {
            if ( !w.numPoints )
              break;
            if ( i != v23 )
            {
              v25 = -v24->b;
              v26 = -v24->a;
              v27 = -v24[-1].d;
              plane.a = -v24[-1].c;
              plane.b = v27;
              plane.c = v26;
              plane.d = v25;
              idWinding::ClipInPlace(&w, &plane, 0.0, 0);
            }
            ++v23;
            ++v24;
          }
          while ( v23 < mapBrush->sides.num );
          v17 = v40;
        }
        idMapBrushSide::GetTextureVectors(v18, textureVecs);
        v28 = 0;
        v29 = w.numPoints == 0;
        if ( w.numPoints > 0 )
        {
          v30 = 0;
          do
          {
            v31 = textureVecs[0].z * w.p[v30].z;
            ++v28;
            ++v30;
            w.p[v30 - 1].s = v31
                           + textureVecs[0].y * w.p[v30 - 1].y
                           + textureVecs[0].x * w.p[v30 - 1].x
                           + textureVecs[0].w;
            w.p[v30 - 1].t = textureVecs[1].z * w.p[v30 - 1].z
                           + textureVecs[1].y * w.p[v30 - 1].y
                           + textureVecs[1].x * w.p[v30 - 1].x
                           + textureVecs[1].w;
          }
          while ( v28 < w.numPoints );
          v29 = w.numPoints == 0;
        }
        if ( !v29 )
          idCollisionModelManagerLocal::PolygonFromWinding(
            v38,
            model,
            &w,
            (const idPlane *)(LODWORD(v17) - 8),
            material,
            primitiveNum);
        v4 = mapBrush;
      }
      LODWORD(v17) += 16;
      v16 = ++i < v4->sides.num;
      v40 = v17;
    }
    while ( v16 );
  }
  v43 = -1;
  w.p = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
}

// FUNC: private: class idCollisionModelLocal * __thiscall idCollisionModelManagerLocal::LoadRenderModel(char const *)
idCollisionModelLocal *__thiscall idCollisionModelManagerLocal::LoadRenderModel(
        idCollisionModelManagerLocal *this,
        char *fileName)
{
  idCollisionModelManagerLocal *v2; // esi
  int v3; // ebp
  const char *v4; // eax
  float v5; // ebp
  int v6; // eax
  float y; // edx
  char *v8; // ecx
  char v9; // al
  idRenderModel *v10; // eax
  idRenderModel *v11; // ebx
  int v12; // edi
  int v13; // ebp
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  idCollisionModelLocal *Model; // eax
  idCollisionModelLocal *v18; // edi
  int granularity; // eax
  bool v20; // cc
  int j; // eax
  int size; // ecx
  int v23; // ecx
  idCollisionModelLocal **list; // ebp
  int k; // eax
  cm_node_t *v26; // eax
  rvRenderModelMD5R *v27; // eax
  int v28; // ebp
  int v29; // eax
  int v30; // ebx
  int numPoints; // ecx
  int *v32; // esi
  int v33; // eax
  int v34; // edx
  int v35; // eax
  int v36; // edx
  idVec5 *v37; // edx
  int v38; // ecx
  int v39; // eax
  int v40; // ecx
  int v41; // eax
  int *v42; // esi
  int v43; // ecx
  int v44; // edx
  int v45; // eax
  int v46; // ecx
  idVec5 *v47; // ecx
  int v48; // eax
  int v49; // edx
  int v50; // eax
  int v51; // edx
  int v52; // esi
  float v53; // ecx
  float v54; // edx
  float v55; // eax
  float v56; // ecx
  idVec5 *v57; // ecx
  float v58; // eax
  float z; // edx
  float x; // eax
  float v61; // edx
  bool collisionSurface; // [esp+2Bh] [ebp-5B5h]
  int i; // [esp+2Ch] [ebp-5B4h]
  int ia; // [esp+2Ch] [ebp-5B4h]
  int local_maxVertices; // [esp+30h] [ebp-5B0h]
  idBounds bounds; // [esp+38h] [ebp-5A8h] BYREF
  idPlane plane; // [esp+58h] [ebp-588h] BYREF
  int v70; // [esp+68h] [ebp-578h]
  int v71; // [esp+6Ch] [ebp-574h]
  int v72; // [esp+70h] [ebp-570h]
  int v73; // [esp+74h] [ebp-56Ch]
  int v74; // [esp+78h] [ebp-568h]
  idRenderModel *renderModel; // [esp+7Ch] [ebp-564h]
  int v76; // [esp+80h] [ebp-560h]
  int v77; // [esp+84h] [ebp-55Ch]
  int v78; // [esp+88h] [ebp-558h]
  int v79; // [esp+8Ch] [ebp-554h]
  int v80; // [esp+90h] [ebp-550h]
  idPlane v81; // [esp+94h] [ebp-54Ch]
  idStr extension; // [esp+A4h] [ebp-53Ch] BYREF
  idFixedWinding w; // [esp+C4h] [ebp-51Ch] BYREF
  int v84; // [esp+5DCh] [ebp-4h]

  v2 = this;
  v3 = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v84 = 1;
  extension.len = 0;
  extension.alloced = 20;
  extension.data = extension.baseBuffer;
  extension.baseBuffer[0] = 0;
  bounds.b[0].x = 0.0;
  LODWORD(bounds.b[0].z) = 20;
  LODWORD(bounds.b[0].y) = &bounds.b[1];
  LOBYTE(bounds.b[1].x) = 0;
  if ( fileName )
  {
    v4 = &fileName[strlen(fileName) + 1];
    LODWORD(v5) = v4 - (fileName + 1);
    v6 = v4 - fileName;
    if ( v6 > 20 )
      idStr::ReAllocate((idStr *)&bounds, v6, 1);
    y = bounds.b[0].y;
    v8 = fileName;
    do
    {
      v9 = *v8;
      *(_BYTE *)LODWORD(y) = *v8++;
      ++LODWORD(y);
    }
    while ( v9 );
    bounds.b[0].x = v5;
    v3 = 0;
  }
  LOBYTE(v84) = 2;
  idStr::ExtractFileExtension((idStr *)&bounds, &extension);
  LOBYTE(v84) = 1;
  idStr::FreeData((idStr *)&bounds);
  if ( !idStr::Icmp(extension.data, "ase") || !idStr::Icmp(extension.data, "lwo") || !idStr::Icmp(extension.data, "obj") )
  {
    if ( renderModelManager->CheckModel(renderModelManager, fileName) )
    {
      v10 = renderModelManager->FindModel(renderModelManager, fileName);
      v11 = v10;
      renderModel = v10;
      if ( v10 )
      {
        collisionSurface = 0;
        if ( v10->NumSurfaces(v10) > 0 )
        {
          while ( (v11->Surface(v11, v3)->shader->surfaceFlags & 0x40) == 0 )
          {
            if ( ++v3 >= v11->NumSurfaces(v11) )
              goto LABEL_18;
          }
          collisionSurface = 1;
        }
LABEL_18:
        v12 = 0;
        v13 = 0;
        i = 0;
        if ( v11->NumSurfaces(v11) <= 0 )
          goto LABEL_74;
        do
        {
          v14 = (int)v11->Surface(v11, v12);
          v15 = *(_DWORD *)(v14 + 4);
          if ( (*(_DWORD *)(v15 + 164) & 0xFFCFFFFF) != 0 && (!collisionSurface || (*(_BYTE *)(v15 + 168) & 0x40) != 0) )
          {
            v16 = *(_DWORD *)(v14 + 8);
            v13 += *(_DWORD *)(v16 + 36);
            i += *(_DWORD *)(v16 + 52);
          }
          ++v12;
        }
        while ( v12 < v11->NumSurfaces(v11) );
        local_maxVertices = v13;
        if ( !v13 || !i )
        {
LABEL_74:
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "No collision geometry on model %s\n",
            fileName);
          LOBYTE(v84) = 0;
          idStr::FreeData(&extension);
          w.p = 0;
          goto LABEL_75;
        }
        Model = idCollisionModelManagerLocal::FindModel(v2, fileName);
        v18 = Model;
        if ( Model )
        {
          idCollisionModelManagerLocal::FreeModelMemory(v2, Model);
        }
        else
        {
          v18 = idCollisionModelManagerLocal::AllocModel(v2);
          if ( !v2->models.list )
          {
            granularity = v2->models.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != v2->models.size )
              {
                v20 = granularity < v2->models.num;
                v2->models.size = granularity;
                if ( v20 )
                  v2->models.num = granularity;
                v2->models.list = (idCollisionModelLocal **)Memory::Allocate(4 * granularity);
                for ( j = 0; j < v2->models.num; ++j )
                  v2->models.list[j] = *(idCollisionModelLocal **)(4 * j);
              }
            }
            else
            {
              v2->models.list = 0;
              v2->models.num = 0;
              v2->models.size = 0;
            }
          }
          size = v2->models.size;
          if ( v2->models.num == size )
          {
            if ( !v2->models.granularity )
              v2->models.granularity = 16;
            v23 = v2->models.granularity + size - (v2->models.granularity + size) % v2->models.granularity;
            if ( v23 > 0 )
            {
              if ( v23 != v2->models.size )
              {
                v20 = v23 < v2->models.num;
                list = v2->models.list;
                v2->models.size = v23;
                if ( v20 )
                  v2->models.num = v23;
                v2->models.list = (idCollisionModelLocal **)Memory::Allocate(4 * v23);
                for ( k = 0; k < v2->models.num; ++k )
                  v2->models.list[k] = list[k];
                if ( list )
                  Memory::Free(list);
              }
            }
            else
            {
              if ( v2->models.list )
                Memory::Free(v2->models.list);
              v2->models.list = 0;
              v2->models.num = 0;
              v2->models.size = 0;
            }
            v13 = local_maxVertices;
          }
          v2->models.list[v2->models.num++] = v18;
        }
        idStr::operator=(&v18->name, fileName);
        v18->refCount = 0;
        v18->fileTime = v11->Timestamp(v11);
        v26 = idCollisionModelManagerLocal::AllocNode(v2, v18, 8);
        v26->planeType = -1;
        v18->node = v26;
        v18->maxVertices = v13;
        v18->numVertices = 0;
        v18->vertices = (cm_vertex_t *)Mem_ClearedAlloc(24 * v13, 8u);
        v18->maxEdges = i;
        v18->numEdges = 0;
        v18->edges = (cm_edge_t *)Mem_ClearedAlloc(36 * i, 8u);
        idCollisionModelManagerLocal::SetupHash(v2);
        idHashIndex::ResizeIndex(v2->cm_vertexHash, v18->maxVertices);
        idHashIndex::ResizeIndex(v2->cm_edgeHash, v18->maxEdges);
        idCollisionModelManagerLocal::ClearHash(v2, &bounds);
        v18->numPrimitives = 0;
        if ( v11->HasSeparateSilTraceMeshes(v11) )
        {
          v27 = (rvRenderModelMD5R *)__RTDynamicCast(
                                       v11,
                                       0,
                                       &idRenderModel `RTTI Type Descriptor',
                                       &rvRenderModelMD5R `RTTI Type Descriptor',
                                       0);
          rvRenderModelMD5R::GenerateCollisionModel(v27, v2, v18);
          goto LABEL_73;
        }
        ia = 0;
        if ( v11->NumSurfaces(v11) <= 0 )
        {
LABEL_73:
          v18->node = idCollisionModelManagerLocal::CreateAxialBSPTree(v2, v18, v18->node);
          v18->isConvex = 0;
          idCollisionModelManagerLocal::FinishModel(v2, v18, 0);
          idCollisionModelManagerLocal::ShutdownHash(v2);
          LOBYTE(v84) = 0;
          idStr::FreeData(&extension);
          v84 = -1;
          w.p = 0;
          w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
          Memory::Free(0);
          return v18;
        }
LABEL_55:
        v28 = (int)v11->Surface(v11, ia);
        v29 = *(_DWORD *)(v28 + 4);
        if ( (*(_DWORD *)(v29 + 164) & 0xFFCFFFFF) == 0 || collisionSurface && (*(_BYTE *)(v29 + 168) & 0x40) == 0 )
          goto LABEL_72;
        v30 = 0;
        if ( *(int *)(*(_DWORD *)(v28 + 8) + 52) <= 0 )
          goto LABEL_71;
        while ( 1 )
        {
          numPoints = 0;
          w.numPoints = 0;
          v32 = (int *)(*(_DWORD *)(*(_DWORD *)(v28 + 8) + 40)
                      + (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v28 + 8) + 56) + 4 * v30 + 8) << 6));
          if ( w.allocedSize < 1 )
          {
            if ( !w.ReAllocate(&w, 1, 1) )
              goto LABEL_63;
            numPoints = w.numPoints;
          }
          v33 = v32[1];
          v76 = *v32;
          v34 = v32[2];
          v77 = v33;
          v35 = v32[14];
          v78 = v34;
          v36 = v32[15];
          v79 = v35;
          v80 = v36;
          v37 = &w.p[numPoints];
          v38 = v77;
          LODWORD(v37->x) = v76;
          v39 = v78;
          LODWORD(v37->y) = v38;
          v40 = v79;
          LODWORD(v37->z) = v39;
          v41 = v80;
          LODWORD(v37->s) = v40;
          LODWORD(v37->t) = v41;
          ++w.numPoints;
LABEL_63:
          v42 = (int *)(*(_DWORD *)(*(_DWORD *)(v28 + 8) + 40)
                      + (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v28 + 8) + 56) + 4 * v30 + 4) << 6));
          if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
          {
            v43 = v42[1];
            v44 = v42[2];
            v70 = *v42;
            v45 = v42[14];
            v71 = v43;
            v46 = v42[15];
            v73 = v45;
            v72 = v44;
            v74 = v46;
            v47 = &w.p[w.numPoints];
            v48 = v71;
            LODWORD(v47->x) = v70;
            v49 = v72;
            LODWORD(v47->y) = v48;
            v50 = v73;
            LODWORD(v47->z) = v49;
            v51 = v74;
            LODWORD(v47->s) = v50;
            LODWORD(v47->t) = v51;
            ++w.numPoints;
          }
          v52 = *(_DWORD *)(*(_DWORD *)(v28 + 8) + 40)
              + (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v28 + 8) + 56) + 4 * v30) << 6);
          if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
          {
            v53 = *(float *)(v52 + 4);
            v54 = *(float *)(v52 + 8);
            bounds.b[0].x = *(float *)v52;
            v55 = *(float *)(v52 + 56);
            bounds.b[0].y = v53;
            v56 = *(float *)(v52 + 60);
            bounds.b[1].x = v55;
            bounds.b[0].z = v54;
            bounds.b[1].y = v56;
            v57 = &w.p[w.numPoints];
            v58 = bounds.b[0].y;
            v57->x = bounds.b[0].x;
            z = bounds.b[0].z;
            v57->y = v58;
            x = bounds.b[1].x;
            v57->z = z;
            v61 = bounds.b[1].y;
            v57->s = x;
            v57->t = v61;
            ++w.numPoints;
          }
          idWinding::GetPlane(&w, &plane);
          v81.a = -plane.a;
          v81.b = -plane.b;
          v81.c = -plane.c;
          v81.d = -plane.d;
          plane = v81;
          idCollisionModelManagerLocal::PolygonFromWinding(
            this,
            v18,
            &w,
            &plane,
            *(const idMaterial **)(v28 + 4),
            v18->numPrimitives);
          v30 += 3;
          if ( v30 >= *(_DWORD *)(*(_DWORD *)(v28 + 8) + 52) )
          {
            v2 = this;
LABEL_71:
            ++v18->numPrimitives;
            v11 = renderModel;
LABEL_72:
            if ( ++ia >= v11->NumSurfaces(v11) )
              goto LABEL_73;
            goto LABEL_55;
          }
        }
      }
    }
  }
  LOBYTE(v84) = 0;
  idStr::FreeData(&extension);
  w.p = 0;
LABEL_75:
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  v84 = -1;
  Memory::Free(0);
  return 0;
}

// FUNC: public: virtual class idCollisionModel * __thiscall idCollisionModelManagerLocal::LoadModel(char const *,char const *)
idCollisionModelLocal *__thiscall idCollisionModelManagerLocal::LoadModel(
        idCollisionModelManagerLocal *this,
        const char *mapName,
        char *modelName)
{
  const char *FullModelName; // eax
  const char *v5; // esi
  int v6; // ebp
  char *data; // edx
  char *v8; // ecx
  char v9; // al
  idCollisionModelLocal *Model; // eax
  idCollisionModelLocal *RenderModel; // esi
  int refCount; // eax
  idCollisionModelLocal *v13; // eax
  int v14; // eax
  int v15; // eax
  idStr name; // [esp+Ch] [ebp-2Ch] BYREF
  int v18; // [esp+34h] [ebp-4h]

  FullModelName = idCollisionModelManagerLocal::GetFullModelName(this, mapName, modelName);
  v5 = FullModelName;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  if ( FullModelName )
  {
    v6 = strlen(FullModelName);
    if ( v6 + 1 > 20 )
      idStr::ReAllocate(&name, v6 + 1, 1);
    data = name.data;
    v8 = (char *)v5;
    do
    {
      v9 = *v8;
      *data++ = *v8++;
    }
    while ( v9 );
    name.len = v6;
  }
  v18 = 0;
  Model = idCollisionModelManagerLocal::FindModel(this, name.data);
  RenderModel = Model;
  if ( Model && Model->fileTime != -1 )
  {
    if ( idCollisionModelManagerLocal::IsRenderModelName(this, Model->name.data) )
    {
      refCount = RenderModel->refCount;
      if ( refCount > 0 )
        RenderModel->refCount = refCount + 1;
    }
LABEL_27:
    v18 = -1;
    idStr::FreeData(&name);
    return RenderModel;
  }
  if ( idCollisionModelManagerLocal::LoadCollisionModelFile(this, name.data, 0) )
  {
    v13 = idCollisionModelManagerLocal::FindModel(this, name.data);
    RenderModel = v13;
    if ( v13 && v13->fileTime != -1 )
    {
      if ( idCollisionModelManagerLocal::IsRenderModelName(this, v13->name.data) )
      {
        v14 = RenderModel->refCount;
        if ( v14 > 0 )
          RenderModel->refCount = v14 + 1;
      }
      goto LABEL_27;
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idCollisionModelManagerLocal::LoadModel: collision file for '%s' contains different model",
      name.data);
  }
  RenderModel = idCollisionModelManagerLocal::LoadRenderModel(this, name.data);
  if ( RenderModel )
  {
    if ( idCollisionModelManagerLocal::IsRenderModelName(this, RenderModel->name.data) )
    {
      v15 = RenderModel->refCount;
      if ( v15 > 0 )
        RenderModel->refCount = v15 + 1;
    }
    if ( com_makingBuild.internalVar->integerValue )
      idCollisionModelManagerLocal::WriteCollisionModelsToFile(this, modelName, 0);
    goto LABEL_27;
  }
  v18 = -1;
  idStr::FreeData(&name);
  return 0;
}

// FUNC: private: class idCollisionModelLocal * __thiscall idCollisionModelManagerLocal::GenerateCollisionModel(class idRenderModel *,char const *)
idCollisionModelLocal *__thiscall idCollisionModelManagerLocal::GenerateCollisionModel(
        idCollisionModelManagerLocal *this,
        idRenderModel *renderModel,
        char *modelName)
{
  idCollisionModelManagerLocal *v3; // esi
  const char *v4; // eax
  float v5; // ebx
  int v6; // eax
  float y; // edx
  char *v8; // ecx
  char v9; // al
  idRenderModel *v10; // ebx
  int j; // edi
  int v12; // edi
  const modelSurface_s *v13; // eax
  const idMaterial *shader; // ecx
  srfTriangles_s *geometry; // eax
  idCollisionModelLocal *Model; // eax
  idCollisionModelLocal *v17; // edi
  idCollisionModelLocal *v18; // eax
  int granularity; // eax
  bool v20; // cc
  int k; // eax
  int size; // ecx
  int v23; // ecx
  idCollisionModelLocal **list; // ebp
  int m; // eax
  cm_node_t *v26; // eax
  idBounds *v27; // eax
  float v28; // edx
  float z; // ecx
  float x; // edx
  float v31; // ecx
  float v32; // edx
  rvRenderModelMD5R *v33; // eax
  int v34; // ebp
  int v35; // eax
  int v36; // ebx
  int numPoints; // ecx
  int *v38; // esi
  int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // edx
  idVec5 *v43; // edx
  int v44; // ecx
  int v45; // eax
  int v46; // ecx
  int v47; // eax
  int *v48; // esi
  int v49; // ecx
  int v50; // edx
  int v51; // eax
  int v52; // ecx
  idVec5 *v53; // ecx
  int v54; // eax
  int v55; // edx
  int v56; // eax
  int v57; // edx
  int v58; // esi
  float v59; // ecx
  float v60; // edx
  float v61; // eax
  float v62; // ecx
  idVec5 *v63; // ecx
  float v64; // eax
  float v65; // edx
  float v66; // eax
  float v67; // edx
  int v69; // [esp+10h] [ebp-5D4h]
  char v70; // [esp+2Bh] [ebp-5B9h]
  int i; // [esp+2Ch] [ebp-5B8h]
  int ia; // [esp+2Ch] [ebp-5B8h]
  int local_maxEdges; // [esp+30h] [ebp-5B4h]
  int local_maxVertices; // [esp+34h] [ebp-5B0h]
  idBounds bounds; // [esp+38h] [ebp-5ACh] BYREF
  idCollisionModelManagerLocal *v76; // [esp+58h] [ebp-58Ch]
  idPlane plane; // [esp+5Ch] [ebp-588h] BYREF
  idPlane v78; // [esp+6Ch] [ebp-578h]
  int v79; // [esp+7Ch] [ebp-568h]
  int v80; // [esp+80h] [ebp-564h]
  int v81; // [esp+84h] [ebp-560h]
  int v82; // [esp+88h] [ebp-55Ch]
  int v83; // [esp+8Ch] [ebp-558h]
  int v84; // [esp+90h] [ebp-554h] BYREF
  int v85; // [esp+94h] [ebp-550h]
  int v86; // [esp+98h] [ebp-54Ch]
  int v87; // [esp+9Ch] [ebp-548h]
  int v88; // [esp+A0h] [ebp-544h]
  idStr extension; // [esp+A8h] [ebp-53Ch] BYREF
  idFixedWinding w; // [esp+C8h] [ebp-51Ch] BYREF
  int v91; // [esp+5E0h] [ebp-4h]

  v3 = this;
  v76 = this;
  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  v91 = 1;
  extension.len = 0;
  extension.alloced = 20;
  extension.data = extension.baseBuffer;
  extension.baseBuffer[0] = 0;
  bounds.b[0].x = 0.0;
  LODWORD(bounds.b[0].z) = 20;
  LODWORD(bounds.b[0].y) = &bounds.b[1];
  LOBYTE(bounds.b[1].x) = 0;
  if ( modelName )
  {
    v4 = &modelName[strlen(modelName) + 1];
    LODWORD(v5) = v4 - (modelName + 1);
    v6 = v4 - modelName;
    if ( v6 > 20 )
      idStr::ReAllocate((idStr *)&bounds, v6, 1);
    y = bounds.b[0].y;
    v8 = modelName;
    do
    {
      v9 = *v8;
      *(_BYTE *)LODWORD(y) = *v8++;
      ++LODWORD(y);
    }
    while ( v9 );
    bounds.b[0].x = v5;
  }
  LOBYTE(v91) = 2;
  idStr::ExtractFileExtension((idStr *)&bounds, &extension);
  LOBYTE(v91) = 1;
  idStr::FreeData((idStr *)&bounds);
  if ( idStr::Icmp(extension.data, "ase") && idStr::Icmp(extension.data, "lwo") && idStr::Icmp(extension.data, "ma") )
    goto LABEL_72;
  v10 = renderModel;
  local_maxVertices = 0;
  local_maxEdges = 0;
  v70 = 0;
  for ( j = 0; j < renderModel->NumSurfaces(renderModel); ++j )
  {
    if ( (renderModel->Surface(renderModel, j)->shader->surfaceFlags & 0x40) != 0 )
      v70 = 1;
  }
  v12 = 0;
  if ( renderModel->NumSurfaces(renderModel) <= 0 )
    goto LABEL_72;
  do
  {
    v13 = renderModel->Surface(renderModel, v12);
    shader = v13->shader;
    if ( (shader->contentFlags & 0xFFCFFFFF) != 0 && (!v70 || (shader->surfaceFlags & 0x40) != 0) )
    {
      geometry = v13->geometry;
      local_maxVertices += geometry->numVerts;
      local_maxEdges += geometry->numIndexes;
    }
    ++v12;
  }
  while ( v12 < renderModel->NumSurfaces(renderModel) );
  if ( !local_maxVertices || !local_maxEdges )
  {
LABEL_72:
    LOBYTE(v91) = 0;
    idStr::FreeData(&extension);
    w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    w.p = 0;
    v91 = -1;
    Memory::Free(0);
    return 0;
  }
  else
  {
    Model = idCollisionModelManagerLocal::FindModel(v3, modelName);
    v17 = Model;
    if ( Model )
    {
      idCollisionModelManagerLocal::FreeModelMemory(v3, Model);
    }
    else
    {
      v18 = (idCollisionModelLocal *)Memory::Allocate(0xC8u);
      if ( v18 )
      {
        v18->__vftable = (idCollisionModelLocal_vtbl *)&idCollisionModelLocal::`vftable';
        v17 = v18;
        v18->name.len = 0;
        v18->name.alloced = 20;
        v18->name.data = v18->name.baseBuffer;
        v18->name.baseBuffer[0] = 0;
        i = (int)v18;
      }
      else
      {
        i = 0;
        v17 = 0;
      }
      idCollisionModelManagerLocal::ClearModel(v3, v17);
      if ( !v3->models.list )
      {
        granularity = v3->models.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != v3->models.size )
          {
            v20 = granularity < v3->models.num;
            v3->models.size = granularity;
            if ( v20 )
              v3->models.num = granularity;
            v3->models.list = (idCollisionModelLocal **)Memory::Allocate(4 * granularity);
            for ( k = 0; k < v3->models.num; ++k )
              v3->models.list[k] = *(idCollisionModelLocal **)(4 * k);
          }
        }
        else
        {
          v3->models.list = 0;
          v3->models.num = 0;
          v3->models.size = 0;
        }
      }
      size = v3->models.size;
      if ( v3->models.num == size )
      {
        if ( !v3->models.granularity )
          v3->models.granularity = 16;
        v23 = v3->models.granularity + size - (v3->models.granularity + size) % v3->models.granularity;
        if ( v23 > 0 )
        {
          if ( v23 != v3->models.size )
          {
            v20 = v23 < v3->models.num;
            list = v3->models.list;
            v3->models.size = v23;
            if ( v20 )
              v3->models.num = v23;
            v3->models.list = (idCollisionModelLocal **)Memory::Allocate(4 * v23);
            for ( m = 0; m < v3->models.num; ++m )
              v3->models.list[m] = list[m];
            if ( list )
              Memory::Free(list);
          }
        }
        else
        {
          if ( v3->models.list )
            Memory::Free(v3->models.list);
          v3->models.list = 0;
          v3->models.num = 0;
          v3->models.size = 0;
        }
      }
      v3->models.list[v3->models.num++] = (idCollisionModelLocal *)i;
    }
    idStr::operator=(&v17->name, modelName);
    v17->refCount = 0;
    v17->fileTime = renderModel->Timestamp(renderModel);
    v26 = idCollisionModelManagerLocal::AllocNode(v3, v17, 8);
    v26->planeType = -1;
    v17->node = v26;
    v17->maxVertices = local_maxVertices;
    v17->maxEdges = local_maxEdges;
    v17->numVertices = 0;
    v17->numEdges = 0;
    v27 = renderModel->Bounds(renderModel, &v84, 0);
    v28 = v27->b[0].y;
    bounds.b[0].x = v27->b[0].x;
    z = v27->b[0].z;
    bounds.b[0].y = v28;
    x = v27->b[1].x;
    bounds.b[0].z = z;
    v31 = v27->b[1].y;
    bounds.b[1].x = x;
    v32 = v27->b[1].z;
    v69 = 24 * v17->maxVertices;
    bounds.b[1].y = v31;
    bounds.b[1].z = v32;
    v17->vertices = (cm_vertex_t *)Mem_ClearedAlloc(v69, 8u);
    v17->edges = (cm_edge_t *)Mem_ClearedAlloc(36 * v17->maxEdges, 8u);
    idCollisionModelManagerLocal::SetupHash(v3);
    idHashIndex::ResizeIndex(v3->cm_vertexHash, v17->maxVertices);
    idHashIndex::ResizeIndex(v3->cm_edgeHash, v17->maxEdges);
    idCollisionModelManagerLocal::ClearHash(v3, &bounds);
    v17->numPrimitives = 0;
    if ( renderModel->HasSeparateSilTraceMeshes(renderModel) )
    {
      v33 = (rvRenderModelMD5R *)__RTDynamicCast(
                                   renderModel,
                                   0,
                                   &idRenderModel `RTTI Type Descriptor',
                                   &rvRenderModelMD5R `RTTI Type Descriptor',
                                   0);
      rvRenderModelMD5R::GenerateCollisionModel(v33, v3, v17);
      goto LABEL_71;
    }
    ia = 0;
    if ( renderModel->NumSurfaces(renderModel) > 0 )
    {
      do
      {
        v34 = (int)v10->Surface(v10, ia);
        v35 = *(_DWORD *)(v34 + 4);
        if ( (*(_DWORD *)(v35 + 164) & 0xFFCFFFFF) == 0 || v70 && (*(_BYTE *)(v35 + 168) & 0x40) == 0 )
          goto LABEL_70;
        v36 = 0;
        if ( *(int *)(*(_DWORD *)(v34 + 8) + 52) <= 0 )
          goto LABEL_69;
        do
        {
          numPoints = 0;
          w.numPoints = 0;
          v38 = (int *)(*(_DWORD *)(*(_DWORD *)(v34 + 8) + 40)
                      + (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v34 + 8) + 56) + 4 * v36 + 8) << 6));
          if ( w.allocedSize >= 1 )
            goto LABEL_60;
          if ( w.ReAllocate(&w, 1, 1) )
          {
            numPoints = w.numPoints;
LABEL_60:
            v39 = v38[1];
            v79 = *v38;
            v40 = v38[2];
            v80 = v39;
            v41 = v38[14];
            v81 = v40;
            v42 = v38[15];
            v82 = v41;
            v83 = v42;
            v43 = &w.p[numPoints];
            v44 = v80;
            LODWORD(v43->x) = v79;
            v45 = v81;
            LODWORD(v43->y) = v44;
            v46 = v82;
            LODWORD(v43->z) = v45;
            v47 = v83;
            LODWORD(v43->s) = v46;
            LODWORD(v43->t) = v47;
            ++w.numPoints;
          }
          v48 = (int *)(*(_DWORD *)(*(_DWORD *)(v34 + 8) + 40)
                      + (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v34 + 8) + 56) + 4 * v36 + 4) << 6));
          if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
          {
            v49 = v48[1];
            v50 = v48[2];
            v84 = *v48;
            v51 = v48[14];
            v85 = v49;
            v52 = v48[15];
            v87 = v51;
            v86 = v50;
            v88 = v52;
            v53 = &w.p[w.numPoints];
            v54 = v85;
            LODWORD(v53->x) = v84;
            v55 = v86;
            LODWORD(v53->y) = v54;
            v56 = v87;
            LODWORD(v53->z) = v55;
            v57 = v88;
            LODWORD(v53->s) = v56;
            LODWORD(v53->t) = v57;
            ++w.numPoints;
          }
          v58 = *(_DWORD *)(*(_DWORD *)(v34 + 8) + 40)
              + (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v34 + 8) + 56) + 4 * v36) << 6);
          if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
          {
            v59 = *(float *)(v58 + 4);
            v60 = *(float *)(v58 + 8);
            bounds.b[0].x = *(float *)v58;
            v61 = *(float *)(v58 + 56);
            bounds.b[0].y = v59;
            v62 = *(float *)(v58 + 60);
            bounds.b[1].x = v61;
            bounds.b[0].z = v60;
            bounds.b[1].y = v62;
            v63 = &w.p[w.numPoints];
            v64 = bounds.b[0].y;
            v63->x = bounds.b[0].x;
            v65 = bounds.b[0].z;
            v63->y = v64;
            v66 = bounds.b[1].x;
            v63->z = v65;
            v67 = bounds.b[1].y;
            v63->s = v66;
            v63->t = v67;
            ++w.numPoints;
          }
          idWinding::GetPlane(&w, &plane);
          v78.a = -plane.a;
          v78.b = -plane.b;
          v78.c = -plane.c;
          v78.d = -plane.d;
          plane = v78;
          idCollisionModelManagerLocal::PolygonFromWinding(
            v76,
            v17,
            &w,
            &plane,
            *(const idMaterial **)(v34 + 4),
            v17->numPrimitives);
          v36 += 3;
        }
        while ( v36 < *(_DWORD *)(*(_DWORD *)(v34 + 8) + 52) );
        v3 = v76;
LABEL_69:
        ++v17->numPrimitives;
        v10 = renderModel;
LABEL_70:
        ++ia;
      }
      while ( ia < v10->NumSurfaces(v10) );
    }
LABEL_71:
    v17->node = idCollisionModelManagerLocal::CreateAxialBSPTree(v3, v17, v17->node);
    v17->isConvex = 0;
    idCollisionModelManagerLocal::FinishModel(v3, v17, 0);
    idCollisionModelManagerLocal::ShutdownHash(v3);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "GenerateCollisonModel() - generated collision model: %s",
      v17->name.data);
    LOBYTE(v91) = 0;
    idStr::FreeData(&extension);
    v91 = -1;
    w.p = 0;
    w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(0);
    return v17;
  }
}

// FUNC: public: virtual class idCollisionModel * __thiscall idCollisionModelManagerLocal::ExtractCollisionModel(class idRenderModel *,char const *)
idCollisionModelLocal *__thiscall idCollisionModelManagerLocal::ExtractCollisionModel(
        idCollisionModelManagerLocal *this,
        idRenderModel *renderModel,
        const char *modelName)
{
  const char *FullModelName; // eax
  const char *v5; // esi
  int v6; // ebp
  char *data; // edx
  char *v8; // ecx
  char v9; // al
  idCollisionModelLocal *Model; // eax
  idCollisionModelLocal *CollisionModel; // esi
  int refCount; // eax
  idCollisionModelLocal *v13; // eax
  int v14; // eax
  int v15; // eax
  idStr name; // [esp+Ch] [ebp-2Ch] BYREF
  int v18; // [esp+34h] [ebp-4h]

  FullModelName = idCollisionModelManagerLocal::GetFullModelName(this, &entityFilter, modelName);
  v5 = FullModelName;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  if ( FullModelName )
  {
    v6 = strlen(FullModelName);
    if ( v6 + 1 > 20 )
      idStr::ReAllocate(&name, v6 + 1, 1);
    data = name.data;
    v8 = (char *)v5;
    do
    {
      v9 = *v8;
      *data++ = *v8++;
    }
    while ( v9 );
    name.len = v6;
  }
  v18 = 0;
  Model = idCollisionModelManagerLocal::FindModel(this, name.data);
  CollisionModel = Model;
  if ( Model && Model->fileTime != -1 )
  {
    if ( idCollisionModelManagerLocal::IsRenderModelName(this, Model->name.data) )
    {
      refCount = CollisionModel->refCount;
      if ( refCount > 0 )
        CollisionModel->refCount = refCount + 1;
    }
LABEL_27:
    v18 = -1;
    idStr::FreeData(&name);
    return CollisionModel;
  }
  if ( idCollisionModelManagerLocal::LoadCollisionModelFile(this, name.data, 0) )
  {
    v13 = idCollisionModelManagerLocal::FindModel(this, name.data);
    CollisionModel = v13;
    if ( v13 && v13->fileTime != -1 )
    {
      if ( idCollisionModelManagerLocal::IsRenderModelName(this, v13->name.data) )
      {
        v14 = CollisionModel->refCount;
        if ( v14 > 0 )
          CollisionModel->refCount = v14 + 1;
      }
      goto LABEL_27;
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idCollisionModelManagerLocal::LoadModel: collision file for '%s' contains different model",
      name.data);
  }
  CollisionModel = idCollisionModelManagerLocal::GenerateCollisionModel(this, renderModel, name.data);
  if ( CollisionModel )
  {
    if ( idCollisionModelManagerLocal::IsRenderModelName(this, CollisionModel->name.data) )
    {
      v15 = CollisionModel->refCount;
      if ( v15 > 0 )
        CollisionModel->refCount = v15 + 1;
    }
    if ( com_makingBuild.internalVar->integerValue )
      idCollisionModelManagerLocal::WriteCollisionModelsToFile(this, name.data, 0);
    goto LABEL_27;
  }
  v18 = -1;
  idStr::FreeData(&name);
  return 0;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ConvertPatch(class idCollisionModelLocal *,class idMapPatch const *,int)
void __thiscall idCollisionModelManagerLocal::ConvertPatch(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        const idMapPatch *patch,
        const idMaterial *primitiveNum)
{
  const idMaterial *v4; // edi
  idSurface_Patch *v5; // esi
  int *list; // eax
  surfaceEdge_s *v7; // eax
  int *v8; // eax
  idDrawVert *v9; // eax

  v4 = declManager->FindMaterial(declManager, patch->material.data, 1);
  if ( (v4->contentFlags & 0xFFCFFFFF) != 0 )
  {
    v5 = (idSurface_Patch *)Memory::Allocate(0x54u);
    if ( v5 )
    {
      v5->verts.granularity = 16;
      v5->verts.list = 0;
      v5->verts.num = 0;
      v5->verts.size = 0;
      v5->indexes.granularity = 16;
      v5->indexes.list = 0;
      v5->indexes.num = 0;
      v5->indexes.size = 0;
      v5->edges.granularity = 16;
      v5->edges.list = 0;
      v5->edges.num = 0;
      v5->edges.size = 0;
      v5->edgeIndexes.granularity = 16;
      v5->edgeIndexes.list = 0;
      v5->edgeIndexes.num = 0;
      v5->edgeIndexes.size = 0;
      idSurface::operator=(v5, &patch->idSurface_Patch);
      v5->width = patch->width;
      v5->height = patch->height;
      v5->maxWidth = patch->maxWidth;
      v5->maxHeight = patch->maxHeight;
      v5->expanded = patch->expanded;
    }
    else
    {
      v5 = 0;
    }
    if ( patch->explicitSubdivisions )
      idSurface_Patch::SubdivideExplicit(v5, patch->horzSubdivisions, patch->vertSubdivisions, 0, 1);
    else
      idSurface_Patch::Subdivide(v5, 24.0, 24.0, -1.0, 0);
    idCollisionModelManagerLocal::CreatePatchPolygons(this, model, v5, v4, (int)primitiveNum);
    if ( v5 )
    {
      list = v5->edgeIndexes.list;
      if ( list )
        Memory::Free(list);
      v5->edgeIndexes.list = 0;
      v5->edgeIndexes.num = 0;
      v5->edgeIndexes.size = 0;
      v7 = v5->edges.list;
      if ( v7 )
        Memory::Free(v7);
      v5->edges.list = 0;
      v5->edges.num = 0;
      v5->edges.size = 0;
      v8 = v5->indexes.list;
      if ( v8 )
        Memory::Free(v8);
      v5->indexes.list = 0;
      v5->indexes.num = 0;
      v5->indexes.size = 0;
      v9 = v5->verts.list;
      if ( v9 )
        Memory::Free(v9);
      v5->verts.list = 0;
      v5->verts.num = 0;
      v5->verts.size = 0;
      Memory::Free(v5);
    }
  }
}

// FUNC: private: class idCollisionModelLocal * __thiscall idCollisionModelManagerLocal::CollisionModelForMapEntity(class idMapFile const *,class idMapEntity const *)
idCollisionModelLocal *__thiscall idCollisionModelManagerLocal::CollisionModelForMapEntity(
        idCollisionModelManagerLocal *this,
        const idMapFile *mapFile,
        idMapEntity *mapEnt)
{
  idMapEntity *v4; // edi
  bool v5; // cc
  const idKeyValue *Key; // eax
  const idPoolStr *value; // edi
  unsigned int len; // ebp
  int v10; // eax
  const idKeyValue *v11; // eax
  const idPoolStr *v12; // edi
  unsigned int v13; // ebp
  int v14; // eax
  char *FullModelName; // eax
  idCollisionModelLocal *Model; // eax
  idCollisionModelLocal *v17; // ebp
  int granularity; // eax
  int i; // eax
  int size; // ecx
  int num; // esi
  int v22; // ecx
  idCollisionModelLocal **list; // edi
  int j; // eax
  int v25; // esi
  cm_edge_t *v26; // eax
  int maxVertices; // edx
  int k; // esi
  const idMapBrush *v29; // eax
  cm_node_t *node; // ecx
  cm_brushRef_t *brushes; // eax
  int v32; // esi
  int m; // esi
  const idMapPatch *v34; // eax
  int type; // ecx
  idBounds bounds; // [esp+Ch] [ebp-44h] BYREF
  idStr name; // [esp+24h] [ebp-2Ch] BYREF
  int v38; // [esp+4Ch] [ebp-4h]
  const idMapFile *mapFilea; // [esp+54h] [ebp+4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v4 = mapEnt;
  v5 = mapEnt->primitives.num <= 0;
  v38 = 0;
  if ( v5 )
  {
    v38 = -1;
    idStr::FreeData(&name);
    return 0;
  }
  else
  {
    if ( mapFile )
    {
      Key = idDict::FindKey(&mapEnt->epairs, "model");
      if ( Key )
      {
        value = Key->value;
        len = value->len;
        v10 = value->len + 1;
        if ( v10 > name.alloced )
          idStr::ReAllocate(&name, v10, 0);
        qmemcpy(name.data, value->data, len);
        v4 = mapEnt;
        name.data[len] = 0;
        name.len = len;
      }
      else
      {
        idStr::operator=(&name, (char *)&entityFilter);
      }
      if ( !*name.data )
      {
        v11 = idDict::FindKey(&v4->epairs, "name");
        if ( v11 )
        {
          v12 = v11->value;
          v13 = v12->len;
          v14 = v12->len + 1;
          if ( v14 > name.alloced )
            idStr::ReAllocate(&name, v14, 0);
          qmemcpy(name.data, v12->data, v13);
          v4 = mapEnt;
          name.data[v13] = 0;
          name.len = v13;
        }
        else
        {
          idStr::operator=(&name, (char *)&entityFilter);
        }
        if ( !*name.data )
        {
          if ( v4 == *mapFile->entities.list )
            idStr::operator=(&name, "worldMap");
          else
            idStr::operator=(&name, "unnamed inline model");
        }
      }
      FullModelName = (char *)idCollisionModelManagerLocal::GetFullModelName(this, mapFile->name.data, name.data);
      idStr::operator=(&name, FullModelName);
      Model = idCollisionModelManagerLocal::FindModel(this, name.data);
      v17 = Model;
      if ( Model )
      {
        idCollisionModelManagerLocal::FreeModelMemory(this, Model);
        v17->fileTime = mapFile->geometryCRC;
      }
      else
      {
        v17 = idCollisionModelManagerLocal::AllocModel(this);
        if ( !this->models.list )
        {
          granularity = this->models.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->models.size )
            {
              v5 = granularity < this->models.num;
              this->models.size = granularity;
              if ( v5 )
                this->models.num = granularity;
              this->models.list = (idCollisionModelLocal **)Memory::Allocate(4 * granularity);
              for ( i = 0; i < this->models.num; ++i )
                this->models.list[i] = *(idCollisionModelLocal **)(4 * i);
            }
          }
          else
          {
            this->models.list = 0;
            this->models.num = 0;
            this->models.size = 0;
          }
        }
        size = this->models.size;
        num = this->models.num;
        if ( num == size )
        {
          if ( !this->models.granularity )
            this->models.granularity = 16;
          v22 = this->models.granularity + size - (this->models.granularity + size) % this->models.granularity;
          if ( v22 > 0 )
          {
            if ( v22 != this->models.size )
            {
              list = this->models.list;
              this->models.size = v22;
              if ( v22 < num )
                this->models.num = v22;
              this->models.list = (idCollisionModelLocal **)Memory::Allocate(4 * v22);
              for ( j = 0; j < this->models.num; ++j )
                this->models.list[j] = list[j];
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( this->models.list )
              Memory::Free(this->models.list);
            this->models.list = 0;
            this->models.num = 0;
            this->models.size = 0;
          }
        }
        this->models.list[this->models.num++] = v17;
        v17->fileTime = mapFile->geometryCRC;
      }
    }
    else
    {
      v17 = idCollisionModelManagerLocal::AllocModel(this);
    }
    v25 = name.len;
    mapFilea = (const idMapFile *)name.len;
    if ( name.len + 1 > v17->name.alloced )
      idStr::ReAllocate(&v17->name, name.len + 1, 0);
    qmemcpy(v17->name.data, name.data, v25);
    *((_BYTE *)&mapFilea->version + (unsigned int)v17->name.data) = 0;
    v17->name.len = (int)mapFilea;
    v17->refCount = 0;
    v17->isConvex = 0;
    v17->node = idCollisionModelManagerLocal::AllocNode(this, v17, 8);
    CM_EstimateVertsAndEdges(&v17->maxVertices, &v17->maxEdges, mapEnt);
    v17->numVertices = 0;
    v17->numEdges = 0;
    v17->vertices = (cm_vertex_t *)Mem_ClearedAlloc(24 * v17->maxVertices, 8u);
    v26 = (cm_edge_t *)Mem_ClearedAlloc(36 * v17->maxEdges, 8u);
    maxVertices = v17->maxVertices;
    v17->edges = v26;
    idHashIndex::ResizeIndex(this->cm_vertexHash, maxVertices);
    idHashIndex::ResizeIndex(this->cm_edgeHash, v17->maxEdges);
    for ( k = 0; k < mapEnt->primitives.num; ++k )
    {
      v29 = (const idMapBrush *)mapEnt->primitives.list[k];
      if ( !v29->type )
        idCollisionModelManagerLocal::ConvertBrush(this, v17, v29, k);
    }
    node = v17->node;
    brushes = node->brushes;
    v32 = 0;
    if ( !brushes )
      goto LABEL_55;
    do
    {
      brushes = brushes->next;
      ++v32;
    }
    while ( brushes );
    if ( v32 > 4 )
      v17->node = idCollisionModelManagerLocal::CreateAxialBSPTree(this, v17, v17->node);
    else
LABEL_55:
      node->planeType = -1;
    if ( v32 )
    {
      CM_GetNodeBounds(&bounds, v17->node);
    }
    else
    {
      bounds.b[0].x = -256.0;
      bounds.b[0].y = -256.0;
      bounds.b[0].z = -256.0;
      bounds.b[1].x = 256.0;
      bounds.b[1].y = 256.0;
      bounds.b[1].z = 256.0;
    }
    idCollisionModelManagerLocal::ClearHash(this, &bounds);
    for ( m = 0; m < mapEnt->primitives.num; ++m )
    {
      v34 = (const idMapPatch *)mapEnt->primitives.list[m];
      type = v34->type;
      if ( type == 1 )
      {
        idCollisionModelManagerLocal::ConvertPatch(this, v17, v34, (const idMaterial *)m);
      }
      else if ( !type )
      {
        idCollisionModelManagerLocal::ConvertBrushSides(this, v17, (const idMapBrush *)v34, m);
      }
    }
    v17->numPrimitives = mapEnt->primitives.num;
    idCollisionModelManagerLocal::FinishModel(this, v17, 1);
    v38 = -1;
    idStr::FreeData(&name);
    return v17;
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::BuildModels(class idMapFile const *,bool)
void __thiscall idCollisionModelManagerLocal::BuildModels(
        idCollisionModelManagerLocal *this,
        const idMapFile *mapFile,
        bool forceReload)
{
  int i; // ebp
  int v5; // edi
  long double v6; // st7
  idTimer timer; // [esp+14h] [ebp-ECh] BYREF
  idCollisionModelLocal model; // [esp+2Ch] [ebp-D4h] BYREF
  int v9; // [esp+FCh] [ebp-4h]

  timer.clockTicks = 0.0;
  timer.state = TS_STARTED;
  timer.start = idLib::sys->GetClockTicks(idLib::sys);
  session->PacifierUpdate(session);
  if ( forceReload
    || !idCollisionModelManagerLocal::LoadCollisionModelFile(this, mapFile->name.data, mapFile->geometryCRC) )
  {
    if ( !mapFile->entities.num )
      return;
    if ( !idCollisionModelManagerLocal::LoadProcBSP(this, mapFile->name.data, mapFile->geometryCRC) )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
        common.type,
        "Failed to load .PROC file for %s",
        mapFile->name.data);
      return;
    }
    for ( i = 0; i < mapFile->entities.num; ++i )
      idCollisionModelManagerLocal::CollisionModelForMapEntity(this, mapFile, mapFile->entities.list[i]);
    Mem_Free(this->procNodes);
    this->procNodes = 0;
    idCollisionModelManagerLocal::WriteCollisionModelsToFile(this, mapFile->name.data, mapFile->geometryCRC);
  }
  session->PacifierUpdate(session);
  timer.clockTicks = idLib::sys->GetClockTicks(idLib::sys) - timer.start + timer.clockTicks;
  if ( idTimer::base < 0.0 )
    idTimer::InitBaseClockTicks(&timer);
  if ( timer.clockTicks > idTimer::base )
    timer.clockTicks = timer.clockTicks - idTimer::base;
  timer.state = TS_STOPPED;
  model.__vftable = (idCollisionModelLocal_vtbl *)&idCollisionModelLocal::`vftable';
  model.name.len = 0;
  model.name.alloced = 20;
  model.name.data = model.name.baseBuffer;
  model.name.baseBuffer[0] = 0;
  v9 = 0;
  idCollisionModelManagerLocal::AccumulateModelInfo(this, &model);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "collision data:\n");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6i models\n",
    this->models.num);
  idCollisionModelManagerLocal::PrintModelInfo(this, &model);
  v5 = *(_DWORD *)common.type;
  v6 = idLib::sys->ClockTicksPerSecond(idLib::sys);
  (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(
    common.type,
    "%.0f msec to load collision data.\n",
    timer.clockTicks / (v6 * 0.001));
  v9 = 1;
  idStr::FreeData(&model.name);
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::LoadMap(class idMapFile const *,bool)
void __thiscall idCollisionModelManagerLocal::LoadMap(
        idCollisionModelManagerLocal *this,
        const idMapFile *mapFile,
        bool forceReload)
{
  char *FullModelName; // eax
  idCollisionModelLocal *Model; // eax
  idStr name; // [esp+Ch] [ebp-2Ch] BYREF
  int v7; // [esp+34h] [ebp-4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v7 = 0;
  if ( !mapFile )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idCollisionModelManagerLocal::LoadMap: NULL mapFile");
  FullModelName = (char *)idCollisionModelManagerLocal::GetFullModelName(this, mapFile->name.data, "worldMap");
  idStr::operator=(&name, FullModelName);
  Model = idCollisionModelManagerLocal::FindModel(this, name.data);
  if ( !Model || Model->fileTime == -1 || forceReload )
  {
    idCollisionModelManagerLocal::SetupHash(this);
    idCollisionModelManagerLocal::BuildModels(this, mapFile, forceReload);
    idCollisionModelManagerLocal::ShutdownHash(this);
  }
  this->loaded = 1;
  idCollisionModelManagerLocal::AddToMapModelReferenceCounts(this, mapFile->name.data, 1);
  v7 = -1;
  idStr::FreeData(&name);
}
