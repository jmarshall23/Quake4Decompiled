
// FUNC: char const * __cdecl Com_GetVersion(void)
const char *__cdecl Com_GetVersion()
{
  return cvarSystem->GetCVarString(cvarSystem, "si_version");
}

// FUNC: char const * __cdecl Com_GetErrorMessage(void)
const char *__cdecl Com_GetErrorMessage()
{
  return (const char *)(*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 56))(common.type);
}

// FUNC: public: void __thiscall rvLanguage::SetHasVO(bool)
void __thiscall rvLanguage::SetHasVO(rvLanguage *this, bool in)
{
  this->hasVO = in;
}

// FUNC: public: bool __thiscall rvLanguage::HasVO(void)const
bool __thiscall rvLanguage::HasVO(rvLanguage *this)
{
  return this->hasVO;
}

// FUNC: public: bool __thiscall rvLanguage::Load(char const *,bool)
bool __thiscall rvLanguage::Load(rvLanguage *this, const char *fileName, bool clear)
{
  return idLangDict::Load(&this->strings, fileName, clear);
}

// FUNC: public: class idLangKeyValue const * __thiscall rvLanguage::GetString(int)const
const idLangKeyValue *__thiscall rvLanguage::GetString(rvLanguage *this, int i)
{
  return idLangDict::GetKeyVal(&this->strings, i);
}

// FUNC: public: char const * __thiscall rvLanguage::GetString(char const *)
const char *__thiscall rvLanguage::GetString(rvLanguage *this, const char *token)
{
  return idLangDict::GetString(&this->strings, token);
}

// FUNC: void __cdecl GSSStartData(void)
void __cdecl GSSStartData()
{
  ;
}

// FUNC: public: virtual void __thiscall idCommonLocal::BeginRedirect(char *,int,void (__cdecl *)(char const *))
void __thiscall idCommonLocal::BeginRedirect(
        idCommonLocal *this,
        char *buffer,
        int buffersize,
        void (__cdecl *flush)(const char *))
{
  if ( buffer && buffersize )
  {
    if ( flush )
    {
      this->rd_buffer = buffer;
      this->rd_buffersize = buffersize;
      this->rd_flush = flush;
      *this->rd_buffer = 0;
    }
  }
}

// FUNC: public: virtual void __thiscall idCommonLocal::EndRedirect(void)
void __thiscall idCommonLocal::EndRedirect(idCommonLocal *this)
{
  if ( this->rd_flush && *this->rd_buffer )
    this->rd_flush(this->rd_buffer);
  this->rd_buffer = 0;
  this->rd_buffersize = 0;
  this->rd_flush = 0;
}

// FUNC: public: virtual void __thiscall idCommonLocal::SetRefreshOnPrint(bool)
void __thiscall idCommonLocal::SetRefreshOnPrint(idCommonLocal *this, bool set)
{
  this->com_refreshOnPrint = set;
}

// FUNC: public: virtual void __cdecl idCommonLocal::Printf(char const *,...)
void idCommonLocal::Printf(idCommonLocal *this, const char *fmt, ...)
{
  va_list va; // [esp+14h] [ebp+10h] BYREF

  va_start(va, fmt);
  this->VPrintf(this, fmt, va);
}

// FUNC: public: virtual void __cdecl idCommonLocal::FatalError(char const *,...)
void __noreturn idCommonLocal::FatalError(idCommonLocal *this, const char *fmt, ...)
{
  va_list va; // [esp+14h] [ebp+10h] BYREF

  va_start(va, fmt);
  if ( this->com_errorEntered )
    Sys_Quit();
  this->com_errorEntered = 1;
  idStr::vsnPrintf(this->errorMessage, 4096, fmt, va);
  this->errorMessage[4095] = 0;
  if ( ((unsigned __int8 (__thiscall *)(idRenderSystem *, _DWORD))renderSystem->IsOpenGLRunning)(renderSystem, 0) )
  {
    if ( cvarSystem->GetCVarBool(cvarSystem, "r_fullscreen") )
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "vid_restart partial windowed\n");
  }
  this->Shutdown(this);
  Sys_Error("%s", this->errorMessage);
}

// FUNC: public: virtual void __thiscall idCommonLocal::Quit(void)
void __thiscall idCommonLocal::Quit(idCommonLocal *this)
{
  if ( !(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 2) )
  {
    if ( !this->com_errorEntered )
      this->Shutdown(this);
    Sys_Quit();
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Not allowed to exit game while Radiant is running\n");
}

// FUNC: private: void __thiscall idCommonLocal::ParseCommandLine(int,char const * *)
void __thiscall idCommonLocal::ParseCommandLine(idCommonLocal *this, int argc, const char **argv)
{
  int i; // [esp+8h] [ebp-4h]

  com_numConsoleLines = 0;
  for ( i = 0; i < argc; ++i )
  {
    if ( *argv[i] == 43 )
    {
      idCmdArgs::AppendArg(&com_consoleLines[com_numConsoleLines++], argv[i] + 1);
    }
    else
    {
      if ( !com_numConsoleLines )
        com_numConsoleLines = 1;
      idCmdArgs::AppendArg(&com_consoleLines[com_numConsoleLines - 1], argv[i]);
    }
  }
}

// FUNC: public: virtual int __thiscall idCommonLocal::GetUserCmdHz(void)const
int __thiscall idCommonLocal::GetUserCmdHz(idCommonLocal *this)
{
  if ( session && ((unsigned __int8 (__thiscall *)(idSession *, idCommonLocal *))session->IsMultiplayer)(session, this) )
    return 60;
  else
    return 60;
}

// FUNC: public: virtual int __thiscall idCommonLocal::GetUserCmdMSec(void)const
int __thiscall idCommonLocal::GetUserCmdMSec(idCommonLocal *this)
{
  if ( session && ((unsigned __int8 (__thiscall *)(idSession *, idCommonLocal *))session->IsMultiplayer)(session, this) )
    return 16;
  else
    return 16;
}

// FUNC: public: virtual void __thiscall idCommonLocal::InitTool(int,class idDict const *)
void __thiscall idCommonLocal::InitTool(idCommonLocal *this, int tool, const idDict *dict)
{
  if ( cvarSystem->GetCVarBool(cvarSystem, "r_fullscreen") )
  {
    cvarSystem->SetCVarBool(cvarSystem, "r_fullscreen", 0, 0);
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "vid_restart\n");
  }
  this->LoadToolsDLL(this);
  if ( this->toolsDLL )
  {
    idKeyInput::ClearStates();
    (*(void (__thiscall **)(_DWORD, int, const idDict *))(**(_DWORD **)common.ip + 20))(
      *(_DWORD *)common.ip,
      tool,
      dict);
  }
}

// FUNC: public: virtual class rvISourceControl * __thiscall idCommonLocal::GetSourceControl(void)
struct rvISourceControl *__thiscall idCommonLocal::GetSourceControl(idCommonLocal *this)
{
  return (struct rvISourceControl *)(*(int (__thiscall **)(_DWORD, idCommonLocal *))(**(_DWORD **)common.ip + 56))(
                                      *(_DWORD *)common.ip,
                                      this);
}

// FUNC: public: virtual void __thiscall idCommonLocal::ActivateTool(bool)
void __thiscall idCommonLocal::ActivateTool(idCommonLocal *this, bool active)
{
  idCommonLocal *v2; // eax

  v2 = this;
  this->editorActive = active;
  LOBYTE(v2) = !active;
  sys->GrabMouseCursor(sys, (bool)v2);
}

// FUNC: public: virtual void __thiscall idCommonLocal::ModViewThink(void)
void __thiscall idCommonLocal::ModViewThink(idCommonLocal *this)
{
  (*(void (__thiscall **)(_DWORD, idCommonLocal *))(**(_DWORD **)common.ip + 84))(*(_DWORD *)common.ip, this);
}

// FUNC: public: virtual void __thiscall idCommonLocal::RunAlwaysThinkGUIs(int)
void __thiscall idCommonLocal::RunAlwaysThinkGUIs(idCommonLocal *this, int time)
{
  uiManager->RunAlwaysThinkGUIs(uiManager, time);
}

// FUNC: public: virtual bool __thiscall idCommonLocal::DoingDeclValidation(void)
bool __thiscall idCommonLocal::DoingDeclValidation(idCommonLocal *this)
{
  return (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 1048704) == 1048704;
}

// FUNC: public: virtual void __thiscall idCommonLocal::SetCrashReportAutoSendString(char const *)
void __thiscall idCommonLocal::SetCrashReportAutoSendString(idCommonLocal *this, const char *psString)
{
  CI_SetCrashReportAutoSendString(psString);
}

// FUNC: public: virtual void __thiscall idCommonLocal::DebuggerCheckBreakpoint(class idInterpreter *,class idProgram *,int)
void __thiscall idCommonLocal::DebuggerCheckBreakpoint(
        idCommonLocal *this,
        idInterpreter *interpreter,
        idProgram *program,
        int instructionPointer)
{
  (*(void (__thiscall **)(_DWORD, idInterpreter *, idProgram *, int))(**(_DWORD **)common.ip + 156))(
    *(_DWORD *)common.ip,
    interpreter,
    program,
    instructionPointer);
}

// FUNC: public: virtual void __thiscall idCommonLocal::WriteFlaggedCVarsToFile(char const *,int,char const *)
void __thiscall idCommonLocal::WriteFlaggedCVarsToFile(
        idCommonLocal *this,
        const char *filename,
        int flags,
        const char *setCmd)
{
  idFile *f; // [esp+4h] [ebp-4h]

  f = fileSystem->OpenFileWrite(fileSystem, filename, "fs_savepath", 0);
  if ( f )
  {
    cvarSystem->WriteFlaggedVariables(cvarSystem, flags, setCmd, f);
    fileSystem->CloseFile(fileSystem, f);
  }
  else
  {
    this->Printf(this, "Couldn't write %s.\n", filename);
  }
}

// FUNC: public: virtual void __thiscall idCommonLocal::WriteConfigToFile(char const *)
void __thiscall idCommonLocal::WriteConfigToFile(idCommonLocal *this, const char *filename)
{
  idFile *f; // [esp+4h] [ebp-4h]

  f = fileSystem->OpenFileWrite(fileSystem, filename, "fs_savepath", 0);
  if ( f )
  {
    idKeyInput::WriteBindings(f);
    cvarSystem->WriteFlaggedVariables(cvarSystem, 0x20000, "seta", f);
    fileSystem->CloseFile(fileSystem, f);
  }
  else
  {
    this->Printf(this, "Couldn't write %s.\n", filename);
  }
}

// FUNC: Com_Editor_f
void __cdecl Com_Editor_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 2, 0);
}

// FUNC: Com_MaterialEditor_f
void __cdecl Com_MaterialEditor_f()
{
  soundSystem->SetMute(soundSystem, 1);
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 0x10000, 0);
}

// FUNC: Com_ModView_f
void __cdecl Com_ModView_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 0x2000, 0);
}

// FUNC: Com_LogView_f
void __cdecl Com_LogView_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 0x4000, 0);
}

// FUNC: Com_EntView_f
void __cdecl Com_EntView_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 0x8000, 0);
}

// FUNC: Com_FXEditor_f
void __cdecl Com_FXEditor_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 1024, 0);
}

// FUNC: Com_ReverbEditor_f
void __cdecl Com_ReverbEditor_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 2048, 0);
}

// FUNC: Com_EditPlaybacks_f
void __cdecl Com_EditPlaybacks_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 4096, 0);
}

// FUNC: Com_FXEditorPlayEffect_f
void __cdecl Com_FXEditorPlayEffect_f()
{
  (*(void (__thiscall **)(_DWORD, _DWORD))(**(_DWORD **)common.ip + 112))(*(_DWORD *)common.ip, 0);
}

// FUNC: Com_FXEditorPlayLoopingEffect_f
void __cdecl Com_FXEditorPlayLoopingEffect_f()
{
  (*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 112))(*(_DWORD *)common.ip, 1);
}

// FUNC: Com_FXEditorStopEffect_f
void __cdecl Com_FXEditorStopEffect_f()
{
  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 116))(*(_DWORD *)common.ip);
}

// FUNC: Com_ActivateEditor_f
void __cdecl Com_ActivateEditor_f()
{
  int v0; // eax

  v0 = (*(int (__thiscall **)(_DWORD, int, _DWORD))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, -1, 0);
  (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 60))(common.type, v0);
}

// FUNC: Com_PhonemeGen_f
void __cdecl Com_PhonemeGen_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 180))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_ShakesGen_f
void __cdecl Com_ShakesGen_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 184))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_RoQFileEncode_f
void __cdecl Com_RoQFileEncode_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 188))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_RenderBump_f
void __cdecl Com_RenderBump_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 192))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_RenderBumpFlat_f
void __cdecl Com_RenderBumpFlat_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 196))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_Dmap_f
void __cdecl Com_Dmap_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 200))(*(_DWORD *)common.ip, args);
}

// FUNC: void __cdecl Com_RunAAS_f(class idCmdArgs const &)
void __cdecl Com_RunAAS_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 204))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_RunAASDir_f
void __cdecl Com_RunAASDir_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 208))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_RunReach_f
void __cdecl Com_RunReach_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 212))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_RunAASTactical_f
void __cdecl Com_RunAASTactical_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 216))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_ScriptDebugger_f
void __cdecl Com_ScriptDebugger_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 8, 0);
}

// FUNC: Com_EditGUIs_f
void __cdecl Com_EditGUIs_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 4, 0);
}

// FUNC: Com_EditLights_f
void __cdecl Com_EditLights_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 32, 0);
}

// FUNC: Com_EditSounds_f
void __cdecl Com_EditSounds_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 64, 0);
}

// FUNC: Com_EditAFs_f
void __cdecl Com_EditAFs_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 256, 0);
}

// FUNC: Com_EditScripts_f
void __cdecl Com_EditScripts_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 16, 0);
}

// FUNC: Com_EditPDAs_f
void __cdecl Com_EditPDAs_f()
{
  (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 60))(common.type, 512, 0);
}

// FUNC: Com_LocalizeLipsyncs_f
void __cdecl Com_LocalizeLipsyncs_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 224))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_LocalizeGuis_f
void __cdecl Com_LocalizeGuis_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 220))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_LocalizeMaps_f
void __cdecl Com_LocalizeMaps_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 228))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_LocalizeValidateLipsyncs_f
void __cdecl Com_LocalizeValidateLipsyncs_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 232))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_LocalizeValidateStrings_f
void __cdecl Com_LocalizeValidateStrings_f(const idCmdArgs *args)
{
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, const idCmdArgs *))(**(_DWORD **)common.ip + 236))(*(_DWORD *)common.ip, args);
}

// FUNC: Com_Quit_f
void __cdecl Com_Quit_f()
{
  idCommonLocal::Quit(&commonLocal);
}

// FUNC: void __cdecl Com_ExecMPMachineSpec_f(class idCmdArgs const &)
void __cdecl Com_ExecMPMachineSpec_f()
{
  cvarSystem->SetCVarInteger(cvarSystem, "image_anisotropy", 1, 0x20000);
  ((void (__thiscall *)(idCVarSystem *, const char *, int, _DWORD))cvarSystem->SetCVarFloat)(
    cvarSystem,
    "r_lod_animations_distance",
    1232348160,
    0);
  cvarSystem->SetCVarBool(cvarSystem, "r_lod_shadows", 1, 0);
  cvarSystem->SetCVarBool(cvarSystem, "r_lod_entities", 1, 0);
}

// FUNC: void __cdecl Com_StartBuild_f(class idCmdArgs const &)
void __cdecl Com_StartBuild_f()
{
  globalImages->StartBuild(globalImages);
}

// FUNC: void __cdecl Com_WriteAssetLog_f(class idCmdArgs const &)
void __cdecl Com_WriteAssetLog_f()
{
  fileSystem->WriteAssetLog(fileSystem);
}

// FUNC: void __cdecl Com_ClearAssetLog_f(class idCmdArgs const &)
void __cdecl Com_ClearAssetLog_f()
{
  fileSystem->ClearAssetLog(fileSystem);
}

// FUNC: void __cdecl Com_ShowMemory_f(class idCmdArgs const &)
void __cdecl Com_ShowMemory_f(const idCmdArgs *args)
{
  unsigned int v1; // eax
  unsigned int total; // [esp+24h] [ebp-4h]
  unsigned int totala; // [esp+24h] [ebp-4h]
  unsigned int totalb; // [esp+24h] [ebp-4h]
  unsigned int totalc; // [esp+24h] [ebp-4h]

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Memory usage:\n");
  total = gameEdit->ScriptSummary(gameEdit, args);
  totala = total + gameEdit->ClassSummary(gameEdit, args);
  totalb = totala + gameEdit->EntitySummary(gameEdit, args);
  totalc = totalb + declManager->ListDeclSummary(declManager, args);
  v1 = session->rw->MemorySummary(session->rw, args);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "Total           - %.1fMeg\n",
    (double)(totalc + v1) / 1024.0);
}

// FUNC: private: virtual void __cdecl rvToolsStub::GEMessage(char const *,...)
void __cdecl rvToolsStub::GEMessage(rvToolsStub *this)
{
  ;
}

// FUNC: Com_Export_MD5R_f
void __cdecl Com_Export_MD5R_f()
{
  renderSystem->ExportMD5R(renderSystem, 0);
}

// FUNC: Com_Export_Cmp_MD5R_f
void __cdecl Com_Export_Cmp_MD5R_f()
{
  renderSystem->ExportMD5R(renderSystem, 1);
}

// FUNC: private: void __thiscall idCommonLocal::PrintLoadingMessage(char const *)
void __thiscall idCommonLocal::PrintLoadingMessage(idCommonLocal *this, const char *msg)
{
  int v2; // eax
  int v3; // eax
  const idMaterial *v4; // eax
  const idVec4 *v5; // eax
  const idMaterial *v6; // [esp-4h] [ebp-1Ch]

  if ( msg )
  {
    if ( *msg )
    {
      v2 = renderSystem->GetScreenHeight(renderSystem);
      v3 = ((int (__thiscall *)(idRenderSystem *, int))renderSystem->GetScreenWidth)(renderSystem, v2);
      ((void (__thiscall *)(idRenderSystem *, int))renderSystem->BeginFrame)(renderSystem, v3);
      v4 = declManager->FindMaterial(declManager, "gfx/splashScreen", 1);
      (*((void (__thiscall **)(idRenderSystem *, _DWORD, _DWORD, int, int, _DWORD, _DWORD, int, int, const idMaterial *))&renderSystem->SetColor4
       + 1))(
        renderSystem,
        0,
        0,
        1142947840,
        1139802112,
        0,
        0,
        1065353216,
        1065353216,
        v4);
      v6 = declManager->FindMaterial(declManager, "gfx/2d/bigchars", 1);
      v5 = idStr::ColorForIndex(58);
      renderSystem->DrawSmallStringExt(renderSystem, (int)(640 - 8 * strlen(msg)) / 2, 410, msg, v5, 1, v6);
      renderSystem->EndFrame(renderSystem, 0, 0, 0, 0);
    }
  }
}

// FUNC: public: virtual void __thiscall idCommonLocal::GUIFrame(bool,bool)
void __thiscall idCommonLocal::GUIFrame(idCommonLocal *this, bool execCmd, bool network)
{
  ((void (__thiscall *)(idSoundSystem *, idCommonLocal *))soundSystem->Frame)(soundSystem, this);
  if ( network )
    idAsyncNetwork::RunFrame();
  session->Frame(session);
  session->UpdateScreen(session, 0);
  Sys_GenerateEvents();
  idEventLoop::RunEventLoop(eventLoop, execCmd);
  com_frameTime = com_ticNumber * (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
}

// FUNC: public: virtual void __thiscall idCommonLocal::LoadToolsDLL(void)
void __thiscall idCommonLocal::LoadToolsDLL(idCommonLocal *this)
{
  _DWORD *v1; // eax
  toolsExport_t *(__cdecl *GetToolsAPI)(toolsImport_s *, void *(__cdecl *)(unsigned int), void (__cdecl *)(void *), unsigned int (__cdecl *)(void *)); // [esp+Ch] [ebp-17Ch]
  char dllPath[256]; // [esp+10h] [ebp-178h] BYREF
  toolsImport_s toolsImport; // [esp+110h] [ebp-78h] BYREF

  if ( !this->toolsDLL )
  {
    fileSystem->FindDLL(fileSystem, "tools", dllPath, 1);
    if ( dllPath[0] )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
        common.type,
        "Loading game DLL: '%s'\n",
        dllPath);
      this->toolsDLL = sys->DLL_Load(sys, dllPath);
      if ( this->toolsDLL )
      {
        GetToolsAPI = (toolsExport_t *(__cdecl *)(toolsImport_s *, void *(__cdecl *)(unsigned int), void (__cdecl *)(void *), unsigned int (__cdecl *)(void *)))Sys_DLL_GetProcAddress(this->toolsDLL, "GetToolsAPI");
        if ( GetToolsAPI )
        {
          toolsImport.version = 2;
          toolsImport.instance = this->toolsDLL;
          toolsImport.ownerWnd = win32.hWnd;
          toolsImport.ownerDC = win32.hDC;
          toolsImport.hGLRC = win32.hGLRC;
          toolsImport.pfd = &win32.pfd;
          toolsImport.sys = sys;
          toolsImport.common = (idCommon *)common.type;
          toolsImport.cmdSystem = cmdSystem;
          toolsImport.cvarSystem = cvarSystem;
          toolsImport.fileSystem = fileSystem;
          toolsImport.renderSystem = renderSystem;
          toolsImport.soundSystem = soundSystem;
          toolsImport.renderModelManager = renderModelManager;
          toolsImport.uiManager = uiManager;
          toolsImport.declManager = declManager;
          toolsImport.AASFile = AASFile;
          toolsImport.collisionModelManager = collisionModelManager;
          toolsImport.gameEdit = gameEdit;
          toolsImport.materialEdit = materialEdit;
          toolsImport.soundShaderEdit = soundShaderEdit;
          toolsImport.declAFEdit = declAFEdit;
          toolsImport.declPlaybackEdit = declPlaybackEdit;
          toolsImport.declEffectEdit = declEffectEdit;
          toolsImport.declLipSyncEdit = declLipSyncEdit;
          toolsImport.windowEdit = windowEdit;
          toolsImport.varEdit = varEdit;
          toolsImport.session = session;
          toolsImport.globalImages = globalImages;
          toolsImport.console = console;
          v1 = (_DWORD *)GetToolsAPI(&toolsImport, Memory::Allocate, Memory::Free, Memory::MSize);
          if ( *v1 == 2 )
          {
            *(_DWORD *)common.ip = v1[1];
          }
          else
          {
            Sys_DLL_Unload(this->toolsDLL);
            this->toolsDLL = 0;
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
              common.type,
              "wrong tools DLL API version");
          }
        }
        else
        {
          Sys_DLL_Unload(this->toolsDLL);
          this->toolsDLL = 0;
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "couldn't find tools DLL API");
        }
      }
      else
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "couldn't load tools dynamic library");
      }
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "couldn't find tools dynamic library");
    }
  }
}

