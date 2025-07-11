
// FUNC: void __cdecl GL_SelectTexture(int)
void __cdecl GL_SelectTexture(int unit)
{
  if ( backEnd.glState.currenttmu != unit )
  {
    if ( unit < 0 || unit >= glConfig.maxTextureUnits && unit >= glConfig.maxTextureImageUnits )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "GL_SelectTexture: unit = %i",
        unit);
    }
    else
    {
      qglActiveTextureARB(unit + 33984);
      qglClientActiveTextureARB(unit + 33984);
      backEnd.glState.currenttmu = unit;
    }
  }
}

// FUNC: void __cdecl GL_Cull(int)
void __cdecl GL_Cull(int cullType)
{
  if ( backEnd.glState.faceCulling != cullType )
  {
    if ( cullType == 2 )
    {
      qglDisable(0xB44u);
      backEnd.glState.faceCulling = 2;
      return;
    }
    if ( backEnd.glState.faceCulling == 2 )
      qglEnable(0xB44u);
    if ( cullType == 1 )
    {
      if ( !backEnd.viewDef->isMirror )
      {
LABEL_8:
        qglCullFace(0x405u);
        backEnd.glState.faceCulling = cullType;
        return;
      }
    }
    else if ( backEnd.viewDef->isMirror )
    {
      goto LABEL_8;
    }
    qglCullFace(0x404u);
    backEnd.glState.faceCulling = cullType;
  }
}

// FUNC: void __cdecl GL_TexEnv(int)
void __cdecl GL_TexEnv(int env)
{
  bool v1; // zf

  if ( env != backEnd.glState.tmu[backEnd.glState.currenttmu].texEnv )
  {
    backEnd.glState.tmu[backEnd.glState.currenttmu].texEnv = env;
    if ( env > 8449 )
    {
      v1 = env == 34160;
    }
    else
    {
      if ( env >= 8448 || env == 260 )
      {
LABEL_9:
        qglTexEnvi(0x2300u, 0x2200u, env);
        return;
      }
      v1 = env == 7681;
    }
    if ( !v1 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "GL_TexEnv: invalid env '%d' passed\n",
        env);
      return;
    }
    goto LABEL_9;
  }
}

// FUNC: void __cdecl GL_PolygonOffsetState(bool,float,float)
void __cdecl GL_PolygonOffsetState(bool enable, float factor, float units)
{
  if ( enable )
  {
    if ( !backEnd.glState.polyOffset
      || factor != backEnd.glState.polyOffsetFactor
      || units != backEnd.glState.polyOffsetUnits )
    {
      qglPolygonOffset(factor, units);
      qglEnable(0x8037u);
      backEnd.glState.polyOffset = 1;
      backEnd.glState.polyOffsetFactor = factor;
      backEnd.glState.polyOffsetUnits = units;
    }
  }
  else if ( backEnd.glState.polyOffset )
  {
    qglDisable(0x8037u);
    backEnd.glState.polyOffset = 0;
  }
}

