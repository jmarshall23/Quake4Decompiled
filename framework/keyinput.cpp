
// FUNC: public: static bool __cdecl idKeyInput::GetOverstrikeMode(void)
bool __cdecl idKeyInput::GetOverstrikeMode()
{
  return key_overstrikeMode;
}

// FUNC: public: static void __cdecl idKeyInput::SetOverstrikeMode(bool)
void __cdecl idKeyInput::SetOverstrikeMode(bool state)
{
  key_overstrikeMode = state;
}

// FUNC: public: static bool __cdecl idKeyInput::IsDown(int)
bool __cdecl idKeyInput::IsDown(int keynum)
{
  return keynum != -1 && keys[keynum].down;
}

// FUNC: public: static int __cdecl idKeyInput::StringToKeyNum(char const *)
int __cdecl idKeyInput::StringToKeyNum(const char *str)
{
  int result; // eax
  char v2; // cl
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  keyname_t *v6; // esi

  if ( !str )
    return -1;
  LOBYTE(result) = *str;
  if ( !*str )
    return -1;
  v2 = str[1];
  if ( !v2 )
    return (unsigned __int8)result;
  if ( (_BYTE)result == 48 && v2 == 120 && strlen(str) == 4 )
  {
    v3 = str[2];
    if ( v3 < 48 || v3 > 57 )
    {
      if ( v3 < 97 || v3 > 102 )
        v4 = 0;
      else
        v4 = v3 - 87;
    }
    else
    {
      v4 = v3 - 48;
    }
    v5 = str[3];
    if ( v5 < 48 || v5 > 57 )
    {
      if ( v5 < 97 || v5 > 102 )
        return 16 * v4;
      else
        return v5 - 87 + 16 * v4;
    }
    else
    {
      return v5 - 48 + 16 * v4;
    }
  }
  else
  {
    v6 = keynames;
    if ( keynames[0].name )
    {
      while ( idStr::Icmp(str, v6->name) )
      {
        ++v6;
        if ( !v6->name )
          return -1;
      }
      return v6->keynum;
    }
    else
    {
      return -1;
    }
  }
}

// FUNC: public: static char const * __cdecl idKeyInput::KeyNumToString(int,bool)
char *__cdecl idKeyInput::KeyNumToString(int keynum, bool localized)
{
  keyname_t *v3; // ecx
  char *strId; // eax
  int v5; // ecx
  char v6; // al
  char v7; // cl
  char v8; // al

  if ( keynum == -1 )
    return "<KEY NOT FOUND>";
  if ( (unsigned int)keynum > 0xFF )
    return "<OUT OF RANGE>";
  if ( keynum > 32 && keynum < 127 && keynum != 34 && keynum != 59 && keynum != 39 && keynum != 92 )
    goto LABEL_15;
  v3 = keynames;
  if ( !keynames[0].name )
  {
LABEL_13:
    if ( !localized || keynum < 128 )
    {
      v5 = keynum >> 4;
      v6 = keynum & 0xF;
      tinystr[0] = 48;
      byte_104E89B1 = 120;
      if ( keynum >> 4 <= 9 )
        v7 = v5 + 48;
      else
        v7 = v5 + 87;
      byte_104E89B2 = v7;
      if ( (keynum & 0xFu) <= 9 )
        v8 = v6 + 48;
      else
        v8 = v6 + 87;
      byte_104E89B3 = v8;
      byte_104E89B4 = 0;
      return tinystr;
    }
LABEL_15:
    tinystr[0] = keynum;
    byte_104E89B1 = 0;
    return tinystr;
  }
  while ( keynum != v3->keynum )
  {
    ++v3;
    if ( !v3->name )
      goto LABEL_13;
  }
  if ( localized && (strId = v3->strId, *strId == 35) )
    return (char *)(*(int (__thiscall **)(netadrtype_t, char *, int))(*(_DWORD *)common.type + 168))(
                     common.type,
                     strId,
                     -1);
  else
    return v3->name;
}

// FUNC: public: static void __cdecl idKeyInput::SetBinding(int,char const *)
void __cdecl idKeyInput::SetBinding(int keynum, char *binding)
{
  if ( keynum != -1 )
  {
    usercmdGen->Clear(usercmdGen);
    idStr::operator=(&keys[keynum].binding, binding);
    keys[keynum].usercmdAction = usercmdGen->CommandStringUsercmdData(usercmdGen, binding);
    cvarSystem->SetModifiedFlags(cvarSystem, 0x20000);
  }
}

