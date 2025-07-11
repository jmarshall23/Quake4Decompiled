
// FUNC: public: void __thiscall rvServerScanGUI::RefreshComplete(void)
void __thiscall rvServerScanGUI::RefreshComplete(rvServerScanGUI *this)
{
  idUserInterface_vtbl *v2; // edi
  const char *v3; // eax
  char *v4; // eax
  int v5; // [esp-Ch] [ebp-10h]
  int v6; // [esp-8h] [ebp-Ch]

  if ( this->scanGUI )
  {
    v2 = this->scanGUI->__vftable;
    v3 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                         common.type,
                         "#str_107294",
                         -1,
                         idAsyncNetwork::client.serverList.numScanned);
    v4 = va(v3);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v2->SetStateString)(
      this->scanGUI,
      "loadNotice",
      v4,
      v5,
      v6);
    ((void (__thiscall *)(idUserInterface *, const char *, int))this->scanGUI->SetStateFloat)(
      this->scanGUI,
      "loadPct",
      1065353216);
    this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::RefreshComplete() - invalid scanGUI\n");
  }
}

// FUNC: public: void __thiscall rvServerScanGUI::Scanning(char const *)
void __thiscall rvServerScanGUI::Scanning(rvServerScanGUI *this, const char *ip)
{
  idUserInterface *scanGUI; // ecx
  idUserInterface_vtbl *v4; // ebx
  int v5; // edi
  const char *v6; // eax
  char *v7; // eax
  idUserInterface *v8; // ecx
  int v9; // [esp+4h] [ebp-1Ch]
  int v10; // [esp+8h] [ebp-18h]
  float v11; // [esp+10h] [ebp-10h]
  int numScanned; // [esp+18h] [ebp-8h]
  int numServers; // [esp+1Ch] [ebp-4h]

  scanGUI = this->scanGUI;
  if ( scanGUI )
  {
    v4 = scanGUI->__vftable;
    v5 = idAsyncNetwork::client.serverList.numServers;
    numScanned = idAsyncNetwork::client.serverList.numScanned;
    numServers = idAsyncNetwork::client.serverList.numServers;
    v6 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int, int, const char *))(*(_DWORD *)common.type + 168))(
                         common.type,
                         "#str_107297",
                         -1,
                         idAsyncNetwork::client.serverList.numScanned,
                         idAsyncNetwork::client.serverList.numServers,
                         ip);
    v7 = va(v6);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v4->SetStateString)(
      this->scanGUI,
      "loadNotice",
      v7,
      v9,
      v10);
    v8 = this->scanGUI;
    if ( v5 )
    {
      v11 = (double)numScanned / (double)numServers;
      ((void (__stdcall *)(const char *, _DWORD))v8->SetStateFloat)("loadPct", LODWORD(v11));
    }
    else
    {
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))v8->SetStateFloat)(v8, "loadPct", 0);
    }
    this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::Scanning() - invalid scanGUI\n");
  }
}

// FUNC: public: void __thiscall rvServerScan::SetPerformanceFlag(struct networkServer_t &)
void __thiscall rvServerScan::SetPerformanceFlag(rvServerScan *this, networkServer_t *server)
{
  const idDecl *v2; // ebx
  int v3; // edi
  idDeclBase *v4; // esi
  const idDecl *v5; // ebx
  int v6; // edi
  idDeclBase *v7; // esi
  const char *v8; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int maxPlayers; // [esp+18h] [ebp-Ch]
  double cpuSpeed; // [esp+1Ch] [ebp-8h]

  cpuSpeed = Sys_ClockTicksPerSecond() * 0.000000001;
  if ( (Sys_GetProcessorId() & 8) != 0 )
  {
    v2 = declManager->FindType(declManager, 4, "MPCPUAMDPlayerLimit", 0, 0);
    v3 = 0;
    maxPlayers = 4;
    if ( (int)v2[1].__vftable <= 0 )
      goto LABEL_24;
    do
    {
      if ( v3 < 0 || v3 >= (int)v2[1].__vftable )
        v4 = 0;
      else
        v4 = &v2[2].base[2 * v3];
      if ( idStr::Icmp((const char *)v4->GetName, "classname") )
      {
        if ( atof((const char *)v4->GetName) > cpuSpeed )
          break;
        maxPlayers = atoi((const char *)v4[1].GetName);
      }
      ++v3;
    }
    while ( v3 < (int)v2[1].__vftable );
  }
  else
  {
    v5 = declManager->FindType(declManager, 4, "MPCPUIntelPlayerLimit", 0, 0);
    v6 = 0;
    maxPlayers = 4;
    if ( (int)v5[1].__vftable <= 0 )
      goto LABEL_24;
    do
    {
      if ( v6 < 0 || v6 >= (int)v5[1].__vftable )
        v7 = 0;
      else
        v7 = &v5[2].base[2 * v6];
      if ( idStr::Icmp((const char *)v7->GetName, "classname") )
      {
        if ( atof((const char *)v7->GetName) > cpuSpeed )
          break;
        maxPlayers = atoi((const char *)v7[1].GetName);
      }
      ++v6;
    }
    while ( v6 < (int)v5[1].__vftable );
  }
  if ( maxPlayers >= 12 )
  {
    v8 = cvarSystem->GetCVarString(cvarSystem, "r_actualRenderer");
    if ( idStr::Icmp(v8, "ARB2") )
      maxPlayers -= 4;
  }
LABEL_24:
  if ( cvarSystem->GetCVarBool(cvarSystem, "developer") )
    maxPlayers = 16;
  Key = idDict::FindKey(&server->serverInfo, "si_maxPlayers");
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  server->performanceFiltered = atoi(data) > maxPlayers;
}

// FUNC: public: void __thiscall rvServerScan::Shutdown(void)
void __thiscall rvServerScan::Shutdown(rvServerScan *this)
{
  void **p_list; // esi
  int v2; // ebx

  p_list = (void **)&this->callbacks[0].list;
  v2 = 7;
  do
  {
    if ( *p_list )
      Memory::Free(*p_list);
    *p_list = 0;
    *(p_list - 3) = 0;
    *(p_list - 2) = 0;
    p_list += 4;
    --v2;
  }
  while ( v2 );
}

// FUNC: public: void __thiscall rvServerScan::RunFrame(void)
void __thiscall rvServerScan::RunFrame(rvServerScan *this)
{
  scan_state_t scanState; // eax
  int v3; // ebp
  int j; // edi
  int v5; // ebx
  int num; // eax
  inServer_t *v7; // eax
  inServer_t *v8; // edi
  int v9; // edi
  rvServerScanGUI **v10; // ebx
  const char *v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // edx
  _DWORD *v15; // eax
  int v16; // edi
  bool v17; // cc
  int i; // [esp+10h] [ebp-4h]

  scanState = this->scanState;
  v3 = 0;
  if ( scanState == IDLE )
    return;
  if ( scanState != NET_SCAN && scanState != 4 )
  {
    if ( Sys_Milliseconds() > this->scanStartTime + 999 )
    {
      this->scanState = IDLE;
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "Lan scan complete\n");
      for ( j = 0; j < this->callbacks[4].num; ++j )
        rvServerScanGUI::RefreshComplete(this->callbacks[4].list[j]);
    }
    return;
  }
  v5 = 0;
  while ( 1 )
  {
    num = this->scanServers.num;
    i = v5;
    if ( this->scanServers.num >= 32 )
      num = 32;
    if ( v5 >= num )
      break;
    v7 = &this->scanServers.list[v3];
    if ( v7->time )
    {
      if ( this->scanServers.list[v3].time < Sys_Milliseconds() )
      {
        if ( v5 >= 0 && v5 < this->scanServers.num )
        {
          v12 = this->scanServers.num - 1;
          this->scanServers.num = v12;
          v13 = v5;
          if ( v5 < v12 )
          {
            v14 = v3 * 20;
            do
            {
              v15 = (_DWORD *)((char *)this->scanServers.list + v14);
              *v15 = v15[5];
              v15[1] = v15[6];
              v15[2] = v15[7];
              v15[3] = v15[8];
              ++v13;
              v15[4] = v15[9];
              v14 += 20;
            }
            while ( v13 < this->scanServers.num );
          }
        }
        --v5;
        --v3;
        ++this->numScanned;
      }
LABEL_23:
      ++v5;
      ++v3;
    }
    else
    {
      idAsyncClient::GetServerInfo(&idAsyncNetwork::client, v7->adr);
      v8 = &this->scanServers.list[v3];
      v8->time = Sys_Milliseconds() + 999;
      v9 = 0;
      if ( this->callbacks[4].num <= 0 )
        goto LABEL_23;
      do
      {
        v10 = &this->callbacks[4].list[v9];
        v11 = Sys_NetAdrToString(this->scanServers.list[v3].adr);
        rvServerScanGUI::Scanning(*v10, v11);
        ++v9;
      }
      while ( v9 < this->callbacks[4].num );
      v5 = i + 1;
      ++v3;
    }
  }
  v16 = 0;
  if ( !this->scanServers.num && Sys_Milliseconds() > this->masterServerTimeout )
  {
    v17 = this->callbacks[4].num <= 0;
    this->scanState = IDLE;
    if ( !v17 )
    {
      do
        rvServerScanGUI::RefreshComplete(this->callbacks[4].list[v16++]);
      while ( v16 < this->callbacks[4].num );
    }
  }
}

// FUNC: public: void __thiscall rvServerScan::AddToFavoritesList(int)
void __thiscall rvServerScan::AddToFavoritesList(rvServerScan *this, int serverIndex)
{
  networkServer_t *v2; // esi
  const char *v3; // edi

  if ( serverIndex < 0 || serverIndex >= this->activeServers.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::AddToFavoritesList() - Invalid server '%d' specified\n",
      serverIndex);
  }
  else
  {
    v2 = &this->activeServers.list[serverIndex];
    if ( !v2->favorite )
    {
      v3 = va(
             "%s[%i.%i.%i.%i:%i]",
             g_favoritesList.internalVar->value,
             v2->adr.ip[0],
             v2->adr.ip[1],
             v2->adr.ip[2],
             v2->adr.ip[3],
             v2->adr.port);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
        common.type,
        "rvServerScanGUI::AddToFavoritesList:  was '%s', now '%s'\n",
        g_favoritesList.internalVar->value,
        v3);
      g_favoritesList.internalVar->InternalSetString(g_favoritesList.internalVar, v3);
      v2->favorite = 1;
    }
  }
}

// FUNC: public: void __thiscall rvServerScan::RemoveFromFavoritesList(int)
void __thiscall rvServerScan::RemoveFromFavoritesList(rvServerScan *this, int serverIndex)
{
  networkServer_t *v2; // esi
  char *v3; // eax
  const char *value; // edi
  const char *v5; // ebp
  unsigned int v6; // eax
  int v7; // ebp
  int v8; // eax
  char *data; // edx
  const char *v10; // ecx
  char v11; // al
  idStr stringVal; // [esp+4h] [ebp-2Ch] BYREF
  int v13; // [esp+2Ch] [ebp-4h]
  int serverIndexa; // [esp+34h] [ebp+4h]

  if ( serverIndex < 0 || serverIndex >= this->activeServers.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::RemoveFromFavoritesList() - Invalid server '%d' specified\n",
      serverIndex);
  }
  else
  {
    v2 = &this->activeServers.list[serverIndex];
    v3 = va("[%i.%i.%i.%i:%i]", v2->adr.ip[0], v2->adr.ip[1], v2->adr.ip[2], v2->adr.ip[3], v2->adr.port);
    value = g_favoritesList.internalVar->value;
    v5 = v3;
    serverIndexa = (int)v3;
    stringVal.len = 0;
    stringVal.alloced = 20;
    stringVal.data = stringVal.baseBuffer;
    stringVal.baseBuffer[0] = 0;
    if ( value )
    {
      v6 = (unsigned int)&value[strlen(value) + 1];
      v7 = v6 - (_DWORD)(value + 1);
      v8 = v6 - (_DWORD)value;
      if ( v8 > 20 )
        idStr::ReAllocate(&stringVal, v8, 1);
      data = stringVal.data;
      v10 = value;
      do
      {
        v11 = *v10;
        *data++ = *v10++;
      }
      while ( v11 );
      stringVal.len = v7;
      v5 = (const char *)serverIndexa;
    }
    v13 = 0;
    idStr::StripLeading(&stringVal, v5);
    idStr::StripTrailing(&stringVal, v5);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "rvServerScanGUI::RemoveFromFavoritesList:  was '%s', now '%s'\n",
      g_favoritesList.internalVar->value,
      stringVal.data);
    g_favoritesList.internalVar->InternalSetString(g_favoritesList.internalVar, stringVal.data);
    v2->favorite = 0;
    v13 = -1;
    idStr::FreeData(&stringVal);
  }
}

// FUNC: private: bool __thiscall rvServerScan::AddToFriendsList(char const *,char const *,char const *)
char __thiscall rvServerScan::AddToFriendsList(
        rvServerScan *this,
        const char *guid,
        const char *name,
        const char *clan)
{
  const char *value; // eax
  int v5; // ebx
  int v6; // esi
  int v7; // ecx
  int v8; // eax
  const char *v10; // esi

  value = g_friendsList.internalVar->value;
  v5 = 0;
  if ( *value )
  {
    do
      ++v5;
    while ( value[v5] );
  }
  v6 = 0;
  if ( *guid )
  {
    do
      ++v6;
    while ( guid[v6] );
  }
  v7 = 0;
  if ( *name )
  {
    do
      ++v7;
    while ( name[v7] );
  }
  v8 = 0;
  if ( *clan )
  {
    do
      ++v8;
    while ( clan[v8] );
  }
  if ( v6 + v7 + v8 + v5 + 8 < 0x4000 )
  {
    v10 = va("%s{[%s][%s][%s]}", g_friendsList.internalVar->value, guid, name, clan);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "rvServerScan::AddToFriendsList() - was '%s', now '%s'\n",
      g_friendsList.internalVar->value,
      v10);
    g_friendsList.internalVar->InternalSetString(g_friendsList.internalVar, v10);
    return 1;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::AddToFriendsList() - friends list too long, remove a friend before adding another");
    return 0;
  }
}

// FUNC: public: void __thiscall rvServerScan::AddToFriendsList(int)
void __userpurge rvServerScan::AddToFriendsList(rvServerScan *this@<ecx>, int a2@<edi>, unsigned int clientNum)
{
  const char *v3; // eax
  const char *v4; // ebp
  const char *value; // esi
  int Text; // eax
  int v7; // ecx
  idDict *v8; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  idDict *v11; // eax
  const idKeyValue *v12; // eax
  const char *v13; // eax
  char truncateClan[64]; // [esp+14h] [ebp-80h] BYREF
  char truncateName[64]; // [esp+54h] [ebp-40h] BYREF

  if ( idAsyncNetwork::server.active || idAsyncNetwork::client.clientState >= CS_CONNECTED )
  {
    if ( clientNum <= 0x1F && game->GetUserInfo(game, clientNum) )
    {
      v3 = networkSystem->GetClientGUID(networkSystem, clientNum);
      v4 = v3;
      if ( *v3 )
      {
        value = g_friendsList.internalVar->value;
        Text = idStr::FindText(value, v3, 0, 0, -1);
        if ( Text < 0 )
          goto LABEL_14;
        v7 = 0;
        if ( *value )
        {
          do
            ++v7;
          while ( value[v7] );
        }
        if ( Text >= v7 )
        {
LABEL_14:
          memset(truncateName, 0, sizeof(truncateName));
          memset(truncateClan, 0, sizeof(truncateClan));
          v8 = (idDict *)((int (__thiscall *)(idGame *, unsigned int, int))game->GetUserInfo)(game, clientNum, a2);
          Key = idDict::FindKey(v8, "ui_name");
          if ( Key )
            data = Key->value->data;
          else
            data = &entityFilter;
          idStr::Copynz(&truncateName[4], data, 64);
          v11 = (idDict *)game->GetUserInfo(game, clientNum);
          v12 = idDict::FindKey(v11, "ui_clan");
          if ( v12 )
            v13 = v12->value->data;
          else
            v13 = &entityFilter;
          idStr::Copynz(truncateClan, v13, 64);
          if ( rvServerScan::AddToFriendsList(this, v4, truncateName, truncateClan) )
            game->SetFriend(game, clientNum, 1);
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
            common.type,
            "rvServerScan::AddToFriendsList() - Not adding duplicate friend '%s'\n",
            v4);
        }
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "rvServerScan::AddToFriendsList() - Bad guid for client %d\n");
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "rvServerScan::AddToFriendsList() - Invalid client '%d' specified\n",
        clientNum);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::AddToFriendsList() - Must be connected to a server to add friends\n");
  }
}

// FUNC: public: bool __thiscall rvServerScan::IsAFriend(int)
bool __thiscall rvServerScan::IsAFriend(rvServerScan *this, unsigned int clientNum)
{
  const char *v3; // eax

  if ( idAsyncNetwork::server.active || idAsyncNetwork::client.clientState >= CS_CONNECTED )
  {
    if ( clientNum > 0x1F )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "rvServerScan::IsAFriend() - Invalid client '%d' specified\n",
        clientNum);
      return 0;
    }
    else
    {
      v3 = networkSystem->GetClientGUID(networkSystem, clientNum);
      if ( *v3 )
      {
        return idStr::FindText(g_friendsList.internalVar->value, v3, 0, 0, -1) >= 0;
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "rvServerScan::AddToFriendsList() - Bad guid for client %d\n");
        return 0;
      }
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::IsAFriend() - Must be connected to a server to query friends\n");
    return 0;
  }
}

// FUNC: private: void __thiscall rvServerScan::DumpAndClearFriends(void)
void __thiscall rvServerScan::DumpAndClearFriends(rvServerScan *this)
{
  idFile *v1; // eax
  idFile *v2; // esi

  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
    common.type,
    "rvServerScan::DumpAndClearFriends() - Dumping malformed friends cvar to %s\n",
    friendDumpName);
  v1 = fileSystem->OpenFileAppend(fileSystem, friendDumpName, 0, "fs_basepath");
  v2 = v1;
  if ( v1 )
  {
    v1->WriteString(
      v1,
      "This file contains corrupted friend information.  You may try and recover your friends list by grabbing the GUIDs "
      "from this dump and re-creating the g_friendsList cvar in your Quake4Config.cfg by hand\n");
    v2->WriteString(v2, "-- START DUMP --\n");
    v2->WriteString(v2, g_friendsList.internalVar->value);
    v2->WriteString(v2, "-- END DUMP --\n");
    fileSystem->CloseFile(fileSystem, v2);
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::DumpAndClearFriends() - Error opening file '%s', not dumping friends\n",
      friendDumpName);
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
    common.type,
    "rvServerScan::DumpAndClearFriends() - Clearing friends cvar\n");
  g_friendsList.internalVar->InternalSetString(g_friendsList.internalVar, &entityFilter);
  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "writeConfiguration\n");
}

// FUNC: public: int __thiscall rvServerScan::GetNumFriendsInFriendsList(void)
int __thiscall rvServerScan::GetNumFriendsInFriendsList(rvServerScan *this)
{
  const char *value; // esi
  int v2; // eax
  unsigned int v3; // eax
  int v4; // edi
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  int Char; // eax
  int i; // esi
  idStr friendsList; // [esp+4h] [ebp-2Ch] BYREF
  int v13; // [esp+2Ch] [ebp-4h]

  value = g_friendsList.internalVar->value;
  v2 = 0;
  friendsList.len = 0;
  friendsList.alloced = 20;
  friendsList.data = friendsList.baseBuffer;
  friendsList.baseBuffer[0] = 0;
  if ( value )
  {
    v3 = (unsigned int)&value[strlen(value) + 1];
    v4 = v3 - (_DWORD)(value + 1);
    v5 = v3 - (_DWORD)value;
    if ( v5 > 20 )
      idStr::ReAllocate(&friendsList, v5, 1);
    data = friendsList.data;
    v7 = value;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    v2 = v4;
    friendsList.len = v4;
  }
  v13 = 0;
  Char = idStr::FindChar(friendsList.data, 123, 0, v2);
  for ( i = 0; Char >= 0; Char = idStr::FindChar(friendsList.data, 123, Char + 1, friendsList.len) )
  {
    if ( Char >= friendsList.len )
      break;
    ++i;
  }
  v13 = -1;
  idStr::FreeData(&friendsList);
  return i;
}

// FUNC: private: bool __thiscall rvServerScan::ValidateGUID(class idStr &)
char __thiscall rvServerScan::ValidateGUID(rvServerScan *this, idStr *guid)
{
  int v3; // esi

  if ( guid->len != 11 )
    return 0;
  v3 = 0;
  while ( idStr::FindChar("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=", guid->data[v3], 0, -1) >= 0 )
  {
    if ( ++v3 >= guid->len )
      return 1;
  }
  return 0;
}

