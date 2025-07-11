
// FUNC: public: void __thiscall idDemo::Shutdown(void)
void __thiscall idDemo::Shutdown(idDemo *this)
{
  this->nextMessageTime = -1;
  this->startTime = -1;
  this->startFrame = -1;
  this->demoState = DEMO_NONE;
  this->timedemo = 0;
  this->file = 0;
  this->ucmd = 0;
  this->usercmd.gameFrame = 0;
  this->usercmd.gameTime = 0;
  this->usercmd.realTime = 0;
  this->usercmd.duplicateCount = 0;
  *(_DWORD *)&this->usercmd.buttons = 0;
  *(_DWORD *)&this->usercmd.upmove = 0;
  *(_DWORD *)&this->usercmd.angles[1] = 0;
  *(_DWORD *)&this->usercmd.mx = 0;
  *(_DWORD *)&this->usercmd.impulse = 0;
  this->usercmd.sequence = 0;
  this->ucmd_offset = 0;
  this->ucmd_start = 0;
  idDict::Clear(&this->userinfo);
}

// FUNC: private: void __thiscall idDemo::WriteHeader(class idFile *)
void __thiscall idDemo::WriteHeader(idDemo *this, idFile *file)
{
  file->WriteInt(file, 1330463822);
  file->WriteInt(file, 7);
  file->WriteInt(file, 131136);
  this->ucmd_offset = file->Tell(file);
  file->WriteInt(file, 0);
  fileSystem->WriteDemoHeader(fileSystem, file);
}

// FUNC: private: int __thiscall idDemo::ReadHeader(class idFile *)
int __thiscall idDemo::ReadHeader(idDemo *this, idFile *file)
{
  idFile *v3; // esi
  int result; // eax
  int v5; // esi
  int version; // [esp+18h] [ebp-8h] BYREF
  int protocol; // [esp+1Ch] [ebp-4h] BYREF

  v3 = file;
  file->ReadInt(file, (int *)&file);
  if ( file == (idFile *)1330463822 )
  {
    v3->ReadInt(v3, &version);
    if ( version == 7 )
    {
      v3->ReadInt(v3, &protocol);
      v3->ReadInt(v3, &this->ucmd_start);
      this->ucmd->Seek(this->ucmd, this->ucmd_start, FS_SEEK_SET);
      result = fileSystem->ReadDemoHeader(fileSystem, v3);
      if ( result != -1 && result )
      {
        v5 = (unsigned __int16)protocol;
        if ( protocol >> 16 == 2 )
        {
          if ( game->ValidateDemoProtocol(game, 64, (unsigned __int16)protocol) )
          {
            return 1;
          }
          else
          {
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "idDemo::ReadHeader: incompatible demo protocol %d.%d ( this build is %d.%d )\n",
              2,
              v5,
              2,
              64);
            return 0;
          }
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "idDemo::ReadHeader: expected protocol %d.%d, got %d.%d\n",
            2,
            64,
            protocol >> 16,
            (unsigned __int16)protocol);
          return 0;
        }
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idDemo::ReadHeader: expected DEMO_VERSION %d, got %d\n",
        7,
        version);
      return 0;
    }
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idDemo::ReadHeader: expected DEMO_IDENT %d, got %d\n",
      1330463822,
      file);
    return 0;
  }
  return result;
}