// FUNC: public: virtual void __thiscall idCommonLocal::UnloadToolsDLL(void)
void __thiscall idCommonLocal::UnloadToolsDLL(idCommonLocal *this)
{
  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 36))(*(_DWORD *)common.ip);
  if ( this->toolsDLL )
  {
    Sys_DLL_Unload(this->toolsDLL);
    this->toolsDLL = 0;
  }
  *(_DWORD *)common.ip = &toolsStub;
}

// FUNC: private: void __thiscall idCommonLocal::LoadGameDLL(void)
void __thiscall idCommonLocal::LoadGameDLL(idCommonLocal *this)
{
  gameImport_t gameImport; // [esp+4h] [ebp-154h] BYREF
  char dllPath[256]; // [esp+40h] [ebp-118h] BYREF
  gameExport_t gameExport; // [esp+144h] [ebp-14h]
  gameExport_t *(__cdecl *GetGameAPI)(gameImport_t *); // [esp+154h] [ebp-4h]

  fileSystem->FindDLL(fileSystem, "game", dllPath, 1);
  if ( dllPath[0] )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "Loading game DLL: '%s'\n",
      dllPath);
    this->gameDLL = sys->DLL_Load(sys, dllPath);
    if ( this->gameDLL )
    {
      GetGameAPI = (gameExport_t *(__cdecl *)(gameImport_t *))Sys_DLL_GetProcAddress(this->gameDLL, "GetGameAPI");
      if ( GetGameAPI )
      {
        gameImport.version = 8;
        gameImport.sys = sys;
        gameImport.common = (idCommon *)common.type;
        gameImport.cmdSystem = cmdSystem;
        gameImport.cvarSystem = cvarSystem;
        gameImport.fileSystem = fileSystem;
        gameImport.networkSystem = networkSystem;
        gameImport.renderSystem = renderSystem;
        gameImport.soundSystem = soundSystem;
        gameImport.renderModelManager = renderModelManager;
        gameImport.uiManager = uiManager;
        gameImport.declManager = declManager;
        gameImport.AASFileManager = AASFileManager;
        gameImport.collisionModelManager = collisionModelManager;
        gameImport.bse = bse;
        gameExport = *GetGameAPI(&gameImport);
        if ( gameExport.version == 8 )
        {
          game = gameExport.game;
          gameEdit = gameExport.gameEdit;
          gameLog = gameExport.gameLog;
          if ( gameExport.game )
            game->Init(game, Memory::Allocate, Memory::Free, Memory::MSize);
        }
        else
        {
          Sys_DLL_Unload(this->gameDLL);
          this->gameDLL = 0;
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "wrong game DLL API version");
        }
      }
      else
      {
        Sys_DLL_Unload(this->gameDLL);
        this->gameDLL = 0;
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "couldn't find game DLL API");
      }
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "couldn't load game dynamic library");
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "couldn't find game dynamic library");
  }
}

// FUNC: private: void __thiscall idCommonLocal::UnloadGameDLL(void)
void __thiscall idCommonLocal::UnloadGameDLL(idCommonLocal *this)
{
  if ( game )
    game->Shutdown(game);
  if ( this->gameDLL )
  {
    Sys_DLL_Unload(this->gameDLL);
    this->gameDLL = 0;
  }
  game = 0;
  gameEdit = 0;
}

// FUNC: public: virtual bool __thiscall idCommonLocal::IsInitialized(void)const
bool __thiscall idCommonLocal::IsInitialized(idCommonLocal *this)
{
  return this->com_fullyInitialized;
}

// FUNC: public: virtual int __thiscall idCommonLocal::GetRModeForMachineSpec(int)const
int __thiscall idCommonLocal::GetRModeForMachineSpec(idCommonLocal *this, int machineSpec)
{
  if ( machineSpec == 3 )
    return 5;
  if ( machineSpec == 2 )
    return 4;
  return 3;
}

// FUNC: public: virtual void __thiscall idCommonLocal::SetDesiredMachineSpec(int)
void __thiscall idCommonLocal::SetDesiredMachineSpec(idCommonLocal *this, int machineSpec)
{
  this->desiredMachineSpec = machineSpec;
}

// FUNC: public: virtual char const * __thiscall idCommonLocal::KeysFromBinding(char const *)
const char *__thiscall idCommonLocal::KeysFromBinding(idCommonLocal *this, const char *bind)
{
  return idKeyInput::KeysFromBinding(bind);
}

// FUNC: void __cdecl GSSEndData(void)
void __cdecl GSSEndData()
{
  ;
}

// FUNC: char const * __cdecl Com_GetStringValue(void *)
const char *__cdecl Com_GetStringValue(_DWORD *var)
{
  return (const char *)var[1];
}

// FUNC: public: __thiscall rvLanguage::rvLanguage(void)
void __thiscall rvLanguage::rvLanguage(rvLanguage *this)
{
  this->language.len = 0;
  this->language.alloced = 20;
  this->language.data = this->language.baseBuffer;
  this->language.baseBuffer[0] = 0;
  idLangDict::idLangDict(&this->strings);
  this->hasVO = 0;
}

// FUNC: private: void __thiscall idCommonLocal::CloseLogFile(void)
void __thiscall idCommonLocal::CloseLogFile(idCommonLocal *this)
{
  if ( this->logFile )
  {
    idCVar::SetBool(&com_logFile, 0);
    fileSystem->CloseFile(fileSystem, this->logFile);
    this->logFile = 0;
  }
}

// FUNC: public: virtual void __thiscall idCommonLocal::VPrintf(char const *,char *)
void __thiscall idCommonLocal::VPrintf(idCommonLocal *this, char *fmt, char *args)
{
  char *v3; // eax
  const char *v4; // [esp+18h] [ebp-108Ch]
  int timeptr; // [esp+90h] [ebp-1014h] BYREF
  tm *tb; // [esp+94h] [ebp-1010h]
  int v8; // [esp+98h] [ebp-100Ch]
  char string; // [esp+9Ch] [ebp-1008h] BYREF
  _BYTE v10[4099]; // [esp+9Dh] [ebp-1007h] BYREF
  int v11; // [esp+10A0h] [ebp-4h]

  if ( cvarSystem->IsInitialized(cvarSystem) )
  {
    if ( idCVar::GetInteger(&com_timestampPrints) )
    {
      v8 = Sys_Milliseconds();
      if ( idCVar::GetInteger(&com_timestampPrints) == 1 )
        v8 /= 1000;
      sprintf(&string, "[%i]", v8);
      v11 = &v10[strlen(&string)] - v10;
    }
    else
    {
      v11 = 0;
    }
    if ( idStr::vsnPrintf(&v10[v11 - 1], 4096 - v11 - 1, fmt, args) < 0 )
    {
      v10[4093] = 10;
      v10[4094] = 0;
      Sys_Printf("idCommon::VPrintf: truncated to %d characters\n", strlen(&string) - 1);
    }
    if ( this->rd_buffer )
    {
      if ( (int)(strlen(this->rd_buffer) + &v10[strlen(&string)] - v10) > this->rd_buffersize - 1 )
      {
        this->rd_flush(this->rd_buffer);
        *this->rd_buffer = 0;
      }
      qmemcpy(&this->rd_buffer[strlen(this->rd_buffer)], &string, &v10[strlen(&string)] - &string);
    }
    else
    {
      console->Print(console, &string);
      PbCaptureConsoleOutput(&string, &v10[strlen(&string)] - v10);
      idStr::RemoveEscapes(&string, 30);
      Sys_Printf("%s", &string);
      (*(void (__thiscall **)(_DWORD, char *))(**(_DWORD **)common.ip + 152))(*(_DWORD *)common.ip, &string);
      if ( idCVar::GetInteger(&com_logFile) && !logFileFailed && fileSystem->IsInitialized(fileSystem) )
      {
        if ( !this->logFile && !recursing )
        {
          if ( *idCVar::GetString(&com_logFileName) )
            v4 = idCVar::GetString(&com_logFileName);
          else
            v4 = "qconsole.log";
          recursing = 1;
          this->logFile = fileSystem->OpenFileWrite(fileSystem, v4, "fs_savepath", 0);
          if ( !this->logFile )
          {
            logFileFailed = 1;
            this->FatalError(this, "failed to open log file '%s'\n", v4);
          }
          recursing = 0;
          if ( idCVar::GetInteger(&com_logFile) > 1 )
            this->logFile->ForceFlush(this->logFile);
          time(&timeptr);
          tb = localtime(&timeptr);
          v3 = asctime(tb);
          this->Printf(this, "log file '%s' opened on %s\n", v4, v3);
        }
        if ( this->logFile )
        {
          this->logFile->Write(this->logFile, &string, &v10[strlen(&string)] - v10);
          this->logFile->Flush(this->logFile);
        }
      }
      if ( this->com_errorEntered != 1 )
      {
        if ( this->com_refreshOnPrint )
          session->UpdateScreen(session, 1);
        session->PacifierUpdate(session);
      }
      (*(void (__thiscall **)(_DWORD, char *))(**(_DWORD **)common.ip + 168))(*(_DWORD *)common.ip, &string);
    }
  }
}

// FUNC: public: virtual void __cdecl idCommonLocal::DPrintf(char const *,...)
void idCommonLocal::DPrintf(idCommonLocal *this, char *fmt, ...)
{
  char dest[4103]; // [esp+4h] [ebp-1008h] BYREF
  bool com_refreshOnPrint; // [esp+100Bh] [ebp-1h]
  va_list va; // [esp+101Ch] [ebp+10h] BYREF

  va_start(va, fmt);
  if ( cvarSystem->IsInitialized(cvarSystem) && idCVar::GetBool(&com_developer) )
  {
    idStr::vsnPrintf(dest, 4096, fmt, va);
    dest[4095] = 0;
    com_refreshOnPrint = this->com_refreshOnPrint;
    this->com_refreshOnPrint = 0;
    this->Printf(this, "^1%s", dest);
    this->com_refreshOnPrint = com_refreshOnPrint;
  }
}

// FUNC: public: virtual void __cdecl idCommonLocal::DWarning(char const *,...)
void idCommonLocal::DWarning(idCommonLocal *this, char *fmt, ...)
{
  char dest[4096]; // [esp+4h] [ebp-1000h] BYREF
  va_list va; // [esp+1014h] [ebp+10h] BYREF

  va_start(va, fmt);
  if ( idCVar::GetBool(&com_developer) )
  {
    idStr::vsnPrintf(dest, 4096, fmt, va);
    dest[4095] = 0;
    this->Printf(this, "^3WARNING: %s\n", dest);
  }
}

// FUNC: private: bool __thiscall idCommonLocal::SafeMode(void)
char __thiscall idCommonLocal::SafeMode(idCommonLocal *this)
{
  const char *v1; // eax
  const char *v2; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < com_numConsoleLines; ++i )
  {
    v1 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( idStr::Icmp(v1, "safe") )
    {
      v2 = idCmdArgs::Argv(&com_consoleLines[i], 0);
      if ( idStr::Icmp(v2, "cvar_restart") )
        continue;
    }
    idCmdArgs::Clear(&com_consoleLines[i]);
    return 1;
  }
  return 0;
}

// FUNC: private: void __thiscall idCommonLocal::CheckToolMode(void)
void __thiscall idCommonLocal::CheckToolMode(idCommonLocal *this)
{
  const char *v1; // eax
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // eax
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  const char *v10; // eax
  const char *v11; // eax
  const char *v12; // eax
  const char *v13; // eax
  const char *v14; // eax
  const char *v15; // eax
  const char *v16; // eax
  const char *v17; // eax
  const char *v18; // eax
  const char *v19; // eax
  const char *v20; // eax
  const char *v21; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < com_numConsoleLines; ++i )
  {
    v1 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( idStr::Icmp(v1, "editguis") )
    {
      v2 = idCmdArgs::Argv(&com_consoleLines[i], 0);
      if ( idStr::Icmp(v2, "debugger") )
      {
        v3 = idCmdArgs::Argv(&com_consoleLines[i], 0);
        if ( idStr::Icmp(v3, "editor") )
        {
          v4 = idCmdArgs::Argv(&com_consoleLines[i], 0);
          if ( idStr::Icmp(v4, "editMaterials") )
          {
            v5 = idCmdArgs::Argv(&com_consoleLines[i], 0);
            if ( idStr::Icmp(v5, "modview") )
            {
              v6 = idCmdArgs::Argv(&com_consoleLines[i], 0);
              if ( idStr::Icmp(v6, "bundler") )
              {
                v7 = idCmdArgs::Argv(&com_consoleLines[i], 0);
                if ( !idStr::Icmp(v7, "makeLoadScreens") )
                  cvarSystem->SetCVarBool(cvarSystem, "com_MakeLoadScreens", 1, 0);
              }
              else
              {
                cvarSystem->SetCVarBool(cvarSystem, "com_Bundler", 1, 0);
              }
            }
            else
            {
              (*(void (__thiscall **)(_DWORD, int, _DWORD))(**(_DWORD **)common.ip + 20))(
                *(_DWORD *)common.ip,
                0x2000,
                0);
            }
          }
          else
          {
            (*(void (__thiscall **)(_DWORD, int, _DWORD))(**(_DWORD **)common.ip + 20))(
              *(_DWORD *)common.ip,
              0x10000,
              0);
          }
        }
        else
        {
          (*(void (__thiscall **)(_DWORD, int, _DWORD))(**(_DWORD **)common.ip + 20))(*(_DWORD *)common.ip, 2, 0);
        }
      }
      else
      {
        (*(void (__thiscall **)(_DWORD, int, _DWORD))(**(_DWORD **)common.ip + 20))(*(_DWORD *)common.ip, 8, 0);
      }
    }
    else
    {
      (*(void (__thiscall **)(_DWORD, int, _DWORD))(**(_DWORD **)common.ip + 20))(*(_DWORD *)common.ip, 4, 0);
    }
    v8 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( !idStr::Icmp(v8, "renderbump") )
      goto LABEL_31;
    v9 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( !idStr::Icmp(v9, "editor") )
      goto LABEL_31;
    v10 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( !idStr::Icmp(v10, "editguis") )
      goto LABEL_31;
    v11 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( !idStr::Icmp(v11, "debugger") )
      goto LABEL_31;
    v12 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( !idStr::Icmp(v12, "dmap") )
      goto LABEL_31;
    v13 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( !idStr::Icmp(v13, "editMaterials") )
      goto LABEL_31;
    v14 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( idStr::Icmp(v14, "modview") )
    {
      v15 = idCmdArgs::Argv(&com_consoleLines[i], 0);
      if ( idStr::Icmp(v15, "editfx") )
      {
        v16 = idCmdArgs::Argv(&com_consoleLines[i], 0);
        if ( idStr::Icmp(v16, "editReverb") )
        {
          v17 = idCmdArgs::Argv(&com_consoleLines[i], 0);
          if ( idStr::Icmp(v17, "editPlaybacks") )
          {
            v18 = idCmdArgs::Argv(&com_consoleLines[i], 0);
            if ( idStr::Icmp(v18, "logview") )
            {
              v19 = idCmdArgs::Argv(&com_consoleLines[i], 0);
              if ( idStr::Icmp(v19, "entview") )
              {
                v20 = idCmdArgs::Argv(&com_consoleLines[i], 0);
                if ( idStr::Icmp(v20, "renderbumpflatgui") )
                {
                  v21 = idCmdArgs::Argv(&com_consoleLines[i], 0);
                  if ( idStr::Icmp(v21, "bundler") )
                    continue;
                }
              }
            }
          }
        }
      }
    }
LABEL_31:
    cvarSystem->SetCVarBool(cvarSystem, "r_fullscreen", 0, 0);
    return;
  }
}

// FUNC: public: virtual void __thiscall idCommonLocal::StartupVariable(char const *,bool)
void __thiscall idCommonLocal::StartupVariable(idCommonLocal *this, const char *match, bool once)
{
  const char *v3; // eax
  const char *v4; // eax
  int j; // [esp+4h] [ebp-Ch]
  const char *s; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  i = 0;
  while ( i < com_numConsoleLines )
  {
    v3 = idCmdArgs::Argv(&com_consoleLines[i], 0);
    if ( idStr::Cmp(v3, "set") )
    {
      ++i;
    }
    else
    {
      s = idCmdArgs::Argv(&com_consoleLines[i], 1);
      if ( match && idStr::Icmp(s, match)
        || (v4 = idCmdArgs::Argv(&com_consoleLines[i], 2), cvarSystem->SetCVarString(cvarSystem, s, v4, 0), !once) )
      {
        ++i;
      }
      else
      {
        for ( j = i + 1; j < com_numConsoleLines; ++j )
          idCmdArgs::operator=(&com_consoleLines[j - 1].argc, (char *)&com_consoleLines[j]);
        --com_numConsoleLines;
      }
    }
  }
}

// FUNC: private: bool __thiscall idCommonLocal::AddStartupCommands(void)
bool __thiscall idCommonLocal::AddStartupCommands(idCommonLocal *this)
{
  const char *v1; // eax
  bool added; // [esp+7h] [ebp-5h]
  int i; // [esp+8h] [ebp-4h]

  added = 0;
  for ( i = 0; i < com_numConsoleLines; ++i )
  {
    if ( idEditField::GetCursor(&com_consoleLines[i]) )
    {
      v1 = idCmdArgs::Argv(&com_consoleLines[i], 0);
      if ( idStr::Icmpn(v1, "set", 3) )
        added = 1;
      cmdSystem->BufferCommandArgs(cmdSystem, CMD_EXEC_APPEND, &com_consoleLines[i]);
    }
  }
  return added;
}

// FUNC: private: void __thiscall idCommonLocal::WriteConfiguration(void)
void __thiscall idCommonLocal::WriteConfiguration(idCommonLocal *this)
{
  int v1; // eax
  bool developer; // [esp+7h] [ebp-1h]

  if ( this->com_fullyInitialized && (cvarSystem->GetModifiedFlags(cvarSystem) & 0x20000) != 0 )
  {
    cvarSystem->ClearModifiedFlags(cvarSystem, 0x20000);
    developer = idCVar::GetBool(&com_developer);
    idCVar::SetBool(&com_developer, 0);
    this->WriteConfigToFile(this, "Quake4Config.cfg");
    session->WriteCDKey(session);
    v1 = ((int (__thiscall *)(idSession *))session->SetMainMenuGuiVars)(session);
    LOBYTE(v1) = developer;
    idCVar::SetBool(&com_developer, v1);
  }
}

// FUNC: Com_RenderBumpFlatGUI_f
void __cdecl Com_RenderBumpFlatGUI_f(idCmdArgs *args)
{
  const char *v1; // eax

  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  if ( idEditField::GetCursor(args) == 2 )
  {
    if ( cvarSystem->GetCVarBool(cvarSystem, "r_fullscreen") )
    {
      cvarSystem->SetCVarBool(cvarSystem, "r_fullscreen", 0, 0);
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "vid_restart\n");
    }
    v1 = idCmdArgs::Argv(args, 1);
    (*(void (__thiscall **)(_DWORD, const char *))(**(_DWORD **)common.ip + 72))(*(_DWORD *)common.ip, v1);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Usage: renderbumpFlatGUI <filename>\n");
  }
}

// FUNC: Com_Freeze_f
void __cdecl Com_Freeze_f(idCmdArgs *args)
{
  const char *v1; // eax
  int start; // [esp+4h] [ebp-Ch]
  float s; // [esp+Ch] [ebp-4h]

  if ( idEditField::GetCursor(args) == 2 )
  {
    if ( idCVar::GetBool(&com_developer) )
    {
      v1 = idCmdArgs::Argv(args, 1);
      s = atof(v1);
      start = idEventLoop::Milliseconds(eventLoop);
      while ( (double)(idEventLoop::Milliseconds(eventLoop) - start) * 0.001 <= s )
        ;
    }
    else
    {
      idCommonLocal::Printf(&commonLocal, "freeze may only be used in developer mode\n");
    }
  }
  else
  {
    idCommonLocal::Printf(&commonLocal, "freeze <seconds>\n");
  }
}

// FUNC: Com_Crash_f
void __cdecl Com_Crash_f()
{
  if ( idCVar::GetBool(&com_developer) )
    MEMORY[0] = 305419896;
  else
    idCommonLocal::Printf(&commonLocal, "crash may only be used in developer mode\n");
}

