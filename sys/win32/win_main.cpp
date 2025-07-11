
// FUNC: void __cdecl Sys_DestroyThread(struct xthreadInfo &)
void __cdecl Sys_DestroyThread(xthreadInfo *info)
{
  WaitForSingleObject((HANDLE)info->threadHandle, 0xFFFFFFFF);
  CloseHandle((HANDLE)info->threadHandle);
  info->threadHandle = 0;
}

// FUNC: void __cdecl Sys_EnterCriticalSection(int)
void __cdecl Sys_EnterCriticalSection(int index)
{
  if ( !TryEnterCriticalSection(&win32.criticalSections[index]) )
    EnterCriticalSection(&win32.criticalSections[index]);
}

// FUNC: void __cdecl Sys_LeaveCriticalSection(int)
void __cdecl Sys_LeaveCriticalSection(int index)
{
  LeaveCriticalSection(&win32.criticalSections[index]);
}

// FUNC: void __cdecl Sys_WaitForEvent(int)
void __cdecl Sys_WaitForEvent()
{
  if ( !win32.backgroundDownloadSemaphore )
    win32.backgroundDownloadSemaphore = CreateEventA(0, 1, 0, 0);
  WaitForSingleObject(win32.backgroundDownloadSemaphore, 0xFFFFFFFF);
  ResetEvent(win32.backgroundDownloadSemaphore);
}

// FUNC: void __cdecl Sys_TriggerEvent(int)
void __cdecl Sys_TriggerEvent()
{
  SetEvent(win32.backgroundDownloadSemaphore);
}

// FUNC: void __cdecl Sys_Error(char const *,...)
void __usercall __noreturn Sys_Error(int a1@<edi>, int a2@<esi>, char *error, ...)
{
  tagMSG Msg; // [esp+8h] [ebp-101Ch] BYREF
  char string[4096]; // [esp+24h] [ebp-1000h] BYREF
  va_list ap; // [esp+102Ch] [ebp+8h] BYREF

  va_start(ap, error);
  vsprintf(string, error, ap);
  Conbuf_AppendText(string);
  Conbuf_AppendText("\n");
  Win_SetErrorText(string);
  sys->ShowConsole(sys, 1, 1);
  timeEndPeriod(1u);
  sys->ShutdownInput(sys);
  GLimp_Shutdown(a1, a2);
  while ( !win32.sysErrorNoWait )
  {
    if ( !GetMessageA(&Msg, 0, 0, 0) )
      (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 12))(common.type);
    TranslateMessage(&Msg);
    DispatchMessageA(&Msg);
  }
  Sys_DestroyConsole();
  exit(1);
}

// FUNC: void __cdecl Sys_Quit(void)
void __cdecl __noreturn Sys_Quit()
{
  systemShuttingDown = 1;
  if ( threadInfo.threadHandle )
    Sys_DestroyThread(&threadInfo);
  if ( hTimer )
  {
    CloseHandle(hTimer);
    hTimer = 0;
  }
  timeEndPeriod(1u);
  sys->ShutdownInput(sys);
  Sys_DestroyConsole();
  CI_ShutdownCrashReporting();
  ExitProcess(0);
}

// FUNC: void __cdecl Sys_Printf(char const *,...)
void Sys_Printf(char *fmt, ...)
{
  char dest[4096]; // [esp+0h] [ebp-1000h] BYREF
  va_list argptr; // [esp+1008h] [ebp+8h] BYREF

  va_start(argptr, fmt);
  idStr::vsnPrintf(dest, 4095, fmt, argptr);
  dest[4095] = 0;
  if ( win32.outputDebugString )
    OutputDebugStringA(dest);
  if ( win32.outputEditString )
    Conbuf_AppendText(dest);
}

// FUNC: void __cdecl Sys_DebugPrintf(char const *,...)
void Sys_DebugPrintf(char *fmt, ...)
{
  char dest[4096]; // [esp+0h] [ebp-1000h] BYREF
  va_list argptr; // [esp+1008h] [ebp+8h] BYREF

  va_start(argptr, fmt);
  idStr::vsnPrintf(dest, 4095, fmt, argptr);
  dest[4095] = 0;
  OutputDebugStringA(dest);
}

// FUNC: void __cdecl Sys_DebugVPrintf(char const *,char *)
void __cdecl Sys_DebugVPrintf(char *fmt, char *arg)
{
  char dest[4096]; // [esp+0h] [ebp-1000h] BYREF

  idStr::vsnPrintf(dest, 4095, fmt, arg);
  dest[4095] = 0;
  OutputDebugStringA(dest);
}

// FUNC: void __cdecl Sys_Sleep(int)
void __cdecl Sys_Sleep(int msec)
{
  Sleep(msec);
}

// FUNC: void __cdecl Sys_Mkdir(char const *)
// attributes: thunk
void __cdecl Sys_Mkdir(const char *path)
{
  mkdir(path);
}

// FUNC: long __cdecl Sys_FileTimeStamp(struct _iobuf *)
int __cdecl Sys_FileTimeStamp(_iobuf *fp)
{
  _stat st; // [esp+0h] [ebp-24h] BYREF

  _fstat(fp->_file, &st);
  return st.st_mtime;
}

// FUNC: _PBsdk_GetKeyValue
const char *__cdecl PBsdk_GetKeyValue()
{
  return &entityFilter;
}

// FUNC: char const * __cdecl Sys_DefaultSavePath(void)
const char *__cdecl Sys_DefaultSavePath()
{
  return cvarSystem->GetCVarString(cvarSystem, "fs_basepath");
}

// FUNC: char * __cdecl Sys_GetClipboardData(void)
char *__cdecl Sys_GetClipboardData()
{
  char *v0; // ebx
  HANDLE ClipboardData; // eax
  void *v2; // edi
  const char *v3; // esi
  SIZE_T v4; // eax

  v0 = 0;
  if ( OpenClipboard(0) )
  {
    ClipboardData = GetClipboardData(1u);
    v2 = ClipboardData;
    if ( ClipboardData )
    {
      v3 = (const char *)GlobalLock(ClipboardData);
      if ( v3 )
      {
        v4 = GlobalSize(v2);
        v0 = (char *)Mem_Alloc(v4 + 1, 0x13u);
        strcpy(v0, v3);
        GlobalUnlock(v2);
        strtok(v0, "\n\r\b");
      }
    }
    CloseClipboard();
  }
  return v0;
}

// FUNC: void __cdecl Sys_SetClipboardData(char const *)
void __cdecl Sys_SetClipboardData(const char *string)
{
  HGLOBAL v1; // eax
  void *v2; // esi
  char *v3; // eax

  v1 = GlobalAlloc(0x2002u, strlen(string) + 1);
  v2 = v1;
  if ( v1 )
  {
    v3 = (char *)GlobalLock(v1);
    if ( v3 )
    {
      lstrcpyA(v3, string);
      GlobalUnlock(v2);
      if ( OpenClipboard(0) )
      {
        EmptyClipboard();
        SetClipboardData(1u, v2);
        CloseClipboard();
      }
      else
      {
        GlobalFree(v2);
      }
    }
  }
}