// FUNC: void __cdecl GL_State(int)
void __cdecl GL_State(int stateBits)
{
  int v1; // ebx
  unsigned int v2; // edi
  unsigned int v3; // esi
  int v4; // eax

  if ( !r_useStateCaching.internalVar->integerValue || backEnd.glState.forceGlState )
  {
    v1 = -1;
    backEnd.glState.forceGlState = 0;
  }
  else
  {
    v1 = stateBits ^ backEnd.glState.glStateBits;
    if ( stateBits == backEnd.glState.glStateBits )
      return;
  }
  if ( (v1 & 0x30000) != 0 )
  {
    if ( (stateBits & 0x20000) != 0 )
    {
      qglDepthFunc(0x202u);
    }
    else if ( (stateBits & 0x10000) != 0 )
    {
      qglDepthFunc(0x207u);
    }
    else
    {
      qglDepthFunc(0x203u);
    }
  }
  if ( (_BYTE)v1 )
  {
    switch ( stateBits & 0xF )
    {
      case 0:
        v2 = 1;
        break;
      case 1:
        v2 = 0;
        break;
      case 3:
        v2 = 774;
        break;
      case 4:
        v2 = 775;
        break;
      case 5:
        v2 = 770;
        break;
      case 6:
        v2 = 771;
        break;
      case 7:
        v2 = 772;
        break;
      case 8:
        v2 = 773;
        break;
      case 9:
        v2 = 776;
        break;
      case 0xA:
        v2 = 768;
        break;
      case 0xB:
        v2 = 769;
        break;
      default:
        v2 = 1;
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "GL_State: invalid src blend state bits\n");
        break;
    }
    switch ( stateBits & 0xF0 )
    {
      case 0:
        v3 = 0;
        break;
      case 0x20:
        v3 = 1;
        break;
      case 0x30:
        v3 = 768;
        break;
      case 0x40:
        v3 = 769;
        break;
      case 0x50:
        v3 = 770;
        break;
      case 0x60:
        v3 = 771;
        break;
      case 0x70:
        v3 = 772;
        break;
      case 0x80:
        v3 = 773;
        break;
      case 0x90:
        v3 = 774;
        break;
      case 0xA0:
        v3 = 775;
        break;
      default:
        v3 = 1;
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "GL_State: invalid dst blend state bits\n");
        break;
    }
    qglBlendFunc(v2, v3);
  }
  if ( (v1 & 0x100) != 0 )
    qglDepthMask((stateBits & 0x100) == 0);
  if ( (v1 & 0x1E00) != 0 )
    qglColorMask(
      (stateBits & 0x200) == 0,
      (stateBits & 0x400) == 0,
      (stateBits & 0x800) == 0,
      (stateBits & 0x1000) == 0);
  if ( (v1 & 0x2000) != 0 )
  {
    if ( (stateBits & 0x2000) != 0 )
      qglPolygonMode(0x408u, 0x1B01u);
    else
      qglPolygonMode(0x408u, 0x1B02u);
  }
  if ( (v1 & 0x70000000) != 0 )
  {
    v4 = stateBits & 0x70000000;
    if ( (stateBits & 0x70000000u) > 0x20000000 )
    {
      if ( v4 == 0x40000000 )
      {
        qglEnable(0xBC0u);
        qglAlphaFunc(0x206u, 0.5);
      }
    }
    else
    {
      if ( (stateBits & 0x70000000) == 0x20000000 )
      {
        qglEnable(0xBC0u);
        qglAlphaFunc(0x201u, 0.5);
        backEnd.glState.glStateBits = stateBits;
        return;
      }
      if ( !v4 )
      {
        qglDisable(0xBC0u);
        backEnd.glState.glStateBits = stateBits;
        return;
      }
      if ( v4 == 0x10000000 )
      {
        qglEnable(0xBC0u);
        qglAlphaFunc(0x202u, 1.0);
        backEnd.glState.glStateBits = stateBits;
        return;
      }
    }
  }
  backEnd.glState.glStateBits = stateBits;
}

// FUNC: void __cdecl GL_PolygonOffset(class idMaterial const *,bool)
void __cdecl GL_PolygonOffset(const idMaterial *material, bool enable)
{
  float units; // [esp+0h] [ebp-4h]

  if ( (material->materialFlags & 2) != 0 )
  {
    units = r_offsetUnits.internalVar->floatValue * material->polygonOffset;
    GL_PolygonOffsetState(enable, r_offsetFactor.internalVar->floatValue, units);
  }
}

