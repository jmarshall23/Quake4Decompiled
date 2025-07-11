
// FUNC: GLimp_SaveGamma
int GLimp_SaveGamma()
{
  idSys_vtbl *v0; // esi
  HWND DesktopWindow; // eax
  HDC v2; // esi
  BOOL DeviceGammaRamp; // eax
  const char *v4; // ecx
  idSys_vtbl *v5; // ebx
  HWND v6; // eax

  v0 = sys->__vftable;
  DesktopWindow = GetDesktopWindow();
  v2 = (HDC)v0->GetDC(sys, DesktopWindow);
  DeviceGammaRamp = GetDeviceGammaRamp(v2, win32.oldHardwareGamma);
  v4 = "success";
  if ( !DeviceGammaRamp )
    v4 = "failed";
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "...getting default gamma ramp: %s\n",
    v4);
  v5 = sys->__vftable;
  v6 = GetDesktopWindow();
  return ((int (__thiscall *)(idSys *, HWND, HDC))v5->ReleaseDC)(sys, v6, v2);
}

// FUNC: GLimp_RestoreGamma
void __usercall GLimp_RestoreGamma(int a1@<edi>, int a2@<esi>)
{
  idSys_vtbl *v2; // esi
  HWND DesktopWindow; // eax
  HDC v4; // esi
  BOOL v5; // eax
  const char *v6; // ecx
  idSys_vtbl *v7; // ebx
  HWND v8; // eax

  if ( win32.oldHardwareGamma[0][255] )
  {
    v2 = sys->__vftable;
    DesktopWindow = GetDesktopWindow();
    v4 = (HDC)((int (__thiscall *)(idSys *, HWND, int, int))v2->GetDC)(sys, DesktopWindow, a1, a2);
    v5 = SetDeviceGammaRamp(v4, win32.oldHardwareGamma);
    v6 = "success";
    if ( !v5 )
      v6 = "failed";
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "...restoring hardware gamma: %s\n",
      v6);
    v7 = sys->__vftable;
    v8 = GetDesktopWindow();
    ((void (__thiscall *)(idSys *, HWND))v7->ReleaseDC)(sys, v8);
  }
}

// FUNC: void __cdecl GLimp_SetGamma(unsigned short * const,unsigned short * const,unsigned short * const)
void __cdecl GLimp_SetGamma(unsigned __int16 *red, unsigned __int16 *green, unsigned __int16 *blue)
{
  HDC__ *hDC; // edi
  int i; // eax
  unsigned __int16 table[3][256]; // [esp+4h] [ebp-600h] BYREF

  hDC = win32.hDC;
  if ( win32.hDC )
  {
    for ( i = 0; i < 256; ++i )
    {
      table[0][i] = *(unsigned __int16 *)((char *)&table[0][i] + (char *)red - (char *)table);
      table[1][i] = *(unsigned __int16 *)((char *)&table[0][i] + (char *)green - (char *)table);
      table[2][i] = *(unsigned __int16 *)((char *)&table[0][i] + (char *)blue - (char *)table);
    }
    if ( !SetDeviceGammaRamp(hDC, table) )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "WARNING: SetDeviceGammaRamp failed.\n");
  }
}

// FUNC: long __stdcall FakeWndProc(struct HWND__ *,unsigned int,unsigned int,long)
LRESULT __stdcall FakeWndProc(HWND__ *hWnd, unsigned int uMsg, unsigned int wParam, int lParam)
{
  HDC__ *v5; // esi
  int v6; // eax
  HGLRC__ *Context; // ebx

  if ( uMsg == 2 )
  {
    PostQuitMessage(0);
    return DefWindowProcA(hWnd, uMsg, wParam, lParam);
  }
  if ( uMsg != 1 )
    return DefWindowProcA(hWnd, uMsg, wParam, lParam);
  v5 = (HDC__ *)sys->GetDC(sys, hWnd);
  v6 = ChoosePixelFormat(v5, &pfd);
  SetPixelFormat(v5, v6, &pfd);
  Context = qwglCreateContext(v5);
  qwglMakeCurrent(v5, Context);
  wglMakeCurrent(0, 0);
  wglDeleteContext(Context);
  sys->ReleaseDC(sys, hWnd, v5);
  return DefWindowProcA(hWnd, 1u, wParam, lParam);
}

