
// FUNC: protected: void __thiscall rvIndexBuffer::CreateIndexStorage(void)
void __thiscall rvIndexBuffer::CreateIndexStorage(rvIndexBuffer *this)
{
  unsigned __int8 *v2; // eax
  unsigned int m_ibID; // edi
  unsigned int v4; // eax
  int v5; // esi

  if ( (this->m_flags & 1) == 0
    || ((this->m_flags & 4) == 0
      ? (v2 = (unsigned __int8 *)Mem_Alloc16(4 * this->m_numIndices, 0x11u))
      : (v2 = (unsigned __int8 *)Mem_Alloc16(2 * this->m_numIndices, 0x11u)),
        (this->m_systemMemStorage = v2) != 0) )
  {
    if ( (this->m_flags & 2) != 0 )
    {
      qglGenBuffersARB(1, &this->m_ibID);
      m_ibID = this->m_ibID;
      if ( m_ibID )
      {
        if ( (this->m_flags & 8) == 0 )
        {
          qglBindBufferARB(0x8893u, m_ibID);
          v4 = this->m_flags >> 2;
          v5 = 2 * this->m_numIndices;
          if ( (v4 & 1) == 0 )
            v5 *= 2;
          qglBufferDataARB(0x8893u, v5, 0, 0x88E4u);
          if ( qglGetError() )
            idLib::common->FatalError(idLib::common, "Unable to allocate index storage");
          qglBindBufferARB(0x8893u, 0);
        }
      }
      else
      {
        idLib::common->FatalError(idLib::common, "rvIndexBuffer: Unable to gen index buffer id");
      }
    }
  }
  else
  {
    idLib::common->FatalError(idLib::common, "Ran out of memory trying to allocate system memory index storage");
  }
}

// FUNC: public: __thiscall rvIndexBuffer::rvIndexBuffer(void)
void __thiscall rvIndexBuffer::rvIndexBuffer(rvIndexBuffer *this)
{
  this->m_flags = 0;
  this->m_lockStatus = 0;
  this->m_numIndices = 0;
  this->m_ibID = 0;
  this->m_lockIndexOffset = 0;
  this->m_lockIndexCount = 0;
  this->m_lockedBase = 0;
  this->m_systemMemStorage = 0;
  this->m_numIndicesWritten = 0;
}

// FUNC: public: bool __thiscall rvIndexBuffer::Lock(int,int,unsigned int,void * &)
char __thiscall rvIndexBuffer::Lock(
        rvIndexBuffer *this,
        int indexOffset,
        int numIndicesToLock,
        unsigned int lockFlags,
        void **indexPtr)
{
  int v5; // eax
  unsigned int v7; // edi
  int v8; // eax
  int v9; // ebp
  unsigned int v10; // ebx
  unsigned __int8 *v11; // ecx
  unsigned int v13; // eax
  unsigned __int8 *v14; // eax
  int v15; // [esp-Ch] [ebp-1Ch]

  v5 = numIndicesToLock;
  v7 = 35000;
  this->m_lockIndexOffset = indexOffset;
  if ( !numIndicesToLock )
    v5 = this->m_numIndices - indexOffset;
  this->m_lockIndexCount = v5;
  v8 = -((this->m_flags & 4) != 0);
  LOBYTE(v8) = v8 & 0xFE;
  v9 = v8 + 4;
  if ( (this->m_flags & 1) != 0 )
  {
    v10 = lockFlags;
    this->m_lockedBase = this->m_systemMemStorage;
LABEL_5:
    v11 = &this->m_lockedBase[v9 * this->m_lockIndexOffset];
    this->m_lockStatus = v10;
    *indexPtr = v11;
    return 1;
  }
  qglBindBufferARB(0x8893u, this->m_ibID);
  v10 = lockFlags;
  if ( (lockFlags & 1) != 0 )
  {
    v7 = lockFlags & 2 | 0x88B8;
  }
  else if ( (lockFlags & 2) != 0 )
  {
    v7 = 35001;
    if ( (this->m_flags & 8) != 0 )
    {
      v10 = lockFlags | 4;
      v13 = 35040;
    }
    else
    {
      v13 = 35044;
    }
    if ( (v10 & 4) != 0 )
    {
      v15 = v9 * this->m_lockIndexCount;
      this->m_lockIndexOffset = 0;
      qglBufferDataARB(0x8893u, v15, 0, v13);
    }
  }
  v14 = (unsigned __int8 *)qglMapBufferARB(0x8893u, v7);
  this->m_lockedBase = v14;
  if ( v14 )
    goto LABEL_5;
  return 0;
}

