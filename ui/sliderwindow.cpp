
// FUNC: public: virtual class idWinVar * __thiscall idSliderWindow::GetWinVarByName(char const *,bool,struct drawWin_t * *)
idWinStr *__thiscall idSliderWindow::GetWinVarByName(
        idSliderWindow *this,
        const char *_name,
        bool fixup,
        drawWin_t **owner)
{
  if ( !idStr::Icmp(_name, "value") )
    return (idWinStr *)&this->value;
  if ( !idStr::Icmp(_name, "cvar") )
    return &this->cvarStr;
  if ( !idStr::Icmp(_name, "liveUpdate") )
    return (idWinStr *)&this->liveUpdate;
  if ( idStr::Icmp(_name, "cvarGroup") )
    return (idWinStr *)idWindow::GetWinVarByName(this, _name, fixup, owner);
  return &this->cvarGroup;
}

// FUNC: public: virtual void __thiscall idSliderWindow::SetBuddy(class idWindow *)
void __thiscall idSliderWindow::SetBuddy(idSliderWindow *this, idWindow *buddy)
{
  this->buddyWin = buddy;
}

// FUNC: public: void __thiscall idSliderWindow::SetRange(float,float,float)
void __thiscall idSliderWindow::SetRange(idSliderWindow *this, float _low, float _high, float _step)
{
  this->low = _low;
  this->high = _high;
  this->stepSize = _step;
}

// FUNC: public: virtual void __thiscall idSliderWindow::DrawBackground(class idRectangle const &)
void __thiscall idSliderWindow::DrawBackground(idSliderWindow *this, const idRectangle *_drawRect)
{
  bool v2; // zf
  float h; // eax
  idRectangle r; // [esp+0h] [ebp-10h] BYREF

  if ( (this->cvar || this->buddyWin) && this->high - this->low > 0.0 )
  {
    v2 = !this->scrollbar;
    r.x = _drawRect->x;
    r.y = _drawRect->y;
    h = _drawRect->h;
    r.w = _drawRect->w;
    r.h = h;
    if ( v2 )
    {
      if ( this->vertical )
      {
        r.y = this->thumbHeight * 0.5 + r.y;
        r.h = r.h - this->thumbHeight;
        idWindow::DrawBackground(this, &r);
        return;
      }
      r.x = this->thumbWidth * 0.5 + r.x;
      r.w = r.w - this->thumbWidth;
    }
    idWindow::DrawBackground(this, &r);
  }
}

// FUNC: private: void __thiscall idSliderWindow::CommonInit(void)
void __thiscall idSliderWindow::CommonInit(idSliderWindow *this)
{
  bool v2; // [esp+Bh] [ebp-5h] BYREF
  float other; // [esp+Ch] [ebp-4h] BYREF

  other = 0.0;
  idWinFloat::operator=(&this->value, &other);
  this->low = 0.0;
  this->high = 100.0;
  this->stepSize = 1.0;
  this->thumbMat = declManager->FindMaterial(declManager, "_default", 1);
  this->buddyWin = 0;
  this->cvar = 0;
  this->cvar_init = 0;
  v2 = 1;
  idWinBool::operator=(&this->liveUpdate, &v2);
  this->vertical = 0;
  this->scrollbar = 0;
  this->verticalFlip = 0;
}

