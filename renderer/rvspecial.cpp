
// FUNC: public: bool __thiscall rvBlurTexture::CreateBuffer(char const *,class idPBufferImage * &)
char __thiscall rvBlurTexture::CreateBuffer(rvBlurTexture *this, const char *Name, idPBufferImage **Image)
{
  idPBufferImage *v3; // eax

  v3 = globalImages->AllocPBufferImage(globalImages, Name);
  *Image = v3;
  v3->useCount = 1;
  (*Image)->type = TT_2D;
  (*Image)->uploadWidth = 256;
  (*Image)->uploadHeight = 256;
  rvTexRenderTarget::Init(
    (*Image)->mRenderTarget,
    (*Image)->uploadWidth,
    (*Image)->uploadHeight,
    32,
    8,
    8,
    8,
    8,
    24,
    0,
    9);
  rvTexRenderTarget::DefaultD3GL((*Image)->mRenderTarget);
  return 1;
}

// FUNC: public: bool __thiscall rvAL::CreateBuffer(char const *,class idPBufferImage * &)
char __thiscall rvAL::CreateBuffer(rvAL *this, const char *Name, idPBufferImage **Image)
{
  idPBufferImage *v3; // eax

  v3 = globalImages->AllocPBufferImage(globalImages, Name);
  *Image = v3;
  v3->useCount = 1;
  (*Image)->type = TT_2D;
  (*Image)->uploadWidth = 512;
  (*Image)->uploadHeight = 512;
  rvTexRenderTarget::Init(
    (*Image)->mRenderTarget,
    (*Image)->uploadWidth,
    (*Image)->uploadHeight,
    32,
    8,
    8,
    8,
    8,
    24,
    0,
    9);
  rvTexRenderTarget::DefaultD3GL((*Image)->mRenderTarget);
  return 1;
}

// FUNC: void __cdecl RB_RestoreDrawingView(void)
void __cdecl RB_RestoreDrawingView()
{
  qglMatrixMode(0x1701u);
  qglLoadMatrixf(backEnd.viewDef->projectionMatrix);
  qglMatrixMode(0x1700u);
  qglLoadIdentity();
  backEnd.currentSpace = 0;
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
    qglEnable(0xB71u);
    qglEnable(0xB90u);
  }
  else
  {
    qglDisable(0xB71u);
    qglDisable(0xB90u);
  }
  backEnd.glState.faceCulling = -1;
  GL_Cull(0);
}

