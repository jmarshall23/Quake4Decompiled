
// FUNC: public: bool __thiscall idAsyncServer::InitPort(void)
char __thiscall idAsyncServer::InitPort(idAsyncServer *this)
{
  int v2; // eax
  int v3; // esi
  int v4; // eax
  int v6; // esi
  idPort *p_serverPort; // edi

  if ( !this->serverPort.port )
  {
    if ( cvarSystem->GetCVarInteger(cvarSystem, "net_port") )
    {
      v2 = cvarSystem->GetCVarInteger(cvarSystem, "net_port");
      if ( !idPort::InitForPort(&this->serverPort, v2) )
      {
        v3 = *(_DWORD *)common.type;
        v4 = cvarSystem->GetCVarInteger(cvarSystem, "net_port");
        (*(void (**)(netadrtype_t, const char *, ...))(v3 + 124))(
          common.type,
          "Unable to open server on port %d (net_port)\n",
          v4);
        return 0;
      }
    }
    else
    {
      v6 = 0;
      p_serverPort = &this->serverPort;
      while ( !idPort::InitForPort(p_serverPort, v6 + 28004) )
      {
        if ( ++v6 >= 4 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "Unable to open server network port.\n");
          return 0;
        }
      }
    }
  }
  return 1;
}

// FUNC: public: virtual int const __thiscall idDeclPDA::GetNumEmails(void)const
int __thiscall idDeclPDA::GetNumEmails(idDeclPDA *this)
{
  return this->emails.num;
}

// FUNC: public: bool __thiscall idAsyncServer::IsClientInGame(int)const
BOOL __thiscall idAsyncServer::IsClientInGame(idAsyncServer *this, int clientNum)
{
  return this->clients[clientNum].clientState >= SCS_INGAME;
}

// FUNC: public: int __thiscall idAsyncServer::GetClientPing(int)const
int __thiscall idAsyncServer::GetClientPing(idAsyncServer *this, int clientNum)
{
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
    return this->clients[clientNum].clientPing;
  else
    return 99999;
}

// FUNC: public: int __thiscall idAsyncServer::GetClientPrediction(int)const
int __thiscall idAsyncServer::GetClientPrediction(idAsyncServer *this, int clientNum)
{
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
    return this->clients[clientNum].clientPrediction;
  else
    return 99999;
}

// FUNC: public: int __thiscall idAsyncServer::GetClientTimeSinceLastPacket(int)const
int __thiscall idAsyncServer::GetClientTimeSinceLastPacket(idAsyncServer *this, int clientNum)
{
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
    return this->serverTime - this->clients[clientNum].lastPacketTime;
  else
    return 99999;
}

// FUNC: public: int __thiscall idAsyncServer::GetClientTimeSinceLastInput(int)const
int __thiscall idAsyncServer::GetClientTimeSinceLastInput(idAsyncServer *this, int clientNum)
{
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
    return this->serverTime - this->clients[clientNum].lastInputTime;
  else
    return 99999;
}

// FUNC: public: float __thiscall idAsyncServer::GetClientIncomingPacketLoss(int)const
double __thiscall idAsyncServer::GetClientIncomingPacketLoss(idAsyncServer *this, int clientNum)
{
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
    return idMsgChannel::GetIncomingPacketLoss(&this->clients[clientNum].channel);
  else
    return 0.0;
}

// FUNC: public: int __thiscall idAsyncServer::GetNumClients(void)const
int __thiscall idAsyncServer::GetNumClients(idAsyncServer *this)
{
  int result; // eax
  int *p_clientState; // ecx
  int v3; // edx

  result = 0;
  p_clientState = (int *)&this->clients[1].clientState;
  v3 = 8;
  do
  {
    if ( *(p_clientState - 16450) >= 3 )
      ++result;
    if ( *p_clientState >= 3 )
      ++result;
    if ( p_clientState[16450] >= 3 )
      ++result;
    if ( p_clientState[32900] >= 3 )
      ++result;
    p_clientState += 65800;
    --v3;
  }
  while ( v3 );
  return result;
}

// FUNC: public: int __thiscall idAsyncServer::GetNumIdleClients(void)const
int __thiscall idAsyncServer::GetNumIdleClients(idAsyncServer *this)
{
  int result; // eax
  int *p_lastInputTime; // edx
  int v3; // edi

  result = 0;
  p_lastInputTime = &this->clients[0].lastInputTime;
  v3 = 8;
  do
  {
    if ( *(p_lastInputTime - 16440) >= 3 && this->serverTime - *p_lastInputTime > 30000 )
      ++result;
    if ( p_lastInputTime[10] >= 3 && this->serverTime - p_lastInputTime[16450] > 30000 )
      ++result;
    if ( p_lastInputTime[16460] >= 3 && this->serverTime - p_lastInputTime[32900] > 30000 )
      ++result;
    if ( p_lastInputTime[32910] >= 3 && this->serverTime - p_lastInputTime[49350] > 30000 )
      ++result;
    p_lastInputTime += 65800;
    --v3;
  }
  while ( v3 );
  return result;
}

// FUNC: public: struct serverClient_s * __thiscall idAsyncServer::GetClientInfo(int)
serverClient_s *__thiscall idAsyncServer::GetClientInfo(idAsyncServer *this, unsigned int clientNum)
{
  if ( clientNum > 0x20 )
    return 0;
  else
    return &this->clients[clientNum];
}

// FUNC: private: void __thiscall idAsyncServer::DuplicateUsercmds(int,int)
void __thiscall idAsyncServer::DuplicateUsercmds(idAsyncServer *this, int frame, int time)
{
  int v3; // eax
  int v5; // esi
  int *p_numDuplicatedUsercmds; // [esp+10h] [ebp-4h]

  v3 = frame;
  v5 = 0;
  p_numDuplicatedUsercmds = &this->clients[0].numDuplicatedUsercmds;
  while ( 1 )
  {
    if ( *(p_numDuplicatedUsercmds - 16443) )
    {
      if ( idAsyncNetwork::DuplicateUsercmd(
             &this->userCmds[(unsigned __int8)(frame - 1)][v5],
             &this->userCmds[(unsigned __int8)frame][v5],
             v3,
             time) )
      {
        ++*p_numDuplicatedUsercmds;
      }
    }
    p_numDuplicatedUsercmds += 16450;
    if ( ++v5 >= 32 )
      break;
    v3 = frame;
  }
}

// FUNC: private: void __thiscall idAsyncServer::ClearClient(int)
void __thiscall idAsyncServer::ClearClient(idAsyncServer *this, int clientNum)
{
  serverClient_s *v2; // esi

  v2 = &this->clients[clientNum];
  v2->clientId = 0;
  v2->clientState = SCS_FREE;
  v2->clientPrediction = 0;
  v2->clientAheadTime = 0;
  v2->clientRate = 0;
  v2->clientPing = 0;
  v2->gameInitSequence = 0;
  v2->gameFrame = 0;
  v2->gameTime = 0;
  idMsgChannel::Shutdown(&this->clients[clientNum].channel);
  v2->lastConnectTime = 0;
  v2->lastEmptyTime = 0;
  v2->lastPingTime = 0;
  v2->lastSnapshotTime = 0;
  v2->lastPacketTime = 0;
  v2->lastInputTime = 0;
  v2->snapshotSequence = 0;
  v2->acknowledgeSnapshotSequence = 0;
  v2->numDuplicatedUsercmds = 0;
  v2->guid[0] = 0;
}

// FUNC: private: void __thiscall idAsyncServer::LocalClientInput(void)
void __thiscall idAsyncServer::LocalClientInput(idAsyncServer *this)
{
  int gameFrame; // ebp
  int v3; // esi
  char v4[40]; // [esp+4h] [ebp-28h] BYREF

  if ( this->localClientNum >= 0 )
  {
    gameFrame = (unsigned __int8)this->gameFrame;
    qmemcpy(
      &this->userCmds[gameFrame][this->localClientNum],
      (const void *)((int (__stdcall *)(char *))usercmdGen->GetDirectUsercmd)(v4),
      sizeof(this->userCmds[gameFrame][this->localClientNum]));
    this->userCmds[gameFrame][this->localClientNum].gameFrame = this->gameFrame;
    this->userCmds[gameFrame][this->localClientNum].gameTime = this->gameTime;
    v3 = this->gameTimeResidual
       - this->realTime
       - (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
    this->userCmds[0][this->localClientNum + gameFrame * 32].realTime = this->gameTime + Sys_Milliseconds() + v3;
    if ( idAsyncNetwork::UsercmdInputChanged(
           &this->userCmds[(unsigned __int8)(this->gameFrame - 1)][this->localClientNum],
           &this->userCmds[0][this->localClientNum + gameFrame * 32]) )
    {
      this->clients[this->localClientNum].lastInputTime = this->serverTime;
    }
    this->clients[this->localClientNum].gameFrame = this->gameFrame;
    this->clients[this->localClientNum].gameTime = this->gameTime;
    this->clients[this->localClientNum].lastPacketTime = this->serverTime;
  }
}

// FUNC: public: void __thiscall idAsyncServer::LocalClientSendReliableMessage(class idBitMsg const &)
void __thiscall idAsyncServer::LocalClientSendReliableMessage(idAsyncServer *this, const idBitMsg *msg)
{
  int localClientNum; // eax

  localClientNum = this->localClientNum;
  if ( localClientNum >= 0 )
    game->ServerProcessReliableMessage(game, localClientNum, msg);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "LocalClientSendReliableMessage: no local client\n");
}

// FUNC: public: struct netadr_t __thiscall idAsyncServer::GetClientAddress(int)
netadr_t *__thiscall idAsyncServer::GetClientAddress(idAsyncServer *this, netadr_t *result, unsigned int clientNum)
{
  bool *v3; // eax
  char *v4; // ecx
  netadrtype_t v5; // esi
  netadr_t *v6; // eax

  if ( clientNum <= 0x1F && (v3 = &this->active + 65800 * clientNum, *((_DWORD *)v3 + 23570) == 4) )
  {
    v4 = (char *)(v3 + 94300);
    v5 = *((_DWORD *)v3 + 23575);
    v6 = result;
    result->type = v5;
    *(_DWORD *)result->ip = *((_DWORD *)v4 + 1);
    *(_DWORD *)&result->port = *((_DWORD *)v4 + 2);
  }
  else
  {
    v6 = result;
    result->type = NA_BAD;
    *(_DWORD *)result->ip = 0;
    *(_DWORD *)&result->port = 0;
  }
  return v6;
}

// FUNC: public: void __thiscall idAsyncServer::SetClientGUID(int,char const *)
void __thiscall idAsyncServer::SetClientGUID(idAsyncServer *this, unsigned int clientNum, const char *guid)
{
  bool *v3; // esi

  if ( clientNum <= 0x1F && (v3 = &this->active + 65800 * clientNum, *((_DWORD *)v3 + 23570) == 4) )
  {
    strncpy((char *)v3 + 160056, guid, 0xCu);
    v3[160067] = 0;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idAsyncServer::SetClientGUID() - Invalid client num '%d' specified",
      clientNum);
  }
}

// FUNC: public: void __thiscall idAsyncServer::ClosePort(void)
void __thiscall idAsyncServer::ClosePort(idAsyncServer *this)
{
  char *baseBuffer; // esi
  int v3; // ebx

  idPort::Close(&this->serverPort);
  baseBuffer = this->challenges[0].authReplyPrint.baseBuffer;
  v3 = 1024;
  do
  {
    idStr::FreeData((idStr *)(baseBuffer - 12));
    *((_DWORD *)baseBuffer - 1) = 20;
    *((_DWORD *)baseBuffer - 2) = baseBuffer;
    *((_DWORD *)baseBuffer - 3) = 0;
    *baseBuffer = 0;
    baseBuffer += 92;
    --v3;
  }
  while ( v3 );
}

// FUNC: public: int __thiscall idAsyncServer::GetOutgoingRate(void)const
int __thiscall idAsyncServer::GetOutgoingRate(idAsyncServer *this)
{
  int result; // eax
  int *p_outgoingRateBytes; // ecx
  int v3; // esi

  result = 0;
  p_outgoingRateBytes = &this->clients[0].channel.outgoingRateBytes;
  v3 = 8;
  do
  {
    if ( *(p_outgoingRateBytes - 20) >= 3 )
      result += *p_outgoingRateBytes;
    if ( p_outgoingRateBytes[16430] >= 3 )
      result += p_outgoingRateBytes[16450];
    if ( p_outgoingRateBytes[32880] >= 3 )
      result += p_outgoingRateBytes[32900];
    if ( p_outgoingRateBytes[49330] >= 3 )
      result += p_outgoingRateBytes[49350];
    p_outgoingRateBytes += 65800;
    --v3;
  }
  while ( v3 );
  return result;
}

// FUNC: public: int __thiscall idAsyncServer::GetIncomingRate(void)const
int __thiscall idAsyncServer::GetIncomingRate(idAsyncServer *this)
{
  int result; // eax
  int *p_incomingRateBytes; // ecx
  int v3; // esi

  result = 0;
  p_incomingRateBytes = &this->clients[0].channel.incomingRateBytes;
  v3 = 8;
  do
  {
    if ( *(p_incomingRateBytes - 22) >= 3 )
      result += *p_incomingRateBytes;
    if ( p_incomingRateBytes[16428] >= 3 )
      result += p_incomingRateBytes[16450];
    if ( p_incomingRateBytes[32878] >= 3 )
      result += p_incomingRateBytes[32900];
    if ( p_incomingRateBytes[49328] >= 3 )
      result += p_incomingRateBytes[49350];
    p_incomingRateBytes += 65800;
    --v3;
  }
  while ( v3 );
  return result;
}

// FUNC: public: int __thiscall idAsyncServer::GetClientOutgoingRate(int)const
int __thiscall idAsyncServer::GetClientOutgoingRate(idAsyncServer *this, int clientNum)
{
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
    return this->clients[clientNum].channel.outgoingRateBytes;
  else
    return -1;
}

// FUNC: public: int __thiscall idAsyncServer::GetClientIncomingRate(int)const
int __thiscall idAsyncServer::GetClientIncomingRate(idAsyncServer *this, int clientNum)
{
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
    return this->clients[clientNum].channel.incomingRateBytes;
  else
    return -1;
}

// FUNC: public: float __thiscall idAsyncServer::GetClientOutgoingCompression(int)const
double __thiscall idAsyncServer::GetClientOutgoingCompression(idAsyncServer *this, int clientNum)
{
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
    return this->clients[clientNum].channel.outgoingCompression;
  else
    return 0.0;
}

// FUNC: public: float __thiscall idAsyncServer::GetClientIncomingCompression(int)const
double __thiscall idAsyncServer::GetClientIncomingCompression(idAsyncServer *this, int clientNum)
{
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
    return this->clients[clientNum].channel.incomingCompression;
  else
    return 0.0;
}

// FUNC: private: void __thiscall idAsyncServer::InitClient(int,int,int)
void __thiscall idAsyncServer::InitClient(idAsyncServer *this, int clientNum, int clientId, int clientRate)
{
  serverClient_s *v5; // esi
  int integerValue; // eax
  usercmd_t *v7; // eax
  int v8; // ecx
  usercmd_t *v9; // esi

  idDict::Clear(&sessLocal.mapSpawnData.userInfo[clientNum]);
  v5 = &this->clients[clientNum];
  v5->clientId = clientId;
  v5->clientState = SCS_CONNECTED;
  v5->clientPrediction = 0;
  v5->clientAheadTime = 0;
  v5->gameInitSequence = -1;
  v5->gameFrame = 0;
  v5->gameTime = 0;
  idMsgChannel::ResetRate(&this->clients[clientNum].channel);
  integerValue = clientRate;
  if ( !clientRate )
    integerValue = idAsyncNetwork::serverMaxClientRate.internalVar->integerValue;
  this->clients[clientNum].clientRate = integerValue;
  if ( idAsyncNetwork::serverMaxClientRate.internalVar->integerValue < integerValue )
    integerValue = idAsyncNetwork::serverMaxClientRate.internalVar->integerValue;
  this->clients[clientNum].channel.maxRate = integerValue;
  this->clients[clientNum].clientPing = 0;
  this->clients[clientNum].lastConnectTime = this->serverTime;
  this->clients[clientNum].lastEmptyTime = this->serverTime;
  this->clients[clientNum].lastPingTime = this->serverTime;
  this->clients[clientNum].lastSnapshotTime = this->serverTime;
  this->clients[clientNum].lastPacketTime = this->serverTime;
  this->clients[clientNum].lastInputTime = this->serverTime;
  this->clients[clientNum].acknowledgeSnapshotSequence = 0;
  this->clients[clientNum].numDuplicatedUsercmds = 0;
  this->clients[clientNum].clientUserDictSequence = 0;
  v7 = &this->userCmds[0][clientNum];
  v8 = 256;
  do
  {
    v9 = v7;
    v7->gameFrame = 0;
    v7->gameTime = 0;
    v7->realTime = 0;
    v7->duplicateCount = 0;
    *(_DWORD *)&v7->buttons = 0;
    *(_DWORD *)&v7->upmove = 0;
    *(_DWORD *)&v7->angles[1] = 0;
    *(_DWORD *)&v7->mx = 0;
    *(_DWORD *)&v7->impulse = 0;
    v7 += 32;
    --v8;
    v9->sequence = 0;
  }
  while ( v8 );
  game->ServerClientConnect(game, clientNum);
}

// FUNC: private: void __thiscall idAsyncServer::InitLocalClient(int)
void __thiscall idAsyncServer::InitLocalClient(idAsyncServer *this, int clientNum)
{
  bool *v3; // ebx
  idDict *v4; // eax
  netadr_t v5[2]; // [esp-10h] [ebp-28h] BYREF

  this->localClientNum = clientNum;
  idAsyncServer::InitClient(this, clientNum, 0, 0);
  v3 = &this->active + 65800 * clientNum;
  memset(v5, 0, 12);
  idMsgChannel::Init((idMsgChannel *)(v3 + 94324), v5[0], this->serverId);
  *((_DWORD *)v3 + 23570) = 4;
  v4 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 512);
  idDict::operator=(&sessLocal.mapSpawnData.userInfo[clientNum], v4);
}

// FUNC: private: void __thiscall idAsyncServer::FakeClientInput(void)
void __thiscall idAsyncServer::FakeClientInput(idAsyncServer *this)
{
  int gameFrame; // ebp
  int v3; // edx
  int *p_turnTime; // esi
  int v5; // eax
  int v6; // ecx
  int v7; // ebp
  bool *v8; // ebx
  double v9; // st6
  double v10; // st5
  double v11; // st3
  double v12; // st7
  float y; // eax
  float z; // ecx
  int v15; // eax
  double v16; // st7
  int v17; // eax
  int i; // [esp+3Ch] [ebp-68h]
  int *p_lastInputTime; // [esp+40h] [ebp-64h]
  int tempClient; // [esp+44h] [ebp-60h]
  float tempClienta; // [esp+44h] [ebp-60h]
  int index; // [esp+4Ch] [ebp-58h]
  idVec3 origin; // [esp+50h] [ebp-54h] BYREF
  idVec3 followOrigin; // [esp+5Ch] [ebp-48h] BYREF
  idAngles delta; // [esp+68h] [ebp-3Ch] BYREF
  int v27; // [esp+78h] [ebp-2Ch]
  int v28; // [esp+7Ch] [ebp-28h]
  idMat3 axis; // [esp+80h] [ebp-24h] BYREF

  gameFrame = (unsigned __int8)this->gameFrame;
  v3 = 0;
  index = gameFrame;
  i = 0;
  p_lastInputTime = &this->clients[0].lastInputTime;
  p_turnTime = &this->fakeInfo[0].turnTime;
  do
  {
    v5 = *(p_lastInputTime - 16429);
    v6 = *(p_lastInputTime - 16427);
    v27 = *(p_lastInputTime - 16428);
    v28 = v6;
    if ( v5 != 4 )
      goto LABEL_28;
    v7 = 32 * gameFrame;
    v8 = &this->active + 40 * v3 + 40 * v7;
    *((_DWORD *)v8 + 549968) = 0;
    *((_DWORD *)v8 + 549969) = 0;
    *((_DWORD *)v8 + 549970) = 0;
    *((_DWORD *)v8 + 549971) = 0;
    *((_DWORD *)v8 + 549972) = 0;
    *((_DWORD *)v8 + 549973) = 0;
    *((_DWORD *)v8 + 549974) = 0;
    *((_DWORD *)v8 + 549975) = 0;
    *((_DWORD *)v8 + 549976) = 0;
    *((_DWORD *)v8 + 549977) = 0;
    v8[2199890] = 127;
    --*p_turnTime;
    game->GetPlayerInfo(game, &origin, &axis, v3, &delta, -1);
    if ( *p_turnTime == -20 )
    {
      v9 = origin.y - *((float *)p_turnTime + 6);
      v10 = origin.z - *((float *)p_turnTime + 7);
      v11 = origin.x - *((float *)p_turnTime + 5);
      if ( sqrt(v10 * v10 + v9 * v9 + v11 * v11) < 50.0 )
      {
        *p_turnTime = 0;
LABEL_8:
        if ( rvRandom::irand(0, 1) )
          v12 = rvRandom::flrand(45.0, 180.0) + *((float *)p_turnTime + 4);
        else
          v12 = *((float *)p_turnTime + 4) - rvRandom::flrand(45.0, 180.0);
        *((float *)p_turnTime + 4) = v12;
        *((float *)p_turnTime + 3) = rvRandom::flrand(-2.0, 2.0);
        y = origin.y;
        z = origin.z;
        p_turnTime[5] = LODWORD(origin.x);
        *((float *)p_turnTime + 6) = y;
        *((float *)p_turnTime + 7) = z;
        goto LABEL_12;
      }
      *p_turnTime = rvRandom::irand(50, 100);
    }
    if ( !*p_turnTime )
      goto LABEL_8;
LABEL_12:
    v15 = p_turnTime[8];
    *((float *)p_turnTime + 4) = *((float *)p_turnTime + 3) + *((float *)p_turnTime + 4);
    if ( v15 >= 0 )
    {
      game->GetPlayerInfo(game, &followOrigin, &axis, v15, 0, -1);
      followOrigin.x = followOrigin.x - origin.x;
      followOrigin.y = followOrigin.y - origin.y;
      followOrigin.z = followOrigin.z - origin.z;
      v16 = idVec3::ToYaw(&followOrigin);
      *((float *)p_turnTime + 4) = v16 - delta.yaw;
      if ( !rvRandom::irand(0, 20) )
        p_turnTime[8] = -1;
    }
    if ( p_turnTime[8] == -1 )
    {
      v17 = rvRandom::irand(0, 32);
      tempClient = v17;
      if ( i != v17
        && this->clients[v17].clientState >= SCS_PUREWAIT
        && game->GetPlayerInfo(game, &origin, &axis, v17, 0, i) )
      {
        p_turnTime[8] = tempClient;
      }
    }
    tempClienta = *((float *)p_turnTime + 4) * 182.04445;
    *((_WORD *)v8 + 1099948) = (int)tempClienta;
    *((_WORD *)v8 + 1099944) = 0;
    if ( !*((_BYTE *)p_turnTime + 36) && *((_BYTE *)p_turnTime + 8) )
      *((_WORD *)v8 + 1099944) = 1;
    if ( --p_turnTime[1] < 0 )
    {
      *((_BYTE *)p_turnTime + 8) = *((_BYTE *)p_turnTime + 8) == 0;
      p_turnTime[1] = rvRandom::irand(5, 20);
    }
    *((_DWORD *)v8 + 549968) = this->gameFrame;
    *((_DWORD *)v8 + 549969) = this->gameTime;
    this->userCmds[0][i + v7].realTime = this->gameTime;
    if ( idAsyncNetwork::UsercmdInputChanged(
           &this->userCmds[(unsigned __int8)(this->gameFrame - 1)][this->localClientNum],
           (const usercmd_t *)(v8 + 2199872)) )
    {
      *p_lastInputTime = this->serverTime;
    }
    gameFrame = index;
    *(p_lastInputTime - 16431) = this->gameFrame;
    *(p_lastInputTime - 16430) = this->gameTime;
    v3 = i;
    *(p_lastInputTime - 1) = this->serverTime;
LABEL_28:
    p_lastInputTime += 16450;
    ++v3;
    p_turnTime += 11;
    i = v3;
  }
  while ( v3 < 32 );
}