// FUNC: void * __cdecl Sys_DLL_GetProcAddress(int,char const *)
FARPROC __cdecl Sys_DLL_GetProcAddress(HMODULE dllHandle, const char *procName)
{
  return GetProcAddress(dllHandle, procName);
}

// FUNC: void __cdecl Sys_DLL_Unload(int)
void __usercall Sys_DLL_Unload(int a1@<edi>, char *dllHandle)
{
  DWORD LastError; // esi

  if ( dllHandle )
  {
    if ( !FreeLibrary((HMODULE)dllHandle) )
    {
      LastError = GetLastError();
      FormatMessageA(0x100u, 0, LastError, 0x400u, (LPSTR)&dllHandle, 0, 0);
      Sys_Error(a1, LastError, "Sys_DLL_Unload: FreeLibrary failed - %s (%d)", dllHandle, LastError);
    }
  }
}

// FUNC: void __cdecl Sys_PurgeMouseEvents(void)
void __cdecl Sys_PurgeMouseEvents()
{
  int v0; // edx
  int v1; // edi
  int i; // esi
  sysEvent_s *v3; // eax
  sysEvent_s *v4; // ecx

  v0 = eventTail;
  v1 = eventHead;
  for ( i = eventTail; v0 < v1; ++v0 )
  {
    v3 = &eventQue[(unsigned __int8)v0];
    if ( v3->evType != SE_MOUSE )
    {
      v4 = &eventQue[(unsigned __int8)i];
      v4->evType = v3->evType;
      v4->evValue = v3->evValue;
      v4->evValue2 = v3->evValue2;
      v4->evPtrLength = v3->evPtrLength;
      v4->evPtr = v3->evPtr;
      ++i;
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "Sys_PurgeMouseEvents: %d events purged\n",
    v1 - i);
  eventHead = i;
}

// FUNC: void __cdecl Sys_QueEvent(int,enum sysEventType_t,int,int,int,void *)
void __cdecl Sys_QueEvent(int time, sysEventType_t type, int value, int value2, int ptrLength, void *ptr)
{
  sysEvent_s *v6; // esi

  v6 = &eventQue[(unsigned __int8)eventHead];
  if ( eventHead - eventTail >= 256 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Sys_QueEvent: overflow\n");
    Sys_PurgeMouseEvents();
    if ( v6->evPtr )
      Mem_Free(v6->evPtr);
    ++eventTail;
  }
  ++eventHead;
  v6->evType = type;
  v6->evValue = value;
  v6->evValue2 = value2;
  v6->evPtrLength = ptrLength;
  v6->evPtr = ptr;
}

// FUNC: void __cdecl Sys_ClearEvents(void)
void __cdecl Sys_ClearEvents()
{
  eventTail = 0;
  eventHead = 0;
}

// FUNC: struct sysEvent_s __cdecl Sys_GetEvent(void)
sysEvent_s *__cdecl Sys_GetEvent(sysEvent_s *result)
{
  unsigned __int8 v1; // al
  sysEvent_s *v2; // ecx
  sysEvent_s *v3; // eax

  v1 = eventTail;
  if ( eventHead <= eventTail )
  {
    v3 = result;
    result->evType = SE_NONE;
    result->evValue = 0;
    result->evValue2 = 0;
    result->evPtrLength = 0;
    result->evPtr = 0;
  }
  else
  {
    ++eventTail;
    v2 = &eventQue[v1];
    v3 = result;
    *result = *v2;
  }
  return v3;
}

// FUNC: void __cdecl Sys_In_Restart_f(class idCmdArgs const &)
void __cdecl Sys_In_Restart_f()
{
  sys->ShutdownInput(sys);
  sys->InitInput(sys);
}

// FUNC: Sys_AsyncThread
void __cdecl Sys_AsyncThread()
{
  Sys_Milliseconds();
  while ( !systemShuttingDown )
  {
    if ( WaitForSingleObject(hTimer, 0x64u) )
      OutputDebugStringA("idPacketServer::PacketServerInterrupt: bad wait return");
    (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 28))(common.type);
  }
}

// FUNC: void __cdecl Sys_StartAsyncThread(void)
void __cdecl Sys_StartAsyncThread()
{
  LONG v0; // eax
  _LARGE_INTEGER t; // [esp+0h] [ebp-8h] BYREF

  hTimer = CreateWaitableTimerA(0, 0, 0);
  if ( !hTimer )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idPacketServer::Spawn: CreateWaitableTimer failed");
  t.QuadPart = 0i64;
  v0 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
  SetWaitableTimer(hTimer, &t, v0, 0, 0, 1);
  Sys_CreateThread(
    (unsigned int (__cdecl *)(void *))Sys_AsyncThread,
    0,
    THREAD_ABOVE_NORMAL,
    &threadInfo,
    "Async",
    g_threads,
    &g_thread_count);
  if ( !threadInfo.threadHandle )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "Sys_StartAsyncThread: failed");
}

// FUNC: void __cdecl Sys_Shutdown(void)
// attributes: thunk
void __stdcall Sys_Shutdown()
{
  CoUninitialize();
}

// FUNC: enum cpuid_t __cdecl Sys_GetProcessorId(void)
cpuid_t __cdecl Sys_GetProcessorId()
{
  return win32.cpuid;
}

// FUNC: public: virtual void __thiscall idSysLocal::OpenURL(char const *,bool)
void __thiscall idSysLocal::OpenURL(idSysLocal *this, const char *url, bool doexit)
{
  int v3; // ecx
  HWND ForegroundWindow; // eax
  idCmdSystem_vtbl *v5; // eax

  v3 = *(_DWORD *)common.type;
  if ( doexit_spamguard )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(v3 + 132))(
      common.type,
      "OpenURL: already in an exit sequence, ignoring %s\n",
      url);
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(v3 + 124))(common.type, "Open URL: %s\n", url);
    if ( ShellExecuteA(0, "open", url, 0, 0, 9) )
    {
      ForegroundWindow = GetForegroundWindow();
      if ( ForegroundWindow )
        sys->ShowWindow(sys, ForegroundWindow, 3);
      if ( doexit )
      {
        v5 = cmdSystem->__vftable;
        doexit_spamguard = 1;
        v5->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "quit\n");
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "Could not open url: '%s' ",
        url);
    }
  }
}

// FUNC: public: virtual void __thiscall idSysLocal::StartProcess(char const *,bool)
void __thiscall idSysLocal::StartProcess(idSysLocal *this, const char *exePath, bool doexit)
{
  _PROCESS_INFORMATION pi; // [esp+4h] [ebp-158h] BYREF
  _STARTUPINFOA StartupInfo; // [esp+14h] [ebp-148h] BYREF
  char szPathOrig[260]; // [esp+58h] [ebp-104h] BYREF

  memset(&StartupInfo, 0, sizeof(StartupInfo));
  StartupInfo.cb = 68;
  strncpy(szPathOrig, exePath, 0x104u);
  if ( CreateProcessA(0, szPathOrig, 0, 0, 0, 0, 0, 0, &StartupInfo, &pi) )
  {
    if ( doexit )
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "quit\n");
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Could not start process: '%s' ",
      szPathOrig);
  }
}

