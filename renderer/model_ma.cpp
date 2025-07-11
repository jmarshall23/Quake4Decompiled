
// FUNC: void __cdecl MA_ParseNodeHeader(class idParser &,struct maNodeHeader_t *)
void __cdecl MA_ParseNodeHeader(idParser *parser, maNodeHeader_t *header)
{
  char *v2; // eax
  int v3; // edx
  char v4; // cl
  char *data; // eax
  int v6; // edx
  char v7; // cl
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v9; // [esp+5Ch] [ebp-4h]

  token.floatvalue = 0.0;
  memset(header, 0, sizeof(maNodeHeader_t));
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v9 = 0;
  while ( idParser::ReadToken(parser, &token) )
  {
    if ( idStr::Icmp(token.data, "-") )
    {
      if ( !idStr::Icmp(token.data, ";") )
        break;
    }
    else
    {
      idParser::ReadToken(parser, &token);
      if ( idStr::Icmp(token.data, "n") )
      {
        if ( !idStr::Icmp(token.data, "p") )
        {
          idParser::ReadToken(parser, &token);
          data = token.data;
          v6 = (char *)header - token.data + 128;
          do
          {
            v7 = *data;
            data[v6] = *data;
            ++data;
          }
          while ( v7 );
        }
      }
      else
      {
        idParser::ReadToken(parser, &token);
        v2 = token.data;
        v3 = (char *)header - token.data;
        do
        {
          v4 = *v2;
          v2[v3] = *v2;
          ++v2;
        }
        while ( v4 );
      }
    }
  }
  v9 = -1;
  idStr::FreeData(&token);
}

// FUNC: bool __cdecl MA_ParseHeaderIndex(struct maAttribHeader_t *,int &,int &,char const *,char const *)
char __cdecl MA_ParseHeaderIndex(
        maAttribHeader_t *header,
        int *minIndex,
        int *maxIndex,
        char *headerType,
        const char *skipString)
{
  idToken token; // [esp+8h] [ebp-11Ch] BYREF
  idParser miniParse; // [esp+58h] [ebp-CCh] BYREF
  int v8; // [esp+120h] [ebp-4h]

  idParser::idParser(&miniParse);
  token.floatvalue = 0.0;
  v8 = 1;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  idParser::LoadMemory(&miniParse, header->name, strlen(header->name), headerType);
  if ( skipString )
    idParser::SkipUntilString(&miniParse, skipString);
  if ( idParser::SkipUntilString(&miniParse, "[") )
  {
    *minIndex = idParser::ParseInt(&miniParse);
    idParser::ReadToken(&miniParse, &token);
    if ( idStr::Icmp(token.data, "]") )
      *maxIndex = idParser::ParseInt(&miniParse);
    else
      *maxIndex = *minIndex;
    LOBYTE(v8) = 0;
    idStr::FreeData(&token);
    v8 = -1;
    idParser::~idParser(&miniParse);
    return 1;
  }
  else
  {
    LOBYTE(v8) = 0;
    idStr::FreeData(&token);
    v8 = -1;
    idParser::~idParser(&miniParse);
    return 0;
  }
}

