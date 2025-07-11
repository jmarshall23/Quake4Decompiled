
// FUNC: void * __cdecl R_GetCommandBuffer(int)
emptyCommand_t *__cdecl R_GetCommandBuffer(int bytes)
{
  emptyCommand_t *result; // eax

  result = (emptyCommand_t *)R_FrameAlloc(bytes);
  result->next = 0;
  frameData[tr.smpFrame]->cmdTail->next = &result->commandId;
  frameData[tr.smpFrame]->cmdTail = result;
  return result;
}

// FUNC: void * __cdecl R_GetCommandBufferDeferred(int)
emptyCommand_t *__cdecl R_GetCommandBufferDeferred(int bytes)
{
  emptyCommand_t *result; // eax
  frameData_t *v2; // ecx

  result = (emptyCommand_t *)R_FrameAlloc(bytes);
  result->next = 0;
  v2 = frameData[tr.smpFrame];
  if ( v2->deferredCmdHead )
    v2->deferredCmdTail->next = &result->commandId;
  else
    v2->deferredCmdHead = result;
  frameData[tr.smpFrame]->deferredCmdTail = result;
  return result;
}

// FUNC: void __cdecl R_SubmitDeferredCommands(void)
void __cdecl R_SubmitDeferredCommands()
{
  frameData_t *v0; // edx

  v0 = frameData[tr.smpFrame];
  if ( v0->deferredCmdHead )
  {
    v0->cmdTail->next = &v0->deferredCmdHead->commandId;
    frameData[tr.smpFrame]->cmdTail = frameData[tr.smpFrame]->deferredCmdTail;
    frameData[tr.smpFrame]->deferredCmdTail = 0;
    frameData[tr.smpFrame]->deferredCmdHead = 0;
  }
}

// FUNC: void __cdecl R_ClearCommandChain(void)
void __cdecl R_ClearCommandChain()
{
  frameData[tr.smpFrame]->cmdTail = (emptyCommand_t *)R_FrameAlloc(8);
  frameData[tr.smpFrame]->cmdHead = frameData[tr.smpFrame]->cmdTail;
  frameData[tr.smpFrame]->cmdHead->commandId = RC_NOP;
  frameData[tr.smpFrame]->cmdHead->next = 0;
  frameData[tr.smpFrame]->deferredCmdTail = 0;
  frameData[tr.smpFrame]->deferredCmdHead = 0;
}

