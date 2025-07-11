
// FUNC: private: void __thiscall idAsyncClient::Clear(void)
void __thiscall idAsyncClient::Clear(idAsyncClient *this)
{
  int v1; // eax

  this->lastConnectTime = -9999;
  this->lastEmptyTime = -9999;
  this->lastPacketTime = -9999;
  this->lastSnapshotTime = -9999;
  v1 = 0;
  this->active = 0;
  this->realTime = 0;
  this->clientTime = 0;
  this->clientId = 0;
  this->clientDataChecksum = 0;
  this->clientNum = 0;
  this->clientState = CS_DISCONNECTED;
  this->clientPrediction = 0;
  this->clientPredictTime = 0;
  this->serverId = 0;
  this->serverChallenge = 0;
  this->serverMessageSequence = 0;
  this->snapshotGameFrame = 0;
  this->snapshotGameTime = 0;
  this->snapshotSequence = 0;
  this->gameInitId = -1;
  this->gameFrame = 0;
  this->gameTimeResidual = 0;
  this->gameTime = 0;
  memset(this->userCmds, 0, sizeof(this->userCmds));
  this->backgroundDownload.completed = 1;
  this->lastRconTime = 0;
  this->showUpdateMessage = 0;
  this->lastFrameDelta = 0;
  this->dlRequest = -1;
  this->dlCount = -1;
  memset(this->dlChecksums, 0, sizeof(this->dlChecksums));
  this->currentDlSize = 0;
  this->totalDlSize = 0;
  this->challengesSent = 0;
  memset(this->guids, 0, sizeof(this->guids));
  do
  {
    sessLocal.mapSpawnData.mapLastUIRequestTime[v1] = 0;
    sessLocal.mapSpawnData.mapLastUIInitialRequest[v1++] = 1;
  }
  while ( v1 < 32 );
  this->demoScaleTimeOffset = 0;
}

// FUNC: public: bool __thiscall idAsyncClient::InitPort(void)
char __thiscall idAsyncClient::InitPort(idAsyncClient *this)
{
  if ( this->clientPort.port || idPort::InitForPort(&this->clientPort, -1) )
  {
    this->guiNetMenu = uiManager->FindGui(uiManager, "guis/netmenu.gui", 1, 0, 1);
    return 1;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't open client network port.\n");
    return 0;
  }
}

// FUNC: public: void __thiscall idAsyncClient::ClosePort(void)
void __thiscall idAsyncClient::ClosePort(idAsyncClient *this)
{
  idPort::Close(&this->clientPort);
}

// FUNC: private: void __thiscall idAsyncClient::ClearPendingPackets(void)
void __thiscall idAsyncClient::ClearPendingPackets(idAsyncClient *this)
{
  idPort *p_clientPort; // esi
  int size; // [esp+4h] [ebp-4010h] BYREF
  netadr_t from; // [esp+8h] [ebp-400Ch] BYREF
  char data[16384]; // [esp+14h] [ebp-4000h] BYREF

  p_clientPort = &this->clientPort;
  while ( idPort::GetPacket(p_clientPort, &from, data, &size, 0x4000) )
    ;
}

// FUNC: private: char const * __thiscall idAsyncClient::HandleGuiCommandInternal(char const *)
const char *__thiscall idAsyncClient::HandleGuiCommandInternal(idAsyncClient *this, const char *cmd)
{
  if ( idStr::Cmp(cmd, "abort") && idStr::Cmp(cmd, "pure_abort") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 140))(
      common.type,
      "idAsyncClient::HandleGuiCommand: unknown cmd %s",
      cmd);
    return 0;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "connection aborted\n");
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
    return &entityFilter;
  }
}

// FUNC: private: static char const * __cdecl idAsyncClient::HandleGuiCommand(char const *)
const char *__cdecl idAsyncClient::HandleGuiCommand(const char *cmd)
{
  return idAsyncClient::HandleGuiCommandInternal(&idAsyncNetwork::client, cmd);
}

// FUNC: public: void __thiscall idAsyncClient::ConnectToServer(struct netadr_t)
void __thiscall idAsyncClient::ConnectToServer(idAsyncClient *this, netadr_t adr)
{
  const char *v3; // eax
  const char *v4; // eax
  char *v5; // eax
  int v6; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+20h] [ebp-4h]

  session->Stop(session);
  if ( idAsyncClient::InitPort(this) )
  {
    if ( cvarSystem->GetCVarBool(cvarSystem, "net_serverDedicated") )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "Can't connect to a server as dedicated\n");
    }
    else
    {
      idAsyncClient::ClearPendingPackets(this);
      this->serverAddress = adr;
      idAsyncClient::Clear(this);
      cvarSystem->SetCVarBool(cvarSystem, "ui_chat", 0, 0);
      this->clientId = Sys_Milliseconds() & 0x7FFF;
      this->clientDataChecksum = declManager->GetChecksum(declManager);
      this->clientState = CS_CHALLENGING;
      this->active = 1;
      this->guiNetMenu = uiManager->FindGui(uiManager, "guis/netmenu.gui", 1, 0, 1);
      v3 = Sys_NetAdrToString(adr);
      v4 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, const char *))(*(_DWORD *)common.type
                                                                                              + 168))(
                           common.type,
                           "#str_106749",
                           -1,
                           v3);
      v5 = va(v4);
      (*(void (__thiscall **)(idUserInterface *, const char *, char *, int, int))(v8 + 56))(
        this->guiNetMenu,
        "status",
        v5,
        v6,
        v7);
      session->SetGUI(session, this->guiNetMenu, idAsyncClient::HandleGuiCommand);
      (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 52))(common.type, 1);
    }
  }
}

// FUNC: public: void __thiscall idAsyncClient::Reconnect(void)
void __thiscall idAsyncClient::Reconnect(idAsyncClient *this)
{
  idAsyncClient::ConnectToServer(this, this->serverAddress);
}

// FUNC: public: void __thiscall idAsyncClient::ConnectToServer(char const *)
void __thiscall idAsyncClient::ConnectToServer(idAsyncClient *this, const char *address)
{
  int v3; // esi
  int v4; // esi
  const char *v5; // eax
  idSession_vtbl *v6; // edi
  int v7; // eax
  const char *v8; // eax
  char *v9; // eax
  idSession_vtbl *v10; // esi
  int v11; // eax
  const char *v12; // eax
  char *v13; // eax
  int v14; // [esp-Ch] [ebp-24h]
  int v15; // [esp-Ch] [ebp-24h]
  int v16; // [esp-8h] [ebp-20h]
  int v17; // [esp-8h] [ebp-20h]
  int v18; // [esp-4h] [ebp-1Ch]
  int v19; // [esp-4h] [ebp-1Ch]
  netadr_t adr; // [esp+Ch] [ebp-Ch] BYREF

  if ( idStr::IsNumeric(address) )
  {
    v3 = atoi(address);
    if ( v3 < 0 || v3 >= rvServerScan::GetNumServers(&this->serverList) )
    {
      v6 = session->__vftable;
      v7 = (*(int (__thiscall **)(netadrtype_t, const char *, int, _DWORD, _DWORD, _DWORD, int))(*(_DWORD *)common.type
                                                                                               + 168))(
             common.type,
             "#str_106735",
             -1,
             0,
             0,
             0,
             1);
      v8 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int, int))(*(_DWORD *)common.type + 168))(
                           common.type,
                           "#str_106733",
                           -1,
                           v3,
                           v7);
      v9 = va(v8);
      ((void (__thiscall *)(idSession *, _DWORD, char *, int, int, int))v6->MessageBoxA)(session, 0, v9, v14, v16, v18);
      return;
    }
    adr = rvServerScanGUI::GetServer(&sessLocal.serverScanGUI, v3)->adr;
  }
  else if ( !Sys_StringToNetAdr(address, &adr, 1) )
  {
    v10 = session->__vftable;
    v11 = (*(int (__thiscall **)(netadrtype_t, const char *, int, _DWORD, _DWORD, _DWORD, int))(*(_DWORD *)common.type
                                                                                              + 168))(
            common.type,
            "#str_106735",
            -1,
            0,
            0,
            0,
            1);
    v12 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, const char *, int))(*(_DWORD *)common.type
                                                                                                  + 168))(
                          common.type,
                          "#str_106734",
                          -1,
                          address,
                          v11);
    v13 = va(v12);
    ((void (__thiscall *)(idSession *, _DWORD, char *, int, int, int))v10->MessageBoxA)(session, 0, v13, v15, v17, v19);
    return;
  }
  if ( !adr.port )
    adr.port = 28004;
  v4 = *(_DWORD *)common.type;
  v5 = Sys_NetAdrToString(adr);
  (*(void (**)(netadrtype_t, const char *, ...))(v4 + 124))(common.type, "\"%s\" resolved to %s\n", address, v5);
  idAsyncClient::ConnectToServer(this, adr);
}

// FUNC: public: int __thiscall idAsyncClient::GetPrediction(void)const
int __thiscall idAsyncClient::GetPrediction(idAsyncClient *this)
{
  if ( this->clientState >= CS_CONNECTED )
    return this->clientPrediction;
  else
    return -1;
}

// FUNC: public: int __thiscall idAsyncClient::GetTimeSinceLastPacket(void)const
int __thiscall idAsyncClient::GetTimeSinceLastPacket(idAsyncClient *this)
{
  if ( this->clientState >= CS_CONNECTED )
    return this->clientTime - this->lastPacketTime;
  else
    return -1;
}

// FUNC: public: float __thiscall idAsyncClient::GetIncomingPacketLoss(void)const
double __thiscall idAsyncClient::GetIncomingPacketLoss(idAsyncClient *this)
{
  if ( this->clientState >= CS_CONNECTED )
    return idMsgChannel::GetIncomingPacketLoss(&this->channel);
  else
    return 0.0;
}

// FUNC: public: struct netadr_t __thiscall idAsyncClient::GetServerAddress(void)
netadr_t *__thiscall idAsyncClient::GetServerAddress(idAsyncClient *this, netadr_t *result)
{
  netadr_t *v2; // eax

  v2 = result;
  *result = this->serverAddress;
  return v2;
}

// FUNC: private: void __thiscall idAsyncClient::InitGame(int,int,int,class idDict const &)
void __thiscall idAsyncClient::InitGame(
        idAsyncClient *this,
        int serverGameInitId,
        int serverGameFrame,
        int serverGameTime,
        idDict *serverSI)
{
  int v5; // esi
  idDict *userInfo; // edi

  this->gameInitId = serverGameInitId;
  this->snapshotGameFrame = serverGameFrame;
  this->gameFrame = serverGameFrame;
  this->snapshotGameTime = serverGameTime;
  this->gameTime = serverGameTime;
  this->gameTimeResidual = 0;
  memset(this->userCmds, 0, sizeof(this->userCmds));
  this->clientUserDictSequence = 0;
  v5 = 0;
  userInfo = sessLocal.mapSpawnData.userInfo;
  do
  {
    idDict::Clear(userInfo);
    sessLocal.mapSpawnData.mapLastUIRequestTime[v5] = 0;
    sessLocal.mapSpawnData.mapLastUIInitialRequest[v5] = 1;
    ++userInfo;
    ++v5;
  }
  while ( (int)userInfo < (int)sessLocal.mapSpawnData.mapLastUIRequestTime );
  idDict::operator=(&sessLocal.mapSpawnData.serverInfo, serverSI);
}

// FUNC: public: enum rconPassCheck_t __thiscall idAsyncClient::CheckRconReturnValue(char const *)
// local variable allocation has failed, the output may be wrong!
int __thiscall idAsyncClient::CheckRconReturnValue(idAsyncClient *this, const char *message)
{
  const char *v2; // eax
  int v3; // edx
  const char *v4; // eax
  int v5; // edx
  const char *v6; // eax
  _BYTE msgServer[12]; // [esp+18h] [ebp-24h] OVERLAPPED BYREF
  char msgPass[11]; // [esp+24h] [ebp-18h] BYREF
  char msgFail[11]; // [esp+30h] [ebp-Ch] BYREF

  v2 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                       common.type,
                       message,
                       -1,
                       10,
                       *(_DWORD *)msgServer,
                       *(_DWORD *)&msgServer[4],
                       *(_DWORD *)&msgServer[8]);
  strncpy(&msgPass[4], v2, *(size_t *)msgPass);
  v3 = *(_DWORD *)common.type;
  *(_DWORD *)msgPass = 10;
  *(_DWORD *)&msgServer[8] = -1;
  *(_DWORD *)&msgServer[4] = "#str_107250";
  v4 = (const char *)(*(int (__thiscall **)(netadrtype_t))(v3 + 168))(common.type);
  strncpy(&msgPass[8], v4, (size_t)"#str_107250");
  v5 = *(_DWORD *)common.type;
  *(_DWORD *)&msgServer[4] = 10;
  *(_DWORD *)msgServer = -1;
  v6 = (const char *)(*(int (__thiscall **)(netadrtype_t))(v5 + 168))(common.type);
  strncpy(msgFail, v6, (size_t)"#str_104847");
  msgServer[10] = 0;
  msgPass[10] = 0;
  msgFail[10] = 0;
  if ( idStr::Cmp(msgPass, msgServer) )
    return idStr::Cmp(msgFail, msgServer) == 0;
  else
    return 2;
}

// FUNC: private: void __thiscall idAsyncClient::ProcessDisconnectMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessDisconnectMessage(idAsyncClient *this, netadr_t from, const idBitMsg *msg)
{
  idSession_vtbl *v3; // esi
  int v4; // eax

  if ( this->clientState )
  {
    if ( Sys_CompareNetAdrBase(from, this->serverAddress) )
    {
      session->Stop(session);
      v3 = session->__vftable;
      v4 = (*(int (__thiscall **)(netadrtype_t, const char *, int, _DWORD, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
             common.type,
             "#str_104319",
             -1,
             0,
             1,
             0,
             0,
             0);
      ((void (__thiscall *)(idSession *, _DWORD, int))v3->MessageBoxA)(session, 0, v4);
      session->StartMenu(session, &entityFilter);
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "Disconnect packet from unknown server.\n");
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Disconnect packet while not connected.\n");
  }
}

// FUNC: private: int __thiscall idAsyncClient::GetDownloadRequest(int const * const,int,int)
int __thiscall idAsyncClient::GetDownloadRequest(
        idAsyncClient *this,
        const int *checksums,
        int count,
        int gamePakChecksum)
{
  int *v5; // eax
  int result; // eax

  v5 = &this->dlChecksums[1];
  if ( !memcmp(&this->dlChecksums[1], checksums, 4 * count) && gamePakChecksum == this->dlChecksums[0] )
    return this->dlRequest;
  this->dlChecksums[0] = gamePakChecksum;
  qmemcpy(v5, checksums, 0x200u);
  result = (3533 * (unsigned __int16)Sys_Milliseconds() + 1) & 0x7FFF;
  this->dlRequest = result;
  this->dlCount = count + (gamePakChecksum != 0);
  return result;
}

// FUNC: public: void __thiscall idAsyncClient::WriteEndUsercmd(class idFile *)const
void __thiscall idAsyncClient::WriteEndUsercmd(idAsyncClient *this, idFile *file)
{
  file->WriteInt(file, -1);
}

// FUNC: public: bool __thiscall idAsyncClient::ReadDemoUsercmd(class idFile *,class usercmd_t &)
char __thiscall idAsyncClient::ReadDemoUsercmd(idAsyncClient *this, idFile *file, usercmd_t *usercmd)
{
  if ( file->ReadInt(file, (int *)usercmd) != 4 || usercmd->gameFrame == -1 )
    return 0;
  file->ReadInt(file, &usercmd->gameTime);
  file->ReadInt(file, &usercmd->realTime);
  file->ReadInt(file, &usercmd->duplicateCount);
  file->ReadShort(file, &usercmd->buttons);
  file->Read(file, &usercmd->forwardmove, 1);
  file->Read(file, &usercmd->rightmove, 1);
  file->Read(file, &usercmd->upmove, 1);
  file->ReadShort(file, usercmd->angles);
  file->ReadShort(file, &usercmd->angles[1]);
  file->ReadShort(file, &usercmd->angles[2]);
  file->Read(file, &usercmd->impulse, 1);
  file->Read(file, &usercmd->flags, 1);
  return 1;
}

// FUNC: public: void __thiscall idAsyncClient::SetDemoUsercmd(class usercmd_t const &)
void __thiscall idAsyncClient::SetDemoUsercmd(idAsyncClient *this, const usercmd_t *usercmd)
{
  qmemcpy(
    &this->userCmds[(unsigned __int8)this->gameFrame][this->clientNum],
    usercmd,
    sizeof(this->userCmds[(unsigned __int8)this->gameFrame][this->clientNum]));
}

// FUNC: public: void __thiscall idAsyncClient::CheckDeclChecksum(void)
void __thiscall idAsyncClient::CheckDeclChecksum(idAsyncClient *this)
{
  int v2; // eax
  int clientDataChecksum; // ecx

  v2 = declManager->GetChecksum(declManager);
  clientDataChecksum = this->clientDataChecksum;
  if ( v2 != clientDataChecksum )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "decl checksum at time of recording ( 0x%x ) and at playback time don't match ( 0x%x )",
      clientDataChecksum,
      v2);
}

// FUNC: public: void __thiscall idAsyncClient::GetServerInfo(struct netadr_t)
void __thiscall idAsyncClient::GetServerInfo(idAsyncClient *this, netadr_t adr)
{
  int v3; // esi
  const char *v4; // eax
  idBitMsg v5; // [esp+10h] [ebp-4024h] BYREF
  char v6[16384]; // [esp+34h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v5);
  if ( idAsyncClient::InitPort(this) )
  {
    v5.readData = (const unsigned __int8 *)v6;
    v5.writeData = (unsigned __int8 *)v6;
    v5.maxSize = 0x4000;
    v5.numValueOverflows = 0;
    idBitMsg::WriteBits(&v5, -1, -16);
    idBitMsg::WriteString(&v5, "getInfo", -1);
    idBitMsg::WriteBits(&v5, this->serverList.challenge, 32);
    idPort::SendPacket(&this->clientPort, adr, v5.writeData, v5.curSize);
    v3 = *(_DWORD *)common.type;
    v4 = Sys_NetAdrToString(adr);
    (*(void (**)(netadrtype_t, const char *, ...))(v3 + 124))(
      common.type,
      "idAsyncClient::GetServerInfo() - Sending getInfo to %s\n",
      v4);
  }
}

// FUNC: public: void __thiscall idAsyncClient::GetServerInfo(char const *)
void __thiscall idAsyncClient::GetServerInfo(idAsyncClient *this, const char *address)
{
  int v3; // ecx
  int v4; // edx
  netadr_t adr; // [esp+8h] [ebp-Ch] BYREF

  if ( address && *address )
  {
    if ( !Sys_StringToNetAdr(address, &adr, 1) )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Couldn't get server address for \"%s\"\n",
        address);
      return;
    }
  }
  else if ( this->active )
  {
    v3 = *(_DWORD *)this->serverAddress.ip;
    v4 = *(_DWORD *)&this->serverAddress.port;
    adr.type = this->serverAddress.type;
    *(_DWORD *)adr.ip = v3;
    *(_DWORD *)&adr.port = v4;
  }
  else
  {
    if ( !idAsyncNetwork::server.active )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "no server found\n");
      return;
    }
    Sys_StringToNetAdr("localhost", &adr, 1);
    adr.port = idDeclPDA::GetNumEmails((idDeclPDA *)&idAsyncNetwork::server);
  }
  if ( !adr.port )
    adr.port = 28004;
  idAsyncClient::GetServerInfo(this, adr);
}

// FUNC: public: void __thiscall idAsyncClient::GetLANServers(void)
void __thiscall idAsyncClient::GetLANServers(idAsyncClient *this)
{
  int v2; // esi
  int v3; // ebp
  idPort *p_clientPort; // ebx
  netadr_t v5; // [esp-14h] [ebp-4054h]
  idBitMsg v6; // [esp+10h] [ebp-4030h] BYREF
  int v7; // [esp+38h] [ebp-4008h]
  unsigned int v8; // [esp+3Ch] [ebp-4004h]
  char v9[16384]; // [esp+40h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v6);
  if ( idAsyncClient::InitPort(this) )
  {
    idAsyncNetwork::LANServer.internalVar->InternalSetBool(idAsyncNetwork::LANServer.internalVar, 1);
    v6.writeData = (unsigned __int8 *)v9;
    v2 = 0;
    v6.readData = (const unsigned __int8 *)v9;
    v6.maxSize = 0x4000;
    v6.numValueOverflows = 0;
    idBitMsg::WriteBits(&v6, -1, -16);
    idBitMsg::WriteString(&v6, "getInfo", -1);
    idBitMsg::WriteBits(&v6, this->serverList.challenge, 32);
    v3 = v7;
    p_clientPort = &this->clientPort;
    do
    {
      LOWORD(v8) = v2 + 28004;
      v5.type = NA_BROADCAST;
      *(_QWORD *)v5.ip = __PAIR64__(v8, v3);
      idPort::SendPacket(p_clientPort, v5, v6.writeData, v6.curSize);
      ++v2;
    }
    while ( v2 < 8 );
  }
}

// FUNC: public: void __thiscall idAsyncClient::GetNETServers(char const *,char const *)
void __thiscall idAsyncClient::GetNETServers(idAsyncClient *this, char *filterPlayer, char *filterClan)
{
  const char *v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  idBitMsg v8; // [esp+10h] [ebp-4034h] BYREF
  netadr_t adr; // [esp+38h] [ebp-400Ch] BYREF

  idBitMsg::idBitMsg((idBitMsg *)&v8.readData);
  if ( idAsyncClient::InitPort(this) )
  {
    ((void (__thiscall *)(idCVar *))idAsyncNetwork::LANServer.internalVar->InternalSetBool)(idAsyncNetwork::LANServer.internalVar);
    v8.readData = (const unsigned __int8 *)&adr.port;
    v8.writeData = (unsigned __int8 *)&adr.port;
    v8.maxSize = 0x4000;
    v8.numValueOverflows = 0;
    idBitMsg::WriteBits(&v8, -1, -16);
    idBitMsg::WriteString(&v8, "getServers", -1);
    idBitMsg::WriteBits(&v8, 131136, 32);
    v4 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->GetCVarString)(
                         cvarSystem,
                         "fs_game",
                         -1);
    idBitMsg::WriteString((idBitMsg *)&v8.readData, v4, 0);
    idBitMsg::WriteString((idBitMsg *)&v8.readData, filterPlayer, -1);
    idBitMsg::WriteString((idBitMsg *)&v8.readData, filterClan, -1);
    v5 = cvarSystem->GetCVarInteger(cvarSystem, "gui_filter_password");
    idBitMsg::WriteBits((idBitMsg *)&v8.readData, v5, 2);
    v6 = cvarSystem->GetCVarInteger(cvarSystem, "gui_filter_players");
    idBitMsg::WriteBits((idBitMsg *)&v8.readData, v6, 2);
    v7 = cvarSystem->GetCVarInteger(cvarSystem, "gui_filter_gameType");
    idBitMsg::WriteBits((idBitMsg *)&v8.readData, v7, 2);
    if ( idAsyncNetwork::GetMasterAddress(0, &adr) )
      idPort::SendPacket(&this->clientPort, adr, v8.readData, v8.writeBit);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "idAsyncClient::GetNETServers() - Error initializing client port\n");
  }
}

