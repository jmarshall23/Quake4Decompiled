
// FUNC: bool __cdecl Sys_IsAppActive(void)
bool __cdecl Sys_IsAppActive()
{
  return win32.activeApp;
}

// FUNC: int __cdecl Sys_Milliseconds(void)
DWORD __cdecl Sys_Milliseconds()
{
  if ( !initialized )
  {
    sys_timeBase = timeGetTime();
    initialized = 1;
  }
  return timeGetTime() - sys_timeBase;
}

// FUNC: int __cdecl Sys_GetSystemRam(void)
char __cdecl Sys_GetSystemRam()
{
  _MEMORYSTATUSEX statex; // [esp+0h] [ebp-40h] BYREF

  statex.dwLength = 64;
  GlobalMemoryStatusEx(&statex);
  return ((statex.ullTotalPhys >> 20) + 8) & 0xF0;
}

// FUNC: int __cdecl Sys_GetDriveFreeSpace(char const *)
int __cdecl Sys_GetDriveFreeSpace(const char *path)
{
  unsigned __int64 lpFreeBytesAvailable; // [esp+8h] [ebp-18h] BYREF
  unsigned __int64 lpTotalNumberOfFreeBytes; // [esp+10h] [ebp-10h] BYREF
  unsigned __int64 lpTotalNumberOfBytes; // [esp+18h] [ebp-8h] BYREF

  if ( GetDiskFreeSpaceExA(
         path,
         (PULARGE_INTEGER)&lpFreeBytesAvailable,
         (PULARGE_INTEGER)&lpTotalNumberOfBytes,
         (PULARGE_INTEGER)&lpTotalNumberOfFreeBytes) )
  {
    return (__int64)((double)lpFreeBytesAvailable * 0.00000095367431640625);
  }
  else
  {
    return 26;
  }
}

// FUNC: void __cdecl Sys_GetCurrentMemoryStatus(struct sysMemoryStats_s &)
void __cdecl Sys_GetCurrentMemoryStatus(sysMemoryStats_s *stats)
{
  unsigned int ullTotalPhys; // edx
  unsigned int ullAvailPhys_high; // ecx
  int v3; // edx
  unsigned int ullAvailPageFile_high; // ecx
  int v5; // edx
  unsigned int ullTotalPageFile_high; // ecx
  int v7; // edx
  unsigned int ullTotalVirtual_high; // ecx
  int v9; // edx
  unsigned int ullAvailVirtual_high; // ecx
  int v11; // edx
  unsigned int ullAvailExtendedVirtual_high; // ecx
  _MEMORYSTATUSEX statex; // [esp+4h] [ebp-40h] BYREF

  memset(&statex, 0, sizeof(statex));
  statex.dwLength = 64;
  GlobalMemoryStatusEx(&statex);
  stats->memoryLoad = 0;
  stats->totalPhysical = 0;
  stats->availPhysical = 0;
  stats->totalPageFile = 0;
  stats->availPageFile = 0;
  stats->totalVirtual = 0;
  stats->availVirtual = 0;
  stats->availExtendedVirtual = 0;
  ullTotalPhys = statex.ullTotalPhys;
  stats->memoryLoad = statex.dwMemoryLoad;
  ullAvailPhys_high = HIDWORD(statex.ullAvailPhys);
  stats->totalPhysical = __PAIR64__(HIDWORD(statex.ullTotalPhys), ullTotalPhys) >> 20;
  v3 = __PAIR64__(ullAvailPhys_high, statex.ullAvailPhys) >> 20;
  ullAvailPageFile_high = HIDWORD(statex.ullAvailPageFile);
  stats->availPhysical = v3;
  v5 = __PAIR64__(ullAvailPageFile_high, statex.ullAvailPageFile) >> 20;
  ullTotalPageFile_high = HIDWORD(statex.ullTotalPageFile);
  stats->availPageFile = v5;
  v7 = __PAIR64__(ullTotalPageFile_high, statex.ullTotalPageFile) >> 20;
  ullTotalVirtual_high = HIDWORD(statex.ullTotalVirtual);
  stats->totalPageFile = v7;
  v9 = __PAIR64__(ullTotalVirtual_high, statex.ullTotalVirtual) >> 20;
  ullAvailVirtual_high = HIDWORD(statex.ullAvailVirtual);
  stats->totalVirtual = v9;
  v11 = __PAIR64__(ullAvailVirtual_high, statex.ullAvailVirtual) >> 20;
  ullAvailExtendedVirtual_high = HIDWORD(statex.ullAvailExtendedVirtual);
  stats->availVirtual = v11;
  stats->availExtendedVirtual = __PAIR64__(ullAvailExtendedVirtual_high, statex.ullAvailExtendedVirtual) >> 20;
}