// FUNC: public: virtual void * __thiscall idSysLocal::CreateWindowExA(char const *,char const *,int,int,int,int,int,void *,void *,void *,void *,int)
HWND __thiscall idSysLocal::CreateWindowExA(
        idSysLocal *this,
        const char *className,
        const char *windowName,
        int style,
        int x,
        int y,
        int w,
        int h,
        HWND parent,
        HMENU menu,
        HINSTANCE instance,
        void *param,
        int extStyle)
{
  return CreateWindowExA(extStyle, className, windowName, style, x, y, w, h, parent, menu, instance, param);
}

// FUNC: public: virtual void * __thiscall idSysLocal::GetDC(void *)
// attributes: thunk
HDC __stdcall idSysLocal::GetDC(HWND hWnd)
{
  return GetDC(hWnd);
}

// FUNC: public: virtual void __thiscall idSysLocal::ReleaseDC(void *,void *)
// attributes: thunk
int __stdcall idSysLocal::ReleaseDC(HWND hWnd, HDC hDC)
{
  return ReleaseDC(hWnd, hDC);
}

// FUNC: public: virtual void __thiscall idSysLocal::ShowWindow(void *,int)
// attributes: thunk
BOOL __stdcall idSysLocal::ShowWindow(HWND hWnd, int nCmdShow)
{
  return ShowWindow(hWnd, nCmdShow);
}

// FUNC: public: virtual void __thiscall idSysLocal::UpdateWindow(void *)
// attributes: thunk
BOOL __stdcall idSysLocal::UpdateWindow(HWND hWnd)
{
  return UpdateWindow(hWnd);
}

// FUNC: public: virtual void __thiscall idSysLocal::SetForegroundWindow(void *)
// attributes: thunk
BOOL __stdcall idSysLocal::SetForegroundWindow(HWND hWnd)
{
  return SetForegroundWindow(hWnd);
}

// FUNC: public: virtual void __thiscall idSysLocal::SetFocus(void *)
// attributes: thunk
HWND __stdcall idSysLocal::SetFocus(HWND hWnd)
{
  return SetFocus(hWnd);
}

// FUNC: public: virtual bool __thiscall idSysLocal::IsWindowVisible(void *)
BOOL __thiscall idSysLocal::IsWindowVisible(idSysLocal *this, HWND hWnd)
{
  return IsWindowVisible(hWnd);
}

// FUNC: public: virtual void __thiscall idSysLocal::DestroyWindow(void *)
// attributes: thunk
BOOL __stdcall idSysLocal::DestroyWindow(HWND hWnd)
{
  return DestroyWindow(hWnd);
}

// FUNC: struct _iobuf * __cdecl Sys_FOpen(char const *,char const *)
// attributes: thunk
_iobuf *__cdecl Sys_FOpen(const char *name, const char *mode)
{
  return fopen(name, mode);
}

// FUNC: void __cdecl Sys_FPrintf(struct _iobuf *,char const *)
None

// FUNC: int __cdecl Sys_FTell(struct _iobuf *)
// attributes: thunk
int __cdecl Sys_FTell(_iobuf *file)
{
  return ftell(file);
}

// FUNC: int __cdecl Sys_FSeek(struct _iobuf *,long,int)
// attributes: thunk
int __cdecl Sys_FSeek(_iobuf *file, int offset, int mode)
{
  return fseek(file, offset, mode);
}

// FUNC: void __cdecl Sys_FClose(struct _iobuf *)
// attributes: thunk
void __cdecl Sys_FClose(_iobuf *file)
{
  fclose(file);
}

// FUNC: int __cdecl Sys_FRead(void *,int,int,struct _iobuf *)
// attributes: thunk
unsigned int __cdecl Sys_FRead(void *buffer, int size, int count, _iobuf *file)
{
  return fread(buffer, size, count, file);
}

// FUNC: int __cdecl Sys_FWrite(void *,int,int,struct _iobuf *)
// attributes: thunk
unsigned int __cdecl Sys_FWrite(void *buffer, int size, int count, _iobuf *file)
{
  return fwrite(buffer, size, count, file);
}

// FUNC: int __cdecl Sys_FEof(struct _iobuf *)
int __cdecl Sys_FEof(_iobuf *stream)
{
  return stream->_flag & 0x10;
}

// FUNC: char * __cdecl Sys_FGets(char *,int,struct _iobuf *)
// attributes: thunk
char *__cdecl Sys_FGets(char *string, int n, _iobuf *stream)
{
  return fgets(string, n, stream);
}

// FUNC: void __cdecl Sys_FFlush(struct _iobuf *)
// attributes: thunk
void __cdecl Sys_FFlush(_iobuf *f)
{
  fflush(f);
}

// FUNC: int __cdecl Sys_SetVBuf(struct _iobuf *,char *,int,unsigned int)
// attributes: thunk
int __cdecl Sys_SetVBuf(_iobuf *stream, char *buffer, int mode, unsigned int size)
{
  return setvbuf(stream, buffer, mode, size);
}

// FUNC: bool __cdecl Sys_LoadVTune(void)
bool __cdecl Sys_LoadVTune()
{
  HMODULE LibraryA; // eax

  LibraryA = vtuneDll;
  if ( !vtuneDll )
  {
    LibraryA = LoadLibraryA("vtuneapi.dll");
    vtuneDll = LibraryA;
    if ( LibraryA )
    {
      VTResume_f = (void (__cdecl *)())GetProcAddress(LibraryA, "VTResume");
      VTPause_f = (void (__cdecl *)())GetProcAddress(vtuneDll, "VTPause");
      LibraryA = vtuneDll;
    }
  }
  return LibraryA != 0;
}

// FUNC: bool __cdecl Sys_AppShouldSleep(void)
bool __cdecl Sys_AppShouldSleep()
{
  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 64))(common.type)
    || idAsyncNetwork::serverDedicated.internalVar->integerValue )
  {
    return 0;
  }
  if ( lastActiveApp && !win32.activeApp )
    startTime = Sys_Milliseconds();
  lastActiveApp = win32.activeApp;
  return (win32.activeApp || Sys_Milliseconds() >= startTime + 2000) && !win32.activeApp;
}

// FUNC: char const * __cdecl Sys_Cwd(void)
char *__cdecl Sys_Cwd()
{
  char *v0; // eax
  int v1; // esi
  int v2; // eax
  char *data; // edx
  char *v4; // ecx
  char v5; // al
  char *v6; // eax
  int v7; // edx
  char v8; // cl
  idStr ret; // [esp+4h] [ebp-2Ch] BYREF
  int v11; // [esp+2Ch] [ebp-4h]

  _getcwd(cwd, 255);
  ret.data = ret.baseBuffer;
  cwd[255] = 0;
  ret.len = 0;
  ret.alloced = 20;
  ret.baseBuffer[0] = 0;
  v0 = &cwd[strlen(cwd) + 1];
  v1 = v0 - &cwd[1];
  v2 = v0 - cwd;
  if ( v2 > 20 )
    idStr::ReAllocate(&ret, v2, 1);
  data = ret.data;
  v4 = cwd;
  do
  {
    v5 = *v4;
    *data++ = *v4++;
  }
  while ( v5 );
  ret.len = v1;
  v11 = 0;
  idStr::BackSlashesToSlashes(&ret);
  v6 = ret.data;
  v7 = cwd - ret.data;
  do
  {
    v8 = *v6;
    v6[v7] = *v6;
    ++v6;
  }
  while ( v8 );
  v11 = -1;
  idStr::FreeData(&ret);
  return cwd;
}

