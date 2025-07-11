
// FUNC: protected: void __thiscall rvVertexFormat::CalcSize(void)
void __thiscall rvVertexFormat::CalcSize(rvVertexFormat *this)
{
  unsigned int v2; // ecx
  const vertexStorageDesc_t *v3; // esi
  int m_size; // esi
  unsigned int v5; // ecx
  int v6; // edx
  int m_numValues; // ecx
  unsigned int v8; // edx
  unsigned int v9; // ecx
  const vertexStorageDesc_t *v10; // esi
  unsigned int v11; // edx
  const vertexStorageDesc_t *v12; // esi
  int v13; // ecx
  unsigned int v14; // edx
  const vertexStorageDesc_t *v15; // esi
  int v16; // ecx
  unsigned int v17; // edx
  const vertexStorageDesc_t *v18; // esi
  int v19; // ecx
  int v20; // esi
  unsigned int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // esi
  unsigned int v25; // ecx
  int v26; // edx
  int v27; // ecx
  int v28; // esi
  unsigned int v29; // ecx
  int v30; // edx
  int v31; // ecx
  int v32; // edx
  int v33; // ebp
  const vertexStorageDesc_t *v34; // edi
  unsigned int v35; // esi
  int v36; // ecx
  int *v37; // [esp+8h] [ebp-8h]
  int curTexCoorda; // [esp+Ch] [ebp-4h]
  int curTexCoordb; // [esp+Ch] [ebp-4h]
  int curTexCoordc; // [esp+Ch] [ebp-4h]
  int curTexCoordd; // [esp+Ch] [ebp-4h]
  int curTexCoorde; // [esp+Ch] [ebp-4h]
  int curTexCoord; // [esp+Ch] [ebp-4h]

  this->m_size = 0;
  this->m_numValues = 0;
  this->m_byteOffset[0] = 0;
  this->m_byteOffset[1] = 0;
  if ( (this->m_flags & 2) != 0 )
  {
    this->m_size = 12;
  }
  else if ( (this->m_flags & 1) != 0 )
  {
    v2 = this->m_dimensions & 7;
    v3 = &vertexStorageDescArray[this->m_dataTypes[0]];
    if ( (this->m_dimensions & 7) != 0 )
    {
      do
      {
        curTexCoorda = v2;
        this->m_tokenSubTypes[this->m_numValues++] = v3->m_tokenSubType;
        this->m_size += 4;
        v2 -= v3->m_numComponents;
      }
      while ( curTexCoorda - v3->m_numComponents > 0 );
    }
    this->m_glVASMask |= 1u;
  }
  m_size = this->m_size;
  v5 = this->m_flags >> 2;
  this->m_byteOffset[2] = m_size;
  if ( (v5 & 1) != 0 )
  {
    v6 = this->m_dataTypes[2];
    m_numValues = this->m_numValues;
    this->m_size = m_size + 4;
    this->m_tokenSubTypes[m_numValues] = vertexStorageDescArray[v6].m_tokenSubType;
    ++this->m_numValues;
    BYTE2(this->m_glVASMask) |= 2u;
  }
  v8 = this->m_flags >> 3;
  this->m_byteOffset[3] = this->m_size;
  if ( (v8 & 1) != 0 )
  {
    v9 = (this->m_dimensions >> 3) & 7;
    v10 = &vertexStorageDescArray[this->m_dataTypes[3]];
    if ( v9 )
    {
      do
      {
        curTexCoordb = v9;
        this->m_tokenSubTypes[this->m_numValues++] = v10->m_tokenSubType;
        this->m_size += 4;
        v9 -= v10->m_numComponents;
      }
      while ( curTexCoordb - v10->m_numComponents > 0 );
    }
    BYTE2(this->m_glVASMask) |= 0x20u;
  }
  v11 = this->m_flags >> 4;
  this->m_byteOffset[4] = this->m_size;
  if ( (v11 & 1) != 0 )
  {
    v12 = &vertexStorageDescArray[this->m_dataTypes[4]];
    v13 = 3;
    do
    {
      curTexCoordc = v13;
      this->m_tokenSubTypes[this->m_numValues++] = v12->m_tokenSubType;
      this->m_size += 4;
      v13 -= v12->m_numComponents;
    }
    while ( curTexCoordc - v12->m_numComponents > 0 );
    this->m_glVASMask |= 2u;
  }
  v14 = this->m_flags >> 5;
  this->m_byteOffset[5] = this->m_size;
  if ( (v14 & 1) != 0 )
  {
    v15 = &vertexStorageDescArray[this->m_dataTypes[5]];
    v16 = 3;
    do
    {
      curTexCoordd = v16;
      this->m_tokenSubTypes[this->m_numValues++] = v15->m_tokenSubType;
      this->m_size += 4;
      v16 -= v15->m_numComponents;
    }
    while ( curTexCoordd - v15->m_numComponents > 0 );
    BYTE2(this->m_glVASMask) |= 0x40u;
  }
  v17 = this->m_flags >> 6;
  this->m_byteOffset[6] = this->m_size;
  if ( (v17 & 1) != 0 )
  {
    v18 = &vertexStorageDescArray[this->m_dataTypes[6]];
    v19 = 3;
    do
    {
      curTexCoorde = v19;
      this->m_tokenSubTypes[this->m_numValues++] = v18->m_tokenSubType;
      this->m_size += 4;
      v19 -= v18->m_numComponents;
    }
    while ( curTexCoorde - v18->m_numComponents > 0 );
    BYTE2(this->m_glVASMask) |= 0x80u;
  }
  v20 = this->m_size;
  v21 = this->m_flags >> 7;
  this->m_byteOffset[7] = v20;
  if ( (v21 & 1) != 0 )
  {
    v22 = this->m_dataTypes[7];
    v23 = this->m_numValues;
    this->m_size = v20 + 4;
    this->m_tokenSubTypes[v23] = vertexStorageDescArray[v22].m_tokenSubType;
    ++this->m_numValues;
    this->m_glVASMask |= 4u;
  }
  v24 = this->m_size;
  v25 = this->m_flags >> 8;
  this->m_byteOffset[8] = v24;
  if ( (v25 & 1) != 0 )
  {
    v26 = this->m_dataTypes[8];
    v27 = this->m_numValues;
    this->m_size = v24 + 4;
    this->m_tokenSubTypes[v27] = vertexStorageDescArray[v26].m_tokenSubType;
    ++this->m_numValues;
    BYTE2(this->m_glVASMask) |= 0x10u;
  }
  v28 = this->m_size;
  v29 = this->m_flags >> 9;
  this->m_byteOffset[9] = v28;
  if ( (v29 & 1) != 0 )
  {
    v30 = this->m_dataTypes[9];
    v31 = this->m_numValues;
    this->m_size = v28 + 4;
    this->m_tokenSubTypes[v31] = vertexStorageDescArray[v30].m_tokenSubType;
    ++this->m_numValues;
    HIBYTE(this->m_glVASMask) |= 0x80u;
  }
  if ( (this->m_flags & 0x400) != 0 )
  {
    v32 = 0;
    curTexCoord = 0;
    v33 = 9;
    v37 = &this->m_byteOffset[10];
    do
    {
      *v37 = this->m_size;
      v34 = &vertexStorageDescArray[this->m_dataTypes[v32 + 10]];
      v35 = (this->m_dimensions >> v33) & 7;
      v36 = v35;
      if ( v35 )
      {
        do
        {
          this->m_tokenSubTypes[this->m_numValues] = v34->m_tokenSubType;
          this->m_size += 4;
          ++this->m_numValues;
          v36 -= v34->m_numComponents;
        }
        while ( v36 > 0 );
        v32 = curTexCoord;
      }
      if ( v35 )
        this->m_glVASMask |= 0x1000000 << v32;
      ++v37;
      ++v32;
      v33 += 3;
      curTexCoord = v32;
    }
    while ( v33 < 30 );
  }
}