// FUNC: public: void __thiscall idAsyncClient::GetFriends(void)
void __thiscall idAsyncClient::GetFriends(idAsyncClient *this)
{
  int v2; // esi
  int v3; // ebx
  netadr_t adr; // [esp+10h] [ebp-403Ch] BYREF
  idBitMsg v5; // [esp+1Ch] [ebp-4030h] BYREF
  char guid[12]; // [esp+40h] [ebp-400Ch] BYREF
  char v7[16384]; // [esp+4Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v5);
  if ( *cvarSystem->GetCVarString(cvarSystem, "com_guid") )
  {
    v2 = 0;
    v5.writeData = (unsigned __int8 *)v7;
    v5.readData = (const unsigned __int8 *)v7;
    v5.maxSize = 0x4000;
    v5.numValueOverflows = 0;
    idBitMsg::WriteBits(&v5, -1, -16);
    idBitMsg::WriteString(&v5, "getFriends", -1);
    idBitMsg::WriteBits(&v5, 131136, 32);
    v3 = 0;
    if ( rvServerScan::GetNumFriendsInFriendsList(&this->serverList) <= 0 )
      goto LABEL_9;
    do
    {
      if ( rvServerScan::GetFriendGUIDFromFriendsList(&this->serverList, v2, guid) )
      {
        idBitMsg::WriteString(&v5, guid, 12);
        ++v3;
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "idAsyncClient::GetFriends() - Bad guid '%s'\n",
          guid);
      }
      ++v2;
    }
    while ( v2 < rvServerScan::GetNumFriendsInFriendsList(&this->serverList) );
    if ( v3 > 0 )
    {
      if ( idAsyncNetwork::GetMasterAddress(0, &adr) )
        idPort::SendPacket(&this->clientPort, adr, v5.writeData, v5.curSize);
    }
    else
    {
LABEL_9:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "idAsyncClient::GetFriends() - No valid guids written, not transmitting\n");
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "idAsyncClient::GetFriends() - client does not have a guid\n");
  }
}

// FUNC: public: void __thiscall idAsyncClient::ListServers(void)
void __thiscall idAsyncClient::ListServers(idAsyncClient *this)
{
  int v2; // ebx
  int v3; // edi
  const idKeyValue *Key; // eax
  int v5; // ebp
  const char *v6; // eax
  const char *data; // [esp+10h] [ebp-8h]
  networkServer_t *v8; // [esp+14h] [ebp-4h]

  v2 = 0;
  if ( this->serverList.activeServers.num > 0 )
  {
    v3 = 0;
    do
    {
      v8 = &this->serverList.activeServers.list[v3];
      Key = idDict::FindKey(&v8->serverInfo, "si_name");
      if ( Key )
        data = Key->value->data;
      else
        data = &entityFilter;
      v5 = *(_DWORD *)common.type;
      v6 = Sys_NetAdrToString(this->serverList.activeServers.list[v3].adr);
      (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(
        common.type,
        "%3d: %s %dms (%s)\n",
        v2++,
        data,
        v8->ping,
        v6);
      ++v3;
    }
    while ( v2 < this->serverList.activeServers.num );
  }
}

// FUNC: public: void __thiscall idAsyncClient::RemoteConsole(char const *)
void __thiscall idAsyncClient::RemoteConsole(idAsyncClient *this, char *command)
{
  int v3; // edx
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int realTime; // eax
  netadr_t a; // [esp+4h] [ebp-4030h] BYREF
  idBitMsg v9; // [esp+10h] [ebp-4024h] BYREF
  char v10[16384]; // [esp+34h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v9);
  if ( idAsyncClient::InitPort(this) )
  {
    if ( this->active )
    {
      v3 = *(_DWORD *)this->serverAddress.ip;
      v4 = *(_DWORD *)&this->serverAddress.port;
      a.type = this->serverAddress.type;
      *(_DWORD *)a.ip = v3;
      *(_DWORD *)&a.port = v4;
    }
    else
    {
      Sys_StringToNetAdr(idAsyncNetwork::clientRemoteConsoleAddress.internalVar->value, &a, 1);
    }
    if ( !a.port )
      a.port = 28004;
    v5 = *(_DWORD *)a.ip;
    this->lastRconAddress.type = a.type;
    v6 = *(_DWORD *)&a.port;
    *(_DWORD *)this->lastRconAddress.ip = v5;
    realTime = this->realTime;
    *(_DWORD *)&this->lastRconAddress.port = v6;
    v9.writeData = (unsigned __int8 *)v10;
    this->lastRconTime = realTime;
    v9.readData = (const unsigned __int8 *)v10;
    v9.maxSize = 0x4000;
    v9.numValueOverflows = 0;
    idBitMsg::WriteBits(&v9, -1, -16);
    idBitMsg::WriteString(&v9, "rcon", -1);
    idBitMsg::WriteString(&v9, idAsyncNetwork::clientRemoteConsolePassword.internalVar->value, -1);
    idBitMsg::WriteString(&v9, command, -1);
    idPort::SendPacket(&this->clientPort, a, v9.writeData, v9.curSize);
  }
}

// FUNC: public: int __thiscall idAsyncClient::GetOutgoingRate(void)const
int __thiscall idAsyncClient::GetOutgoingRate(idAsyncClient *this)
{
  if ( this->clientState >= CS_CONNECTED )
    return this->channel.outgoingRateBytes;
  else
    return -1;
}

// FUNC: public: int __thiscall idAsyncClient::GetIncomingRate(void)const
int __thiscall idAsyncClient::GetIncomingRate(idAsyncClient *this)
{
  if ( this->clientState >= CS_CONNECTED )
    return this->channel.incomingRateBytes;
  else
    return -1;
}

// FUNC: public: float __thiscall idAsyncClient::GetOutgoingCompression(void)const
double __thiscall idAsyncClient::GetOutgoingCompression(idAsyncClient *this)
{
  if ( this->clientState >= CS_CONNECTED )
    return this->channel.outgoingCompression;
  else
    return 0.0;
}

// FUNC: public: float __thiscall idAsyncClient::GetIncomingCompression(void)const
double __thiscall idAsyncClient::GetIncomingCompression(idAsyncClient *this)
{
  if ( this->clientState >= CS_CONNECTED )
    return this->channel.incomingCompression;
  else
    return 0.0;
}

// FUNC: private: void __thiscall idAsyncClient::DuplicateUsercmds(int,int)
void __thiscall idAsyncClient::DuplicateUsercmds(idAsyncClient *this, int frame, int time)
{
  int v3; // edi
  const usercmd_t *v4; // ebp
  usercmd_t *v5; // ebx

  v3 = 0;
  v4 = this->userCmds[(unsigned __int8)(frame - 1)];
  v5 = this->userCmds[(unsigned __int8)frame];
  do
  {
    if ( idAsyncNetwork::DuplicateUsercmd(v4, v5, frame, time) && v3 == this->clientNum )
    {
      if ( idAsyncNetwork::demo.demoState == DEMO_PLAYING )
      {
        if ( idDemo::debug.internalVar->integerValue )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "duped self ucmds for frame %d\n",
            frame);
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
          common.type,
          "duped self ucmds for frame %d\n",
          frame);
      }
    }
    ++v3;
    ++v5;
    ++v4;
  }
  while ( v3 < 32 );
}

// FUNC: private: void __thiscall idAsyncClient::SendEmptyToServer(bool,bool)
void __thiscall idAsyncClient::SendEmptyToServer(idAsyncClient *this, bool force, bool mapLoad)
{
  int realTime; // eax
  int gameInitId; // eax
  int serverMessageSequence; // edx
  int v7; // eax
  idBitMsg msg; // [esp+4h] [ebp-4024h] BYREF
  char v9[16384]; // [esp+28h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  realTime = this->realTime;
  if ( this->lastEmptyTime > realTime )
    this->lastEmptyTime = realTime;
  if ( force || realTime - this->lastEmptyTime >= 500 )
  {
    if ( idAsyncNetwork::verbose.internalVar->integerValue )
    {
      gameInitId = -2;
      if ( !mapLoad )
        gameInitId = this->gameInitId;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "sending empty to server, gameInitId = %d\n",
        gameInitId);
    }
    serverMessageSequence = this->serverMessageSequence;
    msg.readData = (const unsigned __int8 *)v9;
    msg.writeData = (unsigned __int8 *)v9;
    msg.maxSize = 0x4000;
    msg.numValueOverflows = 0;
    idBitMsg::WriteBits(&msg, serverMessageSequence, 32);
    v7 = -2;
    if ( !mapLoad )
      v7 = this->gameInitId;
    idBitMsg::WriteBits(&msg, v7, 32);
    idBitMsg::WriteBits(&msg, this->snapshotSequence, 32);
    idBitMsg::WriteBits(&msg, 0, 8);
    idMsgChannel::SendMessageA(&this->channel, &this->clientPort, this->clientTime, &msg);
    while ( this->channel.unsentFragments )
      idMsgChannel::SendNextFragment(&this->channel, &this->clientPort, this->clientTime);
    this->lastEmptyTime = this->realTime;
  }
}

// FUNC: private: void __thiscall idAsyncClient::SendPingResponseToServer(int)
void __thiscall idAsyncClient::SendPingResponseToServer(idAsyncClient *this, int time)
{
  int serverMessageSequence; // edx
  idBitMsg msg; // [esp+Ch] [ebp-4024h] BYREF
  char v5[16384]; // [esp+30h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  if ( idAsyncNetwork::verbose.internalVar->integerValue == 2 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "sending ping response to server, gameInitId = %d\n",
      this->gameInitId);
  serverMessageSequence = this->serverMessageSequence;
  msg.readData = (const unsigned __int8 *)v5;
  msg.writeData = (unsigned __int8 *)v5;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, serverMessageSequence, 32);
  idBitMsg::WriteBits(&msg, this->gameInitId, 32);
  idBitMsg::WriteBits(&msg, this->snapshotSequence, 32);
  idBitMsg::WriteBits(&msg, 1, 8);
  idBitMsg::WriteBits(&msg, time, 32);
  idMsgChannel::SendMessageA(&this->channel, &this->clientPort, this->clientTime, &msg);
  while ( this->channel.unsentFragments )
    idMsgChannel::SendNextFragment(&this->channel, &this->clientPort, this->clientTime);
}

// FUNC: private: void __thiscall idAsyncClient::SendUsercmdsToServer(void)
void __thiscall idAsyncClient::SendUsercmdsToServer(idAsyncClient *this)
{
  int gameFrame; // ebp
  int v3; // esi
  int serverMessageSequence; // eax
  int integerValue; // eax
  int v6; // edi
  int v7; // esi
  const usercmd_t *v8; // edx
  int clientNum; // ecx
  int v10; // edi
  idBitMsg msg; // [esp+Ch] [ebp-404Ch] BYREF
  char v12[40]; // [esp+30h] [ebp-4028h] BYREF
  char v13[16384]; // [esp+58h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  if ( idAsyncNetwork::verbose.internalVar->integerValue == 2 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "sending usercmd to server: gameInitId = %d, gameFrame = %d, gameTime = %d\n",
      this->gameInitId,
      this->gameFrame,
      this->gameTime);
  gameFrame = (unsigned __int8)this->gameFrame;
  qmemcpy(
    &this->userCmds[gameFrame][this->clientNum],
    (const void *)((int (__stdcall *)(char *))usercmdGen->GetDirectUsercmd)(v12),
    sizeof(this->userCmds[gameFrame][this->clientNum]));
  this->userCmds[gameFrame][this->clientNum].gameFrame = this->gameFrame;
  this->userCmds[gameFrame][this->clientNum].gameTime = this->gameTime;
  v3 = this->gameTime
     + this->clientPredictTime
     + this->gameTimeResidual
     - this->realTime
     - (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
  this->userCmds[gameFrame][this->clientNum].realTime = Sys_Milliseconds() + v3;
  if ( idAsyncNetwork::demo.demoState == DEMO_RECORDING )
    idDemo::RecordUsercmd(&idAsyncNetwork::demo, &this->userCmds[gameFrame][this->clientNum]);
  serverMessageSequence = this->serverMessageSequence;
  msg.writeData = (unsigned __int8 *)v13;
  msg.readData = (const unsigned __int8 *)v13;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, serverMessageSequence, 32);
  idBitMsg::WriteBits(&msg, this->gameInitId, 32);
  idBitMsg::WriteBits(&msg, this->snapshotSequence, 32);
  idBitMsg::WriteBits(&msg, 2, 8);
  idBitMsg::WriteBits(&msg, this->clientPrediction, -16);
  integerValue = idAsyncNetwork::clientUsercmdBackup.internalVar->integerValue;
  if ( integerValue >= 0 )
  {
    if ( integerValue > 10 )
      integerValue = 10;
  }
  else
  {
    integerValue = 0;
  }
  v6 = integerValue + 1;
  idBitMsg::WriteBits(&msg, this->gameFrame, 32);
  idBitMsg::WriteBits(&msg, v6, 8);
  v7 = this->gameFrame - v6 + 1;
  v8 = 0;
  if ( v7 <= this->gameFrame )
  {
    clientNum = this->clientNum;
    do
    {
      v10 = 32 * (unsigned __int8)v7;
      idAsyncNetwork::WriteUserCmdDelta(&msg, &this->userCmds[0][clientNum + v10], v8);
      clientNum = this->clientNum;
      ++v7;
      v8 = &this->userCmds[0][clientNum + v10];
    }
    while ( v7 <= this->gameFrame );
  }
  idMsgChannel::SendMessageA(&this->channel, &this->clientPort, this->clientTime, &msg);
  while ( this->channel.unsentFragments )
    idMsgChannel::SendNextFragment(&this->channel, &this->clientPort, this->clientTime);
}

// FUNC: private: void __thiscall idAsyncClient::ProcessChallengeResponseMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessChallengeResponseMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  const char *v4; // eax
  const char *v5; // eax
  int v6; // ebp
  const char *v7; // eax
  char serverGameBase[1024]; // [esp+10h] [ebp-800h] BYREF
  char serverGame[1024]; // [esp+410h] [ebp-400h] BYREF

  if ( this->clientState == CS_CHALLENGING )
  {
    this->serverChallenge = idBitMsg::ReadBits(msg, 32);
    this->serverId = (__int16)idBitMsg::ReadBits(msg, -16);
    idBitMsg::ReadString(msg, serverGameBase, 1024);
    idBitMsg::ReadString(msg, serverGame, 1024);
    v4 = cvarSystem->GetCVarString(cvarSystem, "fs_game_base");
    if ( idStr::Icmp(v4, serverGameBase)
      || (v5 = cvarSystem->GetCVarString(cvarSystem, "fs_game"), idStr::Icmp(v5, serverGame)) )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "The server is running a different mod (%s-%s). Restarting..\n",
        serverGameBase,
        serverGame);
      cvarSystem->SetCVarString(cvarSystem, "fs_game_base", serverGameBase, 0);
      cvarSystem->SetCVarString(cvarSystem, "fs_game", serverGame, 0);
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "reloadEngine");
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "reconnect\n");
    }
    else
    {
      v6 = *(_DWORD *)common.type;
      v7 = Sys_NetAdrToString(from);
      (*(void (**)(netadrtype_t, const char *, ...))(v6 + 124))(
        common.type,
        "received challenge response 0x%x from %s\n",
        this->serverChallenge,
        v7);
      this->clientState = CS_CONNECTING;
      this->lastConnectTime = -9999;
      this->serverAddress = from;
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Unwanted challenge response received.\n");
  }
}

// FUNC: private: void __thiscall idAsyncClient::ProcessPrintMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessPrintMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  int v4; // ebp
  int Bits; // edi
  const char *v6; // eax
  int v7; // eax
  idSession_vtbl *v8; // edi
  int v9; // eax
  const char *v10; // edi
  idUserInterface_vtbl *v11; // ebx
  int v12; // eax
  idSession_vtbl *v13; // edi
  int v14; // eax
  char string[1024]; // [esp+18h] [ebp-400h] BYREF

  v4 = -1;
  Bits = idBitMsg::ReadBits(msg, 32);
  if ( Bits == 3 )
    v4 = idBitMsg::ReadBits(msg, 32);
  idBitMsg::ReadString(msg, string, 1024);
  v6 = (const char *)(*(int (__thiscall **)(netadrtype_t, char *, int))(*(_DWORD *)common.type + 168))(
                       common.type,
                       string,
                       -1);
  idStr::snPrintf(string, 1023, "%s", v6);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s\n", string);
  if ( Bits == 2 )
  {
    game->ReceiveRemoteConsoleOutput(game, string);
  }
  else if ( Bits == 3 )
  {
    goto LABEL_10;
  }
  v7 = idAsyncClient::CheckRconReturnValue(this, string);
  if ( v7 == 1 )
  {
    game->ProcessRconReturn(game, 0);
    return;
  }
  if ( v7 == 2 )
  {
    game->ProcessRconReturn(game, 1);
    return;
  }
LABEL_10:
  this->guiNetMenu->SetStateString(this->guiNetMenu, "status", string);
  if ( Bits == 3 )
  {
    if ( v4 == 1 )
    {
      v8 = session->__vftable;
      v9 = (*(int (__thiscall **)(netadrtype_t, const char *, int, char *, int, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
             common.type,
             "#str_104321",
             -1,
             string,
             1,
             "passprompt_ok",
             0,
             0);
      v10 = (const char *)((int (__thiscall *)(idSession *, int, int))v8->MessageBoxA)(session, 4, v9);
      idAsyncClient::ClearPendingPackets(this);
      v11 = this->guiNetMenu->__vftable;
      v12 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104322",
              -1);
      v11->SetStateString(this->guiNetMenu, "status", (const char *)v12);
      if ( v10 )
      {
        cvarSystem->SetCVarString(cvarSystem, "password", &entityFilter, 0);
        cvarSystem->SetCVarString(cvarSystem, "password", v10, 0);
      }
      else
      {
        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
      }
    }
    else if ( v4 == 3 )
    {
      v13 = session->__vftable;
      v14 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type
                                                                                                + 168))(
              common.type,
              "#str_104323",
              -1,
              1,
              0,
              0,
              0);
      ((void (__thiscall *)(idSession *, _DWORD, char *, int))v13->MessageBoxA)(session, 0, &string[16], v14);
      idAsyncClient::ClearPendingPackets(this);
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
    }
  }
  else if ( Bits == 4 && this->clientState >= CS_CONNECTING )
  {
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "reconnect");
  }
}

// FUNC: private: void __thiscall idAsyncClient::ProcessServersListMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessServersListMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  const netadr_t *MasterAddress; // eax
  int v5; // ebp
  const char *v6; // eax
  int Bits; // edi
  int v9; // ebx
  int v10; // ebp
  __int16 v11; // ax
  const char *v12; // eax
  netadr_t result; // [esp+10h] [ebp-Ch] BYREF
  rvServerScan *froma; // [esp+20h] [ebp+4h]
  const idBitMsg *msga; // [esp+2Ch] [ebp+10h]

  MasterAddress = idAsyncNetwork::GetMasterAddress(&result);
  if ( Sys_CompareNetAdrBase(*MasterAddress, from) )
  {
    if ( msg->curSize != msg->readCount )
    {
      froma = &this->serverList;
      do
      {
        Bits = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
        v9 = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
        v10 = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
        msga = (const idBitMsg *)(unsigned __int8)idBitMsg::ReadBits(msg, 8);
        v11 = idBitMsg::ReadBits(msg, -16);
        v12 = va("%i.%i.%i.%i:%i", Bits, v9, v10, msga, v11);
        rvServerScan::AddServer(froma, v12, -1);
      }
      while ( msg->curSize != msg->readCount );
    }
  }
  else
  {
    v5 = *(_DWORD *)common.type;
    v6 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v5 + 132))(
      common.type,
      "received a server list from %s - not a valid master\n",
      v6);
  }
}

// FUNC: private: void __thiscall idAsyncClient::ProcessFriendsMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessFriendsMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  const netadr_t *MasterAddress; // eax
  int v5; // ebp
  const char *v6; // eax
  int Bits; // edi
  int v8; // ebx
  int v9; // ebp
  const char *v10; // eax
  rvServerScan *p_serverList; // [esp+10h] [ebp-98h]
  char guid[12]; // [esp+14h] [ebp-94h] BYREF
  int d; // [esp+20h] [ebp-88h]
  int port; // [esp+24h] [ebp-84h]
  char clan[64]; // [esp+28h] [ebp-80h] BYREF
  char name[64]; // [esp+68h] [ebp-40h] BYREF

  MasterAddress = idAsyncNetwork::GetMasterAddress((netadr_t *)guid);
  if ( Sys_CompareNetAdrBase(*MasterAddress, from) )
  {
    if ( msg->curSize != msg->readCount )
    {
      p_serverList = &this->serverList;
      do
      {
        memset(name, 0, sizeof(name));
        memset(clan, 0, sizeof(clan));
        memset(guid, 0, sizeof(guid));
        idBitMsg::ReadString(msg, guid, 12);
        Bits = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
        v8 = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
        v9 = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
        d = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
        port = (__int16)idBitMsg::ReadBits(msg, -16);
        idBitMsg::ReadString(msg, name, 64);
        idBitMsg::ReadString(msg, clan, 64);
        v10 = va("%i.%i.%i.%i:%i", Bits, v8, v9, d, port);
        rvServerScan::AddFriend(p_serverList, guid, name, clan, v10);
      }
      while ( msg->curSize != msg->readCount );
    }
  }
  else
  {
    v5 = *(_DWORD *)common.type;
    v6 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v5 + 132))(
      common.type,
      "received a friends list from %s - not a valid master\n",
      v6);
  }
}

