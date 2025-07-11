
// FUNC: public: virtual bool __thiscall idListWindow::RouteJoystickChange(int,int)
char __thiscall idListWindow::RouteJoystickChange(idListWindow *this, int xd, int yd)
{
  idListWindow_vtbl *v3; // eax
  bool updateVisuals; // [esp+3h] [ebp-15h] BYREF
  sysEvent_s event; // [esp+4h] [ebp-14h] BYREF

  updateVisuals = 0;
  if ( yd < 0 )
  {
    event.evValue = 133;
LABEL_5:
    v3 = this->__vftable;
    event.evType = SE_KEY;
    event.evValue2 = 1;
    v3->HandleEvent(this, &event, &updateVisuals);
    return 1;
  }
  if ( yd > 0 )
  {
    event.evValue = 134;
    goto LABEL_5;
  }
  return 0;
}

// FUNC: public: virtual class idWinVar * __thiscall idListWindow::GetWinVarByName(char const *,bool,struct drawWin_t * *)
idWinStr *__thiscall idListWindow::GetWinVarByName(
        idListWindow *this,
        const char *_name,
        bool fixup,
        drawWin_t **owner)
{
  if ( !idStr::Icmp(_name, "itemHeight") )
    return (idWinStr *)&this->itemHeight;
  if ( !idStr::Icmp(_name, "backgroundFocus") )
    return &this->backgroundFocus;
  if ( !idStr::Icmp(_name, "backgroundLine") )
    return &this->backgroundLine;
  if ( idStr::Icmp(_name, "backgroundHover") )
    return (idWinStr *)idWindow::GetWinVarByName(this, _name, fixup, owner);
  return &this->backgroundHover;
}

// FUNC: public: virtual void __thiscall idListWindow::HandleBuddyUpdate(class idWindow *)
void __thiscall idListWindow::HandleBuddyUpdate(idListWindow *this, idWindow *buddy)
{
  this->top = (int)this->scroller->value.data;
}

// FUNC: public: virtual void __thiscall idListWindow::GainFocus(void)
// attributes: thunk
void __thiscall idListWindow::GainFocus(idSysLocal *this, const idCmdArgs *a2)
{
  SpawnStub(a2);
}

// FUNC: private: void __thiscall idListWindow::ClearSelection(int)
void __thiscall idListWindow::ClearSelection(idListWindow *this, int sel)
{
  int num; // esi
  int v3; // eax
  int *i; // edx
  int v5; // edx
  int v6; // edx
  int *list; // edx
  int v8; // esi
  int *v9; // edx

  num = this->currentSel.num;
  v3 = 0;
  if ( num > 0 )
  {
    for ( i = this->currentSel.list; *i != sel; ++i )
    {
      if ( ++v3 >= num )
        return;
    }
    if ( v3 >= 0 )
    {
      v5 = this->currentSel.num;
      if ( v3 < v5 )
      {
        v6 = v5 - 1;
        for ( this->currentSel.num = v6; v3 < this->currentSel.num; *v9 = v8 )
        {
          list = this->currentSel.list;
          v8 = list[v3 + 1];
          v9 = &list[v3++];
        }
      }
    }
  }
}

// FUNC: private: int __thiscall idListWindow::GetCurrentSel(void)
int __thiscall idListWindow::GetCurrentSel(idListWindow *this)
{
  if ( this->currentSel.num )
    return *this->currentSel.list;
  else
    return 0;
}

// FUNC: private: bool __thiscall idListWindow::IsSelected(int)
bool __thiscall idListWindow::IsSelected(idListWindow *this, int index)
{
  int num; // edx
  int v3; // eax
  int *list; // ecx

  num = this->currentSel.num;
  v3 = 0;
  if ( num <= 0 )
  {
LABEL_5:
    v3 = -1;
  }
  else
  {
    list = this->currentSel.list;
    while ( *list != index )
    {
      ++v3;
      ++list;
      if ( v3 >= num )
        goto LABEL_5;
    }
  }
  return v3 >= 0;
}

// FUNC: private: class idVec4 const & __thiscall idListWindow::GetHighlight(int)
const idVec4 *__thiscall idListWindow::GetHighlight(idListWindow *this, int index)
{
  int num; // edx
  int v3; // eax
  rvPair<int,idVec4> *list; // esi
  rvPair<int,idVec4> *i; // ecx

  num = this->listHighlights.num;
  v3 = 0;
  if ( num <= 0 )
    return &vec4_one;
  list = this->listHighlights.list;
  for ( i = list; i->first != index; ++i )
  {
    if ( ++v3 >= num )
      return &vec4_one;
  }
  return &list[v3].second;
}

// FUNC: private: void __thiscall idListWindow::InitScroller(bool)
void __thiscall idListWindow::InitScroller(idListWindow *this, bool horizontal)
{
  const char *v3; // eax
  const char *v4; // ebp
  idMaterial *v5; // edi
  double ImageWidth; // st7
  double ImageHeight; // st7
  float w; // eax
  float h; // ecx
  double v10; // st6
  const char *v11; // eax
  idRectangle scrollRect; // [esp+10h] [ebp-10h] BYREF

  v3 = "gfx/guis/scrollbarv.tga";
  v4 = "_scrollerWinV";
  if ( horizontal )
  {
    v3 = "gfx/guis/scrollbarh.tga";
    v4 = "_scrollerWinH";
  }
  v5 = (idMaterial *)declManager->FindMaterial(declManager, v3, 1);
  v5->sort = -2.0;
  ImageWidth = (double)idMaterial::GetImageWidth(v5);
  memset(&scrollRect.y, 0, 12);
  this->sizeBias = ImageWidth;
  scrollRect.x = 0.0;
  if ( horizontal )
  {
    ImageHeight = (double)idMaterial::GetImageHeight(v5);
    w = this->clientRect.w;
    scrollRect.x = 0.0;
    scrollRect.w = w;
    this->sizeBias = ImageHeight;
    scrollRect.y = this->clientRect.h - ImageHeight;
    scrollRect.h = ImageHeight;
  }
  else
  {
    h = this->clientRect.h;
    v10 = this->clientRect.w - ImageWidth;
    scrollRect.y = 0.0;
    scrollRect.h = h;
    scrollRect.x = v10;
    scrollRect.w = ImageWidth;
  }
  v11 = v5->base->GetName(v5->base);
  idSliderWindow::InitWithDefaults(
    this->scroller,
    v4,
    &scrollRect,
    &this->foreColor.data,
    &this->matColor.data,
    v11,
    "gfx/guis/scrollbar_thumb.tga",
    !horizontal,
    1);
  if ( !this->scroller->GetBuddy(this->scroller) )
  {
    idWindow::InsertChild(this, this->scroller, 0);
    this->scroller->SetBuddy(this->scroller, this);
  }
}

// FUNC: private: void __thiscall idListWindow::CommonInit(void)
void __thiscall idListWindow::CommonInit(idListWindow *this)
{
  idWinInt_vtbl *v2; // eax
  idStr other; // [esp+8h] [ebp-4Ch] BYREF
  idStr v4; // [esp+28h] [ebp-2Ch] BYREF
  int v5; // [esp+50h] [ebp-4h]

  idStr::operator=(&this->typed, (char *)&entityFilter);
  this->typedTime = 0;
  this->clickTime = 0;
  if ( this->currentSel.list )
    Memory::Free(this->currentSel.list);
  this->currentSel.list = 0;
  this->currentSel.num = 0;
  this->currentSel.size = 0;
  v2 = this->itemHeight.__vftable;
  this->top = 0;
  this->sizeBias = 0.0;
  this->horizontal = 0;
  this->multipleSel = 0;
  this->scroller = 0;
  v2->Set(&this->itemHeight, "0");
  other.len = 0;
  other.alloced = 20;
  other.data = other.baseBuffer;
  other.baseBuffer[0] = 0;
  v5 = 0;
  idWinStr::operator=(&this->backgroundFocus, &other);
  v5 = -1;
  idStr::FreeData(&other);
  other.len = 0;
  other.alloced = 20;
  other.data = other.baseBuffer;
  other.baseBuffer[0] = 0;
  v5 = 1;
  idWinStr::operator=(&this->backgroundLine, &other);
  v5 = -1;
  idStr::FreeData(&other);
  v4.len = 0;
  v4.alloced = 20;
  v4.data = v4.baseBuffer;
  v4.baseBuffer[0] = 0;
  v5 = 2;
  idWinStr::operator=(&this->backgroundHover, &v4);
  v5 = -1;
  idStr::FreeData(&v4);
  idStr::operator=(&this->backgroundGreyed, 0);
  if ( this->greyedLines.list )
    Memory::Free(this->greyedLines.list);
  this->greyedLines.list = 0;
  this->greyedLines.num = 0;
  this->greyedLines.size = 0;
}

// FUNC: private: void __thiscall idListWindow::SetCurrentSel(int)
void __thiscall idListWindow::SetCurrentSel(idListWindow *this, int sel)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v8; // ecx
  int *list; // edi
  int j; // eax

  if ( this->currentSel.list )
    Memory::Free(this->currentSel.list);
  this->currentSel.list = 0;
  this->currentSel.num = 0;
  this->currentSel.size = 0;
  granularity = this->currentSel.granularity;
  if ( granularity > 0 )
  {
    if ( granularity != this->currentSel.size )
    {
      v4 = granularity < this->currentSel.num;
      this->currentSel.size = granularity;
      if ( v4 )
        this->currentSel.num = granularity;
      this->currentSel.list = (int *)Memory::Allocate(4 * granularity);
      for ( i = 0; i < this->currentSel.num; ++i )
        this->currentSel.list[i] = *(_DWORD *)(4 * i);
    }
  }
  else
  {
    this->currentSel.list = 0;
    this->currentSel.num = 0;
    this->currentSel.size = 0;
  }
  num = this->currentSel.num;
  size = this->currentSel.size;
  if ( num == size )
  {
    if ( !this->currentSel.granularity )
      this->currentSel.granularity = 16;
    v8 = size + this->currentSel.granularity - (size + this->currentSel.granularity) % this->currentSel.granularity;
    if ( v8 > 0 )
    {
      if ( v8 != this->currentSel.size )
      {
        list = this->currentSel.list;
        this->currentSel.size = v8;
        if ( v8 < num )
          this->currentSel.num = v8;
        this->currentSel.list = (int *)Memory::Allocate(4 * v8);
        for ( j = 0; j < this->currentSel.num; ++j )
          this->currentSel.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->currentSel.list )
        Memory::Free(this->currentSel.list);
      this->currentSel.list = 0;
      this->currentSel.num = 0;
      this->currentSel.size = 0;
    }
  }
  this->currentSel.list[this->currentSel.num++] = sel;
}

// FUNC: private: void __thiscall idListWindow::AddCurrentSel(int)
void __thiscall idListWindow::AddCurrentSel(idListWindow *this, int sel)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v8; // ecx
  int *list; // edi
  int j; // eax

  if ( !this->currentSel.list )
  {
    granularity = this->currentSel.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->currentSel.size )
      {
        v4 = granularity < this->currentSel.num;
        this->currentSel.size = granularity;
        if ( v4 )
          this->currentSel.num = granularity;
        this->currentSel.list = (int *)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->currentSel.num; ++i )
          this->currentSel.list[i] = *(_DWORD *)(4 * i);
      }
    }
    else
    {
      this->currentSel.list = 0;
      this->currentSel.num = 0;
      this->currentSel.size = 0;
    }
  }
  num = this->currentSel.num;
  size = this->currentSel.size;
  if ( num == size )
  {
    if ( !this->currentSel.granularity )
      this->currentSel.granularity = 16;
    v8 = size + this->currentSel.granularity - (size + this->currentSel.granularity) % this->currentSel.granularity;
    if ( v8 > 0 )
    {
      if ( v8 != this->currentSel.size )
      {
        list = this->currentSel.list;
        this->currentSel.size = v8;
        if ( v8 < num )
          this->currentSel.num = v8;
        this->currentSel.list = (int *)Memory::Allocate(4 * v8);
        for ( j = 0; j < this->currentSel.num; ++j )
          this->currentSel.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->currentSel.list )
        Memory::Free(this->currentSel.list);
      this->currentSel.list = 0;
      this->currentSel.num = 0;
      this->currentSel.size = 0;
    }
  }
  this->currentSel.list[this->currentSel.num++] = sel;
}

