
// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Boolean(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Boolean(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // eax

  if ( args->argc <= 0 )
    v2 = &entityFilter;
  else
    v2 = args->argv[0];
  v3 = va("%s 0", v2);
  callback(v3);
  if ( args->argc <= 0 )
    v4 = va("%s 1", &entityFilter);
  else
    v4 = va("%s 1", args->argv[0]);
  callback(v4);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_String<&char const * * cm_contentsNameByIndex>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_String<&char const * * cm_contentsNameByIndex>(
        const idCmdArgs *args,
        void (__cdecl *callback)(const char *))
{
  const char *v2; // eax
  const char **v3; // esi
  const char *v4; // ecx
  const char *v5; // eax

  v2 = cm_contentsNameByIndex[0];
  if ( cm_contentsNameByIndex[0] )
  {
    v3 = cm_contentsNameByIndex;
    do
    {
      if ( args->argc <= 0 )
        v4 = &entityFilter;
      else
        v4 = args->argv[0];
      v5 = va("%s %s", v4, v2);
      callback(v5);
      v2 = v3[1];
      ++v3;
    }
    while ( v2 );
  }
}

// FUNC: public: virtual __thiscall idCmdSystem::~idCmdSystem(void)
void __thiscall idCmdSystem::~idCmdSystem(idCmdSystem *this)
{
  this->__vftable = (idCmdSystem_vtbl *)&idCmdSystem::`vftable';
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_ConfigName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_ConfigName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "/", 1, ".cfg", 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_FileName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_FileName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "/", 1, &entityFilter, 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_MapName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_MapName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "maps/", 1, ".map", 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_ModelName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_ModelName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(
    cmdSystem,
    args,
    callback,
    "models/",
    0,
    ".lwo",
    ".ase",
    ".md5mesh",
    ".ma",
    0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<0>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<0>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<1>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<1>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 1);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<2>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<2>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 2);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<3>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<3>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 3);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<4>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<4>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 4);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<11>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<11>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 11);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<12>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<12>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 12);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<15>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<15>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 15);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<13>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<13>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 13);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<14>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<14>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 14);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<6>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<6>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 6);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<7>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<7>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 7);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<8>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<8>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 8);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_Decl<9>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_Decl<9>(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_DeclName(cmdSystem, args, callback, 9);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>(
        const idCmdArgs *args,
        void (__cdecl *callback)(const char *))
{
  const char *v2; // eax
  const char **v3; // esi
  const char *v4; // ecx
  const char *v5; // eax

  v2 = listDeclStrings[0];
  if ( listDeclStrings[0] )
  {
    v3 = listDeclStrings;
    do
    {
      if ( args->argc <= 0 )
        v4 = &entityFilter;
      else
        v4 = args->argv[0];
      v5 = va("%s %s", v4, v2);
      callback(v5);
      v2 = v3[1];
      ++v3;
    }
    while ( v2 );
  }
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_GuiName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_GuiName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "guis/", 0, ".gui", 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_SaveGame(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_SaveGame(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "SaveGames/", 1, ".save", 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_DemoName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_DemoName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "demos/", 1, ".demo", 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_String<&char const * * imageFilter>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_String<&char const * * imageFilter>(
        const idCmdArgs *args,
        void (__cdecl *callback)(const char *))
{
  const char *v2; // eax
  const char **v3; // esi
  const char *v4; // ecx
  const char *v5; // eax

  v2 = imageFilter[0];
  if ( imageFilter[0] )
  {
    v3 = imageFilter;
    do
    {
      if ( args->argc <= 0 )
        v4 = &entityFilter;
      else
        v4 = args->argv[0];
      v5 = va("%s %s", v4, v2);
      callback(v5);
      v2 = v3[1];
      ++v3;
    }
    while ( v2 );
  }
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_ImageName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_ImageName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "/", 0, ".tga", ".dds", ".jpg", ".pcx", 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_VideoName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_VideoName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "video/", 0, ".roq", 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_StandaloneVideoName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_StandaloneVideoName(
        const idCmdArgs *args,
        void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "video/", 0, ".wmv", 0);
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_String<&char const * * r_rendererArgs>(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_String<&char const * * r_rendererArgs>(
        const idCmdArgs *args,
        void (__cdecl *callback)(const char *))
{
  const char *v2; // eax
  const char **v3; // esi
  const char *v4; // ecx
  const char *v5; // eax

  v2 = r_rendererArgs[0];
  if ( r_rendererArgs[0] )
  {
    v3 = r_rendererArgs;
    do
    {
      if ( args->argc <= 0 )
        v4 = &entityFilter;
      else
        v4 = args->argv[0];
      v5 = va("%s %s", v4, v2);
      callback(v5);
      v2 = v3[1];
      ++v3;
    }
    while ( v2 );
  }
}

// FUNC: public: static void __cdecl idCmdSystem::ArgCompletion_SoundName(class idCmdArgs const &,void (__cdecl *)(char const *))
void __cdecl idCmdSystem::ArgCompletion_SoundName(const idCmdArgs *args, void (__cdecl *callback)(const char *))
{
  cmdSystem->ArgCompletion_FolderExtension(cmdSystem, args, callback, "sound/", 0, ".wav", ".ogg", 0);
}
