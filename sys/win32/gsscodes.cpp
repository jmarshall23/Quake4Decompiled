
// FUNC: bool __cdecl GSS_GetSecurityCode(void)
char __cdecl GSS_GetSecurityCode()
{
  unsigned int v0; // esi
  int v1; // ebp
  int v3; // eax
  char v4; // cl
  char *v5; // eax
  u_short v6; // di
  struct hostent *v7; // eax
  SOCKET v8; // ebx
  u_short v9; // dx
  unsigned __int16 v10; // ax
  bool v11; // zf
  char *v12; // edi
  signed int v13; // ebp
  int v14; // eax
  int v15; // ebx
  signed int v16; // esi
  int i; // ecx
  char *v18; // eax
  char *v19; // ecx
  HANDLE CurrentProcess; // eax
  unsigned __int8 *v21; // [esp-18h] [ebp-260h]
  bool parsedHTTPHeader; // [esp+Bh] [ebp-23Dh]
  signed int size; // [esp+Ch] [ebp-23Ch]
  unsigned int connectSocket; // [esp+10h] [ebp-238h]
  unsigned int parm; // [esp+18h] [ebp-230h] BYREF
  unsigned __int8 *startFunc; // [esp+1Ch] [ebp-22Ch]
  int v27; // [esp+20h] [ebp-228h]
  sockaddr_in address; // [esp+24h] [ebp-224h] BYREF
  unsigned int output; // [esp+34h] [ebp-214h] BYREF
  char hostName[128]; // [esp+38h] [ebp-210h] BYREF
  WSAData wsaData; // [esp+B8h] [ebp-190h] BYREF

  v0 = (char *)GSSEndData - (char *)((char *)GSSStartData + 5) + 6;
  v1 = 0;
  parm = 0;
  startFunc = (unsigned __int8 *)GSSStartData + 5;
  size = v0;
  if ( v0 > 0x20000 )
    return 0;
  v3 = 0;
  do
  {
    v4 = GSSSecurityTag998.mSecurityID[v3];
    hostName[v3++] = v4;
  }
  while ( v4 );
  v5 = strchr(hostName, 58);
  if ( v5 )
  {
    *v5 = 0;
    v6 = atol(v5 + 1);
  }
  else
  {
    v6 = GSS_PORTS[0];
  }
  if ( WSAStartup(0x101u, &wsaData) )
    return 0;
  v7 = gethostbyname(hostName);
  if ( !v7 )
  {
    WSACleanup();
    return 0;
  }
  if ( v7->h_addrtype != 2
    || (address.sin_family = 2,
        address.sin_addr.S_un.S_addr = **(_DWORD **)v7->h_addr_list,
        address.sin_port = htons(v6),
        v8 = socket(2, 1, 6),
        connectSocket = v8,
        v8 == -1) )
  {
LABEL_16:
    WSACleanup();
    return 0;
  }
  if ( ioctlsocket(v8, -2147195266, &parm) )
    goto LABEL_15;
  if ( GSS_PORTS[0] )
  {
    do
    {
      if ( connect(v8, (const struct sockaddr *)&address, 16) != -1 )
        break;
      v9 = *(&hostshort + 2 * v1++);
      v10 = htons(v9);
      v11 = GSS_PORTS[v1] == 0;
      address.sin_port = v10;
    }
    while ( !v11 );
  }
  if ( !GSS_PORTS[v1] )
  {
LABEL_15:
    closesocket(v8);
    goto LABEL_16;
  }
  send(v8, GSSSecurityTag999.mSecurityID, strlen(GSSSecurityTag999.mSecurityID), 0);
  v12 = (char *)malloc((char *)GSSEndData - (char *)((char *)GSSStartData + 5) + 1030);
  parsedHTTPHeader = 0;
  v13 = 0;
  v27 = Sys_Milliseconds() + 10000;
  while ( Sys_Milliseconds() <= v27 )
  {
    v14 = recv(v8, &v12[v13], size - v13 + 1023, 2);
    if ( !v14 )
      goto LABEL_53;
    v15 = recv(v8, &v12[v13], v14, 0);
    v13 += v15;
    v12[v13] = 0;
    if ( v15 < 4 )
    {
      v8 = connectSocket;
LABEL_53:
      if ( !parsedHTTPHeader )
        goto LABEL_23;
      goto LABEL_47;
    }
    if ( !parsedHTTPHeader )
    {
      if ( idStr::Cmpn(v12, "HTTP", 4) )
        goto LABEL_22;
      v16 = 0;
      if ( v13 > 0 )
      {
        for ( i = 2 - (_DWORD)v12; ; i = 2 - (_DWORD)v12 )
        {
          v18 = &v12[v16];
          v19 = &v12[v16 + i];
          if ( (int)(v19 + 2) <= v15 && *v18 == 13 && v12[v16 + 1] == 10 && v12[v16 + 2] == 13 && v12[v16 + 3] == 10 )
          {
            v16 += 4;
            goto LABEL_44;
          }
          if ( (int)v19 <= v15 && *v18 == 10 && v12[v16 + 1] == 10 )
            break;
          if ( ++v16 >= v13 )
            goto LABEL_44;
        }
        v16 += 2;
      }
LABEL_44:
      if ( v16 > v13 )
      {
LABEL_22:
        v8 = connectSocket;
        goto LABEL_23;
      }
      parsedHTTPHeader = 1;
      memmove((unsigned __int8 *)v12, (unsigned __int8 *)&v12[v16], size - v16 + 1023);
      v13 -= v16;
    }
    v8 = connectSocket;
LABEL_47:
    if ( v13 >= size )
    {
      v0 = (char *)GSSEndData - (char *)((char *)GSSStartData + 5) + 6;
      break;
    }
LABEL_23:
    v0 = (char *)GSSEndData - (char *)((char *)GSSStartData + 5) + 6;
  }
  if ( v13 == v0 )
  {
    v21 = startFunc;
    CurrentProcess = GetCurrentProcess();
    WriteProcessMemory(CurrentProcess, v21, v12, v13, &output);
  }
  free(v12);
  return 1;
}

