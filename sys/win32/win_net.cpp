
// FUNC: char * __cdecl NET_ErrorString(void)
char *__cdecl NET_ErrorString()
{
  int Error; // eax
  char *result; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax

  Error = WSAGetLastError();
  if ( Error > 10051 )
  {
    if ( Error > 10091 )
    {
      if ( Error > 11001 )
      {
        v4 = Error - 11002;
        if ( !v4 )
          return "WSATRY_AGAIN";
        v5 = v4 - 1;
        if ( !v5 )
          return "WSANO_RECOVERY";
        if ( v5 == 1 )
          return "WSANO_DATA";
      }
      else
      {
        if ( Error == 11001 )
          return "WSAHOST_NOT_FOUND";
        v2 = Error - 10092;
        if ( !v2 )
          return "WSAVERNOTSUPPORTED";
        v3 = v2 - 1;
        if ( !v3 )
          return "WSANOTINITIALISED";
        if ( v3 == 8 )
          return "WSAEDISCON";
      }
      return "NO ERROR";
    }
    if ( Error == 10091 )
    {
      return "WSASYSNOTREADY";
    }
    else
    {
      switch ( Error )
      {
        case 10052:
          result = "WSAENETRESET";
          break;
        case 10053:
          result = "WSWSAECONNABORTEDAEINTR";
          break;
        case 10054:
          result = "WSAECONNRESET";
          break;
        case 10055:
          result = "WSAENOBUFS";
          break;
        case 10056:
          result = "WSAEISCONN";
          break;
        case 10057:
          result = "WSAENOTCONN";
          break;
        case 10058:
          result = "WSAESHUTDOWN";
          break;
        case 10059:
          result = "WSAETOOMANYREFS";
          break;
        case 10060:
          result = "WSAETIMEDOUT";
          break;
        case 10061:
          result = "WSAECONNREFUSED";
          break;
        case 10062:
          result = "WSAELOOP";
          break;
        case 10063:
          result = "WSAENAMETOOLONG";
          break;
        case 10064:
          result = "WSAEHOSTDOWN";
          break;
        default:
          return "NO ERROR";
      }
    }
  }
  else if ( Error == 10051 )
  {
    return "WSAENETUNREACH";
  }
  else
  {
    switch ( Error )
    {
      case 10004:
        result = "WSAEINTR";
        break;
      case 10009:
        result = "WSAEBADF";
        break;
      case 10013:
        result = "WSAEACCES";
        break;
      case 10014:
        result = "WSAEFAULT";
        break;
      case 10022:
        result = "WSAEINVAL";
        break;
      case 10024:
        result = "WSAEMFILE";
        break;
      case 10035:
        result = "WSAEWOULDBLOCK";
        break;
      case 10036:
        result = "WSAEINPROGRESS";
        break;
      case 10037:
        result = "WSAEALREADY";
        break;
      case 10038:
        result = "WSAENOTSOCK";
        break;
      case 10039:
        result = "WSAEDESTADDRREQ";
        break;
      case 10040:
        result = "WSAEMSGSIZE";
        break;
      case 10041:
        result = "WSAEPROTOTYPE";
        break;
      case 10042:
        result = "WSAENOPROTOOPT";
        break;
      case 10043:
        result = "WSAEPROTONOSUPPORT";
        break;
      case 10044:
        result = "WSAESOCKTNOSUPPORT";
        break;
      case 10045:
        result = "WSAEOPNOTSUPP";
        break;
      case 10046:
        result = "WSAEPFNOSUPPORT";
        break;
      case 10047:
        result = "WSAEAFNOSUPPORT";
        break;
      case 10048:
        result = "WSAEADDRINUSE";
        break;
      case 10049:
        result = "WSAEADDRNOTAVAIL";
        break;
      case 10050:
        result = "WSAENETDOWN";
        break;
      default:
        return "NO ERROR";
    }
  }
  return result;
}

