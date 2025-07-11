
// FUNC: public: virtual class idWinVar * __thiscall idBindWindow::GetWinVarByName(char const *,bool,struct drawWin_t * *)
idWinStr *__thiscall idBindWindow::GetWinVarByName(
        idBindWindow *this,
        const char *_name,
        bool fixup,
        drawWin_t **owner)
{
  if ( idStr::Icmp(_name, "bind") )
    return (idWinStr *)idWindow::GetWinVarByName(this, _name, fixup, owner);
  else
    return &this->bindName;
}

// FUNC: public: virtual void __thiscall idBindWindow::Activate(bool,class idStr &)
void __thiscall idBindWindow::Activate(idBindWindow *this, bool activate, idStr *act)
{
  idWindow::Activate(this, activate, act);
  this->bindName.Update(&this->bindName);
}

// FUNC: public: virtual __thiscall idBindWindow::~idBindWindow(void)
void __thiscall idBindWindow::~idBindWindow(idBindWindow *this)
{
  this->__vftable = (idBindWindow_vtbl *)&idBindWindow::`vftable';
  idWinStr::~idWinStr(&this->bindName);
  idWindow::~idWindow(this);
}

// FUNC: public: virtual char const * __thiscall idBindWindow::HandleEvent(struct sysEvent_s const *,bool *)
char *__thiscall idBindWindow::HandleEvent(idBindWindow *this, const sysEvent_s *event, bool *updateVisuals)
{
  int evValue; // edi
  const char *Name; // eax
  const char *v6; // eax
  idUserInterfaceLocal *gui; // ecx

  if ( event->evType != SE_KEY || !event->evValue2 )
    return (char *)&entityFilter;
  evValue = event->evValue;
  if ( this->waitingOnKey && evValue )
  {
    this->waitingOnKey = 0;
    if ( evValue == 27 || evValue == 203 )
    {
      Name = idWinVar::GetName(&this->bindName);
      idStr::snPrintf(ret, 256, "clearbind \"%s\"", Name);
    }
    else
    {
      v6 = idWinVar::GetName(&this->bindName);
      idStr::snPrintf(ret, 256, "bind %i \"%s\"", evValue, v6);
    }
    this->RunScript(this, 2);
    idWindow::AddCommand(this, ret);
    return this->cmd.data;
  }
  else if ( evValue == 187 || evValue == 199 )
  {
    gui = this->gui;
    this->waitingOnKey = 1;
    gui->bindHandler = this;
    this->RunScript(this, 2);
    return this->cmd.data;
  }
  else
  {
    return (char *)&entityFilter;
  }
}

// FUNC: public: virtual void __thiscall idBindWindow::PostParse(void)
void __thiscall idBindWindow::PostParse(idBindWindow *this)
{
  const idCmdArgs *v2; // [esp+0h] [ebp-8h]

  SpawnStub(v2);
  idWinVar::SetGuiInfo(&this->bindName, &this->gui->state, this->bindName.data.data);
  this->bindName.Update(&this->bindName);
  BYTE1(this->flags) |= 0x48u;
}

// FUNC: public: virtual void __thiscall idBindWindow::Draw(int,float,float)
void __thiscall idBindWindow::Draw(idBindWindow *this, int time, float x, float y)
{
  float v5; // edi
  float v6; // ebp
  float z; // ebx
  bool v8; // zf
  char *v9; // eax
  idVec4 v10; // [esp-2Ch] [ebp-8Ch]
  float v11; // [esp+8h] [ebp-58h]
  float v12; // [esp+Ch] [ebp-54h]
  idUserInterfaceLocal *textScale; // [esp+20h] [ebp-40h]
  float color_12; // [esp+30h] [ebp-30h]
  idStr str; // [esp+34h] [ebp-2Ch] BYREF
  int v16; // [esp+5Ch] [ebp-4h]

  v5 = this->foreColor.data.x;
  v6 = this->foreColor.data.y;
  z = this->foreColor.data.z;
  color_12 = this->foreColor.data.w;
  str.len = 0;
  str.alloced = 20;
  str.data = str.baseBuffer;
  str.baseBuffer[0] = 0;
  v8 = !this->waitingOnKey;
  v16 = 0;
  if ( v8 )
  {
    if ( idWinStr::Length(&this->bindName) )
      v9 = (char *)this->bindName.c_str(&this->bindName);
    else
      v9 = (char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                     common.type,
                     "#str_107001",
                     -1);
  }
  else
  {
    v9 = (char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                   common.type,
                   "#str_107000",
                   -1);
  }
  idStr::operator=(&str, v9);
  if ( this->waitingOnKey
    || this->hover
    && !this->noEvents.data
    && (textScale = this->gui,
        v12 = ((double (*)(void))textScale->CursorY)(),
        v11 = textScale->CursorX(textScale),
        idWindow::Contains(this, v11, v12)) )
  {
    v5 = this->hoverColor.data.x;
    v6 = this->hoverColor.data.y;
    z = this->hoverColor.data.z;
    color_12 = this->hoverColor.data.w;
  }
  else
  {
    this->hover = 0;
  }
  *(_QWORD *)&v10.x = __PAIR64__(LODWORD(v6), LODWORD(v5));
  *(_QWORD *)&v10.z = __PAIR64__(LODWORD(color_12), LODWORD(z));
  idDeviceContext::DrawTextA(
    this->dc,
    str.data,
    this->textScale.data,
    this->textAlign,
    this->textStyle,
    v10,
    this->textRect,
    0,
    -1,
    0,
    0,
    0,
    0,
    0);
  v16 = -1;
  idStr::FreeData(&str);
}

// FUNC: private: void __thiscall idBindWindow::CommonInit(void)
void __thiscall idBindWindow::CommonInit(idBindWindow *this)
{
  int v2; // eax
  char v3; // cl
  idStr other; // [esp+8h] [ebp-2Ch] BYREF
  int v5; // [esp+30h] [ebp-4h]

  other.data = other.baseBuffer;
  other.alloced = 20;
  other.baseBuffer[0] = 0;
  v2 = 0;
  do
  {
    v3 = *(&entityFilter + v2);
    other.baseBuffer[v2++] = v3;
  }
  while ( v3 );
  other.len = 0;
  v5 = 0;
  idWinStr::operator=(&this->bindName, &other);
  v5 = -1;
  idStr::FreeData(&other);
  this->waitingOnKey = 0;
}

// FUNC: public: __thiscall idBindWindow::idBindWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idBindWindow::idBindWindow(idBindWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idWindow::idWindow(this, d, g);
  this->__vftable = (idBindWindow_vtbl *)&idBindWindow::`vftable';
  this->bindName.guiDict = 0;
  this->bindName.name = 0;
  this->bindName.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->bindName.eval = 1;
  this->bindName.data.len = 0;
  this->bindName.data.alloced = 20;
  this->bindName.data.data = this->bindName.data.baseBuffer;
  this->bindName.data.baseBuffer[0] = 0;
  this->dc = d;
  this->gui = g;
  idBindWindow::CommonInit(this);
}
