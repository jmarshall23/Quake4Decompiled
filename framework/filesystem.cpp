
// FUNC: private: int __thiscall idFileSystemLocal::DirectFileLength(struct _iobuf *)
int __thiscall idFileSystemLocal::DirectFileLength(idFileSystemLocal *this, _iobuf *o)
{
  int v2; // edi
  int v3; // ebx

  v2 = sys->FTell(sys, o);
  sys->FSeek(sys, o, 0, 2);
  v3 = sys->FTell(sys, o);
  sys->FSeek(sys, o, v2, 0);
  return v3;
}

// FUNC: public: virtual int __thiscall idFileSystemLocal::RemoveExplicitFile(char const *)
int __thiscall idFileSystemLocal::RemoveExplicitFile(idFileSystemLocal *this, const char *ospath)
{
  return remove(ospath);
}

// FUNC: public: virtual int __thiscall idFileSystemLocal::ReadFile(char const *,void * *,unsigned int *)
int __thiscall idFileSystemLocal::ReadFile(
        idFileSystemLocal *this,
        const char *relativePath,
        void **buffer,
        unsigned int *timestamp)
{
  unsigned int v6; // ebp
  char *v7; // eax
  const char *v8; // ecx
  void *v9; // esi
  int v10; // eax
  idFile *v12; // eax
  idFile *v13; // edi
  void *v14; // ebp
  int v15; // [esp+14h] [ebp-18h]
  int len; // [esp+28h] [ebp-4h] BYREF
  char buffera; // [esp+34h] [ebp+8h]

  if ( !this->searchPaths )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  if ( !relativePath || !*relativePath )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFileSystemLocal::ReadFile with empty name\n");
  if ( timestamp )
    *timestamp = -1;
  if ( buffer )
    *buffer = 0;
  v6 = strlen(relativePath);
  v7 = strstr(relativePath, ".cfg");
  v8 = &relativePath[v6 - 4];
  if ( v7 == v8 )
  {
    v8 = (const char *)eventLoop;
    buffera = 1;
    if ( eventLoop && idEventLoop::JournalLevel(eventLoop) == 2 )
    {
      ++this->loadCount;
      ++this->loadStack;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
        common.type,
        "Loading %s from journal file.\n",
        relativePath);
      len = 0;
      if ( eventLoop->com_journalDataFile->Read(eventLoop->com_journalDataFile, &len, 4) == 4 )
      {
        v9 = Mem_ClearedAlloc(len + 1, 0xBu);
        *buffer = v9;
        v10 = eventLoop->com_journalDataFile->Read(eventLoop->com_journalDataFile, v9, len);
        if ( v10 != len )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
            common.type,
            "Read from journalDataFile failed");
        *((_BYTE *)v9 + len) = 0;
        return len;
      }
      goto LABEL_20;
    }
  }
  else
  {
    buffera = 0;
  }
  LOBYTE(v8) = buffer != 0;
  v12 = this->OpenFileRead(this, relativePath, v8, 0);
  v13 = v12;
  if ( !v12 )
  {
    if ( !buffer )
      return -1;
LABEL_20:
    *buffer = 0;
    return -1;
  }
  len = v12->Length(v12);
  if ( timestamp )
    *timestamp = v13->Timestamp(v13);
  if ( buffer )
  {
    ++this->loadCount;
    ++this->loadStack;
    v14 = Mem_ClearedAlloc(len + 1, 0xBu);
    v15 = len;
    *buffer = v14;
    v13->Read(v13, v14, v15);
    *((_BYTE *)v14 + len) = 0;
    this->CloseFile(this, v13);
    if ( buffera && eventLoop && idEventLoop::JournalLevel(eventLoop) == 1 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
        common.type,
        "Writing %s to journal file.\n",
        relativePath);
      eventLoop->com_journalDataFile->Write(eventLoop->com_journalDataFile, &len, 4);
      eventLoop->com_journalDataFile->Write(eventLoop->com_journalDataFile, v14, len);
      eventLoop->com_journalDataFile->Flush(eventLoop->com_journalDataFile);
    }
    return len;
  }
  else
  {
    this->CloseFile(this, v13);
    return len;
  }
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::FreeFile(void *)
void __thiscall idFileSystemLocal::FreeFile(idFileSystemLocal *this, void *buffer)
{
  if ( !this->searchPaths )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  if ( !buffer )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFileSystemLocal::FreeFile( NULL )");
  --this->loadStack;
  Mem_Free(buffer);
}

// FUNC: public: virtual unsigned int __thiscall idFileSystemLocal::GetOSMask(void)
char __thiscall idFileSystemLocal::GetOSMask(idFileSystemLocal *this)
{
  int v1; // eax

  v1 = fileSystemLocal.gamePakForOS[0] != 0;
  if ( fileSystemLocal.gamePakForOS[1] )
    LOBYTE(v1) = v1 | 2;
  if ( fileSystemLocal.gamePakForOS[2] )
    LOBYTE(v1) = v1 | 4;
  if ( fileSystemLocal.gamePakForOS[3] )
    LOBYTE(v1) = v1 | 8;
  if ( fileSystemLocal.gamePakForOS[4] )
    LOBYTE(v1) = v1 | 0x10;
  if ( fileSystemLocal.gamePakForOS[5] )
    LOBYTE(v1) = v1 | 0x20;
  if ( !v1 )
    LOBYTE(v1) = -1;
  return v1;
}

// FUNC: public: virtual bool __thiscall idFileSystemLocal::IsInitialized(void)const
BOOL __thiscall idFileSystemLocal::IsInitialized(idFileSystemLocal *this)
{
  return this->searchPaths != 0;
}

// FUNC: private: bool __thiscall idFileSystemLocal::FileAllowedFromDir(char const *)
bool __thiscall idFileSystemLocal::FileAllowedFromDir(idFileSystemLocal *this, char *path)
{
  unsigned int v2; // esi
  const char *v3; // ebx

  v2 = strlen(path);
  v3 = &path[v2 - 4];
  return !idStr::Cmp(v3, ".cfg")
      || !idStr::Cmp(v3, ".dat")
      || !idStr::Cmp(v3, ".dll")
      || !idStr::Cmp(&path[v2 - 3], ".so")
      || v2 > 6 && !idStr::Cmp(&path[v2 - 6], ".dylib")
      || v2 > 0xA && !idStr::Cmp(&path[v2 - 10], ".scriptcfg")
      || v2 > 8 && !idStr::Cmp(&path[v2 - 8], ".netdemo")
      || strstr(path, "savegames") == path
      && (!idStr::Cmp(v3, ".tga") || !idStr::Cmp(v3, ".txt") || !idStr::Cmp(&path[v2 - 5], ".save"))
      || strstr(path, "screenshots") == path && !idStr::Cmp(v3, ".tga")
      || strstr(path, "maps/game") == path && !idStr::Cmp(v3, ".tga")
      || strstr(path, "guis/assets/splash/addon") == path && !idStr::Cmp(v3, ".tga");
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::OpenFileRead(char const *,bool,char const *)
idFile *__thiscall idFileSystemLocal::OpenFileRead(
        idFileSystemLocal *this,
        const char *relativePath,
        BOOL allowCopyFiles,
        const char *gamedir)
{
  return this->OpenFileReadFlags(this, relativePath, 3, 0, allowCopyFiles, gamedir);
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::OpenFileByMode(char const *,enum fsMode_t)
idFile *__thiscall idFileSystemLocal::OpenFileByMode(idFileSystemLocal *this, const char *relativePath, fsMode_t mode)
{
  switch ( mode )
  {
    case FS_READ:
      return this->OpenFileRead(this, relativePath, 1, 0);
    case FS_WRITE:
      return this->OpenFileWrite(this, relativePath, "fs_savepath", 0);
    case FS_APPEND:
      return this->OpenFileAppend(this, relativePath, 1, "fs_basepath");
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
    common.type,
    "idFileSystemLocal::OpenFileByMode: bad mode");
  return 0;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::CloseFile(class idFile *)
void __thiscall idFileSystemLocal::CloseFile(idFileSystemLocal *this, idFile *f)
{
  if ( !this->searchPaths )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  if ( f )
    ((void (__thiscall *)(idFile *, int))f->~idFile)(f, 1);
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::BackgroundDownload(struct backgroundDownload_s *)
void __thiscall idFileSystemLocal::BackgroundDownload(idFileSystemLocal *this, backgroundDownload_s *bgl)
{
  if ( bgl->opcode != DLTYPE_FILE
    || __RTDynamicCast(bgl->f, 0, &idFile `RTTI Type Descriptor', &idFile_Permanent `RTTI Type Descriptor', 0) )
  {
    Sys_EnterCriticalSection(2);
    bgl->next = this->backgroundDownloads;
    this->backgroundDownloads = bgl;
    Sys_TriggerEvent(0);
    Sys_LeaveCriticalSection(2);
  }
  else
  {
    bgl->f->Seek(bgl->f, bgl->file.position, FS_SEEK_SET);
    bgl->f->Read(bgl->f, bgl->file.buffer, bgl->file.length);
    bgl->completed = 1;
  }
}

// FUNC: private: int __thiscall idFileSystemLocal::GetFileChecksum(class idFile *)
unsigned int __thiscall idFileSystemLocal::GetFileChecksum(idFileSystemLocal *this, idFile *file)
{
  int v3; // edi
  void *v4; // ebx
  unsigned int v5; // esi

  file->Seek(file, 0, FS_SEEK_END);
  v3 = file->Tell(file);
  file->Seek(file, 0, FS_SEEK_SET);
  v4 = Mem_Alloc(v3, 0xBu);
  if ( file->Read(file, v4, v3) != v3 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Short read in idFileSystemLocal::GetFileChecksum()\n");
  v5 = MD4_BlockChecksum(v4, v3);
  Mem_Free(v4);
  return v5;
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::MakeTemporaryFile(void)
idFile *__thiscall idFileSystemLocal::MakeTemporaryFile(idFileSystemLocal *this)
{
  _iobuf *v1; // edi
  int *v2; // eax
  int v3; // esi
  char *v4; // eax
  idFile_Permanent *v6; // eax
  int v7; // eax
  int v8; // esi

  v1 = tmpfile();
  if ( v1 )
  {
    v6 = (idFile_Permanent *)Memory::Allocate(0x54u);
    if ( v6 )
    {
      idFile_Permanent::idFile_Permanent(v6);
      v8 = v7;
    }
    else
    {
      v8 = 0;
    }
    *(_DWORD *)(v8 + 76) = v1;
    idStr::operator=((idStr *)(v8 + 4), "<tempfile>");
    idStr::operator=((idStr *)(v8 + 36), "<tempfile>");
    *(_DWORD *)(v8 + 68) = 3;
    *(_DWORD *)(v8 + 72) = 0;
    return (idFile *)v8;
  }
  else
  {
    v2 = _errno();
    v3 = *(_DWORD *)common.type;
    v4 = strerror(*v2);
    (*(void (**)(netadrtype_t, const char *, ...))(v3 + 136))(
      common.type,
      "idFileSystem::MakeTemporaryFile failed: %s",
      v4);
    return 0;
  }
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::SetIsFileLoadingAllowed(bool)
void __thiscall idFileSystemLocal::SetIsFileLoadingAllowed(idFileSystemLocal *this, bool mode)
{
  this->isFileLoadingAllowed = mode;
}

// FUNC: bool __cdecl excludeExtension(struct pureExclusion_s const &,int,class idStr const &)
bool __cdecl excludeExtension(const pureExclusion_s *excl, int l, const idStr *name)
{
  int extLen; // ecx

  extLen = excl->extLen;
  return l > extLen && !idStr::Icmp(&name->data[l - extLen], excl->ext);
}

// FUNC: bool __cdecl excludePathPrefixAndExtension(struct pureExclusion_s const &,int,class idStr const &)
bool __cdecl excludePathPrefixAndExtension(const pureExclusion_s *excl, int l, const idStr *name)
{
  return l > excl->nameLen
      && !idStr::Icmp(&name->data[l - excl->extLen], excl->ext)
      && !idStr::IcmpnPath(name->data, excl->name, strlen(excl->name));
}

// FUNC: bool __cdecl excludeFullName(struct pureExclusion_s const &,int,class idStr const &)
bool __cdecl excludeFullName(const pureExclusion_s *excl, int l, const idStr *name)
{
  return l == excl->nameLen && !idStr::Icmp(name->data, excl->name);
}

// FUNC: public: __thiscall idInitExclusions::idInitExclusions(void)
void __thiscall idInitExclusions::idInitExclusions(idInitExclusions *this)
{
  int v1; // ebx
  int v2; // esi
  const char *name; // edi
  int v4; // edx
  const char *ext; // edi
  int v6; // edx

  if ( pureExclusions[0].func )
  {
    v1 = 0;
    v2 = 0;
    do
    {
      name = pureExclusions[v2].name;
      if ( name )
      {
        v4 = 0;
        if ( *name )
        {
          do
            ++v4;
          while ( name[v4] );
        }
        pureExclusions[v2].nameLen = v4;
      }
      ext = pureExclusions[v2].ext;
      if ( ext )
      {
        v6 = 0;
        if ( *ext )
        {
          do
            ++v6;
          while ( ext[v6] );
        }
        *(int *)((char *)&pureExclusions[0].extLen + v1) = v6;
      }
      v1 = ++v2 * 20;
    }
    while ( pureExclusions[v2].func );
  }
}

// FUNC: private: long __thiscall idFileSystemLocal::HashFileName(char const *)const
int __thiscall idFileSystemLocal::HashFileName(idFileSystemLocal *this, const char *fname)
{
  const char *v2; // edx
  unsigned __int8 v3; // cl
  __int16 i; // ax
  __int16 v5; // di

  v2 = fname;
  v3 = *fname;
  for ( i = 0; v3; i += v5 )
  {
    if ( idStr::lowerCaseCharacter[v3] )
      v3 = idStr::lowerCaseCharacter[v3];
    if ( v3 == 46 )
      break;
    if ( v3 == 92 )
      v3 = 47;
    v5 = (char)v3 * (119 - (_WORD)fname + (_WORD)v2);
    v3 = *++v2;
  }
  return i & 0x3FF;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::CreateOSPath(char const *)
void __thiscall idFileSystemLocal::CreateOSPath(idFileSystemLocal *this, const char *OSPath)
{
  const char *v2; // eax
  int v3; // edi
  int v4; // eax
  char *data; // edx
  const char *v6; // ecx
  char v7; // al
  char *v8; // esi
  bool v9; // zf
  idStr path; // [esp+4h] [ebp-2Ch] BYREF
  int v11; // [esp+2Ch] [ebp-4h]

  if ( !strstr(OSPath, "..") && !strstr(OSPath, "::") )
  {
    path.len = 0;
    path.alloced = 20;
    path.data = path.baseBuffer;
    path.baseBuffer[0] = 0;
    if ( OSPath )
    {
      v2 = &OSPath[strlen(OSPath) + 1];
      v3 = v2 - (OSPath + 1);
      v4 = v2 - OSPath;
      if ( v4 > 20 )
        idStr::ReAllocate(&path, v4, 1);
      data = path.data;
      v6 = OSPath;
      do
      {
        v7 = *v6;
        *data++ = *v6++;
      }
      while ( v7 );
      path.len = v3;
    }
    v8 = path.data + 1;
    v9 = path.data[1] == 0;
    v11 = 0;
    if ( !v9 )
    {
      do
      {
        if ( *v8 == 47 )
        {
          *v8 = 0;
          Sys_Mkdir(path.data);
          *v8 = 47;
        }
        ++v8;
      }
      while ( *v8 );
    }
    v11 = -1;
    idStr::FreeData(&path);
  }
}

// FUNC: public: virtual char const * __thiscall idFileSystemLocal::OSPathToRelativePath(char const *)
char *__thiscall idFileSystemLocal::OSPathToRelativePath(idFileSystemLocal *this, char *OSPath)
{
  const char *v2; // edi
  char *i; // esi
  char v4; // al
  char v5; // cl
  const char *value; // ebx
  int j; // ebp
  char v8; // dl
  char v9; // al
  char *v10; // eax
  char *v11; // eax
  char *v12; // edx
  char v13; // cl

  v2 = OSPath;
  for ( i = strstr(OSPath, "q4base"); i; i = strstr(i + 1, "q4base") )
  {
    v4 = 0;
    if ( i > OSPath )
      v4 = *(i - 1);
    v5 = i[6];
    if ( (v4 == 47 || v4 == 92) && (v5 == 47 || v5 == 92) )
      break;
  }
  value = 0;
  for ( j = 0; j < 2; ++j )
  {
    if ( j )
    {
      if ( j == 1 )
        value = idFileSystemLocal::fs_game_base.internalVar->value;
    }
    else
    {
      value = idFileSystemLocal::fs_game.internalVar->value;
    }
    if ( !i )
    {
      if ( value )
      {
        if ( strlen(value) )
        {
          i = strstr(v2, value);
          if ( i )
          {
            while ( 1 )
            {
              v8 = 0;
              if ( i > v2 )
                v8 = *(i - 1);
              v9 = i[strlen(value)];
              if ( (v8 == 47 || v8 == 92) && (v9 == 47 || v9 == 92) )
                break;
              i = strstr(i + 1, value);
              if ( !i )
                break;
              v2 = OSPath;
            }
            v2 = OSPath;
          }
        }
      }
    }
  }
  if ( i && ((v10 = strstr(i, "/")) != 0 || (v10 = strstr(i, "\\")) != 0) )
  {
    v11 = v10 + 1;
    v12 = (char *)(relativePath - v11);
    do
    {
      v13 = *v11;
      v11[(_DWORD)v12] = *v11;
      ++v11;
    }
    while ( v13 );
    if ( idFileSystemLocal::fs_debug.internalVar->integerValue > 1 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idFileSystem::OSPathToRelativePath: %s becomes %s\n",
        v2,
        relativePath);
      return relativePath;
    }
  }
  else
  {
    if ( com_developer.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "idFileSystem::OSPathToRelativePath failed on %s",
        v2);
    relativePath[0] = 0;
  }
  return relativePath;
}

// FUNC: public: virtual char const * __thiscall idFileSystemLocal::RelativePathToOSPath(char const *,char const *)
const char *__thiscall idFileSystemLocal::RelativePathToOSPath(
        idFileSystemLocal *this,
        const char *relativePath,
        const char *basePath)
{
  const char *value; // eax

  value = cvarSystem->GetCVarString(cvarSystem, basePath);
  if ( !*value )
    value = idFileSystemLocal::fs_savepath.internalVar->value;
  return this->BuildOSPath(this, value, this->gameFolder.data, relativePath);
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::RemoveFile(char const *,char const *)
void __thiscall idFileSystemLocal::RemoveFile(idFileSystemLocal *this, const char *relativePath, const char *basePath)
{
  const char *value; // eax
  char *v5; // eax
  char *v6; // eax
  const char *v7; // eax
  idStr OSPath; // [esp+10h] [ebp-2Ch] BYREF
  int v9; // [esp+38h] [ebp-4h]

  OSPath.len = 0;
  OSPath.alloced = 20;
  OSPath.data = OSPath.baseBuffer;
  OSPath.baseBuffer[0] = 0;
  v9 = 0;
  if ( idStr::Cmp(basePath, "fs_savepath") )
  {
    v7 = cvarSystem->GetCVarString(cvarSystem, basePath);
    v6 = (char *)this->BuildOSPath(this, v7, this->gameFolder.data, relativePath);
  }
  else
  {
    value = idFileSystemLocal::fs_devpath.internalVar->value;
    if ( *value )
    {
      v5 = (char *)this->BuildOSPath(this, value, this->gameFolder.data, relativePath);
      idStr::operator=(&OSPath, v5);
      remove(OSPath.data);
    }
    v6 = (char *)this->BuildOSPath(
                   this,
                   idFileSystemLocal::fs_savepath.internalVar->value,
                   this->gameFolder.data,
                   relativePath);
  }
  idStr::operator=(&OSPath, v6);
  remove(OSPath.data);
  this->ClearDirCache(this);
  v9 = -1;
  idStr::FreeData(&OSPath);
}

// FUNC: public: virtual bool __thiscall idFileSystemLocal::IsPakLoaded(char const *)
char __thiscall idFileSystemLocal::IsPakLoaded(idFileSystemLocal *this, const char *path)
{
  searchpath_s *searchPaths; // esi

  searchPaths = this->searchPaths;
  if ( !searchPaths )
    return 0;
  while ( !searchPaths->pack || idStr::Cmp(searchPaths->pack->pakFilename.data, path) )
  {
    searchPaths = searchPaths->next;
    if ( !searchPaths )
      return 0;
  }
  return 1;
}

// FUNC: public: static void __cdecl idFileSystemLocal::TouchFile_f(class idCmdArgs const &)
void __cdecl idFileSystemLocal::TouchFile_f(const idCmdArgs *args)
{
  idFile *v1; // esi

  if ( args->argc == 2 )
  {
    v1 = fileSystemLocal.OpenFileReadFlags(&fileSystemLocal, args->argv[1], 3, 0, 1, 0);
    if ( v1 )
    {
      if ( !fileSystemLocal.searchPaths )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
          common.type,
          "Filesystem call made without initialization\n");
      ((void (__thiscall *)(idFile *, int))v1->~idFile)(v1, 1);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Usage: touchFile <file>\n");
  }
}

// FUNC: public: static void __cdecl idFileSystemLocal::TouchFileList_f(class idCmdArgs const &)
void __cdecl idFileSystemLocal::TouchFileList_f(const idCmdArgs *args)
{
  bool v1; // cc
  const char *v2; // eax
  int v3; // eax
  const char *v4; // ecx
  idFile *v5; // esi
  const char *buffer; // [esp+24h] [ebp-120h] BYREF
  idToken token; // [esp+28h] [ebp-11Ch] BYREF
  idParser src; // [esp+78h] [ebp-CCh] BYREF
  int v9; // [esp+140h] [ebp-4h]

  if ( args->argc == 2 )
  {
    buffer = 0;
    idParser::idParser(&src, 6156);
    v1 = args->argc <= 1;
    v9 = 0;
    if ( v1 )
      v2 = &entityFilter;
    else
      v2 = args->argv[1];
    if ( fileSystem->ReadFile(fileSystem, v2, (void **)&buffer, 0) && buffer )
    {
      v3 = strlen(buffer);
      v4 = args->argc <= 1 ? &entityFilter : args->argv[1];
      idParser::LoadMemory(&src, buffer, v3, v4);
      if ( src.loaded )
      {
        token.floatvalue = 0.0;
        token.len = 0;
        token.alloced = 20;
        token.data = token.baseBuffer;
        token.baseBuffer[0] = 0;
        LOBYTE(v9) = 1;
        while ( idParser::ReadToken(&src, &token) )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s\n", token.data);
          session->UpdateScreen(session, 1);
          v5 = fileSystemLocal.OpenFileReadFlags(&fileSystemLocal, token.data, 3, 0, 1, 0);
          if ( v5 )
          {
            if ( !fileSystemLocal.searchPaths )
              (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
                common.type,
                "Filesystem call made without initialization\n");
            ((void (__thiscall *)(idFile *, int))v5->~idFile)(v5, 1);
          }
        }
        LOBYTE(v9) = 0;
        idStr::FreeData(&token);
      }
    }
    v9 = -1;
    idParser::~idParser(&src);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Usage: touchFileList <filename>\n");
  }
}

// FUNC: private: void __thiscall idFileSystemLocal::FollowAddonDependencies(struct pack_t *)
void __thiscall idFileSystemLocal::FollowAddonDependencies(idFileSystemLocal *this, pack_t *pak)
{
  addonInfo_t *addon_info; // eax
  int num; // eax
  pack_t *v6; // ebp
  searchpath_s *searchPaths; // eax
  int v8; // edx
  pack_t *pack; // edi
  int v10; // edx
  int v11; // eax
  int *list; // ecx
  int v13; // ecx
  int v14; // ecx
  int *v15; // ecx
  char *data; // [esp-10h] [ebp-1Ch]
  int checksum; // [esp-Ch] [ebp-18h]
  int v18; // [esp+8h] [ebp-4h]
  pack_t *paka; // [esp+10h] [ebp+4h]

  addon_info = pak->addon_info;
  if ( addon_info )
  {
    num = addon_info->depends.num;
    v18 = num;
    if ( num )
    {
      v6 = 0;
      paka = 0;
      if ( num > 0 )
      {
        do
        {
          searchPaths = this->searchPaths;
          v8 = pak->addon_info->depends.list[(_DWORD)v6];
          if ( searchPaths )
          {
            while ( !searchPaths->pack || searchPaths->pack->checksum != v8 )
            {
              searchPaths = searchPaths->next;
              if ( !searchPaths )
                goto LABEL_8;
            }
          }
          else
          {
LABEL_8:
            searchPaths = this->addonPaks;
            if ( !searchPaths )
              goto LABEL_11;
            while ( searchPaths->pack->checksum != v8 )
            {
              searchPaths = searchPaths->next;
              if ( !searchPaths )
                goto LABEL_11;
            }
          }
          pack = searchPaths->pack;
          if ( searchPaths->pack )
          {
            if ( !pack->addon_search )
            {
              v10 = this->addonChecksums.num;
              v11 = 0;
              if ( v10 > 0 )
              {
                list = this->addonChecksums.list;
                while ( *list != pack->checksum )
                {
                  ++v11;
                  ++list;
                  if ( v11 >= v10 )
                    goto LABEL_25;
                }
                if ( v11 >= 0 )
                {
                  v13 = this->addonChecksums.num;
                  if ( v11 < v13 )
                  {
                    v14 = v13 - 1;
                    for ( this->addonChecksums.num = v14; v11 < this->addonChecksums.num; *v15 = v15[1] )
                      v15 = &this->addonChecksums.list[v11++];
                  }
                }
              }
LABEL_25:
              checksum = pack->checksum;
              data = pack->pakFilename.data;
              pack->addon_search = 1;
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                common.type,
                "Addon pk4 %s 0x%x depends on pak %s 0x%x, will be searched\n",
                pak->pakFilename.data,
                pak->checksum,
                data,
                checksum);
              idFileSystemLocal::FollowAddonDependencies(this, pack);
              v6 = paka;
            }
            goto LABEL_12;
          }
LABEL_11:
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "Addon pk4 %s 0x%x depends on unknown pak 0x%x\n",
            pak->pakFilename.data,
            pak->checksum,
            v8);
LABEL_12:
          v6 = (pack_t *)((char *)v6 + 1);
          paka = v6;
        }
        while ( (int)v6 < v18 );
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::ClearPureChecksums(void)
void __thiscall idFileSystemLocal::ClearPureChecksums(idFileSystemLocal *this)
{
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
    common.type,
    "Cleared pure server lock\n");
  if ( this->serverPaks.list )
    Memory::Free(this->serverPaks.list);
  this->serverPaks.list = 0;
  this->serverPaks.num = 0;
  this->serverPaks.size = 0;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::GetPureServerChecksums(int * const,int,int *)
void __thiscall idFileSystemLocal::GetPureServerChecksums(
        idFileSystemLocal *this,
        int *checksums,
        int OS,
        int *_gamePakChecksum)
{
  int i; // eax

  for ( i = 0; i < this->serverPaks.num; ++i )
    checksums[i] = this->serverPaks.list[i]->checksum;
  checksums[i] = 0;
  if ( _gamePakChecksum )
  {
    if ( OS < 0 )
      *_gamePakChecksum = this->gamePakChecksum;
    else
      *_gamePakChecksum = this->gamePakForOS[OS];
  }
}

// FUNC: private: enum pureStatus_t __thiscall idFileSystemLocal::GetPackStatus(struct pack_t *)
int __thiscall idFileSystemLocal::GetPackStatus(idFileSystemLocal *this, pack_t *pak)
{
  pureStatus_t pureStatus; // esi
  fileInPack_s *v4; // edi
  int len; // ebp
  bool (__cdecl **p_func)(const pureExclusion_s *, int, const idStr *); // eax
  bool (__cdecl **v7)(const pureExclusion_s *, int, const idStr *); // esi
  int v8; // eax
  fileInPack_s **hashTable; // [esp+8h] [ebp-38h]
  int i; // [esp+Ch] [ebp-34h]
  int hashindex; // [esp+10h] [ebp-30h]
  idStr name; // [esp+14h] [ebp-2Ch] BYREF
  int v13; // [esp+3Ch] [ebp-4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  pureStatus = pak->pureStatus;
  v13 = 0;
  if ( pureStatus )
  {
    v13 = -1;
    idStr::FreeData(&name);
    return pureStatus;
  }
  else
  {
    i = 0;
    hashindex = 0;
    hashTable = pak->hashTable;
    while ( 1 )
    {
      v4 = *hashTable;
      if ( *hashTable )
        break;
LABEL_11:
      ++hashTable;
      if ( ++hashindex >= 1024 )
        goto LABEL_12;
    }
    while ( 1 )
    {
      len = v4->name.len;
      if ( !pureExclusions[0].func )
        break;
      p_func = &pureExclusions[0].func;
      v7 = &pureExclusions[0].func;
      while ( !(*p_func)((const pureExclusion_s *)(v7 - 4), len, &v4->name) )
      {
        v7 += 5;
        p_func = v7;
        if ( !*v7 )
          goto LABEL_12;
      }
      v4 = v4->next;
      ++i;
      if ( !v4 )
        goto LABEL_11;
    }
LABEL_12:
    if ( i == pak->numfiles )
    {
      pak->pureStatus = PURE_NEVER;
      v13 = -1;
      idStr::FreeData(&name);
      return 3;
    }
    else
    {
      idStr::ExtractFileName(&pak->pakFilename, &name);
      v8 = idStr::IcmpnPath(name.data, "pak", 3);
      v13 = -1;
      if ( v8 )
      {
        pak->pureStatus = PURE_NEUTRAL;
        idStr::FreeData(&name);
        return 1;
      }
      else
      {
        pak->pureStatus = PURE_ALWAYS;
        idStr::FreeData(&name);
        return 2;
      }
    }
  }
}

// FUNC: unsigned int __cdecl BackgroundDownloadThread(void *)
void __cdecl __noreturn BackgroundDownloadThread()
{
  backgroundDownload_s *backgroundDownloads; // esi
  bool v1; // zf

  while ( 1 )
  {
    while ( 1 )
    {
      Sys_EnterCriticalSection(2);
      backgroundDownloads = fileSystemLocal.backgroundDownloads;
      if ( fileSystemLocal.backgroundDownloads )
        break;
      Sys_LeaveCriticalSection(2);
      Sys_WaitForEvent(0);
    }
    fileSystemLocal.backgroundDownloads = fileSystemLocal.backgroundDownloads->next;
    Sys_LeaveCriticalSection(2);
    v1 = backgroundDownloads->opcode == DLTYPE_FILE;
    backgroundDownloads->next = 0;
    if ( v1 )
      _read((int)backgroundDownloads->f[19].Write, backgroundDownloads->file.buffer, backgroundDownloads->file.length);
    else
      backgroundDownloads->url.status = DL_FAILED;
    backgroundDownloads->completed = 1;
  }
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::StartBackgroundDownloadThread(void)
void __thiscall idFileSystemLocal::StartBackgroundDownloadThread(idFileSystemLocal *this)
{
  if ( this->backgroundThread.threadHandle )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "background thread already running\n");
  }
  else
  {
    Sys_CreateThread(
      BackgroundDownloadThread,
      0,
      THREAD_NORMAL,
      &this->backgroundThread,
      "backgroundDownload",
      g_threads,
      &g_thread_count);
    if ( !this->backgroundThread.threadHandle )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "idFileSystemLocal::StartBackgroundDownloadThread: failed");
  }
}

// FUNC: public: virtual bool __thiscall idFileSystemLocal::PerformingCopyFiles(void)const
BOOL __thiscall idFileSystemLocal::PerformingCopyFiles(idFileSystemLocal *this)
{
  return idFileSystemLocal::fs_copyfiles.internalVar->integerValue > 0;
}

// FUNC: public: virtual bool __thiscall idFileSystemLocal::OSpathToImportPath(char const *,class idStr &,bool)
char __thiscall idFileSystemLocal::OSpathToImportPath(
        idFileSystemLocal *this,
        char *osPath,
        idStr *iPath,
        bool stripTemp)
{
  unsigned int v4; // kr00_4
  char *v5; // esi

  if ( idStr::Icmpn(
         osPath,
         idFileSystemLocal::fs_importpath.internalVar->value,
         strlen(idFileSystemLocal::fs_importpath.internalVar->value)) )
  {
    idStr::operator=(iPath, osPath);
    return 0;
  }
  else
  {
    v4 = strlen(idFileSystemLocal::fs_importpath.internalVar->value);
    v5 = &osPath[v4];
    if ( osPath[v4] == 47 || osPath[v4] == 92 )
      ++v5;
    if ( stripTemp )
    {
      if ( !idStr::Icmpn(v5, "work", 4) )
        v5 += 4;
      if ( !idStr::Icmpn(v5, "final", 5) )
        v5 += 5;
      if ( *v5 == 47 || *v5 == 92 )
        ++v5;
    }
    idStr::operator=(iPath, v5);
    return 1;
  }
}

// FUNC: public: virtual int __thiscall idFileSystemLocal::GetNumMaps(void)
int __thiscall idFileSystemLocal::GetNumMaps(idFileSystemLocal *this)
{
  int result; // eax
  searchpath_s *addonPaks; // edx
  int i; // esi
  pack_t *pack; // ecx
  addonInfo_t *addon_info; // ecx

  result = declManager->GetNumDecls(declManager, DECL_MAPDEF);
  addonPaks = 0;
  for ( i = 0; i < 2; ++i )
  {
    if ( i )
    {
      if ( i == 1 )
        addonPaks = this->addonPaks;
    }
    else
    {
      addonPaks = this->searchPaths;
    }
    for ( ; addonPaks; addonPaks = addonPaks->next )
    {
      pack = addonPaks->pack;
      if ( addonPaks->pack && pack->addon )
      {
        addon_info = pack->addon_info;
        if ( addon_info )
          result += addon_info->mapDecls.num;
      }
    }
  }
  return result;
}

// FUNC: public: virtual class idDict const * __thiscall idFileSystemLocal::GetMapDecl(int)
const idDict *__thiscall idFileSystemLocal::GetMapDecl(idFileSystemLocal *this, int idecl)
{
  int v3; // eax
  searchpath_s *addonPaks; // ecx
  const idDecl *v5; // esi
  const char *v6; // eax
  int v8; // edi
  int v9; // edx
  pack_t *pack; // eax
  addonInfo_t *addon_info; // eax
  int num; // eax

  v3 = declManager->GetNumDecls(declManager, DECL_MAPDEF);
  addonPaks = 0;
  if ( idecl >= v3 )
  {
    v8 = idecl - v3;
    v9 = 0;
    while ( 1 )
    {
      if ( v9 )
      {
        if ( v9 == 1 )
          addonPaks = this->addonPaks;
      }
      else
      {
        addonPaks = this->searchPaths;
      }
      if ( addonPaks )
        break;
LABEL_17:
      if ( ++v9 >= 2 )
        return 0;
    }
    while ( 1 )
    {
      pack = addonPaks->pack;
      if ( addonPaks->pack )
      {
        if ( pack->addon )
        {
          addon_info = pack->addon_info;
          if ( addon_info )
          {
            num = addon_info->mapDecls.num;
            if ( v8 < num )
            {
              idDict::operator=(&this->mapDict, addonPaks->pack->addon_info->mapDecls.list[v8]);
              return &this->mapDict;
            }
            v8 -= num;
          }
        }
      }
      addonPaks = addonPaks->next;
      if ( !addonPaks )
        goto LABEL_17;
    }
  }
  v5 = declManager->DeclByIndex(declManager, 17, idecl, 1);
  if ( !v5 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idFileSystemLocal::GetMapDecl %d: not found\n",
      idecl);
  idDict::operator=(&this->mapDict, (idDict *)&v5[1]);
  v6 = v5->base->GetName(v5->base);
  idDict::Set(&this->mapDict, "path", v6);
  return &this->mapDict;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::FindMapScreenshot(char const *,char *,int)
void __thiscall idFileSystemLocal::FindMapScreenshot(idFileSystemLocal *this, const char *path, char *buf, int len)
{
  const char *v5; // eax
  int v6; // ebx
  int v7; // eax
  char *data; // edx
  const char *v9; // ecx
  char v10; // al
  idFile *v11; // eax
  idFile *v12; // esi
  int v13; // ebx
  idStr mapname; // [esp+28h] [ebp-2Ch] BYREF
  int v15; // [esp+50h] [ebp-4h]
  char *patha; // [esp+58h] [ebp+4h]

  mapname.len = 0;
  mapname.alloced = 20;
  mapname.data = mapname.baseBuffer;
  mapname.baseBuffer[0] = 0;
  if ( path )
  {
    v5 = &path[strlen(path) + 1];
    v6 = v5 - (path + 1);
    v7 = v5 - path;
    if ( v7 > 20 )
      idStr::ReAllocate(&mapname, v7, 1);
    data = mapname.data;
    v9 = path;
    do
    {
      v10 = *v9;
      *data++ = *v9++;
    }
    while ( v10 );
    mapname.len = v6;
  }
  v15 = 0;
  idStr::StripPath(&mapname);
  idStr::StripFileExtension(&mapname);
  idStr::snPrintf(buf, len, "gfx/guis/loadscreens/%s.tga", mapname.data);
  if ( this->ReadFile(this, buf, 0, 0) == -1 )
  {
    v11 = this->OpenFileReadFlags(this, buf, 16, 0, 1, 0);
    v12 = v11;
    if ( v11 )
    {
      v13 = v11->Length(v11);
      patha = (char *)Memory::Allocate(v13);
      v12->Read(v12, patha, v13);
      this->CloseFile(this, v12);
      idStr::snPrintf(buf, len, "guis/assets/splash/addon/%s.tga", mapname.data);
      this->WriteFile(this, buf, patha, v13, "fs_savepath");
      Memory::Free(patha);
    }
    else
    {
      idStr::Copynz(buf, "gfx/guis/loadscreens/generic.tga", len);
    }
  }
  v15 = -1;
  idStr::FreeData(&mapname);
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::WriteDemoHeader(class idFile *)
void __thiscall idFileSystemLocal::WriteDemoHeader(idFileSystemLocal *this, idFile *file)
{
  int num; // eax
  int v5; // edi
  int *gamePakForOS; // ebp
  searchpath_s *searchPaths; // eax
  pack_t *pack; // edi
  int filea; // [esp+20h] [ebp+4h]

  file->WriteString(file, idFileSystemLocal::fs_game_base.internalVar->value);
  file->WriteString(file, idFileSystemLocal::fs_game.internalVar->value);
  file->WriteInt(file, this->serverPaks.num);
  num = this->serverPaks.num;
  if ( num )
  {
    v5 = 0;
    if ( num > 0 )
    {
      do
      {
        file->WriteString(file, this->serverPaks.list[v5]->pakFilename.data);
        file->WriteInt(file, this->serverPaks.list[v5++]->checksum);
      }
      while ( v5 < this->serverPaks.num );
    }
    this->UpdateGamePakChecksums(this);
    file->WriteInt(file, 0);
    gamePakForOS = this->gamePakForOS;
    filea = 6;
    do
    {
      if ( *gamePakForOS )
      {
        searchPaths = this->searchPaths;
        if ( searchPaths )
        {
          while ( !searchPaths->pack || searchPaths->pack->checksum != *gamePakForOS )
          {
            searchPaths = searchPaths->next;
            if ( !searchPaths )
              goto LABEL_11;
          }
          pack = searchPaths->pack;
        }
        else
        {
LABEL_11:
          pack = 0;
        }
        file->WriteString(file, pack->pakFilename.data);
        file->WriteInt(file, pack->checksum);
      }
      else
      {
        file->WriteString(file, &entityFilter);
        file->WriteInt(file, 0);
      }
      ++gamePakForOS;
      --filea;
    }
    while ( filea );
  }
}

// FUNC: public: virtual char const * __thiscall idFileSystemLocal::BuildOSPath(char const *,char const *,char const *)
char *__thiscall idFileSystemLocal::BuildOSPath(
        idFileSystemLocal *this,
        char *base,
        const char *game,
        char *relativePath)
{
  bool v4; // zf
  char *data; // ecx
  unsigned __int8 v6; // al
  int i; // esi
  idStr newPath; // [esp+Ch] [ebp-6Ch] BYREF
  idStr testPath; // [esp+2Ch] [ebp-4Ch] BYREF
  idStr fileName; // [esp+4Ch] [ebp-2Ch] BYREF
  int v12; // [esp+74h] [ebp-4h]

  newPath.len = 0;
  newPath.alloced = 20;
  newPath.data = newPath.baseBuffer;
  newPath.baseBuffer[0] = 0;
  v4 = idFileSystemLocal::fs_caseSensitiveOS.internalVar->integerValue == 0;
  v12 = 0;
  if ( v4 && !com_developer.internalVar->integerValue )
    goto LABEL_11;
  testPath.len = 0;
  testPath.alloced = 20;
  testPath.data = testPath.baseBuffer;
  testPath.baseBuffer[0] = 0;
  fileName.alloced = 20;
  fileName.len = 0;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  LOBYTE(v12) = 2;
  sprintf(&testPath, "%s/%s", game, relativePath);
  idStr::StripFilename(&testPath);
  if ( !idStr::HasUpper(testPath.data)
    || ((*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
          common.type,
          "Non-portable: path contains uppercase characters: %s\n",
          testPath.data),
        !idFileSystemLocal::fs_caseSensitiveOS.internalVar->integerValue) )
  {
    LOBYTE(v12) = 1;
    idStr::FreeData(&fileName);
    LOBYTE(v12) = 0;
    idStr::FreeData(&testPath);
LABEL_11:
    idStr::operator=(&newPath, base);
    idStr::StripTrailing(&newPath, 47);
    idStr::StripTrailing(&newPath, 92);
    idStr::AppendPath(&newPath, game);
    idStr::AppendPath(&newPath, relativePath);
    idStr::BackSlashesToSlashes(&newPath);
    idStr::Copynz(OSPath, newPath.data, 1024);
    goto LABEL_12;
  }
  data = testPath.data;
  v6 = *testPath.data;
  for ( i = 0; v6; v6 = testPath.data[i] )
  {
    if ( idStr::lowerCaseCharacter[v6] )
      v6 = idStr::lowerCaseCharacter[v6];
    *data = v6;
    data = &testPath.data[++i];
  }
  idStr::operator=(&fileName, relativePath);
  idStr::StripPath(&fileName);
  idStr::operator=(&newPath, base);
  idStr::AppendPath(&newPath, testPath.data);
  idStr::AppendPath(&newPath, fileName.data);
  idStr::BackSlashesToSlashes(&newPath);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "Fixed up to %s\n",
    newPath.data);
  idStr::Copynz(OSPath, newPath.data, 1024);
  LOBYTE(v12) = 1;
  idStr::FreeData(&fileName);
  LOBYTE(v12) = 0;
  idStr::FreeData(&testPath);
LABEL_12:
  v12 = -1;
  idStr::FreeData(&newPath);
  return OSPath;
}

// FUNC: public: virtual bool __thiscall idFileSystemLocal::FileIsInPAK(char const *)
char __thiscall idFileSystemLocal::FileIsInPAK(idFileSystemLocal *this, const char *relativePath)
{
  const char *v3; // ebx
  int v4; // eax
  searchpath_s *searchPaths; // ebp
  pack_t *pack; // edx
  int num; // esi
  int v8; // eax
  pack_t **list; // ecx
  fileInPack_s *v11; // esi
  int hash; // [esp+8h] [ebp-4h]

  if ( !this->searchPaths )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  v3 = relativePath;
  if ( !relativePath )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFileSystemLocal::FileIsInPAK: NULL 'relativePath' parameter passed\n");
  if ( *relativePath == 47 || *relativePath == 92 )
    v3 = ++relativePath;
  if ( strstr(v3, "..") || strstr(v3, "::") )
    return 0;
  v4 = idFileSystemLocal::HashFileName(this, v3);
  searchPaths = this->searchPaths;
  hash = v4;
  if ( !searchPaths )
    return 0;
  while ( 1 )
  {
    pack = searchPaths->pack;
    if ( searchPaths->pack && pack->hashTable[hash] )
    {
      if ( !this->serverPaks.num )
        goto LABEL_25;
      idFileSystemLocal::GetPackStatus(this, searchPaths->pack);
      pack = searchPaths->pack;
      if ( searchPaths->pack->pureStatus == PURE_NEVER )
        goto LABEL_25;
      num = this->serverPaks.num;
      v8 = 0;
      if ( num > 0 )
        break;
    }
LABEL_20:
    searchPaths = searchPaths->next;
    if ( !searchPaths )
      return 0;
  }
  list = this->serverPaks.list;
  while ( *list != pack )
  {
    ++v8;
    ++list;
    if ( v8 >= num )
      goto LABEL_19;
  }
  if ( v8 < 0 || !&this->serverPaks.list[v8] )
  {
LABEL_19:
    v3 = relativePath;
    goto LABEL_20;
  }
  v3 = relativePath;
LABEL_25:
  v11 = pack->hashTable[hash];
  while ( idFileSystemLocal::FilenameCompare(this, v11->name.data, v3) )
  {
    v11 = v11->next;
    if ( !v11 )
      goto LABEL_20;
  }
  return 1;
}

// FUNC: public: static void __cdecl idFileSystemLocal::Path_f(class idCmdArgs const &)
void __cdecl idFileSystemLocal::Path_f()
{
  int v0; // ecx
  searchpath_s *i; // edi
  pack_t *pack; // eax
  const char *v3; // edx
  int v4; // esi
  int v5; // eax
  char v6; // cl
  char *v7; // edx
  int v8; // eax
  char v9; // cl
  char *v10; // edx
  int v11; // eax
  int j; // esi
  searchpath_s *k; // esi
  pack_t *v14; // eax
  char *data; // ecx
  int v16; // edi
  idStr status; // [esp+Ch] [ebp-2Ch] BYREF
  int v18; // [esp+34h] [ebp-4h]

  status.len = 0;
  status.alloced = 20;
  status.data = status.baseBuffer;
  status.baseBuffer[0] = 0;
  v0 = *(_DWORD *)common.type;
  v18 = 0;
  (*(void (__cdecl **)(netadrtype_t, const char *))(v0 + 124))(common.type, "Current search path:\n");
  for ( i = fileSystemLocal.searchPaths; i; i = i->next )
  {
    pack = i->pack;
    if ( i->pack )
    {
      if ( com_developer.internalVar->integerValue )
      {
        v3 = "referenced";
        if ( !pack->referenced )
          v3 = "not referenced";
        sprintf(&status, "%s (%i files - 0x%x %s", pack->pakFilename.data, pack->numfiles, pack->checksum, v3);
        if ( i->pack->addon )
        {
          v4 = status.len + 10;
          if ( status.len + 11 > status.alloced )
            idStr::ReAllocate(&status, status.len + 11, 1);
          v5 = 0;
          v6 = 32;
          do
          {
            v7 = &status.data[v5++];
            v7[status.len] = v6;
            v6 = aAddon[v5];
          }
          while ( v6 );
        }
        else
        {
          v4 = status.len + 2;
          if ( status.len + 3 > status.alloced )
            idStr::ReAllocate(&status, status.len + 3, 1);
          v8 = 0;
          v9 = 41;
          do
          {
            v10 = &status.data[v8++];
            v10[status.len] = v9;
            v9 = asc_102A2020[v8];
          }
          while ( v9 );
        }
        status.len = v4;
        status.data[v4] = 0;
        (*(void (__cdecl **)(netadrtype_t, char *))(*(_DWORD *)common.type + 124))(common.type, status.data);
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%s (%i files)\n",
          pack->pakFilename.data,
          pack->numfiles);
      }
      if ( fileSystemLocal.serverPaks.num )
      {
        v11 = 0;
        if ( fileSystemLocal.serverPaks.num <= 0 )
          goto LABEL_22;
        while ( fileSystemLocal.serverPaks.list[v11] != i->pack )
        {
          if ( ++v11 >= fileSystemLocal.serverPaks.num )
            goto LABEL_22;
        }
        if ( v11 >= 0 && &fileSystemLocal.serverPaks.list[v11] )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "    on the pure list\n");
        else
LABEL_22:
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "    not on the pure list\n");
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%s/%s\n",
        i->dir->path.data,
        i->dir->gamedir.data);
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "game DLL: 0x%x in pak: 0x%x\n",
    fileSystemLocal.gameDLLChecksum,
    fileSystemLocal.gamePakChecksum);
  for ( j = 0; j < 6; ++j )
  {
    if ( fileSystemLocal.gamePakForOS[j] )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "OS %d - pak 0x%x\n",
        j,
        fileSystemLocal.gamePakForOS[j]);
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Addon pk4s:\n");
  for ( k = fileSystemLocal.addonPaks; k; k = k->next )
  {
    v14 = k->pack;
    data = k->pack->pakFilename.data;
    v16 = *(_DWORD *)common.type;
    if ( com_developer.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(v16 + 124))(
        common.type,
        "%s (%i files - 0x%x)\n",
        data,
        v14->numfiles,
        v14->checksum);
    else
      (*(void (**)(netadrtype_t, const char *, ...))(v16 + 124))(common.type, "%s (%i files)\n", data, v14->numfiles);
  }
  v18 = -1;
  idStr::FreeData(&status);
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::UpdatePureServerChecksums(void)
void __thiscall idFileSystemLocal::UpdatePureServerChecksums(idFileSystemLocal *this)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  pack_t **list; // eax
  searchpath_s *searchPaths; // edi
  int PackStatus; // eax
  int granularity; // eax
  bool v7; // cc
  int j; // eax
  int num; // ebp
  int size; // eax
  int v11; // ecx
  pack_t **v12; // edi
  int k; // eax
  int v14; // ebx
  const char *v15; // eax
  const char *v16; // edi
  int v17; // ebp
  char v18; // cl
  int v19; // eax
  char *v20; // edx
  int i; // [esp+0h] [ebp-30h]
  int ia; // [esp+0h] [ebp-30h]
  idStr checks; // [esp+4h] [ebp-2Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v24; // [esp+24h] [ebp-Ch]
  void *v25; // [esp+28h] [ebp-8h]
  int v26; // [esp+2Ch] [ebp-4h]

  v26 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v25 = &_ehhandler__AddZipFile_idFileSystemLocal__UAEHPBD_Z;
  v24 = ExceptionList;
  list = this->serverPaks.list;
  if ( list )
    Memory::Free(list);
  this->serverPaks.list = 0;
  this->serverPaks.num = 0;
  this->serverPaks.size = 0;
  searchPaths = this->searchPaths;
  i = (int)searchPaths;
  if ( searchPaths )
  {
    while ( 1 )
    {
      if ( searchPaths->pack )
      {
        PackStatus = idFileSystemLocal::GetPackStatus(this, searchPaths->pack);
        if ( PackStatus != 3 && (PackStatus != 1 || searchPaths->pack->referenced) )
        {
          if ( !this->serverPaks.list )
          {
            granularity = this->serverPaks.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->serverPaks.size )
              {
                v7 = granularity < this->serverPaks.num;
                this->serverPaks.size = granularity;
                if ( v7 )
                  this->serverPaks.num = granularity;
                this->serverPaks.list = (pack_t **)Memory::Allocate(4 * granularity);
                for ( j = 0; j < this->serverPaks.num; ++j )
                  this->serverPaks.list[j] = *(pack_t **)(4 * j);
              }
            }
            else
            {
              this->serverPaks.list = 0;
              this->serverPaks.num = 0;
              this->serverPaks.size = 0;
            }
          }
          num = this->serverPaks.num;
          size = this->serverPaks.size;
          if ( num == size )
          {
            if ( !this->serverPaks.granularity )
              this->serverPaks.granularity = 16;
            v11 = size
                + this->serverPaks.granularity
                - (size + this->serverPaks.granularity) % this->serverPaks.granularity;
            if ( v11 > 0 )
            {
              if ( v11 != this->serverPaks.size )
              {
                v12 = this->serverPaks.list;
                this->serverPaks.size = v11;
                if ( v11 < num )
                  this->serverPaks.num = v11;
                this->serverPaks.list = (pack_t **)Memory::Allocate(4 * v11);
                for ( k = 0; k < this->serverPaks.num; ++k )
                  this->serverPaks.list[k] = v12[k];
                if ( v12 )
                  Memory::Free(v12);
              }
            }
            else
            {
              if ( this->serverPaks.list )
                Memory::Free(this->serverPaks.list);
              this->serverPaks.list = 0;
              this->serverPaks.num = 0;
              this->serverPaks.size = 0;
            }
            searchPaths = (searchpath_s *)i;
          }
          this->serverPaks.list[this->serverPaks.num++] = searchPaths->pack;
          if ( this->serverPaks.num >= 128 )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
              common.type,
              "MAX_PURE_PAKS ( %d ) exceeded\n",
              128);
        }
      }
      i = (int)searchPaths->next;
      if ( !i )
        break;
      searchPaths = searchPaths->next;
    }
  }
  if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
  {
    checks.len = 0;
    checks.alloced = 20;
    checks.data = checks.baseBuffer;
    checks.baseBuffer[0] = 0;
    v14 = 0;
    v7 = this->serverPaks.num <= 0;
    v26 = 0;
    ia = 0;
    if ( !v7 )
    {
      do
      {
        v15 = va("%x ", this->serverPaks.list[v14]->checksum);
        v16 = v15;
        if ( v15 )
        {
          v17 = strlen(v15) + checks.len;
          if ( v17 + 1 > checks.alloced )
            idStr::ReAllocate(&checks, v17 + 1, 1);
          v18 = *v16;
          v19 = 0;
          if ( *v16 )
          {
            do
            {
              v20 = &checks.data[v19++];
              v20[checks.len] = v18;
              v18 = v16[v19];
            }
            while ( v18 );
            v14 = ia;
          }
          checks.len = v17;
          checks.data[v17] = 0;
        }
        ia = ++v14;
      }
      while ( v14 < this->serverPaks.num );
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "set pure list - %d paks ( %s)\n",
      this->serverPaks.num,
      checks.data);
    v26 = -1;
    idStr::FreeData(&checks);
  }
}

// FUNC: public: virtual enum fsPureReply_t __thiscall idFileSystemLocal::SetPureServerChecksums(int const * const,int,int * const,int *)
int __thiscall idFileSystemLocal::SetPureServerChecksums(
        idFileSystemLocal *this,
        const int *pureChecksums,
        int _gamePakChecksum,
        int *missingChecksums,
        int *missingGamePakChecksum)
{
  int v6; // eax
  int v7; // ebp
  searchpath_s *searchPaths; // eax
  int v10; // edx
  pack_t *v11; // eax
  searchpath_s *v12; // eax
  pack_t *pack; // ebx
  int v14; // ebx
  int granularity; // eax
  bool v16; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v20; // ecx
  pack_t **list; // edi
  int k; // eax
  int v23; // edx
  int m; // eax
  pack_t **v25; // ecx
  pack_t *v26; // edi
  pack_t **v27; // ecx
  int v28; // edx
  int v29; // eax
  pack_t **v30; // ecx
  int v31; // edx
  int v32; // eax
  pack_t **v33; // ecx
  pack_t *v34; // ebp
  fileInPack_s *v35; // edi
  bool v36; // bl
  bool success; // [esp+Fh] [ebp-119h]
  const int *v38; // [esp+10h] [ebp-118h]
  bool canPrepend; // [esp+17h] [ebp-111h]
  int j; // [esp+18h] [ebp-110h]
  int imissing; // [esp+1Ch] [ebp-10Ch]
  pack_t *v42; // [esp+20h] [ebp-108h]
  int dllHash; // [esp+24h] [ebp-104h]
  char dllName[256]; // [esp+28h] [ebp-100h] BYREF

  success = 1;
  canPrepend = 1;
  sys->DLL_GetFileName(sys, "game", dllName, 256);
  v6 = idFileSystemLocal::HashFileName(this, dllName);
  v7 = 0;
  *missingChecksums = 0;
  *missingGamePakChecksum = 0;
  dllHash = v6;
  imissing = 0;
  if ( !*pureChecksums )
  {
    this->ClearPureChecksums(this);
    return 0;
  }
  if ( !this->serverPaks.num )
    this->UpdatePureServerChecksums(this);
  j = 0;
  if ( *pureChecksums )
  {
    v38 = pureChecksums;
    while ( v7 < this->serverPaks.num && this->serverPaks.list[v7]->checksum == *v38 )
    {
      ++v38;
      ++v7;
      canPrepend = 0;
      j = v7;
LABEL_20:
      if ( !*v38 )
        goto LABEL_21;
    }
    searchPaths = this->searchPaths;
    v10 = *v38;
    if ( searchPaths )
    {
      while ( !searchPaths->pack || searchPaths->pack->checksum != v10 )
      {
        searchPaths = searchPaths->next;
        if ( !searchPaths )
          goto LABEL_14;
      }
    }
    else
    {
LABEL_14:
      searchPaths = this->addonPaks;
      if ( !searchPaths )
        goto LABEL_17;
      while ( searchPaths->pack->checksum != v10 )
      {
        searchPaths = searchPaths->next;
        if ( !searchPaths )
          goto LABEL_17;
      }
    }
    pack = searchPaths->pack;
    v42 = searchPaths->pack;
    if ( searchPaths->pack )
    {
      if ( pack->addon && !pack->addon_search )
      {
        if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "pak %s checksumed 0x%x is on addon list. Restart required.\n",
            pack->pakFilename.data,
            pack->checksum);
        success = 0;
      }
      if ( canPrepend )
      {
        if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "prepend pak %s checksumed 0x%x at index %d\n",
            pack->pakFilename.data,
            pack->checksum,
            v7);
        v14 = v7;
        if ( !this->serverPaks.list )
        {
          granularity = this->serverPaks.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->serverPaks.size )
            {
              v16 = granularity < this->serverPaks.num;
              this->serverPaks.size = granularity;
              if ( v16 )
                this->serverPaks.num = granularity;
              this->serverPaks.list = (pack_t **)Memory::Allocate(4 * granularity);
              for ( i = 0; i < this->serverPaks.num; ++i )
                this->serverPaks.list[i] = *(pack_t **)(4 * i);
            }
          }
          else
          {
            this->serverPaks.list = 0;
            this->serverPaks.num = 0;
            this->serverPaks.size = 0;
          }
        }
        num = this->serverPaks.num;
        size = this->serverPaks.size;
        if ( num == size )
        {
          if ( !this->serverPaks.granularity )
            this->serverPaks.granularity = 16;
          v20 = size
              + this->serverPaks.granularity
              - (size + this->serverPaks.granularity) % this->serverPaks.granularity;
          if ( v20 > 0 )
          {
            if ( v20 != this->serverPaks.size )
            {
              list = this->serverPaks.list;
              this->serverPaks.size = v20;
              if ( v20 < num )
                this->serverPaks.num = v20;
              this->serverPaks.list = (pack_t **)Memory::Allocate(4 * v20);
              for ( k = 0; k < this->serverPaks.num; ++k )
                this->serverPaks.list[k] = list[k];
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( this->serverPaks.list )
              Memory::Free(this->serverPaks.list);
            this->serverPaks.list = 0;
            this->serverPaks.num = 0;
            this->serverPaks.size = 0;
          }
        }
        v23 = j;
        if ( j >= 0 )
        {
          if ( j > this->serverPaks.num )
            v14 = this->serverPaks.num;
        }
        else
        {
          v14 = 0;
        }
        for ( m = this->serverPaks.num; m > v14; *v27 = v26 )
        {
          v25 = this->serverPaks.list;
          v26 = v25[m - 1];
          v27 = &v25[m--];
        }
        ++this->serverPaks.num;
        ++v38;
        this->serverPaks.list[v14] = v42;
        ++j;
        v7 = v23 + 1;
        goto LABEL_20;
      }
      success = 0;
      if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
      {
        v28 = this->serverPaks.num;
        v29 = 0;
        if ( v28 <= 0 )
          goto LABEL_76;
        v30 = this->serverPaks.list;
        while ( *v30 != pack )
        {
          ++v29;
          ++v30;
          if ( v29 >= v28 )
            goto LABEL_76;
        }
        if ( v29 >= 0 && &this->serverPaks.list[v29] )
        {
          v31 = this->serverPaks.num;
          v32 = 0;
          if ( v31 <= 0 )
          {
LABEL_83:
            v32 = -1;
          }
          else
          {
            v33 = this->serverPaks.list;
            while ( *v33 != pack )
            {
              ++v32;
              ++v33;
              if ( v32 >= v31 )
                goto LABEL_83;
            }
          }
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "pak %s checksumed 0x%x is in the pure list at wrong index. Current index is %d, found at %d\n",
            pack->pakFilename.data,
            pack->checksum,
            v7,
            v32);
        }
        else
        {
LABEL_76:
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "pak %s checksumed 0x%x can't be added to pure list because of search order\n",
            pack->pakFilename.data,
            pack->checksum);
        }
      }
      goto LABEL_19;
    }
LABEL_17:
    missingChecksums[imissing] = v10;
    missingChecksums[++imissing] = 0;
    success = 0;
    if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "checksum not found - 0x%x\n",
        *v38);
LABEL_19:
    ++v38;
    goto LABEL_20;
  }
LABEL_21:
  if ( v7 < this->serverPaks.num )
  {
    success = 0;
    do
    {
      if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
      {
        v11 = this->serverPaks.list[v7];
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "pak %s checksumed 0x%x is an extra reference at the end of local pure list\n",
          v11->pakFilename.data,
          v11->checksum);
      }
      ++v7;
    }
    while ( v7 < this->serverPaks.num );
  }
  if ( !_gamePakChecksum )
    return 3;
  if ( _gamePakChecksum != this->gamePakChecksum )
  {
    v12 = this->searchPaths;
    if ( !v12 )
      goto LABEL_86;
    while ( !v12->pack || v12->pack->checksum != _gamePakChecksum )
    {
      v12 = v12->next;
      if ( !v12 )
        goto LABEL_86;
    }
    v34 = v12->pack;
    if ( !v12->pack )
    {
LABEL_86:
      if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "missing the game code pak ( 0x%x )\n",
          _gamePakChecksum);
      *missingGamePakChecksum = _gamePakChecksum;
      return 2;
    }
    if ( !imissing )
    {
      if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "server's game code pak candidate is '%s' ( 0x%x )\n",
          v34->pakFilename.data,
          v34->checksum);
      v35 = v34->hashTable[dllHash];
      if ( v35 )
      {
        while ( idFileSystemLocal::FilenameCompare(this, v35->name.data, dllName) )
        {
          v35 = v35->next;
          if ( !v35 )
            goto LABEL_96;
        }
        this->gamePakChecksum = _gamePakChecksum;
        return 1;
      }
LABEL_96:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "media is misconfigured. server claims pak '%s' ( 0x%x ) has media for us, but '%s' is not found\n",
        v34->pakFilename.data,
        v34->checksum,
        dllName);
      return 3;
    }
    return 2;
  }
  if ( imissing )
    return 2;
  if ( this->loadedFileFromDir )
  {
    v36 = 0;
    if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "SetPureServerChecksums: there are files loaded from dir\n");
      return 1;
    }
  }
  else
  {
    v36 = success;
  }
  return !v36;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::SetRestartChecksums(int const * const,int)
void __thiscall idFileSystemLocal::SetRestartChecksums(
        idFileSystemLocal *this,
        const int *pureChecksums,
        int gamePakChecksum)
{
  int v4; // edx
  searchpath_s *searchPaths; // eax
  pack_t *pack; // ebx
  int num; // edx
  int v8; // eax
  int *list; // ecx
  int granularity; // eax
  bool v11; // cc
  int i; // eax
  int v13; // ebp
  int size; // eax
  int v15; // ecx
  int *v16; // edi
  int j; // eax
  int v18; // eax
  int k; // eax
  int v20; // ebp
  int v21; // eax
  int v22; // ecx
  int *v23; // edi
  int m; // eax
  bool v25; // zf
  const int *v26; // [esp+4h] [ebp-4h]

  if ( this->restartChecksums.list )
    Memory::Free(this->restartChecksums.list);
  this->restartChecksums.list = 0;
  this->restartChecksums.num = 0;
  this->restartChecksums.size = 0;
  if ( *pureChecksums )
  {
    v26 = pureChecksums;
    while ( 1 )
    {
      v4 = *pureChecksums;
      searchPaths = this->searchPaths;
      if ( searchPaths )
        break;
LABEL_9:
      searchPaths = this->addonPaks;
      if ( searchPaths )
      {
        while ( searchPaths->pack->checksum != v4 )
        {
          searchPaths = searchPaths->next;
          if ( !searchPaths )
            goto LABEL_12;
        }
        goto LABEL_13;
      }
LABEL_12:
      pack = 0;
LABEL_14:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
        common.type,
        "SetRestartChecksums failed: no pak for checksum 0x%x\n",
        *pureChecksums);
LABEL_15:
      if ( pack->addon )
      {
        num = this->addonChecksums.num;
        v8 = 0;
        if ( num <= 0 )
          goto LABEL_22;
        list = this->addonChecksums.list;
        while ( *list != pack->checksum )
        {
          ++v8;
          ++list;
          if ( v8 >= num )
            goto LABEL_22;
        }
        if ( v8 < 0 )
        {
LABEL_22:
          if ( !this->addonChecksums.list )
          {
            granularity = this->addonChecksums.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->addonChecksums.size )
              {
                v11 = granularity < this->addonChecksums.num;
                this->addonChecksums.size = granularity;
                if ( v11 )
                  this->addonChecksums.num = granularity;
                this->addonChecksums.list = (int *)Memory::Allocate(4 * granularity);
                for ( i = 0; i < this->addonChecksums.num; ++i )
                  this->addonChecksums.list[i] = *(_DWORD *)(4 * i);
              }
            }
            else
            {
              this->addonChecksums.list = 0;
              this->addonChecksums.num = 0;
              this->addonChecksums.size = 0;
            }
          }
          v13 = this->addonChecksums.num;
          size = this->addonChecksums.size;
          if ( v13 == size )
          {
            if ( !this->addonChecksums.granularity )
              this->addonChecksums.granularity = 16;
            v15 = size
                + this->addonChecksums.granularity
                - (size + this->addonChecksums.granularity) % this->addonChecksums.granularity;
            if ( v15 > 0 )
            {
              if ( v15 != this->addonChecksums.size )
              {
                v16 = this->addonChecksums.list;
                this->addonChecksums.size = v15;
                if ( v15 < v13 )
                  this->addonChecksums.num = v15;
                this->addonChecksums.list = (int *)Memory::Allocate(4 * v15);
                for ( j = 0; j < this->addonChecksums.num; ++j )
                  this->addonChecksums.list[j] = v16[j];
                if ( v16 )
                  Memory::Free(v16);
              }
            }
            else
            {
              if ( this->addonChecksums.list )
                Memory::Free(this->addonChecksums.list);
              this->addonChecksums.list = 0;
              this->addonChecksums.num = 0;
              this->addonChecksums.size = 0;
            }
          }
          this->addonChecksums.list[this->addonChecksums.num++] = pack->checksum;
        }
      }
      if ( !this->restartChecksums.list )
      {
        v18 = this->restartChecksums.granularity;
        if ( v18 > 0 )
        {
          if ( v18 != this->restartChecksums.size )
          {
            v11 = v18 < this->restartChecksums.num;
            this->restartChecksums.size = v18;
            if ( v11 )
              this->restartChecksums.num = v18;
            this->restartChecksums.list = (int *)Memory::Allocate(4 * v18);
            for ( k = 0; k < this->restartChecksums.num; ++k )
              this->restartChecksums.list[k] = *(_DWORD *)(4 * k);
          }
        }
        else
        {
          this->restartChecksums.list = 0;
          this->restartChecksums.num = 0;
          this->restartChecksums.size = 0;
        }
      }
      v20 = this->restartChecksums.num;
      v21 = this->restartChecksums.size;
      if ( v20 == v21 )
      {
        if ( !this->restartChecksums.granularity )
          this->restartChecksums.granularity = 16;
        v22 = v21
            + this->restartChecksums.granularity
            - (v21 + this->restartChecksums.granularity) % this->restartChecksums.granularity;
        if ( v22 > 0 )
        {
          if ( v22 != this->restartChecksums.size )
          {
            v23 = this->restartChecksums.list;
            this->restartChecksums.size = v22;
            if ( v22 < v20 )
              this->restartChecksums.num = v22;
            this->restartChecksums.list = (int *)Memory::Allocate(4 * v22);
            for ( m = 0; m < this->restartChecksums.num; ++m )
              this->restartChecksums.list[m] = v23[m];
            if ( v23 )
              Memory::Free(v23);
          }
        }
        else
        {
          if ( this->restartChecksums.list )
            Memory::Free(this->restartChecksums.list);
          this->restartChecksums.list = 0;
          this->restartChecksums.num = 0;
          this->restartChecksums.size = 0;
        }
      }
      this->restartChecksums.list[this->restartChecksums.num++] = *pureChecksums;
      v25 = v26[1] == 0;
      pureChecksums = ++v26;
      if ( v25 )
      {
        this->restartGamePakChecksum = gamePakChecksum;
        return;
      }
    }
    while ( !searchPaths->pack || searchPaths->pack->checksum != v4 )
    {
      searchPaths = searchPaths->next;
      if ( !searchPaths )
        goto LABEL_9;
    }
LABEL_13:
    pack = searchPaths->pack;
    if ( searchPaths->pack )
      goto LABEL_15;
    goto LABEL_14;
  }
  this->restartGamePakChecksum = gamePakChecksum;
}

// FUNC: private: class idFile_InZip * __thiscall idFileSystemLocal::ReadFileFromZip(struct pack_t *,struct fileInPack_s *,char const *)
idFile_InZip *__thiscall idFileSystemLocal::ReadFileFromZip(
        idFileSystemLocal *this,
        pack_t *pak,
        fileInPack_s *pakFile,
        char *relativePath)
{
  idFile_InZip *v4; // eax
  int v5; // eax
  int v6; // ebp
  void *v7; // eax
  const idStr *v8; // eax
  idStr *v9; // esi
  unsigned int len; // edi
  int v11; // eax
  bool v12; // cc
  int *v13; // esi
  int v14; // edi
  char *data; // [esp-8h] [ebp-68h]
  void *handle; // [esp-4h] [ebp-64h]
  idStr v18; // [esp+14h] [ebp-4Ch] BYREF
  idStr result; // [esp+34h] [ebp-2Ch] BYREF
  int v20; // [esp+5Ch] [ebp-4h]

  v4 = (idFile_InZip *)Memory::Allocate(0x50u);
  v20 = 0;
  if ( v4 )
  {
    idFile_InZip::idFile_InZip(v4);
    v6 = v5;
  }
  else
  {
    v6 = 0;
  }
  handle = pak->handle;
  data = pak->pakFilename.data;
  v20 = -1;
  v7 = unzReOpen(data, handle);
  *(_DWORD *)(v6 + 76) = v7;
  if ( !v7 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "Couldn't reopen %s",
      pak->pakFilename.data);
  idStr::operator=((idStr *)(v6 + 4), relativePath);
  v8 = operator+(&result, &pak->pakFilename, "/");
  v20 = 1;
  v9 = operator+(&v18, v8, relativePath);
  len = v9->len;
  v11 = v9->len + 1;
  v12 = v11 <= *(_DWORD *)(v6 + 44);
  LOBYTE(v20) = 2;
  if ( !v12 )
    idStr::ReAllocate((idStr *)(v6 + 36), v11, 0);
  qmemcpy(*(void **)(v6 + 40), v9->data, len);
  *(_BYTE *)(len + *(_DWORD *)(v6 + 40)) = 0;
  *(_DWORD *)(v6 + 36) = len;
  LOBYTE(v20) = 1;
  idStr::FreeData(&v18);
  v20 = -1;
  idStr::FreeData(&result);
  v13 = *(int **)(v6 + 76);
  v14 = *v13;
  unzSetCurrentFileInfoPosition(pak->handle, pakFile->pos);
  SIMDProcessor->Memcpy(SIMDProcessor, v13, pak->handle, 136);
  *v13 = v14;
  unzOpenCurrentFile(*(void **)(v6 + 76));
  *(_DWORD *)(v6 + 68) = pakFile->pos;
  *(_DWORD *)(v6 + 72) = v13[19];
  return (idFile_InZip *)v6;
}

// FUNC: private: struct pack_t * __thiscall idFileSystemLocal::FindPakForFileChecksum(char const *,int,bool)
pack_t *__thiscall idFileSystemLocal::FindPakForFileChecksum(
        idFileSystemLocal *this,
        char *relativePath,
        int findChecksum,
        bool bReference)
{
  char *v4; // edi
  int v6; // eax
  searchpath_s *searchPaths; // ecx
  pack_t *pack; // ebx
  fileInPack_s *v10; // ebp
  idFile_InZip *FileFromZip; // edi
  int v12; // ebp
  unsigned int FileChecksum; // eax
  searchpath_s *search; // [esp+10h] [ebp-10h]
  fileInPack_s *pakFile; // [esp+14h] [ebp-Ch]
  char *data; // [esp+18h] [ebp-8h]
  int hash; // [esp+1Ch] [ebp-4h]

  v4 = relativePath;
  v6 = idFileSystemLocal::HashFileName(this, relativePath);
  searchPaths = this->searchPaths;
  hash = v6;
  search = searchPaths;
  if ( !searchPaths )
  {
LABEL_2:
    if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "no pak file found for '%s' checksumed %x\n",
        v4,
        findChecksum);
    return 0;
  }
  while ( 1 )
  {
    pack = searchPaths->pack;
    if ( searchPaths->pack )
    {
      if ( pack->hashTable[v6] )
      {
        v10 = pack->hashTable[v6];
        pakFile = v10;
        if ( v10 )
          break;
      }
    }
LABEL_16:
    search = searchPaths->next;
    if ( !search )
      goto LABEL_2;
    searchPaths = searchPaths->next;
  }
  while ( idFileSystemLocal::FilenameCompare(this, v10->name.data, v4) )
  {
LABEL_14:
    v10 = v10->next;
    pakFile = v10;
    if ( !v10 )
    {
      v6 = hash;
      searchPaths = search;
      goto LABEL_16;
    }
  }
  FileFromZip = idFileSystemLocal::ReadFileFromZip(this, pack, v10, v4);
  if ( findChecksum != idFileSystemLocal::GetFileChecksum(this, FileFromZip) )
  {
    if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
    {
      v12 = *(_DWORD *)common.type;
      data = pack->pakFilename.data;
      FileChecksum = idFileSystemLocal::GetFileChecksum(this, FileFromZip);
      (*(void (**)(netadrtype_t, const char *, ...))(v12 + 124))(
        common.type,
        "'%s' in pak '%s' has != checksum %x\n",
        relativePath,
        data,
        FileChecksum);
      v10 = pakFile;
    }
    this->CloseFile(this, FileFromZip);
    v4 = relativePath;
    goto LABEL_14;
  }
  if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "found '%s' with checksum 0x%x in pak '%s'\n",
      relativePath,
      findChecksum,
      pack->pakFilename.data);
  if ( bReference )
    pack->referenced = 1;
  this->CloseFile(this, FileFromZip);
  return pack;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::FindDLL(char const *,char * const,bool)
void __thiscall idFileSystemLocal::FindDLL(
        idFileSystemLocal *this,
        const char *name,
        char *_dllPath,
        bool updateChecksum)
{
  idFile *v5; // edi
  idSys_vtbl *v6; // edx
  int v7; // eax
  bool v8; // zf
  char *v9; // eax
  char *v10; // eax
  idFile *v11; // edi
  int v12; // ebp
  int v13; // eax
  char *v14; // eax
  idFile *v15; // eax
  idFile *v16; // eax
  int FileChecksum; // eax
  pack_t *PakForFileChecksum; // eax
  searchpath_s *searchPaths; // eax
  pack_t *pack; // ebp
  fileInPack_s *i; // ebx
  idFile_InZip *FileFromZip; // edi
  char *v23; // eax
  idFile *v24; // eax
  char *v25; // eax
  idStr dllPath; // [esp+34h] [ebp-134h] BYREF
  int dllHash; // [esp+54h] [ebp-114h]
  pack_t *inPak; // [esp+58h] [ebp-110h] BYREF
  char dllName[256]; // [esp+5Ch] [ebp-10Ch] BYREF
  int v30; // [esp+164h] [ebp-4h]

  v5 = 0;
  dllPath.len = 0;
  dllPath.alloced = 20;
  dllPath.data = dllPath.baseBuffer;
  dllPath.baseBuffer[0] = 0;
  v6 = sys->__vftable;
  v30 = 0;
  v6->DLL_GetFileName(sys, name, dllName, 256);
  v7 = idFileSystemLocal::HashFileName(this, dllName);
  v8 = this->serverPaks.num == 0;
  dllHash = v7;
  if ( !v8 )
    goto LABEL_16;
  if ( IsDebuggerPresent() )
  {
    v9 = (char *)Sys_EXEPath();
    idStr::operator=(&dllPath, v9);
    idStr::StripFilename(&dllPath);
    idStr::AppendPath(&dllPath, dllName);
  }
  else
  {
    v10 = (char *)this->RelativePathToOSPath(this, dllName, "fs_base");
    idStr::operator=(&dllPath, v10);
  }
  v5 = this->OpenExplicitFileRead(this, dllPath.data);
  if ( v5 )
    goto LABEL_29;
  if ( this->serverPaks.num )
  {
LABEL_16:
    searchPaths = this->searchPaths;
    if ( !searchPaths )
      goto LABEL_22;
    while ( !searchPaths->pack || searchPaths->pack->checksum != this->gamePakChecksum )
    {
      searchPaths = searchPaths->next;
      if ( !searchPaths )
        goto LABEL_22;
    }
    pack = searchPaths->pack;
    if ( searchPaths->pack )
    {
      for ( i = pack->hashTable[dllHash]; i; i = i->next )
      {
        if ( !idFileSystemLocal::FilenameCompare(this, i->name.data, dllName) )
        {
          FileFromZip = idFileSystemLocal::ReadFileFromZip(this, pack, i, dllName);
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "found DLL in game pak file: %s\n",
            pack->pakFilename.data);
          v23 = (char *)this->RelativePathToOSPath(this, dllName, "fs_savepath");
          idStr::operator=(&dllPath, v23);
          (*(void (__thiscall **)(idFileSystemLocal *, idFile_InZip *, char *))this->gapF4)(
            this,
            FileFromZip,
            dllPath.data);
          this->CloseFile(this, FileFromZip);
          v24 = this->OpenFileReadFlags(this, dllName, 1, 0, 1, 0);
          v5 = v24;
          if ( v24 )
          {
            this->gameDLLChecksum = idFileSystemLocal::GetFileChecksum(this, v24);
            updateChecksum = 0;
          }
          else
          {
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
              common.type,
              "DLL extraction to fs_savepath failed\n");
          }
        }
      }
    }
    else
    {
LABEL_22:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "FindDLL in pure mode: game pak not found ( 0x%x )\n",
        this->gamePakChecksum);
    }
    goto LABEL_29;
  }
  v11 = this->OpenFileReadFlags(this, dllName, 14, &inPak, 1, 0);
  if ( !v11 )
  {
    v16 = this->OpenFileReadFlags(this, dllName, 1, 0, 1, 0);
    v5 = v16;
    if ( v16 )
    {
      if ( !updateChecksum )
        goto LABEL_34;
      FileChecksum = idFileSystemLocal::GetFileChecksum(this, v16);
      this->gameDLLChecksum = FileChecksum;
      PakForFileChecksum = idFileSystemLocal::FindPakForFileChecksum(this, dllName, FileChecksum, 0);
      if ( PakForFileChecksum )
      {
        this->gamePakChecksum = PakForFileChecksum->checksum;
        goto LABEL_34;
      }
LABEL_33:
      this->gamePakChecksum = 0;
      goto LABEL_34;
    }
LABEL_29:
    if ( !updateChecksum )
      goto LABEL_34;
    if ( v5 )
      this->gameDLLChecksum = idFileSystemLocal::GetFileChecksum(this, v5);
    else
      this->gameDLLChecksum = 0;
    goto LABEL_33;
  }
  v12 = *(_DWORD *)common.type;
  v13 = (int)v11->GetFullPath(v11);
  (*(void (**)(netadrtype_t, const char *, ...))(v12 + 124))(common.type, "found DLL in pak file: %s\n", v13);
  v14 = (char *)this->RelativePathToOSPath(this, dllName, "fs_savepath");
  idStr::operator=(&dllPath, v14);
  (*(void (__thiscall **)(idFileSystemLocal *, idFile *, char *))this->gapF4)(this, v11, dllPath.data);
  this->CloseFile(this, v11);
  v15 = this->OpenFileReadFlags(this, dllName, 1, 0, 1, 0);
  v5 = v15;
  if ( !v15 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "DLL extraction to fs_savepath failed\n");
    goto LABEL_29;
  }
  if ( updateChecksum )
  {
    this->gameDLLChecksum = idFileSystemLocal::GetFileChecksum(this, v15);
    this->gamePakChecksum = inPak->checksum;
  }
LABEL_34:
  if ( v5 )
  {
    v25 = (char *)v5->GetFullPath(v5);
    idStr::operator=(&dllPath, v25);
    this->CloseFile(this, v5);
  }
  else
  {
    idStr::operator=(&dllPath, (char *)&entityFilter);
  }
  idStr::snPrintf(_dllPath, 256, dllPath.data);
  v30 = -1;
  idStr::FreeData(&dllPath);
}

// FUNC: public: virtual enum findFile_t __thiscall idFileSystemLocal::FindFile(char const *)
int __thiscall idFileSystemLocal::FindFile(idFileSystemLocal *this, const char *path)
{
  idFile *v3; // ecx
  const char *v5; // edi
  int num; // edx
  int v7; // eax
  int *list; // ecx
  int granularity; // eax
  bool v10; // cc
  int i; // eax
  int v12; // ebp
  int size; // eax
  int v14; // ecx
  int *v15; // edi
  int j; // eax
  idFile *f; // [esp+14h] [ebp-8h]
  int *v18; // [esp+18h] [ebp-4h]

  v3 = this->OpenFileReadFlags(this, path, 19, &path, 1, 0);
  f = v3;
  if ( !v3 )
    return 0;
  v5 = path;
  if ( path )
  {
    if ( path[56] )
    {
      num = this->addonChecksums.num;
      v7 = 0;
      if ( num <= 0 )
        goto LABEL_11;
      list = this->addonChecksums.list;
      while ( *list != *((_DWORD *)path + 9) )
      {
        ++v7;
        ++list;
        if ( v7 >= num )
          goto LABEL_11;
      }
      if ( v7 < 0 )
      {
LABEL_11:
        v18 = (int *)(path + 36);
        if ( !this->addonChecksums.list )
        {
          granularity = this->addonChecksums.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->addonChecksums.size )
            {
              v10 = granularity < this->addonChecksums.num;
              this->addonChecksums.size = granularity;
              if ( v10 )
                this->addonChecksums.num = granularity;
              this->addonChecksums.list = (int *)Memory::Allocate(4 * granularity);
              for ( i = 0; i < this->addonChecksums.num; ++i )
                this->addonChecksums.list[i] = *(_DWORD *)(4 * i);
            }
          }
          else
          {
            this->addonChecksums.list = 0;
            this->addonChecksums.num = 0;
            this->addonChecksums.size = 0;
          }
        }
        v12 = this->addonChecksums.num;
        size = this->addonChecksums.size;
        if ( v12 == size )
        {
          if ( !this->addonChecksums.granularity )
            this->addonChecksums.granularity = 16;
          v14 = size
              + this->addonChecksums.granularity
              - (size + this->addonChecksums.granularity) % this->addonChecksums.granularity;
          if ( v14 > 0 )
          {
            if ( v14 != this->addonChecksums.size )
            {
              v15 = this->addonChecksums.list;
              this->addonChecksums.size = v14;
              if ( v14 < v12 )
                this->addonChecksums.num = v14;
              this->addonChecksums.list = (int *)Memory::Allocate(4 * v14);
              for ( j = 0; j < this->addonChecksums.num; ++j )
                this->addonChecksums.list[j] = v15[j];
              if ( v15 )
                Memory::Free(v15);
            }
          }
          else
          {
            if ( this->addonChecksums.list )
              Memory::Free(this->addonChecksums.list);
            this->addonChecksums.list = 0;
            this->addonChecksums.num = 0;
            this->addonChecksums.size = 0;
          }
        }
        this->addonChecksums.list[this->addonChecksums.num++] = *v18;
        v5 = path;
      }
      v3 = f;
      if ( v5[56] )
      {
        if ( !v5[57] )
        {
          ((void (__stdcall *)(int))f->~idFile)(1);
          return 2;
        }
      }
    }
    ((void (__thiscall *)(idFile *, int))v3->~idFile)(v3, 1);
  }
  return 1;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::SetAssetLogName(char const *)
void __thiscall idFileSystemLocal::SetAssetLogName(idFileSystemLocal *this, const char *logName)
{
  idStr *p_currentAssetLog; // ebx
  int v4; // esi
  int v5; // eax
  int v6; // eax
  char v7; // cl
  char *data; // eax
  unsigned int v9; // esi
  char v10; // cl
  int i; // eax
  char *v12; // eax
  unsigned int len; // esi
  idStr *p_currentAssetLogUnfiltered; // ebp
  int v15; // eax
  const char *v16; // eax
  const char *v17; // edi
  int v18; // esi
  int v19; // eax
  int v20; // eax
  char v21; // cl
  char *v22; // edx
  char *v23; // eax
  unsigned int v24; // esi
  char v25; // cl
  int j; // eax
  int v27; // edx
  char *v28; // eax
  const char *logNamea; // [esp+18h] [ebp+4h]

  p_currentAssetLog = &this->currentAssetLog;
  idStr::FreeData(&this->currentAssetLog);
  p_currentAssetLog->data = p_currentAssetLog->baseBuffer;
  p_currentAssetLog->len = 0;
  p_currentAssetLog->alloced = 20;
  p_currentAssetLog->baseBuffer[0] = 0;
  v4 = p_currentAssetLog->len + 10;
  v5 = p_currentAssetLog->len + 11;
  if ( v5 > p_currentAssetLog->alloced )
    idStr::ReAllocate(p_currentAssetLog, v5, 1);
  v6 = 0;
  v7 = 97;
  do
  {
    ++v6;
    p_currentAssetLog->data[p_currentAssetLog->len - 1 + v6] = v7;
    v7 = aAssetlogs[v6];
  }
  while ( v7 );
  data = p_currentAssetLog->data;
  p_currentAssetLog->len = v4;
  data[v4] = 0;
  if ( logName )
  {
    v9 = strlen(logName) + p_currentAssetLog->len;
    if ( (signed int)(v9 + 1) > p_currentAssetLog->alloced )
      idStr::ReAllocate(p_currentAssetLog, v9 + 1, 1);
    v10 = *logName;
    for ( i = 0; v10; v10 = logName[i] )
    {
      ++i;
      p_currentAssetLog->data[p_currentAssetLog->len - 1 + i] = v10;
    }
    v12 = p_currentAssetLog->data;
    p_currentAssetLog->len = v9;
    v12[v9] = 0;
  }
  idStr::StripFileExtension(p_currentAssetLog);
  len = p_currentAssetLog->len;
  p_currentAssetLogUnfiltered = &this->currentAssetLogUnfiltered;
  v15 = p_currentAssetLog->len + 1;
  logNamea = (const char *)p_currentAssetLog->len;
  if ( v15 > p_currentAssetLogUnfiltered->alloced )
    idStr::ReAllocate(p_currentAssetLogUnfiltered, v15, 0);
  qmemcpy(p_currentAssetLogUnfiltered->data, p_currentAssetLog->data, len);
  logNamea[(unsigned int)p_currentAssetLogUnfiltered->data] = 0;
  p_currentAssetLogUnfiltered->len = (int)logNamea;
  v16 = cvarSystem->GetCVarString(cvarSystem, "si_entityFilter");
  v17 = v16;
  if ( v16 && *v16 )
  {
    v18 = p_currentAssetLog->len + 1;
    v19 = p_currentAssetLog->len + 2;
    if ( v19 > p_currentAssetLog->alloced )
      idStr::ReAllocate(p_currentAssetLog, v19, 1);
    v20 = 0;
    v21 = 45;
    do
    {
      v22 = &p_currentAssetLog->data[v20++];
      v22[p_currentAssetLog->len] = v21;
      v21 = asc_1029DD84[v20];
    }
    while ( v21 );
    v23 = p_currentAssetLog->data;
    p_currentAssetLog->len = v18;
    v23[v18] = 0;
    v24 = strlen(v17) + p_currentAssetLog->len;
    if ( (signed int)(v24 + 1) > p_currentAssetLog->alloced )
      idStr::ReAllocate(p_currentAssetLog, v24 + 1, 1);
    v25 = *v17;
    for ( j = 0; v25; v25 = v17[j] )
    {
      v27 = j + p_currentAssetLog->len;
      ++j;
      p_currentAssetLog->data[v27] = v25;
    }
    v28 = p_currentAssetLog->data;
    p_currentAssetLog->len = v24;
    v28[v24] = 0;
  }
  printf("Asset log: %s\n", this->currentAssetLog.data);
}

// FUNC: private: void __thiscall idFileSystemLocal::UnloadZipFile(struct pack_t *)
void __thiscall idFileSystemLocal::UnloadZipFile(idFileSystemLocal *this, idPoolStr *pack)
{
  fileInPack_s *data; // eax
  fileInPack_s **p_next; // esi

  unzClose(pack->pool);
  data = (fileInPack_s *)pack[104].data;
  if ( data )
  {
    p_next = &data[-1].next;
    `eh vector destructor iterator'(
      data,
      0x28u,
      (int)data[-1].next,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(p_next);
  }
  idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s(pack);
  Memory::Free(pack);
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::RemoveExplicitPak(char const *)
void __thiscall idFileSystemLocal::RemoveExplicitPak(idFileSystemLocal *this, const char *path)
{
  searchpath_s *searchPaths; // esi
  searchpath_s *v4; // edi

  searchPaths = this->searchPaths;
  v4 = 0;
  if ( searchPaths )
  {
    while ( idStr::Cmp(searchPaths->pack->pakFilename.data, path) )
    {
      v4 = searchPaths;
      searchPaths = searchPaths->next;
      if ( !searchPaths )
        return;
    }
    idFileSystemLocal::UnloadZipFile(this, (idPoolStr *)searchPaths->pack);
    if ( v4 )
      v4->next = searchPaths->next;
    else
      this->searchPaths = searchPaths->next;
    Memory::Free(searchPaths);
  }
}

// FUNC: public: void __thiscall idDEntry::Init(char const *,char const *,class idList<class idStr> const &)
void __thiscall idDEntry::Init(idDEntry *this, char *directory, char *extension, idList<idStr> *list)
{
  idStr::operator=(&this->directory, directory);
  idStr::operator=(&this->extension, extension);
  idList<idStr>::operator=(&this->num, list);
}

// FUNC: public: void __thiscall idDEntry::Clear(void)
void __thiscall idDEntry::Clear(idDEntry *this)
{
  idStr *p_directory; // esi
  idStr *list; // eax
  char *v4; // esi

  p_directory = &this->directory;
  idStr::FreeData(&this->directory);
  p_directory->len = 0;
  p_directory->alloced = 20;
  p_directory->data = p_directory->baseBuffer;
  p_directory->baseBuffer[0] = 0;
  idStr::FreeData(&this->extension);
  this->extension.len = 0;
  this->extension.alloced = 20;
  this->extension.data = this->extension.baseBuffer;
  this->extension.baseBuffer[0] = 0;
  list = this->list;
  if ( list )
  {
    v4 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v4);
  }
  this->list = 0;
  this->num = 0;
  this->size = 0;
}

// FUNC: private: int __thiscall idFileSystemLocal::ListOSFiles(char const *,char const *,class idList<class idStr> &)
const char *__thiscall idFileSystemLocal::ListOSFiles(
        idFileSystemLocal *this,
        char *directory,
        char *extension,
        idList<idStr> *list)
{
  char *v4; // edi
  const char *result; // eax
  int dir_cache_index; // eax
  int v8; // ebp
  char *v9; // eax
  int dir_cache_count; // eax
  int i; // [esp+8h] [ebp-4h]
  const char *extensiona; // [esp+14h] [ebp+8h]

  v4 = extension;
  if ( !extension )
  {
    extension = (char *)&entityFilter;
    v4 = (char *)&entityFilter;
  }
  if ( !idFileSystemLocal::fs_caseSensitiveOS.internalVar->integerValue )
    return (const char *)Sys_ListFiles(directory, v4, list);
  dir_cache_index = this->dir_cache_index;
  i = dir_cache_index - 1;
  if ( dir_cache_index - 1 < dir_cache_index - this->dir_cache_count )
  {
LABEL_11:
    result = (const char *)Sys_ListFiles(directory, v4, list);
    extensiona = result;
    if ( result != (const char *)-1 )
    {
      idDEntry::Init(&this->dir_cache[this->dir_cache_index], directory, v4, list);
      dir_cache_count = this->dir_cache_count;
      this->dir_cache_index = (this->dir_cache_index + 1) % 6;
      if ( dir_cache_count < 6 )
        this->dir_cache_count = dir_cache_count + 1;
      return extensiona;
    }
  }
  else
  {
    v8 = dir_cache_index - 1 + 6;
    while ( idStr::Icmp(this->dir_cache[v8 % 6].directory.data, directory)
         || idStr::Icmp(this->dir_cache[v8 % 6].extension.data, extension) )
    {
      --v8;
      if ( --i < this->dir_cache_index - this->dir_cache_count )
      {
        v4 = extension;
        goto LABEL_11;
      }
    }
    v9 = (char *)this + 84 * (v8 % 6);
    if ( v9 == (char *)-1392 )
      idList<idStr>::operator=(list, 0);
    else
      idList<idStr>::operator=(list, (_DWORD *)v9 + 349);
    return (const char *)list->num;
  }
  return result;
}

// FUNC: public: virtual bool __thiscall idFileSystemLocal::UpdateGamePakChecksums(void)
char __usercall idFileSystemLocal::UpdateGamePakChecksums@<al>(idFileSystemLocal *this@<ecx>, idFile_InZip *a2@<edi>)
{
  idFileSystemLocal *len; // ebx
  pack_t **i; // ebp
  fileInPack_s *v4; // esi
  idFile_InZip *FileFromZip; // esi
  int v6; // eax
  fileInPack_s *v7; // eax
  idFile_InZip_vtbl *v8; // edi
  int v9; // eax
  idLexer *v10; // edi
  int v11; // eax
  idLexer *v12; // eax
  idLexer *v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // ebx
  int v17; // eax
  const char *v19; // [esp-Ch] [ebp-84h]
  char *buf; // [esp+Ch] [ebp-6Ch]
  fileInPack_s *pakFile; // [esp+10h] [ebp-68h]
  int confHash; // [esp+14h] [ebp-64h]
  idToken token; // [esp+1Ch] [ebp-5Ch] BYREF
  int v25; // [esp+74h] [ebp-4h]
  void *retaddr; // [esp+78h] [ebp+0h]

  token.floatvalue = 0.0;
  len = this;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v25 = 0;
  confHash = idFileSystemLocal::HashFileName(this, "binary.conf");
  len->gamePakForOS[0] = 0;
  len->gamePakForOS[1] = 0;
  len->gamePakForOS[2] = 0;
  len->gamePakForOS[3] = 0;
  len->gamePakForOS[4] = 0;
  len->gamePakForOS[5] = 0;
  for ( i = &len->searchPaths->pack; i; i = (pack_t **)i[2] )
  {
    if ( *i )
    {
      (*i)->binary = BINARY_NO;
      v4 = (*i)->hashTable[confHash];
      if ( v4 )
      {
        while ( 1 )
        {
          if ( !idFileSystemLocal::FilenameCompare(len, v4->name.data, "binary.conf") )
          {
            (*i)->binary = BINARY_YES;
            FileFromZip = idFileSystemLocal::ReadFileFromZip(len, *i, v4, "binary.conf");
            v6 = ((int (__thiscall *)(idFile_InZip *, idFile_InZip *))FileFromZip->Length)(FileFromZip, a2);
            v7 = (fileInPack_s *)Memory::Allocate(v6 + 1);
            v8 = FileFromZip->__vftable;
            pakFile = v7;
            v9 = FileFromZip->Length(FileFromZip);
            v8->Read(FileFromZip, pakFile, v9);
            *((_BYTE *)&pakFile->name.len + FileFromZip->Length(FileFromZip)) = 0;
            v10 = (idLexer *)Memory::Allocate(0xC8u);
            LOBYTE(retaddr) = 1;
            if ( v10 )
            {
              v19 = FileFromZip->GetFullPath(FileFromZip);
              v11 = FileFromZip->Length(FileFromZip);
              idLexer::idLexer(v10, (const char *)pakFile, v11, v19, 0);
              v13 = v12;
              buf = (char *)v12;
            }
            else
            {
              buf = 0;
              v13 = 0;
            }
            LOBYTE(retaddr) = 0;
            while ( idLexer::ReadToken(v13, (idToken *)&token.data) )
            {
              if ( idStr::IsNumeric((const char *)token.alloced) )
              {
                v14 = atoi((const char *)token.alloced);
                v15 = v14;
                if ( v14 < 6 && !len->gamePakForOS[v14] )
                {
                  if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
                  {
                    v16 = *(_DWORD *)common.type;
                    v17 = ((int (__thiscall *)(idFile_InZip *, int))FileFromZip->GetFullPath)(
                            FileFromZip,
                            (*i)->checksum);
                    (*(void (**)(netadrtype_t, const char *, ...))(v16 + 124))(
                      common.type,
                      "Adding game pak checksum for OS %d: %s 0x%x\n",
                      v15,
                      v17);
                    len = (idFileSystemLocal *)token.len;
                  }
                  len->gamePakForOS[v15] = (*i)->checksum;
                }
                v13 = (idLexer *)buf;
              }
            }
            a2 = FileFromZip;
            ((void (__thiscall *)(idFileSystemLocal *))len->CloseFile)(len);
            if ( v13 )
            {
              idLexer::~idLexer(v13);
              Memory::Free(v13);
            }
            Memory::Free(buf);
            v4 = pakFile;
          }
          if ( !v4->next )
            break;
          v4 = v4->next;
        }
      }
    }
  }
  if ( !len->gamePakForOS[0] )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "No game code pak reference found for the local OS");
LABEL_29:
    v25 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  if ( !cvarSystem->GetCVarBool(cvarSystem, "net_serverAllowServerMod") && len->gamePakChecksum != len->gamePakForOS[0] )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "The current game code doesn't match pak files (net_serverAllowServerMod is off)");
    goto LABEL_29;
  }
  v25 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::Shutdown(bool)
void __thiscall idFileSystemLocal::Shutdown(idFileSystemLocal *this, bool reloading)
{
  idFileSystemLocal *v2; // ebp
  idStr *p_gameFolder; // esi
  int v4; // edi
  idFileSystemLocal_vtbl *v5; // eax
  searchpath_s *searchPaths; // ebx
  fileInPack_s *buildBuffer; // eax
  char *p_next; // esi
  addonInfo_t *addon_info; // esi
  idDict **list; // eax
  idDict *v11; // ebp
  addonInfo_t *v12; // esi
  pack_t *pack; // esi
  directory_t *dir; // esi
  searchpath_s *next; // [esp+14h] [ebp-4h]
  searchpath_s *reloadinga; // [esp+1Ch] [ebp+4h]

  v2 = this;
  p_gameFolder = &this->gameFolder;
  idStr::FreeData(&this->gameFolder);
  v4 = 0;
  p_gameFolder->len = 0;
  p_gameFolder->alloced = 20;
  p_gameFolder->data = p_gameFolder->baseBuffer;
  p_gameFolder->baseBuffer[0] = 0;
  if ( v2->serverPaks.list )
    Memory::Free(v2->serverPaks.list);
  v2->serverPaks.list = 0;
  v2->serverPaks.num = 0;
  v2->serverPaks.size = 0;
  if ( !reloading )
  {
    if ( v2->restartChecksums.list )
      Memory::Free(v2->restartChecksums.list);
    v2->restartChecksums.list = 0;
    v2->restartChecksums.num = 0;
    v2->restartChecksums.size = 0;
    if ( v2->addonChecksums.list )
      Memory::Free(v2->addonChecksums.list);
    v2->addonChecksums.list = 0;
    v2->addonChecksums.num = 0;
    v2->addonChecksums.size = 0;
  }
  v5 = v2->__vftable;
  v2->loadedFileFromDir = 0;
  v2->gameDLLChecksum = 0;
  v2->gamePakChecksum = 0;
  v5->ClearDirCache(v2);
  searchPaths = v2->searchPaths;
  reloadinga = searchPaths;
  if ( searchPaths )
  {
    while ( 1 )
    {
      do
      {
        next = searchPaths->next;
        if ( searchPaths->pack )
        {
          unzClose(searchPaths->pack->handle);
          buildBuffer = searchPaths->pack->buildBuffer;
          if ( buildBuffer )
          {
            p_next = (char *)&buildBuffer[-1].next;
            `eh vector destructor iterator'(
              buildBuffer,
              0x28u,
              (int)buildBuffer[-1].next,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(p_next);
          }
          addon_info = searchPaths->pack->addon_info;
          if ( addon_info )
          {
            if ( addon_info->mapDecls.num > 0 )
            {
              do
              {
                list = addon_info->mapDecls.list;
                v11 = list[v4];
                if ( v11 )
                {
                  idDict::~idDict(list[v4]);
                  Memory::Free(v11);
                }
                addon_info->mapDecls.list[v4++] = 0;
              }
              while ( v4 < addon_info->mapDecls.num );
              v2 = this;
              v4 = 0;
            }
            if ( addon_info->mapDecls.list )
              Memory::Free(addon_info->mapDecls.list);
            addon_info->mapDecls.list = 0;
            addon_info->mapDecls.num = 0;
            addon_info->mapDecls.size = 0;
            v12 = searchPaths->pack->addon_info;
            if ( v12 )
            {
              addonInfo_t::~addonInfo_t(searchPaths->pack->addon_info);
              Memory::Free(v12);
            }
          }
          pack = searchPaths->pack;
          if ( searchPaths->pack )
          {
            idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s((idPoolStr *)searchPaths->pack);
            Memory::Free(pack);
          }
        }
        dir = searchPaths->dir;
        if ( dir )
        {
          directory_t::~directory_t(searchPaths->dir);
          Memory::Free(dir);
        }
        Memory::Free(searchPaths);
        searchPaths = next;
      }
      while ( next );
      if ( reloadinga != v2->searchPaths )
        break;
      reloadinga = v2->addonPaks;
      if ( !reloadinga )
        break;
      searchPaths = reloadinga;
    }
  }
  v2->searchPaths = 0;
  v2->addonPaks = 0;
  cmdSystem->RemoveCommand(cmdSystem, "path");
  cmdSystem->RemoveCommand(cmdSystem, "dir");
  cmdSystem->RemoveCommand(cmdSystem, "dirtree");
  cmdSystem->RemoveCommand(cmdSystem, "touchFile");
  idDict::Clear(&v2->mapDict);
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::ClearDirCache(void)
void __thiscall idFileSystemLocal::ClearDirCache(idFileSystemLocal *this)
{
  idDEntry *dir_cache; // esi
  int v2; // edi

  this->dir_cache_index = 0;
  this->dir_cache_count = 0;
  dir_cache = this->dir_cache;
  v2 = 6;
  do
  {
    idDEntry::Clear(dir_cache++);
    --v2;
  }
  while ( v2 );
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::WriteAssetLog(void)
void __thiscall idFileSystemLocal::WriteAssetLog(idFileSystemLocal *this)
{
  int len; // esi
  int v3; // edi
  char *data; // ecx
  char *v5; // edx
  char v6; // al
  int v7; // esi
  int v8; // eax
  char v9; // cl
  char *v10; // edx
  idFile *v11; // esi
  int v12; // ebx
  idStr *list; // eax
  char *v14; // esi
  idStr filename; // [esp+20h] [ebp-2Ch] BYREF
  int v16; // [esp+48h] [ebp-4h]

  len = this->currentAssetLog.len;
  filename.data = filename.baseBuffer;
  v3 = 0;
  filename.len = 0;
  filename.alloced = 20;
  filename.baseBuffer[0] = 0;
  if ( len + 1 > 20 )
    idStr::ReAllocate(&filename, len + 1, 1);
  data = this->currentAssetLog.data;
  v5 = filename.data;
  do
  {
    v6 = *data;
    *v5++ = *data++;
  }
  while ( v6 );
  filename.len = len;
  v7 = len + 4;
  v16 = 0;
  if ( v7 + 1 > filename.alloced )
    idStr::ReAllocate(&filename, v7 + 1, 1);
  v8 = 0;
  v9 = 46;
  do
  {
    v10 = &filename.data[v8++];
    v10[filename.len] = v9;
    v9 = aTxt[v8];
  }
  while ( v9 );
  filename.len = v7;
  filename.data[v7] = 0;
  v11 = fileSystem->OpenFileWrite(fileSystem, filename.data, "fs_savepath", 0);
  if ( v11 )
  {
    if ( this->assetLog.num > 0 )
    {
      v12 = 0;
      do
      {
        v11->Write(v11, this->assetLog.list[v12].data, strlen(this->assetLog.list[v12].data));
        v11->Write(v11, "\n", 1);
        ++v3;
        ++v12;
      }
      while ( v3 < this->assetLog.num );
    }
    v11->Flush(v11);
    fileSystem->CloseFile(fileSystem, v11);
    list = this->assetLog.list;
    if ( list )
    {
      v14 = &list[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        list,
        0x20u,
        *(_DWORD *)&list[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v14);
    }
    this->assetLog.list = 0;
    this->assetLog.num = 0;
    this->assetLog.size = 0;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't write %s.\n",
      filename.data);
  }
  v16 = -1;
  idStr::FreeData(&filename);
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::ClearAssetLog(void)
void __thiscall idFileSystemLocal::ClearAssetLog(idFileSystemLocal *this)
{
  idStr *list; // eax
  char *v3; // edi

  list = this->assetLog.list;
  if ( list )
  {
    v3 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v3);
  }
  this->assetLog.list = 0;
  this->assetLog.num = 0;
  this->assetLog.size = 0;
}

// FUNC: public: __thiscall idDEntry::idDEntry(void)
void __thiscall idDEntry::idDEntry(idDEntry *this)
{
  char *baseBuffer; // ecx

  this->granularity = 16;
  this->list = 0;
  this->num = 0;
  this->size = 0;
  this->__vftable = (idDEntry_vtbl *)&idDEntry::`vftable';
  this->directory.len = 0;
  this->directory.alloced = 20;
  baseBuffer = this->directory.baseBuffer;
  this->directory.data = baseBuffer;
  *baseBuffer = 0;
  this->extension.len = 0;
  this->extension.alloced = 20;
  this->extension.data = this->extension.baseBuffer;
  this->extension.baseBuffer[0] = 0;
}

// FUNC: public: virtual __thiscall idDEntry::~idDEntry(void)
void __thiscall idDEntry::~idDEntry(idDEntry *this)
{
  idStr *list; // eax
  char *v3; // edi

  this->__vftable = (idDEntry_vtbl *)&idDEntry::`vftable';
  idStr::FreeData(&this->extension);
  idStr::FreeData(&this->directory);
  list = this->list;
  if ( list )
  {
    v3 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v3);
  }
  this->list = 0;
  this->num = 0;
  this->size = 0;
}

// FUNC: public: __thiscall idFileSystemLocal::idFileSystemLocal(void)
void __thiscall idFileSystemLocal::idFileSystemLocal(idFileSystemLocal *this)
{
  idDict *p_mapDict; // edi
  idKeyValue *list; // ebp
  int num; // ecx
  int v5; // eax
  int i; // eax
  idKeyValue *v7; // ecx
  idHashIndex *p_argHash; // [esp+10h] [ebp-18h]

  this->__vftable = (idFileSystemLocal_vtbl *)&idFileSystemLocal::`vftable';
  this->gameFolder.len = 0;
  this->gameFolder.alloced = 20;
  this->gameFolder.data = this->gameFolder.baseBuffer;
  this->gameFolder.baseBuffer[0] = 0;
  p_mapDict = &this->mapDict;
  this->mapDict.args.granularity = 16;
  this->mapDict.args.list = 0;
  this->mapDict.args.num = 0;
  this->mapDict.args.size = 0;
  p_argHash = &this->mapDict.argHash;
  idHashIndex::Init(&this->mapDict.argHash, 1024, 1024);
  p_mapDict->args.granularity = 16;
  list = p_mapDict->args.list;
  if ( list )
  {
    num = p_mapDict->args.num;
    v5 = p_mapDict->args.num + 15 - (p_mapDict->args.num + 15) % 16;
    if ( v5 != p_mapDict->args.size )
    {
      if ( v5 > 0 )
      {
        p_mapDict->args.size = v5;
        if ( v5 < num )
          p_mapDict->args.num = v5;
        p_mapDict->args.list = (idKeyValue *)Memory::Allocate(8 * v5);
        for ( i = 0; i < p_mapDict->args.num; ++i )
        {
          v7 = p_mapDict->args.list;
          v7[i].key = list[i].key;
          v7[i].value = list[i].value;
        }
        Memory::Free(list);
      }
      else
      {
        Memory::Free(list);
        p_mapDict->args.list = 0;
        p_mapDict->args.num = 0;
        p_mapDict->args.size = 0;
      }
    }
  }
  p_mapDict->argHash.granularity = 16;
  idHashIndex::Free(p_argHash);
  p_argHash->hashSize = 128;
  p_argHash->indexSize = 16;
  this->currentAssetLog.len = 0;
  this->currentAssetLog.alloced = 20;
  this->currentAssetLog.data = this->currentAssetLog.baseBuffer;
  this->currentAssetLog.baseBuffer[0] = 0;
  this->currentAssetLogUnfiltered.len = 0;
  this->currentAssetLogUnfiltered.alloced = 20;
  this->currentAssetLogUnfiltered.data = this->currentAssetLogUnfiltered.baseBuffer;
  this->currentAssetLogUnfiltered.baseBuffer[0] = 0;
  this->assetLog.granularity = 16;
  this->assetLog.list = 0;
  this->assetLog.num = 0;
  this->assetLog.size = 0;
  this->defaultBackgroundDownload.url.url.len = 0;
  this->defaultBackgroundDownload.url.url.alloced = 20;
  this->defaultBackgroundDownload.url.url.data = this->defaultBackgroundDownload.url.url.baseBuffer;
  this->defaultBackgroundDownload.url.url.baseBuffer[0] = 0;
  this->serverPaks.granularity = 16;
  this->serverPaks.list = 0;
  this->serverPaks.num = 0;
  this->serverPaks.size = 0;
  this->restartChecksums.granularity = 16;
  this->restartChecksums.list = 0;
  this->restartChecksums.num = 0;
  this->restartChecksums.size = 0;
  this->addonChecksums.granularity = 16;
  this->addonChecksums.list = 0;
  this->addonChecksums.num = 0;
  this->addonChecksums.size = 0;
  `eh vector constructor iterator'(
    this->dir_cache,
    0x54u,
    6,
    (void (__thiscall *)(void *))idDEntry::idDEntry,
    (void (__thiscall *)(void *))idDEntry::~idDEntry);
  this->searchPaths = 0;
  this->readCount = 0;
  this->loadCount = 0;
  this->loadStack = 0;
  this->dir_cache_index = 0;
  this->dir_cache_count = 0;
  this->d3xp = 0;
  this->loadedFileFromDir = 0;
  this->restartGamePakChecksum = 0;
  this->backgroundThread.name = 0;
  this->backgroundThread.threadHandle = 0;
  this->backgroundThread.threadId = 0;
  this->addonPaks = 0;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::ResetReadCount(void)
void __thiscall idFileSystemLocal::ResetReadCount(idFileSystemLocal *this)
{
  this->readCount = 0;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::AddToReadCount(int)
void __thiscall idFileSystemLocal::AddToReadCount(idFileSystemLocal *this, int c)
{
  this->readCount += c;
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::GetNewFileMemory(void)
void __thiscall idFileSystemLocal::GetNewFileMemory(idFileSystemLocal *this)
{
  idFile_Memory *v1; // eax

  v1 = (idFile_Memory *)Memory::Allocate(0x40u);
  if ( v1 )
    idFile_Memory::idFile_Memory(v1);
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::GetNewFilePermanent(void)
void __thiscall idFileSystemLocal::GetNewFilePermanent(idFileSystemLocal *this)
{
  idFile_Permanent *v1; // eax

  v1 = (idFile_Permanent *)Memory::Allocate(0x54u);
  if ( v1 )
    idFile_Permanent::idFile_Permanent(v1);
}

// FUNC: public: virtual char const * __thiscall idFileSystemLocal::GetAssetLogName(void)
char *__thiscall idFileSystemLocal::GetAssetLogName(idFileSystemLocal *this)
{
  return this->currentAssetLog.data;
}

// FUNC: private: struct _iobuf * __thiscall idFileSystemLocal::OpenOSFile(char const *,char const *,class idStr *)
_iobuf *__thiscall idFileSystemLocal::OpenOSFile(
        idFileSystemLocal *this,
        char *fileName,
        const char *mode,
        idStr *caseSensitiveName)
{
  idSys_vtbl *v5; // eax
  char *v6; // esi
  const idStr *v8; // eax
  idStr *v9; // esi
  unsigned int len; // ebp
  int v11; // eax
  int v12; // esi
  char *v13; // esi
  int i; // [esp+10h] [ebp-A8h]
  int ia; // [esp+10h] [ebp-A8h]
  idList<idStr> list; // [esp+14h] [ebp-A4h] BYREF
  unsigned int v17; // [esp+24h] [ebp-94h]
  _iobuf *fp; // [esp+28h] [ebp-90h]
  idStr entry; // [esp+2Ch] [ebp-8Ch] BYREF
  idStr fpath; // [esp+4Ch] [ebp-6Ch] BYREF
  idStr v21; // [esp+6Ch] [ebp-4Ch] BYREF
  idStr result; // [esp+8Ch] [ebp-2Ch] BYREF
  int v23; // [esp+B4h] [ebp-4h]

  fpath.len = 0;
  fpath.alloced = 20;
  fpath.data = fpath.baseBuffer;
  fpath.baseBuffer[0] = 0;
  v23 = 0;
  entry.len = 0;
  entry.alloced = 20;
  entry.data = entry.baseBuffer;
  entry.baseBuffer[0] = 0;
  list.granularity = 16;
  list.list = 0;
  list.num = 0;
  list.size = 0;
  v5 = sys->__vftable;
  LOBYTE(v23) = 2;
  fp = v5->FOpen(sys, fileName, mode);
  if ( fp || !idFileSystemLocal::fs_caseSensitiveOS.internalVar->integerValue )
  {
    if ( caseSensitiveName )
    {
      idStr::operator=(caseSensitiveName, fileName);
      idStr::StripPath(caseSensitiveName);
    }
LABEL_24:
    LOBYTE(v23) = 1;
    if ( list.list )
    {
      v13 = &list.list[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        list.list,
        0x20u,
        *(_DWORD *)&list.list[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v13);
    }
    list.list = 0;
    list.num = 0;
    list.size = 0;
    LOBYTE(v23) = 0;
    idStr::FreeData(&entry);
    v23 = -1;
    idStr::FreeData(&fpath);
    return fp;
  }
  else
  {
    idStr::operator=(&fpath, fileName);
    idStr::StripFilename(&fpath);
    idStr::StripTrailing(&fpath, 47);
    if ( idFileSystemLocal::ListOSFiles(this, fpath.data, 0, &list) != (const char *)-1 )
    {
      i = 0;
      if ( list.num <= 0 )
        goto LABEL_24;
      v17 = 0;
      while ( 1 )
      {
        v8 = operator+(&result, &fpath, 47);
        LOBYTE(v23) = 3;
        v9 = operator+(&v21, v8, &list.list[v17 / 0x20]);
        len = v9->len;
        v11 = v9->len + 1;
        LOBYTE(v23) = 4;
        if ( v11 > entry.alloced )
          idStr::ReAllocate(&entry, v11, 0);
        qmemcpy(entry.data, v9->data, len);
        entry.data[len] = 0;
        entry.len = len;
        LOBYTE(v23) = 3;
        idStr::FreeData(&v21);
        LOBYTE(v23) = 2;
        idStr::FreeData(&result);
        if ( !idStr::Icmp(entry.data, fileName) )
        {
          fp = sys->FOpen(sys, entry.data, mode);
          if ( fp )
          {
            if ( caseSensitiveName )
            {
              v12 = entry.len;
              ia = entry.len;
              if ( entry.len + 1 > caseSensitiveName->alloced )
                idStr::ReAllocate(caseSensitiveName, entry.len + 1, 0);
              qmemcpy(caseSensitiveName->data, entry.data, v12);
              caseSensitiveName->data[ia] = 0;
              caseSensitiveName->len = ia;
              idStr::StripPath(caseSensitiveName);
            }
            if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                common.type,
                "idFileSystemLocal::OpenFileRead: changed %s to %s\n",
                fileName,
                entry.data);
            goto LABEL_24;
          }
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "idFileSystemLocal::OpenFileRead: fs_caseSensitiveOS 1 could not open %s",
            entry.data);
        }
        v17 += 32;
        if ( ++i >= list.num )
          goto LABEL_24;
      }
    }
    LOBYTE(v23) = 1;
    if ( list.list )
    {
      v6 = &list.list[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        list.list,
        0x20u,
        *(_DWORD *)&list.list[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v6);
    }
    list.list = 0;
    list.num = 0;
    list.size = 0;
    LOBYTE(v23) = 0;
    idStr::FreeData(&entry);
    v23 = -1;
    idStr::FreeData(&fpath);
    return 0;
  }
}

// FUNC: private: struct _iobuf * __thiscall idFileSystemLocal::OpenOSFileCorrectName(class idStr &,char const *)
_iobuf *__thiscall idFileSystemLocal::OpenOSFileCorrectName(idFileSystemLocal *this, idStr *path, const char *mode)
{
  _iobuf *v3; // ebp
  int v4; // edi
  int v5; // eax
  int v6; // eax
  char v7; // cl
  char *v8; // eax
  int v9; // edi
  int i; // eax
  char *v11; // eax
  char *data; // [esp-Ch] [ebp-40h]
  idStr caseName; // [esp+8h] [ebp-2Ch] BYREF
  int v15; // [esp+30h] [ebp-4h]

  caseName.len = 0;
  caseName.alloced = 20;
  caseName.data = caseName.baseBuffer;
  caseName.baseBuffer[0] = 0;
  data = path->data;
  v15 = 0;
  v3 = idFileSystemLocal::OpenOSFile(this, data, mode, &caseName);
  if ( v3 )
  {
    idStr::StripFilename(path);
    v4 = path->len + 1;
    v5 = path->len + 2;
    if ( v5 > path->alloced )
      idStr::ReAllocate(path, v5, 1);
    v6 = 0;
    v7 = 47;
    do
    {
      ++v6;
      path->data[path->len - 1 + v6] = v7;
      v7 = b[v6];
    }
    while ( v7 );
    v8 = path->data;
    path->len = v4;
    v8[v4] = 0;
    v9 = caseName.len + path->len;
    if ( v9 + 1 > path->alloced )
      idStr::ReAllocate(path, v9 + 1, 1);
    for ( i = 0; i < caseName.len; ++i )
      path->data[path->len + i] = caseName.data[i];
    v11 = path->data;
    path->len = v9;
    v11[v9] = 0;
  }
  v15 = -1;
  idStr::FreeData(&caseName);
  return v3;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::CopyOSFile(char const *,char const *)
void __userpurge idFileSystemLocal::CopyOSFile(
        idFileSystemLocal *this@<ecx>,
        int a2@<edi>,
        char *fromOSPath,
        char *toOSPath)
{
  _iobuf *v6; // eax
  _iobuf *v7; // esi
  int v8; // edi
  DWORD FileAttributesA; // eax
  _iobuf *v10; // esi
  int v12; // [esp+0h] [ebp-10h]
  char *toOSPatha; // [esp+18h] [ebp+8h]

  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "copy %s to %s\n",
    fromOSPath,
    toOSPath);
  v6 = idFileSystemLocal::OpenOSFile(this, fromOSPath, "rb", 0);
  v7 = v6;
  if ( v6 )
  {
    v8 = idFileSystemLocal::DirectFileLength(this, v6);
    toOSPatha = (char *)Mem_Alloc(v8, 0xBu);
    if ( ((int (__thiscall *)(idSys *, char *, int, int, _iobuf *, int))sys->FRead)(sys, toOSPatha, 1, v8, v7, a2) != v8 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "short read in idFileSystemLocal::CopyOSFile()\n");
    sys->FClose(sys, v7);
    this->CreateOSPath(this, toOSPath);
    if ( strstr(toOSPath, "/game/") )
    {
      FileAttributesA = GetFileAttributesA(toOSPath);
      if ( FileAttributesA != -1 && (FileAttributesA & 1) != 0 )
      {
        LOBYTE(FileAttributesA) = FileAttributesA & 0xFE;
        SetFileAttributesA(toOSPath, FileAttributesA);
      }
    }
    v10 = idFileSystemLocal::OpenOSFile(this, toOSPath, "wb", 0);
    if ( v10 )
    {
      if ( ((int (__thiscall *)(idSys *, char *, int, int, _iobuf *, int))sys->FWrite)(sys, toOSPatha, 1, v8, v10, v12) != v8 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
          common.type,
          "Quake 4 cannot run due to insufficient disk space.\n");
      sys->FClose(sys, v10);
      Mem_Free(toOSPatha);
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "could not create destination file\n");
      Mem_Free(toOSPatha);
    }
  }
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::CopyOSFile(class idFile *,char const *)
void __thiscall idFileSystemLocal::CopyOSFile(idFileSystemLocal *this, idFile *src, char *toOSPath)
{
  int v5; // edi
  int v6; // eax
  int v7; // edi
  void *v8; // ebx
  _iobuf *v9; // eax
  _iobuf *v10; // esi

  v5 = *(_DWORD *)common.type;
  v6 = ((int (__thiscall *)(idFile *, char *))src->GetName)(src, toOSPath);
  (*(void (__cdecl **)(netadrtype_t, const char *, int))(v5 + 124))(common.type, "copy %s to %s\n", v6);
  src->Seek(src, 0, FS_SEEK_END);
  v7 = src->Tell(src);
  src->Seek(src, 0, FS_SEEK_SET);
  v8 = Mem_Alloc(v7, 0xBu);
  if ( src->Read(src, v8, v7) != v7 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Short read in idFileSystemLocal::CopyOSFile");
  this->CreateOSPath(this, toOSPath);
  v9 = idFileSystemLocal::OpenOSFile(this, toOSPath, "wb", 0);
  v10 = v9;
  if ( v9 )
  {
    if ( sys->FWrite(sys, v8, 1, v7, v9) != v7 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "Quake 4 cannot run due to insufficient disk space.");
    sys->FClose(sys, v10);
    Mem_Free(v8);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "could not create destination file\n");
    Mem_Free(v8);
  }
}

// FUNC: private: struct addonInfo_t * __thiscall idFileSystemLocal::ParseAddonDef(char const *,int)
addonInfo_t *__thiscall idFileSystemLocal::ParseAddonDef(idFileSystemLocal *this, const char *buf, int len)
{
  addonInfo_t *v4; // eax
  addonInfo_t *v5; // eax
  addonInfo_t *v6; // esi
  int granularity; // eax
  bool v8; // cc
  int i; // eax
  int num; // ebx
  int size; // ebp
  int v12; // ecx
  int *list; // edi
  int j; // eax
  idDict *v15; // edi
  idKeyValue *v16; // ebp
  int v17; // ecx
  int v18; // eax
  int m; // eax
  idKeyValue *v20; // ecx
  idDict *v21; // ebx
  int v22; // eax
  int jj; // eax
  int v24; // ebx
  int v25; // ecx
  int v26; // ecx
  idDict **v27; // edi
  int kk; // eax
  int k; // ebp
  idDict *v30; // edi
  idKeyValue *v31; // eax
  bool v32; // zf
  int mm; // edi
  idDict *v34; // ebp
  idKeyValue *v35; // eax
  int n; // edi
  idDict *v37; // ebp
  idKeyValue *v38; // eax
  int ii; // edi
  idDict *v40; // ebp
  idKeyValue *v41; // eax
  idKeyValue *v42; // eax
  idDict *v43; // [esp+4h] [ebp-17Ch]
  int checksum; // [esp+8h] [ebp-178h] BYREF
  idToken token; // [esp+Ch] [ebp-174h] BYREF
  idToken token2; // [esp+5Ch] [ebp-124h] BYREF
  idLexer src; // [esp+ACh] [ebp-D4h] BYREF
  int v48; // [esp+17Ch] [ebp-4h]

  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v48 = 2;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  token2.floatvalue = 0.0;
  token2.len = 0;
  token2.alloced = 20;
  token2.data = token2.baseBuffer;
  token2.baseBuffer[0] = 0;
  idLexer::LoadMemory(&src, buf, len, "<addon.conf>", 1);
  src.flags = 6300;
  if ( !idLexer::SkipUntilString(&src, "addonDef") )
  {
    idLexer::Warning(&src, "ParseAddonDef: no addonDef");
LABEL_5:
    LOBYTE(v48) = 1;
    idStr::FreeData(&token2);
    LOBYTE(v48) = 0;
    idStr::FreeData(&token);
    v48 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
  if ( !idLexer::ReadToken(&src, &token) )
  {
    idLexer::Warning(&src, "Expected {");
    goto LABEL_5;
  }
  v4 = (addonInfo_t *)Memory::Allocate(0x20u);
  checksum = (int)v4;
  LOBYTE(v48) = 3;
  if ( v4 )
  {
    addonInfo_t::addonInfo_t(v4);
    v6 = v5;
  }
  else
  {
    v6 = 0;
  }
  LOBYTE(v48) = 2;
  if ( idLexer::ReadToken(&src, &token) )
  {
    while ( idStr::Icmp(token.data, "}") )
    {
      if ( token.type != 1 )
      {
        idLexer::Warning(&src, "Expected quoted string, but found '%s'", token.data);
        goto LABEL_128;
      }
      if ( sscanf(token.data, "0x%x", &checksum) != 1 && sscanf(token.data, "%x", &checksum) != 1 )
      {
        idLexer::Warning(&src, "Could not parse checksum '%s'", token.data);
        goto LABEL_128;
      }
      if ( !v6->depends.list )
      {
        granularity = v6->depends.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != v6->depends.size )
          {
            v8 = granularity < v6->depends.num;
            v6->depends.size = granularity;
            if ( v8 )
              v6->depends.num = granularity;
            v6->depends.list = (int *)Memory::Allocate(4 * granularity);
            for ( i = 0; i < v6->depends.num; ++i )
              v6->depends.list[i] = *(_DWORD *)(4 * i);
          }
        }
        else
        {
          v6->depends.list = 0;
          v6->depends.num = 0;
          v6->depends.size = 0;
        }
      }
      num = v6->depends.num;
      size = v6->depends.size;
      if ( v6->depends.num == size )
      {
        if ( !v6->depends.granularity )
          v6->depends.granularity = 16;
        v12 = v6->depends.granularity + size - (v6->depends.granularity + size) % v6->depends.granularity;
        if ( v12 > 0 )
        {
          if ( v12 != size )
          {
            list = v6->depends.list;
            v6->depends.size = v12;
            if ( v12 < num )
              v6->depends.num = v12;
            v6->depends.list = (int *)Memory::Allocate(4 * v12);
            for ( j = 0; j < v6->depends.num; ++j )
              v6->depends.list[j] = list[j];
            if ( list )
              Memory::Free(list);
          }
        }
        else
        {
          if ( v6->depends.list )
            Memory::Free(v6->depends.list);
          v6->depends.list = 0;
          v6->depends.num = 0;
          v6->depends.size = 0;
        }
      }
      v6->depends.list[v6->depends.num++] = checksum;
      if ( !idLexer::ReadToken(&src, &token) )
        goto LABEL_128;
    }
    if ( !idLexer::SkipUntilString(&src, "mapDef") )
    {
LABEL_83:
      LOBYTE(v48) = 1;
      idStr::FreeData(&token2);
      LOBYTE(v48) = 0;
      idStr::FreeData(&token);
      v48 = -1;
      idLexer::~idLexer(&src);
      return v6;
    }
    while ( 1 )
    {
      if ( !idLexer::ReadToken(&src, &token) )
      {
        idLexer::Warning(&src, "Expected map path");
        for ( k = 0; k < v6->mapDecls.num; ++k )
        {
          v30 = v6->mapDecls.list[k];
          if ( v30 )
          {
            LOBYTE(v48) = 5;
            idDict::Clear(v30);
            LOBYTE(v48) = 4;
            idHashIndex::Free(&v30->argHash);
            v31 = v30->args.list;
            LOBYTE(v48) = 2;
            if ( v31 )
              Memory::Free(v31);
            v30->args.list = 0;
            v30->args.num = 0;
            v30->args.size = 0;
            Memory::Free(v30);
          }
          v6->mapDecls.list[k] = 0;
        }
        if ( v6->mapDecls.list )
          Memory::Free(v6->mapDecls.list);
        v6->mapDecls.list = 0;
        v6->mapDecls.num = 0;
        v6->mapDecls.size = 0;
        v32 = v6 == 0;
        goto LABEL_129;
      }
      v15 = (idDict *)Memory::Allocate(0x2Cu);
      if ( v15 )
      {
        v15->args.granularity = 16;
        v15->args.list = 0;
        v15->args.num = 0;
        v15->args.size = 0;
        LOBYTE(v48) = 7;
        idHashIndex::Init(&v15->argHash, 1024, 1024);
        v15->args.granularity = 16;
        v16 = v15->args.list;
        LOBYTE(v48) = 8;
        if ( v16 )
        {
          v17 = v15->args.num;
          v18 = v15->args.num + 15 - (v15->args.num + 15) % 16;
          if ( v18 != v15->args.size )
          {
            if ( v18 > 0 )
            {
              v15->args.size = v18;
              if ( v18 < v17 )
                v15->args.num = v18;
              v15->args.list = (idKeyValue *)Memory::Allocate(8 * v18);
              for ( m = 0; m < v15->args.num; ++m )
              {
                v20 = v15->args.list;
                v20[m].key = v16[m].key;
                v20[m].value = v16[m].value;
              }
              Memory::Free(v16);
            }
            else
            {
              Memory::Free(v16);
              v15->args.list = 0;
              v15->args.num = 0;
              v15->args.size = 0;
            }
          }
        }
        v15->argHash.granularity = 16;
        idHashIndex::Free(&v15->argHash);
        v15->argHash.hashSize = 128;
        v15->argHash.indexSize = 16;
        v21 = v15;
        v43 = v15;
      }
      else
      {
        v43 = 0;
        v21 = 0;
      }
      LOBYTE(v48) = 2;
      idDict::Set(v21, "path", token.data);
      if ( !idLexer::ReadToken(&src, &token) )
        break;
      if ( idLexer::ReadToken(&src, &token) )
      {
        while ( idStr::Icmp(token.data, "}") )
        {
          if ( token.type != 1 )
          {
            idLexer::Warning(&src, "Expected quoted string, but found '%s'", token.data);
            for ( n = 0; n < v6->mapDecls.num; ++n )
            {
              v37 = v6->mapDecls.list[n];
              if ( v37 )
              {
                LOBYTE(v48) = 14;
                idDict::Clear(v37);
                LOBYTE(v48) = 13;
                idHashIndex::Free(&v37->argHash);
                v38 = v37->args.list;
                LOBYTE(v48) = 2;
                if ( v38 )
                  Memory::Free(v38);
                v37->args.list = 0;
                v37->args.num = 0;
                v37->args.size = 0;
                Memory::Free(v37);
              }
              v6->mapDecls.list[n] = 0;
            }
            if ( v6->mapDecls.list )
              Memory::Free(v6->mapDecls.list);
            v6->mapDecls.list = 0;
            v6->mapDecls.num = 0;
            v6->mapDecls.size = 0;
            if ( v21 )
            {
              LOBYTE(v48) = 16;
              idDict::Clear(v21);
              LOBYTE(v48) = 15;
              goto LABEL_123;
            }
            goto LABEL_128;
          }
          if ( !idLexer::ReadToken(&src, &token2) )
          {
            idLexer::Warning(&src, "Unexpected end of file");
            for ( ii = 0; ii < v6->mapDecls.num; ++ii )
            {
              v40 = v6->mapDecls.list[ii];
              if ( v40 )
              {
                LOBYTE(v48) = 18;
                idDict::Clear(v40);
                LOBYTE(v48) = 17;
                idHashIndex::Free(&v40->argHash);
                v41 = v40->args.list;
                LOBYTE(v48) = 2;
                if ( v41 )
                  Memory::Free(v41);
                v40->args.list = 0;
                v40->args.num = 0;
                v40->args.size = 0;
                Memory::Free(v40);
              }
              v6->mapDecls.list[ii] = 0;
            }
            if ( v6->mapDecls.list )
              Memory::Free(v6->mapDecls.list);
            v6->mapDecls.list = 0;
            v6->mapDecls.num = 0;
            v6->mapDecls.size = 0;
            if ( v21 )
            {
              LOBYTE(v48) = 20;
              idDict::Clear(v21);
              LOBYTE(v48) = 19;
              goto LABEL_123;
            }
            goto LABEL_128;
          }
          if ( idDict::FindKey(v21, token.data) )
            idLexer::Warning(&src, "'%s' already defined", token.data);
          idDict::Set(v21, token.data, token2.data);
          if ( !idLexer::ReadToken(&src, &token) )
            break;
        }
      }
      if ( !v6->mapDecls.list )
      {
        v22 = v6->mapDecls.granularity;
        if ( v22 > 0 )
        {
          if ( v22 != v6->mapDecls.size )
          {
            v8 = v22 < v6->mapDecls.num;
            v6->mapDecls.size = v22;
            if ( v8 )
              v6->mapDecls.num = v22;
            v6->mapDecls.list = (idDict **)Memory::Allocate(4 * v22);
            for ( jj = 0; jj < v6->mapDecls.num; ++jj )
              v6->mapDecls.list[jj] = *(idDict **)(4 * jj);
          }
        }
        else
        {
          v6->mapDecls.list = 0;
          v6->mapDecls.num = 0;
          v6->mapDecls.size = 0;
        }
      }
      v24 = v6->mapDecls.num;
      v25 = v6->mapDecls.size;
      if ( v24 == v25 )
      {
        if ( !v6->mapDecls.granularity )
          v6->mapDecls.granularity = 16;
        v26 = v6->mapDecls.granularity + v25 - (v6->mapDecls.granularity + v25) % v6->mapDecls.granularity;
        if ( v26 > 0 )
        {
          if ( v26 != v6->mapDecls.size )
          {
            v27 = v6->mapDecls.list;
            v6->mapDecls.size = v26;
            if ( v26 < v24 )
              v6->mapDecls.num = v26;
            v6->mapDecls.list = (idDict **)Memory::Allocate(4 * v26);
            for ( kk = 0; kk < v6->mapDecls.num; ++kk )
              v6->mapDecls.list[kk] = v27[kk];
            if ( v27 )
              Memory::Free(v27);
          }
        }
        else
        {
          if ( v6->mapDecls.list )
            Memory::Free(v6->mapDecls.list);
          v6->mapDecls.list = 0;
          v6->mapDecls.num = 0;
          v6->mapDecls.size = 0;
        }
      }
      v6->mapDecls.list[v6->mapDecls.num++] = v43;
      if ( !idLexer::SkipUntilString(&src, "mapDef") )
        goto LABEL_83;
    }
    idLexer::Warning(&src, "Expected {");
    for ( mm = 0; mm < v6->mapDecls.num; ++mm )
    {
      v34 = v6->mapDecls.list[mm];
      if ( v34 )
      {
        LOBYTE(v48) = 10;
        idDict::Clear(v34);
        LOBYTE(v48) = 9;
        idHashIndex::Free(&v34->argHash);
        v35 = v34->args.list;
        LOBYTE(v48) = 2;
        if ( v35 )
          Memory::Free(v35);
        v34->args.list = 0;
        v34->args.num = 0;
        v34->args.size = 0;
        Memory::Free(v34);
      }
      v6->mapDecls.list[mm] = 0;
    }
    if ( v6->mapDecls.list )
      Memory::Free(v6->mapDecls.list);
    v6->mapDecls.list = 0;
    v6->mapDecls.num = 0;
    v6->mapDecls.size = 0;
    if ( v21 )
    {
      LOBYTE(v48) = 12;
      idDict::Clear(v21);
      LOBYTE(v48) = 11;
LABEL_123:
      idHashIndex::Free(&v21->argHash);
      v42 = v21->args.list;
      LOBYTE(v48) = 2;
      if ( v42 )
        Memory::Free(v42);
      v21->args.list = 0;
      v21->args.num = 0;
      v21->args.size = 0;
      Memory::Free(v21);
    }
  }
LABEL_128:
  v32 = v6 == 0;
LABEL_129:
  if ( !v32 )
  {
    addonInfo_t::~addonInfo_t(v6);
    Memory::Free(v6);
  }
  LOBYTE(v48) = 1;
  idStr::FreeData(&token2);
  LOBYTE(v48) = 0;
  idStr::FreeData(&token);
  v48 = -1;
  idLexer::~idLexer(&src);
  return 0;
}

// FUNC: private: struct pack_t * __thiscall idFileSystemLocal::LoadZipFile(char const *)
_iobuf *__userpurge idFileSystemLocal::LoadZipFile@<eax>(idFileSystemLocal *this@<ecx>, int a2@<ebp>, char *zipfile)
{
  idFileSystemLocal *v3; // ebx
  _iobuf *result; // eax
  _iobuf *v5; // esi
  void *v6; // ebp
  int number_entry; // edi
  int *v8; // eax
  _DWORD *v9; // esi
  _DWORD *v10; // eax
  pack_t *v11; // esi
  int v12; // edi
  unsigned __int8 *v13; // ecx
  unsigned __int8 v14; // al
  int v15; // ebp
  fileInPack_s *v16; // edi
  idFile_InZip *FileFromZip; // eax
  idFile_InZip *v18; // edi
  int v19; // eax
  char *v20; // ebp
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int hash; // [esp+18h] [ebp-87Ch]
  int hasha; // [esp+18h] [ebp-87Ch]
  int len; // [esp+20h] [ebp-874h]
  idFile_InZip_vtbl *lena; // [esp+20h] [ebp-874h]
  int i; // [esp+24h] [ebp-870h]
  int fs_numHeaderLongs; // [esp+28h] [ebp-86Ch]
  void *uf; // [esp+2Ch] [ebp-868h]
  unz_global_info_s gi; // [esp+30h] [ebp-864h] BYREF
  unz_file_info_s file_info; // [esp+38h] [ebp-85Ch] BYREF
  char filename_inzip[2048]; // [esp+88h] [ebp-80Ch] BYREF
  int v36; // [esp+890h] [ebp-4h]

  v3 = this;
  result = idFileSystemLocal::OpenOSFile(this, zipfile, "rb", 0);
  v5 = result;
  if ( result )
  {
    sys->FSeek(sys, result, 0, 2);
    len = sys->FTell(sys, v5);
    sys->FClose(sys, v5);
    fs_numHeaderLongs = 0;
    v6 = unzOpen(zipfile);
    uf = v6;
    if ( unzGetGlobalInfo(v6, &gi) )
    {
      return 0;
    }
    else
    {
      number_entry = gi.number_entry;
      v8 = (int *)Memory::Allocate(40 * gi.number_entry + 4);
      v36 = 0;
      if ( v8 )
      {
        v9 = v8 + 1;
        *v8 = number_entry;
        `eh vector constructor iterator'(
          v8 + 1,
          0x28u,
          number_entry,
          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        hash = (int)v9;
      }
      else
      {
        hash = 0;
      }
      v36 = -1;
      v10 = Memory::Allocate(0x1048u);
      if ( v10 )
      {
        *v10 = 0;
        v10[2] = 20;
        v10[1] = v10 + 3;
        *((_BYTE *)v10 + 12) = 0;
        v11 = (pack_t *)v10;
      }
      else
      {
        v11 = 0;
      }
      memset(v11->hashTable, 0, sizeof(v11->hashTable));
      idStr::operator=(&v11->pakFilename, zipfile);
      v11->handle = v6;
      v11->numfiles = gi.number_entry;
      v11->buildBuffer = (fileInPack_s *)hash;
      v11->referenced = 0;
      v11->binary = BINARY_UNKNOWN;
      v11->addon = 0;
      v11->addon_search = 0;
      v11->addon_info = 0;
      v11->pureStatus = PURE_UNKNOWN;
      v11->length = len;
      unzGoToFirstFile(v6);
      lena = (idFile_InZip_vtbl *)Mem_ClearedAlloc(4 * gi.number_entry, 0xBu);
      i = 0;
      if ( (int)gi.number_entry > 0 )
      {
        v12 = hash + 4;
        while ( !unzGetCurrentFileInfo(v6, &file_info, filename_inzip, 0x800u, 0, 0, 0, 0) )
        {
          if ( file_info.uncompressed_size )
            *((_DWORD *)&lena->~idFile_InZip + fs_numHeaderLongs++) = LittleLong(file_info.crc);
          hasha = idFileSystemLocal::HashFileName(v3, filename_inzip);
          idStr::operator=((idStr *)(v12 - 4), filename_inzip);
          v13 = *(unsigned __int8 **)v12;
          v14 = **(_BYTE **)v12;
          v15 = 0;
          if ( v14 )
          {
            do
            {
              if ( idStr::lowerCaseCharacter[v14] )
                v14 = idStr::lowerCaseCharacter[v14];
              *v13 = v14;
              ++v15;
              v13 = (unsigned __int8 *)(*(_DWORD *)v12 + v15);
              v14 = *v13;
            }
            while ( *v13 );
          }
          idStr::BackSlashesToSlashes((idStr *)(v12 - 4));
          unzGetCurrentFileInfoPosition(uf, (unsigned int *)(v12 + 28));
          *(_DWORD *)(v12 + 32) = v11->hashTable[hasha];
          v11->hashTable[hasha] = (fileInPack_s *)(v12 - 4);
          unzGoToNextFile(uf);
          v3 = this;
          v12 += 40;
          if ( ++i >= (int)gi.number_entry )
            break;
          v6 = uf;
        }
      }
      v11->addon = 0;
      v16 = v11->hashTable[idFileSystemLocal::HashFileName(v3, "addon.conf")];
      if ( v16 )
      {
        while ( idFileSystemLocal::FilenameCompare(v3, v16->name.data, "addon.conf") )
        {
          v16 = v16->next;
          if ( !v16 )
            goto LABEL_29;
        }
        v11->addon = 1;
        FileFromZip = idFileSystemLocal::ReadFileFromZip(v3, v11, v16, "addon.conf");
        v18 = FileFromZip;
        if ( FileFromZip )
        {
          if ( ((int (__thiscall *)(idFile_InZip *, int))FileFromZip->Length)(FileFromZip, a2) )
          {
            v19 = v18->Length(v18);
            v20 = (char *)Memory::Allocate(v19 + 1);
            lena = v18->__vftable;
            v21 = v18->Length(v18);
            lena->Read(v18, v20, v21);
            v20[v18->Length(v18)] = 0;
            v22 = v18->Length(v18);
            v11->addon_info = idFileSystemLocal::ParseAddonDef(v3, v20, v22);
            Memory::Free(v20);
          }
          v3->CloseFile(v3, v18);
        }
      }
LABEL_29:
      v23 = MD4_BlockChecksum(lena, 4 * fs_numHeaderLongs);
      v11->checksum = v23;
      v11->checksum = LittleLong(v23);
      Mem_Free(lena);
      return (_iobuf *)v11;
    }
  }
  return result;
}

// FUNC: public: virtual int __thiscall idFileSystemLocal::AddZipFile(char const *)
int __thiscall idFileSystemLocal::AddZipFile(idFileSystemLocal *this, const char *path)
{
  const char *value; // esi
  unsigned int v4; // eax
  int v5; // edi
  int v6; // eax
  char *data; // edx
  const char *v8; // ecx
  char v9; // al
  _iobuf *ZipFile; // esi
  _iobuf **v12; // eax
  searchpath_s *i; // ecx
  int cnt; // esi
  idStr fullpath; // [esp+10h] [ebp-2Ch] BYREF
  int v16; // [esp+38h] [ebp-4h]

  value = idFileSystemLocal::fs_savepath.internalVar->value;
  fullpath.len = 0;
  fullpath.alloced = 20;
  fullpath.data = fullpath.baseBuffer;
  fullpath.baseBuffer[0] = 0;
  if ( value )
  {
    v4 = (unsigned int)&value[strlen(value) + 1];
    v5 = v4 - (_DWORD)(value + 1);
    v6 = v4 - (_DWORD)value;
    if ( v6 > 20 )
      idStr::ReAllocate(&fullpath, v6, 1);
    data = fullpath.data;
    v8 = value;
    do
    {
      v9 = *v8;
      *data++ = *v8++;
    }
    while ( v9 );
    fullpath.len = v5;
  }
  v16 = 0;
  idStr::AppendPath(&fullpath, path);
  ZipFile = idFileSystemLocal::LoadZipFile(this, (int)this, fullpath.data);
  if ( ZipFile )
  {
    v12 = (_iobuf **)Memory::Allocate(0xCu);
    v12[1] = 0;
    *v12 = ZipFile;
    v12[2] = 0;
    for ( i = this->searchPaths; i->next; i = i->next )
      ;
    i->next = (searchpath_s *)v12;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Appended pk4 %s with checksum 0x%x\n",
      ZipFile->_cnt,
      ZipFile[1]._cnt);
    cnt = ZipFile[1]._cnt;
    v16 = -1;
    idStr::FreeData(&fullpath);
    return cnt;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "AddZipFile %s failed\n",
      path);
    v16 = -1;
    idStr::FreeData(&fullpath);
    return 0;
  }
}

// FUNC: public: virtual bool __thiscall idFileSystemLocal::AddExplicitPak(char const *)
char __userpurge idFileSystemLocal::AddExplicitPak@<al>(idFileSystemLocal *this@<ecx>, int a2@<ebp>, char *path)
{
  searchpath_s *searchPaths; // esi
  _iobuf *ZipFile; // esi
  searchpath_s *v7; // eax
  searchpath_s *v8; // ecx

  searchPaths = this->searchPaths;
  if ( searchPaths )
  {
    while ( idStr::Cmp(searchPaths->pack->pakFilename.data, path) )
    {
      searchPaths = searchPaths->next;
      if ( !searchPaths )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    ZipFile = idFileSystemLocal::LoadZipFile(this, a2, path);
    if ( !ZipFile )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "AddZipFile %s failed\n",
        path);
      return 0;
    }
    v7 = (searchpath_s *)Memory::Allocate(0xCu);
    v7->dir = 0;
    v7->pack = (pack_t *)ZipFile;
    v7->next = 0;
    v8 = this->searchPaths;
    if ( v8 )
    {
      for ( ; v8->next; v8 = v8->next )
        ;
      v8->next = v7;
    }
    else
    {
      this->searchPaths = v7;
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Appended pk4 %s with checksum 0x%x\n",
      ZipFile->_cnt,
      ZipFile[1]._cnt);
  }
  return 1;
}

// FUNC: private: int __thiscall idFileSystemLocal::GetFileList(char const *,class idList<class idStr> const &,class idList<class idStr> &,class idHashIndex &,bool,char const *)
int __thiscall idFileSystemLocal::GetFileList(
        idFileSystemLocal *this,
        char *relativePath,
        const idList<idStr> *extensions,
        idList<idStr> *list,
        idHashIndex *hashIndex,
        bool fullRelativePath,
        const char *gamedir)
{
  idFileSystemLocal *v7; // ebx
  bool v8; // zf
  searchpath_s *searchPaths; // ebp
  directory_t *dir; // esi
  directory_t *v12; // eax
  char *data; // ecx
  idFileSystemLocal_vtbl *v14; // edx
  char *v15; // eax
  bool v16; // cc
  char *v17; // eax
  int v18; // eax
  char v19; // cl
  int v20; // esi
  int v21; // edi
  int len; // ebx
  idStr *v23; // ebp
  int v24; // eax
  char v25; // cl
  int v26; // esi
  int v27; // edi
  int v28; // ebx
  idStr *v29; // ebp
  int v30; // ebx
  int v31; // esi
  int v32; // eax
  char v33; // cl
  char *v34; // edx
  idStr *v35; // esi
  int v36; // edi
  int k; // eax
  char v38; // cl
  char *v39; // edx
  char *v40; // edi
  int num; // edx
  int v42; // eax
  pack_t **v43; // ecx
  idStr *p_pakFilename; // ecx
  int v45; // edi
  int v46; // eax
  char v47; // cl
  char *v48; // edx
  fileInPack_s *buildBuffer; // eax
  int v50; // ebx
  int v51; // edi
  int v52; // ebp
  const char *v53; // esi
  int m; // eax
  const idList<idStr> *v55; // eax
  int v56; // ebx
  int v57; // edi
  int v58; // esi
  int v59; // eax
  char v60; // cl
  char *v61; // edx
  int v62; // esi
  char v63; // cl
  int n; // eax
  char *v65; // edi
  int v66; // esi
  char *v67; // [esp-10h] [ebp-118h]
  int j; // [esp+Ch] [ebp-FCh]
  int ja; // [esp+Ch] [ebp-FCh]
  int jb; // [esp+Ch] [ebp-FCh]
  int jc; // [esp+Ch] [ebp-FCh]
  int v73; // [esp+14h] [ebp-F4h]
  int v74; // [esp+14h] [ebp-F4h]
  int v75; // [esp+14h] [ebp-F4h]
  char *text; // [esp+18h] [ebp-F0h]
  char *texta; // [esp+18h] [ebp-F0h]
  idList<idStr> sysFiles; // [esp+1Ch] [ebp-ECh] BYREF
  int pathLength; // [esp+2Ch] [ebp-DCh]
  int i; // [esp+30h] [ebp-D8h]
  searchpath_s *search; // [esp+34h] [ebp-D4h]
  idStr work; // [esp+38h] [ebp-D0h] BYREF
  pack_t *pak; // [esp+58h] [ebp-B0h]
  idStr levelPakName; // [esp+5Ch] [ebp-ACh] BYREF
  idStr pakName; // [esp+7Ch] [ebp-8Ch] BYREF
  idStr v86; // [esp+9Ch] [ebp-6Ch] BYREF
  idStr v87; // [esp+BCh] [ebp-4Ch] BYREF
  idStr netpath; // [esp+DCh] [ebp-2Ch] BYREF
  int v89; // [esp+104h] [ebp-4h]

  v7 = this;
  work.len = 0;
  work.alloced = 20;
  work.data = work.baseBuffer;
  work.baseBuffer[0] = 0;
  v8 = this->searchPaths == 0;
  v89 = 0;
  if ( v8 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  if ( !extensions->num || !relativePath )
  {
    v89 = -1;
    idStr::FreeData(&work);
    return 0;
  }
  pathLength = strlen(relativePath);
  if ( pathLength )
    ++pathLength;
  searchPaths = v7->searchPaths;
  for ( search = searchPaths; searchPaths; search = searchPaths )
  {
    dir = searchPaths->dir;
    if ( dir )
    {
      if ( gamedir )
      {
        pak = (pack_t *)strlen(gamedir);
        if ( pak )
        {
          if ( idStr::Cmp(dir->gamedir.data, gamedir) )
            goto LABEL_116;
        }
      }
      sysFiles.granularity = 16;
      sysFiles.list = 0;
      sysFiles.num = 0;
      sysFiles.size = 0;
      netpath.len = 0;
      netpath.alloced = 20;
      netpath.data = netpath.baseBuffer;
      netpath.baseBuffer[0] = 0;
      v12 = searchPaths->dir;
      data = v12->gamedir.data;
      v14 = v7->__vftable;
      v67 = v12->path.data;
      LOBYTE(v89) = 2;
      v15 = (char *)v14->BuildOSPath(v7, v67, data, relativePath);
      idStr::operator=(&netpath, v15);
      v16 = extensions->num <= 0;
      i = 0;
      if ( !v16 )
      {
        text = 0;
        do
        {
          idFileSystemLocal::ListOSFiles(
            this,
            netpath.data,
            *(char **)&text[(unsigned int)extensions->list + 4],
            &sysFiles);
          v17 = *(char **)&text[(unsigned int)extensions->list + 4];
          if ( *v17 == 47 && !v17[1] )
          {
            v86.alloced = 20;
            v86.data = v86.baseBuffer;
            v86.baseBuffer[0] = 0;
            v18 = 0;
            do
            {
              v19 = PathName[v18];
              v86.baseBuffer[v18++] = v19;
            }
            while ( v19 );
            v86.len = 1;
            v20 = 0;
            LOBYTE(v89) = 3;
            if ( sysFiles.num > 0 )
            {
              v21 = 0;
              while ( idStr::Cmp(sysFiles.list[v21].data, v86.data) )
              {
                ++v20;
                ++v21;
                if ( v20 >= sysFiles.num )
                  goto LABEL_31;
              }
              if ( v20 >= 0 && v20 < sysFiles.num )
              {
                --sysFiles.num;
                j = v20;
                if ( v20 < sysFiles.num )
                {
                  v73 = v20;
                  do
                  {
                    len = sysFiles.list[v73 + 1].len;
                    v23 = &sysFiles.list[v73];
                    if ( len + 1 > sysFiles.list[v73].alloced )
                      idStr::ReAllocate(&sysFiles.list[v73], len + 1, 0);
                    ++v73;
                    qmemcpy(v23->data, v23[1].data, len);
                    v23->data[len] = 0;
                    v23->len = len;
                    ++j;
                  }
                  while ( j < sysFiles.num );
                }
              }
            }
LABEL_31:
            LOBYTE(v89) = 2;
            idStr::FreeData(&v86);
            v87.alloced = 20;
            v87.data = v87.baseBuffer;
            v87.baseBuffer[0] = 0;
            v24 = 0;
            do
            {
              v25 = asc_102A1C90[v24];
              v87.baseBuffer[v24++] = v25;
            }
            while ( v25 );
            v87.len = 2;
            v26 = 0;
            LOBYTE(v89) = 4;
            if ( sysFiles.num > 0 )
            {
              v27 = 0;
              while ( idStr::Cmp(sysFiles.list[v27].data, v87.data) )
              {
                ++v26;
                ++v27;
                if ( v26 >= sysFiles.num )
                  goto LABEL_45;
              }
              if ( v26 >= 0 && v26 < sysFiles.num )
              {
                --sysFiles.num;
                ja = v26;
                if ( v26 < sysFiles.num )
                {
                  v74 = v26;
                  do
                  {
                    v28 = sysFiles.list[v74 + 1].len;
                    v29 = &sysFiles.list[v74];
                    if ( v28 + 1 > sysFiles.list[v74].alloced )
                      idStr::ReAllocate(&sysFiles.list[v74], v28 + 1, 0);
                    ++v74;
                    qmemcpy(v29->data, v29[1].data, v28);
                    v29->data[v28] = 0;
                    v29->len = v28;
                    ++ja;
                  }
                  while ( ja < sysFiles.num );
                }
              }
            }
LABEL_45:
            LOBYTE(v89) = 2;
            idStr::FreeData(&v87);
          }
          jb = 0;
          if ( sysFiles.num > 0 )
          {
            v30 = 0;
            do
            {
              if ( fullRelativePath )
              {
                idStr::operator=(&work, relativePath);
                v31 = work.len + 1;
                if ( work.len + 2 > work.alloced )
                  idStr::ReAllocate(&work, work.len + 2, 1);
                v32 = 0;
                v33 = 47;
                do
                {
                  v34 = &work.data[v32++];
                  v34[work.len] = v33;
                  v33 = b[v32];
                }
                while ( v33 );
                work.len = v31;
                work.data[v31] = 0;
                v35 = &sysFiles.list[v30];
                v36 = sysFiles.list[v30].len + work.len;
                if ( v36 + 1 > work.alloced )
                  idStr::ReAllocate(&work, v36 + 1, 1);
                for ( k = 0; k < v35->len; v39[work.len] = v38 )
                {
                  v38 = v35->data[k];
                  v39 = &work.data[k++];
                }
                work.len = v36;
                work.data[v36] = 0;
                idFileSystemLocal::AddUnique(this, work.data, list, hashIndex);
              }
              else
              {
                idFileSystemLocal::AddUnique(this, sysFiles.list[v30].data, list, hashIndex);
              }
              ++v30;
              ++jb;
            }
            while ( jb < sysFiles.num );
          }
          text += 32;
          v16 = ++i < extensions->num;
        }
        while ( v16 );
      }
      LOBYTE(v89) = 1;
      idStr::FreeData(&netpath);
      LOBYTE(v89) = 0;
      if ( sysFiles.list )
      {
        v40 = &sysFiles.list[-1].baseBuffer[16];
        `eh vector destructor iterator'(
          sysFiles.list,
          0x20u,
          *(_DWORD *)&sysFiles.list[-1].baseBuffer[16],
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        Memory::Free(v40);
      }
      sysFiles.list = 0;
      sysFiles.num = 0;
      sysFiles.size = 0;
      goto LABEL_115;
    }
    if ( !searchPaths->pack )
      goto LABEL_116;
    if ( v7->serverPaks.num )
    {
      idFileSystemLocal::GetPackStatus(v7, searchPaths->pack);
      if ( searchPaths->pack->pureStatus != PURE_NEVER )
      {
        num = v7->serverPaks.num;
        v42 = 0;
        if ( num <= 0 )
          goto LABEL_116;
        v43 = v7->serverPaks.list;
        while ( *v43 != searchPaths->pack )
        {
          ++v42;
          ++v43;
          if ( v42 >= num )
            goto LABEL_116;
        }
        if ( v42 < 0 || !&v7->serverPaks.list[v42] )
          goto LABEL_116;
      }
    }
    if ( cvarSystem->GetCVarBool(cvarSystem, "fs_mapPaks") )
    {
      levelPakName.len = 0;
      levelPakName.alloced = 20;
      levelPakName.data = levelPakName.baseBuffer;
      levelPakName.baseBuffer[0] = 0;
      pakName.len = 0;
      pakName.alloced = 20;
      pakName.data = pakName.baseBuffer;
      pakName.baseBuffer[0] = 0;
      p_pakFilename = &searchPaths->pack->pakFilename;
      LOBYTE(v89) = 6;
      idStr::ExtractFileName(p_pakFilename, &pakName);
      idStr::ExtractFileName(&v7->currentAssetLogUnfiltered, &levelPakName);
      idStr::StripFileExtension(&levelPakName);
      v45 = levelPakName.len + 4;
      if ( levelPakName.len + 5 > levelPakName.alloced )
        idStr::ReAllocate(&levelPakName, levelPakName.len + 5, 1);
      v46 = 0;
      v47 = 46;
      do
      {
        v48 = &levelPakName.data[v46++];
        v48[levelPakName.len] = v47;
        v47 = aPk4[v46];
      }
      while ( v47 );
      levelPakName.len = v45;
      levelPakName.data[v45] = 0;
      if ( idFileSystemLocal::FilenameCompare(this, levelPakName.data, pakName.data)
        && (idStr::FindText(v7->currentAssetLogUnfiltered.data, "/mp/", 1, 0, v7->currentAssetLogUnfiltered.len) == -1
         || idStr::Icmp(pakName.data, "default.pk4")) )
      {
        LOBYTE(v89) = 5;
        idStr::FreeData(&pakName);
        LOBYTE(v89) = 0;
        idStr::FreeData(&levelPakName);
LABEL_115:
        v7 = this;
        searchPaths = search;
        goto LABEL_116;
      }
      LOBYTE(v89) = 5;
      idStr::FreeData(&pakName);
      LOBYTE(v89) = 0;
      idStr::FreeData(&levelPakName);
      v7 = this;
      searchPaths = search;
    }
    v16 = searchPaths->pack->numfiles <= 0;
    buildBuffer = searchPaths->pack->buildBuffer;
    pak = searchPaths->pack;
    i = 0;
    if ( !v16 )
    {
      v50 = pathLength - 1;
      v75 = pathLength - 1;
      jc = (int)buildBuffer;
      while ( 1 )
      {
        v51 = pathLength;
        v52 = buildBuffer->name.len;
        v53 = buildBuffer->name.data;
        if ( (!pathLength || !idStr::Icmpn(v53, relativePath, v50)) && v53[v50] == 47 )
        {
          texta = (char *)&v53[v51];
          if ( v53[v51] )
          {
            for ( m = v51; v53[m + 1]; ++m )
            {
              if ( v53[m] == 47 )
                break;
            }
            if ( !v53[m + 1] )
            {
              v55 = extensions;
              v56 = 0;
              if ( extensions->num > 0 )
              {
                v57 = 0;
                do
                {
                  if ( v52 >= v55->list[v57].len )
                  {
                    v8 = idStr::Icmp(extensions->list[v57].data, &v53[v52 - extensions->list[v57].len]) == 0;
                    v55 = extensions;
                    if ( v8 )
                      break;
                  }
                  ++v56;
                  ++v57;
                }
                while ( v56 < v55->num );
              }
              if ( v56 < v55->num )
              {
                if ( fullRelativePath )
                {
                  idStr::operator=(&work, relativePath);
                  v58 = work.len + 1;
                  if ( work.len + 2 > work.alloced )
                    idStr::ReAllocate(&work, work.len + 2, 1);
                  v59 = 0;
                  v60 = 47;
                  do
                  {
                    v61 = &work.data[v59++];
                    v61[work.len] = v60;
                    v60 = b[v59];
                  }
                  while ( v60 );
                  work.len = v58;
                  work.data[v58] = 0;
                  if ( texta )
                  {
                    v62 = strlen(texta) + work.len;
                    if ( v62 + 1 > work.alloced )
                      idStr::ReAllocate(&work, v62 + 1, 1);
                    v63 = *texta;
                    for ( n = 0; v63; v63 = texta[n] )
                    {
                      v65 = &work.data[n++];
                      v65[work.len] = v63;
                    }
                    work.len = v62;
                    work.data[v62] = 0;
                  }
                  idStr::StripTrailing(&work, 47);
                  idFileSystemLocal::AddUnique(this, work.data, list, hashIndex);
                }
                else
                {
                  idStr::operator=(&work, texta);
                  idStr::StripTrailing(&work, 47);
                  idFileSystemLocal::AddUnique(this, work.data, list, hashIndex);
                }
              }
            }
          }
        }
        buildBuffer = (fileInPack_s *)(jc + 40);
        v16 = ++i < pak->numfiles;
        jc += 40;
        if ( !v16 )
          break;
        v50 = v75;
      }
      goto LABEL_115;
    }
LABEL_116:
    searchPaths = searchPaths->next;
  }
  v66 = list->num;
  v89 = -1;
  idStr::FreeData(&work);
  return v66;
}

// FUNC: private: int __thiscall idFileSystemLocal::GetFileListTree(char const *,class idList<class idStr> const &,class idList<class idStr> &,class idHashIndex &,char const *)
int __thiscall idFileSystemLocal::GetFileListTree(
        idFileSystemLocal *this,
        char *relativePath,
        const idList<idStr> *extensions,
        idList<idStr> *list,
        idHashIndex *hashIndex,
        const char *gamedir)
{
  int v6; // eax
  char v7; // cl
  _DWORD *v8; // eax
  idStr *v9; // ebp
  int len; // ebx
  bool v11; // cc
  char **p_data; // esi
  int num; // edi
  char *v15; // esi
  int v17; // [esp-8h] [ebp-84h]
  idList<idStr> slash; // [esp+14h] [ebp-68h] BYREF
  idList<idStr> folders; // [esp+24h] [ebp-58h] BYREF
  idHashIndex folderHashIndex; // [esp+34h] [ebp-48h] BYREF
  idStr v22; // [esp+50h] [ebp-2Ch] BYREF
  int v23; // [esp+78h] [ebp-4h]
  const char *gamedira; // [esp+90h] [ebp+14h]

  slash.granularity = 16;
  slash.list = 0;
  slash.num = 0;
  slash.size = 0;
  v23 = 1;
  folders.granularity = 128;
  folders.list = 0;
  folders.num = 0;
  folders.size = 0;
  idHashIndex::Init(&folderHashIndex, 1024, 128);
  v22.data = v22.baseBuffer;
  v22.alloced = 20;
  v22.baseBuffer[0] = 0;
  v6 = 0;
  do
  {
    v7 = b[v6];
    v22.baseBuffer[v6++] = v7;
  }
  while ( v7 );
  v22.len = 1;
  LOBYTE(v23) = 3;
  slash.size = 16;
  v8 = Memory::Allocate(0x204u);
  LOBYTE(v23) = 4;
  if ( v8 )
  {
    v9 = (idStr *)(v8 + 1);
    *v8 = 16;
    `eh vector constructor iterator'(
      v8 + 1,
      0x20u,
      16,
      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  }
  else
  {
    v9 = 0;
  }
  len = v22.len;
  v11 = v22.len + 1 <= v9->alloced;
  LOBYTE(v23) = 3;
  slash.list = v9;
  if ( !v11 )
    idStr::ReAllocate(v9, v22.len + 1, 0);
  qmemcpy(v9->data, v22.data, len);
  v9->data[len] = 0;
  v9->len = len;
  slash.num = 1;
  LOBYTE(v23) = 2;
  idStr::FreeData(&v22);
  idFileSystemLocal::GetFileList(this, relativePath, &slash, &folders, &folderHashIndex, 1, gamedir);
  if ( folders.num > 0 )
  {
    p_data = &folders.list->data;
    gamedira = (const char *)folders.num;
    do
    {
      if ( **p_data != 46 && idStr::Icmp(*p_data, relativePath) )
        idFileSystemLocal::GetFileListTree(this, *p_data, extensions, list, hashIndex, gamedir);
      p_data += 8;
      --gamedira;
    }
    while ( gamedira );
  }
  idFileSystemLocal::GetFileList(this, relativePath, extensions, list, hashIndex, 1, gamedir);
  num = list->num;
  LOBYTE(v23) = 1;
  idHashIndex::Free(&folderHashIndex);
  LOBYTE(v23) = 0;
  if ( folders.list )
  {
    v15 = &folders.list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      folders.list,
      0x20u,
      *(_DWORD *)&folders.list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v15);
  }
  v17 = *(_DWORD *)&v9[-1].baseBuffer[16];
  v23 = -1;
  `eh vector destructor iterator'(
    v9,
    0x20u,
    v17,
    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  Memory::Free(&v9[-1].baseBuffer[16]);
  return num;
}

// FUNC: public: virtual class idFileList * __thiscall idFileSystemLocal::ListFilesTree(char const *,char const *,bool,char const *)
idFileList *__thiscall idFileSystemLocal::ListFilesTree(
        idFileSystemLocal *this,
        char *relativePath,
        const char *extension,
        bool sort,
        const char *gamedir)
{
  _DWORD *v5; // edi
  idStr *v6; // eax
  char *v7; // esi
  idList<idStr> *v8; // ebp
  int num; // eax
  int v10; // ebx
  int *v11; // eax
  _DWORD *v12; // edi
  _DWORD *v13; // eax
  unsigned int v14; // ecx
  idStr *v15; // ebx
  unsigned int v16; // esi
  bool v17; // cc
  int v18; // eax
  int v19; // ecx
  int v20; // ebx
  idFileSystemLocal *v21; // esi
  idFileSystemLocal *v22; // ecx
  int *v23; // eax
  int v24; // esi
  int *p_d3xp; // esi
  unsigned int *v26; // edi
  int *v27; // eax
  idFileSystemLocal *v28; // ebx
  idFileSystemLocal *v29; // eax
  const char *v30; // edi
  searchpath_s **p_searchPaths; // ebx
  unsigned int v32; // esi
  int v33; // eax
  searchpath_s **v34; // ebx
  int v35; // esi
  unsigned int v36; // edi
  int v37; // eax
  char *v38; // esi
  char *v39; // esi
  _DWORD *i; // [esp+Ch] [ebp-70h]
  idStr *v42; // [esp+10h] [ebp-6Ch]
  unsigned int v43; // [esp+14h] [ebp-68h]
  int v44; // [esp+18h] [ebp-64h]
  char *v45; // [esp+1Ch] [ebp-60h]
  idFileSystemLocal *v47; // [esp+20h] [ebp-5Ch]
  int v48; // [esp+24h] [ebp-58h]
  int v49; // [esp+28h] [ebp-54h]
  int alloced; // [esp+2Ch] [ebp-50h]
  idFileSystemLocal *v51; // [esp+30h] [ebp-4Ch]
  _DWORD *v52; // [esp+40h] [ebp-3Ch]
  idList<idStr> extensionList; // [esp+44h] [ebp-38h] BYREF
  idHashIndex hashIndex; // [esp+54h] [ebp-28h] BYREF
  int v55; // [esp+78h] [ebp-4h]
  const char *relativePatha; // [esp+80h] [ebp+4h]
  const char *relativePathb; // [esp+80h] [ebp+4h]
  const char *extensiona; // [esp+84h] [ebp+8h]
  unsigned int *sorta; // [esp+88h] [ebp+Ch]
  int sortb; // [esp+88h] [ebp+Ch]
  const char *gamedira; // [esp+8Ch] [ebp+10h]

  idHashIndex::Init(&hashIndex, 4096, 4096);
  v5 = 0;
  v55 = 1;
  extensionList.granularity = 16;
  extensionList.list = 0;
  extensionList.num = 0;
  extensionList.size = 0;
  v6 = (idStr *)Memory::Allocate(0x30u);
  if ( v6 )
  {
    v6->len = 0;
    v6->alloced = 20;
    v6->data = v6->baseBuffer;
    v6->baseBuffer[0] = 0;
    v6[1].alloced = 16;
    *(_DWORD *)v6[1].baseBuffer = 0;
    v6[1].len = 0;
    v6[1].data = 0;
    v42 = v6;
  }
  else
  {
    v42 = 0;
  }
  LOBYTE(v55) = 1;
  idStr::operator=(v42, relativePath);
  v7 = *(char **)v42[1].baseBuffer;
  v8 = (idList<idStr> *)&v42[1];
  v42[1].alloced = 4096;
  v45 = v7;
  if ( v7 )
  {
    num = v8->num;
    v10 = v8->num + 4095 - (v8->num + 4095) % 4096;
    if ( (char *)v10 != v42[1].data )
    {
      if ( v10 > 0 )
      {
        v42[1].data = (char *)v10;
        if ( v10 < num )
          v8->num = v10;
        v11 = (int *)Memory::Allocate(32 * v10 + 4);
        LOBYTE(v55) = 4;
        if ( v11 )
        {
          v12 = v11 + 1;
          *v11 = v10;
          `eh vector constructor iterator'(
            v11 + 1,
            0x20u,
            v10,
            (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          v13 = v12;
          v5 = 0;
        }
        else
        {
          v13 = 0;
        }
        v17 = v8->num <= 0;
        LOBYTE(v55) = 1;
        *(_DWORD *)v42[1].baseBuffer = v13;
        v44 = 0;
        if ( !v17 )
        {
          for ( i = 0; ; v5 = i )
          {
            v14 = *(_DWORD *)&v7[(_DWORD)v5];
            v15 = (idStr *)((char *)v5 + *(_DWORD *)v42[1].baseBuffer);
            v43 = v14;
            if ( (signed int)(v14 + 1) > v15->alloced )
            {
              idStr::ReAllocate(v15, v14 + 1, 0);
              v14 = v43;
            }
            i += 8;
            qmemcpy(v15->data, *(const void **)&v7[(_DWORD)v5 + 4], v14);
            v7 = v45;
            v15->data[v43] = 0;
            v15->len = v43;
            if ( ++v44 >= v8->num )
              break;
          }
          v5 = 0;
        }
        if ( v7 )
        {
          `eh vector destructor iterator'(
            v7,
            0x20u,
            *((_DWORD *)v7 - 1),
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(v7 - 4);
        }
      }
      else
      {
        `eh vector destructor iterator'(
          v7,
          0x20u,
          *((_DWORD *)v7 - 1),
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        Memory::Free(v7 - 4);
        *(_DWORD *)v42[1].baseBuffer = 0;
        v8->num = 0;
        v42[1].data = 0;
      }
    }
  }
  idFileSystemLocal::GetExtensionList(this, extension, &extensionList);
  idFileSystemLocal::GetFileListTree(this, relativePath, &extensionList, v8, &hashIndex, gamedir);
  if ( sort )
  {
    v16 = v8->num;
    v17 = v8->num <= 0;
    if ( v8->num )
    {
      LOBYTE(v55) = 6;
      if ( v17 )
      {
        v52 = 0;
      }
      else
      {
        v52 = Memory::Allocate(4 * v16);
        v5 = v52;
      }
      v18 = 0;
      if ( v8->num > 0 )
      {
        v19 = 0;
        do
        {
          v5[v18++] = v19 + *(_DWORD *)v42[1].baseBuffer;
          v19 += 32;
        }
        while ( v18 < v8->num );
      }
      if ( v5 )
        qsort(v5, v16, 4u, (int (__cdecl *)(const void *, const void *))idListSortComparePaths<idStr *>);
      v20 = v8->num;
      v21 = 0;
      if ( v8->num > 0 )
      {
        v49 = v8->num;
        v23 = (int *)Memory::Allocate(32 * v20 + 4);
        LOBYTE(v55) = 7;
        if ( v23 )
        {
          v21 = (idFileSystemLocal *)(v23 + 1);
          *v23 = v20;
          `eh vector constructor iterator'(
            v23 + 1,
            0x20u,
            v20,
            (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        }
        LOBYTE(v55) = 6;
        v51 = v21;
        v22 = v21;
      }
      else
      {
        v22 = 0;
        v51 = 0;
        v49 = 0;
      }
      v48 = v20;
      alloced = v42[1].alloced;
      if ( v22 )
      {
        v24 = v42[1].alloced + v20 - 1 - (v42[1].alloced + v20 - 1) % alloced;
        if ( v24 != v49 )
        {
          if ( v24 > 0 )
          {
            v26 = (unsigned int *)v22;
            v47 = v22;
            v49 = v42[1].alloced + v20 - 1 - (v42[1].alloced + v20 - 1) % alloced;
            if ( v24 < v20 )
              v48 = v42[1].alloced + v20 - 1 - (v42[1].alloced + v20 - 1) % alloced;
            v27 = (int *)Memory::Allocate(32 * v24 + 4);
            LOBYTE(v55) = 8;
            if ( v27 )
            {
              v28 = (idFileSystemLocal *)(v27 + 1);
              *v27 = v24;
              `eh vector constructor iterator'(
                v27 + 1,
                0x20u,
                v24,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              v29 = v28;
            }
            else
            {
              v29 = 0;
            }
            LOBYTE(v55) = 6;
            v51 = v29;
            if ( v48 > 0 )
            {
              sorta = v26;
              v30 = (const char *)((char *)v26 - (char *)v29);
              p_searchPaths = &v29->searchPaths;
              extensiona = v30;
              relativePatha = (const char *)v48;
              while ( 1 )
              {
                v32 = *sorta;
                v33 = *sorta + 1;
                gamedira = (const char *)*sorta;
                if ( v33 > (int)p_searchPaths[1] )
                  idStr::ReAllocate((idStr *)(p_searchPaths - 1), v33, 0);
                sorta += 8;
                qmemcpy(*p_searchPaths, *(const void **)((char *)p_searchPaths + (_DWORD)v30), v32);
                *((_BYTE *)&(*p_searchPaths)->pack + (_DWORD)gamedira) = 0;
                *(p_searchPaths - 1) = (searchpath_s *)gamedira;
                p_searchPaths += 8;
                if ( !--relativePatha )
                  break;
                v30 = extensiona;
              }
              v26 = (unsigned int *)v47;
            }
            `eh vector destructor iterator'(
              v26,
              0x20u,
              *(v26 - 1),
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(v26 - 1);
          }
          else
          {
            p_d3xp = &v22[-1].d3xp;
            `eh vector destructor iterator'(
              v22,
              0x20u,
              v22[-1].d3xp,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(p_d3xp);
            v51 = 0;
            v48 = 0;
            v49 = 0;
          }
          v22 = v51;
          v5 = v52;
        }
      }
      sortb = 0;
      if ( v48 > 0 )
      {
        v34 = &v22->searchPaths;
        do
        {
          v35 = v5[sortb];
          v36 = *(_DWORD *)v35;
          v37 = *(_DWORD *)v35 + 1;
          relativePathb = *(const char **)v35;
          if ( v37 > (int)v34[1] )
            idStr::ReAllocate((idStr *)(v34 - 1), v37, 0);
          qmemcpy(*v34, *(const void **)(v35 + 4), v36);
          v5 = v52;
          *((_BYTE *)&(*v34)->pack + (_DWORD)relativePathb) = 0;
          *(v34 - 1) = (searchpath_s *)relativePathb;
          v34 += 8;
          ++sortb;
        }
        while ( sortb < v48 );
        v22 = v51;
      }
      v8->num = v48;
      v42[1].data = (char *)v49;
      v42[1].alloced = alloced;
      v38 = *(char **)v42[1].baseBuffer;
      *(_DWORD *)v42[1].baseBuffer = v22;
      LOBYTE(v55) = 5;
      if ( v5 )
        Memory::Free(v5);
      LOBYTE(v55) = 1;
      if ( v38 )
      {
        `eh vector destructor iterator'(
          v38,
          0x20u,
          *((_DWORD *)v38 - 1),
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        Memory::Free(v38 - 4);
      }
    }
  }
  LOBYTE(v55) = 0;
  if ( extensionList.list )
  {
    v39 = &extensionList.list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      extensionList.list,
      0x20u,
      *(_DWORD *)&extensionList.list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v39);
  }
  extensionList.list = 0;
  extensionList.num = 0;
  extensionList.size = 0;
  v55 = -1;
  idHashIndex::Free(&hashIndex);
  return (idFileList *)v42;
}

// FUNC: private: void __thiscall idFileSystemLocal::AddGameDirectory(char const *,char const *)
void __thiscall idFileSystemLocal::AddGameDirectory(idFileSystemLocal *this, char *path, char *dir)
{
  idFileSystemLocal *v3; // ebx
  searchpath_s *searchPaths; // esi
  directory_t *v5; // eax
  char *v6; // edi
  searchpath_s *v7; // esi
  idStr *v8; // eax
  const char *v9; // ebp
  idFileSystemLocal_vtbl *v10; // eax
  char *v11; // eax
  int num; // ecx
  int v13; // ebp
  _DWORD *v14; // edi
  _DWORD *v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // esi
  idStr *v19; // ebp
  int v20; // ebp
  int *v21; // eax
  _DWORD *v22; // esi
  int v23; // eax
  int v24; // esi
  idStr *v25; // edi
  int *v26; // eax
  _DWORD *v27; // ebp
  int v28; // eax
  char *v29; // edi
  int v30; // ebp
  unsigned int v31; // ebx
  int v32; // eax
  char **p_data; // ebp
  int v34; // esi
  unsigned int v35; // ebx
  int v36; // eax
  idStr *list; // esi
  int v38; // eax
  int size; // eax
  int v40; // eax
  char *v41; // eax
  _iobuf *ZipFile; // esi
  _iobuf **v43; // eax
  char *v44; // edi
  int v45; // [esp+Ch] [ebp-70h]
  unsigned int *v46; // [esp+Ch] [ebp-70h]
  int v47; // [esp+Ch] [ebp-70h]
  int v48; // [esp+10h] [ebp-6Ch]
  char *v50; // [esp+18h] [ebp-64h]
  idStr *v51; // [esp+1Ch] [ebp-60h]
  idList<idStr> pakfiles; // [esp+20h] [ebp-5Ch] BYREF
  int v53; // [esp+30h] [ebp-4Ch]
  int v54; // [esp+34h] [ebp-48h]
  int granularity; // [esp+38h] [ebp-44h]
  idStr *v56; // [esp+3Ch] [ebp-40h]
  int v57; // [esp+40h] [ebp-3Ch]
  int v58; // [esp+44h] [ebp-38h]
  int v59; // [esp+48h] [ebp-34h]
  _DWORD *v60; // [esp+4Ch] [ebp-30h]
  idStr pakfile; // [esp+50h] [ebp-2Ch] BYREF
  int v62; // [esp+78h] [ebp-4h]
  const char *patha; // [esp+80h] [ebp+4h]
  int i; // [esp+84h] [ebp+8h]

  v3 = this;
  pakfile.len = 0;
  pakfile.alloced = 20;
  pakfile.data = pakfile.baseBuffer;
  pakfile.baseBuffer[0] = 0;
  v62 = 0;
  pakfiles.granularity = 16;
  pakfiles.list = 0;
  pakfiles.num = 0;
  pakfiles.size = 0;
  searchPaths = this->searchPaths;
  LOBYTE(v62) = 1;
  if ( searchPaths )
  {
    while ( 1 )
    {
      v5 = searchPaths->dir;
      if ( v5 )
      {
        if ( !idStr::Cmp(v5->path.data, path) && !idStr::Cmp(searchPaths->dir->gamedir.data, dir) )
          break;
      }
      searchPaths = searchPaths->next;
      if ( !searchPaths )
        goto LABEL_6;
    }
    pakfiles.list = 0;
    pakfiles.num = 0;
    pakfiles.size = 0;
    v62 = -1;
    idStr::FreeData(&pakfile);
  }
  else
  {
LABEL_6:
    v6 = dir;
    idStr::operator=(&v3->gameFolder, dir);
    v7 = (searchpath_s *)Memory::Allocate(0xCu);
    v8 = (idStr *)Memory::Allocate(0x40u);
    if ( v8 )
    {
      v8->len = 0;
      v8->data = v8->baseBuffer;
      v8->alloced = 20;
      v8->baseBuffer[0] = 0;
      v8[1].len = 0;
      v8[1].alloced = 20;
      v8[1].data = v8[1].baseBuffer;
      v8[1].baseBuffer[0] = 0;
    }
    else
    {
      v8 = 0;
    }
    v7->pack = 0;
    v9 = path;
    v7->dir = (directory_t *)v8;
    idStr::operator=(v8, path);
    idStr::operator=(&v7->dir->gamedir, dir);
    v7->next = v3->searchPaths;
    v10 = v3->__vftable;
    v3->searchPaths = v7;
    v11 = (char *)v10->BuildOSPath(v3, path, dir, &entityFilter);
    idStr::operator=(&pakfile, v11);
    idFileSystemLocal::ListOSFiles(v3, pakfile.data, ".pk4", &pakfiles);
    num = pakfiles.num;
    if ( pakfiles.num )
    {
      granularity = 16;
      v56 = 0;
      v53 = 0;
      v54 = 0;
      v59 = 16;
      v60 = 0;
      v57 = 0;
      LOBYTE(v62) = 3;
      v13 = pakfiles.num;
      if ( pakfiles.num > 0 )
      {
        v58 = pakfiles.num;
        v15 = Memory::Allocate(4 * pakfiles.num);
        num = pakfiles.num;
        v60 = v15;
        v14 = v15;
      }
      else
      {
        v14 = 0;
        v60 = 0;
        v58 = 0;
      }
      v16 = 0;
      v57 = v13;
      if ( num > 0 )
      {
        v17 = 0;
        do
        {
          v14[v16] = &pakfiles.list[v17];
          num = pakfiles.num;
          ++v16;
          ++v17;
        }
        while ( v16 < pakfiles.num );
      }
      if ( v14 )
      {
        qsort(v14, v13, 4u, (int (__cdecl *)(const void *, const void *))idListSortCompare<idPoolStr const *>);
        num = pakfiles.num;
      }
      v18 = num;
      v45 = num;
      if ( num > 0 )
      {
        v54 = num;
        v20 = num;
        v21 = (int *)Memory::Allocate(32 * num + 4);
        LOBYTE(v62) = 4;
        if ( v21 )
        {
          v22 = v21 + 1;
          *v21 = v20;
          `eh vector constructor iterator'(
            v21 + 1,
            0x20u,
            v20,
            (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          v23 = (int)v22;
          v18 = v45;
        }
        else
        {
          v23 = 0;
        }
        num = pakfiles.num;
        LOBYTE(v62) = 3;
        v56 = (idStr *)v23;
        v19 = (idStr *)v23;
      }
      else
      {
        v19 = 0;
        v56 = 0;
        v54 = 0;
      }
      v53 = v18;
      granularity = pakfiles.granularity;
      if ( v19 )
      {
        v24 = pakfiles.granularity + v18 - 1 - (pakfiles.granularity + v18 - 1) % pakfiles.granularity;
        if ( v24 != v54 )
        {
          if ( v24 > 0 )
          {
            v25 = v19;
            v51 = v19;
            v54 = v24;
            if ( v24 < v45 )
              v53 = v24;
            v26 = (int *)Memory::Allocate(32 * v24 + 4);
            LOBYTE(v62) = 5;
            if ( v26 )
            {
              v27 = v26 + 1;
              *v26 = v24;
              `eh vector constructor iterator'(
                v26 + 1,
                0x20u,
                v24,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              v28 = (int)v27;
            }
            else
            {
              v28 = 0;
            }
            LOBYTE(v62) = 3;
            v56 = (idStr *)v28;
            if ( v53 > 0 )
            {
              v46 = (unsigned int *)v25;
              v29 = (char *)v25 - v28;
              v30 = v28 + 4;
              v50 = v29;
              v48 = v53;
              while ( 1 )
              {
                v31 = *v46;
                v32 = *v46 + 1;
                if ( v32 > *(_DWORD *)(v30 + 4) )
                  idStr::ReAllocate((idStr *)(v30 - 4), v32, 0);
                v46 += 8;
                qmemcpy(*(void **)v30, *(const void **)&v29[v30], v31);
                *(_BYTE *)(v31 + *(_DWORD *)v30) = 0;
                *(_DWORD *)(v30 - 4) = v31;
                v30 += 32;
                if ( !--v48 )
                  break;
                v29 = v50;
              }
              v3 = this;
              v25 = v51;
            }
            `eh vector destructor iterator'(
              v25,
              0x20u,
              *(_DWORD *)&v25[-1].baseBuffer[16],
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(&v25[-1].baseBuffer[16]);
          }
          else
          {
            `eh vector destructor iterator'(
              v19,
              0x20u,
              *(_DWORD *)&v19[-1].baseBuffer[16],
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(&v19[-1].baseBuffer[16]);
            v56 = 0;
            v53 = 0;
            v54 = 0;
          }
          num = pakfiles.num;
          v19 = v56;
          v14 = v60;
        }
      }
      v47 = 0;
      if ( v53 > 0 )
      {
        p_data = &v19->data;
        do
        {
          v34 = v14[v47];
          v35 = *(_DWORD *)v34;
          v36 = *(_DWORD *)v34 + 1;
          if ( v36 > (int)p_data[1] )
            idStr::ReAllocate((idStr *)(p_data - 1), v36, 0);
          qmemcpy(*p_data, *(const void **)(v34 + 4), v35);
          v14 = v60;
          (*p_data)[v35] = 0;
          *(p_data - 1) = (char *)v35;
          p_data += 8;
          ++v47;
        }
        while ( v47 < v53 );
        num = pakfiles.num;
        v3 = this;
        v19 = v56;
      }
      list = pakfiles.list;
      v38 = num;
      num = v53;
      v53 = v38;
      size = pakfiles.size;
      pakfiles.size = v54;
      v54 = size;
      v40 = pakfiles.granularity;
      pakfiles.num = num;
      pakfiles.granularity = granularity;
      granularity = v40;
      pakfiles.list = v19;
      v56 = list;
      LOBYTE(v62) = 2;
      if ( v14 )
      {
        Memory::Free(v14);
        num = pakfiles.num;
      }
      LOBYTE(v62) = 1;
      if ( list )
      {
        `eh vector destructor iterator'(
          list,
          0x20u,
          *(_DWORD *)&list[-1].baseBuffer[16],
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        Memory::Free(&list[-1].baseBuffer[16]);
        num = pakfiles.num;
      }
      v6 = dir;
      v9 = path;
    }
    patha = 0;
    if ( num > 0 )
    {
      i = 0;
      do
      {
        v41 = (char *)v3->BuildOSPath(v3, v9, v6, pakfiles.list[i].data);
        idStr::operator=(&pakfile, v41);
        ZipFile = idFileSystemLocal::LoadZipFile(v3, (int)v9, pakfile.data);
        if ( ZipFile )
        {
          v43 = (_iobuf **)Memory::Allocate(0xCu);
          v43[1] = 0;
          *v43 = ZipFile;
          v43[2] = (_iobuf *)v3->searchPaths->next;
          v3->searchPaths->next = (searchpath_s *)v43;
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "Loaded pk4 %s with checksum 0x%x\n",
            pakfile.data,
            ZipFile[1]._cnt);
        }
        ++i;
        ++patha;
      }
      while ( (int)patha < pakfiles.num );
    }
    LOBYTE(v62) = 0;
    if ( pakfiles.list )
    {
      v44 = &pakfiles.list[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        pakfiles.list,
        0x20u,
        *(_DWORD *)&pakfiles.list[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v44);
    }
    pakfiles.list = 0;
    pakfiles.num = 0;
    pakfiles.size = 0;
    v62 = -1;
    idStr::FreeData(&pakfile);
  }
}

// FUNC: private: void __thiscall idFileSystemLocal::SetupGameDirectories(char const *)
void __thiscall idFileSystemLocal::SetupGameDirectories(idFileSystemLocal *this, char *gameName)
{
  char *value; // eax
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax

  value = (char *)idFileSystemLocal::fs_cdpath.internalVar->value;
  if ( *value )
    idFileSystemLocal::AddGameDirectory(this, value, gameName);
  v4 = (char *)idFileSystemLocal::fs_basepath.internalVar->value;
  if ( *v4 )
    idFileSystemLocal::AddGameDirectory(this, v4, gameName);
  v5 = (char *)idFileSystemLocal::fs_devpath.internalVar->value;
  if ( *v5 )
    idFileSystemLocal::AddGameDirectory(this, v5, gameName);
  v6 = (char *)idFileSystemLocal::fs_savepath.internalVar->value;
  if ( *v6 )
    idFileSystemLocal::AddGameDirectory(this, v6, gameName);
}

// FUNC: public: virtual int __thiscall idFileSystemLocal::ValidateDownloadPakForChecksum(int,char * const,bool)
int __thiscall idFileSystemLocal::ValidateDownloadPakForChecksum(
        idFileSystemLocal *this,
        int checksum,
        char *path,
        bool isBinary)
{
  searchpath_s *searchPaths; // eax
  pack_t *pack; // ebx
  unsigned int len; // ebp
  int v8; // eax
  char *data; // esi
  const char *value; // esi
  idStr *v11; // ebx
  unsigned int v12; // eax
  int v13; // edi
  int v14; // eax
  char *v15; // edx
  const char *v16; // ecx
  char v17; // al
  _DWORD *v18; // eax
  int v19; // ebp
  bool v20; // cc
  const char *v21; // esi
  int v22; // eax
  unsigned int v23; // eax
  int v24; // edi
  int v25; // eax
  char *v26; // edx
  const char *v27; // ecx
  char v28; // al
  unsigned int v29; // esi
  int v30; // eax
  const char *v31; // esi
  int v32; // eax
  unsigned int v33; // eax
  int v34; // edi
  int v35; // eax
  char *v36; // edx
  const char *v37; // ecx
  char v38; // al
  unsigned int v39; // esi
  int v40; // eax
  const char *v41; // esi
  int v42; // eax
  unsigned int v43; // eax
  int v44; // edi
  int v45; // eax
  char *v46; // edx
  const char *v47; // ecx
  char v48; // al
  unsigned int v49; // esi
  int v50; // eax
  int v51; // edi
  idStr *v52; // esi
  pack_t *v53; // ebp
  int length; // ebp
  int v55; // [esp-Ch] [ebp-9Ch]
  int v56; // [esp-Ch] [ebp-9Ch]
  pack_t *pak; // [esp+Ch] [ebp-84h]
  idStr name; // [esp+24h] [ebp-6Ch] BYREF
  idStr relativePath; // [esp+44h] [ebp-4Ch] BYREF
  idStr v60; // [esp+64h] [ebp-2Ch] BYREF
  int v61; // [esp+8Ch] [ebp-4h]

  v61 = 0;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  relativePath.len = 0;
  relativePath.alloced = 20;
  relativePath.data = relativePath.baseBuffer;
  relativePath.baseBuffer[0] = 0;
  searchPaths = this->searchPaths;
  LOBYTE(v61) = 2;
  if ( !searchPaths )
    goto LABEL_7;
  while ( !searchPaths->pack || searchPaths->pack->checksum != checksum )
  {
    searchPaths = searchPaths->next;
    if ( !searchPaths )
      goto LABEL_7;
  }
  pack = searchPaths->pack;
  pak = searchPaths->pack;
  if ( !searchPaths->pack )
  {
LABEL_7:
    LOBYTE(v61) = 1;
    idStr::FreeData(&relativePath);
    LOBYTE(v61) = 0;
    idStr::FreeData(&name);
    return 0;
  }
  len = pack->pakFilename.len;
  v8 = pack->pakFilename.len + 1;
  if ( v8 > 20 )
    idStr::ReAllocate(&name, v8, 0);
  qmemcpy(name.data, pack->pakFilename.data, len);
  name.data[len] = 0;
  name.len = len;
  idStr::StripPath(&name);
  data = name.data;
  if ( strstr(name.data, "pak") == data )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "%s is not a donwloadable pak\n",
      pack->pakFilename.data);
LABEL_12:
    LOBYTE(v61) = 1;
    idStr::FreeData(&relativePath);
    LOBYTE(v61) = 0;
    idStr::FreeData(&name);
    return 0;
  }
  if ( isBinary != (pack->binary == BINARY_YES) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "%s binary flag mismatch\n",
      pack->pakFilename.data);
    goto LABEL_12;
  }
  value = idFileSystemLocal::fs_savepath.internalVar->value;
  v11 = 0;
  v60.len = 0;
  v60.alloced = 20;
  v60.data = v60.baseBuffer;
  v60.baseBuffer[0] = 0;
  if ( value )
  {
    v12 = (unsigned int)&value[strlen(value) + 1];
    v13 = v12 - (_DWORD)(value + 1);
    v14 = v12 - (_DWORD)value;
    if ( v14 > 20 )
      idStr::ReAllocate(&v60, v14, 1);
    v15 = v60.data;
    v16 = value;
    do
    {
      v17 = *v16;
      *v15++ = *v16++;
    }
    while ( v17 );
    v60.len = v13;
  }
  LOBYTE(v61) = 3;
  v18 = Memory::Allocate(0x204u);
  LOBYTE(v61) = 4;
  if ( v18 )
  {
    v11 = (idStr *)(v18 + 1);
    *v18 = 16;
    `eh vector constructor iterator'(
      v18 + 1,
      0x20u,
      16,
      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  }
  v19 = v60.len;
  v20 = v60.len + 1 <= v11->alloced;
  LOBYTE(v61) = 3;
  if ( !v20 )
    idStr::ReAllocate(v11, v60.len + 1, 0);
  qmemcpy(v11->data, v60.data, v19);
  v11->data[v19] = 0;
  v11->len = v19;
  LOBYTE(v61) = 2;
  idStr::FreeData(&v60);
  v21 = idFileSystemLocal::fs_devpath.internalVar->value;
  v22 = 0;
  v60.len = 0;
  v60.alloced = 20;
  v60.data = v60.baseBuffer;
  v60.baseBuffer[0] = 0;
  if ( v21 )
  {
    v23 = (unsigned int)&v21[strlen(v21) + 1];
    v24 = v23 - (_DWORD)(v21 + 1);
    v25 = v23 - (_DWORD)v21;
    if ( v25 > 20 )
      idStr::ReAllocate(&v60, v25, 1);
    v26 = v60.data;
    v27 = v21;
    do
    {
      v28 = *v27;
      *v26++ = *v27++;
    }
    while ( v28 );
    v22 = v24;
    v60.len = v24;
  }
  v29 = v22;
  v30 = v22 + 1;
  v20 = v30 <= v11[1].alloced;
  LOBYTE(v61) = 6;
  if ( !v20 )
    idStr::ReAllocate(v11 + 1, v30, 0);
  qmemcpy(v11[1].data, v60.data, v29);
  v11[1].data[v29] = 0;
  v11[1].len = v29;
  LOBYTE(v61) = 2;
  idStr::FreeData(&v60);
  v31 = idFileSystemLocal::fs_basepath.internalVar->value;
  v32 = 0;
  v60.len = 0;
  v60.alloced = 20;
  v60.data = v60.baseBuffer;
  v60.baseBuffer[0] = 0;
  if ( v31 )
  {
    v33 = (unsigned int)&v31[strlen(v31) + 1];
    v34 = v33 - (_DWORD)(v31 + 1);
    v35 = v33 - (_DWORD)v31;
    if ( v35 > 20 )
      idStr::ReAllocate(&v60, v35, 1);
    v36 = v60.data;
    v37 = v31;
    do
    {
      v38 = *v37;
      *v36++ = *v37++;
    }
    while ( v38 );
    v32 = v34;
    v60.len = v34;
  }
  v39 = v32;
  v40 = v32 + 1;
  v20 = v40 <= v11[2].alloced;
  LOBYTE(v61) = 9;
  if ( !v20 )
    idStr::ReAllocate(v11 + 2, v40, 0);
  qmemcpy(v11[2].data, v60.data, v39);
  v11[2].data[v39] = 0;
  v11[2].len = v39;
  LOBYTE(v61) = 2;
  idStr::FreeData(&v60);
  v41 = idFileSystemLocal::fs_cdpath.internalVar->value;
  v42 = 0;
  v60.len = 0;
  v60.alloced = 20;
  v60.data = v60.baseBuffer;
  v60.baseBuffer[0] = 0;
  if ( v41 )
  {
    v43 = (unsigned int)&v41[strlen(v41) + 1];
    v44 = v43 - (_DWORD)(v41 + 1);
    v45 = v43 - (_DWORD)v41;
    if ( v45 > 20 )
      idStr::ReAllocate(&v60, v45, 1);
    v46 = v60.data;
    v47 = v41;
    do
    {
      v48 = *v47;
      *v46++ = *v47++;
    }
    while ( v48 );
    v42 = v44;
    v60.len = v44;
  }
  v49 = v42;
  v50 = v42 + 1;
  v20 = v50 <= v11[3].alloced;
  LOBYTE(v61) = 12;
  if ( !v20 )
    idStr::ReAllocate(v11 + 3, v50, 0);
  qmemcpy(v11[3].data, v60.data, v49);
  v11[3].data[v49] = 0;
  v11[3].len = v49;
  LOBYTE(v61) = 2;
  idStr::FreeData(&v60);
  v51 = 0;
  v52 = v11;
  while ( 1 )
  {
    if ( v52->len )
    {
      v53 = pak;
      if ( !idStr::Icmpn(v52->data, pak->pakFilename.data, v52->len) )
        break;
    }
    ++v51;
    ++v52;
    if ( v51 >= 4 )
    {
      v53 = pak;
      goto LABEL_55;
    }
  }
  idStr::operator=(&relativePath, &pak->pakFilename.data[v11[v51].len + 1]);
LABEL_55:
  if ( v51 == 4 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idFileSystem::ValidateDownloadPak: failed to extract relative path for %s",
      v53->pakFilename.data);
    LOBYTE(v61) = 1;
    idStr::FreeData(&relativePath);
    LOBYTE(v61) = 0;
    idStr::FreeData(&name);
    v55 = *(_DWORD *)&v11[-1].baseBuffer[16];
    v61 = -1;
    `eh vector destructor iterator'(
      v11,
      0x20u,
      v55,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(&v11[-1].baseBuffer[16]);
    return 0;
  }
  else
  {
    idStr::Copynz(path, relativePath.data, 1024);
    length = v53->length;
    LOBYTE(v61) = 1;
    idStr::FreeData(&relativePath);
    LOBYTE(v61) = 0;
    idStr::FreeData(&name);
    v56 = *(_DWORD *)&v11[-1].baseBuffer[16];
    v61 = -1;
    `eh vector destructor iterator'(
      v11,
      0x20u,
      v56,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(&v11[-1].baseBuffer[16]);
    return length;
  }
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::OpenFileReadFlags(char const *,int,struct pack_t * *,bool,char const *)
idFile_InZip *__thiscall idFileSystemLocal::OpenFileReadFlags(
        idFileSystemLocal *this,
        char *relativePath,
        char searchFlags,
        pack_t **foundInPak,
        bool allowCopyFiles,
        const char *gamedir)
{
  bool v7; // zf
  char *v8; // ebx
  int v9; // eax
  searchpath_s *searchPaths; // edi
  searchpath_s *addonPaks; // edi
  pack_t *pack; // ebx
  fileInPack_s *v13; // esi
  const char *v14; // esi
  directory_t *dir; // ebx
  char *v16; // eax
  _iobuf *v17; // esi
  idFile_Permanent *v18; // eax
  idFile_InZip *v19; // eax
  idFile_InZip *v20; // edi
  int v21; // edx
  int v22; // eax
  pack_t **list; // ecx
  pack_t *v24; // ecx
  int v25; // ebx
  int v26; // eax
  char v27; // cl
  char *v28; // edx
  pack_t *v29; // ebx
  int v30; // eax
  fileInPack_s *v31; // esi
  fileInPack_s *v32; // esi
  idFile_InZip *v33; // ecx
  _iobuf *z; // eax
  int v35; // eax
  const char *v36; // esi
  idFileSystemLocal_vtbl *v37; // edx
  char *v38; // eax
  int v39; // esi
  int v40; // eax
  char v41; // cl
  char *v42; // edx
  int v43; // esi
  int i; // eax
  char v45; // cl
  char *v46; // edx
  int v47; // eax
  bool v48; // cl
  idFileSystemLocal_vtbl *v49; // edx
  char *v50; // eax
  _iobuf *v51; // esi
  int v52; // edi
  _iobuf *v53; // eax
  _iobuf *v54; // esi
  int v55; // ebx
  unsigned int v56; // eax
  int v57; // ebx
  int v58; // eax
  char *v59; // edx
  const char *v60; // ecx
  char v61; // al
  int v62; // esi
  bool v63; // cc
  int v64; // ebx
  int granularity; // esi
  int *v66; // eax
  idStr *v67; // ebx
  idStr *v68; // ebx
  const void *v69; // esi
  int num; // edi
  int size; // eax
  int v72; // esi
  idStr *v73; // eax
  char *v74; // esi
  int *v75; // eax
  idStr *v76; // edi
  idStr *v77; // ebx
  char *v78; // esi
  idStr *v79; // eax
  const char *v80; // eax
  int v81; // esi
  int v82; // eax
  char *v83; // edx
  char *v84; // ecx
  char v85; // al
  int v86; // esi
  int v87; // ebx
  int v88; // esi
  int *v89; // eax
  idStr *v90; // ebx
  idStr *v91; // ebx
  const void *v92; // esi
  int v93; // edi
  int v94; // eax
  int v95; // esi
  int *v96; // eax
  idStr *v97; // edi
  idStr *v98; // ebx
  const void *v99; // esi
  char *v100; // esi
  idStr *v101; // ebx
  int v102; // esi
  idFile_InZip *FileFromZip; // esi
  const char *v105; // [esp-4h] [ebp-D0h]
  const char *v106; // [esp+0h] [ebp-CCh]
  const char *value; // [esp+8h] [ebp-C4h]
  const char *v108; // [esp+8h] [ebp-C4h]
  const char *data; // [esp+Ch] [ebp-C0h]
  const char *v110; // [esp+Ch] [ebp-C0h]
  searchpath_s *search; // [esp+24h] [ebp-A8h]
  searchpath_s *searcha; // [esp+24h] [ebp-A8h]
  idStr *searchb; // [esp+24h] [ebp-A8h]
  unsigned int *searchc; // [esp+24h] [ebp-A8h]
  searchpath_s *searchd; // [esp+24h] [ebp-A8h]
  bool isFromCDPath; // [esp+2Bh] [ebp-A1h]
  int hash; // [esp+2Ch] [ebp-A0h]
  unsigned int *hasha; // [esp+2Ch] [ebp-A0h]
  int hashb; // [esp+2Ch] [ebp-A0h]
  idStr *hashc; // [esp+2Ch] [ebp-A0h]
  unsigned int v121; // [esp+30h] [ebp-9Ch]
  unsigned int v122; // [esp+30h] [ebp-9Ch]
  unsigned int v123; // [esp+30h] [ebp-9Ch]
  int v124; // [esp+30h] [ebp-9Ch]
  int len; // [esp+34h] [ebp-98h]
  unsigned int v126; // [esp+34h] [ebp-98h]
  int v127; // [esp+34h] [ebp-98h]
  int v128; // [esp+34h] [ebp-98h]
  int v129; // [esp+34h] [ebp-98h]
  idStr loadedFile; // [esp+38h] [ebp-94h] BYREF
  idFile_InZip *file; // [esp+58h] [ebp-74h]
  bool isFromSavePath; // [esp+5Fh] [ebp-6Dh]
  idStr netpath; // [esp+60h] [ebp-6Ch] BYREF
  idStr pakName; // [esp+80h] [ebp-4Ch] BYREF
  idStr sourcepath; // [esp+A0h] [ebp-2Ch] BYREF
  int v136; // [esp+C8h] [ebp-4h]

  netpath.len = 0;
  netpath.alloced = 20;
  netpath.data = netpath.baseBuffer;
  netpath.baseBuffer[0] = 0;
  v7 = this->searchPaths == 0;
  v136 = 0;
  if ( v7 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  v8 = relativePath;
  if ( !relativePath )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFileSystemLocal::OpenFileRead: NULL 'relativePath' parameter passed\n");
  if ( foundInPak )
    *foundInPak = 0;
  if ( session->GetMapSpawned(session)
    && !this->isFileLoadingAllowed
    && !(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, -1) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Loading non pre-cached file %s",
      relativePath);
  }
  if ( *relativePath == 47 || *relativePath == 92 )
    v8 = ++relativePath;
  if ( strstr(v8, "..")
    || strstr(v8, "::")
    || !*v8
    || (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 16))(common.type)
    && (!idStr::Icmp(v8, "quake4key") || !idStr::Icmp(v8, "quake4key")) )
  {
    v136 = -1;
    goto LABEL_226;
  }
  v9 = idFileSystemLocal::HashFileName(this, v8);
  searchPaths = this->searchPaths;
  hash = v9;
  search = searchPaths;
  if ( !searchPaths )
  {
LABEL_21:
    if ( (searchFlags & 0x10) != 0 )
    {
      addonPaks = this->addonPaks;
      if ( addonPaks )
      {
        while ( 1 )
        {
          pack = addonPaks->pack;
          v13 = addonPaks->pack->hashTable[hash];
          if ( v13 )
            break;
LABEL_26:
          addonPaks = addonPaks->next;
          if ( !addonPaks )
            goto LABEL_27;
        }
        while ( idFileSystemLocal::FilenameCompare(this, v13->name.data, relativePath) )
        {
          v13 = v13->next;
          if ( !v13 )
            goto LABEL_26;
        }
        FileFromZip = idFileSystemLocal::ReadFileFromZip(this, pack, v13, relativePath);
        if ( foundInPak )
          *foundInPak = pack;
        if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "idFileSystem::OpenFileRead: %s (found in addon pk4 '%s')\n",
            relativePath,
            addonPaks->pack->pakFilename.data);
        v136 = -1;
        idStr::FreeData(&netpath);
        return FileFromZip;
      }
    }
LABEL_27:
    if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Can't find %s\n",
        relativePath);
    v136 = -1;
LABEL_226:
    idStr::FreeData(&netpath);
    return 0;
  }
  while ( 1 )
  {
    v14 = gamedir;
    if ( searchPaths->dir && (searchFlags & 1) != 0 )
    {
      if ( idFileSystemLocal::fs_restrict.internalVar->integerValue || this->serverPaks.num )
      {
        if ( !idFileSystemLocal::FileAllowedFromDir(this, v8) )
          goto LABEL_76;
        v14 = gamedir;
      }
      dir = searchPaths->dir;
      if ( !v14 || !strlen(v14) || !idStr::Cmp(dir->gamedir.data, v14) )
      {
        v16 = (char *)this->BuildOSPath(this, dir->path.data, dir->gamedir.data, relativePath);
        idStr::operator=(&netpath, v16);
        v17 = idFileSystemLocal::OpenOSFileCorrectName(this, &netpath, "rb");
        if ( v17 )
        {
          v18 = (idFile_Permanent *)Memory::Allocate(0x54u);
          LOBYTE(v136) = 1;
          if ( v18 )
          {
            idFile_Permanent::idFile_Permanent(v18);
            v20 = v19;
          }
          else
          {
            v20 = 0;
          }
          file = v20;
          LOBYTE(v136) = 0;
          v20->z = v17;
          idStr::operator=(&v20->name, relativePath);
          len = netpath.len;
          if ( netpath.len + 1 > v20->fullPath.alloced )
            idStr::ReAllocate(&v20->fullPath, netpath.len + 1, 0);
          qmemcpy(file->fullPath.data, netpath.data, len);
          v33 = file;
          file->fullPath.data[len] = 0;
          v33->fullPath.len = len;
          z = (_iobuf *)v33->z;
          v33->zipFilePos = 1;
          v35 = idFileSystemLocal::DirectFileLength(this, z);
          file->fileSize = v35;
          v36 = relativePath;
          if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "idFileSystem::OpenFileRead: %s size %d (found in '%s/%s')\n",
              relativePath,
              v35,
              dir->path.data,
              dir->gamedir.data);
          if ( !this->loadedFileFromDir && !idFileSystemLocal::FileAllowedFromDir(this, relativePath) )
          {
            if ( this->restartChecksums.num )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
                common.type,
                "'%s' loaded from directory: Failed to restart with pure mode restrictions for server connect",
                relativePath);
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
              common.type,
              "filesystem: switching to pure mode will require a restart. '%s' loaded from directory.\n",
              relativePath);
            this->loadedFileFromDir = 1;
          }
          if ( allowCopyFiles && idFileSystemLocal::fs_copyfiles.internalVar->integerValue )
          {
            loadedFile.len = 0;
            loadedFile.alloced = 20;
            loadedFile.data = loadedFile.baseBuffer;
            loadedFile.baseBuffer[0] = 0;
            pakName.len = 0;
            pakName.alloced = 20;
            pakName.data = pakName.baseBuffer;
            pakName.baseBuffer[0] = 0;
            v37 = this->__vftable;
            data = dir->gamedir.data;
            value = idFileSystemLocal::fs_savepath.internalVar->value;
            LOBYTE(v136) = 3;
            v38 = (char *)v37->BuildOSPath(this, value, data, relativePath);
            idStr::operator=(&loadedFile, v38);
            idStr::ExtractFileName(&netpath, &pakName);
            idStr::StripFilename(&loadedFile);
            v39 = loadedFile.len + 1;
            if ( loadedFile.len + 2 > loadedFile.alloced )
              idStr::ReAllocate(&loadedFile, loadedFile.len + 2, 1);
            v40 = 0;
            v41 = 47;
            do
            {
              v42 = &loadedFile.data[v40++];
              v42[loadedFile.len] = v41;
              v41 = b[v40];
            }
            while ( v41 );
            loadedFile.len = v39;
            loadedFile.data[v39] = 0;
            v43 = pakName.len + loadedFile.len;
            if ( pakName.len + loadedFile.len + 1 > loadedFile.alloced )
              idStr::ReAllocate(&loadedFile, pakName.len + loadedFile.len + 1, 1);
            for ( i = 0; i < pakName.len; v46[loadedFile.len] = v45 )
            {
              v45 = pakName.data[i];
              v46 = &loadedFile.data[i++];
            }
            loadedFile.len = v43;
            loadedFile.data[v43] = 0;
            isFromCDPath = idStr::Cmp(dir->path.data, idFileSystemLocal::fs_cdpath.internalVar->value) == 0;
            v47 = idStr::Cmp(dir->path.data, idFileSystemLocal::fs_savepath.internalVar->value);
            v106 = idFileSystemLocal::fs_basepath.internalVar->value;
            v105 = dir->path.data;
            isFromSavePath = v47 == 0;
            v48 = idStr::Cmp(v105, v106) == 0;
            switch ( idFileSystemLocal::fs_copyfiles.internalVar->integerValue )
            {
              case 1:
                if ( isFromCDPath )
                  goto LABEL_114;
                break;
              case 2:
                if ( isFromCDPath )
                  goto LABEL_114;
                if ( isFromSavePath || v48 )
                {
                  sourcepath.len = 0;
                  sourcepath.alloced = 20;
                  sourcepath.data = sourcepath.baseBuffer;
                  sourcepath.baseBuffer[0] = 0;
                  v49 = this->__vftable;
                  v110 = dir->gamedir.data;
                  v108 = idFileSystemLocal::fs_cdpath.internalVar->value;
                  LOBYTE(v136) = 4;
                  v50 = (char *)v49->BuildOSPath(this, v108, v110, relativePath);
                  idStr::operator=(&sourcepath, v50);
                  v51 = idFileSystemLocal::OpenOSFile(this, sourcepath.data, "r", 0);
                  if ( v51 )
                  {
                    v52 = sys->FileTimeStamp(sys, v51);
                    sys->FClose(sys, v51);
                    v53 = idFileSystemLocal::OpenOSFile(this, loadedFile.data, "r", 0);
                    v54 = v53;
                    if ( v53 )
                    {
                      v55 = sys->FileTimeStamp(sys, v53);
                      sys->FClose(sys, v54);
                      if ( v52 > v55 )
                        this->CopyOSFile(this, sourcepath.data, loadedFile.data);
                    }
                  }
                  LOBYTE(v136) = 3;
                  idStr::FreeData(&sourcepath);
                }
                break;
              case 3:
                if ( isFromCDPath || v48 )
                  goto LABEL_114;
                break;
              case 4:
                if ( isFromCDPath && !v48 )
LABEL_114:
                  this->CopyOSFile(this, netpath.data, loadedFile.data);
                break;
              default:
                break;
            }
            LOBYTE(v136) = 2;
            idStr::FreeData(&pakName);
            LOBYTE(v136) = 0;
            idStr::FreeData(&loadedFile);
            v36 = relativePath;
          }
          if ( com_makingBuild.internalVar->integerValue && com_Bundler.internalVar->integerValue )
          {
            loadedFile.len = 0;
            loadedFile.alloced = 20;
            loadedFile.data = loadedFile.baseBuffer;
            loadedFile.baseBuffer[0] = 0;
            v56 = (unsigned int)&v36[strlen(v36) + 1];
            v57 = v56 - (_DWORD)(v36 + 1);
            v58 = v56 - (_DWORD)v36;
            if ( v58 > 20 )
              idStr::ReAllocate(&loadedFile, v58, 1);
            v59 = loadedFile.data;
            v60 = v36;
            do
            {
              v61 = *v60;
              *v59++ = *v60++;
            }
            while ( v61 );
            loadedFile.len = v57;
            v62 = 0;
            v63 = this->assetLog.num <= 0;
            LOBYTE(v136) = 5;
            if ( !v63 )
            {
              v64 = 0;
              while ( idStr::Cmp(this->assetLog.list[v64].data, loadedFile.data) )
              {
                ++v62;
                ++v64;
                if ( v62 >= this->assetLog.num )
                  goto LABEL_128;
              }
              if ( v62 >= 0 )
                goto LABEL_218;
            }
LABEL_128:
            if ( !this->assetLog.list )
            {
              granularity = this->assetLog.granularity;
              if ( granularity > 0 )
              {
                if ( granularity != this->assetLog.size )
                {
                  v63 = granularity < this->assetLog.num;
                  this->assetLog.size = granularity;
                  if ( v63 )
                    this->assetLog.num = granularity;
                  v66 = (int *)Memory::Allocate(32 * granularity + 4);
                  LOBYTE(v136) = 6;
                  if ( v66 )
                  {
                    v67 = (idStr *)(v66 + 1);
                    *v66 = granularity;
                    `eh vector constructor iterator'(
                      v66 + 1,
                      0x20u,
                      granularity,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  }
                  else
                  {
                    v67 = 0;
                  }
                  v63 = this->assetLog.num <= 0;
                  LOBYTE(v136) = 5;
                  this->assetLog.list = v67;
                  searcha = 0;
                  if ( !v63 )
                  {
                    hasha = 0;
                    do
                    {
                      v68 = (idStr *)((char *)hasha + (unsigned int)this->assetLog.list);
                      v126 = *hasha;
                      if ( (signed int)(*hasha + 1) > v68->alloced )
                        idStr::ReAllocate(v68, v126 + 1, 0);
                      v69 = (const void *)hasha[1];
                      hasha += 8;
                      qmemcpy(v68->data, v69, v126);
                      v68->data[v126] = 0;
                      v68->len = v126;
                      searcha = (searchpath_s *)((char *)searcha + 1);
                    }
                    while ( (int)searcha < this->assetLog.num );
                  }
                }
              }
              else
              {
                this->assetLog.list = 0;
                this->assetLog.num = 0;
                this->assetLog.size = 0;
              }
            }
            num = this->assetLog.num;
            size = this->assetLog.size;
            if ( num != size )
              goto LABEL_215;
            if ( !this->assetLog.granularity )
              this->assetLog.granularity = 16;
            v72 = size + this->assetLog.granularity - (size + this->assetLog.granularity) % this->assetLog.granularity;
            if ( v72 > 0 )
            {
              if ( v72 != this->assetLog.size )
              {
                searchb = this->assetLog.list;
                this->assetLog.size = v72;
                if ( v72 < num )
                  this->assetLog.num = v72;
                v75 = (int *)Memory::Allocate(32 * v72 + 4);
                LOBYTE(v136) = 7;
                if ( v75 )
                {
                  v76 = (idStr *)(v75 + 1);
                  *v75 = v72;
                  `eh vector constructor iterator'(
                    v75 + 1,
                    0x20u,
                    v72,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v76 = 0;
                }
                v63 = this->assetLog.num <= 0;
                LOBYTE(v136) = 5;
                this->assetLog.list = v76;
                v127 = 0;
                if ( !v63 )
                {
                  hashb = 0;
                  do
                  {
                    v77 = &this->assetLog.list[hashb];
                    v121 = searchb[hashb].len;
                    if ( (signed int)(v121 + 1) > v77->alloced )
                      idStr::ReAllocate(v77, v121 + 1, 0);
                    v78 = searchb[hashb++].data;
                    qmemcpy(v77->data, v78, v121);
                    v77->data[v121] = 0;
                    v77->len = v121;
                    ++v127;
                  }
                  while ( v127 < this->assetLog.num );
                }
                if ( searchb )
                {
                  v79 = searchb;
                  goto LABEL_214;
                }
              }
              goto LABEL_215;
            }
            goto LABEL_146;
          }
          goto LABEL_219;
        }
      }
      goto LABEL_76;
    }
    if ( searchPaths->pack && (searchFlags & 2) != 0 && searchPaths->pack->hashTable[hash] )
    {
      if ( !this->serverPaks.num )
        goto LABEL_230;
      idFileSystemLocal::GetPackStatus(this, searchPaths->pack);
      if ( searchPaths->pack->pureStatus == PURE_NEVER )
        goto LABEL_230;
      v21 = this->serverPaks.num;
      v22 = 0;
      if ( v21 > 0 )
      {
        list = this->serverPaks.list;
        while ( *list != searchPaths->pack )
        {
          ++v22;
          ++list;
          if ( v22 >= v21 )
            goto LABEL_76;
        }
        if ( v22 >= 0 && &this->serverPaks.list[v22] )
        {
LABEL_230:
          if ( cvarSystem->GetCVarBool(cvarSystem, "fs_mapPaks") )
          {
            loadedFile.len = 0;
            loadedFile.alloced = 20;
            loadedFile.data = loadedFile.baseBuffer;
            loadedFile.baseBuffer[0] = 0;
            pakName.len = 0;
            pakName.alloced = 20;
            pakName.data = pakName.baseBuffer;
            pakName.baseBuffer[0] = 0;
            v24 = searchPaths->pack;
            LOBYTE(v136) = 9;
            idStr::ExtractFileName(&v24->pakFilename, &pakName);
            idStr::ExtractFileName(&this->currentAssetLogUnfiltered, &loadedFile);
            idStr::StripFileExtension(&loadedFile);
            v25 = loadedFile.len + 4;
            if ( loadedFile.len + 5 > loadedFile.alloced )
              idStr::ReAllocate(&loadedFile, loadedFile.len + 5, 1);
            v26 = 0;
            v27 = 46;
            do
            {
              v28 = &loadedFile.data[v26++];
              v28[loadedFile.len] = v27;
              v27 = aPk4[v26];
            }
            while ( v27 );
            loadedFile.len = v25;
            loadedFile.data[v25] = 0;
            if ( idFileSystemLocal::FilenameCompare(this, loadedFile.data, pakName.data)
              && (idStr::FindText(
                    this->currentAssetLogUnfiltered.data,
                    "/mp/",
                    1,
                    0,
                    this->currentAssetLogUnfiltered.len) == -1
               || idStr::Icmp(pakName.data, "default.pk4")) )
            {
              LOBYTE(v136) = 8;
              idStr::FreeData(&pakName);
              LOBYTE(v136) = 0;
              idStr::FreeData(&loadedFile);
              searchPaths = search;
              goto LABEL_76;
            }
            LOBYTE(v136) = 8;
            idStr::FreeData(&pakName);
            LOBYTE(v136) = 0;
            idStr::FreeData(&loadedFile);
            searchPaths = search;
          }
          v29 = searchPaths->pack;
          if ( (searchFlags & 8) == 0 )
            goto LABEL_229;
          if ( v29->binary == BINARY_UNKNOWN )
          {
            v30 = idFileSystemLocal::HashFileName(this, "binary.conf");
            v29->binary = BINARY_NO;
            v31 = searchPaths->pack->hashTable[v30];
            if ( v31 )
            {
              while ( idFileSystemLocal::FilenameCompare(this, v31->name.data, "binary.conf") )
              {
                v31 = v31->next;
                if ( !v31 )
                  goto LABEL_72;
              }
              v29->binary = BINARY_YES;
            }
          }
LABEL_72:
          if ( v29->binary != BINARY_NO )
          {
LABEL_229:
            v32 = v29->hashTable[hash];
            if ( v32 )
              break;
          }
        }
      }
    }
LABEL_76:
    searchPaths = searchPaths->next;
    search = searchPaths;
    if ( !searchPaths )
      goto LABEL_21;
    v8 = relativePath;
  }
  while ( idFileSystemLocal::FilenameCompare(this, v32->name.data, relativePath) )
  {
    v32 = v32->next;
    if ( !v32 )
      goto LABEL_76;
  }
  file = idFileSystemLocal::ReadFileFromZip(this, v29, v32, relativePath);
  if ( foundInPak )
    *foundInPak = v29;
  if ( !v29->referenced && (searchFlags & 4) == 0 )
  {
    if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idFileSystem::OpenFileRead: %s -> adding %s to referenced paks\n",
        relativePath,
        v29->pakFilename.data);
    v29->referenced = 1;
  }
  if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idFileSystem::OpenFileRead: %s (found in '%s')\n",
      relativePath,
      v29->pakFilename.data);
  if ( com_makingBuild.internalVar->integerValue && com_Bundler.internalVar->integerValue )
  {
    loadedFile.len = 0;
    loadedFile.alloced = 20;
    loadedFile.data = loadedFile.baseBuffer;
    loadedFile.baseBuffer[0] = 0;
    v80 = &relativePath[strlen(relativePath) + 1];
    v81 = v80 - (relativePath + 1);
    v82 = v80 - relativePath;
    if ( v82 > 20 )
      idStr::ReAllocate(&loadedFile, v82, 1);
    v83 = loadedFile.data;
    v84 = relativePath;
    do
    {
      v85 = *v84;
      *v83++ = *v84++;
    }
    while ( v85 );
    loadedFile.len = v81;
    v86 = 0;
    v63 = this->assetLog.num <= 0;
    LOBYTE(v136) = 10;
    if ( !v63 )
    {
      v87 = 0;
      while ( idStr::Cmp(this->assetLog.list[v87].data, loadedFile.data) )
      {
        ++v86;
        ++v87;
        if ( v86 >= this->assetLog.num )
          goto LABEL_183;
      }
      if ( v86 >= 0 )
        goto LABEL_218;
    }
LABEL_183:
    if ( !this->assetLog.list )
    {
      v88 = this->assetLog.granularity;
      if ( v88 > 0 )
      {
        if ( v88 != this->assetLog.size )
        {
          v63 = v88 < this->assetLog.num;
          this->assetLog.size = v88;
          if ( v63 )
            this->assetLog.num = v88;
          v89 = (int *)Memory::Allocate(32 * v88 + 4);
          LOBYTE(v136) = 11;
          if ( v89 )
          {
            v90 = (idStr *)(v89 + 1);
            *v89 = v88;
            `eh vector constructor iterator'(
              v89 + 1,
              0x20u,
              v88,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v90 = 0;
          }
          v63 = this->assetLog.num <= 0;
          LOBYTE(v136) = 10;
          this->assetLog.list = v90;
          v128 = 0;
          if ( !v63 )
          {
            searchc = 0;
            do
            {
              v91 = (idStr *)((char *)searchc + (unsigned int)this->assetLog.list);
              v122 = *searchc;
              if ( (signed int)(*searchc + 1) > v91->alloced )
                idStr::ReAllocate(v91, v122 + 1, 0);
              v92 = (const void *)searchc[1];
              searchc += 8;
              qmemcpy(v91->data, v92, v122);
              v91->data[v122] = 0;
              v91->len = v122;
              ++v128;
            }
            while ( v128 < this->assetLog.num );
          }
        }
      }
      else
      {
        this->assetLog.list = 0;
        this->assetLog.num = 0;
        this->assetLog.size = 0;
      }
    }
    v93 = this->assetLog.num;
    v94 = this->assetLog.size;
    if ( v93 != v94 )
      goto LABEL_215;
    if ( !this->assetLog.granularity )
      this->assetLog.granularity = 16;
    v95 = v94 + this->assetLog.granularity - (v94 + this->assetLog.granularity) % this->assetLog.granularity;
    if ( v95 > 0 )
    {
      if ( v95 != this->assetLog.size )
      {
        hashc = this->assetLog.list;
        this->assetLog.size = v95;
        if ( v95 < v93 )
          this->assetLog.num = v95;
        v96 = (int *)Memory::Allocate(32 * v95 + 4);
        LOBYTE(v136) = 12;
        if ( v96 )
        {
          v97 = (idStr *)(v96 + 1);
          *v96 = v95;
          `eh vector constructor iterator'(
            v96 + 1,
            0x20u,
            v95,
            (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        }
        else
        {
          v97 = 0;
        }
        v63 = this->assetLog.num <= 0;
        LOBYTE(v136) = 10;
        this->assetLog.list = v97;
        v129 = 0;
        if ( !v63 )
        {
          searchd = 0;
          do
          {
            v98 = (idStr *)((char *)searchd + (unsigned int)this->assetLog.list);
            v123 = *(int *)((char *)&hashc->len + (_DWORD)searchd);
            if ( (signed int)(v123 + 1) > v98->alloced )
              idStr::ReAllocate(v98, v123 + 1, 0);
            v99 = *(char **)((char *)&hashc->data + (_DWORD)searchd);
            searchd = (searchpath_s *)((char *)searchd + 32);
            qmemcpy(v98->data, v99, v123);
            v98->data[v123] = 0;
            v98->len = v123;
            ++v129;
          }
          while ( v129 < this->assetLog.num );
        }
        if ( hashc )
        {
          v79 = hashc;
LABEL_214:
          v100 = &v79[-1].baseBuffer[16];
          `eh vector destructor iterator'(
            v79,
            0x20u,
            *(_DWORD *)&v79[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(v100);
        }
      }
LABEL_215:
      v101 = &this->assetLog.list[this->assetLog.num];
      v102 = loadedFile.len;
      v124 = loadedFile.len;
      if ( loadedFile.len + 1 > v101->alloced )
        idStr::ReAllocate(v101, loadedFile.len + 1, 0);
      qmemcpy(v101->data, loadedFile.data, v102);
      v101->data[v124] = 0;
      v101->len = v124;
      ++this->assetLog.num;
LABEL_218:
      LOBYTE(v136) = 0;
      idStr::FreeData(&loadedFile);
      goto LABEL_219;
    }
LABEL_146:
    v73 = this->assetLog.list;
    if ( v73 )
    {
      v74 = &v73[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        v73,
        0x20u,
        *(_DWORD *)&v73[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v74);
    }
    this->assetLog.list = 0;
    this->assetLog.num = 0;
    this->assetLog.size = 0;
    goto LABEL_215;
  }
LABEL_219:
  v136 = -1;
  idStr::FreeData(&netpath);
  return file;
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::OpenFileWrite(char const *,char const *,bool)
idFile *__thiscall idFileSystemLocal::OpenFileWrite(
        idFileSystemLocal *this,
        char *relativePath,
        const char *basePath,
        bool ASCII)
{
  bool v5; // zf
  const char *value; // eax
  char *v7; // eax
  idFile_ASCII *v8; // eax
  int v9; // eax
  idFile_Permanent *v10; // eax
  int v11; // ebp
  _iobuf *v12; // eax
  int len; // esi
  idStr OSpath; // [esp+18h] [ebp-2Ch] BYREF
  int v16; // [esp+40h] [ebp-4h]
  int ASCIIa; // [esp+50h] [ebp+Ch]

  OSpath.len = 0;
  OSpath.alloced = 20;
  OSpath.data = OSpath.baseBuffer;
  OSpath.baseBuffer[0] = 0;
  v5 = this->searchPaths == 0;
  v16 = 0;
  if ( v5 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization");
  value = cvarSystem->GetCVarString(cvarSystem, basePath);
  if ( !*value )
    value = idFileSystemLocal::fs_savepath.internalVar->value;
  v7 = (char *)this->BuildOSPath(this, value, this->gameFolder.data, relativePath);
  idStr::operator=(&OSpath, v7);
  if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idFileSystem::OpenFileWrite: %s\n",
      OSpath.data);
  this->ClearDirCache(this);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "writing to: %s\n",
    OSpath.data);
  this->CreateOSPath(this, OSpath.data);
  if ( ASCII )
  {
    v8 = (idFile_ASCII *)Memory::Allocate(0x58u);
    LOBYTE(v16) = 1;
    if ( v8 )
    {
      idFile_ASCII::idFile_ASCII(v8);
      goto LABEL_13;
    }
  }
  else
  {
    v10 = (idFile_Permanent *)Memory::Allocate(0x54u);
    LOBYTE(v16) = 2;
    if ( v10 )
    {
      idFile_Permanent::idFile_Permanent(v10);
      goto LABEL_13;
    }
  }
  v9 = 0;
LABEL_13:
  LOBYTE(v16) = 0;
  v11 = v9;
  v12 = idFileSystemLocal::OpenOSFile(this, OSpath.data, "wb", 0);
  *(_DWORD *)(v11 + 76) = v12;
  if ( v12 )
  {
    idStr::operator=((idStr *)(v11 + 4), relativePath);
    len = OSpath.len;
    ASCIIa = OSpath.len;
    if ( OSpath.len + 1 > *(_DWORD *)(v11 + 44) )
      idStr::ReAllocate((idStr *)(v11 + 36), OSpath.len + 1, 0);
    qmemcpy(*(void **)(v11 + 40), OSpath.data, len);
    *(_BYTE *)(ASCIIa + *(_DWORD *)(v11 + 40)) = 0;
    *(_DWORD *)(v11 + 36) = ASCIIa;
    *(_DWORD *)(v11 + 68) = 2;
    *(_BYTE *)(v11 + 80) = 0;
    *(_DWORD *)(v11 + 72) = 0;
    v16 = -1;
    idStr::FreeData(&OSpath);
    return (idFile *)v11;
  }
  else
  {
    (**(void (__thiscall ***)(int, int))v11)(v11, 1);
    v16 = -1;
    idStr::FreeData(&OSpath);
    return 0;
  }
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::OpenExplicitFileRead(char const *)
idFile *__thiscall idFileSystemLocal::OpenExplicitFileRead(idFileSystemLocal *this, char *OSPath)
{
  idFile_Permanent *v3; // eax
  int v4; // eax
  int v5; // esi
  _iobuf *v6; // eax
  _iobuf *v8; // [esp-4h] [ebp-1Ch]

  if ( !this->searchPaths )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idFileSystem::OpenExplicitFileRead: %s\n",
      OSPath);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "idFileSystem::OpenExplicitFileRead - reading from: %s\n",
    OSPath);
  v3 = (idFile_Permanent *)Memory::Allocate(0x54u);
  if ( v3 )
  {
    idFile_Permanent::idFile_Permanent(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  v6 = idFileSystemLocal::OpenOSFile(this, OSPath, "rb", 0);
  *(_DWORD *)(v5 + 76) = v6;
  if ( v6 )
  {
    idStr::operator=((idStr *)(v5 + 4), OSPath);
    idStr::operator=((idStr *)(v5 + 36), OSPath);
    v8 = *(_iobuf **)(v5 + 76);
    *(_DWORD *)(v5 + 68) = 1;
    *(_BYTE *)(v5 + 80) = 0;
    *(_DWORD *)(v5 + 72) = idFileSystemLocal::DirectFileLength(this, v8);
    return (idFile *)v5;
  }
  else
  {
    (**(void (__thiscall ***)(int, int))v5)(v5, 1);
    return 0;
  }
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::OpenExplicitFileWrite(char const *)
idFile *__thiscall idFileSystemLocal::OpenExplicitFileWrite(idFileSystemLocal *this, char *OSPath)
{
  idFile_Permanent *v3; // eax
  int v4; // eax
  int v5; // esi
  _iobuf *v6; // eax

  if ( !this->searchPaths )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idFileSystem::OpenExplicitFileWrite: %s\n",
      OSPath);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(common.type, "writing to: %s\n", OSPath);
  this->CreateOSPath(this, OSPath);
  v3 = (idFile_Permanent *)Memory::Allocate(0x54u);
  if ( v3 )
  {
    idFile_Permanent::idFile_Permanent(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  v6 = idFileSystemLocal::OpenOSFile(this, OSPath, "wb", 0);
  *(_DWORD *)(v5 + 76) = v6;
  if ( v6 )
  {
    idStr::operator=((idStr *)(v5 + 4), OSPath);
    idStr::operator=((idStr *)(v5 + 36), OSPath);
    *(_DWORD *)(v5 + 68) = 2;
    *(_BYTE *)(v5 + 80) = 0;
    *(_DWORD *)(v5 + 72) = 0;
    return (idFile *)v5;
  }
  else
  {
    (**(void (__thiscall ***)(int, int))v5)(v5, 1);
    return 0;
  }
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::OpenFileAppend(char const *,bool,char const *)
idFile *__thiscall idFileSystemLocal::OpenFileAppend(
        idFileSystemLocal *this,
        char *relativePath,
        bool sync,
        const char *basePath)
{
  bool v5; // zf
  const char *value; // eax
  char *v7; // eax
  idFile_Permanent *v8; // eax
  int v9; // eax
  int v10; // ebp
  _iobuf *v11; // eax
  int len; // esi
  _iobuf *v14; // [esp+4h] [ebp-40h]
  idStr OSpath; // [esp+18h] [ebp-2Ch] BYREF
  int v16; // [esp+40h] [ebp-4h]
  const char *basePatha; // [esp+50h] [ebp+Ch]

  OSpath.len = 0;
  OSpath.alloced = 20;
  OSpath.data = OSpath.baseBuffer;
  OSpath.baseBuffer[0] = 0;
  v5 = this->searchPaths == 0;
  v16 = 0;
  if ( v5 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  value = cvarSystem->GetCVarString(cvarSystem, basePath);
  if ( !*value )
    value = idFileSystemLocal::fs_savepath.internalVar->value;
  v7 = (char *)this->BuildOSPath(this, value, this->gameFolder.data, relativePath);
  idStr::operator=(&OSpath, v7);
  this->CreateOSPath(this, OSpath.data);
  if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idFileSystem::OpenFileAppend: %s\n",
      OSpath.data);
  v8 = (idFile_Permanent *)Memory::Allocate(0x54u);
  LOBYTE(v16) = 1;
  if ( v8 )
  {
    idFile_Permanent::idFile_Permanent(v8);
    v10 = v9;
  }
  else
  {
    v10 = 0;
  }
  LOBYTE(v16) = 0;
  v11 = idFileSystemLocal::OpenOSFile(this, OSpath.data, "ab", 0);
  *(_DWORD *)(v10 + 76) = v11;
  if ( v11 )
  {
    idStr::operator=((idStr *)(v10 + 4), relativePath);
    len = OSpath.len;
    basePatha = (const char *)OSpath.len;
    if ( OSpath.len + 1 > *(_DWORD *)(v10 + 44) )
      idStr::ReAllocate((idStr *)(v10 + 36), OSpath.len + 1, 0);
    qmemcpy(*(void **)(v10 + 40), OSpath.data, len);
    basePatha[*(_DWORD *)(v10 + 40)] = 0;
    *(_DWORD *)(v10 + 36) = basePatha;
    v14 = *(_iobuf **)(v10 + 76);
    *(_DWORD *)(v10 + 68) = 6;
    *(_BYTE *)(v10 + 80) = sync;
    *(_DWORD *)(v10 + 72) = idFileSystemLocal::DirectFileLength(this, v14);
    v16 = -1;
    idStr::FreeData(&OSpath);
    return (idFile *)v10;
  }
  else
  {
    (**(void (__thiscall ***)(int, int))v10)(v10, 1);
    v16 = -1;
    idStr::FreeData(&OSpath);
    return 0;
  }
}

// FUNC: public: virtual class idFile * __thiscall idFileSystemLocal::OpenImportFileRead(char const *)
idFile *__thiscall idFileSystemLocal::OpenImportFileRead(idFileSystemLocal *this, const char *filename)
{
  bool v3; // zf
  idFile_Permanent *v4; // eax
  int v5; // eax
  int v6; // ebp
  _iobuf *v7; // eax
  int len; // esi
  int v10; // esi
  _iobuf *v11; // [esp-4h] [ebp-44h]
  idStr finalName; // [esp+14h] [ebp-2Ch] BYREF
  int v14; // [esp+3Ch] [ebp-4h]
  const char *filenamea; // [esp+44h] [ebp+4h]
  const char *filenameb; // [esp+44h] [ebp+4h]

  finalName.len = 0;
  finalName.alloced = 20;
  finalName.data = finalName.baseBuffer;
  finalName.baseBuffer[0] = 0;
  v3 = this->searchPaths == 0;
  v14 = 0;
  if ( v3 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idFileSystemLocal::OpenImportFileRead: %s\n",
      filename);
  idStr::AppendPath(&finalName, idFileSystemLocal::fs_importpath.internalVar->value);
  idStr::AppendPath(&finalName, filename);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "reading from: %s\n",
    finalName.data);
  v4 = (idFile_Permanent *)Memory::Allocate(0x54u);
  LOBYTE(v14) = 1;
  if ( v4 )
  {
    idFile_Permanent::idFile_Permanent(v4);
    v6 = v5;
  }
  else
  {
    v6 = 0;
  }
  LOBYTE(v14) = 0;
  v7 = idFileSystemLocal::OpenOSFile(this, finalName.data, "rb", 0);
  *(_DWORD *)(v6 + 76) = v7;
  if ( v7 )
  {
    len = finalName.len;
    filenamea = (const char *)finalName.len;
    if ( finalName.len + 1 > *(_DWORD *)(v6 + 12) )
      idStr::ReAllocate((idStr *)(v6 + 4), finalName.len + 1, 0);
    qmemcpy(*(void **)(v6 + 8), finalName.data, len);
    filenamea[*(_DWORD *)(v6 + 8)] = 0;
    *(_DWORD *)(v6 + 4) = filenamea;
    v10 = finalName.len;
    filenameb = (const char *)finalName.len;
    if ( finalName.len + 1 > *(_DWORD *)(v6 + 44) )
      idStr::ReAllocate((idStr *)(v6 + 36), finalName.len + 1, 0);
    qmemcpy(*(void **)(v6 + 40), finalName.data, v10);
    filenameb[*(_DWORD *)(v6 + 40)] = 0;
    *(_DWORD *)(v6 + 36) = filenameb;
    v11 = *(_iobuf **)(v6 + 76);
    *(_DWORD *)(v6 + 68) = 1;
    *(_BYTE *)(v6 + 80) = 0;
    *(_DWORD *)(v6 + 72) = idFileSystemLocal::DirectFileLength(this, v11);
    v14 = -1;
    idStr::FreeData(&finalName);
    return (idFile *)v6;
  }
  else
  {
    (**(void (__thiscall ***)(int, int))v6)(v6, 1);
    v14 = -1;
    idStr::FreeData(&finalName);
    return 0;
  }
}

// FUNC: public: virtual int __thiscall idFileSystemLocal::ReadDemoHeader(class idFile *)
int __thiscall idFileSystemLocal::ReadDemoHeader(idFileSystemLocal *this, idFile *file)
{
  idFile_vtbl *v3; // eax
  int v4; // edi
  int *v5; // eax
  idStr *v6; // esi
  idStr *v7; // eax
  char **p_data; // ebp
  unsigned int v9; // ebx
  bool v10; // zf
  int v11; // ecx
  int v12; // esi
  int *v13; // eax
  idStr *v14; // edi
  idStr *v15; // eax
  char **v16; // ebp
  unsigned int v17; // ebx
  int v18; // eax
  int len; // ebx
  idStr *v20; // ebp
  int *v21; // esi
  bool v22; // cc
  idFile_vtbl *v23; // edx
  int v24; // edi
  int *v25; // ebp
  char **v26; // esi
  int v27; // ecx
  int gameDLLChecksum; // eax
  int result; // eax
  idFileSystemLocal *v30; // esi
  int v31; // edi
  int v32; // ecx
  int *v33; // eax
  int *v34; // ebx
  const char *v35; // eax
  const char *v36; // esi
  int v37; // edi
  char v38; // cl
  int j; // eax
  char *v40; // edx
  int pakNames; // [esp+20h] [ebp-578h]
  int pakNames_4; // [esp+24h] [ebp-574h]
  idStr *pakNames_12; // [esp+2Ch] [ebp-56Ch]
  int i; // [esp+30h] [ebp-568h]
  int ia; // [esp+30h] [ebp-568h]
  int ptr; // [esp+34h] [ebp-564h]
  unsigned int *ptra; // [esp+34h] [ebp-564h]
  int v48; // [esp+38h] [ebp-560h]
  unsigned int *v49; // [esp+38h] [ebp-560h]
  int numPaks; // [esp+3Ch] [ebp-55Ch] BYREF
  int v51; // [esp+40h] [ebp-558h]
  int missingGamePakChecksum; // [esp+44h] [ebp-554h] BYREF
  int *v53; // [esp+48h] [ebp-550h]
  idStr checksums; // [esp+4Ch] [ebp-54Ch] BYREF
  idFileSystemLocal *v55; // [esp+6Ch] [ebp-52Ch]
  int *v56; // [esp+70h] [ebp-528h]
  idStr l_fs_game_base; // [esp+74h] [ebp-524h] BYREF
  idStr l_fs_game; // [esp+94h] [ebp-504h] BYREF
  int gamePakChecksums[6]; // [esp+B4h] [ebp-4E4h] BYREF
  idStr gamePakNames[6]; // [esp+CCh] [ebp-4CCh] BYREF
  int pakChecksums[128]; // [esp+18Ch] [ebp-40Ch] BYREF
  int missingChecksums[128]; // [esp+38Ch] [ebp-20Ch] BYREF
  int v63; // [esp+594h] [ebp-4h]

  v55 = this;
  l_fs_game.len = 0;
  l_fs_game.alloced = 20;
  l_fs_game.data = l_fs_game.baseBuffer;
  l_fs_game.baseBuffer[0] = 0;
  v63 = 2;
  l_fs_game_base.len = 0;
  l_fs_game_base.alloced = 20;
  l_fs_game_base.data = l_fs_game_base.baseBuffer;
  l_fs_game_base.baseBuffer[0] = 0;
  numPaks = 0;
  pakNames_12 = 0;
  pakNames = 0;
  pakNames_4 = 0;
  `eh vector constructor iterator'(
    gamePakNames,
    0x20u,
    6,
    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  v3 = file->__vftable;
  LOBYTE(v63) = 3;
  v3->ReadString(file, &l_fs_game_base);
  file->ReadString(file, &l_fs_game);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "fs_game_base: '%s'\n",
    l_fs_game_base.data);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "fs_game: '%s'\n",
    l_fs_game.data);
  file->ReadInt(file, &numPaks);
  if ( numPaks )
  {
    checksums.len = 0;
    checksums.alloced = 20;
    checksums.data = checksums.baseBuffer;
    checksums.baseBuffer[0] = 0;
    LOBYTE(v63) = 4;
    i = 0;
    if ( numPaks > 0 )
    {
      v56 = pakChecksums;
      do
      {
        file->ReadString(file, &checksums);
        if ( !pakNames_12 && pakNames_4 != 16 )
        {
          v4 = pakNames;
          pakNames_4 = 16;
          if ( pakNames > 16 )
          {
            v4 = 16;
            pakNames = 16;
          }
          v5 = (int *)Memory::Allocate(0x204u);
          v53 = v5;
          LOBYTE(v63) = 5;
          if ( v5 )
          {
            v6 = (idStr *)(v5 + 1);
            *v5 = 16;
            `eh vector constructor iterator'(
              v5 + 1,
              0x20u,
              16,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            v7 = v6;
          }
          else
          {
            v7 = 0;
          }
          LOBYTE(v63) = 4;
          pakNames_12 = v7;
          if ( v4 > 0 )
          {
            v51 = -4 - (_DWORD)v7;
            ptr = 4;
            p_data = &v7->data;
            v48 = pakNames;
            do
            {
              v9 = *(unsigned int *)((char *)p_data + v51);
              if ( (int)(v9 + 1) > (int)p_data[1] )
                idStr::ReAllocate((idStr *)(p_data - 1), v9 + 1, 0);
              qmemcpy(*p_data, *(const void **)ptr, v9);
              (*p_data)[v9] = 0;
              *(p_data - 1) = (char *)v9;
              p_data += 8;
              v10 = v48-- == 1;
              ptr += 32;
            }
            while ( !v10 );
          }
        }
        if ( pakNames == pakNames_4 )
        {
          v11 = (pakNames_4 + 16) % 16;
          v12 = pakNames_4 + 16 - v11;
          if ( v12 > 0 )
          {
            if ( v12 != pakNames_4 )
            {
              ptra = (unsigned int *)pakNames_12;
              pakNames_4 = pakNames_4 + 16 - v11;
              if ( v12 < pakNames )
                pakNames = v12;
              v13 = (int *)Memory::Allocate(32 * v12 + 4);
              v53 = v13;
              LOBYTE(v63) = 6;
              if ( v13 )
              {
                v14 = (idStr *)(v13 + 1);
                *v13 = v12;
                `eh vector constructor iterator'(
                  v13 + 1,
                  0x20u,
                  v12,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                v15 = v14;
              }
              else
              {
                v15 = 0;
              }
              LOBYTE(v63) = 4;
              pakNames_12 = v15;
              if ( pakNames > 0 )
              {
                v49 = ptra;
                v16 = &v15->data;
                v53 = (int *)((char *)ptra - (char *)v15);
                v51 = pakNames;
                do
                {
                  v17 = *v49;
                  v18 = *v49 + 1;
                  if ( v18 > (int)v16[1] )
                    idStr::ReAllocate((idStr *)(v16 - 1), v18, 0);
                  v49 += 8;
                  qmemcpy(*v16, *(const void **)((char *)v16 + (_DWORD)v53), v17);
                  (*v16)[v17] = 0;
                  *(v16 - 1) = (char *)v17;
                  v16 += 8;
                  --v51;
                }
                while ( v51 );
              }
              if ( ptra )
              {
                `eh vector destructor iterator'(
                  ptra,
                  0x20u,
                  *(ptra - 1),
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(ptra - 1);
              }
            }
          }
          else
          {
            if ( pakNames_12 )
            {
              `eh vector destructor iterator'(
                pakNames_12,
                0x20u,
                *(_DWORD *)&pakNames_12[-1].baseBuffer[16],
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(&pakNames_12[-1].baseBuffer[16]);
            }
            pakNames_12 = 0;
            pakNames = 0;
            pakNames_4 = 0;
          }
        }
        len = checksums.len;
        v20 = &pakNames_12[pakNames];
        if ( checksums.len + 1 > v20->alloced )
          idStr::ReAllocate(&pakNames_12[pakNames], checksums.len + 1, 0);
        ++pakNames;
        qmemcpy(v20->data, checksums.data, len);
        v21 = v56;
        v20->data[len] = 0;
        v20->len = len;
        file->ReadInt(file, v21);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
          common.type,
          "pak '%s' 0x%x\n",
          checksums.data,
          *v21);
        v22 = ++i < numPaks;
        v56 = v21 + 1;
      }
      while ( v22 );
    }
    v23 = file->__vftable;
    v24 = 0;
    pakChecksums[i] = 0;
    v23->ReadInt(file, &missingGamePakChecksum);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "record on an OS id: %d, local playback on OS id %d\n",
      missingGamePakChecksum,
      0);
    v25 = gamePakChecksums;
    v26 = &gamePakNames[0].data;
    do
    {
      file->ReadString(file, (idStr *)(v26 - 1));
      file->ReadInt(file, v25);
      if ( *v25 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
          common.type,
          "game pak OS %d: '%s' 0x%x\n",
          v24,
          *v26,
          *v25);
      ++v24;
      v26 += 8;
      ++v25;
    }
    while ( v24 < 6 );
    LOBYTE(v63) = 3;
    idStr::FreeData(&checksums);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "demo wasn't recorded in pure mode\n");
  }
  if ( idStr::Icmp(l_fs_game_base.data, idFileSystemLocal::fs_game_base.internalVar->value)
    || idStr::Icmp(l_fs_game.data, idFileSystemLocal::fs_game.internalVar->value) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "fs_game_base '%s' or fs_game '%s' are not matching the current configuration ( '%s' '%s' )",
      l_fs_game_base.data,
      l_fs_game.data,
      idFileSystemLocal::fs_game_base.internalVar->value,
      idFileSystemLocal::fs_game.internalVar->value);
    v10 = !cvarSystem->GetCVarBool(cvarSystem, "demo_enforceFS");
    v27 = *(_DWORD *)common.type;
    if ( !v10 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(v27 + 124))(
        common.type,
        "demo_enforceFS is enabled, need to reload engine before demo playback\n");
      idFileSystemLocal::fs_game_base.internalVar->InternalSetString(
        idFileSystemLocal::fs_game_base.internalVar,
        l_fs_game_base.data);
      idFileSystemLocal::fs_game.internalVar->InternalSetString(idFileSystemLocal::fs_game.internalVar, l_fs_game.data);
      if ( numPaks )
      {
        gameDLLChecksum = gamePakChecksums[0];
        if ( !gamePakChecksums[0] )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
            common.type,
            "no game pak for this OS was present at recording");
          gameDLLChecksum = v55->gameDLLChecksum;
        }
        fileSystem->SetRestartChecksums(fileSystem, pakChecksums, gameDLLChecksum);
      }
      LOBYTE(v63) = 2;
      `eh vector destructor iterator'(
        gamePakNames,
        0x20u,
        6,
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      LOBYTE(v63) = 1;
      if ( pakNames_12 )
      {
        `eh vector destructor iterator'(
          pakNames_12,
          0x20u,
          *(_DWORD *)&pakNames_12[-1].baseBuffer[16],
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        Memory::Free(&pakNames_12[-1].baseBuffer[16]);
      }
LABEL_52:
      LOBYTE(v63) = 0;
      idStr::FreeData(&l_fs_game_base);
      v63 = -1;
      idStr::FreeData(&l_fs_game);
      return -1;
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(v27 + 124))(
      common.type,
      "demo_enforceFS is off, demo might crash or generally not playback correctly\n");
  }
  if ( numPaks )
  {
    v30 = v55;
    v55->UpdateGamePakChecksums(v55);
    v31 = gamePakChecksums[0];
    if ( !gamePakChecksums[0] )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "no game pak for this OS was present at recording");
      v31 = v30->gameDLLChecksum;
    }
    switch ( v30->SetPureServerChecksums(v30, pakChecksums, v31, missingChecksums, &missingGamePakChecksum) )
    {
      case PURE_OK:
        if ( !cvarSystem->GetCVarBool(cvarSystem, "demo_enforceFS") )
          v30->ClearPureChecksums(v30);
        goto LABEL_86;
      case PURE_RESTART:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
          common.type,
          "a filesystem restart is needed to playback this demo");
        v10 = !cvarSystem->GetCVarBool(cvarSystem, "demo_enforceFS");
        v32 = *(_DWORD *)common.type;
        if ( v10 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(v32 + 124))(
            common.type,
            "demo_enforceFS is off, demo might crash or generally not playback correctly\n");
          goto LABEL_86;
        }
        (*(void (__cdecl **)(netadrtype_t, const char *))(v32 + 124))(
          common.type,
          "demo_enforceFS is enabled, need to reload engine before demo playback\n");
        fileSystem->SetRestartChecksums(fileSystem, pakChecksums, v31);
        LOBYTE(v63) = 2;
        `eh vector destructor iterator'(
          gamePakNames,
          0x20u,
          6,
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        LOBYTE(v63) = 1;
        if ( pakNames_12 )
        {
          `eh vector destructor iterator'(
            pakNames_12,
            0x20u,
            *(_DWORD *)&pakNames_12[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(&pakNames_12[-1].baseBuffer[16]);
        }
        goto LABEL_52;
      case PURE_MISSING:
        checksums.len = 0;
        checksums.alloced = 20;
        checksums.data = checksums.baseBuffer;
        checksums.baseBuffer[0] = 0;
        LOBYTE(v63) = 7;
        ia = 0;
        if ( missingChecksums[0] )
        {
          v33 = missingChecksums;
          v34 = missingChecksums;
          do
          {
            v35 = va("0x%x ", *v33);
            v36 = v35;
            if ( v35 )
            {
              v37 = strlen(v35) + checksums.len;
              if ( v37 + 1 > checksums.alloced )
                idStr::ReAllocate(&checksums, v37 + 1, 1);
              v38 = *v36;
              for ( j = 0; v38; v38 = v36[j] )
              {
                v40 = &checksums.data[j++];
                v40[checksums.len] = v38;
              }
              checksums.len = v37;
              checksums.data[v37] = 0;
            }
            ++ia;
            v33 = ++v34;
          }
          while ( *v34 );
        }
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "missing %d pak files from initial demo recording: %s",
          ia,
          checksums.data);
        if ( missingGamePakChecksum )
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
            common.type,
            "can't match the game code used to record this demo");
        if ( !cvarSystem->GetCVarBool(cvarSystem, "demo_enforceFS") )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "demo_enforceFS is off, demo might crash or generally not playback correctly\n");
          LOBYTE(v63) = 3;
          idStr::FreeData(&checksums);
          goto LABEL_86;
        }
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "demo_enforceFS is enabled, aborting playback\n");
        LOBYTE(v63) = 3;
        idStr::FreeData(&checksums);
        LOBYTE(v63) = 2;
        `eh vector destructor iterator'(
          gamePakNames,
          0x20u,
          6,
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        LOBYTE(v63) = 1;
        if ( pakNames_12 )
        {
          `eh vector destructor iterator'(
            pakNames_12,
            0x20u,
            *(_DWORD *)&pakNames_12[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(&pakNames_12[-1].baseBuffer[16]);
        }
        goto LABEL_77;
      case PURE_NODLL:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
          common.type,
          "can't match the game code used to record this demo");
        if ( !cvarSystem->GetCVarBool(cvarSystem, "demo_enforceFS") )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "demo_enforceFS is off, demo might crash or generally not playback correctly\n");
          goto LABEL_86;
        }
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "demo_enforceFS is enabled, aborting playback\n");
        LOBYTE(v63) = 2;
        `eh vector destructor iterator'(
          gamePakNames,
          0x20u,
          6,
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        LOBYTE(v63) = 1;
        if ( pakNames_12 )
        {
          `eh vector destructor iterator'(
            pakNames_12,
            0x20u,
            *(_DWORD *)&pakNames_12[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(&pakNames_12[-1].baseBuffer[16]);
        }
LABEL_77:
        LOBYTE(v63) = 0;
        idStr::FreeData(&l_fs_game_base);
        v63 = -1;
        idStr::FreeData(&l_fs_game);
        result = 0;
        break;
      default:
        goto LABEL_86;
    }
  }
  else
  {
LABEL_86:
    LOBYTE(v63) = 2;
    `eh vector destructor iterator'(
      gamePakNames,
      0x20u,
      6,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    LOBYTE(v63) = 1;
    if ( pakNames_12 )
    {
      `eh vector destructor iterator'(
        pakNames_12,
        0x20u,
        *(_DWORD *)&pakNames_12[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(&pakNames_12[-1].baseBuffer[16]);
    }
    LOBYTE(v63) = 0;
    idStr::FreeData(&l_fs_game_base);
    v63 = -1;
    idStr::FreeData(&l_fs_game);
    return 1;
  }
  return result;
}

// FUNC: public: virtual int __thiscall idFileSystemLocal::WriteFile(char const *,void const *,int,char const *)
int __thiscall idFileSystemLocal::WriteFile(
        idFileSystemLocal *this,
        char *relativePath,
        const void *buffer,
        int size,
        const char *basePath)
{
  idFile *v6; // esi
  int v8; // ebx

  if ( !this->searchPaths )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Filesystem call made without initialization\n");
  if ( !relativePath || !buffer )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFileSystemLocal::WriteFile: NULL parameter");
  v6 = idFileSystemLocal::OpenFileWrite(this, relativePath, basePath, 0);
  if ( v6 )
  {
    v8 = v6->Write(v6, buffer, size);
    this->CloseFile(this, v6);
    return v8;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Failed to open %s\n",
      relativePath);
    return -1;
  }
}

// FUNC: public: virtual class idFileList * __thiscall idFileSystemLocal::ListFiles(char const *,char const *,bool,bool,char const *)
idFileList *__thiscall idFileSystemLocal::ListFiles(
        idFileSystemLocal *this,
        char *relativePath,
        const char *extension,
        bool sort,
        bool fullRelativePath,
        const char *gamedir)
{
  idStr *v7; // eax
  idStr *v8; // ebx
  idList<idStr> *v9; // ebx
  unsigned int num; // edi
  bool v11; // cc
  _DWORD *v12; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // edi
  char *v16; // ebp
  int *v17; // eax
  int v18; // eax
  int v19; // esi
  int *v20; // eax
  char *v21; // edi
  char *v22; // eax
  const char *v23; // edi
  char *v24; // ebp
  unsigned int v25; // esi
  int v26; // eax
  char *v27; // ebp
  int v28; // edi
  unsigned int v29; // esi
  int v30; // eax
  idStr *list; // edi
  char *v32; // esi
  idStr *v34; // [esp+14h] [ebp-5Ch]
  int v35; // [esp+18h] [ebp-58h]
  int v36; // [esp+1Ch] [ebp-54h]
  int granularity; // [esp+20h] [ebp-50h]
  char *v38; // [esp+24h] [ebp-4Ch]
  _DWORD *ptr; // [esp+34h] [ebp-3Ch]
  idList<idStr> extensionList; // [esp+38h] [ebp-38h] BYREF
  idHashIndex hashIndex; // [esp+48h] [ebp-28h] BYREF
  int v42; // [esp+6Ch] [ebp-4h]
  const char *relativePatha; // [esp+74h] [ebp+4h]
  const char *relativePathb; // [esp+74h] [ebp+4h]
  const char *extensiona; // [esp+78h] [ebp+8h]
  unsigned int *sorta; // [esp+7Ch] [ebp+Ch]
  int sortb; // [esp+7Ch] [ebp+Ch]
  unsigned int fullRelativePatha; // [esp+80h] [ebp+10h]
  const char *gamedira; // [esp+84h] [ebp+14h]

  idHashIndex::Init(&hashIndex, 4096, 4096);
  v42 = 1;
  extensionList.granularity = 16;
  extensionList.list = 0;
  extensionList.num = 0;
  extensionList.size = 0;
  v7 = (idStr *)Memory::Allocate(0x30u);
  if ( v7 )
  {
    v7->len = 0;
    v7->alloced = 20;
    v7->data = v7->baseBuffer;
    v7->baseBuffer[0] = 0;
    v7[1].alloced = 16;
    v8 = v7;
    *(_DWORD *)v7[1].baseBuffer = 0;
    v7[1].len = 0;
    v7[1].data = 0;
    v34 = v7;
  }
  else
  {
    v34 = 0;
    v8 = 0;
  }
  LOBYTE(v42) = 1;
  idStr::operator=(v8, relativePath);
  idFileSystemLocal::GetExtensionList(this, extension, &extensionList);
  v9 = (idList<idStr> *)&v8[1];
  idFileSystemLocal::GetFileList(this, relativePath, &extensionList, v9, &hashIndex, fullRelativePath, gamedir);
  if ( sort )
  {
    num = v9->num;
    v11 = v9->num <= 0;
    if ( v9->num )
    {
      LOBYTE(v42) = 5;
      if ( v11 )
      {
        v12 = 0;
        ptr = 0;
      }
      else
      {
        ptr = Memory::Allocate(4 * num);
        v12 = ptr;
      }
      v13 = 0;
      if ( v9->num > 0 )
      {
        v14 = 0;
        do
          v12[v13++] = &v9->list[v14++];
        while ( v13 < v9->num );
      }
      if ( v12 )
        qsort(v12, num, 4u, (int (__cdecl *)(const void *, const void *))idListSortComparePaths<idStr *>);
      v15 = v9->num;
      if ( v9->num > 0 )
      {
        v36 = v9->num;
        v17 = (int *)Memory::Allocate(32 * v15 + 4);
        LOBYTE(v42) = 6;
        if ( v17 )
        {
          v16 = (char *)(v17 + 1);
          *v17 = v15;
          `eh vector constructor iterator'(
            v17 + 1,
            0x20u,
            v15,
            (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        }
        else
        {
          v16 = 0;
        }
        LOBYTE(v42) = 5;
        v38 = v16;
      }
      else
      {
        v16 = 0;
        v38 = 0;
        v36 = 0;
      }
      v35 = v15;
      granularity = v9->granularity;
      if ( v16 )
      {
        v18 = v9->granularity;
        v19 = v18 + v15 - 1 - (v18 + v15 - 1) % granularity;
        if ( v19 != v36 )
        {
          if ( v19 > 0 )
          {
            extensiona = v16;
            v36 = v18 + v15 - 1 - (v18 + v15 - 1) % granularity;
            if ( v19 < v15 )
              v35 = v18 + v15 - 1 - (v18 + v15 - 1) % granularity;
            v20 = (int *)Memory::Allocate(32 * v19 + 4);
            LOBYTE(v42) = 7;
            if ( v20 )
            {
              v21 = (char *)(v20 + 1);
              *v20 = v19;
              `eh vector constructor iterator'(
                v20 + 1,
                0x20u,
                v19,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              v22 = v21;
            }
            else
            {
              v22 = 0;
            }
            LOBYTE(v42) = 5;
            v38 = v22;
            if ( v35 > 0 )
            {
              v23 = (const char *)(v16 - v22);
              sorta = (unsigned int *)v16;
              v24 = v22 + 4;
              gamedira = (const char *)(extensiona - v22);
              relativePatha = (const char *)v35;
              while ( 1 )
              {
                v25 = *sorta;
                v26 = *sorta + 1;
                fullRelativePatha = *sorta;
                if ( v26 > *((_DWORD *)v24 + 1) )
                  idStr::ReAllocate((idStr *)(v24 - 4), v26, 0);
                sorta += 8;
                qmemcpy(*(void **)v24, *(const void **)&v24[(_DWORD)v23], v25);
                *(_BYTE *)(fullRelativePatha + *(_DWORD *)v24) = 0;
                *((_DWORD *)v24 - 1) = fullRelativePatha;
                v24 += 32;
                if ( !--relativePatha )
                  break;
                v23 = gamedira;
              }
              v16 = (char *)extensiona;
            }
            `eh vector destructor iterator'(
              v16,
              0x20u,
              *((_DWORD *)v16 - 1),
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(v16 - 4);
          }
          else
          {
            `eh vector destructor iterator'(
              v16,
              0x20u,
              *((_DWORD *)v16 - 1),
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(v16 - 4);
            v38 = 0;
            v35 = 0;
            v36 = 0;
          }
          v16 = v38;
        }
      }
      sortb = 0;
      if ( v35 > 0 )
      {
        v27 = v16 + 4;
        do
        {
          v28 = ptr[sortb];
          v29 = *(_DWORD *)v28;
          v30 = *(_DWORD *)v28 + 1;
          relativePathb = *(const char **)v28;
          if ( v30 > *((_DWORD *)v27 + 1) )
            idStr::ReAllocate((idStr *)(v27 - 4), v30, 0);
          qmemcpy(*(void **)v27, *(const void **)(v28 + 4), v29);
          relativePathb[*(_DWORD *)v27] = 0;
          *((_DWORD *)v27 - 1) = relativePathb;
          v27 += 32;
          ++sortb;
        }
        while ( sortb < v35 );
        v16 = v38;
      }
      v9->num = v35;
      v9->size = v36;
      v9->granularity = granularity;
      list = v9->list;
      v9->list = (idStr *)v16;
      LOBYTE(v42) = 4;
      if ( ptr )
        Memory::Free(ptr);
      LOBYTE(v42) = 1;
      if ( list )
      {
        `eh vector destructor iterator'(
          list,
          0x20u,
          *(_DWORD *)&list[-1].baseBuffer[16],
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        Memory::Free(&list[-1].baseBuffer[16]);
      }
    }
  }
  LOBYTE(v42) = 0;
  if ( extensionList.list )
  {
    v32 = &extensionList.list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      extensionList.list,
      0x20u,
      *(_DWORD *)&extensionList.list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v32);
  }
  v42 = -1;
  idHashIndex::Free(&hashIndex);
  return (idFileList *)v34;
}

// FUNC: public: virtual class idModList * __thiscall idFileSystemLocal::ListMods(void)
idModList *__thiscall idFileSystemLocal::ListMods(idFileSystemLocal *this)
{
  int *v2; // eax
  int *v3; // ebp
  int v4; // eax
  char v5; // cl
  int v6; // esi
  int v7; // ebx
  idStr *v8; // ebx
  int v9; // eax
  char v10; // cl
  int v11; // esi
  int v12; // edi
  idStr *v13; // ebx
  int v14; // eax
  char v15; // cl
  int v16; // esi
  int v17; // edi
  idStr *v18; // ebx
  const char *v19; // esi
  unsigned int v20; // eax
  int v21; // ebx
  int v22; // eax
  char *data; // edx
  const char *v24; // ecx
  char v25; // al
  int v26; // eax
  char v27; // cl
  int v28; // esi
  int v29; // edi
  idStr *v30; // ebx
  int v31; // esi
  bool v32; // cc
  int *v33; // eax
  _DWORD *v34; // edi
  idStr *v35; // ebx
  const void *v36; // esi
  int v37; // ebx
  int v38; // edi
  int v39; // esi
  char *v40; // eax
  char *v41; // esi
  int *v42; // eax
  _DWORD *v43; // edi
  idStr *v44; // ebx
  const void *v45; // esi
  idStr *v46; // esi
  unsigned int v47; // edi
  idStr *v48; // ebx
  int v49; // eax
  int v50; // esi
  _DWORD *v51; // eax
  int v52; // ecx
  int v53; // edx
  int v54; // edi
  unsigned int *v55; // ecx
  int v56; // ebx
  int *v57; // eax
  unsigned int *v58; // esi
  int v59; // eax
  int v60; // esi
  char *v61; // esi
  int *v62; // eax
  char *v63; // edi
  char *v64; // eax
  char *v65; // ebx
  int v66; // ebx
  int v67; // esi
  unsigned int v68; // edi
  int v69; // eax
  char *v70; // eax
  char *v71; // ecx
  int alloced; // edx
  char *v73; // eax
  int v74; // eax
  char *v75; // esi
  int v76; // esi
  const char *v77; // ebx
  unsigned int v78; // eax
  int v79; // eax
  char *v80; // edx
  const char *v81; // ecx
  char v82; // al
  _iobuf *v83; // eax
  int v84; // kr00_4
  char *v85; // edx
  char *v86; // ecx
  char v87; // al
  bool v88; // zf
  int v89; // esi
  int *v90; // eax
  _DWORD *v91; // ebx
  unsigned int *v92; // eax
  idStr *v93; // ebx
  const void *v94; // esi
  int v95; // edi
  int v96; // eax
  int v97; // esi
  char *v98; // eax
  char *v99; // esi
  int *v100; // eax
  _DWORD *v101; // edi
  idStr *v102; // ebx
  const void *v103; // esi
  idStr *v104; // ebx
  int v105; // esi
  int v106; // esi
  int *v107; // eax
  _DWORD *v108; // edi
  idStr *v109; // ebx
  const void *v110; // esi
  int v111; // edi
  int v112; // eax
  int v113; // esi
  char *v114; // eax
  char *v115; // esi
  int *v116; // eax
  _DWORD *v117; // edi
  idStr *v118; // ebx
  const void *v119; // esi
  unsigned int v120; // esi
  idStr *v121; // ebx
  int v122; // eax
  int v123; // esi
  int *v124; // eax
  _DWORD *v125; // edi
  idStr *v126; // ebx
  const void *v127; // esi
  int v128; // edi
  int v129; // eax
  int v130; // esi
  char *v131; // eax
  char *v132; // esi
  int *v133; // eax
  _DWORD *v134; // edi
  idStr *v135; // ebx
  const void *v136; // esi
  unsigned int v137; // esi
  idStr *v138; // ebx
  int v139; // eax
  const char *v140; // eax
  int v141; // eax
  char v142; // cl
  int v143; // esi
  int *v144; // eax
  _DWORD *v145; // edi
  idStr *v146; // ebx
  const void *v147; // esi
  char *v148; // ebx
  int v149; // edi
  int v150; // esi
  char *v151; // eax
  char *v152; // esi
  int *v153; // eax
  _DWORD *v154; // edi
  idStr *v155; // ebx
  const void *v156; // esi
  int v157; // eax
  idStr *v158; // ebx
  int v159; // eax
  idStr *v160; // ebx
  unsigned int v161; // esi
  int v162; // eax
  int v163; // eax
  char v164; // cl
  int v165; // esi
  int *v166; // eax
  _DWORD *v167; // edi
  idStr *v168; // ebx
  const void *v169; // esi
  int v170; // edi
  int v171; // eax
  int v172; // esi
  char *v173; // eax
  char *v174; // esi
  int *v175; // eax
  _DWORD *v176; // edi
  idStr *v177; // ebx
  const void *v178; // esi
  int v179; // ecx
  int v180; // eax
  int v181; // ebx
  idStr *v182; // ebx
  idStr *v183; // ebx
  int v184; // esi
  char *v185; // esi
  char *v186; // esi
  char *value; // [esp+4h] [ebp-1ACh]
  int v189; // [esp+24h] [ebp-18Ch]
  int v190; // [esp+24h] [ebp-18Ch]
  int v191; // [esp+24h] [ebp-18Ch]
  int v192; // [esp+24h] [ebp-18Ch]
  unsigned int *v193; // [esp+24h] [ebp-18Ch]
  int v194; // [esp+24h] [ebp-18Ch]
  unsigned int *j; // [esp+24h] [ebp-18Ch]
  int v196; // [esp+24h] [ebp-18Ch]
  unsigned int *v197; // [esp+24h] [ebp-18Ch]
  int v198; // [esp+24h] [ebp-18Ch]
  unsigned int *v199; // [esp+24h] [ebp-18Ch]
  int v200; // [esp+24h] [ebp-18Ch]
  unsigned int *v201; // [esp+24h] [ebp-18Ch]
  int v202; // [esp+24h] [ebp-18Ch]
  int v203; // [esp+24h] [ebp-18Ch]
  unsigned int *v204; // [esp+24h] [ebp-18Ch]
  int v205; // [esp+24h] [ebp-18Ch]
  int v206; // [esp+24h] [ebp-18Ch]
  idStr *v207; // [esp+28h] [ebp-188h]
  int v208; // [esp+28h] [ebp-188h]
  unsigned int v209; // [esp+28h] [ebp-188h]
  unsigned int v210; // [esp+28h] [ebp-188h]
  int v211; // [esp+28h] [ebp-188h]
  unsigned int v212; // [esp+28h] [ebp-188h]
  unsigned int v213; // [esp+28h] [ebp-188h]
  int v214; // [esp+28h] [ebp-188h]
  unsigned int v215; // [esp+28h] [ebp-188h]
  unsigned int v216; // [esp+28h] [ebp-188h]
  int v217; // [esp+28h] [ebp-188h]
  unsigned int v218; // [esp+28h] [ebp-188h]
  unsigned int v219; // [esp+28h] [ebp-188h]
  int v220; // [esp+28h] [ebp-188h]
  unsigned int v221; // [esp+28h] [ebp-188h]
  unsigned int v222; // [esp+28h] [ebp-188h]
  unsigned int v223; // [esp+28h] [ebp-188h]
  unsigned int v224; // [esp+28h] [ebp-188h]
  unsigned int v225; // [esp+28h] [ebp-188h]
  unsigned int v226; // [esp+28h] [ebp-188h]
  int v227; // [esp+28h] [ebp-188h]
  char *ptr; // [esp+2Ch] [ebp-184h]
  char *ptra; // [esp+2Ch] [ebp-184h]
  char *ptrb; // [esp+2Ch] [ebp-184h]
  char *ptrc; // [esp+2Ch] [ebp-184h]
  char *ptrd; // [esp+2Ch] [ebp-184h]
  char *ptre; // [esp+2Ch] [ebp-184h]
  unsigned int *ptrf; // [esp+2Ch] [ebp-184h]
  char *ptrg; // [esp+2Ch] [ebp-184h]
  char *ptrh; // [esp+2Ch] [ebp-184h]
  char *ptri; // [esp+2Ch] [ebp-184h]
  char *ptrj; // [esp+2Ch] [ebp-184h]
  char *ptrk; // [esp+2Ch] [ebp-184h]
  int len; // [esp+30h] [ebp-180h]
  int v241; // [esp+30h] [ebp-180h]
  int v242; // [esp+30h] [ebp-180h]
  int v243; // [esp+30h] [ebp-180h]
  unsigned int v244; // [esp+30h] [ebp-180h]
  int v245; // [esp+30h] [ebp-180h]
  int v246; // [esp+30h] [ebp-180h]
  int v247; // [esp+30h] [ebp-180h]
  int v248; // [esp+30h] [ebp-180h]
  int v249; // [esp+30h] [ebp-180h]
  int v250; // [esp+30h] [ebp-180h]
  int v251; // [esp+30h] [ebp-180h]
  int v252; // [esp+30h] [ebp-180h]
  _iobuf *f; // [esp+34h] [ebp-17Ch]
  unsigned int *fa; // [esp+34h] [ebp-17Ch]
  _iobuf *fb; // [esp+34h] [ebp-17Ch]
  _iobuf *fc; // [esp+34h] [ebp-17Ch]
  int fd; // [esp+34h] [ebp-17Ch]
  _iobuf *fe; // [esp+34h] [ebp-17Ch]
  idFileSystemLocal *v260; // [esp+38h] [ebp-178h]
  idFileSystemLocal *v261; // [esp+38h] [ebp-178h]
  idFileSystemLocal *v262; // [esp+38h] [ebp-178h]
  idFileSystemLocal *v263; // [esp+38h] [ebp-178h]
  idFileSystemLocal *v264; // [esp+38h] [ebp-178h]
  idFileSystemLocal *v265; // [esp+38h] [ebp-178h]
  unsigned int v266; // [esp+3Ch] [ebp-174h]
  int v267; // [esp+3Ch] [ebp-174h]
  int v268; // [esp+3Ch] [ebp-174h]
  int v269; // [esp+3Ch] [ebp-174h]
  idStr gamepath; // [esp+40h] [ebp-170h] BYREF
  idList<idStr> dirs; // [esp+60h] [ebp-150h] BYREF
  int i; // [esp+70h] [ebp-140h]
  idStr descfile; // [esp+74h] [ebp-13Ch] BYREF
  idList<idStr> pk4s; // [esp+94h] [ebp-11Ch] BYREF
  char desc[256]; // [esp+A4h] [ebp-10Ch] BYREF
  int v276; // [esp+1ACh] [ebp-4h]

  dirs.granularity = 16;
  dirs.list = 0;
  dirs.num = 0;
  dirs.size = 0;
  v276 = 1;
  pk4s.granularity = 16;
  pk4s.list = 0;
  pk4s.num = 0;
  pk4s.size = 0;
  v2 = (int *)Memory::Allocate(0x20u);
  if ( v2 )
  {
    v2[2] = 16;
    v2[3] = 0;
    *v2 = 0;
    v2[1] = 0;
    v2[6] = 16;
    v2[7] = 0;
    v2[4] = 0;
    v2[5] = 0;
    v3 = v2;
  }
  else
  {
    v3 = 0;
  }
  value = (char *)idFileSystemLocal::fs_basepath.internalVar->value;
  LOBYTE(v276) = 1;
  idFileSystemLocal::ListOSFiles(this, value, "/", &dirs);
  gamepath.alloced = 20;
  gamepath.data = gamepath.baseBuffer;
  gamepath.baseBuffer[0] = 0;
  v4 = 0;
  do
  {
    v5 = PathName[v4];
    gamepath.baseBuffer[v4++] = v5;
  }
  while ( v5 );
  gamepath.len = 1;
  v6 = 0;
  LOBYTE(v276) = 4;
  if ( dirs.num > 0 )
  {
    v7 = 0;
    while ( idStr::Cmp(dirs.list[v7].data, gamepath.data) )
    {
      ++v6;
      ++v7;
      if ( v6 >= dirs.num )
        goto LABEL_18;
    }
    if ( v6 >= 0 && v6 < dirs.num )
    {
      --dirs.num;
      ptr = (char *)v6;
      if ( v6 < dirs.num )
      {
        v189 = v6;
        do
        {
          v8 = &dirs.list[v189];
          len = dirs.list[v189 + 1].len;
          if ( len + 1 > dirs.list[v189].alloced )
            idStr::ReAllocate(&dirs.list[v189], len + 1, 0);
          ++v189;
          qmemcpy(v8->data, v8[1].data, len);
          v8->data[len] = 0;
          v8->len = len;
          ++ptr;
        }
        while ( (int)ptr < dirs.num );
      }
    }
  }
LABEL_18:
  LOBYTE(v276) = 1;
  idStr::FreeData(&gamepath);
  gamepath.alloced = 20;
  gamepath.data = gamepath.baseBuffer;
  gamepath.baseBuffer[0] = 0;
  v9 = 0;
  do
  {
    v10 = asc_102A1C90[v9];
    gamepath.baseBuffer[v9++] = v10;
  }
  while ( v10 );
  gamepath.len = 2;
  v11 = 0;
  LOBYTE(v276) = 5;
  if ( dirs.num > 0 )
  {
    v12 = 0;
    while ( idStr::Cmp(dirs.list[v12].data, gamepath.data) )
    {
      ++v11;
      ++v12;
      if ( v11 >= dirs.num )
        goto LABEL_32;
    }
    if ( v11 >= 0 && v11 < dirs.num )
    {
      --dirs.num;
      ptra = (char *)v11;
      if ( v11 < dirs.num )
      {
        v190 = v11;
        do
        {
          v13 = &dirs.list[v190];
          v241 = dirs.list[v190 + 1].len;
          if ( v241 + 1 > dirs.list[v190].alloced )
            idStr::ReAllocate(&dirs.list[v190], v241 + 1, 0);
          ++v190;
          qmemcpy(v13->data, v13[1].data, v241);
          v13->data[v241] = 0;
          v13->len = v241;
          ++ptra;
        }
        while ( (int)ptra < dirs.num );
      }
    }
  }
LABEL_32:
  LOBYTE(v276) = 1;
  idStr::FreeData(&gamepath);
  gamepath.alloced = 20;
  gamepath.data = gamepath.baseBuffer;
  gamepath.baseBuffer[0] = 0;
  v14 = 0;
  do
  {
    v15 = gameName[v14];
    gamepath.baseBuffer[v14++] = v15;
  }
  while ( v15 );
  gamepath.len = 6;
  v16 = 0;
  LOBYTE(v276) = 6;
  if ( dirs.num > 0 )
  {
    v17 = 0;
    while ( idStr::Cmp(dirs.list[v17].data, gamepath.data) )
    {
      ++v16;
      ++v17;
      if ( v16 >= dirs.num )
        goto LABEL_46;
    }
    if ( v16 >= 0 && v16 < dirs.num )
    {
      --dirs.num;
      ptrb = (char *)v16;
      if ( v16 < dirs.num )
      {
        v191 = v16;
        do
        {
          v18 = &dirs.list[v191];
          v242 = dirs.list[v191 + 1].len;
          if ( v242 + 1 > dirs.list[v191].alloced )
            idStr::ReAllocate(&dirs.list[v191], v242 + 1, 0);
          ++v191;
          qmemcpy(v18->data, v18[1].data, v242);
          v18->data[v242] = 0;
          v18->len = v242;
          ++ptrb;
        }
        while ( (int)ptrb < dirs.num );
      }
    }
  }
LABEL_46:
  LOBYTE(v276) = 1;
  idStr::FreeData(&gamepath);
  i = 0;
  if ( dirs.num > 0 )
  {
    v192 = 0;
    do
    {
      v19 = this->BuildOSPath(
              this,
              idFileSystemLocal::fs_basepath.internalVar->value,
              dirs.list[v192].data,
              &entityFilter);
      gamepath.len = 0;
      gamepath.alloced = 20;
      gamepath.data = gamepath.baseBuffer;
      gamepath.baseBuffer[0] = 0;
      if ( v19 )
      {
        v20 = (unsigned int)&v19[strlen(v19) + 1];
        v21 = v20 - (_DWORD)(v19 + 1);
        v22 = v20 - (_DWORD)v19;
        if ( v22 > 20 )
          idStr::ReAllocate(&gamepath, v22, 1);
        data = gamepath.data;
        v24 = v19;
        do
        {
          v25 = *v24;
          *data++ = *v24++;
        }
        while ( v25 );
        gamepath.len = v21;
      }
      LOBYTE(v276) = 7;
      idFileSystemLocal::ListOSFiles(this, gamepath.data, ".pk4", &pk4s);
      descfile.data = descfile.baseBuffer;
      descfile.alloced = 20;
      descfile.baseBuffer[0] = 0;
      v26 = 0;
      do
      {
        v27 = gameName[v26];
        descfile.baseBuffer[v26++] = v27;
      }
      while ( v27 );
      descfile.len = 6;
      v28 = 0;
      LOBYTE(v276) = 8;
      if ( pk4s.num > 0 )
      {
        v29 = 0;
        while ( idStr::Cmp(pk4s.list[v29].data, descfile.data) )
        {
          ++v28;
          ++v29;
          if ( v28 >= pk4s.num )
            goto LABEL_68;
        }
        if ( v28 >= 0 && v28 < pk4s.num )
        {
          --pk4s.num;
          f = (_iobuf *)v28;
          if ( v28 < pk4s.num )
          {
            ptrc = (char *)(32 * v28);
            do
            {
              v30 = (idStr *)&ptrc[(unsigned int)pk4s.list];
              v243 = *(_DWORD *)&ptrc[(unsigned int)pk4s.list + 32];
              if ( v243 + 1 > *(_DWORD *)&ptrc[(unsigned int)pk4s.list + 8] )
                idStr::ReAllocate((idStr *)&ptrc[(unsigned int)pk4s.list], v243 + 1, 0);
              ptrc += 32;
              qmemcpy(v30->data, v30[1].data, v243);
              v30->data[v243] = 0;
              v30->len = v243;
              f = (_iobuf *)((char *)f + 1);
            }
            while ( (int)f < pk4s.num );
          }
        }
      }
LABEL_68:
      LOBYTE(v276) = 7;
      idStr::FreeData(&descfile);
      if ( pk4s.num )
      {
        v207 = &dirs.list[v192];
        if ( !v3[3] )
        {
          v31 = v3[2];
          if ( v31 > 0 )
          {
            if ( v31 != v3[1] )
            {
              v32 = v31 < *v3;
              v3[1] = v31;
              if ( v32 )
                *v3 = v31;
              v33 = (int *)Memory::Allocate(32 * v31 + 4);
              LOBYTE(v276) = 9;
              if ( v33 )
              {
                v34 = v33 + 1;
                *v33 = v31;
                `eh vector constructor iterator'(
                  v33 + 1,
                  0x20u,
                  v31,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v34 = 0;
              }
              v32 = *v3 <= 0;
              LOBYTE(v276) = 7;
              v3[3] = (int)v34;
              ptrd = 0;
              if ( !v32 )
              {
                fa = 0;
                do
                {
                  v35 = (idStr *)((char *)fa + v3[3]);
                  v244 = *fa;
                  if ( (signed int)(*fa + 1) > v35->alloced )
                    idStr::ReAllocate(v35, v244 + 1, 0);
                  v36 = (const void *)fa[1];
                  fa += 8;
                  qmemcpy(v35->data, v36, v244);
                  v35->data[v244] = 0;
                  v35->len = v244;
                  ++ptrd;
                }
                while ( (int)ptrd < *v3 );
              }
            }
          }
          else
          {
            v3[3] = 0;
            *v3 = 0;
            v3[1] = 0;
          }
        }
        v37 = *v3;
        v38 = v3[1];
        if ( *v3 == v38 )
        {
          if ( !v3[2] )
            v3[2] = 16;
          v39 = v38 + v3[2] - (v38 + v3[2]) % v3[2];
          if ( v39 > 0 )
          {
            if ( v39 != v38 )
            {
              ptre = (char *)v3[3];
              v3[1] = v39;
              if ( v39 < v37 )
                *v3 = v39;
              v42 = (int *)Memory::Allocate(32 * v39 + 4);
              LOBYTE(v276) = 10;
              if ( v42 )
              {
                v43 = v42 + 1;
                *v42 = v39;
                `eh vector constructor iterator'(
                  v42 + 1,
                  0x20u,
                  v39,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v43 = 0;
              }
              v32 = *v3 <= 0;
              LOBYTE(v276) = 7;
              v3[3] = (int)v43;
              v245 = 0;
              if ( !v32 )
              {
                fb = 0;
                do
                {
                  v44 = (idStr *)((char *)fb + v3[3]);
                  v266 = *(_DWORD *)&ptre[(_DWORD)fb];
                  if ( (signed int)(v266 + 1) > v44->alloced )
                    idStr::ReAllocate(v44, v266 + 1, 0);
                  v45 = *(const void **)&ptre[(_DWORD)fb++ + 4];
                  qmemcpy(v44->data, v45, v266);
                  v44->data[v266] = 0;
                  v44->len = v266;
                  ++v245;
                }
                while ( v245 < *v3 );
              }
              if ( ptre )
              {
                `eh vector destructor iterator'(
                  ptre,
                  0x20u,
                  *((_DWORD *)ptre - 1),
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(ptre - 4);
              }
            }
          }
          else
          {
            v40 = (char *)v3[3];
            if ( v40 )
            {
              v41 = v40 - 4;
              `eh vector destructor iterator'(
                v40,
                0x20u,
                *((_DWORD *)v40 - 1),
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(v41);
            }
            v3[3] = 0;
            *v3 = 0;
            v3[1] = 0;
          }
        }
        v46 = v207;
        v47 = v207->len;
        v48 = (idStr *)(v3[3] + 32 * *v3);
        v49 = v207->len + 1;
        v208 = v207->len;
        if ( v49 > v48->alloced )
          idStr::ReAllocate(v48, v49, 0);
        qmemcpy(v48->data, v46->data, v47);
        v48->data[v208] = 0;
        v48->len = v208;
        ++*v3;
      }
      LOBYTE(v276) = 1;
      idStr::FreeData(&gamepath);
      ++v192;
      ++i;
    }
    while ( i < dirs.num );
  }
  v50 = *v3;
  if ( *v3 )
  {
    descfile.alloced = 16;
    *(_DWORD *)descfile.baseBuffer = 0;
    descfile.len = 0;
    descfile.data = 0;
    gamepath.alloced = 16;
    *(_DWORD *)gamepath.baseBuffer = 0;
    gamepath.len = 0;
    LOBYTE(v276) = 12;
    if ( v50 > 0 )
    {
      gamepath.data = (char *)v50;
      v51 = Memory::Allocate(4 * v50);
    }
    else
    {
      v51 = 0;
      gamepath.data = 0;
    }
    v52 = 0;
    v32 = *v3 <= 0;
    *(_DWORD *)gamepath.baseBuffer = v51;
    gamepath.len = v50;
    if ( !v32 )
    {
      v53 = 0;
      do
      {
        v51[v52++] = v53 + v3[3];
        v53 += 32;
      }
      while ( v52 < *v3 );
    }
    if ( v51 )
      qsort(v51, v50, 4u, (int (__cdecl *)(const void *, const void *))idListSortCompare<idPoolStr const *>);
    v54 = *v3;
    if ( *v3 > 0 )
    {
      v56 = *v3;
      descfile.data = (char *)*v3;
      v57 = (int *)Memory::Allocate(32 * v54 + 4);
      LOBYTE(v276) = 13;
      if ( v57 )
      {
        v58 = (unsigned int *)(v57 + 1);
        *v57 = v54;
        `eh vector constructor iterator'(
          v57 + 1,
          0x20u,
          v54,
          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        v55 = v58;
      }
      else
      {
        v55 = 0;
      }
      LOBYTE(v276) = 12;
    }
    else
    {
      v55 = 0;
      v56 = 0;
      descfile.data = 0;
    }
    v59 = v3[2];
    *(_DWORD *)descfile.baseBuffer = v55;
    descfile.len = v54;
    descfile.alloced = v59;
    if ( v55 )
    {
      v60 = v54 + v59 - 1 - (v54 + v59 - 1) % descfile.alloced;
      if ( v60 != v56 )
      {
        if ( v60 > 0 )
        {
          ptrf = v55;
          descfile.data = (char *)(v54 + v59 - 1 - (v54 + v59 - 1) % descfile.alloced);
          if ( v60 < v54 )
            descfile.len = v54 + v59 - 1 - (v54 + v59 - 1) % descfile.alloced;
          v62 = (int *)Memory::Allocate(32 * v60 + 4);
          LOBYTE(v276) = 14;
          if ( v62 )
          {
            v63 = (char *)(v62 + 1);
            *v62 = v60;
            `eh vector constructor iterator'(
              v62 + 1,
              0x20u,
              v60,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            v64 = v63;
          }
          else
          {
            v64 = 0;
          }
          LOBYTE(v276) = 12;
          *(_DWORD *)descfile.baseBuffer = v64;
          if ( descfile.len > 0 )
          {
            v193 = ptrf;
            v267 = (char *)ptrf - v64;
            v65 = v64 + 4;
            v246 = descfile.len;
            do
            {
              v209 = *v193;
              if ( (signed int)(*v193 + 1) > *((_DWORD *)v65 + 1) )
                idStr::ReAllocate((idStr *)(v65 - 4), v209 + 1, 0);
              v193 += 8;
              qmemcpy(*(void **)v65, *(const void **)&v65[v267], v209);
              *(_BYTE *)(v209 + *(_DWORD *)v65) = 0;
              *((_DWORD *)v65 - 1) = v209;
              v65 += 32;
              --v246;
            }
            while ( v246 );
          }
          `eh vector destructor iterator'(
            ptrf,
            0x20u,
            *(ptrf - 1),
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(ptrf - 1);
        }
        else
        {
          v61 = (char *)(v55 - 1);
          `eh vector destructor iterator'(
            v55,
            0x20u,
            *(v55 - 1),
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(v61);
          *(_DWORD *)descfile.baseBuffer = 0;
          descfile.len = 0;
          descfile.data = 0;
        }
      }
    }
    v194 = 0;
    if ( descfile.len > 0 )
    {
      v66 = *(_DWORD *)descfile.baseBuffer + 4;
      do
      {
        v67 = *(_DWORD *)(*(_DWORD *)gamepath.baseBuffer + 4 * v194);
        v68 = *(_DWORD *)v67;
        v69 = *(_DWORD *)v67 + 1;
        v210 = *(_DWORD *)v67;
        if ( v69 > *(_DWORD *)(v66 + 4) )
          idStr::ReAllocate((idStr *)(v66 - 4), v69, 0);
        qmemcpy(*(void **)v66, *(const void **)(v67 + 4), v68);
        *(_BYTE *)(v210 + *(_DWORD *)v66) = 0;
        *(_DWORD *)(v66 - 4) = v210;
        v66 += 32;
        ++v194;
      }
      while ( v194 < descfile.len );
    }
    v70 = (char *)*v3;
    v71 = descfile.data;
    *v3 = descfile.len;
    alloced = descfile.alloced;
    descfile.len = (int)v70;
    v73 = (char *)v3[1];
    v3[1] = (int)v71;
    descfile.data = v73;
    descfile.alloced = v3[2];
    v74 = *(_DWORD *)descfile.baseBuffer;
    v3[2] = alloced;
    v75 = (char *)v3[3];
    v3[3] = v74;
    *(_DWORD *)descfile.baseBuffer = v75;
    LOBYTE(v276) = 11;
    if ( *(_DWORD *)gamepath.baseBuffer )
      Memory::Free(*(void **)gamepath.baseBuffer);
    LOBYTE(v276) = 1;
    if ( v75 )
    {
      `eh vector destructor iterator'(
        v75,
        0x20u,
        *((_DWORD *)v75 - 1),
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v75 - 4);
    }
  }
  v32 = *v3 <= 0;
  i = 0;
  if ( !v32 )
  {
    do
    {
      v76 = 32 * i;
      v77 = this->BuildOSPath(
              this,
              idFileSystemLocal::fs_basepath.internalVar->value,
              *(_DWORD *)(32 * i + v3[3] + 4),
              "description.txt");
      descfile.len = 0;
      descfile.alloced = 20;
      descfile.data = descfile.baseBuffer;
      descfile.baseBuffer[0] = 0;
      if ( v77 )
      {
        v78 = (unsigned int)&v77[strlen(v77) + 1];
        v211 = v78 - (_DWORD)(v77 + 1);
        v79 = v78 - (_DWORD)v77;
        if ( v79 > 20 )
          idStr::ReAllocate(&descfile, v79, 1);
        v80 = descfile.data;
        v81 = v77;
        do
        {
          v82 = *v81;
          *v80++ = *v81++;
        }
        while ( v82 );
        descfile.len = v211;
      }
      LOBYTE(v276) = 15;
      v83 = idFileSystemLocal::OpenOSFile(this, descfile.data, "r", 0);
      fc = v83;
      if ( v83 )
      {
        if ( sys->FGets(sys, desc, 256, v83) )
        {
          gamepath.len = 0;
          gamepath.alloced = 20;
          gamepath.data = gamepath.baseBuffer;
          gamepath.baseBuffer[0] = 0;
          v84 = strlen(desc);
          if ( v84 + 1 > 20 )
            idStr::ReAllocate(&gamepath, v84 + 1, 1);
          v85 = gamepath.data;
          v86 = desc;
          do
          {
            v87 = *v86;
            *v85++ = *v86++;
          }
          while ( v87 );
          gamepath.len = v84;
          v88 = v3[7] == 0;
          LOBYTE(v276) = 16;
          if ( v88 )
          {
            v89 = v3[6];
            if ( v89 > 0 )
            {
              if ( v89 != v3[5] )
              {
                v32 = v89 < v3[4];
                v3[5] = v89;
                if ( v32 )
                  v3[4] = v89;
                v90 = (int *)Memory::Allocate(32 * v89 + 4);
                LOBYTE(v276) = 17;
                if ( v90 )
                {
                  v91 = v90 + 1;
                  *v90 = v89;
                  `eh vector constructor iterator'(
                    v90 + 1,
                    0x20u,
                    v89,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v91 = 0;
                }
                v92 = 0;
                v32 = v3[4] <= 0;
                LOBYTE(v276) = 16;
                v3[7] = (int)v91;
                v247 = 0;
                if ( !v32 )
                {
                  for ( j = 0; ; v92 = j )
                  {
                    v93 = (idStr *)((char *)v92 + v3[7]);
                    v212 = *v92;
                    if ( (signed int)(*v92 + 1) > v93->alloced )
                      idStr::ReAllocate(v93, v212 + 1, 0);
                    v94 = (const void *)j[1];
                    j += 8;
                    qmemcpy(v93->data, v94, v212);
                    v93->data[v212] = 0;
                    v93->len = v212;
                    if ( ++v247 >= v3[4] )
                      break;
                  }
                }
              }
            }
            else
            {
              v3[7] = 0;
              v3[4] = 0;
              v3[5] = 0;
            }
          }
          v95 = v3[4];
          v96 = v3[5];
          if ( v95 == v96 )
          {
            if ( !v3[6] )
              v3[6] = 16;
            v97 = v96 + v3[6] - (v96 + v3[6]) % v3[6];
            if ( v97 > 0 )
            {
              if ( v97 != v3[5] )
              {
                ptrg = (char *)v3[7];
                v3[5] = v97;
                if ( v97 < v95 )
                  v3[4] = v97;
                v100 = (int *)Memory::Allocate(32 * v97 + 4);
                LOBYTE(v276) = 18;
                if ( v100 )
                {
                  v101 = v100 + 1;
                  *v100 = v97;
                  `eh vector constructor iterator'(
                    v100 + 1,
                    0x20u,
                    v97,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v101 = 0;
                }
                v32 = v3[4] <= 0;
                LOBYTE(v276) = 16;
                v3[7] = (int)v101;
                v248 = 0;
                if ( !v32 )
                {
                  v196 = 0;
                  do
                  {
                    v102 = (idStr *)(v196 + v3[7]);
                    v213 = *(_DWORD *)&ptrg[v196];
                    if ( (signed int)(v213 + 1) > v102->alloced )
                      idStr::ReAllocate(v102, v213 + 1, 0);
                    v103 = *(const void **)&ptrg[v196 + 4];
                    v196 += 32;
                    qmemcpy(v102->data, v103, v213);
                    v102->data[v213] = 0;
                    v102->len = v213;
                    ++v248;
                  }
                  while ( v248 < v3[4] );
                }
                if ( ptrg )
                {
                  `eh vector destructor iterator'(
                    ptrg,
                    0x20u,
                    *((_DWORD *)ptrg - 1),
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  Memory::Free(ptrg - 4);
                }
              }
            }
            else
            {
              v98 = (char *)v3[7];
              if ( v98 )
              {
                v99 = v98 - 4;
                `eh vector destructor iterator'(
                  v98,
                  0x20u,
                  *((_DWORD *)v98 - 1),
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(v99);
              }
              v3[7] = 0;
              v3[4] = 0;
              v3[5] = 0;
            }
          }
          v104 = (idStr *)(v3[7] + 32 * v3[4]);
          v105 = gamepath.len;
          v214 = gamepath.len;
          if ( gamepath.len + 1 > v104->alloced )
            idStr::ReAllocate(v104, gamepath.len + 1, 0);
          qmemcpy(v104->data, gamepath.data, v105);
          v104->data[v214] = 0;
          v104->len = v214;
          ++v3[4];
          LOBYTE(v276) = 15;
          idStr::FreeData(&gamepath);
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 140))(
            common.type,
            "Error reading %s/description.txt",
            *(_DWORD *)(v76 + v3[3] + 4));
          v268 = v76 + v3[3];
          if ( !v3[7] )
          {
            v106 = v3[6];
            if ( v106 > 0 )
            {
              if ( v106 != v3[5] )
              {
                v32 = v106 < v3[4];
                v3[5] = v106;
                if ( v32 )
                  v3[4] = v106;
                v107 = (int *)Memory::Allocate(32 * v106 + 4);
                LOBYTE(v276) = 19;
                if ( v107 )
                {
                  v108 = v107 + 1;
                  *v107 = v106;
                  `eh vector constructor iterator'(
                    v107 + 1,
                    0x20u,
                    v106,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v108 = 0;
                }
                v32 = v3[4] <= 0;
                LOBYTE(v276) = 15;
                v3[7] = (int)v108;
                v249 = 0;
                if ( !v32 )
                {
                  v197 = 0;
                  do
                  {
                    v109 = (idStr *)((char *)v197 + v3[7]);
                    v215 = *v197;
                    if ( (signed int)(*v197 + 1) > v109->alloced )
                      idStr::ReAllocate(v109, v215 + 1, 0);
                    v110 = (const void *)v197[1];
                    v197 += 8;
                    qmemcpy(v109->data, v110, v215);
                    v109->data[v215] = 0;
                    v109->len = v215;
                    ++v249;
                  }
                  while ( v249 < v3[4] );
                }
              }
            }
            else
            {
              v3[7] = 0;
              v3[4] = 0;
              v3[5] = 0;
            }
          }
          v111 = v3[4];
          v112 = v3[5];
          if ( v111 == v112 )
          {
            if ( !v3[6] )
              v3[6] = 16;
            v113 = v112 + v3[6] - (v112 + v3[6]) % v3[6];
            if ( v113 > 0 )
            {
              if ( v113 != v3[5] )
              {
                ptrh = (char *)v3[7];
                v3[5] = v113;
                if ( v113 < v111 )
                  v3[4] = v113;
                v116 = (int *)Memory::Allocate(32 * v113 + 4);
                LOBYTE(v276) = 20;
                if ( v116 )
                {
                  v117 = v116 + 1;
                  *v116 = v113;
                  `eh vector constructor iterator'(
                    v116 + 1,
                    0x20u,
                    v113,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v117 = 0;
                }
                v32 = v3[4] <= 0;
                LOBYTE(v276) = 15;
                v3[7] = (int)v117;
                v250 = 0;
                if ( !v32 )
                {
                  v198 = 0;
                  do
                  {
                    v118 = (idStr *)(v198 + v3[7]);
                    v216 = *(_DWORD *)&ptrh[v198];
                    if ( (signed int)(v216 + 1) > v118->alloced )
                      idStr::ReAllocate(v118, v216 + 1, 0);
                    v119 = *(const void **)&ptrh[v198 + 4];
                    v198 += 32;
                    qmemcpy(v118->data, v119, v216);
                    v118->data[v216] = 0;
                    v118->len = v216;
                    ++v250;
                  }
                  while ( v250 < v3[4] );
                }
                if ( ptrh )
                {
                  `eh vector destructor iterator'(
                    ptrh,
                    0x20u,
                    *((_DWORD *)ptrh - 1),
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  Memory::Free(ptrh - 4);
                }
              }
            }
            else
            {
              v114 = (char *)v3[7];
              if ( v114 )
              {
                v115 = v114 - 4;
                `eh vector destructor iterator'(
                  v114,
                  0x20u,
                  *((_DWORD *)v114 - 1),
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(v115);
              }
              v3[7] = 0;
              v3[4] = 0;
              v3[5] = 0;
            }
          }
          v120 = *(_DWORD *)v268;
          v121 = (idStr *)(v3[7] + 32 * v3[4]);
          v122 = *(_DWORD *)v268 + 1;
          v217 = *(_DWORD *)v268;
          if ( v122 > v121->alloced )
            idStr::ReAllocate(v121, v122, 0);
          qmemcpy(v121->data, *(const void **)(v268 + 4), v120);
          v121->data[v217] = 0;
          v121->len = v217;
          ++v3[4];
        }
        sys->FClose(sys, fc);
      }
      else
      {
        v269 = v76 + v3[3];
        if ( !v3[7] )
        {
          v123 = v3[6];
          if ( v123 > 0 )
          {
            if ( v123 != v3[5] )
            {
              v32 = v123 < v3[4];
              v3[5] = v123;
              if ( v32 )
                v3[4] = v123;
              v124 = (int *)Memory::Allocate(32 * v123 + 4);
              LOBYTE(v276) = 21;
              if ( v124 )
              {
                v125 = v124 + 1;
                *v124 = v123;
                `eh vector constructor iterator'(
                  v124 + 1,
                  0x20u,
                  v123,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v125 = 0;
              }
              v32 = v3[4] <= 0;
              LOBYTE(v276) = 15;
              v3[7] = (int)v125;
              v251 = 0;
              if ( !v32 )
              {
                v199 = 0;
                do
                {
                  v126 = (idStr *)((char *)v199 + v3[7]);
                  v218 = *v199;
                  if ( (signed int)(*v199 + 1) > v126->alloced )
                    idStr::ReAllocate(v126, v218 + 1, 0);
                  v127 = (const void *)v199[1];
                  v199 += 8;
                  qmemcpy(v126->data, v127, v218);
                  v126->data[v218] = 0;
                  v126->len = v218;
                  ++v251;
                }
                while ( v251 < v3[4] );
              }
            }
          }
          else
          {
            v3[7] = 0;
            v3[4] = 0;
            v3[5] = 0;
          }
        }
        v128 = v3[4];
        v129 = v3[5];
        if ( v128 == v129 )
        {
          if ( !v3[6] )
            v3[6] = 16;
          v130 = v129 + v3[6] - (v129 + v3[6]) % v3[6];
          if ( v130 > 0 )
          {
            if ( v130 != v3[5] )
            {
              ptri = (char *)v3[7];
              v3[5] = v130;
              if ( v130 < v128 )
                v3[4] = v130;
              v133 = (int *)Memory::Allocate(32 * v130 + 4);
              LOBYTE(v276) = 22;
              if ( v133 )
              {
                v134 = v133 + 1;
                *v133 = v130;
                `eh vector constructor iterator'(
                  v133 + 1,
                  0x20u,
                  v130,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v134 = 0;
              }
              v32 = v3[4] <= 0;
              LOBYTE(v276) = 15;
              v3[7] = (int)v134;
              v252 = 0;
              if ( !v32 )
              {
                v200 = 0;
                do
                {
                  v135 = (idStr *)(v200 + v3[7]);
                  v219 = *(_DWORD *)&ptri[v200];
                  if ( (signed int)(v219 + 1) > v135->alloced )
                    idStr::ReAllocate(v135, v219 + 1, 0);
                  v136 = *(const void **)&ptri[v200 + 4];
                  v200 += 32;
                  qmemcpy(v135->data, v136, v219);
                  v135->data[v219] = 0;
                  v135->len = v219;
                  ++v252;
                }
                while ( v252 < v3[4] );
              }
              if ( ptri )
              {
                `eh vector destructor iterator'(
                  ptri,
                  0x20u,
                  *((_DWORD *)ptri - 1),
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(ptri - 4);
              }
            }
          }
          else
          {
            v131 = (char *)v3[7];
            if ( v131 )
            {
              v132 = v131 - 4;
              `eh vector destructor iterator'(
                v131,
                0x20u,
                *((_DWORD *)v131 - 1),
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(v132);
            }
            v3[7] = 0;
            v3[4] = 0;
            v3[5] = 0;
          }
        }
        v137 = *(_DWORD *)v269;
        v138 = (idStr *)(v3[7] + 32 * v3[4]);
        v139 = *(_DWORD *)v269 + 1;
        v220 = *(_DWORD *)v269;
        if ( v139 > v138->alloced )
          idStr::ReAllocate(v138, v139, 0);
        qmemcpy(v138->data, *(const void **)(v269 + 4), v137);
        v138->data[v220] = 0;
        v138->len = v220;
        ++v3[4];
      }
      LOBYTE(v276) = 1;
      idStr::FreeData(&descfile);
      v32 = ++i < *v3;
    }
    while ( v32 );
  }
  v140 = cvarSystem->GetCVarString(cvarSystem, "fs_game");
  if ( idStr::Icmp(v140, &entityFilter) )
  {
    gamepath.data = gamepath.baseBuffer;
    gamepath.alloced = 20;
    gamepath.baseBuffer[0] = 0;
    v141 = 0;
    do
    {
      v142 = *(&entityFilter + v141);
      gamepath.baseBuffer[v141++] = v142;
    }
    while ( v142 );
    gamepath.len = 0;
    v88 = v3[3] == 0;
    LOBYTE(v276) = 23;
    fd = 0;
    if ( v88 )
    {
      v143 = v3[2];
      if ( v143 > 0 )
      {
        if ( v143 != v3[1] )
        {
          v32 = v143 < *v3;
          v3[1] = v143;
          if ( v32 )
            *v3 = v143;
          v144 = (int *)Memory::Allocate(32 * v143 + 4);
          LOBYTE(v276) = 24;
          if ( v144 )
          {
            v145 = v144 + 1;
            *v144 = v143;
            `eh vector constructor iterator'(
              v144 + 1,
              0x20u,
              v143,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v145 = 0;
          }
          v32 = *v3 <= 0;
          LOBYTE(v276) = 23;
          v3[3] = (int)v145;
          v260 = 0;
          if ( !v32 )
          {
            v201 = 0;
            do
            {
              v146 = (idStr *)((char *)v201 + v3[3]);
              v221 = *v201;
              if ( (signed int)(*v201 + 1) > v146->alloced )
                idStr::ReAllocate(v146, v221 + 1, 0);
              v147 = (const void *)v201[1];
              v201 += 8;
              qmemcpy(v146->data, v147, v221);
              v146->data[v221] = 0;
              v146->len = v221;
              v260 = (idFileSystemLocal *)((char *)v260 + 1);
            }
            while ( (int)v260 < *v3 );
          }
        }
      }
      else
      {
        v3[3] = 0;
        *v3 = 0;
        v3[1] = 0;
      }
    }
    v148 = (char *)*v3;
    v149 = v3[1];
    if ( *v3 == v149 )
    {
      if ( !v3[2] )
        v3[2] = 16;
      v150 = v149 + v3[2] - (v149 + v3[2]) % v3[2];
      if ( v150 > 0 )
      {
        if ( v150 != v149 )
        {
          ptrj = (char *)v3[3];
          v3[1] = v150;
          if ( v150 < (int)v148 )
            *v3 = v150;
          v153 = (int *)Memory::Allocate(32 * v150 + 4);
          LOBYTE(v276) = 25;
          if ( v153 )
          {
            v154 = v153 + 1;
            *v153 = v150;
            `eh vector constructor iterator'(
              v153 + 1,
              0x20u,
              v150,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v154 = 0;
          }
          v32 = *v3 <= 0;
          LOBYTE(v276) = 23;
          v3[3] = (int)v154;
          v261 = 0;
          if ( !v32 )
          {
            v202 = 0;
            do
            {
              v155 = (idStr *)(v202 + v3[3]);
              v222 = *(_DWORD *)&ptrj[v202];
              if ( (signed int)(v222 + 1) > v155->alloced )
                idStr::ReAllocate(v155, v222 + 1, 0);
              v156 = *(const void **)&ptrj[v202 + 4];
              v202 += 32;
              qmemcpy(v155->data, v156, v222);
              v155->data[v222] = 0;
              v155->len = v222;
              v261 = (idFileSystemLocal *)((char *)v261 + 1);
            }
            while ( (int)v261 < *v3 );
          }
          if ( ptrj )
          {
            `eh vector destructor iterator'(
              ptrj,
              0x20u,
              *((_DWORD *)ptrj - 1),
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(ptrj - 4);
          }
        }
      }
      else
      {
        v151 = (char *)v3[3];
        if ( v151 )
        {
          v152 = v151 - 4;
          `eh vector destructor iterator'(
            v151,
            0x20u,
            *((_DWORD *)v151 - 1),
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(v152);
        }
        v3[3] = 0;
        *v3 = 0;
        v3[1] = 0;
      }
    }
    v157 = *v3;
    if ( *v3 < 0 )
      fd = *v3;
    if ( v157 > fd )
    {
      v203 = 32 * v157;
      v262 = (idFileSystemLocal *)(v157 - fd);
      do
      {
        v158 = (idStr *)(v203 + v3[3]);
        v223 = v158[-1].len;
        if ( (signed int)(v223 + 1) > v158->alloced )
          idStr::ReAllocate(v158, v223 + 1, 0);
        v203 -= 32;
        qmemcpy(v158->data, v158[-1].data, v223);
        v88 = v262 == (idFileSystemLocal *)1;
        v262 = (idFileSystemLocal *)((char *)v262 - 1);
        v158->data[v223] = 0;
        v158->len = v223;
      }
      while ( !v88 );
    }
    v159 = gamepath.len;
    ++*v3;
    v160 = (idStr *)(v3[3] + 32 * fd);
    v161 = v159;
    v162 = v159 + 1;
    if ( v162 > v160->alloced )
      idStr::ReAllocate(v160, v162, 0);
    qmemcpy(v160->data, gamepath.data, v161);
    v160->data[v161] = 0;
    v160->len = v161;
    LOBYTE(v276) = 1;
    idStr::FreeData(&gamepath);
    gamepath.alloced = 20;
    gamepath.data = gamepath.baseBuffer;
    gamepath.baseBuffer[0] = 0;
    v163 = 0;
    do
    {
      v164 = aQuake4_1[v163];
      gamepath.baseBuffer[v163++] = v164;
    }
    while ( v164 );
    gamepath.len = 7;
    v88 = v3[7] == 0;
    LOBYTE(v276) = 26;
    fe = 0;
    if ( v88 )
    {
      v165 = v3[6];
      if ( v165 > 0 )
      {
        if ( v165 != v3[5] )
        {
          v32 = v165 < v3[4];
          v3[5] = v165;
          if ( v32 )
            v3[4] = v165;
          v166 = (int *)Memory::Allocate(32 * v165 + 4);
          LOBYTE(v276) = 27;
          if ( v166 )
          {
            v167 = v166 + 1;
            *v166 = v165;
            `eh vector constructor iterator'(
              v166 + 1,
              0x20u,
              v165,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v167 = 0;
          }
          v32 = v3[4] <= 0;
          LOBYTE(v276) = 26;
          v3[7] = (int)v167;
          v263 = 0;
          if ( !v32 )
          {
            v204 = 0;
            do
            {
              v168 = (idStr *)((char *)v204 + v3[7]);
              v224 = *v204;
              if ( (signed int)(*v204 + 1) > v168->alloced )
                idStr::ReAllocate(v168, v224 + 1, 0);
              v169 = (const void *)v204[1];
              v204 += 8;
              qmemcpy(v168->data, v169, v224);
              v168->data[v224] = 0;
              v168->len = v224;
              v263 = (idFileSystemLocal *)((char *)v263 + 1);
            }
            while ( (int)v263 < v3[4] );
          }
        }
      }
      else
      {
        v3[7] = 0;
        v3[4] = 0;
        v3[5] = 0;
      }
    }
    v170 = v3[4];
    v171 = v3[5];
    if ( v170 == v171 )
    {
      if ( !v3[6] )
        v3[6] = 16;
      v172 = v171 + v3[6] - (v171 + v3[6]) % v3[6];
      if ( v172 > 0 )
      {
        if ( v172 != v3[5] )
        {
          ptrk = (char *)v3[7];
          v3[5] = v172;
          if ( v172 < v170 )
            v3[4] = v172;
          v175 = (int *)Memory::Allocate(32 * v172 + 4);
          LOBYTE(v276) = 28;
          if ( v175 )
          {
            v176 = v175 + 1;
            *v175 = v172;
            `eh vector constructor iterator'(
              v175 + 1,
              0x20u,
              v172,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v176 = 0;
          }
          v32 = v3[4] <= 0;
          LOBYTE(v276) = 26;
          v3[7] = (int)v176;
          v264 = 0;
          if ( !v32 )
          {
            v205 = 0;
            do
            {
              v177 = (idStr *)(v205 + v3[7]);
              v225 = *(_DWORD *)&ptrk[v205];
              if ( (signed int)(v225 + 1) > v177->alloced )
                idStr::ReAllocate(v177, v225 + 1, 0);
              v178 = *(const void **)&ptrk[v205 + 4];
              v205 += 32;
              qmemcpy(v177->data, v178, v225);
              v177->data[v225] = 0;
              v177->len = v225;
              v264 = (idFileSystemLocal *)((char *)v264 + 1);
            }
            while ( (int)v264 < v3[4] );
          }
          if ( ptrk )
          {
            `eh vector destructor iterator'(
              ptrk,
              0x20u,
              *((_DWORD *)ptrk - 1),
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(ptrk - 4);
          }
        }
      }
      else
      {
        v173 = (char *)v3[7];
        if ( v173 )
        {
          v174 = v173 - 4;
          `eh vector destructor iterator'(
            v173,
            0x20u,
            *((_DWORD *)v173 - 1),
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(v174);
        }
        v3[7] = 0;
        v3[4] = 0;
        v3[5] = 0;
      }
    }
    v179 = v3[4];
    if ( v179 >= 0 )
    {
      v180 = 0;
    }
    else
    {
      v180 = v3[4];
      fe = (_iobuf *)v180;
    }
    if ( v179 > v180 )
    {
      v181 = 32 * v179;
      v206 = 32 * v179;
      v265 = (idFileSystemLocal *)(v179 - v180);
      while ( 1 )
      {
        v182 = (idStr *)(v3[7] + v181);
        v226 = v182[-1].len;
        if ( (signed int)(v226 + 1) > v182->alloced )
          idStr::ReAllocate(v182, v226 + 1, 0);
        v206 -= 32;
        qmemcpy(v182->data, v182[-1].data, v226);
        v88 = v265 == (idFileSystemLocal *)1;
        v265 = (idFileSystemLocal *)((char *)v265 - 1);
        v182->data[v226] = 0;
        v182->len = v226;
        if ( v88 )
          break;
        v181 = v206;
      }
      v180 = (int)fe;
    }
    ++v3[4];
    v183 = (idStr *)(v3[7] + 32 * v180);
    v184 = gamepath.len;
    v227 = gamepath.len;
    if ( gamepath.len + 1 > v183->alloced )
      idStr::ReAllocate(v183, gamepath.len + 1, 0);
    qmemcpy(v183->data, gamepath.data, v184);
    v183->data[v227] = 0;
    v183->len = v227;
    LOBYTE(v276) = 1;
    idStr::FreeData(&gamepath);
  }
  LOBYTE(v276) = 0;
  if ( pk4s.list )
  {
    v185 = &pk4s.list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      pk4s.list,
      0x20u,
      *(_DWORD *)&pk4s.list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v185);
  }
  pk4s.list = 0;
  pk4s.num = 0;
  pk4s.size = 0;
  v276 = -1;
  if ( dirs.list )
  {
    v186 = &dirs.list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      dirs.list,
      0x20u,
      *(_DWORD *)&dirs.list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v186);
  }
  return (idModList *)v3;
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::FreeFileList(class idFileList *)
void __thiscall idFileSystemLocal::FreeFileList(idFileSystemLocal *this, idFileList *fileList)
{
  if ( fileList )
  {
    idFileList::~idFileList(fileList);
    Memory::Free(fileList);
  }
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::FreeModList(class idModList *)
void __thiscall idFileSystemLocal::FreeModList(idFileSystemLocal *this, idModList *modList)
{
  if ( modList )
  {
    idModList::~idModList(modList);
    Memory::Free(modList);
  }
}

// FUNC: public: static void __cdecl idFileSystemLocal::Dir_f(class idCmdArgs const &)
void __cdecl idFileSystemLocal::Dir_f(const idCmdArgs *args)
{
  int argc; // eax
  bool v2; // cc
  char *v3; // eax
  char *v4; // esi
  idFileList *v5; // esi
  int v6; // edi
  int v7; // ebp
  idStr relativePath; // [esp+8h] [ebp-4Ch] BYREF
  idStr extension; // [esp+28h] [ebp-2Ch] BYREF
  int v10; // [esp+50h] [ebp-4h]

  relativePath.len = 0;
  relativePath.alloced = 20;
  relativePath.data = relativePath.baseBuffer;
  relativePath.baseBuffer[0] = 0;
  v10 = 0;
  extension.len = 0;
  extension.alloced = 20;
  extension.data = extension.baseBuffer;
  extension.baseBuffer[0] = 0;
  argc = args->argc;
  v2 = args->argc < 2;
  LOBYTE(v10) = 1;
  if ( v2 || argc > 3 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: dir <directory> [extension]\n");
    LOBYTE(v10) = 0;
    idStr::FreeData(&extension);
    v10 = -1;
    idStr::FreeData(&relativePath);
  }
  else
  {
    if ( argc == 2 )
    {
      idStr::operator=(&relativePath, args->argv[1]);
      idStr::operator=(&extension, (char *)&entityFilter);
    }
    else
    {
      if ( argc <= 1 )
        v3 = (char *)&entityFilter;
      else
        v3 = args->argv[1];
      idStr::operator=(&relativePath, v3);
      if ( args->argc <= 2 )
        v4 = (char *)&entityFilter;
      else
        v4 = args->argv[2];
      idStr::operator=(&extension, v4);
      if ( *extension.data != 46 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
          common.type,
          "extension should have a leading dot");
    }
    idStr::BackSlashesToSlashes(&relativePath);
    idStr::StripTrailing(&relativePath, 47);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Listing of %s/*%s\n",
      relativePath.data,
      extension.data);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "---------------\n");
    v5 = idFileSystemLocal::ListFiles(&fileSystemLocal, relativePath.data, extension.data, 0, 0, 0);
    v6 = 0;
    if ( v5->list.num > 0 )
    {
      v7 = 0;
      do
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%s\n",
          v5->list.list[v7].data);
        ++v6;
        ++v7;
      }
      while ( v6 < v5->list.num );
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%d files\n",
      v5->list.num);
    idFileList::~idFileList(v5);
    Memory::Free(v5);
    LOBYTE(v10) = 0;
    idStr::FreeData(&extension);
    v10 = -1;
    idStr::FreeData(&relativePath);
  }
}

// FUNC: public: static void __cdecl idFileSystemLocal::DirTree_f(class idCmdArgs const &)
void __cdecl idFileSystemLocal::DirTree_f(const idCmdArgs *args)
{
  int argc; // eax
  bool v2; // cc
  char *v3; // eax
  char *v4; // esi
  idFileList *v5; // esi
  int v6; // edi
  int v7; // ebp
  idStr relativePath; // [esp+8h] [ebp-4Ch] BYREF
  idStr extension; // [esp+28h] [ebp-2Ch] BYREF
  int v10; // [esp+50h] [ebp-4h]

  relativePath.len = 0;
  relativePath.alloced = 20;
  relativePath.data = relativePath.baseBuffer;
  relativePath.baseBuffer[0] = 0;
  v10 = 0;
  extension.len = 0;
  extension.alloced = 20;
  extension.data = extension.baseBuffer;
  extension.baseBuffer[0] = 0;
  argc = args->argc;
  v2 = args->argc < 2;
  LOBYTE(v10) = 1;
  if ( v2 || argc > 3 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: dirtree <directory> [extension]\n");
    LOBYTE(v10) = 0;
    idStr::FreeData(&extension);
    v10 = -1;
    idStr::FreeData(&relativePath);
  }
  else
  {
    if ( argc == 2 )
    {
      idStr::operator=(&relativePath, args->argv[1]);
      idStr::operator=(&extension, (char *)&entityFilter);
    }
    else
    {
      if ( argc <= 1 )
        v3 = (char *)&entityFilter;
      else
        v3 = args->argv[1];
      idStr::operator=(&relativePath, v3);
      if ( args->argc <= 2 )
        v4 = (char *)&entityFilter;
      else
        v4 = args->argv[2];
      idStr::operator=(&extension, v4);
      if ( *extension.data != 46 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
          common.type,
          "extension should have a leading dot");
    }
    idStr::BackSlashesToSlashes(&relativePath);
    idStr::StripTrailing(&relativePath, 47);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Listing of %s/*%s /s\n",
      relativePath.data,
      extension.data);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "---------------\n");
    v5 = idFileSystemLocal::ListFilesTree(&fileSystemLocal, relativePath.data, extension.data, 0, 0);
    v6 = 0;
    if ( v5->list.num > 0 )
    {
      v7 = 0;
      do
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%s\n",
          v5->list.list[v7].data);
        ++v6;
        ++v7;
      }
      while ( v6 < v5->list.num );
    }
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%d files\n",
      v5->list.num);
    idFileList::~idFileList(v5);
    Memory::Free(v5);
    LOBYTE(v10) = 0;
    idStr::FreeData(&extension);
    v10 = -1;
    idStr::FreeData(&relativePath);
  }
}

// FUNC: private: void __thiscall idFileSystemLocal::Startup(void)
void __usercall idFileSystemLocal::Startup(
        idFileSystemLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        int a4@<edi>,
        int a5@<esi>)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  const char *value; // eax
  const char *v8; // eax
  searchpath_s *searchPaths; // eax
  searchpath_s **p_searchPaths; // ebp
  pack_t *pack; // edi
  int num; // edx
  int v13; // eax
  int *list; // ecx
  int v15; // ecx
  int v16; // ecx
  int *v17; // ecx
  int v18; // edx
  int *v19; // ecx
  searchpath_s **p_next; // edi
  searchpath_s *v21; // ecx
  pack_t *v22; // eax
  bool v23; // zf
  char *v24; // ebp
  char *v25; // edi
  int v26; // ecx
  int v27; // edx
  int v28; // eax
  int v29; // edi
  int *v30; // ecx
  char *v31; // ebp
  bool v32; // cc
  const char *v33; // eax
  char *v34; // edi
  char *v35; // ebx
  char v36; // cl
  int v37; // eax
  char *v38; // edx
  char *v39; // ebp
  const char *v40; // eax
  char *v41; // edi
  char *v42; // ebx
  char v43; // cl
  int v44; // eax
  char *v45; // edx
  int granularity; // eax
  int k; // eax
  int v48; // ebx
  int size; // eax
  int v50; // ecx
  pack_t **v51; // edi
  int m; // eax
  int v53; // eax
  int v54; // ecx
  int v55; // eax
  int *v56; // ecx
  int v57; // edx
  int *v58; // ecx
  char *v59; // ebp
  const char *v60; // eax
  char *v61; // edi
  char *v62; // ebx
  char v63; // cl
  int v64; // eax
  char *v65; // edx
  char *v66; // ebx
  const char *v67; // eax
  char *v68; // edi
  char *v69; // ebp
  char v70; // cl
  int v71; // eax
  char *v72; // edx
  int j; // eax
  int i; // [esp+3Ch] [ebp-938h]
  int checks; // [esp+40h] [ebp-934h]
  int checks_4; // [esp+44h] [ebp-930h]
  int checks_8; // [esp+48h] [ebp-92Ch]
  int checks_12; // [esp+4Ch] [ebp-928h]
  int checks_16; // [esp+50h] [ebp-924h]
  int checks_20; // [esp+54h] [ebp-920h]
  int checks_24; // [esp+58h] [ebp-91Ch]
  int checks_28; // [esp+5Ch] [ebp-918h]
  searchpath_s **search; // [esp+60h] [ebp-914h]
  idCmdArgs args; // [esp+64h] [ebp-910h] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v86; // [esp+968h] [ebp-Ch]
  void *v87; // [esp+96Ch] [ebp-8h]
  int v88; // [esp+970h] [ebp-4h]

  v88 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v87 = &_ehhandler__Startup_idFileSystemLocal__AAEXXZ;
  v86 = ExceptionList;
  (*(void (__stdcall **)(netadrtype_t, const char *, int, int, int, int, int, int, int, int, int, int, int, int, int, searchpath_s **, int, char *, char *, char *, char *, char *, char *, char *, char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "--------- Initializing File System ----------\n",
    a4,
    a5,
    a3,
    a2,
    i,
    checks,
    checks_4,
    checks_8,
    checks_12,
    checks_16,
    checks_20,
    checks_24,
    checks_28,
    search,
    args.argc,
    args.argv[0],
    args.argv[1],
    args.argv[2],
    args.argv[3],
    args.argv[4],
    args.argv[5],
    args.argv[6],
    args.argv[7]);
  if ( this->restartChecksums.num )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "restarting in pure mode with %d pak files\n",
      this->restartChecksums.num);
  if ( this->addonChecksums.num )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "restarting filesystem with %d addon pak file(s) to include\n",
      this->addonChecksums.num);
  idFileSystemLocal::SetupGameDirectories(this, "q4base");
  value = idFileSystemLocal::fs_game_base.internalVar->value;
  if ( *value && idStr::Icmp(value, "q4base") )
    idFileSystemLocal::SetupGameDirectories(this, (char *)idFileSystemLocal::fs_game_base.internalVar->value);
  v8 = idFileSystemLocal::fs_game.internalVar->value;
  if ( *v8
    && idStr::Icmp(v8, "q4base")
    && idStr::Icmp(idFileSystemLocal::fs_game.internalVar->value, idFileSystemLocal::fs_game_base.internalVar->value) )
  {
    idFileSystemLocal::SetupGameDirectories(this, (char *)idFileSystemLocal::fs_game.internalVar->value);
  }
  searchPaths = this->searchPaths;
  p_searchPaths = &this->searchPaths;
  if ( searchPaths )
  {
    do
    {
      pack = searchPaths->pack;
      if ( searchPaths->pack && pack->addon )
      {
        if ( idFileSystemLocal::fs_searchAddons.internalVar->integerValue )
        {
          pack->addon_search = 1;
          p_searchPaths = &(*p_searchPaths)->next;
        }
        else
        {
          num = this->addonChecksums.num;
          v13 = 0;
          if ( num > 0 )
          {
            list = this->addonChecksums.list;
            while ( *list != pack->checksum )
            {
              ++v13;
              ++list;
              if ( v13 >= num )
              {
                p_searchPaths = &(*p_searchPaths)->next;
                goto LABEL_29;
              }
            }
            if ( v13 >= 0 )
            {
              pack->addon_search = 1;
              v15 = this->addonChecksums.num;
              if ( v13 < v15 )
              {
                v16 = v15 - 1;
                for ( this->addonChecksums.num = v16; v13 < this->addonChecksums.num; *v19 = v18 )
                {
                  v17 = this->addonChecksums.list;
                  v18 = v17[v13 + 1];
                  v19 = &v17[v13++];
                }
              }
              idFileSystemLocal::FollowAddonDependencies(this, pack);
            }
          }
          p_searchPaths = &(*p_searchPaths)->next;
        }
      }
      else
      {
        p_searchPaths = &searchPaths->next;
      }
LABEL_29:
      searchPaths = *p_searchPaths;
    }
    while ( *p_searchPaths );
  }
  p_next = &this->searchPaths;
  while ( *p_next )
  {
    v21 = *p_next;
    v22 = (*p_next)->pack;
    if ( v22 && v22->addon )
    {
      if ( v22->addon_search )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "Addon pk4 %s with checksum 0x%x is on the search list\n",
          v22->pakFilename.data,
          v22->checksum);
        p_next = &(*p_next)->next;
      }
      else
      {
        *p_next = v21->next;
        v21->next = this->addonPaks;
        this->addonPaks = v21;
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "Addon pk4 %s with checksum 0x%x is on addon list\n",
          v22->pakFilename.data,
          v22->checksum);
      }
    }
    else
    {
      p_next = &v21->next;
    }
  }
  if ( this->addonChecksums.list )
    Memory::Free(this->addonChecksums.list);
  this->addonChecksums.list = 0;
  this->addonChecksums.num = 0;
  this->addonChecksums.size = 0;
  if ( this->restartChecksums.num )
  {
    v23 = this->searchPaths == 0;
    args.argv[23] = (char *)&this->searchPaths;
    if ( !v23 )
    {
      do
      {
        v24 = args.argv[23];
        v25 = *(char **)args.argv[23];
        v26 = **(_DWORD **)args.argv[23];
        args.argv[14] = *(char **)args.argv[23];
        if ( v26 && (v27 = this->restartChecksums.num, v28 = 0, v27 > 0) )
        {
          v29 = *(_DWORD *)(v26 + 36);
          v30 = this->restartChecksums.list;
          while ( *v30 != v29 )
          {
            ++v28;
            ++v30;
            if ( v28 >= v27 )
              goto LABEL_47;
          }
          if ( v28 == -1 )
          {
LABEL_47:
            v25 = args.argv[14];
            goto LABEL_48;
          }
          if ( v28 )
          {
            if ( !*((_DWORD *)args.argv[14] + 2) )
            {
              if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
              {
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "found pure checksum %x at index %d, but the end of search path is reached\n",
                  *(_DWORD *)(*(_DWORD *)args.argv[14] + 36),
                  v28);
                args.argv[15] = 0;
                args.argv[17] = (char *)20;
                args.argv[16] = (char *)&args.argv[18];
                LOBYTE(args.argv[18]) = 0;
                idStr::FreeData((idStr *)&args.argv[15]);
                v59 = 0;
                v32 = this->serverPaks.num <= 0;
                args.argv[15] = 0;
                args.argv[17] = (char *)20;
                args.argv[16] = (char *)&args.argv[18];
                LOBYTE(args.argv[18]) = 0;
                args.argv[14] = 0;
                if ( !v32 )
                {
                  do
                  {
                    v60 = va("%p ", this->serverPaks.list[(_DWORD)v59]);
                    v61 = (char *)v60;
                    if ( v60 )
                    {
                      v62 = &args.argv[15][strlen(v60)];
                      if ( (int)(v62 + 1) > (int)args.argv[17] )
                        idStr::ReAllocate((idStr *)&args.argv[15], (int)(v62 + 1), 1);
                      v63 = *v61;
                      v64 = 0;
                      if ( *v61 )
                      {
                        do
                        {
                          v65 = &args.argv[16][v64++];
                          v65[(unsigned int)args.argv[15]] = v63;
                          v63 = v61[v64];
                        }
                        while ( v63 );
                        v59 = args.argv[14];
                      }
                      args.argv[15] = v62;
                      args.argv[16][(unsigned int)v62] = 0;
                    }
                    v32 = (int)++v59 < this->serverPaks.num;
                    args.argv[14] = v59;
                  }
                  while ( v32 );
                }
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "%d pure paks - %s \n",
                  this->serverPaks.num,
                  args.argv[16]);
                idStr::FreeData((idStr *)&args.argv[15]);
                v66 = 0;
                v32 = this->restartChecksums.num <= 0;
                args.argv[15] = 0;
                args.argv[17] = (char *)20;
                args.argv[16] = (char *)&args.argv[18];
                LOBYTE(args.argv[18]) = 0;
                args.argv[14] = 0;
                if ( !v32 )
                {
                  do
                  {
                    v67 = va("%x ", this->restartChecksums.list[(_DWORD)v66]);
                    v68 = (char *)v67;
                    if ( v67 )
                    {
                      v69 = &args.argv[15][strlen(v67)];
                      if ( (int)(v69 + 1) > (int)args.argv[17] )
                        idStr::ReAllocate((idStr *)&args.argv[15], (int)(v69 + 1), 1);
                      v70 = *v68;
                      v71 = 0;
                      if ( *v68 )
                      {
                        do
                        {
                          v72 = &args.argv[16][v71++];
                          v72[(unsigned int)args.argv[15]] = v70;
                          v70 = v68[v71];
                        }
                        while ( v70 );
                        v66 = args.argv[14];
                      }
                      args.argv[15] = v69;
                      args.argv[16][(unsigned int)v69] = 0;
                    }
                    v32 = (int)++v66 < this->restartChecksums.num;
                    args.argv[14] = v66;
                  }
                  while ( v32 );
                }
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "%d paks left - %s\n",
                  this->restartChecksums.num,
                  args.argv[16]);
                idStr::FreeData((idStr *)&args.argv[15]);
                v24 = args.argv[23];
              }
              (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
                common.type,
                "Failed to restart with pure mode restrictions for server connect");
            }
            for ( j = *(_DWORD *)(*(_DWORD *)v24 + 8); *(_DWORD *)(j + 8); j = *(_DWORD *)(j + 8) )
              ;
            *(_DWORD *)(j + 8) = *(_DWORD *)v24;
            *(_DWORD *)v24 = *(_DWORD *)(*(_DWORD *)v24 + 8);
            *(_DWORD *)(*(_DWORD *)(j + 8) + 8) = 0;
          }
          else
          {
            if ( !this->serverPaks.list )
            {
              granularity = this->serverPaks.granularity;
              if ( granularity > 0 )
              {
                if ( granularity != this->serverPaks.size )
                {
                  v32 = granularity < this->serverPaks.num;
                  this->serverPaks.size = granularity;
                  if ( v32 )
                    this->serverPaks.num = granularity;
                  this->serverPaks.list = (pack_t **)Memory::Allocate(4 * granularity);
                  for ( k = 0; k < this->serverPaks.num; ++k )
                    this->serverPaks.list[k] = *(pack_t **)(4 * k);
                }
              }
              else
              {
                this->serverPaks.list = 0;
                this->serverPaks.num = 0;
                this->serverPaks.size = 0;
              }
            }
            v48 = this->serverPaks.num;
            size = this->serverPaks.size;
            if ( v48 == size )
            {
              if ( !this->serverPaks.granularity )
                this->serverPaks.granularity = 16;
              v50 = size
                  + this->serverPaks.granularity
                  - (size + this->serverPaks.granularity) % this->serverPaks.granularity;
              if ( v50 > 0 )
              {
                if ( v50 != this->serverPaks.size )
                {
                  v51 = this->serverPaks.list;
                  this->serverPaks.size = v50;
                  if ( v50 < v48 )
                    this->serverPaks.num = v50;
                  this->serverPaks.list = (pack_t **)Memory::Allocate(4 * v50);
                  for ( m = 0; m < this->serverPaks.num; ++m )
                    this->serverPaks.list[m] = v51[m];
                  if ( v51 )
                    Memory::Free(v51);
                }
              }
              else
              {
                if ( this->serverPaks.list )
                  Memory::Free(this->serverPaks.list);
                this->serverPaks.list = 0;
                this->serverPaks.num = 0;
                this->serverPaks.size = 0;
              }
            }
            this->serverPaks.list[this->serverPaks.num++] = *(pack_t **)args.argv[14];
            v53 = this->restartChecksums.num;
            if ( v53 > 0 )
            {
              v54 = v53 - 1;
              v55 = 0;
              for ( this->restartChecksums.num = v54; v55 < this->restartChecksums.num; *v58 = v57 )
              {
                v56 = this->restartChecksums.list;
                v57 = v56[v55 + 1];
                v58 = &v56[v55++];
              }
            }
            if ( !this->restartChecksums.num )
              break;
            args.argv[23] = (char *)(*(_DWORD *)args.argv[23] + 8);
            v24 = args.argv[23];
          }
        }
        else
        {
LABEL_48:
          v24 = v25 + 8;
          args.argv[23] = v25 + 8;
        }
      }
      while ( *(_DWORD *)v24 );
    }
    if ( this->restartChecksums.num )
    {
      if ( idFileSystemLocal::fs_debug.internalVar->integerValue )
      {
        v31 = 0;
        args.argv[15] = 0;
        args.argv[17] = (char *)20;
        args.argv[16] = (char *)&args.argv[18];
        LOBYTE(args.argv[18]) = 0;
        idStr::FreeData((idStr *)&args.argv[15]);
        v32 = this->serverPaks.num <= 0;
        args.argv[15] = 0;
        args.argv[17] = (char *)20;
        args.argv[16] = (char *)&args.argv[18];
        LOBYTE(args.argv[18]) = 0;
        args.argv[14] = 0;
        if ( !v32 )
        {
          do
          {
            v33 = va("%p ", this->serverPaks.list[(_DWORD)v31]);
            v34 = (char *)v33;
            if ( v33 )
            {
              v35 = &args.argv[15][strlen(v33)];
              if ( (int)(v35 + 1) > (int)args.argv[17] )
                idStr::ReAllocate((idStr *)&args.argv[15], (int)(v35 + 1), 1);
              v36 = *v34;
              v37 = 0;
              if ( *v34 )
              {
                do
                {
                  v38 = &args.argv[16][v37++];
                  v38[(unsigned int)args.argv[15]] = v36;
                  v36 = v34[v37];
                }
                while ( v36 );
                v31 = args.argv[14];
              }
              args.argv[15] = v35;
              args.argv[16][(unsigned int)v35] = 0;
            }
            v32 = (int)++v31 < this->serverPaks.num;
            args.argv[14] = v31;
          }
          while ( v32 );
        }
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%d pure paks - %s \n",
          this->serverPaks.num,
          args.argv[16]);
        idStr::FreeData((idStr *)&args.argv[15]);
        v39 = 0;
        v32 = this->restartChecksums.num <= 0;
        args.argv[15] = 0;
        args.argv[17] = (char *)20;
        args.argv[16] = (char *)&args.argv[18];
        LOBYTE(args.argv[18]) = 0;
        args.argv[14] = 0;
        if ( !v32 )
        {
          do
          {
            v40 = va("%x ", this->restartChecksums.list[(_DWORD)v39]);
            v41 = (char *)v40;
            if ( v40 )
            {
              v42 = &args.argv[15][strlen(v40)];
              if ( (int)(v42 + 1) > (int)args.argv[17] )
                idStr::ReAllocate((idStr *)&args.argv[15], (int)(v42 + 1), 1);
              v43 = *v41;
              v44 = 0;
              if ( *v41 )
              {
                do
                {
                  v45 = &args.argv[16][v44++];
                  v45[(unsigned int)args.argv[15]] = v43;
                  v43 = v41[v44];
                }
                while ( v43 );
                v39 = args.argv[14];
              }
              args.argv[15] = v42;
              args.argv[16][(unsigned int)v42] = 0;
            }
            v32 = (int)++v39 < this->restartChecksums.num;
            args.argv[14] = v39;
          }
          while ( v32 );
        }
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%d paks left - %s\n",
          this->restartChecksums.num,
          args.argv[16]);
        idStr::FreeData((idStr *)&args.argv[15]);
      }
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "Failed to restart with pure mode restrictions for server connect");
    }
    this->gamePakChecksum = this->restartGamePakChecksum;
  }
  cmdSystem->AddCommand(
    cmdSystem,
    "dir",
    idFileSystemLocal::Dir_f,
    2,
    "lists a folder",
    idCmdSystem::ArgCompletion_FileName);
  cmdSystem->AddCommand(cmdSystem, "dirtree", idFileSystemLocal::DirTree_f, 2, "lists a folder with subfolders", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "path",
    (void (__cdecl *)(const idCmdArgs *))idFileSystemLocal::Path_f,
    2,
    "lists search paths",
    0);
  cmdSystem->AddCommand(cmdSystem, "touchFile", idFileSystemLocal::TouchFile_f, 2, "touches a file", 0);
  cmdSystem->AddCommand(cmdSystem, "touchFileList", idFileSystemLocal::TouchFileList_f, 2, "touches a list of files", 0);
  idFileSystemLocal::Path_f();
  (*(void (__cdecl **)(netadrtype_t, const char *, idCmdArgs *))(*(_DWORD *)common.type + 124))(
    common.type,
    "file system initialized.\n",
    &args);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::Init(void)
void __thiscall idFileSystemLocal::Init(idFileSystemLocal *this)
{
  const char *v2; // eax
  const char *v3; // eax
  const char *KeyValue; // eax

  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(
    common.type,
    "fs_basepath",
    0);
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(
    common.type,
    "fs_savepath",
    0);
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(
    common.type,
    "fs_cdpath",
    0);
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(
    common.type,
    "fs_devpath",
    0);
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(common.type, "fs_game", 0);
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(
    common.type,
    "fs_game_base",
    0);
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(
    common.type,
    "fs_copyfiles",
    0);
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(
    common.type,
    "fs_restrict",
    0);
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(
    common.type,
    "fs_searchAddons",
    0);
  (*(void (__thiscall **)(netadrtype_t, const char *, _DWORD))(*(_DWORD *)common.type + 32))(
    common.type,
    "fs_importpath",
    0);
  if ( !*idFileSystemLocal::fs_basepath.internalVar->value )
  {
    v2 = Sys_DefaultBasePath();
    idFileSystemLocal::fs_basepath.internalVar->InternalSetString(idFileSystemLocal::fs_basepath.internalVar, v2);
  }
  if ( !*idFileSystemLocal::fs_savepath.internalVar->value )
  {
    v3 = Sys_DefaultSavePath();
    idFileSystemLocal::fs_savepath.internalVar->InternalSetString(idFileSystemLocal::fs_savepath.internalVar, v3);
  }
  if ( !*idFileSystemLocal::fs_cdpath.internalVar->value )
  {
    KeyValue = PBsdk_GetKeyValue();
    idFileSystemLocal::fs_cdpath.internalVar->InternalSetString(idFileSystemLocal::fs_cdpath.internalVar, KeyValue);
  }
  if ( !*idFileSystemLocal::fs_devpath.internalVar->value )
    idFileSystemLocal::fs_devpath.internalVar->InternalSetString(
      idFileSystemLocal::fs_devpath.internalVar,
      idFileSystemLocal::fs_savepath.internalVar->value);
  idFileSystemLocal::Startup(this);
  this->StartBackgroundDownloadThread(this);
  idStr::operator=(&this->currentAssetLog, "assetlogs/default");
  idStr::operator=(&this->currentAssetLogUnfiltered, "assetlogs/default");
  if ( this->ReadFile(this, "default.cfg", 0, 0) <= 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "Couldn't load default.cfg  -  Check your working folder.");
}

// FUNC: public: virtual void __thiscall idFileSystemLocal::Restart(void)
void __usercall idFileSystemLocal::Restart(idFileSystemLocal *this@<ecx>, int a2@<ebx>, int a3@<ebp>, int a4@<edi>)
{
  this->Shutdown(this, 1);
  idFileSystemLocal::Startup(this, a2, a3, a4, (int)this);
  if ( this->ReadFile(this, "default.cfg", 0, 0) <= 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
      common.type,
      "Couldn't load default.cfg  -  Check your working folder.");
}

// FUNC: public: void __thiscall idAsyncClient::WriteDemoHeader(class idFile *)const
void __thiscall idAsyncClient::WriteDemoHeader(idAsyncClient *this, idFile *file)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  const usercmd_t *v9; // ebx
  int v10; // ebp
  int v11; // [esp+5Ch] [ebp-4h]
  usercmd_t (*filea)[32]; // [esp+64h] [ebp+4h]

  file->WriteInt(file, this->clientDataChecksum);
  file->WriteInt(file, this->clientTime);
  file->WriteInt(file, this->clientId);
  file->WriteInt(file, this->clientNum);
  file->WriteInt(file, this->clientPrediction);
  file->WriteInt(file, this->clientPredictTime);
  file->WriteInt(file, this->lastConnectTime);
  v4 = file->WriteInt(file, this->serverAddress.type);
  LOBYTE(v4) = this->serverAddress.ip[0];
  v5 = file->WriteUnsignedChar(file, v4);
  LOBYTE(v5) = this->serverAddress.ip[1];
  v6 = file->WriteUnsignedChar(file, v5);
  LOBYTE(v6) = this->serverAddress.ip[2];
  v7 = file->WriteUnsignedChar(file, v6);
  LOBYTE(v7) = this->serverAddress.ip[3];
  v8 = file->WriteUnsignedChar(file, v7);
  LOWORD(v8) = this->serverAddress.port;
  file->WriteUnsignedShort(file, v8);
  file->WriteInt(file, this->serverId);
  file->WriteInt(file, this->serverChallenge);
  file->WriteInt(file, this->serverMessageSequence);
  file->WriteInt(file, this->snapshotSequence);
  file->WriteInt(file, this->snapshotGameFrame);
  file->WriteInt(file, this->snapshotGameTime);
  file->WriteInt(file, this->gameInitId);
  file->WriteInt(file, this->gameFrame);
  file->WriteInt(file, this->gameTime);
  file->WriteInt(file, this->gameTimeResidual);
  filea = this->userCmds;
  v11 = 32;
  do
  {
    v9 = (const usercmd_t *)filea;
    v10 = 256;
    do
    {
      idAsyncClient::WriteDemoUsercmd(this, file, v9);
      v9 += 32;
      --v10;
    }
    while ( v10 );
    filea = (usercmd_t (*)[32])((char *)filea + 40);
    --v11;
  }
  while ( v11 );
  idMsgChannel::Save(&this->channel, file);
}
