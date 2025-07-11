
// FUNC: public: void __thiscall idSimpleWindow::StateChanged(bool)
void __thiscall idSimpleWindow::StateChanged(idSimpleWindow *this, bool redraw)
{
  idMaterial *background; // ecx

  if ( redraw )
  {
    background = (idMaterial *)this->background;
    if ( background )
    {
      if ( idMaterial::CinematicLength(background) )
        idMaterial::UpdateCinematic((idMaterial *)this->background, this->gui->time);
    }
  }
}

// FUNC: public: void __thiscall idSimpleWindow::ResetCinematics(void)
void __thiscall idSimpleWindow::ResetCinematics(idSimpleWindow *this)
{
  idMaterial *background; // ecx

  background = (idMaterial *)this->background;
  if ( background )
    idMaterial::ResetCinematicTime(background, this->gui->time);
}

// FUNC: protected: void __thiscall idSimpleWindow::DrawBackground(class idRectangle const &)
void __thiscall idSimpleWindow::DrawBackground(idSimpleWindow *this, const idRectangle *drawRect)
{
  idMaterial *background; // ecx
  float scalex; // [esp+8h] [ebp-4h]
  float drawRecta; // [esp+10h] [ebp+4h]

  if ( this->backColor.data.w > 0.0 )
    idDeviceContext::DrawFilledRect(
      this->dc,
      drawRect->x,
      LODWORD(drawRect->y),
      drawRect->w,
      drawRect->h,
      &this->backColor.data);
  background = (idMaterial *)this->background;
  if ( background && this->matColor.data.w > 0.0 )
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

// FUNC: protected: void __thiscall idSimpleWindow::CalcClientRect(float,float)
void __thiscall idSimpleWindow::CalcClientRect(idSimpleWindow *this, float xofs, float yofs)
{
  bool v4; // zf
  idRectangle *p_data; // eax
  float x; // edx
  idRectangle *p_drawRect; // edi
  idRectangle *v8; // ecx
  float w; // edx
  float h; // eax
  idRectangle *p_clientRect; // ecx
  double v12; // st7
  float v13; // ecx
  float v14; // [esp+8h] [ebp-4h]
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
    v14 = this->rect.data.w;
    p_drawRect->x = ((double (__thiscall *)(idWinRectangle *))this->rect.x)(&this->rect) - v14;
    this->drawRect.y = this->rect.data.y - this->rect.data.h;
  }
  p_clientRect = &this->clientRect;
  p_drawRect->x = xofs + p_drawRect->x;
  this->drawRect.y = yofs + this->drawRect.y;
  v12 = this->rect.data.h;
  this->clientRect.x = p_drawRect->x;
  this->clientRect.y = p_drawRect->y;
  this->clientRect.w = p_drawRect->w;
  this->clientRect.h = p_drawRect->h;
  if ( v12 > 0.0 && this->rect.data.w > 0.0 )
  {
    if ( (this->flags & 4) != 0 && 0.0 != this->borderSize )
    {
      p_clientRect->x = this->borderSize + p_clientRect->x;
      this->clientRect.y = this->borderSize + this->clientRect.y;
      this->clientRect.w = this->clientRect.w - this->borderSize;
      this->clientRect.h = this->clientRect.h - this->borderSize;
    }
    this->textRect.x = p_clientRect->x;
    this->textRect.y = this->clientRect.y;
    v13 = this->clientRect.h;
    this->textRect.w = this->clientRect.w;
    this->textRect.h = v13;
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

// FUNC: public: int __thiscall idSimpleWindow::GetWinVarOffset(class idWinVar *,struct drawWin_t *)
int __thiscall idSimpleWindow::GetWinVarOffset(idSimpleWindow *this, idWinVar *wv, drawWin_t *owner)
{
  int result; // eax

  result = -1;
  if ( wv == &this->rect )
    result = 208;
  if ( wv == &this->backColor )
    result = 240;
  if ( wv == &this->matColor )
    result = 272;
  if ( wv == &this->foreColor )
    result = 304;
  if ( wv == &this->borderColor )
    result = 336;
  if ( wv == &this->textScale )
    result = 368;
  if ( wv == &this->rotate )
  {
    result = 388;
    owner->simp = this;
  }
  else if ( result != -1 )
  {
    owner->simp = this;
  }
  return result;
}

// FUNC: public: virtual void __thiscall idSimpleWindow::WriteToSaveGame(class idFile *)
void __thiscall idSimpleWindow::WriteToSaveGame(idSimpleWindow *this, idFile *savefile)
{
  idFile *v2; // esi
  const idMaterial *background; // eax
  int v5; // ebx
  const char *v6; // eax
  idWinVar *v7; // ecx

  v2 = savefile;
  savefile->Write(savefile, &this->flags, 4);
  v2->Write(v2, &this->drawRect, 16);
  v2->Write(v2, &this->clientRect, 16);
  v2->Write(v2, &this->textRect, 16);
  v2->Write(v2, &this->origin, 8);
  v2->Write(v2, &this->matScalex, 4);
  v2->Write(v2, &this->matScaley, 4);
  v2->Write(v2, &this->borderSize, 4);
  v2->Write(v2, &this->textAlign, 4);
  v2->Write(v2, &this->textAlignx, 4);
  v2->Write(v2, &this->textAligny, 4);
  v2->Write(v2, &this->textSpacing, 4);
  v2->Write(v2, &this->textStyle, 1);
  this->text.WriteToSaveGame(&this->text, v2);
  this->visible.WriteToSaveGame(&this->visible, v2);
  this->rect.WriteToSaveGame(&this->rect, v2);
  this->backColor.WriteToSaveGame(&this->backColor, v2);
  this->matColor.WriteToSaveGame(&this->matColor, v2);
  this->foreColor.WriteToSaveGame(&this->foreColor, v2);
  this->borderColor.WriteToSaveGame(&this->borderColor, v2);
  this->textScale.WriteToSaveGame(&this->textScale, v2);
  this->rotate.WriteToSaveGame(&this->rotate, v2);
  this->shear.WriteToSaveGame(&this->shear, v2);
  this->backGroundName.WriteToSaveGame(&this->backGroundName, v2);
  background = this->background;
  v5 = 0;
  if ( background )
  {
    savefile = (idFile *)strlen(background->base->GetName(background->base));
    v2->Write(v2, &savefile, 4);
    v6 = this->background->base->GetName(this->background->base);
    v2->Write(v2, v6, (int)savefile);
  }
  else
  {
    savefile = 0;
    v2->Write(v2, &savefile, 4);
  }
  if ( this->definedVars.num > 0 )
  {
    do
    {
      v7 = this->definedVars.list[v5];
      v7->WriteToSaveGame(v7, v2);
      ++v5;
    }
    while ( v5 < this->definedVars.num );
  }
}

// FUNC: public: virtual void __thiscall idSimpleWindow::ReadFromSaveGame(class idFile *)
void __thiscall idSimpleWindow::ReadFromSaveGame(idSimpleWindow *this, idFile *savefile)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  idFile *v3; // esi
  idFile *v5; // edi
  const idMaterial *v6; // eax
  int i; // edi
  idWinVar *v8; // ecx
  idStr backName; // [esp+ACh] [ebp-2Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v10; // [esp+CCh] [ebp-Ch]
  void *v11; // [esp+D0h] [ebp-8h]
  int v12; // [esp+D4h] [ebp-4h]

  v12 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v11 = &_ehhandler__GetWinVarByName_idSimpleWindow__QAEPAVidWinVar__PBD_Z;
  v10 = ExceptionList;
  v3 = savefile;
  savefile->Read(savefile, &this->flags, 4);
  v3->Read(v3, &this->drawRect, 16);
  v3->Read(v3, &this->clientRect, 16);
  v3->Read(v3, &this->textRect, 16);
  v3->Read(v3, &this->origin, 8);
  v3->Read(v3, &this->matScalex, 4);
  v3->Read(v3, &this->matScaley, 4);
  v3->Read(v3, &this->borderSize, 4);
  v3->Read(v3, &this->textAlign, 4);
  v3->Read(v3, &this->textAlignx, 4);
  v3->Read(v3, &this->textAligny, 4);
  v3->Read(v3, &this->textSpacing, 4);
  v3->Read(v3, &this->textStyle, 1);
  this->text.ReadFromSaveGame(&this->text, v3);
  this->visible.ReadFromSaveGame(&this->visible, v3);
  this->rect.ReadFromSaveGame(&this->rect, v3);
  this->backColor.ReadFromSaveGame(&this->backColor, v3);
  this->matColor.ReadFromSaveGame(&this->matColor, v3);
  this->foreColor.ReadFromSaveGame(&this->foreColor, v3);
  this->borderColor.ReadFromSaveGame(&this->borderColor, v3);
  this->textScale.ReadFromSaveGame(&this->textScale, v3);
  this->rotate.ReadFromSaveGame(&this->rotate, v3);
  this->shear.ReadFromSaveGame(&this->shear, v3);
  this->backGroundName.ReadFromSaveGame(&this->backGroundName, v3);
  v3->Read(v3, &savefile, 4);
  if ( (int)savefile <= 0 )
  {
    this->background = 0;
  }
  else
  {
    backName.len = 0;
    backName.alloced = 20;
    backName.data = backName.baseBuffer;
    backName.baseBuffer[0] = 0;
    v5 = savefile;
    v12 = 0;
    if ( (int)&savefile->__vftable + 1 > 20 )
      idStr::ReAllocate(&backName, (int)&savefile->__vftable + 1, 1);
    backName.len = (int)v5;
    memset(backName.data, 0x20u, (unsigned int)v5);
    backName.data[backName.len] = 0;
    v3->Read(v3, backName.data, (int)savefile);
    v6 = declManager->FindMaterial(declManager, backName.data, 1);
    this->background = v6;
    v6->sort = -2.0;
    v12 = -1;
    idStr::FreeData(&backName);
  }
  for ( i = 0; i < this->definedVars.num; ++i )
  {
    v8 = this->definedVars.list[i];
    v8->ReadFromSaveGame(v8, v3);
  }
}

// FUNC: public: __thiscall idSimpleWindow::idSimpleWindow(class idWindow *)
void __thiscall idSimpleWindow::idSimpleWindow(idSimpleWindow *this, idWindow *win)
{
  idStr *p_name; // edi
  char *baseBuffer; // ecx
  const idMaterial *v6; // ecx
  idWindow *parent; // ebx
  int wina; // [esp+28h] [ebp+4h]

  p_name = &this->name;
  this->__vftable = (idSimpleWindow_vtbl *)&idSimpleWindow::`vftable';
  baseBuffer = this->name.baseBuffer;
  p_name->len = 0;
  p_name->alloced = 20;
  p_name->data = baseBuffer;
  *baseBuffer = 0;
  this->drawRect.h = 0.0;
  this->drawRect.w = 0.0;
  this->drawRect.y = 0.0;
  this->drawRect.x = 0.0;
  this->clientRect.h = 0.0;
  this->clientRect.w = 0.0;
  this->clientRect.y = 0.0;
  this->clientRect.x = 0.0;
  this->textRect.h = 0.0;
  this->textRect.w = 0.0;
  this->textRect.y = 0.0;
  this->textRect.x = 0.0;
  this->text.guiDict = 0;
  this->text.name = 0;
  this->text.eval = 1;
  this->text.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->text.data.len = 0;
  this->text.data.alloced = 20;
  this->text.data.data = this->text.data.baseBuffer;
  this->text.data.baseBuffer[0] = 0;
  this->visible.guiDict = 0;
  this->visible.name = 0;
  this->visible.eval = 1;
  this->visible.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
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
  this->shear.guiDict = 0;
  this->shear.name = 0;
  this->shear.eval = 1;
  this->shear.__vftable = (idWinVec2_vtbl *)&idWinVec2::`vftable';
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
  this->hideCursor.guiDict = 0;
  this->hideCursor.name = 0;
  this->hideCursor.eval = 1;
  this->hideCursor.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->definedVars.granularity = 16;
  this->definedVars.list = 0;
  this->definedVars.num = 0;
  this->definedVars.size = 0;
  this->gui = win->gui;
  this->dc = win->dc;
  this->drawRect = win->drawRect;
  this->clientRect = win->clientRect;
  this->textRect = win->textRect;
  this->origin = win->origin;
  this->fontNum = win->fontNum;
  wina = win->name.len;
  if ( wina + 1 > p_name->alloced )
    idStr::ReAllocate(p_name, wina + 1, 0);
  qmemcpy(p_name->data, win->name.data, wina);
  this->name.data[wina] = 0;
  this->name.len = wina;
  this->matScalex = win->matScalex;
  this->matScaley = win->matScaley;
  this->borderSize = win->borderSize;
  this->textAlign = win->textAlign;
  this->textAlignx = win->textAlignx;
  this->textAligny = win->textAligny;
  this->background = win->background;
  this->flags = win->flags;
  this->textSpacing = (int)win->textSpacing;
  this->textStyle = win->textStyle;
  this->visible.guiDict = win->visible.guiDict;
  idWinVar::SetName(&this->visible, win->visible.name);
  this->visible.data = win->visible.data;
  idWinStr::operator=(&this->text, (int)&win->text);
  this->rect.guiDict = win->rect.guiDict;
  idWinVar::SetName(&this->rect, win->rect.name);
  this->rect.data.x = win->rect.data.x;
  this->rect.data.y = win->rect.data.y;
  this->rect.data.w = win->rect.data.w;
  this->rect.data.h = win->rect.data.h;
  this->backColor.guiDict = win->backColor.guiDict;
  idWinVar::SetName(&this->backColor, win->backColor.name);
  this->backColor.data.x = win->backColor.data.x;
  this->backColor.data.y = win->backColor.data.y;
  this->backColor.data.z = win->backColor.data.z;
  this->backColor.data.w = win->backColor.data.w;
  this->matColor.guiDict = win->matColor.guiDict;
  idWinVar::SetName(&this->matColor, win->matColor.name);
  this->matColor.data.x = win->matColor.data.x;
  this->matColor.data.y = win->matColor.data.y;
  this->matColor.data.z = win->matColor.data.z;
  this->matColor.data.w = win->matColor.data.w;
  this->foreColor.guiDict = win->foreColor.guiDict;
  idWinVar::SetName(&this->foreColor, win->foreColor.name);
  this->foreColor.data.x = win->foreColor.data.x;
  this->foreColor.data.y = win->foreColor.data.y;
  this->foreColor.data.z = win->foreColor.data.z;
  this->foreColor.data.w = win->foreColor.data.w;
  this->borderColor.guiDict = win->borderColor.guiDict;
  idWinVar::SetName(&this->borderColor, win->borderColor.name);
  this->borderColor.data.x = win->borderColor.data.x;
  this->borderColor.data.y = win->borderColor.data.y;
  this->borderColor.data.z = win->borderColor.data.z;
  this->borderColor.data.w = win->borderColor.data.w;
  this->textScale.guiDict = win->textScale.guiDict;
  idWinVar::SetName(&this->textScale, win->textScale.name);
  this->textScale.data = win->textScale.data;
  this->rotate.guiDict = win->rotate.guiDict;
  idWinVar::SetName(&this->rotate, win->rotate.name);
  this->rotate.data = win->rotate.data;
  idWinVec2::operator=(&this->shear, &win->shear);
  idWinBackground::operator=(&this->backGroundName, (int)&win->backGroundName);
  if ( idWinBackground::Length(&this->backGroundName) )
  {
    v6 = declManager->FindMaterial(declManager, this->backGroundName.data.data, 1);
    this->background = v6;
    if ( v6->sort < 100.0 )
      v6->sort = -2.0;
    idMaterial::SetImageClassifications((idMaterial *)this->background, 1);
  }
  this->backGroundName.mat = &this->background;
  this->mParent = win->parent;
  this->hideCursor.guiDict = win->hideCursor.guiDict;
  idWinVar::SetName(&this->hideCursor, win->hideCursor.name);
  this->hideCursor.data = win->hideCursor.data;
  parent = win->parent;
  if ( parent )
  {
    if ( this->text.guiDict )
      idWindow::AddUpdateVar(parent, &this->text);
    if ( this->visible.guiDict )
      idWindow::AddUpdateVar(parent, &this->visible);
    if ( this->rect.guiDict )
      idWindow::AddUpdateVar(parent, &this->rect);
    if ( this->backColor.guiDict )
      idWindow::AddUpdateVar(parent, &this->backColor);
    if ( this->matColor.guiDict )
      idWindow::AddUpdateVar(parent, &this->matColor);
    if ( this->foreColor.guiDict )
      idWindow::AddUpdateVar(parent, &this->foreColor);
    if ( this->borderColor.guiDict )
      idWindow::AddUpdateVar(parent, &this->borderColor);
    if ( this->textScale.guiDict )
      idWindow::AddUpdateVar(parent, &this->textScale);
    if ( this->rotate.guiDict )
      idWindow::AddUpdateVar(parent, &this->rotate);
    if ( this->shear.guiDict )
      idWindow::AddUpdateVar(parent, &this->shear);
    if ( this->backGroundName.guiDict )
      idWindow::AddUpdateVar(parent, &this->backGroundName);
  }
}

// FUNC: public: virtual __thiscall idSimpleWindow::~idSimpleWindow(void)
void __thiscall idSimpleWindow::~idSimpleWindow(idSimpleWindow *this)
{
  int i; // edi
  idWinVar *v3; // ecx
  char *v4; // [esp-24h] [ebp-40h]
  char *v5; // [esp-20h] [ebp-3Ch]
  char *v6; // [esp-1Ch] [ebp-38h]
  char *v7; // [esp-18h] [ebp-34h]
  char *v8; // [esp-14h] [ebp-30h]
  char *v9; // [esp-10h] [ebp-2Ch]
  char *v10; // [esp-Ch] [ebp-28h]
  char *v11; // [esp-8h] [ebp-24h]
  char *name; // [esp-4h] [ebp-20h]
  char *v13; // [esp-4h] [ebp-20h]

  this->__vftable = (idSimpleWindow_vtbl *)&idSimpleWindow::`vftable';
  for ( i = 0; i < this->definedVars.num; ++i )
  {
    v3 = this->definedVars.list[i];
    if ( v3 )
      ((void (__thiscall *)(idWinVar *, int))v3->~idWinVar)(v3, 1);
    this->definedVars.list[i] = 0;
  }
  if ( this->definedVars.list )
    Memory::Free(this->definedVars.list);
  this->definedVars.list = 0;
  this->definedVars.num = 0;
  this->definedVars.size = 0;
  this->definedVars.list = 0;
  this->definedVars.num = 0;
  this->definedVars.size = 0;
  name = this->hideCursor.name;
  this->hideCursor.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(name);
  this->hideCursor.name = 0;
  idWinBackground::~idWinBackground(&this->backGroundName);
  v13 = this->shear.name;
  this->shear.__vftable = (idWinVec2_vtbl *)&idWinVar::`vftable';
  Memory::Free(v13);
  this->shear.name = 0;
  v11 = this->rotate.name;
  this->rotate.__vftable = (idWinFloat_vtbl *)&idWinVar::`vftable';
  Memory::Free(v11);
  this->rotate.name = 0;
  v10 = this->textScale.name;
  this->textScale.__vftable = (idWinFloat_vtbl *)&idWinVar::`vftable';
  Memory::Free(v10);
  this->textScale.name = 0;
  v9 = this->borderColor.name;
  this->borderColor.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v9);
  this->borderColor.name = 0;
  v8 = this->foreColor.name;
  this->foreColor.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v8);
  this->foreColor.name = 0;
  v7 = this->matColor.name;
  this->matColor.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v7);
  this->matColor.name = 0;
  v6 = this->backColor.name;
  this->backColor.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v6);
  this->backColor.name = 0;
  v5 = this->rect.name;
  this->rect.__vftable = (idWinRectangle_vtbl *)&idWinVar::`vftable';
  Memory::Free(v5);
  this->rect.name = 0;
  v4 = this->visible.name;
  this->visible.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(v4);
  this->visible.name = 0;
  idWinStr::~idWinStr(&this->text);
  idStr::FreeData(&this->name);
}

// FUNC: protected: void __thiscall idSimpleWindow::SetupTransforms(float,float)
void __thiscall idSimpleWindow::SetupTransforms(idSimpleWindow *this, float x, float y)
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

  v4 = _S5_42;
  if ( (_S5_42 & 1) == 0 )
  {
    v4 = _S5_42 | 1;
    _S5_42 |= 1u;
  }
  if ( (v4 & 2) == 0 )
  {
    v4 |= 2u;
    _S5_42 = v4;
  }
  trans = mat3_identity;
  v5 = y + this->origin.y;
  v6 = x + this->origin.x;
  org.z = 0.0;
  org.x = v6;
  org.y = v5;
  if ( this->rotate.data != 0.0 )
  {
    if ( (v4 & 4) == 0 )
    {
      v4 |= 4u;
      _S5_42 = v4;
    }
    if ( (v4 & 8) == 0 )
    {
      _S5_42 = v4 | 8;
      vec.x = 0.0;
      vec.y = 0.0;
      vec.z = 1.0;
    }
    v7 = v5;
    data = this->rotate.data;
    rot.origin.y = v7;
    rot.origin.x = org.x;
    rot.angle = data;
    rot.vec = vec;
    rot.origin.z = 0.0;
    rot.axisValid = 0;
    trans = *idRotation::ToMat3(&rot);
    v4 = _S5_42;
  }
  if ( (v4 & 0x10) == 0 )
    _S5_42 = v4 | 0x10;
  smat = mat3_identity;
  if ( 0.0 != ((double (__thiscall *)(idWinVec2 *))this->shear.x)(&this->shear) || this->shear.data.y != 0.0 )
  {
    smat.mat[0].y = this->shear.x(&this->shear);
    smat.mat[1].x = this->shear.data.y;
    p_z = &trans.mat[0].z;
    v10 = 3;
    do
    {
      p_z += 3;
      --v10;
      v13 = smat.mat[1].z * *(p_z - 4) + smat.mat[2].z * *(p_z - 3) + smat.mat[0].z * *(p_z - 5);
      v11 = smat.mat[2].x * *(p_z - 3) + smat.mat[0].x * *(p_z - 5) + smat.mat[1].x * *(p_z - 4);
      v12 = smat.mat[1].y * *(p_z - 4) + smat.mat[2].y * *(p_z - 3) + smat.mat[0].y * *(p_z - 5);
      *(p_z - 3) = v13;
      *(p_z - 5) = v11;
      *(p_z - 4) = v12;
    }
    while ( v10 );
  }
  ya = trans.mat[0].x - mat3_identity.mat[0].x;
  if ( COERCE_FLOAT(LODWORD(ya) & 0x7FFFFFFF) > 0.000001 )
    goto LABEL_26;
  yb = trans.mat[0].y - mat3_identity.mat[0].y;
  if ( COERCE_FLOAT(LODWORD(yb) & 0x7FFFFFFF) > 0.000001
    || (yc = trans.mat[0].z - mat3_identity.mat[0].z, COERCE_FLOAT(LODWORD(yc) & 0x7FFFFFFF) > 0.000001)
    || (yd = trans.mat[1].x - mat3_identity.mat[1].x, COERCE_FLOAT(LODWORD(yd) & 0x7FFFFFFF) > 0.000001)
    || (ye = trans.mat[1].y - mat3_identity.mat[1].y, COERCE_FLOAT(LODWORD(ye) & 0x7FFFFFFF) > 0.000001)
    || (yf = trans.mat[1].z - mat3_identity.mat[1].z, COERCE_FLOAT(LODWORD(yf) & 0x7FFFFFFF) > 0.000001)
    || (yg = trans.mat[2].x - mat3_identity.mat[2].x, COERCE_FLOAT(LODWORD(yg) & 0x7FFFFFFF) > 0.000001)
    || (yh = trans.mat[2].y - mat3_identity.mat[2].y, COERCE_FLOAT(LODWORD(yh) & 0x7FFFFFFF) > 0.000001)
    || (yi = trans.mat[2].z - mat3_identity.mat[2].z, COERCE_FLOAT(LODWORD(yi) & 0x7FFFFFFF) > 0.000001) )
  {
LABEL_26:
    idDeviceContext::SetTransformInfo(this->dc, &org, &trans);
  }
}

// FUNC: public: void __thiscall idSimpleWindow::Redraw(float,float)
void __thiscall idSimpleWindow::Redraw(idSimpleWindow *this, float x, float y)
{
  idRectangle *p_drawRect; // edi
  idRectangle *p_textRect; // ebx
  idRectangle v6; // [esp-2Ch] [ebp-68h]
  idVec3 oldOrg; // [esp+Ch] [ebp-30h] BYREF
  idMat3 oldTrans; // [esp+18h] [ebp-24h] BYREF

  if ( this->visible.data )
  {
    idDeviceContext::SetSize(this->dc, 640.0, 480.0);
    idDeviceContext::GetTransformInfo(this->dc, &oldOrg, &oldTrans);
    idSimpleWindow::CalcClientRect(this, 0.0, 0.0);
    idDeviceContext::SetFont(this->dc, this->fontNum);
    p_drawRect = &this->drawRect;
    this->drawRect.x = x + this->drawRect.x;
    p_textRect = &this->textRect;
    this->drawRect.y = y + this->drawRect.y;
    this->clientRect.x = x + this->clientRect.x;
    this->clientRect.y = y + this->clientRect.y;
    this->textRect.x = x + this->textRect.x;
    this->textRect.y = y + this->textRect.y;
    idSimpleWindow::SetupTransforms(this, x, y);
    if ( (this->flags & 0x10000) != 0 )
      this->dc->enableClipping = 0;
    idSimpleWindow::DrawBackground(this, &this->drawRect);
    if ( (this->flags & 4) != 0 && this->borderSize != 0.0 )
      idDeviceContext::DrawRect(
        this->dc,
        p_drawRect->x,
        LODWORD(this->drawRect.y),
        this->drawRect.w,
        this->drawRect.h,
        this->borderSize,
        &this->borderColor.data);
    v6.x = p_textRect->x;
    v6.y = this->textRect.y;
    *(_QWORD *)&v6.w = *(_QWORD *)&this->textRect.w;
    idDeviceContext::DrawTextA(
      this->dc,
      this->text.data.data,
      this->textScale.data,
      this->textAlign,
      this->textStyle,
      this->foreColor.data,
      v6,
      (this->flags & 0x8000) == 0,
      -1,
      0,
      0,
      0,
      this->textSpacing,
      0);
    idDeviceContext::SetTransformInfo(this->dc, &oldOrg, &oldTrans);
    if ( (this->flags & 0x10000) != 0 )
      this->dc->enableClipping = 1;
    p_drawRect->x = p_drawRect->x - x;
    this->drawRect.y = this->drawRect.y - y;
    this->clientRect.x = this->clientRect.x - x;
    this->clientRect.y = this->clientRect.y - y;
    p_textRect->x = p_textRect->x - x;
    this->textRect.y = this->textRect.y - y;
  }
}

// FUNC: public: class idWinVar * __thiscall idSimpleWindow::GetWinVarByName(char const *)
idWinVar *__thiscall idSimpleWindow::GetWinVarByName(idSimpleWindow *this, char *_name)
{
  void *p_backGroundName; // edi
  int num; // ebx
  int v6; // edi
  idWinVar *v7; // ecx
  const char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  int v11; // eax
  int v12; // edi
  idWinVar *v13; // ebx
  char *v14; // edi
  idWinVar *WinVarByName; // ebp
  idWinVar *v16; // eax
  int granularity; // eax
  bool v18; // cc
  int i; // eax
  int v20; // ebp
  int size; // eax
  int v22; // ecx
  idWinVar **list; // edi
  int j; // eax
  idStr temp; // [esp+Ch] [ebp-2Ch] BYREF
  int v26; // [esp+34h] [ebp-4h]

  p_backGroundName = 0;
  if ( !idStr::Icmp(_name, "background") )
    p_backGroundName = &this->backGroundName;
  if ( !idStr::Icmp(_name, "visible") )
    p_backGroundName = &this->visible;
  if ( !idStr::Icmp(_name, "rect") )
    p_backGroundName = &this->rect;
  if ( !idStr::Icmp(_name, "backColor") )
    p_backGroundName = &this->backColor;
  if ( !idStr::Icmp(_name, "matColor") )
    p_backGroundName = &this->matColor;
  if ( !idStr::Icmp(_name, "foreColor") )
    p_backGroundName = &this->foreColor;
  if ( !idStr::Icmp(_name, "borderColor") )
    p_backGroundName = &this->borderColor;
  if ( !idStr::Icmp(_name, "textScale") )
    p_backGroundName = &this->textScale;
  if ( !idStr::Icmp(_name, "rotate") )
    p_backGroundName = &this->rotate;
  if ( !idStr::Icmp(_name, "shear") )
    p_backGroundName = &this->shear;
  if ( !idStr::Icmp(_name, "text") )
    p_backGroundName = &this->text;
  if ( p_backGroundName )
    return (idWinVar *)p_backGroundName;
  num = this->definedVars.num;
  v6 = 0;
  if ( num > 0 )
  {
    while ( 1 )
    {
      v7 = this->definedVars.list[v6];
      name = v7->name;
      if ( !name )
        goto LABEL_31;
      guiDict = v7->guiDict;
      if ( guiDict )
      {
        if ( *name == 42 )
          break;
      }
LABEL_32:
      if ( !idStr::Icmp(_name, name) )
        return this->definedVars.list[v6];
      if ( ++v6 >= num )
        goto LABEL_34;
    }
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_32;
    }
LABEL_31:
    name = &entityFilter;
    goto LABEL_32;
  }
LABEL_34:
  strrchr((unsigned __int8 *)_name, 0x5Fu);
  v12 = v11;
  v13 = 0;
  if ( !v11 || !*(_BYTE *)(v11 + 1) || *(_BYTE *)(v11 + 2) )
    return 0;
  temp.len = 0;
  temp.alloced = 20;
  temp.data = temp.baseBuffer;
  temp.baseBuffer[0] = 0;
  v26 = 0;
  idStr::operator=(&temp, _name);
  *(_BYTE *)(temp.data - _name + v12) = 0;
  v14 = strchr("xyzw", *(char *)(v12 + 1));
  if ( !v14
    || (WinVarByName = idSimpleWindow::GetWinVarByName(this, temp.data),
        !__RTDynamicCast(WinVarByName, 0, &idWinVar `RTTI Type Descriptor', &idWinVec4 `RTTI Type Descriptor', 0))
    && !__RTDynamicCast(WinVarByName, 0, &idWinVar `RTTI Type Descriptor', &idWinRectangle `RTTI Type Descriptor', 0) )
  {
    v26 = -1;
    idStr::FreeData(&temp);
    return 0;
  }
  v16 = (idWinVar *)Memory::Allocate(0x18u);
  if ( v16 )
  {
    v16->guiDict = 0;
    v16->name = 0;
    v16->eval = 1;
    v16->__vftable = (idWinVar_vtbl *)&idWinFloatMember::`vftable';
    v16[1].__vftable = (idWinVar_vtbl *)WinVarByName;
    v16[1].guiDict = (idDict *)(v14 - "xyzw");
    v13 = v16;
  }
  idWinVar::SetName(v13, _name);
  if ( !this->definedVars.list )
  {
    granularity = this->definedVars.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->definedVars.size )
      {
        v18 = granularity < this->definedVars.num;
        this->definedVars.size = granularity;
        if ( v18 )
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
  v20 = this->definedVars.num;
  size = this->definedVars.size;
  if ( v20 == size )
  {
    if ( !this->definedVars.granularity )
      this->definedVars.granularity = 16;
    v22 = size + this->definedVars.granularity - (size + this->definedVars.granularity) % this->definedVars.granularity;
    if ( v22 > 0 )
    {
      if ( v22 != this->definedVars.size )
      {
        list = this->definedVars.list;
        this->definedVars.size = v22;
        if ( v22 < v20 )
          this->definedVars.num = v22;
        this->definedVars.list = (idWinVar **)Memory::Allocate(4 * v22);
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
  this->definedVars.list[this->definedVars.num++] = v13;
  v26 = -1;
  idStr::FreeData(&temp);
  return v13;
}

// FUNC: public: unsigned int __thiscall idSimpleWindow::Size(void)
unsigned int __thiscall idSimpleWindow::Size(idSimpleWindow *this)
{
  int alloced; // edi
  unsigned int v3; // edi

  if ( this->name.data == this->name.baseBuffer )
    alloced = 0;
  else
    alloced = this->name.alloced;
  v3 = this->text.Size(&this->text) + alloced + 592;
  return v3 + this->backGroundName.Size(&this->backGroundName);
}