// FUNC: private: void __thiscall idAsyncClient::ProcessVersionMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessVersionMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  char string[1024]; // [esp+4h] [ebp-400h] BYREF

  if ( this->updateState == UPDATE_SENT )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "A new version is available\n");
    idBitMsg::ReadString(msg, string, 1024);
    idStr::operator=(&this->updateMSG, string);
    this->updateDirectDownload = (unsigned __int8)idBitMsg::ReadBits(msg, 8) != 0;
    idBitMsg::ReadString(msg, string, 1024);
    idStr::operator=(&this->updateURL, string);
    this->updateMime = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
    idBitMsg::ReadString(msg, string, 1024);
    idStr::operator=(&this->updateFallback, string);
    this->updateState = UPDATE_READY;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "ProcessVersionMessage: version reply, != UPDATE_SENT\n");
  }
}

// FUNC: private: void __thiscall idAsyncClient::SetupConnection(void)
void __thiscall idAsyncClient::SetupConnection(idAsyncClient *this)
{
  int v2; // eax
  const char *v3; // eax
  const char *v4; // eax
  int v5; // ebp
  const char *v6; // eax
  int v7; // ebx
  const char *v8; // eax
  int v9; // eax
  const char *v10; // eax
  const char *v11; // eax
  bool v12; // al
  const char *v13; // [esp+4h] [ebp-4040h]
  char v14; // [esp+8h] [ebp-403Ch]
  int serverChallenge; // [esp+Ch] [ebp-4038h]
  const char *v16; // [esp+10h] [ebp-4034h]
  bool v17; // [esp+14h] [ebp-4030h]
  idBitMsg v18; // [esp+20h] [ebp-4024h] BYREF
  char v19[16384]; // [esp+44h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v18);
  if ( this->clientTime - this->lastConnectTime >= 1000 )
  {
    if ( this->clientState == CS_CHALLENGING )
    {
      if ( this->challengesSent >= cvarSystem->GetCVarInteger(cvarSystem, "net_challengeLimit") )
      {
        v2 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
               common.type,
               "#str_100626",
               -1,
               1,
               0,
               0);
        v14 = ((int (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->GetCVarInteger)(
                cvarSystem,
                "net_challengeLimit",
                v2);
        v13 = Sys_NetAdrToString(this->serverAddress);
        v3 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                             common.type,
                             "#str_107655",
                             -1);
        v4 = va(v3);
        idSessionLocal::MessageBoxA(&sessLocal, MSG_OK, v4, v13, v14, 0, v16, v17);
        this->challengesSent = 0;
        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
      }
      ++this->challengesSent;
      v5 = *(_DWORD *)common.type;
      v6 = Sys_NetAdrToString(this->serverAddress);
      (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(common.type, "Sending challenge to %s\n", v6);
      v18.writeData = (unsigned __int8 *)v19;
      v18.readData = (const unsigned __int8 *)v19;
      v18.maxSize = 0x4000;
      v18.numValueOverflows = 0;
      idBitMsg::WriteBits(&v18, -1, -16);
      idBitMsg::WriteString(&v18, "challenge", -1);
      idBitMsg::WriteBits(&v18, this->clientId, 32);
      idPort::SendPacket(&this->clientPort, this->serverAddress, v18.writeData, v18.curSize);
    }
    else
    {
      if ( this->clientState != CS_CONNECTING )
        return;
      v7 = *(_DWORD *)common.type;
      serverChallenge = this->serverChallenge;
      v8 = Sys_NetAdrToString(this->serverAddress);
      (*(void (**)(netadrtype_t, const char *, ...))(v7 + 124))(
        common.type,
        "sending connect to %s with challenge 0x%x\n",
        v8,
        serverChallenge);
      v18.readData = (const unsigned __int8 *)v19;
      v18.writeData = (unsigned __int8 *)v19;
      v18.maxSize = 0x4000;
      v18.numValueOverflows = 0;
      idBitMsg::WriteBits(&v18, -1, -16);
      idBitMsg::WriteString(&v18, "connect", -1);
      idBitMsg::WriteBits(&v18, 131136, 32);
      idBitMsg::WriteBits(&v18, 0, -16);
      idBitMsg::WriteBits(&v18, this->clientDataChecksum, 32);
      idBitMsg::WriteBits(&v18, this->serverChallenge, 32);
      idBitMsg::WriteBits(&v18, this->clientId, -16);
      v9 = cvarSystem->GetCVarInteger(cvarSystem, "net_clientMaxRate");
      idBitMsg::WriteBits(&v18, v9, 32);
      v10 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->GetCVarString)(
                            cvarSystem,
                            "com_guid",
                            -1);
      idBitMsg::WriteString((idBitMsg *)&v18.readData, v10, (int)v16);
      v11 = cvarSystem->GetCVarString(cvarSystem, "password");
      idBitMsg::WriteString((idBitMsg *)&v18.readData, v11, -1);
      v12 = cvarSystem->GetCVarBool(cvarSystem, "cl_punkbuster");
      idBitMsg::WriteBits(&v18, v12, -16);
      idPort::SendPacket(&this->clientPort, this->serverAddress, v18.writeData, v18.curSize);
      if ( idAsyncNetwork::LANServer.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "net_LANServer is set, connecting in LAN mode\n");
      else
        session->EmitClientAuth(session);
    }
    this->lastConnectTime = this->clientTime;
  }
}

// FUNC: public: void __thiscall idAsyncClient::SendReliableGameMessage(class idBitMsg const &)
void __thiscall idAsyncClient::SendReliableGameMessage(idAsyncClient *this, const idBitMsg *msg)
{
  idBitMsg msga; // [esp+4h] [ebp-4024h] BYREF
  char v4[16384]; // [esp+28h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msga);
  if ( this->clientState >= CS_INGAME )
  {
    msga.readData = (const unsigned __int8 *)v4;
    msga.writeData = (unsigned __int8 *)v4;
    msga.maxSize = 0x4000;
    msga.numValueOverflows = 0;
    idBitMsg::WriteBits(&msga, 4, 8);
    idBitMsg::WriteData(&msga, msg->readData, msg->curSize);
    if ( !idMsgChannel::SendReliableMessage(&this->channel, &msga) )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "client->server reliable messages overflow\n");
  }
}

// FUNC: private: void __thiscall idAsyncClient::Idle(void)
void __thiscall idAsyncClient::Idle(idAsyncClient *this)
{
  char v2[40]; // [esp+4h] [ebp-28h] BYREF

  usercmdGen->GetDirectUsercmd(usercmdGen, (usercmd_t *)v2);
  idAsyncClient::SendEmptyToServer(this, 0, 0);
}

// FUNC: public: void __thiscall idAsyncClient::PacifierUpdate(void)
void __thiscall idAsyncClient::PacifierUpdate(idAsyncClient *this)
{
  if ( this->active )
  {
    this->realTime = Sys_Milliseconds();
    idAsyncClient::SendEmptyToServer(this, 0, 1);
  }
}

// FUNC: public: void __thiscall idAsyncClient::SendVersionCheck(bool)
void __thiscall idAsyncClient::SendVersionCheck(idAsyncClient *this, bool fromMenu)
{
  const char *v3; // eax
  const char *v4; // eax
  int clientTime; // edx
  idSession_vtbl *v6; // esi
  int v7; // eax
  netadr_t v8; // [esp-10h] [ebp-4048h]
  int v9; // [esp+0h] [ebp-4038h]
  idBitMsg v10; // [esp+8h] [ebp-4030h] BYREF
  netadr_t result; // [esp+30h] [ebp-4008h] BYREF

  idBitMsg::idBitMsg(&v10);
  if ( this->updateState == UPDATE_NONE || fromMenu )
  {
    idAsyncClient::InitPort(this);
    v10.writeData = (unsigned __int8 *)&result.port;
    v10.readData = (const unsigned __int8 *)&result.port;
    v10.maxSize = 0x4000;
    v10.numValueOverflows = 0;
    idBitMsg::WriteBits(&v10, -1, -16);
    idBitMsg::WriteString(&v10, "versionCheck", -1);
    idBitMsg::WriteBits(&v10, 131136, 32);
    idBitMsg::WriteBits(&v10, 0, -16);
    v3 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->GetCVarString)(
                         cvarSystem,
                         "si_version",
                         -1);
    idBitMsg::WriteString((idBitMsg *)&v10.readData, v3, v9);
    v4 = cvarSystem->GetCVarString(cvarSystem, "com_guid");
    idBitMsg::WriteString((idBitMsg *)&v10.readData, v4, -1);
    v8 = *idAsyncNetwork::GetMasterAddress(&result);
    idPort::SendPacket(&this->clientPort, v8, v10.readData, v10.writeBit);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "sent a version check request\n");
    clientTime = this->clientTime;
    this->updateState = UPDATE_SENT;
    this->updateSentTime = clientTime;
    this->showUpdateMessage = fromMenu;
    v6 = session->__vftable;
    v7 = (*(int (__thiscall **)(netadrtype_t, const char *, int, _DWORD, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type
                                                                                                + 168))(
           common.type,
           "#str_107683",
           -1,
           0,
           0,
           0,
           0);
    ((void (__thiscall *)(idSession *, int, int))v6->MessageBoxA)(session, 7, v7);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "up-to-date check was already performed\n");
  }
}

// FUNC: private: void __thiscall idAsyncClient::SendVersionDLUpdate(int)
void __thiscall idAsyncClient::SendVersionDLUpdate(idAsyncClient *this, int state)
{
  netadr_t v3; // [esp-14h] [ebp-4048h]
  idBitMsg v4; // [esp+4h] [ebp-4030h] BYREF
  netadr_t result; // [esp+28h] [ebp-400Ch] BYREF
  char v6[16384]; // [esp+34h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v4);
  v4.readData = (const unsigned __int8 *)v6;
  v4.writeData = (unsigned __int8 *)v6;
  v4.maxSize = 0x4000;
  v4.numValueOverflows = 0;
  idBitMsg::WriteBits(&v4, -1, -16);
  idBitMsg::WriteString(&v4, "versionDL", -1);
  idBitMsg::WriteBits(&v4, 131136, 32);
  idBitMsg::WriteBits(&v4, state, -16);
  v3 = *idAsyncNetwork::GetMasterAddress(&result);
  idPort::SendPacket(&this->clientPort, v3, v4.writeData, v4.curSize);
}

// FUNC: public: bool __thiscall idAsyncClient::SendAuthCheck(char const *)
char __thiscall idAsyncClient::SendAuthCheck(idAsyncClient *this, char *cdkey)
{
  const char *v3; // edi
  netadr_t v5; // [esp-14h] [ebp-404Ch]
  idBitMsg v6; // [esp+8h] [ebp-4030h] BYREF
  netadr_t result; // [esp+2Ch] [ebp-400Ch] BYREF
  char v8[16384]; // [esp+38h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v6);
  v6.readData = (const unsigned __int8 *)v8;
  v6.writeData = (unsigned __int8 *)v8;
  v6.maxSize = 0x4000;
  v6.numValueOverflows = 0;
  idBitMsg::WriteBits(&v6, -1, -16);
  idBitMsg::WriteString(&v6, "gameAuth", -1);
  idBitMsg::WriteBits(&v6, 131136, 32);
  v3 = cdkey;
  idBitMsg::WriteBits(&v6, cdkey != 0, 8);
  if ( !cdkey )
    v3 = &entityFilter;
  idBitMsg::WriteString(&v6, v3, -1);
  idAsyncClient::InitPort(this);
  v5 = *idAsyncNetwork::GetMasterAddress(&result);
  idPort::SendPacket(&this->clientPort, v5, v6.writeData, v6.curSize);
  return 1;
}

// FUNC: private: bool __thiscall idAsyncClient::CheckTimeout(void)
char __thiscall idAsyncClient::CheckTimeout(idAsyncClient *this)
{
  int lastPacketTime; // edx
  idSession_vtbl *v2; // esi
  int v3; // eax
  int v4; // eax

  lastPacketTime = this->lastPacketTime;
  if ( lastPacketTime <= 0
    || lastPacketTime + 1000 * idAsyncNetwork::clientServerTimeout.internalVar->integerValue >= this->clientTime )
  {
    return 0;
  }
  session->StopBox(session);
  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
  v2 = session->__vftable;
  v3 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, int))(*(_DWORD *)common.type + 168))(
         common.type,
         "#str_104329",
         -1,
         1,
         0,
         0,
         1);
  v4 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
         common.type,
         "#str_104328",
         -1,
         v3);
  ((void (__thiscall *)(idSession *, _DWORD, int))v2->MessageBoxA)(session, 0, v4);
  return 1;
}

// FUNC: public: void __thiscall idAsyncClient::PbSendPacket(struct netadr_t,void const *,int)
void __thiscall idAsyncClient::PbSendPacket(idAsyncClient *this, netadr_t to, void *data, int size)
{
  idBitMsg v5; // [esp+4h] [ebp-4024h] BYREF
  char v6[16384]; // [esp+28h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v5);
  v5.writeData = (unsigned __int8 *)v6;
  v5.readData = (const unsigned __int8 *)v6;
  v5.maxSize = 0x4000;
  v5.numValueOverflows = 0;
  idBitMsg::WriteData(&v5, data, size);
  idPort::SendPacket(&this->clientPort, to, v5.writeData, v5.curSize);
}

// FUNC: private: int __thiscall idAsyncClient::UpdateDemoTime(int)
int __thiscall idAsyncClient::UpdateDemoTime(idAsyncClient *this, int clamp)
{
  int v3; // eax
  int v4; // ecx
  int result; // eax

  v3 = Sys_Milliseconds();
  if ( (idDemo::scale.internalVar->flags & 0x40000) != 0 )
  {
    this->demoScaleTimeOffset = v3;
    BYTE2(idDemo::scale.internalVar->flags) &= ~4u;
  }
  v4 = (int)((double)(v3 - this->demoScaleTimeOffset) * idDemo::scale.internalVar->floatValue
           + (double)this->demoScaleTimeOffset);
  result = v4 - this->realTime;
  if ( result >= 0 )
  {
    if ( result > clamp )
      result = clamp;
    this->clientTime += result;
    this->realTime = v4;
  }
  else
  {
    result = 0;
    this->clientTime = this->clientTime;
    this->realTime = v4;
  }
  return result;
}

// FUNC: public: int __thiscall idAsyncClient::ReadDemoHeader(class idFile *)
int __thiscall idAsyncClient::ReadDemoHeader(idAsyncClient *this, idFile *file)
{
  usercmd_t *v4; // ebx
  int v5; // ebp
  int v7; // [esp+5Ch] [ebp-8h]
  usercmd_t (*filea)[32]; // [esp+68h] [ebp+4h]

  this->active = 1;
  this->clientState = CS_INGAME;
  this->lastPacketTime = -9999;
  this->demoScaleTimeOffset = 0;
  file->ReadInt(file, &this->clientDataChecksum);
  file->ReadInt(file, &this->clientTime);
  file->ReadInt(file, &this->clientId);
  file->ReadInt(file, &this->clientNum);
  file->ReadInt(file, &this->clientPrediction);
  file->ReadInt(file, &this->clientPredictTime);
  file->ReadInt(file, &this->lastConnectTime);
  file->ReadInt(file, (int *)&this->serverAddress);
  file->ReadUnsignedChar(file, this->serverAddress.ip);
  file->ReadUnsignedChar(file, &this->serverAddress.ip[1]);
  file->ReadUnsignedChar(file, &this->serverAddress.ip[2]);
  file->ReadUnsignedChar(file, &this->serverAddress.ip[3]);
  file->ReadUnsignedShort(file, &this->serverAddress.port);
  file->ReadInt(file, &this->serverId);
  file->ReadInt(file, &this->serverChallenge);
  file->ReadInt(file, &this->serverMessageSequence);
  file->ReadInt(file, &this->snapshotSequence);
  file->ReadInt(file, &this->snapshotGameFrame);
  file->ReadInt(file, &this->snapshotGameTime);
  file->ReadInt(file, &this->gameInitId);
  file->ReadInt(file, &this->gameFrame);
  file->ReadInt(file, &this->gameTime);
  file->ReadInt(file, &this->gameTimeResidual);
  filea = this->userCmds;
  v7 = 32;
  do
  {
    v4 = (usercmd_t *)filea;
    v5 = 256;
    do
    {
      idAsyncClient::ReadDemoUsercmd(this, file, v4);
      v4 += 32;
      --v5;
    }
    while ( v5 );
    filea = (usercmd_t (*)[32])((char *)filea + 40);
    --v7;
  }
  while ( v7 );
  idMsgChannel::Init(&this->channel, this->serverAddress, this->clientId);
  idMsgChannel::Restore(&this->channel, file);
  idAsyncClient::UpdateDemoTime(this, 100);
  return this->gameTime;
}

// FUNC: private: void __thiscall idAsyncClient::WriteAuthInfo(class idBitMsg &,bool)
void __thiscall idAsyncClient::WriteAuthInfo(idAsyncClient *this, idBitMsg *msg, bool disconnect)
{
  const char *CDKey; // edi
  int NumEmails; // eax
  _BYTE *v6; // eax
  const char *v7; // eax
  const char *v8; // eax

  CDKey = idSessionLocal::GetCDKey(&sessLocal);
  idBitMsg::WriteBits(msg, 131136, 32);
  if ( idAsyncNetwork::server.active )
  {
    idBitMsg::WriteBits(msg, 0, 8);
    NumEmails = idDeclPDA::GetNumEmails((idDeclPDA *)&idAsyncNetwork::server);
    idBitMsg::WriteBits(msg, NumEmails, -16);
  }
  else if ( disconnect )
  {
    idBitMsg::WriteBits(msg, 2, 8);
  }
  else
  {
    idBitMsg::WriteBits(msg, 1, 8);
    idBitMsg::WriteNetadr(msg, this->serverAddress);
  }
  v6 = (_BYTE *)((int (__thiscall *)(idCVarSystem *))cvarSystem->GetCVarString)(cvarSystem);
  idBitMsg::WriteBits(msg, *v6 != 0, 8);
  idBitMsg::WriteString(msg, CDKey, -1);
  v7 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->GetCVarString)(
                       cvarSystem,
                       "ui_name",
                       -1);
  idBitMsg::WriteString(msg, v7, (int)"com_guid");
  v8 = cvarSystem->GetCVarString(cvarSystem, "ui_clan");
  idBitMsg::WriteString(msg, v8, -1);
}

// FUNC: public: void __thiscall idAsyncClient::SendClientHeartbeat(bool,bool)
void __thiscall idAsyncClient::SendClientHeartbeat(idAsyncClient *this, bool disconnect, bool force)
{
  int realTime; // edx
  netadr_t v5; // [esp-14h] [ebp-404Ch]
  idBitMsg msg; // [esp+8h] [ebp-4030h] BYREF
  netadr_t result; // [esp+2Ch] [ebp-400Ch] BYREF
  char v8[16384]; // [esp+38h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  if ( (this->realTime >= this->nextHeartbeatTime || disconnect || force)
    && !idAsyncNetwork::LANServer.internalVar->integerValue )
  {
    if ( idAsyncClient::InitPort(this) )
    {
      realTime = this->realTime;
      msg.readData = (const unsigned __int8 *)v8;
      this->nextHeartbeatTime = realTime + 540000;
      msg.writeData = (unsigned __int8 *)v8;
      msg.maxSize = 0x4000;
      msg.numValueOverflows = 0;
      idBitMsg::WriteBits(&msg, -1, -16);
      idBitMsg::WriteString(&msg, "clHtbt", -1);
      idAsyncClient::WriteAuthInfo(this, &msg, disconnect);
      v5 = *idAsyncNetwork::GetMasterAddress(&result);
      idPort::SendPacket(&this->clientPort, v5, msg.writeData, msg.curSize);
    }
  }
}

// FUNC: public: void __thiscall idAsyncClient::DisconnectFromServer(void)
void __thiscall idAsyncClient::DisconnectFromServer(idAsyncClient *this)
{
  int clientNum; // eax
  char *v3; // ecx
  idBitMsg msg; // [esp+4h] [ebp-4024h] BYREF
  char v5[16384]; // [esp+28h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  if ( this->clientState >= CS_CONNECTED )
  {
    game->ResetRconGuiStatus(game);
    fileSystem->ClearPureChecksums(fileSystem);
    msg.readData = (const unsigned __int8 *)v5;
    msg.writeData = (unsigned __int8 *)v5;
    msg.maxSize = 0x4000;
    msg.numValueOverflows = 0;
    idBitMsg::WriteBits(&msg, 3, 8);
    idBitMsg::WriteString(&msg, "disconnect", -1);
    if ( !idMsgChannel::SendReliableMessage(&this->channel, &msg) )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "client->server reliable messages overflow\n");
    idAsyncClient::SendEmptyToServer(this, 1, 0);
    idAsyncClient::SendEmptyToServer(this, 1, 0);
    idAsyncClient::SendEmptyToServer(this, 1, 0);
    idAsyncClient::SendClientHeartbeat(this, 1, 0);
  }
  idMsgChannel::Shutdown(&this->channel);
  clientNum = this->clientNum;
  this->clientState = CS_DISCONNECTED;
  this->clientPredictTime = 0;
  this->active = 0;
  v3 = this->guids[clientNum];
  *(_DWORD *)v3 = 0;
  *((_DWORD *)v3 + 1) = 0;
  *((_DWORD *)v3 + 2) = 0;
}