// FUNC: public: bool __thiscall idDemo::PlayMessage(int,void *,int &,int,int)
char __thiscall idDemo::PlayMessage(idDemo *this, int clientTime, void *data, int *size, int maxSize, int timeOut)
{
  int nextMessageTime; // eax
  int *p_nextMessageTime; // ebx

  if ( this->demoState != DEMO_PLAYING )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idDemo::PlayMessage: called with demoState %d != DEMO_PLAYING\n",
      this->demoState);
    return 0;
  }
  nextMessageTime = this->nextMessageTime;
  p_nextMessageTime = &this->nextMessageTime;
  if ( nextMessageTime < 0 )
  {
    if ( this->file->ReadInt(this->file, &this->nextMessageTime) != 4 )
      goto LABEL_8;
    nextMessageTime = *p_nextMessageTime;
    if ( !*p_nextMessageTime )
      goto LABEL_8;
  }
  if ( timeOut + clientTime <= nextMessageTime )
    return 0;
  this->file->ReadInt(this->file, size);
  if ( this->file->Read(this->file, data, *size) != *size )
  {
LABEL_8:
    session->Stop(session);
    return 0;
  }
  *p_nextMessageTime = -1;
  return 1;
}

// FUNC: public: void __thiscall idDemo::RecordUsercmd(class usercmd_t const &)
void __thiscall idDemo::RecordUsercmd(idDemo *this, const usercmd_t *usercmd)
{
  idAsyncClient::WriteDemoUsercmd(&idAsyncNetwork::client, this->ucmd, usercmd);
}

// FUNC: public: void __thiscall idDemo::RecordMessage(int,class idBitMsg const &)
void __thiscall idDemo::RecordMessage(idDemo *this, int time, const idBitMsg *msg)
{
  this->file->WriteInt(this->file, time);
  this->file->WriteInt(this->file, msg->curSize);
  this->file->Write(this->file, msg->readData, msg->curSize);
}

// FUNC: public: void __thiscall idDemo::ReadUsercmd(int)
void __thiscall idDemo::ReadUsercmd(idDemo *this, int gameFrame)
{
  int v3; // eax
  usercmd_t *p_usercmd; // esi
  int v5; // ebx

  v3 = this->usercmd.gameFrame;
  p_usercmd = &this->usercmd;
  if ( v3 )
  {
    if ( gameFrame == v3 )
    {
      idAsyncClient::SetDemoUsercmd(&idAsyncNetwork::client, &this->usercmd);
      p_usercmd->gameFrame = 0;
      return;
    }
    if ( gameFrame < v3 )
    {
      if ( idDemo::debug.internalVar->integerValue )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "requested ucmd %d, next in stream is %d\n",
          gameFrame,
          v3);
      return;
    }
    if ( idDemo::debug.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "requested ucmd %d, jump buffered %d\n",
        gameFrame,
        v3);
    p_usercmd->gameFrame = 0;
  }
  if ( idAsyncClient::ReadDemoUsercmd(&idAsyncNetwork::client, this->ucmd, p_usercmd) )
  {
    v5 = 0;
    if ( gameFrame <= p_usercmd->gameFrame )
    {
LABEL_19:
      if ( gameFrame == p_usercmd->gameFrame )
      {
        idAsyncClient::SetDemoUsercmd(&idAsyncNetwork::client, p_usercmd);
        p_usercmd->gameFrame = 0;
      }
      else if ( idDemo::debug.internalVar->integerValue )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "requested ucmd %d, next in stream is %d, buffered\n",
          gameFrame,
          p_usercmd->gameFrame);
      }
    }
    else
    {
      while ( idAsyncClient::ReadDemoUsercmd(&idAsyncNetwork::client, this->ucmd, p_usercmd) )
      {
        ++v5;
        if ( gameFrame <= p_usercmd->gameFrame )
        {
          if ( v5 && idDemo::debug.internalVar->integerValue )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "skipped %d ucmds from the stream, to %d in request for %d\n",
              v5,
              p_usercmd->gameFrame,
              gameFrame);
          goto LABEL_19;
        }
      }
      if ( idDemo::debug.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "reached end of usercmd stream\n");
    }
  }
  else if ( idDemo::debug.internalVar->integerValue )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "reached end of usercmd stream\n");
  }
}