// FUNC: GLW_InitDriver
char __cdecl GLW_InitDriver(glimpParms_t parms)
{
  int v2; // eax
  bool v3; // zf
  int v4; // ecx
  tagPIXELFORMATDESCRIPTOR src; // [esp+4h] [ebp-84h] BYREF
  float fAttributes[2]; // [esp+2Ch] [ebp-5Ch] BYREF
  int iAttributes[20]; // [esp+34h] [ebp-54h] BYREF
  unsigned int numFormats; // [esp+84h] [ebp-4h] BYREF

  src.nSize = 40;
  src.nVersion = 1;
  src.dwFlags = 37;
  src.iPixelType = 0;
  src.cColorBits = 32;
  src.cRedBits = 0;
  src.cRedShift = 0;
  src.cGreenBits = 0;
  src.cGreenShift = 0;
  src.cBlueBits = 0;
  src.cBlueShift = 0;
  src.cAlphaBits = 8;
  src.cAlphaShift = 0;
  src.cAccumBits = 0;
  src.cAccumRedBits = 0;
  src.cAccumGreenBits = 0;
  src.cAccumBlueBits = 0;
  src.cAccumAlphaBits = 0;
  src.cDepthBits = 24;
  src.cStencilBits = 8;
  memset(&src.cAuxBuffers, 0, 15);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Initializing OpenGL driver\n");
  if ( !win32.hDC )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "...getting DC: ");
    win32.hDC = (HDC__ *)sys->GetDC(sys, win32.hWnd);
    if ( !win32.hDC )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "^3failed^0\n");
      return 0;
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
  }
  if ( wglChoosePixelFormatARB && parms.multiSamples > 1 )
  {
    iAttributes[3] = parms.multiSamples;
    fAttributes[0] = 0.0;
    fAttributes[1] = 0.0;
    iAttributes[0] = 8257;
    iAttributes[1] = 1;
    iAttributes[2] = 8258;
    iAttributes[4] = 8209;
    iAttributes[5] = 1;
    iAttributes[6] = 8227;
    iAttributes[7] = 8;
    iAttributes[8] = 8226;
    iAttributes[9] = 24;
    iAttributes[10] = 8213;
    iAttributes[11] = 8;
    iAttributes[12] = 8217;
    iAttributes[13] = 8;
    iAttributes[14] = 8215;
    iAttributes[15] = 8;
    iAttributes[16] = 8219;
    iAttributes[17] = 8;
    iAttributes[18] = 0;
    iAttributes[19] = 0;
    wglChoosePixelFormatARB(win32.hDC, iAttributes, fAttributes, 1u, &win32.pixelformat, &numFormats);
  }
  else
  {
    if ( parms.stereo )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "...attempting to use stereo\n");
      src.dwFlags |= 2u;
    }
    v2 = ChoosePixelFormat(win32.hDC, &src);
    win32.pixelformat = v2;
    if ( !v2 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "...^3GLW_ChoosePFD failed^0\n");
      return 0;
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...PIXELFORMAT %d selected\n",
      v2);
  }
  DescribePixelFormat(win32.hDC, win32.pixelformat, 0x28u, &win32.pfd);
  glConfig.depthBits = win32.pfd.cDepthBits;
  glConfig.colorBits = win32.pfd.cColorBits;
  glConfig.stencilBits = win32.pfd.cStencilBits;
  glConfig.alphaBits = win32.pfd.cAlphaBits;
  if ( !win32.pfd.cStencilBits )
    glConfig.stencilBits = 8;
  v3 = !SetPixelFormat(win32.hDC, win32.pixelformat, &win32.pfd);
  v4 = *(_DWORD *)common.type;
  if ( v3 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *, HDC__ *))(v4 + 124))(
      common.type,
      "...^3SetPixelFormat failed^0\n",
      win32.hDC);
    return 0;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(v4 + 124))(common.type, "...creating GL context: ");
    win32.hGLRC = qwglCreateContext(win32.hDC);
    if ( win32.hGLRC )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "...making context current: ");
      if ( qwglMakeCurrent(win32.hDC, win32.hGLRC) )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "succeeded\n");
        return 1;
      }
      else
      {
        qwglDeleteContext(win32.hGLRC);
        win32.hGLRC = 0;
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "^3failed^0\n");
        return 0;
      }
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "^3failed^0\n");
      return 0;
    }
  }
}

