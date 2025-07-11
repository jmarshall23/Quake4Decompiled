
// FUNC: public: virtual void __thiscall idSessionLocal::PrecacheMPSettingsMenu(void)
void __thiscall idSessionLocal::PrecacheMPSettingsMenu(idSessionLocal *this)
{
  this->guiMPSettings = uiManager->FindGui(uiManager, "guis/mpsettings.gui", 1, 0, 1);
  idSessionLocal::SetMainMenuMPModelVars(this);
  idSessionLocal::SetMainMenuCrosshairVars(this);
}

// FUNC: public: virtual char const * __thiscall idSessionLocal::KeysFromBinding(char const *)
char *__thiscall idSessionLocal::KeysFromBinding(idSessionLocal *this, const char *bind)
{
  return idKeyInput::KeysFromBinding(bind);
}

// FUNC: public: bool __thiscall idSessionLocal::MaybeWaitOnCDKey(void)
char __thiscall idSessionLocal::MaybeWaitOnCDKey(idSessionLocal *this)
{
  const char *v1; // eax

  if ( this->authEmitTimeout <= 0 )
    return 0;
  this->authWaitBox = 1;
  v1 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                       common.type,
                       "#str_107191",
                       -1);
  idSessionLocal::MessageBoxA(&sessLocal, MSG_WAIT, v1, 0, 1, 0, 0, 1);
  return 1;
}

// FUNC: public: void __thiscall idSessionLocal::CompleteWipe(void)
void __thiscall idSessionLocal::CompleteWipe(idSessionLocal *this)
{
  idSessionLocal_vtbl *v2; // eax

  if ( com_ticNumber )
  {
    while ( com_ticNumber < this->wipeStopTic )
      this->UpdateScreen(this, 1);
  }
  else
  {
    v2 = this->__vftable;
    this->wipeStopTic = 0;
    ((void (__stdcall *)(int))v2->UpdateScreen)(1);
  }
}