// FUNC: public: void __thiscall rvServerScan::GetFriendFromFriendsList(struct friend_t *,int)
void __thiscall rvServerScan::GetFriendFromFriendsList(rvServerScan *this, friend_t *newFriend, int num)
{
  const char *value; // esi
  int v4; // eax
  unsigned int v5; // eax
  int v6; // edi
  int v7; // eax
  char *data; // edx
  const char *v9; // ecx
  char v10; // al
  int v11; // esi
  int v12; // edi
  int Char; // edi
  int v14; // ebp
  idStr friendsList; // [esp+10h] [ebp-8Ch] BYREF
  idStr scanGuid; // [esp+30h] [ebp-6Ch] BYREF
  idStr scanClan; // [esp+50h] [ebp-4Ch] BYREF
  idStr scanName; // [esp+70h] [ebp-2Ch] BYREF
  int v20; // [esp+98h] [ebp-4h]

  value = g_friendsList.internalVar->value;
  v4 = 0;
  friendsList.len = 0;
  friendsList.alloced = 20;
  friendsList.data = friendsList.baseBuffer;
  friendsList.baseBuffer[0] = 0;
  if ( value )
  {
    v5 = (unsigned int)&value[strlen(value) + 1];
    v6 = v5 - (_DWORD)(value + 1);
    v7 = v5 - (_DWORD)value;
    if ( v7 > 20 )
      idStr::ReAllocate(&friendsList, v7, 1);
    data = friendsList.data;
    v9 = value;
    do
    {
      v10 = *v9;
      *data++ = *v9++;
    }
    while ( v10 );
    v4 = v6;
    friendsList.len = v6;
  }
  v20 = 0;
  v11 = idStr::FindChar(friendsList.data, 123, 0, v4) + 2;
  v12 = 0;
  if ( v11 >= 0 )
  {
    while ( v11 < friendsList.len )
    {
      if ( v12 == num )
      {
        idStr::Mid(&friendsList, &scanGuid, v11, 11);
        LOBYTE(v20) = 1;
        Char = idStr::FindChar(friendsList.data, 93, v11 + 13, friendsList.len);
        v14 = idStr::FindChar(friendsList.data, 93, Char + 1, friendsList.len);
        if ( Char < 0 || Char >= friendsList.len )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "rvServerScan::GetFriendFromFriendsList() - Malformed name after '%d' in friends list\n",
            v11);
          rvServerScan::DumpAndClearFriends(this);
        }
        else if ( v14 < 0 || v14 >= friendsList.len )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "rvServerScan::GetFriendFromFriendsList() - Malformed clan after '%d' in friends list\n",
            v11);
          rvServerScan::DumpAndClearFriends(this);
        }
        else
        {
          idStr::Mid(&friendsList, &scanName, v11 + 13, Char - v11 - 13);
          LOBYTE(v20) = 2;
          idStr::Mid(&friendsList, &scanClan, Char + 2, v14 - Char - 2);
          LOBYTE(v20) = 3;
          idStr::Copynz(newFriend->name, scanName.data, 64);
          idStr::Copynz(newFriend->clan, scanClan.data, 64);
          idStr::Copynz(newFriend->guid, scanGuid.data, 12);
          LOBYTE(v20) = 2;
          idStr::FreeData(&scanClan);
          LOBYTE(v20) = 1;
          idStr::FreeData(&scanName);
        }
        LOBYTE(v20) = 0;
        idStr::FreeData(&scanGuid);
        v20 = -1;
        idStr::FreeData(&friendsList);
        return;
      }
      v11 = idStr::FindChar(friendsList.data, 123, v11, friendsList.len) + 2;
      ++v12;
      if ( v11 < 0 )
        break;
    }
  }
  v20 = -1;
  idStr::FreeData(&friendsList);
}

// FUNC: int __cdecl CompareServersByPingAscending(int const *,int const *)
int __cdecl CompareServersByPingAscending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].ping
       - idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].ping;
}

// FUNC: int __cdecl CompareServersByPingDescending(int const *,int const *)
int __cdecl CompareServersByPingDescending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].ping
       - idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].ping;
}

// FUNC: int __cdecl CompareServersByNameAscending(int const *,int const *)
unsigned int __cdecl CompareServersByNameAscending(const int *serverOneIndex, const int *serverTwoIndex)
{
  networkServer_t *v2; // esi
  const idKeyValue *Key; // eax
  const char *data; // edi
  const idKeyValue *v5; // eax

  v2 = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex];
  Key = idDict::FindKey(&idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].serverInfo, "si_name");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  v5 = idDict::FindKey(&v2->serverInfo, "si_name");
  if ( v5 )
    return idStr::Icmp(v5->value->data, data);
  else
    return idStr::Icmp(&entityFilter, data);
}

// FUNC: int __cdecl CompareServersByNameDescending(int const *,int const *)
unsigned int __cdecl CompareServersByNameDescending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return -CompareServersByNameAscending(serverOneIndex, serverTwoIndex);
}

// FUNC: int __cdecl CompareServersByPlayersAscending(int const *,int const *)
int __cdecl CompareServersByPlayersAscending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].clients
       - idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].clients;
}

// FUNC: int __cdecl CompareServersByPlayersDescending(int const *,int const *)
int __cdecl CompareServersByPlayersDescending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].clients
       - idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].clients;
}

// FUNC: int __cdecl CompareServersByPlayersDescendingNonFull(int const *,int const *)
int __cdecl CompareServersByPlayersDescendingNonFull(const int *serverOneIndex, const int *serverTwoIndex)
{
  networkServer_t *v2; // esi
  networkServer_t *v3; // edi
  const idKeyValue *Key; // eax
  const char *data; // eax
  const idKeyValue *v7; // eax
  const char *v8; // eax
  int clients; // edi

  v2 = &idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex];
  v3 = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex];
  Key = idDict::FindKey(&v2->serverInfo, "si_maxPlayers");
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  if ( v2->clients >= atoi(data) )
    return -1;
  v7 = idDict::FindKey(&v3->serverInfo, "si_maxPlayers");
  if ( v7 )
    v8 = v7->value->data;
  else
    v8 = "0";
  clients = v3->clients;
  if ( clients < atoi(v8) )
    return v2->clients - clients;
  else
    return 1;
}

// FUNC: int __cdecl CompareServersByGameTypeDM(int const *,int const *)
int __cdecl CompareServersByGameTypeDM(const int *serverOneIndex, const int *serverTwoIndex)
{
  idDict *p_serverInfo; // edi
  networkServer_t *v3; // esi
  const idKeyValue *Key; // eax
  const char *data; // eax
  bool v6; // bl
  idDict *v7; // esi
  const idKeyValue *v8; // eax
  const char *v9; // eax
  bool v10; // al
  const idKeyValue *v12; // eax
  const char *v13; // esi
  const idKeyValue *v14; // eax

  p_serverInfo = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].serverInfo;
  v3 = &idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex];
  Key = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  v6 = idStr::Icmp(data, "DM") == 0;
  v7 = &v3->serverInfo;
  v8 = idDict::FindKey(v7, "si_gameType");
  if ( v8 )
    v9 = v8->value->data;
  else
    v9 = &entityFilter;
  v10 = idStr::Icmp(v9, "DM") == 0;
  if ( v6 )
  {
    if ( !v10 )
      return -1;
  }
  else if ( v10 )
  {
    return 1;
  }
  v12 = idDict::FindKey(v7, "si_gameType");
  if ( v12 )
    v13 = v12->value->data;
  else
    v13 = &entityFilter;
  v14 = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( v14 )
    return idStr::Icmp(v14->value->data, v13);
  else
    return idStr::Icmp(&entityFilter, v13);
}

// FUNC: int __cdecl CompareServersByGameTypeTeamDM(int const *,int const *)
int __cdecl CompareServersByGameTypeTeamDM(const int *serverOneIndex, const int *serverTwoIndex)
{
  idDict *p_serverInfo; // edi
  networkServer_t *v3; // esi
  const idKeyValue *Key; // eax
  const char *data; // eax
  bool v6; // bl
  idDict *v7; // esi
  const idKeyValue *v8; // eax
  const char *v9; // eax
  bool v10; // al
  const idKeyValue *v12; // eax
  const char *v13; // esi
  const idKeyValue *v14; // eax

  p_serverInfo = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].serverInfo;
  v3 = &idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex];
  Key = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  v6 = idStr::Icmp(data, "Team DM") == 0;
  v7 = &v3->serverInfo;
  v8 = idDict::FindKey(v7, "si_gameType");
  if ( v8 )
    v9 = v8->value->data;
  else
    v9 = &entityFilter;
  v10 = idStr::Icmp(v9, "Team DM") == 0;
  if ( v6 )
  {
    if ( !v10 )
      return -1;
  }
  else if ( v10 )
  {
    return 1;
  }
  v12 = idDict::FindKey(v7, "si_gameType");
  if ( v12 )
    v13 = v12->value->data;
  else
    v13 = &entityFilter;
  v14 = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( v14 )
    return idStr::Icmp(v14->value->data, v13);
  else
    return idStr::Icmp(&entityFilter, v13);
}

// FUNC: int __cdecl CompareServersByGameTypeTourney(int const *,int const *)
int __cdecl CompareServersByGameTypeTourney(const int *serverOneIndex, const int *serverTwoIndex)
{
  idDict *p_serverInfo; // edi
  networkServer_t *v3; // esi
  const idKeyValue *Key; // eax
  const char *data; // eax
  bool v6; // bl
  idDict *v7; // esi
  const idKeyValue *v8; // eax
  const char *v9; // eax
  bool v10; // al
  const idKeyValue *v12; // eax
  const char *v13; // esi
  const idKeyValue *v14; // eax

  p_serverInfo = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].serverInfo;
  v3 = &idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex];
  Key = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  v6 = idStr::Icmp(data, "Tourney") == 0;
  v7 = &v3->serverInfo;
  v8 = idDict::FindKey(v7, "si_gameType");
  if ( v8 )
    v9 = v8->value->data;
  else
    v9 = &entityFilter;
  v10 = idStr::Icmp(v9, "Tourney") == 0;
  if ( v6 )
  {
    if ( !v10 )
      return -1;
  }
  else if ( v10 )
  {
    return 1;
  }
  v12 = idDict::FindKey(v7, "si_gameType");
  if ( v12 )
    v13 = v12->value->data;
  else
    v13 = &entityFilter;
  v14 = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( v14 )
    return idStr::Icmp(v14->value->data, v13);
  else
    return idStr::Icmp(&entityFilter, v13);
}

// FUNC: int __cdecl CompareServersByGameTypeCTF(int const *,int const *)
int __cdecl CompareServersByGameTypeCTF(const int *serverOneIndex, const int *serverTwoIndex)
{
  idDict *p_serverInfo; // edi
  networkServer_t *v3; // esi
  const idKeyValue *Key; // eax
  const char *data; // eax
  bool v6; // bl
  idDict *v7; // esi
  const idKeyValue *v8; // eax
  const char *v9; // eax
  bool v10; // al
  const idKeyValue *v12; // eax
  const char *v13; // esi
  const idKeyValue *v14; // eax

  p_serverInfo = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].serverInfo;
  v3 = &idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex];
  Key = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  v6 = idStr::Icmp(data, "CTF") == 0;
  v7 = &v3->serverInfo;
  v8 = idDict::FindKey(v7, "si_gameType");
  if ( v8 )
    v9 = v8->value->data;
  else
    v9 = &entityFilter;
  v10 = idStr::Icmp(v9, "CTF") == 0;
  if ( v6 )
  {
    if ( !v10 )
      return -1;
  }
  else if ( v10 )
  {
    return 1;
  }
  v12 = idDict::FindKey(v7, "si_gameType");
  if ( v12 )
    v13 = v12->value->data;
  else
    v13 = &entityFilter;
  v14 = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( v14 )
    return idStr::Icmp(v14->value->data, v13);
  else
    return idStr::Icmp(&entityFilter, v13);
}

// FUNC: int __cdecl CompareServersByGameTypeArenaCTF(int const *,int const *)
int __cdecl CompareServersByGameTypeArenaCTF(const int *serverOneIndex, const int *serverTwoIndex)
{
  idDict *p_serverInfo; // edi
  networkServer_t *v3; // esi
  const idKeyValue *Key; // eax
  const char *data; // eax
  bool v6; // bl
  idDict *v7; // esi
  const idKeyValue *v8; // eax
  const char *v9; // eax
  bool v10; // al
  const idKeyValue *v12; // eax
  const char *v13; // esi
  const idKeyValue *v14; // eax

  p_serverInfo = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].serverInfo;
  v3 = &idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex];
  Key = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  v6 = idStr::Icmp(data, "Arena CTF") == 0;
  v7 = &v3->serverInfo;
  v8 = idDict::FindKey(v7, "si_gameType");
  if ( v8 )
    v9 = v8->value->data;
  else
    v9 = &entityFilter;
  v10 = idStr::Icmp(v9, "Arena CTF") == 0;
  if ( v6 )
  {
    if ( !v10 )
      return -1;
  }
  else if ( v10 )
  {
    return 1;
  }
  v12 = idDict::FindKey(v7, "si_gameType");
  if ( v12 )
    v13 = v12->value->data;
  else
    v13 = &entityFilter;
  v14 = idDict::FindKey(p_serverInfo, "si_gameType");
  if ( v14 )
    return idStr::Icmp(v14->value->data, v13);
  else
    return idStr::Icmp(&entityFilter, v13);
}

// FUNC: int __cdecl CompareServersByMapAscending(int const *,int const *)
unsigned int __cdecl CompareServersByMapAscending(const int *serverOneIndex, const int *serverTwoIndex)
{
  networkServer_t *v2; // esi
  const idKeyValue *Key; // eax
  const char *data; // edi
  const idKeyValue *v5; // eax

  v2 = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex];
  Key = idDict::FindKey(&idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].serverInfo, "si_map");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  v5 = idDict::FindKey(&v2->serverInfo, "si_map");
  if ( v5 )
    return idStr::Icmp(v5->value->data, data);
  else
    return idStr::Icmp(&entityFilter, data);
}

// FUNC: int __cdecl CompareServersByMapDescending(int const *,int const *)
unsigned int __cdecl CompareServersByMapDescending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return -CompareServersByMapAscending(serverOneIndex, serverTwoIndex);
}

// FUNC: int __cdecl CompareServersByFavoriteAscending(int const *,int const *)
int __cdecl CompareServersByFavoriteAscending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].favorite
       - idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].favorite;
}

// FUNC: int __cdecl CompareServersByFavoriteDescending(int const *,int const *)
int __cdecl CompareServersByFavoriteDescending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].favorite
       - idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].favorite;
}

// FUNC: int __cdecl CompareServersByLockedAscending(int const *,int const *)
int __cdecl CompareServersByLockedAscending(const int *serverOneIndex, const int *serverTwoIndex)
{
  networkServer_t *v2; // esi
  const idKeyValue *Key; // eax
  const char *data; // edi
  const idKeyValue *v5; // eax
  const char *v6; // eax
  bool v7; // bl

  v2 = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex];
  Key = idDict::FindKey(&idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].serverInfo, "si_usePass");
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  v5 = idDict::FindKey(&v2->serverInfo, "si_usePass");
  if ( v5 )
    v6 = v5->value->data;
  else
    v6 = "0";
  v7 = atoi(v6) != 0;
  return (atoi(data) != 0) - v7;
}

// FUNC: int __cdecl CompareServersByLockedDescending(int const *,int const *)
int __cdecl CompareServersByLockedDescending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return -CompareServersByLockedAscending(serverOneIndex, serverTwoIndex);
}

// FUNC: int __cdecl CompareServersByDedicatedAscending(int const *,int const *)
int __cdecl CompareServersByDedicatedAscending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].dedicated
       - idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].dedicated;
}

// FUNC: int __cdecl CompareServersByDedicatedDescending(int const *,int const *)
int __cdecl CompareServersByDedicatedDescending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex].dedicated
       - idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].dedicated;
}

// FUNC: int __cdecl CompareServersByPBAscending(int const *,int const *)
int __cdecl CompareServersByPBAscending(const int *serverOneIndex, const int *serverTwoIndex)
{
  networkServer_t *v2; // esi
  const idKeyValue *Key; // eax
  const char *data; // edi
  const idKeyValue *v5; // eax
  const char *v6; // eax
  bool v7; // bl

  v2 = &idAsyncNetwork::client.serverList.activeServers.list[*serverOneIndex];
  Key = idDict::FindKey(
          &idAsyncNetwork::client.serverList.activeServers.list[*serverTwoIndex].serverInfo,
          "sv_punkbuster");
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  v5 = idDict::FindKey(&v2->serverInfo, "sv_punkbuster");
  if ( v5 )
    v6 = v5->value->data;
  else
    v6 = "0";
  v7 = atoi(v6) != 0;
  return (atoi(data) != 0) - v7;
}

// FUNC: int __cdecl CompareServersByPBDescending(int const *,int const *)
int __cdecl CompareServersByPBDescending(const int *serverOneIndex, const int *serverTwoIndex)
{
  return -CompareServersByPBAscending(serverOneIndex, serverTwoIndex);
}

