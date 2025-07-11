
// FUNC: private: virtual bool __thiscall rvPopupWindow::ParseInternalVar(char const *,class idParser *)
bool __thiscall rvPopupWindow::ParseInternalVar(rvPopupWindow *this, const char *_name, idParser *src)
{
  if ( idStr::Icmp(_name, "choicetype") )
  {
    if ( idStr::Icmp(_name, "currentchoice") )
    {
      if ( idStr::Icmp(_name, "allowempty") )
      {
        return idWindow::ParseInternalVar(this, _name, src);
      }
      else
      {
        this->allowEmptyVal = idParser::ParseBool(src);
        return 1;
      }
    }
    else
    {
      this->currentChoice = idParser::ParseInt(src);
      return 1;
    }
  }
  else
  {
    this->choiceType = idParser::ParseInt(src);
    return 1;
  }
}

// FUNC: public: virtual class idWinVar * __thiscall rvPopupWindow::GetWinVarByName(char const *,bool,struct drawWin_t * *)
idWinStr *__thiscall rvPopupWindow::GetWinVarByName(
        rvPopupWindow *this,
        const char *_name,
        bool fixup,
        drawWin_t **owner)
{
  if ( !idStr::Icmp(_name, "choices") )
    return &this->choicesStr;
  if ( !idStr::Icmp(_name, "values") )
    return &this->choiceVals;
  if ( !idStr::Icmp(_name, "cvar") )
    return &this->cvarName;
  if ( !idStr::Icmp(_name, "gui") )
    return &this->guiStr;
  if ( !idStr::Icmp(_name, "liveUpdate") )
    return (idWinStr *)&this->liveUpdate;
  if ( !idStr::Icmp(_name, "updateGroup") )
    return &this->updateGroup;
  if ( !idStr::Icmp(_name, "text") )
    return &this->title;
  if ( idStr::Icmp(_name, "descriptions") )
    return (idWinStr *)idWindow::GetWinVarByName(this, _name, fixup, owner);
  return &this->descStr;
}

// FUNC: private: void __thiscall rvPopupWindow::UpdateValue(void)
void __thiscall rvPopupWindow::UpdateValue(rvPopupWindow *this)
{
  idWinStr_vtbl *v2; // ebx
  char *v3; // eax
  idStr *list; // edi
  bool other; // [esp+Bh] [ebp-1h] BYREF

  if ( this->choiceType )
  {
    if ( this->values.num )
    {
      list = this->values.list;
    }
    else
    {
      if ( !this->choices.num )
        goto LABEL_8;
      list = this->choices.list;
    }
    this->cvarStr.Set(&this->cvarStr, list[this->currentChoice].data);
    goto LABEL_8;
  }
  v2 = this->cvarStr.__vftable;
  v3 = va("%i", this->currentChoice);
  v2->Set(&this->cvarStr, v3);
LABEL_8:
  this->gui->HandleNamedEvent(this->gui, "popupClose");
  idWindow::SetCapture(this->parent, 0);
  other = 0;
  idWinBool::operator=(&this->visible, &other);
}

// FUNC: private: void __thiscall rvPopupWindow::InitVars(void)
void __thiscall rvPopupWindow::InitVars(rvPopupWindow *this)
{
  idWinStr *p_cvarName; // edi
  idCVar *v3; // eax
  int v4; // ebp
  char *data; // ebx
  char *v6; // esi
  int v7; // eax
  int granularity; // eax
  bool v9; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v13; // ecx
  idWinVar **list; // edi
  int j; // eax
  int v16; // eax
  int k; // eax
  int v18; // ebx
  int v19; // eax
  int v20; // ecx
  idWinVar **v21; // edi
  int m; // eax

  p_cvarName = &this->cvarName;
  if ( idWinStr::Length(&this->cvarName) )
  {
    v3 = cvarSystem->Find(cvarSystem, this->cvarName.data.data);
    this->cvar = v3;
    if ( !v3 )
    {
      v4 = *(_DWORD *)common.type;
      data = this->name.data;
      v6 = this->gui->source.data;
      v7 = (int)p_cvarName->c_str(p_cvarName);
      (*(void (**)(netadrtype_t, const char *, ...))(v4 + 136))(
        common.type,
        "rvPopupWindow::InitVars: gui '%s' window '%s' references undefined cvar '%s'",
        v6,
        data,
        v7);
      return;
    }
    if ( !this->updateStr.list )
    {
      granularity = this->updateStr.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->updateStr.size )
        {
          v9 = granularity < this->updateStr.num;
          this->updateStr.size = granularity;
          if ( v9 )
            this->updateStr.num = granularity;
          this->updateStr.list = (idWinVar **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->updateStr.num; ++i )
            this->updateStr.list[i] = *(idWinVar **)(4 * i);
        }
      }
      else
      {
        this->updateStr.list = 0;
        this->updateStr.num = 0;
        this->updateStr.size = 0;
      }
    }
    num = this->updateStr.num;
    size = this->updateStr.size;
    if ( num == size )
    {
      if ( !this->updateStr.granularity )
        this->updateStr.granularity = 16;
      v13 = size + this->updateStr.granularity - (size + this->updateStr.granularity) % this->updateStr.granularity;
      if ( v13 > 0 )
      {
        if ( v13 != this->updateStr.size )
        {
          list = this->updateStr.list;
          this->updateStr.size = v13;
          if ( v13 < num )
            this->updateStr.num = v13;
          this->updateStr.list = (idWinVar **)Memory::Allocate(4 * v13);
          for ( j = 0; j < this->updateStr.num; ++j )
            this->updateStr.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->updateStr.list )
          Memory::Free(this->updateStr.list);
        this->updateStr.list = 0;
        this->updateStr.num = 0;
        this->updateStr.size = 0;
      }
    }
    this->updateStr.list[this->updateStr.num++] = &this->cvarStr;
  }
  if ( idWinStr::Length(&this->guiStr) )
  {
    if ( !this->updateStr.list )
    {
      v16 = this->updateStr.granularity;
      if ( v16 > 0 )
      {
        if ( v16 != this->updateStr.size )
        {
          v9 = v16 < this->updateStr.num;
          this->updateStr.size = v16;
          if ( v9 )
            this->updateStr.num = v16;
          this->updateStr.list = (idWinVar **)Memory::Allocate(4 * v16);
          for ( k = 0; k < this->updateStr.num; ++k )
            this->updateStr.list[k] = *(idWinVar **)(4 * k);
        }
      }
      else
      {
        this->updateStr.list = 0;
        this->updateStr.num = 0;
        this->updateStr.size = 0;
      }
    }
    v18 = this->updateStr.num;
    v19 = this->updateStr.size;
    if ( v18 == v19 )
    {
      if ( !this->updateStr.granularity )
        this->updateStr.granularity = 16;
      v20 = v19 + this->updateStr.granularity - (v19 + this->updateStr.granularity) % this->updateStr.granularity;
      if ( v20 > 0 )
      {
        if ( v20 != this->updateStr.size )
        {
          v21 = this->updateStr.list;
          this->updateStr.size = v20;
          if ( v20 < v18 )
            this->updateStr.num = v20;
          this->updateStr.list = (idWinVar **)Memory::Allocate(4 * v20);
          for ( m = 0; m < this->updateStr.num; ++m )
            this->updateStr.list[m] = v21[m];
          if ( v21 )
            Memory::Free(v21);
        }
      }
      else
      {
        if ( this->updateStr.list )
          Memory::Free(this->updateStr.list);
        this->updateStr.list = 0;
        this->updateStr.num = 0;
        this->updateStr.size = 0;
      }
    }
    this->updateStr.list[this->updateStr.num++] = &this->guiStr;
  }
  idMultiWinVar::SetGuiInfo(&this->updateStr, &this->gui->state);
  idMultiWinVar::Update(&this->updateStr);
}

// FUNC: public: virtual void __thiscall rvPopupWindow::RunNamedEvent(char const *)
void __thiscall rvPopupWindow::RunNamedEvent(rvPopupWindow *this, char *eventName)
{
  idStr *v3; // esi
  unsigned int v4; // ebx
  int v5; // eax
  idCVar *cvar; // eax
  idStr *v7; // esi
  unsigned int len; // ebx
  int v9; // eax
  const char *v10; // eax
  idWinStr_vtbl *v11; // edi
  char *v12; // eax
  idStr group; // [esp+10h] [ebp-6Ch] BYREF
  idStr event; // [esp+30h] [ebp-4Ch] BYREF
  idStr result; // [esp+50h] [ebp-2Ch] BYREF
  int v16; // [esp+78h] [ebp-4h]

  event.len = 0;
  event.alloced = 20;
  event.data = event.baseBuffer;
  event.baseBuffer[0] = 0;
  v16 = 1;
  group.len = 0;
  group.alloced = 20;
  group.data = group.baseBuffer;
  group.baseBuffer[0] = 0;
  if ( idStr::Cmpn(eventName, "cvar read ", 10) )
  {
    if ( !idStr::Cmpn(eventName, "cvar write ", 11) )
    {
      idStr::operator=(&event, eventName);
      v7 = idStr::Mid(&event, &result, 11, event.len - 11);
      len = v7->len;
      v9 = v7->len + 1;
      LOBYTE(v16) = 3;
      if ( v9 > group.alloced )
        idStr::ReAllocate(&group, v9, 0);
      qmemcpy(group.data, v7->data, len);
      group.data[len] = 0;
      group.len = len;
      LOBYTE(v16) = 1;
      idStr::FreeData(&result);
      if ( !idStr::Cmp(group.data, this->updateGroup.data.data) )
      {
        if ( this->cvar && this->cvarStr.guiDict )
        {
          v10 = this->cvarStr.c_str(&this->cvarStr);
          this->cvar->internalVar->InternalSetString(this->cvar->internalVar, v10);
        }
        if ( this->guiStr.guiDict )
        {
          v11 = this->guiStr.__vftable;
          v12 = va("%i", this->currentChoice);
          v11->Set(&this->guiStr, v12);
        }
      }
    }
  }
  else
  {
    idStr::operator=(&event, eventName);
    v3 = idStr::Mid(&event, &result, 10, event.len - 10);
    v4 = v3->len;
    v5 = v3->len + 1;
    LOBYTE(v16) = 2;
    if ( v5 > group.alloced )
      idStr::ReAllocate(&group, v5, 0);
    qmemcpy(group.data, v3->data, v4);
    group.data[v4] = 0;
    group.len = v4;
    LOBYTE(v16) = 1;
    idStr::FreeData(&result);
    if ( !idStr::Cmp(group.data, this->updateGroup.data.data) )
    {
      cvar = this->cvar;
      if ( cvar )
      {
        if ( this->cvarStr.guiDict )
          this->cvarStr.Set(&this->cvarStr, cvar->internalVar->value);
      }
    }
  }
  LOBYTE(v16) = 0;
  idStr::FreeData(&group);
  v16 = -1;
  idStr::FreeData(&event);
}

