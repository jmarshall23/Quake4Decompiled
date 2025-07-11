
// FUNC: void __cdecl BuildHuffmanCode_r(struct huffmanNode_s *,struct huffmanCode_s,struct huffmanCode_s * const)
void __cdecl BuildHuffmanCode_r(huffmanNode_s *node, huffmanCode_s code, huffmanCode_s *codes)
{
  huffmanNode_s *v3; // ebx
  int numBits; // ebp
  huffmanNode_s *v5; // edx
  bool v6; // zf
  huffmanCode_s v7; // [esp-28h] [ebp-5Ch] BYREF
  huffmanCode_s newCode; // [esp+10h] [ebp-24h] BYREF

  v3 = node;
  if ( node->symbol == -1 )
  {
    do
    {
      numBits = code.numBits;
      qmemcpy(&newCode, &code, sizeof(newCode));
      ++newCode.numBits;
      if ( code.numBits > maxHuffmanBits )
        maxHuffmanBits = newCode.numBits;
      v5 = v3->children[0];
      qmemcpy(&v7, &newCode, sizeof(v7));
      BuildHuffmanCode_r(v5, v7, codes);
      v3 = v3->children[1];
      newCode.bits[numBits >> 5] |= 1 << (numBits & 0x1F);
      v6 = v3->symbol == -1;
      qmemcpy(&code, &newCode, sizeof(code));
    }
    while ( v6 );
  }
  qmemcpy(&codes[v3->symbol], &code, sizeof(huffmanCode_s));
}

// FUNC: void __cdecl FreeHuffmanTree_r(struct huffmanNode_s *)
void __cdecl FreeHuffmanTree_r(huffmanNode_s *node)
{
  if ( node->symbol == -1 )
  {
    FreeHuffmanTree_r(node->children[0]);
    FreeHuffmanTree_r(node->children[1]);
  }
  Memory::Free(node);
}

// FUNC: void __cdecl SetupHuffman(void)
void __cdecl SetupHuffman()
{
  huffmanNode_s *v0; // esi
  int i; // edi
  int *v2; // eax
  huffmanNode_s *v3; // edx
  huffmanNode_s *v4; // ecx
  int v5; // edi
  huffmanNode_s *v6; // eax
  int v7; // ecx
  huffmanNode_s *next; // ebx
  huffmanNode_s *v9; // edx
  huffmanNode_s *v10; // ecx
  huffmanCode_s v11; // [esp-28h] [ebp-58h] BYREF
  huffmanCode_s code; // [esp+Ch] [ebp-24h] BYREF

  v0 = 0;
  for ( i = 0; i < 256; ++i )
  {
    v2 = (int *)Memory::Allocate(0x14u);
    *v2 = i;
    v3 = 0;
    v2[1] = huffmanFrequencies[i];
    v2[2] = 0;
    v2[3] = 0;
    v2[4] = 0;
    v4 = v0;
    if ( !v0 )
      goto LABEL_7;
    do
    {
      if ( v2[1] <= v4->frequency )
        break;
      v3 = v4;
      v4 = v4->next;
    }
    while ( v4 );
    if ( v3 )
    {
      v2[2] = (int)v3->next;
      v3->next = (huffmanNode_s *)v2;
    }
    else
    {
LABEL_7:
      v2[2] = (int)v0;
      v0 = (huffmanNode_s *)v2;
    }
  }
  v5 = 255;
  do
  {
    v6 = (huffmanNode_s *)Memory::Allocate(0x14u);
    v6->symbol = -1;
    v7 = v0->frequency + v0->next->frequency;
    v6->next = 0;
    v6->frequency = v7;
    v6->children[0] = v0;
    v6->children[1] = v0->next;
    next = v0->next->next;
    v9 = 0;
    v10 = next;
    if ( !next )
      goto LABEL_15;
    do
    {
      if ( v6->frequency <= v10->frequency )
        break;
      v9 = v10;
      v10 = v10->next;
    }
    while ( v10 );
    if ( v9 )
    {
      v6->next = v9->next;
      v9->next = v6;
    }
    else
    {
LABEL_15:
      v6->next = next;
      next = v6;
    }
    --v5;
    v0 = next;
  }
  while ( v5 );
  memset(&code, 0, sizeof(code));
  maxHuffmanBits = 0;
  qmemcpy(&v11, &code, sizeof(v11));
  BuildHuffmanCode_r(next, v11, huffmanCodes);
  huffmanTree = next;
}

// FUNC: void __cdecl ListHuffmanFrequencies_f(class idCmdArgs const &)
void __cdecl ListHuffmanFrequencies_f()
{
  int *v0; // esi
  int v1; // [esp+0h] [ebp-8h]

  if ( totalUncompressedLength )
    v1 = 100 * totalCompressedLength / totalUncompressedLength;
  else
    v1 = 100;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "// compression ratio = %d%%\n",
    (int)(double)v1);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "static int huffmanFrequencies[] = {\n");
  v0 = &huffmanFrequencies[6];
  do
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "\t0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x,\n",
      *(v0 - 6),
      *(v0 - 5),
      *(v0 - 4),
      *(v0 - 3),
      *(v0 - 2),
      *(v0 - 1),
      *v0,
      v0[1]);
    v0 += 8;
  }
  while ( (int)v0 < (int)&idDeclManagerLocal::decl_show.value );
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "}\n");
}

// FUNC: public: virtual class idMaterial const * __thiscall idDeclManagerLocal::FindMaterial(char const *,bool)
const idMaterial *__thiscall idDeclManagerLocal::FindMaterial(
        idDeclManagerLocal *this,
        const char *name,
        BOOL makeDefault)
{
  return (const idMaterial *)this->FindType(this, 1, name, makeDefault, 0);
}

// FUNC: public: virtual class idDeclSkin const * __thiscall idDeclManagerLocal::FindSkin(char const *,bool)
const idDeclSkin *__thiscall idDeclManagerLocal::FindSkin(idDeclManagerLocal *this, const char *name, BOOL makeDefault)
{
  return (const idDeclSkin *)this->FindType(this, 2, name, makeDefault, 0);
}

// FUNC: public: virtual class idDeclSkin const * __thiscall idDeclManagerLocal::SkinByIndex(int,bool)
const idDeclSkin *__thiscall idDeclManagerLocal::SkinByIndex(idDeclManagerLocal *this, int index, BOOL forceParse)
{
  return (const idDeclSkin *)this->DeclByIndex(this, 2, index, forceParse);
}

// FUNC: public: virtual class idSoundShader const * __thiscall idDeclManagerLocal::FindSound(char const *,bool)
const idSoundShader *__thiscall idDeclManagerLocal::FindSound(
        idDeclManagerLocal *this,
        const char *name,
        BOOL makeDefault)
{
  return (const idSoundShader *)this->FindType(this, 3, name, makeDefault, 0);
}

// FUNC: public: virtual class idSoundShader const * __thiscall idDeclManagerLocal::SoundByIndex(int,bool)
const idSoundShader *__thiscall idDeclManagerLocal::SoundByIndex(idDeclManagerLocal *this, int index, BOOL forceParse)
{
  return (const idSoundShader *)this->DeclByIndex(this, 3, index, forceParse);
}

// FUNC: public: virtual class rvDeclMatType const * __thiscall idDeclManagerLocal::FindMaterialType(char const *,bool)
const rvDeclMatType *__thiscall idDeclManagerLocal::FindMaterialType(
        idDeclManagerLocal *this,
        const char *name,
        BOOL makeDefault)
{
  return (const rvDeclMatType *)this->FindType(this, 6, name, makeDefault, 0);
}

// FUNC: public: virtual class rvDeclMatType const * __thiscall idDeclManagerLocal::MaterialTypeByIndex(int,bool)
const rvDeclMatType *__thiscall idDeclManagerLocal::MaterialTypeByIndex(
        idDeclManagerLocal *this,
        int index,
        BOOL forceParse)
{
  return (const rvDeclMatType *)this->DeclByIndex(this, 6, index, forceParse);
}

// FUNC: public: virtual class rvDeclLipSync const * __thiscall idDeclManagerLocal::FindLipSync(char const *,bool)
const rvDeclLipSync *__thiscall idDeclManagerLocal::FindLipSync(
        idDeclManagerLocal *this,
        const char *name,
        BOOL makeDefault)
{
  return (const rvDeclLipSync *)this->FindType(this, 7, name, makeDefault, 0);
}

// FUNC: public: virtual class rvDeclLipSync const * __thiscall idDeclManagerLocal::LipSyncByIndex(int,bool)
const rvDeclLipSync *__thiscall idDeclManagerLocal::LipSyncByIndex(
        idDeclManagerLocal *this,
        int index,
        BOOL forceParse)
{
  return (const rvDeclLipSync *)this->DeclByIndex(this, 7, index, forceParse);
}

// FUNC: public: virtual class rvDeclPlayback const * __thiscall idDeclManagerLocal::FindPlayback(char const *,bool)
const rvDeclPlayback *__thiscall idDeclManagerLocal::FindPlayback(
        idDeclManagerLocal *this,
        const char *name,
        BOOL makeDefault)
{
  return (const rvDeclPlayback *)this->FindType(this, 8, name, makeDefault, 0);
}

// FUNC: public: virtual class rvDeclPlayback const * __thiscall idDeclManagerLocal::PlaybackByIndex(int,bool)
const rvDeclPlayback *__thiscall idDeclManagerLocal::PlaybackByIndex(
        idDeclManagerLocal *this,
        int index,
        BOOL forceParse)
{
  return (const rvDeclPlayback *)this->DeclByIndex(this, 8, index, forceParse);
}

// FUNC: public: virtual class rvDeclEffect const * __thiscall idDeclManagerLocal::FindEffect(char const *,bool)
const rvDeclEffect *__thiscall idDeclManagerLocal::FindEffect(
        idDeclManagerLocal *this,
        const char *name,
        BOOL makeDefault)
{
  return (const rvDeclEffect *)this->FindType(this, 9, name, makeDefault, 0);
}

// FUNC: public: virtual class rvDeclEffect const * __thiscall idDeclManagerLocal::EffectByIndex(int,bool)
const rvDeclEffect *__thiscall idDeclManagerLocal::EffectByIndex(idDeclManagerLocal *this, int index, BOOL forceParse)
{
  return (const rvDeclEffect *)this->DeclByIndex(this, 9, index, forceParse);
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::FinishLoadingDecls(void)
void __thiscall idDeclManagerLocal::FinishLoadingDecls(idDeclManagerLocal *this)
{
  fileSystem->CloseFile(fileSystem, this->mSingleDeclFile);
  this->mSingleDeclFile = 0;
}

// FUNC: public: virtual int __thiscall idFile_Permanent::Length(void)
declType_t __thiscall idFile_Permanent::Length(idDeclLocal *this)
{
  return this->type;
}

// FUNC: public: virtual enum declState_t __thiscall idDeclLocal::GetState(void)const
declState_t __thiscall idDeclLocal::GetState(idDeclLocal *this)
{
  return this->declState;
}

// FUNC: public: virtual bool __thiscall idDeclLocal::IsImplicit(void)const
BOOL __thiscall idDeclLocal::IsImplicit(idDeclLocal *this)
{
  return this->sourceFile == &declManagerLocal.implicitDecls;
}

// FUNC: public: virtual bool __thiscall idDeclLocal::IsValid(void)const
BOOL __thiscall idDeclLocal::IsValid(idDeclLocal *this)
{
  return this->declState != DS_UNPARSED;
}

// FUNC: public: virtual void __thiscall idDeclLocal::Invalidate(void)
void __thiscall idDeclLocal::Invalidate(idDeclLocal *this)
{
  this->declState = DS_UNPARSED;
}

// FUNC: public: virtual int __thiscall idDeclLocal::Index(void)const
int __thiscall idDeclLocal::Index(idDeclLocal *this)
{
  return this->index;
}

// FUNC: public: virtual int __thiscall idDeclLocal::GetLineNum(void)const
int __thiscall idDeclLocal::GetLineNum(idDeclLocal *this)
{
  return this->sourceLine;
}

// FUNC: protected: virtual char const * __thiscall idDeclLocal::DefaultDefinition(void)const
const char *__thiscall idDeclLocal::DefaultDefinition(idDeclLocal *this)
{
  return "{ }";
}

// FUNC: protected: virtual void __thiscall idDeclLocal::List(void)const
void __thiscall idDeclLocal::List(idDeclLocal *this)
{
  int v1; // esi
  const char *v2; // eax

  v1 = *(_DWORD *)common.type;
  v2 = this->GetName(this);
  (*(void (**)(netadrtype_t, const char *, ...))(v1 + 124))(common.type, "%s\n", v2);
}

// FUNC: public: virtual bool __thiscall idDeclLocal::EverReferenced(void)const
bool __thiscall idDeclLocal::EverReferenced(idDeclLocal *this)
{
  return this->everReferenced;
}

// FUNC: public: virtual void __thiscall idDeclLocal::SetReferencedThisLevel(void)
void __thiscall idDeclLocal::SetReferencedThisLevel(idDeclLocal *this)
{
  this->referencedThisLevel = 1;
  this->everReferenced = 1;
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::StartPlaybackRecord(class rvDeclPlayback *)
void __thiscall idDeclManagerLocal::StartPlaybackRecord(idDeclManagerLocal *this, rvDeclPlayback *playback)
{
  rvDeclPlayback::Start(playback);
}

// FUNC: public: virtual bool __thiscall idDeclManagerLocal::SetPlaybackData(class rvDeclPlayback *,int,int,class rvDeclPlaybackData *)
bool __thiscall idDeclManagerLocal::SetPlaybackData(
        idDeclManagerLocal *this,
        rvDeclPlayback *playback,
        int now,
        int control,
        rvDeclPlaybackData *pbd)
{
  float localTime; // [esp+0h] [ebp-Ch]

  localTime = (double)now * 0.001;
  return rvDeclPlayback::SetCurrentData(playback, localTime, control, pbd);
}

// FUNC: public: virtual bool __thiscall idDeclManagerLocal::GetPlaybackData(class rvDeclPlayback const *,int,int,int,class rvDeclPlaybackData *)
bool __thiscall idDeclManagerLocal::GetPlaybackData(
        idDeclManagerLocal *this,
        rvDeclPlayback *playback,
        int control,
        int now,
        int last,
        rvDeclPlaybackData *pbd)
{
  float localTime; // [esp+0h] [ebp-Ch]
  float lastTime; // [esp+4h] [ebp-8h]

  if ( !playback )
    return 1;
  lastTime = (double)last * 0.001;
  localTime = (double)now * 0.001;
  return rvDeclPlayback::GetCurrentData(playback, control, localTime, lastTime, pbd);
}

// FUNC: public: virtual bool __thiscall idDeclManagerLocal::FinishPlayback(class rvDeclPlayback *)
char __thiscall idDeclManagerLocal::FinishPlayback(idDeclManagerLocal *this, rvDeclPlayback *playback)
{
  return rvDeclPlayback::Finish(playback, -1.0);
}

// FUNC: int __cdecl HuffmanCompressText(char const *,int,unsigned char *,int)
int __cdecl HuffmanCompressText(const char *text, int textLength, unsigned __int8 *compressed, int maxCompressedSize)
{
  int result; // eax
  int v5; // ebp
  huffmanCode_s *v6; // esi
  int v7; // edi
  idBitMsg msg; // [esp+4h] [ebp-24h] BYREF

  idBitMsg::idBitMsg(&msg);
  totalUncompressedLength += textLength;
  msg.writeData = compressed;
  msg.readData = compressed;
  msg.maxSize = maxCompressedSize;
  result = 0;
  v5 = 0;
  msg.numValueOverflows = 0;
  msg.curSize = 0;
  msg.overflowed = 0;
  msg.writeBit = 0;
  if ( textLength > 0 )
  {
    do
    {
      v6 = &huffmanCodes[(unsigned __int8)text[v5]];
      v7 = 0;
      if ( v6->numBits >= 0 && (v6->numBits & 0xFFFFFFE0) != 0 )
      {
        do
          idBitMsg::WriteBits(&msg, v6->bits[v7++], 32);
        while ( v7 < v6->numBits >> 5 );
      }
      if ( (v6->numBits & 0x1F) != 0 )
        idBitMsg::WriteBits(&msg, v6->bits[v7], v6->numBits & 0x1F);
      ++v5;
    }
    while ( v5 < textLength );
    result = msg.curSize;
  }
  totalCompressedLength += result;
  return result;
}

// FUNC: int __cdecl HuffmanDecompressText(char *,int,unsigned char const *,int)
int __cdecl HuffmanDecompressText(char *text, int textLength, const unsigned __int8 *compressed, int compressedSize)
{
  int v4; // edi
  int result; // eax
  huffmanNode_s *v6; // esi
  idBitMsg msg; // [esp+8h] [ebp-24h] BYREF

  idBitMsg::idBitMsg(&msg);
  msg.readData = compressed;
  v4 = 0;
  msg.maxSize = compressedSize;
  msg.curSize = compressedSize;
  result = 0;
  msg.writeData = 0;
  memset(&msg.readCount, 0, 12);
  if ( textLength <= 0 )
  {
    *text = 0;
  }
  else
  {
    do
    {
      v6 = huffmanTree;
      do
        v6 = v6->children[idBitMsg::ReadBits(&msg, 1)];
      while ( v6->symbol == -1 );
      text[v4++] = v6->symbol;
    }
    while ( v4 < textLength );
    result = msg.readCount;
    text[v4] = 0;
  }
  return result;
}

// FUNC: public: __thiscall idDeclFile::idDeclFile(void)
void __thiscall idDeclFile::idDeclFile(idDeclFile *this)
{
  this->fileName.len = 0;
  this->fileName.alloced = 20;
  this->fileName.data = this->fileName.baseBuffer;
  this->fileName.baseBuffer[0] = 0;
  idStr::operator=(&this->fileName, "<implicit file>");
  this->timestamp = 0;
  this->checksum = 0;
  this->fileSize = 0;
  this->numLines = 0;
  this->decls = 0;
  this->defaultType = DECL_MAX_TYPES;
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::BeginLevelLoad(void)
void __thiscall idDeclManagerLocal::BeginLevelLoad(idDeclManagerLocal *this)
{
  idDeclManagerLocal *v1; // edx
  idDeclLocal ***p_list; // ebp
  int v3; // ebx
  int i; // edi
  idDeclLocal *v5; // esi
  idDeclLocal_vtbl *v6; // edx
  idDeclLocal *v7; // ecx
  int num; // esi
  int j; // eax
  idDecl *self; // ecx
  int v11; // [esp+10h] [ebp-8h]

  v1 = this;
  this->insideLevelLoad = 1;
  p_list = &this->linearLists[0].list;
  v11 = 32;
  do
  {
    v3 = (int)*(p_list - 3);
    for ( i = 0; i < v3; ++i )
    {
      v5 = (*p_list)[i];
      if ( !v5->parsedOutsideLevelLoad )
      {
        v6 = v5->__vftable;
        v7 = (*p_list)[i];
        v5->referencedThisLevel = 0;
        v6->MakeDefault(v7);
        v1 = this;
        v5->declState = DS_UNPARSED;
      }
    }
    p_list += 4;
    --v11;
  }
  while ( v11 );
  num = v1->linearLists[1].num;
  for ( j = 0; j < num; ++j )
  {
    self = v1->linearLists[1].list[j]->self;
    if ( self )
      self[16].base = 0;
  }
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::EndLevelLoad(void)
void __thiscall idDeclManagerLocal::EndLevelLoad(idDeclManagerLocal *this)
{
  int num; // ebx
  int v3; // esi
  idMaterial *self; // ecx

  num = this->linearLists[1].num;
  v3 = 0;
  for ( this->insideLevelLoad = 0; v3 < num; ++v3 )
  {
    self = (idMaterial *)this->linearLists[1].list[v3]->self;
    if ( self )
      idMaterial::ResolveUse(self);
  }
}

// FUNC: private: int __thiscall idDeclManagerLocal::GetTotalTextMemory(enum declType_t)
int __thiscall idDeclManagerLocal::GetTotalTextMemory(idDeclManagerLocal *this, declType_t defaultType)
{
  int v3; // ebp
  int i; // edi
  const idDecl *v5; // eax

  v3 = 0;
  for ( i = 0; i < this->GetNumDecls(this, defaultType); ++i )
  {
    v5 = this->DeclByIndex(this, defaultType, i, 0);
    v3 += v5->base->GetCompressedLength(v5->base);
  }
  return v3;
}

// FUNC: public: virtual char const * __thiscall idDeclManagerLocal::GetDeclTypeName(enum declType_t)
char *__thiscall idDeclManagerLocal::GetDeclTypeName(idDeclManagerLocal *this, declType_t defaultType)
{
  return this->declTypes.list[defaultType]->typeName.data;
}

// FUNC: public: virtual int __thiscall idDeclManagerLocal::GetChecksum(void)const
unsigned int __thiscall idDeclManagerLocal::GetChecksum(idDeclManagerLocal *this)
{
  idDeclManagerLocal *v1; // ebx
  int v2; // ecx
  idList<idDeclLocal *> *v3; // eax
  int v4; // edx
  int v5; // esi
  int v6; // eax
  void *v7; // esp
  int v8; // esi
  int v9; // eax
  idDeclLocal ***p_list; // edx
  int v11; // ecx
  idDeclFile *p_implicitDecls; // ebx
  idDeclLocal *v13; // eax
  idDeclManagerLocal *v15; // [esp+Ch] [ebp-Ch] BYREF
  int i; // [esp+10h] [ebp-8h]
  int num; // [esp+14h] [ebp-4h]

  v1 = this;
  v15 = this;
  v2 = 0;
  v3 = &v15->linearLists[2];
  v4 = 8;
  do
  {
    v5 = v3[-1].num + v3[-2].num;
    v3 += 4;
    v2 += v3[-4].num + v3[-3].num + v5;
    --v4;
  }
  while ( v4 );
  v6 = 8 * v2 + 18;
  LOBYTE(v6) = v6 & 0xFC;
  v7 = alloca(v6);
  v8 = 0;
  v9 = 0;
  i = 0;
  p_list = &v1->linearLists[0].list;
  do
  {
    if ( v9 != 12 && v9 != 13 && v9 != 14 && v9 != 15 )
    {
      num = (int)*(p_list - 3);
      v11 = 0;
      if ( num > 0 )
      {
        p_implicitDecls = &v1->implicitDecls;
        do
        {
          v13 = (*p_list)[v11];
          if ( v13->sourceFile != p_implicitDecls )
          {
            *(&v15 + 2 * v8) = (idDeclManagerLocal *)v8;
            *(&v15 + 2 * v8++ + 1) = (idDeclManagerLocal *)v13->checksum;
          }
          ++v11;
        }
        while ( v11 < num );
        v9 = i;
        v1 = v15;
      }
    }
    ++v9;
    p_list += 4;
    i = v9;
  }
  while ( v9 < 32 );
  LittleRevBytes(&v15, 4, 2 * v8);
  return MD5_BlockChecksum(&v15, 8 * v8);
}

// FUNC: public: virtual char const * __thiscall idFile_Memory::GetFullPath(void)
char *__thiscall idFile_Memory::GetFullPath(idCollisionModelLocal *this)
{
  return this->name.data;
}

// FUNC: public: virtual char const * __thiscall idDeclManagerLocal::GetDeclNameFromType(enum declType_t)const
char *__thiscall idDeclManagerLocal::GetDeclNameFromType(idDeclManagerLocal *this, int type)
{
  if ( type < 0 || type >= this->declTypes.num || !this->declTypes.list[type] )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idDeclManager::GetDeclNameFromType: bad type: %i",
      type);
  return this->declTypes.list[type]->typeName.data;
}

// FUNC: public: virtual enum declType_t __thiscall idDeclManagerLocal::GetDeclTypeFromName(char const *)const
declType_t __thiscall idDeclManagerLocal::GetDeclTypeFromName(idDeclManagerLocal *this, const char *typeName)
{
  int v3; // esi
  idDeclType *v4; // eax

  v3 = 0;
  if ( this->declTypes.num <= 0 )
    return 32;
  while ( 1 )
  {
    v4 = this->declTypes.list[v3];
    if ( v4 )
    {
      if ( !idStr::Icmp(v4->typeName.data, typeName) )
        break;
    }
    if ( ++v3 >= this->declTypes.num )
      return 32;
  }
  return this->declTypes.list[v3]->type;
}

// FUNC: public: virtual int __thiscall idDeclManagerLocal::GetNumDecls(enum declType_t)
int __thiscall idDeclManagerLocal::GetNumDecls(idDeclManagerLocal *this, int type)
{
  if ( type < 0 || type >= this->declTypes.num || !this->declTypes.list[type] )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idDeclManager::GetNumDecls: bad type: %i",
      type);
  return this->linearLists[type].num;
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::ListType(class idCmdArgs const &,enum declType_t)
void __thiscall idDeclManagerLocal::ListType(idDeclManagerLocal *this, const idCmdArgs *args, declType_t type)
{
  const char *v5; // eax
  const char *v6; // eax
  int num; // ebp
  char *v8; // ebx
  int v9; // edi
  int v10; // esi
  int v11; // eax
  bool ever; // [esp+13h] [ebp-Dh]
  int printed; // [esp+14h] [ebp-Ch]
  int v14; // [esp+18h] [ebp-8h]
  bool argsa; // [esp+24h] [ebp+4h]

  if ( args->argc <= 1 )
    v5 = &entityFilter;
  else
    v5 = args->argv[1];
  argsa = idStr::Icmp(v5, "all") == 0;
  if ( args->argc <= 1 )
    v6 = &entityFilter;
  else
    v6 = args->argv[1];
  ever = idStr::Icmp(v6, "ever") == 0;
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "--------------------\n");
  num = this->linearLists[type].num;
  v8 = (char *)this + 16 * type;
  v9 = 0;
  for ( printed = 0; v9 < num; ++v9 )
  {
    v10 = *(_DWORD *)(*((_DWORD *)v8 + 241) + 4 * v9);
    if ( argsa || *(_DWORD *)(v10 + 76) && (ever || *(_BYTE *)(v10 + 86)) )
    {
      if ( *(_BYTE *)(v10 + 86) )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "*");
      }
      else if ( *(_BYTE *)(v10 + 85) )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, ".");
      }
      else
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " ");
      }
      if ( *(_DWORD *)(v10 + 76) == 1 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "D");
      else
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " ");
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%4i: ",
        *(_DWORD *)(v10 + 80));
      ++printed;
      if ( *(_DWORD *)(v10 + 76) )
      {
        (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(v10 + 4) + 24))(*(_DWORD *)(v10 + 4));
      }
      else
      {
        v14 = *(_DWORD *)common.type;
        v11 = (*(int (__thiscall **)(int))(*(_DWORD *)v10 + 4))(v10);
        (*(void (**)(netadrtype_t, const char *, ...))(v14 + 124))(common.type, "%s\n", v11);
      }
    }
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "--------------------\n");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%i of %i %s\n",
    printed,
    num,
    this->declTypes.list[type]->typeName.data);
}

// FUNC: public: virtual void __cdecl idDeclManagerLocal::MediaPrint(char const *,...)
void idDeclManagerLocal::MediaPrint(idDeclManagerLocal *this, const char *fmt, ...)
{
  int i; // esi
  char buffer[1024]; // [esp+0h] [ebp-400h] BYREF
  va_list argptr; // [esp+40Ch] [ebp+Ch] BYREF

  va_start(argptr, fmt);
  if ( idDeclManagerLocal::decl_show.internalVar->integerValue )
  {
    for ( i = 0; i < this->indent; ++i )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "    ");
    idStr::vsnPrintf(buffer, 1024, fmt, argptr);
    buffer[1023] = 0;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s", buffer);
  }
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::WritePrecacheCommands(class idFile *)
void __thiscall idDeclManagerLocal::WritePrecacheCommands(idDeclManagerLocal *this, idFile *f)
{
  int v3; // edi
  idDeclLocal ***p_list; // edx
  int v5; // esi
  int v6; // eax
  idDeclLocal *v7; // ecx
  char *data; // esi
  const char *v9; // eax
  idDeclLocal ***v10; // [esp+8h] [ebp-40Ch]
  int j; // [esp+Ch] [ebp-408h]
  int num; // [esp+10h] [ebp-404h]
  char str[1024]; // [esp+14h] [ebp-400h] BYREF

  v3 = 0;
  if ( this->declTypes.num > 0 )
  {
    p_list = &this->linearLists[0].list;
    v10 = &this->linearLists[0].list;
    do
    {
      if ( this->declTypes.list[v3] )
      {
        v5 = (int)*(p_list - 3);
        v6 = 0;
        num = v5;
        for ( j = 0; v6 < v5; j = v6 )
        {
          v7 = (*p_list)[v6];
          if ( v7->referencedThisLevel )
          {
            data = this->declTypes.list[v3]->typeName.data;
            v9 = v7->GetName(v7);
            sprintf(str, "touch %s %s\n", data, v9);
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s", str);
            f->Printf(f, "%s", str);
            v5 = num;
            p_list = v10;
            v6 = j;
          }
          ++v6;
        }
      }
      ++v3;
      p_list += 4;
      v10 = p_list;
    }
    while ( v3 < this->declTypes.num );
  }
}