// FUNC: GLW_CreateWindowClasses
void GLW_CreateWindowClasses()
{
  tagWNDCLASSA wc; // [esp+4h] [ebp-28h] BYREF

  if ( !win32.windowClassRegistered )
  {
    wc.style = 0;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = win32.hInstance;
    wc.hIcon = LoadIconA(win32.hInstance, (LPCSTR)0x400);
    wc.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
    wc.hbrBackground = (HBRUSH__ *)17;
    wc.lpszMenuName = 0;
    wc.lpszClassName = "Quake4";
    if ( !RegisterClassA(&wc) )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "GLW_CreateWindow: could not register window class");
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "...registered window class\n");
    wc.style = 0;
    wc.lpfnWndProc = FakeWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = win32.hInstance;
    wc.hIcon = LoadIconA(win32.hInstance, (LPCSTR)0x400);
    wc.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
    wc.hbrBackground = (HBRUSH__ *)17;
    wc.lpszMenuName = 0;
    wc.lpszClassName = "QUAKE4_WGL_FAKE";
    if ( !RegisterClassA(&wc) )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "GLW_CreateWindow: could not register window class");
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "...registered fake window class\n");
    win32.windowClassRegistered = 1;
  }
}

// FUNC: PrintCDSError
void __thiscall PrintCDSError(void *value)
{
  switch ( (unsigned int)value )
  {
    case 0xFFFFFFFB:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "bad param\n");
      break;
    case 0xFFFFFFFC:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "bad flags\n");
      break;
    case 0xFFFFFFFD:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "not updated\n");
      break;
    case 0xFFFFFFFE:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "bad mode\n");
      break;
    case 0xFFFFFFFF:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "DISP_CHANGE_FAILED\n");
      break;
    case 1u:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "restart required\n");
      break;
    default:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "unknown error %d\n",
        value);
      break;
  }
}

// FUNC: GLW_SetFullScreen
char __cdecl GLW_SetFullScreen(glimpParms_t parms)
{
  int v1; // edi
  char v2; // bl
  int displayHz; // esi
  void *v4; // esi
  netadrtype_t type; // eax
  int v6; // esi
  _devicemodeA devmode; // [esp+10h] [ebp-138h] BYREF
  _devicemodeA dm; // [esp+ACh] [ebp-9Ch] BYREF

  v1 = 0;
  v2 = 0;
  if ( EnumDisplaySettingsA(0, 0, &devmode) )
  {
    displayHz = parms.displayHz;
    while ( 1 )
    {
      if ( (int)devmode.dmPelsWidth >= parms.width
        && (int)devmode.dmPelsHeight >= parms.height
        && devmode.dmBitsPerPel == 32 )
      {
        v2 = 1;
        if ( !parms.displayHz || devmode.dmDisplayFrequency == parms.displayHz )
          break;
      }
      if ( !EnumDisplaySettingsA(0, ++v1, &devmode) )
      {
        if ( !v2 )
          goto LABEL_20;
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "...^3%dhz is unsupported at %dx%d^0\n",
          parms.displayHz,
          parms.width,
          parms.height);
        displayHz = 0;
        break;
      }
    }
    memset(&dm, 0, sizeof(dm));
    dm.dmSize = 156;
    dm.dmPelsWidth = parms.width;
    dm.dmPelsHeight = parms.height;
    dm.dmBitsPerPel = 32;
    dm.dmFields = 1835008;
    if ( displayHz )
    {
      dm.dmDisplayFrequency = displayHz;
      dm.dmFields = 6029312;
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "...calling CDS: ");
    v4 = (void *)ChangeDisplaySettingsA(&dm, 4u);
    type = common.type;
    if ( v4 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "^3failed^0, ");
      PrintCDSError(v4);
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "...trying next higher resolution:");
      v6 = 0;
      if ( !EnumDisplaySettingsA(0, 0, &devmode) )
        goto LABEL_19;
      while ( (int)devmode.dmPelsWidth < parms.width
           || (int)devmode.dmPelsHeight < parms.height
           || devmode.dmBitsPerPel != 32 )
      {
        if ( !EnumDisplaySettingsA(0, ++v6, &devmode) )
          goto LABEL_19;
      }
      if ( ChangeDisplaySettingsA(&devmode, 4u) )
      {
LABEL_19:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "\n...^3no high res mode found^0\n");
        return 0;
      }
      type = common.type;
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)type + 124))(type, "ok\n");
    win32.cdsFullscreen = 1;
    return 1;
  }
  else
  {
LABEL_20:
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...^3%dx%d is unsupported in 32 bit^0\n",
      parms.width,
      parms.height);
    return 0;
  }
}

