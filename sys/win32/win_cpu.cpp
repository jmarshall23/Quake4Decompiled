
// FUNC: double __cdecl Sys_GetClockTicks(void)
double __cdecl Sys_GetClockTicks()
{
  unsigned __int64 v5; // rax

  _EAX = 0;
  __asm { cpuid }
  v5 = __rdtsc();
  return (double)HIDWORD(v5) * 4294967295.0 + (double)(unsigned int)v5;
}

// FUNC: double __cdecl Sys_ClockTicksPerSecond(void)
double __cdecl Sys_ClockTicksPerSecond()
{
  LSTATUS v0; // esi
  double result; // st7
  HKEY__ *hKey; // [esp+0h] [ebp-Ch] BYREF
  unsigned __int8 *ProcSpeed; // [esp+4h] [ebp-8h] BYREF
  unsigned int buflen; // [esp+8h] [ebp-4h] BYREF

  if ( ticks != 0.0
    || RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, 0x20019u, &hKey) )
  {
    return ticks;
  }
  ProcSpeed = 0;
  buflen = 4;
  v0 = RegQueryValueExA(hKey, "~MHz", 0, 0, (LPBYTE)&ProcSpeed, &buflen);
  if ( v0 )
  {
    v0 = RegQueryValueExA(hKey, "~Mhz", 0, 0, (LPBYTE)&ProcSpeed, &buflen);
    if ( v0 )
      v0 = RegQueryValueExA(hKey, "~mhz", 0, 0, (LPBYTE)&ProcSpeed, &buflen);
  }
  RegCloseKey(hKey);
  if ( v0 )
    return ticks;
  result = (double)(unsigned int)ProcSpeed * 1000000.0;
  ticks = result;
  return result;
}

// FUNC: HasCPUID
char __cdecl HasCPUID()
{
  unsigned int v0; // kr00_4
  unsigned int v1; // kr04_4
  unsigned int v2; // kr08_4

  v0 = __readeflags();
  if ( (v0 & 0x200000) != 0 )
  {
    __writeeflags(v0 & 0xFFDFFFFF);
    v1 = __readeflags();
    if ( (v1 & 0x200000) != 0 )
      return 0;
  }
  else
  {
    __writeeflags(v0 | 0x200000);
    v2 = __readeflags();
    if ( (v2 & 0x200000) == 0 )
      return 0;
  }
  return 1;
}

// FUNC: IsAMD
bool __cdecl IsAMD()
{
  char processorString[13]; // [esp+1Ch] [ebp-10h] BYREF

  __asm { pushaw }
  _EAX = 0;
  __asm
  {
    cpuid
    popaw
  }
  *(_DWORD *)processorString = _EBX;
  *(_DWORD *)&processorString[4] = _EDX;
  *(_DWORD *)&processorString[8] = _ECX;
  processorString[12] = 0;
  return idStr::Cmp(processorString, "AuthenticAMD") == 0;
}

// FUNC: Has3DNow
bool __cdecl Has3DNow()
{
  __asm { pushaw }
  _EAX = 0x80000000;
  __asm
  {
    cpuid
    popaw
  }
  if ( _EAX < 0x80000000 )
    return 0;
  __asm { pushaw }
  _EAX = -2147483647;
  __asm
  {
    cpuid
    popaw
  }
  return _EDX < 0;
}

// FUNC: Is64BitAMD
bool __cdecl Is64BitAMD()
{
  __asm { pushaw }
  _EAX = 0x80000000;
  __asm
  {
    cpuid
    popaw
  }
  if ( _EAX < 0x80000000 )
    return 0;
  __asm { pushaw }
  _EAX = -2147483647;
  __asm
  {
    cpuid
    popaw
  }
  return (_EDX & 0x20000000) != 0;
}

