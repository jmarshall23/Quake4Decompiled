
// FUNC: bool __cdecl R_CheckExtension(char *)
char __cdecl R_CheckExtension(char *name)
{
  if ( strstr(glConfig.extensions_string, name) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "...using %s\n", name);
    return 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      name);
    return 0;
  }
}

// FUNC: R_ReloadShaders_f
void __cdecl R_ReloadShaders_f()
{
  rvNewShaderStage::R_Shaders_Shutdown();
  rvNewShaderStage::R_Shaders_Init();
}

// FUNC: R_ListModes_f
void __cdecl R_ListModes_f()
{
  int v0; // esi
  vidmode_s *v1; // edi

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
  v0 = 0;
  if ( s_numVidModes > 0 )
  {
    v1 = r_vidModes;
    do
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%s\n",
        v1->description);
      ++v0;
      ++v1;
    }
    while ( v0 < s_numVidModes );
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
}

// FUNC: void __cdecl init_destination(struct jpeg_compress_struct *)
void __cdecl init_destination(jpeg_compress_struct *cinfo)
{
  jpeg_destination_mgr *dest; // eax
  unsigned int free_in_buffer; // edx

  dest = cinfo->dest;
  free_in_buffer = dest[1].free_in_buffer;
  dest->next_output_byte = dest[1].next_output_byte;
  dest->free_in_buffer = free_in_buffer;
}

// FUNC: void __cdecl term_destination(struct jpeg_compress_struct *)
void __cdecl term_destination(jpeg_compress_struct *cinfo)
{
  hackSize = cinfo->dest[1].free_in_buffer - cinfo->dest->free_in_buffer;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::BeginLevelLoad(void)
void __thiscall idRenderSystemLocal::BeginLevelLoad(idRenderSystemLocal *this)
{
  renderModelManager->BeginLevelLoad(renderModelManager);
  globalImages->BeginLevelLoad(globalImages);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::ShutdownOpenGL(void)
void __thiscall idRenderSystemLocal::ShutdownOpenGL(idRenderSystemLocal *this)
{
  R_ShutdownFrameData();
  R_ShutdownSpecialEffects();
  rvNewShaderStage::R_Shaders_Shutdown();
  glConfig.GLSLProgramAvailable = 0;
  GLimp_Shutdown();
  glConfig.isInitialized = 0;
}

// FUNC: public: virtual bool __thiscall idRenderSystemLocal::IsOpenGLRunning(void)const
bool __thiscall idRenderSystemLocal::IsOpenGLRunning(idRenderSystemLocal *this)
{
  return glConfig.isInitialized;
}

// FUNC: public: virtual bool __thiscall idRenderSystemLocal::IsFullScreen(void)const
bool __thiscall idRenderSystemLocal::IsFullScreen(idRenderSystemLocal *this)
{
  return glConfig.isFullscreen;
}

// FUNC: public: virtual int __thiscall idRenderSystemLocal::GetScreenWidth(void)const
int __thiscall idRenderSystemLocal::GetScreenWidth(idRenderSystemLocal *this)
{
  return glConfig.vidWidth;
}

// FUNC: public: virtual int __thiscall idRenderSystemLocal::GetScreenHeight(void)const
int __thiscall idRenderSystemLocal::GetScreenHeight(idRenderSystemLocal *this)
{
  return glConfig.vidHeight;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::GetCardCaps(bool &,bool &)
void __thiscall idRenderSystemLocal::GetCardCaps(idRenderSystemLocal *this, bool *oldCard, bool *nv10or20)
{
  bool v3; // al

  v3 = tr.backEndRenderer == BE_NV10 || tr.backEndRenderer == BE_NV20;
  *nv10or20 = v3;
  *oldCard = tr.backEndRenderer == BE_ARB
          || tr.backEndRenderer == BE_R200
          || tr.backEndRenderer == BE_NV10
          || tr.backEndRenderer == BE_NV20;
}

// FUNC: R_CheckPortableExtensions
char R_CheckPortableExtensions()
{
  bool v0; // al
  bool v1; // al
  bool v2; // al
  bool v3; // al
  bool v4; // al
  bool v5; // al
  bool v6; // al
  bool v7; // zf
  netadrtype_t type; // eax
  bool v9; // al
  bool v10; // al
  bool v11; // al
  bool v12; // al
  bool v13; // al
  bool v14; // al
  bool v15; // al
  netadrtype_t v16; // eax
  bool v17; // al
  bool v18; // al
  bool v19; // al
  bool v20; // al
  bool v21; // al
  bool v22; // al
  bool v23; // al
  int v24; // esi
  int v25; // eax
  void (__stdcall *v26)(long double, long double); // eax
  const char *v28; // [esp+4h] [ebp-8h]
  const char *v29; // [esp+4h] [ebp-8h]

  glConfig.glVersion = atof(glConfig.version_string);
  if ( strstr(glConfig.extensions_string, "GL_ARB_multitexture") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_ARB_multitexture");
    v0 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_ARB_multitexture");
    v0 = 0;
  }
  glConfig.multitextureAvailable = v0;
  if ( v0 )
  {
    qglMultiTexCoord2fARB = (void (__stdcall *)(unsigned int, float, float))GLimp_ExtensionPointer("glMultiTexCoord2fARB");
    qglMultiTexCoord2fvARB = (void (__stdcall *)(unsigned int, float *))GLimp_ExtensionPointer("glMultiTexCoord2fvARB");
    qglActiveTextureARB = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glActiveTextureARB");
    qglClientActiveTextureARB = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glClientActiveTextureARB");
    qglGetIntegerv(0x84E2u, &glConfig.maxTextureUnits);
    if ( glConfig.maxTextureUnits <= 8 )
    {
      if ( glConfig.maxTextureUnits < 2 )
        glConfig.multitextureAvailable = 0;
    }
    else
    {
      glConfig.maxTextureUnits = 8;
    }
    qglGetIntegerv(0x8871u, &glConfig.maxTextureCoords);
    qglGetIntegerv(0x8872u, &glConfig.maxTextureImageUnits);
  }
  if ( strstr(glConfig.extensions_string, "GL_ARB_texture_env_combine") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_ARB_texture_env_combine");
    v1 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_ARB_texture_env_combine");
    v1 = 0;
  }
  glConfig.textureEnvCombineAvailable = v1;
  if ( strstr(glConfig.extensions_string, "GL_ARB_texture_cube_map") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_ARB_texture_cube_map");
    v2 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_ARB_texture_cube_map");
    v2 = 0;
  }
  glConfig.cubeMapAvailable = v2;
  if ( strstr(glConfig.extensions_string, "GL_ARB_texture_env_dot3") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_ARB_texture_env_dot3");
    v3 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_ARB_texture_env_dot3");
    v3 = 0;
  }
  glConfig.envDot3Available = v3;
  if ( strstr(glConfig.extensions_string, "GL_ARB_texture_env_add") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_ARB_texture_env_add");
    v4 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_ARB_texture_env_add");
    v4 = 0;
  }
  glConfig.textureEnvAddAvailable = v4;
  if ( strstr(glConfig.extensions_string, "GL_ARB_texture_non_power_of_two") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_ARB_texture_non_power_of_two");
    v5 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_ARB_texture_non_power_of_two");
    v5 = 0;
  }
  glConfig.textureNonPowerOfTwoAvailable = v5;
  if ( r_inhibitNativePowerOfTwo.internalVar->integerValue )
    glConfig.textureNonPowerOfTwoAvailable = 0;
  if ( strstr(glConfig.extensions_string, "GL_NV_blend_square") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_NV_blend_square");
    v6 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_NV_blend_square");
    v6 = 0;
  }
  glConfig.blendSquareAvailable = v6;
  v7 = strstr(glConfig.extensions_string, "GL_ARB_texture_compression") == 0;
  type = common.type;
  v28 = "GL_ARB_texture_compression";
  if ( v7
    || ((*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "...using %s\n",
          "GL_ARB_texture_compression"),
        v7 = strstr(glConfig.extensions_string, "GL_EXT_texture_compression_s3tc") == 0,
        type = common.type,
        v28 = "GL_EXT_texture_compression_s3tc",
        v7) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)type + 124))(type, "X..%s not found\n", v28);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Texture compression unavailable");
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_EXT_texture_compression_s3tc");
    qglCompressedTexImage2DARB = (void (__stdcall *)(unsigned int, int, unsigned int, int, int, int, int, const void *))GLimp_ExtensionPointer("glCompressedTexImage2DARB");
    qglGetCompressedTexImageARB = (void (__stdcall *)(unsigned int, int, void *))GLimp_ExtensionPointer("glGetCompressedTexImageARB");
  }
  if ( strstr(glConfig.extensions_string, "GL_EXT_texture_filter_anisotropic") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_EXT_texture_filter_anisotropic");
    v9 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_EXT_texture_filter_anisotropic");
    v9 = 0;
  }
  glConfig.anisotropicAvailable = v9;
  if ( v9 )
  {
    qglGetFloatv(0x84FFu, &glConfig.maxTextureAnisotropy);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "   maxTextureAnisotropy: %f\n",
      glConfig.maxTextureAnisotropy);
  }
  else
  {
    glConfig.maxTextureAnisotropy = 1.0;
  }
  if ( glConfig.glVersion < 1.4 )
  {
    if ( !strstr(glConfig.extensions_string, "GL_EXT_texture_lod") )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "X..%s not found\n",
        "GL_EXT_texture_lod");
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "X..%s not found\n",
        "GL_1.4_texture_lod_bias");
      glConfig.textureLODBiasAvailable = 0;
      goto LABEL_45;
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_EXT_texture_lod");
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "...using %s\n",
    "GL_1.4_texture_lod_bias");
  glConfig.textureLODBiasAvailable = 1;