// FUNC: public: __thiscall idSliderWindow::idSliderWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idSliderWindow::idSliderWindow(idSliderWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idWindow::idWindow(this, d, g);
  this->__vftable = (idSliderWindow_vtbl *)&idSliderWindow::`vftable';
  this->value.guiDict = 0;
  this->value.name = 0;
  this->value.eval = 1;
  this->value.__vftable = (idWinFloat_vtbl *)&idWinFloat::`vftable';
  this->thumbRect.h = 0.0;
  this->thumbRect.w = 0.0;
  this->thumbRect.y = 0.0;
  this->thumbRect.x = 0.0;
  this->thumbShader.len = 0;
  this->thumbShader.alloced = 20;
  this->thumbShader.data = this->thumbShader.baseBuffer;
  this->thumbShader.baseBuffer[0] = 0;
  this->cvarStr.guiDict = 0;
  this->cvarStr.name = 0;
  this->cvarStr.eval = 1;
  this->cvarStr.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->cvarStr.data.len = 0;
  this->cvarStr.data.alloced = 20;
  this->cvarStr.data.data = this->cvarStr.data.baseBuffer;
  this->cvarStr.data.baseBuffer[0] = 0;
  this->liveUpdate.guiDict = 0;
  this->liveUpdate.name = 0;
  this->liveUpdate.eval = 1;
  this->liveUpdate.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->cvarGroup.guiDict = 0;
  this->cvarGroup.name = 0;
  this->cvarGroup.eval = 1;
  this->cvarGroup.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->cvarGroup.data.len = 0;
  this->cvarGroup.data.alloced = 20;
  this->cvarGroup.data.data = this->cvarGroup.data.baseBuffer;
  this->cvarGroup.data.baseBuffer[0] = 0;
  this->dc = d;
  this->gui = g;
  idSliderWindow::CommonInit(this);
}

// FUNC: public: virtual __thiscall idSliderWindow::~idSliderWindow(void)
void __thiscall idSliderWindow::~idSliderWindow(idSliderWindow *this)
{
  char *name; // [esp-4h] [ebp-18h]
  char *v3; // [esp-4h] [ebp-18h]

  this->__vftable = (idSliderWindow_vtbl *)&idSliderWindow::`vftable';
  idWinStr::~idWinStr(&this->cvarGroup);
  name = this->liveUpdate.name;
  this->liveUpdate.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(name);
  this->liveUpdate.name = 0;
  idWinStr::~idWinStr(&this->cvarStr);
  idStr::FreeData(&this->thumbShader);
  v3 = this->value.name;
  this->value.__vftable = (idWinFloat_vtbl *)&idWinVar::`vftable';
  Memory::Free(v3);
  this->value.name = 0;
  idWindow::~idWindow(this);
}

// FUNC: private: virtual bool __thiscall idSliderWindow::ParseInternalVar(char const *,class idParser *)
bool __thiscall idSliderWindow::ParseInternalVar(idSliderWindow *this, const char *_name, idParser *src)
{
  if ( idStr::Icmp(_name, "stepsize") && idStr::Icmp(_name, "step") )
  {
    if ( idStr::Icmp(_name, "low") )
    {
      if ( idStr::Icmp(_name, "high") )
      {
        if ( idStr::Icmp(_name, "vertical") )
        {
          if ( idStr::Icmp(_name, "verticalflip") )
          {
            if ( idStr::Icmp(_name, "scrollbar") )
            {
              if ( idStr::Icmp(_name, "thumbshader") )
              {
                return idWindow::ParseInternalVar(this, _name, src);
              }
              else
              {
                idWindow::ParseString(this, src, &this->thumbShader);
                declManager->FindMaterial(declManager, this->thumbShader.data, 1);
                return 1;
              }
            }
            else
            {
              this->scrollbar = idParser::ParseBool(src);
              return 1;
            }
          }
          else
          {
            this->verticalFlip = idParser::ParseBool(src);
            return 1;
          }
        }
        else
        {
          this->vertical = idParser::ParseBool(src);
          return 1;
        }
      }
      else
      {
        this->high = idParser::ParseFloat(src);
        return 1;
      }
    }
    else
    {
      this->low = idParser::ParseFloat(src);
      return 1;
    }
  }
  else
  {
    this->stepSize = idParser::ParseFloat(src);
    return 1;
  }
}