// FUNC: char const * __cdecl Sys_DefaultBasePath(void)
// attributes: thunk
char *__cdecl Sys_DefaultBasePath()
{
  return Sys_Cwd();
}

// FUNC: char const * __cdecl Sys_EXEPath(void)
char *__cdecl Sys_EXEPath()
{
  int i; // ecx
  int j; // eax

  GetModuleFileNameA(0, exe, 0xFFu);
  for ( i = 0; exe[i]; ++i )
    ;
  for ( j = 0; j < i; ++j )
  {
    if ( exe[j] == 92 )
      exe[j] = 47;
  }
  return exe;
}

// FUNC: int __cdecl Sys_DLL_Load(char const *)
HMODULE __cdecl Sys_DLL_Load(const char *dllName)
{
  HMODULE LibraryA; // esi
  char loadedPath[256]; // [esp+8h] [ebp-100h] BYREF

  LibraryA = LoadLibraryA(dllName);
  if ( !LibraryA )
    return LibraryA;
  GetModuleFileNameA(LibraryA, loadedPath, 0xFFu);
  if ( !idStr::IcmpPath(dllName, loadedPath) )
    return LibraryA;
  Sys_Printf("ERROR: LoadLibrary '%s' wants to load '%s'\n", dllName, loadedPath);
  Sys_DLL_Unload((int)dllName, (char *)LibraryA);
  return 0;
}

// FUNC: void __cdecl Sys_PumpEvents(void)
void __cdecl Sys_PumpEvents()
{
  tagMSG msg; // [esp+4h] [ebp-1Ch] BYREF

  if ( Sys_AppShouldSleep() )
    Sleep(0x64u);
  while ( PeekMessageA(&msg, 0, 0, 0, 0) )
  {
    if ( !GetMessageA(&msg, 0, 0, 0) )
      (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 12))(common.type);
    if ( !win32.sysMsgTime || win32.sysMsgTime <= (int)msg.time )
      win32.sysMsgTime = msg.time;
    if ( !(*(unsigned __int8 (__thiscall **)(_DWORD, tagMSG *))(**(_DWORD **)common.ip + 240))(
            *(_DWORD *)common.ip,
            &msg) )
    {
      TranslateMessage(&msg);
      DispatchMessageA(&msg);
    }
  }
}

// FUNC: void __cdecl Sys_GenerateEvents(void)
void __cdecl Sys_GenerateEvents()
{
  const char *v0; // eax
  const char *v1; // edi
  unsigned int v2; // kr00_4
  char *v3; // eax

  if ( !entered )
  {
    entered = 1;
    Sys_PumpEvents();
    IN_Frame();
    v0 = Sys_ConsoleInput();
    v1 = v0;
    if ( v0 )
    {
      v2 = strlen(v0);
      v3 = (char *)Mem_Alloc(v2 + 1, 0x13u);
      strcpy(v3, v1);
      Sys_QueEvent(0, SE_CONSOLE, 0, 0, v2 + 1, v3);
    }
    entered = 0;
  }
}

// FUNC: void __cdecl Sys_StartProfiling_f(class idCmdArgs const &)
void __cdecl Sys_StartProfiling_f()
{
  if ( Sys_LoadVTune() )
    VTResume_f();
}

// FUNC: void __cdecl Sys_StopProfiling_f(class idCmdArgs const &)
void __cdecl Sys_StopProfiling_f()
{
  if ( Sys_LoadVTune() )
    VTPause_f();
}

// FUNC: bool __cdecl Sys_AlreadyRunning(void)
bool __cdecl Sys_AlreadyRunning()
{
  bool result; // al

  result = 0;
  if ( !__unnamed::win_allowMultipleInstances.internalVar->integerValue )
  {
    CreateMutexA(0, 0, "QUAKE4");
    if ( GetLastError() == 183 || GetLastError() == 5 )
      return 1;
  }
  return result;
}

// FUNC: char const * __cdecl Sys_GetProcessorString(void)
const char *__cdecl Sys_GetProcessorString()
{
  return __unnamed::sys_cpustring.internalVar->value;
}

// FUNC: void __cdecl Win_Frame(void)
void __cdecl Win_Frame()
{
  idCVar *internalVar; // eax

  if ( cvarSystem->IsInitialized(cvarSystem) )
  {
    internalVar = __unnamed::win_viewlog.internalVar;
    if ( (__unnamed::win_viewlog.internalVar->flags & 0x40000) != 0 )
    {
      if ( !com_skipRenderer.internalVar->integerValue && idAsyncNetwork::serverDedicated.internalVar->integerValue != 1 )
      {
        sys->ShowConsole(sys, __unnamed::win_viewlog.internalVar->integerValue, 0);
        internalVar = __unnamed::win_viewlog.internalVar;
      }
      BYTE2(internalVar->flags) &= ~4u;
    }
    win32.outputDebugString = __unnamed::win_outputDebugString.internalVar->integerValue != 0;
    win32.outputEditString = __unnamed::win_outputEditString.internalVar->integerValue != 0;
    win32.sysErrorNoWait = __unnamed::win_sysErrorNoWait.internalVar->integerValue != 0;
  }
}