// FUNC: protected: void __thiscall rvVertexFormat::BuildDataTypes(enum Rv_Vertex_Data_Type_t *)
void __thiscall rvVertexFormat::BuildDataTypes(rvVertexFormat *this, Rv_Vertex_Data_Type_t *dataTypes)
{
  unsigned int m_flags; // ecx
  unsigned __int8 *v4; // esi
  Rv_Vertex_Data_Type_t *v5; // edx
  int v6; // ebp

  m_flags = this->m_flags;
  if ( (m_flags & 2) != 0 || (m_flags & 1) != 0 )
  {
    if ( dataTypes && *dataTypes )
      this->m_dataTypes[0] = *(_BYTE *)dataTypes;
    else
      this->m_dataTypes[0] = 1;
  }
  if ( (m_flags & 4) != 0 )
  {
    if ( dataTypes && *((_DWORD *)dataTypes + 2) )
      this->m_dataTypes[2] = *((_BYTE *)dataTypes + 8);
    else
      this->m_dataTypes[2] = 10;
  }
  if ( (m_flags & 8) != 0 )
  {
    if ( dataTypes && *((_DWORD *)dataTypes + 3) )
      this->m_dataTypes[3] = *((_BYTE *)dataTypes + 12);
    else
      this->m_dataTypes[3] = 1;
  }
  if ( (m_flags & 0x10) != 0 )
  {
    if ( dataTypes && *((_DWORD *)dataTypes + 4) )
      this->m_dataTypes[4] = *((_BYTE *)dataTypes + 16);
    else
      this->m_dataTypes[4] = 1;
  }
  if ( (m_flags & 0x20) != 0 )
  {
    if ( dataTypes && *((_DWORD *)dataTypes + 5) )
      this->m_dataTypes[5] = *((_BYTE *)dataTypes + 20);
    else
      this->m_dataTypes[5] = 1;
  }
  if ( (m_flags & 0x40) != 0 )
  {
    if ( dataTypes && *((_DWORD *)dataTypes + 6) )
      this->m_dataTypes[6] = *((_BYTE *)dataTypes + 24);
    else
      this->m_dataTypes[6] = 1;
  }
  if ( (m_flags & 0x80) != 0 )
  {
    if ( dataTypes && *((_DWORD *)dataTypes + 7) )
      this->m_dataTypes[7] = *((_BYTE *)dataTypes + 28);
    else
      this->m_dataTypes[7] = 7;
  }
  if ( (m_flags & 0x100) != 0 )
  {
    if ( dataTypes && *((_DWORD *)dataTypes + 8) )
      this->m_dataTypes[8] = *((_BYTE *)dataTypes + 32);
    else
      this->m_dataTypes[8] = 7;
  }
  if ( (m_flags & 0x400) != 0 )
  {
    v4 = &this->m_dataTypes[10];
    v5 = dataTypes + 10;
    v6 = 7;
    do
    {
      if ( dataTypes && *v5 )
        *v4 = *(_BYTE *)v5;
      else
        *v4 = 1;
      ++v5;
      ++v4;
      --v6;
    }
    while ( v6 );
  }
  rvVertexFormat::CalcSize(this);
}