// FUNC: public: void __thiscall rvIndexBuffer::Unlock(void)
void __thiscall rvIndexBuffer::Unlock(rvIndexBuffer *this)
{
  unsigned int m_lockStatus; // eax
  int v3; // ecx
  unsigned int m_flags; // eax
  int v5; // ebx
  int v6; // edi

  m_lockStatus = this->m_lockStatus;
  v3 = m_lockStatus & 2;
  if ( (m_lockStatus & 2) != 0 )
  {
    if ( (m_lockStatus & 4) != 0 )
      this->m_numIndicesWritten = this->m_lockIndexCount;
    else
      this->m_numIndicesWritten += this->m_lockIndexCount;
  }
  m_flags = this->m_flags;
  v5 = (this->m_flags & 4) != 0 ? 2 : 4;
  if ( (this->m_flags & 1) != 0 )
  {
    if ( v3 && (m_flags & 2) != 0 )
    {
      v6 = v5 * this->m_lockIndexOffset;
      qglBindBufferARB(0x8893u, this->m_ibID);
      qglBufferSubDataARB(0x8893u, v6, v5 * this->m_lockIndexCount, &this->m_systemMemStorage[v6]);
      qglBindBufferARB(0x8893u, 0);
      this->m_lockStatus = 0;
      this->m_lockIndexOffset = 0;
      this->m_lockIndexCount = 0;
      this->m_lockedBase = 0;
      return;
    }
  }
  else if ( (m_flags & 2) != 0 )
  {
    qglBindBufferARB(0x8893u, this->m_ibID);
    qglUnmapBufferARB(0x8893u);
    qglBindBufferARB(0x8893u, 0);
  }
  this->m_lockStatus = 0;
  this->m_lockIndexOffset = 0;
  this->m_lockIndexCount = 0;
  this->m_lockedBase = 0;
}

// FUNC: public: void __thiscall rvIndexBuffer::CopyRemappedData(int,int,unsigned int *,int *,unsigned int)
void __thiscall rvIndexBuffer::CopyRemappedData(
        rvIndexBuffer *this,
        unsigned int indexBufferOffset,
        void *numIndices,
        unsigned int *indexMapping,
        int *indices,
        unsigned int indexBase)
{
  void *v6; // esi
  _WORD *v8; // eax
  unsigned int v9; // edx
  __int16 v10; // si
  unsigned int *v11; // edi
  int *v12; // ecx
  unsigned int v13; // edx
  unsigned int v14; // esi
  unsigned int *v15; // edi
  int *v16; // ecx

  v6 = numIndices;
  if ( (int)((int)numIndices + indexBufferOffset) <= this->m_numIndices )
  {
    rvIndexBuffer::Lock(this, indexBufferOffset, (int)numIndices, 2u, (void **)&indexBufferOffset);
    v8 = (_WORD *)indexBufferOffset;
    if ( (this->m_flags & 4) != 0 )
    {
      v9 = indexBufferOffset + 2 * (_DWORD)v6;
      if ( indexBufferOffset < v9 )
      {
        v10 = indexBase;
        v11 = indexMapping;
        v12 = indices;
        do
          *v8++ = v10 + LOWORD(v11[*v12++]);
        while ( (unsigned int)v8 < v9 );
      }
    }
    else
    {
      v13 = indexBufferOffset + 4 * (_DWORD)v6;
      if ( indexBufferOffset < v13 )
      {
        v14 = indexBase;
        v15 = indexMapping;
        v16 = indices;
        do
        {
          *(_DWORD *)v8 = v14 + v15[*v16];
          v8 += 2;
          ++v16;
        }
        while ( (unsigned int)v8 < v13 );
      }
    }
    rvIndexBuffer::Unlock(this);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "rvIndexBuffer: attempt to copy index data out-of-bounds");
  }
}