// FUNC: public: virtual class idMaterial const * __thiscall idDeclManagerLocal::MaterialByIndex(int,bool)
const idMaterial *__thiscall idDeclManagerLocal::MaterialByIndex(idDeclManagerLocal *this, int index, BOOL forceParse)
{
  const idMaterial *result; // eax

  result = (const idMaterial *)this->DeclByIndex(this, 1, index, forceParse);
  if ( result )
  {
    if ( this->insideLevelLoad )
    {
      ++result->useCount;
      ++result->globalUseCount;
    }
  }
  return result;
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::FlushDecls(void)
void __thiscall idDeclManagerLocal::FlushDecls(idDeclManagerLocal *this)
{
  int i; // edi
  idDeclLocal *j; // esi
  idDeclLocal_vtbl *v3; // edx

  for ( i = declManagerLocal.loadedFiles.num - 1; i >= 0; --i )
  {
    for ( j = declManagerLocal.loadedFiles.list[i]->decls; j; j = j->nextInFile )
    {
      if ( !j->parsedOutsideLevelLoad )
      {
        v3 = j->__vftable;
        j->referencedThisLevel = 0;
        v3->MakeDefault(j);
        j->declState = DS_UNPARSED;
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::StartLoadingDecls(void)
void __thiscall idDeclManagerLocal::StartLoadingDecls(idDeclManagerLocal *this)
{
  const char *v2; // eax
  char *v3; // eax
  char *v4; // esi
  unsigned int v5; // eax
  int v6; // edi
  int v7; // eax
  char *data; // edx
  char *v9; // ecx
  char v10; // al
  idStr fileName; // [esp+Ch] [ebp-2Ch] BYREF
  int v12; // [esp+34h] [ebp-4h]

  v2 = fileSystem->GetAssetLogName(fileSystem);
  v3 = strchr(v2, 47);
  v4 = v3 + 1;
  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  if ( v3 != (char *)-1 )
  {
    v5 = (unsigned int)&v3[strlen(v3 + 1) + 2];
    v6 = v5 - (_DWORD)(v4 + 1);
    v7 = v5 - (_DWORD)v4;
    if ( v7 > 20 )
      idStr::ReAllocate(&fileName, v7, 1);
    data = fileName.data;
    v9 = v4;
    do
    {
      v10 = *v9;
      *data++ = *v9++;
    }
    while ( v10 );
    fileName.len = v6;
  }
  v12 = 0;
  idStr::SetFileExtension(&fileName, ".decls");
  this->mSingleDeclFile = fileSystem->OpenFileRead(fileSystem, fileName.data, 1, 0);
  v12 = -1;
  idStr::FreeData(&fileName);
}

// FUNC: private: static void __cdecl idDeclManagerLocal::ListAllDecls_f(class idCmdArgs const &)
void __cdecl idDeclManagerLocal::ListAllDecls_f()
{
  int v0; // ebp
  idDeclLocal ***p_list; // ebx
  idDeclType *v2; // eax
  int v3; // edi
  int v4; // esi
  int v5; // ebp
  int v6; // eax
  int i; // [esp+4h] [ebp-4h]

  v0 = 0;
  i = 0;
  if ( declManagerLocal.declTypes.num > 0 )
  {
    p_list = &declManagerLocal.linearLists[0].list;
    do
    {
      v2 = declManagerLocal.declTypes.list[v0];
      if ( v2 )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "Starting %s\n----\n",
          v2->typeName.data);
        v3 = (int)*(p_list - 3);
        v4 = 0;
        if ( v3 > 0 )
        {
          do
          {
            v5 = *(_DWORD *)common.type;
            v6 = (int)(*p_list)[v4]->GetName((*p_list)[v4]);
            (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(common.type, "%s\n", v6);
            ++v4;
          }
          while ( v4 < v3 );
          v0 = i;
        }
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "----\n");
      }
      ++v0;
      p_list += 4;
      i = v0;
    }
    while ( v0 < declManagerLocal.declTypes.num );
  }
}

// FUNC: private: static void __cdecl idDeclManagerLocal::ListDecls_f(class idCmdArgs const &)
void __cdecl idDeclManagerLocal::ListDecls_f()
{
  int v0; // eax
  int v1; // esi
  int v2; // edi
  idDeclLocal ***p_list; // ebx
  int v4; // ebp
  int v5; // esi
  int v6; // edi
  int v7; // eax
  idDecl *self; // ecx
  int j; // eax
  int totalStructs; // [esp+Ch] [ebp-10h]
  int i; // [esp+10h] [ebp-Ch]
  int totalDecls; // [esp+14h] [ebp-8h]

  v0 = 0;
  v1 = 0;
  v2 = 0;
  totalDecls = 0;
  totalStructs = 0;
  i = 0;
  if ( declManagerLocal.declTypes.num > 0 )
  {
    p_list = &declManagerLocal.linearLists[0].list;
    do
    {
      if ( declManagerLocal.declTypes.list[v0] )
      {
        v4 = (int)*(p_list - 3);
        totalDecls += v4;
        v5 = 0;
        v6 = 0;
        if ( v4 > 0 )
        {
          do
          {
            v7 = (*p_list)[v6]->Size((*p_list)[v6]);
            self = (*p_list)[v6]->self;
            v5 += v7;
            if ( self )
              v5 += self->Size(self);
            ++v6;
          }
          while ( v6 < v4 );
          v0 = i;
        }
        totalStructs += v5;
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%4ik %4i %s\n",
          v5 >> 10,
          v4,
          declManagerLocal.declTypes.list[v0]->typeName.data);
        v2 = totalStructs;
        v1 = 0;
        v0 = i;
      }
      ++v0;
      p_list += 4;
      i = v0;
    }
    while ( v0 < declManagerLocal.declTypes.num );
  }
  for ( j = 0; j < declManagerLocal.loadedFiles.num; ++j )
    v1 += declManagerLocal.loadedFiles.list[j]->fileSize;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%i total decls is %i decl files\n",
    totalDecls,
    declManagerLocal.loadedFiles.num);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%iKB in text, %iKB in structures\n",
    v1 >> 10,
    v2 >> 10);
}

// FUNC: public: virtual unsigned int __thiscall idDeclManagerLocal::ListDeclSummary(class idCmdArgs const &)
int __thiscall idDeclManagerLocal::ListDeclSummary(idDeclManagerLocal *this, const idCmdArgs *args)
{
  int v2; // eax
  idDeclLocal ***p_list; // edi
  int v4; // ebp
  int v5; // ebx
  int v6; // esi
  int v7; // eax
  idDecl *self; // ecx
  int totalStructs; // [esp+4h] [ebp-Ch]
  int totalDecls; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  v2 = 0;
  totalDecls = 0;
  totalStructs = 0;
  i = 0;
  if ( declManagerLocal.declTypes.num > 0 )
  {
    p_list = &declManagerLocal.linearLists[0].list;
    do
    {
      if ( declManagerLocal.declTypes.list[v2] )
      {
        v4 = (int)*(p_list - 3);
        totalDecls += v4;
        v5 = 0;
        v6 = 0;
        if ( v4 > 0 )
        {
          do
          {
            v7 = (*p_list)[v6]->Size((*p_list)[v6]);
            self = (*p_list)[v6]->self;
            v5 += v7;
            if ( self )
              v5 += self->Size(self);
            ++v6;
          }
          while ( v6 < v4 );
          v2 = i;
        }
        totalStructs += v5;
      }
      ++v2;
      p_list += 4;
      i = v2;
    }
    while ( v2 < declManagerLocal.declTypes.num );
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "Decls           - %dK in %d decl structs\n",
    totalStructs >> 10,
    totalDecls);
  return totalStructs >> 10;
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::RemoveDeclFile(char const *)
void __thiscall idDeclManagerLocal::RemoveDeclFile(idDeclManagerLocal *this, const char *file)
{
  int v3; // edi
  int num; // eax
  bool v5; // cc
  int v6; // eax
  idDeclFile **v7; // ecx

  v3 = 0;
  if ( this->loadedFiles.num > 0 )
  {
    while ( idStr::Icmp(this->loadedFiles.list[v3]->fileName.data, file) )
    {
      if ( ++v3 >= this->loadedFiles.num )
        return;
    }
    if ( v3 >= 0 )
    {
      num = this->loadedFiles.num;
      if ( v3 < num )
      {
        v5 = v3 < num - 1;
        this->loadedFiles.num = num - 1;
        v6 = v3;
        if ( v5 )
        {
          do
          {
            v7 = &this->loadedFiles.list[v6++];
            *v7 = v7[1];
          }
          while ( v6 < this->loadedFiles.num );
        }
      }
    }
  }
}

// FUNC: public: __thiscall idDeclLocal::idDeclLocal(void)
void __thiscall idDeclLocal::idDeclLocal(idDeclLocal *this)
{
  idStr *p_name; // ecx

  p_name = &this->name;
  this->__vftable = (idDeclLocal_vtbl *)&idDeclLocal::`vftable';
  p_name->len = 0;
  p_name->alloced = 20;
  p_name->data = p_name->baseBuffer;
  p_name->baseBuffer[0] = 0;
  idStr::operator=(p_name, "unnamed");
  this->textSource = 0;
  this->textLength = 0;
  this->compressedLength = 0;
  this->sourceFile = 0;
  this->sourceTextOffset = 0;
  this->sourceTextLength = 0;
  this->sourceLine = 0;
  this->checksum = 0;
  this->index = 0;
  this->declState = DS_UNPARSED;
  this->parsedOutsideLevelLoad = 0;
  this->referencedThisLevel = 0;
  this->everReferenced = 0;
  this->redefinedInReload = 0;
  this->nextInFile = 0;
  this->self = 0;
  this->needsPrecache = 0;
  this->type = DECL_ENTITYDEF;
}

// FUNC: public: virtual int __thiscall idDeclLocal::GetCompressedLength(void)const
const idSoundShader *__thiscall idDeclLocal::GetCompressedLength(idSoundShader *this)
{
  return this->altSound;
}

// FUNC: public: virtual bool __thiscall idMaterial::RebuildTextSource(void)
bool __thiscall idMaterial::RebuildTextSource(idDeclEntityDef *this)
{
  return 0;
}

// FUNC: public: virtual __thiscall idDeclLocal::~idDeclLocal(void)
void __thiscall idDeclLocal::~idDeclLocal(idDeclLocal *this)
{
  this->__vftable = (idDeclLocal_vtbl *)&idDeclLocal::`vftable';
  idStr::FreeData(&this->name);
  this->__vftable = (idDeclLocal_vtbl *)&idDeclBase::`vftable';
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetAmbientNormalMap(void)const
char *__thiscall idImageManagerLocal::GetAmbientNormalMap(idDeclLocal *this)
{
  return this->name.data;
}

// FUNC: public: virtual unsigned int __thiscall idDeclLocal::Size(void)const
int __thiscall idDeclLocal::Size(idDeclLocal *this)
{
  if ( this->name.data == this->name.baseBuffer )
    return 8;
  else
    return this->name.alloced + 8;
}

// FUNC: public: virtual void __thiscall idDeclLocal::GetText(char *)const
void __thiscall idDeclLocal::GetText(idDeclLocal *this, char *text)
{
  HuffmanDecompressText(text, this->textLength, (const unsigned __int8 *)this->textSource, this->compressedLength);
}

// FUNC: protected: void __thiscall idDeclLocal::SetTextLocal(char const *,int)
void __thiscall idDeclLocal::SetTextLocal(idDeclLocal *this, const char *text, int length)
{
  int v4; // eax
  int v5; // edi
  int v6; // eax
  void *v7; // esp
  int v8; // eax
  char *v9; // eax
  int compressedLength; // [esp-4h] [ebp-10h]
  unsigned __int8 v11[12]; // [esp+0h] [ebp-Ch] BYREF

  Mem_Free(this->textSource);
  v4 = MD5_BlockChecksum(text, length);
  v5 = length * ((maxHuffmanBits + 7) >> 3);
  this->checksum = v4;
  v6 = v5 + 3;
  LOBYTE(v6) = (v5 + 3) & 0xFC;
  v7 = alloca(v6);
  v8 = HuffmanCompressText(text, length, v11, v5);
  this->compressedLength = v8;
  v9 = (char *)Mem_Alloc(v8, 0xAu);
  compressedLength = this->compressedLength;
  this->textSource = v9;
  SIMDProcessor->Memcpy(SIMDProcessor, v9, v11, compressedLength);
  this->textLength = length;
}

// FUNC: public: virtual bool __thiscall idDeclLocal::ReplaceSourceFileText(void)
char __thiscall idDeclLocal::ReplaceSourceFileText(idDeclLocal *this)
{
  int v2; // edi
  const char *v3; // eax
  int v4; // eax
  idDeclManagerLocal *sourceFile; // eax
  int v6; // edi
  const char *v7; // eax
  int size; // ebx
  int v10; // eax
  int v11; // eax
  char *v12; // edi
  idFileSystem_vtbl *v13; // ebx
  int v14; // eax
  idFile *v15; // eax
  idFile *v16; // ebx
  int v17; // edi
  idFile_vtbl *v18; // edx
  int v19; // edi
  const char *v20; // eax
  int v21; // eax
  void *v22; // esp
  idDeclLocal_vtbl *v23; // edx
  idFileSystem_vtbl *v24; // ebx
  int v25; // eax
  idFile *v26; // ebx
  int v27; // edi
  idFileSystem_vtbl *v28; // ebx
  int v29; // eax
  idDeclLocal *i; // ecx
  int sourceTextOffset; // eax
  const char *v32; // [esp-4h] [ebp-1Ch]
  const char *v33; // [esp-4h] [ebp-1Ch]
  int v34; // [esp-4h] [ebp-1Ch]
  _BYTE v35[12]; // [esp+0h] [ebp-18h] BYREF
  int oldFileLength; // [esp+Ch] [ebp-Ch]
  int newFileLength; // [esp+10h] [ebp-8h]
  idFile *file; // [esp+14h] [ebp-4h]

  v2 = *(_DWORD *)common.type;
  v3 = this->GetFileName(this);
  v4 = ((int (__thiscall *)(idDeclLocal *, const char *))this->GetName)(this, v3);
  (*(void (__cdecl **)(netadrtype_t, const char *, int))(v2 + 124))(common.type, "Writing '%s' to '%s'...\n", v4);
  sourceFile = (idDeclManagerLocal *)this->sourceFile;
  if ( sourceFile == (idDeclManagerLocal *)&declManagerLocal.implicitDecls )
  {
    v6 = *(_DWORD *)common.type;
    v7 = this->GetName(this);
    (*(void (**)(netadrtype_t, const char *, ...))(v6 + 136))(common.type, "Can't save implicit declaration %s.", v7);
    return 0;
  }
  size = sourceFile->loadedFiles.size;
  v10 = size - this->sourceTextLength;
  oldFileLength = size;
  v11 = this->textLength + v10;
  newFileLength = v11;
  if ( v11 <= size )
    v11 = size;
  v12 = (char *)Mem_Alloc(v11, 0xAu);
  if ( this->sourceFile->fileSize )
  {
    v13 = fileSystem->__vftable;
    v14 = ((int (__thiscall *)(idDeclLocal *, int, _DWORD))this->GetFileName)(this, 1, 0);
    v15 = (idFile *)((int (__thiscall *)(idFileSystem *, int))v13->OpenFileRead)(fileSystem, v14);
    v16 = v15;
    file = v15;
    if ( !v15 )
    {
      Mem_Free(v12);
      v17 = *(_DWORD *)common.type;
      v32 = this->GetFileName(this);
      (*(void (__cdecl **)(netadrtype_t, const char *, const char *))(v17 + 136))(
        common.type,
        "Couldn't open %s for reading.",
        v32);
      return 0;
    }
    if ( v15->Length(v15) != this->sourceFile->fileSize
      || v16->Timestamp(v16) != this->sourceFile->timestamp
      || (v18 = v16->__vftable,
          size = oldFileLength,
          v18->Read(file, v12, oldFileLength),
          fileSystem->CloseFile(fileSystem, file),
          MD5_BlockChecksum(v12, oldFileLength) != this->sourceFile->checksum) )
    {
      Mem_Free(v12);
      v19 = *(_DWORD *)common.type;
      v20 = this->GetFileName(this);
      (*(void (**)(netadrtype_t, const char *, ...))(v19 + 136))(
        common.type,
        "The file %s has been modified outside of the engine.",
        v20);
      return 0;
    }
  }
  v21 = this->textLength + 4;
  LOBYTE(v21) = v21 & 0xFC;
  v22 = alloca(v21);
  v23 = this->__vftable;
  oldFileLength = (int)v35;
  v23->GetText(this, v35);
  memmove(
    (unsigned __int8 *)&v12[this->sourceTextOffset + this->textLength],
    (unsigned __int8 *)&v12[this->sourceTextOffset + this->sourceTextLength],
    size - this->sourceTextOffset - this->sourceTextLength);
  SIMDProcessor->Memcpy(SIMDProcessor, &v12[this->sourceTextOffset], (const void *)oldFileLength, this->textLength);
  v24 = fileSystem->__vftable;
  v25 = ((int (__thiscall *)(idDeclLocal *, const char *, _DWORD))this->GetFileName)(this, "fs_devpath", 0);
  v26 = (idFile *)((int (__thiscall *)(idFileSystem *, int))v24->OpenFileWrite)(fileSystem, v25);
  if ( !v26 )
  {
    Mem_Free(v12);
    v27 = *(_DWORD *)common.type;
    v33 = this->GetFileName(this);
    (*(void (__cdecl **)(netadrtype_t, const char *, const char *))(v27 + 136))(
      common.type,
      "Couldn't open %s for writing.",
      v33);
    return 0;
  }
  v26->Write(v26, v12, newFileLength);
  fileSystem->CloseFile(fileSystem, v26);
  v34 = newFileLength;
  this->sourceFile->fileSize = newFileLength;
  this->sourceFile->checksum = MD5_BlockChecksum(v12, v34);
  v28 = fileSystem->__vftable;
  v29 = ((int (__thiscall *)(idDeclLocal *, _DWORD, unsigned int *))this->GetFileName)(
          this,
          0,
          &this->sourceFile->timestamp);
  ((void (__thiscall *)(idFileSystem *, int))v28->ReadFile)(fileSystem, v29);
  Mem_Free(v12);
  for ( i = this->sourceFile->decls; i; i = i->nextInFile )
  {
    sourceTextOffset = i->sourceTextOffset;
    if ( sourceTextOffset > this->sourceTextOffset )
      i->sourceTextOffset = this->textLength + sourceTextOffset - this->sourceTextLength;
  }
  this->sourceTextLength = this->textLength;
  return 1;
}

// FUNC: public: virtual bool __thiscall idDeclLocal::SourceFileChanged(void)const
bool __thiscall idDeclLocal::SourceFileChanged(idDeclLocal *this)
{
  idFileSystem_vtbl *v2; // edi
  int v3; // eax
  int v4; // eax
  idDeclFile *sourceFile; // esi
  bool result; // al
  unsigned int newTimestamp; // [esp+Ch] [ebp-4h] BYREF

  result = 0;
  if ( !com_SingleDeclFile.internalVar->integerValue && this->sourceFile->fileSize > 0 )
  {
    v2 = fileSystem->__vftable;
    v3 = ((int (__thiscall *)(idDeclLocal *, _DWORD, unsigned int *))this->GetFileName)(this, 0, &newTimestamp);
    v4 = ((int (__thiscall *)(idFileSystem *, int))v2->ReadFile)(fileSystem, v3);
    sourceFile = this->sourceFile;
    if ( v4 != sourceFile->fileSize || newTimestamp != sourceFile->timestamp )
      return 1;
  }
  return result;
}

// FUNC: protected: virtual bool __thiscall idDeclLocal::Parse(char const *,int,bool)
char __thiscall idDeclLocal::Parse(idDeclLocal *this, const char *text, int textLength, bool noCaching)
{
  idDeclLocal_vtbl *v5; // eax
  const char *v6; // eax
  int v8; // [esp-4h] [ebp-DCh]
  idLexer src; // [esp+4h] [ebp-D4h] BYREF
  int v10; // [esp+D4h] [ebp-4h]

  idLexer::idLexer(&src);
  v5 = this->__vftable;
  v10 = 0;
  v8 = v5->GetLineNum(this);
  v6 = this->GetFileName(this);
  idLexer::LoadMemory(&src, text, textLength, v6, v8);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  idLexer::SkipBracedSection(&src, 0);
  v10 = -1;
  idLexer::~idLexer(&src);
  return 1;
}

// FUNC: protected: void __thiscall idDeclLocal::ParseLocal(bool)
void __thiscall idDeclLocal::ParseLocal(idDeclLocal *this, int noCaching)
{
  bool v3; // zf
  idDecl *v4; // eax
  idDeclLocal_vtbl *v5; // edx
  int v6; // eax
  void *v7; // esp
  int v8; // eax
  char v9; // cl
  idDeclLocal_vtbl *v10; // eax
  const char *v11; // eax
  const char *v12; // ebx
  char *data; // edx
  char *v14; // ecx
  char v15; // al
  unsigned int v16; // ebx
  int v17; // eax
  void *v18; // esp
  char *v19; // eax
  idFileSystem_vtbl *v20; // edx
  idFile *v21; // edi
  char *v22; // ebx
  int v23; // eax
  void *v24; // esp
  idDecl *self; // edi
  int v26; // eax
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v28; // edx
  int v29; // edi
  int v30; // eax
  int v31; // eax
  idDecl_vtbl *v32; // edi
  int v33; // eax
  int v34; // [esp-Ch] [ebp-1DCh]
  _DWORD v35[3]; // [esp+0h] [ebp-1D0h] BYREF
  idLexer src2; // [esp+Ch] [ebp-1C4h] BYREF
  idLexer src; // [esp+D4h] [ebp-FCh] BYREF
  idToken token; // [esp+19Ch] [ebp-34h] BYREF
  idStr name; // [esp+1ECh] [ebp+1Ch] BYREF
  idStr def; // [esp+20Ch] [ebp+3Ch] BYREF
  int offset; // [esp+22Ch] [ebp+5Ch]
  char *declText; // [esp+230h] [ebp+60h]
  bool generatedDefaultText; // [esp+237h] [ebp+67h]
  int v44; // [esp+240h] [ebp+70h]

  v3 = this->self == 0;
  generatedDefaultText = 0;
  if ( v3 )
  {
    v4 = declManagerLocal.declTypes.list[this->type]->allocator();
    this->self = v4;
    v4->base = this;
  }
  this->self->FreeData(this->self);
  idDeclManagerLocal::MediaPrint(
    &declManagerLocal,
    "parsing %s %s\n",
    declManagerLocal.declTypes.list[this->type]->typeName.data,
    this->name.data);
  if ( !this->textSource )
    generatedDefaultText = this->self->SetDefaultText(this->self);
  ++declManagerLocal.indent;
  if ( this->textSource )
  {
    v5 = this->__vftable;
    this->declState = DS_PARSED;
    v6 = v5->GetTextLength(this) + 4;
    LOBYTE(v6) = v6 & 0xFC;
    v7 = alloca(v6);
    this->GetText(this, (char *)v35);
    if ( !idStr::Icmpn((const char *)v35, "{ STUB:", 7) )
    {
      idLexer::idLexer(&src);
      v44 = 0;
      idLexer::LoadMemory(
        &src,
        (const char *)v35,
        (char *)v35 + strlen((const char *)v35) + 1 - ((char *)v35 + 1),
        &entityFilter,
        1);
      token.len = 0;
      token.floatvalue = 0.0;
      src.flags = 6300;
      token.alloced = 20;
      token.data = token.baseBuffer;
      token.baseBuffer[0] = 0;
      def.alloced = 20;
      def.data = def.baseBuffer;
      def.baseBuffer[0] = 0;
      v8 = 0;
      do
      {
        v9 = *(&entityFilter + v8);
        def.baseBuffer[v8++] = v9;
      }
      while ( v9 );
      def.len = 0;
      v10 = this->__vftable;
      LOBYTE(v44) = 2;
      v11 = v10->GetName(this);
      v12 = v11;
      name.len = 0;
      name.alloced = 20;
      name.data = name.baseBuffer;
      name.baseBuffer[0] = 0;
      if ( v11 )
      {
        declText = (char *)strlen(v11);
        if ( (int)(declText + 1) > 20 )
          idStr::ReAllocate(&name, (int)(declText + 1), 1);
        data = name.data;
        v14 = (char *)v12;
        do
        {
          v15 = *v14;
          *data++ = *v14++;
        }
        while ( v15 );
        name.len = (int)declText;
      }
      LOBYTE(v44) = 3;
      idLexer::ExpectTokenString(&src, "{");
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "You should precache: %s",
        name.data);
      this->needsPrecache = 1;
      idLexer::ExpectTokenString(&src, "STUB:");
      offset = idLexer::ParseInt(&src);
      v16 = idLexer::ParseInt(&src);
      idLexer::ExpectTokenString(&src, "}");
      v17 = v16 + 4;
      LOBYTE(v17) = (v16 + 4) & 0xFC;
      v18 = alloca(v17);
      v19 = this->sourceFile->fileName.data;
      v20 = fileSystem->__vftable;
      declText = (char *)v35;
      v21 = v20->OpenFileRead(fileSystem, v19, 1, 0);
      v21->Seek(v21, offset, FS_SEEK_SET);
      v21->Read(v21, declText, v16);
      declText[v16] = 0;
      idLexer::idLexer(&src2);
      v34 = v16;
      v22 = declText;
      LOBYTE(v44) = 4;
      src2.flags = 6300;
      idLexer::LoadMemory(&src2, declText, v34, &entityFilter, 1);
      idLexer::ReadToken(&src2, &token);
      idStr::operator=(&def, v22);
      if ( idStr::Icmp(token.data, "guide") )
      {
        declManager->EvaluateInlineGuide(declManager, &name, &def);
      }
      else
      {
        idLexer::ReadToken(&src2, &token);
        declManager->EvaluateGuide(declManager, &token, &src2, &def);
        declManager->EvaluateInlineGuide(declManager, &token, &def);
      }
      fileSystem->CloseFile(fileSystem, v21);
      idDeclLocal::SetTextLocal(this, def.data, def.len);
      v23 = def.len + 4;
      LOBYTE(v23) = (LOBYTE(def.len) + 4) & 0xFC;
      v24 = alloca(v23);
      SIMDProcessor->Memcpy(SIMDProcessor, v35, def.data, def.len + 1);
      LOBYTE(v44) = 3;
      idLexer::~idLexer(&src2);
      LOBYTE(v44) = 2;
      idStr::FreeData(&name);
      LOBYTE(v44) = 1;
      idStr::FreeData(&def);
      LOBYTE(v44) = 0;
      idStr::FreeData(&token);
      v44 = -1;
      idLexer::~idLexer(&src);
    }
    if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 16))(common.type)
      && !declManager->GetInsideLoad(declManager)
      && !(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, -1) )
    {
      self = this->self;
      v26 = ((int (__thiscall *)(idDeclBase *, _DWORD))self->base->GetType)(self->base, v35[0]);
      base = self->base;
      v28 = base->__vftable;
      offset = v26;
      v29 = *(_DWORD *)common.type;
      v30 = (int)v28->GetName(base);
      v31 = ((int (__thiscall *)(idDeclManager *, int, int))declManager->GetDeclNameFromType)(declManager, offset, v30);
      (*(void (__cdecl **)(netadrtype_t, const char *, int))(v29 + 136))(
        common.type,
        "Loading non pre-cached %s decl %s",
        v31);
    }
    v32 = this->self->__vftable;
    v33 = ((int (__thiscall *)(idDeclLocal *, int))this->GetTextLength)(this, noCaching);
    ((void (__thiscall *)(idDecl *, _DWORD *, int))v32->Parse)(this->self, v35, v33);
    if ( generatedDefaultText || com_SingleDeclFile.internalVar->integerValue && !this->needsPrecache )
    {
      Mem_Free(this->textSource);
      this->textSource = 0;
      this->textLength = 0;
    }
    --declManagerLocal.indent;
  }
  else
  {
    this->MakeDefault(this);
    --declManagerLocal.indent;
  }
}

// FUNC: public: void __thiscall rvDeclGuide::Parse(class idLexer *)
void __thiscall rvDeclGuide::Parse(rvDeclGuide *this, idLexer *src)
{
  int v3; // ebp
  unsigned int mNumParms; // eax
  int v5; // eax
  idStr definition; // [esp+8h] [ebp-7Ch] BYREF
  idToken token; // [esp+28h] [ebp-5Ch] BYREF
  int v8; // [esp+80h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v8 = 1;
  definition.len = 0;
  definition.alloced = 20;
  definition.data = definition.baseBuffer;
  definition.baseBuffer[0] = 0;
  v3 = 0;
  idLexer::ExpectTokenString(src, "(");
  this->mNumParms = 0;
  idLexer::ReadToken(src, &token);
  while ( idStr::Cmp(token.data, ")") )
  {
    if ( idStr::Cmp(token.data, ",") )
    {
      mNumParms = this->mNumParms;
      if ( mNumParms <= 0x13 )
        idStr::operator=(&this->mParms[mNumParms], token.data);
      ++this->mNumParms;
    }
    else
    {
      ++v3;
    }
    idLexer::ReadToken(src, &token);
  }
  v5 = this->mNumParms;
  if ( v3 != v5 - 1 )
    idLexer::Warning(
      src,
      "Guide name '%s' only contains %d commas for %d args, expecting %d! Typo?\n",
      this->mName.data,
      v3,
      v5,
      v5 - 1);
  idLexer::ParseBracedSectionExact(src, &this->mDefinition, -1);
  LOBYTE(v8) = 0;
  idStr::FreeData(&definition);
  v8 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: __thiscall rvDeclGuide::~rvDeclGuide(void)
void __thiscall rvDeclGuide::~rvDeclGuide(rvDeclGuide *this)
{
  int v2; // ebp
  char *baseBuffer; // esi

  idStr::FreeData(&this->mName);
  v2 = 20;
  this->mName.len = 0;
  this->mName.alloced = 20;
  this->mName.data = this->mName.baseBuffer;
  this->mName.baseBuffer[0] = 0;
  baseBuffer = this->mParms[0].baseBuffer;
  do
  {
    idStr::FreeData((idStr *)(baseBuffer - 12));
    *((_DWORD *)baseBuffer - 1) = 20;
    *((_DWORD *)baseBuffer - 2) = baseBuffer;
    *((_DWORD *)baseBuffer - 3) = 0;
    *baseBuffer = 0;
    baseBuffer += 32;
    --v2;
  }
  while ( v2 );
  idStr::FreeData(&this->mDefinition);
  this->mDefinition.len = 0;
  this->mDefinition.alloced = 20;
  this->mDefinition.data = this->mDefinition.baseBuffer;
  this->mDefinition.baseBuffer[0] = 0;
  idStr::FreeData(&this->mDefinition);
  `eh vector destructor iterator'(
    this->mParms,
    0x20u,
    20,
    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  idStr::FreeData(&this->mName);
}

// FUNC: public: virtual bool __thiscall idDeclManagerLocal::Validate(enum declType_t,int,class idStr &)
int __thiscall idDeclManagerLocal::Validate(idDeclManagerLocal *this, declType_t type, int iIndex, idStr *strReportTo)
{
  const idDecl *v4; // esi
  int v5; // eax
  void *v6; // esp
  idDecl_vtbl *v7; // ebx
  int v8; // eax
  _BYTE v10[24]; // [esp-Ch] [ebp-18h] BYREF

  v4 = this->DeclByIndex(this, type, iIndex, 0);
  v5 = v4->base->GetTextLength(v4->base) + 4;
  LOBYTE(v5) = v5 & 0xFC;
  v6 = alloca(v5);
  v4->base->GetText(v4->base, v10);
  v7 = v4->__vftable;
  v8 = ((int (__thiscall *)(idDeclBase *, idStr *))v4->base->GetTextLength)(v4->base, strReportTo);
  return ((int (__thiscall *)(const idDecl *, _BYTE *, int))v7->Validate)(v4, v10, v8);
}

// FUNC: public: virtual class idDecl * __thiscall idDeclManagerLocal::AllocateDecl(enum declType_t)
idDecl *__thiscall idDeclManagerLocal::AllocateDecl(idDeclManagerLocal *this, declType_t type)
{
  idDeclLocal *v2; // eax
  idDeclBase *v3; // esi
  idDeclBase *v4; // eax
  idDecl *result; // eax

  v2 = (idDeclLocal *)Memory::Allocate(0x60u);
  v3 = 0;
  if ( v2 )
  {
    idDeclLocal::idDeclLocal(v2);
    v3 = v4;
  }
  result = declManagerLocal.declTypes.list[type]->allocator();
  result->base = v3;
  return result;
}

// FUNC: void __cdecl FlushDecls_f(class idCmdArgs const &)
void __cdecl FlushDecls_f()
{
  idDeclManagerLocal::FlushDecls(&declManagerLocal);
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::RegisterDeclType(char const *,enum declType_t,class idDecl * (__cdecl *)(void))
void __thiscall idDeclManagerLocal::RegisterDeclType(
        idDeclManagerLocal *this,
        char *typeName,
        int type,
        idDecl *(__cdecl *allocator)())
{
  declType_t v4; // ebp
  _DWORD *v6; // eax
  idDeclType *v7; // ebx
  int granularity; // ecx
  int size; // eax
  __int32 v10; // edi
  bool v11; // cc
  idDeclType **list; // ebp
  int i; // eax
  int j; // eax

  v4 = type;
  if ( type < this->declTypes.num && this->declTypes.list[type] )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "idDeclManager::RegisterDeclType: type '%s' already exists",
      typeName);
  }
  else
  {
    v6 = Memory::Allocate(0x28u);
    if ( v6 )
    {
      *v6 = 0;
      v6[2] = 20;
      v6[1] = v6 + 3;
      *((_BYTE *)v6 + 12) = 0;
      v7 = (idDeclType *)v6;
    }
    else
    {
      v7 = 0;
    }
    idStr::operator=(&v7->typeName, typeName);
    v7->type = type;
    v7->allocator = allocator;
    if ( type + 1 > this->declTypes.num )
    {
      if ( type + 1 > this->declTypes.size )
      {
        if ( !this->declTypes.granularity )
          this->declTypes.granularity = 16;
        granularity = this->declTypes.granularity;
        size = this->declTypes.size;
        this->declTypes.num = size;
        v10 = type + granularity - (type + granularity) % granularity;
        if ( v10 > 0 )
        {
          if ( v10 != size )
          {
            v11 = v10 < this->declTypes.num;
            list = this->declTypes.list;
            this->declTypes.size = v10;
            if ( v11 )
              this->declTypes.num = v10;
            this->declTypes.list = (idDeclType **)Memory::Allocate(4 * v10);
            for ( i = 0; i < this->declTypes.num; ++i )
              this->declTypes.list[i] = list[i];
            if ( list )
              Memory::Free(list);
            v4 = type;
          }
        }
        else
        {
          if ( this->declTypes.list )
            Memory::Free(this->declTypes.list);
          this->declTypes.list = 0;
          this->declTypes.num = 0;
          this->declTypes.size = 0;
        }
        for ( j = this->declTypes.num; j < v10; ++j )
          this->declTypes.list[j] = 0;
      }
      this->declTypes.num = type + 1;
    }
    this->declTypes.list[v4] = v7;
  }
}

