
// FUNC: void __cdecl RB_EnterWeaponDepthHack(void)
void __cdecl RB_EnterWeaponDepthHack()
{
  qglDepthRange(0.0, 0.5);
  backEnd.projectionMatrix[14] = backEnd.projectionMatrix[14] * 0.25;
  qglMatrixMode(0x1701u);
  qglLoadMatrixf(backEnd.projectionMatrix);
  backEnd.mvpSpace = 0;
  qglMatrixMode(0x1700u);
}

// FUNC: void __cdecl RB_EnterModelDepthHack(float)
void __cdecl RB_EnterModelDepthHack(float depth)
{
  qglDepthRange(0.0, 1.0);
  backEnd.projectionMatrix[14] = backEnd.projectionMatrix[14] - depth;
  qglMatrixMode(0x1701u);
  qglLoadMatrixf(backEnd.projectionMatrix);
  backEnd.mvpSpace = 0;
  qglMatrixMode(0x1700u);
}

// FUNC: void __cdecl RB_LeaveDepthHack(void)
void __cdecl RB_LeaveDepthHack()
{
  qglDepthRange(0.0, 1.0);
  backEnd.projectionMatrix[14] = backEnd.viewDef->projectionMatrix[14];
  qglMatrixMode(0x1701u);
  qglLoadMatrixf(backEnd.projectionMatrix);
  backEnd.mvpSpace = 0;
  qglMatrixMode(0x1700u);
}

// FUNC: void __cdecl RB_GetShaderTextureMatrix(float const *,struct textureStage_t const *,float * const)
void __cdecl RB_GetShaderTextureMatrix(const float *shaderRegisters, const textureStage_t *texture, float *matrix)
{
  int v3; // eax
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c2
  int v8; // edx
  double v9; // st7
  unsigned __int8 v11; // c0
  unsigned __int8 v12; // c2

  *matrix = shaderRegisters[texture->matrix[0][0]];
  matrix[4] = shaderRegisters[texture->matrix[0][1]];
  matrix[8] = 0.0;
  v3 = texture->matrix[0][2];
  v4 = shaderRegisters[v3];
  matrix[12] = shaderRegisters[v3];
  if ( v6 | v7 || v4 > 40.0 )
    matrix[12] = v4 - (double)(int)v4;
  matrix[1] = shaderRegisters[texture->matrix[1][0]];
  matrix[5] = shaderRegisters[texture->matrix[1][1]];
  matrix[9] = 0.0;
  v8 = texture->matrix[1][2];
  v9 = shaderRegisters[v8];
  matrix[13] = shaderRegisters[v8];
  if ( v11 | v12 || v9 > 40.0 )
    matrix[13] = v9 - (double)(int)v9;
  matrix[2] = 0.0;
  matrix[6] = 0.0;
  matrix[14] = 0.0;
  matrix[3] = 0.0;
  matrix[7] = 0.0;
  matrix[11] = 0.0;
  matrix[10] = 1.0;
  matrix[15] = 1.0;
}

// FUNC: void __cdecl RB_LoadShaderTextureMatrix(float const *,struct textureStage_t const *)
void __cdecl RB_LoadShaderTextureMatrix(const float *shaderRegisters, const textureStage_t *texture)
{
  float matrix[16]; // [esp+0h] [ebp-40h] BYREF

  RB_GetShaderTextureMatrix(shaderRegisters, texture, matrix);
  qglMatrixMode(0x1702u);
  qglLoadMatrixf(matrix);
  qglMatrixMode(0x1700u);
}

// FUNC: void __cdecl RB_FinishStageTexture(struct textureStage_t const *,struct drawSurf_s const *)
void __cdecl RB_FinishStageTexture(const textureStage_t *texture, const drawSurf_s *surf)
{
  texgen_t texgen; // eax
  char *v3; // eax

  texgen = texture->texgen;
  if ( texgen == TG_DIFFUSE_CUBE || texgen == TG_SKYBOX_CUBE || texgen == TG_WOBBLESKY_CUBE )
  {
    v3 = idVertexCache::Position(&vertexCache, surf->geo->ambientCache);
    qglTexCoordPointer(2, 0x1406u, 64, v3 + 56);
  }
  if ( texture->texgen == TG_REFLECT_CUBE )
  {
    qglDisable(0xC60u);
    qglDisable(0xC61u);
    qglDisable(0xC62u);
    qglTexGenf(0x2000u, 0x2500u, 9217.0);
    qglTexGenf(0x2001u, 0x2500u, 9217.0);
    qglTexGenf(0x2002u, 0x2500u, 9217.0);
    GL_DisableVertexAttribState(2u);
    qglMatrixMode(0x1702u);
    qglLoadIdentity();
    qglMatrixMode(0x1700u);
  }
  if ( texture->hasMatrix )
  {
    qglMatrixMode(0x1702u);
    qglLoadIdentity();
    qglMatrixMode(0x1700u);
  }
}

// FUNC: void __cdecl RB_BeginDrawingView(void)
void __cdecl RB_BeginDrawingView()
{
  qglMatrixMode(0x1701u);
  qglLoadMatrixf(backEnd.viewDef->projectionMatrix);
  qglMatrixMode(0x1700u);
  qglViewport(
    tr.viewportOffset[0] + backEnd.viewDef->viewport.x1,
    tr.viewportOffset[1] + backEnd.viewDef->viewport.y1,
    backEnd.viewDef->viewport.x2 - backEnd.viewDef->viewport.x1 + 1,
    backEnd.viewDef->viewport.y2 - backEnd.viewDef->viewport.y1 + 1);
  qglScissor(
    tr.viewportOffset[0] + backEnd.viewDef->scissor.x1 + backEnd.viewDef->viewport.x1,
    tr.viewportOffset[1] + backEnd.viewDef->scissor.y1 + backEnd.viewDef->viewport.y1,
    backEnd.viewDef->scissor.x2 - backEnd.viewDef->scissor.x1 + 1,
    backEnd.viewDef->scissor.y2 - backEnd.viewDef->scissor.y1 + 1);
  backEnd.currentScissor = backEnd.viewDef->scissor;
  GL_State(0x10000);
  if ( backEnd.viewDef->viewEntitys )
  {
    qglStencilMask(0xFFu);
    qglClearStencil(1 << (LOBYTE(glConfig.stencilBits) - 1));
    qglClear(0x500u);
    qglEnable(0xB71u);
  }
  else
  {
    qglDisable(0xB71u);
    qglDisable(0xB90u);
  }
  backEnd.glState.faceCulling = -1;
  GL_Cull(0);
}

