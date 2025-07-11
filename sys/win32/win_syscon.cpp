
// FUNC: long __stdcall InputLineWndProc(struct HWND__ *,unsigned int,unsigned int,long)
LRESULT __stdcall InputLineWndProc(HWND__ *hWnd, int uMsg, HWND__ *wParam, int lParam)
{
  LPARAM v4; // ebx
  UINT v5; // ebp
  signed int v6; // esi
  char *Buffer; // eax
  const char *v8; // eax
  WPARAM v9; // eax
  unsigned int v11; // kr00_4
  const char *v12; // eax
  const char *v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  const char *v17; // eax
  WPARAM v18; // eax
  int historyLine; // eax
  LPARAM Cursor; // [esp-4h] [ebp-14h]
  LPARAM v21; // [esp-4h] [ebp-14h]

  v4 = lParam;
  v5 = uMsg;
  v6 = (signed int)wParam;
  if ( uMsg == 8 )
  {
    if ( wParam == s_wcd.hWnd || wParam == s_wcd.hwndErrorBox )
    {
      sys->SetFocus(sys, hWnd);
      return 0;
    }
    return CallWindowProcA(s_wcd.SysInputLineWndProc, hWnd, v5, v6, v4);
  }
  if ( uMsg != 256 )
  {
    if ( uMsg == 258 && (lParam & 0xFF0000) != 2686976 )
    {
      Buffer = idEditField::GetBuffer(&s_wcd.consoleField);
      GetWindowTextA(s_wcd.hwndInputLine, Buffer, 256);
      SendMessageA(s_wcd.hwndInputLine, 0xB0u, 0, (LPARAM)&uMsg);
      idEditField::SetCursor(&s_wcd.consoleField, uMsg);
      if ( v6 == 13 || v6 == 174 )
      {
        v11 = strlen(s_wcd.consoleText);
        v12 = idEditField::GetBuffer(&s_wcd.consoleField);
        strncat(s_wcd.consoleText, v12, 507 - v11);
        strcat(s_wcd.consoleText, "\n");
        SetWindowTextA(s_wcd.hwndInputLine, &entityFilter);
        v13 = idEditField::GetBuffer(&s_wcd.consoleField);
        Sys_Printf("]%s\n", v13);
        qmemcpy(
          &s_wcd.historyEditLines[s_wcd.nextHistoryLine++ % 64],
          &s_wcd.consoleField,
          sizeof(s_wcd.historyEditLines[s_wcd.nextHistoryLine++ % 64]));
        s_wcd.historyLine = s_wcd.nextHistoryLine;
        idEditField::Clear(&s_wcd.consoleField);
        return 0;
      }
      if ( v6 == 9 )
      {
        idEditField::AutoComplete(&s_wcd.consoleField);
        v8 = idEditField::GetBuffer(&s_wcd.consoleField);
        SetWindowTextA(s_wcd.hwndInputLine, v8);
        Cursor = idEditField::GetCursor((idCmdArgs *)&s_wcd.consoleField);
        v9 = idEditField::GetCursor((idCmdArgs *)&s_wcd.consoleField);
        SendMessageA(s_wcd.hwndInputLine, 0xB1u, v9, Cursor);
        return 0;
      }
      if ( v6 >= 32 && v6 <= 127 || v6 >= 177 && v6 <= 181 || v6 >= 183 && v6 <= 184 )
        idEditField::ClearAutoComplete(&s_wcd.consoleField);
    }
    return CallWindowProcA(s_wcd.SysInputLineWndProc, hWnd, v5, v6, v4);
  }
  v14 = sys->MapKey(sys, lParam, (unsigned __int16)wParam);
  if ( v14 == 133 || v14 == 166 )
  {
    historyLine = s_wcd.historyLine;
    if ( s_wcd.nextHistoryLine - s_wcd.historyLine < 64 && s_wcd.historyLine > 0 )
      historyLine = --s_wcd.historyLine;
    v16 = historyLine % 64;
    goto LABEL_23;
  }
  if ( v14 != 134 && v14 != 172 )
    return CallWindowProcA(s_wcd.SysInputLineWndProc, hWnd, v5, v6, v4);
  v15 = s_wcd.historyLine;
  if ( s_wcd.historyLine != s_wcd.nextHistoryLine )
  {
    ++s_wcd.historyLine;
    v16 = (v15 + 1) % 64;
LABEL_23:
    qmemcpy(&s_wcd.consoleField, &s_wcd.historyEditLines[v16], sizeof(s_wcd.consoleField));
    v17 = idEditField::GetBuffer(&s_wcd.consoleField);
    SetWindowTextA(s_wcd.hwndInputLine, v17);
    v21 = idEditField::GetCursor((idCmdArgs *)&s_wcd.consoleField);
    v18 = idEditField::GetCursor((idCmdArgs *)&s_wcd.consoleField);
    SendMessageA(s_wcd.hwndInputLine, 0xB1u, v18, v21);
    return 0;
  }
  return 0;
}