// FUNC: GSS_GetEncryption
bool __cdecl GSS_GetEncryption()
{
  int v0; // esi
  int v1; // eax
  char v2; // cl
  char *v3; // eax
  u_short v4; // di
  struct hostent *v5; // eax
  SOCKET v7; // ebx
  u_short v8; // dx
  unsigned __int16 v9; // ax
  bool v10; // zf
  unsigned __int8 *v11; // ebp
  int v12; // edi
  int v13; // eax
  int v14; // ebx
  int v15; // esi
  int i; // ecx
  unsigned __int8 *v17; // eax
  unsigned __int8 *v18; // ecx
  unsigned __int8 *v19; // eax
  bool parsedHTTPHeader; // [esp+Bh] [ebp-235h]
  unsigned int connectSocket; // [esp+Ch] [ebp-234h]
  int wantedSize; // [esp+14h] [ebp-22Ch]
  unsigned int parm; // [esp+18h] [ebp-228h] BYREF
  int v24; // [esp+1Ch] [ebp-224h]
  sockaddr_in address; // [esp+20h] [ebp-220h] BYREF
  char hostName[128]; // [esp+30h] [ebp-210h] BYREF
  WSAData wsaData; // [esp+B0h] [ebp-190h] BYREF

  v0 = 0;
  parm = 0;
  v1 = 0;
  do
  {
    v2 = GSSSecurityTag998.mSecurityID[v1];
    hostName[v1++] = v2;
  }
  while ( v2 );
  v3 = strchr(hostName, 58);
  if ( v3 )
  {
    *v3 = 0;
    v4 = atol(v3 + 1);
  }
  else
  {
    v4 = GSS_PORTS[0];
  }
  if ( WSAStartup(0x101u, &wsaData) )
    return 0;
  v5 = gethostbyname(hostName);
  if ( !v5 )
  {
    WSACleanup();
    return 0;
  }
  if ( v5->h_addrtype != 2
    || (address.sin_family = 2,
        address.sin_addr.S_un.S_addr = **(_DWORD **)v5->h_addr_list,
        address.sin_port = htons(v4),
        v7 = socket(2, 1, 6),
        connectSocket = v7,
        v7 == -1) )
  {
LABEL_14:
    WSACleanup();
    return 0;
  }
  if ( ioctlsocket(v7, -2147195266, &parm) )
  {
    closesocket(v7);
    goto LABEL_14;
  }
  if ( GSS_PORTS[0] )
  {
    do
    {
      if ( connect(v7, (const struct sockaddr *)&address, 16) != -1 )
        break;
      v8 = *(&hostshort + 2 * v0++);
      v9 = htons(v8);
      v10 = GSS_PORTS[v0] == 0;
      address.sin_port = v9;
    }
    while ( !v10 );
  }
  if ( !GSS_PORTS[v0] )
  {
    closesocket(v7);
    WSACleanup();
    return 0;
  }
  send(v7, &GSSSecurityTag997.mSecurityID[4], strlen(&GSSSecurityTag997.mSecurityID[4]), 0);
  EncryptionSize = *(_DWORD *)GSSSecurityTag997.mSecurityID;
  v11 = (unsigned __int8 *)malloc(*(_DWORD *)GSSSecurityTag997.mSecurityID + 1024);
  wantedSize = EncryptionSize;
  parsedHTTPHeader = 0;
  v12 = 0;
  v24 = Sys_Milliseconds() + 10000;
  while ( Sys_Milliseconds() <= v24 )
  {
    v13 = recv(v7, (char *)&v11[v12], EncryptionSize - v12 + 1023, 2);
    if ( v13 )
    {
      v14 = recv(v7, (char *)&v11[v12], v13, 0);
      v12 += v14;
      v11[v12] = 0;
      if ( v14 < 4 )
      {
        v7 = connectSocket;
        goto LABEL_50;
      }
      if ( parsedHTTPHeader )
      {
LABEL_44:
        v7 = connectSocket;
LABEL_45:
        if ( v12 >= wantedSize )
          break;
      }
      else
      {
        if ( !idStr::Cmpn((const char *)v11, "HTTP", 4) )
        {
          v15 = 0;
          if ( v12 > 0 )
          {
            for ( i = 2 - (_DWORD)v11; ; i = 2 - (_DWORD)v11 )
            {
              v17 = &v11[v15];
              v18 = &v11[v15 + i];
              if ( (int)(v18 + 2) <= v14 && *v17 == 13 && v11[v15 + 1] == 10 && v11[v15 + 2] == 13 && v11[v15 + 3] == 10 )
              {
                v15 += 4;
                goto LABEL_42;
              }
              if ( (int)v18 <= v14 && *v17 == 10 && v11[v15 + 1] == 10 )
                break;
              if ( ++v15 >= v12 )
                goto LABEL_42;
            }
            v15 += 2;
          }
LABEL_42:
          if ( v15 <= v12 )
          {
            parsedHTTPHeader = 1;
            memmove(v11, &v11[v15], EncryptionSize - v15 + 1023);
            v12 -= v15;
            goto LABEL_44;
          }
        }
        v7 = connectSocket;
      }
    }
    else
    {
LABEL_50:
      if ( parsedHTTPHeader )
        goto LABEL_45;
    }
  }
  closesocket(v7);
  WSACleanup();
  if ( v12 == EncryptionSize )
  {
    v19 = (unsigned __int8 *)malloc(EncryptionSize);
    qmemcpy(v19, v11, EncryptionSize);
    EncryptionBuffer = v19;
  }
  free(v11);
  return EncryptionBuffer != 0;
}