// FUNC: private: void __thiscall idAsyncClient::SendUserInfoToServer(void)
void __thiscall idAsyncClient::SendUserInfoToServer(idAsyncClient *this)
{
  bool v2; // cc
  idDict *v3; // eax
  idDict dict; // [esp+10h] [ebp-405Ch] BYREF
  idBitMsg msg; // [esp+3Ch] [ebp-4030h] BYREF
  char v6[16384]; // [esp+60h] [ebp-400Ch] BYREF
  int v7; // [esp+4068h] [ebp-4h]

  idBitMsg::idBitMsg(&msg);
  dict.args.list = 0;
  dict.args.num = 0;
  dict.args.size = 0;
  v7 = 0;
  idHashIndex::Init(&dict.argHash, 1024, 1024);
  LOBYTE(v7) = 1;
  dict.args.granularity = 16;
  dict.argHash.granularity = 16;
  idHashIndex::Free(&dict.argHash);
  dict.argHash.hashSize = 128;
  dict.argHash.indexSize = 16;
  v2 = this->clientState < CS_CONNECTED;
  v7 = 2;
  if ( v2 )
  {
    v7 = 4;
    idDict::Clear(&dict);
    LOBYTE(v7) = 3;
  }
  else
  {
    v3 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 512);
    idDict::operator=(&dict, v3);
    msg.writeData = (unsigned __int8 *)v6;
    msg.readData = (const unsigned __int8 *)v6;
    msg.maxSize = 0x4000;
    msg.numValueOverflows = 0;
    idBitMsg::WriteBits(&msg, 1, 8);
    idBitMsg::WriteBits(&msg, this->clientUserDictSequence, 32);
    idBitMsg::WriteDeltaDict(&msg, &dict, &sessLocal.mapSpawnData.userInfo[this->clientNum]);
    ++this->clientUserDictSequence;
    if ( !idMsgChannel::SendReliableMessage(&this->channel, &msg) )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "client->server reliable messages overflow\n");
    idDict::operator=(&sessLocal.mapSpawnData.userInfo[this->clientNum], &dict);
    v7 = 6;
    idDict::Clear(&dict);
    LOBYTE(v7) = 5;
  }
  idHashIndex::Free(&dict.argHash);
  v7 = -1;
  if ( dict.args.list )
    Memory::Free(dict.args.list);
}

// FUNC: private: void __thiscall idAsyncClient::ProcessUnreliableServerMessage(class idBitMsg const &)
void __thiscall idAsyncClient::ProcessUnreliableServerMessage(idAsyncClient *this, idBitMsg *msg)
{
  idBitMsg *v3; // ebx
  int Bits; // edi
  unsigned __int8 v5; // al
  int v6; // eax
  int v7; // ebp
  const idKeyValue *Key; // eax
  const char *data; // eax
  bool v10; // bl
  idUserInterface *v11; // eax
  idSession_vtbl *v12; // esi
  int v13; // eax
  int v14; // eax
  __int16 v15; // ax
  int v16; // edi
  unsigned int v17; // ebp
  unsigned __int8 v18; // al
  int v19; // ecx
  int v20; // edi
  char *v21; // ebx
  int v22; // eax
  char *v23; // eax
  int gameTime; // eax
  int snapshotGameTime; // ebp
  int snapshotGameFrame; // eax
  int gameTimeResidual; // edx
  int clientPredictTime; // eax
  int integerValue; // ecx
  int clientPrediction; // eax
  int v31; // ecx
  int v32; // eax
  int clientTime; // edx
  int v34; // eax
  unsigned int i; // [esp+1Ch] [ebp-50h]
  int numClients; // [esp+20h] [ebp-4Ch]
  usercmd_t *last; // [esp+24h] [ebp-48h]
  int numUsercmds; // [esp+28h] [ebp-44h]
  int aheadOfServer; // [esp+2Ch] [ebp-40h]
  int numDuplicatedUsercmds; // [esp+30h] [ebp-3Ch]
  idDict serverSI; // [esp+34h] [ebp-38h] BYREF
  int v42; // [esp+68h] [ebp-4h]
  const idBitMsg *msga; // [esp+70h] [ebp+4h]
  const idBitMsg *msgb; // [esp+70h] [ebp+4h]

  serverSI.args.list = 0;
  serverSI.args.num = 0;
  serverSI.args.size = 0;
  v42 = 0;
  idHashIndex::Init(&serverSI.argHash, 1024, 1024);
  LOBYTE(v42) = 1;
  serverSI.args.granularity = 16;
  serverSI.argHash.granularity = 16;
  idHashIndex::Free(&serverSI.argHash);
  serverSI.argHash.hashSize = 128;
  serverSI.argHash.indexSize = 16;
  v3 = msg;
  v42 = 2;
  Bits = idBitMsg::ReadBits(msg, 32);
  v5 = idBitMsg::ReadBits(msg, 8);
  switch ( v5 )
  {
    case 0u:
      if ( idAsyncNetwork::verbose.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "received empty message from server\n");
      break;
    case 1u:
      if ( idAsyncNetwork::verbose.internalVar->integerValue == 2 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "received ping message from server\n");
      v6 = idBitMsg::ReadBits(msg, 32);
      idAsyncClient::SendPingResponseToServer(this, v6);
      break;
    case 2u:
      v7 = idBitMsg::ReadBits(msg, 32);
      msga = (const idBitMsg *)idBitMsg::ReadBits(msg, 32);
      idBitMsg::ReadDeltaDict(v3, &serverSI, 0);
      Key = idDict::FindKey(&serverSI, "si_pure");
      if ( Key )
        data = Key->value->data;
      else
        data = "0";
      v10 = atoi(data) != 0;
      idAsyncClient::InitGame(this, Bits, v7, (int)msga, &serverSI);
      idMsgChannel::ResetRate(&this->channel);
      if ( idAsyncNetwork::verbose.internalVar->integerValue )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "received gameinit, gameInitId = %d, gameFrame = %d, gameTime = %d\n",
          this->gameInitId,
          this->gameFrame,
          this->gameTime);
      soundSystem->SetMute(soundSystem, 1);
      if ( v10 )
      {
        v11 = uiManager->FindGui(uiManager, "guis/netmenu.gui", 1, 0, 1);
        this->guiNetMenu = v11;
        session->SetGUI(session, v11, idAsyncClient::HandleGuiCommand);
        v12 = session->__vftable;
        v13 = (*(int (__thiscall **)(netadrtype_t, const char *, int, _DWORD, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                common.type,
                "#str_104318",
                -1,
                0,
                "pure_abort",
                0,
                0);
        v14 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                common.type,
                "#str_104317",
                -1,
                v13);
        ((void (__thiscall *)(idSession *, int, int))v12->MessageBoxA)(session, 1, v14);
      }
      else
      {
        session->SetGUI(session, 0, 0);
        idSessionLocal::ExecuteMapChange(&sessLocal, 0, 0);
        soundSystem->SetActiveSoundWorld(soundSystem, 1);
      }
      break;
    case 3u:
      numClients = 0;
      if ( Bits == this->gameInitId )
      {
        this->snapshotSequence = idBitMsg::ReadBits(msg, 32);
        this->snapshotGameFrame = idBitMsg::ReadBits(msg, 32);
        this->snapshotGameTime = idBitMsg::ReadBits(msg, 32);
        numDuplicatedUsercmds = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
        v15 = idBitMsg::ReadBits(msg, -16);
        v16 = v15;
        aheadOfServer = v15;
        game->ClientReadSnapshot(
          game,
          this->clientNum,
          this->snapshotSequence,
          this->snapshotGameFrame,
          this->snapshotGameTime,
          numDuplicatedUsercmds,
          v15,
          msg);
        last = 0;
        v17 = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
        i = v17;
        if ( v17 < 0x20 )
        {
          while ( 1 )
          {
            v18 = idBitMsg::ReadBits(v3, 8);
            v19 = v18;
            numUsercmds = v18;
            if ( v18 > 0xAu )
              break;
            v20 = 0;
            if ( v18 )
            {
              do
              {
                v21 = (char *)this + 1280 * (unsigned __int8)(v20 + this->snapshotGameFrame) + 40 * v17;
                idAsyncNetwork::ReadUserCmdDelta(msg, (usercmd_t *)(v21 + 66044), last);
                v22 = v20 + this->snapshotGameFrame;
                ++v20;
                *((_DWORD *)v21 + 16511) = v22;
                last = (usercmd_t *)(v21 + 66044);
                v17 = i;
                *((_DWORD *)v21 + 16514) = 0;
              }
              while ( v20 < numUsercmds );
              v19 = numUsercmds;
              v3 = msg;
            }
            do
            {
              v23 = (char *)this + 1280 * (unsigned __int8)(v19++ + this->snapshotGameFrame) + 40 * v17;
              *((_DWORD *)v23 + 16511) = 0;
              *((_DWORD *)v23 + 16512) = 0;
            }
            while ( v19 < 256 );
            ++numClients;
            v16 = aheadOfServer;
            i = (unsigned __int8)idBitMsg::ReadBits(v3, 8);
            if ( i >= 0x20 )
              goto LABEL_29;
            v17 = i;
          }
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
            common.type,
            "snapshot %d contains too many user commands for client %d",
            this->snapshotSequence,
            v17);
        }
LABEL_29:
        profile_numClients = numClients;
        if ( this->clientState == CS_CONNECTED )
        {
          this->gameTimeResidual = 0;
          this->clientState = CS_INGAME;
          if ( idAsyncNetwork::verbose.internalVar->integerValue )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "received first snapshot, gameInitId = %d, gameFrame %d gameTime %d\n",
              this->gameInitId,
              this->snapshotGameFrame,
              this->snapshotGameTime);
        }
        else
        {
          if ( idAsyncNetwork::debugClient.internalVar->integerValue >= 2 )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "Snapshot: Sequence %d, GameFrame %d, GameTime %d\n",
              this->snapshotSequence,
              this->gameFrame,
              this->gameTime);
          gameTime = this->gameTime;
          snapshotGameTime = this->snapshotGameTime;
          if ( gameTime < snapshotGameTime
            || gameTime > idAsyncNetwork::clientMaxPrediction.internalVar->integerValue + snapshotGameTime )
          {
            snapshotGameFrame = this->snapshotGameFrame;
            gameTimeResidual = this->gameTimeResidual;
            this->gameFrame = snapshotGameFrame;
            msgb = (const idBitMsg *)snapshotGameFrame;
            this->gameTime = snapshotGameTime;
            if ( gameTimeResidual >= -idAsyncNetwork::clientMaxPrediction.internalVar->integerValue )
            {
              if ( gameTimeResidual > idAsyncNetwork::clientMaxPrediction.internalVar->integerValue )
                gameTimeResidual = idAsyncNetwork::clientMaxPrediction.internalVar->integerValue;
            }
            else
            {
              gameTimeResidual = -idAsyncNetwork::clientMaxPrediction.internalVar->integerValue;
            }
            clientPredictTime = this->clientPredictTime;
            this->gameTimeResidual = gameTimeResidual;
            integerValue = -idAsyncNetwork::clientMaxPrediction.internalVar->integerValue;
            if ( clientPredictTime >= integerValue )
            {
              integerValue = idAsyncNetwork::clientMaxPrediction.internalVar->integerValue;
              if ( clientPredictTime <= integerValue )
                integerValue = clientPredictTime;
            }
            this->clientPredictTime = integerValue;
            if ( idAsyncNetwork::debugClient.internalVar->integerValue )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                common.type,
                "   Adjusted GameFrame %d, GameTime %d, Residual %d, Predict %d\n",
                msgb,
                snapshotGameTime,
                gameTimeResidual,
                integerValue);
          }
          this->clientPrediction += (((unsigned int)(v16 - idAsyncNetwork::clientPrediction.internalVar->integerValue) >> 30) & 2)
                                  - 1;
          clientPrediction = this->clientPrediction;
          v31 = idAsyncNetwork::clientPrediction.internalVar->integerValue;
          if ( clientPrediction >= v31 )
          {
            v31 = idAsyncNetwork::clientMaxPrediction.internalVar->integerValue;
            if ( clientPrediction <= v31 )
              v31 = this->clientPrediction;
          }
          v32 = this->gameTime - this->snapshotGameTime;
          this->clientPrediction = v31;
          clientTime = this->clientTime;
          this->clientPredictTime += (((unsigned int)(v32 - v31) >> 30) & 2) - (v32 - v31) / 4 - 1;
          v34 = this->clientPredictTime;
          this->lastSnapshotTime = clientTime;
          if ( idAsyncNetwork::debugClient.internalVar->integerValue >= 2 )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "   Predict %d\n",
              v34);
          if ( idAsyncNetwork::verbose.internalVar->integerValue == 2 )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "received snapshot, gameInitId = %d, gameFrame = %d, gameTime = %d\n",
              this->gameInitId,
              this->gameFrame,
              this->gameTime);
          if ( numDuplicatedUsercmds && idAsyncNetwork::verbose.internalVar->integerValue == 2 )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "server duplicated %d user commands before snapshot %d\n",
              numDuplicatedUsercmds,
              this->snapshotGameFrame);
        }
      }
      else if ( idAsyncNetwork::verbose.internalVar->integerValue )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "ignoring snapshot with != gameInitId\n");
      }
      break;
    default:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "unknown unreliable server message %d\n",
        v5);
      break;
  }
  v42 = 4;
  idDict::Clear(&serverSI);
  LOBYTE(v42) = 3;
  idHashIndex::Free(&serverSI.argHash);
  v42 = -1;
  if ( serverSI.args.list )
    Memory::Free(serverSI.args.list);
}

// FUNC: private: void __thiscall idAsyncClient::ProcessConnectResponseMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessConnectResponseMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  clientState_t clientState; // eax
  bool v5; // cc
  idKeyValue *list; // eax
  bool v7; // zf
  netadr_t *p_serverAddress; // ebp
  int v9; // esi
  const char *v10; // eax
  int v11; // ebp
  const char *v12; // eax
  int Bits; // ebx
  int v15; // ebp
  int integerValue; // eax
  const char *v17; // [esp-4h] [ebp-4Ch]
  idDict serverSI; // [esp+10h] [ebp-38h] BYREF
  int v19; // [esp+44h] [ebp-4h]
  const idBitMsg *msga; // [esp+58h] [ebp+10h]

  serverSI.args.list = 0;
  serverSI.args.num = 0;
  serverSI.args.size = 0;
  v19 = 0;
  idHashIndex::Init(&serverSI.argHash, 1024, 1024);
  LOBYTE(v19) = 1;
  serverSI.args.granularity = 16;
  serverSI.argHash.granularity = 16;
  idHashIndex::Free(&serverSI.argHash);
  serverSI.argHash.hashSize = 128;
  serverSI.argHash.indexSize = 16;
  clientState = this->clientState;
  v5 = this->clientState < CS_CONNECTED;
  v19 = 2;
  if ( v5 )
  {
    if ( clientState == CS_CONNECTING )
    {
      p_serverAddress = &this->serverAddress;
      if ( Sys_CompareNetAdrBase(from, this->serverAddress) )
      {
        v11 = *(_DWORD *)common.type;
        v12 = Sys_NetAdrToString(from);
        (*(void (**)(netadrtype_t, const char *, ...))(v11 + 124))(
          common.type,
          "received connect response from %s\n",
          v12);
        idMsgChannel::Init(&this->channel, from, this->clientId);
        this->clientNum = idBitMsg::ReadBits(msg, 32);
        this->clientState = CS_CONNECTED;
        this->lastPacketTime = -9999;
        Bits = idBitMsg::ReadBits(msg, 32);
        v15 = idBitMsg::ReadBits(msg, 32);
        msga = (const idBitMsg *)idBitMsg::ReadBits(msg, 32);
        idBitMsg::ReadDeltaDict(msg, &serverSI, 0);
        idAsyncClient::InitGame(this, Bits, v15, (int)msga, &serverSI);
        idSessionLocal::ExecuteMapChange(&sessLocal, 0, 0);
        integerValue = this->clientTime - this->lastConnectTime;
        if ( integerValue >= 0 )
        {
          if ( integerValue > idAsyncNetwork::clientMaxPrediction.internalVar->integerValue )
            integerValue = idAsyncNetwork::clientMaxPrediction.internalVar->integerValue;
        }
        else
        {
          integerValue = 0;
        }
        this->clientPrediction = integerValue;
        this->clientPredictTime = integerValue;
        soundSystem->SetActiveSoundWorld(soundSystem, 1);
        v19 = 10;
        idDict::Clear(&serverSI);
        LOBYTE(v19) = 9;
      }
      else
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "Connect response from a different server.\n");
        v9 = *(_DWORD *)common.type;
        v17 = Sys_NetAdrToString(*p_serverAddress);
        v10 = Sys_NetAdrToString(from);
        (*(void (**)(netadrtype_t, const char *, ...))(v9 + 124))(common.type, "%s should have been %s\n", v10, v17);
        v19 = 8;
        idDict::Clear(&serverSI);
        LOBYTE(v19) = 7;
      }
      idHashIndex::Free(&serverSI.argHash);
      list = serverSI.args.list;
      v7 = serverSI.args.list == 0;
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "Connect response packet while not connecting.\n");
      v19 = 6;
      idDict::Clear(&serverSI);
      LOBYTE(v19) = 5;
      idHashIndex::Free(&serverSI.argHash);
      list = serverSI.args.list;
      v7 = serverSI.args.list == 0;
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Duplicate connect received.\n");
    v19 = 4;
    idDict::Clear(&serverSI);
    LOBYTE(v19) = 3;
    idHashIndex::Free(&serverSI.argHash);
    list = serverSI.args.list;
    v7 = serverSI.args.list == 0;
  }
  v19 = -1;
  if ( !v7 )
    Memory::Free(list);
}

// FUNC: public: bool __thiscall idAsyncClient::SendClientAuthCheck(void)
char __thiscall idAsyncClient::SendClientAuthCheck(idAsyncClient *this)
{
  char inited; // al
  netadr_t v3; // [esp-14h] [ebp-4048h]
  idBitMsg msg; // [esp+4h] [ebp-4030h] BYREF
  netadr_t result; // [esp+28h] [ebp-400Ch] BYREF
  char v6[16384]; // [esp+34h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  inited = idAsyncClient::InitPort(this);
  if ( inited )
  {
    msg.readData = (const unsigned __int8 *)v6;
    msg.writeData = (unsigned __int8 *)v6;
    msg.maxSize = 0x4000;
    msg.numValueOverflows = 0;
    idBitMsg::WriteBits(&msg, -1, -16);
    idBitMsg::WriteString(&msg, "clAuth", -1);
    idAsyncClient::WriteAuthInfo(this, &msg, 0);
    v3 = *idAsyncNetwork::GetMasterAddress(&result);
    idPort::SendPacket(&this->clientPort, v3, msg.writeData, msg.curSize);
    this->nextHeartbeatTime = this->realTime + 540000;
    return 1;
  }
  return inited;
}

// FUNC: private: bool __thiscall idAsyncClient::ValidatePureServerChecksums(struct netadr_t,class idBitMsg const &)
char __thiscall idAsyncClient::ValidatePureServerChecksums(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  idAsyncClient *v3; // ebp
  int v4; // ebx
  int v5; // esi
  int Bits; // eax
  int v7; // esi
  __int32 v8; // eax
  __int32 v9; // eax
  int v11; // esi
  const char *v12; // eax
  int v13; // eax
  int *v14; // eax
  int *v15; // ebp
  const char *v16; // eax
  const char *v17; // esi
  int v18; // edi
  char v19; // cl
  int v20; // eax
  char *v21; // edx
  bool v22; // zf
  const char *v23; // eax
  const char *v24; // esi
  unsigned int v25; // eax
  int v26; // edi
  int v27; // eax
  char *data; // edx
  const char *v29; // ecx
  char v30; // al
  const char *v31; // eax
  const char *v32; // eax
  const char *v33; // esi
  int v34; // edi
  char v35; // cl
  int i; // eax
  char *v37; // edx
  const char *v38; // eax
  const char *v39; // eax
  const char *v40; // esi
  int v41; // edi
  char v42; // cl
  int j; // eax
  char *v44; // edx
  idSession_vtbl *v45; // edi
  char *v46; // esi
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int *v50; // esi
  int v51; // [esp+38h] [ebp-4D98h]
  int v52; // [esp+3Ch] [ebp-4D94h]
  int gamePakChecksum; // [esp+50h] [ebp-4D80h] BYREF
  idStr v54; // [esp+54h] [ebp-4D7Ch] BYREF
  int v55; // [esp+74h] [ebp-4D5Ch]
  idStr v56; // [esp+78h] [ebp-4D58h] BYREF
  idAsyncClient *v57; // [esp+98h] [ebp-4D38h]
  idBitMsg v58; // [esp+9Ch] [ebp-4D34h] BYREF
  int checksums[128]; // [esp+C0h] [ebp-4D10h] BYREF
  int v60[128]; // [esp+2C0h] [ebp-4B10h] BYREF
  idCmdArgs v61; // [esp+4C0h] [ebp-4910h] BYREF
  char v62[16384]; // [esp+DC4h] [ebp-400Ch] BYREF
  int v63; // [esp+4DCCh] [ebp-4h]

  v3 = this;
  v57 = this;
  idBitMsg::idBitMsg(&v58);
  v4 = 0;
  v5 = 0;
  do
  {
    Bits = idBitMsg::ReadBits(msg, 32);
    v60[v5++] = Bits;
    if ( v5 >= 128 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "MAX_PURE_PAKS ( %d ) exceeded in idAsyncClient::ProcessPureMessage\n",
        128);
      return 0;
    }
  }
  while ( Bits );
  v60[v5] = 0;
  v7 = idBitMsg::ReadBits(msg, 32);
  v8 = fileSystem->SetPureServerChecksums(fileSystem, v60, v7, checksums, &gamePakChecksum) - 1;
  if ( v8 )
  {
    v9 = v8 - 1;
    if ( v9 )
    {
      if ( v9 != 1 )
        return 1;
      v11 = *(_DWORD *)common.type;
      v12 = Sys_NetAdrToString(from);
      v13 = (*(int (__thiscall **)(netadrtype_t, const char *, int, const char *))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107211",
              -1,
              v12);
      (*(void (__cdecl **)(netadrtype_t, int))(v11 + 124))(common.type, v13);
      ((void (__thiscall *)(idCmdSystem *, _DWORD, const char *, int, int))cmdSystem->BufferCommandText)(
        cmdSystem,
        0,
        "disconnect",
        v51,
        v52);
    }
    else
    {
      v56.len = 0;
      v56.alloced = 20;
      v56.data = v56.baseBuffer;
      v56.baseBuffer[0] = 0;
      v63 = 0;
      v55 = 0;
      if ( checksums[0] )
      {
        v14 = checksums;
        v15 = checksums;
        do
        {
          v16 = va("0x%x ", *v14);
          v17 = v16;
          if ( v16 )
          {
            v18 = strlen(v16) + v56.len;
            if ( v18 + 1 > v56.alloced )
              idStr::ReAllocate(&v56, v18 + 1, 1);
            v19 = *v17;
            v20 = 0;
            if ( *v17 )
            {
              do
              {
                v21 = &v56.data[v20++];
                v21[v56.len] = v19;
                v19 = v17[v20];
              }
              while ( v19 );
              v4 = v55;
            }
            v56.len = v18;
            v56.data[v18] = 0;
          }
          ++v15;
          ++v4;
          v22 = *v15 == 0;
          v55 = v4;
          v14 = v15;
        }
        while ( !v22 );
        v3 = v57;
      }
      if ( idAsyncNetwork::clientDownload.internalVar->integerValue )
      {
        if ( v3->clientState < CS_CONNECTED )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
            common.type,
            "missing %d paks: %s\n",
            v4 + (gamePakChecksum != 0),
            v56.data);
          v48 = gamePakChecksum;
          if ( gamePakChecksum )
          {
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
              common.type,
              "game code pak: 0x%x\n",
              gamePakChecksum);
            v48 = gamePakChecksum;
          }
          idAsyncClient::GetDownloadRequest(v3, checksums, v4, v48);
          v58.writeData = (unsigned __int8 *)v62;
          v58.readData = (const unsigned __int8 *)v62;
          v58.maxSize = 0x4000;
          v58.numValueOverflows = 0;
          idBitMsg::WriteBits(&v58, -1, -16);
          idBitMsg::WriteString(&v58, "downloadRequest", -1);
          idBitMsg::WriteBits(&v58, v3->serverChallenge, 32);
          idBitMsg::WriteBits(&v58, v3->clientId, -16);
          idBitMsg::WriteBits(&v58, v3->dlRequest, 32);
          idBitMsg::WriteBits(&v58, gamePakChecksum, 32);
          v49 = checksums[0];
          if ( checksums[0] )
          {
            v50 = checksums;
            do
            {
              idBitMsg::WriteBits(&v58, v49, 32);
              v49 = v50[1];
              ++v50;
            }
            while ( v49 );
          }
          idBitMsg::WriteBits(&v58, 0, 32);
          idPort::SendPacket(&v3->clientPort, from, v58.writeData, v58.curSize);
        }
        else
        {
          cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "reconnect");
        }
      }
      else
      {
        Sys_NetAdrToString(from);
        v23 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                              common.type,
                              "#str_107210",
                              -1);
        v24 = va(v23);
        v54.len = 0;
        v54.alloced = 20;
        v54.data = v54.baseBuffer;
        v54.baseBuffer[0] = 0;
        if ( v24 )
        {
          v25 = (unsigned int)&v24[strlen(v24) + 1];
          v26 = v25 - (_DWORD)(v24 + 1);
          v27 = v25 - (_DWORD)v24;
          if ( v27 > 20 )
            idStr::ReAllocate(&v54, v27, 1);
          data = v54.data;
          v29 = v24;
          do
          {
            v30 = *v29;
            *data++ = *v29++;
          }
          while ( v30 );
          v54.len = v26;
        }
        LOBYTE(v63) = 1;
        if ( v4 > 0 )
        {
          v31 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                                common.type,
                                "#str_106751",
                                -1);
          v32 = va(v31);
          v33 = v32;
          if ( v32 )
          {
            v34 = strlen(v32) + v54.len;
            if ( v34 + 1 > v54.alloced )
              idStr::ReAllocate(&v54, v34 + 1, 1);
            v35 = *v33;
            for ( i = 0; v35; v35 = v33[i] )
            {
              v37 = &v54.data[i++];
              v37[v54.len] = v35;
            }
            v54.len = v34;
            v54.data[v34] = 0;
          }
        }
        if ( gamePakChecksum )
        {
          v38 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                                common.type,
                                "#str_106750",
                                -1);
          v39 = va(v38);
          v40 = v39;
          if ( v39 )
          {
            v41 = strlen(v39) + v54.len;
            if ( v41 + 1 > v54.alloced )
              idStr::ReAllocate(&v54, v41 + 1, 1);
            v42 = *v40;
            for ( j = 0; v42; v42 = v40[j] )
            {
              v44 = &v54.data[j++];
              v44[v54.len] = v42;
            }
            v54.len = v41;
            v54.data[v41] = 0;
          }
        }
        (*(void (__cdecl **)(netadrtype_t, char *))(*(_DWORD *)common.type + 124))(common.type, v54.data);
        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
        v45 = session->__vftable;
        v46 = v54.data;
        v47 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type
                                                                                                  + 168))(
                common.type,
                "#str_106735",
                -1,
                1,
                0,
                0,
                0);
        ((void (__thiscall *)(idSession *, _DWORD, char *, int))v45->MessageBoxA)(session, 0, v46, v47);
        LOBYTE(v63) = 0;
        idStr::FreeData(&v54);
      }
      v63 = -1;
      idStr::FreeData(&v56);
    }
  }
  else
  {
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
    fileSystem->SetRestartChecksums(fileSystem, v60, v7);
    v61.argc = 0;
    idCmdArgs::AppendArg(&v61, "reconnect");
    cmdSystem->SetupReloadEngine(cmdSystem, &v61);
  }
  return 0;
}