// FUNC: public: void __thiscall rvVertexFormat::GetTokenSubTypes(enum Rv_Vertex_Component_t,int * const)
void __thiscall rvVertexFormat::GetTokenSubTypes(
        rvVertexFormat *this,
        Rv_Vertex_Component_t vertexComponent,
        int *tokenSubTypes)
{
  int m_tokenSubType; // eax

  m_tokenSubType = vertexStorageDescArray[this->m_dataTypes[vertexComponent]].m_tokenSubType;
  tokenSubTypes[3] = m_tokenSubType;
  tokenSubTypes[2] = m_tokenSubType;
  tokenSubTypes[1] = m_tokenSubType;
  *tokenSubTypes = m_tokenSubType;
}

// FUNC: public: void __thiscall rvVertexFormat::SetVertexDeclaration(int)const
void __thiscall rvVertexFormat::SetVertexDeclaration(rvVertexFormat *this, int vertexStartOffset)
{
  int v3; // edi
  int v4; // eax
  bool m_normalized; // dl
  unsigned int m_countMask; // ecx
  unsigned int v7; // ecx
  unsigned int v8; // ecx
  unsigned int v9; // ecx
  unsigned int v10; // ecx
  unsigned int v11; // ecx
  unsigned int v12; // ecx
  int v13; // ecx
  int v14; // ebx
  unsigned int v15; // ebp
  unsigned int v16; // ecx
  int v17; // eax
  unsigned int v18; // ecx
  int m_size; // [esp-8h] [ebp-18h]
  const void *v20; // [esp-4h] [ebp-14h]
  int v21; // [esp+Ch] [ebp-4h]
  int *vertexStartOffseta; // [esp+14h] [ebp+4h]

  v3 = vertexStartOffset * this->m_size;
  if ( (this->m_flags & 4) != 0 )
  {
    v20 = (const void *)(v3 + this->m_byteOffset[2]);
    m_size = this->m_size;
    v4 = this->m_dataTypes[2];
    m_normalized = formatDescs[this->m_dataTypes[2]].m_normalized;
    m_countMask = formatDescs[this->m_dataTypes[2]].m_countMask;
    qglVertexAttribPointerARB(
      1u,
      (((_BYTE)m_countMask + (unsigned __int8)formatDescs[v4].m_countAdd) & 4)
    + (~m_countMask & formatDescs[v4].m_compressedCount),
      formatDescs[v4].m_glStorage,
      m_normalized,
      m_size,
      v20);
  }
  if ( (this->m_flags & 8) != 0 )
  {
    v7 = formatDescs[this->m_dataTypes[3]].m_countMask;
    qglVertexAttribPointerARB(
      5u,
      (~v7 & formatDescs[this->m_dataTypes[3]].m_compressedCount)
    + ((this->m_dimensions >> 3) & 7 & (v7 + formatDescs[this->m_dataTypes[3]].m_countAdd)),
      formatDescs[this->m_dataTypes[3]].m_glStorage,
      formatDescs[this->m_dataTypes[3]].m_normalized,
      this->m_size,
      (const void *)(v3 + this->m_byteOffset[3]));
  }
  if ( (this->m_flags & 0x10) != 0 )
    qglNormalPointer(
      formatDescs[this->m_dataTypes[4]].m_glStorage,
      this->m_size,
      (const void *)(v3 + this->m_byteOffset[4]));
  if ( (this->m_flags & 0x20) != 0 )
  {
    v8 = formatDescs[this->m_dataTypes[5]].m_countMask;
    qglVertexAttribPointerARB(
      6u,
      (((_BYTE)v8 + (unsigned __int8)formatDescs[this->m_dataTypes[5]].m_countAdd) & 3)
    + (~v8 & formatDescs[this->m_dataTypes[5]].m_compressedCount),
      formatDescs[this->m_dataTypes[5]].m_glStorage,
      formatDescs[this->m_dataTypes[5]].m_normalized,
      this->m_size,
      (const void *)(v3 + this->m_byteOffset[5]));
  }
  if ( (this->m_flags & 0x40) != 0 )
  {
    v9 = formatDescs[this->m_dataTypes[6]].m_countMask;
    qglVertexAttribPointerARB(
      7u,
      (((_BYTE)v9 + (unsigned __int8)formatDescs[this->m_dataTypes[6]].m_countAdd) & 3)
    + (~v9 & formatDescs[this->m_dataTypes[6]].m_compressedCount),
      formatDescs[this->m_dataTypes[6]].m_glStorage,
      formatDescs[this->m_dataTypes[6]].m_normalized,
      this->m_size,
      (const void *)(v3 + this->m_byteOffset[6]));
  }
  if ( (this->m_flags & 0x80) != 0 )
  {
    v10 = formatDescs[this->m_dataTypes[7]].m_countMask;
    qglColorPointer(
      (((_BYTE)v10 + (unsigned __int8)formatDescs[this->m_dataTypes[7]].m_countAdd) & 4)
    + (~v10 & formatDescs[this->m_dataTypes[7]].m_compressedCount),
      formatDescs[this->m_dataTypes[7]].m_glStorage,
      this->m_size,
      (const void *)(v3 + this->m_byteOffset[7]));
  }
  if ( (this->m_flags & 0x100) != 0 )
  {
    v11 = formatDescs[this->m_dataTypes[8]].m_countMask;
    qglVertexAttribPointerARB(
      4u,
      (((_BYTE)v11 + (unsigned __int8)formatDescs[this->m_dataTypes[8]].m_countAdd) & 4)
    + (~v11 & formatDescs[this->m_dataTypes[8]].m_compressedCount),
      formatDescs[this->m_dataTypes[8]].m_glStorage,
      formatDescs[this->m_dataTypes[8]].m_normalized,
      this->m_size,
      (const void *)(v3 + this->m_byteOffset[8]));
  }
  if ( (this->m_flags & 0x200) != 0 )
  {
    v12 = formatDescs[this->m_dataTypes[9]].m_countMask;
    qglVertexAttribPointerARB(
      0xFu,
      (((_BYTE)v12 + (unsigned __int8)formatDescs[this->m_dataTypes[9]].m_countAdd) & 1)
    + (~v12 & formatDescs[this->m_dataTypes[9]].m_compressedCount),
      formatDescs[this->m_dataTypes[9]].m_glStorage,
      formatDescs[this->m_dataTypes[9]].m_normalized,
      this->m_size,
      (const void *)(v3 + this->m_byteOffset[9]));
  }
  if ( (this->m_flags & 0x400) != 0 )
  {
    v13 = 9;
    v14 = 0;
    v21 = 9;
    vertexStartOffseta = &this->m_byteOffset[10];
    do
    {
      v15 = (this->m_dimensions >> v13) & 7;
      if ( v15 )
      {
        v16 = formatDescs[this->m_dataTypes[v14 + 10]].m_countMask;
        v17 = this->m_dataTypes[v14 + 10];
        qglVertexAttribPointerARB(
          v14 + 8,
          (~v16 & formatDescs[v17].m_compressedCount) + (v15 & (v16 + formatDescs[v17].m_countAdd)),
          formatDescs[v17].m_glStorage,
          formatDescs[v17].m_normalized,
          this->m_size,
          (const void *)(v3 + *vertexStartOffseta));
        v13 = v21;
      }
      ++vertexStartOffseta;
      v13 += 3;
      ++v14;
      v21 = v13;
    }
    while ( v13 < 30 );
  }
  if ( (this->m_flags & 1) != 0 )
  {
    v18 = formatDescs[this->m_dataTypes[0]].m_countMask;
    qglVertexPointer(
      (~v18 & formatDescs[this->m_dataTypes[0]].m_compressedCount)
    + (this->m_dimensions & (v18 + formatDescs[this->m_dataTypes[0]].m_countAdd) & 7),
      formatDescs[this->m_dataTypes[0]].m_glStorage,
      this->m_size,
      (const void *)(v3 + this->m_byteOffset[0]));
  }
}