// FUNC: void __cdecl GL_VertexAttribState(unsigned int)
void __cdecl GL_VertexAttribState(unsigned int vertexAttribStateBits)
{
  unsigned int v1; // ebx
  int currenttmu; // esi
  int i; // ebp
  int v4; // edi
  int activeTmu; // [esp+4h] [ebp-4h]

  if ( r_useStateCaching.internalVar->integerValue )
  {
    v1 = vertexAttribStateBits ^ backEnd.glState.vertexAttribStateBits;
    if ( vertexAttribStateBits == backEnd.glState.vertexAttribStateBits )
      return;
  }
  else
  {
    v1 = -1;
  }
  backEnd.glState.vertexAttribStateBits = vertexAttribStateBits;
  if ( (v1 & 1) == 0 )
    goto LABEL_69;
  if ( (vertexAttribStateBits & 1) != 0 )
    qglEnableClientState(0x8074u);
  else
    qglDisableClientState(0x8074u);
  v1 &= ~1u;
  if ( v1 )
  {
LABEL_69:
    if ( (v1 & 4) == 0 )
      goto LABEL_70;
    if ( (vertexAttribStateBits & 4) != 0 )
      qglEnableClientState(0x8076u);
    else
      qglDisableClientState(0x8076u);
    v1 &= ~4u;
    if ( v1 )
    {
LABEL_70:
      if ( (v1 & 2) == 0 )
        goto LABEL_19;
      if ( (vertexAttribStateBits & 2) != 0 )
        qglEnableClientState(0x8075u);
      else
        qglDisableClientState(0x8075u);
      v1 &= ~2u;
      if ( v1 )
      {
LABEL_19:
        if ( (v1 & 0x7F8) != 0 )
        {
          currenttmu = backEnd.glState.currenttmu;
          activeTmu = backEnd.glState.currenttmu;
          for ( i = 0; i < 8; ++i )
          {
            v4 = 8 << i;
            if ( ((8 << i) & v1) != 0 )
            {
              if ( i != backEnd.glState.currenttmu )
              {
                qglClientActiveTextureARB(i + 33984);
                backEnd.glState.currenttmu = i;
              }
              if ( (v4 & vertexAttribStateBits) != 0 )
              {
                if ( ((0x1000000 << i) & v1) != 0 )
                {
                  qglDisableVertexAttribArrayARB(i + 8);
                  v1 &= ~(0x1000000 << i);
                }
                qglEnableClientState(0x8078u);
                currenttmu = activeTmu;
              }
              else
              {
                qglDisableClientState(0x8078u);
              }
              v1 &= ~v4;
              if ( (v1 & 0x7F8) == 0 )
                break;
            }
          }
          if ( currenttmu != backEnd.glState.currenttmu )
          {
            qglClientActiveTextureARB(currenttmu + 33984);
            backEnd.glState.currenttmu = currenttmu;
          }
        }
        if ( (v1 & 0xE20000) != 0 )
        {
          if ( (v1 & 0x20000) != 0 )
          {
            if ( (vertexAttribStateBits & 0x20000) != 0 )
              qglEnableVertexAttribArrayARB(1u);
            else
              qglDisableVertexAttribArrayARB(1u);
          }
          if ( (v1 & 0x200000) != 0 )
          {
            if ( (vertexAttribStateBits & 0x200000) != 0 )
              qglEnableVertexAttribArrayARB(5u);
            else
              qglDisableVertexAttribArrayARB(5u);
          }
          if ( (v1 & 0x400000) != 0 )
          {
            if ( (vertexAttribStateBits & 0x400000) != 0 )
              qglEnableVertexAttribArrayARB(6u);
            else
              qglDisableVertexAttribArrayARB(6u);
          }
          if ( (v1 & 0x800000) != 0 )
          {
            if ( (vertexAttribStateBits & 0x800000) == 0 )
              qglDisableVertexAttribArrayARB(7u);
            else
              qglEnableVertexAttribArrayARB(7u);
          }
        }
        if ( (v1 & 0xF000000) != 0 )
        {
          if ( (v1 & 0x1000000) != 0 )
          {
            if ( (vertexAttribStateBits & 0x1000000) != 0 )
              qglEnableVertexAttribArrayARB(8u);
            else
              qglDisableVertexAttribArrayARB(8u);
          }
          if ( (v1 & 0x2000000) != 0 )
          {
            if ( (vertexAttribStateBits & 0x2000000) != 0 )
              qglEnableVertexAttribArrayARB(9u);
            else
              qglDisableVertexAttribArrayARB(9u);
          }
          if ( (v1 & 0x4000000) != 0 )
          {
            if ( (vertexAttribStateBits & 0x4000000) != 0 )
              qglEnableVertexAttribArrayARB(0xAu);
            else
              qglDisableVertexAttribArrayARB(0xAu);
          }
          if ( (v1 & 0x8000000) != 0 )
          {
            if ( (vertexAttribStateBits & 0x8000000) != 0 )
              qglEnableVertexAttribArrayARB(0xBu);
            else
              qglDisableVertexAttribArrayARB(0xBu);
          }
        }
      }
    }
  }
}

