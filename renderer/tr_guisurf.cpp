
// FUNC: void __cdecl R_ListGuis_f(class idCmdArgs const &)
void __cdecl R_ListGuis_f()
{
  uiManager->ListGuis(uiManager);
}

// FUNC: class idScreenRect __cdecl R_ScreenRectFromDrawSurf(struct drawSurf_s *)
idScreenRect *__cdecl R_ScreenRectFromDrawSurf(idScreenRect *result, drawSurf_s *drawSurf)
{
  const srfTriangles_s *geo; // eax
  rvMesh *primBatchMesh; // ecx
  int v4; // edi
  int v5; // ebx
  idScreenRect *v6; // eax
  float x; // [esp+0h] [ebp-3Ch]
  float y; // [esp+4h] [ebp-38h]
  idVec3 ndc; // [esp+14h] [ebp-28h] BYREF
  idVec3 v; // [esp+20h] [ebp-1Ch] BYREF
  idScreenRect r; // [esp+2Ch] [ebp-10h] BYREF

  idScreenRect::Clear(&r);
  geo = drawSurf->geo;
  primBatchMesh = drawSurf->geo->primBatchMesh;
  if ( primBatchMesh )
  {
    rvMesh::ScreenRectFromDrawSurf(
      primBatchMesh,
      &r,
      drawSurf->space->modelMatrix,
      tr.viewDef->worldSpace.modelViewMatrix,
      tr.viewDef->projectionMatrix,
      &tr.viewDef->viewport,
      geo->silTraceVerts);
  }
  else
  {
    v4 = 0;
    if ( geo->numVerts > 0 )
    {
      v5 = 0;
      do
      {
        R_LocalPointToGlobal(drawSurf->space->modelMatrix, &geo->verts[v5].xyz, &v);
        R_GlobalToNormalizedDeviceCoordinates(
          tr.viewDef->worldSpace.modelViewMatrix,
          tr.viewDef->projectionMatrix,
          &v,
          &ndc);
        y = (double)tr.viewDef->viewport.y2
          - (double)(tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1) * (ndc.y + 1.0) * 0.5;
        x = (double)(tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1) * (ndc.x + 1.0) * 0.5;
        idScreenRect::AddPoint(&r, x, y);
        geo = drawSurf->geo;
        ++v4;
        ++v5;
      }
      while ( v4 < drawSurf->geo->numVerts );
    }
  }
  v6 = result;
  *result = r;
  return v6;
}

// FUNC: void __cdecl R_ReloadGuis_f(class idCmdArgs const &)
void __cdecl R_ReloadGuis_f(const idCmdArgs *args)
{
  const char *v1; // eax

  fileSystem->SetIsFileLoadingAllowed(fileSystem, 1);
  if ( args->argc <= 1 )
    v1 = &entityFilter;
  else
    v1 = args->argv[1];
  if ( idStr::Icmp(v1, "all") )
  {
    LOBYTE(args) = 0;
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Checking for changed gui files...\n");
  }
  else
  {
    LOBYTE(args) = 1;
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Reloading all gui files...\n");
  }
  uiManager->Reload(uiManager, (bool)args);
  fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
}