// FUNC: public: void __thiscall idSessionLocal::ShowLoadingGui(void)
void __thiscall idSessionLocal::ShowLoadingGui(idSessionLocal *this)
{
  int v1; // edi
  int v2; // esi
  int v3; // ecx

  if ( com_ticNumber )
  {
    console->Close(console);
    v1 = Sys_Milliseconds() + 1000;
    v2 = 10;
    while ( 1 )
    {
      if ( Sys_Milliseconds() >= v1 )
      {
        v3 = v2--;
        if ( v3 <= 0 )
          break;
      }
      com_frameTime = com_ticNumber * (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
      soundSystem->Frame(soundSystem);
      session->Frame(session);
      session->UpdateScreen(session, 0);
    }
  }
}

// FUNC: Session_ExitCmdDemo_f
void __cdecl Session_ExitCmdDemo_f()
{
  if ( sessLocal.cmdDemoFile )
  {
    fileSystem->CloseFile(fileSystem, sessLocal.cmdDemoFile);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Command demo exited at logIndex %i\n",
      sessLocal.logIndex);
    sessLocal.cmdDemoFile = 0;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "not reading from a cmdDemo\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::StopRecordingRenderDemo(void)
void __thiscall idSessionLocal::StopRecordingRenderDemo(idSessionLocal *this)
{
  int v2; // edi
  const char *v3; // eax
  idDemoFile *writeDemo; // ecx

  if ( this->writeDemo )
  {
    soundSystem->StopWritingDemo(soundSystem, 1);
    this->rw->StopWritingDemo(this->rw);
    v2 = *(_DWORD *)common.type;
    v3 = this->writeDemo->GetName(this->writeDemo);
    (*(void (**)(netadrtype_t, const char *, ...))(v2 + 124))(common.type, "stopped recording %s.\n", v3);
    idDemoFile::Close(this->writeDemo);
    writeDemo = this->writeDemo;
    if ( writeDemo )
      ((void (__thiscall *)(idDemoFile *, int))writeDemo->~idDemoFile)(writeDemo, 1);
    this->writeDemo = 0;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idSessionLocal::StopRecordingRenderDemo: not recording\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::SaveCmdDemoToFile(class idFile *)
void __thiscall idSessionLocal::SaveCmdDemoToFile(idSessionLocal *this, idFile *file)
{
  idDict *persistentPlayerInfo; // edi
  int v4; // ebp

  idDict::WriteToFileHandle(&this->mapSpawnData.serverInfo, file);
  persistentPlayerInfo = this->mapSpawnData.persistentPlayerInfo;
  v4 = 32;
  do
  {
    idDict::WriteToFileHandle((idDict *)((char *)persistentPlayerInfo - 1568), file);
    idDict::WriteToFileHandle(persistentPlayerInfo++, file);
    --v4;
  }
  while ( v4 );
  file->Write(file, this->mapSpawnData.mapSpawnUsercmd, 1280);
  if ( this->numClients < 1 )
    this->numClients = 1;
  file->Write(file, this->loggedUsercmds, 44 * this->numClients * this->logIndex);
}

// FUNC: public: void __thiscall idSessionLocal::LoadCmdDemoFromFile(class idFile *)
void __thiscall idSessionLocal::LoadCmdDemoFromFile(idSessionLocal *this, idFile *file)
{
  idDict *persistentPlayerInfo; // esi
  int v4; // ebx

  idDict::ReadFromFileHandle(&this->mapSpawnData.serverInfo, file);
  persistentPlayerInfo = this->mapSpawnData.persistentPlayerInfo;
  v4 = 32;
  do
  {
    idDict::ReadFromFileHandle((idDict *)((char *)persistentPlayerInfo - 1568), file);
    idDict::ReadFromFileHandle(persistentPlayerInfo++, file);
    --v4;
  }
  while ( v4 );
  file->Read(file, this->mapSpawnData.mapSpawnUsercmd, 1280);
}

// FUNC: public: void __thiscall idSessionLocal::WriteCmdDemo(char const *,bool)
void __thiscall idSessionLocal::WriteCmdDemo(idSessionLocal *this, const char *demoName, bool save)
{
  idFile *v4; // eax
  idFile *v5; // esi

  if ( *demoName )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "writing save data to %s\n",
      demoName);
    v4 = fileSystem->OpenFileWrite(fileSystem, demoName, "fs_savepath", 0);
    v5 = v4;
    if ( v4 )
    {
      if ( save )
        v4->Write(v4, &this->logIndex, 4);
      idSessionLocal::SaveCmdDemoToFile(this, v5);
      fileSystem->CloseFile(fileSystem, v5);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Couldn't open for writing %s\n",
        demoName);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idSessionLocal::WriteCmdDemo: no name specified\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::TakeNotes(char const *)
void __thiscall idSessionLocal::TakeNotes(idSessionLocal *this, const char *p)
{
  idUserInterface *guiTakeNotes; // eax

  if ( this->mapSpawned )
  {
    if ( idStr::Icmp(p, "initQA") )
    {
      if ( idStr::Icmp(p, "init2") )
        guiTakeNotes = this->guiTakeNotes;
      else
        guiTakeNotes = this->guiBuildNotes;
    }
    else
    {
      guiTakeNotes = this->guiQANotes;
    }
    this->SetGUI(this, guiTakeNotes, 0);
    console->Close(console);
    idSessionLocal::HandleNoteCommands(this, p);
    this->guiActive->Activate(this->guiActive, 1, com_frameTime);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "No map loaded!\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::EditCVars(char const *)
void __thiscall idSessionLocal::EditCVars(idSessionLocal *this, const char *p)
{
  idUserInterface *guiEditCVars; // eax

  if ( this->mapSpawned )
  {
    guiEditCVars = this->guiEditCVars;
    if ( this->guiActive == guiEditCVars )
    {
      this->guiActive = 0;
    }
    else
    {
      this->SetGUI(this, guiEditCVars, 0);
      console->Close(console);
      idSessionLocal::DispatchCommand(this, this->guiActive, "Init", 0);
      this->guiActive->Activate(this->guiActive, 1, com_frameTime);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "No map loaded!\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::SpawnGUI(char const *)
void __thiscall idSessionLocal::SpawnGUI(idSessionLocal *this, const char *p)
{
  if ( this->mapSpawned )
  {
    this->SetGUI(this, this->guiSpawn, 0);
    console->Close(console);
    idSessionLocal::DispatchCommand(this, this->guiActive, "Init", 0);
    this->guiActive->Activate(this->guiActive, 1, com_frameTime);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "No map loaded!\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::DedicatedGUI(void)
void __thiscall idSessionLocal::DedicatedGUI(idSessionLocal *this)
{
  if ( this->mapSpawned )
  {
    this->SetGUI(this, this->guiDedicated, 0);
    console->Close(console);
    idSessionLocal::DispatchCommand(this, this->guiActive, "Init", 0);
    this->guiActive->Activate(this->guiActive, 1, com_frameTime);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "No map loaded!\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::XboxInGameGUI(void)
void __thiscall idSessionLocal::XboxInGameGUI(idSessionLocal *this)
{
  if ( this->mapSpawned )
  {
    this->SetGUI(this, this->guiXboxInGame, 0);
    soundSystem->SetActiveSoundWorld(soundSystem, 1);
    console->Close(console);
    idSessionLocal::DispatchCommand(this, this->guiActive, "Init", 0);
    this->guiActive->Activate(this->guiActive, 1, com_frameTime);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "No map loaded!\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::ScrubSaveGameFileName(class idStr &)const
void __thiscall idSessionLocal::ScrubSaveGameFileName(idSessionLocal *this, idStr *saveFileName)
{
  idStr::ScrubFileName(saveFileName);
}

// FUNC: public: void __thiscall idSessionLocal::DrawWipeModel(void)
void __thiscall idSessionLocal::DrawWipeModel(idSessionLocal *this)
{
  volatile int wipeStopTic; // eax
  float v3; // [esp+0h] [ebp-14h]

  wipeStopTic = this->wipeStopTic;
  if ( this->wipeStartTic < wipeStopTic && (this->wipeHold || com_ticNumber < wipeStopTic) )
  {
    v3 = (double)(com_ticNumber - this->wipeStartTic) / (double)(wipeStopTic - this->wipeStartTic);
    ((void (__stdcall *)(int, int, int, _DWORD))renderSystem->SetColor4)(
      1065353216,
      1065353216,
      1065353216,
      LODWORD(v3));
    (*((void (__thiscall **)(idRenderSystem *, _DWORD, _DWORD, int, int, _DWORD, _DWORD, int, int, const idMaterial *))&renderSystem->SetColor4
     + 1))(
      renderSystem,
      0,
      0,
      1142947840,
      1139802112,
      0,
      0,
      1065353216,
      1065353216,
      this->wipeMaterial);
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::PacifierUpdate(void)
void __thiscall idSessionLocal::PacifierUpdate(idSessionLocal *this)
{
  int v2; // eax
  bool v3; // zf
  float v4; // [esp+0h] [ebp-Ch]

  if ( this->insideExecuteMapChange && !this->insideUpdateScreen )
  {
    v2 = idEventLoop::Milliseconds(eventLoop);
    if ( v2 - this->lastPacifierTime >= 100 )
    {
      v3 = this->guiLoading == 0;
      this->lastPacifierTime = v2;
      if ( !v3 )
      {
        if ( this->bytesNeededForMapLoad )
        {
          v4 = (double)fileSystem->GetReadCount(fileSystem) / (double)this->bytesNeededForMapLoad;
          ((void (__stdcall *)(const char *, _DWORD))this->guiLoading->SetStateFloat)("map_loading", LODWORD(v4));
          this->guiLoading->StateChanged(this->guiLoading, com_frameTime, 0);
        }
      }
      Sys_GenerateEvents();
      this->UpdateScreen(this, 1);
      idAsyncClient::PacifierUpdate(&idAsyncNetwork::client);
      idAsyncServer::PacifierUpdate(&idAsyncNetwork::server);
    }
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::TimeHitch(int)
void __thiscall idSessionLocal::TimeHitch(idSessionLocal *this, int msec)
{
  this->timeHitch += msec;
}

// FUNC: public: virtual void __thiscall idSessionLocal::ReadCDKey(void)
void __thiscall idSessionLocal::ReadCDKey(idSessionLocal *this)
{
  idFileSystem_vtbl *v2; // esi
  int v3; // eax
  const char *v4; // ebp
  idFile *v5; // eax
  idFile *v6; // esi
  char buffer[21]; // [esp+20h] [ebp-18h] BYREF

  this->cdkey_state = CDKEY_UNKNOWN;
  v2 = fileSystem->__vftable;
  v3 = ((int (__thiscall *)(idCVarSystem *, const char *, const char *, const char *))cvarSystem->GetCVarString)(
         cvarSystem,
         "fs_basepath",
         "q4base",
         "quake4key");
  v4 = (const char *)((int (__thiscall *)(idFileSystem *, int))v2->BuildOSPath)(fileSystem, v3);
  v5 = fileSystem->OpenExplicitFileRead(fileSystem, v4);
  v6 = v5;
  if ( v5 )
  {
    memset(buffer, 0, sizeof(buffer));
    v5->Read(v5, buffer, 21);
    fileSystem->CloseFile(fileSystem, v6);
    idStr::Copynz(this->cdkey, buffer, 21);
    this->cdkey[21] = 0;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't read %s.\n",
      v4);
    this->cdkey[0] = 0;
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::ClearCDKey(bool)
void __thiscall idSessionLocal::ClearCDKey(idSessionLocal *this, bool valid)
{
  if ( valid )
  {
    if ( this->cdkey_state == CDKEY_CHECKING )
      this->cdkey_state = CDKEY_OK;
    this->WriteCDKey(this);
  }
  else
  {
    *(_DWORD *)this->cdkey = 0;
    *(_DWORD *)&this->cdkey[4] = 0;
    *(_DWORD *)&this->cdkey[8] = 0;
    *(_DWORD *)&this->cdkey[12] = 0;
    *(_DWORD *)&this->cdkey[16] = 0;
    *(_WORD *)&this->cdkey[20] = 0;
    this->cdkey_state = CDKEY_UNKNOWN;
    this->WriteCDKey(this);
  }
}

// FUNC: public: virtual char const * __thiscall idSessionLocal::GetCDKey(void)
char *__thiscall idSessionLocal::GetCDKey(idSessionLocal *this)
{
  return this->cdkey;
}

// FUNC: public: virtual bool __thiscall idSessionLocal::CDKeysAreValid(bool)
char __thiscall idSessionLocal::CDKeysAreValid(idSessionLocal *this, bool strict)
{
  this->cdkey_state = CDKEY_OK;
  return 1;
}

// FUNC: public: virtual bool __thiscall idSessionLocal::WaitingForGameAuth(void)
BOOL __thiscall idSessionLocal::WaitingForGameAuth(idSessionLocal *this)
{
  return this->authEmitTimeout != 0;
}

// FUNC: public: virtual void __thiscall idSessionLocal::CDKeysAuthReply(bool,char const *)
void __thiscall idSessionLocal::CDKeysAuthReply(idSessionLocal *this, bool valid, char *auth_msg)
{
  int v4; // ecx
  idSessionLocal_vtbl *v5; // edx

  if ( this->authWaitBox )
  {
    this->StopBox(this);
    this->authWaitBox = 0;
  }
  v4 = *(_DWORD *)common.type;
  if ( valid )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(v4 + 132))(common.type, "client is authed in\n");
    if ( this->cdkey_state == CDKEY_CHECKING )
      this->cdkey_state = CDKEY_OK;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(v4 + 132))(common.type, "auth key is invalid\n");
    idStr::operator=(&this->authMsg, auth_msg);
    if ( this->cdkey_state == CDKEY_CHECKING )
      this->cdkey_state = CDKEY_INVALID;
  }
  v5 = this->__vftable;
  this->authEmitTimeout = 0;
  v5->SetCDKeyGuiVars(this);
}

// FUNC: public: virtual int __thiscall idSessionLocal::GetSaveGameVersion(void)
int __thiscall idSessionLocal::GetSaveGameVersion(idSessionLocal *this)
{
  return this->savegameVersion;
}

// FUNC: public: virtual void __thiscall idSessionLocal::AddLoadingIcon(char const *)
void __thiscall idSessionLocal::AddLoadingIcon(idSessionLocal *this, const char *icon)
{
  idUserInterface *guiLoading; // ecx
  int numLoadingIcons; // eax
  idUserInterface_vtbl *v5; // edi
  char *v6; // eax
  idUserInterface_vtbl *v7; // edi
  char *v8; // eax

  guiLoading = this->guiLoading;
  if ( guiLoading )
  {
    numLoadingIcons = this->numLoadingIcons;
    if ( numLoadingIcons < 20 )
    {
      this->numLoadingIcons = numLoadingIcons + 1;
      guiLoading->SetStateInt(guiLoading, "load_icons", numLoadingIcons);
      v5 = this->guiLoading->__vftable;
      v6 = va("load_icon_img_%d", this->numLoadingIcons);
      v5->SetStateString(this->guiLoading, v6, icon);
      v7 = this->guiLoading->__vftable;
      v8 = va("load_icon_%d", this->numLoadingIcons);
      v7->SetStateBool(this->guiLoading, v8, 1);
      this->guiLoading->HandleNamedEvent(this->guiLoading, "iconUpdate");
      this->guiLoading->StateChanged(this->guiLoading, com_frameTime, 0);
    }
  }
  this->PacifierUpdate(this);
}

// FUNC: private: void __thiscall idSessionLocal::ClearLoadingScreen(void)
void __usercall idSessionLocal::ClearLoadingScreen(idSessionLocal *this@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  idUserInterface *guiLoading; // ecx
  int i; // edi
  idUserInterface_vtbl *v6; // ebx
  char *v7; // eax
  idUserInterface_vtbl *v8; // ebx
  char *v9; // eax

  guiLoading = this->guiLoading;
  if ( guiLoading )
  {
    ((void (__thiscall *)(idUserInterface *, const char *, _DWORD, int, int))guiLoading->SetStateInt)(
      guiLoading,
      "load_icons",
      0,
      a3,
      a2);
    for ( i = 0; i < 20; ++i )
    {
      v6 = this->guiLoading->__vftable;
      v7 = va("load_icon_img_%d", i);
      v6->SetStateString(this->guiLoading, v7, &entityFilter);
      v8 = this->guiLoading->__vftable;
      v9 = va("load_icon_%d", i);
      v8->SetStateBool(this->guiLoading, v9, 0);
    }
    this->guiLoading->StateChanged(this->guiLoading, com_frameTime, 0);
    this->numLoadingIcons = 0;
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::LoadUbermessage(void)
void __thiscall idSessionLocal::LoadUbermessage(idSessionLocal *this)
{
  this->uberguiMsg = uiManager->FindGui(uiManager, "guis/ubermsg.gui", 1, 0, 1);
}

// FUNC: void __cdecl Session_RescanSI_f(class idCmdArgs const &)
void __cdecl Session_RescanSI_f()
{
  idDict *v0; // eax

  v0 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 1024);
  idDict::operator=(&sessLocal.mapSpawnData.serverInfo, v0);
  if ( game )
  {
    if ( idAsyncNetwork::server.active )
      ((void (__stdcall *)(mapSpawnData_t *))game->SetServerInfo)(&sessLocal.mapSpawnData);
  }
}

// FUNC: void __cdecl SaveGameRefreshList_f(class idCmdArgs const &)
void __usercall SaveGameRefreshList_f(int a1@<edi>, const idCmdArgs *args)
{
  bool isSaveList; // [esp+0h] [ebp-4h]

  isSaveList = 0;
  if ( args->argc > 1 )
    isSaveList = atoi(args->argv[1]) != 0;
  idSessionLocal::SetSaveGameGuiVars(&sessLocal, a1, isSaveList);
}

// FUNC: Session_TestMap_f
void __cdecl Session_TestMap_f(const idCmdArgs *args)
{
  bool v1; // cc
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // eax
  idStr map; // [esp+18h] [ebp-4Ch] BYREF
  idStr string; // [esp+38h] [ebp-2Ch] BYREF
  int v7; // [esp+60h] [ebp-4h]

  map.len = 0;
  map.alloced = 20;
  map.data = map.baseBuffer;
  map.baseBuffer[0] = 0;
  v7 = 0;
  string.len = 0;
  string.alloced = 20;
  string.data = string.baseBuffer;
  string.baseBuffer[0] = 0;
  v1 = args->argc <= 1;
  LOBYTE(v7) = 1;
  if ( v1 )
    v2 = &entityFilter;
  else
    v2 = args->argv[1];
  idStr::operator=(&map, v2);
  if ( map.len )
  {
    idStr::StripFileExtension(&map);
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
    v3 = va("dmap maps/%s.map", map.data);
    idStr::operator=(&string, v3);
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, string.data);
    v4 = va("devmap %s", map.data);
    idStr::operator=(&string, v4);
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, string.data);
  }
  LOBYTE(v7) = 0;
  idStr::FreeData(&string);
  v7 = -1;
  idStr::FreeData(&map);
}

// FUNC: Sess_WritePrecache_f
void __cdecl Sess_WritePrecache_f(const idCmdArgs *args)
{
  const char *v1; // esi
  unsigned int v2; // eax
  int v3; // edi
  int v4; // eax
  char *data; // edx
  const char *v6; // ecx
  char v7; // al
  idFile *v8; // esi
  idStr str; // [esp+1Ch] [ebp-2Ch] BYREF
  int v10; // [esp+44h] [ebp-4h]

  if ( args->argc == 2 )
  {
    v1 = args->argv[1];
    str.len = 0;
    str.alloced = 20;
    str.data = str.baseBuffer;
    str.baseBuffer[0] = 0;
    if ( v1 )
    {
      v2 = (unsigned int)&v1[strlen(v1) + 1];
      v3 = v2 - (_DWORD)(v1 + 1);
      v4 = v2 - (_DWORD)v1;
      if ( v4 > 20 )
        idStr::ReAllocate(&str, v4, 1);
      data = str.data;
      v6 = v1;
      do
      {
        v7 = *v6;
        *data++ = *v6++;
      }
      while ( v7 );
      str.len = v3;
    }
    v10 = 0;
    idStr::DefaultFileExtension(&str, ".cfg");
    v8 = fileSystem->OpenFileWrite(fileSystem, str.data, "fs_savepath", 0);
    declManager->WritePrecacheCommands(declManager, v8);
    renderModelManager->WritePrecacheCommands(renderModelManager, v8);
    uiManager->WritePrecacheCommands(uiManager, v8);
    fileSystem->CloseFile(fileSystem, v8);
    v10 = -1;
    idStr::FreeData(&str);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "USAGE: writePrecache <execFile>\n");
  }
}

// FUNC: public: static bool __cdecl idAsyncNetwork::IsActive(void)
BOOL __cdecl idAsyncNetwork::IsActive()
{
  return idAsyncNetwork::server.active || idAsyncNetwork::client.active;
}

// FUNC: Session_TestGUI_f
void __cdecl Session_TestGUI_f(const idCmdArgs *args)
{
  const char *v1; // eax

  if ( args->argc > 1 && (v1 = args->argv[1]) != 0 && *v1 )
  {
    sessLocal.guiTest = uiManager->FindGui(uiManager, v1, 1, 0, 1);
    sessLocal.guiTest->Activate(sessLocal.guiTest, 1, com_frameTime);
  }
  else
  {
    sessLocal.guiTest = 0;
  }
}

// FUNC: Session_StopRecordingDemo_f
void __cdecl Session_StopRecordingDemo_f()
{
  idSessionLocal::StopRecordingRenderDemo(&sessLocal);
}

// FUNC: Session_WriteCmdDemo_f
void __cdecl Session_WriteCmdDemo_f(const idCmdArgs *args)
{
  const char *v1; // eax
  idStr filename; // [esp+0h] [ebp-2Ch] BYREF
  int v3; // [esp+28h] [ebp-4h]

  if ( args->argc == 1 )
  {
    FindUnusedFileName("demos/cmdDemo%03i.cdemo", &filename);
    v3 = 0;
    idSessionLocal::WriteCmdDemo(&sessLocal, filename.data, 0);
    v3 = -1;
    idStr::FreeData(&filename);
  }
  else if ( args->argc == 2 )
  {
    v1 = va("demos/%s.cdemo", args->argv[1]);
    idSessionLocal::WriteCmdDemo(&sessLocal, v1, 0);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: writeCmdDemo [demoName]\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::StartRecordingRenderDemo(char const *)
void __thiscall idSessionLocal::StartRecordingRenderDemo(idSessionLocal *this, const char *demoName)
{
  idDemoFile *v3; // eax
  idDemoFile *v4; // eax
  idDemoFile *writeDemo; // ecx
  int v6; // edi
  const char *v7; // eax

  if ( this->writeDemo )
  {
    idSessionLocal::StopRecordingRenderDemo(this);
  }
  else if ( *demoName )
  {
    console->Close(console);
    v3 = (idDemoFile *)Memory::Allocate(0x4Cu);
    if ( v3 )
      idDemoFile::idDemoFile(v3);
    else
      v4 = 0;
    this->writeDemo = v4;
    if ( idDemoFile::OpenForWriting(v4, demoName) )
    {
      v6 = *(_DWORD *)common.type;
      v7 = this->writeDemo->GetName(this->writeDemo);
      (*(void (**)(netadrtype_t, const char *, ...))(v6 + 124))(common.type, "recording to %s\n", v7);
      this->writeDemo->WriteChar(this->writeDemo, 3);
      this->writeDemo->WriteInt(this->writeDemo, 1834);
      soundSystem->StartWritingDemo(soundSystem, 1, this->writeDemo);
      this->rw->StartWritingDemo(this->rw, this->writeDemo);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "error opening %s\n",
        demoName);
      writeDemo = this->writeDemo;
      if ( writeDemo )
        ((void (__thiscall *)(idDemoFile *, int))writeDemo->~idDemoFile)(writeDemo, 1);
      this->writeDemo = 0;
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idSessionLocal::StartRecordingRenderDemo: no name specified\n");
  }
}

// FUNC: public: void __thiscall idSessionLocal::BeginAVICapture(char const *)
void __thiscall idSessionLocal::BeginAVICapture(idSessionLocal *this, const char *demoName)
{
  const char *v3; // eax
  int v4; // ebp
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  idSoundSystem_vtbl *v9; // esi
  char *v10; // eax
  char *v11; // [esp-4h] [ebp-3Ch]
  idStr name; // [esp+Ch] [ebp-2Ch] BYREF
  int v13; // [esp+34h] [ebp-4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  if ( demoName )
  {
    v3 = &demoName[strlen(demoName) + 1];
    v4 = v3 - (demoName + 1);
    v5 = v3 - demoName;
    if ( v5 > 20 )
      idStr::ReAllocate(&name, v5, 1);
    data = name.data;
    v7 = demoName;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    name.len = v4;
  }
  v13 = 0;
  idStr::ExtractFileBase(&name, &this->aviDemoShortName);
  v11 = this->aviDemoShortName.data;
  this->aviCaptureMode = 1;
  this->aviDemoFrameCount = 0.0;
  this->aviTicStart = 0;
  v9 = soundSystem->__vftable;
  v10 = va("demos/%s/", v11);
  v9->AVIOpen(soundSystem, 1, v10, v11);
  v13 = -1;
  idStr::FreeData(&name);
}

// FUNC: public: void __thiscall idSessionLocal::EndAVICapture(void)
void __usercall idSessionLocal::EndAVICapture(idSessionLocal *this@<ecx>, int a2@<esi>)
{
  idFileSystem_vtbl *v3; // esi
  char *v4; // eax
  int v5; // esi
  void *retaddr; // [esp+1Ah] [ebp+0h]

  if ( this->aviCaptureMode )
  {
    ((void (__thiscall *)(idSoundSystem *, int, int))soundSystem->AVIClose)(soundSystem, 1, a2);
    v3 = fileSystem->__vftable;
    v4 = va("demos/%s/%s.roqParam", this->aviDemoShortName.data, this->aviDemoShortName.data);
    v5 = (int)v3->OpenFileWrite(fileSystem, v4, "fs_savepath", 0);
    (*(void (**)(int, const char *, ...))(*(_DWORD *)v5 + 48))(v5, "INPUT_DIR demos/%s\n", this->aviDemoShortName.data);
    (*(void (**)(int, const char *, ...))(*(_DWORD *)v5 + 48))(
      v5,
      "FILENAME demos/%s/%s.RoQ\n",
      this->aviDemoShortName.data,
      this->aviDemoShortName.data);
    (*(void (__cdecl **)(int, const char *))(*(_DWORD *)v5 + 48))(v5, "\nINPUT\n");
    retaddr = (void *)(int)(this->aviDemoFrameCount - 1.0);
    (*(void (**)(int, const char *, ...))(*(_DWORD *)v5 + 48))(
      v5,
      "%s_*.tga [00000-%05i]\n",
      this->aviDemoShortName.data,
      retaddr);
    (*(void (__cdecl **)(int, const char *))(*(_DWORD *)v5 + 48))(v5, "END_INPUT\n");
    (**(void (__thiscall ***)(int, int))v5)(v5, 1);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "captured %i frames for %s.\n",
      (int)this->aviDemoFrameCount,
      this->aviDemoShortName.data);
    this->aviCaptureMode = 0;
  }
}

// FUNC: public: void __thiscall idSessionLocal::AVIGame(char const *)
void __userpurge idSessionLocal::AVIGame(idSessionLocal *this@<ecx>, int a2@<esi>, char *demoName)
{
  char *data; // esi
  idFileSystem_vtbl *v5; // edx
  idStr filename; // [esp+10h] [ebp-2Ch] BYREF
  int v7; // [esp+38h] [ebp-4h]

  if ( this->aviCaptureMode )
  {
    idSessionLocal::EndAVICapture(this, a2);
  }
  else
  {
    if ( !this->mapSpawned )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "No map spawned.\n");
    data = demoName;
    if ( !demoName || !*demoName )
    {
      FindUnusedFileName("demos/game%03i.game", &filename);
      v5 = fileSystem->__vftable;
      v7 = 0;
      data = filename.data;
      v5->WriteFile(fileSystem, filename.data, filename.data, 1, "fs_savepath");
      v7 = -1;
      idStr::FreeData(&filename);
    }
    idSessionLocal::BeginAVICapture(this, data);
  }
}

// FUNC: void __cdecl LoadGame_f(class idCmdArgs const &)
void __usercall LoadGame_f(int a1@<ebp>, const idCmdArgs *args)
{
  const char *v2; // eax

  console->Close(console);
  if ( args->argc >= 2 && (args->argc <= 1 ? (v2 = &entityFilter) : (v2 = args->argv[1]), idStr::Icmp(v2, "quick")) )
  {
    if ( args->argc <= 1 )
      idSessionLocal::LoadGame(&sessLocal, a1, (char *)&entityFilter);
    else
      idSessionLocal::LoadGame(&sessLocal, a1, args->argv[1]);
  }
  else
  {
    idSessionLocal::LoadGame(&sessLocal, a1, 0);
  }
}

// FUNC: void __cdecl SaveGame_f(class idCmdArgs const &)
void __usercall SaveGame_f(int a1@<ebx>, int a2@<edi>, const idCmdArgs *args)
{
  const char *v3; // eax
  const char *v4; // eax

  if ( args->argc >= 2 && (args->argc <= 1 ? (v3 = &entityFilter) : (v3 = args->argv[1]), idStr::Icmp(v3, "quick")) )
  {
    if ( args->argc <= 1 )
      v4 = &entityFilter;
    else
      v4 = args->argv[1];
    if ( idStr::Icmp(v4, "checkPoint") )
    {
      if ( args->argc <= 1 )
        idSessionLocal::SaveGame(&sessLocal, a1, a2, (char *)&entityFilter, 0);
      else
        idSessionLocal::SaveGame(&sessLocal, a1, a2, args->argv[1], 0);
    }
    else
    {
      idSessionLocal::SaveGame(&sessLocal, a1, a2, 0, (char *)3);
    }
  }
  else
  {
    idSessionLocal::SaveGame(&sessLocal, a1, a2, 0, (char *)1);
  }
}

// FUNC: void __cdecl ViewNotes_f(class idCmdArgs const &)
void __cdecl ViewNotes_f(const idCmdArgs *args)
{
  if ( args->argc <= 1 )
    idSessionLocal::TakeNotes(&sessLocal, "init");
  else
    idSessionLocal::TakeNotes(&sessLocal, args->argv[1]);
}

// FUNC: void __cdecl BuildNotes_f(class idCmdArgs const &)
void __cdecl BuildNotes_f(const idCmdArgs *args)
{
  if ( args->argc <= 1 )
    idSessionLocal::TakeNotes(&sessLocal, "init2");
  else
    idSessionLocal::TakeNotes(&sessLocal, args->argv[1]);
}

// FUNC: void __cdecl QANotes_f(class idCmdArgs const &)
void __cdecl QANotes_f(const idCmdArgs *args)
{
  if ( args->argc <= 1 )
    idSessionLocal::TakeNotes(&sessLocal, "initQA");
  else
    idSessionLocal::TakeNotes(&sessLocal, args->argv[1]);
}

// FUNC: void __cdecl EditCVars_f(class idCmdArgs const &)
void __cdecl EditCVars_f(const idCmdArgs *args)
{
  if ( args->argc <= 1 )
    idSessionLocal::EditCVars(&sessLocal, &entityFilter);
  else
    idSessionLocal::EditCVars(&sessLocal, args->argv[1]);
}

// FUNC: void __cdecl SpawnGUI_f(class idCmdArgs const &)
void __cdecl SpawnGUI_f(const idCmdArgs *args)
{
  if ( args->argc <= 1 )
    idSessionLocal::SpawnGUI(&sessLocal, &entityFilter);
  else
    idSessionLocal::SpawnGUI(&sessLocal, args->argv[1]);
}

// FUNC: void __cdecl DedicatedGUI_f(class idCmdArgs const &)
void __cdecl DedicatedGUI_f()
{
  idSessionLocal::DedicatedGUI(&sessLocal);
}

// FUNC: void __cdecl Session_Hitch_f(class idCmdArgs const &)
void __cdecl Session_Hitch_f(const idCmdArgs *args)
{
  int v1; // eax

  soundSystem->SetMute(soundSystem, 1);
  soundSystem->SetActiveSoundWorld(soundSystem, 0);
  Sys_EnterCriticalSection(0);
  if ( args->argc == 2 )
  {
    v1 = atoi(args->argv[1]);
    Sys_Sleep(v1);
  }
  else
  {
    Sys_Sleep(100);
  }
  Sys_LeaveCriticalSection(0);
  soundSystem->SetActiveSoundWorld(soundSystem, 1);
  soundSystem->SetMute(soundSystem, 0);
}

// FUNC: public: virtual bool __thiscall idSessionLocal::ProcessEvent(struct sysEvent_s const *)
char __thiscall idSessionLocal::ProcessEvent(idSessionLocal *this, sysEvent_s *event)
{
  sysEvent_s *v2; // esi
  int v4; // eax
  escReply_t v5; // eax
  const char *v7; // eax
  idUserInterface *guiTest; // ecx
  int evValue; // eax
  const char *v10; // eax
  const char *v11; // esi

  v2 = event;
  if ( this->guiActive
    || event->evType != SE_KEY
    || event->evValue2 != 1
    || (v4 = event->evValue, v4 != 27) && v4 != 203 )
  {
    if ( !console->ProcessEvent(console, event, 0) )
    {
      guiTest = this->guiTest;
      if ( guiTest )
      {
        if ( v2->evType == SE_KEY && v2->evValue2 == 1 && ((evValue = v2->evValue, evValue == 27) || evValue == 203) )
        {
          this->guiTest = 0;
          return 1;
        }
        else
        {
          v10 = guiTest->HandleEvent(guiTest, v2, com_frameTime, 0);
          v11 = v10;
          if ( v10 )
          {
            if ( *v10 )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                common.type,
                "testGui event returned: '%s'\n",
                v10);
          }
          idSessionLocal::HandleMainMenuCommands(this, v11);
          return 1;
        }
      }
      if ( this->guiActive )
      {
        idSessionLocal::MenuEvent(this, v2);
        return 1;
      }
      if ( !this->mapSpawned )
      {
        console->ProcessEvent(console, v2, 1);
        return 1;
      }
      if ( v2->evType != SE_KEY || v2->evValue2 != 1 )
        return 0;
      idKeyInput::ExecKeyBinding(v2->evValue);
    }
    return 1;
  }
  console->Close(console);
  if ( game )
  {
    event = 0;
    v5 = game->HandleESC(game, (idUserInterface **)&event);
    if ( v5 )
    {
      if ( v5 == ESC_GUI )
      {
        this->SetGUI(this, (idUserInterface *)event, 0);
        return 1;
      }
      goto LABEL_10;
    }
    return 1;
  }
LABEL_10:
  v7 = cvarSystem->GetCVarString(cvarSystem, "fs_game");
  if ( idStr::Icmp(v7, "q4basexenon") )
  {
    this->StartMenu(this, &entityFilter);
  }
  else
  {
    if ( !this->mapSpawned )
    {
      this->StartMenu(this, &entityFilter);
      return 1;
    }
    if ( !cvarSystem->GetCVarBool(cvarSystem, "net_serverDedicated") )
    {
      idSessionLocal::XboxInGameGUI(this);
      return 1;
    }
    if ( this->guiActive != this->guiDedicated )
    {
      idSessionLocal::DedicatedGUI(this);
      return 1;
    }
  }
  return 1;
}

// FUNC: public: void __thiscall idSessionLocal::AdvanceRenderDemo(bool)
void __thiscall idSessionLocal::AdvanceRenderDemo(idSessionLocal *this, bool singleFrameOnly)
{
  int v3; // ebp
  int latchedTicNumber; // ecx
  __int64 v5; // rax
  idDemoFile *readDemo; // ecx

  if ( this->lastDemoTic == -1 )
    this->lastDemoTic = this->latchedTicNumber - 1;
  v3 = 0;
  if ( this->aviCaptureMode || this->timeDemo || singleFrameOnly )
  {
    this->lastDemoTic = this->latchedTicNumber;
    goto LABEL_9;
  }
  latchedTicNumber = this->latchedTicNumber;
  v5 = this->latchedTicNumber - this->lastDemoTic;
  v3 = (((int)v5 - HIDWORD(v5)) >> 1) - 1;
  if ( v3 > 4 )
    v3 = 4;
  this->lastDemoTic = latchedTicNumber - latchedTicNumber % 2;
  if ( v3 > -1 )
  {
LABEL_9:
    while ( 1 )
    {
      readDemo = this->readDemo;
      singleFrameOnly = 0;
      readDemo->ReadChar(readDemo, (char *)&singleFrameOnly);
      if ( !singleFrameOnly )
        break;
      if ( singleFrameOnly )
      {
        if ( this->rw->ProcessDemoCommand(
               this->rw,
               this->readDemo,
               &this->currentDemoRenderView,
               &this->portalSkyDemoRenderView,
               &this->demoTimeOffset) )
        {
          --v3;
          ++this->numDemoFrames;
        }
      }
      else if ( singleFrameOnly == 2 )
      {
        soundSystem->ProcessDemoCommand(soundSystem, 1, this->readDemo);
      }
      else if ( singleFrameOnly == 3 )
      {
        this->readDemo->ReadInt(this->readDemo, &this->renderdemoVersion);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "reading a v%d render demo\n",
          this->renderdemoVersion);
        this->savegameVersion = 1834;
      }
      else
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "Bad render demo token");
      }
      if ( v3 <= -1 )
        goto LABEL_23;
    }
    if ( this->numDemoFrames != 1 )
    {
      this->Stop(this);
      this->StartMenu(this, &entityFilter);
    }
  }
LABEL_23:
  if ( idSessionLocal::com_showDemo.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "frame:%i DemoTic:%i latched:%i skip:%i\n",
      this->numDemoFrames,
      this->lastDemoTic,
      this->latchedTicNumber,
      v3);
}

// FUNC: public: void __thiscall idSessionLocal::DrawCmdGraph(void)
void __thiscall idSessionLocal::DrawCmdGraph(idSessionLocal *this)
{
  idRenderSystem_vtbl *v2; // eax
  int v3; // edi
  int v4; // ebx
  idRenderSystem_vtbl *v5; // edx
  int v6; // eax
  float v7; // [esp+4Ch] [ebp-64h]
  float v8; // [esp+50h] [ebp-60h]
  float v9; // [esp+58h] [ebp-58h]
  _DWORD v10[4]; // [esp+60h] [ebp-50h] BYREF
  int v11; // [esp+80h] [ebp-30h]
  int h; // [esp+84h] [ebp-2Ch]
  usercmd_t cmd; // [esp+88h] [ebp-28h] BYREF

  if ( idSessionLocal::com_showAngles.internalVar->integerValue )
  {
    ((void (__thiscall *)(idRenderSystem *, int, int, int, int))renderSystem->SetColor4)(
      renderSystem,
      1036831949,
      1036831949,
      1036831949,
      1065353216);
    (*((void (__thiscall **)(idRenderSystem *, _DWORD, int, int, int, _DWORD, _DWORD, int, int, const idMaterial *))&renderSystem->SetColor4
     + 1))(
      renderSystem,
      0,
      1135607808,
      1128267776,
      1124073472,
      0,
      0,
      1065353216,
      1065353216,
      this->whiteMaterial);
    v2 = renderSystem->__vftable;
    BYTE1(v10[3]) = 0;
    HIWORD(v10[3]) = 16256;
    strcpy((char *)v10, "fff?fff?fff?");
    ((void (__thiscall *)(idRenderSystem *, _DWORD, _DWORD, _DWORD, _DWORD))v2->SetColor4)(
      renderSystem,
      v10[0],
      v10[1],
      v10[2],
      v10[3]);
    v3 = 0;
    v4 = 0;
    v11 = 0;
    do
    {
      ((void (__stdcall *)(usercmd_t *, int))usercmdGen->TicCmd)(&cmd, this->latchedTicNumber + v3 - 60);
      v5 = renderSystem->__vftable;
      v10[3] = this->whiteMaterial;
      v6 = (*(int *)&cmd.angles[1] >> 8) & 0x7F;
      v9 = (float)v6;
      h = 480 - v6;
      v8 = (float)(480 - v6);
      v7 = (float)v11;
      (*((void (__stdcall **)(_DWORD, _DWORD, int, _DWORD, _DWORD, _DWORD, int, int, _DWORD))&v5->SetColor4 + 1))(
        LODWORD(v7),
        LODWORD(v8),
        1065353216,
        LODWORD(v9),
        0,
        0,
        1065353216,
        1065353216,
        v10[3]);
      v4 += 3;
      ++v3;
      v11 = v4;
    }
    while ( v4 < 180 );
  }
}

// FUNC: public: int __thiscall idSessionLocal::GetLocalClientNum(void)
int __thiscall idSessionLocal::GetLocalClientNum(idSessionLocal *this)
{
  if ( idAsyncNetwork::client.active )
    return idAsyncNetwork::client.clientNum;
  if ( !idAsyncNetwork::server.active || !idAsyncNetwork::serverDedicated.internalVar->integerValue )
    return 0;
  if ( idAsyncServer::IsClientInGame(
         &idAsyncNetwork::server,
         idAsyncNetwork::serverDrawClient.internalVar->integerValue) )
  {
    return idAsyncNetwork::serverDrawClient.internalVar->integerValue;
  }
  return -1;
}

// FUNC: public: virtual void __thiscall idSessionLocal::WriteCDKey(void)
void __thiscall idSessionLocal::WriteCDKey(idSessionLocal *this)
{
  idFileSystem_vtbl *v2; // esi
  idCVarSystem_vtbl *v3; // edx
  int v4; // eax
  char *v5; // eax
  idFile *v6; // eax
  idFile *v7; // esi
  idStr filename; // [esp+18h] [ebp-2Ch] BYREF
  int v9; // [esp+40h] [ebp-4h]

  filename.len = 0;
  filename.alloced = 20;
  filename.data = filename.baseBuffer;
  filename.baseBuffer[0] = 0;
  v2 = fileSystem->__vftable;
  v3 = cvarSystem->__vftable;
  v9 = 0;
  v4 = ((int (__thiscall *)(idCVarSystem *, const char *, const char *, const char *))v3->GetCVarString)(
         cvarSystem,
         "fs_basepath",
         "q4base",
         "quake4key");
  v5 = (char *)((int (__thiscall *)(idFileSystem *, int))v2->BuildOSPath)(fileSystem, v4);
  idStr::operator=(&filename, v5);
  v6 = fileSystem->OpenExplicitFileWrite(fileSystem, filename.data);
  v7 = v6;
  if ( v6 )
  {
    v6->Printf(
      v6,
      "%s%s",
      this->cdkey,
      "\n"
      "// Do not give this file to ANYONE.\n"
      "// id Software, Raven Software or Activision will NOT ask you to send this file to them.\n");
    fileSystem->CloseFile(fileSystem, v7);
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't write %s.\n",
      filename.data);
  }
  v9 = -1;
  idStr::FreeData(&filename);
}

// FUNC: private: void __thiscall idSessionLocal::EmitGameAuth(void)
void __thiscall idSessionLocal::EmitGameAuth(idSessionLocal *this)
{
  idStr *p_authMsg; // esi
  char *cdkey; // eax

  p_authMsg = &this->authMsg;
  if ( this->authMsg.alloced < 1 )
    idStr::ReAllocate(&this->authMsg, 1, 1);
  *p_authMsg->data = 0;
  p_authMsg->len = 0;
  if ( this->cdkey_state == CDKEY_CHECKING )
    cdkey = this->cdkey;
  else
    cdkey = 0;
  if ( idAsyncClient::SendAuthCheck(&idAsyncNetwork::client, cdkey) )
  {
    this->authEmitTimeout = Sys_Milliseconds() + 5000;
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "authing with the master..\n");
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "sendAuthCheck failed\n");
    if ( this->cdkey_state == CDKEY_CHECKING )
      this->cdkey_state = CDKEY_OK;
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::EmitClientAuth(void)
void __thiscall idSessionLocal::EmitClientAuth(idSessionLocal *this)
{
  idStr *p_authMsg; // esi

  p_authMsg = &this->authMsg;
  if ( this->authMsg.alloced < 1 )
    idStr::ReAllocate(&this->authMsg, 1, 1);
  *p_authMsg->data = 0;
  p_authMsg->len = 0;
  idAsyncClient::SendClientAuthCheck(&idAsyncNetwork::client);
  this->authEmitTimeout = Sys_Milliseconds() + 5000;
}

// FUNC: private: void __thiscall idSessionLocal::SetupLoadingScreen(void)
void __usercall idSessionLocal::SetupLoadingScreen(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        int a4@<edi>)
{
  const idKeyValue *Key; // eax
  const char *data; // eax
  const char *v7; // eax
  const char *v8; // edi
  unsigned int v9; // ebp
  _BYTE *v10; // edx
  const char *v11; // ecx
  char v12; // al
  const idKeyValue *v13; // eax
  const char *v14; // edi
  idUserInterface_vtbl *v15; // ebp
  const char *v16; // eax
  int Text; // eax
  mapSpawnData_t *p_mapSpawnData; // ecx
  idUserInterface_vtbl *v19; // edi
  const char *v20; // eax
  char *v21; // eax
  const char *v22; // [esp+24h] [ebp-3Ch]
  const char *v23; // [esp+24h] [ebp-3Ch]
  idStr serverAddress; // [esp+34h] [ebp-2Ch] BYREF
  int v25; // [esp+5Ch] [ebp-4h]

  if ( this->guiLoading && (idAsyncNetwork::server.active || idAsyncNetwork::client.active) )
  {
    Key = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_name");
    if ( Key )
      data = Key->value->data;
    else
      data = &entityFilter;
    ((void (__thiscall *)(idUserInterface *, const char *, const char *, int, int, int))this->guiLoading->SetStateString)(
      this->guiLoading,
      "server_name",
      data,
      a3,
      a4,
      a2);
    v7 = networkSystem->GetServerAddress(networkSystem);
    v8 = v7;
    *(_DWORD *)serverAddress.baseBuffer = 0;
    *(_DWORD *)&serverAddress.baseBuffer[8] = 20;
    *(_DWORD *)&serverAddress.baseBuffer[4] = &serverAddress.baseBuffer[12];
    serverAddress.baseBuffer[12] = 0;
    if ( v7 )
    {
      v9 = strlen(v7);
      if ( (int)(v9 + 1) > 20 )
        idStr::ReAllocate((idStr *)serverAddress.baseBuffer, v9 + 1, 1);
      v10 = *(_BYTE **)&serverAddress.baseBuffer[4];
      v11 = v8;
      do
      {
        v12 = *v11;
        *v10++ = *v11++;
      }
      while ( v12 );
      *(_DWORD *)serverAddress.baseBuffer = v9;
    }
    this->guiLoading->SetStateString(this->guiLoading, "server_ip", *(const char **)&serverAddress.baseBuffer[4]);
    v13 = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_gameType");
    if ( v13 )
      v14 = v13->value->data;
    else
      v14 = &entityFilter;
    v15 = this->guiLoading->__vftable;
    v16 = game->GetLongGametypeName(game, v14);
    v15->SetStateString(this->guiLoading, "server_gametype", v16);
    if ( idStr::FindText(v14, "CTF", 0, 0, -1) < 0 )
    {
      Text = idStr::FindText(v14, "Tourney", 0, 0, -1);
      p_mapSpawnData = &this->mapSpawnData;
      if ( Text < 0 )
      {
        idDict::FindKey(&p_mapSpawnData->serverInfo, "si_fraglimit");
        v22 = "#str_107660";
      }
      else
      {
        idDict::FindKey(&p_mapSpawnData->serverInfo, "si_tourneyLimit");
        v22 = "#str_107714";
      }
    }
    else
    {
      idDict::FindKey(&this->mapSpawnData.serverInfo, "si_capturelimit");
      v22 = "#str_107661";
    }
    v19 = this->guiLoading->__vftable;
    v20 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 168))(
                          common.type,
                          v22);
    v21 = va("%s %s", v20, v23);
    v19->SetStateString(this->guiLoading, "server_limit", v21);
    this->guiLoading->StateChanged(this->guiLoading, com_frameTime, 0);
    this->PacifierUpdate(this);
    v25 = -1;
    idStr::FreeData(&serverAddress);
  }
}

// FUNC: Session_DemoShot_f
void __cdecl Session_DemoShot_f(const idCmdArgs *args)
{
  const char *v1; // eax
  idStr filename; // [esp+4h] [ebp-2Ch] BYREF
  int v3; // [esp+2Ch] [ebp-4h]

  if ( args->argc == 2 )
  {
    v1 = va("demos/shot_%s.demo", args->argv[1]);
    idSessionLocal::StartRecordingRenderDemo(&sessLocal, v1);
    sessLocal.UpdateScreen(&sessLocal, 1);
    idSessionLocal::StopRecordingRenderDemo(&sessLocal);
  }
  else
  {
    FindUnusedFileName("demos/shot%03i.demo", &filename);
    v3 = 0;
    idSessionLocal::StartRecordingRenderDemo(&sessLocal, filename.data);
    sessLocal.UpdateScreen(&sessLocal, 1);
    idSessionLocal::StopRecordingRenderDemo(&sessLocal);
    v3 = -1;
    idStr::FreeData(&filename);
  }
}

// FUNC: Session_RecordDemo_f
void __cdecl Session_RecordDemo_f(const idCmdArgs *args)
{
  const char *v1; // eax
  idStr filename; // [esp+0h] [ebp-2Ch] BYREF
  int v3; // [esp+28h] [ebp-4h]

  if ( args->argc == 2 )
  {
    v1 = va("demos/%s.demo", args->argv[1]);
    idSessionLocal::StartRecordingRenderDemo(&sessLocal, v1);
  }
  else
  {
    FindUnusedFileName("demos/demo%03i.demo", &filename);
    v3 = 0;
    idSessionLocal::StartRecordingRenderDemo(&sessLocal, filename.data);
    v3 = -1;
    idStr::FreeData(&filename);
  }
}

// FUNC: Session_AVIGame_f
void __cdecl Session_AVIGame_f(const idCmdArgs *args)
{
  if ( args->argc <= 1 )
    idSessionLocal::AVIGame(&sessLocal, &entityFilter);
  else
    idSessionLocal::AVIGame(&sessLocal, args->argv[1]);
}

// FUNC: public: void __thiscall idSessionLocal::StopPlayingRenderDemo(void)
void __thiscall idSessionLocal::StopPlayingRenderDemo(idSessionLocal *this)
{
  int v2; // edi
  int v3; // ebp
  const char *v4; // eax
  idDemoFile *readDemo; // ecx
  bool v6; // zf
  double v7; // st7
  const char *v8; // edi
  unsigned int v9; // eax
  int v10; // ebp
  int v11; // eax
  char *data; // edx
  const char *v13; // ecx
  char v14; // al
  int v15; // ecx
  int numDemoFrames; // [esp+28h] [ebp-30h]
  idStr message; // [esp+2Ch] [ebp-2Ch] BYREF
  int v18; // [esp+4Ch] [ebp-Ch]
  int v19; // [esp+54h] [ebp-4h]

  if ( this->readDemo )
  {
    v2 = Sys_Milliseconds();
    idSessionLocal::EndAVICapture(this, (int)this);
    idDemoFile::Close(this->readDemo);
    soundSystem->StopAllSounds(soundSystem, 1);
    v3 = *(_DWORD *)common.type;
    v4 = this->readDemo->GetName(this->readDemo);
    (*(void (**)(netadrtype_t, const char *, ...))(v3 + 124))(common.type, "stopped playing %s.\n", v4);
    readDemo = this->readDemo;
    if ( readDemo )
      ((void (__thiscall *)(idDemoFile *, int))readDemo->~idDemoFile)(readDemo, 1);
    v6 = this->timeDemo == TD_NO;
    this->readDemo = 0;
    if ( !v6 )
    {
      numDemoFrames = this->numDemoFrames;
      v7 = (double)(v2 - this->timeDemoStartTime) * 0.001;
      v8 = va("%i frames rendered in %3.1f seconds = %3.1f fps\n", numDemoFrames, v7, (double)numDemoFrames / v7);
      message.len = 0;
      message.alloced = 20;
      message.data = message.baseBuffer;
      message.baseBuffer[0] = 0;
      if ( v8 )
      {
        v9 = (unsigned int)&v8[strlen(v8) + 1];
        v10 = v9 - (_DWORD)(v8 + 1);
        v11 = v9 - (_DWORD)v8;
        if ( v11 > 20 )
          idStr::ReAllocate(&message, v11, 1);
        data = message.data;
        v13 = v8;
        do
        {
          v14 = *v13;
          *data++ = *v13++;
        }
        while ( v14 );
        message.len = v10;
      }
      v15 = *(_DWORD *)common.type;
      v19 = 0;
      (*(void (__stdcall **)(netadrtype_t, char *))(v15 + 124))(common.type, message.data);
      if ( this->timeDemo == TD_YES_THEN_QUIT )
      {
        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "quit\n");
      }
      else
      {
        soundSystem->SetMute(soundSystem, 1);
        ((void (__thiscall *)(idSessionLocal *, _DWORD, int, const char *, int, _DWORD, _DWORD, _DWORD, int, _DWORD))this->MessageBoxA)(
          this,
          0,
          v18,
          "Time Demo Results",
          1,
          0,
          0,
          0,
          message.alloced,
          *(_DWORD *)message.baseBuffer);
        soundSystem->SetMute(soundSystem, 0);
      }
      this->timeDemo = TD_NO;
      v19 = -1;
      idStr::FreeData(&message);
    }
  }
  else
  {
    this->timeDemo = TD_NO;
  }
}

// FUNC: public: void __thiscall idSessionLocal::StartPlayingRenderDemo(class idStr)
void __userpurge idSessionLocal::StartPlayingRenderDemo(idSessionLocal *this@<ecx>, int a2@<edi>, idStr demoName)
{
  idUserInterface *v4; // eax
  int v5; // edi
  int v6; // eax
  idDemoFile *v7; // eax
  idDemoFile *v8; // eax
  idDemoFile *readDemo; // ecx
  idSessionLocal_vtbl *v10; // edx
  idSessionLocal_vtbl *v11; // eax
  idUserInterface *guiLoading; // ecx
  void *retaddr; // [esp+40h] [ebp+0h]

  if ( *demoName.data )
  {
    ((void (__thiscall *)(idSoundSystem *, int, int))soundSystem->StopAllSounds)(soundSystem, -1, a2);
    this->Stop(this);
    console->Close(console);
    v4 = uiManager->FindGui(uiManager, "guis/loading/generic.gui", 1, 0, 1);
    this->guiLoading = v4;
    v5 = (int)v4->__vftable;
    v6 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
           common.type,
           "#str_102087",
           -1);
    (*(void (__thiscall **)(idUserInterface *, const char *, int))(v5 + 56))(this->guiLoading, "demo", v6);
    v7 = (idDemoFile *)Memory::Allocate(0x4Cu);
    LOBYTE(retaddr) = 1;
    if ( v7 )
      idDemoFile::idDemoFile(v7);
    else
      v8 = 0;
    LOBYTE(retaddr) = 0;
    this->readDemo = v8;
    idStr::DefaultFileExtension((idStr *)&demoName.data, ".demo");
    if ( idDemoFile::OpenForReading(this->readDemo, v5, (int)this, (const char *)demoName.alloced) )
    {
      v11 = this->__vftable;
      this->insideExecuteMapChange = 1;
      this->pauseAfterMapChange = 0;
      v11->UpdateScreen(this, 1);
      guiLoading = this->guiLoading;
      this->insideExecuteMapChange = 0;
      guiLoading->SetStateString(guiLoading, "demo", &entityFilter);
      this->renderdemoVersion = 3;
      this->savegameVersion = 1834;
      memset(&this->currentDemoRenderView, 0, sizeof(this->currentDemoRenderView));
      memset(&this->portalSkyDemoRenderView, 0, sizeof(this->portalSkyDemoRenderView));
      soundSystem->SetActiveSoundWorld(soundSystem, 0);
      idSessionLocal::AdvanceRenderDemo(this, 1);
      this->ExitMenu(this);
      this->numDemoFrames = 1;
      this->lastDemoTic = -1;
      this->timeDemoStartTime = Sys_Milliseconds();
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "couldn't open %s\n",
        demoName.alloced);
      readDemo = this->readDemo;
      if ( readDemo )
        ((void (__thiscall *)(idDemoFile *, int))readDemo->~idDemoFile)(readDemo, 1);
      v10 = this->__vftable;
      this->readDemo = 0;
      v10->Stop(this);
      this->StartMenu(this, &entityFilter);
      soundSystem->SetMute(soundSystem, 0);
    }
    idStr::FreeData(&demoName);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idSessionLocal::StartPlayingRenderDemo: no name specified\n");
    idStr::FreeData(&demoName);
  }
}

// FUNC: public: void __thiscall idSessionLocal::TimeRenderDemo(char const *,bool)
void __thiscall idSessionLocal::TimeRenderDemo(idSessionLocal *this, const char *demoName, bool twice)
{
  const char *v4; // eax
  int v5; // ebp
  int v6; // eax
  char *data; // edx
  const char *v8; // ecx
  char v9; // al
  idSoundSystem_vtbl *v10; // edx
  int len; // ebp
  char *v12; // ecx
  char *v13; // edx
  char v14; // al
  idUserInterface_vtbl *v15; // esi
  int v16; // eax
  idSessionLocal_vtbl *v17; // eax
  int v18; // ebp
  char *v19; // ecx
  char *v20; // edx
  char v21; // al
  idStr v22; // [esp-8h] [ebp-5Ch] BYREF
  idStr demo; // [esp+28h] [ebp-2Ch] BYREF
  int v24; // [esp+50h] [ebp-4h]

  demo.len = 0;
  demo.alloced = 20;
  demo.data = demo.baseBuffer;
  demo.baseBuffer[0] = 0;
  if ( demoName )
  {
    v4 = &demoName[strlen(demoName) + 1];
    v5 = v4 - (demoName + 1);
    v6 = v4 - demoName;
    if ( v6 > 20 )
      idStr::ReAllocate(&demo, v6, 1);
    data = demo.data;
    v8 = demoName;
    do
    {
      v9 = *v8;
      *data++ = *v8++;
    }
    while ( v9 );
    demo.len = v5;
  }
  v10 = soundSystem->__vftable;
  v24 = 0;
  v10->SetMute(soundSystem, 1);
  v22.alloced = 20;
  v22.data = v22.baseBuffer;
  v22.len = 0;
  v22.baseBuffer[0] = 0;
  len = demo.len;
  if ( demo.len + 1 > 20 )
    idStr::ReAllocate(&v22, demo.len + 1, 1);
  v12 = demo.data;
  v13 = v22.data;
  do
  {
    v14 = *v12;
    *v13++ = *v12++;
  }
  while ( v14 );
  v22.len = len;
  idSessionLocal::StartPlayingRenderDemo(this, (int)this, v22);
  if ( twice )
  {
    if ( !this->readDemo )
      goto LABEL_22;
    v15 = this->guiLoading->__vftable;
    v16 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_104852",
            -1);
    v15->SetStateString(this->guiLoading, "demo", (const char *)v16);
    this->guiLoading->StateChanged(this->guiLoading, com_frameTime, 0);
    while ( this->readDemo )
    {
      v17 = this->__vftable;
      *(_DWORD *)&v22.baseBuffer[16] = 1;
      this->insideExecuteMapChange = 1;
      this->pauseAfterMapChange = 0;
      v17->UpdateScreen(this, *(_DWORD *)&v22.baseBuffer[16]);
      v22.baseBuffer[16] = 1;
      this->insideExecuteMapChange = 0;
      idSessionLocal::AdvanceRenderDemo(this, v22.baseBuffer[16]);
    }
    this->guiLoading->SetStateString(this->guiLoading, "demo", &entityFilter);
    v22.alloced = 20;
    v22.data = v22.baseBuffer;
    v22.len = 0;
    v22.baseBuffer[0] = 0;
    v18 = demo.len;
    if ( demo.len + 1 > 20 )
      idStr::ReAllocate(&v22, demo.len + 1, 1);
    v19 = demo.data;
    v20 = v22.data;
    do
    {
      v21 = *v19;
      *v20++ = *v19++;
    }
    while ( v21 );
    v22.len = v18;
    idSessionLocal::StartPlayingRenderDemo(this, (int)this, v22);
  }
  if ( this->readDemo )
    this->timeDemo = TD_YES;
LABEL_22:
  v24 = -1;
  idStr::FreeData(&demo);
}

// FUNC: public: void __thiscall idSessionLocal::AVIRenderDemo(char const *)
void __thiscall idSessionLocal::AVIRenderDemo(idSessionLocal *this, const char *_demoName)
{
  const char *v2; // eax
  int v3; // edi
  int v4; // eax
  char *data; // edx
  const char *v6; // ecx
  char v7; // al
  int len; // edi
  char *v9; // ecx
  char *v10; // edx
  char v11; // al
  idSessionLocal *v12; // esi
  idStr v13; // [esp-20h] [ebp-58h] BYREF
  idSessionLocal *v14; // [esp+8h] [ebp-30h]
  idStr demoName; // [esp+Ch] [ebp-2Ch] BYREF
  int v16; // [esp+34h] [ebp-4h]

  v14 = this;
  demoName.len = 0;
  demoName.alloced = 20;
  demoName.data = demoName.baseBuffer;
  demoName.baseBuffer[0] = 0;
  if ( _demoName )
  {
    v2 = &_demoName[strlen(_demoName) + 1];
    v3 = v2 - (_demoName + 1);
    v4 = v2 - _demoName;
    if ( v4 > 20 )
      idStr::ReAllocate(&demoName, v4, 1);
    data = demoName.data;
    v6 = _demoName;
    do
    {
      v7 = *v6;
      *data++ = *v6++;
    }
    while ( v7 );
    demoName.len = v3;
  }
  v13.alloced = 20;
  v13.data = v13.baseBuffer;
  v13.len = 0;
  v13.baseBuffer[0] = 0;
  len = demoName.len;
  v16 = 0;
  if ( demoName.len + 1 > 20 )
    idStr::ReAllocate(&v13, demoName.len + 1, 1);
  v9 = demoName.data;
  v10 = v13.data;
  do
  {
    v11 = *v9;
    *v10++ = *v9++;
  }
  while ( v11 );
  v13.len = len;
  v12 = v14;
  idSessionLocal::StartPlayingRenderDemo(v14, len, v13);
  if ( v12->readDemo )
  {
    idSessionLocal::BeginAVICapture(v12, demoName.data);
    v12->UpdateScreen(v12, 1);
  }
  v16 = -1;
  idStr::FreeData(&demoName);
}

// FUNC: public: void __thiscall idSessionLocal::CompressDemoFile(char const *,char const *)
void __thiscall idSessionLocal::CompressDemoFile(idSessionLocal *this, char *scheme, const char *demoName)
{
  int v3; // eax
  char v4; // cl
  unsigned int v5; // kr00_4
  char v6; // cl
  int i; // eax
  char *v8; // edx
  int len; // esi
  char *data; // ecx
  char *v11; // edx
  char v12; // al
  int v13; // esi
  int v14; // eax
  char v15; // cl
  char *v16; // edx
  int v17; // esi
  idCVarSystem_vtbl *v18; // edi
  int v19; // eax
  int j; // eax
  bool v21; // [esp+3Ch] [ebp-100E8h]
  idStr v22; // [esp+40h] [ebp-100E4h] BYREF
  idStr v23; // [esp+60h] [ebp-100C4h] BYREF
  idDemoFile v24; // [esp+80h] [ebp-100A4h] BYREF
  idDemoFile v25; // [esp+CCh] [ebp-10058h] BYREF
  char buffer[65536]; // [esp+118h] [ebp-1000Ch] BYREF
  int v27; // [esp+10120h] [ebp-4h]

  v23.data = v23.baseBuffer;
  v23.alloced = 20;
  v23.baseBuffer[0] = 0;
  v3 = 0;
  do
  {
    v4 = aDemos[v3];
    v23.baseBuffer[v3++] = v4;
  }
  while ( v4 );
  v23.len = 6;
  v27 = 0;
  if ( demoName )
  {
    v5 = strlen(demoName);
    if ( (int)(v5 + 7) > v23.alloced )
      idStr::ReAllocate(&v23, v5 + 7, 1);
    v6 = *demoName;
    for ( i = 0; v6; v6 = demoName[i] )
    {
      v8 = &v23.data[i++];
      v8[v23.len] = v6;
    }
    v23.len = v5 + 6;
    v23.data[v5 + 6] = 0;
  }
  idStr::DefaultFileExtension(&v23, ".demo");
  len = v23.len;
  v22.len = 0;
  v22.alloced = 20;
  v22.data = v22.baseBuffer;
  v22.baseBuffer[0] = 0;
  if ( v23.len + 1 > 20 )
    idStr::ReAllocate(&v22, v23.len + 1, 1);
  data = v23.data;
  v11 = v22.data;
  do
  {
    v12 = *data;
    *v11++ = *data++;
  }
  while ( v12 );
  v22.len = len;
  LOBYTE(v27) = 1;
  idStr::StripFileExtension(&v22);
  v13 = v22.len + 16;
  if ( v22.len + 17 > v22.alloced )
    idStr::ReAllocate(&v22, v22.len + 17, 1);
  v14 = 0;
  v15 = 95;
  do
  {
    v16 = &v22.data[v14++];
    v16[v22.len] = v15;
    v15 = aCompressedDemo[v14];
  }
  while ( v15 );
  v22.len = v13;
  v22.data[v13] = 0;
  v17 = cvarSystem->GetCVarInteger(cvarSystem, "com_compressDemos");
  v21 = cvarSystem->GetCVarBool(cvarSystem, "com_preloadDemos");
  cvarSystem->SetCVarBool(cvarSystem, "com_preloadDemos", 0, 0);
  v18 = cvarSystem->__vftable;
  v19 = atoi(scheme);
  v18->SetCVarInteger(cvarSystem, "com_compressDemos", v19, 0);
  idDemoFile::idDemoFile(&v24);
  LOBYTE(v27) = 2;
  idDemoFile::idDemoFile(&v25);
  LOBYTE(v27) = 3;
  if ( idDemoFile::OpenForReading(&v24, (int)v18, v17, v23.data) )
  {
    if ( idDemoFile::OpenForWriting(&v25, v22.data) )
    {
      (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 120))(common.type, 1);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Compressing %s to %s...\n",
        v23.data,
        v22.data);
      for ( j = idDemoFile::Read(&v24, buffer, 0xFFFF); j; j = idDemoFile::Read(&v24, buffer, 0xFFFF) )
      {
        idDemoFile::Write(&v25, buffer, j);
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, ".");
      }
      idDemoFile::Close(&v24);
      idDemoFile::Close(&v25);
      cvarSystem->SetCVarBool(cvarSystem, "com_preloadDemos", v21, 0);
      cvarSystem->SetCVarInteger(cvarSystem, "com_compressDemos", v17, 0);
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Done\n");
      (*(void (__thiscall **)(netadrtype_t, _DWORD))(*(_DWORD *)common.type + 120))(common.type, 0);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Could not open %s for writing\n",
        v22.data);
      idDemoFile::Close(&v24);
      cvarSystem->SetCVarBool(cvarSystem, "com_preloadDemos", v21, 0);
      cvarSystem->SetCVarInteger(cvarSystem, "com_compressDemos", v17, 0);
    }
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Could not open %s for reading\n",
      v23.data);
  }
  LOBYTE(v27) = 2;
  idDemoFile::~idDemoFile(&v25);
  LOBYTE(v27) = 1;
  idDemoFile::~idDemoFile(&v24);
  LOBYTE(v27) = 0;
  idStr::FreeData(&v22);
  v27 = -1;
  idStr::FreeData(&v23);
}