// FUNC: void __cdecl Sys_GetCPUCacheSize(int,int &,int &)
void __cdecl Sys_GetCPUCacheSize(int level, int *totalSize, int *lineSize)
{
  int v8; // ebp
  cacheInfo_t *v14; // ebp
  int v15; // eax
  unsigned __int8 code; // bl
  unsigned int v17; // edi
  int v18; // edx
  unsigned __int8 v19; // al
  cacheInfo_t *v20; // ecx
  unsigned int v21; // edi
  int v22; // edx
  unsigned int regs[4]; // [esp+20h] [ebp-10h]
  int levela; // [esp+34h] [ebp+4h]

  *totalSize = 0;
  *lineSize = 0;
  __asm { pushaw }
  _EAX = 2;
  __asm
  {
    cpuid
    popaw
  }
  regs[0] = _EAX;
  regs[1] = _EBX;
  regs[2] = _ECX;
  regs[3] = _EDX;
  if ( (unsigned __int8)_EAX > 1u )
  {
    v8 = (unsigned __int8)_EAX - 1;
    do
    {
      __asm { pushaw }
      _EAX = 2;
      __asm
      {
        cpuid
        popaw
      }
      --v8;
      regs[0] = _EAX;
      regs[1] = _EBX;
      regs[2] = _ECX;
      regs[3] = _EDX;
    }
    while ( v8 );
  }
  v14 = levelCacheInfo[level];
  v15 = 0;
  levela = 0;
  while ( 1 )
  {
    if ( (regs[v15] & 0x80000000) == 0 )
    {
      if ( !v15 )
        regs[0] >>= 8;
      if ( regs[v15] )
        break;
    }
LABEL_16:
    levela = ++v15;
    if ( v15 >= 4 )
      return;
  }
  code = v14->code;
  while ( 1 )
  {
    v17 = regs[v15];
    v18 = 0;
    if ( code )
      break;
LABEL_15:
    v21 = v17 >> 8;
    regs[v15] = v21;
    if ( !v21 )
      goto LABEL_16;
  }
  v19 = code;
  v20 = v14;
  while ( (unsigned __int8)v17 != v19 )
  {
    v19 = v20[1].code;
    ++v20;
    ++v18;
    if ( !v19 )
    {
      v15 = levela;
      goto LABEL_15;
    }
  }
  v22 = v18;
  *totalSize = v14[v22].totalSize;
  *lineSize = v14[v22].lineSize;
}

// FUNC: int __cdecl Sys_CPUCount(int &,int &)
int __cdecl Sys_CPUCount(int *logicalNum, int *physicalNum)
{
  int v2; // esi
  char v8; // dl
  unsigned __int8 v9; // cl
  HANDLE CurrentProcess; // edi
  unsigned int v11; // eax
  DWORD_PTR v13; // esi
  unsigned __int8 PHY_ID_MASK; // [esp+12h] [ebp-32h]
  unsigned __int8 HT_Enabled; // [esp+13h] [ebp-31h]
  unsigned int dwProcessAffinity; // [esp+14h] [ebp-30h] BYREF
  unsigned int dwSystemAffinity[2]; // [esp+18h] [ebp-2Ch] BYREF
  _SYSTEM_INFO info; // [esp+20h] [ebp-24h] BYREF

  *physicalNum = 1;
  *logicalNum = 1;
  v2 = 0;
  info.dwNumberOfProcessors = 0;
  GetSystemInfo(&info);
  *physicalNum = info.dwNumberOfProcessors;
  HT_Enabled = 0;
  _EAX = 1;
  __asm { cpuid }
  dwSystemAffinity[0] = _EBX;
  *logicalNum = BYTE2(_EBX);
  if ( BYTE2(_EBX) )
  {
    v8 = -1;
    v9 = 1;
    PHY_ID_MASK = -1;
    if ( BYTE2(_EBX) > 1u )
    {
      do
      {
        v9 *= 2;
        v8 *= 2;
      }
      while ( v9 < (int)BYTE2(_EBX) );
      PHY_ID_MASK = v8;
    }
    CurrentProcess = GetCurrentProcess();
    GetProcessAffinityMask(CurrentProcess, &dwProcessAffinity, dwSystemAffinity);
    v11 = dwProcessAffinity;
    if ( dwProcessAffinity != dwSystemAffinity[0] )
    {
      *physicalNum = -1;
      return 4;
    }
    v13 = 1;
    do
    {
      if ( v13 > v11 )
        break;
      if ( (v13 & v11) != 0 )
      {
        if ( SetProcessAffinityMask(CurrentProcess, v13) )
        {
          Sleep(0);
          _EAX = 1;
          __asm { cpuid }
          dwSystemAffinity[1] = _EBX;
          if ( (HIBYTE(_EBX) & (unsigned __int8)~PHY_ID_MASK) != 0 )
            HT_Enabled = 1;
        }
        v11 = dwProcessAffinity;
      }
      v13 *= 2;
    }
    while ( v13 );
    SetProcessAffinityMask(CurrentProcess, v11);
    if ( *logicalNum == 1 )
      return 2;
    if ( HT_Enabled )
    {
      *physicalNum /= *logicalNum;
      return 1;
    }
    return 3;
  }
  return v2;
}