// FUNC: void __cdecl R_AddSpecialEffects(struct viewDef_s *)
void __cdecl R_AddSpecialEffects(viewDef_s *parms)
{
  emptyCommand_t *CommandBuffer; // eax

  if ( (tr.specialEffectsEnabled & 3) != 0 )
  {
    CommandBuffer = R_GetCommandBuffer(12);
    CommandBuffer->commandId = RC_DRAW_DEPTH_TEXTURE;
    CommandBuffer[1].commandId = (renderCommand_t)parms;
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::SetSpecialEffectParm(enum ESpecialEffectType,int,float)
void __thiscall idRenderSystemLocal::SetSpecialEffectParm(
        idRenderSystemLocal *this,
        ESpecialEffectType Which,
        int Parm,
        float Value)
{
  if ( Which == SPECIAL_EFFECT_BLUR )
  {
    if ( DepthTexture )
      DepthTexture->shaderParms[Parm] = Value;
  }
  else if ( Which == SPECIAL_EFFECT_AL )
  {
    if ( ptr )
      ptr->shaderParms[Parm] = Value;
  }
}

// FUNC: public: __thiscall rvBlurTexture::rvBlurTexture(void)
void __thiscall rvBlurTexture::rvBlurTexture(rvBlurTexture *this)
{
  const idMaterial *v2; // eax

  rvBlurTexture::CreateBuffer(this, "DepthTexture", &this->mDepthImage);
  rvBlurTexture::CreateBuffer(this, "BlurTexture1", this->mBlurImage);
  v2 = declManager->FindMaterial(declManager, "hs/MedLabs", 1);
  this->mDepthMaterial = v2;
  this->regs = (float *)Mem_ClearedAlloc(4 * v2->numRegisters, 0x10u);
  this->shaderParms[0] = 0.69400001;
  this->shaderParms[1] = 0.69400001;
  this->shaderParms[2] = 0.69400001;
  this->shaderParms[3] = 1.0;
  this->shaderParms[4] = 4.0;
  this->shaderParms[5] = 0.31;
  this->shaderParms[6] = 0.5;
  this->shaderParms[7] = 500.0;
}

// FUNC: void __cdecl RB_T_FillDepthTexture(struct drawSurf_s const *)
void __cdecl RB_T_FillDepthTexture(const drawSurf_s *surf)
{
  const idMaterial *material; // ebp
  int numStages; // esi
  const srfTriangles_s *geo; // edi
  int v4; // ecx
  const float *shaderRegisters; // ebx
  shaderStage_t *v6; // edx
  bool v7; // zf
  shaderStage_t *v8; // edx
  idDrawVert *v9; // edi
  materialCoverage_t coverage; // eax
  shaderStage_t *v11; // esi
  dynamicidImage_t dynamic; // eax
  double v13; // st7
  idImage *v14; // eax
  bool didDraw; // [esp+Eh] [ebp-1Eh]
  bool drawSolid; // [esp+Fh] [ebp-1Dh]
  int v17; // [esp+10h] [ebp-1Ch]
  int stage; // [esp+14h] [ebp-18h]
  const srfTriangles_s *tri; // [esp+18h] [ebp-14h]
  float color[4]; // [esp+1Ch] [ebp-10h] BYREF

  material = surf->material;
  numStages = material->numStages;
  geo = surf->geo;
  tri = surf->geo;
  if ( numStages <= 0 && !material->entityGui && !material->gui
    || !geo->numIndexes
    || material->coverage == MC_TRANSLUCENT )
  {
    return;
  }
  if ( !geo->ambientCache )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "RB_T_FillDepthTexture: !tri->ambientCache\n");
    return;
  }
  v4 = 0;
  shaderRegisters = surf->shaderRegisters;
  if ( numStages < 4 )
  {
LABEL_15:
    v7 = v4 == numStages;
    if ( v4 >= numStages )
      goto LABEL_24;
    v8 = &material->stages[v4];
    do
    {
      if ( shaderRegisters[v8->conditionRegister] != 0.0 )
        break;
      ++v4;
      ++v8;
    }
    while ( v4 < numStages );
  }
  else
  {
    v6 = material->stages + 2;
    while ( shaderRegisters[v6[-2].conditionRegister] == 0.0 )
    {
      if ( shaderRegisters[v6[-1].conditionRegister] != 0.0 )
      {
        ++v4;
        break;
      }
      if ( shaderRegisters[v6->conditionRegister] != 0.0 )
      {
        v4 += 2;
        break;
      }
      if ( shaderRegisters[v6[1].conditionRegister] != 0.0 )
      {
        v4 += 3;
        break;
      }
      v4 += 4;
      v6 += 4;
      if ( v4 >= numStages - 3 )
        goto LABEL_15;
    }
  }
  v7 = v4 == numStages;
LABEL_24:
  if ( !v7 )
  {
    GL_PolygonOffset(material, 1);
    if ( LODWORD(material->sort) == -1065353216 )
    {
      GL_State(3);
      color[2] = 1.0 / backEnd.overBright;
      color[1] = color[2];
      color[0] = color[2];
    }
    else
    {
      memset(color, 0, 12);
    }
    color[3] = 1.0;
    v9 = (idDrawVert *)idVertexCache::Position(&vertexCache, geo->ambientCache);
    qglVertexPointer(3, 0x1406u, 64, v9);
    qglTexCoordPointer(2, 0x1406u, 64, &v9->st);
    coverage = material->coverage;
    drawSolid = coverage == MC_OPAQUE;
    if ( coverage == MC_PERFORATED )
    {
      didDraw = 0;
      qglEnable(0xBC0u);
      stage = 0;
      if ( material->numStages > 0 )
      {
        v17 = 0;
        do
        {
          v11 = &material->stages[v17];
          dynamic = v11->texture.dynamic;
          if ( dynamic != DI_REFLECTION_RENDER
            && dynamic != DI_REFRACTION_RENDER
            && v11->hasAlphaTest
            && shaderRegisters[v11->conditionRegister] != 0.0 )
          {
            v13 = shaderRegisters[v11->color.registers[3]];
            didDraw = 1;
            color[3] = shaderRegisters[v11->color.registers[3]];
            if ( v13 > 0.0 )
            {
              qglColor4fv(color);
              qglAlphaFunc(v11->alphaTestMode, shaderRegisters[v11->alphaTestRegister]);
              v11->texture.image->Bind(v11->texture.image);
              RB_PrepareStageTexturing(v11, surf, v9, 1);
              RB_DrawElementsWithCounters(tri);
              RB_FinishStageTexturing(v11, surf, v9);
            }
          }
          ++v17;
          ++stage;
        }
        while ( stage < material->numStages );
      }
      qglDisable(0xBC0u);
      if ( !didDraw )
        goto LABEL_40;
    }
    if ( drawSolid )
    {
LABEL_40:
      qglColor4fv(color);
      v14 = globalImages->GetWhiteImage(globalImages);
      v14->Bind(v14);
      RB_DrawElementsWithCounters(tri);
    }
    GL_PolygonOffset(material, 0);
    if ( LODWORD(material->sort) == -1065353216 )
      GL_State(0);
  }
}

// FUNC: public: void __thiscall rvBlurTexture::Render(struct drawSurfsCommand_t const *)
void __thiscall rvBlurTexture::Render(rvBlurTexture *this, const drawSurfsCommand_t *DrawSurfs)
{
  idImage *v3; // eax
  idImage *v4; // eax
  shaderStage_t *stages; // ebp
  int v6; // edi
  glstate_t *p_glState; // esi
  idImageManager *v8; // ecx
  int v9; // eax
  idVec3 randomizer; // [esp+1Ch] [ebp-Ch] BYREF

  backEnd.currentRenderNeeded = 1;
  rvTexRenderTarget::BeginRender(this->mDepthImage->mRenderTarget, 0);
  qglClearColor(0.0, 0.0, 0.0, 1.0);
  qglClearDepth(1.0);
  qglDepthRange(0.0, 1.0);
  qglClear(0x4100u);
  backEnd.viewDef = DrawSurfs->viewDef;
  RB_BeginDrawingView();
  qglViewport(0, 0, this->mDepthImage->uploadWidth, this->mDepthImage->uploadHeight);
  qglDisable(0xBE2u);
  qglColor4f(1.0, 1.0, 1.0, 1.0);
  GL_SelectTexture(1);
  GL_SelectTexture(0);
  v3 = globalImages->GetDefaultImage(globalImages);
  v3->Bind(v3);
  v4 = globalImages->GetWhiteImage(globalImages);
  v4->Bind(v4);
  GL_SelectTexture(0);
  qglEnableClientState(0x8078u);
  qglEnableClientState(0x8074u);
  qglDepthFunc(0x203u);
  qglDisable(0xB90u);
  qglStencilFunc(0x207u, 1, 0xFFu);
  idMaterial::EvaluateRegisters(
    (idMaterial *)this->mDepthMaterial,
    this->regs,
    this->shaderParms,
    DrawSurfs->viewDef,
    0,
    &randomizer);
  stages = this->mDepthMaterial->stages;
  stages->newShaderStage->Bind(stages->newShaderStage, this->regs, 0);
  RB_RenderDrawSurfListWithFunction(
    DrawSurfs->viewDef->drawSurfs,
    DrawSurfs->viewDef->numDrawSurfs,
    RB_T_FillDepthTexture);
  stages->newShaderStage->UnBind(stages->newShaderStage);
  rvTexRenderTarget::EndRender(this->mDepthImage->mRenderTarget, 1);
  backEnd.glState.forceGlState = 1;
  GL_SelectTexture(1);
  GL_SelectTexture(0);
  v6 = 0;
  p_glState = &backEnd.glState;
  do
  {
    GL_SelectTexture(v6);
    qglDisable(0x8513u);
    qglDisable(0x806Fu);
    qglDisable(0xDE1u);
    v8 = globalImages;
    p_glState->tmu[0].textureType = TT_DISABLED;
    p_glState->tmu[0].current2DMap = -1;
    p_glState->tmu[0].current3DMap = -1;
    p_glState->tmu[0].currentCubeMap = -1;
    v9 = (int)v8->GetWhiteImage(v8);
    (*(void (__thiscall **)(int))(*(_DWORD *)v9 + 4))(v9);
    p_glState = (glstate_t *)((char *)p_glState + 20);
    ++v6;
  }
  while ( (int)p_glState < (int)&backEnd.glState.currenttmu );
}

