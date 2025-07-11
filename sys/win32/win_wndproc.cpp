
// FUNC: void __cdecl WIN_Sizing(unsigned short,struct tagRECT *)
void __cdecl WIN_Sizing(unsigned __int16 side, tagRECT *rect)
{
  int v2; // ebp
  int v3; // edi
  int v4; // ecx
  int v5; // ebx
  int v6; // ebp
  int v7; // edi
  int v8; // eax
  tagRECT decoRect; // [esp+4h] [ebp-10h] BYREF

  if ( glConfig.isInitialized
    && glConfig.vidHeight > 0
    && glConfig.vidWidth > 0
    && !idKeyInput::IsDown(141)
    && !idKeyInput::IsDown(2) )
  {
    v2 = rect->right - rect->left;
    v3 = rect->bottom - rect->top;
    memset(&decoRect, 0, sizeof(decoRect));
    AdjustWindowRect(&decoRect, (DWORD)&sessLocal.loggedUsercmds[186744].cmd.sequence, 0);
    v4 = decoRect.right - decoRect.left;
    v5 = decoRect.bottom - decoRect.top;
    v6 = v2 - (decoRect.right - decoRect.left);
    v7 = v3 - (decoRect.bottom - decoRect.top);
    if ( v6 < 160 )
      v6 = 160;
    if ( v7 < 120 )
      v7 = 120;
    switch ( side )
    {
      case 1u:
        rect->left = rect->right - v4 - v6;
        rect->bottom = rect->top + v5 + 480 * v6 / 640;
        break;
      case 2u:
        rect->right = v6 + v4 + rect->left;
        rect->bottom = rect->top + v5 + 480 * v6 / 640;
        break;
      case 3u:
      case 5u:
        rect->top = rect->bottom - v5 - v7;
        rect->right = v4 + rect->left + 640 * v7 / 480;
        break;
      case 4u:
        rect->top = rect->bottom - v5 - v7;
        goto LABEL_17;
      case 6u:
      case 8u:
        v8 = v4 + rect->left + 640 * v7 / 480;
        rect->bottom = rect->top + v7 + v5;
        rect->right = v8;
        break;
      case 7u:
        rect->bottom = rect->top + v7 + v5;
LABEL_17:
        rect->left = rect->right - 640 * v7 / 480 - v4;
        break;
      default:
        return;
    }
  }
}

// FUNC: WIN_DisableAltTab
void __thiscall WIN_DisableAltTab(void *this)
{
  const char *v1; // eax
  int old; // [esp+4h] [ebp-4h] BYREF

  old = (int)this;
  if ( !s_alttab_disabled && !__unnamed::win_allowAltTab.internalVar->integerValue )
  {
    v1 = cvarSystem->GetCVarString(cvarSystem, "sys_arch");
    if ( idStr::Icmp(v1, "winnt") )
      SystemParametersInfoA(0x61u, 1u, &old, 0);
    else
      RegisterHotKey(0, 0, 1u, 9u);
    s_alttab_disabled = 1;
  }
}

// FUNC: WIN_EnableAltTab
void __thiscall WIN_EnableAltTab(void *this)
{
  const char *v1; // eax
  int old; // [esp+4h] [ebp-4h] BYREF

  old = (int)this;
  if ( s_alttab_disabled && !__unnamed::win_allowAltTab.internalVar->integerValue )
  {
    v1 = cvarSystem->GetCVarString(cvarSystem, "sys_arch");
    if ( idStr::Icmp(v1, "winnt") )
      SystemParametersInfoA(0x61u, 0, &old, 0);
    else
      UnregisterHotKey(0, 0);
    s_alttab_disabled = 0;
  }
}