// FUNC: void __cdecl Sys_ShowSplash(int,int)
void __cdecl Sys_ShowSplash(int width, int height)
{
  HWND__ *v2; // eax
  tagWNDCLASSA wc; // [esp+0h] [ebp-28h] BYREF

  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.lpszMenuName = 0;
  wc.style = 0;
  wc.lpfnWndProc = SplashWndProc;
  wc.hInstance = win32.hInstance;
  wc.hIcon = LoadIconA(win32.hInstance, (LPCSTR)0x400);
  wc.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
  wc.hbrBackground = (HBRUSH__ *)5;
  wc.lpszClassName = "Quake 4 Splash";
  if ( RegisterClassA(&wc) )
  {
    v2 = (HWND__ *)sys->CreateWindowExA(
                     sys,
                     "Quake 4 Splash",
                     "Quake4",
                     0x80000000,
                     (width - 512) / 2,
                     (height - 384) / 2,
                     512,
                     384,
                     0,
                     0,
                     win32.hInstance,
                     0,
                     0);
    s_wcd.hWndSplash = v2;
    if ( v2 )
    {
      ShowWindow(v2, 1);
      UpdateWindow(s_wcd.hWndSplash);
    }
  }
}

// FUNC: void __cdecl Sys_DestroySplash(void)
void __cdecl Sys_DestroySplash()
{
  if ( s_wcd.hWndSplash )
  {
    sys->ShowWindow(sys, s_wcd.hWndSplash, 0);
    sys->DestroyWindow(sys, s_wcd.hWndSplash);
    s_wcd.hWndSplash = 0;
  }
}

// FUNC: void __cdecl Sys_ShowConsole(int,bool)
void __usercall Sys_ShowConsole(int a1@<edi>, int a2@<esi>, int visLevel, bool quitOnClose)
{
  s_wcd.quitOnClose = quitOnClose;
  if ( s_wcd.hWnd )
  {
    if ( visLevel )
    {
      if ( visLevel == 1 )
      {
        Sys_DestroySplash();
        sys->ShowWindow(sys, s_wcd.hWnd, 1);
        SendMessageA(s_wcd.hwndBuffer, 0xB6u, 0, 0xFFFF);
        sys->UpdateWindow(sys, s_wcd.hWnd);
        sys->SetForegroundWindow(sys, s_wcd.hWnd);
        sys->SetFocus(sys, s_wcd.hwndInputLine);
      }
      else
      {
        if ( visLevel != 2 )
          Sys_Error(a1, a2, "Invalid visLevel %d sent to Sys_ShowConsole\n", visLevel);
        sys->ShowWindow(sys, s_wcd.hWnd, 6);
      }
    }
    else
    {
      sys->ShowWindow(sys, s_wcd.hWnd, 0);
    }
  }
}

// FUNC: void __cdecl Sys_DestroyConsole(void)
void __cdecl Sys_DestroyConsole()
{
  if ( s_wcd.hWnd )
  {
    s_wcd.closing = 1;
    sys->ShowWindow(sys, s_wcd.hWnd, 0);
    sys->DestroyWindow(sys, s_wcd.hWnd);
    s_wcd.hWnd = 0;
  }
}