// FUNC: void __cdecl RB_DrawElementsImmediate(struct srfTriangles_s const *)
void __cdecl RB_DrawElementsImmediate(const srfTriangles_s *tri)
{
  srfTriangles_s *ambientSurface; // eax
  int i; // edi

  ++backEnd.pc.c_drawElements;
  backEnd.pc.c_drawIndexes += tri->numIndexes;
  backEnd.pc.c_drawVertexes += tri->numVerts;
  ambientSurface = tri->ambientSurface;
  if ( ambientSurface )
  {
    if ( tri->indexes == ambientSurface->indexes )
      backEnd.pc.c_drawRefIndexes += tri->numIndexes;
    if ( tri->verts == tri->ambientSurface->verts )
      backEnd.pc.c_drawRefVertexes += tri->numVerts;
  }
  if ( tri->numIndexes && tri->numVerts && tri->verts )
  {
    qglBegin(4u);
    for ( i = 0; i < tri->numIndexes; ++i )
    {
      qglTexCoord2fv(&tri->verts[tri->indexes[i]].st.x);
      qglVertex3fv(&tri->verts[tri->indexes[i]].xyz.x);
    }
    qglEnd();
  }
}

// FUNC: void __cdecl RB_DrawElementsWithCounters(struct srfTriangles_s const *)
void __cdecl RB_DrawElementsWithCounters(const srfTriangles_s *tri)
{
  rvMesh *primBatchMesh; // edi
  int *indexes; // eax
  srfTriangles_s *ambientSurface; // eax
  int numIndexes; // edi
  char *v5; // eax
  int v6; // eax

  primBatchMesh = tri->primBatchMesh;
  if ( primBatchMesh )
  {
    if ( !primBatchMesh->m_drawSetUp )
      rvMesh::SetupForDrawRender(primBatchMesh, 0);
    indexes = tri->indexes;
    if ( indexes )
      rvMesh::Draw(primBatchMesh, tri->skinToModelTransforms, indexes, tri->numIndexes, 0);
    else
      rvMesh::Draw(primBatchMesh, tri->skinToModelTransforms, 0);
    return;
  }
  ++backEnd.pc.c_drawElements;
  backEnd.pc.c_drawIndexes += tri->numIndexes;
  backEnd.pc.c_drawVertexes += tri->numVerts;
  ambientSurface = tri->ambientSurface;
  if ( ambientSurface )
  {
    if ( tri->indexes == ambientSurface->indexes )
      backEnd.pc.c_drawRefIndexes += tri->numIndexes;
    if ( tri->verts == tri->ambientSurface->verts )
      backEnd.pc.c_drawRefVertexes += tri->numVerts;
  }
  if ( tri->indexCache )
  {
    if ( r_useIndexBuffers.internalVar->integerValue )
    {
      numIndexes = 3;
      if ( !r_singleTriangle.internalVar->integerValue )
        numIndexes = tri->numIndexes;
      v5 = idVertexCache::Position(&vertexCache, tri->indexCache);
      qglDrawElements(4u, numIndexes, 0x1405u, v5);
      backEnd.pc.c_vboIndexes += tri->numIndexes;
      return;
    }
  }
  else if ( r_useIndexBuffers.internalVar->integerValue )
  {
    idVertexCache::UnbindIndex(&vertexCache);
  }
  v6 = 3;
  if ( !r_singleTriangle.internalVar->integerValue )
    v6 = tri->numIndexes;
  qglDrawElements(4u, v6, 0x1405u, tri->indexes);
}

// FUNC: void __cdecl RB_DrawShadowElementsWithCounters(struct drawSurf_s const *,int)
void __cdecl RB_DrawShadowElementsWithCounters(const drawSurf_s *surf, int numIndexes)
{
  const srfTriangles_s *geo; // esi
  int v3; // edi
  vertCache_s *indexCache; // eax
  int v5; // esi
  char *v6; // eax

  geo = surf->geo;
  if ( surf->geo->primBatchMesh )
  {
    RB_ARB2_MD5R_DrawShadowElements(surf, numIndexes);
    return;
  }
  GL_VertexAttribState(1u);
  ++backEnd.pc.c_shadowElements;
  v3 = numIndexes;
  backEnd.pc.c_shadowIndexes += numIndexes;
  backEnd.pc.c_shadowVertexes += geo->numVerts;
  indexCache = geo->indexCache;
  if ( indexCache )
  {
    if ( r_useIndexBuffers.internalVar->integerValue )
    {
      v5 = 3;
      if ( !r_singleTriangle.internalVar->integerValue )
        v5 = numIndexes;
      v6 = idVertexCache::Position(&vertexCache, indexCache);
      qglDrawElements(4u, v5, 0x1405u, v6);
      backEnd.pc.c_vboIndexes += numIndexes;
      return;
    }
  }
  else if ( r_useIndexBuffers.internalVar->integerValue )
  {
    idVertexCache::UnbindIndex(&vertexCache);
  }
  if ( r_singleTriangle.internalVar->integerValue )
    v3 = 3;
  qglDrawElements(4u, v3, 0x1405u, geo->indexes);
}