// FUNC: long __stdcall MainWndProc(struct HWND__ *,unsigned int,unsigned int,long)
int __thiscall MainWndProc(void *this, HWND__ *hWnd, unsigned int uMsg, unsigned int wParam, int lParam)
{
  UINT v5; // edi
  LONG WindowLongA; // eax
  int v7; // eax
  int v8; // esi
  int result; // eax
  idCVarSystem_vtbl *v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // esi
  int v14; // eax
  int v15; // edi
  tagRECT r; // [esp+10h] [ebp-10h] BYREF

  v5 = uMsg;
  if ( uMsg <= 0x102 )
  {
    if ( uMsg == 258 )
    {
      if ( (lParam & 0xFF0000) != 2686976 )
        Sys_QueEvent(win32.sysMsgTime, SE_CHAR, wParam, 0, 0, 0);
    }
    else if ( uMsg > 0x10 )
    {
      switch ( uMsg )
      {
        case 0x47u:
          if ( glConfig.isInitialized && GetClientRect(win32.hWnd, &r) )
          {
            glConfig.vidWidth = r.right - r.left;
            glConfig.vidHeight = r.bottom - r.top;
          }
          break;
        case 0x100u:
LABEL_42:
          v12 = sys->MapKey(sys, lParam, wParam);
          v13 = v12;
          if ( v12 && v12 != 141 && v12 != 253 && v12 != 252 )
          {
            Sys_QueEvent(win32.sysMsgTime, SE_KEY, v12, 1, 0, 0);
            sys->AddKeyPress(sys, v13, 1);
          }
          break;
        case 0x101u:
$L116697:
          v7 = sys->MapKey(sys, lParam, wParam);
          v8 = v7;
          if ( v7 && v7 != 141 && v7 != 253 && v7 != 252 )
          {
            Sys_QueEvent(win32.sysMsgTime, SE_KEY, v7, 0, 0, 0);
            sys->AddKeyPress(sys, v8, 0);
          }
          break;
      }
    }
    else if ( uMsg == 16 )
    {
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "quit");
    }
    else
    {
      switch ( uMsg )
      {
        case 1u:
          win32.hWnd = hWnd;
          if ( win32.cdsFullscreen )
            WIN_DisableAltTab(this);
          else
            WIN_EnableAltTab(this);
          SpawnStub();
          break;
        case 2u:
          win32.hWnd = 0;
          if ( win32.cdsFullscreen )
            WIN_EnableAltTab(this);
          break;
        case 3u:
          if ( !win32.cdsFullscreen )
          {
            r.left = 0;
            r.top = 0;
            r.right = 1;
            r.bottom = 1;
            WindowLongA = GetWindowLongA(hWnd, -16);
            AdjustWindowRect(&r, WindowLongA, 0);
            __unnamed::win_xpos.internalVar->InternalSetInteger(
              __unnamed::win_xpos.internalVar,
              r.left + (__int16)lParam);
            __unnamed::win_ypos.internalVar->InternalSetInteger(
              __unnamed::win_ypos.internalVar,
              r.top + SHIWORD(lParam));
            __unnamed::win_xpos.internalVar->flags &= ~0x40000u;
            __unnamed::win_ypos.internalVar->flags &= ~0x40000u;
          }
          break;
        case 6u:
          win32.activeApp = (unsigned __int16)wParam != 0;
          if ( (_WORD)wParam )
          {
            idKeyInput::ClearStates();
            (*(void (__thiscall **)(netadrtype_t, _DWORD))(*(_DWORD *)common.type + 72))(common.type, 0);
            sys->GrabMouseCursor(sys, 1);
          }
          else
          {
            win32.movingWindow = 0;
          }
          soundSystem->SetActiveSoundWorld(soundSystem, 1);
          break;
        default:
          return DefWindowProcA(hWnd, v5, wParam, lParam);
      }
    }
    return DefWindowProcA(hWnd, v5, wParam, lParam);
  }
  if ( uMsg > 0x20A )
  {
    switch ( uMsg )
    {
      case 0x214u:
        WIN_Sizing(wParam, (tagRECT *)lParam);
        break;
      case 0x231u:
        win32.movingWindow = 1;
        break;
      case 0x232u:
        win32.movingWindow = 0;
        break;
    }
    return DefWindowProcA(hWnd, v5, wParam, lParam);
  }
  if ( uMsg == 522 )
  {
    v14 = abs32(SHIWORD(wParam) / 120);
    if ( v14 > 0 )
    {
      v15 = v14;
      do
      {
        Sys_QueEvent(win32.sysMsgTime, SE_KEY, (SHIWORD(wParam) / 120 >= 0) + 195, 1, 0, 0);
        Sys_QueEvent(win32.sysMsgTime, SE_KEY, (SHIWORD(wParam) / 120 >= 0) + 195, 0, 0, 0);
        --v15;
      }
      while ( v15 );
      v5 = uMsg;
    }
    return DefWindowProcA(hWnd, v5, wParam, lParam);
  }
  switch ( uMsg )
  {
    case 0x104u:
      if ( wParam != 13 )
        goto LABEL_42;
      v10 = cvarSystem->__vftable;
      v11 = ((int (__thiscall *)(idRenderSystem *, _DWORD))renderSystem->IsFullScreen)(renderSystem, 0);
      LOBYTE(v11) = (_BYTE)v11 == 0;
      ((void (__thiscall *)(idCVarSystem *, const char *, int))v10->SetCVarBool)(cvarSystem, "r_fullscreen", v11);
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "vid_restart\n");
      result = 0;
      break;
    case 0x105u:
      goto $L116697;
    case 0x112u:
      if ( wParam != 61760 && wParam != 61696 )
        return DefWindowProcA(hWnd, v5, wParam, lParam);
      result = 0;
      break;
    case 0x113u:
      if ( __unnamed::win_timerUpdate.internalVar->integerValue )
        (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 20))(common.type);
      return DefWindowProcA(hWnd, v5, wParam, lParam);
    default:
      return DefWindowProcA(hWnd, v5, wParam, lParam);
  }
  return result;
}
