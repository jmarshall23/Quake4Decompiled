
// FUNC: ASE_ParseBracedBlock
void __usercall ASE_ParseBracedBlock(void (__cdecl *parser)(const char *)@<edi>)
{
  int v1; // esi

  v1 = 0;
  while ( ASE_GetToken(0) )
  {
    if ( idStr::Cmp(ase.token, "{") )
    {
      if ( idStr::Cmp(ase.token, "}") )
      {
        if ( parser )
          parser(ase.token);
      }
      else
      {
        if ( !--v1 )
          return;
        if ( v1 < 0 )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "Unexpected '}'");
      }
    }
    else
    {
      ++v1;
    }
  }
}

// FUNC: ASE_SkipEnclosingBraces
int ASE_SkipEnclosingBraces()
{
  int v0; // esi
  int result; // eax

  v0 = 0;
  for ( result = ASE_GetToken(0); result; result = ASE_GetToken(0) )
  {
    if ( idStr::Cmp(ase.token, "{") )
    {
      result = idStr::Cmp(ase.token, "}");
      if ( !result )
      {
        if ( !--v0 )
          return result;
        if ( v0 < 0 )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "Unexpected '}'");
      }
    }
    else
    {
      ++v0;
    }
  }
  return result;
}

// FUNC: ASE_KeyMESH_VERTEX_LIST
void __cdecl ASE_KeyMESH_VERTEX_LIST(const char *token)
{
  aseMesh_t *currentMesh; // esi

  currentMesh = ase.currentMesh;
  if ( idStr::Cmp(token, "*MESH_VERTEX") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Unknown token '%s' while parsing MESH_VERTEX_LIST",
      token);
  }
  else
  {
    ASE_GetToken(0);
    ASE_GetToken(0);
    currentMesh->vertexes[ase.currentVertex].x = atof(ase.token);
    ASE_GetToken(0);
    currentMesh->vertexes[ase.currentVertex].y = atof(ase.token);
    ASE_GetToken(0);
    currentMesh->vertexes[ase.currentVertex++].z = atof(ase.token);
    if ( ase.currentVertex > currentMesh->numVertexes )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "ase.currentVertex >= pMesh->numVertexes");
  }
}

// FUNC: ASE_KeyMESH_FACE_LIST
void __cdecl ASE_KeyMESH_FACE_LIST(const char *token)
{
  aseMesh_t *currentMesh; // esi

  currentMesh = ase.currentMesh;
  if ( idStr::Cmp(token, "*MESH_FACE") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Unknown token '%s' while parsing MESH_FACE_LIST",
      token);
  }
  else
  {
    ASE_GetToken(0);
    ASE_GetToken(0);
    ASE_GetToken(0);
    currentMesh->faces[ase.currentFace].vertexNum[0] = atoi(ase.token);
    ASE_GetToken(0);
    ASE_GetToken(0);
    currentMesh->faces[ase.currentFace].vertexNum[2] = atoi(ase.token);
    ASE_GetToken(0);
    ASE_GetToken(0);
    currentMesh->faces[ase.currentFace].vertexNum[1] = atoi(ase.token);
    ASE_GetToken(1);
    ++ase.currentFace;
  }
}

// FUNC: ASE_KeyTFACE_LIST
void __cdecl ASE_KeyTFACE_LIST(const char *token)
{
  aseMesh_t *currentMesh; // esi
  int v2; // edi
  int v3; // ebp
  int v4; // eax

  currentMesh = ase.currentMesh;
  if ( idStr::Cmp(token, "*MESH_TFACE") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Unknown token '%s' in MESH_TFACE",
      token);
  }
  else
  {
    ASE_GetToken(0);
    ASE_GetToken(0);
    v2 = atoi(ase.token);
    ASE_GetToken(0);
    v3 = atoi(ase.token);
    ASE_GetToken(0);
    v4 = atoi(ase.token);
    currentMesh->faces[ase.currentFace].tVertexNum[0] = v2;
    currentMesh->faces[ase.currentFace].tVertexNum[1] = v4;
    currentMesh->faces[ase.currentFace++].tVertexNum[2] = v3;
  }
}

// FUNC: ASE_KeyMESH_TVERTLIST
void __cdecl ASE_KeyMESH_TVERTLIST(const char *token)
{
  aseMesh_t *currentMesh; // edi
  int v2; // eax
  char v3; // cl
  int v4; // eax
  char v5; // cl
  int v6; // eax
  char v7; // cl
  char v[80]; // [esp+8h] [ebp-F0h] BYREF
  char u[80]; // [esp+58h] [ebp-A0h] BYREF
  char w[80]; // [esp+A8h] [ebp-50h]

  currentMesh = ase.currentMesh;
  if ( idStr::Cmp(token, "*MESH_TVERT") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Unknown token '%s' while parsing MESH_TVERTLIST",
      token);
  }
  else
  {
    ASE_GetToken(0);
    ASE_GetToken(0);
    v2 = 0;
    do
    {
      v3 = ase.token[v2];
      u[v2++] = v3;
    }
    while ( v3 );
    ASE_GetToken(0);
    v4 = 0;
    do
    {
      v5 = ase.token[v4];
      v[v4++] = v5;
    }
    while ( v5 );
    ASE_GetToken(0);
    v6 = 0;
    do
    {
      v7 = ase.token[v6];
      w[v6++] = v7;
    }
    while ( v7 );
    currentMesh->tvertexes[ase.currentVertex].x = atof(u);
    currentMesh->tvertexes[ase.currentVertex++].y = 1.0 - atof(v);
    if ( ase.currentVertex > currentMesh->numTVertexes )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "ase.currentVertex > pMesh->numTVertexes");
  }
}