// FUNC: public: static int __cdecl idKeyInput::GetUsercmdAction(int)
int __cdecl idKeyInput::GetUsercmdAction(int keynum)
{
  return keys[keynum].usercmdAction;
}

// FUNC: void __cdecl Key_Unbindall_f(class idCmdArgs const &)
void __cdecl Key_Unbindall_f()
{
  int i; // esi

  for ( i = 0; i < 11264; i += 44 )
  {
    if ( i != -44 )
    {
      usercmdGen->Clear(usercmdGen);
      idStr::operator=(&keys[i / 0x2Cu].binding, (char *)&entityFilter);
      keys[i / 0x2Cu].usercmdAction = usercmdGen->CommandStringUsercmdData(usercmdGen, &entityFilter);
      cvarSystem->SetModifiedFlags(cvarSystem, 0x20000);
    }
  }
}

// FUNC: public: static void __cdecl idKeyInput::PreliminaryKeyEvent(int,bool)
void __cdecl idKeyInput::PreliminaryKeyEvent(int keynum, bool down)
{
  keys[keynum].down = down;
}

// FUNC: public: static void __cdecl idKeyInput::ClearStates(void)
void __cdecl idKeyInput::ClearStates()
{
  int i; // eax
  idKey *v1; // ecx

  for ( i = 0; i < 256; ++i )
  {
    v1 = keys;
    if ( keys[i].down )
    {
      keys[i].down = 0;
      v1 = keys;
    }
    v1[i].down = 0;
  }
  usercmdGen->Clear(usercmdGen);
}

// FUNC: public: __thiscall idKey::idKey(void)
void __thiscall idKey::idKey(idKey *this)
{
  char *baseBuffer; // ecx

  this->binding.len = 0;
  this->binding.alloced = 20;
  baseBuffer = this->binding.baseBuffer;
  this->binding.data = baseBuffer;
  *baseBuffer = 0;
  this->down = 0;
  this->repeats = 0;
  this->usercmdAction = 0;
}

// FUNC: public: static void __cdecl idKeyInput::ArgCompletion_KeyName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idKeyInput::ArgCompletion_KeyName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  unsigned int i; // esi
  const char *v3; // eax
  const char *v4; // eax
  char *name; // eax
  keyname_t *j; // esi
  const char *v7; // ecx
  const char *v8; // eax

  for ( i = 0; i < 0x2C; ++i )
  {
    if ( args->argc <= 0 )
      v3 = &entityFilter;
    else
      v3 = args->argv[0];
    v4 = va("%s %c", v3, unnamedkeys[i]);
    callback(v4);
  }
  name = keynames[0].name;
  for ( j = keynames; name; ++j )
  {
    if ( args->argc <= 0 )
      v7 = &entityFilter;
    else
      v7 = args->argv[0];
    v8 = va("%s %s", v7, name);
    callback(v8);
    name = j[1].name;
  }
}

// FUNC: public: static char const * __cdecl idKeyInput::GetBinding(int)
char *__cdecl idKeyInput::GetBinding(int keynum)
{
  if ( keynum == -1 )
    return (char *)&entityFilter;
  else
    return keys[keynum].binding.data;
}

