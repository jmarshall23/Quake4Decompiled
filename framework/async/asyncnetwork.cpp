
// FUNC: public: static bool __cdecl idAsyncNetwork::DuplicateUsercmd(class usercmd_t const &,class usercmd_t &,int,int)
char __cdecl idAsyncNetwork::DuplicateUsercmd(
        const usercmd_t *previousUserCmd,
        usercmd_t *currentUserCmd,
        int frame,
        int time)
{
  bool v4; // cc
  char forwardmove; // cl
  char rightmove; // cl
  char upmove; // cl

  if ( currentUserCmd->gameTime > previousUserCmd->gameTime )
    return 0;
  qmemcpy(currentUserCmd, previousUserCmd, sizeof(usercmd_t));
  v4 = ++currentUserCmd->duplicateCount <= 25;
  currentUserCmd->gameFrame = frame;
  currentUserCmd->gameTime = time;
  currentUserCmd->realTime = time;
  if ( !v4 )
  {
    forwardmove = currentUserCmd->forwardmove;
    LOBYTE(currentUserCmd->buttons) &= ~1u;
    if ( abs8(forwardmove) > 2u )
      currentUserCmd->forwardmove = forwardmove >> 1;
    rightmove = currentUserCmd->rightmove;
    if ( abs8(rightmove) > 2u )
      currentUserCmd->rightmove = rightmove >> 1;
    upmove = currentUserCmd->upmove;
    if ( abs8(upmove) > 2u )
      currentUserCmd->upmove = upmove >> 1;
  }
  return 1;
}

// FUNC: public: static bool __cdecl idAsyncNetwork::UsercmdInputChanged(class usercmd_t const &,class usercmd_t const &)
BOOL __cdecl idAsyncNetwork::UsercmdInputChanged(const usercmd_t *previousUserCmd, const usercmd_t *currentUserCmd)
{
  return previousUserCmd->buttons != currentUserCmd->buttons
      || previousUserCmd->forwardmove != currentUserCmd->forwardmove
      || previousUserCmd->rightmove != currentUserCmd->rightmove
      || previousUserCmd->upmove != currentUserCmd->upmove
      || previousUserCmd->angles[0] != currentUserCmd->angles[0]
      || previousUserCmd->angles[1] != currentUserCmd->angles[1]
      || previousUserCmd->angles[2] != currentUserCmd->angles[2];
}

// FUNC: private: static void __cdecl idAsyncNetwork::NextMap_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::NextMap_f()
{
  idAsyncServer::ExecuteMapChange(&idAsyncNetwork::server);
}

// FUNC: private: static void __cdecl idAsyncNetwork::Reconnect_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::Reconnect_f()
{
  idAsyncClient::Reconnect(&idAsyncNetwork::client);
}

// FUNC: private: static void __cdecl idAsyncNetwork::GetNETServers_f(class idCmdArgs const &)
void __usercall idAsyncNetwork::GetNETServers_f(int a1@<ebp>)
{
  rvServerScan::NetScan(&idAsyncNetwork::client.serverList, a1, &entityFilter, &entityFilter);
}

// FUNC: private: static void __cdecl idAsyncNetwork::GetLANServers_f(class idCmdArgs const &)
void __usercall idAsyncNetwork::GetLANServers_f(int a1@<ebp>)
{
  rvServerScan::LanScan(&idAsyncNetwork::client.serverList, a1);
}

// FUNC: private: static void __cdecl idAsyncNetwork::GetFriends_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::GetFriends_f()
{
  idAsyncClient::GetFriends(&idAsyncNetwork::client);
}

// FUNC: private: static void __cdecl idAsyncNetwork::ListServers_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::ListServers_f()
{
  idAsyncClient::ListServers(&idAsyncNetwork::client);
}

// FUNC: private: static void __cdecl idAsyncNetwork::RemoteConsole_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::RemoteConsole_f(idCmdArgs *args)
{
  char *v1; // eax

  v1 = (char *)idCmdArgs::Args(args, 1, -1, 0);
  idAsyncClient::RemoteConsole(&idAsyncNetwork::client, v1);
}