// FUNC: ASE_KeyMAP_DIFFUSE
void __cdecl ASE_KeyMAP_DIFFUSE(const char *token)
{
  char *v1; // eax
  const char *v2; // eax
  aseMaterial_t *v3; // esi
  aseMaterial_t *v4; // esi
  aseMaterial_t *v5; // esi
  aseMaterial_t *v6; // esi
  aseMaterial_t *v7; // esi
  idStr matname; // [esp+8h] [ebp-4Ch] BYREF
  idStr qpath; // [esp+28h] [ebp-2Ch] BYREF
  int v10; // [esp+50h] [ebp-4h]

  if ( idStr::Cmp(token, "*BITMAP") )
  {
    if ( idStr::Cmp(token, "*UVW_U_OFFSET") )
    {
      if ( idStr::Cmp(token, "*UVW_V_OFFSET") )
      {
        if ( idStr::Cmp(token, "*UVW_U_TILING") )
        {
          if ( idStr::Cmp(token, "*UVW_V_TILING") )
          {
            if ( !idStr::Cmp(token, "*UVW_ANGLE") )
            {
              v7 = ase.model->materials.list[ase.model->materials.num - 1];
              ASE_GetToken(0);
              v7->angle = atof(ase.token);
            }
          }
          else
          {
            v6 = ase.model->materials.list[ase.model->materials.num - 1];
            ASE_GetToken(0);
            v6->vTiling = atof(ase.token);
          }
        }
        else
        {
          v5 = ase.model->materials.list[ase.model->materials.num - 1];
          ASE_GetToken(0);
          v5->uTiling = atof(ase.token);
        }
      }
      else
      {
        v4 = ase.model->materials.list[ase.model->materials.num - 1];
        ASE_GetToken(0);
        v4->vOffset = atof(ase.token);
      }
    }
    else
    {
      v3 = ase.model->materials.list[ase.model->materials.num - 1];
      ASE_GetToken(0);
      v3->uOffset = atof(ase.token);
    }
  }
  else
  {
    qpath.len = 0;
    qpath.alloced = 20;
    qpath.data = qpath.baseBuffer;
    qpath.baseBuffer[0] = 0;
    matname.alloced = 20;
    v10 = 1;
    matname.len = 0;
    matname.data = matname.baseBuffer;
    matname.baseBuffer[0] = 0;
    ASE_GetToken(0);
    v1 = strstr(&ase.token[1], "\"");
    if ( v1 )
      *v1 = 0;
    idStr::operator=(&matname, &ase.token[1]);
    idStr::BackSlashesToSlashes(&matname);
    v2 = fileSystem->OSPathToRelativePath(fileSystem, matname.data);
    idStr::operator=(&qpath, v2);
    idStr::Copynz(ase.currentMaterial->name, qpath.data, 128);
    LOBYTE(v10) = 0;
    idStr::FreeData(&matname);
    v10 = -1;
    idStr::FreeData(&qpath);
  }
}

// FUNC: ASE_KeyMATERIAL
void __cdecl ASE_KeyMATERIAL(const char *token)
{
  if ( !idStr::Cmp(token, "*MAP_DIFFUSE") )
    ASE_ParseBracedBlock(ASE_KeyMAP_DIFFUSE);
}

// FUNC: ASE_KeyNODE_TM
void __cdecl ASE_KeyNODE_TM(const char *token)
{
  int m; // esi
  float *v2; // edi
  int k; // esi
  float *v4; // edi
  int j; // esi
  float *v6; // edi
  int i; // esi
  float *v8; // edi

  if ( idStr::Cmp(token, "*TM_ROW0") )
  {
    if ( idStr::Cmp(token, "*TM_ROW1") )
    {
      if ( idStr::Cmp(token, "*TM_ROW2") )
      {
        if ( !idStr::Cmp(token, "*TM_ROW3") )
        {
          for ( i = 196; i < 208; i += 4 )
          {
            ASE_GetToken(0);
            v8 = (float *)&ase.currentObject->name[i];
            *v8 = atof(ase.token);
          }
        }
      }
      else
      {
        for ( j = 184; j < 196; j += 4 )
        {
          ASE_GetToken(0);
          v6 = (float *)&ase.currentObject->name[j];
          *v6 = atof(ase.token);
        }
      }
    }
    else
    {
      for ( k = 172; k < 184; k += 4 )
      {
        ASE_GetToken(0);
        v4 = (float *)&ase.currentObject->name[k];
        *v4 = atof(ase.token);
      }
    }
  }
  else
  {
    for ( m = 160; m < 172; m += 4 )
    {
      ASE_GetToken(0);
      v2 = (float *)&ase.currentObject->name[m];
      *v2 = atof(ase.token);
    }
  }
}