// FUNC: public: void __thiscall rvVertexFormat::EnableVertexDeclaration(void)const
void __thiscall rvVertexFormat::EnableVertexDeclaration(rvVertexFormat *this)
{
  GL_VertexAttribState(this->m_glVASMask);
}

// FUNC: public: bool __thiscall rvVertexFormat::HasSameComponents(class rvVertexFormat const &)const
char __thiscall rvVertexFormat::HasSameComponents(rvVertexFormat *this, const rvVertexFormat *vf)
{
  unsigned int m_flags; // ecx
  unsigned int m_dimensions; // edx
  int v6; // ecx

  m_flags = vf->m_flags;
  if ( (this->m_flags & vf->m_flags) != vf->m_flags
    || (m_flags & 1) != 0 && ((LOBYTE(this->m_dimensions) ^ LOBYTE(vf->m_dimensions)) & 7) != 0
    || (m_flags & 8) != 0 && ((LOBYTE(this->m_dimensions) ^ LOBYTE(vf->m_dimensions)) & 0x38) != 0 )
  {
    return 0;
  }
  if ( (m_flags & 0x400) == 0 )
    return 1;
  m_dimensions = vf->m_dimensions;
  v6 = 9;
  while ( ((m_dimensions >> v6) & 7) == 0 || ((m_dimensions >> v6) & 7) == ((this->m_dimensions >> v6) & 7) )
  {
    v6 += 3;
    if ( v6 >= 30 )
      return 1;
  }
  return 0;
}

// FUNC: public: bool __thiscall rvVertexFormat::HasSameDataTypes(class rvVertexFormat const &)const
char __thiscall rvVertexFormat::HasSameDataTypes(rvVertexFormat *this, const rvVertexFormat *vf)
{
  unsigned int m_flags; // eax
  int v4; // eax
  char i; // si

  if ( (this->m_flags & 1) != 0 && this->m_dataTypes[0] != vf->m_dataTypes[0] )
    return 0;
  m_flags = this->m_flags;
  if ( (this->m_flags & 2) != 0 && this->m_dataTypes[1] != vf->m_dataTypes[1] )
    return 0;
  if ( (m_flags & 4) != 0 && this->m_dataTypes[2] != vf->m_dataTypes[2]
    || (m_flags & 8) != 0 && this->m_dataTypes[3] != vf->m_dataTypes[3]
    || (m_flags & 0x10) != 0 && this->m_dataTypes[4] != vf->m_dataTypes[4]
    || (m_flags & 0x20) != 0 && this->m_dataTypes[5] != vf->m_dataTypes[5]
    || (m_flags & 0x40) != 0 && this->m_dataTypes[6] != vf->m_dataTypes[6]
    || (m_flags & 0x80) != 0 && this->m_dataTypes[7] != vf->m_dataTypes[7]
    || (m_flags & 0x100) != 0 && this->m_dataTypes[8] != vf->m_dataTypes[8]
    || (m_flags & 0x200) != 0 && this->m_dataTypes[9] != vf->m_dataTypes[9] )
  {
    return 0;
  }
  if ( (m_flags & 0x400) == 0 )
    return 1;
  v4 = 10;
  for ( i = 9; ((vf->m_dimensions >> i) & 7) == 0 || this->m_dataTypes[v4] == vf->m_dataTypes[v4]; i += 3 )
  {
    if ( ++v4 - 10 >= 7 )
      return 1;
  }
  return 0;
}

