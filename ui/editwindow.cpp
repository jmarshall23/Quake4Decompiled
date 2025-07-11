
// FUNC: public: virtual class idWinVar * __thiscall idEditWindow::GetWinVarByName(char const *,bool,struct drawWin_t * *)
idWinStr *__thiscall idEditWindow::GetWinVarByName(
        idEditWindow *this,
        const char *_name,
        bool fixup,
        drawWin_t **owner)
{
  if ( !idStr::Icmp(_name, "cvar") )
    return &this->cvarStr;
  if ( !idStr::Icmp(_name, "password") )
    return (idWinStr *)&this->password;
  if ( !idStr::Icmp(_name, "liveUpdate") )
    return (idWinStr *)&this->liveUpdate;
  if ( idStr::Icmp(_name, "cvarGroup") )
    return (idWinStr *)idWindow::GetWinVarByName(this, _name, fixup, owner);
  return &this->cvarGroup;
}

// FUNC: public: virtual void __thiscall idEditWindow::LoseFocus(void)
void __thiscall idEditWindow::LoseFocus(idEditWindow *this)
{
  this->cursorPos = -1;
}

// FUNC: private: virtual bool __thiscall idEditWindow::ParseInternalVar(char const *,class idParser *)
bool __thiscall idEditWindow::ParseInternalVar(idEditWindow *this, const char *_name, idParser *src)
{
  if ( idStr::Icmp(_name, "maxchars") )
  {
    if ( idStr::Icmp(_name, "numeric") )
    {
      if ( idStr::Icmp(_name, "wrap") )
      {
        if ( idStr::Icmp(_name, "readonly") )
        {
          if ( idStr::Icmp(_name, "forceScroll") )
          {
            if ( idStr::Icmp(_name, "source") )
            {
              if ( idStr::Icmp(_name, "password") )
              {
                if ( idStr::Icmp(_name, "cvarMax") )
                {
                  return idWindow::ParseInternalVar(this, _name, src);
                }
                else
                {
                  this->cvarMax = idParser::ParseInt(src);
                  return 1;
                }
              }
              else
              {
                LOBYTE(src) = idParser::ParseBool(src);
                idWinBool::operator=(&this->password, (bool *)&src);
                return 1;
              }
            }
            else
            {
              idWindow::ParseString(this, src, &this->sourceFile);
              return 1;
            }
          }
          else
          {
            this->forceScroll = idParser::ParseBool(src);
            return 1;
          }
        }
        else
        {
          this->readonly = idParser::ParseBool(src);
          return 1;
        }
      }
      else
      {
        this->wrap = idParser::ParseBool(src);
        return 1;
      }
    }
    else
    {
      this->numeric = idParser::ParseBool(src);
      return 1;
    }
  }
  else
  {
    this->maxChars = idParser::ParseInt(src);
    return 1;
  }
}

// FUNC: private: void __thiscall idEditWindow::CommonInit(void)
void __thiscall idEditWindow::CommonInit(idEditWindow *this)
{
  idSliderWindow *v2; // eax
  idSliderWindow *v3; // eax
  bool other; // [esp+Bh] [ebp-11h] BYREF
  idSliderWindow *v5; // [esp+Ch] [ebp-10h]
  int v6; // [esp+18h] [ebp-4h]

  this->maxChars = 128;
  this->numeric = 0;
  this->paintOffset = 0;
  this->cursorPos = 0;
  this->cursorLine = 0;
  this->cvarMax = 0;
  this->wrap = 0;
  idStr::operator=(&this->sourceFile, (char *)&entityFilter);
  this->scroller = 0;
  this->sizeBias = 0.0;
  this->lastTextLength = 0;
  this->forceScroll = 0;
  other = 0;
  idWinBool::operator=(&this->password, &other);
  this->cvar = 0;
  other = 1;
  idWinBool::operator=(&this->liveUpdate, &other);
  this->readonly = 0;
  v2 = (idSliderWindow *)Memory::Allocate(0x4FCu);
  v5 = v2;
  v6 = 0;
  if ( v2 )
  {
    idSliderWindow::idSliderWindow(v2, this->dc, this->gui);
    this->scroller = v3;
  }
  else
  {
    this->scroller = 0;
  }
}

// FUNC: private: void __thiscall idEditWindow::InitScroller(bool)
void __thiscall idEditWindow::InitScroller(idEditWindow *this, bool horizontal)
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