// FUNC: ASE_KeyCFACE_LIST
void __cdecl ASE_KeyCFACE_LIST(const char *token)
{
  aseMesh_t *currentMesh; // edi
  int *v2; // ebp
  int v3; // esi
  int v4; // ecx

  currentMesh = ase.currentMesh;
  if ( idStr::Cmp(token, "*MESH_CFACE") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Unknown token '%s' in MESH_CFACE",
      token);
  }
  else
  {
    ASE_GetToken(0);
    v2 = remap;
    do
    {
      ASE_GetToken(0);
      v3 = atoi(ase.token);
      currentMesh->faces[ase.currentFace].vertexColors[*v2][0] = (unsigned __int64)(currentMesh->cvertexes[v3].x * 255.0);
      currentMesh->faces[ase.currentFace].vertexColors[*v2][1] = (unsigned __int64)(currentMesh->cvertexes[v3].y * 255.0);
      v4 = *v2++ + 21 * ase.currentFace;
      currentMesh->faces->vertexColors[v4][2] = (unsigned __int64)(currentMesh->cvertexes[v3].z * 255.0);
    }
    while ( (int)v2 < (int)&beam_SnapshotName );
    ++ase.currentFace;
  }
}

// FUNC: ASE_KeyMESH_CVERTLIST
void __cdecl ASE_KeyMESH_CVERTLIST(const char *token)
{
  aseMesh_t *currentMesh; // esi
  float *p_x; // ebx
  float *p_y; // ebx
  float *p_z; // ebx

  currentMesh = ase.currentMesh;
  ase.currentMesh->colorsParsed = 1;
  if ( idStr::Cmp(token, "*MESH_VERTCOL") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Unknown token '%s' while parsing MESH_CVERTLIST",
      token);
  }
  else
  {
    ASE_GetToken(0);
    ASE_GetToken(0);
    p_x = &currentMesh->cvertexes[ase.currentVertex].x;
    *p_x = atof(token);
    ASE_GetToken(0);
    p_y = &currentMesh->cvertexes[ase.currentVertex].y;
    *p_y = atof(token);
    ASE_GetToken(0);
    p_z = &currentMesh->cvertexes[ase.currentVertex].z;
    *p_z = atof(token);
    if ( ++ase.currentVertex > currentMesh->numCVertexes )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "ase.currentVertex > pMesh->numCVertexes");
  }
}