LABEL_45:
  if ( strstr(glConfig.extensions_string, "GL_EXT_shared_texture_palette") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_EXT_shared_texture_palette");
    v10 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_EXT_shared_texture_palette");
    v10 = 0;
  }
  glConfig.sharedTexturePaletteAvailable = v10;
  if ( v10 )
    qglColorTableEXT = (void (__stdcall *)(int, int, int, int, int, const void *))GLimp_ExtensionPointer("glColorTableEXT");
  if ( strstr(glConfig.extensions_string, "GL_EXT_draw_range_elements") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_EXT_draw_range_elements");
    v11 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_EXT_draw_range_elements");
    v11 = 0;
  }
  glConfig.drawRangeElementsAvailable = v11;
  if ( v11 )
    qglDrawRangeElementsEXT = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, int, unsigned int, const void *))GLimp_ExtensionPointer("glDrawRangeElementsEXT");
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Required GL_EXT_draw_range_elements extension is not supported by this driver");
  if ( strstr(glConfig.extensions_string, "GL_EXT_blend_minmax") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_EXT_blend_minmax");
    v12 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_EXT_blend_minmax");
    v12 = 0;
  }
  glConfig.blendMinMaxAvailable = v12;
  if ( v12 )
    qglBlendEquationEXT = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glBlendEquationEXT");
  if ( strstr(glConfig.extensions_string, "GL_NV_float_buffer") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_NV_float_buffer");
    v13 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_NV_float_buffer");
    v13 = 0;
  }
  glConfig.floatBufferAvailable = v13;
  if ( strstr(glConfig.extensions_string, "GL_EXT_texture3D") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_EXT_texture3D");
    v14 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_EXT_texture3D");
    v14 = 0;
  }
  glConfig.texture3DAvailable = v14;
  if ( v14 )
    qglTexImage3D = (void (__stdcall *)(unsigned int, int, int, int, int, int, int, unsigned int, unsigned int, const void *))GLimp_ExtensionPointer("glTexImage3D");
  if ( strstr(glConfig.extensions_string, "GL_EXT_stencil_wrap") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_EXT_stencil_wrap");
    tr.stencilIncr = 34055;
    tr.stencilDecr = 34056;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_EXT_stencil_wrap");
    tr.stencilIncr = 7682;
    tr.stencilDecr = 7683;
  }
  if ( strstr(glConfig.extensions_string, "GL_NV_register_combiners") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_NV_register_combiners");
    v15 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_NV_register_combiners");
    v15 = 0;
  }
  glConfig.registerCombinersAvailable = v15;
  if ( v15 )
  {
    qglCombinerParameterfvNV = (void (__stdcall *)(unsigned int, const float *))GLimp_ExtensionPointer("glCombinerParameterfvNV");
    qglCombinerParameterivNV = (void (__stdcall *)(unsigned int, const int *))GLimp_ExtensionPointer("glCombinerParameterivNV");
    qglCombinerParameterfNV = (void (__stdcall *)(unsigned int, const float))GLimp_ExtensionPointer("glCombinerParameterfNV");
    qglCombinerParameteriNV = (void (__stdcall *)(unsigned int, const int))GLimp_ExtensionPointer("glCombinerParameteriNV");
    qglCombinerInputNV = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glCombinerInputNV");
    qglCombinerOutputNV = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned __int8, unsigned __int8, unsigned __int8))GLimp_ExtensionPointer("glCombinerOutputNV");
    qglFinalCombinerInputNV = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glFinalCombinerInputNV");
  }
  v7 = strstr(glConfig.extensions_string, "NV_vertex_program") == 0;
  v16 = common.type;
  v29 = "NV_vertex_program";
  if ( v7
    || ((*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "...using %s\n",
          "NV_vertex_program"),
        v7 = strstr(glConfig.extensions_string, "NV_fragment_program") == 0,
        v16 = common.type,
        v29 = "NV_fragment_program",
        v7) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)v16 + 124))(v16, "X..%s not found\n", v29);
    glConfig.nvProgramsAvailable = 0;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "NV_fragment_program");
    glConfig.nvProgramsAvailable = 1;
    qglBindProgramNV = (void (__stdcall *)(unsigned int, unsigned int))GLimp_ExtensionPointer("glBindProgramNV");
    qglLoadProgramNV = (void (__stdcall *)(unsigned int, unsigned int, int, const unsigned __int8 *))GLimp_ExtensionPointer("glLoadProgramNV");
    qglProgramParameter4fvNV = (void (__stdcall *)(unsigned int, unsigned int, const float *))GLimp_ExtensionPointer(
                                                                                                "glProgramParameter4fvNV");
  }
  if ( strstr(glConfig.extensions_string, "GL_EXT_stencil_two_side") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_EXT_stencil_two_side");
    v17 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_EXT_stencil_two_side");
    v17 = 0;
  }
  glConfig.twoSidedStencilAvailable = v17;
  if ( v17 )
  {
    qglActiveStencilFaceEXT = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glActiveStencilFaceEXT");
  }
  else
  {
    if ( strstr(glConfig.extensions_string, "GL_ATI_separate_stencil") )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "...using %s\n",
        "GL_ATI_separate_stencil");
      v18 = 1;
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "X..%s not found\n",
        "GL_ATI_separate_stencil");
      v18 = 0;
    }
    glConfig.atiTwoSidedStencilAvailable = v18;
    if ( v18 )
    {
      qglStencilFuncSeparateATI = (void (__stdcall *)(unsigned int, unsigned int, int, unsigned int))GLimp_ExtensionPointer("glStencilFuncSeparateATI");
      qglStencilOpSeparateATI = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glStencilOpSeparateATI");
    }
  }
  if ( strstr(glConfig.extensions_string, "GL_ATI_fragment_shader") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_ATI_fragment_shader");
    v19 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_ATI_fragment_shader");
    v19 = 0;
  }
  glConfig.atiFragmentShaderAvailable = v19;
  if ( v19
    || (strstr(glConfig.extensions_string, "GL_ATI_text_fragment_shader")
      ? ((*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
           common.type,
           "...using %s\n",
           "GL_ATI_text_fragment_shader"),
         v20 = 1)
      : ((*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
           common.type,
           "X..%s not found\n",
           "GL_ATI_text_fragment_shader"),
         v20 = 0),
        glConfig.atiFragmentShaderAvailable = v20) )
  {
    qglGenFragmentShadersATI = (unsigned int (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glGenFragmentShadersATI");
    qglBindFragmentShaderATI = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glBindFragmentShaderATI");
    qglDeleteFragmentShaderATI = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glDeleteFragmentShaderATI");
    qglBeginFragmentShaderATI = GLimp_ExtensionPointer("glBeginFragmentShaderATI");
    qglEndFragmentShaderATI = GLimp_ExtensionPointer("glEndFragmentShaderATI");
    qglPassTexCoordATI = (void (__stdcall *)(unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glPassTexCoordATI");
    qglSampleMapATI = (void (__stdcall *)(unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glSampleMapATI");
    qglColorFragmentOp1ATI = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glColorFragmentOp1ATI");
    qglColorFragmentOp2ATI = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glColorFragmentOp2ATI");
    qglColorFragmentOp3ATI = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glColorFragmentOp3ATI");
    qglAlphaFragmentOp1ATI = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glAlphaFragmentOp1ATI");
    qglAlphaFragmentOp2ATI = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glAlphaFragmentOp2ATI");
    qglAlphaFragmentOp3ATI = (void (__stdcall *)(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int))GLimp_ExtensionPointer("glAlphaFragmentOp3ATI");
    qglSetFragmentShaderConstantATI = (void (__stdcall *)(unsigned int, const float *))GLimp_ExtensionPointer(
                                                                                         "glSetFragmentShaderConstantATI");
  }
  if ( strstr(glConfig.extensions_string, "GL_ARB_vertex_buffer_object") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_ARB_vertex_buffer_object");
    v21 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_ARB_vertex_buffer_object");
    v21 = 0;
  }
  glConfig.ARBVertexBufferObjectAvailable = v21;
  if ( v21 )
  {
    qglBindBufferARB = (void (__stdcall *)(unsigned int, unsigned int))GLimp_ExtensionPointer("glBindBufferARB");
    qglDeleteBuffersARB = (void (__stdcall *)(int, const unsigned int *))GLimp_ExtensionPointer("glDeleteBuffersARB");
    qglGenBuffersARB = (void (__stdcall *)(int, unsigned int *))GLimp_ExtensionPointer("glGenBuffersARB");
    qglIsBufferARB = (unsigned __int8 (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glIsBufferARB");
    qglBufferDataARB = (void (__stdcall *)(unsigned int, int, const void *, unsigned int))GLimp_ExtensionPointer("glBufferDataARB");
    qglBufferSubDataARB = (void (__stdcall *)(unsigned int, int, int, const void *))GLimp_ExtensionPointer("glBufferSubDataARB");
    qglGetBufferSubDataARB = (void (__stdcall *)(unsigned int, int, int, void *))GLimp_ExtensionPointer("glGetBufferSubDataARB");
    qglMapBufferARB = (void *(__stdcall *)(unsigned int, unsigned int))GLimp_ExtensionPointer("glMapBufferARB");
    qglUnmapBufferARB = (unsigned __int8 (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glUnmapBufferARB");
    qglGetBufferParameterivARB = (void (__stdcall *)(unsigned int, unsigned int, int *))GLimp_ExtensionPointer("glGetBufferParameterivARB");
    qglGetBufferPointervARB = (void (__stdcall *)(unsigned int, unsigned int, void **))GLimp_ExtensionPointer("glGetBufferPointervARB");
  }
  if ( strstr(glConfig.extensions_string, "GL_ARB_vertex_program") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "GL_ARB_vertex_program");
    v22 = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "GL_ARB_vertex_program");
    v22 = 0;
  }
  glConfig.ARBVertexProgramAvailable = v22;
  if ( v22 )
  {
    qglVertexAttribPointerARB = (void (__stdcall *)(unsigned int, int, unsigned int, unsigned __int8, int, const void *))GLimp_ExtensionPointer("glVertexAttribPointerARB");
    qglEnableVertexAttribArrayARB = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glEnableVertexAttribArrayARB");
    qglDisableVertexAttribArrayARB = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glDisableVertexAttribArrayARB");
    qglProgramStringARB = (void (__stdcall *)(unsigned int, unsigned int, int, const void *))GLimp_ExtensionPointer("glProgramStringARB");
    qglBindProgramARB = (void (__stdcall *)(unsigned int, unsigned int))GLimp_ExtensionPointer("glBindProgramARB");
    qglGenProgramsARB = (void (__stdcall *)(int, unsigned int *))GLimp_ExtensionPointer("glGenProgramsARB");
    qglProgramEnvParameter4fvARB = (void (__stdcall *)(unsigned int, unsigned int, const float *))GLimp_ExtensionPointer("glProgramEnvParameter4fvARB");
    qglProgramLocalParameter4fvARB = (void (__stdcall *)(unsigned int, unsigned int, const float *))GLimp_ExtensionPointer("glProgramLocalParameter4fvARB");
  }
  if ( r_inhibitFragmentProgram.internalVar->integerValue )
  {
    glConfig.ARBFragmentProgramAvailable = 0;
  }
  else
  {
    if ( strstr(glConfig.extensions_string, "GL_ARB_fragment_program") )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "...using %s\n",
        "GL_ARB_fragment_program");
      v23 = 1;
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "X..%s not found\n",
        "GL_ARB_fragment_program");
      v23 = 0;
    }
    glConfig.ARBFragmentProgramAvailable = v23;
    if ( v23 )
    {
      qglProgramStringARB = (void (__stdcall *)(unsigned int, unsigned int, int, const void *))GLimp_ExtensionPointer("glProgramStringARB");
      qglBindProgramARB = (void (__stdcall *)(unsigned int, unsigned int))GLimp_ExtensionPointer("glBindProgramARB");
      qglProgramEnvParameter4fvARB = (void (__stdcall *)(unsigned int, unsigned int, const float *))GLimp_ExtensionPointer("glProgramEnvParameter4fvARB");
      qglProgramLocalParameter4fvARB = (void (__stdcall *)(unsigned int, unsigned int, const float *))GLimp_ExtensionPointer("glProgramLocalParameter4fvARB");
    }
  }
  if ( !r_inhibitFragmentProgram.internalVar->integerValue
    && !cvarSystem->GetCVarBool(cvarSystem, "net_serverDedicated")
    && R_CheckExtension("GL_ARB_shader_objects")
    && R_CheckExtension("GL_ARB_fragment_shader")
    && R_CheckExtension("GL_ARB_vertex_shader")
    && R_CheckExtension("GL_ARB_shading_language_100") )
  {
    glConfig.GLSLProgramAvailable = 1;
    qglCreateShaderObjectARB = (unsigned int (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glCreateShaderObjectARB");
    qglDeleteObjectARB = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glDeleteObjectARB");
    qglShaderSourceARB = (void (__stdcall *)(unsigned int, int, const char **, const int *))GLimp_ExtensionPointer("glShaderSourceARB");
    qglCompileShaderARB = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glCompileShaderARB");
    qglGetObjectParameterivARB = (void (__stdcall *)(unsigned int, unsigned int, int *))GLimp_ExtensionPointer("glGetObjectParameterivARB");
    qglCreateProgramObjectARB = (unsigned int (__stdcall *)())GLimp_ExtensionPointer("glCreateProgramObjectARB");
    qglAttachObjectARB = (void (__stdcall *)(unsigned int, unsigned int))GLimp_ExtensionPointer("glAttachObjectARB");
    qglDetachObjectARB = (void (__stdcall *)(unsigned int, unsigned int))GLimp_ExtensionPointer("glDetachObjectARB");
    qglLinkProgramARB = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glLinkProgramARB");
    qglUseProgramObjectARB = (void (__stdcall *)(unsigned int))GLimp_ExtensionPointer("glUseProgramObjectARB");
    qglGetUniformLocationARB = (int (__stdcall *)(unsigned int, const char *))GLimp_ExtensionPointer("glGetUniformLocationARB");
    qglUniform1fARB = (void (__stdcall *)(int, float))GLimp_ExtensionPointer("glUniform1fARB");
    qglUniform1iARB = (void (__stdcall *)(int, int))GLimp_ExtensionPointer("glUniform1iARB");
    qglUniform1fvARB = (void (__stdcall *)(int, int, const float *))GLimp_ExtensionPointer("glUniform1fvARB");
    qglUniform2fvARB = (void (__stdcall *)(int, int, const float *))GLimp_ExtensionPointer("glUniform2fvARB");
    qglUniform3fvARB = (void (__stdcall *)(int, int, const float *))GLimp_ExtensionPointer("glUniform3fvARB");
    qglUniform4fvARB = (void (__stdcall *)(int, int, const float *))GLimp_ExtensionPointer("glUniform4fvARB");
    qglGetInfoLogARB = (void (__stdcall *)(unsigned int, int, int *, char *))GLimp_ExtensionPointer("glGetInfoLogARB");
  }
  else
  {
    glConfig.GLSLProgramAvailable = 0;
  }
  if ( !glConfig.multitextureAvailable
    || !glConfig.textureEnvCombineAvailable
    || !glConfig.cubeMapAvailable
    || !glConfig.envDot3Available )
  {
    v24 = *(_DWORD *)common.type;
    v25 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_106780",
            -1);
    (*(void (__cdecl **)(netadrtype_t, int))(v24 + 152))(common.type, v25);
  }
  if ( strstr(glConfig.extensions_string, "EXT_depth_bounds_test") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...using %s\n",
      "EXT_depth_bounds_test");
    LOBYTE(v26) = 1;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "X..%s not found\n",
      "EXT_depth_bounds_test");
    LOBYTE(v26) = 0;
  }
  glConfig.depthBoundsTestAvailable = (char)v26;
  if ( (_BYTE)v26 )
  {
    v26 = (void (__stdcall *)(long double, long double))GLimp_ExtensionPointer("glDepthBoundsEXT");
    qglDepthBoundsEXT = v26;
  }
  return (char)v26;
}

// FUNC: void __cdecl GL_CheckErrors(void)
void __cdecl GL_CheckErrors()
{
  int i; // esi
  unsigned int Error; // eax
  char s[64]; // [esp+4h] [ebp-40h] BYREF

  for ( i = 0; i < 10; ++i )
  {
    Error = qglGetError();
    if ( !Error )
      break;
    switch ( Error )
    {
      case 0x500u:
        strcpy(s, "GL_INVALID_ENUM");
        break;
      case 0x501u:
        strcpy(s, "GL_INVALID_VALUE");
        break;
      case 0x502u:
        strcpy(s, "GL_INVALID_OPERATION");
        break;
      case 0x503u:
        strcpy(s, "GL_STACK_OVERFLOW");
        break;
      case 0x504u:
        strcpy(s, "GL_STACK_UNDERFLOW");
        break;
      case 0x505u:
        strcpy(s, "GL_OUT_OF_MEMORY");
        break;
      default:
        idStr::snPrintf(s, 64, "%i", Error);
        break;
    }
    if ( !r_ignoreGLErrors.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "GL_CheckErrors: %s\n",
        s);
  }
}

// FUNC: R_ReloadMaterials_f
void __cdecl R_ReloadMaterials_f()
{
  int v0; // ebx
  int v1; // eax
  void *v2; // esp
  int i; // esi
  int v4; // esi
  int v5; // ecx
  int v6; // ebx
  int v7; // eax
  int v8; // ecx
  _DWORD v9[3]; // [esp+0h] [ebp-10h]
  int count; // [esp+Ch] [ebp-4h]

  fileSystem->SetIsFileLoadingAllowed(fileSystem, 1);
  v0 = declManager->GetNumDecls(declManager, DECL_MATERIAL);
  v1 = 4 * v0 + 3;
  LOBYTE(v1) = v1 & 0xFC;
  count = v0;
  v2 = alloca(v1);
  for ( i = 0; i < v0; ++i )
    v9[i] = declManager->DeclByIndex(declManager, 1, i, 0);
  v4 = 0;
  if ( v0 > 0 )
  {
    do
    {
      v5 = *(_DWORD *)(v9[v4] + 4);
      v6 = *(_DWORD *)common.type;
      v7 = (*(int (__thiscall **)(int))(*(_DWORD *)v5 + 4))(v5);
      (*(void (**)(netadrtype_t, const char *, ...))(v6 + 124))(common.type, "Reloading %s\n", v7);
      v8 = *(_DWORD *)(v9[v4] + 4);
      (*(void (__thiscall **)(int))(*(_DWORD *)v8 + 28))(v8);
      idMaterial::ReloadImages((idMaterial *)v9[v4++], 0);
    }
    while ( v4 < count );
  }
  fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
}

// FUNC: R_ReloadSurface_f
void __cdecl R_ReloadSurface_f()
{
  double x; // st7
  double y; // st6
  double v2; // st7
  double v3; // st6
  int v4; // esi
  const char *v5; // eax
  float v6; // [esp+0h] [ebp-50h]
  float v7; // [esp+4h] [ebp-4Ch]
  float v8; // [esp+8h] [ebp-48h]
  idVec3 end; // [esp+Ch] [ebp-44h] BYREF
  idVec3 start; // [esp+18h] [ebp-38h] BYREF
  modelTrace_s mt; // [esp+24h] [ebp-2Ch] BYREF

  x = tr.primaryView->renderView.viewaxis.mat[0].x;
  y = tr.primaryView->renderView.viewaxis.mat[0].y;
  start.z = tr.primaryView->renderView.viewaxis.mat[0].z * 16.0;
  v6 = x * 16.0 + tr.primaryView->renderView.vieworg.x;
  v7 = y * 16.0 + tr.primaryView->renderView.vieworg.y;
  v2 = start.z + tr.primaryView->renderView.vieworg.z;
  start.x = v6;
  start.y = v7;
  start.z = v2;
  v3 = tr.primaryView->renderView.viewaxis.mat[0].x * 1000.0;
  end.y = tr.primaryView->renderView.viewaxis.mat[0].y * 1000.0;
  end.z = tr.primaryView->renderView.viewaxis.mat[0].z * 1000.0;
  v8 = end.z + v2;
  end.z = v8;
  end.x = v3 + v6;
  end.y = end.y + v7;
  if ( ((unsigned __int8 (__thiscall *)(idRenderWorldLocal *, modelTrace_s *, idVec3 *, idVec3 *, _DWORD, _DWORD, _DWORD))tr.primaryWorld->Trace)(
         tr.primaryWorld,
         &mt,
         &start,
         &end,
         0,
         0,
         0) )
  {
    fileSystem->SetIsFileLoadingAllowed(fileSystem, 1);
    v4 = *(_DWORD *)common.type;
    v5 = mt.material->base->GetName(mt.material->base);
    (*(void (**)(netadrtype_t, const char *, ...))(v4 + 124))(common.type, "Reloading %s\n", v5);
    mt.material->base->Reload(mt.material->base);
    idMaterial::ReloadImages((idMaterial *)mt.material, 0);
    fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
  }
}

// FUNC: void __cdecl R_TestImage_f(class idCmdArgs const &)
void __cdecl R_TestImage_f(const idCmdArgs *args)
{
  const char *v1; // esi
  int v2; // esi
  const char *v3; // esi

  if ( tr.testVideo )
  {
    ((void (__thiscall *)(idCinematic *, int))tr.testVideo->~idCinematic)(tr.testVideo, 1);
    tr.testVideo = 0;
  }
  tr.testImage = 0;
  if ( args->argc == 2 )
  {
    if ( idStr::IsNumeric(args->argv[1]) )
    {
      if ( args->argc <= 1 )
        v1 = &entityFilter;
      else
        v1 = args->argv[1];
      v2 = atoi(v1);
      if ( v2 >= 0 && v2 < globalImages->GetNumImages(globalImages) )
        tr.testImage = globalImages->GetImageByIndex(globalImages, v2);
    }
    else
    {
      if ( args->argc <= 1 )
        v3 = &entityFilter;
      else
        v3 = args->argv[1];
      tr.testImage = globalImages->ImageFromFile(globalImages, v3, 2, 0, 0, 2, 0, 0);
    }
  }
}

// FUNC: void __cdecl R_TestStandaloneVideo_f(class idCmdArgs const &)
void __cdecl R_TestStandaloneVideo_f(const idCmdArgs *args)
{
  idCinematic *v1; // eax

  if ( tr.testStandaloneVideo )
  {
    ((void (__thiscall *)(idCinematic *, int))tr.testStandaloneVideo->~idCinematic)(tr.testStandaloneVideo, 1);
    tr.testVideo = 0;
  }
  if ( args->argc >= 2 )
  {
    v1 = idCinematic::Alloc();
    tr.testStandaloneVideo = v1;
    if ( v1 )
    {
      if ( args->argc <= 1 )
        v1->InitFromFile(v1, &entityFilter, 1, 1);
      else
        v1->InitFromFile(v1, args->argv[1], 1, 1);
    }
  }
}

// FUNC: void __cdecl R_ReportSurfaceAreas_f(class idCmdArgs const &)
void __cdecl R_ReportSurfaceAreas_f()
{
  int v0; // ebx
  int v1; // eax
  void *v2; // esp
  int i; // esi
  int j; // esi
  int v5; // eax
  int v6; // ecx
  const char *v7; // eax
  int v8; // eax
  int v9; // ecx
  const char *v10; // eax
  float *v11; // eax
  int v12; // ecx
  float v13; // edx
  int v14; // eax
  idFile_vtbl *v15; // ebx
  int v16; // eax
  int v17; // [esp+28h] [ebp-20h]
  int v18; // [esp+28h] [ebp-20h]
  _DWORD v19[3]; // [esp+2Ch] [ebp-1Ch] BYREF
  int count; // [esp+38h] [ebp-10h]
  float v21; // [esp+3Ch] [ebp-Ch]
  int v22; // [esp+40h] [ebp-8h]
  idFile *f; // [esp+44h] [ebp-4h]

  f = fileSystem->OpenFileWrite(fileSystem, "maps/MaterialSurfaceArea.txt", "fs_savepath", 0);
  if ( f )
  {
    v0 = declManager->GetNumDecls(declManager, DECL_MATERIAL);
    v1 = 4 * v0 + 3;
    LOBYTE(v1) = v1 & 0xFC;
    count = v0;
    v2 = alloca(v1);
    for ( i = 0; i < v0; ++i )
      v19[i] = declManager->DeclByIndex(declManager, 1, i, 0);
    qsort(v19, v0, 4u, (int (__cdecl *)(const void *, const void *))R_QsortSurfaceAreas);
    for ( j = 0; j < v0; ++j )
    {
      v5 = 0;
      do
        ++v5;
      while ( aGfxEffects[v5] );
      v6 = *(_DWORD *)(v19[j] + 4);
      v17 = v5;
      v7 = (const char *)(*(int (__thiscall **)(int))(*(_DWORD *)v6 + 4))(v6);
      if ( idStr::Icmpn(v7, "gfx/effects", v17) )
      {
        v8 = 0;
        do
          ++v8;
        while ( aGfxGuis_0[v8] );
        v9 = *(_DWORD *)(v19[j] + 4);
        v18 = v8;
        v10 = (const char *)(*(int (__thiscall **)(int))(*(_DWORD *)v9 + 4))(v9);
        if ( idStr::Icmpn(v10, "gfx/guis", v18) )
        {
          v11 = (float *)v19[j];
          v12 = *((_DWORD *)v11 + 34);
          v13 = v11[70];
          v14 = *((_DWORD *)v11 + 1);
          v22 = v12;
          v15 = f->__vftable;
          v21 = v13;
          v16 = (*(int (__thiscall **)(int))(*(_DWORD *)v14 + 4))(v14);
          v15->Printf(f, "%8.2f %8d %s\n", v21 * 0.00390625, v22, v16);
          v0 = count;
        }
      }
    }
    fileSystem->CloseFile(fileSystem, f);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Dumped cumulative surface areas to maps/MaterialSurfaceArea.txt\n");
  }
}

// FUNC: void __cdecl R_ReportImageDuplication_f(class idCmdArgs const &)
void __cdecl R_ReportImageDuplication_f()
{
  int v0; // edi
  idImage *v1; // eax
  idImage *v2; // ebp
  int v3; // esi
  idImage *v4; // eax
  idImage *v5; // ebx
  int v6; // esi
  int v7; // eax
  int i; // [esp+Ch] [ebp-24h]
  int count; // [esp+10h] [ebp-20h]
  unsigned __int8 *data2; // [esp+14h] [ebp-1Ch] BYREF
  int j; // [esp+18h] [ebp-18h]
  unsigned __int8 *data1; // [esp+1Ch] [ebp-14h] BYREF
  int w1; // [esp+20h] [ebp-10h] BYREF
  int w2; // [esp+24h] [ebp-Ch] BYREF
  int h1; // [esp+28h] [ebp-8h] BYREF
  int h2; // [esp+2Ch] [ebp-4h] BYREF

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Images with duplicated contents:\n");
  v0 = 0;
  count = 0;
  i = 0;
  if ( globalImages->GetNumImages(globalImages) <= 0 )
    goto LABEL_25;
  do
  {
    v1 = globalImages->GetImageByIndex(globalImages, v0);
    v2 = v1;
    if ( v1->isPartialImage || v1->generatorFunction || v1->cubeFiles || v1->defaulted )
      goto LABEL_24;
    R_LoadImageProgram(v1->imgName.data, &data1, &w1, &h1, 0, 0);
    v3 = 0;
    j = 0;
    if ( v0 <= 0 )
      goto LABEL_23;
    while ( 1 )
    {
      v4 = globalImages->GetImageByIndex(globalImages, v3);
      v5 = v4;
      if ( v4->isPartialImage
        || v4->generatorFunction
        || v4->cubeFiles
        || v4->defaulted
        || v2->imageHash != v4->imageHash
        || v4->uploadWidth != v2->uploadWidth
        || v4->uploadHeight != v2->uploadHeight
        || !idStr::Icmp(v2->imgName.data, v4->imgName.data) )
      {
        goto LABEL_20;
      }
      R_LoadImageProgram(v5->imgName.data, &data2, &w2, &h2, 0, 0);
      if ( w2 != w1 || h2 != h1 )
      {
        R_StaticFree(data2);
        goto LABEL_20;
      }
      if ( !memcmp(data1, data2, 4 * h1 * w1) )
        break;
      R_StaticFree(data2);
      v0 = i;
      v3 = j;
LABEL_20:
      j = ++v3;
      if ( v3 >= v0 )
        goto LABEL_23;
    }
    R_StaticFree(data2);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%s == %s\n",
      v2->imgName.data,
      v5->imgName.data);
    session->UpdateScreen(session, 1);
    ++count;
    v0 = i;
LABEL_23:
    R_StaticFree(data1);
LABEL_24:
    i = ++v0;
  }
  while ( v0 < globalImages->GetNumImages(globalImages) );
LABEL_25:
  v6 = *(_DWORD *)common.type;
  v7 = globalImages->GetNumImages(globalImages);
  (*(void (**)(netadrtype_t, const char *, ...))(v6 + 124))(common.type, "%i / %i collisions\n", count, v7);
}

// FUNC: void __cdecl R_ReadTiledPixels(int,int,unsigned char *,struct renderView_s *)
void __cdecl R_ReadTiledPixels(int width, int height, unsigned __int8 *buffer, renderView_s *ref)
{
  unsigned __int8 *v4; // eax
  int v5; // edi
  int vidWidth; // esi
  int vidHeight; // ebx
  int v8; // eax
  int v9; // ecx
  int v10; // ebp
  int v11; // eax
  unsigned int v12; // esi
  unsigned __int8 *v13; // ebx
  int v14; // edx
  unsigned __int8 *v15; // edi
  int v16; // [esp+10h] [ebp-44h]
  int v17; // [esp+14h] [ebp-40h]
  unsigned __int8 *v18; // [esp+18h] [ebp-3Ch]
  unsigned __int8 *temp; // [esp+20h] [ebp-34h]
  int yo; // [esp+24h] [ebp-30h]
  int yoa; // [esp+24h] [ebp-30h]
  int oldWidth; // [esp+28h] [ebp-2Ch]
  int xo; // [esp+2Ch] [ebp-28h]
  int v25; // [esp+30h] [ebp-24h]
  int v26; // [esp+38h] [ebp-1Ch]
  int oldHeight; // [esp+3Ch] [ebp-18h]
  int v28; // [esp+40h] [ebp-14h]
  int v29; // [esp+44h] [ebp-10h]
  int v30; // [esp+48h] [ebp-Ch]
  int v31; // [esp+4Ch] [ebp-8h]
  int v32; // [esp+50h] [ebp-4h]

  v4 = (unsigned __int8 *)R_StaticAlloc(3 * glConfig.vidHeight * (glConfig.vidWidth + 3));
  v5 = width;
  vidWidth = glConfig.vidWidth;
  vidHeight = glConfig.vidHeight;
  tr.tiledViewport[1] = height;
  tr.tiledViewport[0] = width;
  temp = v4;
  oldWidth = glConfig.vidWidth;
  oldHeight = glConfig.vidHeight;
  r_useScissor.internalVar->InternalSetBool(r_useScissor.internalVar, 0);
  v8 = 0;
  xo = 0;
  if ( width > 0 )
  {
    v32 = 3 * vidWidth;
    v9 = -vidWidth;
    v17 = 0;
    v31 = -vidWidth;
    do
    {
      yo = 0;
      if ( height > 0 )
      {
        v25 = vidWidth + v8;
        v29 = -vidHeight;
        v16 = 0;
        v30 = 3 * v5 * vidHeight;
        v18 = buffer;
        do
        {
          tr.viewportOffset[0] = v17;
          tr.viewportOffset[1] = v16;
          if ( ref )
          {
            idRenderSystemLocal::BeginFrame(&tr, vidWidth, vidHeight);
            tr.primaryWorld->RenderScene(tr.primaryWorld, ref, 0);
            idRenderSystemLocal::EndFrame(&tr, 0, 0, 0, 0);
          }
          else
          {
            session->UpdateScreen(session, 1);
          }
          if ( v25 > v5 )
            vidWidth = v17 + v5;
          v10 = vidHeight;
          v28 = yo + vidHeight;
          if ( yo + vidHeight > height )
            v10 = v16 + height;
          qglReadBuffer(0x404u);
          qglReadPixels(0, 0, vidWidth, v10, 0x1907u, 0x1401u, temp);
          v11 = 3 * vidWidth;
          v12 = (3 * vidWidth + 3) & 0xFFFFFFFC;
          yoa = v11;
          if ( v10 > 0 )
          {
            v13 = temp;
            v14 = 3 * v5;
            v15 = v18;
            v26 = v14;
            while ( 1 )
            {
              SIMDProcessor->Memcpy(SIMDProcessor, v15, v13, v11);
              v15 += v26;
              v13 += v12;
              if ( !--v10 )
                break;
              v11 = yoa;
            }
            v5 = width;
            vidHeight = oldHeight;
          }
          v16 += v29;
          v18 += v30;
          vidWidth = oldWidth;
          yo = v28;
        }
        while ( v28 < height );
        v9 = v31;
        v8 = xo;
      }
      buffer += v32;
      v17 += v9;
      v8 += vidWidth;
      xo = v8;
    }
    while ( v8 < v5 );
  }
  r_useScissor.internalVar->InternalSetBool(r_useScissor.internalVar, 1);
  tr.viewportOffset[0] = 0;
  tr.viewportOffset[1] = 0;
  tr.tiledViewport[0] = 0;
  tr.tiledViewport[1] = 0;
  R_StaticFree(temp);
  glConfig.vidWidth = vidWidth;
  glConfig.vidHeight = vidHeight;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::TakeJPGScreenshot(int,int,char const *,int,struct renderView_s *,char const *)
void __thiscall idRenderSystemLocal::TakeJPGScreenshot(
        idRenderSystemLocal *this,
        int width,
        int height,
        const char *fileName,
        int blends,
        renderView_s *ref,
        const char *basePath)
{
  unsigned int v7; // ebx
  int v8; // edi
  int v9; // esi
  unsigned __int8 *v10; // ebp
  int v11; // edi
  unsigned __int16 *v12; // ebx
  int i; // eax
  int j; // ecx
  int v15; // eax
  int v16; // edi
  unsigned __int8 *v17; // esi
  jpeg_destination_mgr *dest; // eax
  unsigned int next_scanline; // eax
  unsigned int image_height; // ecx
  int k; // ebx
  int v22; // [esp+10h] [ebp-1E8h]
  unsigned __int8 *row_pointer[1]; // [esp+14h] [ebp-1E4h] BYREF
  int v24; // [esp+18h] [ebp-1E0h]
  jpeg_compress_struct cinfo; // [esp+1Ch] [ebp-1DCh] BYREF
  jpeg_error_mgr jerr; // [esp+174h] [ebp-84h] BYREF

  v7 = width;
  v8 = height * width;
  v9 = 3 * height * width;
  v24 = height * width;
  v10 = (unsigned __int8 *)R_StaticAlloc(v9);
  if ( blends > 1 )
  {
    v11 = 6 * v8;
    v12 = (unsigned __int16 *)R_StaticAlloc(v11);
    memset(v12, 0, v11);
    r_jitter.internalVar->InternalSetBool(r_jitter.internalVar, 1);
    v22 = blends;
    do
    {
      R_ReadTiledPixels(width, height, v10, ref);
      for ( i = 0; i < v9; ++i )
        v12[i] += v10[i];
      --v22;
    }
    while ( v22 );
    for ( j = 0; j < v9; v10[j - 1] = v15 )
      v15 = v12[j++] / blends;
    R_StaticFree(v12);
    r_jitter.internalVar->InternalSetBool(r_jitter.internalVar, 0);
    v7 = width;
    v8 = v24;
  }
  else
  {
    R_ReadTiledPixels(width, height, v10, ref);
  }
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  v16 = 3 * v8;
  v17 = (unsigned __int8 *)R_StaticAlloc(v16);
  dest = cinfo.dest;
  if ( !cinfo.dest )
  {
    dest = (jpeg_destination_mgr *)cinfo.mem->alloc_small((jpeg_common_struct *)&cinfo, 0, 28);
    cinfo.dest = dest;
  }
  dest->init_destination = init_destination;
  dest->empty_output_buffer = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *))empty_output_buffer;
  dest->term_destination = term_destination;
  dest[1].next_output_byte = v17;
  dest[1].free_in_buffer = v16;
  cinfo.image_width = v7;
  cinfo.image_height = height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 95, 1u);
  jpeg_start_compress(&cinfo, 1u);
  next_scanline = cinfo.next_scanline;
  image_height = cinfo.image_height;
  for ( k = 3 * v7; cinfo.next_scanline < cinfo.image_height; image_height = cinfo.image_height )
  {
    row_pointer[0] = &v10[k * (image_height - next_scanline - 1)];
    jpeg_write_scanlines(&cinfo, row_pointer, 1u);
    next_scanline = cinfo.next_scanline;
  }
  jpeg_finish_compress(&cinfo);
  fileSystem->WriteFile(fileSystem, fileName, v17, hackSize, basePath);
  R_StaticFree(v17);
  jpeg_destroy_decompress(&cinfo);
  R_StaticFree(v10);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::TakeScreenshot(int,int,char const *,int,struct renderView_s *,char const *)
void __thiscall idRenderSystemLocal::TakeScreenshot(
        idRenderSystemLocal *this,
        int width,
        int height,
        const char *fileName,
        int blends,
        renderView_s *ref,
        const char *basePath)
{
  int v7; // esi
  idRenderSystemLocal *v8; // ebp
  unsigned __int8 *v9; // ebx
  unsigned __int16 *v10; // ebp
  int v11; // edi
  int i; // eax
  int j; // ecx
  unsigned __int8 v14; // al
  int v15; // esi
  _BYTE *v16; // ecx
  unsigned int v17; // edi
  char v18; // al
  int v19; // [esp+10h] [ebp-8h]

  v7 = height * width;
  v8 = this;
  this->takingScreenshot = 1;
  v9 = (unsigned __int8 *)R_StaticAlloc(3 * height * width + 18);
  *(_DWORD *)v9 = 0;
  *((_DWORD *)v9 + 1) = 0;
  *((_DWORD *)v9 + 2) = 0;
  *((_DWORD *)v9 + 3) = 0;
  *((_WORD *)v9 + 8) = 0;
  if ( blends > 1 )
  {
    v10 = (unsigned __int16 *)R_StaticAlloc(6 * v7);
    memset(v10, 0, 6 * v7);
    r_jitter.internalVar->InternalSetBool(r_jitter.internalVar, 1);
    v11 = 3 * v7;
    v19 = blends;
    do
    {
      R_ReadTiledPixels(width, height, v9 + 18, ref);
      for ( i = 0; i < v11; ++i )
        v10[i] += v9[i + 18];
      --v19;
    }
    while ( v19 );
    for ( j = 0; j < 3 * v7; v9[j + 17] = v14 )
      v14 = v10[j++] / blends;
    R_StaticFree(v10);
    r_jitter.internalVar->InternalSetBool(r_jitter.internalVar, 0);
    v8 = this;
  }
  else
  {
    R_ReadTiledPixels(width, height, v9 + 18, ref);
  }
  *((_WORD *)v9 + 6) = width;
  v9[14] = height;
  v15 = 3 * v7 + 18;
  v9[2] = 2;
  v9[15] = BYTE1(height);
  v9[16] = 24;
  if ( v15 > 18 )
  {
    v16 = v9 + 20;
    v17 = (v15 - 19) / 3u + 1;
    do
    {
      v18 = *(v16 - 2);
      *(v16 - 2) = *v16;
      *v16 = v18;
      v16 += 3;
      --v17;
    }
    while ( v17 );
  }
  fileSystem->WriteFile(fileSystem, fileName, v9, v15, basePath);
  R_StaticFree(v9);
  v8->takingScreenshot = 0;
}

// FUNC: void __cdecl R_ScreenshotFilename(int &,char const *,char const *,class idStr &)
void __cdecl R_ScreenshotFilename(int *lastNumber, const char *base, const char *ext, idStr *fileName)
{
  int v4; // esi
  int v5; // edi
  int v6; // esi
  signed int v7; // ebx
  char *v8; // eax
  bool restrict; // [esp+1Ch] [ebp-4h]

  restrict = cvarSystem->GetCVarBool(cvarSystem, "fs_restrict");
  cvarSystem->SetCVarBool(cvarSystem, "fs_restrict", 0, 0);
  v4 = ++*lastNumber;
  if ( *lastNumber <= 99999 )
  {
    for ( ; *lastNumber < 99999; v4 = ++*lastNumber )
    {
      v5 = v4 / 10000;
      v6 = v4 % 10000;
      v7 = v6
         - 1000
         * (((int)((unsigned __int64)(v6 * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6)
          + ((unsigned int)((unsigned __int64)(v6 * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 31));
      v8 = va(
             "%s%i%i%i%i%i%s",
             base,
             v5,
             ((int)((unsigned __int64)(v6 * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6)
           + ((unsigned int)((unsigned __int64)(v6 * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 31),
             v7 / 100,
             v7 % 100 / 10,
             v7 % 100 % 10,
             ext);
      idStr::operator=(fileName, v8);
      if ( *lastNumber == 99999 )
        break;
      if ( fileSystem->ReadFile(fileSystem, fileName->data, 0, 0) <= 0 )
        break;
    }
  }
  else
  {
    *lastNumber = 99999;
  }
  cvarSystem->SetCVarBool(cvarSystem, "fs_restrict", restrict, 0);
}

// FUNC: void __cdecl R_ScreenShot_f(class idCmdArgs const &)
void __cdecl R_ScreenShot_f(const idCmdArgs *args)
{
  bool v2; // cc
  const char *v3; // eax
  int argc; // eax
  int vidWidth; // ebx
  int vidHeight; // edi
  int v7; // esi
  const char *v8; // eax
  const char *v9; // eax
  const char *v10; // eax
  const char *v11; // eax
  const char *v12; // eax
  int v13; // eax
  const char *v14; // ebp
  idStr checkname; // [esp+10h] [ebp-2Ch] BYREF
  int v16; // [esp+38h] [ebp-4h]
  const char *argsa; // [esp+40h] [ebp+4h]

  checkname.len = 0;
  checkname.alloced = 20;
  checkname.data = checkname.baseBuffer;
  checkname.baseBuffer[0] = 0;
  v2 = args->argc <= 0;
  v16 = 0;
  if ( v2 )
    v3 = &entityFilter;
  else
    v3 = args->argv[0];
  argsa = ".tga";
  if ( idStr::Icmp(v3, "screenShot") )
    argsa = ".jpg";
  argc = args->argc;
  switch ( args->argc )
  {
    case 1:
      vidWidth = glConfig.vidWidth;
      vidHeight = glConfig.vidHeight;
      v7 = 1;
      R_ScreenshotFilename(&lastNumber, "screenshots/shot", argsa, &checkname);
      goto LABEL_32;
    case 2:
      vidWidth = glConfig.vidWidth;
      vidHeight = glConfig.vidHeight;
      v7 = 1;
      if ( argc <= 1 )
        idStr::operator=(&checkname, (char *)&entityFilter);
      else
        idStr::operator=(&checkname, args->argv[1]);
      goto LABEL_32;
    case 3:
      if ( argc <= 1 )
        v8 = &entityFilter;
      else
        v8 = args->argv[1];
      vidWidth = atoi(v8);
      if ( args->argc <= 2 )
        v9 = &entityFilter;
      else
        v9 = args->argv[2];
      vidHeight = atoi(v9);
      v7 = 1;
      R_ScreenshotFilename(&lastNumber, "screenshots/shot", argsa, &checkname);
      goto LABEL_32;
    case 4:
      if ( argc <= 1 )
        v10 = &entityFilter;
      else
        v10 = args->argv[1];
      vidWidth = atoi(v10);
      if ( args->argc <= 2 )
        v11 = &entityFilter;
      else
        v11 = args->argv[2];
      vidHeight = atoi(v11);
      if ( args->argc <= 3 )
        v12 = &entityFilter;
      else
        v12 = args->argv[3];
      v13 = atoi(v12);
      v7 = v13;
      if ( v13 >= 1 )
      {
        if ( v13 > 256 )
          v7 = 256;
      }
      else
      {
        v7 = 1;
      }
      R_ScreenshotFilename(&lastNumber, "screenshots/shot", argsa, &checkname);
LABEL_32:
      console->Close(console);
      if ( args->argc <= 0 )
        v14 = &entityFilter;
      else
        v14 = args->argv[0];
      if ( idStr::Icmp(v14, "screenShot") )
        idRenderSystemLocal::TakeJPGScreenshot(&tr, vidWidth, vidHeight, checkname.data, v7, 0, "fs_savepath");
      else
        idRenderSystemLocal::TakeScreenshot(&tr, vidWidth, vidHeight, checkname.data, v7, 0, "fs_savepath");
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Wrote %s\n",
        checkname.data);
      break;
    default:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "usage: screenshot\n"
        "       screenshot <filename>\n"
        "       screenshot <width> <height>\n"
        "       screenshot <width> <height> <blends>\n");
      break;
  }
  v16 = -1;
  idStr::FreeData(&checkname);
}

// FUNC: void __cdecl R_SampleCubeMap(class idVec3 const &,int,unsigned char * * const,unsigned char * const)
void __cdecl R_SampleCubeMap(const idVec3 *dir, int size, unsigned __int8 **buffers, unsigned __int8 *result)
{
  int v4; // esi
  double v5; // st7
  double v6; // st7
  double v7; // st7
  int v8; // edi
  int v9; // eax
  int v10; // eax
  float adir; // [esp+8h] [ebp-Ch]
  float adir_4; // [esp+Ch] [ebp-8h]
  float adir_8; // [esp+10h] [ebp-4h]

  adir = fabs(dir->x);
  adir_4 = fabs(dir->y);
  adir_8 = fabs(dir->z);
  if ( dir->x < (double)adir_4 || dir->x < (double)adir_8 )
  {
    v5 = -dir->x;
    if ( v5 < adir_4 || v5 < adir_8 )
    {
      if ( dir->y < (double)adir || dir->y < (double)adir_8 )
      {
        v6 = -dir->y;
        if ( v6 < adir || v6 < adir_8 )
        {
          if ( dir->z < (double)adir_4 || (v4 = 4, dir->z < (double)adir_8) )
            v4 = 5;
        }
        else
        {
          v4 = 3;
        }
      }
      else
      {
        v4 = 2;
      }
    }
    else
    {
      v4 = 1;
    }
  }
  else
  {
    v4 = 0;
  }
  v7 = (double)size;
  v8 = (__int64)((1.0
                - (cubeAxis[v4].mat[1].z * dir->z + cubeAxis[v4].mat[1].y * dir->y + dir->x * cubeAxis[v4].mat[1].x)
                / (cubeAxis[v4].mat[0].z * dir->z + cubeAxis[v4].mat[0].y * dir->y + cubeAxis[v4].mat[0].x * dir->x))
               * v7
               * 0.5);
  v9 = (__int64)((1.0
                - (cubeAxis[v4].mat[2].z * dir->z + cubeAxis[v4].mat[2].y * dir->y + cubeAxis[v4].mat[2].x * dir->x)
                / (cubeAxis[v4].mat[0].z * dir->z + cubeAxis[v4].mat[0].y * dir->y + cubeAxis[v4].mat[0].x * dir->x))
               * v7
               * 0.5);
  if ( v8 >= 0 )
  {
    if ( v8 >= size )
      v8 = size - 1;
  }
  else
  {
    v8 = 0;
  }
  if ( v9 >= 0 )
  {
    if ( v9 >= size )
      v9 = size - 1;
  }
  else
  {
    v9 = 0;
  }
  v10 = 4 * (v8 + size * v9);
  *result = buffers[v4][v10];
  result[1] = buffers[v4][v10 + 1];
  result[2] = buffers[v4][v10 + 2];
  result[3] = buffers[v4][v10 + 3];
}

// FUNC: void __cdecl R_MakeAmbientMap_f(class idCmdArgs const &)
void __cdecl R_MakeAmbientMap_f(const idCmdArgs *args)
{
  int argc; // eax
  bool v2; // zf
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  void *v6; // esp
  char **v7; // edi
  float *p_y; // esi
  unsigned __int8 *v9; // edi
  float v10; // edx
  float v11; // eax
  float v12; // edx
  float v13; // eax
  double v14; // st7
  double v15; // st7
  long double v16; // st6
  long double v17; // rt0
  int k; // edi
  int v19; // ebx
  int i; // esi
  long double v21; // st7
  long double v22; // st7
  double v23; // st7
  unsigned __int64 v24; // rax
  double v25; // st7
  char *v26; // eax
  int j; // esi
  int v28; // [esp+0h] [ebp-7Ch] BYREF
  unsigned __int8 *buffers[6]; // [esp+Ch] [ebp-70h] BYREF
  float v30; // [esp+24h] [ebp-58h]
  char *extensions[6]; // [esp+30h] [ebp-4Ch] BYREF
  double v32; // [esp+48h] [ebp-34h]
  idStr fullname; // [esp+50h] [ebp-2Ch] BYREF
  int height; // [esp+70h] [ebp-Ch] BYREF
  float v35; // [esp+74h] [ebp-8h]
  float v36; // [esp+78h] [ebp-4h]
  float v37; // [esp+7Ch] [ebp+0h]
  float v38; // [esp+80h] [ebp+4h]
  float v39; // [esp+84h] [ebp+8h]
  float v40; // [esp+88h] [ebp+Ch]
  int width; // [esp+8Ch] [ebp+10h] BYREF
  char **v42; // [esp+90h] [ebp+14h]
  unsigned __int8 result[4]; // [esp+94h] [ebp+18h] BYREF
  idVec3 dir; // [esp+98h] [ebp+1Ch]
  unsigned __int8 *outBuffer; // [esp+A4h] [ebp+28h]
  int x; // [esp+A8h] [ebp+2Ch]
  float total[3]; // [esp+ACh] [ebp+30h] BYREF
  int y; // [esp+B8h] [ebp+3Ch]
  float v49; // [esp+BCh] [ebp+40h]
  int map; // [esp+C0h] [ebp+44h]
  const char *baseName; // [esp+C4h] [ebp+48h]
  idMat3 *v52; // [esp+C8h] [ebp+4Ch]
  idVec3 test; // [esp+CCh] [ebp+50h] BYREF
  unsigned __int8 *v54; // [esp+D8h] [ebp+5Ch]
  float limit; // [esp+DCh] [ebp+60h]
  int v56; // [esp+E0h] [ebp+64h]
  int v57; // [esp+ECh] [ebp+70h]
  int outSize; // [esp+F8h] [ebp+7Ch]

  fullname.len = 0;
  fullname.alloced = 20;
  fullname.data = fullname.baseBuffer;
  fullname.baseBuffer[0] = 0;
  argc = args->argc;
  v2 = args->argc == 2;
  v57 = 0;
  extensions[0] = "_px.tga";
  extensions[1] = "_nx.tga";
  extensions[2] = "_py.tga";
  extensions[3] = "_ny.tga";
  extensions[4] = "_pz.tga";
  extensions[5] = "_nz.tga";
  if ( v2 || argc == 3 )
  {
    if ( argc <= 1 )
      baseName = &entityFilter;
    else
      baseName = args->argv[1];
    if ( argc == 3 )
    {
      v3 = atoi(args->argv[2]);
      outSize = v3;
    }
    else
    {
      outSize = 32;
      v3 = 32;
    }
    memset(cubeAxis, 0, sizeof(cubeAxis));
    cubeAxis[0].mat[0].x = 1.0;
    cubeAxis[0].mat[1].z = 1.0;
    cubeAxis[0].mat[2].y = 1.0;
    cubeAxis[1].mat[0].x = -1.0;
    cubeAxis[1].mat[1].z = -1.0;
    cubeAxis[1].mat[2].y = 1.0;
    cubeAxis[2].mat[0].y = 1.0;
    cubeAxis[2].mat[1].x = -1.0;
    cubeAxis[2].mat[2].z = -1.0;
    cubeAxis[3].mat[0].y = -1.0;
    cubeAxis[3].mat[1].x = -1.0;
    cubeAxis[3].mat[2].z = 1.0;
    cubeAxis[4].mat[0].z = 1.0;
    cubeAxis[4].mat[1].x = -1.0;
    cubeAxis[4].mat[2].y = 1.0;
    cubeAxis[5].mat[0].z = -1.0;
    cubeAxis[5].mat[1].x = 1.0;
    cubeAxis[5].mat[2].y = 1.0;
    width = -1;
    height = -1;
    v4 = 0;
    while ( 1 )
    {
      sprintf(&fullname, "env/%s%s", baseName, extensions[v4]);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "loading %s\n",
        fullname.data);
      session->UpdateScreen(session, 1);
      R_LoadImage(fullname.data, &buffers[v4], &width, &height, 0, 1);
      if ( !buffers[v4] )
        break;
      if ( ++v4 >= 6 )
      {
        v5 = 4 * v3 * v3 + 3;
        LOBYTE(v5) = v5 & 0xFC;
        v6 = alloca(v5);
        outBuffer = (unsigned __int8 *)&v28;
        for ( map = 0; map < 2; ++map )
        {
          v7 = extensions;
          p_y = &cubeAxis[0].mat[0].y;
          v42 = extensions;
          v52 = (idMat3 *)&cubeAxis[0].mat[0].y;
          do
          {
            x = 0;
            if ( v3 > 0 )
            {
              v54 = outBuffer + 2;
              v32 = (double)(v3 - 1);
              do
              {
                v9 = v54;
                y = 0;
                v49 = -(((double)x + (double)x) / v32 - 1.0);
                do
                {
                  v10 = p_y[6];
                  v11 = p_y[7];
                  v38 = p_y[5];
                  v40 = v11;
                  v39 = v10;
                  v12 = p_y[3];
                  v13 = p_y[4];
                  v35 = p_y[2];
                  v36 = v12;
                  v37 = v13;
                  v14 = -(((double)y + (double)y) / v32 - 1.0);
                  *(float *)&v56 = v13 * v49 + p_y[1];
                  limit = v12 * v49 + *p_y;
                  v30 = v35 * v49 + *(p_y - 1);
                  *(float *)&v56 = v40 * v14 + *(float *)&v56;
                  LODWORD(dir.z) = v56;
                  limit = v39 * v14 + limit;
                  dir.y = limit;
                  v15 = v30 + v38 * v14;
                  dir.x = v15;
                  v16 = v15 * v15 + limit * limit + *(float *)&v56 * *(float *)&v56;
                  if ( v16 != 0.0 )
                  {
                    v17 = 1.0 / sqrt(v16);
                    dir.x = v15 * v17;
                    dir.y = limit * v17;
                    dir.z = *(float *)&v56 * v17;
                  }
                  memset(total, 0, sizeof(total));
                  v19 = 0;
                  if ( map )
                    limit = 0.95;
                  else
                    limit = 0.25;
                  while ( 1 )
                  {
                    do
                    {
                      for ( i = 0; i < 3; *((float *)&v52 + i) = (double)v56 * 0.000030518509 - 1.0 )
                      {
                        v56 = 2 * (rand() & 0x7FFF);
                        ++i;
                      }
                      v21 = test.x * test.x + test.z * test.z + test.y * test.y;
                    }
                    while ( sqrt(v21) > 1.0 );
                    if ( v21 != 0.0 )
                    {
                      v22 = 1.0 / sqrt(v21);
                      test.x = test.x * v22;
                      test.y = test.y * v22;
                      test.z = test.z * v22;
                    }
                    if ( test.x * dir.x + test.z * dir.z + test.y * dir.y > limit )
                    {
                      R_SampleCubeMap(&test, width, buffers, result);
                      ++v19;
                      total[0] = (double)result[0] + total[0];
                      v56 = result[2];
                      total[1] = (double)result[1] + total[1];
                      total[2] = (double)result[2] + total[2];
                      if ( v19 >= 1000 )
                        break;
                    }
                  }
                  v23 = total[1] * 0.001;
                  *(v9 - 2) = (unsigned __int64)(total[0] * 0.001);
                  v24 = (unsigned __int64)v23;
                  v25 = total[2] * 0.001;
                  *(v9 - 1) = v24;
                  p_y = (float *)v52;
                  *v9 = (unsigned __int64)v25;
                  LODWORD(v24) = y + 1;
                  v9[1] = -1;
                  v9 += 4 * outSize;
                  y = v24;
                }
                while ( (int)v24 < outSize );
                v54 += 4;
                ++x;
              }
              while ( x < outSize );
              v3 = outSize;
              v7 = v42;
            }
            if ( map )
              v26 = va("env/%s_spec%s", baseName, *v7);
            else
              v26 = va("env/%s_amb%s", baseName, *v7);
            idStr::operator=(&fullname, v26);
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "writing %s\n",
              fullname.data);
            session->UpdateScreen(session, 1);
            R_WriteTGA(fullname.data, outBuffer, v3, v3, 0);
            p_y += 9;
            ++v7;
            v52 = (idMat3 *)p_y;
            v42 = v7;
          }
          while ( (int)p_y < (int)&c_callbackUpdate );
        }
        for ( j = 0; j < 6; ++j )
        {
          if ( buffers[j] )
            Mem_Free(buffers[j]);
        }
        goto LABEL_45;
      }
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "failed.\n");
    for ( k = v4 - 1; k >= 0; --k )
      Mem_Free(buffers[k]);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "USAGE: ambientshot <basename> [size]\n");
  }
LABEL_45:
  v57 = -1;
  idStr::FreeData(&fullname);
}

// FUNC: void __cdecl R_SetColorMappings(void)
void __cdecl R_SetColorMappings()
{
  int v0; // esi
  int v1; // ecx
  int v2; // eax
  int i; // [esp+8h] [ebp-Ch]
  int ia; // [esp+8h] [ebp-Ch]
  float g; // [esp+Ch] [ebp-8h]
  float b; // [esp+10h] [ebp-4h]

  v0 = 0;
  b = r_brightness.internalVar->floatValue;
  g = r_gamma.internalVar->floatValue;
  i = 0;
  do
  {
    ia = (int)((double)i * b);
    v1 = ia;
    if ( ia > 255 )
    {
      v1 = 255;
      ia = 255;
    }
    if ( g == 1.0 )
      v2 = v1 | (v1 << 8);
    else
      v2 = (int)(pow((double)ia * 0.0039215689, 1.0 / g) * 65535.0 + 0.5);
    if ( v2 >= 0 )
    {
      if ( v2 > 0xFFFF )
        LOWORD(v2) = -1;
    }
    else
    {
      LOWORD(v2) = 0;
    }
    tr.gammaTable[v0++] = v2;
    i = v0;
  }
  while ( v0 < 256 );
  GLimp_SetGamma(tr.gammaTable, tr.gammaTable, tr.gammaTable);
}

// FUNC: void __cdecl GfxInfo_f(class idCmdArgs const &)
void __cdecl GfxInfo_f()
{
  int v0; // esi
  const char *ProcessorString; // eax
  int v2; // ecx
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  bool v7; // al
  const char *active[2]; // [esp+0h] [ebp-8h]

  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "\nGL_VENDOR: %s\n",
    glConfig.vendor_string,
    "windowed",
    "fullscreen");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "GL_RENDERER: %s\n",
    glConfig.renderer_string);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "GL_VERSION: %s\n",
    glConfig.version_string);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "GL_EXTENSIONS: %s\n",
    glConfig.extensions_string);
  if ( glConfig.wgl_extensions_string )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "WGL_EXTENSIONS: %s\n",
      glConfig.wgl_extensions_string);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "GL_MAX_TEXTURE_SIZE: %d\n",
    glConfig.maxTextureSize);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "GL_MAX_TEXTURE_UNITS_ARB: %d\n",
    glConfig.maxTextureUnits);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "GL_MAX_TEXTURE_COORDS_ARB: %d\n",
    glConfig.maxTextureCoords);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "GL_MAX_TEXTURE_IMAGE_UNITS_ARB: %d\n",
    glConfig.maxTextureImageUnits);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "\nPIXELFORMAT: color(%d-bits) Z(%d-bit) stencil(%d-bits) alpha(%d-bits)\n",
    glConfig.colorBits,
    glConfig.depthBits,
    glConfig.stencilBits,
    glConfig.alphaBits);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "MODE: %d, %d x %d %s hz:",
    r_mode.internalVar->integerValue,
    glConfig.vidWidth,
    glConfig.vidHeight,
    active[r_fullscreen.internalVar->integerValue != 0]);
  if ( glConfig.displayFrequency )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%d\n",
      glConfig.displayFrequency);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "N/A\n");
  v0 = *(_DWORD *)common.type;
  ProcessorString = Sys_GetProcessorString();
  (*(void (**)(netadrtype_t, const char *, ...))(v0 + 124))(common.type, "CPU: %s\n", ProcessorString);
  v2 = *(_DWORD *)common.type;
  active[0] = &entityFilter;
  active[1] = " (ACTIVE)";
  (*(void (**)(netadrtype_t, const char *, ...))(v2 + 124))(
    common.type,
    "ARB path ENABLED%s\n",
    active[tr.backEndRenderer == BE_ARB]);
  v3 = *(_DWORD *)common.type;
  if ( glConfig.allowNV10Path )
    (*(void (**)(netadrtype_t, const char *, ...))(v3 + 124))(
      common.type,
      "NV10 path ENABLED%s\n",
      active[tr.backEndRenderer == BE_NV10]);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(v3 + 124))(common.type, "NV10 path disabled\n");
  v4 = *(_DWORD *)common.type;
  if ( glConfig.allowNV20Path )
    (*(void (**)(netadrtype_t, const char *, ...))(v4 + 124))(
      common.type,
      "NV20 path ENABLED%s\n",
      active[tr.backEndRenderer == BE_NV20]);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(v4 + 124))(common.type, "NV20 path disabled\n");
  v5 = *(_DWORD *)common.type;
  if ( glConfig.allowR200Path )
    (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(
      common.type,
      "R200 path ENABLED%s\n",
      active[tr.backEndRenderer == BE_R200]);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(v5 + 124))(common.type, "R200 path disabled\n");
  v6 = *(_DWORD *)common.type;
  if ( glConfig.allowARB2Path )
    (*(void (**)(netadrtype_t, const char *, ...))(v6 + 124))(
      common.type,
      "ARB2 path ENABLED%s\n",
      active[tr.backEndRenderer == BE_ARB2]);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(v6 + 124))(common.type, "ARB2 path disabled\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "-------\n");
  if ( r_finish.internalVar->integerValue )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Forcing glFinish\n");
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "glFinish not forced\n");
  if ( r_swapInterval.internalVar->integerValue && wglSwapIntervalEXT )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Forcing swapInterval %i\n",
      r_swapInterval.internalVar->integerValue);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "swapInterval not forced\n");
  v7 = glConfig.twoSidedStencilAvailable || glConfig.atiTwoSidedStencilAvailable;
  if ( !r_useTwoSidedStencil.internalVar->integerValue )
  {
    if ( v7 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "Two sided stencil available but disabled\n");
      goto LABEL_35;
    }
    goto LABEL_33;
  }
  if ( !v7 )
  {
LABEL_33:
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Two sided stencil not available\n");
    goto LABEL_35;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Using two sided stencil\n");
LABEL_35:
  if ( idVertexCache::IsFast(&vertexCache) )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Vertex cache is fast\n");
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Vertex cache is SLOW\n");
}