// FUNC: public: void __thiscall rvBlurTexture::Display(struct viewEntity_s const *,bool)
void __thiscall rvBlurTexture::Display(rvBlurTexture *this, const viewEntity_s *viewEnts, bool prePass)
{
  idImage *v4; // eax
  idImage *v5; // eax
  shaderStage_t *stages; // edi
  shaderStage_t *v7; // edi

  if ( prePass && !viewEnts )
  {
    rvTexRenderTarget::BeginRender(this->mBlurImage[0]->mRenderTarget, 0);
    RB_SetGL2D();
    qglViewport(0, 0, this->mBlurImage[0]->uploadWidth, this->mBlurImage[0]->uploadHeight);
    qglColor4f(1.0, 1.0, 1.0, 1.0);
    qglClearColor(0.0, 0.0, 0.0, 1.0);
    qglClearDepth(1.0);
    qglDepthRange(0.0, 1.0);
    qglClear(0x4100u);
    qglDisable(0xBE2u);
    qglColor4f(1.0, 1.0, 1.0, 1.0);
    GL_SelectTexture(1);
    GL_SelectTexture(0);
    v4 = globalImages->GetDefaultImage(globalImages);
    v4->Bind(v4);
    v5 = globalImages->GetWhiteImage(globalImages);
    v5->Bind(v5);
    stages = this->mDepthMaterial->stages;
    stages[1].newShaderStage->Bind(stages[1].newShaderStage, this->regs, 0);
    qglBegin(7u);
    qglTexCoord2f(0.0, 1.0);
    qglVertex2f(0.0, 0.0);
    qglTexCoord2f(1.0, 1.0);
    qglVertex2f(640.0, 0.0);
    qglTexCoord2f(1.0, 0.0);
    qglVertex2f(640.0, 480.0);
    qglTexCoord2f(0.0, 0.0);
    qglVertex2f(0.0, 480.0);
    qglEnd();
    stages[1].newShaderStage->UnBind(stages[1].newShaderStage);
    rvTexRenderTarget::EndRender(this->mBlurImage[0]->mRenderTarget, 1);
    RB_SetGL2D();
    qglBlendFunc(1u, 0);
    qglColor4f(1.0, 1.0, 1.0, 1.0);
    v7 = this->mDepthMaterial->stages;
    v7[2].newShaderStage->Bind(v7[2].newShaderStage, this->regs, 0);
    qglEnable(0xBE2u);
    qglBlendFunc(0x302u, 0x303u);
    qglColor4f(1.0, 1.0, 1.0, 1.0);
    qglBegin(7u);
    qglTexCoord2f(0.0, 1.0);
    qglVertex2f(0.0, 0.0);
    qglTexCoord2f(1.0, 1.0);
    qglVertex2f(640.0, 0.0);
    qglTexCoord2f(1.0, 0.0);
    qglVertex2f(640.0, 480.0);
    qglTexCoord2f(0.0, 0.0);
    qglVertex2f(0.0, 480.0);
    qglEnd();
    v7[2].newShaderStage->UnBind(v7[2].newShaderStage);
    backEnd.glState.forceGlState = 1;
  }
}