// FUNC: public: void __thiscall idDemo::Stop(void)
void __usercall idDemo::Stop(idDemo *this@<ecx>, int a2@<ebp>)
{
  int v3; // eax
  int v4; // edi
  const char *v5; // eax
  int v6; // eax
  idFile *ucmd; // ecx
  const char *v8; // eax
  const char *v9; // edi
  char *v10; // ebp
  _BYTE *alloced; // edx
  const char *v12; // ecx
  char v13; // al
  idFile *v14; // eax
  int v15; // edi
  void *v16; // ebp
  idFile *file; // ecx
  idFile_vtbl *v18; // edx
  int v19; // edi
  int v20; // eax
  float value; // [esp+3Ch] [ebp-68h]
  idStr ucmd_name; // [esp+58h] [ebp-4Ch] BYREF
  idStr sizeStr; // [esp+78h] [ebp-2Ch] BYREF
  int v24; // [esp+A0h] [ebp-4h]
  void *retaddr; // [esp+A4h] [ebp+0h]

  if ( this->demoState == DEMO_RECORDING )
  {
    ((void (__thiscall *)(idFile *, _DWORD, int))this->file->WriteInt)(this->file, 0, a2);
    idAsyncClient::WriteEndUsercmd(&idAsyncNetwork::client, this->ucmd);
    v6 = this->file->Tell(this->file);
    ucmd = this->ucmd;
    this->ucmd_start = v6;
    v8 = ucmd->GetFullPath(ucmd);
    v9 = v8;
    ucmd_name.data = 0;
    *(_DWORD *)ucmd_name.baseBuffer = 20;
    ucmd_name.alloced = (int)&ucmd_name.baseBuffer[4];
    ucmd_name.baseBuffer[4] = 0;
    if ( v8 )
    {
      v10 = (char *)strlen(v8);
      if ( (int)(v10 + 1) > 20 )
        idStr::ReAllocate((idStr *)&ucmd_name.data, (int)(v10 + 1), 1);
      alloced = (_BYTE *)ucmd_name.alloced;
      v12 = v9;
      do
      {
        v13 = *v12;
        *alloced++ = *v12++;
      }
      while ( v13 );
      ucmd_name.data = v10;
    }
    retaddr = 0;
    fileSystem->CloseFile(fileSystem, this->ucmd);
    v14 = fileSystem->OpenExplicitFileRead(fileSystem, ucmd_name.alloced);
    this->ucmd = v14;
    v14->Seek(v14, 0, FS_SEEK_END);
    v15 = this->ucmd->Tell(this->ucmd);
    this->ucmd->Seek(this->ucmd, 0, FS_SEEK_SET);
    v16 = Mem_Alloc(v15, 0xBu);
    if ( this->ucmd->Read(this->ucmd, v16, v15) != v15 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "Short read in idDemo::Stop ( end recording )");
    if ( this->file->Write(this->file, v16, v15) != v15 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "Short write in idDemo::Stop ( end recording )");
    Mem_Free(v16);
    ((void (__thiscall *)(idFile *, int))this->file->Seek)(this->file, this->ucmd_offset);
    this->file->WriteInt(this->file, this->ucmd_start);
    sizeStr.len = 0;
    sizeStr.alloced = 20;
    sizeStr.data = sizeStr.baseBuffer;
    sizeStr.baseBuffer[0] = 0;
    file = this->file;
    v18 = file->__vftable;
    LOBYTE(v24) = 1;
    ucmd_name.len = ((int (__thiscall *)(idFile *, _DWORD))v18->Length)(file, 0);
    value = (float)ucmd_name.len;
    idStr::BestUnit((idStr *)&sizeStr.data, "%.2f", value, (Measure_t)2);
    v19 = *(_DWORD *)common.type;
    v20 = ((int (__thiscall *)(idFile *, int))this->file->GetName)(this->file, sizeStr.alloced);
    (*(void (__cdecl **)(netadrtype_t, const char *, int))(v19 + 124))(
      common.type,
      "stopped network demo recording. '%s' is %s\n",
      v20);
    fileSystem->CloseFile(fileSystem, this->file);
    fileSystem->CloseFile(fileSystem, this->ucmd);
    fileSystem->RemoveExplicitFile(fileSystem, ucmd_name.data);
    idDemo::Shutdown(this);
    LOBYTE(v24) = 0;
    idStr::FreeData(&sizeStr);
    v24 = -1;
    idStr::FreeData(&ucmd_name);
  }
  else if ( this->demoState == DEMO_PLAYING )
  {
    if ( this->timedemo )
    {
      v3 = Sys_Milliseconds();
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%d frames in %d ms: %.2f fps\n",
        com_frameNumber - this->startFrame,
        v3 - this->startTime,
        (double)(com_frameNumber - this->startFrame) * 1000.0 / (double)(v3 - this->startTime));
      soundSystem->SetMute(soundSystem, 0);
    }
    v4 = *(_DWORD *)common.type;
    v5 = this->file->GetName(this->file);
    (*(void (**)(netadrtype_t, const char *, ...))(v4 + 124))(common.type, "stopped demo playback of '%s'\n", v5);
    fileSystem->CloseFile(fileSystem, this->file);
    fileSystem->CloseFile(fileSystem, this->ucmd);
    idAsyncNetwork::client.clientPort.silent = 0;
    idDemo::Shutdown(this);
    cvarSystem->SetCVarsFromDict(cvarSystem, &this->userinfo);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "network demo system is not doing anything");
  }
}

