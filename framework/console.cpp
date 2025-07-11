
// FUNC: void __cdecl SCR_DrawTextRightAlign(float &,char const *,...)
void SCR_DrawTextRightAlign(float *y, const char *text, ...)
{
  int v2; // eax
  char string[1024]; // [esp+10h] [ebp-400h] BYREF
  va_list argptr; // [esp+41Ch] [ebp+Ch] BYREF

  va_start(argptr, text);
  v2 = idStr::vsnPrintf(string, 1024, text, argptr);
  renderSystem->DrawSmallStringExt(
    renderSystem,
    635 - 8 * v2,
    (int)(*y + 2.0),
    string,
    &colorWhite,
    1,
    localConsole.charSetShader);
  *y = *y + 20.0;
}

// FUNC: void __cdecl SCR_DrawTinyTextLeftAlign(float &,char const *,...)
void SCR_DrawTinyTextLeftAlign(float *y, const char *text, ...)
{
  char string[1024]; // [esp+Ch] [ebp-400h] BYREF
  va_list argptr; // [esp+418h] [ebp+Ch] BYREF

  va_start(argptr, text);
  idStr::vsnPrintf(string, 1024, text, argptr);
  renderSystem->DrawTinyStringExt(renderSystem, 0, (int)(*y + 2.0), string, &colorWhite, 1, localConsole.charSetShader);
  *y = *y + 12.0;
}

// FUNC: void __cdecl SCR_DrawTinyTextCenterAlign(float &,char const *,...)
void SCR_DrawTinyTextCenterAlign(float *y, const char *text, ...)
{
  char string[1024]; // [esp+Ch] [ebp-400h] BYREF
  va_list argptr; // [esp+418h] [ebp+Ch] BYREF

  va_start(argptr, text);
  idStr::vsnPrintf(string, 1024, text, argptr);
  renderSystem->DrawTinyStringExt(
    renderSystem,
    320,
    (int)(*y + 2.0),
    string,
    &colorWhite,
    1,
    localConsole.charSetShader);
  *y = *y + 12.0;
}

// FUNC: float __cdecl SCR_DrawMemoryUsage(float)
double __cdecl SCR_DrawMemoryUsage(float y)
{
  memoryStats_t allocs; // [esp+0h] [ebp-20h] BYREF
  memoryStats_t frees; // [esp+10h] [ebp-10h] BYREF

  Mem_GetStats(&allocs);
  SCR_DrawTextRightAlign(&y, "total allocated memory: # %4d, %4d kB    ", allocs.num, allocs.totalSize >> 10);
  Mem_GetFrameStats(&allocs, &frees);
  SCR_DrawTextRightAlign(
    &y,
    "frame alloc: # %4d, %4d kB  frame free: # %4d, %4d kB    ",
    allocs.num,
    allocs.totalSize >> 10,
    frees.num,
    frees.totalSize >> 10);
  Mem_ClearFrameStats();
  return y;
}

// FUNC: public: virtual void __thiscall idConsoleLocal::Shutdown(void)
void __thiscall idConsoleLocal::Shutdown(idConsoleLocal *this)
{
  cmdSystem->RemoveCommand(cmdSystem, "clear");
  cmdSystem->RemoveCommand(cmdSystem, "conDump");
}

// FUNC: public: virtual void __thiscall idConsoleLocal::LoadGraphics(void)
void __thiscall idConsoleLocal::LoadGraphics(idConsoleLocal *this)
{
  this->charSetShader = declManager->FindMaterial(declManager, "gfx/2d/bigchars", 1);
  this->whiteShader = declManager->FindMaterial(declManager, "_white", 1);
  this->consoleShader = declManager->FindMaterial(declManager, "console", 1);
}

// FUNC: public: virtual bool __thiscall idConsoleLocal::Active(void)
bool __thiscall idConsoleLocal::Active(idConsoleLocal *this)
{
  return this->keyCatching;
}

// FUNC: public: virtual void __thiscall idConsoleLocal::ClearNotifyLines(void)
void __thiscall idConsoleLocal::ClearNotifyLines(idConsoleLocal *this)
{
  this->times[0] = 0;
  this->times[1] = 0;
  this->times[2] = 0;
  this->times[3] = 0;
}

// FUNC: public: void __thiscall idConsoleLocal::Dump(char const *)
void __thiscall idConsoleLocal::Dump(idConsoleLocal *this, const char *fileName)
{
  idFile *v3; // ebx
  int current; // edi
  int v5; // esi
  bool v6; // cc
  int v7; // ecx
  unsigned __int8 *v8; // eax
  int i; // eax
  int j; // eax
  char buffer[81]; // [esp+Ch] [ebp-54h] BYREF

  v3 = fileSystem->OpenFileWrite(fileSystem, fileName, "fs_savepath", 0);
  if ( v3 )
  {
    current = this->current;
    v5 = current - 5040;
    if ( current - 5040 < 0 )
      v5 = 0;
    v6 = v5 <= current;
    if ( v5 <= current )
    {
      do
      {
        v7 = 0;
        v8 = (unsigned __int8 *)&this->text[78 * (v5 % 5041) + 2];
        while ( *(v8 - 4) <= 0x20u )
        {
          if ( *(v8 - 2) > 0x20u )
          {
            ++v7;
            break;
          }
          if ( *v8 > 0x20u )
          {
            v7 += 2;
            break;
          }
          if ( v8[2] > 0x20u )
          {
            v7 += 3;
            break;
          }
          if ( v8[4] > 0x20u )
          {
            v7 += 4;
            break;
          }
          if ( v8[6] > 0x20u )
          {
            v7 += 5;
            break;
          }
          v7 += 6;
          v8 += 12;
          if ( v7 >= 78 )
            break;
        }
        if ( v7 != 78 )
          break;
        ++v5;
      }
      while ( v5 <= current );
      v6 = v5 <= current;
    }
    if ( v6 )
    {
      do
      {
        for ( i = 0; i < 78; ++i )
          buffer[i] = this->text[78 * (v5 % 5041) + i];
        for ( j = 77; j >= 0; buffer[j + 1] = 0 )
        {
          if ( buffer[j] > 32 )
            break;
          --j;
        }
        buffer[j + 1] = 13;
        buffer[j + 2] = 10;
        buffer[j + 3] = 0;
        v3->Write(v3, buffer, strlen(buffer));
        ++v5;
      }
      while ( v5 <= this->current );
    }
    fileSystem->CloseFile(fileSystem, v3);
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "couldn't open %s",
      fileName);
  }
}