// FUNC: private: static void __cdecl idAsyncNetwork::CheckNewVersion_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::CheckNewVersion_f()
{
  idAsyncClient::SendVersionCheck(&idAsyncNetwork::client, 0);
}

// FUNC: public: static void __cdecl idAsyncNetwork::ExecuteSessionCommand(char const *)
void __cdecl idAsyncNetwork::ExecuteSessionCommand(const char *sessCmd)
{
  idSession_vtbl *v1; // esi
  int v2; // eax

  if ( *sessCmd )
  {
    if ( !idStr::Icmp(sessCmd, "game_startmenu") )
    {
      v1 = session->__vftable;
      v2 = ((int (__thiscall *)(idGame *, _DWORD))game->StartMenu)(game, 0);
      ((void (__thiscall *)(idSession *, int))v1->SetGUI)(session, v2);
    }
  }
}

// FUNC: public: static bool __cdecl idAsyncNetwork::GetMasterAddress(int,struct netadr_t &)
char __cdecl idAsyncNetwork::GetMasterAddress(int index, netadr_t *adr)
{
  idCVar *var; // eax
  idCVar *internalVar; // ecx
  char result; // al
  int *v5; // edi

  var = idAsyncNetwork::masters[index].var;
  if ( !var )
    return 0;
  internalVar = var->internalVar;
  if ( !*internalVar->value )
    return 0;
  if ( !byte_10DFB5D0[20 * index] || (internalVar->flags & 0x40000) != 0 )
  {
    BYTE2(var->internalVar->flags) &= ~4u;
    v5 = &byte_10DFB5C4[5 * index];
    if ( !Sys_StringToNetAdr(idAsyncNetwork::masters[index].var->internalVar->value, (netadr_t *)v5, 1) )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Failed to resolve master%d: %s\n",
        index,
        idAsyncNetwork::masters[index].var->internalVar->value);
      result = 0;
      *v5 = 0;
      v5[1] = 0;
      v5[2] = 0;
      byte_10DFB5D0[20 * index] = 1;
      return result;
    }
    if ( !LOWORD(MEMORY[0x10DFB5CC][5 * index]) )
      LOWORD(MEMORY[0x10DFB5CC][5 * index]) = atoi("27650");
    byte_10DFB5D0[20 * index] = 1;
  }
  *adr = *(netadr_t *)&byte_10DFB5C4[5 * index];
  return 1;
}

// FUNC: public: static void __cdecl idAsyncNetwork::WriteUserCmdDelta(class idBitMsg &,class usercmd_t const &,class usercmd_t const *)
void __cdecl idAsyncNetwork::WriteUserCmdDelta(idBitMsg *msg, const usercmd_t *cmd, const usercmd_t *base)
{
  if ( base )
  {
    idBitMsg::WriteDeltaLongCounter(msg, base->gameTime, cmd->gameTime);
    idBitMsg::WriteDelta(msg, base->buttons, cmd->buttons, -16);
    idBitMsg::WriteDelta(msg, base->mx, cmd->mx, -16);
    idBitMsg::WriteDelta(msg, base->my, cmd->my, -16);
    idBitMsg::WriteDelta(msg, base->forwardmove, cmd->forwardmove, -8);
    idBitMsg::WriteDelta(msg, base->rightmove, cmd->rightmove, -8);
    idBitMsg::WriteDelta(msg, base->upmove, cmd->upmove, -8);
    idBitMsg::WriteDelta(msg, base->angles[0], cmd->angles[0], -16);
    idBitMsg::WriteDelta(msg, base->angles[1], cmd->angles[1], -16);
    idBitMsg::WriteDelta(msg, base->angles[2], cmd->angles[2], -16);
  }
  else
  {
    idBitMsg::WriteBits(msg, cmd->gameTime, 32);
    idBitMsg::WriteBits(msg, cmd->buttons, -16);
    idBitMsg::WriteBits(msg, cmd->mx, -16);
    idBitMsg::WriteBits(msg, cmd->my, -16);
    idBitMsg::WriteBits(msg, cmd->forwardmove, -8);
    idBitMsg::WriteBits(msg, cmd->rightmove, -8);
    idBitMsg::WriteBits(msg, cmd->upmove, -8);
    idBitMsg::WriteBits(msg, cmd->angles[0], -16);
    idBitMsg::WriteBits(msg, cmd->angles[1], -16);
    idBitMsg::WriteBits(msg, cmd->angles[2], -16);
  }
}