// FUNC: public: void __thiscall idDemo::SessionStop(void)
void __usercall idDemo::SessionStop(idDemo *this@<ecx>, int a2@<ebp>)
{
  if ( this->demoState )
    idDemo::Stop(this, a2);
}

// FUNC: public: static void __cdecl idDemo::Stop_f(class idCmdArgs const &)
void __usercall idDemo::Stop_f(int a1@<ebp>)
{
  if ( idAsyncNetwork::demo.demoState == DEMO_PLAYING )
    session->Stop(session);
  else
    idDemo::Stop(&idAsyncNetwork::demo, a1);
}

// FUNC: public: __thiscall idDemo::idDemo(void)
void __thiscall idDemo::idDemo(idDemo *this)
{
  idDict *p_userinfo; // esi
  idKeyValue *list; // ebp
  int num; // ecx
  int v5; // eax
  int i; // eax
  idKeyValue *v7; // ecx
  idHashIndex *p_argHash; // [esp+10h] [ebp-18h]

  p_userinfo = &this->userinfo;
  this->userinfo.args.granularity = 16;
  this->userinfo.args.list = 0;
  this->userinfo.args.num = 0;
  this->userinfo.args.size = 0;
  p_argHash = &this->userinfo.argHash;
  idHashIndex::Init(&this->userinfo.argHash, 1024, 1024);
  p_userinfo->args.granularity = 16;
  list = p_userinfo->args.list;
  if ( list )
  {
    num = p_userinfo->args.num;
    v5 = p_userinfo->args.num + 15 - (p_userinfo->args.num + 15) % 16;
    if ( v5 != p_userinfo->args.size )
    {
      if ( v5 > 0 )
      {
        p_userinfo->args.size = v5;
        if ( v5 < num )
          p_userinfo->args.num = v5;
        p_userinfo->args.list = (idKeyValue *)Memory::Allocate(8 * v5);
        for ( i = 0; i < p_userinfo->args.num; ++i )
        {
          v7 = p_userinfo->args.list;
          v7[i].key = list[i].key;
          v7[i].value = list[i].value;
        }
        Memory::Free(list);
      }
      else
      {
        Memory::Free(list);
        p_userinfo->args.list = 0;
        p_userinfo->args.num = 0;
        p_userinfo->args.size = 0;
      }
    }
  }
  p_userinfo->argHash.granularity = 16;
  idHashIndex::Free(p_argHash);
  p_argHash->hashSize = 128;
  p_argHash->indexSize = 16;
  this->nextMessageTime = -1;
  this->startTime = -1;
  this->startFrame = -1;
  this->demoState = DEMO_NONE;
  this->timedemo = 0;
  this->file = 0;
  this->ucmd = 0;
  this->usercmd.gameFrame = 0;
  this->usercmd.gameTime = 0;
  this->usercmd.realTime = 0;
  this->usercmd.duplicateCount = 0;
  *(_DWORD *)&this->usercmd.buttons = 0;
  *(_DWORD *)&this->usercmd.upmove = 0;
  *(_DWORD *)&this->usercmd.angles[1] = 0;
  *(_DWORD *)&this->usercmd.mx = 0;
  *(_DWORD *)&this->usercmd.impulse = 0;
  this->usercmd.sequence = 0;
  this->ucmd_offset = 0;
  this->ucmd_start = 0;
  idDict::Clear(&this->userinfo);
}