// FUNC: bool __cdecl Sys_LockMemory(void *,int)
BOOL __cdecl Sys_LockMemory(void *ptr, int bytes)
{
  return VirtualLock(ptr, bytes);
}

// FUNC: bool __cdecl Sys_UnlockMemory(void *,int)
BOOL __cdecl Sys_UnlockMemory(void *ptr, int bytes)
{
  return VirtualUnlock(ptr, bytes);
}

// FUNC: void __cdecl Sys_SetPhysicalWorkMemory(int,int)
void __cdecl Sys_SetPhysicalWorkMemory(int minBytes, int maxBytes)
{
  HANDLE CurrentProcess; // eax

  CurrentProcess = GetCurrentProcess();
  SetProcessWorkingSetSize(CurrentProcess, minBytes, maxBytes);
}

// FUNC: char * __cdecl Sys_GetCurrentUser(void)
char *__cdecl Sys_GetCurrentUser()
{
  unsigned int size; // [esp+0h] [ebp-4h] BYREF

  size = 1024;
  if ( !GetUserNameA(s_userName, &size) )
    strcpy(s_userName, "player");
  if ( !s_userName[0] )
    strcpy(s_userName, "player");
  return s_userName;
}

// FUNC: unsigned long __cdecl GetFuncAddr(unsigned long)
_DWORD *__cdecl GetFuncAddr(_DWORD *midPtPtr)
{
  _DWORD *result; // eax
  int v2; // edx

  result = midPtPtr;
  if ( (*midPtPtr & 0xFFFFFF) != 15502165 )
  {
    do
    {
      v2 = *(_DWORD *)((char *)result - 1);
      result = (_DWORD *)((char *)result - 1);
    }
    while ( (v2 & 0xFFFFFF) != 15502165 );
  }
  return result;
}

// FUNC: unsigned long __cdecl GetCallerAddr(long)
_DWORD *__cdecl GetCallerAddr(_DWORD *_ebp)
{
  _DWORD *v1; // eax
  int res; // [esp+4h] [ebp-4h]

  res = 0;
  if ( *_ebp )
  {
    v1 = (_DWORD *)_ebp[1];
    if ( v1 )
      return GetFuncAddr(v1);
  }
  return (_DWORD *)res;
}

// FUNC: void __cdecl Sys_GetCallStack(unsigned long *,int)
void __usercall Sys_GetCallStack(_DWORD ***a1@<ebp>, unsigned int *callStack, int callStackSize)
{
  _DWORD *v3; // edi
  int v4; // esi
  _DWORD *CallerAddr; // eax

  v3 = **a1;
  v4 = 0;
  if ( callStackSize > 0 )
  {
    while ( 1 )
    {
      CallerAddr = GetCallerAddr(v3);
      callStack[v4] = (unsigned int)CallerAddr;
      if ( !CallerAddr )
        break;
      v3 = (_DWORD *)*v3;
      if ( ++v4 >= callStackSize )
        return;
    }
    if ( v4 < callStackSize )
      memset(&callStack[v4], 0, 4 * (callStackSize - v4));
  }
}