// FUNC: private: void __thiscall idAsyncClient::ProcessPureMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessPureMessage(idAsyncClient *this, const netadr_t from, idBitMsg *msg)
{
  int v4; // eax
  int *v5; // esi
  int v6; // [esp+10h] [ebp-4228h] BYREF
  idBitMsg v7; // [esp+14h] [ebp-4224h] BYREF
  int value[128]; // [esp+38h] [ebp-4200h] BYREF
  char v9[16384]; // [esp+238h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v7);
  if ( this->clientState == CS_CONNECTING )
  {
    if ( idAsyncClient::ValidatePureServerChecksums(this, from, msg) )
    {
      fileSystem->GetPureServerChecksums(fileSystem, value, -1, &v6);
      v7.writeData = (unsigned __int8 *)v9;
      v7.readData = (const unsigned __int8 *)v9;
      v7.maxSize = 0x4000;
      v7.numValueOverflows = 0;
      idBitMsg::WriteBits(&v7, -1, -16);
      idBitMsg::WriteString(&v7, "pureClient", -1);
      idBitMsg::WriteBits(&v7, this->serverChallenge, 32);
      idBitMsg::WriteBits(&v7, this->clientId, -16);
      v4 = value[0];
      if ( value[0] )
      {
        v5 = value;
        do
        {
          idBitMsg::WriteBits(&v7, v4, 32);
          v4 = v5[1];
          ++v5;
        }
        while ( v4 );
      }
      idBitMsg::WriteBits(&v7, 0, 32);
      idBitMsg::WriteBits(&v7, v6, 32);
      idPort::SendPacket(&this->clientPort, from, v7.writeData, v7.curSize);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "clientState != CS_CONNECTING, pure msg ignored\n");
  }
}