// FUNC: void __cdecl GL_EnableVertexAttribState(unsigned int)
void __cdecl GL_EnableVertexAttribState(unsigned int vertexAttribStateBits)
{
  GL_VertexAttribState(vertexAttribStateBits | backEnd.glState.vertexAttribStateBits);
}

// FUNC: void __cdecl GL_DisableVertexAttribState(unsigned int)
void __cdecl GL_DisableVertexAttribState(unsigned int vertexAttribStateBits)
{
  GL_VertexAttribState(backEnd.glState.vertexAttribStateBits & ~vertexAttribStateBits);
}

// FUNC: void __cdecl GL_DisableTexCoordState(void)
void __cdecl GL_DisableTexCoordState()
{
  GL_VertexAttribState(backEnd.glState.vertexAttribStateBits & ~(8 << SLOBYTE(backEnd.glState.currenttmu)));
}

// FUNC: void __cdecl RB_SetGL2D(void)
void __cdecl RB_SetGL2D()
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
  if ( backEnd.glState.faceCulling != 2 )
  {
    qglDisable(0xB44u);
    backEnd.glState.faceCulling = 2;
  }
  qglDisable(0xB71u);
  qglDisable(0xB90u);
}

// FUNC: RB_SetBuffer
void __usercall RB_SetBuffer(_DWORD *data@<eax>)
{
  float *v1; // eax
  const char *value; // ecx
  int v3; // eax
  float c[3]; // [esp+4h] [ebp-Ch] BYREF

  backEnd.frameCount = data[3];
  qglDrawBuffer(data[2]);
  if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 0x2000) )
  {
    v1 = (float *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 100))(*(_DWORD *)common.ip);
    if ( v1 )
      qglClearColor(*v1, v1[1], v1[2], v1[3]);
    else
      qglClearColor(0.25, 0.25, 0.25, 1.0);
LABEL_19:
    qglClear(0x4000u);
    return;
  }
  if ( r_clear.internalVar->floatValue != 0.0 )
    goto LABEL_12;
  value = r_clear.internalVar->value;
  v3 = 0;
  if ( !*value )
    goto LABEL_12;
  do
    ++v3;
  while ( value[v3] );
  if ( v3 != 1
    || r_lockSurfaces.internalVar->integerValue
    || r_singleArea.internalVar->integerValue
    || r_showOverDraw.internalVar->integerValue )
  {
LABEL_12:
    if ( sscanf(r_clear.internalVar->value, "%f %f %f", c, &c[1], &c[2]) == 3 )
    {
      qglClearColor(c[0], c[1], c[2], 1.0);
    }
    else if ( r_clear.internalVar->integerValue == 2 )
    {
      qglClearColor(0.0, 0.0, 0.0, 1.0);
    }
    else if ( r_showOverDraw.internalVar->integerValue )
    {
      qglClearColor(1.0, 1.0, 1.0, 1.0);
    }
    else
    {
      qglClearColor(0.40000001, 0.0, 0.25, 1.0);
    }
    goto LABEL_19;
  }
}