// FUNC: void __cdecl R_SurfaceToTextureAxis(struct srfTriangles_s const *,class idVec3 &,class idVec3 * const)
void __cdecl R_SurfaceToTextureAxis(const srfTriangles_s *tri, idVec3 *origin, idVec3 *axis)
{
  rvMesh *primBatchMesh; // ecx
  int numVerts; // eax
  idVec2 *p_st; // esi
  int v6; // ebx
  int v7; // ecx
  float *p_x; // edx
  double v9; // st7
  double v10; // st7
  int *indexes; // eax
  idDrawVert *verts; // edi
  int v13; // edx
  double v14; // st6
  float *v15; // edx
  int v16; // ecx
  double v17; // st6
  float *v18; // ecx
  float *v19; // esi
  double v20; // st5
  double v21; // st4
  double v22; // st3
  double v23; // st2
  double v24; // st2
  double v25; // st2
  double v26; // st6
  double v27; // st5
  double v28; // st4
  double v29; // st3
  double v30; // st4
  double v31; // st6
  double v32; // st6
  long double v33; // st6
  unsigned __int8 v35; // c2
  unsigned __int8 v36; // c3
  float v37; // eax
  float boundsOrg; // [esp+14h] [ebp-30h]
  float d0; // [esp+1Ch] [ebp-28h]
  float d0_4; // [esp+20h] [ebp-24h]
  float d0_4a; // [esp+20h] [ebp-24h]
  float d0_8; // [esp+24h] [ebp-20h]
  float d0_16; // [esp+2Ch] [ebp-18h]
  float bounds[2][2]; // [esp+30h] [ebp-14h]
  float v45; // [esp+40h] [ebp-4h]
  float tria; // [esp+48h] [ebp+4h]
  float trib; // [esp+48h] [ebp+4h]
  float tric; // [esp+48h] [ebp+4h]

  primBatchMesh = tri->primBatchMesh;
  if ( primBatchMesh )
  {
    rvMesh::SurfaceToTextureAxis(primBatchMesh, origin, axis, tri->silTraceVerts);
    return;
  }
  numVerts = tri->numVerts;
  *(_QWORD *)&bounds[0][0] = 0x497423F0497423F0i64;
  *(_QWORD *)&bounds[1][0] = 0xC97423F0C97423F0ui64;
  if ( numVerts > 0 )
  {
    p_st = &tri->verts->st;
    v6 = numVerts;
    do
    {
      v7 = 0;
      p_x = &p_st->x;
      do
      {
        v9 = *p_x;
        if ( v9 < bounds[0][v7] )
          bounds[0][v7] = *p_x;
        if ( v9 > bounds[1][v7] )
          bounds[1][v7] = v9;
        ++v7;
        ++p_x;
      }
      while ( v7 < 2 );
      p_st += 8;
      --v6;
    }
    while ( v6 );
  }
  boundsOrg = floor((bounds[1][0] + bounds[0][0]) * 0.5);
  v10 = floor((bounds[1][1] + bounds[0][1]) * 0.5);
  indexes = tri->indexes;
  verts = tri->verts;
  v13 = indexes[1] << 6;
  v14 = *(float *)((char *)&verts->xyz.x + v13);
  v15 = (float *)((char *)&verts->xyz.x + v13);
  v16 = *indexes << 6;
  v17 = v14 - *(float *)((char *)&verts->xyz.x + v16);
  v18 = (float *)((char *)&verts->xyz.x + v16);
  v19 = &verts[indexes[2]].xyz.x;
  d0_4 = v15[1] - v18[1];
  v20 = v15[2] - v18[2];
  v21 = v15[14] - v18[14];
  d0_16 = v15[15] - v18[15];
  bounds[0][0] = *v19 - *v18;
  bounds[0][1] = v19[1] - v18[1];
  v22 = v19[2] - v18[2];
  bounds[1][1] = v19[14] - v18[14];
  v23 = v19[15] - v18[15];
  v45 = v23;
  v24 = v23 * v21 - bounds[1][1] * d0_16;
  if ( 0.0 == v24 )
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
  v25 = 1.0 / v24;
  axis->x = (v45 * v17 - bounds[0][0] * d0_16) * v25;
  axis->y = (v45 * d0_4 - bounds[0][1] * d0_16) * v25;
  axis->z = (v45 * v20 - v22 * d0_16) * v25;
  axis[1].x = (bounds[0][0] * v21 - bounds[1][1] * v17) * v25;
  axis[1].y = (bounds[0][1] * v21 - bounds[1][1] * d0_4) * v25;
  axis[1].z = (v22 * v21 - bounds[1][1] * v20) * v25;
  v26 = *v19 - *v15;
  v27 = v19[1] - v15[1];
  v28 = v19[2] - v15[2];
  bounds[0][0] = *v18 - *v15;
  bounds[0][1] = v18[1] - v15[1];
  v29 = v18[2] - v15[2];
  d0 = bounds[0][1] * v28 - v29 * v27;
  d0_4a = v29 * v26 - bounds[0][0] * v28;
  v30 = v26;
  v31 = bounds[0][0] * v27;
  bounds[0][0] = d0;
  d0_8 = v31 - v30 * bounds[0][1];
  bounds[1][0] = d0_8;
  v32 = d0_4a;
  tria = d0_8 * d0_8 + d0_4a * d0_4a + d0 * d0;
  if ( tria != 0.0 )
  {
    v33 = 1.0 / sqrt(tria);
    trib = v33;
    bounds[0][0] = v33 * d0;
    v32 = d0_4a * trib;
    bounds[1][0] = d0_8 * trib;
  }
  if ( v36 | v35 )
  {
    if ( v32 == 0.0 )
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
      goto LABEL_49;
    }
    if ( bounds[1][0] == 0.0 )
    {
      if ( v32 <= 0.0 )
      {
        if ( v32 != -1.0 )
          v32 = -1.0;
      }
      else if ( v32 != 1.0 )
      {
        v32 = 1.0;
      }
      goto LABEL_49;
    }
  }
  else if ( v32 == 0.0 && bounds[1][0] == 0.0 )
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
    goto LABEL_49;
  }
  if ( COERCE_FLOAT(LODWORD(bounds[0][0]) & 0x7FFFFFFF) == 1.0 )
  {
    if ( v32 == 0.0 && bounds[1][0] == 0.0 )
      goto LABEL_49;
    bounds[1][0] = 0.0;
    goto LABEL_48;
  }
  tric = v32;
  if ( COERCE_FLOAT(LODWORD(tric) & 0x7FFFFFFF) == 1.0 )
  {
    if ( bounds[0][0] != 0.0 || bounds[1][0] != 0.0 )
    {
      bounds[1][0] = 0.0;
      bounds[0][0] = 0.0;
    }
    goto LABEL_49;
  }
  if ( COERCE_FLOAT(LODWORD(bounds[1][0]) & 0x7FFFFFFF) == 1.0 && (bounds[0][0] != 0.0 || v32 != 0.0) )
  {
    bounds[0][0] = 0.0;
LABEL_48:
    v32 = 0.0;
  }