// FUNC: public: virtual char const * __thiscall idListWindow::HandleEvent(struct sysEvent_s const *,bool *)
char *__thiscall idListWindow::HandleEvent(idListWindow *this, const sysEvent_s *event, bool *updateVisuals)
{
  const char *v5; // eax
  int data; // ebx
  const char *v7; // ebp
  double MaxCharHeight; // st7
  int evValue; // ebx
  idUserInterfaceLocal *gui; // edi
  int v11; // edi
  int v12; // eax
  idListWindow *v13; // ecx
  idUserInterfaceLocal *v14; // edi
  int v15; // edi
  idUserInterfaceLocal *v16; // ebp
  int time; // eax
  int clickTime; // ecx
  idStr *p_typed; // edi
  int v21; // eax
  int v22; // ebx
  int v23; // ebp
  int v24; // ecx
  int num; // eax
  idSliderWindow *scroller; // ecx
  int v27; // edx
  int v28; // eax
  int v29; // eax
  int CurrentSel; // eax
  int v31; // edx
  int v32; // eax
  int v33; // edi
  idUserInterfaceLocal_vtbl *v34; // ebx
  char *v35; // eax
  idUserInterfaceLocal_vtbl *v36; // ebx
  char *v37; // eax
  idUserInterfaceLocal_vtbl *v38; // edi
  char *v39; // eax
  float x; // [esp+0h] [ebp-38h]
  float xa; // [esp+0h] [ebp-38h]
  float y; // [esp+4h] [ebp-34h]
  float ya; // [esp+4h] [ebp-34h]
  float yb; // [esp+4h] [ebp-34h]
  int yc; // [esp+4h] [ebp-34h]
  int yd; // [esp+4h] [ebp-34h]
  const char *ret; // [esp+18h] [ebp-20h]
  float v48; // [esp+1Ch] [ebp-1Ch]
  int numVisibleLines; // [esp+20h] [ebp-18h]
  sysEvent_s ev; // [esp+24h] [ebp-14h] BYREF
  const sysEvent_s *eventa; // [esp+3Ch] [ebp+4h]
  const sysEvent_s *eventb; // [esp+3Ch] [ebp+4h]

  v5 = idWindow::HandleEvent(this, event, updateVisuals);
  data = this->itemHeight.data;
  v7 = v5;
  ret = v5;
  MaxCharHeight = idWindow::GetMaxCharHeight(this);
  eventa = (const sysEvent_s *)data;
  if ( data <= (int)MaxCharHeight )
    eventa = (const sysEvent_s *)(int)MaxCharHeight;
  evValue = event->evValue;
  v48 = 1.0 / (double)(int)eventa;
  numVisibleLines = (int)(v48 * this->textRect.h);
  eventb = (const sysEvent_s *)evValue;
  if ( event->evType != SE_KEY )
  {
    if ( event->evType == SE_CHAR && idStr::printableCharacter[(unsigned __int8)evValue] )
    {
      if ( this->gui->time > this->typedTime + 1000 )
        idStr::operator=(&this->typed, (char *)&entityFilter);
      p_typed = &this->typed;
      this->typedTime = this->gui->time;
      v21 = this->typed.len + 2;
      if ( v21 > this->typed.alloced )
        idStr::ReAllocate(&this->typed, v21, 1);
      this->typed.data[p_typed->len++] = evValue;
      v22 = 0;
      this->typed.data[p_typed->len] = 0;
      if ( this->listItems.num > 0 )
      {
        v23 = 0;
        while ( idStr::Icmpn(this->typed.data, this->listItems.list[v23].data, p_typed->len) )
        {
          ++v22;
          ++v23;
          if ( v22 >= this->listItems.num )
            goto LABEL_60;
        }
        idListWindow::SetCurrentSel(this, v22);
LABEL_60:
        v7 = ret;
      }
      evValue = (int)eventb;
      goto LABEL_62;
    }
    return (char *)v7;
  }
  if ( !event->evValue2 )
    return (char *)v7;
  if ( evValue == 187 || evValue == 188 )
  {
    if ( this->scroller )
    {
      gui = this->gui;
      y = ((double (*)(void))gui->CursorY)();
      x = gui->CursorX(gui);
      if ( idWindow::Contains(this->scroller, x, y) )
        return (char *)v7;
    }
  }
  if ( evValue == 13 || evValue == 174 )
    goto LABEL_43;
  if ( evValue != 196 )
  {
    if ( evValue == 195 )
    {
      evValue = 134;
      goto LABEL_16;
    }
    if ( evValue != 187 )
      goto LABEL_16;
    v14 = this->gui;
    ya = ((double (*)(void))v14->CursorY)();
    xa = v14->CursorX(v14);
    if ( !idWindow::Contains(this, xa, ya) )
    {
      if ( !this->currentSel.num )
        goto LABEL_67;
LABEL_62:
      if ( *this->currentSel.list < 0 )
        idListWindow::SetCurrentSel(this, 0);
      if ( this->currentSel.num )
        v24 = *this->currentSel.list;
      else
LABEL_67:
        v24 = 0;
      num = this->listItems.num;
      if ( v24 >= num )
        idListWindow::SetCurrentSel(this, num - 1);
      scroller = this->scroller;
      if ( scroller )
      {
        if ( scroller->high <= 0.0 )
        {
          this->top = 0;
          idSliderWindow::SetValue(scroller, 0.0);
        }
        else
        {
          if ( !idKeyInput::IsDown(141) && !idKeyInput::IsDown(2) )
          {
            v27 = this->currentSel.num;
            if ( v27 )
              v28 = *this->currentSel.list;
            else
              v28 = 0;
            if ( this->top > v28 - 1 )
              this->top = idListWindow::GetCurrentSel(this) - 1;
            if ( v27 )
              v29 = *this->currentSel.list;
            else
              v29 = 0;
            if ( this->top < v29 - numVisibleLines + 2 )
            {
              CurrentSel = idListWindow::GetCurrentSel(this);
              this->top = 2 - v31 + CurrentSel;
            }
          }
          v32 = this->listItems.num - 2;
          if ( this->top > v32 )
            this->top = v32;
          if ( this->top < 0 )
            this->top = 0;
          yb = (float)this->top;
          idSliderWindow::SetValue(this->scroller, yb);
        }
      }
      if ( evValue != 187 && evValue != 96 )
      {
        sys->GenerateMouseButtonEvent(sys, &ev, 1, 1);
        idWindow::HandleEvent(this, &ev, updateVisuals);
      }
      if ( this->currentSel.num <= 0 )
      {
        v36 = this->gui->idWindow::__vftable;
        v37 = va("%s_sel_0", this->listName.data);
        v36->SetStateInt(this->gui, v37, 0);
      }
      else
      {
        v33 = 0;
        do
        {
          v34 = this->gui->idWindow::__vftable;
          yc = this->currentSel.list[v33];
          v35 = va("%s_sel_%i", this->listName.data, v33);
          v34->SetStateInt(this->gui, v35, yc);
          ++v33;
        }
        while ( v33 < this->currentSel.num );
      }
      v38 = this->gui->idWindow::__vftable;
      yd = this->currentSel.num;
      v39 = va("%s_numsel", this->listName.data);
      v38->SetStateInt(this->gui, v39, yd);
      return (char *)v7;
    }
    v15 = this->top
        + (int)((((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorY)(this->gui) - this->actualY - 3.0)
              * v48);
    if ( v15 < 0 || v15 >= this->listItems.num )
    {
      idListWindow::SetCurrentSel(this, this->listItems.num - 1);
      this->clickTime = 0;
      goto LABEL_62;
    }
    if ( this->multipleSel && (idKeyInput::IsDown(141) || idKeyInput::IsDown(2)) )
    {
      if ( idListWindow::IsSelected(this, v15) )
        idListWindow::ClearSelection(this, v15);
      else
        idListWindow::AddCurrentSel(this, v15);
      goto LABEL_62;
    }
    v16 = this->gui;
    time = v16->time;
    clickTime = this->clickTime;
    if ( clickTime > time || time > clickTime + 300 )
      this->clickTime = 0;
    if ( !idListWindow::IsSelected(this, v15) || v16->time >= this->clickTime + 300 )
    {
      idListWindow::SetCurrentSel(this, v15);
      v7 = ret;
      this->clickTime = this->gui->time;
      goto LABEL_62;
    }
LABEL_43:
    this->RunScript(this, 10);
    return this->cmd.data;
  }
  evValue = 133;
LABEL_16:
  this->clickTime = 0;
  if ( evValue == 133 || evValue == 146 || evValue == 134 || evValue == 145 )
  {
    v11 = 1;
    if ( evValue == 146 || evValue == 145 )
      v11 = numVisibleLines / 2;
    if ( evValue == 133 || evValue == 146 )
      v11 = -v11;
    if ( idKeyInput::IsDown(141) || idKeyInput::IsDown(2) )
    {
      this->top += v11;
    }
    else
    {
      v12 = idListWindow::GetCurrentSel(this);
      idListWindow::SetCurrentSel(v13, v11 + v12);
    }
    goto LABEL_62;
  }
  return (char *)v7;
}

// FUNC: public: virtual void __thiscall idListWindow::PostParse(void)
void __thiscall idListWindow::PostParse(idListWindow *this)
{
  int v2; // esi
  int *v3; // ebx
  int v4; // edi
  int v5; // ebp
  int len; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // ebp
  int *v11; // esi
  int *v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // esi
  int v17; // edi
  _BYTE *v18; // ecx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  _BYTE *v22; // esi
  _DWORD *v23; // eax
  int v24; // ecx
  int v25; // edx
  void *v26; // ebp
  int v27; // ebx
  int v28; // edi
  idListWindow *v29; // esi
  int v30; // eax
  int v31; // eax
  int v32; // edx
  int v33; // eax
  _BYTE *v34; // esi
  _DWORD *v35; // eax
  int v36; // ecx
  int v37; // edx
  void *v38; // ebp
  int v39; // ebx
  int v40; // edi
  int v41; // eax
  int v42; // eax
  int v43; // edx
  int v44; // eax
  _BYTE *v45; // esi
  _DWORD *v46; // eax
  int v47; // ecx
  int v48; // edx
  int v49; // ebx
  int v50; // edi
  int v51; // eax
  idVec2 *v52; // eax
  idVec2 *v53; // esi
  idVec2 *v54; // ecx
  float *v55; // eax
  int v56; // edx
  int v57; // ecx
  int v58; // esi
  idVec2 *v59; // ebp
  idVec2 *v60; // eax
  idVec2 *v61; // edi
  idVec2 *v62; // eax
  int v63; // edx
  int v64; // ecx
  void *v65; // ebp
  int v66; // ebx
  int v67; // edi
  int v68; // eax
  int v69; // eax
  int v70; // ecx
  int v71; // eax
  _BYTE *v72; // esi
  _DWORD *v73; // eax
  int v74; // ecx
  int v75; // edx
  void *v76; // ebp
  int v77; // ebx
  int v78; // edi
  int v79; // eax
  int v80; // eax
  int v81; // ecx
  int v82; // eax
  _BYTE *v83; // esi
  _DWORD *v84; // eax
  int v85; // ecx
  int v86; // edx
  int v87; // eax
  float v88; // eax
  int granularity; // esi
  bool v90; // cc
  idTabRect *v91; // eax
  idTabRect *v92; // edi
  int v93; // edx
  int v94; // eax
  int num; // edi
  int v96; // eax
  int v97; // esi
  idTabRect *list; // ebp
  idTabRect *v99; // eax
  idTabRect *v100; // edi
  int v101; // edx
  int v102; // eax
  const idCmdArgs *v103; // [esp+0h] [ebp-1F4h]
  int v104; // [esp+10h] [ebp-1E4h]
  int v105; // [esp+10h] [ebp-1E4h]
  int v106; // [esp+10h] [ebp-1E4h]
  float v107; // [esp+10h] [ebp-1E4h]
  float v108; // [esp+10h] [ebp-1E4h]
  int *v109; // [esp+10h] [ebp-1E4h]
  int tabSizes; // [esp+1Ch] [ebp-1D8h]
  idVec2 *tabSizes_12; // [esp+28h] [ebp-1CCh]
  int tabAligns; // [esp+2Ch] [ebp-1C8h]
  int tabAligns_4; // [esp+30h] [ebp-1C4h]
  _BYTE *tabAligns_12; // [esp+38h] [ebp-1BCh]
  int tabStops; // [esp+3Ch] [ebp-1B8h]
  int *tabStops_12; // [esp+48h] [ebp-1ACh]
  int tabIconVOffsets; // [esp+4Ch] [ebp-1A8h]
  void *tabIconVOffsets_12; // [esp+58h] [ebp-19Ch]
  int tabTextScales; // [esp+5Ch] [ebp-198h]
  void *tabTextScales_12; // [esp+68h] [ebp-18Ch]
  int tabVAligns; // [esp+6Ch] [ebp-188h]
  void *tabVAligns_12; // [esp+78h] [ebp-17Ch]
  int tabTypes; // [esp+7Ch] [ebp-178h]
  void *tabTypes_12; // [esp+88h] [ebp-16Ch]
  int i; // [esp+90h] [ebp-164h]
  float *p_x; // [esp+94h] [ebp-160h]
  idToken tok; // [esp+98h] [ebp-15Ch] BYREF
  idVec2 size; // [esp+E8h] [ebp-10Ch]
  int v130; // [esp+F0h] [ebp-104h]
  int v131; // [esp+F4h] [ebp-100h]
  idTabRect r; // [esp+F8h] [ebp-FCh] BYREF
  int v133; // [esp+11Ch] [ebp-D8h]
  int v134; // [esp+120h] [ebp-D4h]
  int v135; // [esp+124h] [ebp-D0h]
  idParser src; // [esp+128h] [ebp-CCh] BYREF
  int v137; // [esp+1F0h] [ebp-4h]

  SpawnStub(v103);
  if ( this->scroller )
    idListWindow::InitScroller(this, this->horizontal);
  v2 = 0;
  v3 = 0;
  v4 = 0;
  tabStops_12 = 0;
  tabStops = 0;
  v5 = 0;
  v137 = 0;
  tabAligns_12 = 0;
  tabAligns = 0;
  tabAligns_4 = 0;
  len = this->tabStopStr.len;
  LOBYTE(v137) = 1;
  if ( len )
  {
    idParser::idParser(&src, this->tabStopStr.data, len, "tabstops", 28);
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    LOBYTE(v137) = 3;
    while ( idParser::ReadToken(&src, &tok) )
    {
      if ( idStr::Cmp(tok.data, ",") )
      {
        v104 = atoi(tok.data);
        if ( !v3 && v4 != 16 )
        {
          v4 = 16;
          if ( v2 > 16 )
          {
            v2 = 16;
            tabStops = 16;
          }
          v3 = (int *)Memory::Allocate(0x40u);
          v7 = 0;
          for ( tabStops_12 = v3; v7 < v2; ++v7 )
            v3[v7] = *(_DWORD *)(4 * v7);
        }
        if ( v2 == v4 )
        {
          v8 = (v4 + 16) % 16;
          v9 = v4 + 16 - v8;
          if ( v9 > 0 )
          {
            if ( v9 != v4 )
            {
              v10 = tabStops;
              v4 = v4 + 16 - v8;
              v11 = v3;
              if ( v9 < tabStops )
              {
                v10 = v9;
                tabStops = v9;
              }
              v12 = (int *)Memory::Allocate(4 * v9);
              v3 = v12;
              tabStops_12 = v12;
              if ( v10 > 0 )
              {
                v13 = tabStops;
                v14 = (char *)v11 - (char *)v12;
                do
                {
                  *v12 = *(int *)((char *)v12 + v14);
                  ++v12;
                  --v13;
                }
                while ( v13 );
              }
              if ( v11 )
                Memory::Free(v11);
            }
          }
          else
          {
            if ( v3 )
              Memory::Free(v3);
            v3 = 0;
            v4 = 0;
            tabStops_12 = 0;
            tabStops = 0;
          }
        }
        v5 = 0;
        v3[tabStops++] = v104;
        v2 = tabStops;
      }
    }
    LOBYTE(v137) = 2;
    idStr::FreeData(&tok);
    LOBYTE(v137) = 1;
    idParser::~idParser(&src);
  }
  v15 = this->tabAlignStr.len;
  if ( v15 )
  {
    idParser::idParser(&src, this->tabAlignStr.data, v15, "tabaligns", 28);
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    LOBYTE(v137) = 5;
    if ( idParser::ReadToken(&src, &tok) )
    {
      v16 = 0;
      do
      {
        if ( idStr::Cmp(tok.data, ",") )
        {
          v17 = atoi(tok.data);
          if ( !tabAligns_12 && v16 != 16 )
          {
            v16 = 16;
            tabAligns_4 = 16;
            if ( v5 > 16 )
              v5 = 16;
            v18 = Memory::Allocate(0x40u);
            v19 = 0;
            for ( tabAligns_12 = v18; v19 < v5; ++v19 )
              *(_DWORD *)&v18[4 * v19] = *(_DWORD *)(4 * v19);
          }
          if ( v5 == v16 )
          {
            v20 = (tabAligns_4 + 16) % 16;
            v21 = tabAligns_4 + 16 - v20;
            if ( v21 > 0 )
            {
              if ( v21 != tabAligns_4 )
              {
                v22 = tabAligns_12;
                tabAligns_4 = tabAligns_4 + 16 - v20;
                if ( v21 < v5 )
                  v5 = v21;
                v23 = Memory::Allocate(4 * v21);
                tabAligns_12 = v23;
                if ( v5 > 0 )
                {
                  v24 = v22 - (_BYTE *)v23;
                  v25 = v5;
                  do
                  {
                    *v23 = *(_DWORD *)((char *)v23 + v24);
                    ++v23;
                    --v25;
                  }
                  while ( v25 );
                }
                if ( v22 )
                  Memory::Free(v22);
              }
            }
            else
            {
              if ( tabAligns_12 )
                Memory::Free(tabAligns_12);
              tabAligns_12 = 0;
              v5 = 0;
              tabAligns_4 = 0;
            }
          }
          v16 = tabAligns_4;
          *(_DWORD *)&tabAligns_12[4 * v5++] = v17;
          tabAligns = v5;
        }
      }
      while ( idParser::ReadToken(&src, &tok) );
    }
    LOBYTE(v137) = 4;
    idStr::FreeData(&tok);
    LOBYTE(v137) = 1;
    idParser::~idParser(&src);
  }
  v26 = 0;
  v27 = 0;
  v28 = 0;
  tabVAligns_12 = 0;
  tabVAligns = 0;
  v29 = this;
  v30 = this->tabVAlignStr.len;
  LOBYTE(v137) = 6;
  if ( v30 )
  {
    idParser::idParser(&src, this->tabVAlignStr.data, v30, "tabvaligns", 28);
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    LOBYTE(v137) = 8;
    while ( idParser::ReadToken(&src, &tok) )
    {
      if ( idStr::Cmp(tok.data, ",") )
      {
        v105 = atoi(tok.data);
        if ( !v26 && v28 != 16 )
        {
          v28 = 16;
          if ( v27 > 16 )
            v27 = 16;
          v26 = Memory::Allocate(0x40u);
          v31 = 0;
          for ( tabVAligns_12 = v26; v31 < v27; ++v31 )
            *((_DWORD *)v26 + v31) = *(_DWORD *)(4 * v31);
        }
        if ( v27 == v28 )
        {
          v32 = (v28 + 16) % 16;
          v33 = v28 + 16 - v32;
          if ( v33 > 0 )
          {
            if ( v33 != v28 )
            {
              v28 = v28 + 16 - v32;
              v34 = v26;
              if ( v33 < v27 )
                v27 = v33;
              v35 = Memory::Allocate(4 * v33);
              v26 = v35;
              tabVAligns_12 = v35;
              if ( v27 > 0 )
              {
                v36 = v34 - (_BYTE *)v35;
                v37 = v27;
                do
                {
                  *v35 = *(_DWORD *)((char *)v35 + v36);
                  ++v35;
                  --v37;
                }
                while ( v37 );
                v26 = tabVAligns_12;
              }
              if ( v34 )
                Memory::Free(v34);
            }
          }
          else
          {
            if ( v26 )
              Memory::Free(v26);
            v26 = 0;
            v27 = 0;
            v28 = 0;
            tabVAligns_12 = 0;
          }
        }
        v29 = this;
        *((_DWORD *)v26 + v27++) = v105;
        tabVAligns = v27;
      }
    }
    LOBYTE(v137) = 7;
    idStr::FreeData(&tok);
    LOBYTE(v137) = 6;
    idParser::~idParser(&src);
  }
  v38 = 0;
  v39 = 0;
  v40 = 0;
  tabTypes_12 = 0;
  tabTypes = 0;
  v41 = v29->tabTypeStr.len;
  LOBYTE(v137) = 9;
  if ( v41 )
  {
    idParser::idParser(&src, v29->tabTypeStr.data, v41, "tabtypes", 28);
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    LOBYTE(v137) = 11;
    while ( idParser::ReadToken(&src, &tok) )
    {
      if ( idStr::Cmp(tok.data, ",") )
      {
        v106 = atoi(tok.data);
        if ( !v38 && v40 != 16 )
        {
          v40 = 16;
          if ( v39 > 16 )
            v39 = 16;
          v38 = Memory::Allocate(0x40u);
          v42 = 0;
          for ( tabTypes_12 = v38; v42 < v39; ++v42 )
            *((_DWORD *)v38 + v42) = *(_DWORD *)(4 * v42);
        }
        if ( v39 == v40 )
        {
          v43 = (v40 + 16) % 16;
          v44 = v40 + 16 - v43;
          if ( v44 > 0 )
          {
            if ( v44 != v40 )
            {
              v40 = v40 + 16 - v43;
              v45 = v38;
              if ( v44 < v39 )
                v39 = v44;
              v46 = Memory::Allocate(4 * v44);
              v38 = v46;
              tabTypes_12 = v46;
              if ( v39 > 0 )
              {
                v47 = v45 - (_BYTE *)v46;
                v48 = v39;
                do
                {
                  *v46 = *(_DWORD *)((char *)v46 + v47);
                  ++v46;
                  --v48;
                }
                while ( v48 );
                v38 = tabTypes_12;
              }
              if ( v45 )
                Memory::Free(v45);
            }
          }
          else
          {
            if ( v38 )
              Memory::Free(v38);
            v38 = 0;
            v39 = 0;
            v40 = 0;
            tabTypes_12 = 0;
          }
        }
        v29 = this;
        *((_DWORD *)v38 + v39++) = v106;
        tabTypes = v39;
      }
    }
    LOBYTE(v137) = 10;
    idStr::FreeData(&tok);
    LOBYTE(v137) = 9;
    idParser::~idParser(&src);
  }
  v49 = 0;
  v50 = 0;
  tabSizes_12 = 0;
  tabSizes = 0;
  v51 = v29->tabIconSizeStr.len;
  LOBYTE(v137) = 12;
  if ( v51 )
  {
    idParser::idParser(&src, v29->tabIconSizeStr.data, v51, "tabiconsizes", 28);
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    LOBYTE(v137) = 14;
    while ( idParser::ReadToken(&src, &tok) )
    {
      if ( idStr::Cmp(tok.data, ",") )
      {
        size.x = (float)atoi(tok.data);
        idParser::ReadToken(&src, &tok);
        idParser::ReadToken(&src, &tok);
        size.y = (float)atoi(tok.data);
        if ( !tabSizes_12 && v49 != 16 )
        {
          v49 = 16;
          if ( v50 > 16 )
          {
            v50 = 16;
            tabSizes = 16;
          }
          v52 = (idVec2 *)Memory::Allocate(0x80u);
          v53 = v52;
          LOBYTE(v137) = 15;
          if ( v52 )
          {
            `vector constructor iterator'(v52, 8u, 16, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
            v54 = v53;
          }
          else
          {
            v54 = 0;
          }
          LOBYTE(v137) = 14;
          tabSizes_12 = v54;
          if ( v50 > 0 )
          {
            v55 = 0;
            v56 = v50;
            do
            {
              *(float *)((char *)&v54->x + (_DWORD)v55) = *v55;
              *(float *)((char *)&v54->y + (_DWORD)v55) = v55[1];
              v55 += 2;
              --v56;
            }
            while ( v56 );
          }
        }
        if ( v50 == v49 )
        {
          v57 = (v49 + 16) % 16;
          v58 = v49 + 16 - v57;
          if ( v58 > 0 )
          {
            if ( v58 != v49 )
            {
              v59 = tabSizes_12;
              v49 = v49 + 16 - v57;
              if ( v58 < tabSizes )
                tabSizes = v58;
              v60 = (idVec2 *)Memory::Allocate(8 * v58);
              v61 = v60;
              LOBYTE(v137) = 16;
              if ( v60 )
              {
                `vector constructor iterator'(v60, 8u, v58, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
                v62 = v61;
              }
              else
              {
                v62 = 0;
              }
              v63 = tabSizes;
              LOBYTE(v137) = 14;
              tabSizes_12 = v62;
              if ( tabSizes > 0 )
              {
                v64 = (char *)v59 - (char *)v62;
                do
                {
                  v62->x = *(float *)((char *)&v62->x + v64);
                  v62->y = *(float *)((char *)&v62->y + v64);
                  ++v62;
                  --v63;
                }
                while ( v63 );
              }
              if ( v59 )
                Memory::Free(v59);
            }
          }
          else
          {
            if ( tabSizes_12 )
              Memory::Free(tabSizes_12);
            v49 = 0;
            tabSizes_12 = 0;
            tabSizes = 0;
          }
        }
        v29 = this;
        tabSizes_12[tabSizes++] = size;
        v50 = tabSizes;
      }
    }
    LOBYTE(v137) = 13;
    idStr::FreeData(&tok);
    LOBYTE(v137) = 12;
    idParser::~idParser(&src);
  }
  v65 = 0;
  v66 = 0;
  v67 = 0;
  tabTextScales_12 = 0;
  tabTextScales = 0;
  v68 = v29->tabTextScalesStr.len;
  LOBYTE(v137) = 17;
  if ( v68 )
  {
    idParser::idParser(&src, v29->tabTextScalesStr.data, v68, "tabTextScales", 28);
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    LOBYTE(v137) = 19;
    while ( idParser::ReadToken(&src, &tok) )
    {
      if ( idStr::Cmp(tok.data, ",") )
      {
        v107 = atof(tok.data);
        if ( !v65 && v67 != 16 )
        {
          v67 = 16;
          if ( v66 > 16 )
            v66 = 16;
          v65 = Memory::Allocate(0x40u);
          v69 = 0;
          for ( tabTextScales_12 = v65; v69 < v66; ++v69 )
            *((_DWORD *)v65 + v69) = *(_DWORD *)(4 * v69);
        }
        if ( v66 == v67 )
        {
          v70 = (v67 + 16) % 16;
          v71 = v67 + 16 - v70;
          if ( v71 > 0 )
          {
            if ( v71 != v67 )
            {
              v67 = v67 + 16 - v70;
              v72 = v65;
              if ( v71 < v66 )
                v66 = v71;
              v73 = Memory::Allocate(4 * v71);
              v65 = v73;
              tabTextScales_12 = v73;
              if ( v66 > 0 )
              {
                v74 = v72 - (_BYTE *)v73;
                v75 = v66;
                do
                {
                  *v73 = *(_DWORD *)((char *)v73 + v74);
                  ++v73;
                  --v75;
                }
                while ( v75 );
                v65 = tabTextScales_12;
              }
              if ( v72 )
                Memory::Free(v72);
            }
          }
          else
          {
            if ( v65 )
              Memory::Free(v65);
            v65 = 0;
            v66 = 0;
            v67 = 0;
            tabTextScales_12 = 0;
          }
        }
        v29 = this;
        *((float *)v65 + v66++) = v107;
        tabTextScales = v66;
      }
    }
    LOBYTE(v137) = 18;
    idStr::FreeData(&tok);
    LOBYTE(v137) = 17;
    idParser::~idParser(&src);
  }
  v76 = 0;
  v77 = 0;
  v78 = 0;
  tabIconVOffsets_12 = 0;
  tabIconVOffsets = 0;
  v79 = v29->tabIconVOffsetStr.len;
  LOBYTE(v137) = 20;
  if ( v79 )
  {
    idParser::idParser(&src, v29->tabIconVOffsetStr.data, v79, "tabiconvoffsets", 28);
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    LOBYTE(v137) = 22;
    while ( idParser::ReadToken(&src, &tok) )
    {
      if ( idStr::Cmp(tok.data, ",") )
      {
        v108 = atof(tok.data);
        if ( !v76 && v78 != 16 )
        {
          v78 = 16;
          if ( v77 > 16 )
            v77 = 16;
          v76 = Memory::Allocate(0x40u);
          v80 = 0;
          for ( tabIconVOffsets_12 = v76; v80 < v77; ++v80 )
            *((_DWORD *)v76 + v80) = *(_DWORD *)(4 * v80);
        }
        if ( v77 == v78 )
        {
          v81 = (v78 + 16) % 16;
          v82 = v78 + 16 - v81;
          if ( v82 > 0 )
          {
            if ( v82 != v78 )
            {
              v78 = v78 + 16 - v81;
              v83 = v76;
              if ( v82 < v77 )
                v77 = v82;
              v84 = Memory::Allocate(4 * v82);
              v76 = v84;
              tabIconVOffsets_12 = v84;
              if ( v77 > 0 )
              {
                v85 = v83 - (_BYTE *)v84;
                v86 = v77;
                do
                {
                  *v84 = *(_DWORD *)((char *)v84 + v85);
                  ++v84;
                  --v86;
                }
                while ( v86 );
                v76 = tabIconVOffsets_12;
              }
              if ( v83 )
                Memory::Free(v83);
            }
          }
          else
          {
            if ( v76 )
              Memory::Free(v76);
            v76 = 0;
            v77 = 0;
            v78 = 0;
            tabIconVOffsets_12 = 0;
          }
        }
        *((float *)v76 + v77++) = v108;
        tabIconVOffsets = v77;
      }
    }
    LOBYTE(v137) = 21;
    idStr::FreeData(&tok);
    LOBYTE(v137) = 20;
    idParser::~idParser(&src);
  }
  i = 0;
  if ( tabStops > 0 )
  {
    v135 = tabStops - 1;
    v131 = tabAligns_12 - (_BYTE *)tabStops_12;
    v134 = (_BYTE *)tabVAligns_12 - (_BYTE *)tabStops_12;
    v130 = (_BYTE *)tabTypes_12 - (_BYTE *)tabStops_12;
    v133 = (_BYTE *)tabIconVOffsets_12 - (_BYTE *)tabStops_12;
    p_x = &tabSizes_12->x;
    v109 = tabStops_12;
    do
    {
      v87 = *v109;
      r.x = *v109;
      if ( i >= v135 )
        r.w = -1;
      else
        r.w = v109[1] - v87 - 4;
      if ( tabAligns == tabStops )
        r.align = *(int *)((char *)v109 + v131);
      else
        r.align = 0;
      if ( tabVAligns <= i )
        r.valign = 0;
      else
        r.valign = *(int *)((char *)v109 + v134);
      if ( tabTypes <= i )
        r.type = 0;
      else
        r.type = *(int *)((char *)v109 + v130);
      if ( tabSizes <= i )
      {
        r.iconSize.y = 0.0;
        r.iconSize.x = 0.0;
      }
      else
      {
        v88 = p_x[1];
        r.iconSize.x = *p_x;
        r.iconSize.y = v88;
      }
      if ( tabIconVOffsets <= i )
        r.iconVOffset = 0.0;
      else
        r.iconVOffset = *(float *)((char *)v109 + v133);
      if ( tabTextScales <= i )
        r.textScale = this->textScale.data;
      else
        r.textScale = *(float *)((char *)v109 + (_BYTE *)tabTextScales_12 - (_BYTE *)tabStops_12);
      if ( !this->tabInfo.list )
      {
        granularity = this->tabInfo.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->tabInfo.size )
          {
            v90 = granularity < this->tabInfo.num;
            this->tabInfo.size = granularity;
            if ( v90 )
              this->tabInfo.num = granularity;
            v91 = (idTabRect *)Memory::Allocate(36 * granularity);
            v92 = v91;
            LODWORD(size.x) = v91;
            LOBYTE(v137) = 23;
            if ( v91 )
              `vector constructor iterator'(
                v91,
                0x24u,
                granularity,
                (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
            else
              v92 = 0;
            v93 = 0;
            v90 = this->tabInfo.num <= 0;
            LOBYTE(v137) = 20;
            this->tabInfo.list = v92;
            if ( !v90 )
            {
              v94 = 0;
              do
              {
                ++v93;
                qmemcpy(&this->tabInfo.list[v94], (const void *)(v94 * 36), sizeof(this->tabInfo.list[v94]));
                ++v94;
              }
              while ( v93 < this->tabInfo.num );
            }
          }
        }
        else
        {
          this->tabInfo.list = 0;
          this->tabInfo.num = 0;
          this->tabInfo.size = 0;
        }
      }
      num = this->tabInfo.num;
      v96 = this->tabInfo.size;
      if ( num == v96 )
      {
        if ( !this->tabInfo.granularity )
          this->tabInfo.granularity = 16;
        v97 = v96 + this->tabInfo.granularity - (v96 + this->tabInfo.granularity) % this->tabInfo.granularity;
        if ( v97 > 0 )
        {
          if ( v97 != this->tabInfo.size )
          {
            list = this->tabInfo.list;
            this->tabInfo.size = v97;
            if ( v97 < num )
              this->tabInfo.num = v97;
            v99 = (idTabRect *)Memory::Allocate(36 * v97);
            v100 = v99;
            LODWORD(size.x) = v99;
            LOBYTE(v137) = 24;
            if ( v99 )
              `vector constructor iterator'(v99, 0x24u, v97, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
            else
              v100 = 0;
            v101 = 0;
            v90 = this->tabInfo.num <= 0;
            LOBYTE(v137) = 20;
            this->tabInfo.list = v100;
            if ( !v90 )
            {
              v102 = 0;
              do
              {
                ++v101;
                qmemcpy(&this->tabInfo.list[v102], &list[v102], sizeof(this->tabInfo.list[v102]));
                ++v102;
              }
              while ( v101 < this->tabInfo.num );
            }
            if ( list )
              Memory::Free(list);
          }
        }
        else
        {
          if ( this->tabInfo.list )
            Memory::Free(this->tabInfo.list);
          this->tabInfo.list = 0;
          this->tabInfo.num = 0;
          this->tabInfo.size = 0;
        }
      }
      p_x += 2;
      ++v109;
      qmemcpy(&this->tabInfo.list[this->tabInfo.num++], &r, sizeof(this->tabInfo.list[this->tabInfo.num++]));
      ++i;
    }
    while ( i < tabStops );
  }
  BYTE1(this->flags) |= 8u;
  LOBYTE(v137) = 17;
  if ( tabIconVOffsets_12 )
    Memory::Free(tabIconVOffsets_12);
  LOBYTE(v137) = 12;
  if ( tabTextScales_12 )
    Memory::Free(tabTextScales_12);
  LOBYTE(v137) = 9;
  if ( tabSizes_12 )
    Memory::Free(tabSizes_12);
  LOBYTE(v137) = 6;
  if ( tabTypes_12 )
    Memory::Free(tabTypes_12);
  LOBYTE(v137) = 1;
  if ( tabVAligns_12 )
    Memory::Free(tabVAligns_12);
  LOBYTE(v137) = 0;
  if ( tabAligns_12 )
    Memory::Free(tabAligns_12);
  v137 = -1;
  if ( tabStops_12 )
    Memory::Free(tabStops_12);
}