// FUNC: void __cdecl R_InitMaterials(void)
void __cdecl R_InitMaterials()
{
  const char *v0; // eax
  idToken token; // [esp+2Ch] [ebp-1ECh] BYREF
  idLexer xen_precache; // [esp+7Ch] [ebp-19Ch] BYREF
  idLexer precache; // [esp+144h] [ebp-D4h] BYREF
  int v4; // [esp+214h] [ebp-4h]

  tr.defaultMaterial = declManager->FindMaterial(declManager, "_default", 0);
  if ( !tr.defaultMaterial )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "_default material not found");
  declManager->FindMaterial(declManager, "_default", 0);
  tr.debugGraphMaterial = declManager->FindMaterial(declManager, "textures/common/debuggraph", 0);
  token.floatvalue = 0.0;
  memset(tr.debugGraph, 0, sizeof(tr.debugGraph));
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v4 = 0;
  idLexer::idLexer(&precache, "materials/precache.lst", 6300, 0);
  LOBYTE(v4) = 1;
  while ( idLexer::ReadToken(&precache, &token) )
    declManager->FindMaterial(declManager, token.data, 1);
  v0 = cvarSystem->GetCVarString(cvarSystem, "fs_game");
  if ( !idStr::Icmp(v0, "q4basexenon") )
  {
    idLexer::idLexer(&xen_precache, "materials/xen_precache.lst", 6300, 0);
    LOBYTE(v4) = 2;
    while ( idLexer::ReadToken(&xen_precache, &token) )
      declManager->FindMaterial(declManager, token.data, 1);
    LOBYTE(v4) = 1;
    idLexer::~idLexer(&xen_precache);
  }
  LOBYTE(v4) = 0;
  idLexer::~idLexer(&precache);
  v4 = -1;
  idStr::FreeData(&token);
}

