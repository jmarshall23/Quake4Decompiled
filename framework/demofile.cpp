
// FUNC: public: void __thiscall idDemoFile::Log(char const *)
void __thiscall idDemoFile::Log(idDemoFile *this, const char *p)
{
  if ( this->fLog && p )
  {
    if ( *p )
      this->fLog->Write(this->fLog, p, strlen(p));
  }
}

// FUNC: public: virtual int __thiscall idDemoFile::Read(void *,int)
int __thiscall idDemoFile::Read(idDemoFile *this, _BYTE *buffer, int len)
{
  int result; // eax

  result = this->compressor->Read(this->compressor, buffer, len);
  if ( !result && len >= 1 )
    *buffer = 0;
  return result;
}

// FUNC: public: virtual int __thiscall idDemoFile::Write(void const *,int)
int __thiscall idDemoFile::Write(idDemoFile *this, const void *buffer, int len)
{
  return this->compressor->Write(this->compressor, buffer, len);
}

// FUNC: public: __thiscall idDemoFile::idDemoFile(void)
void __thiscall idDemoFile::idDemoFile(idDemoFile *this)
{
  this->__vftable = (idDemoFile_vtbl *)&idDemoFile::`vftable';
  this->demoStrings.list = 0;
  this->demoStrings.num = 0;
  this->demoStrings.size = 0;
  this->demoStrings.granularity = 16;
  this->logStr.len = 0;
  this->logStr.alloced = 20;
  this->logStr.data = this->logStr.baseBuffer;
  this->logStr.baseBuffer[0] = 0;
  this->f = 0;
  this->fLog = 0;
  this->log = 0;
  this->fileImage = 0;
  this->compressor = 0;
  this->writing = 0;
}

// FUNC: public: void __thiscall idDemoFile::WriteHashString(char const *)
void __thiscall idDemoFile::WriteHashString(idDemoFile *this, const char *str)
{
  char *v3; // eax
  int v4; // edi
  const char *v5; // ebx
  idStr *v6; // edi
  unsigned int v7; // eax
  int v8; // ebp
  int v9; // eax
  const char *v10; // ecx
  char *data; // edx
  char v12; // al
  idStr *v13; // ebx
  int granularity; // eax
  bool v15; // cc
  int i; // eax
  int num; // edi
  int size; // eax
  int v19; // ecx
  idStr **list; // ebp
  int j; // eax

  if ( this->log && this->fLog )
  {
    v3 = va("%s > Writing hash string\n", this->logStr.data);
    this->fLog->Write(this->fLog, v3, strlen(v3));
  }
  v4 = 0;
  if ( this->demoStrings.num <= 0 )
  {
    v5 = str;
LABEL_10:
    v6 = (idStr *)Memory::Allocate(0x20u);
    if ( v6 )
    {
      v6->len = 0;
      v6->alloced = 20;
      v6->data = v6->baseBuffer;
      v6->baseBuffer[0] = 0;
      if ( v5 )
      {
        v7 = (unsigned int)&v5[strlen(v5) + 1];
        v8 = v7 - (_DWORD)(v5 + 1);
        v9 = v7 - (_DWORD)v5;
        if ( v9 > v6->alloced )
          idStr::ReAllocate(v6, v9, 1);
        v10 = str;
        data = v6->data;
        do
        {
          v12 = *v10;
          *data++ = *v10++;
        }
        while ( v12 );
        v6->len = v8;
      }
      v13 = v6;
    }
    else
    {
      v13 = 0;
    }
    if ( !this->demoStrings.list )
    {
      granularity = this->demoStrings.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->demoStrings.size )
        {
          v15 = granularity < this->demoStrings.num;
          this->demoStrings.size = granularity;
          if ( v15 )
            this->demoStrings.num = granularity;
          this->demoStrings.list = (idStr **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->demoStrings.num; ++i )
            this->demoStrings.list[i] = *(idStr **)(4 * i);
        }
      }
      else
      {
        this->demoStrings.list = 0;
        this->demoStrings.num = 0;
        this->demoStrings.size = 0;
      }
    }
    num = this->demoStrings.num;
    size = this->demoStrings.size;
    if ( num == size )
    {
      if ( !this->demoStrings.granularity )
        this->demoStrings.granularity = 16;
      v19 = size
          + this->demoStrings.granularity
          - (size + this->demoStrings.granularity) % this->demoStrings.granularity;
      if ( v19 > 0 )
      {
        if ( v19 != this->demoStrings.size )
        {
          list = this->demoStrings.list;
          this->demoStrings.size = v19;
          if ( v19 < num )
            this->demoStrings.num = v19;
          this->demoStrings.list = (idStr **)Memory::Allocate(4 * v19);
          for ( j = 0; j < this->demoStrings.num; ++j )
            this->demoStrings.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->demoStrings.list )
          Memory::Free(this->demoStrings.list);
        this->demoStrings.list = 0;
        this->demoStrings.num = 0;
        this->demoStrings.size = 0;
      }
    }
    this->demoStrings.list[this->demoStrings.num++] = v13;
    this->WriteInt(this, -1);
    this->WriteString(this, str);
  }
  else
  {
    while ( 1 )
    {
      v5 = str;
      if ( !idStr::Cmp(this->demoStrings.list[v4]->data, str) )
        break;
      if ( ++v4 >= this->demoStrings.num )
        goto LABEL_10;
    }
    this->WriteInt(this, v4);
  }
}

// FUNC: public: void __thiscall idDemoFile::WriteDict(class idDict const &)
void __thiscall idDemoFile::WriteDict(idDemoFile *this, const idDict *dict)
{
  int num; // ebp
  int i; // esi
  idKeyValue *v5; // eax
  idKeyValue *v6; // eax

  num = dict->args.num;
  this->WriteInt(this, dict->args.num);
  for ( i = 0; i < num; ++i )
  {
    if ( i < 0 || i >= dict->args.num )
      v5 = 0;
    else
      v5 = &dict->args.list[i];
    idDemoFile::WriteHashString(this, v5->key->data);
    if ( i < 0 || i >= dict->args.num )
      v6 = 0;
    else
      v6 = &dict->args.list[i];
    idDemoFile::WriteHashString(this, v6->value->data);
  }
}

// FUNC: public: void __thiscall idDemoFile::Close(void)
void __thiscall idDemoFile::Close(idDemoFile *this)
{
  idCompressor *compressor; // ecx
  idCompressor *v3; // ecx
  int i; // edi
  idStr **list; // ecx
  idStr *v6; // ebp

  if ( this->writing )
  {
    compressor = this->compressor;
    if ( compressor )
      compressor->FinishCompress(compressor);
  }
  if ( this->f )
  {
    fileSystem->CloseFile(fileSystem, this->f);
    this->f = 0;
  }
  if ( this->fLog )
  {
    fileSystem->CloseFile(fileSystem, this->fLog);
    this->fLog = 0;
  }
  if ( this->fileImage )
  {
    Mem_Free(this->fileImage);
    this->fileImage = 0;
  }
  v3 = this->compressor;
  if ( v3 )
  {
    ((void (__thiscall *)(idCompressor *, int))v3->~idCompressor)(v3, 1);
    this->compressor = 0;
  }
  for ( i = 0; i < this->demoStrings.num; ++i )
  {
    list = this->demoStrings.list;
    v6 = list[i];
    if ( v6 )
    {
      idStr::FreeData(list[i]);
      Memory::Free(v6);
    }
    this->demoStrings.list[i] = 0;
  }
  if ( this->demoStrings.list )
    Memory::Free(this->demoStrings.list);
  this->demoStrings.list = 0;
  this->demoStrings.num = 0;
  this->demoStrings.size = 0;
}

// FUNC: public: char const * __thiscall idDemoFile::ReadHashString(void)
char *__thiscall idDemoFile::ReadHashString(idDemoFile *this)
{
  char *v2; // eax
  int v3; // eax
  idStr *v4; // eax
  idStr *v5; // edi
  idDemoFile_vtbl *v6; // eax
  int len; // ebx
  int granularity; // eax
  bool v9; // cc
  int i; // eax
  int num; // ebx
  int size; // ecx
  int v13; // ecx
  idStr **list; // esi
  int j; // eax
  char *v16; // esi
  idStr *v18; // [esp+10h] [ebp-34h]
  int index; // [esp+14h] [ebp-30h] BYREF
  idStr data; // [esp+18h] [ebp-2Ch] BYREF
  int v21; // [esp+40h] [ebp-4h]

  if ( this->log && this->fLog )
  {
    v2 = va("%s > Reading hash string\n", this->logStr.data);
    this->fLog->Write(this->fLog, v2, strlen(v2));
  }
  this->ReadInt(this, &index);
  v3 = index;
  if ( index == -1 )
  {
    v4 = (idStr *)Memory::Allocate(0x20u);
    if ( v4 )
    {
      v5 = v4;
      v4->len = 0;
      v4->alloced = 20;
      v4->data = v4->baseBuffer;
      v4->baseBuffer[0] = 0;
      v18 = v4;
    }
    else
    {
      v18 = 0;
      v5 = 0;
    }
    data.alloced = 20;
    data.len = 0;
    data.data = data.baseBuffer;
    data.baseBuffer[0] = 0;
    v6 = this->__vftable;
    v21 = 0;
    v6->ReadString(this, &data);
    len = data.len;
    if ( data.len + 1 > v5->alloced )
      idStr::ReAllocate(v5, data.len + 1, 0);
    qmemcpy(v5->data, data.data, len);
    v18->data[len] = 0;
    v18->len = len;
    if ( !this->demoStrings.list )
    {
      granularity = this->demoStrings.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->demoStrings.size )
        {
          v9 = granularity < this->demoStrings.num;
          this->demoStrings.size = granularity;
          if ( v9 )
            this->demoStrings.num = granularity;
          this->demoStrings.list = (idStr **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->demoStrings.num; ++i )
            this->demoStrings.list[i] = *(idStr **)(4 * i);
        }
      }
      else
      {
        this->demoStrings.list = 0;
        this->demoStrings.num = 0;
        this->demoStrings.size = 0;
      }
    }
    num = this->demoStrings.num;
    size = this->demoStrings.size;
    if ( num == size )
    {
      if ( !this->demoStrings.granularity )
        this->demoStrings.granularity = 16;
      v13 = this->demoStrings.granularity
          + size
          - (this->demoStrings.granularity + size) % this->demoStrings.granularity;
      if ( v13 > 0 )
      {
        if ( v13 != this->demoStrings.size )
        {
          list = this->demoStrings.list;
          this->demoStrings.size = v13;
          if ( v13 < num )
            this->demoStrings.num = v13;
          this->demoStrings.list = (idStr **)Memory::Allocate(4 * v13);
          for ( j = 0; j < this->demoStrings.num; ++j )
            this->demoStrings.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->demoStrings.list )
          Memory::Free(this->demoStrings.list);
        this->demoStrings.list = 0;
        this->demoStrings.num = 0;
        this->demoStrings.size = 0;
      }
    }
    this->demoStrings.list[this->demoStrings.num++] = v18;
    v16 = v18->data;
    v21 = -1;
    idStr::FreeData(&data);
    return v16;
  }
  else
  {
    if ( index < -1 || index >= this->demoStrings.num )
    {
      idDemoFile::Close(this);
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "demo hash index out of range");
      v3 = index;
    }
    return this->demoStrings.list[v3]->data;
  }
}

// FUNC: public: void __thiscall idDemoFile::ReadDict(class idDict &)
void __thiscall idDemoFile::ReadDict(idDemoFile *this, idDict *dict)
{
  idDict *v3; // ebp
  int i; // edi
  char *HashString; // eax
  char *v6; // eax
  idStr val; // [esp+10h] [ebp-4Ch] BYREF
  idStr key; // [esp+30h] [ebp-2Ch] BYREF
  int v9; // [esp+58h] [ebp-4h]

  key.len = 0;
  key.alloced = 20;
  key.data = key.baseBuffer;
  key.baseBuffer[0] = 0;
  v9 = 1;
  val.len = 0;
  val.alloced = 20;
  val.data = val.baseBuffer;
  val.baseBuffer[0] = 0;
  v3 = dict;
  idDict::Clear(dict);
  this->ReadInt(this, (int *)&dict);
  for ( i = 0; i < (int)dict; ++i )
  {
    HashString = idDemoFile::ReadHashString(this);
    idStr::operator=(&key, HashString);
    v6 = idDemoFile::ReadHashString(this);
    idStr::operator=(&val, v6);
    idDict::Set(v3, key.data, val.data);
  }
  LOBYTE(v9) = 0;
  idStr::FreeData(&val);
  v9 = -1;
  idStr::FreeData(&key);
}

// FUNC: public: virtual __thiscall idDemoFile::~idDemoFile(void)
void __thiscall idDemoFile::~idDemoFile(idDemoFile *this)
{
  idStr **list; // eax

  this->__vftable = (idDemoFile_vtbl *)&idDemoFile::`vftable';
  idDemoFile::Close(this);
  idStr::FreeData(&this->logStr);
  list = this->demoStrings.list;
  if ( list )
    Memory::Free(list);
  this->demoStrings.list = 0;
  this->demoStrings.num = 0;
  this->demoStrings.size = 0;
  this->__vftable = (idDemoFile_vtbl *)&idFile::`vftable';
}

// FUNC: public: bool __thiscall idDemoFile::OpenForReading(char const *)
char __userpurge idDemoFile::OpenForReading@<al>(
        idDemoFile *this@<ecx>,
        int a2@<edi>,
        int a3@<esi>,
        const char *fileName)
{
  idFile *v5; // eax
  int v7; // esi
  unsigned __int8 *v8; // eax
  idFile *f; // ecx
  idFile_Memory *v10; // edi
  idFile *v11; // eax
  const char *v12; // eax
  idFile *v13; // ecx
  idFile *v14; // ecx
  idCompressor *v15; // eax
  idFile *v16; // ecx
  unsigned __int8 *fileImage; // [esp+1Ch] [ebp-30h]
  int compression; // [esp+2Ch] [ebp-20h] BYREF
  char magicBuffer[13]; // [esp+30h] [ebp-1Ch] BYREF

  idDemoFile::Close(this);
  v5 = fileSystem->OpenFileRead(fileSystem, fileName, 1, 0);
  this->f = v5;
  if ( !v5 )
    return 0;
  v7 = ((int (__thiscall *)(idFile *, int, int))v5->Length)(v5, a2, a3);
  if ( idDemoFile::com_preloadDemos.internalVar->integerValue )
  {
    v8 = (unsigned __int8 *)Mem_Alloc(v7, 2u);
    f = this->f;
    this->fileImage = v8;
    f->Read(f, v8, v7);
    fileSystem->CloseFile(fileSystem, this->f);
    v10 = (idFile_Memory *)Memory::Allocate(0x40u);
    v11 = 0;
    if ( v10 )
    {
      fileImage = this->fileImage;
      v12 = va("preloaded(%s)", fileName);
      idFile_Memory::idFile_Memory(v10, v12, (const char *)fileImage, v7);
    }
    this->f = v11;
  }
  if ( idDemoFile::com_logDemos.internalVar->integerValue )
    this->fLog = fileSystem->OpenFileWrite(fileSystem, "demoread.log", "fs_savepath", 0);
  v13 = this->f;
  this->writing = 0;
  v13->Read(v13, &magicBuffer[8], 13);
  v14 = this->f;
  if ( !strcmp(magicBuffer, "Quake4 RDEMO") )
  {
    v14->ReadInt(v14, &compression);
  }
  else
  {
    compression = 0;
    v14->Rewind(v14);
  }
  if ( compression )
  {
    if ( compression == 2 )
    {
      v15 = idCompressor::AllocLZSS();
    }
    else if ( compression == 3 )
    {
      v15 = idCompressor::AllocHuffman();
    }
    else
    {
      idCompressor::AllocLZW();
    }
  }
  else
  {
    v15 = idCompressor::AllocNoCompression();
  }
  v16 = this->f;
  this->compressor = v15;
  v15->Init(v15, v16, 0, 8);
  return 1;
}

// FUNC: public: bool __thiscall idDemoFile::OpenForWriting(char const *)
char __thiscall idDemoFile::OpenForWriting(idDemoFile *this, const char *fileName)
{
  idFile *v3; // eax
  idFile *f; // ecx
  int integerValue; // eax
  int v7; // eax
  idCompressor *v8; // eax
  idFile *v9; // ecx

  idDemoFile::Close(this);
  v3 = fileSystem->OpenFileWrite(fileSystem, fileName, "fs_savepath", 0);
  this->f = v3;
  if ( !v3 )
    return 0;
  if ( idDemoFile::com_logDemos.internalVar->integerValue )
    this->fLog = fileSystem->OpenFileWrite(fileSystem, "demowrite.log", "fs_savepath", 0);
  f = this->f;
  this->writing = 1;
  f->Write(f, "Quake4 RDEMO", 13);
  this->f->WriteInt(this->f, idDemoFile::com_compressDemos.internalVar->integerValue);
  this->f->Flush(this->f);
  integerValue = idDemoFile::com_compressDemos.internalVar->integerValue;
  if ( integerValue )
  {
    v7 = integerValue - 2;
    if ( v7 )
    {
      if ( v7 == 1 )
        v8 = idCompressor::AllocHuffman();
      else
        idCompressor::AllocLZW();
    }
    else
    {
      v8 = idCompressor::AllocLZSS();
    }
  }
  else
  {
    v8 = idCompressor::AllocNoCompression();
  }
  v9 = this->f;
  this->compressor = v8;
  v8->Init(v8, v9, 1, 8);
  return 1;
}