// FUNC: void __cdecl RB_RenderTriangleSurface(struct srfTriangles_s const *)
void __cdecl RB_RenderTriangleSurface(const srfTriangles_s *tri)
{
  vertCache_s *ambientCache; // eax
  char *v2; // esi

  ambientCache = tri->ambientCache;
  if ( ambientCache )
  {
    v2 = idVertexCache::Position(&vertexCache, ambientCache);
    qglVertexPointer(3, 0x1406u, 64, v2);
    qglTexCoordPointer(2, 0x1406u, 64, v2 + 56);
    RB_DrawElementsWithCounters(tri);
  }
  else
  {
    RB_DrawElementsImmediate(tri);
  }
}

// FUNC: void __cdecl RB_T_ShowBatchSizeRenderTriangleSurface(struct drawSurf_s const *)
void __cdecl RB_T_ShowBatchSizeRenderTriangleSurface(const drawSurf_s *surf)
{
  float x; // eax
  float y; // ecx
  float z; // edx
  double v5; // st7
  double v6; // st7
  float v7; // [esp+8h] [ebp-30h]
  float v8; // [esp+Ch] [ebp-2Ch]
  float v9; // [esp+10h] [ebp-28h]
  float v10; // [esp+10h] [ebp-28h]
  float color; // [esp+18h] [ebp-20h]
  float colora; // [esp+18h] [ebp-20h]
  float color_4; // [esp+1Ch] [ebp-1Ch]
  float color_4a; // [esp+1Ch] [ebp-1Ch]
  float color_8; // [esp+20h] [ebp-18h]
  float color_8a; // [esp+20h] [ebp-18h]
  float v17; // [esp+30h] [ebp-8h]
  int surfa; // [esp+3Ch] [ebp+4h]
  float surfb; // [esp+3Ch] [ebp+4h]
  float surfc; // [esp+3Ch] [ebp+4h]

  surfa = surf->geo->numIndexes;
  if ( surfa > 30 )
  {
    if ( surfa <= 600 )
    {
      v5 = (double)surfa * 0.0016666667;
      surfb = v5;
      if ( v5 <= 0.0 )
      {
        x = showBatchSizeBadColor.x;
        y = showBatchSizeBadColor.y;
        z = showBatchSizeBadColor.z;
        goto LABEL_15;
      }
      if ( surfb < 1.0 )
      {
        v7 = showBatchSizeModerateColor.x - showBatchSizeBadColor.x;
        v8 = showBatchSizeModerateColor.y - showBatchSizeBadColor.y;
        v9 = showBatchSizeModerateColor.z - showBatchSizeBadColor.z;
        v10 = v9 * surfb;
        color = v7 * surfb + showBatchSizeBadColor.x;
        color_4 = v8 * surfb + showBatchSizeBadColor.y;
        color_8 = v10 + showBatchSizeBadColor.z;
LABEL_13:
        x = color;
        y = color_4;
        z = color_8;
        goto LABEL_15;
      }
LABEL_10:
      x = showBatchSizeModerateColor.x;
      y = showBatchSizeModerateColor.y;
      z = showBatchSizeModerateColor.z;
      goto LABEL_15;
    }
    if ( surfa <= 1500 )
    {
      v6 = (double)surfa * 0.00066666666;
      surfc = v6;
      if ( v6 <= 0.0 )
        goto LABEL_10;
      if ( surfc < 1.0 )
      {
        colora = showBatchSizeGoodColor.x - showBatchSizeModerateColor.x;
        color_4a = showBatchSizeGoodColor.y - showBatchSizeModerateColor.y;
        color_8a = showBatchSizeGoodColor.z - showBatchSizeModerateColor.z;
        v17 = color_8a * surfc;
        color = colora * surfc + showBatchSizeModerateColor.x;
        color_4 = color_4a * surfc + showBatchSizeModerateColor.y;
        color_8 = v17 + showBatchSizeModerateColor.z;
        goto LABEL_13;
      }
    }
    x = showBatchSizeGoodColor.x;
    y = showBatchSizeGoodColor.y;
    z = showBatchSizeGoodColor.z;
    goto LABEL_15;
  }
  x = showBatchSizeReallyBadColor.x;
  y = showBatchSizeReallyBadColor.y;
  z = showBatchSizeReallyBadColor.z;
LABEL_15:
  qglColor4f(x, y, z, 1.0);
  RB_RenderTriangleSurface(surf->geo);
}

// FUNC: void __cdecl RB_T_ShowTriRenderTriangleSurface(struct drawSurf_s const *)
void __cdecl RB_T_ShowTriRenderTriangleSurface(const drawSurf_s *surf)
{
  if ( !(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 0x2000) )
  {
LABEL_7:
    RB_RenderTriangleSurface(surf->geo);
    return;
  }
  if ( r_showTris.internalVar->integerValue || surf->geo->modviewSelected )
  {
    if ( surf->geo->modviewSelected )
    {
      qglColor4f(0.0, 1.0, 0.0, 1.0);
      RB_RenderTriangleSurface(surf->geo);
      return;
    }
    qglColor4f(1.0, 1.0, 1.0, 1.0);
    goto LABEL_7;
  }
}

// FUNC: void __cdecl RB_T_RenderTriangleSurface(struct drawSurf_s const *)
void __cdecl RB_T_RenderTriangleSurface(const drawSurf_s *surf)
{
  RB_RenderTriangleSurface(surf->geo);
}