// FUNC: public: virtual class idDecl const * __thiscall idDeclManagerLocal::DeclByIndex(enum declType_t,int,bool)
const idDecl *__thiscall idDeclManagerLocal::DeclByIndex(
        idDeclManagerLocal *this,
        int type,
        int index,
        bool forceParse)
{
  char *v5; // edi
  int v6; // esi
  idDecl *v7; // eax

  if ( type < 0 || type >= this->declTypes.num || !this->declTypes.list[type] )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idDeclManager::DeclByIndex: bad type: %i",
      type);
  if ( index < 0 || (v5 = (char *)this + 16 * type, index >= *((_DWORD *)v5 + 238)) )
  {
    v5 = (char *)this + 16 * type;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idDeclManager::DeclByIndex: out of range for type %d (index desired: %d, max: %d)",
      type,
      index,
      *((_DWORD *)v5 + 238));
  }
  v6 = *(_DWORD *)(*((_DWORD *)v5 + 241) + 4 * index);
  if ( !*(_DWORD *)(v6 + 4) )
  {
    v7 = declManagerLocal.declTypes.list[*(_DWORD *)(v6 + 72)]->allocator();
    *(_DWORD *)(v6 + 4) = v7;
    v7->base = (idDeclBase *)v6;
  }
  if ( forceParse && !*(_DWORD *)(v6 + 76) )
    idDeclLocal::ParseLocal((idDeclLocal *)v6, 0);
  return *(const idDecl **)(v6 + 4);
}

// FUNC: public: virtual class idDecl * __thiscall idDeclManagerLocal::CreateNewDecl(enum declType_t,char const *,char const *)
idDecl *__thiscall idDeclManagerLocal::CreateNewDecl(
        idDeclManagerLocal *this,
        int type,
        const char *name,
        idDeclFile *_fileName)
{
  const char *v5; // eax
  int v6; // esi
  int v7; // eax
  char *data; // edx
  idDeclFile *v9; // ecx
  char len; // al
  int v11; // esi
  idHashIndex *v12; // edi
  unsigned __int8 v13; // cl
  char *v14; // eax
  int v15; // edx
  int v16; // edx
  int v17; // esi
  int i; // esi
  idDeclBase *v19; // edi
  idDecl *v20; // eax
  idDecl *self; // esi
  idDeclFile *v23; // esi
  char *v24; // ecx
  bool v25; // zf
  int granularity; // eax
  bool v27; // cc
  int j; // eax
  int num; // edi
  int v30; // eax
  int v31; // ecx
  idDeclFile **list; // esi
  int k; // eax
  idDeclLocal *v34; // eax
  int v35; // eax
  int v36; // edi
  idDecl *v37; // eax
  idDeclType *v38; // esi
  char *v39; // ecx
  char *v40; // edx
  char v41; // al
  int *v42; // ecx
  int v43; // edx
  const char *v44; // esi
  const char *v45; // ecx
  unsigned int v46; // eax
  int v47; // eax
  char *v48; // edx
  const char *v49; // ecx
  char v50; // al
  int v51; // eax
  const char *v52; // eax
  int v53; // eax
  void *v54; // esp
  int m; // eax
  int n; // eax
  int ii; // eax
  idList<idDeclLocal *> *v58; // esi
  int v59; // eax
  int jj; // eax
  int v61; // ecx
  int v62; // ecx
  idDeclLocal **v63; // ebx
  int kk; // eax
  int v65; // ebx
  idHashIndex *v66; // esi
  int indexSize; // eax
  int v68; // eax
  int v69; // edi
  char v70[12]; // [esp+0h] [ebp-484h] BYREF
  char canonicalName[1024]; // [esp+Ch] [ebp-478h] BYREF
  idStr defaultText; // [esp+40Ch] [ebp-78h] BYREF
  idStr fileName; // [esp+42Ch] [ebp-58h] BYREF
  idHashIndex *v74; // [esp+44Ch] [ebp-38h]
  int hash; // [esp+450h] [ebp-34h]
  int size; // [esp+454h] [ebp-30h]
  idStr header; // [esp+458h] [ebp-2Ch] BYREF
  int v78; // [esp+480h] [ebp-4h]
  idDeclLocal ***namea; // [esp+490h] [ebp+Ch]
  idDeclFile *nameb; // [esp+490h] [ebp+Ch]
  const char *namec; // [esp+490h] [ebp+Ch]
  const char *named; // [esp+490h] [ebp+Ch]
  idDeclFile *sourceFile; // [esp+494h] [ebp+10h]

  if ( type < 0 || type >= this->declTypes.num || !this->declTypes.list[type] )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idDeclManager::CreateNewDecl: bad type: %i",
      type);
  idDeclManagerLocal::MakeNameCanonical(name, canonicalName, 1024);
  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  if ( _fileName )
  {
    v5 = (char *)&_fileName->fileName.len + strlen((const char *)_fileName) + 1;
    v6 = v5 - ((const char *)&_fileName->fileName.len + 1);
    v7 = v5 - (const char *)_fileName;
    if ( v7 > 20 )
      idStr::ReAllocate(&fileName, v7, 1);
    data = fileName.data;
    v9 = _fileName;
    do
    {
      len = v9->fileName.len;
      *data = v9->fileName.len;
      v9 = (idDeclFile *)((char *)v9 + 1);
      ++data;
    }
    while ( len );
    fileName.len = v6;
  }
  v11 = 0;
  v78 = 0;
  idStr::BackSlashesToSlashes(&fileName);
  v12 = &this->hashTables[type];
  v13 = canonicalName[0];
  v74 = v12;
  v14 = canonicalName;
  if ( canonicalName[0] )
  {
    v11 = 0;
    do
    {
      if ( idStr::lowerCaseCharacter[v13] )
        v13 = idStr::lowerCaseCharacter[v13];
      v15 = (char)v13 * (_DWORD)&v14[119 - (_DWORD)canonicalName];
      v13 = *++v14;
      v11 += v15;
    }
    while ( v13 );
  }
  v16 = v11 & v12->hashMask & v12->hashMask & v12->lookupMask;
  hash = v11 & v12->hashMask;
  v17 = v12->hash[v16];
  if ( v17 < 0 )
  {
LABEL_20:
    for ( i = 0; i < this->loadedFiles.num; ++i )
    {
      if ( !idStr::Icmp(this->loadedFiles.list[i]->fileName.data, fileName.data) )
        break;
    }
    if ( i >= this->loadedFiles.num )
    {
      v23 = (idDeclFile *)Memory::Allocate(0x38u);
      if ( v23 )
      {
        v24 = fileName.data;
        v23->fileName.len = 0;
        v23->fileName.alloced = 20;
        v23->fileName.data = v23->fileName.baseBuffer;
        v23->fileName.baseBuffer[0] = 0;
        LOBYTE(v78) = 2;
        idStr::operator=(&v23->fileName, v24);
        v23->defaultType = type;
        v23->timestamp = 0;
        v23->checksum = 0;
        v23->fileSize = 0;
        v23->numLines = 0;
        v23->decls = 0;
      }
      else
      {
        v23 = 0;
      }
      v25 = this->loadedFiles.list == 0;
      nameb = v23;
      LOBYTE(v78) = 0;
      sourceFile = v23;
      if ( v25 )
      {
        granularity = this->loadedFiles.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->loadedFiles.size )
          {
            v27 = granularity < this->loadedFiles.num;
            this->loadedFiles.size = granularity;
            if ( v27 )
              this->loadedFiles.num = granularity;
            this->loadedFiles.list = (idDeclFile **)Memory::Allocate(4 * granularity);
            for ( j = 0; j < this->loadedFiles.num; ++j )
              this->loadedFiles.list[j] = *(idDeclFile **)(4 * j);
          }
        }
        else
        {
          this->loadedFiles.list = 0;
          this->loadedFiles.num = 0;
          this->loadedFiles.size = 0;
        }
      }
      num = this->loadedFiles.num;
      v30 = this->loadedFiles.size;
      if ( num == v30 )
      {
        if ( !this->loadedFiles.granularity )
          this->loadedFiles.granularity = 16;
        v31 = this->loadedFiles.granularity
            + v30
            - (this->loadedFiles.granularity + v30) % this->loadedFiles.granularity;
        if ( v31 > 0 )
        {
          if ( v31 != this->loadedFiles.size )
          {
            list = this->loadedFiles.list;
            this->loadedFiles.size = v31;
            if ( v31 < num )
              this->loadedFiles.num = v31;
            this->loadedFiles.list = (idDeclFile **)Memory::Allocate(4 * v31);
            for ( k = 0; k < this->loadedFiles.num; ++k )
              this->loadedFiles.list[k] = list[k];
            if ( list )
              Memory::Free(list);
          }
        }
        else
        {
          if ( this->loadedFiles.list )
            Memory::Free(this->loadedFiles.list);
          this->loadedFiles.list = 0;
          this->loadedFiles.num = 0;
          this->loadedFiles.size = 0;
        }
      }
      this->loadedFiles.list[this->loadedFiles.num++] = nameb;
    }
    else
    {
      sourceFile = this->loadedFiles.list[i];
    }
    v34 = (idDeclLocal *)Memory::Allocate(0x60u);
    LOBYTE(v78) = 3;
    if ( v34 )
    {
      idDeclLocal::idDeclLocal(v34);
      v36 = v35;
    }
    else
    {
      v36 = 0;
    }
    LOBYTE(v78) = 0;
    idStr::operator=((idStr *)(v36 + 8), canonicalName);
    v25 = *(_DWORD *)(v36 + 4) == 0;
    *(_DWORD *)(v36 + 72) = type;
    *(_DWORD *)(v36 + 76) = 0;
    if ( v25 )
    {
      v37 = declManagerLocal.declTypes.list[type]->allocator();
      *(_DWORD *)(v36 + 4) = v37;
      v37->base = (idDeclBase *)v36;
    }
    v38 = this->declTypes.list[type];
    header.data = header.baseBuffer;
    header.len = 0;
    header.alloced = 20;
    header.baseBuffer[0] = 0;
    namec = (const char *)v38->typeName.len;
    if ( v38->typeName.len + 1 > 20 )
      idStr::ReAllocate(&header, (int)(namec + 1), 1);
    v39 = v38->typeName.data;
    v40 = header.data;
    do
    {
      v41 = *v39;
      *v40++ = *v39++;
    }
    while ( v41 );
    header.len = (int)namec;
    v42 = *(int **)(v36 + 4);
    v43 = *v42;
    LOBYTE(v78) = 4;
    v44 = (const char *)(*(int (__thiscall **)(int *))(v43 + 8))(v42);
    v45 = 0;
    defaultText.len = 0;
    defaultText.alloced = 20;
    defaultText.data = defaultText.baseBuffer;
    defaultText.baseBuffer[0] = 0;
    if ( v44 )
    {
      v46 = (unsigned int)&v44[strlen(v44) + 1];
      named = (const char *)(v46 - (_DWORD)(v44 + 1));
      v47 = v46 - (_DWORD)v44;
      if ( v47 > 20 )
        idStr::ReAllocate(&defaultText, v47, 1);
      v48 = defaultText.data;
      v49 = v44;
      do
      {
        v50 = *v49;
        *v48++ = *v49++;
      }
      while ( v50 );
      v45 = named;
      defaultText.len = (int)named;
    }
    v51 = 0;
    for ( LOBYTE(v78) = 5; canonicalName[v51]; ++v51 )
      ;
    v52 = &v45[v51];
    size = (int)&v52[header.len + 2];
    v53 = (int)&v52[header.len + 6];
    LOBYTE(v53) = v53 & 0xFC;
    v54 = alloca(v53);
    SIMDProcessor->Memcpy(SIMDProcessor, v70, header.data, header.len);
    v70[header.len] = 32;
    for ( m = 0; canonicalName[m]; ++m )
      ;
    SIMDProcessor->Memcpy(SIMDProcessor, &v70[header.len + 1], canonicalName, m);
    for ( n = 0; canonicalName[n]; ++n )
      ;
    v70[n + 1 + header.len] = 32;
    for ( ii = 0; canonicalName[ii]; ++ii )
      ;
    SIMDProcessor->Memcpy(SIMDProcessor, &v70[ii + 2 + header.len], defaultText.data, defaultText.len + 1);
    idDeclLocal::SetTextLocal((idDeclLocal *)v36, v70, size);
    *(_DWORD *)(v36 + 52) = sourceFile;
    *(_DWORD *)(v36 + 56) = sourceFile->fileSize;
    *(_DWORD *)(v36 + 60) = 0;
    *(_DWORD *)(v36 + 64) = sourceFile->numLines;
    idDeclLocal::ParseLocal((idDeclLocal *)v36, 0);
    *(_DWORD *)(v36 + 88) = sourceFile->decls;
    sourceFile->decls = (idDeclLocal *)v36;
    v58 = &this->linearLists[type];
    *(_DWORD *)(v36 + 80) = v58->num;
    if ( !this->linearLists[type].list )
    {
      v59 = this->linearLists[type].granularity;
      if ( v59 > 0 )
      {
        if ( v59 != this->linearLists[type].size )
        {
          v27 = v59 < v58->num;
          this->linearLists[type].size = v59;
          if ( v27 )
            v58->num = v59;
          this->linearLists[type].list = (idDeclLocal **)Memory::Allocate(4 * v59);
          for ( jj = 0; jj < v58->num; ++jj )
            this->linearLists[type].list[jj] = *(idDeclLocal **)(4 * jj);
        }
      }
      else
      {
        this->linearLists[type].list = 0;
        v58->num = 0;
        this->linearLists[type].size = 0;
      }
    }
    v61 = this->linearLists[type].size;
    if ( v58->num == v61 )
    {
      if ( !this->linearLists[type].granularity )
        this->linearLists[type].granularity = 16;
      v62 = this->linearLists[type].granularity
          + v61
          - (this->linearLists[type].granularity + v61) % this->linearLists[type].granularity;
      if ( v62 > 0 )
      {
        if ( v62 != this->linearLists[type].size )
        {
          v27 = v62 < v58->num;
          v63 = this->linearLists[type].list;
          v58->size = v62;
          if ( v27 )
            v58->num = v62;
          v58->list = (idDeclLocal **)Memory::Allocate(4 * v62);
          for ( kk = 0; kk < v58->num; ++kk )
            v58->list[kk] = v63[kk];
          if ( v63 )
            Memory::Free(v63);
        }
      }
      else
      {
        if ( this->linearLists[type].list )
          Memory::Free(this->linearLists[type].list);
        this->linearLists[type].list = 0;
        v58->num = 0;
        this->linearLists[type].size = 0;
      }
    }
    v58->list[v58->num++] = (idDeclLocal *)v36;
    v65 = v58->num - 1;
    v66 = v74;
    if ( v74->hash == idHashIndex::INVALID_INDEX )
    {
      indexSize = v74->indexSize;
      if ( v65 >= indexSize )
        indexSize = v65 + 1;
      idHashIndex::Allocate(v74, v74->hashSize, indexSize);
    }
    else if ( v65 >= v74->indexSize )
    {
      idHashIndex::ResizeIndex(v74, v65 + 1);
    }
    v68 = hash & v66->hashMask;
    v66->indexChain[v65] = v66->hash[v68];
    v66->hash[v68] = v65;
    v69 = *(_DWORD *)(v36 + 4);
    LOBYTE(v78) = 4;
    idStr::FreeData(&defaultText);
    LOBYTE(v78) = 0;
    idStr::FreeData(&header);
    v78 = -1;
    idStr::FreeData(&fileName);
    return (idDecl *)v69;
  }
  else
  {
    namea = &this->linearLists[type].list;
    while ( idStr::Icmp((*namea)[v17]->name.data, canonicalName) )
    {
      v17 = v12->indexChain[v17 & v12->lookupMask];
      if ( v17 < 0 )
        goto LABEL_20;
    }
    v19 = (*namea)[v17];
    if ( !v19[1].__vftable )
    {
      v20 = declManagerLocal.declTypes.list[(int)v19[18].__vftable]->allocator();
      v19[1].__vftable = (idDeclBase_vtbl *)v20;
      v20->base = v19;
    }
    self = (*namea)[v17]->self;
    v78 = -1;
    idStr::FreeData(&fileName);
    return self;
  }
}

// FUNC: public: virtual bool __thiscall idDeclManagerLocal::RenameDecl(enum declType_t,char const *,char const *)
char __thiscall idDeclManagerLocal::RenameDecl(
        idDeclManagerLocal *this,
        declType_t type,
        const char *oldName,
        const char *newName)
{
  declType_t v5; // ebx
  idHashIndex *v6; // esi
  unsigned __int8 v7; // cl
  int v8; // edi
  char *v9; // eax
  int v10; // edx
  int v11; // edi
  idDeclLocal ***p_list; // ebx
  idDeclLocal *v14; // ebx
  unsigned __int8 v15; // al
  int v16; // ebp
  char *i; // ecx
  int v18; // edx
  int index; // ebx
  int v20; // edi
  int indexSize; // eax
  int v22; // eax
  int v23; // edx
  int *v24; // ecx
  int v25; // eax
  int v26; // edi
  int v27; // edi
  int *indexChain; // edi
  int v29; // ecx
  int hash; // [esp+10h] [ebp-808h]
  idDeclLocal *decl; // [esp+14h] [ebp-804h]
  char canonicalOldName[1024]; // [esp+18h] [ebp-800h] BYREF
  char canonicalNewName[1024]; // [esp+418h] [ebp-400h] BYREF

  idDeclManagerLocal::MakeNameCanonical(oldName, canonicalOldName, 1024);
  idDeclManagerLocal::MakeNameCanonical(newName, canonicalNewName, 1024);
  v5 = type;
  v6 = &this->hashTables[type];
  v7 = canonicalOldName[0];
  v8 = 0;
  v9 = canonicalOldName;
  if ( canonicalOldName[0] )
  {
    do
    {
      if ( idStr::lowerCaseCharacter[v7] )
        v7 = idStr::lowerCaseCharacter[v7];
      v10 = (char)v7 * (_DWORD)&v9[119 - (_DWORD)canonicalOldName];
      v7 = *++v9;
      v8 += v10;
    }
    while ( v7 );
    v5 = type;
  }
  hash = v8 & v6->hashMask;
  v11 = v6->hash[hash & v6->hashMask & v6->lookupMask];
  if ( v11 < 0 )
    return 0;
  p_list = &this->linearLists[v5].list;
  while ( idStr::Icmp((*p_list)[v11]->name.data, canonicalOldName) )
  {
    v11 = v6->indexChain[v11 & v6->lookupMask];
    if ( v11 < 0 )
      return 0;
  }
  v14 = (*p_list)[v11];
  decl = v14;
  if ( !v14 )
    return 0;
  idStr::operator=(&v14->name, canonicalNewName);
  v15 = canonicalNewName[0];
  v16 = 0;
  for ( i = canonicalNewName; v15; v16 += v18 )
  {
    if ( idStr::lowerCaseCharacter[v15] )
      v15 = idStr::lowerCaseCharacter[v15];
    v18 = (char)v15 * (_DWORD)&i[119 - (_DWORD)canonicalNewName];
    v15 = *++i;
  }
  index = v14->index;
  v20 = v16 & v6->hashMask;
  if ( v6->hash == idHashIndex::INVALID_INDEX )
  {
    indexSize = v6->indexSize;
    if ( index >= indexSize )
      indexSize = index + 1;
    idHashIndex::Allocate(v6, v6->hashSize, indexSize);
  }
  else if ( index >= v6->indexSize )
  {
    idHashIndex::ResizeIndex(v6, index + 1);
  }
  v22 = v20 & v6->hashMask;
  v6->indexChain[index] = v6->hash[v22];
  v6->hash[v22] = index;
  v23 = decl->index;
  v24 = v6->hash;
  v25 = hash & v6->hashMask;
  if ( v24 != idHashIndex::INVALID_INDEX )
  {
    v26 = v24[v25];
    if ( v26 == v23 )
    {
      v27 = v6->indexChain[v23];
    }
    else
    {
      v25 = v24[v25];
      if ( v26 == -1 )
      {
LABEL_32:
        v6->indexChain[v23] = -1;
        return 1;
      }
      while ( 1 )
      {
        indexChain = v6->indexChain;
        v29 = indexChain[v25];
        if ( v29 == v23 )
          break;
        v25 = indexChain[v25];
        if ( v29 == -1 )
          goto LABEL_32;
      }
      v24 = v6->indexChain;
      v27 = v24[v23];
    }
    v24[v25] = v27;
    goto LABEL_32;
  }
  return 1;
}