// FUNC: void __cdecl Net_NetadrToSockadr(struct netadr_t const *,struct sockaddr *)
void __cdecl Net_NetadrToSockadr(const netadr_t *a, sockaddr *s)
{
  netadrtype_t type; // eax

  *(_DWORD *)&s->sa_family = 0;
  *(_DWORD *)&s->sa_data[2] = 0;
  *(_DWORD *)&s->sa_data[6] = 0;
  *(_DWORD *)&s->sa_data[10] = 0;
  type = a->type;
  if ( a->type == NA_BROADCAST )
  {
    s->sa_family = 2;
    *(_DWORD *)&s->sa_data[2] = -1;
    *(_WORD *)s->sa_data = htons(a->port);
  }
  else
  {
    if ( type == NA_IP || type == NA_LOOPBACK )
    {
      s->sa_family = 2;
      *(_DWORD *)&s->sa_data[2] = *(_DWORD *)a->ip;
    }
    *(_WORD *)s->sa_data = htons(a->port);
  }
}

// FUNC: void __cdecl Net_SockadrToNetadr(struct sockaddr *,struct netadr_t *)
void __cdecl Net_SockadrToNetadr(sockaddr *s, netadr_t *a)
{
  u_long v2; // esi

  if ( s->sa_family == 2 )
  {
    v2 = *(_DWORD *)&s->sa_data[2];
    *(_DWORD *)a->ip = v2;
    a->port = htons(*(_WORD *)s->sa_data);
    a->type = 2 * (ntohl(v2) != 2130706433) + 1;
  }
}

// FUNC: bool __cdecl Net_WaitForUDPPacket(int,int)
bool __cdecl Net_WaitForUDPPacket(int netSocket, int timeout)
{
  int v3; // eax
  int *v4; // eax
  int v5; // esi
  char *v6; // eax
  timeval tv; // [esp+0h] [ebp-10Ch] BYREF
  fd_set set; // [esp+8h] [ebp-104h] BYREF

  if ( !netSocket )
    return 0;
  if ( timeout <= 0 )
    return 1;
  tv.tv_usec = 1000 * timeout;
  set.fd_array[0] = netSocket;
  set.fd_count = 1;
  tv.tv_sec = 0;
  v3 = select(netSocket + 1, &set, 0, 0, &tv);
  if ( v3 != -1 )
    return v3 != 0;
  v4 = _errno();
  v5 = *(_DWORD *)common.type;
  v6 = strerror(*v4);
  (*(void (**)(netadrtype_t, const char *, ...))(v5 + 132))(common.type, "Net_WaitForUPDPacket select(): %s\n", v6);
  return 0;
}

// FUNC: void __cdecl Net_SendUDPPacket(int,int,void const *,struct netadr_t)
void __cdecl Net_SendUDPPacket(int netSocket, int length, const void *data, netadr_t to)
{
  int v4; // eax
  int Error; // eax
  const char *v6; // eax
  sockaddr addr; // [esp+4h] [ebp-410h] BYREF
  char buf[1024]; // [esp+14h] [ebp-400h] BYREF

  if ( netSocket )
  {
    Net_NetadrToSockadr(&to, &addr);
    if ( usingSocks && to.type == NA_IP )
    {
      *(_WORD *)&socksBuf[8] = *(_WORD *)addr.sa_data;
      *(_DWORD *)&socksBuf[4] = *(_DWORD *)&addr.sa_data[2];
      socksBuf[0] = 0;
      socksBuf[1] = 0;
      socksBuf[2] = 0;
      socksBuf[3] = 1;
      qmemcpy(&socksBuf[10], data, length);
      v4 = sendto(netSocket, socksBuf, length + 10, 0, &socksRelayAddr, 16);
    }
    else
    {
      v4 = sendto(netSocket, (const char *)data, length, 0, &addr, 16);
    }
    if ( v4 == -1 )
    {
      Error = WSAGetLastError();
      if ( Error != 10035 && (Error != 10049 || to.type != NA_BROADCAST) )
      {
        v6 = NET_ErrorString();
        sprintf(buf, "Net_SendUDPPacket: %s\n", v6);
        OutputDebugStringA(buf);
      }
    }
    else
    {
      net_bytesOut += v4;
      net_clientBytesOut += v4;
      net_serverBytesOut += v4;
    }
  }
}