// FUNC: void __cdecl RB_T_RenderSimpleSurface(struct drawSurf_s const *)
void __cdecl RB_T_RenderSimpleSurface(const drawSurf_s *surf)
{
  idImage *EditorImage; // eax

  GL_State(0);
  qglBlendFunc(0x302u, 0x303u);
  qglColor4f(1.0, 1.0, 1.0, surf->material->editorAlpha);
  EditorImage = idMaterial::GetEditorImage((idMaterial *)surf->material);
  EditorImage->Bind(EditorImage);
  RB_RenderTriangleSurface(surf->geo);
}

// FUNC: void __cdecl RB_T_RenderTriangleSurfacePasses(struct drawSurf_s const *)
void __cdecl RB_T_RenderTriangleSurfacePasses(const drawSurf_s *surf)
{
  const idMaterial *material; // ecx
  int numStages; // eax
  int v3; // ebp
  const srfTriangles_s *geo; // edi
  char *v5; // esi

  material = surf->material;
  numStages = 0;
  if ( material )
  {
    numStages = material->numStages;
    if ( r_showOverDraw.internalVar->integerValue > 1 )
    {
      if ( !numStages )
        return;
      numStages = 1;
    }
  }
  if ( numStages > 0 )
  {
    v3 = numStages;
    do
    {
      geo = surf->geo;
      if ( surf->geo->ambientCache )
      {
        v5 = idVertexCache::Position(&vertexCache, surf->geo->ambientCache);
        qglVertexPointer(3, 0x1406u, 64, v5);
        qglTexCoordPointer(2, 0x1406u, 64, v5 + 56);
        RB_DrawElementsWithCounters(geo);
      }
      else
      {
        RB_DrawElementsImmediate(surf->geo);
      }
      --v3;
    }
    while ( v3 );
  }
}

// FUNC: void __cdecl RB_RenderDrawSurfListWithFunction(struct drawSurf_s * *,int,void (__cdecl *)(struct drawSurf_s const *))
void __cdecl RB_RenderDrawSurfListWithFunction(
        drawSurf_s **drawSurfs,
        int numDrawSurfs,
        void (__cdecl *triFunc_)(const drawSurf_s *))
{
  const viewEntity_s *v3; // ecx
  int v4; // ebx
  drawSurf_s *v5; // edi
  const viewEntity_s *space; // eax
  int weaponDepthHackInViewID; // eax
  const viewEntity_s *v8; // ecx
  const viewEntity_s *v9; // ecx
  int v10; // eax
  float modelDepthHack; // [esp+1Ch] [ebp-4h]

  v3 = 0;
  v4 = 0;
  for ( backEnd.currentSpace = 0; v4 < numDrawSurfs; backEnd.currentSpace = v3 )
  {
    v5 = drawSurfs[v4];
    space = v5->space;
    if ( space != v3 )
      qglLoadMatrixf(space->modelViewMatrix);
    weaponDepthHackInViewID = v5->space->weaponDepthHackInViewID;
    if ( weaponDepthHackInViewID && weaponDepthHackInViewID == backEnd.viewDef->renderView.viewID )
      RB_EnterWeaponDepthHack();
    v8 = v5->space;
    if ( v8->modelDepthHack != 0.0 )
    {
      modelDepthHack = v8->modelDepthHack;
      qglDepthRange(0.0, 1.0);
      backEnd.projectionMatrix[14] = backEnd.projectionMatrix[14] - modelDepthHack;
      qglMatrixMode(0x1701u);
      qglLoadMatrixf(backEnd.projectionMatrix);
      backEnd.mvpSpace = 0;
      qglMatrixMode(0x1700u);
    }
    if ( r_useScissor.internalVar->integerValue && !idScreenRect::Equals(&backEnd.currentScissor, &v5->scissorRect) )
    {
      backEnd.currentScissor = v5->scissorRect;
      qglScissor(
        backEnd.currentScissor.x1 + backEnd.viewDef->viewport.x1,
        (*(int *)&backEnd.currentScissor.x1 >> 16) + backEnd.viewDef->viewport.y1,
        backEnd.currentScissor.x2 - backEnd.currentScissor.x1 + 1,
        (*(int *)&backEnd.currentScissor.x2 >> 16) - (*(int *)&backEnd.currentScissor.x1 >> 16) + 1);
    }
    triFunc_(v5);
    v9 = v5->space;
    v10 = v9->weaponDepthHackInViewID;
    if ( v10 && v10 == backEnd.viewDef->renderView.viewID || v9->modelDepthHack != 0.0 )
    {
      qglDepthRange(0.0, 1.0);
      backEnd.projectionMatrix[14] = backEnd.viewDef->projectionMatrix[14];
      qglMatrixMode(0x1701u);
      qglLoadMatrixf(backEnd.projectionMatrix);
      backEnd.mvpSpace = 0;
      qglMatrixMode(0x1700u);
    }
    v3 = v5->space;
    ++v4;
  }
}