// FUNC: HasHTT
bool __cdecl HasHTT()
{
  int logicalNum; // [esp+14h] [ebp-8h] BYREF
  int physicalNum; // [esp+18h] [ebp-4h] BYREF

  __asm { pushaw }
  _EAX = 1;
  __asm { cpuid }
  physicalNum = _EAX;
  logicalNum = _EBX;
  __asm { popaw }
  return (_EDX & 0x10000000) != 0 && Sys_CPUCount(&logicalNum, &physicalNum) == 1;
}

// FUNC: HasDAZ
bool __cdecl HasDAZ()
{
  int v6[128]; // [esp+430h] [ebp-200h] BYREF

  __asm { pushaw }
  _EAX = 1;
  __asm
  {
    cpuid
    popaw
  }
  if ( (_EDX & 0x1000000) == 0 )
    return 0;
  memset(v6, 0, sizeof(v6));
  _fxsave(v6);
  return (v6[7] & 0x40) == 64;
}

// FUNC: enum cpuid_t __cdecl Sys_GetCPUId(void)
int __cdecl Sys_GetCPUId()
{
  int v31; // ebx
  int flags; // [esp+Ch] [ebp-14h]

  if ( !HasCPUID() )
    return 1;
  flags = IsAMD() ? 8 : 4;
  __asm { pushaw }
  _EAX = 1;
  __asm
  {
    cpuid
    popaw
  }
  if ( (_EDX & 0x800000) != 0 )
    flags |= 0x10u;
  if ( Has3DNow() )
    flags |= 0x20u;
  __asm { pushaw }
  _EAX = 1;
  __asm
  {
    cpuid
    popaw
  }
  if ( (_EDX & 0x2000000) != 0 )
    flags |= 0x4040u;
  __asm { pushaw }
  _EAX = 1;
  __asm
  {
    cpuid
    popaw
  }
  if ( (_EDX & 0x4000000) != 0 )
    LOBYTE(flags) = flags | 0x80;
  __asm { pushaw }
  _EAX = 1;
  __asm
  {
    cpuid
    popaw
  }
  if ( (_ECX & 1) != 0 )
    BYTE1(flags) |= 1u;
  if ( HasHTT() )
    BYTE1(flags) |= 0x10u;
  __asm { pushaw }
  _EAX = 1;
  __asm
  {
    cpuid
    popaw
  }
  if ( (_EDX & 0x8000) != 0 )
    BYTE1(flags) |= 0x20u;
  if ( HasDAZ() )
    flags |= 0x8000u;
  __asm { pushaw }
  _EAX = -2147483647;
  __asm
  {
    cpuid
    popaw
  }
  v31 = flags;
  if ( (_EDX & 0x20000000) != 0 )
    v31 = flags | 0x10000;
  if ( (v31 & 8) != 0 && Is64BitAMD() )
    return v31 | 0x20000;
  return v31;
}