// FUNC: void __cdecl RB_ShowImages(void)
void __cdecl RB_ShowImages()
{
  int i; // ebp
  idImage *v1; // eax
  float v2; // esi
  int v3; // eax
  float w; // [esp+4h] [ebp-18h]
  float h; // [esp+8h] [ebp-14h]
  float x; // [esp+Ch] [ebp-10h]
  float y; // [esp+10h] [ebp-Ch]
  float v8; // [esp+14h] [ebp-8h]
  float v9; // [esp+14h] [ebp-8h]
  int start; // [esp+18h] [ebp-4h]

  RB_SetGL2D();
  qglFinish();
  start = Sys_Milliseconds();
  for ( i = 0; i < globalImages->GetNumImages(globalImages); ++i )
  {
    v1 = globalImages->GetImageByIndex(globalImages, i);
    if ( v1->texnum != -1 || v1->partialImage )
    {
      w = (float)(glConfig.vidWidth / 20);
      h = (float)(glConfig.vidHeight / 15);
      x = (double)(i % 20) * w;
      y = (double)(i / 20) * h;
      if ( r_showImages.internalVar->integerValue == 2 )
      {
        w = (double)v1->uploadWidth * w * 0.001953125;
        h = (double)v1->uploadHeight * h * 0.001953125;
      }
      v1->Bind(v1);
      qglBegin(7u);
      qglTexCoord2f(0.0, 0.0);
      qglVertex2f(x, y);
      qglTexCoord2f(1.0, 0.0);
      v8 = x + w;
      v2 = v8;
      qglVertex2f(v8, y);
      qglTexCoord2f(1.0, 1.0);
      v9 = y + h;
      qglVertex2f(v2, v9);
      qglTexCoord2f(0.0, 1.0);
      qglVertex2f(x, v9);
      qglEnd();
    }
  }
  qglFinish();
  v3 = Sys_Milliseconds();
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%i msec to draw all images\n",
    v3 - start);
}

// FUNC: void __cdecl RB_SetDefaultGLState(void)
void __cdecl RB_SetDefaultGLState()
{
  int v0; // esi
  unsigned int v1; // ebx

  qglClearDepth(1.0);
  qglColor4f(1.0, 1.0, 1.0, 1.0);
  GL_VertexAttribState(0);
  memset(&backEnd.glState, 0, sizeof(backEnd.glState));
  backEnd.glState.forceGlState = 1;
  if ( backEnd.glState.currenttmu )
  {
    if ( glConfig.maxTextureUnits > 0 || glConfig.maxTextureImageUnits > 0 )
    {
      qglActiveTextureARB(0x84C0u);
      qglClientActiveTextureARB(0x84C0u);
      backEnd.glState.currenttmu = 0;
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "GL_SelectTexture: unit = %i",
        0);
    }
  }
  GL_VertexAttribState(9u);
  qglColorMask(1u, 1u, 1u, 1u);
  qglEnable(0xB71u);
  qglEnable(0xBE2u);
  qglEnable(0xC11u);
  qglEnable(0xB44u);
  qglDisable(0xB50u);
  qglDisable(0xB24u);
  qglDisable(0xB90u);
  qglPolygonMode(0x408u, 0x1B02u);
  qglDepthMask(1u);
  qglDepthFunc(0x207u);
  qglCullFace(0x408u);
  qglShadeModel(0x1D01u);
  if ( r_useScissor.internalVar->integerValue )
    qglScissor(0, 0, glConfig.vidWidth, glConfig.vidHeight);
  v0 = glConfig.maxTextureUnits - 1;
  if ( glConfig.maxTextureUnits - 1 >= 0 )
  {
    v1 = v0 + 33984;
    do
    {
      if ( backEnd.glState.currenttmu != v0 )
      {
        if ( v0 < 0 || v0 >= glConfig.maxTextureUnits && v0 >= glConfig.maxTextureImageUnits )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "GL_SelectTexture: unit = %i",
            v0);
        }
        else
        {
          qglActiveTextureARB(v1);
          qglClientActiveTextureARB(v1);
          backEnd.glState.currenttmu = v0;
        }
      }
      qglTexGenf(0x2000u, 0x2500u, 9217.0);
      qglTexGenf(0x2001u, 0x2500u, 9217.0);
      qglTexGenf(0x2002u, 0x2500u, 9217.0);
      qglTexGenf(0x2003u, 0x2500u, 9217.0);
      if ( backEnd.glState.tmu[backEnd.glState.currenttmu].texEnv != 8448 )
      {
        backEnd.glState.tmu[backEnd.glState.currenttmu].texEnv = 8448;
        qglTexEnvi(0x2300u, 0x2200u, 8448);
      }
      qglDisable(0xDE1u);
      if ( glConfig.texture3DAvailable )
        qglDisable(0x806Fu);
      if ( glConfig.cubeMapAvailable )
        qglDisable(0x8513u);
      --v0;
      --v1;
    }
    while ( v0 >= 0 );
  }
}