// FUNC: public: void __thiscall idSessionLocal::UnloadMap(void)
void __thiscall idSessionLocal::UnloadMap(idSessionLocal *this)
{
  idRenderWorld *rw; // ecx

  idSessionLocal::StopPlayingRenderDemo(this);
  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 44))(*(_DWORD *)common.ip);
  if ( soundSystem )
    soundSystem->StopAllSounds(soundSystem, 1);
  if ( game )
    game->MapShutdown(game);
  if ( this->cmdDemoFile )
  {
    fileSystem->CloseFile(fileSystem, this->cmdDemoFile);
    this->cmdDemoFile = 0;
  }
  if ( this->writeDemo )
    idSessionLocal::StopRecordingRenderDemo(this);
  rw = this->rw;
  if ( rw )
    rw->FreeDefs(rw);
  this->objectiveFailed = 0;
  this->mapSpawned = 0;
}

// FUNC: public: void __thiscall idSessionLocal::LoadLoadingGui(char const *,char const *)
void __thiscall idSessionLocal::LoadLoadingGui(idSessionLocal *this, const char *mapName, const char *entityFilter)
{
  int v3; // edi
  const char *v4; // eax
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  int v9; // eax
  bool v10; // zf
  int v11; // edi
  int v12; // eax
  char v13; // cl
  char *v14; // edx
  int v15; // edi
  char v16; // cl
  int i; // eax
  char *v18; // edx
  const idDecl *v19; // eax
  char *v20; // edi
  idDict *v21; // esi
  const idKeyValue *Key; // eax
  char *v23; // eax
  char *v24; // ebx
  const idKeyValue *v25; // eax
  const char *v26; // eax
  const char *v27; // ebp
  const idKeyValue *v28; // eax
  const char *v29; // edi
  const idKeyValue *v30; // eax
  idSessionLocal *v31; // esi
  idUserInterface *v32; // eax
  idUserInterface *guiLoading; // ecx
  idStr mapDeclName; // [esp+50h] [ebp-2Ch] BYREF
  int v36; // [esp+78h] [ebp-4h]

  v3 = 0;
  mapDeclName.len = 0;
  mapDeclName.alloced = 20;
  mapDeclName.data = mapDeclName.baseBuffer;
  mapDeclName.baseBuffer[0] = 0;
  if ( mapName )
  {
    v4 = &mapName[strlen(mapName) + 1];
    v3 = v4 - (mapName + 1);
    v5 = v4 - mapName;
    if ( v5 > 20 )
      idStr::ReAllocate(&mapDeclName, v5, 1);
    data = mapDeclName.data;
    v7 = mapName;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    mapDeclName.len = v3;
  }
  v9 = 0;
  v10 = *entityFilter == 0;
  v36 = 0;
  if ( !v10 )
  {
    do
      ++v9;
    while ( entityFilter[v9] );
    if ( v9 && !idAsyncNetwork::server.active && !idAsyncNetwork::client.active )
    {
      v11 = v3 + 1;
      if ( v11 + 1 > mapDeclName.alloced )
        idStr::ReAllocate(&mapDeclName, v11 + 1, 1);
      v12 = 0;
      v13 = 95;
      do
      {
        v14 = &mapDeclName.data[v12++];
        v14[mapDeclName.len] = v13;
        v13 = asc_1029F57C[v12];
      }
      while ( v13 );
      mapDeclName.len = v11;
      mapDeclName.data[v11] = 0;
      v15 = strlen(entityFilter) + mapDeclName.len;
      if ( v15 + 1 > mapDeclName.alloced )
        idStr::ReAllocate(&mapDeclName, v15 + 1, 1);
      v16 = *entityFilter;
      for ( i = 0; v16; v16 = entityFilter[i] )
      {
        v18 = &mapDeclName.data[i++];
        v18[mapDeclName.len] = v16;
      }
      mapDeclName.len = v15;
      mapDeclName.data[v15] = 0;
    }
  }
  v19 = declManager->FindType(declManager, 17, mapDeclName.data, 0, 0);
  if ( !v19 )
  {
    v24 = mapDeclName.data;
    v27 = &::entityFilter;
    v29 = "gfx/guis/loadscreens/generic";
LABEL_34:
    if ( idAsyncNetwork::server.active || idAsyncNetwork::client.active )
      v32 = uiManager->FindGui(uiManager, "guis/loading/mplevel.gui", 1, 0, 1);
    else
      v32 = uiManager->FindGui(uiManager, "guis/loading/generic.gui", 1, 0, 1);
    goto LABEL_41;
  }
  v20 = mapDeclName.data;
  v21 = (idDict *)&v19[1];
  Key = idDict::FindKey((idDict *)&v19[1], "name");
  if ( Key )
    v23 = Key->value->data;
  else
    v23 = v20;
  v24 = (char *)(*(int (__thiscall **)(netadrtype_t, char *, int))(*(_DWORD *)common.type + 168))(common.type, v23, -1);
  v25 = idDict::FindKey(v21, "objectives");
  if ( v25 )
    v26 = v25->value->data;
  else
    v26 = &::entityFilter;
  v27 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                        common.type,
                        v26,
                        -1);
  v28 = idDict::FindKey(v21, "loadimage");
  if ( v28 )
    v29 = v28->value->data;
  else
    v29 = "gfx/guis/loadscreens/generic";
  v30 = idDict::FindKey(v21, "loadgui");
  if ( v30 )
  {
    v31 = this;
    this->guiLoading = uiManager->FindGui(uiManager, v30->value->data, 1, 0, 1);
    goto LABEL_42;
  }
  if ( !v27 || !*v27 )
    goto LABEL_34;
  v32 = uiManager->FindGui(uiManager, "guis/loading/splevel.gui", 1, 0, 1);