// FUNC: public: void __thiscall idSliderWindow::InitWithDefaults(char const *,class idRectangle const &,class idVec4 const &,class idVec4 const &,char const *,char const *,bool,bool)
void __thiscall idSliderWindow::InitWithDefaults(
        idSliderWindow *this,
        const char *_name,
        const idRectangle *_rect,
        const idVec4 *_foreColor,
        const idVec4 *_matColor,
        const char *_background,
        const char *thumbShader,
        bool _vertical,
        bool _scrollbar)
{
  const idMaterial *v10; // eax
  int ImageWidth; // eax
  idMaterial *thumbMat; // ecx
  const idMaterial *v13; // eax

  idWindow::SetInitialState(this, _name);
  idWinRectangle::operator=(&this->rect, _rect);
  idWinVec4::operator=(&this->foreColor, _foreColor);
  idWinVec4::operator=(&this->matColor, _matColor);
  v10 = declManager->FindMaterial(declManager, thumbShader, 1);
  this->thumbMat = v10;
  v10->sort = -2.0;
  ImageWidth = idMaterial::GetImageWidth((idMaterial *)this->thumbMat);
  thumbMat = (idMaterial *)this->thumbMat;
  this->thumbWidth = (float)ImageWidth;
  this->thumbHeight = (float)idMaterial::GetImageHeight(thumbMat);
  v13 = declManager->FindMaterial(declManager, _background, 1);
  this->background = v13;
  v13->sort = -2.0;
  BYTE1(this->flags) |= 0x40u;
  this->vertical = _vertical;
  this->scrollbar = _scrollbar;
}

// FUNC: public: void __thiscall idSliderWindow::SetValue(float)
void __thiscall idSliderWindow::SetValue(idSliderWindow *this, float _value)
{
  idWinFloat::operator=(&this->value, &_value);
}

// FUNC: private: void __thiscall idSliderWindow::InitCvar(void)
void __thiscall idSliderWindow::InitCvar(idSliderWindow *this)
{
  char *data; // eax
  idCVar *v3; // eax
  char *v4; // ebx
  int v5; // ebp
  char *v6; // edi
  const char *v7; // eax

  data = this->cvarStr.data.data;
  if ( *data )
  {
    v3 = cvarSystem->Find(cvarSystem, data);
    this->cvar = v3;
    if ( !v3 )
    {
      v4 = this->gui->source.data;
      v5 = *(_DWORD *)common.type;
      v6 = this->name.data;
      v7 = this->cvarStr.c_str(&this->cvarStr);
      (*(void (**)(netadrtype_t, const char *, ...))(v5 + 136))(
        common.type,
        "idSliderWindow::InitCvar: gui '%s' window '%s' references undefined cvar '%s'",
        v4,
        v6,
        v7);
      this->cvar_init = 1;
    }
  }
  else
  {
    if ( !this->buddyWin )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "idSliderWindow::InitCvar: gui '%s' window '%s' has an empty cvar string",
        this->gui->source.data,
        this->name.data);
    this->cvar = 0;
    this->cvar_init = 1;
  }
}