// FUNC: public: __thiscall MemInfo::MemInfo(void)
void __thiscall MemInfo::MemInfo(MemInfo *this)
{
  this->filebase.len = 0;
  this->filebase.alloced = 20;
  this->filebase.data = this->filebase.baseBuffer;
  *this->filebase.data = 0;
  this->total = 0;
  this->assetTotals = 0;
  this->imageAssetsTotal = 0;
  this->modelAssetsTotal = 0;
  this->soundAssetsTotal = 0;
  this->collAssetsTotal = 0;
  this->animsAssetsTotal = 0;
  this->aasAssetsTotal = 0;
  this->imageAssetsCount = 0;
  this->modelAssetsCount = 0;
  this->soundAssetsCount = 0;
  this->collAssetsCount = 0;
  this->animsAssetsCount = 0;
  this->aasAssetsCount = 0;
}

// FUNC: void __cdecl Com_WriteConfig_f(class idCmdArgs const &)
void __cdecl Com_WriteConfig_f(idCmdArgs *args)
{
  char *v1; // eax
  idStr filename; // [esp+8h] [ebp-2Ch] BYREF
  int v3; // [esp+30h] [ebp-4h]

  filename.len = 0;
  filename.alloced = 20;
  filename.data = filename.baseBuffer;
  filename.baseBuffer[0] = 0;
  v3 = 0;
  if ( idEditField::GetCursor(args) == 2 )
  {
    v1 = (char *)idCmdArgs::Argv(args, 1);
    idStr::operator=(&filename, v1);
    idStr::DefaultFileExtension(&filename, ".cfg");
    idCommonLocal::Printf(&commonLocal, "Writing %s.\n", filename.data);
    idCommonLocal::WriteConfigToFile(&commonLocal, filename.data);
  }
  else
  {
    idCommonLocal::Printf(&commonLocal, "Usage: writeconfig <filename>\n");
  }
  v3 = -1;
  idStr::FreeData(&filename);
}

// FUNC: void __cdecl Com_ExecMachineSpec_f(class idCmdArgs const &)
void __cdecl Com_ExecMachineSpec_f()
{
  int downSizeSpecular; // [esp+0h] [ebp-20h]
  int downSizeSpecularLimit; // [esp+4h] [ebp-1Ch]
  int downSize; // [esp+8h] [ebp-18h]
  bool oldCard; // [esp+Fh] [ebp-11h] BYREF
  int downSizeBump; // [esp+10h] [ebp-10h]
  bool nv10or20; // [esp+17h] [ebp-9h] BYREF
  int downSizeLimit; // [esp+18h] [ebp-8h]
  int downSizeBumpLimit; // [esp+1Ch] [ebp-4h]

  if ( idCVar::GetInteger(&com_machineSpec) == 3 )
  {
    cvarSystem->SetCVarInteger(cvarSystem, "image_useCompression", 0, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_useNormalCompression", 0, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_usePrecompressedTextures", 0, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_lodbias", 0, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_anisotropy", 8, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_ignoreHighQuality", 0, 0x20000);
    downSize = 0;
    downSizeLimit = 256;
    downSizeSpecular = 0;
    downSizeSpecularLimit = 256;
    downSizeBump = 0;
    downSizeBumpLimit = 256;
    cvarSystem->SetCVarInteger(cvarSystem, "r_mode", 5, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "r_multiSamples", 0, 0x20000);
    ((void (__thiscall *)(idCVarSystem *, const char *, int, int))cvarSystem->SetCVarFloat)(
      cvarSystem,
      "g_brassTime",
      0x40000000,
      0x20000);
    ((void (__thiscall *)(idCVarSystem *, const char *, int, int))cvarSystem->SetCVarFloat)(
      cvarSystem,
      "bse_scale",
      1067030938,
      0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "r_skipNewAmbient", 0, 0x20000);
  }
  else if ( idCVar::GetInteger(&com_machineSpec) == 2 )
  {
    cvarSystem->SetCVarInteger(cvarSystem, "image_useCompression", 1, 0x20000);
    if ( !cvarSystem->GetCVarInteger(cvarSystem, "image_useNormalCompression") )
      cvarSystem->SetCVarInteger(cvarSystem, "image_useNormalCompression", 2, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_usePrecompressedTextures", 1, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_lodbias", 0, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_anisotropy", 4, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_ignoreHighQuality", 0, 0x20000);
    downSize = 0;
    downSizeLimit = 256;
    downSizeSpecular = 0;
    downSizeSpecularLimit = 64;
    downSizeBump = 0;
    downSizeBumpLimit = 256;
    cvarSystem->SetCVarInteger(cvarSystem, "r_mode", 4, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "r_multiSamples", 0, 0x20000);
    ((void (__thiscall *)(idCVarSystem *, const char *, int, int))cvarSystem->SetCVarFloat)(
      cvarSystem,
      "g_brassTime",
      1065353216,
      0x20000);
    ((void (__thiscall *)(idCVarSystem *, const char *, int, int))cvarSystem->SetCVarFloat)(
      cvarSystem,
      "bse_scale",
      1065353216,
      0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "r_skipNewAmbient", 0, 0x20000);
  }
  else if ( idCVar::GetInteger(&com_machineSpec) == 1 )
  {
    cvarSystem->SetCVarInteger(cvarSystem, "image_useCompression", 1, 0x20000);
    if ( !cvarSystem->GetCVarInteger(cvarSystem, "image_useNormalCompression") )
      cvarSystem->SetCVarInteger(cvarSystem, "image_useNormalCompression", 2, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_usePrecompressedTextures", 1, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_lodbias", 0, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_anisotropy", 1, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_ignoreHighQuality", 1, 0x20000);
    downSize = 0;
    downSizeLimit = 256;
    downSizeSpecular = 0;
    downSizeSpecularLimit = 64;
    downSizeBump = 0;
    downSizeBumpLimit = 256;
    cvarSystem->SetCVarInteger(cvarSystem, "r_mode", 3, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "r_multiSamples", 0, 0x20000);
    ((void (__thiscall *)(idCVarSystem *, const char *, _DWORD, int))cvarSystem->SetCVarFloat)(
      cvarSystem,
      "g_brassTime",
      0,
      0x20000);
    ((void (__thiscall *)(idCVarSystem *, const char *, int, int))cvarSystem->SetCVarFloat)(
      cvarSystem,
      "bse_scale",
      1059648963,
      0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "r_skipNewAmbient", 1, 0x20000);
  }
  else
  {
    cvarSystem->SetCVarInteger(cvarSystem, "image_useCompression", 1, 0x20000);
    if ( !cvarSystem->GetCVarInteger(cvarSystem, "image_useNormalCompression") )
      cvarSystem->SetCVarInteger(cvarSystem, "image_useNormalCompression", 2, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_usePrecompressedTextures", 1, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_lodbias", 0, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_anisotropy", 1, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "image_ignoreHighQuality", 1, 0x20000);
    downSize = 1;
    downSizeLimit = 256;
    downSizeSpecular = 1;
    downSizeSpecularLimit = 64;
    downSizeBump = 1;
    downSizeBumpLimit = 256;
    cvarSystem->SetCVarInteger(cvarSystem, "r_mode", 3, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "r_multiSamples", 0, 0x20000);
    ((void (__thiscall *)(idCVarSystem *, const char *, _DWORD, int))cvarSystem->SetCVarFloat)(
      cvarSystem,
      "g_brassTime",
      0,
      0x20000);
    ((void (__thiscall *)(idCVarSystem *, const char *, int, int))cvarSystem->SetCVarFloat)(
      cvarSystem,
      "bse_scale",
      1051260355,
      0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "r_skipNewAmbient", 1, 0x20000);
  }
  if ( Sys_GetVideoRam() < 80 )
  {
    cvarSystem->SetCVarBool(cvarSystem, "image_ignoreHighQuality", 1, 0x20000);
    downSize = 1;
    downSizeLimit = 128;
    downSizeSpecular = 1;
    downSizeSpecularLimit = 64;
    downSizeBump = 1;
    downSizeBumpLimit = 128;
  }
  if ( Sys_GetSystemRam() >= 750 )
  {
    if ( Sys_GetSystemRam() >= 1000 )
      cvarSystem->SetCVarInteger(cvarSystem, "s_maxSoundsPerShader", 0, 0x20000);
    else
      cvarSystem->SetCVarInteger(cvarSystem, "s_maxSoundsPerShader", 2, 0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "com_purgeAll", 0, 0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "r_forceLoadImages", 0, 0x20000);
  }
  else
  {
    cvarSystem->SetCVarBool(cvarSystem, "image_ignoreHighQuality", 1, 0x20000);
    cvarSystem->SetCVarInteger(cvarSystem, "s_maxSoundsPerShader", 1, 0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "com_purgeAll", 1, 0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "r_forceLoadImages", 1, 0x20000);
  }
  cvarSystem->SetCVarInteger(cvarSystem, "image_downSize", downSize, 0x20000);
  cvarSystem->SetCVarInteger(cvarSystem, "image_downSizeLimit", downSizeLimit, 0x20000);
  cvarSystem->SetCVarInteger(cvarSystem, "image_downSizeSpecular", downSizeSpecular, 0x20000);
  cvarSystem->SetCVarInteger(cvarSystem, "image_downSizeSpecularLimit", downSizeSpecularLimit, 0x20000);
  cvarSystem->SetCVarInteger(cvarSystem, "image_downSizeBump", downSizeBump, 0x20000);
  cvarSystem->SetCVarInteger(cvarSystem, "image_downSizeBumpLimit", downSizeBumpLimit, 0x20000);
  oldCard = 0;
  nv10or20 = 0;
  renderSystem->GetCardCaps(renderSystem, &oldCard, &nv10or20);
  if ( oldCard )
  {
    cvarSystem->SetCVarBool(cvarSystem, "g_decals", 0, 0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "g_projectileLights", 0, 0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "r_skipNewAmbient", 1, 0x20000);
  }
  else
  {
    cvarSystem->SetCVarBool(cvarSystem, "g_decals", 1, 0x20000);
    cvarSystem->SetCVarBool(cvarSystem, "g_projectileLights", 1, 0x20000);
  }
}

// FUNC: public: void __thiscall idCommonLocal::SetActiveLanguage(void)
void __thiscall idCommonLocal::SetActiveLanguage(idCommonLocal *this)
{
  char *String; // eax
  char *s2; // [esp+8h] [ebp-3Ch]
  int i; // [esp+14h] [ebp-30h]
  idStr lang; // [esp+18h] [ebp-2Ch] BYREF
  int v6; // [esp+40h] [ebp-4h]

  lang.len = 0;
  lang.alloced = 20;
  lang.data = lang.baseBuffer;
  lang.baseBuffer[0] = 0;
  v6 = 0;
  if ( idCVar::IsModified((idCVar *)&common.port) )
  {
    String = (char *)idCVar::GetString((idCVar *)&common.port);
    idStr::operator=(&lang, String);
    for ( i = 0; i < this->languages.num; ++i )
    {
      s2 = (char *)rvLanguage::GetLanguage(&this->languages.list[i]);
      if ( !idStr::Icmp(lang.data, s2) )
      {
        this->languageDictIndex = i;
        break;
      }
    }
    if ( i == this->languages.num )
    {
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "reset sys_lang");
      idCommonLocal::SetActiveLanguage(this);
    }
    idCVar::ClearModified((idCVar *)&common.port);
    v6 = -1;
    idStr::FreeData(&lang);
  }
  else
  {
    v6 = -1;
    idStr::FreeData(&lang);
  }
}

// FUNC: public: virtual bool __thiscall idCommonLocal::LanguageHasVO(int)const
bool __thiscall idCommonLocal::LanguageHasVO(idCommonLocal *this, int index)
{
  if ( index >= 0 )
    return rvLanguage::HasVO(&this->languages.list[index]);
  else
    return rvLanguage::HasVO(&this->languages.list[this->languageDictIndex]);
}

// FUNC: public: virtual char const * __thiscall idCommonLocal::GetLanguage(int)const
const char *__thiscall idCommonLocal::GetLanguage(idCommonLocal *this, int index)
{
  if ( index >= 0 )
    return rvLanguage::GetLanguage(&this->languages.list[index]);
  else
    return rvLanguage::GetLanguage(&this->languages.list[this->languageDictIndex]);
}

// FUNC: public: virtual char const * __thiscall idCommonLocal::GetLocalizedString(char const *,int)
const char *__thiscall idCommonLocal::GetLocalizedString(idCommonLocal *this, const char *token, int langIndex)
{
  if ( langIndex >= 0 )
    return rvLanguage::GetString(&this->languages.list[langIndex], token);
  else
    return rvLanguage::GetString(&this->languages.list[this->languageDictIndex], token);
}

// FUNC: public: virtual class idLangKeyValue const * __thiscall idCommonLocal::GetLocalizedString(int,int)
const idLangKeyValue *__thiscall idCommonLocal::GetLocalizedString(idCommonLocal *this, int index, int langIndex)
{
  if ( langIndex >= 0 )
    return rvLanguage::GetString(&this->languages.list[langIndex], index);
  else
    return rvLanguage::GetString(&this->languages.list[this->languageDictIndex], index);
}

// FUNC: void __cdecl Com_FinishBuild_f(class idCmdArgs const &)
void __cdecl Com_FinishBuild_f(idCmdArgs *args)
{
  int Cursor; // eax

  if ( game )
    game->CacheDictionaryMedia(game, 0);
  Cursor = idEditField::GetCursor(args);
  LOBYTE(Cursor) = Cursor > 1;
  globalImages->FinishBuild(globalImages, Cursor);
}

// FUNC: IncrementCVar_f
void __cdecl IncrementCVar_f(idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // eax
  float incAmt; // [esp+0h] [ebp-10h]
  float maxAmt; // [esp+4h] [ebp-Ch]
  float val; // [esp+8h] [ebp-8h]
  const char *cvarName; // [esp+Ch] [ebp-4h]

  if ( idEditField::GetCursor(args) > 3 )
  {
    cvarName = idCmdArgs::Argv(args, 1);
    v1 = idCmdArgs::Argv(args, 2);
    incAmt = atof(v1);
    v2 = idCmdArgs::Argv(args, 3);
    maxAmt = atof(v2);
    val = ((double (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarFloat)(cvarSystem, cvarName) + incAmt;
    if ( val > (double)maxAmt )
      val = maxAmt;
    ((void (__thiscall *)(idCVarSystem *, const char *, _DWORD, _DWORD))cvarSystem->SetCVarFloat)(
      cvarSystem,
      cvarName,
      LODWORD(val),
      0);
  }
}

// FUNC: DecrementCVar_f
void __cdecl DecrementCVar_f(idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // eax
  float minAmt; // [esp+0h] [ebp-10h]
  float val; // [esp+4h] [ebp-Ch]
  const char *cvarName; // [esp+8h] [ebp-8h]
  float decAmt; // [esp+Ch] [ebp-4h]

  if ( idEditField::GetCursor(args) > 3 )
  {
    cvarName = idCmdArgs::Argv(args, 1);
    v1 = idCmdArgs::Argv(args, 2);
    decAmt = atof(v1);
    v2 = idCmdArgs::Argv(args, 3);
    minAmt = atof(v2);
    val = ((double (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarFloat)(cvarSystem, cvarName) - decAmt;
    if ( val < (double)minAmt )
      val = minAmt;
    ((void (__thiscall *)(idCVarSystem *, const char *, _DWORD, _DWORD))cvarSystem->SetCVarFloat)(
      cvarSystem,
      cvarName,
      LODWORD(val),
      0);
  }
}

// FUNC: private: void __thiscall idCommonLocal::InitRenderSystem(void)
void __thiscall idCommonLocal::InitRenderSystem(idCommonLocal *this)
{
  const char *v1; // eax

  if ( !idCVar::GetBool(&com_skipRenderer) )
  {
    renderSystem->InitOpenGL(renderSystem);
    v1 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                         common.type,
                         "#str_104343",
                         -1);
    idCommonLocal::PrintLoadingMessage(this, v1);
  }
}

// FUNC: private: void __thiscall idCommonLocal::ApplyVideoSettings(void)
void __thiscall idCommonLocal::ApplyVideoSettings(idCommonLocal *this)
{
  int desiredRMode; // [esp+4h] [ebp-90Ch]
  idCmdArgs args; // [esp+8h] [ebp-908h] BYREF

  idCmdArgs::idCmdArgs(&args);
  if ( this->desiredMachineSpec != -1 )
  {
    desiredRMode = cvarSystem->GetCVarInteger(cvarSystem, "r_mode");
    Com_ExecMachineSpec_f(&args);
    cvarSystem->SetCVarInteger(cvarSystem, "r_mode", desiredRMode, 0);
    this->WriteConfigToFile(this, "Quake4Config.cfg");
  }
}

// FUNC: private: void __thiscall idCommonLocal::InitSIMD(void)
void __thiscall idCommonLocal::InitSIMD(idCommonLocal *this)
{
  bool Bool; // al

  Bool = idCVar::GetBool(&com_forceGenericSIMD);
  idSIMD::InitProcessor("engine", Bool);
  idCVar::ClearModified(&com_forceGenericSIMD);
}

// FUNC: public: virtual void __thiscall idCommonLocal::Frame(void)
void __thiscall idCommonLocal::Frame(idCommonLocal *this)
{
  int v1; // [esp+0h] [ebp-50h] BYREF
  const char *State; // [esp+Ch] [ebp-44h]
  int v4; // [esp+14h] [ebp-3Ch]
  int v6; // [esp+1Ch] [ebp-34h]
  bool v7; // [esp+23h] [ebp-2Dh]
  const char *v8; // [esp+24h] [ebp-2Ch]
  const char *v9; // [esp+28h] [ebp-28h]
  idCommonLocal *thisa; // [esp+34h] [ebp-1Ch]
  int nowTime; // [esp+38h] [ebp-18h]
  int com_frameMsec; // [esp+3Ch] [ebp-14h]
  int *v15; // [esp+40h] [ebp-10h]
  int v16; // [esp+4Ch] [ebp-4h]

  v15 = &v1;
  thisa = this;
  net_bytesIn = 0;
  net_bytesOut = 0;
  if ( idCVar::GetBool(&idAsyncNetwork::debugFrameTime) )
  {
    profile_frameTime = 0;
    profile_predictTime = 0;
    profile_packetTime = 0;
    profile_clientPredictTime = 0;
    profile_gameTimeResidual = 0;
  }
  if ( !net_debug && idCVar::GetBool(&idAsyncNetwork::debugTraffic) )
  {
    net_debug = fileSystem->OpenFileWrite(fileSystem, "debug_net.txt", "fs_savepath", 0);
    net_debug->Printf(
      net_debug,
      "Bytes In, Bytes Out, Server Bytes In, Server Bytes Out, Client Bytes In, Client Bytes Out\n");
  }
  v16 = 0;
  if ( cvarSystem->GetCVarInteger(cvarSystem, "r_videoSettingsFailed") )
  {
    if ( !thisa->IsToolActive(thisa) )
    {
      cvarSystem->SetCVarInteger(cvarSystem, "r_videoSettingsFailed", 0, 0);
      v9 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                           common.type,
                           "#str_100626",
                           -1);
      v8 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                           common.type,
                           "#str_104853",
                           -1);
      session->MessageBoxA(session, MSG_OK, v8, v9, 1, 0, 0, 0);
    }
  }
  Sys_GenerateEvents();
  idCommonLocal::WriteConfiguration(thisa);
  if ( idCVar::IsModified(&com_forceGenericSIMD) )
    idCommonLocal::InitSIMD(thisa);
  idCommonLocal::SetActiveLanguage(thisa);
  v7 = game->IsDebugHudActive(game);
  com_debugHudActive = v7;
  idEventLoop::RunEventLoop(eventLoop, 1);
  v6 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
  com_frameTime = v6 * com_ticNumber;
  if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 0x2000) )
  {
    session->rw->DebugClear(session->rw, 0);
  }
  else if ( !idAsyncClient::IsActive(&idAsyncNetwork::client) && session->rw )
  {
    session->rw->DebugClear(session->rw, com_frameTime);
  }
  soundSystem->Frame(soundSystem);
  idAsyncNetwork::RunFrame();
  if ( idAsyncNetwork::IsActive() )
  {
    if ( idCVar::GetInteger(&idAsyncNetwork::serverDedicated) != 1 )
    {
      session->GuiFrameEvents(session);
      session->UpdateScreen(session, 0);
    }
  }
  else
  {
    session->Frame(session);
    session->UpdateScreen(session, 0);
  }
  if ( idCVar::GetBool(&com_speeds) || com_debugHudActive )
  {
    v4 = Sys_Milliseconds();
    nowTime = v4;
    com_frameMsec = v4 - lastTime;
    lastTime = v4;
    if ( idCVar::GetBool(&com_speeds) )
      thisa->Printf(
        thisa,
        "frame:%i all:%3i gfr:%3i rf:%3i bk:%3i w:(%d)\n",
        com_frameNumber,
        com_frameMsec,
        time_gameFrame,
        time_frontend,
        time_backend,
        time_waiting);
    if ( com_debugHudActive )
    {
      game->DebugSetInt(game, "time_gameFrame", time_gameFrame);
      game->DebugSetInt(game, "time_gameDraw", time_gameDraw);
      game->DebugSetInt(game, "time_totalFrame", com_frameMsec);
      game->DebugSetInt(game, "time_frontend", time_frontend);
      game->DebugSetInt(game, "time_backend", time_backend);
      game->DebugSetInt(game, "time_waiting", time_waiting);
      game->DebugSetInt(game, "incoming_bytes", net_bytesIn);
      game->DebugSetInt(game, "outgoing_bytes", net_bytesOut);
      game->DebugSetInt(game, "catchup_frames", net_catchupFrames);
    }
    net_catchupFrames = 0;
    net_bytesIn = 0;
    net_bytesOut = 0;
    time_waiting = 0;
    time_gameFrame = 0;
    time_gameDraw = 0;
  }
  idLib::frameNumber = ++com_frameNumber;
  if ( !Sys_FPU_StackIsEmpty() )
  {
    State = Sys_FPU_GetState();
    thisa->Printf(thisa, State);
    thisa->FatalError(thisa, "idCommon::Frame: the FPU stack is not empty at the end of the frame\n");
  }
  v16 = -1;
  if ( net_debug )
    net_debug->Printf(
      net_debug,
      "%d, %d, %d, %d, %d, %d\n",
      net_bytesIn,
      net_bytesOut,
      net_serverBytesIn,
      net_serverBytesOut,
      net_clientBytesIn,
      net_clientBytesOut);
}