// FUNC: public: __thiscall rvVertexFormat::rvVertexFormat(void)
void __thiscall rvVertexFormat::rvVertexFormat(rvVertexFormat *this)
{
  this->m_flags = 0;
  this->m_dimensions = 0;
  this->m_size = 0;
  memset(this->m_byteOffset, 0, sizeof(this->m_byteOffset));
  this->m_glVASMask = 0;
}

// FUNC: public: void __thiscall rvVertexFormat::Shutdown(void)
void __thiscall rvVertexFormat::Shutdown(rvVertexFormat *this)
{
  this->m_flags = 0;
  this->m_dimensions = 0;
  this->m_size = 0;
  memset(this->m_byteOffset, 0, sizeof(this->m_byteOffset));
  this->m_glVASMask = 0;
}

// FUNC: protected: void __thiscall rvVertexFormat::ParseComponentDataType(enum Rv_Vertex_Component_t,enum Rv_Vertex_Data_Type_t,class Lexer &)
void __thiscall rvVertexFormat::ParseComponentDataType(
        rvVertexFormat *this,
        Rv_Vertex_Component_t vertexComponent,
        Rv_Vertex_Data_Type_t defaultDataType,
        Lexer *lex)
{
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v6; // [esp+5Ch] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v6 = 0;
  Lexer::ReadToken(lex, &token);
  switch ( toupper(*token.data) )
  {
    case 'B':
      if ( idStr::Icmp(token.data, "Byte") )
      {
        if ( idStr::Icmp(token.data, "ByteN") )
          goto LABEL_56;
        this->m_dataTypes[vertexComponent] = 11;
      }
      else
      {
        this->m_dataTypes[vertexComponent] = 9;
      }
      break;
    case 'C':
      if ( idStr::Icmp(token.data, "Color") )
        goto LABEL_56;
      this->m_dataTypes[vertexComponent] = 7;
      break;
    case 'D':
      if ( idStr::Icmp(token.data, "DEC_10_10_10") )
      {
        if ( idStr::Icmp(token.data, "DEC_10_10_10N") )
        {
          if ( idStr::Icmp(token.data, "DEC_10_11_11") )
          {
            if ( idStr::Icmp(token.data, "DEC_10_11_11N") )
            {
              if ( idStr::Icmp(token.data, "DEC_11_11_10") )
              {
                if ( idStr::Icmp(token.data, "DEC_11_11_10N") )
                  goto LABEL_56;
                this->m_dataTypes[vertexComponent] = 27;
              }
              else
              {
                this->m_dataTypes[vertexComponent] = 25;
              }
            }
            else
            {
              this->m_dataTypes[vertexComponent] = 23;
            }
          }
          else
          {
            this->m_dataTypes[vertexComponent] = 21;
          }
        }
        else
        {
          this->m_dataTypes[vertexComponent] = 19;
        }
      }
      else
      {
        this->m_dataTypes[vertexComponent] = 17;
      }
      break;
    case 'F':
      if ( idStr::Icmp(token.data, "Float") )
      {
        if ( idStr::Icmp(token.data, "Float16") )
          goto LABEL_56;
        this->m_dataTypes[vertexComponent] = 2;
      }
      else
      {
        this->m_dataTypes[vertexComponent] = 1;
      }
      break;
    case 'I':
      if ( idStr::Icmp(token.data, "Int") )
      {
        if ( idStr::Icmp(token.data, "IntN") )
          goto LABEL_56;
        this->m_dataTypes[vertexComponent] = 5;
      }
      else
      {
        this->m_dataTypes[vertexComponent] = 3;
      }
      break;
    case 'S':
      if ( idStr::Icmp(token.data, "Short") )
      {
        if ( idStr::Icmp(token.data, "ShortN") )
          goto LABEL_56;
        this->m_dataTypes[vertexComponent] = 14;
      }
      else
      {
        this->m_dataTypes[vertexComponent] = 12;
      }
      break;
    case 'U':
      if ( idStr::Icmp(token.data, "UInt") )
      {
        if ( idStr::Icmp(token.data, "UIntN") )
        {
          if ( idStr::Icmp(token.data, "UByte") )
          {
            if ( idStr::Icmp(token.data, "UByteN") )
            {
              if ( idStr::Icmp(token.data, "UShort") )
              {
                if ( idStr::Icmp(token.data, "UShortN") )
                {
                  if ( idStr::Icmp(token.data, "UDec_10_10_10") )
                  {
                    if ( idStr::Icmp(token.data, "UDec_10_10_10N") )
                    {
                      if ( idStr::Icmp(token.data, "UDec_10_11_11") )
                      {
                        if ( idStr::Icmp(token.data, "UDec_10_11_11N") )
                        {
                          if ( idStr::Icmp(token.data, "UDec_11_11_10") )
                          {
                            if ( idStr::Icmp(token.data, "UDec_11_11_10N") )
                              goto LABEL_56;
                            this->m_dataTypes[vertexComponent] = 26;
                          }
                          else
                          {
                            this->m_dataTypes[vertexComponent] = 24;
                          }
                        }
                        else
                        {
                          this->m_dataTypes[vertexComponent] = 22;
                        }
                      }
                      else
                      {
                        this->m_dataTypes[vertexComponent] = 20;
                      }
                    }
                    else
                    {
                      this->m_dataTypes[vertexComponent] = 18;
                    }
                  }
                  else
                  {
                    this->m_dataTypes[vertexComponent] = 16;
                  }
                }
                else
                {
                  this->m_dataTypes[vertexComponent] = 15;
                }
              }
              else
              {
                this->m_dataTypes[vertexComponent] = 13;
              }
            }
            else
            {
              this->m_dataTypes[vertexComponent] = 10;
            }
          }
          else
          {
            this->m_dataTypes[vertexComponent] = 8;
          }
        }
        else
        {
          this->m_dataTypes[vertexComponent] = 6;
        }
      }
      else
      {
        this->m_dataTypes[vertexComponent] = 4;
      }
      break;
    default:
LABEL_56:
      Lexer::UnreadToken(lex, &token);
      this->m_dataTypes[vertexComponent] = defaultDataType;
      break;
  }
  v6 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: void __thiscall rvVertexFormat::Write(class idFile &,char const *)
void __thiscall rvVertexFormat::Write(rvVertexFormat *this, idFile *outFile, const char *__formal)
{
  unsigned __int8 v5; // al
  unsigned __int8 v6; // al
  unsigned __int8 v7; // al
  unsigned __int8 v8; // al
  unsigned __int8 v9; // al
  unsigned __int8 v10; // al
  unsigned __int8 v11; // al
  unsigned __int8 v12; // al
  unsigned __int8 v13; // al
  int v14; // ebp
  int i; // ebx
  idFile *outFilea; // [esp+Ch] [ebp+4h]

  outFile->WriteFloatString(outFile, "{ ");
  if ( (this->m_flags & 2) != 0 )
  {
    outFile->WriteFloatString(outFile, "Pos3Swizzled ");
    v5 = this->m_dataTypes[1];
  }
  else
  {
    if ( (this->m_flags & 1) == 0 )
      goto LABEL_7;
    outFile->WriteFloatString(outFile, "Position %d ", this->m_dimensions & 7);
    v5 = this->m_dataTypes[0];
  }
  if ( v5 != 1 )
    outFile->WriteFloatString(outFile, outputDataTypeStrings[v5]);
LABEL_7:
  if ( (this->m_flags & 4) != 0 )
  {
    outFile->WriteFloatString(outFile, "BlendIndex ");
    v6 = this->m_dataTypes[2];
    if ( v6 != 10 )
      outFile->WriteFloatString(outFile, outputDataTypeStrings[v6]);
  }
  if ( (this->m_flags & 8) != 0 )
  {
    outFile->WriteFloatString(
      outFile,
      "BlendWeight %d %d ",
      (this->m_dimensions >> 3) & 7,
      (this->m_dimensions >> 6) & 7);
    v7 = this->m_dataTypes[3];
    if ( v7 != 1 )
      outFile->WriteFloatString(outFile, outputDataTypeStrings[v7]);
  }
  if ( (this->m_flags & 0x10) != 0 )
  {
    outFile->WriteFloatString(outFile, "Normal ");
    v8 = this->m_dataTypes[4];
    if ( v8 != 1 )
      outFile->WriteFloatString(outFile, outputDataTypeStrings[v8]);
  }
  if ( (this->m_flags & 0x20) != 0 )
  {
    outFile->WriteFloatString(outFile, "Tangent ");
    v9 = this->m_dataTypes[5];
    if ( v9 != 1 )
      outFile->WriteFloatString(outFile, outputDataTypeStrings[v9]);
  }
  if ( (this->m_flags & 0x40) != 0 )
  {
    outFile->WriteFloatString(outFile, "Binormal ");
    v10 = this->m_dataTypes[6];
    if ( v10 != 1 )
      outFile->WriteFloatString(outFile, outputDataTypeStrings[v10]);
  }
  if ( (this->m_flags & 0x80) != 0 )
  {
    outFile->WriteFloatString(outFile, "DiffuseColor ");
    v11 = this->m_dataTypes[7];
    if ( v11 != 7 )
      outFile->WriteFloatString(outFile, outputDataTypeStrings[v11]);
  }
  if ( (this->m_flags & 0x100) != 0 )
  {
    outFile->WriteFloatString(outFile, "SpecularColor ");
    v12 = this->m_dataTypes[8];
    if ( v12 != 7 )
      outFile->WriteFloatString(outFile, outputDataTypeStrings[v12]);
  }
  if ( (this->m_flags & 0x200) != 0 )
  {
    outFile->WriteFloatString(outFile, "PointSize ");
    v13 = this->m_dataTypes[9];
    if ( v13 != 1 )
      outFile->WriteFloatString(outFile, outputDataTypeStrings[v13]);
  }
  if ( (this->m_flags & 0x400) != 0 )
  {
    v14 = 0;
    outFilea = (idFile *)&this->m_dataTypes[10];
    for ( i = 9; i < 30; i += 3 )
    {
      if ( ((this->m_dimensions >> i) & 7) != 0 )
        outFile->WriteFloatString(outFile, "TexCoord %d %d ", (this->m_dimensions >> i) & 7, v14);
      if ( LOBYTE(outFilea->__vftable) != 1 )
        outFile->WriteFloatString(outFile, outputDataTypeStrings[LOBYTE(outFilea->__vftable)]);
      outFilea = (idFile *)((char *)outFilea + 1);
      ++v14;
    }
  }
  outFile->WriteFloatString(outFile, "}\n");
}

// FUNC: public: void __thiscall rvVertexFormat::Init(unsigned int,int,int,int,int const * const,enum Rv_Vertex_Data_Type_t *)
void __thiscall rvVertexFormat::Init(
        rvVertexFormat *this,
        unsigned int vtxFmtFlags,
        int posDim,
        int numWeights,
        int numTransforms,
        const int *texDimArray,
        Rv_Vertex_Data_Type_t *dataTypes)
{
  unsigned int v8; // eax
  char v9; // si
  char v10; // di
  int v11; // esi
  int v12; // edi
  int v13; // eax

  if ( this->m_flags )
  {
    this->m_flags = 0;
    this->m_dimensions = 0;
    this->m_size = 0;
    memset(this->m_byteOffset, 0, sizeof(this->m_byteOffset));
    this->m_glVASMask = 0;
  }
  v8 = vtxFmtFlags;
  this->m_flags = vtxFmtFlags;
  if ( (vtxFmtFlags & 2) != 0 )
  {
    LOBYTE(v8) = vtxFmtFlags | 1;
    v9 = 3;
    this->m_flags = v8;
  }
  else
  {
    v9 = posDim;
    if ( posDim > 4 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "Vertex format was initialized with an unsupported position dimension");
  }
  if ( numWeights > 4 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "Vertex format was initialized with an unsupported number of blend weights");
  v10 = numTransforms;
  if ( numTransforms >= 1 )
  {
    if ( numTransforms > numWeights + 1 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "Vertex format was initialized with an unsupported number of blend transforms");
  }
  else
  {
    v10 = 1;
  }
  this->m_dimensions = v9 & 7 | (8 * (numWeights & 7 | (8 * (v10 & 7))));
  if ( (vtxFmtFlags & 0x400) != 0 )
  {
    v11 = 0;
    v12 = 9;
    do
    {
      if ( texDimArray[v11] > 4 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "Vertex format was initialized with an unsupported texture dimension");
      v13 = (texDimArray[v11++] & 7) << v12;
      v12 += 3;
      this->m_dimensions |= v13;
    }
    while ( v11 < 7 );
  }
  rvVertexFormat::BuildDataTypes(this, dataTypes);
}

// FUNC: public: void __thiscall rvVertexFormat::Init(class Lexer &)
void __thiscall rvVertexFormat::Init(rvVertexFormat *this, Lexer *lex)
{
  Rv_Vertex_Component_t v2; // ebp
  bool v4; // zf
  Rv_Vertex_Data_Type_t v5; // ebx
  signed int v6; // ebx
  signed int v7; // ebp
  signed int v8; // eax
  char v9; // bl
  signed int v10; // ebx
  signed int v11; // ebp
  unsigned int m_dimensions; // eax
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v14; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  v2 = RV_VERTEX_COMPONENT_POSITION;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v4 = this->m_flags == 0;
  v14 = 0;
  v5 = RV_VERTEX_DATA_TYPE_FLOAT;
  if ( !v4 )
  {
    this->m_flags = 0;
    this->m_dimensions = 0;
    this->m_size = 0;
    memset(this->m_byteOffset, 0, sizeof(this->m_byteOffset));
    this->m_glVASMask = 0;
  }
  Lexer::ExpectTokenString(lex, "{");
  if ( Lexer::ReadToken(lex, &token) )
  {
    while ( idStr::Icmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "Position") )
      {
        if ( idStr::Icmp(token.data, "PositionSwizzled") )
        {
          if ( idStr::Icmp(token.data, "BlendIndex") )
          {
            if ( idStr::Icmp(token.data, "BlendWeight") )
            {
              if ( idStr::Icmp(token.data, "Normal") )
              {
                if ( idStr::Icmp(token.data, "Tangent") )
                {
                  if ( idStr::Icmp(token.data, "Binormal") )
                  {
                    if ( idStr::Icmp(token.data, "DiffuseColor") )
                    {
                      if ( idStr::Icmp(token.data, "SpecularColor") )
                      {
                        if ( idStr::Icmp(token.data, "PointSize") )
                        {
                          if ( idStr::Icmp(token.data, "TexCoord") )
                          {
                            Lexer::Error(lex, "Expected vertex format keyword");
                          }
                          else
                          {
                            BYTE1(this->m_flags) |= 4u;
                            v10 = Lexer::ParseInt(lex);
                            if ( v10 > 4 )
                              Lexer::Error(
                                lex,
                                "Vertex format was initialized with an unsupported texture coordinate dimension");
                            v11 = Lexer::ParseInt(lex);
                            if ( v11 >= 7 )
                              Lexer::Error(
                                lex,
                                "Vertex format was initialized with an unsupported texture coordinate set");
                            this->m_dimensions |= v10 << (3 * v11 + 9);
                            v2 = v11 + 10;
                            v5 = RV_VERTEX_DATA_TYPE_FLOAT;
                          }
                        }
                        else
                        {
                          BYTE1(this->m_flags) |= 2u;
                          v2 = RV_VERTEX_COMPONENT_POINT_SIZE;
                          v5 = RV_VERTEX_DATA_TYPE_FLOAT;
                        }
                      }
                      else
                      {
                        BYTE1(this->m_flags) |= 1u;
                        v2 = RV_VERTEX_COMPONENT_SPECULAR_COLOR;
                        v5 = RV_VERTEX_DATA_TYPE_COLOR;
                      }
                    }
                    else
                    {
                      LOBYTE(this->m_flags) |= 0x80u;
                      v2 = RV_VERTEX_COMPONENT_DIFFUSE_COLOR;
                      v5 = RV_VERTEX_DATA_TYPE_COLOR;
                    }
                  }
                  else
                  {
                    this->m_flags |= 0x40u;
                    v2 = RV_VERTEX_COMPONENT_BINORMAL;
                    v5 = RV_VERTEX_DATA_TYPE_FLOAT;
                  }
                }
                else
                {
                  this->m_flags |= 0x20u;
                  v2 = RV_VERTEX_COMPONENT_TANGENT;
                  v5 = RV_VERTEX_DATA_TYPE_FLOAT;
                }
              }
              else
              {
                this->m_flags |= 0x10u;
                v2 = RV_VERTEX_COMPONENT_NORMAL;
                v5 = RV_VERTEX_DATA_TYPE_FLOAT;
              }
            }
            else
            {
              this->m_flags |= 8u;
              v7 = Lexer::ParseInt(lex);
              if ( v7 > 4 )
                Lexer::Error(lex, "Vertex format was initialized with an unsupported number of blend weights");
              v8 = Lexer::ParseInt(lex);
              v9 = v8;
              if ( v8 >= 1 )
              {
                if ( v8 > v7 + 1 )
                  Lexer::Error(lex, "Vertex format was initialized with an unsupported number of blend transforms");
              }
              else
              {
                v9 = 1;
              }
              this->m_dimensions |= 8 * (v7 & 7 | (8 * (v9 & 7)));
              v2 = RV_VERTEX_COMPONENT_BLEND_WEIGHT;
              v5 = RV_VERTEX_DATA_TYPE_FLOAT;
            }
          }
          else
          {
            this->m_flags |= 4u;
            v2 = RV_VERTEX_COMPONENT_BLEND_INDEX;
            v5 = RV_VERTEX_DATA_TYPE_UBYTEN;
          }
        }
        else
        {
          this->m_flags |= 2u;
          this->m_dimensions |= 3u;
          v2 = RV_VERTEX_COMPONENT_SWIZZLED_POSITION;
          v5 = RV_VERTEX_DATA_TYPE_FLOAT;
        }
      }
      else
      {
        this->m_flags |= 1u;
        v6 = Lexer::ParseInt(lex);
        if ( v6 > 4 )
          Lexer::Error(lex, "Vertex format was initialized with an unsupported position dimension");
        this->m_dimensions |= v6;
        v2 = RV_VERTEX_COMPONENT_POSITION;
        v5 = RV_VERTEX_DATA_TYPE_FLOAT;
      }
      rvVertexFormat::ParseComponentDataType(this, v2, v5, lex);
      if ( !Lexer::ReadToken(lex, &token) )
        goto LABEL_41;
    }
    rvVertexFormat::CalcSize(this);
    m_dimensions = this->m_dimensions;
    if ( ((m_dimensions >> 6) & 7) == 0 )
    {
      LOBYTE(m_dimensions) = m_dimensions | 0x40;
      this->m_dimensions = m_dimensions;
    }
  }
  else
  {
LABEL_41:
    Lexer::Error(lex, "Unexpected end-of-token stream");
  }
  v14 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: void __thiscall rvVertexFormat::Init(class rvVertexFormat const &)