// FUNC: public: void __thiscall rvServerScanGUI::UpdateServerScanGUI(void)
void __thiscall rvServerScanGUI::UpdateServerScanGUI(rvServerScanGUI *this)
{
  int second; // ebx
  const char *v3; // edi
  idDict *v4; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int v7; // eax
  int num; // edi
  rvPair<int,int> *v9; // edx
  const char *v10; // edi
  idDict *v11; // eax
  const idKeyValue *v12; // eax
  const char *v13; // eax
  int v14; // edi
  idUserInterface_vtbl *v15; // ebx
  networkServer_t *v16; // edi
  const char *v17; // eax
  int v18; // ebx
  idUserInterface_vtbl *v19; // ebp
  char *v20; // eax
  idDict *p_serverInfo; // edi
  const idKeyValue *v22; // eax
  const char *v23; // ebx
  const idDecl *v24; // eax
  const idKeyValue *v25; // eax
  idUserInterface_vtbl *v26; // ebp
  const char *v27; // eax
  char *v28; // eax
  const idKeyValue *v29; // eax
  const char *v30; // eax
  idUserInterface_vtbl *v31; // ebx
  const char *v32; // eax
  char *v33; // eax
  const idKeyValue *v34; // eax
  const char *v35; // eax
  const idKeyValue *v36; // eax
  const char *v37; // eax
  const idKeyValue *v38; // eax
  const idKeyValue *v39; // eax
  const char *v40; // eax
  idUserInterface_vtbl *v41; // ebx
  const char *v42; // eax
  char *v43; // eax
  const idKeyValue *v44; // eax
  const char *v45; // eax
  int v46; // eax
  idUserInterface_vtbl *v47; // ebx
  const char *v48; // eax
  char *v49; // eax
  const idKeyValue *v50; // eax
  const char *v51; // eax
  int v52; // eax
  idUserInterface_vtbl *v53; // ebx
  const char *v54; // eax
  char *v55; // eax
  const idKeyValue *v56; // eax
  const char *v57; // eax
  int v58; // eax
  idUserInterface_vtbl *v59; // ebx
  const char *v60; // eax
  char *v61; // eax
  const idKeyValue *v62; // eax
  const char *v63; // eax
  int v64; // eax
  idUserInterface_vtbl *v65; // edi
  const char *v66; // eax
  char *v67; // eax
  idUserInterface_vtbl *v68; // ebp
  int scanStartTime; // ebx
  int v70; // edi
  const char *v71; // [esp+0h] [ebp-24h]
  const char *v72; // [esp+0h] [ebp-24h]
  const char *v73; // [esp+0h] [ebp-24h]
  const char *v74; // [esp+0h] [ebp-24h]
  const char *v75; // [esp+0h] [ebp-24h]
  const char *v76; // [esp+0h] [ebp-24h]
  const char *v77; // [esp+0h] [ebp-24h]
  const char *v78; // [esp+0h] [ebp-24h]
  int v79; // [esp+4h] [ebp-20h]
  int v80; // [esp+4h] [ebp-20h]
  int v81; // [esp+4h] [ebp-20h]
  int v82; // [esp+4h] [ebp-20h]
  int v83; // [esp+4h] [ebp-20h]
  int v84; // [esp+4h] [ebp-20h]
  int v85; // [esp+4h] [ebp-20h]
  const char *v86; // [esp+8h] [ebp-1Ch]
  int v87; // [esp+8h] [ebp-1Ch]
  int v88; // [esp+8h] [ebp-1Ch]
  const char *v89; // [esp+8h] [ebp-1Ch]
  int v90; // [esp+8h] [ebp-1Ch]
  int v91; // [esp+8h] [ebp-1Ch]
  int v92; // [esp+8h] [ebp-1Ch]
  int v93; // [esp+8h] [ebp-1Ch]
  int v94; // [esp+8h] [ebp-1Ch]
  float v95; // [esp+8h] [ebp-1Ch]
  char (*nickname)[32]; // [esp+1Ch] [ebp-8h]

  if ( sessLocal.guiActive != sessLocal.guiMainMenu )
    return;
  second = 0;
  if ( idAsyncNetwork::client.serverList.lastScan == 4 )
  {
    v3 = va("%s_hover", this->friendsListName.data);
    v4 = (idDict *)this->scanGUI->State(this->scanGUI);
    Key = idDict::FindKey(v4, v3);
    if ( Key )
      data = Key->value->data;
    else
      data = "-1";
    v7 = atoi(data);
    num = this->friendsList.num;
    if ( v7 >= 0 && v7 < num )
    {
      v9 = &this->friendsList.list[v7];
      if ( !idAsyncNetwork::client.serverList.activeFriends.list[v9->first].online )
        goto LABEL_72;
      second = v9->second;
    }
  }
  else
  {
    v10 = va("%s_hover", this->listName.data);
    v11 = (idDict *)this->scanGUI->State(this->scanGUI);
    v12 = idDict::FindKey(v11, v10);
    if ( v12 )
      v13 = v12->value->data;
    else
      v13 = "-1";
    v7 = atoi(v13);
    num = this->serverList.num;
    second = v7;
  }
  if ( v7 != -1 && v7 < num )
  {
    this->scanGUI->SetStateInt(this->scanGUI, "serverinfo_visible", 1);
    v14 = second;
    v15 = this->scanGUI->__vftable;
    v16 = &idAsyncNetwork::client.serverList.activeServers.list[v14];
    v17 = Sys_NetAdrToString(v16->adr);
    v15->SetStateString(this->scanGUI, "server_tooltip_ip", v17);
    v18 = 0;
    nickname = v16->nickname;
    do
    {
      v19 = this->scanGUI->__vftable;
      if ( v18 >= v16->clients )
        v86 = &entityFilter;
      else
        v86 = (const char *)nickname;
      v20 = va("server_tooltip_playerlist_item_%d", v18);
      v19->SetStateString(this->scanGUI, v20, v86);
      ++nickname;
      ++v18;
    }
    while ( v18 < 32 );
    p_serverInfo = &v16->serverInfo;
    v22 = idDict::FindKey(p_serverInfo, "si_map");
    if ( v22 )
      v23 = v22->value->data;
    else
      v23 = &entityFilter;
    v24 = declManager->FindType(declManager, 17, v23, 0, 0);
    if ( v24 )
    {
      v25 = idDict::FindKey((idDict *)&v24[1], "name");
      if ( v25 )
        v23 = v25->value->data;
      v23 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                            common.type,
                            v23,
                            -1);
    }
    v26 = this->scanGUI->__vftable;
    v27 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, const char *))(*(_DWORD *)common.type
                                                                                             + 168))(
                          common.type,
                          "#str_107702",
                          -1,
                          v23);
    v28 = va("%s: %s", v27, v71);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v26->SetStateString)(
      this->scanGUI,
      "server_tooltip_settingslist_item_0",
      v28,
      v79,
      v87);
    v29 = idDict::FindKey(p_serverInfo, "si_timeLimit");
    if ( v29 )
      v30 = v29->value->data;
    else
      v30 = &entityFilter;
    v31 = this->scanGUI->__vftable;
    v32 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, const char *))(*(_DWORD *)common.type
                                                                                             + 168))(
                          common.type,
                          "#str_107659",
                          -1,
                          v30);
    v33 = va("%s: %s", v32, v72);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v31->SetStateString)(
      this->scanGUI,
      "server_tooltip_settingslist_item_1",
      v33,
      v80,
      v88);
    v34 = idDict::FindKey(p_serverInfo, "si_gameType");
    if ( v34 )
      v35 = v34->value->data;
    else
      v35 = &entityFilter;
    if ( idStr::Icmp(v35, "CTF")
      && ((v36 = idDict::FindKey(p_serverInfo, "si_gameType")) == 0 ? (v37 = &entityFilter) : (v37 = v36->value->data),
          idStr::Icmp(v37, "Arena CTF")) )
    {
      v38 = idDict::FindKey(p_serverInfo, "si_fragLimit");
      if ( v38 )
        v89 = v38->value->data;
      else
        v89 = &entityFilter;
      v73 = "#str_107660";
    }
    else
    {
      v39 = idDict::FindKey(p_serverInfo, "si_captureLimit");
      if ( v39 )
        v40 = v39->value->data;
      else
        v40 = &entityFilter;
      v89 = v40;
      v73 = "#str_107661";
    }
    v41 = this->scanGUI->__vftable;
    v42 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, const char *))(*(_DWORD *)common.type
                                                                                             + 168))(
                          common.type,
                          v73,
                          -1,
                          v89);
    v43 = va("%s: %s", v42, v74);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v41->SetStateString)(
      this->scanGUI,
      "server_tooltip_settingslist_item_2",
      v43,
      v81,
      v90);
    v44 = idDict::FindKey(p_serverInfo, "si_teamDamage");
    if ( v44 )
      v45 = v44->value->data;
    else
      v45 = "0";
    if ( atoi(v45) )
      v46 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107703",
              -1);
    else
      v46 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107704",
              -1);
    v47 = this->scanGUI->__vftable;
    v48 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                          common.type,
                          "#str_107664",
                          -1,
                          v46);
    v49 = va("%s: %s", v48, v75);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v47->SetStateString)(
      this->scanGUI,
      "server_tooltip_settingslist_item_3",
      v49,
      v82,
      v91);
    v50 = idDict::FindKey(p_serverInfo, "si_autobalance");
    if ( v50 )
      v51 = v50->value->data;
    else
      v51 = "0";
    if ( atoi(v51) )
      v52 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107703",
              -1);
    else
      v52 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107704",
              -1);
    v53 = this->scanGUI->__vftable;
    v54 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                          common.type,
                          "#str_107666",
                          -1,
                          v52);
    v55 = va("%s: %s", v54, v76);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v53->SetStateString)(
      this->scanGUI,
      "server_tooltip_settingslist_item_4",
      v55,
      v83,
      v92);
    v56 = idDict::FindKey(p_serverInfo, "si_pure");
    if ( v56 )
      v57 = v56->value->data;
    else
      v57 = "0";
    if ( atoi(v57) )
      v58 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107703",
              -1);
    else
      v58 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107704",
              -1);
    v59 = this->scanGUI->__vftable;
    v60 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                          common.type,
                          "#str_107662",
                          -1,
                          v58);
    v61 = va("%s: %s", v60, v77);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v59->SetStateString)(
      this->scanGUI,
      "server_tooltip_settingslist_item_5",
      v61,
      v84,
      v93);
    v62 = idDict::FindKey(p_serverInfo, "si_spectators");
    if ( v62 )
      v63 = v62->value->data;
    else
      v63 = "0";
    if ( atoi(v63) )
      v64 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107703",
              -1);
    else
      v64 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_107704",
              -1);
    v65 = this->scanGUI->__vftable;
    v66 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                          common.type,
                          "#str_104254",
                          -1,
                          v64);
    v67 = va("%s: %s", v66, v78);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v65->SetStateString)(
      this->scanGUI,
      "server_tooltip_settingslist_item_6",
      v67,
      v85,
      v94);
    this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
    goto LABEL_73;
  }
LABEL_72:
  this->scanGUI->SetStateInt(this->scanGUI, "serverinfo_visible", 0);
LABEL_73:
  if ( idAsyncNetwork::client.serverList.scanState == LAN_SCAN )
  {
    if ( idAsyncNetwork::client.serverList.scanStartTime )
    {
      v68 = this->scanGUI->__vftable;
      scanStartTime = idAsyncNetwork::client.serverList.scanStartTime;
      v70 = idAsyncNetwork::client.serverList.scanStartTime + 999;
      v95 = (double)(Sys_Milliseconds() - scanStartTime) / (double)(v70 - scanStartTime);
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))v68->SetStateFloat)(
        this->scanGUI,
        "loadPct",
        LODWORD(v95));
    }
  }
}

// FUNC: public: void __thiscall rvServerScanGUI::StartScan(bool)
void __userpurge rvServerScanGUI::StartScan(rvServerScanGUI *this@<ecx>, int a2@<ebp>, int a3@<edi>, bool refreshOnly)
{
  int i; // edi
  idUserInterface *scanGUI; // ebp
  idUserInterface_vtbl *v7; // ebx
  char *v8; // eax
  idUserInterface *v9; // ebp
  idUserInterface_vtbl *v10; // ebx
  char *v11; // eax
  int j; // edi
  idUserInterface *v13; // ebp
  idUserInterface_vtbl *v14; // ebx
  char *v15; // eax
  idUserInterface *v16; // ebp
  idUserInterface_vtbl *v17; // ebx
  char *v18; // eax
  idUserInterface *v19; // edi
  idUserInterface_vtbl *v20; // ebp
  int v21; // eax
  idUserInterface *v22; // edi
  idUserInterface_vtbl *v23; // ebp
  int v24; // eax
  idUserInterface *v25; // edi
  idUserInterface_vtbl *v26; // ebp
  char *v27; // eax
  const char *v28; // [esp+4h] [ebp-18h]

  if ( !this->scanGUI )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::StartScan() - invalid scanGUI\n");
    return;
  }
  for ( i = 0; i < this->serverList.num; ++i )
  {
    scanGUI = this->scanGUI;
    v7 = this->scanGUI->__vftable;
    v8 = va("%s_item_%i", this->listName.data, i);
    v7->SetStateString(scanGUI, v8, &entityFilter);
    v9 = this->scanGUI;
    v10 = this->scanGUI->__vftable;
    v11 = va("%s_item_%i_greyed", this->listName.data, i);
    v10->SetStateBool(v9, v11, 0);
  }
  for ( j = 0; j < this->friendsList.num; ++j )
  {
    v13 = this->scanGUI;
    v14 = this->scanGUI->__vftable;
    v15 = va("%s_item_%i", this->friendsListName.data, j);
    v14->SetStateString(v13, v15, &entityFilter);
    v16 = this->scanGUI;
    v17 = this->scanGUI->__vftable;
    v18 = va("%s_item_%i_greyed", this->friendsListName.data, j);
    v17->SetStateBool(v16, v18, 0);
  }
  this->currentSort[0] = 0;
  this->currentSort[1] = 0;
  this->currentSort[2] = 0;
  this->currentSort[3] = 0;
  this->currentSort[4] = 0;
  this->currentSort[5] = 0;
  this->currentSort[6] = 0;
  this->currentSort[7] = 0;
  this->currentSort[8] = 0;
  if ( idAsyncNetwork::client.serverList.scanState == LAN_SCAN )
  {
    v28 = "#str_107293";
LABEL_12:
    v19 = this->scanGUI;
    v20 = this->scanGUI->__vftable;
    v21 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, int))(*(_DWORD *)common.type + 168))(
            common.type,
            v28,
            -1,
            a3,
            a2);
    v20->SetStateString(v19, "loadNotice", (const char *)v21);
    goto LABEL_13;
  }
  if ( !refreshOnly )
  {
    v28 = "#str_107736";
    goto LABEL_12;
  }
  ((void (__thiscall *)(idUserInterface *, const char *, const char *, int, int))this->scanGUI->SetStateString)(
    this->scanGUI,
    "loadNotice",
    &entityFilter,
    a3,
    a2);
LABEL_13:
  v22 = this->scanGUI;
  v23 = this->scanGUI->__vftable;
  v24 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
          common.type,
          "#str_107292",
          -1);
  v23->SetStateString(v22, "sortNotice", (const char *)v24);
  ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))this->scanGUI->SetStateFloat)(
    this->scanGUI,
    "loadPct",
    0);
  v25 = this->scanGUI;
  v26 = this->scanGUI->__vftable;
  v27 = va("%s_item_0", this->friendsListName.data);
  v26->SetStateString(v25, v27, &entityFilter);
  this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
  if ( this->serverList.list )
    Memory::Free(this->serverList.list);
  this->serverList.list = 0;
  this->serverList.num = 0;
  this->serverList.size = 0;
  if ( this->friendsList.list )
    Memory::Free(this->friendsList.list);
  this->friendsList.list = 0;
  this->friendsList.num = 0;
  this->friendsList.size = 0;
}

// FUNC: public: struct networkServer_t & __thiscall rvServerScanGUI::GetServer(int)
networkServer_t *__thiscall rvServerScanGUI::GetServer(rvServerScanGUI *this, int listIndex)
{
  return &idAsyncNetwork::client.serverList.activeServers.list[this->serverList.list[listIndex]];
}

// FUNC: public: void __thiscall rvServerScanGUI::Clear(void)
void __thiscall rvServerScanGUI::Clear(rvServerScanGUI *this)
{
  int i; // edi
  idUserInterface_vtbl *v3; // ebp
  char *v4; // eax
  idUserInterface_vtbl *v5; // ebp
  char *v6; // eax
  int j; // edi
  idUserInterface_vtbl *v8; // ebp
  char *v9; // eax

  if ( this->scanGUI )
  {
    for ( i = 0; i < this->serverList.num; ++i )
    {
      v3 = this->scanGUI->__vftable;
      v4 = va("%s_item_%i", this->listName.data, i);
      v3->SetStateString(this->scanGUI, v4, &entityFilter);
      v5 = this->scanGUI->__vftable;
      v6 = va("%s_item_%i_greyed", this->listName.data, i);
      v5->SetStateBool(this->scanGUI, v6, 0);
    }
    for ( j = 0; j < this->friendsList.num; ++j )
    {
      v8 = this->scanGUI->__vftable;
      v9 = va("%s_item_%i", this->friendsListName.data, j);
      v8->SetStateString(this->scanGUI, v9, &entityFilter);
    }
    if ( this->serverList.list )
      Memory::Free(this->serverList.list);
    this->serverList.list = 0;
    this->serverList.num = 0;
    this->serverList.size = 0;
    if ( this->friendsList.list )
      Memory::Free(this->friendsList.list);
    this->friendsList.list = 0;
    this->friendsList.num = 0;
    this->friendsList.size = 0;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::Clear() - invalid scanGUI\n");
  }
}

// FUNC: public: bool __thiscall rvServerScanGUI::IsAFavorite(int)
bool __thiscall rvServerScanGUI::IsAFavorite(rvServerScanGUI *this, int listIndex)
{
  if ( listIndex >= 0 && listIndex < this->serverList.num )
    return idAsyncNetwork::client.serverList.activeServers.list[this->serverList.list[listIndex]].favorite;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
    common.type,
    "rvServerScanGUI::IsAFavorite() - Invalid selected server '%d'\n",
    listIndex);
  return 0;
}

// FUNC: public: bool __thiscall rvServerScanGUI::IsPerformanceFiltered(int)
bool __thiscall rvServerScanGUI::IsPerformanceFiltered(rvServerScanGUI *this, int listIndex)
{
  return idAsyncNetwork::client.serverList.activeServers.list[this->serverList.list[listIndex]].performanceFiltered;
}

// FUNC: public: void __thiscall rvServerScanGUI::ServerSelected(int)
void __thiscall rvServerScanGUI::ServerSelected(rvServerScanGUI *this, int listIndex)
{
  const idKeyValue *Key; // eax
  const char *data; // eax
  idUserInterface_vtbl *v5; // edi
  int v6; // eax
  char screenshot[1024]; // [esp+8h] [ebp-400h] BYREF

  Key = idDict::FindKey(
          &idAsyncNetwork::client.serverList.activeServers.list[this->serverList.list[listIndex]].serverInfo,
          "si_map");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  fileSystem->FindMapScreenshot(fileSystem, data, screenshot, 1024);
  this->scanGUI->SetStateString(this->scanGUI, "browser_levelshot", screenshot);
  declManager->FindMaterial(declManager, screenshot, 1)->sort = -2.0;
  if ( listIndex < 0 || listIndex >= this->serverList.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::IsAFavorite() - Invalid selected server '%d'\n",
      listIndex);
    goto LABEL_9;
  }
  if ( !idAsyncNetwork::client.serverList.activeServers.list[this->serverList.list[listIndex]].favorite )
  {
LABEL_9:
    v5 = this->scanGUI->__vftable;
    v6 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
           common.type,
           "#str_200292",
           -1);
    goto LABEL_10;
  }
  v5 = this->scanGUI->__vftable;
  v6 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
         common.type,
         "#str_200293",
         -1);
LABEL_10:
  v5->SetStateString(this->scanGUI, "favoriteStatus", (const char *)v6);
  this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
}

// FUNC: public: char * __thiscall rvServerScanGUI::BuildFriendsListString(int)
char *__thiscall rvServerScanGUI::BuildFriendsListString(rvServerScanGUI *this, int listIndex)
{
  rvPair<int,int> *v2; // esi
  friend_t *v3; // edi
  networkServer_t *v5; // esi
  const idKeyValue *Key; // eax
  const char *data; // eax

  if ( listIndex < 0 || listIndex >= this->friendsList.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::BuildFriendsListString() - Invalid friend index '%d'\n",
      listIndex);
    return (char *)&entityFilter;
  }
  else
  {
    v2 = &this->friendsList.list[listIndex];
    v3 = &idAsyncNetwork::client.serverList.activeFriends.list[v2->first];
    if ( v2->second == -1 )
    {
      return va("%s\t%s\t%s\t%s\t", v3->name, v3->clan, "Offline", &entityFilter);
    }
    else
    {
      v5 = &idAsyncNetwork::client.serverList.activeServers.list[this->friendsList.list[listIndex].second];
      Key = idDict::FindKey(&v5->serverInfo, "si_name");
      if ( Key )
        data = Key->value->data;
      else
        data = &entityFilter;
      return va("%s\t%s\t%s\t%d\t", v3->name, v3->clan, data, v5->ping);
    }
  }
}

// FUNC: public: struct netadr_t __thiscall rvServerScanGUI::GetFriendServer(int)
netadr_t *__thiscall rvServerScanGUI::GetFriendServer(rvServerScanGUI *this, netadr_t *result, int listIndex)
{
  rvPair<int,int> *v3; // ecx
  int second; // eax
  netadr_t *v5; // eax
  int v6; // edx
  int bad_4; // [esp+8h] [ebp-8h]
  int bad_8; // [esp+Ch] [ebp-4h]

  if ( listIndex < 0 || listIndex >= this->friendsList.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::GetFriendServer() - Invalid friend index '%d'\n",
      listIndex);
    v5 = result;
    result->type = NA_BAD;
    *(_DWORD *)result->ip = bad_4;
    *(_DWORD *)&result->port = bad_8;
  }
  else
  {
    v3 = &this->friendsList.list[listIndex];
    second = v3->second;
    if ( second == -1 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "rvServerScanGUI::GetFriendServer() - Friend '%d' not on a server\n",
        v3->first);
      v5 = result;
      result->type = NA_BAD;
      *(_DWORD *)result->ip = bad_4;
      *(_DWORD *)&result->port = bad_8;
    }
    else
    {
      v6 = second;
      v5 = result;
      *result = idAsyncNetwork::client.serverList.activeServers.list[v6].adr;
    }
  }
  return v5;
}