// FUNC: class idStr __cdecl GetString(class idFile *)
idStr *__cdecl GetString(idStr *result, idFile *file)
{
  idFile *v2; // esi
  idFile_vtbl *v3; // edx
  char i; // al
  char v5; // bl
  int len; // edi
  char *data; // ecx
  char *v8; // edx
  char v9; // al
  idStr ret; // [esp+14h] [ebp-2Ch] BYREF
  int v12; // [esp+3Ch] [ebp-4h]

  ret.len = 0;
  ret.alloced = 20;
  ret.data = ret.baseBuffer;
  ret.baseBuffer[0] = 0;
  v2 = file;
  v3 = file->__vftable;
  v12 = 1;
  v3->Read(file, &file, 1);
  for ( i = (char)file; (_BYTE)file != 10; i = (char)file )
  {
    v5 = i;
    if ( ret.len + 2 > ret.alloced )
      idStr::ReAllocate(&ret, ret.len + 2, 1);
    ret.data[ret.len++] = v5;
    ret.data[ret.len] = 0;
    v2->Read(v2, &file, 1);
  }
  result->data = result->baseBuffer;
  result->len = 0;
  result->alloced = 20;
  result->baseBuffer[0] = 0;
  len = ret.len;
  if ( ret.len + 1 > result->alloced )
    idStr::ReAllocate(result, ret.len + 1, 1);
  data = ret.data;
  v8 = result->data;
  do
  {
    v9 = *data;
    *v8++ = *data++;
  }
  while ( v9 );
  result->len = len;
  LOBYTE(v12) = 0;
  idStr::FreeData(&ret);
  return result;
}

// FUNC: public: void __thiscall idDeclManagerLocal::CheckDecls(void)
void __thiscall idDeclManagerLocal::CheckDecls(idDeclManagerLocal *this)
{
  int i; // edi
  idDeclLocal *j; // esi

  for ( i = 0; i < this->loadedFiles.num; ++i )
  {
    for ( j = this->loadedFiles.list[i]->decls; j; j = j->nextInFile )
    {
      if ( j->declState != DS_PARSED )
        idDeclLocal::ParseLocal(j, 0);
    }
  }
}

// FUNC: private: unsigned int __thiscall idDeclManagerLocal::NumWritableDecls(class idDeclFile *,class idList<enum declType_t> const &,bool)
unsigned int __thiscall idDeclManagerLocal::NumWritableDecls(
        idDeclManagerLocal *this,
        idDeclFile *declFile,
        const idList<enum declType_t> *typesToCount,
        bool writeStubs)
{
  idDeclLocal *decls; // ebx
  unsigned int result; // eax
  int num; // ebp
  int v7; // ecx
  declType_t *list; // edx
  declType_t *v9; // ecx
  bool v10; // cl
  unsigned int count; // [esp+0h] [ebp-4h]

  decls = declFile->decls;
  result = 0;
  count = 0;
  if ( decls )
  {
    num = typesToCount->num;
    do
    {
      v7 = 0;
      if ( num <= 0 )
        goto LABEL_7;
      list = typesToCount->list;
      while ( *list != decls->type )
      {
        ++v7;
        ++list;
        if ( v7 >= num )
          goto LABEL_7;
      }
      if ( v7 < 0 )
LABEL_7:
        v9 = 0;
      else
        v9 = &typesToCount->list[v7];
      v10 = v9 != 0;
      if ( (decls->declState == DS_PARSED || writeStubs) && v10 )
        ++count;
      decls = decls->nextInFile;
    }
    while ( decls );
    return count;
  }
  return result;
}

// FUNC: private: void __thiscall idDeclManagerLocal::WriteDecls(class idFile *,class idDeclFile *,class idList<enum declType_t> const &,bool)
void __userpurge idDeclManagerLocal::WriteDecls(
        idDeclManagerLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        const char *a4@<edi>,
        int a5@<esi>,
        idFile *file,
        idDeclFile *declFile,
        const idList<enum declType_t> *typesToWrite,
        bool writeStubs,
        int a10,
        int a11,
        idFile *a12)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v13; // esp
  idFile *v14; // ebx
  unsigned int v15; // edi
  idDeclLocal *v16; // ebp
  int v17; // eax
  declType_t *list; // ecx
  declType_t *v19; // eax
  int v20; // esi
  int v21; // eax
  char v22; // cl
  idDeclType *v23; // esi
  int i; // edi
  unsigned int len; // ebp
  int v26; // ebx
  int v27; // eax
  char v28; // cl
  int v29; // edx
  const char *v30; // eax
  const char *v31; // esi
  unsigned int v32; // edi
  char v33; // cl
  int j; // eax
  int v35; // edx
  int v36; // esi
  int v37; // eax
  char v38; // cl
  int v39; // edx
  char **v40; // edi
  int k; // esi
  char v42; // bl
  int v43; // esi
  int v44; // eax
  char v45; // cl
  int v46; // edx
  int v47; // esi
  char *data; // edx
  char *v49; // ecx
  char v50; // al
  idStr *v51; // esi
  int v52; // edi
  int m; // eax
  char v54; // cl
  int v55; // edx
  int v56; // esi
  char *v57; // edx
  char *v58; // ecx
  char v59; // al
  idStr *v60; // esi
  int v61; // edi
  int n; // eax
  char v63; // cl
  int v64; // edx
  int v65; // edi
  idFile_vtbl *v67; // edx
  const char *v68; // [esp+30h] [ebp-191A4h]
  int v69; // [esp+34h] [ebp-191A0h]
  int v70; // [esp+38h] [ebp-1919Ch]
  int v71; // [esp+3Ch] [ebp-19198h]
  idStr v72; // [esp+40h] [ebp-19194h] BYREF
  int decls; // [esp+60h] [ebp-19174h]
  _BYTE v74[20]; // [esp+64h] [ebp-19170h] BYREF
  char **v75; // [esp+78h] [ebp-1915Ch]
  idStr a; // [esp+7Ch] [ebp-19158h] BYREF
  idStr v77; // [esp+9Ch] [ebp-19138h] BYREF
  char string[100]; // [esp+BCh] [ebp-19118h] BYREF
  idStr result; // [esp+120h] [ebp-190B4h] BYREF
  idStr v80; // [esp+140h] [ebp-19094h] BYREF
  char v81[64]; // [esp+160h] [ebp-19074h] BYREF
  char v82[64]; // [esp+1A0h] [ebp-19034h] BYREF
  char v83[102376]; // [esp+1E0h] [ebp-18FF4h] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v84; // [esp+191C8h] [ebp-Ch]
  void *v85; // [esp+191CCh] [ebp-8h]
  int v86; // [esp+191D0h] [ebp-4h]

  v86 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v85 = &_ehhandler__WriteDecls_idDeclManagerLocal__AAEXPAVidFile__PAVidDeclFile__ABV__idList_W4declType_t_____N_Z;
  v84 = ExceptionList;
  v13 = alloca(102792);
  v71 = a2;
  v70 = a3;
  v69 = a5;
  v68 = a4;
  v14 = file;
  v15 = idDeclManagerLocal::NumWritableDecls(this, declFile, typesToWrite, writeStubs);
  if ( v15 )
  {
    ((void (__thiscall *)(idFile *, char *, int, const char *, int, int, int))file->Write)(
      file,
      declFile->fileName.data,
      declFile->fileName.len,
      v68,
      a5,
      a3,
      v71);
    file->Write(file, "\n", 1);
    sprintf(&v77.baseBuffer[12], "%d\n", declFile->defaultType);
    file->Write(file, &v77.baseBuffer[12], strlen(&v77.baseBuffer[12]));
    sprintf(&v77.baseBuffer[4], "%d\n", v15);
    file->Write(file, &v77.baseBuffer[4], strlen(&v77.baseBuffer[4]));
  }
  decls = (int)declFile->decls;
  v16 = (idDeclLocal *)decls;
  if ( decls )
  {
    do
    {
      v17 = 0;
      if ( typesToWrite->num <= 0 )
        goto LABEL_8;
      list = typesToWrite->list;
      while ( *list != v16->type )
      {
        ++v17;
        ++list;
        if ( v17 >= typesToWrite->num )
          goto LABEL_8;
      }
      if ( v17 < 0 )
LABEL_8:
        v19 = 0;
      else
        v19 = &typesToWrite->list[v17];
      if ( v19 && (v16->declState == DS_PARSED || writeStubs) )
      {
        v20 = 0;
        if ( declManagerLocal.linearLists[((int (__thiscall *)(idDeclLocal *, const char *, int, int, int, int, char *))v16->GetType)(
                                            v16,
                                            v68,
                                            v69,
                                            v70,
                                            v71,
                                            v72.len,
                                            v72.data)].num > 0 )
        {
          while ( declManagerLocal.linearLists[v16->GetType(v16)].list[v20] != v16 )
          {
            if ( ++v20 >= declManagerLocal.linearLists[v16->GetType(v16)].num )
              goto LABEL_19;
          }
          sprintf(string, "%d\n", v20);
          v14->Write(v14, string, strlen(string));
        }
LABEL_19:
        decls = 20;
        *(_DWORD *)&v72.baseBuffer[16] = v74;
        v74[0] = 0;
        v21 = 0;
        do
        {
          v22 = *(&entityFilter + v21);
          v74[v21++] = v22;
        }
        while ( v22 );
        *(_DWORD *)&v72.baseBuffer[12] = 0;
        v23 = 0;
        for ( i = 0; i < declManagerLocal.declTypes.num; ++i )
        {
          v23 = declManagerLocal.declTypes.list[i];
          if ( v23 && v23->type == v16->GetType(v16) )
            break;
        }
        len = v23->typeName.len;
        v26 = v23->typeName.len + 1;
        if ( v26 > decls )
          idStr::ReAllocate((idStr *)&v72.baseBuffer[12], v26, 0);
        qmemcpy(*(void **)&v72.baseBuffer[16], v23->typeName.data, len);
        *(_BYTE *)(*(_DWORD *)&v72.baseBuffer[16] + len) = 0;
        *(_DWORD *)&v72.baseBuffer[12] = len;
        if ( v26 + 1 > decls )
          idStr::ReAllocate((idStr *)&v72.baseBuffer[12], v26 + 1, 1);
        v27 = 0;
        v28 = 32;
        do
        {
          v29 = v27 + *(_DWORD *)&v72.baseBuffer[16];
          ++v27;
          *(_BYTE *)(v29 + *(_DWORD *)&v72.baseBuffer[12]) = v28;
          v28 = src[v27];
        }
        while ( v28 );
        *(_DWORD *)&v72.baseBuffer[12] = v26;
        *(_BYTE *)(*(_DWORD *)&v72.baseBuffer[16] + v26) = 0;
        v30 = (const char *)(*((int (__thiscall **)(char **))*v75 + 1))(v75);
        v31 = v30;
        if ( v30 )
        {
          v32 = strlen(v30) + *(_DWORD *)&v72.baseBuffer[12];
          if ( (int)(v32 + 1) > decls )
            idStr::ReAllocate((idStr *)&v72.baseBuffer[12], v32 + 1, 1);
          v33 = *v31;
          for ( j = 0; v33; v33 = v31[j] )
          {
            v35 = j + *(_DWORD *)&v72.baseBuffer[16];
            ++j;
            *(_BYTE *)(v35 + *(_DWORD *)&v72.baseBuffer[12]) = v33;
          }
          *(_DWORD *)&v72.baseBuffer[12] = v32;
          *(_BYTE *)(*(_DWORD *)&v72.baseBuffer[16] + v32) = 0;
        }
        v36 = *(_DWORD *)&v72.baseBuffer[12] + 1;
        if ( *(_DWORD *)&v72.baseBuffer[12] + 2 > decls )
          idStr::ReAllocate((idStr *)&v72.baseBuffer[12], *(_DWORD *)&v72.baseBuffer[12] + 2, 1);
        v37 = 0;
        v38 = 10;
        do
        {
          v39 = v37 + *(_DWORD *)&v72.baseBuffer[16];
          ++v37;
          *(_BYTE *)(v39 + *(_DWORD *)&v72.baseBuffer[12]) = v38;
          v38 = pMsg[v37];
        }
        while ( v38 );
        v40 = v75;
        *(_DWORD *)&v72.baseBuffer[12] = v36;
        *(_BYTE *)(*(_DWORD *)&v72.baseBuffer[16] + v36) = 0;
        if ( v40[19] == (char *)2 )
        {
          (*((void (__thiscall **)(char **, char *))*v40 + 12))(v40, v83);
          for ( k = 0; k < (*((int (__thiscall **)(char **))*v40 + 13))(v40); ++k )
          {
            v42 = v83[k];
            if ( *(_DWORD *)&v72.baseBuffer[12] + 2 > decls )
              idStr::ReAllocate((idStr *)&v72.baseBuffer[12], *(_DWORD *)&v72.baseBuffer[12] + 2, 1);
            *(_BYTE *)(*(_DWORD *)&v72.baseBuffer[16] + (*(_DWORD *)&v72.baseBuffer[12])++) = v42;
            *(_BYTE *)(*(_DWORD *)&v72.baseBuffer[16] + *(_DWORD *)&v72.baseBuffer[12]) = 0;
          }
        }
        else
        {
          v43 = *(_DWORD *)&v72.baseBuffer[12] + 9;
          if ( *(_DWORD *)&v72.baseBuffer[12] + 10 > decls )
            idStr::ReAllocate((idStr *)&v72.baseBuffer[12], *(_DWORD *)&v72.baseBuffer[12] + 10, 1);
          v44 = 0;
          v45 = 10;
          do
          {
            v46 = v44 + *(_DWORD *)&v72.baseBuffer[16];
            ++v44;
            *(_BYTE *)(v46 + *(_DWORD *)&v72.baseBuffer[12]) = v45;
            v45 = aStub_1[v44];
          }
          while ( v45 );
          *(_DWORD *)&v72.baseBuffer[12] = v43;
          *(_BYTE *)(*(_DWORD *)&v72.baseBuffer[16] + v43) = 0;
          v72.data = v75[14];
          a.len = 0;
          a.alloced = 20;
          a.data = a.baseBuffer;
          a.baseBuffer[0] = 0;
          v47 = sprintf(v82, "%d", v72.data);
          if ( v47 + 1 > a.alloced )
            idStr::ReAllocate(&a, v47 + 1, 1);
          data = a.data;
          v49 = v82;
          do
          {
            v50 = *v49;
            *data++ = *v49++;
          }
          while ( v50 );
          a.len = v47;
          v51 = operator+(&result, &a, " ");
          v52 = *(_DWORD *)&v72.baseBuffer[12] + v51->len;
          if ( v52 + 1 > decls )
            idStr::ReAllocate((idStr *)&v72.baseBuffer[12], v52 + 1, 1);
          for ( m = 0; m < v51->len; *(_BYTE *)(v55 + *(_DWORD *)&v72.baseBuffer[12]) = v54 )
          {
            v54 = v51->data[m];
            v55 = m + *(_DWORD *)&v72.baseBuffer[16];
            ++m;
          }
          *(_DWORD *)&v72.baseBuffer[12] = v52;
          *(_BYTE *)(*(_DWORD *)&v72.baseBuffer[16] + v52) = 0;
          idStr::FreeData(&result);
          idStr::FreeData(&a);
          v72.data = v75[15];
          v77.len = 0;
          v77.alloced = 20;
          v77.data = v77.baseBuffer;
          v77.baseBuffer[0] = 0;
          v56 = sprintf(v81, "%d", v72.data);
          if ( v56 + 1 > v77.alloced )
            idStr::ReAllocate(&v77, v56 + 1, 1);
          v57 = v77.data;
          v58 = v81;
          do
          {
            v59 = *v58;
            *v57++ = *v58++;
          }
          while ( v59 );
          v77.len = v56;
          v60 = operator+(&v80, &v77, " }");
          v61 = v60->len + *(_DWORD *)&v72.baseBuffer[12];
          if ( v61 + 1 > decls )
            idStr::ReAllocate((idStr *)&v72.baseBuffer[12], v61 + 1, 1);
          for ( n = 0; n < v60->len; *(_BYTE *)(v64 + *(_DWORD *)&v72.baseBuffer[12]) = v63 )
          {
            v63 = v60->data[n];
            v64 = n + *(_DWORD *)&v72.baseBuffer[16];
            ++n;
          }
          *(_DWORD *)&v72.baseBuffer[12] = v61;
          *(_BYTE *)(*(_DWORD *)&v72.baseBuffer[16] + v61) = 0;
          idStr::FreeData(&v80);
          idStr::FreeData(&v77);
        }
        v65 = *(_DWORD *)&v72.baseBuffer[12];
        sprintf(string, "%d\n", *(_DWORD *)&v72.baseBuffer[12] + 1);
        v67 = a12->__vftable;
        v72.data = (char *)strlen(string);
        v72.len = (int)string;
        ((void (__thiscall *)(idFile *))v67->Write)(a12);
        v71 = v65;
        v70 = *(_DWORD *)&v72.baseBuffer[8];
        ((void (__thiscall *)(idFile *))a12->Write)(a12);
        v69 = 1;
        v68 = "\n";
        ((void (__thiscall *)(idFile *))a12->Write)(a12);
        v86 = -1;
        idStr::FreeData(&v72);
        v16 = (idDeclLocal *)decls;
        v14 = a12;
      }
      v16 = v16->nextInFile;
      decls = (int)v16;
    }
    while ( v16 );
  }
}

// FUNC: public: class idDeclLocal * __thiscall idDeclManagerLocal::FindTypeWithoutParsing(enum declType_t,char const *,bool,int)
idDeclLocal *__thiscall idDeclManagerLocal::FindTypeWithoutParsing(
        idDeclManagerLocal *this,
        int type,
        const char *name,
        bool makeDefault,
        int indexToStoreAt)
{
  idHashIndex *v6; // ebp
  unsigned __int8 v7; // cl
  int v8; // esi
  char *j; // eax
  int v10; // edx
  int v11; // esi
  idDeclLocal ***p_list; // edi
  idDeclLocal *v14; // eax
  int v15; // eax
  int v16; // ebp
  declType_t v17; // esi
  idList<idDeclLocal *> *v18; // esi
  int granularity; // eax
  bool v20; // cc
  int jj; // eax
  int size; // ecx
  int v23; // ecx
  idDeclLocal **list; // edi
  int kk; // eax
  idHashIndex *v26; // ecx
  int v27; // esi
  int v28; // ecx
  int v29; // eax
  char *v30; // esi
  int v31; // eax
  void (__thiscall ***v32)(_DWORD, int); // ecx
  int v33; // eax
  int v34; // eax
  idDeclLocal *v35; // eax
  int v36; // eax
  int v37; // edi
  bool v38; // zf
  int v39; // eax
  int k; // eax
  int v41; // eax
  int v42; // ecx
  _DWORD *v43; // ebp
  int m; // eax
  int v45; // eax
  int n; // eax
  int v47; // ebp
  int v48; // eax
  int v49; // ecx
  _DWORD *v50; // edi
  int ii; // eax
  int indexSize; // eax
  int v53; // eax
  idHashIndex *v54; // [esp+10h] [ebp-424h]
  int v56; // [esp+18h] [ebp-41Ch]
  int hash; // [esp+1Ch] [ebp-418h]
  int i; // [esp+20h] [ebp-414h]
  char canonicalName[1024]; // [esp+28h] [ebp-40Ch] BYREF
  int v60; // [esp+430h] [ebp-4h]

  if ( type < 0 || type >= this->declTypes.num || !this->declTypes.list[type] )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idDeclManager::FindTypeWithoutParsing: bad type: %i",
      type);
  idDeclManagerLocal::MakeNameCanonical(name, canonicalName, 1024);
  v6 = &this->hashTables[type];
  v7 = canonicalName[0];
  v8 = 0;
  v54 = v6;
  for ( j = canonicalName; v7; v8 += v10 )
  {
    if ( idStr::lowerCaseCharacter[v7] )
      v7 = idStr::lowerCaseCharacter[v7];
    v10 = (char)v7 * (_DWORD)&j[119 - (_DWORD)canonicalName];
    v7 = *++j;
  }
  hash = v8 & v6->hashMask;
  v11 = v6->hash[hash & v6->hashMask & v6->lookupMask];
  if ( v11 < 0 )
  {
LABEL_13:
    if ( !makeDefault )
      return 0;
    v14 = (idDeclLocal *)Memory::Allocate(0x60u);
    v60 = 0;
    if ( v14 )
    {
      idDeclLocal::idDeclLocal(v14);
      v16 = v15;
    }
    else
    {
      v16 = 0;
    }
    v56 = v16;
    v60 = -1;
    *(_DWORD *)(v16 + 4) = 0;
    idStr::operator=((idStr *)(v16 + 8), canonicalName);
    *(_DWORD *)(v16 + 72) = type;
    *(_DWORD *)(v16 + 76) = 0;
    *(_DWORD *)(v16 + 40) = 0;
    *(_DWORD *)(v16 + 44) = 0;
    *(_DWORD *)(v16 + 52) = &this->implicitDecls;
    *(_BYTE *)(v16 + 86) = 0;
    *(_BYTE *)(v16 + 85) = 0;
    v17 = type;
    *(_BYTE *)(v16 + 84) = !this->insideLevelLoad;
    if ( indexToStoreAt != -1 )
    {
      v30 = (char *)this + v17 * 16;
      v31 = *((_DWORD *)v30 + 238);
      if ( indexToStoreAt >= v31 )
      {
        i = *((_DWORD *)v30 + 238);
        if ( v31 < indexToStoreAt )
        {
          do
          {
            v35 = (idDeclLocal *)Memory::Allocate(0x60u);
            v60 = 1;
            if ( v35 )
            {
              idDeclLocal::idDeclLocal(v35);
              v37 = v36;
            }
            else
            {
              v37 = 0;
            }
            v60 = -1;
            *(_DWORD *)(v37 + 4) = 0;
            idStr::operator=((idStr *)(v37 + 8), (char *)&entityFilter);
            *(_DWORD *)(v37 + 72) = type;
            *(_DWORD *)(v37 + 76) = 0;
            *(_DWORD *)(v37 + 40) = 0;
            *(_DWORD *)(v37 + 44) = 0;
            *(_DWORD *)(v37 + 52) = &this->implicitDecls;
            *(_BYTE *)(v37 + 86) = 0;
            *(_BYTE *)(v37 + 85) = 0;
            v38 = !this->insideLevelLoad;
            *(_DWORD *)(v37 + 80) = i;
            *(_BYTE *)(v37 + 84) = v38;
            *(_BYTE *)(v37 + 87) = 0;
            if ( !*((_DWORD *)v30 + 241) )
            {
              v39 = *((_DWORD *)v30 + 240);
              if ( v39 > 0 )
              {
                if ( v39 != *((_DWORD *)v30 + 239) )
                {
                  v20 = v39 < *((_DWORD *)v30 + 238);
                  *((_DWORD *)v30 + 239) = v39;
                  if ( v20 )
                    *((_DWORD *)v30 + 238) = v39;
                  *((_DWORD *)v30 + 241) = Memory::Allocate(4 * v39);
                  for ( k = 0; k < *((_DWORD *)v30 + 238); ++k )
                    *(_DWORD *)(*((_DWORD *)v30 + 241) + 4 * k) = *(_DWORD *)(4 * k);
                }
              }
              else
              {
                *((_DWORD *)v30 + 241) = 0;
                *((_DWORD *)v30 + 238) = 0;
                *((_DWORD *)v30 + 239) = 0;
              }
            }
            v41 = *((_DWORD *)v30 + 239);
            if ( *((_DWORD *)v30 + 238) == v41 )
            {
              if ( !*((_DWORD *)v30 + 240) )
                *((_DWORD *)v30 + 240) = 16;
              v42 = v41 + *((_DWORD *)v30 + 240) - (v41 + *((_DWORD *)v30 + 240)) % *((_DWORD *)v30 + 240);
              if ( v42 > 0 )
              {
                if ( v42 != *((_DWORD *)v30 + 239) )
                {
                  v20 = v42 < *((_DWORD *)v30 + 238);
                  v43 = (_DWORD *)*((_DWORD *)v30 + 241);
                  *((_DWORD *)v30 + 239) = v42;
                  if ( v20 )
                    *((_DWORD *)v30 + 238) = v42;
                  *((_DWORD *)v30 + 241) = Memory::Allocate(4 * v42);
                  for ( m = 0; m < *((_DWORD *)v30 + 238); ++m )
                    *(_DWORD *)(*((_DWORD *)v30 + 241) + 4 * m) = v43[m];
                  if ( v43 )
                    Memory::Free(v43);
                }
              }
              else
              {
                if ( *((_DWORD *)v30 + 241) )
                  Memory::Free(*((void **)v30 + 241));
                *((_DWORD *)v30 + 241) = 0;
                *((_DWORD *)v30 + 238) = 0;
                *((_DWORD *)v30 + 239) = 0;
              }
            }
            *(_DWORD *)(*((_DWORD *)v30 + 241) + 4 * (*((_DWORD *)v30 + 238))++) = v37;
            ++i;
          }
          while ( i < indexToStoreAt );
        }
        if ( !*((_DWORD *)v30 + 241) )
        {
          v45 = *((_DWORD *)v30 + 240);
          if ( v45 > 0 )
          {
            if ( v45 != *((_DWORD *)v30 + 239) )
            {
              v20 = v45 < *((_DWORD *)v30 + 238);
              *((_DWORD *)v30 + 239) = v45;
              if ( v20 )
                *((_DWORD *)v30 + 238) = v45;
              *((_DWORD *)v30 + 241) = Memory::Allocate(4 * v45);
              for ( n = 0; n < *((_DWORD *)v30 + 238); ++n )
                *(_DWORD *)(*((_DWORD *)v30 + 241) + 4 * n) = *(_DWORD *)(4 * n);
            }
          }
          else
          {
            *((_DWORD *)v30 + 241) = 0;
            *((_DWORD *)v30 + 238) = 0;
            *((_DWORD *)v30 + 239) = 0;
          }
        }
        v47 = *((_DWORD *)v30 + 238);
        v48 = *((_DWORD *)v30 + 239);
        if ( v47 == v48 )
        {
          if ( !*((_DWORD *)v30 + 240) )
            *((_DWORD *)v30 + 240) = 16;
          v49 = v48 + *((_DWORD *)v30 + 240) - (v48 + *((_DWORD *)v30 + 240)) % *((_DWORD *)v30 + 240);
          if ( v49 > 0 )
          {
            if ( v49 != *((_DWORD *)v30 + 239) )
            {
              v50 = (_DWORD *)*((_DWORD *)v30 + 241);
              *((_DWORD *)v30 + 239) = v49;
              if ( v49 < v47 )
                *((_DWORD *)v30 + 238) = v49;
              *((_DWORD *)v30 + 241) = Memory::Allocate(4 * v49);
              for ( ii = 0; ii < *((_DWORD *)v30 + 238); ++ii )
                *(_DWORD *)(*((_DWORD *)v30 + 241) + 4 * ii) = v50[ii];
              if ( v50 )
                Memory::Free(v50);
            }
          }
          else
          {
            if ( *((_DWORD *)v30 + 241) )
              Memory::Free(*((void **)v30 + 241));
            *((_DWORD *)v30 + 241) = 0;
            *((_DWORD *)v30 + 238) = 0;
            *((_DWORD *)v30 + 239) = 0;
          }
        }
        *(_DWORD *)(*((_DWORD *)v30 + 241) + 4 * (*((_DWORD *)v30 + 238))++) = v56;
        *(_DWORD *)(v56 + 80) = indexToStoreAt;
        if ( v54->hash == idHashIndex::INVALID_INDEX )
        {
          indexSize = v54->indexSize;
          if ( indexToStoreAt >= indexSize )
            indexSize = indexToStoreAt + 1;
          idHashIndex::Allocate(v54, v54->hashSize, indexSize);
        }
        else if ( indexToStoreAt >= v54->indexSize )
        {
          idHashIndex::ResizeIndex(v54, indexToStoreAt + 1);
        }
        v53 = hash & v54->hashMask;
        v16 = v56;
        v54->indexChain[indexToStoreAt] = v54->hash[v53];
        v54->hash[v53] = indexToStoreAt;
      }
      else
      {
        v32 = *(void (__thiscall ****)(_DWORD, int))(*((_DWORD *)v30 + 241) + 4 * indexToStoreAt);
        if ( v32 )
          (**v32)(v32, 1);
        *(_DWORD *)(*((_DWORD *)v30 + 241) + 4 * indexToStoreAt) = v16;
        *(_DWORD *)(v16 + 80) = indexToStoreAt;
        if ( v54->hash == idHashIndex::INVALID_INDEX )
        {
          v33 = v54->indexSize;
          if ( indexToStoreAt >= v33 )
            v33 = indexToStoreAt + 1;
          idHashIndex::Allocate(v54, v54->hashSize, v33);
        }
        else if ( indexToStoreAt >= v54->indexSize )
        {
          idHashIndex::ResizeIndex(v54, indexToStoreAt + 1);
        }
        v34 = hash & v54->hashMask;
        v54->indexChain[indexToStoreAt] = v54->hash[v34];
        v54->hash[v34] = indexToStoreAt;
      }
      return (idDeclLocal *)v16;
    }
    v18 = &this->linearLists[v17];
    *(_DWORD *)(v16 + 80) = v18->num;
    if ( !v18->list )
    {
      granularity = v18->granularity;
      if ( granularity > 0 )
      {
        if ( granularity != v18->size )
        {
          v20 = granularity < v18->num;
          v18->size = granularity;
          if ( v20 )
            v18->num = granularity;
          v18->list = (idDeclLocal **)Memory::Allocate(4 * granularity);
          for ( jj = 0; jj < v18->num; ++jj )
            v18->list[jj] = *(idDeclLocal **)(4 * jj);
        }
      }
      else
      {
        v18->list = 0;
        v18->num = 0;
        v18->size = 0;
      }
    }
    size = v18->size;
    if ( v18->num == size )
    {
      if ( !v18->granularity )
        v18->granularity = 16;
      v23 = v18->granularity + size - (v18->granularity + size) % v18->granularity;
      if ( v23 > 0 )
      {
        if ( v23 != v18->size )
        {
          v20 = v23 < v18->num;
          list = v18->list;
          v18->size = v23;
          if ( v20 )
            v18->num = v23;
          v18->list = (idDeclLocal **)Memory::Allocate(4 * v23);
          for ( kk = 0; kk < v18->num; ++kk )
            v18->list[kk] = list[kk];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( v18->list )
          Memory::Free(v18->list);
        v18->list = 0;
        v18->num = 0;
        v18->size = 0;
      }
    }
    v18->list[v18->num++] = (idDeclLocal *)v16;
    v26 = v54;
    v27 = v18->num - 1;
    if ( v54->hash == idHashIndex::INVALID_INDEX )
    {
      v28 = v54->indexSize;
      if ( v27 >= v28 )
        v28 = v27 + 1;
      idHashIndex::Allocate(v54, v54->hashSize, v28);
    }
    else
    {
      if ( v27 < v54->indexSize )
      {
LABEL_51:
        v29 = hash & v26->hashMask;
        v26->indexChain[v27] = v26->hash[v29];
        v26->hash[v29] = v27;
        return (idDeclLocal *)v16;
      }
      idHashIndex::ResizeIndex(v54, v27 + 1);
    }
    v26 = v54;
    goto LABEL_51;
  }
  p_list = &this->linearLists[type].list;
  while ( idStr::Icmp((*p_list)[v11]->name.data, canonicalName) )
  {
    v11 = v6->indexChain[v11 & v6->lookupMask];
    if ( v11 < 0 )
      goto LABEL_13;
  }
  if ( idDeclManagerLocal::decl_show.internalVar->integerValue > 1 )
    this->MediaPrint(this, "referencing %s %s\n", this->declTypes.list[type]->typeName.data, name);
  return (*p_list)[v11];
}

