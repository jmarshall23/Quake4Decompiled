
// FUNC: private: virtual bool __thiscall idChoiceWindow::ParseInternalVar(char const *,class idParser *)
bool __thiscall idChoiceWindow::ParseInternalVar(idChoiceWindow *this, const char *_name, idParser *src)
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

// FUNC: public: virtual class idWinVar * __thiscall idChoiceWindow::GetWinVarByName(char const *,bool,struct drawWin_t * *)
idWinStr *__thiscall idChoiceWindow::GetWinVarByName(
        idChoiceWindow *this,
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
  if ( idStr::Icmp(_name, "updateGroup") )
    return (idWinStr *)idWindow::GetWinVarByName(this, _name, fixup, owner);
  return &this->updateGroup;
}

// FUNC: private: void __thiscall idChoiceWindow::InitVars(void)
void __thiscall idChoiceWindow::InitVars(idChoiceWindow *this)
{
  idChoiceWindow *v1; // ebx
  idWinVar **list; // eax
  idMultiWinVar *p_updateStr; // esi
  idWinStr *p_cvarName; // edi
  idCVar *v5; // eax
  int v6; // ebp
  char *data; // esi
  char *v8; // ebx
  int v9; // eax
  int granularity; // eax
  bool v11; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v15; // ecx
  idWinVar **v16; // edi
  int j; // eax
  int v18; // eax
  int k; // eax
  int v20; // ebx
  int v21; // eax
  int v22; // ecx
  idWinVar **v23; // edi
  int m; // eax

  v1 = this;
  list = this->updateStr.list;
  p_updateStr = &this->updateStr;
  if ( list )
    Memory::Free(list);
  p_cvarName = &v1->cvarName;
  p_updateStr->list = 0;
  p_updateStr->num = 0;
  p_updateStr->size = 0;
  if ( idWinStr::Length(&v1->cvarName) )
  {
    v5 = cvarSystem->Find(cvarSystem, v1->cvarName.data.data);
    v1->cvar = v5;
    if ( !v5 )
    {
      v6 = *(_DWORD *)common.type;
      data = v1->name.data;
      v8 = v1->gui->source.data;
      v9 = (int)p_cvarName->c_str(p_cvarName);
      (*(void (**)(netadrtype_t, const char *, ...))(v6 + 136))(
        common.type,
        "idChoiceWindow::InitVars: gui '%s' window '%s' references undefined cvar '%s'",
        v8,
        data,
        v9);
      return;
    }
    if ( !p_updateStr->list )
    {
      granularity = p_updateStr->granularity;
      if ( granularity > 0 )
      {
        if ( granularity != p_updateStr->size )
        {
          v11 = granularity < p_updateStr->num;
          p_updateStr->size = granularity;
          if ( v11 )
            p_updateStr->num = granularity;
          p_updateStr->list = (idWinVar **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < p_updateStr->num; ++i )
            p_updateStr->list[i] = *(idWinVar **)(4 * i);
        }
      }
      else
      {
        p_updateStr->list = 0;
        p_updateStr->num = 0;
        p_updateStr->size = 0;
      }
    }
    num = p_updateStr->num;
    size = p_updateStr->size;
    if ( p_updateStr->num == size )
    {
      if ( !p_updateStr->granularity )
        p_updateStr->granularity = 16;
      v15 = size + p_updateStr->granularity - (size + p_updateStr->granularity) % p_updateStr->granularity;
      if ( v15 > 0 )
      {
        if ( v15 != p_updateStr->size )
        {
          v16 = p_updateStr->list;
          p_updateStr->size = v15;
          if ( v15 < num )
            p_updateStr->num = v15;
          p_updateStr->list = (idWinVar **)Memory::Allocate(4 * v15);
          for ( j = 0; j < p_updateStr->num; ++j )
            p_updateStr->list[j] = v16[j];
          if ( v16 )
            Memory::Free(v16);
        }
      }
      else
      {
        if ( p_updateStr->list )
          Memory::Free(p_updateStr->list);
        p_updateStr->list = 0;
        p_updateStr->num = 0;
        p_updateStr->size = 0;
      }
    }
    v1 = this;
    p_updateStr->list[p_updateStr->num++] = &this->cvarStr;
  }
  if ( idWinStr::Length(&v1->guiStr) )
  {
    if ( !p_updateStr->list )
    {
      v18 = p_updateStr->granularity;
      if ( v18 > 0 )
      {
        if ( v18 != p_updateStr->size )
        {
          v11 = v18 < p_updateStr->num;
          p_updateStr->size = v18;
          if ( v11 )
            p_updateStr->num = v18;
          p_updateStr->list = (idWinVar **)Memory::Allocate(4 * v18);
          for ( k = 0; k < p_updateStr->num; ++k )
            p_updateStr->list[k] = *(idWinVar **)(4 * k);
        }
      }
      else
      {
        p_updateStr->list = 0;
        p_updateStr->num = 0;
        p_updateStr->size = 0;
      }
    }
    v20 = p_updateStr->num;
    v21 = p_updateStr->size;
    if ( p_updateStr->num == v21 )
    {
      if ( !p_updateStr->granularity )
        p_updateStr->granularity = 16;
      v22 = v21 + p_updateStr->granularity - (v21 + p_updateStr->granularity) % p_updateStr->granularity;
      if ( v22 > 0 )
      {
        if ( v22 != p_updateStr->size )
        {
          v23 = p_updateStr->list;
          p_updateStr->size = v22;
          if ( v22 < v20 )
            p_updateStr->num = v22;
          p_updateStr->list = (idWinVar **)Memory::Allocate(4 * v22);
          for ( m = 0; m < p_updateStr->num; ++m )
            p_updateStr->list[m] = v23[m];
          if ( v23 )
            Memory::Free(v23);
        }
      }
      else
      {
        if ( p_updateStr->list )
          Memory::Free(p_updateStr->list);
        p_updateStr->list = 0;
        p_updateStr->num = 0;
        p_updateStr->size = 0;
      }
    }
    v1 = this;
    p_updateStr->list[p_updateStr->num++] = &this->guiStr;
  }
  idMultiWinVar::SetGuiInfo(p_updateStr, &v1->gui->state);
  idMultiWinVar::Update(p_updateStr);
}