// FUNC: public: static void __cdecl idAsyncNetwork::ReadUserCmdDelta(class idBitMsg const &,class usercmd_t &,class usercmd_t const *)
void __cdecl idAsyncNetwork::ReadUserCmdDelta(idBitMsg *msg, usercmd_t *cmd, const usercmd_t *base)
{
  int DeltaLongCounter; // eax
  int Bits; // eax

  cmd->gameFrame = 0;
  cmd->gameTime = 0;
  cmd->realTime = 0;
  cmd->duplicateCount = 0;
  *(_DWORD *)&cmd->buttons = 0;
  *(_DWORD *)&cmd->upmove = 0;
  *(_DWORD *)&cmd->angles[1] = 0;
  *(_DWORD *)&cmd->mx = 0;
  *(_DWORD *)&cmd->impulse = 0;
  cmd->sequence = 0;
  if ( base )
  {
    DeltaLongCounter = idBitMsg::ReadDeltaLongCounter(msg, base->gameTime);
    cmd->gameTime = DeltaLongCounter;
    cmd->realTime = DeltaLongCounter;
    cmd->buttons = idBitMsg::ReadDelta(msg, base->buttons, -16);
    cmd->mx = idBitMsg::ReadDelta(msg, base->mx, -16);
    cmd->my = idBitMsg::ReadDelta(msg, base->my, -16);
    cmd->forwardmove = idBitMsg::ReadDelta(msg, base->forwardmove, -8);
    cmd->rightmove = idBitMsg::ReadDelta(msg, base->rightmove, -8);
    cmd->upmove = idBitMsg::ReadDelta(msg, base->upmove, -8);
    cmd->angles[0] = idBitMsg::ReadDelta(msg, base->angles[0], -16);
    cmd->angles[1] = idBitMsg::ReadDelta(msg, base->angles[1], -16);
    cmd->angles[2] = idBitMsg::ReadDelta(msg, base->angles[2], -16);
  }
  else
  {
    Bits = idBitMsg::ReadBits(msg, 32);
    cmd->gameTime = Bits;
    cmd->realTime = Bits;
    cmd->buttons = idBitMsg::ReadBits(msg, -16);
    cmd->mx = idBitMsg::ReadBits(msg, -16);
    cmd->my = idBitMsg::ReadBits(msg, -16);
    cmd->forwardmove = idBitMsg::ReadBits(msg, -8);
    cmd->rightmove = idBitMsg::ReadBits(msg, -8);
    cmd->upmove = idBitMsg::ReadBits(msg, -8);
    cmd->angles[0] = idBitMsg::ReadBits(msg, -16);
    cmd->angles[1] = idBitMsg::ReadBits(msg, -16);
    cmd->angles[2] = idBitMsg::ReadBits(msg, -16);
  }
}