// FUNC: struct netadr_t __cdecl Net_GetInterface(int)
netadr_t *__cdecl Net_GetInterface(netadr_t *result, int index)
{
  bool v2; // zf
  netadr_t *v3; // eax
  u_long netAddress_4; // [esp+8h] [ebp-Ch]
  u_short netAddress_8; // [esp+Ch] [ebp-8h]

  netAddress_4 = htonl(*(&netint + 2 * index));
  netAddress_8 = htons(0);
  v2 = ntohl(netAddress_4) == 2130706433;
  v3 = result;
  result->type = 2 * !v2 + 1;
  *(_DWORD *)result->ip = netAddress_4;
  *(_DWORD *)&result->port = netAddress_8;
  return v3;
}

// FUNC: void __cdecl Sys_InitNetworking(void)
void __cdecl Sys_InitNetworking()
{
  int v0; // eax
  int v1; // ecx
  _IP_ADAPTER_INFO *v2; // edi
  ULONG AdaptersInfo; // eax
  int v4; // eax
  unsigned int v5; // eax
  unsigned int v6; // eax
  u_long v7; // eax
  int v8; // ecx
  _IP_ADAPTER_INFO *v9; // esi
  _IP_ADDR_STRING *p_IpAddressList; // ebx
  unsigned int v11; // eax
  unsigned int v12; // eax
  u_long v13; // ebp
  int v14; // eax
  bool foundloopback; // [esp+3h] [ebp-11h]
  _IP_ADAPTER_INFO *pAdapterInfo; // [esp+4h] [ebp-10h]
  unsigned int ulOutBufLen; // [esp+8h] [ebp-Ch] BYREF
  _IP_ADAPTER_INFO *pAdapter; // [esp+Ch] [ebp-8h]
  unsigned int ip_a; // [esp+10h] [ebp-4h]

  v0 = WSAStartup(0x101u, &winsockdata);
  if ( v0 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "WARNING: Winsock initialization failed, returned %d\n",
      v0);
    return;
  }
  v1 = *(_DWORD *)common.type;
  winsockInitialized = 1;
  (*(void (__cdecl **)(netadrtype_t, const char *))(v1 + 124))(common.type, "Winsock Initialized\n");
  num_interfaces = 0;
  foundloopback = 0;
  v2 = (_IP_ADAPTER_INFO *)malloc(0x280u);
  pAdapterInfo = v2;
  if ( !v2 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "Sys_InitNetworking: Couldn't malloc( %d )",
      640);
  ulOutBufLen = 640;
  if ( GetAdaptersInfo(v2, &ulOutBufLen) == 111 )
  {
    free(v2);
    pAdapterInfo = (_IP_ADAPTER_INFO *)malloc(ulOutBufLen);
    if ( !pAdapterInfo )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
        common.type,
        "Sys_InitNetworking: Couldn't malloc( %ld )",
        ulOutBufLen);
    v2 = pAdapterInfo;
  }
  AdaptersInfo = GetAdaptersInfo(v2, &ulOutBufLen);
  if ( AdaptersInfo )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Sys_InitNetworking: GetAdaptersInfo failed (%ld).\n",
      AdaptersInfo);
LABEL_11:
    v4 = num_interfaces;
    goto LABEL_12;
  }
  v9 = v2;
  pAdapter = v2;
  if ( !v2 )
    goto LABEL_11;
  while ( 1 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Found interface: %s %s - ",
      v9->AdapterName,
      v9->Description);
    p_IpAddressList = &v9->IpAddressList;
    if ( v9 != (_IP_ADAPTER_INFO *)-428 )
      break;
    v4 = num_interfaces;
LABEL_26:
    pAdapter = v9->Next;
    if ( !pAdapter )
    {
      if ( foundloopback )
      {
LABEL_14:
        free(v2);
        return;
      }
LABEL_12:
      if ( v4 < 32 )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "Sys_InitNetworking: adding loopback interface\n");
        v5 = inet_addr("127.0.0.1");
        *(&netint + 2 * num_interfaces) = ntohl(v5);
        v6 = inet_addr("255.0.0.0");
        v7 = ntohl(v6);
        v8 = num_interfaces;
        dword_1135C3DC[2 * num_interfaces] = v7;
        num_interfaces = v8 + 1;
      }
      goto LABEL_14;
    }
    v9 = pAdapter;
  }
  while ( 1 )
  {
    if ( !idStr::Icmp("127.0.0.1", p_IpAddressList->IpAddress.String) )
      foundloopback = 1;
    v11 = inet_addr(p_IpAddressList->IpAddress.String);
    ip_a = ntohl(v11);
    v12 = inet_addr(p_IpAddressList->IpMask.String);
    v13 = ntohl(v12);
    if ( v13 )
      break;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%s NULL netmask - skipped\n",
      &p_IpAddressList->IpAddress);
    v4 = num_interfaces;