// FUNC: private: void __thiscall idSliderWindow::UpdateCvar(bool,bool)
void __userpurge idSliderWindow::UpdateCvar(
        idSliderWindow *this@<ecx>,
        int a2@<edi>,
        bool read,
        float force,
        float other)
{
  idCVar *cvar; // eax
  idUserInterfaceLocal *gui; // ecx
  idUserInterfaceLocal_vtbl *v8; // edx
  char *data; // edi
  idDict *v10; // eax
  const idKeyValue *Key; // eax
  const char *v12; // eax
  long double v13; // st7
  idUserInterfaceLocal_vtbl *v14; // edx
  char *v15; // edi
  idDict *v16; // eax
  const idKeyValue *v17; // eax
  const char *v18; // eax

  if ( !this->buddyWin )
  {
    cvar = this->cvar;
    if ( cvar )
    {
      if ( LOBYTE(force) || this->liveUpdate.data )
      {
        force = cvar->internalVar->floatValue;
        idWinFloat::operator=(&this->value, &force);
        gui = this->gui;
        v8 = gui->__vftable;
        data = this->cvarStr.data.data;
        force = this->value.data;
        v10 = (idDict *)v8->State(gui);
        Key = idDict::FindKey(v10, data);
        v12 = Key ? Key->value->data : "0";
        v13 = atof(v12);
        if ( force != v13 )
        {
          v14 = this->gui->idWindow::__vftable;
          if ( read )
          {
            ((void (__stdcall *)(char *, _DWORD))v14->SetStateFloat)(this->cvarStr.data.data, LODWORD(this->value.data));
          }
          else
          {
            v15 = this->cvarStr.data.data;
            v16 = (idDict *)((int (__stdcall *)(int))v14->State)(a2);
            v17 = idDict::FindKey(v16, v15);
            if ( v17 )
              v18 = v17->value->data;
            else
              v18 = "0";
            other = atof(v18);
            idWinFloat::operator=(&this->value, &other);
            ((void (__thiscall *)(idCVar *, _DWORD))this->cvar->internalVar->InternalSetFloat)(
              this->cvar->internalVar,
              LODWORD(this->value.data));
          }
        }
      }
    }
  }
}

