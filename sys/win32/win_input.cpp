
// FUNC: bool __cdecl IN_StartupKeyboard(void)
char __cdecl IN_StartupKeyboard()
{
  IDirectInputA *g_pdi; // ecx
  int v2; // eax
  DIPROPDWORD dipdw; // [esp+28h] [ebp-14h] BYREF

  g_pdi = win32.g_pdi;
  if ( !win32.g_pdi )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "keyboard: DirectInput has not been started\n");
    return 0;
  }
  if ( win32.g_pKeyboard )
  {
    win32.g_pKeyboard->Release(win32.g_pKeyboard);
    g_pdi = win32.g_pdi;
    win32.g_pKeyboard = 0;
  }
  if ( g_pdi->CreateDevice(g_pdi, &GUID_SysKeyboard, &win32.g_pKeyboard, 0) < 0 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "keyboard: couldn't find a keyboard device\n");
    return 0;
  }
  if ( win32.g_pKeyboard->SetDataFormat(win32.g_pKeyboard, &c_dfDIKeyboard) < 0 )
    return 0;
  v2 = win32.g_pKeyboard->SetCooperativeLevel(win32.g_pKeyboard, win32.hWnd, 22u);
  if ( v2 == -2147467263 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "keyboard: SetCooperativeLevel() returned DIERR_UNSUPPORTED.\n"
      "For security reasons, background exclusive keyboard access is not allowed.\n");
    return 0;
  }
  if ( v2 < 0 )
    return 0;
  dipdw.diph.dwSize = 20;
  dipdw.diph.dwHeaderSize = 16;
  dipdw.diph.dwObj = 0;
  dipdw.diph.dwHow = 0;
  dipdw.dwData = 256;
  if ( win32.g_pKeyboard->SetProperty(win32.g_pKeyboard, (const _GUID *)1, (const DIPROPHEADER *)&dipdw) < 0 )
    return 0;
  win32.g_pKeyboard->Acquire(win32.g_pKeyboard);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "keyboard: DirectInput initialized.\n");
  return 1;
}

// FUNC: void __cdecl IN_InitDirectInput(void)
void __cdecl IN_InitDirectInput()
{
  HMODULE ModuleHandleA; // eax

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Initializing DirectInput...\n");
  if ( win32.g_pdi )
  {
    win32.g_pdi->Release(win32.g_pdi);
    win32.g_pdi = 0;
  }
  ModuleHandleA = GetModuleHandleA(0);
  if ( DirectInputCreateA((int)ModuleHandleA, 1792, (int)&win32.g_pdi, 0) < 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "iDirectInputCreate failed\n");
}

// FUNC: void __cdecl IN_DeactivateMouse(void)
void __cdecl IN_DeactivateMouse()
{
  int i; // esi

  if ( win32.g_pMouse && win32.mouseGrabbed )
  {
    win32.g_pMouse->Unacquire(win32.g_pMouse);
    for ( i = 0; i < 10; ++i )
    {
      if ( ShowCursor(1) >= 0 )
        break;
    }
    win32.mouseGrabbed = 0;
  }
}

// FUNC: void __cdecl Sys_ShutdownInput(void)
void __cdecl Sys_ShutdownInput()
{
  IN_DeactivateMouse();
  if ( win32.g_pKeyboard )
  {
    win32.g_pKeyboard->Unacquire(win32.g_pKeyboard);
    if ( win32.g_pKeyboard )
    {
      win32.g_pKeyboard->Release(win32.g_pKeyboard);
      win32.g_pKeyboard = 0;
    }
  }
  if ( win32.g_pMouse )
  {
    win32.g_pMouse->Release(win32.g_pMouse);
    win32.g_pMouse = 0;
  }
  if ( win32.g_pdi )
  {
    win32.g_pdi->Release(win32.g_pdi);
    win32.g_pdi = 0;
  }
}