LABEL_24:
    p_IpAddressList = p_IpAddressList->Next;
    if ( !p_IpAddressList )
    {
      v9 = pAdapter;
      v2 = pAdapterInfo;
      goto LABEL_26;
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%s/%s\n",
    &p_IpAddressList->IpAddress,
    &p_IpAddressList->IpMask);
  v14 = num_interfaces;
  *(&netint + 2 * num_interfaces) = ip_a;
  dword_1135C3DC[2 * v14] = v13;
  v4 = v14 + 1;
  num_interfaces = v4;
  if ( v4 < 32 )
    goto LABEL_24;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "Sys_InitNetworking: MAX_INTERFACES(%d) hit.\n",
    32);
  free(pAdapterInfo);
}

// FUNC: char const * __cdecl Sys_NetAdrToString(struct netadr_t)
char *__cdecl Sys_NetAdrToString(netadr_t a)
{
  int v1; // esi
  char *v2; // esi

  v1 = index_0 << 6;
  index_0 = ((_BYTE)index_0 + 1) & 3;
  v2 = &buf_0[0][v1];
  if ( a.type == NA_LOOPBACK )
  {
    if ( a.port )
      idStr::snPrintf(v2, 64, "localhost:%i", a.port);
    else
      idStr::snPrintf(v2, 64, "localhost");
    return v2;
  }
  else
  {
    if ( a.type == NA_IP )
      idStr::snPrintf(v2, 64, "%i.%i.%i.%i:%i", a.ip[0], a.ip[1], a.ip[2], a.ip[3], a.port);
    return v2;
  }
}