// FUNC: int __cdecl Sys_FPU_PrintStateFlags(char *,int,int,int,int,int,int,int)
int __cdecl Sys_FPU_PrintStateFlags(char *ptr, int ctrl, int stat, int tags, int inof, int inse, int opof, int opse)
{
  int v8; // ebp
  int v9; // esi
  int v10; // esi
  char *name; // eax
  bitFlag_s *v12; // ebp
  const char *v13; // ecx
  int v14; // esi
  int v15; // esi
  int v16; // esi
  char *v17; // eax
  bitFlag_s *v18; // ebx
  const char *v19; // ecx
  int v20; // esi

  v8 = stat;
  v9 = sprintf(
         ptr,
         "CTRL = %08x\nSTAT = %08x\nTAGS = %08x\nINOF = %08x\nINSE = %08x\nOPOF = %08x\nOPSE = %08x\n\n",
         ctrl,
         stat,
         tags,
         inof,
         inse,
         opof,
         opse);
  v10 = sprintf(&ptr[v9], "Control Word:\n") + v9;
  name = controlWordFlags[0].name;
  if ( *controlWordFlags[0].name )
  {
    v12 = controlWordFlags;
    do
    {
      v13 = "true";
      if ( ((1 << v12->bit) & ctrl) == 0 )
        v13 = "false";
      ++v12;
      v10 += sprintf(&ptr[v10], "  %-30s = %s\n", name, v13);
      name = v12->name;
    }
    while ( *v12->name );
    v8 = stat;
  }
  v14 = sprintf(&ptr[v10], "  %-30s = %s\n", "Precision control", precisionControlField[(ctrl >> 8) & 3]) + v10;
  v15 = sprintf(&ptr[v14], "  %-30s = %s\n", "Rounding control", roundingControlField[(ctrl >> 10) & 3]) + v14;
  v16 = sprintf(&ptr[v15], "Status Word:\n") + v15;
  v17 = statusWordFlags[0].name;
  if ( *statusWordFlags[0].name )
  {
    v18 = statusWordFlags;
    do
    {
      v19 = "true";
      if ( ((1 << v18->bit) & v8) == 0 )
        v19 = "false";
      ++v18;
      v16 += sprintf(&ptr[v16], "  %-30s = %s\n", v17, v19);
      v17 = v18->name;
    }
    while ( *v18->name );
  }
  v20 = sprintf(
          &ptr[v16],
          "  %-30s = %d%d%d%d\n",
          "Condition code",
          (v8 >> 8) & 1,
          (v8 >> 9) & 1,
          (v8 >> 10) & 1,
          (v8 >> 14) & 1)
      + v16;
  return v20 + sprintf(&ptr[v20], "  %-30s = %d\n", "Top of stack pointer", (v8 >> 11) & 7);
}

// FUNC: bool __cdecl Sys_FPU_StackIsEmpty(void)
bool __cdecl Sys_FPU_StackIsEmpty()
{
  _EAX = statePtr;
  __asm { fnstenv byte ptr [eax] }
  return *((_WORD *)_EAX + 4) == 0xFFFF;
}