// FUNC: R_SizeUp_f
void __cdecl R_SizeUp_f()
{
  if ( r_screenFraction.internalVar->integerValue + 10 <= 100 )
    ((void (__stdcall *)(int))r_screenFraction.internalVar->InternalSetInteger)(r_screenFraction.internalVar->integerValue + 10);
  else
    r_screenFraction.internalVar->InternalSetInteger(r_screenFraction.internalVar, 100);
}

// FUNC: R_SizeDown_f
void __cdecl R_SizeDown_f()
{
  if ( r_screenFraction.internalVar->integerValue - 10 >= 10 )
    ((void (__stdcall *)(int))r_screenFraction.internalVar->InternalSetInteger)(r_screenFraction.internalVar->integerValue - 10);
  else
    r_screenFraction.internalVar->InternalSetInteger(r_screenFraction.internalVar, 10);
}

// FUNC: void __cdecl R_TouchGui_f(class idCmdArgs const &)
void __cdecl R_TouchGui_f(const idCmdArgs *args)
{
  const char *v1; // esi

  if ( args->argc > 1 && (v1 = args->argv[1], *v1) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "touchGui %s\n", v1);
    session->UpdateScreen(session, 1);
    uiManager->Touch(uiManager, v1);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "USAGE: touchGui <guiName>\n");
  }
}