// FUNC: public: void __thiscall idAsyncServer::DropClient(int,char const *)
void __userpurge idAsyncServer::DropClient(idAsyncServer *this@<ecx>, int a2@<edi>, int clientNum, char *reason)
{
  serverClient_s *v5; // ebx
  int v6; // edi
  serverClientState_t *p_clientState; // ebx
  const char *v8; // edi
  const idKeyValue *Key; // eax
  const char *data; // eax
  idCmdSystem_vtbl *v11; // ebp
  idBitMsg msg; // [esp+10h] [ebp-4024h] BYREF
  char v14[16384]; // [esp+34h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  v5 = &this->clients[clientNum];
  if ( this->clients[clientNum].clientState > SCS_ZOMBIE )
  {
    if ( clientNum != this->localClientNum )
    {
      msg.writeData = (unsigned __int8 *)v14;
      v6 = 0;
      msg.readData = (const unsigned __int8 *)v14;
      msg.maxSize = 0x4000;
      msg.numValueOverflows = 0;
      idBitMsg::WriteBits(&msg, 5, 8);
      idBitMsg::WriteBits(&msg, clientNum, 32);
      idBitMsg::WriteString(&msg, reason, -1);
      p_clientState = &this->clients[0].clientState;
      do
      {
        if ( v6 == clientNum || *(int *)p_clientState >= 3 )
          idAsyncServer::SendReliableMessage(this, v6, &msg);
        ++v6;
        p_clientState += 16450;
      }
      while ( v6 < 32 );
      v5 = &this->clients[clientNum];
    }
    v8 = (const char *)(*(int (__thiscall **)(netadrtype_t, char *, int, int))(*(_DWORD *)common.type + 168))(
                         common.type,
                         reason,
                         -1,
                         a2);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "client %d %s\n",
      clientNum,
      v8);
    Key = idDict::FindKey(&sessLocal.mapSpawnData.userInfo[clientNum], "ui_name");
    if ( Key )
      data = Key->value->data;
    else
      data = &entityFilter;
    v11 = cmdSystem->__vftable;
    va("addChatLine \"%s^0 %s\"", data, v8);
    ((void (__thiscall *)(idCmdSystem *, _DWORD))v11->BufferCommandText)(cmdSystem, 0);
    v5->clientState = SCS_ZOMBIE;
    game->ServerClientDisconnect(game, clientNum);
  }
}

// FUNC: private: void __thiscall idAsyncServer::SendReliableMessage(int,class idBitMsg const &)
void __thiscall idAsyncServer::SendReliableMessage(idAsyncServer *this, int clientNum, const idBitMsg *msg)
{
  if ( clientNum != this->localClientNum && !idMsgChannel::SendReliableMessage(&this->clients[clientNum].channel, msg) )
  {
    idMsgChannel::ClearReliableMessages(&this->clients[clientNum].channel);
    idAsyncServer::DropClient(this, (int)this, clientNum, "#str_107136");
  }
}

// FUNC: private: void __thiscall idAsyncServer::CheckClientTimeouts(void)
void __thiscall idAsyncServer::CheckClientTimeouts(idAsyncServer *this)
{
  int v2; // ebx
  serverClientState_t *p_clientState; // esi
  int v4; // edx
  int serverTime; // eax
  int zombieTimeout; // [esp+10h] [ebp-14h]
  int clientTimeout; // [esp+14h] [ebp-10h]

  zombieTimeout = this->serverTime - 1000 * idAsyncNetwork::serverZombieTimeout.internalVar->integerValue;
  clientTimeout = this->serverTime - 1000 * idAsyncNetwork::serverClientTimeout.internalVar->integerValue;
  v2 = 0;
  p_clientState = &this->clients[0].clientState;
  do
  {
    if ( v2 != this->localClientNum && *((_DWORD *)p_clientState + 11) != 4 )
    {
      v4 = *((_DWORD *)p_clientState + 16439);
      serverTime = this->serverTime;
      if ( v4 <= serverTime )
      {
        if ( *p_clientState == SCS_ZOMBIE && v4 < zombieTimeout )
        {
          idMsgChannel::Shutdown((idMsgChannel *)(p_clientState + 11));
          *p_clientState = SCS_FREE;
        }
        else if ( *(int *)p_clientState >= 2 && v4 < clientTimeout )
        {
          idAsyncServer::DropClient(this, (int)this, v2, "#str_107137");
        }
      }
      else
      {
        *((_DWORD *)p_clientState + 16439) = serverTime;
      }
    }
    ++v2;
    p_clientState += 16450;
  }
  while ( v2 < 32 );
}

// FUNC: private: void __thiscall idAsyncServer::SendUserInfoBroadcast(int,class idDict const &,bool)
void __thiscall idAsyncServer::SendUserInfoBroadcast(
        idAsyncServer *this,
        int userInfoNum,
        idDict *info,
        bool sendToAll)
{
  idDict *v5; // ebp
  int v6; // eax
  int v7; // esi
  idMsgChannel *p_channel; // edi
  char v9; // [esp+15h] [ebp-4029h]
  idBitMsg msg; // [esp+1Ah] [ebp-4024h] BYREF
  char v12[16384]; // [esp+3Eh] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  v5 = (idDict *)game->SetUserInfo(game, userInfoNum, info, 0);
  if ( v5 )
  {
    v9 = 1;
  }
  else
  {
    v9 = 0;
    v5 = info;
  }
  if ( userInfoNum == this->localClientNum )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "local user info modified by server\n");
    cvarSystem->SetCVarsFromDict(cvarSystem, v5);
    cvarSystem->ClearModifiedFlags(cvarSystem, 512);
  }
  msg.writeData = (unsigned __int8 *)v12;
  msg.readData = (const unsigned __int8 *)v12;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, 2, 8);
  idBitMsg::WriteBits(&msg, userInfoNum, 8);
  if ( v9 || sendToAll )
    idBitMsg::WriteBits(&msg, 0, 1);
  else
    idBitMsg::WriteBits(&msg, 1, 1);
  v6 = idDict::Checksum(v5);
  idBitMsg::WriteBits(&msg, v6, 32);
  if ( v9 || sendToAll )
    idBitMsg::WriteDeltaDict(&msg, v5, 0);
  else
    idBitMsg::WriteDeltaDict(&msg, v5, &sessLocal.mapSpawnData.userInfo[userInfoNum]);
  v7 = 0;
  p_channel = &this->clients[0].channel;
  do
  {
    if ( *(int *)&p_channel[-1].reliableReceive.buffer[16356] >= 3
      && (sendToAll || v7 != userInfoNum || v9)
      && v7 != this->localClientNum
      && !idMsgChannel::SendReliableMessage(p_channel, &msg) )
    {
      idMsgChannel::ClearReliableMessages(p_channel);
      idAsyncServer::DropClient(this, (int)p_channel, v7, "#str_107136");
    }
    ++v7;
    p_channel = (idMsgChannel *)((char *)p_channel + 65800);
  }
  while ( v7 < 32 );
  idDict::operator=(&sessLocal.mapSpawnData.userInfo[userInfoNum], v5);
}

// FUNC: public: void __thiscall idAsyncServer::UpdateUI(int)
void __thiscall idAsyncServer::UpdateUI(idAsyncServer *this, int clientNum)
{
  idDict *v3; // eax

  v3 = (idDict *)game->GetUserInfo(game, clientNum);
  if ( v3 )
    idAsyncServer::SendUserInfoBroadcast(this, clientNum, v3, 1);
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "idAsyncServer::UpdateUI: no info from game\n");
}

// FUNC: private: void __thiscall idAsyncServer::SendUserInfoToClient(int,int,class idDict const &)
void __thiscall idAsyncServer::SendUserInfoToClient(idAsyncServer *this, int clientNum, int userInfoNum, idDict *info)
{
  int v5; // eax
  idBitMsg msg; // [esp+8h] [ebp-4024h] BYREF
  char v7[16384]; // [esp+2Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
  {
    msg.writeData = (unsigned __int8 *)v7;
    msg.readData = (const unsigned __int8 *)v7;
    msg.maxSize = 0x4000;
    msg.numValueOverflows = 0;
    idBitMsg::WriteBits(&msg, 2, 8);
    idBitMsg::WriteBits(&msg, userInfoNum, 8);
    idBitMsg::WriteBits(&msg, 0, 1);
    v5 = idDict::Checksum(info);
    idBitMsg::WriteBits(&msg, v5, 32);
    idBitMsg::WriteDeltaDict(&msg, info, 0);
    idAsyncServer::SendReliableMessage(this, clientNum, &msg);
  }
}

// FUNC: private: void __thiscall idAsyncServer::SendSyncedCvarsBroadcast(class idDict const &)
void __thiscall idAsyncServer::SendSyncedCvarsBroadcast(idAsyncServer *this, idDict *cvars)
{
  int v3; // esi
  idMsgChannel *p_channel; // edi
  idBitMsg msg; // [esp+10h] [ebp-4024h] BYREF
  char v6[16384]; // [esp+34h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  msg.readData = (const unsigned __int8 *)v6;
  v3 = 0;
  msg.writeData = (unsigned __int8 *)v6;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, 3, 8);
  idBitMsg::WriteDeltaDict(&msg, cvars, &sessLocal.mapSpawnData.syncedCVars);
  p_channel = &this->clients[0].channel;
  do
  {
    if ( *(int *)&p_channel[-1].reliableReceive.buffer[16356] >= 3
      && v3 != this->localClientNum
      && !idMsgChannel::SendReliableMessage(p_channel, &msg) )
    {
      idMsgChannel::ClearReliableMessages(p_channel);
      idAsyncServer::DropClient(this, (int)p_channel, v3, "#str_107136");
    }
    ++v3;
    p_channel = (idMsgChannel *)((char *)p_channel + 65800);
  }
  while ( v3 < 32 );
  idDict::operator=(&sessLocal.mapSpawnData.syncedCVars, cvars);
}

// FUNC: private: void __thiscall idAsyncServer::SendSyncedCvarsToClient(int,class idDict const &)
void __thiscall idAsyncServer::SendSyncedCvarsToClient(idAsyncServer *this, int clientNum, const idDict *cvars)
{
  idBitMsg msg; // [esp+8h] [ebp-4024h] BYREF
  char v5[16384]; // [esp+2Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  if ( this->clients[clientNum].clientState >= SCS_CONNECTED )
  {
    msg.writeData = (unsigned __int8 *)v5;
    msg.readData = (const unsigned __int8 *)v5;
    msg.maxSize = 0x4000;
    msg.numValueOverflows = 0;
    idBitMsg::WriteBits(&msg, 3, 8);
    idBitMsg::WriteDeltaDict(&msg, cvars, 0);
    idAsyncServer::SendReliableMessage(this, clientNum, &msg);
  }
}

// FUNC: private: void __thiscall idAsyncServer::SendApplySnapshotToClient(int,int)
void __thiscall idAsyncServer::SendApplySnapshotToClient(idAsyncServer *this, int clientNum, int sequence)
{
  idBitMsg msg; // [esp+8h] [ebp-4024h] BYREF
  char v5[16384]; // [esp+2Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  msg.readData = (const unsigned __int8 *)v5;
  msg.writeData = (unsigned __int8 *)v5;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, 6, 8);
  idBitMsg::WriteBits(&msg, sequence, 32);
  if ( clientNum != this->localClientNum && !idMsgChannel::SendReliableMessage(&this->clients[clientNum].channel, &msg) )
  {
    idMsgChannel::ClearReliableMessages(&this->clients[clientNum].channel);
    idAsyncServer::DropClient(this, (int)this, clientNum, "#str_107136");
  }
}

// FUNC: private: bool __thiscall idAsyncServer::SendEmptyToClient(int,bool)
char __thiscall idAsyncServer::SendEmptyToClient(idAsyncServer *this, int clientNum, bool force)
{
  int realTime; // ecx
  int gameInitId; // edx
  idBitMsg msg; // [esp+8h] [ebp-4024h] BYREF
  char v8[16384]; // [esp+2Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  realTime = this->realTime;
  if ( this->clients[clientNum].lastEmptyTime > realTime )
    this->clients[clientNum].lastEmptyTime = realTime;
  if ( !force && this->realTime - this->clients[clientNum].lastEmptyTime < 500 )
    return 0;
  if ( idAsyncNetwork::verbose.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "sending empty to client %d: gameInitId = %d, gameFrame = %d, gameTime = %d\n",
      clientNum,
      this->gameInitId,
      this->gameFrame,
      this->gameTime);
  gameInitId = this->gameInitId;
  msg.readData = (const unsigned __int8 *)v8;
  msg.writeData = (unsigned __int8 *)v8;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, gameInitId, 32);
  idBitMsg::WriteBits(&msg, 0, 8);
  idMsgChannel::SendMessageA(&this->clients[clientNum].channel, &this->serverPort, this->serverTime, &msg);
  this->clients[clientNum].lastEmptyTime = this->realTime;
  return 1;
}

// FUNC: private: bool __thiscall idAsyncServer::SendPingToClient(int)
char __thiscall idAsyncServer::SendPingToClient(idAsyncServer *this, int clientNum)
{
  int realTime; // ecx
  int gameInitId; // edx
  idBitMsg msg; // [esp+8h] [ebp-4024h] BYREF
  char v7[16384]; // [esp+2Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  realTime = this->realTime;
  if ( this->clients[clientNum].lastPingTime > realTime )
    this->clients[clientNum].lastPingTime = realTime;
  if ( this->realTime - this->clients[clientNum].lastPingTime < 500 )
    return 0;
  if ( idAsyncNetwork::verbose.internalVar->integerValue == 2 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "pinging client %d: gameInitId = %d, gameFrame = %d, gameTime = %d\n",
      clientNum,
      this->gameInitId,
      this->gameFrame,
      this->gameTime);
  gameInitId = this->gameInitId;
  msg.readData = (const unsigned __int8 *)v7;
  msg.writeData = (unsigned __int8 *)v7;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, gameInitId, 32);
  idBitMsg::WriteBits(&msg, 1, 8);
  idBitMsg::WriteBits(&msg, this->realTime, 32);
  idMsgChannel::SendMessageA(&this->clients[clientNum].channel, &this->serverPort, this->serverTime, &msg);
  this->clients[clientNum].lastPingTime = this->realTime;
  return 1;
}

// FUNC: private: void __thiscall idAsyncServer::SendGameInitToClient(int)
void __thiscall idAsyncServer::SendGameInitToClient(idAsyncServer *this, int clientNum)
{
  int gameInitId; // [esp-8h] [ebp-4034h]
  idBitMsg msg; // [esp+8h] [ebp-4024h] BYREF
  char v5[16384]; // [esp+2Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  if ( idAsyncNetwork::verbose.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "sending gameinit to client %d: gameInitId = %d, gameFrame = %d, gameTime = %d\n",
      clientNum,
      this->gameInitId,
      this->gameFrame,
      this->gameTime);
  while ( this->clients[clientNum].channel.unsentFragments )
    idMsgChannel::SendNextFragment(&this->clients[clientNum].channel, &this->serverPort, this->serverTime);
  gameInitId = this->gameInitId;
  msg.writeData = (unsigned __int8 *)v5;
  msg.readData = (const unsigned __int8 *)v5;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, gameInitId, 32);
  idBitMsg::WriteBits(&msg, 2, 8);
  idBitMsg::WriteBits(&msg, this->gameFrame, 32);
  idBitMsg::WriteBits(&msg, this->gameTime, 32);
  idBitMsg::WriteDeltaDict(&msg, &sessLocal.mapSpawnData.serverInfo, 0);
  this->clients[clientNum].gameInitSequence = idMsgChannel::SendMessageA(
                                                &this->clients[clientNum].channel,
                                                &this->serverPort,
                                                this->serverTime,
                                                &msg);
}

// FUNC: private: bool __thiscall idAsyncServer::SendSnapshotToClient(int)
char __thiscall idAsyncServer::SendSnapshotToClient(idAsyncServer *this, int clientNum)
{
  int v3; // ebp
  serverClient_s *v4; // esi
  int gameInitId; // eax
  int v7; // ebx
  int numDuplicatedUsercmds; // eax
  int clientAheadTime; // eax
  int *p_gameFrame; // edx
  int integerValue; // eax
  int gameFrame; // ecx
  int v13; // edx
  int v14; // eax
  int v15; // eax
  int v16; // ebp
  int i; // esi
  const usercmd_t *v18; // ebx
  int serverTime; // ecx
  int v20; // [esp+14h] [ebp-4038h]
  int *v21; // [esp+18h] [ebp-4034h]
  usercmd_t *base; // [esp+20h] [ebp-402Ch]
  char v23[4]; // [esp+24h] [ebp-4028h] BYREF
  idBitMsg msg; // [esp+28h] [ebp-4024h] BYREF
  char v25[16384]; // [esp+4Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  v3 = clientNum;
  v4 = &this->clients[clientNum];
  if ( this->serverTime - this->clients[clientNum].lastSnapshotTime < idAsyncNetwork::serverSnapshotDelay.internalVar->integerValue )
    return 0;
  if ( idAsyncNetwork::verbose.internalVar->integerValue == 2 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "sending snapshot to client %d: gameInitId = %d, gameFrame = %d, gameTime = %d\n",
      clientNum,
      this->gameInitId,
      this->gameFrame,
      this->gameTime);
  this->clients[clientNum].clientAheadTime = this->clients[clientNum].gameTime - this->gameTimeResidual - this->gameTime;
  gameInitId = this->gameInitId;
  msg.writeData = (unsigned __int8 *)v25;
  v7 = 0;
  msg.readData = (const unsigned __int8 *)v25;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, gameInitId, 32);
  idBitMsg::WriteBits(&msg, 3, 8);
  idBitMsg::WriteBits(&msg, this->clients[clientNum].snapshotSequence, 32);
  idBitMsg::WriteBits(&msg, this->gameFrame, 32);
  idBitMsg::WriteBits(&msg, this->gameTime, 32);
  numDuplicatedUsercmds = this->clients[clientNum].numDuplicatedUsercmds;
  if ( numDuplicatedUsercmds >= -128 )
  {
    if ( numDuplicatedUsercmds > 127 )
      LOBYTE(numDuplicatedUsercmds) = 127;
  }
  else
  {
    LOBYTE(numDuplicatedUsercmds) = 0x80;
  }
  idBitMsg::WriteBits(&msg, (char)numDuplicatedUsercmds, 8);
  clientAheadTime = this->clients[clientNum].clientAheadTime;
  if ( clientAheadTime >= -32768 )
  {
    if ( clientAheadTime > 0x7FFF )
      LOWORD(clientAheadTime) = 0x7FFF;
  }
  else
  {
    LOWORD(clientAheadTime) = 0x8000;
  }
  idBitMsg::WriteBits(&msg, (__int16)clientAheadTime, -16);
  game->ServerWriteSnapshot(game, clientNum, this->clients[clientNum].snapshotSequence, &msg, (unsigned int *)v23, 32);
  p_gameFrame = &this->clients[0].gameFrame;
  base = 0;
  v20 = 0;
  v21 = &this->clients[0].gameFrame;
  do
  {
    if ( *(p_gameFrame - 9) && v7 != v3 && ((1 << (v7 & 0x1F)) & *(_DWORD *)&v23[4 * (v7 >> 5)]) != 0 )
    {
      integerValue = idAsyncNetwork::serverMaxUsercmdRelay.internalVar->integerValue;
      if ( integerValue >= 1 )
      {
        if ( integerValue > 10 )
          integerValue = 10;
      }
      else
      {
        integerValue = 1;
      }
      gameFrame = this->gameFrame;
      v13 = *p_gameFrame;
      v14 = gameFrame + integerValue;
      if ( v13 < v14 )
        v14 = v13;
      v15 = v14 - gameFrame;
      v16 = 1;
      if ( v15 >= 1 )
        v16 = v15;
      idBitMsg::WriteBits(&msg, v7, 8);
      idBitMsg::WriteBits(&msg, v16, 8);
      for ( i = 0; i < v16; ++i )
      {
        v18 = &this->userCmds[(unsigned __int8)(i + this->gameFrame)][v7];
        idAsyncNetwork::WriteUserCmdDelta(&msg, v18, base);
        base = (usercmd_t *)v18;
        v7 = v20;
      }
      v4 = &this->clients[clientNum];
      v3 = clientNum;
    }
    ++v7;
    p_gameFrame = v21 + 16450;
    v20 = v7;
    v21 += 16450;
  }
  while ( v7 < 32 );
  idBitMsg::WriteBits(&msg, 32, 8);
  idMsgChannel::SendMessageA(&v4->channel, &this->serverPort, this->serverTime, &msg);
  serverTime = this->serverTime;
  ++v4->snapshotSequence;
  v4->lastSnapshotTime = serverTime;
  v4->numDuplicatedUsercmds = 0;
  return 1;
}