// FUNC: private: void __thiscall idCommonLocal::SingleAsyncTic(void)
void __thiscall idCommonLocal::SingleAsyncTic(idCommonLocal *this)
{
  int Integer; // [esp+0h] [ebp-Ch]
  asyncStats_t *stat; // [esp+8h] [ebp-4h]

  stat = &com_asyncStats[com_ticNumber & 0x3FF];
  stat->milliseconds = 0;
  stat->deltaMsec = 0;
  stat->timeConsumed = 0;
  stat->clientPacketsReceived = 0;
  stat->serverPacketsReceived = 0;
  stat->mostRecentServerPacketSequence = 0;
  stat->milliseconds = Sys_Milliseconds();
  stat->deltaMsec = stat->milliseconds - com_asyncStats[((_WORD)com_ticNumber - 1) & 0x3FF].milliseconds;
  Integer = idCVar::GetInteger(&com_asyncSound);
  if ( Integer == 1 )
  {
    Sys_EnterCriticalSection(0);
    soundSystem->AsyncUpdate(soundSystem, stat->milliseconds);
    Sys_LeaveCriticalSection(0);
  }
  else if ( Integer == 3 )
  {
    Sys_EnterCriticalSection(0);
    soundSystem->AsyncUpdateWrite(soundSystem, stat->milliseconds);
    Sys_LeaveCriticalSection(0);
  }
  ++com_ticNumber;
  stat->timeConsumed = Sys_Milliseconds() - stat->milliseconds;
}

// FUNC: public: virtual void __thiscall idCommonLocal::Async(void)
void __thiscall idCommonLocal::Async(idCommonLocal *this)
{
  int v1; // eax
  int v2; // [esp+0h] [ebp-18h]
  unsigned __int16 v3; // [esp+6h] [ebp-12h]
  int msec; // [esp+Ch] [ebp-Ch]
  float timescale; // [esp+10h] [ebp-8h]
  int ticMsec; // [esp+14h] [ebp-4h]

  if ( !this->com_shuttingDown )
  {
    msec = Sys_Milliseconds();
    if ( !lastTicMsec )
      lastTicMsec = msec - (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
    if ( idCVar::GetBool(&com_preciseTic) )
    {
      ticMsec = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
      timescale = idCVar::GetFloat(&com_timescale);
      if ( timescale != 1.0 )
      {
        v1 = v3;
        BYTE1(v1) = HIBYTE(v3) | 0xC;
        v2 = v1;
        ticMsec = (int)((double)ticMsec / timescale);
        if ( ticMsec < 1 )
          ticMsec = 1;
      }
      if ( timescale == 1.0
        && lastTicMsec + 10 * (*(int (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 40))(common.type, v2) < msec )
      {
        lastTicMsec = msec - 10 * (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type);
      }
      while ( ticMsec + lastTicMsec <= msec )
      {
        idCommonLocal::SingleAsyncTic(this);
        lastTicMsec += ticMsec;
      }
    }
    else
    {
      idCommonLocal::SingleAsyncTic(this);
    }
  }
}

// FUNC: private: virtual bool __thiscall rvToolsStub::IsParentWindowVisible(void)
char __thiscall rvToolsStub::IsParentWindowVisible(rvToolsStub *this)
{
  return 1;
}

// FUNC: private: virtual int __thiscall rvToolsStub::IsToolActive(int)
int __thiscall rvToolsStub::IsToolActive(rvToolsStub *this, int index)
{
  return 0;
}

// FUNC: private: virtual bool __thiscall rvToolsStub::MakeCurrent(struct HDC__ *)
bool __thiscall rvToolsStub::MakeCurrent(rvToolsStub *this, HDC__ *hDC)
{
  return 0;
}

// FUNC: private: virtual class idVec4 const * __thiscall rvToolsStub::ModViewGetBgrndColor(void)
const idVec4 *__thiscall rvToolsStub::ModViewGetBgrndColor(rvToolsStub *this)
{
  return 0;
}

// FUNC: private: virtual bool __thiscall rvToolsStub::MakeGameCurrent(void)
bool __thiscall rvToolsStub::MakeGameCurrent(rvToolsStub *this)
{
  return 0;
}

// FUNC: private: virtual void __thiscall rvToolsStub::FXEditorStopEffect(void)
void __thiscall rvToolsStub::FXEditorStopEffect(rvToolsStub *this)
{
  ;
}

// FUNC: private: virtual void __thiscall rvToolsStub::GESetStateKey(class idWindow *,char const *,char const *,bool)
void __thiscall rvToolsStub::GESetStateKey(
        rvToolsStub *this,
        idWindow *window,
        const char *key,
        const char *value,
        bool something)
{
  ;
}

// FUNC: private: virtual void __thiscall rvToolsStub::GEAddScript(class idWindow *,char const *,char const *)
void __thiscall rvToolsStub::GEAddScript(
        rvToolsStub *this,
        idInterpreter *interpreter,
        idProgram *program,
        int instructionPointer)
{
  ;
}

// FUNC: private: virtual void __thiscall rvToolsStub::Set2D(int,int)
void __thiscall rvToolsStub::Set2D(rvToolsStub *this, int optimize, srfTriangles_s *tri)
{
  ;
}

// FUNC: private: virtual bool __thiscall rvToolsStub::DmapSuperOptimizeOccluders(struct SOOData_s *,class idVec4 *,int *,int,class idPlane,class idVec3)
bool __thiscall rvToolsStub::DmapSuperOptimizeOccluders(
        rvToolsStub *this,
        SOOData_s *data,
        idVec4 *verts,
        int *indexes,
        int numIndexes,
        idPlane projectionPlane,
        idVec3 projectionOrigin)
{
  return 0;
}

// FUNC: private: virtual int __thiscall rvToolsStub::GetListenerArea(void)const
int __thiscall rvToolsStub::GetListenerArea(rvToolsStub *this)
{
  return -1;
}

// FUNC: private: virtual void __thiscall rvToolsStub::DmapOutputString(char const *)
void __thiscall rvToolsStub::DmapOutputString(rvToolsStub *this, const idCmdArgs *args)
{
  ;
}

// FUNC: private: virtual int __thiscall rvToolsStub::SetupPixelFormat(struct HDC__ *)
int __thiscall rvToolsStub::SetupPixelFormat(rvToolsStub *this, HDC__ *hDC)
{
  return -1;
}

// FUNC: public: void __thiscall idCommonLocal::SetMachineSpec(void)
void __thiscall idCommonLocal::SetMachineSpec(idCommonLocal *this)
{
  const char *v1; // [esp+1Ch] [ebp-20h]
  bool oldCard; // [esp+26h] [ebp-16h] BYREF
  bool nv10or20; // [esp+27h] [ebp-15h] BYREF
  int sysRam; // [esp+28h] [ebp-14h]
  long double ghz; // [esp+2Ch] [ebp-10h]
  int vidRam; // [esp+34h] [ebp-8h]
  cpuid_t cpu; // [esp+38h] [ebp-4h]

  cpu = Sys_GetProcessorId();
  ghz = Sys_ClockTicksPerSecond() * 9.999999717180685e-10;
  vidRam = Sys_GetVideoRam();
  sysRam = Sys_GetSystemRam();
  oldCard = 0;
  nv10or20 = 0;
  renderSystem->GetCardCaps(renderSystem, &oldCard, &nv10or20);
  if ( oldCard )
    v1 = "a less than optimal video architecture";
  else
    v1 = "an optimal video architecture";
  this->Printf(
    this,
    "Detected\n \t%.2f GHz CPU\n\t%i MB of System memory\n\t%i MB of Video memory on %s\n\n",
    ghz,
    sysRam,
    vidRam,
    v1);
  if ( (cpu & 0x20000) != 0 )
  {
    ghz = ghz * 1.600000023841858;
  }
  else if ( (cpu & 8) != 0 )
  {
    ghz = ghz * 1.149999976158142;
  }
  if ( ghz < 2.890000104904175 || vidRam < 300 || sysRam < 1000 || oldCard )
  {
    if ( ghz < 2.890000104904175 || vidRam < 160 || sysRam < 1000 || oldCard )
    {
      if ( ghz < 2.289999961853027 || vidRam < 160 || sysRam < 750 || oldCard )
      {
        this->Printf(this, "This system qualifies for Low quality.\n");
        idCVar::SetInteger(&com_machineSpec, 0);
      }
      else
      {
        this->Printf(this, "This system qualifies for Medium quality.\n");
        idCVar::SetInteger(&com_machineSpec, 1);
      }
    }
    else
    {
      this->Printf(this, "This system qualifies for High quality!\n");
      idCVar::SetInteger(&com_machineSpec, 2);
    }
  }
  else
  {
    this->Printf(this, "This system qualifies for Ultra quality!\n");
    idCVar::SetInteger(&com_machineSpec, 3);
  }
  idCVar::SetInteger(&com_videoRam, vidRam);
}

// FUNC: public: void __thiscall idCommonLocal::ShutdownGame(bool)
void __thiscall idCommonLocal::ShutdownGame(idCommonLocal *this, bool reloading)
{
  BOOL v2; // eax

  if ( soundSystem )
    soundSystem->StopAllSounds(soundSystem, -1);
  this->UnloadToolsDLL(this);
  idAsyncClient::Shutdown(&idAsyncNetwork::client);
  session->Shutdown(session);
  uiManager->Shutdown(uiManager);
  idAsyncNetwork::Shutdown();
  usercmdGen->Shutdown(usercmdGen);
  idEventLoop::Shutdown(eventLoop);
  if ( soundSystem )
    soundSystem->Shutdown(soundSystem);
  renderSystem->Shutdown(renderSystem);
  declManager->Shutdown(declManager);
  idCommonLocal::UnloadGameDLL(this);
  this->DumpWarnings(this);
  idCommonLocal::CloseLogFile(this);
  LOBYTE(v2) = reloading;
  fileSystem->Shutdown(fileSystem, v2);
}

// FUNC: public: static void __cdecl idCommonLocal::WriteConfiguration_f(class idCmdArgs const &)
void __cdecl idCommonLocal::WriteConfiguration_f()
{
  idCommonLocal::WriteConfiguration(&commonLocal);
}

// FUNC: public: void __thiscall rvLanguage::SetLanguage(class idStr &)
void __thiscall rvLanguage::SetLanguage(rvLanguage *this, idStr *lang)
{
  int len; // ebp
  int v4; // eax

  len = lang->len;
  v4 = lang->len + 1;
  if ( v4 > this->language.alloced )
    idStr::ReAllocate(&this->language, v4, 0);
  qmemcpy(this->language.data, lang->data, len);
  this->language.data[len] = 0;
  this->language.len = len;
}

// FUNC: Com_CreateCM_f
void __cdecl Com_CreateCM_f(idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // eax
  const char *v3; // eax
  const char *Name; // eax
  idMapFile *v5; // [esp+Ch] [ebp-A4h]
  idMapEntity **list; // [esp+28h] [ebp-88h]
  int i; // [esp+2Ch] [ebp-84h]
  idMapFile *v8; // [esp+54h] [ebp-5Ch]
  idCollisionModel *model; // [esp+5Ch] [ebp-54h]
  idStr fileName; // [esp+64h] [ebp-4Ch] BYREF
  idStr extension; // [esp+84h] [ebp-2Ch] BYREF
  int v12; // [esp+ACh] [ebp-4h]

  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  v12 = 1;
  extension.len = 0;
  extension.alloced = 20;
  extension.data = extension.baseBuffer;
  extension.baseBuffer[0] = 0;
  if ( idEditField::GetCursor(args) < 2 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "createCM <filename.map|.lwo>\n");
    LOBYTE(v12) = 0;
    idStr::FreeData(&extension);
    v12 = -1;
    idStr::FreeData(&fileName);
    return;
  }
  v1 = idCmdArgs::Argv(args, 1);
  idStr::operator=(&fileName, v1);
  idStr::ExtractFileExtension(&fileName, &extension);
  if ( idStr::Icmp(extension.data, "map") )
  {
    idCVar::SetBool(&com_makingBuild, 1);
    model = collisionModelManager->LoadModel(collisionModelManager, &entityFilter, fileName.data);
    if ( model )
      collisionModelManager->FreeModel(collisionModelManager, model);
    idCVar::SetBool(&com_makingBuild, 0);
    goto LABEL_28;
  }
  v8 = (idMapFile *)Memory::Allocate(0x54u);
  LOBYTE(v12) = 2;
  if ( v8 )
  {
    v8->entities.list = 0;
    v8->entities.granularity = 16;
    if ( v8->entities.list )
      Memory::Free(v8->entities.list);
    v8->entities.list = 0;
    v8->entities.num = 0;
    v8->entities.size = 0;
    LOBYTE(v12) = 3;
    v8->name.len = 0;
    v8->name.alloced = 20;
    v8->name.data = v8->name.baseBuffer;
    *v8->name.data = 0;
    LOBYTE(v12) = 4;
    v8->mExportEntities.list = 0;
    v8->mExportEntities.granularity = 16;
    if ( v8->mExportEntities.list )
      Memory::Free(v8->mExportEntities.list);
    v8->mExportEntities.list = 0;
    v8->mExportEntities.num = 0;
    v8->mExportEntities.size = 0;
    LOBYTE(v12) = 5;
    v8->version = 3;
    v8->fileTime = 0;
    v8->geometryCRC = 0;
    v8->entities.granularity = 256;
    list = v8->entities.list;
    v8->entities.size = 1024;
    if ( v8->entities.size < v8->entities.num )
      v8->entities.num = v8->entities.size;
    v8->entities.list = (idMapEntity **)Memory::Allocate(4 * v8->entities.size);
    for ( i = 0; i < v8->entities.num; ++i )
      v8->entities.list[i] = list[i];
    if ( list )
      Memory::Free(list);
    v8->hasPrimitiveData = 0;
    v8->mHasFuncGroups = 0;
    LOBYTE(v12) = 2;
    v5 = v8;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v12) = 1;
  v2 = idCmdArgs::Argv(args, 1);
  if ( idMapFile::Parse(v5, v2, 0, 0) )
  {
    idMapFile::Resolve(v5);
    collisionModelManager->LoadMap(collisionModelManager, v5, 1);
    Name = idMapFile::GetName(v5);
    collisionModelManager->FreeMap(collisionModelManager, Name);
    if ( v5 )
    {
      idMapFile::~idMapFile(v5);
      Memory::Free(v5);
    }
LABEL_28:
    LOBYTE(v12) = 0;
    idStr::FreeData(&extension);
    v12 = -1;
    idStr::FreeData(&fileName);
    return;
  }
  if ( v5 )
  {
    idMapFile::~idMapFile(v5);
    Memory::Free(v5);
  }
  v3 = idCmdArgs::Argv(args, 1);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
    common.type,
    "Couldn't load map file: '%s'",
    v3);
  LOBYTE(v12) = 0;
  idStr::FreeData(&extension);
  v12 = -1;
  idStr::FreeData(&fileName);
}

// FUNC: Com_EditDecls_f
void __cdecl Com_EditDecls_f(idCmdArgs *args)
{
  const char *v1; // eax
  char *key; // [esp+8h] [ebp-60h]
  idDict dict; // [esp+30h] [ebp-38h] BYREF
  int v4; // [esp+64h] [ebp-4h]

  dict.args.list = 0;
  dict.args.num = 0;
  dict.args.size = 0;
  v4 = 0;
  idHashIndex::Init(&dict.argHash, 1024, 1024);
  LOBYTE(v4) = 1;
  dict.args.granularity = 16;
  dict.argHash.granularity = 16;
  idHashIndex::Free(&dict.argHash);
  dict.argHash.hashSize = 128;
  dict.argHash.indexSize = 16;
  v4 = 2;
  if ( idEditField::GetCursor(args) > 1 )
  {
    key = (char *)idCmdArgs::Argv(args, 1);
    v1 = va("%i", 1);
    idDict::Set(&dict, key, v1);
  }
  (*(void (__thiscall **)(netadrtype_t, int, idDict *))(*(_DWORD *)common.type + 60))(common.type, 128, &dict);
  v4 = 4;
  idDict::Clear(&dict);
  LOBYTE(v4) = 3;
  idHashIndex::Free(&dict.argHash);
  v4 = -1;
  if ( dict.args.list )
    Memory::Free(dict.args.list);
}

// FUNC: PrintMemInfo_f
void __cdecl PrintMemInfo_f()
{
  idStr *v0; // [esp+54h] [ebp-38Ch]
  idStr *v1; // [esp+5Ch] [ebp-384h]
  idStr *v2; // [esp+64h] [ebp-37Ch]
  idStr *v3; // [esp+6Ch] [ebp-374h]
  idStr *v4; // [esp+74h] [ebp-36Ch]
  idStr *v5; // [esp+7Ch] [ebp-364h]
  idStr *v6; // [esp+84h] [ebp-35Ch]
  idStr *v7; // [esp+90h] [ebp-350h]
  idStr *v8; // [esp+98h] [ebp-348h]
  idStr *v9; // [esp+A0h] [ebp-340h]
  idStr *v10; // [esp+A8h] [ebp-338h]
  idStr *v11; // [esp+B0h] [ebp-330h]
  idStr *v12; // [esp+B8h] [ebp-328h]
  idStr *v13; // [esp+C0h] [ebp-320h]
  idStr *v14; // [esp+C8h] [ebp-318h]
  idStr *v15; // [esp+D0h] [ebp-310h]
  idStr *v16; // [esp+D8h] [ebp-308h]
  idStr *v17; // [esp+E0h] [ebp-300h]
  idStr *v18; // [esp+E8h] [ebp-2F8h]
  idStr *v19; // [esp+F0h] [ebp-2F0h]
  idStr v20; // [esp+F4h] [ebp-2ECh] BYREF
  idStr v21; // [esp+114h] [ebp-2CCh] BYREF
  idStr v22; // [esp+134h] [ebp-2ACh] BYREF
  idStr v23; // [esp+154h] [ebp-28Ch] BYREF
  idStr v24; // [esp+174h] [ebp-26Ch] BYREF
  idStr v25; // [esp+194h] [ebp-24Ch] BYREF
  idStr v26; // [esp+1B4h] [ebp-22Ch] BYREF
  idStr v27; // [esp+1D4h] [ebp-20Ch] BYREF
  idStr v28; // [esp+1F4h] [ebp-1ECh] BYREF
  idStr v29; // [esp+214h] [ebp-1CCh] BYREF
  idStr v30; // [esp+234h] [ebp-1ACh] BYREF
  idStr v31; // [esp+254h] [ebp-18Ch] BYREF
  idStr v32; // [esp+274h] [ebp-16Ch] BYREF
  idStr v33; // [esp+294h] [ebp-14Ch] BYREF
  idStr v34; // [esp+2B4h] [ebp-12Ch] BYREF
  idStr v35; // [esp+2D4h] [ebp-10Ch] BYREF
  idStr v36; // [esp+2F4h] [ebp-ECh] BYREF
  idStr v37; // [esp+314h] [ebp-CCh] BYREF
  idStr v38; // [esp+334h] [ebp-ACh] BYREF
  idStr result; // [esp+354h] [ebp-8Ch] BYREF
  MemInfo mi; // [esp+374h] [ebp-6Ch] BYREF
  idFile *f; // [esp+3D0h] [ebp-10h]
  int v42; // [esp+3DCh] [ebp-4h]

  MemInfo::MemInfo(&mi);
  v42 = 0;
  session->GetCurrentMapName(session, (idStr *)&mi);
  renderSystem->PrintMemInfo(renderSystem, &mi);
  soundSystem->PrintMemInfo(soundSystem, &mi);
  collisionModelManager->PrintMemInfo(collisionModelManager, &mi);
  gameEdit->PrintMemInfo(gameEdit, &mi);
  v19 = idStr::FormatNumber(&result, mi.imageAssetsCount);
  LOBYTE(v42) = 1;
  v18 = idStr::FormatNumber(&v38, mi.imageAssetsTotal);
  LOBYTE(v42) = 2;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " Used image memory: %s bytes in %s items\n",
    v18->data,
    v19->data);
  LOBYTE(v42) = 1;
  idStr::FreeData(&v38);
  LOBYTE(v42) = 0;
  idStr::FreeData(&result);
  mi.assetTotals += mi.imageAssetsTotal;
  v17 = idStr::FormatNumber(&v37, mi.modelAssetsCount);
  LOBYTE(v42) = 3;
  v16 = idStr::FormatNumber(&v36, mi.modelAssetsTotal);
  LOBYTE(v42) = 4;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " Used model memory: %s bytes in %s items\n",
    v16->data,
    v17->data);
  LOBYTE(v42) = 3;
  idStr::FreeData(&v36);
  LOBYTE(v42) = 0;
  idStr::FreeData(&v37);
  mi.assetTotals += mi.modelAssetsTotal;
  v15 = idStr::FormatNumber(&v35, mi.soundAssetsCount);
  LOBYTE(v42) = 5;
  v14 = idStr::FormatNumber(&v34, mi.soundAssetsTotal);
  LOBYTE(v42) = 6;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " Used sound memory: %s bytes in %s items\n",
    v14->data,
    v15->data);
  LOBYTE(v42) = 5;
  idStr::FreeData(&v34);
  LOBYTE(v42) = 0;
  idStr::FreeData(&v35);
  mi.assetTotals += mi.soundAssetsTotal;
  v13 = idStr::FormatNumber(&v33, mi.collAssetsCount);
  LOBYTE(v42) = 7;
  v12 = idStr::FormatNumber(&v32, mi.collAssetsTotal);
  LOBYTE(v42) = 8;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " Used coll memory : %s bytes in %s items\n",
    v12->data,
    v13->data);
  LOBYTE(v42) = 7;
  idStr::FreeData(&v32);
  LOBYTE(v42) = 0;
  idStr::FreeData(&v33);
  mi.assetTotals += mi.collAssetsTotal;
  v11 = idStr::FormatNumber(&v31, mi.aasAssetsCount);
  LOBYTE(v42) = 9;
  v10 = idStr::FormatNumber(&v30, mi.aasAssetsTotal);
  LOBYTE(v42) = 10;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " Used AAS memory  : %s bytes in %s items\n",
    v10->data,
    v11->data);
  LOBYTE(v42) = 9;
  idStr::FreeData(&v30);
  LOBYTE(v42) = 0;
  idStr::FreeData(&v31);
  mi.assetTotals += mi.aasAssetsTotal;
  v9 = idStr::FormatNumber(&v29, mi.animsAssetsCount);
  LOBYTE(v42) = 11;
  v8 = idStr::FormatNumber(&v28, mi.animsAssetsTotal);
  LOBYTE(v42) = 12;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " Used anims memory: %s bytes in %s items\n",
    v8->data,
    v9->data);
  LOBYTE(v42) = 11;
  idStr::FreeData(&v28);
  LOBYTE(v42) = 0;
  idStr::FreeData(&v29);
  mi.assetTotals += mi.animsAssetsTotal;
  v7 = idStr::FormatNumber(&v27, mi.assetTotals);
  LOBYTE(v42) = 13;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " Used asset memory: %s bytes\n",
    v7->data);
  LOBYTE(v42) = 0;
  idStr::FreeData(&v27);
  f = fileSystem->OpenFileAppend(fileSystem, "maps/printmeminfo.txt", 0, "fs_basepath");
  if ( f )
  {
    v6 = idStr::FormatNumber(&v26, mi.aasAssetsTotal);
    LOBYTE(v42) = 14;
    v5 = idStr::FormatNumber(&v25, mi.animsAssetsTotal);
    LOBYTE(v42) = 15;
    v4 = idStr::FormatNumber(&v24, mi.soundAssetsTotal);
    LOBYTE(v42) = 16;
    v3 = idStr::FormatNumber(&v23, mi.collAssetsTotal);
    LOBYTE(v42) = 17;
    v2 = idStr::FormatNumber(&v22, mi.modelAssetsTotal);
    LOBYTE(v42) = 18;
    v1 = idStr::FormatNumber(&v21, mi.imageAssetsTotal);
    LOBYTE(v42) = 19;
    v0 = idStr::FormatNumber(&v20, mi.assetTotals);
    LOBYTE(v42) = 20;
    f->Printf(
      f,
      "total(%s ) image(%s ) model(%s ) coll(%s ) sound(%s ) anims(%s ) aas(%s ): %s\n",
      v0->data,
      v1->data,
      v2->data,
      v3->data,
      v4->data,
      v5->data,
      v6->data,
      mi.filebase.data);
    LOBYTE(v42) = 19;
    idStr::FreeData(&v20);
    LOBYTE(v42) = 18;
    idStr::FreeData(&v21);
    LOBYTE(v42) = 17;
    idStr::FreeData(&v22);
    LOBYTE(v42) = 16;
    idStr::FreeData(&v23);
    LOBYTE(v42) = 15;
    idStr::FreeData(&v24);
    LOBYTE(v42) = 14;
    idStr::FreeData(&v25);
    LOBYTE(v42) = 0;
    idStr::FreeData(&v26);
    fileSystem->CloseFile(fileSystem, f);
    v42 = -1;
    idStr::FreeData(&mi.filebase);
  }
  else
  {
    v42 = -1;
    idStr::FreeData(&mi.filebase);
  }
}