// FUNC: public: void __thiscall idDemo::Record(class idCmdArgs const &)
void __userpurge idDemo::Record(idDemo *this@<ecx>, int a2@<esi>, const idCmdArgs *args)
{
  bool v4; // zf
  char v5; // bl
  const char *v6; // eax
  int v7; // esi
  int v8; // eax
  char v9; // cl
  char *v10; // edx
  int i; // esi
  int len; // ebx
  idFile *v13; // eax
  char *data; // edx
  int v15; // ebx
  int v16; // esi
  int v17; // eax
  char v18; // cl
  char *v19; // edx
  idFile *v20; // eax
  idDict *userInfo; // esi
  idStr filename; // [esp+24h] [ebp-6Ch] BYREF
  idStr ucmdname; // [esp+44h] [ebp-4Ch] BYREF
  idStr testname; // [esp+64h] [ebp-2Ch] BYREF
  int v26; // [esp+8Ch] [ebp-4h]

  filename.len = 0;
  filename.alloced = 20;
  filename.data = filename.baseBuffer;
  filename.baseBuffer[0] = 0;
  v4 = this->demoState == DEMO_RECORDING;
  v26 = 0;
  if ( v4 )
    idDemo::Stop(this, (int)this);
  if ( this->demoState )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "demo system is currently busy. can't start recording");