// FUNC: private: void __thiscall idAsyncServer::ProcessChallengeMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncServer::ProcessChallengeMessage(idAsyncServer *this, netadr_t from, idBitMsg *msg)
{
  unsigned int v4; // ebx
  int v5; // edi
  challenge_s *challenges; // esi
  bool *v7; // esi
  int v8; // ebx
  int *v9; // esi
  int v10; // edi
  const char *v11; // eax
  const char *v12; // eax
  const char *v13; // eax
  const char *v14; // eax
  netadr_t v15; // [esp-14h] [ebp-4060h]
  netadr_t v16; // [esp-14h] [ebp-4060h]
  netadr_t v17; // [esp-Ch] [ebp-4058h]
  netadr_t v18; // [esp-Ch] [ebp-4058h]
  netadr_t v19; // [esp-Ch] [ebp-4058h]
  netadr_t v20; // [esp-Ch] [ebp-4058h]
  idPort *Bits; // [esp+10h] [ebp-403Ch]
  idPort *v22; // [esp+10h] [ebp-403Ch]
  int time; // [esp+14h] [ebp-4038h]
  int v24; // [esp+18h] [ebp-4034h]
  idBitMsg v25; // [esp+1Ch] [ebp-4030h] BYREF
  netadr_t result; // [esp+40h] [ebp-400Ch] BYREF
  char v27[16384]; // [esp+4Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v25);
  v4 = *(_DWORD *)&from.port;
  v5 = 0;
  Bits = (idPort *)idBitMsg::ReadBits(msg, 32);
  v24 = 0;
  time = 0x7FFFFFFF;
  challenges = this->challenges;
  while ( challenges->connected
       || !Sys_CompareNetAdrBase(from, challenges->address)
       || Bits != (idPort *)challenges->clientId )
  {
    if ( challenges->time < time )
    {
      time = challenges->time;
      v24 = v5;
    }
    ++v5;
    ++challenges;
    if ( v5 >= 1024 )
    {
      v5 = v24;
      v7 = &this->active + 92 * v24;
      *(netadr_t *)(v7 + 64) = from;
      *((_DWORD *)v7 + 19) = Bits;
      v8 = rand() << 16;
      *((_DWORD *)v7 + 20) = this->serverTime ^ rand() ^ v8;
      *((_DWORD *)v7 + 21) = this->serverTime;
      v7[92] = 0;
      *((_DWORD *)v7 + 24) = 0;
      *((_DWORD *)v7 + 25) = 0;
      *((_DWORD *)v7 + 26) = 0;
      idStr::operator=((idStr *)(v7 + 108), (char *)&entityFilter);
      v4 = *(_DWORD *)&from.port;
      v7[140] = 0;
      break;
    }
  }
  v9 = (int *)(&this->active + 92 * v5);
  v9[22] = this->serverTime;
  v10 = *(_DWORD *)common.type;
  v17.type = from.type;
  *(_QWORD *)v17.ip = __PAIR64__(v4, *(unsigned int *)from.ip);
  v11 = Sys_NetAdrToString(v17);
  (*(void (**)(netadrtype_t, const char *, ...))(v10 + 124))(common.type, "sending challenge 0x%x to %s\n", v9[20], v11);
  v25.writeData = (unsigned __int8 *)v27;
  v25.readData = (const unsigned __int8 *)v27;
  v25.maxSize = 0x4000;
  v25.numValueOverflows = 0;
  idBitMsg::WriteBits(&v25, -1, -16);
  idBitMsg::WriteString(&v25, "challengeResponse", -1);
  idBitMsg::WriteBits(&v25, v9[20], 32);
  idBitMsg::WriteBits(&v25, this->serverId, -16);
  v12 = cvarSystem->GetCVarString(cvarSystem, "fs_game_base");
  idBitMsg::WriteString(&v25, v12, -1);
  v13 = cvarSystem->GetCVarString(cvarSystem, "fs_game");
  idBitMsg::WriteString(&v25, v13, -1);
  v15.type = from.type;
  *(_QWORD *)v15.ip = __PAIR64__(v4, *(unsigned int *)from.ip);
  idPort::SendPacket(&this->serverPort, v15, v25.writeData, v25.curSize);
  v18.type = from.type;
  *(_QWORD *)v18.ip = __PAIR64__(v4, *(unsigned int *)from.ip);
  if ( !Sys_IsLANAddress(v18) || idAsyncNetwork::forceInternet.internalVar->integerValue )
  {
    if ( idAsyncNetwork::LANServer.internalVar->integerValue )
    {
      v19.type = from.type;
      *(_QWORD *)v19.ip = __PAIR64__(v4, *(unsigned int *)from.ip);
      v22 = *(idPort **)common.type;
      v14 = Sys_NetAdrToString(v19);
      ((void (*)(netadrtype_t, const char *, ...))v22[4].bytesWritten)(
        common.type,
        "net_LANServer is enabled. Client %s is not a LAN address, will be rejected\n",
        v14);
      v9[24] = 2;
    }
    else
    {
      v25.curSize = 0;
      v25.overflowed = 0;
      v25.writeBit = 0;
      idBitMsg::WriteBits(&v25, -1, -16);
      idBitMsg::WriteString(&v25, "srvAuth", -1);
      idBitMsg::WriteBits(&v25, 131136, 32);
      v20.type = from.type;
      *(_QWORD *)v20.ip = __PAIR64__(v4, *(unsigned int *)from.ip);
      idBitMsg::WriteNetadr(&v25, v20);
      idBitMsg::WriteBits(&v25, -1, 32);
      v16 = *idAsyncNetwork::GetMasterAddress(&result);
      idPort::SendPacket(&this->serverPort, v16, v25.writeData, v25.curSize);
    }
  }
  else
  {
    v9[24] = 1;
  }
}

// FUNC: private: bool __thiscall idAsyncServer::SendPureServerMessage(struct netadr_t,int)
char __thiscall idAsyncServer::SendPureServerMessage(idAsyncServer *this, netadr_t to, int OS)
{
  int v4; // esi
  const char *v5; // eax
  int type; // eax
  netadr_t *p_a; // esi
  int value; // [esp+10h] [ebp-422Ch] BYREF
  idAsyncServer *v9; // [esp+14h] [ebp-4228h]
  idBitMsg v10; // [esp+18h] [ebp-4224h] BYREF
  netadr_t a; // [esp+3Ch] [ebp-4200h] BYREF
  char v12[16384]; // [esp+23Ch] [ebp-4000h] BYREF

  v9 = this;
  idBitMsg::idBitMsg(&v10);
  fileSystem->GetPureServerChecksums(fileSystem, (int *)&a, OS, &value);
  if ( a.type )
  {
    v4 = *(_DWORD *)common.type;
    v5 = Sys_NetAdrToString(to);
    (*(void (**)(netadrtype_t, const char *, ...))(v4 + 132))(common.type, "client %s: sending pure pak list\n", v5);
    v10.writeData = (unsigned __int8 *)v12;
    v10.readData = (const unsigned __int8 *)v12;
    v10.maxSize = 0x4000;
    v10.numValueOverflows = 0;
    idBitMsg::WriteBits(&v10, -1, -16);
    idBitMsg::WriteString(&v10, "pureServer", -1);
    type = a.type;
    if ( a.type )
    {
      p_a = &a;
      do
      {
        idBitMsg::WriteBits(&v10, type, 32);
        type = *(_DWORD *)p_a->ip;
        p_a = (netadr_t *)((char *)p_a + 4);
      }
      while ( type );
    }
    idBitMsg::WriteBits(&v10, 0, 32);
    idBitMsg::WriteBits(&v10, value, 32);
    idPort::SendPacket(&v9->serverPort, to, v10.writeData, v10.curSize);
    return 1;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "pure server has no pak files referenced");
    return 0;
  }
}

// FUNC: private: bool __thiscall idAsyncServer::SendReliablePureToClient(int)
char __thiscall idAsyncServer::SendReliablePureToClient(idAsyncServer *this, int clientNum)
{
  int v4; // eax
  int *v5; // esi
  int v6; // [esp+Ch] [ebp-4228h] BYREF
  idBitMsg msg; // [esp+10h] [ebp-4224h] BYREF
  int value[128]; // [esp+34h] [ebp-4200h] BYREF
  char v9[16384]; // [esp+234h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  fileSystem->GetPureServerChecksums(fileSystem, value, this->clients[clientNum].OS, &v6);
  if ( value[0] )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "client %d: sending pure pak list (reliable channel) @ gameInitId %d\n",
      clientNum,
      this->gameInitId);
    msg.writeData = (unsigned __int8 *)v9;
    msg.readData = (const unsigned __int8 *)v9;
    msg.maxSize = 0x4000;
    msg.numValueOverflows = 0;
    idBitMsg::WriteBits(&msg, 0, 8);
    idBitMsg::WriteBits(&msg, this->gameInitId, 32);
    v4 = value[0];
    if ( value[0] )
    {
      v5 = value;
      do
      {
        idBitMsg::WriteBits(&msg, v4, 32);
        v4 = v5[1];
        ++v5;
      }
      while ( v4 );
    }
    idBitMsg::WriteBits(&msg, 0, 32);
    idBitMsg::WriteBits(&msg, v6, 32);
    idAsyncServer::SendReliableMessage(this, clientNum, &msg);
    return 1;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "pure server has no pak files referenced");
    return 0;
  }
}

// FUNC: private: bool __thiscall idAsyncServer::VerifyChecksumMessage(int,struct netadr_t const *,class idBitMsg const &,class idStr &,int)
char __thiscall idAsyncServer::VerifyChecksumMessage(
        idAsyncServer *this,
        int clientNum,
        const netadr_t *from,
        idBitMsg *msg,
        idStr *reply,
        int OS)
{
  int v6; // esi
  int Bits; // eax
  int v8; // esi
  char *v9; // eax
  int v11; // ecx
  int v12; // esi
  int v13; // eax
  int v14; // esi
  char *v15; // eax
  char *v16; // eax
  int serverGamePakChecksum; // [esp+Ch] [ebp-404h] BYREF
  int serverChecksums[128]; // [esp+10h] [ebp-400h] BYREF
  int checksums[128]; // [esp+210h] [ebp-200h]

  v6 = 0;
  do
  {
    Bits = idBitMsg::ReadBits(msg, 32);
    checksums[v6++] = Bits;
    if ( v6 >= 128 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "MAX_PURE_PAKS ( %d ) exceeded in idAsyncServer::ProcessPureMessage\n",
        128);
      sprintf(reply, "#str_107144");
      return 0;
    }
  }
  while ( Bits );
  v8 = idBitMsg::ReadBits(msg, 32);
  fileSystem->GetPureServerChecksums(fileSystem, serverChecksums, OS, &serverGamePakChecksum);
  if ( serverGamePakChecksum == v8 )
  {
    v11 = serverChecksums[0];
    v12 = 0;
    if ( serverChecksums[0] )
    {
      v13 = 0;
      while ( checksums[v13] == v11 )
      {
        v13 = ++v12;
        v11 = serverChecksums[v12];
        if ( !v11 )
          goto LABEL_14;
      }
      if ( from )
        v16 = (char *)Sys_NetAdrToString(*from);
      else
        v16 = va("%d", clientNum);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
        common.type,
        "client %s: pak missing ( 0x%x )\n",
        v16,
        serverChecksums[v12]);
      sprintf(reply, "pak missing ( 0x%x )\n", serverChecksums[v12]);
      return 0;
    }
    else
    {
LABEL_14:
      v14 = checksums[v12];
      if ( v14 )
      {
        if ( from )
          v15 = (char *)Sys_NetAdrToString(*from);
        else
          v15 = va("%d", clientNum);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
          common.type,
          "client %s: extra pak file referenced ( 0x%x )\n",
          v15,
          v14);
        sprintf(reply, "extra pak file referenced ( 0x%x )\n", v14);
        return 0;
      }
      else
      {
        return 1;
      }
    }
  }
  else
  {
    if ( from )
      v9 = (char *)Sys_NetAdrToString(*from);
    else
      v9 = va("%d", clientNum);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "client %s: invalid game code pak ( 0x%x )\n",
      v9,
      v8);
    sprintf(reply, "#str_107145");
    return 0;
  }
}

// FUNC: private: void __thiscall idAsyncServer::ProcessReliablePure(int,class idBitMsg const &)
void __thiscall idAsyncServer::ProcessReliablePure(idAsyncServer *this, int clientNum, idBitMsg *msg)
{
  int Bits; // eax
  bool *v5; // ebp
  idStr reply; // [esp+8h] [ebp-4050h] BYREF
  idBitMsg v7; // [esp+28h] [ebp-4030h] BYREF
  char v8[16384]; // [esp+4Ch] [ebp-400Ch] BYREF
  int v9; // [esp+4054h] [ebp-4h]

  reply.len = 0;
  reply.alloced = 20;
  reply.data = reply.baseBuffer;
  reply.baseBuffer[0] = 0;
  v9 = 0;
  idBitMsg::idBitMsg(&v7);
  Bits = idBitMsg::ReadBits(msg, 32);
  if ( Bits != this->gameInitId )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "client %d: ignoring reliable pure from an old gameInit (%d)\n",
      clientNum,
      Bits);
    v9 = -1;
    idStr::FreeData(&reply);
    return;
  }
  v5 = &this->active + 65800 * clientNum;
  if ( *((_DWORD *)v5 + 23570) != 2 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "client %d: got reliable pure while != SCS_PUREWAIT, sending a reload\n",
      clientNum);
    v7.readData = (const unsigned __int8 *)v8;
    v7.writeData = (unsigned __int8 *)v8;
    v7.maxSize = 0x4000;
    v7.numValueOverflows = 0;
    idBitMsg::WriteBits(&v7, 1, 8);
    idAsyncServer::SendReliableMessage(this, clientNum, msg);
LABEL_8:
    *((_DWORD *)v5 + 23570) = 3;
    goto LABEL_9;
  }
  if ( idAsyncServer::VerifyChecksumMessage(this, clientNum, 0, msg, &reply, *((_DWORD *)v5 + 23568)) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "client %d: passed pure checks (reliable channel)\n",
      clientNum);
    goto LABEL_8;
  }
  idAsyncServer::DropClient(this, (int)this, clientNum, reply.data);
LABEL_9:
  v9 = -1;
  idStr::FreeData(&reply);
}

// FUNC: public: void __thiscall idAsyncServer::SendReliableGameMessage(int,class idBitMsg const &)
void __thiscall idAsyncServer::SendReliableGameMessage(
        idAsyncServer *this,
        unsigned int clientNum,
        const idBitMsg *msg)
{
  int v4; // esi
  idMsgChannel *p_channel; // edi
  idBitMsg msga; // [esp+8h] [ebp-4024h] BYREF
  char v7[16384]; // [esp+2Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msga);
  msga.readData = (const unsigned __int8 *)v7;
  v4 = 0;
  msga.writeData = (unsigned __int8 *)v7;
  msga.maxSize = 0x4000;
  msga.numValueOverflows = 0;
  idBitMsg::WriteBits(&msga, 7, 8);
  idBitMsg::WriteData(&msga, msg->readData, msg->curSize);
  if ( clientNum > 0x1F )
  {
    p_channel = &this->clients[0].channel;
    do
    {
      if ( *(_DWORD *)&p_channel[-1].reliableReceive.buffer[16356] == 4
        && v4 != this->localClientNum
        && !idMsgChannel::SendReliableMessage(p_channel, &msga) )
      {
        idMsgChannel::ClearReliableMessages(p_channel);
        idAsyncServer::DropClient(this, v4, "#str_107136");
      }
      ++v4;
      p_channel = (idMsgChannel *)((char *)p_channel + 65800);
    }
    while ( v4 < 32 );
  }
  else if ( this->clients[clientNum].clientState == SCS_INGAME )
  {
    idAsyncServer::SendReliableMessage(this, clientNum, &msga);
  }
}

// FUNC: public: void __thiscall idAsyncServer::SendReliableGameMessageExcluding(int,class idBitMsg const &)
void __thiscall idAsyncServer::SendReliableGameMessageExcluding(
        idAsyncServer *this,
        int clientNum,
        const idBitMsg *msg)
{
  int v4; // esi
  idMsgChannel *p_channel; // edi
  idBitMsg msga; // [esp+10h] [ebp-4024h] BYREF
  char v7[16384]; // [esp+34h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msga);
  msga.readData = (const unsigned __int8 *)v7;
  v4 = 0;
  msga.writeData = (unsigned __int8 *)v7;
  msga.maxSize = 0x4000;
  msga.numValueOverflows = 0;
  idBitMsg::WriteBits(&msga, 7, 8);
  idBitMsg::WriteData(&msga, msg->readData, msg->curSize);
  p_channel = &this->clients[0].channel;
  do
  {
    if ( v4 != clientNum
      && *(_DWORD *)&p_channel[-1].reliableReceive.buffer[16356] == 4
      && v4 != this->localClientNum
      && !idMsgChannel::SendReliableMessage(p_channel, &msga) )
    {
      idMsgChannel::ClearReliableMessages(p_channel);
      idAsyncServer::DropClient(this, (int)p_channel, v4, "#str_107136");
    }
    ++v4;
    p_channel = (idMsgChannel *)((char *)p_channel + 65800);
  }
  while ( v4 < 32 );
}

// FUNC: private: void __thiscall idAsyncServer::PrintOOB(struct netadr_t,int,char const *)
void __thiscall idAsyncServer::PrintOOB(idAsyncServer *this, netadr_t to, int opcode, char *string)
{
  idBitMsg v5; // [esp+4h] [ebp-4024h] BYREF
  char v6[16384]; // [esp+28h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v5);
  v5.readData = (const unsigned __int8 *)v6;
  v5.writeData = (unsigned __int8 *)v6;
  v5.maxSize = 0x4000;
  v5.numValueOverflows = 0;
  idBitMsg::WriteBits(&v5, -1, -16);
  idBitMsg::WriteString(&v5, "print", -1);
  idBitMsg::WriteBits(&v5, opcode, 32);
  idBitMsg::WriteString(&v5, string, -1);
  idPort::SendPacket(&this->serverPort, to, v5.writeData, v5.curSize);
}

// FUNC: private: void __thiscall idAsyncServer::WriteInfo(class idBitMsg &)
void __thiscall idAsyncServer::WriteInfo(idAsyncServer *this, idBitMsg *msg)
{
  int v3; // ebp
  idDict *userInfo; // edi
  int *p_clientPing; // ebx
  const idKeyValue *Key; // eax
  const char *data; // eax
  const idKeyValue *v8; // eax
  const char *v9; // eax
  int v10; // eax

  idBitMsg::WriteBits(msg, 131136, 32);
  idBitMsg::WriteDeltaDict(msg, &sessLocal.mapSpawnData.serverInfo, 0);
  v3 = 0;
  userInfo = sessLocal.mapSpawnData.userInfo;
  p_clientPing = &this->clients[0].clientPing;
  do
  {
    if ( *(p_clientPing - 4) >= 3 )
    {
      idBitMsg::WriteBits(msg, v3, 8);
      idBitMsg::WriteBits(msg, *p_clientPing, -16);
      idBitMsg::WriteBits(msg, p_clientPing[11], 32);
      Key = idDict::FindKey(userInfo, "ui_name");
      if ( Key )
        data = Key->value->data;
      else
        data = "Player";
      idBitMsg::WriteString(msg, data, -1);
      v8 = idDict::FindKey(userInfo, "ui_clan");
      if ( v8 )
        v9 = v8->value->data;
      else
        v9 = &entityFilter;
      idBitMsg::WriteString(msg, v9, -1);
    }
    ++userInfo;
    ++v3;
    p_clientPing += 16450;
  }
  while ( (int)userInfo < (int)sessLocal.mapSpawnData.mapLastUIRequestTime );
  idBitMsg::WriteBits(msg, 32, 8);
  v10 = fileSystem->GetOSMask(fileSystem);
  idBitMsg::WriteBits(msg, v10, 32);
}

// FUNC: public: void __thiscall idAsyncServer::MasterHeartbeat(bool)
void __thiscall idAsyncServer::MasterHeartbeat(idAsyncServer *this, bool force)
{
  int serverTime; // eax
  int i; // edi
  int v5; // ebx
  const char *v6; // eax
  netadr_t adr; // [esp+Ch] [ebp-4030h] BYREF
  idBitMsg msg; // [esp+18h] [ebp-4024h] BYREF
  char v9[16384]; // [esp+3Ch] [ebp-4000h] BYREF

  if ( idAsyncNetwork::LANServer.internalVar->integerValue )
  {
    if ( force )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "net_LANServer is enabled. Not sending heartbeats\n");
  }
  else
  {
    if ( force )
      this->nextHeartbeatTime = 0;
    serverTime = this->serverTime;
    if ( serverTime >= this->nextHeartbeatTime )
    {
      this->nextHeartbeatTime = serverTime + 300000;
      for ( i = 0; i < 5; ++i )
      {
        if ( idAsyncNetwork::GetMasterAddress(i, &adr) )
        {
          v5 = *(_DWORD *)common.type;
          v6 = Sys_NetAdrToString(adr);
          (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(common.type, "Sending heartbeat to %s\n", v6);
          idBitMsg::idBitMsg(&msg);
          msg.writeData = (unsigned __int8 *)v9;
          msg.readData = (const unsigned __int8 *)v9;
          msg.maxSize = 0x4000;
          msg.numValueOverflows = 0;
          idBitMsg::WriteBits(&msg, -1, -16);
          idBitMsg::WriteString(&msg, "heartbeat", -1);
          idAsyncServer::WriteInfo(this, &msg);
          idPort::SendPacket(&this->serverPort, adr, msg.writeData, msg.curSize);
        }
      }
    }
  }
}

// FUNC: private: void __thiscall idAsyncServer::SendEnterGameToClient(int)
void __thiscall idAsyncServer::SendEnterGameToClient(idAsyncServer *this, int clientNum)
{
  idBitMsg msg; // [esp+8h] [ebp-4024h] BYREF
  char v4[16384]; // [esp+2Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  msg.readData = (const unsigned __int8 *)v4;
  msg.writeData = (unsigned __int8 *)v4;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, 8, 8);
  if ( clientNum != this->localClientNum && !idMsgChannel::SendReliableMessage(&this->clients[clientNum].channel, &msg) )
  {
    idMsgChannel::ClearReliableMessages(&this->clients[clientNum].channel);
    idAsyncServer::DropClient(this, (int)this, clientNum, "#str_107136");
  }
}

// FUNC: private: void __thiscall idAsyncServer::SendGUIDsToClient(int)
void __thiscall idAsyncServer::SendGUIDsToClient(idAsyncServer *this, int clientNum)
{
  int v3; // edi
  idMsgChannel *p_channel; // ebx
  int v5; // edi
  char *guid; // ebx
  idMsgChannel *v7; // edi
  bool *v8; // [esp+10h] [ebp-4028h]
  idBitMsg msg; // [esp+14h] [ebp-4024h] BYREF
  char v10[16384]; // [esp+38h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  msg.readData = (const unsigned __int8 *)v10;
  v3 = 0;
  msg.writeData = (unsigned __int8 *)v10;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  idBitMsg::WriteBits(&msg, 9, 8);
  idBitMsg::WriteBits(&msg, clientNum, 8);
  v8 = &this->active + 65800 * clientNum;
  idBitMsg::WriteString(&msg, (const char *)v8 + 160056, -1);
  p_channel = &this->clients[0].channel;
  do
  {
    if ( *(int *)&p_channel[-1].reliableReceive.buffer[16356] >= 3 )
    {
      if ( v3 == this->localClientNum )
      {
        idAsyncServer::SetClientGUID(this, clientNum, (const char *)v8 + 160056);
      }
      else if ( !idMsgChannel::SendReliableMessage(p_channel, &msg) )
      {
        idMsgChannel::ClearReliableMessages(p_channel);
        idAsyncServer::DropClient(this, v3, v3, "#str_107136");
      }
    }
    ++v3;
    p_channel = (idMsgChannel *)((char *)p_channel + 65800);
  }
  while ( v3 < 32 );
  v5 = 0;
  msg.curSize = 0;
  msg.overflowed = 0;
  msg.writeBit = 0;
  idBitMsg::WriteBits(&msg, 9, 8);
  guid = this->clients[0].guid;
  do
  {
    if ( *((int *)guid - 16444) >= 3 )
    {
      idBitMsg::WriteBits(&msg, v5, 8);
      idBitMsg::WriteString(&msg, guid, -1);
    }
    ++v5;
    guid += 65800;
  }
  while ( v5 < 32 );
  if ( clientNum != this->localClientNum )
  {
    v7 = (idMsgChannel *)(v8 + 94324);
    if ( !idMsgChannel::SendReliableMessage((idMsgChannel *)(v8 + 94324), &msg) )
    {
      idMsgChannel::ClearReliableMessages(v7);
      idAsyncServer::DropClient(this, (int)v7, clientNum, "#str_107136");
    }
  }
}

// FUNC: public: void __thiscall idAsyncServer::UpdateAsyncStatsAvg(void)
void __thiscall idAsyncServer::UpdateAsyncStatsAvg(idAsyncServer *this)
{
  int stats_current; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int *v6; // ecx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx

  stats_current = this->stats_current;
  this->stats_average_sum -= this->stats_outrate[stats_current];
  this->stats_outrate[stats_current] = idAsyncServer::GetOutgoingRate(&idAsyncNetwork::server);
  v3 = this->stats_current;
  v4 = this->stats_outrate[v3];
  if ( v4 <= this->stats_max )
  {
    if ( v3 == this->stats_max_index )
    {
      this->stats_max = 0;
      v5 = 2;
      v6 = &this->stats_outrate[1];
      do
      {
        v7 = *(v6 - 1);
        if ( v7 > this->stats_max )
        {
          this->stats_max = v7;
          this->stats_max_index = v5 - 2;
        }
        if ( *v6 > this->stats_max )
        {
          this->stats_max = *v6;
          this->stats_max_index = v5 - 1;
        }
        v8 = v6[1];
        if ( v8 > this->stats_max )
        {
          this->stats_max = v8;
          this->stats_max_index = v5;
        }
        v9 = v6[2];
        if ( v9 > this->stats_max )
        {
          this->stats_max = v9;
          this->stats_max_index = v5 + 1;
        }
        v10 = v6[3];
        if ( v10 > this->stats_max )
        {
          this->stats_max = v10;
          this->stats_max_index = v5 + 2;
        }
        v11 = v6[4];
        if ( v11 > this->stats_max )
        {
          this->stats_max = v11;
          this->stats_max_index = v5 + 3;
        }
        v5 += 6;
        v6 += 6;
      }
      while ( v5 - 2 < 60 );
    }
  }
  else
  {
    this->stats_max = v4;
    this->stats_max_index = v3;
  }
  this->stats_average_sum += this->stats_outrate[v3];
  this->stats_current = (v3 + 1) % 60;
}