// FUNC: public: __thiscall rvAL::rvAL(void)
void __thiscall rvAL::rvAL(rvAL *this)
{
  const idMaterial *v2; // eax
  int v3; // ebx
  idRenderWorldLocal *primaryWorld; // eax
  idRenderLightLocal *v5; // edi
  idVec3 *v6; // eax
  idVec3 *v7; // ecx
  long double v8; // st4
  long double v9; // st7

  rvAL::CreateBuffer(this, "DepthTexture", &this->mDepthImage);
  rvAL::CreateBuffer(this, "BlurTexture1", this->mBlurImage);
  v2 = declManager->FindMaterial(declManager, "hs/ALSetup", 1);
  this->mDepthMaterial = v2;
  ALMaterial = v2;
  v3 = 0;
  this->regs = (float *)Mem_ClearedAlloc(4 * v2->numRegisters, 0x10u);
  this->offset = 0.0;
  this->count = 0;
  primaryWorld = tr.primaryWorld;
  do
  {
    if ( v3 >= primaryWorld->lightDefs.num )
      break;
    v5 = primaryWorld->lightDefs.list[v3];
    if ( v5 )
    {
      v6 = &this->lOrigin[this->count];
      v6->x = v5->globalLightOrigin.x;
      v6->y = v5->globalLightOrigin.y;
      v6->z = v5->globalLightOrigin.z;
      this->lColor[this->count].x = rvRandom::flrand(0.0, 1.0);
      this->lColor[this->count].y = rvRandom::flrand(0.0, 1.0);
      this->lColor[this->count].z = rvRandom::flrand(0.0, 1.0);
      this->lColor[this->count].x = v5->parms.shaderParms[0];
      this->lColor[this->count].y = v5->parms.shaderParms[1];
      this->lColor[this->count].z = v5->parms.shaderParms[2];
      v7 = &this->lColor[this->count];
      v8 = v7->x * v7->x + v7->y * v7->y + v7->z * v7->z;
      if ( v8 != 0.0 )
      {
        v9 = 1.0 / sqrt(v8);
        v7->x = v9 * v7->x;
        v7->y = v9 * v7->y;
        v7->z = v9 * v7->z;
      }
      this->lSize[this->count++] = 300.0;
      primaryWorld = tr.primaryWorld;
    }
    ++v3;
  }
  while ( this->count < 100 );
}

// FUNC: void __cdecl RB_T_FillDepthTextureAL(struct drawSurf_s const *)
void __cdecl RB_T_FillDepthTextureAL(const drawSurf_s *surf)
{
  const idMaterial *material; // ebp
  int numStages; // esi
  const srfTriangles_s *geo; // edi
  int v4; // ecx
  const float *shaderRegisters; // ebx
  shaderStage_t *v6; // edx
  bool v7; // zf
  shaderStage_t *v8; // edx
  idDrawVert *v9; // edi
  materialCoverage_t coverage; // eax
  shaderStage_t *v11; // esi
  dynamicidImage_t dynamic; // eax
  double v13; // st7
  int v14; // edx
  int v15; // eax
  shaderStage_t *stages; // esi
  stageLighting_t *p_lighting; // ecx
  bool didDraw; // [esp+Eh] [ebp-1Eh]
  bool drawSolid; // [esp+Fh] [ebp-1Dh]
  int v20; // [esp+10h] [ebp-1Ch]
  int stage; // [esp+14h] [ebp-18h]
  const srfTriangles_s *tri; // [esp+18h] [ebp-14h]
  float color[4]; // [esp+1Ch] [ebp-10h] BYREF

  material = surf->material;
  numStages = material->numStages;
  geo = surf->geo;
  tri = surf->geo;
  if ( numStages <= 0 && !material->entityGui && !material->gui
    || !geo->numIndexes
    || material->coverage == MC_TRANSLUCENT )
  {
    return;
  }
  if ( !geo->ambientCache )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "RB_T_FillDepthTexture: !tri->ambientCache\n");
    return;
  }
  v4 = 0;
  shaderRegisters = surf->shaderRegisters;
  if ( numStages < 4 )
  {
LABEL_15:
    v7 = v4 == numStages;
    if ( v4 >= numStages )
      goto LABEL_24;
    v8 = &material->stages[v4];
    do
    {
      if ( shaderRegisters[v8->conditionRegister] != 0.0 )
        break;
      ++v4;
      ++v8;
    }
    while ( v4 < numStages );
  }
  else
  {
    v6 = material->stages + 2;
    while ( shaderRegisters[v6[-2].conditionRegister] == 0.0 )
    {
      if ( shaderRegisters[v6[-1].conditionRegister] != 0.0 )
      {
        ++v4;
        break;
      }
      if ( shaderRegisters[v6->conditionRegister] != 0.0 )
      {
        v4 += 2;
        break;
      }
      if ( shaderRegisters[v6[1].conditionRegister] != 0.0 )
      {
        v4 += 3;
        break;
      }
      v4 += 4;
      v6 += 4;
      if ( v4 >= numStages - 3 )
        goto LABEL_15;
    }
  }
  v7 = v4 == numStages;