// FUNC: public: void __thiscall rvIndexBuffer::CopyData(int,int,int *,unsigned int)
void __thiscall rvIndexBuffer::CopyData(
        rvIndexBuffer *this,
        unsigned int indexBufferOffset,
        void *numIndices,
        int *indices,
        unsigned int indexBase)
{
  void *v5; // esi
  _WORD *v7; // eax
  unsigned int v8; // edx
  __int16 v9; // si
  int *v10; // ecx
  unsigned int v11; // edx
  unsigned int v12; // esi
  int *v13; // ecx

  v5 = numIndices;
  if ( (int)((int)numIndices + indexBufferOffset) <= this->m_numIndices )
  {
    rvIndexBuffer::Lock(this, indexBufferOffset, (int)numIndices, 2u, (void **)&indexBufferOffset);
    v7 = (_WORD *)indexBufferOffset;
    if ( (this->m_flags & 4) != 0 )
    {
      v8 = indexBufferOffset + 2 * (_DWORD)v5;
      if ( indexBufferOffset < v8 )
      {
        v9 = indexBase;
        v10 = indices;
        do
          *v7++ = v9 + *(_WORD *)v10++;
        while ( (unsigned int)v7 < v8 );
      }
    }
    else
    {
      v11 = indexBufferOffset + 4 * (_DWORD)v5;
      if ( indexBufferOffset < v11 )
      {
        v12 = indexBase;
        v13 = indices;
        do
        {
          *(_DWORD *)v7 = v12 + *v13;
          v7 += 2;
          ++v13;
        }
        while ( (unsigned int)v7 < v11 );
      }
    }
    rvIndexBuffer::Unlock(this);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "rvIndexBuffer: attempt to copy index data out-of-bounds");
  }
}

// FUNC: public: void __thiscall rvIndexBuffer::Write(class idFile &,char const *)
void __thiscall rvIndexBuffer::Write(rvIndexBuffer *this, idFile *outFile, const char *prepend)
{
  int v4; // eax
  void *v5; // esp
  int v7; // eax
  char *v8; // eax
  bool v9; // zf
  int v10; // edx
  char *v11; // eax
  char v12[12]; // [esp+0h] [ebp-18h] BYREF
  char *v13; // [esp+Ch] [ebp-Ch]
  void *indexBasePtr; // [esp+10h] [ebp-8h] BYREF
  int prependLen; // [esp+14h] [ebp-4h]
  int curIndex; // [esp+20h] [ebp+8h]

  prependLen = strlen(prepend);
  v4 = prependLen + 6;
  LOBYTE(v4) = (prependLen + 6) & 0xFC;
  v5 = alloca(v4);
  outFile->WriteFloatString(outFile, "%sIndexBuffer\n", prepend);
  outFile->WriteFloatString(outFile, "%s{\n", prepend);
  strcpy(v12, prepend);
  v7 = prependLen;
  v12[prependLen] = 9;
  v8 = &v12[v7 + 1];
  *v8 = 0;
  v9 = (this->m_flags & 1) == 0;
  v13 = v8;
  if ( !v9 )
    outFile->WriteFloatString(outFile, "%sSystemMemory\n", v12);
  if ( (this->m_flags & 2) != 0 )
    outFile->WriteFloatString(outFile, "%sVideoMemory\n", v12);
  outFile->WriteFloatString(outFile, "%sIndex[ %d ]\n", v12, this->m_numIndicesWritten);
  outFile->WriteFloatString(outFile, "%s{\n", v12);
  v10 = prependLen;
  *v13 = 9;
  v12[v10 + 2] = 0;
  if ( rvIndexBuffer::Lock(this, 0, this->m_numIndicesWritten, 1u, &indexBasePtr) )
  {
    outFile->WriteFloatString(outFile, v12);
    curIndex = 0;
    if ( (this->m_flags & 4) != 0 )
    {
      if ( this->m_numIndicesWritten > 0 )
      {
        do
        {
          outFile->WriteFloatString(outFile, "%d ", *((unsigned __int16 *)indexBasePtr + curIndex));
          if ( (curIndex & 0xF) == 15 )
            outFile->WriteFloatString(outFile, "\n%s", v12);
          ++curIndex;
        }
        while ( curIndex < this->m_numIndicesWritten );
      }
    }
    else if ( this->m_numIndicesWritten > 0 )
    {
      do
      {
        outFile->WriteFloatString(outFile, "%d ", *((_DWORD *)indexBasePtr + curIndex));
        if ( (curIndex & 0xF) == 15 )
          outFile->WriteFloatString(outFile, "\n%s", v12);
        ++curIndex;
      }
      while ( curIndex < this->m_numIndicesWritten );
    }
    outFile->WriteFloatString(outFile, "\n");
    rvIndexBuffer::Unlock(this);
    v11 = v13;
    v12[prependLen] = 9;
    *v11 = 0;
    outFile->WriteFloatString(outFile, "%s}\n", v12);
    outFile->WriteFloatString(outFile, "%s}\n", prepend);
  }
  else
  {
    idLib::common->FatalError(idLib::common, "Index buffer cannot be mapped for access");
  }
}