// FUNC: private: void __thiscall idEditWindow::EnsureCursorVisible(void)
void __thiscall idEditWindow::EnsureCursorVisible(idEditWindow *this)
{
  int v2; // ebx
  int MaxCharWidth; // edx
  int v4; // ebx
  int v5; // edi
  char *name; // eax
  const char *v7; // eax
  const idKeyValue *Key; // eax
  char *data; // eax
  int IsEscape; // eax
  idList<int> *p_breaks; // edi
  unsigned int flags; // eax
  int cursorPos; // ecx
  double MaxCharHeight; // st7
  int v15; // edx
  int v16; // eax
  bool v17; // cc
  int v18; // edx
  int *v19; // ecx
  double cursorLine; // st7
  idRectangle v21; // [esp-24h] [ebp-58h]
  idRectangle v22; // [esp-24h] [ebp-58h]
  float v23; // [esp+0h] [ebp-34h]
  float _value; // [esp+4h] [ebp-30h]
  float _valuea; // [esp+4h] [ebp-30h]
  float fit; // [esp+18h] [ebp-1Ch]
  int cursorXa; // [esp+1Ch] [ebp-18h]
  int cursorX; // [esp+1Ch] [ebp-18h]
  int maxWidth; // [esp+20h] [ebp-14h]
  __int64 rect_8; // [esp+2Ch] [ebp-8h]
  unsigned int rect_8a; // [esp+2Ch] [ebp-8h]

  if ( this->readonly )
  {
    this->cursorPos = -1;
  }
  else if ( this->maxChars == 1 )
  {
    this->cursorPos = 0;
  }
  v2 = 0;
  if ( this->dc )
  {
    idWindow::SetFont(this);
    if ( this->wrap )
    {
      p_breaks = &this->breaks;
      if ( this->breaks.list )
        Memory::Free(this->breaks.list);
      this->breaks.list = 0;
      p_breaks->num = 0;
      this->breaks.size = 0;
      *(float *)&rect_8 = this->textRect.w;
      if ( this->wrap && this->scroller->high > 0.0 )
        *(float *)&rect_8 = *(float *)&rect_8 - this->sizeBias;
      flags = this->flags;
      if ( (flags & 0x20) != 0 )
        cursorPos = this->cursorPos;
      else
        cursorPos = -1;
      *(_QWORD *)&v21.x = *(_QWORD *)&this->textRect.x;
      HIDWORD(rect_8) = LODWORD(this->textRect.h);
      *(_QWORD *)&v21.w = rect_8;
      idDeviceContext::DrawTextA(
        this->dc,
        this->text.data.data,
        this->textScale.data,
        this->textAlign,
        this->textStyle,
        colorWhite,
        v21,
        1,
        cursorPos,
        1,
        &this->breaks,
        0,
        0,
        (flags & 0x20000000) != 0);
      MaxCharHeight = idWindow::GetMaxCharHeight(this);
      if ( MaxCharHeight <= 0.0 )
        MaxCharHeight = 1.0;
      fit = this->textRect.h / (MaxCharHeight * 1.25);
      if ( (double)p_breaks->num <= fit )
      {
        idSliderWindow::SetRange(this->scroller, 0.0, 0.0, 1.0);
      }
      else
      {
        if ( this->scroller->high == 0.0 )
        {
          if ( this->breaks.list )
            Memory::Free(this->breaks.list);
          this->breaks.list = 0;
          p_breaks->num = 0;
          this->breaks.size = 0;
          if ( (this->flags & 0x20) != 0 )
            v15 = this->cursorPos;
          else
            v15 = -1;
          *(_QWORD *)&v22.x = *(_QWORD *)&this->textRect.x;
          *(float *)&rect_8a = this->textRect.w - this->sizeBias;
          *(_QWORD *)&v22.w = __PAIR64__(LODWORD(this->textRect.h), rect_8a);
          idDeviceContext::DrawTextA(
            this->dc,
            this->text.data.data,
            this->textScale.data,
            this->textAlign,
            this->textStyle,
            colorWhite,
            v22,
            1,
            v15,
            1,
            &this->breaks,
            0,
            0,
            0);
        }
        v23 = (double)p_breaks->num - fit;
        idSliderWindow::SetRange(this->scroller, 0.0, v23, 1.0);
      }
      if ( this->forceScroll )
      {
        _value = (double)p_breaks->num - fit;
        idSliderWindow::SetValue(this->scroller, _value);
        return;
      }
      if ( !this->readonly )
      {
        v16 = 1;
        v17 = p_breaks->num <= 1;
        this->cursorLine = 0;
        if ( !v17 )
        {
          v18 = this->cursorPos;
          v19 = this->breaks.list + 1;
          do
          {
            if ( v18 < *v19 )
              break;
            this->cursorLine = v16++;
            ++v19;
          }
          while ( v16 < p_breaks->num );
        }
        cursorX = (int)this->scroller->value.data;
        cursorLine = (double)this->cursorLine;
        if ( this->cursorLine >= cursorX )
        {
          if ( cursorLine < (double)cursorX + fit )
            return;
          cursorLine = cursorLine - fit + 1.0;
        }
        _valuea = cursorLine;
        idSliderWindow::SetValue(this->scroller, _valuea);
      }
    }
    else
    {
      if ( this->password.data )
      {
        v2 = this->cursorPos * idDeviceContext::CharWidth(this->dc, 0x2Au, this->textScale.data, 0);
      }
      else
      {
        v5 = 0;
        while ( 1 )
        {
          if ( this->text.guiDict )
          {
            name = this->text.name;
            if ( name )
            {
              if ( *name )
              {
                v7 = idWinVar::GetName(&this->text);
                Key = idDict::FindKey(this->text.guiDict, v7);
                if ( Key )
                  data = Key->value->data;
                else
                  data = (char *)&entityFilter;
                idStr::operator=(&this->text.data, data);
              }
            }
          }
          if ( v5 >= this->text.data.len || v5 >= this->cursorPos )
            break;
          IsEscape = idStr::IsEscape(&this->text.data.data[v5], 0);
          if ( IsEscape )
            v5 += IsEscape;
          else
            v2 += idDeviceContext::CharWidth(this->dc, this->text.data.data[v5++], this->textScale.data, 0);
        }
      }
      cursorXa = v2;
      MaxCharWidth = (int)idWindow::GetMaxCharWidth(this);
      v4 = v2 - MaxCharWidth;
      maxWidth = (int)((double)cursorXa - this->textRect.w + (double)MaxCharWidth);
      if ( this->paintOffset > v4 )
        this->paintOffset = v4 - 6 * MaxCharWidth;
      if ( this->paintOffset < maxWidth )
        this->paintOffset = maxWidth;
      if ( this->paintOffset < 0 )
        this->paintOffset = 0;
      idSliderWindow::SetRange(this->scroller, 0.0, 0.0, 1.0);
    }
  }
}