// FUNC: ASE_KeyMESH_NORMALS
void __cdecl ASE_KeyMESH_NORMALS(const char *token)
{
  aseMesh_t *currentMesh; // esi
  float *vertexNum; // edi
  int v3; // eax
  int v4; // ebx
  long double v5; // st7
  long double v6; // st4
  long double v7; // st7
  int v8; // eax
  int v9; // ebx
  int v10; // ebp
  int i; // edi
  long double v12; // st7
  float *v13; // ecx
  int v14; // eax
  long double v15; // st4
  long double v16; // st7
  float n; // [esp+Ch] [ebp-Ch]
  float na; // [esp+Ch] [ebp-Ch]
  float n_4; // [esp+10h] [ebp-8h]
  float n_4a; // [esp+10h] [ebp-8h]

  currentMesh = ase.currentMesh;
  ase.currentMesh->normalsParsed = 1;
  vertexNum = (float *)currentMesh->faces[ase.currentFace].vertexNum;
  if ( idStr::Cmp(token, "*MESH_FACENORMAL") )
  {
    if ( !idStr::Cmp(token, "*MESH_VERTEXNORMAL") )
    {
      ASE_GetToken(0);
      v8 = atoi(ase.token);
      v9 = v8;
      if ( v8 >= currentMesh->numVertexes || v8 < 0 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
          common.type,
          "MESH_NORMALS vertex index out of range: %i",
          v8);
      v10 = (int)currentMesh->faces[ase.currentFace - 1].vertexNum;
      for ( i = 0; i < 3; ++i )
      {
        if ( v9 == *(_DWORD *)(v10 + 4 * i) )
          break;
      }
      if ( i == 3 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "MESH_NORMALS vertex index doesn't match face");
      ASE_GetToken(0);
      na = atof(ase.token);
      ASE_GetToken(0);
      n_4a = atof(ase.token);
      ASE_GetToken(0);
      v12 = atof(ase.token);
      v13 = (float *)(v10 + 4 * (3 * i + 9));
      v14 = v10 + 12 * i;
      *v13 = v12 * currentMesh->transform[2].x + n_4a * currentMesh->transform[1].x + na * currentMesh->transform[0].x;
      *(float *)(v14 + 40) = v12 * currentMesh->transform[2].y
                           + n_4a * currentMesh->transform[1].y
                           + na * currentMesh->transform[0].y;
      *(float *)(v14 + 44) = v12 * currentMesh->transform[2].z
                           + n_4a * currentMesh->transform[1].z
                           + na * currentMesh->transform[0].z;
      v15 = *v13 * *v13 + v13[1] * v13[1] + v13[2] * v13[2];
      if ( v15 != 0.0 )
      {
        v16 = 1.0 / sqrt(v15);
        *v13 = v16 * *v13;
        v13[1] = v16 * v13[1];
        v13[2] = v16 * v13[2];
      }
    }
  }
  else
  {
    ASE_GetToken(0);
    v3 = atoi(ase.token);
    v4 = v3;
    if ( v3 >= currentMesh->numFaces || v3 < 0 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "MESH_NORMALS face index out of range: %i",
        v3);
    if ( v4 != ase.currentFace )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "MESH_NORMALS face index != currentFace");
    ASE_GetToken(0);
    n = atof(ase.token);
    ASE_GetToken(0);
    n_4 = atof(ase.token);
    ASE_GetToken(0);
    v5 = atof(ase.token);
    vertexNum[6] = v5 * currentMesh->transform[2].x
                 + n_4 * currentMesh->transform[1].x
                 + n * currentMesh->transform[0].x;
    vertexNum[7] = v5 * currentMesh->transform[2].y
                 + n_4 * currentMesh->transform[1].y
                 + n * currentMesh->transform[0].y;
    vertexNum[8] = v5 * currentMesh->transform[2].z
                 + n_4 * currentMesh->transform[1].z
                 + n * currentMesh->transform[0].z;
    v6 = vertexNum[6] * vertexNum[6] + vertexNum[7] * vertexNum[7] + vertexNum[8] * vertexNum[8];
    if ( v6 != 0.0 )
    {
      v7 = 1.0 / sqrt(v6);
      vertexNum[6] = v7 * vertexNum[6];
      vertexNum[7] = v7 * vertexNum[7];
      vertexNum[8] = v7 * vertexNum[8];
    }
    ++ase.currentFace;
  }
}