// FUNC: void __cdecl Conbuf_WriteOutput(void)
void __cdecl Conbuf_WriteOutput()
{
  if ( s_wcd.resetOutput )
  {
    SendMessageA(s_wcd.hwndBuffer, 0xB1u, 0, -1);
    s_wcd.resetOutput = 0;
  }
  if ( s_wcd.refreshConsole )
  {
    SendMessageA(s_wcd.hwndBuffer, 0xB6u, 0, 0xFFFF);
    SendMessageA(s_wcd.hwndBuffer, 0xB7u, 0, 0);
    SendMessageA(s_wcd.hwndBuffer, 0xC2u, 0, (LPARAM)s_wcd.buffer);
    s_wcd.refreshConsole = 0;
    s_wcd.bufferPos = s_wcd.buffer;
    s_wcd.buffer[0] = 0;
    s_wcd.bufferLineCount = 0;
  }
}

// FUNC: char * __cdecl Sys_ConsoleInput(void)
char *__cdecl Sys_ConsoleInput()
{
  char *consoleText; // eax
  char v2; // cl

  if ( !s_wcd.consoleText[0] )
    return 0;
  consoleText = s_wcd.consoleText;
  do
  {
    v2 = *consoleText;
    consoleText[512] = *consoleText;
    ++consoleText;
  }
  while ( v2 );
  s_wcd.consoleText[0] = 0;
  return s_wcd.returnedText;
}

// FUNC: void __cdecl Conbuf_AppendText(char const *)
void __cdecl Conbuf_AppendText(const char *pMsg)
{
  const char *v1; // edx
  char *v2; // esi
  int v3; // ebx
  unsigned int v4; // ebp
  char v5; // al
  const char *v6; // edi
  int IsEscape; // eax
  unsigned int v8; // eax
  unsigned int v9; // esi
  char *bufferPos; // edx
  char *v11; // ecx
  char v12; // al
  const char *v13; // [esp+Ch] [ebp-8004h]
  char v14[32768]; // [esp+10h] [ebp-8000h] BYREF

  v1 = pMsg;
  v2 = v14;
  v3 = 0;
  if ( strlen(pMsg) <= 0x3FFF )
  {
    v13 = pMsg;
  }
  else
  {
    v1 = &pMsg[strlen(pMsg) - 0x3FFF];
    v13 = v1;
  }
  if ( *v1 )
  {
    v4 = 0;
    while ( 1 )
    {
      if ( v4 >= 0x7FFF )
        goto LABEL_19;
      v5 = v1[v3];
      v6 = &v1[v3];
      if ( v5 == 10 && v1[v3 + 1] == 13 )
        break;
      if ( v5 == 13 )
      {
        *v2 = 13;
        v2[1] = 10;
        v2 += 2;
        v4 += 2;
        goto LABEL_17;
      }
      if ( v5 == 10 )
      {
        *v2 = 13;
        v2[1] = 10;
        v2 += 2;
        v4 += 2;
        goto LABEL_17;
      }
      if ( !idStr::IsEscape(&v1[v3], 0) )
      {
        v1 = v13;
        *v2++ = *v6;
        ++v4;
        goto LABEL_17;
      }
      IsEscape = idStr::IsEscape(v6, 0);
      v1 = v13;
      v3 += IsEscape;
LABEL_18:
      if ( !v1[v3] )
        goto LABEL_19;
    }
    *v2 = 13;
    v2[1] = 10;
    v2 += 2;
    v4 += 2;
    ++v3;
LABEL_17:
    ++v3;
    goto LABEL_18;
  }
LABEL_19:
  v8 = s_totalChars;
  *v2 = 0;
  v9 = v2 - v14;
  s_totalChars = v9 + v8;
  if ( v9 + v8 > 0x7000 )
  {
    s_totalChars = v9;
    s_wcd.resetOutput = 1;
    s_wcd.bufferPos = s_wcd.buffer;
    s_wcd.buffer[0] = 0;
    s_wcd.bufferLineCount = 0;
  }
  if ( v9 + s_wcd.bufferPos - s_wcd.buffer > 0x8000 )
  {
    s_wcd.refreshConsole = 1;
    Conbuf_WriteOutput();
  }
  bufferPos = s_wcd.bufferPos;
  v11 = v14;
  do
  {
    v12 = *v11;
    *bufferPos++ = *v11++;
  }
  while ( v12 );
  s_wcd.bufferPos += v9;
  ++s_wcd.bufferLineCount;
  s_wcd.refreshConsole = 1;
  if ( s_wcd.viewlogUpdateCount > 0 && s_wcd.bufferLineCount > s_wcd.viewlogUpdateCount )
    Conbuf_WriteOutput();
}

