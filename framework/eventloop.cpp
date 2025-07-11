
// FUNC: public: void __thiscall idEventLoop::Shutdown(void)
void __thiscall idEventLoop::Shutdown(idEventLoop *this)
{
  if ( this->com_journalFile )
  {
    fileSystem->CloseFile(fileSystem, this->com_journalFile);
    this->com_journalFile = 0;
  }
  if ( this->com_journalDataFile )
  {
    fileSystem->CloseFile(fileSystem, this->com_journalDataFile);
    this->com_journalDataFile = 0;
  }
}

// FUNC: public: int __thiscall idEventLoop::Milliseconds(void)
int __thiscall idEventLoop::Milliseconds(idEventLoop *this)
{
  return Sys_Milliseconds() - this->initialTimeOffset;
}

// FUNC: private: struct sysEvent_s __thiscall idEventLoop::GetRealEvent(void)
sysEvent_s *__thiscall idEventLoop::GetRealEvent(idEventLoop *this, sysEvent_s *result)
{
  int evPtrLength; // edx
  void *v4; // eax
  idFile *com_journalFile; // ecx
  int v6; // eax
  sysEvent_s *Event; // eax
  int v8; // eax
  sysEvent_s *v9; // eax
  sysEvent_s ev; // [esp+10h] [ebp-28h] BYREF
  sysEvent_s v11; // [esp+24h] [ebp-14h] BYREF

  if ( idEventLoop::com_journal.internalVar->integerValue == 2 )
  {
    if ( ((int (__stdcall *)(sysEvent_s *, int))this->com_journalFile->Read)(&ev, 20) != 20 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "Error reading from journal file");
    evPtrLength = ev.evPtrLength;
    if ( ev.evPtrLength )
    {
      v4 = Mem_ClearedAlloc(ev.evPtrLength, 0x14u);
      com_journalFile = this->com_journalFile;
      ev.evPtr = v4;
      v6 = com_journalFile->Read(com_journalFile, v4, ev.evPtrLength);
      evPtrLength = ev.evPtrLength;
      if ( v6 != ev.evPtrLength )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
          common.type,
          "Error reading from journal file");
LABEL_13:
        evPtrLength = ev.evPtrLength;
      }
    }
  }
  else
  {
    Event = Sys_GetEvent(&v11);
    ev.evType = Event->evType;
    ev.evValue = Event->evValue;
    ev.evValue2 = Event->evValue2;
    evPtrLength = Event->evPtrLength;
    ev.evPtrLength = evPtrLength;
    ev.evPtr = Event->evPtr;
    if ( idEventLoop::com_journal.internalVar->integerValue == 1 )
    {
      if ( this->com_journalFile->Write(this->com_journalFile, &ev, 20) != 20 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
          common.type,
          "Error writing to journal file");
      evPtrLength = ev.evPtrLength;
      if ( ev.evPtrLength )
      {
        v8 = this->com_journalFile->Write(this->com_journalFile, ev.evPtr, ev.evPtrLength);
        evPtrLength = ev.evPtrLength;
        if ( v8 != ev.evPtrLength )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
            common.type,
            "Error writing to journal file");
          goto LABEL_13;
        }
      }
    }
  }
  v9 = result;
  result->evType = ev.evType;
  result->evValue = ev.evValue;
  result->evValue2 = ev.evValue2;
  result->evPtrLength = evPtrLength;
  result->evPtr = ev.evPtr;
  return v9;
}

// FUNC: public: int __thiscall idEventLoop::RunEventLoop(bool)
int __thiscall idEventLoop::RunEventLoop(idEventLoop *this, bool commandExecution)
{
  int com_pushedEventsTail; // eax
  int v4; // eax
  sysEvent_s *v5; // eax
  sysEventType_t evType; // edi
  int evValue; // esi
  int evValue2; // edx
  int evPtrLength; // ecx
  void *evPtr; // eax
  sysEvent_s result; // [esp+10h] [ebp-3Ch] BYREF
  int v13[4]; // [esp+24h] [ebp-28h] BYREF
  void *ptr; // [esp+34h] [ebp-18h]
  sysEvent_s ev; // [esp+38h] [ebp-14h]

  while ( 1 )
  {
    if ( commandExecution )
      cmdSystem->ExecuteCommandBuffer(cmdSystem);
    com_pushedEventsTail = this->com_pushedEventsTail;
    if ( this->com_pushedEventsHead <= com_pushedEventsTail )
    {
      idEventLoop::GetRealEvent(this, &result);
      evPtr = result.evPtr;
      evPtrLength = result.evPtrLength;
      evValue2 = result.evValue2;
      evValue = result.evValue;
      evType = result.evType;
    }
    else
    {
      v4 = com_pushedEventsTail + 1;
      this->com_pushedEventsTail = v4;
      v5 = &this->com_pushedEvents[((_BYTE)v4 - 1) & 0x3F];
      evType = v5->evType;
      evValue = v5->evValue;
      evValue2 = v5->evValue2;
      evPtrLength = v5->evPtrLength;
      evPtr = v5->evPtr;
      result.evType = evType;
      result.evValue = evValue;
      result.evValue2 = evValue2;
      result.evPtrLength = evPtrLength;
      result.evPtr = evPtr;
    }
    ev.evValue = evValue;
    ev.evValue2 = evValue2;
    ev.evPtrLength = evPtrLength;
    ev.evPtr = evPtr;
    if ( evType == SE_NONE )
      break;
    v13[0] = evType;
    v13[1] = evValue;
    v13[2] = evValue2;
    v13[3] = evPtrLength;
    ptr = evPtr;
    if ( evType == SE_KEY )
    {
      idKeyInput::PreliminaryKeyEvent(evValue, evValue2 != 0);
      evType = v13[0];
    }
    if ( evType == SE_CONSOLE )
    {
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, (const char *)ptr);
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "\n");
    }
    else
    {
      session->ProcessEvent(session, (const sysEvent_s *)v13);
    }
    if ( ptr )
      Mem_Free(ptr);
  }
  return 0;
}

// FUNC: public: void __thiscall idEventLoop::Init(void)
void __thiscall idEventLoop::Init(idEventLoop *this)
{
  int integerValue; // eax
  idFile *v3; // eax

  this->initialTimeOffset = Sys_Milliseconds();
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(common.type, "journal", 0);
  integerValue = idEventLoop::com_journal.internalVar->integerValue;
  if ( integerValue == 1 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Journaling events\n");
    this->com_journalFile = fileSystem->OpenFileWrite(fileSystem, "journal.dat", "fs_savepath", 0);
    v3 = fileSystem->OpenFileWrite(fileSystem, "journaldata.dat", "fs_savepath", 0);
LABEL_5:
    this->com_journalDataFile = v3;
    goto LABEL_6;
  }
  if ( integerValue == 2 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Replaying journaled events\n");
    this->com_journalFile = fileSystem->OpenFileRead(fileSystem, "journal.dat", 1, 0);
    v3 = fileSystem->OpenFileRead(fileSystem, "journaldata.dat", 1, 0);
    goto LABEL_5;
  }
LABEL_6:
  if ( !this->com_journalFile || !this->com_journalDataFile )
  {
    idEventLoop::com_journal.internalVar->InternalSetInteger(idEventLoop::com_journal.internalVar, 0);
    this->com_journalFile = 0;
    this->com_journalDataFile = 0;
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't open journal files\n");
  }
}

// FUNC: public: int __thiscall idEventLoop::JournalLevel(void)const
int __thiscall idEventLoop::JournalLevel(idEventLoop *this)
{
  return idEventLoop::com_journal.internalVar->integerValue;
}