// FUNC: public: void __thiscall idAsyncServer::GetAsyncStatsAvgMsg(class idStr &)
void __thiscall idAsyncServer::GetAsyncStatsAvgMsg(idAsyncServer *this, idStr *msg)
{
  sprintf(
    msg,
    "avrg out: %d B/s - max %d B/s ( over %d ms )",
    this->stats_average_sum / 60,
    this->stats_max,
    60 * idAsyncNetwork::serverSnapshotDelay.internalVar->integerValue);
}

// FUNC: public: void __thiscall idAsyncServer::ListClients(void)
void __thiscall idAsyncServer::ListClients(idAsyncServer *this)
{
  int v1; // ebx
  idDict *userInfo; // edi
  serverClientState_t *p_clientState; // ebp
  const char *v4; // esi
  const idKeyValue *Key; // eax
  const char *data; // ecx

  v1 = 0;
  userInfo = sessLocal.mapSpawnData.userInfo;
  p_clientState = &this->clients[0].clientState;
  do
  {
    if ( *p_clientState )
    {
      switch ( *p_clientState )
      {
        case SCS_ZOMBIE:
          v4 = "zombie";
          break;
        case SCS_CONNECTED:
          v4 = "connected";
          break;
        case SCS_INGAME:
          v4 = "in game";
          break;
        default:
          v4 = "unknown";
          break;
      }
      Key = idDict::FindKey(userInfo, "ui_name");
      if ( Key )
        data = Key->value->data;
      else
        data = "???";
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%2d  %-9s %s\n",
        v1,
        v4,
        data);
    }
    ++userInfo;
    ++v1;
    p_clientState += 16450;
  }
  while ( (int)userInfo < (int)sessLocal.mapSpawnData.mapLastUIRequestTime );
}

// FUNC: public: void __thiscall idAsyncServer::FakeClientPacifist_f(class idCmdArgs const &)
void __thiscall idAsyncServer::FakeClientPacifist_f(idAsyncServer *this, const idCmdArgs *args)
{
  unsigned int v3; // eax
  unsigned int v4; // ecx
  bool v5; // al
  idDict *v6; // ecx
  const idKeyValue *Key; // eax
  const char *data; // eax
  const idKeyValue *v9; // eax
  const char *v10; // eax

  if ( idAsyncNetwork::client.active )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "FakeClientPacifist_f() - Command can only be run on server\n");
  }
  else if ( args->argc > 1 )
  {
    v3 = atoi(args->argv[1]);
    if ( v3 > 0x1F )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "FakeClientPacifist_f() - client num '%d' out of range (valid: 0 -> %d)\n",
        v3,
        32);
    }
    else if ( this->clients[v3].channel.remoteAddress.type == NA_FAKE )
    {
      v4 = v3;
      v5 = !this->fakeInfo[v3].pacifist;
      this->fakeInfo[v4].pacifist = v5;
      v6 = &sessLocal.mapSpawnData.userInfo[v4];
      if ( v5 )
      {
        Key = idDict::FindKey(v6, "name");
        if ( Key )
          data = Key->value->data;
        else
          data = &entityFilter;
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "FakeClientPacifist_f() - '%s' is now peaceful\n",
          data);
      }
      else
      {
        v9 = idDict::FindKey(v6, "name");
        if ( v9 )
          v10 = v9->value->data;
        else
          v10 = &entityFilter;
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "FakeClientPacifist_f() - '%s' is now aggressive\n",
          v10);
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "FakeClientPacifist_f() - client num '%d' is not a fake client\n",
        v3);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "FakeClientPacifist_f() - Command requires an argument: client num of desired fake client\n");
  }
}

// FUNC: public: void __thiscall idAsyncServer::FakeClient_f(class idCmdArgs const &)
void __thiscall idAsyncServer::FakeClient_f(idAsyncServer *this, const idCmdArgs *args)
{
  int argc; // eax
  int v4; // esi
  const char **v5; // edi
  const char *v6; // eax
  const char *v7; // eax
  int v8; // edi
  serverClientState_t *i; // eax
  bool *v10; // esi
  int v11; // esi
  idDict *v12; // eax
  const char *v13; // eax
  netadr_t v14; // [esp-10h] [ebp-34h]
  bool pacifist; // [esp+13h] [ebp-11h]
  int count; // [esp+14h] [ebp-10h]

  pacifist = 0;
  if ( idAsyncNetwork::client.active )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "FakeClient_f() - Command can only be run on server\n");
  }
  else
  {
    argc = args->argc;
    v4 = 1;
    count = 1;
    if ( args->argc <= 1 )
      goto LABEL_30;
    v5 = (const char **)&args->argv[1];
    do
    {
      if ( v4 < 0 || v4 >= argc )
        v6 = &entityFilter;
      else
        v6 = *v5;
      if ( idStr::Icmp(v6, "add") )
      {
        if ( v4 < 0 || v4 >= args->argc )
          v7 = &entityFilter;
        else
          v7 = *v5;
        if ( !idStr::Icmp(v7, "pacifist") )
          pacifist = 1;
      }
      else
      {
        ++v4;
        ++v5;
        if ( v4 < 0 || v4 >= args->argc )
          count = atol(&entityFilter);
        else
          count = atol(*v5);
      }
      argc = args->argc;
      ++v4;
      ++v5;
    }
    while ( v4 < args->argc );
    if ( count > 0 )
    {
LABEL_30:
      do
      {
        v8 = 0;
        for ( i = &this->clients[0].clientState; *i; i += 16450 )
        {
          if ( ++v8 >= 32 )
            return;
        }
        if ( v8 == -1 )
          break;
        idAsyncServer::InitClient(this, v8, v8, 10000);
        v10 = &this->active + 65800 * v8;
        v14.type = NA_FAKE;
        *(_QWORD *)v14.ip = 0i64;
        idMsgChannel::Init((idMsgChannel *)(v10 + 94324), v14, this->serverId);
        *((_DWORD *)v10 + 23570) = 4;
        v11 = v8;
        v12 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 512);
        idDict::operator=(&sessLocal.mapSpawnData.userInfo[v8], v12);
        v13 = va("FAKE%d", v8);
        idDict::Set(&sessLocal.mapSpawnData.userInfo[v8], "ui_name", v13);
        this->fakeInfo[v11].turnTime = 100;
        this->fakeInfo[v11].jumpTime = 100;
        this->fakeInfo[v11].attackTime = 100;
        this->fakeInfo[v11].turnDir = 0.0;
        this->fakeInfo[v11].currentAngle = 0.0;
        this->fakeInfo[v11].lastOrigin.z = 0.0;
        this->fakeInfo[v11].lastOrigin.y = 0.0;
        this->fakeInfo[v11].lastOrigin.x = 0.0;
        this->fakeInfo[v11].followClient = 0;
        this->fakeInfo[v11].pacifist = pacifist;
        game->SetUserInfo(game, v8, &sessLocal.mapSpawnData.userInfo[v8], 0);
        game->ServerClientBegin(game, v8);
        idAsyncServer::SendUserInfoBroadcast(this, v8, &sessLocal.mapSpawnData.userInfo[v8], 1);
        --count;
      }
      while ( count > 0 );
    }
  }
}

// FUNC: public: void __thiscall idAsyncServer::PbSendPacket(struct netadr_t,void const *,int)
void __thiscall idAsyncServer::PbSendPacket(idAsyncServer *this, netadr_t to, void *data, int size)
{
  idBitMsg v5; // [esp+4h] [ebp-4024h] BYREF
  char v6[16384]; // [esp+28h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v5);
  v5.writeData = (unsigned __int8 *)v6;
  v5.readData = (const unsigned __int8 *)v6;
  v5.maxSize = 0x4000;
  v5.numValueOverflows = 0;
  idBitMsg::WriteData(&v5, data, size);
  idPort::SendPacket(&this->serverPort, to, v5.writeData, v5.curSize);
}

// FUNC: public: void __thiscall idAsyncServer::Kill(void)
void __usercall idAsyncServer::Kill(idAsyncServer *this@<ecx>, int a2@<edi>)
{
  int i; // esi
  int v4; // esi
  bool *p_unsentFragments; // edi
  int v6; // [esp+4h] [ebp-4h]

  if ( this->active )
  {
    if ( this->localClientNum >= 0 )
      idAsyncClient::SendClientHeartbeat(&idAsyncNetwork::client, 1, 0);
    for ( i = 0; i < 32; ++i )
      idAsyncServer::DropClient(this, a2, i, "#str_107135");
    v6 = 4;
    do
    {
      v4 = 0;
      p_unsentFragments = &this->clients[0].channel.unsentFragments;
      do
      {
        if ( *((_DWORD *)p_unsentFragments - 30) == 1 )
        {
          if ( *p_unsentFragments )
            idMsgChannel::SendNextFragment(
              (idMsgChannel *)(p_unsentFragments - 76),
              &this->serverPort,
              this->serverTime);
          else
            idAsyncServer::SendEmptyToClient(this, v4, 1);
        }
        ++v4;
        p_unsentFragments += 65800;
      }
      while ( v4 < 32 );
      Sys_Sleep(10);
      --v6;
    }
    while ( v6 );
    fileSystem->ClearPureChecksums(fileSystem);
    this->active = 0;
    session->Stop(session);
  }
}

// FUNC: public: void __thiscall idAsyncServer::ExecuteMapChange(void)
void __thiscall idAsyncServer::ExecuteMapChange(idAsyncServer *this)
{
  idFileSystem_vtbl *v2; // edx
  idGame_vtbl *v3; // edi
  const char *v4; // eax
  int v5; // eax
  int v6; // eax
  idCVarSystem_vtbl *v7; // edx
  const idKeyValue *Key; // eax
  const char *data; // eax
  findFile_t v10; // edi
  int v11; // edi
  int len; // esi
  char *v13; // ecx
  char *v14; // edx
  char v15; // al
  int v16; // eax
  char v17; // cl
  char *v18; // edx
  char v19; // al
  int v20; // edi
  serverClientState_t *p_clientState; // ebp
  const char *v22; // eax
  int v23; // edi
  serverClientState_t *v24; // ebp
  const idKeyValue *v25; // eax
  const char *v26; // eax
  const idKeyValue *v27; // eax
  const char *v28; // eax
  idSession_vtbl *v29; // edi
  int v30; // eax
  int v31; // eax
  idGame_vtbl *v32; // edi
  BOOL v33; // eax
  const idKeyValue *v34; // eax
  const char *v35; // eax
  int v36; // edi
  serverClientState_t *v37; // ebp
  serverClientState_t *v38; // eax
  int v39; // ebp
  idDict *userInfo; // edi
  float *p_y; // esi
  int v42; // edx
  idDict *v43; // eax
  const char *v44; // eax
  netadr_t v45; // [esp+24h] [ebp-40B4h]
  const char *v46; // [esp+2Ch] [ebp-40ACh]
  int serverId; // [esp+30h] [ebp-40A8h]
  char v48; // [esp+34h] [ebp-40A4h]
  serverClientState_t *v49; // [esp+48h] [ebp-4090h]
  idStr v50; // [esp+4Ch] [ebp-408Ch] BYREF
  idMsgChannel *v51; // [esp+6Ch] [ebp-406Ch]
  idStr string; // [esp+70h] [ebp-4068h] BYREF
  int v53; // [esp+90h] [ebp-4048h]
  int v54; // [esp+94h] [ebp-4044h]
  int v55; // [esp+98h] [ebp-4040h]
  idBitMsg msg; // [esp+9Ch] [ebp-403Ch] BYREF
  int v57; // [esp+C0h] [ebp-4018h]
  char v58[16384]; // [esp+CCh] [ebp-400Ch] BYREF
  int v59; // [esp+40D4h] [ebp-4h]

  idBitMsg::idBitMsg(&msg);
  string.len = 0;
  string.alloced = 20;
  string.data = string.baseBuffer;
  string.baseBuffer[0] = 0;
  v2 = fileSystem->__vftable;
  v59 = 0;
  v2->ClearPureChecksums(fileSystem);
  v3 = game->__vftable;
  v4 = cvarSystem->GetCVarString(cvarSystem, "si_gametype");
  v5 = ((int (__thiscall *)(idCVarSystem *, const char *, const char *))cvarSystem->GetCVarString)(
         cvarSystem,
         "si_map",
         v4);
  v6 = ((int (__thiscall *)(idGame *, char **, int))v3->GetBestGameType)(game, &v50.data, v5);
  v7 = cvarSystem->__vftable;
  v46 = *(const char **)(v6 + 4);
  LOBYTE(v59) = 1;
  v7->SetCVarString(cvarSystem, "si_gametype", v46, 0);
  LOBYTE(v59) = 0;
  idStr::FreeData(&v50);
  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "rescanSI");
  Key = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_map");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  sprintf(&string, "maps/%s", data);
  idStr::SetFileExtension(&string, ".map");
  v10 = fileSystem->FindFile(fileSystem, string.data);
  if ( v10 == FIND_NO )
  {
    v11 = string.len + 1;
    v50.len = 0;
    v50.alloced = 20;
    v50.data = v50.baseBuffer;
    v50.baseBuffer[0] = 0;
    len = string.len;
    if ( string.len + 1 > 20 )
      idStr::ReAllocate(&v50, v11, 1);
    v13 = string.data;
    v14 = v50.data;
    do
    {
      v15 = *v13;
      *v14++ = *v13++;
    }
    while ( v15 );
    v50.len = len;
    LOBYTE(v59) = 2;
    if ( v11 + 1 > v50.alloced )
      idStr::ReAllocate(&v50, v11 + 1, 1);
    v16 = 0;
    v17 = 99;
    do
    {
      v18 = &v50.data[v16++];
      v18[v50.len] = v17;
      v17 = aC_3[v16];
    }
    while ( v17 );
    v50.len = v11;
    v50.data[v11] = 0;
    v10 = fileSystem->FindFile(fileSystem, v50.data);
    LOBYTE(v59) = 0;
    idStr::FreeData(&v50);
  }
  if ( v10 == FIND_NO )
  {
    (*(void (__stdcall **)(netadrtype_t))(*(_DWORD *)common.type + 124))(common.type);
LABEL_69:
    ((void (__thiscall *)(idCmdSystem *, int))cmdSystem->BufferCommandText)(cmdSystem, 2);
    goto LABEL_70;
  }
  if ( v10 == FIND_ADDON )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "map %s is in an addon pak - reloading\n",
      string.data);
    v19 = 1;
  }
  else
  {
    v19 = 0;
  }
  if ( !this->serverReloadingEngine && (v19 || idAsyncNetwork::serverReloadEngine.internalVar->integerValue) )
  {
    if ( idAsyncNetwork::serverReloadEngine.internalVar->integerValue )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "net_serverReloadEngine enabled - doing a full reload\n");
    v20 = 0;
    p_clientState = &this->clients[0].clientState;
    do
    {
      if ( *(int *)p_clientState >= 2 && v20 != this->localClientNum )
      {
        msg.writeData = (unsigned __int8 *)v58;
        msg.readData = (const unsigned __int8 *)v58;
        msg.maxSize = 0x4000;
        msg.numValueOverflows = 0;
        idBitMsg::WriteBits(&msg, 1, 8);
        idAsyncServer::SendReliableMessage(this, v20, &msg);
        *p_clientState = SCS_ZOMBIE;
      }
      ++v20;
      p_clientState += 16450;
    }
    while ( v20 < 32 );
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "reloadEngine");
    this->serverReloadingEngine = 1;
    goto LABEL_69;
  }
  this->serverReloadingEngine = 0;
  this->serverTime = 0;
  this->nextHeartbeatTime = 0;
  this->gameInitId ^= Sys_Milliseconds();
  this->gameFrame = 0;
  this->gameTime = 0;
  this->gameTimeResidual = 0;
  memset(this->userCmds, 0, sizeof(this->userCmds));
  if ( idAsyncNetwork::serverDedicated.internalVar->integerValue )
  {
    this->localClientNum = -1;
  }
  else
  {
    idAsyncServer::InitLocalClient(this, 0);
    v22 = cvarSystem->GetCVarString(cvarSystem, "com_guid");
    if ( this->clients[0].clientState == SCS_INGAME )
    {
      strncpy(this->clients[0].guid, v22, 0xCu);
      this->clients[0].guid[11] = 0;
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "idAsyncServer::SetClientGUID() - Invalid client num '%d' specified",
        0);
    }
    session->EmitClientAuth(session);
  }
  v23 = 0;
  v24 = &this->clients[0].clientState;
  do
  {
    if ( *(int *)v24 >= 2 && v23 != this->localClientNum )
    {
      idAsyncServer::InitClient(this, v23, *((_DWORD *)v24 - 1), *((_DWORD *)v24 + 3));
      idAsyncServer::SendGameInitToClient(this, v23);
      v25 = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_pure");
      v26 = v25 ? v25->value->data : "0";
      if ( atoi(v26) )
        *v24 = SCS_PUREWAIT;
    }
    ++v23;
    v24 += 16450;
  }
  while ( v23 < 32 );
  v27 = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_pure");
  if ( v27 )
    v28 = v27->value->data;
  else
    v28 = "0";
  if ( !atoi(v28) || fileSystem->UpdateGamePakChecksums(fileSystem) )
  {
    idSessionLocal::ExecuteMapChange(&sessLocal, (int)this, (int)v24, v23, 0, 0, 0, v48);
    if ( this->localClientNum < 0 )
    {
      game->SetLocalClient(game, -1);
    }
    else
    {
      game->SetLocalClient(game, this->localClientNum);
      game->SetUserInfo(game, this->localClientNum, &sessLocal.mapSpawnData.userInfo[this->localClientNum], 0);
      game->ServerClientBegin(game, this->localClientNum);
      v32 = game->__vftable;
      LOBYTE(v33) = rvServerScan::IsAFriend(&idAsyncNetwork::client.serverList, this->localClientNum);
      v32->SetFriend(game, this->localClientNum, v33);
    }
    v34 = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_pure");
    if ( v34 )
      v35 = v34->value->data;
    else
      v35 = "0";
    if ( atoi(v35) )
    {
      fileSystem->UpdatePureServerChecksums(fileSystem);
      v36 = 0;
      v37 = &this->clients[0].clientState;
      do
      {
        if ( *v37 == SCS_PUREWAIT && !idAsyncServer::SendReliablePureToClient(this, v36) )
          *v37 = SCS_CONNECTED;
        ++v36;
        v37 += 16450;
      }
      while ( v36 < 32 );
    }
    v38 = &this->clients[0].clientState;
    v39 = 0;
    userInfo = sessLocal.mapSpawnData.userInfo;
    v49 = &this->clients[0].clientState;
    p_y = &this->fakeInfo[0].lastOrigin.y;
    do
    {
      if ( *v38 == SCS_CONNECTED )
      {
        v51 = (idMsgChannel *)(v38 + 11);
        v53 = *((_DWORD *)v38 + 11);
        v42 = *((_DWORD *)v38 + 12);
        v55 = *((_DWORD *)v38 + 13);
        v54 = v42;
        if ( v53 == 4 )
        {
          serverId = this->serverId;
          v45.type = NA_FAKE;
          *(_QWORD *)v45.ip = 0i64;
          v57 = 0;
          idMsgChannel::Init(v51, v45, serverId);
          *v49 = SCS_INGAME;
          v43 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 512);
          idDict::operator=(userInfo, v43);
          v44 = va("FAKE%d", v39);
          idDict::Set(userInfo, "ui_name", v44);
          *((_DWORD *)p_y - 6) = 100;
          *((_DWORD *)p_y - 7) = 100;
          *((_DWORD *)p_y - 5) = 100;
          *(p_y - 3) = 0.0;
          *(p_y - 2) = 0.0;
          p_y[1] = 0.0;
          *p_y = 0.0;
          *(p_y - 1) = 0.0;
          game->SetUserInfo(game, v39, userInfo, 0);
          game->ServerClientBegin(game, v39);
          idAsyncServer::SendUserInfoBroadcast(this, v39, userInfo, 1);
          v38 = v49;
        }
      }
      v38 += 16450;
      ++userInfo;
      ++v39;
      p_y += 11;
      v49 = v38;
    }
    while ( (int)userInfo < (int)sessLocal.mapSpawnData.mapLastUIRequestTime );
    soundSystem->SetActiveSoundWorld(soundSystem, 1);
  }
  else
  {
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "disconnect\n");
    v29 = session->__vftable;
    v30 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type
                                                                                              + 168))(
            common.type,
            "#str_104338",
            -1,
            1,
            0,
            0,
            0);
    v31 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_104337",
            -1,
            v30);
    ((void (__thiscall *)(idSession *, _DWORD, int))v29->MessageBoxA)(session, 0, v31);
  }
LABEL_70:
  v59 = -1;
  idStr::FreeData(&string);
}

