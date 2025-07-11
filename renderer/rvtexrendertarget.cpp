
// FUNC: private: void __thiscall rvTexRenderTarget::ResetValues(void)
void __thiscall rvTexRenderTarget::ResetValues(rvTexRenderTarget *this)
{
  this->m_hPBuffer = 0;
  this->m_hDC = 0;
  rvTexRenderTarget::m_hPrevDC = 0;
  this->m_textureObjName = 0;
  this->m_resWidth = 0;
  this->m_resHeight = 0;
  this->m_flags = 0;
  this->m_numRedBits = 0;
  this->m_numGreenBits = 0;
  this->m_numBlueBits = 0;
  this->m_numAlphaBits = 0;
  this->m_numDepthBits = 0;
  this->m_numStencilBits = 0;
  this->m_target = 3553;
}

// FUNC: public: void __thiscall rvTexRenderTarget::EndRender(bool)
void __thiscall rvTexRenderTarget::EndRender(rvTexRenderTarget *this, bool RestorePreviousDC)
{
  int v2; // esi
  DWORD LastError; // eax

  if ( RestorePreviousDC )
  {
    if ( !qwglMakeCurrent(rvTexRenderTarget::m_hPrevDC, rvTexRenderTarget::m_hPrevGLRC) )
    {
      v2 = *(_DWORD *)common.type;
      LastError = GetLastError();
      (*(void (**)(netadrtype_t, const char *, ...))(v2 + 156))(
        common.type,
        "qwglMakeCurrent(m_hPrevDC, m_hPrevGLRC) failed, last error %x\n",
        LastError);
    }
    qglDrawBuffer(rvTexRenderTarget::m_prevDrawBuffer);
    qglReadBuffer(rvTexRenderTarget::m_prevReadBuffer);
    qglViewport(rvTexRenderTarget::m_prevViewport[0], dword_110DA338, dword_110DA33C, dword_110DA340);
    rvTexRenderTarget::m_hPrevDC = 0;
    rvTexRenderTarget::m_hPrevGLRC = 0;
  }
}

// FUNC: public: void __thiscall rvTexRenderTarget::EndTexture(void)
void __thiscall rvTexRenderTarget::EndTexture(rvTexRenderTarget *this)
{
  qwglReleaseTexImageARB(this->m_hPBuffer, 8323);
  this->m_textureObjName = 0;
}

// FUNC: public: __thiscall rvTexRenderTarget::rvTexRenderTarget(void)
void __thiscall rvTexRenderTarget::rvTexRenderTarget(rvTexRenderTarget *this)
{
  this->m_hPBuffer = 0;
  this->m_hDC = 0;
  rvTexRenderTarget::m_hPrevDC = 0;
  this->m_textureObjName = 0;
  this->m_resWidth = 0;
  this->m_resHeight = 0;
  this->m_flags = 0;
  this->m_numRedBits = 0;
  this->m_numGreenBits = 0;
  this->m_numBlueBits = 0;
  this->m_numAlphaBits = 0;
  this->m_numDepthBits = 0;
  this->m_numStencilBits = 0;
  this->m_target = 3553;
}