// FUNC: void __cdecl Com_SetMachineSpec_f(class idCmdArgs const &)
void __cdecl Com_SetMachineSpec_f()
{
  idCommonLocal::SetMachineSpec(&commonLocal);
}

// FUNC: public: virtual void __thiscall idCommonLocal::ClearWarnings(char const *)
void __thiscall idCommonLocal::ClearWarnings(idCommonLocal *this, char *reason)
{
  idStr::operator=(&this->warningCaption, reason);
  if ( this->warningList.list )
    idStr::`vector deleting destructor'(this->warningList.list, 3);
  this->warningList.list = 0;
  this->warningList.num = 0;
  this->warningList.size = 0;
}

// FUNC: public: void __thiscall idCommonLocal::FilterLangList(class idList<class idStr> *,class idStr)
void __thiscall idCommonLocal::FilterLangList(idCommonLocal *this, idList<idStr> *list, idStr lang)
{
  idStr *v3; // [esp+14h] [ebp-B4h]
  idStr *v4; // [esp+18h] [ebp-B0h]
  unsigned int v5; // [esp+20h] [ebp-A8h]
  int j; // [esp+24h] [ebp-A4h]
  idStr *v7; // [esp+30h] [ebp-98h]
  unsigned int v8; // [esp+38h] [ebp-90h]
  idStr *v9; // [esp+3Ch] [ebp-8Ch]
  unsigned int v10; // [esp+44h] [ebp-84h]
  idStr *v11; // [esp+48h] [ebp-80h]
  unsigned int len; // [esp+50h] [ebp-78h]
  idStr v13; // [esp+58h] [ebp-70h] BYREF
  idStr result; // [esp+78h] [ebp-50h] BYREF
  int i; // [esp+98h] [ebp-30h]
  idStr temp; // [esp+9Ch] [ebp-2Ch] BYREF
  int v17; // [esp+C4h] [ebp-4h]

  v17 = 1;
  temp.len = 0;
  temp.alloced = 20;
  temp.data = temp.baseBuffer;
  temp.baseBuffer[0] = 0;
  for ( i = 0; i < list->num; ++i )
  {
    v11 = &list->list[i];
    len = v11->len;
    if ( v11->len + 1 > temp.alloced )
      idStr::ReAllocate(&temp, v11->len + 1, 0);
    qmemcpy(temp.data, v11->data, len);
    temp.data[len] = 0;
    temp.len = len;
    v9 = idStr::Right(&temp, &result, len - 8);
    LOBYTE(v17) = 2;
    v10 = v9->len;
    if ( v9->len + 1 > temp.alloced )
      idStr::ReAllocate(&temp, v9->len + 1, 0);
    qmemcpy(temp.data, v9->data, v10);
    temp.data[v10] = 0;
    temp.len = v10;
    LOBYTE(v17) = 1;
    idStr::FreeData(&result);
    v7 = idStr::Left(&temp, &v13, lang.len);
    LOBYTE(v17) = 3;
    v8 = v7->len;
    if ( v7->len + 1 > temp.alloced )
      idStr::ReAllocate(&temp, v7->len + 1, 0);
    qmemcpy(temp.data, v7->data, v8);
    temp.data[v8] = 0;
    temp.len = v8;
    LOBYTE(v17) = 1;
    idStr::FreeData(&v13);
    if ( idStr::Icmp(temp.data, lang.data) )
    {
      if ( i >= 0 && i < list->num )
      {
        --list->num;
        for ( j = i; j < list->num; ++j )
        {
          v4 = &list->list[j + 1];
          v3 = &list->list[j];
          v5 = v4->len;
          if ( v4->len + 1 > v3->alloced )
            idStr::ReAllocate(v3, v4->len + 1, 0);
          qmemcpy(v3->data, v4->data, v5);
          v3->data[v5] = 0;
          v3->len = v5;
        }
      }
      --i;
    }
  }
  LOBYTE(v17) = 0;
  idStr::FreeData(&temp);
  v17 = -1;
  idStr::FreeData(&lang);
}

// FUNC: public: virtual void __thiscall idCommonLocal::Shutdown(void)
void __thiscall idCommonLocal::Shutdown(idCommonLocal *this)
{
  rvLanguage *v2; // [esp+14h] [ebp-14h]
  idStr *list; // [esp+20h] [ebp-8h]

  if ( !this->com_shuttingDown )
  {
    this->com_shuttingDown = 1;
    (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 36))(*(_DWORD *)common.ip);
    idCommonLocal::ApplyVideoSettings(this);
    idAsyncClient::Shutdown(&idAsyncNetwork::client);
    idCommonLocal::ShutdownGame(this, 0);
    PbShutdown();
    Sys_Shutdown();
    console->Shutdown(console);
    idKeyInput::Shutdown();
    cvarSystem->Shutdown(cvarSystem);
    cmdSystem->Shutdown(cmdSystem);
    this->ClearWarnings(this, "Quake4 shutdown");
    idStr::FreeData(&this->warningCaption);
    this->warningCaption.len = 0;
    this->warningCaption.alloced = 20;
    this->warningCaption.data = this->warningCaption.baseBuffer;
    *this->warningCaption.data = 0;
    if ( this->errorList.list )
    {
      list = this->errorList.list;
      if ( list )
        idStr::`vector deleting destructor'(list, 3);
    }
    this->errorList.list = 0;
    this->errorList.num = 0;
    this->errorList.size = 0;
    if ( this->languages.list )
    {
      v2 = this->languages.list;
      if ( v2 )
        rvLanguage::`vector deleting destructor'(v2, 3);
    }
    this->languages.list = 0;
    this->languages.num = 0;
    this->languages.size = 0;
    Mem_EnableLeakTest("engine");
    idLib::ShutDown();
  }
}

// FUNC: public: __thiscall idCommonLocal::idCommonLocal(void)
void __thiscall idCommonLocal::idCommonLocal(idCommonLocal *this)
{
  char *baseBuffer; // ecx

  this->__vftable = (idCommonLocal_vtbl *)&idCommonLocal::`vftable';
  baseBuffer = this->warningCaption.baseBuffer;
  this->warningCaption.len = 0;
  this->warningCaption.alloced = 20;
  this->warningCaption.data = baseBuffer;
  *baseBuffer = 0;
  this->warningList.granularity = 16;
  this->warningList.list = 0;
  this->warningList.num = 0;
  this->warningList.size = 0;
  this->errorList.granularity = 16;
  this->errorList.list = 0;
  this->errorList.num = 0;
  this->errorList.size = 0;
  this->languages.granularity = 16;
  this->languages.list = 0;
  this->languages.num = 0;
  this->languages.size = 0;
  this->com_fullyInitialized = 0;
  this->com_refreshOnPrint = 0;
  this->com_errorEntered = 0;
  this->com_shuttingDown = 0;
  this->logFile = 0;
  this->errorMessage[0] = 0;
  this->rd_buffer = 0;
  this->rd_buffersize = 0;
  this->rd_flush = 0;
  this->toolsActive = 0;
  this->toolsDLL = 0;
  this->editorActive = 0;
  this->languageDictIndex = 0;
  this->gameDLL = 0;
  this->desiredMachineSpec = -1;
  memset(this->warningCount, 0, sizeof(this->warningCount));
  this->com_renderableGameFrame = 1;
}

// FUNC: public: virtual int __thiscall idCommonLocal::GetFrameTime(void)const
unsigned int __thiscall idCommonLocal::GetFrameTime(idCommonLocal *this)
{
  return com_frameTime;
}

// FUNC: public: virtual bool __thiscall idUserInterfaceLocal::IsUniqued(void)const
bool __thiscall idUserInterfaceLocal::IsUniqued(idCommonLocal *this)
{
  return this->com_renderableGameFrame;
}

// FUNC: public: virtual void __thiscall idCommonLocal::SetRenderableGameFrame(bool)
void __thiscall idCommonLocal::SetRenderableGameFrame(idCommonLocal *this, bool in)
{
  this->com_renderableGameFrame = in;
}

// FUNC: public: virtual char const * __thiscall idCommonLocal::GetErrorMessage(void)const
char *__thiscall idCommonLocal::GetErrorMessage(idCommonLocal *this)
{
  return this->errorMessage;
}

// FUNC: public: virtual bool __thiscall idCommonLocal::IsToolActive(void)const
bool __thiscall idCommonLocal::IsToolActive(idCommonLocal *this)
{
  return this->editorActive;
}

// FUNC: public: virtual int __thiscall idCommonLocal::GetNumLanguages(void)const
int __thiscall idCommonLocal::GetNumLanguages(idCommonLocal *this)
{
  return this->languages.num;
}

// FUNC: public: virtual int __thiscall idCommonLocal::GetNumLocalizedStrings(void)const
int __thiscall idCommonLocal::GetNumLocalizedStrings(idCommonLocal *this)
{
  return idLangDict::GetNumKeyVals(&this->languages.list->strings);
}

// FUNC: public: virtual void __cdecl idCommonLocal::Warning(char const *,...)
// bad sp value at call has been detected, the output may be wrong!
void __usercall idCommonLocal::Warning(int a1@<edi>, int a2@<esi>, idCommonLocal *this, char *fmt, ...)
{
  void *v4; // esp
  idStr *v5; // [esp+4h] [ebp-110Ch]
  idStr *v6; // [esp+10h] [ebp-1100h]
  char v7; // [esp+1Bh] [ebp-10F5h]
  char *data; // [esp+20h] [ebp-10F0h]
  char *p_dest; // [esp+24h] [ebp-10ECh]
  _BYTE *v10; // [esp+34h] [ebp-10DCh]
  idList<idStr> *p_warningList; // [esp+38h] [ebp-10D8h]
  idStr *v12; // [esp+3Ch] [ebp-10D4h]
  int v13; // [esp+44h] [ebp-10CCh]
  int v14; // [esp+48h] [ebp-10C8h]
  idStr *v15; // [esp+4Ch] [ebp-10C4h]
  unsigned int v16; // [esp+58h] [ebp-10B8h]
  idStr *v17; // [esp+60h] [ebp-10B0h]
  int *v18; // [esp+6Ch] [ebp-10A4h]
  int size; // [esp+74h] [ebp-109Ch]
  idStr *v20; // [esp+78h] [ebp-1098h]
  int k; // [esp+7Ch] [ebp-1094h]
  int granularity; // [esp+80h] [ebp-1090h]
  idStr *v23; // [esp+84h] [ebp-108Ch]
  unsigned int len; // [esp+90h] [ebp-1080h]
  idStr *v25; // [esp+98h] [ebp-1078h]
  int *ptr; // [esp+A4h] [ebp-106Ch]
  int count; // [esp+ACh] [ebp-1064h]
  idStr *list; // [esp+B0h] [ebp-1060h]
  int j; // [esp+B4h] [ebp-105Ch]
  int v30; // [esp+B8h] [ebp-1058h]
  int i; // [esp+C0h] [ebp-1050h]
  int v32; // [esp+C4h] [ebp-104Ch]
  idStr v33; // [esp+D4h] [ebp-103Ch] BYREF
  int v34; // [esp+F4h] [ebp-101Ch]
  char *argptr; // [esp+F8h] [ebp-1018h]
  char dest; // [esp+FCh] [ebp-1014h] BYREF
  _BYTE v37[4102]; // [esp+FDh] [ebp-1013h] BYREF
  char v38; // [esp+1103h] [ebp-Dh]
  int v39; // [esp+110Ch] [ebp-4h]
  va_list va; // [esp+1120h] [ebp+10h] BYREF

  va_start(va, fmt);
  v4 = alloca(4356);
  idStr::vsnPrintf(&dest, 4096, fmt, va);
  argptr = 0;
  v37[4094] = 0;
  v38 = 0;
  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t, int, int))(*(_DWORD *)common.type + 96))(common.type, a1, a2) )
  {
    v38 = 1;
  }
  else if ( this->warningList.num < 256 )
  {
    v33.len = 0;
    v33.alloced = 20;
    v33.data = v33.baseBuffer;
    v33.baseBuffer[0] = 0;
    if ( &dest )
    {
      v10 = &v37[strlen(&dest)];
      if ( v10 - v37 + 1 > v33.alloced )
        idStr::ReAllocate(&v33, v10 - v37 + 1, 1);
      p_dest = &dest;
      data = v33.data;
      do
      {
        v7 = *p_dest;
        *data++ = *p_dest++;
      }
      while ( v7 );
      v33.len = v10 - v37;
    }
    v39 = 0;
    p_warningList = &this->warningList;
    for ( i = 0; i < p_warningList->num; ++i )
    {
      if ( !idStr::Cmp(this->warningList.list[i].data, v33.data) )
      {
        v32 = i;
        goto LABEL_16;
      }
    }
    v32 = -1;
LABEL_16:
    if ( v32 < 0 )
    {
      if ( !this->warningList.list )
      {
        granularity = this->warningList.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->warningList.size )
          {
            list = this->warningList.list;
            this->warningList.size = granularity;
            if ( this->warningList.size < this->warningList.num )
              this->warningList.num = this->warningList.size;
            count = this->warningList.size;
            ptr = (int *)Memory::Allocate(32 * count + 4);
            LOBYTE(v39) = 1;
            if ( ptr )
            {
              *ptr = count;
              `eh vector constructor iterator'(
                ptr + 1,
                0x20u,
                count,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              v6 = (idStr *)(ptr + 1);
            }
            else
            {
              v6 = 0;
            }
            LOBYTE(v39) = 0;
            this->warningList.list = v6;
            for ( j = 0; j < p_warningList->num; ++j )
            {
              v23 = &this->warningList.list[j];
              len = list[j].len;
              if ( (signed int)(len + 1) > v23->alloced )
                idStr::ReAllocate(v23, len + 1, 0);
              qmemcpy(v23->data, list[j].data, len);
              v23->data[len] = 0;
              v23->len = len;
            }
            if ( list )
              idStr::`vector deleting destructor'(list, 3);
          }
        }
        else
        {
          if ( this->warningList.list )
          {
            v25 = this->warningList.list;
            if ( v25 )
              idStr::`vector deleting destructor'(v25, 3);
          }
          this->warningList.list = 0;
          p_warningList->num = 0;
          this->warningList.size = 0;
        }
      }
      if ( this->warningList.num == this->warningList.size )
      {
        if ( !this->warningList.granularity )
          this->warningList.granularity = 16;
        v30 = this->warningList.granularity + this->warningList.size;
        v14 = v30 - v30 % this->warningList.granularity;
        if ( v14 > 0 )
        {
          if ( v14 != this->warningList.size )
          {
            v20 = this->warningList.list;
            this->warningList.size = v14;
            if ( this->warningList.size < this->warningList.num )
              this->warningList.num = this->warningList.size;
            size = this->warningList.size;
            v18 = (int *)Memory::Allocate(32 * size + 4);
            LOBYTE(v39) = 2;
            if ( v18 )
            {
              *v18 = size;
              `eh vector constructor iterator'(
                v18 + 1,
                0x20u,
                size,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              v5 = (idStr *)(v18 + 1);
            }
            else
            {
              v5 = 0;
            }
            LOBYTE(v39) = 0;
            this->warningList.list = v5;
            for ( k = 0; k < p_warningList->num; ++k )
            {
              v15 = &this->warningList.list[k];
              v16 = v20[k].len;
              if ( (signed int)(v16 + 1) > v15->alloced )
                idStr::ReAllocate(v15, v16 + 1, 0);
              qmemcpy(v15->data, v20[k].data, v16);
              v15->data[v16] = 0;
              v15->len = v16;
            }
            if ( v20 )
              idStr::`vector deleting destructor'(v20, 3);
          }
        }
        else
        {
          if ( this->warningList.list )
          {
            v17 = this->warningList.list;
            if ( v17 )
              idStr::`vector deleting destructor'(v17, 3);
          }
          this->warningList.list = 0;
          p_warningList->num = 0;
          this->warningList.size = 0;
        }
      }
      v12 = &this->warningList.list[this->warningList.num];
      v13 = v33.len;
      if ( v33.len + 1 > v12->alloced )
        idStr::ReAllocate(v12, v33.len + 1, 0);
      qmemcpy(v12->data, v33.data, v13);
      v12->data[v13] = 0;
      v12->len = v13;
      v32 = p_warningList->num++;
    }
    v34 = v32;
    v39 = -1;
    idStr::FreeData(&v33);
    if ( !idCVar::GetBool(&com_uniqueWarnings) || idCVar::GetBool(&com_uniqueWarnings) && !this->warningCount[v34] )
      v38 = 1;
    if ( this->warningCount[v34] < 1000 )
      ++this->warningCount[v34];
  }
  if ( v38 )
    this->Printf(this, "^3WARNING: ^1%s\n", &dest);
}

// FUNC: public: virtual void __thiscall idCommonLocal::PrintWarnings(void)
void __thiscall idCommonLocal::PrintWarnings(idCommonLocal *this)
{
  int i; // [esp+20h] [ebp-4h]

  if ( this->warningList.num )
  {
    idList<idStr>::Sort(&this->warningList, idListSortCompare<idStr>);
    this->Printf(this, "----------------- Warnings ------------------\n");
    this->Printf(this, "during %s...\n", this->warningCaption.data);
    for ( i = 0; i < this->warningList.num; ++i )
      this->Printf(this, "^3WARNING: ^1%s\n", this->warningList.list[i].data);
    if ( this->warningList.num )
    {
      if ( this->warningList.num < 256 )
        this->Printf(this, "%d warnings\n", this->warningList.num);
      else
        this->Printf(this, "more than %d warnings\n", 256);
    }
  }
}