void __thiscall rvVertexFormat::Init(rvVertexFormat *this, const rvVertexFormat *vf)
{
  unsigned __int8 *m_dataTypes; // edi
  int *m_byteOffset; // esi
  int v5; // eax
  int v6; // ecx
  unsigned __int8 *m_tokenSubTypes; // esi
  int v8; // edi

  if ( this->m_flags )
  {
    this->m_flags = 0;
    this->m_dimensions = 0;
    this->m_size = 0;
    memset(this->m_byteOffset, 0, sizeof(this->m_byteOffset));
    this->m_glVASMask = 0;
  }
  this->m_flags = vf->m_flags;
  this->m_dimensions = vf->m_dimensions;
  this->m_size = vf->m_size;
  this->m_numValues = vf->m_numValues;
  m_dataTypes = this->m_dataTypes;
  m_byteOffset = this->m_byteOffset;
  v5 = (char *)vf - (char *)this;
  v6 = 18;
  do
  {
    *m_byteOffset = *(int *)((char *)m_byteOffset + v5);
    *m_dataTypes = m_dataTypes[v5];
    ++m_byteOffset;
    ++m_dataTypes;
    --v6;
  }
  while ( v6 );
  m_tokenSubTypes = this->m_tokenSubTypes;
  v8 = 72;
  do
  {
    *m_tokenSubTypes = m_tokenSubTypes[v5];
    ++m_tokenSubTypes;
    --v8;
  }
  while ( v8 );
  this->m_glVASMask = vf->m_glVASMask;
}

// FUNC: public: __thiscall rvVertexFormat::rvVertexFormat(unsigned int,int,int,int,int const * const)
void __thiscall rvVertexFormat::rvVertexFormat(
        rvVertexFormat *this,
        unsigned int vtxFmtFlags,
        int posDim,
        int numWeights,
        int numTransforms,
        const int *texDimArray)
{
  this->m_flags = 0;
  this->m_dimensions = 0;
  this->m_size = 0;
  memset(this->m_byteOffset, 0, sizeof(this->m_byteOffset));
  this->m_glVASMask = 0;
  rvVertexFormat::Init(this, vtxFmtFlags, posDim, numWeights, numTransforms, texDimArray, 0);
}