// FUNC: private: void __thiscall idConsoleLocal::PageUp(void)
void __thiscall idConsoleLocal::PageUp(idConsoleLocal *this)
{
  this->display -= 2;
  if ( this->current - this->display >= 5041 )
    this->display = this->current - 5040;
}

// FUNC: private: void __thiscall idConsoleLocal::PageDown(void)
void __thiscall idConsoleLocal::PageDown(idConsoleLocal *this)
{
  int current; // eax

  this->display += 2;
  current = this->current;
  if ( this->display > current )
    this->display = current;
}

// FUNC: private: void __thiscall idConsoleLocal::Scroll(void)
void __thiscall idConsoleLocal::Scroll(idConsoleLocal *this)
{
  if ( this->lastKeyEvent != -1 && this->lastKeyEvent + 200 <= idEventLoop::Milliseconds(eventLoop) )
  {
    if ( idKeyInput::IsDown(146) )
    {
      idConsoleLocal::PageUp(this);
      this->nextKeyEvent = 100;
    }
    else if ( idKeyInput::IsDown(145) )
    {
      idConsoleLocal::PageDown(this);
      this->nextKeyEvent = 100;
    }
  }
}

// FUNC: private: void __thiscall idConsoleLocal::DrawInput(void)
void __thiscall idConsoleLocal::DrawInput(idConsoleLocal *this)
{
  idEditField *p_consoleField; // edi
  int v3; // ebp
  unsigned int v4; // kr00_4
  int v5; // esi
  idRenderSystem_vtbl *v6; // esi
  idVec4 *v7; // eax
  float v8; // [esp+10h] [ebp-3Ch]
  float v9; // [esp+14h] [ebp-38h]
  float v10; // [esp+18h] [ebp-34h]
  const idMaterial *whiteShader; // [esp+30h] [ebp-1Ch]
  idRenderSystem_vtbl *v12; // [esp+44h] [ebp-8h]

  p_consoleField = &this->consoleField;
  v3 = (int)((double)this->vislines - 36.0);
  if ( idSoundSystemLocal::GetActiveSoundWorld(&this->consoleField) )
  {
    v4 = strlen(idEditField::GetBuffer(p_consoleField));
    v5 = v4 - idSoundSystemLocal::GetActiveSoundWorld(p_consoleField);
    if ( v5 > 0 )
    {
      ((void (__thiscall *)(idRenderSystem *, int, int, int, int))renderSystem->SetColor4)(
        renderSystem,
        1061997773,
        1045220557,
        1045220557,
        1055286886);
      whiteShader = this->whiteShader;
      v10 = (float)(8 * v5);
      v12 = renderSystem->__vftable;
      v9 = (float)(v3 + 2);
      v8 = (float)(8 * idSoundSystemLocal::GetActiveSoundWorld(p_consoleField) + 16);
      (*((void (__thiscall **)(idRenderSystem *, _DWORD, _DWORD, _DWORD, int, _DWORD, _DWORD, _DWORD, _DWORD, const idMaterial *))&v12->SetColor4
       + 1))(
        renderSystem,
        LODWORD(v8),
        LODWORD(v9),
        LODWORD(v10),
        1096810496,
        0,
        0,
        0,
        0,
        whiteShader);
    }
  }
  v6 = renderSystem->__vftable;
  v7 = idStr::ColorForIndex(58);
  v6->SetColor(renderSystem, v7);
  renderSystem->DrawSmallChar(renderSystem, 8, v3, 93, localConsole.charSetShader);
  idEditField::Draw(p_consoleField, 16, v3, 616, 1, this->charSetShader);
}

// FUNC: public: virtual void __thiscall idConsoleLocal::SetProcFileOutOfDate(bool)
void __thiscall idConsoleLocal::SetProcFileOutOfDate(idConsoleLocal *this, bool state)
{
  this->procFileOutOfDate = state;
}

// FUNC: public: virtual void __thiscall idConsoleLocal::SetAASFileOutOfDate(bool)
void __thiscall idConsoleLocal::SetAASFileOutOfDate(idConsoleLocal *this, bool state)
{
  this->aasFileOutOfDate = state;
}

// FUNC: public: virtual void __thiscall idConsoleLocal::SetConsoleInput(char const *)
void __thiscall idConsoleLocal::SetConsoleInput(idConsoleLocal *this, const char *input)
{
  idEditField::SetBuffer(&this->consoleField, input);
}

// FUNC: public: virtual char const * __thiscall idConsoleLocal::GetConsoleInput(void)
char *__thiscall idConsoleLocal::GetConsoleInput(idConsoleLocal *this)
{
  return idEditField::GetBuffer(&this->consoleField);
}

// FUNC: public: virtual void __thiscall idConsoleLocal::TabComplete(void)
void __thiscall idConsoleLocal::TabComplete(idConsoleLocal *this)
{
  idEditField::AutoComplete(&this->consoleField);
}