// FUNC: public: virtual bool __thiscall idListWindow::RunScript(int)
bool __thiscall idListWindow::RunScript(idListWindow *this, int n)
{
  bool v3; // bl
  const char *v4; // edi
  idDict *v5; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int v8; // eax

  v3 = idWindow::RunScript(this, n);
  v4 = va("%s_sel_0", this->listName.data);
  v5 = (idDict *)this->gui->State(this->gui);
  Key = idDict::FindKey(v5, v4);
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  v8 = atoi(data);
  idListWindow::SetCurrentSel(this, v8);
  return v3;
}

// FUNC: private: virtual bool __thiscall idListWindow::ParseInternalVar(char const *,class idParser *)
bool __thiscall idListWindow::ParseInternalVar(idListWindow *this, const char *_name, idParser *src)
{
  bool result; // al
  idSliderWindow *v6; // eax
  idSliderWindow *v7; // eax
  char *data; // esi
  idMaterial *v9; // esi
  const idMaterial *v10; // eax
  const char *v11; // eax
  int v12; // ebp
  int v13; // eax
  char *v14; // edx
  const char *v15; // ecx
  char v16; // al
  idMaterial *v17; // ebp
  char v18; // al
  int v19; // edi
  const char *i; // ecx
  int v21; // ebp
  idHashTable<idMaterial const *>::hashnode_s **heads; // ebp
  int v23; // eax
  idHashTable<idMaterial const *>::hashnode_s *v24; // edi
  idHashTable<idMaterial const *>::hashnode_s **p_next; // ebp
  int v26; // eax
  idHashTable<rvDeclGuide *>::hashnode_s *v27; // eax
  idHashTable<idMaterial const *>::hashnode_s *v28; // eax
  bool v29; // bl
  char *v30; // [esp-10h] [ebp-88h]
  idStr strName; // [esp+Ch] [ebp-6Ch] BYREF
  idStr tmp; // [esp+2Ch] [ebp-4Ch] BYREF
  idStr matName; // [esp+4Ch] [ebp-2Ch] BYREF
  int v34; // [esp+74h] [ebp-4h]
  bool _nameb; // [esp+7Ch] [ebp+4h]
  const char *_namea; // [esp+7Ch] [ebp+4h]
  idParser *srca; // [esp+80h] [ebp+8h]

  if ( !idStr::Icmp(_name, "horizontal") )
  {
    this->horizontal = idParser::ParseBool(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "listname") )
  {
    idWindow::ParseString(this, src, &this->listName);
    return 1;
  }
  if ( !idStr::Icmp(_name, "tabstops") )
  {
    idWindow::ParseString(this, src, &this->tabStopStr);
    return 1;
  }
  if ( !idStr::Icmp(_name, "tabaligns") )
  {
    idWindow::ParseString(this, src, &this->tabAlignStr);
    return 1;
  }
  if ( !idStr::Icmp(_name, "multipleSel") )
  {
    this->multipleSel = idParser::ParseBool(src);
    return 1;
  }
  if ( !idStr::Icmp(_name, "tabvaligns") )
  {
    idWindow::ParseString(this, src, &this->tabVAlignStr);
    return 1;
  }
  if ( !idStr::Icmp(_name, "scrollbar") )
  {
    if ( idParser::ParseBool(src) && !this->scroller )
    {
      v6 = (idSliderWindow *)Memory::Allocate(0x4FCu);
      v34 = 0;
      if ( v6 )
      {
        idSliderWindow::idSliderWindow(v6, this->dc, this->gui);
        this->scroller = v7;
        return 1;
      }
      else
      {
        result = 1;
        this->scroller = 0;
      }
      return result;
    }
    return 1;
  }
  if ( !idStr::Icmp(_name, "tabTypes") )
  {
    idWindow::ParseString(this, src, &this->tabTypeStr);
    return 1;
  }
  if ( !idStr::Icmp(_name, "backgroundFocus") )
  {
    tmp.len = 0;
    tmp.alloced = 20;
    tmp.data = tmp.baseBuffer;
    tmp.baseBuffer[0] = 0;
    v34 = 1;
    idWindow::ParseString(this, src, &tmp);
    idWinStr::operator=(&this->backgroundFocus, &tmp);
    data = this->backgroundFocus.data.data;
    goto LABEL_27;
  }
  if ( !idStr::Icmp(_name, "backgroundLine") )
  {
    tmp.len = 0;
    tmp.alloced = 20;
    tmp.data = tmp.baseBuffer;
    tmp.baseBuffer[0] = 0;
    v34 = 2;
    idWindow::ParseString(this, src, &tmp);
    idWinStr::operator=(&this->backgroundLine, &tmp);
    data = this->backgroundLine.data.data;
    goto LABEL_27;
  }
  if ( !idStr::Icmp(_name, "backgroundHover") )
  {
    tmp.len = 0;
    tmp.alloced = 20;
    tmp.data = tmp.baseBuffer;
    tmp.baseBuffer[0] = 0;
    v34 = 3;
    idWindow::ParseString(this, src, &tmp);
    idWinStr::operator=(&this->backgroundHover, &tmp);
    data = this->backgroundHover.data.data;
LABEL_27:
    v9 = (idMaterial *)declManager->FindMaterial(declManager, data, 1);
    idMaterial::SetImageClassifications(v9, 1);
    if ( v9 && (v9->materialFlags & 1) == 0 )
      v9->sort = -2.0;
    v34 = -1;
    idStr::FreeData(&tmp);
    return 1;
  }
  if ( idStr::Icmp(_name, "backgroundGreyed") )
  {
    if ( idStr::Icmp(_name, "tabTextScales") )
    {
      if ( idStr::Icmp(_name, "tabIconSizes") )
      {
        if ( idStr::Icmp(_name, "tabIconVOffset") )
        {
          strName.len = 0;
          strName.alloced = 20;
          strName.data = strName.baseBuffer;
          strName.baseBuffer[0] = 0;
          if ( _name )
          {
            v11 = &_name[strlen(_name) + 1];
            v12 = v11 - (_name + 1);
            v13 = v11 - _name;
            if ( v13 > 20 )
              idStr::ReAllocate(&strName, v13, 1);
            v14 = strName.data;
            v15 = _name;
            do
            {
              v16 = *v15;
              *v14++ = *v15++;
            }
            while ( v16 );
            strName.len = v12;
          }
          v34 = 4;
          v30 = idStr::Left(&strName, &matName, 4)->data;
          LOBYTE(v34) = 5;
          _nameb = idStr::Icmp(v30, "mtr_") == 0;
          LOBYTE(v34) = 4;
          idStr::FreeData(&matName);
          if ( _nameb )
          {
            matName.len = 0;
            matName.alloced = 20;
            matName.data = matName.baseBuffer;
            matName.baseBuffer[0] = 0;
            LOBYTE(v34) = 6;
            idWindow::ParseString(this, src, &matName);
            v17 = (idMaterial *)declManager->FindMaterial(declManager, matName.data, 1);
            srca = (idParser *)v17;
            idMaterial::SetImageClassifications(v17, 1);
            if ( v17 && (v17->materialFlags & 1) == 0 )
              v17->sort = -2.0;
            v18 = *_name;
            v19 = 0;
            for ( i = _name; v18; v19 += v21 )
            {
              v21 = v18 * (_DWORD)&i[119 - (_DWORD)_name];
              v18 = *++i;
            }
            heads = this->iconMaterials.heads;
            v23 = v19 & this->iconMaterials.tablesizemask;
            v24 = heads[v23];
            p_next = &heads[v23];
            _namea = (const char *)(v23 * 4);
            if ( v24 )
            {
              while ( 1 )
              {
                v26 = idStr::Cmp(v24->key.data, _name);
                if ( !v26 )
                  break;
                if ( v26 <= 0 )
                {
                  p_next = &v24->next;
                  v24 = v24->next;
                  if ( v24 )
                    continue;
                }
                goto LABEL_59;
              }
              v24->value = (const idMaterial *)srca;
            }
            else
            {
LABEL_59:
              ++this->iconMaterials.numentries;
              v27 = (idHashTable<rvDeclGuide *>::hashnode_s *)Memory::Allocate(0x28u);
              LOBYTE(v34) = 7;
              if ( v27 )
                idHashTable<maTransform_s *>::hashnode_s::hashnode_s(
                  v27,
                  _name,
                  (rvDeclGuide *)srca,
                  *(idHashTable<rvDeclGuide *>::hashnode_s **)&_namea[(unsigned int)this->iconMaterials.heads]);
              else
                v28 = 0;
              *p_next = v28;
              v28->next = v24;
            }
            LOBYTE(v34) = 4;
            idStr::FreeData(&matName);
            v34 = -1;
            idStr::FreeData(&strName);
            return 1;
          }
          else
          {
            v29 = idWindow::ParseInternalVar(this, _name, src);
            v34 = -1;
            idStr::FreeData(&strName);
            return v29;
          }
        }
        else
        {
          idWindow::ParseString(this, src, &this->tabIconVOffsetStr);
          return 1;
        }
      }
      else
      {
        idWindow::ParseString(this, src, &this->tabIconSizeStr);
        return 1;
      }
    }
    else
    {
      idWindow::ParseString(this, src, &this->tabTextScalesStr);
      return 1;
    }
  }
  else
  {
    idWindow::ParseString(this, src, &this->backgroundGreyed);
    v10 = declManager->FindMaterial(declManager, this->backgroundGreyed.data, 1);
    if ( v10 && (v10->materialFlags & 1) == 0 )
      v10->sort = -2.0;
    return 1;
  }
}