// FUNC: private: void __thiscall idEditWindow::InitCvar(void)
void __thiscall idEditWindow::InitCvar(idEditWindow *this)
{
  char *data; // eax
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  idCVar *v6; // eax
  char *v7; // ebx
  idWinStr_vtbl *v8; // eax
  idWinStr *p_cvarStr; // ecx
  char *v10; // edi
  int v11; // esi
  int v12; // eax

  data = this->cvarStr.data.data;
  if ( *data )
  {
    v6 = cvarSystem->Find(cvarSystem, data);
    this->cvar = v6;
    if ( !v6 )
    {
      v7 = this->gui->source.data;
      v8 = this->cvarStr.__vftable;
      p_cvarStr = &this->cvarStr;
      v10 = this->name.data;
      v11 = *(_DWORD *)common.type;
      v12 = (int)v8->c_str(p_cvarStr);
      (*(void (**)(netadrtype_t, const char *, ...))(v11 + 136))(
        common.type,
        "idEditWindow::InitCvar: gui '%s' window '%s' references undefined cvar '%s'",
        v7,
        v10,
        v12);
    }
  }
  else
  {
    name = this->text.name;
    if ( name )
    {
      guiDict = this->text.guiDict;
      if ( guiDict && *name == 42 )
      {
        Key = idDict::FindKey(guiDict, name + 1);
        if ( Key )
          name = Key->value->data;
        else
          name = (char *)&entityFilter;
      }
      if ( !name )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "idEditWindow::InitCvar: gui '%s' window '%s' has an empty cvar string",
          this->gui->source.data,
          this->name.data);
    }
    this->cvar = 0;
  }
}