LABEL_41:
  this->guiLoading = v32;
  v31 = this;
LABEL_42:
  guiLoading = v31->guiLoading;
  if ( guiLoading )
  {
    ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))guiLoading->SetStateFloat)(
      guiLoading,
      "map_loading",
      0);
    v31->guiLoading->SetStateString(v31->guiLoading, "loading_bkgnd", v29);
    v31->guiLoading->SetStateString(v31->guiLoading, "loading_levelname", v24);
    v31->guiLoading->SetStateString(v31->guiLoading, "loading_objectives", v27);
    declManager->FindMaterial(declManager, v29, 1)->sort = -2.0;
    v31->guiLoading->StateChanged(v31->guiLoading, com_frameTime, 0);
  }
  v36 = -1;
  idStr::FreeData(&mapDeclName);
}

// FUNC: public: int __thiscall idSessionLocal::GetBytesNeededForMapLoad(char const *,char const *)
int __thiscall idSessionLocal::GetBytesNeededForMapLoad(
        idSessionLocal *this,
        const char *mapName,
        const char *entityFilter)
{
  int v3; // edi
  const char *v4; // eax
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  int v9; // eax
  bool v10; // zf
  int v11; // edi
  int v12; // eax
  char v13; // cl
  char *v14; // edx
  int v15; // edi
  char v16; // cl
  int i; // eax
  char *v18; // edx
  const idDecl *v19; // esi
  const char *v20; // eax
  const idKeyValue *Key; // eax
  const char *v22; // eax
  int v23; // esi
  bool v25; // cc
  idStr mapDeclName; // [esp+10h] [ebp-2Ch] BYREF
  int v27; // [esp+38h] [ebp-4h]

  v3 = 0;
  mapDeclName.len = 0;
  mapDeclName.alloced = 20;
  mapDeclName.data = mapDeclName.baseBuffer;
  mapDeclName.baseBuffer[0] = 0;
  if ( mapName )
  {
    v4 = &mapName[strlen(mapName) + 1];
    v3 = v4 - (mapName + 1);
    v5 = v4 - mapName;
    if ( v5 > 20 )
      idStr::ReAllocate(&mapDeclName, v5, 1);
    data = mapDeclName.data;
    v7 = mapName;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    mapDeclName.len = v3;
  }
  v9 = 0;
  v10 = *entityFilter == 0;
  v27 = 0;
  if ( !v10 )
  {
    do
      ++v9;
    while ( entityFilter[v9] );
    if ( v9 )
    {
      v11 = v3 + 1;
      if ( v11 + 1 > mapDeclName.alloced )
        idStr::ReAllocate(&mapDeclName, v11 + 1, 1);
      v12 = 0;
      v13 = 95;
      do
      {
        v14 = &mapDeclName.data[v12++];
        v14[mapDeclName.len] = v13;
        v13 = asc_1029F57C[v12];
      }
      while ( v13 );
      mapDeclName.len = v11;
      mapDeclName.data[v11] = 0;
      v15 = strlen(entityFilter) + mapDeclName.len;
      if ( v15 + 1 > mapDeclName.alloced )
        idStr::ReAllocate(&mapDeclName, v15 + 1, 1);
      v16 = *entityFilter;
      for ( i = 0; v16; v16 = entityFilter[i] )
      {
        v18 = &mapDeclName.data[i++];
        v18[mapDeclName.len] = v16;
      }
      mapDeclName.len = v15;
      mapDeclName.data[v15] = 0;
    }
  }
  v19 = declManager->FindType(declManager, 17, mapDeclName.data, 0, 0);
  if ( v19 )
  {
    v20 = va("size%d", com_machineSpec.internalVar->integerValue < 0 ? 0 : com_machineSpec.internalVar->integerValue);
    Key = idDict::FindKey((idDict *)&v19[1], v20);
    if ( Key )
      v22 = Key->value->data;
    else
      v22 = "0";
    v23 = atoi(v22);
    v27 = -1;
    idStr::FreeData(&mapDeclName);
    return v23;
  }
  else
  {
    v25 = com_machineSpec.internalVar->integerValue < 2;
    v27 = -1;
    idStr::FreeData(&mapDeclName);
    if ( v25 )
      return 209715200;
    else
      return 419430400;
  }
}

// FUNC: public: void __thiscall idSessionLocal::SetBytesNeededForMapLoad(char const *,char const *,int)
void __thiscall idSessionLocal::SetBytesNeededForMapLoad(
        idSessionLocal *this,
        const char *mapName,
        const char *entityFilter,
        int bytesNeeded)
{
  int v4; // edi
  const char *v5; // eax
  int v6; // eax
  char *data; // edx
  const char *v8; // ecx
  char v9; // al
  int v10; // eax
  bool v11; // zf
  int v12; // edi
  int v13; // eax
  char v14; // cl
  char *v15; // edx
  int v16; // edi
  char v17; // cl
  int i; // eax
  char *v19; // edx
  idDeclEntityDef *v20; // eax
  idDeclEntityDef *v21; // ebx
  const char *v22; // esi
  const char *v23; // eax
  int v24; // eax
  char v25; // cl
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v27; // edx
  const char *v28; // eax
  const char *v29; // esi
  int v30; // edi
  char v31; // cl
  int j; // eax
  char *v33; // edx
  int v34; // esi
  int v35; // eax
  char v36; // cl
  char *v37; // edx
  int v38; // ebp
  idDict *p_dict; // eax
  int v40; // esi
  const idStr *v41; // eax
  const idStr *v42; // eax
  const idStr *v43; // eax
  idStr *v44; // esi
  int v45; // edi
  int k; // eax
  char v47; // cl
  char *v48; // edx
  int v49; // esi
  int v50; // eax
  char v51; // cl
  char *v52; // edx
  const idStr *v53; // [esp-18h] [ebp-FCh]
  idStr declText; // [esp+14h] [ebp-D0h] BYREF
  idDeclEntityDef *mapDef; // [esp+34h] [ebp-B0h]
  idStr mapDeclName; // [esp+38h] [ebp-ACh] BYREF
  idStr v57; // [esp+58h] [ebp-8Ch] BYREF
  idStr v58; // [esp+78h] [ebp-6Ch] BYREF
  idStr v59; // [esp+98h] [ebp-4Ch] BYREF
  idStr result; // [esp+B8h] [ebp-2Ch] BYREF
  int v61; // [esp+E0h] [ebp-4h]

  v4 = 0;
  mapDeclName.len = 0;
  mapDeclName.alloced = 20;
  mapDeclName.data = mapDeclName.baseBuffer;
  mapDeclName.baseBuffer[0] = 0;
  if ( mapName )
  {
    v5 = &mapName[strlen(mapName) + 1];
    v4 = v5 - (mapName + 1);
    v6 = v5 - mapName;
    if ( v6 > 20 )
      idStr::ReAllocate(&mapDeclName, v6, 1);
    data = mapDeclName.data;
    v8 = mapName;
    do
    {
      v9 = *v8;
      *data++ = *v8++;
    }
    while ( v9 );
    mapDeclName.len = v4;
  }
  v10 = 0;
  v11 = *entityFilter == 0;
  v61 = 0;
  if ( !v11 )
  {
    do
      ++v10;
    while ( entityFilter[v10] );
    if ( v10 )
    {
      v12 = v4 + 1;
      if ( v12 + 1 > mapDeclName.alloced )
        idStr::ReAllocate(&mapDeclName, v12 + 1, 1);
      v13 = 0;
      v14 = 95;
      do
      {
        v15 = &mapDeclName.data[v13++];
        v15[mapDeclName.len] = v14;
        v14 = asc_1029F57C[v13];
      }
      while ( v14 );
      mapDeclName.len = v12;
      mapDeclName.data[v12] = 0;
      v16 = strlen(entityFilter) + mapDeclName.len;
      if ( v16 + 1 > mapDeclName.alloced )
        idStr::ReAllocate(&mapDeclName, v16 + 1, 1);
      v17 = *entityFilter;
      for ( i = 0; v17; v17 = entityFilter[i] )
      {
        v19 = &mapDeclName.data[i++];
        v19[mapDeclName.len] = v17;
      }
      mapDeclName.len = v16;
      mapDeclName.data[v16] = 0;
    }
  }
  v20 = (idDeclEntityDef *)declManager->FindType(declManager, 17, mapDeclName.data, 0, 0);
  v11 = com_updateLoadSize.internalVar->integerValue == 0;
  v21 = v20;
  mapDef = v20;
  if ( !v11 && v20 )
  {
    v22 = va("size%d", com_machineSpec.internalVar->integerValue);
    v23 = va("%i", bytesNeeded);
    idDict::Set(&v21->dict, v22, v23);
    declText.alloced = 20;
    declText.data = declText.baseBuffer;
    declText.baseBuffer[0] = 0;
    v24 = 0;
    do
    {
      v25 = aMapdef_0[v24];
      declText.baseBuffer[v24++] = v25;
    }
    while ( v25 );
    declText.len = 9;
    base = v21->base;
    v27 = base->__vftable;
    LOBYTE(v61) = 1;
    v28 = v27->GetName(base);
    v29 = v28;
    if ( v28 )
    {
      v30 = strlen(v28) + declText.len;
      if ( v30 + 1 > declText.alloced )
        idStr::ReAllocate(&declText, v30 + 1, 1);
      v31 = *v29;
      for ( j = 0; v31; v31 = v29[j] )
      {
        v33 = &declText.data[j++];
        v33[declText.len] = v31;
      }
      declText.len = v30;
      declText.data[v30] = 0;
    }
    v34 = declText.len + 4;
    if ( declText.len + 5 > declText.alloced )
      idStr::ReAllocate(&declText, declText.len + 5, 1);
    v35 = 0;
    v36 = 32;
    do
    {
      v37 = &declText.data[v35++];
      v37[declText.len] = v36;
      v36 = asc_102A4C88[v35];
    }
    while ( v36 );
    declText.len = v34;
    declText.data[v34] = 0;
    v38 = 0;
    p_dict = &v21->dict;
    if ( v21->dict.args.num > 0 )
    {
      do
      {
        if ( v38 >= 0 && v38 < p_dict->args.num )
        {
          v40 = (int)&p_dict->args.list[v38];
          if ( v40 )
          {
            if ( idStr::Cmp(*(const char **)(*(_DWORD *)v40 + 4), "classname") )
            {
              v41 = operator+(&result, "\t\"", *(const idStr **)v40);
              LOBYTE(v61) = 2;
              v42 = operator+(&v58, v41, "\"\t\t\"");
              v53 = *(const idStr **)(v40 + 4);
              LOBYTE(v61) = 3;
              v43 = operator+(&v59, v42, v53);
              LOBYTE(v61) = 4;
              v44 = operator+(&v57, v43, "\"\r\n");
              v45 = v44->len + declText.len;
              LOBYTE(v61) = 5;
              if ( v45 + 1 > declText.alloced )
                idStr::ReAllocate(&declText, v45 + 1, 1);
              for ( k = 0; k < v44->len; v48[declText.len] = v47 )
              {
                v47 = v44->data[k];
                v48 = &declText.data[k++];
              }
              declText.len = v45;
              declText.data[v45] = 0;
              LOBYTE(v61) = 4;
              idStr::FreeData(&v57);
              LOBYTE(v61) = 3;
              idStr::FreeData(&v59);
              LOBYTE(v61) = 2;
              idStr::FreeData(&v58);
              LOBYTE(v61) = 1;
              idStr::FreeData(&result);
            }
          }
        }
        ++v38;
        p_dict = &mapDef->dict;
      }
      while ( v38 < mapDef->dict.args.num );
      v21 = mapDef;
    }
    v49 = declText.len + 1;
    if ( declText.len + 2 > declText.alloced )
      idStr::ReAllocate(&declText, declText.len + 2, 1);
    v50 = 0;
    v51 = 125;
    do
    {
      v52 = &declText.data[v50++];
      v52[declText.len] = v51;
      v51 = asc_102990B8[v50];
    }
    while ( v51 );
    declText.len = v49;
    declText.data[v49] = 0;
    v21->base->SetText(v21->base, declText.data);
    v21->base->ReplaceSourceFileText(v21->base);
    LOBYTE(v61) = 0;
    idStr::FreeData(&declText);
  }
  v61 = -1;
  idStr::FreeData(&mapDeclName);
}

// FUNC: void __cdecl TabComplete_f(class idCmdArgs const &)
void __cdecl TabComplete_f(const idCmdArgs *args)
{
  const idCmdArgs *v1; // ebx
  const char *v2; // esi
  int v3; // edi
  unsigned int v4; // eax
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  int v9; // eax
  char v10; // cl
  char *v11; // edx
  int v12; // ebp
  int v13; // esi
  int v14; // eax
  char v15; // cl
  char *v16; // edx
  const char *v17; // esi
  unsigned int v18; // eax
  int v19; // edi
  int v20; // eax
  char v21; // cl
  int v22; // eax
  char *v23; // edx
  int v24; // esi
  const char *v25; // eax
  const char **v26; // [esp+4h] [ebp-30h]
  idStr input; // [esp+8h] [ebp-2Ch] BYREF
  int v28; // [esp+30h] [ebp-4h]

  v1 = args;
  if ( args->argc <= 1 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "TabComplete_f() - Usage\n\ttabComplete <string>\n");
    return;
  }
  v2 = args->argv[1];
  v3 = 0;
  input.len = 0;
  input.alloced = 20;
  input.data = input.baseBuffer;
  input.baseBuffer[0] = 0;
  if ( v2 )
  {
    v4 = (unsigned int)&v2[strlen(v2) + 1];
    v3 = v4 - (_DWORD)(v2 + 1);
    v5 = v4 - (_DWORD)v2;
    if ( v5 > 20 )
      idStr::ReAllocate(&input, v5, 1);
    data = input.data;
    v7 = v2;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    input.len = v3;
  }
  v28 = 0;
  if ( v3 + 2 > input.alloced )
    idStr::ReAllocate(&input, v3 + 2, 1);
  v9 = 0;
  v10 = 32;
  do
  {
    v11 = &input.data[v9++];
    v11[input.len] = v10;
    v10 = src[v9];
  }
  while ( v10 );
  input.len = v3 + 1;
  v12 = 2;
  input.data[v3 + 1] = 0;
  if ( args->argc > 2 )
  {
    v26 = (const char **)&args->argv[2];
    while ( 1 )
    {
      v13 = input.len + 1;
      if ( input.len + 2 > input.alloced )
        idStr::ReAllocate(&input, input.len + 2, 1);
      v14 = 0;
      v15 = 32;
      do
      {
        v16 = &input.data[v14++];
        v16[input.len] = v15;
        v15 = src[v14];
      }
      while ( v15 );
      input.len = v13;
      input.data[v13] = 0;
      if ( v12 < 0 || v12 >= v1->argc )
        break;
      v17 = *v26;
      if ( *v26 )
        goto LABEL_22;
LABEL_28:
      ++v26;
      if ( ++v12 >= v1->argc )
        goto LABEL_29;
    }
    v17 = &entityFilter;
LABEL_22:
    v18 = (unsigned int)&v17[strlen(v17) + 1];
    v19 = v18 - (_DWORD)(v17 + 1) + input.len;
    v20 = v18 - (_DWORD)v17 + input.len;
    if ( v20 > input.alloced )
      idStr::ReAllocate(&input, v20, 1);
    v21 = *v17;
    v22 = 0;
    if ( *v17 )
    {
      do
      {
        v23 = &input.data[v22++];
        v23[input.len] = v21;
        v21 = v17[v22];
      }
      while ( v21 );
      v1 = args;
    }
    input.len = v19;
    input.data[v19] = 0;
    goto LABEL_28;
  }
LABEL_29:
  console->SetConsoleInput(console, input.data);
  console->TabComplete(console);
  v24 = *(_DWORD *)common.type;
  v25 = console->GetConsoleInput(console);
  (*(void (**)(netadrtype_t, const char *, ...))(v24 + 124))(common.type, "Console Input: %s\n", v25);
  console->SetConsoleInput(console, &entityFilter);
  v28 = -1;
  idStr::FreeData(&input);
}

// FUNC: public: void __thiscall idSessionLocal::Draw(void)
void __thiscall idSessionLocal::Draw(idSessionLocal *this)
{
  idUserInterface *guiLoading; // ecx
  idUserInterface *guiMsg; // ecx
  idUserInterface *guiActive; // eax
  idUserInterface *guiMsgRestore; // ecx
  idUserInterface *v6; // ecx
  idDict *v7; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  idUserInterface *v10; // eax
  idGame_vtbl *v11; // edi
  int v12; // eax
  idUserInterface *v13; // ecx
  idGame_vtbl *v14; // edi
  int v15; // eax
  int v16; // eax
  idGame_vtbl *v17; // ebx
  int v18; // edi
  int LocalClientNum; // eax
  idRenderSystem_vtbl *v20; // edi
  const idMaterial *v21; // eax
  bool fullConsole; // [esp+7h] [ebp-1h]

  fullConsole = 0;
  rvServerScanGUI::UpdateServerScanGUI(&this->serverScanGUI);
  if ( this->insideExecuteMapChange )
  {
    guiLoading = this->guiLoading;
    if ( guiLoading )
      guiLoading->Redraw(guiLoading, com_frameTime);
    guiMsg = this->guiMsg;
    if ( this->guiActive == guiMsg )
      goto LABEL_5;
  }
  else if ( this->pauseAfterMapChange )
  {
    guiActive = this->guiActive;
    if ( guiActive )
    {
      if ( guiActive == this->guiMsg )
      {
        guiMsgRestore = this->guiMsgRestore;
        if ( guiMsgRestore )
          guiMsgRestore->Redraw(guiMsgRestore, com_frameTime);
      }
      this->guiActive->Redraw(this->guiActive, com_frameTime);
    }
    else
    {
      this->pauseAfterMapChange = 0;
      soundSystem->SetActiveSoundWorld(soundSystem, 1);
      Sys_ClearEvents();
      idKeyInput::ClearStates();
    }
  }
  else
  {
    guiMsg = this->guiTest;
    if ( guiMsg )
    {
LABEL_5:
      guiMsg->Redraw(guiMsg, com_frameTime);
      goto LABEL_46;
    }
    v6 = this->guiActive;
    if ( !v6
      || ((v7 = (idDict *)v6->State(v6), (Key = idDict::FindKey(v7, "gameDraw")) == 0)
        ? (data = "0")
        : (data = Key->value->data),
          atoi(data)) )
    {
      if ( this->readDemo )
      {
        if ( this->portalSkyDemoRenderView.time )
          this->rw->RenderScene(this->rw, &this->portalSkyDemoRenderView, 0);
        this->rw->RenderScene(this->rw, &this->currentDemoRenderView, 0);
        renderSystem->DrawDemoPics(renderSystem);
      }
      else if ( this->mapSpawned )
      {
        if ( idSessionLocal::com_skipGameDraw.internalVar->integerValue
          || idSessionLocal::GetLocalClientNum(this) < 0
          || (v16 = Sys_Milliseconds(),
              v17 = game->__vftable,
              v18 = v16,
              LocalClientNum = idSessionLocal::GetLocalClientNum(this),
              LOBYTE(v17) = v17->Draw(game, LocalClientNum),
              time_gameDraw += Sys_Milliseconds() - v18,
              !(_BYTE)v17) )
        {
          renderSystem->SetColor(renderSystem, &colorBlack);
          v20 = renderSystem->__vftable;
          v21 = declManager->FindMaterial(declManager, "_white", 1);
          (*((void (__thiscall **)(idRenderSystem *, _DWORD, _DWORD, int, int, _DWORD, _DWORD, int, int, const idMaterial *))&v20->SetColor4
           + 1))(
            renderSystem,
            0,
            0,
            1142947840,
            1139802112,
            0,
            0,
            1065353216,
            1065353216,
            v21);
        }
        if ( this->writeDemo )
          renderSystem->WriteDemoPics(renderSystem);
      }
      else
      {
        console->Draw(console, 1);
        fullConsole = 1;
      }
    }
    else
    {
      v10 = this->guiActive;
      if ( (v10 == this->guiTakeNotes
         || v10 == this->guiBuildNotes
         || v10 == this->guiQANotes
         || v10 == this->guiEditCVars
         || v10 == this->guiSpawn)
        && !idSessionLocal::com_skipGameDraw.internalVar->integerValue )
      {
        v11 = game->__vftable;
        v12 = idSessionLocal::GetLocalClientNum(this);
        v11->Draw(game, v12);
      }
      if ( this->guiActive == this->guiMsg )
      {
        v13 = this->guiMsgRestore;
        if ( v13 )
          v13->Redraw(v13, com_frameTime);
      }
      if ( idAsyncNetwork::server.active || idAsyncNetwork::client.active )
      {
        v14 = game->__vftable;
        v15 = idSessionLocal::GetLocalClientNum(this);
        if ( v14->PlayerChatDisabled(game, v15) )
        {
          cvarSystem->SetCVarBool(cvarSystem, "ui_chat", 1, 0);
          cvarSystem->SetModifiedFlags(cvarSystem, 512);
        }
      }
      this->guiActive->Redraw(this->guiActive, com_frameTime);
    }
  }
LABEL_46:
  idSessionLocal::DrawWipeModel(this);
  idSessionLocal::DrawCmdGraph(this);
  if ( !fullConsole )
    console->Draw(console, 0);
}