// FUNC: private: static void __cdecl idAsyncNetwork::SpawnServer_f(class idCmdArgs const &)
void __usercall idAsyncNetwork::SpawnServer_f(int a1@<edi>, const idCmdArgs *args)
{
  const char *v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax

  if ( args->argc > 1 )
    cvarSystem->SetCVarString(cvarSystem, "si_map", args->argv[1], 0);
  v2 = cvarSystem->GetCVarString(cvarSystem, "si_gameType");
  if ( !idStr::Icmp(v2, "singleplayer") )
    cvarSystem->SetCVarString(cvarSystem, "si_gameType", "DM", 0);
  v3 = cvarSystem->GetCVarInteger(cvarSystem, "net_serverDedicated");
  if ( !v3 )
  {
LABEL_8:
    if ( !renderSystem->IsOpenGLRunning(renderSystem) )
    {
      v5 = *(_DWORD *)common.type;
      v6 = cvarSystem->GetCVarInteger(cvarSystem, "net_serverDedicated");
      (*(void (**)(netadrtype_t, const char *, ...))(v5 + 136))(
        common.type,
        "OpenGL is not running, net_serverDedicated == %d",
        v6);
    }
    goto LABEL_10;
  }
  v4 = v3 - 1;
  if ( v4 )
  {
    if ( v4 != 1 )
      goto LABEL_10;
    goto LABEL_8;
  }
  if ( renderSystem->IsOpenGLRunning(renderSystem) )
  {
    sys->ShowConsole(sys, 1, 0);
    renderSystem->ShutdownOpenGL(renderSystem);
  }
  soundSystem->SetMute(soundSystem, 1);
  soundSystem->ShutdownHW(soundSystem);
LABEL_10:
  if ( idAsyncNetwork::server.active )
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "serverMapRestart");
  else
    idAsyncServer::Spawn(&idAsyncNetwork::server, a1);
  if ( cvarSystem->GetCVarBool(cvarSystem, "com_WriteSingleDeclFile") )
    declManager->WriteDeclFile(declManager);
}

// FUNC: private: static void __cdecl idAsyncNetwork::Connect_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::Connect_f(const idCmdArgs *args)
{
  if ( idAsyncNetwork::server.active )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "already running a server\n");
  }
  else if ( args->argc == 2 )
  {
    idAsyncClient::ConnectToServer(&idAsyncNetwork::client, args->argv[1]);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "USAGE: connect <serverName>\n");
  }
}

// FUNC: private: static void __cdecl idAsyncNetwork::WriteServerConfig_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::WriteServerConfig_f(const idCmdArgs *args)
{
  const char *v1; // eax

  if ( args->argc >= 2 )
  {
    if ( args->argc <= 1 )
      v1 = &entityFilter;
    else
      v1 = args->argv[1];
    (*(void (__thiscall **)(netadrtype_t, const char *, int, const char *))(*(_DWORD *)common.type + 80))(
      common.type,
      v1,
      1024,
      "seta");
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "USAGE: WriteServerConfig <filename>\n");
  }
}

// FUNC: private: static void __cdecl idAsyncNetwork::GetServerInfo_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::GetServerInfo_f(const idCmdArgs *args)
{
  if ( args->argc <= 1 )
    idAsyncClient::GetServerInfo(&idAsyncNetwork::client, &entityFilter);
  else
    idAsyncClient::GetServerInfo(&idAsyncNetwork::client, args->argv[1]);
}

// FUNC: private: static void __cdecl idAsyncNetwork::AddFriend_f(class idCmdArgs const &)
void __usercall idAsyncNetwork::AddFriend_f(int a1@<edi>, const idCmdArgs *args)
{
  unsigned int v2; // eax

  if ( !idAsyncNetwork::client.active )
  {
    if ( !idAsyncNetwork::server.active )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "idAsyncNetwork::AddFriend_f() - Network not initialized\n");
      return;
    }
LABEL_6:
    if ( idAsyncNetwork::server.localClientNum == -1 )
      goto LABEL_7;
    goto LABEL_8;
  }
  if ( idAsyncNetwork::client.clientState != CS_CONNECTED )
  {
LABEL_7:
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "idAsyncNetwork::AddFriend_f() - Can only be called when connected to a server or running a listen server\n");
    return;
  }
  if ( idAsyncNetwork::server.active )
    goto LABEL_6;
LABEL_8:
  if ( args->argc > 1 )
  {
    v2 = atoi(args->argv[1]);
    rvServerScan::AddToFriendsList(&idAsyncNetwork::client.serverList, a1, v2);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idAsyncNetwork::AddFriend_f() - Usage: addFriend <clientNum>\n");
  }
}