// FUNC: public: __thiscall idEditWindow::idEditWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idEditWindow::idEditWindow(idEditWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idWindow::idWindow(this, d, g);
  this->__vftable = (idEditWindow_vtbl *)&idEditWindow::`vftable';
  this->sourceFile.len = 0;
  this->sourceFile.alloced = 20;
  this->sourceFile.data = this->sourceFile.baseBuffer;
  this->sourceFile.baseBuffer[0] = 0;
  this->breaks.granularity = 16;
  this->breaks.list = 0;
  this->breaks.num = 0;
  this->breaks.size = 0;
  this->password.guiDict = 0;
  this->password.name = 0;
  this->password.eval = 1;
  this->password.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
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
  idEditWindow::CommonInit(this);
}

// FUNC: public: virtual __thiscall idEditWindow::~idEditWindow(void)
void __thiscall idEditWindow::~idEditWindow(idEditWindow *this)
{
  int *list; // eax
  char *name; // [esp-4h] [ebp-1Ch]
  char *v4; // [esp-4h] [ebp-1Ch]

  this->__vftable = (idEditWindow_vtbl *)&idEditWindow::`vftable';
  idWinStr::~idWinStr(&this->cvarGroup);
  name = this->liveUpdate.name;
  this->liveUpdate.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(name);
  this->liveUpdate.name = 0;
  idWinStr::~idWinStr(&this->cvarStr);
  v4 = this->password.name;
  this->password.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(v4);
  this->password.name = 0;
  list = this->breaks.list;
  if ( list )
    Memory::Free(list);
  this->breaks.list = 0;
  this->breaks.num = 0;
  this->breaks.size = 0;
  idStr::FreeData(&this->sourceFile);
  idWindow::~idWindow(this);
}

// FUNC: public: virtual void __thiscall idEditWindow::GainFocus(void)
void __thiscall idEditWindow::GainFocus(idEditWindow *this)
{
  this->cursorPos = idWinStr::Length(&this->text);
  idEditWindow::EnsureCursorVisible(this);
}

// FUNC: public: virtual void __thiscall idEditWindow::PostParse(void)
void __usercall idEditWindow::PostParse(idEditWindow *this@<ecx>, int a2@<edi>)
{
  char *v3; // ebp
  const char *v4; // eax
  int v5; // edi
  int v6; // eax
  char *data; // edx
  char *v8; // ecx
  char v9; // al
  const idCmdArgs *v10; // [esp+8h] [ebp-34h]
  void *buffer; // [esp+Ch] [ebp-30h] BYREF
  char *v12; // [esp+10h] [ebp-2Ch]
  idStr other; // [esp+14h] [ebp-28h] BYREF
  int retaddr; // [esp+3Ch] [ebp+0h]

  SpawnStub(v10);
  if ( !this->maxChars )
    this->maxChars = 10;
  if ( this->sourceFile.len )
  {
    ((void (__thiscall *)(idFileSystem *, char *, void **, _DWORD, int))fileSystem->ReadFile)(
      fileSystem,
      this->sourceFile.data,
      &buffer,
      0,
      a2);
    v3 = v12;
    other.len = 0;
    other.alloced = 20;
    other.data = other.baseBuffer;
    other.baseBuffer[0] = 0;
    if ( v12 )
    {
      v4 = &v12[strlen(v12) + 1];
      v5 = v4 - (v12 + 1);
      v6 = v4 - v12;
      if ( v6 > 20 )
        idStr::ReAllocate(&other, v6, 1);
      data = other.data;
      v8 = v3;
      do
      {
        v9 = *v8;
        *data++ = *v8++;
      }
      while ( v9 );
      other.len = v5;
    }
    idWinStr::operator=(&this->text, &other);
    retaddr = -1;
    idStr::FreeData(&other);
    fileSystem->FreeFile(fileSystem, v12);
  }
  idEditWindow::InitCvar(this);
  idEditWindow::InitScroller(this, 0);
  idEditWindow::EnsureCursorVisible(this);
  BYTE1(this->flags) |= 8u;
}

