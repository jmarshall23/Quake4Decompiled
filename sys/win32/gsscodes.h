
// FUNC: public: virtual bool __thiscall CGSS_NormalFileSystem::fopen(char const *,char const *)
bool __thiscall CGSS_NormalFileSystem::fopen(CGSS_NormalFileSystem *this, const char *filenameIn, const char *mode)
{
  const char *v3; // eax
  char v5; // cl
  int i; // esi
  idSys *v7; // ecx
  _iobuf *v8; // eax
  char filename[128]; // [esp+8h] [ebp-80h] BYREF

  v3 = filenameIn;
  v5 = *filenameIn;
  for ( i = 0; v5; ++i )
  {
    v3[filename - filenameIn] = v5;
    v5 = *++v3;
  }
  v7 = sys;
  filename[i] = 0;
  v8 = v7->FOpen(v7, filename, mode);
  this->mFH = v8;
  return v8 != 0;
}

// FUNC: public: virtual int __thiscall CGSS_NormalFileSystem::fseek(long,int)
int __thiscall CGSS_NormalFileSystem::fseek(CGSS_NormalFileSystem *this, int offset, int origin)
{
  return sys->FSeek(sys, this->mFH, offset, origin);
}

// FUNC: public: virtual long __thiscall CGSS_NormalFileSystem::ftell(void)
int __thiscall CGSS_NormalFileSystem::ftell(CGSS_NormalFileSystem *this)
{
  return sys->FTell(sys, this->mFH);
}

// FUNC: public: virtual unsigned int __thiscall CGSS_NormalFileSystem::fread(void *,unsigned int,unsigned int)
int __thiscall CGSS_NormalFileSystem::fread(CGSS_NormalFileSystem *this, void *buffer, int size, int count)
{
  return sys->FRead(sys, buffer, size, count, this->mFH);
}

// FUNC: public: virtual bool __thiscall CGSS_NormalFileSystem::fclose(void)
char __thiscall CGSS_NormalFileSystem::fclose(CGSS_NormalFileSystem *this)
{
  sys->FClose(sys, this->mFH);
  this->mFH = 0;
  return 1;
}