// FUNC: public: void __thiscall rvServerScan::AddServer(char const *,int)
void __thiscall rvServerScan::AddServer(rvServerScan *this, const char *srv, int time)
{
  bool v4; // zf
  int granularity; // eax
  bool v6; // cc
  inServer_t *v7; // eax
  int v8; // ecx
  netadrtype_t *v9; // eax
  inServer_t *v10; // edx
  int num; // ebx
  int size; // ecx
  int v13; // ecx
  inServer_t *list; // edi
  inServer_t *v15; // eax
  int v16; // ecx
  int v17; // eax
  inServer_t *v18; // ebx
  inServer_t newServer; // [esp+Ch] [ebp-14h] BYREF

  this->masterServerTimeout = Sys_Milliseconds() + 1500;
  if ( Sys_StringToNetAdr(srv, &newServer.adr, 0) )
  {
    if ( !newServer.adr.port )
      newServer.adr.port = 28004;
    ++this->numServers;
    v4 = this->scanServers.list == 0;
    newServer.time = time < 0 ? 0 : time;
    if ( v4 )
    {
      granularity = this->scanServers.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->scanServers.size )
        {
          v6 = granularity < this->scanServers.num;
          this->scanServers.size = granularity;
          if ( v6 )
            this->scanServers.num = granularity;
          v7 = (inServer_t *)Memory::Allocate(20 * granularity);
          v8 = 0;
          v6 = this->scanServers.num <= 0;
          this->scanServers.list = v7;
          if ( !v6 )
          {
            v9 = 0;
            do
            {
              v10 = (inServer_t *)((char *)v9 + (unsigned int)this->scanServers.list);
              v10->adr.type = *v9;
              *(netadrtype_t *)v10->adr.ip = v9[1];
              *(netadrtype_t *)&v10->adr.port = v9[2];
              v10->id = v9[3];
              ++v8;
              v10->time = v9[4];
              v9 += 5;
            }
            while ( v8 < this->scanServers.num );
          }
        }
      }
      else
      {
        this->scanServers.list = 0;
        this->scanServers.num = 0;
        this->scanServers.size = 0;
      }
    }
    num = this->scanServers.num;
    size = this->scanServers.size;
    if ( this->scanServers.num == size )
    {
      if ( !this->scanServers.granularity )
        this->scanServers.granularity = 16;
      v13 = this->scanServers.granularity
          + size
          - (this->scanServers.granularity + size) % this->scanServers.granularity;
      if ( v13 > 0 )
      {
        if ( v13 != this->scanServers.size )
        {
          list = this->scanServers.list;
          this->scanServers.size = v13;
          if ( v13 < num )
            this->scanServers.num = v13;
          v15 = (inServer_t *)Memory::Allocate(20 * v13);
          v16 = 0;
          v6 = this->scanServers.num <= 0;
          this->scanServers.list = v15;
          if ( !v6 )
          {
            v17 = 0;
            do
            {
              v18 = &this->scanServers.list[v17];
              v18->adr.type = list[v17].adr.type;
              *(_DWORD *)v18->adr.ip = *(_DWORD *)list[v17].adr.ip;
              *(_DWORD *)&v18->adr.port = *(_DWORD *)&list[v17].adr.port;
              v18->id = list[v17].id;
              ++v16;
              v18->time = list[v17++].time;
            }
            while ( v16 < this->scanServers.num );
          }
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->scanServers.list )
          Memory::Free(this->scanServers.list);
        this->scanServers.list = 0;
        this->scanServers.num = 0;
        this->scanServers.size = 0;
      }
    }
    this->scanServers.list[this->scanServers.num++] = newServer;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "rvServerScan::AddServer: failed to parse server %s\n",
      srv);
  }
}

// FUNC: public: void __thiscall rvServerScan::RegisterGUICallback(class rvServerScanGUI *,enum scanGuiCallback_t)
void __thiscall rvServerScan::RegisterGUICallback(rvServerScan *this, rvServerScanGUI *gui, scanGuiCallback_t type)
{
  idList<rvServerScanGUI *> *v3; // esi
  int granularity; // eax
  bool v5; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v9; // ecx
  rvServerScanGUI **list; // edi
  int j; // eax

  v3 = &this->callbacks[type];
  if ( !v3->list )
  {
    granularity = v3->granularity;
    if ( granularity > 0 )
    {
      if ( granularity != v3->size )
      {
        v5 = granularity < v3->num;
        v3->size = granularity;
        if ( v5 )
          v3->num = granularity;
        v3->list = (rvServerScanGUI **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < v3->num; ++i )
          v3->list[i] = *(rvServerScanGUI **)(4 * i);
      }
    }
    else
    {
      v3->list = 0;
      v3->num = 0;
      v3->size = 0;
    }
  }
  num = v3->num;
  size = v3->size;
  if ( v3->num == size )
  {
    if ( !v3->granularity )
      v3->granularity = 16;
    v9 = size + v3->granularity - (size + v3->granularity) % v3->granularity;
    if ( v9 > 0 )
    {
      if ( v9 != v3->size )
      {
        list = v3->list;
        v3->size = v9;
        if ( v9 < num )
          v3->num = v9;
        v3->list = (rvServerScanGUI **)Memory::Allocate(4 * v9);
        for ( j = 0; j < v3->num; ++j )
          v3->list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( v3->list )
        Memory::Free(v3->list);
      v3->list = 0;
      v3->num = 0;
      v3->size = 0;
    }
  }
  v3->list[v3->num++] = gui;
}

// FUNC: private: bool __thiscall rvServerScan::RemoveFromFriendsList(char const *)
char __thiscall rvServerScan::RemoveFromFriendsList(rvServerScan *this, const char *guid)
{
  const char *value; // esi
  int v3; // eax
  int v6; // ebp
  int v7; // eax
  int Text; // ebx
  int v9; // eax
  const char *v10; // edi
  unsigned int v11; // eax
  int v12; // ebx
  int v13; // eax
  char *data; // edx
  const char *v15; // ecx
  char v16; // al
  int v17; // edx
  int v18; // eax
  idStr *v19; // esi
  idStr *v20; // eax
  const char *v21; // eax
  idStr friends; // [esp+8h] [ebp-6Ch] BYREF
  idStr v23; // [esp+28h] [ebp-4Ch] BYREF
  idStr v24; // [esp+48h] [ebp-2Ch] BYREF
  int v25; // [esp+70h] [ebp-4h]
  void *retaddr; // [esp+74h] [ebp+0h]
  const char *guida; // [esp+78h] [ebp+4h]

  value = g_friendsList.internalVar->value;
  v3 = 0;
  if ( *value )
  {
    do
      ++v3;
    while ( value[v3] );
    if ( v3 >= 0x4000 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "rvServerScan::RemoveFromFriendsList() - friends cvar too long\n");
      rvServerScan::DumpAndClearFriends(this);
      return 0;
    }
  }
  v6 = idStr::FindText(value, guid, 0, 0, -1) - 2;
  if ( v6 < 0 )
    goto LABEL_25;
  v7 = 0;
  if ( *value )
  {
    do
      ++v7;
    while ( value[v7] );
  }
  if ( v6 >= v7 )
  {
LABEL_25:
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "rvServerScan::RemoveFromFriendsList() - Not removing non-friend '%s'\n",
      guid);
    return 0;
  }
  if ( value[v6] != 123 )
    goto LABEL_10;
  Text = idStr::FindText(value, "}", 0, v6, -1);
  guida = (const char *)Text;
  if ( Text < 0 )
    goto LABEL_10;
  v9 = 0;
  if ( *value )
  {
    do
      ++v9;
    while ( value[v9] );
  }
  if ( Text >= v9 )
  {
LABEL_10:
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::RemoveFromFriendsList() - Malformed friends cvar '%s'\n",
      value);
    rvServerScan::DumpAndClearFriends(this);
    return 0;
  }
  v10 = g_friendsList.internalVar->value;
  friends.len = 0;
  friends.alloced = 20;
  friends.data = friends.baseBuffer;
  friends.baseBuffer[0] = 0;
  if ( v10 )
  {
    v11 = (unsigned int)&v10[strlen(v10) + 1];
    v12 = v11 - (_DWORD)(v10 + 1);
    v13 = v11 - (_DWORD)v10;
    if ( v13 > 20 )
      idStr::ReAllocate(&friends, v13, 1);
    data = friends.data;
    v15 = v10;
    do
    {
      v16 = *v15;
      *data++ = *v15++;
    }
    while ( v16 );
    friends.len = v12;
    Text = (int)guida;
  }
  v17 = *(_DWORD *)common.type;
  v25 = 0;
  (*(void (__stdcall **)(netadrtype_t))(v17 + 132))(common.type);
  v18 = 0;
  if ( *value )
  {
    do
      ++v18;
    while ( value[v18] );
  }
  v19 = idStr::Right((idStr *)&friends.data, (idStr *)&v24.data, v18 - Text - 1);
  v20 = idStr::Left((idStr *)&friends.data, (idStr *)&v23.data, v6);
  LOBYTE(retaddr) = 2;
  v21 = va("%s%s", v20->data, v19->data);
  g_friendsList.internalVar->InternalSetString(g_friendsList.internalVar, v21);
  LOBYTE(v25) = 1;
  idStr::FreeData(&v23);
  LOBYTE(v25) = 0;
  idStr::FreeData(&v24);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "rvServerScanGUI::RemoveFromFriendsList:  now '%s'\n",
    g_friendsList.internalVar->value);
  v25 = -1;
  idStr::FreeData(&friends);
  return 1;
}

// FUNC: public: void __thiscall rvServerScan::RemoveFromFriendsList(int)
void __thiscall rvServerScan::RemoveFromFriendsList(rvServerScan *this, unsigned int clientNum)
{
  const char *v3; // eax

  if ( idAsyncNetwork::server.active || idAsyncNetwork::client.clientState >= CS_CONNECTED )
  {
    if ( clientNum > 0x1F )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "rvServerScan::RemoveFromFriendsList() - Invalid client '%d' specified\n",
        clientNum);
    }
    else
    {
      v3 = networkSystem->GetClientGUID(networkSystem, clientNum);
      if ( *v3 )
      {
        if ( rvServerScan::RemoveFromFriendsList(this, v3) )
          game->SetFriend(game, clientNum, 0);
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "rvServerScan::RemoveFromFriendsList() - Bad guid for client %d\n");
      }
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::RemoveFromFriendsList() - Must be connected to a server to remove friends\n");
  }
}

// FUNC: public: void __thiscall rvServerScan::UpdateFriend(char const *,char const *,char const *)
void __thiscall rvServerScan::UpdateFriend(rvServerScan *this, const char *guid, const char *name, const char *clan)
{
  const char *value; // esi
  int Text; // eax
  int v7; // ecx
  const char *v8; // eax
  int v9; // esi
  int v10; // eax
  char *data; // edx
  const char *v12; // ecx
  char v13; // al
  int v14; // eax
  int v15; // eax
  idStr strGuid; // [esp+14h] [ebp-2Ch] BYREF
  int v18; // [esp+3Ch] [ebp-4h]

  value = g_friendsList.internalVar->value;
  Text = idStr::FindText(value, guid, 0, 0, -1);
  if ( Text < 0 )
    goto LABEL_23;
  v7 = 0;
  if ( *value )
  {
    do
      ++v7;
    while ( value[v7] );
  }
  if ( Text >= v7 )
  {
LABEL_23:
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::UpdateFriend() - Got an update friend for someone not on my friends list {[%s][%s][%s]}\n",
      guid,
      name,
      clan);
  }
  else
  {
    strGuid.len = 0;
    strGuid.alloced = 20;
    strGuid.data = strGuid.baseBuffer;
    strGuid.baseBuffer[0] = 0;
    if ( guid )
    {
      v8 = &guid[strlen(guid) + 1];
      v9 = v8 - (guid + 1);
      v10 = v8 - guid;
      if ( v10 > 20 )
        idStr::ReAllocate(&strGuid, v10, 1);
      data = strGuid.data;
      v12 = guid;
      do
      {
        v13 = *v12;
        *data++ = *v12++;
      }
      while ( v13 );
      strGuid.len = v9;
    }
    v18 = 0;
    if ( rvServerScan::ValidateGUID(this, &strGuid) )
    {
      v14 = 0;
      if ( !*name )
        goto LABEL_17;
      do
        ++v14;
      while ( name[v14] );
      if ( v14 >= 64 )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "rvServerScan::UpdateFriend() - Malformed name '%s'\n",
          name);
      }
      else
      {
LABEL_17:
        v15 = 0;
        if ( !*clan )
          goto LABEL_21;
        do
          ++v15;
        while ( clan[v15] );
        if ( v15 >= 64 )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "rvServerScan::UpdateFriend() - Malformed clan '%s'\n",
            clan);
        }
        else
        {
LABEL_21:
          rvServerScan::RemoveFromFriendsList(this, guid);
          rvServerScan::AddToFriendsList(this, guid, name, clan);
        }
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "rvServerScan::UpdateFriend() - Malformed guid '%s'\n",
        guid);
    }
    v18 = -1;
    idStr::FreeData(&strGuid);
  }
}

// FUNC: public: bool __thiscall rvServerScan::GetFriendGUIDFromFriendsList(int,char *)
char __thiscall rvServerScan::GetFriendGUIDFromFriendsList(rvServerScan *this, int num, char *guid)
{
  const char *value; // esi
  int v4; // eax
  unsigned int v5; // eax
  int v6; // edi
  int v7; // eax
  char *data; // edx
  const char *v9; // ecx
  char v10; // al
  int v11; // esi
  int v12; // edi
  idStr friendsList; // [esp+14h] [ebp-4Ch] BYREF
  idStr scanGuid; // [esp+34h] [ebp-2Ch] BYREF
  int v17; // [esp+5Ch] [ebp-4h]

  value = g_friendsList.internalVar->value;
  v4 = 0;
  friendsList.len = 0;
  friendsList.alloced = 20;
  friendsList.data = friendsList.baseBuffer;
  friendsList.baseBuffer[0] = 0;
  if ( value )
  {
    v5 = (unsigned int)&value[strlen(value) + 1];
    v6 = v5 - (_DWORD)(value + 1);
    v7 = v5 - (_DWORD)value;
    if ( v7 > 20 )
      idStr::ReAllocate(&friendsList, v7, 1);
    data = friendsList.data;
    v9 = value;
    do
    {
      v10 = *v9;
      *data++ = *v9++;
    }
    while ( v10 );
    v4 = v6;
    friendsList.len = v6;
  }
  v17 = 0;
  v11 = idStr::FindChar(friendsList.data, 123, 0, v4) + 2;
  v12 = 0;
  if ( v11 >= 0 )
  {
    while ( v11 < friendsList.len )
    {
      idStr::Mid(&friendsList, &scanGuid, v11, 11);
      LOBYTE(v17) = 1;
      if ( v12 == num )
      {
        if ( rvServerScan::ValidateGUID(this, &scanGuid) )
        {
          idStr::Copynz(guid, scanGuid.data, 12);
          LOBYTE(v17) = 0;
          idStr::FreeData(&scanGuid);
          v17 = -1;
          idStr::FreeData(&friendsList);
          return 1;
        }
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "rvServerScan::GetFriendGUID() - Malformed guid '%s'\n",
          scanGuid.data);
        rvServerScan::DumpAndClearFriends(this);
        LOBYTE(v17) = 0;
        idStr::FreeData(&scanGuid);
        break;
      }
      v11 = idStr::FindChar(friendsList.data, 123, v11, friendsList.len) + 2;
      ++v12;
      LOBYTE(v17) = 0;
      idStr::FreeData(&scanGuid);
      if ( v11 < 0 )
        break;
    }
  }
  v17 = -1;
  idStr::FreeData(&friendsList);
  return 0;
}

// FUNC: public: void __thiscall rvServerScanGUI::SetupServerScanGUI(class idUserInterface *,char const *,char const *)
void __thiscall rvServerScanGUI::SetupServerScanGUI(
        rvServerScanGUI *this,
        idUserInterface *serverScanGUI,
        const char *listDefName,
        const char *friendsListDefName)
{
  int v5; // eax
  const char *v6; // eax
  int v7; // edi
  int v8; // eax
  char *data; // edx
  const char *v10; // ecx
  char v11; // al
  unsigned int v12; // esi
  int v13; // eax
  bool v14; // cc
  int v15; // eax
  const char *v16; // eax
  int v17; // edi
  int v18; // eax
  char *v19; // edx
  const char *v20; // ecx
  char v21; // al
  unsigned int v22; // esi
  int v23; // eax
  idUserInterface_vtbl *v24; // esi
  int v25; // eax
  idStr v26; // [esp+10h] [ebp-4Ch] BYREF
  idStr v27; // [esp+30h] [ebp-2Ch] BYREF
  int v28; // [esp+58h] [ebp-4h]

  this->scanGUI = serverScanGUI;
  v5 = 0;
  v26.len = 0;
  v26.alloced = 20;
  v26.data = v26.baseBuffer;
  v26.baseBuffer[0] = 0;
  if ( listDefName )
  {
    v6 = &listDefName[strlen(listDefName) + 1];
    v7 = v6 - (listDefName + 1);
    v8 = v6 - listDefName;
    if ( v8 > 20 )
      idStr::ReAllocate(&v26, v8, 1);
    data = v26.data;
    v10 = listDefName;
    do
    {
      v11 = *v10;
      *data++ = *v10++;
    }
    while ( v11 );
    v5 = v7;
    v26.len = v7;
  }
  v12 = v5;
  v13 = v5 + 1;
  v14 = v13 <= this->listName.alloced;
  v28 = 0;
  if ( !v14 )
    idStr::ReAllocate(&this->listName, v13, 0);
  qmemcpy(this->listName.data, v26.data, v12);
  this->listName.data[v12] = 0;
  this->listName.len = v12;
  v28 = -1;
  idStr::FreeData(&v26);
  v15 = 0;
  v27.len = 0;
  v27.alloced = 20;
  v27.data = v27.baseBuffer;
  v27.baseBuffer[0] = 0;
  if ( friendsListDefName )
  {
    v16 = &friendsListDefName[strlen(friendsListDefName) + 1];
    v17 = v16 - (friendsListDefName + 1);
    v18 = v16 - friendsListDefName;
    if ( v18 > 20 )
      idStr::ReAllocate(&v27, v18, 1);
    v19 = v27.data;
    v20 = friendsListDefName;
    do
    {
      v21 = *v20;
      *v19++ = *v20++;
    }
    while ( v21 );
    v15 = v17;
    v27.len = v17;
  }
  v22 = v15;
  v23 = v15 + 1;
  v14 = v23 <= this->friendsListName.alloced;
  v28 = 1;
  if ( !v14 )
    idStr::ReAllocate(&this->friendsListName, v23, 0);
  qmemcpy(this->friendsListName.data, v27.data, v22);
  this->friendsListName.data[v22] = 0;
  this->friendsListName.len = v22;
  v28 = -1;
  idStr::FreeData(&v27);
  rvServerScan::RegisterGUICallback(&idAsyncNetwork::client.serverList, this, SG_CALLBACK_NEW_SERVER);
  rvServerScan::RegisterGUICallback(&idAsyncNetwork::client.serverList, this, SG_CALLBACK_REFRESH_COMPLETE);
  rvServerScan::RegisterGUICallback(&idAsyncNetwork::client.serverList, this, SG_CALLBACK_START_SCAN);
  rvServerScan::RegisterGUICallback(&idAsyncNetwork::client.serverList, this, SG_CALLBACK_SCANNING);
  rvServerScan::RegisterGUICallback(
    &idAsyncNetwork::client.serverList,
    this,
    SG_CALLBACK_REFRESH_COMPLETE|SG_CALLBACK_SCANNING);
  rvServerScan::RegisterGUICallback(&idAsyncNetwork::client.serverList, this, SG_NUM_CALLBACKS);
  this->scanGUI->SetStateString(this->scanGUI, "loadNotice", &entityFilter);
  v24 = this->scanGUI->__vftable;
  v25 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
          common.type,
          "#str_107292",
          -1);
  v24->SetStateString(this->scanGUI, "sortNotice", (const char *)v25);
  ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))this->scanGUI->SetStateFloat)(
    this->scanGUI,
    "loadPct",
    0);
  this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
}