// FUNC: void __cdecl RB_RenderDrawSurfChainWithFunction(struct drawSurf_s const *,void (__cdecl *)(struct drawSurf_s const *))
void __cdecl RB_RenderDrawSurfChainWithFunction(
        const drawSurf_s *drawSurfs,
        void (__cdecl *triFunc_)(const drawSurf_s *))
{
  const drawSurf_s *v2; // edi
  const viewEntity_s *v3; // ecx
  const viewEntity_s *space; // eax
  int weaponDepthHackInViewID; // eax
  const viewEntity_s *v6; // ecx
  const viewEntity_s *v7; // ecx
  int v8; // eax
  float modelDepthHack; // [esp+1Ch] [ebp-4h]

  v2 = drawSurfs;
  v3 = 0;
  for ( backEnd.currentSpace = 0; v2; v2 = v2->nextOnLight )
  {
    space = v2->space;
    if ( space != v3 )
      qglLoadMatrixf(space->modelViewMatrix);
    weaponDepthHackInViewID = v2->space->weaponDepthHackInViewID;
    if ( weaponDepthHackInViewID && weaponDepthHackInViewID == backEnd.viewDef->renderView.viewID )
      RB_EnterWeaponDepthHack();
    v6 = v2->space;
    if ( v6->modelDepthHack != 0.0 )
    {
      modelDepthHack = v6->modelDepthHack;
      qglDepthRange(0.0, 1.0);
      backEnd.projectionMatrix[14] = backEnd.projectionMatrix[14] - modelDepthHack;
      qglMatrixMode(0x1701u);
      qglLoadMatrixf(backEnd.projectionMatrix);
      backEnd.mvpSpace = 0;
      qglMatrixMode(0x1700u);
    }
    if ( r_useScissor.internalVar->integerValue && !idScreenRect::Equals(&backEnd.currentScissor, &v2->scissorRect) )
    {
      backEnd.currentScissor = v2->scissorRect;
      qglScissor(
        backEnd.currentScissor.x1 + backEnd.viewDef->viewport.x1,
        (*(int *)&backEnd.currentScissor.x1 >> 16) + backEnd.viewDef->viewport.y1,
        backEnd.currentScissor.x2 - backEnd.currentScissor.x1 + 1,
        (*(int *)&backEnd.currentScissor.x2 >> 16) - (*(int *)&backEnd.currentScissor.x1 >> 16) + 1);
    }
    triFunc_(v2);
    v7 = v2->space;
    v8 = v7->weaponDepthHackInViewID;
    if ( v8 && v8 == backEnd.viewDef->renderView.viewID || v7->modelDepthHack != 0.0 )
    {
      qglDepthRange(0.0, 1.0);
      backEnd.projectionMatrix[14] = backEnd.viewDef->projectionMatrix[14];
      qglMatrixMode(0x1701u);
      qglLoadMatrixf(backEnd.projectionMatrix);
      backEnd.mvpSpace = 0;
      qglMatrixMode(0x1700u);
    }
    v3 = v2->space;
    backEnd.currentSpace = v3;
  }
}

// FUNC: void __cdecl RB_BindVariableStageImage(struct textureStage_t const *,float const *)
void __cdecl RB_BindVariableStageImage(const textureStage_t *texture)
{
  idImage *v1; // eax
  cinData_t *v2; // eax
  const unsigned __int8 *image; // ecx
  int imageWidth; // edx
  int imageHeight; // esi
  idImage *v6; // eax
  int v7; // eax
  const unsigned __int8 *v8; // [esp-10h] [ebp-24h]
  int v9; // [esp-Ch] [ebp-20h]
  cinData_t cin; // [esp+4h] [ebp-10h] BYREF

  if ( texture->cinematic )
  {
    if ( r_skipDynamicTextures.internalVar->integerValue )
    {
LABEL_3:
      v1 = globalImages->GetDefaultImage(globalImages);
      v1->Bind(v1);
      return;
    }
    v2 = texture->cinematic->ImageForTime(
           texture->cinematic,
           &cin,
           (int)((backEnd.viewDef->floatTime + backEnd.viewDef->renderView.shaderParms[11]) * 1000.0));
    image = v2->image;
    imageWidth = v2->imageWidth;
    imageHeight = v2->imageHeight;
    cin.status = v2->status;
    if ( image )
    {
      v9 = imageWidth;
      v8 = image;
      v6 = globalImages->GetCinematicImage(globalImages);
      idImage::UploadScratch(v6, v8, v9, imageHeight);
    }
    else
    {
      v7 = ((int (__fastcall *)(idImageManager *, int))globalImages->GetBlackImage)(globalImages, imageWidth);
      (*(void (__thiscall **)(int))(*(_DWORD *)v7 + 4))(v7);
    }
  }
  else
  {
    if ( r_skipTextures.internalVar->integerValue )
      goto LABEL_3;
    if ( texture->image )
      texture->image->Bind(texture->image);
  }
}

// FUNC: void __cdecl RB_BindStageTexture(float const *,struct textureStage_t const *,struct drawSurf_s const *)
void __cdecl RB_BindStageTexture(const float *shaderRegisters, const textureStage_t *texture, const drawSurf_s *surf)
{
  char *v3; // eax
  texgen_t texgen; // eax
  char *v5; // eax
  char *v6; // eax
  float mat[16]; // [esp+Ch] [ebp-40h] BYREF

  RB_BindVariableStageImage(texture);
  if ( texture->texgen == TG_DIFFUSE_CUBE )
  {
    v3 = idVertexCache::Position(&vertexCache, surf->geo->ambientCache);
    qglTexCoordPointer(3, 0x1406u, 64, v3 + 16);
  }
  texgen = texture->texgen;
  if ( texgen == TG_SKYBOX_CUBE || texgen == TG_WOBBLESKY_CUBE )
  {
    v5 = idVertexCache::Position(&vertexCache, surf->dynamicTexCoords);
    qglTexCoordPointer(3, 0x1406u, 0, v5);
  }
  if ( texture->texgen == TG_REFLECT_CUBE )
  {
    qglEnable(0xC60u);
    qglEnable(0xC61u);
    qglEnable(0xC62u);
    qglTexGenf(0x2000u, 0x2500u, 34066.0);
    qglTexGenf(0x2001u, 0x2500u, 34066.0);
    qglTexGenf(0x2002u, 0x2500u, 34066.0);
    GL_EnableVertexAttribState(2u);
    v6 = idVertexCache::Position(&vertexCache, surf->geo->ambientCache);
    qglNormalPointer(0x1406u, 64, v6 + 16);
    qglMatrixMode(0x1702u);
    R_TransposeGLMatrix(backEnd.viewDef->worldSpace.modelViewMatrix, mat);
    qglLoadMatrixf(mat);
    qglMatrixMode(0x1700u);
  }
  if ( texture->hasMatrix )
  {
    RB_GetShaderTextureMatrix(shaderRegisters, texture, mat);
    qglMatrixMode(0x1702u);
    qglLoadMatrixf(mat);
    qglMatrixMode(0x1700u);
  }
}