// FUNC: float __cdecl SCR_DrawFPS(float)
double __cdecl SCR_DrawFPS(float y)
{
  int v1; // eax
  int v2; // esi
  double v3; // st7
  double v4; // st7
  int v5; // eax
  int v6; // ecx
  const char *v7; // eax
  int fps; // [esp+10h] [ebp-14h]
  float fpsa; // [esp+10h] [ebp-14h]
  idVec4 color; // [esp+14h] [ebp-10h] BYREF

  v1 = Sys_Milliseconds();
  v2 = v1 - previous;
  previous = v1;
  if ( com_showFPS.internalVar->integerValue == 2 )
  {
    if ( v2 >= 16 )
    {
      fps = 1000;
      if ( v2 <= 1000 )
        fps = v2;
    }
    else
    {
      fps = 16;
    }
    v3 = 1000.0 / (double)fps;
    fpsa = v3;
    if ( v3 <= 15.0 )
    {
      ((void (__thiscall *)(idRenderSystem *, _DWORD, _DWORD, int, idVec4 *))renderSystem->DebugGraph)(
        renderSystem,
        LODWORD(fpsa),
        0,
        1115291648,
        &colorPurple);
    }
    else
    {
      v4 = (fpsa - 15.0) * 0.021052632;
      if ( v4 >= 0.0 )
      {
        if ( v4 > 1.0 )
          v4 = 1.0;
      }
      else
      {
        v4 = 0.0;
      }
      color.z = 0.0;
      color.w = 1.0;
      color.x = 1.0 - v4;
      color.y = v4;
      ((void (__thiscall *)(idRenderSystem *, _DWORD, _DWORD, int, idVec4 *))renderSystem->DebugGraph)(
        renderSystem,
        LODWORD(fpsa),
        0,
        1115291648,
        &color);
    }
  }
  v5 = index + 1;
  previousTimes[index % 4] = v2;
  index = v5;
  if ( v5 > 4 )
  {
    v6 = dword_10417CB4 + dword_10417CB0 + previousTimes[0] + dword_10417CAC;
    if ( !v6 )
      v6 = 1;
    v7 = va("%ifps", (40000 / v6 + 5) / 10);
    renderSystem->DrawBigStringExt(
      renderSystem,
      635 - 16 * strlen(v7),
      (int)y + 2,
      v7,
      &colorWhite,
      1,
      localConsole.charSetShader);
  }
  return y + 20.0;
}

// FUNC: float __cdecl SCR_DrawAsyncStats(float)
double __cdecl SCR_DrawAsyncStats(float y)
{
  int OutgoingRate; // eax
  int IncomingRate; // eax
  int i; // esi
  int ClientOutgoingRate; // edi
  int ClientIncomingRate; // ebx
  int v7; // esi
  int v8; // edi
  int Prediction; // [esp+10h] [ebp-4Ch]
  float incomingCompression; // [esp+24h] [ebp-38h]
  float incomingCompressiona; // [esp+24h] [ebp-38h]
  float outgoingCompression; // [esp+28h] [ebp-34h]
  float outgoingCompressiona; // [esp+28h] [ebp-34h]
  int outgoingCompressionb; // [esp+28h] [ebp-34h]
  idStr msg; // [esp+2Ch] [ebp-30h] BYREF
  int v16; // [esp+58h] [ebp-4h]

  if ( idAsyncNetwork::server.active )
  {
    SCR_DrawTextRightAlign(&y, "server delay = %d msec", idAsyncNetwork::server.gameTimeResidual);
    OutgoingRate = idAsyncServer::GetOutgoingRate(&idAsyncNetwork::server);
    SCR_DrawTextRightAlign(&y, "total outgoing rate = %d KB/s", OutgoingRate >> 10);
    IncomingRate = idAsyncServer::GetIncomingRate(&idAsyncNetwork::server);
    SCR_DrawTextRightAlign(&y, "total incoming rate = %d KB/s", IncomingRate >> 10);
    for ( i = 0; i < 32; ++i )
    {
      ClientOutgoingRate = idAsyncServer::GetClientOutgoingRate(&idAsyncNetwork::server, i);
      ClientIncomingRate = idAsyncServer::GetClientIncomingRate(&idAsyncNetwork::server, i);
      outgoingCompression = idAsyncServer::GetClientOutgoingCompression(&idAsyncNetwork::server, i);
      incomingCompression = idAsyncServer::GetClientIncomingCompression(&idAsyncNetwork::server, i);
      if ( ClientOutgoingRate != -1 && ClientIncomingRate != -1 )
        SCR_DrawTextRightAlign(
          &y,
          "client %d: out rate = %d B/s (% -2.1f%%), in rate = %d B/s (% -2.1f%%)",
          i,
          ClientOutgoingRate,
          outgoingCompression,
          ClientIncomingRate,
          incomingCompression);
    }
    msg.len = 0;
    msg.alloced = 20;
    msg.data = msg.baseBuffer;
    msg.baseBuffer[0] = 0;
    v16 = 0;
    idAsyncServer::GetAsyncStatsAvgMsg(&idAsyncNetwork::server, &msg);
    SCR_DrawTextRightAlign(&y, msg.data);
    v16 = -1;
    idStr::FreeData(&msg);
    return y;
  }
  else
  {
    if ( idAsyncNetwork::client.active )
    {
      v7 = idAsyncClient::GetOutgoingRate(&idAsyncNetwork::client);
      v8 = idAsyncClient::GetIncomingRate(&idAsyncNetwork::client);
      outgoingCompressiona = idAsyncClient::GetOutgoingCompression(&idAsyncNetwork::client);
      incomingCompressiona = idAsyncClient::GetIncomingCompression(&idAsyncNetwork::client);
      if ( v7 != -1 && v8 != -1 )
        SCR_DrawTextRightAlign(
          &y,
          "out rate = %d B/s (% -2.1f%%), in rate = %d B/s (% -2.1f%%)",
          v7,
          outgoingCompressiona,
          v8,
          incomingCompressiona);
      Prediction = idAsyncClient::GetPrediction(&idAsyncNetwork::client);
      outgoingCompressionb = (int)idAsyncClient::GetIncomingPacketLoss(&idAsyncNetwork::client);
      SCR_DrawTextRightAlign(&y, "packet loss = %d%%, client prediction = %d", outgoingCompressionb, Prediction);
      SCR_DrawTextRightAlign(&y, "predicted frames: %d", idAsyncNetwork::client.lastFrameDelta);
    }
    return y;
  }
}