// FUNC: private: virtual void __thiscall idCommonLocal::DumpWarnings(void)
void __thiscall idCommonLocal::DumpWarnings(idCommonLocal *this)
{
  char *v1; // eax
  const char *v2; // eax
  idStr *v3; // [esp+10h] [ebp-2C0h]
  idStr *v4; // [esp+1Ch] [ebp-2B4h]
  idStr *v5; // [esp+30h] [ebp-2A0h]
  idStr *v6; // [esp+3Ch] [ebp-294h]
  idStr *v8; // [esp+54h] [ebp-27Ch]
  int nn; // [esp+58h] [ebp-278h]
  idList<idStr> *p_errorList; // [esp+64h] [ebp-26Ch]
  idStr *v11; // [esp+7Ch] [ebp-254h]
  idStr *v12; // [esp+9Ch] [ebp-234h]
  int v13; // [esp+A0h] [ebp-230h]
  unsigned int v14; // [esp+A8h] [ebp-228h]
  idStr *v15; // [esp+B0h] [ebp-220h]
  unsigned int v16; // [esp+BCh] [ebp-214h]
  int *v17; // [esp+D0h] [ebp-200h]
  idStr *v18; // [esp+DCh] [ebp-1F4h]
  int kk; // [esp+E0h] [ebp-1F0h]
  int v20; // [esp+E4h] [ebp-1ECh]
  int v21; // [esp+E8h] [ebp-1E8h]
  int *v22; // [esp+10Ch] [ebp-1C4h]
  unsigned int v23; // [esp+124h] [ebp-1ACh]
  _DWORD *v24; // [esp+154h] [ebp-17Ch]
  int v25; // [esp+158h] [ebp-178h]
  int v26; // [esp+15Ch] [ebp-174h]
  int v27; // [esp+160h] [ebp-170h]
  idStr *v28; // [esp+164h] [ebp-16Ch]
  int jj; // [esp+168h] [ebp-168h]
  int mm; // [esp+168h] [ebp-168h]
  idStr *v31; // [esp+178h] [ebp-158h]
  int ii; // [esp+17Ch] [ebp-154h]
  idList<idStr> *p_warningList; // [esp+188h] [ebp-148h]
  idStr *list; // [esp+1A0h] [ebp-130h]
  idStr *v35; // [esp+1C0h] [ebp-110h]
  int v36; // [esp+1C4h] [ebp-10Ch]
  unsigned int v37; // [esp+1CCh] [ebp-104h]
  idStr *v38; // [esp+1D4h] [ebp-FCh]
  unsigned int len; // [esp+1E0h] [ebp-F0h]
  int *v40; // [esp+1F4h] [ebp-DCh]
  idStr *v41; // [esp+200h] [ebp-D0h]
  int m; // [esp+204h] [ebp-CCh]
  int v43; // [esp+208h] [ebp-C8h]
  int v44; // [esp+20Ch] [ebp-C4h]
  idStr *v45; // [esp+210h] [ebp-C0h]
  unsigned int v46; // [esp+21Ch] [ebp-B4h]
  int *v47; // [esp+230h] [ebp-A0h]
  int k; // [esp+240h] [ebp-90h]
  unsigned int num; // [esp+248h] [ebp-88h]
  _DWORD *base; // [esp+278h] [ebp-58h]
  int v51; // [esp+27Ch] [ebp-54h]
  int v52; // [esp+27Ch] [ebp-54h]
  int v53; // [esp+280h] [ebp-50h]
  int granularity; // [esp+284h] [ebp-4Ch]
  idStr *v55; // [esp+288h] [ebp-48h]
  int j; // [esp+28Ch] [ebp-44h]
  int n; // [esp+28Ch] [ebp-44h]
  idStr osPath; // [esp+298h] [ebp-38h] BYREF
  idFile *warningFile; // [esp+2B8h] [ebp-18h]
  int i; // [esp+2BCh] [ebp-14h]
  int wNum; // [esp+2C0h] [ebp-10h]
  int v62; // [esp+2CCh] [ebp-4h]

  wNum = 0;
  if ( this->warningList.num )
  {
    warningFile = fileSystem->OpenFileWrite(fileSystem, "warnings.txt", "fs_savepath", 0);
    if ( warningFile )
    {
      warningFile->Printf(warningFile, "----------------- Warnings ------------------\n\n");
      warningFile->Printf(warningFile, "during %s...\n", this->warningCaption.data);
      p_warningList = &this->warningList;
      if ( this->warningList.num )
      {
        v55 = 0;
        v51 = 0;
        v53 = 0;
        v62 = 1;
        num = p_warningList->num;
        if ( p_warningList->num > 0 )
          base = Memory::Allocate(4 * num);
        else
          base = 0;
        for ( j = 0; j < p_warningList->num; ++j )
          base[j] = &this->warningList.list[j];
        if ( base )
          qsort(base, num, 4u, (int (__cdecl *)(const void *, const void *))idListSortCompare<idPoolStr const *>);
        v44 = p_warningList->num;
        if ( p_warningList->num > 0 )
        {
          if ( v44 )
          {
            v53 = p_warningList->num;
            if ( v44 < 0 )
              v51 = p_warningList->num;
            v47 = (int *)Memory::Allocate(32 * v53 + 4);
            LOBYTE(v62) = 2;
            if ( v47 )
            {
              *v47 = v53;
              `eh vector constructor iterator'(
                v47 + 1,
                0x20u,
                v53,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              v6 = (idStr *)(v47 + 1);
            }
            else
            {
              v6 = 0;
            }
            LOBYTE(v62) = 1;
            v55 = v6;
            for ( k = 0; k < v51; ++k )
            {
              v45 = &v6[k];
              v46 = *(_DWORD *)(32 * k);
              if ( (signed int)(v46 + 1) > v45->alloced )
                idStr::ReAllocate(v45, v46 + 1, 0);
              qmemcpy(v45->data, *(const void **)(32 * k + 4), v46);
              v45->data[v46] = 0;
              v45->len = v46;
            }
          }
        }
        else
        {
          v55 = 0;
          v53 = 0;
        }
        v52 = v44;
        granularity = this->warningList.granularity;
        if ( v55 )
        {
          v43 = v44 + granularity - 1 - (v44 + granularity - 1) % granularity;
          if ( v43 != v53 )
          {
            if ( v43 > 0 )
            {
              if ( v43 != v53 )
              {
                v41 = v55;
                v53 = v44 + granularity - 1 - (v44 + granularity - 1) % granularity;
                if ( v43 < v44 )
                  v52 = v44 + granularity - 1 - (v44 + granularity - 1) % granularity;
                v40 = (int *)Memory::Allocate(32 * v53 + 4);
                LOBYTE(v62) = 3;
                if ( v40 )
                {
                  *v40 = v53;
                  `eh vector constructor iterator'(
                    v40 + 1,
                    0x20u,
                    v53,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  v5 = (idStr *)(v40 + 1);
                }
                else
                {
                  v5 = 0;
                }
                LOBYTE(v62) = 1;
                v55 = v5;
                for ( m = 0; m < v52; ++m )
                {
                  v38 = &v5[m];
                  len = v41[m].len;
                  if ( (signed int)(len + 1) > v38->alloced )
                    idStr::ReAllocate(v38, len + 1, 0);
                  qmemcpy(v38->data, v41[m].data, len);
                  v38->data[len] = 0;
                  v38->len = len;
                }
                idStr::`vector deleting destructor'(v41, 3);
              }
            }
            else
            {
              idStr::`vector deleting destructor'(v55, 3);
              v55 = 0;
              v52 = 0;
              v53 = 0;
            }
          }
        }
        for ( n = 0; n < v52; ++n )
        {
          v36 = base[n];
          v35 = &v55[n];
          v37 = *(_DWORD *)v36;
          if ( *(_DWORD *)v36 + 1 > v35->alloced )
            idStr::ReAllocate(v35, *(_DWORD *)v36 + 1, 0);
          qmemcpy(v35->data, *(const void **)(v36 + 4), v37);
          v35->data[v37] = 0;
          v35->len = v37;
        }
        p_warningList->num = v52;
        this->warningList.size = v53;
        this->warningList.granularity = granularity;
        list = this->warningList.list;
        this->warningList.list = v55;
        LOBYTE(v62) = 0;
        if ( base )
          Memory::Free(base);
        v62 = -1;
        if ( list )
          idStr::`vector deleting destructor'(list, 3);
      }
      for ( i = 0; i < this->warningList.num; ++i )
      {
        v31 = &this->warningList.list[i];
        idStr::RemoveEscapes(v31->data, 30);
        for ( ii = 0; v31->data[ii]; ++ii )
          ;
        v31->len = ii;
        wNum = this->warningCount[i];
        warningFile->Printf(warningFile, "WARNING: %s  (%d times)\n", this->warningList.list[i].data, wNum);
      }
      if ( this->warningList.num < 256 )
        warningFile->Printf(warningFile, "\n%d warnings.\n", this->warningList.num);
      else
        warningFile->Printf(warningFile, "\nmore than %d warnings!\n", 256);
      warningFile->Printf(warningFile, "\n\n------------------ Errors ------------------\n\n");
      p_errorList = &this->errorList;
      if ( this->errorList.num )
      {
        v28 = 0;
        v26 = 0;
        v62 = 5;
        v23 = p_errorList->num;
        if ( p_errorList->num > 0 )
          v24 = Memory::Allocate(4 * v23);
        else
          v24 = 0;
        for ( jj = 0; jj < p_errorList->num; ++jj )
          v24[jj] = &this->errorList.list[jj];
        if ( v24 )
          qsort(v24, v23, 4u, (int (__cdecl *)(const void *, const void *))idListSortCompare<idPoolStr const *>);
        v21 = p_errorList->num;
        if ( p_errorList->num > 0 )
        {
          if ( v21 )
          {
            v26 = p_errorList->num;
            v22 = (int *)Memory::Allocate(32 * v21 + 4);
            LOBYTE(v62) = 6;
            if ( v22 )
            {
              *v22 = v21;
              `eh vector constructor iterator'(
                v22 + 1,
                0x20u,
                v21,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              v4 = (idStr *)(v22 + 1);
            }
            else
            {
              v4 = 0;
            }
            LOBYTE(v62) = 5;
            v28 = v4;
          }
        }
        else
        {
          v28 = 0;
          v26 = 0;
        }
        v25 = v21;
        v27 = this->errorList.granularity;
        if ( v28 )
        {
          v20 = v21 + v27 - 1 - (v21 + v27 - 1) % v27;
          if ( v20 != v26 )
          {
            if ( v20 > 0 )
            {
              if ( v20 != v26 )
              {
                v18 = v28;
                v26 = v21 + v27 - 1 - (v21 + v27 - 1) % v27;
                if ( v20 < v21 )
                  v25 = v21 + v27 - 1 - (v21 + v27 - 1) % v27;
                v17 = (int *)Memory::Allocate(32 * v20 + 4);
                LOBYTE(v62) = 7;
                if ( v17 )
                {
                  *v17 = v20;
                  `eh vector constructor iterator'(
                    v17 + 1,
                    0x20u,
                    v20,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  v3 = (idStr *)(v17 + 1);
                }
                else
                {
                  v3 = 0;
                }
                LOBYTE(v62) = 5;
                v28 = v3;
                for ( kk = 0; kk < v25; ++kk )
                {
                  v15 = &v3[kk];
                  v16 = v18[kk].len;
                  if ( (signed int)(v16 + 1) > v15->alloced )
                    idStr::ReAllocate(v15, v16 + 1, 0);
                  qmemcpy(v15->data, v18[kk].data, v16);
                  v15->data[v16] = 0;
                  v15->len = v16;
                }
                idStr::`vector deleting destructor'(v18, 3);
              }
            }
            else
            {
              idStr::`vector deleting destructor'(v28, 3);
              v28 = 0;
              v25 = 0;
              v26 = 0;
            }
          }
        }
        for ( mm = 0; mm < v25; ++mm )
        {
          v13 = v24[mm];
          v12 = &v28[mm];
          v14 = *(_DWORD *)v13;
          if ( *(_DWORD *)v13 + 1 > v12->alloced )
            idStr::ReAllocate(v12, *(_DWORD *)v13 + 1, 0);
          qmemcpy(v12->data, *(const void **)(v13 + 4), v14);
          v12->data[v14] = 0;
          v12->len = v14;
        }
        p_errorList->num = v25;
        this->errorList.size = v26;
        this->errorList.granularity = v27;
        v11 = this->errorList.list;
        this->errorList.list = v28;
        LOBYTE(v62) = 4;
        if ( v24 )
          Memory::Free(v24);
        v62 = -1;
        if ( v11 )
          idStr::`vector deleting destructor'(v11, 3);
      }
      for ( i = 0; i < this->errorList.num; ++i )
      {
        v8 = &this->errorList.list[i];
        idStr::RemoveEscapes(v8->data, 30);
        for ( nn = 0; v8->data[nn]; ++nn )
          ;
        v8->len = nn;
        warningFile->Printf(warningFile, "ERROR: %s", this->errorList.list[i].data);
      }
      warningFile->ForceFlush(warningFile);
      fileSystem->CloseFile(fileSystem, warningFile);
      if ( !cvarSystem->GetCVarBool(cvarSystem, "com_makingBuild")
        && !cvarSystem->GetCVarBool(cvarSystem, "com_updateLoadSize") )
      {
        osPath.len = 0;
        osPath.alloced = 20;
        osPath.data = osPath.baseBuffer;
        osPath.baseBuffer[0] = 0;
        v62 = 8;
        v1 = (char *)fileSystem->RelativePathToOSPath(fileSystem, "warnings.txt", "fs_savepath");
        idStr::operator=(&osPath, v1);
        v2 = va("Notepad.exe %s", osPath.data);
        WinExec(v2, 5u);
        v62 = -1;
        idStr::FreeData(&osPath);
      }
    }
  }
}

// FUNC: public: virtual void __cdecl idCommonLocal::Error(char const *,...)
// bad sp value at call has been detected, the output may be wrong!
// positive sp value has been detected, the output may be wrong!
void __usercall __noreturn idCommonLocal::Error(int a1@<edi>, int a2@<esi>, idCommonLocal *this, char *fmt, ...)
{
  void *v4; // esp
  char v5; // cl
  const void *v6; // eax
  const void *v7; // eax
  const void *v8; // eax
  idStr *v9; // [esp+4h] [ebp-3108h]
  idStr *v10; // [esp+10h] [ebp-30FCh]
  char *data; // [esp+20h] [ebp-30ECh]
  char *errorMessage; // [esp+24h] [ebp-30E8h]
  char *v13; // [esp+34h] [ebp-30D8h]
  idList<idStr> *p_errorList; // [esp+38h] [ebp-30D4h]
  idStr *v15; // [esp+3Ch] [ebp-30D0h]
  int v16; // [esp+44h] [ebp-30C8h]
  int v17; // [esp+48h] [ebp-30C4h]
  idStr *v18; // [esp+4Ch] [ebp-30C0h]
  unsigned int v19; // [esp+58h] [ebp-30B4h]
  int *v20; // [esp+6Ch] [ebp-30A0h]
  int size; // [esp+74h] [ebp-3098h]
  idStr *v22; // [esp+78h] [ebp-3094h]
  int k; // [esp+7Ch] [ebp-3090h]
  int granularity; // [esp+80h] [ebp-308Ch]
  idStr *v25; // [esp+84h] [ebp-3088h]
  unsigned int len; // [esp+90h] [ebp-307Ch]
  int *ptr; // [esp+A4h] [ebp-3068h]
  int count; // [esp+ACh] [ebp-3060h]
  idStr *list; // [esp+B0h] [ebp-305Ch]
  int j; // [esp+B4h] [ebp-3058h]
  int v31; // [esp+B8h] [ebp-3054h]
  int i; // [esp+C0h] [ebp-304Ch]
  int v33; // [esp+C4h] [ebp-3048h]
  idException v34; // [esp+D4h] [ebp-3038h] BYREF
  char v35[2048]; // [esp+8D4h] [ebp-2838h] BYREF
  idException v36; // [esp+10D4h] [ebp-2038h] BYREF
  char v37[2048]; // [esp+18D4h] [ebp-1838h] BYREF
  idException v38; // [esp+20D4h] [ebp-1038h] BYREF
  char pExceptionObject[2048]; // [esp+28D4h] [ebp-838h] BYREF
  idStr v40; // [esp+30D4h] [ebp-38h] BYREF
  char *argptr; // [esp+30F4h] [ebp-18h]
  int v42; // [esp+30F8h] [ebp-14h]
  int v43; // [esp+30FCh] [ebp-10h]
  int v44; // [esp+3108h] [ebp-4h]
  va_list va; // [esp+311Ch] [ebp+10h] BYREF

  va_start(va, fmt);
  v4 = alloca(12544);
  v43 = 2;
  this->com_refreshOnPrint = 0;
  if ( ((int (__thiscall *)(idCVarSystem *, const char *, int, int))cvarSystem->GetCVarInteger)(
         cvarSystem,
         "fs_copyfiles",
         a1,
         a2) )
  {
    v43 = 1;
  }
  if ( !renderSystem->IsOpenGLRunning(renderSystem) )
    v43 = 1;
  if ( this->com_errorEntered )
  {
    if ( this->com_errorEntered == 1 )
      Sys_Quit();
    v43 = 1;
  }
  v42 = Sys_Milliseconds();
  if ( v42 - lastErrorTime >= 100 )
  {
    errorCount = 0;
  }
  else if ( ++errorCount > 3 )
  {
    v43 = 1;
  }
  lastErrorTime = v42;
  this->com_errorEntered = v43;
  idStr::vsnPrintf(this->errorMessage, 4096, fmt, va);
  argptr = 0;
  this->errorMessage[4095] = 0;
  if ( !(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 4) )
  {
    Sys_SetClipboardData(this->errorMessage);
    v40.len = 0;
    v40.alloced = 20;
    v40.data = v40.baseBuffer;
    v40.baseBuffer[0] = 0;
    if ( this != (idCommonLocal *)-16 )
    {
      v13 = &this->errorMessage[strlen(this->errorMessage) + 1];
      if ( v13 - this->errorMessage > v40.alloced )
        idStr::ReAllocate(&v40, v13 - this->errorMessage, 1);
      errorMessage = this->errorMessage;
      data = v40.data;
      do
      {
        v5 = *errorMessage;
        *data++ = *errorMessage++;
      }
      while ( v5 );
      v40.len = v13 - &this->errorMessage[1];
    }
    v44 = 0;
    p_errorList = &this->errorList;
    for ( i = 0; i < p_errorList->num; ++i )
    {
      if ( !idStr::Cmp(this->errorList.list[i].data, v40.data) )
      {
        v33 = i;
        goto LABEL_27;
      }
    }
    v33 = -1;
LABEL_27:
    if ( v33 < 0 )
    {
      if ( !this->errorList.list )
      {
        granularity = this->errorList.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->errorList.size )
          {
            list = this->errorList.list;
            this->errorList.size = granularity;
            if ( this->errorList.size < this->errorList.num )
              this->errorList.num = this->errorList.size;
            count = this->errorList.size;
            ptr = (int *)Memory::Allocate(32 * count + 4);
            LOBYTE(v44) = 1;
            if ( ptr )
            {
              *ptr = count;
              `eh vector constructor iterator'(
                ptr + 1,
                0x20u,
                count,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              v10 = (idStr *)(ptr + 1);
            }
            else
            {
              v10 = 0;
            }
            LOBYTE(v44) = 0;
            this->errorList.list = v10;
            for ( j = 0; j < p_errorList->num; ++j )
            {
              v25 = &this->errorList.list[j];
              len = list[j].len;
              if ( (signed int)(len + 1) > v25->alloced )
                idStr::ReAllocate(v25, len + 1, 0);
              qmemcpy(v25->data, list[j].data, len);
              v25->data[len] = 0;
              v25->len = len;
            }
            if ( list )
              idStr::`vector deleting destructor'(list, 3);
          }
        }
        else
        {
          if ( this->errorList.list )
            idStr::`vector deleting destructor'(this->errorList.list, 3);
          this->errorList.list = 0;
          p_errorList->num = 0;
          this->errorList.size = 0;
        }
      }
      if ( this->errorList.num == this->errorList.size )
      {
        if ( !this->errorList.granularity )
          this->errorList.granularity = 16;
        v31 = this->errorList.granularity + this->errorList.size;
        v17 = v31 - v31 % this->errorList.granularity;
        if ( v17 > 0 )
        {
          if ( v17 != this->errorList.size )
          {
            v22 = this->errorList.list;
            this->errorList.size = v17;
            if ( this->errorList.size < this->errorList.num )
              this->errorList.num = this->errorList.size;
            size = this->errorList.size;
            v20 = (int *)Memory::Allocate(32 * size + 4);
            LOBYTE(v44) = 2;
            if ( v20 )
            {
              *v20 = size;
              `eh vector constructor iterator'(
                v20 + 1,
                0x20u,
                size,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              v9 = (idStr *)(v20 + 1);
            }
            else
            {
              v9 = 0;
            }
            LOBYTE(v44) = 0;
            this->errorList.list = v9;
            for ( k = 0; k < p_errorList->num; ++k )
            {
              v18 = &this->errorList.list[k];
              v19 = v22[k].len;
              if ( (signed int)(v19 + 1) > v18->alloced )
                idStr::ReAllocate(v18, v19 + 1, 0);
              qmemcpy(v18->data, v22[k].data, v19);
              v18->data[v19] = 0;
              v18->len = v19;
            }
            if ( v22 )
              idStr::`vector deleting destructor'(v22, 3);
          }
        }
        else
        {
          if ( this->errorList.list )
            idStr::`vector deleting destructor'(this->errorList.list, 3);
          this->errorList.list = 0;
          p_errorList->num = 0;
          this->errorList.size = 0;
        }
      }
      v15 = &this->errorList.list[this->errorList.num];
      v16 = v40.len;
      if ( v40.len + 1 > v15->alloced )
        idStr::ReAllocate(v15, v40.len + 1, 0);
      qmemcpy(v15->data, v40.data, v16);
      v15->data[v16] = 0;
      v15->len = v16;
      ++p_errorList->num;
    }
    v44 = -1;
    idStr::FreeData(&v40);
    session->Stop(session);
  }
  (*(void (__thiscall **)(_DWORD, char *))(**(_DWORD **)common.ip + 80))(*(_DWORD *)common.ip, this->errorMessage);
  if ( v43 == 3 )
  {
    this->com_errorEntered = 0;
    idException::idException(&v38, this->errorMessage);
    qmemcpy(pExceptionObject, v6, sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, &_TI1_AVidException__);
  }
  if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 12) )
  {
    this->com_errorEntered = 0;
    idException::idException(&v36, this->errorMessage);
    qmemcpy(v37, v7, sizeof(v37));
    _CxxThrowException(v37, &_TI1_AVidException__);
  }
  if ( v43 == 2 )
  {
    this->Printf(this, "********************\nERROR: %s\n********************\n", this->errorMessage);
    this->com_errorEntered = 0;
    idException::idException(&v34, this->errorMessage);
    qmemcpy(v35, v8, sizeof(v35));
    _CxxThrowException(v35, &_TI1_AVidException__);
  }
  this->Printf(this, "********************\nERROR: %s\n********************\n", this->errorMessage);
  if ( cvarSystem->GetCVarBool(cvarSystem, "r_fullscreen") )
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "vid_restart partial windowed\n");
  ((void (__thiscall *)(idCommonLocal *, char *))this->Shutdown)(this, argptr);
  Sys_Error("%s", this->errorMessage);
}