LABEL_24:
  if ( !v7 )
  {
    GL_PolygonOffset(material, 1);
    if ( LODWORD(material->sort) == -1065353216 )
    {
      GL_State(3);
      color[2] = 1.0 / backEnd.overBright;
      color[1] = color[2];
      color[0] = color[2];
    }
    else
    {
      memset(color, 0, 12);
    }
    color[3] = 1.0;
    v9 = (idDrawVert *)idVertexCache::Position(&vertexCache, geo->ambientCache);
    qglVertexPointer(3, 0x1406u, 64, v9);
    qglTexCoordPointer(2, 0x1406u, 64, &v9->st);
    coverage = material->coverage;
    drawSolid = coverage == MC_OPAQUE;
    if ( coverage == MC_PERFORATED )
    {
      didDraw = 0;
      qglEnable(0xBC0u);
      stage = 0;
      if ( material->numStages > 0 )
      {
        v20 = 0;
        do
        {
          v11 = &material->stages[v20];
          dynamic = v11->texture.dynamic;
          if ( dynamic != DI_REFLECTION_RENDER
            && dynamic != DI_REFRACTION_RENDER
            && v11->hasAlphaTest
            && shaderRegisters[v11->conditionRegister] != 0.0 )
          {
            v13 = shaderRegisters[v11->color.registers[3]];
            didDraw = 1;
            color[3] = shaderRegisters[v11->color.registers[3]];
            if ( v13 > 0.0 )
            {
              qglColor4fv(color);
              qglAlphaFunc(v11->alphaTestMode, shaderRegisters[v11->alphaTestRegister]);
              v11->texture.image->Bind(v11->texture.image);
              RB_PrepareStageTexturing(v11, surf, v9, 1);
              RB_DrawElementsWithCounters(tri);
              RB_FinishStageTexturing(v11, surf, v9);
            }
          }
          ++v20;
          ++stage;
        }
        while ( stage < material->numStages );
      }
      qglDisable(0xBC0u);
      if ( !didDraw )
        goto LABEL_40;
    }
    if ( drawSolid )
    {
LABEL_40:
      qglColor4fv(color);
      v14 = material->numStages;
      v15 = 0;
      if ( v14 > 0 )
      {
        stages = material->stages;
        p_lighting = &stages->lighting;
        while ( *p_lighting != SL_DIFFUSE )
        {
          ++v15;
          p_lighting += 33;
          if ( v15 >= v14 )
            goto LABEL_46;
        }
        rvNewShaderStage::SetTextureParm(ALMaterial->stages->newShaderStage, "Image", stages[v15].texture.image);
        ALMaterial->stages->newShaderStage->Bind(ALMaterial->stages->newShaderStage, ptr->regs, 0);
      }
LABEL_46:
      RB_DrawElementsWithCounters(tri);
    }
    GL_PolygonOffset(material, 0);
    if ( LODWORD(material->sort) == -1065353216 )
      GL_State(0);
  }
}

// FUNC: public: void __thiscall rvAL::Render(struct drawSurfsCommand_t const *)
void __thiscall rvAL::Render(rvAL *this, const drawSurfsCommand_t *DrawSurfs)
{
  idImage *v3; // eax
  idImage *v4; // eax
  shaderStage_t *stages; // esi
  int v6; // edi
  glstate_t *p_glState; // esi
  idImageManager *v8; // ecx
  int v9; // eax
  idVec3 randomizer; // [esp+20h] [ebp-Ch] BYREF

  rvTexRenderTarget::BeginRender(this->mDepthImage->mRenderTarget, 0);
  qglClearColor(0.0, 0.0, 0.0, 1.0);
  qglClearDepth(1.0);
  qglDepthRange(0.0, 1.0);
  qglClear(0x4100u);
  backEnd.viewDef = DrawSurfs->viewDef;
  RB_BeginDrawingView();
  qmemcpy(backEnd.projectionMatrix, backEnd.viewDef->projectionMatrix, sizeof(backEnd.projectionMatrix));
  qglViewport(0, 0, this->mDepthImage->uploadWidth, this->mDepthImage->uploadHeight);
  qglDisable(0xBE2u);
  qglColor4f(1.0, 1.0, 1.0, 1.0);
  GL_SelectTexture(1);
  GL_SelectTexture(0);
  v3 = globalImages->GetDefaultImage(globalImages);
  v3->Bind(v3);
  v4 = globalImages->GetWhiteImage(globalImages);
  v4->Bind(v4);
  GL_SelectTexture(0);
  qglEnableClientState(0x8078u);
  qglEnableClientState(0x8074u);
  qglDepthFunc(0x203u);
  qglDisable(0xB90u);
  qglStencilFunc(0x207u, 1, 0xFFu);
  idMaterial::EvaluateRegisters(
    (idMaterial *)this->mDepthMaterial,
    this->regs,
    this->shaderParms,
    DrawSurfs->viewDef,
    0,
    &randomizer);
  stages = this->mDepthMaterial->stages;
  stages->newShaderStage->Bind(stages->newShaderStage, this->regs, 0);
  RB_RenderDrawSurfListWithFunction(
    DrawSurfs->viewDef->drawSurfs,
    DrawSurfs->viewDef->numDrawSurfs,
    RB_T_FillDepthTextureAL);
  stages->newShaderStage->UnBind(stages->newShaderStage);
  rvTexRenderTarget::EndRender(this->mDepthImage->mRenderTarget, 1);
  backEnd.glState.forceGlState = 1;
  GL_SelectTexture(1);
  GL_SelectTexture(0);
  v6 = 0;
  p_glState = &backEnd.glState;
  do
  {
    GL_SelectTexture(v6);
    qglDisable(0x8513u);
    qglDisable(0x806Fu);
    qglDisable(0xDE1u);
    v8 = globalImages;
    p_glState->tmu[0].textureType = TT_DISABLED;
    p_glState->tmu[0].current2DMap = -1;
    p_glState->tmu[0].current3DMap = -1;
    p_glState->tmu[0].currentCubeMap = -1;
    v9 = (int)v8->GetWhiteImage(v8);
    (*(void (__thiscall **)(int))(*(_DWORD *)v9 + 4))(v9);
    p_glState = (glstate_t *)((char *)p_glState + 20);
    ++v6;
  }
  while ( (int)p_glState < (int)&backEnd.glState.currenttmu );
}

// FUNC: void __cdecl RB_SetGL2D2(void)
void __cdecl RB_SetGL2D2()
{
  qglViewport(0, 0, glConfig.vidWidth, glConfig.vidHeight);
  if ( r_useScissor.internalVar->integerValue )
    qglScissor(0, 0, glConfig.vidWidth, glConfig.vidHeight);
  qglMatrixMode(0x1701u);
  qglLoadIdentity();
  qglOrtho(0.0, 640.0, 480.0, 0.0, 0.0, 1.0);
  qglMatrixMode(0x1700u);
  qglLoadIdentity();
  GL_State(65637);
  GL_Cull(2);
  qglDisable(0xB71u);
  qglDisable(0xB90u);
}