// FUNC: public: virtual char const * __thiscall rvPopupWindow::HandleEvent(struct sysEvent_s const *,bool *)
char *__thiscall rvPopupWindow::HandleEvent(rvPopupWindow *this, const sysEvent_s *event, bool *updateVisuals)
{
  idWindow *v4; // edi
  char v5; // bl
  const sysEvent_s *v6; // ecx
  int evValue; // ebp
  int v10; // edi
  int v11; // ebx
  int currentChoice; // eax
  bool v13; // cc
  int v14; // eax
  const char *v15; // eax
  idWinStr_vtbl *v16; // ebx
  char *v17; // eax
  bool runAction2; // [esp+13h] [ebp-11h]
  int key; // [esp+14h] [ebp-10h]
  int potentialChoice; // [esp+18h] [ebp-Ch]
  int v21; // [esp+1Ch] [ebp-8h]
  idWindow *parent; // [esp+20h] [ebp-4h]

  v4 = this->parent;
  v5 = 0;
  runAction2 = 0;
  parent = v4;
  idWindow::SetCapture(v4, this);
  v6 = event;
  if ( event->evType == SE_KEY )
  {
    evValue = event->evValue;
    if ( evValue == 136 || evValue == 170 )
    {
      if ( !event->evValue2 )
      {
        this->RunScript(this, 9);
        return this->cmd.data;
      }
      if ( ++this->currentChoice >= this->choices.num )
        this->currentChoice = 0;
      v5 = 1;
    }
    if ( evValue == 205 )
    {
      if ( ++this->currentChoice >= this->choices.num )
        this->currentChoice = 0;
    }
    else
    {
      if ( evValue != 135 && evValue != 168 && evValue != 206 )
      {
LABEL_18:
        if ( v6->evValue2 || evValue == 199 )
        {
          if ( v5 )
            goto LABEL_38;
          goto LABEL_39;
        }
        return (char *)&entityFilter;
      }
      if ( --this->currentChoice < 0 )
        this->currentChoice = this->choices.num - 1;
    }
    v5 = 1;
    goto LABEL_18;
  }
  if ( event->evType != SE_CHAR )
    return (char *)&entityFilter;
  evValue = event->evValue;
  v10 = 0;
  key = evValue;
  potentialChoice = -1;
  if ( this->choices.num <= 0 )
    goto LABEL_35;
  v11 = 0;
  while ( 1 )
  {
    v21 = toupper(*this->choices.list[v11].data);
    if ( toupper(evValue) != v21 )
      goto LABEL_31;
    currentChoice = this->currentChoice;
    v13 = v10 <= currentChoice;
    if ( v10 < currentChoice )
    {
      if ( potentialChoice < 0 )
      {
        potentialChoice = v10;
        goto LABEL_31;
      }
      v13 = v10 <= currentChoice;
    }
    if ( !v13 )
    {
      evValue = key;
      this->currentChoice = v10;
      v4 = parent;
      runAction2 = 1;
      goto LABEL_38;
    }
LABEL_31:
    ++v10;
    ++v11;
    if ( v10 >= this->choices.num )
      break;
    evValue = key;
  }
  if ( potentialChoice >= 0 )
    this->currentChoice = potentialChoice;
  evValue = key;
LABEL_35:
  v4 = parent;
  runAction2 = 1;
LABEL_38:
  this->RunScript(this, 2);
  v6 = event;
LABEL_39:
  if ( evValue == 199 )
  {
    if ( !v6->evValue2 )
      goto LABEL_44;
LABEL_43:
    rvPopupWindow::UpdateValue(this);
    v6 = event;
  }
  else if ( evValue == 187 )
  {
    goto LABEL_43;
  }
LABEL_44:
  v14 = v6->evValue;
  if ( v14 == 27 || v14 == 203 || evValue == 200 && v6->evValue2 )
  {
    idWindow::SetCapture(v4, 0);
    LOBYTE(event) = 0;
    idWinBool::operator=(&this->visible, (bool *)&event);
    idStr::operator=(&this->cmd, "fool the back button");
  }
  if ( this->liveUpdate.data )
  {
    if ( this->cvar && this->cvarStr.guiDict )
    {
      v15 = this->cvarStr.c_str(&this->cvarStr);
      this->cvar->internalVar->InternalSetString(this->cvar->internalVar, v15);
    }
    if ( this->guiStr.guiDict )
    {
      v16 = this->guiStr.__vftable;
      v17 = va("%i", this->currentChoice);
      v16->Set(&this->guiStr, v17);
    }
  }
  if ( runAction2 )
    this->RunScript(this, 9);
  return this->cmd.data;
}

// FUNC: private: void __thiscall rvPopupWindow::CommonInit(void)
void __thiscall rvPopupWindow::CommonInit(rvPopupWindow *this)
{
  idStr *list; // eax
  char *v3; // edi
  bool other; // [esp+Bh] [ebp-1h] BYREF

  this->currentChoice = 0;
  this->choiceType = 0;
  this->cvar = 0;
  other = 1;
  idWinBool::operator=(&this->liveUpdate, &other);
  list = this->choices.list;
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
  this->choices.list = 0;
  this->choices.num = 0;
  this->choices.size = 0;
  this->allowEmptyVal = 0;
}

// FUNC: public: __thiscall rvPopupWindow::rvPopupWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall rvPopupWindow::rvPopupWindow(rvPopupWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idWindow::idWindow(this, d, g);
  this->__vftable = (rvPopupWindow_vtbl *)&rvPopupWindow::`vftable';
  this->latchedChoices.len = 0;
  this->latchedChoices.alloced = 20;
  this->latchedChoices.data = this->latchedChoices.baseBuffer;
  this->latchedChoices.baseBuffer[0] = 0;
  this->choicesStr.guiDict = 0;
  this->choicesStr.name = 0;
  this->choicesStr.eval = 1;
  this->choicesStr.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->choicesStr.data.len = 0;
  this->choicesStr.data.alloced = 20;
  this->choicesStr.data.data = this->choicesStr.data.baseBuffer;
  this->choicesStr.data.baseBuffer[0] = 0;
  this->latchedDesc.len = 0;
  this->latchedDesc.alloced = 20;
  this->latchedDesc.data = this->latchedDesc.baseBuffer;
  this->latchedDesc.baseBuffer[0] = 0;
  this->descStr.guiDict = 0;
  this->descStr.name = 0;
  this->descStr.eval = 1;
  this->descStr.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->descStr.data.len = 0;
  this->descStr.data.alloced = 20;
  this->descStr.data.data = this->descStr.data.baseBuffer;
  this->descStr.data.baseBuffer[0] = 0;
  this->latchedVals.len = 0;
  this->latchedVals.alloced = 20;
  this->latchedVals.data = this->latchedVals.baseBuffer;
  this->latchedVals.baseBuffer[0] = 0;
  this->choiceVals.guiDict = 0;
  this->choiceVals.name = 0;
  this->choiceVals.eval = 1;
  this->choiceVals.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->choiceVals.data.len = 0;
  this->choiceVals.data.alloced = 20;
  this->choiceVals.data.data = this->choiceVals.data.baseBuffer;
  this->choiceVals.data.baseBuffer[0] = 0;
  this->choices.granularity = 16;
  this->choices.list = 0;
  this->choices.num = 0;
  this->choices.size = 0;
  this->values.granularity = 16;
  this->values.list = 0;
  this->values.num = 0;
  this->values.size = 0;
  this->descriptions.granularity = 16;
  this->descriptions.list = 0;
  this->descriptions.num = 0;
  this->descriptions.size = 0;
  this->guiStr.guiDict = 0;
  this->guiStr.name = 0;
  this->guiStr.eval = 1;
  this->guiStr.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->guiStr.data.len = 0;
  this->guiStr.data.alloced = 20;
  this->guiStr.data.data = this->guiStr.data.baseBuffer;
  this->guiStr.data.baseBuffer[0] = 0;
  this->cvarStr.guiDict = 0;
  this->cvarStr.name = 0;
  this->cvarStr.eval = 1;
  this->cvarStr.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->cvarStr.data.len = 0;
  this->cvarStr.data.alloced = 20;
  this->cvarStr.data.data = this->cvarStr.data.baseBuffer;
  this->cvarStr.data.baseBuffer[0] = 0;
  this->cvarName.guiDict = 0;
  this->cvarName.name = 0;
  this->cvarName.eval = 1;
  this->cvarName.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->cvarName.data.len = 0;
  this->cvarName.data.alloced = 20;
  this->cvarName.data.data = this->cvarName.data.baseBuffer;
  this->cvarName.data.baseBuffer[0] = 0;
  this->title.guiDict = 0;
  this->title.name = 0;
  this->title.eval = 1;
  this->title.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->title.data.len = 0;
  this->title.data.alloced = 20;
  this->title.data.data = this->title.data.baseBuffer;
  this->title.data.baseBuffer[0] = 0;
  this->updateStr.granularity = 16;
  this->updateStr.list = 0;
  this->updateStr.num = 0;
  this->updateStr.size = 0;
  this->liveUpdate.guiDict = 0;
  this->liveUpdate.name = 0;
  this->liveUpdate.eval = 1;
  this->liveUpdate.__vftable = (idWinBool_vtbl *)&idWinBool::`vftable';
  this->updateGroup.guiDict = 0;
  this->updateGroup.name = 0;
  this->updateGroup.eval = 1;
  this->updateGroup.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->updateGroup.data.alloced = 20;
  this->updateGroup.data.len = 0;
  this->updateGroup.data.data = this->updateGroup.data.baseBuffer;
  this->updateGroup.data.baseBuffer[0] = 0;
  this->dc = d;
  this->gui = g;
  rvPopupWindow::CommonInit(this);
}