// FUNC: public: void __thiscall idAsyncClient::Shutdown(void)
void __thiscall idAsyncClient::Shutdown(idAsyncClient *this)
{
  idStr *p_updateMSG; // edi
  pakDlEntry_t *list; // eax
  int *p_checksum; // edi

  p_updateMSG = &this->updateMSG;
  this->guiNetMenu = 0;
  idStr::FreeData(&this->updateMSG);
  p_updateMSG->len = 0;
  p_updateMSG->alloced = 20;
  p_updateMSG->data = p_updateMSG->baseBuffer;
  p_updateMSG->baseBuffer[0] = 0;
  idStr::FreeData(&this->updateURL);
  this->updateURL.len = 0;
  this->updateURL.alloced = 20;
  this->updateURL.data = this->updateURL.baseBuffer;
  this->updateURL.baseBuffer[0] = 0;
  idStr::FreeData(&this->updateFile);
  this->updateFile.len = 0;
  this->updateFile.alloced = 20;
  this->updateFile.data = this->updateFile.baseBuffer;
  this->updateFile.baseBuffer[0] = 0;
  idStr::FreeData(&this->updateFallback);
  this->updateFallback.len = 0;
  this->updateFallback.alloced = 20;
  this->updateFallback.data = this->updateFallback.baseBuffer;
  this->updateFallback.baseBuffer[0] = 0;
  idStr::FreeData(&this->backgroundDownload.url.url);
  this->backgroundDownload.url.url.len = 0;
  this->backgroundDownload.url.url.alloced = 20;
  this->backgroundDownload.url.url.data = this->backgroundDownload.url.url.baseBuffer;
  this->backgroundDownload.url.url.baseBuffer[0] = 0;
  list = this->dlList.list;
  if ( list )
  {
    p_checksum = &list[-1].checksum;
    `eh vector destructor iterator'(
      list,
      0x48u,
      list[-1].checksum,
      (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
    Memory::Free(p_checksum);
  }
  this->dlList.list = 0;
  this->dlList.num = 0;
  this->dlList.size = 0;
}

// FUNC: private: void __thiscall idAsyncClient::ProcessReliableMessagePure(class idBitMsg const &)
void __thiscall idAsyncClient::ProcessReliableMessagePure(idAsyncClient *this, idBitMsg *msg)
{
  int Bits; // eax
  int v4; // eax
  int *v5; // esi
  int v6; // [esp+14h] [ebp-4228h] BYREF
  idBitMsg v7; // [esp+18h] [ebp-4224h] BYREF
  int value[128]; // [esp+3Ch] [ebp-4200h] BYREF
  char v9[16384]; // [esp+23Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v7);
  session->SetGUI(session, 0, 0);
  if ( idAsyncNetwork::demo.demoState == DEMO_RECORDING )
    idDemo::Stop(&idAsyncNetwork::demo);
  Bits = idBitMsg::ReadBits(msg, 32);
  if ( Bits == this->gameInitId )
  {
    if ( idAsyncClient::ValidatePureServerChecksums(this, this->serverAddress, msg) )
    {
      if ( idAsyncNetwork::verbose.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "received new pure server info. ExecuteMapChange and report back\n");
      idSessionLocal::ExecuteMapChange(&sessLocal, 1, 0);
      fileSystem->GetPureServerChecksums(fileSystem, value, -1, &v6);
      v7.readData = (const unsigned __int8 *)v9;
      v7.writeData = (unsigned __int8 *)v9;
      v7.maxSize = 0x4000;
      v7.numValueOverflows = 0;
      idBitMsg::WriteBits(&v7, 0, 8);
      idBitMsg::WriteBits(&v7, this->gameInitId, 32);
      v4 = value[0];
      if ( value[0] )
      {
        v5 = value;
        do
        {
          idBitMsg::WriteBits(&v7, v4, 32);
          v4 = v5[1];
          ++v5;
        }
        while ( v4 );
      }
      idBitMsg::WriteBits(&v7, 0, 32);
      idBitMsg::WriteBits(&v7, v6, 32);
      if ( !idMsgChannel::SendReliableMessage(&this->channel, &v7) )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "client->server reliable messages overflow\n");
      soundSystem->SetActiveSoundWorld(soundSystem, 1);
    }
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "ignoring pure server checksum from an outdated gameInitId (%d)\n",
      Bits);
  }
}

// FUNC: private: void __thiscall idAsyncClient::ProcessReliableServerMessages(void)
void __thiscall idAsyncClient::ProcessReliableServerMessages(idAsyncClient *this)
{
  idAsyncClient *v1; // ebp
  unsigned int v2; // ecx
  int i; // esi
  __int64 v4; // rax
  int v5; // esi
  idDict *v6; // edi
  bool v7; // bl
  int v8; // ebp
  __int64 v9; // rax
  idGame *v10; // ecx
  int v11; // esi
  const char *v12; // eax
  idSession_vtbl *v13; // esi
  int v14; // eax
  idDict *v15; // esi
  const idKeyValue *Key; // eax
  const char *data; // eax
  idCmdSystem_vtbl *v18; // edi
  char *v19; // eax
  int v20; // esi
  rvServerScan *p_serverList; // ebp
  unsigned int v22; // esi
  char *v23; // edi
  idGame_vtbl *v24; // edi
  BOOL v25; // eax
  char v26; // [esp+13h] [ebp-4829h]
  idBitMsg msg; // [esp+18h] [ebp-4824h] BYREF
  char dest[16]; // [esp+3Ch] [ebp-4800h] BYREF
  char v30[1008]; // [esp+4Ch] [ebp-47F0h] BYREF
  char buffer[1024]; // [esp+43Ch] [ebp-4400h] BYREF
  char v32[16384]; // [esp+83Ch] [ebp-4000h] BYREF

  v1 = this;
  idBitMsg::idBitMsg(&msg);
  msg.readData = (const unsigned __int8 *)v32;
  v2 = com_frameTime;
  v26 = 0;
  msg.writeData = (unsigned __int8 *)v32;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  for ( i = 0; i < 32; ++i )
  {
    v4 = (int)(sessLocal.mapSpawnData.mapLastUIRequestTime[i] - v2);
    if ( (int)((HIDWORD(v4) ^ v4) - HIDWORD(v4)) > 1000 && !sessLocal.mapSpawnData.mapLastUIInitialRequest[i] )
    {
      idBitMsg::WriteBits(&msg, 7, 8);
      idBitMsg::WriteBits(&msg, i, 8);
      v2 = com_frameTime;
      sessLocal.mapSpawnData.mapLastUIRequestTime[i] = com_frameTime + 1000;
    }
  }
  if ( 8 * msg.curSize != (-msg.writeBit & 7) && !idMsgChannel::SendReliableMessage(&v1->channel, &msg) )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "client->server reliable messages overflow\n");
  msg.writeData = (unsigned __int8 *)v32;
  msg.readData = (const unsigned __int8 *)v32;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  while ( idMsgChannel::GetReliableMessage(&v1->channel, &msg) )
  {
    switch ( (unsigned __int8)idBitMsg::ReadBits(&msg, 8) )
    {
      case 0u:
        idAsyncClient::ProcessReliableMessagePure(v1, &msg);
        continue;
      case 1u:
        if ( idAsyncNetwork::verbose.internalVar->integerValue )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "got MESSAGE_RELOAD from server\n");
        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "reconnect\n");
        continue;
      case 2u:
        v5 = (unsigned __int8)idBitMsg::ReadBits(&msg, 8);
        v6 = &sessLocal.mapSpawnData.userInfo[v5];
        v7 = idBitMsg::ReadBits(&msg, 1) != 0;
        v8 = idBitMsg::ReadBits(&msg, 32);
        if ( v7 )
          idBitMsg::ReadDeltaDict(&msg, v6, v6);
        else
          idBitMsg::ReadDeltaDict(&msg, v6, 0);
        if ( v5 == this->clientNum )
          goto LABEL_23;
        if ( v8 == idDict::Checksum(v6) )
        {
          if ( v5 == this->clientNum )
          {
LABEL_23:
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
              common.type,
              "local user info modified by server\n");
            cvarSystem->SetCVarsFromDict(cvarSystem, v6);
            cvarSystem->ClearModifiedFlags(cvarSystem, 512);
          }
          v10 = game;
          sessLocal.mapSpawnData.mapLastUIInitialRequest[v5] = 1;
          v10->SetUserInfo(v10, v5, v6, 1);
          break;
        }
        v9 = (int)(sessLocal.mapSpawnData.mapLastUIRequestTime[v5] - com_frameTime);
        if ( (int)((HIDWORD(v9) ^ v9) - HIDWORD(v9)) > 1000 || sessLocal.mapSpawnData.mapLastUIInitialRequest[v5] )
        {
          sessLocal.mapSpawnData.mapLastUIRequestTime[v5] = com_frameTime - 1000;
          sessLocal.mapSpawnData.mapLastUIInitialRequest[v5] = 0;
        }
        break;
      case 3u:
        idBitMsg::ReadDeltaDict(&msg, &sessLocal.mapSpawnData.syncedCVars, &sessLocal.mapSpawnData.syncedCVars);
        cvarSystem->SetCVarsFromDict(cvarSystem, &sessLocal.mapSpawnData.syncedCVars);
        if ( !idAsyncNetwork::allowCheats.internalVar->integerValue )
          cvarSystem->ResetFlaggedVariables(cvarSystem, 0x2000);
        continue;
      case 4u:
        idBitMsg::ReadString(&msg, buffer, 1024);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s\n", buffer);
        continue;
      case 5u:
        v11 = idBitMsg::ReadBits(&msg, 32);
        idBitMsg::ReadString(&msg, dest, 1024);
        v12 = (const char *)(*(int (__thiscall **)(netadrtype_t, char *, int))(*(_DWORD *)common.type + 168))(
                              common.type,
                              dest,
                              -1);
        idStr::snPrintf(dest, 1023, "%s", v12);
        if ( v11 == v1->clientNum )
        {
          session->Stop(session);
          v13 = session->__vftable;
          v14 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                  common.type,
                  "#str_104319",
                  -1,
                  1,
                  0,
                  0,
                  0);
          ((void (__thiscall *)(idSession *, _DWORD, char *, int))v13->MessageBoxA)(session, 0, v30, v14);
          session->StartMenu(session, &entityFilter);
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "client %d %s\n",
            v11,
            dest);
          v15 = &sessLocal.mapSpawnData.userInfo[v11];
          Key = idDict::FindKey(v15, "ui_name");
          if ( Key )
            data = Key->value->data;
          else
            data = &entityFilter;
          v18 = cmdSystem->__vftable;
          v19 = va("addChatLine \"%s^0 %s\"", data, dest);
          v18->BufferCommandText(cmdSystem, CMD_EXEC_NOW, v19);
          idDict::Clear(v15);
        }
        continue;
      case 6u:
        v20 = idBitMsg::ReadBits(&msg, 32);
        if ( !game->ClientApplySnapshot(game, v1->clientNum, v20) )
        {
          session->Stop(session);
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
            common.type,
            "couldn't apply snapshot %d",
            v20);
        }
        continue;
      case 8u:
        idAsyncClient::SendUserInfoToServer(v1);
        game->SetUserInfo(game, v1->clientNum, &sessLocal.mapSpawnData.userInfo[v1->clientNum], 1);
        cvarSystem->ClearModifiedFlags(cvarSystem, 512);
        continue;
      case 9u:
        if ( msg.curSize - msg.readCount <= 0 )
          continue;
        p_serverList = &v1->serverList;
        do
        {
          v22 = (unsigned __int8)idBitMsg::ReadBits(&msg, 8);
          v23 = (char *)this + 12 * v22;
          idBitMsg::ReadString(&msg, v23 + 395536, 12);
          v23[395547] = 0;
          v24 = game->__vftable;
          LOBYTE(v25) = rvServerScan::IsAFriend(p_serverList, v22);
          v24->SetFriend(game, v22, v25);
        }
        while ( msg.curSize - msg.readCount > 0 );
        break;
      case 0xAu:
        v1->clientUserDictSequence = idBitMsg::ReadBits(&msg, 32);
        if ( !v26 )
        {
          idDict::Clear(&sessLocal.mapSpawnData.userInfo[v1->clientNum]);
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "re-send requested!\n");
          idAsyncClient::SendUserInfoToServer(v1);
          v26 = 1;
        }
        continue;
      default:
        game->ClientProcessReliableMessage(game, v1->clientNum, &msg);
        continue;
    }
    v1 = this;
  }
}

// FUNC: private: void __thiscall idAsyncClient::ProcessInfoResponseMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessInfoResponseMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  char v3; // bl
  int Bits; // eax
  int v5; // esi
  const char *v6; // eax
  int v7; // edi
  const char *v8; // eax
  unsigned int i; // edi
  __int16 v10; // ax
  int v11; // eax
  int active; // esi
  const idKeyValue *Key; // eax
  const char *data; // eax
  int v15; // edi
  const char *v16; // eax
  int v17; // [esp-10h] [ebp-940h]
  int v18; // [esp-Ch] [ebp-93Ch]
  const char *v19; // [esp-4h] [ebp-934h]
  networkServer_t serverInfo; // [esp+14h] [ebp-91Ch] BYREF
  int v22; // [esp+92Ch] [ebp-4h]

  networkServer_t::networkServer_t(&serverInfo);
  v3 = 0;
  v22 = 0;
  if ( from.type == NA_LOOPBACK || cvarSystem->GetCVarBool(cvarSystem, "developer") )
    v3 = 1;
  serverInfo.adr = from;
  serverInfo.clients = 0;
  serverInfo.challenge = idBitMsg::ReadBits(msg, 32);
  Bits = idBitMsg::ReadBits(msg, 32);
  if ( Bits == 131136 )
  {
    idBitMsg::ReadDeltaDict(msg, &serverInfo.serverInfo, 0);
    if ( v3 )
    {
      v7 = *(_DWORD *)common.type;
      v8 = Sys_NetAdrToString(serverInfo.adr);
      (*(void (**)(netadrtype_t, const char *, ...))(v7 + 124))(common.type, "server IP = %s\n", v8);
      idDict::Print(&serverInfo.serverInfo);
    }
    for ( i = (unsigned __int8)idBitMsg::ReadBits(msg, 8); i < 0x20; i = (unsigned __int8)idBitMsg::ReadBits(msg, 8) )
    {
      v10 = idBitMsg::ReadBits(msg, -16);
      serverInfo.pings[serverInfo.clients] = v10;
      v11 = idBitMsg::ReadBits(msg, 32);
      serverInfo.rate[serverInfo.clients] = v11;
      idBitMsg::ReadString(msg, serverInfo.nickname[serverInfo.clients], 32);
      idBitMsg::ReadString(msg, serverInfo.clans[serverInfo.clients], 32);
      if ( v3 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "client %2d: %s, ping = %d, rate = %d\n",
          i,
          serverInfo.nickname[serverInfo.clients],
          serverInfo.pings[serverInfo.clients],
          serverInfo.rate[serverInfo.clients]);
      ++serverInfo.clients;
    }
    serverInfo.OSMask = idBitMsg::ReadBits(msg, 32);
    serverInfo.favorite = 0;
    active = rvServerScan::AddActiveServer(&this->serverList, &serverInfo);
    Key = idDict::FindKey(&serverInfo.serverInfo, "si_name");
    if ( Key )
      data = Key->value->data;
    else
      data = &entityFilter;
    v15 = *(_DWORD *)common.type;
    v19 = data;
    v16 = Sys_NetAdrToString(serverInfo.adr);
    (*(void (**)(netadrtype_t, const char *, ...))(v15 + 124))(
      common.type,
      "%d: server %s - protocol %d.%d - %s\n",
      active,
      v16,
      2,
      64,
      v19);
  }
  else
  {
    v5 = *(_DWORD *)common.type;
    v18 = (unsigned __int16)Bits;
    v17 = Bits >> 16;
    v6 = Sys_NetAdrToString(serverInfo.adr);
    (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(
      common.type,
      "server %s ignored - protocol %d.%d, expected %d.%d\n",
      v6,
      v17,
      v18,
      2,
      64);
  }
  v22 = -1;
  networkServer_t::~networkServer_t(&serverInfo);
}

// FUNC: private: void __thiscall idAsyncClient::HandleDownloads(void)
void __usercall idAsyncClient::HandleDownloads(idAsyncClient *this@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  clientUpdateState_t updateState; // eax
  idSession_vtbl *v5; // esi
  int v6; // eax
  int v7; // eax
  char *v8; // esi
  idSession_vtbl *v9; // ebx
  int v10; // eax
  idFile *v11; // eax
  int v12; // eax
  idSession_vtbl *v13; // edi
  char *v14; // eax
  bool v15; // zf
  const char *v16; // esi
  unsigned int v17; // eax
  int v18; // ebx
  int v19; // eax
  _BYTE *v20; // edx
  const char *v21; // ecx
  char v22; // al
  idSession_vtbl *v23; // esi
  int v24; // eax
  int v25; // eax
  idStr *p_dltitle; // ecx
  idSys_vtbl *v27; // esi
  char *v28; // eax
  int v29; // esi
  idSession_vtbl *v30; // edi
  int v31; // eax
  const char *v32; // eax
  char *v33; // eax
  const char *v34; // eax
  const char *v35; // esi
  int v36; // ebx
  _BYTE *v37; // edx
  const char *v38; // ecx
  char v39; // al
  idSession_vtbl *v40; // esi
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // esi
  int v46; // ebx
  idFile *v47; // eax
  pakDlEntry_t *v48; // esi
  const char *v49; // eax
  const char *v50; // eax
  const char *v51; // esi
  unsigned int len; // ebx
  char v53; // cl
  int v54; // eax
  int v55; // edx
  double v56; // st7
  pakDlEntry_t *v57; // edx
  int v58; // eax
  char *v59; // eax
  int v60; // edx
  const char *v61; // esi
  unsigned int v62; // eax
  int v63; // edi
  int v64; // eax
  _BYTE *v65; // edx
  const char *v66; // ecx
  char v67; // al
  int v68; // esi
  void *v69; // ebx
  int v70; // edi
  int v71; // eax
  int v72; // eax
  int v73; // eax
  int v74; // edi
  pakDlEntry_t *v75; // ecx
  int num; // eax
  int v77; // eax
  int v78; // esi
  pakDlEntry_t *list; // eax
  int *p_checksum; // esi
  idSession_vtbl *v81; // esi
  const char *v82; // eax
  char *v83; // eax
  pakDlEntry_t *v84; // eax
  int *v85; // esi
  idSession_vtbl *v86; // esi
  int v87; // eax
  int v88; // eax
  pakDlEntry_t *v89; // eax
  int *v90; // esi
  int v91; // [esp+24h] [ebp-B0h]
  int v92; // [esp+28h] [ebp-ACh]
  int v93; // [esp+2Ch] [ebp-A8h]
  int v94; // [esp+30h] [ebp-A4h]
  int v95; // [esp+34h] [ebp-A0h]
  int v96; // [esp+34h] [ebp-A0h]
  int v97; // [esp+38h] [ebp-9Ch]
  int v98; // [esp+38h] [ebp-9Ch]
  int v99; // [esp+3Ch] [ebp-98h]
  int v100; // [esp+3Ch] [ebp-98h]
  int v102; // [esp+44h] [ebp-90h]
  int v103; // [esp+48h] [ebp-8Ch]
  char *data; // [esp+4Ch] [ebp-88h]
  int pakCount; // [esp+54h] [ebp-80h]
  int numPaksa; // [esp+58h] [ebp-7Ch]
  int numPaks; // [esp+58h] [ebp-7Ch]
  idFile_Permanent *f; // [esp+5Ch] [ebp-78h]
  idFile_Permanent *fa; // [esp+5Ch] [ebp-78h]
  int saveas; // [esp+60h] [ebp-74h]
  int progress_start; // [esp+64h] [ebp-70h]
  idStr dltitle; // [esp+68h] [ebp-6Ch] BYREF
  idStr finalPath; // [esp+88h] [ebp-4Ch] BYREF
  idStr name; // [esp+A8h] [ebp-2Ch] BYREF
  int v115; // [esp+D0h] [ebp-4h]

  updateState = this->updateState;
  if ( updateState == UPDATE_SENT && this->clientTime > this->updateSentTime + 2000 )
  {
    this->updateState = UPDATE_DONE;
    session->StopBox(session);
    if ( this->showUpdateMessage )
    {
      v5 = session->__vftable;
      v6 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type
                                                                                               + 168))(
             common.type,
             "#str_104837",
             -1,
             1,
             0,
             0,
             0);
      v7 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
             common.type,
             "#str_104839",
             -1,
             v6);
      ((void (__thiscall *)(idSession *, _DWORD, int))v5->MessageBoxA)(session, 0, v7);
      this->showUpdateMessage = 0;
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "No update available\n");
    return;
  }
  v102 = a3;
  if ( !this->backgroundDownload.completed )
    return;
  if ( updateState != UPDATE_READY )
  {
    if ( !this->dlList.num )
      return;
    session->StopBox(session);
    pakCount = 1;
    this->currentDlSize = 0;
    while ( 1 )
    {
      if ( *this->dlList.list->url.data )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "start download for %s\n",
          this->dlList.list->url.data);
        v47 = fileSystem->MakeTemporaryFile(fileSystem);
        fa = (idFile_Permanent *)v47;
        if ( !v47 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
            common.type,
            "could not create temporary file");
          list = this->dlList.list;
          if ( list )
          {
            p_checksum = &list[-1].checksum;
            `eh vector destructor iterator'(
              list,
              0x48u,
              list[-1].checksum,
              (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
            Memory::Free(p_checksum);
          }
          this->dlList.list = 0;
          this->dlList.num = 0;
          this->dlList.size = 0;
          return;
        }
        v48 = this->dlList.list;
        this->backgroundDownload.completed = 0;
        this->backgroundDownload.opcode = DLTYPE_URL;
        this->backgroundDownload.f = v47;
        this->backgroundDownload.url.status = DL_WAIT;
        this->backgroundDownload.url.dlnow = 0;
        this->backgroundDownload.url.dltotal = v48->size;
        saveas = v48->url.len;
        if ( v48->url.len + 1 > this->backgroundDownload.url.url.alloced )
          idStr::ReAllocate(&this->backgroundDownload.url.url, saveas + 1, 0);
        qmemcpy(this->backgroundDownload.url.url.data, v48->url.data, saveas);
        this->backgroundDownload.url.url.data[saveas] = 0;
        this->backgroundDownload.url.url.len = saveas;
        ((void (__thiscall *)(idFileSystem *, backgroundDownload_s *, int, int, int, char *))fileSystem->BackgroundDownload)(
          fileSystem,
          &this->backgroundDownload,
          a2,
          v102,
          v103,
          data);
        *(_DWORD *)&dltitle.baseBuffer[4] = 0;
        *(_DWORD *)&dltitle.baseBuffer[12] = 20;
        *(_DWORD *)&dltitle.baseBuffer[8] = &dltitle.baseBuffer[16];
        dltitle.baseBuffer[16] = 0;
        data = this->dlList.list->filename.data;
        v103 = -1;
        v49 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 168))(
                              common.type,
                              "#str_107213");
        sprintf((idStr *)&dltitle.alloced, v49);
        if ( saveas > 1 )
        {
          v50 = va(" (%d/%d)", fa, saveas);
          v51 = v50;
          if ( v50 )
          {
            len = strlen(v50) + dltitle.alloced;
            dltitle.len = len;
            if ( (int)(len + 1) > *(int *)&dltitle.baseBuffer[4] )
              idStr::ReAllocate((idStr *)&dltitle.alloced, len + 1, 1);
            v53 = *v51;
            v54 = 0;
            if ( *v51 )
            {
              do
              {
                v55 = v54 + *(_DWORD *)dltitle.baseBuffer;
                ++v54;
                *(_BYTE *)(v55 + dltitle.alloced) = v53;
                v53 = v51[v54];
              }
              while ( v53 );
              len = dltitle.len;
            }
            dltitle.alloced = len;
            *(_BYTE *)(*(_DWORD *)dltitle.baseBuffer + len) = 0;
          }
        }
        dltitle.len = this->totalDlSize;
        if ( dltitle.len )
        {
          v56 = (double)dltitle.len;
          numPaksa = this->currentDlSize;
          v57 = this->dlList.list;
          v58 = (unsigned __int16)numPaksa;
          BYTE1(v58) = BYTE1(numPaksa) | 0xC;
          dltitle.len = v58;
          dltitle.len = numPaksa + v57->size;
          dltitle.data = (char *)(int)((double)numPaksa * 100.0 / v56);
          v59 = dltitle.data;
          dltitle.len = (int)((double)dltitle.len * 100.0 / v56);
          v60 = dltitle.len;
        }
        else
        {
          v59 = 0;
          v60 = 100;
        }
        session->DownloadProgressBox(
          session,
          &this->backgroundDownload,
          *(const char **)dltitle.baseBuffer,
          (int)v59,
          v60);
        if ( this->backgroundDownload.url.status != DL_DONE )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "download failed: %s",
            this->dlList.list->url.data);
          if ( this->backgroundDownload.url.dlerror[0] )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
              common.type,
              "curl error: %s",
              this->backgroundDownload.url.dlerror);
          v86 = session->__vftable;
          v87 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD))(*(_DWORD *)common.type + 168))(
                  common.type,
                  "#str_107216",
                  -1,
                  1,
                  0);
          v88 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                  common.type,
                  "#str_107215",
                  -1,
                  v87);
          ((void (__thiscall *)(idSession *, _DWORD, int))v86->MessageBoxA)(session, 0, v88);
          v89 = this->dlList.list;
          if ( v89 )
          {
            v90 = &v89[-1].checksum;
            `eh vector destructor iterator'(
              v89,
              0x48u,
              v89[-1].checksum,
              (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
            Memory::Free(v90);
          }
          this->dlList.list = 0;
          this->dlList.num = 0;
          this->dlList.size = 0;
          goto LABEL_95;
        }
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "file downloaded\n");
        v61 = cvarSystem->GetCVarString(cvarSystem, "fs_savepath");
        finalPath.alloced = 0;
        *(_DWORD *)&finalPath.baseBuffer[4] = 20;
        *(_DWORD *)finalPath.baseBuffer = &finalPath.baseBuffer[8];
        finalPath.baseBuffer[8] = 0;
        if ( v61 )
        {
          v62 = (unsigned int)&v61[strlen(v61) + 1];
          v63 = v62 - (_DWORD)(v61 + 1);
          v64 = v62 - (_DWORD)v61;
          if ( v64 > 20 )
            idStr::ReAllocate((idStr *)&finalPath.alloced, v64, 1);
          v65 = *(_BYTE **)finalPath.baseBuffer;
          v66 = v61;
          do
          {
            v67 = *v66;
            *v65++ = *v66++;
          }
          while ( v67 );
          finalPath.alloced = v63;
        }
        idStr::AppendPath((idStr *)&finalPath.alloced, this->dlList.list->filename.data);
        fileSystem->CreateOSPath(fileSystem, *(const char **)finalPath.baseBuffer);
        dltitle.len = (int)fileSystem->OpenExplicitFileWrite(fileSystem, *(_DWORD *)finalPath.baseBuffer);
        v68 = progress_start;
        v69 = Mem_Alloc(0x100000, 0x1Eu);
        (*(void (__thiscall **)(int, _DWORD, int))(*(_DWORD *)progress_start + 40))(progress_start, 0, 1);
        numPaks = (*(int (__thiscall **)(int))(*(_DWORD *)v68 + 28))(v68);
        (*(void (__thiscall **)(int, _DWORD, int))(*(_DWORD *)v68 + 40))(v68, 0, 2);
        for ( ; numPaks; numPaks -= v70 )
        {
          v70 = numPaks;
          if ( numPaks >= 0x100000 )
            v70 = 0x100000;
          v71 = (*(int (__thiscall **)(int, void *, int))(*(_DWORD *)progress_start + 12))(progress_start, v69, v70);
          if ( v71 != v70 )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
              common.type,
              "short read %d of %d in idFileSystem::HandleDownload",
              v71,
              v70);
          v72 = (*(int (__thiscall **)(int, void *, int))(*(_DWORD *)dltitle.len + 16))(dltitle.len, v69, v70);
          if ( v72 != v70 )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
              common.type,
              "short write %d of %d in idFileSystem::HandleDownload",
              v72,
              v70);
        }
        v102 = progress_start;
        ((void (__thiscall *)(idFileSystem *))fileSystem->CloseFile)(fileSystem);
        a2 = progress_start;
        ((void (__thiscall *)(idFileSystem *))fileSystem->CloseFile)(fileSystem);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "saved as %s\n",
          finalPath.data);
        Mem_Free(v69);
        v73 = fileSystem->AddZipFile(fileSystem, this->dlList.list->filename.data);
        v74 = 0;
        if ( !v73 || (v75 = this->dlList.list, v73 != v75->checksum) )
        {
          v81 = session->__vftable;
          v82 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int, int, const char *, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                                common.type,
                                "#str_107214",
                                -1,
                                v73,
                                this->dlList.list->checksum,
                                "Download failed",
                                1,
                                0,
                                0,
                                0);
          v83 = va(v82);
          ((void (__thiscall *)(idSession *, _DWORD, char *, int, int, int, int, int, int, int))v81->MessageBoxA)(
            session,
            0,
            v83,
            v91,
            v92,
            v93,
            v94,
            v96,
            v98,
            v100);
          fileSystem->RemoveFile(fileSystem, this->dlList.list->filename.data, "fs_savepath");
          v84 = this->dlList.list;
          if ( v84 )
          {
            v85 = &v84[-1].checksum;
            `eh vector destructor iterator'(
              v84,
              0x48u,
              v84[-1].checksum,
              (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
            Memory::Free(v85);
          }
          this->dlList.list = 0;
          this->dlList.num = 0;
          this->dlList.size = 0;
          LOBYTE(v115) = 2;
          idStr::FreeData(&finalPath);
LABEL_95:
          p_dltitle = &dltitle;
          goto LABEL_96;
        }
        this->currentDlSize += v75->size;
        LOBYTE(v115) = 2;
        idStr::FreeData(&finalPath);
        num = this->dlList.num;
        ++pakCount;
        if ( num > 0 )
        {
          v77 = num - 1;
          v78 = 0;
          for ( this->dlList.num = v77; v78 < this->dlList.num; ++v74 )
          {
            pakDlEntry_t::operator=(&this->dlList.list[v74].url, (int)&this->dlList.list[v74 + 1]);
            ++v78;
          }
        }
        v115 = -1;
        idStr::FreeData(&dltitle);
      }
      else
      {
        v43 = this->dlList.num;
        if ( v43 > 0 )
        {
          v44 = v43 - 1;
          v45 = 0;
          this->dlList.num = v44;
          if ( v44 > 0 )
          {
            v46 = 0;
            do
            {
              pakDlEntry_t::operator=(&this->dlList.list[v46].url, (int)&this->dlList.list[v46 + 1]);
              ++v45;
              ++v46;
            }
            while ( v45 < this->dlList.num );
          }
        }
      }
      if ( !this->dlList.num )
      {
        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "reconnect\n");
        return;
      }
    }
  }
  session->StopBox(session);
  v8 = this->updateMSG.data;
  v9 = session->__vftable;
  v10 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type
                                                                                                  + 168))(
          common.type,
          "#str_104330",
          -1,
          1,
          "yes",
          0,
          0);
  if ( !*(_BYTE *)((int (__thiscall *)(idSession *, int, char *, int))v9->MessageBoxA)(session, 3, v8, v10) )
  {
LABEL_11:
    this->updateState = UPDATE_DONE;
    return;
  }
  if ( !this->updateDirectDownload )
  {
    sys->OpenURL(sys, this->updateURL.data, 1);
    goto LABEL_11;
  }
  idStr::ExtractFileName(&this->updateURL, &this->updateFile);
  v11 = (idFile *)((int (__thiscall *)(idFileSystem *, char *, const char *, _DWORD, int, int))fileSystem->OpenFileWrite)(
                    fileSystem,
                    this->updateFile.data,
                    "fs_savepath",
                    0,
                    a2,
                    a3);
  this->backgroundDownload.f = v11;
  f = (idFile_Permanent *)v11;
  this->dltotal = 0;
  this->dlnow = 0;
  this->backgroundDownload.completed = 0;
  this->backgroundDownload.opcode = DLTYPE_URL;
  this->backgroundDownload.url.status = DL_WAIT;
  this->backgroundDownload.url.dlnow = 0;
  this->backgroundDownload.url.dltotal = 0;
  dltitle.len = this->updateURL.len;
  if ( dltitle.len + 1 > this->backgroundDownload.url.url.alloced )
    idStr::ReAllocate(&this->backgroundDownload.url.url, dltitle.len + 1, 0);
  v12 = dltitle.len;
  qmemcpy(this->backgroundDownload.url.url.data, this->updateURL.data, dltitle.len);
  this->backgroundDownload.url.url.data[dltitle.len] = 0;
  this->backgroundDownload.url.url.len = v12;
  fileSystem->BackgroundDownload(fileSystem, &this->backgroundDownload);
  this->updateState = UPDATE_DLING;
  idAsyncClient::SendVersionDLUpdate(this, 0);
  v13 = session->__vftable;
  v14 = va("Downloading %s\n", this->updateFile.data);
  v13->DownloadProgressBox(session, &this->backgroundDownload, v14, 0, 100);
  v15 = this->backgroundDownload.url.status == DL_DONE;
  this->updateState = UPDATE_DONE;
  if ( v15 )
  {
    idAsyncClient::SendVersionDLUpdate(this, 1);
    v16 = f->GetFullPath(f);
    name.alloced = 0;
    *(_DWORD *)&name.baseBuffer[4] = 20;
    *(_DWORD *)name.baseBuffer = &name.baseBuffer[8];
    name.baseBuffer[8] = 0;
    if ( v16 )
    {
      v17 = (unsigned int)&v16[strlen(v16) + 1];
      v18 = v17 - (_DWORD)(v16 + 1);
      v19 = v17 - (_DWORD)v16;
      if ( v19 > 20 )
        idStr::ReAllocate((idStr *)&name.alloced, v19, 1);
      v20 = *(_BYTE **)name.baseBuffer;
      v21 = v16;
      do
      {
        v22 = *v21;
        *v20++ = *v21++;
      }
      while ( v22 );
      name.alloced = v18;
    }
    fileSystem->CloseFile(fileSystem, f);
    v23 = session->__vftable;
    v24 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_104332",
            -1,
            1,
            "yes",
            0,
            0);
    v25 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_104331",
            -1,
            v24);
    if ( *(_BYTE *)((int (__thiscall *)(idSession *, int, int))v23->MessageBoxA)(session, 3, v25) )
    {
      if ( this->updateMime )
      {
        v27 = sys->__vftable;
        v28 = va("file://%s", *(const char **)name.baseBuffer);
        ((void (__thiscall *)(idSys *, char *))v27->OpenURL)(sys, v28);
      }
      else
      {
        ((void (__thiscall *)(idSys *, _DWORD))sys->StartProcess)(sys, *(_DWORD *)name.baseBuffer);
      }
      p_dltitle = &name;
    }
    else
    {
      v29 = *(_DWORD *)name.baseBuffer;
      v30 = session->__vftable;
      v31 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104334",
              -1,
              1,
              0);
      v32 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int, int))(*(_DWORD *)common.type + 168))(
                            common.type,
                            "#str_104333",
                            -1,
                            v29,
                            v31);
      v33 = va(v32);
      ((void (__thiscall *)(idSession *, _DWORD, char *, int, int, int))v30->MessageBoxA)(
        session,
        0,
        v33,
        v95,
        v97,
        v99);
      p_dltitle = &name;
    }
  }
  else
  {
    if ( this->backgroundDownload.url.dlerror[0] )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "update download failed. curl error: %s",
        this->backgroundDownload.url.dlerror);
    idAsyncClient::SendVersionDLUpdate(this, 2);
    v34 = f->GetName(f);
    v35 = v34;
    name.alloced = 0;
    *(_DWORD *)&name.baseBuffer[4] = 20;
    *(_DWORD *)name.baseBuffer = &name.baseBuffer[8];
    name.baseBuffer[8] = 0;
    if ( v34 )
    {
      v36 = strlen(v34);
      if ( v36 + 1 > 20 )
        idStr::ReAllocate((idStr *)&name.alloced, v36 + 1, 1);
      v37 = *(_BYTE **)name.baseBuffer;
      v38 = v35;
      do
      {
        v39 = *v38;
        *v37++ = *v38++;
      }
      while ( v39 );
      name.alloced = v36;
    }
    fileSystem->CloseFile(fileSystem, f);
    fileSystem->RemoveFile(fileSystem, *(const char **)name.baseBuffer, "fs_savepath");
    v40 = session->__vftable;
    v41 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type
                                                                                              + 168))(
            common.type,
            "#str_104336",
            -1,
            1,
            0,
            0,
            0);
    v42 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_104335",
            -1,
            v41);
    ((void (__thiscall *)(idSession *, _DWORD, int))v40->MessageBoxA)(session, 0, v42);
    if ( this->updateFallback.len )
      sys->OpenURL(sys, this->updateFallback.data, 1);
    else
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "no fallback URL\n");
    p_dltitle = &name;
  }
LABEL_96:
  v115 = -1;
  idStr::FreeData(p_dltitle);
}