// FUNC: void __cdecl RB_ExecuteBackEndCommands(struct emptyCommand_t const *)
void __cdecl RB_ExecuteBackEndCommands(emptyCommand_t *cmds)
{
  emptyCommand_t *v1; // esi
  int v2; // edi
  int v3; // ebp
  int v4; // ebx
  idImage *commandId; // ecx
  int c_copyRenders; // [esp+10h] [ebp-8h]
  int c_swapBuffers; // [esp+14h] [ebp-4h]

  v1 = cmds;
  v2 = 0;
  v3 = 0;
  v4 = 0;
  c_swapBuffers = 0;
  c_copyRenders = 0;
  if ( cmds->commandId || cmds->next )
  {
    backEndStartTime = Sys_Milliseconds();
    RB_SetDefaultGLState();
    globalImages->CompleteBackgroundImageLoads(globalImages);
    do
    {
      switch ( v1->commandId )
      {
        case RC_NOP:
          break;
        case RC_DRAW_DEPTH_TEXTURE:
          RB_DrawDepthTexture((const drawSurfsCommand_t *)v1);
          break;
        case RC_DRAW_VIEW:
          RB_DrawView(v1);
          if ( *(_DWORD *)(v1[1].commandId + 472) )
            ++v3;
          else
            ++v4;
          break;
        case RC_SET_BUFFER:
          RB_SetBuffer(v1);
          ++v2;
          break;
        case RC_COPY_RENDER:
          if ( !r_skipCopyTexture.internalVar->integerValue )
          {
            commandId = (idImage *)v1[3].commandId;
            if ( commandId )
              idImage::CopyFramebuffer(commandId, v1[1].commandId, (int)v1[1].next, v1[2].commandId, (int)v1[2].next, 0);
          }
          ++c_copyRenders;
          break;
        case RC_SWAP_BUFFERS:
          if ( r_showImages.internalVar->integerValue )
            RB_ShowImages();
          if ( r_finish.internalVar->integerValue )
            qglFinish();
          if ( !r_frontBuffer.internalVar->integerValue )
            GLimp_SwapBuffers();
          ++c_swapBuffers;
          break;
        default:
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "RB_ExecuteBackEndCommands: bad commandId");
          break;
      }
      v1 = (emptyCommand_t *)v1->next;
    }
    while ( v1 );
    qglBindTexture(0xDE1u, 0);
    backEnd.glState.tmu[0].current2DMap = -1;
    backEndFinishTime = Sys_Milliseconds();
    backEnd.pc.msec = backEndFinishTime - backEndStartTime;
    if ( r_debugRenderToTexture.internalVar->integerValue == 1 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "3d: %i, 2d: %i, SetBuf: %i, SwpBuf: %i, CpyRenders: %i, CpyFrameBuf: %i\n",
        v3,
        v4,
        v2,
        c_swapBuffers,
        c_copyRenders,
        backEnd.c_copyFrameBuffer);
      backEnd.c_copyFrameBuffer = 0;
    }
  }
}
