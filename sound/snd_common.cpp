
// FUNC: public: __thiscall rvCommonSample::rvCommonSample(void)
void __thiscall rvCommonSample::rvCommonSample(rvCommonSample *this)
{
  char *baseBuffer; // ecx

  this->__vftable = (rvCommonSample_vtbl *)&rvCommonSample::`vftable';
  this->name.len = 0;
  this->name.alloced = 20;
  baseBuffer = this->name.baseBuffer;
  this->name.data = baseBuffer;
  *baseBuffer = 0;
  this->timestamp = 0;
  this->defaultSound = 0;
  this->purged = 0;
  this->levelLoadReferenced = 0;
}

// FUNC: TestSound_f
void __cdecl TestSound_f(const idCmdArgs *args)
{
  idSoundSystem_vtbl *v1; // esi
  int v2; // eax

  if ( args->argc == 2 )
  {
    v1 = soundSystem->__vftable;
    v2 = ((int (__thiscall *)(idSoundSystem *, char *, int))soundSystem->GetActiveSoundWorld)(
           soundSystem,
           args->argv[1],
           -1);
    ((void (__thiscall *)(idSoundSystem *, int))v1->PlayShaderDirectly)(soundSystem, v2);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Usage: testSound <file>\n");
  }
}

// FUNC: ListActiveSounds_f
void __cdecl ListActiveSounds_f(const idCmdArgs *args)
{
  int v1; // eax

  v1 = -1;
  if ( args->argc > 1 )
    v1 = atol(args->argv[1]);
  soundSystem->ListActiveSounds(soundSystem, v1);
}

// FUNC: SoundLog_f
void __usercall SoundLog_f(int a1@<ebp>)
{
  int v1; // esi
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // esi
  int v7; // ebp
  int v8; // eax
  int v9; // esi
  int v10; // eax

  v1 = *(_DWORD *)common.type;
  v2 = declManager->GetNumDecls(declManager, DECL_SOUND);
  (*(void (**)(netadrtype_t, const char *, ...))(v1 + 124))(common.type, "Processing %d sound decls....\n", v2);
  v3 = 0;
  v4 = 1;
  if ( declManager->GetNumDecls(declManager, DECL_SOUND) > 1 )
  {
    do
    {
      v5 = ((int (__thiscall *)(idDeclManager *, int, _DWORD, int))declManager->SoundByIndex)(declManager, v4, 0, a1);
      v6 = *(_DWORD *)(v5 + 380);
      if ( v6 )
      {
        v7 = *(_DWORD *)common.type;
        v8 = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v5 + 4) + 4))(*(_DWORD *)(v5 + 4));
        (*(void (**)(netadrtype_t, const char *, ...))(v7 + 124))(common.type, "%d plays: '%s'\n", v6, v8);
        ++v3;
      }
      a1 = 3;
      ++v4;
    }
    while ( v4 < ((int (__thiscall *)(idDeclManager *))declManager->GetNumDecls)(declManager) );
  }
  v9 = *(_DWORD *)common.type;
  v10 = declManager->GetNumDecls(declManager, DECL_SOUND);
  (*(void (**)(netadrtype_t, const char *, ...))(v9 + 124))(common.type, "%d sounds played out of %d\n", v3, v10);
}

// FUNC: FadeSoundClass_f
void __cdecl FadeSoundClass_f(const idCmdArgs *args)
{
  const char *v1; // esi
  idSoundSystem_vtbl *v2; // edi
  int v3; // eax
  float v4; // [esp+0h] [ebp-14h]
  int v5; // [esp+10h] [ebp-4h]

  if ( args->argc == 3 )
  {
    v1 = args->argv[1];
    v2 = soundSystem->__vftable;
    v4 = atof(args->argv[2]);
    v5 = (int)atof(v1);
    v3 = ((int (__thiscall *)(idSoundSystem *, int, _DWORD, _DWORD))soundSystem->GetActiveSoundWorld)(
           soundSystem,
           v5,
           LODWORD(v4),
           0);
    ((void (__thiscall *)(idSoundSystem *, int))v2->FadeSoundClasses)(soundSystem, v3);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Usage: fadeSoundClass <classnum> <dB>\n");
  }
}

// FUNC: void __cdecl S_InitSoundSystem(void)
void __cdecl S_InitSoundSystem()
{
  S_InitDefault();
  cmdSystem->AddCommand(cmdSystem, "testSound", TestSound_f, 9, "tests a sound", idCmdSystem::ArgCompletion_SoundName);
  cmdSystem->AddCommand(cmdSystem, "listActiveSounds", ListActiveSounds_f, 9, "list the active sounds", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "soundLog",
    (void (__cdecl *)(const idCmdArgs *))SoundLog_f,
    9,
    "list the number of times sounds have been played",
    0);
  cmdSystem->AddCommand(cmdSystem, "fadeSoundClass", FadeSoundClass_f, 9, "fade the specified sound class", 0);
  soundSystem->Init(soundSystem);
}

// FUNC: void __cdecl S_ExpandOggFiles(void)
void __usercall S_ExpandOggFiles(int a1@<edi>)
{
  int v1; // esi
  idSoundShader *v2; // edi

  v1 = 1;
  if ( declManager->GetNumDecls(declManager, DECL_SOUND) > 1 )
  {
    do
    {
      v2 = (idSoundShader *)((int (__thiscall *)(idDeclManager *, int, int, _DWORD, int))declManager->DeclByIndex)(
                              declManager,
                              3,
                              v1,
                              0,
                              a1);
      if ( v2->base->IsValid(v2->base) )
        idSoundShader::ExpandSmallOggs(v2, 0);
      a1 = 3;
      ++v1;
    }
    while ( v1 < ((int (__thiscall *)(idDeclManager *))declManager->GetNumDecls)(declManager) );
  }
}