LABEL_10:
    v26 = -1;
    idStr::FreeData(&filename);
    return;
  }
  if ( idAsyncNetwork::server.active )
  {
    if ( !idAsyncNetwork::client.active )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "only client side network demo recording is supported");
      goto LABEL_10;
    }
  }
  else if ( !idAsyncNetwork::client.active )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "can only record network demos during network games");
    goto LABEL_10;
  }
  v5 = 1;
  if ( args->argc < 2 )
  {
    idStr::operator=(&filename, "demos/demo");
  }
  else
  {
    if ( args->argc <= 1 )
      v6 = &entityFilter;
    else
      v6 = args->argv[1];
    sprintf(&filename, "demos/%s", v6);
    idStr::StripFileExtension(&filename);
    v7 = filename.len + 8;
    if ( filename.len + 9 > filename.alloced )
      idStr::ReAllocate(&filename, filename.len + 9, 1);
    v8 = 0;
    v9 = 46;
    do
    {
      v10 = &filename.data[v8++];
      v10[filename.len] = v9;
      v9 = aNetdemo[v8];
    }
    while ( v9 );
    filename.len = v7;
    filename.data[v7] = 0;
    if ( fileSystem->ReadFile(fileSystem, filename.data, 0, 0) > 0 )
      idStr::StripFileExtension(&filename);
    else
      v5 = 0;
  }
  testname.len = 0;
  testname.alloced = 20;
  testname.data = testname.baseBuffer;
  testname.baseBuffer[0] = 0;
  ucmdname.len = 0;
  ucmdname.alloced = 20;
  ucmdname.data = ucmdname.baseBuffer;
  ucmdname.baseBuffer[0] = 0;
  LOBYTE(v26) = 2;
  if ( v5 )
  {
    for ( i = 0; i < 999; ++i )
    {
      sprintf(&testname, "%s%03d.netdemo", filename.data, i);
      if ( fileSystem->ReadFile(fileSystem, testname.data, 0, 0) <= 0 )
        break;
    }
    if ( i == 999 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "no demo filename slots left");
      goto LABEL_46;
    }
  }
  else
  {
    len = filename.len;
    if ( filename.len + 1 > 20 )
      idStr::ReAllocate(&testname, filename.len + 1, 0);
    qmemcpy(testname.data, filename.data, len);
    testname.data[len] = 0;
    testname.len = len;
  }
  v13 = fileSystem->OpenFileWrite(fileSystem, testname.data, "fs_savepath", 0);
  this->file = v13;
  if ( v13 )
  {
    v15 = testname.len;
    if ( testname.len + 1 > ucmdname.alloced )
      idStr::ReAllocate(&ucmdname, testname.len + 1, 0);
    qmemcpy(ucmdname.data, testname.data, v15);
    ucmdname.data[v15] = 0;
    ucmdname.len = v15;
    idStr::StripFileExtension(&ucmdname);
    v16 = ucmdname.len + 5;
    if ( ucmdname.len + 6 > ucmdname.alloced )
      idStr::ReAllocate(&ucmdname, ucmdname.len + 6, 1);
    v17 = 0;
    v18 = 46;
    do
    {
      v19 = &ucmdname.data[v17++];
      v19[ucmdname.len] = v18;
      v18 = aUcmd[v17];
    }
    while ( v18 );
    ucmdname.len = v16;
    ucmdname.data[v16] = 0;
    v20 = (idFile *)((int (__thiscall *)(idFileSystem *, char *, const char *, _DWORD, int))fileSystem->OpenFileWrite)(
                      fileSystem,
                      ucmdname.data,
                      "fs_savepath",
                      0,
                      a2);
    this->ucmd = v20;
    if ( v20 )
    {
      this->demoState = DEMO_RECORDING;
      (*(void (__stdcall **)(netadrtype_t))(*(_DWORD *)common.type + 124))(common.type);
      idDemo::WriteHeader(this, this->file);
      idAsyncClient::WriteDemoHeader(&idAsyncNetwork::client, this->file);
      userInfo = sessLocal.mapSpawnData.userInfo;
      do
        idDemo::WriteDict(this, this->file, userInfo++);
      while ( (int)userInfo < (int)sessLocal.mapSpawnData.mapLastUIRequestTime );
      idDemo::WriteDict(this, this->file, &sessLocal.mapSpawnData.serverInfo);
      idDemo::WriteDict(this, this->file, &sessLocal.mapSpawnData.syncedCVars);
      game->SetDemoState(game, DEMO_RECORDING);
      game->WriteClientNetworkInfo(game, this->file, idAsyncNetwork::client.clientNum);
      goto LABEL_46;
    }
    fileSystem->CloseFile(fileSystem, this->file);
    data = ucmdname.data;
    this->file = 0;
  }
  else
  {
    data = testname.data;
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
    common.type,
    "failed to open '%s'",
    data);
LABEL_46:
  LOBYTE(v26) = 1;
  idStr::FreeData(&ucmdname);
  LOBYTE(v26) = 0;
  idStr::FreeData(&testname);
  v26 = -1;
  idStr::FreeData(&filename);
}