// FUNC: private: static void __cdecl idAsyncNetwork::RemoveFriend_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::RemoveFriend_f(const idCmdArgs *args)
{
  unsigned int v1; // eax

  if ( !idAsyncNetwork::client.active )
  {
    if ( !idAsyncNetwork::server.active )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "idAsyncNetwork::RemoveFriend_f() - Network not initialized\n");
      return;
    }
LABEL_6:
    if ( idAsyncNetwork::server.localClientNum == -1 )
      goto LABEL_7;
    goto LABEL_8;
  }
  if ( idAsyncNetwork::client.clientState != CS_CONNECTED )
  {
LABEL_7:
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "idAsyncNetwork::RemoveFriend_f() - Can only be called when connected to a server or running a listen server\n");
    return;
  }
  if ( idAsyncNetwork::server.active )
    goto LABEL_6;
LABEL_8:
  if ( args->argc > 1 )
  {
    v1 = atoi(args->argv[1]);
    rvServerScan::RemoveFromFriendsList(&idAsyncNetwork::client.serverList, v1);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idAsyncNetwork::RemoveFriend_f() - Usage: removeFriend <clientNum>\n");
  }
}

// FUNC: private: static void __cdecl idAsyncNetwork::Heartbeat_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::Heartbeat_f()
{
  if ( idAsyncNetwork::server.active )
    idAsyncServer::MasterHeartbeat(&idAsyncNetwork::server, 1);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "server is not running\n");
}

// FUNC: private: static void __cdecl idAsyncNetwork::Kick_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::Kick_f(const idCmdArgs *args)
{
  const char *v1; // edi
  char *v2; // eax
  int v3; // esi
  const char *v4; // eax
  idStr clientId; // [esp+0h] [ebp-2Ch] BYREF
  int v6; // [esp+28h] [ebp-4h]

  clientId.len = 0;
  clientId.alloced = 20;
  clientId.data = clientId.baseBuffer;
  clientId.baseBuffer[0] = 0;
  v6 = 0;
  if ( idAsyncNetwork::server.active )
  {
    v1 = (const char *)args;
    if ( args->argc <= 1 )
      v2 = (char *)&entityFilter;
    else
      v2 = args->argv[1];
    idStr::operator=(&clientId, v2);
    if ( idStr::IsNumeric(clientId.data) )
    {
      v3 = atoi(clientId.data);
      if ( idAsyncNetwork::server.localClientNum == v3 )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "can't kick the host\n");
      }
      else if ( args->argc <= 2 || (v1 = args->argv[2], idStr::Icmp(v1, "ban")) )
      {
        idAsyncServer::DropClient(&idAsyncNetwork::server, (int)v1, v3, "#str_107134");
      }
      else
      {
        v4 = networkSystem->GetClientGUID(networkSystem, v3);
        if ( v4 && *v4 )
        {
          game->AddGuidToBanList(game, v4);
          idAsyncServer::DropClient(&idAsyncNetwork::server, (int)v1, v3, "#str_107239");
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
            common.type,
            "idMultiplayerGame::HandleServerAdminBanPlayer:  client %d had bad guid!\n",
            v3);
        }
      }
      v6 = -1;
      idStr::FreeData(&clientId);
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "usage: kick <client number> [ban]\n");
      v6 = -1;
      idStr::FreeData(&clientId);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "server is not running\n");
    v6 = -1;
    idStr::FreeData(&clientId);
  }
}

// FUNC: private: static void __cdecl idAsyncNetwork::ListClients_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::ListClients_f()
{
  if ( idAsyncNetwork::server.active )
    idAsyncServer::ListClients(&idAsyncNetwork::server);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "server is not running\n");
}

// FUNC: private: static void __cdecl idAsyncNetwork::GetServers_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::GetServers_f()
{
  idAsyncClient::GetNETServers(&idAsyncNetwork::client, (char *)&entityFilter, (char *)&entityFilter);
}

// FUNC: private: static void __cdecl idAsyncNetwork::TestServerList_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::TestServerList_f(const idCmdArgs *args)
{
  const char *v1; // eax
  int v2; // eax

  if ( args->argc <= 1 )
    v1 = &entityFilter;
  else
    v1 = args->argv[1];
  v2 = atoi(v1);
  rvServerScan::AddTestServers(&idAsyncNetwork::client.serverList, v2);
}