// FUNC: public: virtual void __thiscall idDeclLocal::EnsureNotPurged(void)
void __thiscall idDeclLocal::EnsureNotPurged(idDeclLocal *this)
{
  if ( this->declState == DS_UNPARSED )
    idDeclLocal::ParseLocal(this, 0);
}

// FUNC: public: virtual void __thiscall idDeclLocal::SetText(char const *)
void __thiscall idDeclLocal::SetText(idDeclLocal *this, const char *text)
{
  int v2; // eax

  v2 = 0;
  if ( *text )
  {
    do
      ++v2;
    while ( text[v2] );
  }
  idDeclLocal::SetTextLocal(this, text, v2);
}

// FUNC: public: virtual void __thiscall idDeclLocal::MakeDefault(void)
void __thiscall idDeclLocal::MakeDefault(idDeclLocal *this)
{
  bool v2; // zf
  idDecl *v3; // eax
  const char *v4; // edi

  idDeclManagerLocal::MediaPrint(&declManagerLocal, "DEFAULTED\n");
  v2 = this->self == 0;
  this->declState = DS_DEFAULTED;
  if ( v2 )
  {
    v3 = declManagerLocal.declTypes.list[this->type]->allocator();
    this->self = v3;
    v3->base = this;
  }
  v4 = this->self->DefaultDefinition(this->self);
  if ( ++recursionLevel > 100 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "idDecl::MakeDefault: bad DefaultDefinition(): %s",
      v4);
  this->self->FreeData(this->self);
  this->self->Parse(this->self, v4, strlen(v4), 0);
  --recursionLevel;
}

// FUNC: public: virtual class idStr __thiscall idDeclManagerLocal::GetNewName(enum declType_t,char const *)
idStr *__thiscall idDeclManagerLocal::GetNewName(
        idDeclManagerLocal *this,
        idStr *result,
        declType_t type,
        const char *base)
{
  idDeclManager_vtbl *v4; // edx
  int v5; // esi
  char *v6; // eax
  idStr *v7; // esi
  char *data; // edx
  const char *v9; // ecx
  char v10; // al
  int len; // edi
  char *v13; // ecx
  char *v14; // edx
  char v15; // al
  idStr name; // [esp+18h] [ebp-2Ch] BYREF
  int v17; // [esp+40h] [ebp-4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v4 = declManager->__vftable;
  v5 = 1;
  v17 = 1;
  v4->GetNumDecls(declManager, type);
  while ( 1 )
  {
    v6 = va("%s%d", base, v5);
    idStr::operator=(&name, v6);
    if ( !declManager->FindType(declManager, type, name.data, 0, 0) )
      break;
    if ( ++v5 >= 1024 )
    {
      v7 = result;
      result->alloced = 20;
      result->len = 0;
      result->data = result->baseBuffer;
      result->baseBuffer[0] = 0;
      if ( result->alloced < 10 )
        idStr::ReAllocate(result, 10, 1);
      data = result->data;
      v9 = "*unknown*";
      do
      {
        v10 = *v9;
        *data++ = *v9++;
      }
      while ( v10 );
      result->len = 9;
      goto LABEL_9;
    }
  }
  v7 = result;
  result->data = result->baseBuffer;
  result->alloced = 20;
  result->len = 0;
  result->baseBuffer[0] = 0;
  len = name.len;
  if ( name.len + 1 > result->alloced )
    idStr::ReAllocate(result, name.len + 1, 1);
  v13 = name.data;
  v14 = result->data;
  do
  {
    v15 = *v13;
    *v14++ = *v13++;
  }
  while ( v15 );
  result->len = len;
LABEL_9:
  LOBYTE(v17) = 0;
  idStr::FreeData(&name);
  return v7;
}

// FUNC: public: void __thiscall rvDeclGuide::RemoveOuterBracing(void)
void __thiscall rvDeclGuide::RemoveOuterBracing(rvDeclGuide *this)
{
  idStr *p_mDefinition; // ebx
  int v2; // eax
  idStr *v3; // esi
  unsigned int len; // ebp
  int v5; // eax
  bool v6; // cc
  int Char; // eax
  idStr *v8; // esi
  unsigned int v9; // ebp
  int v10; // eax
  idStr result; // [esp+10h] [ebp-4Ch] BYREF
  idStr v12; // [esp+30h] [ebp-2Ch] BYREF
  int v13; // [esp+58h] [ebp-4h]

  p_mDefinition = &this->mDefinition;
  v2 = idStr::Last(&this->mDefinition, 125);
  v3 = idStr::Left(p_mDefinition, &result, v2 - 1);
  len = v3->len;
  v5 = v3->len + 1;
  v6 = v5 <= p_mDefinition->alloced;
  v13 = 0;
  if ( !v6 )
    idStr::ReAllocate(p_mDefinition, v5, 0);
  qmemcpy(p_mDefinition->data, v3->data, len);
  p_mDefinition->data[len] = 0;
  p_mDefinition->len = len;
  v13 = -1;
  idStr::FreeData(&result);
  Char = idStr::FindChar(p_mDefinition->data, 123, 0, p_mDefinition->len);
  v8 = idStr::Right(p_mDefinition, &v12, p_mDefinition->len - Char - 1);
  v9 = v8->len;
  v10 = v8->len + 1;
  v6 = v10 <= p_mDefinition->alloced;
  v13 = 1;
  if ( !v6 )
    idStr::ReAllocate(p_mDefinition, v10, 0);
  qmemcpy(p_mDefinition->data, v8->data, v9);
  p_mDefinition->data[v9] = 0;
  p_mDefinition->len = v9;
  v13 = -1;
  idStr::FreeData(&v12);
}

// FUNC: public: bool __thiscall rvDeclGuide::Evaluate(class idLexer *,class idStr &)
char __thiscall rvDeclGuide::Evaluate(rvDeclGuide *this, idLexer *src, idStr *definition)
{
  rvDeclGuide *v3; // ebx
  int v4; // esi
  char *v5; // ebp
  int len; // ebx
  size_t v8; // esi
  bool v9; // cc
  char *v10; // esi
  char *v11; // ebp
  const char **p_data; // ebx
  char *i; // edi
  const char *v14; // ecx
  char *v15; // edx
  char v16; // al
  char *v17; // eax
  int v18; // ebp
  char v19; // cl
  int v20; // [esp+4h] [ebp-A2FCh]
  const char **v21; // [esp+4h] [ebp-A2FCh]
  int v23; // [esp+Ch] [ebp-A2F4h]
  const char **v24; // [esp+10h] [ebp-A2F0h]
  char *v25; // [esp+14h] [ebp-A2ECh]
  char *v26; // [esp+18h] [ebp-A2E8h]
  unsigned int v27; // [esp+1Ch] [ebp-A2E4h]
  int v28; // [esp+20h] [ebp-A2E0h]
  idToken token; // [esp+24h] [ebp-A2DCh] BYREF
  char ptr[4]; // [esp+74h] [ebp-A28Ch] BYREF
  char v31[636]; // [esp+78h] [ebp-A288h] BYREF
  char Destination[20480]; // [esp+2F4h] [ebp-A00Ch] BYREF
  char v33[20480]; // [esp+52F4h] [ebp-500Ch] BYREF
  int v34; // [esp+A2FCh] [ebp-4h]

  token.floatvalue = 0.0;
  v3 = this;
  v4 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v34 = 0;
  v20 = 0;
  `eh vector constructor iterator'(
    ptr,
    0x20u,
    20,
    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  LOBYTE(v34) = 1;
  idLexer::ExpectTokenString(src, "(");
  v5 = v31;
  do
  {
    idLexer::ReadToken(src, &token);
    if ( !idStr::Cmp(token.data, ")") )
      break;
    if ( idStr::Cmp(token.data, ",") )
    {
      len = token.len;
      if ( token.len + 1 > *((_DWORD *)v5 + 1) )
        idStr::ReAllocate((idStr *)(v5 - 4), token.len + 1, 0);
      ++v20;
      qmemcpy(*(void **)v5, token.data, len);
      v4 = v20;
      *(_BYTE *)(len + *(_DWORD *)v5) = 0;
      *((_DWORD *)v5 - 1) = len;
      v3 = this;
      v5 += 32;
    }
  }
  while ( v4 < 20 );
  if ( v4 == v3->mNumParms )
  {
    v8 = v3->mDefinition.len + 1;
    if ( v8 > 0x5000 )
      v8 = 20480;
    strncpy(Destination, v3->mDefinition.data, v8);
    v9 = v3->mNumParms <= 0;
    Destination[v8] = 0;
    v25 = Destination;
    v10 = Destination;
    v26 = v33;
    v11 = v33;
    v23 = 0;
    if ( !v9 )
    {
      p_data = (const char **)&v3->mParms[0].data;
      v21 = (const char **)v31;
      v24 = p_data;
      do
      {
        v28 = (int)*(p_data - 1);
        v27 = strlen(*v21);
        for ( i = strstr(v10, *p_data); i; i = strstr(&i[v28], *p_data) )
        {
          if ( i != Destination )
          {
            strncpy(v11, v10, i - v10);
            v11 += i - v10;
            p_data = v24;
          }
          v14 = *v21;
          v15 = v11;
          do
          {
            v16 = *v14;
            *v15++ = *v14++;
          }
          while ( v16 );
          v11 += v27;
          v10 = &i[v28];
        }
        v17 = v10;
        v18 = v11 - v10;
        do
        {
          v19 = *v17;
          v17[v18] = *v17;
          ++v17;
        }
        while ( v19 );
        v10 = v26;
        v11 = v25;
        v21 += 8;
        p_data += 8;
        v9 = v23 + 1 < this->mNumParms;
        v26 = v25;
        v25 = v10;
        ++v23;
        v24 = p_data;
      }
      while ( v9 );
    }
    idStr::operator=(definition, v10);
    LOBYTE(v34) = 0;
    `eh vector destructor iterator'(
      ptr,
      0x20u,
      20,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    v34 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
    LOBYTE(v34) = 0;
    `eh vector destructor iterator'(
      ptr,
      0x20u,
      20,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    v34 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: __thiscall rvDeclGuide::rvDeclGuide(class idStr &)
void __thiscall rvDeclGuide::rvDeclGuide(rvDeclGuide *this, idStr *name)
{
  int len; // ebx
  int v4; // eax
  char *baseBuffer; // esi
  int v6; // ebx

  this->mName.len = 0;
  this->mName.alloced = 20;
  this->mName.data = this->mName.baseBuffer;
  this->mName.baseBuffer[0] = 0;
  `eh vector constructor iterator'(
    this->mParms,
    0x20u,
    20,
    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
  this->mDefinition.len = 0;
  this->mDefinition.alloced = 20;
  this->mDefinition.data = this->mDefinition.baseBuffer;
  this->mDefinition.baseBuffer[0] = 0;
  len = name->len;
  v4 = name->len + 1;
  if ( v4 > this->mName.alloced )
    idStr::ReAllocate(&this->mName, v4, 0);
  qmemcpy(this->mName.data, name->data, len);
  this->mName.data[len] = 0;
  this->mName.len = len;
  baseBuffer = this->mParms[0].baseBuffer;
  v6 = 20;
  do
  {
    idStr::FreeData((idStr *)(baseBuffer - 12));
    *((_DWORD *)baseBuffer - 1) = 20;
    *((_DWORD *)baseBuffer - 2) = baseBuffer;
    *((_DWORD *)baseBuffer - 3) = 0;
    *baseBuffer = 0;
    baseBuffer += 32;
    --v6;
  }
  while ( v6 );
}

// FUNC: public: int __thiscall idDeclFile::LoadAndParse(bool)
int __thiscall idDeclFile::LoadAndParse(idDeclFile *this, bool unique)
{
  idDeclFile *v2; // ebx
  unsigned int len; // ebp
  int v4; // eax
  int v5; // esi
  idDeclLocal *i; // eax
  int num; // ebp
  int v9; // esi
  idDeclType *v10; // edi
  int type; // ebp
  int v12; // ebx
  int v13; // edi
  bool referencedThisLevel; // bl
  idDeclLocal *TypeWithoutParsing; // eax
  idDeclLocal *v16; // esi
  idDeclFile *sourceFile; // eax
  const char *data; // edi
  char *v19; // ebx
  char *textSource; // eax
  int v21; // eax
  int v22; // ecx
  idDeclLocal *j; // esi
  idDeclFile *v24; // eax
  int checksum; // ebx
  char *v26; // [esp-4h] [ebp-1B0h]
  bool guide; // [esp+13h] [ebp-199h]
  char *buffer; // [esp+18h] [ebp-194h] BYREF
  int startMarker; // [esp+1Ch] [ebp-190h]
  idStr name; // [esp+20h] [ebp-18Ch] BYREF
  int sourceLine; // [esp+40h] [ebp-16Ch]
  int numTypes; // [esp+44h] [ebp-168h]
  idStr stripped; // [esp+48h] [ebp-164h] BYREF
  idStr definition; // [esp+68h] [ebp-144h] BYREF
  idToken token; // [esp+88h] [ebp-124h] BYREF
  idLexer src; // [esp+D8h] [ebp-D4h] BYREF
  int v38; // [esp+1A8h] [ebp-4h]

  v2 = this;
  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v38 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  definition.len = 0;
  definition.alloced = 20;
  definition.data = definition.baseBuffer;
  definition.baseBuffer[0] = 0;
  stripped.len = 0;
  stripped.alloced = 20;
  stripped.data = stripped.baseBuffer;
  stripped.baseBuffer[0] = 0;
  len = v2->fileName.len;
  v4 = v2->fileName.len + 1;
  LOBYTE(v38) = 4;
  if ( v4 > 20 )
    idStr::ReAllocate(&stripped, v4, 0);
  qmemcpy(stripped.data, v2->fileName.data, len);
  stripped.data[len] = 0;
  stripped.len = len;
  idStr::StripFileExtension(&stripped);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "...loading '%s'\n",
    v2->fileName.data);
  v5 = fileSystem->ReadFile(fileSystem, v2->fileName.data, (void **)&buffer, &v2->timestamp);
  if ( v5 == -1 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "couldn't load %s",
      v2->fileName.data);
LABEL_7:
    LOBYTE(v38) = 3;
    idStr::FreeData(&stripped);
    LOBYTE(v38) = 2;
    idStr::FreeData(&definition);
    LOBYTE(v38) = 1;
    idStr::FreeData(&name);
    LOBYTE(v38) = 0;
    idStr::FreeData(&token);
    v38 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
  if ( !idLexer::LoadMemory(&src, buffer, v5, v2->fileName.data, 1) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Couldn't parse %s",
      v2->fileName.data);
    Mem_Free(buffer);
    goto LABEL_7;
  }
  for ( i = v2->decls; i; i = i->nextInFile )
    i->redefinedInReload = 0;
  src.flags = 6300;
  v2->checksum = MD5_BlockChecksum(buffer, v5);
  v2->fileSize = v5;
  while ( 1 )
  {
    sourceLine = src.line;
    startMarker = src.script_p - src.buffer;
    if ( !idLexer::ReadToken(&src, &token) )
      break;
    guide = 0;
    if ( !idStr::Icmp(token.data, "guide") )
    {
      guide = 1;
      idLexer::ReadToken(&src, &token);
    }
    num = declManagerLocal.declTypes.num;
    v9 = 0;
    numTypes = declManagerLocal.declTypes.num;
    if ( declManagerLocal.declTypes.num > 0 )
    {
      while ( 1 )
      {
        v10 = declManagerLocal.declTypes.list[v9];
        if ( v10 )
        {
          if ( !idStr::Icmp(v10->typeName.data, token.data) )
            break;
        }
        if ( ++v9 >= num )
          goto LABEL_21;
      }
      type = v10->type;
      if ( v9 < numTypes )
        goto LABEL_25;
    }
LABEL_21:
    if ( !idStr::Icmp(token.data, "{") )
      goto LABEL_27;
    if ( v2->defaultType == DECL_MAX_TYPES )
    {
      idLexer::Warning(&src, "No type");
    }
    else
    {
      idLexer::UnreadToken(&src, &token);
      type = v2->defaultType;
LABEL_25:
      if ( !idLexer::ReadToken(&src, &token) )
      {
        idLexer::Warning(&src, "Type without definition at end of file");
        break;
      }
      if ( idStr::Icmp(token.data, "{") )
      {
        if ( type == 16 )
        {
          idLexer::SkipBracedSection(&src, 1);
        }
        else
        {
          v12 = token.len;
          if ( token.len + 1 > name.alloced )
            idStr::ReAllocate(&name, token.len + 1, 0);
          qmemcpy(name.data, token.data, v12);
          name.data[v12] = 0;
          name.len = v12;
          if ( unique && idStr::Cmp(stripped.data, name.data) )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
              common.type,
              "%s must be in a file of the same name!",
              name.data);
          if ( guide )
            declManager->EvaluateGuide(declManager, &name, &src, &definition);
          else
            idLexer::ParseBracedSectionExact(&src, &definition, -1);
          declManager->EvaluateInlineGuide(declManager, &name, &definition);
          v13 = src.script_p - src.buffer - startMarker;
          referencedThisLevel = 0;
          TypeWithoutParsing = idDeclManagerLocal::FindTypeWithoutParsing(&declManagerLocal, type, name.data, 0, -1);
          v16 = TypeWithoutParsing;
          if ( !TypeWithoutParsing )
          {
            v16 = idDeclManagerLocal::FindTypeWithoutParsing(&declManagerLocal, type, name.data, 1, -1);
            v16->nextInFile = this->decls;
            this->decls = v16;
            goto LABEL_48;
          }
          sourceFile = TypeWithoutParsing->sourceFile;
          if ( sourceFile == this && !v16->redefinedInReload )
          {
            referencedThisLevel = v16->referencedThisLevel;
LABEL_48:
            textSource = v16->textSource;
            v16->redefinedInReload = 1;
            if ( textSource )
            {
              Mem_Free(textSource);
              v16->textSource = 0;
            }
            idDeclLocal::SetTextLocal(v16, definition.data, definition.len);
            v21 = startMarker;
            v22 = sourceLine;
            v16->sourceFile = this;
            v16->sourceTextOffset = v21;
            v16->sourceTextLength = v13;
            v16->sourceLine = v22;
            v16->declState = DS_UNPARSED;
            if ( referencedThisLevel || image_writeProgramImages.internalVar->integerValue )
              idDeclLocal::ParseLocal(v16, 0);
            goto LABEL_11;
          }
          data = sourceFile->fileName.data;
          v19 = name.data;
          if ( type < 0 || type >= declManagerLocal.declTypes.num || !declManagerLocal.declTypes.list[type] )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
              common.type,
              "idDeclManager::GetDeclNameFromType: bad type: %i",
              type);
          idLexer::Warning(
            &src,
            "%s '%s' previously defined at %s:%i",
            declManagerLocal.declTypes.list[type]->typeName.data,
            v19,
            data,
            v16->sourceLine);
LABEL_11:
          v2 = this;
        }
      }
      else
      {
LABEL_27:
        idLexer::Warning(&src, "Missing decl name");
        idLexer::SkipBracedSection(&src, 0);
      }
    }
  }
  v26 = buffer;
  v2->numLines = src.line;
  Mem_Free(v26);
  for ( j = v2->decls; j; j = j->nextInFile )
  {
    if ( !j->redefinedInReload )
    {
      j->MakeDefault(j);
      v24 = j->sourceFile;
      j->sourceTextOffset = v24->fileSize;
      j->sourceTextLength = 0;
      j->sourceLine = v24->numLines;
    }
  }
  checksum = v2->checksum;
  LOBYTE(v38) = 3;
  idStr::FreeData(&stripped);
  LOBYTE(v38) = 2;
  idStr::FreeData(&definition);
  LOBYTE(v38) = 1;
  idStr::FreeData(&name);
  LOBYTE(v38) = 0;
  idStr::FreeData(&token);
  v38 = -1;
  idLexer::~idLexer(&src);
  return checksum;
}

// FUNC: void __cdecl CheckDecls_f(class idCmdArgs const &)
void __cdecl CheckDecls_f()
{
  idDeclManagerLocal::CheckDecls(&declManagerLocal);
}

