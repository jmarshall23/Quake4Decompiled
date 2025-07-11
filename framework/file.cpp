
// FUNC: public: virtual void __thiscall idFile_Common::Rewind(void)
void __thiscall idFile_Common::Rewind(idFile_Common *this)
{
  this->Seek(this, 0, FS_SEEK_SET);
}

// FUNC: public: virtual int __thiscall idFile_Common::VPrintf(char const *,char *)
int __thiscall idFile_Common::VPrintf(idFile_Common *this, char *fmt, char *args)
{
  int v4; // eax
  char dest[4096]; // [esp+4h] [ebp-1000h] BYREF

  v4 = idStr::vsnPrintf(dest, 4095, fmt, args);
  return this->Write(this, dest, v4);
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadUnsignedInt(unsigned int &)
int __thiscall idFile_Common::ReadUnsignedInt(idFile_Common *this, unsigned int *value)
{
  int v2; // edi

  v2 = this->Read(this, value, 4);
  *value = LittleLong(*value);
  return v2;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadShort(short &)
int __thiscall idFile_Common::ReadShort(idFile_Common *this, unsigned __int16 *value)
{
  int v2; // edi

  v2 = this->Read(this, value, 2);
  *value = LittleShort(*value);
  return v2;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadUnsignedChar(unsigned char &)
int __thiscall idFile_Common::ReadUnsignedChar(idFile_Common *this, unsigned __int8 *value)
{
  return this->Read(this, value, 1);
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadFloat(float &)
int __thiscall idFile_Common::ReadFloat(idFile_Common *this, float *value)
{
  int v2; // edi

  v2 = this->Read(this, value, 4);
  *value = LittleFloat(*value);
  return v2;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadBool(bool &)
int __thiscall idFile_Common::ReadBool(idFile_Common *this, bool *value)
{
  int result; // eax
  unsigned __int8 c; // [esp+5h] [ebp-1h] BYREF

  c = HIBYTE(this);
  result = this->ReadUnsignedChar(this, &c);
  *value = c != 0;
  return result;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadVec2(class idVec2 &)
int __thiscall idFile_Common::ReadVec2(idFile_Common *this, idVec2 *vec)
{
  int v2; // edi

  v2 = this->Read(this, vec, 8);
  LittleRevBytes(vec, 4, 2);
  return v2;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadVec3(class idVec3 &)
int __thiscall idFile_Common::ReadVec3(idFile_Common *this, idVec3 *vec)
{
  int v2; // edi

  v2 = this->Read(this, vec, 12);
  LittleRevBytes(vec, 4, 3);
  return v2;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadVec4(class idVec4 &)
int __thiscall idFile_Common::ReadVec4(idFile_Common *this, idVec4 *vec)
{
  int v2; // edi

  v2 = this->Read(this, vec, 16);
  LittleRevBytes(vec, 4, 4);
  return v2;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadVec5(class idVec5 &)
int __thiscall idFile_Common::ReadVec5(idFile_Common *this, idVec5 *vec)
{
  int v2; // edi

  v2 = this->Read(this, vec, 20);
  LittleRevBytes(vec, 4, 5);
  return v2;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadVec6(class idVec6 &)
int __thiscall idFile_Common::ReadVec6(idFile_Common *this, idVec6 *vec)
{
  int v2; // edi

  v2 = this->Read(this, vec, 24);
  LittleRevBytes(vec, 4, 6);
  return v2;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadMat3(class idMat3 &)
int __thiscall idFile_Common::ReadMat3(idFile_Common *this, idMat3 *mat)
{
  int v2; // edi

  v2 = this->Read(this, mat, 36);
  LittleRevBytes(mat, 4, 9);
  return v2;
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteInt(int)
int __thiscall idFile_Common::WriteInt(idFile_Common *this, int value)
{
  int v3; // eax
  idFile_Common_vtbl *v4; // edx

  v3 = LittleLong(value);
  v4 = this->__vftable;
  value = v3;
  return v4->Write(this, &value, 4);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteUnsignedShort(unsigned short)
int __thiscall idFile_Common::WriteUnsignedShort(idFile_Common *this, int value)
{
  int v3; // eax
  idFile_Common_vtbl *v4; // edx

  LOWORD(v3) = LittleShort(value);
  v4 = this->__vftable;
  value = v3;
  return v4->Write(this, &value, 2);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteChar(char)
int __thiscall idFile_Common::WriteChar(idFile_Common *this, unsigned __int8 value)
{
  return this->Write(this, &value, 1);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteFloat(float)
int __thiscall idFile_Common::WriteFloat(idFile_Common *this, float value)
{
  value = LittleFloat(value);
  return this->Write(this, &value, 4);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteBool(bool)
int __thiscall idFile_Common::WriteBool(idFile_Common *this, int value)
{
  return this->WriteUnsignedChar(this, value);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteString(char const *)
int __thiscall idFile_Common::WriteString(idFile_Common *this, const char *value)
{
  unsigned int v3; // edi

  v3 = strlen(value);
  this->WriteInt(this, v3);
  return this->Write(this, value, v3);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteVec2(class idVec2 const &)
int __thiscall idFile_Common::WriteVec2(idFile_Common *this, const idVec2 *vec)
{
  float y; // edx
  idVec2 v; // [esp+4h] [ebp-8h] BYREF

  y = vec->y;
  v.x = vec->x;
  v.y = y;
  LittleRevBytes(&v, 4, 2);
  return this->Write(this, &v, 8);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteVec3(class idVec3 const &)
int __thiscall idFile_Common::WriteVec3(idFile_Common *this, const idVec3 *vec)
{
  float y; // edx
  float z; // eax
  idVec3 v; // [esp+4h] [ebp-Ch] BYREF

  y = vec->y;
  z = vec->z;
  v.x = vec->x;
  v.y = y;
  v.z = z;
  LittleRevBytes(&v, 4, 3);
  return this->Write(this, &v, 12);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteVec4(class idVec4 const &)
int __thiscall idFile_Common::WriteVec4(idFile_Common *this, const idVec4 *vec)
{
  float y; // edx
  float z; // ecx
  float w; // edx
  idVec4 v; // [esp+4h] [ebp-10h] BYREF

  y = vec->y;
  v.x = vec->x;
  z = vec->z;
  v.y = y;
  w = vec->w;
  v.z = z;
  v.w = w;
  LittleRevBytes(&v, 4, 4);
  return this->Write(this, &v, 16);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteVec5(class idVec5 const &)
int __thiscall idFile_Common::WriteVec5(idFile_Common *this, const idVec5 *vec)
{
  float y; // edx
  float z; // ecx
  float s; // edx
  float t; // eax
  idVec5 v; // [esp+4h] [ebp-14h] BYREF

  y = vec->y;
  v.x = vec->x;
  z = vec->z;
  v.y = y;
  s = vec->s;
  t = vec->t;
  v.z = z;
  v.s = s;
  v.t = t;
  LittleRevBytes(&v, 4, 5);
  return this->Write(this, &v, 20);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteVec6(class idVec6 const &)
int __thiscall idFile_Common::WriteVec6(idFile_Common *this, const idVec6 *vec)
{
  float v3; // edx
  float v4; // ecx
  float v5; // edx
  float v6; // ecx
  float v7; // edx
  idVec6 v; // [esp+4h] [ebp-18h] BYREF

  v3 = vec->p[1];
  v.p[0] = vec->p[0];
  v4 = vec->p[2];
  v.p[1] = v3;
  v5 = vec->p[3];
  v.p[2] = v4;
  v6 = vec->p[4];
  v.p[3] = v5;
  v7 = vec->p[5];
  v.p[4] = v6;
  v.p[5] = v7;
  LittleRevBytes(&v, 4, 6);
  return this->Write(this, &v, 24);
}

// FUNC: public: virtual int __thiscall idFile_Common::WriteMat3(class idMat3 const &)
int __thiscall idFile_Common::WriteMat3(idFile_Common *this, const idMat3 *mat)
{
  idMat3 v; // [esp+Ch] [ebp-24h] BYREF

  qmemcpy(&v, mat, sizeof(v));
  LittleRevBytes(&v, 4, 9);
  return this->Write(this, &v, 36);
}

// FUNC: public: virtual void __thiscall idFile_Common::WriteNumericStructArray(int,int * const,int,unsigned char *,char const *)
void __thiscall idFile_Common::WriteNumericStructArray(
        idFile_Common *this,
        int numStructElements,
        int *tokenSubTypeStructElements,
        int arrayCount,
        unsigned __int8 *arrayStorage,
        const char *prepend)
{
  int i; // ebx
  int v9; // [esp+14h] [ebp-4h]

  if ( arrayCount > 0 )
  {
    v9 = arrayCount;
    do
    {
      this->WriteFloatString(this, prepend);
      for ( i = 0; i < numStructElements; arrayStorage += 4 )
      {
        if ( SLOBYTE(tokenSubTypeStructElements[i]) >= 0 )
          this->WriteFloatString(this, "%u ", *(_DWORD *)arrayStorage);
        else
          this->WriteFloatString(this, "%f ", *(float *)arrayStorage);
        ++i;
      }
      this->WriteFloatString(this, "\n");
      --v9;
    }
    while ( v9 );
  }
}

// FUNC: public: virtual void __thiscall idFile_Common::WriteSyncId(void)
void __thiscall idFile_Common::WriteSyncId(idFile_Common *this)
{
  this->WriteInt(this, 518508557);
}

// FUNC: public: virtual void __thiscall idFile_Common::ReadSyncId(char const *,char const *)
void __thiscall idFile_Common::ReadSyncId(idFile_Common *this, const char *detail, const char *classname)
{
  int v3; // edx
  int num; // [esp+4h] [ebp-4h] BYREF

  num = (int)this;
  this->ReadInt(this, &num);
  if ( num != 518508557 )
  {
    v3 = *(_DWORD *)common.type;
    if ( classname )
      (*(void (**)(netadrtype_t, const char *, ...))(v3 + 152))(
        common.type,
        "File synchronisation problem: %s in class %s",
        detail,
        classname);
    else
      (*(void (**)(netadrtype_t, const char *, ...))(v3 + 152))(common.type, "File synchronisation problem: %s", detail);
  }
}

// FUNC: public: virtual int __thiscall idFile_Memory::Tell(void)
int __thiscall idFile_Memory::Tell(idFile_Memory *this)
{
  return this->curPtr - this->filePtr;
}

// FUNC: public: virtual void __thiscall idFile_Memory::Rewind(void)
void __thiscall idFile_Memory::Rewind(idFile_Memory *this)
{
  idFile_Memory_vtbl *v1; // eax

  v1 = this->__vftable;
  this->mode = 1;
  ((void (__stdcall *)(_DWORD, int))v1->Seek)(0, 2);
}

// FUNC: public: virtual void __thiscall idFile_Memory::MakeReadOnly(void)
void __thiscall idFile_Memory::MakeReadOnly(idFile_Memory *this)
{
  idFile_Memory_vtbl *v1; // eax

  v1 = this->__vftable;
  this->mode = 1;
  ((void (*)(void))v1->Rewind)();
}

// FUNC: public: virtual void __thiscall idFile_Memory::Clear(bool)
void __thiscall idFile_Memory::Clear(idFile_Memory *this, bool freeMemory)
{
  char *filePtr; // [esp-4h] [ebp-Ch]

  this->fileSize = 0;
  this->granularity = 0x4000;
  if ( freeMemory )
  {
    filePtr = this->filePtr;
    this->allocated = 0;
    Mem_Free(filePtr);
    this->filePtr = 0;
    this->curPtr = 0;
  }
  else
  {
    this->curPtr = this->filePtr;
  }
}

// FUNC: public: void __thiscall idFile_Memory::SetData(char const *,int)
void __thiscall idFile_Memory::SetData(idFile_Memory *this, char *data, int length)
{
  this->maxSize = 0;
  this->allocated = 0;
  this->fileSize = length;
  this->granularity = 0x4000;
  this->mode = 1;
  this->filePtr = data;
  this->curPtr = data;
}

// FUNC: public: virtual int __thiscall idFile_BitMsg::Seek(long,enum fsOrigin_t)
int __thiscall idFile_BitMsg::Seek(idFile_Common *this, int offset, fsOrigin_t origin)
{
  return -1;
}

// FUNC: public: virtual void __thiscall idFile_Permanent::ForceFlush(void)
void __thiscall idFile_Permanent::ForceFlush(idFile_Permanent *this)
{
  sys->SetVBuf(sys, this->o, 0, 4, 0);
}

// FUNC: public: virtual void __thiscall idFile_Permanent::Flush(void)
void __thiscall idFile_Permanent::Flush(idFile_Permanent *this)
{
  sys->FFlush(sys, this->o);
}

// FUNC: public: virtual int __thiscall idFile_Permanent::Tell(void)
int __thiscall idFile_Permanent::Tell(idFile_Permanent *this)
{
  return sys->FTell(sys, this->o);
}

// FUNC: public: virtual unsigned int __thiscall idFile_Permanent::Timestamp(void)
int __thiscall idFile_Permanent::Timestamp(idFile_Permanent *this)
{
  return sys->FileTimeStamp(sys, this->o);
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteInt(int)
int __thiscall idFile_ASCII::WriteInt(idFile_ASCII *this, int value)
{
  idFile_ASCII_vtbl *v3; // eax

  v3 = this->__vftable;
  ++this->inside;
  v3->WriteFloatString(this, "Integer: %d\r\n", value);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteUnsignedInt(unsigned int)
int __thiscall idFile_ASCII::WriteUnsignedInt(idFile_ASCII *this, unsigned int value)
{
  idFile_ASCII_vtbl *v3; // eax

  v3 = this->__vftable;
  ++this->inside;
  v3->WriteFloatString(this, "Unsigned: %u\r\n", value);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteShort(short)
int __thiscall idFile_ASCII::WriteShort(idFile_ASCII *this, __int16 value)
{
  idFile_ASCII_vtbl *v3; // eax

  v3 = this->__vftable;
  ++this->inside;
  v3->WriteFloatString(this, "Short: %d\r\n", value);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteUnsignedShort(unsigned short)
int __thiscall idFile_ASCII::WriteUnsignedShort(idFile_ASCII *this, unsigned __int16 value)
{
  idFile_ASCII_vtbl *v3; // eax

  v3 = this->__vftable;
  ++this->inside;
  v3->WriteFloatString(this, "Unsigned Short: %u\r\n", value);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteChar(char)
int __thiscall idFile_ASCII::WriteChar(idFile_ASCII *this, char value)
{
  idFile_ASCII_vtbl *v3; // eax

  v3 = this->__vftable;
  ++this->inside;
  v3->WriteFloatString(this, "Char: %d\r\n", value);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteUnsignedChar(unsigned char)
int __thiscall idFile_ASCII::WriteUnsignedChar(idFile_ASCII *this, unsigned __int8 value)
{
  idFile_ASCII_vtbl *v3; // eax

  v3 = this->__vftable;
  ++this->inside;
  v3->WriteFloatString(this, "Byte: %u\r\n", value);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteFloat(float)
int __thiscall idFile_ASCII::WriteFloat(idFile_ASCII *this, float value)
{
  idFile_ASCII_vtbl *v3; // eax

  v3 = this->__vftable;
  ++this->inside;
  v3->WriteFloatString(this, "Float: %f\r\n", value);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteBool(bool)
int __thiscall idFile_ASCII::WriteBool(idFile_ASCII *this, bool value)
{
  const char *v3; // eax

  ++this->inside;
  v3 = "true";
  if ( !value )
    v3 = "false";
  this->WriteFloatString(this, "Bool: %s\r\n", v3);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteString(char const *)
int __thiscall idFile_ASCII::WriteString(idFile_ASCII *this, const char *string)
{
  unsigned int v3; // kr00_4
  idFile_ASCII_vtbl *v4; // ecx

  v3 = strlen(string);
  v4 = this->__vftable;
  ++this->inside;
  v4->WriteFloatString(this, "String: len=%d %s\r\n", v3, string);
  --this->inside;
  return 0;
}

// FUNC: public: virtual void __thiscall idFile_ASCII::WriteNumericStructArray(int,int * const,int,unsigned char *,char const *)
void __thiscall idFile_ASCII::WriteNumericStructArray(
        idFile_ASCII *this,
        int numStructElements,
        int *tokenSubTypeStructElements,
        int arrayCount,
        unsigned __int8 *arrayStorage,
        const char *prepend)
{
  ;
}

// FUNC: public: virtual void __thiscall idFile_ASCII::WriteSyncId(void)
void __thiscall idFile_ASCII::WriteSyncId(idFile_ASCII *this)
{
  idFile_ASCII_vtbl *v2; // eax

  v2 = this->__vftable;
  ++this->inside;
  v2->WriteFloatString(this, "==========\r\n");
  --this->inside;
}

// FUNC: public: virtual int __thiscall idFile_InZip::Read(void *,int)
int __thiscall idFile_InZip::Read(idFile_InZip *this, void *buffer, int len)
{
  int CurrentFile; // esi

  CurrentFile = unzReadCurrentFile(this->z, buffer, len);
  fileSystem->AddToReadCount(fileSystem, CurrentFile);
  return CurrentFile;
}

// FUNC: public: virtual int __thiscall idFile_InZip::Tell(void)
int __thiscall idFile_InZip::Tell(idFile_InZip *this)
{
  return unztell(this->z);
}

// FUNC: public: virtual int __cdecl idFile_Common::Printf(char const *,...)
int idFile_Common::Printf(idFile_Common *this, char *fmt, ...)
{
  int v2; // kr00_4
  char *data; // edx
  char *v4; // ecx
  char v5; // al
  int v6; // esi
  idStr v8; // [esp+8h] [ebp-102Ch] BYREF
  char dest[4096]; // [esp+28h] [ebp-100Ch] BYREF
  int v10; // [esp+1030h] [ebp-4h]
  va_list argptr; // [esp+1040h] [ebp+Ch] BYREF

  va_start(argptr, fmt);
  idStr::vsnPrintf(dest, 4095, fmt, argptr);
  v8.data = v8.baseBuffer;
  v8.len = 0;
  v8.alloced = 20;
  v8.baseBuffer[0] = 0;
  v2 = strlen(dest);
  if ( v2 + 1 > 20 )
    idStr::ReAllocate(&v8, v2 + 1, 1);
  data = v8.data;
  v4 = dest;
  do
  {
    v5 = *v4;
    *data++ = *v4++;
  }
  while ( v5 );
  v8.len = v2;
  v10 = 0;
  idStr::Replace(&v8, "\n", "\r\n");
  v6 = this->Write(this, v8.data, v8.len);
  v10 = -1;
  idStr::FreeData(&v8);
  return v6;
}

// FUNC: public: virtual int __thiscall idFile_Common::ReadString(class idStr &)
int __thiscall idFile_Common::ReadString(idFile_Common *this, idStr *string)
{
  int v3; // edi
  int len; // [esp+Ch] [ebp-4h] BYREF

  this->ReadInt(this, &len);
  v3 = len;
  if ( len < 0 )
    return 0;
  if ( len + 1 > string->alloced )
    idStr::ReAllocate(string, len + 1, 1);
  string->len = v3;
  memset(string->data, 0x20u, v3);
  string->data[string->len] = 0;
  return this->Read(this, string->data, len);
}

// FUNC: public: __thiscall idFile_Memory::idFile_Memory(char const *,char const *,int)
void __thiscall idFile_Memory::idFile_Memory(idFile_Memory *this, char *name, char *data, int length)
{
  idStr *p_name; // ecx

  p_name = &this->name;
  this->__vftable = (idFile_Memory_vtbl *)&idFile_Memory::`vftable';
  p_name->len = 0;
  p_name->alloced = 20;
  p_name->data = p_name->baseBuffer;
  p_name->baseBuffer[0] = 0;
  idStr::operator=(p_name, name);
  this->fileSize = length;
  this->filePtr = data;
  this->curPtr = data;
  this->maxSize = 0;
  this->allocated = 0;
  this->granularity = 0x4000;
  this->mode = 1;
}

// FUNC: public: virtual __thiscall idFile_Memory::~idFile_Memory(void)
void __thiscall idFile_Memory::~idFile_Memory(idFile_Memory *this)
{
  char *filePtr; // eax

  this->__vftable = (idFile_Memory_vtbl *)&idFile_Memory::`vftable';
  filePtr = this->filePtr;
  if ( filePtr && this->allocated > 0 && !this->maxSize )
    Mem_Free(filePtr);
  idStr::FreeData(&this->name);
  this->__vftable = (idFile_Memory_vtbl *)&idFile::`vftable';
}

// FUNC: public: virtual int __thiscall idFile_Memory::Read(void *,int)
int __thiscall idFile_Memory::Read(idFile_Memory *this, void *buffer, int len)
{
  char *filePtr; // ecx
  int fileSize; // eax
  char *curPtr; // edx
  int v8; // edi

  if ( (this->mode & 1) != 0 )
  {
    filePtr = this->filePtr;
    fileSize = this->fileSize;
    curPtr = this->curPtr;
    v8 = len;
    if ( &curPtr[len] > &filePtr[fileSize] )
      v8 = (int)&filePtr[fileSize - (_DWORD)curPtr];
    SIMDProcessor->Memcpy(SIMDProcessor, buffer, curPtr, v8);
    this->curPtr += v8;
    return v8;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFile_Memory::Read: %s not opened in read mode",
      this->name.data);
    return 0;
  }
}

// FUNC: public: virtual int __thiscall idFile_Memory::Write(void const *,int)
int __thiscall idFile_Memory::Write(idFile_Memory *this, const void *buffer, int len)
{
  int allocated; // ebx
  int v6; // eax
  int v7; // edi
  void *v8; // ebx
  char *filePtr; // eax
  int fileSize; // eax

  if ( (this->mode & 2) == 0 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFile_Memory::Write: %s not opened in write mode",
      this->name.data);
    return 0;
  }
  allocated = this->allocated;
  v6 = this->curPtr - this->filePtr - allocated + len + 1;
  if ( v6 > 0 )
  {
    if ( this->maxSize )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "idFile_Memory::Write: exceeded maximum size %d",
        this->maxSize);
      return 0;
    }
    v7 = this->granularity * (v6 / this->granularity + 1);
    v8 = Mem_Alloc(v7 + allocated, 0xBu);
    if ( this->allocated )
      SIMDProcessor->Memcpy(SIMDProcessor, v8, this->filePtr, this->allocated);
    filePtr = this->filePtr;
    this->allocated += v7;
    this->curPtr += (_BYTE *)v8 - filePtr;
    if ( filePtr )
      Mem_Free(filePtr);
    this->filePtr = (char *)v8;
  }
  SIMDProcessor->Memcpy(SIMDProcessor, this->curPtr, buffer, len);
  this->fileSize += len;
  fileSize = this->fileSize;
  this->curPtr += len;
  this->filePtr[fileSize] = 0;
  return len;
}

// FUNC: public: virtual int __thiscall idFile_Memory::Seek(long,enum fsOrigin_t)
int __thiscall idFile_Memory::Seek(idFile_Memory *this, int offset, fsOrigin_t origin)
{
  char *curPtr; // edx
  char *filePtr; // eax

  if ( origin )
  {
    if ( origin == FS_SEEK_END )
    {
      this->curPtr = &this->filePtr[this->fileSize - offset];
    }
    else
    {
      if ( origin != FS_SEEK_SET )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "idFile_Memory::Seek: bad origin for %s\n",
          this->name.data);
        return -1;
      }
      this->curPtr = &this->filePtr[offset];
    }
  }
  else
  {
    this->curPtr += offset;
  }
  curPtr = this->curPtr;
  filePtr = this->filePtr;
  if ( curPtr >= filePtr )
  {
    filePtr += this->fileSize;
    if ( curPtr <= filePtr )
      return 0;
  }
  this->curPtr = filePtr;
  return -1;
}

// FUNC: public: __thiscall idFile_BitMsg::idFile_BitMsg(class idBitMsg &)
void __thiscall idFile_BitMsg::idFile_BitMsg(idFile_BitMsg *this, idBitMsg *msg)
{
  idStr *p_name; // ecx

  p_name = &this->name;
  this->__vftable = (idFile_BitMsg_vtbl *)&idFile_BitMsg::`vftable';
  p_name->len = 0;
  p_name->alloced = 20;
  p_name->data = p_name->baseBuffer;
  p_name->baseBuffer[0] = 0;
  idStr::operator=(p_name, "*unknown*");
  this->msg = msg;
  this->mode = 2;
}

// FUNC: public: __thiscall idFile_BitMsg::idFile_BitMsg(class idBitMsg const &)
void __thiscall idFile_BitMsg::idFile_BitMsg(idFile_BitMsg *this, idBitMsg *msg)
{
  idStr *p_name; // ecx

  p_name = &this->name;
  this->__vftable = (idFile_BitMsg_vtbl *)&idFile_BitMsg::`vftable';
  p_name->len = 0;
  p_name->alloced = 20;
  p_name->data = p_name->baseBuffer;
  p_name->baseBuffer[0] = 0;
  idStr::operator=(p_name, "*unknown*");
  this->msg = msg;
  this->mode = 1;
}

// FUNC: public: virtual __thiscall idFile_BitMsg::~idFile_BitMsg(void)
void __thiscall idFile_BitMsg::~idFile_BitMsg(idFile_BitMsg *this)
{
  this->__vftable = (idFile_BitMsg_vtbl *)&idFile_BitMsg::`vftable';
  idStr::FreeData(&this->name);
  this->__vftable = (idFile_BitMsg_vtbl *)&idFile::`vftable';
}

// FUNC: public: virtual int __thiscall idFile_BitMsg::Read(void *,int)
int __thiscall idFile_BitMsg::Read(idFile_BitMsg *this, void *buffer, int len)
{
  if ( (this->mode & 1) != 0 )
    return idBitMsg::ReadData(this->msg, buffer, len);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
    common.type,
    "idFile_BitMsg::Read: %s not opened in read mode",
    this->name.data);
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_BitMsg::Write(void const *,int)
int __thiscall idFile_BitMsg::Write(idFile_BitMsg *this, const void *buffer, int len)
{
  if ( (this->mode & 2) != 0 )
  {
    idBitMsg::WriteData(this->msg, buffer, len);
    return len;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFile_Memory::Write: %s not opened in write mode",
      this->name.data);
    return 0;
  }
}

// FUNC: public: virtual int __thiscall idFile_BitMsg::Length(void)
int __thiscall idFile_BitMsg::Length(idFile_BitMsg *this)
{
  return this->msg->curSize;
}

// FUNC: public: virtual int __thiscall idFile_BitMsg::Tell(void)
int __thiscall idFile_BitMsg::Tell(idFile_BitMsg *this)
{
  if ( (this->mode & 1) != 0 )
    return this->msg->readCount;
  else
    return this->msg->curSize;
}

// FUNC: public: __thiscall idFile_Permanent::idFile_Permanent(void)
void __thiscall idFile_Permanent::idFile_Permanent(idFile_Permanent *this)
{
  idStr *p_name; // ecx

  p_name = &this->name;
  this->__vftable = (idFile_Permanent_vtbl *)&idFile_Permanent::`vftable';
  p_name->len = 0;
  p_name->alloced = 20;
  p_name->data = p_name->baseBuffer;
  p_name->baseBuffer[0] = 0;
  this->fullPath.len = 0;
  this->fullPath.alloced = 20;
  this->fullPath.data = this->fullPath.baseBuffer;
  this->fullPath.baseBuffer[0] = 0;
  idStr::operator=(p_name, "invalid");
  this->o = 0;
  this->mode = 0;
  this->fileSize = 0;
  this->handleSync = 0;
}

// FUNC: public: virtual __thiscall idFile_Permanent::~idFile_Permanent(void)
void __thiscall idFile_Permanent::~idFile_Permanent(idFile_Permanent *this)
{
  _iobuf *o; // eax

  this->__vftable = (idFile_Permanent_vtbl *)&idFile_Permanent::`vftable';
  o = this->o;
  if ( o )
    sys->FClose(sys, o);
  idStr::FreeData(&this->fullPath);
  idStr::FreeData(&this->name);
  this->__vftable = (idFile_Permanent_vtbl *)&idFile::`vftable';
}

// FUNC: public: virtual int __thiscall idFile_Permanent::Read(void *,int)
int __thiscall idFile_Permanent::Read(idFile_Permanent *this, char *buffer, int len)
{
  int v6; // edi
  int v7; // eax
  int v8; // esi
  int buffera; // [esp+10h] [ebp+4h]

  if ( (this->mode & 1) == 0 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFile_Permanent::Read: %s not opened in read mode",
      this->name.data);
    return 0;
  }
  if ( !this->o )
    return 0;
  v6 = len;
  buffera = 0;
  if ( !len )
  {
LABEL_13:
    fileSystem->AddToReadCount(fileSystem, v6);
    return v6;
  }
  while ( 1 )
  {
    v7 = sys->FRead(sys, buffer, 1, v6, this->o);
    v8 = v7;
    if ( v7 )
    {
      if ( v7 == -1 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "idFile_Permanent::Read: -1 bytes read from %s",
          this->name.data);
      goto LABEL_11;
    }
    if ( buffera )
      break;
    buffera = 1;
LABEL_11:
    v6 -= v8;
    buffer += v8;
    if ( !v6 )
    {
      v6 = len;
      goto LABEL_13;
    }
  }
  fileSystem->AddToReadCount(fileSystem, len - v6);
  return len - v6;
}

// FUNC: public: virtual int __thiscall idFile_Permanent::Write(void const *,int)
int __thiscall idFile_Permanent::Write(idFile_Permanent *this, char *buffer, int len)
{
  int v6; // edi
  int i; // ebp
  int v8; // eax

  if ( (this->mode & 2) == 0 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idFile_Permanent::Write: %s not opened in write mode",
      this->name.data);
    return 0;
  }
  if ( !this->o )
    return 0;
  v6 = len;
  for ( i = 0; v6; buffer += v8 )
  {
    v8 = sys->FWrite(sys, buffer, 1, v6, this->o);
    if ( v8 )
    {
      if ( v8 == -1 )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "idFile_Permanent::Write: -1 bytes written to %s\n",
          this->name.data);
        return 0;
      }
    }
    else
    {
      if ( i )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "idFile_Permanent::Write: 0 bytes written to %s\n",
          this->name.data);
        return 0;
      }
      i = 1;
    }
    this->fileSize += v8;
    v6 -= v8;
  }
  if ( this->handleSync )
    sys->FFlush(sys, this->o);
  return len;
}

// FUNC: public: virtual int __thiscall idFile_Permanent::Seek(long,enum fsOrigin_t)
int __thiscall idFile_Permanent::Seek(idFile_Permanent *this, int offset, fsOrigin_t origin)
{
  int v4; // esi

  if ( origin )
  {
    if ( origin == FS_SEEK_END )
    {
      v4 = 2;
    }
    else if ( origin == FS_SEEK_SET )
    {
      v4 = 0;
    }
    else
    {
      v4 = 1;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
        common.type,
        "idFile_Permanent::Seek: bad origin for %s\n",
        this->name.data);
    }
  }
  else
  {
    v4 = 1;
  }
  return sys->FSeek(sys, this->o, offset, v4);
}

// FUNC: public: __thiscall idFile_ASCII::idFile_ASCII(void)
void __thiscall idFile_ASCII::idFile_ASCII(idFile_ASCII *this)
{
  idFile_Permanent::idFile_Permanent(this);
  this->__vftable = (idFile_ASCII_vtbl *)&idFile_ASCII::`vftable';
  this->inside = 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::Write(void const *,int)
int __thiscall idFile_ASCII::Write(idFile_ASCII *this, char *buffer, int len)
{
  idFile_ASCII_vtbl *v4; // eax
  int i; // edi

  if ( this->inside )
    return idFile_Permanent::Write(this, buffer, len);
  v4 = this->__vftable;
  this->inside = 1;
  v4->WriteFloatString(this, "len=%d  ", len);
  for ( i = 0; i < len; ++i )
    this->WriteFloatString(this, "%02x", (unsigned __int8)buffer[i]);
  this->WriteFloatString(this, "\r\n");
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteVec2(class idVec2 const &)
int __thiscall idFile_ASCII::WriteVec2(idFile_ASCII *this, const idVec2 *vec)
{
  ++this->inside;
  this->WriteFloatString(this, "Vec2: %f %f\r\n", vec->x, vec->y);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteVec3(class idVec3 const &)
int __thiscall idFile_ASCII::WriteVec3(idFile_ASCII *this, const idVec3 *vec)
{
  ++this->inside;
  this->WriteFloatString(this, "Vec3: %f %f %f\r\n", vec->x, vec->y, vec->z);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteVec4(class idVec4 const &)
int __thiscall idFile_ASCII::WriteVec4(idFile_ASCII *this, const idVec4 *vec)
{
  ++this->inside;
  this->WriteFloatString(this, "Vec4: %f %f %f %f\r\n", vec->x, vec->y, vec->z, vec->w);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteVec5(class idVec5 const &)
int __thiscall idFile_ASCII::WriteVec5(idFile_ASCII *this, const idVec5 *vec)
{
  ++this->inside;
  this->WriteFloatString(this, "Vec5: %f %f %f %f %f\r\n", vec->x, vec->y, vec->z, vec->s, vec->t);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteVec6(class idVec6 const &)
int __thiscall idFile_ASCII::WriteVec6(idFile_ASCII *this, const idVec6 *vec)
{
  ++this->inside;
  this->WriteFloatString(
    this,
    "Vec6: %f %f %f %f %f %f\r\n",
    vec->p[0],
    vec->p[1],
    vec->p[2],
    vec->p[3],
    vec->p[4],
    vec->p[5]);
  --this->inside;
  return 0;
}

// FUNC: public: virtual int __thiscall idFile_ASCII::WriteMat3(class idMat3 const &)
int __thiscall idFile_ASCII::WriteMat3(idFile_ASCII *this, const idMat3 *mat)
{
  ++this->inside;
  this->WriteFloatString(
    this,
    "Mat3: ( %f %f %f ) ( %f %f %f ) ( %f %f %f )\r\n",
    mat->mat[0].x,
    mat->mat[0].y,
    mat->mat[0].z,
    mat->mat[1].x,
    mat->mat[1].y,
    mat->mat[1].z,
    mat->mat[2].x,
    mat->mat[2].y,
    mat->mat[2].z);
  --this->inside;
  return 0;
}

// FUNC: public: __thiscall idFile_InZip::idFile_InZip(void)
void __thiscall idFile_InZip::idFile_InZip(idFile_InZip *this)
{
  idStr *p_name; // ecx

  p_name = &this->name;
  this->__vftable = (idFile_InZip_vtbl *)&idFile_InZip::`vftable';
  p_name->len = 0;
  p_name->alloced = 20;
  p_name->data = p_name->baseBuffer;
  p_name->baseBuffer[0] = 0;
  this->fullPath.len = 0;
  this->fullPath.alloced = 20;
  this->fullPath.data = this->fullPath.baseBuffer;
  this->fullPath.baseBuffer[0] = 0;
  idStr::operator=(p_name, "invalid");
  this->zipFilePos = 0;
  this->fileSize = 0;
  this->z = 0;
}

// FUNC: public: virtual __thiscall idFile_InZip::~idFile_InZip(void)
void __thiscall idFile_InZip::~idFile_InZip(idFile_InZip *this)
{
  this->__vftable = (idFile_InZip_vtbl *)&idFile_InZip::`vftable';
  unzCloseCurrentFile(this->z);
  unzClose(this->z);
  idStr::FreeData(&this->fullPath);
  idStr::FreeData(&this->name);
  this->__vftable = (idFile_InZip_vtbl *)&idFile::`vftable';
}

// FUNC: public: virtual int __thiscall idFile_InZip::Write(void const *,int)
int __thiscall idFile_InZip::Write(idFile_InZip *this, const void *buffer, int len)
{
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
    common.type,
    "idFile_InZip::Write: cannot write to the zipped file %s",
    this->name.data);
  return 0;
}

// FUNC: public: virtual void __thiscall idFile_InZip::ForceFlush(void)
void __thiscall idFile_InZip::ForceFlush(idFile_InZip *this)
{
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
    common.type,
    "idFile_InZip::ForceFlush: cannot flush the zipped file %s",
    this->name.data);
}

// FUNC: public: virtual void __thiscall idFile_InZip::Flush(void)
void __thiscall idFile_InZip::Flush(idFile_InZip *this)
{
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
    common.type,
    "idFile_InZip::Flush: cannot flush the zipped file %s",
    this->name.data);
}

// FUNC: public: virtual int __thiscall idFile_InZip::Seek(long,enum fsOrigin_t)
int __thiscall idFile_InZip::Seek(idFile_InZip *this, int offset, fsOrigin_t origin)
{
  int v5; // ebx
  void *v6; // esp
  int v7; // edi
  _BYTE v8[32792]; // [esp-800Ch] [ebp-801Ch] BYREF
  idFile_InZip *v9; // [esp+Ch] [ebp-4h]

  v9 = this;
  if ( origin )
  {
    if ( origin == FS_SEEK_END )
    {
      v5 = this->fileSize - offset;
    }
    else
    {
      if ( origin != FS_SEEK_SET )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "idFile_InZip::Seek: bad origin for %s\n",
          this->name.data);
        return -1;
      }
      v5 = offset;
    }
    unzSetCurrentFileInfoPosition(this->z, this->zipFilePos);
    unzOpenCurrentFile(this->z);
    if ( v5 <= 0 )
      return 0;
  }
  else
  {
    v5 = offset;
  }
  v6 = alloca(32784);
  v7 = 0;
  if ( v5 - 0x8000 > 0 )
  {
    while ( unzReadCurrentFile(v9->z, v8, 0x8000u) >= 0x8000 )
    {
      v7 += 0x8000;
      if ( v7 >= v5 - 0x8000 )
        return -(v5 != v7 + unzReadCurrentFile(v9->z, v8, v5 - v7));
    }
    return -1;
  }
  return -(v5 != v7 + unzReadCurrentFile(v9->z, v8, v5 - v7));
}

// FUNC: int __cdecl FS_WriteFloatString(char *,int,char const *,char *)
int __cdecl FS_WriteFloatString(char *buf, int max, const char *fmt, char *argPtr)
{
  int v4; // esi
  const char *v5; // ebx
  char v6; // al
  bool v7; // zf
  int v8; // eax
  const char *v9; // ebx
  int v10; // eax
  int v11; // eax
  const char *v12; // ebx
  char v13; // bl
  char v14; // bl
  char *v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // eax
  double v20; // [esp+0h] [ebp-6Ch]
  char *v21; // [esp+18h] [ebp-54h]
  char *v22; // [esp+1Ch] [ebp-50h]
  idStr format; // [esp+20h] [ebp-4Ch] BYREF
  idStr tmp; // [esp+40h] [ebp-2Ch] BYREF
  int v25; // [esp+68h] [ebp-4h]
  char fmta; // [esp+78h] [ebp+Ch]
  const char *fmtb; // [esp+78h] [ebp+Ch]

  v4 = 0;
  tmp.len = 0;
  tmp.alloced = 20;
  tmp.data = tmp.baseBuffer;
  tmp.baseBuffer[0] = 0;
  v25 = 0;
  format.len = 0;
  format.alloced = 20;
  format.data = format.baseBuffer;
  format.baseBuffer[0] = 0;
  v5 = fmt;
  v6 = *fmt;
  v7 = *fmt == 0;
  LOBYTE(v25) = 1;
  if ( !v7 )
  {
    v22 = argPtr - 4;
    v21 = argPtr - 8;
    do
    {
      if ( v6 == 37 )
      {
        idStr::operator=(&format, (char *)&entityFilter);
        fmta = *v5;
        if ( format.len + 2 > format.alloced )
          idStr::ReAllocate(&format, format.len + 2, 1);
        format.data[format.len] = fmta;
        v11 = format.len + 1;
        v12 = v5 + 1;
        for ( fmtb = v12; ; v12 = fmtb )
        {
          format.len = v11;
          format.data[v11] = 0;
          v13 = *v12;
          if ( (v13 < 48 || v13 > 57) && v13 != 46 && v13 != 45 && v13 != 43 && v13 != 35 )
            break;
          if ( format.len + 2 > format.alloced )
            idStr::ReAllocate(&format, format.len + 2, 1);
          format.data[format.len] = v13;
          v11 = format.len + 1;
          ++fmtb;
        }
        v14 = *fmtb;
        if ( format.len + 2 > format.alloced )
          idStr::ReAllocate(&format, format.len + 2, 1);
        format.data[format.len++] = v14;
        format.data[format.len] = 0;
        switch ( *fmtb )
        {
          case '%':
            v4 += idStr::snPrintf(&buf[v4], max - v4, format.data);
            break;
          case 'E':
          case 'G':
          case 'e':
          case 'f':
          case 'g':
            v22 += 8;
            v20 = *((double *)v21 + 1);
            v21 += 8;
            if ( format.len <= 2 )
            {
              v15 = va("%1.10f", v20);
              idStr::operator=(&tmp, v15);
              idStr::StripTrailing(&tmp, 0x30u);
              idStr::StripTrailing(&tmp, 0x2Eu);
              v16 = idStr::snPrintf(&buf[v4], max - v4, "%s", tmp.data);
              goto LABEL_30;
            }
            v4 += idStr::snPrintf(&buf[v4], max - v4, format.data, v20);
            break;
          case 'X':
          case 'd':
          case 'i':
          case 'o':
          case 'u':
          case 'x':
            v21 += 4;
            v22 += 4;
            v16 = idStr::snPrintf(&buf[v4], max - v4, format.data, *(_DWORD *)v22);
LABEL_30:
            v4 += v16;
            break;
          case 'c':
            v21 += 4;
            v17 = v22[4];
            v22 += 4;
            v18 = idStr::snPrintf(&buf[v4], max - v4, format.data, v17);
            goto LABEL_35;
          case 's':
            v21 += 4;
            v22 += 4;
            v18 = idStr::snPrintf(&buf[v4], max - v4, format.data, *(_DWORD *)v22);
LABEL_35:
            v4 += v18;
            break;
          default:
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
              common.type,
              "FS_WriteFloatString: invalid format %s",
              format.data);
            break;
        }
        v5 = fmtb + 1;
      }
      else if ( v6 == 92 )
      {
        v8 = v5[1];
        v9 = v5 + 1;
        switch ( v8 )
        {
          case '\\':
            v10 = idStr::snPrintf(&buf[v4], max - v4, "\\");
            goto LABEL_11;
          case 'n':
            v4 += idStr::snPrintf(&buf[v4], max - v4, "\n");
            v5 = v9 + 1;
            break;
          case 't':
            v10 = idStr::snPrintf(&buf[v4], max - v4, "\t");
LABEL_11:
            v4 += v10;
            v5 = v9 + 1;
            break;
          case 'v':
            v4 += idStr::snPrintf(&buf[v4], max - v4, "\v");
            v5 = v9 + 1;
            break;
          default:
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
              common.type,
              "FS_WriteFloatString: unknown escape character '%c'",
              v8);
            v5 = v9 + 1;
            break;
        }
      }
      else
      {
        v4 += idStr::snPrintf(&buf[v4], max - v4, "%c", v6);
        ++v5;
      }
      v6 = *v5;
    }
    while ( *v5 );
  }
  LOBYTE(v25) = 0;
  idStr::FreeData(&format);
  v25 = -1;
  idStr::FreeData(&tmp);
  return v4;
}

// FUNC: public: virtual int __cdecl idFile_Common::WriteFloatString(char const *,...)
int idFile_Common::WriteFloatString(idFile_Common *this, char *fmt, ...)
{
  int v2; // eax
  char buf[4096]; // [esp+0h] [ebp-1000h] BYREF
  va_list argPtr; // [esp+100Ch] [ebp+Ch] BYREF

  va_start(argPtr, fmt);
  v2 = FS_WriteFloatString(buf, 4096, fmt, argPtr);
  return this->Write(this, buf, v2);
}

// FUNC: public: __thiscall idFile_Memory::idFile_Memory(void)
void __thiscall idFile_Memory::idFile_Memory(idFile_Memory *this)
{
  idStr *p_name; // ecx

  p_name = &this->name;
  this->__vftable = (idFile_Memory_vtbl *)&idFile_Memory::`vftable';
  p_name->len = 0;
  p_name->alloced = 20;
  p_name->data = p_name->baseBuffer;
  p_name->baseBuffer[0] = 0;
  idStr::operator=(p_name, "*unknown*");
  this->maxSize = 0;
  this->fileSize = 0;
  this->allocated = 0;
  this->filePtr = 0;
  this->curPtr = 0;
  this->granularity = 0x4000;
  this->mode = 2;
}