// FUNC: bool __cdecl Sys_IsLANAddress(struct netadr_t)
char __cdecl Sys_IsLANAddress(netadr_t adr)
{
  char result; // al
  u_long v2; // eax
  int v3; // edx

  result = adr.type;
  if ( adr.type != NA_LOOPBACK )
  {
    if ( adr.type == NA_IP )
    {
      if ( num_interfaces && (v2 = ntohl(*(u_long *)adr.ip), v3 = 0, num_interfaces > 0) )
      {
        while ( (dword_1135C3DC[2 * v3] & *(&netint + 2 * v3)) != (v2 & dword_1135C3DC[2 * v3]) )
        {
          if ( ++v3 >= num_interfaces )
            return 0;
        }
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// FUNC: bool __cdecl Sys_CompareNetAdrBase(struct netadr_t,struct netadr_t)
char __cdecl Sys_CompareNetAdrBase(netadr_t a, netadr_t b)
{
  if ( a.type == b.type )
  {
    if ( a.type == NA_LOOPBACK )
      return 1;
    if ( a.type == NA_IP )
    {
      if ( a.ip[0] == b.ip[0] && a.ip[1] == b.ip[1] && a.ip[2] == b.ip[2] && a.ip[3] == b.ip[3] )
        return 1;
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "Sys_CompareNetAdrBase: bad address type\n");
    }
  }
  return 0;
}

// FUNC: public: __thiscall idPort::idPort(void)
void __thiscall idPort::idPort(idPort *this)
{
  this->netSocket = 0;
  this->port = 0;
  this->silent = 0;
}

// FUNC: Net_ExtractPort
bool __usercall Net_ExtractPort@<al>(const char *src@<esi>, char *buf@<ebx>, int bufsize@<edi>, int *port)
{
  signed int v4; // eax
  char *v5; // eax
  char *v7; // [esp+0h] [ebp-Ch]
  const char *v8; // [esp+4h] [ebp-8h]
  size_t v9; // [esp+8h] [ebp-4h]

  strncpy(v7, v8, v9);
  v4 = strlen(src);
  if ( bufsize - 1 < v4 )
    v4 = bufsize - 1;
  buf[v4] = 0;
  v5 = strchr(buf, 58);
  if ( !v5 )
    return 0;
  *v5 = 0;
  *port = strtol(v5 + 1, 0, 10);
  return *_errno() != 34;
}

// FUNC: Net_StringToSockaddr
char __usercall Net_StringToSockaddr@<al>(char *s@<eax>, sockaddr *sadr, bool doDNSResolve)
{
  char v4; // al
  unsigned int v5; // eax
  unsigned int v7; // eax
  struct hostent *v8; // edi
  u_short v9; // [esp-4h] [ebp-118h]
  int port; // [esp+10h] [ebp-104h] BYREF
  char buf[256]; // [esp+14h] [ebp-100h] BYREF

  *(_DWORD *)&sadr->sa_family = 0;
  *(_DWORD *)&sadr->sa_data[2] = 0;
  *(_DWORD *)&sadr->sa_data[6] = 0;
  *(_DWORD *)&sadr->sa_data[10] = 0;
  sadr->sa_family = 2;
  *(_WORD *)sadr->sa_data = 0;
  v4 = *s;
  if ( v4 >= 48 && v4 <= 57 )
  {
    v5 = inet_addr(s);
    if ( v5 != -1 )
    {
      *(_DWORD *)&sadr->sa_data[2] = v5;
      return 1;
    }
    if ( Net_ExtractPort(s, buf, 256, &port) )
    {
      v7 = inet_addr(buf);
      if ( v7 != -1 )
      {
        v9 = port;
        *(_DWORD *)&sadr->sa_data[2] = v7;
        *(_WORD *)sadr->sa_data = htons(v9);
        return 1;
      }
    }
    return 0;
  }
  if ( doDNSResolve )
  {
    v8 = gethostbyname(s);
    if ( !v8 )
    {
      if ( !Net_ExtractPort(s, buf, 256, &port) )
        return 0;
      v8 = gethostbyname(buf);
      if ( !v8 )
        return 0;
      *(_WORD *)sadr->sa_data = htons(port);
    }
    *(_DWORD *)&sadr->sa_data[2] = **(_DWORD **)v8->h_addr_list;
  }
  return 1;
}

// FUNC: int __cdecl NET_IPSocket(char const *,int)
SOCKET __cdecl NET_IPSocket(char *net_interface, int port)
{
  SOCKET v2; // eax
  SOCKET v3; // esi
  int v4; // esi
  char *v5; // eax
  int v7; // esi
  char *v8; // eax
  int v9; // esi
  char *v10; // eax
  int v11; // edi
  char *v12; // eax
  unsigned int _true; // [esp+Ch] [ebp-18h] BYREF
  int i; // [esp+10h] [ebp-14h] BYREF
  sockaddr_in address; // [esp+14h] [ebp-10h] BYREF

  _true = 1;
  i = 1;
  if ( net_interface )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "Opening IP socket: %s:%i\n",
      net_interface,
      port);
  else
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "Opening IP socket: localhost:%i\n",
      port);
  v2 = socket(2, 2, 17);
  v3 = v2;
  if ( v2 == -1 )
  {
    if ( WSAGetLastError() != 10047 )
    {
      v4 = *(_DWORD *)common.type;
      v5 = NET_ErrorString();
      (*(void (**)(netadrtype_t, const char *, ...))(v4 + 124))(
        common.type,
        "WARNING: UDP_OpenSocket: socket: %s\n",
        v5);
    }
    return 0;
  }
  else if ( ioctlsocket(v2, -2147195266, &_true) == -1 )
  {
    v7 = *(_DWORD *)common.type;
    v8 = NET_ErrorString();
    (*(void (**)(netadrtype_t, const char *, ...))(v7 + 124))(
      common.type,
      "WARNING: UDP_OpenSocket: ioctl FIONBIO: %s\n",
      v8);
    return 0;
  }
  else if ( setsockopt(v3, 0xFFFF, 32, (const char *)&i, 4) == -1 )
  {
    v9 = *(_DWORD *)common.type;
    v10 = NET_ErrorString();
    (*(void (**)(netadrtype_t, const char *, ...))(v9 + 124))(
      common.type,
      "WARNING: UDP_OpenSocket: setsockopt SO_BROADCAST: %s\n",
      v10);
    return 0;
  }
  else
  {
    if ( net_interface && *net_interface && idStr::Icmp(net_interface, "localhost") )
      Net_StringToSockaddr(net_interface, (sockaddr *)&address, 1);
    else
      address.sin_addr.S_un.S_addr = 0;
    if ( port == -1 )
      address.sin_port = 0;
    else
      address.sin_port = htons(port);
    address.sin_family = 2;
    if ( bind(v3, (const struct sockaddr *)&address, 16) == -1 )
    {
      v11 = *(_DWORD *)common.type;
      v12 = NET_ErrorString();
      (*(void (**)(netadrtype_t, const char *, ...))(v11 + 124))(
        common.type,
        "WARNING: UDP_OpenSocket: bind: %s\n",
        v12);
      closesocket(v3);
      return 0;
    }
    else
    {
      return v3;
    }
  }
}

// FUNC: bool __cdecl Net_GetUDPPacket(int,struct netadr_t &,char *,int &,int)
char __cdecl Net_GetUDPPacket(int netSocket, netadr_t *net_from, char *data, int *size, int maxSize)
{
  int v5; // ebp
  int Error; // eax
  const char *v7; // eax
  netadr_t *v9; // esi
  char *v10; // eax
  int fromlen; // [esp+10h] [ebp-414h] BYREF
  sockaddr from; // [esp+14h] [ebp-410h] BYREF
  char buf[1024]; // [esp+24h] [ebp-400h] BYREF

  if ( !netSocket )
    return 0;
  fromlen = 16;
  v5 = recvfrom(netSocket, data, maxSize, 0, &from, &fromlen);
  if ( v5 == -1 )
  {
    Error = WSAGetLastError();
    if ( Error != 10035 && Error != 10054 )
    {
      v7 = NET_ErrorString();
      sprintf(buf, "Net_GetUDPPacket: %s\n", v7);
      OutputDebugStringA(buf);
      return 0;
    }
    return 0;
  }
  if ( netSocket == ip_socket )
  {
    *(_DWORD *)&from.sa_data[6] = 0;
    *(_DWORD *)&from.sa_data[10] = 0;
  }
  if ( usingSocks && netSocket == ip_socket && !memcmp(&from, &socksRelayAddr, fromlen) )
  {
    if ( v5 < 10 || *data || data[1] || data[2] || data[3] != 1 )
      return 0;
    v9 = net_from;
    net_from->type = NA_IP;
    *(_DWORD *)net_from->ip = *((_DWORD *)data + 1);
    net_from->port = *((_WORD *)data + 4);
    memmove((unsigned __int8 *)data, (unsigned __int8 *)data + 10, v5 - 10);
  }
  else
  {
    v9 = net_from;
    Net_SockadrToNetadr(&from, net_from);
  }
  if ( v5 == maxSize )
  {
    v10 = Sys_NetAdrToString(*v9);
    sprintf(buf, "Net_GetUDPPacket: oversize packet from %s\n", v10);
    OutputDebugStringA(buf);
    return 0;
  }
  *size = v5;
  net_bytesIn += v5;
  net_serverBytesIn += *size;
  net_clientBytesIn += *size;
  return 1;
}

// FUNC: bool __cdecl Sys_StringToNetAdr(char const *,struct netadr_t *,bool)
char __cdecl Sys_StringToNetAdr(char *s, netadr_t *a, bool doDNSResolve)
{
  char result; // al
  u_long v4; // edi
  u_short v5; // [esp-Ch] [ebp-1Ch]
  sockaddr sadr; // [esp+0h] [ebp-10h] BYREF

  result = Net_StringToSockaddr(s, &sadr, doDNSResolve);
  if ( result )
  {
    if ( sadr.sa_family == 2 )
    {
      v4 = *(_DWORD *)&sadr.sa_data[2];
      v5 = *(_WORD *)sadr.sa_data;
      *(_DWORD *)a->ip = *(_DWORD *)&sadr.sa_data[2];
      a->port = htons(v5);
      a->type = 2 * (ntohl(v4) != 2130706433) + 1;
    }
    return 1;
  }
  return result;
}

// FUNC: public: bool __thiscall idPort::GetPacket(struct netadr_t &,void *,int &,int)
char __thiscall idPort::GetPacket(idPort *this, netadr_t *from, char *data, int *size, int maxSize)
{
  int *v5; // esi
  bool i; // bl
  int integerValue; // edi
  udpMsg_s *v9; // ebx
  idUDPLag *v10; // eax
  udpMsg_s *recieveLast; // ecx
  int v12; // esi
  idUDPLag *v13; // eax
  udpMsg_s *recieveFirst; // ebx
  idUDPLag *v16; // eax
  idUDPLag *v17; // eax
  idUDPLag *v18; // eax
  udpMsg_s *free; // edx

  v5 = size;
  for ( i = Net_GetUDPPacket(this->netSocket, from, data, size, maxSize);
        i;
        i = Net_GetUDPPacket(this->netSocket, from, data, v5, maxSize) )
  {
    integerValue = net_forceDrop.internalVar->integerValue;
    if ( integerValue <= 0 || rand() >= 0x7FFF * integerValue / 100 )
    {
      ++this->packetsRead;
      this->bytesRead += *v5;
      if ( net_forceLatency.internalVar->integerValue <= 0 )
        break;
      v9 = idBlockAlloc<udpMsg_s,64,30>::Alloc(&udpPorts[this->port]->udpMsgAllocator);
      qmemcpy(v9, data, *v5);
      v9->size = *size;
      v9->address = *from;
      v9->time = Sys_Milliseconds();
      v9->next = 0;
      v10 = udpPorts[this->port];
      recieveLast = v10->recieveLast;
      if ( recieveLast )
        recieveLast->next = v9;
      else
        v10->recieveFirst = v9;
      v5 = size;
      udpPorts[this->port]->recieveLast = v9;
    }
  }
  v12 = net_forceLatency.internalVar->integerValue;
  if ( v12 <= 0 )
  {
    v13 = udpPorts[this->port];
    if ( !v13 || !v13->recieveFirst )
      return i;
  }
  recieveFirst = udpPorts[this->port]->recieveFirst;
  if ( !recieveFirst || recieveFirst->time > Sys_Milliseconds() - v12 )
    return 0;
  qmemcpy(data, recieveFirst, recieveFirst->size);
  *size = recieveFirst->size;
  *from = recieveFirst->address;
  v16 = udpPorts[this->port];
  v16->recieveFirst = v16->recieveFirst->next;
  v17 = udpPorts[this->port];
  if ( !v17->recieveFirst )
    v17->recieveLast = 0;
  v18 = udpPorts[this->port];
  free = (udpMsg_s *)v18->udpMsgAllocator.free;
  v18 = (idUDPLag *)((char *)v18 + 16);
  recieveFirst[-1].next = free;
  --v18->recieveLast;
  v18->sendLast = (udpMsg_s *)((char *)recieveFirst - 4);
  return 1;
}

// FUNC: public: bool __thiscall idPort::GetPacketBlocking(struct netadr_t &,void *,int &,int,int)
bool __thiscall idPort::GetPacketBlocking(
        idPort *this,
        netadr_t *from,
        char *data,
        int *size,
        int maxSize,
        int timeout)
{
  Net_WaitForUDPPacket(this->netSocket, timeout);
  return idPort::GetPacket(this, from, data, size, maxSize) != 0;
}

// FUNC: public: void __thiscall idPort::SendPacket(struct netadr_t,void const *,int)
void __thiscall idPort::SendPacket(idPort *this, netadr_t to, const void *data, int size)
{
  int integerValue; // esi
  idUDPLag *v6; // eax
  udpMsg_s *v7; // ebx
  idUDPLag *v8; // eax
  udpMsg_s *sendLast; // ecx
  udpMsg_s *i; // esi
  int v11; // ebx
  idUDPLag *v12; // eax
  idUDPLag *v13; // eax
  idUDPLag *v14; // eax
  idBlockAlloc<udpMsg_s,64,30>::element_s *free; // ecx
  udpMsg_s **p_next; // esi

  ++this->packetsWritten;
  this->bytesWritten += size;
  if ( !this->silent )
  {
    integerValue = net_forceDrop.internalVar->integerValue;
    if ( integerValue <= 0 || rand() >= 0x7FFF * integerValue / 100 )
    {
      if ( net_forceLatency.internalVar->integerValue > 0 || (v6 = udpPorts[this->port]) != 0 && v6->sendFirst )
      {
        v7 = idBlockAlloc<udpMsg_s,64,30>::Alloc(&udpPorts[this->port]->udpMsgAllocator);
        qmemcpy(v7, data, size);
        v7->address.type = to.type;
        v7->size = size;
        *(_DWORD *)v7->address.ip = *(_DWORD *)to.ip;
        *(_DWORD *)&v7->address.port = *(_DWORD *)&to.port;
        v7->time = Sys_Milliseconds();
        v7->next = 0;
        v8 = udpPorts[this->port];
        sendLast = v8->sendLast;
        if ( sendLast )
          sendLast->next = v7;
        else
          v8->sendFirst = v7;
        udpPorts[this->port]->sendLast = v7;
        for ( i = udpPorts[this->port]->sendFirst; i; i = udpPorts[this->port]->sendFirst )
        {
          v11 = net_forceLatency.internalVar->integerValue;
          if ( i->time > Sys_Milliseconds() - v11 )
            break;
          Net_SendUDPPacket(this->netSocket, i->size, i, i->address);
          v12 = udpPorts[this->port];
          v12->sendFirst = v12->sendFirst->next;
          v13 = udpPorts[this->port];
          if ( !v13->sendFirst )
            v13->sendLast = 0;
          v14 = udpPorts[this->port];
          free = v14->udpMsgAllocator.free;
          v14 = (idUDPLag *)((char *)v14 + 16);
          p_next = &i[-1].next;
          *p_next = (udpMsg_s *)free;
          --v14->recieveLast;
          v14->sendLast = (udpMsg_s *)p_next;
        }
      }
      else
      {
        Net_SendUDPPacket(this->netSocket, size, data, to);
      }
    }
  }
}

// FUNC: public: __thiscall idUDPLag::~idUDPLag(void)
void __thiscall idUDPLag::~idUDPLag(idUDPLag *this)
{
  idBlockAlloc<udpMsg_s,64,30> *p_udpMsgAllocator; // esi

  p_udpMsgAllocator = &this->udpMsgAllocator;
  idBlockAlloc<udpMsg_s,64,30>::Shutdown(&this->udpMsgAllocator);
  idBlockAlloc<udpMsg_s,64,30>::Shutdown(p_udpMsgAllocator);
}

// FUNC: public: bool __thiscall idPort::InitForPort(int)
char __thiscall idPort::InitForPort(idPort *this, int portNumber)
{
  int v3; // eax
  idUDPLag *v5; // eax
  int len; // [esp+Ch] [ebp-14h] BYREF
  sockaddr_in address; // [esp+10h] [ebp-10h] BYREF

  len = 16;
  v3 = NET_IPSocket(net_ip.internalVar->value, portNumber);
  this->netSocket = v3;
  if ( v3 > 0 )
  {
    this->port = portNumber;
    if ( portNumber == -1 )
    {
      getsockname(v3, (struct sockaddr *)&address, &len);
      this->port = address.sin_port;
    }
    v5 = (idUDPLag *)Memory::Allocate(0x20u);
    if ( v5 )
    {
      v5->udpMsgAllocator.blocks = 0;
      v5->udpMsgAllocator.free = 0;
      v5->udpMsgAllocator.active = 0;
      v5->udpMsgAllocator.total = 0;
      v5->recieveLast = 0;
      v5->recieveFirst = 0;
      v5->sendLast = 0;
      v5->sendFirst = 0;
    }
    else
    {
      v5 = 0;
    }
    udpPorts[this->port] = v5;
    return 1;
  }
  else
  {
    this->netSocket = 0;
    this->port = 0;
    return 0;
  }
}

// FUNC: public: void __thiscall idPort::Close(void)
void __thiscall idPort::Close(idPort *this)
{
  int port; // eax
  idUDPLag *v3; // edi

  if ( this->netSocket )
  {
    port = this->port;
    v3 = udpPorts[port];
    if ( v3 )
    {
      idUDPLag::~idUDPLag(udpPorts[port]);
      Memory::Free(v3);
      udpPorts[this->port] = 0;
    }
    closesocket(this->netSocket);
    this->netSocket = 0;
    this->port = 0;
  }
}

// FUNC: public: __thiscall idPort::~idPort(void)
// attributes: thunk
void __thiscall idPort::~idPort(idPort *this)
{
  idPort::Close(this);
}