// FUNC: public: void __thiscall idDeclManagerLocal::RegisterDeclFolder(char const *,char const *,enum declType_t,bool,bool)
void __thiscall idDeclManagerLocal::RegisterDeclFolder(
        idDeclManagerLocal *this,
        char *folder,
        char *extension,
        declType_t defaultType,
        bool unique,
        bool norecurse)
{
  int v6; // esi
  int num; // eax
  _DWORD *v9; // eax
  idDeclFolder *v10; // esi
  int granularity; // eax
  bool v12; // cc
  int j; // eax
  int v14; // ebx
  int size; // eax
  int v16; // ecx
  idDeclFolder **list; // edi
  int k; // eax
  const idStr *v19; // eax
  idStr *v20; // esi
  unsigned int len; // ebx
  int v22; // eax
  int m; // esi
  idDeclFile *v24; // ecx
  idDeclFile *v25; // esi
  char *v26; // ecx
  bool v27; // zf
  int v28; // eax
  int n; // eax
  int v30; // esi
  int v31; // eax
  int v32; // ecx
  idDeclFile **v33; // edi
  int ii; // eax
  const char *v35; // edi
  idFileList *v36; // ebx
  int v37; // esi
  int v38; // edi
  char *v39; // ecx
  char *v40; // edx
  char v41; // al
  const idStr *v42; // eax
  char *v43; // [esp+8h] [ebp-C8h]
  const char *data; // [esp+Ch] [ebp-C4h]
  idFileList *fileList; // [esp+2Ch] [ebp-A4h]
  idFileList *fileLista; // [esp+2Ch] [ebp-A4h]
  int i; // [esp+30h] [ebp-A0h]
  int ia; // [esp+30h] [ebp-A0h]
  idDeclFolder *declFolder; // [esp+34h] [ebp-9Ch]
  int v50; // [esp+38h] [ebp-98h]
  idDeclFile *v51; // [esp+3Ch] [ebp-94h]
  idDeclFile *v52; // [esp+40h] [ebp-90h]
  idStr fileName; // [esp+44h] [ebp-8Ch] BYREF
  idStr a; // [esp+64h] [ebp-6Ch] BYREF
  idStr result; // [esp+84h] [ebp-4Ch] BYREF
  idStr v56; // [esp+A4h] [ebp-2Ch] BYREF
  int v57; // [esp+CCh] [ebp-4h]

  v6 = 0;
  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  num = this->declFolders.num;
  v57 = 0;
  if ( num > 0 )
  {
    do
    {
      if ( !idStr::Icmp(this->declFolders.list[v6]->folder.data, folder)
        && !idStr::Icmp(this->declFolders.list[v6]->extension.data, extension) )
      {
        break;
      }
      ++v6;
    }
    while ( v6 < this->declFolders.num );
  }
  if ( v6 >= this->declFolders.num )
  {
    v9 = Memory::Allocate(0x44u);
    if ( v9 )
    {
      *v9 = 0;
      v9[1] = v9 + 3;
      v9[2] = 20;
      *((_BYTE *)v9 + 12) = 0;
      v9[8] = 0;
      v9[10] = 20;
      v9[9] = v9 + 11;
      *((_BYTE *)v9 + 44) = 0;
      v10 = (idDeclFolder *)v9;
    }
    else
    {
      v10 = 0;
    }
    declFolder = v10;
    idStr::operator=(&v10->folder, folder);
    idStr::operator=(&v10->extension, extension);
    v10->defaultType = defaultType;
    if ( !this->declFolders.list )
    {
      granularity = this->declFolders.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->declFolders.size )
        {
          v12 = granularity < this->declFolders.num;
          this->declFolders.size = granularity;
          if ( v12 )
            this->declFolders.num = granularity;
          this->declFolders.list = (idDeclFolder **)Memory::Allocate(4 * granularity);
          for ( j = 0; j < this->declFolders.num; ++j )
            this->declFolders.list[j] = *(idDeclFolder **)(4 * j);
        }
      }
      else
      {
        this->declFolders.list = 0;
        this->declFolders.num = 0;
        this->declFolders.size = 0;
      }
    }
    v14 = this->declFolders.num;
    size = this->declFolders.size;
    if ( v14 == size )
    {
      if ( !this->declFolders.granularity )
        this->declFolders.granularity = 16;
      v16 = size
          + this->declFolders.granularity
          - (size + this->declFolders.granularity) % this->declFolders.granularity;
      if ( v16 > 0 )
      {
        if ( v16 != this->declFolders.size )
        {
          list = this->declFolders.list;
          this->declFolders.size = v16;
          if ( v16 < v14 )
            this->declFolders.num = v16;
          this->declFolders.list = (idDeclFolder **)Memory::Allocate(4 * v16);
          for ( k = 0; k < this->declFolders.num; ++k )
            this->declFolders.list[k] = list[k];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->declFolders.list )
          Memory::Free(this->declFolders.list);
        this->declFolders.list = 0;
        this->declFolders.num = 0;
        this->declFolders.size = 0;
      }
    }
    this->declFolders.list[this->declFolders.num++] = v10;
  }
  else
  {
    declFolder = this->declFolders.list[v6];
  }
  fileList = fileSystem->ListFiles(fileSystem, declFolder->folder.data, declFolder->extension.data, 1, 0, 0);
  i = 0;
  if ( fileList->list.num > 0 )
  {
    v50 = 0;
    do
    {
      v19 = operator+(&result, &declFolder->folder, "/");
      data = fileList->list.list[v50].data;
      LOBYTE(v57) = 1;
      v20 = operator+(&a, v19, data);
      len = v20->len;
      v22 = v20->len + 1;
      LOBYTE(v57) = 2;
      if ( v22 > fileName.alloced )
        idStr::ReAllocate(&fileName, v22, 0);
      qmemcpy(fileName.data, v20->data, len);
      fileName.data[len] = 0;
      fileName.len = len;
      LOBYTE(v57) = 1;
      idStr::FreeData(&a);
      LOBYTE(v57) = 0;
      idStr::FreeData(&result);
      for ( m = 0; m < this->loadedFiles.num; ++m )
      {
        if ( !idStr::Icmp(fileName.data, this->loadedFiles.list[m]->fileName.data) )
          break;
      }
      if ( m >= this->loadedFiles.num )
      {
        v25 = (idDeclFile *)Memory::Allocate(0x38u);
        if ( v25 )
        {
          v26 = fileName.data;
          v25->fileName.len = 0;
          v25->fileName.alloced = 20;
          v25->fileName.data = v25->fileName.baseBuffer;
          v25->fileName.baseBuffer[0] = 0;
          LOBYTE(v57) = 4;
          idStr::operator=(&v25->fileName, v26);
          v25->defaultType = defaultType;
          v25->timestamp = 0;
          v25->checksum = 0;
          v25->fileSize = 0;
          v25->numLines = 0;
          v25->decls = 0;
        }
        else
        {
          v25 = 0;
        }
        v27 = this->loadedFiles.list == 0;
        v51 = v25;
        LOBYTE(v57) = 0;
        v52 = v25;
        if ( v27 )
        {
          v28 = this->loadedFiles.granularity;
          if ( v28 > 0 )
          {
            if ( v28 != this->loadedFiles.size )
            {
              v12 = v28 < this->loadedFiles.num;
              this->loadedFiles.size = v28;
              if ( v12 )
                this->loadedFiles.num = v28;
              this->loadedFiles.list = (idDeclFile **)Memory::Allocate(4 * v28);
              for ( n = 0; n < this->loadedFiles.num; ++n )
                this->loadedFiles.list[n] = *(idDeclFile **)(4 * n);
            }
          }
          else
          {
            this->loadedFiles.list = 0;
            this->loadedFiles.num = 0;
            this->loadedFiles.size = 0;
          }
        }
        v30 = this->loadedFiles.num;
        v31 = this->loadedFiles.size;
        if ( v30 == v31 )
        {
          if ( !this->loadedFiles.granularity )
            this->loadedFiles.granularity = 16;
          v32 = v31
              + this->loadedFiles.granularity
              - (v31 + this->loadedFiles.granularity) % this->loadedFiles.granularity;
          if ( v32 > 0 )
          {
            if ( v32 != this->loadedFiles.size )
            {
              v33 = this->loadedFiles.list;
              this->loadedFiles.size = v32;
              if ( v32 < v30 )
                this->loadedFiles.num = v32;
              this->loadedFiles.list = (idDeclFile **)Memory::Allocate(4 * v32);
              for ( ii = 0; ii < this->loadedFiles.num; ++ii )
                this->loadedFiles.list[ii] = v33[ii];
              if ( v33 )
                Memory::Free(v33);
            }
          }
          else
          {
            if ( this->loadedFiles.list )
              Memory::Free(this->loadedFiles.list);
            this->loadedFiles.list = 0;
            this->loadedFiles.num = 0;
            this->loadedFiles.size = 0;
          }
        }
        this->loadedFiles.list[this->loadedFiles.num++] = v51;
        v24 = v52;
      }
      else
      {
        v24 = this->loadedFiles.list[m];
      }
      idDeclFile::LoadAndParse(v24, unique);
      ++v50;
      ++i;
    }
    while ( i < fileList->list.num );
  }
  fileSystem->FreeFileList(fileSystem, fileList);
  if ( !norecurse )
  {
    v35 = folder;
    v36 = fileSystem->ListFiles(fileSystem, folder, "/", 1, 0, 0);
    ia = 0;
    if ( v36->list.num > 0 )
    {
      fileLista = 0;
      do
      {
        v37 = *(int *)((char *)&v36->list.list->data + (unsigned int)fileLista);
        if ( *(_BYTE *)v37 && *(_BYTE *)v37 != 46 && *(_BYTE *)(v37 + 1) != 46 )
        {
          a.len = 0;
          a.alloced = 20;
          a.data = a.baseBuffer;
          a.baseBuffer[0] = 0;
          if ( v35 )
          {
            v38 = strlen(v35);
            if ( v38 + 1 > 20 )
              idStr::ReAllocate(&a, v38 + 1, 1);
            v39 = folder;
            v40 = a.data;
            do
            {
              v41 = *v39;
              *v40++ = *v39++;
            }
            while ( v41 );
            a.len = v38;
            v35 = folder;
          }
          LOBYTE(v57) = 5;
          v42 = operator+(&v56, &a, "/");
          LOBYTE(v57) = 6;
          v43 = operator+(&result, v42, (const char *)v37)->data;
          LOBYTE(v57) = 7;
          idDeclManagerLocal::RegisterDeclFolder(this, v43, extension, defaultType, unique, 0);
          LOBYTE(v57) = 6;
          idStr::FreeData(&result);
          LOBYTE(v57) = 5;
          idStr::FreeData(&v56);
          LOBYTE(v57) = 0;
          idStr::FreeData(&a);
        }
        fileLista = (idFileList *)((char *)fileLista + 32);
        ++ia;
      }
      while ( ia < v36->list.num );
    }
    fileSystem->FreeFileList(fileSystem, v36);
  }
  v57 = -1;
  idStr::FreeData(&fileName);
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::RegisterDeclFolderWrapper(char const *,char const *,enum declType_t,bool,bool)
void __thiscall idDeclManagerLocal::RegisterDeclFolderWrapper(
        idDeclManagerLocal *this,
        char *folder,
        char *extension,
        declType_t defaultType,
        bool unique,
        bool norecurse)
{
  int v7; // ebx
  int TotalTextMemory; // ebp
  int v9; // eax
  const char *v10; // [esp-4h] [ebp-14h]
  int norecursea; // [esp+24h] [ebp+14h]

  v7 = Sys_Milliseconds();
  idDeclManagerLocal::RegisterDeclFolder(this, folder, extension, defaultType, unique, norecurse);
  TotalTextMemory = idDeclManagerLocal::GetTotalTextMemory(this, defaultType);
  norecursea = *(_DWORD *)common.type;
  v10 = this->GetDeclTypeName(this, defaultType);
  v9 = Sys_Milliseconds();
  (*(void (**)(netadrtype_t, const char *, ...))(norecursea + 124))(
    common.type,
    "%dms to load %dk of %s\n",
    v9 - v7,
    (TotalTextMemory + 1023) / 1024,
    v10);
}

// FUNC: public: virtual class idDecl const * __thiscall idDeclManagerLocal::FindType(enum declType_t,char const *,bool,bool)
idDeclLocal *__thiscall idDeclManagerLocal::FindType(
        idDeclManagerLocal *this,
        int type,
        const char *name,
        bool makeDefault,
        int noCaching)
{
  const char *v5; // eax
  idDeclLocal *result; // eax
  idDecl *v8; // esi
  idDecl *v9; // eax
  idDeclBase *base; // eax

  v5 = name;
  if ( !name || !*name )
    v5 = "_emptyName";
  result = idDeclManagerLocal::FindTypeWithoutParsing(this, type, v5, makeDefault, -1);
  v8 = (idDecl *)result;
  if ( result )
  {
    if ( !result->self )
    {
      v9 = declManagerLocal.declTypes.list[result->type]->allocator();
      v8->base = (idDeclBase *)v9;
      v9->base = (idDeclBase *)v8;
    }
    if ( !v8[9].base )
    {
      idDeclLocal::ParseLocal((idDeclLocal *)v8, noCaching);
      if ( (_BYTE)noCaching )
        v8->List(v8);
    }
    v8->base->Index(v8->base);
    if ( this->insideLevelLoad )
      LOBYTE(v8[10].base) = 0;
    if ( type == 1 )
    {
      base = v8->base;
      if ( this->insideLevelLoad )
      {
        ++base[33].__vftable;
        ++base[34].__vftable;
      }
    }
    return (idDeclLocal *)v8->base;
  }
  return result;
}

// FUNC: public: virtual class idDecl const * __thiscall idDeclManagerLocal::FindDeclWithoutParsing(enum declType_t,char const *,bool)
const idDecl *__thiscall idDeclManagerLocal::FindDeclWithoutParsing(
        idDeclManagerLocal *this,
        int type,
        const char *name,
        bool makeDefault)
{
  idDeclLocal *TypeWithoutParsing; // eax

  TypeWithoutParsing = idDeclManagerLocal::FindTypeWithoutParsing(this, type, name, makeDefault, -1);
  if ( TypeWithoutParsing )
    return TypeWithoutParsing->self;
  else
    return 0;
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::PrintType(class idCmdArgs const &,enum declType_t)
void __thiscall idDeclManagerLocal::PrintType(idDeclManagerLocal *this, const idCmdArgs *args, int type)
{
  const char *v4; // eax
  idDeclLocal *TypeWithoutParsing; // esi
  const char *v6; // ecx
  int v7; // eax
  void *v8; // esp
  declState_t declState; // eax
  __int32 v10; // eax
  _BYTE v11[12]; // [esp+0h] [ebp-Ch] BYREF

  if ( args->argc >= 2 )
  {
    if ( args->argc <= 1 )
      v4 = &entityFilter;
    else
      v4 = args->argv[1];
    TypeWithoutParsing = idDeclManagerLocal::FindTypeWithoutParsing(this, type, v4, 0, -1);
    if ( TypeWithoutParsing )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%s %s:\n",
        this->declTypes.list[type]->typeName.data,
        TypeWithoutParsing->name.data);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "source: %s:%i\n",
        TypeWithoutParsing->sourceFile->fileName.data,
        TypeWithoutParsing->sourceLine);
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "----------\n");
      if ( TypeWithoutParsing->textSource )
      {
        v7 = TypeWithoutParsing->textLength + 4;
        LOBYTE(v7) = v7 & 0xFC;
        v8 = alloca(v7);
        TypeWithoutParsing->GetText(TypeWithoutParsing, v11);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s\n", v11);
      }
      else
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "NO SOURCE\n");
      }
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "----------\n");
      declState = TypeWithoutParsing->declState;
      if ( declState )
      {
        v10 = declState - 1;
        if ( v10 )
        {
          if ( v10 == 1 )
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Parsed.\n");
        }
        else
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "<DEFAULTED>\n");
        }
      }
      else
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Unparsed.\n");
      }
      if ( TypeWithoutParsing->referencedThisLevel )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "Currently referenced this level.\n");
      }
      else if ( TypeWithoutParsing->everReferenced )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "Referenced in a previous level.\n");
      }
      else
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "Never referenced.\n");
      }
      if ( TypeWithoutParsing->self )
        TypeWithoutParsing->self->Print(TypeWithoutParsing->self);
    }
    else
    {
      if ( args->argc <= 1 )
        v6 = &entityFilter;
      else
        v6 = args->argv[1];
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%s '%s' not found.\n",
        this->declTypes.list[type]->typeName.data,
        v6);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "USAGE: Print<decl type> <decl name> [type specific parms]\n");
  }
}

// FUNC: public: int __thiscall idDeclFile::LoadAndParse(class idFile *)
int __thiscall idDeclFile::LoadAndParse(idDeclFile *this, idFile *file)
{
  idDeclFile *v2; // ebp
  idFile *v3; // ebx
  unsigned int v4; // ecx
  idDeclLocal *decls; // eax
  unsigned int v6; // edi
  void *v7; // esi
  int v8; // eax
  idFile v9; // edx
  int v10; // edi
  const char *v11; // eax
  int line; // eax
  int num; // ebp
  int v14; // esi
  idDeclType *v15; // edi
  declType_t type; // ebp
  int len; // ebx
  int v18; // ebx
  int v19; // edi
  idDeclLocal *TypeWithoutParsing; // eax
  idDeclLocal *v21; // esi
  idDeclFile *sourceFile; // eax
  const char *data; // edi
  char *v24; // ebx
  char *textSource; // eax
  int v26; // eax
  int v27; // edi
  int v28; // eax
  int v29; // edi
  int v30; // eax
  idDeclLocal *j; // esi
  idDeclFile *v33; // eax
  int checksum; // esi
  bool guide; // [esp+Fh] [ebp-205h]
  void *buffer; // [esp+14h] [ebp-200h]
  unsigned int i; // [esp+18h] [ebp-1FCh]
  idStr name; // [esp+1Ch] [ebp-1F8h] BYREF
  unsigned int declCount; // [esp+3Ch] [ebp-1D8h]
  int numTypes; // [esp+40h] [ebp-1D4h]
  int index; // [esp+44h] [ebp-1D0h]
  int startMarker; // [esp+48h] [ebp-1CCh]
  int sourceLine; // [esp+4Ch] [ebp-1C8h]
  idStr definition; // [esp+50h] [ebp-1C4h] BYREF
  idStr declSizeString; // [esp+70h] [ebp-1A4h] BYREF
  idStr indexString; // [esp+90h] [ebp-184h] BYREF
  idStr stripped; // [esp+B0h] [ebp-164h] BYREF
  idToken token; // [esp+D0h] [ebp-144h] BYREF
  idLexer src; // [esp+120h] [ebp-F4h] BYREF
  idStr declCountString; // [esp+1E8h] [ebp-2Ch] BYREF
  int v52; // [esp+210h] [ebp-4h]

  token.floatvalue = 0.0;
  v2 = this;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v52 = 4;
  buffer = 0;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  definition.len = 0;
  definition.alloced = 20;
  definition.data = definition.baseBuffer;
  definition.baseBuffer[0] = 0;
  stripped.len = 0;
  stripped.alloced = 20;
  stripped.data = stripped.baseBuffer;
  stripped.baseBuffer[0] = 0;
  v3 = file;
  GetString(&declCountString, file);
  LOBYTE(v52) = 5;
  v4 = atoi(declCountString.data);
  decls = v2->decls;
  for ( declCount = v4; decls; decls = decls->nextInFile )
    decls->redefinedInReload = 0;
  i = 0;
  if ( !v4 )
    goto LABEL_54;
  while ( 1 )
  {
    idLexer::idLexer(&src);
    LOBYTE(v52) = 6;
    GetString(&indexString, v3);
    LOBYTE(v52) = 7;
    index = atoi(indexString.data);
    GetString(&declSizeString, v3);
    LOBYTE(v52) = 8;
    v6 = atoi(declSizeString.data);
    v7 = Memory::Allocate(v6);
    if ( v7 != buffer )
      Memory::Free(buffer);
    buffer = v7;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "...loading '%s'\n",
      v2->fileName.data);
    v8 = v3->Read(v3, v7, v6);
    v9.__vftable = v3->__vftable;
    v10 = v8;
    if ( v8 == -1 )
    {
      v27 = *(_DWORD *)common.type;
      v28 = (int)v9.GetFullPath(v3);
      (*(void (**)(netadrtype_t, const char *, ...))(v27 + 156))(common.type, "couldn't load %s", v28);
LABEL_51:
      LOBYTE(v52) = 7;
      idStr::FreeData(&declSizeString);
      LOBYTE(v52) = 6;
      idStr::FreeData(&indexString);
      LOBYTE(v52) = 5;
      idLexer::~idLexer(&src);
      LOBYTE(v52) = 4;
      idStr::FreeData(&declCountString);
      LOBYTE(v52) = 3;
      idStr::FreeData(&stripped);
      LOBYTE(v52) = 2;
      idStr::FreeData(&definition);
      LOBYTE(v52) = 1;
      idStr::FreeData(&name);
      LOBYTE(v52) = 0;
      Memory::Free(v7);
      v52 = -1;
      idStr::FreeData(&token);
      return 0;
    }
    v11 = v9.GetFullPath(v3);
    if ( !idLexer::LoadMemory(&src, (const char *)v7, v10, v11, 1) )
    {
      v29 = *(_DWORD *)common.type;
      v30 = (int)v3->GetFullPath(v3);
      (*(void (**)(netadrtype_t, const char *, ...))(v29 + 152))(common.type, "Couldn't parse %s", v30);
      goto LABEL_51;
    }
    src.flags = 6300;
    v2->checksum = MD5_BlockChecksum(v7, v10);
    startMarker = src.script_p - src.buffer;
    line = src.line;
    v2->fileSize = v10;
    sourceLine = line;
    if ( !idLexer::ReadToken(&src, &token) )
      break;
    guide = 0;
    if ( !idStr::Icmp(token.data, "guide") )
    {
      guide = 1;
      idLexer::ReadToken(&src, &token);
    }
    num = declManagerLocal.declTypes.num;
    v14 = 0;
    numTypes = declManagerLocal.declTypes.num;
    if ( declManagerLocal.declTypes.num <= 0 )
      goto LABEL_17;
    while ( 1 )
    {
      v15 = declManagerLocal.declTypes.list[v14];
      if ( v15 )
      {
        if ( !idStr::Icmp(v15->typeName.data, token.data) )
          break;
      }
      if ( ++v14 >= num )
        goto LABEL_17;
    }
    type = v15->type;
    if ( v14 >= numTypes )
    {
LABEL_17:
      if ( !idStr::Icmp(token.data, "{") )
        goto LABEL_18;
      if ( this->defaultType == DECL_MAX_TYPES )
      {
        idLexer::Warning(&src, "No type");
        goto LABEL_26;
      }
      idLexer::UnreadToken(&src, &token);
      type = this->defaultType;
    }
    if ( !idLexer::ReadToken(&src, &token) )
    {
      idLexer::Warning(&src, "Type without definition at end of file");
      LOBYTE(v52) = 7;
      idStr::FreeData(&declSizeString);
      LOBYTE(v52) = 6;
      idStr::FreeData(&indexString);
      LOBYTE(v52) = 5;
      idLexer::~idLexer(&src);
      v2 = this;
      goto LABEL_54;
    }
    if ( !idStr::Icmp(token.data, "{") )
    {
LABEL_18:
      idLexer::Warning(&src, "Missing decl name");
      idLexer::SkipBracedSection(&src, 0);
      goto LABEL_26;
    }
    if ( type != DECL_MODELEXPORT )
    {
      len = token.len;
      if ( token.len + 1 > name.alloced )
        idStr::ReAllocate(&name, token.len + 1, 0);
      qmemcpy(name.data, token.data, len);
      name.data[len] = 0;
      name.len = len;
      if ( guide )
        declManager->EvaluateGuide(declManager, &name, &src, &definition);
      else
        idLexer::ParseBracedSectionExact(&src, &definition, -1);
      declManager->EvaluateInlineGuide(declManager, &name, &definition);
      v18 = startMarker;
      v19 = src.script_p - src.buffer - startMarker;
      TypeWithoutParsing = idDeclManagerLocal::FindTypeWithoutParsing(&declManagerLocal, type, name.data, 0, -1);
      v21 = TypeWithoutParsing;
      if ( TypeWithoutParsing )
      {
        sourceFile = TypeWithoutParsing->sourceFile;
        if ( sourceFile != this || v21->redefinedInReload )
        {
          data = sourceFile->fileName.data;
          v24 = name.data;
          if ( type < DECL_TABLE || type >= declManagerLocal.declTypes.num || !declManagerLocal.declTypes.list[type] )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
              common.type,
              "idDeclManager::GetDeclNameFromType: bad type: %i",
              type);
          idLexer::Warning(
            &src,
            "%s '%s' previously defined at %s:%i",
            declManagerLocal.declTypes.list[type]->typeName.data,
            v24,
            data,
            v21->sourceLine);
          goto LABEL_46;
        }
      }
      else
      {
        v21 = idDeclManagerLocal::FindTypeWithoutParsing(&declManagerLocal, type, name.data, 1, index);
        v21->nextInFile = this->decls;
        this->decls = v21;
      }
      textSource = v21->textSource;
      v21->declState = DS_UNPARSED;
      v21->redefinedInReload = 1;
      if ( textSource )
      {
        if ( v21->needsPrecache )
        {
LABEL_46:
          LOBYTE(v52) = 7;
          idStr::FreeData(&declSizeString);
          LOBYTE(v52) = 6;
          idStr::FreeData(&indexString);
          LOBYTE(v52) = 5;
          idLexer::~idLexer(&src);
          v3 = file;
          goto LABEL_47;
        }
        Mem_Free(textSource);
        v21->textSource = 0;
      }
      if ( !v21->needsPrecache )
      {
        idDeclLocal::SetTextLocal(v21, definition.data, definition.len);
        v26 = sourceLine;
        v21->sourceFile = this;
        v21->sourceTextOffset = v18;
        v21->sourceTextLength = v19;
        v21->sourceLine = v26;
      }
      goto LABEL_46;
    }
    idLexer::SkipBracedSection(&src, 1);
LABEL_26:
    LOBYTE(v52) = 7;
    idStr::FreeData(&declSizeString);
    LOBYTE(v52) = 6;
    idStr::FreeData(&indexString);
    LOBYTE(v52) = 5;
    idLexer::~idLexer(&src);
LABEL_47:
    v2 = this;
    if ( ++i >= declCount )
      goto LABEL_54;
  }
  LOBYTE(v52) = 7;
  idStr::FreeData(&declSizeString);
  LOBYTE(v52) = 6;
  idStr::FreeData(&indexString);
  LOBYTE(v52) = 5;
  idLexer::~idLexer(&src);