// FUNC: public: void __thiscall idRenderSystemLocal::Clear(void)
void __thiscall idRenderSystemLocal::Clear(idRenderSystemLocal *this)
{
  idRenderWorldLocal **list; // eax

  this->registered = 0;
  this->frameCount = 0;
  this->viewCount = 0;
  this->staticAllocCount = 0;
  this->frameShaderTime = 0.0;
  this->viewportOffset[0] = 0;
  this->viewportOffset[1] = 0;
  this->tiledViewport[0] = 0;
  this->tiledViewport[1] = 0;
  this->backEndRenderer = BE_BAD;
  this->backEndRendererHasVertexPrograms = 0;
  this->backEndRendererMaxLight = 1.0;
  this->ambientLightVector.w = 0.0;
  this->ambientLightVector.z = 0.0;
  this->ambientLightVector.y = 0.0;
  this->ambientLightVector.x = 0.0;
  this->sortOffset = 0.0;
  list = this->worlds.list;
  if ( list )
    Memory::Free(list);
  this->worlds.list = 0;
  this->worlds.num = 0;
  this->worlds.size = 0;
  this->primaryWorld = 0;
  memset(&this->primaryRenderView, 0, sizeof(this->primaryRenderView));
  this->primaryView = 0;
  this->defaultMaterial = 0;
  this->debugGraphMaterial = 0;
  this->testImage = 0;
  this->viewDef = 0;
  memset(&this->pc, 0, sizeof(this->pc));
  this->lockSurfacesCmd.commandId = RC_NOP;
  this->lockSurfacesCmd.next = 0;
  this->lockSurfacesCmd.viewDef = 0;
  memset(&this->identitySpace, 0, sizeof(this->identitySpace));
  this->stencilIncr = 0;
  this->stencilDecr = 0;
  memset(this->renderCrops, 0, sizeof(this->renderCrops));
  this->currentRenderCrop = 0;
  this->guiRecursionLevel = 0;
  this->guiModel = 0;
  this->demoGuiModel = 0;
  this->guiOverlayModel = 0;
  this->specialEffectsEnabled = 0;
  memset(this->gammaTable, 0, sizeof(this->gammaTable));
  this->takingScreenshot = 0;
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::EndLevelLoad(void)
void __thiscall idRenderSystemLocal::EndLevelLoad(idRenderSystemLocal *this)
{
  renderModelManager->EndLevelLoad(renderModelManager);
  globalImages->EndLevelLoad(globalImages);
  if ( r_forceLoadImages.internalVar->integerValue )
  {
    if ( glConfig.isInitialized )
      RB_ShowImages();
  }
}

// FUNC: void __cdecl R_InitOpenGL(void)
void __cdecl R_InitOpenGL()
{
  int v0; // esi
  int integerValue; // eax
  int v2; // eax
  int v3; // edx
  int height; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // edi
  const char *v8; // eax
  int v9; // ecx
  idCVarSystem_vtbl *v10; // esi
  int v11; // eax
  const char *v12; // esi
  unsigned int v13; // eax
  int v14; // eax
  char *data; // edx
  const char *v16; // ecx
  char v17; // al
  void *v18; // ecx
  glimpParms_t v19; // [esp+24h] [ebp-96Ch]
  bool nv10or20; // [esp+46h] [ebp-94Ah] BYREF
  bool oldCard; // [esp+47h] [ebp-949h] BYREF
  int temp; // [esp+48h] [ebp-948h] BYREF
  idStr videoCard; // [esp+4Ch] [ebp-944h] BYREF
  glimpParms_t parms; // [esp+6Ch] [ebp-924h]
  idCmdArgs args; // [esp+80h] [ebp-910h]
  int v26; // [esp+98Ch] [ebp-4h]

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "--------------- R_InitOpenGL ----------------\n");
  if ( glConfig.isInitialized )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "R_InitOpenGL called while active");
  tr.viewportOffset[0] = 0;
  tr.viewportOffset[1] = 0;
  v0 = 0;
  parms.stereo = 0;
  do
  {
    integerValue = r_mode.internalVar->integerValue;
    if ( integerValue >= -1 && integerValue < s_numVidModes )
    {
      if ( integerValue == -1 )
      {
        glConfig.vidWidth = r_customWidth.internalVar->integerValue;
        glConfig.vidHeight = r_customHeight.internalVar->integerValue;
      }
      else
      {
        v2 = integerValue;
        v3 = dword_102FA394[v2 * 3];
        height = r_vidModes[v2].height;
        glConfig.vidWidth = v3;
        glConfig.vidHeight = height;
      }
    }
    v5 = r_displayRefresh.internalVar->integerValue;
    v6 = r_multiSamples.internalVar->integerValue;
    parms.fullScreen = r_fullscreen.internalVar->integerValue != 0;
    *(_QWORD *)&v19.width = *(_QWORD *)&glConfig.vidWidth;
    v7 = *(_DWORD *)&parms.fullScreen;
    *(_DWORD *)&v19.fullScreen = *(_DWORD *)&parms.fullScreen;
    *(_QWORD *)&v19.displayHz = __PAIR64__(v6, v5);
    if ( GLimp_Init(v19) )
      break;
    if ( v0 == 1 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "Unable to initialize OpenGL");
    r_mode.internalVar->InternalSetInteger(r_mode.internalVar, 3);
    r_fullscreen.internalVar->InternalSetInteger(r_fullscreen.internalVar, 1);
    r_displayRefresh.internalVar->InternalSetInteger(r_displayRefresh.internalVar, 0);
    r_multiSamples.internalVar->InternalSetInteger(r_multiSamples.internalVar, 0);
    r_videoSettingsFailed.internalVar->InternalSetInteger(r_videoSettingsFailed.internalVar, 1);
    ++v0;
  }
  while ( v0 < 2 );
  sys->InitInput(sys);
  v8 = cvarSystem->GetCVarString(cvarSystem, "s_deviceName");
  v9 = 0;
  if ( !*v8 )
    goto LABEL_16;
  do
    ++v9;
  while ( v8[v9] );
  if ( v9 )
  {
    soundSystem->GetDefaultDeviceName(soundSystem);
  }
  else
  {
LABEL_16:
    v10 = cvarSystem->__vftable;
    v11 = ((int (__thiscall *)(idSoundSystem *, _DWORD))soundSystem->GetDefaultDeviceName)(soundSystem, 0);
    ((void (__thiscall *)(idCVarSystem *, const char *, int))v10->SetCVarString)(cvarSystem, "s_deviceName", v11);
  }
  soundSystem->InitHW(soundSystem);
  glConfig.vendor_string = (const char *)qglGetString(0x1F00u);
  glConfig.renderer_string = (const char *)qglGetString(0x1F01u);
  glConfig.version_string = (const char *)qglGetString(0x1F02u);
  glConfig.extensions_string = (const char *)qglGetString(0x1F03u);
  v12 = va("%s/%s/%s", glConfig.vendor_string, glConfig.renderer_string, glConfig.version_string);
  videoCard.len = 0;
  videoCard.alloced = 20;
  videoCard.data = videoCard.baseBuffer;
  videoCard.baseBuffer[0] = 0;
  if ( v12 )
  {
    v13 = (unsigned int)&v12[strlen(v12) + 1];
    v7 = v13 - (_DWORD)(v12 + 1);
    v14 = v13 - (_DWORD)v12;
    if ( v14 > 20 )
      idStr::ReAllocate(&videoCard, v14, 1);
    data = videoCard.data;
    v16 = v12;
    do
    {
      v17 = *v16;
      *data++ = *v16++;
    }
    while ( v17 );
    videoCard.len = v7;
  }
  v26 = 0;
  idStr::ReplaceChar(&videoCard, 92, 47);
  r_videoCard.internalVar->InternalSetString(r_videoCard.internalVar, videoCard.data);
  qglGetIntegerv(0xD33u, &temp);
  glConfig.maxTextureSize = temp;
  if ( temp <= 0 )
    glConfig.maxTextureSize = 256;
  glConfig.isInitialized = 1;
  R_CheckPortableExtensions();
  R_NV10_Init();
  R_NV20_Init(v18);
  R_R200_Init();
  R_ARB2_Init();
  rvNewShaderStage::R_Shaders_Init(v7);
  cmdSystem->AddCommand(
    cmdSystem,
    "reloadARBprograms",
    (void (__cdecl *)(const idCmdArgs *))R_ReloadARBPrograms_f,
    4,
    "reloads ARB programs",
    0);
  args.argc = 0;
  R_ReloadARBPrograms_f();
  idVertexCache::Init(&vertexCache);
  R_InitFrameData();
  BYTE2(r_renderer.internalVar->flags) |= 4u;
  idRenderSystemLocal::SetBackEndRenderer(&tr);
  if ( cvarSystem->GetCVarInteger(cvarSystem, "image_useNormalCompression")
    && !cvarSystem->GetCVarBool(cvarSystem, "com_makingBuild") )
  {
    renderSystem->GetCardCaps(renderSystem, &oldCard, &nv10or20);
    if ( BYTE2(temp) )
      ((void (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->SetCVarInteger)(
        cvarSystem,
        "image_useNormalCompression",
        1);
    else
      ((void (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->SetCVarInteger)(
        cvarSystem,
        "image_useNormalCompression",
        2);
  }
  R_SetColorMappings();
  v26 = -1;
  idStr::FreeData(&videoCard);
}

// FUNC: void __cdecl R_TestVideo_f(class idCmdArgs const &)
void __cdecl R_TestVideo_f(const idCmdArgs *args)
{
  idCinematic *v1; // eax
  const char *v2; // ecx
  cinData_t *v3; // eax
  const unsigned __int8 *image; // ecx
  int imageWidth; // edx
  int imageHeight; // esi
  int v7; // ecx
  const char *v8; // edi
  unsigned int v9; // eax
  char *v10; // esi
  int v11; // eax
  _BYTE *alloced; // edx
  const char *v13; // ecx
  char v14; // al
  idStr *v15; // esi
  char *v16; // ebp
  int v17; // eax
  int v18; // [esp+3Ch] [ebp-68h]
  cinData_t cin; // [esp+48h] [ebp-5Ch] BYREF
  idStr wavString; // [esp+58h] [ebp-4Ch] BYREF
  idStr result; // [esp+7Ch] [ebp-28h] BYREF
  int v22; // [esp+A0h] [ebp-4h]
  int retaddr; // [esp+A4h] [ebp+0h]
  int len; // [esp+ACh] [ebp+8h]

  if ( tr.testVideo )
  {
    ((void (__thiscall *)(idCinematic *, int))tr.testVideo->~idCinematic)(tr.testVideo, 1);
    tr.testVideo = 0;
  }
  tr.testImage = 0;
  if ( args->argc >= 2 )
  {
    tr.testImage = globalImages->ImageFromFile(globalImages, "_scratch", 2, 0, 0, 2, 0, 0);
    v1 = idCinematic::Alloc();
    tr.testVideo = v1;
    if ( args->argc <= 1 )
      v2 = &entityFilter;
    else
      v2 = args->argv[1];
    v1->InitFromFile(v1, v2, 1, 2);
    v3 = tr.testVideo->ImageForTime(tr.testVideo, &cin, 0);
    image = v3->image;
    imageWidth = v3->imageWidth;
    imageHeight = v3->imageHeight;
    cin.status = v3->status;
    if ( image )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%i x %i images\n",
        imageWidth,
        imageHeight);
      len = ((int (__thiscall *)(idCinematic *, int))tr.testVideo->AnimationLength)(tr.testVideo, v18);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%5.1f seconds of video\n",
        (double)len * 0.001);
      tr.testVideoStartTime = (double)tr.primaryRenderView.time * 0.001;
      v7 = (args->argc != 2) + 1;
      if ( v7 < 0 || v7 >= args->argc )
        v8 = &entityFilter;
      else
        v8 = args->argv[v7];
      wavString.data = 0;
      *(_DWORD *)wavString.baseBuffer = 20;
      wavString.alloced = (int)&wavString.baseBuffer[4];
      wavString.baseBuffer[4] = 0;
      if ( v8 )
      {
        v9 = (unsigned int)&v8[strlen(v8) + 1];
        v10 = (char *)(v9 - (_DWORD)(v8 + 1));
        v11 = v9 - (_DWORD)v8;
        if ( v11 > 20 )
          idStr::ReAllocate((idStr *)&wavString.data, v11, 1);
        alloced = (_BYTE *)wavString.alloced;
        v13 = v8;
        do
        {
          v14 = *v13;
          *alloced++ = *v13++;
        }
        while ( v14 );
        wavString.data = v10;
      }
      retaddr = 1;
      idStr::StripFileExtension((idStr *)&wavString.data);
      v15 = operator+(&result, (const idStr *)&wavString.data, ".wav");
      v16 = (char *)v15->len;
      v17 = v15->len + 1;
      if ( v17 > *(int *)wavString.baseBuffer )
        idStr::ReAllocate((idStr *)&wavString.data, v17, 0);
      qmemcpy((void *)wavString.alloced, v15->data, (unsigned int)v16);
      v16[wavString.alloced] = 0;
      wavString.data = v16;
      LOBYTE(retaddr) = 0;
      idStr::FreeData(&result);
      ((void (__thiscall *)(idSoundSystem *, int, int))soundSystem->PlayShaderDirectly)(
        soundSystem,
        1,
        wavString.alloced);
      v22 = -1;
      idStr::FreeData(&wavString);
    }
    else
    {
      if ( tr.testVideo )
        ((void (__thiscall *)(idCinematic *, int))tr.testVideo->~idCinematic)(tr.testVideo, 1);
      tr.testVideo = 0;
      tr.testImage = 0;
    }
  }
}

// FUNC: void __cdecl R_Benchmark_f(class idCmdArgs const &)
void __cdecl R_Benchmark_f()
{
  int v0; // esi
  int v1; // edx
  double v2; // st7
  double v3; // st7
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  float v9; // [esp+5Ch] [ebp-B0h]
  float v10; // [esp+5Ch] [ebp-B0h]
  float v11; // [esp+60h] [ebp-ACh]
  float textureOverhead; // [esp+64h] [ebp-A8h]
  int size; // [esp+68h] [ebp-A4h]
  float sizea; // [esp+68h] [ebp-A4h]
  float initialFPS; // [esp+6Ch] [ebp-A0h]
  float overdrawAnalysis; // [esp+70h] [ebp-9Ch]
  __int64 overdrawAnalysis_4; // [esp+74h] [ebp-98h]
  float triDiverOverhead; // [esp+80h] [ebp-8Ch] BYREF
  renderView_s view; // [esp+84h] [ebp-88h] BYREF

  if ( tr.primaryView )
  {
    renderView_s::operator=(&view, (int)&tr.primaryRenderView);
    v0 = 100;
    initialFPS = 0.0;
    size = 100;
    do
    {
      r_screenFraction.internalVar->InternalSetInteger(r_screenFraction.internalVar, v0);
      textureOverhead = R_RenderingFPS(&view);
      v1 = *(_DWORD *)common.type;
      overdrawAnalysis_4 = (__int64)((double)(glConfig.vidWidth * glConfig.vidHeight)
                                   * ((double)size
                                    * 0.01)
                                   * ((double)size
                                    * 0.01)
                                   * 0.001);
      v2 = 1000.0 / textureOverhead;
      if ( v0 == 100 )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(v1 + 124))(
          common.type,
          "kpix: %4i  msec:%5.1f fps:%5.1f\n",
          (_DWORD)overdrawAnalysis_4,
          v2,
          textureOverhead);
        initialFPS = textureOverhead;
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(v1 + 124))(
          common.type,
          "kpix: %4i     msec:%5.1f fps:%5.1f benefit:%5.1f\n",
          (_DWORD)overdrawAnalysis_4,
          v2,
          textureOverhead,
          textureOverhead - initialFPS);
      }
      v0 -= 10;
      size = v0;
    }
    while ( v0 >= 10 );
    v3 = 1.0 / initialFPS;
    sizea = v3;
    overdrawAnalysis = v3 * textureOverhead;
    r_singleTriangle.internalVar->InternalSetBool(r_singleTriangle.internalVar, 1);
    v11 = R_RenderingFPS((const renderView_s *)&triDiverOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "single tri     msec:%5.1f fps:%5.1f benefit:%5.1f\n",
      1000.0 / v11,
      v11,
      v11 - sizea);
    r_singleTriangle.internalVar->InternalSetBool(r_singleTriangle.internalVar, 0);
    r_screenFraction.internalVar->InternalSetInteger(r_screenFraction.internalVar, 100);
    r_skipRenderContext.internalVar->InternalSetBool(r_skipRenderContext.internalVar, 1);
    v9 = R_RenderingFPS((const renderView_s *)&triDiverOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "no context     msec:%5.1f fps:%5.1f benefit:%5.1f\n",
      1000.0 / v9,
      v9,
      v9 - textureOverhead);
    r_skipRenderContext.internalVar->InternalSetBool(r_skipRenderContext.internalVar, 0);
    r_skipDiffuse.internalVar->InternalSetInteger(r_skipDiffuse.internalVar, 1);
    v4 = R_RenderingFPS((const renderView_s *)&triDiverOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "no Diffuse     msec:%5.1f fps:%5.1f benefit:%5.1f\n",
      1000.0 / v4,
      v4,
      v4 - textureOverhead);
    r_skipDiffuse.internalVar->InternalSetInteger(r_skipDiffuse.internalVar, 0);
    r_skipBump.internalVar->InternalSetInteger(r_skipBump.internalVar, 1);
    v5 = R_RenderingFPS((const renderView_s *)&triDiverOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "no Bump        msec:%5.1f fps:%5.1f benefit:%5.1f\n",
      1000.0 / v5,
      v5,
      v5 - textureOverhead);
    r_skipBump.internalVar->InternalSetInteger(r_skipBump.internalVar, 0);
    r_skipSpecular.internalVar->InternalSetInteger(r_skipSpecular.internalVar, 1);
    v6 = R_RenderingFPS((const renderView_s *)&triDiverOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "no Specular    msec:%5.1f fps:%5.1f benefit:%5.1f\n",
      1000.0 / v6,
      v6,
      v6 - textureOverhead);
    r_skipSpecular.internalVar->InternalSetInteger(r_skipSpecular.internalVar, 0);
    r_skipTextures.internalVar->InternalSetInteger(r_skipTextures.internalVar, 1);
    v10 = R_RenderingFPS((const renderView_s *)&triDiverOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "no Textures    msec:%5.1f fps:%5.1f benefit:%5.1f\n",
      1000.0 / v10,
      v10,
      v10 - textureOverhead);
    r_skipTextures.internalVar->InternalSetInteger(r_skipTextures.internalVar, 0);
    r_skipGuiShaders.internalVar->InternalSetInteger(r_skipGuiShaders.internalVar, 1);
    v7 = R_RenderingFPS((const renderView_s *)&triDiverOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "no GUIShaders  msec:%5.1f fps:%5.1f benefit:%5.1f\n",
      1000.0 / v7,
      v7,
      v7 - textureOverhead);
    r_skipGuiShaders.internalVar->InternalSetInteger(r_skipGuiShaders.internalVar, 0);
    r_skipUpdates.internalVar->InternalSetInteger(r_skipUpdates.internalVar, 1);
    v8 = R_RenderingFPS((const renderView_s *)&triDiverOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "no Updates     msec:%5.1f fps:%5.1f benefit:%5.1f\n",
      1000.0 / v8,
      v8,
      v8 - textureOverhead);
    r_skipUpdates.internalVar->InternalSetInteger(r_skipUpdates.internalVar, 0);
    tr.mBenchmarkMode = BENCHMARK_NONE;
    (*(void (__stdcall **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "--- Analysis ---\n");
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Overdraw: %5.1f\n",
      overdrawAnalysis);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Texture overhead: %5.1f\n",
      textureOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Triangle Driver overhead: %5.1f\n",
      triDiverOverhead);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Driver overhead: %5.1f\n",
      *(float *)&overdrawAnalysis_4);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Visible Entities: %i\n",
      tr.mSavePC.c_visibleViewEntities);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Shadow Entities: %i\n",
      tr.mSavePC.c_shadowViewEntities);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Light Entities: %i\n",
      tr.mSavePC.c_viewLights);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "No primaryView for benchmarking\n");
  }
}

