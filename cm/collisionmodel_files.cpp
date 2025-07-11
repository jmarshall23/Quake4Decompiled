
// FUNC: private: void __thiscall idCollisionModelManagerLocal::WriteNodes(class idFile *,struct cm_node_t *)
void __thiscall idCollisionModelManagerLocal::WriteNodes(
        idCollisionModelManagerLocal *this,
        idFile *fp,
        cm_node_t *node)
{
  cm_node_t *v3; // esi

  v3 = node;
  fp->WriteFloatString(fp, "\t( %d %f )\n", node->planeType, node->planeDist);
  if ( node->planeType != -1 )
  {
    do
    {
      idCollisionModelManagerLocal::WriteNodes(this, fp, v3->children[0]);
      v3 = v3->children[1];
      fp->WriteFloatString(fp, "\t( %d %f )\n", v3->planeType, v3->planeDist);
    }
    while ( v3->planeType != -1 );
  }
}

// FUNC: private: struct cm_node_t * __thiscall idCollisionModelManagerLocal::ParseNodes(class Lexer *,class idCollisionModelLocal *,struct cm_node_t *)
cm_node_t *__thiscall idCollisionModelManagerLocal::ParseNodes(
        idCollisionModelManagerLocal *this,
        Lexer *src,
        idCollisionModelLocal *model,
        cm_node_t *parent)
{
  int v5; // ecx
  cm_node_t *v6; // esi

  v5 = (++model->numNodes >= 8) - 1;
  LOBYTE(v5) = v5 & 8;
  v6 = idCollisionModelManagerLocal::AllocNode(this, model, v5 + 256);
  v6->brushes = 0;
  v6->polygons = 0;
  v6->parent = parent;
  Lexer::ExpectTokenString(src, "(");
  v6->planeType = Lexer::ParseInt(src);
  v6->planeDist = Lexer::ParseFloat(src, 0);
  Lexer::ExpectTokenString(src, ")");
  if ( v6->planeType != -1 )
  {
    v6->children[0] = idCollisionModelManagerLocal::ParseNodes(this, src, model, v6);
    v6->children[1] = idCollisionModelManagerLocal::ParseNodes(this, src, model, v6);
  }
  return v6;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::WritePolygons(class idFile *,struct cm_node_t *)
void __thiscall idCollisionModelManagerLocal::WritePolygons(
        idCollisionModelManagerLocal *this,
        idFile *fp,
        cm_node_t *node)
{
  cm_node_t *i; // ebx
  cm_polygonRef_t *polygons; // ecx
  cm_polygon_t *p; // esi
  int checkCount; // eax
  int j; // ebx
  idFile_vtbl *v8; // ebx
  int v9; // eax
  int numEdges; // [esp+1Ch] [ebp-1Ch]
  cm_polygonRef_t *pref; // [esp+30h] [ebp-8h]

  for ( i = node; ; node = i )
  {
    polygons = i->polygons;
    for ( pref = polygons; polygons; pref = polygons )
    {
      p = polygons->p;
      checkCount = this->checkCount;
      if ( polygons->p->checkcount != checkCount )
      {
        numEdges = p->numEdges;
        p->checkcount = checkCount;
        fp->WriteFloatString(fp, "\t%d (", numEdges);
        for ( j = 0; j < p->numEdges; ++j )
          fp->WriteFloatString(fp, " %d", p->edges[j]);
        fp->WriteFloatString(fp, " ) ( %f %f %f ) %f", p->plane.a, p->plane.b, p->plane.c, -p->plane.d);
        fp->WriteFloatString(fp, " ( %f %f %f )", p->bounds.b[0].x, p->bounds.b[0].y, p->bounds.b[0].z);
        fp->WriteFloatString(fp, " ( %f %f %f )", p->bounds.b[1].x, p->bounds.b[1].y, p->bounds.b[1].z);
        v8 = fp->__vftable;
        v9 = (int)p->material->base->GetName(p->material->base);
        v8->WriteFloatString(fp, " \"%s\"", v9);
        fp->WriteFloatString(fp, " ( %f %f )", p->texBounds[0].x, p->texBounds[0].y);
        fp->WriteFloatString(fp, " ( %f %f )", p->texBounds[1].x, p->texBounds[1].y);
        fp->WriteFloatString(fp, " ( %f %f )", p->texBounds[2].x, p->texBounds[2].y);
        fp->WriteFloatString(fp, " %d", p->primitiveNum);
        fp->WriteFloatString(fp, "\n");
        polygons = pref;
        i = node;
      }
      polygons = polygons->next;
    }
    if ( i->planeType == -1 )
      break;
    idCollisionModelManagerLocal::WritePolygons(this, fp, i->children[0]);
    i = i->children[1];
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::WriteBrushes(class idFile *,struct cm_node_t *)
void __thiscall idCollisionModelManagerLocal::WriteBrushes(
        idCollisionModelManagerLocal *this,
        idFile *fp,
        cm_node_t *node)
{
  cm_node_t *i; // ebx
  cm_brushRef_t *brushes; // ecx
  cm_brush_t *b; // esi
  int checkCount; // eax
  int v7; // ebx
  idFile_vtbl *v8; // ebx
  const char *v9; // eax
  int numPlanes; // [esp+1Ch] [ebp-1Ch]
  int v11; // [esp+2Ch] [ebp-Ch]
  cm_brushRef_t *bref; // [esp+34h] [ebp-4h]

  for ( i = node; ; node = i )
  {
    brushes = i->brushes;
    for ( bref = brushes; brushes; bref = brushes )
    {
      b = brushes->b;
      checkCount = this->checkCount;
      if ( brushes->b->checkcount != checkCount )
      {
        numPlanes = b->numPlanes;
        b->checkcount = checkCount;
        fp->WriteFloatString(fp, "\t%d {\n", numPlanes);
        v7 = 0;
        if ( b->numPlanes > 0 )
        {
          v11 = 0;
          do
          {
            fp->WriteFloatString(
              fp,
              "\t\t( %f %f %f ) %f\n",
              b->planes[v11].a,
              b->planes[v11].b,
              b->planes[v11].c,
              -b->planes[v11].d);
            ++v11;
            ++v7;
          }
          while ( v7 < b->numPlanes );
        }
        fp->WriteFloatString(fp, "\t} ( %f %f %f )", b->bounds.b[0].x, b->bounds.b[0].y, b->bounds.b[0].z);
        fp->WriteFloatString(fp, " ( %f %f %f )", b->bounds.b[1].x, b->bounds.b[1].y, b->bounds.b[1].z);
        v8 = fp->__vftable;
        v9 = idCollisionModelManagerLocal::StringFromContents(this, b->contents);
        v8->WriteFloatString(fp, " \"%s\"", v9);
        fp->WriteFloatString(fp, " %d\n", b->primitiveNum);
        brushes = bref;
        i = node;
      }
      brushes = brushes->next;
    }
    if ( i->planeType == -1 )
      break;
    idCollisionModelManagerLocal::WriteBrushes(this, fp, i->children[0]);
    i = i->children[1];
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ParseVertices(class Lexer *,class idCollisionModelLocal *)
void __thiscall idCollisionModelManagerLocal::ParseVertices(
        idCollisionModelManagerLocal *this,
        Lexer *src,
        idCollisionModelLocal *model)
{
  int v3; // eax
  cm_vertex_t *v4; // eax
  int v5; // ebx
  bool v6; // cc
  int v7; // edi

  Lexer::ExpectTokenString(src, "{");
  v3 = Lexer::ParseInt(src);
  model->numVertices = v3;
  model->maxVertices = v3;
  v4 = (cm_vertex_t *)Mem_Alloc(24 * v3, 8u);
  v5 = 0;
  v6 = model->numVertices <= 0;
  model->vertices = v4;
  if ( !v6 )
  {
    v7 = 0;
    do
    {
      Lexer::Parse1DMatrix(src, 3, &model->vertices[v7].p.x);
      model->vertices[v7].side = 0;
      model->vertices[v7].sideSet = 0;
      model->vertices[v7].checkcount = 0;
      ++v5;
      ++v7;
    }
    while ( v5 < model->numVertices );
  }
  Lexer::ExpectTokenString(src, "}");
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ParseEdges(class Lexer *,class idCollisionModelLocal *)
void __thiscall idCollisionModelManagerLocal::ParseEdges(
        idCollisionModelManagerLocal *this,
        Lexer *src,
        idCollisionModelLocal *model)
{
  int v3; // eax
  cm_edge_t *v4; // eax
  int v5; // ebp
  bool v6; // cc
  int v7; // edi
  cm_edge_t *edges; // eax
  int p_normal; // eax

  Lexer::ExpectTokenString(src, "{");
  v3 = Lexer::ParseInt(src);
  model->numEdges = v3;
  model->maxEdges = v3;
  v4 = (cm_edge_t *)Mem_Alloc(36 * v3, 8u);
  v5 = 0;
  v6 = model->numEdges <= 0;
  model->edges = v4;
  if ( !v6 )
  {
    v7 = 0;
    do
    {
      Lexer::ExpectTokenString(src, "(");
      model->edges[v7].vertexNum[0] = Lexer::ParseInt(src);
      model->edges[v7].vertexNum[1] = Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, ")");
      model->edges[v7].side = 0;
      model->edges[v7].sideSet = 0;
      model->edges[v7].internal = Lexer::ParseInt(src);
      model->edges[v7].numUsers = Lexer::ParseInt(src);
      edges = model->edges;
      edges[v7].normal.x = vec3_origin.x;
      p_normal = (int)&edges[v7].normal;
      *(float *)(p_normal + 4) = vec3_origin.y;
      *(float *)(p_normal + 8) = vec3_origin.z;
      model->edges[v7].checkcount = 0;
      model->numInternalEdges += model->edges[v7].internal;
      ++v5;
      ++v7;
    }
    while ( v5 < model->numEdges );
  }
  Lexer::ExpectTokenString(src, "}");
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ParsePolygons(class Lexer *,class idCollisionModelLocal *)
void __thiscall idCollisionModelManagerLocal::ParsePolygons(
        idCollisionModelManagerLocal *this,
        Lexer *src,
        idCollisionModelLocal *model)
{
  int v3; // eax
  idCollisionModelLocal *v4; // esi
  int v5; // eax
  int v6; // ebp
  cm_polygon_t *v7; // esi
  int i; // ebp
  const idMaterial *v9; // eax
  idVec3 normal; // [esp+Ch] [ebp-68h] BYREF
  idToken token; // [esp+18h] [ebp-5Ch] BYREF
  int v13; // [esp+70h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v13 = 0;
  v3 = Lexer::ParseInt(src);
  v4 = model;
  model->maxPolygons = v3;
  model->numPolygons = 0;
  model->polygons = (cm_polygon_t *)Mem_Alloc16(88 * v3, 8u);
  v5 = Lexer::ParseInt(src);
  model->maxPolygonEdges = v5;
  model->numPolygonEdges = 0;
  model->polygonEdges = (int *)Mem_Alloc16(4 * v5, 8u);
  Lexer::ExpectTokenString(src, "{");
  if ( !Lexer::CheckTokenString(src, "}") )
  {
    while ( 1 )
    {
      v6 = Lexer::ParseInt(src);
      v7 = idCollisionModelManagerLocal::AllocPolygon(this, v4, v6);
      v7->numEdges = v6;
      Lexer::ExpectTokenString(src, "(");
      for ( i = 0; i < v7->numEdges; ++i )
        v7->edges[i] = Lexer::ParseInt(src);
      Lexer::ExpectTokenString(src, ")");
      Lexer::Parse1DMatrix(src, 3, &normal.x);
      *(idVec3 *)&v7->plane.a = normal;
      v7->plane.d = -Lexer::ParseFloat(src, 0);
      Lexer::Parse1DMatrix(src, 3, (float *)v7);
      Lexer::Parse1DMatrix(src, 3, &v7->bounds.b[1].x);
      Lexer::ExpectTokenType(src, 1, 0, &token);
      v9 = declManager->FindMaterial(declManager, token.data, 1);
      v7->material = v9;
      v7->contents = v9->contentFlags;
      v7->texBounds[0].y = 0.0;
      v7->texBounds[0].x = 0.0;
      v7->texBounds[1].y = 0.0;
      v7->texBounds[1].x = 0.0;
      v7->texBounds[2].y = 0.0;
      v7->texBounds[2].x = 0.0;
      if ( Lexer::ReadToken(src, &token) )
      {
        if ( idStr::Cmp(token.data, "(") )
        {
          Lexer::UnreadToken(src, &token);
        }
        else
        {
          Lexer::UnreadToken(src, &token);
          Lexer::Parse1DMatrix(src, 2, &v7->texBounds[0].x);
          Lexer::Parse1DMatrix(src, 2, &v7->texBounds[1].x);
          Lexer::Parse1DMatrix(src, 2, &v7->texBounds[2].x);
          v7->primitiveNum = Lexer::ParseInt(src);
        }
      }
      v7->checkcount = 0;
      idCollisionModelManagerLocal::R_FilterPolygonIntoTree(this, model, model->node, 0, v7);
      if ( Lexer::CheckTokenString(src, "}") )
        break;
      v4 = model;
    }
  }
  v13 = -1;
  idStr::FreeData(&token);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::ParseBrushes(class Lexer *,class idCollisionModelLocal *)
void __thiscall idCollisionModelManagerLocal::ParseBrushes(
        idCollisionModelManagerLocal *this,
        Lexer *src,
        idCollisionModelLocal *model)
{
  int v3; // eax
  idCollisionModelLocal *v4; // ebp
  int v5; // eax
  int v6; // ebx
  cm_brush_t *v7; // esi
  int v8; // ebx
  int v9; // ebp
  idVec3 normal; // [esp+Ch] [ebp-68h] BYREF
  idToken token; // [esp+18h] [ebp-5Ch] BYREF
  int v13; // [esp+70h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v13 = 0;
  v3 = Lexer::ParseInt(src);
  v4 = model;
  model->maxBrushes = v3;
  model->numBrushes = 0;
  model->brushes = (cm_brush_t *)Mem_Alloc16(48 * v3, 8u);
  v5 = Lexer::ParseInt(src);
  model->maxBrushPlanes = v5;
  model->numBrushPlanes = 0;
  model->brushPlanes = (idPlane *)Mem_Alloc16(16 * v5, 8u);
  Lexer::ExpectTokenString(src, "{");
  while ( !Lexer::CheckTokenString(src, "}") )
  {
    v6 = Lexer::ParseInt(src);
    v7 = idCollisionModelManagerLocal::AllocBrush(this, v4, v6);
    v7->numPlanes = v6;
    Lexer::ExpectTokenString(src, "{");
    v8 = 0;
    if ( v7->numPlanes > 0 )
    {
      v9 = 0;
      do
      {
        Lexer::Parse1DMatrix(src, 3, &normal.x);
        *(idVec3 *)&v7->planes[v9].a = normal;
        v7->planes[v9].d = -Lexer::ParseFloat(src, 0);
        ++v8;
        ++v9;
      }
      while ( v8 < v7->numPlanes );
      v4 = model;
    }
    Lexer::ExpectTokenString(src, "}");
    Lexer::Parse1DMatrix(src, 3, (float *)v7);
    Lexer::Parse1DMatrix(src, 3, &v7->bounds.b[1].x);
    Lexer::ReadToken(src, &token);
    if ( token.type == 3 )
    {
      if ( (token.subtype & 0x10000) == 0 )
        idToken::NumberValue(&token);
      v7->contents = token.intvalue;
    }
    else
    {
      v7->contents = idCollisionModelManagerLocal::ContentsFromString(this, token.data);
      v7->primitiveNum = Lexer::ParseInt(src);
    }
    v7->checkcount = 0;
    v7->material = 0;
    idCollisionModelManagerLocal::R_FilterBrushIntoTree(this, v4, v4->node, 0, v7);
  }
  v13 = -1;
  idStr::FreeData(&token);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::WriteCollisionModel(class idFile *,class idCollisionModelLocal *)
void __thiscall idCollisionModelManagerLocal::WriteCollisionModel(
        idCollisionModelManagerLocal *this,
        idFile *fp,
        idCollisionModelLocal *model)
{
  int len; // esi
  int v4; // ebx
  char *data; // ecx
  char *v6; // edx
  char v7; // al
  int v8; // eax
  int v9; // ebx
  int v10; // [esp+28h] [ebp-38h]
  int v11; // [esp+28h] [ebp-38h]
  idStr name; // [esp+30h] [ebp-30h] BYREF
  int v14; // [esp+5Ch] [ebp-4h]

  len = model->name.len;
  v4 = 0;
  name.data = name.baseBuffer;
  name.len = 0;
  name.alloced = 20;
  name.baseBuffer[0] = 0;
  if ( len + 1 > 20 )
    idStr::ReAllocate(&name, len + 1, 1);
  data = model->name.data;
  v6 = name.data;
  do
  {
    v7 = *data;
    *v6++ = *data++;
  }
  while ( v7 );
  name.len = len;
  v14 = 0;
  if ( !idStr::Icmpn(name.data, "maps/", 5) )
  {
    v8 = idStr::Last(&name, 47);
    if ( v8 != -1 )
      idStr::operator=(&name, &name.data[v8 + 1]);
  }
  fp->WriteFloatString(fp, "collisionModel \"%s\" %d {\n", name.data, model->numPrimitives);
  fp->WriteFloatString(fp, "\tvertices { /* numVertices = */ %d\n", model->numVertices);
  if ( model->numVertices > 0 )
  {
    v10 = 0;
    do
    {
      fp->WriteFloatString(
        fp,
        "\t/* %d */ ( %f %f %f )\n",
        v4,
        model->vertices[v10].p.x,
        model->vertices[v10].p.y,
        model->vertices[v10].p.z);
      ++v10;
      ++v4;
    }
    while ( v4 < model->numVertices );
  }
  fp->WriteFloatString(fp, "\t}\n");
  fp->WriteFloatString(fp, "\tedges { /* numEdges = */ %d\n", model->numEdges);
  v9 = 0;
  if ( model->numEdges > 0 )
  {
    v11 = 0;
    do
    {
      fp->WriteFloatString(
        fp,
        "\t/* %d */ ( %d %d ) %d %d\n",
        v9,
        model->edges[v11].vertexNum[0],
        model->edges[v11].vertexNum[1],
        model->edges[v11].internal,
        model->edges[v11].numUsers);
      ++v11;
      ++v9;
    }
    while ( v9 < model->numEdges );
  }
  fp->WriteFloatString(fp, "\t}\n");
  fp->WriteFloatString(fp, "\tnodes {\n");
  idCollisionModelManagerLocal::WriteNodes(this, fp, model->node);
  fp->WriteFloatString(fp, "\t}\n");
  ++this->checkCount;
  fp->WriteFloatString(
    fp,
    "\tpolygons /* numPolygons = */ %d /* numPolygonEdges = */ %d {\n",
    model->numPolygons,
    model->numPolygonEdges);
  ++this->checkCount;
  idCollisionModelManagerLocal::WritePolygons(this, fp, model->node);
  fp->WriteFloatString(fp, "\t}\n");
  ++this->checkCount;
  fp->WriteFloatString(
    fp,
    "\tbrushes /* numBrushes = */ %d /* numBrushPlanes = */ %d {\n",
    model->numBrushes,
    model->numBrushPlanes);
  ++this->checkCount;
  idCollisionModelManagerLocal::WriteBrushes(this, fp, model->node);
  fp->WriteFloatString(fp, "\t}\n");
  fp->WriteFloatString(fp, "}\n");
  v14 = -1;
  idStr::FreeData(&name);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::WriteCollisionModelsToFile(char const *,unsigned int)
void __thiscall idCollisionModelManagerLocal::WriteCollisionModelsToFile(
        idCollisionModelManagerLocal *this,
        char *filename,
        unsigned int mapFileCRC)
{
  idFile *v4; // eax
  idFile *v5; // ebp
  int v6; // eax
  char v7; // cl
  char *v8; // edx
  int i; // esi
  idCollisionModelLocal *v10; // eax
  idStr mask; // [esp+14h] [ebp-4Ch] BYREF
  idStr name; // [esp+34h] [ebp-2Ch] BYREF
  int v13; // [esp+5Ch] [ebp-4h]
  int filenamea; // [esp+64h] [ebp+4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v13 = 1;
  mask.len = 0;
  mask.alloced = 20;
  mask.data = mask.baseBuffer;
  mask.baseBuffer[0] = 0;
  idStr::operator=(&name, filename);
  idStr::SetFileExtension(&name, "cm");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "writing %s\n", name.data);
  v4 = fileSystem->OpenFileWrite(fileSystem, name.data, "fs_devpath", 0);
  v5 = v4;
  if ( v4 )
  {
    v4->WriteFloatString(v4, "%s \"%s\"\n\n", "CM", "3");
    v5->WriteFloatString(v5, "%u\n\n", mapFileCRC);
    idStr::operator=(&mask, filename);
    if ( !idCollisionModelManagerLocal::IsRenderModelName(this, mask.data) )
    {
      idStr::StripFileExtension(&mask);
      filenamea = mask.len + 1;
      if ( mask.len + 2 > mask.alloced )
        idStr::ReAllocate(&mask, mask.len + 2, 1);
      v6 = 0;
      v7 = 47;
      do
      {
        v8 = &mask.data[v6++];
        v8[mask.len] = v7;
        v7 = b[v6];
      }
      while ( v7 );
      mask.len = filenamea;
      mask.data[filenamea] = 0;
    }
    for ( i = 0; i < this->models.num; ++i )
    {
      v10 = this->models.list[i];
      if ( v10->fileTime != -1 && !idStr::Icmpn(v10->name.data, mask.data, mask.len) )
        idCollisionModelManagerLocal::WriteCollisionModel(this, v5, this->models.list[i]);
    }
    fileSystem->CloseFile(fileSystem, v5);
    if ( cvarSystem->GetCVarInteger(cvarSystem, "com_BinaryWrite") )
      idLexer::WriteBinaryFile(name.data);
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idCollisionModelManagerLocal::WriteCollisionModelsToFile: Error opening file %s",
      name.data);
  }
  LOBYTE(v13) = 0;
  idStr::FreeData(&mask);
  v13 = -1;
  idStr::FreeData(&name);
}

// FUNC: public: virtual bool __thiscall idCollisionModelManagerLocal::WriteCollisionModelForMapEntity(class idMapEntity const *,char const *,bool)
char __thiscall idCollisionModelManagerLocal::WriteCollisionModelForMapEntity(
        idCollisionModelManagerLocal *this,
        const idMapEntity *mapEnt,
        char *filename,
        bool testTraceModel)
{
  idCollisionModelLocal *v5; // ebp
  idFile *v6; // eax
  idFile *v7; // esi
  idStr name; // [esp+18h] [ebp-B38h] BYREF
  idTraceModel trm; // [esp+38h] [ebp-B18h] BYREF
  int v11; // [esp+B4Ch] [ebp-4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v11 = 0;
  idCollisionModelManagerLocal::SetupHash(this);
  v5 = idCollisionModelManagerLocal::CollisionModelForMapEntity(this, 0, mapEnt);
  idStr::operator=(&v5->name, filename);
  idStr::operator=(&name, filename);
  idStr::SetFileExtension(&name, "cm");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "writing %s\n", name.data);
  v6 = fileSystem->OpenFileWrite(fileSystem, name.data, "fs_devpath", 0);
  v7 = v6;
  if ( v6 )
  {
    v6->WriteFloatString(v6, "%s \"%s\"\n\n", "CM", "3");
    v7->WriteFloatString(v7, "%u\n\n", 0);
    idCollisionModelManagerLocal::WriteCollisionModel(this, v7, v5);
    fileSystem->CloseFile(fileSystem, v7);
    if ( cvarSystem->GetCVarInteger(cvarSystem, "com_BinaryWrite") )
      idLexer::WriteBinaryFile(name.data);
    if ( testTraceModel )
    {
      trm.type = TRM_INVALID;
      trm.numPolys = 0;
      trm.numEdges = 0;
      trm.numVerts = 0;
      memset(&trm.bounds, 0, sizeof(trm.bounds));
      idCollisionModelManagerLocal::TrmFromModel(this, v5, &trm);
    }
    this->FreeModel(this, v5);
    v11 = -1;
    idStr::FreeData(&name);
    return 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idCollisionModelManagerLocal::WriteCollisionModelForMapEntity: Error opening file %s\n",
      name.data);
    this->FreeModel(this, v5);
    v11 = -1;
    idStr::FreeData(&name);
    return 0;
  }
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::ParseCollisionModel(class Lexer *,char const *,unsigned int)
char __thiscall idCollisionModelManagerLocal::ParseCollisionModel(
        idCollisionModelManagerLocal *this,
        Lexer *src,
        const char *fileName,
        int mapFileCRC)
{
  const char *v5; // eax
  int v6; // ebx
  int v7; // eax
  char *data; // edx
  const char *v9; // ecx
  char v10; // al
  const idStr *v11; // eax
  idStr *v12; // edi
  unsigned int len; // ebx
  int v14; // eax
  idCollisionModelLocal *Model; // eax
  idCollisionModelLocal *v16; // ebx
  int granularity; // eax
  bool v18; // cc
  int i; // eax
  int num; // esi
  int size; // ecx
  int v22; // ecx
  idCollisionModelLocal **list; // edi
  int j; // eax
  int v25; // esi
  unsigned int intvalue; // eax
  int v28; // [esp+8h] [ebp-C0h]
  idStr name; // [esp+Ch] [ebp-BCh] BYREF
  idToken token; // [esp+2Ch] [ebp-9Ch] BYREF
  idStr v31; // [esp+7Ch] [ebp-4Ch] BYREF
  idStr result; // [esp+9Ch] [ebp-2Ch] BYREF
  int v33; // [esp+C4h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v33 = 0;
  Lexer::ExpectTokenType(src, 1, 0, &token);
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  if ( fileName )
  {
    v5 = &fileName[strlen(fileName) + 1];
    v6 = v5 - (fileName + 1);
    v7 = v5 - fileName;
    if ( v7 > 20 )
      idStr::ReAllocate(&name, v7, 1);
    data = name.data;
    v9 = fileName;
    do
    {
      v10 = *v9;
      *data++ = *v9++;
    }
    while ( v10 );
    name.len = v6;
  }
  LOBYTE(v33) = 1;
  if ( !idStr::Icmpn(name.data, "maps/", 5) )
  {
    idStr::StripFileExtension(&name);
    v11 = operator+(&result, &name, "/");
    LOBYTE(v33) = 2;
    v12 = operator+(&v31, v11, &token);
    len = v12->len;
    v14 = v12->len + 1;
    LOBYTE(v33) = 3;
    if ( v14 > token.alloced )
      idStr::ReAllocate(&token, v14, 0);
    qmemcpy(token.data, v12->data, len);
    token.data[len] = 0;
    token.len = len;
    LOBYTE(v33) = 2;
    idStr::FreeData(&v31);
    LOBYTE(v33) = 1;
    idStr::FreeData(&result);
  }
  Model = idCollisionModelManagerLocal::FindModel(this, token.data);
  v16 = Model;
  if ( Model )
  {
    idCollisionModelManagerLocal::FreeModelMemory(this, Model);
  }
  else
  {
    v16 = idCollisionModelManagerLocal::AllocModel(this);
    if ( !this->models.list )
    {
      granularity = this->models.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->models.size )
        {
          v18 = granularity < this->models.num;
          this->models.size = granularity;
          if ( v18 )
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
    num = this->models.num;
    size = this->models.size;
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
    this->models.list[this->models.num++] = v16;
  }
  v25 = token.len;
  v28 = token.len;
  if ( token.len + 1 > v16->name.alloced )
    idStr::ReAllocate(&v16->name, token.len + 1, 0);
  qmemcpy(v16->name.data, token.data, v25);
  v16->name.data[v28] = 0;
  v16->name.len = v28;
  v16->fileTime = mapFileCRC;
  v16->refCount = 0;
  Lexer::ExpectTokenType(src, 3, 0, &token);
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
  v16->numPrimitives = intvalue;
  Lexer::ExpectTokenString(src, "{");
  while ( !Lexer::CheckTokenString(src, "}") )
  {
    Lexer::ReadToken(src, &token);
    if ( idStr::Cmp(token.data, "vertices") )
    {
      if ( idStr::Cmp(token.data, "edges") )
      {
        if ( idStr::Cmp(token.data, "nodes") )
        {
          if ( idStr::Cmp(token.data, "polygons") )
          {
            if ( idStr::Cmp(token.data, "brushes") )
              Lexer::Error(src, "ParseCollisionModel: bad token \"%s\"", token.data);
            else
              idCollisionModelManagerLocal::ParseBrushes(this, src, v16);
          }
          else
          {
            idCollisionModelManagerLocal::ParsePolygons(this, src, v16);
          }
        }
        else
        {
          Lexer::ExpectTokenString(src, "{");
          v16->node = idCollisionModelManagerLocal::ParseNodes(this, src, v16, 0);
          Lexer::ExpectTokenString(src, "}");
        }
      }
      else
      {
        idCollisionModelManagerLocal::ParseEdges(this, src, v16);
      }
    }
    else
    {
      idCollisionModelManagerLocal::ParseVertices(this, src, v16);
    }
  }
  ++this->checkCount;
  idCollisionModelManagerLocal::CalculateEdgeNormals(this, v16, v16->node);
  CM_GetNodeBounds(&v16->bounds, v16->node);
  v16->contents = CM_GetNodeContents(v16->node);
  v16->usedMemory = CM_GetModelMemory(v16);
  LOBYTE(v33) = 0;
  idStr::FreeData(&name);
  v33 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::LoadCollisionModelFile(char const *,unsigned int)
char __thiscall idCollisionModelManagerLocal::LoadCollisionModelFile(
        idCollisionModelManagerLocal *this,
        char *name,
        int mapFileCRC)
{
  Lexer *Lexer; // esi
  unsigned int intvalue; // eax
  bool v6; // zf
  idStr fileName; // [esp+10h] [ebp-7Ch] BYREF
  idToken token; // [esp+30h] [ebp-5Ch] BYREF
  int v10; // [esp+88h] [ebp-4h]

  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  token.floatvalue = 0.0;
  v10 = 1;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  idStr::operator=(&fileName, name);
  idStr::SetFileExtension(&fileName, "cm");
  Lexer = LexerFactory::MakeLexer(fileName.data, 40, 0);
  if ( !Lexer::IsLoaded(Lexer) )
    goto LABEL_27;
  if ( !Lexer::ExpectTokenString(Lexer, "CM") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "%s is not an CM file.",
      fileName.data);
LABEL_27:
    v6 = Lexer == 0;
LABEL_28:
    if ( !v6 )
    {
      Lexer::~Lexer(Lexer);
      Memory::Free(Lexer);
    }
    LOBYTE(v10) = 0;
    idStr::FreeData(&token);
    v10 = -1;
    idStr::FreeData(&fileName);
    return 0;
  }
  if ( !Lexer::ReadToken(Lexer, &token) || idStr::Cmp(token.data, "3") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "%s has version %s instead of %s",
      fileName.data,
      token.data,
      "3");
    goto LABEL_27;
  }
  if ( !Lexer::ExpectTokenType(Lexer, 3, 1, &token) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "%s has no map file CRC",
      fileName.data);
    goto LABEL_27;
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
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%s is out of date\n",
      fileName.data);
LABEL_16:
    v6 = Lexer == 0;
    goto LABEL_28;
  }
  while ( Lexer::ReadToken(Lexer, &token) )
  {
    if ( idStr::Cmp(token.data, "collisionModel") )
    {
      Lexer::Error(Lexer, "idCollisionModelManagerLocal::LoadCollisionModelFile: bad token \"%s\"", token.data);
    }
    else if ( !idCollisionModelManagerLocal::ParseCollisionModel(this, Lexer, name, mapFileCRC) )
    {
      goto LABEL_16;
    }
  }
  if ( Lexer )
  {
    Lexer::~Lexer(Lexer);
    Memory::Free(Lexer);
  }
  LOBYTE(v10) = 0;
  idStr::FreeData(&token);
  v10 = -1;
  idStr::FreeData(&fileName);
  return 1;
}