// FUNC: __stdcall WinMain(x,x,x,x)
int __userpurge WinMain@<eax>(
        int a1@<edi>,
        int a2@<esi>,
        HINSTANCE__ *hInstance,
        HINSTANCE__ *hPrevInstance,
        char *lpCmdLine,
        int nCmdShow)
{
  HCURSOR CursorA; // eax
  char *v7; // eax
  _RTL_CRITICAL_SECTION *criticalSections; // esi
  HCURSOR hcurSave; // [esp+14h] [ebp-4h]
  HICON__ *hcurSavea; // [esp+14h] [ebp-4h]

  if ( !Memory::sOK )
    Memory::Error("Unprotected allocation in DLL detected prior to initialization of memory system");
  Memory::mAllocator = malloc;
  Memory::mDeallocator = free;
  Memory::mMSize = _msize;
  CursorA = LoadCursorA(0, (LPCSTR)0x7F02);
  hcurSave = SetCursor(CursorA);
  Sys_SetPhysicalWorkMemory(201326592, 0x40000000);
  Sys_GetCurrentMemoryStatus(&exeLaunchMemoryStats);
  win32.hInstance = hInstance;
  CI_InitCrashReporting();
  idStr::Copynz(sys_cmdline, lpCmdLine, 1024);
  if ( sys_cmdline[0] )
  {
    v7 = sys_cmdline;
    do
    {
      if ( *v7 == 92 )
        *v7 = 47;
      ++v7;
    }
    while ( *v7 );
  }
  Sys_CreateConsole();
  SetErrorMode(1u);
  criticalSections = win32.criticalSections;
  do
    InitializeCriticalSection(criticalSections++);
  while ( (int)criticalSections < (int)&win32.backgroundDownloadSemaphore );
  Sys_Milliseconds();
  Sys_FPU_EnableExceptions(0);
  Sys_FPU_SetPrecision(1);
  GSS_GetSecurityCode();
  (*(void (__thiscall **)(netadrtype_t, _DWORD, _DWORD, char *, int, int))(*(_DWORD *)common.type + 4))(
    common.type,
    0,
    0,
    lpCmdLine,
    a1,
    a2);
  if ( __unnamed::win_notaskkeys.internalVar->integerValue )
    DisableTaskKeys(1, 0, 0);
  Sys_StartAsyncThread();
  if ( __unnamed::win_viewlog.internalVar->integerValue
    || com_skipRenderer.internalVar->integerValue
    || idAsyncNetwork::serverDedicated.internalVar->integerValue )
  {
    ((void (__thiscall *)(idSys *, int, int, HCURSOR))sys->ShowConsole)(sys, 1, 1, hcurSave);
  }
  else
  {
    ((void (__thiscall *)(idSys *, _DWORD, _DWORD, HCURSOR))sys->ShowConsole)(sys, 0, 0, hcurSave);
  }
  SetCursor(hcurSavea);
  if ( !strstr(lpCmdLine, "+debugger") )
  {
    ((void (__thiscall *)(idSys *, HWND__ *, HICON__ *))sys->SetFocus)(sys, win32.hWnd, hcurSavea);
    while ( 1 )
    {
      Win_Frame();
      if ( __unnamed::win_enableFPUExceptions.internalVar->integerValue )
        Sys_FPU_EnableExceptions(7);
      else
        Sys_FPU_EnableExceptions(0);
      (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 32))(*(_DWORD *)common.ip);
      sys->UpdateConsole(sys);
      (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 20))(common.type);
    }
  }
  return 0;
}