// FUNC: public: bool __thiscall rvTexRenderTarget::Init(int,int,int,int,int,int,int,int,int,int)
char __thiscall rvTexRenderTarget::Init(
        rvTexRenderTarget *this,
        int resWidth,
        int resHeight,
        int numColorBits,
        int numRedBits,
        int numGreenBits,
        int numBlueBits,
        int numAlphaBits,
        int numDepthBits,
        int numStencilBits,
        int flags)
{
  int v12; // eax
  BOOL v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // esi
  DWORD LastError; // eax
  int v22; // eax
  int v23; // ecx
  HDC__ *v24; // edx
  int v25; // eax
  HPBUFFERARB__ *PbufferARB; // eax
  int v27; // esi
  DWORD v28; // eax
  HDC__ *PbufferDCARB; // eax
  HGLRC__ *Context; // eax
  unsigned int count; // [esp+10h] [ebp-70h] BYREF
  HDC__ *hdc; // [esp+14h] [ebp-6Ch]
  int pixelFormatIndex; // [esp+18h] [ebp-68h] BYREF
  HGLRC__ *glRC; // [esp+1Ch] [ebp-64h]
  int attributePairs[24]; // [esp+20h] [ebp-60h] BYREF

  hdc = qwglGetCurrentDC();
  glRC = qwglGetCurrentContext();
  attributePairs[0] = 8237;
  attributePairs[1] = 1;
  if ( (flags & 2) != 0 )
  {
    attributePairs[2] = 8368;
    attributePairs[3] = 1;
    v12 = 5;
    if ( numAlphaBits )
    {
      attributePairs[4] = 8372;
    }
    else if ( numBlueBits )
    {
      attributePairs[4] = 8371;
    }
    else if ( numGreenBits )
    {
      attributePairs[4] = 8370;
    }
    else
    {
      attributePairs[4] = 8369;
    }
  }
  else
  {
    v13 = numAlphaBits != 0;
    if ( (flags & 0xC) != 0 )
      v14 = v13 + 8304;
    else
      v14 = v13 + 8352;
    attributePairs[2] = v14;
    v12 = 3;
  }
  attributePairs[v12] = 1;
  v15 = v12 + 1;
  attributePairs[v15++] = 8212;
  attributePairs[v15] = numColorBits;
  attributePairs[++v15] = 8213;
  attributePairs[++v15] = numRedBits;
  attributePairs[++v15] = 8215;
  attributePairs[v15 + 1] = numGreenBits;
  v15 += 2;
  attributePairs[v15++] = 8217;
  attributePairs[v15++] = numBlueBits;
  attributePairs[v15++] = 8219;
  attributePairs[v15] = numAlphaBits;
  v16 = v15 + 1;
  if ( (flags & 1) != 0 )
  {
    attributePairs[v16] = 8226;
    v17 = v16 + 1;
    attributePairs[v17++] = numDepthBits;
    attributePairs[v17++] = 8227;
    attributePairs[v17] = numStencilBits;
    v16 = v17 + 1;
  }
  attributePairs[v16] = 0;
  v18 = v16 + 1;
  attributePairs[v18] = 0;
  count = v18 + 1;
  if ( !qwglChoosePixelFormatARB(hdc, attributePairs, 0, 1u, &pixelFormatIndex, &count) )
  {
    v19 = *(_DWORD *)common.type;
    LastError = GetLastError();
    (*(void (**)(netadrtype_t, const char *, ...))(v19 + 136))(
      common.type,
      "qwglChoosePixelFormatARB() failed, last error %x\n",
      LastError);
    return 0;
  }
  if ( !count )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "qwglChoosePixelFormatARB() couldn't find any matches\n");
    return 0;
  }
  attributePairs[0] = 8307;
  if ( (flags & 4) != 0 )
  {
    attributePairs[1] = 8312;
    this->m_target = 34067;
  }
  else if ( (flags & 8) != 0 )
  {
    attributePairs[1] = 8314;
    this->m_target = 3553;
  }
  else
  {
    attributePairs[1] = 8354;
    this->m_target = 34037;
  }
  attributePairs[2] = 8306;
  if ( (flags & 2) == 0 )
  {
    attributePairs[3] = (numAlphaBits != 0) + 8309;
    goto LABEL_33;
  }
  if ( numAlphaBits )
  {
    attributePairs[3] = 8376;
LABEL_33:
    v22 = 4;
    goto LABEL_34;
  }
  if ( numBlueBits )
  {
    attributePairs[3] = 8375;
    goto LABEL_33;
  }
  v22 = 4;
  if ( numGreenBits )
    attributePairs[3] = 8374;
  else
    attributePairs[3] = 8373;
