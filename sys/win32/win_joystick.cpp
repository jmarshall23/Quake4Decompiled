
// FUNC: public: int __thiscall rvInput::ConvertThumbstickValue(unsigned int)
int __thiscall rvInput::ConvertThumbstickValue(rvInput *this, unsigned int sThumbstickValue)
{
  if ( sThumbstickValue > 0x9998 )
    return (int)((1.0 - cos((double)(sThumbstickValue - 39320) * 0.000038147555 * 1.5707964)) * 127.0);
  if ( sThumbstickValue >= 0x6666 )
    return 0;
  return (int)((1.0 - cos(((double)sThumbstickValue * 0.000038147555 - 1.0) * 1.570796370506287)) * -127.0);
}

// FUNC: public: void __thiscall rvInput::GetInput(void)
void __thiscall rvInput::GetInput(rvInput *this)
{
  int v2; // edi
  BOOL v3; // eax
  BOOL v4; // ecx
  BOOL v5; // ecx
  unsigned __int16 v6; // ax
  int wDigitalButtons; // esi
  int wOldDigitalButtons; // edi
  int v9; // eax
  _DWORD *v10; // edx
  int v11; // ebp
  int v12; // [esp+Ch] [ebp-38h]
  joyinfoex_tag InputState; // [esp+10h] [ebp-34h] BYREF

  this->mNoControllers = 0;
  v2 = dword_1131A19C;
  InputState.dwSize = 52;
  InputState.dwFlags = 255;
  v3 = joyGetPosEx(0, &InputState) == 0;
  dword_1131A19C = v3;
  v4 = v2 && !v3;
  dword_1131A1A4 = v4;
  v5 = !v2 && v3;
  dword_1131A1A0 = v5;
  if ( !v3 )
  {
    ++this->mNoControllers;
    return;
  }
  if ( v5 )
  {
    *(_DWORD *)&rvInput::mGamepads[0].wDigitalButtons = 0;
    dword_1131A1A4 = 0;
    dword_1131A1AC = 0;
    dword_1131A1B0 = 0;
    dword_1131A19C = 1;
    dword_1131A1A0 = 1;
    dword_1131A1A8 = 1;
  }
  joystickAxises[0] = rvInput::ConvertThumbstickValue(this, InputState.dwXpos);
  dword_1131A144 = rvInput::ConvertThumbstickValue(this, InputState.dwYpos);
  dword_1131A148 = rvInput::ConvertThumbstickValue(this, InputState.dwUpos);
  dword_1131A14C = rvInput::ConvertThumbstickValue(this, InputState.dwRpos);
  LOBYTE(v6) = InputState.dwButtons;
  rvInput::mGamepads[0].wDigitalButtons = InputState.dwButtons;
  if ( InputState.dwPOV > 0x4650 )
  {
    switch ( InputState.dwPOV )
    {
      case 0x57E4u:
        HIBYTE(v6) = BYTE1(InputState.dwButtons) | 0xC0;
        break;
      case 0x6978u:
        HIBYTE(v6) = BYTE1(InputState.dwButtons) | 0x80;
        break;
      case 0x7B0Cu:
        HIBYTE(v6) = BYTE1(InputState.dwButtons) | 0x90;
        break;
      default:
        goto LABEL_32;
    }
  }
  else if ( InputState.dwPOV == 18000 )
  {
    HIBYTE(v6) = BYTE1(InputState.dwButtons) | 0x40;
  }
  else if ( InputState.dwPOV > 0x2328 )
  {
    if ( InputState.dwPOV != 13500 )
      goto LABEL_32;
    HIBYTE(v6) = BYTE1(InputState.dwButtons) | 0x60;
  }
  else if ( InputState.dwPOV == 9000 )
  {
    HIBYTE(v6) = BYTE1(InputState.dwButtons) | 0x20;
  }
  else if ( InputState.dwPOV )
  {
    if ( InputState.dwPOV != 4500 )
      goto LABEL_32;
    HIBYTE(v6) = BYTE1(InputState.dwButtons) | 0x30;
  }
  else
  {
    HIBYTE(v6) = BYTE1(InputState.dwButtons) | 0x10;
  }
  rvInput::mGamepads[0].wDigitalButtons = v6;
LABEL_32:
  wDigitalButtons = rvInput::mGamepads[0].wDigitalButtons;
  wOldDigitalButtons = rvInput::mGamepads[0].wOldDigitalButtons;
  v9 = 2;
  v10 = &unk_1131A15C;
  v12 = 4;
  do
  {
    *(v10 - 1) = (((1 << (v9 - 2)) & wDigitalButtons) > 0)
               + 2 * ((((1 << (v9 - 2)) & wDigitalButtons) > 0) ^ (((1 << (v9 - 2)) & wOldDigitalButtons) > 0));
    *v10 = (((1 << (v9 - 1)) & wDigitalButtons) > 0)
         + 2 * ((((1 << (v9 - 1)) & wDigitalButtons) > 0) ^ (((1 << (v9 - 1)) & wOldDigitalButtons) > 0));
    v10[1] = (((1 << v9) & wDigitalButtons) > 0)
           + 2 * ((((1 << v9) & wDigitalButtons) > 0) ^ (((1 << v9) & wOldDigitalButtons) > 0));
    v11 = 1 << (v9 + 1);
    v9 += 4;
    v10 += 4;
    *(v10 - 2) = ((v11 & wDigitalButtons) > 0) + 2 * (((v11 & wDigitalButtons) > 0) ^ ((v11 & wOldDigitalButtons) > 0));
    --v12;
  }
  while ( v12 );
  rvInput::mGamepads[0].wOldDigitalButtons = rvInput::mGamepads[0].wDigitalButtons;
  dword_1131A1AC = 0;
}