// FUNC: Com_Error_f
void __cdecl Com_Error_f(idCmdArgs *args)
{
  if ( idCVar::GetBool(&com_developer) )
  {
    if ( idEditField::GetCursor(args) > 1 )
      idCommonLocal::FatalError(&commonLocal, "Testing fatal error");
    idCommonLocal::Error(&commonLocal, "Testing drop error");
  }
  idCommonLocal::Printf(&commonLocal, "error may only be used in developer mode\n");
}

// FUNC: public: bool __thiscall idCommonLocal::AddLanguage(class idStr &)
char __thiscall idCommonLocal::AddLanguage(idCommonLocal *this, idStr *language)
{
  rvLanguage *v3; // [esp+4h] [ebp-180h]
  rvLanguage *v4; // [esp+10h] [ebp-174h]
  idList<rvLanguage> *p_languages; // [esp+1Ch] [ebp-168h]
  int v7; // [esp+70h] [ebp-114h]
  int *v8; // [esp+BCh] [ebp-C8h]
  int size; // [esp+C4h] [ebp-C0h]
  rvLanguage *v10; // [esp+C8h] [ebp-BCh]
  int k; // [esp+CCh] [ebp-B8h]
  int granularity; // [esp+D0h] [ebp-B4h]
  int *ptr; // [esp+ECh] [ebp-98h]
  int count; // [esp+F4h] [ebp-90h]
  rvLanguage *list; // [esp+F8h] [ebp-8Ch]
  int j; // [esp+FCh] [ebp-88h]
  int v17; // [esp+100h] [ebp-84h]
  char *s2; // [esp+10Ch] [ebp-78h]
  int i; // [esp+11Ch] [ebp-68h]
  rvLanguage lang; // [esp+120h] [ebp-64h] BYREF
  int v21; // [esp+180h] [ebp-4h]

  rvLanguage::rvLanguage(&lang);
  v21 = 0;
  for ( i = 0; i < this->languages.num; ++i )
  {
    s2 = (char *)rvLanguage::GetLanguage(&this->languages.list[i]);
    if ( !idStr::Icmp(language->data, s2) )
    {
      v21 = 1;
      idLangDict::~idLangDict(&lang.strings);
      v21 = -1;
      idStr::FreeData(&lang.language);
      return 0;
    }
  }
  rvLanguage::SetLanguage(&lang, language);
  p_languages = &this->languages;
  if ( !this->languages.list )
  {
    granularity = this->languages.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->languages.size )
      {
        list = this->languages.list;
        this->languages.size = granularity;
        if ( this->languages.size < this->languages.num )
          this->languages.num = this->languages.size;
        count = this->languages.size;
        ptr = (int *)Memory::Allocate(84 * count + 4);
        LOBYTE(v21) = 2;
        if ( ptr )
        {
          *ptr = count;
          `eh vector constructor iterator'(
            ptr + 1,
            0x54u,
            count,
            (void (__thiscall *)(void *))rvLanguage::rvLanguage,
            (void (__thiscall *)(void *))rvLanguage::~rvLanguage);
          v4 = (rvLanguage *)(ptr + 1);
        }
        else
        {
          v4 = 0;
        }
        LOBYTE(v21) = 0;
        this->languages.list = v4;
        for ( j = 0; j < p_languages->num; ++j )
          rvLanguage::operator=(&this->languages.list[j].language, (int)&list[j]);
        if ( list )
          rvLanguage::`vector deleting destructor'(list, 3);
      }
    }
    else
    {
      if ( this->languages.list )
        rvLanguage::`vector deleting destructor'(this->languages.list, 3);
      this->languages.list = 0;
      p_languages->num = 0;
      this->languages.size = 0;
    }
  }
  if ( this->languages.num == this->languages.size )
  {
    if ( !this->languages.granularity )
      this->languages.granularity = 16;
    v17 = this->languages.granularity + this->languages.size;
    v7 = v17 - v17 % this->languages.granularity;
    if ( v7 > 0 )
    {
      if ( v7 != this->languages.size )
      {
        v10 = this->languages.list;
        this->languages.size = v7;
        if ( this->languages.size < this->languages.num )
          this->languages.num = this->languages.size;
        size = this->languages.size;
        v8 = (int *)Memory::Allocate(84 * size + 4);
        LOBYTE(v21) = 3;
        if ( v8 )
        {
          *v8 = size;
          `eh vector constructor iterator'(
            v8 + 1,
            0x54u,
            size,
            (void (__thiscall *)(void *))rvLanguage::rvLanguage,
            (void (__thiscall *)(void *))rvLanguage::~rvLanguage);
          v3 = (rvLanguage *)(v8 + 1);
        }
        else
        {
          v3 = 0;
        }
        LOBYTE(v21) = 0;
        this->languages.list = v3;
        for ( k = 0; k < p_languages->num; ++k )
          rvLanguage::operator=(&this->languages.list[k].language, (int)&v10[k]);
        if ( v10 )
          rvLanguage::`vector deleting destructor'(v10, 3);
      }
    }
    else
    {
      if ( this->languages.list )
        rvLanguage::`vector deleting destructor'(this->languages.list, 3);
      this->languages.list = 0;
      p_languages->num = 0;
      this->languages.size = 0;
    }
  }
  rvLanguage::operator=(&this->languages.list[this->languages.num].language, (int)&lang);
  ++p_languages->num;
  v21 = 4;
  idLangDict::~idLangDict(&lang.strings);
  v21 = -1;
  idStr::FreeData(&lang.language);
  return 1;
}

// FUNC: public: void __thiscall idCommonLocal::InitLanguageDict(void)
void __thiscall idCommonLocal::InitLanguageDict(idCommonLocal *this)
{
  const char *Language; // eax
  char *v2; // eax
  const char *Name; // eax
  const char *v4; // eax
  const char *v5; // eax
  idStr v6; // [esp-20h] [ebp-334h] BYREF
  idStr *v7; // [esp+8h] [ebp-30Ch]
  idStr *v8; // [esp+Ch] [ebp-308h]
  idStr *v9; // [esp+10h] [ebp-304h]
  char *v10; // [esp+18h] [ebp-2FCh]
  char *v11; // [esp+1Ch] [ebp-2F8h]
  const char *v12; // [esp+20h] [ebp-2F4h]
  int v13; // [esp+24h] [ebp-2F0h]
  const char *v14; // [esp+2Ch] [ebp-2E8h]
  const char *v15; // [esp+30h] [ebp-2E4h]
  idStr *v16; // [esp+34h] [ebp-2E0h]
  bool *v17; // [esp+3Ch] [ebp-2D8h]
  rvLanguage *v18; // [esp+40h] [ebp-2D4h]
  bool *v19; // [esp+44h] [ebp-2D0h]
  idStr *v20; // [esp+48h] [ebp-2CCh]
  idStr *v21; // [esp+4Ch] [ebp-2C8h]
  bool *v22; // [esp+54h] [ebp-2C0h]
  idCommonLocal *thisa; // [esp+58h] [ebp-2BCh]
  idStr *v24; // [esp+5Ch] [ebp-2B8h]
  idStr *v25; // [esp+60h] [ebp-2B4h]
  idStr *v26; // [esp+64h] [ebp-2B0h]
  idStr *v27; // [esp+68h] [ebp-2ACh]
  char *v28; // [esp+6Ch] [ebp-2A8h]
  idStr *v29; // [esp+70h] [ebp-2A4h]
  const char *v30; // [esp+74h] [ebp-2A0h]
  int v31; // [esp+78h] [ebp-29Ch]
  int v32; // [esp+7Ch] [ebp-298h]
  rvLanguage *v33; // [esp+84h] [ebp-290h]
  const idList<idStr> *v34; // [esp+88h] [ebp-28Ch]
  idStr *v35; // [esp+8Ch] [ebp-288h]
  idStr *v36; // [esp+90h] [ebp-284h]
  int v37; // [esp+94h] [ebp-280h]
  int v38; // [esp+98h] [ebp-27Ch]
  void *v39; // [esp+A4h] [ebp-270h]
  idStr *v40; // [esp+A8h] [ebp-26Ch]
  int v41; // [esp+ACh] [ebp-268h]
  int n; // [esp+B0h] [ebp-264h]
  int v43; // [esp+B4h] [ebp-260h]
  rvLanguage *v44; // [esp+C0h] [ebp-254h]
  char *data; // [esp+C8h] [ebp-24Ch]
  int v46; // [esp+D0h] [ebp-244h]
  idList<rvLanguage> *v47; // [esp+D4h] [ebp-240h]
  rvLanguage *v48; // [esp+D8h] [ebp-23Ch]
  rvLanguage *v49; // [esp+DCh] [ebp-238h]
  rvLanguage *v50; // [esp+E0h] [ebp-234h]
  rvLanguage *v51; // [esp+E4h] [ebp-230h]
  void *v52; // [esp+E8h] [ebp-22Ch]
  rvLanguage *v53; // [esp+ECh] [ebp-228h]
  int size; // [esp+F0h] [ebp-224h]
  rvLanguage *v55; // [esp+F4h] [ebp-220h]
  int m; // [esp+F8h] [ebp-21Ch]
  int num; // [esp+FCh] [ebp-218h]
  idStr *v58; // [esp+100h] [ebp-214h]
  idStr *v59; // [esp+104h] [ebp-210h]
  int v60; // [esp+108h] [ebp-20Ch]
  int v61; // [esp+10Ch] [ebp-208h]
  idStr *v62; // [esp+110h] [ebp-204h]
  int end; // [esp+114h] [ebp-200h]
  const idList<idStr> *v64; // [esp+118h] [ebp-1FCh]
  idStr *v65; // [esp+11Ch] [ebp-1F8h]
  idStr *v66; // [esp+120h] [ebp-1F4h]
  int amount; // [esp+124h] [ebp-1F0h]
  int len; // [esp+128h] [ebp-1ECh]
  void *ptr; // [esp+134h] [ebp-1E0h]
  idStr *v70; // [esp+138h] [ebp-1DCh]
  int count; // [esp+13Ch] [ebp-1D8h]
  int k; // [esp+140h] [ebp-1D4h]
  idList<rvLanguage> *p_languages; // [esp+144h] [ebp-1D0h]
  rvLanguage *list; // [esp+148h] [ebp-1CCh]
  rvLanguage *v75; // [esp+14Ch] [ebp-1C8h]
  idStr *v76; // [esp+150h] [ebp-1C4h]
  idStr result; // [esp+154h] [ebp-1C0h] BYREF
  idList<idStr> currentLangList; // [esp+174h] [ebp-1A0h] BYREF
  int offset; // [esp+184h] [ebp-190h]
  int j; // [esp+188h] [ebp-18Ch]
  idStr fileName; // [esp+18Ch] [ebp-188h] BYREF
  idFileList *langFiles; // [esp+1ACh] [ebp-168h]
  char localeInfo[256]; // [esp+1B0h] [ebp-164h] BYREF
  idFileList *langFolders; // [esp+2B0h] [ebp-64h]
  idStr temp; // [esp+2B4h] [ebp-60h] BYREF
  idStr folder; // [esp+2D4h] [ebp-40h] BYREF
  int i; // [esp+2F4h] [ebp-20h]
  idList<idStr> langList; // [esp+2F8h] [ebp-1Ch]
  int v89; // [esp+310h] [ebp-4h]

  thisa = this;
  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  v89 = 2;
  folder.len = 0;
  folder.alloced = 20;
  folder.data = folder.baseBuffer;
  folder.baseBuffer[0] = 0;
  temp.len = 0;
  temp.alloced = 20;
  temp.data = temp.baseBuffer;
  temp.baseBuffer[0] = 0;
  GetLocaleInfoA(0x800u, 0x1002u, localeInfo, 256);
  idCVar::SetString(&sys_country, localeInfo);
  GetLocaleInfoA(0x800u, 0x1001u, localeInfo, 256);
  idCVar::SetString(&sys_language, localeInfo);
  p_languages = &thisa->languages;
  if ( thisa->languages.list )
  {
    list = p_languages->list;
    v75 = list;
    if ( list )
      v22 = rvLanguage::`vector deleting destructor'(v75, 3);
    else
      v22 = 0;
  }
  p_languages->list = 0;
  p_languages->num = 0;
  p_languages->size = 0;
  langFiles = fileSystem->ListFilesTree(fileSystem, "strings", ".lang", 1, 0);
  thisa->StartupVariable(thisa, "sys_lang", 0);
  idStr::operator=(&temp, "english");
  idCommonLocal::AddLanguage(thisa, &temp);
  v64 = idFileList::GetList(langFiles);
  langList.list = 0;
  langList.num = 0;
  langList.size = 0;
  langList.num = v64->num;
  langList.size = v64->size;
  langList.granularity = v64->granularity;
  if ( langList.size )
  {
    count = langList.size;
    ptr = Memory::Allocate(32 * langList.size + 4);
    LOBYTE(v89) = 3;
    if ( ptr )
    {
      *(_DWORD *)ptr = count;
      `eh vector constructor iterator'(
        (char *)ptr + 4,
        0x20u,
        count,
        (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      v21 = (idStr *)((char *)ptr + 4);
    }
    else
    {
      v21 = 0;
    }
    v70 = v21;
    LOBYTE(v89) = 2;
    langList.list = v21;
    for ( k = 0; k < langList.num; ++k )
    {
      v66 = &v64->list[k];
      v65 = &langList.list[k];
      len = v66->len;
      amount = len + 1;
      if ( len + 1 > v65->alloced )
        idStr::ReAllocate(v65, amount, 0);
      qmemcpy(v65->data, v66->data, len);
      v65->data[len] = 0;
      v65->len = len;
    }
  }
  LOBYTE(v89) = 4;
  for ( i = 0; i < langList.num; ++i )
  {
    idStr::StripLeading(&langList.list[i], "strings/");
    end = -1;
    v62 = &langList.list[i];
    end = v62->len;
    offset = idStr::FindChar(v62->data, 95, 0, end);
    if ( offset > -1 )
    {
      v20 = idStr::Left(&langList.list[i], &result, offset);
      v59 = v20;
      LOBYTE(v89) = 5;
      v58 = &langList.list[i];
      v61 = v20->len;
      v60 = v61 + 1;
      if ( v61 + 1 > v58->alloced )
        idStr::ReAllocate(v58, v60, 0);
      qmemcpy(v58->data, v59->data, v61);
      v58->data[v61] = 0;
      v58->len = v61;
      LOBYTE(v89) = 4;
      idStr::FreeData(&result);
      idCommonLocal::AddLanguage(thisa, &langList.list[i]);
    }
  }
  num = thisa->languages.num;
  v47 = &thisa->languages;
  if ( num > 0 )
  {
    if ( num != v47->size )
    {
      v55 = v47->list;
      v47->size = num;
      if ( v47->size < v47->num )
        v47->num = v47->size;
      size = v47->size;
      v52 = Memory::Allocate(84 * size + 4);
      LOBYTE(v89) = 6;
      if ( v52 )
      {
        *(_DWORD *)v52 = size;
        `eh vector constructor iterator'(
          (char *)v52 + 4,
          0x54u,
          size,
          (void (__thiscall *)(void *))rvLanguage::rvLanguage,
          (void (__thiscall *)(void *))rvLanguage::~rvLanguage);
        v18 = (rvLanguage *)((char *)v52 + 4);
      }
      else
      {
        v18 = 0;
      }
      v53 = v18;
      LOBYTE(v89) = 4;
      v47->list = v18;
      for ( m = 0; m < v47->num; ++m )
        rvLanguage::operator=(&v47->list[m].language, (int)&v55[m]);
      if ( v55 )
      {
        v50 = v55;
        v51 = v55;
        v17 = rvLanguage::`vector deleting destructor'(v55, 3);
      }
    }
  }
  else
  {
    if ( v47->list )
    {
      v48 = v47->list;
      v49 = v48;
      if ( v48 )
        v19 = rvLanguage::`vector deleting destructor'(v49, 3);
      else
        v19 = 0;
    }
    v47->list = 0;
    v47->num = 0;
    v47->size = 0;
  }
  v47->num = num;
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Found default language English with VO\n");
  rvLanguage::SetHasVO(thisa->languages.list, 1);
  for ( i = 1; ; ++i )
  {
    v46 = thisa->languages.num;
    if ( i >= v46 )
      break;
    Language = rvLanguage::GetLanguage(&thisa->languages.list[i]);
    v2 = va("sound/vo_%s", Language);
    idStr::operator=(&folder, v2);
    data = folder.data;
    langFolders = fileSystem->ListFiles(fileSystem, folder.data, "/", 0, 0, 0);
    v44 = &thisa->languages.list[i];
    Name = idMapFile::GetName((idMapFile *)langFolders);
    rvLanguage::SetHasVO(v44, Name != 0);
    if ( rvLanguage::HasVO(&thisa->languages.list[i]) )
    {
      v4 = rvLanguage::GetLanguage(&thisa->languages.list[i]);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        ".... found additional language '%s' with VO\n",
        v4);
    }
    else
    {
      v5 = rvLanguage::GetLanguage(&thisa->languages.list[i]);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        ".... found additional language '%s' without VO\n",
        v5);
    }
    fileSystem->FreeFileList(fileSystem, langFolders);
  }
  for ( i = 0; ; ++i )
  {
    v43 = thisa->languages.num;
    if ( i >= v43 )
      break;
    v34 = idFileList::GetList(langFiles);
    currentLangList.list = 0;
    currentLangList.num = 0;
    currentLangList.size = 0;
    currentLangList.num = v34->num;
    currentLangList.size = v34->size;
    currentLangList.granularity = v34->granularity;
    if ( currentLangList.size )
    {
      v41 = currentLangList.size;
      v39 = Memory::Allocate(32 * currentLangList.size + 4);
      LOBYTE(v89) = 7;
      if ( v39 )
      {
        *(_DWORD *)v39 = v41;
        `eh vector constructor iterator'(
          (char *)v39 + 4,
          0x20u,
          v41,
          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        v16 = (idStr *)((char *)v39 + 4);
      }
      else
      {
        v16 = 0;
      }
      v40 = v16;
      LOBYTE(v89) = 4;
      currentLangList.list = v16;
      for ( n = 0; n < currentLangList.num; ++n )
      {
        v36 = &v34->list[n];
        v35 = &currentLangList.list[n];
        v38 = v36->len;
        v37 = v38 + 1;
        if ( v38 + 1 > v35->alloced )
          idStr::ReAllocate(v35, v37, 0);
        qmemcpy(v35->data, v36->data, v38);
        v35->data[v38] = 0;
        v35->len = v38;
      }
    }
    LOBYTE(v89) = 8;
    v33 = &thisa->languages.list[i];
    v30 = rvLanguage::GetLanguage(v33);
    v76 = &v6;
    v29 = &v6;
    v6.len = 0;
    v6.alloced = 20;
    v6.data = v6.baseBuffer;
    v6.baseBuffer[0] = 0;
    if ( v30 )
    {
      v15 = v30;
      v14 = v30 + 1;
      v15 += strlen(v15);
      v13 = ++v15 - (v30 + 1);
      v32 = v13;
      v31 = v15 - v30;
      if ( v15 - v30 > v29->alloced )
        idStr::ReAllocate(v29, v31, 1);
      v12 = v30;
      v11 = v29->data;
      v10 = v11;
      strcpy(v11, v30);
      v29->len = v32;
    }
    v9 = v29;
    idCommonLocal::FilterLangList(thisa, &currentLangList, v6);
    for ( j = 0; j < currentLangList.num; ++j )
    {
      v28 = currentLangList.list[j].data;
      rvLanguage::Load(&thisa->languages.list[i], v28, 0);
    }
    LOBYTE(v89) = 4;
    if ( currentLangList.list )
    {
      v26 = currentLangList.list;
      v27 = currentLangList.list;
      v8 = idStr::`vector deleting destructor'(currentLangList.list, 3);
    }
    currentLangList.list = 0;
    currentLangList.num = 0;
    currentLangList.size = 0;
  }
  fileSystem->FreeFileList(fileSystem, langFiles);
  idCommonLocal::SetActiveLanguage(thisa);
  LOBYTE(v89) = 2;
  if ( langList.list )
  {
    v24 = langList.list;
    v25 = langList.list;
    v7 = idStr::`vector deleting destructor'(langList.list, 3);
  }
  langList.list = 0;
  langList.num = 0;
  langList.size = 0;
  LOBYTE(v89) = 1;
  idStr::FreeData(&temp);
  LOBYTE(v89) = 0;
  idStr::FreeData(&folder);
  v89 = -1;
  idStr::FreeData(&fileName);
}