// FUNC: Con_Dump_f
void __cdecl Con_Dump_f(const idCmdArgs *args)
{
  const char *v1; // esi
  unsigned int v2; // eax
  int v3; // edi
  int v4; // eax
  char *data; // edx
  const char *v6; // ecx
  char v7; // al
  idStr fileName; // [esp+0h] [ebp-2Ch] BYREF
  int v9; // [esp+28h] [ebp-4h]

  if ( args->argc == 2 )
  {
    v1 = args->argv[1];
    fileName.len = 0;
    fileName.alloced = 20;
    fileName.data = fileName.baseBuffer;
    fileName.baseBuffer[0] = 0;
    if ( v1 )
    {
      v2 = (unsigned int)&v1[strlen(v1) + 1];
      v3 = v2 - (_DWORD)(v1 + 1);
      v4 = v2 - (_DWORD)v1;
      if ( v4 > 20 )
        idStr::ReAllocate(&fileName, v4, 1);
      data = fileName.data;
      v6 = v1;
      do
      {
        v7 = *v6;
        *data++ = *v6++;
      }
      while ( v7 );
      fileName.len = v3;
    }
    v9 = 0;
    idStr::DefaultFileExtension(&fileName, ".txt");
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Dumped console text to %s.\n",
      fileName.data);
    idConsoleLocal::Dump(&localConsole, fileName.data);
    v9 = -1;
    idStr::FreeData(&fileName);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: conDump <filename>\n");
  }
}

// FUNC: public: virtual void __thiscall idConsoleLocal::Close(void)
void __thiscall idConsoleLocal::Close(idConsoleLocal *this)
{
  int v1; // edx
  idConsoleLocal_vtbl *v2; // eax

  this->keyCatching = 0;
  this->finalFrac = 0.0;
  v1 = com_frameTime;
  this->displayFrac = 0.0;
  v2 = this->__vftable;
  this->fracTime = v1;
  ((void (*)(void))v2->ClearNotifyLines)();
}

// FUNC: private: void __thiscall idConsoleLocal::KeyDownEvent(int)
void __thiscall idConsoleLocal::KeyDownEvent(idConsoleLocal *this, int key)
{
  int v3; // eax
  int v4; // eax
  int historyLine; // eax
  int v6; // esi
  idEditField *p_consoleField; // ebp
  char *Buffer; // eax
  idCmdSystem_vtbl *v9; // esi
  char *v10; // eax

  if ( key >= 149 && key <= 160 )
  {
    idKeyInput::ExecKeyBinding(key);
    return;
  }
  switch ( key )
  {
    case 108:
      if ( idKeyInput::IsDown(141) || idKeyInput::IsDown(2) )
      {
        memset32(this->text, 169871904, 0x30000u);
        this->display = this->current;
        return;
      }
      break;
    case 13:
    case 174:
      v6 = *(_DWORD *)common.type;
      p_consoleField = &this->consoleField;
      Buffer = idEditField::GetBuffer(&this->consoleField);
      (*(void (**)(netadrtype_t, const char *, ...))(v6 + 124))(common.type, "]%s\n", Buffer);
      v9 = cmdSystem->__vftable;
      v10 = idEditField::GetBuffer(&this->consoleField);
      v9->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, v10);
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "\n");
      qmemcpy(
        &this->historyEditLines[this->nextHistoryLine++ % 64],
        p_consoleField,
        sizeof(this->historyEditLines[this->nextHistoryLine++ % 64]));
      this->historyLine = this->nextHistoryLine;
      idEditField::Clear(&this->consoleField);
      idEditField::SetWidthInChars(&this->consoleField, 78);
      session->UpdateScreen(session, 1);
      return;
    case 9:
      idEditField::AutoComplete(&this->consoleField);
      return;
    case 133:
      goto LABEL_42;
  }
  if ( tolower(key) == 112 && (idKeyInput::IsDown(141) || idKeyInput::IsDown(2)) )
  {
LABEL_42:
    historyLine = this->historyLine;
    if ( this->nextHistoryLine - historyLine < 64 && historyLine > 0 )
      this->historyLine = historyLine - 1;
    v4 = this->historyLine;
    goto LABEL_41;
  }
  if ( key == 134 || tolower(key) == 110 && (idKeyInput::IsDown(141) || idKeyInput::IsDown(2)) )
  {
    v3 = this->historyLine;
    if ( v3 == this->nextHistoryLine )
      return;
    v4 = v3 + 1;
    this->historyLine = v4;
LABEL_41:
    qmemcpy(&this->consoleField, &this->historyEditLines[v4 % 64], sizeof(this->consoleField));
    return;
  }
  switch ( key )
  {
    case 146:
      idConsoleLocal::PageUp(this);
LABEL_23:
      this->lastKeyEvent = idEventLoop::Milliseconds(eventLoop);
      this->nextKeyEvent = 200;
      return;
    case 145:
      idConsoleLocal::PageDown(this);
      goto LABEL_23;
    case 196:
      idConsoleLocal::PageUp(this);
      return;
    case 195:
      idConsoleLocal::PageDown(this);
      return;
    case 147:
      if ( idKeyInput::IsDown(141) || idKeyInput::IsDown(2) )
      {
        this->display = 0;
        return;
      }
      break;
    default:
      if ( key == 148 && (idKeyInput::IsDown(141) || idKeyInput::IsDown(2)) )
      {
        this->display = this->current;
        return;
      }
      break;
  }
  idEditField::KeyDownEvent(&this->consoleField, key);
}

