
// FUNC: public: void __thiscall idWindow::SetFont(void)
void __thiscall idWindow::SetFont(idWindow *this)
{
  idDeviceContext::SetFont(this->dc, this->fontNum);
}

// FUNC: public: float __thiscall idWindow::GetMaxCharHeight(void)
double __thiscall idWindow::GetMaxCharHeight(idWindow *this)
{
  idDeviceContext::SetFont(this->dc, this->fontNum);
  return (double)idDeviceContext::MaxCharHeight(this->dc, this->textScale.data);
}

// FUNC: public: float __thiscall idWindow::GetMaxCharWidth(void)
double __thiscall idWindow::GetMaxCharWidth(idWindow *this)
{
  idDeviceContext::SetFont(this->dc, this->fontNum);
  return (double)idDeviceContext::MaxCharWidth(this->dc, this->textScale.data);
}

// FUNC: public: virtual void __thiscall idWindow::MouseEnter(void)
void __thiscall idWindow::MouseEnter(idWindow *this)
{
  if ( !this->noEvents.data )
    this->RunScript(this, 0);
}

// FUNC: public: virtual void __thiscall idWindow::MouseExit(void)
void __thiscall idWindow::MouseExit(idWindow *this)
{
  if ( !this->noEvents.data )
    this->RunScript(this, 1);
}

// FUNC: public: bool __thiscall idWindow::Contains(class idRectangle const &,float,float)
bool __thiscall idWindow::Contains(idWindow *this, const idRectangle *sr, float x, float y)
{
  double v4; // st7
  float w; // edx
  float h; // eax
  double v7; // st7
  idRectangle r; // [esp+0h] [ebp-10h] BYREF

  v4 = this->actualX - this->drawRect.x;
  r.x = sr->x;
  r.y = sr->y;
  w = sr->w;
  h = sr->h;
  r.x = v4 + r.x;
  r.w = w;
  v7 = this->actualY - this->drawRect.y + r.y;
  r.h = h;
  r.y = v7;
  return idRectangle::Contains(&r, x, y);
}

// FUNC: public: bool __thiscall idWindow::Contains(float,float)
bool __thiscall idWindow::Contains(idWindow *this, float x, float y)
{
  float h; // eax
  float actualX; // edx
  float actualY; // eax
  idRectangle r; // [esp+0h] [ebp-10h] BYREF

  r.x = this->drawRect.x;
  r.y = this->drawRect.y;
  h = this->drawRect.h;
  r.w = this->drawRect.w;
  actualX = this->actualX;
  r.h = h;
  actualY = this->actualY;
  r.x = actualX;
  r.y = actualY;
  return idRectangle::Contains(&r, x, y);
}

// FUNC: public: virtual void __thiscall idWindow::DrawBackground(class idRectangle const &)
void __thiscall idWindow::DrawBackground(idWindow *this, const idRectangle *drawRect)
{
  idMaterial *background; // ecx
  float scalex; // [esp+8h] [ebp-4h]
  float drawRecta; // [esp+10h] [ebp+4h]

  if ( this->backColor.data.w != 0.0 )
    idDeviceContext::DrawFilledRect(
      this->dc,
      drawRect->x,
      LODWORD(drawRect->y),
      drawRect->w,
      drawRect->h,
      &this->backColor.data);
  background = (idMaterial *)this->background;
  if ( background && this->matColor.data.w != 0.0 )
  {
    if ( (this->flags & 0x40000) != 0 )
    {
      scalex = drawRect->w / (double)idMaterial::GetImageWidth(background);
      drawRecta = drawRect->h / (double)idMaterial::GetImageHeight((idMaterial *)this->background);
      idDeviceContext::DrawMaterial(
        this->dc,
        drawRect->x,
        LODWORD(drawRect->y),
        drawRect->w,
        drawRect->h,
        this->background,
        &this->matColor.data,
        scalex,
        drawRecta);
    }
    else
    {
      idDeviceContext::DrawMaterial(
        this->dc,
        drawRect->x,
        LODWORD(drawRect->y),
        drawRect->w,
        drawRect->h,
        this->background,
        &this->matColor.data,
        this->matScalex,
        this->matScaley);
    }
  }
}

// FUNC: public: void __thiscall idWindow::DrawBorderAndCaption(class idRectangle const &)
void __thiscall idWindow::DrawBorderAndCaption(idWindow *this, const idRectangle *drawRect)
{
  if ( (this->flags & 4) != 0 && this->borderSize != 0.0 && this->borderColor.data.w != 0.0 )
    idDeviceContext::DrawRect(
      this->dc,
      drawRect->x,
      LODWORD(drawRect->y),
      drawRect->w,
      drawRect->h,
      this->borderSize,
      &this->borderColor.data);
}

// FUNC: public: void __thiscall idWindow::CalcClientRect(float,float)
void __thiscall idWindow::CalcClientRect(idWindow *this, float xofs, float yofs)
{
  bool v4; // zf
  idRectangle *p_data; // eax
  float x; // edx
  idRectangle *p_drawRect; // edi
  idRectangle *v8; // ecx
  float w; // edx
  float h; // eax
  unsigned int flags; // edx
  idWindow *parent; // eax
  idRectangle *p_clientRect; // ecx
  double v14; // st7
  float v15; // ebx
  float v16; // edi
  float v17; // ecx
  float v18; // [esp+8h] [ebp-4h]
  float y; // [esp+8h] [ebp-4h]
  float xofsa; // [esp+10h] [ebp+4h]
  float yofsa; // [esp+14h] [ebp+8h]

  v4 = (this->flags & 0x20000) == 0;
  p_data = &this->rect.data;
  x = this->rect.data.x;
  p_drawRect = &this->drawRect;
  v8 = &this->drawRect;
  v8->x = x;
  v8->y = p_data->y;
  w = p_data->w;
  h = p_data->h;
  v8->w = w;
  v8->h = h;
  if ( !v4 )
  {
    v18 = this->rect.data.w;
    p_drawRect->x = ((double (__thiscall *)(idWinRectangle *))this->rect.x)(&this->rect) - v18;
    this->drawRect.y = this->rect.data.y - this->rect.data.h;
  }
  flags = this->flags;
  if ( (flags & 0x180) != 0 )
  {
    parent = this->parent;
    if ( parent )
    {
      if ( (flags & 0x80u) == 0 )
        this->drawRect.y = (parent->rect.data.h - this->rect.data.h) * 0.5;
      else
        p_drawRect->x = (parent->rect.data.w - this->rect.data.w) * 0.5;
    }
  }
  p_clientRect = &this->clientRect;
  p_drawRect->x = xofs + p_drawRect->x;
  this->drawRect.y = yofs + this->drawRect.y;
  v14 = this->rect.data.h;
  this->clientRect.x = p_drawRect->x;
  this->clientRect.y = p_drawRect->y;
  v15 = p_drawRect->w;
  v16 = p_drawRect->h;
  this->clientRect.w = v15;
  this->clientRect.h = v16;
  if ( v14 > 0.0 && this->rect.data.w > 0.0 )
  {
    if ( (flags & 4) != 0 && 0.0 != this->borderSize )
    {
      p_clientRect->x = this->borderSize + p_clientRect->x;
      this->clientRect.y = this->borderSize + this->clientRect.y;
      this->clientRect.w = this->clientRect.w - this->borderSize;
      this->clientRect.h = this->clientRect.h - this->borderSize;
    }
    this->textRect.x = p_clientRect->x;
    this->textRect.y = this->clientRect.y;
    v17 = this->clientRect.h;
    this->textRect.w = this->clientRect.w;
    this->textRect.h = v17;
    this->textRect.w = this->textRect.w - 2.0;
    this->textRect.h = this->textRect.h - 2.0;
    this->textRect.x = this->textRect.x + 2.0 + this->textAlignx;
    this->textRect.y = this->textRect.y + 2.0 + this->textAligny;
  }
  xofsa = this->rect.data.w;
  y = this->rect.data.y;
  yofsa = this->rect.data.h;
  this->origin.x = ((double (__thiscall *)(idWinRectangle *))this->rect.x)(&this->rect) + xofsa * 0.5;
  this->origin.y = yofsa * 0.5 + y;
}

// FUNC: public: virtual void __thiscall idWindow::LoseCapture(void)
void __thiscall idWindow::LoseCapture(idWindow *this)
{
  this->flags &= ~0x40u;
}

// FUNC: public: void __thiscall idWindow::SetFlag(unsigned int)
void __thiscall idWindow::SetFlag(idWindow *this, unsigned int f)
{
  this->flags |= f;
}

// FUNC: public: void __thiscall idWindow::ClearFlag(unsigned int)
void __thiscall idWindow::ClearFlag(idWindow *this, unsigned int f)
{
  this->flags &= ~f;
}

// FUNC: public: class idWindow * __thiscall idWindow::GetCaptureChild(void)
idWindow *__thiscall idWindow::GetCaptureChild(idWindow *this)
{
  if ( (this->flags & 0x10000000) != 0 )
    return this->gui->GetDesktop(this->gui)->captureChild;
  else
    return 0;
}

// FUNC: public: class idWindow * __thiscall idWindow::GetFocusedChild(void)
idWindow *__thiscall idWindow::GetFocusedChild(idWindow *this)
{
  if ( (this->flags & 0x10000000) != 0 )
    return this->gui->GetDesktop(this->gui)->focusedChild;
  else
    return 0;
}

// FUNC: public: class idWindow * __thiscall idWindow::SetFocus(class idWindow *,bool)
idWindow *__thiscall idWindow::SetFocus(idWindow *this, idWindow *w, bool scripts)
{
  idWindow *result; // eax
  idWindow *focusedChild; // edi
  idWindow_vtbl *v6; // edx
  idWindow_vtbl *v7; // eax

  result = 0;
  if ( (w->flags & 0x800) != 0 )
  {
    focusedChild = this->gui->GetDesktop(this->gui)->focusedChild;
    if ( focusedChild )
    {
      v6 = focusedChild->__vftable;
      focusedChild->flags &= ~0x20u;
      v6->LoseFocus(focusedChild);
    }
    if ( scripts )
    {
      if ( focusedChild )
        focusedChild->RunScript(focusedChild, 14);
      w->RunScript(w, 13);
    }
    v7 = w->__vftable;
    w->flags |= 0x20u;
    v7->GainFocus(w);
    this->gui->GetDesktop(this->gui)->focusedChild = w;
    return focusedChild;
  }
  return result;
}

// FUNC: protected: void __thiscall idWindow::SaveExpressionParseState(void)
void __thiscall idWindow::SaveExpressionParseState(idWindow *this)
{
  bool *v2; // eax

  v2 = (bool *)Mem_Alloc(4096, 0x13u);
  this->saveTemps = v2;
  qmemcpy(v2, idWindow::registerIsTemporary, 0x1000u);
}

// FUNC: protected: void __thiscall idWindow::RestoreExpressionParseState(void)
void __thiscall idWindow::RestoreExpressionParseState(idWindow *this)
{
  qmemcpy(idWindow::registerIsTemporary, this->saveTemps, sizeof(idWindow::registerIsTemporary));
  Mem_Free(this->saveTemps);
}

// FUNC: public: void __thiscall idWindow::StartTransition(void)
void __thiscall idWindow::StartTransition(idWindow *this)
{
  BYTE1(this->flags) |= 4u;
}

// FUNC: public: void __thiscall idWindow::ResetCinematics(void)
void __thiscall idWindow::ResetCinematics(idWindow *this)
{
  idMaterial *background; // ecx

  background = (idMaterial *)this->background;
  if ( background )
    idMaterial::ResetCinematicTime(background, this->gui->time);
}

// FUNC: public: bool __thiscall idWindow::RunScriptList(class idGuiScriptList *)
char __thiscall idWindow::RunScriptList(idWindow *this, idGuiScriptList *src)
{
  if ( !src )
    return 0;
  idGuiScriptList::Execute(src, this);
  return 1;
}

// FUNC: public: void __thiscall idWindow::WriteSaveGameString(char const *,class idFile *)
void __thiscall idWindow::WriteSaveGameString(idWindow *this, const char *string, idFile *savefile)
{
  const char *v3; // edi
  idFile *v4; // esi

  v3 = string;
  string = (const char *)strlen(string);
  v4 = savefile;
  savefile->Write(savefile, &string, 4);
  v4->Write(v4, v3, (int)string);
}

// FUNC: protected: bool __thiscall idWindow::IsVisible(void)
char __thiscall idWindow::IsVisible(idWindow *this)
{
  if ( !this->visible.data )
    return 0;
  while ( 1 )
  {
    this = this->parent;
    if ( !this )
      break;
    if ( !this->visible.data )
      return 0;
  }
  return 1;
}

// FUNC: public: void __thiscall idWindow::ScreenToClient(class idRectangle *)
void __thiscall idWindow::ScreenToClient(idWindow *this, idRectangle *r)
{
  idWindow *v2; // esi
  double v3; // st7
  int x; // [esp+8h] [ebp-8h]
  int y; // [esp+Ch] [ebp-4h]

  v2 = this;
  x = 0;
  for ( y = 0; v2; y = (int)v3 )
  {
    x = (int)(((double (__thiscall *)(idWinRectangle *))v2->rect.x)(&v2->rect) + (double)x);
    v3 = (double)y + v2->rect.data.y;
    v2 = v2->parent;
  }
  r->x = r->x - (double)x;
  r->y = r->y - (double)y;
}

// FUNC: public: void __thiscall idWindow::ClientToScreen(class idRectangle *)
void __thiscall idWindow::ClientToScreen(idWindow *this, idRectangle *r)
{
  idWindow *v2; // esi
  double v3; // st7
  int x; // [esp+8h] [ebp-8h]
  int y; // [esp+Ch] [ebp-4h]

  v2 = this;
  x = 0;
  for ( y = 0; v2; y = (int)v3 )
  {
    x = (int)(((double (__thiscall *)(idWinRectangle *))v2->rect.x)(&v2->rect) + (double)x);
    v3 = (double)y + v2->rect.data.y;
    v2 = v2->parent;
  }
  r->x = (double)x + r->x;
  r->y = (double)y + r->y;
}

// FUNC: public: unsigned int __thiscall idWindow::Size(void)
unsigned int __thiscall idWindow::Size(idWindow *this)
{
  int num; // ebx
  int v3; // ebp
  int i; // esi
  unsigned int v5; // eax

  num = this->children.num;
  v3 = 0;
  for ( i = 0; i < num; v3 += v5 )
    v5 = idWindow::Size(this->children.list[i++]);
  return this->Allocated(this) + v3 + 1048;
}

// FUNC: public: virtual unsigned int __thiscall idWindow::Allocated(void)
unsigned int __thiscall idWindow::Allocated(idWindow *this)
{
  int alloced; // edi
  unsigned int v3; // edi
  unsigned int v4; // eax
  int num; // ebp
  unsigned int v6; // edi
  int i; // ebx
  idWinVar *v8; // ecx
  idGuiScriptList **scripts; // ebx
  int v10; // ebp
  int v11; // ebp
  int j; // ebx
  int v13; // eax
  int v14; // ebp
  int k; // ebx
  int v16; // eax
  int v17; // ebp
  int m; // ebx
  idSimpleWindow *simp; // ecx

  if ( this->name.data == this->name.baseBuffer )
    alloced = 0;
  else
    alloced = this->name.alloced;
  v3 = this->text.Size(&this->text) + alloced;
  v4 = this->backGroundName.Size(&this->backGroundName);
  num = this->definedVars.num;
  v6 = v4 + v3;
  for ( i = 0; i < num; v6 += v8->Size(v8) )
    v8 = this->definedVars.list[i++];
  scripts = this->scripts;
  v10 = 28;
  do
  {
    if ( *scripts )
      v6 += idGuiScriptList::Size(*scripts);
    ++scripts;
    --v10;
  }
  while ( v10 );
  v11 = this->timeLineEvents.num;
  for ( j = 0; j < v11; v6 += v13 + 12 )
    v13 = idGuiScriptList::Size(this->timeLineEvents.list[j++]->event);
  v14 = this->namedEvents.num;
  for ( k = 0; k < v14; v6 += v16 + 36 )
    v16 = idGuiScriptList::Size(this->namedEvents.list[k++]->mEvent);
  v17 = this->drawWindows.num;
  for ( m = 0; m < v17; ++m )
  {
    simp = this->drawWindows.list[m].simp;
    if ( simp )
      v6 += idSimpleWindow::Size(simp);
  }
  return v6;
}

// FUNC: public: virtual void __thiscall idWindow::Draw(int,float,float)
void __thiscall idWindow::Draw(idWindow *this, int time, float x, float y)
{
  idWinStr *p_text; // edi
  const char *v6; // eax
  double v7; // st7
  const char *v8; // eax
  const char *v9; // eax
  int v10; // [esp-4Ch] [ebp-70h]
  float v11; // [esp-48h] [ebp-6Ch]
  int textAlign; // [esp-44h] [ebp-68h]
  int textStyle; // [esp-40h] [ebp-64h]
  idVec4 data; // [esp-3Ch] [ebp-60h]
  idVec4 v15; // [esp-3Ch] [ebp-60h]
  idVec4 v16; // [esp-3Ch] [ebp-60h]
  idRectangle textRect; // [esp-2Ch] [ebp-50h]
  idRectangle v18; // [esp-2Ch] [ebp-50h]
  idRectangle v19; // [esp-2Ch] [ebp-50h]
  bool v20; // [esp-1Ch] [ebp-40h]
  int textSpacing; // [esp-8h] [ebp-2Ch]
  float h; // [esp+8h] [ebp-1Ch]
  int adjust; // [esp+Ch] [ebp-18h]
  float textScale; // [esp+10h] [ebp-14h]
  __int64 v25; // [esp+14h] [ebp-10h]

  p_text = &this->text;
  if ( idWinStr::Length(&this->text) )
  {
    textSpacing = (int)this->textSpacing;
    v20 = (this->flags & 0x8000) == 0;
    textRect = this->textRect;
    data = this->foreColor.data;
    textStyle = this->textStyle;
    textAlign = this->textAlign;
    v11 = this->textScale.data;
    v6 = p_text->c_str(p_text);
    idDeviceContext::DrawTextA(
      this->dc,
      v6,
      v11,
      textAlign,
      textStyle,
      data,
      textRect,
      v20,
      -1,
      0,
      0,
      0,
      textSpacing,
      0);
    if ( idWindow::gui_edit.internalVar->integerValue )
    {
      this->dc->enableClipping = 0;
      textScale = this->rect.data.y;
      *(float *)&v25 = this->rect.x(&this->rect);
      *((float *)&v25 + 1) = textScale - 15.0;
      *(_QWORD *)&v18.x = v25;
      *(_QWORD *)&v18.w = 0x41A0000042C80000i64;
      v15 = idDeviceContext::colorWhite;
      v7 = ((double (__thiscall *)(idWinRectangle *, int))this->rect.x)(&this->rect, (int)this->rect.data.y);
      v8 = va("x: %i  y: %i", (int)v7, v10);
      idDeviceContext::DrawTextA(this->dc, v8, 0.25, 0, 0, v15, v18, 0, -1, 0, 0, 0, 0, 0);
      adjust = SLODWORD(this->rect.data.w);
      h = this->rect.data.h;
      *(float *)&v25 = ((double (__thiscall *)(idWinRectangle *))this->rect.x)(&this->rect) + *(float *)&adjust;
      *((float *)&v25 + 1) = *(float *)&adjust + h + 5.0;
      *(_QWORD *)&v19.x = v25;
      *(_QWORD *)&v19.w = 0x41A0000042C80000i64;
      v16 = idDeviceContext::colorWhite;
      v9 = va("w: %i  h: %i", (int)this->rect.data.w, (int)this->rect.data.h);
      idDeviceContext::DrawTextA(this->dc, v9, 0.25, 0, 0, v16, v19, 0, -1, 0, 0, 0, 0, 0);
      this->dc->enableClipping = 1;
    }
  }
}

// FUNC: public: void __thiscall idWindow::BringToTop(class idWindow *)
void __thiscall idWindow::BringToTop(idWindow *this, idWindow *w)
{
  int num; // esi
  int v3; // eax
  idWindow **i; // edx
  idWindow **list; // edx
  idWindow *v6; // ebx
  idWindow **v7; // edx

  if ( !w || (w->flags & 0x200) != 0 )
  {
    num = this->children.num;
    v3 = 0;
    if ( num > 0 )
    {
      for ( i = this->children.list; ; ++i )
      {
        ++v3;
        if ( *i == w )
          break;
        if ( v3 >= num )
          return;
      }
      for ( ; v3 < num; *(v7 - 1) = v6 )
      {
        list = this->children.list;
        v6 = list[v3];
        v7 = &list[v3++];
      }
      this->children.list[num - 1] = w;
    }
  }
}

// FUNC: public: virtual void __thiscall idWindow::FindBestChild_r(int,int,int &,int &,int &,int &,class idWindow *,class idWindow * &)
void __thiscall idWindow::FindBestChild_r(
        idWindow *this,
        int xd,
        int yd,
        int *startX,
        int *startY,
        int *bestX,
        int *bestY,
        idWindow *current,
        idWindow **best)
{
  int num; // edi
  idWindow *v10; // esi
  int actualX; // ebp
  double actualY; // st7
  int v13; // edi
  bool v14; // sf
  bool v15; // sf
  int c; // [esp+4h] [ebp-10h]
  idWindow *v17; // [esp+8h] [ebp-Ch]

  num = this->children.num;
  v17 = this;
  if ( num > 0 )
  {
    while ( 1 )
    {
      v10 = this->children.list[--num];
      c = num;
      if ( !v10->visible.data )
        goto LABEL_35;
      if ( v10->noEvents.data || !v10->scripts[0] || v10 == current )
      {
        v10->FindBestChild_r(v10, xd, yd, startX, startY, bestX, bestY, current, best);
        goto LABEL_35;
      }
      actualX = (int)v10->actualX;
      actualY = v10->actualY;
      v13 = (int)actualY;
      if ( gui_debugScript.internalVar->integerValue )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "Examing %s at (%08x) at (%d,%d)\n",
          v10->name.data,
          v10,
          actualX,
          (int)actualY);
      v14 = yd < 0;
      if ( yd > 0 )
      {
        if ( v13 > *startY && (!*best || v13 < *bestY) )
        {
          *best = v10;
          *bestY = v13;
          goto LABEL_31;
        }
        v14 = yd < 0;
      }
      if ( !v14 || v13 >= *startY || *best && v13 <= *bestY )
      {
        v15 = xd < 0;
        if ( xd <= 0 )
          goto LABEL_26;
        if ( actualX <= *startX || *best && actualX >= *bestX )
        {
          v15 = xd < 0;
LABEL_26:
          if ( !v15 || actualX >= *startX || *best && actualX <= *bestX )
            goto LABEL_31;
        }
        *best = v10;
        *bestX = actualX;
        goto LABEL_31;
      }
      *best = v10;
      *bestY = v13;
LABEL_31:
      if ( gui_debugScript.internalVar->integerValue )
      {
        if ( *best == v10 )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "   Best Yet\n");
      }
      num = c;
LABEL_35:
      if ( num <= 0 )
        return;
      this = v17;
    }
  }
}

// FUNC: public: virtual void __thiscall idWindow::Init(void)
void __thiscall idWindow::Init(idWindow *this)
{
  int num; // edi
  int i; // esi
  idWindow *v4; // ecx

  if ( !session->GetLoadingSaveGame(session) )
    this->RunScript(this, 16);
  num = this->children.num;
  for ( i = 0; i < num; ++i )
  {
    v4 = this->children.list[i];
    v4->Init(v4);
  }
}

// FUNC: public: virtual void __thiscall idWindow::Trigger(void)
void __thiscall idWindow::Trigger(idWindow *this)
{
  int num; // ebx
  int i; // esi
  idWindow *v4; // ecx

  this->RunScript(this, 8);
  num = this->children.num;
  for ( i = 0; i < num; ++i )
  {
    v4 = this->children.list[i];
    v4->Trigger(v4);
  }
  this->StateChanged(this, 1);
}

// FUNC: public: class idWindow * __thiscall idWindow::SetCapture(class idWindow *)
idWindow *__thiscall idWindow::SetCapture(idWindow *this, idWindow *w)
{
  int num; // ecx
  idWindow *v4; // edi
  int v5; // eax
  idWindow **list; // edx
  idWindow_vtbl *v7; // edx

  num = this->children.num;
  v4 = 0;
  v5 = 0;
  if ( num > 0 )
  {
    list = this->children.list;
    while ( ((*list)->flags & 0x40) == 0 )
    {
      ++v5;
      ++list;
      if ( v5 >= num )
        goto LABEL_7;
    }
    v4 = this->children.list[v5];
    v4->LoseCapture(v4);
  }
LABEL_7:
  if ( w )
  {
    v7 = w->__vftable;
    w->flags |= 0x40u;
    v7->GainCapture(w);
  }
  this->gui->GetDesktop(this->gui)->captureChild = w;
  return v4;
}

// FUNC: public: void __thiscall idWindow::DebugDraw(int,float,float)
void __thiscall idWindow::DebugDraw(idWindow *this, int time, float x, float y)
{
  idDeviceContext *dc; // eax
  int integerValue; // eax
  idWinStr_vtbl *v7; // eax
  char *v8; // eax
  double v9; // st7
  idUserInterfaceLocal *gui; // esi
  unsigned __int64 v11; // st7
  double v12; // st7
  double v13; // [esp+8h] [ebp-460h]
  double v14; // [esp+10h] [ebp-458h]
  double v15; // [esp+18h] [ebp-450h]
  double v16; // [esp+18h] [ebp-450h]
  idStr str; // [esp+38h] [ebp-430h] BYREF
  char out[1024]; // [esp+58h] [ebp-410h] BYREF
  int v19; // [esp+464h] [ebp-4h]

  dc = this->dc;
  if ( dc )
  {
    dc->enableClipping = 0;
    integerValue = idWindow::gui_debug.internalVar->integerValue;
    if ( integerValue == 1 )
    {
      idDeviceContext::DrawRect(
        this->dc,
        this->drawRect.x,
        LODWORD(this->drawRect.y),
        this->drawRect.w,
        this->drawRect.h,
        1.0,
        &idDeviceContext::colorRed);
    }
    else if ( integerValue == 2 )
    {
      str.len = 0;
      str.alloced = 20;
      str.data = str.baseBuffer;
      str.baseBuffer[0] = 0;
      v7 = this->text.__vftable;
      v19 = 0;
      v8 = (char *)v7->c_str(&this->text);
      idStr::operator=(&str, v8);
      if ( str.len )
        sprintf(buff, "%s\n", str.data);
      v9 = ((double (__thiscall *)(idWinRectangle *, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))this->rect.x)(
             &this->rect,
             COERCE_UNSIGNED_INT64(this->rect.data.y),
             HIDWORD(COERCE_UNSIGNED_INT64(this->rect.data.y)),
             COERCE_UNSIGNED_INT64(this->rect.data.w),
             HIDWORD(COERCE_UNSIGNED_INT64(this->rect.data.w)),
             COERCE_UNSIGNED_INT64(this->rect.data.h),
             HIDWORD(COERCE_UNSIGNED_INT64(this->rect.data.h)));
      sprintf(out, "Rect: %0.1f, %0.1f, %0.1f, %0.1f\n", v9, v13, v14, v15);
      strcat(buff, out);
      sprintf(
        out,
        "Draw Rect: %0.1f, %0.1f, %0.1f, %0.1f\n",
        this->drawRect.x,
        this->drawRect.y,
        this->drawRect.w,
        this->drawRect.h);
      strcat(buff, out);
      sprintf(
        out,
        "Client Rect: %0.1f, %0.1f, %0.1f, %0.1f\n",
        this->clientRect.x,
        this->clientRect.y,
        this->clientRect.w,
        this->clientRect.h);
      strcat(buff, out);
      gui = this->gui;
      *(double *)&v11 = ((double (*)(void))gui->CursorY)();
      v12 = ((double (__thiscall *)(idUserInterfaceLocal *, _DWORD, _DWORD))gui->CursorX)(gui, v11, HIDWORD(v11));
      sprintf(out, "Cursor: %0.1f : %0.1f\n", v12, v16);
      strcat(buff, out);
      idDeviceContext::DrawTextA(
        this->dc,
        buff,
        this->textScale.data,
        this->textAlign,
        this->textStyle,
        this->foreColor.data,
        this->textRect,
        1,
        -1,
        0,
        0,
        0,
        0,
        0);
      v19 = -1;
      idStr::FreeData(&str);
    }
    this->dc->enableClipping = 1;
  }
}

// FUNC: public: void __thiscall idWindow::CalcRects(float,float)
void __thiscall idWindow::CalcRects(idWindow *this, float x, float y)
{
  int v4; // edi
  int num; // ebx
  float v6; // ecx
  idWindow *win; // ecx
  float v8; // [esp+0h] [ebp-14h]
  float v9; // [esp+4h] [ebp-10h]

  idWindow::CalcClientRect(this, 0.0, 0.0);
  v4 = 0;
  this->drawRect.x = x + this->drawRect.x;
  this->drawRect.y = y + this->drawRect.y;
  this->clientRect.x = x + this->clientRect.x;
  this->clientRect.y = y + this->clientRect.y;
  num = this->drawWindows.num;
  v6 = this->drawRect.y;
  this->actualX = this->drawRect.x;
  this->actualY = v6;
  if ( num > 0 )
  {
    do
    {
      win = this->drawWindows.list[v4].win;
      if ( win )
      {
        v9 = this->yOffset + this->clientRect.y;
        v8 = this->xOffset + this->clientRect.x;
        idWindow::CalcRects(win, v8, v9);
      }
      ++v4;
    }
    while ( v4 < num );
  }
  this->drawRect.x = this->drawRect.x - x;
  this->drawRect.y = this->drawRect.y - y;
  this->clientRect.x = this->clientRect.x - x;
  this->clientRect.y = this->clientRect.y - y;
}

// FUNC: public: void __thiscall idWindow::SetDC(class idDeviceContext *)
void __thiscall idWindow::SetDC(idWindow *this, idDeviceContext *d)
{
  float forceAspectHeight; // eax
  int num; // ebp
  int i; // esi
  float forceAspectWidth; // [esp-8h] [ebp-18h]

  forceAspectHeight = this->forceAspectHeight;
  forceAspectWidth = this->forceAspectWidth;
  this->dc = d;
  idDeviceContext::SetSize(d, forceAspectWidth, forceAspectHeight);
  num = this->children.num;
  for ( i = 0; i < num; ++i )
    idWindow::SetDC(this->children.list[i], d);
}

// FUNC: public: virtual void __thiscall idWindow::ArchiveToDictionary(class idDict *,bool)
void __thiscall idWindow::ArchiveToDictionary(idWindow *this, idDict *dict, bool useNames)
{
  int num; // ebx
  int i; // esi
  idWindow *v6; // ecx

  num = this->children.num;
  for ( i = 0; i < num; ++i )
  {
    v6 = this->children.list[i];
    v6->ArchiveToDictionary(v6, dict, 1);
  }
}

// FUNC: public: virtual void __thiscall idWindow::InitFromDictionary(class idDict *,bool)
void __thiscall idWindow::InitFromDictionary(idWindow *this, idDict *dict, bool byName)
{
  int num; // ebx
  int i; // esi
  idWindow *v6; // ecx

  num = this->children.num;
  for ( i = 0; i < num; ++i )
  {
    v6 = this->children.list[i];
    v6->InitFromDictionary(v6, dict, 1);
  }
}

// FUNC: public: void __thiscall idWindow::SetupBackground(void)
void __thiscall idWindow::SetupBackground(idWindow *this)
{
  idMaterial *v2; // eax
  const idMaterial *background; // ecx

  if ( idWinBackground::Length(&this->backGroundName) )
  {
    v2 = (idMaterial *)declManager->FindMaterial(declManager, this->backGroundName.data.data, 1);
    this->background = v2;
    idMaterial::SetImageClassifications(v2, 1);
    background = this->background;
    if ( background )
    {
      if ( (background->materialFlags & 1) == 0 && background->sort < 100.0 )
        background->sort = -2.0;
    }
  }
  this->backGroundName.mat = &this->background;
}

// FUNC: public: void __thiscall idWindow::SetupFromState(void)
void __thiscall idWindow::SetupFromState(idWindow *this)
{
  idStr str; // [esp+Ch] [ebp-2Ch] BYREF
  int v3; // [esp+34h] [ebp-4h]

  str.len = 0;
  str.alloced = 20;
  str.data = str.baseBuffer;
  str.baseBuffer[0] = 0;
  v3 = 0;
  this->background = 0;
  idWindow::SetupBackground(this);
  if ( this->borderSize != 0.0 )
    this->flags |= 4u;
  if ( idRegisterList::FindReg(&this->regList, "rotate") || idRegisterList::FindReg(&this->regList, "shear") )
    BYTE1(this->flags) |= 0x20u;
  idWindow::CalcClientRect(this, 0.0, 0.0);
  if ( this->scripts[2] )
  {
    BYTE1(this->flags) |= 8u;
    this->cursor = 1;
  }
  v3 = -1;
  idStr::FreeData(&str);
}

// FUNC: public: int __thiscall idWindow::GetWinVarOffset(class idWinVar *,struct drawWin_t *)
int __thiscall idWindow::GetWinVarOffset(idWindow *this, idWinVar *wv, drawWin_t *owner)
{
  int result; // eax
  int i; // ebx
  drawWin_t *list; // edx
  idWindow *win; // ecx

  result = -1;
  if ( wv == &this->rect )
    result = 284;
  if ( wv == &this->backColor )
    result = 316;
  if ( wv == &this->matColor )
    result = 348;
  if ( wv == &this->foreColor )
    result = 380;
  if ( wv == &this->hoverColor )
    result = 412;
  if ( wv == &this->borderColor )
    result = 444;
  if ( wv == &this->textScale )
    result = 476;
  if ( wv == &this->rotate )
  {
    owner->win = this;
    return 496;
  }
  else if ( result == -1 )
  {
    for ( i = 0; i < this->drawWindows.num; ++i )
    {
      list = this->drawWindows.list;
      win = list[i].win;
      if ( win )
        result = idWindow::GetWinVarOffset(win, wv, owner);
      else
        result = idSimpleWindow::GetWinVarOffset(list[i].simp, wv, owner);
      if ( result != -1 )
        break;
    }
  }
  else
  {
    owner->win = this;
  }
  return result;
}

// FUNC: protected: void __thiscall idWindow::ParseVec4(class idParser *,class idVec4 &)
void __thiscall idWindow::ParseVec4(idWindow *this, idParser *src, idVec4 *out)
{
  idToken tok; // [esp+4h] [ebp-5Ch] BYREF
  int v4; // [esp+5Ch] [ebp-4h]

  tok.floatvalue = 0.0;
  tok.len = 0;
  tok.alloced = 20;
  tok.data = tok.baseBuffer;
  tok.baseBuffer[0] = 0;
  v4 = 0;
  idParser::ReadToken(src, &tok);
  out->x = atof(tok.data);
  idParser::ExpectTokenString(src, ",");
  idParser::ReadToken(src, &tok);
  out->y = atof(tok.data);
  idParser::ExpectTokenString(src, ",");
  idParser::ReadToken(src, &tok);
  out->z = atof(tok.data);
  idParser::ExpectTokenString(src, ",");
  idParser::ReadToken(src, &tok);
  out->w = atof(tok.data);
  v4 = -1;
  idStr::FreeData(&tok);
}

// FUNC: public: void __thiscall idWindow::SetInitialState(char const *)
void __thiscall idWindow::SetInitialState(idWindow *this, char *_name)
{
  idStr::operator=(&this->name, _name);
  this->matScalex = 1.0;
  this->matScaley = 1.0;
  this->forceAspectWidth = 640.0;
  this->forceAspectHeight = 480.0;
  LOBYTE(_name) = 0;
  idWinBool::operator=(&this->noTime, (bool *)&_name);
  LOBYTE(_name) = 1;
  idWinBool::operator=(&this->visible, (bool *)&_name);
  this->flags = 0;
}

// FUNC: public: struct drawWin_t * __thiscall idWindow::FindChildByName(char const *)
drawWin_t *__thiscall idWindow::FindChildByName(idWindow *this, const char *_name)
{
  drawWin_t *result; // eax
  int num; // edx
  int startChildSearch; // ecx
  int v7; // eax
  int v8; // esi
  int v9; // ebp
  drawWin_t *list; // eax
  idWindow *win; // ecx
  drawWin_t *v12; // eax
  drawWin_t *v13; // eax
  drawWin_t *v14; // ecx
  int phase; // [esp+8h] [ebp-8h]
  int c; // [esp+Ch] [ebp-4h]
  const char *_namea; // [esp+14h] [ebp+4h]

  if ( !idStr::Icmp(this->name.data, _name) )
  {
    dw.win = this;
    dw.simp = 0;
    return &dw;
  }
  num = this->drawWindows.num;
  startChildSearch = this->startChildSearch;
  c = num;
  _namea = (const char *)startChildSearch;
  if ( startChildSearch >= num )
  {
    _namea = 0;
    startChildSearch = 0;
  }
  v7 = 0;
  phase = 0;
  while ( 1 )
  {
    v8 = v7 == 0 ? startChildSearch : 0;
    v9 = startChildSearch;
    if ( !v7 )
      v9 = num;
    if ( v8 < v9 )
      break;
LABEL_16:
    phase = ++v7;
    if ( v7 >= 2 )
      return 0;
  }
  while ( 1 )
  {
    list = this->drawWindows.list;
    win = list[v8].win;
    v12 = &list[v8];
    if ( !win )
      break;
    if ( !idStr::Icmp(win->name.data, _name) )
    {
      v13 = this->drawWindows.list;
      this->startChildSearch = v8;
      return &v13[v8];
    }
    result = idWindow::FindChildByName(this->drawWindows.list[v8].win, _name);
    if ( result )
    {
      this->startChildSearch = v8;
      return result;
    }
LABEL_14:
    if ( ++v8 >= v9 )
    {
      v7 = phase;
      startChildSearch = (int)_namea;
      num = c;
      goto LABEL_16;
    }
  }
  if ( idStr::Icmp(v12->simp->name.data, _name) )
    goto LABEL_14;
  v14 = this->drawWindows.list;
  this->startChildSearch = v8;
  return &v14[v8];
}

// FUNC: public: void __thiscall idWindow::ResetTime(int)
void __thiscall idWindow::ResetTime(idWindow *this, int t)
{
  int num; // edx
  int v4; // eax
  idTimeLineEvent *v5; // ecx
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // esi
  idDict *v10; // edi
  const char *v11; // eax
  int v12; // esi
  int v13; // ebx
  int v14; // edx
  float *v15; // ecx
  int v16; // eax
  bool v17; // cc
  int v18; // eax
  int v19; // [esp+10h] [ebp-4h]
  int ta; // [esp+18h] [ebp+4h]

  num = this->timeLineEvents.num;
  v4 = 0;
  for ( this->timeLine = this->gui->time - t; v4 < num; ++v4 )
  {
    v5 = this->timeLineEvents.list[v4];
    if ( v5->time >= t )
      v5->pending = 1;
  }
  guiDict = this->noTime.guiDict;
  this->noTime.data = 0;
  if ( guiDict )
  {
    name = this->noTime.name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->noTime.name;
        goto LABEL_12;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_12:
        v10 = this->noTime.guiDict;
        v11 = va("%i", this->noTime.data);
        idDict::Set(v10, data, v11);
        goto LABEL_13;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_12;
  }
LABEL_13:
  v12 = this->transitions.num;
  v13 = 0;
  ta = v12;
  if ( v12 > 0 )
  {
    v14 = 0;
    v19 = 0;
    do
    {
      v15 = (float *)((char *)this->transitions.list + v14);
      if ( v15[5] + v15[4] + v15[3] + v15[2] <= (double)this->gui->time && *(_DWORD *)v15 )
      {
        if ( v13 >= 0 )
        {
          v16 = this->transitions.num;
          if ( v13 < v16 )
          {
            v17 = v13 < v16 - 1;
            this->transitions.num = v16 - 1;
            v18 = v13;
            if ( v17 )
            {
              do
              {
                ++v18;
                qmemcpy(
                  (char *)this->transitions.list + v14,
                  (char *)&this->transitions.list[1] + v14,
                  sizeof(idTransitionData));
                v14 += 136;
              }
              while ( v18 < this->transitions.num );
              v14 = v19;
              v12 = ta;
            }
          }
        }
        --v13;
        v14 -= 136;
        ta = --v12;
      }
      ++v13;
      v14 += 136;
      v19 = v14;
    }
    while ( v13 < v12 );
  }
}

// FUNC: public: virtual bool __thiscall idWindow::RunScript(int)
char __thiscall idWindow::RunScript(idWindow *this, unsigned int n)
{
  idGuiScriptList *v3; // ecx

  if ( n > 0x1B )
    return 0;
  if ( gui_debugScript.internalVar->integerValue )
  {
    if ( this->scripts[n] )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "GUI: %s: execute %s\n",
        this->name.data,
        idWindow::ScriptNames[n]);
  }
  v3 = this->scripts[n];
  if ( !v3 )
    return 0;
  idGuiScriptList::Execute(v3, this);
  return 1;
}

// FUNC: protected: void __thiscall idWindow::EvaluateRegisters(float *)
void __thiscall idWindow::EvaluateRegisters(idWindow *this, float *registers)
{
  idWindow *v2; // ebp
  idWinVec4 *num; // ecx
  int v4; // eax
  int v6; // edi
  int v7; // edx
  unsigned int v8; // ecx
  int v9; // ebx
  float *v10; // eax
  char *v11; // edx
  wexpOp_t *v12; // edi
  int v13; // ecx
  int v14; // ecx
  const idDecl *v15; // eax
  double v16; // st7
  int c; // ecx
  int a; // ecx
  const char *v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  idWindow *v24; // [esp+10h] [ebp-10h]
  int v25; // [esp+10h] [ebp-10h]
  int v26; // [esp+14h] [ebp-Ch]
  int v27; // [esp+14h] [ebp-Ch]
  idWinVec4 *var; // [esp+18h] [ebp-8h]
  int b; // [esp+1Ch] [ebp-4h]
  float *registersa; // [esp+24h] [ebp+4h]
  int registersb; // [esp+24h] [ebp+4h]
  int registersc; // [esp+24h] [ebp+4h]

  v2 = this;
  num = (idWinVec4 *)this->expressionRegisters.num;
  v4 = v2->ops.num;
  v24 = v2;
  var = num;
  b = v4;
  v6 = 1;
  if ( (int)&num[-1].data.w + 3 >= 4 )
  {
    v26 = 4 - (_DWORD)registers;
    v7 = -8 - (_DWORD)registers;
    v8 = (((unsigned int)&num[-1].data.z + 3) >> 2) + 1;
    v9 = 3;
    v10 = registers + 3;
    registersa = (float *)(-8 - (_DWORD)registers);
    v6 = 4 * v8 + 1;
    while ( 1 )
    {
      v11 = (char *)v10 + v7;
      *(v10 - 2) = *(float *)&v11[(unsigned int)v2->expressionRegisters.list];
      *(v10 - 1) = *(float *)&v11[(unsigned int)v24->expressionRegisters.list + 4];
      *v10 = v24->expressionRegisters.list[v9];
      v2 = v24;
      v10[1] = *(float *)((char *)v24->expressionRegisters.list + (unsigned int)v10 + v26);
      v9 += 4;
      v10 += 4;
      if ( !--v8 )
        break;
      v7 = (int)registersa;
    }
    num = var;
    v4 = b;
  }
  for ( ; v6 < (int)num; ++v6 )
    registers[v6] = v2->expressionRegisters.list[v6];
  *registers = (float)v2->gui->time;
  if ( v4 > 0 )
  {
    v25 = 0;
    v27 = v4;
    do
    {
      v12 = &v2->ops.list[v25];
      v13 = v12->b;
      if ( v13 != -2 )
      {
        switch ( v12->opType )
        {
          case WOP_TYPE_ADD:
            registers[v12->c] = registers[v12->a] + registers[v13];
            break;
          case WOP_TYPE_SUBTRACT:
            registers[v12->c] = registers[v12->a] - registers[v13];
            break;
          case WOP_TYPE_MULTIPLY:
            registers[v12->c] = registers[v12->a] * registers[v13];
            break;
          case WOP_TYPE_DIVIDE:
            if ( registers[v13] == 0.0 )
            {
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
                common.type,
                "Divide by zero in window '%s' in %s",
                v2->name.data,
                v2->gui->source.data);
              registers[v12->c] = registers[v12->a];
            }
            else
            {
              registers[v12->c] = registers[v12->a] / registers[v13];
            }
            break;
          case WOP_TYPE_MOD:
            b = (int)registers[v13];
            v14 = b;
            if ( !b )
              v14 = 1;
            b = (int)registers[v12->a];
            registers[v12->c] = (float)(b % v14);
            break;
          case WOP_TYPE_TABLE:
            v15 = declManager->DeclByIndex(declManager, 0, v12->a, 1);
            registers[v12->c] = ((double (__thiscall *)(const idDecl *, _DWORD))v15->__vftable[1].~idDecl)(
                                  v15,
                                  LODWORD(registers[v12->b]));
            break;
          case WOP_TYPE_GT:
            registers[v12->c] = (float)(registers[v12->a] > (double)registers[v13]);
            break;
          case WOP_TYPE_GE:
            registers[v12->c] = (float)(registers[v12->a] >= (double)registers[v13]);
            break;
          case WOP_TYPE_LT:
            registers[v12->c] = (float)(registers[v12->a] < (double)registers[v13]);
            break;
          case WOP_TYPE_LE:
            registers[v12->c] = (float)(registers[v12->a] <= (double)registers[v13]);
            break;
          case WOP_TYPE_EQ:
            registers[v12->c] = (float)(registers[v12->a] == registers[v13]);
            break;
          case WOP_TYPE_NE:
            registers[v12->c] = (float)(registers[v12->a] != registers[v13]);
            break;
          case WOP_TYPE_AND:
            if ( registers[v12->a] == 0.0 || (registersb = 1, registers[v13] == 0.0) )
              registersb = 0;
            registers[v12->c] = (float)registersb;
            break;
          case WOP_TYPE_OR:
            if ( registers[v12->a] != 0.0 || (registersc = 0, registers[v13] != 0.0) )
              registersc = 1;
            registers[v12->c] = (float)registersc;
            break;
          case WOP_TYPE_VAR:
            if ( !v12->a )
              goto LABEL_40;
            if ( v13 < 0 || registers[v13] < 0.0 || registers[v13] >= 4.0 )
            {
              registers[v12->c] = ((double (__thiscall *)(int))*(_DWORD *)(*(_DWORD *)v12->a + 48))(v12->a);
            }
            else
            {
              v16 = registers[v13];
              c = v12->c;
              var = (idWinVec4 *)v12->a;
              b = (int)v16;
              LODWORD(registers[c]) = *(&var + (int)v16);
            }
            break;
          case WOP_TYPE_VARS:
            a = v12->a;
            if ( !a )
              goto LABEL_56;
            v19 = (const char *)(*(int (__thiscall **)(int))(*(_DWORD *)a + 32))(a);
            registers[v12->c] = atof(v19);
            break;
          case WOP_TYPE_VARF:
            v20 = v12->a;
            if ( !v20 )
              goto LABEL_56;
            registers[v12->c] = *(float *)(v20 + 16);
            break;
          case WOP_TYPE_VARI:
            v22 = v12->a;
            if ( !v22 )
              goto LABEL_56;
            registers[v12->c] = (float)*(int *)(v22 + 16);
            break;
          case WOP_TYPE_VARB:
            v23 = v12->a;
            if ( v23 )
              registers[v12->c] = (float)*(unsigned __int8 *)(v23 + 16);
            else
LABEL_56:
              registers[v12->c] = 0.0;
            break;
          case WOP_TYPE_COND:
            if ( registers[v12->a] == 0.0 )
              registers[v12->c] = registers[v12->d];
            else
              registers[v12->c] = registers[v13];
            break;
          case WOP_TYPE_VARFM:
            v21 = v12->a;
            if ( v21 )
              registers[v12->c] = ((double (__thiscall *)(_DWORD, _DWORD))*(_DWORD *)(**(_DWORD **)(v21 + 16) + 24))(
                                    *(_DWORD *)(v21 + 16),
                                    *(_DWORD *)(v21 + 20));
            else
LABEL_40:
              registers[v12->c] = 0.0;
            break;
          default:
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
              common.type,
              "R_EvaluateExpression: bad opcode");
            break;
        }
      }
      ++v25;
      --v27;
    }
    while ( v27 );
  }
}

// FUNC: public: void __thiscall idWindow::WriteSaveGameTransition(struct idTransitionData &,class idFile *)
void __thiscall idWindow::WriteSaveGameTransition(idWindow *this, idTransitionData *trans, idFile *savefile)
{
  int v4; // eax
  char v5; // cl
  int guiDict; // ebx
  void *v7; // eax
  idUserInterfaceLocal *gui; // ecx
  idWindow *v9; // eax
  int WinVarOffset; // eax
  idWinVar *v11; // ecx
  idWindow *v12; // eax
  char *v13; // eax
  idWindow *v14; // eax
  drawWin_t *ChildByName; // eax
  idWinVar *data; // [esp-14h] [ebp-5Ch]
  idWinVar *v18; // [esp-8h] [ebp-50h]
  idWinVar *v19; // [esp-8h] [ebp-50h]
  char *v20; // [esp-4h] [ebp-4Ch]
  int offset; // [esp+10h] [ebp-38h] BYREF
  drawWin_t dw; // [esp+14h] [ebp-34h] BYREF
  idStr winName; // [esp+1Ch] [ebp-2Ch] BYREF
  int v24; // [esp+44h] [ebp-4h]

  winName.data = winName.baseBuffer;
  winName.alloced = 20;
  winName.baseBuffer[0] = 0;
  v4 = 0;
  do
  {
    v5 = *(&entityFilter + v4);
    winName.baseBuffer[v4++] = v5;
  }
  while ( v5 );
  winName.len = 0;
  data = trans->data;
  v24 = 0;
  dw.simp = 0;
  dw.win = 0;
  guiDict = -1;
  v7 = __RTDynamicCast(data, 0, &idWinVar `RTTI Type Descriptor', &idWinFloatMember `RTTI Type Descriptor', 0);
  gui = this->gui;
  if ( v7 )
  {
    v18 = (idWinVar *)trans->data[1].__vftable;
    v9 = gui->GetDesktop(gui);
    WinVarOffset = idWindow::GetWinVarOffset(v9, v18, &dw);
    v11 = trans->data;
    offset = WinVarOffset;
    guiDict = (int)v11[1].guiDict;
  }
  else
  {
    v19 = trans->data;
    v12 = gui->GetDesktop(gui);
    offset = idWindow::GetWinVarOffset(v12, v19, &dw);
  }
  if ( dw.win )
  {
    v13 = dw.win->name.data;
    goto LABEL_9;
  }
  if ( dw.simp )
  {
    v13 = dw.simp->name.data;
LABEL_9:
    idStr::operator=(&winName, v13);
  }
  v20 = winName.data;
  v14 = this->gui->GetDesktop(this->gui);
  ChildByName = idWindow::FindChildByName(v14, v20);
  if ( offset != -1 && ChildByName && (ChildByName->win || ChildByName->simp) )
  {
    savefile->Write(savefile, &offset, 4);
    idWindow::WriteSaveGameString(this, winName.data, savefile);
    savefile->Write(savefile, &trans->interp, 128);
    savefile->WriteInt(savefile, guiDict);
  }
  else
  {
    offset = -1;
    savefile->Write(savefile, &offset, 4);
  }
  v24 = -1;
  idStr::FreeData(&winName);
}

// FUNC: public: virtual void __thiscall idWindow::WriteToSaveGame(class idFile *)
void __userpurge idWindow::WriteToSaveGame(idWindow *this@<ecx>, int a2@<ebp>, idFile *savefile, int winID)
{
  char *data; // ebx
  unsigned int v6; // eax
  char *v8; // ebx
  idFile_vtbl *v9; // edx
  char *v10; // ebx
  idFile_vtbl *v11; // edx
  int i; // ebx
  idWinVar *v13; // ecx
  idWindow *focusedChild; // eax
  idWindow *captureChild; // eax
  idWindow *overChild; // eax
  idGuiScriptList **scripts; // ebx
  int v18; // ebp
  int j; // ebx
  idTimeLineEvent *v20; // eax
  idGuiScriptList *event; // ecx
  int v22; // ebx
  int v23; // ebp
  int k; // ebx
  rvNamedEvent *v25; // eax
  const char *v26; // ebp
  unsigned int v27; // eax
  idFile_vtbl *v28; // edx
  idGuiScriptList *mEvent; // ecx
  int m; // ebx
  drawWin_t *list; // eax
  idWindow *win; // ecx
  idSimpleWindow *simp; // eax
  int v34; // [esp+164h] [ebp-8h] BYREF
  int num; // [esp+168h] [ebp-4h] BYREF
  int retaddr; // [esp+16Ch] [ebp+0h] BYREF

  data = this->cmd.data;
  v6 = strlen(data);
  v34 = v6;
  ((void (__thiscall *)(idFile *, int *, int, int))savefile->Write)(savefile, &v34, 4, a2);
  savefile->Write(savefile, data, num);
  savefile->Write(savefile, &this->actualX, 4);
  savefile->Write(savefile, &this->actualY, 4);
  savefile->Write(savefile, &this->childID, 4);
  savefile->Write(savefile, &this->flags, 4);
  savefile->Write(savefile, &this->lastTimeRun, 4);
  savefile->Write(savefile, &this->drawRect, 16);
  savefile->Write(savefile, &this->clientRect, 16);
  savefile->Write(savefile, &this->origin, 8);
  savefile->Write(savefile, &this->timeLine, 4);
  savefile->Write(savefile, &this->xOffset, 4);
  savefile->Write(savefile, &this->yOffset, 4);
  savefile->Write(savefile, &this->cursor, 1);
  savefile->Write(savefile, &this->forceAspectWidth, 4);
  savefile->Write(savefile, &this->forceAspectHeight, 4);
  savefile->Write(savefile, &this->matScalex, 4);
  savefile->Write(savefile, &this->matScaley, 4);
  savefile->Write(savefile, &this->borderSize, 4);
  savefile->Write(savefile, &this->textAlign, 1);
  savefile->Write(savefile, &this->textAlignx, 4);
  savefile->Write(savefile, &this->textAligny, 4);
  savefile->Write(savefile, &this->textStyle, 1);
  savefile->Write(savefile, &this->textSpacing, 4);
  savefile->Write(savefile, &this->shear, 8);
  v8 = this->name.data;
  v9 = savefile->__vftable;
  num = strlen(v8);
  v9->Write(savefile, &num, 4);
  savefile->Write(savefile, v8, num);
  v10 = this->comment.data;
  v11 = savefile->__vftable;
  num = strlen(v10);
  v11->Write(savefile, &num, 4);
  savefile->Write(savefile, v10, num);
  this->noTime.WriteToSaveGame(&this->noTime, savefile);
  this->visible.WriteToSaveGame(&this->visible, savefile);
  this->rect.WriteToSaveGame(&this->rect, savefile);
  this->backColor.WriteToSaveGame(&this->backColor, savefile);
  this->matColor.WriteToSaveGame(&this->matColor, savefile);
  this->foreColor.WriteToSaveGame(&this->foreColor, savefile);
  this->hoverColor.WriteToSaveGame(&this->hoverColor, savefile);
  this->borderColor.WriteToSaveGame(&this->borderColor, savefile);
  this->textScale.WriteToSaveGame(&this->textScale, savefile);
  this->noEvents.WriteToSaveGame(&this->noEvents, savefile);
  this->rotate.WriteToSaveGame(&this->rotate, savefile);
  this->text.WriteToSaveGame(&this->text, savefile);
  this->backGroundName.WriteToSaveGame(&this->backGroundName, savefile);
  this->hideCursor.WriteToSaveGame(&this->hideCursor, savefile);
  for ( i = 0; i < this->definedVars.num; ++i )
  {
    v13 = this->definedVars.list[i];
    v13->WriteToSaveGame(v13, savefile);
  }
  savefile->Write(savefile, &this->textRect, 16);
  focusedChild = this->focusedChild;
  if ( focusedChild )
    winID = focusedChild->childID;
  else
    winID = -1;
  savefile->Write(savefile, &winID, 4);
  captureChild = this->captureChild;
  if ( captureChild )
    winID = captureChild->childID;
  else
    winID = -1;
  savefile->Write(savefile, &winID, 4);
  overChild = this->overChild;
  if ( overChild )
    winID = overChild->childID;
  else
    winID = -1;
  savefile->Write(savefile, &winID, 4);
  scripts = this->scripts;
  v18 = 28;
  do
  {
    if ( *scripts )
      idGuiScriptList::WriteToSaveGame(*scripts, savefile);
    ++scripts;
    --v18;
  }
  while ( v18 );
  for ( j = 0; j < this->timeLineEvents.num; ++j )
  {
    v20 = this->timeLineEvents.list[j];
    if ( v20 )
    {
      savefile->Write(savefile, &v20->pending, 1);
      savefile->Write(savefile, this->timeLineEvents.list[j], 4);
      event = this->timeLineEvents.list[j]->event;
      if ( event )
        idGuiScriptList::WriteToSaveGame(event, savefile);
    }
  }
  retaddr = this->transitions.num;
  ((void (__thiscall *)(idFile *, int *))savefile->Write)(savefile, &retaddr);
  v22 = 0;
  if ( this->transitions.num > 0 )
  {
    v23 = 0;
    do
    {
      idWindow::WriteSaveGameTransition(this, &this->transitions.list[v23], savefile);
      ++v22;
      ++v23;
    }
    while ( v22 < this->transitions.num );
  }
  for ( k = 0; k < this->namedEvents.num; ++k )
  {
    v25 = this->namedEvents.list[k];
    if ( v25 )
    {
      v26 = v25->mName.data;
      v27 = strlen(v26);
      v28 = savefile->__vftable;
      v34 = v27;
      v28->Write(savefile, &v34, 4);
      savefile->Write(savefile, v26, v34);
      mEvent = this->namedEvents.list[k]->mEvent;
      if ( mEvent )
        idGuiScriptList::WriteToSaveGame(mEvent, savefile);
    }
  }
  idRegisterList::WriteToSaveGame(&this->regList, savefile);
  for ( m = 0; m < this->drawWindows.num; ++m )
  {
    list = this->drawWindows.list;
    win = list[m].win;
    simp = list[m].simp;
    if ( simp )
    {
      simp->WriteToSaveGame(simp, savefile);
    }
    else if ( win )
    {
      win->WriteToSaveGame(win, savefile);
    }
  }
}

// FUNC: public: void __thiscall idWindow::ReadSaveGameString(class idStr &,class idFile *)
void __thiscall idWindow::ReadSaveGameString(idWindow *this, idStr *string, idFile *savefile)
{
  idFile *v3; // ebx
  idFile *v4; // edi

  v3 = savefile;
  savefile->Read(savefile, &savefile, 4);
  v4 = savefile;
  if ( (int)savefile < 0 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "idWindow::ReadSaveGameString: invalid length");
    v4 = savefile;
  }
  if ( (int)&v4->__vftable + 1 > string->alloced )
    idStr::ReAllocate(string, (int)&v4->__vftable + 1, 1);
  string->len = (int)v4;
  memset(string->data, 0x20u, (unsigned int)v4);
  string->data[string->len] = 0;
  v3->Read(v3, string->data, (int)savefile);
}

// FUNC: public: int __thiscall idWindow::NumTransitions(void)
int __thiscall idWindow::NumTransitions(idWindow *this)
{
  int num; // ebx
  int i; // esi
  int v4; // eax

  num = this->transitions.num;
  for ( i = 0; i < this->children.num; num += v4 )
    v4 = idWindow::NumTransitions(this->children.list[i++]);
  return num;
}

// FUNC: public: void __thiscall idWindow::FixupTransitions(void)
void __thiscall idWindow::FixupTransitions(idWindow *this)
{
  int v2; // edi
  int v3; // ebx
  idUserInterfaceLocal *gui; // esi
  idWindow *v5; // eax
  drawWin_t *ChildByName; // eax
  idWinVar *data; // ecx
  drawWin_t *v8; // esi
  idWindow *win; // edx
  idSimpleWindow *simp; // esi
  idTransitionData *v11; // edx
  int v12; // eax
  idWinVar *p_rect; // esi
  idTransitionData *list; // ecx
  int offset; // eax
  idTransitionData *v16; // ecx
  idWinVar *v17; // eax
  int v18; // ecx
  idWinVar *v19; // edx
  int num; // eax
  bool v21; // cc
  int v22; // eax
  int v23; // edx
  int j; // esi
  const char *v25; // [esp-8h] [ebp-1Ch]
  int c; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  v2 = 0;
  c = this->transitions.num;
  i = 0;
  if ( c > 0 )
  {
    v3 = 0;
    do
    {
      gui = this->gui;
      v25 = this->transitions.list[v3].data->c_str(this->transitions.list[v3].data);
      v5 = gui->GetDesktop(gui);
      ChildByName = idWindow::FindChildByName(v5, v25);
      data = this->transitions.list[v3].data;
      v8 = ChildByName;
      if ( data )
        ((void (__thiscall *)(idWinVar *, int))data->~idWinVar)(data, 1);
      this->transitions.list[v3].data = 0;
      if ( !v8 )
        goto LABEL_37;
      win = v8->win;
      if ( v8->win )
      {
        list = this->transitions.list;
        offset = list[v3].offset;
        v16 = &list[v3];
        switch ( offset )
        {
          case 284:
            v16->data = &win->rect;
            break;
          case 316:
            v16->data = &win->backColor;
            break;
          case 348:
            v16->data = &win->matColor;
            break;
          case 380:
            v16->data = &win->foreColor;
            break;
          case 444:
            v16->data = &win->borderColor;
            break;
          case 476:
            v16->data = &win->textScale;
            break;
          case 496:
            v16->data = &win->rotate;
            break;
        }
        goto LABEL_37;
      }
      simp = v8->simp;
      if ( simp )
      {
        v11 = this->transitions.list;
        v12 = v11[v3].offset;
        switch ( v12 )
        {
          case 208:
            p_rect = &simp->rect;
LABEL_36:
            v11[v3].data = p_rect;
            break;
          case 240:
            p_rect = &simp->backColor;
            goto LABEL_36;
          case 272:
            p_rect = &simp->matColor;
            goto LABEL_36;
          case 304:
            p_rect = &simp->foreColor;
            goto LABEL_36;
          case 336:
            p_rect = &simp->borderColor;
            goto LABEL_36;
          case 368:
            p_rect = &simp->textScale;
            goto LABEL_36;
          case 388:
            p_rect = &simp->rotate;
            goto LABEL_36;
        }
      }
LABEL_37:
      if ( this->transitionSubs.list[v2] != -1 )
      {
        v17 = (idWinVar *)Memory::Allocate(0x18u);
        if ( v17 )
        {
          v18 = this->transitionSubs.list[v2];
          v19 = this->transitions.list[v3].data;
          v17->guiDict = 0;
          v17->name = 0;
          v17->eval = 1;
          v17->__vftable = (idWinVar_vtbl *)&idWinFloatMember::`vftable';
          v17[1].__vftable = (idWinVar_vtbl *)v19;
          v17[1].guiDict = (idDict *)v18;
        }
        else
        {
          v17 = 0;
        }
        this->transitions.list[v3].data = v17;
      }
      if ( !this->transitions.list[v3].data )
      {
        if ( v2 >= 0 )
        {
          num = this->transitions.num;
          if ( v2 < num )
          {
            v21 = v2 < num - 1;
            this->transitions.num = num - 1;
            v22 = v2;
            if ( v21 )
            {
              v23 = v3 * 136;
              do
              {
                ++v22;
                qmemcpy(
                  (char *)this->transitions.list + v23,
                  (char *)&this->transitions.list[1] + v23,
                  sizeof(idTransitionData));
                v23 += 136;
              }
              while ( v22 < this->transitions.num );
              v2 = i;
            }
          }
        }
        --v2;
        --v3;
        --c;
      }
      ++v2;
      ++v3;
      i = v2;
    }
    while ( v2 < c );
  }
  for ( j = 0; j < this->children.num; ++j )
    idWindow::FixupTransitions(this->children.list[j]);
  if ( this->transitionSubs.list )
    Memory::Free(this->transitionSubs.list);
  this->transitionSubs.list = 0;
  this->transitionSubs.num = 0;
  this->transitionSubs.size = 0;
}

// FUNC: public: void __thiscall idWindow::FixupParms(void)
void __thiscall idWindow::FixupParms(idWindow *this)
{
  int num; // ebx
  int i; // edi
  idGuiScriptList **scripts; // edi
  int v5; // ebx
  int v6; // ebx
  int j; // edi
  int v8; // ebx
  int k; // edi
  int v10; // edi
  wexpOp_t *v11; // eax
  char *a; // ebx
  idWinVar *v13; // ebp
  int v14; // [esp+Ch] [ebp-4h]

  num = this->children.num;
  for ( i = 0; i < num; ++i )
    idWindow::FixupParms(this->children.list[i]);
  scripts = this->scripts;
  v5 = 28;
  do
  {
    if ( *scripts )
      idGuiScriptList::FixupParms(*scripts, this);
    ++scripts;
    --v5;
  }
  while ( v5 );
  v6 = this->timeLineEvents.num;
  for ( j = 0; j < v6; ++j )
    idGuiScriptList::FixupParms(this->timeLineEvents.list[j]->event, this);
  v8 = this->namedEvents.num;
  for ( k = 0; k < v8; ++k )
    idGuiScriptList::FixupParms(this->namedEvents.list[k]->mEvent, this);
  if ( this->ops.num > 0 )
  {
    v10 = 0;
    v14 = this->ops.num;
    do
    {
      v11 = &this->ops.list[v10];
      if ( v11->b == -2 )
      {
        a = (char *)v11->a;
        v13 = this->GetWinVarByName(this, a, 1, 0);
        Memory::Free(a);
        this->ops.list[v10].a = (int)v13;
        this->ops.list[v10].b = -1;
      }
      ++v10;
      --v14;
    }
    while ( v14 );
  }
  if ( (this->flags & 0x10000000) != 0 )
    idWindow::CalcRects(this, 0.0, 0.0);
}

// FUNC: protected: bool __thiscall idWindow::IsSimple(void)
bool __thiscall idWindow::IsSimple(idWindow *this)
{
  int v2; // eax
  idGuiScriptList **i; // ecx

  v2 = (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 4);
  if ( !v2 && !this->ops.num && (this->flags & 0x180) == 0 && !this->children.num && !this->drawWindows.num )
  {
    for ( i = this->scripts; !*i; ++i )
    {
      if ( ++v2 >= 28 )
        return !this->timeLineEvents.num
            && !this->namedEvents.num
            && LODWORD(this->forceAspectWidth) == 1142947840
            && LODWORD(this->forceAspectHeight) == 1139802112;
    }
  }
  return 0;
}

// FUNC: public: bool __thiscall idWindow::Interactive(void)
char __thiscall idWindow::Interactive(idWindow *this)
{
  int num; // edi
  int v4; // esi

  if ( this->scripts[2] )
    return 1;
  num = this->children.num;
  v4 = 0;
  if ( num <= 0 )
    return 0;
  while ( !idWindow::Interactive(this->children.list[v4]) )
  {
    if ( ++v4 >= num )
      return 0;
  }
  return 1;
}

// FUNC: public: void __thiscall idWindow::SetChildWinVarVal(char const *,char const *,char const *)
void __thiscall idWindow::SetChildWinVarVal(idWindow *this, const char *name, char *var, const char *val)
{
  drawWin_t *ChildByName; // eax
  idSimpleWindow *simp; // ecx
  idWinVar *WinVarByName; // eax
  idWinVar *v7; // esi

  ChildByName = idWindow::FindChildByName(this, name);
  if ( ChildByName )
  {
    simp = ChildByName->simp;
    if ( simp )
    {
      WinVarByName = idSimpleWindow::GetWinVarByName(simp, var);
    }
    else
    {
      if ( !ChildByName->win )
        return;
      WinVarByName = ChildByName->win->GetWinVarByName(ChildByName->win, var, 0, 0);
    }
    v7 = WinVarByName;
    if ( WinVarByName )
    {
      WinVarByName->Set(WinVarByName, val);
      v7->SetEval(v7, 0);
    }
  }
}

// FUNC: public: int __thiscall idWindow::GetChildCount(void)
int __thiscall idWindow::GetChildCount(idWindow *this)
{
  return this->drawWindows.num;
}

// FUNC: public: class idWindow * __thiscall idWindow::GetChild(int)
idWindow *__thiscall idWindow::GetChild(idWindow *this, int index)
{
  return this->drawWindows.list[index].win;
}

// FUNC: public: int __thiscall idWindow::GetChildIndex(class idWindow *)
int __thiscall idWindow::GetChildIndex(idWindow *this, idWindow *window)
{
  int num; // edx
  int result; // eax
  drawWin_t *i; // ecx

  num = this->drawWindows.num;
  result = 0;
  if ( num <= 0 )
    return -1;
  for ( i = this->drawWindows.list; i->win != window; ++i )
  {
    if ( ++result >= num )
      return -1;
  }
  return result;
}

// FUNC: private: virtual char const * __thiscall rvWindowEditLocal::GetScriptName(int)const
const char *__thiscall rvWindowEditLocal::GetScriptName(rvWindowEditLocal *this, int index)
{
  return idWindow::ScriptNames[index];
}

// FUNC: private: virtual int __thiscall rvWindowEditLocal::GetChildCount(class idWindow *)const
int __thiscall rvWindowEditLocal::GetChildCount(rvWindowEditLocal *this, idWindow *edit)
{
  return edit->drawWindows.num;
}

// FUNC: public: void __thiscall idWindow::CommonInit(void)
void __thiscall idWindow::CommonInit(idWindow *this)
{
  int v2; // eax
  char v3; // cl
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // edi
  idDict *v8; // ebp
  const char *v9; // eax
  bool other; // [esp+Fh] [ebp-41h] BYREF
  float v11; // [esp+10h] [ebp-40h] BYREF
  idVec4 v12; // [esp+14h] [ebp-3Ch] BYREF
  idStr v13; // [esp+24h] [ebp-2Ch] BYREF
  int v14; // [esp+4Ch] [ebp-4h]

  this->childID = 0;
  this->flags = 0;
  this->lastTimeRun = 0;
  this->origin.y = 0.0;
  this->origin.x = 0.0;
  this->matScalex = 1.0;
  this->matScaley = 1.0;
  this->fontNum = 0;
  this->timeLine = -1;
  this->yOffset = 0.0;
  this->xOffset = 0.0;
  this->cursor = 0;
  this->forceAspectWidth = 640.0;
  this->forceAspectHeight = 480.0;
  this->borderSize = 0.0;
  other = 0;
  idWinBool::operator=(&this->noTime, &other);
  other = 1;
  idWinBool::operator=(&this->visible, &other);
  this->textAlign = 0;
  this->textAlignx = 0.0;
  this->textAligny = 0.0;
  this->textStyle = 0;
  this->textSpacing = 0.0;
  other = 0;
  idWinBool::operator=(&this->noEvents, &other);
  v11 = 0.0;
  idWinFloat::operator=(&this->rotate, &v11);
  this->shear.y = 0.0;
  this->shear.x = 0.0;
  v11 = 0.34999999;
  idWinFloat::operator=(&this->textScale, &v11);
  idWinVec4::Zero(&this->backColor);
  v12.x = 1.0;
  v12.y = 1.0;
  v12.z = 1.0;
  v12.w = 1.0;
  idWinVec4::operator=(&this->foreColor, &v12);
  v12.x = 1.0;
  v12.y = 1.0;
  v12.z = 1.0;
  v12.w = 1.0;
  idWinVec4::operator=(&this->hoverColor, &v12);
  v12.x = 1.0;
  v12.y = 1.0;
  v12.z = 1.0;
  v12.w = 1.0;
  idWinVec4::operator=(&this->matColor, &v12);
  idWinVec4::Zero(&this->borderColor);
  this->background = 0;
  v13.alloced = 20;
  v13.data = v13.baseBuffer;
  v13.baseBuffer[0] = 0;
  v2 = 0;
  do
  {
    v3 = *(&entityFilter + v2);
    v13.baseBuffer[v2++] = v3;
  }
  while ( v3 );
  v13.len = 0;
  v14 = 0;
  idWinBackground::operator=(&this->backGroundName, &v13);
  v14 = -1;
  idStr::FreeData(&v13);
  this->focusedChild = 0;
  this->captureChild = 0;
  this->overChild = 0;
  this->parent = 0;
  this->startChildSearch = 0;
  this->saveOps = 0;
  this->saveRegs = 0;
  this->timeLine = -1;
  this->textStyle = 0;
  this->currentChild = 0;
  this->hover = 0;
  this->scripts[0] = 0;
  this->scripts[1] = 0;
  this->scripts[2] = 0;
  this->scripts[3] = 0;
  this->scripts[4] = 0;
  this->scripts[5] = 0;
  this->scripts[6] = 0;
  this->scripts[7] = 0;
  this->scripts[8] = 0;
  this->scripts[9] = 0;
  this->scripts[10] = 0;
  this->scripts[11] = 0;
  this->scripts[12] = 0;
  this->scripts[13] = 0;
  this->scripts[14] = 0;
  this->scripts[15] = 0;
  this->scripts[16] = 0;
  this->scripts[17] = 0;
  this->scripts[18] = 0;
  this->scripts[19] = 0;
  this->scripts[20] = 0;
  this->scripts[21] = 0;
  this->scripts[22] = 0;
  this->scripts[23] = 0;
  this->scripts[24] = 0;
  this->scripts[25] = 0;
  this->scripts[26] = 0;
  this->scripts[27] = 0;
  guiDict = this->hideCursor.guiDict;
  this->hideCursor.data = 0;
  if ( guiDict )
  {
    name = this->hideCursor.name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->hideCursor.name;
        goto LABEL_10;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_10:
        v8 = this->hideCursor.guiDict;
        v9 = va("%i", this->hideCursor.data);
        idDict::Set(v8, data, v9);
        goto LABEL_11;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_10;
  }
LABEL_11:
  if ( this->transitionSubs.list )
    Memory::Free(this->transitionSubs.list);
  this->transitionSubs.list = 0;
  this->transitionSubs.num = 0;
  this->transitionSubs.size = 0;
}

// FUNC: public: __thiscall idWindow::idWindow(class idUserInterfaceLocal *)
void __thiscall idWindow::idWindow(idWindow *this, idUserInterfaceLocal *ui)
{
  idRegisterList *p_regList; // edi
  idHashIndex *p_regHash; // ebp
  idRegister **list; // eax
  int v6; // ecx
  bool v7; // cc
  int v8; // eax
  int i; // [esp+10h] [ebp-1Ch]
  idRegister **ptr; // [esp+14h] [ebp-18h]

  this->__vftable = (idWindow_vtbl *)&idWindow::`vftable';
  this->cmd.len = 0;
  this->cmd.alloced = 20;
  this->cmd.data = this->cmd.baseBuffer;
  this->cmd.baseBuffer[0] = 0;
  this->drawRect.h = 0.0;
  this->drawRect.w = 0.0;
  this->drawRect.y = 0.0;
  this->drawRect.x = 0.0;
  this->clientRect.h = 0.0;
  this->clientRect.w = 0.0;
  this->clientRect.y = 0.0;
  this->clientRect.x = 0.0;
  this->name.len = 0;
  this->name.alloced = 20;
  this->name.data = this->name.baseBuffer;
  this->name.baseBuffer[0] = 0;
  this->comment.len = 0;
  this->comment.alloced = 20;
  this->comment.data = this->comment.baseBuffer;
  this->comment.baseBuffer[0] = 0;
  this->noTime.guiDict = 0;
  this->noTime.name = 0;
  this->noTime.eval = 1;
  this->noTime.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->visible.guiDict = 0;
  this->visible.name = 0;
  this->visible.eval = 1;
  this->visible.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->noEvents.guiDict = 0;
  this->noEvents.name = 0;
  this->noEvents.eval = 1;
  this->noEvents.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->rect.guiDict = 0;
  this->rect.name = 0;
  this->rect.eval = 1;
  this->rect.__vftable = (idWinRectangle_vtbl *)&idWinRectangle::`vftable';
  this->rect.data.h = 0.0;
  this->rect.data.w = 0.0;
  this->rect.data.y = 0.0;
  this->rect.data.x = 0.0;
  this->backColor.guiDict = 0;
  this->backColor.name = 0;
  this->backColor.eval = 1;
  this->backColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->matColor.guiDict = 0;
  this->matColor.name = 0;
  this->matColor.eval = 1;
  this->matColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->foreColor.guiDict = 0;
  this->foreColor.name = 0;
  this->foreColor.eval = 1;
  this->foreColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->hoverColor.guiDict = 0;
  this->hoverColor.name = 0;
  this->hoverColor.eval = 1;
  this->hoverColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->borderColor.guiDict = 0;
  this->borderColor.name = 0;
  this->borderColor.eval = 1;
  this->borderColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->textScale.guiDict = 0;
  this->textScale.name = 0;
  this->textScale.eval = 1;
  this->textScale.__vftable = (idWinFloat_vtbl *)&idWinFloat::`vftable';
  this->rotate.guiDict = 0;
  this->rotate.name = 0;
  this->rotate.eval = 1;
  this->rotate.__vftable = (idWinFloat_vtbl *)&idWinFloat::`vftable';
  this->text.guiDict = 0;
  this->text.name = 0;
  this->text.eval = 1;
  this->text.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->text.data.len = 0;
  this->text.data.alloced = 20;
  this->text.data.data = this->text.data.baseBuffer;
  this->text.data.baseBuffer[0] = 0;
  this->backGroundName.guiDict = 0;
  this->backGroundName.name = 0;
  this->backGroundName.eval = 1;
  this->backGroundName.data.len = 0;
  this->backGroundName.data.alloced = 20;
  this->backGroundName.data.data = this->backGroundName.data.baseBuffer;
  this->backGroundName.data.baseBuffer[0] = 0;
  this->backGroundName.__vftable = (idWinBackground_vtbl *)&idWinBackground::`vftable';
  this->backGroundName.data.len = 0;
  this->backGroundName.data.alloced = 20;
  this->backGroundName.data.data = this->backGroundName.data.baseBuffer;
  this->backGroundName.data.baseBuffer[0] = 0;
  this->backGroundName.mat = 0;
  this->definedVars.granularity = 16;
  this->definedVars.list = 0;
  this->definedVars.num = 0;
  this->definedVars.size = 0;
  this->updateVars.granularity = 16;
  this->updateVars.list = 0;
  this->updateVars.num = 0;
  this->updateVars.size = 0;
  this->textRect.h = 0.0;
  this->textRect.w = 0.0;
  this->textRect.y = 0.0;
  this->textRect.x = 0.0;
  this->children.granularity = 16;
  this->children.list = 0;
  this->children.num = 0;
  this->children.size = 0;
  this->drawWindows.granularity = 16;
  this->drawWindows.list = 0;
  this->drawWindows.num = 0;
  this->drawWindows.size = 0;
  this->timeLineEvents.granularity = 16;
  this->timeLineEvents.list = 0;
  this->timeLineEvents.num = 0;
  this->timeLineEvents.size = 0;
  this->transitions.granularity = 16;
  this->transitions.list = 0;
  this->transitions.num = 0;
  this->transitions.size = 0;
  this->ops.granularity = 16;
  this->ops.list = 0;
  this->ops.num = 0;
  this->ops.size = 0;
  this->expressionRegisters.granularity = 16;
  this->expressionRegisters.list = 0;
  this->expressionRegisters.num = 0;
  this->expressionRegisters.size = 0;
  this->namedEvents.granularity = 16;
  this->namedEvents.list = 0;
  this->namedEvents.num = 0;
  this->namedEvents.size = 0;
  this->transitionSubs.granularity = 16;
  this->transitionSubs.list = 0;
  this->transitionSubs.num = 0;
  this->transitionSubs.size = 0;
  p_regList = &this->regList;
  this->regList.regs.granularity = 16;
  this->regList.regs.list = 0;
  this->regList.regs.num = 0;
  this->regList.regs.size = 0;
  p_regHash = &this->regList.regHash;
  idHashIndex::Init(&this->regList.regHash, 1024, 1024);
  list = p_regList->regs.list;
  p_regList->regs.granularity = 4;
  ptr = list;
  if ( list )
  {
    v6 = p_regList->regs.num + 3 - (p_regList->regs.num + 3) % 4;
    if ( v6 != p_regList->regs.size )
    {
      if ( v6 > 0 )
      {
        v7 = v6 < p_regList->regs.num;
        p_regList->regs.size = v6;
        if ( v7 )
          p_regList->regs.num = v6;
        p_regList->regs.list = (idRegister **)Memory::Allocate(4 * v6);
        v8 = 0;
        for ( i = 0; i < p_regList->regs.num; ++i )
        {
          p_regList->regs.list[i] = ptr[v8];
          v8 = i + 1;
        }
        if ( ptr )
          Memory::Free(ptr);
      }
      else
      {
        Memory::Free(list);
        p_regList->regs.list = 0;
        p_regList->regs.num = 0;
        p_regList->regs.size = 0;
      }
    }
  }
  p_regList->regHash.granularity = 4;
  idHashIndex::Free(p_regHash);
  p_regHash->hashSize = 32;
  p_regHash->indexSize = 4;
  this->hideCursor.guiDict = 0;
  this->hideCursor.name = 0;
  this->hideCursor.eval = 1;
  this->hideCursor.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->dc = 0;
  this->gui = ui;
  idWindow::CommonInit(this);
}

// FUNC: public: __thiscall idWindow::idWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idWindow::idWindow(idWindow *this, idDeviceContext *d, idUserInterfaceLocal *ui)
{
  idRegisterList *p_regList; // edi
  idHashIndex *p_regHash; // ebp
  idRegister **list; // eax
  int v7; // ecx
  bool v8; // cc
  int v9; // eax
  int i; // [esp+10h] [ebp-1Ch]
  idRegister **ptr; // [esp+14h] [ebp-18h]

  this->__vftable = (idWindow_vtbl *)&idWindow::`vftable';
  this->cmd.len = 0;
  this->cmd.alloced = 20;
  this->cmd.data = this->cmd.baseBuffer;
  this->cmd.baseBuffer[0] = 0;
  this->drawRect.h = 0.0;
  this->drawRect.w = 0.0;
  this->drawRect.y = 0.0;
  this->drawRect.x = 0.0;
  this->clientRect.h = 0.0;
  this->clientRect.w = 0.0;
  this->clientRect.y = 0.0;
  this->clientRect.x = 0.0;
  this->name.len = 0;
  this->name.alloced = 20;
  this->name.data = this->name.baseBuffer;
  this->name.baseBuffer[0] = 0;
  this->comment.len = 0;
  this->comment.alloced = 20;
  this->comment.data = this->comment.baseBuffer;
  this->comment.baseBuffer[0] = 0;
  this->noTime.guiDict = 0;
  this->noTime.name = 0;
  this->noTime.eval = 1;
  this->noTime.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->visible.guiDict = 0;
  this->visible.name = 0;
  this->visible.eval = 1;
  this->visible.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->noEvents.guiDict = 0;
  this->noEvents.name = 0;
  this->noEvents.eval = 1;
  this->noEvents.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->rect.guiDict = 0;
  this->rect.name = 0;
  this->rect.eval = 1;
  this->rect.__vftable = (idWinRectangle_vtbl *)&idWinRectangle::`vftable';
  this->rect.data.h = 0.0;
  this->rect.data.w = 0.0;
  this->rect.data.y = 0.0;
  this->rect.data.x = 0.0;
  this->backColor.guiDict = 0;
  this->backColor.name = 0;
  this->backColor.eval = 1;
  this->backColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->matColor.guiDict = 0;
  this->matColor.name = 0;
  this->matColor.eval = 1;
  this->matColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->foreColor.guiDict = 0;
  this->foreColor.name = 0;
  this->foreColor.eval = 1;
  this->foreColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->hoverColor.guiDict = 0;
  this->hoverColor.name = 0;
  this->hoverColor.eval = 1;
  this->hoverColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->borderColor.guiDict = 0;
  this->borderColor.name = 0;
  this->borderColor.eval = 1;
  this->borderColor.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->textScale.guiDict = 0;
  this->textScale.name = 0;
  this->textScale.eval = 1;
  this->textScale.__vftable = (idWinFloat_vtbl *)&idWinFloat::`vftable';
  this->rotate.guiDict = 0;
  this->rotate.name = 0;
  this->rotate.eval = 1;
  this->rotate.__vftable = (idWinFloat_vtbl *)&idWinFloat::`vftable';
  this->text.guiDict = 0;
  this->text.name = 0;
  this->text.eval = 1;
  this->text.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->text.data.len = 0;
  this->text.data.alloced = 20;
  this->text.data.data = this->text.data.baseBuffer;
  this->text.data.baseBuffer[0] = 0;
  this->backGroundName.guiDict = 0;
  this->backGroundName.name = 0;
  this->backGroundName.eval = 1;
  this->backGroundName.data.len = 0;
  this->backGroundName.data.alloced = 20;
  this->backGroundName.data.data = this->backGroundName.data.baseBuffer;
  this->backGroundName.data.baseBuffer[0] = 0;
  this->backGroundName.__vftable = (idWinBackground_vtbl *)&idWinBackground::`vftable';
  this->backGroundName.data.len = 0;
  this->backGroundName.data.alloced = 20;
  this->backGroundName.data.data = this->backGroundName.data.baseBuffer;
  this->backGroundName.data.baseBuffer[0] = 0;
  this->backGroundName.mat = 0;
  this->definedVars.granularity = 16;
  this->definedVars.list = 0;
  this->definedVars.num = 0;
  this->definedVars.size = 0;
  this->updateVars.granularity = 16;
  this->updateVars.list = 0;
  this->updateVars.num = 0;
  this->updateVars.size = 0;
  this->textRect.h = 0.0;
  this->textRect.w = 0.0;
  this->textRect.y = 0.0;
  this->textRect.x = 0.0;
  this->children.granularity = 16;
  this->children.list = 0;
  this->children.num = 0;
  this->children.size = 0;
  this->drawWindows.granularity = 16;
  this->drawWindows.list = 0;
  this->drawWindows.num = 0;
  this->drawWindows.size = 0;
  this->timeLineEvents.granularity = 16;
  this->timeLineEvents.list = 0;
  this->timeLineEvents.num = 0;
  this->timeLineEvents.size = 0;
  this->transitions.granularity = 16;
  this->transitions.list = 0;
  this->transitions.num = 0;
  this->transitions.size = 0;
  this->ops.granularity = 16;
  this->ops.list = 0;
  this->ops.num = 0;
  this->ops.size = 0;
  this->expressionRegisters.granularity = 16;
  this->expressionRegisters.list = 0;
  this->expressionRegisters.num = 0;
  this->expressionRegisters.size = 0;
  this->namedEvents.granularity = 16;
  this->namedEvents.list = 0;
  this->namedEvents.num = 0;
  this->namedEvents.size = 0;
  this->transitionSubs.granularity = 16;
  this->transitionSubs.list = 0;
  this->transitionSubs.num = 0;
  this->transitionSubs.size = 0;
  p_regList = &this->regList;
  this->regList.regs.granularity = 16;
  this->regList.regs.list = 0;
  this->regList.regs.num = 0;
  this->regList.regs.size = 0;
  p_regHash = &this->regList.regHash;
  idHashIndex::Init(&this->regList.regHash, 1024, 1024);
  list = p_regList->regs.list;
  p_regList->regs.granularity = 4;
  ptr = list;
  if ( list )
  {
    v7 = p_regList->regs.num + 3 - (p_regList->regs.num + 3) % 4;
    if ( v7 != p_regList->regs.size )
    {
      if ( v7 > 0 )
      {
        v8 = v7 < p_regList->regs.num;
        p_regList->regs.size = v7;
        if ( v8 )
          p_regList->regs.num = v7;
        p_regList->regs.list = (idRegister **)Memory::Allocate(4 * v7);
        v9 = 0;
        for ( i = 0; i < p_regList->regs.num; ++i )
        {
          p_regList->regs.list[i] = ptr[v9];
          v9 = i + 1;
        }
        if ( ptr )
          Memory::Free(ptr);
      }
      else
      {
        Memory::Free(list);
        p_regList->regs.list = 0;
        p_regList->regs.num = 0;
        p_regList->regs.size = 0;
      }
    }
  }
  p_regList->regHash.granularity = 4;
  idHashIndex::Free(p_regHash);
  p_regHash->hashSize = 32;
  p_regHash->indexSize = 4;
  this->hideCursor.guiDict = 0;
  this->hideCursor.name = 0;
  this->hideCursor.eval = 1;
  this->hideCursor.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->gui = ui;
  this->dc = d;
  idWindow::CommonInit(this);
}

// FUNC: public: virtual void __thiscall idWindow::Activate(bool,class idStr &)
void __thiscall idWindow::Activate(idWindow *this, BOOL activate, idStr *act)
{
  int num; // ebx
  int i; // edi
  idWinVar *v6; // ecx
  int v7; // ebx
  int j; // ebp
  idWindow *v9; // ecx
  int len; // eax
  int v11; // esi
  int v12; // eax
  int v13; // eax
  char v14; // cl
  char *data; // eax

  num = this->updateVars.num;
  for ( i = 0; i < num; ++i )
  {
    v6 = this->updateVars.list[i];
    v6->Update(v6);
  }
  this->RunScript(this, 5 - activate);
  v7 = this->children.num;
  for ( j = 0; j < v7; ++j )
  {
    v9 = this->children.list[j];
    v9->Activate(v9, activate, act);
  }
  len = act->len;
  if ( act->len )
  {
    v11 = len + 3;
    v12 = len + 4;
    if ( v12 > act->alloced )
      idStr::ReAllocate(act, v12, 1);
    v13 = 0;
    v14 = 32;
    do
    {
      ++v13;
      act->data[act->len - 1 + v13] = v14;
      v14 = asc_102D104C[v13];
    }
    while ( v14 );
    data = act->data;
    act->len = v11;
    data[v11] = 0;
  }
}

// FUNC: public: void __thiscall idWindow::AddUpdateVar(class idWinVar *)
void __thiscall idWindow::AddUpdateVar(idWindow *this, idWinVar *var)
{
  int num; // edx
  int v4; // eax
  idWinVar **list; // ecx
  int granularity; // eax
  int i; // eax
  int size; // eax
  int v9; // ebx
  int v10; // ecx
  idWinVar **v11; // edi
  int j; // eax

  num = this->updateVars.num;
  v4 = 0;
  if ( num <= 0 )
    goto LABEL_7;
  list = this->updateVars.list;
  while ( *list != var )
  {
    ++v4;
    ++list;
    if ( v4 >= this->updateVars.num )
      goto LABEL_7;
  }
  if ( v4 < 0 )
  {
LABEL_7:
    if ( !this->updateVars.list )
    {
      granularity = this->updateVars.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->updateVars.size )
        {
          this->updateVars.size = granularity;
          if ( granularity < num )
            this->updateVars.num = granularity;
          this->updateVars.list = (idWinVar **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->updateVars.num; ++i )
            this->updateVars.list[i] = *(idWinVar **)(4 * i);
        }
      }
      else
      {
        this->updateVars.list = 0;
        this->updateVars.num = 0;
        this->updateVars.size = 0;
      }
    }
    size = this->updateVars.size;
    v9 = this->updateVars.num;
    if ( v9 == size )
    {
      if ( !this->updateVars.granularity )
        this->updateVars.granularity = 16;
      v10 = size + this->updateVars.granularity - (size + this->updateVars.granularity) % this->updateVars.granularity;
      if ( v10 > 0 )
      {
        if ( v10 != this->updateVars.size )
        {
          v11 = this->updateVars.list;
          this->updateVars.size = v10;
          if ( v10 < v9 )
            this->updateVars.num = v10;
          this->updateVars.list = (idWinVar **)Memory::Allocate(4 * v10);
          for ( j = 0; j < this->updateVars.num; ++j )
            this->updateVars.list[j] = v11[j];
          if ( v11 )
            Memory::Free(v11);
        }
      }
      else
      {
        if ( this->updateVars.list )
          Memory::Free(this->updateVars.list);
        this->updateVars.list = 0;
        this->updateVars.num = 0;
        this->updateVars.size = 0;
      }
    }
    this->updateVars.list[this->updateVars.num++] = var;
  }
}

// FUNC: public: void __thiscall idWindow::AddCommand(char const *)
void __thiscall idWindow::AddCommand(idWindow *this, char *_cmd)
{
  int len; // esi
  idStr *p_cmd; // ebx
  char *data; // ecx
  char *v5; // edx
  char v6; // al
  int v7; // esi
  int v8; // eax
  char v9; // cl
  char *v10; // edx
  int v11; // esi
  char v12; // cl
  int i; // eax
  char *v14; // edx
  int v15; // ebp
  idStr str; // [esp+4h] [ebp-2Ch] BYREF
  int v17; // [esp+2Ch] [ebp-4h]

  if ( *_cmd )
  {
    len = this->cmd.len;
    p_cmd = &this->cmd;
    str.data = str.baseBuffer;
    str.len = 0;
    str.alloced = 20;
    str.baseBuffer[0] = 0;
    if ( len + 1 > 20 )
      idStr::ReAllocate(&str, len + 1, 1);
    data = p_cmd->data;
    v5 = str.data;
    do
    {
      v6 = *data;
      *v5++ = *data++;
    }
    while ( v6 );
    str.len = len;
    v17 = 0;
    if ( len )
    {
      v7 = len + 3;
      if ( v7 + 1 > str.alloced )
        idStr::ReAllocate(&str, v7 + 1, 1);
      v8 = 0;
      v9 = 32;
      do
      {
        v10 = &str.data[v8++];
        v10[str.len] = v9;
        v9 = asc_102D104C[v8];
      }
      while ( v9 );
      str.len = v7;
      str.data[v7] = 0;
      v11 = strlen(_cmd) + str.len;
      if ( v11 + 1 > str.alloced )
        idStr::ReAllocate(&str, v11 + 1, 1);
      v12 = *_cmd;
      for ( i = 0; v12; v12 = _cmd[i] )
      {
        v14 = &str.data[i++];
        v14[str.len] = v12;
      }
      str.len = v11;
      str.data[v11] = 0;
    }
    else
    {
      idStr::operator=(&str, _cmd);
    }
    v15 = str.len;
    if ( str.len + 1 > p_cmd->alloced )
      idStr::ReAllocate(p_cmd, str.len + 1, 0);
    qmemcpy(p_cmd->data, str.data, v15);
    p_cmd->data[v15] = 0;
    p_cmd->len = v15;
    v17 = -1;
    idStr::FreeData(&str);
  }
}

// FUNC: protected: void __thiscall idWindow::Time(void)
void __thiscall idWindow::Time(idWindow *this)
{
  idStr *p_cmd; // ebx
  int num; // ebp
  int i; // esi
  idTimeLineEvent *v5; // eax
  idGuiScriptList *event; // ecx
  idUserInterfaceLocal *gui; // esi
  idStr *p_pendingCmd; // esi
  int v9; // ebp
  int v10; // eax
  int v11; // eax
  char v12; // cl
  int v13; // edx
  char *data; // eax
  idUserInterfaceLocal *v15; // esi
  int v16; // edi
  idStr *v17; // esi
  int j; // eax
  char *v19; // edx
  idStr *v20; // [esp+4h] [ebp-4h]

  if ( !this->noTime.data )
  {
    if ( this->timeLine == -1 )
      this->timeLine = this->gui->time;
    p_cmd = &this->cmd;
    v20 = &this->cmd;
    idStr::operator=(&this->cmd, (char *)&entityFilter);
    num = this->timeLineEvents.num;
    if ( num > 0 )
    {
      for ( i = 0; i < num; ++i )
      {
        v5 = this->timeLineEvents.list[i];
        if ( v5->pending && this->gui->time - this->timeLine >= v5->time )
        {
          v5->pending = 0;
          event = this->timeLineEvents.list[i]->event;
          if ( event )
            idGuiScriptList::Execute(event, this);
        }
      }
    }
    gui = this->gui;
    if ( gui->active && p_cmd->len )
    {
      p_pendingCmd = &gui->pendingCmd;
      if ( p_pendingCmd->len )
      {
        v9 = p_pendingCmd->len + 1;
        v10 = p_pendingCmd->len + 2;
        if ( v10 > p_pendingCmd->alloced )
          idStr::ReAllocate(p_pendingCmd, v10, 1);
        v11 = 0;
        v12 = 32;
        do
        {
          v13 = v11 + p_pendingCmd->len;
          ++v11;
          p_pendingCmd->data[v13] = v12;
          v12 = src[v11];
        }
        while ( v12 );
        data = p_pendingCmd->data;
        p_cmd = v20;
        p_pendingCmd->len = v9;
        data[v9] = 0;
      }
      v15 = this->gui;
      v16 = v15->pendingCmd.len + p_cmd->len;
      v17 = &v15->pendingCmd;
      if ( v16 + 1 > v17->alloced )
        idStr::ReAllocate(v17, v16 + 1, 1);
      for ( j = 0; j < p_cmd->len; ++j )
        v17->data[v17->len + j] = p_cmd->data[j];
      v19 = v17->data;
      v17->len = v16;
      v19[v16] = 0;
    }
  }
}

// FUNC: public: float __thiscall idWindow::EvalRegs(int,bool)
double __thiscall idWindow::EvalRegs(idWindow *this, unsigned int test, bool force)
{
  bool v4; // zf

  if ( !force && test <= 0xFFF && lastEval == this )
    return regs[test];
  v4 = this->expressionRegisters.num == 0;
  lastEval = this;
  if ( !v4 )
  {
    idRegisterList::SetToRegs(&this->regList, regs);
    idWindow::EvaluateRegisters(this, regs);
    idRegisterList::GetFromRegs(&this->regList, regs);
  }
  if ( test > 0xFFF )
    return 0.0;
  else
    return regs[test];
}

// FUNC: public: void __thiscall idWindow::SetupTransforms(float,float)
void __thiscall idWindow::SetupTransforms(idWindow *this, float x, float y)
{
  unsigned int v4; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st6
  double data; // st7
  float *p_z; // eax
  int v10; // ecx
  double v11; // st6
  double v12; // st7
  float v13; // [esp+Ch] [ebp-4h]
  float ya; // [esp+18h] [ebp+8h]
  float yb; // [esp+18h] [ebp+8h]
  float yc; // [esp+18h] [ebp+8h]
  float yd; // [esp+18h] [ebp+8h]
  float ye; // [esp+18h] [ebp+8h]
  float yf; // [esp+18h] [ebp+8h]
  float yg; // [esp+18h] [ebp+8h]
  float yh; // [esp+18h] [ebp+8h]
  float yi; // [esp+18h] [ebp+8h]

  v4 = _S14_18;
  if ( (_S14_18 & 1) == 0 )
  {
    v4 = _S14_18 | 1;
    _S14_18 |= 1u;
  }
  if ( (v4 & 2) == 0 )
  {
    v4 |= 2u;
    _S14_18 = v4;
  }
  trans_0 = mat3_identity;
  v5 = y + this->origin.y;
  v6 = x + this->origin.x;
  org_0.z = 0.0;
  org_0.x = v6;
  org_0.y = v5;
  if ( this->rotate.data != 0.0 )
  {
    if ( (v4 & 4) == 0 )
    {
      v4 |= 4u;
      _S14_18 = v4;
    }
    if ( (v4 & 8) == 0 )
    {
      _S14_18 = v4 | 8;
      vec_0.x = 0.0;
      vec_0.y = 0.0;
      vec_0.z = 1.0;
    }
    v7 = v5;
    data = this->rotate.data;
    rot_0.origin.y = v7;
    rot_0.origin.x = org_0.x;
    rot_0.angle = data;
    rot_0.vec = vec_0;
    rot_0.origin.z = 0.0;
    rot_0.axisValid = 0;
    trans_0 = *idRotation::ToMat3(&rot_0);
    v4 = _S14_18;
  }
  if ( this->shear.x != 0.0 || this->shear.y != 0.0 )
  {
    if ( (v4 & 0x10) == 0 )
      _S14_18 = v4 | 0x10;
    smat_0 = mat3_identity;
    smat_0.mat[0].y = this->shear.x;
    smat_0.mat[1].x = this->shear.y;
    p_z = &trans_0.mat[0].z;
    v10 = 3;
    do
    {
      p_z += 3;
      --v10;
      v13 = smat_0.mat[1].z * *(p_z - 4) + smat_0.mat[2].z * *(p_z - 3) + smat_0.mat[0].z * *(p_z - 5);
      v11 = smat_0.mat[2].x * *(p_z - 3) + smat_0.mat[0].x * *(p_z - 5) + smat_0.mat[1].x * *(p_z - 4);
      v12 = smat_0.mat[1].y * *(p_z - 4) + smat_0.mat[2].y * *(p_z - 3) + smat_0.mat[0].y * *(p_z - 5);
      *(p_z - 3) = v13;
      *(p_z - 5) = v11;
      *(p_z - 4) = v12;
    }
    while ( v10 );
  }
  ya = trans_0.mat[0].x - mat3_identity.mat[0].x;
  if ( COERCE_FLOAT(LODWORD(ya) & 0x7FFFFFFF) > 0.000001 )
    goto LABEL_26;
  yb = trans_0.mat[0].y - mat3_identity.mat[0].y;
  if ( COERCE_FLOAT(LODWORD(yb) & 0x7FFFFFFF) > 0.000001
    || (yc = trans_0.mat[0].z - mat3_identity.mat[0].z, COERCE_FLOAT(LODWORD(yc) & 0x7FFFFFFF) > 0.000001)
    || (yd = trans_0.mat[1].x - mat3_identity.mat[1].x, COERCE_FLOAT(LODWORD(yd) & 0x7FFFFFFF) > 0.000001)
    || (ye = trans_0.mat[1].y - mat3_identity.mat[1].y, COERCE_FLOAT(LODWORD(ye) & 0x7FFFFFFF) > 0.000001)
    || (yf = trans_0.mat[1].z - mat3_identity.mat[1].z, COERCE_FLOAT(LODWORD(yf) & 0x7FFFFFFF) > 0.000001)
    || (yg = trans_0.mat[2].x - mat3_identity.mat[2].x, COERCE_FLOAT(LODWORD(yg) & 0x7FFFFFFF) > 0.000001)
    || (yh = trans_0.mat[2].y - mat3_identity.mat[2].y, COERCE_FLOAT(LODWORD(yh) & 0x7FFFFFFF) > 0.000001)
    || (yi = trans_0.mat[2].z - mat3_identity.mat[2].z, COERCE_FLOAT(LODWORD(yi) & 0x7FFFFFFF) > 0.000001) )
  {
LABEL_26:
    idDeviceContext::SetTransformInfo(this->dc, &org_0, &trans_0);
  }
}

// FUNC: public: virtual class idWinVar * __thiscall idWindow::GetWinVarByName(char const *,bool,struct drawWin_t * *)
idWinVar *__thiscall idWindow::GetWinVarByName(idWindow *this, char *_name, BOOL fixup, drawWin_t **owner)
{
  int v5; // eax
  const char *v6; // eax
  int v7; // edi
  int v8; // eax
  char *data; // edx
  char *v10; // ecx
  char v11; // al
  int v12; // edi
  int Text; // eax
  int num; // ebx
  idWinVar *v15; // ecx
  const char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *v18; // eax
  const char *v19; // eax
  idWinVar *v20; // ecx
  idDict *v21; // ecx
  const idKeyValue *v22; // eax
  idRegister *Reg; // eax
  idWindow *parent; // ecx
  idWinVar *v26; // eax
  idWinVar *v27; // ebx
  int granularity; // eax
  bool v29; // cc
  int i; // eax
  int v31; // ebp
  int size; // eax
  int v33; // ecx
  idWinVar **list; // edi
  int j; // eax
  int v36; // eax
  int v37; // edi
  idUserInterfaceLocal *gui; // ecx
  idUserInterfaceLocal_vtbl *v39; // edx
  idWindow *v40; // eax
  drawWin_t *ChildByName; // eax
  int v42; // esi
  idWinVar *WinVarByName; // esi
  int v44; // eax
  int v45; // edi
  char *v46; // edi
  idWinVar *v47; // ebp
  idWinVar *v48; // eax
  int v49; // eax
  int k; // eax
  int v51; // ebp
  int v52; // eax
  int v53; // ecx
  idWinVar **v54; // edi
  int m; // eax
  char *v56; // [esp-4h] [ebp-A8h]
  idWinVar *retVar; // [esp+10h] [ebp-94h]
  idWinVar *retVara; // [esp+10h] [ebp-94h]
  bool guiVar; // [esp+17h] [ebp-8Dh]
  idStr key; // [esp+18h] [ebp-8Ch] BYREF
  idStr temp; // [esp+38h] [ebp-6Ch] BYREF
  idStr var; // [esp+58h] [ebp-4Ch] BYREF
  idStr winName; // [esp+78h] [ebp-2Ch] BYREF
  int v64; // [esp+A0h] [ebp-4h]

  retVar = 0;
  if ( owner )
    *owner = 0;
  if ( !idStr::Icmp(_name, "notime") )
    retVar = &this->noTime;
  if ( !idStr::Icmp(_name, "background") )
    retVar = &this->backGroundName;
  if ( !idStr::Icmp(_name, "visible") )
    retVar = &this->visible;
  if ( !idStr::Icmp(_name, "rect") )
    retVar = &this->rect;
  if ( !idStr::Icmp(_name, "backColor") )
    retVar = &this->backColor;
  if ( !idStr::Icmp(_name, "matColor") )
    retVar = &this->matColor;
  if ( !idStr::Icmp(_name, "foreColor") )
    retVar = &this->foreColor;
  if ( !idStr::Icmp(_name, "hoverColor") )
    retVar = &this->hoverColor;
  if ( !idStr::Icmp(_name, "borderColor") )
    retVar = &this->borderColor;
  if ( !idStr::Icmp(_name, "textScale") )
    retVar = &this->textScale;
  if ( !idStr::Icmp(_name, "rotate") )
    retVar = &this->rotate;
  if ( !idStr::Icmp(_name, "noEvents") )
    retVar = &this->noEvents;
  if ( !idStr::Icmp(_name, "text") )
    retVar = &this->text;
  if ( !idStr::Icmp(_name, "backGroundName") )
    retVar = &this->backGroundName;
  if ( !idStr::Icmp(_name, "hidecursor") )
    retVar = &this->hideCursor;
  v5 = 0;
  key.len = 0;
  key.alloced = 20;
  key.data = key.baseBuffer;
  key.baseBuffer[0] = 0;
  if ( _name )
  {
    v6 = &_name[strlen(_name) + 1];
    v7 = v6 - (_name + 1);
    v8 = v6 - _name;
    if ( v8 > 20 )
      idStr::ReAllocate(&key, v8, 1);
    data = key.data;
    v10 = _name;
    do
    {
      v11 = *v10;
      *data++ = *v10++;
    }
    while ( v11 );
    v5 = v7;
    key.len = v7;
  }
  v12 = 0;
  v64 = 0;
  Text = idStr::FindText(key.data, VAR_GUIPREFIX_16, 1, 0, v5);
  num = this->definedVars.num;
  guiVar = Text >= 0;
  if ( num > 0 )
  {
    while ( 1 )
    {
      if ( guiVar )
      {
        v15 = this->definedVars.list[v12];
        name = v15->name;
        if ( !name )
          goto LABEL_46;
        guiDict = v15->guiDict;
        if ( guiDict && *name == 42 )
        {
          v18 = idDict::FindKey(guiDict, name + 1);
          if ( v18 )
          {
            v19 = va("%s", v18->value->data);
            goto LABEL_54;
          }
LABEL_46:
          name = &entityFilter;
        }
        v19 = va("%s", name);
        goto LABEL_54;
      }
      v20 = this->definedVars.list[v12];
      v19 = v20->name;
      if ( !v19 )
        goto LABEL_53;
      v21 = v20->guiDict;
      if ( v21 )
      {
        if ( *v19 == 42 )
          break;
      }
LABEL_54:
      if ( !idStr::Icmp(_name, v19) )
      {
        retVar = this->definedVars.list[v12];
        goto LABEL_58;
      }
      if ( ++v12 >= num )
        goto LABEL_58;
    }
    v22 = idDict::FindKey(v21, v19 + 1);
    if ( v22 )
    {
      v19 = v22->value->data;
      goto LABEL_54;
    }
LABEL_53:
    v19 = &entityFilter;
    goto LABEL_54;
  }
LABEL_58:
  if ( retVar )
  {
    if ( fixup )
    {
      if ( *_name != 36 )
      {
        Reg = idRegisterList::FindReg(&this->regList, _name);
        if ( Reg )
          Reg->enabled = 0;
      }
    }
    if ( owner )
    {
      parent = this->parent;
      if ( parent )
        *owner = idWindow::FindChildByName(parent, this->name.data);
    }
    v64 = -1;
    idStr::FreeData(&key);
    return retVar;
  }
  if ( key.len > 5 && guiVar )
  {
    v26 = (idWinVar *)Memory::Allocate(0x30u);
    if ( v26 )
    {
      v26->guiDict = 0;
      v26->name = 0;
      v26->eval = 1;
      v26->__vftable = (idWinVar_vtbl *)&idWinStr::`vftable';
      v26[1].__vftable = 0;
      v26[1].name = (char *)20;
      v26[1].guiDict = (idDict *)&v26[1].eval;
      v26[1].eval = 0;
      v27 = v26;
    }
    else
    {
      v27 = 0;
    }
    v27->Init(v27, _name, this);
    if ( !this->definedVars.list )
    {
      granularity = this->definedVars.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->definedVars.size )
        {
          v29 = granularity < this->definedVars.num;
          this->definedVars.size = granularity;
          if ( v29 )
            this->definedVars.num = granularity;
          this->definedVars.list = (idWinVar **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->definedVars.num; ++i )
            this->definedVars.list[i] = *(idWinVar **)(4 * i);
        }
      }
      else
      {
        this->definedVars.list = 0;
        this->definedVars.num = 0;
        this->definedVars.size = 0;
      }
    }
    v31 = this->definedVars.num;
    size = this->definedVars.size;
    if ( v31 == size )
    {
      if ( !this->definedVars.granularity )
        this->definedVars.granularity = 16;
      v33 = size
          + this->definedVars.granularity
          - (size + this->definedVars.granularity) % this->definedVars.granularity;
      if ( v33 > 0 )
      {
        if ( v33 != this->definedVars.size )
        {
          list = this->definedVars.list;
          this->definedVars.size = v33;
          if ( v33 < v31 )
            this->definedVars.num = v33;
          this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v33);
          for ( j = 0; j < this->definedVars.num; ++j )
            this->definedVars.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->definedVars.list )
          Memory::Free(this->definedVars.list);
        this->definedVars.list = 0;
        this->definedVars.num = 0;
        this->definedVars.size = 0;
      }
    }
    this->definedVars.list[this->definedVars.num++] = v27;
    v64 = -1;
    idStr::FreeData(&key);
    return v27;
  }
  if ( fixup )
  {
    v36 = idStr::FindText(key.data, "::", 1, 0, key.len);
    v37 = v36;
    if ( v36 > 0 )
    {
      idStr::Left(&key, &winName, v36);
      LOBYTE(v64) = 1;
      idStr::Right(&key, &var, key.len - v37 - 2);
      gui = this->gui;
      v39 = gui->__vftable;
      v56 = winName.data;
      LOBYTE(v64) = 2;
      v40 = v39->GetDesktop(gui);
      ChildByName = idWindow::FindChildByName(v40, v56);
      if ( ChildByName )
      {
        if ( ChildByName->win )
        {
          v42 = (int)ChildByName->win->GetWinVarByName(ChildByName->win, var.data, 0, owner);
          LOBYTE(v64) = 1;
          idStr::FreeData(&var);
          LOBYTE(v64) = 0;
          idStr::FreeData(&winName);
          v64 = -1;
          idStr::FreeData(&key);
          return (idWinVar *)v42;
        }
        else
        {
          if ( owner )
            *owner = ChildByName;
          WinVarByName = idSimpleWindow::GetWinVarByName(ChildByName->simp, var.data);
          LOBYTE(v64) = 1;
          idStr::FreeData(&var);
          LOBYTE(v64) = 0;
          idStr::FreeData(&winName);
          v64 = -1;
          idStr::FreeData(&key);
          return WinVarByName;
        }
      }
      LOBYTE(v64) = 1;
      idStr::FreeData(&var);
      LOBYTE(v64) = 0;
      idStr::FreeData(&winName);
    }
  }
  strrchr((unsigned __int8 *)_name, 0x5Fu);
  v45 = v44;
  if ( !v44 || !*(_BYTE *)(v44 + 1) || *(_BYTE *)(v44 + 2) )
  {
LABEL_137:
    v64 = -1;
    idStr::FreeData(&key);
    return 0;
  }
  temp.len = 0;
  temp.alloced = 20;
  temp.data = temp.baseBuffer;
  temp.baseBuffer[0] = 0;
  LOBYTE(v64) = 3;
  idStr::operator=(&temp, _name);
  *(_BYTE *)(temp.data - _name + v45) = 0;
  v46 = strchr("xyzw", *(char *)(v45 + 1));
  if ( !v46
    || (v47 = this->GetWinVarByName(this, temp.data, fixup, owner),
        !__RTDynamicCast(v47, 0, &idWinVar `RTTI Type Descriptor', &idWinVec4 `RTTI Type Descriptor', 0))
    && !__RTDynamicCast(v47, 0, &idWinVar `RTTI Type Descriptor', &idWinRectangle `RTTI Type Descriptor', 0) )
  {
    LOBYTE(v64) = 0;
    idStr::FreeData(&temp);
    goto LABEL_137;
  }
  v48 = (idWinVar *)Memory::Allocate(0x18u);
  if ( v48 )
  {
    v48->guiDict = 0;
    v48->name = 0;
    v48->eval = 1;
    v48->__vftable = (idWinVar_vtbl *)&idWinFloatMember::`vftable';
    v48[1].__vftable = (idWinVar_vtbl *)v47;
    v48[1].guiDict = (idDict *)(v46 - "xyzw");
    retVara = v48;
    idWinVar::SetName(v48, _name);
  }
  else
  {
    retVara = 0;
    idWinVar::SetName(0, _name);
  }
  if ( !this->definedVars.list )
  {
    v49 = this->definedVars.granularity;
    if ( v49 > 0 )
    {
      if ( v49 != this->definedVars.size )
      {
        v29 = v49 < this->definedVars.num;
        this->definedVars.size = v49;
        if ( v29 )
          this->definedVars.num = v49;
        this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v49);
        for ( k = 0; k < this->definedVars.num; ++k )
          this->definedVars.list[k] = *(idWinVar **)(4 * k);
      }
    }
    else
    {
      this->definedVars.list = 0;
      this->definedVars.num = 0;
      this->definedVars.size = 0;
    }
  }
  v51 = this->definedVars.num;
  v52 = this->definedVars.size;
  if ( v51 == v52 )
  {
    if ( !this->definedVars.granularity )
      this->definedVars.granularity = 16;
    v53 = v52 + this->definedVars.granularity - (v52 + this->definedVars.granularity) % this->definedVars.granularity;
    if ( v53 > 0 )
    {
      if ( v53 != this->definedVars.size )
      {
        v54 = this->definedVars.list;
        this->definedVars.size = v53;
        if ( v53 < v51 )
          this->definedVars.num = v53;
        this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v53);
        for ( m = 0; m < this->definedVars.num; ++m )
          this->definedVars.list[m] = v54[m];
        if ( v54 )
          Memory::Free(v54);
      }
    }
    else
    {
      if ( this->definedVars.list )
        Memory::Free(this->definedVars.list);
      this->definedVars.list = 0;
      this->definedVars.num = 0;
      this->definedVars.size = 0;
    }
  }
  this->definedVars.list[this->definedVars.num++] = retVara;
  LOBYTE(v64) = 0;
  idStr::FreeData(&temp);
  v64 = -1;
  idStr::FreeData(&key);
  return retVara;
}

// FUNC: protected: void __thiscall idWindow::ParseString(class idParser *,class idStr &)
void __thiscall idWindow::ParseString(idWindow *this, idParser *src, idStr *out)
{
  int len; // ebx
  idToken tok; // [esp+4h] [ebp-5Ch] BYREF
  int v5; // [esp+5Ch] [ebp-4h]

  tok.floatvalue = 0.0;
  tok.len = 0;
  tok.alloced = 20;
  tok.data = tok.baseBuffer;
  tok.baseBuffer[0] = 0;
  v5 = 0;
  if ( idParser::ReadToken(src, &tok) )
  {
    len = tok.len;
    if ( tok.len + 1 > out->alloced )
      idStr::ReAllocate(out, tok.len + 1, 0);
    qmemcpy(out->data, tok.data, len);
    out->data[len] = 0;
    out->len = len;
  }
  v5 = -1;
  idStr::FreeData(&tok);
}

// FUNC: protected: virtual bool __thiscall idWindow::ParseInternalVar(char const *,class idParser *)
char __thiscall idWindow::ParseInternalVar(idWindow *this, const char *_name, idParser *src)
{
  idStr fontStr; // [esp+8h] [ebp-9Ch] BYREF
  idStr playStr; // [esp+28h] [ebp-7Ch] BYREF
  idToken tok; // [esp+48h] [ebp-5Ch] BYREF
  int v8; // [esp+A0h] [ebp-4h]

  if ( !idStr::Icmp(_name, "showtime") )
  {
    if ( idParser::ParseBool(src) )
      BYTE2(this->flags) |= 0x80u;
    return 1;
  }
  if ( !idStr::Icmp(_name, "showcoords") )
  {
    if ( idParser::ParseBool(src) )
      BYTE2(this->flags) |= 0x40u;
    return 1;
  }
  if ( !idStr::Icmp(_name, "forceaspectwidth") )
  {
    this->forceAspectWidth = idParser::ParseFloat(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "forceaspectheight") )
  {
    this->forceAspectHeight = idParser::ParseFloat(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "matscalex") )
  {
    this->matScalex = idParser::ParseFloat(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "matscaley") )
  {
    this->matScaley = idParser::ParseFloat(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "bordersize") )
  {
    this->borderSize = idParser::ParseFloat(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "nowrap") )
  {
    if ( idParser::ParseBool(src) )
      BYTE1(this->flags) |= 0x80u;
    return 1;
  }
  if ( !idStr::Icmp(_name, "textSpacing") )
  {
    this->textSpacing = idParser::ParseFloat(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "textalign") )
  {
    this->textAlign = idParser::ParseInt(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "textalignx") )
  {
    this->textAlignx = idParser::ParseFloat(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "textaligny") )
  {
    this->textAligny = idParser::ParseFloat(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "shear") )
  {
    this->shear.x = idParser::ParseFloat(src);
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    v8 = 0;
    idParser::ReadToken(src, &tok);
    if ( !idStr::Icmp(tok.data, ",") )
    {
      this->shear.y = idParser::ParseFloat(src);
      v8 = -1;
      idStr::FreeData(&tok);
      return 1;
    }
    idParser::Error(src, "Expected comma in shear definiation");
    v8 = -1;
    idStr::FreeData(&tok);
    return 0;
  }
  if ( !idStr::Icmp(_name, "textStyle") )
  {
    this->textStyle = idParser::ParseInt(src);
    return 1;
  }
  if ( idStr::Icmp(_name, "wantenter") )
  {
    if ( idStr::Icmp(_name, "naturalmatscale") )
    {
      if ( idStr::Icmp(_name, "noclip") )
      {
        if ( idStr::Icmp(_name, "nocursor") )
        {
          if ( idStr::Icmp(_name, "menugui") )
          {
            if ( idStr::Icmp(_name, "modal") )
            {
              if ( idStr::Icmp(_name, "invertrect") )
              {
                if ( idStr::Icmp(_name, "alwaysThink") )
                {
                  if ( idStr::Icmp(_name, "chatWindow") )
                  {
                    if ( !idStr::Icmp(_name, "name") )
                    {
                      idWindow::ParseString(this, src, &this->name);
                      return 1;
                    }
                    if ( !idStr::Icmp(_name, "play") )
                    {
                      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
                        common.type,
                        "play encountered during gui parse.. see Robert\n");
                      playStr.len = 0;
                      playStr.alloced = 20;
                      playStr.data = playStr.baseBuffer;
                      playStr.baseBuffer[0] = 0;
                      v8 = 1;
                      idWindow::ParseString(this, src, &playStr);
                      v8 = -1;
                      idStr::FreeData(&playStr);
                      return 1;
                    }
                    if ( !idStr::Icmp(_name, "comment") )
                    {
                      idWindow::ParseString(this, src, &this->comment);
                      return 1;
                    }
                    if ( !idStr::Icmp(_name, "font") )
                    {
                      fontStr.len = 0;
                      fontStr.alloced = 20;
                      fontStr.data = fontStr.baseBuffer;
                      fontStr.baseBuffer[0] = 0;
                      v8 = 2;
                      idWindow::ParseString(this, src, &fontStr);
                      this->fontNum = idDeviceContext::FindFont(this->dc, fontStr.data);
                      v8 = -1;
                      idStr::FreeData(&fontStr);
                      return 1;
                    }
                    return 0;
                  }
                  if ( idParser::ParseBool(src) )
                    HIBYTE(this->flags) |= 0x20u;
                  return 1;
                }
                else
                {
                  if ( idParser::ParseBool(src) )
                    HIBYTE(this->flags) |= 8u;
                  return 1;
                }
              }
              else
              {
                if ( idParser::ParseBool(src) )
                  BYTE2(this->flags) |= 2u;
                return 1;
              }
            }
            else
            {
              if ( idParser::ParseBool(src) )
                BYTE1(this->flags) |= 2u;
              return 1;
            }
          }
          else
          {
            if ( idParser::ParseBool(src) )
              BYTE2(this->flags) |= 0x10u;
            return 1;
          }
        }
        else
        {
          if ( idParser::ParseBool(src) )
            BYTE2(this->flags) |= 8u;
          return 1;
        }
      }
      else
      {
        if ( idParser::ParseBool(src) )
          BYTE2(this->flags) |= 1u;
        return 1;
      }
    }
    else
    {
      if ( idParser::ParseBool(src) )
        BYTE2(this->flags) |= 4u;
      return 1;
    }
  }
  else
  {
    if ( idParser::ParseBool(src) )
      HIBYTE(this->flags) |= 1u;
    return 1;
  }
}

// FUNC: public: bool __thiscall idWindow::ParseRegEntry(char const *,class idParser *)
char __thiscall idWindow::ParseRegEntry(idWindow *this, char *name, idParser *src)
{
  char *data; // edx
  unsigned __int8 v5; // al
  int v6; // edi
  char *v7; // ecx
  idWinVar *v8; // ebx
  int v9; // ebp
  const idRegEntry *v10; // edi
  idWinStr *v11; // eax
  int v12; // eax
  bool v13; // cc
  int jj; // eax
  int v15; // ebx
  int v16; // eax
  int v17; // ecx
  idWinVar **list; // edi
  int kk; // eax
  idWinStr *v20; // eax
  int granularity; // eax
  int i; // eax
  int num; // ebx
  int size; // eax
  int v25; // ecx
  int j; // eax
  idWinStr *v27; // eax
  int v28; // eax
  int n; // eax
  int v30; // ebx
  int v31; // eax
  int v32; // ecx
  int ii; // eax
  idWinStr *v34; // eax
  idWinStr *v35; // eax
  int v36; // eax
  int k; // eax
  int v38; // ebx
  int v39; // eax
  int v40; // ecx
  int m; // eax
  idWinStr *v43; // [esp+10h] [ebp-84h]
  int other; // [esp+14h] [ebp-80h] BYREF
  idStr work; // [esp+18h] [ebp-7Ch] BYREF
  idToken tok; // [esp+38h] [ebp-5Ch] BYREF
  int v47; // [esp+90h] [ebp-4h]

  work.len = 0;
  work.alloced = 20;
  work.data = work.baseBuffer;
  work.baseBuffer[0] = 0;
  v47 = 0;
  idStr::operator=(&work, name);
  data = work.data;
  v5 = *work.data;
  v6 = 0;
  if ( *work.data )
  {
    v7 = work.data;
    do
    {
      if ( idStr::lowerCaseCharacter[v5] )
        v5 = idStr::lowerCaseCharacter[v5];
      *v7 = v5;
      data = work.data;
      v5 = work.data[++v6];
      v7 = &work.data[v6];
    }
    while ( v5 );
  }
  v8 = this->GetWinVarByName(this, data, 0, 0);
  if ( !v8 )
  {
LABEL_10:
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    LOBYTE(v47) = 1;
    if ( !idParser::ReadToken(src, &tok) )
    {
LABEL_106:
      LOBYTE(v47) = 0;
      idStr::FreeData(&tok);
      goto LABEL_107;
    }
    if ( v8 )
    {
      v8->Set(v8, tok.data);
      goto LABEL_106;
    }
    if ( tok.type == 3 )
    {
      if ( (tok.subtype & 1) != 0 )
      {
        v20 = (idWinStr *)Memory::Allocate(0x14u);
        if ( v20 )
        {
          v20->guiDict = 0;
          v20->name = 0;
          v20->eval = 1;
          v20->__vftable = (idWinStr_vtbl *)&idWinInt::`vftable';
          v43 = v20;
        }
        else
        {
          v43 = 0;
        }
        *(float *)&other = COERCE_FLOAT(atoi(tok.data));
        idWinInt::operator=((idWinInt *)v43, &other);
        idWinVar::SetName(v43, work.data);
        if ( !this->definedVars.list )
        {
          granularity = this->definedVars.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->definedVars.size )
            {
              v13 = granularity < this->definedVars.num;
              this->definedVars.size = granularity;
              if ( v13 )
                this->definedVars.num = granularity;
              this->definedVars.list = (idWinVar **)Memory::Allocate(4 * granularity);
              for ( i = 0; i < this->definedVars.num; ++i )
                this->definedVars.list[i] = *(idWinVar **)(4 * i);
            }
          }
          else
          {
            this->definedVars.list = 0;
            this->definedVars.num = 0;
            this->definedVars.size = 0;
          }
        }
        num = this->definedVars.num;
        size = this->definedVars.size;
        if ( num != size )
          goto LABEL_105;
        if ( !this->definedVars.granularity )
          this->definedVars.granularity = 16;
        v25 = size
            + this->definedVars.granularity
            - (size + this->definedVars.granularity) % this->definedVars.granularity;
        if ( v25 > 0 )
        {
          if ( v25 != this->definedVars.size )
          {
            list = this->definedVars.list;
            this->definedVars.size = v25;
            if ( v25 < num )
              this->definedVars.num = v25;
            this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v25);
            for ( j = 0; j < this->definedVars.num; ++j )
              this->definedVars.list[j] = list[j];
            goto LABEL_103;
          }
LABEL_105:
          this->definedVars.list[this->definedVars.num++] = v43;
          goto LABEL_106;
        }
      }
      else if ( SLOBYTE(tok.subtype) >= 0 )
      {
        v34 = (idWinStr *)Memory::Allocate(0x30u);
        if ( v34 )
        {
          idWinStr::idWinStr(v34);
          v43 = v35;
        }
        else
        {
          v43 = 0;
        }
        idWinStr::operator=(v43, &tok);
        idWinVar::SetName(v43, work.data);
        if ( !this->definedVars.list )
        {
          v36 = this->definedVars.granularity;
          if ( v36 > 0 )
          {
            if ( v36 != this->definedVars.size )
            {
              v13 = v36 < this->definedVars.num;
              this->definedVars.size = v36;
              if ( v13 )
                this->definedVars.num = v36;
              this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v36);
              for ( k = 0; k < this->definedVars.num; ++k )
                this->definedVars.list[k] = *(idWinVar **)(4 * k);
            }
          }
          else
          {
            this->definedVars.list = 0;
            this->definedVars.num = 0;
            this->definedVars.size = 0;
          }
        }
        v38 = this->definedVars.num;
        v39 = this->definedVars.size;
        if ( v38 != v39 )
          goto LABEL_105;
        if ( !this->definedVars.granularity )
          this->definedVars.granularity = 16;
        v40 = v39
            + this->definedVars.granularity
            - (v39 + this->definedVars.granularity) % this->definedVars.granularity;
        if ( v40 > 0 )
        {
          if ( v40 != this->definedVars.size )
          {
            list = this->definedVars.list;
            this->definedVars.size = v40;
            if ( v40 < v38 )
              this->definedVars.num = v40;
            this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v40);
            for ( m = 0; m < this->definedVars.num; ++m )
              this->definedVars.list[m] = list[m];
            goto LABEL_103;
          }
          goto LABEL_105;
        }
      }
      else
      {
        v27 = (idWinStr *)Memory::Allocate(0x14u);
        if ( v27 )
        {
          v27->guiDict = 0;
          v27->name = 0;
          v27->eval = 1;
          v27->__vftable = (idWinStr_vtbl *)&idWinFloat::`vftable';
          v43 = v27;
        }
        else
        {
          v43 = 0;
        }
        *(float *)&other = atof(tok.data);
        idWinFloat::operator=((idWinFloat *)v43, (float *)&other);
        idWinVar::SetName(v43, work.data);
        if ( !this->definedVars.list )
        {
          v28 = this->definedVars.granularity;
          if ( v28 > 0 )
          {
            if ( v28 != this->definedVars.size )
            {
              v13 = v28 < this->definedVars.num;
              this->definedVars.size = v28;
              if ( v13 )
                this->definedVars.num = v28;
              this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v28);
              for ( n = 0; n < this->definedVars.num; ++n )
                this->definedVars.list[n] = *(idWinVar **)(4 * n);
            }
          }
          else
          {
            this->definedVars.list = 0;
            this->definedVars.num = 0;
            this->definedVars.size = 0;
          }
        }
        v30 = this->definedVars.num;
        v31 = this->definedVars.size;
        if ( v30 != v31 )
          goto LABEL_105;
        if ( !this->definedVars.granularity )
          this->definedVars.granularity = 16;
        v32 = v31
            + this->definedVars.granularity
            - (v31 + this->definedVars.granularity) % this->definedVars.granularity;
        if ( v32 > 0 )
        {
          if ( v32 != this->definedVars.size )
          {
            list = this->definedVars.list;
            this->definedVars.size = v32;
            if ( v32 < v30 )
              this->definedVars.num = v32;
            this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v32);
            for ( ii = 0; ii < this->definedVars.num; ++ii )
              this->definedVars.list[ii] = list[ii];
            goto LABEL_103;
          }
          goto LABEL_105;
        }
      }
    }
    else
    {
      v11 = (idWinStr *)Memory::Allocate(0x30u);
      if ( v11 )
      {
        v11->guiDict = 0;
        v11->name = 0;
        v11->eval = 1;
        v11->__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
        v11->data.len = 0;
        v11->data.alloced = 20;
        v11->data.data = v11->data.baseBuffer;
        v11->data.baseBuffer[0] = 0;
        v43 = v11;
      }
      else
      {
        v43 = 0;
      }
      idWinStr::operator=(v43, &tok);
      idWinVar::SetName(v43, work.data);
      if ( !this->definedVars.list )
      {
        v12 = this->definedVars.granularity;
        if ( v12 > 0 )
        {
          if ( v12 != this->definedVars.size )
          {
            v13 = v12 < this->definedVars.num;
            this->definedVars.size = v12;
            if ( v13 )
              this->definedVars.num = v12;
            this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v12);
            for ( jj = 0; jj < this->definedVars.num; ++jj )
              this->definedVars.list[jj] = *(idWinVar **)(4 * jj);
          }
        }
        else
        {
          this->definedVars.list = 0;
          this->definedVars.num = 0;
          this->definedVars.size = 0;
        }
      }
      v15 = this->definedVars.num;
      v16 = this->definedVars.size;
      if ( v15 != v16 )
        goto LABEL_105;
      if ( !this->definedVars.granularity )
        this->definedVars.granularity = 16;
      v17 = v16 + this->definedVars.granularity - (v16 + this->definedVars.granularity) % this->definedVars.granularity;
      if ( v17 > 0 )
      {
        if ( v17 != this->definedVars.size )
        {
          list = this->definedVars.list;
          this->definedVars.size = v17;
          if ( v17 < v15 )
            this->definedVars.num = v17;
          this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v17);
          for ( kk = 0; kk < this->definedVars.num; ++kk )
            this->definedVars.list[kk] = list[kk];
LABEL_103:
          if ( list )
            Memory::Free(list);
          goto LABEL_105;
        }
        goto LABEL_105;
      }
    }
    if ( this->definedVars.list )
      Memory::Free(this->definedVars.list);
    this->definedVars.list = 0;
    this->definedVars.num = 0;
    this->definedVars.size = 0;
    goto LABEL_105;
  }
  v9 = 0;
  v10 = idWindow::RegisterVars;
  while ( idStr::Icmp(work.data, v10->name) )
  {
    ++v10;
    ++v9;
    if ( (int)v10 >= (int)&idWindow::NumRegisterVars )
      goto LABEL_10;
  }
  idRegisterList::AddReg(&this->regList, work.data, *(&type + 3 * v9), src, this, v8);
LABEL_107:
  v47 = -1;
  idStr::FreeData(&work);
  return 1;
}

// FUNC: public: int __thiscall idWindow::ExpressionConstant(float)
int __thiscall idWindow::ExpressionConstant(idWindow *this, float f)
{
  int num; // edx
  int v4; // ecx
  int result; // eax
  int granularity; // eax
  bool v7; // cc
  int i; // eax
  int v9; // ebp
  int size; // eax
  int v11; // ecx
  float *list; // edi
  int j; // eax
  int v14; // eax
  int k; // eax
  int v16; // ebp
  int v17; // eax
  int v18; // ecx
  float *v19; // edi
  int m; // eax
  int v21; // [esp+Ch] [ebp-4h]

  num = this->expressionRegisters.num;
  v4 = 1;
  if ( num <= 1 )
  {
LABEL_5:
    if ( num == 4096 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "expressionConstant: gui %s hit MAX_EXPRESSION_REGISTERS",
        this->gui->source.data);
      return 0;
    }
    else
    {
      if ( v4 > num )
      {
        v21 = v4 - num;
        do
        {
          if ( !this->expressionRegisters.list )
          {
            granularity = this->expressionRegisters.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->expressionRegisters.size )
              {
                v7 = granularity < this->expressionRegisters.num;
                this->expressionRegisters.size = granularity;
                if ( v7 )
                  this->expressionRegisters.num = granularity;
                this->expressionRegisters.list = (float *)Memory::Allocate(4 * granularity);
                for ( i = 0; i < this->expressionRegisters.num; ++i )
                  this->expressionRegisters.list[i] = *(float *)(4 * i);
              }
            }
            else
            {
              this->expressionRegisters.list = 0;
              this->expressionRegisters.num = 0;
              this->expressionRegisters.size = 0;
            }
          }
          v9 = this->expressionRegisters.num;
          size = this->expressionRegisters.size;
          if ( v9 == size )
          {
            if ( !this->expressionRegisters.granularity )
              this->expressionRegisters.granularity = 16;
            v11 = size
                + this->expressionRegisters.granularity
                - (size + this->expressionRegisters.granularity) % this->expressionRegisters.granularity;
            if ( v11 > 0 )
            {
              if ( v11 != this->expressionRegisters.size )
              {
                list = this->expressionRegisters.list;
                this->expressionRegisters.size = v11;
                if ( v11 < v9 )
                  this->expressionRegisters.num = v11;
                this->expressionRegisters.list = (float *)Memory::Allocate(4 * v11);
                for ( j = 0; j < this->expressionRegisters.num; ++j )
                  this->expressionRegisters.list[j] = list[j];
                if ( list )
                  Memory::Free(list);
              }
            }
            else
            {
              if ( this->expressionRegisters.list )
                Memory::Free(this->expressionRegisters.list);
              this->expressionRegisters.list = 0;
              this->expressionRegisters.num = 0;
              this->expressionRegisters.size = 0;
            }
          }
          this->expressionRegisters.list[this->expressionRegisters.num++] = -9999999.0;
          --v21;
        }
        while ( v21 );
      }
      if ( !this->expressionRegisters.list )
      {
        v14 = this->expressionRegisters.granularity;
        if ( v14 > 0 )
        {
          if ( v14 != this->expressionRegisters.size )
          {
            v7 = v14 < this->expressionRegisters.num;
            this->expressionRegisters.size = v14;
            if ( v7 )
              this->expressionRegisters.num = v14;
            this->expressionRegisters.list = (float *)Memory::Allocate(4 * v14);
            for ( k = 0; k < this->expressionRegisters.num; ++k )
              this->expressionRegisters.list[k] = *(float *)(4 * k);
          }
        }
        else
        {
          this->expressionRegisters.list = 0;
          this->expressionRegisters.num = 0;
          this->expressionRegisters.size = 0;
        }
      }
      v16 = this->expressionRegisters.num;
      v17 = this->expressionRegisters.size;
      if ( v16 == v17 )
      {
        if ( !this->expressionRegisters.granularity )
          this->expressionRegisters.granularity = 16;
        v18 = v17
            + this->expressionRegisters.granularity
            - (v17 + this->expressionRegisters.granularity) % this->expressionRegisters.granularity;
        if ( v18 > 0 )
        {
          if ( v18 != this->expressionRegisters.size )
          {
            v19 = this->expressionRegisters.list;
            this->expressionRegisters.size = v18;
            if ( v18 < v16 )
              this->expressionRegisters.num = v18;
            this->expressionRegisters.list = (float *)Memory::Allocate(4 * v18);
            for ( m = 0; m < this->expressionRegisters.num; ++m )
              this->expressionRegisters.list[m] = v19[m];
            if ( v19 )
              Memory::Free(v19);
          }
        }
        else
        {
          if ( this->expressionRegisters.list )
            Memory::Free(this->expressionRegisters.list);
          this->expressionRegisters.list = 0;
          this->expressionRegisters.num = 0;
          this->expressionRegisters.size = 0;
        }
      }
      this->expressionRegisters.list[this->expressionRegisters.num++] = f;
      result = this->expressionRegisters.num - 1;
      idWindow::registerIsTemporary[result] = 0;
    }
  }
  else
  {
    while ( idWindow::registerIsTemporary[v4] || this->expressionRegisters.list[v4] != f )
    {
      if ( ++v4 >= num )
        goto LABEL_5;
    }
    return v4;
  }
  return result;
}

// FUNC: protected: int __thiscall idWindow::ExpressionTemporary(void)
int __thiscall idWindow::ExpressionTemporary(idWindow *this)
{
  int num; // eax
  int granularity; // eax
  bool v5; // cc
  int i; // eax
  int v7; // ebp
  int size; // eax
  int v9; // ecx
  float *list; // edi
  int j; // eax

  num = this->expressionRegisters.num;
  if ( num == 4096 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "expressionTemporary: gui %s hit MAX_EXPRESSION_REGISTERS",
      this->gui->source.data);
    return 0;
  }
  else
  {
    idWindow::registerIsTemporary[num] = 1;
    if ( !this->expressionRegisters.list )
    {
      granularity = this->expressionRegisters.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->expressionRegisters.size )
        {
          v5 = granularity < this->expressionRegisters.num;
          this->expressionRegisters.size = granularity;
          if ( v5 )
            this->expressionRegisters.num = granularity;
          this->expressionRegisters.list = (float *)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->expressionRegisters.num; ++i )
            this->expressionRegisters.list[i] = *(float *)(4 * i);
        }
      }
      else
      {
        this->expressionRegisters.list = 0;
        this->expressionRegisters.num = 0;
        this->expressionRegisters.size = 0;
      }
    }
    v7 = this->expressionRegisters.num;
    size = this->expressionRegisters.size;
    if ( v7 == size )
    {
      if ( !this->expressionRegisters.granularity )
        this->expressionRegisters.granularity = 16;
      v9 = size
         + this->expressionRegisters.granularity
         - (size + this->expressionRegisters.granularity) % this->expressionRegisters.granularity;
      if ( v9 > 0 )
      {
        if ( v9 != this->expressionRegisters.size )
        {
          list = this->expressionRegisters.list;
          this->expressionRegisters.size = v9;
          if ( v9 < v7 )
            this->expressionRegisters.num = v9;
          this->expressionRegisters.list = (float *)Memory::Allocate(4 * v9);
          for ( j = 0; j < this->expressionRegisters.num; ++j )
            this->expressionRegisters.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->expressionRegisters.list )
          Memory::Free(this->expressionRegisters.list);
        this->expressionRegisters.list = 0;
        this->expressionRegisters.num = 0;
        this->expressionRegisters.size = 0;
      }
    }
    this->expressionRegisters.list[this->expressionRegisters.num++] = 0.0;
    return this->expressionRegisters.num - 1;
  }
}

// FUNC: protected: struct wexpOp_t * __thiscall idWindow::ExpressionOp(void)
wexpOp_t *__thiscall idWindow::ExpressionOp(idWindow *this)
{
  int granularity; // eax
  bool v4; // cc
  wexpOp_t *v5; // eax
  int v6; // ecx
  wexpOpType_t *v7; // eax
  wexpOp_t *v8; // edx
  int num; // ebp
  int size; // ecx
  int v11; // eax
  wexpOp_t *list; // edi
  wexpOp_t *v13; // eax
  int v14; // ecx
  int v15; // eax
  wexpOp_t *v16; // edx
  wexpOpType_t opType; // ebp
  wexpOp_t *v18; // edi
  wexpOp_t *v19; // edx
  wexpOp_t *v20; // [esp+4h] [ebp-4h]

  if ( this->ops.num == 4096 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "expressionOp: gui %s hit MAX_EXPRESSION_OPS",
      this->gui->source.data);
    return this->ops.list;
  }
  else
  {
    if ( !this->ops.list )
    {
      granularity = this->ops.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->ops.size )
        {
          v4 = granularity < this->ops.num;
          this->ops.size = granularity;
          if ( v4 )
            this->ops.num = granularity;
          v5 = (wexpOp_t *)Memory::Allocate(20 * granularity);
          v6 = 0;
          v4 = this->ops.num <= 0;
          this->ops.list = v5;
          if ( !v4 )
          {
            v7 = 0;
            do
            {
              v8 = (wexpOp_t *)((char *)v7 + (unsigned int)this->ops.list);
              v8->opType = *v7;
              v8->a = v7[1];
              v8->b = v7[2];
              v8->c = v7[3];
              ++v6;
              v8->d = v7[4];
              v7 += 5;
            }
            while ( v6 < this->ops.num );
          }
        }
      }
      else
      {
        this->ops.list = 0;
        this->ops.num = 0;
        this->ops.size = 0;
      }
    }
    num = this->ops.num;
    size = this->ops.size;
    if ( num == size )
    {
      if ( !this->ops.granularity )
        this->ops.granularity = 16;
      v11 = this->ops.granularity + size - (this->ops.granularity + size) % this->ops.granularity;
      if ( v11 > 0 )
      {
        if ( v11 != this->ops.size )
        {
          list = this->ops.list;
          v20 = list;
          this->ops.size = v11;
          if ( v11 < num )
            this->ops.num = v11;
          v13 = (wexpOp_t *)Memory::Allocate(20 * v11);
          v14 = 0;
          v4 = this->ops.num <= 0;
          this->ops.list = v13;
          if ( !v4 )
          {
            v15 = 0;
            do
            {
              v16 = &list[v15];
              opType = list[v15].opType;
              v18 = &this->ops.list[v15];
              v18->opType = opType;
              v18->a = v16->a;
              v18->b = v16->b;
              v18->c = v16->c;
              v18->d = v16->d;
              list = v20;
              ++v14;
              ++v15;
            }
            while ( v14 < this->ops.num );
          }
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->ops.list )
          Memory::Free(this->ops.list);
        this->ops.list = 0;
        this->ops.num = 0;
        this->ops.size = 0;
      }
    }
    v19 = &this->ops.list[this->ops.num];
    v19->opType = WOP_TYPE_ADD;
    v19->a = 0;
    v19->b = 0;
    v19->c = 0;
    v19->d = 0;
    ++this->ops.num;
    return &this->ops.list[this->ops.num - 1];
  }
}

// FUNC: protected: int __thiscall idWindow::ParseEmitOp(class idParser *,int,enum wexpOpType_t,int,struct wexpOp_t * *)
int __thiscall idWindow::ParseEmitOp(
        idWindow *this,
        idParser *src,
        int a,
        wexpOpType_t opType,
        int priority,
        wexpOp_t **opp)
{
  int v7; // ebx
  wexpOp_t *v8; // esi

  v7 = idWindow::ParseExpressionPriority(this, src, priority, 0, 0);
  v8 = idWindow::ExpressionOp(this);
  v8->opType = opType;
  v8->a = a;
  v8->b = v7;
  v8->c = idWindow::ExpressionTemporary(this);
  if ( opp )
    *opp = v8;
  return v8->c;
}

// FUNC: protected: int __thiscall idWindow::ParseTerm(class idParser *,class idWinVar *,int)
int __thiscall idWindow::ParseTerm(idWindow *this, idParser *src, idWinVar *var, idParser *component)
{
  int v6; // esi
  long double floatvalue; // st7
  const idDecl *v9; // eax
  int v10; // ebx
  wexpOp_t *v11; // edi
  int v12; // esi
  idWinVar *v13; // edi
  wexpOp_t *v14; // ebp
  wexpOp_t *v15; // ebp
  _BYTE *v16; // eax
  char *data; // ecx
  int v18; // ebx
  _BYTE *v19; // edx
  char v20; // al
  wexpOp_t *v21; // edi
  float f; // [esp+10h] [ebp-70h]
  idToken token; // [esp+24h] [ebp-5Ch] BYREF
  int v24; // [esp+7Ch] [ebp-4h]
  idParser *srcb; // [esp+84h] [ebp+4h]
  idParser *srca; // [esp+84h] [ebp+4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v24 = 0;
  idParser::ReadToken(src, &token);
  if ( !idStr::Cmp(token.data, "(") )
  {
    v6 = idWindow::ParseExpressionPriority(this, src, 4, 0, 0);
    idParser::ExpectTokenString(src, ")");
    v24 = -1;
    idStr::FreeData(&token);
    return v6;
  }
  if ( !idStr::Icmp(token.data, "time") )
  {
    v24 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  if ( !idStr::Cmp(token.data, "-") )
  {
    idParser::ReadToken(src, &token);
    if ( token.type == 3 )
      goto LABEL_11;
    if ( idStr::Cmp(token.data, ".") )
    {
      idParser::Warning(src, "Bad negative number '%s'", token.data);
      v24 = -1;
      idStr::FreeData(&token);
      return 0;
    }
    if ( token.type == 3 )
    {
LABEL_11:
      if ( (token.subtype & 0x10000) == 0 )
        idToken::NumberValue(&token);
      floatvalue = -token.floatvalue;
    }
    else
    {
      floatvalue = -0.0;
    }
    goto LABEL_47;
  }
  if ( token.type == 3 )
    goto LABEL_44;
  if ( !idStr::Cmp(token.data, ".") || !idStr::Cmp(token.data, "-") )
  {
    if ( token.type != 3 )
    {
      floatvalue = 0.0;
LABEL_47:
      f = floatvalue;
      v12 = idWindow::ExpressionConstant(this, f);
      goto LABEL_48;
    }
LABEL_44:
    if ( (token.subtype & 0x10000) == 0 )
      idToken::NumberValue(&token);
    floatvalue = token.floatvalue;
    goto LABEL_47;
  }
  v9 = declManager->FindType(declManager, 0, token.data, 0, 0);
  if ( v9 )
  {
    v10 = v9->base->Index(v9->base);
    idParser::ExpectTokenString(src, "[");
    srcb = (idParser *)idWindow::ParseExpressionPriority(this, src, 4, 0, 0);
    idParser::ExpectTokenString(src, "]");
    v11 = idWindow::ExpressionOp(this);
    v11->opType = WOP_TYPE_TABLE;
    v11->a = v10;
    v11->b = (int)srcb;
    v12 = idWindow::ExpressionTemporary(this);
    v11->c = v12;
  }
  else
  {
    v13 = var;
    if ( var || (v13 = this->GetWinVarByName(this, token.data, 1, 0)) != 0 )
    {
      v13->Init(v13, token.data, this);
      srca = component;
      if ( __RTDynamicCast(v13, 0, &idWinVar `RTTI Type Descriptor', &idWinVec4 `RTTI Type Descriptor', 0) )
      {
        if ( idParser::ReadToken(src, &token) )
        {
          if ( idStr::Cmp(token.data, "[") )
          {
            idParser::UnreadToken(src, &token);
          }
          else
          {
            srca = (idParser *)idWindow::ParseExpressionPriority(this, src, 4, 0, 0);
            idParser::ExpectTokenString(src, "]");
          }
        }
        v14 = idWindow::ExpressionOp(this);
        v14->b = (int)srca;
        v14->opType = WOP_TYPE_VAR;
        v14->a = (int)v13;
        v12 = idWindow::ExpressionTemporary(this);
        v14->c = v12;
      }
      else
      {
        if ( __RTDynamicCast(v13, 0, &idWinVar `RTTI Type Descriptor', &idWinFloat `RTTI Type Descriptor', 0) )
        {
          v15 = idWindow::ExpressionOp(this);
          v15->opType = WOP_TYPE_VARF;
        }
        else if ( __RTDynamicCast(v13, 0, &idWinVar `RTTI Type Descriptor', &idWinFloatMember `RTTI Type Descriptor', 0) )
        {
          v15 = idWindow::ExpressionOp(this);
          v15->opType = WOP_TYPE_VARFM;
        }
        else if ( __RTDynamicCast(v13, 0, &idWinVar `RTTI Type Descriptor', &idWinInt `RTTI Type Descriptor', 0) )
        {
          v15 = idWindow::ExpressionOp(this);
          v15->opType = WOP_TYPE_VARI;
        }
        else if ( __RTDynamicCast(v13, 0, &idWinVar `RTTI Type Descriptor', &idWinBool `RTTI Type Descriptor', 0) )
        {
          v15 = idWindow::ExpressionOp(this);
          v15->opType = WOP_TYPE_VARB;
        }
        else
        {
          if ( !__RTDynamicCast(v13, 0, &idWinVar `RTTI Type Descriptor', &idWinStr `RTTI Type Descriptor', 0) )
          {
            idParser::Warning(src, "Var expression not vec4, float or int '%s'", token.data);
            v24 = -1;
            idStr::FreeData(&token);
            return 0;
          }
          v15 = idWindow::ExpressionOp(this);
          v15->opType = WOP_TYPE_VARS;
        }
        v15->a = (int)v13;
        v15->b = (int)component;
        v12 = idWindow::ExpressionTemporary(this);
        v15->c = v12;
      }
    }
    else
    {
      v16 = Memory::Allocate(token.len + 1);
      data = token.data;
      v18 = (int)v16;
      v19 = v16;
      do
      {
        v20 = *data;
        *v19++ = *data++;
      }
      while ( v20 );
      v21 = idWindow::ExpressionOp(this);
      v21->opType = WOP_TYPE_VAR;
      v21->a = v18;
      v21->b = -2;
      v12 = idWindow::ExpressionTemporary(this);
      v21->c = v12;
    }
  }
LABEL_48:
  v24 = -1;
  idStr::FreeData(&token);
  return v12;
}

// FUNC: protected: int __thiscall idWindow::ParseExpressionPriority(class idParser *,int,class idWinVar *,int)
int __thiscall idWindow::ParseExpressionPriority(
        idWindow *this,
        idParser *src,
        int priority,
        idWinVar *var,
        int component)
{
  int v6; // esi
  int v8; // ebp
  int v9; // ebx
  wexpOp_t *v10; // edi
  int v11; // esi
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v16; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v16 = 0;
  if ( !priority )
  {
    v6 = idWindow::ParseTerm(this, src, var, (idParser *)component);
    v16 = -1;
    idStr::FreeData(&token);
    return v6;
  }
  v8 = idWindow::ParseExpressionPriority(this, src, priority - 1, var, component);
  if ( !idParser::ReadToken(src, &token) )
    goto LABEL_42;
  switch ( priority )
  {
    case 1:
      if ( !idStr::Cmp(token.data, "*") )
      {
        v9 = idWindow::ParseExpressionPriority(this, src, 1, 0, 0);
        v10 = idWindow::ExpressionOp(this);
        v10->opType = WOP_TYPE_MULTIPLY;
        v10->a = v8;
        v10->b = v9;
        v11 = idWindow::ExpressionTemporary(this);
        v10->c = v11;
LABEL_35:
        v16 = -1;
        idStr::FreeData(&token);
        return v11;
      }
      if ( !idStr::Cmp(token.data, "/") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_DIVIDE, 1, 0);
LABEL_34:
        v11 = v12;
        goto LABEL_35;
      }
      if ( !idStr::Cmp(token.data, "%") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_MOD, 1, 0);
        goto LABEL_34;
      }
      goto LABEL_41;
    case 2:
      if ( !idStr::Cmp(token.data, "+") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_ADD, 2, 0);
        goto LABEL_34;
      }
      if ( !idStr::Cmp(token.data, "-") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_SUBTRACT, 2, 0);
        goto LABEL_34;
      }
      goto LABEL_41;
    case 3:
      if ( !idStr::Cmp(token.data, ">") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_GT, 3, 0);
        goto LABEL_34;
      }
      if ( !idStr::Cmp(token.data, ">=") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_GE, 3, 0);
        goto LABEL_34;
      }
      if ( !idStr::Cmp(token.data, "<") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_LT, 3, 0);
        goto LABEL_34;
      }
      if ( !idStr::Cmp(token.data, "<=") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_LE, 3, 0);
        goto LABEL_34;
      }
      if ( !idStr::Cmp(token.data, "==") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_EQ, 3, 0);
        goto LABEL_34;
      }
      if ( !idStr::Cmp(token.data, "!=") )
      {
        v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_NE, 3, 0);
        goto LABEL_34;
      }
      goto LABEL_41;
  }
  if ( priority != 4 )
    goto LABEL_41;
  if ( !idStr::Cmp(token.data, "&&") )
  {
    v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_AND, 4, 0);
    goto LABEL_34;
  }
  if ( !idStr::Cmp(token.data, "||") )
  {
    v12 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_OR, 4, 0);
    goto LABEL_34;
  }
  if ( idStr::Cmp(token.data, "?") )
  {
LABEL_41:
    idParser::UnreadToken(src, &token);
LABEL_42:
    v16 = -1;
    idStr::FreeData(&token);
    return v8;
  }
  component = 0;
  v13 = idWindow::ParseEmitOp(this, src, v8, WOP_TYPE_COND, 4, (wexpOp_t **)&component);
  if ( idParser::ReadToken(src, &token) )
  {
    if ( !idStr::Cmp(token.data, ":") )
    {
      v14 = idWindow::ParseExpressionPriority(this, src, 3, var, 0);
      *(_DWORD *)(component + 16) = v14;
    }
  }
  v16 = -1;
  idStr::FreeData(&token);
  return v13;
}

// FUNC: public: int __thiscall idWindow::ParseExpression(class idParser *,class idWinVar *,int)
int __thiscall idWindow::ParseExpression(idWindow *this, idParser *src, idWinVar *var, int component)
{
  return idWindow::ParseExpressionPriority(this, src, 4, var, 0);
}

// FUNC: public: void __thiscall idWindow::ReadSaveGameTransition(struct idTransitionData &,class idFile *)
void __thiscall idWindow::ReadSaveGameTransition(idWindow *this, idTransitionData *trans, idFile *savefile)
{
  idFile *v3; // edi
  int granularity; // eax
  bool v6; // cc
  int i; // eax
  int size; // eax
  int num; // ebp
  int v10; // ecx
  int *list; // edi
  int j; // eax
  bool v13; // zf
  idFile *v14; // eax
  idWinVar *v15; // eax
  idWinVar *v16; // esi
  int temp; // [esp+14h] [ebp-30h] BYREF
  idStr winName; // [esp+18h] [ebp-2Ch] BYREF
  int v19; // [esp+40h] [ebp-4h]

  v3 = savefile;
  savefile->Read(savefile, &savefile, 4);
  if ( savefile != (idFile *)-1 )
  {
    winName.len = 0;
    winName.alloced = 20;
    winName.data = winName.baseBuffer;
    winName.baseBuffer[0] = 0;
    v19 = 0;
    idWindow::ReadSaveGameString(this, &winName, v3);
    v3->Read(v3, &trans->interp, 128);
    v3->ReadInt(v3, &temp);
    if ( !this->transitionSubs.list )
    {
      granularity = this->transitionSubs.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->transitionSubs.size )
        {
          v6 = granularity < this->transitionSubs.num;
          this->transitionSubs.size = granularity;
          if ( v6 )
            this->transitionSubs.num = granularity;
          this->transitionSubs.list = (int *)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->transitionSubs.num; ++i )
            this->transitionSubs.list[i] = *(_DWORD *)(4 * i);
        }
      }
      else
      {
        this->transitionSubs.list = 0;
        this->transitionSubs.num = 0;
        this->transitionSubs.size = 0;
      }
    }
    size = this->transitionSubs.size;
    num = this->transitionSubs.num;
    if ( num == size )
    {
      if ( !this->transitionSubs.granularity )
        this->transitionSubs.granularity = 16;
      v10 = size
          + this->transitionSubs.granularity
          - (size + this->transitionSubs.granularity) % this->transitionSubs.granularity;
      if ( v10 > 0 )
      {
        if ( v10 != this->transitionSubs.size )
        {
          list = this->transitionSubs.list;
          this->transitionSubs.size = v10;
          if ( v10 < num )
            this->transitionSubs.num = v10;
          this->transitionSubs.list = (int *)Memory::Allocate(4 * v10);
          for ( j = 0; j < this->transitionSubs.num; ++j )
            this->transitionSubs.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->transitionSubs.list )
          Memory::Free(this->transitionSubs.list);
        this->transitionSubs.list = 0;
        this->transitionSubs.num = 0;
        this->transitionSubs.size = 0;
      }
    }
    this->transitionSubs.list[this->transitionSubs.num++] = temp;
    v13 = winName.len == 0;
    v14 = savefile;
    trans->data = 0;
    trans->offset = (int)v14;
    if ( !v13 )
    {
      v15 = (idWinVar *)Memory::Allocate(0x30u);
      if ( v15 )
      {
        v15->guiDict = 0;
        v15->name = 0;
        v15->eval = 1;
        v15->__vftable = (idWinVar_vtbl *)&idWinStr::`vftable';
        v15[1].__vftable = 0;
        v15[1].name = (char *)20;
        v15[1].guiDict = (idDict *)&v15[1].eval;
        v15[1].eval = 0;
        v16 = v15;
      }
      else
      {
        v16 = 0;
      }
      v16->Set(v16, winName.data);
      trans->data = v16;
    }
    v19 = -1;
    idStr::FreeData(&winName);
  }
}

// FUNC: public: void __thiscall idWindow::AddChild(class idWindow *)
void __thiscall idWindow::AddChild(idWindow *this, idWindow *win)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v8; // ecx
  idWindow **list; // edi
  int j; // eax

  if ( !this->children.list )
  {
    granularity = this->children.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->children.size )
      {
        v4 = granularity < this->children.num;
        this->children.size = granularity;
        if ( v4 )
          this->children.num = granularity;
        this->children.list = (idWindow **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->children.num; ++i )
          this->children.list[i] = *(idWindow **)(4 * i);
      }
    }
    else
    {
      this->children.list = 0;
      this->children.num = 0;
      this->children.size = 0;
    }
  }
  num = this->children.num;
  size = this->children.size;
  if ( num == size )
  {
    if ( !this->children.granularity )
      this->children.granularity = 16;
    v8 = size + this->children.granularity - (size + this->children.granularity) % this->children.granularity;
    if ( v8 > 0 )
    {
      if ( v8 != this->children.size )
      {
        list = this->children.list;
        this->children.size = v8;
        if ( v8 < num )
          this->children.num = v8;
        this->children.list = (idWindow **)Memory::Allocate(4 * v8);
        for ( j = 0; j < this->children.num; ++j )
          this->children.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->children.list )
        Memory::Free(this->children.list);
      this->children.list = 0;
      this->children.num = 0;
      this->children.size = 0;
    }
  }
  this->children.list[this->children.num++] = win;
  win->childID = this->children.num - 1;
}

// FUNC: public: void __thiscall idWindow::RemoveChild(class idWindow *)
void __thiscall idWindow::RemoveChild(idWindow *this, idWindow *win)
{
  int num; // esi
  int v3; // eax
  idWindow **list; // edx
  idWindow **v5; // edx
  idWindow *v6; // esi
  idWindow **v7; // edx
  int v8; // esi
  int v9; // eax
  drawWin_t *i; // edx
  int v11; // edx
  bool v12; // cc
  int v13; // edx
  drawWin_t *v14; // eax
  idWindow *v15; // esi
  drawWin_t *v16; // eax

  num = this->children.num;
  v3 = 0;
  if ( num > 0 )
  {
    list = this->children.list;
    while ( *list != win )
    {
      ++v3;
      ++list;
      if ( v3 >= this->children.num )
        goto LABEL_10;
    }
    if ( v3 >= 0 && v3 < num )
    {
      for ( this->children.num = num - 1; v3 < this->children.num; *v7 = v6 )
      {
        v5 = this->children.list;
        v6 = v5[v3 + 1];
        v7 = &v5[v3++];
      }
    }
  }
LABEL_10:
  v8 = this->drawWindows.num;
  v9 = 0;
  if ( v8 > 0 )
  {
    for ( i = this->drawWindows.list; i->win != win; ++i )
    {
      if ( ++v9 >= v8 )
        return;
    }
    if ( v9 >= 0 )
    {
      v11 = this->drawWindows.num;
      if ( v9 < v11 )
      {
        v12 = v9 < v11 - 1;
        this->drawWindows.num = v11 - 1;
        v13 = v9;
        if ( v12 )
        {
          do
          {
            v14 = this->drawWindows.list;
            v15 = v14[v13 + 1].win;
            v16 = &v14[v13];
            v16->win = v15;
            ++v13;
            v16->simp = v16[1].simp;
          }
          while ( v13 < this->drawWindows.num );
        }
      }
    }
  }
}

// FUNC: public: bool __thiscall idWindow::InsertChild(class idWindow *,class idWindow *)
int __thiscall idWindow::InsertChild(idWindow *this, idWindow *win, idWindow *before)
{
  int num; // ecx
  int v5; // ebx
  drawWin_t *list; // eax
  int granularity; // eax
  int v8; // edi
  int v9; // eax
  bool v10; // cc
  int k; // eax
  drawWin_t *v12; // ecx
  int v13; // eax
  int v14; // ebp
  int v15; // ecx
  drawWin_t *v16; // edi
  int m; // eax
  drawWin_t *v18; // ecx
  int n; // ecx
  drawWin_t *v20; // eax
  idWindow *v21; // edx
  drawWin_t *v22; // eax
  drawWin_t *v23; // ecx
  int result; // eax
  int i; // eax
  drawWin_t *v26; // ecx
  int size; // eax
  int v28; // ebp
  int v29; // ecx
  drawWin_t *v30; // edi
  int j; // eax
  drawWin_t *v32; // ecx
  int v33; // ecx
  drawWin_t *v34; // edx

  idWindow::AddChild(this, win);
  win->parent = this;
  if ( !before )
    goto LABEL_6;
  num = this->drawWindows.num;
  v5 = 0;
  if ( num <= 0 )
    goto LABEL_6;
  list = this->drawWindows.list;
  while ( list->win != before )
  {
    ++v5;
    ++list;
    if ( v5 >= num )
      goto LABEL_6;
  }
  if ( v5 == -1 )
  {
LABEL_6:
    if ( !this->drawWindows.list )
    {
      granularity = this->drawWindows.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->drawWindows.size )
        {
          v10 = granularity < this->drawWindows.num;
          this->drawWindows.size = granularity;
          if ( v10 )
            this->drawWindows.num = granularity;
          this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * granularity);
          for ( i = 0; i < this->drawWindows.num; ++i )
          {
            v26 = this->drawWindows.list;
            v26[i].win = *(idWindow **)(8 * i);
            v26[i].simp = *(idSimpleWindow **)(8 * i + 4);
          }
        }
      }
      else
      {
        this->drawWindows.list = 0;
        this->drawWindows.num = 0;
        this->drawWindows.size = 0;
      }
    }
    size = this->drawWindows.size;
    v28 = this->drawWindows.num;
    if ( v28 == size )
    {
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v29 = size
          + this->drawWindows.granularity
          - (size + this->drawWindows.granularity) % this->drawWindows.granularity;
      if ( v29 > 0 )
      {
        if ( v29 != this->drawWindows.size )
        {
          v30 = this->drawWindows.list;
          this->drawWindows.size = v29;
          if ( v29 < v28 )
            this->drawWindows.num = v29;
          this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v29);
          for ( j = 0; j < this->drawWindows.num; ++j )
          {
            v32 = this->drawWindows.list;
            v32[j].win = v30[j].win;
            v32[j].simp = v30[j].simp;
          }
          if ( v30 )
            Memory::Free(v30);
        }
      }
      else
      {
        if ( this->drawWindows.list )
          Memory::Free(this->drawWindows.list);
        this->drawWindows.list = 0;
        this->drawWindows.num = 0;
        this->drawWindows.size = 0;
      }
    }
    v33 = this->drawWindows.num;
    v34 = this->drawWindows.list;
    v34[v33].win = win;
    result = 1;
    v34[v33].simp = 0;
    ++this->drawWindows.num;
  }
  else
  {
    v8 = v5;
    if ( !this->drawWindows.list )
    {
      v9 = this->drawWindows.granularity;
      if ( v9 > 0 )
      {
        if ( v9 != this->drawWindows.size )
        {
          v10 = v9 < this->drawWindows.num;
          this->drawWindows.size = v9;
          if ( v10 )
            this->drawWindows.num = v9;
          this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v9);
          for ( k = 0; k < this->drawWindows.num; ++k )
          {
            v12 = this->drawWindows.list;
            v12[k].win = *(idWindow **)(8 * k);
            v12[k].simp = *(idSimpleWindow **)(8 * k + 4);
          }
        }
      }
      else
      {
        this->drawWindows.list = 0;
        this->drawWindows.num = 0;
        this->drawWindows.size = 0;
      }
    }
    v13 = this->drawWindows.size;
    v14 = this->drawWindows.num;
    if ( v14 == v13 )
    {
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v15 = v13 + this->drawWindows.granularity - (v13 + this->drawWindows.granularity) % this->drawWindows.granularity;
      if ( v15 > 0 )
      {
        if ( v15 != this->drawWindows.size )
        {
          v16 = this->drawWindows.list;
          this->drawWindows.size = v15;
          if ( v15 < v14 )
            this->drawWindows.num = v15;
          this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v15);
          for ( m = 0; m < this->drawWindows.num; ++m )
          {
            v18 = this->drawWindows.list;
            v18[m].win = v16[m].win;
            v18[m].simp = v16[m].simp;
          }
          if ( v16 )
            Memory::Free(v16);
        }
      }
      else
      {
        if ( this->drawWindows.list )
          Memory::Free(this->drawWindows.list);
        this->drawWindows.list = 0;
        this->drawWindows.num = 0;
        this->drawWindows.size = 0;
      }
      v8 = v5;
    }
    if ( v5 >= 0 )
    {
      if ( v5 > this->drawWindows.num )
        v8 = this->drawWindows.num;
    }
    else
    {
      v8 = 0;
    }
    for ( n = this->drawWindows.num; n > v8; v22->simp = v22[-1].simp )
    {
      v20 = this->drawWindows.list;
      v21 = v20[n - 1].win;
      v22 = &v20[n];
      v22->win = v21;
      --n;
    }
    ++this->drawWindows.num;
    v23 = this->drawWindows.list;
    v23[v8].win = win;
    result = 1;
    v23[v8].simp = 0;
  }
  return result;
}

// FUNC: protected: void __thiscall idWindow::SetDefaults(void)
void __thiscall idWindow::SetDefaults(idWindow *this)
{
  int v2; // eax
  char v3; // cl
  int v4; // eax
  char v5; // cl
  bool other; // [esp+Bh] [ebp-51h] BYREF
  float v7; // [esp+Ch] [ebp-50h] BYREF
  idStr v8; // [esp+10h] [ebp-4Ch] BYREF
  idStr v9; // [esp+30h] [ebp-2Ch] BYREF
  int v10; // [esp+58h] [ebp-4h]

  this->matScalex = 1.0;
  this->matScaley = 1.0;
  this->forceAspectWidth = 640.0;
  this->forceAspectHeight = 480.0;
  this->borderSize = 0.0;
  other = 0;
  idWinBool::operator=(&this->noTime, &other);
  other = 1;
  idWinBool::operator=(&this->visible, &other);
  this->textAlign = 0;
  this->textAlignx = 0.0;
  this->textAligny = 0.0;
  this->textStyle = 0;
  this->textSpacing = 0.0;
  other = 0;
  idWinBool::operator=(&this->noEvents, &other);
  v7 = 0.0;
  idWinFloat::operator=(&this->rotate, &v7);
  this->shear.y = 0.0;
  this->shear.x = 0.0;
  v7 = 0.34999999;
  idWinFloat::operator=(&this->textScale, &v7);
  idWinVec4::Zero(&this->backColor);
  v8.len = 1065353216;
  v8.data = (char *)1065353216;
  v8.alloced = 1065353216;
  *(_DWORD *)v8.baseBuffer = 1065353216;
  idWinVec4::operator=(&this->foreColor, (const idVec4 *)&v8);
  v8.len = 1065353216;
  v8.data = (char *)1065353216;
  v8.alloced = 1065353216;
  *(_DWORD *)v8.baseBuffer = 1065353216;
  idWinVec4::operator=(&this->hoverColor, (const idVec4 *)&v8);
  v8.len = 1065353216;
  v8.data = (char *)1065353216;
  v8.alloced = 1065353216;
  *(_DWORD *)v8.baseBuffer = 1065353216;
  idWinVec4::operator=(&this->matColor, (const idVec4 *)&v8);
  idWinVec4::Zero(&this->borderColor);
  v8.alloced = 20;
  v8.data = v8.baseBuffer;
  v8.baseBuffer[0] = 0;
  v2 = 0;
  do
  {
    v3 = *(&entityFilter + v2);
    v8.baseBuffer[v2++] = v3;
  }
  while ( v3 );
  v8.len = 0;
  v10 = 0;
  idWinStr::operator=(&this->text, &v8);
  v10 = -1;
  idStr::FreeData(&v8);
  this->background = 0;
  v9.alloced = 20;
  v9.data = v9.baseBuffer;
  v9.baseBuffer[0] = 0;
  v4 = 0;
  do
  {
    v5 = *(&entityFilter + v4);
    v9.baseBuffer[v4++] = v5;
  }
  while ( v5 );
  v9.len = 0;
  v10 = 1;
  idWinBackground::operator=(&this->backGroundName, &v9);
  v10 = -1;
  idStr::FreeData(&v9);
}

// FUNC: public: bool __thiscall idWindow::UpdateFromDictionary(class idDict &)
char __thiscall idWindow::UpdateFromDictionary(idWindow *this, idDict *dict)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  int num; // eax
  int v5; // edi
  idKeyValue *v6; // esi
  const idPoolStr *value; // edi
  unsigned int len; // esi
  int v9; // eax
  idWindow_vtbl *v10; // edx
  bool v11; // zf
  char *data; // [esp-10h] [ebp-ECh]
  int i; // [esp+8h] [ebp-D4h]
  int v15; // [esp+Ch] [ebp-D0h]
  idParser src; // [esp+10h] [ebp-CCh] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v17; // [esp+D0h] [ebp-Ch]
  void *v18; // [esp+D4h] [ebp-8h]
  int v19; // [esp+D8h] [ebp-4h]

  v19 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v18 = &_ehhandler__UpdateFromDictionary_idWindow__QAE_NAAVidDict___Z;
  v17 = ExceptionList;
  idWindow::SetDefaults(this);
  idRegisterList::Reset(&this->regList);
  if ( this->expressionRegisters.list )
    Memory::Free(this->expressionRegisters.list);
  this->expressionRegisters.list = 0;
  this->expressionRegisters.num = 0;
  this->expressionRegisters.size = 0;
  if ( this->ops.list )
    Memory::Free(this->ops.list);
  this->ops.list = 0;
  this->ops.num = 0;
  this->ops.size = 0;
  num = dict->args.num;
  v5 = 0;
  for ( i = 0; v5 < dict->args.num; i = v5 )
  {
    if ( v5 < 0 || v5 >= num )
      v6 = 0;
    else
      v6 = &dict->args.list[v5];
    if ( idStr::Icmp(v6->key->data, "name") )
    {
      idParser::idParser(&src, v6->value->data, v6->value->len, &entityFilter, 6156);
      v10 = this->__vftable;
      data = v6->key->data;
      v19 = 0;
      if ( !v10->ParseInternalVar(this, data, &src) )
        idWindow::ParseRegEntry(this, v6->key->data, &src);
      v19 = -1;
      idParser::~idParser(&src);
    }
    else
    {
      value = v6->value;
      len = value->len;
      v9 = value->len + 1;
      v15 = value->len;
      if ( v9 > this->name.alloced )
        idStr::ReAllocate(&this->name, v9, 0);
      qmemcpy(this->name.data, value->data, len);
      v5 = i;
      this->name.data[v15] = 0;
      this->name.len = v15;
    }
    num = dict->args.num;
    ++v5;
  }
  v11 = this->expressionRegisters.num == 0;
  lastEval = this;
  if ( !v11 )
  {
    idRegisterList::SetToRegs(&this->regList, regs);
    idWindow::EvaluateRegisters(this, regs);
    idRegisterList::GetFromRegs(&this->regList, regs);
  }
  idWindow::SetupFromState(this);
  this->PostParse(this);
  return 1;
}

// FUNC: public: void __thiscall idWindow::SetWrapper(int)
void __thiscall idWindow::SetWrapper(idWindow *this, int wrapper)
{
  idWinInt *v3; // eax
  idWinInt *v4; // edi
  int granularity; // eax
  bool v6; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v10; // ecx
  idWinVar **list; // edi
  int j; // eax
  idWinInt *v13; // [esp+10h] [ebp-4h]

  v3 = (idWinInt *)Memory::Allocate(0x14u);
  if ( v3 )
  {
    v4 = v3;
    v3->guiDict = 0;
    v3->name = 0;
    v3->eval = 1;
    v3->__vftable = (idWinInt_vtbl *)&idWinInt::`vftable';
    v13 = v3;
  }
  else
  {
    v13 = 0;
    v4 = 0;
  }
  idWinInt::operator=(v4, &wrapper);
  v4->SetEval(v4, 0);
  idWinVar::SetName(v4, "guied_wrapper");
  if ( !this->definedVars.list )
  {
    granularity = this->definedVars.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->definedVars.size )
      {
        v6 = granularity < this->definedVars.num;
        this->definedVars.size = granularity;
        if ( v6 )
          this->definedVars.num = granularity;
        this->definedVars.list = (idWinVar **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->definedVars.num; ++i )
          this->definedVars.list[i] = *(idWinVar **)(4 * i);
      }
    }
    else
    {
      this->definedVars.list = 0;
      this->definedVars.num = 0;
      this->definedVars.size = 0;
    }
  }
  num = this->definedVars.num;
  size = this->definedVars.size;
  if ( num == size )
  {
    if ( !this->definedVars.granularity )
      this->definedVars.granularity = 16;
    v10 = size + this->definedVars.granularity - (size + this->definedVars.granularity) % this->definedVars.granularity;
    if ( v10 > 0 )
    {
      if ( v10 != this->definedVars.size )
      {
        list = this->definedVars.list;
        this->definedVars.size = v10;
        if ( v10 < num )
          this->definedVars.num = v10;
        this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v10);
        for ( j = 0; j < this->definedVars.num; ++j )
          this->definedVars.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->definedVars.list )
        Memory::Free(this->definedVars.list);
      this->definedVars.list = 0;
      this->definedVars.num = 0;
      this->definedVars.size = 0;
    }
    v4 = v13;
  }
  this->definedVars.list[this->definedVars.num++] = v4;
}

// FUNC: class idWindow * __cdecl CreateNewWindow(int,class idDeviceContext *,class idUserInterface *)
void __cdecl CreateNewWindow(int type, idDeviceContext *d, idUserInterfaceLocal *gui)
{
  idWindow *v3; // eax
  idBindWindow *v4; // eax
  idRenderWindow *v5; // eax
  idGraphWindow *v6; // eax
  idChoiceWindow *v7; // eax
  idEditWindow *v8; // eax
  idSliderWindow *v9; // eax
  idListWindow *v10; // eax
  rvPopupWindow *v11; // eax

  switch ( type )
  {
    case 1:
      v3 = (idWindow *)Memory::Allocate(0x418u);
      if ( v3 )
        idWindow::idWindow(v3, d, gui);
      break;
    case 2:
      v8 = (idEditWindow *)Memory::Allocate(0x500u);
      if ( v8 )
        idEditWindow::idEditWindow(v8, d, gui);
      break;
    case 3:
      v7 = (idChoiceWindow *)Memory::Allocate(0x5CCu);
      if ( v7 )
        idChoiceWindow::idChoiceWindow(v7, d, gui);
      break;
    case 4:
      v9 = (idSliderWindow *)Memory::Allocate(0x4FCu);
      if ( v9 )
        idSliderWindow::idSliderWindow(v9, d, gui);
      break;
    case 5:
      v4 = (idBindWindow *)Memory::Allocate(0x44Cu);
      if ( v4 )
        idBindWindow::idBindWindow(v4, d, gui);
      break;
    case 6:
      v10 = (idListWindow *)Memory::Allocate(0x678u);
      if ( v10 )
        idListWindow::idListWindow(v10, d, gui);
      break;
    case 7:
      v5 = (idRenderWindow *)Memory::Allocate(0x1034u);
      if ( v5 )
        idRenderWindow::idRenderWindow(v5, d, gui);
      break;
    case 8:
      v6 = (idGraphWindow *)Memory::Allocate(0x550u);
      if ( v6 )
        idGraphWindow::idGraphWindow(v6, d, gui);
      break;
    case 9:
      v11 = (rvPopupWindow *)Memory::Allocate(0x65Cu);
      if ( v11 )
        rvPopupWindow::rvPopupWindow(v11, d, gui);
      break;
    default:
      return;
  }
}

// FUNC: private: virtual void __thiscall rvWindowEditLocal::SetWrapper(class idWindow *,int)
void __thiscall rvWindowEditLocal::SetWrapper(rvWindowEditLocal *this, idWindow *edit, int wrapper)
{
  idWindow::SetWrapper(edit, wrapper);
}

// FUNC: private: virtual void __thiscall rvWindowEditLocal::InsertChild(class idWindow *,class idWindow *,class idWindow *)
void __thiscall rvWindowEditLocal::InsertChild(
        rvWindowEditLocal *this,
        idWindow *edit,
        idWindow *current,
        idWindow *before)
{
  idWindow::InsertChild(edit, current, before);
}

// FUNC: private: virtual void __thiscall rvWindowEditLocal::RemoveChild(class idWindow *,class idWindow *)
void __thiscall rvWindowEditLocal::RemoveChild(rvWindowEditLocal *this, idWindow *edit, idWindow *current)
{
  idWindow::RemoveChild(edit, current);
}

// FUNC: private: virtual bool __thiscall rvWindowEditLocal::UpdateFromDictionary(class idWindow *,class idDict &)
char __thiscall rvWindowEditLocal::UpdateFromDictionary(rvWindowEditLocal *this, idWindow *edit, idDict *dict)
{
  return idWindow::UpdateFromDictionary(edit, dict);
}

// FUNC: private: virtual bool __thiscall rvWindowEditLocal::ParseRegEntry(class idWindow *,char const *,class idParser *)
char __thiscall rvWindowEditLocal::ParseRegEntry(rvWindowEditLocal *this, idWindow *edit, char *name, idParser *src)
{
  return idWindow::ParseRegEntry(edit, name, src);
}

// FUNC: private: virtual class idWindow * __thiscall rvWindowEditLocal::CreateNewWindow(int,class idDeviceContext *,class idUserInterface *)
idWindow *__thiscall rvWindowEditLocal::CreateNewWindow(
        rvWindowEditLocal *this,
        int type,
        idDeviceContext *d,
        idUserInterface *gui)
{
  return CreateNewWindow(type, d, gui);
}

// FUNC: public: virtual char const * __thiscall idWindow::RouteMouseCoords(float,float)
const char *__thiscall idWindow::RouteMouseCoords(idWindow *this, float xd, float yd)
{
  bool v4; // zf
  idWindow *captureChild; // eax
  int v6; // esi
  int num; // edi
  idWindow *v9; // ebx
  idUserInterfaceLocal *gui; // esi
  idWindow *overChild; // ecx
  idWindow *v12; // esi
  unsigned int len; // ebx
  idStr *p_cmd; // esi
  idWindow *v15; // eax
  idWindow *v16; // ecx
  idWindow *v17; // esi
  unsigned int v18; // edi
  idStr *v19; // esi
  idWindow *v20; // eax
  idWindow *v21; // esi
  unsigned int v22; // ebx
  idStr *v23; // esi
  idWindow *v24; // eax
  float x; // [esp+0h] [ebp-48h]
  float y; // [esp+4h] [ebp-44h]
  char *ya; // [esp+4h] [ebp-44h]
  char *yb; // [esp+4h] [ebp-44h]
  char *yc; // [esp+4h] [ebp-44h]
  idStr str; // [esp+1Ch] [ebp-2Ch] BYREF
  int v31; // [esp+44h] [ebp-4h]

  str.len = 0;
  str.alloced = 20;
  str.data = str.baseBuffer;
  str.baseBuffer[0] = 0;
  v4 = (this->flags & 0x10000000) == 0;
  v31 = 0;
  if ( v4 || !this->gui->GetDesktop(this->gui)->captureChild )
  {
    if ( xd != -2000.0 && yd != -2000.0 )
    {
      num = this->children.num;
      if ( num <= 0 )
      {
LABEL_14:
        overChild = this->overChild;
        if ( overChild )
        {
          overChild->MouseExit(overChild);
          v12 = this->overChild;
          len = v12->cmd.len;
          p_cmd = &v12->cmd;
          if ( (int)(len + 1) > str.alloced )
            idStr::ReAllocate(&str, len + 1, 0);
          qmemcpy(str.data, p_cmd->data, len);
          str.data[len] = 0;
          str.len = len;
          if ( len )
          {
            ya = str.data;
            v15 = this->gui->GetDesktop(this->gui);
            idWindow::AddCommand(v15, ya);
            idStr::operator=(&this->overChild->cmd, (char *)&entityFilter);
          }
          this->overChild = 0;
        }
      }
      else
      {
        while ( 1 )
        {
          v9 = this->children.list[--num];
          if ( v9->visible.data && !v9->noEvents.data )
          {
            gui = this->gui;
            y = gui->CursorY(gui);
            x = gui->CursorX(gui);
            if ( idWindow::Contains(v9, &v9->drawRect, x, y) )
              break;
          }
          if ( num <= 0 )
            goto LABEL_14;
        }
        idDeviceContext::SetCursor(this->dc, v9->cursor);
        v9->hover = 1;
        v16 = this->overChild;
        if ( v16 == v9 )
        {
          if ( (v9->flags & 0x4000) == 0 )
            ((void (__thiscall *)(idWindow *, _DWORD, _DWORD))v9->RouteMouseCoords)(v9, LODWORD(xd), LODWORD(yd));
        }
        else
        {
          if ( v16 )
          {
            v16->MouseExit(v16);
            v17 = this->overChild;
            v18 = v17->cmd.len;
            v19 = &v17->cmd;
            if ( (int)(v18 + 1) > str.alloced )
              idStr::ReAllocate(&str, v18 + 1, 0);
            qmemcpy(str.data, v19->data, v18);
            str.data[v18] = 0;
            str.len = v18;
            if ( v18 )
            {
              yb = str.data;
              v20 = this->gui->GetDesktop(this->gui);
              idWindow::AddCommand(v20, yb);
              idStr::operator=(&this->overChild->cmd, (char *)&entityFilter);
            }
          }
          this->overChild = v9;
          v9->MouseEnter(v9);
          v21 = this->overChild;
          v22 = v21->cmd.len;
          v23 = &v21->cmd;
          if ( (int)(v22 + 1) > str.alloced )
            idStr::ReAllocate(&str, v22 + 1, 0);
          qmemcpy(str.data, v23->data, v22);
          str.data[v22] = 0;
          str.len = v22;
          if ( v22 )
          {
            yc = str.data;
            v24 = this->gui->GetDesktop(this->gui);
            idWindow::AddCommand(v24, yc);
            idStr::operator=(&this->overChild->cmd, (char *)&entityFilter);
          }
        }
      }
    }
    v31 = -1;
    idStr::FreeData(&str);
    return &entityFilter;
  }
  else
  {
    if ( (this->flags & 0x10000000) != 0 )
      captureChild = this->gui->GetDesktop(this->gui)->captureChild;
    else
      captureChild = 0;
    v6 = ((int (__thiscall *)(idWindow *, _DWORD, _DWORD))captureChild->RouteMouseCoords)(
           captureChild,
           LODWORD(xd),
           LODWORD(yd));
    v31 = -1;
    idStr::FreeData(&str);
    return (const char *)v6;
  }
}

// FUNC: public: virtual bool __thiscall idWindow::RunControllerScript(int,struct sysEvent_s const *,bool *)
char __thiscall idWindow::RunControllerScript(idWindow *this, int script, const sysEvent_s *event, bool *updateVisuals)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  char v6; // bl
  idWindow *focusedChild; // esi
  idWindow *v8; // ecx
  idWindow_vtbl *v9; // edx
  idWindow *v10; // ebx
  unsigned int len; // edi
  idStr *p_cmd; // esi
  idWindow *v13; // eax
  idWindow *overChild; // esi
  unsigned int v15; // ebx
  idStr *v16; // esi
  idWindow *v17; // eax
  idWindow *v18; // eax
  idWindow *parent; // ecx
  char *data; // [esp-10h] [ebp-48h]
  char *v22; // [esp-10h] [ebp-48h]
  idStr str; // [esp+Ch] [ebp-2Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v24; // [esp+2Ch] [ebp-Ch]
  void *v25; // [esp+30h] [ebp-8h]
  int v26; // [esp+34h] [ebp-4h]

  v26 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v25 = &_ehhandler__RouteJoystickChange_idWindow__UAE_NHH_Z;
  v24 = ExceptionList;
  v6 = 0;
  if ( (this->flags & 0x10000000) == 0 )
    return v6;
  focusedChild = this->gui->GetDesktop(this->gui)->focusedChild;
  if ( !focusedChild )
    return v6;
  if ( focusedChild->visible.data && ((v8 = focusedChild->parent) == 0 || idWindow::IsVisible(v8))
    || (focusedChild = this->overChild) != 0 && idWindow::IsVisible(this->overChild) )
  {
    str.len = 0;
    str.alloced = 20;
    str.data = str.baseBuffer;
    str.baseBuffer[0] = 0;
    v9 = focusedChild->__vftable;
    v26 = 0;
    if ( v9->RunScript(focusedChild, script) )
    {
      if ( (this->flags & 0x10000000) != 0 )
      {
        v10 = this->gui->GetDesktop(this->gui)->focusedChild;
        if ( v10 )
        {
          idDeviceContext::SetCursor(this->dc, v10->cursor);
          v10->hover = 1;
          focusedChild->MouseExit(focusedChild);
          len = focusedChild->cmd.len;
          p_cmd = &focusedChild->cmd;
          if ( (int)(len + 1) > str.alloced )
            idStr::ReAllocate(&str, len + 1, 0);
          qmemcpy(str.data, p_cmd->data, len);
          str.data[len] = 0;
          str.len = len;
          if ( len )
          {
            data = str.data;
            v13 = this->gui->GetDesktop(this->gui);
            idWindow::AddCommand(v13, data);
            idStr::operator=(p_cmd, (char *)&entityFilter);
          }
          this->overChild = v10;
          v10->MouseEnter(v10);
          overChild = this->overChild;
          v15 = overChild->cmd.len;
          v16 = &overChild->cmd;
          if ( (int)(v15 + 1) > str.alloced )
            idStr::ReAllocate(&str, v15 + 1, 0);
          qmemcpy(str.data, v16->data, v15);
          str.data[v15] = 0;
          str.len = v15;
          if ( v15 )
          {
            v22 = str.data;
            v17 = this->gui->GetDesktop(this->gui);
            idWindow::AddCommand(v17, v22);
            idStr::operator=(&this->overChild->cmd, (char *)&entityFilter);
          }
          v18 = this->overChild;
          parent = v18->parent;
          if ( parent )
          {
            if ( gui_debugScript.internalVar->integerValue )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                common.type,
                "\nSetting %s to have overchild %s (%08x) at (%d,%d)\n",
                parent->name.data,
                v18->name.data);
            this->overChild->parent->overChild = this->overChild;
          }
        }
      }
      v26 = -1;
      idStr::FreeData(&str);
      return 1;
    }
    v26 = -1;
    idStr::FreeData(&str);
  }
  return 0;
}

// FUNC: public: virtual bool __thiscall idWindow::RouteJoystickChange(int,int)
char __thiscall idWindow::RouteJoystickChange(idWindow *this, int xd, int yd)
{
  idWindow *v4; // ebx
  bool v5; // zf
  idWindow *captureChild; // eax
  bool v7; // bl
  idWindow *overChild; // edx
  idWindow *v10; // edx
  idWindow *v11; // esi
  unsigned int len; // ebx
  idStr *p_cmd; // esi
  int num; // edi
  idWindow *v15; // esi
  double actualY; // st7
  int v17; // eax
  int v18; // edi
  bool v19; // sf
  idWindow *v20; // ecx
  idWindow *v21; // esi
  unsigned int v22; // ebx
  idStr *v23; // esi
  idWindow *v24; // eax
  idWindow *v25; // esi
  idWindow *v26; // eax
  char *v27; // [esp-4h] [ebp-64h]
  char *data; // [esp-4h] [ebp-64h]
  idWindow *best; // [esp+14h] [ebp-4Ch]
  int bestY; // [esp+18h] [ebp-48h]
  int startY; // [esp+1Ch] [ebp-44h]
  int bestX; // [esp+20h] [ebp-40h]
  int startX; // [esp+24h] [ebp-3Ch]
  int testX; // [esp+28h] [ebp-38h]
  int c; // [esp+2Ch] [ebp-34h]
  idStr str; // [esp+34h] [ebp-2Ch] BYREF
  int v37; // [esp+5Ch] [ebp-4h]

  str.len = 0;
  str.alloced = 20;
  str.data = str.baseBuffer;
  str.baseBuffer[0] = 0;
  v4 = 0;
  v5 = (this->flags & 0x10000000) == 0;
  v37 = 0;
  best = 0;
  if ( !v5 && this->gui->GetDesktop(this->gui)->captureChild )
  {
    if ( (this->flags & 0x10000000) != 0 )
      captureChild = this->gui->GetDesktop(this->gui)->captureChild;
    else
      captureChild = 0;
    v7 = captureChild->RouteJoystickChange(captureChild, xd, yd);
    v37 = -1;
    idStr::FreeData(&str);
    return v7;
  }
  overChild = this->overChild;
  bestY = 0;
  bestX = 0;
  if ( overChild && idWindow::IsVisible(overChild) && !v10->noEvents.data && v10->scripts[0] )
  {
    if ( !xd && !yd )
    {
      idWindow::SetFocus(this, v10, 1);
      idDeviceContext::SetCursor(this->dc, this->overChild->cursor);
      this->overChild->hover = 1;
      this->overChild->MouseEnter(this->overChild);
      v11 = this->overChild;
      len = v11->cmd.len;
      p_cmd = &v11->cmd;
      if ( (int)(len + 1) > str.alloced )
        idStr::ReAllocate(&str, len + 1, 0);
LABEL_67:
      qmemcpy(str.data, p_cmd->data, len);
      str.data[len] = 0;
      str.len = len;
      if ( len )
      {
        data = str.data;
        v26 = this->gui->GetDesktop(this->gui);
        idWindow::AddCommand(v26, data);
        idStr::operator=(&this->overChild->cmd, (char *)&entityFilter);
      }
LABEL_69:
      v37 = -1;
      idStr::FreeData(&str);
      return 1;
    }
    startX = (int)v10->actualX;
    startY = (int)v10->actualY;
    if ( gui_debugScript.internalVar->integerValue )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "\nRoutJoystickChange: %s has overChild %s (%08x) at (%d,%d)\n",
        this->name.data,
        v10->name.data,
        v10,
        startX,
        startY);
      v4 = 0;
    }
  }
  else
  {
    startY = 0;
    startX = 0;
  }
  num = this->children.num;
  if ( num <= 0 )
    goto LABEL_72;
  do
  {
    v15 = this->children.list[--num];
    c = num;
    if ( !v15->visible.data )
      continue;
    if ( !v15->noEvents.data && v15->scripts[0] && v15 != this->overChild )
    {
      testX = (int)v15->actualX;
      actualY = v15->actualY;
      v17 = testX;
      v18 = (int)actualY;
      if ( gui_debugScript.internalVar->integerValue )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "Examing %s at (%08x) at (%d,%d)\n",
          v15->name.data,
          v15,
          testX,
          (int)actualY);
        v17 = testX;
      }
      if ( yd )
      {
        if ( yd > 0 && v18 > startY && (!v4 || v18 < bestY) )
        {
          bestY = (int)actualY;
          goto LABEL_50;
        }
        if ( yd < 0 && v18 < startY && (!v4 || v18 > bestY) )
        {
          bestY = (int)actualY;
          goto LABEL_50;
        }
      }
      else if ( v18 > startY && (!v4 || v18 < bestY) )
      {
        bestY = (int)actualY;
LABEL_50:
        best = v15;
        v4 = v15;
LABEL_51:
        if ( gui_debugScript.internalVar->integerValue && v4 == v15 )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "   Best Yet\n");
        num = c;
        continue;
      }
      v19 = xd < 0;
      if ( xd > 0 )
      {
        if ( v17 > startX && (!v4 || v17 < bestX) )
        {
LABEL_49:
          bestX = v17;
          goto LABEL_50;
        }
        v19 = xd < 0;
      }
      if ( !v19 || v17 >= startX || v4 && v17 <= bestX )
        goto LABEL_51;
      goto LABEL_49;
    }
    if ( v15->RouteJoystickChange(v15, xd, yd) )
      goto LABEL_69;
  }
  while ( num > 0 );
  if ( v4 )
  {
    if ( gui_debugScript.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "FINAL: %s (%08x) at (%d,%d)\n",
        v4->name.data,
        v4,
        bestX,
        bestY);
    idWindow::SetFocus(this, v4, 1);
    idDeviceContext::SetCursor(this->dc, v4->cursor);
    v4->hover = 1;
    v20 = this->overChild;
    if ( v20 )
    {
      v20->MouseExit(v20);
      v21 = this->overChild;
      v22 = v21->cmd.len;
      v23 = &v21->cmd;
      if ( (int)(v22 + 1) > str.alloced )
        idStr::ReAllocate(&str, v22 + 1, 0);
      qmemcpy(str.data, v23->data, v22);
      str.data[v22] = 0;
      str.len = v22;
      if ( v22 )
      {
        v27 = str.data;
        v24 = this->gui->GetDesktop(this->gui);
        idWindow::AddCommand(v24, v27);
        idStr::operator=(&this->overChild->cmd, (char *)&entityFilter);
      }
      v4 = best;
    }
    this->overChild = v4;
    v4->MouseEnter(v4);
    v25 = this->overChild;
    len = v25->cmd.len;
    p_cmd = &v25->cmd;
    if ( (int)(len + 1) > str.alloced )
      idStr::ReAllocate(&str, len + 1, 0);
    goto LABEL_67;
  }
LABEL_72:
  v37 = -1;
  idStr::FreeData(&str);
  return 0;
}

// FUNC: public: virtual void __thiscall idWindow::StateChanged(bool)
void __thiscall idWindow::StateChanged(idWindow *this, BOOL redraw)
{
  int num; // ebx
  int i; // edi
  idWinVar *v5; // ecx
  int v6; // ebp
  int j; // edi
  drawWin_t *list; // eax
  idWindow *win; // ecx
  drawWin_t *v10; // eax
  idMaterial *background; // ecx

  num = this->updateVars.num;
  for ( i = 0; i < num; ++i )
  {
    v5 = this->updateVars.list[i];
    v5->Update(v5);
  }
  if ( this->expressionRegisters.num && this->ops.num )
  {
    lastEval = this;
    idRegisterList::SetToRegs(&this->regList, regs);
    idWindow::EvaluateRegisters(this, regs);
    idRegisterList::GetFromRegs(&this->regList, regs);
  }
  v6 = this->drawWindows.num;
  for ( j = 0; j < v6; ++j )
  {
    list = this->drawWindows.list;
    win = list[j].win;
    v10 = &list[j];
    if ( win )
      win->StateChanged(win, redraw);
    else
      idSimpleWindow::StateChanged(v10->simp, redraw);
  }
  if ( redraw )
  {
    if ( (this->flags & 0x10000000) != 0 )
      ((void (__thiscall *)(idWindow *, _DWORD, _DWORD))this->Redraw)(this, 0, 0);
    background = (idMaterial *)this->background;
    if ( background )
    {
      if ( idMaterial::CinematicLength(background) )
        idMaterial::UpdateCinematic((idMaterial *)this->background, this->gui->time);
    }
  }
}

// FUNC: public: virtual void __thiscall idWindow::RunNamedEvent(char const *)
void __thiscall idWindow::RunNamedEvent(idWindow *this, const char *eventName)
{
  int num; // edi
  int v4; // ebx
  int v5; // ebp
  int i; // edi
  idWinVar *v7; // ecx
  idGuiScriptList *mEvent; // ecx
  int v9; // ebx
  int j; // edi
  idWindow *v11; // ecx

  num = this->namedEvents.num;
  v4 = 0;
  if ( num > 0 )
  {
    while ( idStr::Icmp(this->namedEvents.list[v4]->mName.data, eventName) )
    {
      if ( ++v4 >= num )
        goto LABEL_12;
    }
    v5 = this->updateVars.num;
    for ( i = 0; i < v5; ++i )
    {
      v7 = this->updateVars.list[i];
      v7->Update(v7);
    }
    if ( this->expressionRegisters.num && this->ops.num )
    {
      lastEval = this;
      idRegisterList::SetToRegs(&this->regList, regs);
      idWindow::EvaluateRegisters(this, regs);
      idRegisterList::GetFromRegs(&this->regList, regs);
    }
    mEvent = this->namedEvents.list[v4]->mEvent;
    if ( mEvent )
      idGuiScriptList::Execute(mEvent, this);
  }
LABEL_12:
  v9 = this->children.num;
  for ( j = 0; j < v9; ++j )
  {
    v11 = this->children.list[j];
    v11->RunNamedEvent(v11, eventName);
  }
}

// FUNC: public: bool __thiscall idWindow::ParseScript(class idParser *,class idGuiScriptList &,int *,bool)
char __thiscall idWindow::ParseScript(
        idWindow *this,
        idParser *src,
        idGuiScriptList *list,
        int *timeParm,
        bool elseBlock)
{
  idGuiScript *v7; // eax
  idGuiScript *v8; // eax
  idGuiScript *v9; // esi
  idGuiScriptList *v10; // eax
  idGuiScriptList *v11; // eax
  bool ifElseBlock; // [esp+Fh] [ebp-5Dh]
  idToken token; // [esp+10h] [ebp-5Ch] BYREF
  int v15; // [esp+68h] [ebp-4h]
  int elseBlocka; // [esp+7Ch] [ebp+10h]

  token.floatvalue = 0.0;
  ifElseBlock = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v15 = 0;
  if ( elseBlock
    && (idParser::ReadToken(src, &token),
        ifElseBlock = idStr::Icmp(token.data, "if") == 0,
        idParser::UnreadToken(src, &token),
        ifElseBlock)
    || idParser::ExpectTokenString(src, "{") )
  {
    elseBlocka = 0;
    while ( idParser::ReadToken(src, &token) )
    {
      if ( !idStr::Cmp(token.data, "{") )
        ++elseBlocka;
      if ( !idStr::Cmp(token.data, "}") && elseBlocka-- <= 0 )
      {
LABEL_24:
        v15 = -1;
        idStr::FreeData(&token);
        return 1;
      }
      v7 = (idGuiScript *)Memory::Allocate(0x20u);
      LOBYTE(v15) = 1;
      if ( v7 )
      {
        idGuiScript::idGuiScript(v7);
        v9 = v8;
      }
      else
      {
        v9 = 0;
      }
      LOBYTE(v15) = 0;
      if ( idStr::Icmp(token.data, "if") )
      {
        idParser::UnreadToken(src, &token);
        if ( !idStr::Cmp(token.data, "{") )
        {
          idParser::Error(src, "Unexpected {");
          if ( v9 )
          {
            idGuiScript::~idGuiScript(v9);
            Memory::Free(v9);
          }
          goto LABEL_31;
        }
        idGuiScript::Parse(v9, src);
        idGuiScriptList::Append(list, v9);
      }
      else
      {
        v9->conditionReg = idWindow::ParseExpressionPriority(this, src, 4, 0, 0);
        v10 = (idGuiScriptList *)Memory::Allocate(0x10u);
        if ( v10 )
        {
          v10->list.list = 0;
          v10->list.num = 0;
          v10->list.size = 0;
          v10->list.granularity = 4;
        }
        else
        {
          v10 = 0;
        }
        LOBYTE(v15) = 0;
        v9->ifList = v10;
        idWindow::ParseScript(this, src, v10, 0, 0);
        if ( idParser::ReadToken(src, &token) )
        {
          if ( idStr::Cmp(token.data, "else") )
          {
            idParser::UnreadToken(src, &token);
          }
          else
          {
            v11 = (idGuiScriptList *)Memory::Allocate(0x10u);
            if ( v11 )
            {
              v11->list.list = 0;
              v11->list.num = 0;
              v11->list.size = 0;
              v11->list.granularity = 4;
            }
            else
            {
              v11 = 0;
            }
            LOBYTE(v15) = 0;
            v9->elseList = v11;
            idWindow::ParseScript(this, src, v11, 0, 1);
          }
        }
        idGuiScriptList::Append(list, v9);
        if ( ifElseBlock )
          goto LABEL_24;
      }
    }
    idParser::Error(src, "Unexpected end of file");
  }
LABEL_31:
  v15 = -1;
  idStr::FreeData(&token);
  return 0;
}

// FUNC: protected: bool __thiscall idWindow::ParseScriptEntry(char const *,class idParser *)
char __thiscall idWindow::ParseScriptEntry(idWindow *this, const char *name, idParser *src)
{
  int v4; // esi
  idGuiScriptList *v6; // edi
  idGuiScriptList *v7; // eax

  v4 = 0;
  while ( idStr::Icmp(name, idWindow::ScriptNames[v4]) )
  {
    if ( ++v4 >= 28 )
      return 0;
  }
  v6 = this->scripts[v4];
  if ( v6 )
  {
    idGuiScriptList::~idGuiScriptList(this->scripts[v4]);
    Memory::Free(v6);
  }
  v7 = (idGuiScriptList *)Memory::Allocate(0x10u);
  if ( v7 )
  {
    v7->list.list = 0;
    v7->list.num = 0;
    v7->list.size = 0;
    v7->list.granularity = 4;
  }
  else
  {
    v7 = 0;
  }
  this->scripts[v4] = v7;
  return idWindow::ParseScript(this, src, v7, 0, 0);
}

// FUNC: protected: void __thiscall idWindow::Transition(void)
void __thiscall idWindow::Transition(idWindow *this)
{
  idWindow *v1; // ebp
  int num; // eax
  idTransitionData *v3; // edx
  idUserInterfaceLocal *gui; // ecx
  double time; // st7
  double v6; // st7
  double accelTime; // st7
  double startTime; // st6
  double v9; // st7
  double v10; // st6
  float v11; // eax
  float v12; // ecx
  float v13; // ebx
  double linearTime; // st7
  double v15; // st6
  float v16; // esi
  float *p_x; // ebx
  float v18; // eax
  double v19; // st7
  double v20; // st6
  float v21; // eax
  double decelTime; // st7
  double v23; // st6
  float v24; // ebx
  int *p_currentValue; // eax
  bool v26; // c0
  int v27; // ecx
  int v28; // eax
  extrapolation_t extrapolationType; // ecx
  double v30; // st7
  double v31; // st7
  double v32; // st7
  float w; // eax
  float *v34; // ecx
  double v35; // st7
  float v36; // eax
  double v37; // st7
  double v38; // st6
  double v39; // st6
  double v40; // st6
  double v41; // st7
  double v42; // st7
  double v43; // st7
  float v44; // eax
  float v45; // ecx
  double v46; // st6
  double v47; // st5
  double v48; // st4
  double v49; // st5
  double v50; // st7
  double v51; // st7
  float v52; // ecx
  float v53; // eax
  double v54; // st6
  double v55; // st6
  double v56; // st5
  double v57; // st4
  double v58; // st5
  float v59; // ecx
  double v60; // st7
  double v61; // st7
  float v62; // eax
  float v63; // ecx
  long double v64; // st6
  double v65; // st5
  double v66; // st4
  double v67; // st7
  double v68; // st7
  float v69; // ecx
  float v70; // eax
  long double v71; // st6
  long double v72; // st6
  double v73; // st5
  double v74; // st4
  double v75; // st5
  int w_low; // ecx
  bool clear; // [esp+Bh] [ebp-259h]
  float v78; // [esp+Ch] [ebp-258h]
  float v79; // [esp+10h] [ebp-254h]
  int v80; // [esp+14h] [ebp-250h]
  float v81; // [esp+18h] [ebp-24Ch] BYREF
  float v82; // [esp+1Ch] [ebp-248h]
  float v83; // [esp+20h] [ebp-244h]
  int v84; // [esp+24h] [ebp-240h]
  float v85; // [esp+28h] [ebp-23Ch]
  idWindow *v86; // [esp+2Ch] [ebp-238h]
  int v87; // [esp+30h] [ebp-234h]
  float v88; // [esp+34h] [ebp-230h]
  float v89; // [esp+38h] [ebp-22Ch]
  float v90; // [esp+3Ch] [ebp-228h]
  float v91; // [esp+40h] [ebp-224h]
  float v92; // [esp+44h] [ebp-220h]
  float v93; // [esp+48h] [ebp-21Ch]
  float v94; // [esp+4Ch] [ebp-218h]
  float v95; // [esp+50h] [ebp-214h]
  float v96; // [esp+54h] [ebp-210h]
  float v97; // [esp+58h] [ebp-20Ch]
  float v98; // [esp+5Ch] [ebp-208h]
  float v99; // [esp+60h] [ebp-204h]
  float v100; // [esp+64h] [ebp-200h]
  float v101; // [esp+68h] [ebp-1FCh]
  float v102; // [esp+6Ch] [ebp-1F8h]
  float v103; // [esp+70h] [ebp-1F4h]
  float v104; // [esp+74h] [ebp-1F0h]
  float v105; // [esp+78h] [ebp-1ECh]
  float v106; // [esp+7Ch] [ebp-1E8h]
  float v107; // [esp+80h] [ebp-1E4h]
  float v108; // [esp+84h] [ebp-1E0h]
  float v109; // [esp+88h] [ebp-1DCh]
  float v110; // [esp+8Ch] [ebp-1D8h]
  float v111; // [esp+90h] [ebp-1D4h]
  float v112; // [esp+94h] [ebp-1D0h]
  float v113; // [esp+98h] [ebp-1CCh]
  float v114; // [esp+9Ch] [ebp-1C8h]
  float v115; // [esp+A0h] [ebp-1C4h]
  float v116; // [esp+A4h] [ebp-1C0h]
  float v117; // [esp+A8h] [ebp-1BCh]
  float v118; // [esp+ACh] [ebp-1B8h]
  float v119; // [esp+B0h] [ebp-1B4h]
  float x; // [esp+B4h] [ebp-1B0h]
  float y; // [esp+B8h] [ebp-1ACh]
  float z; // [esp+BCh] [ebp-1A8h]
  float v123; // [esp+C0h] [ebp-1A4h]
  float v124; // [esp+C4h] [ebp-1A0h]
  float v125; // [esp+C8h] [ebp-19Ch]
  float v126; // [esp+CCh] [ebp-198h]
  float v127; // [esp+D0h] [ebp-194h]
  float v128; // [esp+D4h] [ebp-190h]
  float v129; // [esp+D8h] [ebp-18Ch]
  float v130; // [esp+DCh] [ebp-188h]
  float v131; // [esp+E0h] [ebp-184h]
  float v132; // [esp+E4h] [ebp-180h]
  float v133; // [esp+E8h] [ebp-17Ch]
  float v134; // [esp+ECh] [ebp-178h]
  float v135; // [esp+F0h] [ebp-174h]
  float v136; // [esp+F4h] [ebp-170h]
  float v137; // [esp+F8h] [ebp-16Ch]
  float v138; // [esp+FCh] [ebp-168h]
  float v139; // [esp+100h] [ebp-164h]
  float v140; // [esp+104h] [ebp-160h]
  float v141; // [esp+108h] [ebp-15Ch]
  float v142; // [esp+10Ch] [ebp-158h]
  float v143; // [esp+110h] [ebp-154h]
  float v144; // [esp+114h] [ebp-150h]
  float v145; // [esp+118h] [ebp-14Ch]
  float v146; // [esp+11Ch] [ebp-148h]
  float v147; // [esp+120h] [ebp-144h]
  float v148; // [esp+124h] [ebp-140h]
  float v149; // [esp+128h] [ebp-13Ch]
  float v150; // [esp+12Ch] [ebp-138h]
  float v151; // [esp+130h] [ebp-134h]
  float v152; // [esp+134h] [ebp-130h]
  float v153; // [esp+138h] [ebp-12Ch]
  float v154; // [esp+13Ch] [ebp-128h]
  float v155; // [esp+140h] [ebp-124h]
  float v156; // [esp+144h] [ebp-120h]
  float v157; // [esp+148h] [ebp-11Ch]
  float v158; // [esp+14Ch] [ebp-118h]
  float v159; // [esp+150h] [ebp-114h]
  float v160; // [esp+154h] [ebp-110h]
  float v161; // [esp+158h] [ebp-10Ch]
  float v162; // [esp+15Ch] [ebp-108h]
  float v163; // [esp+160h] [ebp-104h]
  float v164; // [esp+168h] [ebp-FCh]
  float v165; // [esp+16Ch] [ebp-F8h]
  float v166; // [esp+170h] [ebp-F4h]
  float v167; // [esp+174h] [ebp-F0h]
  float v168; // [esp+178h] [ebp-ECh]
  float v169; // [esp+17Ch] [ebp-E8h]
  float v170; // [esp+188h] [ebp-DCh]
  float v171; // [esp+18Ch] [ebp-D8h]
  float v172; // [esp+190h] [ebp-D4h]
  float v173; // [esp+194h] [ebp-D0h]
  float v174; // [esp+198h] [ebp-CCh]
  float v175; // [esp+19Ch] [ebp-C8h]
  float v176; // [esp+1A8h] [ebp-BCh]
  float v177; // [esp+1ACh] [ebp-B8h]
  float v178; // [esp+1B0h] [ebp-B4h]
  float v179; // [esp+1B4h] [ebp-B0h]
  float v180; // [esp+1B8h] [ebp-ACh]
  float v181; // [esp+1BCh] [ebp-A8h]
  float v182; // [esp+1C8h] [ebp-9Ch]
  float v183; // [esp+1CCh] [ebp-98h]
  float v184; // [esp+1D0h] [ebp-94h]
  float v185; // [esp+1D4h] [ebp-90h]
  float v186; // [esp+1D8h] [ebp-8Ch]
  float v187; // [esp+1DCh] [ebp-88h]
  float v188; // [esp+1ECh] [ebp-78h]
  float v189; // [esp+1F0h] [ebp-74h]
  float v190; // [esp+1FCh] [ebp-68h]
  float v191; // [esp+200h] [ebp-64h]
  float v192; // [esp+204h] [ebp-60h]
  float v193; // [esp+210h] [ebp-54h]
  float v194; // [esp+214h] [ebp-50h]
  float v195; // [esp+220h] [ebp-44h]
  float v196; // [esp+224h] [ebp-40h]
  float v197; // [esp+230h] [ebp-34h]
  float v198; // [esp+23Ch] [ebp-28h]
  float v199; // [esp+240h] [ebp-24h]
  float v200; // [esp+24Ch] [ebp-18h]
  float v201; // [esp+250h] [ebp-14h]
  float v202; // [esp+254h] [ebp-10h]
  float v203; // [esp+260h] [ebp-4h]

  v1 = this;
  num = this->transitions.num;
  v86 = this;
  clear = 1;
  if ( num <= 0 )
    goto LABEL_40;
  v80 = 0;
  v87 = num;
  do
  {
    v3 = &v1->transitions.list[v80];
    gui = v1->gui;
    if ( v3->interp.decelTime + v3->interp.linearTime + v3->interp.accelTime + v3->interp.startTime <= (double)gui->time )
    {
      (*(void (__stdcall **)(float *))&v3->data->gap8[4])(&v3->interp.endValue.x);
      goto LABEL_38;
    }
    time = (double)gui->time;
    clear = 0;
    v79 = time;
    v6 = time - v3->interp.startTime;
    if ( v6 >= v3->interp.accelTime )
    {
      v85 = v3->interp.linearTime + v3->interp.accelTime;
      if ( v6 >= v85 )
      {
        if ( v3->interp.extrapolate.extrapolationType == EXTRAPOLATION_DECELLINEAR )
          goto LABEL_14;
        v19 = v3->interp.decelTime * 0.00050000002;
        v20 = v19 * v3->interp.extrapolate.speed.x;
        v170 = v19 * v3->interp.extrapolate.speed.y;
        v171 = v19 * v3->interp.extrapolate.speed.z;
        v172 = v19 * v3->interp.extrapolate.speed.w;
        v92 = v3->interp.endValue.x - v20;
        v21 = v92;
        v93 = v3->interp.endValue.y - v170;
        v12 = v93;
        v94 = v3->interp.endValue.z - v171;
        v16 = v94;
        v95 = v3->interp.endValue.w - v172;
        decelTime = v3->interp.decelTime;
        v23 = v85 + v3->interp.startTime;
        v3->interp.extrapolate.startValue.x = v92;
        v3->interp.extrapolate.startValue.y = v12;
        v3->interp.extrapolate.extrapolationType = EXTRAPOLATION_DECELLINEAR;
        v24 = v95;
        v3->interp.extrapolate.startTime = v23;
        v3->interp.extrapolate.startValue.z = v16;
        v3->interp.extrapolate.startValue.w = v24;
        v3->interp.extrapolate.duration = decelTime;
        v3->interp.extrapolate.baseSpeed.x = v3->interp.extrapolate.baseSpeed.x;
        v3->interp.extrapolate.baseSpeed.y = v3->interp.extrapolate.baseSpeed.y;
        v3->interp.extrapolate.baseSpeed.z = v3->interp.extrapolate.baseSpeed.z;
        v3->interp.extrapolate.baseSpeed.w = v3->interp.extrapolate.baseSpeed.w;
        v3->interp.extrapolate.speed.x = v3->interp.extrapolate.speed.x;
        v3->interp.extrapolate.speed.y = v3->interp.extrapolate.speed.y;
        v3->interp.extrapolate.speed.z = v3->interp.extrapolate.speed.z;
        v3->interp.extrapolate.speed.w = v3->interp.extrapolate.speed.w;
        p_x = &v3->interp.extrapolate.currentValue.x;
        v3->interp.extrapolate.currentValue.x = v21;
        v18 = v95;
      }
      else
      {
        if ( v3->interp.extrapolate.extrapolationType == EXTRAPOLATION_LINEAR )
          goto LABEL_14;
        v9 = v3->interp.accelTime * 0.00050000002;
        v10 = v9 * v3->interp.extrapolate.speed.x;
        v164 = v9 * v3->interp.extrapolate.speed.y;
        v165 = v9 * v3->interp.extrapolate.speed.z;
        v166 = v9 * v3->interp.extrapolate.speed.w;
        v88 = v10 + v3->interp.startValue.x;
        v11 = v88;
        v89 = v164 + v3->interp.startValue.y;
        v12 = v89;
        v90 = v165 + v3->interp.startValue.z;
        v91 = v166 + v3->interp.startValue.w;
        v13 = v91;
        linearTime = v3->interp.linearTime;
        v15 = v3->interp.accelTime + v3->interp.startTime;
        v3->interp.extrapolate.startValue.x = v88;
        v3->interp.extrapolate.startValue.y = v12;
        v3->interp.extrapolate.extrapolationType = EXTRAPOLATION_LINEAR;
        v16 = v90;
        v3->interp.extrapolate.startTime = v15;
        v3->interp.extrapolate.startValue.z = v16;
        v3->interp.extrapolate.startValue.w = v13;
        v3->interp.extrapolate.duration = linearTime;
        v3->interp.extrapolate.baseSpeed.x = v3->interp.extrapolate.baseSpeed.x;
        v3->interp.extrapolate.baseSpeed.y = v3->interp.extrapolate.baseSpeed.y;
        v3->interp.extrapolate.baseSpeed.z = v3->interp.extrapolate.baseSpeed.z;
        v3->interp.extrapolate.baseSpeed.w = v3->interp.extrapolate.baseSpeed.w;
        v3->interp.extrapolate.speed.x = v3->interp.extrapolate.speed.x;
        v3->interp.extrapolate.speed.y = v3->interp.extrapolate.speed.y;
        v3->interp.extrapolate.speed.z = v3->interp.extrapolate.speed.z;
        v3->interp.extrapolate.speed.w = v3->interp.extrapolate.speed.w;
        p_x = &v3->interp.extrapolate.currentValue.x;
        v3->interp.extrapolate.currentValue.x = v11;
        v18 = v91;
      }
      v1 = v86;
      p_x[1] = v12;
      p_x[2] = v16;
      v3->interp.extrapolate.currentTime = -1.0;
      p_x[3] = v18;
    }
    else if ( v3->interp.extrapolate.extrapolationType != EXTRAPOLATION_ACCELLINEAR )
    {
      accelTime = v3->interp.accelTime;
      startTime = v3->interp.startTime;
      v3->interp.extrapolate.extrapolationType = EXTRAPOLATION_ACCELLINEAR;
      v3->interp.extrapolate.startTime = startTime;
      v3->interp.extrapolate.duration = accelTime;
      v3->interp.extrapolate.startValue.x = v3->interp.startValue.x;
      v3->interp.extrapolate.startValue.y = v3->interp.startValue.y;
      v3->interp.extrapolate.startValue.z = v3->interp.startValue.z;
      v3->interp.extrapolate.startValue.w = v3->interp.startValue.w;
      v3->interp.extrapolate.baseSpeed.x = v3->interp.extrapolate.baseSpeed.x;
      v3->interp.extrapolate.baseSpeed.y = v3->interp.extrapolate.baseSpeed.y;
      v3->interp.extrapolate.baseSpeed.z = v3->interp.extrapolate.baseSpeed.z;
      v3->interp.extrapolate.baseSpeed.w = v3->interp.extrapolate.baseSpeed.w;
      v3->interp.extrapolate.speed.x = v3->interp.extrapolate.speed.x;
      v3->interp.extrapolate.speed.y = v3->interp.extrapolate.speed.y;
      v3->interp.extrapolate.speed.z = v3->interp.extrapolate.speed.z;
      v3->interp.extrapolate.speed.w = v3->interp.extrapolate.speed.w;
      v3->interp.extrapolate.currentTime = -1.0;
      v3->interp.extrapolate.currentValue.x = v3->interp.startValue.x;
      v3->interp.extrapolate.currentValue.y = v3->interp.startValue.y;
      v3->interp.extrapolate.currentValue.z = v3->interp.startValue.z;
      v3->interp.extrapolate.currentValue.w = v3->interp.startValue.w;
    }
LABEL_14:
    v78 = v79;
    if ( v79 == v3->interp.extrapolate.currentTime )
    {
      p_currentValue = (int *)&v3->interp.extrapolate.currentValue;
    }
    else
    {
      v26 = v79 < (double)v3->interp.extrapolate.startTime;
      v3->interp.extrapolate.currentTime = v79;
      if ( !v26 )
      {
        extrapolationType = v3->interp.extrapolate.extrapolationType;
        if ( (extrapolationType & 0x40) == 0 )
        {
          v30 = v3->interp.extrapolate.duration + v3->interp.extrapolate.startTime;
          if ( v79 > v30 )
            v78 = v30;
        }
        switch ( extrapolationType & 0xFFFFFFBF )
        {
          case 1u:
            v31 = v78 - v3->interp.extrapolate.startTime;
            x = v3->interp.extrapolate.baseSpeed.x;
            v32 = v31 * 0.001;
            y = v3->interp.extrapolate.baseSpeed.y;
            w = v3->interp.extrapolate.baseSpeed.w;
            z = v3->interp.extrapolate.baseSpeed.z;
            v123 = w;
            v34 = &v3->interp.extrapolate.currentValue.x;
            v182 = y * v32;
            v183 = z * v32;
            v184 = w * v32;
            v160 = x * v32 + v3->interp.extrapolate.startValue.x;
            v161 = v182 + v3->interp.extrapolate.startValue.y;
            v162 = v183 + v3->interp.extrapolate.startValue.z;
            v35 = v184 + v3->interp.extrapolate.startValue.w;
            v3->interp.extrapolate.currentValue.x = v160;
            v3->interp.extrapolate.currentValue.y = v161;
            v163 = v35;
            v3->interp.extrapolate.currentValue.z = v162;
            v36 = v163;
            goto LABEL_35;
          case 2u:
            v37 = (v78 - v3->interp.extrapolate.startTime) * 0.001;
            v108 = v3->interp.extrapolate.baseSpeed.x + v3->interp.extrapolate.speed.x;
            v38 = v3->interp.extrapolate.baseSpeed.y;
            v148 = v108;
            v109 = v38 + v3->interp.extrapolate.speed.y;
            v39 = v3->interp.extrapolate.baseSpeed.z;
            v149 = v109;
            v110 = v39 + v3->interp.extrapolate.speed.z;
            v40 = v3->interp.extrapolate.baseSpeed.w;
            v150 = v110;
            v34 = &v3->interp.extrapolate.currentValue.x;
            v111 = v40 + v3->interp.extrapolate.speed.w;
            v151 = v111;
            v176 = v109 * v37;
            v177 = v110 * v37;
            v178 = v111 * v37;
            v116 = v108 * v37 + v3->interp.extrapolate.startValue.x;
            v117 = v176 + v3->interp.extrapolate.startValue.y;
            v118 = v177 + v3->interp.extrapolate.startValue.z;
            v41 = v178 + v3->interp.extrapolate.startValue.w;
            v3->interp.extrapolate.currentValue.x = v116;
            v3->interp.extrapolate.currentValue.y = v117;
            v119 = v41;
            v3->interp.extrapolate.currentValue.z = v118;
            v36 = v119;
            goto LABEL_35;
          case 4u:
            if ( v3->interp.extrapolate.duration == 0.0 )
              goto LABEL_30;
            v42 = v78 - v3->interp.extrapolate.startTime;
            v140 = v3->interp.extrapolate.speed.x;
            v43 = v42 / v3->interp.extrapolate.duration;
            v141 = v3->interp.extrapolate.speed.y;
            v44 = v3->interp.extrapolate.speed.w;
            v142 = v3->interp.extrapolate.speed.z;
            v143 = v44;
            v124 = v3->interp.extrapolate.baseSpeed.x;
            v125 = v3->interp.extrapolate.baseSpeed.y;
            v45 = v3->interp.extrapolate.baseSpeed.w;
            v126 = v3->interp.extrapolate.baseSpeed.z;
            v127 = v45;
            v46 = v43 * v43 * 0.5 * (v3->interp.extrapolate.duration * 0.001);
            v167 = v140 * v46;
            v168 = v141 * v46;
            v169 = v142 * v46;
            v188 = v126 * v43;
            v189 = v45 * v43;
            v192 = v124 * v43 + v3->interp.extrapolate.startValue.x;
            v47 = v125 * v43 + v3->interp.extrapolate.startValue.y;
            v48 = v188 + v3->interp.extrapolate.startValue.z;
            v193 = v189 + v3->interp.extrapolate.startValue.w;
            v156 = v192 + v167;
            v3->interp.extrapolate.currentValue.x = v156;
            v157 = v47 + v168;
            v3->interp.extrapolate.currentValue.y = v157;
            v158 = v48 + v169;
            v49 = v193;
            v3->interp.extrapolate.currentValue.z = v158;
            v159 = v49 + v46 * v44;
            v3->interp.extrapolate.currentValue.w = v159;
            break;
          case 8u:
            if ( v3->interp.extrapolate.duration == 0.0 )
              goto LABEL_33;
            v50 = v78 - v3->interp.extrapolate.startTime;
            v132 = v3->interp.extrapolate.speed.x;
            v51 = v50 / v3->interp.extrapolate.duration;
            v133 = v3->interp.extrapolate.speed.y;
            v52 = v3->interp.extrapolate.speed.w;
            v134 = v3->interp.extrapolate.speed.z;
            v135 = v52;
            v104 = v3->interp.extrapolate.baseSpeed.x;
            v105 = v3->interp.extrapolate.baseSpeed.y;
            v53 = v3->interp.extrapolate.baseSpeed.w;
            v106 = v3->interp.extrapolate.baseSpeed.z;
            v107 = v53;
            v34 = &v3->interp.extrapolate.currentValue.x;
            v54 = (v51 - v51 * v51 * 0.5) * (v3->interp.extrapolate.duration * 0.001);
            v173 = v132 * v54;
            v174 = v133 * v54;
            v175 = v134 * v54;
            v55 = v54 * v135;
            v200 = v106 * v51;
            v201 = v53 * v51;
            v196 = v104 * v51 + v3->interp.extrapolate.startValue.x;
            v56 = v105 * v51 + v3->interp.extrapolate.startValue.y;
            v57 = v200 + v3->interp.extrapolate.startValue.z;
            v197 = v201 + v3->interp.extrapolate.startValue.w;
            v112 = v196 + v173;
            v3->interp.extrapolate.currentValue.x = v112;
            v113 = v56 + v174;
            v3->interp.extrapolate.currentValue.y = v113;
            v114 = v57 + v175;
            v58 = v197;
            v3->interp.extrapolate.currentValue.z = v114;
            v115 = v58 + v55;
            v36 = v115;
            goto LABEL_35;
          case 0x10u:
            if ( v3->interp.extrapolate.duration == 0.0 )
            {
LABEL_30:
              v3->interp.extrapolate.currentValue.x = v3->interp.extrapolate.startValue.x;
              v3->interp.extrapolate.currentValue.y = v3->interp.extrapolate.startValue.y;
              v59 = v3->interp.extrapolate.startValue.w;
              v3->interp.extrapolate.currentValue.z = v3->interp.extrapolate.startValue.z;
              v3->interp.extrapolate.currentValue.w = v59;
            }
            else
            {
              v60 = v78 - v3->interp.extrapolate.startTime;
              v96 = v3->interp.extrapolate.speed.x;
              v61 = v60 / v3->interp.extrapolate.duration;
              v97 = v3->interp.extrapolate.speed.y;
              v62 = v3->interp.extrapolate.speed.w;
              v98 = v3->interp.extrapolate.speed.z;
              v99 = v62;
              v128 = v3->interp.extrapolate.baseSpeed.x;
              v129 = v3->interp.extrapolate.baseSpeed.y;
              v63 = v3->interp.extrapolate.baseSpeed.w;
              v130 = v3->interp.extrapolate.baseSpeed.z;
              v131 = v63;
              v64 = (1.0 - cos(idMath::HALF_PI * v61)) * v3->interp.extrapolate.duration * 0.70710677 * 0.001;
              v179 = v96 * v64;
              v180 = v97 * v64;
              v181 = v98 * v64;
              v190 = v130 * v61;
              v191 = v63 * v61;
              v194 = v128 * v61 + v3->interp.extrapolate.startValue.x;
              v65 = v129 * v61 + v3->interp.extrapolate.startValue.y;
              v66 = v190 + v3->interp.extrapolate.startValue.z;
              v195 = v191 + v3->interp.extrapolate.startValue.w;
              v136 = v194 + v179;
              v3->interp.extrapolate.currentValue.x = v136;
              v137 = v65 + v180;
              v3->interp.extrapolate.currentValue.y = v137;
              v138 = v66 + v181;
              v139 = v195 + v64 * v62;
              v3->interp.extrapolate.currentValue.z = v138;
              v3->interp.extrapolate.currentValue.w = v139;
            }
            break;
          case 0x20u:
            if ( v3->interp.extrapolate.duration == 0.0 )
            {
LABEL_33:
              v34 = &v3->interp.extrapolate.currentValue.x;
              v3->interp.extrapolate.currentValue.x = v3->interp.extrapolate.startValue.x;
              v3->interp.extrapolate.currentValue.y = v3->interp.extrapolate.startValue.y;
              v36 = v3->interp.extrapolate.startValue.w;
              v3->interp.extrapolate.currentValue.z = v3->interp.extrapolate.startValue.z;
            }
            else
            {
              v67 = v78 - v3->interp.extrapolate.startTime;
              v144 = v3->interp.extrapolate.speed.x;
              v68 = v67 / v3->interp.extrapolate.duration;
              v145 = v3->interp.extrapolate.speed.y;
              v69 = v3->interp.extrapolate.speed.w;
              v146 = v3->interp.extrapolate.speed.z;
              v147 = v69;
              v152 = v3->interp.extrapolate.baseSpeed.x;
              v153 = v3->interp.extrapolate.baseSpeed.y;
              v70 = v3->interp.extrapolate.baseSpeed.w;
              v154 = v3->interp.extrapolate.baseSpeed.z;
              v155 = v70;
              v34 = &v3->interp.extrapolate.currentValue.x;
              v71 = sin(idMath::HALF_PI * v68) * v3->interp.extrapolate.duration * 0.70710677 * 0.001;
              v185 = v144 * v71;
              v186 = v145 * v71;
              v187 = v146 * v71;
              v72 = v71 * v147;
              v198 = v154 * v68;
              v199 = v70 * v68;
              v202 = v152 * v68 + v3->interp.extrapolate.startValue.x;
              v73 = v153 * v68 + v3->interp.extrapolate.startValue.y;
              v74 = v198 + v3->interp.extrapolate.startValue.z;
              v203 = v199 + v3->interp.extrapolate.startValue.w;
              v100 = v202 + v185;
              v3->interp.extrapolate.currentValue.x = v100;
              v101 = v73 + v186;
              v3->interp.extrapolate.currentValue.y = v101;
              v102 = v74 + v187;
              v75 = v203;
              v3->interp.extrapolate.currentValue.z = v102;
              v103 = v75 + v72;
              v36 = v103;
            }
LABEL_35:
            v34[3] = v36;
            break;
          default:
            break;
        }
        v81 = v3->interp.extrapolate.currentValue.x;
        v82 = v3->interp.extrapolate.currentValue.y;
        w_low = LODWORD(v3->interp.extrapolate.currentValue.w);
        v83 = v3->interp.extrapolate.currentValue.z;
        v84 = w_low;
        goto LABEL_37;
      }
      p_currentValue = (int *)&v3->interp.extrapolate.startValue;
    }
    v81 = *(float *)p_currentValue;
    v82 = *((float *)p_currentValue + 1);
    v27 = p_currentValue[2];
    v28 = p_currentValue[3];
    v83 = *(float *)&v27;
    v84 = v28;
LABEL_37:
    (*(void (__thiscall **)(idWinVar *, float *))&v3->data->gap8[4])(v3->data, &v81);
LABEL_38:
    ++v80;
    --v87;
  }
  while ( v87 );
  if ( clear )
  {
LABEL_40:
    if ( v1->transitions.size < 0 )
      idList<idTransitionData>::Resize(&v1->transitions, 0);
    v1->transitions.num = 0;
    BYTE1(v1->flags) &= ~4u;
  }
}

// FUNC: public: void __thiscall idWindow::AddTransition(class idWinVar *,class idVec4,class idVec4,int,float,float)
void __thiscall idWindow::AddTransition(
        idWindow *this,
        idWinVar *dest,
        idVec4 from,
        idVec4 to,
        int time,
        float accelTime,
        float decelTime)
{
  double v8; // st7
  double v9; // st5
  float linearTime; // eax
  unsigned __int8 v12; // c2
  unsigned __int8 v13; // c3
  idList<idTransitionData> *p_transitions; // ebx
  int size; // eax
  float v16; // [esp+Ch] [ebp-B0h]
  idVec4 v17; // [esp+10h] [ebp-ACh]
  float v18; // [esp+18h] [ebp-A4h]
  float v19; // [esp+1Ch] [ebp-A0h]
  idVec4 v20; // [esp+20h] [ebp-9Ch]
  float v21; // [esp+30h] [ebp-8Ch]
  idTransitionData data; // [esp+34h] [ebp-88h] BYREF

  idTransitionData::idTransitionData(&data);
  v21 = (float)time;
  v8 = (double)this->gui->time;
  data.data = dest;
  data.interp.startTime = v8;
  data.interp.endValue = to;
  data.interp.accelTime = v21 * accelTime;
  data.interp.startValue = from;
  data.interp.decelTime = v21 * decelTime;
  if ( v21 > 0.0 )
  {
    v9 = data.interp.decelTime + data.interp.accelTime;
    if ( v9 > v21 )
    {
      data.interp.accelTime = v21 * data.interp.accelTime / v9;
      data.interp.decelTime = v21 - data.interp.accelTime;
    }
    data.interp.extrapolate.currentValue = from;
    data.interp.extrapolate.currentTime = -1.0;
    data.interp.extrapolate.startValue = from;
    data.interp.linearTime = v21 - data.interp.accelTime - data.interp.decelTime;
    v18 = to.z - from.z;
    v19 = to.w - from.w;
    v16 = 1000.0 / ((data.interp.decelTime + data.interp.accelTime) * 0.5 + data.interp.linearTime);
    v20.z = v18 * v16;
    v20.w = v19 * v16;
    if ( data.interp.accelTime == 0.0 )
    {
      v17.z = 0.0;
      v17.y = 0.0;
      v17.x = 0.0;
      v17.w = 0.0;
      data.interp.extrapolate.startTime = v8;
      if ( v13 | v12 )
      {
        linearTime = data.interp.decelTime;
        data.interp.extrapolate.extrapolationType = EXTRAPOLATION_DECELLINEAR;
      }
      else
      {
        linearTime = data.interp.linearTime;
        data.interp.extrapolate.extrapolationType = EXTRAPOLATION_LINEAR;
      }
    }
    else
    {
      linearTime = data.interp.accelTime;
      v17.x = 0.0;
      v17.y = 0.0;
      data.interp.extrapolate.extrapolationType = EXTRAPOLATION_ACCELLINEAR;
      v17.z = 0.0;
      v17.w = 0.0;
      data.interp.extrapolate.startTime = v8;
    }
    data.interp.extrapolate.duration = linearTime;
    data.interp.extrapolate.baseSpeed = v17;
    v20.x = (to.x - from.x) * v16;
    v20.y = (to.y - from.y) * v16;
    data.interp.extrapolate.speed = v20;
  }
  p_transitions = &this->transitions;
  if ( !p_transitions->list )
    idList<idTransitionData>::Resize(p_transitions, p_transitions->granularity);
  size = p_transitions->size;
  if ( p_transitions->num == size )
  {
    if ( !p_transitions->granularity )
      p_transitions->granularity = 16;
    idList<idTransitionData>::Resize(
      p_transitions,
      size + p_transitions->granularity - (size + p_transitions->granularity) % p_transitions->granularity);
  }
  qmemcpy(&p_transitions->list[p_transitions->num++], &data, sizeof(p_transitions->list[p_transitions->num++]));
}

// FUNC: public: void __thiscall idWindow::ClearTransitions(void)
void __thiscall idWindow::ClearTransitions(idWindow *this)
{
  idList<idTransitionData> *p_transitions; // edi

  p_transitions = &this->transitions;
  if ( this->transitions.size < 0 )
    idList<idTransitionData>::Resize(&this->transitions, 0);
  p_transitions->num = 0;
  BYTE1(this->flags) &= ~4u;
}

// FUNC: public: virtual void __thiscall idWindow::ReadFromSaveGame(class idFile *)
void __userpurge idWindow::ReadFromSaveGame(idWindow *this@<ecx>, int a2@<ebx>, int a3@<esi>, idFile *savefile)
{
  int j; // esi
  idWinVar *v7; // ecx
  idFile_vtbl *v8; // edx
  int v9; // eax
  idWindow **list; // edx
  int v11; // esi
  int v12; // eax
  idWindow **v13; // edx
  int v14; // esi
  int v15; // eax
  idWindow **v16; // edx
  int v17; // esi
  idGuiScriptList **scripts; // esi
  int v19; // edi
  int k; // esi
  idTimeLineEvent *v21; // eax
  idGuiScriptList *event; // ecx
  idList<idTransitionData> *p_transitions; // esi
  int size; // eax
  int m; // esi
  rvNamedEvent *v26; // eax
  idGuiScriptList *mEvent; // ecx
  int n; // esi
  drawWin_t *v29; // eax
  idWindow *win; // ecx
  idSimpleWindow *simp; // eax
  int i; // [esp+12Ch] [ebp-90h]
  int num; // [esp+130h] [ebp-8Ch] BYREF
  idTransitionData trans; // [esp+134h] [ebp-88h] BYREF

  if ( this->transitions.list )
    Memory::Free(this->transitions.list);
  this->transitions.list = 0;
  this->transitions.num = 0;
  this->transitions.size = 0;
  idWindow::ReadSaveGameString(this, &this->cmd, savefile);
  ((void (__thiscall *)(idFile *, float *, int, int, int))savefile->Read)(savefile, &this->actualX, 4, a3, a2);
  savefile->Read(savefile, &this->actualY, 4);
  savefile->Read(savefile, &this->childID, 4);
  savefile->Read(savefile, &this->flags, 4);
  savefile->Read(savefile, &this->lastTimeRun, 4);
  savefile->Read(savefile, &this->drawRect, 16);
  savefile->Read(savefile, &this->clientRect, 16);
  savefile->Read(savefile, &this->origin, 8);
  savefile->Read(savefile, &this->timeLine, 4);
  savefile->Read(savefile, &this->xOffset, 4);
  savefile->Read(savefile, &this->yOffset, 4);
  savefile->Read(savefile, &this->cursor, 1);
  savefile->Read(savefile, &this->forceAspectWidth, 4);
  savefile->Read(savefile, &this->forceAspectHeight, 4);
  savefile->Read(savefile, &this->matScalex, 4);
  savefile->Read(savefile, &this->matScaley, 4);
  savefile->Read(savefile, &this->borderSize, 4);
  savefile->Read(savefile, &this->textAlign, 1);
  savefile->Read(savefile, &this->textAlignx, 4);
  savefile->Read(savefile, &this->textAligny, 4);
  savefile->Read(savefile, &this->textStyle, 1);
  savefile->Read(savefile, &this->textSpacing, 4);
  savefile->Read(savefile, &this->shear, 8);
  idWindow::ReadSaveGameString(this, &this->name, savefile);
  idWindow::ReadSaveGameString(this, &this->comment, savefile);
  this->noTime.ReadFromSaveGame(&this->noTime, savefile);
  this->visible.ReadFromSaveGame(&this->visible, savefile);
  this->rect.ReadFromSaveGame(&this->rect, savefile);
  this->backColor.ReadFromSaveGame(&this->backColor, savefile);
  this->matColor.ReadFromSaveGame(&this->matColor, savefile);
  this->foreColor.ReadFromSaveGame(&this->foreColor, savefile);
  this->hoverColor.ReadFromSaveGame(&this->hoverColor, savefile);
  this->borderColor.ReadFromSaveGame(&this->borderColor, savefile);
  this->textScale.ReadFromSaveGame(&this->textScale, savefile);
  this->noEvents.ReadFromSaveGame(&this->noEvents, savefile);
  this->rotate.ReadFromSaveGame(&this->rotate, savefile);
  this->text.ReadFromSaveGame(&this->text, savefile);
  this->backGroundName.ReadFromSaveGame(&this->backGroundName, savefile);
  this->hideCursor.ReadFromSaveGame(&this->hideCursor, savefile);
  for ( j = 0; j < this->definedVars.num; ++j )
  {
    v7 = this->definedVars.list[j];
    v7->ReadFromSaveGame(v7, savefile);
  }
  savefile->Read(savefile, &this->textRect, 16);
  v8 = savefile->__vftable;
  num = -1;
  v8->Read(savefile, &num, 4);
  v9 = 0;
  if ( this->children.num > 0 )
  {
    list = this->children.list;
    v11 = num;
    do
    {
      if ( (*list)->childID == v11 )
        this->focusedChild = *list;
      ++v9;
      ++list;
    }
    while ( v9 < this->children.num );
  }
  savefile->Read(savefile, &num, 4);
  v12 = 0;
  if ( this->children.num > 0 )
  {
    v13 = this->children.list;
    v14 = num;
    do
    {
      if ( (*v13)->childID == v14 )
        this->captureChild = *v13;
      ++v12;
      ++v13;
    }
    while ( v12 < this->children.num );
  }
  savefile->Read(savefile, &num, 4);
  v15 = 0;
  if ( this->children.num > 0 )
  {
    v16 = this->children.list;
    v17 = num;
    do
    {
      if ( (*v16)->childID == v17 )
        this->overChild = *v16;
      ++v15;
      ++v16;
    }
    while ( v15 < this->children.num );
  }
  scripts = this->scripts;
  v19 = 28;
  do
  {
    if ( *scripts )
      idGuiScriptList::ReadFromSaveGame(*scripts, savefile);
    ++scripts;
    --v19;
  }
  while ( v19 );
  for ( k = 0; k < this->timeLineEvents.num; ++k )
  {
    v21 = this->timeLineEvents.list[k];
    if ( v21 )
    {
      savefile->Read(savefile, &v21->pending, 1);
      savefile->Read(savefile, this->timeLineEvents.list[k], 4);
      event = this->timeLineEvents.list[k]->event;
      if ( event )
        idGuiScriptList::ReadFromSaveGame(event, savefile);
    }
  }
  savefile->Read(savefile, &trans.offset, 4);
  for ( i = 0; i < num; ++i )
  {
    idTransitionData::idTransitionData(&trans);
    trans.data = 0;
    idWindow::ReadSaveGameTransition(this, &trans, savefile);
    if ( trans.data )
    {
      p_transitions = &this->transitions;
      if ( !this->transitions.list )
        idList<idTransitionData>::Resize(&this->transitions, this->transitions.granularity);
      size = this->transitions.size;
      if ( p_transitions->num == size )
      {
        if ( !this->transitions.granularity )
          this->transitions.granularity = 16;
        idList<idTransitionData>::Resize(
          &this->transitions,
          size + this->transitions.granularity - (size + this->transitions.granularity) % this->transitions.granularity);
      }
      qmemcpy(&this->transitions.list[p_transitions->num], &trans, sizeof(this->transitions.list[p_transitions->num]));
      ++this->transitions.num;
    }
  }
  for ( m = 0; m < this->namedEvents.num; ++m )
  {
    v26 = this->namedEvents.list[m];
    if ( v26 )
    {
      idWindow::ReadSaveGameString(this, &v26->mName, savefile);
      mEvent = this->namedEvents.list[m]->mEvent;
      if ( mEvent )
        idGuiScriptList::ReadFromSaveGame(mEvent, savefile);
    }
  }
  idRegisterList::ReadFromSaveGame(&this->regList, savefile);
  for ( n = 0; n < this->drawWindows.num; ++n )
  {
    v29 = this->drawWindows.list;
    win = v29[n].win;
    simp = v29[n].simp;
    if ( simp )
    {
      simp->ReadFromSaveGame(simp, savefile);
    }
    else if ( win )
    {
      win->ReadFromSaveGame(win, savefile);
    }
  }
  if ( (this->flags & 0x10000000) != 0 )
    idWindow::FixupTransitions(this);
}

// FUNC: public: void __thiscall idWindow::CleanUp(void)
void __thiscall idWindow::CleanUp(idWindow *this)
{
  int num; // ebx
  int i; // edi
  idSimpleWindow *simp; // ecx
  int j; // edi
  rvNamedEvent **list; // eax
  rvNamedEvent *v7; // ebx
  int k; // edi
  idWindow *v9; // ecx
  int m; // edi
  idWinVar *v11; // ecx
  int n; // edi
  idTimeLineEvent *v13; // ebx
  idGuiScriptList *event; // ebp
  idGuiScriptList **scripts; // edi
  int v16; // ebp
  idGuiScriptList *v17; // ebx

  num = this->drawWindows.num;
  for ( i = 0; i < num; ++i )
  {
    simp = this->drawWindows.list[i].simp;
    if ( simp )
      ((void (__thiscall *)(idSimpleWindow *, int))simp->~idSimpleWindow)(simp, 1);
  }
  idRegisterList::Reset(&this->regList);
  for ( j = 0; j < this->namedEvents.num; ++j )
  {
    list = this->namedEvents.list;
    v7 = list[j];
    if ( v7 )
    {
      rvNamedEvent::~rvNamedEvent(list[j]);
      Memory::Free(v7);
    }
    this->namedEvents.list[j] = 0;
  }
  if ( this->namedEvents.list )
    Memory::Free(this->namedEvents.list);
  this->namedEvents.list = 0;
  this->namedEvents.num = 0;
  this->namedEvents.size = 0;
  if ( this->drawWindows.list )
    Memory::Free(this->drawWindows.list);
  this->drawWindows.list = 0;
  this->drawWindows.num = 0;
  this->drawWindows.size = 0;
  for ( k = 0; k < this->children.num; ++k )
  {
    v9 = this->children.list[k];
    if ( v9 )
      ((void (__thiscall *)(idWindow *, int))v9->~idWindow)(v9, 1);
    this->children.list[k] = 0;
  }
  if ( this->children.list )
    Memory::Free(this->children.list);
  this->children.list = 0;
  this->children.num = 0;
  this->children.size = 0;
  for ( m = 0; m < this->definedVars.num; ++m )
  {
    v11 = this->definedVars.list[m];
    if ( v11 )
      ((void (__thiscall *)(idWinVar *, int))v11->~idWinVar)(v11, 1);
    this->definedVars.list[m] = 0;
  }
  if ( this->definedVars.list )
    Memory::Free(this->definedVars.list);
  this->definedVars.list = 0;
  this->definedVars.num = 0;
  this->definedVars.size = 0;
  for ( n = 0; n < this->timeLineEvents.num; ++n )
  {
    v13 = this->timeLineEvents.list[n];
    if ( v13 )
    {
      event = v13->event;
      if ( event )
      {
        idGuiScriptList::~idGuiScriptList(v13->event);
        Memory::Free(event);
      }
      Memory::Free(v13);
    }
    this->timeLineEvents.list[n] = 0;
  }
  if ( this->timeLineEvents.list )
    Memory::Free(this->timeLineEvents.list);
  this->timeLineEvents.list = 0;
  this->timeLineEvents.num = 0;
  this->timeLineEvents.size = 0;
  scripts = this->scripts;
  v16 = 28;
  do
  {
    v17 = *scripts;
    if ( *scripts )
    {
      idGuiScriptList::~idGuiScriptList(*scripts);
      Memory::Free(v17);
    }
    ++scripts;
    --v16;
  }
  while ( v16 );
  idWindow::CommonInit(this);
}

// FUNC: public: virtual __thiscall idWindow::~idWindow(void)
void __thiscall idWindow::~idWindow(idWindow *this)
{
  idRegister **list; // eax
  int *v3; // eax
  rvNamedEvent **v4; // eax
  float *v5; // eax
  wexpOp_t *v6; // eax
  idTransitionData *v7; // eax
  idTimeLineEvent **v8; // eax
  drawWin_t *v9; // eax
  idWindow **v10; // eax
  idWinVar **v11; // eax
  idWinVar **v12; // eax
  char *v13; // [esp-2Ch] [ebp-50h]
  char *v14; // [esp-28h] [ebp-4Ch]
  char *v15; // [esp-24h] [ebp-48h]
  char *v16; // [esp-20h] [ebp-44h]
  char *v17; // [esp-1Ch] [ebp-40h]
  char *v18; // [esp-18h] [ebp-3Ch]
  char *v19; // [esp-14h] [ebp-38h]
  char *v20; // [esp-10h] [ebp-34h]
  char *v21; // [esp-Ch] [ebp-30h]
  char *v22; // [esp-8h] [ebp-2Ch]
  char *name; // [esp-4h] [ebp-28h]
  char *v24; // [esp-4h] [ebp-28h]

  this->__vftable = (idWindow_vtbl *)&idWindow::`vftable';
  idWindow::CleanUp(this);
  name = this->hideCursor.name;
  this->hideCursor.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(name);
  this->hideCursor.name = 0;
  idHashIndex::Free(&this->regList.regHash);
  list = this->regList.regs.list;
  if ( list )
    Memory::Free(list);
  this->regList.regs.list = 0;
  this->regList.regs.num = 0;
  this->regList.regs.size = 0;
  v3 = this->transitionSubs.list;
  if ( v3 )
    Memory::Free(v3);
  this->transitionSubs.list = 0;
  this->transitionSubs.num = 0;
  this->transitionSubs.size = 0;
  v4 = this->namedEvents.list;
  if ( v4 )
    Memory::Free(v4);
  this->namedEvents.list = 0;
  this->namedEvents.num = 0;
  this->namedEvents.size = 0;
  v5 = this->expressionRegisters.list;
  if ( v5 )
    Memory::Free(v5);
  this->expressionRegisters.list = 0;
  this->expressionRegisters.num = 0;
  this->expressionRegisters.size = 0;
  v6 = this->ops.list;
  if ( v6 )
    Memory::Free(v6);
  this->ops.list = 0;
  this->ops.num = 0;
  this->ops.size = 0;
  v7 = this->transitions.list;
  if ( v7 )
    Memory::Free(v7);
  this->transitions.list = 0;
  this->transitions.num = 0;
  this->transitions.size = 0;
  v8 = this->timeLineEvents.list;
  if ( v8 )
    Memory::Free(v8);
  this->timeLineEvents.list = 0;
  this->timeLineEvents.num = 0;
  this->timeLineEvents.size = 0;
  v9 = this->drawWindows.list;
  if ( v9 )
    Memory::Free(v9);
  this->drawWindows.list = 0;
  this->drawWindows.num = 0;
  this->drawWindows.size = 0;
  v10 = this->children.list;
  if ( v10 )
    Memory::Free(v10);
  this->children.list = 0;
  this->children.num = 0;
  this->children.size = 0;
  v11 = this->updateVars.list;
  if ( v11 )
    Memory::Free(v11);
  this->updateVars.list = 0;
  this->updateVars.num = 0;
  this->updateVars.size = 0;
  v12 = this->definedVars.list;
  if ( v12 )
    Memory::Free(v12);
  this->definedVars.list = 0;
  this->definedVars.num = 0;
  this->definedVars.size = 0;
  idWinBackground::~idWinBackground(&this->backGroundName);
  idWinStr::~idWinStr(&this->text);
  v24 = this->rotate.name;
  this->rotate.__vftable = (idWinFloat_vtbl *)&idWinVar::`vftable';
  Memory::Free(v24);
  this->rotate.name = 0;
  v22 = this->textScale.name;
  this->textScale.__vftable = (idWinFloat_vtbl *)&idWinVar::`vftable';
  Memory::Free(v22);
  this->textScale.name = 0;
  v21 = this->borderColor.name;
  this->borderColor.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v21);
  this->borderColor.name = 0;
  v20 = this->hoverColor.name;
  this->hoverColor.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v20);
  this->hoverColor.name = 0;
  v19 = this->foreColor.name;
  this->foreColor.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v19);
  this->foreColor.name = 0;
  v18 = this->matColor.name;
  this->matColor.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v18);
  this->matColor.name = 0;
  v17 = this->backColor.name;
  this->backColor.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v17);
  this->backColor.name = 0;
  v16 = this->rect.name;
  this->rect.__vftable = (idWinRectangle_vtbl *)&idWinVar::`vftable';
  Memory::Free(v16);
  this->rect.name = 0;
  v15 = this->noEvents.name;
  this->noEvents.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(v15);
  this->noEvents.name = 0;
  v14 = this->visible.name;
  this->visible.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(v14);
  this->visible.name = 0;
  v13 = this->noTime.name;
  this->noTime.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(v13);
  this->noTime.name = 0;
  idStr::FreeData(&this->comment);
  idStr::FreeData(&this->name);
  idStr::FreeData(&this->cmd);
}

// FUNC: protected: bool __thiscall idWindow::RunTimeEvents(int)
char __thiscall idWindow::RunTimeEvents(idWindow *this, int time)
{
  int num; // ebx
  int v5; // edi
  idWinVar *v6; // ecx
  int v7; // ebx
  int i; // edi

  if ( this->lastTimeRun > time )
    this->lastTimeRun = time;
  if ( time - this->lastTimeRun < (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) )
    return 0;
  num = this->updateVars.num;
  v5 = 0;
  for ( this->lastTimeRun = time; v5 < num; ++v5 )
  {
    v6 = this->updateVars.list[v5];
    v6->Update(v6);
  }
  if ( this->expressionRegisters.num && this->ops.num )
  {
    lastEval = this;
    idRegisterList::SetToRegs(&this->regList, regs);
    idWindow::EvaluateRegisters(this, regs);
    idRegisterList::GetFromRegs(&this->regList, regs);
  }
  if ( (this->flags & 0x400) != 0 )
    idWindow::Transition(this);
  idWindow::Time(this);
  this->RunScript(this, 7);
  v7 = this->children.num;
  for ( i = 0; i < v7; ++i )
    idWindow::RunTimeEvents(this->children.list[i], time);
  return 1;
}

// FUNC: public: virtual char const * __thiscall idWindow::HandleEvent(struct sysEvent_s const *,bool *)
char *__thiscall idWindow::HandleEvent(idWindow *this, const sysEvent_s *event, bool *updateVisuals)
{
  bool v4; // zf
  sysEventType_t evType; // eax
  int evValue; // esi
  idUserInterfaceLocal *v9; // esi
  idWindow **v10; // edx
  idWindow *v11; // esi
  idWindow *v12; // ecx
  char *result; // eax
  idWindow *CaptureChild; // eax
  idWindow **v15; // edi
  idUserInterfaceLocal *gui; // esi
  idWindow **list; // edx
  idWindow *v18; // esi
  idWindow *v19; // ecx
  idUserInterfaceLocal *v20; // edi
  idUserInterfaceLocal *v21; // esi
  idWindow **v22; // edi
  idWindow *v23; // eax
  idWindow *v24; // eax
  int v25; // edi
  idWindow *v26; // ebx
  idWindow *parent; // esi
  int v28; // eax
  int v29; // edx
  idWindow *win; // ecx
  idWindow *v31; // eax
  int j; // esi
  idWindow *v33; // ecx
  idWindow *v34; // eax
  idWindow *v35; // esi
  bool v36; // al
  idWindow *v37; // eax
  idWindow *v38; // eax
  idWindow_vtbl *v39; // esi
  idWindow *FocusedChild; // eax
  idStr *p_returnCmd; // ebx
  idUserInterfaceLocal *v42; // eax
  idStr *v43; // esi
  int v44; // edi
  int v45; // eax
  int v46; // eax
  char v47; // cl
  int v48; // edx
  char *data; // eax
  idUserInterfaceLocal *v50; // edi
  int v51; // ebx
  idStr *v52; // esi
  int i; // eax
  char v54; // cl
  char *v55; // edx
  char *v56; // edx
  idStr *p_pendingCmd; // esi
  float x; // [esp+0h] [ebp-1Ch]
  float xa; // [esp+0h] [ebp-1Ch]
  float xb; // [esp+0h] [ebp-1Ch]
  float xc; // [esp+0h] [ebp-1Ch]
  float xd; // [esp+0h] [ebp-1Ch]
  float xe; // [esp+0h] [ebp-1Ch]
  float y; // [esp+4h] [ebp-18h]
  float ya; // [esp+4h] [ebp-18h]
  float yb; // [esp+4h] [ebp-18h]
  float yc; // [esp+4h] [ebp-18h]
  float yd; // [esp+4h] [ebp-18h]
  float ye; // [esp+4h] [ebp-18h]
  float v70; // [esp+8h] [ebp-14h]
  float v71; // [esp+Ch] [ebp-10h]
  idWindow **v72; // [esp+18h] [ebp-4h]
  int v73; // [esp+18h] [ebp-4h]
  int num; // [esp+18h] [ebp-4h]
  idUserInterfaceLocal *eventa; // [esp+20h] [ebp+4h]
  int updateVisualsa; // [esp+24h] [ebp+8h]
  bool *updateVisualsb; // [esp+24h] [ebp+8h]
  bool *updateVisualsc; // [esp+24h] [ebp+8h]
  bool *updateVisualsd; // [esp+24h] [ebp+8h]

  idStr::operator=(&this->cmd, (char *)&entityFilter);
  if ( (this->flags & 0x10000000) != 0 )
  {
    v4 = this->expressionRegisters.num == 0;
    actionDownRun = 0;
    actionUpRun = 0;
    if ( !v4 && this->ops.num )
    {
      lastEval = this;
      idRegisterList::SetToRegs(&this->regList, regs);
      idWindow::EvaluateRegisters(this, regs);
      idRegisterList::GetFromRegs(&this->regList, regs);
    }
    idWindow::RunTimeEvents(this, this->gui->time);
    idWindow::CalcRects(this, 0.0, 0.0);
    idDeviceContext::SetCursor(this->dc, 0);
  }
  if ( !this->visible.data || this->noEvents.data )
    goto LABEL_175;
  evType = event->evType;
  if ( event->evType != SE_KEY )
  {
    if ( evType != SE_MOUSE || (this->flags & 0x80000) != 0 )
    {
      if ( evType != SE_JOYSTICK_AXIS || (this->flags & 0x80000) != 0 )
      {
        if ( evType == SE_CHAR )
        {
          if ( idWindow::GetFocusedChild(this) )
          {
            FocusedChild = idWindow::GetFocusedChild(this);
            result = (char *)FocusedChild->HandleEvent(FocusedChild, event, updateVisuals);
            if ( result )
            {
              if ( *result )
                return result;
            }
          }
        }
        goto LABEL_175;
      }
      if ( updateVisuals )
        *updateVisuals = 1;
      v39 = this->__vftable;
      if ( event->evValue )
      {
        v71 = (double)(*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type)
            * 0.001
            * 210.0
            * (double)event->evValue2
            * 0.0078740157;
        result = (char *)((int (__thiscall *)(idWindow *, _DWORD, _DWORD))v39->RouteMouseCoords)(this, 0, LODWORD(v71));
      }
      else
      {
        v70 = (double)(*(int (__thiscall **)(netadrtype_t, _DWORD))(*(_DWORD *)common.type + 40))(common.type, 0)
            * 0.001
            * 210.0
            * (double)event->evValue2
            * 0.0078740157;
        result = (char *)((int (__thiscall *)(idWindow *, _DWORD))v39->RouteMouseCoords)(this, LODWORD(v70));
      }
    }
    else
    {
      if ( updateVisuals )
        *updateVisuals = 1;
      ye = (float)event->evValue2;
      xe = (float)event->evValue;
      result = (char *)((int (__thiscall *)(idWindow *, _DWORD, _DWORD))this->RouteMouseCoords)(
                         this,
                         LODWORD(xe),
                         LODWORD(ye));
    }
    goto LABEL_168;
  }
  v4 = this->expressionRegisters.num == 0;
  lastEval = this;
  if ( !v4 )
  {
    idRegisterList::SetToRegs(&this->regList, regs);
    idWindow::EvaluateRegisters(this, regs);
    idRegisterList::GetFromRegs(&this->regList, regs);
  }
  if ( updateVisuals )
    *updateVisuals = 1;
  evValue = event->evValue;
  if ( evValue != 187 )
  {
    if ( evValue == 188 )
    {
      if ( !event->evValue2 && idWindow::GetCaptureChild(this) )
        goto LABEL_42;
      v73 = this->children.num - 1;
      if ( v73 < 0 )
      {
LABEL_61:
        if ( event->evValue2 )
          actionDownRun = this->RunScript(this, 3);
        goto LABEL_175;
      }
      while ( 1 )
      {
        v15 = &this->children.list[v73];
        if ( !(*v15)->visible.data )
          goto LABEL_60;
        gui = this->gui;
        yb = ((double (*)(void))gui->CursorY)();
        xb = gui->CursorX(gui);
        if ( !idWindow::Contains(*v15, &(*v15)->drawRect, xb, yb) )
          goto LABEL_60;
        list = this->children.list;
        v18 = list[v73];
        if ( v18->noEvents.data )
          goto LABEL_60;
        if ( event->evValue2 )
        {
          idWindow::BringToTop(this, list[v73]);
          idWindow::SetFocus(v19, v18, 1);
        }
        v20 = this->gui;
        yc = ((double (*)(void))v20->CursorY)();
        xc = v20->CursorX(v20);
        if ( !idWindow::Contains(v18, &v18->clientRect, xc, yc) && idWindow::GetCaptureChild(this) != v18 )
          goto LABEL_60;
        if ( idWindow::gui_edit.internalVar->integerValue )
          break;
        if ( (v18->flags & 0x10) != 0 )
          goto LABEL_56;
LABEL_57:
        result = (char *)v18->HandleEvent(v18, event, updateVisuals);
        if ( result && *result )
          return result;
        if ( (v18->flags & 0x200) != 0 )
          return (char *)&entityFilter;
LABEL_60:
        if ( --v73 < 0 )
          goto LABEL_61;
      }
      if ( (v18->flags & 0x1000) == 0 )
        goto LABEL_57;
LABEL_56:
      idWindow::SetCapture(this, v18);
      goto LABEL_57;
    }
    if ( evValue == 189 )
    {
      if ( idWindow::gui_edit.internalVar->integerValue )
      {
        num = this->children.num;
        for ( updateVisualsb = 0; (int)updateVisualsb < num; ++updateVisualsb )
        {
          v21 = this->gui;
          v22 = &this->children.list[(_DWORD)updateVisualsb];
          yd = ((double (*)(void))v21->CursorY)();
          xd = v21->CursorX(v21);
          if ( idRectangle::Contains(&(*v22)->drawRect, xd, yd) )
          {
            if ( event->evValue2 )
            {
              v23 = this->children.list[(_DWORD)updateVisualsb];
              v23->flags ^= 0x1000u;
              if ( (this->children.list[(_DWORD)updateVisualsb]->flags & 0x1000) != 0 )
              {
                BYTE1(this->flags) &= ~0x10u;
                return "childsel";
              }
            }
          }
        }
      }
      goto LABEL_175;
    }
    if ( evValue == 9 && event->evValue2 )
    {
      if ( !idWindow::GetFocusedChild(this) )
        goto LABEL_175;
      v24 = idWindow::GetFocusedChild(this);
      result = (char *)v24->HandleEvent(v24, event, updateVisuals);
      if ( result && *result )
        return result;
      v25 = 1;
      if ( idKeyInput::IsDown(142) || idKeyInput::IsDown(3) )
        v25 = -1;
      updateVisualsc = (bool *)idWindow::GetFocusedChild(this);
      v26 = idWindow::GetFocusedChild(this);
      parent = v26->parent;
      if ( !parent )
        goto LABEL_175;
      while ( 1 )
      {
        v28 = 0;
        if ( v26 )
        {
          v28 = v25 + idWindow::GetChildIndex(parent, v26);
        }
        else if ( v25 < 0 )
        {
          v28 = parent->drawWindows.num - 1;
        }
        v29 = parent->drawWindows.num;
        if ( v28 >= v29 )
          break;
        while ( 1 )
        {
          if ( v28 < 0 )
            goto LABEL_94;
          win = parent->drawWindows.list[v28].win;
          if ( win == (idWindow *)updateVisualsc )
            goto LABEL_175;
          if ( win && !win->noEvents.data && win->visible.data )
          {
            if ( (win->flags & 0x800) != 0 )
            {
              idWindow::SetFocus(this, win, 1);
              goto LABEL_175;
            }
            if ( win->drawWindows.num > 0 )
              break;
          }
          v28 += v25;
          if ( v28 >= v29 )
            goto LABEL_94;
        }
        parent = parent->drawWindows.list[v28].win;
        v26 = 0;
LABEL_95:
        if ( !parent )
          goto LABEL_175;
      }
LABEL_94:
      v26 = parent;
      parent = parent->parent;
      if ( parent != this->gui->GetDesktop(this->gui) )
        goto LABEL_95;
LABEL_175:
      updateVisualsd = (bool *)this->cmd.len;
      p_returnCmd = &this->gui->returnCmd;
      if ( (int)(updateVisualsd + 1) > this->gui->returnCmd.alloced )
        idStr::ReAllocate(p_returnCmd, (int)(updateVisualsd + 1), 0);
      qmemcpy(p_returnCmd->data, this->cmd.data, (unsigned int)updateVisualsd);
      updateVisualsd[(unsigned int)p_returnCmd->data] = 0;
      p_returnCmd->len = (int)updateVisualsd;
      v42 = this->gui;
      if ( v42->pendingCmd.len )
      {
        v43 = &v42->returnCmd;
        v44 = v42->returnCmd.len + 3;
        v45 = v42->returnCmd.len + 4;
        if ( v45 > v43->alloced )
          idStr::ReAllocate(v43, v45, 1);
        v46 = 0;
        v47 = 32;
        do
        {
          v48 = v46 + v43->len;
          ++v46;
          v43->data[v48] = v47;
          v47 = asc_102D104C[v46];
        }
        while ( v47 );
        data = v43->data;
        v43->len = v44;
        data[v44] = 0;
        v50 = this->gui;
        v51 = v50->returnCmd.len + v50->pendingCmd.len;
        v52 = &v50->returnCmd;
        if ( v51 + 1 > v50->returnCmd.alloced )
          idStr::ReAllocate(&v50->returnCmd, v51 + 1, 1);
        for ( i = 0; i < v50->pendingCmd.len; v55[v52->len] = v54 )
        {
          v54 = v50->pendingCmd.data[i];
          v55 = &v50->returnCmd.data[i++];
        }
        v56 = v50->returnCmd.data;
        v52->len = v51;
        v56[v51] = 0;
        p_pendingCmd = &this->gui->pendingCmd;
        idStr::FreeData(p_pendingCmd);
        p_pendingCmd->len = 0;
        p_pendingCmd->alloced = 20;
        p_pendingCmd->data = p_pendingCmd->baseBuffer;
        p_pendingCmd->baseBuffer[0] = 0;
      }
      idStr::operator=(&this->cmd, (char *)&entityFilter);
      return this->gui->returnCmd.data;
    }
    if ( (IsEscapeKey(event->evValue) || evValue == 200) && event->evValue2 )
    {
      if ( !this->RunControllerScript(this, 19, event, updateVisuals) )
      {
        if ( idWindow::GetFocusedChild(this) )
        {
          v31 = idWindow::GetFocusedChild(this);
          result = (char *)v31->HandleEvent(v31, event, updateVisuals);
          if ( result )
          {
            if ( *result )
              return result;
          }
        }
        if ( (this->flags & 0x80000) != 0 )
        {
          for ( j = this->children.num - 1; j >= 0; --j )
          {
            v33 = this->children.list[j];
            if ( v33->visible.data )
              v33->HandleEvent(v33, event, updateVisuals);
          }
        }
        this->RunScript(this, 6);
      }
      goto LABEL_175;
    }
    if ( evValue == 13 )
    {
      if ( idWindow::GetFocusedChild(this) )
      {
        v34 = idWindow::GetFocusedChild(this);
        result = (char *)v34->HandleEvent(v34, event, updateVisuals);
        if ( result )
        {
          if ( *result )
            return result;
        }
      }
      if ( (this->flags & 0x1000000) != 0 )
      {
        if ( event->evValue2 )
          this->RunScript(this, 2);
        else
          this->RunScript(this, 9);
      }
      goto LABEL_175;
    }
    if ( event->evValue2 )
    {
      switch ( evValue )
      {
        case 199:
          if ( idWindow::GetFocusedChild(this) )
          {
            v35 = idWindow::GetFocusedChild(this);
            result = (char *)v35->HandleEvent(v35, event, updateVisuals);
            if ( result && *result )
              return result;
            if ( v35->visible.data )
            {
              if ( event->evValue2 && !actionDownRun )
              {
                actionDownRun = v35->RunScript(v35, 2);
                idWindow::AddCommand(this, v35->cmd.data);
                this->RunControllerScript(this, 18, event, updateVisuals);
                goto LABEL_175;
              }
              if ( !actionUpRun )
                actionUpRun = v35->RunScript(v35, 9);
            }
          }
          this->RunControllerScript(this, 18, event, updateVisuals);
          goto LABEL_175;
        case 205:
          this->RunControllerScript(this, 22, event, updateVisuals);
          goto LABEL_175;
        case 206:
          this->RunControllerScript(this, 23, event, updateVisuals);
          goto LABEL_175;
        case 207:
          this->RunControllerScript(this, 25, event, updateVisuals);
          goto LABEL_175;
        case 208:
          this->RunControllerScript(this, 24, event, updateVisuals);
          goto LABEL_175;
        case 197:
          v36 = this->RunControllerScript(this, 20, event, updateVisuals);
LABEL_142:
          if ( v36 )
            goto LABEL_175;
          if ( !idWindow::GetFocusedChild(this) )
            goto LABEL_175;
          v37 = idWindow::GetFocusedChild(this);
          if ( v37->GetType(v37) != WT_BIND )
            goto LABEL_175;
LABEL_145:
          v38 = idWindow::GetFocusedChild(this);
          result = (char *)v38->HandleEvent(v38, event, updateVisuals);
LABEL_168:
          if ( result && *result )
            return result;
          goto LABEL_175;
        case 198:
          v36 = this->RunControllerScript(this, 21, event, updateVisuals);
          goto LABEL_142;
        case 203:
          this->RunControllerScript(this, 17, event, updateVisuals);
          goto LABEL_175;
        case 202:
          v36 = this->RunControllerScript(this, 26, event, updateVisuals);
          goto LABEL_142;
        case 201:
          v36 = this->RunControllerScript(this, 27, event, updateVisuals);
          goto LABEL_142;
      }
    }
    if ( !idWindow::GetFocusedChild(this) )
      goto LABEL_175;
    goto LABEL_145;
  }
  if ( !event->evValue2 && idWindow::GetCaptureChild(this) )
  {
LABEL_42:
    CaptureChild = idWindow::GetCaptureChild(this);
    CaptureChild->LoseCapture(CaptureChild);
    this->gui->GetDesktop(this->gui)->captureChild = 0;
    return (char *)&entityFilter;
  }
  updateVisualsa = this->children.num - 1;
  if ( updateVisualsa < 0 )
  {
LABEL_30:
    if ( !event->evValue2 || actionDownRun )
    {
      if ( !actionUpRun )
        actionUpRun = this->RunScript(this, 9);
    }
    else
    {
      actionDownRun = this->RunScript(this, 2);
    }
    goto LABEL_175;
  }
  while ( 1 )
  {
    v72 = &this->children.list[updateVisualsa];
    if ( !(*v72)->visible.data )
      goto LABEL_29;
    v9 = this->gui;
    y = ((double (*)(void))v9->CursorY)();
    x = v9->CursorX(v9);
    if ( !idWindow::Contains(*v72, &(*v72)->drawRect, x, y) )
      goto LABEL_29;
    v10 = this->children.list;
    v11 = v10[updateVisualsa];
    if ( v11->noEvents.data )
      goto LABEL_29;
    if ( event->evValue2 )
    {
      idWindow::BringToTop(this, v10[updateVisualsa]);
      idWindow::SetFocus(v12, v11, 1);
      if ( (v11->flags & 0x4000) != 0 )
        idWindow::SetCapture(this, v11);
    }
    eventa = this->gui;
    ya = ((double (*)(void))eventa->CursorY)();
    xa = eventa->CursorX(eventa);
    if ( !idWindow::Contains(v11, &v11->clientRect, xa, ya) )
      break;
    idWindow::SetFocus(this, v11, 1);
    result = (char *)v11->HandleEvent(v11, event, updateVisuals);
    if ( result && *result )
      return result;
    if ( (v11->flags & 0x200) != 0 )
      return (char *)&entityFilter;
LABEL_29:
    if ( --updateVisualsa < 0 )
      goto LABEL_30;
  }
  if ( !event->evValue2 )
    goto LABEL_29;
  idWindow::SetFocus(this, v11, 1);
  if ( (v11->flags & 0x10) != 0 || idWindow::gui_edit.internalVar->integerValue )
    idWindow::SetCapture(this, v11);
  return (char *)&entityFilter;
}

// FUNC: public: virtual void __thiscall idWindow::Redraw(float,float)
void __thiscall idWindow::Redraw(idWindow *this, float x, float y)
{
  int integerValue; // eax
  int v5; // edi
  idUserInterfaceLocal *gui; // ecx
  idUserInterfaceLocal_vtbl *v7; // edx
  idDict *v8; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  const char *v11; // eax
  idUserInterfaceLocal *v12; // edi
  double v13; // st7
  idRectangle *p_clientRect; // ebx
  float v15; // ecx
  int v16; // edi
  drawWin_t *list; // edx
  idWindow *win; // ecx
  unsigned int flags; // eax
  idUserInterfaceLocal *v20; // edi
  unsigned __int64 v21; // st7
  double v22; // st7
  char *v23; // eax
  idVec4 v24; // [esp+18h] [ebp-C8h]
  idRectangle v25; // [esp+28h] [ebp-B8h]
  idRectangle v26; // [esp+28h] [ebp-B8h]
  idRectangle v27; // [esp+28h] [ebp-B8h]
  idRectangle v28; // [esp+44h] [ebp-9Ch]
  int v29; // [esp+48h] [ebp-98h]
  int v30; // [esp+4Ch] [ebp-94h]
  float v31; // [esp+4Ch] [ebp-94h]
  double v32; // [esp+4Ch] [ebp-94h]
  int v33; // [esp+50h] [ebp-90h]
  float v34; // [esp+50h] [ebp-90h]
  int time; // [esp+68h] [ebp-78h]
  int v36; // [esp+6Ch] [ebp-74h]
  int ca; // [esp+70h] [ebp-70h]
  int cb; // [esp+70h] [ebp-70h]
  int c; // [esp+70h] [ebp-70h]
  idVec3 oldOrg; // [esp+74h] [ebp-6Ch] BYREF
  idRectangle v41; // [esp+80h] [ebp-60h]
  idStr str; // [esp+90h] [ebp-50h] BYREF
  idMat3 oldTrans; // [esp+B0h] [ebp-30h] BYREF
  int v44; // [esp+DCh] [ebp-4h]

  str.len = 0;
  str.alloced = 20;
  str.data = str.baseBuffer;
  str.baseBuffer[0] = 0;
  integerValue = r_skipGuiShaders.internalVar->integerValue;
  v44 = 0;
  if ( integerValue != 1 && this->dc )
  {
    v5 = this->gui->time;
    time = v5;
    if ( (this->flags & 0x10000000) != 0 && integerValue != 3 )
      idWindow::RunTimeEvents(this, v5);
    if ( r_skipGuiShaders.internalVar->integerValue != 2 )
    {
      if ( (this->flags & 0x800000) != 0 )
      {
        gui = this->gui;
        v7 = gui->__vftable;
        *(_QWORD *)&v41.x = 1120403456i64;
        *(_QWORD *)&v41.w = 0x42A0000042A00000i64;
        v8 = (idDict *)v7->State(gui);
        Key = idDict::FindKey(v8, "name");
        if ( Key )
          data = Key->value->data;
        else
          data = &entityFilter;
        v24 = idDeviceContext::colorWhite;
        v11 = va(" %0.1f seconds\n%s", (double)(v5 - this->timeLine) * 0.001, data);
        idDeviceContext::DrawTextA(this->dc, v11, 0.34999999, 0, 0, v24, v41, 0, -1, 0, 0, 0, 0, 0);
      }
      if ( (this->flags & 0x400000) != 0 )
      {
        this->dc->enableClipping = 0;
        v12 = this->gui;
        ca = SLODWORD(this->rect.data.y);
        v13 = ((double (__fastcall *)(idUserInterfaceLocal *))v12->CursorY)(v12);
        v36 = (int)((double (__thiscall *)(idUserInterfaceLocal *, int))v12->CursorX)(v12, (int)v13);
        cb = (int)((double (__thiscall *)(idWinRectangle *, int, int))this->rect.x)(
                    &this->rect,
                    (int)*(float *)&ca,
                    v36);
        sprintf(&str, "x: %i y: %i  cursorx: %i cursory: %i", cb, v29, v30, v33);
        *(_QWORD *)&v41.x = 0i64;
        *(_QWORD *)&v25.x = 0i64;
        *(_QWORD *)&v41.w = 0x41A0000042C80000i64;
        *(_QWORD *)&v25.w = 0x41A0000042C80000i64;
        idDeviceContext::DrawTextA(
          this->dc,
          str.data,
          0.25,
          0,
          0,
          idDeviceContext::colorWhite,
          v25,
          0,
          -1,
          0,
          0,
          0,
          0,
          0);
        this->dc->enableClipping = 1;
      }
      if ( this->visible.data )
      {
        idWindow::CalcClientRect(this, 0.0, 0.0);
        idDeviceContext::SetFont(this->dc, this->fontNum);
        idDeviceContext::SetSize(this->dc, this->forceAspectWidth, this->forceAspectHeight);
        p_clientRect = &this->clientRect;
        this->drawRect.x = x + this->drawRect.x;
        this->drawRect.y = y + this->drawRect.y;
        this->clientRect.x = x + this->clientRect.x;
        this->clientRect.y = y + this->clientRect.y;
        this->textRect.x = x + this->textRect.x;
        this->textRect.y = y + this->textRect.y;
        v15 = this->drawRect.y;
        this->actualX = this->drawRect.x;
        this->actualY = v15;
        idDeviceContext::GetTransformInfo(this->dc, &oldOrg, &oldTrans);
        idWindow::SetupTransforms(this, x, y);
        this->DrawBackground(this, &this->drawRect);
        idWindow::DrawBorderAndCaption(this, &this->drawRect);
        if ( (this->flags & 0x10000) == 0 )
        {
          *(_QWORD *)&v28.x = *(_QWORD *)&p_clientRect->x;
          *(_QWORD *)&v28.w = *(_QWORD *)&this->clientRect.w;
          idDeviceContext::PushClipRect(this->dc, v28);
        }
        if ( r_skipGuiShaders.internalVar->integerValue < 5 )
          ((void (__thiscall *)(idWindow *, int, _DWORD, _DWORD))this->Draw)(this, time, LODWORD(x), LODWORD(y));
        if ( idWindow::gui_debug.internalVar->integerValue )
          idWindow::DebugDraw(this, time, x, y);
        v16 = 0;
        c = this->drawWindows.num;
        if ( c > 0 )
        {
          do
          {
            list = this->drawWindows.list;
            win = list[v16].win;
            v34 = this->yOffset + this->clientRect.y;
            v31 = p_clientRect->x + this->xOffset;
            if ( win )
              win->Redraw(win, COERCE_FLOAT(LODWORD(v31)), COERCE_FLOAT(LODWORD(v34)));
            else
              idSimpleWindow::Redraw(list[v16].simp, v31, v34);
            ++v16;
          }
          while ( v16 < c );
        }
        idDeviceContext::SetTransformInfo(this->dc, &oldOrg, &oldTrans);
        if ( (this->flags & 0x10000) == 0 )
          idDeviceContext::PopClipRect(this->dc);
        if ( idWindow::gui_edit.internalVar->integerValue
          || (flags = this->flags, (flags & 0x10000000) != 0)
          && (flags & 0x80000) == 0
          && !this->hideCursor.data
          && (this->gui->active || (flags & 0x100000) != 0) )
        {
          idDeviceContext::SetTransformInfo(this->dc, &vec3_origin, &mat3_identity);
          this->gui->DrawCursor(this->gui);
        }
        if ( idWindow::gui_debug.internalVar->integerValue && (this->flags & 0x10000000) != 0 )
        {
          this->dc->enableClipping = 0;
          v20 = this->gui;
          *(double *)&v21 = ((double (*)(void))v20->CursorY)();
          v22 = ((double (__thiscall *)(idUserInterfaceLocal *, _DWORD, _DWORD))v20->CursorX)(v20, v21, HIDWORD(v21));
          sprintf(&str, "x: %1.f y: %1.f", v22, v32);
          *(_QWORD *)&v41.x = 0i64;
          *(_QWORD *)&v26.x = 0i64;
          *(_QWORD *)&v41.w = 0x41A0000042C80000i64;
          *(_QWORD *)&v26.w = 0x41A0000042C80000i64;
          idDeviceContext::DrawTextA(
            this->dc,
            str.data,
            0.25,
            0,
            0,
            idDeviceContext::colorWhite,
            v26,
            0,
            -1,
            0,
            0,
            0,
            0,
            0);
          v23 = this->gui->source.data;
          *(_QWORD *)&v41.x = 0x41A0000000000000i64;
          *(_QWORD *)&v27.x = 0x41A0000000000000i64;
          *(_QWORD *)&v41.w = 0x41A0000043960000i64;
          *(_QWORD *)&v27.w = 0x41A0000043960000i64;
          idDeviceContext::DrawTextA(this->dc, v23, 0.25, 0, 0, idDeviceContext::colorWhite, v27, 0, -1, 0, 0, 0, 0, 0);
          this->dc->enableClipping = 1;
        }
        this->drawRect.x = this->drawRect.x - x;
        this->drawRect.y = this->drawRect.y - y;
        p_clientRect->x = p_clientRect->x - x;
        this->clientRect.y = this->clientRect.y - y;
        this->textRect.x = this->textRect.x - x;
        this->textRect.y = this->textRect.y - y;
      }
    }
  }
  v44 = -1;
  idStr::FreeData(&str);
}

// FUNC: public: virtual bool __thiscall idWindow::Parse(class idParser *,bool)
char __userpurge idWindow::Parse@<al>(idWindow *this@<ecx>, int a2@<edi>, idParser *src, idParser *rebuild)
{
  int i; // ebx
  rvNamedEvent *v6; // edi
  idGuiScriptList *mEvent; // ecx
  idEditWindow *v8; // eax
  idWindow *v9; // eax
  idWindow *v10; // ebx
  bool *v11; // eax
  int v12; // eax
  bool v13; // cc
  int ii; // eax
  drawWin_t *v15; // ecx
  int v16; // edi
  int v17; // ecx
  int v18; // ecx
  drawWin_t *v19; // esi
  int jj; // eax
  drawWin_t *v21; // ecx
  idChoiceWindow *v22; // eax
  idWindow *v23; // eax
  bool *v24; // eax
  int v25; // eax
  int kk; // eax
  drawWin_t *v27; // edx
  int v28; // edi
  int v29; // ecx
  int v30; // ecx
  int mm; // eax
  drawWin_t *v32; // ecx
  idSliderWindow *v33; // eax
  idWindow *v34; // eax
  bool *v35; // eax
  int v36; // eax
  int nn; // eax
  drawWin_t *v38; // edx
  int v39; // edi
  int v40; // ecx
  int v41; // ecx
  int i1; // eax
  drawWin_t *v43; // ecx
  idMarkerWindow *v44; // eax
  idWindow *v45; // eax
  bool *v46; // eax
  int v47; // eax
  int i2; // eax
  drawWin_t *v49; // edx
  int v50; // edi
  int v51; // ecx
  int v52; // ecx
  int i3; // eax
  drawWin_t *v54; // ecx
  idBindWindow *v55; // eax
  idWindow *v56; // eax
  idWindow *v57; // edi
  int v58; // eax
  int i4; // eax
  drawWin_t *v60; // ecx
  int v61; // ebx
  int v62; // ecx
  int v63; // ecx
  int v64; // ecx
  drawWin_t *v65; // edx
  drawWin_t *v66; // esi
  int i5; // eax
  drawWin_t *v68; // ecx
  idListWindow *v69; // eax
  idWindow *v70; // eax
  int v71; // eax
  int i6; // eax
  drawWin_t *v73; // ecx
  int v74; // ebx
  int v75; // ecx
  int v76; // ecx
  int i7; // eax
  drawWin_t *v78; // ecx
  idFieldWindow *v79; // eax
  idWindow *v80; // eax
  int v81; // eax
  int i8; // eax
  drawWin_t *v83; // ecx
  int v84; // ebx
  int v85; // ecx
  int v86; // ecx
  int i9; // eax
  drawWin_t *v88; // ecx
  idRenderWindow *v89; // eax
  idWindow *v90; // eax
  int v91; // eax
  int i10; // eax
  drawWin_t *v93; // ecx
  int v94; // ebx
  int v95; // ecx
  int v96; // ecx
  int i11; // eax
  drawWin_t *v98; // ecx
  idGraphWindow *v99; // eax
  idWindow *v100; // eax
  int v101; // eax
  int i12; // eax
  drawWin_t *v103; // ecx
  int v104; // ebx
  int v105; // ecx
  int v106; // ecx
  int i13; // eax
  drawWin_t *v108; // ecx
  rvPopupWindow *v109; // eax
  idWindow *v110; // eax
  int v111; // eax
  int i14; // eax
  drawWin_t *v113; // ecx
  int v114; // ebx
  int v115; // ecx
  int v116; // ecx
  int i15; // eax
  drawWin_t *v118; // ecx
  rvNamedEvent *v119; // eax
  rvNamedEvent *v120; // eax
  int v121; // esi
  char *v122; // edi
  int v123; // eax
  int v124; // esi
  char *v125; // eax
  int v126; // eax
  int i28; // eax
  int v128; // edi
  int v129; // ecx
  int v130; // ecx
  rvNamedEvent **v131; // esi
  int i29; // eax
  idTimeLineEvent *v133; // eax
  idTimeLineEvent *v134; // eax
  int *p_time; // edi
  int v136; // eax
  char v137; // cl
  int v138; // esi
  int v139; // eax
  char v140; // cl
  char *v141; // edx
  int v142; // eax
  int v143; // esi
  int i25; // eax
  char v145; // cl
  char *v146; // edx
  int v147; // esi
  char *v148; // edi
  int v149; // eax
  int v150; // eax
  int i26; // eax
  int v152; // ebx
  int v153; // ecx
  int v154; // ecx
  idTimeLineEvent **v155; // esi
  int i27; // eax
  int v157; // ebx
  char *v158; // ecx
  unsigned __int8 v159; // al
  int i22; // esi
  idWinVar *v161; // eax
  idWinVar *v162; // ebx
  int v163; // eax
  int i23; // eax
  int v165; // edi
  int v166; // ecx
  int v167; // ecx
  idWinVar **v168; // esi
  int i24; // eax
  int v170; // esi
  char *v171; // eax
  int intvalue; // ebx
  int v173; // edi
  char *v174; // esi
  char *v175; // eax
  char *v176; // esi
  int v177; // edi
  char *v178; // eax
  int v179; // ebx
  char *v180; // ecx
  unsigned __int8 v181; // al
  int i19; // esi
  idWinVar *v183; // eax
  idWinVar *v184; // ebx
  int v185; // eax
  int v186; // esi
  int v187; // eax
  int i20; // eax
  int v189; // ecx
  int v190; // ecx
  _DWORD *v191; // edi
  int i21; // eax
  const char *alloced; // edi
  idUserInterfaceLocal *gui; // esi
  int v195; // eax
  int v196; // esi
  char *v197; // eax
  int v198; // ebx
  char *v199; // ecx
  unsigned __int8 v200; // al
  int i16; // esi
  idWinVar *v202; // eax
  idWinVar *v203; // ebx
  int v204; // eax
  int i17; // eax
  int v206; // edi
  int v207; // ecx
  int v208; // ecx
  idWinVar **v209; // esi
  int i18; // eax
  int v211; // esi
  char *v212; // eax
  declType_t v213; // eax
  const char *v214; // eax
  const char *v215; // eax
  int len; // esi
  char *v217; // edi
  int Flags; // eax
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // edi
  idDict *v223; // ebx
  const char *v224; // eax
  drawWin_t *ChildByName; // eax
  drawWin_t *v226; // ebx
  bool *v227; // eax
  idWindow *v228; // eax
  idWindow *v229; // eax
  bool *v230; // eax
  idSimpleWindow *v231; // eax
  idSimpleWindow *v232; // eax
  bool v233; // zf
  int v234; // eax
  int m; // eax
  drawWin_t *v236; // ecx
  int v237; // edi
  int v238; // ecx
  int v239; // ecx
  drawWin_t *v240; // esi
  int n; // eax
  drawWin_t *v242; // ecx
  int v243; // ecx
  drawWin_t *v244; // edx
  idWindow *focusedChild; // eax
  idWindow_vtbl *v246; // edx
  idWindow_vtbl *v247; // eax
  int granularity; // eax
  int j; // eax
  drawWin_t *list; // ecx
  int num; // edi
  int size; // ecx
  int v253; // ecx
  int k; // eax
  drawWin_t *v255; // ecx
  void *v257; // [esp-1Ch] [ebp-768h]
  char *v258; // [esp-8h] [ebp-754h]
  char *v259; // [esp-8h] [ebp-754h]
  char *v260; // [esp-8h] [ebp-754h]
  char *v261; // [esp-8h] [ebp-754h]
  idWindow *v262; // [esp-8h] [ebp-754h]
  char *v263; // [esp-8h] [ebp-754h]
  char *v264; // [esp-8h] [ebp-754h]
  idGuiScriptList *ptr; // [esp+Ch] [ebp-740h]
  void *ptra; // [esp+Ch] [ebp-740h]
  void (__thiscall **ptrc)(_DWORD, idWindow *, char *, char *); // [esp+Ch] [ebp-740h]
  idSimpleWindow *ptrb; // [esp+Ch] [ebp-740h]
  char ret; // [esp+13h] [ebp-739h]
  rvNamedEvent *timeParm; // [esp+14h] [ebp-738h]
  idTimeLineEvent *timeParma; // [esp+14h] [ebp-738h]
  int *timeParmb; // [esp+14h] [ebp-738h]
  idStr work; // [esp+18h] [ebp-734h] BYREF
  idToken token; // [esp+38h] [ebp-714h] BYREF
  idStr scriptName; // [esp+88h] [ebp-6C4h] BYREF
  idToken v277; // [esp+A8h] [ebp-6A4h] BYREF
  idRectangle other; // [esp+F8h] [ebp-654h] BYREF
  idStr v279; // [esp+108h] [ebp-644h] BYREF
  idStr v280; // [esp+128h] [ebp-624h] BYREF
  idStr str; // [esp+148h] [ebp-604h] BYREF
  idStr v282; // [esp+168h] [ebp-5E4h] BYREF
  idStr v283; // [esp+188h] [ebp-5C4h] BYREF
  idStr v284; // [esp+1A8h] [ebp-5A4h] BYREF
  idStr v285; // [esp+1C8h] [ebp-584h] BYREF
  idStr out; // [esp+1E8h] [ebp-564h] BYREF
  idStr v287; // [esp+208h] [ebp-544h] BYREF
  idStr v288; // [esp+228h] [ebp-524h] BYREF
  idStr v289; // [esp+248h] [ebp-504h] BYREF
  idToken token2; // [esp+268h] [ebp-4E4h] BYREF
  idToken v291; // [esp+2B8h] [ebp-494h] BYREF
  idToken token5; // [esp+308h] [ebp-444h] BYREF
  idToken token4; // [esp+358h] [ebp-3F4h] BYREF
  idToken token3; // [esp+3A8h] [ebp-3A4h] BYREF
  idToken token6; // [esp+3F8h] [ebp-354h] BYREF
  idToken token7; // [esp+448h] [ebp-304h] BYREF
  idToken v297; // [esp+498h] [ebp-2B4h] BYREF
  idLexer src2; // [esp+4E8h] [ebp-264h] BYREF
  idLexer v299; // [esp+5B0h] [ebp-19Ch] BYREF
  idLexer v300; // [esp+678h] [ebp-D4h] BYREF
  int v301; // [esp+748h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  token2.floatvalue = 0.0;
  v301 = 7;
  token2.len = 0;
  token2.alloced = 20;
  token2.data = token2.baseBuffer;
  token2.baseBuffer[0] = 0;
  token3.floatvalue = 0.0;
  token3.len = 0;
  token3.alloced = 20;
  token3.data = token3.baseBuffer;
  token3.baseBuffer[0] = 0;
  token4.floatvalue = 0.0;
  token4.len = 0;
  token4.alloced = 20;
  token4.data = token4.baseBuffer;
  token4.baseBuffer[0] = 0;
  token5.floatvalue = 0.0;
  token5.len = 0;
  token5.alloced = 20;
  token5.data = token5.baseBuffer;
  token5.baseBuffer[0] = 0;
  token6.floatvalue = 0.0;
  token6.len = 0;
  token6.alloced = 20;
  token6.data = token6.baseBuffer;
  token6.baseBuffer[0] = 0;
  token7.floatvalue = 0.0;
  token7.len = 0;
  token7.alloced = 20;
  token7.data = token7.baseBuffer;
  token7.baseBuffer[0] = 0;
  work.len = 0;
  work.alloced = 20;
  work.data = work.baseBuffer;
  work.baseBuffer[0] = 0;
  if ( (_BYTE)rebuild )
    idWindow::CleanUp(this);
  if ( this->timeLineEvents.list )
    Memory::Free(this->timeLineEvents.list);
  this->timeLineEvents.list = 0;
  this->timeLineEvents.num = 0;
  this->timeLineEvents.size = 0;
  if ( this->transitions.list )
    Memory::Free(this->transitions.list);
  this->transitions.list = 0;
  this->transitions.num = 0;
  this->transitions.size = 0;
  for ( i = 0; i < this->namedEvents.num; ++i )
  {
    v6 = this->namedEvents.list[i];
    if ( v6 )
    {
      mEvent = v6->mEvent;
      LOBYTE(v301) = 8;
      ptr = mEvent;
      if ( mEvent )
      {
        idGuiScriptList::~idGuiScriptList(mEvent);
        Memory::Free(ptr);
      }
      LOBYTE(v301) = 7;
      idStr::FreeData(&v6->mName);
      Memory::Free(v6);
    }
    this->namedEvents.list[i] = 0;
  }
  if ( this->namedEvents.list )
    Memory::Free(this->namedEvents.list);
  this->namedEvents.list = 0;
  this->namedEvents.num = 0;
  this->namedEvents.size = 0;
  idParser::ExpectTokenType(src, 4, 0, &token);
  idWindow::SetInitialState(this, token.data);
  idParser::ExpectTokenString(src, "{");
  idParser::ExpectAnyToken(src, &token);
  ret = 1;
  (*(void (__thiscall **)(_DWORD, idWindow *))(**(_DWORD **)common.ip + 124))(*(_DWORD *)common.ip, this);
  if ( !idStr::Cmp(token.data, "}") )
  {
LABEL_539:
    v233 = this->expressionRegisters.num == 0;
    lastEval = this;
    if ( !v233 )
    {
      idRegisterList::SetToRegs(&this->regList, regs);
      idWindow::EvaluateRegisters(this, regs);
      idRegisterList::GetFromRegs(&this->regList, regs);
    }
    goto LABEL_541;
  }
  while ( 1 )
  {
    idParser::SetMarker(src);
    if ( !idStr::Cmp(token.data, "windowDef") || !idStr::Cmp(token.data, "animationDef") )
    {
      if ( idStr::Cmp(token.data, "animationDef") )
        goto LABEL_479;
      guiDict = this->visible.guiDict;
      this->visible.data = 0;
      if ( !guiDict )
      {
LABEL_478:
        memset(&other, 0, sizeof(other));
        idWinRectangle::operator=(&this->rect, &other);
LABEL_479:
        idParser::ExpectTokenType(src, 4, 0, &token);
        idToken::operator=((int)&token2, (int)&token);
        idParser::UnreadToken(src, &token);
        ChildByName = idWindow::FindChildByName(this, token2.data);
        v226 = ChildByName;
        if ( ChildByName && ChildByName->win )
        {
          v227 = (bool *)Mem_Alloc(4096, 0x13u);
          this->saveTemps = v227;
          qmemcpy(v227, idWindow::registerIsTemporary, 0x1000u);
          v226->win->Parse(v226->win, src, (bool)rebuild);
          qmemcpy(idWindow::registerIsTemporary, this->saveTemps, sizeof(idWindow::registerIsTemporary));
          Mem_Free(this->saveTemps);
          goto LABEL_537;
        }
        v228 = (idWindow *)Memory::Allocate(0x418u);
        LOBYTE(v301) = 9;
        if ( v228 )
        {
          idWindow::idWindow(v228, this->dc, this->gui);
          v10 = v229;
        }
        else
        {
          v10 = 0;
        }
        LOBYTE(v301) = 7;
        v230 = (bool *)Mem_Alloc(4096, 0x13u);
        this->saveTemps = v230;
        qmemcpy(v230, idWindow::registerIsTemporary, 0x1000u);
        v10->Parse(v10, src, (bool)rebuild);
        qmemcpy(idWindow::registerIsTemporary, this->saveTemps, sizeof(idWindow::registerIsTemporary));
        Mem_Free(this->saveTemps);
        v10->parent = this;
        if ( !idWindow::IsSimple(v10) )
        {
          idWindow::AddChild(this, v10);
          if ( (v10->flags & 0x800) != 0 )
          {
            focusedChild = this->gui->GetDesktop(this->gui)->focusedChild;
            if ( focusedChild )
            {
              v246 = focusedChild->__vftable;
              focusedChild->flags &= ~0x20u;
              v246->LoseFocus(focusedChild);
            }
            v247 = v10->__vftable;
            v10->flags |= 0x20u;
            v247->GainFocus(v10);
            this->gui->GetDesktop(this->gui)->focusedChild = v10;
          }
          if ( !this->drawWindows.list )
          {
            granularity = this->drawWindows.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->drawWindows.size )
              {
                v13 = granularity < this->drawWindows.num;
                this->drawWindows.size = granularity;
                if ( v13 )
                  this->drawWindows.num = granularity;
                this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * granularity);
                for ( j = 0; j < this->drawWindows.num; ++j )
                {
                  list = this->drawWindows.list;
                  list[j].win = *(idWindow **)(8 * j);
                  list[j].simp = *(idSimpleWindow **)(8 * j + 4);
                }
              }
            }
            else
            {
              this->drawWindows.list = 0;
              this->drawWindows.num = 0;
              this->drawWindows.size = 0;
            }
          }
          num = this->drawWindows.num;
          size = this->drawWindows.size;
          if ( num != size )
            goto LABEL_535;
          if ( !this->drawWindows.granularity )
            this->drawWindows.granularity = 16;
          v253 = this->drawWindows.granularity
               + size
               - (this->drawWindows.granularity + size) % this->drawWindows.granularity;
          if ( v253 > 0 )
          {
            if ( v253 != this->drawWindows.size )
            {
              v19 = this->drawWindows.list;
              this->drawWindows.size = v253;
              if ( v253 < num )
                this->drawWindows.num = v253;
              this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v253);
              for ( k = 0; k < this->drawWindows.num; ++k )
              {
                v255 = this->drawWindows.list;
                v255[k].win = v19[k].win;
                v255[k].simp = v19[k].simp;
              }
LABEL_533:
              if ( v19 )
                Memory::Free(v19);
            }
LABEL_535:
            v65 = this->drawWindows.list;
            v64 = this->drawWindows.num;
            v65[v64].win = v10;
LABEL_536:
            v65[v64].simp = 0;
            ++this->drawWindows.num;
            goto LABEL_537;
          }
LABEL_100:
          if ( this->drawWindows.list )
            Memory::Free(this->drawWindows.list);
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
          goto LABEL_535;
        }
        v231 = (idSimpleWindow *)Memory::Allocate(0x230u);
        LOBYTE(v301) = 10;
        if ( v231 )
        {
          idSimpleWindow::idSimpleWindow(v231, v10);
          ptrb = v232;
        }
        else
        {
          ptrb = 0;
        }
        v233 = this->drawWindows.list == 0;
        LOBYTE(v301) = 7;
        if ( v233 )
        {
          v234 = this->drawWindows.granularity;
          if ( v234 > 0 )
          {
            if ( v234 != this->drawWindows.size )
            {
              v13 = v234 < this->drawWindows.num;
              this->drawWindows.size = v234;
              if ( v13 )
                this->drawWindows.num = v234;
              this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v234);
              for ( m = 0; m < this->drawWindows.num; ++m )
              {
                v236 = this->drawWindows.list;
                v236[m].win = *(idWindow **)(8 * m);
                v236[m].simp = *(idSimpleWindow **)(8 * m + 4);
              }
            }
          }
          else
          {
            this->drawWindows.list = 0;
            this->drawWindows.num = 0;
            this->drawWindows.size = 0;
          }
        }
        v237 = this->drawWindows.num;
        v238 = this->drawWindows.size;
        if ( v237 == v238 )
        {
          if ( !this->drawWindows.granularity )
            this->drawWindows.granularity = 16;
          v239 = this->drawWindows.granularity
               + v238
               - (this->drawWindows.granularity + v238) % this->drawWindows.granularity;
          if ( v239 > 0 )
          {
            if ( v239 != this->drawWindows.size )
            {
              v240 = this->drawWindows.list;
              this->drawWindows.size = v239;
              if ( v239 < v237 )
                this->drawWindows.num = v239;
              this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v239);
              for ( n = 0; n < this->drawWindows.num; ++n )
              {
                v242 = this->drawWindows.list;
                v242[n].win = v240[n].win;
                v242[n].simp = v240[n].simp;
              }
              if ( v240 )
                Memory::Free(v240);
            }
          }
          else
          {
            if ( this->drawWindows.list )
              Memory::Free(this->drawWindows.list);
            this->drawWindows.list = 0;
            this->drawWindows.num = 0;
            this->drawWindows.size = 0;
          }
        }
        v243 = this->drawWindows.num;
        v244 = this->drawWindows.list;
        v244[v243].win = 0;
        v244[v243].simp = ptrb;
        ++this->drawWindows.num;
        ((void (__thiscall *)(idWindow *, int))v10->~idWindow)(v10, 1);
        goto LABEL_537;
      }
      name = this->visible.name;
      if ( name )
      {
        if ( *name != 42 )
        {
          data = this->visible.name;
          goto LABEL_477;
        }
        Key = idDict::FindKey(guiDict, name + 1);
        if ( Key )
        {
          data = Key->value->data;
LABEL_477:
          v223 = this->visible.guiDict;
          v224 = va("%i", this->visible.data);
          idDict::Set(v223, data, v224);
          goto LABEL_478;
        }
      }
      data = (char *)&entityFilter;
      goto LABEL_477;
    }
    if ( !idStr::Cmp(token.data, "editDef") )
    {
      v8 = (idEditWindow *)Memory::Allocate(0x500u);
      LOBYTE(v301) = 11;
      if ( v8 )
      {
        idEditWindow::idEditWindow(v8, this->dc, this->gui);
        v10 = v9;
      }
      else
      {
        v10 = 0;
      }
      LOBYTE(v301) = 7;
      v11 = (bool *)Mem_Alloc(4096, 0x13u);
      this->saveTemps = v11;
      qmemcpy(v11, idWindow::registerIsTemporary, 0x1000u);
      v10->Parse(v10, src, (bool)rebuild);
      qmemcpy(idWindow::registerIsTemporary, this->saveTemps, sizeof(idWindow::registerIsTemporary));
      Mem_Free(this->saveTemps);
      idWindow::AddChild(this, v10);
      v10->parent = this;
      if ( !this->drawWindows.list )
      {
        v12 = this->drawWindows.granularity;
        if ( v12 > 0 )
        {
          if ( v12 != this->drawWindows.size )
          {
            v13 = v12 < this->drawWindows.num;
            this->drawWindows.size = v12;
            if ( v13 )
              this->drawWindows.num = v12;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v12);
            for ( ii = 0; ii < this->drawWindows.num; ++ii )
            {
              v15 = this->drawWindows.list;
              v15[ii].win = *(idWindow **)(8 * ii);
              v15[ii].simp = *(idSimpleWindow **)(8 * ii + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v16 = this->drawWindows.num;
      v17 = this->drawWindows.size;
      if ( v16 != v17 )
        goto LABEL_535;
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v18 = this->drawWindows.granularity + v17 - (this->drawWindows.granularity + v17) % this->drawWindows.granularity;
      if ( v18 > 0 )
      {
        if ( v18 != this->drawWindows.size )
        {
          v19 = this->drawWindows.list;
          this->drawWindows.size = v18;
          if ( v18 < v16 )
            this->drawWindows.num = v18;
          this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v18);
          for ( jj = 0; jj < this->drawWindows.num; ++jj )
          {
            v21 = this->drawWindows.list;
            v21[jj].win = v19[jj].win;
            v21[jj].simp = v19[jj].simp;
          }
          goto LABEL_533;
        }
        goto LABEL_535;
      }
      goto LABEL_100;
    }
    if ( !idStr::Cmp(token.data, "choiceDef") )
    {
      v22 = (idChoiceWindow *)Memory::Allocate(0x5CCu);
      LOBYTE(v301) = 12;
      if ( v22 )
      {
        idChoiceWindow::idChoiceWindow(v22, this->dc, this->gui);
        v10 = v23;
      }
      else
      {
        v10 = 0;
      }
      LOBYTE(v301) = 7;
      v24 = (bool *)Mem_Alloc(4096, 0x13u);
      this->saveTemps = v24;
      qmemcpy(v24, idWindow::registerIsTemporary, 0x1000u);
      v10->Parse(v10, src, (bool)rebuild);
      qmemcpy(idWindow::registerIsTemporary, this->saveTemps, sizeof(idWindow::registerIsTemporary));
      Mem_Free(this->saveTemps);
      idWindow::AddChild(this, v10);
      v10->parent = this;
      if ( !this->drawWindows.list )
      {
        v25 = this->drawWindows.granularity;
        if ( v25 > 0 )
        {
          if ( v25 != this->drawWindows.size )
          {
            v13 = v25 < this->drawWindows.num;
            this->drawWindows.size = v25;
            if ( v13 )
              this->drawWindows.num = v25;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v25);
            for ( kk = 0; kk < this->drawWindows.num; ++kk )
            {
              v27 = this->drawWindows.list;
              v27[kk].win = *(idWindow **)(8 * kk);
              v27[kk].simp = *(idSimpleWindow **)(8 * kk + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v28 = this->drawWindows.num;
      v29 = this->drawWindows.size;
      if ( v28 != v29 )
        goto LABEL_535;
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v30 = this->drawWindows.granularity + v29 - (this->drawWindows.granularity + v29) % this->drawWindows.granularity;
      if ( v30 > 0 )
      {
        if ( v30 != this->drawWindows.size )
        {
          v19 = this->drawWindows.list;
          this->drawWindows.size = v30;
          if ( v30 < v28 )
            this->drawWindows.num = v30;
          this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v30);
          for ( mm = 0; mm < this->drawWindows.num; ++mm )
          {
            v32 = this->drawWindows.list;
            v32[mm].win = v19[mm].win;
            v32[mm].simp = v19[mm].simp;
          }
          goto LABEL_533;
        }
        goto LABEL_535;
      }
      goto LABEL_100;
    }
    if ( !idStr::Cmp(token.data, "sliderDef") )
    {
      v33 = (idSliderWindow *)Memory::Allocate(0x4FCu);
      LOBYTE(v301) = 13;
      if ( v33 )
      {
        idSliderWindow::idSliderWindow(v33, this->dc, this->gui);
        v10 = v34;
      }
      else
      {
        v10 = 0;
      }
      LOBYTE(v301) = 7;
      v35 = (bool *)Mem_Alloc(4096, 0x13u);
      this->saveTemps = v35;
      qmemcpy(v35, idWindow::registerIsTemporary, 0x1000u);
      v10->Parse(v10, src, (bool)rebuild);
      qmemcpy(idWindow::registerIsTemporary, this->saveTemps, sizeof(idWindow::registerIsTemporary));
      Mem_Free(this->saveTemps);
      idWindow::AddChild(this, v10);
      v10->parent = this;
      if ( !this->drawWindows.list )
      {
        v36 = this->drawWindows.granularity;
        if ( v36 > 0 )
        {
          if ( v36 != this->drawWindows.size )
          {
            v13 = v36 < this->drawWindows.num;
            this->drawWindows.size = v36;
            if ( v13 )
              this->drawWindows.num = v36;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v36);
            for ( nn = 0; nn < this->drawWindows.num; ++nn )
            {
              v38 = this->drawWindows.list;
              v38[nn].win = *(idWindow **)(8 * nn);
              v38[nn].simp = *(idSimpleWindow **)(8 * nn + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v39 = this->drawWindows.num;
      v40 = this->drawWindows.size;
      if ( v39 != v40 )
        goto LABEL_535;
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v41 = this->drawWindows.granularity + v40 - (this->drawWindows.granularity + v40) % this->drawWindows.granularity;
      if ( v41 > 0 )
      {
        if ( v41 != this->drawWindows.size )
        {
          v19 = this->drawWindows.list;
          this->drawWindows.size = v41;
          if ( v41 < v39 )
            this->drawWindows.num = v41;
          this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v41);
          for ( i1 = 0; i1 < this->drawWindows.num; ++i1 )
          {
            v43 = this->drawWindows.list;
            v43[i1].win = v19[i1].win;
            v43[i1].simp = v19[i1].simp;
          }
          goto LABEL_533;
        }
        goto LABEL_535;
      }
      goto LABEL_100;
    }
    if ( !idStr::Cmp(token.data, "markerDef") )
    {
      v44 = (idMarkerWindow *)Memory::Allocate(0xE574u);
      LOBYTE(v301) = 14;
      if ( v44 )
      {
        idMarkerWindow::idMarkerWindow(v44, this->dc, this->gui);
        v10 = v45;
      }
      else
      {
        v10 = 0;
      }
      LOBYTE(v301) = 7;
      v46 = (bool *)Mem_Alloc(4096, 0x13u);
      this->saveTemps = v46;
      qmemcpy(v46, idWindow::registerIsTemporary, 0x1000u);
      v10->Parse(v10, src, (bool)rebuild);
      qmemcpy(idWindow::registerIsTemporary, this->saveTemps, sizeof(idWindow::registerIsTemporary));
      Mem_Free(this->saveTemps);
      idWindow::AddChild(this, v10);
      v10->parent = this;
      if ( !this->drawWindows.list )
      {
        v47 = this->drawWindows.granularity;
        if ( v47 > 0 )
        {
          if ( v47 != this->drawWindows.size )
          {
            v13 = v47 < this->drawWindows.num;
            this->drawWindows.size = v47;
            if ( v13 )
              this->drawWindows.num = v47;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v47);
            for ( i2 = 0; i2 < this->drawWindows.num; ++i2 )
            {
              v49 = this->drawWindows.list;
              v49[i2].win = *(idWindow **)(8 * i2);
              v49[i2].simp = *(idSimpleWindow **)(8 * i2 + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v50 = this->drawWindows.num;
      v51 = this->drawWindows.size;
      if ( v50 != v51 )
        goto LABEL_535;
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v52 = this->drawWindows.granularity + v51 - (this->drawWindows.granularity + v51) % this->drawWindows.granularity;
      if ( v52 > 0 )
      {
        if ( v52 != this->drawWindows.size )
        {
          v19 = this->drawWindows.list;
          this->drawWindows.size = v52;
          if ( v52 < v50 )
            this->drawWindows.num = v52;
          this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v52);
          for ( i3 = 0; i3 < this->drawWindows.num; ++i3 )
          {
            v54 = this->drawWindows.list;
            v54[i3].win = v19[i3].win;
            v54[i3].simp = v19[i3].simp;
          }
          goto LABEL_533;
        }
        goto LABEL_535;
      }
      goto LABEL_100;
    }
    if ( !idStr::Cmp(token.data, "bindDef") )
    {
      v55 = (idBindWindow *)Memory::Allocate(0x44Cu);
      LOBYTE(v301) = 15;
      if ( v55 )
      {
        idBindWindow::idBindWindow(v55, this->dc, this->gui);
        v57 = v56;
      }
      else
      {
        v57 = 0;
      }
      LOBYTE(v301) = 7;
      idWindow::SaveExpressionParseState(this);
      v57->Parse(v57, src, (bool)rebuild);
      idWindow::RestoreExpressionParseState(this);
      idWindow::AddChild(this, v57);
      v57->parent = this;
      if ( !this->drawWindows.list )
      {
        v58 = this->drawWindows.granularity;
        if ( v58 > 0 )
        {
          if ( v58 != this->drawWindows.size )
          {
            v13 = v58 < this->drawWindows.num;
            this->drawWindows.size = v58;
            if ( v13 )
              this->drawWindows.num = v58;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v58);
            for ( i4 = 0; i4 < this->drawWindows.num; ++i4 )
            {
              v60 = this->drawWindows.list;
              v60[i4].win = *(idWindow **)(8 * i4);
              v60[i4].simp = *(idSimpleWindow **)(8 * i4 + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v61 = this->drawWindows.num;
      v62 = this->drawWindows.size;
      if ( v61 == v62 )
      {
        if ( !this->drawWindows.granularity )
          this->drawWindows.granularity = 16;
        v63 = this->drawWindows.granularity
            + v62
            - (this->drawWindows.granularity + v62) % this->drawWindows.granularity;
        if ( v63 <= 0 )
        {
LABEL_125:
          if ( this->drawWindows.list )
            Memory::Free(this->drawWindows.list);
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
          v64 = this->drawWindows.num;
          v65 = this->drawWindows.list;
          v65[v64].win = v57;
          goto LABEL_536;
        }
        if ( v63 != this->drawWindows.size )
        {
          v66 = this->drawWindows.list;
          this->drawWindows.size = v63;
          if ( v63 < v61 )
            this->drawWindows.num = v63;
          this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v63);
          for ( i5 = 0; i5 < this->drawWindows.num; ++i5 )
          {
            v68 = this->drawWindows.list;
            v68[i5].win = v66[i5].win;
            v68[i5].simp = v66[i5].simp;
          }
          goto LABEL_243;
        }
      }
LABEL_245:
      v64 = this->drawWindows.num;
      v65 = this->drawWindows.list;
      v65[v64].win = v57;
      goto LABEL_536;
    }
    if ( !idStr::Cmp(token.data, "listDef") )
    {
      v69 = (idListWindow *)Memory::Allocate(0x678u);
      LOBYTE(v301) = 16;
      if ( v69 )
      {
        idListWindow::idListWindow(v69, this->dc, this->gui);
        v57 = v70;
      }
      else
      {
        v57 = 0;
      }
      LOBYTE(v301) = 7;
      idWindow::SaveExpressionParseState(this);
      v57->Parse(v57, src, (bool)rebuild);
      idWindow::RestoreExpressionParseState(this);
      idWindow::AddChild(this, v57);
      v57->parent = this;
      if ( !this->drawWindows.list )
      {
        v71 = this->drawWindows.granularity;
        if ( v71 > 0 )
        {
          if ( v71 != this->drawWindows.size )
          {
            v13 = v71 < this->drawWindows.num;
            this->drawWindows.size = v71;
            if ( v13 )
              this->drawWindows.num = v71;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v71);
            for ( i6 = 0; i6 < this->drawWindows.num; ++i6 )
            {
              v73 = this->drawWindows.list;
              v73[i6].win = *(idWindow **)(8 * i6);
              v73[i6].simp = *(idSimpleWindow **)(8 * i6 + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v74 = this->drawWindows.num;
      v75 = this->drawWindows.size;
      if ( v74 != v75 )
        goto LABEL_245;
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v76 = this->drawWindows.granularity + v75 - (this->drawWindows.granularity + v75) % this->drawWindows.granularity;
      if ( v76 <= 0 )
        goto LABEL_125;
      if ( v76 == this->drawWindows.size )
        goto LABEL_245;
      v66 = this->drawWindows.list;
      this->drawWindows.size = v76;
      if ( v76 < v74 )
        this->drawWindows.num = v76;
      this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v76);
      for ( i7 = 0; i7 < this->drawWindows.num; ++i7 )
      {
        v78 = this->drawWindows.list;
        v78[i7].win = v66[i7].win;
        v78[i7].simp = v66[i7].simp;
      }
LABEL_243:
      if ( v66 )
        Memory::Free(v66);
      goto LABEL_245;
    }
    if ( !idStr::Cmp(token.data, "fieldDef") )
    {
      v79 = (idFieldWindow *)Memory::Allocate(0x44Cu);
      LOBYTE(v301) = 17;
      if ( v79 )
      {
        idFieldWindow::idFieldWindow(v79, this->dc, this->gui);
        v57 = v80;
      }
      else
      {
        v57 = 0;
      }
      LOBYTE(v301) = 7;
      idWindow::SaveExpressionParseState(this);
      v57->Parse(v57, src, (bool)rebuild);
      idWindow::RestoreExpressionParseState(this);
      idWindow::AddChild(this, v57);
      v57->parent = this;
      if ( !this->drawWindows.list )
      {
        v81 = this->drawWindows.granularity;
        if ( v81 > 0 )
        {
          if ( v81 != this->drawWindows.size )
          {
            v13 = v81 < this->drawWindows.num;
            this->drawWindows.size = v81;
            if ( v13 )
              this->drawWindows.num = v81;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v81);
            for ( i8 = 0; i8 < this->drawWindows.num; ++i8 )
            {
              v83 = this->drawWindows.list;
              v83[i8].win = *(idWindow **)(8 * i8);
              v83[i8].simp = *(idSimpleWindow **)(8 * i8 + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v84 = this->drawWindows.num;
      v85 = this->drawWindows.size;
      if ( v84 != v85 )
        goto LABEL_245;
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v86 = this->drawWindows.granularity + v85 - (this->drawWindows.granularity + v85) % this->drawWindows.granularity;
      if ( v86 <= 0 )
        goto LABEL_125;
      if ( v86 == this->drawWindows.size )
        goto LABEL_245;
      v66 = this->drawWindows.list;
      this->drawWindows.size = v86;
      if ( v86 < v84 )
        this->drawWindows.num = v86;
      this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v86);
      for ( i9 = 0; i9 < this->drawWindows.num; ++i9 )
      {
        v88 = this->drawWindows.list;
        v88[i9].win = v66[i9].win;
        v88[i9].simp = v66[i9].simp;
      }
      goto LABEL_243;
    }
    if ( !idStr::Cmp(token.data, "renderDef") )
    {
      v89 = (idRenderWindow *)Memory::Allocate(0x1034u);
      LOBYTE(v301) = 18;
      if ( v89 )
      {
        idRenderWindow::idRenderWindow(v89, this->dc, this->gui);
        v57 = v90;
      }
      else
      {
        v57 = 0;
      }
      LOBYTE(v301) = 7;
      idWindow::SaveExpressionParseState(this);
      v57->Parse(v57, src, (bool)rebuild);
      idWindow::RestoreExpressionParseState(this);
      idWindow::AddChild(this, v57);
      v57->parent = this;
      if ( !this->drawWindows.list )
      {
        v91 = this->drawWindows.granularity;
        if ( v91 > 0 )
        {
          if ( v91 != this->drawWindows.size )
          {
            v13 = v91 < this->drawWindows.num;
            this->drawWindows.size = v91;
            if ( v13 )
              this->drawWindows.num = v91;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v91);
            for ( i10 = 0; i10 < this->drawWindows.num; ++i10 )
            {
              v93 = this->drawWindows.list;
              v93[i10].win = *(idWindow **)(8 * i10);
              v93[i10].simp = *(idSimpleWindow **)(8 * i10 + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v94 = this->drawWindows.num;
      v95 = this->drawWindows.size;
      if ( v94 != v95 )
        goto LABEL_245;
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v96 = this->drawWindows.granularity + v95 - (this->drawWindows.granularity + v95) % this->drawWindows.granularity;
      if ( v96 <= 0 )
        goto LABEL_125;
      if ( v96 == this->drawWindows.size )
        goto LABEL_245;
      v66 = this->drawWindows.list;
      this->drawWindows.size = v96;
      if ( v96 < v94 )
        this->drawWindows.num = v96;
      this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v96);
      for ( i11 = 0; i11 < this->drawWindows.num; ++i11 )
      {
        v98 = this->drawWindows.list;
        v98[i11].win = v66[i11].win;
        v98[i11].simp = v66[i11].simp;
      }
      goto LABEL_243;
    }
    if ( !idStr::Cmp(token.data, "graphDef") )
    {
      v99 = (idGraphWindow *)Memory::Allocate(0x550u);
      LOBYTE(v301) = 19;
      if ( v99 )
      {
        idGraphWindow::idGraphWindow(v99, this->dc, this->gui);
        v57 = v100;
      }
      else
      {
        v57 = 0;
      }
      LOBYTE(v301) = 7;
      idWindow::SaveExpressionParseState(this);
      v57->Parse(v57, src, (bool)rebuild);
      idWindow::RestoreExpressionParseState(this);
      idWindow::AddChild(this, v57);
      v57->parent = this;
      if ( !this->drawWindows.list )
      {
        v101 = this->drawWindows.granularity;
        if ( v101 > 0 )
        {
          if ( v101 != this->drawWindows.size )
          {
            v13 = v101 < this->drawWindows.num;
            this->drawWindows.size = v101;
            if ( v13 )
              this->drawWindows.num = v101;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v101);
            for ( i12 = 0; i12 < this->drawWindows.num; ++i12 )
            {
              v103 = this->drawWindows.list;
              v103[i12].win = *(idWindow **)(8 * i12);
              v103[i12].simp = *(idSimpleWindow **)(8 * i12 + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v104 = this->drawWindows.num;
      v105 = this->drawWindows.size;
      if ( v104 != v105 )
        goto LABEL_245;
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v106 = this->drawWindows.granularity
           + v105
           - (this->drawWindows.granularity + v105) % this->drawWindows.granularity;
      if ( v106 <= 0 )
        goto LABEL_125;
      if ( v106 == this->drawWindows.size )
        goto LABEL_245;
      v66 = this->drawWindows.list;
      this->drawWindows.size = v106;
      if ( v106 < v104 )
        this->drawWindows.num = v106;
      this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v106);
      for ( i13 = 0; i13 < this->drawWindows.num; ++i13 )
      {
        v108 = this->drawWindows.list;
        v108[i13].win = v66[i13].win;
        v108[i13].simp = v66[i13].simp;
      }
      goto LABEL_243;
    }
    if ( !idStr::Cmp(token.data, "popupDef") )
    {
      v109 = (rvPopupWindow *)Memory::Allocate(0x65Cu);
      LOBYTE(v301) = 20;
      if ( v109 )
      {
        rvPopupWindow::rvPopupWindow(v109, this->dc, this->gui);
        v57 = v110;
      }
      else
      {
        v57 = 0;
      }
      LOBYTE(v301) = 7;
      idWindow::SaveExpressionParseState(this);
      v57->Parse(v57, src, (bool)rebuild);
      idWindow::RestoreExpressionParseState(this);
      idWindow::AddChild(this, v57);
      v57->parent = this;
      if ( !this->drawWindows.list )
      {
        v111 = this->drawWindows.granularity;
        if ( v111 > 0 )
        {
          if ( v111 != this->drawWindows.size )
          {
            v13 = v111 < this->drawWindows.num;
            this->drawWindows.size = v111;
            if ( v13 )
              this->drawWindows.num = v111;
            this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v111);
            for ( i14 = 0; i14 < this->drawWindows.num; ++i14 )
            {
              v113 = this->drawWindows.list;
              v113[i14].win = *(idWindow **)(8 * i14);
              v113[i14].simp = *(idSimpleWindow **)(8 * i14 + 4);
            }
          }
        }
        else
        {
          this->drawWindows.list = 0;
          this->drawWindows.num = 0;
          this->drawWindows.size = 0;
        }
      }
      v114 = this->drawWindows.num;
      v115 = this->drawWindows.size;
      if ( v114 != v115 )
        goto LABEL_245;
      if ( !this->drawWindows.granularity )
        this->drawWindows.granularity = 16;
      v116 = this->drawWindows.granularity
           + v115
           - (this->drawWindows.granularity + v115) % this->drawWindows.granularity;
      if ( v116 <= 0 )
        goto LABEL_125;
      if ( v116 == this->drawWindows.size )
        goto LABEL_245;
      v66 = this->drawWindows.list;
      this->drawWindows.size = v116;
      if ( v116 < v114 )
        this->drawWindows.num = v116;
      this->drawWindows.list = (drawWin_t *)Memory::Allocate(8 * v116);
      for ( i15 = 0; i15 < this->drawWindows.num; ++i15 )
      {
        v118 = this->drawWindows.list;
        v118[i15].win = v66[i15].win;
        v118[i15].simp = v66[i15].simp;
      }
      goto LABEL_243;
    }
    if ( idStr::Cmp(token.data, "onNamedEvent") )
    {
      if ( idStr::Cmp(token.data, "onTime") )
      {
        if ( idStr::Cmp(token.data, "definefloat") )
        {
          if ( idStr::Cmp(token.data, "defineicon") )
          {
            if ( idStr::Cmp(token.data, "definevec4") )
            {
              if ( idStr::Cmp(token.data, "float") )
              {
                if ( idStr::Cmp(token.data, "requiredecl") )
                {
                  if ( idWindow::ParseScriptEntry(this, token.data, src) )
                  {
                    if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 4) )
                    {
                      v279.len = 0;
                      v279.alloced = 20;
                      v279.data = v279.baseBuffer;
                      v279.baseBuffer[0] = 0;
                      v282.alloced = 20;
                      v282.len = 0;
                      v282.data = v282.baseBuffer;
                      v282.baseBuffer[0] = 0;
                      LOBYTE(v301) = 37;
                      idParser::GetStringFromMarker(src, &v279, 0);
                      len = v279.len;
                      v217 = v279.data;
                      Flags = idParser::GetFlags(src);
                      idLexer::idLexer(&v300, v217, len, &entityFilter, Flags);
                      LOBYTE(v301) = 38;
                      idLexer::ParseBracedSectionExact(&v300, &v282, 1);
                      (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *))(**(_DWORD **)common.ip + 136))(
                        *(_DWORD *)common.ip,
                        this,
                        token.data,
                        v282.data);
                      LOBYTE(v301) = 37;
                      idLexer::~idLexer(&v300);
                      LOBYTE(v301) = 36;
                      idStr::FreeData(&v282);
                      LOBYTE(v301) = 7;
                      idStr::FreeData(&v279);
                    }
                  }
                  else if ( ((unsigned __int8 (__thiscall *)(idWindow *, char *, idParser *, int))this->ParseInternalVar)(
                              this,
                              token.data,
                              src,
                              a2) )
                  {
                    a2 = 4;
                    if ( (*(int (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip) )
                    {
                      v283.len = 0;
                      v283.alloced = 20;
                      v283.data = v283.baseBuffer;
                      v283.baseBuffer[0] = 0;
                      LOBYTE(v301) = 39;
                      idParser::GetStringFromMarker(src, &v283, 0);
                      (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *, _DWORD))(**(_DWORD **)common.ip + 144))(
                        *(_DWORD *)common.ip,
                        this,
                        token.data,
                        v283.data,
                        0);
                      LOBYTE(v301) = 7;
                      idStr::FreeData(&v283);
                    }
                  }
                  else
                  {
                    idWindow::ParseRegEntry(this, (const char *)token.alloced, src);
                    a2 = 4;
                    if ( (*(int (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip) )
                    {
                      v285.len = 0;
                      v285.alloced = 20;
                      v285.data = v285.baseBuffer;
                      v285.baseBuffer[0] = 0;
                      LOBYTE(v301) = 40;
                      idParser::GetStringFromMarker(src, &v285, 0);
                      (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *, _DWORD))(**(_DWORD **)common.ip + 144))(
                        *(_DWORD *)common.ip,
                        this,
                        token.data,
                        v285.data,
                        0);
                      LOBYTE(v301) = 7;
                      idStr::FreeData(&v285);
                    }
                  }
                }
                else
                {
                  v297.floatvalue = 0.0;
                  v297.len = 0;
                  v297.alloced = 20;
                  v297.data = v297.baseBuffer;
                  v297.baseBuffer[0] = 0;
                  LOBYTE(v301) = 35;
                  idParser::ReadToken(src, &token);
                  idParser::ReadToken(src, &v297);
                  v213 = declManager->GetDeclTypeFromName(declManager, token.data);
                  if ( v213 >= DECL_MAX_TYPES )
                  {
                    v215 = va("Unknown decl type: %s", token.data);
                    idParser::Error(src, v215);
                  }
                  else if ( !declManager->FindType(declManager, v213, v297.data, 1, 0) )
                  {
                    v214 = va("Unknown %s decl %s", token.data, v297.data);
                    idParser::Error(src, v214);
                    LOBYTE(v301) = 7;
                    idStr::FreeData(&v297);
                    goto LABEL_537;
                  }
                  LOBYTE(v301) = 7;
                  idStr::FreeData(&v297);
                }
              }
              else
              {
                idParser::ReadToken(src, &token);
                v198 = token.len;
                if ( token.len + 1 > work.alloced )
                  idStr::ReAllocate(&work, token.len + 1, 0);
                qmemcpy(work.data, token.data, v198);
                work.data[v198] = 0;
                v199 = work.data;
                work.len = v198;
                v200 = *work.data;
                for ( i16 = 0; v200; v200 = work.data[i16] )
                {
                  if ( idStr::lowerCaseCharacter[v200] )
                    v200 = idStr::lowerCaseCharacter[v200];
                  *v199 = v200;
                  v199 = &work.data[++i16];
                }
                v202 = (idWinVar *)Memory::Allocate(0x14u);
                if ( v202 )
                {
                  v202->guiDict = 0;
                  v202->name = 0;
                  v202->eval = 1;
                  v202->__vftable = (idWinVar_vtbl *)&idWinFloat::`vftable';
                  v203 = v202;
                }
                else
                {
                  v203 = 0;
                }
                idWinVar::SetName(v203, work.data);
                if ( !this->definedVars.list )
                {
                  v204 = this->definedVars.granularity;
                  if ( v204 > 0 )
                  {
                    if ( v204 != this->definedVars.size )
                    {
                      v13 = v204 < this->definedVars.num;
                      this->definedVars.size = v204;
                      if ( v13 )
                        this->definedVars.num = v204;
                      this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v204);
                      for ( i17 = 0; i17 < this->definedVars.num; ++i17 )
                        this->definedVars.list[i17] = *(idWinVar **)(4 * i17);
                    }
                  }
                  else
                  {
                    this->definedVars.list = 0;
                    this->definedVars.num = 0;
                    this->definedVars.size = 0;
                  }
                }
                v206 = this->definedVars.num;
                v207 = this->definedVars.size;
                if ( v206 == v207 )
                {
                  if ( !this->definedVars.granularity )
                    this->definedVars.granularity = 16;
                  v208 = this->definedVars.granularity
                       + v207
                       - (this->definedVars.granularity + v207) % this->definedVars.granularity;
                  if ( v208 > 0 )
                  {
                    if ( v208 != this->definedVars.size )
                    {
                      v209 = this->definedVars.list;
                      this->definedVars.size = v208;
                      if ( v208 < v206 )
                        this->definedVars.num = v208;
                      this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v208);
                      for ( i18 = 0; i18 < this->definedVars.num; ++i18 )
                        this->definedVars.list[i18] = v209[i18];
                      if ( v209 )
                        Memory::Free(v209);
                    }
                  }
                  else
                  {
                    if ( this->definedVars.list )
                      Memory::Free(this->definedVars.list);
                    this->definedVars.list = 0;
                    this->definedVars.num = 0;
                    this->definedVars.size = 0;
                  }
                }
                this->definedVars.list[this->definedVars.num++] = v203;
                idParser::SetMarker(src);
                idRegisterList::AddReg(&this->regList, work.data, 1, src, this, v203);
                if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 4) )
                {
                  v288.len = 0;
                  v288.alloced = 20;
                  v288.data = v288.baseBuffer;
                  v288.baseBuffer[0] = 0;
                  LOBYTE(v301) = 34;
                  idParser::GetStringFromMarker(src, &v288, 1);
                  v211 = **(_DWORD **)common.ip;
                  v264 = v288.data;
                  v212 = va("float\t\"%s\"", token.data);
                  (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *))(v211 + 140))(
                    *(_DWORD *)common.ip,
                    this,
                    v212,
                    v264);
                  LOBYTE(v301) = 7;
                  idStr::FreeData(&v288);
                }
              }
            }
            else
            {
              idParser::ReadToken(src, &token);
              v179 = token.len;
              if ( token.len + 1 > work.alloced )
                idStr::ReAllocate(&work, token.len + 1, 0);
              qmemcpy(work.data, token.data, v179);
              work.data[v179] = 0;
              v180 = work.data;
              work.len = v179;
              v181 = *work.data;
              for ( i19 = 0; v181; v181 = work.data[i19] )
              {
                if ( idStr::lowerCaseCharacter[v181] )
                  v181 = idStr::lowerCaseCharacter[v181];
                *v180 = v181;
                v180 = &work.data[++i19];
              }
              v183 = (idWinVar *)Memory::Allocate(0x20u);
              if ( v183 )
              {
                v183->guiDict = 0;
                v183->name = 0;
                v183->eval = 1;
                v183->__vftable = (idWinVar_vtbl *)&idWinVec4::`vftable';
                v184 = v183;
              }
              else
              {
                v184 = 0;
              }
              idWinVar::SetName(v184, work.data);
              idParser::SetMarker(src);
              v185 = ((int (__thiscall *)(idUserInterfaceLocal *, int))this->gui->GetDesktop)(this->gui, a2);
              v186 = v185 + 648;
              if ( !*(_DWORD *)(v185 + 660) )
              {
                v187 = *(_DWORD *)(v185 + 656);
                if ( v187 > 0 )
                {
                  if ( v187 != *(_DWORD *)(v186 + 4) )
                  {
                    v13 = v187 < *(_DWORD *)v186;
                    *(_DWORD *)(v186 + 4) = v187;
                    if ( v13 )
                      *(_DWORD *)v186 = v187;
                    *(_DWORD *)(v186 + 12) = Memory::Allocate(4 * v187);
                    for ( i20 = 0; i20 < *(_DWORD *)v186; ++i20 )
                      *(_DWORD *)(*(_DWORD *)(v186 + 12) + 4 * i20) = *(_DWORD *)(4 * i20);
                  }
                }
                else
                {
                  *(_DWORD *)(v186 + 12) = 0;
                  *(_DWORD *)v186 = 0;
                  *(_DWORD *)(v186 + 4) = 0;
                }
              }
              v189 = *(_DWORD *)(v186 + 4);
              if ( *(_DWORD *)v186 == v189 )
              {
                if ( !*(_DWORD *)(v186 + 8) )
                  *(_DWORD *)(v186 + 8) = 16;
                v190 = *(_DWORD *)(v186 + 8) + v189 - (*(_DWORD *)(v186 + 8) + v189) % *(_DWORD *)(v186 + 8);
                if ( v190 > 0 )
                {
                  if ( v190 != *(_DWORD *)(v186 + 4) )
                  {
                    v13 = v190 < *(_DWORD *)v186;
                    v191 = *(_DWORD **)(v186 + 12);
                    *(_DWORD *)(v186 + 4) = v190;
                    if ( v13 )
                      *(_DWORD *)v186 = v190;
                    *(_DWORD *)(v186 + 12) = Memory::Allocate(4 * v190);
                    for ( i21 = 0; i21 < *(_DWORD *)v186; ++i21 )
                      *(_DWORD *)(*(_DWORD *)(v186 + 12) + 4 * i21) = v191[i21];
                    if ( v191 )
                      Memory::Free(v191);
                  }
                }
                else
                {
                  if ( *(_DWORD *)(v186 + 12) )
                    Memory::Free(*(void **)(v186 + 12));
                  *(_DWORD *)(v186 + 12) = 0;
                  *(_DWORD *)v186 = 0;
                  *(_DWORD *)(v186 + 4) = 0;
                }
              }
              *(_DWORD *)(*(_DWORD *)(v186 + 12) + 4 * (*(_DWORD *)v186)++) = v184;
              alloced = (const char *)work.alloced;
              gui = this->gui;
              ret = HIBYTE(gui);
              v262 = gui->GetDesktop(gui);
              v195 = (int)gui->GetDesktop(gui);
              idRegisterList::AddReg((idRegisterList *)(v195 + 984), alloced, 0, rebuild, v262, v184);
              a2 = 4;
              if ( (*(int (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip) )
              {
                v284.len = 0;
                v284.alloced = 20;
                v284.data = v284.baseBuffer;
                v284.baseBuffer[0] = 0;
                LOBYTE(v301) = 33;
                idParser::GetStringFromMarker(src, &v284, 1);
                v196 = **(_DWORD **)common.ip;
                v263 = v284.data;
                v197 = va("definevec4\t\"%s\"", token.data);
                (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *))(v196 + 140))(
                  *(_DWORD *)common.ip,
                  this,
                  v197,
                  v263);
                LOBYTE(v301) = 7;
                idStr::FreeData(&v284);
              }
            }
          }
          else
          {
            v291.floatvalue = 0.0;
            v291.len = 0;
            v291.alloced = 20;
            v291.data = v291.baseBuffer;
            v291.baseBuffer[0] = 0;
            v277.floatvalue = 0.0;
            v277.len = 0;
            v277.alloced = 20;
            v277.data = v277.baseBuffer;
            v277.baseBuffer[0] = 0;
            LOBYTE(v301) = 32;
            idParser::ReadToken(src, &token);
            idParser::ReadToken(src, &v291);
            if ( !idParser::ReadToken(src, &v277) || idStr::Icmp(v277.data, ",") )
            {
              idParser::UnreadToken(src, &v277);
              idDeviceContext::RegisterIcon(this->dc, token.data, v291.data, -1, -1, -1, -1);
              if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 4) )
              {
                v176 = token.data;
                v177 = **(_DWORD **)common.ip;
                v261 = va("\"%s\"", v291.data);
                v178 = va("defineicon\t\"%s\"", v176);
                (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *))(v177 + 140))(
                  *(_DWORD *)common.ip,
                  this,
                  v178,
                  v261);
              }
            }
            else
            {
              idParser::ReadToken(src, &v277);
              if ( v277.type == 3 )
              {
                if ( (v277.subtype & 0x10000) == 0 )
                  idToken::NumberValue(&v277);
                ptra = (void *)v277.intvalue;
              }
              else
              {
                ptra = 0;
              }
              idParser::ExpectTokenString(src, ",");
              idParser::ReadToken(src, &v277);
              if ( v277.type == 3 )
              {
                if ( (v277.subtype & 0x10000) == 0 )
                  idToken::NumberValue(&v277);
                timeParmb = (int *)v277.intvalue;
              }
              else
              {
                timeParmb = 0;
              }
              idParser::ExpectTokenString(src, ",");
              idParser::ReadToken(src, &v277);
              if ( v277.type == 3 )
              {
                if ( (v277.subtype & 0x10000) == 0 )
                  idToken::NumberValue(&v277);
                intvalue = v277.intvalue;
              }
              else
              {
                intvalue = 0;
              }
              idParser::ExpectTokenString(src, ",");
              idParser::ReadToken(src, &v277);
              if ( v277.type == 3 )
              {
                if ( (v277.subtype & 0x10000) == 0 )
                  idToken::NumberValue(&v277);
                v173 = v277.intvalue;
              }
              else
              {
                v173 = 0;
              }
              idDeviceContext::RegisterIcon(this->dc, token.data, v291.data, (int)ptra, (int)timeParmb, intvalue, v173);
              if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 4) )
              {
                (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
                  common.type,
                  "TTimo - idWindow::Parse EDITOR_GUI: fixed a string format bug - best guess on the fix. Please verify");
                v174 = token.data;
                v257 = ptra;
                ptrc = **(void (__thiscall ****)(_DWORD, idWindow *, char *, char *))common.ip;
                v260 = va("\"%s\"\t%d,%d,%d,%d", v291.data, v257, timeParmb, intvalue, v173);
                v175 = va("defineicon\t\"%s\"", v174);
                ptrc[35](*(_DWORD *)common.ip, this, v175, v260);
              }
            }
            LOBYTE(v301) = 31;
            idStr::FreeData(&v277);
            LOBYTE(v301) = 7;
            idStr::FreeData(&v291);
          }
        }
        else
        {
          idParser::ReadToken(src, &token);
          v157 = token.len;
          if ( token.len + 1 > work.alloced )
            idStr::ReAllocate(&work, token.len + 1, 0);
          qmemcpy(work.data, token.data, v157);
          work.data[v157] = 0;
          v158 = work.data;
          work.len = v157;
          v159 = *work.data;
          for ( i22 = 0; v159; v159 = work.data[i22] )
          {
            if ( idStr::lowerCaseCharacter[v159] )
              v159 = idStr::lowerCaseCharacter[v159];
            *v158 = v159;
            v158 = &work.data[++i22];
          }
          v161 = (idWinVar *)Memory::Allocate(0x14u);
          if ( v161 )
          {
            v161->guiDict = 0;
            v161->name = 0;
            v161->eval = 1;
            v161->__vftable = (idWinVar_vtbl *)&idWinFloat::`vftable';
            v162 = v161;
          }
          else
          {
            v162 = 0;
          }
          idWinVar::SetName(v162, work.data);
          if ( !this->definedVars.list )
          {
            v163 = this->definedVars.granularity;
            if ( v163 > 0 )
            {
              if ( v163 != this->definedVars.size )
              {
                v13 = v163 < this->definedVars.num;
                this->definedVars.size = v163;
                if ( v13 )
                  this->definedVars.num = v163;
                this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v163);
                for ( i23 = 0; i23 < this->definedVars.num; ++i23 )
                  this->definedVars.list[i23] = *(idWinVar **)(4 * i23);
              }
            }
            else
            {
              this->definedVars.list = 0;
              this->definedVars.num = 0;
              this->definedVars.size = 0;
            }
          }
          v165 = this->definedVars.num;
          v166 = this->definedVars.size;
          if ( v165 == v166 )
          {
            if ( !this->definedVars.granularity )
              this->definedVars.granularity = 16;
            v167 = this->definedVars.granularity
                 + v166
                 - (this->definedVars.granularity + v166) % this->definedVars.granularity;
            if ( v167 > 0 )
            {
              if ( v167 != this->definedVars.size )
              {
                v168 = this->definedVars.list;
                this->definedVars.size = v167;
                if ( v167 < v165 )
                  this->definedVars.num = v167;
                this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v167);
                for ( i24 = 0; i24 < this->definedVars.num; ++i24 )
                  this->definedVars.list[i24] = v168[i24];
                if ( v168 )
                  Memory::Free(v168);
              }
            }
            else
            {
              if ( this->definedVars.list )
                Memory::Free(this->definedVars.list);
              this->definedVars.list = 0;
              this->definedVars.num = 0;
              this->definedVars.size = 0;
            }
          }
          this->definedVars.list[this->definedVars.num++] = v162;
          idParser::SetMarker(src);
          idRegisterList::AddReg(&this->regList, work.data, 1, src, this, v162);
          if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 4) )
          {
            v289.len = 0;
            v289.alloced = 20;
            v289.data = v289.baseBuffer;
            v289.baseBuffer[0] = 0;
            LOBYTE(v301) = 30;
            idParser::GetStringFromMarker(src, &v289, 1);
            v170 = **(_DWORD **)common.ip;
            v259 = v289.data;
            v171 = va("definefloat\t\"%s\"", token.data);
            (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *))(v170 + 140))(
              *(_DWORD *)common.ip,
              this,
              v171,
              v259);
            LOBYTE(v301) = 7;
            idStr::FreeData(&v289);
          }
        }
      }
      else
      {
        v133 = (idTimeLineEvent *)Memory::Allocate(0xCu);
        LOBYTE(v301) = 25;
        if ( v133 )
        {
          idTimeLineEvent::idTimeLineEvent(v133);
          p_time = &v134->time;
          timeParma = v134;
        }
        else
        {
          timeParma = 0;
          p_time = 0;
        }
        LOBYTE(v301) = 7;
        if ( !idParser::ReadToken(src, &token) )
        {
          idParser::Error(src, "Unexpected end of file");
          goto LABEL_545;
        }
        scriptName.alloced = 20;
        scriptName.data = scriptName.baseBuffer;
        scriptName.baseBuffer[0] = 0;
        v136 = 0;
        do
        {
          v137 = aOntime_1[v136];
          scriptName.baseBuffer[v136++] = v137;
        }
        while ( v137 );
        scriptName.len = 7;
        LOBYTE(v301) = 26;
        if ( idStr::Icmp(token.data, "+") )
        {
          *p_time = atoi(token.data);
        }
        else
        {
          v138 = scriptName.len + 1;
          if ( scriptName.len + 2 > scriptName.alloced )
            idStr::ReAllocate(&scriptName, scriptName.len + 2, 1);
          v139 = 0;
          v140 = 43;
          do
          {
            v141 = &scriptName.data[v139++];
            v141[scriptName.len] = v140;
            v140 = asc_102B06E8[v139];
          }
          while ( v140 );
          scriptName.len = v138;
          scriptName.data[v138] = 0;
          if ( !idParser::ReadToken(src, &token) )
          {
            idParser::Error(src, "Unexpected end of file");
            LOBYTE(v301) = 7;
            idStr::FreeData(&scriptName);
            goto LABEL_545;
          }
          v142 = this->timeLineEvents.num;
          if ( v142 )
            *p_time = this->timeLineEvents.list[v142 - 1]->time;
          else
            *p_time = 0;
          *p_time += atoi(token.data);
        }
        v143 = scriptName.len + token.len;
        if ( scriptName.len + token.len + 1 > scriptName.alloced )
          idStr::ReAllocate(&scriptName, scriptName.len + token.len + 1, 1);
        for ( i25 = 0; i25 < token.len; v146[scriptName.len] = v145 )
        {
          v145 = token.data[i25];
          v146 = &scriptName.data[i25++];
        }
        scriptName.len = v143;
        scriptName.data[v143] = 0;
        idParser::SetMarker(src);
        if ( !idWindow::ParseScript(this, src, timeParma->event, &timeParma->time, 0) )
        {
          ret = 0;
          LOBYTE(v301) = 7;
          idStr::FreeData(&scriptName);
          goto LABEL_541;
        }
        if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 4) )
        {
          v280.len = 0;
          v280.alloced = 20;
          v280.data = v280.baseBuffer;
          v280.baseBuffer[0] = 0;
          v287.len = 0;
          v287.alloced = 20;
          v287.data = v287.baseBuffer;
          v287.baseBuffer[0] = 0;
          LOBYTE(v301) = 28;
          idParser::GetStringFromMarker(src, &v280, 0);
          v147 = v280.len;
          v148 = v280.data;
          v149 = idParser::GetFlags(src);
          idLexer::idLexer(&v299, v148, v147, &entityFilter, v149);
          LOBYTE(v301) = 29;
          idLexer::ParseBracedSectionExact(&v299, &v287, 1);
          (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *))(**(_DWORD **)common.ip + 136))(
            *(_DWORD *)common.ip,
            this,
            scriptName.data,
            v287.data);
          LOBYTE(v301) = 28;
          idLexer::~idLexer(&v299);
          LOBYTE(v301) = 27;
          idStr::FreeData(&v287);
          LOBYTE(v301) = 26;
          idStr::FreeData(&v280);
        }
        timeParma->pending = 1;
        if ( !this->timeLineEvents.list )
        {
          v150 = this->timeLineEvents.granularity;
          if ( v150 > 0 )
          {
            if ( v150 != this->timeLineEvents.size )
            {
              v13 = v150 < this->timeLineEvents.num;
              this->timeLineEvents.size = v150;
              if ( v13 )
                this->timeLineEvents.num = v150;
              this->timeLineEvents.list = (idTimeLineEvent **)Memory::Allocate(4 * v150);
              for ( i26 = 0; i26 < this->timeLineEvents.num; ++i26 )
                this->timeLineEvents.list[i26] = *(idTimeLineEvent **)(4 * i26);
            }
          }
          else
          {
            this->timeLineEvents.list = 0;
            this->timeLineEvents.num = 0;
            this->timeLineEvents.size = 0;
          }
        }
        v152 = this->timeLineEvents.num;
        v153 = this->timeLineEvents.size;
        if ( v152 == v153 )
        {
          if ( !this->timeLineEvents.granularity )
            this->timeLineEvents.granularity = 16;
          v154 = this->timeLineEvents.granularity
               + v153
               - (this->timeLineEvents.granularity + v153) % this->timeLineEvents.granularity;
          if ( v154 > 0 )
          {
            if ( v154 != this->timeLineEvents.size )
            {
              v155 = this->timeLineEvents.list;
              this->timeLineEvents.size = v154;
              if ( v154 < v152 )
                this->timeLineEvents.num = v154;
              this->timeLineEvents.list = (idTimeLineEvent **)Memory::Allocate(4 * v154);
              for ( i27 = 0; i27 < this->timeLineEvents.num; ++i27 )
                this->timeLineEvents.list[i27] = v155[i27];
              if ( v155 )
                Memory::Free(v155);
            }
          }
          else
          {
            if ( this->timeLineEvents.list )
              Memory::Free(this->timeLineEvents.list);
            this->timeLineEvents.list = 0;
            this->timeLineEvents.num = 0;
            this->timeLineEvents.size = 0;
          }
        }
        this->timeLineEvents.list[this->timeLineEvents.num++] = timeParma;
        LOBYTE(v301) = 7;
        idStr::FreeData(&scriptName);
      }
    }
    else
    {
      if ( !idParser::ReadToken(src, &token) )
      {
        idParser::Error(src, "Expected event name");
LABEL_545:
        LOBYTE(v301) = 6;
        idStr::FreeData(&work);
        LOBYTE(v301) = 5;
        idStr::FreeData(&token7);
        LOBYTE(v301) = 4;
        idStr::FreeData(&token6);
        LOBYTE(v301) = 3;
        idStr::FreeData(&token5);
        LOBYTE(v301) = 2;
        idStr::FreeData(&token4);
        LOBYTE(v301) = 1;
        idStr::FreeData(&token3);
        LOBYTE(v301) = 0;
        idStr::FreeData(&token2);
        v301 = -1;
        idStr::FreeData(&token);
        return 0;
      }
      v119 = (rvNamedEvent *)Memory::Allocate(0x24u);
      LOBYTE(v301) = 21;
      if ( v119 )
      {
        rvNamedEvent::rvNamedEvent(v119, token.data);
        timeParm = v120;
      }
      else
      {
        timeParm = 0;
      }
      LOBYTE(v301) = 7;
      idParser::SetMarker(src);
      if ( !idWindow::ParseScript(this, src, timeParm->mEvent, 0, 0) )
        goto LABEL_548;
      if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 4) )
      {
        str.len = 0;
        str.alloced = 20;
        str.data = str.baseBuffer;
        str.baseBuffer[0] = 0;
        out.len = 0;
        out.alloced = 20;
        out.data = out.baseBuffer;
        out.baseBuffer[0] = 0;
        LOBYTE(v301) = 23;
        idParser::GetStringFromMarker(src, &str, 0);
        v121 = str.len;
        v122 = str.data;
        v123 = idParser::GetFlags(src);
        idLexer::idLexer(&src2, v122, v121, &entityFilter, v123);
        LOBYTE(v301) = 24;
        idLexer::ParseBracedSectionExact(&src2, &out, 1);
        v124 = **(_DWORD **)common.ip;
        v258 = out.data;
        v125 = va("onNamedEvent %s", token.data);
        (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *))(v124 + 136))(
          *(_DWORD *)common.ip,
          this,
          v125,
          v258);
        LOBYTE(v301) = 23;
        idLexer::~idLexer(&src2);
        LOBYTE(v301) = 22;
        idStr::FreeData(&out);
        LOBYTE(v301) = 7;
        idStr::FreeData(&str);
      }
      if ( !this->namedEvents.list )
      {
        v126 = this->namedEvents.granularity;
        if ( v126 > 0 )
        {
          if ( v126 != this->namedEvents.size )
          {
            v13 = v126 < this->namedEvents.num;
            this->namedEvents.size = v126;
            if ( v13 )
              this->namedEvents.num = v126;
            this->namedEvents.list = (rvNamedEvent **)Memory::Allocate(4 * v126);
            for ( i28 = 0; i28 < this->namedEvents.num; ++i28 )
              this->namedEvents.list[i28] = *(rvNamedEvent **)(4 * i28);
          }
        }
        else
        {
          this->namedEvents.list = 0;
          this->namedEvents.num = 0;
          this->namedEvents.size = 0;
        }
      }
      v128 = this->namedEvents.num;
      v129 = this->namedEvents.size;
      if ( v128 == v129 )
      {
        if ( !this->namedEvents.granularity )
          this->namedEvents.granularity = 16;
        v130 = this->namedEvents.granularity
             + v129
             - (this->namedEvents.granularity + v129) % this->namedEvents.granularity;
        if ( v130 > 0 )
        {
          if ( v130 != this->namedEvents.size )
          {
            v131 = this->namedEvents.list;
            this->namedEvents.size = v130;
            if ( v130 < v128 )
              this->namedEvents.num = v130;
            this->namedEvents.list = (rvNamedEvent **)Memory::Allocate(4 * v130);
            for ( i29 = 0; i29 < this->namedEvents.num; ++i29 )
              this->namedEvents.list[i29] = v131[i29];
            if ( v131 )
              Memory::Free(v131);
          }
        }
        else
        {
          if ( this->namedEvents.list )
            Memory::Free(this->namedEvents.list);
          this->namedEvents.list = 0;
          this->namedEvents.num = 0;
          this->namedEvents.size = 0;
        }
      }
      this->namedEvents.list[this->namedEvents.num++] = timeParm;
    }
LABEL_537:
    if ( !idParser::ReadToken(src, &token) )
      break;
    if ( !idStr::Cmp(token.data, "}") )
      goto LABEL_539;
  }
  idParser::Error(src, "Unexpected end of file");
LABEL_548:
  ret = 0;
LABEL_541:
  idWindow::SetupFromState(this);
  this->PostParse(this);
  (*(void (__thiscall **)(_DWORD, idWindow *))(**(_DWORD **)common.ip + 132))(*(_DWORD *)common.ip, this);
  LOBYTE(v301) = 6;
  idStr::FreeData(&work);
  LOBYTE(v301) = 5;
  idStr::FreeData(&token7);
  LOBYTE(v301) = 4;
  idStr::FreeData(&token6);
  LOBYTE(v301) = 3;
  idStr::FreeData(&token5);
  LOBYTE(v301) = 2;
  idStr::FreeData(&token4);
  LOBYTE(v301) = 1;
  idStr::FreeData(&token3);
  LOBYTE(v301) = 0;
  idStr::FreeData(&token2);
  v301 = -1;
  idStr::FreeData(&token);
  return ret;
}

// FUNC: public: void __thiscall idWindow::ParseExpression(class idParser *,int,class idStr &)
void __thiscall idWindow::ParseExpression(idWindow *this, idParser *src, int component, idStr *out)
{
  int v4; // ebp
  idWinFloat var; // [esp+Ch] [ebp-510h] BYREF
  idUserInterfaceLocal ui; // [esp+20h] [ebp-4FCh] BYREF
  idWindow tempwin; // [esp+F8h] [ebp-424h] BYREF
  int v8; // [esp+518h] [ebp-4h]

  var.guiDict = 0;
  var.name = 0;
  var.eval = 1;
  var.__vftable = (idWinFloat_vtbl *)&idWinFloat::`vftable';
  v8 = 0;
  idUserInterfaceLocal::idUserInterfaceLocal(&ui);
  LOBYTE(v8) = 1;
  idWindow::idWindow(&tempwin, &ui);
  LOBYTE(v8) = 2;
  idStr::FreeData(out);
  out->len = 0;
  out->alloced = 20;
  out->data = out->baseBuffer;
  out->baseBuffer[0] = 0;
  idParser::SetMarker(src);
  if ( component - 1 > 0 )
  {
    v4 = component - 1;
    do
    {
      idWindow::ParseExpressionPriority(&tempwin, src, 4, &var, 0);
      idParser::ExpectTokenString(src, ",");
      --v4;
    }
    while ( v4 );
  }
  idWindow::ParseExpressionPriority(&tempwin, src, 4, &var, 0);
  idParser::GetStringFromMarker(src, out, 1);
  LOBYTE(v8) = 1;
  idWindow::~idWindow(&tempwin);
  LOBYTE(v8) = 0;
  idUserInterfaceLocal::~idUserInterfaceLocal(&ui);
  v8 = -1;
  var.__vftable = (idWinFloat_vtbl *)&idWinVar::`vftable';
  Memory::Free(var.name);
}

// FUNC: public: bool __thiscall idWindow::ParseScript(char const *)
char __thiscall idWindow::ParseScript(idWindow *this, const char *text)
{
  idWindow *v2; // esi
  int i; // eax
  const idStr *v4; // eax
  const idStr *v5; // eax
  idStr *v6; // eax
  int v7; // edx
  const idStr *v8; // eax
  const idStr *v9; // eax
  idStr *v10; // eax
  int v11; // edx
  int v12; // esi
  int j; // eax
  int v14; // esi
  int k; // eax
  char *v16; // edx
  int m; // eax
  int n; // esi
  char *v19; // edi
  const char *v20; // eax
  char *v21; // eax
  const idStr *v22; // eax
  const idStr *v23; // eax
  idStr *v24; // eax
  int v25; // edx
  char *data; // [esp-Ch] [ebp-35Ch]
  char *v28; // [esp-Ch] [ebp-35Ch]
  char *v29; // [esp-Ch] [ebp-35Ch]
  const char *v30; // [esp-8h] [ebp-358h]
  int v31; // [esp-4h] [ebp-354h] BYREF
  idStr v32; // [esp+8h] [ebp-348h] BYREF
  idStr v33; // [esp+28h] [ebp-328h] BYREF
  idStr v34; // [esp+48h] [ebp-308h] BYREF
  idStr v35; // [esp+68h] [ebp-2E8h] BYREF
  idStr v36; // [esp+88h] [ebp-2C8h] BYREF
  idStr v37; // [esp+A8h] [ebp-2A8h] BYREF
  idStr v38; // [esp+C8h] [ebp-288h] BYREF
  idStr v39; // [esp+E8h] [ebp-268h] BYREF
  idStr v40; // [esp+108h] [ebp-248h] BYREF
  idToken token3; // [esp+128h] [ebp-228h] BYREF
  idParser src; // [esp+178h] [ebp-1D8h] BYREF
  idToken token2; // [esp+23Ch] [ebp-114h] BYREF
  idWindow *v44; // [esp+28Ch] [ebp-C4h]
  idStr result; // [esp+290h] [ebp-C0h] BYREF
  idToken token; // [esp+2B0h] [ebp-A0h] BYREF
  idStr out; // [esp+300h] [ebp-50h] BYREF
  idStr scriptName; // [esp+320h] [ebp-30h] BYREF
  int *v49; // [esp+340h] [ebp-10h]
  int v50; // [esp+34Ch] [ebp-4h]

  token.floatvalue = 0.0;
  v2 = this;
  v49 = &v31;
  v44 = this;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  token2.floatvalue = 0.0;
  v50 = 5;
  token2.len = 0;
  token2.alloced = 20;
  token2.data = token2.baseBuffer;
  token2.baseBuffer[0] = 0;
  out.len = 0;
  out.alloced = 20;
  out.data = out.baseBuffer;
  out.baseBuffer[0] = 0;
  result.len = 0;
  result.alloced = 20;
  result.data = result.baseBuffer;
  result.baseBuffer[0] = 0;
  scriptName.alloced = 20;
  scriptName.len = 0;
  scriptName.data = scriptName.baseBuffer;
  scriptName.baseBuffer[0] = 0;
  for ( i = 0; text[i]; ++i )
    ;
  idParser::idParser(&src, text, i, &entityFilter, 6156);
  LOBYTE(v50) = 6;
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        if ( !idParser::ReadToken(&src, &token) )
        {
          LOBYTE(v50) = 5;
          idParser::~idParser(&src);
          v50 = 3;
          idStr::FreeData(&scriptName);
          LOBYTE(v50) = 2;
          idStr::FreeData(&result);
          LOBYTE(v50) = 1;
          idStr::FreeData(&out);
          LOBYTE(v50) = 0;
          idStr::FreeData(&token2);
          v50 = -1;
          idStr::FreeData(&token);
          return 1;
        }
        if ( idStr::Icmp(token.data, "definevec4") )
          break;
        if ( !idParser::ReadToken(&src, &token2) )
        {
          idParser::Error(&src, "expected define name");
          goto LABEL_52;
        }
        idWindow::ParseExpression(v2, &src, 4, &out);
        v4 = operator+(&v36, &token, "\t\"");
        LOBYTE(v50) = 7;
        v5 = operator+(&v38, v4, &token2);
        LOBYTE(v50) = 8;
        v6 = operator+(&v34, v5, "\"");
        v7 = **(_DWORD **)common.ip;
        data = v6->data;
        LOBYTE(v50) = 9;
        (*(void (__cdecl **)(idWindow *, char *, char *))(v7 + 140))(v2, data, out.data);
        LOBYTE(v50) = 8;
        idStr::FreeData(&v34);
        LOBYTE(v50) = 7;
        idStr::FreeData(&v38);
        LOBYTE(v50) = 6;
        idStr::FreeData(&v36);
      }
      if ( idStr::Icmp(token.data, "definefloat") && idStr::Icmp(token.data, "float") )
        break;
      if ( !idParser::ReadToken(&src, &token2) )
      {
        v30 = "expected define name";
LABEL_51:
        idParser::Error(&src, v30);
LABEL_52:
        LOBYTE(v50) = 5;
        idParser::~idParser(&src);
        LOBYTE(v50) = 3;
        idStr::FreeData(&scriptName);
        LOBYTE(v50) = 2;
        idStr::FreeData(&result);
        LOBYTE(v50) = 1;
        idStr::FreeData(&out);
        LOBYTE(v50) = 0;
        goto LABEL_55;
      }
      idWindow::ParseExpression(v2, &src, 1, &out);
      v22 = operator+(&v39, &token, "\t\"");
      LOBYTE(v50) = 10;
      v23 = operator+(&v33, v22, &token2);
      LOBYTE(v50) = 11;
      v24 = operator+(&v37, v23, "\"");
      v25 = **(_DWORD **)common.ip;
      v29 = v24->data;
      LOBYTE(v50) = 12;
      (*(void (__cdecl **)(idWindow *, char *, char *))(v25 + 140))(v2, v29, out.data);
      LOBYTE(v50) = 11;
      idStr::FreeData(&v37);
      LOBYTE(v50) = 10;
      idStr::FreeData(&v33);
      LOBYTE(v50) = 6;
      idStr::FreeData(&v39);
    }
    if ( idStr::Icmp(token.data, "defineicon") )
      break;
    token3.floatvalue = 0.0;
    token3.len = 0;
    token3.alloced = 20;
    token3.data = token3.baseBuffer;
    token3.baseBuffer[0] = 0;
    LOBYTE(v50) = 13;
    if ( !idParser::ReadToken(&src, &token2) )
    {
      idParser::Error(&src, "expected icon name");
      LOBYTE(v50) = 6;
      idStr::FreeData(&token3);
      goto LABEL_52;
    }
    if ( !idParser::ReadTokenOnLine(&src, &token3) )
    {
      idParser::Error(&src, "expected icon parms");
      LOBYTE(v50) = 6;
      idStr::FreeData(&token3);
      goto LABEL_52;
    }
    v8 = operator+(&v35, &token, "\t\"");
    LOBYTE(v50) = 14;
    v9 = operator+(&v32, v8, &token2);
    LOBYTE(v50) = 15;
    v10 = operator+(&v40, v9, "\"");
    v11 = **(_DWORD **)common.ip;
    v28 = v10->data;
    LOBYTE(v50) = 16;
    (*(void (__cdecl **)(idWindow *, char *, char *))(v11 + 140))(v2, v28, token3.data);
    LOBYTE(v50) = 15;
    idStr::FreeData(&v40);
    LOBYTE(v50) = 14;
    idStr::FreeData(&v32);
    LOBYTE(v50) = 13;
    idStr::FreeData(&v35);
    LOBYTE(v50) = 6;
    idStr::FreeData(&token3);
LABEL_18:
    if ( !idParser::ParseBracedSectionExact(&src, &out, 1) )
      goto LABEL_52;
    v2 = v44;
    (*(void (__thiscall **)(_DWORD, idWindow *, char *, char *))(**(_DWORD **)common.ip + 136))(
      *(_DWORD *)common.ip,
      v44,
      scriptName.data,
      out.data);
  }
  if ( !idStr::Icmp(token.data, "ontime") )
  {
    if ( !idParser::ReadToken(&src, &token) )
      goto LABEL_22;
    idStr::operator=(&scriptName, "onTime ");
    if ( !idStr::Icmp(token.data, "+") )
    {
      v12 = scriptName.len + token.len;
      if ( scriptName.len + token.len + 1 > scriptName.alloced )
        idStr::ReAllocate(&scriptName, scriptName.len + token.len + 1, 1);
      for ( j = 0; j < token.len; ++j )
        scriptName.data[j + scriptName.len] = token.data[j];
      scriptName.len = v12;
      scriptName.data[v12] = 0;
      if ( !idParser::ReadToken(&src, &token) )
      {
LABEL_22:
        v30 = "expected time";
        goto LABEL_51;
      }
    }
    v14 = scriptName.len + token.len;
    if ( scriptName.len + token.len + 1 > scriptName.alloced )
      idStr::ReAllocate(&scriptName, scriptName.len + token.len + 1, 1);
    for ( k = 0; ; ++k )
    {
      v16 = scriptName.data;
      if ( k >= token.len )
        break;
      scriptName.data[k + scriptName.len] = token.data[k];
    }
    goto LABEL_35;
  }
  if ( !idStr::Icmp(token.data, "onNamedevent") )
  {
    if ( !idParser::ReadToken(&src, &token) )
      goto LABEL_22;
    idStr::operator=(&scriptName, "onNamedEvent ");
    v14 = scriptName.len + token.len;
    if ( scriptName.len + token.len + 1 > scriptName.alloced )
      idStr::ReAllocate(&scriptName, scriptName.len + token.len + 1, 1);
    for ( m = 0; ; ++m )
    {
      v16 = scriptName.data;
      if ( m >= token.len )
        break;
      scriptName.data[m + scriptName.len] = token.data[m];
    }
LABEL_35:
    scriptName.len = v14;
    v16[v14] = 0;
    goto LABEL_18;
  }
  for ( n = 0; n < 28; ++n )
  {
    v19 = token.data;
    v20 = windowEdit->GetScriptName(windowEdit, n);
    if ( !idStr::Icmp(v20, v19) )
    {
      v21 = (char *)windowEdit->GetScriptName(windowEdit, n);
      idStr::operator=(&scriptName, v21);
      goto LABEL_18;
    }
  }
  idParser::Error(&src, "expected script name");
  LOBYTE(v50) = 5;
  idParser::~idParser(&src);
  LOBYTE(v50) = 3;
  idStr::FreeData(&scriptName);
  LOBYTE(v50) = 2;
  idStr::FreeData(&result);
  LOBYTE(v50) = 1;
  idStr::FreeData(&out);
  LOBYTE(v50) = 0;
LABEL_55:
  idStr::FreeData(&token2);
  v50 = -1;
  idStr::FreeData(&token);
  return 0;
}

// FUNC: private: virtual bool __thiscall rvWindowEditLocal::ParseScript(class idWindow *,char const *)
char __thiscall rvWindowEditLocal::ParseScript(rvWindowEditLocal *this, idWindow *edit, const char *text)
{
  return idWindow::ParseScript(edit, text);
}