// FUNC: public: virtual void __thiscall idListWindow::Draw(int,float,float)
void __thiscall idListWindow::Draw(idListWindow *this, int time, float x, float y)
{
  int num; // ebp
  int data; // ebx
  idRectangle *p_textRect; // edi
  float v8; // ecx
  float w; // eax
  float v10; // edx
  double MaxCharHeight; // st7
  idSliderWindow *scroller; // eax
  idUserInterfaceLocal *gui; // edi
  idUserInterfaceLocal_vtbl *v14; // edx
  idUserInterfaceLocal_vtbl *v15; // edi
  char *v16; // eax
  idDeclManager_vtbl *v17; // edi
  const char *v18; // eax
  int v19; // eax
  idDeclManager_vtbl *v20; // edi
  int v21; // ebp
  int v22; // eax
  float v23; // eax
  idWinStr_vtbl *v24; // edx
  float v25; // edi
  idDeclManager_vtbl *v26; // ebx
  int v27; // eax
  int v28; // ebx
  const idMaterial *v29; // eax
  double v30; // st7
  idUserInterfaceLocal *v31; // edi
  idUserInterfaceLocal_vtbl *v32; // edx
  char *v33; // eax
  idUserInterfaceLocal_vtbl *v34; // edi
  char *v35; // eax
  int v36; // edx
  int v37; // eax
  int *list; // ecx
  int v39; // eax
  rvPair<int,idVec4> *v40; // ecx
  bool v41; // zf
  idUserInterfaceLocal *v42; // edi
  idUserInterfaceLocal_vtbl *v43; // edx
  idVec4 *p_data; // eax
  float v45; // ecx
  float v46; // edx
  float z; // edi
  float v48; // eax
  int v49; // ebp
  bool v50; // cc
  idStr *v51; // eax
  const char *v52; // ecx
  int v53; // edi
  int Char; // eax
  idTabRect *v55; // eax
  double v56; // st7
  idTabRect *v57; // eax
  double v58; // st7
  int valign; // eax
  float v60; // edi
  float v61; // ebp
  float v62; // ebx
  double v63; // st7
  double v64; // st7
  double v65; // st7
  idTabRect *v66; // edx
  int type; // ecx
  char *v68; // ecx
  char v69; // al
  int v70; // edi
  char *j; // ebx
  unsigned int v72; // ebp
  idHashTable<idMaterial const *>::hashnode_s *v73; // edi
  int v74; // eax
  const idMaterial *value; // eax
  idTabRect *v76; // ecx
  int align; // edx
  double v78; // st7
  int v79; // edx
  double v80; // st7
  idDeviceContext *dc; // ecx
  int v82; // ebx
  idStr *v83; // eax
  double v84; // st7
  idVec4 v85; // [esp+8h] [ebp-14Ch]
  idRectangle v86; // [esp+18h] [ebp-13Ch]
  float v87; // [esp+28h] [ebp-12Ch]
  float v88; // [esp+28h] [ebp-12Ch]
  float v89; // [esp+28h] [ebp-12Ch]
  float v90; // [esp+28h] [ebp-12Ch]
  float v91; // [esp+34h] [ebp-120h]
  float h; // [esp+3Ch] [ebp-118h]
  float ha; // [esp+3Ch] [ebp-118h]
  float hb; // [esp+3Ch] [ebp-118h]
  float hc; // [esp+3Ch] [ebp-118h]
  float hd; // [esp+3Ch] [ebp-118h]
  float v97; // [esp+40h] [ebp-114h]
  int v98; // [esp+40h] [ebp-114h]
  float v99; // [esp+40h] [ebp-114h]
  const idVec4 *Highlight; // [esp+40h] [ebp-114h]
  int v101; // [esp+40h] [ebp-114h]
  float v102; // [esp+50h] [ebp-104h]
  idRectangle rect; // [esp+54h] [ebp-100h] BYREF
  unsigned int hovering; // [esp+64h] [ebp-F0h]
  int v105; // [esp+68h] [ebp-ECh]
  int tab; // [esp+6Ch] [ebp-E8h]
  float v107; // [esp+70h] [ebp-E4h]
  int stop; // [esp+74h] [ebp-E0h]
  float bottom; // [esp+78h] [ebp-DCh]
  int i; // [esp+7Ch] [ebp-D8h]
  float lineHeight; // [esp+80h] [ebp-D4h]
  const idMaterial *matLine; // [esp+84h] [ebp-D0h]
  float width; // [esp+88h] [ebp-CCh]
  idRectangle iconRect; // [esp+8Ch] [ebp-C8h]
  idVec4 color; // [esp+9Ch] [ebp-B8h]
  float scale; // [esp+ACh] [ebp-A8h]
  float v117; // [esp+B0h] [ebp-A4h]
  int count; // [esp+B4h] [ebp-A0h]
  idRectangle rectText; // [esp+B8h] [ebp-9Ch]
  idVec4 v120; // [esp+C8h] [ebp-8Ch] BYREF
  idVec4 v121; // [esp+D8h] [ebp-7Ch] BYREF
  idVec4 v122; // [esp+E8h] [ebp-6Ch] BYREF
  idVec4 v123; // [esp+F8h] [ebp-5Ch] BYREF
  idVec4 v124; // [esp+108h] [ebp-4Ch] BYREF
  idRectangle rectHover; // [esp+118h] [ebp-3Ch] BYREF
  idStr work; // [esp+128h] [ebp-2Ch] BYREF
  int v127; // [esp+150h] [ebp-4h]

  work.len = 0;
  work.alloced = 20;
  work.data = work.baseBuffer;
  work.baseBuffer[0] = 0;
  num = this->listItems.num;
  data = this->itemHeight.data;
  p_textRect = &this->textRect;
  v127 = 0;
  v8 = this->textRect.y;
  rect.x = this->textRect.x;
  w = this->textRect.w;
  rect.y = v8;
  v10 = this->textScale.data;
  rect.h = this->textRect.h;
  count = num;
  rect.w = w;
  scale = v10;
  MaxCharHeight = idWindow::GetMaxCharHeight(this);
  bottom = *(float *)&data;
  LODWORD(v107) = (int)MaxCharHeight;
  if ( data <= (int)MaxCharHeight )
    LODWORD(bottom) = (int)MaxCharHeight;
  width = this->textRect.w;
  scroller = this->scroller;
  lineHeight = (float)SLODWORD(bottom);
  bottom = p_textRect->h + p_textRect->y;
  if ( scroller && scroller->high > 0.0 )
  {
    if ( this->horizontal )
    {
      bottom = bottom - this->sizeBias;
    }
    else
    {
      width = width - this->sizeBias;
      rect.w = width;
    }
  }
  if ( this->noEvents.data
    || (gui = this->gui,
        v14 = gui->__vftable,
        tab = (int)gui,
        v97 = ((double (*)(void))v14->CursorY)(),
        h = gui->CursorX(gui),
        !idWindow::Contains(this, h, v97)) )
  {
    this->hover = 0;
  }
  v15 = this->gui->idWindow::__vftable;
  v16 = va("%s_hover", this->listName.data);
  v15->SetStateInt(this->gui, v16, -1);
  i = this->top;
  if ( i >= num )
    goto LABEL_88;
  v105 = 32 * i;
  v107 = lineHeight - 1.0;
  v117 = lineHeight + 3.0;
  do
  {
    v17 = declManager->__vftable;
    v18 = this->backgroundFocus.c_str(&this->backgroundFocus);
    v19 = ((int (__thiscall *)(idDeclManager *, const char *))v17->FindMaterial)(declManager, v18);
    v20 = declManager->__vftable;
    v21 = v19;
    v22 = ((int (__thiscall *)(idWinStr *, int))this->backgroundLine.c_str)(&this->backgroundLine, 1);
    v23 = COERCE_FLOAT(((int (__thiscall *)(idDeclManager *, int))v20->FindMaterial)(declManager, v22));
    v24 = this->backgroundHover.__vftable;
    v25 = v23;
    v26 = declManager->__vftable;
    lineHeight = v23;
    v27 = ((int (__thiscall *)(idWinStr *, int))v24->c_str)(&this->backgroundHover, 1);
    v28 = ((int (__thiscall *)(idDeclManager *, int))v26->FindMaterial)(declManager, v27);
    *(float *)&v29 = COERCE_FLOAT((int)declManager->FindMaterial(declManager, this->backgroundGreyed.data, 1));
    v30 = *(float *)&tab;
    v107 = *(float *)&v29;
    *(_DWORD *)(v21 + 184) = -1073741824;
    *(_DWORD *)(LODWORD(v25) + 184) = -1073741824;
    *(_DWORD *)(v28 + 184) = -1073741824;
    LODWORD(rect.w) = i;
    rectHover.x = rect.x + 3.0;
    v31 = this->gui;
    rectHover.w = v30;
    v124.w = v102;
    rectHover.y = rect.y;
    v32 = v31->__vftable;
    v105 = (int)v31;
    ha = v32->CursorY(v31);
    hb = ((double (__thiscall *)(idUserInterfaceLocal *, _DWORD))v31->CursorX)(v31, LODWORD(ha));
    if ( idWindow::Contains(this, &rectHover, hb, COERCE_FLOAT(1)) )
    {
      v33 = this->listName.data;
      v34 = this->gui->idWindow::__vftable;
      v98 = i;
      LOBYTE(hovering) = 1;
      v35 = va("%s_hover", v33);
      v34->SetStateInt(this->gui, v35, v98);
    }
    else
    {
      LOBYTE(hovering) = 0;
    }
    v36 = this->currentSel.num;
    v37 = 0;
    if ( v36 <= 0 )
      goto LABEL_20;
    list = this->currentSel.list;
    while ( *list != i )
    {
      ++v37;
      ++list;
      if ( v37 >= v36 )
        goto LABEL_20;
    }
    if ( v37 < 0 )
    {
LABEL_20:
      if ( v105 >= 0 && i < this->greyedLines.num && this->greyedLines.list[i] )
      {
        v87 = rect.y + 3.0;
        v123.x = 1.0;
        v123.y = 1.0;
        v123.z = 1.0;
        v123.w = 1.0;
        idDeviceContext::DrawMaterial(this->dc, rect.x, v87, rect.w, rect.h, (const idMaterial *)stop, &v123, 1.0, 1.0);
      }
      else if ( !(_BYTE)hovering || this->noEvents.data )
      {
        v39 = 0;
        if ( this->listHighlights.num <= 0 )
        {
LABEL_33:
          v122.x = 1.0;
          v122.y = 1.0;
          v122.z = 1.0;
          v122.w = 1.0;
          v90 = rect.y + 3.0;
          idDeviceContext::DrawMaterial(this->dc, rect.x, v90, rect.w, rect.h, matLine, &v122, 1.0, 1.0);
        }
        else
        {
          v40 = this->listHighlights.list;
          while ( v40->first != i )
          {
            ++v39;
            ++v40;
            if ( v39 >= this->listHighlights.num )
              goto LABEL_33;
          }
          Highlight = idListWindow::GetHighlight(this, i);
          hd = rect.h - 3.0;
          v91 = rect.y + 3.0;
          idDeviceContext::DrawFilledRect(this->dc, rect.x, v91, rect.w, hd, Highlight);
        }
      }
      else
      {
        v89 = rect.y + 3.0;
        v121.x = 1.0;
        v121.y = 1.0;
        v121.z = 1.0;
        v121.w = 1.0;
        idDeviceContext::DrawMaterial(this->dc, rect.x, v89, rect.w, rect.h, (const idMaterial *)v28, &v121, 1.0, 1.0);
      }
    }
    else
    {
      v88 = rect.y + 3.0;
      v120.x = 1.0;
      v120.y = 1.0;
      v120.z = 1.0;
      v120.w = 1.0;
      idDeviceContext::DrawMaterial(this->dc, rect.x, v88, rect.w, rect.h, (const idMaterial *)v21, &v120, 1.0, 1.0);
    }
    v41 = !this->hover;
    rect.h = v107;
    rect.y = rect.y + 1.0;
    if ( v41
      || this->noEvents.data
      || (v42 = this->gui,
          v43 = v42->__vftable,
          tab = (int)v42,
          v99 = v43->CursorY(v42),
          hc = v42->CursorX(v42),
          !idWindow::Contains(this, &rect, hc, v99)) )
    {
      p_data = &this->foreColor.data;
    }
    else
    {
      p_data = &this->hoverColor.data;
    }
    v45 = p_data->x;
    v46 = p_data->y;
    z = p_data->z;
    v48 = p_data->w;
    v49 = v105;
    rect.y = rect.y - 1.0;
    color.w = v48;
    v50 = this->tabInfo.num <= 0;
    rect.h = v117;
    v51 = this->listItems.list;
    color.x = v45;
    color.y = v46;
    color.z = z;
    if ( v50 )
    {
      *(_QWORD *)&v85.x = __PAIR64__(LODWORD(v46), LODWORD(v45));
      *(_QWORD *)&v85.z = __PAIR64__(LODWORD(color.w), LODWORD(z));
      idDeviceContext::DrawTextA(
        this->dc,
        *(const char **)((char *)&v51->data + v105),
        scale,
        3,
        this->textStyle,
        v85,
        rect,
        0,
        -1,
        0,
        0,
        0,
        0,
        0);
      goto LABEL_86;
    }
    v101 = *(int *)((char *)&v51->len + v105);
    v52 = *(char **)((char *)&v51->data + v105);
    v53 = 0;
    *(float *)&tab = 0.0;
    Char = idStr::FindChar(v52, 9, 0, v101);
    v50 = *(int *)((char *)&this->listItems.list->len + v49) <= 0;
    stop = Char;
    if ( v50 )
      goto LABEL_84;
    hovering = 0;
    while ( tab < this->tabInfo.num )
    {
      idStr::Mid((idStr *)((char *)this->listItems.list + v105), v53, stop - v53, &work);
      v55 = this->tabInfo.list;
      v56 = (double)v55[hovering / 0x24].x;
      v57 = &v55[hovering / 0x24];
      rect.x = v56 + this->textRect.x;
      matLine = (const idMaterial *)v57->w;
      if ( *(float *)&matLine == NAN )
        v58 = width - (double)v57->x;
      else
        v58 = (double)(int)matLine;
      rect.w = v58;
      idDeviceContext::PushClipRect(this->dc, rect);
      valign = this->tabInfo.list[hovering / 0x24].valign;
      v60 = rect.x;
      v61 = rect.w;
      v62 = rect.h;
      rectText.y = rect.y;
      if ( valign )
      {
        if ( valign == 2 )
        {
          v65 = idWindow::GetMaxCharHeight(this);
          v64 = lineHeight - v65 + rectText.y;
        }
        else
        {
          v64 = rectText.y + 3.0;
        }
      }
      else
      {
        *(float *)&matLine = lineHeight * 0.5;
        v63 = idWindow::GetMaxCharHeight(this);
        v64 = *(float *)&matLine - v63 * 0.5 + rectText.y + 1.0;
      }
      v66 = this->tabInfo.list;
      rectText.y = v64;
      type = v66[hovering / 0x24].type;
      if ( type )
      {
        if ( type == 1 )
        {
          v68 = work.data;
          v69 = *work.data;
          v70 = 0;
          for ( j = work.data; v69; v70 += v72 )
          {
            v72 = v69 * (_DWORD)&v68[119 - (unsigned int)work.data];
            v69 = *++v68;
          }
          v73 = this->iconMaterials.heads[v70 & this->iconMaterials.tablesizemask];
          if ( v73 )
          {
            while ( 1 )
            {
              v74 = idStr::Cmp(v73->key.data, j);
              if ( !v74 )
                break;
              if ( v74 <= 0 )
              {
                v73 = v73->next;
                if ( v73 )
                  continue;
              }
              goto LABEL_62;
            }
            value = v73->value;
          }
          else
          {
LABEL_62:
            value = declManager->FindMaterial(declManager, "_default", 1);
          }
          v76 = &this->tabInfo.list[hovering / 0x24];
          iconRect.w = v76->iconSize.x;
          iconRect.h = v76->iconSize.y;
          align = v76->align;
          iconRect.y = 0.0;
          iconRect.x = 0.0;
          switch ( align )
          {
            case 0:
              iconRect.x = rect.x;
              break;
            case 1:
              v78 = rect.w * 0.5 + rect.x - iconRect.w * 0.5;
              goto LABEL_70;
            case 2:
              v78 = rect.x + rect.w - iconRect.w;
LABEL_70:
              iconRect.x = v78;
              break;
          }
          v79 = v76->valign;
          switch ( v79 )
          {
            case 0:
              v80 = rect.y;
              goto LABEL_77;
            case 1:
              v80 = rect.h * 0.5 + rect.y - iconRect.h * 0.5;
              goto LABEL_77;
            case 2:
              v80 = rect.y + rect.h - iconRect.h;
LABEL_77:
              iconRect.y = v80 + v76->iconVOffset;
              break;
          }
          dc = this->dc;
          v124.x = 1.0;
          v124.y = 1.0;
          v124.z = 1.0;
          v124.w = 1.0;
          idDeviceContext::DrawMaterial(dc, iconRect.x, iconRect.y, iconRect.w, iconRect.h, value, &v124, 1.0, 1.0);
        }
      }
      else
      {
        *(_QWORD *)&v86.x = __PAIR64__(LODWORD(rectText.y), LODWORD(v60));
        *(_QWORD *)&v86.w = __PAIR64__(LODWORD(v62), LODWORD(v61));
        idDeviceContext::DrawTextA(
          this->dc,
          work.data,
          v66[hovering / 0x24].textScale,
          v66[hovering / 0x24].align,
          this->textStyle,
          color,
          v86,
          0,
          -1,
          0,
          0,
          0,
          0,
          0);
      }
      idDeviceContext::PopClipRect(this->dc);
      v82 = v105;
      v53 = stop + 1;
      stop = idStr::FindChar(
               *(const char **)((char *)&this->listItems.list->data + v105),
               9,
               stop + 1,
               *(int *)((char *)&this->listItems.list->len + v105));
      if ( stop < 0 )
        stop = *(int *)((char *)&this->listItems.list->len + v82);
      v83 = this->listItems.list;
      ++tab;
      hovering += 36;
      if ( v53 >= *(int *)((char *)&v83->len + v82) )
        goto LABEL_84;
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idListWindow::Draw: gui '%s' window '%s' tabInfo.Num() exceeded",
      this->gui->source.data,
      this->name.data);
LABEL_84:
    rect.x = this->textRect.x;
    rect.w = width;
LABEL_86:
    v84 = rect.y + lineHeight;
    rect.y = v84;
    if ( v84 > bottom )
      break;
    v105 += 32;
    ++i;
  }
  while ( i < count );
LABEL_88:
  v127 = -1;
  idStr::FreeData(&work);
}