// FUNC: private: void __thiscall idAsyncServer::ProcessUnreliableClientMessage(int,class idBitMsg const &)
void __thiscall idAsyncServer::ProcessUnreliableClientMessage(idAsyncServer *this, int clientNum, idBitMsg *msg)
{
  idAsyncServer *v3; // ebp
  serverClient_s *v4; // edi
  idBitMsg *v5; // esi
  int Bits; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int v9; // eax
  serverClientState_t clientState; // ecx
  int v11; // eax
  idDict *userInfo; // esi
  idGame_vtbl *v13; // esi
  BOOL v14; // eax
  unsigned __int8 v15; // al
  int v16; // ecx
  int v17; // eax
  unsigned __int8 v18; // al
  int v19; // esi
  bool *v20; // ebp
  int *p_clientState; // [esp+14h] [ebp-14h]
  unsigned __int8 v22; // [esp+14h] [ebp-14h]
  int clientGameFrame; // [esp+18h] [ebp-10h]
  usercmd_t *last; // [esp+1Ch] [ebp-Ch]
  usercmd_t *lasta; // [esp+1Ch] [ebp-Ch]
  usercmd_t *lastb; // [esp+1Ch] [ebp-Ch]
  int clientGameInitId; // [esp+24h] [ebp-4h]

  v3 = this;
  v4 = &this->clients[clientNum];
  if ( this->clients[clientNum].clientState != SCS_ZOMBIE )
  {
    v5 = msg;
    last = (usercmd_t *)idBitMsg::ReadBits(msg, 32);
    Bits = idBitMsg::ReadBits(msg, 32);
    clientGameInitId = Bits;
    if ( Bits == -2 )
    {
      if ( idAsyncNetwork::verbose.internalVar->integerValue )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "ignore unreliable msg from client %d, gameInitId == ID_MAP_LOAD\n",
          clientNum);
    }
    else if ( Bits == v3->gameInitId )
    {
      v9 = idBitMsg::ReadBits(msg, 32);
      clientState = v4->clientState;
      v4->acknowledgeSnapshotSequence = v9;
      if ( clientState == SCS_CONNECTED )
      {
        v11 = 0;
        v4->clientState = SCS_INGAME;
        lasta = 0;
        userInfo = sessLocal.mapSpawnData.userInfo;
        p_clientState = (int *)&v3->clients[0].clientState;
        do
        {
          if ( *p_clientState >= 3 && v11 != clientNum )
          {
            idAsyncServer::SendUserInfoToClient(v3, clientNum, v11, userInfo);
            v11 = (int)lasta;
          }
          p_clientState += 16450;
          ++v11;
          ++userInfo;
          lasta = (usercmd_t *)v11;
        }
        while ( (int)userInfo < (int)sessLocal.mapSpawnData.mapLastUIRequestTime );
        idAsyncServer::SendSyncedCvarsToClient(v3, clientNum, &sessLocal.mapSpawnData.syncedCVars);
        idAsyncServer::SendEnterGameToClient(v3, clientNum);
        game->ServerClientBegin(game, clientNum);
        game->ServerWriteInitialReliableMessages(game, clientNum);
        idAsyncServer::SendGUIDsToClient(v3, clientNum);
        if ( !cvarSystem->GetCVarInteger(cvarSystem, "net_serverDedicated") )
        {
          v13 = game->__vftable;
          LOBYTE(v14) = rvServerScan::IsAFriend(&idAsyncNetwork::client.serverList, clientNum);
          v13->SetFriend(game, clientNum, v14);
        }
        v5 = msg;
      }
      else if ( clientState == SCS_INGAME && game->ServerApplySnapshot(game, clientNum, v9) )
      {
        idAsyncServer::SendApplySnapshotToClient(v3, clientNum, v4->acknowledgeSnapshotSequence);
      }
      v15 = idBitMsg::ReadBits(v5, 8);
      v16 = v15;
      if ( v15 )
      {
        v17 = v15 - 1;
        if ( v17 )
        {
          if ( v17 == 1 )
          {
            if ( v4->clientState != SCS_PUREWAIT )
            {
              v4->clientPrediction = (__int16)idBitMsg::ReadBits(v5, -16);
              clientGameFrame = idBitMsg::ReadBits(v5, 32);
              lastb = 0;
              v18 = idBitMsg::ReadBits(v5, 8);
              v19 = clientGameFrame - v18 + 1;
              if ( v19 <= clientGameFrame )
              {
                v22 = clientGameFrame - v18;
                while ( 1 )
                {
                  v20 = &v3->active + 1280 * (unsigned __int8)v19 + 40 * clientNum;
                  idAsyncNetwork::ReadUserCmdDelta(msg, (usercmd_t *)(v20 + 2199872), lastb);
                  *((_DWORD *)v20 + 549971) = 0;
                  *((_DWORD *)v20 + 549968) = v19;
                  if ( idAsyncNetwork::UsercmdInputChanged(
                         &this->userCmds[v22][clientNum],
                         (const usercmd_t *)(v20 + 2199872)) )
                  {
                    v4->lastInputTime = this->serverTime;
                  }
                  ++v22;
                  ++v19;
                  lastb = (usercmd_t *)(v20 + 2199872);
                  if ( v19 > clientGameFrame )
                    break;
                  v3 = this;
                }
                if ( v20 != (bool *)-2199872 )
                {
                  v4->gameFrame = *((_DWORD *)v20 + 549968);
                  v4->gameTime = *((_DWORD *)v20 + 549969);
                }
              }
              if ( idAsyncNetwork::verbose.internalVar->integerValue == 2 )
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "received user command for client %d, gameInitId = %d, gameFrame, %d gameTime %d\n",
                  clientNum,
                  clientGameInitId,
                  v4->gameFrame,
                  v4->gameTime);
            }
          }
          else
          {
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "unknown unreliable message %d from client %d\n",
              v16,
              clientNum);
          }
        }
        else
        {
          v4->clientPing = v3->realTime - idBitMsg::ReadBits(v5, 32);
        }
      }
      else if ( idAsyncNetwork::verbose.internalVar->integerValue )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 124))(
          common.type,
          "received empty message for client %d\n",
          clientNum);
      }
    }
    else if ( (int)last <= v4->gameInitSequence )
    {
      if ( idAsyncNetwork::verbose.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 124))(
          common.type,
          "ignore unreliable msg from client %d, wrong gameInit, old sequence\n",
          clientNum);
    }
    else
    {
      v4->clientState = SCS_CONNECTED;
      idAsyncServer::SendGameInitToClient(v3, clientNum);
      Key = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_pure");
      if ( Key )
        data = Key->value->data;
      else
        data = "0";
      if ( atoi(data) )
      {
        v4->clientState = SCS_PUREWAIT;
        if ( !idAsyncServer::SendReliablePureToClient(v3, clientNum) )
          v4->clientState = SCS_CONNECTED;
      }
    }
  }
}

// FUNC: private: void __thiscall idAsyncServer::ProcessReliableClientMessages(int)
void __thiscall idAsyncServer::ProcessReliableClientMessages(idAsyncServer *this, int clientNum)
{
  bool *v3; // edi
  idKeyValue *list; // edi
  int v5; // edx
  int v6; // eax
  int i; // eax
  int v8; // edi
  int v9; // eax
  unsigned __int8 v10; // al
  bool *v11; // [esp+10h] [ebp-4460h]
  idDict dict; // [esp+14h] [ebp-445Ch] BYREF
  idBitMsg msg; // [esp+40h] [ebp-4430h] BYREF
  char buffer[1024]; // [esp+64h] [ebp-440Ch] BYREF
  char v15[16384]; // [esp+464h] [ebp-400Ch] BYREF
  int v16; // [esp+446Ch] [ebp-4h]

  idBitMsg::idBitMsg(&msg);
  v3 = &this->active + 65800 * clientNum;
  msg.writeData = (unsigned __int8 *)v15;
  v11 = v3;
  msg.readData = (const unsigned __int8 *)v15;
  msg.maxSize = 0x4000;
  msg.numValueOverflows = 0;
  while ( idMsgChannel::GetReliableMessage((idMsgChannel *)(v3 + 94324), &msg) )
  {
    switch ( (unsigned __int8)idBitMsg::ReadBits(&msg, 8) )
    {
      case 0u:
        idAsyncServer::ProcessReliablePure(this, clientNum, &msg);
        break;
      case 1u:
        dict.args.granularity = 16;
        dict.args.list = 0;
        dict.args.num = 0;
        dict.args.size = 0;
        v16 = 0;
        idHashIndex::Init(&dict.argHash, 1024, 1024);
        dict.args.granularity = 16;
        list = dict.args.list;
        LOBYTE(v16) = 1;
        if ( dict.args.list )
        {
          v5 = (dict.args.num + 15) % 16;
          v6 = dict.args.num + 15 - v5;
          if ( v6 != dict.args.size )
          {
            if ( v6 > 0 )
            {
              dict.args.size = dict.args.num + 15 - v5;
              if ( v6 < dict.args.num )
                dict.args.num = dict.args.num + 15 - v5;
              dict.args.list = (idKeyValue *)Memory::Allocate(8 * v6);
              for ( i = 0; i < dict.args.num; ++i )
              {
                dict.args.list[i].key = list[i].key;
                dict.args.list[i].value = list[i].value;
              }
              if ( list )
                Memory::Free(list);
            }
            else
            {
              Memory::Free(dict.args.list);
              dict.args.list = 0;
              dict.args.num = 0;
              dict.args.size = 0;
            }
          }
        }
        dict.argHash.granularity = 16;
        idHashIndex::Free(&dict.argHash);
        dict.argHash.hashSize = 128;
        dict.argHash.indexSize = 16;
        v16 = 2;
        v8 = idBitMsg::ReadBits(&msg, 32);
        idBitMsg::ReadDeltaDict(&msg, &dict, &sessLocal.mapSpawnData.userInfo[clientNum]);
        v9 = *((_DWORD *)v11 + 40017);
        if ( v8 == v9 )
        {
          *((_DWORD *)v11 + 40017) = v9 + 1;
          idAsyncServer::SendUserInfoBroadcast(this, clientNum, &dict, 0);
        }
        v16 = 4;
        idDict::Clear(&dict);
        LOBYTE(v16) = 3;
        idHashIndex::Free(&dict.argHash);
        v16 = -1;
        if ( dict.args.list )
          Memory::Free(dict.args.list);
        v3 = &this->active + 65800 * clientNum;
        dict.args.list = 0;
        dict.args.num = 0;
        dict.args.size = 0;
        break;
      case 2u:
        idBitMsg::ReadString(&msg, buffer, 1024);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s\n", buffer);
        break;
      case 3u:
        idAsyncServer::DropClient(this, (int)v3, clientNum, "#str_107138");
        break;
      case 7u:
        v10 = idBitMsg::ReadBits(&msg, 8);
        idAsyncServer::SendUserInfoToClient(this, clientNum, v10, &sessLocal.mapSpawnData.userInfo[v10]);
        break;
      default:
        game->ServerProcessReliableMessage(game, clientNum, &msg);
        break;
    }
  }
}

// FUNC: private: void __thiscall idAsyncServer::ProcessAuthMessage(class idBitMsg const &)
void __thiscall idAsyncServer::ProcessAuthMessage(idAsyncServer *this, idBitMsg *msg)
{
  int v2; // edi
  unsigned __int8 Bits; // al
  int v5; // ebx
  unsigned __int8 v6; // al
  int *p_clientId; // eax
  bool *v8; // esi
  int v9; // edi
  const char *v10; // eax
  int v11; // edi
  const char *v12; // eax
  const char *v13; // eax
  int v14; // esi
  const char *v15; // eax
  int v16; // edi
  const char *v17; // eax
  int v18; // esi
  const char *v19; // eax
  authReplyMsg_t v20; // edi
  char *data; // eax
  int v22; // eax
  int v23; // ebp
  const char *v24; // eax
  int len; // eax
  unsigned int v26; // ebx
  int v27; // eax
  netadr_t v28; // [esp-Ch] [ebp-468h]
  const char *v29; // [esp-8h] [ebp-464h]
  const char *v30; // [esp-4h] [ebp-460h]
  int v31; // [esp-4h] [ebp-460h]
  int v32; // [esp-4h] [ebp-460h]
  netadr_t client_from; // [esp+10h] [ebp-44Ch] BYREF
  int clientId; // [esp+1Ch] [ebp-440h]
  authReplyMsg_t replyMsg; // [esp+20h] [ebp-43Ch]
  char client_guid[12]; // [esp+24h] [ebp-438h] BYREF
  idStr replyPrintMsg; // [esp+30h] [ebp-42Ch] BYREF
  char string[1024]; // [esp+50h] [ebp-40Ch] BYREF
  int v39; // [esp+458h] [ebp-4h]

  v2 = 0;
  replyMsg = AUTH_REPLY_WAITING;
  replyPrintMsg.len = 0;
  replyPrintMsg.alloced = 20;
  replyPrintMsg.data = replyPrintMsg.baseBuffer;
  replyPrintMsg.baseBuffer[0] = 0;
  v39 = 0;
  Bits = idBitMsg::ReadBits(msg, 8);
  v5 = Bits;
  if ( !Bits || Bits >= 4u )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "auth: invalid reply %d\n",
      Bits);
    goto LABEL_31;
  }
  clientId = (__int16)idBitMsg::ReadBits(msg, -16);
  idBitMsg::ReadNetadr(msg, &client_from);
  idBitMsg::ReadString(msg, client_guid, 12);
  if ( v5 != 1 )
  {
    v6 = idBitMsg::ReadBits(msg, 8);
    replyMsg = v6;
    if ( !v6 || v6 >= 5u )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
        common.type,
        "auth: invalid reply msg %d\n",
        v6);
      goto LABEL_31;
    }
    if ( v6 == 3 )
    {
      idBitMsg::ReadString(msg, string, 1024);
      idStr::operator=(&replyPrintMsg, string);
    }
  }
  this->lastAuthTime = this->serverTime;
  p_clientId = &this->challenges[0].clientId;
  while ( *((_BYTE *)p_clientId + 16) || *p_clientId != clientId )
  {
    ++v2;
    p_clientId += 23;
    if ( v2 >= 1024 )
    {
      v14 = *(_DWORD *)common.type;
      v15 = Sys_NetAdrToString(client_from);
      (*(void (**)(netadrtype_t, const char *, ...))(v14 + 132))(
        common.type,
        "auth: failed client lookup %s %s\n",
        v15,
        client_guid);
      goto LABEL_31;
    }
  }
  v8 = &this->active + 92 * v2;
  clientId = strlen((const char *)v8 + 140);
  if ( clientId )
  {
    if ( idStr::Cmp((const char *)v8 + 140, client_guid) )
    {
      v11 = *(_DWORD *)common.type;
      v12 = Sys_NetAdrToString(*(const netadr_t *)(v8 + 64));
      (*(void (**)(netadrtype_t, const char *, ...))(v11 + 132))(
        common.type,
        "auth: client %s %s not matched, auth server says guid %s\n",
        v12,
        v8 + 140,
        client_guid);
    }
    else
    {
      if ( !Sys_CompareNetAdrBase(client_from, *(const netadr_t *)(v8 + 64)) )
      {
        v28 = *(netadr_t *)(v8 + 64);
        clientId = *(_DWORD *)common.type;
        v30 = Sys_NetAdrToString(v28);
        v13 = Sys_NetAdrToString(client_from);
        (*(void (**)(netadrtype_t, const char *, ...))(clientId + 132))(
          common.type,
          "auth: matched guid '%s' for != IPs %s and %s\n",
          client_guid,
          v13,
          v30);
      }
      if ( *((_DWORD *)v8 + 24) )
      {
        v16 = *(_DWORD *)common.type;
        v31 = *((_DWORD *)v8 + 24);
        v17 = Sys_NetAdrToString(*(const netadr_t *)(v8 + 64));
        (*(void (**)(netadrtype_t, const char *, ...))(v16 + 140))(
          common.type,
          "auth: challenge 0x%x %s authState %d != CDK_WAIT",
          *((_DWORD *)v8 + 20),
          v17,
          v31);
      }
      else
      {
        idStr::snPrintf((char *)v8 + 140, 12, client_guid);
        if ( v5 == 1 )
        {
          *((_DWORD *)v8 + 24) = 1;
          v18 = *(_DWORD *)common.type;
          v19 = Sys_NetAdrToString(client_from);
          (*(void (**)(netadrtype_t, const char *, ...))(v18 + 124))(
            common.type,
            "client %s %s is authed\n",
            v19,
            client_guid);
        }
        else
        {
          v20 = replyMsg;
          if ( replyMsg == AUTH_REPLY_PRINT )
            data = replyPrintMsg.data;
          else
            data = (char *)authReplyMsg[replyMsg];
          v22 = (*(int (__thiscall **)(netadrtype_t, char *, int))(*(_DWORD *)common.type + 168))(common.type, data, -1);
          v23 = *(_DWORD *)common.type;
          v32 = v22;
          v29 = authReplyStr[v5];
          v24 = Sys_NetAdrToString(client_from);
          (*(void (**)(netadrtype_t, const char *, ...))(v23 + 132))(
            common.type,
            "auth: client %s %s - %s %s\n",
            v24,
            client_guid,
            v29,
            v32);
          len = replyPrintMsg.len;
          *((_DWORD *)v8 + 25) = v5;
          v26 = len;
          v27 = len + 1;
          *((_DWORD *)v8 + 26) = v20;
          if ( v27 > *((_DWORD *)v8 + 29) )
            idStr::ReAllocate((idStr *)(v8 + 108), v27, 0);
          qmemcpy(*((void **)v8 + 28), replyPrintMsg.data, v26);
          *(_BYTE *)(v26 + *((_DWORD *)v8 + 28)) = 0;
          *((_DWORD *)v8 + 27) = v26;
        }
      }
    }
  }
  else
  {
    v9 = *(_DWORD *)common.type;
    v10 = Sys_NetAdrToString(*(const netadr_t *)(v8 + 64));
    (*(void (**)(netadrtype_t, const char *, ...))(v9 + 132))(common.type, "auth: client %s has no guid yet\n", v10);
  }
LABEL_31:
  v39 = -1;
  idStr::FreeData(&replyPrintMsg);
}

// FUNC: private: int __thiscall idAsyncServer::ValidateChallenge(struct netadr_t,int,int)
int __thiscall idAsyncServer::ValidateChallenge(idAsyncServer *this, netadr_t from, int challenge, int clientId)
{
  int v4; // edi
  idMsgChannel *p_channel; // esi
  int v6; // edi
  unsigned __int16 *p_port; // esi
  int v9; // esi
  const char *v10; // eax

  v4 = 0;
  p_channel = &this->clients[0].channel;
  while ( !*(_DWORD *)&p_channel[-1].reliableReceive.buffer[16356]
       || !Sys_CompareNetAdrBase(from, p_channel->remoteAddress)
       || clientId != *(_DWORD *)&p_channel[-1].reliableReceive.buffer[16352]
       && from.port != p_channel->remoteAddress.port )
  {
    ++v4;
    p_channel = (idMsgChannel *)((char *)p_channel + 65800);
    if ( v4 >= 32 )
      goto LABEL_7;
  }
  if ( this->serverTime - p_channel[1].remoteAddress.type < 2000 )
  {
    v9 = *(_DWORD *)common.type;
    v10 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v9 + 124))(common.type, "%s: reconnect rejected : too soon\n", v10);
    return -1;
  }
LABEL_7:
  v6 = 0;
  p_port = &this->challenges[0].address.port;
  do
  {
    if ( Sys_CompareNetAdrBase(from, *(const netadr_t *)(p_port - 4))
      && from.port == *p_port
      && challenge == *((_DWORD *)p_port + 2) )
    {
      break;
    }
    ++v6;
    p_port += 46;
  }
  while ( v6 < 1024 );
  if ( v6 != 1024 )
    return v6;
  idAsyncServer::PrintOOB(this, from, 4, "#str_104840");
  return -1;
}