// FUNC: public: virtual void __thiscall idSessionLocal::UpdateScreen(bool)
void __thiscall idSessionLocal::UpdateScreen(idSessionLocal *this, bool outOfSequence)
{
  idRenderSystem_vtbl *v3; // esi
  int v4; // eax
  int v5; // eax

  if ( (*(unsigned __int8 (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 16))(*(_DWORD *)common.ip)
    && !this->insideUpdateScreen )
  {
    this->insideUpdateScreen = 1;
    if ( outOfSequence )
      sys->GrabMouseCursor(sys, 0);
    v3 = renderSystem->__vftable;
    v4 = renderSystem->GetScreenHeight(renderSystem);
    v5 = ((int (__thiscall *)(idRenderSystem *, int))renderSystem->GetScreenWidth)(renderSystem, v4);
    ((void (__thiscall *)(idRenderSystem *, int))v3->BeginFrame)(renderSystem, v5);
    idSessionLocal::Draw(this);
    if ( com_speeds.internalVar->integerValue || com_debugHudActive || profile_netDebugActive )
    {
      renderSystem->EndFrame(renderSystem, &time_frontend, &time_backend, 0, 0);
      this->insideUpdateScreen = 0;
    }
    else
    {
      renderSystem->EndFrame(renderSystem, 0, 0, 0, 0);
      this->insideUpdateScreen = 0;
    }
  }
}

// FUNC: public: virtual bool __thiscall idSessionLocal::CheckKey(char const *,bool,bool)
char __thiscall idSessionLocal::CheckKey(idSessionLocal *this, const char *key, bool netConnect, bool offline_valid)
{
  char *v5; // eax
  char v6; // cl
  int i; // esi
  int j; // eax
  char v9; // bl
  char v10; // bl
  int v11; // esi
  int k; // esi
  unsigned int v13; // eax
  unsigned int v14; // ecx
  idSessionLocal_vtbl *v16; // eax
  char l_chk[5]; // [esp+Ch] [ebp-64h] BYREF
  char s_chk[5]; // [esp+14h] [ebp-5Ch] BYREF
  int checksumIndices[4]; // [esp+1Ch] [ebp-54h]
  char l_key[21]; // [esp+2Ch] [ebp-44h] BYREF
  idStr s_key; // [esp+44h] [ebp-2Ch] BYREF
  int v22; // [esp+6Ch] [ebp-4h]

  checksumIndices[0] = 6;
  checksumIndices[1] = 11;
  checksumIndices[2] = 15;
  checksumIndices[3] = 4;
  s_key.len = 0;
  s_key.alloced = 20;
  s_key.data = s_key.baseBuffer;
  s_key.baseBuffer[0] = 0;
  v22 = 0;
  s_chk[4] = 0;
  idStr::Copynz(l_key, key, 21);
  if ( l_key[0] )
  {
    v5 = l_key;
    do
    {
      v6 = *v5;
      if ( idStr::upperCaseCharacter[(unsigned __int8)*v5] )
        v6 = idStr::upperCaseCharacter[(unsigned __int8)*v5];
      *v5++ = v6;
    }
    while ( *v5 );
  }
  for ( i = 0; i < 22; ++i )
  {
    for ( j = 0; j < 4; ++j )
    {
      if ( checksumIndices[j] == i )
      {
        s_chk[j] = l_key[i];
        goto LABEL_15;
      }
    }
    v9 = l_key[i];
    if ( s_key.len + 2 > s_key.alloced )
      idStr::ReAllocate(&s_key, s_key.len + 2, 1);
    s_key.data[s_key.len++] = v9;
    s_key.data[s_key.len] = 0;
LABEL_15:
    ;
  }
  v10 = 1;
  v11 = 0;
  while ( strchr(CDKEY_DIGITS, s_key.data[v11]) )
  {
    if ( ++v11 >= 16 )
      goto LABEL_21;
  }
  v10 = 0;
LABEL_21:
  for ( k = 0; k < 4; ++k )
  {
    if ( !strchr(CDKEY_DIGITS, s_chk[k]) )
      goto LABEL_26;
  }
  if ( !v10
    || (l_chk[4] = 0,
        v13 = CRC32_BlockChecksum(s_key.data, 16),
        v14 = (unsigned __int16)(v13 ^ HIWORD(v13)),
        l_chk[0] = CDKEY_DIGITS[(unsigned __int16)v14 >> 12],
        l_chk[1] = CDKEY_DIGITS[(v14 >> 8) & 0xF],
        l_chk[2] = CDKEY_DIGITS[(unsigned __int8)(v13 ^ BYTE2(v13)) >> 4],
        l_chk[3] = CDKEY_DIGITS[((unsigned __int8)v13 ^ BYTE2(v13)) & 0xF],
        idStr::Icmp(s_chk, l_chk)) )
  {
LABEL_26:
    v22 = -1;
    idStr::FreeData(&s_key);
    return 0;
  }
  idStr::Copynz(this->cdkey, l_key, 21);
  v16 = this->__vftable;
  this->cdkey_state = 3 - netConnect;
  v16->WriteCDKey(this);
  if ( !netConnect )
    idSessionLocal::EmitGameAuth(this);
  this->SetCDKeyGuiVars(this);
  v22 = -1;
  idStr::FreeData(&s_key);
  return 1;
}

// FUNC: public: virtual void __thiscall idSessionLocal::GetCurrentMapName(class idStr &)
void __thiscall idSessionLocal::GetCurrentMapName(idSessionLocal *this, idStr *current)
{
  idStr *v3; // edi
  int v4; // ebx
  bool v5; // cc
  int i; // eax
  char v7; // cl
  int v8; // edx
  char *data; // eax
  idStr result; // [esp+8h] [ebp-2Ch] BYREF
  int v11; // [esp+30h] [ebp-4h]

  idStr::operator=(current, this->currentMapName.data);
  if ( this->currentFilterString.len )
  {
    v3 = operator+(&result, "-", &this->currentFilterString);
    v4 = v3->len + current->len;
    v5 = v4 + 1 <= current->alloced;
    v11 = 0;
    if ( !v5 )
      idStr::ReAllocate(current, v4 + 1, 1);
    for ( i = 0; i < v3->len; current->data[v8] = v7 )
    {
      v7 = v3->data[i];
      v8 = i + current->len;
      ++i;
    }
    data = current->data;
    current->len = v4;
    data[v4] = 0;
    v11 = -1;
    idStr::FreeData(&result);
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::SetLoadingText(char const *)
void __thiscall idSessionLocal::SetLoadingText(idSessionLocal *this, const char *loadingText)
{
  idStr *p_loadingStr; // esi
  char *v4; // eax
  unsigned int v5; // edi
  char v6; // cl
  int i; // eax
  char *data; // eax

  p_loadingStr = &this->loadingStr;
  v4 = (char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                 common.type,
                 "#str_107667",
                 -1);
  idStr::operator=(&this->loadingStr, v4);
  if ( loadingText )
  {
    v5 = strlen(loadingText) + p_loadingStr->len;
    if ( (signed int)(v5 + 1) > this->loadingStr.alloced )
      idStr::ReAllocate(&this->loadingStr, v5 + 1, 1);
    v6 = *loadingText;
    for ( i = 0; v6; v6 = loadingText[i] )
    {
      ++i;
      this->loadingStr.data[this->loadingStr.len - 1 + i] = v6;
    }
    data = this->loadingStr.data;
    p_loadingStr->len = v5;
    data[v5] = 0;
  }
  if ( this->guiLoading )
  {
    this->guiLoading->SetStateString(this->guiLoading, "server_loadinfo", this->loadingStr.data);
    this->guiLoading->StateChanged(this->guiLoading, com_frameTime, 0);
  }
  this->PacifierUpdate(this);
}

// FUNC: Session_PromptKey_f
void __cdecl Session_PromptKey_f(const idCmdArgs *args)
{
  char *data; // esi
  const char *v2; // eax
  const char *v3; // eax
  char *v4; // esi
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  int v8; // eax
  const char *v9; // eax
  idStr msg; // [esp+1Ch] [ebp-2Ch] BYREF
  int v11; // [esp+44h] [ebp-4h]

  if ( recursed )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "promptKey recursed - aborted");
  }
  else if ( cvarSystem->GetCVarInteger(cvarSystem, "net_serverDedicated") )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "promptKey on dedicated server, ignoring");
  }
  else
  {
    recursed = 1;
    while ( 1 )
    {
      if ( sessLocal.authEmitTimeout > 0 )
      {
        sessLocal.authWaitBox = 1;
        v6 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                             common.type,
                             "#str_107191",
                             -1);
        idSessionLocal::MessageBoxA(&sessLocal, MSG_WAIT, v6, 0, 1, 0, 0, 1);
        sessLocal.cdkey_state = CDKEY_OK;
        goto LABEL_16;
      }
      data = sessLocal.authMsg.data;
      if ( !*sessLocal.authMsg.data )
        data = (char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                         common.type,
                         "#str_104308",
                         -1);
      v2 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                           common.type,
                           "#str_104305",
                           -1);
      v3 = idSessionLocal::MessageBoxA(&sessLocal, MSG_CDKEY, data, v2, 1, 0, 0, 1);
      if ( !v3 )
        break;
      if ( idSessionLocal::CheckKey(&sessLocal, v3, 0, 0) )
      {
        if ( sessLocal.authEmitTimeout > 0 )
        {
          sessLocal.authWaitBox = 1;
          v7 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                               common.type,
                               "#str_107191",
                               -1);
          idSessionLocal::MessageBoxA(&sessLocal, MSG_WAIT, v7, 0, 1, 0, 0, 1);
          sessLocal.cdkey_state = CDKEY_OK;
        }
        idSessionLocal::WriteCDKey(&sessLocal);
        v8 = (*(int (__thiscall **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 168))(
               common.type,
               "#str_104305");
        v9 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                             common.type,
                             "#str_104307",
                             -1,
                             v8);
        idSessionLocal::MessageBoxA(&sessLocal, MSG_OK, v9, (const char *)0xFFFFFFFF, 1, 0, 0, 1);
        goto LABEL_16;
      }
      msg.len = 0;
      msg.alloced = 20;
      msg.data = msg.baseBuffer;
      msg.baseBuffer[0] = 0;
      v11 = 0;
      idAsyncNetwork::BuildInvalidKeyMsg(&msg, 0);
      v4 = msg.data;
      v5 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                           common.type,
                           "#str_104310",
                           -1);
      idSessionLocal::MessageBoxA(&sessLocal, MSG_OK, v4, v5, 1, 0, 0, 1);
      v11 = -1;
      idStr::FreeData(&msg);
    }
    if ( args->argc == 2 && !idStr::Icmp(args->argv[1], "force") )
    {
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "quit\n");
      cmdSystem->ExecuteCommandBuffer(cmdSystem);
    }
LABEL_16:
    recursed = 0;
  }
}

// FUNC: public: void __thiscall idSessionLocal::Clear(void)
void __thiscall idSessionLocal::Clear(idSessionLocal *this)
{
  idStr *p_currentMapName; // edi
  idStr *list; // eax
  char *v4; // edi
  idStr *v5; // eax
  char *v6; // edi
  idStr *p_authMsg; // esi

  p_currentMapName = &this->currentMapName;
  this->insideUpdateScreen = 0;
  this->insideExecuteMapChange = 0;
  this->pauseAfterMapChange = 0;
  this->objectiveFailed = 0;
  this->lastCheckPoint = -1;
  this->loadingSaveGame = 0;
  this->savegameFile = 0;
  this->savegameVersion = 0;
  idStr::FreeData(&this->currentMapName);
  p_currentMapName->len = 0;
  p_currentMapName->alloced = 20;
  p_currentMapName->data = p_currentMapName->baseBuffer;
  p_currentMapName->baseBuffer[0] = 0;
  idStr::FreeData(&this->currentFilterString);
  this->currentFilterString.len = 0;
  this->currentFilterString.alloced = 20;
  this->currentFilterString.data = this->currentFilterString.baseBuffer;
  this->currentFilterString.baseBuffer[0] = 0;
  idStr::FreeData(&this->aviDemoShortName);
  this->aviDemoShortName.len = 0;
  this->aviDemoShortName.alloced = 20;
  this->aviDemoShortName.data = this->aviDemoShortName.baseBuffer;
  this->aviDemoShortName.baseBuffer[0] = 0;
  idStr::FreeData(this->msgFireBack);
  this->msgFireBack[0].len = 0;
  this->msgFireBack[0].alloced = 20;
  this->msgFireBack[0].data = this->msgFireBack[0].baseBuffer;
  this->msgFireBack[0].baseBuffer[0] = 0;
  idStr::FreeData(&this->msgFireBack[1]);
  this->msgFireBack[1].len = 0;
  this->msgFireBack[1].alloced = 20;
  this->msgFireBack[1].data = this->msgFireBack[1].baseBuffer;
  this->msgFireBack[1].baseBuffer[0] = 0;
  this->timeHitch = 0;
  this->rw = 0;
  this->readDemo = 0;
  this->writeDemo = 0;
  this->renderdemoVersion = 0;
  this->cmdDemoFile = 0;
  this->syncNextGameFrame = 0;
  this->mapSpawned = 0;
  this->guiActive = 0;
  this->aviCaptureMode = 0;
  this->timeDemo = TD_NO;
  this->waitingOnBind = 0;
  this->lastPacifierTime = 0;
  this->msgRunning = 0;
  this->guiMsgRestore = 0;
  this->msgIgnoreButtons = 0;
  this->bytesNeededForMapLoad = 0;
  this->wipeHold = 0;
  this->wipeStopTic = 0;
  this->wipeStartTic = 1;
  list = this->loadGameList.list;
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
  this->loadGameList.list = 0;
  this->loadGameList.num = 0;
  this->loadGameList.size = 0;
  v5 = this->modsList.list;
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
  this->modsList.list = 0;
  this->modsList.num = 0;
  this->modsList.size = 0;
  this->authEmitTimeout = 0;
  this->authWaitBox = 0;
  p_authMsg = &this->authMsg;
  idStr::FreeData(p_authMsg);
  p_authMsg->len = 0;
  p_authMsg->alloced = 20;
  p_authMsg->data = p_authMsg->baseBuffer;
  p_authMsg->baseBuffer[0] = 0;
}

// FUNC: public: virtual void __thiscall idSessionLocal::Stop(void)
void __usercall idSessionLocal::Stop(idSessionLocal *this@<ecx>, int a2@<edi>)
{
  this->wipeHold = 0;
  this->wipeStopTic = 0;
  this->wipeStartTic = 1;
  idSessionLocal::UnloadMap(this);
  idAsyncClient::DisconnectFromServer(&idAsyncNetwork::client);
  idAsyncServer::Kill(&idAsyncNetwork::server, a2);
  idDemo::SessionStop(&idAsyncNetwork::demo);
  if ( soundSystem )
    soundSystem->StopAllSounds(soundSystem, 1);
  this->insideUpdateScreen = 0;
  this->insideExecuteMapChange = 0;
  this->pauseAfterMapChange = 0;
}

// FUNC: public: virtual void __thiscall idSessionLocal::Shutdown(void)
void __thiscall idSessionLocal::Shutdown(idSessionLocal *this)
{
  idRenderWorld *rw; // ecx
  idDict *persistentPlayerInfo; // edi
  int v4; // ebp
  idListGUI *guiMainMenu_MapList; // ecx
  const char *v6; // eax
  idListGUI *guiDedicated_PlayerList; // ecx
  idListGUI *guiAvailableMapList; // ecx
  idListGUI *guiCycleMapList; // ecx
  idListGUI *guiSysLinkAvailableMapList; // ecx
  idListGUI *guiSysLinkCycleMapList; // ecx
  idListGUI *guiQuickMatch; // ecx
  idListGUI *guiSaveGameList; // ecx

  if ( this->aviCaptureMode )
    idSessionLocal::EndAVICapture(this);
  this->Stop(this);
  bse->Shutdown(bse);
  rw = this->rw;
  if ( rw )
  {
    ((void (__thiscall *)(idRenderWorld *, int))rw->~idRenderWorld)(rw, 1);
    this->rw = 0;
    if ( soundSystem )
      soundSystem->SetRenderWorld(soundSystem, 0);
  }
  idDict::Clear(&this->mapSpawnData.serverInfo);
  idDict::Clear(&this->mapSpawnData.syncedCVars);
  persistentPlayerInfo = this->mapSpawnData.persistentPlayerInfo;
  v4 = 32;
  do
  {
    idDict::Clear((idDict *)((char *)persistentPlayerInfo - 1568));
    idDict::Clear(persistentPlayerInfo++);
    --v4;
  }
  while ( v4 );
  guiMainMenu_MapList = this->guiMainMenu_MapList;
  if ( guiMainMenu_MapList )
  {
    guiMainMenu_MapList->Shutdown(guiMainMenu_MapList);
    uiManager->FreeListGUI(uiManager, this->guiMainMenu_MapList);
    this->guiMainMenu_MapList = 0;
  }
  rvServerScanGUI::Clear(&this->serverScanGUI);
  v6 = cvarSystem->GetCVarString(cvarSystem, "fs_game");
  if ( !idStr::Icmp(v6, "q4basexenon") )
  {
    guiDedicated_PlayerList = this->guiDedicated_PlayerList;
    if ( guiDedicated_PlayerList )
    {
      guiDedicated_PlayerList->Shutdown(guiDedicated_PlayerList);
      uiManager->FreeListGUI(uiManager, this->guiDedicated_PlayerList);
      this->guiDedicated_PlayerList = 0;
    }
    guiAvailableMapList = this->guiAvailableMapList;
    if ( guiAvailableMapList )
    {
      guiAvailableMapList->Shutdown(guiAvailableMapList);
      uiManager->FreeListGUI(uiManager, this->guiAvailableMapList);
      this->guiAvailableMapList = 0;
    }
    guiCycleMapList = this->guiCycleMapList;
    if ( guiCycleMapList )
    {
      guiCycleMapList->Shutdown(guiCycleMapList);
      uiManager->FreeListGUI(uiManager, this->guiCycleMapList);
      this->guiCycleMapList = 0;
    }
    guiSysLinkAvailableMapList = this->guiSysLinkAvailableMapList;
    if ( guiSysLinkAvailableMapList )
    {
      guiSysLinkAvailableMapList->Shutdown(guiSysLinkAvailableMapList);
      uiManager->FreeListGUI(uiManager, this->guiSysLinkAvailableMapList);
      this->guiSysLinkAvailableMapList = 0;
    }
    guiSysLinkCycleMapList = this->guiSysLinkCycleMapList;
    if ( guiSysLinkCycleMapList )
    {
      guiSysLinkCycleMapList->Shutdown(guiSysLinkCycleMapList);
      uiManager->FreeListGUI(uiManager, this->guiSysLinkCycleMapList);
      this->guiSysLinkCycleMapList = 0;
    }
    guiQuickMatch = this->guiQuickMatch;
    if ( guiQuickMatch )
    {
      guiQuickMatch->Shutdown(guiQuickMatch);
      uiManager->FreeListGUI(uiManager, this->guiQuickMatch);
      this->guiQuickMatch = 0;
    }
    guiSaveGameList = this->guiSaveGameList;
    if ( guiSaveGameList )
    {
      guiSaveGameList->Shutdown(guiSaveGameList);
      uiManager->FreeListGUI(uiManager, this->guiSaveGameList);
      this->guiSaveGameList = 0;
      this->lastGuiSaveGameListSelection = -1;
    }
  }
  idSessionLocal::Clear(this);
}

// FUNC: public: void __thiscall idSessionLocal::StartWipe(char const *,bool)
void __thiscall idSessionLocal::StartWipe(idSessionLocal *this, const char *_wipeMaterial, bool hold)
{
  double v4; // st7
  float floatValue; // [esp+20h] [ebp-4h]

  console->Close(console);
  renderSystem->CropRenderSize(renderSystem, 640, 480, 1, 0);
  session->rw->PushMarkedDefs(session->rw);
  (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 52))(common.type, 1);
  idSessionLocal::Draw(this);
  renderSystem->CaptureRenderToImage(renderSystem, "_scratch");
  renderSystem->UnCrop(renderSystem);
  this->wipeMaterial = declManager->FindMaterial(declManager, _wipeMaterial, 0);
  this->wipeStartTic = com_ticNumber;
  floatValue = idSessionLocal::com_wipeSeconds.internalVar->floatValue;
  v4 = floatValue / (double)(*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
  this->wipeHold = hold;
  this->wipeStopTic = (int)(v4 * 1000.0 + (double)this->wipeStartTic);
}

// FUNC: Session_CompressDemo_f
void __cdecl Session_CompressDemo_f(const idCmdArgs *args)
{
  if ( args->argc == 2 )
  {
    idSessionLocal::CompressDemoFile(&sessLocal, "2", args->argv[1]);
  }
  else if ( args->argc == 3 )
  {
    idSessionLocal::CompressDemoFile(&sessLocal, args->argv[2], args->argv[1]);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "use: CompressDemo <file> [scheme]\nscheme is the same as com_compressDemo, defaults to 2");
  }
}

// FUNC: Session_PlayDemo_f
void __cdecl Session_PlayDemo_f(const idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // edi
  unsigned int v3; // eax
  int v4; // ebx
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  idStr v9; // [esp-20h] [ebp-2Ch] BYREF

  if ( args->argc >= 2 )
  {
    if ( args->argc <= 1 )
      v1 = &entityFilter;
    else
      v1 = args->argv[1];
    v2 = va("demos/%s", v1);
    v9.len = 0;
    v9.alloced = 20;
    v9.data = v9.baseBuffer;
    v9.baseBuffer[0] = 0;
    if ( v2 )
    {
      v3 = (unsigned int)&v2[strlen(v2) + 1];
      v4 = v3 - (_DWORD)(v2 + 1);
      v5 = v3 - (_DWORD)v2;
      if ( v5 > v9.alloced )
        idStr::ReAllocate(&v9, v5, 1);
      data = v9.data;
      v7 = v2;
      do
      {
        v8 = *v7;
        *data++ = *v7++;
      }
      while ( v8 );
      v9.len = v4;
    }
    idSessionLocal::StartPlayingRenderDemo(&sessLocal, v9);
  }
}

// FUNC: Session_TimeDemo_f
void __cdecl Session_TimeDemo_f(const idCmdArgs *args)
{
  int argc; // eax
  const char *v2; // ecx
  const char *v3; // eax
  bool v4; // [esp-4h] [ebp-4h]

  argc = args->argc;
  if ( args->argc >= 2 )
  {
    if ( argc <= 1 )
      v2 = &entityFilter;
    else
      v2 = args->argv[1];
    v4 = argc > 2;
    v3 = va("demos/%s", v2);
    idSessionLocal::TimeRenderDemo(&sessLocal, v3, v4);
  }
}

// FUNC: Session_TimeDemoQuit_f
void __cdecl Session_TimeDemoQuit_f(const idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // eax

  if ( args->argc <= 1 )
    v1 = &entityFilter;
  else
    v1 = args->argv[1];
  v2 = va("demos/%s", v1);
  idSessionLocal::TimeRenderDemo(&sessLocal, v2, 0);
  if ( sessLocal.timeDemo == TD_YES )
    sessLocal.timeDemo = TD_YES_THEN_QUIT;
}

// FUNC: Session_AVIDemo_f
void __cdecl Session_AVIDemo_f(const idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // eax

  if ( args->argc <= 1 )
    v1 = &entityFilter;
  else
    v1 = args->argv[1];
  v2 = va("demos/%s", v1);
  idSessionLocal::AVIRenderDemo(&sessLocal, v2);
}

// FUNC: Session_Disconnect_f
void __cdecl Session_Disconnect_f()
{
  idSessionLocal::Stop(&sessLocal);
  if ( sessLocal.guiMainMenu )
  {
    sessLocal.guiMainMenu->SetStateString(sessLocal.guiMainMenu, "inGame", "0");
    sessLocal.guiMainMenu->HandleNamedEvent(sessLocal.guiMainMenu, "onActivate");
    sessLocal.guiMainMenu->HandleNamedEvent(sessLocal.guiMainMenu, "MusicRestart");
  }
  idSessionLocal::StartMenu(&sessLocal, &entityFilter);
  if ( soundSystem )
    soundSystem->SetMute(soundSystem, 0);
}