LABEL_49:
  v37 = bounds[1][0];
  axis[2].x = bounds[0][0];
  axis[2].y = v32;
  axis[2].z = v37;
  origin->x = (boundsOrg - v18[14]) * axis->x + *v18;
  origin->y = (boundsOrg - v18[14]) * axis->y + v18[1];
  origin->z = (boundsOrg - v18[14]) * axis->z + v18[2];
  origin->x = (v10 - v18[15]) * axis[1].x + origin->x;
  origin->y = (v10 - v18[15]) * axis[1].y + origin->y;
  origin->z = (v10 - v18[15]) * axis[1].z + origin->z;
}

// FUNC: void __cdecl R_RenderGuiSurf(class idUserInterface *,struct drawSurf_s *)
void __cdecl R_RenderGuiSurf(idUserInterface *gui, drawSurf_s *drawSurf)
{
  const viewEntity_s *space; // edx
  idDict *v3; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  idScreenRect *v6; // eax
  int v7; // edi
  float v8; // [esp+1Ch] [ebp-F0h]
  float v9; // [esp+1Ch] [ebp-F0h]
  float v10; // [esp+1Ch] [ebp-F0h]
  float v11; // [esp+1Ch] [ebp-F0h]
  float ratioY; // [esp+34h] [ebp-D8h]
  float ratioX; // [esp+38h] [ebp-D4h]
  int rect; // [esp+3Ch] [ebp-D0h]
  idVec3 origin; // [esp+4Ch] [ebp-C0h] BYREF
  idVec3 axis[3]; // [esp+58h] [ebp-B4h] BYREF
  float guiModelMatrix[16]; // [esp+7Ch] [ebp-90h] BYREF
  idScreenRect result; // [esp+BCh] [ebp-50h] BYREF
  float modelMatrix[16]; // [esp+CCh] [ebp-40h] BYREF

  if ( r_skipGuiShaders.internalVar->integerValue != 1 && tr.guiRecursionLevel != 4 )
  {
    ++tr.pc.c_guiSurfs;
    R_SurfaceToTextureAxis(drawSurf->geo, &origin, axis);
    guiModelMatrix[0] = axis[0].x * 0.0015625;
    guiModelMatrix[12] = origin.x;
    guiModelMatrix[8] = axis[2].x;
    guiModelMatrix[10] = axis[2].z;
    guiModelMatrix[4] = axis[1].x * 0.002083333333333333;
    space = drawSurf->space;
    guiModelMatrix[9] = axis[2].y;
    guiModelMatrix[13] = origin.y;
    guiModelMatrix[1] = axis[0].y * 0.0015625;
    guiModelMatrix[14] = origin.z;
    guiModelMatrix[5] = axis[1].y * 0.002083333333333333;
    guiModelMatrix[3] = 0.0;
    guiModelMatrix[7] = 0.0;
    guiModelMatrix[11] = 0.0;
    guiModelMatrix[15] = 1.0;
    guiModelMatrix[2] = axis[0].z * 0.0015625;
    guiModelMatrix[6] = axis[1].z * 0.002083333333333333;
    myGlMultMatrix(guiModelMatrix, space->modelMatrix, modelMatrix);
    ++tr.guiRecursionLevel;
    idGuiModel::Clear(tr.guiModel);
    gui->Redraw(gui, tr.viewDef->renderView.time);
    idGuiModel::EmitToCurrentView(
      tr.guiModel,
      modelMatrix,
      drawSurf->space->weaponDepthHackInViewID,
      drawSurf->space->entityDef->parms.shaderParms);
    idGuiModel::Clear(tr.guiModel);
    v3 = (idDict *)gui->State(gui);
    Key = idDict::FindKey(v3, "2d_calc");
    if ( Key )
      data = Key->value->data;
    else
      data = "0";
    if ( atoi(data) )
    {
      v6 = R_ScreenRectFromDrawSurf(&result, drawSurf);
      v7 = *(_DWORD *)&v6->x2;
      rect = *(_DWORD *)&v6->x1;
      ratioX = 640.0 / (double)(tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1);
      ratioY = 480.0 / (double)(tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1);
      v8 = (double)(__int16)*(_DWORD *)&v6->x1 * ratioX;
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))gui->SetStateFloat)(gui, "2d_min_x", LODWORD(v8));
      v9 = (double)SHIWORD(rect) * ratioY;
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))gui->SetStateFloat)(gui, "2d_min_y", LODWORD(v9));
      v10 = (double)(__int16)v7 * ratioX;
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))gui->SetStateFloat)(gui, "2d_max_x", LODWORD(v10));
      v11 = (double)SHIWORD(v7) * ratioY;
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))gui->SetStateFloat)(gui, "2d_max_y", LODWORD(v11));
      gui->SetStateBool(gui, "2d_calc", 0);
    }
    --tr.guiRecursionLevel;
  }
}