LABEL_54:
  for ( j = v2->decls; j; j = j->nextInFile )
  {
    if ( !j->redefinedInReload )
    {
      j->MakeDefault(j);
      v33 = j->sourceFile;
      j->sourceTextOffset = v33->fileSize;
      j->sourceTextLength = 0;
      j->sourceLine = v33->numLines;
    }
  }
  checksum = v2->checksum;
  LOBYTE(v52) = 4;
  idStr::FreeData(&declCountString);
  LOBYTE(v52) = 3;
  idStr::FreeData(&stripped);
  LOBYTE(v52) = 2;
  idStr::FreeData(&definition);
  LOBYTE(v52) = 1;
  idStr::FreeData(&name);
  LOBYTE(v52) = 0;
  Memory::Free(buffer);
  v52 = -1;
  idStr::FreeData(&token);
  return checksum;
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::LoadDeclsFromFile(void)
void __thiscall idDeclManagerLocal::LoadDeclsFromFile(idDeclManagerLocal *this)
{
  idDeclManagerLocal *v1; // esi
  idFile *mSingleDeclFile; // eax
  int v3; // eax
  idStr *String; // esi
  unsigned int len; // ebp
  int v6; // eax
  idStr *v7; // esi
  unsigned int v8; // ebp
  int v9; // eax
  int v10; // esi
  idStr *v11; // eax
  int v12; // ebp
  idStr *v13; // eax
  int v14; // ebx
  idDeclFolder **v15; // ecx
  int v16; // edi
  int num; // ebp
  int size; // ebx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  idDeclFolder **v22; // esi
  int v23; // eax
  int v24; // ebp
  idDeclFile *v25; // esi
  int v26; // edi
  int v27; // eax
  char *data; // ecx
  char *v29; // edx
  char v30; // al
  int v31; // eax
  idDeclFile *v32; // esi
  char *v33; // ecx
  idDeclFile *v34; // ecx
  idDeclFile **list; // ecx
  int granularity; // ebp
  int v37; // eax
  int v38; // edx
  int v39; // eax
  idDeclFile **v40; // edi
  int v41; // eax
  idStr *v42; // [esp+8h] [ebp-11Ch]
  declType_t defaultType; // [esp+Ch] [ebp-118h]
  int v45; // [esp+14h] [ebp-110h]
  idStr extension; // [esp+18h] [ebp-10Ch] BYREF
  idStr fileName; // [esp+38h] [ebp-ECh] BYREF
  idStr folderFile; // [esp+58h] [ebp-CCh] BYREF
  idStr folder; // [esp+78h] [ebp-ACh] BYREF
  idStr defaultTypeString; // [esp+98h] [ebp-8Ch] BYREF
  idStr countString; // [esp+B8h] [ebp-6Ch] BYREF
  idStr result; // [esp+D8h] [ebp-4Ch] BYREF
  idStr v53; // [esp+F8h] [ebp-2Ch] BYREF
  int v54; // [esp+120h] [ebp-4h]

  v1 = this;
  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  mSingleDeclFile = this->mSingleDeclFile;
  v54 = 0;
  if ( mSingleDeclFile )
  {
    folder.len = 0;
    folder.alloced = 20;
    folder.data = folder.baseBuffer;
    folder.baseBuffer[0] = 0;
    extension.alloced = 20;
    extension.len = 0;
    extension.data = extension.baseBuffer;
    extension.baseBuffer[0] = 0;
    LOBYTE(v54) = 2;
    GetString(&countString, mSingleDeclFile);
    LOBYTE(v54) = 3;
    v3 = atoi(countString.data);
    if ( v3 )
    {
      v45 = v3;
      while ( 1 )
      {
        String = GetString(&result, v1->mSingleDeclFile);
        len = String->len;
        v6 = String->len + 1;
        LOBYTE(v54) = 4;
        if ( v6 > fileName.alloced )
          idStr::ReAllocate(&fileName, v6, 0);
        qmemcpy(fileName.data, String->data, len);
        fileName.data[len] = 0;
        fileName.len = len;
        LOBYTE(v54) = 3;
        idStr::FreeData(&result);
        idStr::ExtractFileExtension(&fileName, &extension);
        v7 = operator+(&v53, ".", &extension);
        v8 = v7->len;
        v9 = v7->len + 1;
        LOBYTE(v54) = 5;
        if ( v9 > extension.alloced )
          idStr::ReAllocate(&extension, v9, 0);
        qmemcpy(extension.data, v7->data, v8);
        extension.data[v8] = 0;
        extension.len = v8;
        LOBYTE(v54) = 3;
        idStr::FreeData(&v53);
        idStr::ExtractFilePath(&fileName, &folder);
        idStr::StripTrailingOnce(&folder, "/");
        GetString(&defaultTypeString, this->mSingleDeclFile);
        LOBYTE(v54) = 6;
        v10 = 0;
        defaultType = atoi(defaultTypeString.data);
        if ( declManagerLocal.declFolders.num <= 0 )
          break;
        while ( idStr::Icmp(declManagerLocal.declFolders.list[v10]->folder.data, folder.data)
             || idStr::Icmp(declManagerLocal.declFolders.list[v10]->extension.data, extension.data) )
        {
          if ( ++v10 >= declManagerLocal.declFolders.num )
            goto LABEL_15;
        }
        if ( v10 >= declManagerLocal.declFolders.num )
          break;
LABEL_46:
        v24 = 0;
        if ( declManagerLocal.loadedFiles.num > 0 )
        {
          while ( 1 )
          {
            v25 = declManagerLocal.loadedFiles.list[v24];
            folderFile.len = 0;
            folderFile.alloced = 20;
            folderFile.data = folderFile.baseBuffer;
            folderFile.baseBuffer[0] = 0;
            v26 = v25->fileName.len;
            v27 = v25->fileName.len + 1;
            if ( v27 > 20 )
              idStr::ReAllocate(&folderFile, v27, 1);
            data = v25->fileName.data;
            v29 = folderFile.data;
            do
            {
              v30 = *data;
              *v29++ = *data++;
            }
            while ( v30 );
            folderFile.len = v26;
            LOBYTE(v54) = 7;
            v31 = idStr::Icmp(fileName.data, folderFile.data);
            LOBYTE(v54) = 6;
            if ( !v31 )
              break;
            idStr::FreeData(&folderFile);
            if ( ++v24 >= declManagerLocal.loadedFiles.num )
              goto LABEL_53;
          }
          idStr::FreeData(&folderFile);
          if ( v24 < declManagerLocal.loadedFiles.num )
          {
            v34 = declManagerLocal.loadedFiles.list[v24];
            goto LABEL_82;
          }
        }
LABEL_53:
        v32 = (idDeclFile *)Memory::Allocate(0x38u);
        if ( v32 )
        {
          v33 = fileName.data;
          v32->fileName.len = 0;
          v32->fileName.alloced = 20;
          v32->fileName.data = v32->fileName.baseBuffer;
          v32->fileName.baseBuffer[0] = 0;
          LOBYTE(v54) = 9;
          idStr::operator=(&v32->fileName, v33);
          v32->defaultType = defaultType;
          v32->timestamp = 0;
          v32->checksum = 0;
          v32->fileSize = 0;
          v32->numLines = 0;
          v32->decls = 0;
        }
        else
        {
          v32 = 0;
        }
        list = declManagerLocal.loadedFiles.list;
        granularity = declManagerLocal.loadedFiles.granularity;
        LOBYTE(v54) = 6;
        if ( !declManagerLocal.loadedFiles.list )
        {
          if ( declManagerLocal.loadedFiles.granularity <= 0 )
          {
            list = 0;
            declManagerLocal.loadedFiles.list = 0;
            declManagerLocal.loadedFiles.num = 0;
            declManagerLocal.loadedFiles.size = 0;
LABEL_68:
            if ( !granularity )
            {
              granularity = 16;
              declManagerLocal.loadedFiles.granularity = 16;
            }
            v38 = (declManagerLocal.loadedFiles.size + granularity) % granularity;
            v39 = declManagerLocal.loadedFiles.size + granularity - v38;
            if ( v39 > 0 )
            {
              if ( v39 != declManagerLocal.loadedFiles.size )
              {
                v40 = list;
                declManagerLocal.loadedFiles.size = declManagerLocal.loadedFiles.size + granularity - v38;
                if ( v39 < declManagerLocal.loadedFiles.num )
                  declManagerLocal.loadedFiles.num = v39;
                list = (idDeclFile **)Memory::Allocate(4 * v39);
                v41 = 0;
                for ( declManagerLocal.loadedFiles.list = list; v41 < declManagerLocal.loadedFiles.num; ++v41 )
                {
                  list[v41] = v40[v41];
                  list = declManagerLocal.loadedFiles.list;
                }
                if ( v40 )
                {
                  Memory::Free(v40);
                  list = declManagerLocal.loadedFiles.list;
                }
              }
            }
            else
            {
              if ( list )
                Memory::Free(list);
              list = 0;
              declManagerLocal.loadedFiles.list = 0;
              declManagerLocal.loadedFiles.num = 0;
              declManagerLocal.loadedFiles.size = 0;
            }
            goto LABEL_81;
          }
          if ( declManagerLocal.loadedFiles.granularity != declManagerLocal.loadedFiles.size )
          {
            declManagerLocal.loadedFiles.size = declManagerLocal.loadedFiles.granularity;
            if ( declManagerLocal.loadedFiles.granularity < declManagerLocal.loadedFiles.num )
              declManagerLocal.loadedFiles.num = declManagerLocal.loadedFiles.granularity;
            list = (idDeclFile **)Memory::Allocate(4 * declManagerLocal.loadedFiles.granularity);
            v37 = 0;
            for ( declManagerLocal.loadedFiles.list = list; v37 < declManagerLocal.loadedFiles.num; ++v37 )
            {
              list[v37] = *(idDeclFile **)(4 * v37);
              list = declManagerLocal.loadedFiles.list;
            }
            granularity = declManagerLocal.loadedFiles.granularity;
          }
        }
        if ( declManagerLocal.loadedFiles.num == declManagerLocal.loadedFiles.size )
          goto LABEL_68;
LABEL_81:
        list[declManagerLocal.loadedFiles.num++] = v32;
        v34 = v32;
LABEL_82:
        idDeclFile::LoadAndParse(v34, this->mSingleDeclFile);
        LOBYTE(v54) = 3;
        idStr::FreeData(&defaultTypeString);
        if ( !--v45 )
          goto LABEL_83;
        v1 = this;
      }
LABEL_15:
      v11 = (idStr *)Memory::Allocate(0x44u);
      if ( v11 )
      {
        v11->len = 0;
        v11->data = v11->baseBuffer;
        v11->alloced = 20;
        v11->baseBuffer[0] = 0;
        v11[1].len = 0;
        v11[1].alloced = 20;
        v11[1].data = v11[1].baseBuffer;
        v11[1].baseBuffer[0] = 0;
      }
      else
      {
        v11 = 0;
      }
      v12 = folder.len;
      v42 = v11;
      if ( folder.len + 1 > v11->alloced )
        idStr::ReAllocate(v11, folder.len + 1, 0);
      v13 = v42;
      qmemcpy(v42->data, folder.data, v12);
      v42->data[v12] = 0;
      v42->len = v12;
      v14 = extension.len;
      if ( extension.len + 1 > v42[1].alloced )
      {
        idStr::ReAllocate(v42 + 1, extension.len + 1, 0);
        v13 = v42;
      }
      qmemcpy(v42[1].data, extension.data, v14);
      v42[1].data[v14] = 0;
      v42[1].len = v14;
      v13[2].len = defaultType;
      v15 = declManagerLocal.declFolders.list;
      v16 = declManagerLocal.declFolders.granularity;
      if ( !declManagerLocal.declFolders.list )
      {
        if ( declManagerLocal.declFolders.granularity <= 0 )
        {
          num = 0;
          size = 0;
          declManagerLocal.declFolders.num = 0;
          declManagerLocal.declFolders.size = 0;
          goto LABEL_32;
        }
        if ( declManagerLocal.declFolders.granularity != declManagerLocal.declFolders.size )
        {
          declManagerLocal.declFolders.size = declManagerLocal.declFolders.granularity;
          if ( declManagerLocal.declFolders.granularity < declManagerLocal.declFolders.num )
            declManagerLocal.declFolders.num = declManagerLocal.declFolders.granularity;
          v15 = (idDeclFolder **)Memory::Allocate(4 * declManagerLocal.declFolders.granularity);
          v19 = 0;
          for ( declManagerLocal.declFolders.list = v15; v19 < declManagerLocal.declFolders.num; ++v19 )
          {
            v15[v19] = *(idDeclFolder **)(4 * v19);
            v15 = declManagerLocal.declFolders.list;
          }
          v16 = declManagerLocal.declFolders.granularity;
        }
      }
      num = declManagerLocal.declFolders.num;
      size = declManagerLocal.declFolders.size;
      if ( declManagerLocal.declFolders.num != declManagerLocal.declFolders.size )
      {
LABEL_45:
        v15[declManagerLocal.declFolders.num++] = (idDeclFolder *)v42;
        goto LABEL_46;
      }
LABEL_32:
      if ( !v16 )
      {
        v16 = 16;
        declManagerLocal.declFolders.granularity = 16;
      }
      v20 = (size + v16) % v16;
      v21 = size + v16 - v20;
      if ( v21 > 0 )
      {
        if ( v21 != size )
        {
          v22 = v15;
          declManagerLocal.declFolders.size = size + v16 - v20;
          if ( v21 < num )
            declManagerLocal.declFolders.num = size + v16 - v20;
          v15 = (idDeclFolder **)Memory::Allocate(4 * v21);
          v23 = 0;
          for ( declManagerLocal.declFolders.list = v15; v23 < declManagerLocal.declFolders.num; ++v23 )
          {
            v15[v23] = v22[v23];
            v15 = declManagerLocal.declFolders.list;
          }
          if ( v22 )
          {
            Memory::Free(v22);
            v15 = declManagerLocal.declFolders.list;
          }
        }
      }
      else
      {
        if ( v15 )
          Memory::Free(v15);
        v15 = 0;
        declManagerLocal.declFolders.list = 0;
        declManagerLocal.declFolders.num = 0;
        declManagerLocal.declFolders.size = 0;
      }
      goto LABEL_45;
    }
LABEL_83:
    LOBYTE(v54) = 2;
    idStr::FreeData(&countString);
    LOBYTE(v54) = 1;
    idStr::FreeData(&extension);
    LOBYTE(v54) = 0;
    idStr::FreeData(&folder);
  }
  v54 = -1;
  idStr::FreeData(&fileName);
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::WriteDeclFile(void)
void __usercall idDeclManagerLocal::WriteDeclFile(idDeclManagerLocal *this@<ecx>, int a2@<ebx>)
{
  const char *v2; // eax
  char *v3; // eax
  char *v4; // esi
  unsigned int v5; // eax
  int v6; // edi
  int v7; // eax
  char *data; // edx
  char *v9; // ecx
  char v10; // al
  idFile *v11; // ebx
  _DWORD *v12; // esi
  _DWORD *v13; // ebp
  int v14; // edi
  int i; // edi
  int v16; // edi
  int j; // edi
  int v18; // [esp+Ch] [ebp-C0h]
  int v19; // [esp+10h] [ebp-BCh]
  idFile *v20; // [esp+14h] [ebp-B8h]
  idList<enum declType_t> gameTypes; // [esp+1Ch] [ebp-B0h] BYREF
  idList<enum declType_t> frameworkTypes; // [esp+2Ch] [ebp-A0h] BYREF
  idStr fileNameString; // [esp+3Ch] [ebp-90h] BYREF
  char numberBuf[100]; // [esp+5Ch] [ebp-70h] BYREF
  int v25; // [esp+C8h] [ebp-4h]
  void *retaddr; // [esp+CCh] [ebp+0h]

  v2 = fileSystem->GetAssetLogName(fileSystem);
  v3 = strchr(v2, 47);
  v4 = v3 + 1;
  fileNameString.len = 0;
  fileNameString.alloced = 20;
  fileNameString.data = fileNameString.baseBuffer;
  fileNameString.baseBuffer[0] = 0;
  if ( v3 != (char *)-1 )
  {
    v5 = (unsigned int)&v3[strlen(v3 + 1) + 2];
    v6 = v5 - (_DWORD)(v4 + 1);
    v7 = v5 - (_DWORD)v4;
    if ( v7 > 20 )
      idStr::ReAllocate(&fileNameString, v7, 1);
    data = fileNameString.data;
    v9 = v4;
    do
    {
      v10 = *v9;
      *data++ = *v9++;
    }
    while ( v10 );
    fileNameString.len = v6;
  }
  v25 = 0;
  idStr::SetFileExtension(&fileNameString, ".decls");
  v11 = (idFile *)((int (__thiscall *)(idFileSystem *, char *, const char *, _DWORD, int))fileSystem->OpenFileWrite)(
                    fileSystem,
                    fileNameString.data,
                    "fs_savepath",
                    0,
                    a2);
  frameworkTypes.list = (declType_t *)16;
  fileNameString.len = 0;
  gameTypes.list = (declType_t *)16;
  LOBYTE(retaddr) = 2;
  frameworkTypes.granularity = 16;
  v12 = Memory::Allocate(0x40u);
  *v12 = 0;
  v12[1] = 1;
  v12[2] = 2;
  v12[3] = 3;
  v12[4] = 6;
  v12[5] = 7;
  v12[6] = 8;
  v12[7] = 9;
  v12[8] = 12;
  v12[9] = 13;
  v12[10] = 14;
  v12[11] = 15;
  fileNameString.len = (int)v12;
  v12[12] = 17;
  frameworkTypes.size = 13;
  gameTypes.granularity = 16;
  v13 = Memory::Allocate(0x40u);
  *v13 = 4;
  v13[1] = 5;
  v13[2] = 10;
  v13[3] = 11;
  v13[4] = 16;
  v14 = 0;
  frameworkTypes.num = (int)v13;
  gameTypes.size = 5;
  for ( gameTypes.num = 0; v14 < declManagerLocal.loadedFiles.num; ++v14 )
    gameTypes.num += idDeclManagerLocal::NumWritableDecls(
                       &declManagerLocal,
                       declManagerLocal.loadedFiles.list[v14],
                       (const idList<enum declType_t> *)&frameworkTypes.size,
                       0) != 0;
  sprintf(&numberBuf[4], "%d\n", gameTypes.num);
  v11->Write(v11, &numberBuf[4], strlen(&numberBuf[4]));
  for ( i = 0; i < declManagerLocal.loadedFiles.num; ++i )
    idDeclManagerLocal::WriteDecls(
      &declManagerLocal,
      (int)v11,
      (int)v13,
      (const char *)i,
      (int)v12,
      v11,
      declManagerLocal.loadedFiles.list[i],
      (const idList<enum declType_t> *)&frameworkTypes.size,
      0,
      v18,
      v19,
      v20);
  v16 = 0;
  for ( gameTypes.num = 0; v16 < declManagerLocal.loadedFiles.num; ++v16 )
    gameTypes.num += idDeclManagerLocal::NumWritableDecls(
                       &declManagerLocal,
                       declManagerLocal.loadedFiles.list[v16],
                       (const idList<enum declType_t> *)&gameTypes.size,
                       0) != 0;
  sprintf(&numberBuf[4], "%d\n", gameTypes.num);
  v11->Write(v11, &numberBuf[4], strlen(&numberBuf[4]));
  for ( j = 0; j < declManagerLocal.loadedFiles.num; ++j )
    idDeclManagerLocal::WriteDecls(
      &declManagerLocal,
      (int)v11,
      (int)v13,
      (const char *)j,
      (int)v12,
      v11,
      declManagerLocal.loadedFiles.list[j],
      (const idList<enum declType_t> *)&gameTypes.size,
      0,
      v18,
      v19,
      v20);
  ((void (__thiscall *)(idFileSystem *))fileSystem->CloseFile)(fileSystem);
  LOBYTE(v25) = 1;
  if ( v13 )
    Memory::Free(v13);
  LOBYTE(v25) = 0;
  if ( v12 )
    Memory::Free(v12);
  v25 = -1;
  idStr::FreeData(&fileNameString);
}

// FUNC: private: static void __cdecl idDeclManagerLocal::ResaveDecl_f(class idCmdArgs const &)
void __cdecl idDeclManagerLocal::ResaveDecl_f(const idCmdArgs *args)
{
  int j; // esi
  idDeclType *v2; // eax
  int v3; // edi
  idDeclType *v4; // eax
  const char *v5; // ecx
  const char *v6; // eax
  idDeclLocal *Type; // esi
  int v8; // edi
  int v9; // eax
  int i; // ebx
  const idDecl *v11; // esi
  int v12; // ebp
  int v13; // eax

  if ( args->argc >= 2 )
  {
    v3 = 0;
    if ( declManagerLocal.declTypes.num <= 0 )
      goto LABEL_16;
    while ( 1 )
    {
      v4 = declManagerLocal.declTypes.list[v3];
      if ( v4 )
      {
        v5 = args->argc <= 1 ? &entityFilter : args->argv[1];
        if ( !idStr::Icmp(v4->typeName.data, v5) )
          break;
      }
      if ( ++v3 >= declManagerLocal.declTypes.num )
        goto LABEL_16;
    }
    if ( v3 < declManagerLocal.declTypes.num )
    {
      if ( args->argc <= 2 )
      {
        for ( i = 0; ; ++i )
        {
          if ( v3 < 0 || v3 >= declManagerLocal.declTypes.num || !declManagerLocal.declTypes.list[v3] )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
              common.type,
              "idDeclManager::GetNumDecls: bad type: %i",
              v3);
          if ( i >= declManagerLocal.linearLists[v3].num )
            break;
          v11 = idDeclManagerLocal::DeclByIndex(&declManagerLocal, v3, i, 1);
          v12 = *(_DWORD *)common.type;
          v13 = (int)v11->base->GetName(v11->base);
          (*(void (**)(netadrtype_t, const char *, ...))(v12 + 124))(common.type, "...resaving: %s\n", v13);
          v11->RebuildTextSource((idDecl *)v11);
          v11->base->ReplaceSourceFileText(v11->base);
        }
      }
      else
      {
        Type = idDeclManagerLocal::FindType(&declManagerLocal, v3, args->argv[2], 1, 0);
        v8 = *(_DWORD *)common.type;
        v9 = ((int (__thiscall *)(idDecl *))Type->self->SetDefaultText)(Type->self);
        (*(void (**)(netadrtype_t, const char *, ...))(v8 + 124))(common.type, "...resaving: %s\n", v9);
        Type->EnsureNotPurged(Type);
        Type->self->__vftable[1].Size(Type->self);
      }
    }
    else
    {
LABEL_16:
      if ( args->argc <= 1 )
        v6 = &entityFilter;
      else
        v6 = args->argv[1];
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "unknown decl type '%s'\n",
        v6);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: resaveDecl <type> [name]\n");
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "valid types: ");
    for ( j = 0; j < declManagerLocal.declTypes.num; ++j )
    {
      v2 = declManagerLocal.declTypes.list[j];
      if ( v2 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%s ",
          v2->typeName.data);
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
  }
}

// FUNC: private: static void __cdecl idDeclManagerLocal::TouchDecl_f(class idCmdArgs const &)
void __cdecl idDeclManagerLocal::TouchDecl_f(const idCmdArgs *args)
{
  int i; // esi
  idDeclType *v2; // eax
  int v3; // esi
  idDeclType *v4; // eax
  const char *v5; // ecx
  const char *v6; // eax
  const char *v7; // eax
  const char *v8; // eax

  if ( args->argc == 3 )
  {
    v3 = 0;
    if ( declManagerLocal.declTypes.num <= 0 )
      goto LABEL_16;
    while ( 1 )
    {
      v4 = declManagerLocal.declTypes.list[v3];
      if ( v4 )
      {
        v5 = args->argc <= 1 ? &entityFilter : args->argv[1];
        if ( !idStr::Icmp(v4->typeName.data, v5) )
          break;
      }
      if ( ++v3 >= declManagerLocal.declTypes.num )
        goto LABEL_16;
    }
    if ( v3 < declManagerLocal.declTypes.num )
    {
      if ( args->argc <= 2 )
        v7 = &entityFilter;
      else
        v7 = args->argv[2];
      if ( !idDeclManagerLocal::FindType(&declManagerLocal, v3, v7, 1, 0) )
      {
        if ( args->argc <= 2 )
          v8 = &entityFilter;
        else
          v8 = args->argv[2];
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%s '%s' not found\n",
          declManagerLocal.declTypes.list[v3]->typeName.data,
          v8);
      }
    }
    else
    {
LABEL_16:
      if ( args->argc <= 1 )
        v6 = &entityFilter;
      else
        v6 = args->argv[1];
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "unknown decl type '%s'\n",
        v6);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: touch <type> <name>\n");
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "valid types: ");
    for ( i = 0; i < declManagerLocal.declTypes.num; ++i )
    {
      v2 = declManagerLocal.declTypes.list[i];
      if ( v2 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%s ",
          v2->typeName.data);
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
  }
}

// FUNC: public: class rvDeclGuide * __thiscall idDeclManagerLocal::GetNewGuide(class idLexer *,class idStr &)
rvDeclGuide *__thiscall idDeclManagerLocal::GetNewGuide(idDeclManagerLocal *this, idLexer *src, idStr *file)
{
  char *data; // eax
  char v6; // cl
  char *v7; // ebp
  int v8; // edx
  unsigned int v9; // ebp
  idHashTable<rvDeclGuide *>::hashnode_s *v10; // esi
  int v11; // eax
  rvDeclGuide *v12; // eax
  rvDeclGuide *v13; // eax
  rvDeclGuide *v14; // esi
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v16; // [esp+64h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v16 = 0;
  if ( idLexer::ReadToken(src, &token) )
  {
    data = token.data;
    v6 = *token.data;
    v7 = token.data;
    v8 = 0;
    if ( *token.data )
    {
      do
      {
        v9 = v6 * (_DWORD)&data[119 - (unsigned int)token.data];
        v6 = *++data;
        v8 += v9;
      }
      while ( v6 );
      v7 = token.data;
    }
    v10 = this->guideTable.heads[v8 & this->guideTable.tablesizemask];
    if ( v10 )
    {
      while ( 1 )
      {
        v11 = idStr::Cmp(v10->key.data, v7);
        if ( !v11 )
          break;
        if ( v11 <= 0 )
        {
          v10 = v10->next;
          if ( v10 )
            continue;
        }
        goto LABEL_10;
      }
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "Guide file '%s' contains duplicate guide '%s'\n",
        file->data,
        token.data);
      idLexer::SkipBracedSection(src, 1);
      v16 = -1;
      idStr::FreeData(&token);
      return 0;
    }
    else
    {
LABEL_10:
      v12 = (rvDeclGuide *)Memory::Allocate(0x2C4u);
      LOBYTE(v16) = 1;
      if ( v12 )
      {
        rvDeclGuide::rvDeclGuide(v12, &token);
        v14 = v13;
      }
      else
      {
        v14 = 0;
      }
      LOBYTE(v16) = 0;
      rvDeclGuide::Parse(v14, src);
      v16 = -1;
      idStr::FreeData(&token);
      return v14;
    }
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Guide file '%s' has unknown token '%s'\n",
      file->data,
      token.data);
    v16 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: virtual bool __thiscall idDeclManagerLocal::EvaluateGuide(class idStr &,class idLexer *,class idStr &)
char __thiscall idDeclManagerLocal::EvaluateGuide(
        idDeclManagerLocal *this,
        idStr *name,
        idLexer *src,
        idStr *definition)
{
  idDeclManagerLocal *v4; // edi
  char *data; // edx
  char v6; // cl
  char *v7; // ebp
  int v8; // esi
  char *v9; // eax
  unsigned int v10; // ebp
  idHashTable<rvDeclGuide *>::hashnode_s *v11; // esi
  int v12; // eax
  idToken guideName; // [esp+10h] [ebp-5Ch] BYREF
  int v16; // [esp+68h] [ebp-4h]

  guideName.floatvalue = 0.0;
  v4 = this;
  guideName.len = 0;
  guideName.alloced = 20;
  guideName.data = guideName.baseBuffer;
  guideName.baseBuffer[0] = 0;
  v16 = 0;
  idStr::operator=(definition, (char *)&entityFilter);
  idLexer::ReadToken(src, &guideName);
  data = guideName.data;
  v6 = *guideName.data;
  v7 = guideName.data;
  v8 = 0;
  v9 = guideName.data;
  if ( *guideName.data )
  {
    do
    {
      v10 = v6 * (_DWORD)&v9[119 - (unsigned int)guideName.data];
      v6 = *++v9;
      v8 += v10;
    }
    while ( v6 );
    v7 = guideName.data;
    v4 = this;
  }
  v11 = v4->guideTable.heads[v8 & v4->guideTable.tablesizemask];
  if ( v11 )
  {
    while ( 1 )
    {
      v12 = idStr::Cmp(v11->key.data, v7);
      if ( !v12 )
        break;
      if ( v12 <= 0 )
      {
        v11 = v11->next;
        if ( v11 )
          continue;
      }
      data = guideName.data;
      goto LABEL_9;
    }
    rvDeclGuide::Evaluate(v11->value, src, definition);
    v16 = -1;
    idStr::FreeData(&guideName);
    return 1;
  }
  else
  {
LABEL_9:
    idLexer::Warning(src, "Guide name '%s' not found in '%s'", data, name->data);
    idLexer::SkipRestOfLine(src);
    v16 = -1;
    idStr::FreeData(&guideName);
    return 0;
  }
}

// FUNC: public: virtual bool __thiscall idDeclManagerLocal::EvaluateInlineGuide(class idStr &,class idStr &)
char __thiscall idDeclManagerLocal::EvaluateInlineGuide(idDeclManagerLocal *this, idStr *name, idStr *definition)
{
  int len; // ebp
  int v4; // eax
  int v5; // ebp
  char *v6; // ecx
  char v7; // al
  int v8; // esi
  char *v9; // edi
  unsigned int v10; // ebp
  idHashTable<rvDeclGuide *>::hashnode_s *v11; // esi
  int v12; // eax
  idStr *v14; // esi
  unsigned int v15; // ebp
  int v16; // eax
  int v17; // esi
  int i; // eax
  char v19; // cl
  char *v20; // edx
  idStr *v21; // esi
  int v22; // edi
  int j; // eax
  char v24; // cl
  char *v25; // edx
  int v26; // ebp
  int v27; // ecx
  char *data; // [esp-8h] [ebp-1E8h]
  int defOffset; // [esp+10h] [ebp-1D0h]
  int length; // [esp+14h] [ebp-1CCh]
  int lengtha; // [esp+14h] [ebp-1CCh]
  idStr temp; // [esp+18h] [ebp-1C8h] BYREF
  idDeclManagerLocal *v33; // [esp+38h] [ebp-1A8h]
  idStr expanded; // [esp+3Ch] [ebp-1A4h] BYREF
  idStr store; // [esp+5Ch] [ebp-184h] BYREF
  idToken token; // [esp+7Ch] [ebp-164h] BYREF
  idLexer lexer; // [esp+CCh] [ebp-114h] BYREF
  idStr v38; // [esp+194h] [ebp-4Ch] BYREF
  idStr result; // [esp+1B4h] [ebp-2Ch] BYREF
  int v40; // [esp+1DCh] [ebp-4h]

  v33 = this;
  idLexer::idLexer(&lexer);
  token.floatvalue = 0.0;
  v40 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  expanded.len = 0;
  expanded.alloced = 20;
  expanded.data = expanded.baseBuffer;
  expanded.baseBuffer[0] = 0;
  temp.len = 0;
  temp.alloced = 20;
  temp.data = temp.baseBuffer;
  temp.baseBuffer[0] = 0;
  store.len = 0;
  store.alloced = 20;
  store.data = store.baseBuffer;
  store.baseBuffer[0] = 0;
  len = definition->len;
  v4 = definition->len + 1;
  LOBYTE(v40) = 4;
  if ( v4 > 20 )
    idStr::ReAllocate(&store, v4, 0);
  qmemcpy(store.data, definition->data, len);
  store.data[len] = 0;
  data = name->data;
  store.len = len;
  idLexer::LoadMemory(&lexer, store.data, len, data, 1);
  lexer.flags = 6300;
  defOffset = 0;
  while ( !idLexer::EndOfFile(&lexer) )
  {
    v5 = lexer.script_p - lexer.buffer;
    length = lexer.script_p - lexer.buffer;
    if ( !idLexer::ReadToken(&lexer, &token) )
      break;
    if ( !idStr::Icmp(token.data, "inlineGuide") )
    {
      idLexer::ReadToken(&lexer, &token);
      v6 = token.data;
      v7 = *token.data;
      v8 = 0;
      v9 = token.data;
      if ( *token.data )
      {
        do
        {
          v10 = v7 * (_DWORD)&v6[119 - (unsigned int)token.data];
          v7 = *++v6;
          v8 += v10;
        }
        while ( v7 );
        v5 = length;
      }
      v11 = v33->guideTable.heads[v8 & v33->guideTable.tablesizemask];
      if ( !v11 )
      {
LABEL_13:
        LOBYTE(v40) = 3;
        idStr::FreeData(&store);
        LOBYTE(v40) = 2;
        idStr::FreeData(&temp);
        LOBYTE(v40) = 1;
        idStr::FreeData(&expanded);
        LOBYTE(v40) = 0;
        idStr::FreeData(&token);
        v40 = -1;
        idLexer::~idLexer(&lexer);
        return 0;
      }
      while ( 1 )
      {
        v12 = idStr::Cmp(v11->key.data, v9);
        if ( !v12 )
          break;
        if ( v12 <= 0 )
        {
          v11 = v11->next;
          if ( v11 )
            continue;
        }
        goto LABEL_13;
      }
      rvDeclGuide::Evaluate(v11->value, &lexer, &expanded);
      lengtha = lexer.script_p - lexer.buffer - v5;
      v14 = idStr::Left(definition, &result, defOffset + v5);
      v15 = v14->len;
      v16 = v14->len + 1;
      LOBYTE(v40) = 5;
      if ( v16 > temp.alloced )
        idStr::ReAllocate(&temp, v16, 0);
      qmemcpy(temp.data, v14->data, v15);
      temp.data[v15] = 0;
      temp.len = v15;
      LOBYTE(v40) = 4;
      idStr::FreeData(&result);
      v17 = temp.len + expanded.len;
      if ( temp.len + expanded.len + 1 > temp.alloced )
        idStr::ReAllocate(&temp, temp.len + expanded.len + 1, 1);
      for ( i = 0; i < expanded.len; v20[temp.len] = v19 )
      {
        v19 = expanded.data[i];
        v20 = &temp.data[i++];
      }
      temp.len = v17;
      temp.data[v17] = 0;
      v21 = idStr::Right(definition, &v38, definition->len + lexer.buffer - lexer.script_p - defOffset);
      v22 = v21->len + temp.len;
      LOBYTE(v40) = 6;
      if ( v22 + 1 > temp.alloced )
        idStr::ReAllocate(&temp, v22 + 1, 1);
      for ( j = 0; j < v21->len; v25[temp.len] = v24 )
      {
        v24 = v21->data[j];
        v25 = &temp.data[j++];
      }
      temp.len = v22;
      temp.data[v22] = 0;
      LOBYTE(v40) = 4;
      idStr::FreeData(&v38);
      v26 = temp.len;
      if ( temp.len + 1 > definition->alloced )
        idStr::ReAllocate(definition, temp.len + 1, 0);
      qmemcpy(definition->data, temp.data, v26);
      definition->data[v26] = 0;
      v27 = expanded.len - lengtha;
      definition->len = v26;
      defOffset += v27;
    }
  }
  LOBYTE(v40) = 3;
  idStr::FreeData(&store);
  LOBYTE(v40) = 2;
  idStr::FreeData(&temp);
  LOBYTE(v40) = 1;
  idStr::FreeData(&expanded);
  LOBYTE(v40) = 0;
  idStr::FreeData(&token);
  v40 = -1;
  idLexer::~idLexer(&lexer);
  return 1;
}

