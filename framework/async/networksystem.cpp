
// FUNC: public: virtual void __thiscall idNetworkSystem::AddFriend(int)
void __userpurge idNetworkSystem::AddFriend(idNetworkSystem *this@<ecx>, int a2@<edi>, int clientNum)
{
  rvServerScan::AddToFriendsList(&idAsyncNetwork::client.serverList, a2, clientNum);
}

// FUNC: public: virtual void __thiscall idNetworkSystem::RemoveFriend(int)
void __thiscall idNetworkSystem::RemoveFriend(idNetworkSystem *this, int clientNum)
{
  rvServerScan::RemoveFromFriendsList(&idAsyncNetwork::client.serverList, clientNum);
}

// FUNC: public: virtual void __thiscall idNetworkSystem::SetLoadingText(char const *)
void __thiscall idNetworkSystem::SetLoadingText(idNetworkSystem *this, const char *loadingText)
{
  session->SetLoadingText(session, loadingText);
}

// FUNC: public: virtual void __thiscall idNetworkSystem::AddLoadingIcon(char const *)
void __thiscall idNetworkSystem::AddLoadingIcon(idNetworkSystem *this, const char *icon)
{
  session->AddLoadingIcon(session, icon);
}

// FUNC: public: virtual void __thiscall idNetworkSystem::ServerSendReliableMessage(int,class idBitMsg const &)
void __thiscall idNetworkSystem::ServerSendReliableMessage(idNetworkSystem *this, int clientNum, const idBitMsg *msg)
{
  if ( idAsyncNetwork::server.active )
    idAsyncServer::SendReliableGameMessage(&idAsyncNetwork::server, clientNum, msg);
}