// FUNC: void __cdecl Sys_Init(void)
void __usercall Sys_Init(int a1@<esi>)
{
  const char *CurrentUser; // eax
  const char *v2; // edx
  const char *v3; // ecx
  int v4; // esi
  double v5; // st7
  int v6; // eax
  char v7; // cl
  char *v8; // edx
  int v9; // eax
  char v10; // cl
  char *v11; // edx
  int v12; // eax
  char v13; // cl
  char *v14; // edx
  int v15; // eax
  char v16; // cl
  char *v17; // edx
  int v18; // eax
  char v19; // cl
  char *v20; // edx
  int v21; // esi
  int v22; // eax
  char v23; // cl
  char *v24; // edx
  int v25; // esi
  int v26; // eax
  char v27; // cl
  char *v28; // edx
  int v29; // esi
  int v30; // eax
  char v31; // cl
  char *v32; // edx
  int v33; // esi
  int v34; // eax
  char v35; // cl
  char *v36; // edx
  int v37; // esi
  int v38; // eax
  char v39; // cl
  char *v40; // edx
  int v41; // esi
  int v42; // eax
  char v43; // cl
  char *v44; // edx
  int v45; // esi
  int v46; // eax
  char v47; // cl
  char *v48; // edx
  int v49; // esi
  int v50; // eax
  char v51; // cl
  char *v52; // edx
  const char *value; // ecx
  int v54; // eax
  cpuid_t v55; // esi
  int v56; // esi
  int SystemRam; // eax
  int v58; // esi
  int VideoRam; // eax
  idCVarSystem_vtbl *v60; // esi
  int v61; // eax
  idCVarSystem_vtbl *v62; // esi
  int v63; // eax
  idCVarSystem_vtbl *v64; // esi
  float v65; // [esp+48h] [ebp-180h]
  const char *v66; // [esp+4Ch] [ebp-17Ch]
  idStr string; // [esp+5Ch] [ebp-16Ch] BYREF
  int cacheTotalSize[4]; // [esp+7Ch] [ebp-14Ch] BYREF
  int physicalNum; // [esp+8Ch] [ebp-13Ch] BYREF
  int logicalNum; // [esp+90h] [ebp-138h] BYREF
  int cacheLineSize[4]; // [esp+94h] [ebp-134h] BYREF
  idToken token; // [esp+A4h] [ebp-124h] BYREF
  idLexer src; // [esp+F4h] [ebp-D4h] BYREF
  int v74; // [esp+1C4h] [ebp-4h]

  CoInitialize(0);
  timeBeginPeriod(1u);
  cmdSystem->AddCommand(
    cmdSystem,
    "in_restart",
    (void (__cdecl *)(const idCmdArgs *))Sys_In_Restart_f,
    2,
    "restarts the input system",
    0);
  cmdSystem->AddCommand(cmdSystem, "help", (void (__cdecl *)(const idCmdArgs *))SpawnStub, 2, "shows help", 0);
  CurrentUser = Sys_GetCurrentUser();
  __unnamed::win_username.internalVar->InternalSetString(__unnamed::win_username.internalVar, CurrentUser);
  win32.osversion.dwOSVersionInfoSize = 148;
  if ( !GetVersionExA(&win32.osversion) )
    Sys_Error(0, a1, "Couldn't get OS info");
  if ( win32.osversion.dwMajorVersion < 4 )
    Sys_Error(0, a1, "Quake4 requires Windows version 4 or greater");
  if ( !win32.osversion.dwPlatformId )
    Sys_Error(0, a1, "Quake4 doesn't run on Win32s");
  if ( win32.osversion.dwPlatformId == 2 )
  {
    if ( win32.osversion.dwMajorVersion <= 4 )
    {
      __unnamed::sys_arch.internalVar->InternalSetString(__unnamed::sys_arch.internalVar, "WinNT (NT)");
      goto LABEL_33;
    }
    if ( win32.osversion.dwMajorVersion == 5 )
    {
      switch ( win32.osversion.dwMinorVersion )
      {
        case 0u:
          v66 = "Win2K (NT)";
LABEL_32:
          __unnamed::sys_arch.internalVar->InternalSetString(__unnamed::sys_arch.internalVar, v66);
          goto LABEL_33;
        case 1u:
          __unnamed::sys_arch.internalVar->InternalSetString(__unnamed::sys_arch.internalVar, "WinXP (NT)");
          goto LABEL_33;
        case 2u:
          v66 = "Server 2003 (NT)";
          goto LABEL_32;
      }
    }
    __unnamed::sys_arch.internalVar->InternalSetString(__unnamed::sys_arch.internalVar, "Unknown NT variant");
    goto LABEL_33;
  }
  if ( win32.osversion.dwPlatformId != 1 )
  {
    v66 = "Unknown Windows variant";
    goto LABEL_32;
  }
  if ( win32.osversion.dwMajorVersion != 4 )
  {
LABEL_30:
    __unnamed::sys_arch.internalVar->InternalSetString(__unnamed::sys_arch.internalVar, "Unknown 95 variant");
    goto LABEL_33;
  }
  if ( !win32.osversion.dwMinorVersion )
  {
    if ( win32.osversion.szCSDVersion[1] == 67 )
      __unnamed::sys_arch.internalVar->InternalSetString(__unnamed::sys_arch.internalVar, "Win95 OSR2 (95)");
    else
      __unnamed::sys_arch.internalVar->InternalSetString(__unnamed::sys_arch.internalVar, "Win95 (95)");
    goto LABEL_33;
  }
  if ( win32.osversion.dwMinorVersion != 10 )
  {
    if ( win32.osversion.dwMinorVersion == 90 )
    {
      v66 = "WinMe (95)";
      goto LABEL_32;
    }
    goto LABEL_30;
  }
  if ( win32.osversion.szCSDVersion[1] == 65 )
    __unnamed::sys_arch.internalVar->InternalSetString(__unnamed::sys_arch.internalVar, "Win98SE (95)");
  else
    __unnamed::sys_arch.internalVar->InternalSetString(__unnamed::sys_arch.internalVar, "Win98 (95)");
LABEL_33:
  if ( idStr::Icmp(__unnamed::sys_cpustring.internalVar->value, "detect") )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "forcing CPU type to ");
    value = __unnamed::sys_cpustring.internalVar->value;
    v54 = 0;
    if ( *value )
    {
      do
        ++v54;
      while ( value[v54] );
    }
    idLexer::idLexer(&src, value, v54, "sys_cpustring", 0);
    token.floatvalue = 0.0;
    v74 = 2;
    token.len = 0;
    token.alloced = 20;
    token.data = token.baseBuffer;
    token.baseBuffer[0] = 0;
    v55 = CPUID_NONE;
    if ( !idLexer::ReadToken(&src, &token) )
      goto LABEL_131;
    do
    {
      if ( idStr::Icmp(token.data, "generic") )
      {
        if ( idStr::Icmp(token.data, "intel") )
        {
          if ( idStr::Icmp(token.data, "amd") )
          {
            if ( idStr::Icmp(token.data, "mmx") )
            {
              if ( idStr::Icmp(token.data, "3dnow") )
              {
                if ( idStr::Icmp(token.data, "sse") )
                {
                  if ( idStr::Icmp(token.data, "sse2") )
                  {
                    if ( idStr::Icmp(token.data, "sse3") )
                    {
                      if ( !idStr::Icmp(token.data, "htt") )
                        v55 |= 0x1000u;
                    }
                    else
                    {
                      v55 |= 0x100u;
                    }
                  }
                  else
                  {
                    v55 |= 0x80u;
                  }
                }
                else
                {
                  v55 |= 0x40u;
                }
              }
              else
              {
                v55 |= 0x20u;
              }
            }
            else
            {
              v55 |= 0x10u;
            }
          }
          else
          {
            v55 |= 8u;
          }
        }
        else
        {
          v55 |= 4u;
        }
      }
      else
      {
        v55 |= 2u;
      }
    }
    while ( idLexer::ReadToken(&src, &token) );
    if ( v55 == CPUID_NONE )
    {
LABEL_131:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "WARNING: unknown sys_cpustring '%s'\n",
        __unnamed::sys_cpustring.internalVar->value);
      v55 = CPUID_GENERIC;
    }
    memset(cacheLineSize, 0, sizeof(cacheLineSize));
    memset(cacheTotalSize, 0, sizeof(cacheTotalSize));
    win32.cpuid = v55;
    LOBYTE(v74) = 1;
    idStr::FreeData(&token);
    v74 = -1;
    idLexer::~idLexer(&src);
  }
  else
  {
    string.len = 0;
    string.alloced = 20;
    string.data = string.baseBuffer;
    string.baseBuffer[0] = 0;
    v74 = 0;
    Sys_CPUCount(&logicalNum, &physicalNum);
    v2 = "s";
    if ( logicalNum <= 1 )
      v2 = &entityFilter;
    v3 = "s";
    if ( physicalNum <= 1 )
      v3 = &entityFilter;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%d physical CPU%s, %d logical CPU%s\n",
      physicalNum,
      v3,
      logicalNum,
      v2);
    v4 = *(_DWORD *)common.type;
    v5 = Sys_ClockTicksPerSecond();
    (*(void (**)(netadrtype_t, const char *, ...))(v4 + 124))(common.type, "%1.0f MHz ", v5 * 0.000001);
    win32.cpuid = Sys_GetCPUId();
    idStr::FreeData(&string);
    string.len = 0;
    string.alloced = 20;
    string.data = string.baseBuffer;
    string.baseBuffer[0] = 0;
    if ( (BYTE2(win32.cpuid) & 2) != 0 )
    {
      v6 = 0;
      v7 = 54;
      do
      {
        v8 = &string.data[v6++];
        v8[string.len] = v7;
        v7 = a64BitAmdCpu[v6];
      }
      while ( v7 );
      string.len = 14;
      string.data[14] = 0;
    }
    else if ( (win32.cpuid & 8) != 0 )
    {
      v9 = 0;
      v10 = 65;
      do
      {
        v11 = &string.data[v9++];
        v11[string.len] = v10;
        v10 = aAmdCpu[v9];
      }
      while ( v10 );
      string.len = 7;
      string.data[7] = 0;
    }
    else if ( (win32.cpuid & 4) != 0 )
    {
      v12 = 0;
      v13 = 73;
      do
      {
        v14 = &string.data[v12++];
        v14[string.len] = v13;
        v13 = aIntelCpu[v12];
      }
      while ( v13 );
      string.len = 9;
      string.data[9] = 0;
    }
    else if ( (win32.cpuid & 1) != 0 )
    {
      v15 = 0;
      v16 = 117;
      do
      {
        v17 = &string.data[v15++];
        v17[string.len] = v16;
        v16 = aUnsupportedCpu[v15];
      }
      while ( v16 );
      string.len = 15;
      string.data[15] = 0;
    }
    else
    {
      v18 = 0;
      v19 = 103;
      do
      {
        v20 = &string.data[v18++];
        v20[string.len] = v19;
        v19 = aGenericCpu[v18];
      }
      while ( v19 );
      string.len = 11;
      string.data[11] = 0;
    }
    v21 = string.len + 6;
    if ( string.len + 7 > string.alloced )
      idStr::ReAllocate(&string, string.len + 7, 1);
    v22 = 0;
    v23 = 32;
    do
    {
      v24 = &string.data[v22++];
      v24[string.len] = v23;
      v23 = aWith[v22];
    }
    while ( v23 );
    string.len = v21;
    string.data[v21] = 0;
    if ( (win32.cpuid & 0x10) != 0 )
    {
      v25 = string.len + 6;
      if ( string.len + 7 > string.alloced )
        idStr::ReAllocate(&string, string.len + 7, 1);
      v26 = 0;
      v27 = 77;
      do
      {
        v28 = &string.data[v26++];
        v28[string.len] = v27;
        v27 = aMmx_0[v26];
      }
      while ( v27 );
      string.len = v25;
      string.data[v25] = 0;
    }
    if ( (win32.cpuid & 0x20) != 0 )
    {
      v29 = string.len + 9;
      if ( string.len + 10 > string.alloced )
        idStr::ReAllocate(&string, string.len + 10, 1);
      v30 = 0;
      v31 = 51;
      do
      {
        v32 = &string.data[v30++];
        v32[string.len] = v31;
        v31 = a3dnow_1[v30];
      }
      while ( v31 );
      string.len = v29;
      string.data[v29] = 0;
    }
    if ( (win32.cpuid & 0x40) != 0 )
    {
      v33 = string.len + 6;
      if ( string.len + 7 > string.alloced )
        idStr::ReAllocate(&string, string.len + 7, 1);
      v34 = 0;
      v35 = 83;
      do
      {
        v36 = &string.data[v34++];
        v36[string.len] = v35;
        v35 = aSse_1[v34];
      }
      while ( v35 );
      string.len = v33;
      string.data[v33] = 0;
    }
    if ( SLOBYTE(win32.cpuid) < 0 )
    {
      v37 = string.len + 7;
      if ( string.len + 8 > string.alloced )
        idStr::ReAllocate(&string, string.len + 8, 1);
      v38 = 0;
      v39 = 83;
      do
      {
        v40 = &string.data[v38++];
        v40[string.len] = v39;
        v39 = aSse2_1[v38];
      }
      while ( v39 );
      string.len = v37;
      string.data[v37] = 0;
    }
    if ( (BYTE1(win32.cpuid) & 1) != 0 )
    {
      v41 = string.len + 7;
      if ( string.len + 8 > string.alloced )
        idStr::ReAllocate(&string, string.len + 8, 1);
      v42 = 0;
      v43 = 83;
      do
      {
        v44 = &string.data[v42++];
        v44[string.len] = v43;
        v43 = aSse3_1[v42];
      }
      while ( v43 );
      string.len = v41;
      string.data[v41] = 0;
    }
    if ( (BYTE1(win32.cpuid) & 0x10) != 0 )
    {
      v45 = string.len + 6;
      if ( string.len + 7 > string.alloced )
        idStr::ReAllocate(&string, string.len + 7, 1);
      v46 = 0;
      v47 = 72;
      do
      {
        v48 = &string.data[v46++];
        v48[string.len] = v47;
        v47 = aHtt_0[v46];
      }
      while ( v47 );
      string.len = v45;
      string.data[v45] = 0;
    }
    if ( (BYTE2(win32.cpuid) & 1) != 0 )
    {
      v49 = string.len + 8;
      if ( string.len + 9 > string.alloced )
        idStr::ReAllocate(&string, string.len + 9, 1);
      v50 = 0;
      v51 = 69;
      do
      {
        v52 = &string.data[v50++];
        v52[string.len] = v51;
        v51 = aEm64t[v50];
      }
      while ( v51 );
      string.len = v49;
      string.data[v49] = 0;
    }
    idStr::StripTrailing(&string, " & ");
    idStr::StripTrailing(&string, " with ");
    __unnamed::sys_cpustring.internalVar->InternalSetString(__unnamed::sys_cpustring.internalVar, string.data);
    if ( (win32.cpuid & 0x10) == 0 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "CPU does not support the Intel Multi Media Extensions (MMX)");
    if ( (win32.cpuid & 0x40) == 0 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "CPU does not support the Intel Streaming SIMD Extensions (SSE)");
    Sys_GetCPUCacheSize(1, &cacheTotalSize[1], &cacheLineSize[1]);
    Sys_GetCPUCacheSize(2, &cacheTotalSize[2], &cacheLineSize[2]);
    Sys_GetCPUCacheSize(3, &cacheTotalSize[3], &cacheLineSize[3]);
    v74 = -1;
    idStr::FreeData(&string);
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%s\n",
    __unnamed::sys_cpustring.internalVar->value);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%d kB 1st level cache, %d kB 2nd level cache, %d kB 3rd level cache\n",
    cacheTotalSize[1],
    cacheTotalSize[2],
    cacheTotalSize[3]);
  v56 = *(_DWORD *)common.type;
  SystemRam = Sys_GetSystemRam();
  (*(void (__stdcall **)(netadrtype_t, const char *, int))(v56 + 124))(common.type, "%d MB System Memory\n", SystemRam);
  v58 = *(_DWORD *)common.type;
  VideoRam = Sys_GetVideoRam();
  (*(void (**)(netadrtype_t, const char *, ...))(v58 + 124))(common.type, "%d MB Video Memory\n", VideoRam);
  v60 = cvarSystem->__vftable;
  v61 = Sys_GetVideoRam();
  v60->SetCVarInteger(cvarSystem, "com_videoRam", v61, 0);
  v62 = cvarSystem->__vftable;
  v63 = Sys_GetSystemRam();
  v62->SetCVarInteger(cvarSystem, "com_systemRam", v63, 0);
  v64 = cvarSystem->__vftable;
  v65 = Sys_ClockTicksPerSecond() * 9.999999717180685e-10;
  ((void (__thiscall *)(idCVarSystem *, const char *, _DWORD, _DWORD))v64->SetCVarFloat)(
    cvarSystem,
    "com_cpuSpeed",
    LODWORD(v65),
    0);
  win32.outputDebugString = __unnamed::win_outputDebugString.internalVar->integerValue != 0;
  win32.outputEditString = __unnamed::win_outputEditString.internalVar->integerValue != 0;
  win32.sysErrorNoWait = __unnamed::win_sysErrorNoWait.internalVar->integerValue != 0;
  cmdSystem->AddCommand(
    cmdSystem,
    "vtuneResume",
    (void (__cdecl *)(const idCmdArgs *))Sys_StartProfiling_f,
    32,
    "unpauses VTune data collection",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "vtunePause",
    (void (__cdecl *)(const idCmdArgs *))Sys_StopProfiling_f,
    32,
    "pauses VTune data collection",
    0);
}