// FUNC: void __cdecl R_LockSurfaceScene(struct viewDef_s *)
void __cdecl R_LockSurfaceScene(viewDef_s *parms)
{
  viewEntity_s *i; // esi
  emptyCommand_t *v2; // eax
  frameData_t *v3; // ecx
  frameData_t *v4; // ecx

  memset(&parms->worldSpace, 0, sizeof(parms->worldSpace));
  R_SetViewMatrix(&parms->renderView, parms->worldSpace.modelMatrix, parms->worldSpace.modelViewMatrix);
  qmemcpy(&tr.lockSurfacesCmd.viewDef->worldSpace, &parms->worldSpace, sizeof(tr.lockSurfacesCmd.viewDef->worldSpace));
  for ( i = tr.lockSurfacesCmd.viewDef->viewEntitys; i; i = i->next )
    myGlMultMatrix(i->modelMatrix, tr.lockSurfacesCmd.viewDef->worldSpace.modelViewMatrix, i->modelViewMatrix);
  if ( (parms->renderFlags & 0x20) != 0 )
  {
    v2 = (emptyCommand_t *)R_FrameAlloc(12);
    v2->next = 0;
    v3 = frameData[tr.smpFrame];
    if ( v3->deferredCmdHead )
      v3->deferredCmdTail->next = &v2->commandId;
    else
      v3->deferredCmdHead = v2;
    frameData[tr.smpFrame]->deferredCmdTail = v2;
  }
  else
  {
    v4 = frameData[tr.smpFrame];
    if ( v4->deferredCmdHead )
    {
      v4->cmdTail->next = &v4->deferredCmdHead->commandId;
      frameData[tr.smpFrame]->cmdTail = frameData[tr.smpFrame]->deferredCmdTail;
      frameData[tr.smpFrame]->deferredCmdTail = 0;
      frameData[tr.smpFrame]->deferredCmdHead = 0;
    }
    v2 = (emptyCommand_t *)R_FrameAlloc(12);
    v2->next = 0;
    frameData[tr.smpFrame]->cmdTail->next = &v2->commandId;
    frameData[tr.smpFrame]->cmdTail = v2;
  }
  *(drawSurfsCommand_t *)&v2->commandId = tr.lockSurfacesCmd;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::SetColor4(float,float,float,float)
void __thiscall idRenderSystemLocal::SetColor4(idRenderSystemLocal *this, float r, float g, float b, float a)
{
  idGuiModel::SetColor(this->guiModel, r, g, b, a);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawStretchPic(class idDrawVert const *,int const *,int,int,class idMaterial const *,bool,float,float,float,float)
void __thiscall idRenderSystemLocal::DrawStretchPic(
        idRenderSystemLocal *this,
        const idDrawVert *verts,
        const int *indexes,
        int vertCount,
        int indexCount,
        const idMaterial *material,
        bool clip,
        float min_x,
        float min_y,
        float max_x,
        float max_y)
{
  idGuiModel::DrawStretchPic(
    this->guiModel,
    verts,
    indexes,
    vertCount,
    indexCount,
    material,
    clip,
    min_x,
    min_y,
    max_x,
    max_y);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawStretchPic(float,float,float,float,float,float,float,float,class idMaterial const *)
void __thiscall idRenderSystemLocal::DrawStretchPic(
        idRenderSystemLocal *this,
        float x,
        float y,
        float w,
        float h,
        int s1,
        int t1,
        int s2,
        int t2,
        const idMaterial *material)
{
  idGuiModel::DrawStretchPic(this->guiModel, x, y, w, h, s1, t1, s2, t2, material);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawStretchTri(class idVec2,class idVec2,class idVec2,class idVec2,class idVec2,class idVec2,class idMaterial const *)
void __thiscall idRenderSystemLocal::DrawStretchTri(
        idRenderSystemLocal *this,
        idVec2 p1,
        idVec2 p2,
        idVec2 p3,
        idVec2 t1,
        idVec2 t2,
        idVec2 t3,
        const idMaterial *material)
{
  idGuiModel::DrawStretchTri(tr.guiModel, p1, p2, p3, t1, t2, t3, material);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::GlobalToNormalizedDeviceCoordinates(class idVec3 const &,class idVec3 &)
void __thiscall idRenderSystemLocal::GlobalToNormalizedDeviceCoordinates(
        idRenderSystemLocal *this,
        const idVec3 *global,
        idVec3 *ndc)
{
  if ( tr.viewDef )
    R_GlobalToNormalizedDeviceCoordinates(
      tr.viewDef->worldSpace.modelViewMatrix,
      tr.viewDef->projectionMatrix,
      global,
      ndc);
  else
    R_GlobalToNormalizedDeviceCoordinates(
      tr.primaryView->worldSpace.modelViewMatrix,
      tr.primaryView->projectionMatrix,
      global,
      ndc);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::GetGLSettings(int &,int &)
void __thiscall idRenderSystemLocal::GetGLSettings(idRenderSystemLocal *this, int *width, int *height)
{
  *width = glConfig.vidWidth;
  *height = glConfig.vidHeight;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawTinyChar(int,int,int,class idMaterial const *)
void __thiscall idRenderSystemLocal::DrawTinyChar(
        idRenderSystemLocal *this,
        int x,
        int y,
        unsigned __int8 ch,
        const idMaterial *material)
{
  float v6; // [esp+0h] [ebp-28h]
  float v7; // [esp+4h] [ebp-24h]
  float v8; // [esp+18h] [ebp-10h]
  float v9; // [esp+1Ch] [ebp-Ch]
  float fcol; // [esp+24h] [ebp-4h]
  float v11; // [esp+34h] [ebp+Ch]

  if ( ch != 32 && y >= -8 )
  {
    v11 = (double)((int)ch >> 4) * 0.0625;
    fcol = (double)(ch & 0xF) * 0.0625;
    v9 = v11 + 0.0625;
    v8 = fcol + 0.0625;
    v7 = (float)y;
    v6 = (float)x;
    (*((void (__thiscall **)(idRenderSystemLocal *, _DWORD, _DWORD, int, int, _DWORD, _DWORD, _DWORD, _DWORD, const idMaterial *))&this->SetColor4
     + 1))(
      this,
      LODWORD(v6),
      LODWORD(v7),
      1082130432,
      1090519040,
      LODWORD(fcol),
      LODWORD(v11),
      LODWORD(v8),
      LODWORD(v9),
      material);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawSmallChar(int,int,int,class idMaterial const *)
void __thiscall idRenderSystemLocal::DrawSmallChar(
        idRenderSystemLocal *this,
        int x,
        int y,
        unsigned __int8 ch,
        const idMaterial *material)
{
  float v6; // [esp+0h] [ebp-28h]
  float v7; // [esp+4h] [ebp-24h]
  float v8; // [esp+18h] [ebp-10h]
  float v9; // [esp+1Ch] [ebp-Ch]
  float fcol; // [esp+24h] [ebp-4h]
  float v11; // [esp+34h] [ebp+Ch]

  if ( ch != 32 && y >= -16 )
  {
    v11 = (double)((int)ch >> 4) * 0.0625;
    fcol = (double)(ch & 0xF) * 0.0625;
    v9 = v11 + 0.0625;
    v8 = fcol + 0.0625;
    v7 = (float)y;
    v6 = (float)x;
    (*((void (__thiscall **)(idRenderSystemLocal *, _DWORD, _DWORD, int, int, _DWORD, _DWORD, _DWORD, _DWORD, const idMaterial *))&this->SetColor4
     + 1))(
      this,
      LODWORD(v6),
      LODWORD(v7),
      1090519040,
      1098907648,
      LODWORD(fcol),
      LODWORD(v11),
      LODWORD(v8),
      LODWORD(v9),
      material);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawBigChar(int,int,int,class idMaterial const *)
void __thiscall idRenderSystemLocal::DrawBigChar(
        idRenderSystemLocal *this,
        int x,
        int y,
        unsigned __int8 ch,
        const idMaterial *material)
{
  float v6; // [esp+0h] [ebp-28h]
  float v7; // [esp+4h] [ebp-24h]
  float v8; // [esp+18h] [ebp-10h]
  float v9; // [esp+1Ch] [ebp-Ch]
  float fcol; // [esp+24h] [ebp-4h]
  float v11; // [esp+34h] [ebp+Ch]

  if ( ch != 32 && y >= -16 )
  {
    v11 = (double)((int)ch >> 4) * 0.0625;
    fcol = (double)(ch & 0xF) * 0.0625;
    v9 = v11 + 0.0625;
    v8 = fcol + 0.0625;
    v7 = (float)y;
    v6 = (float)x;
    (*((void (__thiscall **)(idRenderSystemLocal *, _DWORD, _DWORD, int, int, _DWORD, _DWORD, _DWORD, _DWORD, const idMaterial *))&this->SetColor4
     + 1))(
      this,
      LODWORD(v6),
      LODWORD(v7),
      1098907648,
      1098907648,
      LODWORD(fcol),
      LODWORD(v11),
      LODWORD(v8),
      LODWORD(v9),
      material);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::BeginFrame(struct viewDef_s *,int,int)
void __thiscall idRenderSystemLocal::BeginFrame(
        idRenderSystemLocal *this,
        viewDef_s *viewDef,
        int windowWidth,
        int windowHeight)
{
  tr.viewDef = viewDef;
  this->BeginFrame(this, windowWidth, windowHeight);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawDemoPics(void)
void __thiscall idRenderSystemLocal::DrawDemoPics(idRenderSystemLocal *this)
{
  idGuiModel::EmitFullScreen(this->demoGuiModel);
}

// FUNC: public: void __thiscall idRenderSystemLocal::RenderViewToViewport(struct renderView_s const *,class idScreenRect *)
void __thiscall idRenderSystemLocal::RenderViewToViewport(
        idRenderSystemLocal *this,
        const renderView_s *renderView,
        idScreenRect *viewport)
{
  int currentRenderCrop; // eax
  renderCrop_t *v4; // esi
  float wRatio; // [esp+14h] [ebp-Ch]
  float hRatio; // [esp+18h] [ebp-8h]
  float renderViewa; // [esp+24h] [ebp+4h]
  float renderViewb; // [esp+24h] [ebp+4h]
  float renderViewc; // [esp+24h] [ebp+4h]
  float renderViewd; // [esp+24h] [ebp+4h]

  currentRenderCrop = this->currentRenderCrop;
  v4 = &this->renderCrops[currentRenderCrop];
  wRatio = (double)this->renderCrops[currentRenderCrop].width * 0.0015625;
  hRatio = (double)this->renderCrops[currentRenderCrop].height * 0.0020833334;
  renderViewa = (double)renderView->x * wRatio + (double)v4->x;
  viewport->x1 = (int)renderViewa;
  renderViewb = (double)v4->x + floor((double)(renderView->x + renderView->width) * wRatio + 0.5) - 1.0;
  viewport->x2 = (int)renderViewb;
  renderViewc = (double)(v4->y + v4->height) - floor((double)(renderView->y + renderView->height) * hRatio + 0.5);
  viewport->y1 = (int)renderViewc;
  renderViewd = (double)(v4->y + v4->height) - floor((double)renderView->y * hRatio + 0.5) - 1.0;
  viewport->y2 = (int)renderViewd;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::PrintMemInfo(class MemInfo *)
void __thiscall idRenderSystemLocal::PrintMemInfo(idRenderSystemLocal *this, MemInfo *mi)
{
  globalImages->PrintMemInfo(globalImages, mi);
  renderModelManager->PrintMemInfo(renderModelManager, mi);
}

// FUNC: public: virtual bool __thiscall idRenderSystemLocal::UploadImage(char const *,unsigned char const *,int,int)
char __thiscall idRenderSystemLocal::UploadImage(
        idRenderSystemLocal *this,
        const char *imageName,
        const unsigned __int8 *data,
        int width,
        int height)
{
  idImage *v5; // esi

  v5 = globalImages->GetImage(globalImages, imageName);
  if ( !v5 )
    return 0;
  idImage::UploadScratch(v5, data, width, height);
  idImage::SetImageFilterAndRepeat(v5);
  return 1;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DebugGraph(float,float,float,class idVec4 const &)
void __thiscall idRenderSystemLocal::DebugGraph(
        idRenderSystemLocal *this,
        float cur,
        float min,
        float max,
        const idVec4 *color)
{
  unsigned __int8 *v6; // esi
  int v7; // edi
  double v8; // st7
  unsigned __int8 *v10; // eax
  int v11; // ecx
  unsigned __int8 *v12; // eax
  int v13; // ecx
  int v14; // [esp+10h] [ebp-8h]
  int cura; // [esp+1Ch] [ebp+4h]
  int mina; // [esp+20h] [ebp+8h]
  float maxb; // [esp+24h] [ebp+Ch]
  float maxc; // [esp+24h] [ebp+Ch]
  float maxd; // [esp+24h] [ebp+Ch]
  float maxe; // [esp+24h] [ebp+Ch]
  float maxa; // [esp+24h] [ebp+Ch]
  const idVec4 *colora; // [esp+28h] [ebp+10h]

  v6 = this->debugGraph[0][0];
  v7 = 64;
  do
  {
    memmove(v6, v6 + 4, 0x3FCu);
    v6 += 1024;
    --v7;
  }
  while ( v7 );
  v8 = (max - cur) / (max - min);
  if ( v8 >= min )
  {
    if ( v8 > max )
      v8 = max;
  }
  else
  {
    v8 = min;
  }
  maxb = v8 * 64.0;
  mina = (int)maxb;
  maxc = color->x * 255.0;
  cura = (int)maxc;
  maxd = color->y * 255.0;
  colora = (const idVec4 *)(int)maxd;
  maxe = color->z * 255.0;
  v14 = (int)maxe;
  maxa = color->w * 255.0;
  if ( mina > 0 )
  {
    v10 = &this->debugGraph[0][255][1];
    v11 = mina;
    do
    {
      *(v10 - 1) = 0;
      *v10 = 0;
      v10[1] = 0;
      v10[2] = 0;
      v10 += 1024;
      --v11;
    }
    while ( v11 );
  }
  if ( mina < 64 )
  {
    v12 = &this->debugGraph[mina][255][1];
    v13 = 64 - mina;
    do
    {
      *v12 = (unsigned __int8)colora;
      v12[1] = v14;
      *(v12 - 1) = cura;
      v12[2] = (int)maxa;
      v12 += 1024;
      --v13;
    }
    while ( v13 );
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::CopyPrimBatchTriangles(class idDrawVert *,int *,class rvMesh *,class rvSilTraceVertT const *)
void __thiscall idRenderSystemLocal::CopyPrimBatchTriangles(
        idRenderSystemLocal *this,
        idDrawVert *destDrawVerts,
        int *destIndices,
        rvMesh *primBatchMesh,
        const rvSilTraceVertT *silTraceVerts)
{
  rvMesh::CopyTriangles(primBatchMesh, destDrawVerts, destIndices, silTraceVerts);
}

// FUNC: R_PerformanceCounters
int R_PerformanceCounters()
{
  idGame_vtbl *v0; // esi
  double v1; // st7
  int v2; // esi
  int v3; // eax
  int result; // eax
  int memoryHighwater; // [esp+50h] [ebp-18h]
  __int64 v6; // [esp+60h] [ebp-8h]

  if ( com_debugHudActive )
  {
    game->DebugSetInt(game, "r_views", tr.pc.c_numViews);
    game->DebugSetInt(game, "r_draws", backEnd.pc.c_drawElements + backEnd.pc.c_shadowElements);
    game->DebugSetInt(game, "r_verts", backEnd.pc.c_drawVertexes + backEnd.pc.c_shadowVertexes);
    game->DebugSetInt(game, "r_tris", (backEnd.pc.c_shadowIndexes + backEnd.pc.c_drawIndexes) / 3);
    game->DebugSetInt(game, "r_shadowtris", backEnd.pc.c_shadowIndexes / 3);
    v0 = game->__vftable;
    v6 = (__int64)((double)globalImages->SumOfUsedImages(globalImages) * 0.00000095367431640625);
    v0->DebugSetInt(game, "r_mbytes", v6);
    game->DebugSetInt(game, "r_viewEnts", tr.pc.c_visibleViewEntities);
    game->DebugSetInt(game, "r_shadowEnts", tr.pc.c_shadowViewEntities);
    game->DebugSetInt(game, "r_viewLights", tr.pc.c_viewLights);
  }
  if ( r_showPrimitives.internalVar->integerValue )
  {
    v1 = (double)globalImages->SumOfUsedImages(globalImages) * 0.00000095367431640625;
    if ( r_showPrimitives.internalVar->integerValue <= 1 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "views:%i draws:%i tris:%i (shdw:%i) (vbo:%i) image:%5.1f MB\n",
        tr.pc.c_numViews,
        backEnd.pc.c_drawElements + backEnd.pc.c_shadowElements,
        (backEnd.pc.c_shadowIndexes + backEnd.pc.c_drawIndexes) / 3,
        backEnd.pc.c_shadowIndexes / 3,
        backEnd.pc.c_vboIndexes / 3,
        v1);
    else
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "v:%i ds:%i t:%i/%i v:%i/%i st:%i sv:%i image:%5.1f MB\n",
        tr.pc.c_numViews,
        backEnd.pc.c_drawElements + backEnd.pc.c_shadowElements,
        backEnd.pc.c_drawIndexes / 3,
        (backEnd.pc.c_drawIndexes - backEnd.pc.c_drawRefIndexes) / 3,
        backEnd.pc.c_drawVertexes,
        backEnd.pc.c_drawVertexes - backEnd.pc.c_drawRefVertexes,
        backEnd.pc.c_shadowIndexes / 3,
        backEnd.pc.c_shadowVertexes,
        v1);
  }
  if ( r_showDynamic.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "callback:%i md5:%i dfrmVerts:%i dfrmTris:%i tangTris:%i guis:%i decals:%i\n",
      tr.pc.c_entityDefCallbacks,
      tr.pc.c_generateMd5,
      tr.pc.c_deformedVerts,
      tr.pc.c_deformedIndexes / 3,
      tr.pc.c_tangentIndexes / 3,
      tr.pc.c_guiSurfs,
      tr.pc.c_numDecalIndexes / 3);
  if ( r_showCull.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%i sin %i sclip  %i sout %i bin %i bout\n",
      tr.pc.c_sphere_cull_in,
      tr.pc.c_sphere_cull_clip,
      tr.pc.c_sphere_cull_out,
      tr.pc.c_box_cull_in,
      tr.pc.c_box_cull_out);
  if ( r_showAlloc.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "alloc:%i free:%i\n",
      tr.pc.c_alloc,
      tr.pc.c_free);
  if ( r_showInteractions.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "createInteractions:%i createLightTris:%i createShadowVolumes:%i\n",
      tr.pc.c_createInteractions,
      tr.pc.c_createLightTris,
      tr.pc.c_createShadowVolumes);
  if ( r_showDefs.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "viewEnts:%i  shadowEnts:%i  viewLghts:%i  pushes:%i  viewEff:%i  culledEff:%i\n",
      tr.pc.c_visibleViewEntities,
      tr.pc.c_shadowViewEntities,
      tr.pc.c_viewLights,
      tr.pc.c_numVolumePushes,
      tr.pc.c_visibleViewEffects,
      tr.pc.c_culledViewEffects);
  if ( r_showUpdates.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "ents:%3i/%3i/%3i lights:%3i/%3i/%3i effects:%3i/%3i/%3i\n",
      tr.pc.c_entityUpdates,
      tr.pc.c_entityPushes,
      tr.pc.c_entityPushesSuppressed,
      tr.pc.c_lightUpdates,
      tr.pc.c_lightPushes,
      tr.pc.c_lightPushesSuppressed,
      tr.pc.c_effectUpdates,
      tr.pc.c_effectPushes,
      tr.pc.c_effectPushesSuppressed);
  if ( r_showMemory.internalVar->integerValue )
  {
    v2 = *(_DWORD *)common.type;
    memoryHighwater = frameData[0]->memoryHighwater;
    v3 = R_CountFrameData();
    (*(void (**)(netadrtype_t, const char *, ...))(v2 + 124))(common.type, "frameData: %i (%i)\n", v3, memoryHighwater);
  }
  if ( r_showLightScale.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "lightScale: %f\n",
      backEnd.pc.maxLightValue);
  if ( r_showRenderTrace.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Num render model polys trace tested: %d\n",
      backEnd.pc.c_renderPolysTraceTested);
  SIMDProcessor->Memcpy(SIMDProcessor, &tr.mSavePC, &tr.pc, 156);
  result = 0;
  memset(&tr.pc, 0, sizeof(tr.pc));
  memset(&backEnd.pc, 0, sizeof(backEnd.pc));
  return result;
}

// FUNC: R_IssueRenderCommands
void R_IssueRenderCommands()
{
  frameData_t *v0; // ecx
  emptyCommand_t *cmdHead; // eax

  v0 = frameData[tr.smpFrame];
  cmdHead = v0->cmdHead;
  if ( cmdHead->commandId || cmdHead->next )
  {
    if ( !r_skipBackEnd.internalVar->integerValue )
      RB_ExecuteBackEndCommands(v0->cmdHead);
    R_ClearCommandChain();
  }
}

// FUNC: void __cdecl R_AddDrawViewCmd(struct viewDef_s *)
void __cdecl R_AddDrawViewCmd(viewDef_s *parms)
{
  emptyCommand_t *CommandBufferDeferred; // eax

  if ( (parms->renderFlags & 0x20) != 0 )
  {
    CommandBufferDeferred = R_GetCommandBufferDeferred(12);
  }
  else
  {
    R_SubmitDeferredCommands();
    CommandBufferDeferred = (emptyCommand_t *)R_FrameAlloc(12);
    CommandBufferDeferred->next = 0;
    frameData[tr.smpFrame]->cmdTail->next = &CommandBufferDeferred->commandId;
    frameData[tr.smpFrame]->cmdTail = CommandBufferDeferred;
  }
  CommandBufferDeferred->commandId = RC_DRAW_VIEW;
  CommandBufferDeferred[1].commandId = (renderCommand_t)parms;
  if ( parms->viewEntitys )
    tr.lockSurfacesCmd = *(drawSurfsCommand_t *)&CommandBufferDeferred->commandId;
  ++tr.pc.c_numViews;
  if ( r_showSurfaces.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "view:%p surfs:%i\n",
      parms,
      parms->numDrawSurfs);
}

// FUNC: R_CheckCvars
idCVar *R_CheckCvars()
{
  idCVar *result; // eax
  int integerValue; // eax

  globalImages->CheckCvars(globalImages);
  if ( (r_gamma.internalVar->flags & 0x40000) != 0 || (r_brightness.internalVar->flags & 0x40000) != 0 )
  {
    BYTE2(r_gamma.internalVar->flags) &= ~4u;
    BYTE2(r_brightness.internalVar->flags) &= ~4u;
    R_SetColorMappings();
  }
  result = r_testSpecialEffect.internalVar;
  if ( (r_testSpecialEffect.internalVar->flags & 0x40000) != 0 )
  {
    integerValue = r_testSpecialEffect.internalVar->integerValue;
    if ( integerValue )
    {
      renderSystem->SetSpecialEffect(renderSystem, (ESpecialEffectType)integerValue, 1);
      ((void (__thiscall *)(idRenderSystem *, int, int, _DWORD))renderSystem->SetSpecialEffectParm)(
        renderSystem,
        r_testSpecialEffect.internalVar->integerValue,
        r_testSpecialEffectParm.internalVar->integerValue,
        LODWORD(r_testSpecialEffectParmValue.internalVar->floatValue));
    }
    else
    {
      renderSystem->ShutdownSpecialEffects(renderSystem);
    }
    result = r_testSpecialEffect.internalVar;
    BYTE2(r_testSpecialEffect.internalVar->flags) &= ~4u;
  }
  return result;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::SetColor(class idVec4 const &)
void __thiscall idRenderSystemLocal::SetColor(idRenderSystemLocal *this, const idVec4 *rgba)
{
  idGuiModel::SetColor(this->guiModel, rgba->x, rgba->y, rgba->z, rgba->w);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawTinyStringExt(int,int,char const *,class idVec4 const &,bool,class idMaterial const *)
void __thiscall idRenderSystemLocal::DrawTinyStringExt(
        idRenderSystemLocal *this,
        int x,
        int y,
        const char *string,
        const idVec4 *setColor,
        char forceColor,
        const idMaterial *material)
{
  const char *v9; // edi
  int IsEscape; // ebx
  unsigned __int8 v11; // al
  idVec4 *v12; // eax
  float w; // ecx
  idRenderSystemLocal_vtbl *v14; // edx
  idVec4 color; // [esp+Ch] [ebp-10h] BYREF

  v9 = string;
  this->SetColor(this, setColor);
  if ( *v9 )
  {
    while ( 1 )
    {
      IsEscape = idStr::IsEscape(v9, (int *)&string);
      if ( !IsEscape )
      {
        this->DrawTinyChar(this, x, y, *(unsigned __int8 *)v9, material);
        x += 4;
        ++v9;
        goto LABEL_10;
      }
      if ( forceColor || ((unsigned __int8)string & 4) == 0 )
        goto LABEL_8;
      v11 = v9[1];
      if ( v11 != 48 )
        break;
      this->SetColor(this, setColor);
      v9 += IsEscape;
LABEL_10:
      if ( !*v9 )
        goto LABEL_11;
    }
    v12 = idStr::ColorForIndex(v11);
    color.x = v12->x;
    color.y = v12->y;
    color.z = v12->z;
    w = setColor->w;
    color.w = v12->w;
    v14 = this->__vftable;
    color.w = w;
    v14->SetColor(this, &color);
LABEL_8:
    v9 += IsEscape;
    goto LABEL_10;
  }
LABEL_11:
  this->SetColor(this, &colorWhite);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawSmallStringExt(int,int,char const *,class idVec4 const &,bool,class idMaterial const *)
void __thiscall idRenderSystemLocal::DrawSmallStringExt(
        idRenderSystemLocal *this,
        int x,
        int y,
        const char *string,
        const idVec4 *setColor,
        char forceColor,
        const idMaterial *material)
{
  const char *v9; // edi
  int IsEscape; // ebx
  unsigned __int8 v11; // al
  idVec4 *v12; // eax
  float w; // ecx
  idRenderSystemLocal_vtbl *v14; // edx
  idVec4 color; // [esp+Ch] [ebp-10h] BYREF

  v9 = string;
  this->SetColor(this, setColor);
  if ( *v9 )
  {
    while ( 1 )
    {
      IsEscape = idStr::IsEscape(v9, (int *)&string);
      if ( !IsEscape )
      {
        this->DrawSmallChar(this, x, y, *(unsigned __int8 *)v9, material);
        x += 8;
        ++v9;
        goto LABEL_10;
      }
      if ( forceColor || ((unsigned __int8)string & 4) == 0 )
        goto LABEL_8;
      v11 = v9[1];
      if ( v11 != 48 )
        break;
      this->SetColor(this, setColor);
      v9 += IsEscape;
LABEL_10:
      if ( !*v9 )
        goto LABEL_11;
    }
    v12 = idStr::ColorForIndex(v11);
    color.x = v12->x;
    color.y = v12->y;
    color.z = v12->z;
    w = setColor->w;
    color.w = v12->w;
    v14 = this->__vftable;
    color.w = w;
    v14->SetColor(this, &color);
LABEL_8:
    v9 += IsEscape;
    goto LABEL_10;
  }
LABEL_11:
  this->SetColor(this, &colorWhite);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::DrawBigStringExt(int,int,char const *,class idVec4 const &,bool,class idMaterial const *)
void __thiscall idRenderSystemLocal::DrawBigStringExt(
        idRenderSystemLocal *this,
        int x,
        int y,
        const char *string,
        const idVec4 *setColor,
        char forceColor,
        const idMaterial *material)
{
  const char *v9; // edi
  int IsEscape; // ebx
  char v11; // al
  idVec4 *v12; // eax
  float w; // ecx
  idRenderSystemLocal_vtbl *v14; // edx
  idVec4 color; // [esp+Ch] [ebp-10h] BYREF

  v9 = string;
  this->SetColor(this, setColor);
  if ( *v9 )
  {
    while ( 1 )
    {
      IsEscape = idStr::IsEscape(v9, (int *)&string);
      if ( !IsEscape )
      {
        this->DrawBigChar(this, x, y, *v9, material);
        x += 16;
        ++v9;
        goto LABEL_10;
      }
      if ( forceColor || ((unsigned __int8)string & 4) == 0 )
        goto LABEL_8;
      v11 = v9[1];
      if ( v11 != 48 )
        break;
      this->SetColor(this, setColor);
      v9 += IsEscape;
LABEL_10:
      if ( !*v9 )
        goto LABEL_11;
    }
    v12 = idStr::ColorForIndex(v11);
    color.x = v12->x;
    color.y = v12->y;
    color.z = v12->z;
    w = setColor->w;
    color.w = v12->w;
    v14 = this->__vftable;
    color.w = w;
    v14->SetColor(this, &color);
LABEL_8:
    v9 += IsEscape;
    goto LABEL_10;
  }
LABEL_11:
  this->SetColor(this, &colorWhite);
}

// FUNC: public: void __thiscall idRenderSystemLocal::SetBackEndRenderer(void)
void __thiscall idRenderSystemLocal::SetBackEndRenderer(idRenderSystemLocal *this)
{
  bool backEndRendererHasVertexPrograms; // dl
  backEndName_t backEndRenderer; // eax
  idRenderWorldLocal *primaryWorld; // ecx
  bool oldVPstate; // [esp+7h] [ebp-1h]

  if ( (r_renderer.internalVar->flags & 0x40000) != 0 )
  {
    backEndRendererHasVertexPrograms = this->backEndRendererHasVertexPrograms;
    this->backEndRenderer = BE_BAD;
    oldVPstate = backEndRendererHasVertexPrograms;
    if ( idStr::Icmp(r_renderer.internalVar->value, "arb") )
    {
      if ( idStr::Icmp(r_renderer.internalVar->value, "arb2") )
      {
        if ( idStr::Icmp(r_renderer.internalVar->value, "nv10") )
        {
          if ( idStr::Icmp(r_renderer.internalVar->value, "nv20") )
          {
            if ( !idStr::Icmp(r_renderer.internalVar->value, "r200") && glConfig.allowR200Path )
              this->backEndRenderer = BE_R200;
          }
          else if ( glConfig.allowNV20Path )
          {
            this->backEndRenderer = BE_NV20;
          }
        }
        else if ( glConfig.allowNV10Path )
        {
          this->backEndRenderer = BE_NV10;
        }
      }
      else if ( glConfig.allowARB2Path )
      {
        this->backEndRenderer = BE_ARB2;
      }
    }
    else
    {
      this->backEndRenderer = BE_ARB;
    }
    if ( this->backEndRenderer == BE_BAD )
    {
      if ( !glConfig.allowARB2Path || glConfig.preferNV20Path )
      {
        if ( glConfig.allowR200Path )
        {
          this->backEndRenderer = BE_R200;
        }
        else if ( glConfig.allowNV20Path )
        {
          this->backEndRenderer = BE_NV20;
        }
        else
        {
          this->backEndRenderer = glConfig.allowNV10Path;
        }
      }
      else
      {
        this->backEndRenderer = BE_ARB2;
      }
    }
    backEndRenderer = this->backEndRenderer;
    this->backEndRendererHasVertexPrograms = 0;
    this->backEndRendererMaxLight = 1.0;
    switch ( backEndRenderer )
    {
      case BE_ARB:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "using ARB renderSystem\n");
        r_actualRenderer.internalVar->InternalSetString(r_actualRenderer.internalVar, "ARB");
        break;
      case BE_NV10:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "using NV10 renderSystem\n");
        r_actualRenderer.internalVar->InternalSetString(r_actualRenderer.internalVar, "NV10");
        break;
      case BE_NV20:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "using NV20 renderSystem\n");
        this->backEndRendererHasVertexPrograms = 1;
        r_actualRenderer.internalVar->InternalSetString(r_actualRenderer.internalVar, "NV20");
        break;
      case BE_R200:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "using R200 renderSystem\n");
        this->backEndRendererHasVertexPrograms = 1;
        r_actualRenderer.internalVar->InternalSetString(r_actualRenderer.internalVar, "R200");
        break;
      case BE_ARB2:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "using ARB2 renderSystem\n");
        this->backEndRendererHasVertexPrograms = 1;
        this->backEndRendererMaxLight = 999.0;
        r_actualRenderer.internalVar->InternalSetString(r_actualRenderer.internalVar, "ARB2");
        if ( !glConfig.preferSimpleLighting )
          ((void (__thiscall *)(idCVar *, _DWORD))r_lightDetailLevel.internalVar->InternalSetFloat)(
            r_lightDetailLevel.internalVar,
            0);
        break;
      default:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
          common.type,
          "SetbackEndRenderer: bad back end");
        break;
    }
    if ( oldVPstate != this->backEndRendererHasVertexPrograms )
    {
      idVertexCache::PurgeAll(&vertexCache);
      primaryWorld = this->primaryWorld;
      if ( primaryWorld )
        idRenderWorldLocal::FreeInteractions(primaryWorld);
    }
    BYTE2(r_renderer.internalVar->flags) &= ~4u;
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::BeginFrame(int,int)
void __thiscall idRenderSystemLocal::BeginFrame(idRenderSystemLocal *this, int windowWidth, int windowHeight)
{
  int v4; // ecx
  int v5; // eax
  _DWORD *CommandBufferDeferred; // eax

  if ( glConfig.isInitialized )
  {
    bse->UpdateRateTimes(bse);
    idRenderSystemLocal::SetBackEndRenderer(this);
    idGuiModel::Clear(this->guiModel);
    v4 = this->tiledViewport[0];
    if ( v4 )
    {
      v5 = this->tiledViewport[1];
    }
    else
    {
      v5 = windowHeight;
      v4 = windowWidth;
    }
    glConfig.vidHeight = v5;
    glConfig.vidWidth = v4;
    this->renderCrops[0].x = 0;
    this->renderCrops[0].y = 0;
    this->renderCrops[0].width = v4;
    this->renderCrops[0].height = v5;
    this->currentRenderCrop = 0;
    if ( r_screenFraction.internalVar->integerValue != 100 )
      this->CropRenderSize(
        this,
        (int)((double)(640 * r_screenFraction.internalVar->integerValue) * 0.0099999998),
        (int)((double)(480 * r_screenFraction.internalVar->integerValue) * 0.0099999998),
        0,
        0);
    backEnd.currentRenderCopied = 0;
    ++this->frameCount;
    this->guiRecursionLevel = 0;
    this->frameShaderTime = (double)idEventLoop::Milliseconds(eventLoop) * 0.001;
    CommandBufferDeferred = R_GetCommandBufferDeferred(16);
    *CommandBufferDeferred = 3;
    CommandBufferDeferred[3] = this->frameCount;
    CommandBufferDeferred[2] = 1029 - (r_frontBuffer.internalVar->integerValue != 0);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::WriteDemoPics(void)
void __thiscall idRenderSystemLocal::WriteDemoPics(idRenderSystemLocal *this)
{
  if ( r_showDemo.internalVar->integerValue )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "DC_GUI_MODEL\n");
  session->writeDemo->WriteChar(session->writeDemo, 1);
  session->writeDemo->WriteChar(session->writeDemo, 20);
  idGuiModel::WriteToDemo(this->guiModel, session->writeDemo);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::CropRenderSize(int,int,bool,bool)
void __thiscall idRenderSystemLocal::CropRenderSize(
        idRenderSystemLocal *this,
        int width,
        int height,
        bool makePowerOfTwo,
        bool forceDimensions)
{
  int v6; // edi
  int v7; // esi
  renderCrop_t *v8; // eax
  idScreenRect r; // [esp+14h] [ebp-98h] BYREF
  renderView_s renderView; // [esp+24h] [ebp-88h] BYREF

  if ( glConfig.isInitialized )
  {
    idGuiModel::EmitFullScreen(this->guiModel);
    idGuiModel::Clear(this->guiModel);
    if ( width < 1 || height < 1 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "CropRenderSize: bad sizes");
    if ( session->writeDemo )
    {
      session->writeDemo->WriteChar(session->writeDemo, 1);
      session->writeDemo->WriteChar(session->writeDemo, 14);
      session->writeDemo->WriteInt(session->writeDemo, width);
      session->writeDemo->WriteInt(session->writeDemo, height);
      session->writeDemo->WriteInt(session->writeDemo, makePowerOfTwo);
      if ( r_showDemo.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_CROP_RENDER\n");
    }
    renderView.x = 0;
    renderView.y = 0;
    renderView.width = width;
    renderView.height = height;
    idRenderSystemLocal::RenderViewToViewport(this, &renderView, &r);
    v6 = r.x2 - r.x1 + 1;
    v7 = r.y2 - r.y1 + 1;
    if ( forceDimensions )
    {
      v7 = renderView.height;
      v6 = width;
    }
    if ( makePowerOfTwo )
    {
      v6 = RoundDownToPowerOfTwo(v6);
      v7 = RoundDownToPowerOfTwo(v7);
    }
    for ( ; v6 > glConfig.vidWidth; v6 >>= 1 )
      ;
    for ( ; v7 > glConfig.vidHeight; v7 >>= 1 )
      ;
    if ( this->currentRenderCrop == 8 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "idRenderSystemLocal::CropRenderSize: currentRenderCrop == MAX_RENDER_CROPS");
    v8 = &this->renderCrops[++this->currentRenderCrop];
    v8->width = v6;
    v8->height = v7;
    v8->x = 0;
    v8->y = 0;
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::UnCrop(void)
void __thiscall idRenderSystemLocal::UnCrop(idRenderSystemLocal *this)
{
  if ( glConfig.isInitialized )
  {
    if ( this->currentRenderCrop < 1 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "idRenderSystemLocal::UnCrop: currentRenderCrop < 1");
    idGuiModel::EmitFullScreen(this->guiModel);
    idGuiModel::Clear(this->guiModel);
    --this->currentRenderCrop;
    if ( session->writeDemo )
    {
      session->writeDemo->WriteChar(session->writeDemo, 1);
      session->writeDemo->WriteChar(session->writeDemo, 15);
      if ( r_showDemo.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "DC_UNCROP\n");
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::CaptureRenderToImage(char const *)
void __thiscall idRenderSystemLocal::CaptureRenderToImage(idRenderSystemLocal *this, const char *imageName)
{
  idImage *v3; // ebx
  renderCrop_t *v4; // esi
  emptyCommand_t *v5; // eax

  if ( glConfig.isInitialized )
  {
    idGuiModel::EmitFullScreen(this->guiModel);
    idGuiModel::Clear(this->guiModel);
    if ( session->writeDemo )
    {
      session->writeDemo->WriteChar(session->writeDemo, 1);
      session->writeDemo->WriteChar(session->writeDemo, 16);
      idDemoFile::WriteHashString(session->writeDemo, imageName);
      if ( r_showDemo.internalVar->integerValue )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_CAPTURE_RENDER: %s\n",
          imageName);
    }
    v3 = globalImages->ImageFromFile(globalImages, imageName, 2, 1, 0, 2, 0, 0);
    v4 = &this->renderCrops[this->currentRenderCrop];
    R_SubmitDeferredCommands();
    v5 = (emptyCommand_t *)R_FrameAlloc(32);
    v5->next = 0;
    frameData[tr.smpFrame]->cmdTail->next = &v5->commandId;
    frameData[tr.smpFrame]->cmdTail = v5;
    v5->commandId = RC_COPY_RENDER;
    v5[1].commandId = v4->x;
    v5[1].next = (renderCommand_t *)v4->y;
    v5[2].commandId = v4->width;
    v5[2].next = (renderCommand_t *)v4->height;
    v5[3].commandId = (renderCommand_t)v3;
    v5[3].next = (renderCommand_t *)v3->cubeFaceBound;
    idGuiModel::Clear(this->guiModel);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::CaptureRenderToMemory(void *)
void __thiscall idRenderSystemLocal::CaptureRenderToMemory(idRenderSystemLocal *this, char *buffer)
{
  renderCrop_t *v3; // edi
  int v4; // esi
  char *v5; // ebp
  char *v6; // eax
  char *v7; // ecx

  if ( glConfig.isInitialized )
  {
    v3 = &this->renderCrops[this->currentRenderCrop];
    idGuiModel::EmitFullScreen(this->guiModel);
    idGuiModel::Clear(this->guiModel);
    R_IssueRenderCommands();
    qglReadBuffer(0x405u);
    v4 = v3->height * (v3->width + 3);
    v5 = (char *)R_StaticAlloc(3 * v4);
    qglReadPixels(v3->x, v3->y, v3->width, v3->height, 0x1907u, 0x1401u, v5);
    if ( v4 > 0 )
    {
      v6 = buffer + 2;
      v7 = v5 + 2;
      do
      {
        *(v6 - 2) = *(v7 - 2);
        *(v6 - 1) = *(v7 - 1);
        *v6 = *v7;
        v6[1] = -1;
        v7 += 3;
        v6 += 4;
        --v4;
      }
      while ( v4 );
    }
    R_StaticFree(v5);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::CaptureRenderToFile(char const *,bool)
void __thiscall idRenderSystemLocal::CaptureRenderToFile(
        idRenderSystemLocal *this,
        const char *fileName,
        bool fixAlpha)
{
  renderCrop_t *v4; // edi
  int v5; // esi
  char *v6; // ebp
  unsigned __int8 *v7; // eax
  unsigned __int8 *v8; // ebx
  _BYTE *v9; // eax
  _BYTE *v10; // ecx

  if ( glConfig.isInitialized )
  {
    v4 = &this->renderCrops[this->currentRenderCrop];
    idGuiModel::EmitFullScreen(this->guiModel);
    idGuiModel::Clear(this->guiModel);
    R_IssueRenderCommands();
    qglReadBuffer(0x405u);
    v5 = v4->height * (v4->width + 3);
    v6 = (char *)R_StaticAlloc(3 * v5);
    qglReadPixels(v4->x, v4->y, v4->width, v4->height, 0x1907u, 0x1401u, v6);
    v7 = (unsigned __int8 *)R_StaticAlloc(4 * v5);
    v8 = v7;
    if ( v5 > 0 )
    {
      v9 = v7 + 2;
      v10 = v6 + 2;
      do
      {
        *(v9 - 2) = *(v10 - 2);
        *(v9 - 1) = *(v10 - 1);
        *v9 = *v10;
        v9[1] = -1;
        v10 += 3;
        v9 += 4;
        --v5;
      }
      while ( v5 );
    }
    R_WriteTGA(fileName, v8, v4->width, v4->height, 1);
    R_StaticFree(v6);
    R_StaticFree(v8);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::ShowDebugGraph(void)
void __thiscall idRenderSystemLocal::ShowDebugGraph(idRenderSystemLocal *this)
{
  if ( r_showDebugGraph.internalVar->integerValue )
  {
    ((void (__stdcall *)(const char *, unsigned __int8 (*)[256][4], int, int))this->UploadImage)(
      "textures/common/debuggraph.tga",
      this->debugGraph,
      256,
      64);
    ((void (__thiscall *)(idRenderSystemLocal *, int, int, int, int))this->SetColor4)(
      this,
      1065353216,
      1065353216,
      1065353216,
      1065353216);
    (*((void (__thiscall **)(idRenderSystemLocal *, int, int, int, int, _DWORD, _DWORD, int, int, const idMaterial *))&this->SetColor4
     + 1))(
      this,
      1092616192,
      1136525312,
      1132462080,
      1115684864,
      0,
      0,
      1065353216,
      1065353216,
      this->debugGraphMaterial);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::RemoveAllModelReferences(class idRenderModel *)
void __thiscall idRenderSystemLocal::RemoveAllModelReferences(idRenderSystemLocal *this, idRenderModel *model)
{
  int i; // esi
  idRenderWorldLocal *v4; // ecx

  for ( i = 0; i < this->worlds.num; ++i )
  {
    v4 = this->worlds.list[i];
    v4->RemoveAllModelReferences(v4, model);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::ExportMD5R(bool)
void __thiscall idRenderSystemLocal::ExportMD5R(idRenderSystemLocal *this, bool compressed)
{
  int i; // esi

  rvRenderModelMD5R::WriteAll(compressed);
  for ( i = 0; i < this->worlds.num; ++i )
    idRenderWorldLocal::WriteMD5R(this->worlds.list[i], compressed);
}

// FUNC: public: __thiscall idRenderSystemLocal::idRenderSystemLocal(void)
void __thiscall idRenderSystemLocal::idRenderSystemLocal(idRenderSystemLocal *this)
{
  this->__vftable = (idRenderSystemLocal_vtbl *)&idRenderSystemLocal::`vftable';
  this->lastLoadedImage.len = 0;
  this->lastLoadedImage.alloced = 20;
  this->lastLoadedImage.data = this->lastLoadedImage.baseBuffer;
  this->lastLoadedImage.baseBuffer[0] = 0;
  this->worlds.granularity = 16;
  this->worlds.list = 0;
  this->worlds.num = 0;
  this->worlds.size = 0;
  idRenderSystemLocal::Clear(this);
}

// FUNC: public: virtual __thiscall idRenderSystemLocal::~idRenderSystemLocal(void)
void __thiscall idRenderSystemLocal::~idRenderSystemLocal(idRenderSystemLocal *this)
{
  idRenderWorldLocal **list; // eax

  this->__vftable = (idRenderSystemLocal_vtbl *)&idRenderSystemLocal::`vftable';
  list = this->worlds.list;
  if ( list )
    Memory::Free(list);
  this->worlds.list = 0;
  this->worlds.num = 0;
  this->worlds.size = 0;
  idStr::FreeData(&this->lastLoadedImage);
  this->__vftable = (idRenderSystemLocal_vtbl *)&idRenderSystem::`vftable';
}

// FUNC: public: void __thiscall idRenderSystemLocal::DrawLimits(class idGuiModel *)
void __thiscall idRenderSystemLocal::DrawLimits(idRenderSystemLocal *this, idGuiModel *gui)
{
  idDeclManager_vtbl *v3; // edx
  const idMaterial *v4; // edi
  const idMaterial *v5; // ebx
  idAngles *v6; // eax
  char *v7; // eax
  int v8; // ebp
  double v9; // st7
  idRenderSystemLocal_vtbl *v10; // eax
  const char *v11; // eax
  const char *v12; // ebp
  int v13; // edx
  char v14; // cl
  int v15; // eax
  char *v16; // edx
  unsigned int v17; // eax
  int integerValue; // ecx
  unsigned int v19; // eax
  int v20; // ecx
  int v21; // ecx
  unsigned int v22; // ebp
  double v23; // st7
  idRenderSystemLocal_vtbl *v24; // edx
  const char *v25; // eax
  const char *v26; // ebp
  int v27; // edx
  char v28; // cl
  int v29; // eax
  char *v30; // edx
  signed int v31; // ebp
  double v32; // st7
  idRenderSystemLocal_vtbl *v33; // eax
  const char *v34; // eax
  const char *v35; // ebp
  int v36; // edx
  char v37; // cl
  int v38; // eax
  char *v39; // edx
  const idMaterial *v40; // ebp
  double v41; // st7
  idRenderSystemLocal_vtbl *v42; // eax
  const char *v43; // eax
  const char *v44; // edi
  int v45; // ebx
  char v46; // cl
  int i; // eax
  char *v48; // edx
  float percent; // [esp+154h] [ebp-99Ch]
  int percenta; // [esp+154h] [ebp-99Ch]
  float percentb; // [esp+154h] [ebp-99Ch]
  int percentc; // [esp+154h] [ebp-99Ch]
  float percentd; // [esp+154h] [ebp-99Ch]
  int percente; // [esp+154h] [ebp-99Ch]
  float percentf; // [esp+154h] [ebp-99Ch]
  idAngles result; // [esp+158h] [ebp-998h] BYREF
  float v57; // [esp+164h] [ebp-98Ch]
  const idMaterial *white; // [esp+168h] [ebp-988h]
  idVec4 color; // [esp+16Ch] [ebp-984h] BYREF
  idStr clipboardInfo; // [esp+17Ch] [ebp-974h] BYREF
  idGuiModel *saveGui; // [esp+19Ch] [ebp-954h]
  char msg[64]; // [esp+1A0h] [ebp-950h] BYREF
  idCmdArgs args; // [esp+1E0h] [ebp-910h] BYREF
  int v64; // [esp+AECh] [ebp-4h]

  if ( com_Limits.internalVar->integerValue
    && !(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, -1) )
  {
    v3 = declManager->__vftable;
    saveGui = this->guiModel;
    v4 = v3->FindMaterial(declManager, "gfx/2d/bigchars", 1);
    v5 = declManager->FindMaterial(declManager, "_white", 1);
    white = v5;
    args.argc = 0;
    clipboardInfo.len = 0;
    clipboardInfo.alloced = 20;
    clipboardInfo.data = clipboardInfo.baseBuffer;
    clipboardInfo.baseBuffer[0] = 0;
    v64 = 0;
    v6 = idMat3::ToAngles(&tr.primaryRenderView.viewaxis, &result);
    v7 = va(
           "Origin: %g %g %g %g\r\n",
           tr.primaryRenderView.vieworg.x,
           tr.primaryRenderView.vieworg.y,
           tr.primaryRenderView.vieworg.z,
           v6->yaw);
    idStr::operator=(&clipboardInfo, v7);
    this->guiModel = gui;
    v8 = (backEnd.pc.c_drawIndexes + backEnd.pc.c_shadowIndexes) / 3 - 100000;
    v9 = (double)v8 * 0.000019999999;
    percent = v9;
    if ( v9 > 0.0 )
    {
      if ( percent > 1.0 )
        percent = 1.0;
      idStr::snPrintf(msg, 64, "%d", v8);
      v57 = percent;
      result.roll = 0.0;
      color.z = 0.0;
      result.pitch = 1.0;
      result.yaw = 0.0;
      color.x = 1.0;
      color.y = 0.0;
      v10 = this->__vftable;
      color.w = percent;
      v10->SetColor(this, &color);
      (*((void (__thiscall **)(idRenderSystemLocal *, int, int, int, int, _DWORD, _DWORD, int, int, const idMaterial *))&this->SetColor4
       + 1))(
        this,
        1141145600,
        1112014848,
        1120403456,
        1109393408,
        0,
        0,
        1065353216,
        1065353216,
        v5);
      this->DrawSmallStringExt(this, 532, 54, "Scene Tris", &colorWhite, 1, v4);
      this->DrawSmallStringExt(this, 532, 70, msg, &colorWhite, 1, v4);
      v11 = va("Scene Tris Over: %d\r\n", v8);
      v12 = v11;
      if ( v11 )
      {
        v13 = strlen(v11) + clipboardInfo.len;
        percenta = v13;
        if ( v13 + 1 > clipboardInfo.alloced )
        {
          idStr::ReAllocate(&clipboardInfo, v13 + 1, 1);
          v13 = percenta;
        }
        v14 = *v12;
        v15 = 0;
        if ( *v12 )
        {
          do
          {
            v16 = &clipboardInfo.data[v15++];
            v16[clipboardInfo.len] = v14;
            v14 = v12[v15];
          }
          while ( v14 );
          v5 = white;
          v13 = percenta;
        }
        clipboardInfo.len = v13;
        clipboardInfo.data[v13] = 0;
      }
    }
    idCmdArgs::TokenizeString(&args, "showmemory noprint", 0);
    v17 = globalImages->ListImageSummary(globalImages);
    integerValue = com_machineSpec.internalVar->integerValue;
    v19 = v17 >> 20;
    if ( integerValue )
    {
      v20 = integerValue - 1;
      if ( v20 )
      {
        if ( v20 == 1 )
          v21 = 200;
        else
          v21 = 99999;
      }
      else
      {
        v21 = 80;
      }
    }
    else
    {
      v21 = 45;
    }
    v22 = v19 - v21;
    v23 = (double)(int)(v19 - v21) / (double)(v21 / 4);
    percentb = v23;
    if ( v23 > 0.0 )
    {
      if ( percentb > 1.0 )
        percentb = 1.0;
      idStr::snPrintf(msg, 64, "%d megs", v22);
      v57 = percentb;
      result.pitch = 0.0;
      result.roll = 0.0;
      color.x = 0.0;
      result.yaw = 1.0;
      color.z = 0.0;
      color.y = 1.0;
      v24 = this->__vftable;
      color.w = percentb;
      v24->SetColor(this, &color);
      (*((void (__thiscall **)(idRenderSystemLocal *, int, int, int, int, _DWORD, _DWORD, int, int, const idMaterial *))&this->SetColor4
       + 1))(
        this,
        1141145600,
        1125515264,
        1120403456,
        1109393408,
        0,
        0,
        1065353216,
        1065353216,
        v5);
      this->DrawSmallStringExt(this, 532, 154, "Textures", &colorWhite, 1, v4);
      this->DrawSmallStringExt(this, 532, 170, msg, &colorWhite, 1, v4);
      v25 = va("Texture Memory Over: %d megs\r\n", v22);
      v26 = v25;
      if ( v25 )
      {
        v27 = strlen(v25) + clipboardInfo.len;
        percentc = v27;
        if ( v27 + 1 > clipboardInfo.alloced )
        {
          idStr::ReAllocate(&clipboardInfo, v27 + 1, 1);
          v27 = percentc;
        }
        v28 = *v26;
        v29 = 0;
        if ( *v26 )
        {
          do
          {
            v30 = &clipboardInfo.data[v29++];
            v30[clipboardInfo.len] = v28;
            v28 = v26[v29];
          }
          while ( v28 );
          v5 = white;
          v27 = percentc;
        }
        clipboardInfo.len = v27;
        clipboardInfo.data[v27] = 0;
      }
    }
    v31 = (soundSystem->ListSoundSummary(soundSystem) >> 20) - 32;
    v32 = (double)v31 * 0.125;
    percentd = v32;
    if ( v32 > 0.0 )
    {
      if ( percentd > 1.0 )
        percentd = 1.0;
      idStr::snPrintf(msg, 64, "%d megs", v31);
      v57 = percentd;
      result.roll = 1.0;
      color.z = 1.0;
      result.pitch = 0.0;
      result.yaw = 0.0;
      color.x = 0.0;
      color.y = 0.0;
      v33 = this->__vftable;
      color.w = percentd;
      v33->SetColor(this, &color);
      (*((void (__thiscall **)(idRenderSystemLocal *, int, int, int, int, _DWORD, _DWORD, int, int, const idMaterial *))&this->SetColor4
       + 1))(
        this,
        1141145600,
        1128792064,
        1120403456,
        1109393408,
        0,
        0,
        1065353216,
        1065353216,
        v5);
      this->DrawSmallStringExt(this, 532, 204, "Sounds", &colorWhite, 1, v4);
      this->DrawSmallStringExt(this, 532, 220, msg, &colorWhite, 1, v4);
      v34 = va("Sound Memory Over: %d megs\r\n", v31);
      v35 = v34;
      if ( v34 )
      {
        v36 = strlen(v34) + clipboardInfo.len;
        percente = v36;
        if ( v36 + 1 > clipboardInfo.alloced )
        {
          idStr::ReAllocate(&clipboardInfo, v36 + 1, 1);
          v36 = percente;
        }
        v37 = *v35;
        v38 = 0;
        if ( *v35 )
        {
          do
          {
            v39 = &clipboardInfo.data[v38++];
            v39[clipboardInfo.len] = v37;
            v37 = v35[v38];
          }
          while ( v37 );
          v5 = white;
          v36 = percente;
        }
        clipboardInfo.len = v36;
        clipboardInfo.data[v36] = 0;
      }
    }
    if ( game )
    {
      v40 = (const idMaterial *)(game->DebugGetStatInt(game, "ai_thinkCount") - 5);
      white = v40;
      v41 = (double)(int)v40 * 0.2;
      percentf = v41;
      if ( v41 > 0.0 )
      {
        if ( percentf > 1.0 )
          percentf = 1.0;
        idStr::snPrintf(msg, 64, "%d active", v40);
        v57 = percentf;
        result.roll = 1.0;
        color.z = 1.0;
        result.pitch = 0.0;
        result.yaw = 1.0;
        color.x = 0.0;
        color.y = 1.0;
        v42 = this->__vftable;
        color.w = percentf;
        v42->SetColor(this, &color);
        (*((void (__thiscall **)(idRenderSystemLocal *, int, int, int, int, _DWORD, _DWORD, int, int, const idMaterial *))&this->SetColor4
         + 1))(
          this,
          1141145600,
          1132068864,
          1120403456,
          1109393408,
          0,
          0,
          1065353216,
          1065353216,
          v5);
        this->DrawSmallStringExt(this, 532, 254, "AI", &colorWhite, 1, v4);
        this->DrawSmallStringExt(this, 532, 270, msg, &colorWhite, 1, v4);
        v43 = va("Active AI Over: %d creatures\r\n", v40);
        v44 = v43;
        if ( v43 )
        {
          v45 = strlen(v43) + clipboardInfo.len;
          if ( v45 + 1 > clipboardInfo.alloced )
            idStr::ReAllocate(&clipboardInfo, v45 + 1, 1);
          v46 = *v44;
          for ( i = 0; v46; v46 = v44[i] )
          {
            v48 = &clipboardInfo.data[i++];
            v48[clipboardInfo.len] = v46;
          }
          clipboardInfo.len = v45;
          clipboardInfo.data[v45] = 0;
        }
      }
    }
    if ( com_Limits.internalVar->integerValue == 2 )
    {
      Sys_SetClipboardData(clipboardInfo.data);
      com_Limits.internalVar->InternalSetInteger(com_Limits.internalVar, 1);
    }
    this->guiModel = saveGui;
    v64 = -1;
    idStr::FreeData(&clipboardInfo);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::EndFrame(int *,int *,int *,int *)
void __thiscall idRenderSystemLocal::EndFrame(
        idRenderSystemLocal *this,
        int *frontEndMsec,
        int *backEndMsec,
        int *numVerts,
        int *numIndexes)
{
  const idMaterial *v6; // eax
  double vidHeight; // st7
  const idMaterial *v8; // edi
  double v9; // st7
  float v10; // ebx
  emptyCommand_t *v11; // eax
  float x; // [esp+8h] [ebp-3Ch]
  float y; // [esp+Ch] [ebp-38h]
  float heightSize; // [esp+3Ch] [ebp-8h]
  float heightSizea; // [esp+3Ch] [ebp-8h]
  float widthSize; // [esp+40h] [ebp-4h]

  if ( glConfig.isInitialized )
  {
    idRenderSystemLocal::DrawLimits(this, this->guiOverlayModel);
    idGuiModel::EmitFullScreen(this->guiOverlayModel);
    idGuiModel::Clear(this->guiOverlayModel);
    if ( r_showSafeArea.internalVar->integerValue )
    {
      v6 = declManager->FindMaterial(declManager, "_white", 1);
      vidHeight = (double)glConfig.vidHeight;
      v8 = v6;
      if ( r_aspectRatio.internalVar->integerValue )
      {
        heightSize = vidHeight * 0.050000001 * 480.0 / (double)glConfig.vidHeight;
        v9 = (double)glConfig.vidWidth * 0.050000001;
      }
      else
      {
        heightSize = vidHeight * 0.075000003 * 480.0 / (double)glConfig.vidHeight;
        v9 = (double)glConfig.vidWidth * 0.075000003;
      }
      widthSize = v9 * 640.0 / (double)glConfig.vidWidth;
      idGuiModel::SetColor(this->guiModel, 1.0, 0.75, 0.0, 0.75);
      v10 = heightSize;
      idGuiModel::DrawStretchPic(this->guiModel, 0.0, 0.0, 640.0, heightSize, 0.0, 0.0, 1.0, 1.0, v8);
      y = 480.0 - heightSize;
      idGuiModel::DrawStretchPic(this->guiModel, 0.0, y, 640.0, heightSize, 0.0, 0.0, 1.0, 1.0, v8);
      heightSizea = 480.0 - (heightSize + heightSize);
      idGuiModel::DrawStretchPic(this->guiModel, 0.0, v10, widthSize, heightSizea, 0.0, 0.0, 1.0, 1.0, v8);
      x = 640.0 - widthSize;
      idGuiModel::DrawStretchPic(this->guiModel, x, v10, widthSize, heightSizea, 0.0, 0.0, 1.0, 1.0, v8);
    }
    idGuiModel::EmitFullScreen(this->guiModel);
    idGuiModel::Clear(this->guiModel);
    if ( frontEndMsec )
      *frontEndMsec = this->pc.frontEndMsec;
    if ( backEndMsec )
      *backEndMsec = backEnd.pc.msec;
    if ( numVerts )
      *numVerts = backEnd.pc.c_drawVertexes;
    if ( numIndexes )
      *numIndexes = backEnd.pc.c_drawIndexes;
    R_PerformanceCounters();
    R_CheckCvars();
    if ( com_developer.internalVar->integerValue )
      GL_CheckErrors();
    R_SubmitDeferredCommands();
    v11 = (emptyCommand_t *)R_FrameAlloc(8);
    v11->next = 0;
    frameData[tr.smpFrame]->cmdTail->next = &v11->commandId;
    frameData[tr.smpFrame]->cmdTail = v11;
    v11->commandId = RC_SWAP_BUFFERS;
    R_IssueRenderCommands();
    renderSystem->ToggleSmpFrame(renderSystem);
    idVertexCache::EndFrame(&vertexCache);
    if ( session->writeDemo )
    {
      session->writeDemo->WriteChar(session->writeDemo, 1);
      session->writeDemo->WriteChar(session->writeDemo, 17);
      if ( r_showDemo.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_END_FRAME\n\n");
    }
  }
}

// FUNC: public: virtual class idRenderWorld * __thiscall idRenderSystemLocal::AllocRenderWorld(void)
idRenderWorldLocal *__thiscall idRenderSystemLocal::AllocRenderWorld(idRenderSystemLocal *this)
{
  idRenderWorldLocal *v2; // eax
  idRenderWorldLocal *v3; // eax
  int granularity; // eax
  bool v5; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v9; // ecx
  idRenderWorldLocal **list; // edi
  int j; // eax
  idRenderWorldLocal *result; // eax
  idRenderWorldLocal *v13; // [esp+Ch] [ebp-10h]

  v2 = (idRenderWorldLocal *)Memory::Allocate(0x180u);
  if ( v2 )
  {
    idRenderWorldLocal::idRenderWorldLocal(v2);
    v13 = v3;
  }
  else
  {
    v13 = 0;
  }
  if ( !this->worlds.list )
  {
    granularity = this->worlds.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->worlds.size )
      {
        v5 = granularity < this->worlds.num;
        this->worlds.size = granularity;
        if ( v5 )
          this->worlds.num = granularity;
        this->worlds.list = (idRenderWorldLocal **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->worlds.num; ++i )
          this->worlds.list[i] = *(idRenderWorldLocal **)(4 * i);
      }
    }
    else
    {
      this->worlds.list = 0;
      this->worlds.num = 0;
      this->worlds.size = 0;
    }
  }
  num = this->worlds.num;
  size = this->worlds.size;
  if ( num == size )
  {
    if ( !this->worlds.granularity )
      this->worlds.granularity = 16;
    v9 = size + this->worlds.granularity - (size + this->worlds.granularity) % this->worlds.granularity;
    if ( v9 > 0 )
    {
      if ( v9 != this->worlds.size )
      {
        list = this->worlds.list;
        this->worlds.size = v9;
        if ( v9 < num )
          this->worlds.num = v9;
        this->worlds.list = (idRenderWorldLocal **)Memory::Allocate(4 * v9);
        for ( j = 0; j < this->worlds.num; ++j )
          this->worlds.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->worlds.list )
        Memory::Free(this->worlds.list);
      this->worlds.list = 0;
      this->worlds.num = 0;
      this->worlds.size = 0;
    }
  }
  result = v13;
  this->worlds.list[this->worlds.num++] = v13;
  return result;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::FreeRenderWorld(class idRenderWorld *)
void __thiscall idRenderSystemLocal::FreeRenderWorld(idRenderSystemLocal *this, idRenderWorldLocal *rw)
{
  int num; // edi
  int v3; // edx
  idRenderWorldLocal **list; // esi
  idRenderWorldLocal **v5; // esi
  idRenderWorldLocal *v6; // edi
  idRenderWorldLocal **v7; // esi

  if ( this->primaryWorld == rw )
    this->primaryWorld = 0;
  num = this->worlds.num;
  v3 = 0;
  if ( num > 0 )
  {
    list = this->worlds.list;
    while ( *list != rw )
    {
      ++v3;
      ++list;
      if ( v3 >= this->worlds.num )
        goto LABEL_12;
    }
    if ( v3 >= 0 && v3 < num )
    {
      for ( this->worlds.num = num - 1; v3 < this->worlds.num; *v7 = v6 )
      {
        v5 = this->worlds.list;
        v6 = v5[v3 + 1];
        v7 = &v5[v3++];
      }
    }
  }
LABEL_12:
  if ( rw )
    ((void (__thiscall *)(idRenderWorldLocal *, int))rw->~idRenderWorldLocal)(rw, 1);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::TrackTextureUsage(enum idRenderSystem::TextureTrackCommand,int,char const *)
void __thiscall idRenderSystemLocal::TrackTextureUsage(
        idRenderSystemLocal *this,
        idFile *command,
        int frametime,
        char *name)
{
  const char *v4; // ecx
  idImageManager_vtbl *v5; // edx
  int v6; // edi
  int v7; // esi
  idImage *v8; // eax
  unsigned int v9; // edi
  int v10; // ebx
  int v11; // esi
  idImage *v12; // eax
  const char *v13; // esi
  unsigned int v14; // eax
  int v15; // edi
  int v16; // eax
  char *data; // edx
  const char *v18; // ecx
  char v19; // al
  int v20; // esi
  int v21; // eax
  char v22; // cl
  char *v23; // edx
  int v24; // esi
  int i; // eax
  char v26; // cl
  char *v27; // edx
  idFile *v28; // edi
  const char *v29; // eax
  int j; // ebx
  idImage *v31; // esi
  char *v32; // ecx
  char *v33; // edx
  char v34; // al
  cubeFiles_t cubeFiles; // eax
  bool v36; // zf
  const char *v37; // eax
  const char *v38; // edx
  unsigned int v39; // eax
  char *v40; // edi
  unsigned int v42; // eax
  int v43; // eax
  const char *v44; // eax
  const char *v45; // eax
  int v46; // eax
  void *v47; // esp
  unsigned int v48; // ebx
  int v49; // esi
  int v50; // ecx
  const char *v51; // eax
  int v52; // ecx
  _DWORD v53[3]; // [esp+0h] [ebp-640h] BYREF
  char dest2[512]; // [esp+Ch] [ebp-634h] BYREF
  char dest1[512]; // [esp+20Ch] [ebp-434h] BYREF
  char imagename[512]; // [esp+40Ch] [ebp-234h] BYREF
  unsigned int k; // [esp+60Ch] [ebp-34h]
  idStr logname; // [esp+610h] [ebp-30h] BYREF
  unsigned int offset; // [esp+630h] [ebp-10h]
  int v60; // [esp+63Ch] [ebp-4h]
  idFile *log; // [esp+648h] [ebp+8h]
  idFile *loga; // [esp+648h] [ebp+8h]
  char shift; // [esp+650h] [ebp+10h]
  signed int shifta; // [esp+650h] [ebp+10h]

  if ( (_S6_7 & 1) == 0 )
  {
    _S6_7 |= 1u;
    trackName.len = 0;
    trackName.alloced = 20;
    trackName.data = trackName.baseBuffer;
    trackName.baseBuffer[0] = 0;
    atexit(_E7_22);
  }
  if ( command )
  {
    if ( command == (idFile *)1 )
    {
      if ( buffer && frametime >= lastframe + 1 && samples < maxSamples )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "Update @ %d\n",
          frametime);
        shift = samples & 0x1F;
        v9 = samples >> 5;
        v10 = globalImages->GetNumImages(globalImages);
        v11 = 0;
        for ( log = (idFile *)v10; v11 < v10; ++v11 )
        {
          v12 = globalImages->GetImageByIndex(globalImages, v11);
          if ( v12->bindCount > 0 )
          {
            *((_DWORD *)buffer + v9 + v11 * blockDwords) |= 1 << shift;
            v10 = (int)log;
            v12->bindCount = 0;
          }
        }
        ++samples;
        lastframe = frametime;
      }
    }
    else if ( command == (idFile *)2 && buffer )
    {
      v13 = fileSystem->GetAssetLogName(fileSystem);
      logname.len = 0;
      logname.alloced = 20;
      logname.data = logname.baseBuffer;
      logname.baseBuffer[0] = 0;
      if ( v13 )
      {
        v14 = (unsigned int)&v13[strlen(v13) + 1];
        v15 = v14 - (_DWORD)(v13 + 1);
        v16 = v14 - (_DWORD)v13;
        if ( v16 > 20 )
          idStr::ReAllocate(&logname, v16, 1);
        data = logname.data;
        v18 = v13;
        do
        {
          v19 = *v18;
          *data++ = *v18++;
        }
        while ( v19 );
        logname.len = v15;
      }
      v60 = 0;
      idStr::StripFileExtension(&logname);
      v20 = logname.len + 1;
      if ( logname.len + 2 > logname.alloced )
        idStr::ReAllocate(&logname, logname.len + 2, 1);
      v21 = 0;
      v22 = 95;
      do
      {
        v23 = &logname.data[v21++];
        v23[logname.len] = v22;
        v22 = asc_1029F57C[v21];
      }
      while ( v22 );
      logname.len = v20;
      logname.data[v20] = 0;
      v24 = trackName.len + logname.len;
      if ( trackName.len + logname.len + 1 > logname.alloced )
        idStr::ReAllocate(&logname, trackName.len + logname.len + 1, 1);
      for ( i = 0; i < trackName.len; v27[logname.len] = v26 )
      {
        v26 = trackName.data[i];
        v27 = &logname.data[i++];
      }
      logname.len = v24;
      logname.data[v24] = 0;
      idStr::SetFileExtension(&logname, "cinlog");
      v28 = fileSystem->OpenFileWrite(fileSystem, logname.data, "fs_savepath", 0);
      loga = v28;
      if ( v28 )
      {
        shifta = globalImages->GetNumImages(globalImages);
        v29 = va("%d\n", shifta);
        v28->Write(v28, v29, strlen(v29));
        for ( j = 0; j < shifta; ++j )
        {
          v31 = globalImages->GetImageByIndex(globalImages, j);
          v32 = v31->imgName.data;
          offset = (unsigned int)v31;
          v33 = imagename;
          do
          {
            v34 = *v32;
            *v33++ = *v32++;
          }
          while ( v34 );
          cubeFiles = v31->cubeFiles;
          if ( cubeFiles )
          {
            v36 = cubeFiles == CF_NATIVE;
            v37 = "_px";
            if ( !v36 )
              v37 = "_forward";
            v38 = v37;
            v39 = strlen(v37) + 1;
            v40 = &dest1[511];
            while ( *++v40 )
              ;
            qmemcpy(v40, v38, v39);
            v28 = loga;
            v31 = (idImage *)offset;
          }
          idImage::ImageProgramStringToCompressedFileName(v31, imagename, dest1);
          v42 = idImage::ImageNameCRC32(imagename);
          idImage::ImageNamePlusCRC32(dest1, v42, dest2);
          v43 = idImage::StorageSize(v31);
          v44 = va("%04d %d %s\n", j, v43, dest2);
          v28->Write(v28, v44, strlen(v44));
        }
        v45 = va("%d\n", frametime);
        loga->Write(loga, v45, strlen(v45));
        v46 = 4 * shifta + 3;
        LOBYTE(v46) = v46 & 0xFC;
        v47 = alloca(v46);
        memset(v53, 0, 4 * ((unsigned int)(4 * shifta) >> 2));
        v48 = 0;
        if ( samples != -1 )
        {
          do
          {
            offset = v48 >> 5;
            v49 = 0;
            for ( k = v48 & 0x1F; v49 < shifta; ++v49 )
            {
              if ( !globalImages->GetImageByIndex(globalImages, v49)->generatorFunction )
              {
                if ( ((1 << k) & *((_DWORD *)buffer + offset + v49 * blockDwords)) != 0 )
                {
                  ++v53[v49];
                }
                else
                {
                  v50 = v53[v49];
                  if ( v50 )
                  {
                    v51 = va("%08d %08d %d\n", v48 - v50, v50, v49);
                    loga->Write(loga, v51, strlen(v51));
                  }
                  v53[v49] = 0;
                }
              }
            }
            ++v48;
          }
          while ( v48 < samples + 1 );
        }
        loga->Flush(loga);
        fileSystem->CloseFile(fileSystem, loga);
        Mem_Free(buffer);
        v52 = *(_DWORD *)common.type;
        buffer = 0;
        maxSamples = 0;
        samples = 0;
        blockDwords = 0;
        (*(void (**)(netadrtype_t, const char *, ...))(v52 + 124))(
          common.type,
          "Stopped texture tracking: %s\n",
          trackName.data);
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
          common.type,
          "Couldn't write %s.",
          logname.data);
      }
      v60 = -1;
      idStr::FreeData(&logname);
    }
  }
  else if ( !buffer && r_trackTextureUsage.internalVar->integerValue )
  {
    v4 = name;
    if ( !name )
      v4 = "unknown";
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Starting texture tracking: %s\n",
      v4);
    v5 = globalImages->__vftable;
    blockDwords = (unsigned int)(240 * frametime) >> 5;
    maxSamples = 32 * blockDwords - 1;
    samples = 0;
    v6 = v5->GetNumImages(globalImages);
    v7 = 0;
    buffer = Mem_ClearedAlloc(4 * v6 * blockDwords, 0x10u);
    for ( lastframe = -1; v7 < v6; v8->bindCount = 0 )
      v8 = globalImages->GetImageByIndex(globalImages, v7++);
    if ( name )
      idStr::operator=(&trackName, name);
    else
      idStr::operator=(&trackName, "unknown");
  }
}
