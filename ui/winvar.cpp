
// FUNC: public: void __thiscall idWinVar::SetGuiInfo(class idDict *,char const *)
void __thiscall idWinVar::SetGuiInfo(idWinVar *this, idDict *gd, const char *_name)
{
  this->guiDict = gd;
  idWinVar::SetName(this, _name);
}

// FUNC: public: void __thiscall idMultiWinVar::Update(void)
void __thiscall idMultiWinVar::Update(idMultiWinVar *this)
{
  int i; // esi
  idWinVar *v3; // ecx

  for ( i = 0; i < this->num; ++i )
  {
    v3 = this->list[i];
    v3->Update(v3);
  }
}

// FUNC: public: void __thiscall idMultiWinVar::SetGuiInfo(class idDict *)
void __thiscall idMultiWinVar::SetGuiInfo(idMultiWinVar *this, idDict *dict)
{
  int i; // esi
  idWinVar **v4; // edi
  const char *v5; // eax
  idWinVar *v6; // ecx

  for ( i = 0; i < this->num; ++i )
  {
    v4 = &this->list[i];
    v5 = (*v4)->c_str(*v4);
    v6 = *v4;
    v6->guiDict = dict;
    idWinVar::SetName(v6, v5);
  }
}

// FUNC: public: virtual void __thiscall idWinVar::Init(char const *,class idWindow *)
void __thiscall idWinVar::Init(idWinVar *this, const char *_name, idWindow *win)
{
  int v3; // eax
  char *baseBuffer; // edx
  const char *v6; // eax
  int v7; // esi
  const char *v8; // ecx
  char v9; // al
  idStr *v10; // esi
  unsigned int len; // ebp
  int v12; // eax
  char *data; // [esp-4h] [ebp-60h]
  idStr key; // [esp+10h] [ebp-4Ch] BYREF
  idStr result; // [esp+30h] [ebp-2Ch] BYREF
  int v16; // [esp+58h] [ebp-4h]

  v3 = 0;
  baseBuffer = key.baseBuffer;
  key.len = 0;
  key.alloced = 20;
  key.data = key.baseBuffer;
  key.baseBuffer[0] = 0;
  if ( _name )
  {
    v6 = &_name[strlen(_name) + 1];
    v7 = v6 - (_name + 1);
    if ( v6 - _name > 20 )
    {
      idStr::ReAllocate(&key, v6 - _name, 1);
      baseBuffer = key.data;
    }
    v8 = _name;
    do
    {
      v9 = *v8;
      *baseBuffer++ = *v8++;
    }
    while ( v9 );
    baseBuffer = key.data;
    v3 = v7;
    key.len = v7;
  }
  v16 = 0;
  this->guiDict = 0;
  if ( v3 > 5 && *baseBuffer == 103 && baseBuffer[1] == 117 && baseBuffer[2] == 105 && baseBuffer[3] == 58 )
  {
    v10 = idStr::Right(&key, &result, v3 - VAR_GUIPREFIX_LEN_17);
    len = v10->len;
    v12 = v10->len + 1;
    LOBYTE(v16) = 1;
    if ( v12 > key.alloced )
      idStr::ReAllocate(&key, v12, 0);
    qmemcpy(key.data, v10->data, len);
    key.data[len] = 0;
    key.len = len;
    LOBYTE(v16) = 0;
    idStr::FreeData(&result);
    data = key.data;
    this->guiDict = &win->gui->state;
    idWinVar::SetName(this, data);
    idWindow::AddUpdateVar(win, this);
  }
  else
  {
    this->Set(this, _name);
  }
  v16 = -1;
  idStr::FreeData(&key);
}

// FUNC: public: virtual void __thiscall rvVarEditLocal::Init(class idWinVar *,char const *,class idWindow *)
void __thiscall rvVarEditLocal::Init(rvVarEditLocal *this, idWinVar *edit, const char *name, idWindow *window)
{
  idWinVar::Init(edit, name, window);
}