// FUNC: public: void __thiscall idListWindow::UpdateList(void)
void __thiscall idListWindow::UpdateList(idListWindow *this)
{
  idStr *list; // eax
  char *v3; // esi
  const char *v4; // esi
  idDict *v5; // eax
  const idKeyValue *Key; // eax
  const idPoolStr *v7; // esi
  unsigned int len; // ebx
  int v9; // eax
  int granularity; // esi
  bool v11; // cc
  int *v12; // eax
  idStr *v13; // edi
  idStr *v14; // ebx
  const void *v15; // esi
  int num; // edi
  int size; // eax
  int v18; // esi
  idStr *v19; // eax
  char *v20; // esi
  int *v21; // eax
  idStr *v22; // edi
  idStr *v23; // ebx
  char *data; // esi
  idStr *v25; // ebx
  int v26; // esi
  idUserInterfaceLocal *gui; // esi
  idDict *v28; // eax
  bool v29; // zf
  int v30; // esi
  rvPair<int,idVec4> *v31; // eax
  rvPair<int,idVec4> *v32; // edi
  int v33; // ecx
  int *v34; // eax
  rvPair<int,idVec4> *v35; // edx
  int v36; // edi
  int v37; // eax
  int v38; // esi
  rvPair<int,idVec4> *v39; // ebx
  rvPair<int,idVec4> *v40; // eax
  rvPair<int,idVec4> *v41; // edi
  int v42; // ecx
  int v43; // eax
  rvPair<int,idVec4> *v44; // esi
  rvPair<int,idVec4> *v45; // edx
  float x; // ecx
  float y; // eax
  float z; // ecx
  float w; // eax
  const char *v50; // esi
  idDict *v51; // eax
  const idKeyValue *v52; // eax
  const char *v53; // eax
  int v54; // eax
  int i; // eax
  int v56; // edi
  int v57; // eax
  int v58; // ecx
  bool *v59; // esi
  int j; // eax
  int v61; // eax
  int k; // eax
  int v63; // edi
  int v64; // eax
  int v65; // ecx
  bool *v66; // esi
  int m; // eax
  idUserInterfaceLocal_vtbl *v68; // esi
  char *v69; // eax
  int v70; // esi
  double MaxCharHeight; // st7
  const char *v72; // esi
  idDict *v73; // eax
  const idKeyValue *v74; // eax
  const char *v75; // eax
  int v76; // eax
  idSliderWindow *scroller; // ecx
  int v78; // eax
  int v79; // edx
  idSliderWindow *v80; // ecx
  int v81; // edx
  const char *v82; // [esp+0h] [ebp-A0h]
  int _high; // [esp+8h] [ebp-98h]
  float _higha; // [esp+8h] [ebp-98h]
  int value; // [esp+1Ch] [ebp-84h]
  float valuea; // [esp+1Ch] [ebp-84h]
  unsigned int *v87; // [esp+20h] [ebp-80h]
  int v88; // [esp+20h] [ebp-80h]
  char *ptr; // [esp+24h] [ebp-7Ch]
  idStr *ptra; // [esp+24h] [ebp-7Ch]
  unsigned int vert; // [esp+28h] [ebp-78h]
  int verta; // [esp+28h] [ebp-78h]
  int vertb; // [esp+28h] [ebp-78h]
  float vertc; // [esp+28h] [ebp-78h]
  int fit; // [esp+2Ch] [ebp-74h]
  int fita; // [esp+2Ch] [ebp-74h]
  idVec4 highlight; // [esp+30h] [ebp-70h] BYREF
  idVec4 v98; // [esp+44h] [ebp-5Ch]
  idStr str; // [esp+54h] [ebp-4Ch] BYREF
  idStr strName; // [esp+74h] [ebp-2Ch] BYREF
  int v101; // [esp+9Ch] [ebp-4h]

  str.len = 0;
  str.alloced = 20;
  str.data = str.baseBuffer;
  str.baseBuffer[0] = 0;
  v101 = 0;
  strName.len = 0;
  strName.alloced = 20;
  strName.data = strName.baseBuffer;
  strName.baseBuffer[0] = 0;
  list = this->listItems.list;
  LOBYTE(v101) = 1;
  if ( list )
  {
    v3 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v3);
  }
  this->listItems.list = 0;
  this->listItems.num = 0;
  this->listItems.size = 0;
  if ( this->listHighlights.list )
    Memory::Free(this->listHighlights.list);
  this->listHighlights.list = 0;
  this->listHighlights.num = 0;
  this->listHighlights.size = 0;
  if ( this->greyedLines.list )
    Memory::Free(this->greyedLines.list);
  this->greyedLines.list = 0;
  this->greyedLines.num = 0;
  this->greyedLines.size = 0;
  value = 0;
  while ( 1 )
  {
    v4 = va("%s_item_%i", this->listName.data, value);
    v5 = (idDict *)this->gui->State(this->gui);
    Key = idDict::FindKey(v5, v4);
    if ( !Key )
      break;
    v7 = Key->value;
    len = v7->len;
    v9 = v7->len + 1;
    if ( v9 > str.alloced )
      idStr::ReAllocate(&str, v9, 0);
    qmemcpy(str.data, v7->data, len);
    str.data[len] = 0;
    str.len = len;
    if ( len )
    {
      if ( !this->listItems.list )
      {
        granularity = this->listItems.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->listItems.size )
          {
            v11 = granularity < this->listItems.num;
            this->listItems.size = granularity;
            if ( v11 )
              this->listItems.num = granularity;
            v12 = (int *)Memory::Allocate(32 * granularity + 4);
            LOBYTE(v101) = 2;
            if ( v12 )
            {
              v13 = (idStr *)(v12 + 1);
              *v12 = granularity;
              `eh vector constructor iterator'(
                v12 + 1,
                0x20u,
                granularity,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            }
            else
            {
              v13 = 0;
            }
            v11 = this->listItems.num <= 0;
            LOBYTE(v101) = 1;
            this->listItems.list = v13;
            ptr = 0;
            if ( !v11 )
            {
              v87 = 0;
              do
              {
                v14 = (idStr *)((char *)v87 + (unsigned int)this->listItems.list);
                vert = *v87;
                if ( (signed int)(*v87 + 1) > v14->alloced )
                  idStr::ReAllocate(v14, vert + 1, 0);
                v15 = (const void *)v87[1];
                v87 += 8;
                qmemcpy(v14->data, v15, vert);
                v14->data[vert] = 0;
                v14->len = vert;
                ++ptr;
              }
              while ( (int)ptr < this->listItems.num );
            }
          }
        }
        else
        {
          this->listItems.list = 0;
          this->listItems.num = 0;
          this->listItems.size = 0;
        }
      }
      num = this->listItems.num;
      size = this->listItems.size;
      if ( num == size )
      {
        if ( !this->listItems.granularity )
          this->listItems.granularity = 16;
        v18 = size + this->listItems.granularity - (size + this->listItems.granularity) % this->listItems.granularity;
        if ( v18 > 0 )
        {
          if ( v18 != this->listItems.size )
          {
            ptra = this->listItems.list;
            this->listItems.size = v18;
            if ( v18 < num )
              this->listItems.num = v18;
            v21 = (int *)Memory::Allocate(32 * v18 + 4);
            LOBYTE(v101) = 3;
            if ( v21 )
            {
              v22 = (idStr *)(v21 + 1);
              *v21 = v18;
              `eh vector constructor iterator'(
                v21 + 1,
                0x20u,
                v18,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            }
            else
            {
              v22 = 0;
            }
            v11 = this->listItems.num <= 0;
            LOBYTE(v101) = 1;
            this->listItems.list = v22;
            verta = 0;
            if ( !v11 )
            {
              v88 = 0;
              do
              {
                v23 = &this->listItems.list[v88];
                fit = ptra[v88].len;
                if ( fit + 1 > v23->alloced )
                  idStr::ReAllocate(v23, fit + 1, 0);
                data = ptra[v88++].data;
                qmemcpy(v23->data, data, fit);
                v23->data[fit] = 0;
                v23->len = fit;
                ++verta;
              }
              while ( verta < this->listItems.num );
            }
            if ( ptra )
            {
              `eh vector destructor iterator'(
                ptra,
                0x20u,
                *(_DWORD *)&ptra[-1].baseBuffer[16],
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(&ptra[-1].baseBuffer[16]);
            }
          }
        }
        else
        {
          v19 = this->listItems.list;
          if ( v19 )
          {
            v20 = &v19[-1].baseBuffer[16];
            `eh vector destructor iterator'(
              v19,
              0x20u,
              *(_DWORD *)&v19[-1].baseBuffer[16],
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(v20);
          }
          this->listItems.list = 0;
          this->listItems.num = 0;
          this->listItems.size = 0;
        }
      }
      v25 = &this->listItems.list[this->listItems.num];
      v26 = str.len;
      fita = str.len;
      if ( str.len + 1 > v25->alloced )
        idStr::ReAllocate(v25, str.len + 1, 0);
      qmemcpy(v25->data, str.data, v26);
      v25->data[fita] = 0;
      v25->len = fita;
      ++this->listItems.num;
      gui = this->gui;
      v82 = va("%s_item_%i_highlight", this->listName.data, value);
      v28 = (idDict *)gui->State(gui);
      if ( idDict::GetVec4(v28, v82, &entityFilter, &highlight) )
      {
        v29 = this->listHighlights.list == 0;
        v98 = highlight;
        if ( v29 )
        {
          v30 = this->listHighlights.granularity;
          if ( v30 > 0 )
          {
            if ( v30 != this->listHighlights.size )
            {
              v11 = v30 < this->listHighlights.num;
              this->listHighlights.size = v30;
              if ( v11 )
                this->listHighlights.num = v30;
              v31 = (rvPair<int,idVec4> *)Memory::Allocate(20 * v30);
              v32 = v31;
              LOBYTE(v101) = 4;
              if ( v31 )
                `vector constructor iterator'(v31, 0x14u, v30, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
              else
                v32 = 0;
              v33 = 0;
              v11 = this->listHighlights.num <= 0;
              LOBYTE(v101) = 1;
              this->listHighlights.list = v32;
              if ( !v11 )
              {
                v34 = 0;
                do
                {
                  v35 = (rvPair<int,idVec4> *)((char *)v34 + (unsigned int)this->listHighlights.list);
                  v35->first = *v34;
                  LODWORD(v35->second.x) = v34[1];
                  LODWORD(v35->second.y) = v34[2];
                  LODWORD(v35->second.z) = v34[3];
                  ++v33;
                  LODWORD(v35->second.w) = v34[4];
                  v34 += 5;
                }
                while ( v33 < this->listHighlights.num );
              }
            }
          }
          else
          {
            this->listHighlights.list = 0;
            this->listHighlights.num = 0;
            this->listHighlights.size = 0;
          }
        }
        v36 = this->listHighlights.num;
        v37 = this->listHighlights.size;
        if ( v36 == v37 )
        {
          if ( !this->listHighlights.granularity )
            this->listHighlights.granularity = 16;
          v38 = v37
              + this->listHighlights.granularity
              - (v37 + this->listHighlights.granularity) % this->listHighlights.granularity;
          if ( v38 > 0 )
          {
            if ( v38 != this->listHighlights.size )
            {
              v39 = this->listHighlights.list;
              this->listHighlights.size = v38;
              if ( v38 < v36 )
                this->listHighlights.num = v38;
              v40 = (rvPair<int,idVec4> *)Memory::Allocate(20 * v38);
              v41 = v40;
              LOBYTE(v101) = 5;
              if ( v40 )
                `vector constructor iterator'(v40, 0x14u, v38, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
              else
                v41 = 0;
              v42 = 0;
              v11 = this->listHighlights.num <= 0;
              LOBYTE(v101) = 1;
              this->listHighlights.list = v41;
              if ( !v11 )
              {
                v43 = 0;
                do
                {
                  v44 = &this->listHighlights.list[v43];
                  v44->first = v39[v43].first;
                  v44->second.x = v39[v43].second.x;
                  v44->second.y = v39[v43].second.y;
                  v44->second.z = v39[v43].second.z;
                  ++v42;
                  v44->second.w = v39[v43++].second.w;
                }
                while ( v42 < this->listHighlights.num );
              }
              if ( v39 )
                Memory::Free(v39);
            }
          }
          else
          {
            if ( this->listHighlights.list )
              Memory::Free(this->listHighlights.list);
            this->listHighlights.list = 0;
            this->listHighlights.num = 0;
            this->listHighlights.size = 0;
          }
        }
        v45 = &this->listHighlights.list[this->listHighlights.num];
        x = v98.x;
        v45->first = value;
        y = v98.y;
        v45->second.x = x;
        z = v98.z;
        v45->second.y = y;
        w = v98.w;
        v45->second.z = z;
        v45->second.w = w;
        ++this->listHighlights.num;
      }
      v50 = va("%s_item_%i_greyed", this->listName.data, value);
      v51 = (idDict *)this->gui->State(this->gui);
      v52 = idDict::FindKey(v51, v50);
      if ( v52 )
        v53 = v52->value->data;
      else
        v53 = "0";
      if ( atoi(v53) )
      {
        if ( !this->greyedLines.list )
        {
          v54 = this->greyedLines.granularity;
          if ( v54 > 0 )
          {
            if ( v54 != this->greyedLines.size )
            {
              v11 = v54 < this->greyedLines.num;
              this->greyedLines.size = v54;
              if ( v11 )
                this->greyedLines.num = v54;
              this->greyedLines.list = (bool *)Memory::Allocate(v54);
              for ( i = 0; i < this->greyedLines.num; ++i )
                this->greyedLines.list[i] = *(_BYTE *)i;
            }
          }
          else
          {
            this->greyedLines.list = 0;
            this->greyedLines.num = 0;
            this->greyedLines.size = 0;
          }
        }
        v56 = this->greyedLines.num;
        v57 = this->greyedLines.size;
        if ( v56 == v57 )
        {
          if ( !this->greyedLines.granularity )
            this->greyedLines.granularity = 16;
          v58 = v57
              + this->greyedLines.granularity
              - (v57 + this->greyedLines.granularity) % this->greyedLines.granularity;
          if ( v58 > 0 )
          {
            if ( v58 != this->greyedLines.size )
            {
              v59 = this->greyedLines.list;
              this->greyedLines.size = v58;
              if ( v58 < v56 )
                this->greyedLines.num = v58;
              this->greyedLines.list = (bool *)Memory::Allocate(v58);
              for ( j = 0; j < this->greyedLines.num; ++j )
                this->greyedLines.list[j] = v59[j];
              if ( v59 )
                Memory::Free(v59);
            }
          }
          else
          {
            if ( this->greyedLines.list )
              Memory::Free(this->greyedLines.list);
            this->greyedLines.list = 0;
            this->greyedLines.num = 0;
            this->greyedLines.size = 0;
          }
        }
        this->greyedLines.list[this->greyedLines.num] = 1;
      }
      else
      {
        if ( !this->greyedLines.list )
        {
          v61 = this->greyedLines.granularity;
          if ( v61 > 0 )
          {
            if ( v61 != this->greyedLines.size )
            {
              v11 = v61 < this->greyedLines.num;
              this->greyedLines.size = v61;
              if ( v11 )
                this->greyedLines.num = v61;
              this->greyedLines.list = (bool *)Memory::Allocate(v61);
              for ( k = 0; k < this->greyedLines.num; ++k )
                this->greyedLines.list[k] = *(_BYTE *)k;
            }
          }
          else
          {
            this->greyedLines.list = 0;
            this->greyedLines.num = 0;
            this->greyedLines.size = 0;
          }
        }
        v63 = this->greyedLines.num;
        v64 = this->greyedLines.size;
        if ( v63 == v64 )
        {
          if ( !this->greyedLines.granularity )
            this->greyedLines.granularity = 16;
          v65 = v64
              + this->greyedLines.granularity
              - (v64 + this->greyedLines.granularity) % this->greyedLines.granularity;
          if ( v65 > 0 )
          {
            if ( v65 != this->greyedLines.size )
            {
              v66 = this->greyedLines.list;
              this->greyedLines.size = v65;
              if ( v65 < v63 )
                this->greyedLines.num = v65;
              this->greyedLines.list = (bool *)Memory::Allocate(v65);
              for ( m = 0; m < this->greyedLines.num; ++m )
                this->greyedLines.list[m] = v66[m];
              if ( v66 )
                Memory::Free(v66);
            }
          }
          else
          {
            if ( this->greyedLines.list )
              Memory::Free(this->greyedLines.list);
            this->greyedLines.list = 0;
            this->greyedLines.num = 0;
            this->greyedLines.size = 0;
          }
        }
        this->greyedLines.list[this->greyedLines.num] = 0;
      }
      ++this->greyedLines.num;
    }
    if ( ++value >= 1024 )
      goto LABEL_134;
  }
  idStr::operator=(&str, (char *)&entityFilter);