// FUNC: public: char * __thiscall rvServerScanGUI::BuildListString(int)
char *__thiscall rvServerScanGUI::BuildListString(rvServerScanGUI *this, int listIndex)
{
  networkServer_t *v2; // ebp
  const idKeyValue *Key; // eax
  const idPoolStr *value; // esi
  unsigned int len; // ebx
  int v6; // eax
  int v7; // esi
  int v8; // eax
  idStr *v9; // esi
  unsigned int v10; // ebx
  int v11; // eax
  idDict *p_serverInfo; // edi
  const idKeyValue *v13; // eax
  const char *data; // eax
  int v15; // eax
  idDict *v16; // ecx
  bool v17; // bl
  const idKeyValue *v18; // eax
  const char *v19; // eax
  char *v20; // eax
  const idKeyValue *v21; // eax
  const char *v22; // eax
  char *v23; // eax
  const idKeyValue *v24; // eax
  const char *v25; // eax
  const idKeyValue *v26; // eax
  const char *v27; // eax
  const char *v28; // ebx
  char *v29; // ebp
  const idKeyValue *v30; // eax
  const char *v31; // esi
  const idKeyValue *v32; // eax
  const char *v33; // eax
  char *v34; // esi
  int v36; // [esp-14h] [ebp-74h]
  int v37; // [esp-14h] [ebp-74h]
  const char *v38; // [esp+4h] [ebp-5Ch]
  const char *v39; // [esp+8h] [ebp-58h]
  const char *v40; // [esp+Ch] [ebp-54h]
  const char *v41; // [esp+10h] [ebp-50h]
  idStr shortMap; // [esp+14h] [ebp-4Ch] BYREF
  idStr result; // [esp+34h] [ebp-2Ch] BYREF
  int v44; // [esp+5Ch] [ebp-4h]
  const char *listIndexa; // [esp+64h] [ebp+4h]

  if ( listIndex < 0 || listIndex >= this->serverList.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::BuildListString() - Invalid server index '%d'\n",
      listIndex);
    return (char *)&entityFilter;
  }
  else
  {
    v2 = &idAsyncNetwork::client.serverList.activeServers.list[this->serverList.list[listIndex]];
    shortMap.len = 0;
    shortMap.alloced = 20;
    shortMap.data = shortMap.baseBuffer;
    shortMap.baseBuffer[0] = 0;
    v44 = 0;
    Key = idDict::FindKey(&v2->serverInfo, "si_map");
    if ( Key )
    {
      value = Key->value;
      len = value->len;
      v6 = value->len + 1;
      if ( v6 > shortMap.alloced )
        idStr::ReAllocate(&shortMap, v6, 0);
      qmemcpy(shortMap.data, value->data, len);
      shortMap.data[len] = 0;
      shortMap.len = len;
    }
    else
    {
      idStr::operator=(&shortMap, (char *)&entityFilter);
    }
    v7 = shortMap.len;
    v8 = idStr::Last(&shortMap, 47);
    v9 = idStr::Right(&shortMap, &result, v7 - v8 - 1);
    v10 = v9->len;
    v11 = v9->len + 1;
    LOBYTE(v44) = 1;
    if ( v11 > shortMap.alloced )
      idStr::ReAllocate(&shortMap, v11, 0);
    qmemcpy(shortMap.data, v9->data, v10);
    shortMap.data[v10] = 0;
    shortMap.len = v10;
    LOBYTE(v44) = 0;
    idStr::FreeData(&result);
    p_serverInfo = &v2->serverInfo;
    v13 = idDict::FindKey(&v2->serverInfo, "si_maxPlayers");
    if ( v13 )
      data = v13->value->data;
    else
      data = "0";
    v15 = atoi(data);
    v16 = &v2->serverInfo;
    v17 = v2->ping > 300;
    if ( v2->clients == v15 )
    {
      v18 = idDict::FindKey(v16, "si_maxPlayers");
      if ( v18 )
        v19 = v18->value->data;
      else
        v19 = "0";
      v36 = atoi(v19);
      v20 = va("^c920%d/%d", v2->clients, v36);
    }
    else
    {
      v21 = idDict::FindKey(v16, "si_maxPlayers");
      if ( v21 )
        v22 = v21->value->data;
      else
        v22 = "0";
      v37 = atoi(v22);
      v20 = va("%d/%d", v2->clients, v37);
    }
    listIndexa = v20;
    if ( v17 )
      v23 = va("^c920%d", v2->ping);
    else
      v23 = va("%d", v2->ping);
    v38 = v23;
    v24 = idDict::FindKey(&v2->serverInfo, "sv_punkbuster");
    if ( v24 )
      v25 = v24->value->data;
    else
      v25 = "0";
    if ( atoi(v25) )
      v39 = I_PB_ENABLED;
    else
      v39 = I_PB_DISABLED;
    if ( v2->dedicated )
      v40 = I_DEDICATED_ENABLED;
    else
      v40 = I_DEDICATED_DISABLED;
    v26 = idDict::FindKey(&v2->serverInfo, "si_usepass");
    if ( v26 )
      v27 = v26->value->data;
    else
      v27 = "0";
    if ( atoi(v27) )
      v41 = I_PASSWORD_ENABLED;
    else
      v41 = I_PASSWORD_DISABLED;
    v28 = I_FAVORITE_ENABLED;
    if ( !v2->favorite )
      v28 = I_FAVORITE_DISABLED;
    v29 = shortMap.data;
    v30 = idDict::FindKey(p_serverInfo, "si_gametype");
    if ( v30 )
      v31 = v30->value->data;
    else
      v31 = &entityFilter;
    v32 = idDict::FindKey(p_serverInfo, "si_name");
    if ( v32 )
      v33 = v32->value->data;
    else
      v33 = &entityFilter;
    v34 = va("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t", v28, v41, v40, v39, v33, v38, listIndexa, v31, v29);
    v44 = -1;
    idStr::FreeData(&shortMap);
    return v34;
  }
}

// FUNC: public: void __thiscall rvServerScanGUI::Populate(void)
void __thiscall rvServerScanGUI::Populate(rvServerScanGUI *this)
{
  int i; // edi
  char *data; // ebx
  idUserInterface_vtbl *v4; // ebp
  char *v5; // eax
  idUserInterface_vtbl *v6; // ebx
  int v7; // edx
  char *v8; // eax
  idUserInterface_vtbl *v9; // edi
  char *v10; // eax
  char *v11; // [esp-Ch] [ebp-14h]
  int v12; // [esp-Ch] [ebp-14h]

  for ( i = 0; i < this->serverList.num; ++i )
  {
    data = this->listName.data;
    v4 = this->scanGUI->__vftable;
    v11 = rvServerScanGUI::BuildListString(this, i);
    v5 = va("%s_item_%i", data, i);
    v4->SetStateString(this->scanGUI, v5, v11);
    v6 = this->scanGUI->__vftable;
    v7 = 2320 * this->serverList.list[i];
    LOBYTE(v7) = *(&idAsyncNetwork::client.serverList.activeServers.list->performanceFiltered + v7);
    v12 = v7;
    v8 = va("%s_item_%i_greyed", this->listName.data, i);
    v6->SetStateBool(this->scanGUI, v8, v12);
  }
  v9 = this->scanGUI->__vftable;
  v10 = va("%s_item_%i", this->listName.data, this->serverList.num);
  v9->SetStateString(this->scanGUI, v10, &entityFilter);
}

// FUNC: public: void __thiscall rvServerScanGUI::Update(int)
void __thiscall rvServerScanGUI::Update(rvServerScanGUI *this, int listIndex)
{
  char *data; // ebx
  idUserInterface_vtbl *v4; // ebp
  char *v5; // eax
  idUserInterface_vtbl *v6; // ebx
  int v7; // edx
  char *v8; // eax
  char *v9; // [esp-10h] [ebp-14h]
  int v10; // [esp-10h] [ebp-14h]

  if ( this->scanGUI )
  {
    data = this->listName.data;
    v4 = this->scanGUI->__vftable;
    v9 = rvServerScanGUI::BuildListString(this, listIndex);
    v5 = va("%s_item_%i", data, listIndex);
    v4->SetStateString(this->scanGUI, v5, v9);
    v6 = this->scanGUI->__vftable;
    v7 = 2320 * this->serverList.list[listIndex];
    LOBYTE(v7) = *(&idAsyncNetwork::client.serverList.activeServers.list->performanceFiltered + v7);
    v10 = v7;
    v8 = va("%s_item_%i_greyed", this->listName.data, listIndex);
    v6->SetStateBool(this->scanGUI, v8, v10);
    this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
  }
}

// FUNC: public: void __thiscall rvServerScanGUI::AddToFavoritesList(int)
void __thiscall rvServerScanGUI::AddToFavoritesList(rvServerScanGUI *this, int listIndex)
{
  if ( listIndex < 0 || listIndex >= this->serverList.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::AddToFavoritesList() - Invalid selected server '%d'\n",
      listIndex);
  }
  else
  {
    rvServerScan::AddToFavoritesList(&idAsyncNetwork::client.serverList, this->serverList.list[listIndex]);
    rvServerScanGUI::Update(this, listIndex);
  }
}

// FUNC: public: void __thiscall rvServerScanGUI::RemoveFromFavoritesList(int)
void __thiscall rvServerScanGUI::RemoveFromFavoritesList(rvServerScanGUI *this, int listIndex)
{
  if ( listIndex < 0 || listIndex >= this->serverList.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::RemoveFromFavoritesList() - Invalid selected server '%d'\n",
      listIndex);
  }
  else
  {
    rvServerScan::RemoveFromFavoritesList(&idAsyncNetwork::client.serverList, this->serverList.list[listIndex]);
    rvServerScanGUI::Update(this, listIndex);
  }
}

// FUNC: public: void __thiscall rvServerScanGUI::FriendUpdate(int)
void __thiscall rvServerScanGUI::FriendUpdate(rvServerScanGUI *this, int listIndex)
{
  idUserInterface_vtbl *v3; // edi
  char *v4; // eax
  idUserInterface_vtbl *v5; // esi
  const char *v6; // eax
  char *v7; // eax
  idUserInterface *scanGUI; // ecx
  int v9; // [esp+14h] [ebp-C0h]
  char *v10; // [esp+18h] [ebp-BCh]
  int v11; // [esp+18h] [ebp-BCh]
  float v12; // [esp+18h] [ebp-BCh]
  char *numServersa; // [esp+2Ch] [ebp-A8h]
  int numServers; // [esp+2Ch] [ebp-A8h]
  int numScanned; // [esp+30h] [ebp-A4h]
  friend_t selFriend; // [esp+34h] [ebp-A0h] BYREF

  if ( this->scanGUI )
  {
    v3 = this->scanGUI->__vftable;
    numServersa = this->friendsListName.data;
    v10 = rvServerScanGUI::BuildFriendsListString(this, listIndex);
    v4 = va("%s_item_%i", numServersa, listIndex);
    v3->SetStateString(this->scanGUI, v4, v10);
    numServers = idAsyncNetwork::client.serverList.numServers;
    qmemcpy(
      &selFriend,
      &idAsyncNetwork::client.serverList.activeFriends.list[this->friendsList.list[listIndex].first],
      sizeof(selFriend));
    v5 = this->scanGUI->__vftable;
    numScanned = idAsyncNetwork::client.serverList.numScanned;
    v6 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int, int, char *))(*(_DWORD *)common.type
                                                                                                + 168))(
                         common.type,
                         "#str_107297",
                         -1,
                         idAsyncNetwork::client.serverList.numScanned,
                         idAsyncNetwork::client.serverList.numServers,
                         selFriend.name);
    v7 = va(v6);
    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v5->SetStateString)(
      this->scanGUI,
      "loadNotice",
      v7,
      v9,
      v11);
    scanGUI = this->scanGUI;
    if ( numServers )
    {
      v12 = (double)numScanned / (double)numServers;
      ((void (__stdcall *)(const char *, _DWORD))scanGUI->SetStateFloat)("loadPct", LODWORD(v12));
    }
    else
    {
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))scanGUI->SetStateFloat)(scanGUI, "loadPct", 0);
    }
    this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::FriendUpdate() - invalid scanGUI\n");
  }
}

// FUNC: public: void __thiscall rvServerScan::AddFriend(char const *,char const *,char const *,char const *)
void __thiscall rvServerScan::AddFriend(
        rvServerScan *this,
        const char *guid,
        const char *name,
        const char *clan,
        const char *server)
{
  int v6; // edi
  int v7; // ebx
  int v8; // ebx
  friend_t *list; // eax
  bool v10; // zf
  unsigned __int16 *p_port; // ebx
  int v12; // eax
  int v13; // ebx
  int v14; // edi
  bool v15; // cc
  int num; // ecx
  int granularity; // eax
  inServer_t *v18; // eax
  int v19; // ecx
  netadrtype_t *v20; // eax
  inServer_t *v21; // edx
  int v22; // ebx
  int size; // ecx
  int v24; // ecx
  inServer_t *v25; // edi
  inServer_t *v26; // eax
  int v27; // ecx
  int v28; // eax
  inServer_t *v29; // ebx
  inServer_t newServer; // [esp+10h] [ebp-14h] BYREF

  Sys_StringToNetAdr(server, &newServer.adr, 0);
  if ( !newServer.adr.port )
    newServer.adr.port = 28004;
  v6 = 0;
  if ( this->activeFriends.num > 0 )
  {
    v7 = 0;
    while ( idStr::Icmp(guid, this->activeFriends.list[v7].guid) )
    {
      ++v6;
      ++v7;
      if ( v6 >= this->activeFriends.num )
        goto LABEL_12;
    }
    v8 = v6;
    if ( !Sys_StringToNetAdr(server, &this->activeFriends.list[v6].server, 0) )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "rvServerScan::AddFriend(): failed to parse server %s\n",
        server);
      return;
    }
    list = this->activeFriends.list;
    v10 = list[v8].server.port == 0;
    p_port = &list[v8].server.port;
    if ( v10 )
      *p_port = 28004;
  }
LABEL_12:
  if ( v6 < this->activeFriends.num )
  {
    v12 = Sys_Milliseconds();
    ++this->numServers;
    v13 = 0;
    v14 = 0;
    v15 = this->scanServers.num <= 0;
    this->masterServerTimeout = v12 + 1500;
    newServer.time = 0;
    if ( !v15 )
    {
      do
      {
        if ( Sys_CompareNetAdrBase(this->scanServers.list[v13].adr, newServer.adr)
          && this->scanServers.list[v13].adr.port == newServer.adr.port )
        {
          break;
        }
        ++v14;
        ++v13;
      }
      while ( v14 < this->scanServers.num );
    }
    num = this->scanServers.num;
    if ( v14 >= this->scanServers.num )
    {
      if ( !this->scanServers.list )
      {
        granularity = this->scanServers.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->scanServers.size )
          {
            this->scanServers.size = granularity;
            if ( granularity < num )
              this->scanServers.num = granularity;
            v18 = (inServer_t *)Memory::Allocate(20 * granularity);
            v19 = 0;
            v15 = this->scanServers.num <= 0;
            this->scanServers.list = v18;
            if ( !v15 )
            {
              v20 = 0;
              do
              {
                v21 = (inServer_t *)((char *)v20 + (unsigned int)this->scanServers.list);
                v21->adr.type = *v20;
                *(netadrtype_t *)v21->adr.ip = v20[1];
                *(netadrtype_t *)&v21->adr.port = v20[2];
                v21->id = v20[3];
                ++v19;
                v21->time = v20[4];
                v20 += 5;
              }
              while ( v19 < this->scanServers.num );
            }
          }
        }
        else
        {
          this->scanServers.list = 0;
          this->scanServers.num = 0;
          this->scanServers.size = 0;
        }
      }
      v22 = this->scanServers.num;
      size = this->scanServers.size;
      if ( this->scanServers.num == size )
      {
        if ( !this->scanServers.granularity )
          this->scanServers.granularity = 16;
        v24 = this->scanServers.granularity
            + size
            - (this->scanServers.granularity + size) % this->scanServers.granularity;
        if ( v24 > 0 )
        {
          if ( v24 != this->scanServers.size )
          {
            v25 = this->scanServers.list;
            this->scanServers.size = v24;
            if ( v24 < v22 )
              this->scanServers.num = v24;
            v26 = (inServer_t *)Memory::Allocate(20 * v24);
            v27 = 0;
            v15 = this->scanServers.num <= 0;
            this->scanServers.list = v26;
            if ( !v15 )
            {
              v28 = 0;
              do
              {
                v29 = &this->scanServers.list[v28];
                v29->adr.type = v25[v28].adr.type;
                *(_DWORD *)v29->adr.ip = *(_DWORD *)v25[v28].adr.ip;
                *(_DWORD *)&v29->adr.port = *(_DWORD *)&v25[v28].adr.port;
                v29->id = v25[v28].id;
                ++v27;
                v29->time = v25[v28++].time;
              }
              while ( v27 < this->scanServers.num );
            }
            if ( v25 )
              Memory::Free(v25);
          }
        }
        else
        {
          if ( this->scanServers.list )
            Memory::Free(this->scanServers.list);
          this->scanServers.list = 0;
          this->scanServers.num = 0;
          this->scanServers.size = 0;
        }
      }
      this->scanServers.list[this->scanServers.num++] = newServer;
    }
    rvServerScan::UpdateFriend(this, guid, name, clan);
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::AddFriend() - Master server replied with friend '%s', which we do not have on our local list\n",
      guid);
  }
}

// FUNC: public: __thiscall rvServerScanGUI::rvServerScanGUI(void)
void __thiscall rvServerScanGUI::rvServerScanGUI(rvServerScanGUI *this)
{
  this->serverList.granularity = 16;
  this->serverList.list = 0;
  this->serverList.num = 0;
  this->serverList.size = 0;
  this->friendsList.granularity = 16;
  this->friendsList.list = 0;
  this->friendsList.num = 0;
  this->friendsList.size = 0;
  this->listName.len = 0;
  this->listName.alloced = 20;
  this->listName.data = this->listName.baseBuffer;
  this->listName.baseBuffer[0] = 0;
  this->friendsListName.len = 0;
  this->friendsListName.alloced = 20;
  this->friendsListName.data = this->friendsListName.baseBuffer;
  this->friendsListName.baseBuffer[0] = 0;
  this->multifieldSort.sortingFields.list = 0;
  this->multifieldSort.sortingFields.num = 0;
  this->multifieldSort.sortingFields.size = 0;
  this->multifieldSort.sortingFields.granularity = 16;
  this->scanGUI = 0;
  this->currentSort[0] = 0;
  this->currentSort[1] = 0;
  this->currentSort[2] = 0;
  this->currentSort[3] = 0;
  this->currentSort[4] = 0;
  this->currentSort[5] = 0;
  this->currentSort[6] = 0;
  this->currentSort[7] = 0;
  this->currentSort[8] = 0;
}

// FUNC: public: void __thiscall rvServerScanGUI::NewServer(int)
void __userpurge rvServerScanGUI::NewServer(rvServerScanGUI *this@<ecx>, int a2@<ebx>, int a3@<edi>, int serverIndex)
{
  int granularity; // eax
  bool v6; // cc
  int i; // eax
  int size; // ecx
  int num; // ebx
  int v10; // ecx
  int *list; // edi
  int j; // eax
  idUserInterface_vtbl *v14; // ebx
  int v15; // edi
  char *v16; // eax
  int v17; // eax
  idUserInterface_vtbl *v18; // ebx
  char *v19; // eax
  int numScanned; // ebx
  int numServers; // edi
  networkServer_t *v22; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  idUserInterface_vtbl *v25; // ebp
  const char *v26; // eax
  char *v27; // eax
  idUserInterface *scanGUI; // ecx
  const idKeyValue *v29; // eax
  const char *v30; // eax
  idUserInterface_vtbl *v31; // edi
  const char *v32; // eax
  char *v33; // eax
  char *v34; // [esp+20h] [ebp-18h]
  int v36; // [esp+24h] [ebp-14h]
  int v37; // [esp+24h] [ebp-14h]
  int v39; // [esp+28h] [ebp-10h]
  int v40; // [esp+28h] [ebp-10h]
  float v41; // [esp+28h] [ebp-10h]
  int v42; // [esp+28h] [ebp-10h]
  char *serverIndexb; // [esp+3Ch] [ebp+4h]
  int serverIndexa; // [esp+3Ch] [ebp+4h]
  int v45; // [esp+44h] [ebp+Ch]

  if ( this->scanGUI )
  {
    if ( !this->serverList.list )
    {
      granularity = this->serverList.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->serverList.size )
        {
          v6 = granularity < this->serverList.num;
          this->serverList.size = granularity;
          if ( v6 )
            this->serverList.num = granularity;
          this->serverList.list = (int *)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->serverList.num; ++i )
            this->serverList.list[i] = *(_DWORD *)(4 * i);
        }
      }
      else
      {
        this->serverList.list = 0;
        this->serverList.num = 0;
        this->serverList.size = 0;
      }
    }
    size = this->serverList.size;
    num = this->serverList.num;
    if ( num == size )
    {
      if ( !this->serverList.granularity )
        this->serverList.granularity = 16;
      v10 = this->serverList.granularity + size - (this->serverList.granularity + size) % this->serverList.granularity;
      if ( v10 > 0 )
      {
        if ( v10 != this->serverList.size )
        {
          list = this->serverList.list;
          this->serverList.size = v10;
          if ( v10 < num )
            this->serverList.num = v10;
          this->serverList.list = (int *)Memory::Allocate(4 * v10);
          for ( j = 0; j < this->serverList.num; ++j )
            this->serverList.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->serverList.list )
          Memory::Free(this->serverList.list);
        this->serverList.list = 0;
        this->serverList.num = 0;
        this->serverList.size = 0;
      }
    }
    this->serverList.list[this->serverList.num++] = serverIndex;
    v14 = this->scanGUI->__vftable;
    v15 = this->serverList.num - 1;
    serverIndexb = this->listName.data;
    v34 = rvServerScanGUI::BuildListString(this, v15);
    v16 = va("%s_item_%i", serverIndexb, v15);
    ((void (__thiscall *)(idUserInterface *, char *, char *, int, int))v14->SetStateString)(
      this->scanGUI,
      v16,
      v34,
      a3,
      a2);
    v17 = this->serverList.list[v15];
    LOBYTE(v17) = idAsyncNetwork::client.serverList.activeServers.list[v17].performanceFiltered;
    v18 = this->scanGUI->__vftable;
    if ( (_BYTE)v17 )
      v39 = v17;
    else
      v39 = 0;
    v19 = va("%s_item_%i_greyed", this->listName.data, v15);
    v18->SetStateBool(this->scanGUI, v19, v39);
    numScanned = idAsyncNetwork::client.serverList.numScanned;
    numServers = idAsyncNetwork::client.serverList.numServers;
    v22 = &idAsyncNetwork::client.serverList.activeServers.list[serverIndex];
    v45 = idAsyncNetwork::client.serverList.numScanned;
    serverIndexa = idAsyncNetwork::client.serverList.numServers;
    if ( idAsyncNetwork::client.serverList.scanState == NET_SCAN )
    {
      Key = idDict::FindKey(&v22->serverInfo, "si_name");
      if ( Key )
        data = Key->value->data;
      else
        data = &entityFilter;
      v25 = this->scanGUI->__vftable;
      v26 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int, int, const char *))(*(_DWORD *)common.type + 168))(
                            common.type,
                            "#str_107297",
                            -1,
                            numScanned,
                            numServers,
                            data);
      v27 = va(v26);
      ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v25->SetStateString)(
        this->scanGUI,
        "loadNotice",
        v27,
        v36,
        v40);
      scanGUI = this->scanGUI;
      if ( numServers )
      {
        v41 = (double)v45 / (double)serverIndexa;
        ((void (__stdcall *)(const char *, _DWORD))scanGUI->SetStateFloat)("loadPct", LODWORD(v41));
      }
      else
      {
        ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))scanGUI->SetStateFloat)(scanGUI, "loadPct", 0);
      }
    }
    else if ( idAsyncNetwork::client.serverList.scanState == LAN_SCAN )
    {
      v29 = idDict::FindKey(&v22->serverInfo, "si_name");
      if ( v29 )
        v30 = v29->value->data;
      else
        v30 = &entityFilter;
      v31 = this->scanGUI->__vftable;
      v32 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, const char *))(*(_DWORD *)common.type
                                                                                               + 168))(
                            common.type,
                            "#str_107298",
                            -1,
                            v30);
      v33 = va(v32);
      ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))v31->SetStateString)(
        this->scanGUI,
        "loadNotice",
        v33,
        v37,
        v42);
    }
    this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::NewServer() - invalid scanGUI\n");
  }
}