// FUNC: private: void __thiscall idEditWindow::UpdateCvar(bool,bool)
void __thiscall idEditWindow::UpdateCvar(idEditWindow *this, bool read, bool force)
{
  idCVar *cvar; // eax
  idCVar *internalVar; // eax
  const char *value; // esi
  unsigned int v7; // eax
  int v8; // edi
  int v9; // eax
  char *data; // edx
  const char *v11; // ecx
  char v12; // al
  int cvarMax; // eax
  idCVar *v14; // edx
  idStr other; // [esp+4h] [ebp-2Ch] BYREF
  int v16; // [esp+2Ch] [ebp-4h]

  if ( force || this->liveUpdate.data )
  {
    cvar = this->cvar;
    if ( cvar )
    {
      internalVar = cvar->internalVar;
      if ( read )
      {
        value = internalVar->value;
        other.len = 0;
        other.alloced = 20;
        other.data = other.baseBuffer;
        other.baseBuffer[0] = 0;
        if ( value )
        {
          v7 = (unsigned int)&value[strlen(value) + 1];
          v8 = v7 - (_DWORD)(value + 1);
          v9 = v7 - (_DWORD)value;
          if ( v9 > 20 )
            idStr::ReAllocate(&other, v9, 1);
          data = other.data;
          v11 = value;
          do
          {
            v12 = *v11;
            *data++ = *v11++;
          }
          while ( v12 );
          other.len = v8;
        }
        v16 = 0;
        idWinStr::operator=(&this->text, &other);
        v16 = -1;
        idStr::FreeData(&other);
      }
      else
      {
        internalVar->InternalSetString(internalVar, this->text.data.data);
        cvarMax = this->cvarMax;
        if ( cvarMax )
        {
          v14 = this->cvar->internalVar;
          if ( v14->integerValue > cvarMax )
            ((void (__stdcall *)(int))v14->InternalSetInteger)(this->cvarMax);
        }
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idEditWindow::RunNamedEvent(char const *)
void __thiscall idEditWindow::RunNamedEvent(idEditWindow *this, char *eventName)
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
        idEditWindow::UpdateCvar(this, 0, 1);
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
      idEditWindow::UpdateCvar(this, 1, 1);
  }
  LOBYTE(v12) = 0;
  idStr::FreeData(&group);
  v12 = -1;
  idStr::FreeData(&event);
}

// FUNC: public: virtual void __thiscall idEditWindow::Draw(int,float,float)
void __thiscall idEditWindow::Draw(idEditWindow *this, int time, float x, float y)
{
  int v5; // edi
  bool v6; // zf
  char *data; // ebx
  int v8; // edi
  int v9; // eax
  char v10; // cl
  char *v11; // edx
  double paintOffset; // st7
  float h; // ebp
  double v14; // st7
  idUserInterfaceLocal *gui; // edi
  int cursorPos; // eax
  idRectangle v17; // [esp-24h] [ebp-90h]
  float v18; // [esp+0h] [ebp-6Ch]
  float v19; // [esp+4h] [ebp-68h]
  int len; // [esp+18h] [ebp-54h]
  float scale; // [esp+1Ch] [ebp-50h]
  __int64 rect; // [esp+20h] [ebp-4Ch]
  float rect_8; // [esp+28h] [ebp-44h]
  float rect_12; // [esp+2Ch] [ebp-40h]
  idVec4 color; // [esp+30h] [ebp-3Ch]
  idStr pass; // [esp+40h] [ebp-2Ch] BYREF
  int v27; // [esp+68h] [ebp-4h]

  color = this->foreColor.data;
  idEditWindow::UpdateCvar(this, 1, 0);
  v5 = idWinStr::Length(&this->text);
  len = v5;
  if ( v5 != this->lastTextLength )
  {
    idSliderWindow::SetValue(this->scroller, 0.0);
    this->cursorPos = v5;
    idEditWindow::EnsureCursorVisible(this);
    this->lastTextLength = v5;
  }
  scale = this->textScale.data;
  pass.len = 0;
  pass.alloced = 20;
  pass.data = pass.baseBuffer;
  pass.baseBuffer[0] = 0;
  v6 = !this->password.data;
  v27 = 0;
  data = this->text.data.data;
  if ( !v6 )
  {
    if ( *data )
    {
      do
      {
        v8 = pass.len + 1;
        if ( pass.len + 2 > pass.alloced )
          idStr::ReAllocate(&pass, pass.len + 2, 1);
        v9 = 0;
        v10 = 42;
        do
        {
          v11 = &pass.data[v9++];
          v11[pass.len] = v10;
          v10 = asc_1029A1CC[v9];
        }
        while ( v10 );
        pass.len = v8;
        ++data;
        pass.data[v8] = 0;
      }
      while ( *data );
      v5 = len;
    }
    data = pass.data;
  }
  if ( this->cursorPos > v5 )
    this->cursorPos = v5;
  paintOffset = (double)this->paintOffset;
  h = this->textRect.h;
  *(float *)&rect = this->textRect.x - paintOffset;
  HIDWORD(rect) = LODWORD(this->textRect.y);
  rect_8 = paintOffset + this->textRect.w;
  if ( this->wrap && this->scroller->high > 0.0 )
  {
    v14 = idWindow::GetMaxCharHeight(this) * 1.25;
    if ( v14 <= 0.0 )
      v14 = 1.0;
    *((float *)&rect + 1) = *((float *)&rect + 1) - this->scroller->value.data * v14;
    rect_8 = rect_8 - this->sizeBias;
    rect_12 = (double)this->breaks.num * v14;
    h = rect_12;
  }
  if ( this->hover
    && !this->noEvents.data
    && (gui = this->gui, v19 = gui->CursorY(gui), v18 = gui->CursorX(gui), idWindow::Contains(this, v18, v19)) )
  {
    color = this->hoverColor.data;
  }
  else
  {
    this->hover = 0;
  }
  if ( (this->flags & 0x20) != 0 )
  {
    color = this->hoverColor.data;
    cursorPos = this->cursorPos;
  }
  else
  {
    cursorPos = -1;
  }
  *(_QWORD *)&v17.x = rect;
  *(_QWORD *)&v17.w = __PAIR64__(LODWORD(h), LODWORD(rect_8));
  idDeviceContext::DrawTextA(
    this->dc,
    data,
    scale,
    0,
    this->textStyle,
    color,
    v17,
    this->wrap,
    cursorPos,
    0,
    0,
    0,
    0,
    (this->flags & 0x20000000) != 0);
  v27 = -1;
  idStr::FreeData(&pass);
}

// FUNC: public: virtual char const * __thiscall idEditWindow::HandleEvent(struct sysEvent_s const *,bool *)
const char *__thiscall idEditWindow::HandleEvent(idEditWindow *this, const sysEvent_s *event, bool *updateVisuals)
{
  const char *result; // eax
  const char *v5; // eax
  int evValue; // ebx
  int v7; // edi
  int maxChars; // eax
  int v9; // ecx
  char *v10; // eax
  int v11; // ebx
  int v12; // eax
  char *v13; // edx
  char *v14; // ecx
  char v15; // al
  int cursorPos; // eax
  char *v17; // eax
  int v18; // edi
  int v19; // eax
  char *data; // edx
  char *v21; // ecx
  char v22; // al
  int v23; // eax
  char *v24; // eax
  int v25; // edi
  int v26; // eax
  char *v27; // edx
  char *v28; // ecx
  char v29; // al
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int cursorLine; // eax
  int v42; // eax
  int v43; // eax
  idSliderWindow *scroller; // ecx
  int v45; // eax
  idSliderWindow *v46; // ecx
  float _value; // [esp+0h] [ebp-64h]
  float _valuea; // [esp+0h] [ebp-64h]
  const char *ret; // [esp+14h] [ebp-50h]
  idStr other; // [esp+18h] [ebp-4Ch] BYREF
  idStr v51; // [esp+38h] [ebp-2Ch] BYREF
  int v52; // [esp+60h] [ebp-4h]

  result = &entityFilter;
  ret = &entityFilter;
  if ( !this->wrap || (result = idWindow::HandleEvent(this, event, updateVisuals), (ret = result) == 0) || !*result )
  {
    if ( event->evType == SE_CHAR || event->evType == SE_KEY )
    {
      v5 = this->text.c_str(&this->text);
      idStr::Copynz(buffer_0, v5, 4096);
      evValue = event->evValue;
      v7 = idWinStr::Length(&this->text);
      if ( event->evType == SE_CHAR )
      {
        if ( event->evValue == 1 )
          return &entityFilter;
        if ( updateVisuals )
          *updateVisuals = 1;
        maxChars = this->maxChars;
        if ( maxChars && v7 > maxChars )
          v7 = this->maxChars;
        if ( evValue != 13 && evValue != 174 || !event->evValue2 )
        {
          if ( evValue != 27 && evValue != 203 )
          {
            if ( !this->readonly )
            {
              if ( evValue == 8 || evValue == 127 )
              {
                cursorPos = this->cursorPos;
                if ( cursorPos > 0 )
                {
                  if ( cursorPos < v7 )
                  {
                    memmove(
                      (unsigned __int8 *)&buffer_0[cursorPos - 1],
                      (unsigned __int8 *)&buffer_0[cursorPos],
                      v7 - cursorPos + 1);
                    --this->cursorPos;
                  }
                  else
                  {
                    *((_BYTE *)&idDeviceContext::colorNone.w + v7 + 3) = 0;
                    this->cursorPos = v7 - 1;
                  }
                  other.data = other.baseBuffer;
                  other.len = 0;
                  other.alloced = 20;
                  other.baseBuffer[0] = 0;
                  v17 = &buffer_0[strlen(buffer_0) + 1];
                  v18 = v17 - &buffer_0[1];
                  v19 = v17 - buffer_0;
                  if ( v19 > 20 )
                    idStr::ReAllocate(&other, v19, 1);
                  data = other.data;
                  v21 = buffer_0;
                  do
                  {
                    v22 = *v21;
                    *data++ = *v21++;
                  }
                  while ( v22 );
                  other.len = v18;
                  v52 = 0;
                  idWinStr::operator=(&this->text, &other);
                  v52 = -1;
                  idStr::FreeData(&other);
                  idEditWindow::UpdateCvar(this, 0, 0);
                  this->RunScript(this, 2);
                }
              }
              else if ( (this->wrap && (evValue == 13 || evValue == 174)
                      || idStr::printableCharacter[(unsigned __int8)evValue])
                     && (!this->numeric || evValue >= 48 && evValue <= 57 || evValue == 46) )
              {
                if ( this->dc->overStrikeMode )
                {
                  if ( maxChars && this->cursorPos >= maxChars )
                    return &entityFilter;
                  goto LABEL_37;
                }
                if ( v7 != 4095 && (!maxChars || v7 < maxChars) )
                {
                  memmove(
                    &byte_11373AB9[this->cursorPos],
                    (unsigned __int8 *)&buffer_0[this->cursorPos],
                    v7 - this->cursorPos + 1);
LABEL_37:
                  v9 = this->cursorPos;
                  other.data = other.baseBuffer;
                  buffer_0[v9] = evValue;
                  other.len = 0;
                  other.alloced = 20;
                  other.baseBuffer[0] = 0;
                  v10 = &buffer_0[strlen(buffer_0) + 1];
                  v11 = v10 - &buffer_0[1];
                  v12 = v10 - buffer_0;
                  if ( v12 > 20 )
                    idStr::ReAllocate(&other, v12, 1);
                  v13 = other.data;
                  v14 = buffer_0;
                  do
                  {
                    v15 = *v14;
                    *v13++ = *v14++;
                  }
                  while ( v15 );
                  other.len = v11;
                  v52 = 1;
                  idWinStr::operator=(&this->text, &other);
                  v52 = -1;
                  idStr::FreeData(&other);
                  idEditWindow::UpdateCvar(this, 0, 0);
                  this->RunScript(this, 2);
                  ++v7;
LABEL_68:
                  v30 = this->cursorPos;
                  if ( v30 < v7 )
                  {
                    v31 = v30 + 1;
LABEL_70:
                    this->cursorPos = v31;
                    goto LABEL_71;
                  }
                  goto LABEL_71;
                }
              }
            }
            return &entityFilter;
          }
LABEL_125:
          this->RunScript(this, 6);
          return this->cmd.data;
        }
LABEL_129:
        this->RunScript(this, 2);
        this->RunScript(this, 10);
        return this->cmd.data;
      }
      if ( event->evType != SE_KEY )
        return ret;
      if ( event->evValue2 )
      {
        if ( updateVisuals )
          *updateVisuals = 1;
        switch ( evValue )
        {
          case 144:
            if ( !this->readonly )
            {
              v23 = this->cursorPos;
              if ( v23 < v7 )
              {
                memmove((unsigned __int8 *)&buffer_0[v23], &byte_11373AB9[v23], v7 - v23);
                v51.data = v51.baseBuffer;
                v51.len = 0;
                v51.alloced = 20;
                v51.baseBuffer[0] = 0;
                v24 = &buffer_0[strlen(buffer_0) + 1];
                v25 = v24 - &buffer_0[1];
                v26 = v24 - buffer_0;
                if ( v26 > 20 )
                  idStr::ReAllocate(&v51, v26, 1);
                v27 = v51.data;
                v28 = buffer_0;
                do
                {
                  v29 = *v28;
                  *v27++ = *v28++;
                }
                while ( v29 );
                v51.len = v25;
                v52 = 2;
                idWinStr::operator=(&this->text, &v51);
                v52 = -1;
                idStr::FreeData(&v51);
                idEditWindow::UpdateCvar(this, 0, 0);
                this->RunScript(this, 2);
              }
            }
            return ret;
          case 136:
            if ( this->cursorPos >= v7 )
              goto LABEL_71;
            if ( idKeyInput::IsDown(141) || idKeyInput::IsDown(2) )
            {
              if ( this->cursorPos < v7 )
              {
                do
                {
                  v32 = this->cursorPos;
                  if ( buffer_0[v32] == 32 )
                    break;
                  v33 = v32 + 1;
                  this->cursorPos = v33;
                }
                while ( v33 < v7 );
                if ( this->cursorPos < v7 )
                {
                  do
                  {
                    v34 = this->cursorPos;
                    if ( buffer_0[v34] != 32 )
                      break;
                    v35 = v34 + 1;
                    this->cursorPos = v35;
                  }
                  while ( v35 < v7 );
                }
              }
              goto LABEL_71;
            }
            goto LABEL_68;
          case 135:
            if ( idKeyInput::IsDown(141) || idKeyInput::IsDown(2) )
            {
              if ( this->cursorPos > 0 )
              {
                do
                {
                  v37 = this->cursorPos;
                  if ( *((_BYTE *)&idDeviceContext::colorNone.w + v37 + 3) != 32 )
                    break;
                  v38 = v37 - 1;
                  this->cursorPos = v38;
                }
                while ( v38 > 0 );
                if ( this->cursorPos > 0 )
                {
                  do
                  {
                    v39 = this->cursorPos;
                    if ( *((_BYTE *)&idDeviceContext::colorNone.w + v39 + 3) == 32 )
                      break;
                    v40 = v39 - 1;
                    this->cursorPos = v40;
                  }
                  while ( v40 > 0 );
                }
              }
              goto LABEL_71;
            }
            v36 = this->cursorPos;
            if ( v36 > 0 )
            {
              v31 = v36 - 1;
              goto LABEL_70;
            }
LABEL_71:
            idEditWindow::EnsureCursorVisible(this);
            return ret;
          case 147:
            if ( idKeyInput::IsDown(141)
              || idKeyInput::IsDown(2)
              || (cursorLine = this->cursorLine, cursorLine <= 0)
              || cursorLine >= this->breaks.num )
            {
              this->cursorPos = 0;
            }
            else
            {
              this->cursorPos = this->breaks.list[cursorLine];
            }
            goto LABEL_71;
          case 148:
            if ( idKeyInput::IsDown(141)
              || idKeyInput::IsDown(2)
              || (v42 = this->cursorLine, v42 < -1)
              || v42 >= this->breaks.num - 1 )
            {
              this->cursorPos = v7;
              goto LABEL_71;
            }
            v31 = this->breaks.list[v42 + 1] - 1;
            goto LABEL_70;
          case 143:
            if ( !this->readonly )
              this->dc->overStrikeMode = !this->dc->overStrikeMode;
            return ret;
          case 134:
            if ( idKeyInput::IsDown(141) || idKeyInput::IsDown(2) )
            {
              scroller = this->scroller;
              _value = scroller->value.data + 1.0;
              idSliderWindow::SetValue(scroller, _value);
            }
            else
            {
              v43 = this->cursorLine;
              if ( v43 < this->breaks.num - 1 )
              {
                this->cursorPos += this->breaks.list[v43 + 1] - this->breaks.list[v43];
                idEditWindow::EnsureCursorVisible(this);
              }
            }
            break;
          case 133:
            if ( idKeyInput::IsDown(141) || idKeyInput::IsDown(2) )
            {
              v46 = this->scroller;
              _valuea = v46->value.data - 1.0;
              idSliderWindow::SetValue(v46, _valuea);
            }
            else
            {
              v45 = this->cursorLine;
              if ( v45 > 0 )
              {
                this->cursorPos += this->breaks.list[v45 - 1] - this->breaks.list[v45];
                idEditWindow::EnsureCursorVisible(this);
              }
            }
            break;
          case 13:
          case 174:
            goto LABEL_129;
        }
        if ( !IsEscapeKey(evValue) )
        {
          if ( evValue == 187 || evValue == 188 )
          {
            this->RunScript(this, 2);
            return this->cmd.data;
          }
          return ret;
        }
        goto LABEL_125;
      }
      if ( evValue == 13 || evValue == 174 )
      {
        this->RunScript(this, 11);
        return this->cmd.data;
      }
      else
      {
        if ( evValue == 9 )
          this->RunScript(this, 12);
        else
          this->RunScript(this, 9);
        return this->cmd.data;
      }
    }
  }
  return result;
}

// FUNC: public: virtual void __thiscall idEditWindow::Activate(bool,class idStr &)
void __thiscall idEditWindow::Activate(idEditWindow *this, bool activate, idStr *act)
{
  idWindow::Activate(this, activate, act);
  if ( activate )
  {
    idEditWindow::UpdateCvar(this, 1, 1);
    idEditWindow::EnsureCursorVisible(this);
  }
}