LABEL_134:
  v68 = this->gui->idWindow::__vftable;
  _high = this->listItems.num;
  v69 = va("%s_num", this->listName.data);
  v68->SetStateInt(this->gui, v69, _high);
  v70 = this->itemHeight.data;
  MaxCharHeight = idWindow::GetMaxCharHeight(this);
  vertb = v70;
  if ( v70 <= (int)MaxCharHeight )
    vertb = (int)MaxCharHeight;
  vertc = (float)vertb;
  if ( vertc != 0.0 )
  {
    v72 = va("%s_sel_0", this->listName.data);
    v73 = (idDict *)this->gui->State(this->gui);
    v74 = idDict::FindKey(v73, v72);
    if ( v74 )
      v75 = v74->value->data;
    else
      v75 = "0";
    v76 = atoi(v75);
    idListWindow::SetCurrentSel(this, v76);
    scroller = this->scroller;
    if ( scroller )
    {
      v78 = this->listItems.num;
      v79 = (int)(this->textRect.h / vertc);
      if ( v78 >= v79 )
      {
        _higha = (float)(v78 - v79);
        idSliderWindow::SetRange(scroller, 0.0, _higha, 1.0);
      }
      else
      {
        idSliderWindow::SetRange(scroller, 0.0, 0.0, 1.0);
      }
      v80 = this->scroller;
      valuea = v80->value.data;
      v81 = this->listItems.num;
      if ( (double)(v81 - 1) < valuea )
        valuea = (float)(v81 - 1);
      if ( valuea < 0.0 )
        valuea = 0.0;
      idSliderWindow::SetValue(v80, valuea);
      this->top = (int)valuea;
    }
    else
    {
      this->top = 0;
    }
    this->typedTime = 0;
    idStr::operator=(&this->typed, (char *)&entityFilter);
  }
  LOBYTE(v101) = 0;
  idStr::FreeData(&strName);
  v101 = -1;
  idStr::FreeData(&str);
}