// FUNC: bool __cdecl MA_ParseAttribHeader(class idParser &,struct maAttribHeader_t *)
char __cdecl MA_ParseAttribHeader(idParser *parser, maAttribHeader_t *header)
{
  char *data; // eax
  int v3; // edx
  char v4; // cl
  idToken token; // [esp+0h] [ebp-5Ch] BYREF
  int v7; // [esp+58h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  memset(header, 0, sizeof(maAttribHeader_t));
  v7 = 0;
  idParser::ReadToken(parser, &token);
  if ( !idStr::Icmp(token.data, "-") )
  {
    idParser::ReadToken(parser, &token);
    if ( !idStr::Icmp(token.data, "s") )
    {
      header->size = idParser::ParseInt(parser);
      idParser::ReadToken(parser, &token);
    }
  }
  data = token.data;
  v3 = (char *)header - token.data;
  do
  {
    v4 = *data;
    data[v3] = *data;
    ++data;
  }
  while ( v4 );
  v7 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: bool __cdecl MA_ReadVec3(class idParser &,class idVec3 &)
char __cdecl MA_ReadVec3(idParser *parser, idVec3 *vec)
{
  void *v2; // esp
  idLexer *scriptstack; // esi
  const char *data; // esi
  char *v5; // eax
  char *v6; // edx
  char v7; // cl
  idStr v9; // [esp+0h] [ebp-1060h] BYREF
  double v10; // [esp+38h] [ebp-1028h]
  char v11[2048]; // [esp+50h] [ebp-1010h] BYREF
  char pExceptionObject[2052]; // [esp+850h] [ebp-810h] BYREF
  int v13; // [esp+105Ch] [ebp-4h]

  v2 = alloca(4176);
  v10 = 0.0;
  v9.len = 0;
  v9.alloced = 20;
  v9.data = v9.baseBuffer;
  v9.baseBuffer[0] = 0;
  v13 = 0;
  if ( !idParser::SkipUntilString(parser, "double3") )
  {
    scriptstack = parser->scriptstack;
    if ( scriptstack )
      data = scriptstack->filename.data;
    else
      data = &entityFilter;
    v5 = va("Maya Loader '%s': Invalid Vec3", data);
    v6 = v11;
    do
    {
      v7 = *v5;
      *v6++ = *v5++;
    }
    while ( v7 );
    qmemcpy(pExceptionObject, v11, 0x800u);
    _CxxThrowException(pExceptionObject, &_TI1_AVidException__);
  }
  vec->x = idParser::ParseFloat(parser);
  vec->z = idParser::ParseFloat(parser);
  vec->y = idParser::ParseFloat(parser);
  v13 = -1;
  idStr::FreeData(&v9);
  return 1;
}

// FUNC: bool __cdecl MA_ParseVertex(class idParser &,struct maAttribHeader_t *)
char __cdecl MA_ParseVertex(idParser *parser, maAttribHeader_t *header)
{
  bool v2; // zf
  idVec3 **p_vertexes; // edi
  int size; // eax
  int v5; // esi
  int v6; // ebp
  int minIndex; // [esp+4h] [ebp-64h] BYREF
  int maxIndex; // [esp+8h] [ebp-60h] BYREF
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v11; // [esp+64h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v2 = maGlobal.currentObject->mesh.vertexes == 0;
  p_vertexes = &maGlobal.currentObject->mesh.vertexes;
  v11 = 0;
  if ( v2 )
  {
    size = header->size;
    maGlobal.currentObject->mesh.numVertexes = size;
    *p_vertexes = (idVec3 *)Mem_Alloc(12 * size, 0xEu);
  }
  if ( MA_ParseHeaderIndex(header, &minIndex, &maxIndex, "VertexHeader", 0) && minIndex <= maxIndex )
  {
    v5 = minIndex;
    v6 = maxIndex - minIndex + 1;
    do
    {
      (*p_vertexes)[v5].x = idParser::ParseFloat(parser);
      (*p_vertexes)[v5].z = idParser::ParseFloat(parser);
      (*p_vertexes)[v5++].y = -idParser::ParseFloat(parser);
      --v6;
    }
    while ( v6 );
  }
  v11 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: bool __cdecl MA_ParseVertexTransforms(class idParser &,struct maAttribHeader_t *)
char __cdecl MA_ParseVertexTransforms(idParser *parser, maAttribHeader_t *header)
{
  maMesh_t *p_mesh; // esi
  bool v3; // zf
  int size; // eax
  int v5; // ebp
  int j; // ebx
  int i; // [esp+8h] [ebp-B4h] BYREF
  int maxIndex; // [esp+Ch] [ebp-B0h] BYREF
  idToken token; // [esp+10h] [ebp-ACh] BYREF
  idToken tk2; // [esp+60h] [ebp-5Ch] BYREF
  int v12; // [esp+B8h] [ebp-4h]

  token.floatvalue = 0.0;
  p_mesh = &maGlobal.currentObject->mesh;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v3 = maGlobal.currentObject->mesh.vertTransforms == 0;
  v12 = 0;
  if ( v3 )
  {
    if ( !header->size )
      header->size = 1;
    size = header->size;
    p_mesh->numVertTransforms = size;
    p_mesh->vertTransforms = (idVec4 *)Mem_Alloc(16 * size, 0xEu);
    p_mesh->nextVertTransformIndex = 0;
  }
  if ( MA_ParseHeaderIndex(header, &i, &maxIndex, "VertexTransformHeader", 0) )
  {
    idParser::ReadToken(parser, &token);
    if ( idStr::Icmp(token.data, "-") )
    {
      idParser::UnreadToken(parser, &token);
    }
    else
    {
      tk2.floatvalue = 0.0;
      tk2.len = 0;
      tk2.alloced = 20;
      tk2.data = tk2.baseBuffer;
      tk2.baseBuffer[0] = 0;
      LOBYTE(v12) = 1;
      idParser::ReadToken(parser, &tk2);
      if ( idStr::Icmp(tk2.data, "type") )
      {
        idParser::UnreadToken(parser, &tk2);
        idParser::UnreadToken(parser, &token);
      }
      else
      {
        idParser::SkipUntilString(parser, "float3");
      }
      LOBYTE(v12) = 0;
      idStr::FreeData(&tk2);
    }
    v5 = i;
    for ( j = maxIndex; v5 <= j; i = v5 )
    {
      p_mesh->vertTransforms[p_mesh->nextVertTransformIndex].x = idParser::ParseFloat(parser);
      p_mesh->vertTransforms[p_mesh->nextVertTransformIndex].z = idParser::ParseFloat(parser);
      p_mesh->vertTransforms[p_mesh->nextVertTransformIndex].y = -idParser::ParseFloat(parser);
      ++v5;
      p_mesh->vertTransforms[p_mesh->nextVertTransformIndex++].w = (float)i;
    }
  }
  v12 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: bool __cdecl MA_ParseEdge(class idParser &,struct maAttribHeader_t *)
char __cdecl MA_ParseEdge(idParser *parser, maAttribHeader_t *header)
{
  bool v2; // zf
  idVec3 **p_edges; // edi
  int size; // eax
  int v5; // esi
  int v6; // ebp
  int minIndex; // [esp+4h] [ebp-64h] BYREF
  int maxIndex; // [esp+8h] [ebp-60h] BYREF
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v11; // [esp+64h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v2 = maGlobal.currentObject->mesh.edges == 0;
  p_edges = &maGlobal.currentObject->mesh.edges;
  v11 = 0;
  if ( v2 )
  {
    size = header->size;
    maGlobal.currentObject->mesh.numEdges = size;
    *p_edges = (idVec3 *)Mem_Alloc(12 * size, 0xEu);
  }
  if ( MA_ParseHeaderIndex(header, &minIndex, &maxIndex, "EdgeHeader", 0) && minIndex <= maxIndex )
  {
    v5 = minIndex;
    v6 = maxIndex - minIndex + 1;
    do
    {
      (*p_edges)[v5].x = idParser::ParseFloat(parser);
      (*p_edges)[v5].y = idParser::ParseFloat(parser);
      (*p_edges)[v5++].z = idParser::ParseFloat(parser);
      --v6;
    }
    while ( v6 );
  }
  v11 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: bool __cdecl MA_ParseNormal(class idParser &,struct maAttribHeader_t *)
char __cdecl MA_ParseNormal(idParser *parser, maAttribHeader_t *header)
{
  maMesh_t *p_mesh; // edi
  bool v3; // zf
  int size; // eax
  int v5; // esi
  int v6; // ebx
  idVec3 *normals; // ecx
  double z; // st7
  float *p_x; // ecx
  long double v10; // st4
  long double v11; // st7
  int maxIndex; // [esp+8h] [ebp-B4h] BYREF
  int minIndex; // [esp+Ch] [ebp-B0h] BYREF
  idToken token; // [esp+10h] [ebp-ACh] BYREF
  idToken tk2; // [esp+60h] [ebp-5Ch] BYREF
  int v17; // [esp+B8h] [ebp-4h]

  token.floatvalue = 0.0;
  p_mesh = &maGlobal.currentObject->mesh;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v3 = maGlobal.currentObject->mesh.normals == 0;
  v17 = 0;
  if ( v3 )
  {
    size = header->size;
    maGlobal.currentObject->mesh.numNormals = size;
    p_mesh->normals = (idVec3 *)Mem_Alloc(12 * size, 0xEu);
  }
  if ( MA_ParseHeaderIndex(header, &minIndex, &maxIndex, "NormalHeader", 0) )
  {
    idParser::ReadToken(parser, &token);
    if ( idStr::Icmp(token.data, "-") )
    {
      idParser::UnreadToken(parser, &token);
    }
    else
    {
      tk2.floatvalue = 0.0;
      tk2.len = 0;
      tk2.alloced = 20;
      tk2.data = tk2.baseBuffer;
      tk2.baseBuffer[0] = 0;
      LOBYTE(v17) = 1;
      idParser::ReadToken(parser, &tk2);
      if ( idStr::Icmp(tk2.data, "type") )
      {
        idParser::UnreadToken(parser, &tk2);
        idParser::UnreadToken(parser, &token);
      }
      else
      {
        idParser::SkipUntilString(parser, "float3");
      }
      LOBYTE(v17) = 0;
      idStr::FreeData(&tk2);
    }
    if ( minIndex <= maxIndex )
    {
      v5 = minIndex;
      v6 = maxIndex - minIndex + 1;
      do
      {
        p_mesh->normals[v5].x = idParser::ParseFloat(parser);
        p_mesh->normals[v5].z = idParser::ParseFloat(parser);
        p_mesh->normals[v5].y = -idParser::ParseFloat(parser);
        normals = p_mesh->normals;
        z = normals[v5].z;
        p_x = &normals[v5].x;
        v10 = *p_x * *p_x + p_x[1] * p_x[1] + z * z;
        if ( v10 != 0.0 )
        {
          v11 = 1.0 / sqrt(v10);
          *p_x = v11 * *p_x;
          p_x[1] = v11 * p_x[1];
          p_x[2] = v11 * p_x[2];
        }
        ++v5;
        --v6;
      }
      while ( v6 );
    }
    p_mesh->normalsParsed = 1;
    p_mesh->nextNormal = 0;
    v17 = -1;
    idStr::FreeData(&token);
  }
  else
  {
    v17 = -1;
    idStr::FreeData(&token);
  }
  return 1;
}

// FUNC: bool __cdecl MA_ParseFace(class idParser &,struct maAttribHeader_t *)
char __cdecl MA_ParseFace(idParser *parser, maAttribHeader_t *header)
{
  void *v2; // esp
  bool v3; // zf
  maFace_t **p_faces; // ebx
  int size; // ecx
  int v6; // edi
  int v7; // edi
  idLexer *v9; // esi
  const char *v10; // esi
  const char *v11; // eax
  const void *v12; // eax
  idLexer *v13; // esi
  const char *v14; // esi
  const char *v15; // eax
  const void *v16; // eax
  idLexer *v17; // esi
  const char *v18; // esi
  const char *v19; // eax
  const void *v20; // eax
  idLexer *scriptstack; // esi
  const char *data; // esi
  const char *v23; // eax
  const void *v24; // eax
  int minIndex; // [esp+0h] [ebp-1068h] BYREF
  int maxIndex; // [esp+4h] [ebp-1064h] BYREF
  idToken token; // [esp+8h] [ebp-1060h] BYREF
  char pExceptionObject[2048]; // [esp+58h] [ebp-1010h] BYREF
  idException v29; // [esp+858h] [ebp-810h] BYREF
  int v30; // [esp+1064h] [ebp-4h]

  v2 = alloca(4188);
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v3 = maGlobal.currentObject->mesh.faces == 0;
  p_faces = &maGlobal.currentObject->mesh.faces;
  v30 = 0;
  if ( v3 )
  {
    size = header->size;
    maGlobal.currentObject->mesh.numFaces = size;
    *p_faces = (maFace_t *)Mem_Alloc(84 * size, 0xEu);
  }
  if ( MA_ParseHeaderIndex(header, &minIndex, &maxIndex, "FaceHeader", 0) )
  {
    v6 = minIndex - 1;
    if ( idParser::ReadToken(parser, &token) )
    {
      v7 = v6;
      do
      {
        if ( !idStr::Icmp(token.data, "createNode")
          || !idStr::Icmp(token.data, "connectAttr")
          || !idStr::Icmp(token.data, "select") )
        {
          idParser::UnreadToken(parser, &token);
          break;
        }
        if ( idStr::Icmp(token.data, "f") )
        {
          if ( idStr::Icmp(token.data, "mu") )
          {
            if ( idStr::Icmp(token.data, "mf") )
            {
              if ( !idStr::Icmp(token.data, "fc") )
              {
                if ( idParser::ParseInt(parser) != 3 )
                {
                  scriptstack = parser->scriptstack;
                  if ( scriptstack )
                    data = scriptstack->filename.data;
                  else
                    data = &entityFilter;
                  v23 = va("Maya Loader '%s': Invalid vertex color.", data);
                  idException::idException(&v29, v23);
                  qmemcpy(pExceptionObject, v24, sizeof(pExceptionObject));
                  _CxxThrowException(pExceptionObject, &_TI1_AVidException__);
                }
                (*p_faces)[v7].vertexColors[0] = idParser::ParseInt(parser);
                (*p_faces)[v7].vertexColors[1] = idParser::ParseInt(parser);
                (*p_faces)[v7].vertexColors[2] = idParser::ParseInt(parser);
              }
              continue;
            }
            if ( idParser::ParseInt(parser) != 3 )
            {
              v17 = parser->scriptstack;
              if ( v17 )
                v18 = v17->filename.data;
              else
                v18 = &entityFilter;
              v19 = va("Maya Loader '%s': Invalid texture coordinates.", v18);
              idException::idException(&v29, v19);
              qmemcpy(pExceptionObject, v20, sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, &_TI1_AVidException__);
            }
          }
          else
          {
            idParser::ParseInt(parser);
            if ( idParser::ParseInt(parser) != 3 )
            {
              v13 = parser->scriptstack;
              if ( v13 )
                v14 = v13->filename.data;
              else
                v14 = &entityFilter;
              v15 = va("Maya Loader '%s': Invalid texture coordinates.", v14);
              idException::idException(&v29, v15);
              qmemcpy(pExceptionObject, v16, sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, &_TI1_AVidException__);
            }
          }
          (*p_faces)[v7].tVertexNum[0] = idParser::ParseInt(parser);
          (*p_faces)[v7].tVertexNum[1] = idParser::ParseInt(parser);
          (*p_faces)[v7].tVertexNum[2] = idParser::ParseInt(parser);
        }
        else
        {
          if ( idParser::ParseInt(parser) != 3 )
          {
            v9 = parser->scriptstack;
            if ( v9 )
              v10 = v9->filename.data;
            else
              v10 = &entityFilter;
            v11 = va("Maya Loader '%s': Face is not a triangle.", v10);
            idException::idException(&v29, v11);
            qmemcpy(pExceptionObject, v12, sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, &_TI1_AVidException__);
          }
          (*p_faces)[++v7].edge[0] = idParser::ParseInt(parser);
          (*p_faces)[v7].edge[1] = idParser::ParseInt(parser);
          (*p_faces)[v7].edge[2] = idParser::ParseInt(parser);
          (*p_faces)[v7].vertexColors[2] = -1;
          (*p_faces)[v7].vertexColors[1] = -1;
          (*p_faces)[v7].vertexColors[0] = -1;
        }
      }
      while ( idParser::ReadToken(parser, &token) );
    }
  }
  v30 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: bool __cdecl MA_ParseColor(class idParser &,struct maAttribHeader_t *)
char __cdecl MA_ParseColor(idParser *parser, maAttribHeader_t *header)
{
  bool v2; // zf
  unsigned __int8 **p_colors; // edi
  int size; // eax
  int v5; // esi
  int i; // ebp
  int minIndex; // [esp+4h] [ebp-64h] BYREF
  int maxIndex; // [esp+8h] [ebp-60h] BYREF
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v11; // [esp+64h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v2 = maGlobal.currentObject->mesh.colors == 0;
  p_colors = &maGlobal.currentObject->mesh.colors;
  v11 = 0;
  if ( v2 )
  {
    size = header->size;
    maGlobal.currentObject->mesh.numColors = size;
    *p_colors = (unsigned __int8 *)Mem_Alloc(4 * size, 0xEu);
  }
  if ( MA_ParseHeaderIndex(header, &minIndex, &maxIndex, "ColorHeader", 0) )
  {
    v5 = minIndex;
    for ( i = maxIndex; v5 <= i; ++v5 )
    {
      (*p_colors)[4 * v5] = (unsigned __int64)(idParser::ParseFloat(parser) * 255.0);
      (*p_colors)[4 * v5 + 1] = (unsigned __int64)(idParser::ParseFloat(parser) * 255.0);
      (*p_colors)[4 * v5 + 2] = (unsigned __int64)(idParser::ParseFloat(parser) * 255.0);
      (*p_colors)[4 * v5 + 3] = (unsigned __int64)(idParser::ParseFloat(parser) * 255.0);
    }
  }
  v11 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: bool __cdecl MA_ParseTVert(class idParser &,struct maAttribHeader_t *)
char __cdecl MA_ParseTVert(idParser *parser, maAttribHeader_t *header)
{
  maMesh_t *p_mesh; // ebp
  int size; // eax
  int v4; // esi
  int i; // ebx
  int maxIndex; // [esp+8h] [ebp-B4h] BYREF
  int minIndex; // [esp+Ch] [ebp-B0h] BYREF
  idToken token; // [esp+10h] [ebp-ACh] BYREF
  idToken tk2; // [esp+60h] [ebp-5Ch] BYREF
  int v11; // [esp+B8h] [ebp-4h]

  token.floatvalue = 0.0;
  p_mesh = &maGlobal.currentObject->mesh;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v11 = 0;
  if ( !strstr(header->name, "uvsn") )
  {
    if ( !p_mesh->tvertexes )
    {
      size = header->size;
      p_mesh->numTVertexes = size;
      p_mesh->tvertexes = (idVec2 *)Mem_Alloc(8 * size, 0xEu);
    }
    if ( MA_ParseHeaderIndex(header, &minIndex, &maxIndex, "TextureCoordHeader", "uvsp") )
    {
      idParser::ReadToken(parser, &token);
      if ( idStr::Icmp(token.data, "-") )
      {
        idParser::UnreadToken(parser, &token);
      }
      else
      {
        tk2.floatvalue = 0.0;
        tk2.len = 0;
        tk2.alloced = 20;
        tk2.data = tk2.baseBuffer;
        tk2.baseBuffer[0] = 0;
        LOBYTE(v11) = 1;
        idParser::ReadToken(parser, &tk2);
        if ( idStr::Icmp(tk2.data, "type") )
        {
          idParser::UnreadToken(parser, &tk2);
          idParser::UnreadToken(parser, &token);
        }
        else
        {
          idParser::SkipUntilString(parser, "float2");
        }
        LOBYTE(v11) = 0;
        idStr::FreeData(&tk2);
      }
      v4 = minIndex;
      for ( i = maxIndex; v4 <= i; p_mesh->tvertexes[v4 - 1].y = 1.0 - idParser::ParseFloat(parser) )
        p_mesh->tvertexes[v4++].x = idParser::ParseFloat(parser);
    }
  }
  v11 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: bool __cdecl MA_QuickIsVertShared(int,int)
char __cdecl MA_QuickIsVertShared(int faceIndex, int vertIndex)
{
  maFace_t *faces; // edx
  int v3; // edi
  maFace_t *i; // edx
  int v5; // eax
  idVec3 *v6; // ecx
  double v7; // st7
  int vertNum; // [esp+Ch] [ebp-4h]
  float vertIndexa; // [esp+18h] [ebp+8h]

  faces = maGlobal.currentObject->mesh.faces;
  vertNum = faces->vertexNum[14 * faceIndex + 7 * faceIndex + vertIndex];
  v3 = 0;
  for ( i = &faces[faceIndex]; ; i = (maFace_t *)((char *)i + 4) )
  {
    v5 = i->edge[0];
    if ( i->edge[0] < 0 )
    {
      vertIndexa = (float)i->edge[0];
      HIBYTE(vertIndexa) &= ~0x80u;
      v5 = (int)(vertIndexa - 1.0);
    }
    v6 = &maGlobal.currentObject->mesh.edges[v5];
    if ( LODWORD(v6->z) == 1065353216 )
    {
      v7 = (double)vertNum;
      if ( v6->x == v7 || v6->y == v7 )
        break;
    }
    if ( ++v3 >= 3 )
      return 0;
  }
  return 1;
}

// FUNC: void __cdecl MA_GetSharedFace(int,int,int &,int &)
void __cdecl MA_GetSharedFace(int faceIndex, int vertIndex, int *sharedFace, int *sharedVert)
{
  int v4; // ebp
  maMesh_t *p_mesh; // ebx
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  double v9; // st7
  int v10; // edx
  int v11; // esi
  int v12; // eax
  int *vertexNum; // ecx
  bool v14; // cc
  int edgeIndex; // [esp+14h] [ebp-Ch]
  int v16; // [esp+18h] [ebp-8h]
  float vertIndexa; // [esp+28h] [ebp+8h]

  v4 = maGlobal.currentObject->mesh.faces->vertexNum[14 * faceIndex + 7 * faceIndex + vertIndex];
  p_mesh = &maGlobal.currentObject->mesh;
  v6 = 84 * faceIndex;
  *sharedFace = -1;
  *sharedVert = -1;
  edgeIndex = 0;
  v16 = 84 * faceIndex;
  do
  {
    v7 = *(int *)((char *)p_mesh->faces->edge + v6);
    if ( v7 < 0 )
    {
      vertIndexa = (float)*(int *)((char *)p_mesh->faces->edge + v6);
      HIBYTE(vertIndexa) &= ~0x80u;
      v7 = (int)(vertIndexa - 1.0);
    }
    v8 = (int)&p_mesh->edges[v7];
    if ( *(_DWORD *)(v8 + 8) == 1065353216 )
    {
      v9 = (double)v4;
      if ( *(float *)v8 == v9 || *(float *)(v8 + 4) == v9 )
      {
        v10 = 0;
        if ( faceIndex > 0 )
        {
          v11 = 0;
          do
          {
            v12 = 0;
            vertexNum = p_mesh->faces[v11].vertexNum;
            while ( *vertexNum != v4 )
            {
              ++v12;
              ++vertexNum;
              if ( v12 >= 3 )
                goto LABEL_14;
            }
            *sharedFace = v10;
            *sharedVert = v12;
LABEL_14:
            ++v10;
            ++v11;
          }
          while ( v10 < faceIndex );
          v6 = v16;
        }
      }
    }
    if ( *sharedFace != -1 )
      break;
    v6 += 4;
    v14 = ++edgeIndex < 3;
    v16 = v6;
  }
  while ( v14 );
}

// FUNC: void __cdecl MA_ApplyTransformation(struct maModel_s *)
void __cdecl MA_ApplyTransformation(maModel_s *model)
{
  maModel_s *v1; // eax
  int i; // ebp
  maObject_t *v3; // ebx
  maTransform_s *transform; // edx
  maMesh_t *p_mesh; // ebx
  long double v6; // st7
  long double v7; // st7
  long double v8; // st7
  long double v9; // st6
  long double v10; // st7
  float y; // eax
  float z; // ecx
  int v13; // edi
  bool v14; // cc
  int v15; // esi
  float *p_x; // ecx
  double v17; // st7
  double v18; // st6
  double v19; // st5
  float v20; // eax
  float *v21; // ecx
  double v22; // st7
  double v23; // st6
  double v24; // st5
  float v25; // eax
  float *v26; // ecx
  double v27; // st7
  double v28; // st6
  double v29; // st5
  float v30; // eax
  float *v31; // ecx
  double v32; // st7
  double v33; // st6
  double v34; // st5
  float v35; // eax
  float *v36; // eax
  double v37; // st7
  double v38; // st6
  float v39; // [esp+4h] [ebp-140h]
  float v40; // [esp+4h] [ebp-140h]
  float v41; // [esp+4h] [ebp-140h]
  float v42; // [esp+4h] [ebp-140h]
  float v43; // [esp+4h] [ebp-140h]
  float v44; // [esp+4h] [ebp-140h]
  float v45; // [esp+4h] [ebp-140h]
  float v46; // [esp+4h] [ebp-140h]
  float v47; // [esp+4h] [ebp-140h]
  float v48; // [esp+4h] [ebp-140h]
  float v49; // [esp+4h] [ebp-140h]
  idMat4 rotx; // [esp+8h] [ebp-13Ch] BYREF
  idMat4 rotz; // [esp+48h] [ebp-FCh] BYREF
  idMat4 roty; // [esp+88h] [ebp-BCh] BYREF
  idMat4 scale; // [esp+C8h] [ebp-7Ch] BYREF
  float v54; // [esp+110h] [ebp-34h]
  float v55; // [esp+11Ch] [ebp-28h]
  float v56; // [esp+128h] [ebp-1Ch]
  float v57; // [esp+134h] [ebp-10h]
  float v58; // [esp+140h] [ebp-4h]

  v1 = model;
  for ( i = 0; i < v1->objects.num; ++i )
  {
    v3 = v1->objects.list[i];
    transform = v3->mesh.transform;
    p_mesh = &v3->mesh;
    if ( transform )
    {
      do
      {
        v6 = fabs(transform->rotate.x);
        qmemcpy(&rotx, &mat4_identity, sizeof(rotx));
        qmemcpy(&roty, &mat4_identity, sizeof(roty));
        qmemcpy(&rotz, &mat4_identity, sizeof(rotz));
        if ( v6 > 0.0 )
        {
          v7 = -transform->rotate.x * idMath::M_DEG2RAD;
          qmemcpy(&rotx, &mat4_identity, sizeof(rotx));
          v39 = sin(v7);
          rotx.mat[1].z = v39;
          rotx.mat[1].y = cos(v7);
          rotx.mat[2].y = -v39;
          rotx.mat[2].z = rotx.mat[1].y;
        }
        if ( fabs(transform->rotate.y) > 0.0 )
        {
          v8 = idMath::M_DEG2RAD * transform->rotate.y;
          v9 = sin(v8);
          qmemcpy(&roty, &mat4_identity, sizeof(roty));
          v40 = cos(v8);
          roty.mat[0].x = v40;
          roty.mat[2].z = v40;
          roty.mat[0].z = -v9;
          roty.mat[2].x = v9;
        }
        if ( fabs(transform->rotate.z) > 0.0 )
        {
          v10 = -transform->rotate.z * idMath::M_DEG2RAD;
          qmemcpy(&rotz, &mat4_identity, sizeof(rotz));
          v41 = sin(v10);
          rotz.mat[0].y = v41;
          rotz.mat[0].x = cos(v10);
          rotz.mat[1].x = -v41;
          rotz.mat[1].y = rotz.mat[0].x;
        }
        y = transform->scale.y;
        qmemcpy(&scale, &mat4_identity, sizeof(scale));
        scale.mat[0].x = transform->scale.x;
        z = transform->scale.z;
        v13 = 0;
        v14 = p_mesh->numVertexes <= 0;
        scale.mat[1].y = y;
        scale.mat[2].z = z;
        if ( !v14 )
        {
          v15 = 0;
          do
          {
            p_x = &p_mesh->vertexes[v15].x;
            v42 = scale.mat[3].y * p_x[1] + scale.mat[3].z * p_x[2] + scale.mat[3].x * *p_x + scale.mat[3].w;
            if ( v42 == 0.0 )
            {
              v17 = 0.0;
              v56 = 0.0;
              v18 = 0.0;
            }
            else
            {
              if ( v42 == 1.0 )
              {
                v17 = scale.mat[0].y * p_x[1] + scale.mat[0].z * p_x[2] + scale.mat[0].x * *p_x + scale.mat[0].w;
                v18 = scale.mat[1].z * p_x[2] + scale.mat[1].y * p_x[1] + scale.mat[1].x * *p_x + scale.mat[1].w;
                v19 = scale.mat[2].y * p_x[1] + scale.mat[2].z * p_x[2] + scale.mat[2].x * *p_x + scale.mat[2].w;
              }
              else
              {
                v43 = 1.0 / v42;
                v17 = (scale.mat[0].y * p_x[1] + scale.mat[0].z * p_x[2] + scale.mat[0].x * *p_x + scale.mat[0].w) * v43;
                v18 = (scale.mat[1].z * p_x[2] + scale.mat[1].y * p_x[1] + scale.mat[1].x * *p_x + scale.mat[1].w) * v43;
                v19 = (scale.mat[2].y * p_x[1] + scale.mat[2].z * p_x[2] + scale.mat[2].x * *p_x + scale.mat[2].w) * v43;
              }
              v56 = v19;
            }
            v20 = v56;
            *p_x = v17;
            p_x[2] = v20;
            p_x[1] = v18;
            v21 = &p_mesh->vertexes[v15].x;
            v44 = rotx.mat[3].x * *v21 + rotx.mat[3].y * v21[1] + rotx.mat[3].z * v21[2] + rotx.mat[3].w;
            if ( v44 == 0.0 )
            {
              v22 = 0.0;
              v57 = 0.0;
              v23 = 0.0;
            }
            else
            {
              if ( v44 == 1.0 )
              {
                v22 = rotx.mat[0].z * v21[2] + rotx.mat[0].y * v21[1] + rotx.mat[0].x * *v21 + rotx.mat[0].w;
                v23 = rotx.mat[1].x * *v21 + rotx.mat[1].z * v21[2] + rotx.mat[1].y * v21[1] + rotx.mat[1].w;
                v24 = rotx.mat[2].x * *v21 + rotx.mat[2].y * v21[1] + rotx.mat[2].z * v21[2] + rotx.mat[2].w;
              }
              else
              {
                v45 = 1.0 / v44;
                v22 = (rotx.mat[0].z * v21[2] + rotx.mat[0].y * v21[1] + rotx.mat[0].x * *v21 + rotx.mat[0].w) * v45;
                v23 = (rotx.mat[1].x * *v21 + rotx.mat[1].z * v21[2] + rotx.mat[1].y * v21[1] + rotx.mat[1].w) * v45;
                v24 = (rotx.mat[2].x * *v21 + rotx.mat[2].y * v21[1] + rotx.mat[2].z * v21[2] + rotx.mat[2].w) * v45;
              }
              v57 = v24;
            }
            v25 = v57;
            *v21 = v22;
            v21[2] = v25;
            v21[1] = v23;
            v26 = &p_mesh->vertexes[v15].x;
            v46 = rotz.mat[3].x * *v26 + rotz.mat[3].y * v26[1] + rotz.mat[3].z * v26[2] + rotz.mat[3].w;
            if ( v46 == 0.0 )
            {
              v27 = 0.0;
              v55 = 0.0;
              v28 = 0.0;
            }
            else
            {
              if ( v46 == 1.0 )
              {
                v27 = rotz.mat[0].x * *v26 + rotz.mat[0].z * v26[2] + rotz.mat[0].y * v26[1] + rotz.mat[0].w;
                v28 = rotz.mat[1].z * v26[2] + rotz.mat[1].y * v26[1] + rotz.mat[1].x * *v26 + rotz.mat[1].w;
                v29 = rotz.mat[2].y * v26[1] + rotz.mat[2].z * v26[2] + rotz.mat[2].x * *v26 + rotz.mat[2].w;
              }
              else
              {
                v47 = 1.0 / v46;
                v27 = (rotz.mat[0].x * *v26 + rotz.mat[0].z * v26[2] + rotz.mat[0].y * v26[1] + rotz.mat[0].w) * v47;
                v28 = (rotz.mat[1].z * v26[2] + rotz.mat[1].y * v26[1] + rotz.mat[1].x * *v26 + rotz.mat[1].w) * v47;
                v29 = (rotz.mat[2].y * v26[1] + rotz.mat[2].z * v26[2] + rotz.mat[2].x * *v26 + rotz.mat[2].w) * v47;
              }
              v55 = v29;
            }
            v30 = v55;
            *v26 = v27;
            v26[2] = v30;
            v26[1] = v28;
            v31 = &p_mesh->vertexes[v15].x;
            v48 = roty.mat[3].y * v31[1] + roty.mat[3].z * v31[2] + roty.mat[3].x * *v31 + roty.mat[3].w;
            if ( v48 == 0.0 )
            {
              v32 = 0.0;
              v54 = 0.0;
              v33 = 0.0;
            }
            else
            {
              if ( v48 == 1.0 )
              {
                v32 = roty.mat[0].x * *v31 + roty.mat[0].z * v31[2] + roty.mat[0].y * v31[1] + roty.mat[0].w;
                v33 = roty.mat[1].x * *v31 + roty.mat[1].z * v31[2] + roty.mat[1].y * v31[1] + roty.mat[1].w;
                v34 = roty.mat[2].y * v31[1] + roty.mat[2].z * v31[2] + roty.mat[2].x * *v31 + roty.mat[2].w;
              }
              else
              {
                v49 = 1.0 / v48;
                v32 = (roty.mat[0].x * *v31 + roty.mat[0].z * v31[2] + roty.mat[0].y * v31[1] + roty.mat[0].w) * v49;
                v33 = (roty.mat[1].x * *v31 + roty.mat[1].z * v31[2] + roty.mat[1].y * v31[1] + roty.mat[1].w) * v49;
                v34 = (roty.mat[2].y * v31[1] + roty.mat[2].z * v31[2] + roty.mat[2].x * *v31 + roty.mat[2].w) * v49;
              }
              v54 = v34;
            }
            v35 = v54;
            *v31 = v32;
            v31[2] = v35;
            ++v13;
            v31[1] = v33;
            v36 = &p_mesh->vertexes[v15].x;
            v37 = *v36 + transform->translate.x;
            ++v15;
            v38 = v36[1] + transform->translate.y;
            v58 = v36[2] + transform->translate.z;
            v36[2] = v58;
            *v36 = v37;
            v36[1] = v38;
          }
          while ( v13 < p_mesh->numVertexes );
        }
        transform = transform->parent;
      }
      while ( transform );
      v1 = model;
    }
  }
}

// FUNC: bool __cdecl MA_ParseTransform(class idParser &)
char __cdecl MA_ParseTransform(idParser *parser)
{
  void *v1; // edi
  char Vec3; // al
  char v4; // al
  char *parent; // ecx
  int v6; // esi
  int v7; // edx
  idHashTable<maTransform_s *>::hashnode_s *v8; // esi
  signed int v9; // eax
  char v10; // cl
  idHashTable<maTransform_s *> *p_transforms; // ebp
  int v12; // edx
  maNodeHeader_t *i; // eax
  int v14; // edi
  int v15; // ebx
  idHashTable<maTransform_s *>::hashnode_s *v16; // esi
  idHashTable<maTransform_s *>::hashnode_s **p_next; // edi
  signed int v18; // eax
  idHashTable<rvDeclGuide *>::hashnode_s *v19; // eax
  idHashTable<maTransform_s *>::hashnode_s *v20; // eax
  rvDeclGuide *transform; // [esp+10h] [ebp-164h]
  idToken token; // [esp+14h] [ebp-160h] BYREF
  idHashTable<rvDeclGuide *>::hashnode_s *v23; // [esp+64h] [ebp-110h]
  maNodeHeader_t header; // [esp+68h] [ebp-10Ch] BYREF
  int v25; // [esp+170h] [ebp-4h]

  memset(&header, 0, sizeof(header));
  v1 = Mem_Alloc(40, 0xEu);
  *(_DWORD *)v1 = 0;
  *((_DWORD *)v1 + 1) = 0;
  *((_DWORD *)v1 + 2) = 0;
  *((_DWORD *)v1 + 3) = 0;
  *((_DWORD *)v1 + 4) = 0;
  *((_DWORD *)v1 + 5) = 0;
  *((_DWORD *)v1 + 6) = 0;
  *((_DWORD *)v1 + 7) = 0;
  *((_DWORD *)v1 + 8) = 0;
  *((_DWORD *)v1 + 9) = 0;
  transform = (rvDeclGuide *)v1;
  *((_DWORD *)v1 + 8) = 1065353216;
  *((_DWORD *)v1 + 7) = 1065353216;
  *((_DWORD *)v1 + 6) = 1065353216;
  MA_ParseNodeHeader(parser, &header);
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v25 = 0;
  if ( !idParser::ReadToken(parser, &token) )
    goto LABEL_17;
  while ( idStr::Icmp(token.data, "createNode")
       && idStr::Icmp(token.data, "connectAttr")
       && idStr::Icmp(token.data, "select") )
  {
    if ( !idStr::Icmp(token.data, "setAttr") )
    {
      idParser::ReadToken(parser, &token);
      if ( idStr::Icmp(token.data, ".t") )
      {
        if ( idStr::Icmp(token.data, ".r") )
        {
          if ( idStr::Icmp(token.data, ".s") )
          {
            idParser::SkipRestOfLine(parser);
            goto LABEL_16;
          }
          Vec3 = MA_ReadVec3(parser, (idVec3 *)v1 + 2);
        }
        else
        {
          Vec3 = MA_ReadVec3(parser, (idVec3 *)v1 + 1);
        }
        if ( !Vec3 )
        {
LABEL_12:
          v25 = -1;
          idStr::FreeData(&token);
          return 0;
        }
      }
      else
      {
        if ( !MA_ReadVec3(parser, (idVec3 *)v1) )
          goto LABEL_12;
        *((float *)v1 + 1) = *((float *)v1 + 1) * -1.0;
      }
    }
LABEL_16:
    if ( !idParser::ReadToken(parser, &token) )
      goto LABEL_17;
  }
  idParser::UnreadToken(parser, &token);
LABEL_17:
  v4 = header.parent[0];
  if ( header.parent[0] )
  {
    parent = header.parent;
    v6 = 0;
    v7 = 119;
    do
    {
      ++parent;
      v6 += v7 * v4;
      v4 = *parent;
      ++v7;
    }
    while ( *parent );
    v8 = maGlobal.model->transforms.heads[v6 & maGlobal.model->transforms.tablesizemask];
    if ( v8 )
    {
      while ( 1 )
      {
        v9 = idStr::Cmp(v8->key.data, header.parent);
        if ( !v9 )
          break;
        if ( v9 <= 0 )
        {
          v8 = v8->next;
          if ( v8 )
            continue;
        }
        goto LABEL_28;
      }
      if ( v8 != (idHashTable<maTransform_s *>::hashnode_s *)-32 )
        *((_DWORD *)v1 + 9) = v8->value;
    }
  }
LABEL_28:
  v10 = header.name[0];
  p_transforms = &maGlobal.model->transforms;
  v12 = 0;
  for ( i = &header; v10; v12 += v14 )
  {
    v14 = v10 * ((_DWORD)i + 119 - (_DWORD)&header);
    v10 = i->name[1];
    i = (maNodeHeader_t *)((char *)i + 1);
  }
  v15 = v12 & maGlobal.model->transforms.tablesizemask;
  v16 = p_transforms->heads[v15];
  p_next = &p_transforms->heads[v15];
  if ( v16 )
  {
    while ( 1 )
    {
      v18 = idStr::Cmp(v16->key.data, header.name);
      if ( !v18 )
        break;
      if ( v18 <= 0 )
      {
        p_next = &v16->next;
        v16 = v16->next;
        if ( v16 )
          continue;
      }
      goto LABEL_34;
    }
    v16->value = (maTransform_s *)transform;
  }
  else
  {
LABEL_34:
    ++p_transforms->numentries;
    v19 = (idHashTable<rvDeclGuide *>::hashnode_s *)Memory::Allocate(0x28u);
    v23 = v19;
    LOBYTE(v25) = 1;
    if ( v19 )
      idHashTable<maTransform_s *>::hashnode_s::hashnode_s(
        v19,
        header.name,
        transform,
        (idHashTable<rvDeclGuide *>::hashnode_s *)p_transforms->heads[v15]);
    else
      v20 = 0;
    *p_next = v20;
    v20->next = v16;
  }
  v25 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: void __cdecl MA_ParseMesh(class idParser &)
void __cdecl MA_ParseMesh(idParser *parser)
{
  void *v1; // esp
  idList<maObject_t *> *p_objects; // esi
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v8; // ecx
  maObject_t **list; // edi
  int j; // eax
  char v11; // al
  char *parent; // ecx
  int v13; // esi
  int v14; // edx
  idHashTable<maTransform_s *>::hashnode_s *v15; // esi
  signed int v16; // eax
  maMesh_t *p_mesh; // esi
  int v18; // ecx
  int v19; // ebx
  maFace_t *faces; // edx
  int v21; // eax
  idVec3 *edges; // edi
  double x; // st7
  int v24; // ebx
  int k; // edi
  maFace_t *v26; // ecx
  idVec3 *v27; // eax
  int *v28; // ecx
  int nextNormal; // eax
  int *v30; // eax
  int *v31; // ecx
  int v32; // eax
  maFace_t *v33; // ecx
  int v34; // edx
  maFace_t *v35; // ecx
  int y_low; // ebx
  idVec3 *v37; // ecx
  maFace_t *v38; // ecx
  int v39; // edx
  maFace_t *v40; // edx
  int v41; // edi
  maFace_t *v42; // ecx
  int v43; // edx
  int v44; // edx
  int v45; // edi
  idVec4 *vertTransforms; // eax
  double w; // st7
  float *p_x; // ecx
  idVec3 *vertexes; // ebx
  float *v50; // eax
  int v51; // esi
  char *v52; // eax
  int v53; // esi
  char *v54; // eax
  int v55; // esi
  char *v56; // eax
  idLexer *scriptstack; // eax
  const char *data; // eax
  char *v59; // eax
  char *v60; // edx
  char v61; // cl
  int faceIndex; // [esp+0h] [ebp-1208h]
  maObject_t *v63; // [esp+4h] [ebp-1204h]
  int sharedFace; // [esp+8h] [ebp-1200h] BYREF
  int sharedVert; // [esp+Ch] [ebp-11FCh] BYREF
  float v66; // [esp+10h] [ebp-11F8h]
  float v67; // [esp+14h] [ebp-11F4h]
  int v68; // [esp+18h] [ebp-11F0h]
  float z; // [esp+1Ch] [ebp-11ECh]
  idToken token; // [esp+20h] [ebp-11E8h] BYREF
  maAttribHeader_t v71; // [esp+70h] [ebp-1198h] BYREF
  maNodeHeader_t header; // [esp+F8h] [ebp-1110h] BYREF
  char v73[2048]; // [esp+1F8h] [ebp-1010h] BYREF
  char pExceptionObject[2052]; // [esp+9F8h] [ebp-810h] BYREF
  int v75; // [esp+1204h] [ebp-4h]

  v1 = alloca(4604);
  v63 = (maObject_t *)Mem_Alloc(332, 0xEu);
  memset(v63, 0, sizeof(maObject_t));
  p_objects = &maGlobal.model->objects;
  if ( !maGlobal.model->objects.list )
  {
    granularity = maGlobal.model->objects.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != maGlobal.model->objects.size )
      {
        v4 = granularity < p_objects->num;
        maGlobal.model->objects.size = granularity;
        if ( v4 )
          p_objects->num = granularity;
        p_objects->list = (maObject_t **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < p_objects->num; ++i )
          p_objects->list[i] = *(maObject_t **)(4 * i);
      }
    }
    else
    {
      maGlobal.model->objects.list = 0;
      p_objects->num = 0;
      p_objects->size = 0;
    }
  }
  num = p_objects->num;
  size = p_objects->size;
  if ( p_objects->num == size )
  {
    if ( !p_objects->granularity )
      p_objects->granularity = 16;
    v8 = size + p_objects->granularity - (size + p_objects->granularity) % p_objects->granularity;
    if ( v8 > 0 )
    {
      if ( v8 != p_objects->size )
      {
        list = p_objects->list;
        p_objects->size = v8;
        if ( v8 < num )
          p_objects->num = v8;
        p_objects->list = (maObject_t **)Memory::Allocate(4 * v8);
        for ( j = 0; j < p_objects->num; ++j )
          p_objects->list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( p_objects->list )
        Memory::Free(p_objects->list);
      p_objects->list = 0;
      p_objects->num = 0;
      p_objects->size = 0;
    }
  }
  p_objects->list[p_objects->num++] = v63;
  maGlobal.currentObject = v63;
  v63->materialRef = -1;
  MA_ParseNodeHeader(parser, &header);
  v11 = header.parent[0];
  if ( header.parent[0] )
  {
    parent = header.parent;
    v13 = 0;
    v14 = 119;
    do
    {
      ++parent;
      v13 += v14 * v11;
      v11 = *parent;
      ++v14;
    }
    while ( *parent );
    v15 = maGlobal.model->transforms.heads[v13 & maGlobal.model->transforms.tablesizemask];
    if ( v15 )
    {
      while ( 1 )
      {
        v16 = idStr::Cmp(v15->key.data, header.parent);
        if ( !v16 )
          break;
        if ( v16 <= 0 )
        {
          v15 = v15->next;
          if ( v15 )
            continue;
        }
        goto LABEL_33;
      }
      if ( v15 != (idHashTable<maTransform_s *>::hashnode_s *)-32 )
        maGlobal.currentObject->mesh.transform = v15->value;
    }
  }
LABEL_33:
  strcpy(v63->name, header.name);
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v75 = 0;
  if ( idParser::ReadToken(parser, &token) )
  {
    while ( idStr::Icmp(token.data, "createNode")
         && idStr::Icmp(token.data, "connectAttr")
         && idStr::Icmp(token.data, "select") )
    {
      if ( !idStr::Icmp(token.data, "setAttr") )
      {
        MA_ParseAttribHeader(parser, &v71);
        if ( strstr(v71.name, ".vt") )
        {
          MA_ParseVertex(parser, &v71);
        }
        else if ( strstr(v71.name, ".ed") )
        {
          MA_ParseEdge(parser, &v71);
        }
        else if ( strstr(v71.name, ".pt") )
        {
          MA_ParseVertexTransforms(parser, &v71);
        }
        else if ( strstr(v71.name, ".n") )
        {
          MA_ParseNormal(parser, &v71);
        }
        else if ( strstr(v71.name, ".fc") )
        {
          MA_ParseFace(parser, &v71);
        }
        else if ( strstr(v71.name, ".clr") )
        {
          MA_ParseColor(parser, &v71);
        }
        else if ( strstr(v71.name, ".uvst") )
        {
          MA_ParseTVert(parser, &v71);
        }
        else
        {
          idParser::SkipRestOfLine(parser);
        }
      }
      if ( !idParser::ReadToken(parser, &token) )
        goto LABEL_56;
    }
    idParser::UnreadToken(parser, &token);
  }
LABEL_56:
  p_mesh = &maGlobal.currentObject->mesh;
  v4 = maGlobal.currentObject->mesh.numFaces <= 0;
  sharedVert = 0;
  if ( !v4 )
  {
    v18 = 12;
    sharedFace = 12;
    do
    {
      v19 = 3;
      do
      {
        faces = p_mesh->faces;
        v21 = *(int *)((char *)&faces->edge[-3] + v18);
        edges = p_mesh->edges;
        if ( v21 >= 0 )
        {
          x = edges[v21].x;
        }
        else
        {
          v66 = (float)*(int *)((char *)&faces->edge[-3] + v18);
          HIBYTE(v66) &= ~0x80u;
          x = edges[(int)(v66 - 1.0)].y;
        }
        *(int *)((char *)faces->edge + v18) = (int)x;
        v18 += 4;
        --v19;
      }
      while ( v19 );
      v18 = sharedFace + 84;
      v4 = ++sharedVert < p_mesh->numFaces;
      sharedFace += 84;
    }
    while ( v4 );
  }
  if ( p_mesh->normalsParsed )
  {
    faceIndex = 0;
    if ( p_mesh->numFaces > 0 )
    {
      v24 = 4;
      do
      {
        for ( k = 0; k < 3; ++k )
        {
          sharedFace = -1;
          sharedVert = -1;
          if ( !MA_QuickIsVertShared(faceIndex, k)
            || (MA_GetSharedFace(faceIndex, k, &sharedFace, &sharedVert), sharedFace == -1) )
          {
            nextNormal = p_mesh->nextNormal;
            if ( nextNormal >= p_mesh->numNormals )
            {
              scriptstack = parser->scriptstack;
              if ( scriptstack )
                data = scriptstack->filename.data;
              else
                data = &entityFilter;
              v59 = va("Maya Loader '%s': Invalid Normals Index.", data);
              v60 = v73;
              do
              {
                v61 = *v59;
                *v60++ = *v59++;
              }
              while ( v61 );
              qmemcpy(pExceptionObject, v73, 0x800u);
              _CxxThrowException(pExceptionObject, &_TI1_AVidException__);
            }
            v30 = (int *)&p_mesh->normals[nextNormal];
            v31 = &p_mesh->faces->edge[3 * v24 + 3 * k];
            *v31 = *v30;
            v31[1] = v30[1];
            v31[2] = v30[2];
            ++p_mesh->nextNormal;
          }
          else
          {
            v26 = p_mesh->faces;
            v27 = &v26[sharedFace].vertexNormals[sharedVert];
            v28 = &v26->edge[3 * v24 + 3 * k];
            *v28 = LODWORD(v27->x);
            v28[1] = LODWORD(v27->y);
            v28[2] = LODWORD(v27->z);
          }
        }
        v24 += 7;
        ++faceIndex;
      }
      while ( faceIndex < p_mesh->numFaces );
    }
  }
  v4 = p_mesh->numFaces <= 0;
  sharedFace = 0;
  if ( !v4 )
  {
    v32 = 0;
    do
    {
      v33 = p_mesh->faces;
      v34 = v33[v32].vertexNum[1];
      v33[v32].vertexNum[1] = v33[v32].vertexNum[2];
      p_mesh->faces[v32].vertexNum[2] = v34;
      v35 = &p_mesh->faces[v32];
      v67 = v35->vertexNormals[1].x;
      y_low = LODWORD(v35->vertexNormals[1].y);
      z = v35->vertexNormals[1].z;
      v35->vertexNormals[1].x = v35->vertexNormals[2].x;
      v35->vertexNormals[1].y = v35->vertexNormals[2].y;
      v35->vertexNormals[1].z = v35->vertexNormals[2].z;
      v37 = &p_mesh->faces[v32].vertexNormals[2];
      v37->x = v67;
      LODWORD(v37->y) = y_low;
      v37->z = z;
      v38 = p_mesh->faces;
      v39 = v38[v32].tVertexNum[1];
      v38[v32].tVertexNum[1] = v38[v32].tVertexNum[2];
      p_mesh->faces[v32].tVertexNum[2] = v39;
      v40 = p_mesh->faces;
      v41 = v40[v32].vertexColors[2];
      v42 = &v40[v32];
      v43 = v40[v32].vertexColors[1];
      v42->vertexColors[1] = v41;
      p_mesh->faces[v32++].vertexColors[2] = v43;
      v4 = sharedFace + 1 < p_mesh->numFaces;
      v68 = y_low;
      ++sharedFace;
    }
    while ( v4 );
  }
  v44 = 0;
  if ( p_mesh->numVertTransforms > 0 )
  {
    v45 = 0;
    do
    {
      vertTransforms = p_mesh->vertTransforms;
      w = vertTransforms[v45].w;
      p_x = &vertTransforms[v45].x;
      vertexes = p_mesh->vertexes;
      ++v44;
      ++v45;
      sharedFace = (int)w;
      v50 = &vertexes[(int)w].x;
      *v50 = *p_x + *v50;
      v50[1] = p_x[1] + v50[1];
      v50[2] = p_x[2] + v50[2];
    }
    while ( v44 < p_mesh->numVertTransforms );
  }
  if ( maGlobal.verbose )
  {
    v51 = *(_DWORD *)common.type;
    v52 = va("MESH %s - parent %s\n", header.name, header.parent);
    (*(void (__cdecl **)(netadrtype_t, char *))(v51 + 124))(common.type, v52);
    if ( maGlobal.verbose )
    {
      v53 = *(_DWORD *)common.type;
      v54 = va("\tverts:%d\n", maGlobal.currentObject->mesh.numVertexes);
      (*(void (__cdecl **)(netadrtype_t, char *))(v53 + 124))(common.type, v54);
      if ( maGlobal.verbose )
      {
        v55 = *(_DWORD *)common.type;
        v56 = va("\tfaces:%d\n", maGlobal.currentObject->mesh.numFaces);
        (*(void (__cdecl **)(netadrtype_t, char *))(v55 + 124))(common.type, v56);
      }
    }
  }
  v75 = -1;
  idStr::FreeData(&token);
}

// FUNC: void __cdecl MA_ParseFileNode(class idParser &)
void __cdecl MA_ParseFileNode(idParser *parser)
{
  idParser *v1; // esi
  char *v2; // ebp
  char *data; // ecx
  _BYTE *v4; // edx
  char v5; // al
  char v6; // al
  idHashTable<maFileNode_t *> *p_fileNodes; // ebx
  int v8; // edx
  char *i; // ecx
  int v10; // edi
  int v11; // eax
  idHashTable<maFileNode_t *>::hashnode_s *v12; // esi
  idHashTable<maFileNode_t *>::hashnode_s **p_next; // edi
  signed int v14; // eax
  idHashTable<rvDeclGuide *>::hashnode_s *v15; // eax
  idHashTable<maFileNode_t *>::hashnode_s *v16; // eax
  int v17; // [esp+4h] [ebp-1E8h]
  idToken token; // [esp+Ch] [ebp-1E0h] BYREF
  maAttribHeader_t attribHeader; // [esp+5Ch] [ebp-190h] BYREF
  maNodeHeader_t header; // [esp+E0h] [ebp-10Ch] BYREF
  int v21; // [esp+1E8h] [ebp-4h]

  v1 = parser;
  MA_ParseNodeHeader(parser, &header);
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v21 = 0;
  if ( idParser::ReadToken(parser, &token) )
  {
    while ( idStr::Icmp(token.data, "createNode")
         && idStr::Icmp(token.data, "connectAttr")
         && idStr::Icmp(token.data, "select") )
    {
      if ( !idStr::Icmp(token.data, "setAttr") )
      {
        MA_ParseAttribHeader(v1, &attribHeader);
        if ( strstr(attribHeader.name, ".ftn") )
        {
          idParser::SkipUntilString(v1, "string");
          idParser::ReadToken(v1, &token);
          if ( !idStr::Icmp(token.data, "(") )
            idParser::ReadToken(v1, &token);
          v2 = (char *)Mem_Alloc(1152, 0xEu);
          strcpy(v2, header.name);
          data = token.data;
          v4 = v2 + 128;
          do
          {
            v5 = *data;
            *v4++ = *data++;
          }
          while ( v5 );
          v6 = *v2;
          p_fileNodes = &maGlobal.model->fileNodes;
          v8 = 0;
          for ( i = v2; v6; v8 += v10 )
          {
            v10 = v6 * (_DWORD)&i[119 - (_DWORD)v2];
            v6 = *++i;
          }
          v11 = v8 & maGlobal.model->fileNodes.tablesizemask;
          v12 = p_fileNodes->heads[v11];
          p_next = &p_fileNodes->heads[v11];
          v17 = v11 * 4;
          if ( v12 )
          {
            while ( 1 )
            {
              v14 = idStr::Cmp(v12->key.data, v2);
              if ( !v14 )
                break;
              if ( v14 <= 0 )
              {
                p_next = &v12->next;
                v12 = v12->next;
                if ( v12 )
                  continue;
              }
              goto LABEL_17;
            }
            v12->value = (maFileNode_t *)v2;
            v1 = parser;
          }
          else
          {
LABEL_17:
            ++p_fileNodes->numentries;
            v15 = (idHashTable<rvDeclGuide *>::hashnode_s *)Memory::Allocate(0x28u);
            LOBYTE(v21) = 1;
            if ( v15 )
            {
              idHashTable<maTransform_s *>::hashnode_s::hashnode_s(
                v15,
                v2,
                (rvDeclGuide *)v2,
                *(idHashTable<rvDeclGuide *>::hashnode_s **)((char *)p_fileNodes->heads + v17));
              *p_next = v16;
              v16->next = v12;
            }
            else
            {
              *p_next = 0;
              MEMORY[0x24] = v12;
            }
            v1 = parser;
            LOBYTE(v21) = 0;
          }
        }
        else
        {
          idParser::SkipRestOfLine(v1);
        }
      }
      if ( !idParser::ReadToken(v1, &token) )
        goto LABEL_26;
    }
    idParser::UnreadToken(v1, &token);
  }
LABEL_26:
  v21 = -1;
  idStr::FreeData(&token);
}

// FUNC: void __cdecl MA_ParseMaterialNode(class idParser &)
void __cdecl MA_ParseMaterialNode(idParser *parser)
{
  maMaterialNode_s *v1; // esi
  maMaterialNode_s *matNode; // [esp+8h] [ebp-104h] BYREF
  maNodeHeader_t header; // [esp+Ch] [ebp-100h] BYREF

  MA_ParseNodeHeader(parser, &header);
  v1 = (maMaterialNode_s *)Mem_Alloc(136, 0xEu);
  memset(v1, 0, sizeof(maMaterialNode_s));
  matNode = v1;
  strcpy(v1->name, header.name);
  idHashTable<maMaterialNode_s *>::Set(&maGlobal.model->materialNodes, v1->name, &matNode);
}

// FUNC: void __cdecl MA_ParseCreateNode(class idParser &)
void __cdecl MA_ParseCreateNode(idParser *parser)
{
  idToken token; // [esp+0h] [ebp-5Ch] BYREF
  int v2; // [esp+58h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v2 = 0;
  idParser::ReadToken(parser, &token);
  if ( idStr::Icmp(token.data, "transform") )
  {
    if ( idStr::Icmp(token.data, "mesh") )
    {
      if ( idStr::Icmp(token.data, "file") )
      {
        if ( !idStr::Icmp(token.data, "shadingEngine")
          || !idStr::Icmp(token.data, "lambert")
          || !idStr::Icmp(token.data, "phong")
          || !idStr::Icmp(token.data, "blinn") )
        {
          MA_ParseMaterialNode(parser);
        }
      }
      else
      {
        MA_ParseFileNode(parser);
      }
    }
    else
    {
      MA_ParseMesh(parser);
    }
  }
  else
  {
    MA_ParseTransform(parser);
  }
  v2 = -1;
  idStr::FreeData(&token);
}

// FUNC: int __cdecl MA_AddMaterial(char const *)
int __cdecl MA_AddMaterial(char *materialName)
{
  char v1; // cl
  int v2; // edx
  const char *i; // eax
  int v4; // ebx
  idHashTable<maMaterialNode_s *>::hashnode_s *v5; // esi
  signed int v6; // eax
  maMaterialNode_s **p_value; // eax
  maMaterialNode_s *v9; // esi
  void *v10; // ebp
  idFileSystem_vtbl *v11; // edx
  char *v12; // eax
  char *data; // ecx
  _BYTE *v14; // edx
  char v15; // al
  idList<maMaterial_t *> *p_materials; // esi
  int granularity; // eax
  bool v18; // cc
  int j; // eax
  int num; // ebp
  int size; // eax
  int v22; // ecx
  maMaterial_t **list; // edi
  int k; // eax
  int v25; // esi
  int path; // [esp-4h] [ebp-40h]
  idStr qPath; // [esp+10h] [ebp-2Ch] BYREF
  int v28; // [esp+38h] [ebp-4h]
  const char *materialNamea; // [esp+40h] [ebp+4h]

  v1 = *materialName;
  v2 = 0;
  for ( i = materialName; v1; v2 += v4 )
  {
    v4 = v1 * (_DWORD)&i[119 - (_DWORD)materialName];
    v1 = *++i;
  }
  v5 = maGlobal.model->materialNodes.heads[v2 & maGlobal.model->materialNodes.tablesizemask];
  if ( !v5 )
    return -1;
  while ( 1 )
  {
    v6 = idStr::Cmp(v5->key.data, materialName);
    if ( !v6 )
      break;
    if ( v6 <= 0 )
    {
      v5 = v5->next;
      if ( v5 )
        continue;
    }
    return -1;
  }
  p_value = &v5->value;
  if ( v5 == (idHashTable<maMaterialNode_s *>::hashnode_s *)-32 )
    return -1;
  v9 = *p_value;
  if ( !*p_value )
    return -1;
  while ( !v9->file )
  {
    v9 = v9->child;
    if ( !v9 )
      return -1;
  }
  v10 = Mem_Alloc(148, 0xEu);
  memset(v10, 0, 0x94u);
  materialNamea = (const char *)v10;
  qPath.len = 0;
  qPath.alloced = 20;
  qPath.data = qPath.baseBuffer;
  qPath.baseBuffer[0] = 0;
  v11 = fileSystem->__vftable;
  path = (int)v9->file->path;
  v28 = 0;
  v12 = (char *)v11->OSPathToRelativePath(fileSystem, (const char *)path);
  idStr::operator=(&qPath, v12);
  data = qPath.data;
  v14 = v10;
  do
  {
    v15 = *data;
    *v14++ = *data++;
  }
  while ( v15 );
  p_materials = &maGlobal.model->materials;
  if ( !maGlobal.model->materials.list )
  {
    granularity = maGlobal.model->materials.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != maGlobal.model->materials.size )
      {
        v18 = granularity < p_materials->num;
        maGlobal.model->materials.size = granularity;
        if ( v18 )
          p_materials->num = granularity;
        p_materials->list = (maMaterial_t **)Memory::Allocate(4 * granularity);
        for ( j = 0; j < p_materials->num; ++j )
          p_materials->list[j] = *(maMaterial_t **)(4 * j);
      }
    }
    else
    {
      maGlobal.model->materials.list = 0;
      p_materials->num = 0;
      p_materials->size = 0;
    }
  }
  num = p_materials->num;
  size = p_materials->size;
  if ( p_materials->num == size )
  {
    if ( !p_materials->granularity )
      p_materials->granularity = 16;
    v22 = size + p_materials->granularity - (size + p_materials->granularity) % p_materials->granularity;
    if ( v22 > 0 )
    {
      if ( v22 != p_materials->size )
      {
        list = p_materials->list;
        p_materials->size = v22;
        if ( v22 < num )
          p_materials->num = v22;
        p_materials->list = (maMaterial_t **)Memory::Allocate(4 * v22);
        for ( k = 0; k < p_materials->num; ++k )
          p_materials->list[k] = list[k];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( p_materials->list )
        Memory::Free(p_materials->list);
      p_materials->list = 0;
      p_materials->num = 0;
      p_materials->size = 0;
    }
  }
  p_materials->list[p_materials->num++] = (maMaterial_t *)materialNamea;
  v25 = maGlobal.model->materials.num - 1;
  v28 = -1;
  idStr::FreeData(&qPath);
  return v25;
}

// FUNC: bool __cdecl MA_ParseConnectAttr(class idParser &)
char __cdecl MA_ParseConnectAttr(idParser *parser)
{
  void *v1; // esp
  int len; // ebx
  int Text; // eax
  idLexer *scriptstack; // eax
  const char *data; // eax
  char *v6; // eax
  char *v7; // edx
  char v8; // cl
  idStr *v9; // esi
  unsigned int v10; // ebx
  int v11; // eax
  idStr *v12; // esi
  unsigned int v13; // ebx
  int v14; // eax
  int v15; // ebx
  int v16; // eax
  idLexer *v17; // eax
  const char *v18; // eax
  char *v19; // eax
  char *v20; // edx
  char v21; // cl
  idStr *v22; // esi
  unsigned int v23; // ebx
  int v24; // eax
  idStr *v25; // esi
  unsigned int v26; // ebx
  int v27; // eax
  char *v28; // eax
  char v29; // dl
  char *v30; // edi
  int v31; // esi
  char *v32; // ecx
  unsigned int v33; // ebx
  idHashTable<maMaterialNode_s *>::hashnode_s *v34; // esi
  signed int v35; // eax
  maMaterialNode_s **p_value; // ebx
  char *v37; // ecx
  char v38; // al
  int v39; // esi
  char *v40; // edi
  unsigned int v41; // ebx
  idHashTable<maMaterialNode_s *>::hashnode_s *v42; // esi
  signed int v43; // eax
  maMaterialNode_s **v44; // esi
  char v45; // cl
  int v46; // esi
  const char *v47; // edi
  int v48; // edx
  int v49; // ebx
  idHashTable<maFileNode_t *>::hashnode_s *v50; // esi
  signed int v51; // eax
  char *v52; // ecx
  char v53; // al
  char *v54; // ebx
  int v55; // esi
  unsigned int v56; // ebx
  idHashTable<maMaterialNode_s *>::hashnode_s *v57; // esi
  signed int v58; // eax
  maMaterialNode_s **v59; // esi
  maModel_s *model; // eax
  int v61; // esi
  bool v62; // zf
  char *v63; // edx
  char *materialName; // ecx
  char v65; // al
  int v67; // [esp+0h] [ebp-1128h]
  int v68; // [esp+0h] [ebp-1128h]
  maMaterialNode_s **v69; // [esp+0h] [ebp-1128h]
  idStr v70; // [esp+4h] [ebp-1124h] BYREF
  idStr v71; // [esp+24h] [ebp-1104h] BYREF
  maFileNode_t **v72; // [esp+44h] [ebp-10E4h]
  idStr v73; // [esp+48h] [ebp-10E0h] BYREF
  idStr v74; // [esp+68h] [ebp-10C0h] BYREF
  idStr v75; // [esp+88h] [ebp-10A0h] BYREF
  idStr result; // [esp+A8h] [ebp-1080h] BYREF
  idToken token; // [esp+C8h] [ebp-1060h] BYREF
  char v78[2048]; // [esp+118h] [ebp-1010h] BYREF
  char pExceptionObject[2052]; // [esp+918h] [ebp-810h] BYREF
  int v80; // [esp+1124h] [ebp-4h]

  v1 = alloca(4380);
  v70.len = 0;
  v70.alloced = 20;
  v70.data = v70.baseBuffer;
  v70.baseBuffer[0] = 0;
  v80 = 5;
  v71.len = 0;
  v71.alloced = 20;
  v71.data = v71.baseBuffer;
  v71.baseBuffer[0] = 0;
  v73.len = 0;
  v73.alloced = 20;
  v73.data = v73.baseBuffer;
  v73.baseBuffer[0] = 0;
  v74.len = 0;
  v74.alloced = 20;
  v74.data = v74.baseBuffer;
  v74.baseBuffer[0] = 0;
  v75.len = 0;
  v75.alloced = 20;
  v75.data = v75.baseBuffer;
  v75.baseBuffer[0] = 0;
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  idParser::ReadToken(parser, &token);
  len = token.len;
  if ( token.len + 1 > 20 )
    idStr::ReAllocate(&v70, token.len + 1, 0);
  qmemcpy(v70.data, token.data, len);
  v70.data[len] = 0;
  v70.len = len;
  Text = idStr::FindText(v70.data, ".", 1, 0, len);
  v67 = Text;
  if ( Text == -1 )
  {
    scriptstack = parser->scriptstack;
    if ( scriptstack )
      data = scriptstack->filename.data;
    else
      data = &entityFilter;
    v6 = va("Maya Loader '%s': Invalid Connect Attribute.", data);
    v7 = v78;
    do
    {
      v8 = *v6;
      *v7++ = *v6++;
    }
    while ( v8 );
    qmemcpy(pExceptionObject, v78, 0x800u);
    _CxxThrowException(pExceptionObject, &_TI1_AVidException__);
  }
  v9 = idStr::Left(&v70, &result, Text);
  v10 = v9->len;
  v11 = v9->len + 1;
  LOBYTE(v80) = 6;
  if ( v11 > v71.alloced )
    idStr::ReAllocate(&v71, v11, 0);
  qmemcpy(v71.data, v9->data, v10);
  v71.data[v10] = 0;
  v71.len = v10;
  LOBYTE(v80) = 5;
  idStr::FreeData(&result);
  v12 = idStr::Right(&v70, &result, v70.len - v67 - 1);
  v13 = v12->len;
  v14 = v12->len + 1;
  LOBYTE(v80) = 7;
  if ( v14 > v73.alloced )
    idStr::ReAllocate(&v73, v14, 0);
  qmemcpy(v73.data, v12->data, v13);
  v73.data[v13] = 0;
  v73.len = v13;
  LOBYTE(v80) = 5;
  idStr::FreeData(&result);
  idParser::ReadToken(parser, &token);
  v15 = token.len;
  if ( token.len + 1 > v70.alloced )
    idStr::ReAllocate(&v70, token.len + 1, 0);
  qmemcpy(v70.data, token.data, v15);
  v70.data[v15] = 0;
  v70.len = v15;
  v16 = idStr::FindText(v70.data, ".", 1, 0, v15);
  v68 = v16;
  if ( v16 == -1 )
  {
    v17 = parser->scriptstack;
    if ( v17 )
      v18 = v17->filename.data;
    else
      v18 = &entityFilter;
    v19 = va("Maya Loader '%s': Invalid Connect Attribute.", v18);
    v20 = pExceptionObject;
    do
    {
      v21 = *v19;
      *v20++ = *v19++;
    }
    while ( v21 );
    qmemcpy(v78, pExceptionObject, sizeof(v78));
    _CxxThrowException(v78, &_TI1_AVidException__);
  }
  v22 = idStr::Left(&v70, &result, v16);
  v23 = v22->len;
  v24 = v22->len + 1;
  LOBYTE(v80) = 8;
  if ( v24 > v74.alloced )
    idStr::ReAllocate(&v74, v24, 0);
  qmemcpy(v74.data, v22->data, v23);
  v74.data[v23] = 0;
  v74.len = v23;
  LOBYTE(v80) = 5;
  idStr::FreeData(&result);
  v25 = idStr::Right(&v70, &result, v70.len - v68 - 1);
  v26 = v25->len;
  v27 = v25->len + 1;
  LOBYTE(v80) = 9;
  if ( v27 > v75.alloced )
    idStr::ReAllocate(&v75, v27, 0);
  qmemcpy(v75.data, v25->data, v26);
  v75.data[v26] = 0;
  v75.len = v26;
  LOBYTE(v80) = 5;
  idStr::FreeData(&result);
  if ( idStr::FindText(v73.data, "oc", 1, 0, v73.len) != -1 )
  {
    v28 = v71.data;
    v29 = *v71.data;
    v30 = v71.data;
    v31 = 0;
    v32 = v71.data;
    if ( *v71.data )
    {
      do
      {
        v33 = v29 * (_DWORD)&v32[119 - (unsigned int)v71.data];
        v29 = *++v32;
        v31 += v33;
      }
      while ( v29 );
      v30 = v71.data;
    }
    v34 = maGlobal.model->materialNodes.heads[v31 & maGlobal.model->materialNodes.tablesizemask];
    if ( v34 )
    {
      while ( 1 )
      {
        v35 = idStr::Cmp(v34->key.data, v30);
        if ( !v35 )
          break;
        if ( v35 <= 0 )
        {
          v34 = v34->next;
          if ( v34 )
            continue;
        }
        goto LABEL_47;
      }
      p_value = &v34->value;
      v69 = &v34->value;
      if ( v34 != (idHashTable<maMaterialNode_s *>::hashnode_s *)-32 )
      {
        v37 = v74.data;
        v38 = *v74.data;
        v39 = 0;
        v40 = v74.data;
        if ( *v74.data )
        {
          do
          {
            v41 = v38 * (_DWORD)&v37[119 - (unsigned int)v74.data];
            v38 = *++v37;
            v39 += v41;
          }
          while ( v38 );
          p_value = v69;
        }
        v42 = maGlobal.model->materialNodes.heads[v39 & maGlobal.model->materialNodes.tablesizemask];
        if ( v42 )
        {
          while ( 1 )
          {
            v43 = idStr::Cmp(v42->key.data, v40);
            if ( !v43 )
              break;
            if ( v43 <= 0 )
            {
              v42 = v42->next;
              if ( v42 )
                continue;
            }
            goto LABEL_47;
          }
          v44 = &v42->value;
          if ( v44 )
            (*v44)->child = *p_value;
        }
      }
LABEL_47:
      v28 = v71.data;
    }
    v45 = *v28;
    v46 = 0;
    v47 = v28;
    if ( *v28 )
    {
      v48 = 119 - (_DWORD)v28;
      do
      {
        v49 = v45 * (_DWORD)&v28[v48];
        v45 = *++v28;
        v46 += v49;
      }
      while ( v45 );
    }
    v50 = maGlobal.model->fileNodes.heads[v46 & maGlobal.model->fileNodes.tablesizemask];
    if ( v50 )
    {
      while ( 1 )
      {
        v51 = idStr::Cmp(v50->key.data, v47);
        if ( !v51 )
          break;
        if ( v51 <= 0 )
        {
          v50 = v50->next;
          if ( v50 )
            continue;
        }
        goto LABEL_67;
      }
      v72 = &v50->value;
      if ( v50 != (idHashTable<maFileNode_t *>::hashnode_s *)-32 )
      {
        v52 = v74.data;
        v53 = *v74.data;
        v54 = v74.data;
        v55 = 0;
        if ( *v74.data )
        {
          do
          {
            v56 = v53 * (_DWORD)&v52[119 - (unsigned int)v74.data];
            v53 = *++v52;
            v55 += v56;
          }
          while ( v53 );
          v54 = v74.data;
        }
        v57 = maGlobal.model->materialNodes.heads[v55 & maGlobal.model->materialNodes.tablesizemask];
        if ( v57 )
        {
          while ( 1 )
          {
            v58 = idStr::Cmp(v57->key.data, v54);
            if ( !v58 )
              break;
            if ( v58 <= 0 )
            {
              v57 = v57->next;
              if ( v57 )
                continue;
            }
            goto LABEL_67;
          }
          v59 = &v57->value;
          if ( v59 )
            (*v59)->file = *v72;
        }
      }
    }
  }
LABEL_67:
  if ( idStr::FindText(v73.data, "iog", 1, 0, v73.len) != -1 )
  {
    model = maGlobal.model;
    v61 = 0;
    if ( maGlobal.model->objects.num > 0 )
    {
      while ( 1 )
      {
        v62 = idStr::Cmp(model->objects.list[v61]->name, v71.data) == 0;
        model = maGlobal.model;
        if ( v62 )
          break;
        if ( ++v61 >= maGlobal.model->objects.num )
          goto LABEL_74;
      }
      v63 = v74.data;
      materialName = maGlobal.model->objects.list[v61]->materialName;
      do
      {
        v65 = *v63;
        *materialName++ = *v63++;
      }
      while ( v65 );
    }
  }
LABEL_74:
  LOBYTE(v80) = 4;
  idStr::FreeData(&token);
  LOBYTE(v80) = 3;
  idStr::FreeData(&v75);
  LOBYTE(v80) = 2;
  idStr::FreeData(&v74);
  LOBYTE(v80) = 1;
  idStr::FreeData(&v73);
  LOBYTE(v80) = 0;
  idStr::FreeData(&v71);
  v80 = -1;
  idStr::FreeData(&v70);
  return 1;
}

// FUNC: struct maModel_s * __cdecl MA_Parse(char const *,char const *,bool)
maModel_s *__cdecl MA_Parse(const char *buffer, char *filename, bool verbose)
{
  maModel_s *v3; // eax
  maModel_s *v4; // eax
  maModel_s *v5; // esi
  maObject_t **list; // edi
  bool v7; // cc
  int i; // eax
  maMaterial_t **v9; // edi
  idList<maMaterial_t *> *p_materials; // esi
  int j; // eax
  maModel_s *model; // eax
  int k; // esi
  int v14; // edi
  maModel_s *v15; // esi
  idToken token; // [esp+10h] [ebp-11Ch] BYREF
  idParser parser; // [esp+60h] [ebp-CCh] BYREF
  int v19; // [esp+128h] [ebp-4h]

  maGlobal.model = 0;
  *(_DWORD *)&maGlobal.verbose = verbose;
  maGlobal.currentObject = 0;
  v3 = (maModel_s *)Memory::Allocate(0x54u);
  v19 = 0;
  if ( v3 )
  {
    maModel_s::maModel_s(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  maGlobal.model = v5;
  list = v5->objects.list;
  v7 = v5->objects.num <= 32;
  v19 = -1;
  v5->objects.granularity = 32;
  v5->objects.size = 32;
  if ( !v7 )
    v5->objects.num = 32;
  v5->objects.list = (maObject_t **)Memory::Allocate(0x80u);
  for ( i = 0; i < v5->objects.num; ++i )
    v5->objects.list[i] = list[i];
  if ( list )
    Memory::Free(list);
  v9 = maGlobal.model->materials.list;
  p_materials = &maGlobal.model->materials;
  v7 = maGlobal.model->materials.num <= 32;
  maGlobal.model->materials.granularity = 32;
  p_materials->size = 32;
  if ( !v7 )
    p_materials->num = 32;
  p_materials->list = (maMaterial_t **)Memory::Allocate(0x80u);
  for ( j = 0; j < p_materials->num; ++j )
    p_materials->list[j] = v9[j];
  if ( v9 )
    Memory::Free(v9);
  idParser::idParser(&parser);
  v19 = 1;
  idParser::SetFlags(&parser, 8);
  idParser::LoadMemory(&parser, buffer, strlen(buffer), filename);
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  LOBYTE(v19) = 2;
  while ( idParser::ReadToken(&parser, &token) )
  {
    if ( idStr::Icmp(token.data, "createNode") )
    {
      if ( !idStr::Icmp(token.data, "connectAttr") )
        MA_ParseConnectAttr(&parser);
    }
    else
    {
      MA_ParseCreateNode(&parser);
    }
  }
  model = maGlobal.model;
  for ( k = 0; k < maGlobal.model->objects.num; ++k )
  {
    v14 = (int)&model->objects.list[k];
    *(_DWORD *)(*(_DWORD *)v14 + 128) = MA_AddMaterial((char *)(*(_DWORD *)v14 + 132));
    model = maGlobal.model;
  }
  MA_ApplyTransformation(model);
  v15 = maGlobal.model;
  LOBYTE(v19) = 1;
  idStr::FreeData(&token);
  v19 = -1;
  idParser::~idParser(&parser);
  return v15;
}

// FUNC: void __cdecl MA_Free(struct maModel_s *)
void __cdecl MA_Free(maModel_s *ma)
{
  int v1; // ebp
  int i; // ebx
  maObject_t *v3; // esi
  int j; // esi
  int tablesize; // ebx
  int v6; // ecx
  int v7; // edx
  idHashTable<maTransform_s *>::hashnode_s **heads; // esi
  idHashTable<maTransform_s *>::hashnode_s *v9; // eax
  void **p_value; // eax
  int k; // ebp
  idHashTable<maTransform_s *>::hashnode_s *v12; // esi
  idPoolStr *v13; // ebx
  int v14; // ebp
  int v15; // ebx
  int v16; // ecx
  int v17; // edx
  idHashTable<maFileNode_t *>::hashnode_s **v18; // esi
  idHashTable<maFileNode_t *>::hashnode_s *v19; // eax
  void **v20; // eax
  int m; // ebp
  idHashTable<maFileNode_t *>::hashnode_s *v22; // esi
  idPoolStr *v23; // ebx
  int v24; // ebx
  int v25; // ebp
  int v26; // ecx
  int v27; // edx
  idHashTable<maMaterialNode_s *>::hashnode_s **v28; // esi
  idHashTable<maMaterialNode_s *>::hashnode_s *v29; // eax
  void **v30; // eax
  int n; // ebp
  idHashTable<maMaterialNode_s *>::hashnode_s *v32; // esi
  idPoolStr *v33; // ebx

  v1 = 0;
  if ( ma )
  {
    for ( i = 0; i < ma->objects.num; ++i )
    {
      v3 = ma->objects.list[i];
      if ( v3->mesh.vertexes )
        Mem_Free(v3->mesh.vertexes);
      if ( v3->mesh.vertTransforms )
        Mem_Free(v3->mesh.vertTransforms);
      if ( v3->mesh.normals )
        Mem_Free(v3->mesh.normals);
      if ( v3->mesh.tvertexes )
        Mem_Free(v3->mesh.tvertexes);
      if ( v3->mesh.edges )
        Mem_Free(v3->mesh.edges);
      if ( v3->mesh.colors )
        Mem_Free(v3->mesh.colors);
      if ( v3->mesh.faces )
        Mem_Free(v3->mesh.faces);
      Mem_Free(v3);
    }
    if ( ma->objects.list )
      Memory::Free(ma->objects.list);
    ma->objects.list = 0;
    ma->objects.num = 0;
    ma->objects.size = 0;
    for ( j = 0; j < ma->materials.num; ++j )
      Mem_Free(ma->materials.list[j]);
    if ( ma->materials.list )
      Memory::Free(ma->materials.list);
    ma->materials.list = 0;
    ma->materials.num = 0;
    ma->materials.size = 0;
    if ( ma->transforms.numentries > 0 )
    {
      do
      {
        if ( v1 < 0
          || v1 > ma->transforms.numentries
          || (tablesize = ma->transforms.tablesize, v6 = 0, v7 = 0, tablesize <= 0) )
        {
LABEL_33:
          p_value = 0;
        }
        else
        {
          heads = ma->transforms.heads;
          while ( 1 )
          {
            v9 = *heads;
            if ( *heads )
              break;
LABEL_32:
            ++v7;
            ++heads;
            if ( v7 >= tablesize )
              goto LABEL_33;
          }
          while ( v6 != v1 )
          {
            v9 = v9->next;
            ++v6;
            if ( !v9 )
              goto LABEL_32;
          }
          p_value = (void **)&v9->value;
        }
        Mem_Free(*p_value);
        ++v1;
      }
      while ( v1 < ma->transforms.numentries );
    }
    for ( k = 0; k < ma->transforms.tablesize; ++k )
    {
      v12 = ma->transforms.heads[k];
      while ( v12 )
      {
        v13 = (idPoolStr *)v12;
        v12 = v12->next;
        idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s(v13);
        Memory::Free(v13);
      }
      ma->transforms.heads[k] = 0;
    }
    v14 = 0;
    for ( ma->transforms.numentries = 0; v14 < ma->fileNodes.numentries; ++v14 )
    {
      if ( v14 < 0 || v14 > ma->fileNodes.numentries || (v15 = ma->fileNodes.tablesize, v16 = 0, v17 = 0, v15 <= 0) )
      {
LABEL_48:
        v20 = 0;
      }
      else
      {
        v18 = ma->fileNodes.heads;
        while ( 1 )
        {
          v19 = *v18;
          if ( *v18 )
            break;
LABEL_47:
          ++v17;
          ++v18;
          if ( v17 >= v15 )
            goto LABEL_48;
        }
        while ( v16 != v14 )
        {
          v19 = v19->next;
          ++v16;
          if ( !v19 )
            goto LABEL_47;
        }
        v20 = (void **)&v19->value;
      }
      Mem_Free(*v20);
    }
    for ( m = 0; m < ma->fileNodes.tablesize; ++m )
    {
      v22 = ma->fileNodes.heads[m];
      while ( v22 )
      {
        v23 = (idPoolStr *)v22;
        v22 = v22->next;
        idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s(v23);
        Memory::Free(v23);
      }
      ma->fileNodes.heads[m] = 0;
    }
    v24 = 0;
    for ( ma->fileNodes.numentries = 0; v24 < ma->materialNodes.numentries; ++v24 )
    {
      if ( v24 < 0
        || v24 > ma->materialNodes.numentries
        || (v25 = ma->materialNodes.tablesize, v26 = 0, v27 = 0, v25 <= 0) )
      {
LABEL_63:
        v30 = 0;
      }
      else
      {
        v28 = ma->materialNodes.heads;
        while ( 1 )
        {
          v29 = *v28;
          if ( *v28 )
            break;
LABEL_62:
          ++v27;
          ++v28;
          if ( v27 >= v25 )
            goto LABEL_63;
        }
        while ( v26 != v24 )
        {
          v29 = v29->next;
          ++v26;
          if ( !v29 )
            goto LABEL_62;
        }
        v30 = (void **)&v29->value;
      }
      Mem_Free(*v30);
    }
    for ( n = 0; n < ma->materialNodes.tablesize; ++n )
    {
      v32 = ma->materialNodes.heads[n];
      while ( v32 )
      {
        v33 = (idPoolStr *)v32;
        v32 = v32->next;
        idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s(v33);
        Memory::Free(v33);
      }
      ma->materialNodes.heads[n] = 0;
    }
    ma->materialNodes.numentries = 0;
    maModel_s::~maModel_s(ma);
    Memory::Free(ma);
  }
}

// FUNC: struct maModel_s * __cdecl MA_Load(char const *)
maModel_s *__cdecl MA_Load(char *fileName)
{
  idFileSystem_vtbl *v1; // eax
  maModel_s *v3; // esi
  idFileSystem_vtbl *v4; // edx
  int v5; // [esp+0h] [ebp-28h] BYREF
  unsigned int timeStamp; // [esp+10h] [ebp-18h] BYREF
  char *buf[2]; // [esp+14h] [ebp-14h] BYREF
  int v8; // [esp+24h] [ebp-4h]

  v1 = fileSystem->__vftable;
  buf[1] = (char *)&v5;
  v1->ReadFile(fileSystem, fileName, (void **)buf, &timeStamp);
  if ( !buf[0] )
    return 0;
  v8 = 0;
  v3 = MA_Parse(buf[0], fileName, 0);
  v3->timeStamp = timeStamp;
  v4 = fileSystem->__vftable;
  v8 = -1;
  v4->FreeFile(fileSystem, buf[0]);
  return v3;
}