// FUNC: private: void __thiscall idConsoleLocal::UpdateDisplayFraction(void)
void __thiscall idConsoleLocal::UpdateDisplayFraction(idConsoleLocal *this)
{
  int v1; // eax
  double v2; // st7
  double v3; // st7

  if ( idConsoleLocal::con_speed.internalVar->floatValue <= 0.1 )
  {
    v1 = com_frameTime;
    this->displayFrac = this->finalFrac;
    this->fracTime = v1;
    return;
  }
  if ( this->finalFrac >= (double)this->displayFrac )
  {
    if ( this->finalFrac <= (double)this->displayFrac )
      return;
    v3 = (double)(int)(com_frameTime - this->fracTime) * idConsoleLocal::con_speed.internalVar->floatValue * 0.001
       + this->displayFrac;
    this->displayFrac = v3;
    if ( v3 > this->finalFrac )
      goto LABEL_8;
  }
  else
  {
    v2 = this->displayFrac
       - (double)(int)(com_frameTime - this->fracTime) * idConsoleLocal::con_speed.internalVar->floatValue * 0.001;
    this->displayFrac = v2;
    if ( v2 < this->finalFrac )
LABEL_8:
      this->displayFrac = this->finalFrac;
  }
  this->fracTime = com_frameTime;
}

// FUNC: public: virtual bool __thiscall idConsoleLocal::ProcessEvent(struct sysEvent_s const *,bool)
char __thiscall idConsoleLocal::ProcessEvent(idConsoleLocal *this, const sysEvent_s *event, bool forceAccept)
{
  sysEventType_t evType; // ecx
  bool v5; // dl
  int evValue; // eax

  evType = event->evType;
  v5 = event->evType == SE_KEY && event->evValue == 1;
  if ( !forceAccept )
  {
    if ( v5 )
    {
      if ( event->evValue2 )
      {
        idEditField::ClearAutoComplete(&this->consoleField);
        if ( this->keyCatching )
        {
          this->Close(this);
          sys->GrabMouseCursor(sys, 1);
          cvarSystem->SetCVarBool(cvarSystem, "ui_chat", 0, 0);
        }
        else
        {
          idEditField::Clear(&this->consoleField);
          this->keyCatching = 1;
          if ( idKeyInput::IsDown(142) || idKeyInput::IsDown(3) )
          {
            this->finalFrac = 0.2;
            this->fracTime = com_frameTime;
          }
          else
          {
            this->finalFrac = 0.5;
            this->fracTime = com_frameTime;
          }
          cvarSystem->SetCVarBool(cvarSystem, "ui_chat", 1, 0);
        }
        return 1;
      }
      return 1;
    }
    if ( !this->keyCatching )
      return 0;
  }
  if ( evType != SE_CHAR )
  {
    if ( evType == SE_KEY )
    {
      if ( event->evValue2 )
        idConsoleLocal::KeyDownEvent(this, event->evValue);
      return 1;
    }
    return 0;
  }
  evValue = event->evValue;
  if ( evValue != 1 )
    idEditField::CharEvent(&this->consoleField, evValue);
  return 1;
}

// FUNC: private: void __thiscall idConsoleLocal::Linefeed(void)
void __thiscall idConsoleLocal::Linefeed(idConsoleLocal *this)
{
  int v1; // esi
  int display; // edx
  int current; // eax
  int v4; // edx

  v1 = 0;
  if ( this->current >= 0 )
    this->times[this->current & 3] = com_frameTime;
  display = this->display;
  current = this->current;
  this->x = 0;
  if ( display == current )
    this->display = display + 1;
  this->current = current + 1;
  do
  {
    v4 = v1 + 78 * (this->current % 5041);
    ++v1;
    this->text[v4] = 2592;
  }
  while ( v1 < 78 );
}

// FUNC: public: virtual void __thiscall idConsoleLocal::Print(char const *)
void __thiscall idConsoleLocal::Print(idConsoleLocal *this, const char *txt)
{
  const char *v2; // edi
  int v4; // ebp
  int IsEscape; // eax
  char v6; // cl
  int v7; // ebx
  int x; // ecx
  int v9; // eax
  __int16 v10; // cx
  __int16 v11; // ax
  __int16 v12; // bp
  char color; // [esp+Ch] [ebp-8h]
  int type; // [esp+10h] [ebp-4h] BYREF

  v2 = txt;
  (*(void (__thiscall **)(_DWORD, const char *))(**(_DWORD **)common.ip + 40))(*(_DWORD *)common.ip, txt);
  v4 = *(unsigned __int8 *)txt;
  color = 10;
  if ( *txt )
  {
    do
    {
      IsEscape = idStr::IsEscape(v2, &type);
      if ( IsEscape )
      {
        if ( (type & 4) == 0 )
          goto LABEL_7;
        v6 = v2[1];
        if ( v6 != 48 )
        {
          color = v6 & 0xF;
LABEL_7:
          v2 += IsEscape;
          goto LABEL_39;
        }
        color = 10;
        v2 += IsEscape;
      }
      else
      {
        v7 = this->current % 5041;
        if ( v4 > 32 )
        {
          x = this->x;
          if ( !x || *((__int16 *)&this->keyCatching + 78 * v7 + x) <= 32 )
          {
            v9 = 0;
            while ( v2[v9] > 32 )
            {
              if ( v2[v9 + 1] <= 32 )
              {
                ++v9;
                break;
              }
              if ( v2[v9 + 2] <= 32 )
              {
                v9 += 2;
                break;
              }
              if ( v2[v9 + 3] <= 32 )
              {
                v9 += 3;
                break;
              }
              if ( v2[v9 + 4] <= 32 )
              {
                v9 += 4;
                break;
              }
              if ( v2[v9 + 5] <= 32 )
              {
                v9 += 5;
                break;
              }
              v9 += 6;
              if ( v9 >= 78 )
                break;
            }
            if ( v9 != 78 && v9 + x >= 78 )
              idConsoleLocal::Linefeed(this);
          }
        }
        ++v2;
        switch ( v4 )
        {
          case 9:
            LOBYTE(v11) = 0;
            HIBYTE(v11) = color;
            v12 = v11 | 0x20;
            do
            {
              this->text[78 * v7 + this->x++] = v12;
              if ( this->x >= 78 )
              {
                idConsoleLocal::Linefeed(this);
                this->x = 0;
              }
            }
            while ( (this->x & 3) != 0 );
            goto LABEL_39;
          case 10:
            idConsoleLocal::Linefeed(this);
            goto LABEL_39;
          case 13:
            goto LABEL_33;
        }
        LOBYTE(v10) = 0;
        HIBYTE(v10) = color;
        this->text[78 * v7 + this->x] = v4 | v10;
        if ( ++this->x >= 78 )
        {
          idConsoleLocal::Linefeed(this);
LABEL_33:
          this->x = 0;
        }
      }
LABEL_39:
      v4 = *(unsigned __int8 *)v2;
    }
    while ( *v2 );
  }
  if ( this->current >= 0 )
    this->times[this->current & 3] = com_frameTime;
}