// FUNC: int __cdecl Sys_ListFiles(char const *,char const *,class idList<class idStr> &)
int __cdecl Sys_ListFiles(const char *directory, const char *extension, idList<idStr> *list)
{
  int v3; // esi
  const char *v4; // eax
  char *v5; // eax
  char *v6; // edi
  int v7; // edi
  char *v9; // edi
  unsigned __int8 v10; // al
  int i; // ebp
  int granularity; // edi
  bool v13; // cc
  char *v14; // eax
  idStr *v15; // ebp
  unsigned int v16; // edi
  idStr *v17; // ebp
  int v18; // eax
  int num; // edi
  int size; // eax
  int v21; // ebp
  char *v22; // eax
  char *v23; // edi
  char *v24; // esi
  char *v25; // eax
  idStr *v26; // edi
  int v27; // esi
  unsigned int v28; // edi
  idStr *v29; // ebp
  int len; // edi
  idStr *v31; // ebp
  int v32; // ebx
  char *data; // [esp-8h] [ebp-190h]
  unsigned int v34; // [esp-8h] [ebp-190h]
  unsigned int v35; // [esp-8h] [ebp-190h]
  char *v36; // [esp-8h] [ebp-190h]
  int j; // [esp+Ch] [ebp-17Ch]
  int k; // [esp+Ch] [ebp-17Ch]
  int v39; // [esp+10h] [ebp-178h]
  char *v40; // [esp+10h] [ebp-178h]
  int v41; // [esp+14h] [ebp-174h]
  int v42; // [esp+18h] [ebp-170h]
  int v43; // [esp+18h] [ebp-170h]
  int flag; // [esp+1Ch] [ebp-16Ch]
  int findhandle; // [esp+20h] [ebp-168h]
  idStr name; // [esp+24h] [ebp-164h] BYREF
  idStr search; // [esp+44h] [ebp-144h] BYREF
  _finddata_t findinfo; // [esp+64h] [ebp-124h] BYREF
  int v49; // [esp+184h] [ebp-4h]

  v3 = 0;
  search.len = 0;
  search.alloced = 20;
  search.data = search.baseBuffer;
  search.baseBuffer[0] = 0;
  v49 = 1;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v4 = extension;
  if ( !extension )
  {
    v4 = &entityFilter;
LABEL_3:
    flag = 16;
    goto LABEL_4;
  }
  if ( *extension != 47 || extension[1] )
    goto LABEL_3;
  v4 = &entityFilter;
  flag = 0;
LABEL_4:
  sprintf(&search, "%s\\*%s", directory, v4);
  v5 = (char *)list->list;
  if ( v5 )
  {
    v6 = v5 - 4;
    `eh vector destructor iterator'(
      v5,
      0x20u,
      *((_DWORD *)v5 - 1),
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    if ( Memory::mDeallocator )
      Memory::mDeallocator(v6);
    else
      free(v6);
  }
  data = search.data;
  list->list = 0;
  list->num = 0;
  list->size = 0;
  v7 = _findfirst(data, &findinfo);
  findhandle = v7;
  if ( v7 == -1 )
  {
    LOBYTE(v49) = 0;
    idStr::FreeData(&name);
    v49 = -1;
    idStr::FreeData(&search);
    return -1;
  }
  do
  {
    if ( flag == (findinfo.attrib & 0x10) )
      continue;
    idStr::operator=(&name, findinfo.name);
    v9 = name.data;
    v10 = *name.data;
    for ( i = 0; v10; v9 = &name.data[i] )
    {
      if ( idStr::lowerCaseCharacter[v10] )
        v10 = idStr::lowerCaseCharacter[v10];
      *v9 = v10;
      v10 = name.data[++i];
    }
    idStr::BackSlashesToSlashes(&name);
    if ( !list->list )
    {
      granularity = list->granularity;
      if ( granularity > 0 )
      {
        if ( granularity != list->size )
        {
          v13 = granularity < list->num;
          list->size = granularity;
          if ( v13 )
            list->num = granularity;
          v34 = 32 * granularity + 4;
          if ( Memory::mAllocator )
            v14 = (char *)Memory::mAllocator(v34);
          else
            v14 = (char *)malloc(v34);
          LOBYTE(v49) = 2;
          if ( v14 )
          {
            v15 = (idStr *)(v14 + 4);
            *(_DWORD *)v14 = granularity;
            `eh vector constructor iterator'(
              v14 + 4,
              0x20u,
              granularity,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v15 = 0;
          }
          v13 = list->num <= 0;
          LOBYTE(v49) = 1;
          list->list = v15;
          v39 = 0;
          if ( !v13 )
          {
            for ( j = 0; ; v3 = j )
            {
              v16 = *(_DWORD *)v3;
              v17 = (idStr *)((char *)list->list + v3);
              v18 = *(_DWORD *)v3 + 1;
              v42 = *(_DWORD *)v3;
              if ( v18 > v17->alloced )
                idStr::ReAllocate(v17, v18, 0);
              j += 32;
              qmemcpy(v17->data, *(const void **)(v3 + 4), v16);
              v17->data[v42] = 0;
              v17->len = v42;
              if ( ++v39 >= list->num )
                break;
            }
          }
        }
      }
      else
      {
        list->list = 0;
        list->num = 0;
        list->size = 0;
      }
    }
    num = list->num;
    size = list->size;
    if ( list->num == size )
    {
      if ( !list->granularity )
        list->granularity = 16;
      v21 = size + list->granularity - (size + list->granularity) % list->granularity;
      if ( v21 > 0 )
      {
        if ( v21 != list->size )
        {
          v24 = (char *)list->list;
          v40 = v24;
          list->size = v21;
          if ( v21 < num )
            list->num = v21;
          v35 = 32 * v21 + 4;
          if ( Memory::mAllocator )
            v25 = (char *)Memory::mAllocator(v35);
          else
            v25 = (char *)malloc(v35);
          LOBYTE(v49) = 3;
          if ( v25 )
          {
            v26 = (idStr *)(v25 + 4);
            *(_DWORD *)v25 = v21;
            `eh vector constructor iterator'(
              v25 + 4,
              0x20u,
              v21,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v26 = 0;
          }
          v13 = list->num <= 0;
          LOBYTE(v49) = 1;
          list->list = v26;
          v43 = 0;
          if ( !v13 )
          {
            v27 = 0;
            for ( k = 0; ; v27 = k )
            {
              v28 = *(_DWORD *)&v40[v27];
              v29 = (idStr *)((char *)list->list + v27);
              if ( (signed int)(v28 + 1) > v29->alloced )
                idStr::ReAllocate(v29, v28 + 1, 0);
              k += 32;
              qmemcpy(v29->data, *(const void **)&v40[v27 + 4], v28);
              v29->data[v28] = 0;
              v29->len = v28;
              if ( ++v43 >= list->num )
                break;
            }
            v24 = v40;
          }
          if ( v24 )
          {
            `eh vector destructor iterator'(
              v24,
              0x20u,
              *((_DWORD *)v24 - 1),
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            v36 = v24 - 4;
            if ( Memory::mDeallocator )
              Memory::mDeallocator(v36);
            else
              free(v36);
          }
        }
        goto LABEL_65;
      }
      v22 = (char *)list->list;
      if ( !v22 )
        goto LABEL_44;
      v23 = v22 - 4;
      `eh vector destructor iterator'(
        v22,
        0x20u,
        *((_DWORD *)v22 - 1),
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      if ( !Memory::mDeallocator )
      {
        free(v23);
LABEL_44:
        list->list = 0;
        list->num = 0;
        list->size = 0;
        goto LABEL_65;
      }
      Memory::mDeallocator(v23);
      list->list = 0;
      list->num = 0;
      list->size = 0;
    }
LABEL_65:
    len = name.len;
    v31 = &list->list[list->num];
    v41 = name.len;
    if ( name.len + 1 > v31->alloced )
      idStr::ReAllocate(v31, name.len + 1, 0);
    qmemcpy(v31->data, name.data, len);
    v7 = findhandle;
    v31->data[v41] = 0;
    v31->len = v41;
    ++list->num;
    v3 = 0;
  }
  while ( _findnext(v7, &findinfo) != -1 );
  _findclose(v7);
  v32 = list->num;
  LOBYTE(v49) = 0;
  idStr::FreeData(&name);
  v49 = -1;
  idStr::FreeData(&search);
  return v32;
}