// FUNC: void __cdecl RB_DetermineLightScale(void)
void __cdecl RB_DetermineLightScale()
{
  double v0; // st7
  viewLight_s *i; // edi
  const idMaterial *lightShader; // eax
  int numStages; // esi
  const float *shaderRegisters; // edx
  int *v5; // ecx
  double v6; // st6
  double v7; // st6
  double v8; // st6
  unsigned __int8 v10; // c0
  unsigned __int8 v11; // c3
  float v; // [esp+8h] [ebp-4h]
  float va; // [esp+8h] [ebp-4h]
  float vb; // [esp+8h] [ebp-4h]

  v0 = 1.0;
  for ( i = backEnd.viewDef->viewLights; i; i = i->next )
  {
    if ( i->localInteractions || i->globalInteractions || i->translucentInteractions )
    {
      lightShader = i->lightShader;
      numStages = lightShader->numStages;
      if ( numStages > 0 )
      {
        shaderRegisters = i->shaderRegisters;
        v5 = &lightShader->stages->color.registers[1];
        do
        {
          v6 = shaderRegisters[*(v5 - 1)] * r_lightScale.internalVar->floatValue;
          if ( v6 > v0 )
          {
            v = v6;
            v0 = v;
          }
          v7 = shaderRegisters[*v5] * r_lightScale.internalVar->floatValue;
          if ( v7 > v0 )
          {
            va = v7;
            v0 = va;
          }
          v8 = shaderRegisters[v5[1]] * r_lightScale.internalVar->floatValue;
          if ( v8 > v0 )
          {
            vb = v8;
            v0 = vb;
          }
          v5 += 33;
          --numStages;
        }
        while ( numStages );
      }
    }
  }
  backEnd.pc.maxLightValue = v0;
  if ( v10 | v11 )
  {
    backEnd.lightScale = r_lightScale.internalVar->floatValue;
    backEnd.overBright = 1.0;
  }
  else
  {
    backEnd.lightScale = r_lightScale.internalVar->floatValue / v0 * tr.backEndRendererMaxLight;
    backEnd.overBright = v0 / tr.backEndRendererMaxLight;
  }
}

// FUNC: void __cdecl R_SetDrawInteraction(struct shaderStage_t const *,float const *,class idImage * *,class idVec4 * const,float * const)
void __cdecl R_SetDrawInteraction(
        const shaderStage_t *surfaceStage,
        const float *surfaceRegs,
        idImage **image,
        idVec4 *matrix,
        float *color)
{
  double w; // st7
  int v6; // eax
  double v7; // st7
  unsigned __int8 v9; // c0
  unsigned __int8 v10; // c2
  int v11; // eax
  double v12; // st7
  unsigned __int8 v14; // c0
  unsigned __int8 v15; // c2
  int v16; // eax
  double v17; // st7
  unsigned __int8 v19; // c0
  unsigned __int8 v20; // c2
  int v21; // edx
  double v22; // st7
  unsigned __int8 v24; // c0
  unsigned __int8 v25; // c2

  *image = surfaceStage->texture.image;
  if ( surfaceStage->texture.hasMatrix )
  {
    matrix->x = surfaceRegs[surfaceStage->texture.matrix[0][0]];
    matrix->y = surfaceRegs[surfaceStage->texture.matrix[0][1]];
    matrix->z = 0.0;
    matrix->w = surfaceRegs[surfaceStage->texture.matrix[0][2]];
    matrix[1].x = surfaceRegs[surfaceStage->texture.matrix[1][0]];
    matrix[1].y = surfaceRegs[surfaceStage->texture.matrix[1][1]];
    matrix[1].z = 0.0;
    w = matrix->w;
    matrix[1].w = surfaceRegs[surfaceStage->texture.matrix[1][2]];
    if ( w < -40.0 || matrix->w > 40.0 )
      matrix->w = matrix->w - (double)(int)matrix->w;
    if ( matrix[1].w < -40.0 || matrix[1].w > 40.0 )
      matrix[1].w = matrix[1].w - (double)(int)matrix[1].w;
  }
  else
  {
    matrix->x = 1.0;
    matrix->y = 0.0;
    matrix->z = 0.0;
    matrix->w = 0.0;
    matrix[1].x = 0.0;
    matrix[1].y = 1.0;
    matrix[1].z = 0.0;
    matrix[1].w = 0.0;
  }
  if ( color )
  {
    v6 = surfaceStage->color.registers[0];
    v7 = surfaceRegs[v6];
    *color = surfaceRegs[v6];
    if ( v9 | v10 )
    {
      *color = 0.0;
    }
    else if ( v7 > 1.0 )
    {
      *color = 1.0;
    }
    v11 = surfaceStage->color.registers[1];
    v12 = surfaceRegs[v11];
    color[1] = surfaceRegs[v11];
    if ( v14 | v15 )
    {
      color[1] = 0.0;
    }
    else if ( v12 > 1.0 )
    {
      color[1] = 1.0;
    }
    v16 = surfaceStage->color.registers[2];
    v17 = surfaceRegs[v16];
    color[2] = surfaceRegs[v16];
    if ( v19 | v20 )
    {
      color[2] = 0.0;
    }
    else if ( v17 > 1.0 )
    {
      color[2] = 1.0;
    }
    v21 = surfaceStage->color.registers[3];
    v22 = surfaceRegs[v21];
    color[3] = surfaceRegs[v21];
    if ( v24 | v25 )
    {
      color[3] = 0.0;
    }
    else if ( v22 > 1.0 )
    {
      color[3] = 1.0;
    }
  }
}

