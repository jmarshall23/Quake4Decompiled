
// FUNC: public: void __thiscall usercmd_t::ByteSwap(void)
void __thiscall usercmd_t::ByteSwap(usercmd_t *this)
{
  __int16 v2; // ax
  __int16 v3; // cx
  __int16 v4; // ax
  __int16 v5; // dx

  v2 = LittleShort(this->angles[0]);
  v3 = this->angles[1];
  this->angles[0] = v2;
  v4 = LittleShort(v3);
  v5 = this->angles[2];
  this->angles[1] = v4;
  this->angles[2] = LittleShort(v5);
  this->sequence = LittleLong(this->sequence);
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::InhibitUsercmd(enum inhibit_t,bool)
void __thiscall idUsercmdGenLocal::InhibitUsercmd(idUsercmdGenLocal *this, inhibit_t subsystem, bool inhibit)
{
  int v3; // edx

  v3 = 1 << subsystem;
  if ( inhibit )
    this->inhibitCommands |= v3;
  else
    this->inhibitCommands &= ~v3;
}

// FUNC: public: virtual int __thiscall idUsercmdGenLocal::GetNumUserCommands(void)
int __thiscall idUsercmdGenLocal::GetNumUserCommands(idUsercmdGenLocal *this)
{
  return 120;
}

// FUNC: public: virtual char const * __thiscall idUsercmdGenLocal::GetUserCommandName(int)
const char *__thiscall idUsercmdGenLocal::GetUserCommandName(idUsercmdGenLocal *this, unsigned int index)
{
  if ( index > 0x77 )
    return &entityFilter;
  else
    return userCmdStrings[index].string;
}

// FUNC: public: virtual int __thiscall idUsercmdGenLocal::CommandStringUsercmdData(char const *)
usercmdButton_t __thiscall idUsercmdGenLocal::CommandStringUsercmdData(idUsercmdGenLocal *this, const char *cmdString)
{
  userCmdString_t *v2; // esi

  v2 = userCmdStrings;
  if ( !userCmdStrings[0].string )
    return 0;
  while ( idStr::Icmp(cmdString, v2->string) )
  {
    ++v2;
    if ( !v2->string )
      return 0;
  }
  return v2->button;
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::Init(void)
void __thiscall idUsercmdGenLocal::Init(idUsercmdGenLocal *this)
{
  this->initialized = 1;
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::Shutdown(void)
void __thiscall idUsercmdGenLocal::Shutdown(idUsercmdGenLocal *this)
{
  this->initialized = 0;
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::Clear(void)
void __thiscall idUsercmdGenLocal::Clear(idUsercmdGenLocal *this)
{
  memset(this->buttonState, 0, sizeof(this->buttonState));
  memset(this->keyState, 0, 0xFCu);
  *(_WORD *)&this->keyState[252] = 0;
  this->inhibitCommands = 0;
  this->mouseDy = 0;
  this->mouseDx = 0;
  this->mouseButton = 0;
  this->mouseDown = 0;
}

// FUNC: public: virtual class usercmd_t __thiscall idUsercmdGenLocal::TicCmd(int)
usercmd_t *__thiscall idUsercmdGenLocal::TicCmd(idUsercmdGenLocal *this, usercmd_t *result, int ticNumber)
{
  usercmd_t *v4; // eax

  if ( ticNumber > com_ticNumber + 1 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idUsercmdGenLocal::TicCmd ticNumber > com_ticNumber");
  v4 = result;
  qmemcpy(result, &this->buffered[ticNumber & 0x3F], sizeof(usercmd_t));
  return v4;
}

// FUNC: private: void __thiscall idUsercmdGenLocal::Key(int,bool)
void __thiscall idUsercmdGenLocal::Key(idUsercmdGenLocal *this, int keyNum, bool down)
{
  int UsercmdAction; // eax

  if ( this->keyState[keyNum] != down )
  {
    this->keyState[keyNum] = down;
    UsercmdAction = idKeyInput::GetUsercmdAction(keyNum);
    if ( down )
    {
      ++this->buttonState[UsercmdAction];
      if ( !this->inhibitCommands && UsercmdAction >= 28 && UsercmdAction <= 120 )
      {
        this->cmd.flags ^= 1u;
        this->cmd.impulse = UsercmdAction - 28;
      }
    }
    else if ( --this->buttonState[UsercmdAction] < 0 )
    {
      this->buttonState[UsercmdAction] = 0;
    }
  }
}

// FUNC: private: void __thiscall idUsercmdGenLocal::Mouse(void)
void __thiscall idUsercmdGenLocal::Mouse(idUsercmdGenLocal *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  bool v5; // zf
  int v6; // edi
  int v7; // eax
  int UsercmdAction; // eax
  int v9; // eax
  bool v11; // cc
  int v12; // eax
  int v13; // eax
  const idCmdArgs *v14; // [esp+0h] [ebp-18h]
  int value; // [esp+8h] [ebp-10h] BYREF
  int i; // [esp+Ch] [ebp-Ch]
  int action; // [esp+10h] [ebp-8h] BYREF
  int numEvents; // [esp+14h] [ebp-4h]

  v2 = Sys_PollMouseInputEvents();
  numEvents = v2;
  if ( v2 )
  {
    v3 = 0;
    i = 0;
    if ( v2 > 0 )
    {
      do
      {
        if ( Sys_ReturnMouseInputEvent(v3, &action, &value) )
        {
          if ( (unsigned int)action > 7 )
          {
            switch ( action )
            {
              case 8:
                v13 = value;
                this->mouseDx += value;
                this->continuousMouseX += v13;
                break;
              case 9:
                v12 = value;
                this->mouseDy += value;
                this->continuousMouseY += v12;
                break;
              case 10:
                v6 = (value >= 0) + 195;
                v7 = abs32(value);
                if ( v7 > 0 )
                {
                  do
                  {
                    v5 = this->keyState[v6];
                    value = v7 - 1;
                    if ( !v5 )
                    {
                      this->keyState[v6] = 1;
                      UsercmdAction = idKeyInput::GetUsercmdAction(v6);
                      ++this->buttonState[UsercmdAction];
                      if ( !this->inhibitCommands && UsercmdAction >= 28 && UsercmdAction <= 120 )
                      {
                        this->cmd.flags ^= 1u;
                        this->cmd.impulse = UsercmdAction - 28;
                      }
                    }
                    if ( this->keyState[v6] )
                    {
                      this->keyState[v6] = 0;
                      v9 = idKeyInput::GetUsercmdAction(v6);
                      if ( --this->buttonState[v9] < 0 )
                        this->buttonState[v9] = 0;
                    }
                    v7 = value;
                    v11 = value <= 0;
                    this->mouseButton = v6;
                    this->mouseDown = 1;
                  }
                  while ( !v11 );
                }
                v3 = i;
                value = v7 - 1;
                break;
            }
          }
          else
          {
            v4 = action + 187;
            v5 = value == 0;
            this->mouseButton = action + 187;
            this->mouseDown = !v5;
            idUsercmdGenLocal::Key(this, v4, !v5);
          }
        }
        i = ++v3;
      }
      while ( v3 < numEvents );
    }
  }
  SpawnStub(v14);
}

// FUNC: private: void __thiscall idUsercmdGenLocal::Keyboard(void)
void __thiscall idUsercmdGenLocal::Keyboard(idUsercmdGenLocal *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // esi
  const idCmdArgs *v5; // [esp+0h] [ebp-10h]
  BOOL state; // [esp+8h] [ebp-8h] BYREF
  int key; // [esp+Ch] [ebp-4h] BYREF

  v2 = Sys_PollKeyboardInputEvents();
  v3 = v2;
  if ( v2 )
  {
    v4 = 0;
    if ( v2 > 0 )
    {
      do
      {
        if ( Sys_ReturnKeyboardInputEvent(v4, &key, (bool *)&state) )
          idUsercmdGenLocal::Key(this, key, state);
        ++v4;
      }
      while ( v4 < v3 );
    }
  }
  SpawnStub(v5);
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::MouseState(int *,int *,int *,bool *)
void __thiscall idUsercmdGenLocal::MouseState(idUsercmdGenLocal *this, int *x, int *y, int *button, bool *down)
{
  *x = this->continuousMouseX;
  *y = this->continuousMouseY;
  *button = this->mouseButton;
  *down = this->mouseDown;
}

// FUNC: private: void __thiscall idUsercmdGenLocal::AdjustAngles(void)
void __thiscall idUsercmdGenLocal::AdjustAngles(idUsercmdGenLocal *this)
{
  double v2; // st7
  float floatValue; // [esp+8h] [ebp-4h]

  if ( this->toggled_run.on != (idUsercmdGenLocal::in_alwaysRun.internalVar->integerValue != 0) )
  {
    (*(void (__fastcall **)(netadrtype_t, int))(*(_DWORD *)common.type + 40))(
      common.type,
      this->toggled_run.on ^ (idUsercmdGenLocal::in_alwaysRun.internalVar->integerValue != 0));
    floatValue = idUsercmdGenLocal::in_angleSpeedKey.internalVar->floatValue;
    v2 = (double)(*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) * 0.001 * floatValue;
  }
  else
  {
    v2 = (double)(*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) * 0.001;
  }
  if ( this->buttonState[9] <= 0 )
  {
    this->viewangles.y = this->viewangles.y
                       - (double)(this->buttonState[4] > 0)
                       * idUsercmdGenLocal::in_yawSpeed.internalVar->floatValue
                       * v2;
    this->viewangles.y = (double)(this->buttonState[3] > 0)
                       * idUsercmdGenLocal::in_yawSpeed.internalVar->floatValue
                       * v2
                       + this->viewangles.y;
  }
  this->viewangles.x = this->viewangles.x
                     - (double)(this->buttonState[7] > 0)
                     * idUsercmdGenLocal::in_pitchSpeed.internalVar->floatValue
                     * v2;
  this->viewangles.x = (double)(this->buttonState[8] > 0)
                     * idUsercmdGenLocal::in_pitchSpeed.internalVar->floatValue
                     * v2
                     + this->viewangles.x;
}

// FUNC: private: void __thiscall idUsercmdGenLocal::KeyMove(void)
void __thiscall idUsercmdGenLocal::KeyMove(idUsercmdGenLocal *this)
{
  int v1; // esi
  int v2; // edx
  int v3; // eax
  char v4; // al
  int side; // [esp+8h] [ebp-4h]

  v1 = 0;
  if ( this->buttonState[9] > 0 )
    v1 = 127 * ((this->buttonState[4] > 0) - (this->buttonState[3] > 0));
  side = 127 * ((this->buttonState[11] > 0) - (this->buttonState[10] > 0)) + v1;
  v2 = 127 * ((this->buttonState[1] > 0) - this->toggled_crouch.on);
  v3 = 127 * ((this->buttonState[5] > 0) - (this->buttonState[6] > 0));
  if ( v3 >= -128 )
  {
    if ( v3 > 127 )
      LOBYTE(v3) = 127;
  }
  else
  {
    LOBYTE(v3) = 0x80;
  }
  this->cmd.forwardmove = v3;
  v4 = side;
  if ( side >= -128 )
  {
    if ( side > 127 )
      v4 = 127;
  }
  else
  {
    v4 = 0x80;
  }
  this->cmd.rightmove = v4;
  if ( v2 >= -128 )
  {
    if ( v2 <= 127 )
      this->cmd.upmove = v2;
    else
      this->cmd.upmove = 127;
  }
  else
  {
    this->cmd.upmove = 0x80;
  }
}

// FUNC: private: void __thiscall idUsercmdGenLocal::MouseMove(void)
void __thiscall idUsercmdGenLocal::MouseMove(idUsercmdGenLocal *this)
{
  int v1; // edi
  idUsercmdGenLocal *v2; // esi
  unsigned int v3; // eax
  int integerValue; // ebp
  double v5; // st7
  int v6; // eax
  double v7; // st6
  int v8; // edi
  unsigned int v9; // ebx
  unsigned int v10; // eax
  unsigned int v11; // ecx
  unsigned int v12; // edx
  unsigned int v13; // esi
  int v14; // ecx
  int v15; // ebp
  double v16; // st5
  int v17; // eax
  int v18; // ebp
  double v19; // st5
  double v20; // st7
  double v21; // st6
  int v22; // eax
  double v23; // st5
  int v24; // edi
  unsigned int v25; // ebx
  unsigned int v26; // eax
  unsigned int v27; // ecx
  unsigned int v28; // edx
  unsigned int v29; // esi
  int v30; // ecx
  int v31; // ebp
  double v32; // st4
  int v33; // eax
  double v34; // st4
  int v35; // ecx
  double v36; // st7
  long double v37; // st7
  long double v38; // st7
  int v39; // eax
  int v40; // eax
  float mx; // [esp+2Ch] [ebp-18h]
  float mxa; // [esp+2Ch] [ebp-18h]
  int i; // [esp+30h] [ebp-14h]
  int ia; // [esp+30h] [ebp-14h]
  int ib; // [esp+30h] [ebp-14h]
  int strafeMy; // [esp+34h] [ebp-10h]
  int strafeMya; // [esp+34h] [ebp-10h]
  float strafeMyb; // [esp+34h] [ebp-10h]
  float fabsmxa; // [esp+38h] [ebp-Ch]
  float fabsmyb; // [esp+3Ch] [ebp-8h]
  int fabsmy; // [esp+3Ch] [ebp-8h]
  float fabsmya; // [esp+3Ch] [ebp-8h]
  float mySign; // [esp+40h] [ebp-4h]

  v1 = historyCounter;
  v2 = this;
  v3 = 2 * (historyCounter & 7);
  history[v3 / 2][0] = this->mouseDx;
  dword_10DFA7FC[v3] = this->mouseDy;
  integerValue = idUsercmdGenLocal::m_smooth.internalVar->integerValue;
  strafeMy = integerValue;
  if ( integerValue >= 1 )
  {
    if ( integerValue <= 8 )
      goto LABEL_6;
    integerValue = 8;
  }
  else
  {
    integerValue = 1;
  }
  strafeMy = integerValue;
LABEL_6:
  v5 = 0.0;
  v6 = 0;
  v7 = 0.0;
  if ( integerValue >= 4 )
  {
    v8 = v1 - 2;
    v9 = ((unsigned int)(integerValue - 4) >> 2) + 1;
    i = 4 * v9;
    do
    {
      v10 = 2 * (((_BYTE)v8 + 2) & 7);
      v11 = 2 * (((_BYTE)v8 + 1) & 7);
      v12 = 2 * (v8 & 7);
      v13 = 2 * (((_BYTE)v8 - 1) & 7);
      v8 -= 4;
      --v9;
      v5 = v5
         + (double)history[v10 / 2][0]
         + (double)history[v11 / 2][0]
         + (double)history[v12 / 2][0]
         + (double)history[v13 / 2][0];
      v7 = v7
         + (double)dword_10DFA7FC[v10]
         + (double)dword_10DFA7FC[v11]
         + (double)dword_10DFA7FC[v12]
         + (double)dword_10DFA7FC[v13];
    }
    while ( v9 );
    v1 = historyCounter;
    v6 = i;
    v2 = this;
  }
  if ( v6 < integerValue )
  {
    v14 = v1 - v6;
    v15 = integerValue - v6;
    do
    {
      v16 = (double)history[v14 & 7][0];
      v17 = 2 * (v14-- & 7);
      --v15;
      v5 = v5 + v16;
      v7 = v7 + (double)dword_10DFA7FC[v17];
    }
    while ( v15 );
  }
  v18 = idUsercmdGenLocal::m_strafeSmooth.internalVar->integerValue;
  v19 = 1.0 / (double)strafeMy;
  strafeMya = v18;
  mx = v19 * v5;
  v20 = v19 * v7;
  if ( v18 >= 1 )
  {
    if ( v18 <= 8 )
      goto LABEL_18;
    v18 = 8;
  }
  else
  {
    v18 = 1;
  }
  strafeMya = v18;
LABEL_18:
  v21 = 0.0;
  v22 = 0;
  v23 = 0.0;
  if ( v18 >= 4 )
  {
    v24 = v1 - 2;
    v25 = ((unsigned int)(v18 - 4) >> 2) + 1;
    ia = 4 * v25;
    do
    {
      v26 = 2 * (((_BYTE)v24 + 2) & 7);
      v27 = 2 * (((_BYTE)v24 + 1) & 7);
      v28 = 2 * (v24 & 7);
      v29 = 2 * (((_BYTE)v24 - 1) & 7);
      v24 -= 4;
      --v25;
      v21 = v21
          + (double)history[v26 / 2][0]
          + (double)history[v27 / 2][0]
          + (double)history[v28 / 2][0]
          + (double)history[v29 / 2][0];
      v23 = v23
          + (double)dword_10DFA7FC[v26]
          + (double)dword_10DFA7FC[v27]
          + (double)dword_10DFA7FC[v28]
          + (double)dword_10DFA7FC[v29];
    }
    while ( v25 );
    v1 = historyCounter;
    v2 = this;
    v22 = ia;
  }
  if ( v22 < v18 )
  {
    v30 = v1 - v22;
    v31 = v18 - v22;
    do
    {
      v32 = (double)history[v30 & 7][0];
      v33 = 2 * (v30-- & 7);
      --v31;
      v21 = v21 + v32;
      v23 = v23 + (double)dword_10DFA7FC[v33];
    }
    while ( v31 );
  }
  historyCounter = v1 + 1;
  v34 = 1.0 / (double)strafeMya;
  *(float *)&ib = v34 * v21;
  strafeMyb = v34 * v23;
  if ( COERCE_FLOAT(LODWORD(mx) & 0x7FFFFFFF) > 1000.0
    || (fabsmxa = v20, COERCE_FLOAT(LODWORD(fabsmxa) & 0x7FFFFFFF) > 1000.0) )
  {
    Sys_DebugPrintf("idUsercmdGenLocal::MouseMove: Ignoring ridiculous mouse delta.\n");
    v20 = 0.0;
    mx = 0.0;
  }
  if ( idUsercmdGenLocal::m_maxInput.internalVar->floatValue != 0.0 )
  {
    fabsmyb = v20;
    fabsmy = LODWORD(fabsmyb) & 0x7FFFFFFF;
    if ( COERCE_FLOAT(LODWORD(mx) & 0x7FFFFFFF) > (double)idUsercmdGenLocal::m_maxInput.internalVar->floatValue )
      mx = mx / COERCE_FLOAT(LODWORD(mx) & 0x7FFFFFFF) * idUsercmdGenLocal::m_maxInput.internalVar->floatValue;
    if ( *(float *)&fabsmy > (double)idUsercmdGenLocal::m_maxInput.internalVar->floatValue )
    {
      mySign = v20 / *(float *)&fabsmy;
      v20 = mySign * idUsercmdGenLocal::m_maxInput.internalVar->floatValue;
    }
  }
  mxa = mx * idUsercmdGenLocal::sensitivity.internalVar->floatValue;
  fabsmya = v20 * idUsercmdGenLocal::sensitivity.internalVar->floatValue;
  if ( idUsercmdGenLocal::m_showMouseRate.internalVar->integerValue )
    Sys_DebugPrintf(
      "[%3i %3i  = %5.1f %5.1f = %5.1f %5.1f] ",
      v2->mouseDx,
      v2->mouseDy,
      mxa,
      fabsmya,
      *(float *)&ib,
      strafeMyb);
  v2->mouseDx = 0;
  v2->mouseDy = 0;
  if ( *(float *)&ib != 0.0 || strafeMyb != 0.0 )
  {
    v35 = v2->buttonState[9];
    if ( v35 > 0 || (v2->cmd.buttons & 0x10) == 0 )
    {
      *(float *)&ib = *(float *)&ib * idUsercmdGenLocal::m_strafeScale.internalVar->floatValue;
      v36 = strafeMyb * idUsercmdGenLocal::m_strafeScale.internalVar->floatValue;
      strafeMyb = v36;
      v37 = sqrt(v36 * strafeMyb + *(float *)&ib * *(float *)&ib);
      if ( v37 > 127.0 )
      {
        v38 = 1.0 / v37;
        *(float *)&ib = *(float *)&ib * v38 * 127.0;
        strafeMyb = v38 * strafeMyb * 127.0;
      }
    }
    if ( v35 > 0 )
    {
      v39 = (int)((double)v2->cmd.rightmove + *(float *)&ib);
      if ( v39 >= -128 )
      {
        if ( v39 > 127 )
          LOBYTE(v39) = 127;
      }
      else
      {
        LOBYTE(v39) = 0x80;
      }
      v2->cmd.rightmove = v39;
    }
    else
    {
      v2->viewangles.y = v2->viewangles.y - mxa * idUsercmdGenLocal::m_yaw.internalVar->floatValue;
    }
    if ( v2->buttonState[9] <= 0 && (v2->cmd.buttons & 0x10) != 0 )
    {
      v2->viewangles.x = fabsmya * idUsercmdGenLocal::m_pitch.internalVar->floatValue + v2->viewangles.x;
    }
    else
    {
      v40 = (int)((double)v2->cmd.forwardmove - strafeMyb);
      if ( v40 >= -128 )
      {
        if ( v40 > 127 )
          LOBYTE(v40) = 127;
        v2->cmd.forwardmove = v40;
      }
      else
      {
        v2->cmd.forwardmove = 0x80;
      }
    }
  }
}

// FUNC: private: void __thiscall idUsercmdGenLocal::JoystickMove(void)
void __thiscall idUsercmdGenLocal::JoystickMove(idUsercmdGenLocal *this)
{
  double v1; // st7
  double v2; // st7
  float v3; // [esp+0h] [ebp-8h]
  float v4; // [esp+4h] [ebp-4h]

  v1 = (double)this->slowJoystick * 0.01;
  this->viewangles.y = this->viewangles.y
                     - (double)this->joystickAxis[0] * idUsercmdGenLocal::m_yaw.internalVar->floatValue * v1;
  this->viewangles.x = (double)this->joystickAxis[1] * idUsercmdGenLocal::m_pitch.internalVar->floatValue * v1
                     + this->viewangles.x;
  v3 = (double)this->joystickAxis[2] * 0.0078740157 * 127.0;
  v2 = (double)this->joystickAxis[3];
  this->cmd.rightmove += (int)v3;
  v4 = v2 * 0.0078740157 * 127.0;
  this->cmd.forwardmove -= (int)v4;
}

// FUNC: private: void __thiscall idUsercmdGenLocal::CmdButtons(void)
void __thiscall idUsercmdGenLocal::CmdButtons(idUsercmdGenLocal *this)
{
  this->cmd.buttons = 0;
  if ( this->buttonState[12] > 0 )
    this->cmd.buttons = 256;
  if ( this->buttonState[13] > 0 )
    HIBYTE(this->cmd.buttons) |= 2u;
  if ( this->buttonState[14] > 0 )
    HIBYTE(this->cmd.buttons) |= 4u;
  if ( this->buttonState[15] > 0 )
    HIBYTE(this->cmd.buttons) |= 8u;
  if ( this->buttonState[16] > 0 )
    HIBYTE(this->cmd.buttons) |= 0x10u;
  if ( this->buttonState[17] > 0 )
    HIBYTE(this->cmd.buttons) |= 0x20u;
  if ( this->buttonState[18] > 0 )
    HIBYTE(this->cmd.buttons) |= 0x40u;
  if ( this->buttonState[19] > 0 )
    this->cmd.buttons |= 0x8000u;
  if ( this->buttonState[20] > 0 )
    LOBYTE(this->cmd.buttons) |= 1u;
  if ( this->toggled_run.on != (idUsercmdGenLocal::in_alwaysRun.internalVar->integerValue != 0) )
    LOBYTE(this->cmd.buttons) |= 2u;
  if ( this->toggled_zoom.on )
    LOBYTE(this->cmd.buttons) |= 4u;
  if ( this->buttonState[23] > 0 || this->buttonState[47] > 0 )
    LOBYTE(this->cmd.buttons) |= 8u;
  if ( this->buttonState[25] > 0 )
    LOBYTE(this->cmd.buttons) |= 0x20u;
  if ( this->buttonState[26] > 0 )
    LOBYTE(this->cmd.buttons) |= 0x40u;
  if ( this->buttonState[27] > 0 )
    LOBYTE(this->cmd.buttons) |= 0x80u;
  if ( this->buttonState[9] > 0 )
    this->cmd.buttons |= 0x100u;
  if ( idUsercmdGenLocal::in_freeLook.internalVar->integerValue != this->buttonState[24] > 0 )
    LOBYTE(this->cmd.buttons) |= 0x10u;
}

// FUNC: private: void __thiscall idUsercmdGenLocal::InitCurrent(void)
void __thiscall idUsercmdGenLocal::InitCurrent(idUsercmdGenLocal *this)
{
  unsigned __int8 flags; // al

  this->cmd.gameFrame = 0;
  this->cmd.gameTime = 0;
  this->cmd.realTime = 0;
  this->cmd.duplicateCount = 0;
  *(_DWORD *)&this->cmd.buttons = 0;
  *(_DWORD *)&this->cmd.upmove = 0;
  *(_DWORD *)&this->cmd.angles[1] = 0;
  *(_DWORD *)&this->cmd.mx = 0;
  *(_DWORD *)&this->cmd.impulse = 0;
  this->cmd.sequence = 0;
  flags = this->flags;
  this->cmd.impulse = this->impulse;
  this->cmd.flags = flags;
  this->cmd.buttons |= 2u;
  this->cmd.buttons |= idUsercmdGenLocal::in_freeLook.internalVar->integerValue != 0 ? 0x10 : 0;
}

// FUNC: private: void __thiscall idUsercmdGenLocal::MakeCurrent(void)
void __thiscall idUsercmdGenLocal::MakeCurrent(idUsercmdGenLocal *this)
{
  idVec3 *p_viewangles; // edi
  int v3; // eax
  bool v4; // cl
  int v5; // eax
  int v6; // eax
  idUsercmdGenLocal *v7; // ecx
  double v9; // st7
  unsigned __int8 v10; // c0
  unsigned __int8 v11; // c3
  __int16 *angles; // eax
  float *p_x; // ecx
  int v14; // edx
  __int16 continuousMouseX; // dx
  bool v16; // zf
  char stuffedImpulse; // cl
  int flags; // eax
  float v19; // [esp+Ch] [ebp-14h]
  float oldAngles; // [esp+14h] [ebp-Ch]

  p_viewangles = &this->viewangles;
  oldAngles = this->viewangles.x;
  if ( this->inhibitCommands )
  {
    this->mouseDx = 0;
    this->mouseDy = 0;
  }
  else
  {
    v3 = this->buttonState[2] > 0;
    if ( idUsercmdGenLocal::in_toggleCrouch.internalVar->integerValue )
    {
      if ( this->buttonState[2] > 0 )
      {
        if ( !this->toggled_crouch.held )
        {
          this->toggled_crouch.on ^= 1u;
          this->toggled_crouch.held = 1;
        }
      }
      else
      {
        this->toggled_crouch.held = 0;
      }
    }
    else
    {
      this->toggled_crouch.held = 0;
      this->toggled_crouch.on = v3;
    }
    v4 = idUsercmdGenLocal::in_toggleRun.internalVar->integerValue
      && (idAsyncNetwork::server.active || idAsyncNetwork::client.active);
    v5 = this->buttonState[21] > 0;
    if ( v4 )
    {
      if ( this->buttonState[21] > 0 )
      {
        if ( !this->toggled_run.held )
        {
          this->toggled_run.on ^= 1u;
          this->toggled_run.held = 1;
        }
      }
      else
      {
        this->toggled_run.held = 0;
      }
    }
    else
    {
      this->toggled_run.held = 0;
      this->toggled_run.on = v5;
    }
    v6 = this->buttonState[22] > 0;
    if ( idUsercmdGenLocal::in_toggleZoom.internalVar->integerValue )
    {
      if ( this->buttonState[22] > 0 )
      {
        if ( !this->toggled_zoom.held )
        {
          this->toggled_zoom.on ^= 1u;
          this->toggled_zoom.held = 1;
        }
      }
      else
      {
        this->toggled_zoom.held = 0;
      }
    }
    else
    {
      this->toggled_zoom.held = 0;
      this->toggled_zoom.on = v6;
    }
    idUsercmdGenLocal::AdjustAngles(this);
    idUsercmdGenLocal::CmdButtons(this);
    idUsercmdGenLocal::KeyMove(v7);
    idUsercmdGenLocal::MouseMove(this);
    idUsercmdGenLocal::JoystickMove(this);
    v9 = oldAngles;
    if ( v10 | v11 )
    {
      if ( v9 - p_viewangles->x > 90.0 )
        p_viewangles->x = oldAngles - 90.0;
    }
    else
    {
      p_viewangles->x = v9 + 90.0;
    }
  }
  angles = this->cmd.angles;
  p_x = &p_viewangles->x;
  v14 = 3;
  do
  {
    v19 = *p_x * 182.04445;
    *angles++ = (int)v19;
    ++p_x;
    --v14;
  }
  while ( v14 );
  continuousMouseX = this->continuousMouseX;
  this->cmd.my = this->continuousMouseY;
  v16 = this->stuffedImpulse == -1;
  this->cmd.mx = continuousMouseX;
  if ( !v16 )
  {
    stuffedImpulse = this->stuffedImpulse;
    this->cmd.flags ^= 1u;
    this->cmd.impulse = stuffedImpulse;
    this->stuffedImpulse = -1;
  }
  flags = this->cmd.flags;
  this->impulse = this->cmd.impulse;
  this->flags = flags;
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::InitForNewMap(void)
void __thiscall idUsercmdGenLocal::InitForNewMap(idUsercmdGenLocal *this)
{
  idUsercmdGenLocal_vtbl *v2; // edx

  this->flags = 0;
  this->impulse = 0;
  this->toggled_crouch.held = 0;
  this->toggled_crouch.on = 0;
  this->toggled_run.held = 0;
  this->toggled_run.on = 0;
  this->toggled_zoom.held = 0;
  this->toggled_zoom.on = 0;
  v2 = this->__vftable;
  this->toggled_run.on = idUsercmdGenLocal::in_alwaysRun.internalVar->integerValue != 0;
  v2->Clear(this);
  this->ClearAngles(this);
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::ClearAngles(void)
void __thiscall idUsercmdGenLocal::ClearAngles(idUsercmdGenLocal *this)
{
  this->viewangles.z = 0.0;
  this->viewangles.y = 0.0;
  this->viewangles.x = 0.0;
}

// FUNC: private: void __thiscall idUsercmdGenLocal::Joystick(void)
void __thiscall idUsercmdGenLocal::Joystick(idUsercmdGenLocal *this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  const idCmdArgs *v5; // [esp+0h] [ebp-10h]
  int value; // [esp+8h] [ebp-8h] BYREF
  int action; // [esp+Ch] [ebp-4h] BYREF

  v2 = Sys_PollJoystickInputEvents();
  v3 = v2;
  if ( v2 )
  {
    v4 = 0;
    if ( v2 > 0 )
    {
      do
      {
        if ( Sys_ReturnJoystickInputEvent(v4, &action, &value) )
        {
          if ( (unsigned int)action > 0xF )
          {
            switch ( action )
            {
              case 16:
                if ( idUsercmdGenLocal::in_joystickLeftStickMove.internalVar->integerValue )
                  this->joystickAxis[2] = value;
                else
                  this->joystickAxis[0] = value;
                break;
              case 17:
                if ( idUsercmdGenLocal::in_joystickLeftStickMove.internalVar->integerValue )
                  this->joystickAxis[3] = value;
                else
                  this->joystickAxis[1] = value;
                break;
              case 18:
                if ( idUsercmdGenLocal::in_joystickLeftStickMove.internalVar->integerValue )
                  this->joystickAxis[0] = value;
                else
                  this->joystickAxis[2] = value;
                break;
              case 19:
                if ( idUsercmdGenLocal::in_joystickLeftStickMove.internalVar->integerValue )
                  this->joystickAxis[1] = value;
                else
                  this->joystickAxis[3] = value;
                break;
              default:
                break;
            }
          }
          else
          {
            idUsercmdGenLocal::Key(this, action + 197, value != 0);
          }
        }
        ++v4;
      }
      while ( v4 < v3 );
    }
  }
  SpawnStub(v5);
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::UsercmdInterrupt(void)
void __thiscall idUsercmdGenLocal::UsercmdInterrupt(idUsercmdGenLocal *this)
{
  idUsercmdGenLocal *v2; // ecx

  if ( this->initialized )
  {
    idUsercmdGenLocal::InitCurrent(this);
    idUsercmdGenLocal::Mouse(v2);
    idUsercmdGenLocal::Keyboard(this);
    idUsercmdGenLocal::Joystick(this);
    idUsercmdGenLocal::MakeCurrent(this);
    this->cmd.sequence = com_ticNumber + 1;
    qmemcpy(
      &this->buffered[((_BYTE)com_ticNumber + 1) & 0x3F],
      &this->cmd,
      sizeof(this->buffered[((_BYTE)com_ticNumber + 1) & 0x3F]));
  }
}

// FUNC: public: virtual class usercmd_t __thiscall idUsercmdGenLocal::GetDirectUsercmd(void)
usercmd_t *__thiscall idUsercmdGenLocal::GetDirectUsercmd(idUsercmdGenLocal *this, usercmd_t *result)
{
  idUsercmdGenLocal *v3; // ecx
  usercmd_t *v4; // eax

  idUsercmdGenLocal::InitCurrent(this);
  idUsercmdGenLocal::Mouse(v3);
  idUsercmdGenLocal::Keyboard(this);
  idUsercmdGenLocal::Joystick(this);
  idUsercmdGenLocal::MakeCurrent(this);
  v4 = result;
  this->cmd.duplicateCount = 0;
  qmemcpy(result, &this->cmd, sizeof(usercmd_t));
  return v4;
}

// FUNC: public: __thiscall idUsercmdGenLocal::idUsercmdGenLocal(void)
void __thiscall idUsercmdGenLocal::idUsercmdGenLocal(idUsercmdGenLocal *this)
{
  this->__vftable = (idUsercmdGenLocal_vtbl *)&idUsercmdGenLocal::`vftable';
  this->toggled_crouch.held = 0;
  this->toggled_crouch.on = 0;
  this->toggled_run.held = 0;
  this->toggled_run.on = 0;
  this->toggled_zoom.held = 0;
  this->toggled_zoom.on = 0;
  this->lastCommandTime = 0;
  this->initialized = 0;
  this->flags = 0;
  this->impulse = 0;
  this->toggled_crouch.held = 0;
  this->toggled_crouch.on = 0;
  this->toggled_run.held = 0;
  this->toggled_run.on = 0;
  this->toggled_zoom.held = 0;
  this->toggled_zoom.on = 0;
  this->toggled_run.on = idUsercmdGenLocal::in_alwaysRun.internalVar->integerValue != 0;
  this->viewangles.z = 0.0;
  this->viewangles.y = 0.0;
  this->viewangles.x = 0.0;
  memset(this->buttonState, 0, sizeof(this->buttonState));
  memset(this->keyState, 0, 0xFCu);
  *(_WORD *)&this->keyState[252] = 0;
  this->inhibitCommands = 0;
  this->mouseDy = 0;
  this->mouseDx = 0;
  this->mouseButton = 0;
  this->mouseDown = 0;
  this->slowJoystick = 100;
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::SetSlowJoystick(int)
void __thiscall idUsercmdGenLocal::SetSlowJoystick(idUsercmdGenLocal *this, int slow)
{
  this->slowJoystick = slow;
}

// FUNC: public: virtual void __thiscall idUsercmdGenLocal::StuffImpulse(int)
void __thiscall idUsercmdGenLocal::StuffImpulse(idUsercmdGenLocal *this, int impulse)
{
  this->stuffedImpulse = impulse;
}