// FUNC: int __cdecl Sys_MapKey(unsigned long,unsigned short)
int __cdecl Sys_MapKey(unsigned int key, unsigned __int16 wParam)
{
  int result; // eax

  switch ( BYTE2(key) )
  {
    case ')':
      return 1;
    case '*':
      return 142;
    case '6':
      return 3;
  }
  if ( !wParam )
    return (unsigned __int8)MapVirtualKeyA(wParam, 2u);
  if ( wParam >= 0x100u )
    return (unsigned __int8)MapVirtualKeyA(wParam, 2u);
  result = virtualKeyConvert[wParam][HIBYTE(key) & 1];
  if ( !virtualKeyConvert[wParam][HIBYTE(key) & 1] )
    return (unsigned __int8)MapVirtualKeyA(wParam, 2u);
  return result;
}

// FUNC: char const * __cdecl Sys_GetCallStackStr(unsigned long const *,int)
char *__cdecl Sys_GetCallStackStr(const unsigned int *callStack, int callStackSize)
{
  int v2; // edi
  int i; // esi
  unsigned int v4; // ebp
  idStr funcName; // [esp+8h] [ebp-4Ch] BYREF
  idStr module; // [esp+28h] [ebp-2Ch] BYREF
  int v8; // [esp+50h] [ebp-4h]

  v2 = 0;
  module.len = 0;
  module.alloced = 20;
  module.data = module.baseBuffer;
  module.baseBuffer[0] = 0;
  v8 = 1;
  funcName.len = 0;
  funcName.alloced = 20;
  funcName.data = funcName.baseBuffer;
  funcName.baseBuffer[0] = 0;
  for ( i = callStackSize - 1; i >= 0; --i )
  {
    v4 = callStack[i];
    idStr::operator=(&module, (char *)&entityFilter);
    sprintf(&funcName, "0x%08x", v4);
    v2 += sprintf(&string[v2], " -> %s", funcName.data);
  }
  LOBYTE(v8) = 0;
  idStr::FreeData(&funcName);
  v8 = -1;
  idStr::FreeData(&module);
  return string;
}

// FUNC: char const * __cdecl Sys_GetCallStackCurStr(int)
char *__cdecl Sys_GetCallStackCurStr(int depth)
{
  int v1; // eax
  void *v2; // esp
  unsigned int v4[2]; // [esp+0h] [ebp-8h] BYREF
  _DWORD **savedregs; // [esp+8h] [ebp+0h] BYREF

  v1 = 4 * depth + 3;
  LOBYTE(v1) = v1 & 0xFC;
  v2 = alloca(v1);
  Sys_GetCallStack(&savedregs, v4, depth);
  return Sys_GetCallStackStr(v4, depth);
}