// FUNC: private: void __thiscall idAsyncClient::ProcessDownloadInfoMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ProcessDownloadInfoMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  int Bits; // ebp
  int v5; // ecx
  int dlRequest; // eax
  idSession_vtbl *v7; // esi
  int v8; // eax
  const char *v9; // eax
  char *v10; // eax
  int v11; // ebp
  char v12; // al
  int v13; // ecx
  bool v14; // zf
  int granularity; // edi
  bool v16; // cc
  int *v17; // eax
  pakDlEntry_t *v18; // ebp
  int v19; // ebp
  int v20; // edi
  int num; // ebp
  int size; // edi
  int v23; // edi
  pakDlEntry_t *v24; // eax
  int *p_checksum; // edi
  pakDlEntry_t *list; // ebx
  int *v27; // eax
  pakDlEntry_t *v28; // ebp
  int v29; // ebp
  int v30; // edi
  int checksum; // edx
  int v32; // edi
  int *v33; // eax
  pakDlEntry_t *v34; // ebp
  int v35; // ebp
  int v36; // edi
  int v37; // ebp
  int v38; // edi
  int v39; // edi
  pakDlEntry_t *v40; // eax
  int *v41; // edi
  pakDlEntry_t *v42; // ebx
  int *v43; // eax
  pakDlEntry_t *v44; // ebp
  int v45; // ebp
  int v46; // edi
  int v47; // ecx
  int dlCount; // eax
  pakDlEntry_t *v49; // eax
  int *v50; // edi
  idSession_vtbl *v51; // esi
  int v52; // eax
  int v53; // eax
  char v54; // bl
  idSession_vtbl *v55; // edi
  int v56; // eax
  int v57; // eax
  pakDlEntry_t *v58; // eax
  int *v59; // edi
  char *v60; // edi
  idSession_vtbl *v61; // ebx
  int v62; // eax
  const char *v63; // eax
  pakDlEntry_t *v64; // eax
  int *v65; // edi
  char *data; // edi
  int v67; // eax
  int v68; // eax
  int v69; // [esp+Ch] [ebp-49Ch]
  int value; // [esp+10h] [ebp-498h]
  float valuea; // [esp+10h] [ebp-498h]
  int v72; // [esp+14h] [ebp-494h]
  bool gotAllFiles; // [esp+2Ah] [ebp-47Eh]
  bool gotGame; // [esp+2Bh] [ebp-47Dh]
  int pakIndex; // [esp+2Ch] [ebp-47Ch]
  idStr sizeStr; // [esp+34h] [ebp-474h] BYREF
  pakDlEntry_t entry; // [esp+54h] [ebp-454h] BYREF
  char buf[1024]; // [esp+9Ch] [ebp-40Ch] BYREF
  int v79; // [esp+4A4h] [ebp-4h]

  Bits = idBitMsg::ReadBits(msg, 32);
  v5 = (unsigned __int8)idBitMsg::ReadBits(msg, 8);
  entry.url.data = entry.url.baseBuffer;
  entry.url.len = 0;
  entry.url.alloced = 20;
  entry.url.baseBuffer[0] = 0;
  entry.filename.len = 0;
  entry.filename.alloced = 20;
  entry.filename.data = entry.filename.baseBuffer;
  entry.filename.baseBuffer[0] = 0;
  sizeStr.alloced = 20;
  v79 = 0;
  gotAllFiles = 1;
  sizeStr.len = 0;
  sizeStr.data = sizeStr.baseBuffer;
  sizeStr.baseBuffer[0] = 0;
  dlRequest = this->dlRequest;
  LOBYTE(v79) = 1;
  gotGame = 0;
  if ( dlRequest != -1 && Bits == dlRequest )
  {
    this->dlRequest = -1;
    if ( v5 == 1 )
    {
      idBitMsg::ReadString(msg, buf, 1024);
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
      v7 = session->__vftable;
      v8 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
             common.type,
             "#str_107218",
             -1,
             1,
             "yes",
             0,
             0);
      v9 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, char *, int))(*(_DWORD *)common.type
                                                                                             + 168))(
                           common.type,
                           "#str_107217",
                           -1,
                           &buf[16],
                           v8);
      v10 = va(v9);
      if ( *(_BYTE *)((int (__thiscall *)(idSession *, int, char *, int, int, int))v7->MessageBoxA)(
                       session,
                       3,
                       v10,
                       v69,
                       value,
                       v72) )
        sys->OpenURL(sys, buf, 1);
      goto LABEL_102;
    }
    if ( v5 == 2 )
    {
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
      if ( this->dlList.num )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
          common.type,
          "tried to process a download list while already busy downloading things");
LABEL_102:
        LOBYTE(v79) = 0;
        idStr::FreeData(&sizeStr);
        v79 = -1;
        pakDlEntry_t::~pakDlEntry_t(&entry);
        return;
      }
      pakIndex = -1;
      this->totalDlSize = 0;