// FUNC: ASE_KeyMESH
void __cdecl ASE_KeyMESH(const char *token)
{
  aseMesh_t *currentMesh; // esi
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax

  currentMesh = ase.currentMesh;
  if ( idStr::Cmp(token, "*TIMEVALUE") )
  {
    if ( idStr::Cmp(token, "*MESH_NUMVERTEX") )
    {
      if ( idStr::Cmp(token, "*MESH_NUMTVERTEX") )
      {
        if ( idStr::Cmp(token, "*MESH_NUMCVERTEX") )
        {
          if ( idStr::Cmp(token, "*MESH_NUMFACES") )
          {
            if ( idStr::Cmp(token, "*MESH_NUMTVFACES") )
            {
              if ( idStr::Cmp(token, "*MESH_NUMCVFACES") )
              {
                if ( idStr::Cmp(token, "*MESH_VERTEX_LIST") )
                {
                  if ( idStr::Cmp(token, "*MESH_TVERTLIST") )
                  {
                    if ( idStr::Cmp(token, "*MESH_CVERTLIST") )
                    {
                      if ( idStr::Cmp(token, "*MESH_FACE_LIST") )
                      {
                        if ( idStr::Cmp(token, "*MESH_TFACELIST") )
                        {
                          if ( idStr::Cmp(token, "*MESH_CFACELIST") )
                          {
                            if ( !idStr::Cmp(token, "*MESH_NORMALS") )
                            {
                              if ( !currentMesh->faces )
                                (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
                                  common.type,
                                  "*MESH_NORMALS before *MESH_FACE_LIST");
                              ase.currentFace = 0;
                              if ( ase.verbose )
                                (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
                                  common.type,
                                  ".....parsing MESH_NORMALS\n");
                              ASE_ParseBracedBlock(ASE_KeyMESH_NORMALS);
                            }
                          }
                          else
                          {
                            if ( !currentMesh->faces )
                              (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
                                common.type,
                                "*MESH_CFACELIST before *MESH_FACE_LIST");
                            ase.currentFace = 0;
                            if ( ase.verbose )
                              (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
                                common.type,
                                ".....parsing MESH_CFACE_LIST\n");
                            ASE_ParseBracedBlock(ASE_KeyCFACE_LIST);
                          }
                        }
                        else
                        {
                          if ( !currentMesh->faces )
                            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
                              common.type,
                              "*MESH_TFACELIST before *MESH_FACE_LIST");
                          ase.currentFace = 0;
                          if ( ase.verbose )
                            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
                              common.type,
                              ".....parsing MESH_TFACE_LIST\n");
                          ASE_ParseBracedBlock(ASE_KeyTFACE_LIST);
                        }
                      }
                      else
                      {
                        currentMesh->faces = (aseFace_t *)Mem_Alloc(84 * currentMesh->numFaces, 0xEu);
                        ase.currentFace = 0;
                        if ( ase.verbose )
                          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
                            common.type,
                            ".....parsing MESH_FACE_LIST\n");
                        ASE_ParseBracedBlock(ASE_KeyMESH_FACE_LIST);
                      }
                    }
                    else
                    {
                      ase.currentVertex = 0;
                      currentMesh->cvertexes = (idVec3 *)Mem_Alloc(12 * currentMesh->numCVertexes, 0xEu);
                      if ( ase.verbose )
                        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
                          common.type,
                          ".....parsing MESH_CVERTLIST\n");
                      ASE_ParseBracedBlock(ASE_KeyMESH_CVERTLIST);
                    }
                  }
                  else
                  {
                    ase.currentVertex = 0;
                    currentMesh->tvertexes = (idVec2 *)Mem_Alloc(8 * currentMesh->numTVertexes, 0xEu);
                    if ( ase.verbose )
                      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
                        common.type,
                        ".....parsing MESH_TVERTLIST\n");
                    ASE_ParseBracedBlock(ASE_KeyMESH_TVERTLIST);
                  }
                }
                else
                {
                  currentMesh->vertexes = (idVec3 *)Mem_Alloc(12 * currentMesh->numVertexes, 0xEu);
                  ase.currentVertex = 0;
                  if ( ase.verbose )
                    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
                      common.type,
                      ".....parsing MESH_VERTEX_LIST\n");
                  ASE_ParseBracedBlock(ASE_KeyMESH_VERTEX_LIST);
                }
              }
              else
              {
                ASE_GetToken(0);
                v8 = atoi(ase.token);
                currentMesh->numCVFaces = v8;
                if ( ase.verbose )
                  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                    common.type,
                    ".....num cvfaces: %d\n",
                    v8);
                if ( currentMesh->numTVFaces != currentMesh->numFaces )
                  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
                    common.type,
                    "MESH_NUMCVFACES != MESH_NUMFACES");
              }
            }
            else
            {
              ASE_GetToken(0);
              v7 = atoi(ase.token);
              currentMesh->numTVFaces = v7;
              if ( ase.verbose )
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  ".....num tvfaces: %d\n",
                  v7);
              if ( currentMesh->numTVFaces != currentMesh->numFaces )
                (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
                  common.type,
                  "MESH_NUMTVFACES != MESH_NUMFACES");
            }
          }
          else
          {
            ASE_GetToken(0);
            v6 = atoi(ase.token);
            currentMesh->numFaces = v6;
            if ( ase.verbose )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                common.type,
                ".....num faces: %d\n",
                v6);
          }
        }
        else
        {
          ASE_GetToken(0);
          v5 = atoi(ase.token);
          currentMesh->numCVertexes = v5;
          if ( ase.verbose )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              ".....num cvertexes: %d\n",
              v5);
        }
      }
      else
      {
        ASE_GetToken(0);
        v4 = atoi(ase.token);
        currentMesh->numTVertexes = v4;
        if ( ase.verbose )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            ".....num tvertexes: %d\n",
            v4);
      }
    }
    else
    {
      ASE_GetToken(0);
      v3 = atoi(ase.token);
      currentMesh->numVertexes = v3;
      if ( ase.verbose )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          ".....num vertexes: %d\n",
          v3);
    }
  }
  else
  {
    ASE_GetToken(0);
    v2 = atoi(ase.token);
    currentMesh->timeValue = v2;
    if ( ase.verbose )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        ".....timevalue: %d\n",
        v2);
  }
}

// FUNC: ASE_KeyMATERIAL_LIST
void __cdecl ASE_KeyMATERIAL_LIST(const char *token)
{
  idList<aseMaterial_t *> *p_materials; // esi
  int granularity; // eax
  bool v3; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v7; // ecx
  aseMaterial_t **list; // edi
  int j; // eax

  if ( idStr::Cmp(token, "*MATERIAL_COUNT") )
  {
    if ( !idStr::Cmp(token, "*MATERIAL") )
    {
      if ( ase.verbose )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "..material %d\n",
          ase.model->materials.num);
      ase.currentMaterial = (aseMaterial_t *)Mem_Alloc(148, 0xEu);
      memset(ase.currentMaterial, 0, sizeof(aseMaterial_t));
      ase.currentMaterial->uTiling = 1.0;
      ase.currentMaterial->vTiling = 1.0;
      p_materials = &ase.model->materials;
      if ( !ase.model->materials.list )
      {
        granularity = ase.model->materials.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != ase.model->materials.size )
          {
            v3 = granularity < p_materials->num;
            ase.model->materials.size = granularity;
            if ( v3 )
              p_materials->num = granularity;
            p_materials->list = (aseMaterial_t **)Memory::Allocate(4 * granularity);
            for ( i = 0; i < p_materials->num; ++i )
              p_materials->list[i] = *(aseMaterial_t **)(4 * i);
          }
        }
        else
        {
          ase.model->materials.list = 0;
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
        v7 = size + p_materials->granularity - (size + p_materials->granularity) % p_materials->granularity;
        if ( v7 > 0 )
        {
          if ( v7 != p_materials->size )
          {
            list = p_materials->list;
            p_materials->size = v7;
            if ( v7 < num )
              p_materials->num = v7;
            p_materials->list = (aseMaterial_t **)Memory::Allocate(4 * v7);
            for ( j = 0; j < p_materials->num; ++j )
              p_materials->list[j] = list[j];
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
      p_materials->list[p_materials->num++] = ase.currentMaterial;
      ASE_ParseBracedBlock(ASE_KeyMATERIAL);
    }
  }
  else
  {
    ASE_GetToken(0);
    if ( ase.verbose )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "..num materials: %s\n",
        ase.token);
  }
}

