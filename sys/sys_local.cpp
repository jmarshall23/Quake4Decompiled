
// FUNC: public: virtual void __cdecl idSysLocal::DebugPrintf(char const *,...)
void idSysLocal::DebugPrintf(idSysLocal *this, const char *fmt, ...)
{
  va_list arg; // [esp+Ch] [ebp+Ch] BYREF

  va_start(arg, fmt);
  Sys_DebugVPrintf(fmt, arg);
}

// FUNC: public: virtual void __thiscall idSysLocal::DebugVPrintf(char const *,char *)
void __thiscall idSysLocal::DebugVPrintf(idSysLocal *this, const char *fmt, char *arg)
{
  Sys_DebugVPrintf(fmt, arg);
}

// FUNC: public: virtual double __thiscall idSysLocal::GetClockTicks(void)
// attributes: thunk
long double __thiscall idSysLocal::GetClockTicks(idSysLocal *this)
{
  return Sys_GetClockTicks();
}

// FUNC: public: virtual double __thiscall idSysLocal::ClockTicksPerSecond(void)
// attributes: thunk
long double __thiscall idSysLocal::ClockTicksPerSecond(idSysLocal *this)
{
  return Sys_ClockTicksPerSecond();
}

// FUNC: public: virtual enum cpuid_t __thiscall idSysLocal::GetProcessorId(void)
// attributes: thunk
cpuid_t __thiscall idSysLocal::GetProcessorId(idSysLocal *this)
{
  return Sys_GetProcessorId();
}

// FUNC: public: virtual char const * __thiscall idSysLocal::GetProcessorString(void)
// attributes: thunk
const char *__thiscall idSysLocal::GetProcessorString(idSysLocal *this)
{
  return Sys_GetProcessorString();
}

// FUNC: public: virtual char const * __thiscall idSysLocal::FPU_GetState(void)
// attributes: thunk
const char *__thiscall idSysLocal::FPU_GetState(idSysLocal *this)
{
  return Sys_FPU_GetState();
}

// FUNC: public: virtual bool __thiscall idSysLocal::FPU_StackIsEmpty(void)
// attributes: thunk
bool __thiscall idSysLocal::FPU_StackIsEmpty(idSysLocal *this)
{
  return Sys_FPU_StackIsEmpty();
}

// FUNC: public: virtual void __thiscall idSysLocal::FPU_SetFTZ(bool)
void __thiscall idSysLocal::FPU_SetFTZ(idSysLocal *this, bool enable)
{
  Sys_FPU_SetFTZ(enable);
}

// FUNC: public: virtual void __thiscall idSysLocal::FPU_SetDAZ(bool)
void __thiscall idSysLocal::FPU_SetDAZ(idSysLocal *this, bool enable)
{
  Sys_FPU_SetDAZ(enable);
}

// FUNC: public: virtual bool __thiscall idSysLocal::LockMemory(void *,int)
bool __thiscall idSysLocal::LockMemory(idSysLocal *this, void *ptr, int bytes)
{
  return Sys_LockMemory(ptr, bytes);
}

// FUNC: public: virtual bool __thiscall idSysLocal::UnlockMemory(void *,int)
bool __thiscall idSysLocal::UnlockMemory(idSysLocal *this, void *ptr, int bytes)
{
  return Sys_UnlockMemory(ptr, bytes);
}

// FUNC: public: virtual void __thiscall idSysLocal::GetCallStack(unsigned long *,int)
void __thiscall idSysLocal::GetCallStack(idSysLocal *this, unsigned int *callStack, int callStackSize)
{
  Sys_GetCallStack(callStack, callStackSize);
}

// FUNC: public: virtual char const * __thiscall idSysLocal::GetCallStackStr(unsigned long const *,int)
const char *__thiscall idSysLocal::GetCallStackStr(idSysLocal *this, const unsigned int *callStack, int callStackSize)
{
  return Sys_GetCallStackStr(callStack, callStackSize);
}