// FUNC: public: virtual void __thiscall idListWindow::StateChanged(bool)
// attributes: thunk
void __thiscall idListWindow::StateChanged(idListWindow *this, bool redraw)
{
  idListWindow::UpdateList(this);
}

// FUNC: public: __thiscall idListWindow::idListWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idListWindow::idListWindow(idListWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idHashTable<idMaterial const *>::hashnode_s **v4; // eax
  unsigned int v5; // edx
  int v6; // eax

  idWindow::idWindow(this, d, g);
  this->__vftable = (idListWindow_vtbl *)&idListWindow::`vftable';
  this->tabInfo.granularity = 16;
  this->tabInfo.list = 0;
  this->tabInfo.num = 0;
  this->tabInfo.size = 0;
  this->tabStopStr.len = 0;
  this->tabStopStr.alloced = 20;
  this->tabStopStr.data = this->tabStopStr.baseBuffer;
  this->tabStopStr.baseBuffer[0] = 0;
  this->tabAlignStr.len = 0;
  this->tabAlignStr.alloced = 20;
  this->tabAlignStr.data = this->tabAlignStr.baseBuffer;
  this->tabAlignStr.baseBuffer[0] = 0;
  this->tabVAlignStr.len = 0;
  this->tabVAlignStr.alloced = 20;
  this->tabVAlignStr.data = this->tabVAlignStr.baseBuffer;
  this->tabVAlignStr.baseBuffer[0] = 0;
  this->tabTypeStr.len = 0;
  this->tabTypeStr.alloced = 20;
  this->tabTypeStr.data = this->tabTypeStr.baseBuffer;
  this->tabTypeStr.baseBuffer[0] = 0;
  this->tabIconSizeStr.len = 0;
  this->tabIconSizeStr.alloced = 20;
  this->tabIconSizeStr.data = this->tabIconSizeStr.baseBuffer;
  this->tabIconSizeStr.baseBuffer[0] = 0;
  this->tabIconVOffsetStr.len = 0;
  this->tabIconVOffsetStr.alloced = 20;
  this->tabIconVOffsetStr.data = this->tabIconVOffsetStr.baseBuffer;
  this->tabIconVOffsetStr.baseBuffer[0] = 0;
  this->tabTextScalesStr.len = 0;
  this->tabTextScalesStr.alloced = 20;
  this->tabTextScalesStr.data = this->tabTextScalesStr.baseBuffer;
  this->tabTextScalesStr.baseBuffer[0] = 0;
  this->iconMaterials.tablesize = 256;
  v4 = (idHashTable<idMaterial const *>::hashnode_s **)Memory::Allocate(0x400u);
  v5 = 4 * this->iconMaterials.tablesize;
  this->iconMaterials.heads = v4;
  memset(v4, 0, v5);
  v6 = this->iconMaterials.tablesize - 1;
  this->iconMaterials.numentries = 0;
  this->iconMaterials.tablesizemask = v6;
  this->listItems.granularity = 16;
  this->listItems.list = 0;
  this->listItems.num = 0;
  this->listItems.size = 0;
  this->currentSel.granularity = 16;
  this->currentSel.list = 0;
  this->currentSel.num = 0;
  this->currentSel.size = 0;
  this->listName.len = 0;
  this->listName.alloced = 20;
  this->listName.data = this->listName.baseBuffer;
  this->listName.baseBuffer[0] = 0;
  this->typed.len = 0;
  this->typed.alloced = 20;
  this->typed.data = this->typed.baseBuffer;
  this->typed.baseBuffer[0] = 0;
  this->listHighlights.granularity = 16;
  this->listHighlights.list = 0;
  this->listHighlights.num = 0;
  this->listHighlights.size = 0;
  this->itemHeight.guiDict = 0;
  this->itemHeight.name = 0;
  this->itemHeight.eval = 1;
  this->itemHeight.__vftable = (idWinInt_vtbl *)&idWinInt::`vftable';
  this->backgroundFocus.guiDict = 0;
  this->backgroundFocus.name = 0;
  this->backgroundFocus.eval = 1;
  this->backgroundFocus.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->backgroundFocus.data.len = 0;
  this->backgroundFocus.data.alloced = 20;
  this->backgroundFocus.data.data = this->backgroundFocus.data.baseBuffer;
  this->backgroundFocus.data.baseBuffer[0] = 0;
  this->backgroundLine.guiDict = 0;
  this->backgroundLine.name = 0;
  this->backgroundLine.eval = 1;
  this->backgroundLine.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->backgroundLine.data.len = 0;
  this->backgroundLine.data.alloced = 20;
  this->backgroundLine.data.data = this->backgroundLine.data.baseBuffer;
  this->backgroundLine.data.baseBuffer[0] = 0;
  this->backgroundHover.guiDict = 0;
  this->backgroundHover.name = 0;
  this->backgroundHover.eval = 1;
  this->backgroundHover.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->backgroundHover.data.len = 0;
  this->backgroundHover.data.alloced = 20;
  this->backgroundHover.data.data = this->backgroundHover.data.baseBuffer;
  this->backgroundHover.data.baseBuffer[0] = 0;
  this->backgroundGreyed.len = 0;
  this->backgroundGreyed.alloced = 20;
  this->backgroundGreyed.data = this->backgroundGreyed.baseBuffer;
  this->backgroundGreyed.baseBuffer[0] = 0;
  this->greyedLines.granularity = 16;
  this->greyedLines.list = 0;
  this->greyedLines.num = 0;
  this->greyedLines.size = 0;
  this->dc = d;
  this->gui = g;
  idListWindow::CommonInit(this);
}

// FUNC: public: virtual void __thiscall idListWindow::Activate(bool,class idStr &)
void __thiscall idListWindow::Activate(idListWindow *this, bool activate, idStr *act)
{
  idWindow::Activate(this, activate, act);
  if ( activate )
    idListWindow::UpdateList(this);
}