// FUNC: ASE_KeyMESH_ANIMATION
void __cdecl ASE_KeyMESH_ANIMATION(const char *token)
{
  aseMesh_t *v1; // ebx
  idList<aseMesh_t *> *p_frames; // esi
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v8; // ecx
  aseMesh_t **list; // edi
  int j; // eax

  if ( idStr::Cmp(token, "*MESH") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Unknown token '%s' while parsing MESH_ANIMATION",
      token);
  }
  else
  {
    if ( ase.verbose )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "...found MESH\n");
    v1 = (aseMesh_t *)Mem_Alloc(96, 0xEu);
    memset(v1, 0, sizeof(aseMesh_t));
    p_frames = &ase.currentObject->frames;
    ase.currentMesh = v1;
    if ( !ase.currentObject->frames.list )
    {
      granularity = ase.currentObject->frames.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != ase.currentObject->frames.size )
        {
          v4 = granularity < p_frames->num;
          ase.currentObject->frames.size = granularity;
          if ( v4 )
            p_frames->num = granularity;
          p_frames->list = (aseMesh_t **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < p_frames->num; ++i )
            p_frames->list[i] = *(aseMesh_t **)(4 * i);
        }
      }
      else
      {
        ase.currentObject->frames.list = 0;
        p_frames->num = 0;
        p_frames->size = 0;
      }
    }
    num = p_frames->num;
    size = p_frames->size;
    if ( p_frames->num == size )
    {
      if ( !p_frames->granularity )
        p_frames->granularity = 16;
      v8 = size + p_frames->granularity - (size + p_frames->granularity) % p_frames->granularity;
      if ( v8 > 0 )
      {
        if ( v8 != p_frames->size )
        {
          list = p_frames->list;
          p_frames->size = v8;
          if ( v8 < num )
            p_frames->num = v8;
          p_frames->list = (aseMesh_t **)Memory::Allocate(4 * v8);
          for ( j = 0; j < p_frames->num; ++j )
            p_frames->list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( p_frames->list )
          Memory::Free(p_frames->list);
        p_frames->list = 0;
        p_frames->num = 0;
        p_frames->size = 0;
      }
    }
    p_frames->list[p_frames->num++] = v1;
    ASE_ParseBracedBlock(ASE_KeyMESH);
  }
}

// FUNC: ASE_KeyGEOMOBJECT
void __cdecl ASE_KeyGEOMOBJECT(const char *token)
{
  aseObject_t *currentObject; // edi

  currentObject = ase.currentObject;
  if ( !idStr::Cmp(token, "*NODE_NAME") )
  {
    ASE_GetToken(1);
    if ( ase.verbose )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, " %s\n", ase.token);
    idStr::Copynz(currentObject->name, ase.token, 128);
    return;
  }
  if ( !idStr::Cmp(token, "*NODE_PARENT") )
  {
LABEL_19:
    ASE_GetToken(1);
    return;
  }
  if ( !idStr::Cmp(token, "*NODE_TM") || !idStr::Cmp(token, "*TM_ANIMATION") )
  {
    ASE_ParseBracedBlock(ASE_KeyNODE_TM);
    return;
  }
  if ( !idStr::Cmp(token, "*MESH") )
  {
    ase.currentMesh = &ase.currentObject->mesh;
    ase.currentObject->mesh.timeValue = 0;
    ASE_ParseBracedBlock(ASE_KeyMESH);
    return;
  }
  if ( !idStr::Cmp(token, "*MATERIAL_REF") )
  {
    ASE_GetToken(0);
    currentObject->materialRef = atoi(ase.token);
    return;
  }
  if ( idStr::Cmp(token, "*MESH_ANIMATION") )
  {
    if ( idStr::Cmp(token, "*PROP_MOTIONBLUR")
      && idStr::Cmp(token, "*PROP_CASTSHADOW")
      && idStr::Cmp(token, "*PROP_RECVSHADOW") )
    {
      return;
    }
    goto LABEL_19;
  }
  if ( ase.verbose )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "..found MESH_ANIMATION\n");
  ASE_ParseBracedBlock(ASE_KeyMESH_ANIMATION);
}