// FUNC: private: void __thiscall idAsyncServer::ProcessConnectMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncServer::ProcessConnectMessage(idAsyncServer *this, netadr_t from, idBitMsg *msg)
{
  idAsyncServer *v3; // edi
  int Bits; // esi
  char *v5; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edi
  const char *v12; // eax
  int v13; // eax
  int v14; // edi
  const char *v15; // eax
  int v16; // eax
  int *p_clientState; // edi
  int v18; // ecx
  idGame_vtbl *v19; // edi
  const char *v20; // eax
  int v21; // edi
  const char *v22; // eax
  const char *v23; // eax
  __int16 v24; // ax
  const char *v25; // eax
  int v26; // edi
  const char *v27; // eax
  const idKeyValue *v28; // eax
  const char *v29; // eax
  const idKeyValue *v30; // eax
  const char *v31; // eax
  int v32; // edi
  const char *v33; // eax
  int v34; // eax
  idMsgChannel *p_channel; // edi
  int v36; // edx
  bool v37; // zf
  bool *v38; // edi
  int v39; // edi
  const char *v40; // eax
  bool *v41; // edi
  int v42; // eax
  const char *v43; // edx
  int v44; // eax
  int v45; // edi
  const char *v46; // eax
  idAsyncServer *v47; // edi
  netadr_t v48; // [esp-10h] [ebp-85B4h]
  char *v49; // [esp+0h] [ebp-85A4h]
  int v50; // [esp+0h] [ebp-85A4h]
  int v51; // [esp+0h] [ebp-85A4h]
  int challenge; // [esp+14h] [ebp-8590h]
  int challengee; // [esp+14h] [ebp-8590h]
  int challengea; // [esp+14h] [ebp-8590h]
  const char *challengeb; // [esp+14h] [ebp-8590h]
  int challengec; // [esp+14h] [ebp-8590h]
  char *challenged; // [esp+14h] [ebp-8590h]
  int value; // [esp+1Ch] [ebp-8588h]
  int valuea; // [esp+1Ch] [ebp-8588h]
  bool *v61; // [esp+20h] [ebp-8584h]
  idBitMsg v62; // [esp+24h] [ebp-8580h] BYREF
  int OS; // [esp+48h] [ebp-855Ch]
  int clientId; // [esp+4Ch] [ebp-8558h]
  char buffer[12]; // [esp+50h] [ebp-8554h] BYREF
  int clientRate; // [esp+5Ch] [ebp-8548h]
  idBitMsg v67; // [esp+60h] [ebp-8544h] BYREF
  netadr_t result; // [esp+84h] [ebp-8520h] BYREF
  char v69[20]; // [esp+90h] [ebp-8514h] BYREF
  char Destination[253]; // [esp+A4h] [ebp-8500h] BYREF
  __int16 v71; // [esp+1A1h] [ebp-8403h]
  char v72; // [esp+1A3h] [ebp-8401h]
  char s[1024]; // [esp+1A4h] [ebp-8400h] BYREF
  char v74[16384]; // [esp+5A4h] [ebp-8000h] BYREF
  char v75[16384]; // [esp+45A4h] [ebp-4000h] BYREF

  v3 = this;
  idBitMsg::idBitMsg(&v62);
  Bits = idBitMsg::ReadBits(msg, 32);
  OS = (__int16)idBitMsg::ReadBits(msg, -16);
  if ( Bits != 131136 )
  {
    v5 = va("server uses protocol %d.%d\n", 2, 64);
    idAsyncServer::PrintOOB(v3, from, 1, v5);
  }
  value = idBitMsg::ReadBits(msg, 32);
  challenge = idBitMsg::ReadBits(msg, 32);
  clientId = (__int16)idBitMsg::ReadBits(msg, -16);
  clientRate = idBitMsg::ReadBits(msg, 32);
  Key = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_pure");
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  if ( !atoi(data) && value != v3->serverDataChecksum )
  {
    v49 = "#str_104842";
LABEL_49:
    idAsyncServer::PrintOOB(v3, from, 0, v49);
    return;
  }
  v8 = idAsyncServer::ValidateChallenge(v3, from, challenge, clientId);
  if ( v8 == -1 )
    return;
  v61 = &v3->active + 92 * v8;
  *((_DWORD *)v61 + 38) = OS;
  idBitMsg::ReadString(msg, buffer, 12);
  v9 = *((_DWORD *)v61 + 24);
  if ( v9 )
  {
    v10 = v9 - 2;
    if ( !v10 )
    {
      v11 = *(_DWORD *)common.type;
      v12 = Sys_NetAdrToString(from);
      (*(void (**)(netadrtype_t, const char *, ...))(v11 + 132))(common.type, "%s: not a lan client\n", v12);
      idAsyncServer::PrintOOB(this, from, 0, "#str_104843");
      return;
    }
    if ( v10 == 1 )
    {
      idAsyncServer::SendPureServerMessage(v3, from, OS);
      return;
    }
  }
  else
  {
    if ( *((_DWORD *)v61 + 25) )
      goto LABEL_72;
    v13 = v3->serverTime - v3->lastAuthTime;
    if ( v13 >= v3->serverTime - *((_DWORD *)v61 + 21) )
      v13 = v3->serverTime - *((_DWORD *)v61 + 21);
    if ( v13 <= 5000 )
    {
LABEL_72:
      v42 = *((_DWORD *)v61 + 26);
      if ( v42 == 3 )
        v43 = (const char *)*((_DWORD *)v61 + 28);
      else
        v43 = authReplyMsg[v42];
      challenged = (char *)v43;
      v44 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              v43,
              -1);
      v45 = *(_DWORD *)common.type;
      v51 = v44;
      v46 = Sys_NetAdrToString(from);
      (*(void (**)(netadrtype_t, const char *, ...))(v45 + 132))(common.type, "%s: %s\n", v46, v51);
      if ( *((_DWORD *)v61 + 26) > 1u )
      {
        v47 = this;
      }
      else
      {
        idBitMsg::idBitMsg(&v67);
        v67.writeData = (unsigned __int8 *)v75;
        v67.readData = (const unsigned __int8 *)v75;
        v67.maxSize = 0x4000;
        v67.numValueOverflows = 0;
        idBitMsg::WriteBits(&v67, -1, -16);
        idBitMsg::WriteString(&v67, "authrequired", -1);
        v47 = this;
        idPort::SendPacket(&this->serverPort, from, v67.writeData, v67.curSize);
      }
      idAsyncServer::PrintOOB(v47, from, 0, challenged);
      idStr::snPrintf((char *)v61 + 140, 12, buffer);
      if ( *((_DWORD *)v61 + 25) != 3 )
      {
        v62.readData = (const unsigned __int8 *)v74;
        v62.writeData = (unsigned __int8 *)v74;
        v62.maxSize = 0x4000;
        v62.numValueOverflows = 0;
        idBitMsg::WriteBits(&v62, -1, -16);
        idBitMsg::WriteString(&v62, "srvAuth", -1);
        idBitMsg::WriteBits(&v62, 131136, 32);
        idBitMsg::WriteNetadr(&v62, from);
        idBitMsg::WriteBits(&v62, clientId, 32);
        idBitMsg::WriteString(&v62, buffer, -1);
        v48 = *idAsyncNetwork::GetMasterAddress(&result);
        idPort::SendPacket(&v47->serverPort, v48, v62.writeData, v62.curSize);
      }
      return;
    }
    v14 = *(_DWORD *)common.type;
    v15 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v14 + 132))(common.type, "%s: Authorize server timed out\n", v15);
    v3 = this;
  }
  v16 = 0;
  p_clientState = (int *)&v3->clients[1].clientState;
  v18 = 8;
  do
  {
    if ( *(p_clientState - 16450) >= 2 )
      ++v16;
    if ( *p_clientState >= 2 )
      ++v16;
    if ( p_clientState[16450] >= 2 )
      ++v16;
    if ( p_clientState[32900] >= 2 )
      ++v16;
    p_clientState += 65800;
    --v18;
  }
  while ( v18 );
  challengee = v16;
  idBitMsg::ReadString(msg, v69, 17);
  v19 = game->__vftable;
  v20 = Sys_NetAdrToString(from);
  challengea = v19->ServerAllowClient(game, challengee, v20, buffer, v69, s);
  if ( challengea )
  {
    v21 = *(_DWORD *)common.type;
    v22 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v21 + 132))(common.type, "game denied connection for %s\n", v22);
    v62.writeData = (unsigned __int8 *)v74;
    v62.readData = (const unsigned __int8 *)v74;
    v62.maxSize = 0x4000;
    v62.numValueOverflows = 0;
    idBitMsg::WriteBits(&v62, -1, -16);
    idBitMsg::WriteString(&v62, "print", -1);
    idBitMsg::WriteBits(&v62, 3, 32);
    idBitMsg::WriteBits(&v62, challengea, 32);
    idBitMsg::WriteString(&v62, s, -1);
    idPort::SendPacket(&this->serverPort, from, v62.writeData, v62.curSize);
    return;
  }
  memset(Destination, 0, sizeof(Destination));
  v71 = 0;
  v72 = 0;
  v23 = Sys_NetAdrToString(from);
  strncpy(Destination, v23, 0x100u);
  v24 = idBitMsg::ReadBits(msg, -16);
  v25 = PbAuthClient(Destination, v24, buffer);
  challengeb = v25;
  if ( v25 )
  {
    if ( strstr(v25, "must be Enabled") )
      challengeb = "#str_107237";
    v26 = *(_DWORD *)common.type;
    v27 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v26 + 132))(
      common.type,
      "game denied connection for %s; pb not enabled on client\n",
      v27);
    v62.writeData = (unsigned __int8 *)v74;
    v62.readData = (const unsigned __int8 *)v74;
    v62.maxSize = 0x4000;
    v62.numValueOverflows = 0;
    idBitMsg::WriteBits(&v62, -1, -16);
    idBitMsg::WriteString(&v62, "print", -1);
    idBitMsg::WriteBits(&v62, 3, 32);
    idBitMsg::WriteBits(&v62, 3, 32);
    idBitMsg::WriteString(&v62, challengeb, -1);
    idPort::SendPacket(&this->serverPort, from, v62.writeData, v62.curSize);
    return;
  }
  v28 = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_pure");
  if ( v28 )
    v29 = v28->value->data;
  else
    v29 = "0";
  v3 = this;
  if ( atoi(v29) && *((_DWORD *)v61 + 24) != 4 && idAsyncServer::SendPureServerMessage(this, from, OS) )
  {
    *((_DWORD *)v61 + 24) = 3;
    return;
  }
  v30 = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_pure");
  if ( v30 )
    v31 = v30->value->data;
  else
    v31 = "0";
  if ( atoi(v31) && value != this->serverDataChecksum )
  {
    v49 = "#str_104844";
    goto LABEL_49;
  }
  v32 = *(_DWORD *)common.type;
  v50 = this->serverTime - *((_DWORD *)v61 + 22);
  v33 = Sys_NetAdrToString(from);
  (*(void (**)(netadrtype_t, const char *, ...))(v32 + 124))(
    common.type,
    "challenge from %s connecting with %d ping\n",
    v33,
    v50);
  v34 = 0;
  v61[92] = 1;
  challengec = 0;
  while ( 2 )
  {
    valuea = 0;
    p_channel = &this->clients[0].channel;
    while ( 1 )
    {
      if ( !v34 )
      {
        if ( !Sys_CompareNetAdrBase(from, p_channel->remoteAddress) )
          goto LABEL_66;
        if ( clientId == *(_DWORD *)&p_channel[-1].reliableReceive.buffer[16352] )
          goto LABEL_68;
        v36 = *(_DWORD *)p_channel->remoteAddress.ip;
        v37 = from.port == p_channel->remoteAddress.port;
        result.type = p_channel->remoteAddress.type;
        *(_DWORD *)result.ip = v36;
LABEL_65:
        if ( v37 )
          goto LABEL_68;
        goto LABEL_66;
      }
      if ( v34 != 1 )
      {
        if ( v34 != 2 )
          goto LABEL_66;
        v37 = *(_DWORD *)&p_channel[-1].reliableReceive.buffer[16356] == 0;
        goto LABEL_65;
      }
      if ( *(int *)&p_channel[-1].reliableReceive.buffer[16356] < 2
        && Sys_CompareNetAdrBase(from, p_channel->remoteAddress) )
      {
LABEL_68:
        v38 = &this->active + 65800 * valuea;
        idMsgChannel::Init((idMsgChannel *)(v38 + 94324), from, this->serverId);
        *((_DWORD *)v38 + 23568) = OS;
        strncpy((char *)v38 + 160056, buffer, 0xCu);
        v38[160067] = 0;
        goto LABEL_69;
      }
LABEL_66:
      p_channel = (idMsgChannel *)((char *)p_channel + 65800);
      if ( ++valuea >= 32 )
        break;
      v34 = challengec;
    }
    v34 = ++challengec;
    if ( challengec < 3 )
      continue;
    break;
  }
LABEL_69:
  if ( valuea < 32 )
  {
    v39 = *(_DWORD *)common.type;
    v40 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v39 + 124))(common.type, "sending connect response to %s\n", v40);
    v62.readData = (const unsigned __int8 *)v74;
    v62.writeData = (unsigned __int8 *)v74;
    v62.maxSize = 0x4000;
    v62.numValueOverflows = 0;
    idBitMsg::WriteBits(&v62, -1, -16);
    idBitMsg::WriteString(&v62, "connectResponse", -1);
    idBitMsg::WriteBits(&v62, valuea, 32);
    idBitMsg::WriteBits(&v62, this->gameInitId, 32);
    idBitMsg::WriteBits(&v62, this->gameFrame, 32);
    idBitMsg::WriteBits(&v62, this->gameTime, 32);
    idBitMsg::WriteDeltaDict(&v62, &sessLocal.mapSpawnData.serverInfo, 0);
    idPort::SendPacket(&this->serverPort, from, v62.writeData, v62.curSize);
    idAsyncServer::InitClient(this, valuea, clientId, clientRate);
    v41 = &this->active + 65800 * valuea;
    *((_DWORD *)v41 + 23578) = 1;
    *((_DWORD *)v41 + 40011) = 1;
    *(netadr_t *)(v41 + 94300) = from;
    memset(v61 + 64, 0, 0x5Cu);
  }
  else
  {
    idAsyncServer::PrintOOB(this, from, 0, "#str_104845");
  }
}

// FUNC: private: void __thiscall idAsyncServer::ProcessPureMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncServer::ProcessPureMessage(idAsyncServer *this, netadr_t from, idBitMsg *msg)
{
  idBitMsg *v4; // edi
  int Bits; // ebx
  __int16 v6; // ax
  netadrtype_t type; // ebp
  unsigned int v8; // ebx
  int v9; // eax
  bool v10; // zf
  int v11; // esi
  const char *v12; // eax
  int v13; // esi
  const char *v14; // eax
  netadr_t v15; // [esp-14h] [ebp-50h]
  netadr_t v16; // [esp-Ch] [ebp-48h]
  netadr_t v17; // [esp-Ch] [ebp-48h]
  int v18; // [esp-8h] [ebp-44h]
  idStr reply; // [esp+10h] [ebp-2Ch] BYREF
  int v20; // [esp+38h] [ebp-4h]

  reply.len = 0;
  reply.alloced = 20;
  reply.data = reply.baseBuffer;
  reply.baseBuffer[0] = 0;
  v4 = msg;
  v20 = 0;
  Bits = idBitMsg::ReadBits(msg, 32);
  v6 = idBitMsg::ReadBits(v4, -16);
  type = from.type;
  v18 = Bits;
  v8 = *(_DWORD *)from.ip;
  v9 = idAsyncServer::ValidateChallenge(this, from, v18, v6);
  if ( v9 != -1 )
  {
    v10 = this->challenges[v9].authState == CDK_PUREWAIT;
    msg = (idBitMsg *)((char *)this + 92 * v9);
    if ( v10 )
    {
      if ( idAsyncServer::VerifyChecksumMessage(this, v9, &from, v4, &reply, this->challenges[v9].OS) )
      {
        v13 = *(_DWORD *)common.type;
        v17.type = type;
        *(_QWORD *)v17.ip = __PAIR64__(*(unsigned int *)&from.port, v8);
        v14 = Sys_NetAdrToString(v17);
        (*(void (**)(netadrtype_t, const char *, ...))(v13 + 132))(common.type, "client %s: passed pure checks\n", v14);
        msg[2].readBit = 4;
      }
      else
      {
        v15.type = type;
        *(_QWORD *)v15.ip = __PAIR64__(*(unsigned int *)&from.port, v8);
        idAsyncServer::PrintOOB(this, v15, 0, reply.data);
      }
    }
    else
    {
      v11 = *(_DWORD *)common.type;
      v16.type = type;
      *(_QWORD *)v16.ip = __PAIR64__(*(unsigned int *)&from.port, v8);
      v12 = Sys_NetAdrToString(v16);
      (*(void (**)(netadrtype_t, const char *, ...))(v11 + 132))(
        common.type,
        "client %s: got pure message, not in CDK_PUREWAIT\n",
        v12);
    }
  }
  v20 = -1;
  idStr::FreeData(&reply);
}

// FUNC: void __cdecl RConRedirect(char const *)
void __cdecl RConRedirect(char *string)
{
  idAsyncNetwork::server.noRconOutput = 0;
  idAsyncServer::PrintOOB(&idAsyncNetwork::server, idAsyncNetwork::server.rconAddress, 2, string);
}

// FUNC: private: void __thiscall idAsyncServer::ProcessRemoteConsoleMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncServer::ProcessRemoteConsoleMessage(idAsyncServer *this, const netadr_t from, idBitMsg *msg)
{
  int v4; // edi
  const char *v5; // eax
  char *v6; // [esp-4h] [ebp-4438h]
  idBitMsg v7; // [esp+10h] [ebp-4424h] BYREF
  char buffer[1024]; // [esp+34h] [ebp-4400h] BYREF
  char v9[16384]; // [esp+434h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v7);
  if ( !*idAsyncNetwork::serverRemoteConsolePassword.internalVar->value )
  {
    v6 = "#str_104846";
LABEL_7:
    idAsyncServer::PrintOOB(this, from, 2, v6);
    return;
  }
  idBitMsg::ReadString(msg, buffer, 1024);
  if ( idStr::Icmp(buffer, idAsyncNetwork::serverRemoteConsolePassword.internalVar->value) )
  {
    idAsyncServer::PrintOOB(this, from, 2, "#str_104847");
    return;
  }
  idBitMsg::ReadString(msg, buffer, 1024);
  if ( !idStr::Icmp(buffer, "verifyRconPass") )
  {
    v6 = "#str_107250";
    goto LABEL_7;
  }
  v4 = *(_DWORD *)common.type;
  v5 = Sys_NetAdrToString(from);
  (*(void (**)(netadrtype_t, const char *, ...))(v4 + 124))(common.type, "rcon from %s: %s\n", v5, buffer);
  this->rconAddress = from;
  this->noRconOutput = 1;
  (*(void (__thiscall **)(netadrtype_t, char *, int, void (__cdecl *)(const char *)))(*(_DWORD *)common.type + 112))(
    common.type,
    v9,
    0x4000,
    RConRedirect);
  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, buffer);
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 116))(common.type);
  if ( this->noRconOutput )
    idAsyncServer::PrintOOB(this, this->rconAddress, 2, "#str_104848");
}

// FUNC: private: void __thiscall idAsyncServer::ProcessGetInfoMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncServer::ProcessGetInfoMessage(idAsyncServer *this, netadr_t from, idBitMsg *msg)
{
  int v4; // ebp
  const char *v5; // eax
  int Bits; // eax
  int v7; // ebp
  idBitMsg msga; // [esp+10h] [ebp-4024h] BYREF
  char v9[16384]; // [esp+34h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msga);
  if ( this->active )
  {
    v4 = *(_DWORD *)common.type;
    v5 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v4 + 132))(common.type, "Sending info response to %s\n", v5);
    Bits = idBitMsg::ReadBits(msg, 32);
    msga.writeData = (unsigned __int8 *)v9;
    v7 = Bits;
    msga.readData = (const unsigned __int8 *)v9;
    msga.maxSize = 0x4000;
    msga.numValueOverflows = 0;
    idBitMsg::WriteBits(&msga, -1, -16);
    idBitMsg::WriteString(&msga, "infoResponse", -1);
    idBitMsg::WriteBits(&msga, v7, 32);
    idAsyncServer::WriteInfo(this, &msga);
    idPort::SendPacket(&this->serverPort, from, msga.writeData, msga.curSize);
  }
}

// FUNC: public: __thiscall idAsyncServer::idAsyncServer(void)
void __thiscall idAsyncServer::idAsyncServer(idAsyncServer *this)
{
  int i; // edi

  idPort::idPort(&this->serverPort);
  `eh vector constructor iterator'(
    this->challenges,
    0x5Cu,
    1024,
    (void (__thiscall *)(void *))challenge_s::challenge_s,
    (void (__thiscall *)(void *))challenge_s::~challenge_s);
  `eh vector constructor iterator'(
    this->clients,
    0x10108u,
    32,
    (void (__thiscall *)(void *))serverClient_s::serverClient_s,
    (void (__thiscall *)(void *))SpawnStub);
  this->active = 0;
  this->realTime = 0;
  this->serverTime = 0;
  this->serverId = 0;
  this->serverDataChecksum = 0;
  this->localClientNum = -1;
  this->gameInitId = 0;
  this->gameFrame = 0;
  this->gameTime = 0;
  this->gameTimeResidual = 0;
  memset(this->challenges, 0, sizeof(this->challenges));
  memset(this->userCmds, 0, sizeof(this->userCmds));
  for ( i = 0; i < 32; ++i )
    idAsyncServer::ClearClient(this, i);
  this->serverReloadingEngine = 0;
  this->nextHeartbeatTime = 0;
  this->nextAsyncStatsTime = 0;
  this->lastAuthTime = 0;
  this->noRconOutput = 1;
  memset(this->stats_outrate, 0, sizeof(this->stats_outrate));
  this->stats_current = 0;
  this->stats_average_sum = 0;
  this->stats_max = 0;
  this->stats_max_index = 0;
}

// FUNC: public: void __thiscall idAsyncServer::Spawn(void)
void __usercall idAsyncServer::Spawn(idAsyncServer *this@<ecx>, int a2@<edi>)
{
  int i; // edi
  idCVar *internalVar; // eax
  __int32 *Interface; // eax
  __int32 v6; // ecx
  __int32 v7; // edx
  __int32 v8; // eax
  int size; // [esp+4h] [ebp-401Ch] BYREF
  netadr_t from; // [esp+8h] [ebp-4018h] BYREF
  netadr_t result; // [esp+14h] [ebp-400Ch] BYREF
  char data[16384]; // [esp+20h] [ebp-4000h] BYREF

  session->Stop(session);
  if ( !this->active && idAsyncServer::InitPort(this) )
  {
    while ( idPort::GetPacket(&this->serverPort, &from, data, &size, 0x4000) )
      ;
    if ( !idAsyncNetwork::allowCheats.internalVar->integerValue )
      cvarSystem->ResetFlaggedVariables(cvarSystem, 0x2000);
    memset(this->challenges, 0, sizeof(this->challenges));
    memset(this->userCmds, 0, sizeof(this->userCmds));
    for ( i = 0; i < 32; ++i )
      idAsyncServer::ClearClient(this, i);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Server spawned on port %i.\n",
      this->serverPort.port);
    if ( ((unsigned __int8 (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->GetCVarBool)(
           cvarSystem,
           "sv_punkbuster",
           a2) )
    {
      if ( !idAsyncNetwork::serverDedicated.internalVar->integerValue )
        EnablePbCl();
    }
    internalVar = idAsyncNetwork::LANServer.internalVar;
    LOBYTE(internalVar) = idAsyncNetwork::LANServer.internalVar->integerValue != 0;
    ((void (__stdcall *)(const char *, idCVar *))cvarSystem->SetCVarBool)("pb_sv_lan", internalVar);
    this->serverDataChecksum = declManager->GetChecksum(declManager);
    this->serverId = Sys_Milliseconds() & 0x7FFF;
    this->active = 1;
    this->nextHeartbeatTime = 0;
    this->nextAsyncStatsTime = 0;
    Interface = (__int32 *)Net_GetInterface(&result, 0);
    v6 = *Interface;
    v7 = Interface[1];
    v8 = Interface[2];
    this->serverAddress.type = v6;
    LOWORD(v6) = this->serverPort.port;
    *(_DWORD *)this->serverAddress.ip = v7;
    *(_DWORD *)&this->serverAddress.port = v8;
    this->serverAddress.port = v6;
    idAsyncServer::ExecuteMapChange(this);
    this->nextHeartbeatTime = 0;
  }
}

// FUNC: private: void __thiscall idAsyncServer::ProcessDownloadRequestMessage(struct netadr_t,class idBitMsg const &)
void __thiscall idAsyncServer::ProcessDownloadRequestMessage(idAsyncServer *this, const netadr_t from, idBitMsg *msg)
{
  int Bits; // esi
  int v5; // ebx
  int v6; // eax
  int v7; // edi
  const char *v8; // eax
  int v9; // esi
  int v10; // kr00_4
  char *data; // edx
  char *v12; // ecx
  char v13; // al
  _DWORD *v14; // eax
  idStr *v15; // ebx
  int len; // ebp
  bool v17; // cc
  int i; // esi
  int v19; // eax
  int v20; // kr04_4
  char *v21; // edx
  char *v22; // ecx
  char v23; // al
  int v24; // edi
  _DWORD *v25; // eax
  idStr *v26; // esi
  idStr *v27; // eax
  char **p_data; // ebp
  unsigned int v29; // ebx
  int v30; // edx
  int v31; // ecx
  int v32; // esi
  int v33; // ebx
  int *v34; // eax
  idStr *v35; // edi
  idStr *v36; // eax
  char **v37; // ebp
  unsigned int v38; // ebx
  int v39; // eax
  idStr *v40; // ebx
  int v41; // ebp
  int v42; // ebx
  int v43; // esi
  int v44; // eax
  char v45; // cl
  char *v46; // edx
  const char *v47; // esi
  unsigned int v48; // eax
  int v49; // edi
  int v50; // eax
  char v51; // cl
  int j; // eax
  char *v53; // edx
  idGame_vtbl *v54; // ebp
  const char *v55; // eax
  idStr *v56; // eax
  bool v57; // zf
  char *v58; // esi
  int v59; // ebx
  char *v60; // edi
  unsigned int v61; // eax
  int v62; // edi
  int v63; // eax
  char *v64; // ecx
  char v65; // al
  int v66; // edi
  _DWORD *v67; // eax
  idStr *v68; // esi
  idStr *v69; // eax
  char **v70; // ebp
  unsigned int v71; // ebx
  int v72; // edx
  int v73; // ecx
  int v74; // esi
  int v75; // ebx
  int *v76; // eax
  idStr *v77; // edi
  idStr *v78; // eax
  char **v79; // ebp
  unsigned int v80; // ebx
  int v81; // eax
  idStr *v82; // ebx
  int v83; // ebp
  int v84; // ebx
  const char **v85; // esi
  int v86; // edi
  char *v87; // esi
  char *v88; // [esp+10h] [ebp-86F0h]
  int v89; // [esp+28h] [ebp-86D8h]
  unsigned int *v90; // [esp+28h] [ebp-86D8h]
  const char **v91; // [esp+28h] [ebp-86D8h]
  char *v92; // [esp+28h] [ebp-86D8h]
  unsigned int *v93; // [esp+28h] [ebp-86D8h]
  idStr *v94; // [esp+28h] [ebp-86D8h]
  char *v95; // [esp+2Ch] [ebp-86D4h]
  unsigned int *v96; // [esp+2Ch] [ebp-86D4h]
  unsigned int *v97; // [esp+2Ch] [ebp-86D4h]
  char *v98; // [esp+2Ch] [ebp-86D4h]
  int v99; // [esp+30h] [ebp-86D0h]
  int v100; // [esp+30h] [ebp-86D0h]
  int v101; // [esp+30h] [ebp-86D0h]
  int v102; // [esp+34h] [ebp-86CCh]
  int v103; // [esp+34h] [ebp-86CCh]
  int v104; // [esp+34h] [ebp-86CCh]
  int v105; // [esp+34h] [ebp-86CCh]
  int v106; // [esp+38h] [ebp-86C8h]
  int v107; // [esp+3Ch] [ebp-86C4h]
  idStr *ptr; // [esp+44h] [ebp-86BCh]
  int v109; // [esp+48h] [ebp-86B8h]
  char *v110; // [esp+48h] [ebp-86B8h]
  int v111; // [esp+4Ch] [ebp-86B4h]
  int v112; // [esp+50h] [ebp-86B0h]
  idStr *v113; // [esp+58h] [ebp-86A8h]
  bool *v114; // [esp+5Ch] [ebp-86A4h]
  int v115; // [esp+5Ch] [ebp-86A4h]
  int v116; // [esp+5Ch] [ebp-86A4h]
  int v117; // [esp+60h] [ebp-86A0h]
  idStr v118; // [esp+64h] [ebp-869Ch] BYREF
  idAsyncServer *v119; // [esp+84h] [ebp-867Ch]
  idStr v120; // [esp+88h] [ebp-8678h] BYREF
  idBitMsg v121; // [esp+A8h] [ebp-8658h] BYREF
  int value; // [esp+CCh] [ebp-8634h]
  idBitMsg v123; // [esp+D0h] [ebp-8630h] BYREF
  char Str[1024]; // [esp+F4h] [ebp-860Ch] BYREF
  int v125[128]; // [esp+4F4h] [ebp-820Ch]
  char v126[16384]; // [esp+6F4h] [ebp-800Ch] BYREF
  char v127[16384]; // [esp+46F4h] [ebp-400Ch] BYREF
  int v128; // [esp+86FCh] [ebp-4h]

  v119 = this;
  v128 = 2;
  v113 = 0;
  v111 = 0;
  v112 = 0;
  v120.len = 0;
  v120.alloced = 20;
  v120.data = v120.baseBuffer;
  v120.baseBuffer[0] = 0;
  idBitMsg::idBitMsg(&v121);
  idBitMsg::idBitMsg(&v123);
  v109 = 0;
  Bits = idBitMsg::ReadBits(msg, 32);
  v5 = (__int16)idBitMsg::ReadBits(msg, -16);
  value = idBitMsg::ReadBits(msg, 32);
  v6 = idAsyncServer::ValidateChallenge(this, from, Bits, v5);
  if ( v6 == -1 )
    goto LABEL_4;
  v114 = &this->active + 92 * v6;
  if ( *((_DWORD *)v114 + 24) != 3 )
  {
    v7 = *(_DWORD *)common.type;
    v8 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v7 + 132))(
      common.type,
      "client %s: got download request message, not in CDK_PUREWAIT\n",
      v8);
LABEL_4:
    LOBYTE(v128) = 1;
    idStr::FreeData(&v120);
    return;
  }
  v9 = idBitMsg::ReadBits(msg, 32);
  if ( !v9 )
    goto LABEL_8;
  v125[0] = fileSystem->ValidateDownloadPakForChecksum(fileSystem, v9, Str, 1);
  if ( !v125[0] )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "client requested unknown game pak 0x%x",
      v9);
