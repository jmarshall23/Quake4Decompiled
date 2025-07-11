
// FUNC: long __stdcall MyTaskKeyHookLL(int,unsigned int,long)
LRESULT __stdcall MyTaskKeyHookLL(int nCode, unsigned int wp, int *lp)
{
  SHORT AsyncKeyState; // ax
  int v4; // ecx
  int v5; // eax

  if ( nCode )
    return CallNextHookEx(g_hHookKbdLL, nCode, wp, (LPARAM)lp);
  AsyncKeyState = GetAsyncKeyState(17);
  v4 = *lp;
  v5 = AsyncKeyState >> 15;
  if ( (*lp != 27 || !v5)
    && (v4 != 9 || (lp[2] & 0x20) == 0)
    && (v4 != 27 || (lp[2] & 0x20) == 0)
    && v4 != 91
    && v4 != 92 )
  {
    return CallNextHookEx(g_hHookKbdLL, nCode, wp, (LPARAM)lp);
  }
  if ( g_bBeep && (wp == 260 || wp == 256) )
    MessageBeep(0);
  return 1;
}

// FUNC: void __cdecl DisableTaskKeys(int,int,int)
void __cdecl DisableTaskKeys(HKEY bDisable, int bBeep, unsigned int bTaskMgr)
{
  HKEY v3; // esi

  v3 = bDisable;
  if ( bDisable )
  {
    if ( !g_hHookKbdLL )
      g_hHookKbdLL = SetWindowsHookExA(13, (HOOKPROC)MyTaskKeyHookLL, win32.hInstance, 0);
  }
  else if ( g_hHookKbdLL )
  {
    UnhookWindowsHookEx(g_hHookKbdLL);
    g_hHookKbdLL = 0;
  }
  g_bBeep = bBeep;
  if ( bTaskMgr )
  {
    if ( RegOpenKeyA(HKEY_CURRENT_USER, KEY_DisableTaskMgr, &bDisable) )
      RegCreateKeyA(HKEY_CURRENT_USER, KEY_DisableTaskMgr, &bDisable);
    if ( v3 )
    {
      bBeep = 1;
      RegSetValueExA(bDisable, VAL_DisableTaskMgr, 0, 4u, (const BYTE *)&bBeep, 4u);
    }
    else
    {
      RegDeleteValueA(bDisable, VAL_DisableTaskMgr);
    }
  }
}