LABEL_34:
  if ( (flags & 8) != 0 )
  {
    attributePairs[4] = 8308;
    attributePairs[5] = 1;
    v22 = 6;
  }
  v23 = pixelFormatIndex;
  v24 = hdc;
  attributePairs[v22] = 0;
  v25 = v22 + 1;
  attributePairs[v25] = 0;
  count = v25 + 1;
  PbufferARB = qwglCreatePbufferARB(v24, v23, resWidth, resHeight, attributePairs);
  this->m_hPBuffer = PbufferARB;
  if ( !PbufferARB )
  {
    v27 = *(_DWORD *)common.type;
    v28 = GetLastError();
    (*(void (**)(netadrtype_t, const char *, ...))(v27 + 136))(
      common.type,
      "qwglCreatePbufferARB() failed, last error %x\n",
      v28);
    return 0;
  }
  PbufferDCARB = qwglGetPbufferDCARB(PbufferARB);
  this->m_hDC = PbufferDCARB;
  if ( !PbufferDCARB )
    goto LABEL_44;
  Context = qwglCreateContext(PbufferDCARB);
  this->m_hGLRC = Context;
  if ( !Context )
  {
LABEL_43:
    qwglReleasePbufferDCARB(this->m_hPBuffer, this->m_hDC);
LABEL_44:
    qwglDestroyPbufferARB(this->m_hPBuffer);
    rvTexRenderTarget::ResetValues(this);
    return 0;
  }
  if ( glRC && !qwglShareLists(glRC, Context) )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "qwglShareLists() couldn't share display list resources\n");
    qwglDeleteContext(this->m_hGLRC);
    goto LABEL_43;
  }
  this->m_flagsSave = flags;
  this->m_flags = flags;
  this->m_numColorBitsSave = numColorBits;
  this->m_numColorBits = numColorBits;
  this->m_numRedBitsSave = numRedBits;
  this->m_numRedBits = numRedBits;
  this->m_numGreenBitsSave = numGreenBits;
  this->m_numGreenBits = numGreenBits;
  this->m_numBlueBitsSave = numBlueBits;
  this->m_numBlueBits = numBlueBits;
  this->m_numDepthBitsSave = numDepthBits;
  this->m_numDepthBits = numDepthBits;
  this->m_resHeightSave = resHeight;
  this->m_resHeight = resHeight;
  this->m_resWidthSave = resWidth;
  this->m_resWidth = resWidth;
  this->m_numAlphaBitsSave = numAlphaBits;
  this->m_numAlphaBits = numAlphaBits;
  this->m_numStencilBitsSave = numStencilBits;
  this->m_numStencilBits = numStencilBits;
  return 1;
}

// FUNC: public: void __thiscall rvTexRenderTarget::Release(void)
void __thiscall rvTexRenderTarget::Release(rvTexRenderTarget *this)
{
  if ( this->m_hPBuffer )
  {
    if ( this->m_hDC )
    {
      if ( this->m_hGLRC )
        qwglDeleteContext(this->m_hGLRC);
      qwglReleasePbufferDCARB(this->m_hPBuffer, this->m_hDC);
    }
    qwglDestroyPbufferARB(this->m_hPBuffer);
  }
  this->m_hPBuffer = 0;
  this->m_hDC = 0;
  rvTexRenderTarget::m_hPrevDC = 0;
  this->m_textureObjName = 0;
  this->m_resWidth = 0;
  this->m_resHeight = 0;
  this->m_flags = 0;
  this->m_numRedBits = 0;
  this->m_numGreenBits = 0;
  this->m_numBlueBits = 0;
  this->m_numAlphaBits = 0;
  this->m_numDepthBits = 0;
  this->m_numStencilBits = 0;
  this->m_target = 3553;
}

// FUNC: public: bool __thiscall rvTexRenderTarget::Restore(void)
char __thiscall rvTexRenderTarget::Restore(rvTexRenderTarget *this)
{
  return rvTexRenderTarget::Init(
           this,
           this->m_resWidthSave,
           this->m_resHeightSave,
           this->m_numColorBitsSave,
           this->m_numRedBitsSave,
           this->m_numGreenBitsSave,
           this->m_numBlueBitsSave,
           this->m_numAlphaBitsSave,
           this->m_numDepthBitsSave,
           this->m_numStencilBitsSave,
           this->m_flagsSave);
}