// FUNC: void __cdecl R_VidRestart_f(class idCmdArgs const &)
void __cdecl R_VidRestart_f(const idCmdArgs *args)
{
  int argc; // eax
  int v2; // esi
  const char **v3; // ebp
  const char *v4; // eax
  const char *v5; // eax
  unsigned int Error; // eax
  glimpParms_t v7; // [esp-14h] [ebp-944h]
  bool forceWindow; // [esp+12h] [ebp-91Eh]
  bool full; // [esp+13h] [ebp-91Dh]
  bool latch; // [esp+14h] [ebp-91Ch]
  int parms_8; // [esp+20h] [ebp-910h]
  idCmdArgs v12; // [esp+2Ch] [ebp-904h] BYREF

  if ( glConfig.isInitialized )
  {
    glConfig.isInitialized = 0;
    (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 108))(common.type);
    argc = args->argc;
    v2 = 1;
    full = 1;
    forceWindow = 0;
    if ( args->argc > 1 )
    {
      v3 = (const char **)&args->argv[1];
      do
      {
        if ( v2 < 0 || v2 >= argc )
          v4 = &entityFilter;
        else
          v4 = *v3;
        if ( idStr::Icmp(v4, "partial") )
        {
          if ( v2 < 0 || v2 >= args->argc )
            v5 = &entityFilter;
          else
            v5 = *v3;
          if ( !idStr::Icmp(v5, "windowed") )
            forceWindow = 1;
        }
        else
        {
          full = 0;
        }
        argc = args->argc;
        ++v2;
        ++v3;
      }
      while ( v2 < args->argc );
    }
    sys->GrabMouseCursor(sys, 0);
    renderModelManager->FreeModelVertexCaches(renderModelManager);
    R_FreeDerivedData();
    renderSystem->ToggleSmpFrame(renderSystem);
    renderSystem->ToggleSmpFrame(renderSystem);
    idVertexCache::PurgeAll(&vertexCache);
    if ( full )
    {
      soundSystem->ShutdownHW(soundSystem);
      sys->ShutdownInput(sys);
      globalImages->PurgeAllImages(globalImages);
      R_ShutdownSpecialEffects();
      rvNewShaderStage::R_Shaders_Shutdown((int)args);
      glConfig.GLSLProgramAvailable = 0;
      GLimp_Shutdown();
      glConfig.isInitialized = 0;
      latch = cvarSystem->GetCVarBool(cvarSystem, "r_fullscreen");
      if ( forceWindow )
        cvarSystem->SetCVarBool(cvarSystem, "r_fullscreen", 0, 0);
      R_InitOpenGL();
      cvarSystem->SetCVarBool(cvarSystem, "r_fullscreen", latch, 0);
      globalImages->ReloadAllImages(globalImages);
    }
    else
    {
      LOBYTE(parms_8) = !forceWindow && r_fullscreen.internalVar->integerValue != 0;
      *(_QWORD *)&v7.width = *(_QWORD *)&glConfig.vidWidth;
      BYTE1(parms_8) = 0;
      *(_DWORD *)&v7.fullScreen = parms_8;
      v7.displayHz = r_displayRefresh.internalVar->integerValue;
      v7.multiSamples = r_multiSamples.internalVar->integerValue;
      GLimp_SetScreenParms(v7);
    }
    ++tr.viewCount;
    tr.viewDef = 0;
    v12.argc = 0;
    R_RegenerateWorld_f(&v12);
    Error = qglGetError();
    if ( Error )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "glGetError() = 0x%x\n",
        Error);
    soundSystem->SetMute(soundSystem, 0);
  }
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::InitOpenGL(void)
void __thiscall idRenderSystemLocal::InitOpenGL(idRenderSystemLocal *this)
{
  unsigned int Error; // eax

  if ( !glConfig.isInitialized )
  {
    R_InitOpenGL();
    globalImages->ReloadAllImages(globalImages);
    Error = qglGetError();
    if ( Error )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "glGetError() = 0x%x\n",
        Error);
  }
}