// FUNC: void __cdecl Com_ReloadLanguage_f(class idCmdArgs const &)
void __cdecl Com_ReloadLanguage_f()
{
  fileSystem->SetIsFileLoadingAllowed(fileSystem, 1);
  idCommonLocal::InitLanguageDict(&commonLocal);
  fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
}

// FUNC: public: void __thiscall idCommonLocal::InitGame(void)
void __thiscall idCommonLocal::InitGame(idCommonLocal *this)
{
  const char *v1; // eax
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // eax
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  bool sysDetect; // [esp+7h] [ebp-90Dh]
  idFile *file; // [esp+8h] [ebp-90Ch]
  idCmdArgs args; // [esp+Ch] [ebp-908h] BYREF

  fileSystem->Init(fileSystem);
  declManager->Init(declManager);
  idCommonLocal::CheckToolMode(this);
  v1 = fileSystem->RelativePathToOSPath(fileSystem, "config.spec", "fs_savepath");
  file = fileSystem->OpenExplicitFileRead(fileSystem, v1);
  sysDetect = file == 0;
  if ( !file )
    file = fileSystem->OpenFileWrite(fileSystem, "config.spec", "fs_savepath", 0);
  fileSystem->CloseFile(fileSystem, file);
  idCmdArgs::idCmdArgs(&args);
  if ( sysDetect )
  {
    idCommonLocal::SetMachineSpec(this);
    Com_ExecMachineSpec_f(&args);
    cvarSystem->SetCVarInteger(cvarSystem, "s_numberOfSpeakers", 6, 0);
  }
  renderSystem->Init(renderSystem);
  idCommonLocal::InitLanguageDict(this);
  console->LoadGraphics(console);
  idEventLoop::Init(eventLoop);
  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "exec default.cfg\n");
  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "exec editor.cfg\n");
  if ( !idCommonLocal::SafeMode(this) )
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "exec Quake4Config.cfg\n");
  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "exec autoexec.cfg\n");
  if ( idCVar::GetBool(&com_Bundler) )
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "exec bundlesettings.cfg\n");
  cmdSystem->ExecuteCommandBuffer(cmdSystem);
  this->StartupVariable(this, 0, 0);
  idCommonLocal::SetActiveLanguage(this);
  sys->UpdateConsole(sys);
  cvarSystem->ClearModifiedFlags(cvarSystem, 0x20000);
  usercmdGen->Init(usercmdGen);
  v2 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                       common.type,
                       "#str_104346",
                       -1);
  idCommonLocal::PrintLoadingMessage(this, v2);
  S_InitSoundSystem();
  v3 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                       common.type,
                       "#str_104347",
                       -1);
  idCommonLocal::PrintLoadingMessage(this, v3);
  idAsyncNetwork::Init();
  if ( idCVar::GetInteger(&idAsyncNetwork::serverDedicated) == 1 )
  {
    idAsyncServer::InitPort(&idAsyncNetwork::server);
    cvarSystem->SetCVarBool(cvarSystem, "s_noSound", 1, 0);
  }
  else
  {
    v4 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                         common.type,
                         "#str_104348",
                         -1);
    idCommonLocal::PrintLoadingMessage(this, v4);
    idCommonLocal::InitRenderSystem(this);
  }
  v5 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                       common.type,
                       "#str_104349",
                       -1);
  idCommonLocal::PrintLoadingMessage(this, v5);
  uiManager->Init(uiManager);
  v6 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                       common.type,
                       "#str_104350",
                       -1);
  idCommonLocal::PrintLoadingMessage(this, v6);
  idCommonLocal::LoadGameDLL(this);
  v7 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                       common.type,
                       "#str_104351",
                       -1);
  idCommonLocal::PrintLoadingMessage(this, v7);
  session->Init(session);
  if ( sysDetect )
  {
    idCommonLocal::SetMachineSpec(this);
    Com_ExecMachineSpec_f(&args);
  }
  if ( idCVar::GetBool(&com_MakeLoadScreens) )
    GenerateXenonLoadScreenData();
}

// FUNC: void __cdecl Com_ReloadEngine_f(class idCmdArgs const &)
void __cdecl Com_ReloadEngine_f(idCmdArgs *args)
{
  const char *v1; // eax
  bool menu; // [esp+3h] [ebp-1h]

  menu = 0;
  if ( idCommonLocal::IsInitialized(&commonLocal) )
  {
    fileSystem->SetIsFileLoadingAllowed(fileSystem, 1);
    if ( idEditField::GetCursor(args) > 1 )
    {
      v1 = idCmdArgs::Argv(args, 1);
      menu = idStr::Icmp(v1, "menu") == 0;
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "============= ReloadEngine start =============\n");
    if ( !menu )
      sys->ShowConsole(sys, 1, 0);
    idCommonLocal::ShutdownGame(&commonLocal, 1);
    idCommonLocal::InitGame(&commonLocal);
    if ( !menu && !idCVar::GetBool(&idAsyncNetwork::serverDedicated) )
      sys->ShowConsole(sys, 0, 0);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "============= ReloadEngine end ===============\n");
    if ( !cmdSystem->PostReloadEngine(cmdSystem) && menu )
      session->StartMenu(session, &entityFilter);
    fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
  }
}

// FUNC: private: void __thiscall idCommonLocal::InitCommands(void)
void __thiscall idCommonLocal::InitCommands(idCommonLocal *this)
{
  cmdSystem->AddCommand(cmdSystem, "error", (void (__cdecl *)(const idCmdArgs *))Com_Error_f, 3, "causes an error", 0);
  cmdSystem->AddCommand(cmdSystem, "crash", (void (__cdecl *)(const idCmdArgs *))Com_Crash_f, 3, "causes a crash", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "freeze",
    (void (__cdecl *)(const idCmdArgs *))Com_Freeze_f,
    3,
    "freezes the game for a number of seconds",
    0);
  cmdSystem->AddCommand(cmdSystem, "quit", (void (__cdecl *)(const idCmdArgs *))Com_Quit_f, 2, "quits the game", 0);
  cmdSystem->AddCommand(cmdSystem, "exit", (void (__cdecl *)(const idCmdArgs *))Com_Quit_f, 2, "exits the game", 0);
  cmdSystem->AddCommand(cmdSystem, "writeConfig", Com_WriteConfig_f, 2, "writes a config file", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "reloadEngine",
    Com_ReloadEngine_f,
    2,
    "reloads the engine down to including the file system",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "setMachineSpec",
    Com_SetMachineSpec_f,
    2,
    "detects system capabilities and sets com_machineSpec to appropriate value",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "execMachineSpec",
    Com_ExecMachineSpec_f,
    2,
    "execs the appropriate config files and sets cvars based on com_machineSpec",
    0);
  cmdSystem->AddCommand(cmdSystem, "execMPMachineSpec", Com_ExecMPMachineSpec_f, 2, "sets cvars for multiplayer", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "showMemory",
    Com_ShowMemory_f,
    32,
    "gives a reasonably detailed account of memory usage",
    0);
  cmdSystem->AddCommand(cmdSystem, "dmap", Com_Dmap_f, 32, "compiles a map", idCmdSystem::ArgCompletion_MapName);
  cmdSystem->AddCommand(
    cmdSystem,
    "createCM",
    (void (__cdecl *)(const idCmdArgs *))Com_CreateCM_f,
    32,
    "creates a .cm file for a map",
    idCmdSystem::ArgCompletion_FileName);
  cmdSystem->AddCommand(
    cmdSystem,
    "renderbump",
    Com_RenderBump_f,
    32,
    "renders a bump map",
    idCmdSystem::ArgCompletion_ModelName);
  cmdSystem->AddCommand(
    cmdSystem,
    "renderbumpFlat",
    Com_RenderBumpFlat_f,
    32,
    "renders a flat bump map",
    idCmdSystem::ArgCompletion_ModelName);
  cmdSystem->AddCommand(
    cmdSystem,
    "runAAS",
    Com_RunAAS_f,
    32,
    "compiles an AAS file for a map",
    idCmdSystem::ArgCompletion_MapName);
  cmdSystem->AddCommand(
    cmdSystem,
    "runAASDir",
    Com_RunAASDir_f,
    32,
    "compiles AAS files for all maps in a folder",
    idCmdSystem::ArgCompletion_MapName);
  cmdSystem->AddCommand(
    cmdSystem,
    "runReach",
    Com_RunReach_f,
    32,
    "calculates reachability for an AAS file",
    idCmdSystem::ArgCompletion_MapName);
  cmdSystem->AddCommand(cmdSystem, "roq", Com_RoQFileEncode_f, 32, "encodes a roq file", 0);
  cmdSystem->AddCommand(cmdSystem, "phonemeGen", Com_PhonemeGen_f, 32, "generates phonemes for text/wav combination", 0);
  cmdSystem->AddCommand(cmdSystem, "shakesGen", Com_ShakesGen_f, 32, "generates shake data for sound shaders", 0);
  cmdSystem->AddCommand(cmdSystem, "localizeGuis", Com_LocalizeGuis_f, 3, "localize gui file", 0);
  cmdSystem->AddCommand(cmdSystem, "localizeLipsyncs", Com_LocalizeLipsyncs_f, 3, "localize lipsyncs", 0);
  cmdSystem->AddCommand(cmdSystem, "localizeMaps", Com_LocalizeMaps_f, 3, "localize map files", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "localizeValidateLipsyncs",
    Com_LocalizeValidateLipsyncs_f,
    3,
    "ensures the emotions in the localized strings match those in the English string",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "localizeValidateStrings",
    Com_LocalizeValidateStrings_f,
    3,
    "makes sure each string exists and is localised",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "runAASTactical",
    Com_RunAASTactical_f,
    32,
    "calculates tactical features for an AAS file",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editor",
    (void (__cdecl *)(const idCmdArgs *))Com_Editor_f,
    32,
    "launches the level editor Radiant",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editLights",
    (void (__cdecl *)(const idCmdArgs *))Com_EditLights_f,
    32,
    "launches the in-game Light Editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editSounds",
    (void (__cdecl *)(const idCmdArgs *))Com_EditSounds_f,
    32,
    "launches the in-game Sound Editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editDecls",
    (void (__cdecl *)(const idCmdArgs *))Com_EditDecls_f,
    32,
    "launches the in-game Declaration Editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editAFs",
    (void (__cdecl *)(const idCmdArgs *))Com_EditAFs_f,
    32,
    "launches the in-game Articulated Figure Editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editScripts",
    (void (__cdecl *)(const idCmdArgs *))Com_EditScripts_f,
    32,
    "launches the in-game Script Editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editGUIs",
    (void (__cdecl *)(const idCmdArgs *))Com_EditGUIs_f,
    32,
    "launches the GUI Editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editPDAs",
    (void (__cdecl *)(const idCmdArgs *))Com_EditPDAs_f,
    32,
    "launches the in-game PDA Editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "debugger",
    (void (__cdecl *)(const idCmdArgs *))Com_ScriptDebugger_f,
    32,
    "launches the Script Debugger",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editFX",
    (void (__cdecl *)(const idCmdArgs *))Com_FXEditor_f,
    32,
    "launches the fx editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editReverb",
    (void (__cdecl *)(const idCmdArgs *))Com_ReverbEditor_f,
    32,
    "launches the reverb editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editPlaybacks",
    (void (__cdecl *)(const idCmdArgs *))Com_EditPlaybacks_f,
    32,
    "launches the playback editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editFX_play",
    (void (__cdecl *)(const idCmdArgs *))Com_FXEditorPlayEffect_f,
    32,
    "plays current effect in fx editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editFX_playlooping",
    (void (__cdecl *)(const idCmdArgs *))Com_FXEditorPlayLoopingEffect_f,
    32,
    "plays current effect in fx editor as looping effect",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editFX_stop",
    (void (__cdecl *)(const idCmdArgs *))Com_FXEditorStopEffect_f,
    32,
    "stops current effect in fx editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "editMaterials",
    (void (__cdecl *)(const idCmdArgs *))Com_MaterialEditor_f,
    32,
    "launches the Material Editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "modview",
    (void (__cdecl *)(const idCmdArgs *))Com_ModView_f,
    32,
    "launches the model viewer",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "renderbumpFlatGUI",
    (void (__cdecl *)(const idCmdArgs *))Com_RenderBumpFlatGUI_f,
    32,
    "launches the renderbump flat gui",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "activateEditor",
    (void (__cdecl *)(const idCmdArgs *))Com_ActivateEditor_f,
    32,
    "activates the currently open editor",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "logview",
    (void (__cdecl *)(const idCmdArgs *))Com_LogView_f,
    32,
    "launches the game log viewer",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "entview",
    (void (__cdecl *)(const idCmdArgs *))Com_EntView_f,
    32,
    "launches the game entity viewer",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "writeAssetLog",
    Com_WriteAssetLog_f,
    2,
    "generates log file of all the assets loaded",
    0);
  cmdSystem->AddCommand(cmdSystem, "clearAssetLog", Com_ClearAssetLog_f, 2, "clears log of all the assets loaded", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "showMemAlloc",
    Mem_ShowMemAlloc_f,
    32,
    "Prints outstanding mem_alloc tags -- Debug only",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "bundler",
    (void (__cdecl *)(const idCmdArgs *))rvToolsStub::GEMessage,
    32,
    "Setup the bundler settings",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "makeLoadScreens",
    SpawnStub,
    32,
    "Stub to keep the game from erroring out on startup when building load screens",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "exportMD5R",
    (void (__cdecl *)(const idCmdArgs *))Com_Export_MD5R_f,
    32,
    "Export all MD5R models",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "exportCmpMD5R",
    (void (__cdecl *)(const idCmdArgs *))Com_Export_Cmp_MD5R_f,
    32,
    "Export all MD5R models in a compressed form",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "printMemInfo",
    (void (__cdecl *)(const idCmdArgs *))PrintMemInfo_f,
    2,
    "prints memory debugging data",
    0);
  cmdSystem->AddCommand(cmdSystem, "memoryDump", Mem_Dump_f, 3, "creates a memory dump", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "memoryDumpCompressed",
    Mem_DumpCompressed_f,
    3,
    "creates a compressed memory dump",
    0);
  cmdSystem->AddCommand(cmdSystem, "showStringMemory", idStr::ShowMemoryUsage_f, 2, "shows memory used by strings", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "showDictMemory",
    idDict::ShowMemoryUsage_f,
    2,
    "shows memory used by dictionaries",
    0);
  cmdSystem->AddCommand(cmdSystem, "listDictKeys", idDict::ListKeys_f, 3, "lists all keys used by dictionaries", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "listDictValues",
    idDict::ListValues_f,
    3,
    "lists all values used by dictionaries",
    0);
  cmdSystem->AddCommand(cmdSystem, "testSIMD", idSIMD::Test_f, 3, "test SIMD code", 0);
  cmdSystem->AddCommand(cmdSystem, "reloadLanguage", Com_ReloadLanguage_f, 2, "reload language dict", 0);
  cmdSystem->AddCommand(cmdSystem, "startBuild", Com_StartBuild_f, 3, "prepares to make a build", 0);
  cmdSystem->AddCommand(cmdSystem, "finishBuild", Com_FinishBuild_f, 3, "finishes the build process", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "IncrementCVar",
    (void (__cdecl *)(const idCmdArgs *))IncrementCVar_f,
    2,
    "IncrementCVar <name> <amount> <max>",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "DecrementCVar",
    (void (__cdecl *)(const idCmdArgs *))DecrementCVar_f,
    2,
    "DecrementCVar <name> <amount> <min>",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "WriteConfiguration",
    (void (__cdecl *)(const idCmdArgs *))idCommonLocal::WriteConfiguration_f,
    2,
    "WriteConfiguration",
    0);
}

// FUNC: public: virtual void __thiscall idCommonLocal::Init(int,char const * *,char const *)
void __thiscall idCommonLocal::Init(idCommonLocal *this, int argc, const char **argv, const char *cmdline)
{
  int v4; // [esp+0h] [ebp-948h] BYREF
  bool v6; // [esp+Fh] [ebp-939h]
  int v9; // [esp+18h] [ebp-930h]
  const char **v11; // [esp+20h] [ebp-928h]
  idCommonLocal *thisa; // [esp+24h] [ebp-924h]
  idCVarHelp *j; // [esp+28h] [ebp-920h]
  idCVar *i; // [esp+2Ch] [ebp-91Ch]
  idCmdArgs args; // [esp+30h] [ebp-918h] BYREF
  int *v16; // [esp+938h] [ebp-10h]
  int v17; // [esp+944h] [ebp-4h]

  v16 = &v4;
  thisa = this;
  v17 = 0;
  idLib::sys = sys;
  idLib::common = (idCommon *)common.type;
  idLib::cvarSystem = cvarSystem;
  idLib::fileSystem = fileSystem;
  com_debugHudActive = 0;
  idLib::Init();
  thisa->ClearWarnings(thisa, "Quake4 initialization");
  PBsdk_SetPointers();
  idCmdArgs::idCmdArgs(&args);
  if ( cmdline )
  {
    idCmdArgs::TokenizeString(&args, cmdline, 1);
    v11 = idCmdArgs::GetArgs(&args, &argc);
    argv = v11;
  }
  idCommonLocal::ParseCommandLine(thisa, argc, argv);
  cmdSystem->Init(cmdSystem);
  cvarSystem->Init(cvarSystem);
  if ( idCVar::staticVars != (idCVar *)-1 )
  {
    for ( i = idCVar::staticVars; i; i = i->next )
      cvarSystem->Register(cvarSystem, i);
    idCVar::staticVars = (idCVar *)-1;
  }
  thisa->Printf(thisa, "%s\n", &version);
  if ( idCVarHelp::staticCVarHelps != (idCVarHelp *)-1 )
  {
    for ( j = idCVarHelp::staticCVarHelps; j; j = (idCVarHelp *)j->next )
      (*(void (__thiscall **)(idCVarSystem *, idCVarHelp *))cvarSystem->gap10)(cvarSystem, j);
    idCVarHelp::staticCVarHelps = (idCVarHelp *)-1;
  }
  idKeyInput::Init();
  console->Init(console);
  Sys_Init();
  Sys_InitNetworking();
  thisa->StartupVariable(thisa, 0, 0);
  if ( cvarSystem->GetCVarInteger(cvarSystem, "net_serverDedicated") )
    cvarSystem->SetCVarInteger(cvarSystem, "win_viewlog", 1, 0);
  v9 = cvarSystem->GetCVarInteger(cvarSystem, "win_viewlog");
  sys->ShowConsole(sys, v9, 1);
  if ( !idCVar::GetInteger(&idAsyncNetwork::serverDedicated) && Sys_AlreadyRunning() )
    Sys_Quit();
  idCommonLocal::InitSIMD(thisa);
  idCommonLocal::InitCommands(thisa);
  if ( argc > 0 && !idStr::Icmp(*argv, "bundler") )
  {
    cvarSystem->SetCVarBool(cvarSystem, "com_makingBuild", 1, 0);
    cvarSystem->SetCVarBool(cvarSystem, "com_Bundler", 1, 0);
  }
  idCommonLocal::InitGame(thisa);
  v6 = idCommonLocal::AddStartupCommands(thisa);
  if ( !v6 || idCVar::GetBool(&com_Bundler) )
    session->StartMenu(session, "playIntro");
  thisa->Printf(thisa, "------ Common Initialization Complete -------\n");
  if ( idCVar::GetBool(&com_makingBuild) && !idCVar::GetBool(&com_Bundler) )
  {
    cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "reloadImages rebuild");
    cmdSystem->ExecuteCommandBuffer(cmdSystem);
  }
  if ( cvarSystem->GetCVarBool(cvarSystem, "com_WriteSingleDeclFile") )
    declManager->WriteDeclFile(declManager);
  thisa->PrintWarnings(thisa);
  console->ClearNotifyLines(console);
  thisa->com_fullyInitialized = 1;
}

// FUNC: public: char const * __thiscall idLangDict::GetString(char const *)const
char *__thiscall idLangDict::GetString(idLangDict *this, const char *str)
{
  int v4; // esi

  if ( !str || !*str )
    return (char *)&entityFilter;
  if ( idStr::Cmpn(str, "#str_", 5) )
    return (char *)str;
  v4 = this->hash.hash[this->hash.hashMask & this->hash.lookupMask & idLangDict::GetHashKey(this, str)];
  if ( v4 == -1 )
  {
LABEL_8:
    idLib::common->Warning(idLib::common, "Unknown string id %s", str);
    return (char *)str;
  }
  else
  {
    while ( idStr::Cmp(this->args.list[v4].key.data, str) )
    {
      v4 = this->hash.indexChain[v4 & this->hash.lookupMask];
      if ( v4 == -1 )
        goto LABEL_8;
    }
    return this->args.list[v4].value.data;
  }
}