// FUNC: void __cdecl ASE_ParseGeomObject(void)
void __cdecl ASE_ParseGeomObject()
{
  aseObject_t *v0; // ebp
  idList<aseObject_t *> *p_objects; // esi
  int granularity; // eax
  bool v3; // cc
  int i; // eax
  int size; // eax
  int num; // ebx
  int v7; // ecx
  aseObject_t **list; // edi
  int j; // eax
  aseMesh_t **v10; // esi
  int k; // eax

  if ( ase.verbose )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "GEOMOBJECT");
  v0 = (aseObject_t *)Mem_Alloc(244, 0xEu);
  memset(v0, 0, sizeof(aseObject_t));
  p_objects = &ase.model->objects;
  if ( !ase.model->objects.list )
  {
    granularity = ase.model->objects.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != ase.model->objects.size )
      {
        v3 = granularity < p_objects->num;
        ase.model->objects.size = granularity;
        if ( v3 )
          p_objects->num = granularity;
        p_objects->list = (aseObject_t **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < p_objects->num; ++i )
          p_objects->list[i] = *(aseObject_t **)(4 * i);
      }
    }
    else
    {
      ase.model->objects.list = 0;
      p_objects->num = 0;
      p_objects->size = 0;
    }
  }
  size = p_objects->size;
  num = p_objects->num;
  if ( p_objects->num == size )
  {
    if ( !p_objects->granularity )
      p_objects->granularity = 16;
    v7 = size + p_objects->granularity - (size + p_objects->granularity) % p_objects->granularity;
    if ( v7 > 0 )
    {
      if ( v7 != p_objects->size )
      {
        list = p_objects->list;
        p_objects->size = v7;
        if ( v7 < num )
          p_objects->num = v7;
        p_objects->list = (aseObject_t **)Memory::Allocate(4 * v7);
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
  p_objects->list[p_objects->num++] = v0;
  ase.currentObject = v0;
  v10 = v0->frames.list;
  v3 = v0->frames.num <= 32;
  v0->frames.granularity = 32;
  v0->frames.size = 32;
  if ( !v3 )
    v0->frames.num = 32;
  v0->frames.list = (aseMesh_t **)Memory::Allocate(0x80u);
  for ( k = 0; k < v0->frames.num; ++k )
    v0->frames.list[k] = v10[k];
  if ( v10 )
    Memory::Free(v10);
  ASE_ParseBracedBlock(ASE_KeyGEOMOBJECT);
}

// FUNC: ASE_KeyGROUP
void __cdecl ASE_KeyGROUP(const char *token)
{
  if ( !idStr::Cmp(token, "*GEOMOBJECT") )
    ASE_ParseGeomObject();
}

// FUNC: struct aseModel_s * __cdecl ASE_Parse(char const *,bool)
aseModel_s *__cdecl ASE_Parse(const char *buffer, bool verbose)
{
  aseModel_s *v2; // eax
  aseObject_t **list; // edi
  idList<aseObject_t *> *p_objects; // esi
  bool v5; // cc
  int i; // eax
  aseMaterial_t **v7; // edi
  idList<aseMaterial_t *> *p_materials; // esi
  int j; // eax

  memset(&ase, 0, sizeof(ase));
  ase.verbose = verbose;
  ase.buffer = buffer;
  ase.len = strlen(buffer);
  ase.curpos = buffer;
  ase.currentObject = 0;
  v2 = (aseModel_s *)Memory::Allocate(0x24u);
  if ( v2 )
  {
    v2->materials.granularity = 16;
    v2->materials.list = 0;
    v2->materials.num = 0;
    v2->materials.size = 0;
    v2->objects.granularity = 16;
    v2->objects.list = 0;
    v2->objects.num = 0;
    v2->objects.size = 0;
  }
  else
  {
    v2 = 0;
  }
  ase.model = v2;
  v2->timeStamp = 0;
  v2->materials.num = 0;
  v2->materials.size = 0;
  v2->materials.granularity = 0;
  v2->materials.list = 0;
  v2->objects.num = 0;
  v2->objects.size = 0;
  v2->objects.granularity = 0;
  v2->objects.list = 0;
  list = ase.model->objects.list;
  p_objects = &ase.model->objects;
  v5 = ase.model->objects.num <= 32;
  ase.model->objects.granularity = 32;
  p_objects->size = 32;
  if ( !v5 )
    p_objects->num = 32;
  p_objects->list = (aseObject_t **)Memory::Allocate(0x80u);
  for ( i = 0; i < p_objects->num; ++i )
    p_objects->list[i] = list[i];
  if ( list )
    Memory::Free(list);
  v7 = ase.model->materials.list;
  p_materials = &ase.model->materials;
  v5 = ase.model->materials.num <= 32;
  ase.model->materials.granularity = 32;
  p_materials->size = 32;
  if ( !v5 )
    p_materials->num = 32;
  p_materials->list = (aseMaterial_t **)Memory::Allocate(0x80u);
  for ( j = 0; j < p_materials->num; ++j )
    p_materials->list[j] = v7[j];
  if ( v7 )
    Memory::Free(v7);
  if ( ASE_GetToken(0) )
  {
    while ( 1 )
    {
      if ( !idStr::Cmp(ase.token, "*3DSMAX_ASCIIEXPORT") || !idStr::Cmp(ase.token, "*COMMENT") )
      {
        ASE_GetToken(1);
        goto LABEL_35;
      }
      if ( !idStr::Cmp(ase.token, "*SCENE") )
        goto LABEL_25;
      if ( idStr::Cmp(ase.token, "*GROUP") )
        break;
      ASE_GetToken(0);
      ASE_ParseBracedBlock(ASE_KeyGROUP);
LABEL_35:
      if ( !ASE_GetToken(0) )
        return ase.model;
    }
    if ( idStr::Cmp(ase.token, "*SHAPEOBJECT") && idStr::Cmp(ase.token, "*CAMERAOBJECT") )
    {
      if ( idStr::Cmp(ase.token, "*MATERIAL_LIST") )
      {
        if ( idStr::Cmp(ase.token, "*GEOMOBJECT") )
        {
          if ( ase.token[0] )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "Unknown token '%s'\n",
              ase.token);
        }
        else
        {
          ASE_ParseGeomObject();
        }
      }
      else
      {
        if ( ase.verbose )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "MATERIAL_LIST\n");
        ASE_ParseBracedBlock(ASE_KeyMATERIAL_LIST);
      }
      goto LABEL_35;
    }
LABEL_25:
    ASE_SkipEnclosingBraces();
    goto LABEL_35;
  }
  return ase.model;
}