LABEL_10:
      v11 = pakIndex;
      do
      {
        while ( 1 )
        {
          pakIndex = ++v11;
          v12 = idBitMsg::ReadBits(msg, 8);
          if ( v12 == 1 )
          {
            if ( !v11 )
              gotGame = 1;
            idBitMsg::ReadString(msg, buf, 1024);
            idStr::operator=(&entry.filename, buf);
            idBitMsg::ReadString(msg, buf, 1024);
            idStr::operator=(&entry.url, buf);
            entry.size = idBitMsg::ReadBits(msg, 32);
            v13 = this->dlChecksums[v11];
            this->totalDlSize += entry.size;
            v14 = this->dlList.list == 0;
            entry.checksum = v13;
            if ( v14 )
            {
              granularity = this->dlList.granularity;
              if ( granularity > 0 )
              {
                if ( granularity != this->dlList.size )
                {
                  v16 = granularity < this->dlList.num;
                  this->dlList.size = granularity;
                  if ( v16 )
                    this->dlList.num = granularity;
                  v17 = (int *)Memory::Allocate(72 * granularity + 4);
                  LOBYTE(v79) = 3;
                  if ( v17 )
                  {
                    v18 = (pakDlEntry_t *)(v17 + 1);
                    *v17 = granularity;
                    `eh vector constructor iterator'(
                      v17 + 1,
                      0x48u,
                      granularity,
                      (void (__thiscall *)(void *))pakDlEntry_t::pakDlEntry_t,
                      (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
                  }
                  else
                  {
                    v18 = 0;
                  }
                  this->dlList.list = v18;
                  v19 = 0;
                  v16 = this->dlList.num <= 0;
                  LOBYTE(v79) = 1;
                  if ( !v16 )
                  {
                    v20 = 0;
                    do
                    {
                      pakDlEntry_t::operator=(&this->dlList.list[v20].url, v20 * 72);
                      ++v19;
                      ++v20;
                    }
                    while ( v19 < this->dlList.num );
                  }
                }
              }
              else
              {
                this->dlList.list = 0;
                this->dlList.num = 0;
                this->dlList.size = 0;
              }
            }
            num = this->dlList.num;
            size = this->dlList.size;
            if ( num == size )
            {
              if ( !this->dlList.granularity )
                this->dlList.granularity = 16;
              v23 = this->dlList.granularity + size - (this->dlList.granularity + size) % this->dlList.granularity;
              if ( v23 > 0 )
              {
                if ( v23 != this->dlList.size )
                {
                  list = this->dlList.list;
                  this->dlList.size = v23;
                  if ( v23 < num )
                    this->dlList.num = v23;
                  v27 = (int *)Memory::Allocate(72 * v23 + 4);
                  LOBYTE(v79) = 4;
                  if ( v27 )
                  {
                    v28 = (pakDlEntry_t *)(v27 + 1);
                    *v27 = v23;
                    `eh vector constructor iterator'(
                      v27 + 1,
                      0x48u,
                      v23,
                      (void (__thiscall *)(void *))pakDlEntry_t::pakDlEntry_t,
                      (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
                  }
                  else
                  {
                    v28 = 0;
                  }
                  this->dlList.list = v28;
                  v29 = 0;
                  v16 = this->dlList.num <= 0;
                  LOBYTE(v79) = 1;
                  if ( !v16 )
                  {
                    v30 = 0;
                    do
                    {
                      pakDlEntry_t::operator=(&this->dlList.list[v30].url, (int)&list[v30]);
                      ++v29;
                      ++v30;
                    }
                    while ( v29 < this->dlList.num );
                  }
                  if ( list )
                  {
                    `eh vector destructor iterator'(
                      list,
                      0x48u,
                      list[-1].checksum,
                      (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
                    Memory::Free(&list[-1].checksum);
                  }
                }
              }
              else
              {
                v24 = this->dlList.list;
                if ( v24 )
                {
                  p_checksum = &v24[-1].checksum;
                  `eh vector destructor iterator'(
                    v24,
                    0x48u,
                    v24[-1].checksum,
                    (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
                  Memory::Free(p_checksum);
                }
                this->dlList.list = 0;
                this->dlList.num = 0;
                this->dlList.size = 0;
              }
            }
            pakDlEntry_t::operator=(&this->dlList.list[this->dlList.num].url, (int)&entry);
            checksum = entry.checksum;
            ++this->dlList.num;
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "download %s from %s ( 0x%x )\n",
              entry.filename.data,
              entry.url.data,
              checksum);
            goto LABEL_10;
          }
          if ( v12 )
            break;
          idBitMsg::ReadString(msg, buf, 1024);
          idStr::operator=(&entry.filename, buf);
          idStr::operator=(&entry.url, (char *)&entityFilter);
          v14 = this->dlList.list == 0;
          entry.size = 0;
          entry.checksum = 0;
          if ( v14 )
          {
            v32 = this->dlList.granularity;
            if ( v32 > 0 )
            {
              if ( v32 != this->dlList.size )
              {
                v16 = v32 < this->dlList.num;
                this->dlList.size = v32;
                if ( v16 )
                  this->dlList.num = v32;
                v33 = (int *)Memory::Allocate(72 * v32 + 4);
                LOBYTE(v79) = 5;
                if ( v33 )
                {
                  v34 = (pakDlEntry_t *)(v33 + 1);
                  *v33 = v32;
                  `eh vector constructor iterator'(
                    v33 + 1,
                    0x48u,
                    v32,
                    (void (__thiscall *)(void *))pakDlEntry_t::pakDlEntry_t,
                    (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
                }
                else
                {
                  v34 = 0;
                }
                this->dlList.list = v34;
                v35 = 0;
                v16 = this->dlList.num <= 0;
                LOBYTE(v79) = 1;
                if ( !v16 )
                {
                  v36 = 0;
                  do
                  {
                    pakDlEntry_t::operator=(&this->dlList.list[v36].url, v36 * 72);
                    ++v35;
                    ++v36;
                  }
                  while ( v35 < this->dlList.num );
                }
              }
            }
            else
            {
              this->dlList.list = 0;
              this->dlList.num = 0;
              this->dlList.size = 0;
            }
          }
          v37 = this->dlList.num;
          v38 = this->dlList.size;
          if ( v37 == v38 )
          {
            if ( !this->dlList.granularity )
              this->dlList.granularity = 16;
            v39 = this->dlList.granularity + v38 - (this->dlList.granularity + v38) % this->dlList.granularity;
            if ( v39 > 0 )
            {
              if ( v39 != this->dlList.size )
              {
                v42 = this->dlList.list;
                this->dlList.size = v39;
                if ( v39 < v37 )
                  this->dlList.num = v39;
                v43 = (int *)Memory::Allocate(72 * v39 + 4);
                LOBYTE(v79) = 6;
                if ( v43 )
                {
                  v44 = (pakDlEntry_t *)(v43 + 1);
                  *v43 = v39;
                  `eh vector constructor iterator'(
                    v43 + 1,
                    0x48u,
                    v39,
                    (void (__thiscall *)(void *))pakDlEntry_t::pakDlEntry_t,
                    (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
                }
                else
                {
                  v44 = 0;
                }
                this->dlList.list = v44;
                v45 = 0;
                v16 = this->dlList.num <= 0;
                LOBYTE(v79) = 1;
                if ( !v16 )
                {
                  v46 = 0;
                  do
                  {
                    pakDlEntry_t::operator=(&this->dlList.list[v46].url, (int)&v42[v46]);
                    ++v45;
                    ++v46;
                  }
                  while ( v45 < this->dlList.num );
                }
                if ( v42 )
                {
                  `eh vector destructor iterator'(
                    v42,
                    0x48u,
                    v42[-1].checksum,
                    (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
                  Memory::Free(&v42[-1].checksum);
                }
              }
            }
            else
            {
              v40 = this->dlList.list;
              if ( v40 )
              {
                v41 = &v40[-1].checksum;
                `eh vector destructor iterator'(
                  v40,
                  0x48u,
                  v40[-1].checksum,
                  (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
                Memory::Free(v41);
              }
              this->dlList.list = 0;
              this->dlList.num = 0;
              this->dlList.size = 0;
            }
          }
          pakDlEntry_t::operator=(&this->dlList.list[this->dlList.num].url, (int)&entry);
          v11 = pakIndex;
          ++this->dlList.num;
          if ( pakIndex || this->dlChecksums[0] )
          {
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "no download offered for %s ( 0x%x )\n",
              entry.filename.data,
              this->dlChecksums[pakIndex]);
            gotAllFiles = 0;
          }
        }
      }
      while ( v12 != 2 );
      v47 = this->dlList.num;
      dlCount = this->dlCount;
      if ( v47 < dlCount )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%d files were ignored by the server\n",
          dlCount - v47);
        gotAllFiles = 0;
      }
      valuea = (float)this->totalDlSize;
      idStr::BestUnit(&sizeStr, "%.2f", valuea, MEASURE_SIZE);
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
      if ( this->totalDlSize )
      {
        v54 = 0;
        if ( gotGame )
        {
          v55 = session->__vftable;
          v54 = 1;
          v56 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                  common.type,
                  "#str_107221",
                  -1,
                  1,
                  "yes",
                  0,
                  0);
          v57 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                  common.type,
                  "#str_107220",
                  -1,
                  v56);
          if ( !*(_BYTE *)((int (__thiscall *)(idSession *, int, int))v55->MessageBoxA)(session, 3, v57) )
          {
            v58 = this->dlList.list;
            if ( v58 )
            {
              v59 = &v58[-1].checksum;
              `eh vector destructor iterator'(
                v58,
                0x48u,
                v58[-1].checksum,
                (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
              Memory::Free(v59);
            }
            this->dlList.list = 0;
            this->dlList.num = 0;
            this->dlList.size = 0;
            goto LABEL_102;
          }
        }
        if ( gotAllFiles )
        {
          if ( v54 || idAsyncNetwork::clientDownload.internalVar->integerValue != 1 )
            goto LABEL_102;
          data = sizeStr.data;
          v61 = session->__vftable;
          v67 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                  common.type,
                  "#str_107218",
                  -1,
                  1,
                  "yes",
                  0,
                  0);
          v63 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, char *, int))(*(_DWORD *)common.type
                                                                                                  + 168))(
                                common.type,
                                "#str_107224",
                                -1,
                                data,
                                v67);
        }
        else
        {
          v60 = sizeStr.data;
          v61 = session->__vftable;
          v62 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                  common.type,
                  "#str_107218",
                  -1,
                  1,
                  "yes",
                  0,
                  0);
          v63 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, char *, int))(*(_DWORD *)common.type
                                                                                                  + 168))(
                                common.type,
                                "#str_107222",
                                -1,
                                v60,
                                v62);
        }
        va(v63);
        if ( !*(_BYTE *)((int (__thiscall *)(idSession *, int))v61->MessageBoxA)(session, 3) )
        {
          v64 = this->dlList.list;
          if ( v64 )
          {
            v65 = &v64[-1].checksum;
            `eh vector destructor iterator'(
              v64,
              0x48u,
              v64[-1].checksum,
              (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
            Memory::Free(v65);
          }
          this->dlList.list = 0;
          this->dlList.num = 0;
          this->dlList.size = 0;
        }
        goto LABEL_102;
      }
      v49 = this->dlList.list;
      if ( v49 )
      {
        v50 = &v49[-1].checksum;
        `eh vector destructor iterator'(
          v49,
          0x48u,
          v49[-1].checksum,
          (void (__thiscall *)(void *))pakDlEntry_t::~pakDlEntry_t);
        Memory::Free(v50);
      }
      this->dlList.list = 0;
      this->dlList.num = 0;
      this->dlList.size = 0;
      v51 = session->__vftable;
      v52 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type
                                                                                                + 168))(
              common.type,
              "#str_107218",
              -1,
              1,
              0,
              0,
              0);
      v53 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107219",
              -1,
              v52);
    }
    else
    {
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect");
      v51 = session->__vftable;
      v68 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type
                                                                                                + 168))(
              common.type,
              "#str_107218",
              -1,
              1,
              0,
              0,
              0);
      v53 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107223",
              -1,
              v68);
    }
    ((void (__thiscall *)(idSession *, _DWORD, int))v51->MessageBoxA)(session, 0, v53);
    goto LABEL_102;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
    common.type,
    "bad download id from server, ignored");
  LOBYTE(v79) = 0;
  idStr::FreeData(&sizeStr);
  v79 = 2;
  idStr::FreeData(&entry.filename);
  v79 = -1;
  idStr::FreeData(&entry.url);
}

// FUNC: private: void __thiscall idAsyncClient::ConnectionlessMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncClient::ConnectionlessMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  unsigned int v4; // ebx
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  netadr_t v8; // [esp-10h] [ebp-830h]
  netadr_t v9; // [esp-Ch] [ebp-82Ch]
  idAsyncClient *v11; // [esp+Ch] [ebp-814h]
  idAsyncClient *v12; // [esp+Ch] [ebp-814h]
  idAsyncClient *v13; // [esp+Ch] [ebp-814h]
  netadr_t result; // [esp+10h] [ebp-810h] BYREF
  char string[2048]; // [esp+20h] [ebp-800h] BYREF

  idBitMsg::ReadString(msg, string, 2048);
  if ( idStr::Icmp(string, &entityFilter) )
  {
    if ( !idStr::Icmp(string, "infoResponse") )
    {
      idAsyncClient::ProcessInfoResponseMessage(this, from, msg);
      return;
    }
    v4 = *(_DWORD *)&from.port;
    v9 = *idAsyncNetwork::GetMasterAddress(&result);
    if ( !Sys_CompareNetAdrBase(from, v9) )
      goto LABEL_45;
    if ( !idStr::Icmp(string, "servers") )
    {
      idAsyncClient::ProcessServersListMessage(this, from, msg);
      return;
    }
    if ( !idStr::Icmp(string, "authKey") )
    {
      session->CDKeysAuthReply(session, 1, 0);
      return;
    }
    if ( !idStr::Icmp(string, "newVersion") )
    {
      idAsyncClient::ProcessVersionMessage(this, from, msg);
      return;
    }
    if ( idStr::Icmp(string, "friends") )
    {
LABEL_45:
      if ( Sys_CompareNetAdrBase(from, this->serverAddress)
        || this->lastRconTime + 10000 >= this->realTime && Sys_CompareNetAdrBase(from, this->lastRconAddress) )
      {
        if ( idStr::Icmp(string, "challengeResponse") )
        {
          if ( idStr::Icmp(string, "connectResponse") )
          {
            if ( idStr::Icmp(string, "disconnect") )
            {
              if ( idStr::Icmp(string, "print") )
              {
                if ( idStr::Icmp(string, "pureServer") )
                {
                  if ( !idStr::Icmp(string, "downloadInfo") )
                    idAsyncClient::ProcessDownloadInfoMessage(this, from, msg);
                  if ( !idStr::Icmp(string, "authrequired") && idAsyncNetwork::LANServer.internalVar->integerValue )
                  {
                    v12 = *(idAsyncClient **)common.type;
                    v6 = Sys_NetAdrToString(from);
                    ((void (*)(netadrtype_t, const char *, ...))v12->serverList.callbacks[4].size)(
                      common.type,
                      "server %s requests master authorization for this client. Turning off LAN mode\n",
                      v6);
                    idAsyncNetwork::LANServer.internalVar->InternalSetBool(idAsyncNetwork::LANServer.internalVar, 0);
                    v4 = *(_DWORD *)&from.port;
                  }
                  v8.type = from.type;
                  *(_QWORD *)v8.ip = __PAIR64__(v4, *(unsigned int *)from.ip);
                  v13 = *(idAsyncClient **)common.type;
                  v7 = Sys_NetAdrToString(v8);
                  ((void (*)(netadrtype_t, const char *, ...))v13->serverList.callbacks[4].num)(
                    common.type,
                    "ignored message from %s: %s\n",
                    v7,
                    string);
                }
                else
                {
                  idAsyncClient::ProcessPureMessage(this, from, msg);
                }
              }
              else
              {
                idAsyncClient::ProcessPrintMessage(this, from, msg);
              }
            }
            else
            {
              idAsyncClient::ProcessDisconnectMessage(this, from, msg);
            }
          }
          else
          {
            idAsyncClient::ProcessConnectResponseMessage(this, from, msg);
          }
        }
        else
        {
          idAsyncClient::ProcessChallengeResponseMessage(this, from, msg);
        }
      }
      else
      {
        v11 = *(idAsyncClient **)common.type;
        v5 = Sys_NetAdrToString(from);
        ((void (*)(netadrtype_t, const char *, ...))v11->serverList.callbacks[4].num)(
          common.type,
          "got message '%s' from bad source: %s\n",
          string,
          v5);
      }
    }
    else
    {
      idAsyncClient::ProcessFriendsMessage(this, from, msg);
    }
  }
  else if ( msg->curSize <= 2048 )
  {
    qmemcpy(string, msg->readData, msg->curSize);
    if ( !idStr::Icmpn(string, &byte_102A92FC, 7)
      && string[7] != 83
      && string[7] != 50
      && string[7] != 71
      && string[7] != 73
      && string[7] != 89
      && string[7] != 66
      && string[7] != 76 )
    {
      PbClAddEvent(13, msg->curSize - 4, &string[4]);
    }
  }
}

// FUNC: private: void __thiscall idAsyncClient::ProcessMessage(struct netadr_t,class idBitMsg &)
void __thiscall idAsyncClient::ProcessMessage(idAsyncClient *this, netadr_t from, idBitMsg *msg)
{
  int v5; // esi
  const char *v6; // eax
  int v7; // esi
  const char *v8; // eax
  idBitMsg *msga; // [esp+20h] [ebp+10h]

  if ( idAsyncNetwork::demo.demoState == DEMO_RECORDING )
    idDemo::RecordMessage(&idAsyncNetwork::demo, this->clientTime, msg);
  msga = (idBitMsg *)(__int16)idBitMsg::ReadBits(msg, -16);
  if ( msga == (idBitMsg *)-1 )
  {
    idAsyncClient::ConnectionlessMessage(this, from, msg);
  }
  else if ( this->clientState >= CS_CONNECTED )
  {
    if ( msg->curSize - msg->readCount >= 4 )
    {
      if ( Sys_CompareNetAdrBase(from, this->channel.remoteAddress) && msga == (idBitMsg *)this->serverId )
      {
        if ( idMsgChannel::Process(&this->channel, from, this->clientTime, msg, &this->serverMessageSequence) )
        {
          this->lastPacketTime = this->clientTime;
          idAsyncClient::ProcessReliableServerMessages(this);
          idAsyncClient::ProcessUnreliableServerMessage(this, msg);
        }
      }
      else
      {
        v7 = *(_DWORD *)common.type;
        v8 = Sys_NetAdrToString(from);
        (*(void (**)(netadrtype_t, const char *, ...))(v7 + 132))(
          common.type,
          "%s: sequenced server packet without connection\n",
          v8);
      }
    }
    else
    {
      v5 = *(_DWORD *)common.type;
      v6 = Sys_NetAdrToString(from);
      (*(void (**)(netadrtype_t, const char *, ...))(v5 + 132))(common.type, "%s: tiny packet\n", v6);
    }
  }
}

// FUNC: public: void __thiscall idAsyncClient::RunDemoFrame(void)
void __thiscall idAsyncClient::RunDemoFrame(idAsyncClient *this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // eax
  bool v5; // bl
  int v6; // eax
  int snapshotGameFrame; // ecx
  bool v8; // cc
  int size; // [esp+10h] [ebp-446Ch] BYREF
  BOOL v10; // [esp+14h] [ebp-4468h]
  idBitMsg msg; // [esp+18h] [ebp-4464h] BYREF
  char v12[40]; // [esp+3Ch] [ebp-4440h] BYREF
  char v13[1048]; // [esp+64h] [ebp-4418h] BYREF
  char data[16384]; // [esp+47Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  usercmdGen->GetDirectUsercmd(usercmdGen, (usercmd_t *)v12);
  if ( !idAsyncNetwork::demo.timedemo )
  {
    this->gameTimeResidual += idAsyncClient::UpdateDemoTime(this, 100);
    do
    {
      v4 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
      v5 = idDemo::PlayMessage(
             &idAsyncNetwork::demo,
             this->clientTime,
             data,
             &size,
             0x4000,
             v4 - this->gameTimeResidual - 1);
      if ( v5 )
      {
        msg.writeData = (unsigned __int8 *)data;
        msg.readData = (const unsigned __int8 *)data;
        msg.maxSize = 0x4000;
        msg.numValueOverflows = 0;
        msg.curSize = 0x4000;
        if ( size <= 0x4000 )
          msg.curSize = size;
        msg.readCount = 0;
        msg.readBit = 0;
        idAsyncClient::ProcessMessage(this, this->serverAddress, &msg);
      }
      else if ( idAsyncNetwork::demo.demoState != DEMO_PLAYING )
      {
        return;
      }
      this->gameTimeResidual += idAsyncClient::UpdateDemoTime(this, 100);
    }
    while ( v5
         || this->gameTimeResidual < (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) );
    game->ClientRun(game);
    while ( this->gameTimeResidual >= (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) )
    {
      idDemo::ReadUsercmd(&idAsyncNetwork::demo, this->gameFrame);
      ++this->gameFrame;
      this->gameTime += (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
      v6 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
      snapshotGameFrame = this->snapshotGameFrame;
      this->gameTimeResidual -= v6;
      if ( snapshotGameFrame < this->gameFrame )
      {
        do
        {
          idAsyncClient::DuplicateUsercmds(this, this->snapshotGameFrame, this->snapshotGameTime);
          if ( this->snapshotGameFrame + 1 < this->gameFrame
            || (v8 = this->gameTimeResidual < (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type),
                LOBYTE(v10) = 1,
                !v8) )
          {
            LOBYTE(v10) = 0;
          }
          game->ClientPrediction(
            game,
            (gameReturn_t *)v13,
            this->clientNum,
            this->userCmds[(unsigned __int8)this->snapshotGameFrame],
            v10,
            0);
          ++this->snapshotGameFrame;
          this->snapshotGameTime += (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
        }
        while ( this->snapshotGameFrame < this->gameFrame );
      }
    }
    goto LABEL_26;
  }
  v2 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
  this->clientTime += v2;
  while ( idDemo::PlayMessage(&idAsyncNetwork::demo, this->clientTime, data, &size, 0x4000, v2 - 1) )
  {
    msg.writeData = (unsigned __int8 *)data;
    msg.readData = (const unsigned __int8 *)data;
    msg.maxSize = 0x4000;
    msg.numValueOverflows = 0;
    msg.curSize = 0x4000;
    if ( size <= 0x4000 )
      msg.curSize = size;
    msg.readCount = 0;
    msg.readBit = 0;
    idAsyncClient::ProcessMessage(this, this->serverAddress, &msg);
  }
  if ( idAsyncNetwork::demo.demoState == DEMO_PLAYING )
  {
    game->ClientRun(game);
    idDemo::ReadUsercmd(&idAsyncNetwork::demo, this->gameFrame);
    this->gameTime += v2;
    if ( this->snapshotGameFrame < ++this->gameFrame )
    {
      do
      {
        idAsyncClient::DuplicateUsercmds(this, this->snapshotGameFrame, this->snapshotGameTime);
        v3 = this->snapshotGameFrame + 1;
        LOBYTE(v3) = v3 >= this->gameFrame;
        game->ClientPrediction(
          game,
          (gameReturn_t *)v13,
          this->clientNum,
          this->userCmds[(unsigned __int8)this->snapshotGameFrame],
          v3,
          0);
        ++this->snapshotGameFrame;
        this->snapshotGameTime += v2;
      }
      while ( this->snapshotGameFrame < this->gameFrame );
    }
LABEL_26:
    session->rw->PushMarkedDefs(session->rw);
  }
}

// FUNC: public: __thiscall idAsyncClient::idAsyncClient(void)
void __thiscall idAsyncClient::idAsyncClient(idAsyncClient *this)
{
  rvServerScan::rvServerScan(&this->serverList);
  idPort::idPort(&this->clientPort);
  idMsgChannel::idMsgChannel(&this->channel);
  this->updateMSG.len = 0;
  this->updateMSG.alloced = 20;
  this->updateMSG.data = this->updateMSG.baseBuffer;
  this->updateMSG.baseBuffer[0] = 0;
  this->updateURL.len = 0;
  this->updateURL.alloced = 20;
  this->updateURL.data = this->updateURL.baseBuffer;
  this->updateURL.baseBuffer[0] = 0;
  this->updateFile.len = 0;
  this->updateFile.alloced = 20;
  this->updateFile.data = this->updateFile.baseBuffer;
  this->updateFile.baseBuffer[0] = 0;
  this->updateFallback.len = 0;
  this->updateFallback.alloced = 20;
  this->updateFallback.data = this->updateFallback.baseBuffer;
  this->updateFallback.baseBuffer[0] = 0;
  this->backgroundDownload.url.url.len = 0;
  this->backgroundDownload.url.url.alloced = 20;
  this->backgroundDownload.url.url.data = this->backgroundDownload.url.url.baseBuffer;
  this->backgroundDownload.url.url.baseBuffer[0] = 0;
  this->dlList.granularity = 16;
  this->dlList.list = 0;
  this->dlList.num = 0;
  this->dlList.size = 0;
  this->guiNetMenu = 0;
  this->updateState = UPDATE_NONE;
  this->nextHeartbeatTime = 0;
  idAsyncClient::Clear(this);
}

// FUNC: public: void __thiscall idAsyncClient::RunFrame(void)
void __thiscall idAsyncClient::RunFrame(idAsyncClient *this)
{
  int v2; // ebx
  int v3; // eax
  int v4; // edi
  bool v5; // zf
  int v6; // ecx
  tm *v7; // eax
  const char *v8; // eax
  const char *v9; // edi
  unsigned int v10; // kr00_4
  int v11; // ebx
  char v12; // cl
  int i; // eax
  char *v14; // edx
  int v15; // edi
  int j; // eax
  unsigned __int8 v17; // cl
  char *v18; // edx
  int v19; // edi
  int v20; // eax
  char v21; // cl
  char *v22; // edx
  const char *v23; // eax
  const char *v24; // edi
  int v25; // ebx
  char v26; // cl
  int k; // eax
  char *v28; // edx
  int v29; // edi
  int v30; // eax
  char v31; // cl
  char *v32; // edx
  idFile *v33; // eax
  idFile v34; // edi
  long double v35; // st7
  idFile_vtbl *v36; // edi
  int VideoRam; // eax
  int v38; // ecx
  int v39; // eax
  int v40; // ecx
  int *v41; // eax
  int v42; // eax
  bool PacketBlocking; // bl
  int v44; // eax
  int v45; // ecx
  int realTime; // edx
  int v47; // ebx
  int v48; // edi
  int v49; // eax
  int snapshotGameFrame; // ecx
  int snapshotGameTime; // edx
  int v52; // eax
  int v53; // eax
  int v54; // ecx
  int v55; // eax
  netadr_t v56; // [esp+2Ch] [ebp-84DCh]
  int SystemRam; // [esp+38h] [ebp-84D0h]
  const char *ProcessorString; // [esp+3Ch] [ebp-84CCh]
  int timeptr; // [esp+50h] [ebp-84B8h] BYREF
  BOOL v60; // [esp+54h] [ebp-84B4h]
  idStr v61; // [esp+58h] [ebp-84B0h] BYREF
  int v62; // [esp+78h] [ebp-8490h] BYREF
  idBitMsg v63; // [esp+7Ch] [ebp-848Ch] BYREF
  int size; // [esp+A4h] [ebp-8464h] BYREF
  netadr_t from; // [esp+A8h] [ebp-8460h] BYREF
  idBitMsg msg; // [esp+B4h] [ebp-8454h] BYREF
  netadr_t result; // [esp+D8h] [ebp-8430h] BYREF
  char sessCmd[1048]; // [esp+E4h] [ebp-8424h] BYREF
  char data[16384]; // [esp+4FCh] [ebp-800Ch] BYREF
  char v70[16384]; // [esp+44FCh] [ebp-400Ch] BYREF
  int v71; // [esp+8504h] [ebp-4h]

  if ( idAsyncNetwork::demo.demoState == DEMO_PLAYING )
  {
    idAsyncClient::RunDemoFrame(this);
  }
  else
  {
    idBitMsg::idBitMsg(&msg);
    v2 = 0;
    timeptr = 0;
    v60 = 0;
    v3 = Sys_Milliseconds();
    if ( v3 - this->realTime >= 0 )
    {
      v4 = 100;
      if ( v3 - this->realTime <= 100 )
        v4 = v3 - this->realTime;
    }
    else
    {
      v4 = 0;
    }
    this->clientTime += v4;
    v5 = this->clientPort.port == 0;
    this->realTime = v3;
    if ( !v5 )
    {
      idAsyncClient::HandleDownloads(this, 0, v4);
      this->gameTimeResidual += v4;
      if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
      {
        if ( idAsyncNetwork::debugStartLevel.internalVar->integerValue )
        {
          v63.writeData = 0;
          v63.maxSize = 20;
          v63.readData = (const unsigned __int8 *)&v63.curSize;
          LOBYTE(v63.curSize) = 0;
          v61.alloced = 20;
          v71 = 0;
          v61.len = 0;
          v61.data = v61.baseBuffer;
          v61.baseBuffer[0] = 0;
          timeptr = 0;
          v6 = *(_DWORD *)common.type;
          LOBYTE(v71) = 1;
          (*(void (__cdecl **)(netadrtype_t, const char *))(v6 + 124))(
            common.type,
            "Match starting, frame time logging on\n");
          profile_netDebugActive = 1;
          idAsyncNetwork::debugStartLevel.internalVar->InternalSetBool(idAsyncNetwork::debugStartLevel.internalVar, 0);
          session->GetCurrentMapName(session, (idStr *)&v63);
          idStr::StripFileExtension((idStr *)&v63);
          idStr::StripPath((idStr *)&v63);
          idStr::operator=(&v61, "logs/timing_logs/");
          timeptr = time(&timeptr);
          v7 = localtime(&timeptr);
          v8 = va("%02d%02d%02d_%02d%02d_", v7->tm_year % 100, v7->tm_mon + 1, v7->tm_mday, v7->tm_hour, v7->tm_min);
          v9 = v8;
          if ( v8 )
          {
            v10 = strlen(v8);
            v11 = v10 + v61.len;
            if ( (int)(v10 + v61.len + 1) > v61.alloced )
              idStr::ReAllocate(&v61, v10 + v61.len + 1, 1);
            v12 = *v9;
            for ( i = 0; v12; v12 = v9[i] )
            {
              v14 = &v61.data[i++];
              v14[v61.len] = v12;
            }
            v61.len = v11;
            v61.data[v11] = 0;
            v2 = v60;
          }
          v15 = (int)&v63.writeData[v61.len];
          if ( (int)&v63.writeData[v61.len + 1] > v61.alloced )
            idStr::ReAllocate(&v61, (int)&v63.writeData[v61.len + 1], 1);
          for ( j = 0; j < (int)v63.writeData; v18[v61.len] = v17 )
          {
            v17 = v63.readData[j];
            v18 = &v61.data[j++];
          }
          v61.len = v15;
          v61.data[v15] = 0;
          v19 = v61.len + 1;
          if ( v61.len + 2 > v61.alloced )
            idStr::ReAllocate(&v61, v61.len + 2, 1);
          v20 = 0;
          v21 = 95;
          do
          {
            v22 = &v61.data[v20++];
            v22[v61.len] = v21;
            v21 = asc_1029F57C[v20];
          }
          while ( v21 );
          v61.len = v19;
          v61.data[v19] = 0;
          v23 = cvarSystem->GetCVarString(cvarSystem, "win_username");
          v24 = v23;
          if ( v23 )
          {
            v25 = strlen(v23) + v61.len;
            if ( v25 + 1 > v61.alloced )
              idStr::ReAllocate(&v61, v25 + 1, 1);
            v26 = *v24;
            for ( k = 0; v26; v26 = v24[k] )
            {
              v28 = &v61.data[k++];
              v28[v61.len] = v26;
            }
            v61.len = v25;
            v61.data[v25] = 0;
            v2 = v60;
          }
          v29 = v61.len + 12;
          if ( v61.len + 13 > v61.alloced )
            idStr::ReAllocate(&v61, v61.len + 13, 1);
          v30 = 0;
          v31 = 95;
          do
          {
            v32 = &v61.data[v30++];
            v32[v61.len] = v31;
            v31 = aTimelogCsv[v30];
          }
          while ( v31 );
          v61.len = v29;
          v61.data[v29] = 0;
          if ( profile_File )
            fileSystem->CloseFile(fileSystem, profile_File);
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "Attempting to open file '%s'\n",
            v61.data);
          v33 = fileSystem->OpenFileWrite(fileSystem, v61.data, "fs_savePath", 0);
          profile_File = v33;
          if ( v33
            || ((*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "ERROR:  unable to open frame log '%s'!\n",
                  v61.data),
                (v33 = profile_File) != 0) )
          {
            v34.__vftable = v33->__vftable;
            ProcessorString = Sys_GetProcessorString();
            SystemRam = Sys_GetSystemRam();
            v35 = Sys_ClockTicksPerSecond();
            v34.Printf(profile_File, "%0.3fghz %d MB %s\n", v35 * 9.999999717180685e-10, SystemRam, ProcessorString);
            v36 = profile_File->__vftable;
            VideoRam = Sys_GetVideoRam();
            v36->Printf(profile_File, "%s %d MB\n", glConfig.renderer_string, VideoRam);
            profile_File->Printf(profile_File, "%s %s V%s Build %u\n", "Quake4", "Release", "", 0);
            profile_File->Printf(
              profile_File,
              "fps,frameTime,predictTime,packetTime,clientPredictTime,gameTimeResidual,frontEnd,backEnd,waiting,inBytes,o"
              "utBytes,catchupFrames,numPlayers\n");
          }
          LOBYTE(v71) = 0;
          idStr::FreeData(&v61);
          v71 = -1;
          idStr::FreeData((idStr *)&v63);
        }
        profile_gameTimeResidual = this->gameTimeResidual;
        profile_clientPredictTime = this->clientPredictTime;
        v38 = Sys_Milliseconds();
        v39 = v38 - profilePrevious;
        timeptr = v38;
        profilePrevious = v38;
        profile_frameTime = v39;
        v40 = profileIndex + 1;
        profilePreviousFrames[profileIndex % 4] = v39;
        profileIndex = v40;
        if ( v40 >= 4 )
        {
          v41 = profilePreviousFrames;
          do
            v2 += *v41++;
          while ( (int)v41 < (int)&idAsyncNetwork::verbose );
          profile_fps = 4000 / v2;
        }
        else
        {
          profile_fps = 0;
        }
      }
      do
      {
        v42 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
        PacketBlocking = idPort::GetPacketBlocking(
                           &this->clientPort,
                           &from,
                           data,
                           &size,
                           0x4000,
                           v42 - this->gameTimeResidual - this->clientPredictTime - 1);
        if ( PacketBlocking )
        {
          msg.writeData = (unsigned __int8 *)data;
          msg.readData = (const unsigned __int8 *)data;
          msg.maxSize = 0x4000;
          msg.numValueOverflows = 0;
          msg.curSize = 0x4000;
          if ( size <= 0x4000 )
            msg.curSize = size;
          msg.readCount = 0;
          msg.readBit = 0;
          idAsyncClient::ProcessMessage(this, from, &msg);
        }
        v44 = Sys_Milliseconds();
        v45 = v44 - this->realTime;
        if ( v45 >= 0 )
        {
          if ( v45 > 100 )
            v45 = 100;
        }
        else
        {
          v45 = 0;
        }
        this->clientTime += v45;
        this->gameTimeResidual += v45;
        this->realTime = v44;
      }
      while ( PacketBlocking
           || this->clientPredictTime + this->gameTimeResidual < (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) );
      if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
        profile_packetTime = Sys_Milliseconds() - timeptr;
      rvServerScan::RunFrame(&this->serverList);
      if ( this->clientState )
      {
        if ( this->clientState >= CS_CONNECTED )
        {
          if ( !idAsyncClient::CheckTimeout(this) )
          {
            idBitMsg::idBitMsg(&v63);
            if ( this->realTime >= this->nextHeartbeatTime
              && !idAsyncNetwork::LANServer.internalVar->integerValue
              && idAsyncClient::InitPort(this) )
            {
              realTime = this->realTime;
              v63.readData = (const unsigned __int8 *)v70;
              this->nextHeartbeatTime = realTime + 540000;
              v63.writeData = (unsigned __int8 *)v70;
              v63.maxSize = 0x4000;
              v63.numValueOverflows = 0;
              idBitMsg::WriteBits(&v63, -1, -16);
              idBitMsg::WriteString(&v63, "clHtbt", -1);
              idAsyncClient::WriteAuthInfo(this, &v63, 0);
              v56 = *idAsyncNetwork::GetMasterAddress(&result);
              idPort::SendPacket(&this->clientPort, v56, v63.writeData, v63.curSize);
            }
            if ( this->clientState >= CS_INGAME )
            {
              if ( (cvarSystem->GetModifiedFlags(cvarSystem) & 0x200) != 0 )
              {
                game->ThrottleUserInfo(game);
                idAsyncClient::SendUserInfoToServer(this);
                game->SetUserInfo(game, this->clientNum, &sessLocal.mapSpawnData.userInfo[this->clientNum], 1);
                cvarSystem->ClearModifiedFlags(cvarSystem, 512);
              }
              if ( this->clientPredictTime + this->gameTimeResidual >= (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) )
                this->lastFrameDelta = 0;
              if ( com_speeds.internalVar->integerValue || com_debugHudActive )
                time_gameFrame = Sys_Milliseconds();
              if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
                timeptr = Sys_Milliseconds();
              game->ClientRun(game);
              v47 = 0;
              profile_catchupFrames = 0;
              v48 = 0;
              while ( this->clientPredictTime + this->gameTimeResidual >= (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) )
              {
                idAsyncClient::SendUsercmdsToServer(this);
                ++this->gameFrame;
                this->gameTime += (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
                v49 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
                snapshotGameFrame = this->snapshotGameFrame;
                this->gameTimeResidual -= v49;
                if ( snapshotGameFrame < this->gameFrame )
                {
                  do
                  {
                    snapshotGameTime = this->snapshotGameTime;
                    v52 = this->snapshotGameFrame;
                    ++this->lastFrameDelta;
                    idAsyncClient::DuplicateUsercmds(this, v52, snapshotGameTime);
                    if ( this->snapshotGameFrame + 1 < this->gameFrame
                      || (v53 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type),
                          v54 = this->clientPredictTime + this->gameTimeResidual,
                          LOBYTE(v60) = 1,
                          v54 >= v53) )
                    {
                      LOBYTE(v60) = 0;
                    }
                    game->ClientPrediction(
                      game,
                      (gameReturn_t *)sessCmd,
                      this->clientNum,
                      this->userCmds[(unsigned __int8)this->snapshotGameFrame],
                      v60,
                      (ClientStats_t *)&v62);
                    ++v48;
                    if ( BYTE2(v62) )
                      ++v47;
                    ++net_catchupFrames;
                    ++profile_catchupFrames;
                    idAsyncNetwork::ExecuteSessionCommand(sessCmd);
                    ++this->snapshotGameFrame;
                    this->snapshotGameTime += (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
                  }
                  while ( this->snapshotGameFrame < this->gameFrame );
                }
              }
              if ( idAsyncNetwork::debugClient.internalVar->integerValue >= 2 )
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "DC: %d frames: %d new / %d old\n",
                  v48,
                  v47,
                  v48 - v47);
              if ( com_debugHudActive )
              {
                game->DebugSetInt(game, "old_frames", v48 - v47);
                game->DebugSetInt(game, "new_frames", v47);
              }
              if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
              {
                v55 = Sys_Milliseconds() - timeptr;
                profile_predictTime = v55;
              }
              else
              {
                v55 = profile_predictTime;
              }
              if ( com_speeds.internalVar->integerValue || com_debugHudActive )
              {
                time_gameFrame = Sys_Milliseconds() - time_gameFrame;
                v55 = profile_predictTime;
              }
              if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
              {
                if ( profile_File )
                  profile_File->Printf(
                    profile_File,
                    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                    profile_fps,
                    profile_frameTime,
                    v55,
                    profile_packetTime,
                    profile_clientPredictTime,
                    profile_gameTimeResidual,
                    time_frontend,
                    time_backend,
                    time_waiting,
                    net_bytesIn,
                    net_bytesOut,
                    profile_catchupFrames,
                    profile_numClients);
              }
              session->rw->PushMarkedDefs(session->rw);
            }
            else
            {
              idAsyncClient::Idle(this);
              this->gameTimeResidual = 0;
            }
          }
        }
        else
        {
          usercmdGen->GetDirectUsercmd(usercmdGen, (usercmd_t *)&v63);
          idAsyncClient::SetupConnection(this);
          this->gameTimeResidual = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) - 1;
          this->clientPredictTime = 0;
        }
      }
      else
      {
        usercmdGen->GetDirectUsercmd(usercmdGen, (usercmd_t *)&v63);
        this->gameTimeResidual = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) - 1;
        this->clientPredictTime = 0;
      }
    }
  }
}