// FUNC: public: void __thiscall rvTexRenderTarget::BeginRender(int)
void __thiscall rvTexRenderTarget::BeginRender(rvTexRenderTarget *this, int cubeFace)
{
  HPBUFFERARB__ *m_hPBuffer; // eax
  int v4; // ebx
  DWORD LastError; // eax
  int attributePairs[4]; // [esp+4h] [ebp-10h] BYREF

  if ( this->m_textureObjName )
  {
    qwglReleaseTexImageARB(this->m_hPBuffer, 8323);
    this->m_textureObjName = 0;
  }
  if ( !rvTexRenderTarget::m_hPrevDC && !rvTexRenderTarget::m_hPrevGLRC )
  {
    rvTexRenderTarget::m_hPrevDC = qwglGetCurrentDC();
    rvTexRenderTarget::m_hPrevGLRC = qwglGetCurrentContext();
    qglGetIntegerv(0xC01u, (int *)&rvTexRenderTarget::m_prevDrawBuffer);
    qglGetIntegerv(0xC02u, (int *)&rvTexRenderTarget::m_prevReadBuffer);
    qglGetIntegerv(0xBA2u, rvTexRenderTarget::m_prevViewport);
  }
  if ( (this->m_flags & 4) != 0 )
  {
    m_hPBuffer = this->m_hPBuffer;
    attributePairs[0] = 8316;
    attributePairs[1] = cubeFace;
    attributePairs[2] = 0;
    attributePairs[3] = 0;
    qwglSetPbufferAttribARB(m_hPBuffer, attributePairs);
  }
  if ( !qwglMakeCurrent(this->m_hDC, this->m_hGLRC) )
  {
    v4 = *(_DWORD *)common.type;
    LastError = GetLastError();
    (*(void (**)(netadrtype_t, const char *, ...))(v4 + 156))(
      common.type,
      "qwglMakeCurrent(m_hDC, m_hGLRC) failed, last error %x\n",
      LastError);
  }
  qglDrawBuffer(0x404u);
  qglReadBuffer(0x404u);
  qglViewport(0, 0, this->m_resWidth, this->m_resHeight);
}

// FUNC: public: void __thiscall rvTexRenderTarget::BeginTexture(unsigned int,int,int,int)
void __thiscall rvTexRenderTarget::BeginTexture(
        rvTexRenderTarget *this,
        unsigned int textureObjName,
        int minFilter,
        int magFilter,
        int wrap)
{
  if ( this->m_textureObjName )
  {
    qwglReleaseTexImageARB(this->m_hPBuffer, 8323);
    this->m_textureObjName = 0;
  }
  qglBindTexture(this->m_target, textureObjName);
  qglTexParameteri(this->m_target, 0x2801u, minFilter);
  qglTexParameteri(this->m_target, 0x2800u, magFilter);
  qglTexParameteri(this->m_target, 0x2802u, wrap);
  qglTexParameteri(this->m_target, 0x2803u, wrap);
  qwglBindTexImageARB(this->m_hPBuffer, 8323);
  this->m_textureObjName = textureObjName;
}

// FUNC: public: __thiscall rvTexRenderTarget::~rvTexRenderTarget(void)
// attributes: thunk
void __thiscall rvTexRenderTarget::~rvTexRenderTarget(rvTexRenderTarget *this)
{
  rvTexRenderTarget::Release(this);
}

// FUNC: public: void __thiscall rvTexRenderTarget::DefaultD3GL(void)
void __thiscall rvTexRenderTarget::DefaultD3GL(rvTexRenderTarget *this)
{
  rvTexRenderTarget::BeginRender(this, 0);
  qglClearDepth(1.0);
  qglClear(0x4100u);
  qglEnable(0xB71u);
  qglDisable(0xBC0u);
  qglDepthFunc(0x203u);
  qglMatrixMode(0x1700u);
  qglLoadIdentity();
  qglMatrixMode(0x1701u);
  qglLoadIdentity();
  qglEnableClientState(0x8074u);
  qglDisableClientState(0x8075u);
  qglEnableClientState(0x8078u);
  qglDisableClientState(0x8076u);
  qglShadeModel(0x1D01u);
  qglCullFace(0x405u);
  qglEnable(0xB44u);
  qglDisable(0xBE2u);
  qglDisable(0xB50u);
  qglDisable(0xDE1u);
  rvTexRenderTarget::EndRender(this, 1);
}