// FUNC: struct aseModel_s * __cdecl ASE_Load(char const *)
aseModel_s *__cdecl ASE_Load(const char *fileName)
{
  aseModel_s *result; // eax
  aseModel_s *v2; // esi
  char *buf; // [esp+Ch] [ebp-8h] BYREF
  unsigned int timeStamp; // [esp+10h] [ebp-4h] BYREF

  fileSystem->ReadFile(fileSystem, fileName, (void **)&buf, &timeStamp);
  result = (aseModel_s *)buf;
  if ( buf )
  {
    v2 = ASE_Parse(buf, 0);
    v2->timeStamp = timeStamp;
    fileSystem->FreeFile(fileSystem, buf);
    return v2;
  }
  return result;
}

// FUNC: void __cdecl ASE_Free(struct aseModel_s *)
void __cdecl ASE_Free(aseModel_s *ase)
{
  int v2; // ebx
  int v3; // esi
  bool v4; // zf
  bool v5; // sf
  aseObject_t *v6; // edi
  void **v7; // esi
  int i; // esi
  aseModel_s *asea; // [esp+Ch] [ebp+4h]

  v2 = 0;
  if ( ase )
  {
    v3 = 0;
    v4 = ase->objects.num == 0;
    v5 = ase->objects.num < 0;
    asea = 0;
    if ( !v5 && !v4 )
    {
      do
      {
        v6 = ase->objects.list[v3];
        if ( v6->frames.num > 0 )
        {
          do
          {
            v7 = (void **)v6->frames.list[v2];
            if ( v7[20] )
              Mem_Free(v7[20]);
            if ( v7[21] )
              Mem_Free(v7[21]);
            if ( v7[22] )
              Mem_Free(v7[22]);
            if ( v7[23] )
              Mem_Free(v7[23]);
            Mem_Free(v7);
            ++v2;
          }
          while ( v2 < v6->frames.num );
          v3 = (int)asea;
        }
        if ( v6->frames.list )
          Memory::Free(v6->frames.list);
        v6->frames.list = 0;
        v6->frames.num = 0;
        v6->frames.size = 0;
        if ( v6->mesh.vertexes )
          Mem_Free(v6->mesh.vertexes);
        if ( v6->mesh.tvertexes )
          Mem_Free(v6->mesh.tvertexes);
        if ( v6->mesh.cvertexes )
          Mem_Free(v6->mesh.cvertexes);
        if ( v6->mesh.faces )
          Mem_Free(v6->mesh.faces);
        Mem_Free(v6);
        ++v3;
        v2 = 0;
        asea = (aseModel_s *)v3;
      }
      while ( v3 < ase->objects.num );
    }
    if ( ase->objects.list )
      Memory::Free(ase->objects.list);
    ase->objects.list = 0;
    ase->objects.num = 0;
    ase->objects.size = 0;
    for ( i = 0; i < ase->materials.num; ++i )
      Mem_Free(ase->materials.list[i]);
    if ( ase->materials.list )
      Memory::Free(ase->materials.list);
    ase->materials.list = 0;
    ase->materials.num = 0;
    ase->materials.size = 0;
    aseModel_s::~aseModel_s(ase);
    Memory::Free(ase);
  }
}