// FUNC: public: virtual void __thiscall idChoiceWindow::RunNamedEvent(char const *)
void __thiscall idChoiceWindow::RunNamedEvent(idChoiceWindow *this, char *eventName)
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

// FUNC: private: void __thiscall idChoiceWindow::CommonInit(void)
void __thiscall idChoiceWindow::CommonInit(idChoiceWindow *this)
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

// FUNC: public: __thiscall idChoiceWindow::idChoiceWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idChoiceWindow::idChoiceWindow(idChoiceWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idWindow::idWindow(this, d, g);
  this->__vftable = (idChoiceWindow_vtbl *)&idChoiceWindow::`vftable';
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
  idChoiceWindow::CommonInit(this);
}

// FUNC: public: virtual __thiscall idChoiceWindow::~idChoiceWindow(void)
void __thiscall idChoiceWindow::~idChoiceWindow(idChoiceWindow *this)
{
  idWinVar **list; // eax
  idStr *v3; // eax
  char *v4; // edi
  idStr *v5; // eax
  char *v6; // edi
  char *name; // [esp-4h] [ebp-20h]

  this->__vftable = (idChoiceWindow_vtbl *)&idChoiceWindow::`vftable';
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
  idWinStr::~idWinStr(&this->cvarName);
  idWinStr::~idWinStr(&this->cvarStr);
  idWinStr::~idWinStr(&this->guiStr);
  v3 = this->values.list;
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
  this->values.list = 0;
  this->values.num = 0;
  this->values.size = 0;
  v5 = this->choices.list;
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
  this->choices.list = 0;
  this->choices.num = 0;
  this->choices.size = 0;
  idWinStr::~idWinStr(&this->choiceVals);
  idStr::FreeData(&this->latchedVals);
  idWinStr::~idWinStr(&this->choicesStr);
  idStr::FreeData(&this->latchedChoices);
  idWindow::~idWindow(this);
}