// FUNC: public: void __thiscall rvServerScanGUI::FriendAdd(int)
void __thiscall rvServerScanGUI::FriendAdd(rvServerScanGUI *this, int index)
{
  idList<rvPair<int,int> > *p_friendsList; // esi
  int size; // eax
  int num; // ecx
  rvPair<int,int> *list; // edx

  p_friendsList = &this->friendsList;
  if ( !this->friendsList.list )
    idList<rvPair<int,int>>::Resize(&this->friendsList, this->friendsList.granularity);
  size = p_friendsList->size;
  if ( p_friendsList->num == size )
  {
    if ( !p_friendsList->granularity )
      p_friendsList->granularity = 16;
    idList<rvPair<int,int>>::Resize(
      p_friendsList,
      size + p_friendsList->granularity - (size + p_friendsList->granularity) % p_friendsList->granularity);
  }
  num = p_friendsList->num;
  list = p_friendsList->list;
  list[num].first = index;
  list[num].second = -1;
  rvServerScanGUI::FriendUpdate(this, p_friendsList->num++);
}

// FUNC: public: void __thiscall rvServerScan::Clear(bool)
void __thiscall rvServerScan::Clear(rvServerScan *this, bool shutdown)
{
  inServer_t *list; // eax
  networkServer_t *v4; // eax
  bool *p_favorite; // edi

  list = this->scanServers.list;
  this->scanIndex = 0;
  this->scanState = IDLE;
  this->lastScan = IDLE;
  this->masterServerTimeout = 0;
  this->numServers = 0;
  this->numScanned = 0;
  this->scanStartTime = 0;
  if ( list )
    Memory::Free(list);
  this->scanServers.list = 0;
  this->scanServers.num = 0;
  this->scanServers.size = 0;
  v4 = this->activeServers.list;
  if ( v4 )
  {
    p_favorite = &v4[-1].favorite;
    `eh vector destructor iterator'(
      v4,
      0x910u,
      *(_DWORD *)&v4[-1].favorite,
      (void (__thiscall *)(void *))networkServer_t::~networkServer_t);
    Memory::Free(p_favorite);
  }
  this->activeServers.list = 0;
  this->activeServers.num = 0;
  this->activeServers.size = 0;
  if ( this->activeFriends.list )
    Memory::Free(this->activeFriends.list);
  this->activeFriends.list = 0;
  this->activeFriends.num = 0;
  this->activeFriends.size = 0;
  if ( shutdown )
    rvServerScan::Shutdown(this);
}

// FUNC: public: void __thiscall rvServerScan::NetScan(char const *,char const *)
void __userpurge rvServerScan::NetScan(
        rvServerScan *this@<ecx>,
        int a2@<ebp>,
        const char *playerName,
        const char *clanName)
{
  int v5; // edi
  bool v6; // cc

  rvServerScan::Clear(this, 0);
  ++this->challenge;
  this->masterServerTimeout = Sys_Milliseconds() + 1500;
  idAsyncClient::GetNETServers(&idAsyncNetwork::client, playerName, clanName);
  this->scanStartTime = Sys_Milliseconds();
  v5 = 0;
  v6 = this->callbacks[1].num <= 0;
  this->scanState = NET_SCAN;
  this->lastScan = NET_SCAN;
  if ( !v6 )
  {
    do
    {
      rvServerScanGUI::StartScan(this->callbacks[1].list[v5], a2, v5, 0);
      ++v5;
    }
    while ( v5 < this->callbacks[1].num );
  }
}

// FUNC: public: void __thiscall rvServerScan::FriendScan(void)
void __usercall rvServerScan::FriendScan(rvServerScan *this@<ecx>, int a2@<edi>)
{
  int v3; // eax
  int v4; // esi
  bool v5; // cc
  bool v6; // zf
  int granularity; // eax
  friend_t *v8; // eax
  int v9; // edx
  int v10; // eax
  int num; // edi
  int size; // ecx
  int v13; // ecx
  friend_t *list; // ebx
  friend_t *v15; // eax
  int v16; // edx
  int v17; // eax
  int v18; // edi
  rvServerScanGUI *v19; // ebx
  idList<rvPair<int,int> > *p_friendsList; // esi
  int v21; // ecx
  int v22; // edx
  rvPair<int,int> *v23; // ecx
  int i; // [esp+14h] [ebp-ACh]
  int index; // [esp+1Ch] [ebp-A4h]
  friend_t newFriend; // [esp+20h] [ebp-A0h] BYREF

  rvServerScan::Clear(this, 0);
  ++this->challenge;
  this->scanState = 4;
  this->lastScan = 4;
  this->masterServerTimeout = Sys_Milliseconds() + 1500;
  v3 = Sys_Milliseconds();
  v4 = 0;
  v5 = this->callbacks[1].num <= 0;
  this->scanStartTime = v3;
  if ( !v5 )
  {
    do
      rvServerScanGUI::StartScan(this->callbacks[1].list[v4++], (int)this, a2, 0);
    while ( v4 < this->callbacks[1].num );
  }
  for ( i = 0; i < rvServerScan::GetNumFriendsInFriendsList(this); ++i )
  {
    memset(&newFriend, 0, sizeof(newFriend));
    rvServerScan::GetFriendFromFriendsList(this, &newFriend, i);
    v6 = this->activeFriends.list == 0;
    newFriend.online = 0;
    newFriend.server.type = NA_BAD;
    if ( v6 )
    {
      granularity = this->activeFriends.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->activeFriends.size )
        {
          v5 = granularity < this->activeFriends.num;
          this->activeFriends.size = granularity;
          if ( v5 )
            this->activeFriends.num = granularity;
          v8 = (friend_t *)Memory::Allocate(156 * granularity);
          v9 = 0;
          v5 = this->activeFriends.num <= 0;
          this->activeFriends.list = v8;
          if ( !v5 )
          {
            v10 = 0;
            do
            {
              ++v9;
              qmemcpy(&this->activeFriends.list[v10], (const void *)(v10 * 156), sizeof(this->activeFriends.list[v10]));
              ++v10;
            }
            while ( v9 < this->activeFriends.num );
          }
        }
      }
      else
      {
        this->activeFriends.list = 0;
        this->activeFriends.num = 0;
        this->activeFriends.size = 0;
      }
    }
    num = this->activeFriends.num;
    size = this->activeFriends.size;
    if ( num == size )
    {
      if ( !this->activeFriends.granularity )
        this->activeFriends.granularity = 16;
      v13 = this->activeFriends.granularity
          + size
          - (this->activeFriends.granularity + size) % this->activeFriends.granularity;
      if ( v13 > 0 )
      {
        if ( v13 != this->activeFriends.size )
        {
          list = this->activeFriends.list;
          this->activeFriends.size = v13;
          if ( v13 < num )
            this->activeFriends.num = v13;
          v15 = (friend_t *)Memory::Allocate(156 * v13);
          v16 = 0;
          v5 = this->activeFriends.num <= 0;
          this->activeFriends.list = v15;
          if ( !v5 )
          {
            v17 = 0;
            do
            {
              ++v16;
              qmemcpy(&this->activeFriends.list[v17], &list[v17], sizeof(this->activeFriends.list[v17]));
              ++v17;
            }
            while ( v16 < this->activeFriends.num );
          }
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->activeFriends.list )
          Memory::Free(this->activeFriends.list);
        this->activeFriends.list = 0;
        this->activeFriends.num = 0;
        this->activeFriends.size = 0;
      }
    }
    qmemcpy(
      &this->activeFriends.list[this->activeFriends.num++],
      &newFriend,
      sizeof(this->activeFriends.list[this->activeFriends.num++]));
    v18 = 0;
    for ( index = this->activeFriends.num - 1; v18 < this->callbacks[6].num; ++v18 )
    {
      v19 = this->callbacks[6].list[v18];
      p_friendsList = &v19->friendsList;
      if ( !v19->friendsList.list )
        idList<rvPair<int,int>>::Resize(&v19->friendsList, v19->friendsList.granularity);
      v21 = v19->friendsList.size;
      if ( p_friendsList->num == v21 )
      {
        if ( !v19->friendsList.granularity )
          v19->friendsList.granularity = 16;
        idList<rvPair<int,int>>::Resize(
          p_friendsList,
          v19->friendsList.granularity + v21 - (v19->friendsList.granularity + v21) % v19->friendsList.granularity);
      }
      v22 = p_friendsList->num;
      v23 = v19->friendsList.list;
      v23[v22].first = index;
      v23[v22].second = -1;
      rvServerScanGUI::FriendUpdate(v19, p_friendsList->num++);
    }
  }
  idAsyncClient::GetFriends(&idAsyncNetwork::client);
}

// FUNC: public: void __thiscall rvServerScan::LanScan(void)
void __usercall rvServerScan::LanScan(rvServerScan *this@<ecx>, int a2@<ebp>)
{
  int i; // edi

  rvServerScan::Clear(this, 0);
  ++this->challenge;
  this->scanState = LAN_SCAN;
  this->lastScan = LAN_SCAN;
  this->scanStartTime = Sys_Milliseconds();
  idAsyncClient::GetLANServers(&idAsyncNetwork::client);
  for ( i = 0; i < this->callbacks[1].num; ++i )
    rvServerScanGUI::StartScan(this->callbacks[1].list[i], a2, i, 0);
}

// FUNC: public: void __thiscall rvServerScan::RemoveFriend(int)
void __thiscall rvServerScan::RemoveFriend(rvServerScan *this, int i)
{
  int num; // eax
  bool v4; // cc
  int v5; // eax
  int v6; // edx
  int v7; // edi
  int v8; // ebx
  int v9; // esi
  char *v10; // eax
  int v11; // eax
  rvServerScanGUI *v12; // ecx
  int v13; // edx
  int v14; // eax
  rvPair<int,int> *list; // edi
  rvPair<int,int> *v16; // esi
  int z; // [esp+10h] [ebp-Ch]
  int j; // [esp+14h] [ebp-8h]
  int v19; // [esp+18h] [ebp-4h]
  int ia; // [esp+20h] [ebp+4h]

  if ( i < 0 || i >= this->activeFriends.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScan::RemoveFriend() - Invalid friend id '%d'\n",
      i);
  }
  else
  {
    rvServerScan::RemoveFromFriendsList(this, this->activeFriends.list[i].guid);
    num = this->activeFriends.num;
    if ( i < num )
    {
      v4 = i < num - 1;
      this->activeFriends.num = num - 1;
      v5 = i;
      if ( v4 )
      {
        v6 = i;
        do
        {
          ++v5;
          qmemcpy(
            &this->activeFriends.list[v6],
            &this->activeFriends.list[v6 + 1],
            sizeof(this->activeFriends.list[v6]));
          ++v6;
        }
        while ( v5 < this->activeFriends.num );
      }
    }
    v7 = 0;
    v8 = 0;
    if ( this->activeFriends.num > 0 )
    {
      v19 = 0;
      ia = 0;
      do
      {
        v9 = 0;
        for ( *(&this->activeFriends.list->online + v7) = 0; v9 < this->callbacks[6].num; ++v9 )
          rvServerScanGUI::FriendAdd(this->callbacks[6].list[v9], v8);
        for ( z = 0; z < this->activeServers.num; ++z )
        {
          if ( Sys_CompareNetAdrBase(
                 this->activeServers.list[ia].adr,
                 *(const netadr_t *)((char *)&this->activeFriends.list->server + v7)) )
          {
            v10 = &this->activeFriends.list->guid[v7];
            if ( this->activeServers.list[ia].adr.port == *((_WORD *)v10 + 74) )
            {
              v10[152] = 1;
              v11 = 0;
              j = 0;
              if ( this->callbacks[5].num > 0 )
              {
                do
                {
                  v12 = this->callbacks[5].list[v11];
                  v13 = v12->friendsList.num;
                  v14 = 0;
                  if ( v13 <= 0 )
                  {
LABEL_19:
                    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
                      common.type,
                      "rvServerScanGUI::FriendOnline() - Called with unknown friend '%d'\n",
                      v8);
                  }
                  else
                  {
                    list = v12->friendsList.list;
                    v16 = list;
                    while ( v16->first != v8 )
                    {
                      ++v14;
                      ++v16;
                      if ( v14 >= v13 )
                        goto LABEL_19;
                    }
                    list[v14].first = v8;
                    list[v14].second = z;
                    rvServerScanGUI::FriendUpdate(v12, v14);
                  }
                  v11 = ++j;
                }
                while ( j < this->callbacks[5].num );
                v7 = v19;
              }
            }
          }
        }
        ++ia;
        ++v8;
        v7 += 156;
        v19 = v7;
      }
      while ( v8 < this->activeFriends.num );
    }
  }
}

// FUNC: public: void __thiscall rvServerScanGUI::RemoveFromFriendsList(int)
void __userpurge rvServerScanGUI::RemoveFromFriendsList(
        rvServerScanGUI *this@<ecx>,
        int a2@<ebp>,
        signed int a3@<edi>,
        int listIndex)
{
  int num; // ecx
  int first; // ebp
  int v7; // edi
  idUserInterface_vtbl *v8; // ebx
  char *v9; // eax
  idUserInterface_vtbl *v10; // ebx
  char *v11; // eax
  signed int i; // edi
  idGame_vtbl *v13; // ebp
  int v14; // eax

  if ( listIndex < 0 || (num = this->friendsList.num, listIndex >= num) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "rvServerScanGUI::RemoveFromFriendsList() - Invalid friend index '%d'\n",
      listIndex);
  }
  else
  {
    first = this->friendsList.list[listIndex].first;
    v7 = 0;
    if ( num > 0 )
    {
      do
      {
        v8 = this->scanGUI->__vftable;
        v9 = va("%s_item_%i", this->friendsListName.data, v7);
        v8->SetStateString(this->scanGUI, v9, &entityFilter);
        v10 = this->scanGUI->__vftable;
        v11 = va("%s_item_%i_greyed", this->friendsListName.data, v7);
        v10->SetStateBool(this->scanGUI, v11, 0);
        ++v7;
      }
      while ( v7 < this->friendsList.num );
    }
    if ( this->friendsList.list )
      Memory::Free(this->friendsList.list);
    this->friendsList.list = 0;
    this->friendsList.num = 0;
    this->friendsList.size = 0;
    rvServerScan::RemoveFriend(&idAsyncNetwork::client.serverList, first);
    if ( game && (idAsyncNetwork::server.active || idAsyncNetwork::client.active) )
    {
      for ( i = 0; i < 32; ++i )
      {
        if ( ((int (__thiscall *)(idNetworkSystem *, signed int, signed int, int))networkSystem->GetClientGUID)(
               networkSystem,
               i,
               a3,
               a2) )
        {
          v13 = game->__vftable;
          LOBYTE(v14) = rvServerScan::IsAFriend(&idAsyncNetwork::client.serverList, i);
          a2 = v14;
          a3 = i;
          ((void (__thiscall *)(idGame *))v13->SetFriend)(game);
        }
        else
        {
          a2 = 0;
          a3 = i;
          ((void (__thiscall *)(idGame *))game->SetFriend)(game);
        }
      }
    }
    this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
  }
}

// FUNC: public: __thiscall rvServerScan::rvServerScan(void)
void __thiscall rvServerScan::rvServerScan(rvServerScan *this)
{
  this->scanServers.granularity = 16;
  this->scanServers.list = 0;
  this->scanServers.num = 0;
  this->scanServers.size = 0;
  this->activeServers.granularity = 16;
  this->activeServers.list = 0;
  this->activeServers.num = 0;
  this->activeServers.size = 0;
  this->activeFriends.granularity = 16;
  this->activeFriends.list = 0;
  this->activeFriends.num = 0;
  this->activeFriends.size = 0;
  `eh vector constructor iterator'(
    this->callbacks,
    0x10u,
    7,
    (void (__thiscall *)(void *))idList<rvServerScanGUI *>::`default constructor closure',
    (void (__thiscall *)(void *))idList<idDeclFolder *>::~idList<idDeclFolder *>);
  rvServerScan::Clear(this, 0);
  this->challenge = 0;
}

// FUNC: public: void __thiscall rvServerScan::Refresh(void)
void __usercall rvServerScan::Refresh(rvServerScan *this@<ecx>, int a2@<edi>)
{
  scan_state_t lastScan; // ecx
  int num; // eax
  networkServer_t *v5; // eax
  int granularity; // eax
  bool v7; // cc
  inServer_t *v8; // eax
  int v9; // ecx
  netadrtype_t *v10; // eax
  inServer_t *v11; // edx
  int v12; // ebx
  int size; // ecx
  int v14; // ecx
  inServer_t *list; // edi
  inServer_t *v16; // eax
  int v17; // ecx
  int v18; // eax
  inServer_t *v19; // ebx
  inServer_t *v20; // edx
  networkServer_t *v21; // eax
  bool *p_favorite; // edi
  int v23; // eax
  int v24; // edi
  int v25; // [esp+8h] [ebp-1Ch]
  int i; // [esp+Ch] [ebp-18h]
  netadrtype_t newServer; // [esp+10h] [ebp-14h]
  int newServer_4; // [esp+14h] [ebp-10h]
  int newServer_8; // [esp+18h] [ebp-Ch]
  int newServer_12; // [esp+1Ch] [ebp-8h]

  if ( this->scanServers.list )
    Memory::Free(this->scanServers.list);
  lastScan = this->lastScan;
  num = this->activeServers.num;
  this->scanServers.list = 0;
  this->scanServers.num = 0;
  this->scanServers.size = 0;
  this->numServers = num;
  if ( lastScan == LAN_SCAN )
  {
    rvServerScan::LanScan(this, 0);
  }
  else if ( lastScan == 4 )
  {
    rvServerScan::FriendScan(this, a2);
  }
  else if ( num )
  {
    this->numScanned = 0;
    i = 0;
    if ( num > 0 )
    {
      v25 = 0;
      do
      {
        v5 = &this->activeServers.list[v25];
        newServer = v5->adr.type;
        newServer_4 = *(_DWORD *)v5->adr.ip;
        newServer_8 = *(_DWORD *)&v5->adr.port;
        if ( !this->scanServers.list )
        {
          granularity = this->scanServers.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->scanServers.size )
            {
              v7 = granularity < this->scanServers.num;
              this->scanServers.size = granularity;
              if ( v7 )
                this->scanServers.num = granularity;
              v8 = (inServer_t *)Memory::Allocate(20 * granularity);
              v9 = 0;
              v7 = this->scanServers.num <= 0;
              this->scanServers.list = v8;
              if ( !v7 )
              {
                v10 = 0;
                do
                {
                  v11 = (inServer_t *)((char *)v10 + (unsigned int)this->scanServers.list);
                  v11->adr.type = *v10;
                  *(netadrtype_t *)v11->adr.ip = v10[1];
                  *(netadrtype_t *)&v11->adr.port = v10[2];
                  v11->id = v10[3];
                  ++v9;
                  v11->time = v10[4];
                  v10 += 5;
                }
                while ( v9 < this->scanServers.num );
              }
            }
          }
          else
          {
            this->scanServers.list = 0;
            this->scanServers.num = 0;
            this->scanServers.size = 0;
          }
        }
        v12 = this->scanServers.num;
        size = this->scanServers.size;
        if ( this->scanServers.num == size )
        {
          if ( !this->scanServers.granularity )
            this->scanServers.granularity = 16;
          v14 = this->scanServers.granularity
              + size
              - (this->scanServers.granularity + size) % this->scanServers.granularity;
          if ( v14 > 0 )
          {
            if ( v14 != this->scanServers.size )
            {
              list = this->scanServers.list;
              this->scanServers.size = v14;
              if ( v14 < v12 )
                this->scanServers.num = v14;
              v16 = (inServer_t *)Memory::Allocate(20 * v14);
              v17 = 0;
              v7 = this->scanServers.num <= 0;
              this->scanServers.list = v16;
              if ( !v7 )
              {
                v18 = 0;
                do
                {
                  v19 = &this->scanServers.list[v18];
                  v19->adr.type = list[v18].adr.type;
                  *(_DWORD *)v19->adr.ip = *(_DWORD *)list[v18].adr.ip;
                  *(_DWORD *)&v19->adr.port = *(_DWORD *)&list[v18].adr.port;
                  v19->id = list[v18].id;
                  ++v17;
                  v19->time = list[v18++].time;
                }
                while ( v17 < this->scanServers.num );
              }
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( this->scanServers.list )
              Memory::Free(this->scanServers.list);
            this->scanServers.list = 0;
            this->scanServers.num = 0;
            this->scanServers.size = 0;
          }
        }
        ++v25;
        v20 = &this->scanServers.list[this->scanServers.num];
        v20->adr.type = newServer;
        *(_DWORD *)v20->adr.ip = newServer_4;
        *(_DWORD *)&v20->adr.port = newServer_8;
        v20->id = newServer_12;
        v20->time = 0;
        ++this->scanServers.num;
        ++i;
      }
      while ( i < this->activeServers.num );
    }
    v21 = this->activeServers.list;
    if ( v21 )
    {
      p_favorite = &v21[-1].favorite;
      `eh vector destructor iterator'(
        v21,
        0x910u,
        *(_DWORD *)&v21[-1].favorite,
        (void (__thiscall *)(void *))networkServer_t::~networkServer_t);
      Memory::Free(p_favorite);
    }
    this->activeServers.list = 0;
    this->activeServers.num = 0;
    this->activeServers.size = 0;
    this->scanState = this->lastScan;
    v23 = Sys_Milliseconds();
    v24 = 0;
    v7 = this->callbacks[1].num <= 0;
    this->scanStartTime = v23;
    if ( !v7 )
    {
      do
      {
        rvServerScanGUI::StartScan(this->callbacks[1].list[v24], 0, v24, 1);
        ++v24;
      }
      while ( v24 < this->callbacks[1].num );
    }
  }
  else
  {
    rvServerScan::NetScan(this, 0, &entityFilter, &entityFilter);
  }
}