// FUNC: void __cdecl Key_Bind_f(class idCmdArgs const &)
void __cdecl Key_Bind_f(const idCmdArgs *args)
{
  const idCmdArgs *v1; // esi
  int argc; // ebp
  const char *v3; // eax
  int v4; // eax
  const char *v5; // eax
  bool v6; // zf
  idKey *v7; // eax
  char *data; // eax
  const char *v9; // ecx
  const char *v10; // eax
  int v11; // ebx
  char **v12; // eax
  const char *v13; // ecx
  const char *v14; // esi
  unsigned int v15; // edx
  char *v16; // edi
  char *v18; // edi
  int b; // [esp+8h] [ebp-404h] BYREF
  char cmd[1024]; // [esp+Ch] [ebp-400h] BYREF

  v1 = args;
  argc = args->argc;
  if ( args->argc >= 2 )
  {
    if ( argc <= 1 )
      v3 = &entityFilter;
    else
      v3 = args->argv[1];
    v4 = idKeyInput::StringToKeyNum(v3);
    b = v4;
    if ( v4 == -1 )
    {
      if ( args->argc <= 1 )
        v5 = &entityFilter;
      else
        v5 = args->argv[1];
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "\"%s\" isn't a valid key\n",
        v5);
    }
    else if ( argc == 2 )
    {
      v6 = keys[v4].binding.len == 0;
      v7 = &keys[v4];
      if ( v6 )
      {
        if ( args->argc <= 1 )
          v10 = &entityFilter;
        else
          v10 = args->argv[1];
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "\"%s\" is not bound\n",
          v10);
      }
      else
      {
        data = v7->binding.data;
        if ( args->argc <= 1 )
          v9 = &entityFilter;
        else
          v9 = args->argv[1];
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "\"%s\" = \"%s\"\n",
          v9,
          data);
      }
    }
    else
    {
      v11 = 2;
      cmd[0] = 0;
      if ( argc > 2 )
      {
        v12 = &args->argv[2];
        while ( 1 )
        {
          v13 = v11 < 0 || v11 >= v1->argc ? &entityFilter : *v12;
          v14 = v13;
          v15 = strlen(v13) + 1;
          v16 = (char *)&b + 3;
          while ( *++v16 )
            ;
          qmemcpy(v16, v14, v15);
          if ( v11 != argc - 1 )
          {
            v18 = (char *)&b + 3;
            while ( *++v18 )
              ;
            strcpy(v18, " ");
          }
          ++v11;
          ++v12;
          if ( v11 >= argc )
            break;
          v1 = args;
        }
        v4 = b;
      }
      idKeyInput::SetBinding(v4, cmd);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "bind <key> [command] : attach a command to a key\n");
  }
}

// FUNC: public: static void __cdecl idKeyInput::WriteBindings(class idFile *)
void __cdecl idKeyInput::WriteBindings(idFile *f)
{
  int i; // ebx
  int v2; // esi
  const char *name; // eax
  keyname_t *v4; // eax
  int v5; // eax
  char v6; // cl
  char v7; // al
  char v8; // cl
  char *data; // esi
  char *v10; // eax
  keyname_t *v11; // eax
  int v12; // eax
  char v13; // cl
  char v14; // al
  char v15; // cl

  f->Printf(f, "unbindall\n");
  for ( i = 0; i < 256; ++i )
  {
    v2 = i;
    if ( keys[i].binding.len )
    {
      if ( i == -1 )
      {
        name = "<KEY NOT FOUND>";
      }
      else if ( i < 0 )
      {
        name = "<OUT OF RANGE>";
      }
      else if ( i <= 32 || i >= 127 || i == 34 || i == 59 || i == 39 || i == 92 )
      {
        v4 = keynames;
        if ( keynames[0].name )
        {
          while ( i != v4->keynum )
          {
            ++v4;
            if ( !v4->name )
              goto LABEL_16;
          }
          name = v4->name;
        }
        else
        {
LABEL_16:
          v5 = i >> 4;
          v6 = i & 0xF;
          tinystr[0] = 48;
          byte_104E89B1 = 120;
          if ( i >> 4 <= 9 )
            v7 = v5 + 48;
          else
            v7 = v5 + 87;
          byte_104E89B2 = v7;
          if ( (i & 0xFu) <= 9 )
            v8 = v6 + 48;
          else
            v8 = v6 + 87;
          byte_104E89B3 = v8;
          byte_104E89B4 = 0;
          name = tinystr;
        }
      }
      else
      {
        tinystr[0] = i;
        byte_104E89B1 = 0;
        name = tinystr;
      }
      if ( idStr::Cmp(name, "\\") )
      {
        data = keys[v2].binding.data;
        if ( i == -1 )
        {
          v10 = "<KEY NOT FOUND>";
        }
        else if ( i < 0 )
        {
          v10 = "<OUT OF RANGE>";
        }
        else if ( i <= 32 || i >= 127 || i == 34 || i == 59 || i == 39 || i == 92 )
        {
          v11 = keynames;
          if ( keynames[0].name )
          {
            while ( i != v11->keynum )
            {
              ++v11;
              if ( !v11->name )
                goto LABEL_40;
            }
            v10 = v11->name;
          }
          else
          {
LABEL_40:
            v12 = i >> 4;
            v13 = i & 0xF;
            tinystr[0] = 48;
            byte_104E89B1 = 120;
            if ( i >> 4 <= 9 )
              v14 = v12 + 48;
            else
              v14 = v12 + 87;
            byte_104E89B2 = v14;
            if ( (i & 0xFu) <= 9 )
              v15 = v13 + 48;
            else
              v15 = v13 + 87;
            byte_104E89B3 = v15;
            byte_104E89B4 = 0;
            v10 = tinystr;
          }
        }
        else
        {
          tinystr[0] = i;
          byte_104E89B1 = 0;
          v10 = tinystr;
        }
        f->Printf(f, "bind \"%s\" \"%s\"\n", v10, data);
      }
      else
      {
        f->Printf(f, "bind \"\\\" \"%s\"\n", keys[v2].binding.data);
      }
    }
  }
}