// FUNC: void __cdecl WriteDeclFile_f(class idCmdArgs const &)
void __usercall WriteDeclFile_f(int a1@<ebx>)
{
  idDeclManagerLocal::WriteDeclFile(&declManagerLocal, a1);
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::Shutdown(void)
void __thiscall idDeclManagerLocal::Shutdown(idDeclManagerLocal *this)
{
  void **p_list; // edi
  int i; // ebp
  int v4; // esi
  int v5; // ecx
  void (__thiscall ***v6)(_DWORD, int); // ecx
  bool v7; // zf
  int j; // esi
  idDeclFile **list; // eax
  idDeclFile *v10; // edi
  int k; // esi
  idDeclType **v12; // edx
  idDeclType *v13; // edi
  int m; // esi
  idDeclFolder **v15; // ecx
  idDeclFolder *v16; // edi
  huffmanNode_s *v17; // eax
  huffmanNode_s **v18; // esi
  idHashIndex *v19; // [esp+8h] [ebp-10h]
  int v20; // [esp+Ch] [ebp-Ch]

  p_list = (void **)&this->linearLists[0].list;
  while ( 1 )
  {
    for ( i = 0; i < (int)*(p_list - 3); ++i )
    {
      v4 = *((_DWORD *)*p_list + i);
      v5 = *(_DWORD *)(v4 + 4);
      if ( v5 )
      {
        (*(void (__thiscall **)(int))(*(_DWORD *)v5 + 16))(v5);
        v6 = *(void (__thiscall ****)(_DWORD, int))(v4 + 4);
        if ( v6 )
          (**v6)(v6, 1);
      }
      if ( *(_DWORD *)(v4 + 40) )
      {
        Mem_Free(*(void **)(v4 + 40));
        *(_DWORD *)(v4 + 40) = 0;
      }
      (**(void (__thiscall ***)(int, int))v4)(v4, 1);
    }
    if ( *p_list )
      Memory::Free(*p_list);
    *p_list = 0;
    *(p_list - 3) = 0;
    *(p_list - 2) = 0;
    idHashIndex::Free(v19);
    p_list += 4;
    v7 = v20-- == 1;
    ++v19;
    if ( v7 )
    {
      for ( j = 0; j < this->loadedFiles.num; ++j )
      {
        list = this->loadedFiles.list;
        v10 = list[j];
        if ( v10 )
        {
          idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s((idPoolStr *)list[j]);
          Memory::Free(v10);
        }
        this->loadedFiles.list[j] = 0;
      }
      if ( this->loadedFiles.list )
        Memory::Free(this->loadedFiles.list);
      this->loadedFiles.list = 0;
      this->loadedFiles.num = 0;
      this->loadedFiles.size = 0;
      for ( k = 0; k < this->declTypes.num; ++k )
      {
        v12 = this->declTypes.list;
        v13 = v12[k];
        if ( v13 )
        {
          idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s((idPoolStr *)v12[k]);
          Memory::Free(v13);
        }
        this->declTypes.list[k] = 0;
      }
      if ( this->declTypes.list )
        Memory::Free(this->declTypes.list);
      this->declTypes.list = 0;
      this->declTypes.num = 0;
      this->declTypes.size = 0;
      for ( m = 0; m < this->declFolders.num; ++m )
      {
        v15 = this->declFolders.list;
        v16 = v15[m];
        if ( v16 )
        {
          idDeclFolder::~idDeclFolder(v15[m]);
          Memory::Free(v16);
        }
        this->declFolders.list[m] = 0;
      }
      if ( this->declFolders.list )
        Memory::Free(this->declFolders.list);
      v17 = huffmanTree;
      this->declFolders.list = 0;
      this->declFolders.num = 0;
      this->declFolders.size = 0;
      if ( v17 )
      {
        v18 = (huffmanNode_s **)v17;
        if ( v17->symbol == -1 )
        {
          FreeHuffmanTree_r(v17->children[0]);
          FreeHuffmanTree_r(v18[4]);
        }
        Memory::Free(v18);
      }
      __asm { jmp     dword ptr [edx+7Ch] }
    }
  }
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::Reload(bool)
void __thiscall idDeclManagerLocal::Reload(idDeclManagerLocal *this, bool force)
{
  int num; // eax
  int v4; // esi
  int v5; // ebx
  int v6; // ebp
  char *v7; // eax
  idDeclFile *v8; // esi
  int v9; // [esp+10h] [ebp-4h] BYREF

  num = this->loadedFiles.num;
  v4 = 0;
  if ( num > 0 )
  {
    do
    {
      v5 = **(_DWORD **)common.ip;
      v6 = v4 + 1;
      v7 = va("%d/%d: %s\n", v4 + 1, num, this->loadedFiles.list[v4]->fileName.data);
      (*(void (__thiscall **)(_DWORD, char *))(v5 + 40))(*(_DWORD *)common.ip, v7);
      v8 = this->loadedFiles.list[v4];
      if ( force
        || !v8->timestamp
        || (fileSystem->ReadFile(fileSystem, v8->fileName.data, 0, (unsigned int *)&v9), v9 != v8->timestamp) )
      {
        idDeclFile::LoadAndParse(v8, 0);
      }
      num = this->loadedFiles.num;
      v4 = v6;
    }
    while ( v6 < num );
  }
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::ReloadFile(char const *,bool)
void __thiscall idDeclManagerLocal::ReloadFile(idDeclManagerLocal *this, const char *filename, int force)
{
  int v4; // ebp
  char v5; // bl
  idDeclFile **list; // eax
  idDeclFile *v7; // edi

  v4 = 0;
  if ( this->loadedFiles.num > 0 )
  {
    v5 = force;
    do
    {
      if ( !idStr::Icmp(this->loadedFiles.list[v4]->fileName.data, filename) )
      {
        list = this->loadedFiles.list;
        this->checksum ^= list[v4]->checksum;
        v7 = list[v4];
        if ( v5
          || !v7->timestamp
          || (fileSystem->ReadFile(fileSystem, v7->fileName.data, 0, (unsigned int *)&force), force != v7->timestamp) )
        {
          idDeclFile::LoadAndParse(v7, 0);
        }
        this->checksum ^= this->loadedFiles.list[v4]->checksum;
      }
      ++v4;
    }
    while ( v4 < this->loadedFiles.num );
  }
}

// FUNC: public: virtual void __thiscall idDeclLocal::Reload(void)
void __thiscall idDeclLocal::Reload(idDeclLocal *this)
{
  idDeclFile *sourceFile; // esi
  int v2; // [esp+Ch] [ebp-4h] BYREF

  sourceFile = this->sourceFile;
  if ( !sourceFile->timestamp
    || (fileSystem->ReadFile(fileSystem, sourceFile->fileName.data, 0, (unsigned int *)&v2), v2 != sourceFile->timestamp) )
  {
    idDeclFile::LoadAndParse(sourceFile, 0);
  }
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::ParseGuides(void)
void __thiscall idDeclManagerLocal::ParseGuides(idDeclManagerLocal *this)
{
  int v2; // ecx
  int v3; // eax
  idHashTable<rvDeclGuide *>::hashnode_s *v4; // esi
  idStr *p_key; // edi
  rvDeclGuide *value; // ebp
  idFileList *v7; // eax
  idFileList *v8; // edi
  idStr *list; // eax
  char *data; // esi
  unsigned int v11; // eax
  int v12; // edi
  int v13; // eax
  char v14; // cl
  int k; // eax
  char *v16; // edx
  rvDeclGuide *NewGuide; // eax
  const char *v18; // ebp
  char v19; // al
  int v20; // edx
  const char *m; // ecx
  int v22; // edi
  idHashTable<rvDeclGuide *>::hashnode_s **heads; // edi
  int v24; // eax
  idHashTable<rvDeclGuide *>::hashnode_s *v25; // esi
  idHashTable<rvDeclGuide *>::hashnode_s **p_next; // edi
  int v27; // eax
  idHashTable<rvDeclGuide *>::hashnode_s *v28; // eax
  int v29; // edx
  idHashTable<rvDeclGuide *>::hashnode_s *v30; // eax
  rvDeclGuide *v31; // eax
  rvDeclGuide *v32; // esi
  char v33; // al
  int v34; // edx
  const char *n; // ecx
  int v36; // edi
  idHashTable<rvDeclGuide *>::hashnode_s **v37; // edi
  int v38; // eax
  int v39; // eax
  int j; // [esp+14h] [ebp-15Ch]
  int v41; // [esp+14h] [ebp-15Ch]
  rvDeclGuide *newDeclGuide; // [esp+18h] [ebp-158h]
  int v43; // [esp+1Ch] [ebp-154h]
  int v44; // [esp+1Ch] [ebp-154h]
  idFileList *guideFiles; // [esp+20h] [ebp-150h]
  int i; // [esp+24h] [ebp-14Ch]
  idStr file; // [esp+28h] [ebp-148h] BYREF
  idHashTable<rvDeclGuide *>::hashnode_s *v48; // [esp+48h] [ebp-128h]
  idToken token; // [esp+4Ch] [ebp-124h] BYREF
  idLexer src; // [esp+9Ch] [ebp-D4h] BYREF
  int v51; // [esp+16Ch] [ebp-4h]

  idLexer::idLexer(&src);
  v51 = 0;
  file.len = 0;
  file.alloced = 20;
  file.data = file.baseBuffer;
  file.baseBuffer[0] = 0;
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v2 = *(_DWORD *)common.type;
  LOBYTE(v51) = 2;
  (*(void (__cdecl **)(netadrtype_t, const char *))(v2 + 124))(common.type, "Loading guides.... ");
  v3 = 0;
  for ( j = 0; v3 < this->guideTable.tablesize; j = v3 )
  {
    v4 = this->guideTable.heads[v3];
    if ( v4 )
    {
      do
      {
        p_key = &v4->key;
        value = v4->value;
        v4 = v4->next;
        if ( value )
        {
          rvDeclGuide::~rvDeclGuide(value);
          Memory::Free(value);
        }
        idStr::FreeData(p_key);
        Memory::Free(p_key);
      }
      while ( v4 );
      v3 = j;
    }
    this->guideTable.heads[v3++] = 0;
  }
  this->guideTable.numentries = 0;
  v7 = fileSystem->ListFiles(fileSystem, "guides", ".guide", 1, 0, 0);
  v8 = v7;
  guideFiles = v7;
  if ( v7->list.num )
  {
    src.flags = 152;
    i = 0;
    if ( v7->list.num <= 0 )
      goto LABEL_46;
    v41 = 0;
    while ( 1 )
    {
      idStr::operator=(&file, "guides/");
      list = v8->list.list;
      data = list[v41].data;
      if ( data )
      {
        v11 = (unsigned int)&list[v41].data[strlen(list[v41].data) + 1];
        v12 = v11 - (_DWORD)(data + 1) + file.len;
        v13 = v11 - (_DWORD)data + file.len;
        if ( v13 > file.alloced )
          idStr::ReAllocate(&file, v13, 1);
        v14 = *data;
        for ( k = 0; v14; v14 = data[k] )
        {
          v16 = &file.data[k++];
          v16[file.len] = v14;
        }
        file.len = v12;
        file.data[v12] = 0;
        v8 = guideFiles;
      }
      if ( !idLexer::LoadFile(&src, file.data, 0) )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "Couldn't load %s",
          file.data);
        break;
      }
      if ( !idLexer::ReadToken(&src, &token) )
        goto LABEL_45;
      do
      {
        if ( !idStr::Icmp(token.data, "guide") )
        {
          NewGuide = idDeclManagerLocal::GetNewGuide(this, &src, &file);
          newDeclGuide = NewGuide;
          if ( !NewGuide )
            continue;
          v18 = NewGuide->mName.data;
          v19 = *v18;
          v20 = 0;
          for ( m = v18; v19; v20 += v22 )
          {
            v22 = v19 * (_DWORD)&m[119 - (_DWORD)v18];
            v19 = *++m;
          }
          heads = this->guideTable.heads;
          v24 = v20 & this->guideTable.tablesizemask;
          v25 = heads[v24];
          p_next = &heads[v24];
          v43 = v24 * 4;
          if ( v25 )
          {
            while ( 1 )
            {
              v27 = idStr::Cmp(v25->key.data, v18);
              if ( !v27 )
                break;
              if ( v27 <= 0 )
              {
                p_next = &v25->next;
                v25 = v25->next;
                if ( v25 )
                  continue;
              }
              goto LABEL_27;
            }
LABEL_30:
            v25->value = newDeclGuide;
            continue;
          }
LABEL_27:
          ++this->guideTable.numentries;
          v28 = (idHashTable<rvDeclGuide *>::hashnode_s *)Memory::Allocate(0x28u);
          v48 = v28;
          LOBYTE(v51) = 3;
          if ( v28 )
          {
            v29 = v43;
            goto LABEL_29;
          }
          goto LABEL_41;
        }
        if ( !idStr::Icmp(token.data, "inlineGuide") )
        {
          v31 = idDeclManagerLocal::GetNewGuide(this, &src, &file);
          v32 = v31;
          newDeclGuide = v31;
          if ( v31 )
          {
            rvDeclGuide::RemoveOuterBracing(v31);
            v18 = v32->mName.data;
            v33 = *v18;
            v34 = 0;
            for ( n = v18; v33; v34 += v36 )
            {
              v36 = v33 * (_DWORD)&n[119 - (_DWORD)v18];
              v33 = *++n;
            }
            v37 = this->guideTable.heads;
            v38 = v34 & this->guideTable.tablesizemask;
            v25 = v37[v38];
            p_next = &v37[v38];
            v44 = v38 * 4;
            if ( v25 )
            {
              while ( 1 )
              {
                v39 = idStr::Cmp(v25->key.data, v18);
                if ( !v39 )
                  goto LABEL_30;
                if ( v39 <= 0 )
                {
                  p_next = &v25->next;
                  v25 = v25->next;
                  if ( v25 )
                    continue;
                }
                break;
              }
            }
            ++this->guideTable.numentries;
            v28 = (idHashTable<rvDeclGuide *>::hashnode_s *)Memory::Allocate(0x28u);
            v48 = v28;
            LOBYTE(v51) = 4;
            if ( v28 )
            {
              v29 = v44;
LABEL_29:
              idHashTable<maTransform_s *>::hashnode_s::hashnode_s(
                v28,
                v18,
                newDeclGuide,
                *(idHashTable<rvDeclGuide *>::hashnode_s **)((char *)this->guideTable.heads + v29));
LABEL_42:
              *p_next = v30;
              LOBYTE(v51) = 2;
              v30->next = v25;
              continue;
            }
LABEL_41:
            v30 = 0;
            goto LABEL_42;
          }
        }
      }
      while ( idLexer::ReadToken(&src, &token) );
      v8 = guideFiles;
LABEL_45:
      idLexer::FreeSource(&src);
      ++v41;
      if ( ++i >= v8->list.num )
      {
LABEL_46:
        fileSystem->FreeFileList(fileSystem, v8);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "%d loaded\n",
          this->guideTable.numentries);
        break;
      }
    }
  }
  LOBYTE(v51) = 1;
  idStr::FreeData(&token);
  LOBYTE(v51) = 0;
  idStr::FreeData(&file);
  v51 = -1;
  idLexer::~idLexer(&src);
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::ShutdownGuides(void)
void __thiscall idDeclManagerLocal::ShutdownGuides(idDeclManagerLocal *this)
{
  int v1; // eax
  idHashTable<rvDeclGuide *>::hashnode_s *v3; // esi
  idPoolStr *v4; // edi
  rvDeclGuide *value; // ebp
  int v6; // ebp
  idHashTable<rvDeclGuide *>::hashnode_s *v7; // esi
  idPoolStr *v8; // edi
  int i; // [esp+10h] [ebp-4h]

  v1 = 0;
  for ( i = 0; v1 < this->guideTable.tablesize; i = v1 )
  {
    v3 = this->guideTable.heads[v1];
    if ( v3 )
    {
      do
      {
        v4 = (idPoolStr *)v3;
        value = v3->value;
        v3 = v3->next;
        if ( value )
        {
          rvDeclGuide::~rvDeclGuide(value);
          Memory::Free(value);
        }
        idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s(v4);
        Memory::Free(v4);
      }
      while ( v3 );
      v1 = i;
    }
    this->guideTable.heads[v1++] = 0;
  }
  v6 = 0;
  for ( this->guideTable.numentries = 0; v6 < this->guideTable.tablesize; ++v6 )
  {
    v7 = this->guideTable.heads[v6];
    while ( v7 )
    {
      v8 = (idPoolStr *)v7;
      v7 = v7->next;
      idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s(v8);
      Memory::Free(v8);
    }
    this->guideTable.heads[v6] = 0;
  }
  this->guideTable.numentries = 0;
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::SetInsideLoad(bool)
void __thiscall idDeclManagerLocal::SetInsideLoad(idDeclManagerLocal *this, bool var)
{
  this->insideLevelLoad = var;
}

// FUNC: public: virtual bool __thiscall idDeclManagerLocal::GetInsideLoad(void)
bool __thiscall idDeclManagerLocal::GetInsideLoad(idDeclManagerLocal *this)
{
  return this->insideLevelLoad;
}

// FUNC: private: static void __cdecl idDeclManagerLocal::ReloadDecls_f(class idCmdArgs const &)
void __cdecl idDeclManagerLocal::ReloadDecls_f(const idCmdArgs *args)
{
  const char *v1; // eax
  bool argsa; // [esp+8h] [ebp+4h]

  fileSystem->SetIsFileLoadingAllowed(fileSystem, 1);
  idDeclManagerLocal::ParseGuides(&declManagerLocal);
  if ( args->argc <= 1 )
    v1 = &entityFilter;
  else
    v1 = args->argv[1];
  if ( idStr::Icmp(v1, "all") )
  {
    argsa = 0;
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "reloading changed decl files:\n");
  }
  else
  {
    argsa = 1;
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "reloading all decl files:\n");
  }
  soundSystem->SetMute(soundSystem, 1);
  idDeclManagerLocal::Reload(&declManagerLocal, argsa);
  soundSystem->SetMute(soundSystem, 0);
  fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
}

// FUNC: private: static void __cdecl idDeclManagerLocal::ReloadFile_f(class idCmdArgs const &)
void __cdecl idDeclManagerLocal::ReloadFile_f(const idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // eax

  fileSystem->SetIsFileLoadingAllowed(fileSystem, 1);
  idDeclManagerLocal::ParseGuides(&declManagerLocal);
  if ( args->argc <= 1 )
    goto LABEL_5;
  if ( !args->argv[1] )
  {
LABEL_11:
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: \n  reloadFile <fileName>\n");
    return;
  }
  if ( args->argc <= 1 )
LABEL_5:
    v1 = &entityFilter;
  else
    v1 = args->argv[1];
  if ( !strlen(v1) )
    goto LABEL_11;
  soundSystem->SetMute(soundSystem, 1);
  if ( args->argc <= 1 )
    v2 = &entityFilter;
  else
    v2 = args->argv[1];
  idDeclManagerLocal::ReloadFile(&declManagerLocal, v2, 1);
  soundSystem->SetMute(soundSystem, 0);
  fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
}

// FUNC: public: virtual void __thiscall idDeclManagerLocal::Init(void)
void __thiscall idDeclManagerLocal::Init(idDeclManagerLocal *this)
{
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "------------ Initializing Decls -------------\n");
  this->checksum = 0;
  SetupHuffman();
  this->ParseGuides(this);
  this->RegisterDeclType(this, "table", DECL_TABLE, idDeclAllocator<idDeclTable>);
  this->RegisterDeclType(this, "material", DECL_MATERIAL, idDeclAllocator<idMaterial>);
  this->RegisterDeclType(this, "skin", DECL_SKIN, idDeclAllocator<idDeclSkin>);
  this->RegisterDeclType(this, "sound", DECL_SOUND, idDeclAllocator<idSoundShader>);
  this->RegisterDeclType(this, "entityDef", DECL_ENTITYDEF, idDeclAllocator<idDeclEntityDef>);
  this->RegisterDeclType(this, "mapDef", DECL_MAPDEF, idDeclAllocator<idDeclEntityDef>);
  this->RegisterDeclType(this, "materialType", DECL_MATERIALTYPE, idDeclAllocator<rvDeclMatType>);
  this->RegisterDeclType(this, "lipSync", DECL_LIPSYNC, idDeclAllocator<rvDeclLipSync>);
  this->RegisterDeclType(this, "playback", DECL_PLAYBACK, idDeclAllocator<rvDeclPlayback>);
  this->RegisterDeclType(this, "effect", DECL_EFFECT, idDeclAllocator<rvDeclEffect>);
  this->RegisterDeclType(this, "articulatedFigure", DECL_AF, idDeclAllocator<idDeclAF>);
  this->RegisterDeclType(this, "pda", DECL_PDA, idDeclAllocator<idDeclPDA>);
  this->RegisterDeclType(this, "email", DECL_EMAIL, idDeclAllocator<idDeclEmail>);
  this->RegisterDeclType(this, "video", DECL_VIDEO, idDeclAllocator<idDeclVideo>);
  this->RegisterDeclType(this, "audio", DECL_AUDIO, idDeclAllocator<idDeclAudio>);
  if ( cvarSystem->GetCVarBool(cvarSystem, "com_SingleDeclFile") )
  {
    this->StartLoadingDecls(this);
    this->LoadDeclsFromFile(this);
    cmdSystem->AddCommand(cmdSystem, "flushDecls", FlushDecls_f, 2, "deallocates all current decls", 0);
    cmdSystem->AddCommand(
      cmdSystem,
      "checkDecls",
      CheckDecls_f,
      2,
      "checks to make sure decls that are loaded have no textSource",
      0);
  }
  else
  {
    cmdSystem->AddCommand(
      cmdSystem,
      "writeDeclFile",
      WriteDeclFile_f,
      2,
      "writes all currently parsed decls to a file",
      0);
    this->RegisterDeclFolderWrapper(this, "materials", ".mtr", DECL_MATERIAL, 0, 0);
    this->RegisterDeclFolderWrapper(this, "skins", ".skin", DECL_SKIN, 0, 0);
    this->RegisterDeclFolderWrapper(this, "sound", ".sndshd", DECL_SOUND, 0, 1);
    this->RegisterDeclFolderWrapper(this, "materials/types", ".mtt", DECL_MATERIALTYPE, 0, 0);
    this->RegisterDeclFolderWrapper(this, "lipsync", ".lipsync", DECL_LIPSYNC, 0, 0);
    this->RegisterDeclFolderWrapper(this, "playbacks", ".playback", DECL_PLAYBACK, 1, 0);
    this->RegisterDeclFolderWrapper(this, "effects", ".fx", DECL_EFFECT, 1, 0);
  }
  cmdSystem->AddCommand(cmdSystem, "listDecls", idDeclManagerLocal::ListDecls_f, 2, "lists all decls", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "listAllDecls",
    idDeclManagerLocal::ListAllDecls_f,
    2,
    "lists every single decl, not just the summary",
    0);
  cmdSystem->AddCommand(cmdSystem, "reloadDecls", idDeclManagerLocal::ReloadDecls_f, 2, "reloads decls", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "reloadFile",
    idDeclManagerLocal::ReloadFile_f,
    2,
    "reloads a single specific decl file",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "resaveDecl",
    idDeclManagerLocal::ResaveDecl_f,
    2,
    "resaves a decl or every decl of a certain type",
    0);
  cmdSystem->AddCommand(cmdSystem, "touch", idDeclManagerLocal::TouchDecl_f, 2, "touches a decl", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "listTables",
    idListDecls_f<0>,
    2,
    "lists tables",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listMaterials",
    idListDecls_f<1>,
    2,
    "lists materials",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listSkins",
    idListDecls_f<2>,
    2,
    "lists skins",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listSoundShaders",
    idListDecls_f<3>,
    2,
    "lists sound shaders",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listEntityDefs",
    idListDecls_f<4>,
    2,
    "lists entity defs",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listAF",
    idListDecls_f<11>,
    2,
    "lists articulated figures",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listPDAs",
    idListDecls_f<12>,
    2,
    "lists PDAs",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listEmails",
    idListDecls_f<15>,
    2,
    "lists Emails",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listVideos",
    idListDecls_f<13>,
    2,
    "lists Videos",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listAudios",
    idListDecls_f<14>,
    2,
    "lists Audios",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listMaterialTypes",
    idListDecls_f<6>,
    2,
    "lists material types",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listLipsyncs",
    idListDecls_f<7>,
    2,
    "lists lip sync decls",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listPlaybacks",
    idListDecls_f<8>,
    2,
    "lists playback decls",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listEffects",
    idListDecls_f<9>,
    2,
    "lists effect decls",
    idCmdSystem::ArgCompletion_String<&char const * * listDeclStrings>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printTable",
    idPrintDecls_f<0>,
    2,
    "prints a table",
    idCmdSystem::ArgCompletion_Decl<0>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printMaterial",
    idPrintDecls_f<1>,
    2,
    "prints a material",
    idCmdSystem::ArgCompletion_Decl<1>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printSkin",
    idPrintDecls_f<2>,
    2,
    "prints a skin",
    idCmdSystem::ArgCompletion_Decl<2>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printSoundShader",
    idPrintDecls_f<3>,
    2,
    "prints a sound shader",
    idCmdSystem::ArgCompletion_Decl<3>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printEntityDef",
    idPrintDecls_f<4>,
    2,
    "prints an entity def",
    idCmdSystem::ArgCompletion_Decl<4>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printAF",
    idPrintDecls_f<11>,
    2,
    "prints an articulated figure",
    idCmdSystem::ArgCompletion_Decl<11>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printPDA",
    idPrintDecls_f<12>,
    2,
    "prints an PDA",
    idCmdSystem::ArgCompletion_Decl<12>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printEmail",
    idPrintDecls_f<15>,
    2,
    "prints an Email",
    idCmdSystem::ArgCompletion_Decl<15>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printVideo",
    idPrintDecls_f<13>,
    2,
    "prints a Audio",
    idCmdSystem::ArgCompletion_Decl<13>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printAudio",
    idPrintDecls_f<14>,
    2,
    "prints an Video",
    idCmdSystem::ArgCompletion_Decl<14>);
  cmdSystem->AddCommand(
    cmdSystem,
    "listHuffmanFrequencies",
    ListHuffmanFrequencies_f,
    2,
    "lists decl text character frequencies",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "printMaterialTypes",
    idPrintDecls_f<6>,
    2,
    "prints material types",
    idCmdSystem::ArgCompletion_Decl<6>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printLipsyncs",
    idPrintDecls_f<7>,
    2,
    "prints lip syncs",
    idCmdSystem::ArgCompletion_Decl<7>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printPlaybacks",
    idPrintDecls_f<8>,
    2,
    "prints playbacks",
    idCmdSystem::ArgCompletion_Decl<8>);
  cmdSystem->AddCommand(
    cmdSystem,
    "printEffects",
    idPrintDecls_f<9>,
    2,
    "prints effects",
    idCmdSystem::ArgCompletion_Decl<9>);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
}