// FUNC: public: int __thiscall rvServerScan::AddActiveServer(struct networkServer_t &)
int __thiscall rvServerScan::AddActiveServer(rvServerScan *this, networkServer_t *newServer)
{
  scan_state_t scanState; // eax
  int v4; // esi
  networkServer_t *v5; // ebp
  int v6; // esi
  int v8; // ebx
  int v9; // edi
  const char *value; // edi
  const char *v11; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int v14; // esi
  const char *v15; // eax
  int v16; // edi
  int v17; // ebx
  int v18; // esi
  const char *v19; // eax
  inServer_t *v20; // ebx
  int v21; // eax
  int v22; // ecx
  inServer_t *v23; // eax
  idList<networkServer_t> *p_activeServers; // edi
  int size; // ecx
  int v26; // ebx
  int v27; // edi
  const char *v28; // eax
  int i; // edi
  int v30; // ebx
  int v31; // edi
  friend_t *list; // edx
  int v33; // eax
  rvServerScanGUI *v34; // ecx
  int num; // edx
  int v36; // eax
  rvPair<int,int> *v37; // ebp
  rvPair<int,int> *v38; // edi
  const char *v39; // [esp-10h] [ebp-2Ch]
  const char *v40; // [esp-10h] [ebp-2Ch]
  int index; // [esp+10h] [ebp-Ch]
  int j; // [esp+14h] [ebp-8h]
  int v43; // [esp+18h] [ebp-4h]

  scanState = this->scanState;
  if ( scanState == IDLE )
  {
    v4 = *(_DWORD *)common.type;
    v39 = Sys_NetAdrToString(newServer->adr);
    (*(void (__cdecl **)(netadrtype_t, const char *, const char *))(v4 + 136))(
      common.type,
      "rvServerScan::AddActiveServer() - Info response from %s while not scanning\n",
      v39);
    return -1;
  }
  v5 = newServer;
  if ( newServer->challenge != this->challenge )
  {
    v6 = *(_DWORD *)common.type;
    v40 = Sys_NetAdrToString(newServer->adr);
    (*(void (__cdecl **)(netadrtype_t, const char *, const char *))(v6 + 136))(
      common.type,
      "rvServerScan::AddActiveServer() - Unexpected info response from %s\n",
      v40);
    return -1;
  }
  if ( scanState == NET_SCAN || scanState == 4 )
  {
    v16 = 0;
    if ( this->scanServers.num <= 0 )
    {
LABEL_23:
      v18 = *(_DWORD *)common.type;
      v19 = Sys_NetAdrToString(newServer->adr);
      (*(void (**)(netadrtype_t, const char *, ...))(v18 + 136))(
        common.type,
        "rvServerScan::AddActiveServer() - Unexpected active server '%s'\n",
        v19);
      return -1;
    }
    v17 = 0;
    while ( !Sys_CompareNetAdrBase(this->scanServers.list[v17].adr, newServer->adr)
         || this->scanServers.list[v17].adr.port != newServer->adr.port )
    {
      ++v16;
      ++v17;
      if ( v16 >= this->scanServers.num )
        goto LABEL_23;
    }
    v20 = &this->scanServers.list[v16];
    newServer->ping = 999 - v20->time + Sys_Milliseconds();
    if ( v16 >= 0 && v16 < this->scanServers.num )
    {
      v21 = this->scanServers.num - 1;
      this->scanServers.num = v21;
      if ( v16 < v21 )
      {
        v22 = v16;
        do
        {
          v23 = &this->scanServers.list[v22];
          v23->adr.type = v23[1].adr.type;
          *(_DWORD *)v23->adr.ip = *(_DWORD *)v23[1].adr.ip;
          *(_DWORD *)&v23->adr.port = *(_DWORD *)&v23[1].adr.port;
          v23->id = v23[1].id;
          ++v16;
          v23->time = v23[1].time;
          ++v22;
        }
        while ( v16 < this->scanServers.num );
      }
    }
    ++this->numScanned;
    goto LABEL_15;
  }
  if ( scanState != LAN_SCAN )
  {
LABEL_15:
    value = g_favoritesList.internalVar->value;
    v11 = Sys_NetAdrToString(newServer->adr);
    newServer->favorite = strstr(value, v11) != 0;
    Key = idDict::FindKey(&newServer->serverInfo, "net_serverDedicated");
    if ( Key )
      data = Key->value->data;
    else
      data = "0";
    newServer->dedicated = atoi(data) > 0;
    rvServerScan::SetPerformanceFlag(this, newServer);
    p_activeServers = &this->activeServers;
    if ( !this->activeServers.list )
      idList<networkServer_t>::Resize(&this->activeServers, this->activeServers.granularity);
    size = this->activeServers.size;
    if ( p_activeServers->num == size )
    {
      if ( !this->activeServers.granularity )
        this->activeServers.granularity = 16;
      idList<networkServer_t>::Resize(
        &this->activeServers,
        this->activeServers.granularity
      + size
      - (this->activeServers.granularity + size) % this->activeServers.granularity);
    }
    networkServer_t::operator=((char *)&this->activeServers.list[p_activeServers->num], (int)newServer);
    v26 = p_activeServers->num++;
    v27 = *(_DWORD *)common.type;
    index = v26;
    v28 = Sys_NetAdrToString(newServer->adr);
    (*(void (**)(netadrtype_t, const char *, ...))(v27 + 124))(
      common.type,
      "rvServerScan::AddActiveServer() - Added active server %s\n",
      v28);
    for ( i = 0; i < this->callbacks[3].num; ++i )
      rvServerScanGUI::NewServer(this->callbacks[3].list[i], v26, i, v26);
    if ( this->scanState == 4 )
    {
      v30 = 0;
      if ( this->activeFriends.num > 0 )
      {
        v31 = 0;
        v43 = 0;
        do
        {
          if ( Sys_CompareNetAdrBase(v5->adr, *(const netadr_t *)((char *)&this->activeFriends.list->server + v31)) )
          {
            list = this->activeFriends.list;
            if ( v5->adr.port == *(_WORD *)&list->server.ip[v31 + 4] )
            {
              *(&list->online + v31) = 1;
              v33 = 0;
              j = 0;
              if ( this->callbacks[5].num > 0 )
              {
                do
                {
                  v34 = this->callbacks[5].list[v33];
                  num = v34->friendsList.num;
                  v36 = 0;
                  if ( num <= 0 )
                  {
LABEL_50:
                    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
                      common.type,
                      "rvServerScanGUI::FriendOnline() - Called with unknown friend '%d'\n",
                      v30);
                  }
                  else
                  {
                    v37 = v34->friendsList.list;
                    v38 = v37;
                    while ( v38->first != v30 )
                    {
                      ++v36;
                      ++v38;
                      if ( v36 >= num )
                      {
                        v5 = newServer;
                        goto LABEL_50;
                      }
                    }
                    v37[v36].first = v30;
                    v37[v36].second = index;
                    rvServerScanGUI::FriendUpdate(v34, v36);
                    v5 = newServer;
                  }
                  v33 = ++j;
                }
                while ( j < this->callbacks[5].num );
                v31 = v43;
              }
            }
          }
          ++v30;
          v31 += 156;
          v43 = v31;
        }
        while ( v30 < this->activeFriends.num );
      }
      return index;
    }
    return v26;
  }
  v8 = 0;
  newServer->ping = Sys_Milliseconds() - this->scanStartTime;
  if ( this->activeServers.num <= 0 )
  {
LABEL_14:
    ++this->numScanned;
    ++this->numServers;
    goto LABEL_15;
  }
  v9 = 0;
  while ( !Sys_CompareNetAdrBase(this->activeServers.list[v9].adr, newServer->adr)
       || this->activeServers.list[v9].adr.port != newServer->adr.port )
  {
    ++v8;
    ++v9;
    if ( v8 >= this->activeServers.num )
      goto LABEL_14;
  }
  v14 = *(_DWORD *)common.type;
  v15 = Sys_NetAdrToString(newServer->adr);
  (*(void (**)(netadrtype_t, const char *, ...))(v14 + 136))(
    common.type,
    "rvServerScan::AddActiveServer() - Duplicate LAN response from %s\n",
    v15);
  return -1;
}

// FUNC: public: void __thiscall rvServerScan::AddTestServers(int)
void __thiscall rvServerScan::AddTestServers(rvServerScan *this, int num)
{
  int v3; // ebx
  int i; // esi
  int v5; // eax
  const char *v6; // eax
  int v7; // esi
  int v8; // eax
  const char *v9; // eax
  rvServerScan *v10; // edi
  char *v11; // edi
  const char *v12; // eax
  const char *v13; // eax
  int v14; // eax
  const char *v15; // eax
  int v16; // eax
  const char *v17; // eax
  int v18; // eax
  const char *v19; // eax
  int v20; // eax
  const char *v21; // eax
  int v22; // eax
  const char *v23; // eax
  int v24; // eax
  const char *v25; // eax
  int v26; // eax
  const char *v27; // eax
  int v28; // eax
  const char *v29; // eax
  const char *v30; // eax
  const char *v31; // eax
  int clients; // eax
  const char *v33; // eax
  const char *v34; // eax
  int v35; // [esp-14h] [ebp-944h]
  int v36; // [esp-10h] [ebp-940h]
  int v37; // [esp-Ch] [ebp-93Ch]
  int v38; // [esp-Ch] [ebp-93Ch]
  int v39; // [esp-Ch] [ebp-93Ch]
  int v40; // [esp-4h] [ebp-934h]
  networkServer_t fakeServer; // [esp+10h] [ebp-920h] BYREF
  int v43; // [esp+92Ch] [ebp-4h]
  int savedregs; // [esp+930h] [ebp+0h] BYREF

  rvRandom::mSeed = com_frameTime;
  srand(com_frameTime);
  v3 = 0;
  rvServerScan::Clear(this, 0);
  this->scanState = LAN_SCAN;
  this->lastScan = LAN_SCAN;
  this->scanStartTime = Sys_Milliseconds();
  for ( i = 0; i < this->callbacks[1].num; ++i )
    rvServerScanGUI::StartScan(this->callbacks[1].list[i], (int)&savedregs, (int)this, 0);
  networkServer_t::networkServer_t(&fakeServer);
  v43 = 0;
  if ( num > 0 )
  {
    do
    {
      v37 = rand() % 255;
      v36 = rand() % 255;
      v35 = rand() % 255;
      v5 = rand();
      v6 = va("%d.%d.%d.%d", v5 % 255, v35, v36, v37);
      Sys_StringToNetAdr(v6, &fakeServer.adr, 0);
      fakeServer.challenge = 0;
      v7 = 0;
      memset(fakeServer.nickname, 0, 2048);
      v8 = rvRandom::irand(0, 1);
      v9 = va("%i", v8);
      idDict::Set(&fakeServer.serverInfo, "net_serverDedicated", v9);
      fakeServer.id = v3;
      fakeServer.OSMask = 0;
      fakeServer.performanceFiltered = rvRandom::irand(0, 1) != 0;
      v10 = this;
      fakeServer.ping = rvRandom::irand(0, 1000);
      fakeServer.challenge = this->challenge;
      fakeServer.clients = 0;
      if ( rvRandom::irand(1, 16) > 0 )
      {
        v11 = fakeServer.nickname[0];
        do
        {
          v12 = va("Player %d", v7);
          strncpy(v11, v12, 0x20u);
          v13 = va("Player %d", v7);
          strncpy(v11, v13, 0x20u);
          fakeServer.pings[v7] = rvRandom::irand(0, 300);
          fakeServer.rate[v7] = rvRandom::irand(0, 1000);
          ++fakeServer.clients;
          ++v7;
          v11 += 32;
        }
        while ( v7 < rvRandom::irand(1, 16) );
        v10 = this;
      }
      v14 = rvRandom::irand(1, 20);
      v15 = va("%i", v14);
      idDict::Set(&fakeServer.serverInfo, "si_timeLimit", v15);
      v16 = rvRandom::irand(1, 20);
      v17 = va("%i", v16);
      idDict::Set(&fakeServer.serverInfo, "si_fragLimit", v17);
      v18 = rvRandom::irand(1, 20);
      v19 = va("%i", v18);
      idDict::Set(&fakeServer.serverInfo, "si_captureLimit", v19);
      v20 = rvRandom::irand(0, 1);
      v21 = va("%i", v20 != 0);
      idDict::Set(&fakeServer.serverInfo, "si_autobalance", v21);
      v22 = rvRandom::irand(0, 1);
      v23 = va("%i", v22 != 0);
      idDict::Set(&fakeServer.serverInfo, "si_pure", v23);
      v24 = rvRandom::irand(0, 1);
      v25 = va("%i", v24 != 0);
      idDict::Set(&fakeServer.serverInfo, "si_spectators", v25);
      v26 = rvRandom::irand(0, 1);
      v27 = va("%i", v26 != 0);
      idDict::Set(&fakeServer.serverInfo, "sv_punkbuster", v27);
      v28 = rvRandom::irand(0, 1);
      v29 = va("%i", v28 != 0);
      idDict::Set(&fakeServer.serverInfo, "si_usepass", v29);
      v30 = va("Quake 4 Server %d", v3);
      idDict::Set(&fakeServer.serverInfo, "si_name", v30);
      switch ( rvRandom::irand(1, 5) )
      {
        case 1:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "DM");
          goto LABEL_12;
        case 2:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "Team DM");
          goto LABEL_12;
        case 3:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "Tourney");
LABEL_12:
          v38 = rvRandom::irand(1, 9);
          v31 = va("mp/q4dm%d", v38);
          goto LABEL_16;
        case 4:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "CTF");
          goto LABEL_15;
        case 5:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "Arena CTF");
LABEL_15:
          v39 = rvRandom::irand(1, 5);
          v31 = va("mp/q4ctf%d", v39);
LABEL_16:
          idDict::Set(&fakeServer.serverInfo, "si_map", v31);
          break;
        default:
          break;
      }
      clients = rvRandom::irand(2, 16);
      if ( clients < fakeServer.clients )
        clients = fakeServer.clients;
      v33 = va("%i", clients);
      idDict::Set(&fakeServer.serverInfo, "si_maxPlayers", v33);
      v40 = Sys_Milliseconds() - fakeServer.ping;
      v34 = Sys_NetAdrToString(fakeServer.adr);
      rvServerScan::AddServer(v10, v34, v40);
      rvServerScan::AddActiveServer(v10, &fakeServer);
      ++v3;
    }
    while ( v3 < num );
  }
  v43 = -1;
  networkServer_t::~networkServer_t(&fakeServer);
}