// FUNC: RB_SubmittInteraction
void __usercall RB_SubmittInteraction(
        drawInteraction_t *din@<esi>,
        void (__cdecl *DrawInteraction)(const drawInteraction_t *))
{
  if ( din->bumpImage )
  {
    if ( !din->diffuseImage || r_skipDiffuse.internalVar->integerValue || r_skipTextures.internalVar->integerValue )
      din->diffuseImage = globalImages->GetBlackImage(globalImages);
    if ( !din->specularImage
      || r_skipSpecular.internalVar->integerValue
      || din->ambientLight
      || r_skipTextures.internalVar->integerValue )
    {
      din->specularImage = globalImages->GetBlackImage(globalImages);
    }
    if ( !din->bumpImage || r_skipBump.internalVar->integerValue || r_skipTextures.internalVar->integerValue )
      din->bumpImage = globalImages->GetFlatNormalMap(globalImages);
    if ( (din->diffuseColor.x > 0.0 || din->diffuseColor.y > 0.0 || din->diffuseColor.z > 0.0)
      && din->diffuseImage != globalImages->GetBlackImage(globalImages)
      || (din->specularColor.x > 0.0 || din->specularColor.y > 0.0 || din->specularColor.z > 0.0)
      && din->specularImage != globalImages->GetBlackImage(globalImages) )
    {
      DrawInteraction(din);
    }
  }
}

// FUNC: void __cdecl RB_DrawView(void const *)
void __cdecl RB_DrawView(const void *data)
{
  const viewDef_s *viewDef; // eax

  backEnd.viewDef = (const viewDef_s *)*((_DWORD *)data + 2);
  qmemcpy(backEnd.projectionMatrix, backEnd.viewDef->projectionMatrix, sizeof(backEnd.projectionMatrix));
  viewDef = backEnd.viewDef;
  backEnd.mvpSpace = 0;
  if ( backEnd.viewDef->numDrawSurfs && (!r_skipRender.internalVar->integerValue || !backEnd.viewDef->viewEntitys) )
  {
    if ( r_skipRenderContext.internalVar->integerValue && backEnd.viewDef->viewEntitys )
    {
      GLimp_DeactivateContext();
      viewDef = backEnd.viewDef;
    }
    backEnd.pc.c_surfaces += viewDef->numDrawSurfs;
    RB_ShowOverdraw();
    RB_STD_DrawView();
    if ( r_skipRenderContext.internalVar->integerValue )
    {
      if ( backEnd.viewDef->viewEntitys )
      {
        GLimp_ActivateContext();
        RB_SetDefaultGLState();
      }
    }
  }
}