// FUNC: public: virtual char const * __thiscall idSysLocal::GetCallStackCurStr(int)
const char *__thiscall idSysLocal::GetCallStackCurStr(idSysLocal *this, int depth)
{
  return Sys_GetCallStackCurStr(depth);
}

// FUNC: public: virtual int __thiscall idSysLocal::DLL_Load(char const *)
int __thiscall idSysLocal::DLL_Load(idSysLocal *this, const char *dllName)
{
  return Sys_DLL_Load(dllName);
}

// FUNC: public: virtual void * __thiscall idSysLocal::DLL_GetProcAddress(int,char const *)
void *__thiscall idSysLocal::DLL_GetProcAddress(idSysLocal *this, int dllHandle, const char *procName)
{
  return Sys_DLL_GetProcAddress(dllHandle, procName);
}

// FUNC: public: virtual void __thiscall idSysLocal::DLL_Unload(int)
void __thiscall idSysLocal::DLL_Unload(idSysLocal *this, int dllHandle)
{
  Sys_DLL_Unload(dllHandle);
}

// FUNC: public: virtual void __thiscall idSysLocal::DLL_GetFileName(char const *,char *,int)
void __thiscall idSysLocal::DLL_GetFileName(idSysLocal *this, const char *baseName, char *dllName, int maxLength)
{
  idStr::snPrintf(dllName, maxLength, "%sx86.dll", baseName);
}

// FUNC: public: virtual struct sysEvent_s __thiscall idSysLocal::GenerateMouseButtonEvent(int,bool)
sysEvent_s *__thiscall idSysLocal::GenerateMouseButtonEvent(
        idSysLocal *this,
        sysEvent_s *result,
        int button,
        bool down)
{
  sysEvent_s *v4; // eax

  v4 = result;
  result->evType = SE_KEY;
  result->evValue = button + 186;
  result->evValue2 = down;
  result->evPtrLength = 0;
  result->evPtr = 0;
  return v4;
}

// FUNC: public: virtual struct sysEvent_s __thiscall idSysLocal::GenerateMouseMoveEvent(int,int)
sysEvent_s *__thiscall idSysLocal::GenerateMouseMoveEvent(idSysLocal *this, sysEvent_s *result, int deltax, int deltay)
{
  sysEvent_s *v4; // eax

  v4 = result;
  result->evType = SE_MOUSE;
  result->evValue = deltax;
  result->evValue2 = deltay;
  result->evPtrLength = 0;
  result->evPtr = 0;
  return v4;
}

// FUNC: public: virtual int __thiscall idSysLocal::MapKey(unsigned long,unsigned short)
int __thiscall idSysLocal::MapKey(idSysLocal *this, unsigned int key, unsigned __int16 wParam)
{
  return Sys_MapKey(key, wParam);
}

// FUNC: public: virtual void __thiscall idSysLocal::AddKeyPress(int,bool)
void __thiscall idSysLocal::AddKeyPress(idSysLocal *this, __int16 keynum, bool down)
{
  int v3; // eax

  if ( idSysLocal::free > 0 )
  {
    v3 = idSysLocal::head;
    --idSysLocal::free;
    idSysLocal::keyPress[idSysLocal::head].keynum = keynum;
    byte_11310FBA[4 * v3] = down;
    idSysLocal::head = (unsigned __int8)(v3 + 1);
  }
}

// FUNC: public: virtual bool __thiscall idSysLocal::GetKeyPress(int,int &,bool &)
bool __thiscall idSysLocal::GetKeyPress(idSysLocal *this, int n, int *key, bool *state)
{
  bool result; // al

  if ( idSysLocal::free >= 250 )
    return 0;
  *key = idSysLocal::keyPress[idSysLocal::tail].keynum;
  *state = byte_11310FBA[4 * idSysLocal::tail];
  result = 1;
  ++idSysLocal::free;
  idSysLocal::tail = (unsigned __int8)(idSysLocal::tail + 1);
  return result;
}