// FUNC: private: static void __cdecl idAsyncNetwork::TestFriendsList_f(class idCmdArgs const &)
void __usercall idAsyncNetwork::TestFriendsList_f(int a1@<edi>, const idCmdArgs *args)
{
  const char *v2; // eax
  int v3; // eax

  if ( args->argc <= 1 )
    v2 = &entityFilter;
  else
    v2 = args->argv[1];
  v3 = atoi(v2);
  rvServerScan::AddTestFriends(&idAsyncNetwork::client.serverList, a1, v3);
}

// FUNC: private: static void __cdecl idAsyncNetwork::UpdateUI_f(class idCmdArgs const &)
void __cdecl idAsyncNetwork::UpdateUI_f(idCmdArgs *args)
{
  const char *v1; // eax
  int v2; // eax

  if ( args->argc == 2 )
  {
    if ( idAsyncNetwork::server.active )
    {
      v1 = idCmdArgs::Args(args, 1, -1, 0);
      v2 = atoi(v1);
      idAsyncServer::UpdateUI(&idAsyncNetwork::server, v2);
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "idAsyncNetwork::UpdateUI_f: server is not active\n");
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "idAsyncNetwork::UpdateUI_f: wrong arguments\n");
  }
}

// FUNC: public: static struct netadr_t __cdecl idAsyncNetwork::GetMasterAddress(void)
netadr_t *__cdecl idAsyncNetwork::GetMasterAddress(netadr_t *result)
{
  netadr_t *v1; // eax
  netadr_t ret; // [esp+0h] [ebp-Ch] BYREF

  idAsyncNetwork::GetMasterAddress(0, &ret);
  v1 = result;
  *result = *(netadr_t *)byte_10DFB5C4;
  return v1;
}

// FUNC: public: static void __cdecl idAsyncNetwork::BuildInvalidKeyMsg(class idStr &,bool)
void __cdecl idAsyncNetwork::BuildInvalidKeyMsg(idStr *msg, bool valid)
{
  const char *v2; // eax
  char *v3; // ebx
  int v4; // edi
  char v5; // cl
  int i; // eax
  char *data; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  char v11; // cl
  char *v12; // eax
  const char *v13; // eax
  char *v14; // edi
  int v15; // ebx
  char v16; // cl
  int j; // eax
  char *v18; // eax

  if ( !valid )
  {
    v2 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                         common.type,
                         "#str_107194",
                         -1);
    v3 = (char *)v2;
    if ( v2 )
    {
      v4 = strlen(v2) + msg->len;
      if ( v4 + 1 > msg->alloced )
        idStr::ReAllocate(msg, v4 + 1, 1);
      v5 = *v3;
      for ( i = 0; v5; v5 = v3[i] )
      {
        ++i;
        msg->data[msg->len - 1 + i] = v5;
      }
      data = msg->data;
      msg->len = v4;
      data[v4] = 0;
    }
  }
  v8 = msg->len + 1;
  v9 = msg->len + 2;
  if ( v9 > msg->alloced )
    idStr::ReAllocate(msg, v9, 1);
  v10 = 0;
  v11 = 10;
  do
  {
    ++v10;
    msg->data[msg->len - 1 + v10] = v11;
    v11 = pMsg[v10];
  }
  while ( v11 );
  v12 = msg->data;
  msg->len = v8;
  v12[v8] = 0;
  v13 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                        common.type,
                        "#str_104304",
                        -1);
  v14 = (char *)v13;
  if ( v13 )
  {
    v15 = strlen(v13) + msg->len;
    if ( v15 + 1 > msg->alloced )
      idStr::ReAllocate(msg, v15 + 1, 1);
    v16 = *v14;
    for ( j = 0; v16; v16 = v14[j] )
    {
      ++j;
      msg->data[msg->len - 1 + j] = v16;
    }
    v18 = msg->data;
    msg->len = v15;
    v18[v15] = 0;
  }
}