// FUNC: public: void __thiscall idSessionLocal::ExecuteMapChange(bool,bool)
void __userpurge idSessionLocal::ExecuteMapChange(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        int a4@<edi>,
        int a5@<esi>,
        bool noFadeWipe,
        char noUnMute,
        char a8)
{
  const idKeyValue *Key; // eax
  const char *data; // esi
  unsigned int v11; // eax
  int v12; // edi
  int v13; // eax
  _BYTE *v14; // edx
  const char *v15; // ecx
  char v16; // al
  int v17; // eax
  char v18; // cl
  int v19; // esi
  int i; // eax
  char v21; // cl
  int v22; // edx
  const idKeyValue *v23; // eax
  const char *v24; // esi
  unsigned int v25; // eax
  unsigned int v26; // ebx
  int v27; // eax
  _BYTE *v28; // edx
  const char *v29; // ecx
  char v30; // al
  int len; // esi
  char *v32; // ecx
  _BYTE *v33; // edx
  char v34; // al
  char len_high; // bl
  bool v36; // cc
  char *v37; // eax
  unsigned int v38; // esi
  char *v39; // eax
  int v40; // eax
  char v41; // cl
  int v42; // esi
  int j; // eax
  char v44; // cl
  int v45; // edx
  idSessionLocal_vtbl *v46; // eax
  int v47; // esi
  idDict *persistentPlayerInfo; // edi
  int v49; // eax
  idStr *v50; // eax
  bool v51; // bl
  idFile *savegameFile; // edx
  char *v53; // esi
  idGame_vtbl *v54; // edi
  int v55; // eax
  int k; // esi
  idDict *v57; // eax
  const idKeyValue *v58; // eax
  const char *v59; // eax
  char *v60; // esi
  idGame_vtbl *v61; // edi
  int v62; // eax
  idNetworkSystem_vtbl *v63; // esi
  int v64; // eax
  char *v65; // esi
  char *v66; // edi
  int v67; // eax
  idNetworkSystem_vtbl *v68; // esi
  int v69; // eax
  int v70; // edx
  int m; // esi
  idNetworkSystem_vtbl *v72; // esi
  int v73; // eax
  int v74; // eax
  idUserInterface *guiLoading; // ecx
  idDict *v76; // eax
  const idKeyValue *v77; // eax
  const char *v78; // eax
  long double v79; // st7
  double v80; // st7
  int v81; // eax
  idUserInterface *guiTakeNotes; // ecx
  idUserInterface *guiBuildNotes; // ecx
  idUserInterface *guiQANotes; // ecx
  idUserInterface *guiEditCVars; // ecx
  idUserInterface *guiSpawn; // ecx
  const idKeyValue *v87; // eax
  char *v88; // eax
  const char *v89; // [esp+108h] [ebp-4E8h]
  int v91; // [esp+110h] [ebp-4E0h]
  int v93; // [esp+114h] [ebp-4DCh]
  bool reloadingSameMap; // [esp+11Bh] [ebp-4D5h]
  bool pcta; // [esp+11Ch] [ebp-4D4h]
  float pct; // [esp+11Ch] [ebp-4D4h]
  idDict *v97; // [esp+120h] [ebp-4D0h]
  bool active; // [esp+124h] [ebp-4CCh]
  idStr fullMapName; // [esp+128h] [ebp-4C8h] BYREF
  idStr namePlusMaps; // [esp+148h] [ebp-4A8h] BYREF
  idStr mapString; // [esp+168h] [ebp-488h] BYREF
  int start; // [esp+188h] [ebp-468h]
  idStr filterString; // [esp+18Ch] [ebp-464h] BYREF
  idStr lastMapName; // [esp+1ACh] [ebp-444h] BYREF
  char v105[1040]; // [esp+1D4h] [ebp-41Ch] BYREF
  int v106; // [esp+5ECh] [ebp-4h]

  ((void (__thiscall *)(idSoundSystem *, int, int, int))soundSystem->SetMute)(soundSystem, 1, a5, a3);
  soundSystem->StopAllSounds(soundSystem, -1);
  soundSystem->SetActiveSoundWorld(soundSystem, 0);
  if ( !a8 )
  {
    idSessionLocal::StartWipe(this, "gfx/wipes/fade", 1);
    idSessionLocal::CompleteWipe(this);
  }
  fullMapName.len = (int)&this->mapSpawnData;
  Key = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_map");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  mapString.alloced = 0;
  *(_DWORD *)&mapString.baseBuffer[4] = 20;
  *(_DWORD *)mapString.baseBuffer = &mapString.baseBuffer[8];
  mapString.baseBuffer[8] = 0;
  if ( data )
  {
    v11 = (unsigned int)&data[strlen(data) + 1];
    v12 = v11 - (_DWORD)(data + 1);
    v13 = v11 - (_DWORD)data;
    if ( v13 > 20 )
      idStr::ReAllocate((idStr *)&mapString.alloced, v13, 1);
    v14 = *(_BYTE **)mapString.baseBuffer;
    v15 = data;
    do
    {
      v16 = *v15;
      *v14++ = *v15++;
    }
    while ( v16 );
    mapString.alloced = v12;
  }
  ((void (__thiscall *)(idSessionLocal *, int, int))this->PacifierUpdate)(this, a4, a2);
  *(_DWORD *)&fullMapName.baseBuffer[8] = &fullMapName.baseBuffer[16];
  *(_DWORD *)&fullMapName.baseBuffer[12] = 20;
  fullMapName.baseBuffer[16] = 0;
  v17 = 0;
  do
  {
    v18 = aMaps_0[v17];
    fullMapName.baseBuffer[v17++ + 16] = v18;
  }
  while ( v18 );
  *(_DWORD *)&fullMapName.baseBuffer[4] = 5;
  v19 = *(_DWORD *)&mapString.baseBuffer[4] + 5;
  if ( *(_DWORD *)&mapString.baseBuffer[4] + 6 > *(int *)&fullMapName.baseBuffer[12] )
    idStr::ReAllocate((idStr *)&fullMapName.baseBuffer[4], *(_DWORD *)&mapString.baseBuffer[4] + 6, 1);
  for ( i = 0; i < *(int *)&mapString.baseBuffer[4]; *(_BYTE *)(v22 + *(_DWORD *)&fullMapName.baseBuffer[4]) = v21 )
  {
    v21 = *(_BYTE *)(*(_DWORD *)&mapString.baseBuffer[8] + i);
    v22 = i + *(_DWORD *)&fullMapName.baseBuffer[8];
    ++i;
  }
  *(_DWORD *)&fullMapName.baseBuffer[4] = v19;
  *(_BYTE *)(*(_DWORD *)&fullMapName.baseBuffer[8] + v19) = 0;
  idStr::StripFileExtension((idStr *)&fullMapName.baseBuffer[4]);
  idSessionLocal::UnloadMap(this);
  this->PacifierUpdate(this);
  console->SetProcFileOutOfDate(console, 0);
  v23 = idDict::FindKey((idDict *)fullMapName.alloced, "si_entityFilter");
  if ( v23 )
    v24 = v23->value->data;
  else
    v24 = &entityFilter;
  *(_DWORD *)&filterString.baseBuffer[4] = 0;
  *(_DWORD *)&filterString.baseBuffer[12] = 20;
  *(_DWORD *)&filterString.baseBuffer[8] = &filterString.baseBuffer[16];
  filterString.baseBuffer[16] = 0;
  if ( v24 )
  {
    v25 = (unsigned int)&v24[strlen(v24) + 1];
    v26 = v25 - (_DWORD)(v24 + 1);
    v27 = v25 - (_DWORD)v24;
    if ( v27 > 20 )
      idStr::ReAllocate((idStr *)&filterString.baseBuffer[4], v27, 1);
    v28 = *(_BYTE **)&filterString.baseBuffer[8];
    v29 = v24;
    do
    {
      v30 = *v29;
      *v28++ = *v29++;
    }
    while ( v30 );
    *(_DWORD *)&filterString.baseBuffer[4] = v26;
  }
  len = this->currentMapName.len;
  *(_DWORD *)&lastMapName.baseBuffer[4] = 0;
  *(_DWORD *)&lastMapName.baseBuffer[12] = 20;
  *(_DWORD *)&lastMapName.baseBuffer[8] = &lastMapName.baseBuffer[16];
  lastMapName.baseBuffer[16] = 0;
  if ( len + 1 > 20 )
    idStr::ReAllocate((idStr *)&lastMapName.baseBuffer[4], len + 1, 1);
  v32 = this->currentMapName.data;
  v33 = *(_BYTE **)&lastMapName.baseBuffer[8];
  do
  {
    v34 = *v32;
    *v33++ = *v32++;
  }
  while ( v34 );
  *(_DWORD *)&lastMapName.baseBuffer[4] = len;
  if ( idStr::Cmp(*(const char **)&fullMapName.baseBuffer[8], this->currentMapName.data)
    || idStr::Cmp(*(const char **)&filterString.baseBuffer[8], this->currentFilterString.data) )
  {
    fullMapName.data = *(char **)&fullMapName.baseBuffer[4];
    v36 = *(_DWORD *)&fullMapName.baseBuffer[4] + 1 <= this->currentMapName.alloced;
    HIBYTE(fullMapName.len) = 0;
    if ( !v36 )
      idStr::ReAllocate(&this->currentMapName, *(_DWORD *)&fullMapName.baseBuffer[4] + 1, 0);
    v37 = fullMapName.data;
    qmemcpy(this->currentMapName.data, *(const void **)&fullMapName.baseBuffer[8], (unsigned int)fullMapName.data);
    fullMapName.data[(unsigned int)this->currentMapName.data] = 0;
    this->currentMapName.len = (int)v37;
    v38 = *(_DWORD *)&filterString.baseBuffer[4];
    v36 = *(_DWORD *)&filterString.baseBuffer[4] + 1 <= this->currentFilterString.alloced;
    fullMapName.data = *(char **)&filterString.baseBuffer[4];
    if ( !v36 )
      idStr::ReAllocate(&this->currentFilterString, *(_DWORD *)&filterString.baseBuffer[4] + 1, 0);
    v39 = fullMapName.data;
    qmemcpy(this->currentFilterString.data, *(const void **)&filterString.baseBuffer[8], v38);
    fullMapName.data[(unsigned int)this->currentFilterString.data] = 0;
    this->currentFilterString.len = (int)v39;
    len_high = HIBYTE(fullMapName.len);
    this->lastCheckPoint = -1;
  }
  else
  {
    len_high = 1;
    HIBYTE(fullMapName.len) = 1;
  }
  fileSystem->SetAssetLogName(fileSystem, *(const char **)&fullMapName.baseBuffer[8]);
  if ( !len_high && cvarSystem->GetCVarBool(cvarSystem, "com_SingleDeclFile") )
  {
    declManager->FlushDecls(declManager);
    declManager->StartLoadingDecls(declManager);
    declManager->LoadDeclsFromFile(declManager);
    declManager->LoadDeclsFromFile(declManager);
    declManager->FinishLoadingDecls(declManager);
  }
  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 48))(*(_DWORD *)common.ip);
  if ( !len_high )
  {
    this->PacifierUpdate(this);
    declManager->BeginLevelLoad(declManager);
    this->PacifierUpdate(this);
    renderSystem->BeginLevelLoad(renderSystem);
    this->PacifierUpdate(this);
    soundSystem->BeginLevelLoad(soundSystem, *(const char **)&fullMapName.baseBuffer[8]);
    this->PacifierUpdate(this);
    bse->BeginLevelLoad(bse);
    *(_DWORD *)&namePlusMaps.baseBuffer[12] = 20;
    *(_DWORD *)&namePlusMaps.baseBuffer[8] = &namePlusMaps.baseBuffer[16];
    namePlusMaps.baseBuffer[16] = 0;
    v40 = 0;
    do
    {
      v41 = aMaps_0[v40];
      namePlusMaps.baseBuffer[v40++ + 16] = v41;
    }
    while ( v41 );
    *(_DWORD *)&namePlusMaps.baseBuffer[4] = 5;
    v42 = thePreviousMap.len + 5;
    if ( thePreviousMap.len + 6 > *(int *)&namePlusMaps.baseBuffer[12] )
      idStr::ReAllocate((idStr *)&namePlusMaps.baseBuffer[4], thePreviousMap.len + 6, 1);
    for ( j = 0; j < thePreviousMap.len; *(_BYTE *)(v45 + *(_DWORD *)&namePlusMaps.baseBuffer[4]) = v44 )
    {
      v44 = thePreviousMap.data[j];
      v45 = j + *(_DWORD *)&namePlusMaps.baseBuffer[8];
      ++j;
    }
    *(_DWORD *)&namePlusMaps.baseBuffer[4] = v42;
    *(_BYTE *)(*(_DWORD *)&namePlusMaps.baseBuffer[8] + v42) = 0;
    collisionModelManager->FreeMap(collisionModelManager, *(const char **)&namePlusMaps.baseBuffer[8]);
    collisionModelManager->PurgeModels(collisionModelManager);
    idStr::FreeData((idStr *)&namePlusMaps.baseBuffer[4]);
  }
  uiManager->BeginLevelLoad(uiManager);
  this->PacifierUpdate(this);
  uiManager->Reload(uiManager, 1);
  idSessionLocal::LoadLoadingGui(
    this,
    *(const char **)&mapString.baseBuffer[8],
    *(const char **)&filterString.baseBuffer[8]);
  this->insideExecuteMapChange = 1;
  this->pauseAfterMapChange = 0;
  idSessionLocal::ClearLoadingScreen(this);
  idSessionLocal::SetupLoadingScreen(this);
  fileSystem->ResetReadCount(fileSystem);
  if ( len_high )
    this->bytesNeededForMapLoad = 31457280;
  else
    this->bytesNeededForMapLoad = idSessionLocal::GetBytesNeededForMapLoad(
                                    this,
                                    *(const char **)&mapString.baseBuffer[8],
                                    *(const char **)&filterString.baseBuffer[8]);
  v46 = this->__vftable;
  this->wipeHold = 0;
  this->wipeStopTic = 0;
  this->wipeStartTic = 1;
  v46->ExitMenu(this);
  idSessionLocal::ShowLoadingGui(this);
  (*(void (__thiscall **)(netadrtype_t, _DWORD))(*(_DWORD *)common.type + 148))(
    common.type,
    *(_DWORD *)&mapString.baseBuffer[8]);
  sys->GrabMouseCursor(sys, 0);
  if ( !idAsyncNetwork::server.active && !idAsyncNetwork::client.active )
    this->numClients = 1;
  *(_DWORD *)filterString.baseBuffer = Sys_Milliseconds();
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "------------ Map Initialization -------------\n");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "Map: %s\n",
    *(_DWORD *)&mapString.baseBuffer[8]);
  this->PacifierUpdate(this);
  if ( !this->rw->InitFromMap(this->rw, *(const char **)&fullMapName.baseBuffer[8]) )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "couldn't load %s",
      *(_DWORD *)&fullMapName.baseBuffer[4]);
  this->PacifierUpdate(this);
  usercmdGen->InitForNewMap(usercmdGen);
  v47 = 0;
  memset(this->mapSpawnData.mapSpawnUsercmd, 0, sizeof(this->mapSpawnData.mapSpawnUsercmd));
  if ( this->numClients > 0 )
  {
    persistentPlayerInfo = this->mapSpawnData.persistentPlayerInfo;
    do
    {
      v49 = ((int (__thiscall *)(idSessionLocal *))this->PacifierUpdate)(this);
      LOBYTE(v49) = idAsyncNetwork::client.active;
      game->SetUserInfo(game, v47, (const idDict *)&persistentPlayerInfo[-36].argHash, v49);
      game->SetPersistentPlayerInfo(game, v47++, persistentPlayerInfo++);
    }
    while ( v47 < this->numClients );
  }
  if ( this->loadingSaveGame && this->savegameFile )
  {
    v50 = operator+((idStr *)namePlusMaps.baseBuffer, (const idStr *)fullMapName.baseBuffer, ".map");
    noUnMute = 5;
    v51 = !game->InitFromSaveGame(game, v50->data, this->rw, this->savegameFile);
    LOBYTE(v106) = 3;
    idStr::FreeData(&namePlusMaps);
    if ( v51 )
    {
      savegameFile = this->savegameFile;
      this->loadingSaveGame = 0;
      fileSystem->CloseFile(fileSystem, savegameFile);
      this->savegameFile = 0;
      ((void (__thiscall *)(idGame *))game->SetServerInfo)(game);
      v53 = operator+(&namePlusMaps, &fullMapName, ".map")->data;
      pcta = idAsyncNetwork::client.active;
      v54 = game->__vftable;
      LOBYTE(v106) = 6;
      active = idAsyncNetwork::server.active;
      v55 = Sys_Milliseconds();
      v54->InitFromNewMap(game, v53, this->rw, active, pcta, v55);
      LOBYTE(v106) = 3;
      idStr::FreeData(&namePlusMaps);
    }
    len_high = reloadingSameMap;
  }
  else
  {
    ((void (__thiscall *)(idGame *, char *, int))game->SetServerInfo)(game, fullMapName.data, v93);
    v60 = operator+((idStr *)&namePlusMaps.baseBuffer[8], (const idStr *)&fullMapName.baseBuffer[8], ".map")->data;
    fullMapName.baseBuffer[4] = idAsyncNetwork::client.active;
    v61 = game->__vftable;
    LOBYTE(fullMapName.alloced) = idAsyncNetwork::server.active;
    v62 = Sys_Milliseconds();
    v61->InitFromNewMap(game, v60, this->rw, fullMapName.alloced, *(_DWORD *)&fullMapName.baseBuffer[4], v62);
    LOBYTE(v106) = 3;
    idStr::FreeData(&namePlusMaps);
  }
  this->PacifierUpdate(this);
  if ( com_Bundler.internalVar->integerValue && this->IsMultiplayer(this) )
    this->PrecacheMPSettingsMenu(this);
  if ( !idAsyncNetwork::server.active && !idAsyncNetwork::client.active && !this->loadingSaveGame )
  {
    for ( k = 0; k < this->numClients; ++k )
    {
      this->PacifierUpdate(this);
      game->SpawnPlayer(game, k);
      if ( game->GetUserInfo(game, k) )
      {
        v57 = (idDict *)((int (__thiscall *)(idGame *, int, const char *))game->GetUserInfo)(game, k, v89);
        v58 = idDict::FindKey(v57, "ui_name");
        if ( v58 )
          v59 = v58->value->data;
        else
          v59 = &entityFilter;
        v89 = v59;
        ((void (__thiscall *)(idNetworkSystem *))networkSystem->SetLoadingText)(networkSystem);
      }
    }
  }
  if ( !len_high )
  {
    v63 = networkSystem->__vftable;
    v64 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_107669",
            -1);
    v63->SetLoadingText(networkSystem, (const char *)v64);
    this->PacifierUpdate(this);
    bse->EndLevelLoad(bse);
    this->PacifierUpdate(this);
    renderSystem->EndLevelLoad(renderSystem);
    soundSystem->EndLevelLoad(soundSystem, fullMapName.data);
    declManager->EndLevelLoad(declManager);
    v65 = filterString.data;
    v66 = mapString.data;
    v67 = fileSystem->GetReadCount(fileSystem);
    idSessionLocal::SetBytesNeededForMapLoad(this, v66, v65, v67);
  }
  this->PacifierUpdate(this);
  uiManager->EndLevelLoad(uiManager);
  if ( !idAsyncNetwork::server.active && !idAsyncNetwork::client.active && !this->loadingSaveGame )
  {
    v68 = networkSystem->__vftable;
    v69 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_107737",
            -1,
            v91,
            v93);
    v68->SetLoadingText(networkSystem, (const char *)v69);
    for ( m = 0; m < 10; ++m )
    {
      LOBYTE(v70) = m == 9;
      (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 52))(common.type, v70);
      game->RunFrame(game, (gameReturn_t *)v105, this->mapSpawnData.mapSpawnUsercmd, 0, 1);
    }
    session->rw->PushMarkedDefs(session->rw);
    v72 = networkSystem->__vftable;
    v73 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_107738",
            -1);
    v72->SetLoadingText(networkSystem, (const char *)v73);
  }
  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 52))(*(_DWORD *)common.ip);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
  v74 = Sys_Milliseconds();
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%6d msec to load %s\n",
    v74 - start,
    mapString.data);
  this->PacifierUpdate(this);
  this->rw->GenerateAllInteractions(this->rw);
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 144))(common.type);
  guiLoading = this->guiLoading;
  if ( guiLoading && this->bytesNeededForMapLoad )
  {
    v76 = (idDict *)guiLoading->State(guiLoading);
    v77 = idDict::FindKey(v76, "map_loading");
    if ( v77 )
      v78 = v77->value->data;
    else
      v78 = "0";
    v79 = atof(v78);
    pct = v79;
    if ( v79 >= 0.0 )
    {
      if ( pct < 1.0 )
        goto LABEL_96;
    }
    else
    {
      pct = 0.0;
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))this->guiLoading->SetStateFloat)(
        this->guiLoading,
        "map_loading",
        0);
      while ( 1 )
      {
        this->guiLoading->StateChanged(this->guiLoading, com_frameTime, 0);
        Sys_GenerateEvents();
        this->UpdateScreen(this, 1);
        v80 = pct + 0.050000001;
        pct = v80;
        if ( v80 >= 1.0 )
          break;
LABEL_96:
        ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))this->guiLoading->SetStateFloat)(
          this->guiLoading,
          "map_loading",
          LODWORD(pct));
      }
    }
  }
  this->PacifierUpdate(this);
  idSessionLocal::StartWipe(this, "gfx/wipes/fade_blend", 0);
  this->PacifierUpdate(this);
  usercmdGen->Clear(usercmdGen);
  this->logIndex = 0;
  v81 = com_ticNumber;
  this->latchedTicNumber = com_ticNumber;
  this->lastGameTic = v81;
  console->ClearNotifyLines(console);
  guiTakeNotes = this->guiTakeNotes;
  if ( guiTakeNotes )
  {
    guiTakeNotes->SetStateInt(guiTakeNotes, "init", 0);
    this->guiTakeNotes->StateChanged(this->guiTakeNotes, com_frameTime, 0);
    if ( com_makingBuild.internalVar->integerValue )
    {
      this->guiActive = this->guiTakeNotes;
      idSessionLocal::InitNotes(this, 1, "None");
      this->guiActive = 0;
    }
  }
  guiBuildNotes = this->guiBuildNotes;
  if ( guiBuildNotes )
  {
    guiBuildNotes->SetStateInt(guiBuildNotes, "init2", 0);
    this->guiBuildNotes->StateChanged(this->guiBuildNotes, com_frameTime, 0);
  }
  guiQANotes = this->guiQANotes;
  if ( guiQANotes )
  {
    guiQANotes->SetStateInt(guiQANotes, "initQA", 0);
    this->guiQANotes->StateChanged(this->guiQANotes, com_frameTime, 0);
  }
  guiEditCVars = this->guiEditCVars;
  if ( guiEditCVars )
  {
    guiEditCVars->SetStateInt(guiEditCVars, "init", 0);
    this->guiEditCVars->StateChanged(this->guiEditCVars, com_frameTime, 0);
  }
  guiSpawn = this->guiSpawn;
  if ( guiSpawn )
  {
    guiSpawn->SetStateInt(guiSpawn, "init", 0);
    this->guiSpawn->StateChanged(this->guiSpawn, com_frameTime, 0);
  }
  idSessionLocal::ClearLoadingScreen(this);
  this->insideExecuteMapChange = 0;
  Sys_SetPhysicalWorkMemory(-1, -1);
  if ( !noUnMute )
    soundSystem->SetMute(soundSystem, 0);
  this->mapSpawned = 1;
  Sys_ClearEvents();
  v87 = idDict::FindKey(v97, "si_map");
  if ( v87 )
    v88 = v87->value->data;
  else
    v88 = (char *)&entityFilter;
  idStr::operator=(&thePreviousMap, v88);
  LOBYTE(v106) = 2;
  idStr::FreeData(&lastMapName);
  LOBYTE(v106) = 1;
  idStr::FreeData(&filterString);
  LOBYTE(v106) = 0;
  idStr::FreeData(&fullMapName);
  v106 = -1;
  idStr::FreeData(&mapString);
}

// FUNC: public: virtual void __thiscall idSessionLocal::QuickMapChange(char const *)
void __userpurge idSessionLocal::QuickMapChange(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        const char *newMap)
{
  idDict *userInfo; // edi
  idDict *v6; // eax
  idDict *v7; // eax
  const char *v8; // eax
  char v9; // [esp+0h] [ebp-8h]

  userInfo = this->mapSpawnData.userInfo;
  idDict::Clear(this->mapSpawnData.userInfo);
  idDict::Clear(this->mapSpawnData.persistentPlayerInfo);
  v6 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 512);
  idDict::operator=(userInfo, v6);
  idDict::Clear(&this->mapSpawnData.serverInfo);
  v7 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 1024);
  idDict::operator=(&this->mapSpawnData.serverInfo, v7);
  idDict::Set(&this->mapSpawnData.serverInfo, "si_map", newMap);
  v8 = va("%i", 1);
  idDict::Set(&this->mapSpawnData.serverInfo, "si_numPlayers", v8);
  idDict::Set(&this->mapSpawnData.serverInfo, "si_gameType", "singleplayer");
  idSessionLocal::ExecuteMapChange(this, a2, a3, (int)&this->mapSpawnData, (int)this, 0, 0, v9);
  this->guiActive = 0;
  soundSystem->SetActiveSoundWorld(soundSystem, 1);
}