// FUNC: private: void __thiscall idChoiceWindow::ValidateChoice(void)
void __thiscall idChoiceWindow::ValidateChoice(idChoiceWindow *this)
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

// FUNC: private: void __thiscall idChoiceWindow::UpdateChoice(void)
void __thiscall idChoiceWindow::UpdateChoice(idChoiceWindow *this)
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
      idChoiceWindow::ValidateChoice(this);
    }
    else
    {
      v4 = *this->updateStr.list;
      if ( v4->guiDict )
      {
        v5 = v4->c_str(v4);
        this->currentChoice = atoi(v5);
      }
      idChoiceWindow::ValidateChoice(this);
    }
  }
}

// FUNC: private: void __thiscall idChoiceWindow::UpdateChoicesAndVals(void)
void __thiscall idChoiceWindow::UpdateChoicesAndVals(idChoiceWindow *this)
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
  char *v99; // [esp-10h] [ebp-190h]
  char *data; // [esp-Ch] [ebp-18Ch]
  char *ptr; // [esp+8h] [ebp-178h]
  idStr *ptra; // [esp+8h] [ebp-178h]
  unsigned int *ptrb; // [esp+8h] [ebp-178h]
  char *ptrc; // [esp+8h] [ebp-178h]
  unsigned int *ptrd; // [esp+8h] [ebp-178h]
  char *ptre; // [esp+8h] [ebp-178h]
  unsigned int *ptrf; // [esp+8h] [ebp-178h]
  char *ptrg; // [esp+8h] [ebp-178h]
  unsigned int v109; // [esp+Ch] [ebp-174h]
  int v110; // [esp+Ch] [ebp-174h]
  unsigned int v111; // [esp+Ch] [ebp-174h]
  unsigned int v112; // [esp+Ch] [ebp-174h]
  int v113; // [esp+Ch] [ebp-174h]
  unsigned int v114; // [esp+Ch] [ebp-174h]
  unsigned int v115; // [esp+Ch] [ebp-174h]
  int v116; // [esp+Ch] [ebp-174h]
  unsigned int v117; // [esp+Ch] [ebp-174h]
  unsigned int v118; // [esp+Ch] [ebp-174h]
  int v119; // [esp+Ch] [ebp-174h]
  unsigned int *v120; // [esp+10h] [ebp-170h]
  char *v121; // [esp+10h] [ebp-170h]
  idStr *v122; // [esp+10h] [ebp-170h]
  idStr *v123; // [esp+10h] [ebp-170h]
  idStr *v124; // [esp+10h] [ebp-170h]
  unsigned int v125; // [esp+14h] [ebp-16Ch]
  int v126; // [esp+14h] [ebp-16Ch]
  int v127; // [esp+14h] [ebp-16Ch]
  int v128; // [esp+14h] [ebp-16Ch]
  int v129; // [esp+14h] [ebp-16Ch]
  int v130; // [esp+14h] [ebp-16Ch]
  int v131; // [esp+14h] [ebp-16Ch]
  int v132; // [esp+14h] [ebp-16Ch]
  bool negNum; // [esp+1Bh] [ebp-165h]
  idStr str2; // [esp+1Ch] [ebp-164h] BYREF
  idToken token; // [esp+3Ch] [ebp-144h] BYREF
  idStr str3; // [esp+8Ch] [ebp-F4h] BYREF
  idLexer src; // [esp+ACh] [ebp-D4h] BYREF
  int v138; // [esp+17Ch] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v138 = 2;
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
  v99 = this->latchedChoices.data;
  LOBYTE(v138) = 3;
  if ( idStr::Icmp(v99, data) )
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
                LOBYTE(v138) = 4;
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
                LOBYTE(v138) = 3;
                this->choices.list = v10;
                ptr = 0;
                if ( !v8 )
                {
                  v120 = 0;
                  do
                  {
                    v11 = (idStr *)((char *)v120 + (unsigned int)this->choices.list);
                    v125 = *v120;
                    if ( (signed int)(*v120 + 1) > v11->alloced )
                      idStr::ReAllocate(v11, v125 + 1, 0);
                    v12 = (const void *)v120[1];
                    v120 += 8;
                    qmemcpy(v11->data, v12, v125);
                    v11->data[v125] = 0;
                    v11->len = v125;
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
                LOBYTE(v138) = 5;
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
                LOBYTE(v138) = 3;
                this->choices.list = v19;
                v126 = 0;
                if ( !v8 )
                {
                  v121 = 0;
                  do
                  {
                    v20 = (idStr *)&v121[(unsigned int)this->choices.list];
                    v109 = *(int *)((char *)&ptra->len + (_DWORD)v121);
                    if ( (signed int)(v109 + 1) > v20->alloced )
                      idStr::ReAllocate(v20, v109 + 1, 0);
                    v21 = *(char **)((char *)&ptra->data + (_DWORD)v121);
                    v121 += 32;
                    qmemcpy(v20->data, v21, v109);
                    v20->data[v109] = 0;
                    v20->len = v109;
                    ++v126;
                  }
                  while ( v126 < this->choices.num );
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
          v110 = str2.len;
          if ( str2.len + 1 > v22->alloced )
            idStr::ReAllocate(v22, str2.len + 1, 0);
          qmemcpy(v22->data, str2.data, len);
          v22->data[v110] = 0;
          v22->len = v110;
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
              LOBYTE(v138) = 6;
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
              LOBYTE(v138) = 3;
              this->choices.list = v34;
              v127 = 0;
              if ( !v8 )
              {
                ptrb = 0;
                do
                {
                  v35 = (idStr *)((char *)ptrb + (unsigned int)this->choices.list);
                  v111 = *ptrb;
                  if ( (signed int)(*ptrb + 1) > v35->alloced )
                    idStr::ReAllocate(v35, v111 + 1, 0);
                  v36 = (const void *)ptrb[1];
                  ptrb += 8;
                  qmemcpy(v35->data, v36, v111);
                  v35->data[v111] = 0;
                  v35->len = v111;
                  ++v127;
                }
                while ( v127 < this->choices.num );
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
              v122 = this->choices.list;
              this->choices.size = v39;
              if ( v39 < v37 )
                this->choices.num = v39;
              v42 = (int *)Memory::Allocate(32 * v39 + 4);
              LOBYTE(v138) = 7;
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
              LOBYTE(v138) = 3;
              this->choices.list = v43;
              v128 = 0;
              if ( !v8 )
              {
                ptrc = 0;
                do
                {
                  v44 = (idStr *)&ptrc[(unsigned int)this->choices.list];
                  v112 = *(int *)((char *)&v122->len + (_DWORD)ptrc);
                  if ( (signed int)(v112 + 1) > v44->alloced )
                    idStr::ReAllocate(v44, v112 + 1, 0);
                  v45 = *(char **)((char *)&v122->data + (_DWORD)ptrc);
                  ptrc += 32;
                  qmemcpy(v44->data, v45, v112);
                  v44->data[v112] = 0;
                  v44->len = v112;
                  ++v128;
                }
                while ( v128 < this->choices.num );
              }
              if ( v122 )
              {
                `eh vector destructor iterator'(
                  v122,
                  0x20u,
                  *(_DWORD *)&v122[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(&v122[-1].baseBuffer[16]);
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
        v113 = str2.len;
        if ( str2.len + 1 > v46->alloced )
          idStr::ReAllocate(v46, str2.len + 1, 0);
        qmemcpy(v46->data, str2.data, v47);
        v46->data[v113] = 0;
        v46->len = v113;
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
                  LOBYTE(v138) = 8;
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
                  LOBYTE(v138) = 3;
                  this->values.list = v55;
                  v129 = 0;
                  if ( !v8 )
                  {
                    v56 = 0;
                    for ( ptrd = 0; ; v56 = ptrd )
                    {
                      v57 = (idStr *)((char *)v56 + (unsigned int)this->values.list);
                      v114 = *v56;
                      if ( (signed int)(*v56 + 1) > v57->alloced )
                        idStr::ReAllocate(v57, v114 + 1, 0);
                      v58 = (const void *)ptrd[1];
                      ptrd += 8;
                      qmemcpy(v57->data, v58, v114);
                      v57->data[v114] = 0;
                      v57->len = v114;
                      if ( ++v129 >= this->values.num )
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
                  v123 = this->values.list;
                  this->values.size = v61;
                  if ( v61 < v59 )
                    this->values.num = v61;
                  v64 = (int *)Memory::Allocate(32 * v61 + 4);
                  LOBYTE(v138) = 9;
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
                  LOBYTE(v138) = 3;
                  this->values.list = v65;
                  v130 = 0;
                  if ( !v8 )
                  {
                    ptre = 0;
                    do
                    {
                      v66 = (idStr *)&ptre[(unsigned int)this->values.list];
                      v115 = *(int *)((char *)&v123->len + (_DWORD)ptre);
                      if ( (signed int)(v115 + 1) > v66->alloced )
                        idStr::ReAllocate(v66, v115 + 1, 0);
                      v67 = *(char **)((char *)&v123->data + (_DWORD)ptre);
                      ptre += 32;
                      qmemcpy(v66->data, v67, v115);
                      v66->data[v115] = 0;
                      v66->len = v115;
                      ++v130;
                    }
                    while ( v130 < this->values.num );
                  }
                  if ( v123 )
                  {
                    `eh vector destructor iterator'(
                      v123,
                      0x20u,
                      *(_DWORD *)&v123[-1].baseBuffer[16],
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    Memory::Free(&v123[-1].baseBuffer[16]);
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
            v116 = str2.len;
            if ( str2.len + 1 > v68->alloced )
              idStr::ReAllocate(v68, str2.len + 1, 0);
            qmemcpy(v68->data, str2.data, v69);
            v68->data[v116] = 0;
            v68->len = v116;
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
              LOBYTE(v138) = 10;
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
              LOBYTE(v138) = 3;
              this->values.list = v84;
              v131 = 0;
              if ( !v8 )
              {
                ptrf = 0;
                do
                {
                  v85 = (idStr *)((char *)ptrf + (unsigned int)this->values.list);
                  v117 = *ptrf;
                  if ( (signed int)(*ptrf + 1) > v85->alloced )
                    idStr::ReAllocate(v85, v117 + 1, 0);
                  v86 = (const void *)ptrf[1];
                  ptrf += 8;
                  qmemcpy(v85->data, v86, v117);
                  v85->data[v117] = 0;
                  v85->len = v117;
                  ++v131;
                }
                while ( v131 < this->values.num );
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
              v124 = this->values.list;
              this->values.size = v89;
              if ( v89 < v87 )
                this->values.num = v89;
              v92 = (int *)Memory::Allocate(32 * v89 + 4);
              LOBYTE(v138) = 11;
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
              LOBYTE(v138) = 3;
              this->values.list = v93;
              v132 = 0;
              if ( !v8 )
              {
                ptrg = 0;
                do
                {
                  v94 = (idStr *)&ptrg[(unsigned int)this->values.list];
                  v118 = *(_DWORD *)&ptrg[(_DWORD)v124];
                  if ( (signed int)(v118 + 1) > v94->alloced )
                    idStr::ReAllocate(v94, v118 + 1, 0);
                  v95 = *(const void **)&ptrg[(_DWORD)v124 + 4];
                  ptrg += 32;
                  qmemcpy(v94->data, v95, v118);
                  v94->data[v118] = 0;
                  v94->len = v118;
                  ++v132;
                }
                while ( v132 < this->values.num );
              }
              if ( v124 )
              {
                `eh vector destructor iterator'(
                  v124,
                  0x20u,
                  *(_DWORD *)&v124[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(&v124[-1].baseBuffer[16]);
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
        v119 = str2.len;
        if ( str2.len + 1 > v96->alloced )
          idStr::ReAllocate(v96, str2.len + 1, 0);
        qmemcpy(v96->data, str2.data, v97);
        v96->data[v119] = 0;
        v96->len = v119;
        ++this->values.num;
      }
    }
    if ( this->choices.num != this->values.num )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "idChoiceWindow:: gui '%s' window '%s' has value count unequal to choices count",
        this->gui->source.data,
        this->name.data);
    v98 = (char *)this->choiceVals.c_str(&this->choiceVals);
    idStr::operator=(&this->latchedVals, v98);
  }
  LOBYTE(v138) = 2;
  idLexer::~idLexer(&src);
  LOBYTE(v138) = 1;
  idStr::FreeData(&str3);
  LOBYTE(v138) = 0;
  idStr::FreeData(&str2);
  v138 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: virtual void __thiscall idChoiceWindow::PostParse(void)
void __thiscall idChoiceWindow::PostParse(idChoiceWindow *this)
{
  const char *v2; // eax
  idWinStr_vtbl *v3; // ebx
  char *v4; // eax
  const idCmdArgs *v5; // [esp+0h] [ebp-4h]

  SpawnStub(v5);
  idChoiceWindow::UpdateChoicesAndVals(this);
  idChoiceWindow::InitVars(this);
  idChoiceWindow::UpdateChoice(this);
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

// FUNC: public: virtual void __thiscall idChoiceWindow::Draw(int,float,float)
void __thiscall idChoiceWindow::Draw(idChoiceWindow *this, int time, float x, float y)
{
  float v5; // edi
  float v6; // ebp
  float z; // ebx
  bool v8; // zf
  idVec4 v9; // [esp-34h] [ebp-60h]
  float v10; // [esp+0h] [ebp-2Ch]
  float v11; // [esp+4h] [ebp-28h]
  idUserInterfaceLocal *gui; // [esp+18h] [ebp-14h]
  float color_12; // [esp+28h] [ebp-4h]

  v5 = this->foreColor.data.x;
  v6 = this->foreColor.data.y;
  z = this->foreColor.data.z;
  color_12 = this->foreColor.data.w;
  idChoiceWindow::UpdateChoicesAndVals(this);
  idChoiceWindow::UpdateChoice(this);
  v8 = this->choices.num == 0;
  this->textAlign = 0;
  if ( !v8 )
  {
    if ( this->hover
      && !this->noEvents.data
      && (gui = this->gui,
          v11 = ((double (*)(void))gui->CursorY)(),
          v10 = gui->CursorX(gui),
          idWindow::Contains(this, v10, v11)) )
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
    if ( (this->flags & 0x20) != 0 )
    {
      v5 = this->hoverColor.data.x;
      v6 = this->hoverColor.data.y;
      z = this->hoverColor.data.z;
      color_12 = this->hoverColor.data.w;
    }
    *(_QWORD *)&v9.x = __PAIR64__(LODWORD(v6), LODWORD(v5));
    *(_QWORD *)&v9.z = __PAIR64__(LODWORD(color_12), LODWORD(z));
    idDeviceContext::DrawTextA(
      this->dc,
      this->choices.list[this->currentChoice].data,
      this->textScale.data,
      0,
      this->textStyle,
      v9,
      this->textRect,
      0,
      -1,
      0,
      0,
      0,
      0,
      0);
  }
}

// FUNC: public: virtual void __thiscall idChoiceWindow::Activate(bool,class idStr &)
void __thiscall idChoiceWindow::Activate(idChoiceWindow *this, bool activate, idStr *act)
{
  idWindow::Activate(this, activate, act);
  if ( activate )
    idChoiceWindow::UpdateChoice(this);
}

// FUNC: private: void __thiscall idChoiceWindow::UpdateValue(void)
void __thiscall idChoiceWindow::UpdateValue(idChoiceWindow *this)
{
  idUserInterfaceLocal_vtbl *v2; // edi
  char *v3; // eax
  int v4; // eax
  idWinStr_vtbl *v5; // ebx
  char *v6; // eax

  v2 = this->gui->idWindow::__vftable;
  v3 = va("%s_sel", this->name.data);
  v4 = v2->GetStateInt(this->gui, v3, "0");
  if ( v4 != this->currentChoice )
  {
    this->currentChoice = v4;
    idChoiceWindow::ValidateChoice(this);
  }
  if ( this->choiceType )
  {
    if ( this->values.num )
    {
      this->cvarStr.Set(&this->cvarStr, this->values.list[this->currentChoice].data);
    }
    else if ( this->choices.num )
    {
      this->cvarStr.Set(&this->cvarStr, this->choices.list[this->currentChoice].data);
    }
  }
  else
  {
    v5 = this->cvarStr.__vftable;
    v6 = va("%i", this->currentChoice);
    v5->Set(&this->cvarStr, v6);
  }
}

// FUNC: public: virtual char const * __thiscall idChoiceWindow::HandleEvent(struct sysEvent_s const *,bool *)
const char *__thiscall idChoiceWindow::HandleEvent(idChoiceWindow *this, const sysEvent_s *event, bool *updateVisuals)
{
  char v4; // bl
  int evValue; // ecx
  idUserInterfaceLocal_vtbl *v8; // edi
  int v9; // edi
  int v10; // ebp
  int v11; // ebx
  char *v12; // eax
  const char *v13; // eax
  idWinStr_vtbl *v14; // ebx
  char *v15; // eax
  int currentChoice; // [esp-4h] [ebp-14h]
  const sysEvent_s *eventa; // [esp+14h] [ebp+4h]

  v4 = 0;
  if ( event->evType == SE_KEY )
  {
    if ( !event->evValue2 )
    {
      this->RunScript(this, 9);
      return this->cmd.data;
    }
    evValue = event->evValue;
    if ( evValue == 136 || evValue == 170 || evValue == 187 )
    {
      if ( ++this->currentChoice >= this->choices.num )
        this->currentChoice = 0;
      v4 = 1;
    }
    if ( evValue == 199 )
    {
      if ( ++this->currentChoice >= this->choices.num )
        this->currentChoice = 0;
    }
    else
    {
      if ( evValue != 135 && evValue != 168 && evValue != 188 )
        goto LABEL_19;
      if ( --this->currentChoice < 0 )
        this->currentChoice = this->choices.num - 1;
    }
    v4 = 1;
LABEL_19:
    v8 = this->gui->idWindow::__vftable;
    currentChoice = this->currentChoice;
    goto LABEL_27;
  }
  if ( event->evType != SE_CHAR )
    return &entityFilter;
  v9 = 0;
  eventa = (const sysEvent_s *)event->evValue;
  if ( this->choices.num > 0 )
  {
    v10 = 0;
    while ( 1 )
    {
      v11 = toupper(*this->choices.list[v10].data);
      if ( toupper((int)eventa) == v11 )
        break;
      ++v9;
      ++v10;
      if ( v9 >= this->choices.num )
        goto LABEL_25;
    }
    if ( v9 == -1 || this->currentChoice == v9 )
    {
LABEL_25:
      v4 = 0;
      goto LABEL_26;
    }
    this->currentChoice = v9;
    v4 = 1;
  }
LABEL_26:
  v8 = this->gui->idWindow::__vftable;
  currentChoice = this->currentChoice;
LABEL_27:
  v12 = va("%s_sel", this->name.data);
  v8->SetStateInt(this->gui, v12, currentChoice);
  if ( v4 )
    this->RunScript(this, 2);
  idChoiceWindow::UpdateValue(this);
  if ( this->liveUpdate.data )
  {
    if ( this->cvar && this->cvarStr.guiDict )
    {
      v13 = this->cvarStr.c_str(&this->cvarStr);
      this->cvar->internalVar->InternalSetString(this->cvar->internalVar, v13);
    }
    if ( this->guiStr.guiDict )
    {
      v14 = this->guiStr.__vftable;
      v15 = va("%i", this->currentChoice);
      v14->Set(&this->guiStr, v15);
    }
  }
  return this->cmd.data;
}

// FUNC: public: virtual void __thiscall idChoiceWindow::StateChanged(bool)
void __thiscall idChoiceWindow::StateChanged(idChoiceWindow *this, bool redraw)
{
  idWindow::StateChanged(this, redraw);
  idChoiceWindow::UpdateChoicesAndVals(this);
  idChoiceWindow::UpdateValue(this);
  idChoiceWindow::UpdateChoice(this);
}