// FUNC: public: void __thiscall rvIndexBuffer::Shutdown(void)
void __thiscall rvIndexBuffer::Shutdown(rvIndexBuffer *this)
{
  if ( this->m_lockStatus )
    rvIndexBuffer::Unlock(this);
  if ( this->m_systemMemStorage )
    Mem_Free16(this->m_systemMemStorage);
  if ( this->m_ibID )
    qglDeleteBuffersARB(1, &this->m_ibID);
  this->m_ibID = 0;
  this->m_flags = 0;
  this->m_lockStatus = 0;
  this->m_numIndices = 0;
  this->m_lockIndexOffset = 0;
  this->m_lockIndexCount = 0;
  this->m_lockedBase = 0;
  this->m_systemMemStorage = 0;
  this->m_numIndicesWritten = 0;
}

// FUNC: public: void __thiscall rvIndexBuffer::Resize(int)
void __thiscall rvIndexBuffer::Resize(rvIndexBuffer *this, int numIndices)
{
  int m_numIndices; // eax
  int v4; // ebx
  int v5; // ebp
  void *v6; // edi
  bool v7; // zf

  m_numIndices = this->m_numIndices;
  if ( numIndices != m_numIndices && (this->m_flags & 1) != 0 )
  {
    if ( m_numIndices > numIndices )
      m_numIndices = numIndices;
    if ( (this->m_flags & 4) != 0 )
    {
      v4 = 2 * numIndices;
      v5 = 2 * m_numIndices;
    }
    else
    {
      v4 = 4 * numIndices;
      v5 = 4 * m_numIndices;
    }
    v6 = Mem_Alloc16(v4, 0x11u);
    if ( v6 )
    {
      SIMDProcessor->Memcpy(SIMDProcessor, v6, this->m_systemMemStorage, v5);
      Mem_Free16(this->m_systemMemStorage);
      v7 = (this->m_flags & 2) == 0;
      this->m_systemMemStorage = (unsigned __int8 *)v6;
      if ( !v7 )
      {
        qglBindBufferARB(0x8893u, this->m_ibID);
        qglBufferDataARB(0x8893u, v4, this->m_systemMemStorage, 0x88E4u);
        qglBindBufferARB(0x8893u, 0);
      }
      this->m_numIndices = numIndices;
    }
    else
    {
      idLib::common->FatalError(idLib::common, "Ran out of memory trying to allocate system memory index storage");
      rvIndexBuffer::Shutdown(this);
    }
  }
}