// FUNC: char const * __cdecl Sys_FPU_GetState(void)
char *__cdecl Sys_FPU_GetState()
{
  int v1; // esi
  int v2; // eax
  int v3; // ebx
  char *v4; // esi
  int v6; // eax
  double v8; // [esp+0h] [ebp-70h]
  long double fpuStack[8]; // [esp+14h] [ebp-5Ch] BYREF
  int stat; // [esp+54h] [ebp-1Ch]
  int tags; // [esp+58h] [ebp-18h]
  int inof; // [esp+5Ch] [ebp-14h]
  int inse; // [esp+60h] [ebp-10h]
  int opof; // [esp+64h] [ebp-Ch]
  int numValues; // [esp+68h] [ebp-8h]
  long double *fpuStackPtr; // [esp+6Ch] [ebp-4h]

  __asm
  {
    fld     ds:__real@0000000000000000
    fstp    [ebp+fpuStack]
    fld     ds:__real@0000000000000000
    fstp    [ebp+fpuStack+8]
    fld     ds:__real@0000000000000000
  }
  fpuStackPtr = fpuStack;
  __asm
  {
    fstp    [ebp+fpuStack+10h]
    fld     ds:__real@0000000000000000
    fstp    [ebp+fpuStack+18h]
    fld     ds:__real@0000000000000000
    fstp    [ebp+fpuStack+20h]
    fld     ds:__real@0000000000000000
    fstp    [ebp+fpuStack+28h]
    fld     ds:__real@0000000000000000
    fstp    [ebp+fpuStack+30h]
    fld     ds:__real@0000000000000000
    fstp    [ebp+fpuStack+38h]
  }
  _ESI = statePtr;
  __asm { fnstenv byte ptr [esi] }
  v1 = ~*((_DWORD *)_ESI + 2);
  v2 = 0;
  if ( (v1 & 0xC000) != 0 )
  {
    __asm { fst     qword ptr [edi] }
    v2 = 1;
    if ( (v1 & 0x3000) != 0 )
    {
      __asm
      {
        fxch    st(1)
        fst     qword ptr [edi+8]
      }
      v2 = 2;
      __asm { fxch    st(1) }
      if ( (v1 & 0xC00) != 0 )
      {
        __asm
        {
          fxch    st(2)
          fst     qword ptr [edi+10h]
        }
        v2 = 3;
        __asm { fxch    st(2) }
        if ( (v1 & 0x300) != 0 )
        {
          __asm
          {
            fxch    st(3)
            fst     qword ptr [edi+18h]
          }
          v2 = 4;
          __asm { fxch    st(3) }
          if ( (v1 & 0xC0) != 0 )
          {
            __asm
            {
              fxch    st(4)
              fst     qword ptr [edi+20h]
            }
            v2 = 5;
            __asm { fxch    st(4) }
            if ( (v1 & 0x30) != 0 )
            {
              __asm
              {
                fxch    st(5)
                fst     qword ptr [edi+28h]
              }
              v2 = 6;
              __asm { fxch    st(5) }
              if ( (v1 & 0xC) != 0 )
              {
                __asm
                {
                  fxch    st(6)
                  fst     qword ptr [edi+30h]
                }
                v2 = 7;
                __asm { fxch    st(6) }
                if ( (v1 & 3) != 0 )
                {
                  __asm
                  {
                    fxch    st(7)
                    fst     qword ptr [edi+38h]
                  }
                  v2 = 8;
                  __asm { fxch    st(7) }
                }
              }
            }
          }
        }
      }
    }
  }
  numValues = v2;
  v3 = *(_DWORD *)fpuState;
  stat = *(_DWORD *)&fpuState[4];
  inse = *(_DWORD *)&fpuState[16];
  tags = *(_DWORD *)&fpuState[8];
  inof = *(_DWORD *)&fpuState[12];
  opof = *(_DWORD *)&fpuState[20];
  fpuStackPtr = *(long double **)&fpuState[24];
  v4 = &fpuString[sprintf(fpuString, "FPU State:\nnum values on stack = %d\n", v2)];
  for ( _EDI = 0; _EDI < 8; ++_EDI )
  {
    __asm
    {
      fld     [ebp+edi*8+fpuStack]
      fstp    [esp+70h+var_70]
    }
    v6 = sprintf(v4, "ST%d = %1.10e\n", _EDI, v8);
    v4 += v6;
  }
  Sys_FPU_PrintStateFlags(v4, v3, stat, tags, inof, inse, opof, (int)fpuStackPtr);
  return fpuString;
}

// FUNC: void __cdecl Sys_FPU_EnableExceptions(int)
void __cdecl Sys_FPU_EnableExceptions(char exceptions)
{
  *(_WORD *)statePtr = ~(exceptions & 0x3F) & (*(_WORD *)statePtr | 0x3F);
}

// FUNC: void __cdecl Sys_FPU_SetPrecision(int)
void __cdecl Sys_FPU_SetPrecision(char precision)
{
  unsigned __int16 v1; // cx
  int precisionBits; // [esp+4h] [ebp-8h]
  __int16 v3; // [esp+8h] [ebp-4h]
  __int16 v4; // [esp+Ah] [ebp-2h]

  precisionBits = 0x10000;
  v4 = 0;
  LOBYTE(v1) = 0;
  v3 = 3;
  HIBYTE(v1) = *((_BYTE *)&precisionBits + 2 * (precision & 3));
  precisionBits = v1;
  *(_WORD *)statePtr = v1 | *(_WORD *)statePtr & 0xFCFF;
}

// FUNC: void __cdecl Sys_FPU_SetDAZ(bool)
void __cdecl Sys_FPU_SetDAZ(bool enable)
{
  _mm_setcsr((enable << 6) | _mm_getcsr() & 0xFFFFFFBF);
}

// FUNC: void __cdecl Sys_FPU_SetFTZ(bool)
void __cdecl Sys_FPU_SetFTZ(bool enable)
{
  _mm_setcsr((enable << 15) | _mm_getcsr() & 0xFFFF7FFF);
}