// FUNC: void __cdecl Win_SetErrorText(char const *)
void __cdecl Win_SetErrorText(const char *buf)
{
  idStr::Copynz(s_wcd.errorString, buf, 80);
  if ( !s_wcd.hwndErrorBox )
  {
    s_wcd.hwndErrorBox = (HWND__ *)sys->CreateWindowExA(
                                     sys,
                                     "static",
                                     0,
                                     1342181376,
                                     6,
                                     5,
                                     526,
                                     30,
                                     s_wcd.hWnd,
                                     10,
                                     win32.hInstance,
                                     0,
                                     0);
    SendMessageA(s_wcd.hwndErrorBox, 0x30u, (WPARAM)s_wcd.hfBufferFont, 0);
    SetWindowTextA(s_wcd.hwndErrorBox, s_wcd.errorString);
    sys->DestroyWindow(sys, s_wcd.hwndInputLine);
    s_wcd.hwndInputLine = 0;
  }
}

// FUNC: void __cdecl Sys_CreateConsole(void)
void __cdecl Sys_CreateConsole()
{
  idSys_vtbl *v0; // esi
  HWND DesktopWindow; // eax
  HDC v2; // esi
  HWND v3; // eax
  HWND__ *v4; // eax
  HDC v5; // esi
  int DeviceCaps; // eax
  int v7; // eax
  idEditField *historyEditLines; // esi
  int sheight; // [esp+140h] [ebp-44h]
  idSys_vtbl *v10; // [esp+144h] [ebp-40h]
  int swidth; // [esp+148h] [ebp-3Ch]
  tagRECT rect; // [esp+14Ch] [ebp-38h] BYREF
  tagWNDCLASSA wc; // [esp+15Ch] [ebp-28h] BYREF

  wc.style = 0;
  wc.lpfnWndProc = (int (__stdcall *)(HWND__ *, unsigned int, unsigned int, int))ConWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = win32.hInstance;
  wc.hIcon = LoadIconA(win32.hInstance, (LPCSTR)0x400);
  wc.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
  wc.hbrBackground = (HBRUSH__ *)5;
  wc.lpszMenuName = 0;
  wc.lpszClassName = "Quake 4 WinConsole";
  if ( RegisterClassA(&wc) )
  {
    rect.left = 0;
    rect.right = 540;
    rect.top = 0;
    rect.bottom = 450;
    AdjustWindowRect(&rect, 0x80CA0000, 0);
    v0 = sys->__vftable;
    DesktopWindow = GetDesktopWindow();
    v2 = (HDC)v0->GetDC(sys, DesktopWindow);
    swidth = GetDeviceCaps(v2, 8);
    sheight = GetDeviceCaps(v2, 10);
    v10 = sys->__vftable;
    v3 = GetDesktopWindow();
    v10->ReleaseDC(sys, v3, v2);
    s_wcd.windowWidth = rect.right - rect.left + 1;
    s_wcd.windowHeight = rect.bottom - rect.top + 1;
    v4 = (HWND__ *)sys->CreateWindowExA(
                     sys,
                     "Quake 4 WinConsole",
                     "Quake4",
                     -2134245376,
                     (swidth - 600) / 2,
                     (sheight - 450) / 2,
                     rect.right - rect.left + 1,
                     rect.bottom - rect.top + 1,
                     0,
                     0,
                     win32.hInstance,
                     0,
                     0);
    s_wcd.hWnd = v4;
    if ( v4 )
    {
      v5 = (HDC)sys->GetDC(sys, v4);
      DeviceCaps = GetDeviceCaps(v5, 90);
      v7 = MulDiv(8, DeviceCaps, 72);
      s_wcd.hfBufferFont = CreateFontA(-v7, 0, 0, 0, 300, 0, 0, 0, 1u, 0, 0, 0, 0x31u, "Courier New");
      sys->ReleaseDC(sys, s_wcd.hWnd, v5);
      s_wcd.hwndInputLine = (HWND__ *)sys->CreateWindowExA(
                                        sys,
                                        "edit",
                                        0,
                                        1350566016,
                                        6,
                                        400,
                                        528,
                                        20,
                                        s_wcd.hWnd,
                                        101,
                                        win32.hInstance,
                                        0,
                                        0);
      SendMessageA(s_wcd.hwndInputLine, 0xC5u, 0x100u, 0);
      s_wcd.hwndButtonCopy = (HWND__ *)sys->CreateWindowExA(
                                         sys,
                                         "button",
                                         0,
                                         1342177281,
                                         5,
                                         425,
                                         72,
                                         24,
                                         s_wcd.hWnd,
                                         1,
                                         win32.hInstance,
                                         0,
                                         0);
      SendMessageA(s_wcd.hwndButtonCopy, 0xCu, 0, (LPARAM)"copy");
      s_wcd.hwndButtonClear = (HWND__ *)sys->CreateWindowExA(
                                          sys,
                                          "button",
                                          0,
                                          1342177281,
                                          82,
                                          425,
                                          72,
                                          24,
                                          s_wcd.hWnd,
                                          3,
                                          win32.hInstance,
                                          0,
                                          0);
      SendMessageA(s_wcd.hwndButtonClear, 0xCu, 0, (LPARAM)"clear");
      s_wcd.hwndButtonQuit = (HWND__ *)sys->CreateWindowExA(
                                         sys,
                                         "button",
                                         0,
                                         1342177281,
                                         462,
                                         425,
                                         72,
                                         24,
                                         s_wcd.hWnd,
                                         2,
                                         win32.hInstance,
                                         0,
                                         0);
      SendMessageA(s_wcd.hwndButtonQuit, 0xCu, 0, (LPARAM)"quit");
      s_wcd.hwndBuffer = (HWND__ *)sys->CreateWindowExA(
                                     sys,
                                     "edit",
                                     0,
                                     1352665156,
                                     6,
                                     40,
                                     526,
                                     354,
                                     s_wcd.hWnd,
                                     100,
                                     win32.hInstance,
                                     0,
                                     0);
      SendMessageA(s_wcd.hwndBuffer, 0x30u, (WPARAM)s_wcd.hfBufferFont, 0);
      s_wcd.SysInputLineWndProc = (int (__stdcall *)(HWND__ *, unsigned int, unsigned int, int))SetWindowLongA(
                                                                                                  s_wcd.hwndInputLine,
                                                                                                  -4,
                                                                                                  (LONG)InputLineWndProc);
      SendMessageA(s_wcd.hwndInputLine, 0x30u, (WPARAM)s_wcd.hfBufferFont, 0);
      s_wcd.quitOnClose = 0;
      if ( s_wcd.hWnd )
        sys->ShowWindow(sys, s_wcd.hWnd, 0);
      Sys_ShowSplash(swidth, sheight);
      idEditField::Clear(&s_wcd.consoleField);
      historyEditLines = s_wcd.historyEditLines;
      do
        idEditField::Clear(historyEditLines++);
      while ( (int)historyEditLines < (int)&s_wcd.nextHistoryLine );
      s_wcd.resetOutput = 0;
      s_wcd.refreshConsole = 0;
      s_wcd.bufferPos = s_wcd.buffer;
      s_wcd.buffer[0] = 0;
      s_wcd.bufferLineCount = 0;
      s_wcd.viewlogUpdateCount = 10;
    }
  }
}

// FUNC: void __cdecl Sys_UpdateConsole(void)
void __cdecl Sys_UpdateConsole()
{
  if ( s_wcd.hWndSplash )
  {
    sys->ShowWindow(sys, s_wcd.hWndSplash, 0);
    sys->DestroyWindow(sys, s_wcd.hWndSplash);
    s_wcd.hWndSplash = 0;
  }
  if ( (win_viewlog_xpos.internalVar->flags & 0x40000) != 0 || (win_viewlog_ypos.internalVar->flags & 0x40000) != 0 )
  {
    MoveWindow(
      s_wcd.hWnd,
      win_viewlog_xpos.internalVar->integerValue,
      win_viewlog_ypos.internalVar->integerValue,
      s_wcd.windowWidth,
      s_wcd.windowHeight,
      1);
    win_viewlog_xpos.internalVar->flags &= ~0x40000u;
    win_viewlog_ypos.internalVar->flags &= ~0x40000u;
  }
  s_wcd.viewlogUpdateCount = win_viewlog_update_count.internalVar->integerValue;
  Conbuf_WriteOutput();
}