// FUNC: public: virtual int __thiscall idSysLocal::GetNumKeyPresses(void)
int __thiscall idSysLocal::GetNumKeyPresses(idSysLocal *this)
{
  return 250 - idSysLocal::free;
}

// FUNC: public: virtual void __thiscall idSysLocal::ShowConsole(int,bool)
void __thiscall idSysLocal::ShowConsole(idSysLocal *this, int visLevel, bool quitOnClose)
{
  Sys_ShowConsole(visLevel, quitOnClose);
}

// FUNC: public: virtual void __thiscall idSysLocal::UpdateConsole(void)
// attributes: thunk
void __thiscall idSysLocal::UpdateConsole(idSysLocal *this)
{
  Sys_UpdateConsole();
}

// FUNC: public: virtual bool __thiscall idSysLocal::IsAppActive(void)const
// attributes: thunk
bool __thiscall idSysLocal::IsAppActive(idSysLocal *this)
{
  return Sys_IsAppActive();
}

// FUNC: public: virtual int __thiscall idSysLocal::Milliseconds(void)
// attributes: thunk
int __thiscall idSysLocal::Milliseconds(idSoundSystemLocal *this)
{
  return Sys_Milliseconds();
}

// FUNC: public: virtual void __thiscall idSysLocal::GrabMouseCursor(bool)
void __thiscall idSysLocal::GrabMouseCursor(idSysLocal *this, bool grabIt)
{
  Sys_GrabMouseCursor(grabIt);
}

// FUNC: public: virtual void __thiscall idSysLocal::GenerateEvents(void)
// attributes: thunk
void __thiscall idSysLocal::GenerateEvents(idSysLocal *this)
{
  Sys_GenerateEvents();
}

// FUNC: public: virtual void __thiscall idSysLocal::InitInput(void)
// attributes: thunk
void __thiscall idSysLocal::InitInput(idSysLocal *this)
{
  Sys_InitInput();
}

// FUNC: public: virtual void __thiscall idSysLocal::ShutdownInput(void)
// attributes: thunk
void __thiscall idSysLocal::ShutdownInput(idSysLocal *this)
{
  Sys_ShutdownInput();
}