// FUNC: private: void __thiscall idConsoleLocal::DrawNotify(void)
void __usercall idConsoleLocal::DrawNotify(idConsoleLocal *this@<ecx>, int a2@<esi>)
{
  idRenderSystem_vtbl *v3; // esi
  idVec4 *v4; // eax
  int current; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // esi
  int v9; // eax
  __int16 *v10; // edi
  int v11; // eax
  idRenderSystem_vtbl *v12; // ebp
  idVec4 *v13; // eax
  idRenderSystem_vtbl *v14; // esi
  idVec4 *v15; // eax
  int currentColor; // [esp+1Ch] [ebp-Ch]
  int v18; // [esp+20h] [ebp-8h]
  idConsoleLocal *retaddr; // [esp+28h] [ebp+0h]

  if ( !idConsoleLocal::con_noPrint.internalVar->integerValue )
  {
    v3 = renderSystem->__vftable;
    v4 = idStr::ColorForIndex(7);
    ((void (__thiscall *)(idRenderSystem *, idVec4 *, int))v3->SetColor)(renderSystem, v4, a2);
    current = this->current;
    v6 = current - 3;
    currentColor = 0;
    if ( current - 3 <= current )
    {
      do
      {
        if ( v6 >= 0 )
        {
          v7 = this->times[v6 & 3];
          if ( v7 )
          {
            if ( idConsoleLocal::con_notifyTime.internalVar->floatValue * 1000.0 >= (double)(int)(com_frameTime - v7) )
            {
              v8 = 8;
              v9 = 39 * (v6 % 5041);
              v10 = &this->text[78 * (v6 % 5041)];
              do
              {
                if ( (unsigned __int8)*v10 != 32 )
                {
                  LOWORD(v9) = *v10;
                  v11 = (v9 >> 8) & 0xF;
                  if ( v11 != v18 )
                  {
                    v12 = renderSystem->__vftable;
                    v18 = v11;
                    v13 = idStr::ColorForIndex(v11);
                    v12->SetColor(renderSystem, v13);
                    this = retaddr;
                  }
                  v9 = ((int (__stdcall *)(int, int, _DWORD, const idMaterial *))renderSystem->DrawSmallChar)(
                         v8,
                         currentColor,
                         *(unsigned __int8 *)v10,
                         localConsole.charSetShader);
                }
                v8 += 8;
                ++v10;
              }
              while ( v8 < 632 );
              currentColor += 16;
            }
          }
        }
        ++v6;
      }
      while ( v6 <= this->current );
    }
    v14 = renderSystem->__vftable;
    v15 = idStr::ColorForIndex(58);
    v14->SetColor(renderSystem, v15);
  }
}