// FUNC: void __cdecl GLimp_Shutdown(void)
void __usercall GLimp_Shutdown(int a1@<edi>, int a2@<esi>)
{
  int v2; // ecx
  int Current; // eax
  int v4; // eax
  const char *success[2]; // [esp+8h] [ebp-8h]

  v2 = *(_DWORD *)common.type;
  success[0] = "failed";
  success[1] = "success";
  (*(void (__cdecl **)(netadrtype_t, const char *))(v2 + 124))(common.type, "Shutting down OpenGL subsystem\n");
  if ( qwglMakeCurrent )
  {
    Current = qwglMakeCurrent(0, 0);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...wglMakeCurrent( NULL, NULL ): %s\n",
      success[Current != 0]);
  }
  if ( win32.hGLRC )
  {
    v4 = qwglDeleteContext(win32.hGLRC);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "...deleting GL context: %s\n",
      success[v4 != 0]);
    win32.hGLRC = 0;
  }
  if ( win32.hDC )
  {
    sys->ReleaseDC(sys, win32.hWnd, win32.hDC);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "...releasing DC: success\n");
    win32.hDC = 0;
  }
  if ( win32.hWnd )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "...destroying window\n");
    sys->ShowWindow(sys, win32.hWnd, 0);
    sys->DestroyWindow(sys, win32.hWnd);
    win32.hWnd = 0;
  }
  if ( win32.cdsFullscreen )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "...resetting display\n");
    ChangeDisplaySettingsA(0, 0);
    win32.cdsFullscreen = 0;
  }
  if ( win32.renderThreadHandle )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "...closing smp thread\n");
    CloseHandle(win32.renderThreadHandle);
    win32.renderThreadHandle = 0;
  }
  GLimp_RestoreGamma(a1, a2);
  QGL_Shutdown();
}

// FUNC: void __cdecl GLimp_ActivateContext(void)
void __cdecl GLimp_ActivateContext()
{
  if ( !qwglMakeCurrent(win32.hDC, win32.hGLRC) )
    ++win32.wglErrors;
}

// FUNC: void __cdecl GLimp_DeactivateContext(void)
void __cdecl GLimp_DeactivateContext()
{
  qglFinish();
  if ( !qwglMakeCurrent(win32.hDC, 0) )
    ++win32.wglErrors;
}

// FUNC: _GLimp_ExtensionPointer
int (__stdcall *__cdecl GLimp_ExtensionPointer(const char *name))()
{
  int (__stdcall *ProcAddress)(); // esi

  ProcAddress = qwglGetProcAddress(name);
  if ( !ProcAddress )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      name);
  return ProcAddress;
}