// FUNC: void __cdecl Key_ListBinds_f(class idCmdArgs const &)
void __cdecl Key_ListBinds_f()
{
  int i; // ebx
  char *data; // edx
  char *name; // eax
  keyname_t *v3; // eax
  int v4; // eax
  char v5; // cl
  char v6; // al
  char v7; // cl

  for ( i = 0; i < 256; ++i )
  {
    if ( keys[i].binding.len )
    {
      data = keys[i].binding.data;
      if ( i == -1 )
      {
        name = "<KEY NOT FOUND>";
      }
      else if ( i < 0 )
      {
        name = "<OUT OF RANGE>";
      }
      else if ( i <= 32 || i >= 127 || i == 34 || i == 59 || i == 39 || i == 92 )
      {
        v3 = keynames;
        if ( keynames[0].name )
        {
          while ( i != v3->keynum )
          {
            ++v3;
            if ( !v3->name )
              goto LABEL_16;
          }
          name = v3->name;
        }
        else
        {
LABEL_16:
          v4 = i >> 4;
          v5 = i & 0xF;
          tinystr[0] = 48;
          byte_104E89B1 = 120;
          if ( i >> 4 <= 9 )
            v6 = v4 + 48;
          else
            v6 = v4 + 87;
          byte_104E89B2 = v6;
          if ( (i & 0xFu) <= 9 )
            v7 = v5 + 48;
          else
            v7 = v5 + 87;
          byte_104E89B3 = v7;
          byte_104E89B4 = 0;
          name = tinystr;
        }
      }
      else
      {
        tinystr[0] = i;
        byte_104E89B1 = 0;
        name = tinystr;
      }
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%s \"%s\"\n",
        name,
        data);
    }
  }
}

// FUNC: public: static bool __cdecl idKeyInput::UnbindBinding(char const *)
char __cdecl idKeyInput::UnbindBinding(const char *binding)
{
  char v1; // bl
  int v2; // edi
  int i; // esi

  v1 = 0;
  if ( binding && *binding )
  {
    v2 = 0;
    for ( i = 0; i < 256; ++i )
    {
      if ( !idStr::Icmp(keys[i].binding.data, binding) )
      {
        idKeyInput::SetBinding(v2, (char *)&entityFilter);
        v1 = 1;
      }
      ++v2;
    }
  }
  return v1;
}

// FUNC: public: static int __cdecl idKeyInput::NumBinds(char const *)
int __cdecl idKeyInput::NumBinds(const char *binding)
{
  int v1; // ebx
  int i; // esi

  v1 = 0;
  if ( binding && *binding )
  {
    for ( i = 0; i < 256; ++i )
    {
      if ( !idStr::Icmp(keys[i].binding.data, binding) )
        ++v1;
    }
  }
  return v1;
}

// FUNC: public: static bool __cdecl idKeyInput::KeyIsBoundTo(int,char const *)
bool __cdecl idKeyInput::KeyIsBoundTo(unsigned int keynum, const char *binding)
{
  return keynum <= 0xFF && idStr::Icmp(keys[keynum].binding.data, binding) == 0;
}

// FUNC: public: static bool __cdecl idKeyInput::ExecKeyBinding(int)
char __cdecl idKeyInput::ExecKeyBinding(int keynum)
{
  idKey *v1; // eax

  v1 = &keys[keynum];
  if ( v1->usercmdAction )
    return 0;
  if ( v1->binding.len )
  {
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, v1->binding.data);
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "\n");
  }
  return 1;
}