// FUNC: public: void __thiscall rvServerScan::AddTestFriends(int)
void __userpurge rvServerScan::AddTestFriends(rvServerScan *this@<ecx>, int a2@<edi>, int num)
{
  int v4; // eax
  int v5; // esi
  bool v6; // cc
  char *v7; // eax
  char *clan; // edx
  char v9; // cl
  char *v10; // eax
  char *name; // edx
  char v12; // cl
  char *v13; // eax
  friend_t *p_newFriend; // edx
  char v15; // cl
  int v16; // eax
  const char *v17; // eax
  bool v18; // zf
  int granularity; // eax
  friend_t *v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edi
  int size; // eax
  int v25; // eax
  friend_t *v26; // eax
  int v27; // edx
  int v28; // eax
  char *v29; // eax
  rvServerScanGUI *v30; // esi
  int v31; // eax
  int j; // eax
  rvPair<int,int> *list; // ecx
  int v34; // ecx
  int v35; // ecx
  rvPair<int,int> *v36; // edi
  int k; // eax
  rvPair<int,int> *v38; // ecx
  int v39; // ecx
  rvPair<int,int> *v40; // edx
  int v41; // esi
  int v42; // edi
  friend_t *v43; // esi
  const char *v44; // eax
  int v45; // eax
  const char *v46; // eax
  int v47; // eax
  int challenge; // ecx
  int v49; // edi
  char *v50; // esi
  const char *v51; // eax
  const char *v52; // eax
  int v53; // eax
  const char *v54; // eax
  int v55; // eax
  const char *v56; // eax
  int v57; // eax
  const char *v58; // eax
  int v59; // eax
  const char *v60; // eax
  int v61; // eax
  const char *v62; // eax
  int v63; // eax
  const char *v64; // eax
  int v65; // eax
  const char *v66; // eax
  int v67; // eax
  const char *v68; // eax
  int v69; // esi
  const char *v70; // eax
  const char *v71; // eax
  int clients; // eax
  const char *v73; // eax
  netadr_t *v74; // edx
  int v75; // [esp-14h] [ebp-9ECh]
  int v76; // [esp-10h] [ebp-9E8h]
  int v77; // [esp-Ch] [ebp-9E4h]
  int v78; // [esp-Ch] [ebp-9E4h]
  int v79; // [esp-Ch] [ebp-9E4h]
  int i; // [esp+Ch] [ebp-9CCh]
  int ia; // [esp+Ch] [ebp-9CCh]
  int ib; // [esp+Ch] [ebp-9CCh]
  friend_t *ptr; // [esp+10h] [ebp-9C8h]
  char *ptra; // [esp+10h] [ebp-9C8h]
  char *ptrb; // [esp+10h] [ebp-9C8h]
  int index; // [esp+14h] [ebp-9C4h]
  friend_t newFriend; // [esp+18h] [ebp-9C0h] BYREF
  networkServer_t fakeServer; // [esp+B8h] [ebp-920h] BYREF
  int v89; // [esp+9D4h] [ebp-4h]
  int savedregs; // [esp+9D8h] [ebp+0h] BYREF

  rvRandom::mSeed = com_frameTime;
  srand(com_frameTime);
  rvServerScan::Clear(this, 0);
  ++this->challenge;
  this->scanState = 4;
  this->lastScan = 4;
  this->masterServerTimeout = Sys_Milliseconds() + 1500;
  v4 = Sys_Milliseconds();
  v5 = 0;
  v6 = this->callbacks[1].num <= 0;
  this->scanStartTime = v4;
  if ( !v6 )
  {
    do
      rvServerScanGUI::StartScan(this->callbacks[1].list[v5++], (int)&savedregs, a2, 0);
    while ( v5 < this->callbacks[1].num );
  }
  for ( i = 0; i < num; ++i )
  {
    memset(&newFriend, 0, sizeof(newFriend));
    v7 = va("Clan %d", i);
    clan = newFriend.clan;
    do
    {
      v9 = *v7;
      *clan++ = *v7++;
    }
    while ( v9 );
    v10 = va("Player %d", i);
    name = newFriend.name;
    do
    {
      v12 = *v10;
      *name++ = *v10++;
    }
    while ( v12 );
    newFriend.online = 0;
    v13 = va("abcdefgh%03d", i);
    p_newFriend = &newFriend;
    do
    {
      v15 = *v13;
      p_newFriend->guid[0] = *v13++;
      p_newFriend = (friend_t *)((char *)p_newFriend + 1);
    }
    while ( v15 );
    v77 = rand() % 255;
    v76 = rand() % 255;
    v75 = rand() % 255;
    v16 = rand();
    v17 = va("%d.%d.%d.%d", v16 % 255, v75, v76, v77);
    Sys_StringToNetAdr(v17, &newFriend.server, 0);
    v18 = this->activeFriends.list == 0;
    newFriend.server.type = NA_IP;
    if ( v18 )
    {
      granularity = this->activeFriends.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->activeFriends.size )
        {
          v6 = granularity < this->activeFriends.num;
          this->activeFriends.size = granularity;
          if ( v6 )
            this->activeFriends.num = granularity;
          v20 = (friend_t *)Memory::Allocate(156 * granularity);
          v21 = 0;
          v6 = this->activeFriends.num <= 0;
          this->activeFriends.list = v20;
          if ( !v6 )
          {
            v22 = 0;
            do
            {
              ++v21;
              qmemcpy(&this->activeFriends.list[v22], (const void *)(v22 * 156), sizeof(this->activeFriends.list[v22]));
              ++v22;
            }
            while ( v21 < this->activeFriends.num );
          }
        }
      }
      else
      {
        this->activeFriends.list = 0;
        this->activeFriends.num = 0;
        this->activeFriends.size = 0;
      }
    }
    v23 = this->activeFriends.num;
    size = this->activeFriends.size;
    if ( v23 == size )
    {
      if ( !this->activeFriends.granularity )
        this->activeFriends.granularity = 16;
      v25 = size
          + this->activeFriends.granularity
          - (size + this->activeFriends.granularity) % this->activeFriends.granularity;
      if ( v25 > 0 )
      {
        if ( v25 != this->activeFriends.size )
        {
          ptr = this->activeFriends.list;
          this->activeFriends.size = v25;
          if ( v25 < v23 )
            this->activeFriends.num = v25;
          v26 = (friend_t *)Memory::Allocate(156 * v25);
          v27 = 0;
          v6 = this->activeFriends.num <= 0;
          this->activeFriends.list = v26;
          if ( !v6 )
          {
            v28 = 0;
            do
            {
              ++v27;
              qmemcpy(&this->activeFriends.list[v28], &ptr[v28], sizeof(this->activeFriends.list[v28]));
              ++v28;
            }
            while ( v27 < this->activeFriends.num );
          }
          if ( ptr )
            Memory::Free(ptr);
        }
      }
      else
      {
        if ( this->activeFriends.list )
          Memory::Free(this->activeFriends.list);
        this->activeFriends.list = 0;
        this->activeFriends.num = 0;
        this->activeFriends.size = 0;
      }
    }
    qmemcpy(
      &this->activeFriends.list[this->activeFriends.num++],
      &newFriend,
      sizeof(this->activeFriends.list[this->activeFriends.num++]));
    index = this->activeFriends.num - 1;
    v29 = 0;
    for ( ptra = 0; (int)ptra < this->callbacks[6].num; ++ptra )
    {
      v30 = this->callbacks[6].list[(_DWORD)v29];
      if ( !v30->friendsList.list )
      {
        v31 = v30->friendsList.granularity;
        if ( v31 > 0 )
        {
          if ( v31 != v30->friendsList.size )
          {
            v6 = v31 < v30->friendsList.num;
            v30->friendsList.size = v31;
            if ( v6 )
              v30->friendsList.num = v31;
            v30->friendsList.list = (rvPair<int,int> *)Memory::Allocate(8 * v31);
            for ( j = 0; j < v30->friendsList.num; ++j )
            {
              list = v30->friendsList.list;
              list[j].first = *(_DWORD *)(8 * j);
              list[j].second = *(_DWORD *)(8 * j + 4);
            }
          }
        }
        else
        {
          v30->friendsList.list = 0;
          v30->friendsList.num = 0;
          v30->friendsList.size = 0;
        }
      }
      v34 = v30->friendsList.size;
      if ( v30->friendsList.num == v34 )
      {
        if ( !v30->friendsList.granularity )
          v30->friendsList.granularity = 16;
        v35 = v30->friendsList.granularity + v34 - (v30->friendsList.granularity + v34) % v30->friendsList.granularity;
        if ( v35 > 0 )
        {
          if ( v35 != v30->friendsList.size )
          {
            v6 = v35 < v30->friendsList.num;
            v36 = v30->friendsList.list;
            v30->friendsList.size = v35;
            if ( v6 )
              v30->friendsList.num = v35;
            v30->friendsList.list = (rvPair<int,int> *)Memory::Allocate(8 * v35);
            for ( k = 0; k < v30->friendsList.num; ++k )
            {
              v38 = v30->friendsList.list;
              v38[k].first = v36[k].first;
              v38[k].second = v36[k].second;
            }
            if ( v36 )
              Memory::Free(v36);
          }
        }
        else
        {
          if ( v30->friendsList.list )
            Memory::Free(v30->friendsList.list);
          v30->friendsList.list = 0;
          v30->friendsList.num = 0;
          v30->friendsList.size = 0;
        }
      }
      v39 = v30->friendsList.num;
      v40 = v30->friendsList.list;
      v40[v39].first = index;
      v40[v39].second = -1;
      rvServerScanGUI::FriendUpdate(v30, v30->friendsList.num++);
      v29 = ptra + 1;
    }
  }
  v41 = num;
  if ( num > 0 )
  {
    v42 = 0;
    ia = num;
    do
    {
      if ( rvRandom::flrand(0.0, 10.0) >= 3.0 )
      {
        v43 = &this->activeFriends.list[v42];
        v44 = Sys_NetAdrToString(v43->server);
        rvServerScan::AddFriend(this, v43->guid, v43->name, v43->clan, v44);
      }
      ++v42;
      --ia;
    }
    while ( ia );
    v41 = num;
  }
  networkServer_t::networkServer_t(&fakeServer);
  v89 = 0;
  ib = 0;
  if ( v41 > 0 )
  {
    ptrb = 0;
    do
    {
      fakeServer.challenge = 0;
      memset(fakeServer.nickname, 0, 2048);
      v45 = rvRandom::irand(0, 1);
      v46 = va("%i", v45);
      idDict::Set(&fakeServer.serverInfo, "net_serverDedicated", v46);
      fakeServer.id = ib;
      fakeServer.OSMask = 0;
      fakeServer.performanceFiltered = rvRandom::irand(0, 1) != 0;
      v47 = rvRandom::irand(0, 1000);
      challenge = this->challenge;
      fakeServer.ping = v47;
      fakeServer.challenge = challenge;
      fakeServer.clients = 0;
      v49 = 0;
      if ( rvRandom::irand(1, 16) > 0 )
      {
        v50 = fakeServer.nickname[0];
        do
        {
          v51 = va("Player %d", v49);
          strncpy(v50, v51, 0x20u);
          v52 = va("Player %d", v49);
          strncpy(v50, v52, 0x20u);
          fakeServer.pings[v49] = rvRandom::irand(0, 300);
          fakeServer.rate[v49] = rvRandom::irand(0, 1000);
          ++fakeServer.clients;
          ++v49;
          v50 += 32;
        }
        while ( v49 < rvRandom::irand(1, 16) );
      }
      v53 = rvRandom::irand(1, 20);
      v54 = va("%i", v53);
      idDict::Set(&fakeServer.serverInfo, "si_timeLimit", v54);
      v55 = rvRandom::irand(1, 20);
      v56 = va("%i", v55);
      idDict::Set(&fakeServer.serverInfo, "si_fragLimit", v56);
      v57 = rvRandom::irand(1, 20);
      v58 = va("%i", v57);
      idDict::Set(&fakeServer.serverInfo, "si_captureLimit", v58);
      v59 = rvRandom::irand(0, 1);
      v60 = va("%i", v59 != 0);
      idDict::Set(&fakeServer.serverInfo, "si_autobalance", v60);
      v61 = rvRandom::irand(0, 1);
      v62 = va("%i", v61 != 0);
      idDict::Set(&fakeServer.serverInfo, "si_pure", v62);
      v63 = rvRandom::irand(0, 1);
      v64 = va("%i", v63 != 0);
      idDict::Set(&fakeServer.serverInfo, "si_spectators", v64);
      v65 = rvRandom::irand(0, 1);
      v66 = va("%i", v65 != 0);
      idDict::Set(&fakeServer.serverInfo, "sv_punkbuster", v66);
      v67 = rvRandom::irand(0, 1);
      v68 = va("%i", v67 != 0);
      idDict::Set(&fakeServer.serverInfo, "si_usepass", v68);
      v69 = ib;
      v70 = va("Quake 4 Server %d", ib);
      idDict::Set(&fakeServer.serverInfo, "si_name", v70);
      switch ( rvRandom::irand(1, 5) )
      {
        case 1:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "DM");
          goto LABEL_74;
        case 2:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "Team DM");
          goto LABEL_74;
        case 3:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "Tourney");
LABEL_74:
          v78 = rvRandom::irand(1, 9);
          v71 = va("mp/q4dm%d", v78);
          goto LABEL_78;
        case 4:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "CTF");
          goto LABEL_77;
        case 5:
          idDict::Set(&fakeServer.serverInfo, "si_gametype", "Arena CTF");
LABEL_77:
          v79 = rvRandom::irand(1, 5);
          v71 = va("mp/q4ctf%d", v79);
LABEL_78:
          idDict::Set(&fakeServer.serverInfo, "si_map", v71);
          break;
        default:
          break;
      }
      clients = rvRandom::irand(2, 16);
      if ( clients < fakeServer.clients )
        clients = fakeServer.clients;
      v73 = va("%i", clients);
      idDict::Set(&fakeServer.serverInfo, "si_maxPlayers", v73);
      v74 = (netadr_t *)&ptrb[(unsigned int)this->activeFriends.list + 140];
      fakeServer.adr.type = v74->type;
      *(_DWORD *)fakeServer.adr.ip = *(_DWORD *)v74->ip;
      *(_DWORD *)&fakeServer.adr.port = *(_DWORD *)&v74->port;
      rvServerScan::AddActiveServer(this, &fakeServer);
      ++ib;
      ptrb += 156;
    }
    while ( v69 + 1 < num );
  }
  v89 = -1;
  networkServer_t::~networkServer_t(&fakeServer);
}

// FUNC: public: void __thiscall rvServerScanGUI::Sort(enum sortColumn_t)
void __thiscall rvServerScanGUI::Sort(rvServerScanGUI *this, sortColumn_t sortColumn)
{
  int v3; // eax
  sortInfo_t **currentSort; // ecx
  sortInfo_t *v5; // ebx
  sortInfo_t *v6; // ebp
  sortInfo_t **v7; // eax
  int v8; // ecx
  sortInfo_t **v9; // edi
  rvMultifieldSort<int> *p_multifieldSort; // esi
  int v11; // ecx
  int granularity; // eax
  int *v13; // edi
  int v14; // eax
  int *v15; // ecx
  int v16; // ecx
  int v17; // ecx
  sortInfo_t **v18; // eax
  sortInfo_t **v19; // eax
  int v20; // edx
  bool v21; // cc
  int j; // eax
  int num; // ebp
  int size; // eax
  int v25; // ecx
  int (__cdecl **list)(const int *, const int *); // edi
  int k; // eax
  const char *v28; // eax
  const char *v29; // eax
  const char *v30; // edi
  int v31; // ebp
  char v32; // cl
  int m; // eax
  char *v34; // edx
  int v35; // edi
  int v36; // eax
  char v37; // cl
  char *v38; // edx
  rvServerScanGUI *v39; // ebx
  int v40; // edi
  int v41; // esi
  int v42; // eax
  idUserInterface_vtbl *v43; // esi
  int v44; // eax
  int i; // [esp+10h] [ebp-34h]
  int (__cdecl *fn)(const int *, const int *); // [esp+14h] [ebp-30h]
  idStr sortDesc; // [esp+18h] [ebp-2Ch] BYREF
  int v49; // [esp+40h] [ebp-4h]
  sortInfo_t **sortColumna; // [esp+48h] [ebp+4h]

  if ( (unsigned int)sortColumn > SC_MAP )
  {
    this->currentSort[0] = 0;
    this->currentSort[1] = 0;
    this->currentSort[2] = 0;
    this->currentSort[3] = 0;
    this->currentSort[4] = 0;
    this->currentSort[5] = 0;
    this->currentSort[6] = 0;
    this->currentSort[7] = 0;
    this->currentSort[8] = 0;
    v43 = this->scanGUI->__vftable;
    v44 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_107292",
            -1);
    v43->SetStateString(this->scanGUI, "sortNotice", (const char *)v44);
    this->scanGUI->StateChanged(this->scanGUI, com_frameTime, 0);
  }
  else
  {
    v3 = 0;
    currentSort = this->currentSort;
    while ( !*currentSort || (*currentSort)->column != sortColumn )
    {
      ++v3;
      ++currentSort;
      if ( v3 >= 9 )
        goto LABEL_8;
    }
    v5 = this->currentSort[v3];
    if ( !v5 )
    {
LABEL_8:
      v6 = &rvServerScanGUI::sorts[rvServerScanGUI::sortSelectionOrder[sortColumn][0]];
      v7 = &this->currentSort[8];
      v8 = 8;
      do
      {
        *v7 = *(v7 - 1);
        --v7;
        --v8;
      }
      while ( v8 );
      goto LABEL_10;
    }
    v13 = rvServerScanGUI::sortSelectionOrder[sortColumn];
    v14 = 0;
    v15 = v13;
    while ( v5 != &rvServerScanGUI::sorts[*v15] )
    {
      ++v14;
      ++v15;
      if ( v14 >= 5 )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "rvServerScanGUI::Sort() - Can't find place in selection order for column '%d', defaulting to first sort\n",
          sortColumn);
        v6 = &rvServerScanGUI::sorts[*v13];
        goto LABEL_26;
      }
    }
    v16 = dword_102F5A84[4 * sortColumn + sortColumn + v14];
    if ( v16 == -1 || v14 == 4 )
      v16 = *v13;
    v6 = &rvServerScanGUI::sorts[v16];
LABEL_26:
    v17 = 0;
    v18 = this->currentSort;
    while ( !*v18 || v5->column != (*v18)->column )
    {
      ++v17;
      ++v18;
      if ( v17 >= 9 )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "rvServerScanGUI::Sort() - Can't find existing sort in current sort list\n");
        goto LABEL_10;
      }
    }
    if ( v17 > 0 )
    {
      v19 = &this->currentSort[v17];
      v20 = v17;
      do
      {
        *v19 = *(v19 - 1);
        --v19;
        --v20;
      }
      while ( v20 );
    }
LABEL_10:
    v9 = this->currentSort;
    p_multifieldSort = &this->multifieldSort;
    this->currentSort[0] = v6;
    if ( this->multifieldSort.sortingFields.list )
      Memory::Free(this->multifieldSort.sortingFields.list);
    this->multifieldSort.sortingFields.list = 0;
    p_multifieldSort->sortingFields.num = 0;
    this->multifieldSort.sortingFields.size = 0;
    sortDesc.len = 0;
    sortDesc.alloced = 20;
    sortDesc.data = sortDesc.baseBuffer;
    sortDesc.baseBuffer[0] = 0;
    v11 = 0;
    v49 = 0;
    i = 0;
    sortColumna = this->currentSort;
    do
    {
      if ( v11 >= 3 )
        break;
      if ( *v9 )
      {
        fn = (*v9)->fn;
        if ( !this->multifieldSort.sortingFields.list )
        {
          granularity = this->multifieldSort.sortingFields.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->multifieldSort.sortingFields.size )
            {
              v21 = granularity < p_multifieldSort->sortingFields.num;
              this->multifieldSort.sortingFields.size = granularity;
              if ( v21 )
                p_multifieldSort->sortingFields.num = granularity;
              this->multifieldSort.sortingFields.list = (int (__cdecl **)(const int *, const int *))Memory::Allocate(4 * granularity);
              for ( j = 0; j < p_multifieldSort->sortingFields.num; ++j )
                this->multifieldSort.sortingFields.list[j] = *(int (__cdecl **)(const int *, const int *))(4 * j);
            }
          }
          else
          {
            this->multifieldSort.sortingFields.list = 0;
            p_multifieldSort->sortingFields.num = 0;
            this->multifieldSort.sortingFields.size = 0;
          }
        }
        num = p_multifieldSort->sortingFields.num;
        size = this->multifieldSort.sortingFields.size;
        if ( p_multifieldSort->sortingFields.num == size )
        {
          if ( !this->multifieldSort.sortingFields.granularity )
            this->multifieldSort.sortingFields.granularity = 16;
          v25 = size
              + this->multifieldSort.sortingFields.granularity
              - (size + this->multifieldSort.sortingFields.granularity) % this->multifieldSort.sortingFields.granularity;
          if ( v25 > 0 )
          {
            if ( v25 != this->multifieldSort.sortingFields.size )
            {
              list = this->multifieldSort.sortingFields.list;
              this->multifieldSort.sortingFields.size = v25;
              if ( v25 < num )
                p_multifieldSort->sortingFields.num = v25;
              this->multifieldSort.sortingFields.list = (int (__cdecl **)(const int *, const int *))Memory::Allocate(4 * v25);
              for ( k = 0; k < p_multifieldSort->sortingFields.num; ++k )
                this->multifieldSort.sortingFields.list[k] = list[k];
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( this->multifieldSort.sortingFields.list )
              Memory::Free(this->multifieldSort.sortingFields.list);
            this->multifieldSort.sortingFields.list = 0;
            p_multifieldSort->sortingFields.num = 0;
            this->multifieldSort.sortingFields.size = 0;
          }
        }
        this->multifieldSort.sortingFields.list[this->multifieldSort.sortingFields.num] = fn;
        ++p_multifieldSort->sortingFields.num;
        v28 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                              common.type,
                              (*sortColumna)->description,
                              -1);
        v29 = va(v28, "^iarr");
        v30 = v29;
        if ( v29 )
        {
          v31 = strlen(v29) + sortDesc.len;
          if ( v31 + 1 > sortDesc.alloced )
            idStr::ReAllocate(&sortDesc, v31 + 1, 1);
          v32 = *v30;
          for ( m = 0; v32; v32 = v30[m] )
          {
            v34 = &sortDesc.data[m++];
            v34[sortDesc.len] = v32;
          }
          sortDesc.len = v31;
          sortDesc.data[v31] = 0;
        }
        v35 = sortDesc.len + 1;
        if ( sortDesc.len + 2 > sortDesc.alloced )
          idStr::ReAllocate(&sortDesc, sortDesc.len + 2, 1);
        v36 = 0;
        v37 = 59;
        do
        {
          v38 = &sortDesc.data[v36++];
          v38[sortDesc.len] = v37;
          v37 = asc_102A5CB4[v36];
        }
        while ( v37 );
        sortDesc.len = v35;
        sortDesc.data[v35] = 0;
        v11 = i;
      }
      ++v11;
      v9 = sortColumna + 1;
      i = v11;
      ++sortColumna;
    }
    while ( v11 < 9 );
    v39 = this;
    v40 = Sys_Milliseconds();
    rvMultifieldSort<int>::QSort_Iterative(p_multifieldSort, &this->serverList, 0, this->serverList.num);
    v41 = *(_DWORD *)common.type;
    v42 = Sys_Milliseconds();
    (*(void (**)(netadrtype_t, const char *, ...))(v41 + 124))(common.type, "Sort took %d ms\n", v42 - v40);
    rvServerScanGUI::Populate(this);
    v39->scanGUI->SetStateString(v39->scanGUI, "sortNotice", sortDesc.data);
    v39->scanGUI->StateChanged(v39->scanGUI, com_frameTime, 0);
    v49 = -1;
    idStr::FreeData(&sortDesc);
  }
}