// FUNC: void __cdecl GLW_CheckWGLExtensions(struct HDC__ *)
void __cdecl GLW_CheckWGLExtensions(HDC__ *hDC)
{
  const char *(__stdcall *ProcAddress)(HDC__ *); // esi
  int (__stdcall *v2)(int); // esi
  int (__stdcall *v3)(HDC__ *, int, int, unsigned int, const int *, int *); // esi
  int (__stdcall *v4)(HDC__ *, int, int, unsigned int, const int *, float *); // esi
  int (__stdcall *v5)(HDC__ *, const int *, const float *, unsigned int, int *, unsigned int *); // esi
  HPBUFFERARB__ *(__stdcall *v6)(HDC__ *, int, int, int, const int *); // esi
  HDC__ *(__stdcall *v7)(HPBUFFERARB__ *); // esi
  int (__stdcall *v8)(HPBUFFERARB__ *, HDC__ *); // esi
  int (__stdcall *v9)(HPBUFFERARB__ *); // esi
  int (__stdcall *v10)(HPBUFFERARB__ *, int, int *); // esi
  int (__stdcall *v11)(HPBUFFERARB__ *, int); // esi
  int (__stdcall *v12)(HPBUFFERARB__ *, int); // esi
  int (__stdcall *v13)(HPBUFFERARB__ *, const int *); // esi

  ProcAddress = (const char *(__stdcall *)(HDC__ *))qwglGetProcAddress("wglGetExtensionsStringARB");
  if ( !ProcAddress )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglGetExtensionsStringARB");
  wglGetExtensionsStringARB = ProcAddress;
  if ( ProcAddress )
    glConfig.wgl_extensions_string = ProcAddress(hDC);
  else
    glConfig.wgl_extensions_string = &entityFilter;
  v2 = (int (__stdcall *)(int))qwglGetProcAddress("wglSwapIntervalEXT");
  if ( !v2 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglSwapIntervalEXT");
  wglSwapIntervalEXT = v2;
  BYTE2(r_swapInterval.internalVar->flags) |= 4u;
  v3 = (int (__stdcall *)(HDC__ *, int, int, unsigned int, const int *, int *))qwglGetProcAddress("wglGetPixelFormatAttribivARB");
  if ( !v3 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglGetPixelFormatAttribivARB");
  wglGetPixelFormatAttribivARB = v3;
  v4 = (int (__stdcall *)(HDC__ *, int, int, unsigned int, const int *, float *))qwglGetProcAddress("wglGetPixelFormatAttribfvARB");
  if ( !v4 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglGetPixelFormatAttribfvARB");
  wglGetPixelFormatAttribfvARB = v4;
  v5 = (int (__stdcall *)(HDC__ *, const int *, const float *, unsigned int, int *, unsigned int *))qwglGetProcAddress("wglChoosePixelFormatARB");
  if ( !v5 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglChoosePixelFormatARB");
  wglChoosePixelFormatARB = v5;
  v6 = (HPBUFFERARB__ *(__stdcall *)(HDC__ *, int, int, int, const int *))qwglGetProcAddress("wglCreatePbufferARB");
  if ( !v6 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglCreatePbufferARB");
  wglCreatePbufferARB = v6;
  v7 = (HDC__ *(__stdcall *)(HPBUFFERARB__ *))qwglGetProcAddress("wglGetPbufferDCARB");
  if ( !v7 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglGetPbufferDCARB");
  wglGetPbufferDCARB = v7;
  v8 = (int (__stdcall *)(HPBUFFERARB__ *, HDC__ *))qwglGetProcAddress("wglReleasePbufferDCARB");
  if ( !v8 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglReleasePbufferDCARB");
  wglReleasePbufferDCARB = v8;
  v9 = (int (__stdcall *)(HPBUFFERARB__ *))qwglGetProcAddress("wglDestroyPbufferARB");
  if ( !v9 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglDestroyPbufferARB");
  wglDestroyPbufferARB = v9;
  v10 = (int (__stdcall *)(HPBUFFERARB__ *, int, int *))qwglGetProcAddress("wglQueryPbufferARB");
  if ( !v10 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglQueryPbufferARB");
  wglQueryPbufferARB = v10;
  v11 = (int (__stdcall *)(HPBUFFERARB__ *, int))qwglGetProcAddress("wglBindTexImageARB");
  if ( !v11 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglBindTexImageARB");
  wglBindTexImageARB = v11;
  v12 = (int (__stdcall *)(HPBUFFERARB__ *, int))qwglGetProcAddress("wglReleaseTexImageARB");
  if ( !v12 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglReleaseTexImageARB");
  wglReleaseTexImageARB = v12;
  v13 = (int (__stdcall *)(HPBUFFERARB__ *, const int *))qwglGetProcAddress("wglSetPbufferAttribARB");
  if ( !v13 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't find proc address for: %s\n",
      "wglSetPbufferAttribARB");
  wglSetPbufferAttribARB = v13;
}

// FUNC: GLW_GetWGLExtensionsWithFakeWindow
BOOL GLW_GetWGLExtensionsWithFakeWindow()
{
  void *v0; // edi
  HDC__ *v1; // esi
  HGLRC Context; // ebx
  BOOL result; // eax
  tagMSG msg; // [esp+40h] [ebp-1Ch] BYREF

  v0 = sys->CreateWindowExA(sys, "QUAKE4_WGL_FAKE", "Quake4", 13565952, 40, 40, 640, 480, 0, 0, win32.hInstance, 0, 0);
  if ( !v0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "GLW_GetWGLExtensionsWithFakeWindow: Couldn't create fake window");
  v1 = (HDC__ *)sys->GetDC(sys, v0);
  Context = wglCreateContext(v1);
  wglMakeCurrent(v1, Context);
  GLW_CheckWGLExtensions(v1);
  wglDeleteContext(Context);
  sys->ReleaseDC(sys, v0, v1);
  sys->DestroyWindow(sys, v0);
  for ( result = GetMessageA(&msg, 0, 0, 0); result; result = GetMessageA(&msg, 0, 0, 0) )
  {
    TranslateMessage(&msg);
    DispatchMessageA(&msg);
  }
  return result;
}

// FUNC: GLW_CreateWindow
char __cdecl GLW_CreateWindow(glimpParms_t parms)
{
  int width; // esi
  int height; // edi
  int integerValue; // ebp
  int v4; // ebx
  char inited; // al
  idSys_vtbl *v7; // edx
  int exstyle; // [esp+24h] [ebp-18h]
  int stylebits; // [esp+28h] [ebp-14h]
  tagRECT r; // [esp+2Ch] [ebp-10h] BYREF

  if ( parms.fullScreen )
  {
    width = parms.width;
    height = parms.height;
    exstyle = 8;
    stylebits = -1878523904;
    integerValue = 0;
LABEL_10:
    v4 = 0;
    goto LABEL_11;
  }
  r.bottom = parms.height;
  r.left = 0;
  r.top = 0;
  r.right = parms.width;
  exstyle = 0;
  stylebits = 13369344;
  AdjustWindowRect(&r, 0xCC0000u, 0);
  width = r.right - r.left;
  integerValue = __unnamed::win_xpos.internalVar->integerValue;
  height = r.bottom - r.top;
  v4 = __unnamed::win_ypos.internalVar->integerValue;
  if ( r.right - r.left + integerValue > win32.desktopWidth )
    integerValue = win32.desktopWidth - width;
  if ( height + v4 > win32.desktopHeight )
    v4 = win32.desktopHeight - height;
  if ( integerValue < 0 )
    integerValue = 0;
  if ( v4 < 0 )
    goto LABEL_10;
LABEL_11:
  win32.hWnd = (HWND__ *)sys->CreateWindowExA(
                           sys,
                           "Quake4",
                           "Quake4",
                           stylebits,
                           integerValue,
                           v4,
                           width,
                           height,
                           0,
                           0,
                           win32.hInstance,
                           0,
                           exstyle);
  if ( win32.hWnd )
  {
    if ( !(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 6) )
    {
      SetTimer(win32.hWnd, 0, 0x64u, 0);
      sys->ShowWindow(sys, win32.hWnd, 5);
      sys->UpdateWindow(sys, win32.hWnd);
    }
    (*(void (__cdecl **)(netadrtype_t))(*(_DWORD *)common.type + 124))(common.type);
    inited = GLW_InitDriver(parms);
    v7 = sys->__vftable;
    if ( inited )
    {
      if ( ((unsigned __int8 (__stdcall *)(HWND__ *))v7->IsWindowVisible)(win32.hWnd) )
      {
        sys->SetForegroundWindow(sys, win32.hWnd);
        sys->SetFocus(sys, win32.hWnd);
      }
      glConfig.isFullscreen = parms.fullScreen;
      return 1;
    }
    else
    {
      ((void (__stdcall *)(HWND__ *, _DWORD))v7->ShowWindow)(win32.hWnd, 0);
      sys->DestroyWindow(sys, win32.hWnd);
      win32.hWnd = 0;
      return 0;
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "^3GLW_CreateWindow() - Couldn't create window^0\n");
    return 0;
  }
}

// FUNC: bool __cdecl GLimp_Init(struct glimpParms_t)
char __cdecl GLimp_Init(glimpParms_t parms)
{
  idSys_vtbl *v1; // esi
  HWND DesktopWindow; // eax
  HDC v3; // esi
  idSys_vtbl *v4; // edi
  HWND v5; // eax
  const char *value; // esi

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Initializing OpenGL subsystem\n");
  v1 = sys->__vftable;
  DesktopWindow = GetDesktopWindow();
  v3 = (HDC)v1->GetDC(sys, DesktopWindow);
  win32.desktopBitsPixel = GetDeviceCaps(v3, 12);
  win32.desktopWidth = GetDeviceCaps(v3, 8);
  win32.desktopHeight = GetDeviceCaps(v3, 10);
  v4 = sys->__vftable;
  v5 = GetDesktopWindow();
  v4->ReleaseDC(sys, v5, v3);
  if ( win32.desktopBitsPixel >= 32 || parms.fullScreen )
  {
    GLimp_SaveGamma();
    GLW_CreateWindowClasses();
    value = r_glDriver.internalVar->value;
    if ( !*value )
      value = "opengl32";
    if ( QGL_Init(value) )
    {
      GLW_GetWGLExtensionsWithFakeWindow();
      if ( (!parms.fullScreen || GLW_SetFullScreen(parms)) && GLW_CreateWindow(parms) )
      {
        GLW_CheckWGLExtensions(win32.hDC);
        QGL_Extensions_Init();
        return 1;
      }
      else
      {
        GLimp_Shutdown(parms.displayHz, parms.multiSamples);
        return 0;
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "^3GLimp_Init() could not load r_glDriver \"%s\"^0\n",
        value);
      return 0;
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "^3Windowed mode requires 32 bit desktop depth^0\n");
    return 0;
  }
}

// FUNC: bool __cdecl GLimp_SetScreenParms(struct glimpParms_t)
bool __cdecl GLimp_SetScreenParms(glimpParms_t parms)
{
  int v1; // edi
  bool fullScreen; // bl
  int integerValue; // esi
  bool ret; // [esp+Fh] [ebp-B9h]
  int w; // [esp+10h] [ebp-B8h]
  int h; // [esp+14h] [ebp-B4h]
  tagRECT r; // [esp+18h] [ebp-B0h] BYREF
  _devicemodeA dm; // [esp+28h] [ebp-A0h] BYREF

  memset(&dm, 0, sizeof(dm));
  v1 = 0;
  dm.dmSize = 156;
  dm.dmFields = 1835008;
  if ( parms.displayHz )
  {
    dm.dmDisplayFrequency = parms.displayHz;
    dm.dmFields = 6029312;
  }
  fullScreen = parms.fullScreen;
  win32.cdsFullscreen = parms.fullScreen;
  glConfig.isFullscreen = parms.fullScreen;
  if ( parms.fullScreen )
  {
    SetWindowLongA(win32.hWnd, -16, -1878523904);
    SetWindowLongA(win32.hWnd, -20, 8);
    dm.dmPelsWidth = parms.width;
    dm.dmPelsHeight = parms.height;
    dm.dmBitsPerPel = 32;
    h = 0;
    w = 0;
    integerValue = 0;
  }
  else
  {
    r.bottom = parms.height;
    r.left = 0;
    r.top = 0;
    r.right = parms.width;
    integerValue = __unnamed::win_xpos.internalVar->integerValue;
    v1 = __unnamed::win_ypos.internalVar->integerValue;
    w = parms.width;
    h = parms.height;
    if ( integerValue + parms.width > win32.desktopWidth )
      integerValue = win32.desktopWidth - parms.width;
    if ( v1 + parms.height > win32.desktopHeight )
      v1 = win32.desktopHeight - parms.height;
    if ( integerValue < 0 )
      integerValue = 0;
    if ( v1 < 0 )
      v1 = 0;
    dm.dmPelsWidth = win32.desktopWidth;
    dm.dmPelsHeight = win32.desktopHeight;
    dm.dmBitsPerPel = win32.desktopBitsPixel;
    AdjustWindowRect(&r, (DWORD)&sessLocal.loggedUsercmds[186744].cmd.sequence, 0);
    SetWindowLongA(win32.hWnd, -16, (LONG)&sessLocal.loggedUsercmds[186744].cmd.sequence);
    SetWindowLongA(win32.hWnd, -20, 0);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%i %i %i %i\n",
      integerValue,
      v1,
      parms.width,
      parms.height);
    fullScreen = 0;
  }
  ret = ChangeDisplaySettingsA(&dm, fullScreen ? 4 : 0) == 0;
  SetWindowPos(win32.hWnd, (HWND)(fullScreen - 2), integerValue, v1, w, h, fullScreen ? 3 : 64);
  return ret;
}

// FUNC: void __cdecl GLimp_SwapBuffers(void)
void __cdecl GLimp_SwapBuffers()
{
  if ( (r_swapInterval.internalVar->flags & 0x40000) != 0 )
  {
    BYTE2(r_swapInterval.internalVar->flags) &= ~4u;
    if ( wglSwapIntervalEXT )
      wglSwapIntervalEXT(r_swapInterval.internalVar->integerValue);
  }
  qwglSwapBuffers(win32.hDC);
}