// FUNC: public: virtual void __thiscall idNetworkSystem::ServerSendReliableMessageExcluding(int,class idBitMsg const &)
void __thiscall idNetworkSystem::ServerSendReliableMessageExcluding(
        idNetworkSystem *this,
        int clientNum,
        const idBitMsg *msg)
{
  if ( idAsyncNetwork::server.active )
  {
    if ( clientNum == -1 )
      idAsyncServer::SendReliableGameMessage(&idAsyncNetwork::server, -1, msg);
    else
      idAsyncServer::SendReliableGameMessageExcluding(&idAsyncNetwork::server, clientNum, msg);
  }
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ServerGetClientPing(int)
int __thiscall idNetworkSystem::ServerGetClientPing(idNetworkSystem *this, int clientNum)
{
  if ( idAsyncNetwork::server.active )
    return idAsyncServer::GetClientPing(&idAsyncNetwork::server, clientNum);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ServerGetClientPrediction(int)
int __thiscall idNetworkSystem::ServerGetClientPrediction(idNetworkSystem *this, int clientNum)
{
  if ( idAsyncNetwork::server.active )
    return idAsyncServer::GetClientPrediction(&idAsyncNetwork::server, clientNum);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ServerGetClientTimeSinceLastPacket(int)
int __thiscall idNetworkSystem::ServerGetClientTimeSinceLastPacket(idNetworkSystem *this, int clientNum)
{
  if ( idAsyncNetwork::server.active )
    return idAsyncServer::GetClientTimeSinceLastPacket(&idAsyncNetwork::server, clientNum);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ServerGetClientTimeSinceLastInput(int)
int __thiscall idNetworkSystem::ServerGetClientTimeSinceLastInput(idNetworkSystem *this, int clientNum)
{
  if ( idAsyncNetwork::server.active )
    return idAsyncServer::GetClientTimeSinceLastInput(&idAsyncNetwork::server, clientNum);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ServerGetClientOutgoingRate(int)
int __thiscall idNetworkSystem::ServerGetClientOutgoingRate(idNetworkSystem *this, int clientNum)
{
  if ( idAsyncNetwork::server.active )
    return idAsyncServer::GetClientOutgoingRate(&idAsyncNetwork::server, clientNum);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ServerGetClientIncomingRate(int)
int __thiscall idNetworkSystem::ServerGetClientIncomingRate(idNetworkSystem *this, int clientNum)
{
  if ( idAsyncNetwork::server.active )
    return idAsyncServer::GetClientIncomingRate(&idAsyncNetwork::server, clientNum);
  else
    return 0;
}

// FUNC: public: virtual float __thiscall idNetworkSystem::ServerGetClientIncomingPacketLoss(int)
double __thiscall idNetworkSystem::ServerGetClientIncomingPacketLoss(idNetworkSystem *this, int clientNum)
{
  if ( idAsyncNetwork::server.active )
    return idAsyncServer::GetClientIncomingPacketLoss(&idAsyncNetwork::server, clientNum);
  else
    return 0.0;
}

// FUNC: public: virtual void __thiscall idNetworkSystem::ClientSendReliableMessage(class idBitMsg const &)
void __thiscall idNetworkSystem::ClientSendReliableMessage(idNetworkSystem *this, const idBitMsg *msg)
{
  if ( idAsyncNetwork::client.active )
  {
    idAsyncClient::SendReliableGameMessage(&idAsyncNetwork::client, msg);
  }
  else if ( idAsyncNetwork::server.active )
  {
    idAsyncServer::LocalClientSendReliableMessage(&idAsyncNetwork::server, msg);
  }
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ClientGetPrediction(void)
int __thiscall idNetworkSystem::ClientGetPrediction(idNetworkSystem *this)
{
  if ( idAsyncNetwork::client.active )
    return idAsyncClient::GetPrediction(&idAsyncNetwork::client);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ClientGetTimeSinceLastPacket(void)
int __thiscall idNetworkSystem::ClientGetTimeSinceLastPacket(idNetworkSystem *this)
{
  if ( idAsyncNetwork::client.active )
    return idAsyncClient::GetTimeSinceLastPacket(&idAsyncNetwork::client);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ClientGetOutgoingRate(void)
int __thiscall idNetworkSystem::ClientGetOutgoingRate(idNetworkSystem *this)
{
  if ( idAsyncNetwork::client.active )
    return idAsyncClient::GetOutgoingRate(&idAsyncNetwork::client);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idNetworkSystem::ClientGetIncomingRate(void)
int __thiscall idNetworkSystem::ClientGetIncomingRate(idNetworkSystem *this)
{
  if ( idAsyncNetwork::client.active )
    return idAsyncClient::GetIncomingRate(&idAsyncNetwork::client);
  else
    return 0;
}

// FUNC: public: virtual float __thiscall idNetworkSystem::ClientGetIncomingPacketLoss(void)
double __thiscall idNetworkSystem::ClientGetIncomingPacketLoss(idNetworkSystem *this)
{
  if ( idAsyncNetwork::client.active )
    return idAsyncClient::GetIncomingPacketLoss(&idAsyncNetwork::client);
  else
    return 0.0;
}

// FUNC: public: virtual char const * __thiscall idNetworkSystem::GetServerAddress(void)
const char *__thiscall idNetworkSystem::GetServerAddress(idNetworkSystem *this)
{
  netadr_t v2; // [esp-Ch] [ebp-18h]
  netadr_t result; // [esp+0h] [ebp-Ch] BYREF

  if ( idAsyncNetwork::client.active )
  {
    v2 = *idAsyncClient::GetServerAddress(&idAsyncNetwork::client, &result);
    return Sys_NetAdrToString(v2);
  }
  else if ( idAsyncNetwork::server.active )
  {
    return Sys_NetAdrToString(idAsyncNetwork::server.serverAddress);
  }
  else
  {
    return &entityFilter;
  }
}

// FUNC: public: virtual char const * __thiscall idNetworkSystem::GetClientAddress(int)
const char *__thiscall idNetworkSystem::GetClientAddress(idNetworkSystem *this, int clientNum)
{
  netadr_t v3; // [esp-Ch] [ebp-18h]
  netadr_t result; // [esp+0h] [ebp-Ch] BYREF

  if ( !idAsyncNetwork::server.active )
    return &entityFilter;
  v3 = *idAsyncServer::GetClientAddress(&idAsyncNetwork::server, &result, clientNum);
  return Sys_NetAdrToString(v3);
}

// FUNC: public: virtual char const * __thiscall idNetworkSystem::GetClientGUID(int)
char *__thiscall idNetworkSystem::GetClientGUID(idNetworkSystem *this, unsigned int clientNum)
{
  if ( clientNum > 0x1F )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idNetworkSystem::GetClientGUID() - Invalid clientNum '%d'\n",
      clientNum);
    return 0;
  }
  else if ( idAsyncNetwork::server.active )
  {
    return idAsyncNetwork::server.clients[clientNum].guid;
  }
  else
  {
    return idAsyncNetwork::client.guids[clientNum];
  }
}