// FUNC: public: virtual bool __thiscall CGSS_EncryptedFileSystem::fopen(char const *,char const *)
BOOL __thiscall CGSS_EncryptedFileSystem::fopen(CGSS_EncryptedFileSystem *this, const char *filename, const char *mode)
{
  _iobuf *v4; // eax

  this->mOffset = 0;
  this->mFileSize = 0;
  v4 = fopen(filename, mode);
  this->mFH = v4;
  if ( v4 )
  {
    fseek(v4, 0, 2);
    this->mFileSize = ftell(this->mFH);
    fseek(this->mFH, 0, 0);
  }
  return this->mFH != 0;
}

// FUNC: public: virtual int __thiscall CGSS_EncryptedFileSystem::fseek(long,int)
int __thiscall CGSS_EncryptedFileSystem::fseek(CGSS_EncryptedFileSystem *this, int offset, int origin)
{
  if ( origin )
  {
    if ( origin == 1 )
    {
      this->mOffset += offset;
      return fseek(this->mFH, offset, 1);
    }
    if ( origin == 2 )
    {
      this->mOffset = this->mFileSize + 2;
      return fseek(this->mFH, offset, 2);
    }
  }
  else
  {
    this->mOffset = offset;
  }
  return fseek(this->mFH, offset, origin);
}