// FUNC: int __cdecl Sys_GetVideoRam(void)
unsigned int __cdecl Sys_GetVideoRam()
{
  unsigned __int16 *v0; // ebx
  IWbemLocator_vtbl *v1; // ecx
  IWbemServices_vtbl *v3; // edx
  unsigned __int16 **v4; // eax
  int v5; // esi
  IEnumWbemClassObject_vtbl *v6; // ecx
  bool v7; // zf
  IWbemClassObject *p; // eax
  IWbemClassObject_vtbl *v9; // edx
  const unsigned __int16 **v10; // eax
  int v11; // esi
  const unsigned __int16 *v12; // [esp+48h] [ebp-60h]
  unsigned __int16 *v13; // [esp+4Ch] [ebp-5Ch]
  ATL::CComPtr<IWbemServices> spServices; // [esp+6Ch] [ebp-3Ch] BYREF
  ATL::CComPtr<IWbemLocator> spLoc; // [esp+70h] [ebp-38h] BYREF
  ATL::CComPtr<IWbemClassObject> spInstance; // [esp+74h] [ebp-34h] BYREF
  ATL::CComPtr<IEnumWbemClassObject> spEnumInst; // [esp+78h] [ebp-30h] BYREF
  unsigned int retSize; // [esp+7Ch] [ebp-2Ch]
  ATL::CComBSTR v19; // [esp+80h] [ebp-28h] BYREF
  unsigned int uNumOfInstances; // [esp+84h] [ebp-24h] BYREF
  ATL::CComBSTR bstrNamespace; // [esp+88h] [ebp-20h]
  ATL::CComVariant varSize; // [esp+8Ch] [ebp-1Ch] BYREF
  int v23; // [esp+A4h] [ebp-4h]

  retSize = 64;
  spLoc.p = 0;
  v23 = 0;
  if ( CoCreateInstance(&CLSID_WbemLocator, 0, 0x15u, &IID_IWbemLocator, (LPVOID *)&spLoc.p) || !spLoc.p )
  {
    v23 = -1;
    if ( spLoc.p )
      spLoc.p->Release(spLoc.p);
    return 64;
  }
  else
  {
    v0 = A2WBSTR("\\\\.\\root\\CIMV2", -1);
    bstrNamespace.m_str = v0;
    if ( !v0 )
      ATL::AtlThrow(-2147024882);
    spServices.p = 0;
    v1 = spLoc.p->__vftable;
    LOBYTE(v23) = 2;
    if ( v1->ConnectServer(spLoc.p, v0, 0, 0, 0, 0, 0, 0, &spServices.p) )
    {
      LOBYTE(v23) = 1;
      if ( spServices.p )
        spServices.p->Release(spServices.p);
      SysFreeString(v0);
      v23 = -1;
      if ( spLoc.p )
      {
        spLoc.p->Release(spLoc.p);
        return 64;
      }
      return 64;
    }
    if ( CoSetProxyBlanket(spServices.p, 0xAu, 0, 0, 3u, 3u, 0, 0) )
    {
      LOBYTE(v23) = 1;
      if ( spServices.p )
        spServices.p->Release(spServices.p);
      SysFreeString(v0);
      v23 = -1;
      if ( spLoc.p )
        spLoc.p->Release(spLoc.p);
      return 64;
    }
    spEnumInst.p = 0;
    LOBYTE(v23) = 3;
    ATL::CComBSTR::CComBSTR(&v19, "Win32_VideoController");
    v3 = spServices.p->__vftable;
    v13 = *v4;
    LOBYTE(v23) = 4;
    v5 = v3->CreateInstanceEnum(spServices.p, v13, 1, 0, &spEnumInst.p);
    SysFreeString(v19.m_str);
    if ( v5 || !spEnumInst.p )
    {
      LOBYTE(v23) = 2;
      if ( spEnumInst.p )
        spEnumInst.p->Release(spEnumInst.p);
      LOBYTE(v23) = 1;
      if ( spServices.p )
        spServices.p->Release(spServices.p);
      SysFreeString(v0);
      v23 = -1;
      if ( spLoc.p )
        spLoc.p->Release(spLoc.p);
      return 64;
    }
    else
    {
      uNumOfInstances = 0;
      spInstance.p = 0;
      v6 = spEnumInst.p->__vftable;
      LOBYTE(v23) = 5;
      v7 = v6->Next(spEnumInst.p, 10000, 1u, &spInstance.p, &uNumOfInstances) == 0;
      p = spInstance.p;
      if ( v7 && spInstance.p )
      {
        VariantInit(&varSize);
        LOBYTE(v23) = 6;
        ATL::CComBSTR::CComBSTR(&v19, "AdapterRAM");
        v9 = spInstance.p->__vftable;
        v12 = *v10;
        LOBYTE(v23) = 7;
        v11 = v9->Get(spInstance.p, v12, 0, &varSize, 0, 0);
        SysFreeString(v19.m_str);
        if ( !v11 )
        {
          retSize = (signed int)varSize.decVal.Lo32 / 0x100000;
          if ( !((signed int)varSize.decVal.Lo32 / 0x100000) )
            retSize = 64;
        }
        VariantClear(&varSize);
        p = spInstance.p;
      }
      LOBYTE(v23) = 3;
      if ( p )
        p->Release(p);
      LOBYTE(v23) = 2;
      if ( spEnumInst.p )
        spEnumInst.p->Release(spEnumInst.p);
      LOBYTE(v23) = 1;
      if ( spServices.p )
        spServices.p->Release(spServices.p);
      SysFreeString(v0);
      v23 = -1;
      if ( spLoc.p )
        spLoc.p->Release(spLoc.p);
      return retSize;
    }
  }
}