// FUNC: public: __thiscall idSessionLocal::idSessionLocal(void)
void __thiscall idSessionLocal::idSessionLocal(idSessionLocal *this)
{
  this->__vftable = (idSessionLocal_vtbl *)&idSessionLocal::`vftable';
  mapSpawnData_t::mapSpawnData_t(&this->mapSpawnData);
  this->currentMapName.len = 0;
  this->currentMapName.alloced = 20;
  this->currentMapName.data = this->currentMapName.baseBuffer;
  this->currentMapName.baseBuffer[0] = 0;
  this->currentFilterString.len = 0;
  this->currentFilterString.alloced = 20;
  this->currentFilterString.data = this->currentFilterString.baseBuffer;
  this->currentFilterString.baseBuffer[0] = 0;
  this->aviDemoShortName.len = 0;
  this->aviDemoShortName.alloced = 20;
  this->aviDemoShortName.data = this->aviDemoShortName.baseBuffer;
  this->aviDemoShortName.baseBuffer[0] = 0;
  rvServerScanGUI::rvServerScanGUI(&this->serverScanGUI);
  this->masterMapList.granularity = 16;
  this->masterMapList.list = 0;
  this->masterMapList.num = 0;
  this->masterMapList.size = 0;
  `eh vector constructor iterator'(
    this->msgFireBack,
    0x20u,
    2,
    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  this->loadGameList.granularity = 16;
  this->loadGameList.list = 0;
  this->loadGameList.num = 0;
  this->loadGameList.size = 0;
  this->modsList.granularity = 16;
  this->modsList.list = 0;
  this->modsList.num = 0;
  this->modsList.size = 0;
  this->mpAvailMapList.granularity = 16;
  this->mpAvailMapList.list = 0;
  this->mpAvailMapList.num = 0;
  this->mpAvailMapList.size = 0;
  this->mpCycleMapList.granularity = 16;
  this->mpCycleMapList.list = 0;
  this->mpCycleMapList.num = 0;
  this->mpCycleMapList.size = 0;
  this->authMsg.len = 0;
  this->authMsg.alloced = 20;
  this->authMsg.data = this->authMsg.baseBuffer;
  this->authMsg.baseBuffer[0] = 0;
  this->loadingStr.len = 0;
  this->loadingStr.alloced = 20;
  this->loadingStr.data = this->loadingStr.baseBuffer;
  this->loadingStr.baseBuffer[0] = 0;
  this->guiMsgRestore = 0;
  this->guiMsg = 0;
  this->guiActive = 0;
  this->guiGameOver = 0;
  this->guiLoading = 0;
  this->guiRestartMenu = 0;
  this->guiIntro = 0;
  this->guiMainMenu = 0;
  this->guiInGame = 0;
  this->guiQANotes = 0;
  this->guiTakeNotes = 0;
  this->guiTest = 0;
  this->guiMPSettings = 0;
  this->guiDedicated = 0;
  this->guiXboxInGame = 0;
  this->guiBuildNotes = 0;
  this->guiSpawn = 0;
  this->guiEditCVars = 0;
  idSessionLocal::Clear(this);
}