// FUNC: public: virtual char const * __thiscall idSliderWindow::HandleEvent(struct sysEvent_s const *,bool *)
const char *__thiscall idSliderWindow::HandleEvent(idSliderWindow *this, float event, bool *updateVisuals)
{
  int v4; // edi

  if ( *(_DWORD *)LODWORD(event) != 1 || !*(_DWORD *)(LODWORD(event) + 8) )
    return &entityFilter;
  v4 = *(_DWORD *)(LODWORD(event) + 4);
  switch ( v4 )
  {
    case 187:
      idWindow::SetCapture(this, this);
      ((void (__thiscall *)(idSliderWindow *, _DWORD, _DWORD))this->RouteMouseCoords)(this, 0, 0);
      return &entityFilter;
    case 136:
    case 170:
LABEL_9:
      event = this->stepSize + this->value.data;
      idWinFloat::operator=(&this->value, &event);
      break;
    case 188:
      if ( ((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorY)(this->gui) <= this->thumbRect.y )
      {
LABEL_13:
        if ( ((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorY)(this->gui) < this->thumbRect.y )
        {
LABEL_14:
          event = this->value.data - this->stepSize;
          idWinFloat::operator=(&this->value, &event);
          goto LABEL_15;
        }
        goto LABEL_15;
      }
      goto LABEL_9;
  }
  if ( v4 == 135 || v4 == 168 )
    goto LABEL_14;
  if ( v4 == 188 )
    goto LABEL_13;
LABEL_15:
  if ( this->buddyWin )
  {
    this->buddyWin->HandleBuddyUpdate(this->buddyWin, this);
    return &entityFilter;
  }
  ((void (__thiscall *)(idUserInterfaceLocal *, char *, _DWORD))this->gui->SetStateFloat)(
    this->gui,
    this->cvarStr.data.data,
    LODWORD(this->value.data));
  idSliderWindow::UpdateCvar(this, 0, 0);
  return &entityFilter;
}

// FUNC: public: virtual void __thiscall idSliderWindow::PostParse(void)
void __thiscall idSliderWindow::PostParse(idSliderWindow *this)
{
  const idMaterial *v2; // eax
  int ImageWidth; // eax
  idMaterial *thumbMat; // ecx
  int ImageHeight; // eax
  const idCmdArgs *v6; // [esp+4h] [ebp-8h]
  float other; // [esp+8h] [ebp-4h] BYREF

  SpawnStub(v6);
  other = 0.0;
  idWinFloat::operator=(&this->value, &other);
  v2 = declManager->FindMaterial(declManager, this->thumbShader.data, 1);
  this->thumbMat = v2;
  v2->sort = -2.0;
  ImageWidth = idMaterial::GetImageWidth((idMaterial *)this->thumbMat);
  thumbMat = (idMaterial *)this->thumbMat;
  LODWORD(other) = ImageWidth;
  this->thumbWidth = (float)ImageWidth;
  ImageHeight = idMaterial::GetImageHeight(thumbMat);
  BYTE1(this->flags) |= 0x48u;
  LODWORD(other) = ImageHeight;
  this->thumbHeight = (float)ImageHeight;
  idSliderWindow::InitCvar(this);
}

// FUNC: public: virtual void __thiscall idSliderWindow::Draw(int,float,float)
void __thiscall idSliderWindow::Draw(idSliderWindow *this, int time, float x, float y)
{
  bool v5; // zf
  idVec4 *p_data; // eax
  float v7; // edx
  float z; // ecx
  float v9; // edx
  int ImageWidth; // eax
  idMaterial *thumbMat; // ecx
  double v12; // st7
  double v13; // st7
  double v14; // st6
  double v15; // st6
  float thumbHeight; // eax
  idUserInterfaceLocal *gui; // edi
  float v18; // eax
  float v19; // edx
  float v20; // eax
  float v21; // eax
  float v22; // edx
  float v23; // eax
  float v24; // [esp+0h] [ebp-34h]
  float v25; // [esp+4h] [ebp-30h]
  float w; // [esp+8h] [ebp-2Ch]
  float h; // [esp+Ch] [ebp-28h]
  float v28; // [esp+10h] [ebp-24h]
  float v29; // [esp+14h] [ebp-20h]
  idVec4 color; // [esp+24h] [ebp-10h] BYREF

  v5 = this->cvar == 0;
  p_data = &this->foreColor.data;
  v7 = this->foreColor.data.y;
  color.x = this->foreColor.data.x;
  z = this->foreColor.data.z;
  color.y = v7;
  v9 = p_data->w;
  color.z = z;
  color.w = v9;
  if ( !v5 || this->buddyWin )
  {
    if ( this->thumbWidth == 0.0 || this->thumbHeight == 0.0 )
    {
      ImageWidth = idMaterial::GetImageWidth((idMaterial *)this->thumbMat);
      thumbMat = (idMaterial *)this->thumbMat;
      this->thumbWidth = (float)ImageWidth;
      this->thumbHeight = (float)idMaterial::GetImageHeight(thumbMat);
    }
    idSliderWindow::UpdateCvar(this, 1, 0);
    if ( this->value.data <= (double)this->high )
    {
      if ( this->value.data < (double)this->low )
        idWinFloat::operator=(&this->value, &this->low);
    }
    else
    {
      idWinFloat::operator=(&this->value, &this->high);
    }
    v12 = this->high - this->low;
    if ( v12 > 0.0 )
    {
      v13 = (this->value.data - this->low) / v12;
      if ( this->vertical )
      {
        if ( this->verticalFlip )
          v13 = 1.0 - v13;
        v14 = this->drawRect.h - this->thumbHeight;
        this->thumbRect.x = this->drawRect.x;
        this->thumbRect.y = v14 * v13 + this->drawRect.y;
      }
      else
      {
        v15 = this->drawRect.w - this->thumbWidth;
        this->thumbRect.y = this->drawRect.y;
        this->thumbRect.x = v15 * v13 + this->drawRect.x;
      }
      v5 = !this->hover;
      thumbHeight = this->thumbHeight;
      this->thumbRect.w = this->thumbWidth;
      this->thumbRect.h = thumbHeight;
      if ( v5
        || this->noEvents.data
        || (gui = this->gui,
            v29 = ((double (*)(void))gui->CursorY)(),
            v28 = gui->CursorX(gui),
            !idWindow::Contains(this, v28, v29)) )
      {
        this->hover = 0;
      }
      else
      {
        v18 = this->hoverColor.data.y;
        color.x = this->hoverColor.data.x;
        v19 = this->hoverColor.data.z;
        color.y = v18;
        v20 = this->hoverColor.data.w;
        color.z = v19;
        color.w = v20;
      }
      if ( (this->flags & 0x40) != 0 )
      {
        v21 = this->hoverColor.data.y;
        color.x = this->hoverColor.data.x;
        v22 = this->hoverColor.data.z;
        color.y = v21;
        v23 = this->hoverColor.data.w;
        color.z = v22;
        color.w = v23;
        this->hover = 1;
      }
      idDeviceContext::DrawMaterial(
        this->dc,
        this->thumbRect.x,
        this->thumbRect.y,
        this->thumbRect.w,
        this->thumbRect.h,
        this->thumbMat,
        &color,
        1.0,
        1.0);
      if ( (this->flags & 0x20) != 0 )
      {
        h = this->thumbRect.h - 2.0;
        w = this->thumbRect.w - 2.0;
        v25 = this->thumbRect.y + 1.0;
        v24 = this->thumbRect.x + 1.0;
        idDeviceContext::DrawRect(this->dc, v24, v25, w, h, 1.0, &color);
      }
    }
  }
}

// FUNC: public: virtual char const * __thiscall idSliderWindow::RouteMouseCoords(float,float)
const char *__userpurge idSliderWindow::RouteMouseCoords@<eax>(
        idSliderWindow *this@<ecx>,
        int a2@<edi>,
        float xd,
        float yd)
{
  bool v5; // zf
  double actualX; // st7
  double v7; // st6
  float y; // edx
  double v9; // st7
  double v10; // st6
  idUserInterfaceLocal *gui; // ecx
  float h; // edx
  float actualY; // eax
  idUserInterfaceLocal_vtbl *v14; // edx
  double v15; // st7
  float *p_high; // ecx
  idWinFloat *p_value; // ecx
  float *p_low; // [esp-4h] [ebp-1Ch]
  float v20; // [esp+0h] [ebp-18h]
  float v21; // [esp+4h] [ebp-14h] BYREF
  idRectangle r; // [esp+8h] [ebp-10h]

  if ( (this->flags & 0x40) == 0 )
    return &entityFilter;
  v5 = !this->vertical;
  actualX = this->actualX;
  v7 = this->thumbWidth * 0.5;
  y = this->drawRect.y;
  r.x = this->drawRect.x;
  v9 = actualX + v7;
  r.w = this->drawRect.w;
  v10 = r.w - this->thumbWidth;
  gui = this->gui;
  r.y = y;
  h = this->drawRect.h;
  actualY = this->actualY;
  r.w = v10;
  r.h = h;
  v14 = gui->__vftable;
  r.y = actualY;
  if ( v5 )
  {
    r.x = this->thumbWidth * 0.5 + v9;
    r.w = r.w - this->thumbWidth;
    if ( ((double (*)(void))v14->CursorX)() >= r.x
      && r.w + r.x >= ((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorX)(this->gui) )
    {
      p_low = &v21;
      v21 = (this->high - this->low)
          * ((((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorX)(this->gui) - r.x)
           / r.w)
          + this->low;
      goto LABEL_22;
    }
    if ( ((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorX)(this->gui) < r.x )
    {
      p_low = &this->low;
      goto LABEL_22;
    }
    p_high = &this->high;
LABEL_21:
    p_low = p_high;
    goto LABEL_22;
  }
  r.y = this->thumbHeight * 0.5 + r.y;
  r.h = r.h - this->thumbHeight;
  if ( ((double (*)(void))v14->CursorY)() >= r.y
    && r.h + r.y >= ((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorY)(this->gui) )
  {
    v15 = (((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorY)(this->gui) - r.y) / r.h;
    if ( this->verticalFlip )
      v15 = 1.0 - v15;
    p_low = &v21;
    v21 = (this->high - this->low) * v15 + this->low;
    goto LABEL_22;
  }
  if ( ((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorY)(this->gui) < r.y )
  {
    if ( this->verticalFlip )
    {
      p_low = &this->high;
LABEL_22:
      idWinFloat::operator=(&this->value, p_low);
      goto LABEL_23;
    }
    p_high = &this->low;
    goto LABEL_21;
  }
  p_value = &this->value;
  if ( this->verticalFlip )
    idWinFloat::operator=(p_value, &this->low);
  else
    idWinFloat::operator=(p_value, &this->high);
LABEL_23:
  if ( this->buddyWin )
    this->buddyWin->HandleBuddyUpdate(this->buddyWin, this);
  else
    ((void (__thiscall *)(idUserInterfaceLocal *, char *, _DWORD))this->gui->SetStateFloat)(
      this->gui,
      this->cvarStr.data.data,
      LODWORD(this->value.data));
  idSliderWindow::UpdateCvar(this, a2, 0, 0.0, v20);
  return &entityFilter;
}

// FUNC: public: virtual void __thiscall idSliderWindow::Activate(bool,class idStr &)
void __thiscall idSliderWindow::Activate(idSliderWindow *this, bool activate, idStr *act)
{
  idWindow::Activate(this, activate, act);
  if ( activate )
    idSliderWindow::UpdateCvar(this, 1, 1);
}

// FUNC: public: virtual void __thiscall idSliderWindow::RunNamedEvent(char const *)
void __thiscall idSliderWindow::RunNamedEvent(idSliderWindow *this, char *eventName)
{
  idStr *v3; // esi
  unsigned int v4; // ebp
  int v5; // eax
  idStr *v6; // esi
  unsigned int len; // ebp
  int v8; // eax
  idStr group; // [esp+10h] [ebp-6Ch] BYREF
  idStr event; // [esp+30h] [ebp-4Ch] BYREF
  idStr result; // [esp+50h] [ebp-2Ch] BYREF
  int v12; // [esp+78h] [ebp-4h]

  event.len = 0;
  event.alloced = 20;
  event.data = event.baseBuffer;
  event.baseBuffer[0] = 0;
  v12 = 1;
  group.len = 0;
  group.alloced = 20;
  group.data = group.baseBuffer;
  group.baseBuffer[0] = 0;
  if ( idStr::Cmpn(eventName, "cvar read ", 10) )
  {
    if ( !idStr::Cmpn(eventName, "cvar write ", 11) )
    {
      idStr::operator=(&event, eventName);
      v6 = idStr::Mid(&event, &result, 11, event.len - 11);
      len = v6->len;
      v8 = v6->len + 1;
      LOBYTE(v12) = 3;
      if ( v8 > group.alloced )
        idStr::ReAllocate(&group, v8, 0);
      qmemcpy(group.data, v6->data, len);
      group.data[len] = 0;
      group.len = len;
      LOBYTE(v12) = 1;
      idStr::FreeData(&result);
      if ( !idStr::Cmp(group.data, this->cvarGroup.data.data) )
        idSliderWindow::UpdateCvar(this, 0, 1);
    }
  }
  else
  {
    idStr::operator=(&event, eventName);
    v3 = idStr::Mid(&event, &result, 10, event.len - 10);
    v4 = v3->len;
    v5 = v3->len + 1;
    LOBYTE(v12) = 2;
    if ( v5 > group.alloced )
      idStr::ReAllocate(&group, v5, 0);
    qmemcpy(group.data, v3->data, v4);
    group.data[v4] = 0;
    group.len = v4;
    LOBYTE(v12) = 1;
    idStr::FreeData(&result);
    if ( !idStr::Cmp(group.data, this->cvarGroup.data.data) )
      idSliderWindow::UpdateCvar(this, 1, 1);
  }
  LOBYTE(v12) = 0;
  idStr::FreeData(&group);
  v12 = -1;
  idStr::FreeData(&event);
}