// FUNC: private: void __thiscall idConsoleLocal::DrawSolidConsole(float)
void __userpurge idConsoleLocal::DrawSolidConsole(idConsoleLocal *this@<ecx>, int a2@<ebx>, int a3@<esi>, float frac)
{
  idConsoleLocal *v4; // ebp
  int v5; // edi
  double v6; // st7
  idRenderSystem_vtbl *v7; // esi
  idVec4 *v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // esi
  int v12; // ebp
  int v13; // edi
  int display; // ecx
  int v15; // ebx
  idRenderSystem_vtbl *v16; // esi
  idVec4 *v17; // eax
  int v18; // edi
  int v19; // ebx
  idRenderSystem_vtbl *v20; // esi
  idVec4 *v21; // eax
  int v22; // esi
  int v23; // eax
  __int16 *v24; // edi
  int v25; // eax
  idRenderSystem_vtbl *v26; // ebx
  idVec4 *v27; // eax
  bool v28; // cc
  idRenderSystem_vtbl *v29; // esi
  idVec4 *v30; // eax
  float v31; // [esp+78h] [ebp-140h]
  float y; // [esp+90h] [ebp-128h]
  int lines; // [esp+94h] [ebp-124h]
  float v36; // [esp+98h] [ebp-120h]
  int rows; // [esp+9Ch] [ebp-11Ch]
  int currentColor; // [esp+A0h] [ebp-118h]
  int i; // [esp+A4h] [ebp-114h]
  idVec4 color; // [esp+A8h] [ebp-110h] BYREF
  char version[256]; // [esp+B8h] [ebp-100h] BYREF

  v4 = this;
  *(float *)&rows = frac * 480.0;
  v5 = (int)*(float *)&rows;
  lines = v5;
  if ( v5 > 0 )
  {
    if ( v5 > 480 )
    {
      lines = 480;
      v5 = 480;
    }
    v6 = *(float *)&rows - 2.0;
    if ( v6 >= 1.0 )
    {
      v31 = 1.0 - this->displayFrac;
      y = v6;
      (*((void (__stdcall **)(_DWORD, _DWORD, int, _DWORD, _DWORD, _DWORD, int, int, const idMaterial *))&renderSystem->SetColor4
       + 1))(
        0,
        0,
        1142947840,
        LODWORD(y),
        0,
        LODWORD(v31),
        1065353216,
        1065353216,
        this->consoleShader);
    }
    v7 = renderSystem->__vftable;
    v8 = idStr::ColorForIndex(58);
    ((void (__thiscall *)(idRenderSystem *, idVec4 *, int, int))v7->SetColor)(renderSystem, v8, a3, a2);
    (*((void (__thiscall **)(idRenderSystem *, _DWORD, idConsoleLocal *, int, int, _DWORD, _DWORD, _DWORD, _DWORD, const idMaterial *))&renderSystem->SetColor4
     + 1))(
      renderSystem,
      0,
      this,
      1142947840,
      0x40000000,
      0,
      0,
      0,
      0,
      v4->whiteShader);
    renderSystem->SetColor(renderSystem, &colorWhite);
    color.z = colorWhite.x;
    color.w = colorWhite.y;
    *(float *)version = colorWhite.z;
    *(_DWORD *)&version[4] = 1056964608;
    renderSystem->SetColor(renderSystem, (idVec4 *)&color.z);
    v9 = sprintf(
           &version[8],
           "%s %s %s V%s Build %u",
           GSSSecurityTag100.mSecurityID,
           "Quake4",
           "Release",
           "",
           0);
    v10 = v9;
    v11 = 0;
    if ( v9 > 0 )
    {
      v12 = v5 - 20;
      v13 = 8 * (80 - v9);
      do
      {
        ((void (__stdcall *)(int, int, _DWORD, const idMaterial *))renderSystem->DrawSmallChar)(
          v13,
          v12,
          version[v11++ + 8],
          localConsole.charSetShader);
        v13 += 8;
      }
      while ( v11 < v10 );
      *(float *)&v5 = frac * 480.0;
      v4 = (idConsoleLocal *)(int)*(float *)&rows;
    }
    display = v4->display;
    v4->vislines = v5;
    currentColor = v5 - 48;
    v15 = (v5 - 8) / 8;
    v36 = (float)(v5 - 48);
    i = v15;
    if ( display != v4->current )
    {
      v16 = renderSystem->__vftable;
      v17 = idStr::ColorForIndex(58);
      v16->SetColor(renderSystem, v17);
      v18 = 8;
      v11 = 80;
      do
      {
        currentColor = (int)v36;
        renderSystem->DrawSmallChar(renderSystem, v18, currentColor, 94, localConsole.charSetShader);
        v18 += 32;
      }
      while ( v18 < 632 );
      i = v15 - 1;
      v36 = v36 - 16.0;
    }
    v19 = v4->display;
    if ( !v11 )
      --v19;
    v20 = renderSystem->__vftable;
    v21 = idStr::ColorForIndex(7);
    v20->SetColor(renderSystem, v21);
    color.x = 0.0;
    if ( currentColor > 0 )
    {
      do
      {
        if ( v19 < 0 )
          break;
        if ( v4->current - v19 < 5041 )
        {
          v22 = 8;
          v23 = 39 * (v19 % 5041);
          v24 = &v4->text[78 * (v19 % 5041)];
          do
          {
            if ( (unsigned __int8)*v24 != 32 )
            {
              LOWORD(v23) = *v24;
              v25 = (v23 >> 8) & 0xF;
              if ( v25 != i )
              {
                v26 = renderSystem->__vftable;
                i = v25;
                v27 = idStr::ColorForIndex(v25);
                v26->SetColor(renderSystem, v27);
                v19 = LODWORD(v36);
              }
              v23 = ((int (__stdcall *)(int, int, _DWORD, const idMaterial *))renderSystem->DrawSmallChar)(
                      v22,
                      (int)*(float *)&lines,
                      *(unsigned __int8 *)v24,
                      localConsole.charSetShader);
            }
            v22 += 8;
            ++v24;
          }
          while ( v22 < 632 );
        }
        --v19;
        v28 = LODWORD(color.x) + 1 < currentColor;
        *(float *)&lines = *(float *)&lines - 16.0;
        ++LODWORD(color.x);
        v36 = *(float *)&v19;
      }
      while ( v28 );
    }
    idConsoleLocal::DrawInput(v4);
    v29 = renderSystem->__vftable;
    v30 = idStr::ColorForIndex(58);
    v29->SetColor(renderSystem, v30);
  }
}