// FUNC: char const * __cdecl Sys_TimeStampToStr(long)
char *__cdecl Sys_TimeStampToStr(int timeStamp)
{
  tm *v1; // edi
  idCVarSystem_vtbl *v2; // eax
  const char *v3; // eax
  const char *v4; // esi
  int v5; // edi
  char *data; // edx
  char *v7; // ecx
  char v8; // al
  char *v9; // eax
  int v10; // esi
  int v11; // eax
  char v12; // cl
  char *v13; // edx
  const char *v14; // eax
  const char *v15; // esi
  int v16; // edi
  char v17; // cl
  int i; // eax
  char *v19; // edx
  int v20; // esi
  int v21; // eax
  char v22; // cl
  char *v23; // edx
  const char *v24; // eax
  const char *v25; // esi
  int v26; // edi
  char v27; // cl
  int j; // eax
  char *v29; // edx
  int v30; // esi
  int v31; // eax
  char v32; // cl
  char *v33; // edx
  int tm_hour; // eax
  const char *v35; // eax
  const char *v36; // esi
  unsigned int v37; // kr08_4
  int v38; // edi
  char v39; // cl
  int m; // eax
  char *v41; // edx
  int v42; // esi
  int v43; // eax
  char v44; // cl
  char *v45; // edx
  const char *v46; // eax
  const char *v47; // esi
  char v48; // cl
  int k; // eax
  char *v50; // edx
  int v51; // esi
  int v52; // eax
  char v53; // cl
  char *v54; // edx
  const char *v55; // eax
  const char *v56; // esi
  int v57; // edi
  char v58; // cl
  int n; // eax
  char *v60; // edx
  int v61; // esi
  int v62; // eax
  int v63; // eax
  char v64; // cl
  char *v65; // edx
  int v66; // eax
  char v67; // cl
  char *v68; // edx
  char *v69; // eax
  int v70; // esi
  int v71; // eax
  char v72; // cl
  char *v73; // edx
  const char *v74; // eax
  const char *v75; // esi
  int v76; // edi
  char v77; // cl
  int ii; // eax
  char *v79; // edx
  int v80; // esi
  int v81; // eax
  char v82; // cl
  char *v83; // edx
  const char *v84; // eax
  const char *v85; // esi
  int v86; // edi
  char v87; // cl
  int jj; // eax
  char *v89; // edx
  int v90; // esi
  int v91; // eax
  char v92; // cl
  char *v93; // edx
  const char *v94; // eax
  const char *v95; // esi
  int v96; // edi
  char v97; // cl
  int kk; // eax
  char *v99; // edx
  int v100; // esi
  int v101; // eax
  char v102; // cl
  char *v103; // edx
  const char *v104; // eax
  const char *v105; // esi
  int v106; // edi
  char v107; // cl
  int mm; // eax
  char *v109; // edx
  int ts; // [esp+10h] [ebp-50h] BYREF
  idStr out; // [esp+14h] [ebp-4Ch] BYREF
  idStr lang; // [esp+34h] [ebp-2Ch] BYREF
  int v114; // [esp+5Ch] [ebp-4h]
  tm *timeStampa; // [esp+64h] [ebp+4h]

  timeString[0] = 0;
  ts = timeStamp;
  v1 = localtime(&ts);
  timeStampa = v1;
  out.len = 0;
  out.alloced = 20;
  out.data = out.baseBuffer;
  out.baseBuffer[0] = 0;
  v2 = cvarSystem->__vftable;
  v114 = 0;
  v3 = v2->GetCVarString(cvarSystem, "sys_lang");
  v4 = v3;
  lang.len = 0;
  lang.alloced = 20;
  lang.data = lang.baseBuffer;
  lang.baseBuffer[0] = 0;
  if ( v3 )
  {
    v5 = strlen(v3);
    if ( v5 + 1 > 20 )
      idStr::ReAllocate(&lang, v5 + 1, 1);
    data = lang.data;
    v7 = (char *)v4;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    lang.len = v5;
    v1 = timeStampa;
  }
  LOBYTE(v114) = 1;
  if ( !idStr::Icmp(lang.data, "english") )
  {
    v9 = va("%02d", v1->tm_mon + 1);
    idStr::operator=(&out, v9);
    v10 = out.len + 1;
    if ( out.len + 2 > out.alloced )
      idStr::ReAllocate(&out, out.len + 2, 1);
    v11 = 0;
    v12 = 47;
    do
    {
      v13 = &out.data[v11++];
      v13[out.len] = v12;
      v12 = b[v11];
    }
    while ( v12 );
    out.len = v10;
    out.data[v10] = 0;
    v14 = va("%02d", timeStampa->tm_mday);
    v15 = v14;
    if ( v14 )
    {
      v16 = strlen(v14) + out.len;
      if ( v16 + 1 > out.alloced )
        idStr::ReAllocate(&out, v16 + 1, 1);
      v17 = *v15;
      for ( i = 0; v17; v17 = v15[i] )
      {
        v19 = &out.data[i++];
        v19[out.len] = v17;
      }
      out.len = v16;
      out.data[v16] = 0;
    }
    v20 = out.len + 1;
    if ( out.len + 2 > out.alloced )
      idStr::ReAllocate(&out, out.len + 2, 1);
    v21 = 0;
    v22 = 47;
    do
    {
      v23 = &out.data[v21++];
      v23[out.len] = v22;
      v22 = b[v21];
    }
    while ( v22 );
    out.len = v20;
    out.data[v20] = 0;
    v24 = va("%d", timeStampa->tm_year + 1900);
    v25 = v24;
    if ( v24 )
    {
      v26 = strlen(v24) + out.len;
      if ( v26 + 1 > out.alloced )
        idStr::ReAllocate(&out, v26 + 1, 1);
      v27 = *v25;
      for ( j = 0; v27; v27 = v25[j] )
      {
        v29 = &out.data[j++];
        v29[out.len] = v27;
      }
      out.len = v26;
      out.data[v26] = 0;
    }
    v30 = out.len + 1;
    if ( out.len + 2 > out.alloced )
      idStr::ReAllocate(&out, out.len + 2, 1);
    v31 = 0;
    v32 = 9;
    do
    {
      v33 = &out.data[v31++];
      v33[out.len] = v32;
      v32 = prepend[v31];
    }
    while ( v32 );
    out.len = v30;
    out.data[v30] = 0;
    tm_hour = timeStampa->tm_hour;
    if ( tm_hour <= 12 )
    {
      if ( !tm_hour )
      {
        v42 = out.len + 2;
        if ( out.len + 3 > out.alloced )
          idStr::ReAllocate(&out, out.len + 3, 1);
        v43 = 0;
        v44 = 49;
        do
        {
          v45 = &out.data[v43++];
          v45[out.len] = v44;
          v44 = a12[v43];
        }
        while ( v44 );
        out.len = v42;
        out.data[v42] = 0;
        goto LABEL_51;
      }
      v46 = va("%02d", timeStampa->tm_hour);
      v47 = v46;
      if ( v46 )
      {
        v38 = strlen(v46) + out.len;
        if ( v38 + 1 > out.alloced )
          idStr::ReAllocate(&out, v38 + 1, 1);
        v48 = *v47;
        for ( k = 0; v48; v48 = v47[k] )
        {
          v50 = &out.data[k++];
          v50[out.len] = v48;
        }
        goto LABEL_50;
      }
    }
    else
    {
      v35 = va("%02d", tm_hour - 12);
      v36 = v35;
      if ( v35 )
      {
        v37 = strlen(v35);
        v38 = v37 + out.len;
        if ( (int)(v37 + out.len + 1) > out.alloced )
          idStr::ReAllocate(&out, v37 + out.len + 1, 1);
        v39 = *v36;
        for ( m = 0; v39; v39 = v36[m] )
        {
          v41 = &out.data[m++];
          v41[out.len] = v39;
        }
LABEL_50:
        out.len = v38;
        out.data[v38] = 0;
      }
    }
LABEL_51:
    v51 = out.len + 1;
    if ( out.len + 2 > out.alloced )
      idStr::ReAllocate(&out, out.len + 2, 1);
    v52 = 0;
    v53 = 58;
    do
    {
      v54 = &out.data[v52++];
      v54[out.len] = v53;
      v53 = asc_102CBE6C[v52];
    }
    while ( v53 );
    out.len = v51;
    out.data[v51] = 0;
    v55 = va("%02d", timeStampa->tm_min);
    v56 = v55;
    if ( v55 )
    {
      v57 = strlen(v55) + out.len;
      if ( v57 + 1 > out.alloced )
        idStr::ReAllocate(&out, v57 + 1, 1);
      v58 = *v56;
      for ( n = 0; v58; v58 = v56[n] )
      {
        v60 = &out.data[n++];
        v60[out.len] = v58;
      }
      out.len = v57;
      out.data[v57] = 0;
    }
    v61 = out.len + 2;
    v62 = out.len + 3;
    if ( timeStampa->tm_hour < 12 )
    {
      if ( v62 > out.alloced )
        idStr::ReAllocate(&out, out.len + 3, 1);
      v66 = 0;
      v67 = 97;
      do
      {
        v68 = &out.data[v66++];
        v68[out.len] = v67;
        v67 = aAm[v66];
      }
      while ( v67 );
      out.len = v61;
      out.data[v61] = 0;
    }
    else
    {
      if ( v62 > out.alloced )
        idStr::ReAllocate(&out, out.len + 3, 1);
      v63 = 0;
      v64 = 112;
      do
      {
        v65 = &out.data[v63++];
        v65[out.len] = v64;
        v64 = aPm_0[v63];
      }
      while ( v64 );
      out.len = v61;
      out.data[v61] = 0;
    }
    goto LABEL_112;
  }
  v69 = va("%02d", v1->tm_mday);
  idStr::operator=(&out, v69);
  v70 = out.len + 1;
  if ( out.len + 2 > out.alloced )
    idStr::ReAllocate(&out, out.len + 2, 1);
  v71 = 0;
  v72 = 47;
  do
  {
    v73 = &out.data[v71++];
    v73[out.len] = v72;
    v72 = b[v71];
  }
  while ( v72 );
  out.len = v70;
  out.data[v70] = 0;
  v74 = va("%02d", timeStampa->tm_mon + 1);
  v75 = v74;
  if ( v74 )
  {
    v76 = strlen(v74) + out.len;
    if ( v76 + 1 > out.alloced )
      idStr::ReAllocate(&out, v76 + 1, 1);
    v77 = *v75;
    for ( ii = 0; v77; v77 = v75[ii] )
    {
      v79 = &out.data[ii++];
      v79[out.len] = v77;
    }
    out.len = v76;
    out.data[v76] = 0;
  }
  v80 = out.len + 1;
  if ( out.len + 2 > out.alloced )
    idStr::ReAllocate(&out, out.len + 2, 1);
  v81 = 0;
  v82 = 47;
  do
  {
    v83 = &out.data[v81++];
    v83[out.len] = v82;
    v82 = b[v81];
  }
  while ( v82 );
  out.len = v80;
  out.data[v80] = 0;
  v84 = va("%d", timeStampa->tm_year + 1900);
  v85 = v84;
  if ( v84 )
  {
    v86 = strlen(v84) + out.len;
    if ( v86 + 1 > out.alloced )
      idStr::ReAllocate(&out, v86 + 1, 1);
    v87 = *v85;
    for ( jj = 0; v87; v87 = v85[jj] )
    {
      v89 = &out.data[jj++];
      v89[out.len] = v87;
    }
    out.len = v86;
    out.data[v86] = 0;
  }
  v90 = out.len + 1;
  if ( out.len + 2 > out.alloced )
    idStr::ReAllocate(&out, out.len + 2, 1);
  v91 = 0;
  v92 = 9;
  do
  {
    v93 = &out.data[v91++];
    v93[out.len] = v92;
    v92 = prepend[v91];
  }
  while ( v92 );
  out.len = v90;
  out.data[v90] = 0;
  v94 = va("%02d", timeStampa->tm_hour);
  v95 = v94;
  if ( v94 )
  {
    v96 = strlen(v94) + out.len;
    if ( v96 + 1 > out.alloced )
      idStr::ReAllocate(&out, v96 + 1, 1);
    v97 = *v95;
    for ( kk = 0; v97; v97 = v95[kk] )
    {
      v99 = &out.data[kk++];
      v99[out.len] = v97;
    }
    out.len = v96;
    out.data[v96] = 0;
  }
  v100 = out.len + 1;
  if ( out.len + 2 > out.alloced )
    idStr::ReAllocate(&out, out.len + 2, 1);
  v101 = 0;
  v102 = 58;
  do
  {
    v103 = &out.data[v101++];
    v103[out.len] = v102;
    v102 = asc_102CBE6C[v101];
  }
  while ( v102 );
  out.len = v100;
  out.data[v100] = 0;
  v104 = va("%02d", timeStampa->tm_min);
  v105 = v104;
  if ( v104 )
  {
    v106 = strlen(v104) + out.len;
    if ( v106 + 1 > out.alloced )
      idStr::ReAllocate(&out, v106 + 1, 1);
    v107 = *v105;
    for ( mm = 0; v107; v107 = v105[mm] )
    {
      v109 = &out.data[mm++];
      v109[out.len] = v107;
    }
    out.len = v106;
    out.data[v106] = 0;
  }
LABEL_112:
  idStr::Copynz(timeString, out.data, 1024);
  LOBYTE(v114) = 0;
  idStr::FreeData(&lang);
  v114 = -1;
  idStr::FreeData(&out);
  return timeString;
}