// FUNC: void __cdecl R_EnvShot_f(class idCmdArgs const &)
void __cdecl R_EnvShot_f(const idCmdArgs *args)
{
  char *v1; // esi
  int v2; // ebx
  int argc; // eax
  bool v4; // zf
  int v5; // ebp
  int v6; // ebx
  int v7; // edi
  float *p_z; // esi
  float v9; // edx
  float v10; // eax
  float v11; // edx
  float v12; // ecx
  float v13; // eax
  float v14; // edx
  float v15; // ecx
  float v16; // eax
  float v17; // ecx
  const char *v18; // [esp-8h] [ebp-438h]
  const char *baseName; // [esp+Ch] [ebp-424h]
  idStr fullname; // [esp+10h] [ebp-420h] BYREF
  char *extensions[6]; // [esp+30h] [ebp-400h]
  renderView_s ref; // [esp+48h] [ebp-3E8h] BYREF
  idMat3 axis[6]; // [esp+D0h] [ebp-360h] BYREF
  viewDef_s primary; // [esp+1A8h] [ebp-288h] BYREF
  int v25; // [esp+42Ch] [ebp-4h]

  fullname.len = 0;
  fullname.alloced = 20;
  fullname.data = fullname.baseBuffer;
  fullname.baseBuffer[0] = 0;
  v25 = 0;
  v1 = (char *)axis;
  v2 = 6;
  do
  {
    `vector constructor iterator'(v1, 0xCu, 3, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
    v1 += 36;
    --v2;
  }
  while ( v2 );
  argc = args->argc;
  v4 = args->argc == 2;
  primary.viewFrustum.dFar = 0.0;
  primary.viewFrustum.dNear = 0.0;
  extensions[0] = "_px.tga";
  extensions[1] = "_nx.tga";
  extensions[2] = "_py.tga";
  extensions[3] = "_ny.tga";
  extensions[4] = "_pz.tga";
  extensions[5] = "_nz.tga";
  if ( v4 || argc == 3 || argc == 4 )
  {
    if ( argc <= 1 )
      baseName = &entityFilter;
    else
      baseName = args->argv[1];
    if ( argc == 4 )
    {
      v5 = atoi(args->argv[2]);
      if ( args->argc <= 3 )
        v6 = atoi(&entityFilter);
      else
        v6 = atoi(args->argv[3]);
    }
    else
    {
      if ( argc == 3 )
        v5 = atoi(args->argv[2]);
      else
        v5 = 256;
      v6 = 1;
    }
    if ( tr.primaryView )
    {
      viewDef_s::operator=(&primary, &tr.primaryView->renderView.viewID);
      memset(axis, 0, sizeof(axis));
      axis[0].mat[0].x = 1.0;
      axis[0].mat[1].z = 1.0;
      axis[0].mat[2].y = 1.0;
      axis[1].mat[0].x = -1.0;
      axis[1].mat[1].z = -1.0;
      axis[1].mat[2].y = 1.0;
      axis[2].mat[0].y = 1.0;
      axis[2].mat[1].x = -1.0;
      axis[2].mat[2].z = -1.0;
      axis[3].mat[0].y = -1.0;
      axis[3].mat[1].x = -1.0;
      axis[3].mat[2].z = 1.0;
      axis[4].mat[0].z = 1.0;
      axis[4].mat[1].x = -1.0;
      axis[4].mat[2].y = 1.0;
      axis[5].mat[0].z = -1.0;
      axis[5].mat[1].x = 1.0;
      axis[5].mat[2].y = 1.0;
      v7 = 0;
      p_z = &axis[0].mat[0].z;
      do
      {
        renderView_s::operator=(&ref, (int)&primary);
        v9 = *(p_z - 2);
        ref.y = 0;
        ref.x = 0;
        ref.width = glConfig.vidWidth;
        v10 = *(p_z - 1);
        ref.viewaxis.mat[0].x = v9;
        v11 = p_z[1];
        ref.height = glConfig.vidHeight;
        v12 = *p_z;
        ref.viewaxis.mat[0].y = v10;
        v13 = p_z[2];
        ref.viewaxis.mat[1].x = v11;
        v14 = p_z[4];
        ref.viewaxis.mat[0].z = v12;
        v15 = p_z[3];
        ref.viewaxis.mat[1].y = v13;
        v16 = p_z[5];
        ref.viewaxis.mat[2].x = v14;
        v18 = extensions[v7];
        ref.viewaxis.mat[1].z = v15;
        v17 = p_z[6];
        ref.viewaxis.mat[2].y = v16;
        ref.viewaxis.mat[2].z = v17;
        ref.fov_y = 90.0;
        ref.fov_x = 90.0;
        sprintf(&fullname, "env/%s%s", baseName, v18);
        idRenderSystemLocal::TakeScreenshot(&tr, v5, v5, fullname.data, v6, &ref, "fs_savepath");
        ++v7;
        p_z += 9;
      }
      while ( v7 < 6 );
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Wrote %s, etc\n",
        fullname.data);
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "No primary view.\n");
    }
    v25 = -1;
    idStr::FreeData(&fullname);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "USAGE: envshot <basename> [size] [blends]\n");
    v25 = -1;
    idStr::FreeData(&fullname);
  }
}

// FUNC: void __cdecl R_InitCommands(void)
void __cdecl R_InitCommands()
{
  cmdSystem->AddCommand(
    cmdSystem,
    "MakeMegaTexture",
    (void (__cdecl *)(const idCmdArgs *))idMegaTexture::MakeMegaTexture_f,
    5,
    "processes giant images",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "sizeUp",
    (void (__cdecl *)(const idCmdArgs *))R_SizeUp_f,
    4,
    "makes the rendered view larger",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "sizeDown",
    (void (__cdecl *)(const idCmdArgs *))R_SizeDown_f,
    4,
    "makes the rendered view smaller",
    0);
  cmdSystem->AddCommand(cmdSystem, "reloadGuis", R_ReloadGuis_f, 4, "reloads guis", 0);
  cmdSystem->AddCommand(cmdSystem, "listGuis", R_ListGuis_f, 4, "lists guis", 0);
  cmdSystem->AddCommand(cmdSystem, "touchGui", R_TouchGui_f, 4, "touches a gui", 0);
  cmdSystem->AddCommand(cmdSystem, "screenshot", R_ScreenShot_f, 4, "takes a tga screenshot", 0);
  cmdSystem->AddCommand(cmdSystem, "screenshotJpeg", R_ScreenShot_f, 4, "takes a jpg screenshot", 0);
  cmdSystem->AddCommand(cmdSystem, "envshot", R_EnvShot_f, 4, "takes an environment shot", 0);
  cmdSystem->AddCommand(cmdSystem, "makeAmbientMap", R_MakeAmbientMap_f, 5, "makes an ambient map", 0);
  cmdSystem->AddCommand(cmdSystem, "benchmark", (void (__cdecl *)(const idCmdArgs *))R_Benchmark_f, 4, "benchmark", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "gfxInfo",
    (void (__cdecl *)(const idCmdArgs *))GfxInfo_f,
    4,
    "show graphics info",
    0);
  cmdSystem->AddCommand(cmdSystem, "modulateLights", R_ModulateLights_f, 5, "modifies shader parms on all lights", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "testImage",
    R_TestImage_f,
    5,
    "displays the given image centered on screen",
    idCmdSystem::ArgCompletion_ImageName);
  cmdSystem->AddCommand(
    cmdSystem,
    "testVideo",
    R_TestVideo_f,
    5,
    "displays the given cinematic",
    idCmdSystem::ArgCompletion_VideoName);
  cmdSystem->AddCommand(
    cmdSystem,
    "testStandaloneVideo",
    R_TestStandaloneVideo_f,
    5,
    "displays the a standalone cinematic",
    idCmdSystem::ArgCompletion_StandaloneVideoName);
  cmdSystem->AddCommand(
    cmdSystem,
    "reportSurfaceAreas",
    (void (__cdecl *)(const idCmdArgs *))R_ReportSurfaceAreas_f,
    4,
    "lists all used materials sorted by surface area",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "reportImageDuplication",
    (void (__cdecl *)(const idCmdArgs *))R_ReportImageDuplication_f,
    4,
    "checks all referenced images for duplications",
    0);
  cmdSystem->AddCommand(cmdSystem, "regenerateWorld", R_RegenerateWorld_f, 4, "regenerates all interactions", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "showInteractionMemory",
    (void (__cdecl *)(const idCmdArgs *))R_ShowInteractionMemory_f,
    4,
    "shows memory used by interactions",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "showTriSurfMemory",
    R_ShowTriSurfMemory_f,
    4,
    "shows memory used by triangle surfaces",
    0);
  cmdSystem->AddCommand(cmdSystem, "vid_restart", R_VidRestart_f, 4, "restarts renderSystem", 0);
  cmdSystem->AddCommand(cmdSystem, "listRenderEntityDefs", R_ListRenderEntityDefs_f, 4, "lists the entity defs", 0);
  cmdSystem->AddCommand(cmdSystem, "listRenderLightDefs", R_ListRenderLightDefs_f, 4, "lists the light defs", 0);
  cmdSystem->AddCommand(cmdSystem, "listRenderEffectDefs", R_ListRenderEffectDefs_f, 4, "lists the effect defs", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "listModes",
    (void (__cdecl *)(const idCmdArgs *))R_ListModes_f,
    4,
    "lists all video modes",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "reloadSurface",
    (void (__cdecl *)(const idCmdArgs *))R_ReloadSurface_f,
    4,
    "reloads the decl and images for selected surface",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "reloadMaterials",
    (void (__cdecl *)(const idCmdArgs *))R_ReloadMaterials_f,
    4,
    "reloads all currently loaded materials",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "reloadShaders",
    (void (__cdecl *)(const idCmdArgs *))R_ReloadShaders_f,
    4,
    "reloads the hardware shader programs",
    0);
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::Init(void)
void __thiscall idRenderSystemLocal::Init(idRenderSystemLocal *this)
{
  idGuiModel *v2; // eax
  idGuiModel *v3; // eax
  idGuiModel *v4; // eax
  idGuiModel *v5; // eax
  idGuiModel *v6; // eax
  idGuiModel *v7; // eax

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "-------- Initializing renderSystem ----------\n");
  this->viewCount = 1;
  this->ambientLightVector.x = 0.5;
  this->ambientLightVector.y = 0.11500001;
  this->ambientLightVector.z = 0.89249998;
  this->ambientLightVector.w = 1.0;
  memset(&backEnd, 0, sizeof(backEnd));
  R_InitCommands();
  v2 = (idGuiModel *)Memory::Allocate(0x34u);
  if ( v2 )
    idGuiModel::idGuiModel(v2);
  else
    v3 = 0;
  this->guiModel = v3;
  idGuiModel::Clear(v3);
  v4 = (idGuiModel *)Memory::Allocate(0x34u);
  if ( v4 )
    idGuiModel::idGuiModel(v4);
  else
    v5 = 0;
  this->demoGuiModel = v5;
  idGuiModel::Clear(v5);
  R_InitTriSurfData();
  v6 = (idGuiModel *)Memory::Allocate(0x34u);
  if ( v6 )
    idGuiModel::idGuiModel(v6);
  else
    v7 = 0;
  this->guiOverlayModel = v7;
  idGuiModel::Clear(v7);
  globalImages->Init(globalImages);
  idCinematic::InitCinematic();
  R_SetColorMappings();
  R_InitMaterials();
  renderModelManager->Init(renderModelManager);
  this->identitySpace.modelMatrix[0] = 1.0;
  this->identitySpace.modelMatrix[5] = 1.0;
  this->identitySpace.modelMatrix[10] = 1.0;
  idRenderSystemLocal::SetBackEndRenderer(this);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "renderSystem initialized.\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
}

// FUNC: public: virtual void __thiscall idRenderSystemLocal::Shutdown(void)
void __thiscall idRenderSystemLocal::Shutdown(idRenderSystemLocal *this)
{
  idGuiModel *guiModel; // edi
  idGuiModel *demoGuiModel; // edi
  idGuiModel *guiOverlayModel; // edi
  idStr *p_lastLoadedImage; // esi

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "idRenderSystem::Shutdown()\n");
  if ( glConfig.isInitialized )
    globalImages->PurgeAllImages(globalImages);
  renderModelManager->Shutdown(renderModelManager);
  idCinematic::ShutdownCinematic();
  globalImages->Shutdown(globalImages);
  R_ShutdownFrameData();
  idVertexCache::~idVertexCache(&vertexCache);
  R_ShutdownTriSurfData();
  guiModel = this->guiModel;
  if ( guiModel )
  {
    idGuiModel::~idGuiModel(this->guiModel);
    Memory::Free(guiModel);
  }
  demoGuiModel = this->demoGuiModel;
  if ( demoGuiModel )
  {
    idGuiModel::~idGuiModel(this->demoGuiModel);
    Memory::Free(demoGuiModel);
  }
  guiOverlayModel = this->guiOverlayModel;
  if ( guiOverlayModel )
  {
    idGuiModel::~idGuiModel(this->guiOverlayModel);
    Memory::Free(guiOverlayModel);
  }
  idRenderSystemLocal::Clear(this);
  if ( this->IsOpenGLRunning(this) )
    this->ShutdownOpenGL(this);
  p_lastLoadedImage = &this->lastLoadedImage;
  idStr::FreeData(p_lastLoadedImage);
  p_lastLoadedImage->len = 0;
  p_lastLoadedImage->alloced = 20;
  p_lastLoadedImage->data = p_lastLoadedImage->baseBuffer;
  p_lastLoadedImage->baseBuffer[0] = 0;
}

// FUNC: $E123
int _E123()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_finish);
  }
  else
  {
    r_finish.next = idCVar::staticVars;
    idCVar::staticVars = &r_finish;
  }
  return atexit(_E124_0);
}

// FUNC: $E126
int _E126()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_swapInterval);
  }
  else
  {
    r_swapInterval.next = idCVar::staticVars;
    idCVar::staticVars = &r_swapInterval;
  }
  return atexit(_E127_0);
}

// FUNC: $E129
int _E129()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_gamma);
  }
  else
  {
    r_gamma.next = idCVar::staticVars;
    idCVar::staticVars = &r_gamma;
  }
  return atexit(_E130_0);
}

// FUNC: $E132
int _E132()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_brightness);
  }
  else
  {
    r_brightness.next = idCVar::staticVars;
    idCVar::staticVars = &r_brightness;
  }
  return atexit(_E133_0);
}

// FUNC: $E135
int _E135()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_renderer);
  }
  else
  {
    r_renderer.next = idCVar::staticVars;
    idCVar::staticVars = &r_renderer;
  }
  return atexit(_E136_0);
}

// FUNC: $E141
int _E141()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipSuppress);
  }
  else
  {
    r_skipSuppress.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipSuppress;
  }
  return atexit(_E142);
}

// FUNC: $E144
int _E144()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipPostProcess);
  }
  else
  {
    r_skipPostProcess.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipPostProcess;
  }
  return atexit(_E145);
}

// FUNC: $E147
int _E147()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipLightScale);
  }
  else
  {
    r_skipLightScale.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipLightScale;
  }
  return atexit(_E148);
}

// FUNC: $E150
int _E150()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipInteractions);
  }
  else
  {
    r_skipInteractions.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipInteractions;
  }
  return atexit(_E151);
}

// FUNC: $E153
int _E153()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipDynamicTextures);
  }
  else
  {
    r_skipDynamicTextures.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipDynamicTextures;
  }
  return atexit(_E154);
}

// FUNC: $E156
int _E156()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipCopyTexture);
  }
  else
  {
    r_skipCopyTexture.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipCopyTexture;
  }
  return atexit(_E157);
}

// FUNC: $E159
int _E159()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipBackEnd);
  }
  else
  {
    r_skipBackEnd.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipBackEnd;
  }
  return atexit(_E160);
}

// FUNC: $E162
int _E162()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipRender);
  }
  else
  {
    r_skipRender.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipRender;
  }
  return atexit(_E163);
}

// FUNC: $E165
int _E165()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipRenderContext);
  }
  else
  {
    r_skipRenderContext.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipRenderContext;
  }
  return atexit(_E166);
}

// FUNC: $E168
int _E168()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipTranslucent);
  }
  else
  {
    r_skipTranslucent.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipTranslucent;
  }
  return atexit(_E169);
}

// FUNC: $E171
int _E171()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipAmbient);
  }
  else
  {
    r_skipAmbient.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipAmbient;
  }
  return atexit(_E172);
}

// FUNC: $E174
int _E174()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipNewAmbient);
  }
  else
  {
    r_skipNewAmbient.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipNewAmbient;
  }
  return atexit(_E175);
}

// FUNC: $E177
int _E177()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipBlendLights);
  }
  else
  {
    r_skipBlendLights.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipBlendLights;
  }
  return atexit(_E178);
}

// FUNC: $E180
int _E180()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipFogLights);
  }
  else
  {
    r_skipFogLights.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipFogLights;
  }
  return atexit(_E181);
}

// FUNC: $E183
int _E183()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipDeforms);
  }
  else
  {
    r_skipDeforms.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipDeforms;
  }
  return atexit(_E184);
}

// FUNC: $E186
int _E186()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipFrontEnd);
  }
  else
  {
    r_skipFrontEnd.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipFrontEnd;
  }
  return atexit(_E187);
}

// FUNC: $E189
int _E189()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipUpdates);
  }
  else
  {
    r_skipUpdates.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipUpdates;
  }
  return atexit(_E190);
}

// FUNC: $E192
int _E192()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipOverlays);
  }
  else
  {
    r_skipOverlays.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipOverlays;
  }
  return atexit(_E193);
}

// FUNC: $E195
int _E195()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipSpecular);
  }
  else
  {
    r_skipSpecular.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipSpecular;
  }
  return atexit(_E196);
}

// FUNC: $E198
int _E198()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipBump);
  }
  else
  {
    r_skipBump.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipBump;
  }
  return atexit(_E199);
}

// FUNC: $E201
int _E201()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipDiffuse);
  }
  else
  {
    r_skipDiffuse.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipDiffuse;
  }
  return atexit(_E202);
}

// FUNC: $E204
int _E204()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipROQ);
  }
  else
  {
    r_skipROQ.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipROQ;
  }
  return atexit(_E205);
}

// FUNC: $E207
int _E207()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipDownsize);
  }
  else
  {
    r_skipDownsize.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipDownsize;
  }
  return atexit(_E208);
}

// FUNC: $E210
int _E210()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_testSpecialEffect);
  }
  else
  {
    r_testSpecialEffect.next = idCVar::staticVars;
    idCVar::staticVars = &r_testSpecialEffect;
  }
  return atexit(_E211);
}

// FUNC: $E213
int _E213()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_testSpecialEffectParm);
  }
  else
  {
    r_testSpecialEffectParm.next = idCVar::staticVars;
    idCVar::staticVars = &r_testSpecialEffectParm;
  }
  return atexit(_E214);
}

// FUNC: $E216
int _E216()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_testSpecialEffectParmValue);
  }
  else
  {
    r_testSpecialEffectParmValue.next = idCVar::staticVars;
    idCVar::staticVars = &r_testSpecialEffectParmValue;
  }
  return atexit(_E217);
}

// FUNC: $E219
int _E219()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_ignore);
  }
  else
  {
    r_ignore.next = idCVar::staticVars;
    idCVar::staticVars = &r_ignore;
  }
  return atexit(_E220);
}

// FUNC: $E222
int _E222()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_ignore2);
  }
  else
  {
    r_ignore2.next = idCVar::staticVars;
    idCVar::staticVars = &r_ignore2;
  }
  return atexit(_E223);
}

// FUNC: $E225
int _E225()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_usePreciseTriangleInteractions);
  }
  else
  {
    r_usePreciseTriangleInteractions.next = idCVar::staticVars;
    idCVar::staticVars = &r_usePreciseTriangleInteractions;
  }
  return atexit(_E226);
}

// FUNC: $E228
int _E228()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useCulling);
  }
  else
  {
    r_useCulling.next = idCVar::staticVars;
    idCVar::staticVars = &r_useCulling;
  }
  return atexit(_E229);
}

// FUNC: $E231
int _E231()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useLightCulling);
  }
  else
  {
    r_useLightCulling.next = idCVar::staticVars;
    idCVar::staticVars = &r_useLightCulling;
  }
  return atexit(_E232);
}

// FUNC: $E234
int _E234()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useLightScissors);
  }
  else
  {
    r_useLightScissors.next = idCVar::staticVars;
    idCVar::staticVars = &r_useLightScissors;
  }
  return atexit(_E235);
}

// FUNC: $E237
int _E237()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useClippedLightScissors);
  }
  else
  {
    r_useClippedLightScissors.next = idCVar::staticVars;
    idCVar::staticVars = &r_useClippedLightScissors;
  }
  return atexit(_E238);
}

// FUNC: $E240
int _E240()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useEntityCulling);
  }
  else
  {
    r_useEntityCulling.next = idCVar::staticVars;
    idCVar::staticVars = &r_useEntityCulling;
  }
  return atexit(_E241);
}

// FUNC: $E243
int _E243()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useEntityScissors);
  }
  else
  {
    r_useEntityScissors.next = idCVar::staticVars;
    idCVar::staticVars = &r_useEntityScissors;
  }
  return atexit(_E244);
}

// FUNC: $E246
int _E246()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useInteractionCulling);
  }
  else
  {
    r_useInteractionCulling.next = idCVar::staticVars;
    idCVar::staticVars = &r_useInteractionCulling;
  }
  return atexit(_E247);
}

// FUNC: $E249
int _E249()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useInteractionScissors);
  }
  else
  {
    r_useInteractionScissors.next = idCVar::staticVars;
    idCVar::staticVars = &r_useInteractionScissors;
  }
  return atexit(_E250);
}

// FUNC: $E252
int _E252()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useShadowCulling);
  }
  else
  {
    r_useShadowCulling.next = idCVar::staticVars;
    idCVar::staticVars = &r_useShadowCulling;
  }
  return atexit(_E253);
}

// FUNC: $E255
int _E255()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useFrustumFarDistance);
  }
  else
  {
    r_useFrustumFarDistance.next = idCVar::staticVars;
    idCVar::staticVars = &r_useFrustumFarDistance;
  }
  return atexit(_E256);
}

// FUNC: $E258
int _E258()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_clear);
  }
  else
  {
    r_clear.next = idCVar::staticVars;
    idCVar::staticVars = &r_clear;
  }
  return atexit(_E259);
}

// FUNC: $E261
int _E261()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_offsetFactor);
  }
  else
  {
    r_offsetFactor.next = idCVar::staticVars;
    idCVar::staticVars = &r_offsetFactor;
  }
  return atexit(_E262);
}

// FUNC: $E264
int _E264()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_offsetUnits);
  }
  else
  {
    r_offsetUnits.next = idCVar::staticVars;
    idCVar::staticVars = &r_offsetUnits;
  }
  return atexit(_E265);
}

// FUNC: $E267
int _E267()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_shadowPolygonOffset);
  }
  else
  {
    r_shadowPolygonOffset.next = idCVar::staticVars;
    idCVar::staticVars = &r_shadowPolygonOffset;
  }
  return atexit(_E268);
}

// FUNC: $E270
int _E270()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_shadowPolygonFactor);
  }
  else
  {
    r_shadowPolygonFactor.next = idCVar::staticVars;
    idCVar::staticVars = &r_shadowPolygonFactor;
  }
  return atexit(_E271);
}

// FUNC: $E273
int _E273()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_frontBuffer);
  }
  else
  {
    r_frontBuffer.next = idCVar::staticVars;
    idCVar::staticVars = &r_frontBuffer;
  }
  return atexit(_E274);
}

// FUNC: $E276
int _E276()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipSubviews);
  }
  else
  {
    r_skipSubviews.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipSubviews;
  }
  return atexit(_E277);
}

// FUNC: $E279
int _E279()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipGuiShaders);
  }
  else
  {
    r_skipGuiShaders.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipGuiShaders;
  }
  return atexit(_E280);
}

// FUNC: $E282
int _E282()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_subviewOnly);
  }
  else
  {
    r_subviewOnly.next = idCVar::staticVars;
    idCVar::staticVars = &r_subviewOnly;
  }
  return atexit(_E283);
}

// FUNC: $E285
int _E285()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_shadows);
  }
  else
  {
    r_shadows.next = idCVar::staticVars;
    idCVar::staticVars = &r_shadows;
  }
  return atexit(_E286);
}

// FUNC: $E288
int _E288()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_testARBProgram);
  }
  else
  {
    r_testARBProgram.next = idCVar::staticVars;
    idCVar::staticVars = &r_testARBProgram;
  }
  return atexit(_E289);
}

// FUNC: $E291
int _E291()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_testGamma);
  }
  else
  {
    r_testGamma.next = idCVar::staticVars;
    idCVar::staticVars = &r_testGamma;
  }
  return atexit(_E292);
}

// FUNC: $E294
int _E294()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_testGammaBias);
  }
  else
  {
    r_testGammaBias.next = idCVar::staticVars;
    idCVar::staticVars = &r_testGammaBias;
  }
  return atexit(_E295);
}

// FUNC: $E297
int _E297()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_testStepGamma);
  }
  else
  {
    r_testStepGamma.next = idCVar::staticVars;
    idCVar::staticVars = &r_testStepGamma;
  }
  return atexit(_E298);
}

// FUNC: $E300
int _E300()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lightScale);
  }
  else
  {
    r_lightScale.next = idCVar::staticVars;
    idCVar::staticVars = &r_lightScale;
  }
  return atexit(_E301);
}

// FUNC: $E303
int _E303()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lightSourceRadius);
  }
  else
  {
    r_lightSourceRadius.next = idCVar::staticVars;
    idCVar::staticVars = &r_lightSourceRadius;
  }
  return atexit(_E304);
}

// FUNC: $E306
int _E306()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_flareSize);
  }
  else
  {
    r_flareSize.next = idCVar::staticVars;
    idCVar::staticVars = &r_flareSize;
  }
  return atexit(_E307);
}

// FUNC: $E309
int _E309()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useSimpleInteraction);
  }
  else
  {
    r_useSimpleInteraction.next = idCVar::staticVars;
    idCVar::staticVars = &r_useSimpleInteraction;
  }
  return atexit(_E310);
}

// FUNC: $E312
int _E312()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_usePenumbraMapShadows);
  }
  else
  {
    r_usePenumbraMapShadows.next = idCVar::staticVars;
    idCVar::staticVars = &r_usePenumbraMapShadows;
  }
  return atexit(_E313);
}

// FUNC: $E315
int _E315()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_shadowMapDepthBias);
  }
  else
  {
    r_shadowMapDepthBias.next = idCVar::staticVars;
    idCVar::staticVars = &r_shadowMapDepthBias;
  }
  return atexit(_E316);
}

// FUNC: $E318
int _E318()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_shadowMapSlopeScaleBias);
  }
  else
  {
    r_shadowMapSlopeScaleBias.next = idCVar::staticVars;
    idCVar::staticVars = &r_shadowMapSlopeScaleBias;
  }
  return atexit(_E319);
}

// FUNC: $E321
int _E321()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_penumbraMapDepthBias);
  }
  else
  {
    r_penumbraMapDepthBias.next = idCVar::staticVars;
    idCVar::staticVars = &r_penumbraMapDepthBias;
  }
  return atexit(_E322);
}

// FUNC: $E324
int _E324()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useExternalShadows);
  }
  else
  {
    r_useExternalShadows.next = idCVar::staticVars;
    idCVar::staticVars = &r_useExternalShadows;
  }
  return atexit(_E325);
}

// FUNC: $E327
int _E327()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useOptimizedShadows);
  }
  else
  {
    r_useOptimizedShadows.next = idCVar::staticVars;
    idCVar::staticVars = &r_useOptimizedShadows;
  }
  return atexit(_E328);
}

// FUNC: $E330
int _E330()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useScissor);
  }
  else
  {
    r_useScissor.next = idCVar::staticVars;
    idCVar::staticVars = &r_useScissor;
  }
  return atexit(_E331);
}

// FUNC: $E333
int _E333()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useCombinerDisplayLists);
  }
  else
  {
    r_useCombinerDisplayLists.next = idCVar::staticVars;
    idCVar::staticVars = &r_useCombinerDisplayLists;
  }
  return atexit(_E334);
}

// FUNC: $E336
int _E336()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useDepthBoundsTest);
  }
  else
  {
    r_useDepthBoundsTest.next = idCVar::staticVars;
    idCVar::staticVars = &r_useDepthBoundsTest;
  }
  return atexit(_E337);
}

// FUNC: $E339
int _E339()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_screenFraction);
  }
  else
  {
    r_screenFraction.next = idCVar::staticVars;
    idCVar::staticVars = &r_screenFraction;
  }
  return atexit(_E340);
}

// FUNC: $E342
int _E342()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_demonstrateBug);
  }
  else
  {
    r_demonstrateBug.next = idCVar::staticVars;
    idCVar::staticVars = &r_demonstrateBug;
  }
  return atexit(_E343);
}

// FUNC: $E345
int _E345()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_usePortals);
  }
  else
  {
    r_usePortals.next = idCVar::staticVars;
    idCVar::staticVars = &r_usePortals;
  }
  return atexit(_E346);
}

// FUNC: $E348
int _E348()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_singleLight);
  }
  else
  {
    r_singleLight.next = idCVar::staticVars;
    idCVar::staticVars = &r_singleLight;
  }
  return atexit(_E349);
}

// FUNC: $E351
int _E351()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_singleEntity);
  }
  else
  {
    r_singleEntity.next = idCVar::staticVars;
    idCVar::staticVars = &r_singleEntity;
  }
  return atexit(_E352);
}

// FUNC: $E354
int _E354()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_singleSurface);
  }
  else
  {
    r_singleSurface.next = idCVar::staticVars;
    idCVar::staticVars = &r_singleSurface;
  }
  return atexit(_E355);
}

// FUNC: $E357
int _E357()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_singleArea);
  }
  else
  {
    r_singleArea.next = idCVar::staticVars;
    idCVar::staticVars = &r_singleArea;
  }
  return atexit(_E358);
}

// FUNC: $E360
int _E360()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_forceLoadImages);
  }
  else
  {
    r_forceLoadImages.next = idCVar::staticVars;
    idCVar::staticVars = &r_forceLoadImages;
  }
  return atexit(_E361);
}

// FUNC: $E363
int _E363()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_orderIndexes);
  }
  else
  {
    r_orderIndexes.next = idCVar::staticVars;
    idCVar::staticVars = &r_orderIndexes;
  }
  return atexit(_E364);
}

// FUNC: $E366
int _E366()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lightAllBackFaces);
  }
  else
  {
    r_lightAllBackFaces.next = idCVar::staticVars;
    idCVar::staticVars = &r_lightAllBackFaces;
  }
  return atexit(_E367);
}

// FUNC: $E369
int _E369()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showPortals);
  }
  else
  {
    r_showPortals.next = idCVar::staticVars;
    idCVar::staticVars = &r_showPortals;
  }
  return atexit(_E370);
}

// FUNC: $E372
int _E372()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showUnsmoothedTangents);
  }
  else
  {
    r_showUnsmoothedTangents.next = idCVar::staticVars;
    idCVar::staticVars = &r_showUnsmoothedTangents;
  }
  return atexit(_E373);
}

// FUNC: $E375
int _E375()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showSilhouette);
  }
  else
  {
    r_showSilhouette.next = idCVar::staticVars;
    idCVar::staticVars = &r_showSilhouette;
  }
  return atexit(_E376);
}

// FUNC: $E378
int _E378()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showVertexColor);
  }
  else
  {
    r_showVertexColor.next = idCVar::staticVars;
    idCVar::staticVars = &r_showVertexColor;
  }
  return atexit(_E379);
}

// FUNC: $E381
int _E381()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showUpdates);
  }
  else
  {
    r_showUpdates.next = idCVar::staticVars;
    idCVar::staticVars = &r_showUpdates;
  }
  return atexit(_E382);
}

// FUNC: $E384
int _E384()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showDemo);
  }
  else
  {
    r_showDemo.next = idCVar::staticVars;
    idCVar::staticVars = &r_showDemo;
  }
  return atexit(_E385);
}

// FUNC: $E387
int _E387()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showDynamic);
  }
  else
  {
    r_showDynamic.next = idCVar::staticVars;
    idCVar::staticVars = &r_showDynamic;
  }
  return atexit(_E388);
}

// FUNC: $E390
int _E390()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showLightScale);
  }
  else
  {
    r_showLightScale.next = idCVar::staticVars;
    idCVar::staticVars = &r_showLightScale;
  }
  return atexit(_E391);
}

// FUNC: $E393
int _E393()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showRenderTrace);
  }
  else
  {
    r_showRenderTrace.next = idCVar::staticVars;
    idCVar::staticVars = &r_showRenderTrace;
  }
  return atexit(_E394);
}

// FUNC: $E396
int _E396()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showDefs);
  }
  else
  {
    r_showDefs.next = idCVar::staticVars;
    idCVar::staticVars = &r_showDefs;
  }
  return atexit(_E397);
}

// FUNC: $E399
int _E399()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showTrace);
  }
  else
  {
    r_showTrace.next = idCVar::staticVars;
    idCVar::staticVars = &r_showTrace;
  }
  return atexit(_E400);
}

// FUNC: $E402
int _E402()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showIntensity);
  }
  else
  {
    r_showIntensity.next = idCVar::staticVars;
    idCVar::staticVars = &r_showIntensity;
  }
  return atexit(_E403);
}

// FUNC: $E405
int _E405()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showImages);
  }
  else
  {
    r_showImages.next = idCVar::staticVars;
    idCVar::staticVars = &r_showImages;
  }
  return atexit(_E406);
}

// FUNC: $E408
int _E408()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showSmp);
  }
  else
  {
    r_showSmp.next = idCVar::staticVars;
    idCVar::staticVars = &r_showSmp;
  }
  return atexit(_E409);
}

// FUNC: $E411
int _E411()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showLights);
  }
  else
  {
    r_showLights.next = idCVar::staticVars;
    idCVar::staticVars = &r_showLights;
  }
  return atexit(_E412);
}

// FUNC: $E414
int _E414()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showShadows);
  }
  else
  {
    r_showShadows.next = idCVar::staticVars;
    idCVar::staticVars = &r_showShadows;
  }
  return atexit(_E415);
}

// FUNC: $E417
int _E417()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showShadowCount);
  }
  else
  {
    r_showShadowCount.next = idCVar::staticVars;
    idCVar::staticVars = &r_showShadowCount;
  }
  return atexit(_E418);
}

// FUNC: $E420
int _E420()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showLightScissors);
  }
  else
  {
    r_showLightScissors.next = idCVar::staticVars;
    idCVar::staticVars = &r_showLightScissors;
  }
  return atexit(_E421);
}

// FUNC: $E423
int _E423()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showEntityScissors);
  }
  else
  {
    r_showEntityScissors.next = idCVar::staticVars;
    idCVar::staticVars = &r_showEntityScissors;
  }
  return atexit(_E424);
}

// FUNC: $E426
int _E426()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showInteractionFrustums);
  }
  else
  {
    r_showInteractionFrustums.next = idCVar::staticVars;
    idCVar::staticVars = &r_showInteractionFrustums;
  }
  return atexit(_E427);
}

// FUNC: $E429
int _E429()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showInteractionScissors);
  }
  else
  {
    r_showInteractionScissors.next = idCVar::staticVars;
    idCVar::staticVars = &r_showInteractionScissors;
  }
  return atexit(_E430);
}

// FUNC: $E432
int _E432()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showLightCount);
  }
  else
  {
    r_showLightCount.next = idCVar::staticVars;
    idCVar::staticVars = &r_showLightCount;
  }
  return atexit(_E433);
}

// FUNC: $E435
int _E435()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showViewEntitys);
  }
  else
  {
    r_showViewEntitys.next = idCVar::staticVars;
    idCVar::staticVars = &r_showViewEntitys;
  }
  return atexit(_E436);
}

// FUNC: $E438
int _E438()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showTris);
  }
  else
  {
    r_showTris.next = idCVar::staticVars;
    idCVar::staticVars = &r_showTris;
  }
  return atexit(_E439);
}

// FUNC: $E441
int _E441()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showDebugGraph);
  }
  else
  {
    r_showDebugGraph.next = idCVar::staticVars;
    idCVar::staticVars = &r_showDebugGraph;
  }
  return atexit(_E442);
}

// FUNC: $E444
int _E444()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showSurfaceInfo);
  }
  else
  {
    r_showSurfaceInfo.next = idCVar::staticVars;
    idCVar::staticVars = &r_showSurfaceInfo;
  }
  return atexit(_E445);
}

// FUNC: $E447
int _E447()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showBatchSize);
  }
  else
  {
    r_showBatchSize.next = idCVar::staticVars;
    idCVar::staticVars = &r_showBatchSize;
  }
  return atexit(_E448);
}

// FUNC: $E450
int _E450()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_limitBatchSize);
  }
  else
  {
    r_limitBatchSize.next = idCVar::staticVars;
    idCVar::staticVars = &r_limitBatchSize;
  }
  return atexit(_E451);
}

// FUNC: $E453
int _E453()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showNormals);
  }
  else
  {
    r_showNormals.next = idCVar::staticVars;
    idCVar::staticVars = &r_showNormals;
  }
  return atexit(_E454);
}

// FUNC: $E456
int _E456()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showMemory);
  }
  else
  {
    r_showMemory.next = idCVar::staticVars;
    idCVar::staticVars = &r_showMemory;
  }
  return atexit(_E457);
}

// FUNC: $E459
int _E459()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showCull);
  }
  else
  {
    r_showCull.next = idCVar::staticVars;
    idCVar::staticVars = &r_showCull;
  }
  return atexit(_E460);
}

// FUNC: $E462
int _E462()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showInteractions);
  }
  else
  {
    r_showInteractions.next = idCVar::staticVars;
    idCVar::staticVars = &r_showInteractions;
  }
  return atexit(_E463);
}

// FUNC: $E465
int _E465()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showDepth);
  }
  else
  {
    r_showDepth.next = idCVar::staticVars;
    idCVar::staticVars = &r_showDepth;
  }
  return atexit(_E466);
}

// FUNC: $E468
int _E468()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showSurfaces);
  }
  else
  {
    r_showSurfaces.next = idCVar::staticVars;
    idCVar::staticVars = &r_showSurfaces;
  }
  return atexit(_E469);
}

// FUNC: $E471
int _E471()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showPrimitives);
  }
  else
  {
    r_showPrimitives.next = idCVar::staticVars;
    idCVar::staticVars = &r_showPrimitives;
  }
  return atexit(_E472);
}

// FUNC: $E474
int _E474()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showEdges);
  }
  else
  {
    r_showEdges.next = idCVar::staticVars;
    idCVar::staticVars = &r_showEdges;
  }
  return atexit(_E475);
}

// FUNC: $E477
int _E477()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showTexturePolarity);
  }
  else
  {
    r_showTexturePolarity.next = idCVar::staticVars;
    idCVar::staticVars = &r_showTexturePolarity;
  }
  return atexit(_E478);
}

// FUNC: $E480
int _E480()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showTangentSpace);
  }
  else
  {
    r_showTangentSpace.next = idCVar::staticVars;
    idCVar::staticVars = &r_showTangentSpace;
  }
  return atexit(_E481);
}

// FUNC: $E483
int _E483()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showTriangleTangents);
  }
  else
  {
    r_showTriangleTangents.next = idCVar::staticVars;
    idCVar::staticVars = &r_showTriangleTangents;
  }
  return atexit(_E484);
}

// FUNC: $E486
int _E486()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showDominantTri);
  }
  else
  {
    r_showDominantTri.next = idCVar::staticVars;
    idCVar::staticVars = &r_showDominantTri;
  }
  return atexit(_E487);
}

// FUNC: $E489
int _E489()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showAlloc);
  }
  else
  {
    r_showAlloc.next = idCVar::staticVars;
    idCVar::staticVars = &r_showAlloc;
  }
  return atexit(_E490);
}

// FUNC: $E492
int _E492()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showTextureVectors);
  }
  else
  {
    r_showTextureVectors.next = idCVar::staticVars;
    idCVar::staticVars = &r_showTextureVectors;
  }
  return atexit(_E493);
}

// FUNC: $E495
int _E495()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showOverDraw);
  }
  else
  {
    r_showOverDraw.next = idCVar::staticVars;
    idCVar::staticVars = &r_showOverDraw;
  }
  return atexit(_E496);
}

// FUNC: $E498
int _E498()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_debugSphereSubdivision);
  }
  else
  {
    r_debugSphereSubdivision.next = idCVar::staticVars;
    idCVar::staticVars = &r_debugSphereSubdivision;
  }
  return atexit(_E499);
}

// FUNC: $E501
int _E501()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showSafeArea);
  }
  else
  {
    r_showSafeArea.next = idCVar::staticVars;
    idCVar::staticVars = &r_showSafeArea;
  }
  return atexit(_E502);
}

// FUNC: $E504
int _E504()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lockSurfaces);
  }
  else
  {
    r_lockSurfaces.next = idCVar::staticVars;
    idCVar::staticVars = &r_lockSurfaces;
  }
  return atexit(_E505);
}

// FUNC: $E507
int _E507()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_useEntityCallbacks);
  }
  else
  {
    r_useEntityCallbacks.next = idCVar::staticVars;
    idCVar::staticVars = &r_useEntityCallbacks;
  }
  return atexit(_E508);
}

// FUNC: $E510
int _E510()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showSkel);
  }
  else
  {
    r_showSkel.next = idCVar::staticVars;
    idCVar::staticVars = &r_showSkel;
  }
  return atexit(_E511);
}

// FUNC: $E513
int _E513()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_drawBoundInfo);
  }
  else
  {
    r_drawBoundInfo.next = idCVar::staticVars;
    idCVar::staticVars = &r_drawBoundInfo;
  }
  return atexit(_E514);
}

// FUNC: $E516
int _E516()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_jointNameScale);
  }
  else
  {
    r_jointNameScale.next = idCVar::staticVars;
    idCVar::staticVars = &r_jointNameScale;
  }
  return atexit(_E517);
}

// FUNC: $E519
int _E519()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_jointNameOffset);
  }
  else
  {
    r_jointNameOffset.next = idCVar::staticVars;
    idCVar::staticVars = &r_jointNameOffset;
  }
  return atexit(_E520);
}

// FUNC: $E522
int _E522()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_debugLineDepthTest);
  }
  else
  {
    r_debugLineDepthTest.next = idCVar::staticVars;
    idCVar::staticVars = &r_debugLineDepthTest;
  }
  return atexit(_E523);
}

// FUNC: $E525
int _E525()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_debugLineWidth);
  }
  else
  {
    r_debugLineWidth.next = idCVar::staticVars;
    idCVar::staticVars = &r_debugLineWidth;
  }
  return atexit(_E526);
}

// FUNC: $E528
int _E528()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_debugArrowStep);
  }
  else
  {
    r_debugArrowStep.next = idCVar::staticVars;
    idCVar::staticVars = &r_debugArrowStep;
  }
  return atexit(_E529);
}

// FUNC: $E531
int _E531()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_debugPolygonFilled);
  }
  else
  {
    r_debugPolygonFilled.next = idCVar::staticVars;
    idCVar::staticVars = &r_debugPolygonFilled;
  }
  return atexit(_E532);
}

// FUNC: $E534
int _E534()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_materialOverride);
  }
  else
  {
    r_materialOverride.next = idCVar::staticVars;
    idCVar::staticVars = &r_materialOverride;
  }
  return atexit(_E535);
}

// FUNC: $E537
int _E537()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_debugRenderToTexture);
  }
  else
  {
    r_debugRenderToTexture.next = idCVar::staticVars;
    idCVar::staticVars = &r_debugRenderToTexture;
  }
  return atexit(_E538);
}

// FUNC: $E540
int _E540()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_actualRenderer);
  }
  else
  {
    r_actualRenderer.next = idCVar::staticVars;
    idCVar::staticVars = &r_actualRenderer;
  }
  return atexit(_E541);
}

// FUNC: $E543
int _E543()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_test);
  }
  else
  {
    r_test.next = idCVar::staticVars;
    idCVar::staticVars = &r_test;
  }
  return atexit(_E544);
}

// FUNC: $E546
int _E546()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipDecals);
  }
  else
  {
    r_skipDecals.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipDecals;
  }
  return atexit(_E547);
}

// FUNC: $E549
int _E549()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_suppressMultipleUpdates);
  }
  else
  {
    r_suppressMultipleUpdates.next = idCVar::staticVars;
    idCVar::staticVars = &r_suppressMultipleUpdates;
  }
  return atexit(_E550);
}

// FUNC: $E552
int _E552()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_inhibitNativePowerOfTwo);
  }
  else
  {
    r_inhibitNativePowerOfTwo.next = idCVar::staticVars;
    idCVar::staticVars = &r_inhibitNativePowerOfTwo;
  }
  return atexit(_E553);
}

// FUNC: $E555
int _E555()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lod_shadows);
  }
  else
  {
    r_lod_shadows.next = idCVar::staticVars;
    idCVar::staticVars = &r_lod_shadows;
  }
  return atexit(_E556);
}

// FUNC: $E558
int _E558()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lod_entities);
  }
  else
  {
    r_lod_entities.next = idCVar::staticVars;
    idCVar::staticVars = &r_lod_entities;
  }
  return atexit(_E559);
}

// FUNC: $E561
int _E561()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lod_shadows_percent);
  }
  else
  {
    r_lod_shadows_percent.next = idCVar::staticVars;
    idCVar::staticVars = &r_lod_shadows_percent;
  }
  return atexit(_E562);
}

// FUNC: $E564
int _E564()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lod_entities_percent);
  }
  else
  {
    r_lod_entities_percent.next = idCVar::staticVars;
    idCVar::staticVars = &r_lod_entities_percent;
  }
  return atexit(_E565);
}

// FUNC: $E567
int _E567()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lod_animations_distance);
  }
  else
  {
    r_lod_animations_distance.next = idCVar::staticVars;
    idCVar::staticVars = &r_lod_animations_distance;
  }
  return atexit(_E568);
}

// FUNC: $E570
int _E570()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lod_animations_wait);
  }
  else
  {
    r_lod_animations_wait.next = idCVar::staticVars;
    idCVar::staticVars = &r_lod_animations_wait;
  }
  return atexit(_E571);
}

// FUNC: $E573
int _E573()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_lod_animations_coverage);
  }
  else
  {
    r_lod_animations_coverage.next = idCVar::staticVars;
    idCVar::staticVars = &r_lod_animations_coverage;
  }
  return atexit(_E574);
}

// FUNC: $E576
int _E576()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showOverdrawMax);
  }
  else
  {
    r_showOverdrawMax.next = idCVar::staticVars;
    idCVar::staticVars = &r_showOverdrawMax;
  }
  return atexit(_E577);
}

// FUNC: $E579
int _E579()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showOverdrawDivisor);
  }
  else
  {
    r_showOverdrawDivisor.next = idCVar::staticVars;
    idCVar::staticVars = &r_showOverdrawDivisor;
  }
  return atexit(_E580);
}

// FUNC: $E582
int _E582()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showUnweld);
  }
  else
  {
    r_showUnweld.next = idCVar::staticVars;
    idCVar::staticVars = &r_showUnweld;
  }
  return atexit(_E583);
}

// FUNC: $E585
int _E585()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showLightPortals);
  }
  else
  {
    r_showLightPortals.next = idCVar::staticVars;
    idCVar::staticVars = &r_showLightPortals;
  }
  return atexit(_E586);
}

// FUNC: $E588
int _E588()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showEditorImages);
  }
  else
  {
    r_showEditorImages.next = idCVar::staticVars;
    idCVar::staticVars = &r_showEditorImages;
  }
  return atexit(_E589);
}

// FUNC: $E591
int _E591()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_showHitImages);
  }
  else
  {
    r_showHitImages.next = idCVar::staticVars;
    idCVar::staticVars = &r_showHitImages;
  }
  return atexit(_E592);
}

// FUNC: $E594
int _E594()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_skipTextures);
  }
  else
  {
    r_skipTextures.next = idCVar::staticVars;
    idCVar::staticVars = &r_skipTextures;
  }
  return atexit(_E595);
}

// FUNC: $E597
int _E597()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_portalsDistanceCull);
  }
  else
  {
    r_portalsDistanceCull.next = idCVar::staticVars;
    idCVar::staticVars = &r_portalsDistanceCull;
  }
  return atexit(_E598);
}

// FUNC: $E600
int _E600()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_videoCard);
  }
  else
  {
    r_videoCard.next = idCVar::staticVars;
    idCVar::staticVars = &r_videoCard;
  }
  return atexit(_E601);
}

// FUNC: $E603
int _E603()
{
  if ( idCVar::staticVars == (idCVar *)-1 )
  {
    cvarSystem->Register(cvarSystem, &r_trackTextureUsage);
  }
  else
  {
    r_trackTextureUsage.next = idCVar::staticVars;
    idCVar::staticVars = &r_trackTextureUsage;
  }
  return atexit(_E604);
}

// FUNC: $E606
idCVarHelp *_E606()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showPrimitives);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showPrimitives;
  else
    idCVarHelp::staticCVarHelps = &help_r_showPrimitives;
  idCVarHelp::staticCVarHelpsTail = &help_r_showPrimitives;
  help_r_showPrimitives.next = 0;
  return result;
}

// FUNC: $E608
idCVarHelp *_E608()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showDefs);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showDefs;
  else
    idCVarHelp::staticCVarHelps = &help_r_showDefs;
  idCVarHelp::staticCVarHelpsTail = &help_r_showDefs;
  help_r_showDefs.next = 0;
  return result;
}

// FUNC: $E610
idCVarHelp *_E610()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showTris);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showTris;
  else
    idCVarHelp::staticCVarHelps = &help_r_showTris;
  idCVarHelp::staticCVarHelpsTail = &help_r_showTris;
  help_r_showTris.next = 0;
  return result;
}

// FUNC: $E612
idCVarHelp *_E612()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showLights);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showLights;
  else
    idCVarHelp::staticCVarHelps = &help_r_showLights;
  idCVarHelp::staticCVarHelpsTail = &help_r_showLights;
  help_r_showLights.next = 0;
  return result;
}

// FUNC: $E614
idCVarHelp *_E614()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showUnsmoothedTangents);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showUnsmoothedTangents;
  else
    idCVarHelp::staticCVarHelps = &help_r_showUnsmoothedTangents;
  idCVarHelp::staticCVarHelpsTail = &help_r_showUnsmoothedTangents;
  help_r_showUnsmoothedTangents.next = 0;
  return result;
}

// FUNC: $E616
idCVarHelp *_E616()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showOverDraw);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showOverDraw;
  else
    idCVarHelp::staticCVarHelps = &help_r_showOverDraw;
  idCVarHelp::staticCVarHelpsTail = &help_r_showOverDraw;
  help_r_showOverDraw.next = 0;
  return result;
}

// FUNC: $E618
idCVarHelp *_E618()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showPortals);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showPortals;
  else
    idCVarHelp::staticCVarHelps = &help_r_showPortals;
  idCVarHelp::staticCVarHelpsTail = &help_r_showPortals;
  help_r_showPortals.next = 0;
  return result;
}

// FUNC: $E620
idCVarHelp *_E620()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showLightPortals);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showLightPortals;
  else
    idCVarHelp::staticCVarHelps = &help_r_showLightPortals;
  idCVarHelp::staticCVarHelpsTail = &help_r_showLightPortals;
  help_r_showLightPortals.next = 0;
  return result;
}

// FUNC: $E622
idCVarHelp *_E622()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_lockSurfaces);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_lockSurfaces;
  else
    idCVarHelp::staticCVarHelps = &help_r_lockSurfaces;
  idCVarHelp::staticCVarHelpsTail = &help_r_lockSurfaces;
  help_r_lockSurfaces.next = 0;
  return result;
}

// FUNC: $E624
idCVarHelp *_E624()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showEditorImages);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showEditorImages;
  else
    idCVarHelp::staticCVarHelps = &help_r_showEditorImages;
  idCVarHelp::staticCVarHelpsTail = &help_r_showEditorImages;
  help_r_showEditorImages.next = 0;
  return result;
}

// FUNC: $E626
idCVarHelp *_E626()
{
  idCVarHelp *result; // eax

  if ( idCVarHelp::staticCVarHelps == (idCVarHelp *)-1 )
    return (idCVarHelp *)(*(int (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(
                           cvarSystem,
                           &help_r_showHitImages);
  result = idCVarHelp::staticCVarHelpsTail;
  if ( idCVarHelp::staticCVarHelpsTail )
    idCVarHelp::staticCVarHelpsTail->next = &help_r_showHitImages;
  else
    idCVarHelp::staticCVarHelps = &help_r_showHitImages;
  idCVarHelp::staticCVarHelpsTail = &help_r_showHitImages;
  help_r_showHitImages.next = 0;
  return result;
}

// FUNC: $E632
void _E632()
{
  idMat3 *v0; // esi
  int v1; // edi

  v0 = cubeAxis;
  v1 = 6;
  do
  {
    `vector constructor iterator'(v0++, 0xCu, 3, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
    --v1;
  }
  while ( v1 );
}