// FUNC: public: void __thiscall idDemo::Play(class idCmdArgs const &,bool)
void __userpurge idDemo::Play(idDemo *this@<ecx>, int a2@<edi>, const idCmdArgs *args, bool _timedemo)
{
  int v5; // ebp
  bool v6; // zf
  const char *v7; // ecx
  idFile *v8; // eax
  const char *v9; // eax
  idFile *v10; // eax
  int v11; // edi
  int v12; // eax
  char v13; // cl
  char *v14; // edx
  idFile *v15; // eax
  const char *v16; // eax
  idFile *file; // ecx
  const char *v18; // eax
  idFileSystem_vtbl *v19; // edi
  int v20; // eax
  idFile *v21; // eax
  idFile *v22; // ecx
  int v23; // esi
  int v24; // eax
  int Header; // eax
  int v26; // edi
  int v27; // edi
  const char *v28; // eax
  idDict *v29; // eax
  int DemoHeader; // ebx
  idDict *userInfo; // edi
  idDict *v32; // edi
  int v33; // [esp+24h] [ebp-960h]
  char v34; // [esp+28h] [ebp-95Ch]
  idStr filename; // [esp+34h] [ebp-950h] BYREF
  idStr ucmdname; // [esp+54h] [ebp-930h] BYREF
  idCmdArgs v37; // [esp+74h] [ebp-910h] BYREF
  int v38; // [esp+980h] [ebp-4h]

  v5 = 0;
  filename.len = 0;
  filename.alloced = 20;
  filename.data = filename.baseBuffer;
  filename.baseBuffer[0] = 0;
  v38 = 0;
  ucmdname.len = 0;
  ucmdname.alloced = 20;
  ucmdname.data = ucmdname.baseBuffer;
  ucmdname.baseBuffer[0] = 0;
  v6 = this->demoState == DEMO_NONE;
  LOBYTE(v38) = 1;
  if ( !v6 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "stopping current demo system activity");
    session->Stop(session);
  }
  if ( args->argc == 2 )
  {
    v33 = a2;
    idStr::operator=(&filename, args->argv[1]);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "trying %s\n",
      filename.data);
    v8 = fileSystem->OpenFileRead(fileSystem, filename.data, 1, 0);
    this->file = v8;
    if ( !v8 )
    {
      v9 = args->argc <= 1 ? &entityFilter : args->argv[1];
      sprintf(&filename, "demos/%s", v9);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
        common.type,
        "trying %s\n",
        filename.data);
      v10 = fileSystem->OpenFileRead(fileSystem, filename.data, 1, 0);
      this->file = v10;
      if ( !v10 )
      {
        idStr::StripFileExtension(&filename);
        v11 = filename.len + 8;
        if ( filename.len + 9 > filename.alloced )
          idStr::ReAllocate(&filename, filename.len + 9, 1);
        v12 = 0;
        v13 = 46;
        do
        {
          v14 = &filename.data[v12++];
          v14[filename.len] = v13;
          v13 = aNetdemo[v12];
        }
        while ( v13 );
        filename.len = v11;
        filename.data[v11] = 0;
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
          common.type,
          "trying %s\n",
          filename.data);
        v5 = 0;
        v15 = fileSystem->OpenFileRead(fileSystem, filename.data, 1, 0);
        this->file = v15;
        if ( !v15 )
        {
          (*(void (__stdcall **)(netadrtype_t))(*(_DWORD *)common.type + 132))(common.type);
          if ( args->argc <= 1 )
            v16 = &entityFilter;
          else
            v16 = args->argv[1];
          this->file = fileSystem->OpenExplicitFileRead(fileSystem, v16);
        }
      }
    }
    file = this->file;
    if ( file )
    {
      v19 = fileSystem->__vftable;
      v20 = (int)file->GetFullPath(file);
      v21 = v19->OpenExplicitFileRead(fileSystem, (const char *)v20);
      this->ucmd = v21;
      if ( v21 )
      {
        ((void (__thiscall *)(idSession *, int))session->Stop)(session, v33);
        Header = idDemo::ReadHeader(this, this->file);
        v26 = Header;
        if ( Header == -1 || !Header )
        {
          fileSystem->CloseFile(fileSystem, this->file);
          this->file = 0;
          if ( v26 == -1 )
          {
            v37.argc = 0;
            idCmdArgs::AppendArg(&v37, "playNetDemo");
            idCmdArgs::AppendArg(&v37, filename.data);
            cmdSystem->SetupReloadEngine(cmdSystem, &v37);
          }
        }
        else
        {
          v27 = *(_DWORD *)common.type;
          v28 = this->file->GetFullPath(this->file);
          (*(void (**)(netadrtype_t, const char *, ...))(v27 + 124))(
            common.type,
            "start network demo playback from '%s'\n",
            v28);
          this->demoState = DEMO_PLAYING;
          v29 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 512);
          idDict::operator=(&this->userinfo, v29);
          DemoHeader = idAsyncClient::ReadDemoHeader(&idAsyncNetwork::client, this->file);
          idAsyncNetwork::client.clientPort.silent = 1;
          userInfo = sessLocal.mapSpawnData.userInfo;
          do
            idDemo::ReadDict(this, this->file, userInfo++);
          while ( (int)userInfo < (int)sessLocal.mapSpawnData.mapLastUIRequestTime );
          idDemo::ReadDict(this, this->file, &sessLocal.mapSpawnData.serverInfo);
          idDemo::ReadDict(this, this->file, &sessLocal.mapSpawnData.syncedCVars);
          idSessionLocal::ExecuteMapChange(&sessLocal, DemoHeader, 0, (int)userInfo, (int)this, 0, 0, v34);
          idAsyncClient::CheckDeclChecksum(&idAsyncNetwork::client);
          game->SetDemoState(game, DEMO_PLAYING);
          v32 = sessLocal.mapSpawnData.userInfo;
          do
            game->SetUserInfo(game, v5++, v32++, 1);
          while ( (int)v32 < (int)sessLocal.mapSpawnData.mapLastUIRequestTime );
          cvarSystem->SetCVarsFromDict(cvarSystem, &sessLocal.mapSpawnData.syncedCVars);
          game->ReadClientNetworkInfo(game, DemoHeader, this->file, idAsyncNetwork::client.clientNum);
          this->nextMessageTime = -1;
          this->timedemo = _timedemo;
          if ( _timedemo )
          {
            this->startTime = Sys_Milliseconds();
            this->startFrame = com_frameNumber;
            soundSystem->SetMute(soundSystem, 1);
          }
        }
      }
      else
      {
        v22 = this->file;
        v23 = *(_DWORD *)common.type;
        v24 = (int)v22->GetFullPath(v22);
        (*(void (**)(netadrtype_t, const char *, ...))(v23 + 156))(
          common.type,
          "failed to open a second handle on '%s'",
          v24);
      }
    }
    else
    {
      if ( args->argc <= 1 )
        v18 = &entityFilter;
      else
        v18 = args->argv[1];
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "file not found: %s",
        v18);
    }
    LOBYTE(v38) = 0;
    idStr::FreeData(&ucmdname);
    v38 = -1;
    idStr::FreeData(&filename);
  }
  else
  {
    if ( args->argc <= 0 )
      v7 = &entityFilter;
    else
      v7 = args->argv[0];
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(common.type, "usage: %s <demo>", v7);
    LOBYTE(v38) = 0;
    idStr::FreeData(&ucmdname);
    v38 = -1;
    idStr::FreeData(&filename);
  }
}

// FUNC: public: static void __cdecl idDemo::Record_f(class idCmdArgs const &)
void __usercall idDemo::Record_f(int a1@<esi>, const idCmdArgs *args)
{
  idDemo::Record(&idAsyncNetwork::demo, a1, args);
}

// FUNC: public: static void __cdecl idDemo::Play_f(class idCmdArgs const &)
void __usercall idDemo::Play_f(int a1@<edi>, const idCmdArgs *args)
{
  idDemo::Play(&idAsyncNetwork::demo, a1, args, 0);
}

// FUNC: public: static void __cdecl idDemo::TimeDemo_f(class idCmdArgs const &)
void __usercall idDemo::TimeDemo_f(int a1@<edi>, const idCmdArgs *args)
{
  idDemo::Play(&idAsyncNetwork::demo, a1, args, 1);
}