// FUNC: float __cdecl SCR_DrawSoundDecoders(float)
double __cdecl SCR_DrawSoundDecoders(float y)
{
  int v1; // esi
  idSoundSystem_vtbl *v2; // edx
  int v3; // ebx
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  double lastVolume; // [esp+8h] [ebp-B4h]
  int v10; // [esp+18h] [ebp-A4h]
  float starty; // [esp+28h] [ebp-94h]
  soundDecoderInfo_t decoderInfo; // [esp+2Ch] [ebp-90h] BYREF
  idStr name; // [esp+8Ch] [ebp-30h] BYREF
  int v14; // [esp+B8h] [ebp-4h]

  v1 = 0;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  decoderInfo.name.alloced = 20;
  decoderInfo.format.alloced = 20;
  v14 = 0;
  decoderInfo.name.len = 0;
  decoderInfo.name.data = decoderInfo.name.baseBuffer;
  decoderInfo.name.baseBuffer[0] = 0;
  decoderInfo.format.len = 0;
  decoderInfo.format.data = decoderInfo.format.baseBuffer;
  decoderInfo.format.baseBuffer[0] = 0;
  starty = y;
  v2 = soundSystem->__vftable;
  LOBYTE(v14) = 1;
  v3 = v2->GetSoundDecoderInfo(soundSystem, -1, &decoderInfo);
  if ( v3 != -1 )
  {
    while ( 1 )
    {
      v4 = decoderInfo.current44kHzTime - decoderInfo.start44kHzTime;
      v5 = decoderInfo.num44kHzSamples / decoderInfo.numChannels;
      if ( decoderInfo.current44kHzTime - decoderInfo.start44kHzTime <= decoderInfo.num44kHzSamples
                                                                      / decoderInfo.numChannels )
        break;
      if ( decoderInfo.looping )
      {
        v6 = 25 * (v4 % v5);
LABEL_7:
        v7 = 4 * v6 / v5;
        goto LABEL_8;
      }
      v7 = 100;
LABEL_8:
      v10 = decoderInfo.numBytes >> 10;
      lastVolume = decoderInfo.lastVolume;
      if ( v1 > 35 )
      {
        SCR_DrawTinyTextCenterAlign(
          &y,
          "%3d: %3d%% (%1.2f) %s: %s (%dkB)",
          v1,
          v7,
          lastVolume,
          decoderInfo.format.data,
          decoderInfo.name.data,
          v10);
      }
      else
      {
        SCR_DrawTinyTextLeftAlign(
          &y,
          "%3d: %3d%% (%1.2f) %s: %s (%dkB)",
          v1,
          v7,
          lastVolume,
          decoderInfo.format.data,
          decoderInfo.name.data,
          v10);
        if ( v1 == 35 )
          y = starty;
      }
      ++v1;
      v3 = soundSystem->GetSoundDecoderInfo(soundSystem, v3, &decoderInfo);
      if ( v3 == -1 )
        goto LABEL_13;
    }
    v6 = 25 * v4;
    goto LABEL_7;
  }
LABEL_13:
  LOBYTE(v14) = 2;
  idStr::FreeData(&decoderInfo.format);
  LOBYTE(v14) = 0;
  idStr::FreeData(&decoderInfo.name);
  v14 = -1;
  idStr::FreeData(&name);
  return y;
}

// FUNC: Con_Clear_f
void __cdecl Con_Clear_f()
{
  memset32(localConsole.text, 169871904, 0x30000u);
  localConsole.display = localConsole.current;
}

// FUNC: public: virtual void __thiscall idConsoleLocal::Init(void)
void __thiscall idConsoleLocal::Init(idConsoleLocal *this)
{
  idEditField *p_consoleField; // edi
  idEditField *historyEditLines; // esi
  int v4; // edi

  p_consoleField = &this->consoleField;
  this->keyCatching = 0;
  this->lastKeyEvent = -1;
  this->nextKeyEvent = 200;
  idEditField::Clear(&this->consoleField);
  idEditField::SetWidthInChars(p_consoleField, 78);
  historyEditLines = this->historyEditLines;
  v4 = 64;
  do
  {
    idEditField::Clear(historyEditLines);
    idEditField::SetWidthInChars(historyEditLines++, 78);
    --v4;
  }
  while ( v4 );
  cmdSystem->AddCommand(
    cmdSystem,
    "clear",
    (void (__cdecl *)(const idCmdArgs *))Con_Clear_f,
    2,
    "clears the console",
    0);
  cmdSystem->AddCommand(cmdSystem, "conDump", Con_Dump_f, 2, "dumps the console text to a file", 0);
}

// FUNC: public: virtual void __thiscall idConsoleLocal::Draw(bool)
void __userpurge idConsoleLocal::Draw(idConsoleLocal *this@<ecx>, int a2@<ebx>, bool forceFullScreen)
{
  bool v4; // zf
  float y; // [esp+4h] [ebp-4h] BYREF

  v4 = this->charSetShader == 0;
  y = 0.0;
  if ( !v4 )
  {
    if ( forceFullScreen )
    {
      this->Close(this);
      this->keyCatching = 1;
    }
    idConsoleLocal::Scroll(this);
    idConsoleLocal::UpdateDisplayFraction(this);
    if ( forceFullScreen )
    {
      idConsoleLocal::DrawSolidConsole(this, a2, (int)this, 1.0);
    }
    else if ( this->displayFrac == 0.0 )
    {
      if ( !idConsoleLocal::con_noPrint.internalVar->integerValue )
        idConsoleLocal::DrawNotify(this, (int)this);
    }
    else
    {
      idConsoleLocal::DrawSolidConsole(this, a2, (int)this, this->displayFrac);
    }
    if ( com_showFPS.internalVar->integerValue )
      y = SCR_DrawFPS(0.0);
    if ( com_showMemoryUsage.internalVar->integerValue )
      y = SCR_DrawMemoryUsage(y);
    if ( com_showAsyncStats.internalVar->integerValue )
      y = SCR_DrawAsyncStats(y);
    if ( com_showSoundDecoders.internalVar->integerValue )
      y = SCR_DrawSoundDecoders(y);
    if ( this->procFileOutOfDate )
      SCR_DrawTextRightAlign(&y, "PROC");
    if ( !idAsyncNetwork::client.active && !idAsyncNetwork::server.active && this->aasFileOutOfDate )
      SCR_DrawTextRightAlign(&y, "AAS");
    renderSystem->ShowDebugGraph(renderSystem);
  }
}