// FUNC: void __cdecl Key_Unbind_f(class idCmdArgs const &)
void __cdecl Key_Unbind_f(const idCmdArgs *args)
{
  int v1; // eax
  const char *v2; // eax
  const char *v3; // esi

  if ( args->argc == 2 )
  {
    v1 = idKeyInput::StringToKeyNum(args->argv[1]);
    if ( v1 == -1 )
    {
      if ( args->argc <= 1 )
        v2 = &entityFilter;
      else
        v2 = args->argv[1];
      if ( !idKeyInput::UnbindBinding(v2) )
      {
        if ( args->argc <= 1 )
          v3 = &entityFilter;
        else
          v3 = args->argv[1];
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "\"%s\" isn't a valid key\n",
          v3);
      }
    }
    else
    {
      idKeyInput::SetBinding(v1, (char *)&entityFilter);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "unbind <key> : remove commands from a key\n");
  }
}

// FUNC: void __cdecl Key_BindUnBindTwo_f(class idCmdArgs const &)
void __cdecl Key_BindUnBindTwo_f(const idCmdArgs *args)
{
  const char *v1; // eax
  int v2; // ebp
  const char *v3; // esi
  unsigned int v4; // eax
  int v5; // edi
  int v6; // eax
  char *data; // edx
  const char *v8; // ecx
  char v9; // al
  idStr bind; // [esp+4h] [ebp-2Ch] BYREF
  int v11; // [esp+2Ch] [ebp-4h]

  if ( args->argc >= 3 )
  {
    if ( args->argc <= 1 )
      v1 = &entityFilter;
    else
      v1 = args->argv[1];
    v2 = atoi(v1);
    if ( args->argc <= 2 )
      v3 = &entityFilter;
    else
      v3 = args->argv[2];
    bind.len = 0;
    bind.alloced = 20;
    bind.data = bind.baseBuffer;
    bind.baseBuffer[0] = 0;
    if ( v3 )
    {
      v4 = (unsigned int)&v3[strlen(v3) + 1];
      v5 = v4 - (_DWORD)(v3 + 1);
      v6 = v4 - (_DWORD)v3;
      if ( v6 > 20 )
        idStr::ReAllocate(&bind, v6, 1);
      data = bind.data;
      v8 = v3;
      do
      {
        v9 = *v8;
        *data++ = *v8++;
      }
      while ( v9 );
      bind.len = v5;
    }
    v11 = 0;
    if ( idKeyInput::NumBinds(bind.data) >= 2 && !idKeyInput::KeyIsBoundTo(v2, bind.data) )
      idKeyInput::UnbindBinding(bind.data);
    idKeyInput::SetBinding(v2, bind.data);
    v11 = -1;
    idStr::FreeData(&bind);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "bindunbindtwo <keynum> [command]\n");
  }
}

// FUNC: public: static char const * __cdecl idKeyInput::KeysFromBinding(char const *)
char *__cdecl idKeyInput::KeysFromBinding(const char *bind)
{
  int v1; // esi
  int v2; // edi
  int i; // esi
  const char *v4; // eax
  const char *v5; // eax
  const char *v6; // eax
  char *result; // eax
  char *v8; // ecx
  char v9; // dl
  int v10; // edi

  v1 = keyNum;
  keyName[keyNum][0] = 0;
  if ( bind && *bind )
  {
    v2 = 0;
    for ( i = 0; i < 256; ++i )
    {
      if ( !idStr::Icmp(keys[i].binding.data, bind) )
      {
        if ( keyName[keyNum][0] )
        {
          v4 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                               common.type,
                               "#str_107183",
                               -1);
          idStr::Append(keyName[keyNum], 128, v4);
        }
        v5 = idKeyInput::KeyNumToString(v2, 1);
        idStr::Append(keyName[keyNum], 128, v5);
      }
      ++v2;
    }
    v1 = keyNum;
  }
  if ( !keyName[v1][0] )
  {
    v6 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                         common.type,
                         "#str_107133",
                         -1);
    idStr::Copynz(keyName[keyNum], v6, 128);
    v1 = keyNum;
  }
  result = keyName[v1];
  if ( *result )
  {
    v8 = keyName[v1];
    do
    {
      v9 = *v8;
      v10 = (unsigned __int8)*v8;
      if ( idStr::lowerCaseCharacter[v10] )
        v9 = idStr::lowerCaseCharacter[v10];
      *v8++ = v9;
    }
    while ( *v8 );
  }
  keyNum = (v1 + 1) % 8;
  return result;
}