// FUNC: int __cdecl Sys_PollKeyboardInputEvents(void)
// local variable allocation has failed, the output may be wrong!
int __cdecl Sys_PollKeyboardInputEvents()
{
  signed int v1; // ebx
  DIDEVICEOBJECTDATA *v2; // edi
  bool v3; // al
  bool v4; // zf
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int TickCount; // eax
  int v10; // [esp+4h] [ebp-20h]
  int v11; // [esp+4h] [ebp-20h]
  int v12; // [esp+4h] [ebp-20h]
  unsigned int dwElements; // [esp+1Ch] [ebp-8h] BYREF
  BOOL state; // [esp+20h] [ebp-4h] OVERLAPPED

  if ( win32.g_pKeyboard )
  {
    dwElements = 256;
    if ( win32.g_pKeyboard->GetDeviceData(win32.g_pKeyboard, 16u, polled_didod, &dwElements, 0) )
    {
      if ( win32.g_pKeyboard->Acquire(win32.g_pKeyboard) >= 0 )
      {
        win32.g_pKeyboard->GetDeviceData(win32.g_pKeyboard, 16u, 0, &dwElements, 0);
        return sys->GetNumKeyPresses(sys);
      }
    }
    else
    {
      v1 = 0;
      if ( (int)dwElements > 0 )
      {
        v2 = polled_didod;
        do
        {
          v3 = (v2->dwData & 0x80) == 0x80;
          v5 = v2->dwOfs - 29;
          v4 = v2->dwOfs == 29;
          LOBYTE(state) = v3;
          if ( v4 )
          {
            v12 = v3;
            TickCount = GetTickCount();
            Sys_QueEvent(TickCount, SE_KEY, 141, v12, 0, 0);
            sys->AddKeyPress(sys, 141, state);
          }
          else
          {
            v6 = v5 - 154;
            if ( v6 )
            {
              if ( v6 == 1 )
              {
                v10 = v3;
                v7 = GetTickCount();
                Sys_QueEvent(v7, SE_KEY, 253, v10, 0, 0);
                sys->AddKeyPress(sys, 253, state);
              }
            }
            else
            {
              v11 = v3;
              v8 = GetTickCount();
              Sys_QueEvent(v8, SE_KEY, 252, v11, 0, 0);
              sys->AddKeyPress(sys, 252, state);
            }
          }
          ++v1;
          ++v2;
        }
        while ( v1 < (int)dwElements );
      }
    }
  }
  return sys->GetNumKeyPresses(sys);
}

// FUNC: int __cdecl Sys_ReturnKeyboardInputEvent(int,int &,bool &)
BOOL __cdecl Sys_ReturnKeyboardInputEvent(int n, int *ch, bool *state)
{
  return sys->GetKeyPress(sys, n, ch, state);
}

// FUNC: void __cdecl Sys_QueMouseEvents(int)
void __cdecl Sys_QueMouseEvents(int dwElements)
{
  int *p_dwData; // esi
  int v2; // ebp
  unsigned int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // ebx

  if ( dwElements > 0 )
  {
    p_dwData = (int *)&polled_didod[0].dwData;
    v2 = dwElements;
    do
    {
      v3 = *(p_dwData - 1);
      if ( v3 < 0xC || v3 > 0x13 )
      {
        if ( v3 )
        {
          if ( v3 == 4 )
          {
            Sys_QueEvent(p_dwData[1], SE_MOUSE, 0, *p_dwData, 0, 0);
          }
          else if ( v3 == 8 )
          {
            v4 = abs32(*p_dwData / 120);
            v5 = (*p_dwData / 120 >= 0) + 195;
            if ( v4 > 0 )
            {
              v6 = v4;
              do
              {
                Sys_QueEvent(p_dwData[1], SE_KEY, v5, 1, 0, 0);
                Sys_QueEvent(p_dwData[1], SE_KEY, v5, 0, 0, 0);
                --v6;
              }
              while ( v6 );
            }
          }
        }
        else
        {
          Sys_QueEvent(p_dwData[1], SE_MOUSE, *p_dwData, 0, 0, 0);
        }
      }
      else
      {
        Sys_QueEvent(p_dwData[1], SE_KEY, v3 + 175, (*p_dwData & 0x80) == 0x80, 0, 0);
      }
      p_dwData += 4;
      --v2;
    }
    while ( v2 );
  }
}