// FUNC: public: virtual __thiscall idSessionLocal::~idSessionLocal(void)
void __thiscall idSessionLocal::~idSessionLocal(idSessionLocal *this)
{
  idStr *list; // eax
  char *v3; // edi
  idStr *v4; // eax
  char *v5; // edi
  idStr *v6; // eax
  char *v7; // edi
  idStr *v8; // eax
  char *v9; // edi
  idStr *v10; // eax
  char *v11; // edi

  this->__vftable = (idSessionLocal_vtbl *)&idSessionLocal::`vftable';
  idStr::FreeData(&this->loadingStr);
  idStr::FreeData(&this->authMsg);
  list = this->mpCycleMapList.list;
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
  this->mpCycleMapList.list = 0;
  this->mpCycleMapList.num = 0;
  this->mpCycleMapList.size = 0;
  v4 = this->mpAvailMapList.list;
  if ( v4 )
  {
    v5 = &v4[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v4,
      0x20u,
      *(_DWORD *)&v4[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v5);
  }
  this->mpAvailMapList.list = 0;
  this->mpAvailMapList.num = 0;
  this->mpAvailMapList.size = 0;
  v6 = this->modsList.list;
  if ( v6 )
  {
    v7 = &v6[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v6,
      0x20u,
      *(_DWORD *)&v6[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v7);
  }
  this->modsList.list = 0;
  this->modsList.num = 0;
  this->modsList.size = 0;
  v8 = this->loadGameList.list;
  if ( v8 )
  {
    v9 = &v8[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v8,
      0x20u,
      *(_DWORD *)&v8[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v9);
  }
  this->loadGameList.list = 0;
  this->loadGameList.num = 0;
  this->loadGameList.size = 0;
  `eh vector destructor iterator'(
    this->msgFireBack,
    0x20u,
    2,
    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  v10 = this->masterMapList.list;
  if ( v10 )
  {
    v11 = &v10[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v10,
      0x20u,
      *(_DWORD *)&v10[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v11);
  }
  this->masterMapList.list = 0;
  this->masterMapList.num = 0;
  this->masterMapList.size = 0;
  rvServerScanGUI::~rvServerScanGUI(&this->serverScanGUI);
  idStr::FreeData(&this->aviDemoShortName);
  idStr::FreeData(&this->currentFilterString);
  idStr::FreeData(&this->currentMapName);
  mapSpawnData_t::~mapSpawnData_t(&this->mapSpawnData);
  this->__vftable = (idSessionLocal_vtbl *)&idSession::`vftable';
}

// FUNC: public: void __thiscall idSessionLocal::MoveToNewMap(char const *,char const *)
void __userpurge idSessionLocal::MoveToNewMap(
        idSessionLocal *this@<ecx>,
        int a2@<ebp>,
        const char *mapName,
        const char *entityFilter)
{
  mapSpawnData_t *p_mapSpawnData; // edi
  const idKeyValue *Key; // eax
  const char *data; // eax
  const idKeyValue *v8; // eax
  const char *v9; // eax
  const idKeyValue *v10; // eax
  const char *v11; // eax
  const idKeyValue *v12; // eax
  const char *v13; // eax
  const idKeyValue *v14; // eax
  const char *v15; // eax
  idUserInterface *guiLoading; // eax
  idSessionLocal_vtbl *v17; // edx
  idWindow *v18; // eax
  char v19; // [esp+0h] [ebp-Ch]
  unsigned int v20; // [esp+0h] [ebp-Ch]

  p_mapSpawnData = &this->mapSpawnData;
  idDict::Set(&this->mapSpawnData.serverInfo, "si_map", mapName);
  idDict::Set(&p_mapSpawnData->serverInfo, "si_entityFilter", entityFilter);
  Key = idDict::FindKey(&p_mapSpawnData->serverInfo, "si_gameType");
  if ( Key )
    data = Key->value->data;
  else
    data = &::entityFilter;
  cvarSystem->SetCVarString(cvarSystem, "si_gameType", data, 0);
  v8 = idDict::FindKey(&p_mapSpawnData->serverInfo, "si_numPlayers");
  if ( v8 )
    v9 = v8->value->data;
  else
    v9 = &::entityFilter;
  cvarSystem->SetCVarString(cvarSystem, "si_numPlayers", v9, 0);
  v10 = idDict::FindKey(&p_mapSpawnData->serverInfo, "si_map");
  if ( v10 )
    v11 = v10->value->data;
  else
    v11 = &::entityFilter;
  cvarSystem->SetCVarString(cvarSystem, "si_map", v11, 0);
  v12 = idDict::FindKey(&p_mapSpawnData->serverInfo, "si_name");
  if ( v12 )
    v13 = v12->value->data;
  else
    v13 = &::entityFilter;
  cvarSystem->SetCVarString(cvarSystem, "si_name", v13, 0);
  cvarSystem->SetCVarString(cvarSystem, "si_entityFilter", entityFilter, 0);
  idSessionLocal::ExecuteMapChange(this, (int)entityFilter, a2, (int)p_mapSpawnData, (int)this, 0, 1, v19);
  v14 = idDict::FindKey(&p_mapSpawnData->serverInfo, "devmap");
  if ( v14 )
    v15 = v14->value->data;
  else
    v15 = "0";
  if ( !atoi(v15) )
    idSessionLocal::SaveGame(this, 0, ST_AUTO);
  if ( idSessionLocal::com_skipLevelLoadPause.internalVar->integerValue || (guiLoading = this->guiLoading) == 0 )
  {
    this->SetGUI(this, 0, 0);
    soundSystem->SetMute(soundSystem, 0);
  }
  else
  {
    v17 = this->__vftable;
    this->pauseAfterMapChange = 1;
    v17->SetGUI(this, guiLoading, 0);
    soundSystem->SetMute(soundSystem, 1);
    v18 = (idWindow *)((int (__thiscall *)(idUserInterface *, int))this->guiActive->GetDesktop)(
                        this->guiActive,
                        0x100000);
    idWindow::SetFlag(v18, v20);
    ((void (__thiscall *)(idUserInterface *, const char *))this->guiActive->SetStateBool)(
      this->guiActive,
      "gui::cursor");
    this->guiActive->HandleNamedEvent(this->guiActive, "FinishedLoading");
  }
  soundSystem->SetActiveSoundWorld(soundSystem, 1);
}

// FUNC: public: void __thiscall idSessionLocal::RunGameTic(bool)
void __userpurge idSessionLocal::RunGameTic(idSessionLocal *this@<ecx>, int a2@<esi>, int isLastCatchupFrame)
{
  idFile *cmdDemoFile; // ecx
  bool v5; // zf
  int v6; // eax
  idGame_vtbl *v7; // edi
  int v8; // esi
  int v9; // eax
  int logIndex; // eax
  const char *v11; // eax
  int v12; // esi
  idDict *persistentPlayerInfo; // edi
  idDict *v14; // eax
  const char *v15; // ecx
  const char *v16; // eax
  const char *v17; // eax
  const char *v18; // eax
  const char *v19; // eax
  const char *v20; // eax
  const char *v21; // eax
  const char *v22; // eax
  idUserInterface *guiGameOver; // eax
  logCmd_t logCmd; // [esp+Ch] [ebp-D98h] BYREF
  usercmd_t cmd; // [esp+38h] [ebp-D6Ch] BYREF
  char v26[40]; // [esp+60h] [ebp-D44h] BYREF
  idCmdArgs args; // [esp+88h] [ebp-D1Ch] BYREF
  gameReturn_t ret; // [esp+98Ch] [ebp-418h] BYREF

  cmdDemoFile = this->cmdDemoFile;
  logCmd.consistencyHash = -1;
  if ( cmdDemoFile )
  {
    if ( cmdDemoFile->Read(cmdDemoFile, &logCmd, 44) )
    {
      qmemcpy(&cmd, &logCmd, sizeof(cmd));
      usercmd_t::ByteSwap(&cmd);
      logCmd.consistencyHash = LittleLong(logCmd.consistencyHash);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Command demo completed at logIndex %i\n",
        this->logIndex);
      fileSystem->CloseFile(fileSystem, this->cmdDemoFile);
      v5 = !this->aviCaptureMode;
      this->cmdDemoFile = 0;
      if ( !v5 )
      {
        idSessionLocal::EndAVICapture(this, a2);
        this->Shutdown(this);
      }
    }
  }
  if ( !this->cmdDemoFile )
  {
    qmemcpy(&cmd, usercmdGen->GetDirectUsercmd(usercmdGen, v26), sizeof(cmd));
    ++this->lastGameTic;
  }
  v6 = Sys_Milliseconds();
  v7 = game->__vftable;
  v8 = v6;
  v9 = (*(int (__thiscall **)(_DWORD, int, int))(**(_DWORD **)common.ip + 28))(
         *(_DWORD *)common.ip,
         -1,
         isLastCatchupFrame);
  ((void (__thiscall *)(idGame *, char *, int *, int))v7->RunFrame)(game, &ret.sessionCommand[4], &cmd.gameTime, v9);
  time_gameFrame += Sys_Milliseconds() - v8;
  if ( this->cmdDemoFile && ret.consistencyHash != logCmd.consistencyHash )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Consistency failure on logIndex %i\n",
      this->logIndex);
    this->Stop(this);
    return;
  }
  logIndex = this->logIndex;
  if ( logIndex < 216000 )
  {
    qmemcpy(&this->loggedUsercmds[logIndex], &cmd, 0x28u);
    this->loggedUsercmds[this->logIndex++].consistencyHash = ret.consistencyHash;
  }
  v5 = ret.sessionCommand[0] == 0;
  this->syncNextGameFrame = ret.syncNextGameFrame;
  if ( !v5 )
  {
    args.argc = 0;
    idCmdArgs::TokenizeString(&args, ret.sessionCommand, 0);
    v11 = args.argv[0];
    if ( args.argc <= 0 )
      v11 = &entityFilter;
    if ( !idStr::Icmp(v11, "map") )
    {
      v12 = 0;
      if ( this->numClients > 0 )
      {
        persistentPlayerInfo = this->mapSpawnData.persistentPlayerInfo;
        do
        {
          v14 = (idDict *)game->GetPersistentPlayerInfo(game, v12);
          idDict::operator=(persistentPlayerInfo, v14);
          ++v12;
          ++persistentPlayerInfo;
        }
        while ( v12 < this->numClients );
      }
      idDict::Delete(&this->mapSpawnData.serverInfo, "devmap");
      v15 = args.argv[2];
      if ( args.argc <= 2 )
        v15 = &entityFilter;
      v16 = args.argv[1];
      if ( args.argc <= 1 )
        v16 = &entityFilter;
LABEL_24:
      idSessionLocal::MoveToNewMap(this, (int)this, v16, v15);
      return;
    }
    v17 = args.argv[0];
    if ( args.argc <= 0 )
      v17 = &entityFilter;
    if ( !idStr::Icmp(v17, "devmap") )
    {
      idDict::Set(&this->mapSpawnData.serverInfo, "devmap", "1");
      v15 = args.argv[2];
      if ( args.argc <= 2 )
        v15 = &entityFilter;
      v16 = args.argv[1];
      if ( args.argc <= 1 )
        v16 = &entityFilter;
      goto LABEL_24;
    }
    v18 = args.argv[0];
    if ( args.argc <= 0 )
      v18 = &entityFilter;
    if ( !idStr::Icmp(v18, "died") )
    {
      idSessionLocal::UnloadMap(this);
      this->SetGUI(this, this->guiRestartMenu, 0);
      ((void (__thiscall *)(idUserInterface *, _DWORD, _DWORD))this->guiRestartMenu->SetCursor)(
        this->guiRestartMenu,
        0,
        0);
      return;
    }
    v19 = args.argv[0];
    if ( args.argc <= 0 )
      v19 = &entityFilter;
    if ( !idStr::Icmp(v19, "disconnect") )
    {
LABEL_53:
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_INSERT, "stoprecording ; disconnect");
      return;
    }
    v20 = args.argv[0];
    if ( args.argc <= 0 )
      v20 = &entityFilter;
    if ( !idStr::Icmp(v20, "endOfDemo") )
    {
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "endOfDemo");
      return;
    }
    v21 = args.argv[0];
    if ( args.argc <= 0 )
      v21 = &entityFilter;
    if ( !idStr::Icmp(v21, "objectiveFailed") )
    {
      this->objectiveFailed = 1;
      return;
    }
    v22 = args.argv[0];
    if ( args.argc <= 0 )
      v22 = &entityFilter;
    if ( !idStr::Icmp(v22, "endOfGame") )
    {
      guiGameOver = this->guiGameOver;
      if ( guiGameOver )
      {
        this->SetGUI(this, guiGameOver, 0);
        return;
      }
      goto LABEL_53;
    }
  }
}

// FUNC: public: void __thiscall idSessionLocal::StartNewGame(char const *,bool,char const *,bool)
void __userpurge idSessionLocal::StartNewGame(
        idSessionLocal *this@<ecx>,
        int a2@<ebp>,
        int a3@<edi>,
        const char *mapName,
        bool devmap,
        const char *entityFilter,
        bool clearUserNfo)
{
  idDict *v8; // eax
  idDict *v9; // eax
  idDict *v10; // eax

  if ( idAsyncNetwork::server.active )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Server running, use si_map / serverMapRestart\n");
  }
  else if ( idAsyncNetwork::client.active )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Client running, disconnect from server first\n");
  }
  else
  {
    if ( clearUserNfo )
    {
      idDict::Clear(this->mapSpawnData.userInfo);
      idDict::Clear(this->mapSpawnData.persistentPlayerInfo);
      v8 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 512);
      idDict::operator=(this->mapSpawnData.userInfo, v8);
    }
    idDict::Clear(&this->mapSpawnData.serverInfo);
    v9 = (idDict *)((int (__thiscall *)(idCVarSystem *, int, int))cvarSystem->MoveCVarsToDict)(cvarSystem, 1024, a3);
    idDict::operator=(&this->mapSpawnData.serverInfo, v9);
    idDict::Set(&this->mapSpawnData.serverInfo, "si_gameType", "singleplayer");
    if ( (_BYTE)entityFilter )
      idDict::Set(&this->mapSpawnData.serverInfo, "devmap", "1");
    idDict::Clear(&this->mapSpawnData.syncedCVars);
    v10 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 2048);
    idDict::operator=(&this->mapSpawnData.syncedCVars, v10);
    idSessionLocal::MoveToNewMap(this, a2, mapName, entityFilter);
    if ( cvarSystem->GetCVarBool(cvarSystem, "com_WriteSingleDeclFile") )
    {
      session->Frame(session);
      session->UpdateScreen(session, 1);
      declManager->WriteDeclFile(declManager);
    }
    if ( com_makingBuild.internalVar->integerValue )
    {
      if ( !com_Bundler.internalVar->integerValue )
      {
        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "reloadImages rebuild");
        cmdSystem->ExecuteCommandBuffer(cmdSystem);
      }
    }
  }
}

// FUNC: public: void __thiscall idSessionLocal::StartPlayingCmdDemo(char const *)
void __userpurge idSessionLocal::StartPlayingCmdDemo(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        const char *demoName)
{
  int v5; // eax
  char v6; // cl
  unsigned int v7; // kr00_4
  char v8; // cl
  int i; // eax
  char *v10; // edx
  idFile *v11; // eax
  idUserInterface *v12; // eax
  idFile *v13; // eax
  idFile *cmdDemoFile; // [esp+24h] [ebp-34h]
  char v15; // [esp+28h] [ebp-30h]
  idStr fullDemoName; // [esp+2Ch] [ebp-2Ch] BYREF
  int v17; // [esp+54h] [ebp-4h]

  this->Stop(this);
  fullDemoName.alloced = 20;
  fullDemoName.data = fullDemoName.baseBuffer;
  fullDemoName.baseBuffer[0] = 0;
  v5 = 0;
  do
  {
    v6 = aDemos[v5];
    fullDemoName.baseBuffer[v5++] = v6;
  }
  while ( v6 );
  fullDemoName.len = 6;
  v17 = 0;
  if ( demoName )
  {
    v7 = strlen(demoName);
    if ( (int)(v7 + 7) > fullDemoName.alloced )
      idStr::ReAllocate(&fullDemoName, v7 + 7, 1);
    v8 = *demoName;
    for ( i = 0; v8; v8 = demoName[i] )
    {
      v10 = &fullDemoName.data[i++];
      v10[fullDemoName.len] = v8;
    }
    fullDemoName.len = v7 + 6;
    fullDemoName.data[v7 + 6] = 0;
  }
  idStr::DefaultFileExtension(&fullDemoName, ".cdemo");
  v11 = fileSystem->OpenFileRead(fileSystem, fullDemoName.data, 1, 0);
  this->cmdDemoFile = v11;
  if ( v11 )
  {
    v12 = uiManager->FindGui(uiManager, "guis/loading/generic.gui", 1, 0, 1);
    cmdDemoFile = this->cmdDemoFile;
    this->guiLoading = v12;
    idSessionLocal::LoadCmdDemoFromFile(this, cmdDemoFile);
    idSessionLocal::ExecuteMapChange(this, a2, a3, (int)demoName, (int)this, 0, 0, v15);
    v13 = fileSystem->OpenFileRead(fileSystem, fullDemoName.data, 1, 0);
    this->cmdDemoFile = v13;
    idSessionLocal::LoadCmdDemoFromFile(this, v13);
    idSessionLocal::RunGameTic(this, (int)this, 1);
    soundSystem->SetActiveSoundWorld(soundSystem, 1);
    this->rw->PushMarkedDefs(this->rw);
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't open %s\n",
      fullDemoName.data);
  }
  v17 = -1;
  idStr::FreeData(&fullDemoName);
}

// FUNC: public: void __thiscall idSessionLocal::TimeCmdDemo(char const *)
void __userpurge idSessionLocal::TimeCmdDemo(idSessionLocal *this@<ecx>, int a2@<ebx>, const char *demoName)
{
  idSessionLocal_vtbl *v4; // edx
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  double v8; // st7
  int minuteStart; // [esp+20h] [ebp-8h]
  int startTime; // [esp+24h] [ebp-4h]
  int savedregs; // [esp+28h] [ebp+0h] BYREF

  idSessionLocal::StartPlayingCmdDemo(this, a2, (int)&savedregs, demoName);
  v4 = this->__vftable;
  v5 = 0;
  this->wipeHold = 0;
  this->wipeStopTic = 0;
  this->wipeStartTic = 1;
  v4->UpdateScreen(this, 1);
  v6 = Sys_Milliseconds();
  minuteStart = v6;
  while ( this->cmdDemoFile )
  {
    idSessionLocal::RunGameTic(this, (int)this, 1);
    this->rw->PushMarkedDefs(this->rw);
    ++v5;
    if ( v5 / 3600 != (v5 - 1) / 3600 )
    {
      v7 = Sys_Milliseconds();
      v8 = (double)(v7 - minuteStart);
      minuteStart = v7;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "minute %i took %3.1f seconds\n",
        v5 / 3600,
        v8 * 0.001);
      this->UpdateScreen(this, 1);
    }
  }
  startTime = Sys_Milliseconds() - v6;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%i seconds of game, replayed in %5.1f seconds\n",
    v5 / 60,
    (double)startTime * 0.001);
}

// FUNC: public: virtual void __thiscall idSessionLocal::Frame(void)
void __usercall idSessionLocal::Frame(idSessionLocal *this@<ecx>, int a2@<ebp>)
{
  idSoundSystem_vtbl *v3; // edi
  int v4; // eax
  char *v5; // eax
  int v6; // ecx
  double v7; // st7
  int i; // ebp
  char *v9; // eax
  double aviDemoFrameCount; // st7
  int v11; // eax
  int integerValue; // eax
  int latchedTicNumber; // edi
  int lastDemoTic; // edi
  int v15; // ebp
  bool v16; // cc
  idSessionLocal_vtbl *v17; // edx
  int v18; // edx
  idDict *v19; // eax
  idDict *v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // eax
  int v24; // et2
  int v25; // eax
  int v26; // ebp
  int j; // edi
  char *data; // [esp+0h] [ebp-78h]
  int aviTicStart; // [esp+4h] [ebp-74h]
  int v30; // [esp+8h] [ebp-70h]
  int v31; // [esp+1Ch] [ebp-5Ch]
  int c; // [esp+20h] [ebp-58h]
  int ca; // [esp+20h] [ebp-58h]
  idStr name; // [esp+24h] [ebp-54h] BYREF
  int v35[10]; // [esp+44h] [ebp-34h] BYREF
  int v36; // [esp+74h] [ebp-4h]

  if ( !com_asyncSound.internalVar->integerValue )
  {
    v3 = soundSystem->__vftable;
    v4 = Sys_Milliseconds();
    v3->AsyncUpdate(soundSystem, v4);
  }
  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 64))(common.type)
    && (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 6) )
  {
    return;
  }
  if ( console->Active(console)
    || (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 64))(common.type) )
  {
    sys->GrabMouseCursor(sys, 0);
  }
  else
  {
    sys->GrabMouseCursor(sys, 1);
  }
  v30 = a2;
  if ( this->aviCaptureMode )
  {
    name.len = 0;
    name.alloced = 20;
    name.data = name.baseBuffer;
    name.baseBuffer[0] = 0;
    aviTicStart = this->aviTicStart;
    data = this->aviDemoShortName.data;
    v36 = 0;
    v5 = va("demos/%s/%s_%05i.tga", data, data, aviTicStart);
    idStr::operator=(&name, v5);
    v31 = (*(int (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 40))(common.type, a2);
    v6 = this->aviTicStart + 1;
    name.len = this->aviTicStart;
    v7 = 30.0 / (1000.0 / (double)v31 / (double)c) + this->aviDemoFrameCount;
    this->aviDemoFrameCount = v7;
    ca = (int)v7;
    if ( v6 != (int)v7 )
    {
      name.len = (int)(v7 - (double)name.len);
      for ( i = name.len; i; --i )
      {
        renderSystem->TakeScreenshot(
          renderSystem,
          idSessionLocal::com_aviDemoWidth.internalVar->integerValue,
          idSessionLocal::com_aviDemoHeight.internalVar->integerValue,
          (const char *)name.alloced,
          idSessionLocal::com_aviDemoSamples.internalVar->integerValue,
          0,
          "fs_savepath");
        v9 = va("demos/%s/%s_%05i.tga", this->aviDemoShortName.data, this->aviDemoShortName.data, ++this->aviTicStart);
        idStr::operator=((idStr *)&name.data, v9);
      }
    }
    aviDemoFrameCount = this->aviDemoFrameCount;
    v11 = (unsigned __int16)v31;
    BYTE1(v11) = BYTE1(v31) | 0xC;
    name.len = v11;
    this->aviTicStart = (int)aviDemoFrameCount;
    console->ClearNotifyLines(console);
    ((void (__thiscall *)(idRenderSystem *, int, int, _DWORD, int, _DWORD, const char *, int))renderSystem->TakeScreenshot)(
      renderSystem,
      idSessionLocal::com_aviDemoWidth.internalVar->integerValue,
      idSessionLocal::com_aviDemoHeight.internalVar->integerValue,
      *(_DWORD *)&name.baseBuffer[16],
      idSessionLocal::com_aviDemoSamples.internalVar->integerValue,
      0,
      "fs_savepath",
      ca);
    v36 = -1;
    idStr::FreeData(&name);
  }
  if ( this->latchedTicNumber > com_ticNumber )
    this->latchedTicNumber = com_ticNumber;
  integerValue = idSessionLocal::com_minTics.internalVar->integerValue;
  latchedTicNumber = this->latchedTicNumber + 1;
  if ( integerValue > 1 )
    latchedTicNumber = integerValue + this->lastGameTic;
  if ( this->readDemo )
  {
    if ( this->timeDemo || this->numDemoFrames == 1 )
    {
      latchedTicNumber = this->latchedTicNumber;
      goto LABEL_26;
    }
    lastDemoTic = this->lastDemoTic;
  }
  else
  {
    if ( !this->writeDemo )
      goto LABEL_26;
    lastDemoTic = this->lastGameTic;
  }
  latchedTicNumber = lastDemoTic + 2;
LABEL_26:
  if ( idSessionLocal::com_fixedTic.internalVar->integerValue )
    latchedTicNumber = this->latchedTicNumber;
  v15 = Sys_Milliseconds();
  v16 = com_ticNumber < latchedTicNumber;
  for ( this->latchedTicNumber = com_ticNumber; v16; this->latchedTicNumber = com_ticNumber )
  {
    Sys_Sleep(1);
    v16 = com_ticNumber < latchedTicNumber;
  }
  time_waiting = Sys_Milliseconds() - v15;
  if ( this->authEmitTimeout && Sys_Milliseconds() > this->authEmitTimeout )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "no reply from auth\n");
    if ( this->authWaitBox )
    {
      this->StopBox(this);
      this->authWaitBox = 0;
    }
    if ( this->cdkey_state == CDKEY_CHECKING )
      this->cdkey_state = CDKEY_OK;
    if ( this->authMsg.alloced < 1 )
      idStr::ReAllocate(&this->authMsg, 1, 1);
    *this->authMsg.data = 0;
    this->authMsg.len = 0;
    v17 = this->__vftable;
    this->authEmitTimeout = 0;
    v17->SetCDKeyGuiVars(this);
  }
  this->GuiFrameEvents(this);
  if ( this->readDemo )
  {
    idSessionLocal::AdvanceRenderDemo(this, 0);
    return;
  }
  if ( !this->mapSpawned || this->guiActive )
    usercmdGen->GetDirectUsercmd(usercmdGen, (usercmd_t *)v35);
  if ( !this->mapSpawned || this->pauseAfterMapChange )
  {
    if ( game )
      game->MenuFrame(game);
  }
  else
  {
    if ( this->guiActive )
    {
      this->lastGameTic = this->latchedTicNumber;
      return;
    }
    if ( !idAsyncNetwork::IsActive() )
    {
      if ( (((int (__thiscall *)(idCVarSystem *, int))cvarSystem->GetModifiedFlags)(cvarSystem, v30) & 0x200) != 0 )
      {
        v19 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 512);
        v20 = idDict::operator=(this->mapSpawnData.userInfo, v19);
        LOBYTE(v20) = idAsyncNetwork::client.active;
        game->SetUserInfo(game, 0, this->mapSpawnData.userInfo, (bool)v20);
        cvarSystem->ClearModifiedFlags(cvarSystem, 512);
      }
      v21 = this->latchedTicNumber - this->lastGameTic;
      if ( this->timeHitch )
      {
        v22 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
        v24 = this->timeHitch % v22;
        v23 = this->timeHitch / v22;
        v18 = v24;
        this->timeHitch = 0;
        this->lastGameTic += v23;
        v21 -= v23;
      }
      if ( v21 > 10 )
      {
        v18 = this->latchedTicNumber - 10;
        this->lastGameTic = v18;
      }
      if ( this->writeDemo )
      {
        if ( v21 < 2 )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "idSessionLocal::Frame: numCmdsToRun < fixedTic");
        v18 = this->latchedTicNumber - 2;
        goto LABEL_63;
      }
      v25 = idSessionLocal::com_fixedTic.internalVar->integerValue;
      if ( v25 <= 0 )
      {
        if ( this->aviCaptureMode )
        {
          v18 = this->latchedTicNumber - idSessionLocal::com_aviDemoTics.internalVar->integerValue;
LABEL_63:
          this->lastGameTic = v18;
        }
      }
      else
      {
        this->lastGameTic = this->latchedTicNumber - v25;
      }
      if ( idSessionLocal::com_syncGameFrame.internalVar->integerValue )
        this->syncNextGameFrame = 1;
      if ( this->syncNextGameFrame )
      {
        v18 = this->latchedTicNumber - 1;
        this->lastGameTic = v18;
        this->syncNextGameFrame = 0;
      }
      if ( idSessionLocal::com_showTics.internalVar->integerValue )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%i ",
          this->latchedTicNumber - this->lastGameTic);
      v26 = this->latchedTicNumber - this->lastGameTic;
      for ( j = 0; j < v26; ++j )
      {
        LOBYTE(v18) = j == v26 - 1;
        (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 52))(common.type, v18);
        idSessionLocal::RunGameTic(this, 1);
        if ( !this->mapSpawned )
          break;
        if ( this->syncNextGameFrame )
          break;
      }
      session->rw->PushMarkedDefs(session->rw);
      (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 52))(common.type, 1);
      com_debugHudActive = game->IsDebugHudActive(game);
    }
  }
}

// FUNC: Session_Map_f
void __cdecl Session_Map_f(const idCmdArgs *args)
{
  bool v2; // cc
  const char *v3; // eax
  const char *v4; // eax
  const char *v5; // eax
  idStr *v6; // eax
  idFileSystem_vtbl *v7; // edx
  const char *v8; // eax
  char *data; // [esp+1Ch] [ebp-84h]
  char v10; // [esp+30h] [ebp-70h]
  idStr string; // [esp+34h] [ebp-6Ch] BYREF
  idStr map; // [esp+54h] [ebp-4Ch] BYREF
  idStr result; // [esp+74h] [ebp-2Ch] BYREF
  int v14; // [esp+9Ch] [ebp-4h]
  char argsa; // [esp+A4h] [ebp+4h]

  v10 = 0;
  map.len = 0;
  map.alloced = 20;
  map.data = map.baseBuffer;
  map.baseBuffer[0] = 0;
  v14 = 0;
  string.len = 0;
  string.alloced = 20;
  string.data = string.baseBuffer;
  string.baseBuffer[0] = 0;
  v2 = args->argc <= 1;
  LOBYTE(v14) = 1;
  if ( v2 )
    v3 = &entityFilter;
  else
    v3 = args->argv[1];
  idStr::operator=(&map, v3);
  if ( map.len )
  {
    idStr::StripFileExtension(&map);
    v4 = va("maps/%s.map", map.data);
    idStr::operator=(&string, v4);
    if ( args->argc <= 2 )
      v5 = &entityFilter;
    else
      v5 = args->argv[2];
    cvarSystem->SetCVarString(cvarSystem, "si_entityFilter", v5, 0);
    fileSystem->SetAssetLogName(fileSystem, string.data);
    if ( fileSystem->ReadFile(fileSystem, string.data, 0, 0) != -1
      || (v6 = operator+(&result, &string, "c"),
          v7 = fileSystem->__vftable,
          data = v6->data,
          LOBYTE(v14) = 2,
          v10 = 1,
          argsa = 1,
          v7->ReadFile(fileSystem, data, 0, 0) != -1) )
    {
      argsa = 0;
    }
    v14 = 1;
    if ( (v10 & 1) != 0 )
      idStr::FreeData(&result);
    if ( argsa )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Can't find map %s\n",
        string.data);
    }
    else
    {
      cvarSystem->SetCVarBool(cvarSystem, "developer", 0, 0);
      if ( args->argc <= 2 )
        v8 = &entityFilter;
      else
        v8 = args->argv[2];
      idSessionLocal::StartNewGame(&sessLocal, map.data, 0, v8, 1);
    }
  }
  LOBYTE(v14) = 0;
  idStr::FreeData(&string);
  v14 = -1;
  idStr::FreeData(&map);
}

// FUNC: Session_DevMap_f
void __cdecl Session_DevMap_f(const idCmdArgs *args)
{
  bool v2; // cc
  const char *v3; // eax
  const char *v4; // eax
  idStr *v5; // eax
  idFileSystem_vtbl *v6; // edx
  const char *v7; // eax
  char *data; // [esp+18h] [ebp-84h]
  char v9; // [esp+2Ch] [ebp-70h]
  idStr map; // [esp+30h] [ebp-6Ch] BYREF
  idStr string; // [esp+50h] [ebp-4Ch] BYREF
  idStr result; // [esp+70h] [ebp-2Ch] BYREF
  int v13; // [esp+98h] [ebp-4h]
  char argsa; // [esp+A0h] [ebp+4h]

  v9 = 0;
  map.len = 0;
  map.alloced = 20;
  map.data = map.baseBuffer;
  map.baseBuffer[0] = 0;
  v13 = 0;
  string.len = 0;
  string.alloced = 20;
  string.data = string.baseBuffer;
  string.baseBuffer[0] = 0;
  v2 = args->argc <= 1;
  LOBYTE(v13) = 1;
  if ( v2 )
    v3 = &entityFilter;
  else
    v3 = args->argv[1];
  idStr::operator=(&map, v3);
  if ( map.len )
  {
    idStr::StripFileExtension(&map);
    v4 = va("maps/%s.map", map.data);
    idStr::operator=(&string, v4);
    if ( fileSystem->ReadFile(fileSystem, string.data, 0, 0) != -1
      || (v5 = operator+(&result, &string, "c"),
          v6 = fileSystem->__vftable,
          data = v5->data,
          LOBYTE(v13) = 2,
          v9 = 1,
          argsa = 1,
          v6->ReadFile(fileSystem, data, 0, 0) != -1) )
    {
      argsa = 0;
    }
    v13 = 1;
    if ( (v9 & 1) != 0 )
      idStr::FreeData(&result);
    if ( argsa )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Can't find map %s\n",
        string.data);
    }
    else
    {
      cvarSystem->SetCVarBool(cvarSystem, "developer", 1, 0);
      cvarSystem->SetCVarBool(cvarSystem, "con_noPrint", 0, 0);
      if ( args->argc <= 2 )
        v7 = &entityFilter;
      else
        v7 = args->argv[2];
      idSessionLocal::StartNewGame(&sessLocal, map.data, 1, v7, 1);
    }
  }
  LOBYTE(v13) = 0;
  idStr::FreeData(&string);
  v13 = -1;
  idStr::FreeData(&map);
}

// FUNC: Session_PlayCmdDemo_f
void __cdecl Session_PlayCmdDemo_f(const idCmdArgs *args)
{
  if ( args->argc <= 1 )
    idSessionLocal::StartPlayingCmdDemo(&sessLocal, &entityFilter);
  else
    idSessionLocal::StartPlayingCmdDemo(&sessLocal, args->argv[1]);
}

// FUNC: Session_TimeCmdDemo_f
void __cdecl Session_TimeCmdDemo_f(const idCmdArgs *args)
{
  if ( args->argc <= 1 )
    idSessionLocal::TimeCmdDemo(&sessLocal, &entityFilter);
  else
    idSessionLocal::TimeCmdDemo(&sessLocal, args->argv[1]);
}

// FUNC: Session_AVICmdDemo_f
void __cdecl Session_AVICmdDemo_f(const idCmdArgs *args)
{
  const char *v1; // esi

  if ( args->argc <= 1 )
    v1 = &entityFilter;
  else
    v1 = args->argv[1];
  idSessionLocal::StartPlayingCmdDemo(&sessLocal, v1);
  idSessionLocal::BeginAVICapture(&sessLocal, v1);
}

// FUNC: public: virtual void __thiscall idSessionLocal::Init(void)
void __thiscall idSessionLocal::Init(idSessionLocal *this)
{
  const char *v2; // eax
  idRenderWorld *v3; // eax
  idListGUI *v4; // eax
  idUserInterface *guiMainMenu; // ecx
  const char *v6; // eax
  const char *v7; // eax
  idUserInterface *v8; // eax
  idListGUI *guiMainMenu_MapList; // ecx
  idListGUI *v10; // eax
  idUserInterface *guiDedicated; // ecx
  idListGUI *v12; // eax
  idUserInterface *v13; // ecx
  idListGUI *v14; // eax
  idUserInterface *v15; // ecx
  idListGUI *v16; // eax
  idUserInterface *v17; // ecx
  idListGUI *v18; // eax
  idUserInterface *v19; // ecx
  idListGUI *v20; // eax
  idUserInterface *v21; // ecx
  idListGUI *v22; // eax
  idUserInterface *v23; // ecx
  idSessionLocal_vtbl *v24; // eax
  const idCmdArgs *v25; // [esp+0h] [ebp-8h]
  int v26; // [esp+0h] [ebp-8h]

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "----------- Initializing Session ------------\n");
  SpawnStub(v25);
  ((void (__thiscall *)(idCmdSystem *, const char *, void (__cdecl *)(const idCmdArgs *), int, const char *, _DWORD, int))cmdSystem->AddCommand)(
    cmdSystem,
    "SaveGameRefreshList",
    SaveGameRefreshList_f,
    2,
    "refresh the gui's save list",
    0,
    v26);
  cmdSystem->AddCommand(cmdSystem, "writePrecache", Sess_WritePrecache_f, 3, "writes precache commands", 0);
  cmdSystem->AddCommand(cmdSystem, "map", Session_Map_f, 2, "loads a map", idCmdSystem::ArgCompletion_MapName);
  cmdSystem->AddCommand(
    cmdSystem,
    "devmap",
    Session_DevMap_f,
    2,
    "loads a map in developer mode",
    idCmdSystem::ArgCompletion_MapName);
  cmdSystem->AddCommand(cmdSystem, "testmap", Session_TestMap_f, 2, "tests a map", idCmdSystem::ArgCompletion_MapName);
  cmdSystem->AddCommand(cmdSystem, "writeCmdDemo", Session_WriteCmdDemo_f, 2, "writes a command demo", 0);
  cmdSystem->AddCommand(cmdSystem, "playCmdDemo", Session_PlayCmdDemo_f, 2, "plays back a command demo", 0);
  cmdSystem->AddCommand(cmdSystem, "timeCmdDemo", Session_TimeCmdDemo_f, 2, "times a command demo", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "exitCmdDemo",
    (void (__cdecl *)(const idCmdArgs *))Session_ExitCmdDemo_f,
    2,
    "exits a command demo",
    0);
  cmdSystem->AddCommand(cmdSystem, "aviCmdDemo", Session_AVICmdDemo_f, 2, "writes AVIs for a command demo", 0);
  cmdSystem->AddCommand(cmdSystem, "aviGame", Session_AVIGame_f, 2, "writes AVIs for the current game", 0);
  cmdSystem->AddCommand(cmdSystem, "recordDemo", Session_RecordDemo_f, 2, "records a demo", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "stopRecording",
    (void (__cdecl *)(const idCmdArgs *))Session_StopRecordingDemo_f,
    2,
    "stops demo recording",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "playDemo",
    Session_PlayDemo_f,
    2,
    "plays back a demo",
    idCmdSystem::ArgCompletion_DemoName);
  cmdSystem->AddCommand(
    cmdSystem,
    "timeDemo",
    Session_TimeDemo_f,
    2,
    "times a demo",
    idCmdSystem::ArgCompletion_DemoName);
  cmdSystem->AddCommand(
    cmdSystem,
    "timeDemoQuit",
    Session_TimeDemoQuit_f,
    2,
    "times a demo and quits",
    idCmdSystem::ArgCompletion_DemoName);
  cmdSystem->AddCommand(
    cmdSystem,
    "aviDemo",
    Session_AVIDemo_f,
    2,
    "writes AVIs for a demo",
    idCmdSystem::ArgCompletion_DemoName);
  cmdSystem->AddCommand(
    cmdSystem,
    "compressDemo",
    Session_CompressDemo_f,
    2,
    "compresses a demo file",
    idCmdSystem::ArgCompletion_DemoName);
  cmdSystem->AddCommand(
    cmdSystem,
    "disconnect",
    (void (__cdecl *)(const idCmdArgs *))Session_Disconnect_f,
    2,
    "disconnects from a game",
    0);
  cmdSystem->AddCommand(cmdSystem, "demoShot", Session_DemoShot_f, 2, "writes a screenshot for a demo", 0);
  cmdSystem->AddCommand(cmdSystem, "testGUI", Session_TestGUI_f, 2, "tests a gui", idCmdSystem::ArgCompletion_GuiName);
  cmdSystem->AddCommand(cmdSystem, "saveGame", SaveGame_f, 3, "saves a game", 0);
  cmdSystem->AddCommand(cmdSystem, "loadGame", LoadGame_f, 3, "loads a game", idCmdSystem::ArgCompletion_SaveGame);
  v2 = (const char *)((int (__thiscall *)(idCVarSystem *))cvarSystem->GetCVarString)(cvarSystem);
  if ( !idStr::Icmp(v2, "fs_game") )
    cmdSystem->AddCommand(cmdSystem, "dedicatedGUI", DedicatedGUI_f, 2, "Show the dedicated server GUI for Xenon", 0);
  ((void (__thiscall *)(idCmdSystem *, const char *, void (__cdecl *)(const idCmdArgs *), int, const char *, _DWORD, const char *))cmdSystem->AddCommand)(
    cmdSystem,
    "viewNotes",
    ViewNotes_f,
    2,
    "notes about the current map",
    0,
    "q4basexenon");
  cmdSystem->AddCommand(cmdSystem, "buildNotes", BuildNotes_f, 2, "build notes about the current map", 0);
  cmdSystem->AddCommand(cmdSystem, "QANotes", QANotes_f, 2, "qa notes about the current map", 0);
  cmdSystem->AddCommand(cmdSystem, "editCVars", EditCVars_f, 2, "edit cvars", 0);
  cmdSystem->AddCommand(cmdSystem, "spawnGUI", SpawnGUI_f, 2, "spawn gui", 0);
  cmdSystem->AddCommand(cmdSystem, "tabComplete", TabComplete_f, 2, "tab completes it's argument", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "rescanSI",
    Session_RescanSI_f,
    2,
    "internal - rescan serverinfo cvars and tell game",
    0);
  cmdSystem->AddCommand(cmdSystem, "promptKey", Session_PromptKey_f, 2, "prompt and sets the CD Key", 0);
  cmdSystem->AddCommand(cmdSystem, "hitch", Session_Hitch_f, 3, "hitches the game", 0);
  v3 = renderSystem->AllocRenderWorld(renderSystem);
  this->rw = v3;
  soundSystem->SetRenderWorld(soundSystem, v3);
  bse->Init(bse);
  this->guiMainMenu = uiManager->FindGui(uiManager, "guis/mainmenu.gui", 1, 0, 1);
  v4 = uiManager->AllocListGUI(uiManager);
  guiMainMenu = this->guiMainMenu;
  this->guiMainMenu_MapList = v4;
  v4->Config(v4, guiMainMenu, "mapList");
  rvServerScanGUI::SetupServerScanGUI(&this->serverScanGUI, this->guiMainMenu, "serverlist", "friendslist");
  this->guiRestartMenu = uiManager->FindGui(uiManager, "guis/restart.gui", 1, 0, 1);
  this->guiGameOver = uiManager->FindGui(uiManager, "guis/gameover.gui", 1, 0, 1);
  this->guiMsg = uiManager->FindGui(uiManager, "guis/msg.gui", 1, 0, 1);
  v6 = (const char *)((int (__thiscall *)(idCVarSystem *))cvarSystem->GetCVarString)(cvarSystem);
  if ( !idStr::Icmp(v6, "fs_game") )
    this->LoadUbermessage(this);
  v7 = cvarSystem->GetCVarString(cvarSystem, "fs_game");
  if ( !idStr::Icmp(v7, "q4basexenon") )
  {
    this->guiXboxInGame = uiManager->FindGui(uiManager, "guis/mainmenu.gui", 1, 0, 1);
    v8 = uiManager->FindGui(uiManager, "guis/dedserveradmin.gui", 1, 0, 1);
    guiMainMenu_MapList = this->guiMainMenu_MapList;
    this->guiDedicated = v8;
    guiMainMenu_MapList->Config(guiMainMenu_MapList, v8, "mapList");
    v10 = uiManager->AllocListGUI(uiManager);
    guiDedicated = this->guiDedicated;
    this->guiDedicated_PlayerList = v10;
    v10->Config(v10, guiDedicated, "playerList");
    v12 = uiManager->AllocListGUI(uiManager);
    v13 = this->guiMainMenu;
    this->guiAvailableMapList = v12;
    v12->Config(v12, v13, "availmaplist");
    v14 = uiManager->AllocListGUI(uiManager);
    v15 = this->guiMainMenu;
    this->guiSysLinkAvailableMapList = v14;
    v14->Config(v14, v15, "syslinkavailmaplist");
    v16 = uiManager->AllocListGUI(uiManager);
    v17 = this->guiMainMenu;
    this->guiCycleMapList = v16;
    v16->Config(v16, v17, "mapcyclelist");
    v18 = uiManager->AllocListGUI(uiManager);
    v19 = this->guiMainMenu;
    this->guiSysLinkCycleMapList = v18;
    v18->Config(v18, v19, "syslinkmapcyclelist");
    v20 = uiManager->AllocListGUI(uiManager);
    v21 = this->guiMainMenu;
    this->guiQuickMatch = v20;
    v20->Config(v20, v21, "quickmatchserverlist");
    v22 = uiManager->AllocListGUI(uiManager);
    v23 = this->guiMainMenu;
    this->guiSaveGameList = v22;
    v22->Config(v22, v23, "loadGame");
    this->lastGuiSaveGameListSelection = -1;
  }
  this->guiTakeNotes = uiManager->FindGui(uiManager, "guis/takeNotes2.gui", 1, 0, 1);
  this->guiBuildNotes = uiManager->FindGui(uiManager, "guis/takeNotes.gui", 1, 0, 1);
  this->guiQANotes = uiManager->FindGui(uiManager, "guis/takeNotesQA.gui", 1, 0, 1);
  this->guiEditCVars = uiManager->FindGui(uiManager, "guis/editcvars.gui", 1, 0, 1);
  this->guiSpawn = uiManager->FindGui(uiManager, "guis/spawn.gui", 1, 0, 1);
  this->guiIntro = uiManager->FindGui(uiManager, "guis/intro.gui", 1, 0, 1);
  this->whiteMaterial = declManager->FindMaterial(declManager, "_white", 1);
  v24 = this->__vftable;
  this->guiInGame = 0;
  this->guiTest = 0;
  this->guiActive = 0;
  this->guiHandle = 0;
  v24->ReadCDKey(this);
  MapManager::CreateDefaultMapList();
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "session initialized\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
}