LABEL_8:
    Str[0] = 0;
    v109 = 1;
  }
  v118.data = v118.baseBuffer;
  v118.len = 0;
  v118.alloced = 20;
  v118.baseBuffer[0] = 0;
  v10 = strlen(Str);
  if ( v10 + 1 > 20 )
    idStr::ReAllocate(&v118, v10 + 1, 1);
  data = v118.data;
  v12 = Str;
  do
  {
    v13 = *v12;
    *data++ = *v12++;
  }
  while ( v13 );
  v118.len = v10;
  LOBYTE(v128) = 3;
  v107 = 16;
  v14 = Memory::Allocate(0x204u);
  LOBYTE(v128) = 4;
  if ( v14 )
  {
    v15 = (idStr *)(v14 + 1);
    *v14 = 16;
    `eh vector constructor iterator'(
      v14 + 1,
      0x20u,
      16,
      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  }
  else
  {
    v15 = 0;
  }
  len = v118.len;
  v17 = v118.len + 1 <= v15->alloced;
  LOBYTE(v128) = 3;
  ptr = v15;
  if ( !v17 )
    idStr::ReAllocate(v15, v118.len + 1, 0);
  qmemcpy(v15->data, v118.data, len);
  v15->data[len] = 0;
  v15->len = len;
  v106 = 1;
  LOBYTE(v128) = 2;
  idStr::FreeData(&v118);
  v99 = 1;
  for ( i = idBitMsg::ReadBits(msg, 32); i; i = idBitMsg::ReadBits(msg, 32) )
  {
    v19 = fileSystem->ValidateDownloadPakForChecksum(fileSystem, i, Str, 0);
    v125[v99] = v19;
    if ( !v19 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "client requested an unknown pak 0x%x",
        i);
      ++v109;
      Str[0] = 0;
    }
    v118.data = v118.baseBuffer;
    v118.len = 0;
    v118.alloced = 20;
    v118.baseBuffer[0] = 0;
    v20 = strlen(Str);
    if ( v20 + 1 > 20 )
      idStr::ReAllocate(&v118, v20 + 1, 1);
    v21 = v118.data;
    v22 = Str;
    do
    {
      v23 = *v22;
      *v21++ = *v22++;
    }
    while ( v23 );
    v118.len = v20;
    LOBYTE(v128) = 6;
    if ( !ptr && v107 != 16 )
    {
      v24 = v106;
      v107 = 16;
      if ( v106 > 16 )
      {
        v24 = 16;
        v106 = 16;
      }
      v25 = Memory::Allocate(0x204u);
      LOBYTE(v128) = 7;
      if ( v25 )
      {
        v26 = (idStr *)(v25 + 1);
        *v25 = 16;
        `eh vector constructor iterator'(
          v25 + 1,
          0x20u,
          16,
          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        v27 = v26;
      }
      else
      {
        v27 = 0;
      }
      LOBYTE(v128) = 6;
      ptr = v27;
      if ( v24 > 0 )
      {
        v89 = 4;
        p_data = &v27->data;
        v102 = -4 - (_DWORD)v27;
        v95 = (char *)v24;
        do
        {
          v29 = *(unsigned int *)((char *)p_data + v102);
          if ( (int)(v29 + 1) > (int)p_data[1] )
            idStr::ReAllocate((idStr *)(p_data - 1), v29 + 1, 0);
          qmemcpy(*p_data, *(const void **)v89, v29);
          (*p_data)[v29] = 0;
          *(p_data - 1) = (char *)v29;
          p_data += 8;
          v57 = v95-- == (char *)1;
          v89 += 32;
        }
        while ( !v57 );
      }
    }
    v30 = v107;
    if ( v106 == v107 )
    {
      v31 = (v107 + 16) % 16;
      v32 = v107 + 16 - v31;
      if ( v32 > 0 )
      {
        if ( v32 != v107 )
        {
          v33 = v106;
          v90 = (unsigned int *)ptr;
          v107 = v107 + 16 - v31;
          if ( v32 < v106 )
          {
            v33 = v30 + 16 - v31;
            v106 = v33;
          }
          v34 = (int *)Memory::Allocate(32 * v32 + 4);
          LOBYTE(v128) = 8;
          if ( v34 )
          {
            v35 = (idStr *)(v34 + 1);
            *v34 = v32;
            `eh vector constructor iterator'(
              v34 + 1,
              0x20u,
              v32,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            v36 = v35;
          }
          else
          {
            v36 = 0;
          }
          LOBYTE(v128) = 6;
          ptr = v36;
          if ( v33 > 0 )
          {
            v96 = v90;
            v37 = &v36->data;
            v117 = (char *)v90 - (char *)v36;
            v103 = v106;
            do
            {
              v38 = *v96;
              v39 = *v96 + 1;
              if ( v39 > (int)v37[1] )
                idStr::ReAllocate((idStr *)(v37 - 1), v39, 0);
              v96 += 8;
              qmemcpy(*v37, *(char **)((char *)v37 + v117), v38);
              (*v37)[v38] = 0;
              *(v37 - 1) = (char *)v38;
              v37 += 8;
              --v103;
            }
            while ( v103 );
          }
          if ( v90 )
          {
            `eh vector destructor iterator'(
              v90,
              0x20u,
              *(v90 - 1),
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(v90 - 1);
          }
        }
      }
      else
      {
        if ( ptr )
        {
          `eh vector destructor iterator'(
            ptr,
            0x20u,
            *(_DWORD *)&ptr[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(&ptr[-1].baseBuffer[16]);
        }
        ptr = 0;
        v106 = 0;
        v107 = 0;
      }
    }
    v40 = &ptr[v106];
    v41 = v118.len;
    if ( v118.len + 1 > v40->alloced )
      idStr::ReAllocate(&ptr[v106], v118.len + 1, 0);
    qmemcpy(v40->data, v118.data, v41);
    v40->data[v41] = 0;
    ++v106;
    v40->len = v41;
    LOBYTE(v128) = 2;
    idStr::FreeData(&v118);
    ++v99;
  }
  v42 = 0;
  if ( v106 > 0 )
  {
    v91 = (const char **)&ptr->data;
    do
    {
      if ( v42 > 0 )
      {
        v43 = v120.len + 1;
        if ( v120.len + 2 > v120.alloced )
          idStr::ReAllocate(&v120, v120.len + 2, 1);
        v44 = 0;
        v45 = 59;
        do
        {
          v46 = &v120.data[v44++];
          v46[v120.len] = v45;
          v45 = asc_102A5CB4[v44];
        }
        while ( v45 );
        v120.len = v43;
        v120.data[v43] = 0;
      }
      v47 = *v91;
      if ( *v91 )
      {
        v48 = (unsigned int)&(*v91)[strlen(*v91) + 1];
        v49 = v48 - (_DWORD)(v47 + 1) + v120.len;
        v50 = v48 - (_DWORD)v47 + v120.len;
        if ( v50 > v120.alloced )
          idStr::ReAllocate(&v120, v50, 1);
        v51 = *v47;
        for ( j = 0; v51; v51 = v47[j] )
        {
          v53 = &v120.data[j++];
          v53[v120.len] = v51;
        }
        v120.len = v49;
        v120.data[v49] = 0;
      }
      v91 += 8;
      ++v42;
    }
    while ( v42 < v106 );
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "got download request for %d paks - %s\n",
    v99 - v109,
    v120.data);
  v121.writeData = (unsigned __int8 *)v126;
  v121.readData = (const unsigned __int8 *)v126;
  v121.maxSize = 0x4000;
  v121.numValueOverflows = 0;
  idBitMsg::WriteBits(&v121, -1, -16);
  idBitMsg::WriteString(&v121, "downloadInfo", -1);
  idBitMsg::WriteBits(&v121, value, 32);
  v54 = game->__vftable;
  v88 = v120.data;
  v55 = Sys_NetAdrToString(from);
  if ( !v54->DownloadRequest(game, v55, (const char *)v114 + 140, v88, Str) )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "game: no downloads\n");
    idBitMsg::WriteBits(&v121, 3, 8);
    idPort::SendPacket(&v119->serverPort, from, v121.writeData, v121.curSize);
    LOBYTE(v128) = 1;
    idStr::FreeData(&v120);
    v56 = ptr;
    v57 = ptr == 0;
    goto LABEL_142;
  }
  v58 = Str;
  v59 = 0;
  v100 = 0;
  v60 = strchr(Str, 59);
  v110 = v60;
  while ( 1 )
  {
    if ( v60 )
      *v60 = 0;
    if ( v59 )
      break;
    v59 = atoi(v58);
    v100 = v59;
LABEL_121:
    if ( v60 )
    {
      v58 = v60 + 1;
      v60 = strchr(v60 + 1, 59);
      v110 = v60;
      if ( v58 )
        continue;
    }
    goto LABEL_123;
  }
  if ( v59 == 1 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "download request: redirect to URL %s\n",
      v58);
    idBitMsg::WriteBits(&v121, 1, 8);
    idBitMsg::WriteString(&v121, v58, -1);
    idPort::SendPacket(&v119->serverPort, from, v121.writeData, v121.curSize);
    goto LABEL_139;
  }
  if ( v59 == 2 )
  {
    v118.len = 0;
    v118.alloced = 20;
    v118.data = v118.baseBuffer;
    v118.baseBuffer[0] = 0;
    if ( v58 )
    {
      v61 = (unsigned int)&v58[strlen(v58) + 1];
      v62 = v61 - (_DWORD)(v58 + 1);
      v63 = v61 - (_DWORD)v58;
      if ( v63 > 20 )
        idStr::ReAllocate(&v118, v63, 1);
      v64 = v118.data;
      do
      {
        v65 = *v58;
        *v64++ = *v58++;
      }
      while ( v65 );
      v118.len = v62;
    }
    LOBYTE(v128) = 9;
    if ( !v113 && v112 != 16 )
    {
      v66 = v111;
      v112 = 16;
      if ( v111 > 16 )
      {
        v66 = 16;
        v111 = 16;
      }
      v67 = Memory::Allocate(0x204u);
      LOBYTE(v128) = 10;
      if ( v67 )
      {
        v68 = (idStr *)(v67 + 1);
        *v67 = 16;
        `eh vector constructor iterator'(
          v67 + 1,
          0x20u,
          16,
          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        v69 = v68;
      }
      else
      {
        v69 = 0;
      }
      LOBYTE(v128) = 9;
      v113 = v69;
      if ( v66 > 0 )
      {
        v104 = 4;
        v70 = &v69->data;
        v115 = -4 - (_DWORD)v69;
        v92 = (char *)v66;
        do
        {
          v71 = *(unsigned int *)((char *)v70 + v115);
          if ( (int)(v71 + 1) > (int)v70[1] )
            idStr::ReAllocate((idStr *)(v70 - 1), v71 + 1, 0);
          qmemcpy(*v70, *(const void **)v104, v71);
          (*v70)[v71] = 0;
          *(v70 - 1) = (char *)v71;
          v70 += 8;
          v57 = v92-- == (char *)1;
          v104 += 32;
        }
        while ( !v57 );
      }
    }
    v72 = v112;
    if ( v111 == v112 )
    {
      v73 = (v112 + 16) % 16;
      v74 = v112 + 16 - v73;
      if ( v74 > 0 )
      {
        if ( v74 != v112 )
        {
          v75 = v111;
          v97 = (unsigned int *)v113;
          v112 = v112 + 16 - v73;
          if ( v74 < v111 )
          {
            v75 = v72 + 16 - v73;
            v111 = v75;
          }
          v76 = (int *)Memory::Allocate(32 * v74 + 4);
          LOBYTE(v128) = 11;
          if ( v76 )
          {
            v77 = (idStr *)(v76 + 1);
            *v76 = v74;
            `eh vector constructor iterator'(
              v76 + 1,
              0x20u,
              v74,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            v78 = v77;
          }
          else
          {
            v78 = 0;
          }
          LOBYTE(v128) = 9;
          v113 = v78;
          if ( v75 > 0 )
          {
            v93 = v97;
            v79 = &v78->data;
            v116 = (char *)v97 - (char *)v78;
            v105 = v111;
            do
            {
              v80 = *v93;
              v81 = *v93 + 1;
              if ( v81 > (int)v79[1] )
                idStr::ReAllocate((idStr *)(v79 - 1), v81, 0);
              v93 += 8;
              qmemcpy(*v79, *(char **)((char *)v79 + v116), v80);
              (*v79)[v80] = 0;
              *(v79 - 1) = (char *)v80;
              v79 += 8;
              --v105;
            }
            while ( v105 );
          }
          if ( v97 )
          {
            `eh vector destructor iterator'(
              v97,
              0x20u,
              *(v97 - 1),
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(v97 - 1);
          }
        }
      }
      else
      {
        if ( v113 )
        {
          `eh vector destructor iterator'(
            v113,
            0x20u,
            *(_DWORD *)&v113[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(&v113[-1].baseBuffer[16]);
        }
        v113 = 0;
        v111 = 0;
        v112 = 0;
      }
    }
    v82 = &v113[v111];
    v83 = v118.len;
    if ( v118.len + 1 > v82->alloced )
      idStr::ReAllocate(&v113[v111], v118.len + 1, 0);
    ++v111;
    qmemcpy(v82->data, v118.data, v83);
    v82->data[v83] = 0;
    v82->len = v83;
    LOBYTE(v128) = 2;
    idStr::FreeData(&v118);
    v59 = v100;
    v60 = v110;
    goto LABEL_121;
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(common.type, "wrong op type %d\n", v59);
LABEL_123:
  if ( v59 == 2 )
  {
    v98 = 0;
    v101 = 0;
    idBitMsg::WriteBits(&v121, 2, 8);
    v84 = 0;
    v123.writeData = (unsigned __int8 *)v127;
    v123.readData = (const unsigned __int8 *)v127;
    v123.maxSize = 0x4000;
    v123.numValueOverflows = 0;
    if ( v111 > 0 )
    {
      v94 = v113;
      v85 = (const char **)&ptr->data;
      while ( 1 )
      {
        v86 = v125[v84];
        v123.curSize = 0;
        v123.overflowed = 0;
        v123.writeBit = 0;
        if ( v86 && v94->len )
        {
          v98 += v86;
          ++v101;
          idBitMsg::WriteBits(&v123, 1, 8);
          idBitMsg::WriteString(&v123, *v85, -1);
          idBitMsg::WriteString(&v123, *(const char **)((char *)v85 + (char *)v113 - (char *)ptr), -1);
          idBitMsg::WriteBits(&v123, v86, 32);
        }
        else
        {
          idBitMsg::WriteBits(&v123, 0, 8);
          idBitMsg::WriteString(&v123, *v85, -1);
        }
        if ( v121.maxSize - v123.curSize - v121.curSize <= 5 )
          break;
        idBitMsg::WriteData(&v121, v123.writeData, v123.curSize);
        ++v94;
        ++v84;
        v85 += 8;
        if ( v84 >= v111 )
          goto LABEL_136;
      }
      idBitMsg::WriteBits(&v121, 2, 8);
    }
LABEL_136:
    if ( v84 == v111 )
      idBitMsg::WriteBits(&v121, 2, 8);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "download request: download %d paks, %d bytes\n",
      v101,
      v98);
    idPort::SendPacket(&v119->serverPort, from, v121.writeData, v121.curSize);
  }
LABEL_139:
  LOBYTE(v128) = 1;
  idStr::FreeData(&v120);
  LOBYTE(v128) = 0;
  if ( v113 )
  {
    `eh vector destructor iterator'(
      v113,
      0x20u,
      *(_DWORD *)&v113[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(&v113[-1].baseBuffer[16]);
  }
  v56 = ptr;
  v57 = ptr == 0;
LABEL_142:
  v128 = -1;
  if ( !v57 )
  {
    v87 = &v56[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v56,
      0x20u,
      *(_DWORD *)&v56[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v87);
  }
}

// FUNC: private: bool __thiscall idAsyncServer::ConnectionlessMessage(struct netadr_t,class idBitMsg const &)
char __thiscall idAsyncServer::ConnectionlessMessage(idAsyncServer *this, netadr_t from, idBitMsg *msg)
{
  int curSize; // ecx
  int v5; // edi
  idMsgChannel *p_channel; // esi
  int v7; // eax
  int v8; // ebx
  char v9; // al
  int v11; // esi
  const char *v12; // eax
  netadr_t v13; // [esp-Ch] [ebp-82Ch]
  netadr_t remoteAddr; // [esp+10h] [ebp-810h] BYREF
  char string[2048]; // [esp+20h] [ebp-800h] BYREF

  idBitMsg::ReadString(msg, string, 2048);
  if ( idStr::Icmp(string, &entityFilter) )
  {
    if ( !idStr::Icmp(string, "getInfo") )
    {
      idAsyncServer::ProcessGetInfoMessage(this, from, msg);
      return 0;
    }
    if ( !idStr::Icmp(string, "rcon") )
    {
      idAsyncServer::ProcessRemoteConsoleMessage(this, from, msg);
      return 1;
    }
    if ( !this->active )
    {
      idAsyncServer::PrintOOB(this, from, 0, "#str_104849");
      return 0;
    }
    if ( !idStr::Icmp(string, "challenge") )
    {
      idAsyncServer::ProcessChallengeMessage(this, from, msg);
      return 0;
    }
    if ( !idStr::Icmp(string, "connect") )
    {
      idAsyncServer::ProcessConnectMessage(this, from, msg);
      return 0;
    }
    if ( !idStr::Icmp(string, "pureClient") )
    {
      idAsyncServer::ProcessPureMessage(this, from, msg);
      return 0;
    }
    if ( !idStr::Icmp(string, "downloadRequest") )
      idAsyncServer::ProcessDownloadRequestMessage(this, from, msg);
    if ( !idStr::Icmp(string, "auth") )
    {
      v13 = *idAsyncNetwork::GetMasterAddress(&remoteAddr);
      if ( !Sys_CompareNetAdrBase(from, v13) )
      {
        v11 = *(_DWORD *)common.type;
        v12 = Sys_NetAdrToString(from);
        (*(void (**)(netadrtype_t, const char *, ...))(v11 + 124))(common.type, "auth: bad source %s\n", v12);
        return 0;
      }
      if ( idAsyncNetwork::LANServer.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "auth message from master. net_LANServer is enabled, ignored.\n");
      idAsyncServer::ProcessAuthMessage(this, msg);
    }
  }
  else
  {
    curSize = msg->curSize;
    if ( curSize <= 2048 )
    {
      qmemcpy(string, msg->readData, curSize);
      if ( !idStr::Icmpn(string, &byte_102A92FC, 7) )
      {
        v5 = 0;
        p_channel = &this->clients[0].channel;
        while ( 1 )
        {
          if ( *(int *)&p_channel[-1].reliableReceive.buffer[16356] >= 3 )
          {
            v7 = *(_DWORD *)p_channel->remoteAddress.ip;
            v8 = *(_DWORD *)&p_channel->remoteAddress.port;
            remoteAddr.type = p_channel->remoteAddress.type;
            *(_DWORD *)remoteAddr.ip = v7;
            if ( Sys_CompareNetAdrBase(from, p_channel->remoteAddress) && from.port == (_WORD)v8 )
              break;
          }
          ++v5;
          p_channel = (idMsgChannel *)((char *)p_channel + 65800);
          if ( v5 >= 32 )
          {
            v5 = -1;
            break;
          }
        }
        v9 = string[7];
        if ( string[7] != 67 && string[7] != 49 && string[7] != 74 )
        {
          PbSvAddEvent(13, v5, msg->curSize - 4, &string[4]);
          v9 = string[7];
        }
        if ( v9 != 83 && v9 != 50 && v9 != 71 && v9 != 73 && v9 != 89 && v9 != 66 && v9 != 76 )
        {
          PbClAddEvent(13, msg->curSize - 4, &string[4]);
          return 0;
        }
      }
    }
  }
  return 0;
}

// FUNC: private: bool __thiscall idAsyncServer::ProcessMessage(struct netadr_t,class idBitMsg &)
char __thiscall idAsyncServer::ProcessMessage(idAsyncServer *this, const netadr_t from, idBitMsg *msg)
{
  int v5; // esi
  const char *v6; // eax
  int v7; // ebx
  idMsgChannel *i; // esi
  int Bits; // [esp+10h] [ebp-402Ch]
  int sequence; // [esp+14h] [ebp-4028h] BYREF
  idBitMsg v11; // [esp+18h] [ebp-4024h] BYREF
  char v12[16384]; // [esp+3Ch] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&v11);
  Bits = (__int16)idBitMsg::ReadBits(msg, -16);
  if ( Bits == -1 )
    return idAsyncServer::ConnectionlessMessage(this, from, msg);
  if ( msg->curSize - msg->readCount >= 4 )
  {
    v7 = 0;
    for ( i = &this->clients[0].channel;
          !*(_DWORD *)&i[-1].reliableReceive.buffer[16356]
       || !Sys_CompareNetAdrBase(from, i->remoteAddress)
       || Bits != *(_DWORD *)&i[-1].reliableReceive.buffer[16352];
          i = (idMsgChannel *)((char *)i + 65800) )
    {
      if ( ++v7 >= 32 )
      {
        v11.writeData = (unsigned __int8 *)v12;
        v11.readData = (const unsigned __int8 *)v12;
        v11.maxSize = 0x4000;
        v11.numValueOverflows = 0;
        idBitMsg::WriteBits(&v11, -1, -16);
        idBitMsg::WriteString(&v11, "disconnect", -1);
        idPort::SendPacket(&this->serverPort, from, v11.writeData, v11.curSize);
        return 0;
      }
    }
    if ( !idMsgChannel::Process(i, from, this->serverTime, msg, &sequence)
      || *(_DWORD *)&i[-1].reliableReceive.buffer[16356] == 1 )
    {
      return 0;
    }
    i[1].maxRate = this->serverTime;
    idAsyncServer::ProcessReliableClientMessages(this, v7);
    idAsyncServer::ProcessUnreliableClientMessage(this, v7, msg);
    return 0;
  }
  else
  {
    v5 = *(_DWORD *)common.type;
    v6 = Sys_NetAdrToString(from);
    (*(void (**)(netadrtype_t, const char *, ...))(v5 + 132))(common.type, "%s: tiny packet\n", v6);
    return 0;
  }
}

// FUNC: public: void __thiscall idAsyncServer::ProcessConnectionLessMessages(void)
void __thiscall idAsyncServer::ProcessConnectionLessMessages(idAsyncServer *this)
{
  int size; // [esp+10h] [ebp-4034h] BYREF
  netadr_t from; // [esp+14h] [ebp-4030h] BYREF
  idBitMsg msg; // [esp+20h] [ebp-4024h] BYREF
  char data[16384]; // [esp+44h] [ebp-4000h] BYREF

  idBitMsg::idBitMsg(&msg);
  if ( this->serverPort.port && idPort::GetPacket(&this->serverPort, &from, data, &size, 0x4000) )
  {
    do
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
      if ( (unsigned __int16)idBitMsg::ReadBits(&msg, -16) == 0xFFFF )
        idAsyncServer::ConnectionlessMessage(this, from, &msg);
    }
    while ( idPort::GetPacket(&this->serverPort, &from, data, &size, 0x4000) );
  }
}

// FUNC: public: void __thiscall idAsyncServer::RunFrame(void)
void __thiscall idAsyncServer::RunFrame(idAsyncServer *this)
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
  char v17; // cl
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
  int v38; // eax
  int v39; // ecx
  int v40; // eax
  int *v41; // eax
  int v42; // eax
  bool PacketBlocking; // bl
  int v44; // eax
  int v45; // ecx
  int NumIdleClients; // edi
  idAsyncServer *v47; // ecx
  BOOL v48; // edi
  int integerValue; // eax
  idCVar_vtbl *v50; // edx
  idKeyValue *list; // edi
  int v52; // edx
  int v53; // eax
  int m; // eax
  idCVarSystem_vtbl *v55; // eax
  idDict *v56; // eax
  idKeyValue *v57; // edi
  int v58; // edx
  int v59; // eax
  int n; // eax
  idGame_vtbl *v61; // eax
  idDict *v62; // eax
  int gameTimeResidual; // ecx
  int v64; // ebx
  int v65; // edi
  int v66; // edx
  int v67; // eax
  int v68; // ebx
  int *p_maxRate; // edi
  int v70; // eax
  netadrtype_t type; // ebx
  int v72; // edi
  int v73; // ebp
  int OutgoingRate; // eax
  int v75; // ebx
  serverClientState_t *p_clientState; // edi
  int v77; // eax
  int v78; // edx
  int v79; // ecx
  double v80; // st7
  double v81; // st6
  int v82; // edi
  char *v83; // eax
  idFile *v84; // edi
  idFile_vtbl *v85; // ebx
  int NumClients; // eax
  int v87; // [esp+68h] [ebp-44F4h]
  int SystemRam; // [esp+6Ch] [ebp-44F0h]
  int stats_max; // [esp+6Ch] [ebp-44F0h]
  const char *ProcessorString; // [esp+70h] [ebp-44ECh]
  int v91; // [esp+70h] [ebp-44ECh]
  int v92; // [esp+70h] [ebp-44ECh]
  int timeSeconds; // [esp+88h] [ebp-44D4h] BYREF
  idDict newInfo; // [esp+8Ch] [ebp-44D0h] BYREF
  idStr fileName; // [esp+B8h] [ebp-44A4h] BYREF
  int lastCatchup; // [esp+D8h] [ebp-4484h]
  idGame_vtbl *v97; // [esp+DCh] [ebp-4480h]
  int size; // [esp+E0h] [ebp-447Ch] BYREF
  netadr_t from; // [esp+E4h] [ebp-4478h] BYREF
  idBitMsg msg; // [esp+F0h] [ebp-446Ch] BYREF
  idStr string; // [esp+114h] [ebp-4448h] BYREF
  gameReturn_t ret; // [esp+134h] [ebp-4428h] BYREF
  unsigned __int8 msgBuf[16384]; // [esp+54Ch] [ebp-4010h] BYREF
  int v104; // [esp+4558h] [ebp-4h]

  idBitMsg::idBitMsg(&msg);
  v2 = 0;
  timeSeconds = 0;
  lastCatchup = 0;
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
  this->serverTime += v4;
  v5 = this->serverPort.port == 0;
  v97 = (idGame_vtbl *)v4;
  this->realTime = v3;
  if ( !v5 )
  {
    if ( this->active )
    {
      this->gameTimeResidual += v4;
      if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
      {
        if ( idAsyncNetwork::debugStartLevel.internalVar->integerValue )
        {
          newInfo.args.num = 0;
          newInfo.args.granularity = 20;
          newInfo.args.size = (int)&newInfo.args.list;
          LOBYTE(newInfo.args.list) = 0;
          v104 = 0;
          fileName.len = 0;
          fileName.alloced = 20;
          fileName.data = fileName.baseBuffer;
          fileName.baseBuffer[0] = 0;
          timeSeconds = 0;
          v6 = *(_DWORD *)common.type;
          LOBYTE(v104) = 1;
          (*(void (__cdecl **)(netadrtype_t, const char *))(v6 + 124))(
            common.type,
            "Match starting, frame time logging on\n");
          profile_netDebugActive = 1;
          idAsyncNetwork::debugStartLevel.internalVar->InternalSetBool(idAsyncNetwork::debugStartLevel.internalVar, 0);
          session->GetCurrentMapName(session, (idStr *)&newInfo);
          idStr::StripFileExtension((idStr *)&newInfo);
          idStr::StripPath((idStr *)&newInfo);
          idStr::operator=(&fileName, "logs/timing_logs/");
          timeSeconds = time(&timeSeconds);
          v7 = localtime(&timeSeconds);
          v8 = va("%02d%02d%02d_%02d%02d_", v7->tm_year % 100, v7->tm_mon + 1, v7->tm_mday, v7->tm_hour, v7->tm_min);
          v9 = v8;
          if ( v8 )
          {
            v10 = strlen(v8);
            v11 = v10 + fileName.len;
            if ( (int)(v10 + fileName.len + 1) > fileName.alloced )
              idStr::ReAllocate(&fileName, v10 + fileName.len + 1, 1);
            v12 = *v9;
            for ( i = 0; v12; v12 = v9[i] )
            {
              v14 = &fileName.data[i++];
              v14[fileName.len] = v12;
            }
            fileName.len = v11;
            fileName.data[v11] = 0;
          }
          v15 = fileName.len + newInfo.args.num;
          if ( fileName.len + newInfo.args.num + 1 > fileName.alloced )
            idStr::ReAllocate(&fileName, fileName.len + newInfo.args.num + 1, 1);
          for ( j = 0; j < newInfo.args.num; v18[fileName.len] = v17 )
          {
            v17 = *(_BYTE *)(newInfo.args.size + j);
            v18 = &fileName.data[j++];
          }
          fileName.len = v15;
          fileName.data[v15] = 0;
          v19 = fileName.len + 1;
          if ( fileName.len + 2 > fileName.alloced )
            idStr::ReAllocate(&fileName, fileName.len + 2, 1);
          v20 = 0;
          v21 = 95;
          do
          {
            v22 = &fileName.data[v20++];
            v22[fileName.len] = v21;
            v21 = asc_1029F57C[v20];
          }
          while ( v21 );
          fileName.len = v19;
          fileName.data[v19] = 0;
          v23 = cvarSystem->GetCVarString(cvarSystem, "win_username");
          v24 = v23;
          if ( v23 )
          {
            v25 = strlen(v23) + fileName.len;
            if ( v25 + 1 > fileName.alloced )
              idStr::ReAllocate(&fileName, v25 + 1, 1);
            v26 = *v24;
            for ( k = 0; v26; v26 = v24[k] )
            {
              v28 = &fileName.data[k++];
              v28[fileName.len] = v26;
            }
            fileName.len = v25;
            fileName.data[v25] = 0;
          }
          v29 = fileName.len + 14;
          if ( fileName.len + 15 > fileName.alloced )
            idStr::ReAllocate(&fileName, fileName.len + 15, 1);
          v30 = 0;
          v31 = 95;
          do
          {
            v32 = &fileName.data[v30++];
            v32[fileName.len] = v31;
            v31 = aServerlogCsv[v30];
          }
          while ( v31 );
          fileName.len = v29;
          fileName.data[v29] = 0;
          if ( profile_File )
            fileSystem->CloseFile(fileSystem, profile_File);
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "Attempting to open file '%s'\n",
            fileName.data);
          v33 = fileSystem->OpenFileWrite(fileSystem, fileName.data, "fs_savepath", 0);
          profile_File = v33;
          if ( v33
            || ((*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "ERROR:  unable to open frame log '%s'!\n",
                  fileName.data),
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
              "fps,frameTime,predictTime,packetTime,waiting,inBytes,outBytes,inSecBytes,outSecBytes,numPlayers\n");
          }
          LOBYTE(v104) = 0;
          idStr::FreeData(&fileName);
          v104 = -1;
          idStr::FreeData((idStr *)&newInfo);
          v4 = (int)v97;
          v2 = lastCatchup;
        }
        v38 = Sys_Milliseconds();
        v39 = v38 - profilePrevious_0;
        timeSeconds = v38;
        profilePrevious_0 = v38;
        profile_frameTime = v39;
        v40 = profileIndex_0 + 1;
        profilePreviousFrames_0[profileIndex_0 % 4] = v39;
        profileIndex_0 = v40;
        if ( v40 >= 4 )
        {
          v41 = profilePreviousFrames_0;
          do
            v2 += *v41++;
          while ( (int)v41 < (int)&idDemo::enforceFS );
          profile_fps = 4000 / v2;
        }
        else
        {
          profile_fps = 0;
        }
        profileSecondCount += v39;
        if ( profileSecondCount >= 1000 )
          profileSecondCount = 0;
      }
      if ( this->localClientNum < 0
        && v4 >= (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "hitch (%d msec)\n",
          v4);
      }
      while ( 1 )
      {
        v42 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
        PacketBlocking = idPort::GetPacketBlocking(
                           &this->serverPort,
                           &from,
                           msgBuf,
                           &size,
                           0x4000,
                           v42 - this->gameTimeResidual - 1);
        if ( PacketBlocking )
        {
          msg.writeData = msgBuf;
          msg.readData = msgBuf;
          msg.maxSize = 0x4000;
          msg.numValueOverflows = 0;
          msg.curSize = 0x4000;
          if ( size <= 0x4000 )
            msg.curSize = size;
          msg.readCount = 0;
          msg.readBit = 0;
          if ( idAsyncServer::ProcessMessage(this, from, &msg) )
            break;
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
        this->serverTime += v45;
        this->gameTimeResidual += v45;
        this->realTime = v44;
        if ( !PacketBlocking
          && this->gameTimeResidual >= (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type) )
        {
          if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
            profile_packetTime = Sys_Milliseconds() - timeSeconds;
          idAsyncServer::MasterHeartbeat(this, 0);
          if ( this->localClientNum >= 0 )
            idAsyncClient::SendClientHeartbeat(&idAsyncNetwork::client, 0, 0);
          idAsyncServer::CheckClientTimeouts(this);
          v48 = 1;
          if ( idAsyncServer::GetNumClients(this) )
          {
            NumIdleClients = idAsyncServer::GetNumIdleClients(this);
            if ( NumIdleClients == idAsyncServer::GetNumClients(v47) )
              v48 = 0;
          }
          integerValue = idAsyncNetwork::idleServer.internalVar->integerValue;
          if ( (integerValue != 0) == v48 )
          {
            v50 = idAsyncNetwork::idleServer.internalVar->__vftable;
            LOBYTE(lastCatchup) = integerValue == 0;
            v50->InternalSetBool(idAsyncNetwork::idleServer.internalVar, lastCatchup);
            cvarSystem->SetCVarString(cvarSystem, "si_idleServer", idAsyncNetwork::idleServer.internalVar->value, 0);
            cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "rescanSI\n");
          }
          if ( this->serverTime <= 1879048192 )
          {
            if ( (cvarSystem->GetModifiedFlags(cvarSystem) & 0x800) != 0 )
            {
              newInfo.args.granularity = 16;
              newInfo.args.list = 0;
              newInfo.args.num = 0;
              newInfo.args.size = 0;
              v104 = 2;
              idHashIndex::Init(&newInfo.argHash, 1024, 1024);
              list = newInfo.args.list;
              LOBYTE(v104) = 3;
              newInfo.args.granularity = 16;
              if ( newInfo.args.list )
              {
                v52 = (newInfo.args.num + 15) % 16;
                v53 = newInfo.args.num + 15 - v52;
                if ( v53 != newInfo.args.size )
                {
                  if ( v53 > 0 )
                  {
                    newInfo.args.size = newInfo.args.num + 15 - v52;
                    if ( v53 < newInfo.args.num )
                      newInfo.args.num = newInfo.args.num + 15 - v52;
                    newInfo.args.list = (idKeyValue *)Memory::Allocate(8 * v53);
                    for ( m = 0; m < newInfo.args.num; ++m )
                    {
                      newInfo.args.list[m].key = list[m].key;
                      newInfo.args.list[m].value = list[m].value;
                    }
                    if ( list )
                      Memory::Free(list);
                  }
                  else
                  {
                    Memory::Free(newInfo.args.list);
                    newInfo.args.list = 0;
                    newInfo.args.num = 0;
                    newInfo.args.size = 0;
                  }
                }
              }
              newInfo.argHash.granularity = 16;
              idHashIndex::Free(&newInfo.argHash);
              newInfo.argHash.hashSize = 128;
              newInfo.argHash.indexSize = 16;
              v55 = cvarSystem->__vftable;
              v104 = 4;
              v56 = (idDict *)v55->MoveCVarsToDict(cvarSystem, 2048);
              idDict::operator=(&newInfo, v56);
              idAsyncServer::SendSyncedCvarsBroadcast(this, &newInfo);
              cvarSystem->ClearModifiedFlags(cvarSystem, 2048);
              v104 = 6;
              idDict::Clear(&newInfo);
              LOBYTE(v104) = 5;
              idHashIndex::Free(&newInfo.argHash);
              v104 = -1;
              if ( newInfo.args.list )
                Memory::Free(newInfo.args.list);
            }
            if ( (cvarSystem->GetModifiedFlags(cvarSystem) & 0x200) != 0 )
            {
              if ( this->localClientNum >= 0 )
              {
                newInfo.args.granularity = 16;
                newInfo.args.list = 0;
                newInfo.args.num = 0;
                newInfo.args.size = 0;
                v104 = 7;
                idHashIndex::Init(&newInfo.argHash, 1024, 1024);
                v57 = newInfo.args.list;
                LOBYTE(v104) = 8;
                newInfo.args.granularity = 16;
                if ( newInfo.args.list )
                {
                  v58 = (newInfo.args.num + 15) % 16;
                  v59 = newInfo.args.num + 15 - v58;
                  if ( v59 != newInfo.args.size )
                  {
                    if ( v59 > 0 )
                    {
                      newInfo.args.size = newInfo.args.num + 15 - v58;
                      if ( v59 < newInfo.args.num )
                        newInfo.args.num = newInfo.args.num + 15 - v58;
                      newInfo.args.list = (idKeyValue *)Memory::Allocate(8 * v59);
                      for ( n = 0; n < newInfo.args.num; ++n )
                      {
                        newInfo.args.list[n].key = v57[n].key;
                        newInfo.args.list[n].value = v57[n].value;
                      }
                      if ( v57 )
                        Memory::Free(v57);
                    }
                    else
                    {
                      Memory::Free(newInfo.args.list);
                      newInfo.args.list = 0;
                      newInfo.args.num = 0;
                      newInfo.args.size = 0;
                    }
                  }
                }
                newInfo.argHash.granularity = 16;
                idHashIndex::Free(&newInfo.argHash);
                newInfo.argHash.hashSize = 128;
                newInfo.argHash.indexSize = 16;
                v61 = game->__vftable;
                v104 = 9;
                v61->ThrottleUserInfo(game);
                v62 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 512);
                idDict::operator=(&newInfo, v62);
                idAsyncServer::SendUserInfoBroadcast(this, this->localClientNum, &newInfo, 0);
                v104 = 11;
                idDict::Clear(&newInfo);
                LOBYTE(v104) = 10;
                idHashIndex::Free(&newInfo.argHash);
                v104 = -1;
                if ( newInfo.args.list )
                  Memory::Free(newInfo.args.list);
              }
              cvarSystem->ClearModifiedFlags(cvarSystem, 512);
            }
            if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
              timeSeconds = Sys_Milliseconds();
            gameTimeResidual = this->gameTimeResidual;
            profile_catchupFrames = 0;
            v5 = idSessionLocal::com_syncGameFrame.internalVar->integerValue == 0;
            profile_gameTimeResidual = gameTimeResidual;
            if ( !v5 )
              this->gameTimeResidual = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
            for ( ;
                  this->gameTimeResidual >= (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
                  ++profile_catchupFrames )
            {
              idAsyncServer::LocalClientInput(this);
              idAsyncServer::FakeClientInput(this);
              idAsyncServer::DuplicateUsercmds(this, this->gameFrame, this->gameTime);
              v64 = 0;
              if ( com_speeds.internalVar->integerValue || com_debugHudActive )
                v64 = Sys_Milliseconds();
              LOBYTE(lastCatchup) = this->gameTimeResidual < 2
                                                           * (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type
                                                                                                 + 40))(common.type);
              v65 = lastCatchup;
              (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 52))(common.type, lastCatchup);
              v66 = **(_DWORD **)common.ip;
              v97 = game->__vftable;
              v67 = (*(int (__thiscall **)(_DWORD, int, int))(v66 + 28))(*(_DWORD *)common.ip, -1, v65);
              (*(void (__thiscall **)(idGame *, char *, usercmd_t *, int))(size + 64))(
                game,
                &ret.sessionCommand[4],
                this->userCmds[(unsigned __int8)this->gameFrame],
                v67);
              if ( com_speeds.internalVar->integerValue || com_debugHudActive )
                time_gameFrame += Sys_Milliseconds() - time_gameFrame - v64;
              idAsyncNetwork::ExecuteSessionCommand(ret.sessionCommand);
              ++this->gameFrame;
              this->gameTime += (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
              this->gameTimeResidual -= (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
            }
            idAsyncServer::DuplicateUsercmds(this, this->gameFrame, this->gameTime);
            if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
              profile_predictTime = Sys_Milliseconds() - timeSeconds;
            session->rw->PushMarkedDefs(session->rw);
            (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 52))(common.type, 1);
            v68 = 0;
            p_maxRate = &this->clients[0].channel.maxRate;
            do
            {
              if ( *(p_maxRate - 15) && v68 != this->localClientNum )
              {
                if ( (idAsyncNetwork::serverMaxClientRate.internalVar->flags & 0x40000) != 0 )
                {
                  v70 = idAsyncNetwork::serverMaxClientRate.internalVar->integerValue;
                  if ( *(p_maxRate - 12) < v70 )
                    v70 = *(p_maxRate - 12);
                  *p_maxRate = v70;
                }
                if ( idMsgChannel::ReadyToSend((idMsgChannel *)(p_maxRate - 4), this->serverTime) )
                {
                  if ( *((_BYTE *)p_maxRate + 60) )
                  {
                    idMsgChannel::SendNextFragment((idMsgChannel *)(p_maxRate - 4), &this->serverPort, this->serverTime);
                  }
                  else if ( *(p_maxRate - 15) == 4 )
                  {
                    if ( !idAsyncServer::SendSnapshotToClient(this, v68) )
                      idAsyncServer::SendPingToClient(this, v68);
                  }
                  else
                  {
                    idAsyncServer::SendEmptyToClient(this, v68, 0);
                  }
                }
              }
              ++v68;
              p_maxRate += 16450;
            }
            while ( v68 < 32 );
            if ( com_showAsyncStats.internalVar->integerValue )
            {
              idAsyncServer::UpdateAsyncStatsAvg(this);
              if ( idAsyncNetwork::serverDedicated.internalVar->integerValue )
              {
                if ( this->serverTime >= this->nextAsyncStatsTime )
                {
                  type = common.type;
                  v72 = this->gameTimeResidual;
                  v73 = *(_DWORD *)common.type;
                  v91 = idAsyncServer::GetIncomingRate(this) >> 10;
                  OutgoingRate = idAsyncServer::GetOutgoingRate(this);
                  (*(void (**)(netadrtype_t, const char *, ...))(v73 + 124))(
                    type,
                    "delay = %d msec, total outgoing rate = %d KB/s, total incoming rate = %d KB/s\n",
                    v72,
                    OutgoingRate >> 10,
                    v91);
                  v75 = 0;
                  p_clientState = &this->clients[0].clientState;
                  do
                  {
                    v77 = *p_clientState;
                    if ( *(int *)p_clientState >= 3 )
                      v78 = *((_DWORD *)p_clientState + 20);
                    else
                      v78 = -1;
                    if ( v77 >= 3 )
                      v79 = *((_DWORD *)p_clientState + 22);
                    else
                      v79 = -1;
                    if ( v77 >= 3 )
                      v80 = *((float *)p_clientState + 23);
                    else
                      v80 = 0.0;
                    if ( v77 >= 3 )
                      v81 = *((float *)p_clientState + 24);
                    else
                      v81 = 0.0;
                    if ( v78 != -1 && v79 != -1 )
                      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                        common.type,
                        "client %d: out rate = %d B/s (% -2.1f%%), in rate = %d B/s (% -2.1f%%)\n",
                        v75,
                        v78,
                        v80,
                        v79,
                        v81);
                    ++v75;
                    p_clientState += 16450;
                  }
                  while ( v75 < 32 );
                  string.len = 0;
                  string.alloced = 20;
                  string.data = string.baseBuffer;
                  string.baseBuffer[0] = 0;
                  v92 = 60 * idAsyncNetwork::serverSnapshotDelay.internalVar->integerValue;
                  stats_max = this->stats_max;
                  v87 = this->stats_average_sum / 60;
                  v104 = 12;
                  sprintf(&string, "avrg out: %d B/s - max %d B/s ( over %d ms )", v87, stats_max, v92);
                  v82 = *(_DWORD *)common.type;
                  v83 = va("%s\n", string.data);
                  (*(void (__cdecl **)(netadrtype_t, char *))(v82 + 124))(common.type, v83);
                  this->nextAsyncStatsTime = this->serverTime + 1000;
                  v104 = -1;
                  idStr::FreeData(&string);
                }
              }
            }
            if ( idAsyncNetwork::debugFrameTime.internalVar->integerValue )
            {
              v84 = profile_File;
              if ( profile_File )
              {
                v85 = profile_File->__vftable;
                NumClients = idAsyncServer::GetNumClients(this);
                v85->Printf(
                  v84,
                  "%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
                  profile_fps,
                  profile_frameTime,
                  profile_predictTime,
                  profile_packetTime,
                  "SRV - N/A",
                  profile_gameTimeResidual,
                  time_frontend,
                  time_backend,
                  time_waiting,
                  net_bytesIn,
                  net_bytesOut,
                  profile_catchupFrames,
                  NumClients);
              }
            }
            BYTE2(idAsyncNetwork::serverMaxClientRate.internalVar->flags) &= ~4u;
          }
          else
          {
            idAsyncServer::ExecuteMapChange(this);
          }
          return;
        }
      }
    }
    else
    {
      idAsyncServer::ProcessConnectionLessMessages(this);
    }
  }
}

// FUNC: public: void __thiscall idAsyncServer::PacifierUpdate(void)
void __thiscall idAsyncServer::PacifierUpdate(idAsyncServer *this)
{
  int v2; // esi
  bool *p_unsentFragments; // edi

  if ( this->active )
  {
    this->realTime = Sys_Milliseconds();
    idAsyncServer::ProcessConnectionLessMessages(this);
    v2 = 0;
    p_unsentFragments = &this->clients[0].channel.unsentFragments;
    do
    {
      if ( *((int *)p_unsentFragments - 30) >= 2 )
      {
        if ( *p_unsentFragments )
          idMsgChannel::SendNextFragment((idMsgChannel *)(p_unsentFragments - 76), &this->serverPort, this->serverTime);
        else
          idAsyncServer::SendEmptyToClient(this, v2, 0);
      }
      ++v2;
      p_unsentFragments += 65800;
    }
    while ( v2 < 32 );
  }
}