// FUNC: void __cdecl RB_CreateSingleDrawInteractions(struct drawSurf_s const *,void (__cdecl *)(struct drawInteraction_t const *))
void __cdecl RB_CreateSingleDrawInteractions(
        const drawSurf_s *surf,
        void (__cdecl *DrawInteraction)(const drawInteraction_t *))
{
  const drawSurf_s *v2; // esi
  const float *shaderRegisters; // ebp
  viewLight_s *vLight; // edi
  const float *v5; // ebx
  const srfTriangles_s *geo; // eax
  int weaponDepthHackInViewID; // eax
  const viewEntity_s *space; // ecx
  const viewEntity_s *v9; // eax
  int i; // esi
  const idMaterial *v11; // edi
  shaderStage_t *v12; // esi
  int v13; // ebx
  shaderStage_t *stages; // edi
  stageLighting_t lighting; // eax
  const shaderStage_t *v16; // edi
  __int32 v17; // eax
  int v18; // eax
  const viewEntity_s *v19; // ecx
  int v20; // eax
  const idMaterial *lightShader; // [esp+28h] [ebp-168h]
  const idMaterial *surfaceShader; // [esp+2Ch] [ebp-164h]
  int v23; // [esp+30h] [ebp-160h]
  int lightStageNum; // [esp+34h] [ebp-15Ch]
  float lightColor; // [esp+38h] [ebp-158h]
  float lightColor_4; // [esp+3Ch] [ebp-154h]
  float lightColor_8; // [esp+40h] [ebp-150h]
  float lightColor_12; // [esp+44h] [ebp-14Ch]
  int surfaceStageNum; // [esp+48h] [ebp-148h]
  const float *lightRegs; // [esp+4Ch] [ebp-144h]
  drawInteraction_t inter; // [esp+50h] [ebp-140h] BYREF
  idPlane lightProject[4]; // [esp+150h] [ebp-40h] BYREF

  v2 = surf;
  shaderRegisters = surf->shaderRegisters;
  vLight = backEnd.vLight;
  v5 = backEnd.vLight->shaderRegisters;
  surfaceShader = surf->material;
  lightShader = backEnd.vLight->lightShader;
  lightRegs = v5;
  if ( !r_skipInteractions.internalVar->integerValue )
  {
    geo = surf->geo;
    if ( surf->geo )
    {
      if ( geo->ambientCache || geo->primBatchMesh )
      {
        if ( surf->space != backEnd.currentSpace )
        {
          backEnd.currentSpace = surf->space;
          qglLoadMatrixf(surf->space->modelViewMatrix);
        }
        if ( r_useScissor.internalVar->integerValue )
        {
          if ( !idScreenRect::Equals(&backEnd.currentScissor, &surf->scissorRect) )
          {
            backEnd.currentScissor = surf->scissorRect;
            qglScissor(
              backEnd.currentScissor.x1 + backEnd.viewDef->viewport.x1,
              (*(int *)&backEnd.currentScissor.x1 >> 16) + backEnd.viewDef->viewport.y1,
              backEnd.currentScissor.x2 - backEnd.currentScissor.x1 + 1,
              (*(int *)&backEnd.currentScissor.x2 >> 16) - (*(int *)&backEnd.currentScissor.x1 >> 16) + 1);
          }
          v2 = surf;
        }
        weaponDepthHackInViewID = v2->space->weaponDepthHackInViewID;
        if ( weaponDepthHackInViewID && weaponDepthHackInViewID == backEnd.viewDef->renderView.viewID )
          RB_EnterWeaponDepthHack();
        space = v2->space;
        if ( space->modelDepthHack != 0.0 )
          RB_EnterModelDepthHack(space->modelDepthHack);
        v9 = v2->space;
        inter.surf = v2;
        inter.lightFalloffImage = vLight->falloffImage;
        R_GlobalPointToLocal(v9->modelMatrix, &vLight->globalLightOrigin, (idVec3 *)&inter.localLightOrigin);
        R_GlobalPointToLocal(
          v2->space->modelMatrix,
          &backEnd.viewDef->renderView.vieworg,
          (idVec3 *)&inter.localViewOrigin);
        inter.localLightOrigin.w = 0.0;
        inter.localViewOrigin.w = 1.0;
        inter.ambientLight = lightShader->ambientLight;
        `vector constructor iterator'(
          (char *)lightProject,
          0x10u,
          4,
          (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
        for ( i = 0; i < 4; ++i )
          R_GlobalPlaneToLocal(surf->space->modelMatrix, &backEnd.vLight->lightProject[i], &lightProject[i]);
        v11 = lightShader;
        lightStageNum = 0;
        if ( lightShader->numStages > 0 )
        {
          v23 = 0;
          do
          {
            v12 = &v11->stages[v23];
            if ( !v5 || v5[v12->conditionRegister] != 0.0 )
            {
              inter.lightImage = v12->texture.image;
              SIMDProcessor->Memcpy(SIMDProcessor, inter.lightProjection, lightProject, 64);
              if ( v12->texture.hasMatrix )
              {
                RB_GetShaderTextureMatrix(v5, &v12->texture, backEnd.lightTextureMatrix);
                RB_BakeTextureMatrixIntoTexgen((idPlane *)inter.lightProjection);
              }
              memset(&inter.bumpImage, 0, 44);
              surfaceStageNum = 0;
              lightColor = backEnd.lightScale * v5[v12->color.registers[0]];
              lightColor_4 = backEnd.lightScale * v5[v12->color.registers[1]];
              lightColor_8 = backEnd.lightScale * v5[v12->color.registers[2]];
              lightColor_12 = v5[v12->color.registers[3]];
              if ( surfaceShader->numStages > 0 )
              {
                v13 = 0;
                do
                {
                  stages = surfaceShader->stages;
                  lighting = stages[v13].lighting;
                  v16 = &stages[v13];
                  v17 = lighting - 1;
                  if ( v17 )
                  {
                    v18 = v17 - 1;
                    if ( v18 )
                    {
                      if ( v18 == 1 && shaderRegisters[v16->conditionRegister] != 0.0 )
                      {
                        if ( inter.specularImage )
                          RB_SubmittInteraction(&inter, DrawInteraction);
                        R_SetDrawInteraction(
                          v16,
                          shaderRegisters,
                          &inter.specularImage,
                          inter.specularMatrix,
                          &inter.specularColor.x);
                        inter.specularColor.x = inter.specularColor.x * lightColor;
                        inter.specularColor.y = inter.specularColor.y * lightColor_4;
                        inter.specularColor.z = inter.specularColor.z * lightColor_8;
                        inter.specularColor.w = inter.specularColor.w * lightColor_12;
                        inter.vertexColor = v16->vertexColor;
                      }
                    }
                    else if ( shaderRegisters[v16->conditionRegister] != 0.0 )
                    {
                      if ( inter.diffuseImage )
                        RB_SubmittInteraction(&inter, DrawInteraction);
                      R_SetDrawInteraction(
                        v16,
                        shaderRegisters,
                        &inter.diffuseImage,
                        inter.diffuseMatrix,
                        &inter.diffuseColor.x);
                      inter.diffuseColor.x = inter.diffuseColor.x * lightColor;
                      inter.diffuseColor.y = inter.diffuseColor.y * lightColor_4;
                      inter.diffuseColor.z = inter.diffuseColor.z * lightColor_8;
                      inter.diffuseColor.w = inter.diffuseColor.w * lightColor_12;
                      inter.vertexColor = v16->vertexColor;
                    }
                  }
                  else if ( shaderRegisters[v16->conditionRegister] != 0.0 )
                  {
                    RB_SubmittInteraction(&inter, DrawInteraction);
                    inter.diffuseImage = 0;
                    inter.specularImage = 0;
                    R_SetDrawInteraction(v16, shaderRegisters, &inter.bumpImage, inter.bumpMatrix, 0);
                  }
                  ++v13;
                  ++surfaceStageNum;
                }
                while ( surfaceStageNum < surfaceShader->numStages );
                v5 = lightRegs;
                v11 = lightShader;
              }
              RB_SubmittInteraction(&inter, DrawInteraction);
            }
            ++v23;
            ++lightStageNum;
          }
          while ( lightStageNum < v11->numStages );
        }
        v19 = surf->space;
        v20 = v19->weaponDepthHackInViewID;
        if ( v20 && v20 == backEnd.viewDef->renderView.viewID || v19->modelDepthHack != 0.0 )
        {
          qglDepthRange(0.0, 1.0);
          backEnd.projectionMatrix[14] = backEnd.viewDef->projectionMatrix[14];
          qglMatrixMode(0x1701u);
          qglLoadMatrixf(backEnd.projectionMatrix);
          backEnd.mvpSpace = 0;
          qglMatrixMode(0x1700u);
        }
      }
    }
  }
}