// FUNC: public: __thiscall rvIndexBuffer::~rvIndexBuffer(void)
// attributes: thunk
void __thiscall rvIndexBuffer::~rvIndexBuffer(rvIndexBuffer *this)
{
  rvIndexBuffer::Shutdown(this);
}

// FUNC: public: void __thiscall rvIndexBuffer::Init(int,unsigned int)
void __thiscall rvIndexBuffer::Init(rvIndexBuffer *this, int numIndices, unsigned int flagMask)
{
  if ( this->m_flags )
    rvIndexBuffer::Shutdown(this);
  this->m_numIndices = numIndices;
  this->m_flags = flagMask;
  rvIndexBuffer::CreateIndexStorage(this);
}

// FUNC: public: void __thiscall rvIndexBuffer::Init(class Lexer &)
void __thiscall rvIndexBuffer::Init(rvIndexBuffer *this, Lexer *lex)
{
  bool v3; // zf
  Lexer *v4; // edi
  Lexer *v5; // ebx
  Lexer *v6; // ebp
  Lexer *v7; // ebp
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v9; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v3 = this->m_flags == 0;
  v9 = 0;
  if ( !v3 )
    rvIndexBuffer::Shutdown(this);
  v4 = lex;
  Lexer::ExpectTokenString(lex, "{");
  this->m_flags = 0;
  while ( Lexer::ReadToken(v4, &token) )
  {
    if ( idStr::Icmp(token.data, "SystemMemory") )
    {
      if ( idStr::Icmp(token.data, "VideoMemory") )
        break;
      this->m_flags |= 2u;
    }
    else
    {
      this->m_flags |= 1u;
    }
  }
  if ( !this->m_flags )
    this->m_flags = 2;
  if ( !idStr::Icmp(token.data, "BitDepth") )
  {
    if ( Lexer::ParseInt(v4) == 16 )
      this->m_flags |= 4u;
    Lexer::ReadToken(v4, &token);
  }
  if ( idStr::Icmp(token.data, "Index") )
    Lexer::Error(v4, "Expected index header");
  Lexer::ExpectTokenString(v4, "[");
  this->m_numIndices = Lexer::ParseInt(v4);
  Lexer::ExpectTokenString(v4, "]");
  Lexer::ExpectTokenString(v4, "{");
  if ( this->m_numIndices <= 0 )
    Lexer::Error(v4, "Invalid index count");
  rvIndexBuffer::CreateIndexStorage(this);
  if ( rvIndexBuffer::Lock(this, 0, this->m_numIndices, 6u, (void **)&lex) )
  {
    v5 = lex;
    if ( (this->m_flags & 4) != 0 )
    {
      v6 = (Lexer *)((char *)lex + 2 * this->m_numIndices);
      if ( lex < v6 )
      {
        do
        {
          LOWORD(v5->mFile) = Lexer::ParseInt(v4);
          v5 = (Lexer *)((char *)v5 + 2);
        }
        while ( v5 < v6 );
      }
    }
    else
    {
      v7 = (Lexer *)((char *)lex + 4 * this->m_numIndices);
      if ( lex < v7 )
      {
        do
        {
          v5->mFile = (idFile *)Lexer::ParseInt(v4);
          v5 = (Lexer *)((char *)v5 + 4);
        }
        while ( v5 < v7 );
      }
    }
    rvIndexBuffer::Unlock(this);
    Lexer::ExpectTokenString(v4, "}");
    Lexer::ExpectTokenString(v4, "}");
    v9 = -1;
    idStr::FreeData(&token);
  }
  else
  {
    Lexer::Error(v4, "Index buffer cannot be mapped for access");
    rvIndexBuffer::Shutdown(this);
    v9 = -1;
    idStr::FreeData(&token);
  }
}
