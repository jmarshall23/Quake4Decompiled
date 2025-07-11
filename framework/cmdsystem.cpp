
// FUNC: int __cdecl idListSortCompare<struct commandDef_s const *>(struct commandDef_s const * const *,struct commandDef_s const * const *)
unsigned int __cdecl idListSortCompare<commandDef_s const *>(
        const commandDef_s *const *a,
        const commandDef_s *const *b)
{
  return idStr::Icmp((*a)->name, (*b)->name);
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::AddCommand(char const *,void (__cdecl *)(class idCmdArgs const &),int,char const *,void (__cdecl *)(class idCmdArgs const &,void (__cdecl *)(char const *)))
void __thiscall idCmdSystemLocal::AddCommand(
        idCmdSystemLocal *this,
        const char *cmdName,
        void (__cdecl *function)(const idCmdArgs *),
        int flags,
        const char *description,
        void (__cdecl *argCompletion)(const idCmdArgs *, void (__cdecl *)(const char *)))
{
  commandDef_s *commands; // esi
  commandDef_s *v8; // esi

  commands = this->commands;
  if ( commands )
  {
    while ( idStr::Cmp(cmdName, commands->name) )
    {
      commands = commands->next;
      if ( !commands )
        goto LABEL_4;
    }
    if ( function != commands->function )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idCmdSystemLocal::AddCommand: %s already defined\n",
        cmdName);
  }
  else
  {
LABEL_4:
    v8 = (commandDef_s *)Memory::Allocate(0x18u);
    v8->name = Mem_CopyString(cmdName);
    v8->function = function;
    v8->argCompletion = argCompletion;
    v8->flags = flags;
    v8->description = Mem_CopyString(description);
    v8->next = this->commands;
    this->commands = v8;
  }
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::RemoveCommand(char const *)
void __thiscall idCmdSystemLocal::RemoveCommand(idCmdSystemLocal *this, const char *cmdName)
{
  commandDef_s *commands; // esi
  commandDef_s **p_commands; // edi

  commands = this->commands;
  p_commands = &this->commands;
  if ( commands )
  {
    while ( idStr::Cmp(cmdName, commands->name) )
    {
      p_commands = &commands->next;
      commands = commands->next;
      if ( !commands )
        return;
    }
    *p_commands = commands->next;
    Mem_Free(commands->name);
    Mem_Free(commands->description);
    Memory::Free(commands);
  }
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::RemoveFlaggedCommands(int)
void __thiscall idCmdSystemLocal::RemoveFlaggedCommands(idCmdSystemLocal *this, int flags)
{
  commandDef_s *commands; // esi
  commandDef_s **p_commands; // edi

  commands = this->commands;
  p_commands = &this->commands;
  if ( commands )
  {
    do
    {
      if ( (flags & commands->flags) != 0 )
      {
        *p_commands = commands->next;
        Mem_Free(commands->name);
        Mem_Free(commands->description);
        Memory::Free(commands);
      }
      else
      {
        p_commands = &commands->next;
      }
      commands = *p_commands;
    }
    while ( *p_commands );
  }
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::CommandCompletion(void (__cdecl *)(char const *))
void __thiscall idCmdSystemLocal::CommandCompletion(idCmdSystemLocal *this, void (__cdecl *callback)(const char *))
{
  commandDef_s *i; // esi

  for ( i = this->commands; i; i = i->next )
    callback(i->name);
}

// FUNC: private: void __thiscall idCmdSystemLocal::InsertCommandText(char const *)
void __thiscall idCmdSystemLocal::InsertCommandText(idCmdSystemLocal *this, const char *text)
{
  unsigned int v3; // edi
  int textLength; // eax
  int i; // eax

  v3 = strlen(text) + 1;
  textLength = this->textLength;
  if ( (int)(textLength + v3) <= 0x10000 )
  {
    for ( i = textLength - 1; i >= 0; this->textBuf[v3 + 1 + i] = this->textBuf[i + 1] )
      --i;
    SIMDProcessor->Memcpy(SIMDProcessor, this->textBuf, text, v3 - 1);
    *((_BYTE *)&this->textLength + v3 + 3) = 10;
    this->textLength += v3;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idCmdSystemLocal::InsertText: buffer overflow\n");
  }
}

// FUNC: private: void __thiscall idCmdSystemLocal::AppendCommandText(char const *)
void __thiscall idCmdSystemLocal::AppendCommandText(idCmdSystemLocal *this, const char *text)
{
  int v3; // edi
  int textLength; // eax

  v3 = strlen(text);
  textLength = this->textLength;
  if ( textLength + v3 < 0x10000 )
  {
    SIMDProcessor->Memcpy(SIMDProcessor, &this->textBuf[textLength], text, v3);
    this->textLength += v3;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idCmdSystemLocal::AppendText: buffer overflow\n");
  }
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::SetupReloadEngine(class idCmdArgs const &)
void __thiscall idCmdSystemLocal::SetupReloadEngine(idCmdSystemLocal *this, idCmdArgs *args)
{
  this->BufferCommandText(this, CMD_EXEC_APPEND, "reloadEngine\n");
  idCmdArgs::operator=(&this->postReload.argc, (char *)args);
}

// FUNC: private: static void __cdecl idCmdSystemLocal::Echo_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::Echo_f(const idCmdArgs *args)
{
  int argc; // eax
  int v2; // esi
  const char **v3; // edi
  const char *v4; // ecx

  argc = args->argc;
  v2 = 1;
  if ( args->argc > 1 )
  {
    v3 = (const char **)&args->argv[1];
    do
    {
      if ( v2 < 0 || v2 >= argc )
        v4 = &entityFilter;
      else
        v4 = *v3;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s ", v4);
      argc = args->argc;
      ++v2;
      ++v3;
    }
    while ( v2 < args->argc );
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
}

// FUNC: private: static void __cdecl idCmdSystemLocal::Wait_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::Wait_f(const idCmdArgs *args)
{
  if ( args->argc == 2 )
    cmdSystemLocal.wait = atoi(args->argv[1]);
  else
    cmdSystemLocal.wait = 1;
}

// FUNC: private: static void __cdecl idCmdSystemLocal::Parse_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::Parse_f(const idCmdArgs *args)
{
  int argc; // eax
  int v2; // esi
  char **argv; // edi
  const char *v4; // ecx

  argc = args->argc;
  v2 = 0;
  if ( args->argc > 0 )
  {
    argv = args->argv;
    do
    {
      if ( v2 < 0 || v2 >= argc )
        v4 = &entityFilter;
      else
        v4 = *argv;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%i: %s\n", v2, v4);
      argc = args->argc;
      ++v2;
      ++argv;
    }
    while ( v2 < args->argc );
  }
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::ArgCompletion(char const *,void (__cdecl *)(char const *))
void __thiscall idCmdSystemLocal::ArgCompletion(
        idCmdSystemLocal *this,
        const char *cmdString,
        void (__cdecl *callback)(const char *))
{
  commandDef_s *commands; // esi
  const char *v5; // eax
  idCmdArgs args; // [esp+4h] [ebp-904h] BYREF

  args.argc = 0;
  idCmdArgs::TokenizeString(&args, cmdString, 0);
  commands = this->commands;
  if ( commands )
  {
    while ( 1 )
    {
      if ( commands->argCompletion )
      {
        v5 = args.argv[0];
        if ( args.argc <= 0 )
          v5 = &entityFilter;
        if ( !idStr::Icmp(v5, commands->name) )
          break;
      }
      commands = commands->next;
      if ( !commands )
        return;
    }
    commands->argCompletion(&args, callback);
  }
}

// FUNC: private: void __thiscall idCmdSystemLocal::ExecuteTokenizedString(class idCmdArgs const &)
void __thiscall idCmdSystemLocal::ExecuteTokenizedString(idCmdSystemLocal *this, idCmdArgs *args)
{
  const char *v3; // eax
  commandDef_s **p_commands; // ebp
  commandDef_s **p_next; // edi
  commandDef_s *v6; // esi
  const char *v7; // eax
  const char *v8; // ebx
  void (__cdecl *function)(const idCmdArgs *); // esi
  char dest; // [esp+8h] [ebp-10004h] BYREF
  _BYTE v11[2]; // [esp+9h] [ebp-10003h] BYREF
  char s1[65537]; // [esp+Bh] [ebp-10001h] BYREF

  if ( args->argc )
  {
    v3 = idCmdArgs::Args(args, 0, -1, 0);
    idStr::snPrintf(&dest, 0x10000, "%s", v3);
    s1[65533] = 0;
    if ( idStr::Icmpn(&dest, "pb_", 3) )
    {
      p_commands = &this->commands;
      p_next = &this->commands;
      if ( !this->commands )
        goto LABEL_12;
      while ( 1 )
      {
        v6 = *p_next;
        v7 = args->argc <= 0 ? &entityFilter : args->argv[0];
        if ( !idStr::Icmp(v7, v6->name) )
          break;
        p_next = &v6->next;
        if ( !v6->next )
          goto LABEL_12;
      }
      *p_next = v6->next;
      v6->next = *p_commands;
      *p_commands = v6;
      if ( (v6->flags & 0x21) != 0
        && session
        && session->IsMultiplayer(session)
        && !cvarSystem->GetCVarBool(cvarSystem, "net_allowCheats") )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *, char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "Command '%s' not valid in multiplayer mode.\n",
          v6->name);
        return;
      }
      function = v6->function;
      if ( function )
      {
        function(args);
      }
      else
      {
LABEL_12:
        if ( !cvarSystem->Command(cvarSystem, args) )
        {
          if ( args->argc <= 0 )
            v8 = &entityFilter;
          else
            v8 = args->argv[0];
          (*(void (__cdecl **)(netadrtype_t, const char *, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "Unknown command '%s'\n",
            v8);
        }
      }
    }
    else if ( idStr::Cmpn(s1, "sv_", 3) )
    {
      PbClAddEvent(14, &v11[strlen(&dest)] - v11, &dest);
    }
    else
    {
      PbSvAddEvent(14, -1, &v11[strlen(&dest)] - v11, &dest);
    }
  }
}

// FUNC: private: void __thiscall idCmdSystemLocal::ExecuteCommandText(char const *)
void __thiscall idCmdSystemLocal::ExecuteCommandText(idCmdSystemLocal *this, char *text)
{
  idCmdArgs args; // [esp+8h] [ebp-10904h] BYREF
  char dest; // [esp+90Ch] [ebp-10000h] BYREF
  _BYTE v5[2]; // [esp+90Dh] [ebp-FFFFh] BYREF
  char s1[65533]; // [esp+90Fh] [ebp-FFFDh] BYREF

  s1[65532] = 0;
  idStr::snPrintf(&dest, 0x10000, "%s", text);
  if ( idStr::Icmpn(&dest, "pb_", 3) )
  {
    idCmdArgs::TokenizeString(&args, text, 0);
    idCmdSystemLocal::ExecuteTokenizedString(this, &args);
  }
  else if ( idStr::Cmpn(s1, "sv_", 3) )
  {
    PbClAddEvent(14, &v5[strlen(&dest)] - v5, &dest);
  }
  else
  {
    PbSvAddEvent(14, -1, &v5[strlen(&dest)] - v5, &dest);
  }
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::BufferCommandText(enum cmdExecution_t,char const *)
void __thiscall idCmdSystemLocal::BufferCommandText(idCmdSystemLocal *this, cmdExecution_t exec, char *text)
{
  if ( exec )
  {
    if ( exec == CMD_EXEC_INSERT )
    {
      idCmdSystemLocal::InsertCommandText(this, text);
    }
    else if ( exec == CMD_EXEC_APPEND )
    {
      idCmdSystemLocal::AppendCommandText(this, text);
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "idCmdSystemLocal::BufferCommandText: bad exec type");
    }
  }
  else
  {
    idCmdSystemLocal::ExecuteCommandText(this, text);
  }
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::ExecuteCommandBuffer(void)
void __thiscall idCmdSystemLocal::ExecuteCommandBuffer(idCmdSystemLocal *this)
{
  bool v2; // zf
  int v3; // ebp
  char v4; // cl
  unsigned __int8 *textBuf; // ebx
  unsigned __int8 v6; // al
  unsigned __int8 *v7; // eax
  unsigned __int8 *v8; // edx
  int num; // eax
  int v10; // eax
  int v11; // edi
  int v12; // ebp
  int v13; // ebp
  int i; // [esp+4h] [ebp-908h]
  idCmdArgs args; // [esp+8h] [ebp-904h] BYREF

  v2 = this->textLength == 0;
  args.argc = 0;
  if ( !v2 )
  {
    while ( !this->wait )
    {
      v3 = 0;
      v4 = 0;
      textBuf = this->textBuf;
      i = 0;
      if ( this->textLength > 0 )
      {
        do
        {
          v6 = textBuf[v3];
          if ( v6 == 34 )
            ++v4;
          if ( (v4 & 1) == 0 && v6 == 59 )
            break;
          if ( v6 == 10 )
            break;
          if ( v6 == 13 )
            break;
          ++v3;
        }
        while ( v3 < this->textLength );
        i = v3;
      }
      textBuf[v3] = 0;
      if ( idStr::Icmpn((const char *)this->textBuf, "pb_", 3) )
      {
        if ( idStr::Cmp((const char *)this->textBuf, "_execTokenized") )
        {
          idCmdArgs::TokenizeString(&args, (const char *)this->textBuf, 0);
        }
        else
        {
          idCmdArgs::operator=(&args, (char *)this->tokenizedCmds.list);
          num = this->tokenizedCmds.num;
          if ( num > 0 )
          {
            v10 = num - 1;
            v11 = 0;
            this->tokenizedCmds.num = v10;
            if ( v10 > 0 )
            {
              v12 = 0;
              do
              {
                idCmdArgs::operator=(&this->tokenizedCmds.list[v12].argc, (char *)&this->tokenizedCmds.list[v12 + 1]);
                ++v11;
                ++v12;
              }
              while ( v11 < this->tokenizedCmds.num );
              v3 = i;
            }
          }
        }
      }
      else
      {
        v2 = idStr::Cmpn((const char *)&this->textBuf[3], "sv_", 3) == 0;
        v7 = this->textBuf;
        v8 = &this->textBuf[1];
        if ( v2 )
          PbSvAddEvent(14, -1, &v7[strlen((const char *)v7) + 1] - v8, (char *)this->textBuf);
        else
          PbClAddEvent(14, &v7[strlen((const char *)v7) + 1] - v8, (char *)this->textBuf);
      }
      if ( v3 == this->textLength )
      {
        this->textLength = 0;
      }
      else
      {
        v13 = v3 + 1;
        this->textLength -= v13;
        memmove(this->textBuf, &textBuf[v13], this->textLength);
      }
      idCmdSystemLocal::ExecuteTokenizedString(this, &args);
      if ( !this->textLength )
        return;
    }
    --this->wait;
  }
}

// FUNC: public: virtual bool __thiscall idCmdSystemLocal::PostReloadEngine(void)
char __thiscall idCmdSystemLocal::PostReloadEngine(idCmdSystemLocal *this)
{
  idCmdArgs *p_postReload; // esi

  p_postReload = &this->postReload;
  if ( !this->postReload.argc )
    return 0;
  ((void (__stdcall *)(int, idCmdArgs *))this->BufferCommandArgs)(2, &this->postReload);
  p_postReload->argc = 0;
  return 1;
}

// FUNC: private: static void __cdecl idCmdSystemLocal::SystemList_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::SystemList_f(idCmdArgs *args)
{
  idCmdSystemLocal::ListByFlags(args, CMD_FL_SYSTEM);
}

// FUNC: private: static void __cdecl idCmdSystemLocal::RendererList_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::RendererList_f(idCmdArgs *args)
{
  idCmdSystemLocal::ListByFlags(args, CMD_FL_RENDERER);
}

// FUNC: private: static void __cdecl idCmdSystemLocal::SoundList_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::SoundList_f(idCmdArgs *args)
{
  idCmdSystemLocal::ListByFlags(args, CMD_FL_SOUND);
}

// FUNC: private: static void __cdecl idCmdSystemLocal::GameList_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::GameList_f(idCmdArgs *args)
{
  idCmdSystemLocal::ListByFlags(args, CMD_FL_GAME);
}

// FUNC: private: static void __cdecl idCmdSystemLocal::ToolList_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::ToolList_f(idCmdArgs *args)
{
  idCmdSystemLocal::ListByFlags(args, CMD_FL_TOOL);
}

// FUNC: private: static void __cdecl idCmdSystemLocal::Exec_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::Exec_f(const idCmdArgs *args)
{
  int argc; // eax
  bool v2; // zf
  char *v3; // eax
  const char *v4; // esi
  const char *v5; // esi
  char *f; // [esp+Ch] [ebp-30h] BYREF
  idStr filename; // [esp+10h] [ebp-2Ch] BYREF
  int v8; // [esp+38h] [ebp-4h]

  f = 0;
  filename.len = 0;
  filename.alloced = 20;
  filename.data = filename.baseBuffer;
  filename.baseBuffer[0] = 0;
  argc = args->argc;
  v2 = args->argc == 2;
  v8 = 0;
  if ( v2 )
  {
    if ( argc <= 1 )
      v3 = (char *)&entityFilter;
    else
      v3 = args->argv[1];
    idStr::operator=(&filename, v3);
    idStr::DefaultFileExtension(&filename, ".cfg");
    fileSystem->ReadFile(fileSystem, filename.data, (void **)&f, 0);
    if ( f )
    {
      if ( args->argc <= 1 )
        v5 = &entityFilter;
      else
        v5 = args->argv[1];
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "execing %s\n", v5);
      idCmdSystemLocal::InsertCommandText(&cmdSystemLocal, f);
      fileSystem->FreeFile(fileSystem, f);
    }
    else
    {
      if ( args->argc <= 1 )
        v4 = &entityFilter;
      else
        v4 = args->argv[1];
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "couldn't exec %s\n",
        v4);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "exec <filename> : execute a script file\n");
  }
  v8 = -1;
  idStr::FreeData(&filename);
}

// FUNC: private: static void __cdecl idCmdSystemLocal::Vstr_f(class idCmdArgs const &)
void __cdecl idCmdSystemLocal::Vstr_f(const idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // eax

  if ( args->argc == 2 )
  {
    v1 = cvarSystem->GetCVarString(cvarSystem, args->argv[1]);
    v2 = va("%s\n", v1);
    idCmdSystemLocal::AppendCommandText(&cmdSystemLocal, v2);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "vstr <variablename> : execute a variable command\n");
  }
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::Init(void)
void __thiscall idCmdSystemLocal::Init(idCmdSystemLocal *this)
{
  this->AddCommand(this, "listCmds", idCmdSystemLocal::List_f, 2, "lists commands", 0);
  this->AddCommand(this, "listSystemCmds", idCmdSystemLocal::SystemList_f, 2, "lists system commands", 0);
  this->AddCommand(this, "listRendererCmds", idCmdSystemLocal::RendererList_f, 2, "lists renderer commands", 0);
  this->AddCommand(this, "listSoundCmds", idCmdSystemLocal::SoundList_f, 2, "lists sound commands", 0);
  this->AddCommand(this, "listGameCmds", idCmdSystemLocal::GameList_f, 2, "lists game commands", 0);
  this->AddCommand(this, "listToolCmds", idCmdSystemLocal::ToolList_f, 2, "lists tool commands", 0);
  this->AddCommand(
    this,
    "exec",
    idCmdSystemLocal::Exec_f,
    2,
    "executes a config file",
    idCmdSystem::ArgCompletion_ConfigName);
  this->AddCommand(this, "vstr", idCmdSystemLocal::Vstr_f, 2, "inserts the current value of a cvar as command text", 0);
  this->AddCommand(this, "echo", idCmdSystemLocal::Echo_f, 2, "prints text", 0);
  this->AddCommand(this, "parse", idCmdSystemLocal::Parse_f, 2, "prints tokenized string", 0);
  this->AddCommand(
    this,
    "wait",
    idCmdSystemLocal::Wait_f,
    2,
    "delays remaining buffered commands one or more frames",
    0);
  idStr::operator=(&this->completionString, "*");
  this->textLength = 0;
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::ArgCompletion_DeclName(class idCmdArgs const &,void (__cdecl *)(char const *),int)
void __thiscall idCmdSystemLocal::ArgCompletion_DeclName(
        idCmdSystemLocal *this,
        const idCmdArgs *args,
        void (__cdecl *callback)(const char *),
        int type)
{
  int v4; // ebp
  int v5; // edi
  const char *v6; // esi
  unsigned int v7; // eax
  int v8; // ebp
  int v9; // eax
  char *data; // edx
  const char *v11; // ecx
  char v12; // al
  const idStr *v13; // esi
  idDeclManager_vtbl *v14; // eax
  int v15; // eax
  const char *v16; // eax
  char *v17; // [esp-14h] [ebp-90h]
  int num; // [esp+Ch] [ebp-70h]
  idStr a; // [esp+10h] [ebp-6Ch] BYREF
  idStr v20; // [esp+30h] [ebp-4Ch] BYREF
  idStr result; // [esp+50h] [ebp-2Ch] BYREF
  int v22; // [esp+78h] [ebp-4h]

  if ( declManager )
  {
    v4 = declManager->GetNumDecls(declManager, (declType_t)type);
    v5 = 0;
    for ( num = v4; v5 < v4; ++v5 )
    {
      if ( args->argc <= 0 )
        v6 = &entityFilter;
      else
        v6 = args->argv[0];
      a.len = 0;
      a.alloced = 20;
      a.data = a.baseBuffer;
      a.baseBuffer[0] = 0;
      if ( v6 )
      {
        v7 = (unsigned int)&v6[strlen(v6) + 1];
        v8 = v7 - (_DWORD)(v6 + 1);
        v9 = v7 - (_DWORD)v6;
        if ( v9 > 20 )
          idStr::ReAllocate(&a, v9, 1);
        data = a.data;
        v11 = v6;
        do
        {
          v12 = *v11;
          *data++ = *v11++;
        }
        while ( v12 );
        a.len = v8;
        v4 = num;
      }
      v22 = 0;
      v13 = operator+(&result, &a, " ");
      v14 = declManager->__vftable;
      LOBYTE(v22) = 1;
      v15 = (int)v14->DeclByIndex(declManager, (declType_t)type, v5, 0);
      v16 = (const char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v15 + 4) + 4))(*(_DWORD *)(v15 + 4));
      v17 = operator+(&v20, v13, v16)->data;
      LOBYTE(v22) = 2;
      callback(v17);
      LOBYTE(v22) = 1;
      idStr::FreeData(&v20);
      LOBYTE(v22) = 0;
      idStr::FreeData(&result);
      v22 = -1;
      idStr::FreeData(&a);
    }
  }
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::Shutdown(void)
void __thiscall idCmdSystemLocal::Shutdown(idCmdSystemLocal *this)
{
  commandDef_s *i; // edi
  idStr *list; // eax
  char *v4; // edi

  for ( i = this->commands; i; i = this->commands )
  {
    this->commands = i->next;
    Mem_Free(i->name);
    Mem_Free(i->description);
    Memory::Free(i);
  }
  idStr::FreeData(&this->completionString);
  this->completionString.len = 0;
  this->completionString.alloced = 20;
  this->completionString.data = this->completionString.baseBuffer;
  this->completionString.baseBuffer[0] = 0;
  list = this->completionParms.list;
  if ( list )
  {
    v4 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v4);
  }
  this->completionParms.list = 0;
  this->completionParms.num = 0;
  this->completionParms.size = 0;
  if ( this->tokenizedCmds.list )
    Memory::Free(this->tokenizedCmds.list);
  this->tokenizedCmds.list = 0;
  this->tokenizedCmds.num = 0;
  this->tokenizedCmds.size = 0;
  this->postReload.argc = 0;
}

// FUNC: public: virtual void __thiscall idCmdSystemLocal::BufferCommandArgs(enum cmdExecution_t,class idCmdArgs const &)
void __thiscall idCmdSystemLocal::BufferCommandArgs(idCmdSystemLocal *this, cmdExecution_t exec, idCmdArgs *args)
{
  idList<idCmdArgs> *p_tokenizedCmds; // esi
  int size; // eax

  if ( exec )
  {
    if ( exec == CMD_EXEC_APPEND )
    {
      idCmdSystemLocal::AppendCommandText(this, "_execTokenized\n");
      p_tokenizedCmds = &this->tokenizedCmds;
      if ( !p_tokenizedCmds->list )
        idList<idCmdArgs>::Resize(p_tokenizedCmds, p_tokenizedCmds->granularity);
      size = p_tokenizedCmds->size;
      if ( p_tokenizedCmds->num == size )
      {
        if ( !p_tokenizedCmds->granularity )
          p_tokenizedCmds->granularity = 16;
        idList<idCmdArgs>::Resize(
          p_tokenizedCmds,
          size + p_tokenizedCmds->granularity - (size + p_tokenizedCmds->granularity) % p_tokenizedCmds->granularity);
      }
      idCmdArgs::operator=(&p_tokenizedCmds->list[p_tokenizedCmds->num].argc, (char *)args);
      ++p_tokenizedCmds->num;
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "idCmdSystemLocal::BufferCommandArgs: bad exec type");
    }
  }
  else
  {
    idCmdSystemLocal::ExecuteTokenizedString(this, args);
  }
}

// FUNC: public: virtual void __cdecl idCmdSystemLocal::ArgCompletion_FolderExtension(class idCmdArgs const &,void (__cdecl *)(char const *),char const *,bool,...)
void idCmdSystemLocal::ArgCompletion_FolderExtension(
        idCmdSystemLocal *this,
        const idCmdArgs *args,
        void (__cdecl *callback)(const char *),
        const char *folder,
        bool stripFolder,
        ...)
{
  bool v5; // cc
  char *v6; // eax
  int v7; // esi
  int v8; // eax
  char v9; // cl
  char *v10; // edx
  const char *v11; // esi
  int v12; // edi
  char v13; // cl
  int j; // eax
  char *v15; // edx
  idStr *list; // eax
  char *v17; // esi
  char *v18; // eax
  idStr *v19; // esi
  unsigned int v20; // ebx
  int v21; // eax
  const char *data; // esi
  unsigned int v23; // eax
  int v24; // edi
  int v25; // eax
  char *v26; // edx
  const char *v27; // ecx
  char v28; // al
  const idStr *v29; // eax
  const char *v30; // ecx
  const idStr *v31; // eax
  idStr *v32; // esi
  unsigned int v33; // ebx
  int v34; // eax
  int granularity; // esi
  int *v36; // eax
  idStr *v37; // edi
  idStr *v38; // ebx
  const void *v39; // esi
  int num; // edi
  int size; // eax
  int v42; // esi
  idStr *v43; // eax
  char *v44; // esi
  int *v45; // eax
  idStr *v46; // edi
  idStr *v47; // ebx
  const void *v48; // esi
  int v49; // esi
  idStr *v50; // ebx
  const char *v51; // eax
  const char *v52; // esi
  unsigned int v53; // eax
  int v54; // edi
  int v55; // eax
  char *v56; // edx
  const char *v57; // ecx
  char v58; // al
  const idStr *v59; // eax
  const char *v60; // ecx
  idStr *v61; // esi
  unsigned int v62; // ebx
  int v63; // eax
  int v64; // esi
  int *v65; // eax
  idStr *v66; // edi
  idStr *v67; // ebx
  const void *v68; // esi
  int v69; // edi
  int v70; // eax
  int v71; // esi
  idStr *v72; // eax
  char *v73; // esi
  int *v74; // eax
  idStr *v75; // edi
  idStr *v76; // ebx
  const void *v77; // esi
  int v78; // esi
  idStr *v79; // ebx
  int v80; // esi
  int v81; // edi
  char *ptr; // [esp+2Ch] [ebp-10Ch]
  idStr *ptra; // [esp+2Ch] [ebp-10Ch]
  _DWORD *ptrb; // [esp+2Ch] [ebp-10Ch]
  char *ptrc; // [esp+2Ch] [ebp-10Ch]
  unsigned int *v86; // [esp+30h] [ebp-108h]
  char *v87; // [esp+30h] [ebp-108h]
  _BYTE *v88; // [esp+30h] [ebp-108h]
  idStr *v89; // [esp+30h] [ebp-108h]
  int len; // [esp+34h] [ebp-104h]
  unsigned int v91; // [esp+34h] [ebp-104h]
  unsigned int v92; // [esp+34h] [ebp-104h]
  int v93; // [esp+34h] [ebp-104h]
  const char **v94; // [esp+34h] [ebp-104h]
  int v95; // [esp+38h] [ebp-100h]
  int v96; // [esp+38h] [ebp-100h]
  int v97; // [esp+38h] [ebp-100h]
  unsigned int v98; // [esp+3Ch] [ebp-FCh]
  int v99; // [esp+3Ch] [ebp-FCh]
  int v100; // [esp+40h] [ebp-F8h]
  int v101; // [esp+40h] [ebp-F8h]
  idFileList *names; // [esp+44h] [ebp-F4h]
  idFileList *namesa; // [esp+44h] [ebp-F4h]
  int i; // [esp+48h] [ebp-F0h]
  int ia; // [esp+48h] [ebp-F0h]
  idStr name; // [esp+4Ch] [ebp-ECh] BYREF
  idStr string; // [esp+6Ch] [ebp-CCh] BYREF
  idStr path; // [esp+8Ch] [ebp-ACh] BYREF
  idStr parm; // [esp+ACh] [ebp-8Ch] BYREF
  idStr v110; // [esp+CCh] [ebp-6Ch] BYREF
  idStr result; // [esp+ECh] [ebp-4Ch] BYREF
  idStr v112; // [esp+10Ch] [ebp-2Ch] BYREF
  int v113; // [esp+134h] [ebp-4h]
  const char *v114; // [esp+150h] [ebp+18h] BYREF
  va_list va; // [esp+150h] [ebp+18h]
  va_list va1; // [esp+154h] [ebp+1Ch] BYREF

  va_start(va1, stripFolder);
  va_start(va, stripFolder);
  v114 = va_arg(va1, const char *);
  string.len = 0;
  string.alloced = 20;
  string.data = string.baseBuffer;
  string.baseBuffer[0] = 0;
  v5 = args->argc <= 0;
  v113 = 0;
  if ( v5 )
    v6 = (char *)&entityFilter;
  else
    v6 = args->argv[0];
  idStr::operator=(&string, v6);
  v7 = string.len + 1;
  if ( string.len + 2 > string.alloced )
    idStr::ReAllocate(&string, string.len + 2, 1);
  v8 = 0;
  v9 = 32;
  do
  {
    v10 = &string.data[v8++];
    v10[string.len] = v9;
    v9 = src[v8];
  }
  while ( v9 );
  string.len = v7;
  string.data[v7] = 0;
  if ( args->argc <= 1 )
  {
    v11 = &entityFilter;
  }
  else
  {
    v11 = args->argv[1];
    if ( !v11 )
      goto LABEL_15;
  }
  v12 = strlen(v11) + string.len;
  if ( v12 + 1 > string.alloced )
    idStr::ReAllocate(&string, v12 + 1, 1);
  v13 = *v11;
  for ( j = 0; v13; v13 = v11[j] )
  {
    v15 = &string.data[j++];
    v15[string.len] = v13;
  }
  string.len = v12;
  string.data[v12] = 0;
LABEL_15:
  if ( idStr::Icmp(string.data, this->completionString.data) )
  {
    parm.len = 0;
    parm.alloced = 20;
    parm.data = parm.baseBuffer;
    parm.baseBuffer[0] = 0;
    path.alloced = 20;
    path.len = 0;
    path.data = path.baseBuffer;
    path.baseBuffer[0] = 0;
    len = string.len;
    v5 = string.len + 1 <= this->completionString.alloced;
    LOBYTE(v113) = 2;
    if ( !v5 )
      idStr::ReAllocate(&this->completionString, string.len + 1, 0);
    qmemcpy(this->completionString.data, string.data, len);
    this->completionString.data[len] = 0;
    this->completionString.len = len;
    list = this->completionParms.list;
    if ( list )
    {
      v17 = &list[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        list,
        0x20u,
        *(_DWORD *)&list[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v17);
    }
    this->completionParms.list = 0;
    this->completionParms.num = 0;
    this->completionParms.size = 0;
    if ( args->argc <= 1 )
      v18 = (char *)&entityFilter;
    else
      v18 = args->argv[1];
    idStr::operator=(&parm, v18);
    idStr::ExtractFilePath(&parm, &path);
    if ( stripFolder || !path.len )
    {
      v19 = operator+(&name, folder, &path);
      v20 = v19->len;
      v21 = v19->len + 1;
      LOBYTE(v113) = 3;
      if ( v21 > path.alloced )
        idStr::ReAllocate(&path, v21, 0);
      qmemcpy(path.data, v19->data, v20);
      path.data[v20] = 0;
      path.len = v20;
      LOBYTE(v113) = 2;
      idStr::FreeData(&name);
    }
    idStr::StripLeading(&path, 47);
    idStr::StripTrailing(&path, 47);
    names = fileSystem->ListFiles(fileSystem, path.data, "/", 1, 1, 0);
    i = 0;
    if ( names->list.num > 0 )
    {
      v100 = 0;
      do
      {
        data = names->list.list[v100].data;
        name.len = 0;
        name.alloced = 20;
        name.data = name.baseBuffer;
        name.baseBuffer[0] = 0;
        if ( data )
        {
          v23 = (unsigned int)&data[strlen(data) + 1];
          v24 = v23 - (_DWORD)(data + 1);
          v25 = v23 - (_DWORD)data;
          if ( v25 > 20 )
            idStr::ReAllocate(&name, v25, 1);
          v26 = name.data;
          v27 = data;
          do
          {
            v28 = *v27;
            *v26++ = *v27++;
          }
          while ( v28 );
          name.len = v24;
        }
        LOBYTE(v113) = 4;
        if ( stripFolder )
        {
          idStr::StripLeading(&name, folder);
          idStr::StripTrailing(&name, folder);
        }
        else
        {
          idStr::StripLeading(&name, "/");
          idStr::StripTrailing(&name, "/");
        }
        v29 = operator+(&result, " ", &name);
        v5 = args->argc <= 0;
        LOBYTE(v113) = 5;
        if ( v5 )
          v30 = &entityFilter;
        else
          v30 = args->argv[0];
        v31 = operator+(&v110, v30, v29);
        LOBYTE(v113) = 6;
        v32 = operator+(&v112, v31, "/");
        v33 = v32->len;
        v34 = v32->len + 1;
        LOBYTE(v113) = 7;
        if ( v34 > name.alloced )
          idStr::ReAllocate(&name, v34, 0);
        qmemcpy(name.data, v32->data, v33);
        name.data[v33] = 0;
        name.len = v33;
        LOBYTE(v113) = 6;
        idStr::FreeData(&v112);
        LOBYTE(v113) = 5;
        idStr::FreeData(&v110);
        LOBYTE(v113) = 4;
        idStr::FreeData(&result);
        if ( !this->completionParms.list )
        {
          granularity = this->completionParms.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->completionParms.size )
            {
              v5 = granularity < this->completionParms.num;
              this->completionParms.size = granularity;
              if ( v5 )
                this->completionParms.num = granularity;
              v36 = (int *)Memory::Allocate(32 * granularity + 4);
              LOBYTE(v113) = 8;
              if ( v36 )
              {
                v37 = (idStr *)(v36 + 1);
                *v36 = granularity;
                `eh vector constructor iterator'(
                  v36 + 1,
                  0x20u,
                  granularity,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v37 = 0;
              }
              v5 = this->completionParms.num <= 0;
              LOBYTE(v113) = 4;
              this->completionParms.list = v37;
              ptr = 0;
              if ( !v5 )
              {
                v86 = 0;
                do
                {
                  v38 = (idStr *)((char *)v86 + (unsigned int)this->completionParms.list);
                  v91 = *v86;
                  if ( (signed int)(*v86 + 1) > v38->alloced )
                    idStr::ReAllocate(v38, v91 + 1, 0);
                  v39 = (const void *)v86[1];
                  v86 += 8;
                  qmemcpy(v38->data, v39, v91);
                  v38->data[v91] = 0;
                  v38->len = v91;
                  ++ptr;
                }
                while ( (int)ptr < this->completionParms.num );
              }
            }
          }
          else
          {
            this->completionParms.list = 0;
            this->completionParms.num = 0;
            this->completionParms.size = 0;
          }
        }
        num = this->completionParms.num;
        size = this->completionParms.size;
        if ( num == size )
        {
          if ( !this->completionParms.granularity )
            this->completionParms.granularity = 16;
          v42 = size
              + this->completionParms.granularity
              - (size + this->completionParms.granularity) % this->completionParms.granularity;
          if ( v42 > 0 )
          {
            if ( v42 != this->completionParms.size )
            {
              ptra = this->completionParms.list;
              this->completionParms.size = v42;
              if ( v42 < num )
                this->completionParms.num = v42;
              v45 = (int *)Memory::Allocate(32 * v42 + 4);
              LOBYTE(v113) = 9;
              if ( v45 )
              {
                v46 = (idStr *)(v45 + 1);
                *v45 = v42;
                `eh vector constructor iterator'(
                  v45 + 1,
                  0x20u,
                  v42,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v46 = 0;
              }
              v5 = this->completionParms.num <= 0;
              LOBYTE(v113) = 4;
              this->completionParms.list = v46;
              v95 = 0;
              if ( !v5 )
              {
                v87 = 0;
                do
                {
                  v47 = (idStr *)&v87[(unsigned int)this->completionParms.list];
                  v92 = *(int *)((char *)&ptra->len + (_DWORD)v87);
                  if ( (signed int)(v92 + 1) > v47->alloced )
                    idStr::ReAllocate(v47, v92 + 1, 0);
                  v48 = *(char **)((char *)&ptra->data + (_DWORD)v87);
                  v87 += 32;
                  qmemcpy(v47->data, v48, v92);
                  v47->data[v92] = 0;
                  v47->len = v92;
                  ++v95;
                }
                while ( v95 < this->completionParms.num );
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
            v43 = this->completionParms.list;
            if ( v43 )
            {
              v44 = &v43[-1].baseBuffer[16];
              `eh vector destructor iterator'(
                v43,
                0x20u,
                *(_DWORD *)&v43[-1].baseBuffer[16],
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(v44);
            }
            this->completionParms.list = 0;
            this->completionParms.num = 0;
            this->completionParms.size = 0;
          }
        }
        v49 = name.len;
        v50 = &this->completionParms.list[this->completionParms.num];
        v93 = name.len;
        if ( name.len + 1 > v50->alloced )
          idStr::ReAllocate(v50, name.len + 1, 0);
        qmemcpy(v50->data, name.data, v49);
        v50->data[v93] = 0;
        v50->len = v93;
        ++this->completionParms.num;
        LOBYTE(v113) = 2;
        idStr::FreeData(&name);
        ++v100;
        ++i;
      }
      while ( i < names->list.num );
    }
    fileSystem->FreeFileList(fileSystem, names);
    v51 = v114;
    if ( v114 )
    {
      va_copy((va_list)v94, va);
      do
      {
        namesa = fileSystem->ListFiles(fileSystem, path.data, v51, 1, 1, 0);
        ia = 0;
        if ( namesa->list.num > 0 )
        {
          v101 = 0;
          do
          {
            v52 = namesa->list.list[v101].data;
            name.len = 0;
            name.alloced = 20;
            name.data = name.baseBuffer;
            name.baseBuffer[0] = 0;
            if ( v52 )
            {
              v53 = (unsigned int)&v52[strlen(v52) + 1];
              v54 = v53 - (_DWORD)(v52 + 1);
              v55 = v53 - (_DWORD)v52;
              if ( v55 > 20 )
                idStr::ReAllocate(&name, v55, 1);
              v56 = name.data;
              v57 = v52;
              do
              {
                v58 = *v57;
                *v56++ = *v57++;
              }
              while ( v58 );
              name.len = v54;
            }
            LOBYTE(v113) = 10;
            if ( stripFolder )
            {
              idStr::StripLeading(&name, folder);
              idStr::StripTrailing(&name, folder);
            }
            else
            {
              idStr::StripLeading(&name, "/");
              idStr::StripTrailing(&name, "/");
            }
            v59 = operator+(&v110, " ", &name);
            v5 = args->argc <= 0;
            LOBYTE(v113) = 11;
            if ( v5 )
              v60 = &entityFilter;
            else
              v60 = args->argv[0];
            v61 = operator+(&result, v60, v59);
            v62 = v61->len;
            v63 = v61->len + 1;
            LOBYTE(v113) = 12;
            if ( v63 > name.alloced )
              idStr::ReAllocate(&name, v63, 0);
            qmemcpy(name.data, v61->data, v62);
            name.data[v62] = 0;
            name.len = v62;
            LOBYTE(v113) = 11;
            idStr::FreeData(&result);
            LOBYTE(v113) = 10;
            idStr::FreeData(&v110);
            if ( !this->completionParms.list )
            {
              v64 = this->completionParms.granularity;
              if ( v64 > 0 )
              {
                if ( v64 != this->completionParms.size )
                {
                  v5 = v64 < this->completionParms.num;
                  this->completionParms.size = v64;
                  if ( v5 )
                    this->completionParms.num = v64;
                  v65 = (int *)Memory::Allocate(32 * v64 + 4);
                  LOBYTE(v113) = 13;
                  if ( v65 )
                  {
                    v66 = (idStr *)(v65 + 1);
                    *v65 = v64;
                    `eh vector constructor iterator'(
                      v65 + 1,
                      0x20u,
                      v64,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  }
                  else
                  {
                    v66 = 0;
                  }
                  v5 = this->completionParms.num <= 0;
                  LOBYTE(v113) = 10;
                  this->completionParms.list = v66;
                  v96 = 0;
                  if ( !v5 )
                  {
                    ptrb = 0;
                    do
                    {
                      v67 = (idStr *)((char *)ptrb + (unsigned int)this->completionParms.list);
                      v88 = (_BYTE *)*ptrb;
                      if ( *ptrb + 1 > v67->alloced )
                        idStr::ReAllocate(v67, (int)(v88 + 1), 0);
                      v68 = (const void *)ptrb[1];
                      ptrb += 8;
                      qmemcpy(v67->data, v68, (unsigned int)v88);
                      v88[(unsigned int)v67->data] = 0;
                      v67->len = (int)v88;
                      ++v96;
                    }
                    while ( v96 < this->completionParms.num );
                  }
                }
              }
              else
              {
                this->completionParms.list = 0;
                this->completionParms.num = 0;
                this->completionParms.size = 0;
              }
            }
            v69 = this->completionParms.num;
            v70 = this->completionParms.size;
            if ( v69 == v70 )
            {
              if ( !this->completionParms.granularity )
                this->completionParms.granularity = 16;
              v71 = v70
                  + this->completionParms.granularity
                  - (v70 + this->completionParms.granularity) % this->completionParms.granularity;
              if ( v71 > 0 )
              {
                if ( v71 != this->completionParms.size )
                {
                  v89 = this->completionParms.list;
                  this->completionParms.size = v71;
                  if ( v71 < v69 )
                    this->completionParms.num = v71;
                  v74 = (int *)Memory::Allocate(32 * v71 + 4);
                  LOBYTE(v113) = 14;
                  if ( v74 )
                  {
                    v75 = (idStr *)(v74 + 1);
                    *v74 = v71;
                    `eh vector constructor iterator'(
                      v74 + 1,
                      0x20u,
                      v71,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  }
                  else
                  {
                    v75 = 0;
                  }
                  v5 = this->completionParms.num <= 0;
                  LOBYTE(v113) = 10;
                  this->completionParms.list = v75;
                  v97 = 0;
                  if ( !v5 )
                  {
                    ptrc = 0;
                    do
                    {
                      v76 = (idStr *)&ptrc[(unsigned int)this->completionParms.list];
                      v98 = *(_DWORD *)&ptrc[(_DWORD)v89];
                      if ( (signed int)(v98 + 1) > v76->alloced )
                        idStr::ReAllocate(v76, v98 + 1, 0);
                      v77 = *(const void **)&ptrc[(_DWORD)v89 + 4];
                      ptrc += 32;
                      qmemcpy(v76->data, v77, v98);
                      v76->data[v98] = 0;
                      v76->len = v98;
                      ++v97;
                    }
                    while ( v97 < this->completionParms.num );
                  }
                  if ( v89 )
                  {
                    `eh vector destructor iterator'(
                      v89,
                      0x20u,
                      *(_DWORD *)&v89[-1].baseBuffer[16],
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    Memory::Free(&v89[-1].baseBuffer[16]);
                  }
                }
              }
              else
              {
                v72 = this->completionParms.list;
                if ( v72 )
                {
                  v73 = &v72[-1].baseBuffer[16];
                  `eh vector destructor iterator'(
                    v72,
                    0x20u,
                    *(_DWORD *)&v72[-1].baseBuffer[16],
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  Memory::Free(v73);
                }
                this->completionParms.list = 0;
                this->completionParms.num = 0;
                this->completionParms.size = 0;
              }
            }
            v78 = name.len;
            v79 = &this->completionParms.list[this->completionParms.num];
            v99 = name.len;
            if ( name.len + 1 > v79->alloced )
              idStr::ReAllocate(v79, name.len + 1, 0);
            qmemcpy(v79->data, name.data, v78);
            v79->data[v99] = 0;
            v79->len = v99;
            ++this->completionParms.num;
            LOBYTE(v113) = 2;
            idStr::FreeData(&name);
            ++v101;
            ++ia;
          }
          while ( ia < namesa->list.num );
        }
        fileSystem->FreeFileList(fileSystem, namesa);
        v51 = *++v94;
      }
      while ( *v94 );
    }
    LOBYTE(v113) = 1;
    idStr::FreeData(&path);
    LOBYTE(v113) = 0;
    idStr::FreeData(&parm);
  }
  v80 = 0;
  if ( this->completionParms.num > 0 )
  {
    v81 = 0;
    do
    {
      callback(this->completionParms.list[v81].data);
      ++v80;
      ++v81;
    }
    while ( v80 < this->completionParms.num );
  }
  v113 = -1;
  idStr::FreeData(&string);
}