// FUNC: public: virtual __thiscall rvPopupWindow::~rvPopupWindow(void)
void __thiscall rvPopupWindow::~rvPopupWindow(rvPopupWindow *this)
{
  idWinVar **list; // eax
  idStr *v3; // eax
  char *v4; // edi
  idStr *v5; // eax
  char *v6; // edi
  idStr *v7; // eax
  char *v8; // edi
  char *name; // [esp-4h] [ebp-20h]

  this->__vftable = (rvPopupWindow_vtbl *)&rvPopupWindow::`vftable';
  idWinStr::~idWinStr(&this->updateGroup);
  name = this->liveUpdate.name;
  this->liveUpdate.__vftable = (idWinBool_vtbl *)&idWinVar::`vftable';
  Memory::Free(name);
  this->liveUpdate.name = 0;
  list = this->updateStr.list;
  if ( list )
    Memory::Free(list);
  this->updateStr.list = 0;
  this->updateStr.num = 0;
  this->updateStr.size = 0;
  idWinStr::~idWinStr(&this->title);
  idWinStr::~idWinStr(&this->cvarName);
  idWinStr::~idWinStr(&this->cvarStr);
  idWinStr::~idWinStr(&this->guiStr);
  v3 = this->descriptions.list;
  if ( v3 )
  {
    v4 = &v3[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v3,
      0x20u,
      *(_DWORD *)&v3[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v4);
  }
  this->descriptions.list = 0;
  this->descriptions.num = 0;
  this->descriptions.size = 0;
  v5 = this->values.list;
  if ( v5 )
  {
    v6 = &v5[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v5,
      0x20u,
      *(_DWORD *)&v5[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v6);
  }
  this->values.list = 0;
  this->values.num = 0;
  this->values.size = 0;
  v7 = this->choices.list;
  if ( v7 )
  {
    v8 = &v7[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v7,
      0x20u,
      *(_DWORD *)&v7[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v8);
  }
  this->choices.list = 0;
  this->choices.num = 0;
  this->choices.size = 0;
  idWinStr::~idWinStr(&this->choiceVals);
  idStr::FreeData(&this->latchedVals);
  idWinStr::~idWinStr(&this->descStr);
  idStr::FreeData(&this->latchedDesc);
  idWinStr::~idWinStr(&this->choicesStr);
  idStr::FreeData(&this->latchedChoices);
  idWindow::~idWindow(this);
}

// FUNC: private: void __thiscall rvPopupWindow::ValidateChoice(void)
void __thiscall rvPopupWindow::ValidateChoice(rvPopupWindow *this)
{
  int currentChoice; // eax
  const char *v3; // eax
  const char *v4; // esi
  int v5; // ebx
  char *data; // edx
  char *v7; // ecx
  char v8; // al
  bool v9; // zf
  int granularity; // esi
  bool v11; // cc
  int *v12; // eax
  idStr *v13; // ebx
  int v14; // esi
  unsigned int v15; // edi
  idStr *v16; // ebx
  int v17; // eax
  int num; // ebx
  int size; // esi
  int v20; // esi
  idStr *v21; // eax
  char *v22; // esi
  idStr *list; // edi
  int *v24; // eax
  idStr *v25; // ebx
  int v26; // esi
  unsigned int v27; // edi
  idStr *v28; // ebx
  idStr *v29; // ebx
  int len; // esi
  int i; // [esp+8h] [ebp-3Ch]
  int j; // [esp+8h] [ebp-3Ch]
  int v33; // [esp+Ch] [ebp-38h]
  idStr *v34; // [esp+Ch] [ebp-38h]
  int v35; // [esp+10h] [ebp-34h]
  int v36; // [esp+10h] [ebp-34h]
  int v37; // [esp+14h] [ebp-30h]
  idStr v38; // [esp+18h] [ebp-2Ch] BYREF
  int v39; // [esp+40h] [ebp-4h]

  currentChoice = this->currentChoice;
  if ( currentChoice < 0 || currentChoice >= this->choices.num )
    this->currentChoice = 0;
  if ( !this->choices.num )
  {
    v3 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                         common.type,
                         "#str_107731",
                         -1);
    v4 = v3;
    v38.len = 0;
    v38.alloced = 20;
    v38.data = v38.baseBuffer;
    v38.baseBuffer[0] = 0;
    if ( v3 )
    {
      v5 = strlen(v3);
      if ( v5 + 1 > 20 )
        idStr::ReAllocate(&v38, v5 + 1, 1);
      data = v38.data;
      v7 = (char *)v4;
      do
      {
        v8 = *v7;
        *data++ = *v7++;
      }
      while ( v8 );
      v38.len = v5;
    }
    v9 = this->choices.list == 0;
    v39 = 0;
    if ( v9 )
    {
      granularity = this->choices.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->choices.size )
        {
          v11 = granularity < this->choices.num;
          this->choices.size = granularity;
          if ( v11 )
            this->choices.num = granularity;
          v12 = (int *)Memory::Allocate(32 * granularity + 4);
          LOBYTE(v39) = 1;
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
          v11 = this->choices.num <= 0;
          LOBYTE(v39) = 0;
          this->choices.list = v13;
          v33 = 0;
          if ( !v11 )
          {
            v14 = 0;
            for ( i = 0; ; v14 = i )
            {
              v15 = *(_DWORD *)v14;
              v16 = (idStr *)((char *)this->choices.list + v14);
              v17 = *(_DWORD *)v14 + 1;
              v35 = *(_DWORD *)v14;
              if ( v17 > v16->alloced )
                idStr::ReAllocate(v16, v17, 0);
              i += 32;
              qmemcpy(v16->data, *(const void **)(v14 + 4), v15);
              v16->data[v35] = 0;
              v16->len = v35;
              if ( ++v33 >= this->choices.num )
                break;
            }
          }
        }
      }
      else
      {
        this->choices.list = 0;
        this->choices.num = 0;
        this->choices.size = 0;
      }
    }
    num = this->choices.num;
    size = this->choices.size;
    if ( num == size )
    {
      if ( !this->choices.granularity )
        this->choices.granularity = 16;
      v20 = this->choices.granularity + size - (this->choices.granularity + size) % this->choices.granularity;
      if ( v20 > 0 )
      {
        if ( v20 != this->choices.size )
        {
          list = this->choices.list;
          v34 = list;
          this->choices.size = v20;
          if ( v20 < num )
            this->choices.num = v20;
          v24 = (int *)Memory::Allocate(32 * v20 + 4);
          LOBYTE(v39) = 2;
          if ( v24 )
          {
            v25 = (idStr *)(v24 + 1);
            *v24 = v20;
            `eh vector constructor iterator'(
              v24 + 1,
              0x20u,
              v20,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v25 = 0;
          }
          v26 = 0;
          v11 = this->choices.num <= 0;
          LOBYTE(v39) = 0;
          this->choices.list = v25;
          v36 = 0;
          if ( !v11 )
          {
            for ( j = 0; ; v26 = j )
            {
              v27 = *(int *)((char *)&list->len + v26);
              v28 = (idStr *)((char *)this->choices.list + v26);
              if ( (signed int)(v27 + 1) > v28->alloced )
                idStr::ReAllocate(v28, v27 + 1, 0);
              j += 32;
              qmemcpy(v28->data, *(const void **)((char *)&v34->data + v26), v27);
              v28->data[v27] = 0;
              v28->len = v27;
              v11 = ++v36 < this->choices.num;
              list = v34;
              if ( !v11 )
                break;
            }
          }
          if ( list )
          {
            `eh vector destructor iterator'(
              list,
              0x20u,
              *(_DWORD *)&list[-1].baseBuffer[16],
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(&list[-1].baseBuffer[16]);
          }
        }
      }
      else
      {
        v21 = this->choices.list;
        if ( v21 )
        {
          v22 = &v21[-1].baseBuffer[16];
          `eh vector destructor iterator'(
            v21,
            0x20u,
            *(_DWORD *)&v21[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(v22);
        }
        this->choices.list = 0;
        this->choices.num = 0;
        this->choices.size = 0;
      }
    }
    v29 = &this->choices.list[this->choices.num];
    len = v38.len;
    v37 = v38.len;
    if ( v38.len + 1 > v29->alloced )
      idStr::ReAllocate(v29, v38.len + 1, 0);
    qmemcpy(v29->data, v38.data, len);
    v29->data[v37] = 0;
    v29->len = v37;
    ++this->choices.num;
    v39 = -1;
    idStr::FreeData(&v38);
  }
}

// FUNC: private: void __thiscall rvPopupWindow::UpdateChoice(void)
void __thiscall rvPopupWindow::UpdateChoice(rvPopupWindow *this)
{
  idMultiWinVar *p_updateStr; // edi
  idCVar *cvar; // eax
  idWinVar *v4; // ecx
  const char *v5; // eax
  int num; // ebp
  int v7; // ebx
  int v8; // edi
  idStr *list; // eax
  const char *v10; // eax
  const char *data; // [esp-Ch] [ebp-14h]

  p_updateStr = &this->updateStr;
  if ( this->updateStr.num )
  {
    if ( this->liveUpdate.data )
    {
      cvar = this->cvar;
      if ( cvar )
      {
        if ( this->cvarStr.guiDict )
          this->cvarStr.Set(&this->cvarStr, cvar->internalVar->value);
      }
    }
    idMultiWinVar::Update(p_updateStr);
    if ( this->choiceType )
    {
      num = this->values.num;
      if ( !num )
        num = this->choices.num;
      v7 = 0;
      if ( num > 0 )
      {
        v8 = 0;
        do
        {
          if ( this->values.num )
            list = this->values.list;
          else
            list = this->choices.list;
          data = list[v8].data;
          v10 = this->cvarStr.c_str(&this->cvarStr);
          if ( !idStr::Icmp(v10, data) )
            break;
          ++v7;
          ++v8;
        }
        while ( v7 < num );
      }
      if ( v7 == num )
        v7 = 0;
      this->currentChoice = v7;
      rvPopupWindow::ValidateChoice(this);
    }
    else
    {
      v4 = *this->updateStr.list;
      if ( v4->guiDict )
      {
        v5 = v4->c_str(v4);
        this->currentChoice = atoi(v5);
      }
      rvPopupWindow::ValidateChoice(this);
    }
  }
}

// FUNC: private: void __thiscall rvPopupWindow::UpdateChoicesAndVals(void)
void __thiscall rvPopupWindow::UpdateChoicesAndVals(rvPopupWindow *this)
{
  idStr *list; // eax
  char *v3; // edi
  char *v4; // edi
  int v5; // eax
  char *v6; // eax
  int granularity; // esi
  bool v8; // cc
  int *v9; // eax
  idStr *v10; // edi
  idStr *v11; // ebx
  const void *v12; // esi
  int num; // edi
  int size; // eax
  int v15; // esi
  idStr *v16; // eax
  char *v17; // esi
  int *v18; // eax
  idStr *v19; // edi
  idStr *v20; // ebx
  const void *v21; // esi
  idStr *v22; // ebx
  int len; // esi
  int v24; // esi
  int i; // eax
  char v26; // cl
  char *v27; // edx
  int v28; // esi
  int v29; // eax
  char v30; // cl
  char *v31; // edx
  int v32; // esi
  int *v33; // eax
  idStr *v34; // edi
  idStr *v35; // ebx
  const void *v36; // esi
  int v37; // edi
  int v38; // eax
  int v39; // esi
  idStr *v40; // eax
  char *v41; // esi
  int *v42; // eax
  idStr *v43; // edi
  idStr *v44; // ebx
  const void *v45; // esi
  idStr *v46; // ebx
  int v47; // esi
  char *v48; // eax
  idStr *v49; // eax
  char *v50; // edi
  char *v51; // edi
  int v52; // eax
  int v53; // esi
  int *v54; // eax
  idStr *v55; // edi
  unsigned int *v56; // eax
  idStr *v57; // ebx
  const void *v58; // esi
  int v59; // edi
  int v60; // eax
  int v61; // esi
  idStr *v62; // eax
  char *v63; // esi
  int *v64; // eax
  idStr *v65; // edi
  idStr *v66; // ebx
  const void *v67; // esi
  idStr *v68; // ebx
  int v69; // esi
  int v70; // esi
  int v71; // eax
  char v72; // cl
  char *v73; // edx
  int v74; // esi
  int j; // eax
  char v76; // cl
  char *v77; // edx
  int v78; // esi
  int v79; // eax
  char v80; // cl
  char *v81; // edx
  int v82; // esi
  int *v83; // eax
  idStr *v84; // edi
  idStr *v85; // ebx
  const void *v86; // esi
  int v87; // edi
  int v88; // eax
  int v89; // esi
  idStr *v90; // eax
  char *v91; // esi
  int *v92; // eax
  idStr *v93; // edi
  idStr *v94; // ebx
  const void *v95; // esi
  idStr *v96; // ebx
  int v97; // esi
  char *v98; // eax
  idStr *v99; // eax
  char *v100; // edi
  char *v101; // edi
  int v102; // eax
  char *v103; // eax
  int v104; // esi
  int *v105; // eax
  idStr *v106; // edi
  unsigned int *v107; // eax
  idStr *v108; // ebx
  const void *v109; // esi
  int v110; // edi
  int v111; // eax
  int v112; // esi
  idStr *v113; // eax
  char *v114; // esi
  int *v115; // eax
  idStr *v116; // edi
  idStr *v117; // ebx
  const void *v118; // esi
  idStr *v119; // ebx
  int v120; // esi
  int v121; // esi
  int k; // eax
  char v123; // cl
  char *v124; // edx
  int v125; // esi
  int v126; // eax
  char v127; // cl
  char *v128; // edx
  int v129; // esi
  int *v130; // eax
  idStr *v131; // edi
  idStr *v132; // ebx
  const void *v133; // esi
  int v134; // edi
  int v135; // eax
  int v136; // esi
  idStr *v137; // eax
  char *v138; // esi
  int *v139; // eax
  idStr *v140; // edi
  idStr *v141; // ebx
  const void *v142; // esi
  idStr *v143; // ebx
  int v144; // esi
  char *v145; // eax
  char *v146; // [esp-10h] [ebp-190h]
  char *data; // [esp-Ch] [ebp-18Ch]
  char *ptr; // [esp+8h] [ebp-178h]
  idStr *ptra; // [esp+8h] [ebp-178h]
  unsigned int *ptrb; // [esp+8h] [ebp-178h]
  char *ptrc; // [esp+8h] [ebp-178h]
  unsigned int *ptrd; // [esp+8h] [ebp-178h]
  char *ptre; // [esp+8h] [ebp-178h]
  unsigned int *ptrf; // [esp+8h] [ebp-178h]
  char *ptrg; // [esp+8h] [ebp-178h]
  unsigned int *ptrh; // [esp+8h] [ebp-178h]
  char *ptri; // [esp+8h] [ebp-178h]
  unsigned int *ptrj; // [esp+8h] [ebp-178h]
  char *ptrk; // [esp+8h] [ebp-178h]
  unsigned int v160; // [esp+Ch] [ebp-174h]
  int v161; // [esp+Ch] [ebp-174h]
  unsigned int v162; // [esp+Ch] [ebp-174h]
  unsigned int v163; // [esp+Ch] [ebp-174h]
  int v164; // [esp+Ch] [ebp-174h]
  unsigned int v165; // [esp+Ch] [ebp-174h]
  unsigned int v166; // [esp+Ch] [ebp-174h]
  int v167; // [esp+Ch] [ebp-174h]
  unsigned int v168; // [esp+Ch] [ebp-174h]
  unsigned int v169; // [esp+Ch] [ebp-174h]
  int v170; // [esp+Ch] [ebp-174h]
  unsigned int v171; // [esp+Ch] [ebp-174h]
  unsigned int v172; // [esp+Ch] [ebp-174h]
  int v173; // [esp+Ch] [ebp-174h]
  unsigned int v174; // [esp+Ch] [ebp-174h]
  unsigned int v175; // [esp+Ch] [ebp-174h]
  int v176; // [esp+Ch] [ebp-174h]
  unsigned int v177; // [esp+10h] [ebp-170h]
  int v178; // [esp+10h] [ebp-170h]
  int v179; // [esp+10h] [ebp-170h]
  int v180; // [esp+10h] [ebp-170h]
  int v181; // [esp+10h] [ebp-170h]
  int v182; // [esp+10h] [ebp-170h]
  int v183; // [esp+10h] [ebp-170h]
  int v184; // [esp+10h] [ebp-170h]
  int v185; // [esp+10h] [ebp-170h]
  int v186; // [esp+10h] [ebp-170h]
  int v187; // [esp+10h] [ebp-170h]
  int v188; // [esp+10h] [ebp-170h]
  unsigned int *v189; // [esp+14h] [ebp-16Ch]
  char *v190; // [esp+14h] [ebp-16Ch]
  idStr *v191; // [esp+14h] [ebp-16Ch]
  idStr *v192; // [esp+14h] [ebp-16Ch]
  idStr *v193; // [esp+14h] [ebp-16Ch]
  idStr *v194; // [esp+14h] [ebp-16Ch]
  idStr *v195; // [esp+14h] [ebp-16Ch]
  bool negNum; // [esp+1Bh] [ebp-165h]
  idStr str2; // [esp+1Ch] [ebp-164h] BYREF
  idToken token; // [esp+3Ch] [ebp-144h] BYREF
  idStr str3; // [esp+8Ch] [ebp-F4h] BYREF
  idLexer src; // [esp+ACh] [ebp-D4h] BYREF
  int v201; // [esp+17Ch] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v201 = 2;
  str2.len = 0;
  str2.alloced = 20;
  str2.data = str2.baseBuffer;
  str2.baseBuffer[0] = 0;
  str3.alloced = 20;
  str3.len = 0;
  str3.data = str3.baseBuffer;
  str3.baseBuffer[0] = 0;
  idLexer::idLexer(&src);
  data = this->choicesStr.data.data;
  v146 = this->latchedChoices.data;
  LOBYTE(v201) = 3;
  if ( idStr::Icmp(v146, data) )
  {
    list = this->choices.list;
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
    this->choices.list = 0;
    this->choices.num = 0;
    this->choices.size = 0;
    idLexer::FreeSource(&src);
    v4 = this->choicesStr.data.data;
    src.flags = 6276;
    v5 = idWinStr::Length(&this->choicesStr);
    idLexer::LoadMemory(&src, v4, v5, "<ChoiceList>", 1);
    if ( src.loaded )
    {
      while ( idLexer::ReadToken(&src, &token) )
      {
        if ( idStr::Cmp(token.data, ";") )
        {
          v24 = str2.len + token.len;
          if ( str2.len + token.len + 1 > str2.alloced )
            idStr::ReAllocate(&str2, str2.len + token.len + 1, 1);
          for ( i = 0; i < token.len; v27[str2.len] = v26 )
          {
            v26 = token.data[i];
            v27 = &str2.data[i++];
          }
          str2.len = v24;
          str2.data[v24] = 0;
          v28 = str2.len + 1;
          if ( str2.len + 2 > str2.alloced )
            idStr::ReAllocate(&str2, str2.len + 2, 1);
          v29 = 0;
          v30 = 32;
          do
          {
            v31 = &str2.data[v29++];
            v31[str2.len] = v30;
            v30 = ::src[v29];
          }
          while ( v30 );
          str2.len = v28;
          str2.data[v28] = 0;
        }
        else if ( str2.len || this->allowEmptyVal )
        {
          idStr::StripTrailingWhitespace(&str2);
          v6 = (char *)(*(int (__thiscall **)(netadrtype_t, char *, int))(*(_DWORD *)common.type + 168))(
                         common.type,
                         str2.data,
                         -1);
          idStr::operator=(&str2, v6);
          if ( !this->choices.list )
          {
            granularity = this->choices.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->choices.size )
              {
                v8 = granularity < this->choices.num;
                this->choices.size = granularity;
                if ( v8 )
                  this->choices.num = granularity;
                v9 = (int *)Memory::Allocate(32 * granularity + 4);
                LOBYTE(v201) = 4;
                if ( v9 )
                {
                  v10 = (idStr *)(v9 + 1);
                  *v9 = granularity;
                  `eh vector constructor iterator'(
                    v9 + 1,
                    0x20u,
                    granularity,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v10 = 0;
                }
                v8 = this->choices.num <= 0;
                LOBYTE(v201) = 3;
                this->choices.list = v10;
                ptr = 0;
                if ( !v8 )
                {
                  v189 = 0;
                  do
                  {
                    v11 = (idStr *)((char *)v189 + (unsigned int)this->choices.list);
                    v177 = *v189;
                    if ( (signed int)(*v189 + 1) > v11->alloced )
                      idStr::ReAllocate(v11, v177 + 1, 0);
                    v12 = (const void *)v189[1];
                    v189 += 8;
                    qmemcpy(v11->data, v12, v177);
                    v11->data[v177] = 0;
                    v11->len = v177;
                    ++ptr;
                  }
                  while ( (int)ptr < this->choices.num );
                }
              }
            }
            else
            {
              this->choices.list = 0;
              this->choices.num = 0;
              this->choices.size = 0;
            }
          }
          num = this->choices.num;
          size = this->choices.size;
          if ( num == size )
          {
            if ( !this->choices.granularity )
              this->choices.granularity = 16;
            v15 = size + this->choices.granularity - (size + this->choices.granularity) % this->choices.granularity;
            if ( v15 > 0 )
            {
              if ( v15 != this->choices.size )
              {
                ptra = this->choices.list;
                this->choices.size = v15;
                if ( v15 < num )
                  this->choices.num = v15;
                v18 = (int *)Memory::Allocate(32 * v15 + 4);
                LOBYTE(v201) = 5;
                if ( v18 )
                {
                  v19 = (idStr *)(v18 + 1);
                  *v18 = v15;
                  `eh vector constructor iterator'(
                    v18 + 1,
                    0x20u,
                    v15,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v19 = 0;
                }
                v8 = this->choices.num <= 0;
                LOBYTE(v201) = 3;
                this->choices.list = v19;
                v178 = 0;
                if ( !v8 )
                {
                  v190 = 0;
                  do
                  {
                    v20 = (idStr *)&v190[(unsigned int)this->choices.list];
                    v160 = *(_DWORD *)&v190[(_DWORD)ptra];
                    if ( (signed int)(v160 + 1) > v20->alloced )
                      idStr::ReAllocate(v20, v160 + 1, 0);
                    v21 = *(const void **)&v190[(_DWORD)ptra + 4];
                    v190 += 32;
                    qmemcpy(v20->data, v21, v160);
                    v20->data[v160] = 0;
                    v20->len = v160;
                    ++v178;
                  }
                  while ( v178 < this->choices.num );
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
              v16 = this->choices.list;
              if ( v16 )
              {
                v17 = &v16[-1].baseBuffer[16];
                `eh vector destructor iterator'(
                  v16,
                  0x20u,
                  *(_DWORD *)&v16[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(v17);
              }
              this->choices.list = 0;
              this->choices.num = 0;
              this->choices.size = 0;
            }
          }
          v22 = &this->choices.list[this->choices.num];
          len = str2.len;
          v161 = str2.len;
          if ( str2.len + 1 > v22->alloced )
            idStr::ReAllocate(v22, str2.len + 1, 0);
          qmemcpy(v22->data, str2.data, len);
          v22->data[v161] = 0;
          v22->len = v161;
          ++this->choices.num;
          idStr::operator=(&str2, (char *)&entityFilter);
        }
      }
      if ( str2.len || this->allowEmptyVal )
      {
        idStr::StripTrailingWhitespace(&str2);
        if ( !this->choices.list )
        {
          v32 = this->choices.granularity;
          if ( v32 > 0 )
          {
            if ( v32 != this->choices.size )
            {
              v8 = v32 < this->choices.num;
              this->choices.size = v32;
              if ( v8 )
                this->choices.num = v32;
              v33 = (int *)Memory::Allocate(32 * v32 + 4);
              LOBYTE(v201) = 6;
              if ( v33 )
              {
                v34 = (idStr *)(v33 + 1);
                *v33 = v32;
                `eh vector constructor iterator'(
                  v33 + 1,
                  0x20u,
                  v32,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v34 = 0;
              }
              v8 = this->choices.num <= 0;
              LOBYTE(v201) = 3;
              this->choices.list = v34;
              v179 = 0;
              if ( !v8 )
              {
                ptrb = 0;
                do
                {
                  v35 = (idStr *)((char *)ptrb + (unsigned int)this->choices.list);
                  v162 = *ptrb;
                  if ( (signed int)(*ptrb + 1) > v35->alloced )
                    idStr::ReAllocate(v35, v162 + 1, 0);
                  v36 = (const void *)ptrb[1];
                  ptrb += 8;
                  qmemcpy(v35->data, v36, v162);
                  v35->data[v162] = 0;
                  v35->len = v162;
                  ++v179;
                }
                while ( v179 < this->choices.num );
              }
            }
          }
          else
          {
            this->choices.list = 0;
            this->choices.num = 0;
            this->choices.size = 0;
          }
        }
        v37 = this->choices.num;
        v38 = this->choices.size;
        if ( v37 == v38 )
        {
          if ( !this->choices.granularity )
            this->choices.granularity = 16;
          v39 = v38 + this->choices.granularity - (v38 + this->choices.granularity) % this->choices.granularity;
          if ( v39 > 0 )
          {
            if ( v39 != this->choices.size )
            {
              v191 = this->choices.list;
              this->choices.size = v39;
              if ( v39 < v37 )
                this->choices.num = v39;
              v42 = (int *)Memory::Allocate(32 * v39 + 4);
              LOBYTE(v201) = 7;
              if ( v42 )
              {
                v43 = (idStr *)(v42 + 1);
                *v42 = v39;
                `eh vector constructor iterator'(
                  v42 + 1,
                  0x20u,
                  v39,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v43 = 0;
              }
              v8 = this->choices.num <= 0;
              LOBYTE(v201) = 3;
              this->choices.list = v43;
              v180 = 0;
              if ( !v8 )
              {
                ptrc = 0;
                do
                {
                  v44 = (idStr *)&ptrc[(unsigned int)this->choices.list];
                  v163 = *(_DWORD *)&ptrc[(_DWORD)v191];
                  if ( (signed int)(v163 + 1) > v44->alloced )
                    idStr::ReAllocate(v44, v163 + 1, 0);
                  v45 = *(const void **)&ptrc[(_DWORD)v191 + 4];
                  ptrc += 32;
                  qmemcpy(v44->data, v45, v163);
                  v44->data[v163] = 0;
                  v44->len = v163;
                  ++v180;
                }
                while ( v180 < this->choices.num );
              }
              if ( v191 )
              {
                `eh vector destructor iterator'(
                  v191,
                  0x20u,
                  *(_DWORD *)&v191[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(&v191[-1].baseBuffer[16]);
              }
            }
          }
          else
          {
            v40 = this->choices.list;
            if ( v40 )
            {
              v41 = &v40[-1].baseBuffer[16];
              `eh vector destructor iterator'(
                v40,
                0x20u,
                *(_DWORD *)&v40[-1].baseBuffer[16],
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(v41);
            }
            this->choices.list = 0;
            this->choices.num = 0;
            this->choices.size = 0;
          }
        }
        v46 = &this->choices.list[this->choices.num];
        v47 = str2.len;
        v164 = str2.len;
        if ( str2.len + 1 > v46->alloced )
          idStr::ReAllocate(v46, str2.len + 1, 0);
        qmemcpy(v46->data, str2.data, v47);
        v46->data[v164] = 0;
        v46->len = v164;
        ++this->choices.num;
      }
    }
    v48 = (char *)this->choicesStr.c_str(&this->choicesStr);
    idStr::operator=(&this->latchedChoices, v48);
  }
  if ( idWinStr::Length(&this->choiceVals) && idStr::Icmp(this->latchedVals.data, this->choiceVals.data.data) )
  {
    v49 = this->values.list;
    if ( v49 )
    {
      v50 = &v49[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        v49,
        0x20u,
        *(_DWORD *)&v49[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v50);
    }
    this->values.list = 0;
    this->values.num = 0;
    this->values.size = 0;
    idLexer::FreeSource(&src);
    v51 = this->choiceVals.data.data;
    src.flags = 6272;
    v52 = idWinStr::Length(&this->choiceVals);
    idLexer::LoadMemory(&src, v51, v52, "<ChoiceVals>", 1);
    idStr::operator=(&str2, (char *)&entityFilter);
    negNum = 0;
    if ( src.loaded )
    {
      while ( idLexer::ReadToken(&src, &token) )
      {
        if ( idStr::Cmp(token.data, "-") )
        {
          if ( idStr::Cmp(token.data, ";") )
          {
            if ( negNum )
            {
              v70 = str2.len + 1;
              if ( str2.len + 2 > str2.alloced )
                idStr::ReAllocate(&str2, str2.len + 2, 1);
              v71 = 0;
              v72 = 45;
              do
              {
                v73 = &str2.data[v71++];
                v73[str2.len] = v72;
                v72 = asc_1029DD84[v71];
              }
              while ( v72 );
              str2.len = v70;
              str2.data[v70] = 0;
              negNum = 0;
            }
            v74 = str2.len + token.len;
            if ( str2.len + token.len + 1 > str2.alloced )
              idStr::ReAllocate(&str2, str2.len + token.len + 1, 1);
            for ( j = 0; j < token.len; v77[str2.len] = v76 )
            {
              v76 = token.data[j];
              v77 = &str2.data[j++];
            }
            str2.len = v74;
            str2.data[v74] = 0;
            v78 = str2.len + 1;
            if ( str2.len + 2 > str2.alloced )
              idStr::ReAllocate(&str2, str2.len + 2, 1);
            v79 = 0;
            v80 = 32;
            do
            {
              v81 = &str2.data[v79++];
              v81[str2.len] = v80;
              v80 = ::src[v79];
            }
            while ( v80 );
            str2.len = v78;
            str2.data[v78] = 0;
          }
          else if ( str2.len || this->allowEmptyVal )
          {
            idStr::StripTrailingWhitespace(&str2);
            if ( !this->values.list )
            {
              v53 = this->values.granularity;
              if ( v53 > 0 )
              {
                if ( v53 != this->values.size )
                {
                  v8 = v53 < this->values.num;
                  this->values.size = v53;
                  if ( v8 )
                    this->values.num = v53;
                  v54 = (int *)Memory::Allocate(32 * v53 + 4);
                  LOBYTE(v201) = 8;
                  if ( v54 )
                  {
                    v55 = (idStr *)(v54 + 1);
                    *v54 = v53;
                    `eh vector constructor iterator'(
                      v54 + 1,
                      0x20u,
                      v53,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  }
                  else
                  {
                    v55 = 0;
                  }
                  v8 = this->values.num <= 0;
                  LOBYTE(v201) = 3;
                  this->values.list = v55;
                  v181 = 0;
                  if ( !v8 )
                  {
                    v56 = 0;
                    for ( ptrd = 0; ; v56 = ptrd )
                    {
                      v57 = (idStr *)((char *)v56 + (unsigned int)this->values.list);
                      v165 = *v56;
                      if ( (signed int)(*v56 + 1) > v57->alloced )
                        idStr::ReAllocate(v57, v165 + 1, 0);
                      v58 = (const void *)ptrd[1];
                      ptrd += 8;
                      qmemcpy(v57->data, v58, v165);
                      v57->data[v165] = 0;
                      v57->len = v165;
                      if ( ++v181 >= this->values.num )
                        break;
                    }
                  }
                }
              }
              else
              {
                this->values.list = 0;
                this->values.num = 0;
                this->values.size = 0;
              }
            }
            v59 = this->values.num;
            v60 = this->values.size;
            if ( v59 == v60 )
            {
              if ( !this->values.granularity )
                this->values.granularity = 16;
              v61 = v60 + this->values.granularity - (v60 + this->values.granularity) % this->values.granularity;
              if ( v61 > 0 )
              {
                if ( v61 != this->values.size )
                {
                  v192 = this->values.list;
                  this->values.size = v61;
                  if ( v61 < v59 )
                    this->values.num = v61;
                  v64 = (int *)Memory::Allocate(32 * v61 + 4);
                  LOBYTE(v201) = 9;
                  if ( v64 )
                  {
                    v65 = (idStr *)(v64 + 1);
                    *v64 = v61;
                    `eh vector constructor iterator'(
                      v64 + 1,
                      0x20u,
                      v61,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  }
                  else
                  {
                    v65 = 0;
                  }
                  v8 = this->values.num <= 0;
                  LOBYTE(v201) = 3;
                  this->values.list = v65;
                  v182 = 0;
                  if ( !v8 )
                  {
                    ptre = 0;
                    do
                    {
                      v66 = (idStr *)&ptre[(unsigned int)this->values.list];
                      v166 = *(_DWORD *)&ptre[(_DWORD)v192];
                      if ( (signed int)(v166 + 1) > v66->alloced )
                        idStr::ReAllocate(v66, v166 + 1, 0);
                      v67 = *(const void **)&ptre[(_DWORD)v192 + 4];
                      ptre += 32;
                      qmemcpy(v66->data, v67, v166);
                      v66->data[v166] = 0;
                      v66->len = v166;
                      ++v182;
                    }
                    while ( v182 < this->values.num );
                  }
                  if ( v192 )
                  {
                    `eh vector destructor iterator'(
                      v192,
                      0x20u,
                      *(_DWORD *)&v192[-1].baseBuffer[16],
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    Memory::Free(&v192[-1].baseBuffer[16]);
                  }
                }
              }
              else
              {
                v62 = this->values.list;
                if ( v62 )
                {
                  v63 = &v62[-1].baseBuffer[16];
                  `eh vector destructor iterator'(
                    v62,
                    0x20u,
                    *(_DWORD *)&v62[-1].baseBuffer[16],
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  Memory::Free(v63);
                }
                this->values.list = 0;
                this->values.num = 0;
                this->values.size = 0;
              }
            }
            v68 = &this->values.list[this->values.num];
            v69 = str2.len;
            v167 = str2.len;
            if ( str2.len + 1 > v68->alloced )
              idStr::ReAllocate(v68, str2.len + 1, 0);
            qmemcpy(v68->data, str2.data, v69);
            v68->data[v167] = 0;
            v68->len = v167;
            ++this->values.num;
            idStr::operator=(&str2, (char *)&entityFilter);
          }
        }
        else
        {
          negNum = 1;
        }
      }
      if ( str2.len || this->allowEmptyVal )
      {
        idStr::StripTrailingWhitespace(&str2);
        if ( !this->values.list )
        {
          v82 = this->values.granularity;
          if ( v82 > 0 )
          {
            if ( v82 != this->values.size )
            {
              v8 = v82 < this->values.num;
              this->values.size = v82;
              if ( v8 )
                this->values.num = v82;
              v83 = (int *)Memory::Allocate(32 * v82 + 4);
              LOBYTE(v201) = 10;
              if ( v83 )
              {
                v84 = (idStr *)(v83 + 1);
                *v83 = v82;
                `eh vector constructor iterator'(
                  v83 + 1,
                  0x20u,
                  v82,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v84 = 0;
              }
              v8 = this->values.num <= 0;
              LOBYTE(v201) = 3;
              this->values.list = v84;
              v183 = 0;
              if ( !v8 )
              {
                ptrf = 0;
                do
                {
                  v85 = (idStr *)((char *)ptrf + (unsigned int)this->values.list);
                  v168 = *ptrf;
                  if ( (signed int)(*ptrf + 1) > v85->alloced )
                    idStr::ReAllocate(v85, v168 + 1, 0);
                  v86 = (const void *)ptrf[1];
                  ptrf += 8;
                  qmemcpy(v85->data, v86, v168);
                  v85->data[v168] = 0;
                  v85->len = v168;
                  ++v183;
                }
                while ( v183 < this->values.num );
              }
            }
          }
          else
          {
            this->values.list = 0;
            this->values.num = 0;
            this->values.size = 0;
          }
        }
        v87 = this->values.num;
        v88 = this->values.size;
        if ( v87 == v88 )
        {
          if ( !this->values.granularity )
            this->values.granularity = 16;
          v89 = v88 + this->values.granularity - (v88 + this->values.granularity) % this->values.granularity;
          if ( v89 > 0 )
          {
            if ( v89 != this->values.size )
            {
              v193 = this->values.list;
              this->values.size = v89;
              if ( v89 < v87 )
                this->values.num = v89;
              v92 = (int *)Memory::Allocate(32 * v89 + 4);
              LOBYTE(v201) = 11;
              if ( v92 )
              {
                v93 = (idStr *)(v92 + 1);
                *v92 = v89;
                `eh vector constructor iterator'(
                  v92 + 1,
                  0x20u,
                  v89,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v93 = 0;
              }
              v8 = this->values.num <= 0;
              LOBYTE(v201) = 3;
              this->values.list = v93;
              v184 = 0;
              if ( !v8 )
              {
                ptrg = 0;
                do
                {
                  v94 = (idStr *)&ptrg[(unsigned int)this->values.list];
                  v169 = *(_DWORD *)&ptrg[(_DWORD)v193];
                  if ( (signed int)(v169 + 1) > v94->alloced )
                    idStr::ReAllocate(v94, v169 + 1, 0);
                  v95 = *(const void **)&ptrg[(_DWORD)v193 + 4];
                  ptrg += 32;
                  qmemcpy(v94->data, v95, v169);
                  v94->data[v169] = 0;
                  v94->len = v169;
                  ++v184;
                }
                while ( v184 < this->values.num );
              }
              if ( v193 )
              {
                `eh vector destructor iterator'(
                  v193,
                  0x20u,
                  *(_DWORD *)&v193[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(&v193[-1].baseBuffer[16]);
              }
            }
          }
          else
          {
            v90 = this->values.list;
            if ( v90 )
            {
              v91 = &v90[-1].baseBuffer[16];
              `eh vector destructor iterator'(
                v90,
                0x20u,
                *(_DWORD *)&v90[-1].baseBuffer[16],
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(v91);
            }
            this->values.list = 0;
            this->values.num = 0;
            this->values.size = 0;
          }
        }
        v96 = &this->values.list[this->values.num];
        v97 = str2.len;
        v170 = str2.len;
        if ( str2.len + 1 > v96->alloced )
          idStr::ReAllocate(v96, str2.len + 1, 0);
        qmemcpy(v96->data, str2.data, v97);
        v96->data[v170] = 0;
        v96->len = v170;
        ++this->values.num;
      }
    }
    if ( this->choices.num != this->values.num )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "rvPopupWindow:: gui '%s' window '%s' has value count unequal to choices count",
        this->gui->source.data,
        this->name.data);
    v98 = (char *)this->choiceVals.c_str(&this->choiceVals);
    idStr::operator=(&this->latchedVals, v98);
  }
  if ( idStr::Icmp(this->latchedDesc.data, this->descStr.data.data) )
  {
    v99 = this->descriptions.list;
    if ( v99 )
    {
      v100 = &v99[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        v99,
        0x20u,
        *(_DWORD *)&v99[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v100);
    }
    this->descriptions.list = 0;
    this->descriptions.num = 0;
    this->descriptions.size = 0;
    idLexer::FreeSource(&src);
    v101 = this->descStr.data.data;
    src.flags = 6276;
    v102 = idWinStr::Length(&this->descStr);
    idLexer::LoadMemory(&src, v101, v102, "<DescList>", 1);
    idStr::operator=(&str2, (char *)&entityFilter);
    if ( src.loaded )
    {
      while ( idLexer::ReadToken(&src, &token) )
      {
        if ( idStr::Cmp(token.data, ";") )
        {
          v121 = str2.len + token.len;
          if ( str2.len + token.len + 1 > str2.alloced )
            idStr::ReAllocate(&str2, str2.len + token.len + 1, 1);
          for ( k = 0; k < token.len; v124[str2.len] = v123 )
          {
            v123 = token.data[k];
            v124 = &str2.data[k++];
          }
          str2.len = v121;
          str2.data[v121] = 0;
          v125 = str2.len + 1;
          if ( str2.len + 2 > str2.alloced )
            idStr::ReAllocate(&str2, str2.len + 2, 1);
          v126 = 0;
          v127 = 32;
          do
          {
            v128 = &str2.data[v126++];
            v128[str2.len] = v127;
            v127 = ::src[v126];
          }
          while ( v127 );
          str2.len = v125;
          str2.data[v125] = 0;
        }
        else if ( str2.len || this->allowEmptyVal )
        {
          idStr::StripTrailingWhitespace(&str2);
          v103 = (char *)(*(int (__thiscall **)(netadrtype_t, char *, int))(*(_DWORD *)common.type + 168))(
                           common.type,
                           str2.data,
                           -1);
          idStr::operator=(&str2, v103);
          if ( !this->descriptions.list )
          {
            v104 = this->descriptions.granularity;
            if ( v104 > 0 )
            {
              if ( v104 != this->descriptions.size )
              {
                v8 = v104 < this->descriptions.num;
                this->descriptions.size = v104;
                if ( v8 )
                  this->descriptions.num = v104;
                v105 = (int *)Memory::Allocate(32 * v104 + 4);
                LOBYTE(v201) = 12;
                if ( v105 )
                {
                  v106 = (idStr *)(v105 + 1);
                  *v105 = v104;
                  `eh vector constructor iterator'(
                    v105 + 1,
                    0x20u,
                    v104,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v106 = 0;
                }
                v8 = this->descriptions.num <= 0;
                LOBYTE(v201) = 3;
                this->descriptions.list = v106;
                v185 = 0;
                if ( !v8 )
                {
                  v107 = 0;
                  for ( ptrh = 0; ; v107 = ptrh )
                  {
                    v108 = (idStr *)((char *)v107 + (unsigned int)this->descriptions.list);
                    v171 = *v107;
                    if ( (signed int)(*v107 + 1) > v108->alloced )
                      idStr::ReAllocate(v108, v171 + 1, 0);
                    v109 = (const void *)ptrh[1];
                    ptrh += 8;
                    qmemcpy(v108->data, v109, v171);
                    v108->data[v171] = 0;
                    v108->len = v171;
                    if ( ++v185 >= this->descriptions.num )
                      break;
                  }
                }
              }
            }
            else
            {
              this->descriptions.list = 0;
              this->descriptions.num = 0;
              this->descriptions.size = 0;
            }
          }
          v110 = this->descriptions.num;
          v111 = this->descriptions.size;
          if ( v110 == v111 )
          {
            if ( !this->descriptions.granularity )
              this->descriptions.granularity = 16;
            v112 = v111
                 + this->descriptions.granularity
                 - (v111 + this->descriptions.granularity) % this->descriptions.granularity;
            if ( v112 > 0 )
            {
              if ( v112 != this->descriptions.size )
              {
                v194 = this->descriptions.list;
                this->descriptions.size = v112;
                if ( v112 < v110 )
                  this->descriptions.num = v112;
                v115 = (int *)Memory::Allocate(32 * v112 + 4);
                LOBYTE(v201) = 13;
                if ( v115 )
                {
                  v116 = (idStr *)(v115 + 1);
                  *v115 = v112;
                  `eh vector constructor iterator'(
                    v115 + 1,
                    0x20u,
                    v112,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v116 = 0;
                }
                v8 = this->descriptions.num <= 0;
                LOBYTE(v201) = 3;
                this->descriptions.list = v116;
                v186 = 0;
                if ( !v8 )
                {
                  ptri = 0;
                  do
                  {
                    v117 = (idStr *)&ptri[(unsigned int)this->descriptions.list];
                    v172 = *(_DWORD *)&ptri[(_DWORD)v194];
                    if ( (signed int)(v172 + 1) > v117->alloced )
                      idStr::ReAllocate(v117, v172 + 1, 0);
                    v118 = *(const void **)&ptri[(_DWORD)v194 + 4];
                    ptri += 32;
                    qmemcpy(v117->data, v118, v172);
                    v117->data[v172] = 0;
                    v117->len = v172;
                    ++v186;
                  }
                  while ( v186 < this->descriptions.num );
                }
                if ( v194 )
                {
                  `eh vector destructor iterator'(
                    v194,
                    0x20u,
                    *(_DWORD *)&v194[-1].baseBuffer[16],
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  Memory::Free(&v194[-1].baseBuffer[16]);
                }
              }
            }
            else
            {
              v113 = this->descriptions.list;
              if ( v113 )
              {
                v114 = &v113[-1].baseBuffer[16];
                `eh vector destructor iterator'(
                  v113,
                  0x20u,
                  *(_DWORD *)&v113[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(v114);
              }
              this->descriptions.list = 0;
              this->descriptions.num = 0;
              this->descriptions.size = 0;
            }
          }
          v119 = &this->descriptions.list[this->descriptions.num];
          v120 = str2.len;
          v173 = str2.len;
          if ( str2.len + 1 > v119->alloced )
            idStr::ReAllocate(v119, str2.len + 1, 0);
          qmemcpy(v119->data, str2.data, v120);
          v119->data[v173] = 0;
          v119->len = v173;
          ++this->descriptions.num;
          idStr::operator=(&str2, (char *)&entityFilter);
        }
      }
      if ( str2.len || this->allowEmptyVal )
      {
        idStr::StripTrailingWhitespace(&str2);
        if ( !this->descriptions.list )
        {
          v129 = this->descriptions.granularity;
          if ( v129 > 0 )
          {
            if ( v129 != this->descriptions.size )
            {
              v8 = v129 < this->descriptions.num;
              this->descriptions.size = v129;
              if ( v8 )
                this->descriptions.num = v129;
              v130 = (int *)Memory::Allocate(32 * v129 + 4);
              LOBYTE(v201) = 14;
              if ( v130 )
              {
                v131 = (idStr *)(v130 + 1);
                *v130 = v129;
                `eh vector constructor iterator'(
                  v130 + 1,
                  0x20u,
                  v129,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v131 = 0;
              }
              v8 = this->descriptions.num <= 0;
              LOBYTE(v201) = 3;
              this->descriptions.list = v131;
              v187 = 0;
              if ( !v8 )
              {
                ptrj = 0;
                do
                {
                  v132 = (idStr *)((char *)ptrj + (unsigned int)this->descriptions.list);
                  v174 = *ptrj;
                  if ( (signed int)(*ptrj + 1) > v132->alloced )
                    idStr::ReAllocate(v132, v174 + 1, 0);
                  v133 = (const void *)ptrj[1];
                  ptrj += 8;
                  qmemcpy(v132->data, v133, v174);
                  v132->data[v174] = 0;
                  v132->len = v174;
                  ++v187;
                }
                while ( v187 < this->descriptions.num );
              }
            }
          }
          else
          {
            this->descriptions.list = 0;
            this->descriptions.num = 0;
            this->descriptions.size = 0;
          }
        }
        v134 = this->descriptions.num;
        v135 = this->descriptions.size;
        if ( v134 == v135 )
        {
          if ( !this->descriptions.granularity )
            this->descriptions.granularity = 16;
          v136 = v135
               + this->descriptions.granularity
               - (v135 + this->descriptions.granularity) % this->descriptions.granularity;
          if ( v136 > 0 )
          {
            if ( v136 != this->descriptions.size )
            {
              v195 = this->descriptions.list;
              this->descriptions.size = v136;
              if ( v136 < v134 )
                this->descriptions.num = v136;
              v139 = (int *)Memory::Allocate(32 * v136 + 4);
              LOBYTE(v201) = 15;
              if ( v139 )
              {
                v140 = (idStr *)(v139 + 1);
                *v139 = v136;
                `eh vector constructor iterator'(
                  v139 + 1,
                  0x20u,
                  v136,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v140 = 0;
              }
              v8 = this->descriptions.num <= 0;
              LOBYTE(v201) = 3;
              this->descriptions.list = v140;
              v188 = 0;
              if ( !v8 )
              {
                ptrk = 0;
                do
                {
                  v141 = (idStr *)&ptrk[(unsigned int)this->descriptions.list];
                  v175 = *(_DWORD *)&ptrk[(_DWORD)v195];
                  if ( (signed int)(v175 + 1) > v141->alloced )
                    idStr::ReAllocate(v141, v175 + 1, 0);
                  v142 = *(const void **)&ptrk[(_DWORD)v195 + 4];
                  ptrk += 32;
                  qmemcpy(v141->data, v142, v175);
                  v141->data[v175] = 0;
                  v141->len = v175;
                  ++v188;
                }
                while ( v188 < this->descriptions.num );
              }
              if ( v195 )
              {
                `eh vector destructor iterator'(
                  v195,
                  0x20u,
                  *(_DWORD *)&v195[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(&v195[-1].baseBuffer[16]);
              }
            }
          }
          else
          {
            v137 = this->descriptions.list;
            if ( v137 )
            {
              v138 = &v137[-1].baseBuffer[16];
              `eh vector destructor iterator'(
                v137,
                0x20u,
                *(_DWORD *)&v137[-1].baseBuffer[16],
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(v138);
            }
            this->descriptions.list = 0;
            this->descriptions.num = 0;
            this->descriptions.size = 0;
          }
        }
        v143 = &this->descriptions.list[this->descriptions.num];
        v144 = str2.len;
        v176 = str2.len;
        if ( str2.len + 1 > v143->alloced )
          idStr::ReAllocate(v143, str2.len + 1, 0);
        qmemcpy(v143->data, str2.data, v144);
        v143->data[v176] = 0;
        v143->len = v176;
        ++this->descriptions.num;
      }
    }
    if ( this->choices.num != this->descriptions.num )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "rvPopupWindow:: gui '%s' window '%s' has description count unequal to choices count",
        this->gui->source.data,
        this->name.data);
    v145 = (char *)this->descStr.c_str(&this->descStr);
    idStr::operator=(&this->latchedDesc, v145);
  }
  LOBYTE(v201) = 2;
  idLexer::~idLexer(&src);
  LOBYTE(v201) = 1;
  idStr::FreeData(&str3);
  LOBYTE(v201) = 0;
  idStr::FreeData(&str2);
  v201 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: virtual void __thiscall rvPopupWindow::PostParse(void)
void __thiscall rvPopupWindow::PostParse(rvPopupWindow *this)
{
  const char *v2; // eax
  idWinStr_vtbl *v3; // ebx
  char *v4; // eax
  const idCmdArgs *v5; // [esp+0h] [ebp-4h]

  SpawnStub(v5);
  rvPopupWindow::UpdateChoicesAndVals(this);
  rvPopupWindow::InitVars(this);
  rvPopupWindow::UpdateChoice(this);
  if ( this->liveUpdate.data )
  {
    if ( this->cvar && this->cvarStr.guiDict )
    {
      v2 = this->cvarStr.c_str(&this->cvarStr);
      this->cvar->internalVar->InternalSetString(this->cvar->internalVar, v2);
    }
    if ( this->guiStr.guiDict )
    {
      v3 = this->guiStr.__vftable;
      v4 = va("%i", this->currentChoice);
      v3->Set(&this->guiStr, v4);
    }
  }
  BYTE1(this->flags) |= 8u;
}

// FUNC: public: virtual void __thiscall rvPopupWindow::Draw(int,float,float)
void __thiscall rvPopupWindow::Draw(rvPopupWindow *this, int time, float x, float y)
{
  float v5; // ebx
  float v6; // ebp
  idRectangle *p_textRect; // edi
  idRectangle *v8; // ecx
  double v9; // st6
  int num; // eax
  int v11; // edi
  float v12; // eax
  float v13; // ecx
  float z; // edx
  idVec4 v15; // [esp-3Ch] [ebp-A0h]
  idVec4 v16; // [esp-3Ch] [ebp-A0h]
  int v17; // [esp+10h] [ebp-54h]
  idRectangle choiceRect; // [esp+14h] [ebp-50h]
  idRectangle descRect; // [esp+24h] [ebp-40h]
  idRectangle titleRect; // [esp+34h] [ebp-30h]
  __int64 baseColor_8; // [esp+4Ch] [ebp-18h]
  float color_12; // [esp+60h] [ebp-4h]

  v5 = this->foreColor.data.x;
  v6 = this->foreColor.data.y;
  baseColor_8 = *(_QWORD *)&this->foreColor.data.z;
  p_textRect = &this->textRect;
  v8 = &this->textRect;
  *(_QWORD *)&titleRect.x = *(_QWORD *)&v8->x;
  titleRect.w = v8->w;
  choiceRect.x = v8->x;
  rvPopupWindow::UpdateChoicesAndVals(this);
  choiceRect.w = this->textRect.w * 0.5;
  choiceRect.h = this->textRect.h * 0.75;
  if ( this->choices.num > 0 )
    choiceRect.h = choiceRect.h / (double)this->choices.num;
  choiceRect.y = this->textRect.y + this->textRect.h * 0.25;
  v9 = this->textRect.w * 0.5;
  descRect.w = v9;
  titleRect.h = this->textRect.h * 0.25;
  descRect.h = this->textRect.h * 0.75;
  descRect.y = choiceRect.y;
  *(_QWORD *)&v15.x = __PAIR64__(LODWORD(v6), LODWORD(v5));
  *(_QWORD *)&v15.z = baseColor_8;
  descRect.x = p_textRect->x + v9;
  idDeviceContext::DrawTextA(
    this->dc,
    this->title.data.data,
    this->textScale.data,
    1,
    this->textStyle,
    v15,
    titleRect,
    0,
    -1,
    0,
    0,
    0,
    0,
    0);
  num = this->choices.num;
  v11 = 0;
  if ( num )
  {
    if ( num > 0 )
    {
      v17 = 0;
      do
      {
        v12 = v5;
        v13 = v6;
        color_12 = *((float *)&baseColor_8 + 1);
        LODWORD(z) = baseColor_8;
        if ( this->currentChoice == v11 )
        {
          v12 = this->hoverColor.data.x;
          v13 = this->hoverColor.data.y;
          z = this->hoverColor.data.z;
          color_12 = this->hoverColor.data.w;
        }
        *(_QWORD *)&v16.x = __PAIR64__(LODWORD(v13), LODWORD(v12));
        *(_QWORD *)&v16.z = __PAIR64__(LODWORD(color_12), LODWORD(z));
        idDeviceContext::DrawTextA(
          this->dc,
          this->choices.list[v17].data,
          this->textScale.data,
          1,
          this->textStyle,
          v16,
          choiceRect,
          0,
          -1,
          0,
          0,
          0,
          0,
          0);
        ++v11;
        ++v17;
        choiceRect.y = choiceRect.y + choiceRect.h;
      }
      while ( v11 < this->choices.num );
    }
    if ( this->descriptions.num == this->choices.num )
      idDeviceContext::DrawTextA(
        this->dc,
        this->descriptions.list[this->currentChoice].data,
        this->textScale.data,
        0,
        this->textStyle,
        this->foreColor.data,
        descRect,
        0,
        -1,
        0,
        0,
        0,
        0,
        0);
  }
}

// FUNC: public: virtual void __thiscall rvPopupWindow::Activate(bool,class idStr &)
void __thiscall rvPopupWindow::Activate(rvPopupWindow *this, bool activate, idStr *act)
{
  idWindow::Activate(this, activate, act);
  if ( activate )
    rvPopupWindow::UpdateChoice(this);
}

// FUNC: public: virtual void __thiscall rvPopupWindow::StateChanged(bool)
void __thiscall rvPopupWindow::StateChanged(rvPopupWindow *this, bool redraw)
{
  idWindow::StateChanged(this, redraw);
  rvPopupWindow::UpdateChoicesAndVals(this);
  rvPopupWindow::InitVars(this);
  rvPopupWindow::UpdateChoice(this);
}