// FUNC: void __cdecl R_ShutdownSpecialEffects(void)
void __cdecl R_ShutdownSpecialEffects()
{
  rvBlurTexture *v0; // esi
  rvAL *v1; // esi

  if ( DepthTexture )
  {
    v0 = DepthTexture;
    Mem_Free(DepthTexture->regs);
    Memory::Free(v0);
    DepthTexture = 0;
  }
  if ( ptr )
  {
    v1 = ptr;
    Mem_Free(ptr->regs);
    Memory::Free(v1);
    ptr = 0;
  }
  tr.specialEffectsEnabled = 0;
}

// FUNC: void __cdecl RB_DrawDepthTexture(void const *)
void __cdecl RB_DrawDepthTexture(const drawSurfsCommand_t *data)
{
  backEnd.viewDef = data->viewDef;
  if ( backEnd.viewDef->numDrawSurfs )
  {
    if ( DepthTexture )
      rvBlurTexture::Render(DepthTexture, data);
    if ( ptr )
      rvAL::Render(ptr, data);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::SetSpecialEffect(enum ESpecialEffectType,bool)
void __thiscall idRenderSystemLocal::SetSpecialEffect(
        idRenderSystemLocal *this,
        ESpecialEffectType Which,
        bool Enabled)
{
  rvAL *v3; // eax
  rvAL *v4; // eax
  rvBlurTexture *v5; // eax
  rvBlurTexture *v6; // eax

  if ( Enabled )
  {
    this->specialEffectsEnabled |= Which;
    if ( Which == SPECIAL_EFFECT_BLUR )
    {
      if ( !DepthTexture && glConfig.allowARB2Path )
      {
        v5 = (rvBlurTexture *)Memory::Allocate(0x44u);
        if ( v5 )
        {
          rvBlurTexture::rvBlurTexture(v5);
          DepthTexture = v6;
        }
        else
        {
          DepthTexture = 0;
        }
      }
    }
    else if ( Which == SPECIAL_EFFECT_AL && !ptr && glConfig.allowARB2Path )
    {
      v3 = (rvAL *)Memory::Allocate(0xB50u);
      if ( v3 )
      {
        rvAL::rvAL(v3);
        ptr = v4;
      }
      else
      {
        ptr = 0;
      }
    }
  }
  else
  {
    this->specialEffectsEnabled &= ~Which;
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::ShutdownSpecialEffects(void)
// attributes: thunk
void __thiscall idRenderSystemLocal::ShutdownSpecialEffects(idRenderSystemLocal *this)
{
  R_ShutdownSpecialEffects();
}

// FUNC: public: void __thiscall rvAL::DrawLight(class idVec3 &,float,class idVec3 &)
void __thiscall rvAL::DrawLight(rvAL *this, idVec3 *origin, float size, idVec3 *color)
{
  int v5; // edx
  float *p_b; // ecx
  double v7; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st4
  double v11; // st7
  double v12; // st7
  double v13; // st7
  long double v14; // st7
  unsigned __int8 v16; // c2
  unsigned __int8 v17; // c3
  double d; // st6
  rvNewShaderStage *mainStage; // ecx
  float v20; // esi
  int mLightLocParm; // [esp-18h] [ebp-A0h]
  float *regs; // [esp-14h] [ebp-9Ch]
  float v23; // [esp-Ch] [ebp-94h]
  float y1; // [esp+8h] [ebp-80h]
  float x1; // [esp+Ch] [ebp-7Ch]
  float x2; // [esp+10h] [ebp-78h]
  float y2; // [esp+14h] [ebp-74h]
  float v28; // [esp+18h] [ebp-70h]
  float v29; // [esp+18h] [ebp-70h]
  float v30; // [esp+18h] [ebp-70h]
  float v31; // [esp+18h] [ebp-70h]
  float v32; // [esp+1Ch] [ebp-6Ch]
  float v33; // [esp+1Ch] [ebp-6Ch]
  float v34; // [esp+1Ch] [ebp-6Ch]
  float v35; // [esp+1Ch] [ebp-6Ch]
  float v36; // [esp+1Ch] [ebp-6Ch]
  float v37; // [esp+1Ch] [ebp-6Ch]
  float fd; // [esp+20h] [ebp-68h] BYREF
  float v39; // [esp+24h] [ebp-64h]
  float v40; // [esp+28h] [ebp-60h]
  float v41; // [esp+2Ch] [ebp-5Ch]
  idVec3 temp; // [esp+30h] [ebp-58h] BYREF
  idVec3 ndc; // [esp+3Ch] [ebp-4Ch] BYREF
  idPlane plane; // [esp+48h] [ebp-40h]
  idVec3 points[4]; // [esp+58h] [ebp-30h] BYREF

  v5 = 0;
  p_b = &backEnd.viewDef->frustum[0].b;
  while ( *(p_b - 1) * origin->x + p_b[1] * origin->z + origin->y * *p_b + p_b[2] <= size )
  {
    ++v5;
    p_b += 4;
    if ( v5 >= 5 )
    {
      temp.x = tr.primaryRenderView.viewaxis.mat[1].x * size;
      temp.y = tr.primaryRenderView.viewaxis.mat[1].y * size;
      temp.z = tr.primaryRenderView.viewaxis.mat[1].z * size;
      v7 = tr.primaryRenderView.viewaxis.mat[2].x * size;
      v40 = tr.primaryRenderView.viewaxis.mat[2].y * size;
      v41 = tr.primaryRenderView.viewaxis.mat[2].z * size;
      v8 = temp.x + origin->x;
      ndc.x = v8;
      v9 = temp.y + origin->y;
      ndc.y = v9;
      v10 = temp.z + origin->z;
      v28 = v10;
      ndc.z = v10 + v41;
      points[0].z = ndc.z;
      points[0].x = ndc.x + v7;
      points[0].y = ndc.y + v40;
      ndc.x = origin->x - temp.x;
      ndc.y = origin->y - temp.y;
      v32 = origin->z - temp.z;
      ndc.z = v32 + v41;
      points[1].z = ndc.z;
      points[1].x = ndc.x + v7;
      points[1].y = ndc.y + v40;
      ndc.z = v32 - v41;
      points[2].z = ndc.z;
      points[2].x = ndc.x - v7;
      points[2].y = ndc.y - v40;
      ndc.x = v8;
      ndc.y = v9;
      ndc.z = v28 - v41;
      points[3].z = ndc.z;
      points[3].x = ndc.x - v7;
      points[3].y = ndc.y - v40;
      R_GlobalToNormalizedDeviceCoordinates(
        tr.primaryView->worldSpace.modelViewMatrix,
        tr.primaryView->projectionMatrix,
        points,
        &ndc);
      x1 = (double)(backEnd.viewDef->viewport.x2 - backEnd.viewDef->viewport.x1) * (ndc.x + 1.0) * 0.5;
      y1 = (double)backEnd.viewDef->viewport.y2
         - (double)(backEnd.viewDef->viewport.y2 - backEnd.viewDef->viewport.y1) * (ndc.y + 1.0) * 0.5;
      R_GlobalToNormalizedDeviceCoordinates(
        tr.primaryView->worldSpace.modelViewMatrix,
        tr.primaryView->projectionMatrix,
        &points[2],
        &ndc);
      x2 = (double)(backEnd.viewDef->viewport.x2 - backEnd.viewDef->viewport.x1) * (ndc.x + 1.0) * 0.5;
      y2 = (double)backEnd.viewDef->viewport.y2
         - (double)(backEnd.viewDef->viewport.y2 - backEnd.viewDef->viewport.y1) * (ndc.y + 1.0) * 0.5;
      if ( x1 > (double)x2 )
      {
        v11 = (double)backEnd.viewDef->viewport.x2;
        x1 = v11 - x1;
        x2 = v11 - x2;
      }
      if ( y1 > (double)y2 )
      {
        v12 = (double)backEnd.viewDef->viewport.y2;
        y1 = v12 - y1;
        y2 = v12 - y2;
      }
      R_LocalPointToGlobal(tr.primaryView->worldSpace.modelViewMatrix, origin, &temp);
      v39 = tr.primaryRenderView.viewaxis.mat[2].z * tr.primaryRenderView.viewaxis.mat[1].y
          - tr.primaryRenderView.viewaxis.mat[2].y * tr.primaryRenderView.viewaxis.mat[1].z;
      v40 = tr.primaryRenderView.viewaxis.mat[2].x * tr.primaryRenderView.viewaxis.mat[1].z
          - tr.primaryRenderView.viewaxis.mat[2].z * tr.primaryRenderView.viewaxis.mat[1].x;
      v41 = tr.primaryRenderView.viewaxis.mat[2].y * tr.primaryRenderView.viewaxis.mat[1].x
          - tr.primaryRenderView.viewaxis.mat[2].x * tr.primaryRenderView.viewaxis.mat[1].y;
      plane.c = v41;
      plane.a = v39;
      v13 = v40;
      v33 = v39 * v39 + v41 * v41 + v40 * v40;
      if ( v33 == 0.0 )
      {
        v29 = 0.0;
      }
      else
      {
        v14 = 1.0 / sqrt(v33);
        v30 = v14;
        plane.a = v14 * v39;
        v13 = v40 * v30;
        plane.c = v41 * v30;
        v29 = v30 * v33;
      }
      if ( v17 | v16 )
      {
        if ( v13 == 0.0 )
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
          goto LABEL_44;
        }
        if ( plane.c == 0.0 )
        {
          if ( v13 <= 0.0 )
          {
            if ( v13 != -1.0 )
              v13 = -1.0;
          }
          else if ( v13 != 1.0 )
          {
            v13 = 1.0;
          }
          goto LABEL_44;
        }
      }
      else if ( v13 == 0.0 && plane.c == 0.0 )
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
        goto LABEL_44;
      }
      if ( COERCE_FLOAT(LODWORD(plane.a) & 0x7FFFFFFF) == 1.0 )
      {
        if ( v13 != 0.0 || plane.c != 0.0 )
        {
          plane.c = 0.0;
          goto LABEL_43;
        }
      }
      else
      {
        v34 = v13;
        if ( COERCE_FLOAT(LODWORD(v34) & 0x7FFFFFFF) == 1.0 )
        {
          if ( plane.a != 0.0 || plane.c != 0.0 )
          {
            plane.c = 0.0;
            plane.a = 0.0;
          }
          goto LABEL_44;
        }
        if ( COERCE_FLOAT(LODWORD(plane.c) & 0x7FFFFFFF) == 1.0 && (plane.a != 0.0 || v13 != 0.0) )
        {
          plane.a = 0.0;
LABEL_43:
          v13 = 0.0;
        }
      }
LABEL_44:
      if ( v29 == 0.0 )
        d = plane.d;
      else
        d = -(plane.c * tr.primaryView->renderView.vieworg.z
            + v13 * tr.primaryView->renderView.vieworg.y
            + plane.a * tr.primaryView->renderView.vieworg.x);
      mainStage = this->mainStage;
      regs = this->regs;
      mLightLocParm = this->mLightLocParm;
      fd = v13 * origin->y + plane.c * origin->z + plane.a * origin->x + d;
      rvNewShaderStage::SetShaderParameter(mainStage, mLightLocParm, regs, &temp.x, 3);
      rvNewShaderStage::SetShaderParameter(this->mainStage, this->mLightColorParm, this->regs, &color->x, 3);
      rvNewShaderStage::SetShaderParameter(this->mainStage, this->mLightSizeParm, this->regs, &size, 1);
      rvNewShaderStage::SetShaderParameter(this->mainStage, this->mLightMinDistanceParm, this->regs, &fd, 1);
      this->mainStage->UpdateShaderParms(this->mainStage, ptr->regs, 0);
      qglBegin(7u);
      v35 = 1.0 - y1 * 0.0020876827;
      v31 = x1 * 0.0015649452;
      qglTexCoord2f(v31, v35);
      qglMultiTexCoord2fARB(0x84C1u, 0.0, 0.0);
      qglVertex2f(x1, y1);
      v23 = v35;
      v36 = x2 * 0.0015649452;
      v20 = v36;
      qglTexCoord2f(v36, v23);
      qglMultiTexCoord2fARB(0x84C1u, 1.0, 0.0);
      qglVertex2f(x2, y1);
      v37 = 1.0 - y2 * 0.0020876827;
      qglTexCoord2f(v20, v37);
      qglMultiTexCoord2fARB(0x84C1u, 1.0, 1.0);
      qglVertex2f(x2, y2);
      qglTexCoord2f(v31, v37);
      qglMultiTexCoord2fARB(0x84C1u, 0.0, 1.0);
      qglVertex2f(x1, y2);
      qglEnd();
      ++numDrawn;
      return;
    }
  }
}

// FUNC: public: void __thiscall rvAL::Display(struct viewEntity_s const *,bool)
void __thiscall rvAL::Display(rvAL *this, const viewEntity_s *viewEnts, bool prePass)
{
  int v3; // ebx
  rvNewShaderStage *newShaderStage; // ecx
  int ShaderParameter; // eax
  rvNewShaderStage *mainStage; // ecx
  int v8; // eax
  rvNewShaderStage *v9; // ecx
  int v10; // eax
  rvNewShaderStage *v11; // ecx
  bool v12; // cc
  float *lSize; // ebp
  float *p_z; // edi
  double v15; // st7
  float v16; // edx
  long double v17; // st6
  double v18; // st7
  idVec3 origin; // [esp+Ch] [ebp-30h] BYREF
  idVec3 color; // [esp+18h] [ebp-24h] BYREF
  idVec3 amount; // [esp+24h] [ebp-18h]
  float v22; // [esp+38h] [ebp-4h]
  int prePassa; // [esp+44h] [ebp+8h]

  v3 = 0;
  if ( !prePass )
  {
    newShaderStage = ALMaterial->stages[1].newShaderStage;
    this->mainStage = newShaderStage;
    ShaderParameter = rvNewShaderStage::FindShaderParameter(newShaderStage, "LightLoc");
    mainStage = this->mainStage;
    this->mLightLocParm = ShaderParameter;
    v8 = rvNewShaderStage::FindShaderParameter(mainStage, "LightColor");
    v9 = this->mainStage;
    this->mLightColorParm = v8;
    v10 = rvNewShaderStage::FindShaderParameter(v9, "LightSize");
    v11 = this->mainStage;
    this->mLightSizeParm = v10;
    this->mLightMinDistanceParm = rvNewShaderStage::FindShaderParameter(v11, "LightMinDistance");
    RB_SetGL2D2();
    qglColor4f(1.0, 1.0, 1.0, 1.0);
    GL_State(32);
    numDrawn = 0;
    if ( viewEnts && !cvarSystem->GetCVarBool(cvarSystem, "rj") )
    {
      this->mainStage->Bind(this->mainStage, ptr->regs, 0);
      memset(&origin, 0, sizeof(origin));
      color.x = 1.0;
      color.y = 1.0;
      color.z = 0.0;
      rvAL::DrawLight(this, &origin, 200.0, &color);
      v12 = this->count <= 0;
      prePassa = 0;
      this->offset = this->offset + 0.0049999999;
      if ( !v12 )
      {
        lSize = this->lSize;
        p_z = &this->lOrigin[0].z;
        do
        {
          v15 = (double)prePassa;
          v22 = *p_z;
          v16 = *lSize;
          v17 = 0.78422999 * v15 + this->offset;
          origin.z = v22;
          amount.x = cos(v17) * 0.0;
          amount.y = cos(v15 * 0.234 + this->offset) * 0.0;
          v18 = amount.y + *(p_z - 1);
          origin.x = amount.x + *(p_z - 2);
          origin.y = v18;
          rvAL::DrawLight(this, &origin, v16, (idVec3 *)(p_z + 298));
          ++v3;
          p_z += 3;
          ++lSize;
          prePassa = v3;
        }
        while ( v3 < this->count );
      }
      this->mainStage->UnBind(this->mainStage);
    }
    backEnd.glState.forceGlState = 1;
    RB_RestoreDrawingView();
  }
}

// FUNC: void __cdecl RB_DisplaySpecialEffects(struct viewEntity_s const *,bool)
void __cdecl RB_DisplaySpecialEffects(const viewEntity_s *viewEnts, bool prePass)
{
  if ( (tr.specialEffectsEnabled & 1) != 0 && DepthTexture )
    rvBlurTexture::Display(DepthTexture, viewEnts, prePass);
  if ( (tr.specialEffectsEnabled & 2) != 0 )
  {
    if ( ptr )
      rvAL::Display(ptr, viewEnts, prePass);
  }
}