// FUNC: int __cdecl Sys_PollMouseInputEvents(void)
unsigned int __thiscall Sys_PollMouseInputEvents(void *this)
{
  unsigned int dwElements; // [esp+18h] [ebp-4h] BYREF

  dwElements = (unsigned int)this;
  if ( !win32.g_pMouse || !win32.mouseGrabbed )
    return 0;
  dwElements = 256;
  if ( win32.g_pMouse->GetDeviceData(win32.g_pMouse, 16u, polled_didod, &dwElements, 0) )
  {
    if ( win32.g_pMouse->Acquire(win32.g_pMouse) < 0 )
      return 0;
    win32.g_pMouse->GetDeviceData(win32.g_pMouse, 16u, polled_didod, &dwElements, 0);
  }
  Sys_QueMouseEvents(dwElements);
  return dwElements;
}

// FUNC: int __cdecl Sys_ReturnMouseInputEvent(int,int &,int &)
BOOL __cdecl Sys_ReturnMouseInputEvent(int n, int *action, int *value)
{
  signed int dwOfs; // ecx

  dwOfs = polled_didod[n].dwOfs;
  if ( dwOfs < 12 || dwOfs > 19 )
  {
    if ( dwOfs )
    {
      if ( dwOfs == 4 )
      {
        *value = polled_didod[n].dwData;
        *action = 9;
        return 1;
      }
      else if ( dwOfs == 8 )
      {
        *value = (signed int)polled_didod[n].dwData / 120;
        *action = 10;
        return *value != 0;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      *value = polled_didod[n].dwData;
      *action = 8;
      return 1;
    }
  }
  else
  {
    *value = (polled_didod[n].dwData & 0x80) == 0x80;
    *action = dwOfs - 12;
    return 1;
  }
}

// FUNC: void __cdecl Sys_QueJoystickEvents(int)
void __cdecl Sys_QueJoystickEvents(int dwElements)
{
  int v1; // esi
  int i; // edi
  int v3; // eax

  v1 = 0;
  for ( i = Sys_Milliseconds(); v1 < dwElements; ++v1 )
  {
    if ( v1 >= 0 )
    {
      if ( v1 >= 16 )
      {
        if ( v1 < 22 )
        {
          v3 = *(&polled_didod[252].dwOfs + v1);
          if ( v3 )
            Sys_QueEvent(i, SE_JOYSTICK_AXIS, v1 - 16, v3, 0, 0);
        }
      }
      else if ( (joystickDigitalButtons[v1] & 2) != 0 )
      {
        Sys_QueEvent(i, SE_KEY, digitalXlat[v1] + 197, joystickDigitalButtons[v1] & 1, 0, 0);
      }
    }
  }
}

// FUNC: int __cdecl Sys_ReturnJoystickInputEvent(int,int &,int &)
int __cdecl Sys_ReturnJoystickInputEvent(int n, int *action, int *value)
{
  if ( n < 0 )
    return 1;
  if ( n < 16 )
  {
    *action = digitalXlat[n];
    *value = joystickDigitalButtons[n] & 1;
    return 1;
  }
  if ( n - 16 < 6 )
  {
    *action = n;
    *value = joystickAxises[n - 16];
    return 1;
  }
  return 0;
}

// FUNC: void __cdecl IN_ActivateMouse(void)
void __cdecl IN_ActivateMouse()
{
  int i; // esi

  if ( __unnamed::in_mouse.internalVar->integerValue && !win32.mouseGrabbed && win32.g_pMouse )
  {
    win32.mouseGrabbed = 1;
    for ( i = 0; i < 10; ++i )
    {
      if ( ShowCursor(0) < 0 )
        break;
    }
    if ( win32.g_pMouse->Acquire(win32.g_pMouse) >= 0 )
      win32.g_pMouse->SetCooperativeLevel(win32.g_pMouse, win32.hWnd, 5u);
  }
}

// FUNC: void __cdecl IN_Frame(void)
void __cdecl IN_Frame()
{
  bool v0; // al

  if ( win32.g_pMouse && win32.g_pKeyboard )
  {
    v0 = __unnamed::in_mouse.internalVar->integerValue != 0;
    if ( !win32.cdsFullscreen )
    {
      if ( win32.mouseReleased )
        v0 = 0;
      if ( win32.movingWindow )
        v0 = 0;
      if ( !win32.activeApp )
        v0 = 0;
    }
    if ( v0 != win32.mouseGrabbed )
    {
      if ( win32.mouseGrabbed )
        IN_DeactivateMouse();
      else
        IN_ActivateMouse();
    }
  }
}

// FUNC: void __cdecl Sys_GrabMouseCursor(bool)
void __cdecl Sys_GrabMouseCursor(bool grabIt)
{
  win32.mouseReleased = !grabIt;
  if ( !grabIt )
    IN_Frame();
}

// FUNC: int __cdecl Sys_PollJoystickInputEvents(void)
int __cdecl Sys_PollJoystickInputEvents()
{
  if ( !__unnamed::in_joystick.internalVar->integerValue )
    return 0;
  rvInput::GetInput(&joystickInput);
  Sys_QueJoystickEvents(22);
  return 22;
}

// FUNC: bool __cdecl Sys_IsJoystickEnabled(void)
BOOL __cdecl Sys_IsJoystickEnabled()
{
  return __unnamed::in_joystick.internalVar->integerValue != 0;
}

// FUNC: bool __cdecl IN_InitDIMouse(void)
char __cdecl IN_InitDIMouse()
{
  void *v1; // ecx
  DIPROPDWORD dipdw; // [esp+24h] [ebp-14h] BYREF

  if ( !win32.g_pdi )
    return 0;
  if ( win32.g_pdi->CreateDevice(win32.g_pdi, &GUID_SysMouse, &win32.g_pMouse, 0) < 0 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "mouse: Couldn't open DI mouse device\n");
    return 0;
  }
  if ( win32.g_pMouse->SetDataFormat(win32.g_pMouse, &c_dfDIMouse2) < 0 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "mouse: Couldn't set DI mouse format\n");
    return 0;
  }
  if ( win32.g_pMouse->SetCooperativeLevel(win32.g_pMouse, win32.hWnd, 5u) < 0 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "mouse: Couldn't set DI coop level\n");
    return 0;
  }
  dipdw.diph.dwSize = 20;
  dipdw.diph.dwHeaderSize = 16;
  dipdw.diph.dwObj = 0;
  dipdw.diph.dwHow = 0;
  dipdw.dwData = 256;
  if ( win32.g_pMouse->SetProperty(win32.g_pMouse, (const _GUID *)1, (const DIPROPHEADER *)&dipdw) < 0 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "mouse: Couldn't set DI buffersize\n");
    return 0;
  }
  IN_ActivateMouse();
  Sys_PollMouseInputEvents(v1);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "mouse: DirectInput initialized.\n");
  return 1;
}

// FUNC: void __cdecl Sys_InitInput(void)
void __cdecl Sys_InitInput()
{
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "\n------------ Input Initialization -----------\n");
  IN_InitDirectInput();
  if ( __unnamed::in_mouse.internalVar->integerValue )
  {
    IN_InitDIMouse();
    sys->GrabMouseCursor(sys, 0);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Mouse control not active.\n");
  }
  IN_StartupKeyboard();
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
  BYTE2(__unnamed::in_mouse.internalVar->flags) &= ~4u;
}