// FUNC: public: virtual long __thiscall CGSS_EncryptedFileSystem::ftell(void)
int __thiscall CGSS_EncryptedFileSystem::ftell(CGSS_EncryptedFileSystem *this)
{
  return ftell(this->mFH);
}

// FUNC: public: virtual unsigned int __thiscall CGSS_EncryptedFileSystem::fread(void *,unsigned int,unsigned int)
unsigned int __thiscall CGSS_EncryptedFileSystem::fread(
        CGSS_EncryptedFileSystem *this,
        char *buffer,
        unsigned int size,
        unsigned int count)
{
  char *v4; // edi
  unsigned int v6; // ebp
  signed int v7; // ecx
  signed int i; // ebx
  int v9; // edx

  v4 = buffer;
  v6 = fread(buffer, size, count, this->mFH);
  v7 = size * v6;
  for ( i = 0; i < v7; *(v4 - 1) ^= this->mEncryptionData[v9] )
  {
    v9 = (i + this->mOffset) % this->mEncryptionSize;
    ++i;
    ++v4;
  }
  this->mOffset += v7;
  return v6;
}

// FUNC: public: virtual bool __thiscall CGSS_EncryptedFileSystem::fclose(void)
char __thiscall CGSS_EncryptedFileSystem::fclose(CGSS_EncryptedFileSystem *this)
{
  fclose(this->mFH);
  this->mFH = 0;
  return 1;
}

// FUNC: class IGSS_FileSystem * __cdecl GSS_GetFileSystem(void)
IGSS_FileSystem *__cdecl GSS_GetFileSystem()
{
  IGSS_FileSystem *result; // eax
  IGSS_FileSystem_vtbl *v1; // ecx
  IGSS_FileSystem_vtbl *v2; // edx

  if ( EncryptionBuffer || !TriedEncryptionBuffer && (TriedEncryptionBuffer = 1, GSS_GetEncryption(), EncryptionBuffer) )
  {
    result = (IGSS_FileSystem *)Memory::Allocate(0x18u);
    if ( result )
    {
      v1 = (IGSS_FileSystem_vtbl *)EncryptionBuffer;
      v2 = (IGSS_FileSystem_vtbl *)EncryptionSize;
      result->__vftable = (IGSS_FileSystem_vtbl *)&CGSS_EncryptedFileSystem::`vftable';
      result[1].__vftable = 0;
      result[2].__vftable = 0;
      result[3].__vftable = 0;
      result[4].__vftable = v1;
      result[5].__vftable = v2;
      return result;
    }
  }
  else
  {
    result = (IGSS_FileSystem *)Memory::Allocate(8u);
    if ( result )
    {
      result->__vftable = (IGSS_FileSystem_vtbl *)&CGSS_NormalFileSystem::`vftable';
      return result;
    }
  }
  return 0;
}
