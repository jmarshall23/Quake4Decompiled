
// FUNC: protected: void __thiscall rvVertexBuffer::ResetValues(void)
void __thiscall rvVertexBuffer::ResetValues(rvVertexBuffer *this)
{
  float **m_texCoordArrays; // ecx

  this->m_flags = 0;
  this->m_lockStatus = 0;
  this->m_numVertices = 0;
  this->m_vbID = 0;
  this->m_lockVertexOffset = 0;
  this->m_lockVertexCount = 0;
  this->m_lockedBase = 0;
  this->m_numVerticesWritten = 0;
  this->m_interleavedStorage = 0;
  this->m_positionArray = 0;
  this->m_swizzledPositionArray = 0;
  this->m_blendIndexArray = 0;
  this->m_blendWeightArray = 0;
  this->m_normalArray = 0;
  this->m_tangentArray = 0;
  this->m_binormalArray = 0;
  this->m_diffuseColorArray = 0;
  this->m_specularColorArray = 0;
  this->m_pointSizeArray = 0;
  m_texCoordArrays = this->m_texCoordArrays;
  *m_texCoordArrays = 0;
  m_texCoordArrays[1] = 0;
  m_texCoordArrays[2] = 0;
  m_texCoordArrays[3] = 0;
  m_texCoordArrays[4] = 0;
  m_texCoordArrays[5] = 0;
  m_texCoordArrays[6] = 0;
}

// FUNC: protected: void __thiscall rvVertexBuffer::CreateVertexStorage(void)
void __thiscall rvVertexBuffer::CreateVertexStorage(rvVertexBuffer *this)
{
  char v2; // bl
  float *v3; // eax
  int v4; // eax
  float *v5; // eax
  unsigned int *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  unsigned int *v11; // eax
  unsigned int *v12; // eax
  float *v13; // eax
  int v14; // edi
  float **m_texCoordArrays; // ebp
  float *v16; // eax
  unsigned __int8 *v17; // eax
  unsigned int m_vbID; // edi
  unsigned int Error; // eax

  if ( (this->m_flags & 1) == 0 )
    goto LABEL_32;
  if ( (this->m_flags & 4) != 0 )
  {
    v2 = 0;
    if ( (this->m_format.m_flags & 1) != 0 )
    {
      v3 = (float *)Mem_Alloc16(4 * this->m_numVertices * (this->m_format.m_dimensions & 7), 0x11u);
      this->m_positionArray = v3;
      v2 = v3 == 0;
    }
    if ( (this->m_format.m_flags & 2) != 0 )
    {
      v4 = this->m_numVertices + 3;
      LOBYTE(v4) = v4 & 0xFC;
      v5 = (float *)Mem_Alloc16(12 * v4, 0x11u);
      this->m_swizzledPositionArray = v5;
      v2 |= v5 == 0;
    }
    if ( (this->m_format.m_flags & 4) != 0 )
    {
      v6 = (unsigned int *)Mem_Alloc16(4 * this->m_numVertices, 0x11u);
      this->m_blendIndexArray = v6;
      v2 |= v6 == 0;
    }
    if ( (this->m_format.m_flags & 8) != 0 )
    {
      v7 = (float *)Mem_Alloc16(4 * this->m_numVertices * ((this->m_format.m_dimensions >> 3) & 7), 0x11u);
      this->m_blendWeightArray = v7;
      v2 |= v7 == 0;
    }
    if ( (this->m_format.m_flags & 0x10) != 0 )
    {
      v8 = (float *)Mem_Alloc16(12 * this->m_numVertices, 0x11u);
      this->m_normalArray = v8;
      v2 |= v8 == 0;
    }
    if ( (this->m_format.m_flags & 0x20) != 0 )
    {
      v9 = (float *)Mem_Alloc16(12 * this->m_numVertices, 0x11u);
      this->m_tangentArray = v9;
      v2 |= v9 == 0;
    }
    if ( (this->m_format.m_flags & 0x40) != 0 )
    {
      v10 = (float *)Mem_Alloc16(12 * this->m_numVertices, 0x11u);
      this->m_binormalArray = v10;
      v2 |= v10 == 0;
    }
    if ( (this->m_format.m_flags & 0x80) != 0 )
    {
      v11 = (unsigned int *)Mem_Alloc16(4 * this->m_numVertices, 0x11u);
      this->m_diffuseColorArray = v11;
      v2 |= v11 == 0;
    }
    if ( (this->m_format.m_flags & 0x100) != 0 )
    {
      v12 = (unsigned int *)Mem_Alloc16(4 * this->m_numVertices, 0x11u);
      this->m_specularColorArray = v12;
      v2 |= v12 == 0;
    }
    if ( (this->m_format.m_flags & 0x200) != 0 )
    {
      v13 = (float *)Mem_Alloc16(4 * this->m_numVertices, 0x11u);
      this->m_pointSizeArray = v13;
      v2 |= v13 == 0;
    }
    if ( (this->m_format.m_flags & 0x400) != 0 )
    {
      v14 = 9;
      m_texCoordArrays = this->m_texCoordArrays;
      do
      {
        if ( ((this->m_format.m_dimensions >> v14) & 7) != 0 )
        {
          v16 = (float *)Mem_Alloc16(4 * ((this->m_format.m_dimensions >> v14) & 7) * this->m_numVertices, 0x11u);
          *m_texCoordArrays = v16;
          v2 |= v16 == 0;
        }
        v14 += 3;
        ++m_texCoordArrays;
      }
      while ( v14 < 30 );
    }
  }
  else
  {
    v17 = (unsigned __int8 *)Mem_Alloc16(this->m_format.m_size * this->m_numVertices, 0x11u);
    this->m_interleavedStorage = v17;
    v2 = v17 == 0;
  }
  if ( v2 )
  {
    idLib::common->Error(idLib::common, "Ran out of memory trying to allocate system memory vertex storage");
  }
  else
  {
LABEL_32:
    if ( (this->m_flags & 2) != 0 )
    {
      qglGetError();
      qglGenBuffersARB(1, &this->m_vbID);
      m_vbID = this->m_vbID;
      if ( m_vbID )
      {
        if ( (this->m_flags & 8) == 0 )
        {
          qglBindBufferARB(0x8892u, m_vbID);
          qglBufferDataARB(0x8892u, this->m_format.m_size * this->m_numVertices, 0, 0x88E4u);
          Error = qglGetError();
          if ( Error )
          {
            idLib::common->Error(idLib::common, "Unable to allocate vertex storage - %d", Error);
          }
          else
          {
            rvVertexFormat::SetVertexDeclaration(&this->m_format, 0);
            qglBindBufferARB(0x8892u, 0);
          }
        }
      }
      else
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "rvVertexBuffer: Unable to gen buffer id");
      }
    }
  }
}

// FUNC: protected: bool __thiscall rvVertexBuffer::LockInterleaved(int,int,unsigned int,void * &,int &)
char __thiscall rvVertexBuffer::LockInterleaved(
        rvVertexBuffer *this,
        int vertexOffset,
        int numVerticesToLock,
        unsigned int lockFlags,
        void **startPtr,
        int *stride)
{
  bool v7; // zf
  unsigned int v8; // edi
  unsigned int v9; // ebx
  unsigned __int8 *v10; // eax
  unsigned int v12; // eax
  unsigned __int8 *v13; // eax
  int v14; // [esp-Ch] [ebp-18h]

  v7 = (this->m_flags & 1) == 0;
  v8 = 35000;
  this->m_lockVertexOffset = vertexOffset;
  this->m_lockVertexCount = numVerticesToLock;
  if ( !v7 )
  {
    this->m_lockedBase = this->m_interleavedStorage;
LABEL_3:
    v9 = lockFlags;
LABEL_4:
    v10 = &this->m_lockedBase[this->m_lockVertexOffset * this->m_format.m_size];
    this->m_lockStatus = v9;
    *startPtr = v10;
    *stride = this->m_format.m_size;
    return 1;
  }
  if ( this->m_lockStatus )
    goto LABEL_3;
  qglBindBufferARB(0x8892u, this->m_vbID);
  v9 = lockFlags;
  if ( (lockFlags & 1) != 0 )
  {
    v8 = lockFlags & 2 | 0x88B8;
  }
  else if ( (lockFlags & 2) != 0 )
  {
    v8 = 35001;
    if ( (this->m_flags & 8) != 0 )
    {
      v9 = lockFlags | 4;
      v12 = 35040;
    }
    else
    {
      v12 = 35044;
    }
    if ( (v9 & 4) != 0 )
    {
      if ( !this->m_lockVertexCount )
        this->m_lockVertexCount = this->m_numVertices;
      v14 = this->m_lockVertexCount * this->m_format.m_size;
      this->m_lockVertexOffset = 0;
      qglBufferDataARB(0x8892u, v14, 0, v12);
    }
  }
  v13 = (unsigned __int8 *)qglMapBufferARB(0x8892u, v8);
  this->m_lockedBase = v13;
  if ( v13 )
    goto LABEL_4;
  return 0;
}

// FUNC: protected: void __thiscall rvVertexBuffer::TransferSoAToAoS(unsigned char *)
void __thiscall rvVertexBuffer::TransferSoAToAoS(rvVertexBuffer *this, unsigned __int8 *vertexDest)
{
  int m_numVertices; // eax
  float *m_swizzledPositionArray; // edi
  unsigned __int8 *v4; // esi
  float *v5; // ebx
  unsigned __int8 *v6; // esi
  unsigned __int8 *v7; // esi
  unsigned __int8 *v8; // esi
  unsigned __int8 *v9; // esi
  unsigned __int8 *v10; // esi
  unsigned __int8 *v11; // esi
  unsigned __int8 *v12; // esi
  unsigned __int8 *v13; // esi
  unsigned __int8 *v14; // esi
  _DWORD *v15; // esi
  _DWORD *v16; // esi
  _DWORD *v17; // esi
  _DWORD *v18; // esi
  _DWORD *v19; // esi
  _DWORD *v20; // esi
  unsigned __int8 *v21; // esi
  unsigned __int8 *v22; // esi
  unsigned __int8 *v23; // esi
  float *m_positionArray; // esi
  unsigned __int8 *v25; // edi
  float *v26; // ebx
  unsigned __int8 *v27; // edi
  unsigned __int8 *v28; // edi
  unsigned __int8 *v29; // edi
  float *i; // eax
  int v31; // edx
  _DWORD *v32; // esi
  float *j; // eax
  int v34; // edx
  int *v35; // esi
  int v36; // edx
  float *k; // eax
  int v38; // edx
  int *v39; // esi
  int v40; // edx
  int v41; // edx
  unsigned int *m_blendIndexArray; // eax
  unsigned int *v43; // esi
  unsigned __int8 *m; // edx
  float *m_blendWeightArray; // esi
  unsigned __int8 *v46; // edi
  float *v47; // ebx
  unsigned __int8 *v48; // edi
  unsigned __int8 *v49; // edi
  unsigned __int8 *v50; // edi
  float *n; // eax
  int v52; // edx
  _DWORD *v53; // esi
  float *ii; // eax
  int v55; // edx
  int *v56; // esi
  int v57; // edx
  float *jj; // eax
  int v59; // edx
  int *v60; // esi
  int v61; // edx
  int v62; // edx
  float *m_normalArray; // eax
  float *v64; // esi
  unsigned __int8 *kk; // edx
  int v66; // edi
  int *v67; // eax
  int v68; // edi
  float *m_tangentArray; // eax
  float *v70; // esi
  unsigned __int8 *mm; // edx
  int v72; // edi
  int *v73; // eax
  int v74; // edi
  float *m_binormalArray; // eax
  float *v76; // esi
  unsigned __int8 *nn; // edx
  int v78; // edi
  int *v79; // eax
  int v80; // edi
  unsigned int *m_diffuseColorArray; // eax
  unsigned int *v82; // esi
  unsigned __int8 *i1; // edx
  unsigned int *m_specularColorArray; // eax
  unsigned int *v85; // esi
  unsigned __int8 *i2; // edx
  float *m_pointSizeArray; // edi
  float *v88; // ebx
  unsigned __int8 *v89; // esi
  unsigned __int8 *v90; // esi
  unsigned __int8 *v91; // esi
  unsigned __int8 *v92; // esi
  float **m_texCoordArrays; // ebp
  float *v94; // esi
  unsigned __int8 *v95; // edi
  float *v96; // ebx
  unsigned __int8 *v97; // edi
  unsigned __int8 *v98; // edi
  unsigned __int8 *v99; // edi
  float *i3; // eax
  int v101; // edx
  _DWORD *v102; // esi
  float *i4; // eax
  int v104; // edx
  int *v105; // esi
  int v106; // edx
  float *i5; // eax
  int v108; // edx
  int *v109; // esi
  int v110; // edx
  int v111; // edx
  int v112; // [esp+10h] [ebp-4h]

  if ( (this->m_format.m_flags & 2) != 0 )
  {
    m_numVertices = this->m_numVertices;
    m_swizzledPositionArray = this->m_swizzledPositionArray;
    LOBYTE(m_numVertices) = m_numVertices & 0xFC;
    v4 = vertexDest;
    v5 = &m_swizzledPositionArray[3 * m_numVertices];
    if ( (12 * m_numVertices + 47) / 48 >= 4 )
    {
      do
      {
        *(float *)v4 = *m_swizzledPositionArray;
        *((float *)v4 + 1) = m_swizzledPositionArray[4];
        *((float *)v4 + 2) = m_swizzledPositionArray[8];
        v6 = &v4[this->m_format.m_size];
        *(float *)v6 = m_swizzledPositionArray[1];
        *((float *)v6 + 1) = m_swizzledPositionArray[5];
        *((float *)v6 + 2) = m_swizzledPositionArray[9];
        v7 = &v6[this->m_format.m_size];
        *(float *)v7 = m_swizzledPositionArray[2];
        *((float *)v7 + 1) = m_swizzledPositionArray[6];
        *((float *)v7 + 2) = m_swizzledPositionArray[10];
        v8 = &v7[this->m_format.m_size];
        *(float *)v8 = m_swizzledPositionArray[3];
        *((float *)v8 + 1) = m_swizzledPositionArray[7];
        *((float *)v8 + 2) = m_swizzledPositionArray[11];
        v9 = &v8[this->m_format.m_size];
        *(float *)v9 = m_swizzledPositionArray[12];
        *((float *)v9 + 1) = m_swizzledPositionArray[16];
        *((float *)v9 + 2) = m_swizzledPositionArray[20];
        v10 = &v9[this->m_format.m_size];
        *(float *)v10 = m_swizzledPositionArray[13];
        *((float *)v10 + 1) = m_swizzledPositionArray[17];
        *((float *)v10 + 2) = m_swizzledPositionArray[21];
        v11 = &v10[this->m_format.m_size];
        *(float *)v11 = m_swizzledPositionArray[14];
        *((float *)v11 + 1) = m_swizzledPositionArray[18];
        *((float *)v11 + 2) = m_swizzledPositionArray[22];
        v12 = &v11[this->m_format.m_size];
        *(float *)v12 = m_swizzledPositionArray[15];
        *((float *)v12 + 1) = m_swizzledPositionArray[19];
        *((float *)v12 + 2) = m_swizzledPositionArray[23];
        v13 = &v12[this->m_format.m_size];
        *(float *)v13 = m_swizzledPositionArray[24];
        *((float *)v13 + 1) = m_swizzledPositionArray[28];
        *((float *)v13 + 2) = m_swizzledPositionArray[32];
        v14 = &v13[this->m_format.m_size];
        *v14 = *((_DWORD *)m_swizzledPositionArray + 25);
        v14[1] = *((_DWORD *)m_swizzledPositionArray + 29);
        v14[2] = *((_DWORD *)m_swizzledPositionArray + 33);
        v15 = (_DWORD *)((char *)v14 + this->m_format.m_size);
        *v15 = *((_DWORD *)m_swizzledPositionArray + 26);
        v15[1] = *((_DWORD *)m_swizzledPositionArray + 30);
        v15[2] = *((_DWORD *)m_swizzledPositionArray + 34);
        v16 = (_DWORD *)((char *)v15 + this->m_format.m_size);
        *v16 = *((_DWORD *)m_swizzledPositionArray + 27);
        v16[1] = *((_DWORD *)m_swizzledPositionArray + 31);
        v16[2] = *((_DWORD *)m_swizzledPositionArray + 35);
        v17 = (_DWORD *)((char *)v16 + this->m_format.m_size);
        *v17 = *((_DWORD *)m_swizzledPositionArray + 36);
        v17[1] = *((_DWORD *)m_swizzledPositionArray + 40);
        v17[2] = *((_DWORD *)m_swizzledPositionArray + 44);
        v18 = (_DWORD *)((char *)v17 + this->m_format.m_size);
        *v18 = *((_DWORD *)m_swizzledPositionArray + 37);
        v18[1] = *((_DWORD *)m_swizzledPositionArray + 41);
        v18[2] = *((_DWORD *)m_swizzledPositionArray + 45);
        v19 = (_DWORD *)((char *)v18 + this->m_format.m_size);
        *v19 = *((_DWORD *)m_swizzledPositionArray + 38);
        v19[1] = *((_DWORD *)m_swizzledPositionArray + 42);
        v19[2] = *((_DWORD *)m_swizzledPositionArray + 46);
        v20 = (_DWORD *)((char *)v19 + this->m_format.m_size);
        *v20 = *((_DWORD *)m_swizzledPositionArray + 39);
        v20[1] = *((_DWORD *)m_swizzledPositionArray + 43);
        v20[2] = *((_DWORD *)m_swizzledPositionArray + 47);
        v4 = (unsigned __int8 *)v20 + this->m_format.m_size;
        m_swizzledPositionArray += 48;
      }
      while ( (int)m_swizzledPositionArray < (int)(v5 - 36) );
    }
    for ( ; m_swizzledPositionArray < v5; m_swizzledPositionArray += 12 )
    {
      *(float *)v4 = *m_swizzledPositionArray;
      *((float *)v4 + 1) = m_swizzledPositionArray[4];
      *((float *)v4 + 2) = m_swizzledPositionArray[8];
      v21 = &v4[this->m_format.m_size];
      *(float *)v21 = m_swizzledPositionArray[1];
      *((float *)v21 + 1) = m_swizzledPositionArray[5];
      *((float *)v21 + 2) = m_swizzledPositionArray[9];
      v22 = &v21[this->m_format.m_size];
      *(float *)v22 = m_swizzledPositionArray[2];
      *((float *)v22 + 1) = m_swizzledPositionArray[6];
      *((float *)v22 + 2) = m_swizzledPositionArray[10];
      v23 = &v22[this->m_format.m_size];
      *(float *)v23 = m_swizzledPositionArray[3];
      *((float *)v23 + 1) = m_swizzledPositionArray[7];
      *((float *)v23 + 2) = m_swizzledPositionArray[11];
      v4 = &v23[this->m_format.m_size];
    }
    if ( v5 < &v5[this->m_numVertices & 3] )
    {
      while ( 1 )
      {
        *(float *)v4 = *v5;
        *((float *)v4 + 1) = v5[4];
        *((float *)v4 + 2) = v5[8];
        v4 += this->m_format.m_size;
      }
    }
  }
  else if ( (this->m_format.m_flags & 1) != 0 )
  {
    m_positionArray = this->m_positionArray;
    v25 = vertexDest;
    switch ( this->m_format.m_dimensions & 7 )
    {
      case 1u:
        v26 = &m_positionArray[this->m_numVertices];
        if ( (4 * this->m_numVertices + 3) / 4 >= 4 )
        {
          do
          {
            *(float *)v25 = *m_positionArray;
            v27 = &v25[this->m_format.m_size];
            *(float *)v27 = m_positionArray[1];
            v28 = &v27[this->m_format.m_size];
            *(float *)v28 = m_positionArray[2];
            v29 = &v28[this->m_format.m_size];
            *(float *)v29 = m_positionArray[3];
            v25 = &v29[this->m_format.m_size];
            m_positionArray += 4;
          }
          while ( (int)m_positionArray < (int)(v26 - 3) );
        }
        for ( ; m_positionArray < v26; ++m_positionArray )
        {
          *(float *)v25 = *m_positionArray;
          v25 += this->m_format.m_size;
        }
        break;
      case 2u:
        for ( i = &m_positionArray[2 * this->m_numVertices]; m_positionArray < i; m_positionArray = (float *)(v32 + 1) )
        {
          v31 = *(_DWORD *)m_positionArray;
          v32 = m_positionArray + 1;
          *(_DWORD *)v25 = v31;
          *((_DWORD *)v25 + 1) = *v32;
          v25 += this->m_format.m_size;
        }
        break;
      case 3u:
        for ( j = &m_positionArray[3 * this->m_numVertices]; m_positionArray < j; m_positionArray = (float *)(v35 + 1) )
        {
          v34 = *(_DWORD *)m_positionArray;
          v35 = (int *)(m_positionArray + 1);
          *(_DWORD *)v25 = v34;
          v36 = *v35++;
          *((_DWORD *)v25 + 1) = v36;
          *((_DWORD *)v25 + 2) = *v35;
          v25 += this->m_format.m_size;
        }
        break;
      case 4u:
        for ( k = &m_positionArray[4 * this->m_numVertices]; m_positionArray < k; m_positionArray = (float *)(v39 + 1) )
        {
          v38 = *(_DWORD *)m_positionArray;
          v39 = (int *)(m_positionArray + 1);
          *(_DWORD *)v25 = v38;
          v40 = *v39++;
          *((_DWORD *)v25 + 1) = v40;
          v41 = *v39++;
          *((_DWORD *)v25 + 2) = v41;
          *((_DWORD *)v25 + 3) = *v39;
          v25 += this->m_format.m_size;
        }
        break;
      default:
        break;
    }
  }
  if ( (this->m_format.m_flags & 4) != 0 )
  {
    m_blendIndexArray = this->m_blendIndexArray;
    v43 = &m_blendIndexArray[this->m_numVertices];
    for ( m = &vertexDest[this->m_format.m_byteOffset[2]]; m_blendIndexArray < v43; ++m_blendIndexArray )
    {
      *(_DWORD *)m = *m_blendIndexArray;
      m += this->m_format.m_size;
    }
  }
  if ( (this->m_format.m_flags & 8) != 0 )
  {
    m_blendWeightArray = this->m_blendWeightArray;
    v46 = &vertexDest[this->m_format.m_byteOffset[3]];
    switch ( (this->m_format.m_dimensions >> 3) & 7 )
    {
      case 1u:
        v47 = &m_blendWeightArray[this->m_numVertices];
        if ( (4 * this->m_numVertices + 3) / 4 >= 4 )
        {
          do
          {
            *(float *)v46 = *m_blendWeightArray;
            v48 = &v46[this->m_format.m_size];
            *(float *)v48 = m_blendWeightArray[1];
            v49 = &v48[this->m_format.m_size];
            *(float *)v49 = m_blendWeightArray[2];
            v50 = &v49[this->m_format.m_size];
            *(float *)v50 = m_blendWeightArray[3];
            v46 = &v50[this->m_format.m_size];
            m_blendWeightArray += 4;
          }
          while ( (int)m_blendWeightArray < (int)(v47 - 3) );
        }
        for ( ; m_blendWeightArray < v47; ++m_blendWeightArray )
        {
          *(float *)v46 = *m_blendWeightArray;
          v46 += this->m_format.m_size;
        }
        break;
      case 2u:
        for ( n = &m_blendWeightArray[2 * this->m_numVertices];
              m_blendWeightArray < n;
              m_blendWeightArray = (float *)(v53 + 1) )
        {
          v52 = *(_DWORD *)m_blendWeightArray;
          v53 = m_blendWeightArray + 1;
          *(_DWORD *)v46 = v52;
          *((_DWORD *)v46 + 1) = *v53;
          v46 += this->m_format.m_size;
        }
        break;
      case 3u:
        for ( ii = &m_blendWeightArray[3 * this->m_numVertices];
              m_blendWeightArray < ii;
              m_blendWeightArray = (float *)(v56 + 1) )
        {
          v55 = *(_DWORD *)m_blendWeightArray;
          v56 = (int *)(m_blendWeightArray + 1);
          *(_DWORD *)v46 = v55;
          v57 = *v56++;
          *((_DWORD *)v46 + 1) = v57;
          *((_DWORD *)v46 + 2) = *v56;
          v46 += this->m_format.m_size;
        }
        break;
      case 4u:
        for ( jj = &m_blendWeightArray[4 * this->m_numVertices];
              m_blendWeightArray < jj;
              m_blendWeightArray = (float *)(v60 + 1) )
        {
          v59 = *(_DWORD *)m_blendWeightArray;
          v60 = (int *)(m_blendWeightArray + 1);
          *(_DWORD *)v46 = v59;
          v61 = *v60++;
          *((_DWORD *)v46 + 1) = v61;
          v62 = *v60++;
          *((_DWORD *)v46 + 2) = v62;
          *((_DWORD *)v46 + 3) = *v60;
          v46 += this->m_format.m_size;
        }
        break;
      default:
        break;
    }
  }
  if ( (this->m_format.m_flags & 0x10) != 0 )
  {
    m_normalArray = this->m_normalArray;
    v64 = &m_normalArray[3 * this->m_numVertices];
    for ( kk = &vertexDest[this->m_format.m_byteOffset[4]]; m_normalArray < v64; m_normalArray = (float *)(v67 + 1) )
    {
      v66 = *(_DWORD *)m_normalArray;
      v67 = (int *)(m_normalArray + 1);
      *(_DWORD *)kk = v66;
      v68 = *v67++;
      *((_DWORD *)kk + 1) = v68;
      *((_DWORD *)kk + 2) = *v67;
      kk += this->m_format.m_size;
    }
  }
  if ( (this->m_format.m_flags & 0x20) != 0 )
  {
    m_tangentArray = this->m_tangentArray;
    v70 = &m_tangentArray[3 * this->m_numVertices];
    for ( mm = &vertexDest[this->m_format.m_byteOffset[5]]; m_tangentArray < v70; m_tangentArray = (float *)(v73 + 1) )
    {
      v72 = *(_DWORD *)m_tangentArray;
      v73 = (int *)(m_tangentArray + 1);
      *(_DWORD *)mm = v72;
      v74 = *v73++;
      *((_DWORD *)mm + 1) = v74;
      *((_DWORD *)mm + 2) = *v73;
      mm += this->m_format.m_size;
    }
  }
  if ( (this->m_format.m_flags & 0x40) != 0 )
  {
    m_binormalArray = this->m_binormalArray;
    v76 = &m_binormalArray[3 * this->m_numVertices];
    for ( nn = &vertexDest[this->m_format.m_byteOffset[6]]; m_binormalArray < v76; m_binormalArray = (float *)(v79 + 1) )
    {
      v78 = *(_DWORD *)m_binormalArray;
      v79 = (int *)(m_binormalArray + 1);
      *(_DWORD *)nn = v78;
      v80 = *v79++;
      *((_DWORD *)nn + 1) = v80;
      *((_DWORD *)nn + 2) = *v79;
      nn += this->m_format.m_size;
    }
  }
  if ( (this->m_format.m_flags & 0x80) != 0 )
  {
    m_diffuseColorArray = this->m_diffuseColorArray;
    v82 = &m_diffuseColorArray[this->m_numVertices];
    for ( i1 = &vertexDest[this->m_format.m_byteOffset[7]]; m_diffuseColorArray < v82; ++m_diffuseColorArray )
    {
      *(_DWORD *)i1 = *m_diffuseColorArray;
      i1 += this->m_format.m_size;
    }
  }
  if ( (this->m_format.m_flags & 0x100) != 0 )
  {
    m_specularColorArray = this->m_specularColorArray;
    v85 = &m_specularColorArray[this->m_numVertices];
    for ( i2 = &vertexDest[this->m_format.m_byteOffset[8]]; m_specularColorArray < v85; ++m_specularColorArray )
    {
      *(_DWORD *)i2 = *m_specularColorArray;
      i2 += this->m_format.m_size;
    }
  }
  if ( (this->m_format.m_flags & 0x200) != 0 )
  {
    m_pointSizeArray = this->m_pointSizeArray;
    v88 = &m_pointSizeArray[this->m_numVertices];
    v89 = &vertexDest[this->m_format.m_byteOffset[9]];
    if ( (4 * this->m_numVertices + 3) / 4 >= 4 )
    {
      do
      {
        *(float *)v89 = *m_pointSizeArray;
        v90 = &v89[this->m_format.m_size];
        *(float *)v90 = m_pointSizeArray[1];
        v91 = &v90[this->m_format.m_size];
        *(float *)v91 = m_pointSizeArray[2];
        v92 = &v91[this->m_format.m_size];
        *(float *)v92 = m_pointSizeArray[3];
        v89 = &v92[this->m_format.m_size];
        m_pointSizeArray += 4;
      }
      while ( (int)m_pointSizeArray < (int)(v88 - 3) );
    }
    for ( ; m_pointSizeArray < v88; ++m_pointSizeArray )
    {
      *(float *)v89 = *m_pointSizeArray;
      v89 += this->m_format.m_size;
    }
  }
  if ( (this->m_format.m_flags & 0x400) != 0 )
  {
    m_texCoordArrays = this->m_texCoordArrays;
    v112 = 7;
    do
    {
      v94 = *m_texCoordArrays;
      if ( *m_texCoordArrays )
      {
        v95 = (unsigned __int8 *)((int)*(m_texCoordArrays - 97) + (_DWORD)vertexDest);
        switch ( this->m_format.m_dimensions & 7 )
        {
          case 1u:
            v96 = &v94[this->m_numVertices];
            if ( (4 * this->m_numVertices + 3) / 4 >= 4 )
            {
              do
              {
                *(float *)v95 = *v94;
                v97 = &v95[this->m_format.m_size];
                *(float *)v97 = v94[1];
                v98 = &v97[this->m_format.m_size];
                *(float *)v98 = v94[2];
                v99 = &v98[this->m_format.m_size];
                *(float *)v99 = v94[3];
                v95 = &v99[this->m_format.m_size];
                v94 += 4;
              }
              while ( (int)v94 < (int)(v96 - 3) );
            }
            for ( ; v94 < v96; ++v94 )
            {
              *(float *)v95 = *v94;
              v95 += this->m_format.m_size;
            }
            break;
          case 2u:
            for ( i3 = &v94[2 * this->m_numVertices]; v94 < i3; v94 = (float *)(v102 + 1) )
            {
              v101 = *(_DWORD *)v94;
              v102 = v94 + 1;
              *(_DWORD *)v95 = v101;
              *((_DWORD *)v95 + 1) = *v102;
              v95 += this->m_format.m_size;
            }
            break;
          case 3u:
            for ( i4 = &v94[3 * this->m_numVertices]; v94 < i4; v94 = (float *)(v105 + 1) )
            {
              v104 = *(_DWORD *)v94;
              v105 = (int *)(v94 + 1);
              *(_DWORD *)v95 = v104;
              v106 = *v105++;
              *((_DWORD *)v95 + 1) = v106;
              *((_DWORD *)v95 + 2) = *v105;
              v95 += this->m_format.m_size;
            }
            break;
          case 4u:
            for ( i5 = &v94[4 * this->m_numVertices]; v94 < i5; v94 = (float *)(v109 + 1) )
            {
              v108 = *(_DWORD *)v94;
              v109 = (int *)(v94 + 1);
              *(_DWORD *)v95 = v108;
              v110 = *v109++;
              *((_DWORD *)v95 + 1) = v110;
              v111 = *v109++;
              *((_DWORD *)v95 + 2) = v111;
              *((_DWORD *)v95 + 3) = *v109;
              v95 += this->m_format.m_size;
            }
            break;
          default:
            break;
        }
      }
      ++m_texCoordArrays;
      --v112;
    }
    while ( v112 );
  }
}

// FUNC: public: void __thiscall rvVertexBuffer::SetupForRender(int,class rvVertexFormat const &)
void __thiscall rvVertexBuffer::SetupForRender(
        rvVertexBuffer *this,
        int vertexStartOffset,
        rvVertexFormat *formatNeeded)
{
  if ( (this->m_flags & 2) != 0 )
  {
    qglBindBufferARB(0x8892u, this->m_vbID);
    rvVertexFormat::SetVertexDeclaration(&this->m_format, vertexStartOffset);
    rvVertexFormat::EnableVertexDeclaration(formatNeeded);
  }
}

// FUNC: protected: class rvSilTraceVertT * __thiscall rvVertexBuffer::GetSilTraceVertexArray(int)
rvSilTraceVertT *__thiscall rvVertexBuffer::GetSilTraceVertexArray(rvVertexBuffer *this, int vertexOffset)
{
  return (rvSilTraceVertT *)&this->m_interleavedStorage[16 * vertexOffset];
}

// FUNC: public: void __thiscall rvVertexBuffer::SetLoadFormat(class rvVertexFormat const &)
void __thiscall rvVertexBuffer::SetLoadFormat(rvVertexBuffer *this, const rvVertexFormat *loadFormat)
{
  rvVertexFormat::Init(&this->m_loadFormat, loadFormat);
}

// FUNC: public: __thiscall rvVertexBuffer::rvVertexBuffer(void)
void __thiscall rvVertexBuffer::rvVertexBuffer(rvVertexBuffer *this)
{
  rvVertexFormat::rvVertexFormat(&this->m_format);
  rvVertexFormat::rvVertexFormat(&this->m_loadFormat);
  rvVertexBuffer::ResetValues(this);
}

// FUNC: public: void __thiscall rvVertexBuffer::Unlock(void)
void __thiscall rvVertexBuffer::Unlock(rvVertexBuffer *this)
{
  unsigned int m_lockStatus; // eax
  int v3; // edi
  unsigned __int8 *v4; // eax

  m_lockStatus = this->m_lockStatus;
  if ( (m_lockStatus & 2) != 0 )
  {
    if ( (m_lockStatus & 4) != 0 )
      this->m_numVerticesWritten = this->m_lockVertexCount;
    else
      this->m_numVerticesWritten += this->m_lockVertexCount;
  }
  if ( (this->m_flags & 1) != 0 )
  {
    if ( (m_lockStatus & 2) != 0 && (this->m_flags & 2) != 0 )
    {
      v3 = this->m_format.m_size * this->m_lockVertexOffset;
      qglBindBufferARB(0x8892u, this->m_vbID);
      if ( (this->m_flags & 4) != 0 )
      {
        v4 = (unsigned __int8 *)qglMapBufferARB(0x8892u, 0x88B9u);
        if ( v4 )
        {
          rvVertexBuffer::TransferSoAToAoS(this, &v4[v3]);
          qglUnmapBufferARB(0x8892u);
          qglBindBufferARB(0x8892u, 0);
          goto LABEL_15;
        }
      }
      else
      {
        qglBufferSubDataARB(
          0x8892u,
          v3,
          this->m_format.m_size * this->m_lockVertexCount,
          &this->m_interleavedStorage[v3]);
      }
      qglBindBufferARB(0x8892u, 0);
    }
  }
  else if ( (this->m_flags & 2) != 0 )
  {
    qglBindBufferARB(0x8892u, this->m_vbID);
    qglUnmapBufferARB(0x8892u);
    qglBindBufferARB(0x8892u, 0);
  }
LABEL_15:
  this->m_lockStatus = 0;
  this->m_lockVertexOffset = 0;
  this->m_lockVertexCount = 0;
  this->m_lockedBase = 0;
}

// FUNC: public: void __thiscall rvVertexBuffer::CopyData(int,int,unsigned char const *,int,class rvVertexFormat const &,unsigned int const *)
void __thiscall rvVertexBuffer::CopyData(
        rvVertexBuffer *this,
        int destVertexOffset,
        int numVertices,
        const unsigned __int8 *srcPtr,
        int srcStride,
        int srcFormat,
        const unsigned int *copyMapping)
{
  const unsigned int *v8; // ebx
  int v9; // ebp
  int v10; // edi
  int v11; // eax
  int v12; // edx
  unsigned __int8 *destPtr; // [esp+4h] [ebp-Ch] BYREF
  int v14; // [esp+8h] [ebp-8h]
  int v15; // [esp+Ch] [ebp-4h]

  if ( rvVertexBuffer::LockInterleaved(this, destVertexOffset, numVertices, 2u, (void **)&destPtr, &destVertexOffset) )
  {
    v8 = copyMapping;
    v9 = srcStride;
    v10 = srcFormat;
    if ( (this->m_format.m_flags & 1) != 0 && (*(_BYTE *)srcFormat & 1) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[this->m_format.m_byteOffset[0]],
        destVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[0],
        this->m_format.m_dimensions & 7,
        &srcPtr[*(_DWORD *)(srcFormat + 16)],
        srcStride,
        (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(srcFormat + 160),
        *(_DWORD *)(srcFormat + 4) & 7,
        numVertices,
        copyMapping,
        0,
        0);
    if ( (this->m_format.m_flags & 4) != 0 && (*(_DWORD *)v10 & 4) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[this->m_format.m_byteOffset[2]],
        destVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[2],
        1,
        &srcPtr[*(_DWORD *)(v10 + 24)],
        v9,
        (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(v10 + 162),
        1,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 8) != 0 && (*(_DWORD *)v10 & 8) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[this->m_format.m_byteOffset[3]],
        destVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[3],
        (this->m_format.m_dimensions >> 3) & 7,
        &srcPtr[*(_DWORD *)(v10 + 28)],
        v9,
        (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(v10 + 163),
        (*(_DWORD *)(v10 + 4) >> 3) & 7,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x10) != 0 && (*(_DWORD *)v10 & 0x10) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[this->m_format.m_byteOffset[4]],
        destVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[4],
        3,
        &srcPtr[*(_DWORD *)(v10 + 32)],
        v9,
        (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(v10 + 164),
        3,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x20) != 0 && (*(_DWORD *)v10 & 0x20) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[this->m_format.m_byteOffset[5]],
        destVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[5],
        3,
        &srcPtr[*(_DWORD *)(v10 + 36)],
        v9,
        (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(v10 + 165),
        3,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x40) != 0 && (*(_DWORD *)v10 & 0x40) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[this->m_format.m_byteOffset[6]],
        destVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[6],
        3,
        &srcPtr[*(_DWORD *)(v10 + 40)],
        v9,
        (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(v10 + 166),
        3,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x80) != 0 && (*(_DWORD *)v10 & 0x80) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[this->m_format.m_byteOffset[7]],
        destVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[7],
        1,
        &srcPtr[*(_DWORD *)(v10 + 44)],
        v9,
        (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(v10 + 167),
        1,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x100) != 0 && (*(_DWORD *)v10 & 0x100) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[this->m_format.m_byteOffset[8]],
        destVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[8],
        1,
        &srcPtr[*(_DWORD *)(v10 + 48)],
        v9,
        (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(v10 + 168),
        1,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x200) != 0 && (*(_DWORD *)v10 & 0x200) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[this->m_format.m_byteOffset[9]],
        destVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[9],
        1,
        &srcPtr[*(_DWORD *)(v10 + 52)],
        v9,
        (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(v10 + 169),
        1,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x400) != 0 && (*(_DWORD *)v10 & 0x400) != 0 )
    {
      copyMapping = (const unsigned int *)&this->m_format.m_byteOffset[10];
      srcStride = 10;
      srcFormat = 9;
      v15 = v10 - (_DWORD)this;
      v14 = 7;
      do
      {
        v11 = (this->m_format.m_dimensions >> srcFormat) & 7;
        v12 = (*(_DWORD *)(v10 + 4) >> srcFormat) & 7;
        if ( v11 )
        {
          if ( v12 )
            rvVertexBuffer::ComponentCopy(
              &destPtr[*copyMapping],
              destVertexOffset,
              (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[srcStride],
              v11,
              &srcPtr[*(const unsigned int *)((char *)copyMapping + v15)],
              v9,
              (Rv_Vertex_Data_Type_t)*(unsigned __int8 *)(srcStride + v10 + 160),
              v12,
              numVertices,
              v8,
              0,
              0);
        }
        ++copyMapping;
        srcFormat += 3;
        ++srcStride;
        --v14;
      }
      while ( v14 );
    }
    rvVertexBuffer::Unlock(this);
  }
  else
  {
    idLib::common->Error(idLib::common, "Vertex buffer cannot be mapped for access");
  }
}

// FUNC: public: void __thiscall rvVertexBuffer::CopyData(unsigned char *,int,class rvVertexFormat const &,int,int,unsigned int const *)
void __thiscall rvVertexBuffer::CopyData(
        rvVertexBuffer *this,
        unsigned __int8 *destPtr,
        int destStride,
        const rvVertexFormat *destFormat,
        int srcVertexOffset,
        int numVertices,
        const unsigned int *copyMapping)
{
  const unsigned int *v8; // ebx
  int v11; // eax
  int v12; // edx
  const unsigned __int8 *srcPtr; // [esp+4h] [ebp-Ch] BYREF
  int v14; // [esp+8h] [ebp-8h]
  int v15; // [esp+Ch] [ebp-4h]
  int destStridea; // [esp+18h] [ebp+8h]
  char destFormata; // [esp+1Ch] [ebp+Ch]

  if ( rvVertexBuffer::LockInterleaved(this, srcVertexOffset, numVertices, 1u, (void **)&srcPtr, &srcVertexOffset) )
  {
    v8 = copyMapping;
    if ( (this->m_format.m_flags & 1) != 0 && (destFormat->m_flags & 1) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[destFormat->m_byteOffset[0]],
        destStride,
        (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[0],
        destFormat->m_dimensions & 7,
        &srcPtr[this->m_format.m_byteOffset[0]],
        srcVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[0],
        this->m_format.m_dimensions & 7,
        numVertices,
        copyMapping,
        0,
        0);
    if ( (this->m_format.m_flags & 4) != 0 && (destFormat->m_flags & 4) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[destFormat->m_byteOffset[2]],
        destStride,
        (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[2],
        1,
        &srcPtr[this->m_format.m_byteOffset[2]],
        srcVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[2],
        1,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 8) != 0 && (destFormat->m_flags & 8) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[destFormat->m_byteOffset[3]],
        destStride,
        (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[3],
        (destFormat->m_dimensions >> 3) & 7,
        &srcPtr[this->m_format.m_byteOffset[3]],
        srcVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[3],
        (this->m_format.m_dimensions >> 3) & 7,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x10) != 0 && (destFormat->m_flags & 0x10) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[destFormat->m_byteOffset[4]],
        destStride,
        (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[4],
        3,
        &srcPtr[this->m_format.m_byteOffset[4]],
        srcVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[4],
        3,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x20) != 0 && (destFormat->m_flags & 0x20) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[destFormat->m_byteOffset[5]],
        destStride,
        (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[5],
        3,
        &srcPtr[this->m_format.m_byteOffset[5]],
        srcVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[5],
        3,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x40) != 0 && (destFormat->m_flags & 0x40) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[destFormat->m_byteOffset[6]],
        destStride,
        (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[6],
        3,
        &srcPtr[this->m_format.m_byteOffset[6]],
        srcVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[6],
        3,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x80) != 0 && (destFormat->m_flags & 0x80) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[destFormat->m_byteOffset[7]],
        destStride,
        (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[7],
        1,
        &srcPtr[this->m_format.m_byteOffset[7]],
        srcVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[7],
        1,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x100) != 0 && (destFormat->m_flags & 0x100) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[destFormat->m_byteOffset[8]],
        destStride,
        (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[8],
        1,
        &srcPtr[this->m_format.m_byteOffset[8]],
        srcVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[8],
        1,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x200) != 0 && (destFormat->m_flags & 0x200) != 0 )
      rvVertexBuffer::ComponentCopy(
        &destPtr[destFormat->m_byteOffset[9]],
        destStride,
        (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[9],
        1,
        &srcPtr[this->m_format.m_byteOffset[9]],
        srcVertexOffset,
        (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[9],
        1,
        numVertices,
        v8,
        0,
        0);
    if ( (this->m_format.m_flags & 0x400) != 0 && (destFormat->m_flags & 0x400) != 0 )
    {
      copyMapping = (const unsigned int *)&destFormat->m_byteOffset[10];
      destStridea = 10;
      destFormata = 9;
      v15 = (char *)this - (char *)destFormat;
      v14 = 7;
      do
      {
        v11 = (destFormat->m_dimensions >> destFormata) & 7;
        v12 = (this->m_format.m_dimensions >> destFormata) & 7;
        if ( v11 )
        {
          if ( v12 )
            rvVertexBuffer::ComponentCopy(
              &destPtr[*copyMapping],
              destStride,
              (Rv_Vertex_Data_Type_t)destFormat->m_dataTypes[destStridea],
              v11,
              &srcPtr[*(const unsigned int *)((char *)copyMapping + v15)],
              srcVertexOffset,
              (Rv_Vertex_Data_Type_t)this->m_format.m_dataTypes[destStridea],
              v12,
              numVertices,
              v8,
              0,
              0);
        }
        ++copyMapping;
        destFormata += 3;
        ++destStridea;
        --v14;
      }
      while ( v14 );
    }
    rvVertexBuffer::Unlock(this);
  }
  else
  {
    idLib::common->Error(idLib::common, "Vertex buffer cannot be mapped for access");
  }
}

// FUNC: public: void __thiscall rvVertexBuffer::Write(class idFile &,char const *)
void __thiscall rvVertexBuffer::Write(rvVertexBuffer *this, idFile *outFile, const char *prepend)
{
  int v4; // eax
  void *v5; // esp
  idFile_vtbl *v7; // eax
  int v8; // eax
  char *v9; // eax
  idFile_vtbl *v10; // ecx
  unsigned int m_flags; // eax
  int v12; // eax
  int v13; // ecx
  unsigned __int8 *v14; // eax
  int m_numValues; // ecx
  int i; // eax
  char *v17; // ecx
  int m_size; // [esp-14h] [ebp-154h]
  int m_numVerticesWritten; // [esp-8h] [ebp-148h]
  char v20[12]; // [esp+0h] [ebp-140h] BYREF
  int tokenSubTypeStructElements[72]; // [esp+Ch] [ebp-134h] BYREF
  int dim; // [esp+12Ch] [ebp-14h]
  char *v23; // [esp+130h] [ebp-10h]
  int v24; // [esp+134h] [ebp-Ch]
  int prependLen; // [esp+138h] [ebp-8h]
  unsigned __int8 *tempVertexData; // [esp+13Ch] [ebp-4h]
  rvVertexBuffer *vertexStorage; // [esp+148h] [ebp+8h]
  unsigned __int8 *vertexStoragea; // [esp+148h] [ebp+8h]
  unsigned __int8 *vertexStorageb; // [esp+148h] [ebp+8h]

  prependLen = strlen(prepend);
  v4 = prependLen + 6;
  LOBYTE(v4) = (prependLen + 6) & 0xFC;
  v5 = alloca(v4);
  v7 = outFile->__vftable;
  tempVertexData = 0;
  v7->WriteFloatString(outFile, "%sVertexBuffer\n", prepend);
  outFile->WriteFloatString(outFile, "%s{\n", prepend);
  strcpy(v20, prepend);
  v8 = prependLen;
  v20[prependLen] = 9;
  v9 = &v20[v8 + 1];
  *v9 = 0;
  v10 = outFile->__vftable;
  v23 = v9;
  v10->WriteFloatString(outFile, "%sVertexFormat ", v20);
  m_flags = this->m_flags;
  if ( (m_flags & 0x20) == 0 || (m_flags & 4) != 0 )
    vertexStorage = this;
  else
    vertexStorage = (rvVertexBuffer *)&this->m_loadFormat;
  rvVertexFormat::Write(&vertexStorage->m_format, outFile, v20);
  if ( (vertexStorage->m_format.m_flags != this->m_loadFormat.m_flags
     || vertexStorage->m_format.m_dimensions != this->m_loadFormat.m_dimensions)
    && (this->m_flags & 4) == 0 )
  {
    outFile->WriteFloatString(outFile, "%sLoadVertexFormat ", v20);
    rvVertexFormat::Write(&this->m_loadFormat, outFile, v20);
  }
  if ( (this->m_flags & 1) != 0 )
    outFile->WriteFloatString(outFile, "%sSystemMemory\n", v20);
  if ( (this->m_flags & 2) != 0 )
    outFile->WriteFloatString(outFile, "%sVideoMemory\n", v20);
  if ( (this->m_flags & 4) != 0 )
    outFile->WriteFloatString(outFile, "%sSoA\n", v20);
  outFile->WriteFloatString(outFile, "%sVertex[ %d ]\n", v20, this->m_numVerticesWritten);
  outFile->WriteFloatString(outFile, "%s{\n", v20);
  if ( (this->m_flags & 0x10) == 0 )
  {
    v12 = prependLen;
    *v23 = 9;
    v20[v12 + 2] = 0;
    if ( (this->m_flags & 4) != 0 )
    {
      if ( (this->m_format.m_flags & 2) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(
          &this->m_format,
          RV_VERTEX_COMPONENT_SWIZZLED_POSITION,
          tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          3,
          tokenSubTypeStructElements,
          (this->m_numVerticesWritten + 3) & 0xFFFFFFFC,
          (unsigned __int8 *)this->m_swizzledPositionArray,
          v20);
      }
      else if ( (this->m_format.m_flags & 1) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_POSITION, tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          this->m_format.m_dimensions & 7,
          tokenSubTypeStructElements,
          this->m_numVerticesWritten,
          (unsigned __int8 *)this->m_positionArray,
          v20);
      }
      if ( (this->m_format.m_flags & 4) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_BLEND_INDEX, tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          1,
          tokenSubTypeStructElements,
          this->m_numVerticesWritten,
          (unsigned __int8 *)this->m_blendIndexArray,
          v20);
      }
      if ( (this->m_format.m_flags & 8) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_BLEND_WEIGHT, tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          (this->m_format.m_dimensions >> 3) & 7,
          tokenSubTypeStructElements,
          this->m_numVerticesWritten,
          (unsigned __int8 *)this->m_blendWeightArray,
          v20);
      }
      if ( (this->m_format.m_flags & 0x10) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_NORMAL, tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          3,
          tokenSubTypeStructElements,
          this->m_numVerticesWritten,
          (unsigned __int8 *)this->m_normalArray,
          v20);
      }
      if ( (this->m_format.m_flags & 0x20) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_TANGENT, tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          3,
          tokenSubTypeStructElements,
          this->m_numVerticesWritten,
          (unsigned __int8 *)this->m_tangentArray,
          v20);
      }
      if ( (this->m_format.m_flags & 0x40) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_BINORMAL, tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          3,
          tokenSubTypeStructElements,
          this->m_numVerticesWritten,
          (unsigned __int8 *)this->m_binormalArray,
          v20);
      }
      if ( (this->m_format.m_flags & 0x80) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_DIFFUSE_COLOR, tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          1,
          tokenSubTypeStructElements,
          this->m_numVerticesWritten,
          (unsigned __int8 *)this->m_diffuseColorArray,
          v20);
      }
      if ( (this->m_format.m_flags & 0x100) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(
          &this->m_format,
          RV_VERTEX_COMPONENT_SPECULAR_COLOR,
          tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          1,
          tokenSubTypeStructElements,
          this->m_numVerticesWritten,
          (unsigned __int8 *)this->m_specularColorArray,
          v20);
      }
      if ( (this->m_format.m_flags & 0x200) != 0 )
      {
        rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_POINT_SIZE, tokenSubTypeStructElements);
        outFile->WriteNumericStructArray(
          outFile,
          1,
          tokenSubTypeStructElements,
          this->m_numVerticesWritten,
          (unsigned __int8 *)this->m_pointSizeArray,
          v20);
      }
      if ( (this->m_format.m_flags & 0x400) != 0 )
      {
        v13 = 9;
        vertexStoragea = 0;
        v24 = 9;
        tempVertexData = (unsigned __int8 *)this->m_texCoordArrays;
        do
        {
          dim = (this->m_format.m_dimensions >> v13) & 7;
          if ( dim )
          {
            rvVertexFormat::GetTokenSubTypes(
              &this->m_format,
              (Rv_Vertex_Component_t)(vertexStoragea + 10),
              tokenSubTypeStructElements);
            outFile->WriteNumericStructArray(
              outFile,
              dim,
              tokenSubTypeStructElements,
              this->m_numVerticesWritten,
              *(unsigned __int8 **)tempVertexData,
              v20);
            v13 = v24;
          }
          ++vertexStoragea;
          tempVertexData += 4;
          v13 += 3;
          v24 = v13;
        }
        while ( v13 < 30 );
      }
    }
    else
    {
      if ( (this->m_flags & 1) != 0 )
      {
        vertexStorageb = this->m_interleavedStorage;
      }
      else
      {
        qglBindBufferARB(0x8892u, this->m_vbID);
        vertexStorageb = (unsigned __int8 *)qglMapBufferARB(0x8892u, 0x88B9u);
        if ( !vertexStorageb )
        {
          idLib::common->Error(idLib::common, "Vertex buffer cannot be mapped for access");
          return;
        }
      }
      if ( !rvVertexFormat::HasSameDataTypes(&this->m_loadFormat, &this->m_format) )
      {
        v14 = (unsigned __int8 *)Mem_Alloc16(this->m_loadFormat.m_size * this->m_numVerticesWritten, 0x11u);
        m_numVerticesWritten = this->m_numVerticesWritten;
        m_size = this->m_loadFormat.m_size;
        tempVertexData = v14;
        rvVertexBuffer::CopyData(this, v14, m_size, &this->m_loadFormat, 0, m_numVerticesWritten, 0);
        vertexStorageb = tempVertexData;
      }
      m_numValues = this->m_loadFormat.m_numValues;
      for ( i = 0; i < m_numValues; ++i )
        tokenSubTypeStructElements[i] = this->m_loadFormat.m_tokenSubTypes[i];
      outFile->WriteNumericStructArray(
        outFile,
        this->m_loadFormat.m_numValues,
        tokenSubTypeStructElements,
        this->m_numVerticesWritten,
        vertexStorageb,
        v20);
      if ( tempVertexData )
        Mem_Free16(tempVertexData);
      if ( (this->m_flags & 1) == 0 )
        qglUnmapBufferARB(0x8892u);
    }
    v17 = v23;
    v20[prependLen] = 9;
    *v17 = 0;
  }
  outFile->WriteFloatString(outFile, "%s}\n", v20);
  outFile->WriteFloatString(outFile, "%s}\n", prepend);
}

// FUNC: public: void __thiscall rvVertexBuffer::Shutdown(void)
void __thiscall rvVertexBuffer::Shutdown(rvVertexBuffer *this)
{
  void **m_texCoordArrays; // edi
  int v3; // ebx

  if ( this->m_lockStatus )
    rvVertexBuffer::Unlock(this);
  if ( this->m_interleavedStorage )
    Mem_Free16(this->m_interleavedStorage);
  if ( this->m_positionArray )
    Mem_Free16(this->m_positionArray);
  if ( this->m_swizzledPositionArray )
    Mem_Free16(this->m_swizzledPositionArray);
  if ( this->m_blendIndexArray )
    Mem_Free16(this->m_blendIndexArray);
  if ( this->m_blendWeightArray )
    Mem_Free16(this->m_blendWeightArray);
  if ( this->m_normalArray )
    Mem_Free16(this->m_normalArray);
  if ( this->m_tangentArray )
    Mem_Free16(this->m_tangentArray);
  if ( this->m_binormalArray )
    Mem_Free16(this->m_binormalArray);
  if ( this->m_diffuseColorArray )
    Mem_Free16(this->m_diffuseColorArray);
  if ( this->m_specularColorArray )
    Mem_Free16(this->m_specularColorArray);
  if ( this->m_pointSizeArray )
    Mem_Free16(this->m_pointSizeArray);
  m_texCoordArrays = (void **)this->m_texCoordArrays;
  v3 = 7;
  do
  {
    if ( *m_texCoordArrays )
      Mem_Free16(*m_texCoordArrays);
    ++m_texCoordArrays;
    --v3;
  }
  while ( v3 );
  if ( this->m_vbID )
    qglDeleteBuffersARB(1, &this->m_vbID);
  rvVertexFormat::Shutdown(&this->m_format);
  rvVertexFormat::Shutdown(&this->m_loadFormat);
  rvVertexBuffer::ResetValues(this);
}

// FUNC: public: void __thiscall rvVertexBuffer::Resize(int)
void __thiscall rvVertexBuffer::Resize(rvVertexBuffer *this, int numVertices)
{
  int v2; // ebp
  int m_numVertices; // edi
  void *v5; // ebx
  int v6; // eax
  void *v7; // ebx
  int v8; // eax
  void *v9; // ebx
  void *v10; // ebx
  void *v11; // ebx
  void *v12; // ebx
  void *v13; // ebx
  void *v14; // ebx
  void *v15; // ebx
  void *v16; // ebx
  char v17; // cl
  float **m_texCoordArrays; // ebx
  void *v19; // edi
  unsigned __int8 *v20; // eax
  void *v21; // ebx
  bool v22; // zf
  int numCopyVerts; // [esp+54h] [ebp-8h]
  int v24; // [esp+58h] [ebp-4h]

  v2 = numVertices;
  m_numVertices = this->m_numVertices;
  if ( numVertices != m_numVertices && (this->m_flags & 1) != 0 )
  {
    numCopyVerts = this->m_numVertices;
    if ( m_numVertices > numVertices )
    {
      numCopyVerts = numVertices;
      m_numVertices = numVertices;
    }
    if ( (this->m_flags & 4) != 0 )
    {
      if ( (this->m_format.m_flags & 1) != 0 )
      {
        v5 = Mem_Alloc16(4 * numVertices * (this->m_format.m_dimensions & 7), 0x11u);
        LOBYTE(numVertices) = (v5 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          SIMDProcessor->Memcpy(
            SIMDProcessor,
            v5,
            this->m_positionArray,
            4 * m_numVertices * (this->m_format.m_dimensions & 7));
          Mem_Free16(this->m_positionArray);
          this->m_positionArray = (float *)v5;
        }
      }
      if ( (this->m_format.m_flags & 2) != 0 )
      {
        v6 = v2 + 3;
        LOBYTE(v6) = (v2 + 3) & 0xFC;
        v7 = Mem_Alloc16(12 * v6, 0x11u);
        LOBYTE(numVertices) = (v7 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          v8 = m_numVertices + 3;
          LOBYTE(v8) = (m_numVertices + 3) & 0xFC;
          SIMDProcessor->Memcpy(SIMDProcessor, v7, this->m_swizzledPositionArray, 12 * v8);
          Mem_Free16(this->m_swizzledPositionArray);
          this->m_swizzledPositionArray = (float *)v7;
        }
      }
      if ( (this->m_format.m_flags & 4) != 0 )
      {
        v9 = Mem_Alloc16(4 * v2, 0x11u);
        LOBYTE(numVertices) = (v9 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          SIMDProcessor->Memcpy(SIMDProcessor, v9, this->m_blendIndexArray, 4 * m_numVertices);
          Mem_Free16(this->m_blendIndexArray);
          this->m_blendIndexArray = (unsigned int *)v9;
        }
      }
      if ( (this->m_format.m_flags & 8) != 0 )
      {
        v10 = Mem_Alloc16(4 * v2 * ((this->m_format.m_dimensions >> 3) & 7), 0x11u);
        LOBYTE(numVertices) = (v10 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          SIMDProcessor->Memcpy(
            SIMDProcessor,
            v10,
            this->m_blendWeightArray,
            4 * m_numVertices * ((this->m_format.m_dimensions >> 3) & 7));
          Mem_Free16(this->m_blendWeightArray);
          this->m_blendWeightArray = (float *)v10;
        }
      }
      if ( (this->m_format.m_flags & 0x10) != 0 )
      {
        v11 = Mem_Alloc16(12 * v2, 0x11u);
        LOBYTE(numVertices) = (v11 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          SIMDProcessor->Memcpy(SIMDProcessor, v11, this->m_normalArray, 12 * m_numVertices);
          Mem_Free16(this->m_normalArray);
          this->m_normalArray = (float *)v11;
        }
      }
      if ( (this->m_format.m_flags & 0x20) != 0 )
      {
        v12 = Mem_Alloc16(12 * v2, 0x11u);
        LOBYTE(numVertices) = (v12 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          SIMDProcessor->Memcpy(SIMDProcessor, v12, this->m_tangentArray, 12 * m_numVertices);
          Mem_Free16(this->m_tangentArray);
          this->m_tangentArray = (float *)v12;
        }
      }
      if ( (this->m_format.m_flags & 0x40) != 0 )
      {
        v13 = Mem_Alloc16(12 * v2, 0x11u);
        LOBYTE(numVertices) = (v13 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          SIMDProcessor->Memcpy(SIMDProcessor, v13, this->m_binormalArray, 12 * m_numVertices);
          Mem_Free16(this->m_binormalArray);
          this->m_binormalArray = (float *)v13;
        }
      }
      if ( (this->m_format.m_flags & 0x80) != 0 )
      {
        v14 = Mem_Alloc16(4 * v2, 0x11u);
        LOBYTE(numVertices) = (v14 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          SIMDProcessor->Memcpy(SIMDProcessor, v14, this->m_diffuseColorArray, 4 * m_numVertices);
          Mem_Free16(this->m_diffuseColorArray);
          this->m_diffuseColorArray = (unsigned int *)v14;
        }
      }
      if ( (this->m_format.m_flags & 0x100) != 0 )
      {
        v15 = Mem_Alloc16(4 * v2, 0x11u);
        LOBYTE(numVertices) = (v15 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          SIMDProcessor->Memcpy(SIMDProcessor, v15, this->m_specularColorArray, 4 * m_numVertices);
          Mem_Free16(this->m_specularColorArray);
          this->m_specularColorArray = (unsigned int *)v15;
        }
      }
      if ( (this->m_format.m_flags & 0x200) != 0 )
      {
        v16 = Mem_Alloc16(4 * v2, 0x11u);
        LOBYTE(numVertices) = (v16 == 0) | numVertices;
        if ( !(_BYTE)numVertices )
        {
          SIMDProcessor->Memcpy(SIMDProcessor, v16, this->m_pointSizeArray, 4 * m_numVertices);
          Mem_Free16(this->m_pointSizeArray);
          this->m_pointSizeArray = (float *)v16;
        }
      }
      if ( (this->m_format.m_flags & 0x400) != 0 )
      {
        v17 = 9;
        v24 = 9;
        m_texCoordArrays = this->m_texCoordArrays;
        do
        {
          if ( ((this->m_format.m_dimensions >> v17) & 7) != 0 )
          {
            v19 = Mem_Alloc16(4 * v2 * ((this->m_format.m_dimensions >> v17) & 7), 0x11u);
            LOBYTE(numVertices) = (v19 == 0) | numVertices;
            if ( !(_BYTE)numVertices )
            {
              SIMDProcessor->Memcpy(
                SIMDProcessor,
                v19,
                *m_texCoordArrays,
                4 * numCopyVerts * ((this->m_format.m_dimensions >> v24) & 7));
              Mem_Free16(*m_texCoordArrays);
              *m_texCoordArrays = (float *)v19;
            }
          }
          v17 = v24 + 3;
          ++m_texCoordArrays;
          v24 += 3;
        }
        while ( v24 < 30 );
      }
      if ( !(_BYTE)numVertices )
      {
        if ( (this->m_flags & 2) != 0 )
        {
          qglBindBufferARB(0x8892u, this->m_vbID);
          v20 = (unsigned __int8 *)qglMapBufferARB(0x8892u, 0x88B9u);
          if ( v20 )
          {
            rvVertexBuffer::TransferSoAToAoS(this, v20);
            qglUnmapBufferARB(0x8892u);
          }
        }
LABEL_46:
        this->m_numVertices = v2;
        return;
      }
    }
    else
    {
      v21 = Mem_Alloc16(numVertices * this->m_format.m_size, 0x11u);
      if ( v21 )
      {
        SIMDProcessor->Memcpy(SIMDProcessor, v21, this->m_interleavedStorage, m_numVertices * this->m_format.m_size);
        Mem_Free16(this->m_interleavedStorage);
        v22 = (this->m_flags & 2) == 0;
        this->m_interleavedStorage = (unsigned __int8 *)v21;
        if ( !v22 )
        {
          qglBindBufferARB(0x8892u, this->m_vbID);
          qglBufferDataARB(0x8892u, numVertices * this->m_format.m_size, this->m_interleavedStorage, 0x88E4u);
          qglBindBufferARB(0x8892u, 0);
          this->m_numVertices = numVertices;
          return;
        }
        goto LABEL_46;
      }
    }
    idLib::common->Error(idLib::common, "Ran out of memory trying to allocate system memory vertex storage");
    rvVertexBuffer::Shutdown(this);
  }
}

// FUNC: public: bool __thiscall rvVertexBuffer::LockPosition(int,int,unsigned int,unsigned char * &,int &)
char __thiscall rvVertexBuffer::LockPosition(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVerticesToLock,
        unsigned int lockFlags,
        unsigned __int8 **posPtr,
        int *stride)
{
  bool v7; // zf
  float *m_positionArray; // ecx
  char result; // al

  v7 = (this->m_flags & 4) == 0;
  this->m_lockVertexOffset = vertexBufferOffset;
  this->m_lockVertexCount = numVerticesToLock;
  if ( v7 )
  {
    result = rvVertexBuffer::LockInterleaved(
               this,
               vertexBufferOffset,
               numVerticesToLock,
               lockFlags,
               (void **)posPtr,
               stride);
    if ( result )
    {
      *posPtr += this->m_format.m_byteOffset[0];
      return 1;
    }
  }
  else
  {
    m_positionArray = this->m_positionArray;
    this->m_lockStatus = lockFlags;
    *posPtr = (unsigned __int8 *)m_positionArray;
    *stride = 4 * (this->m_format.m_dimensions & 7);
    return 1;
  }
  return result;
}

// FUNC: public: bool __thiscall rvVertexBuffer::LockBlendIndex(int,int,unsigned int,unsigned char * &,int &)
char __thiscall rvVertexBuffer::LockBlendIndex(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVerticesToLock,
        unsigned int lockFlags,
        unsigned __int8 **blendIndexPtr,
        int *stride)
{
  bool v7; // zf
  unsigned __int8 *m_blendIndexArray; // ecx
  char result; // al

  v7 = (this->m_flags & 4) == 0;
  this->m_lockVertexOffset = vertexBufferOffset;
  this->m_lockVertexCount = numVerticesToLock;
  if ( v7 )
  {
    result = rvVertexBuffer::LockInterleaved(
               this,
               vertexBufferOffset,
               numVerticesToLock,
               lockFlags,
               (void **)blendIndexPtr,
               stride);
    if ( result )
    {
      *blendIndexPtr += this->m_format.m_byteOffset[2];
      return 1;
    }
  }
  else
  {
    m_blendIndexArray = (unsigned __int8 *)this->m_blendIndexArray;
    this->m_lockStatus = lockFlags;
    *blendIndexPtr = m_blendIndexArray;
    *stride = 4;
    return 1;
  }
  return result;
}

// FUNC: public: bool __thiscall rvVertexBuffer::LockBlendWeight(int,int,unsigned int,unsigned char * &,int &)
char __thiscall rvVertexBuffer::LockBlendWeight(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVerticesToLock,
        unsigned int lockFlags,
        unsigned __int8 **blendWeightPtr,
        int *stride)
{
  bool v7; // zf
  float *m_blendWeightArray; // ecx
  char result; // al

  v7 = (this->m_flags & 4) == 0;
  this->m_lockVertexOffset = vertexBufferOffset;
  this->m_lockVertexCount = numVerticesToLock;
  if ( v7 )
  {
    result = rvVertexBuffer::LockInterleaved(
               this,
               vertexBufferOffset,
               numVerticesToLock,
               lockFlags,
               (void **)blendWeightPtr,
               stride);
    if ( result )
    {
      *blendWeightPtr += this->m_format.m_byteOffset[3];
      return 1;
    }
  }
  else
  {
    m_blendWeightArray = this->m_blendWeightArray;
    this->m_lockStatus = lockFlags;
    *blendWeightPtr = (unsigned __int8 *)m_blendWeightArray;
    *stride = 4 * ((this->m_format.m_dimensions >> 3) & 7);
    return 1;
  }
  return result;
}

// FUNC: public: bool __thiscall rvVertexBuffer::LockNormal(int,int,unsigned int,unsigned char * &,int &)
char __thiscall rvVertexBuffer::LockNormal(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVerticesToLock,
        unsigned int lockFlags,
        unsigned __int8 **normalPtr,
        int *stride)
{
  bool v7; // zf
  float *m_normalArray; // ecx
  char result; // al

  v7 = (this->m_flags & 4) == 0;
  this->m_lockVertexOffset = vertexBufferOffset;
  this->m_lockVertexCount = numVerticesToLock;
  if ( v7 )
  {
    result = rvVertexBuffer::LockInterleaved(
               this,
               vertexBufferOffset,
               numVerticesToLock,
               lockFlags,
               (void **)normalPtr,
               stride);
    if ( result )
    {
      *normalPtr += this->m_format.m_byteOffset[4];
      return 1;
    }
  }
  else
  {
    m_normalArray = this->m_normalArray;
    this->m_lockStatus = lockFlags;
    *normalPtr = (unsigned __int8 *)m_normalArray;
    *stride = 12;
    return 1;
  }
  return result;
}

// FUNC: public: bool __thiscall rvVertexBuffer::LockTangent(int,int,unsigned int,unsigned char * &,int &)
char __thiscall rvVertexBuffer::LockTangent(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVerticesToLock,
        unsigned int lockFlags,
        unsigned __int8 **tangentPtr,
        int *stride)
{
  bool v7; // zf
  float *m_tangentArray; // ecx
  char result; // al

  v7 = (this->m_flags & 4) == 0;
  this->m_lockVertexOffset = vertexBufferOffset;
  this->m_lockVertexCount = numVerticesToLock;
  if ( v7 )
  {
    result = rvVertexBuffer::LockInterleaved(
               this,
               vertexBufferOffset,
               numVerticesToLock,
               lockFlags,
               (void **)tangentPtr,
               stride);
    if ( result )
    {
      *tangentPtr += this->m_format.m_byteOffset[5];
      return 1;
    }
  }
  else
  {
    m_tangentArray = this->m_tangentArray;
    this->m_lockStatus = lockFlags;
    *tangentPtr = (unsigned __int8 *)m_tangentArray;
    *stride = 12;
    return 1;
  }
  return result;
}

// FUNC: public: bool __thiscall rvVertexBuffer::LockBinormal(int,int,unsigned int,unsigned char * &,int &)
char __thiscall rvVertexBuffer::LockBinormal(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVerticesToLock,
        unsigned int lockFlags,
        unsigned __int8 **binormalPtr,
        int *stride)
{
  bool v7; // zf
  float *m_binormalArray; // ecx
  char result; // al

  v7 = (this->m_flags & 4) == 0;
  this->m_lockVertexOffset = vertexBufferOffset;
  this->m_lockVertexCount = numVerticesToLock;
  if ( v7 )
  {
    result = rvVertexBuffer::LockInterleaved(
               this,
               vertexBufferOffset,
               numVerticesToLock,
               lockFlags,
               (void **)binormalPtr,
               stride);
    if ( result )
    {
      *binormalPtr += this->m_format.m_byteOffset[6];
      return 1;
    }
  }
  else
  {
    m_binormalArray = this->m_binormalArray;
    this->m_lockStatus = lockFlags;
    *binormalPtr = (unsigned __int8 *)m_binormalArray;
    *stride = 12;
    return 1;
  }
  return result;
}

// FUNC: public: bool __thiscall rvVertexBuffer::LockDiffuseColor(int,int,unsigned int,unsigned char * &,int &)
char __thiscall rvVertexBuffer::LockDiffuseColor(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVerticesToLock,
        unsigned int lockFlags,
        unsigned __int8 **diffuseColorPtr,
        int *stride)
{
  bool v7; // zf
  unsigned __int8 *m_diffuseColorArray; // ecx
  char result; // al

  v7 = (this->m_flags & 4) == 0;
  this->m_lockVertexOffset = vertexBufferOffset;
  this->m_lockVertexCount = numVerticesToLock;
  if ( v7 )
  {
    result = rvVertexBuffer::LockInterleaved(
               this,
               vertexBufferOffset,
               numVerticesToLock,
               lockFlags,
               (void **)diffuseColorPtr,
               stride);
    if ( result )
    {
      *diffuseColorPtr += this->m_format.m_byteOffset[7];
      return 1;
    }
  }
  else
  {
    m_diffuseColorArray = (unsigned __int8 *)this->m_diffuseColorArray;
    this->m_lockStatus = lockFlags;
    *diffuseColorPtr = m_diffuseColorArray;
    *stride = 4;
    return 1;
  }
  return result;
}

// FUNC: public: bool __thiscall rvVertexBuffer::LockTextureCoordinate(int,int,int,unsigned int,unsigned char * &,int &)
char __thiscall rvVertexBuffer::LockTextureCoordinate(
        rvVertexBuffer *this,
        int texCoordOffset,
        int vertexBufferOffset,
        int numVerticesToLock,
        unsigned int lockFlags,
        unsigned __int8 **texCoordPtr,
        int *stride)
{
  bool v8; // zf
  char result; // al

  v8 = (this->m_flags & 4) == 0;
  this->m_lockVertexOffset = vertexBufferOffset;
  this->m_lockVertexCount = numVerticesToLock;
  if ( v8 )
  {
    result = rvVertexBuffer::LockInterleaved(
               this,
               vertexBufferOffset,
               numVerticesToLock,
               lockFlags,
               (void **)texCoordPtr,
               stride);
    if ( result )
    {
      *texCoordPtr += this->m_format.m_byteOffset[texCoordOffset + 10];
      return 1;
    }
  }
  else
  {
    this->m_lockStatus = lockFlags;
    *texCoordPtr = (unsigned __int8 *)this->m_texCoordArrays[texCoordOffset];
    *stride = 4 * ((this->m_format.m_dimensions >> (3 * texCoordOffset + 9)) & 7);
    return 1;
  }
  return result;
}

// FUNC: public: void __thiscall rvVertexBuffer::CopyRemappedData(int,int,unsigned int *,unsigned int *,class rvBlend4DrawVert *,bool)
void __thiscall rvVertexBuffer::CopyRemappedData(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVertices,
        unsigned int *copyMapping,
        unsigned int *transformMapOldToNew,
        rvBlend4DrawVert *srcVertData,
        float *absBlendWeights)
{
  int v7; // ebx
  rvVertexBuffer *v8; // ebp
  bool v9; // cc
  rvBlend4DrawVert *v10; // esi
  int v11; // edx
  int v12; // edi
  unsigned int *v13; // ecx
  rvBlend4DrawVert *v14; // eax
  float *p_x; // edi
  float *v16; // edi
  char *v17; // eax
  _DWORD *v18; // edi
  char *v19; // eax
  _DWORD *v20; // edi
  char *v21; // eax
  float *v22; // ecx
  int v23; // ecx
  unsigned __int8 *v24; // edi
  _DWORD *v25; // eax
  signed int v26; // ebp
  float *v27; // edx
  int v28; // edi
  int v29; // eax
  float *p_z; // ecx
  unsigned int v31; // edx
  long double v32; // st7
  float *v33; // eax
  rvBlend4DrawVert *v34; // ecx
  long double v35; // st7
  int v36; // eax
  rvBlend4DrawVert *v37; // ecx
  float *v38; // eax
  int v39; // edi
  _DWORD *v40; // eax
  _DWORD *v41; // ecx
  unsigned int v42; // edx
  _DWORD *v43; // eax
  rvVertexBuffer *v44; // eax
  bool v45; // zf
  int v46; // edx
  rvBlend4DrawVert *m_normalArray; // eax
  rvVertexBuffer *v48; // edi
  bool v49; // al
  int v50; // edi
  unsigned int *v51; // ecx
  _DWORD *v52; // edi
  _DWORD *v53; // edi
  char *v54; // eax
  _DWORD *v55; // edi
  char *v56; // eax
  _DWORD *v57; // edi
  char *v58; // eax
  _DWORD *v59; // ecx
  rvVertexBuffer *v60; // ebp
  rvBlend4DrawVert *m_tangentArray; // eax
  int v62; // edx
  bool v63; // al
  int v64; // ecx
  unsigned int *v65; // ecx
  _DWORD *v66; // edi
  _DWORD *v67; // edi
  char *v68; // eax
  _DWORD *v69; // edi
  char *v70; // eax
  _DWORD *v71; // edi
  char *v72; // eax
  _DWORD *v73; // ecx
  rvBlend4DrawVert *m_binormalArray; // eax
  int v75; // edx
  bool v76; // al
  int v77; // edi
  unsigned int *v78; // ecx
  _DWORD *v79; // edi
  _DWORD *v80; // edi
  char *v81; // eax
  _DWORD *v82; // edi
  char *v83; // eax
  _DWORD *v84; // edi
  char *v85; // eax
  _DWORD *v86; // ecx
  float *m_diffuseColorArray; // edx
  bool v88; // al
  int i; // ecx
  int v90; // edx
  int v91; // edi
  unsigned int *v92; // ecx
  rvBlend4DrawVert *v93; // eax
  rvBlend4DrawVert *v94; // edi
  rvBlend4DrawVert *v95; // edi
  char *v96; // eax
  rvBlend4DrawVert *v97; // edi
  char *v98; // eax
  rvBlend4DrawVert *v99; // edi
  char *v100; // eax
  rvBlend4DrawVert *v101; // ecx
  int stride; // [esp+8h] [ebp-10h] BYREF
  int curVertex; // [esp+Ch] [ebp-Ch]
  rvVertexBuffer *v104; // [esp+10h] [ebp-8h]
  unsigned __int8 *bytePtr; // [esp+14h] [ebp-4h] BYREF

  v7 = numVertices;
  v8 = this;
  v9 = numVertices + vertexBufferOffset <= this->m_numVertices;
  v104 = this;
  if ( !v9 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "rvVertexBuffer: attempt to copy vertex data out-of-bounds");
    return;
  }
  v10 = srcVertData;
  if ( (this->m_format.m_flags & 1) != 0 && (this->m_format.m_dimensions & 7) >= 3 )
  {
    rvVertexBuffer::LockPosition(this, vertexBufferOffset, numVertices, 2u, (unsigned __int8 **)&srcVertData, &stride);
    v11 = stride;
    v12 = 0;
    if ( numVertices < 4 )
    {
      v14 = srcVertData;
    }
    else
    {
      bytePtr = (unsigned __int8 *)(((unsigned int)(numVertices - 4) >> 2) + 1);
      v13 = copyMapping + 2;
      curVertex = 4 * (_DWORD)bytePtr;
      v14 = srcVertData;
      do
      {
        p_x = &v10[*(v13 - 2)].xyz.x;
        v14->xyz.x = *p_x;
        v14->xyz.y = p_x[1];
        v14->xyz.z = p_x[2];
        v16 = &v10[*(v13 - 1)].xyz.x;
        *(float *)((char *)&v14->xyz.x + v11) = *v16;
        *(float *)((char *)&v14->xyz.y + v11) = v16[1];
        *(float *)((char *)&v14->xyz.z + v11) = v16[2];
        v17 = (char *)v14 + v11;
        v18 = (_DWORD *)&v10[*v13].xyz.x;
        *(_DWORD *)&v17[v11] = *v18;
        *(_DWORD *)&v17[v11 + 4] = v18[1];
        v19 = &v17[v11];
        *((_DWORD *)v19 + 2) = v18[2];
        v20 = (_DWORD *)&v10[v13[1]].xyz.x;
        v21 = &v19[v11];
        *(_DWORD *)v21 = *v20;
        *((_DWORD *)v21 + 1) = v20[1];
        *((_DWORD *)v21 + 2) = v20[2];
        v14 = (rvBlend4DrawVert *)&v21[v11];
        v13 += 4;
        --bytePtr;
      }
      while ( bytePtr );
      v12 = curVertex;
      v8 = v104;
      srcVertData = v14;
    }
    if ( v12 < numVertices )
    {
      do
      {
        v22 = &v10[copyMapping[v12]].xyz.x;
        v14->xyz.x = *v22;
        v14->xyz.y = v22[1];
        v14->xyz.z = v22[2];
        ++v12;
        v14 = (rvBlend4DrawVert *)((char *)v14 + v11);
      }
      while ( v12 < numVertices );
      v8 = v104;
      srcVertData = v14;
    }
  }
  if ( (v8->m_format.m_flags & 4) != 0 )
  {
    rvVertexBuffer::LockBlendIndex(v104, vertexBufferOffset, numVertices, 2u, &bytePtr, &stride);
    v23 = 0;
    if ( numVertices > 0 )
    {
      v24 = bytePtr;
      do
      {
        v25 = (_DWORD *)&v10[copyMapping[v23]].xyz.x;
        *v24 = transformMapOldToNew[v25[3]];
        v24[1] = transformMapOldToNew[v25[4]];
        v24[2] = transformMapOldToNew[v25[5]];
        v24[3] = transformMapOldToNew[v25[6]];
        v24 += stride;
        ++v23;
      }
      while ( v23 < numVertices );
    }
  }
  if ( (v104->m_format.m_flags & 8) != 0 )
  {
    v26 = (v104->m_format.m_dimensions >> 3) & 7;
    rvVertexBuffer::LockBlendWeight(
      v104,
      vertexBufferOffset,
      numVertices,
      2u,
      (unsigned __int8 **)&srcVertData,
      &stride);
    if ( (_BYTE)absBlendWeights )
    {
      curVertex = 0;
      if ( numVertices > 0 )
      {
        do
        {
          v27 = (float *)copyMapping[curVertex];
          v28 = 0;
          absBlendWeights = v27;
          if ( v26 >= 4 )
          {
            v29 = (int)&v10[(_DWORD)v27].blendWeight[1];
            p_z = &srcVertData->xyz.z;
            v31 = ((unsigned int)(v26 - 4) >> 2) + 1;
            v28 = 4 * v31;
            do
            {
              v32 = *(float *)(v29 - 4);
              v29 += 16;
              p_z += 4;
              --v31;
              *(p_z - 6) = fabs(v32);
              *(p_z - 5) = fabs(*(float *)(v29 - 16));
              *(p_z - 4) = fabs(*(float *)(v29 - 12));
              *(p_z - 3) = fabs(*(float *)(v29 - 8));
            }
            while ( v31 );
          }
          if ( v28 >= v26 )
          {
            v34 = srcVertData;
          }
          else
          {
            v33 = &v10[(_DWORD)absBlendWeights].blendWeight[v28];
            v34 = srcVertData;
            do
            {
              ++v28;
              v35 = fabs(*v33++);
              *((float *)v34 + v28 - 1) = v35;
            }
            while ( v28 < v26 );
          }
          v9 = curVertex + 1 < numVertices;
          srcVertData = (rvBlend4DrawVert *)((char *)v34 + stride);
          ++curVertex;
        }
        while ( v9 );
      }
    }
    else
    {
      v36 = 0;
      curVertex = 0;
      if ( numVertices > 0 )
      {
        v37 = srcVertData;
        do
        {
          v38 = (float *)copyMapping[v36];
          v39 = 0;
          absBlendWeights = v38;
          if ( v26 >= 4 )
          {
            v40 = (_DWORD *)&v10[(_DWORD)v38].blendWeight[1];
            v41 = (_DWORD *)&v37->xyz.z;
            v42 = ((unsigned int)(v26 - 4) >> 2) + 1;
            v39 = 4 * v42;
            do
            {
              *(v41 - 2) = *(v40 - 1);
              *(v41 - 1) = *v40;
              *v41 = v40[1];
              v41[1] = v40[2];
              v40 += 4;
              v41 += 4;
              --v42;
            }
            while ( v42 );
            v38 = absBlendWeights;
            v37 = srcVertData;
            v7 = numVertices;
          }
          if ( v39 < v26 )
          {
            v43 = (_DWORD *)&v10[(_DWORD)v38].blendWeight[v39];
            do
              *((_DWORD *)&v37->xyz.x + v39++) = *v43++;
            while ( v39 < v26 );
          }
          v37 = (rvBlend4DrawVert *)((char *)v37 + stride);
          v36 = curVertex + 1;
          v9 = curVertex + 1 < v7;
          srcVertData = v37;
          ++curVertex;
        }
        while ( v9 );
      }
    }
  }
  v44 = v104;
  if ( (v104->m_format.m_flags & 0x10) != 0 )
  {
    v45 = (v104->m_flags & 4) == 0;
    v104->m_lockVertexOffset = vertexBufferOffset;
    v44->m_lockVertexCount = v7;
    if ( v45 )
    {
      v48 = v104;
      v49 = rvVertexBuffer::LockInterleaved(v104, vertexBufferOffset, v7, 2u, (void **)&srcVertData, &stride);
      v46 = stride;
      v45 = !v49;
      m_normalArray = srcVertData;
      if ( v45 )
      {
LABEL_46:
        v50 = 0;
        if ( v7 >= 4 )
        {
          absBlendWeights = (float *)(((unsigned int)(v7 - 4) >> 2) + 1);
          v51 = copyMapping + 2;
          curVertex = 4 * (_DWORD)absBlendWeights;
          do
          {
            v52 = (_DWORD *)&v10[*(v51 - 2)].xyz.x;
            m_normalArray->xyz.x = (float)v52[11];
            m_normalArray->xyz.y = (float)v52[12];
            m_normalArray->xyz.z = (float)v52[13];
            v53 = (_DWORD *)&v10[*(v51 - 1)].xyz.x;
            *(float *)((char *)&m_normalArray->xyz.x + v46) = (float)v53[11];
            *(float *)((char *)&m_normalArray->xyz.y + v46) = (float)v53[12];
            *(float *)((char *)&m_normalArray->xyz.z + v46) = (float)v53[13];
            v54 = (char *)m_normalArray + v46;
            v55 = (_DWORD *)&v10[*v51].xyz.x;
            *(_DWORD *)&v54[v46] = v55[11];
            *(_DWORD *)&v54[v46 + 4] = v55[12];
            v56 = &v54[v46];
            *((_DWORD *)v56 + 2) = v55[13];
            v57 = (_DWORD *)&v10[v51[1]].xyz.x;
            v58 = &v56[v46];
            *(_DWORD *)v58 = v57[11];
            *((_DWORD *)v58 + 1) = v57[12];
            *((_DWORD *)v58 + 2) = v57[13];
            m_normalArray = (rvBlend4DrawVert *)&v58[v46];
            v51 += 4;
            absBlendWeights = (float *)((char *)absBlendWeights - 1);
          }
          while ( absBlendWeights );
          v50 = curVertex;
          srcVertData = m_normalArray;
        }
        if ( v50 < v7 )
        {
          do
          {
            v59 = (_DWORD *)&v10[copyMapping[v50]].xyz.x;
            m_normalArray->xyz.x = (float)v59[11];
            m_normalArray->xyz.y = (float)v59[12];
            m_normalArray->xyz.z = (float)v59[13];
            ++v50;
            m_normalArray = (rvBlend4DrawVert *)((char *)m_normalArray + v46);
          }
          while ( v50 < v7 );
          srcVertData = m_normalArray;
        }
        goto LABEL_53;
      }
      m_normalArray = (rvBlend4DrawVert *)((char *)srcVertData + v48->m_format.m_byteOffset[4]);
    }
    else
    {
      v46 = 12;
      v44->m_lockStatus = 2;
      m_normalArray = (rvBlend4DrawVert *)v44->m_normalArray;
      stride = 12;
    }
    srcVertData = m_normalArray;
    goto LABEL_46;
  }
LABEL_53:
  v60 = v104;
  if ( (v104->m_format.m_flags & 0x20) == 0 )
    goto LABEL_66;
  v45 = (v104->m_flags & 4) == 0;
  v104->m_lockVertexOffset = vertexBufferOffset;
  v60->m_lockVertexCount = v7;
  if ( !v45 )
  {
    m_tangentArray = (rvBlend4DrawVert *)v60->m_tangentArray;
    v62 = 12;
    v60->m_lockStatus = 2;
    stride = 12;
LABEL_58:
    srcVertData = m_tangentArray;
    goto LABEL_59;
  }
  v63 = rvVertexBuffer::LockInterleaved(v60, vertexBufferOffset, v7, 2u, (void **)&srcVertData, &stride);
  v62 = stride;
  v45 = !v63;
  m_tangentArray = srcVertData;
  if ( !v45 )
  {
    m_tangentArray = (rvBlend4DrawVert *)((char *)srcVertData + v60->m_format.m_byteOffset[5]);
    goto LABEL_58;
  }
LABEL_59:
  v64 = 0;
  curVertex = 0;
  if ( v7 >= 4 )
  {
    absBlendWeights = (float *)(((unsigned int)(v7 - 4) >> 2) + 1);
    v65 = copyMapping + 2;
    curVertex = 4 * (_DWORD)absBlendWeights;
    do
    {
      v66 = (_DWORD *)&v10[*(v65 - 2)].xyz.x;
      m_tangentArray->xyz.x = (float)v66[14];
      m_tangentArray->xyz.y = (float)v66[15];
      m_tangentArray->xyz.z = (float)v66[16];
      v67 = (_DWORD *)&v10[*(v65 - 1)].xyz.x;
      *(float *)((char *)&m_tangentArray->xyz.x + v62) = (float)v67[14];
      *(float *)((char *)&m_tangentArray->xyz.y + v62) = (float)v67[15];
      *(float *)((char *)&m_tangentArray->xyz.z + v62) = (float)v67[16];
      v68 = (char *)m_tangentArray + v62;
      v69 = (_DWORD *)&v10[*v65].xyz.x;
      *(_DWORD *)&v68[v62] = v69[14];
      *(_DWORD *)&v68[v62 + 4] = v69[15];
      v70 = &v68[v62];
      *((_DWORD *)v70 + 2) = v69[16];
      v71 = (_DWORD *)&v10[v65[1]].xyz.x;
      v72 = &v70[v62];
      *(_DWORD *)v72 = v71[14];
      *((_DWORD *)v72 + 1) = v71[15];
      *((_DWORD *)v72 + 2) = v71[16];
      m_tangentArray = (rvBlend4DrawVert *)&v72[v62];
      v65 += 4;
      absBlendWeights = (float *)((char *)absBlendWeights - 1);
    }
    while ( absBlendWeights );
    v64 = curVertex;
    v60 = v104;
    srcVertData = m_tangentArray;
  }
  if ( v64 < v7 )
  {
    do
    {
      v73 = (_DWORD *)&v10[copyMapping[v64]].xyz.x;
      m_tangentArray->xyz.x = (float)v73[14];
      m_tangentArray->xyz.y = (float)v73[15];
      m_tangentArray->xyz.z = (float)v73[16];
      v64 = curVertex + 1;
      m_tangentArray = (rvBlend4DrawVert *)((char *)m_tangentArray + v62);
      ++curVertex;
    }
    while ( curVertex < v7 );
    srcVertData = m_tangentArray;
  }
LABEL_66:
  if ( (v60->m_format.m_flags & 0x40) != 0 )
  {
    v45 = (v60->m_flags & 4) == 0;
    v60->m_lockVertexOffset = vertexBufferOffset;
    v60->m_lockVertexCount = v7;
    if ( v45 )
    {
      v76 = rvVertexBuffer::LockInterleaved(v60, vertexBufferOffset, v7, 2u, (void **)&srcVertData, &stride);
      v75 = stride;
      v45 = !v76;
      m_binormalArray = srcVertData;
      if ( v45 )
      {
LABEL_72:
        v77 = 0;
        if ( v7 >= 4 )
        {
          absBlendWeights = (float *)(((unsigned int)(v7 - 4) >> 2) + 1);
          v78 = copyMapping + 2;
          curVertex = 4 * (_DWORD)absBlendWeights;
          do
          {
            v79 = (_DWORD *)&v10[*(v78 - 2)].xyz.x;
            m_binormalArray->xyz.x = (float)v79[17];
            m_binormalArray->xyz.y = (float)v79[18];
            m_binormalArray->xyz.z = (float)v79[19];
            v80 = (_DWORD *)&v10[*(v78 - 1)].xyz.x;
            *(float *)((char *)&m_binormalArray->xyz.x + v75) = (float)v80[17];
            *(float *)((char *)&m_binormalArray->xyz.y + v75) = (float)v80[18];
            *(float *)((char *)&m_binormalArray->xyz.z + v75) = (float)v80[19];
            v81 = (char *)m_binormalArray + v75;
            v82 = (_DWORD *)&v10[*v78].xyz.x;
            *(_DWORD *)&v81[v75] = v82[17];
            *(_DWORD *)&v81[v75 + 4] = v82[18];
            v83 = &v81[v75];
            *((_DWORD *)v83 + 2) = v82[19];
            v84 = (_DWORD *)&v10[v78[1]].xyz.x;
            v85 = &v83[v75];
            *(_DWORD *)v85 = v84[17];
            *((_DWORD *)v85 + 1) = v84[18];
            *((_DWORD *)v85 + 2) = v84[19];
            m_binormalArray = (rvBlend4DrawVert *)&v85[v75];
            v78 += 4;
            absBlendWeights = (float *)((char *)absBlendWeights - 1);
          }
          while ( absBlendWeights );
          v77 = curVertex;
          v60 = v104;
          srcVertData = m_binormalArray;
        }
        if ( v77 < v7 )
        {
          do
          {
            v86 = (_DWORD *)&v10[copyMapping[v77]].xyz.x;
            m_binormalArray->xyz.x = (float)v86[17];
            m_binormalArray->xyz.y = (float)v86[18];
            m_binormalArray->xyz.z = (float)v86[19];
            ++v77;
            m_binormalArray = (rvBlend4DrawVert *)((char *)m_binormalArray + v75);
          }
          while ( v77 < v7 );
          v60 = v104;
          srcVertData = m_binormalArray;
        }
        goto LABEL_79;
      }
      m_binormalArray = (rvBlend4DrawVert *)((char *)srcVertData + v60->m_format.m_byteOffset[6]);
    }
    else
    {
      m_binormalArray = (rvBlend4DrawVert *)v60->m_binormalArray;
      v75 = 12;
      v60->m_lockStatus = 2;
      stride = 12;
    }
    srcVertData = m_binormalArray;
    goto LABEL_72;
  }
LABEL_79:
  if ( (v60->m_format.m_flags & 0x80) != 0 )
  {
    v45 = (v60->m_flags & 4) == 0;
    v60->m_lockVertexOffset = vertexBufferOffset;
    v60->m_lockVertexCount = v7;
    if ( v45 )
    {
      v88 = rvVertexBuffer::LockInterleaved(v60, vertexBufferOffset, v7, 2u, (void **)&absBlendWeights, &stride);
      m_diffuseColorArray = absBlendWeights;
      if ( v88 )
        m_diffuseColorArray = (float *)((char *)absBlendWeights + v60->m_format.m_byteOffset[7]);
    }
    else
    {
      m_diffuseColorArray = (float *)v60->m_diffuseColorArray;
      v60->m_lockStatus = 2;
      stride = 4;
    }
    for ( i = 0; i < v7; ++i )
    {
      *m_diffuseColorArray = *(float *)v10[copyMapping[i]].color;
      m_diffuseColorArray = (float *)((char *)m_diffuseColorArray + stride);
    }
  }
  if ( (v60->m_format.m_flags & 0x400) != 0 && ((v60->m_format.m_dimensions >> 9) & 7) >= 2 )
  {
    rvVertexBuffer::LockTextureCoordinate(v60, 0, vertexBufferOffset, v7, 2u, (unsigned __int8 **)&srcVertData, &stride);
    v90 = stride;
    v91 = 0;
    if ( v7 < 4 )
    {
      v93 = srcVertData;
    }
    else
    {
      absBlendWeights = (float *)(((unsigned int)(v7 - 4) >> 2) + 1);
      v92 = copyMapping + 2;
      curVertex = 4 * (_DWORD)absBlendWeights;
      v93 = srcVertData;
      do
      {
        v94 = &v10[*(v92 - 2)];
        v93->xyz.x = v94->st.x;
        v93->xyz.y = v94->st.y;
        v95 = &v10[*(v92 - 1)];
        *(float *)((char *)&v93->xyz.x + v90) = v95->st.x;
        *(float *)((char *)&v93->xyz.y + v90) = v95->st.y;
        v96 = (char *)v93 + v90;
        v97 = &v10[*v92];
        *(float *)&v96[v90] = v97->st.x;
        v98 = &v96[v90];
        *((_DWORD *)v98 + 1) = LODWORD(v97->st.y);
        v99 = &v10[v92[1]];
        v100 = &v98[v90];
        *(float *)v100 = v99->st.x;
        *((_DWORD *)v100 + 1) = LODWORD(v99->st.y);
        v93 = (rvBlend4DrawVert *)&v100[v90];
        v92 += 4;
        absBlendWeights = (float *)((char *)absBlendWeights - 1);
      }
      while ( absBlendWeights );
      v91 = curVertex;
      v60 = v104;
    }
    if ( v91 < v7 )
    {
      do
      {
        v101 = &v10[copyMapping[v91]];
        v93->xyz.x = v101->st.x;
        v93->xyz.y = v101->st.y;
        ++v91;
        v93 = (rvBlend4DrawVert *)((char *)v93 + v90);
      }
      while ( v91 < v7 );
      v60 = v104;
    }
  }
  if ( v60->m_lockStatus )
    rvVertexBuffer::Unlock(v60);
}

// FUNC: public: void __thiscall rvVertexBuffer::CopyRemappedShadowVolData(int,int,unsigned int *,unsigned int *,class rvBlend4DrawVert *)
void __thiscall rvVertexBuffer::CopyRemappedShadowVolData(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVertices,
        unsigned int *copyMapping,
        unsigned int *transformMapOldToNew,
        rvBlend4DrawVert *srcVertData)
{
  rvVertexBuffer *v6; // ebp
  bool v7; // cc
  rvBlend4DrawVert *v8; // esi
  unsigned int v9; // eax
  int v10; // ecx
  int v11; // edi
  unsigned int *v12; // edi
  rvBlend4DrawVert *v13; // eax
  float *p_x; // edx
  char *v15; // eax
  _DWORD *v16; // edx
  char *v17; // eax
  char *v18; // eax
  _DWORD *v19; // edx
  char *v20; // eax
  char *v21; // eax
  _DWORD *v22; // edx
  char *v23; // eax
  char *v24; // eax
  float *v25; // edx
  _DWORD *v26; // eax
  int v27; // ecx
  signed int v28; // edi
  unsigned int *v29; // edi
  float *v30; // edx
  char *v31; // eax
  _DWORD *v32; // edx
  char *v33; // eax
  char *v34; // eax
  _DWORD *v35; // edx
  char *v36; // eax
  char *v37; // eax
  char *v38; // eax
  _DWORD *v39; // edx
  char *v40; // eax
  float *v41; // edx
  _DWORD *v42; // eax
  unsigned __int8 *v43; // ecx
  _DWORD *v44; // edi
  __int64 v45; // rax
  __int64 v46; // rax
  __int64 v47; // rax
  unsigned __int8 *v48; // ecx
  __int64 v49; // rax
  __int64 v50; // rax
  __int64 v51; // rax
  unsigned __int8 *v52; // ecx
  _DWORD *v53; // edi
  __int64 v54; // rax
  __int64 v55; // rax
  __int64 v56; // rax
  __int64 v57; // rax
  unsigned __int8 *v58; // ecx
  __int64 v59; // rax
  __int64 v60; // rax
  __int64 v61; // rax
  __int64 v62; // rax
  int v63; // edi
  int v64; // eax
  rvBlend4DrawVert *v65; // ecx
  int v66; // ebp
  float *p_z; // edx
  unsigned int v68; // eax
  int v69; // ebx
  unsigned int v70; // ebp
  int v71; // ecx
  long double v72; // st7
  float *v73; // edx
  long double v74; // st7
  rvBlend4DrawVert *v75; // ecx
  int v76; // ebx
  int v77; // edx
  unsigned int v78; // ebp
  int v79; // ecx
  long double v80; // st7
  float *v81; // eax
  long double v82; // st7
  int curVertex; // [esp+8h] [ebp-10h]
  int curVertexa; // [esp+8h] [ebp-10h]
  int curVertexb; // [esp+8h] [ebp-10h]
  int stride; // [esp+Ch] [ebp-Ch] BYREF
  rvVertexBuffer *v87; // [esp+10h] [ebp-8h]
  unsigned __int8 *bytePtr; // [esp+14h] [ebp-4h] BYREF
  float *vertexBufferOffseta; // [esp+1Ch] [ebp+4h]
  int vertexBufferOffsetb; // [esp+1Ch] [ebp+4h]

  v6 = this;
  v7 = vertexBufferOffset + 2 * numVertices <= this->m_numVertices;
  v87 = this;
  if ( !v7 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "rvVertexBuffer: attempt to copy shadow volume vertex data out-of-bounds");
    return;
  }
  v8 = srcVertData;
  if ( (this->m_format.m_flags & 1) != 0 )
  {
    v9 = this->m_format.m_dimensions & 7;
    if ( v9 == 3 )
    {
      rvVertexBuffer::LockPosition(
        this,
        vertexBufferOffset,
        2 * numVertices,
        2u,
        (unsigned __int8 **)&srcVertData,
        &stride);
      v10 = stride;
      v11 = 0;
      if ( numVertices < 4 )
      {
        v13 = srcVertData;
      }
      else
      {
        bytePtr = (unsigned __int8 *)(((unsigned int)(numVertices - 4) >> 2) + 1);
        v12 = copyMapping + 2;
        curVertex = 4 * (_DWORD)bytePtr;
        v13 = srcVertData;
        do
        {
          p_x = &v8[*(v12 - 2)].xyz.x;
          v13->xyz.x = *p_x;
          v13->xyz.y = p_x[1];
          v13->xyz.z = p_x[2];
          *(float *)((char *)&v13->xyz.x + v10) = *p_x;
          *(float *)((char *)&v13->xyz.y + v10) = p_x[1];
          *(float *)((char *)&v13->xyz.z + v10) = p_x[2];
          v15 = (char *)v13 + v10;
          v16 = (_DWORD *)&v8[*(v12 - 1)].xyz.x;
          *(_DWORD *)&v15[v10] = *v16;
          *(_DWORD *)&v15[v10 + 4] = v16[1];
          *(_DWORD *)&v15[v10 + 8] = v16[2];
          v17 = &v15[v10];
          *(_DWORD *)&v17[v10] = *v16;
          *(_DWORD *)&v17[v10 + 4] = v16[1];
          *(_DWORD *)&v17[v10 + 8] = v16[2];
          v18 = &v17[v10];
          v19 = (_DWORD *)&v8[*v12].xyz.x;
          *(_DWORD *)&v18[v10] = *v19;
          *(_DWORD *)&v18[v10 + 4] = v19[1];
          *(_DWORD *)&v18[v10 + 8] = v19[2];
          v20 = &v18[v10];
          *(_DWORD *)&v20[v10] = *v19;
          *(_DWORD *)&v20[v10 + 4] = v19[1];
          *(_DWORD *)&v20[v10 + 8] = v19[2];
          v21 = &v20[v10];
          v22 = (_DWORD *)&v8[v12[1]].xyz.x;
          *(_DWORD *)&v21[v10] = *v22;
          v23 = &v21[v10];
          *((_DWORD *)v23 + 1) = v22[1];
          *((_DWORD *)v23 + 2) = v22[2];
          v24 = &v23[v10];
          *(_DWORD *)v24 = *v22;
          *((_DWORD *)v24 + 1) = v22[1];
          *((_DWORD *)v24 + 2) = v22[2];
          v13 = (rvBlend4DrawVert *)&v24[v10];
          v12 += 4;
          --bytePtr;
        }
        while ( bytePtr );
        v11 = curVertex;
        v6 = v87;
        srcVertData = v13;
      }
      if ( v11 < numVertices )
      {
        do
        {
          v25 = &v8[copyMapping[v11]].xyz.x;
          v13->xyz.x = *v25;
          v13->xyz.y = v25[1];
          v13->xyz.z = v25[2];
          v26 = (_DWORD *)((char *)&v13->xyz.x + v10);
          *v26 = *(_DWORD *)v25;
          v26[1] = *((_DWORD *)v25 + 1);
          v26[2] = *((_DWORD *)v25 + 2);
          ++v11;
          v13 = (rvBlend4DrawVert *)((char *)v26 + v10);
        }
        while ( v11 < numVertices );
LABEL_21:
        v6 = v87;
        srcVertData = v13;
      }
    }
    else if ( v9 == 4 )
    {
      rvVertexBuffer::LockPosition(
        this,
        vertexBufferOffset,
        2 * numVertices,
        2u,
        (unsigned __int8 **)&srcVertData,
        &stride);
      v27 = stride;
      v28 = 0;
      if ( numVertices < 4 )
      {
        v13 = srcVertData;
      }
      else
      {
        v29 = copyMapping + 2;
        bytePtr = (unsigned __int8 *)(((unsigned int)(numVertices - 4) >> 2) + 1);
        v13 = srcVertData;
        do
        {
          v30 = &v8[*(v29 - 2)].xyz.x;
          v13->xyz.x = *v30;
          v13->xyz.y = v30[1];
          v13->xyz.z = v30[2];
          v13->blendIndex[0] = 1065353216;
          *(float *)((char *)&v13->xyz.x + v27) = *v30;
          *(float *)((char *)&v13->xyz.y + v27) = v30[1];
          *(float *)((char *)&v13->xyz.z + v27) = v30[2];
          *(int *)((char *)v13->blendIndex + v27) = 0;
          v31 = (char *)v13 + v27;
          v32 = (_DWORD *)&v8[*(v29 - 1)].xyz.x;
          *(_DWORD *)&v31[v27] = *v32;
          *(_DWORD *)&v31[v27 + 4] = v32[1];
          *(_DWORD *)&v31[v27 + 8] = v32[2];
          *(_DWORD *)&v31[v27 + 12] = 1065353216;
          v33 = &v31[v27];
          *(_DWORD *)&v33[v27] = *v32;
          *(_DWORD *)&v33[v27 + 4] = v32[1];
          *(_DWORD *)&v33[v27 + 8] = v32[2];
          *(_DWORD *)&v33[v27 + 12] = 0;
          v34 = &v33[v27];
          v35 = (_DWORD *)&v8[*v29].xyz.x;
          *(_DWORD *)&v34[v27] = *v35;
          *(_DWORD *)&v34[v27 + 4] = v35[1];
          *(_DWORD *)&v34[v27 + 8] = v35[2];
          v36 = &v34[v27];
          *((_DWORD *)v36 + 3) = 1065353216;
          *(_DWORD *)&v36[v27] = *v35;
          *(_DWORD *)&v36[v27 + 4] = v35[1];
          v37 = &v36[v27];
          *((_DWORD *)v37 + 2) = v35[2];
          *((_DWORD *)v37 + 3) = 0;
          v38 = &v37[v27];
          v39 = (_DWORD *)&v8[v29[1]].xyz.x;
          *(_DWORD *)v38 = *v39;
          *((_DWORD *)v38 + 1) = v39[1];
          *((_DWORD *)v38 + 2) = v39[2];
          *((_DWORD *)v38 + 3) = 1065353216;
          v40 = &v38[v27];
          *(_DWORD *)v40 = *v39;
          *((_DWORD *)v40 + 1) = v39[1];
          *((_DWORD *)v40 + 2) = v39[2];
          *((_DWORD *)v40 + 3) = 0;
          v13 = (rvBlend4DrawVert *)&v40[v27];
          v29 += 4;
          --bytePtr;
        }
        while ( bytePtr );
        v28 = 4 * (((unsigned int)(numVertices - 4) >> 2) + 1);
        v6 = v87;
        srcVertData = v13;
      }
      if ( v28 < numVertices )
      {
        do
        {
          v41 = &v8[copyMapping[v28]].xyz.x;
          v13->xyz.x = *v41;
          v13->xyz.y = v41[1];
          v13->xyz.z = v41[2];
          v13->blendIndex[0] = 1065353216;
          v42 = (_DWORD *)((char *)&v13->xyz.x + v27);
          *v42 = *(_DWORD *)v41;
          v42[1] = *((_DWORD *)v41 + 1);
          v42[2] = *((_DWORD *)v41 + 2);
          v42[3] = 0;
          ++v28;
          v13 = (rvBlend4DrawVert *)((char *)v42 + v27);
        }
        while ( v28 < numVertices );
        goto LABEL_21;
      }
    }
  }
  if ( (v6->m_format.m_flags & 4) == 0 )
    goto LABEL_32;
  rvVertexBuffer::LockBlendIndex(v6, vertexBufferOffset, 2 * numVertices, 2u, &bytePtr, &stride);
  curVertexa = 0;
  if ( (v6->m_format.m_dimensions & 7) == 3 )
  {
    if ( numVertices <= 0 )
      goto LABEL_32;
    v43 = bytePtr;
    do
    {
      v44 = (_DWORD *)&v8[copyMapping[curVertexa]].xyz.x;
      v45 = (int)transformMapOldToNew[v44[3]];
      *v43 = (BYTE4(v45) ^ v45) - BYTE4(v45);
      v46 = (int)transformMapOldToNew[v44[4]];
      v43[1] = (BYTE4(v46) ^ v46) - BYTE4(v46);
      v47 = (int)transformMapOldToNew[v44[5]];
      v43[2] = (BYTE4(v47) ^ v47) - BYTE4(v47);
      v43[3] = -1;
      v48 = &v43[stride];
      v49 = (int)transformMapOldToNew[v44[3]];
      *v48 = (BYTE4(v49) ^ v49) - BYTE4(v49);
      v50 = (int)transformMapOldToNew[v44[4]];
      v48[1] = (BYTE4(v50) ^ v50) - BYTE4(v50);
      v51 = (int)transformMapOldToNew[v44[5]];
      v48[2] = (BYTE4(v51) ^ v51) - BYTE4(v51);
      v48[3] = 0;
      v43 = &v48[stride];
      ++curVertexa;
    }
    while ( curVertexa < numVertices );
  }
  else
  {
    if ( numVertices <= 0 )
      goto LABEL_32;
    v52 = bytePtr;
    do
    {
      v53 = (_DWORD *)&v8[copyMapping[curVertexa]].xyz.x;
      v54 = (int)transformMapOldToNew[v53[3]];
      *v52 = (BYTE4(v54) ^ v54) - BYTE4(v54);
      v55 = (int)transformMapOldToNew[v53[4]];
      v52[1] = (BYTE4(v55) ^ v55) - BYTE4(v55);
      v56 = (int)transformMapOldToNew[v53[5]];
      v52[2] = (BYTE4(v56) ^ v56) - BYTE4(v56);
      v57 = (int)transformMapOldToNew[v53[6]];
      v52[3] = (BYTE4(v57) ^ v57) - BYTE4(v57);
      v58 = &v52[stride];
      v59 = (int)transformMapOldToNew[v53[3]];
      *v58 = (BYTE4(v59) ^ v59) - BYTE4(v59);
      v60 = (int)transformMapOldToNew[v53[4]];
      v58[1] = (BYTE4(v60) ^ v60) - BYTE4(v60);
      v61 = (int)transformMapOldToNew[v53[5]];
      v58[2] = (BYTE4(v61) ^ v61) - BYTE4(v61);
      v62 = (int)transformMapOldToNew[v53[6]];
      v58[3] = (BYTE4(v62) ^ v62) - BYTE4(v62);
      v52 = &v58[stride];
      ++curVertexa;
    }
    while ( curVertexa < numVertices );
  }
  v6 = v87;
LABEL_32:
  if ( (v6->m_format.m_flags & 8) != 0 )
  {
    v63 = (v6->m_format.m_dimensions >> 3) & 7;
    rvVertexBuffer::LockBlendWeight(
      v6,
      vertexBufferOffset,
      2 * numVertices,
      2u,
      (unsigned __int8 **)&srcVertData,
      &stride);
    v64 = 0;
    curVertexb = 0;
    if ( numVertices > 0 )
    {
      v65 = srcVertData;
      v66 = stride;
      p_z = &srcVertData->xyz.z;
      vertexBufferOffseta = &srcVertData->xyz.z;
      do
      {
        v68 = copyMapping[v64];
        v69 = 0;
        if ( v63 >= 4 )
        {
          v70 = ((unsigned int)(v63 - 4) >> 2) + 1;
          v71 = (int)&v8[v68].blendWeight[1];
          v69 = 4 * v70;
          do
          {
            v72 = *(float *)(v71 - 4);
            v71 += 16;
            p_z += 4;
            --v70;
            *(p_z - 6) = fabs(v72);
            *(p_z - 5) = fabs(*(float *)(v71 - 16));
            *(p_z - 4) = fabs(*(float *)(v71 - 12));
            *(p_z - 3) = fabs(*(float *)(v71 - 8));
          }
          while ( v70 );
          v66 = stride;
          v65 = srcVertData;
        }
        if ( v69 < v63 )
        {
          v73 = &v8[v68].blendWeight[v69];
          do
          {
            ++v69;
            v74 = fabs(*v73++);
            *((float *)v65 + v69 - 1) = v74;
          }
          while ( v69 < v63 );
        }
        vertexBufferOffsetb = (int)vertexBufferOffseta + v66;
        v75 = (rvBlend4DrawVert *)((char *)v65 + v66);
        v76 = 0;
        srcVertData = v75;
        if ( v63 >= 4 )
        {
          v77 = vertexBufferOffsetb;
          v78 = ((unsigned int)(v63 - 4) >> 2) + 1;
          v79 = (int)&v8[v68].blendWeight[1];
          v76 = 4 * v78;
          do
          {
            v80 = *(float *)(v79 - 4);
            v79 += 16;
            v77 += 16;
            --v78;
            *(float *)(v77 - 24) = fabs(v80);
            *(float *)(v77 - 20) = fabs(*(float *)(v79 - 16));
            *(float *)(v77 - 16) = fabs(*(float *)(v79 - 12));
            *(float *)(v77 - 12) = fabs(*(float *)(v79 - 8));
          }
          while ( v78 );
          v75 = srcVertData;
          v66 = stride;
        }
        if ( v76 < v63 )
        {
          v81 = &v8[v68].blendWeight[v76];
          do
          {
            ++v76;
            v82 = fabs(*v81++);
            *((float *)v75 + v76 - 1) = v82;
          }
          while ( v76 < v63 );
        }
        v64 = curVertexb + 1;
        v65 = (rvBlend4DrawVert *)((char *)v75 + v66);
        p_z = (float *)(v66 + vertexBufferOffsetb);
        v7 = curVertexb + 1 < numVertices;
        srcVertData = v65;
        vertexBufferOffseta = (float *)(v66 + vertexBufferOffsetb);
        ++curVertexb;
      }
      while ( v7 );
      v6 = v87;
    }
  }
  if ( v6->m_lockStatus )
    rvVertexBuffer::Unlock(v6);
}

// FUNC: public: int __thiscall rvVertexBuffer::CopySilTraceData(unsigned int *,int,int,int *,class idDrawVert const *)
unsigned int __thiscall rvVertexBuffer::CopySilTraceData(
        rvVertexBuffer *this,
        unsigned int *indexMapping,
        unsigned int *vertexBufferOffset,
        int numVertices,
        int *copyMapping,
        const idDrawVert *srcVertData)
{
  rvVertexBuffer *v6; // ebx
  int v7; // edi
  unsigned int v8; // esi
  bool v9; // cc
  unsigned int *v11; // ebx
  int v12; // ebp
  const idDrawVert *v13; // edi
  float *v14; // eax
  unsigned int *v15; // ecx
  int v16; // edx
  int v17; // edx
  int v18; // ebp
  float *v19; // edx
  int v20; // edx
  int v21; // edx
  int v22; // ebp
  float *v23; // edx
  int v24; // edx
  int v25; // edx
  int v26; // ebp
  float *v27; // edx
  unsigned int v28; // edx
  int v29; // ebp
  float *v30; // edx
  const idDrawVert *v31; // ecx
  unsigned int *v32; // edx
  int v33; // ecx
  int v34; // ecx
  int v35; // edx
  float *v36; // ecx
  unsigned int *v37; // ebp
  int v38; // ebx
  const idDrawVert *v39; // edi
  float *v40; // eax
  unsigned int *v41; // ecx
  int v42; // edx
  int v43; // edx
  int v44; // ebx
  float *v45; // edx
  int v46; // edx
  int v47; // edx
  int v48; // ebx
  float *v49; // edx
  int v50; // edx
  int v51; // edx
  int v52; // ebx
  float *v53; // edx
  unsigned int v54; // edx
  int v55; // ebx
  float *v56; // edx
  const idDrawVert *v57; // ecx
  unsigned int *v58; // edx
  int v59; // ecx
  int v60; // ecx
  int v61; // edx
  float *v62; // ecx
  int v63; // ecx
  unsigned int *v64; // eax
  const idDrawVert *v65; // ebp
  int v66; // edx
  int v67; // [esp+Ch] [ebp-14h]
  int v68; // [esp+Ch] [ebp-14h]
  int curVertex; // [esp+10h] [ebp-10h]
  int curVertexa; // [esp+10h] [ebp-10h]
  float *floatPtr; // [esp+14h] [ebp-Ch] BYREF
  rvVertexBuffer *v72; // [esp+18h] [ebp-8h]
  int numVertsWritten; // [esp+1Ch] [ebp-4h]

  v6 = this;
  v7 = numVertices;
  numVertsWritten = this->m_numVerticesWritten;
  v8 = 0;
  v9 = (int)vertexBufferOffset + numVertices <= this->m_numVertices;
  v72 = this;
  if ( v9 )
  {
    if ( (this->m_format.m_flags & 1) != 0 && (this->m_format.m_dimensions & 7) >= 3 )
    {
      rvVertexBuffer::LockPosition(
        this,
        (int)vertexBufferOffset,
        numVertices,
        2u,
        (unsigned __int8 **)&floatPtr,
        (int *)&vertexBufferOffset);
      if ( (v6->m_format.m_dimensions & 7) < 4 )
      {
        v37 = vertexBufferOffset;
        v38 = 0;
        v9 = v7 < 4;
        v39 = srcVertData;
        curVertexa = 0;
        if ( v9 )
        {
          v40 = floatPtr;
        }
        else
        {
          vertexBufferOffset = (unsigned int *)(copyMapping + 3);
          srcVertData = (const idDrawVert *)((char *)copyMapping - (char *)indexMapping);
          v40 = floatPtr;
          v68 = 2;
          v41 = indexMapping + 1;
          do
          {
            v42 = *(vertexBufferOffset - 3);
            if ( v42 == v38 )
            {
              v43 = v42 << 6;
              v44 = *(_DWORD *)((char *)&v39->xyz.x + v43);
              v45 = (float *)((char *)&v39->xyz.x + v43);
              *(_DWORD *)v40 = v44;
              v40[1] = v45[1];
              v40[2] = v45[2];
              v40 = (float *)((int)v40 + (_DWORD)v37);
              *(v41 - 1) = v8++;
            }
            v46 = *(unsigned int *)((char *)v41 + (_DWORD)srcVertData);
            if ( v46 == v68 - 1 )
            {
              v47 = v46 << 6;
              v48 = *(_DWORD *)((char *)&v39->xyz.x + v47);
              v49 = (float *)((char *)&v39->xyz.x + v47);
              *(_DWORD *)v40 = v48;
              v40[1] = v49[1];
              v40[2] = v49[2];
              v40 = (float *)((int)v40 + (_DWORD)v37);
              *v41 = v8++;
            }
            v50 = *(vertexBufferOffset - 1);
            if ( v50 == v68 )
            {
              v51 = v50 << 6;
              v52 = *(_DWORD *)((char *)&v39->xyz.x + v51);
              v53 = (float *)((char *)&v39->xyz.x + v51);
              *(_DWORD *)v40 = v52;
              v40[1] = v53[1];
              v40[2] = v53[2];
              v40 = (float *)((int)v40 + (_DWORD)v37);
              v41[1] = v8++;
            }
            if ( *vertexBufferOffset == v68 + 1 )
            {
              v54 = *vertexBufferOffset << 6;
              v55 = *(_DWORD *)((char *)&v39->xyz.x + v54);
              v56 = (float *)((char *)&v39->xyz.x + v54);
              *(_DWORD *)v40 = v55;
              v40[1] = v56[1];
              v40[2] = v56[2];
              v40 = (float *)((int)v40 + (_DWORD)v37);
              v41[2] = v8++;
            }
            vertexBufferOffset += 4;
            v68 += 4;
            v38 = curVertexa + 4;
            v41 += 4;
            curVertexa += 4;
          }
          while ( curVertexa < numVertices - 3 );
        }
        if ( v38 < numVertices )
        {
          vertexBufferOffset = &indexMapping[v38];
          v57 = (const idDrawVert *)((char *)copyMapping - (char *)indexMapping);
          v58 = vertexBufferOffset;
          for ( srcVertData = (const idDrawVert *)((char *)copyMapping - (char *)indexMapping); ; v57 = srcVertData )
          {
            v59 = *(unsigned int *)((char *)v58 + (_DWORD)v57);
            if ( v59 == v38 )
            {
              v60 = v59 << 6;
              v61 = *(_DWORD *)((char *)&v39->xyz.x + v60);
              v62 = (float *)((char *)&v39->xyz.x + v60);
              *(_DWORD *)v40 = v61;
              v40[1] = v62[1];
              v58 = vertexBufferOffset;
              v40[2] = v62[2];
              v40 = (float *)((int)v40 + (_DWORD)v37);
              *v58 = v8++;
            }
            ++v38;
            vertexBufferOffset = ++v58;
            if ( v38 >= numVertices )
              break;
          }
        }
      }
      else
      {
        v11 = vertexBufferOffset;
        v12 = 0;
        v9 = v7 < 4;
        v13 = srcVertData;
        curVertex = 0;
        if ( v9 )
        {
          v14 = floatPtr;
        }
        else
        {
          vertexBufferOffset = (unsigned int *)(copyMapping + 3);
          srcVertData = (const idDrawVert *)((char *)copyMapping - (char *)indexMapping);
          v14 = floatPtr;
          v67 = 2;
          v15 = indexMapping + 1;
          do
          {
            v16 = *(vertexBufferOffset - 3);
            if ( v16 == v12 )
            {
              v17 = v16 << 6;
              v18 = *(_DWORD *)((char *)&v13->xyz.x + v17);
              v19 = (float *)((char *)&v13->xyz.x + v17);
              *(_DWORD *)v14 = v18;
              v14[1] = v19[1];
              v14[2] = v19[2];
              v14[3] = 1.0;
              v14 = (float *)((int)v14 + (_DWORD)v11);
              *(v15 - 1) = v8++;
            }
            v20 = *(unsigned int *)((char *)v15 + (_DWORD)srcVertData);
            if ( v20 == v67 - 1 )
            {
              v21 = v20 << 6;
              v22 = *(_DWORD *)((char *)&v13->xyz.x + v21);
              v23 = (float *)((char *)&v13->xyz.x + v21);
              *(_DWORD *)v14 = v22;
              v14[1] = v23[1];
              v14[2] = v23[2];
              v14[3] = 1.0;
              v14 = (float *)((int)v14 + (_DWORD)v11);
              *v15 = v8++;
            }
            v24 = *(vertexBufferOffset - 1);
            if ( v24 == v67 )
            {
              v25 = v24 << 6;
              v26 = *(_DWORD *)((char *)&v13->xyz.x + v25);
              v27 = (float *)((char *)&v13->xyz.x + v25);
              *(_DWORD *)v14 = v26;
              v14[1] = v27[1];
              v14[2] = v27[2];
              v14[3] = 1.0;
              v14 = (float *)((int)v14 + (_DWORD)v11);
              v15[1] = v8++;
            }
            if ( *vertexBufferOffset == v67 + 1 )
            {
              v28 = *vertexBufferOffset << 6;
              v29 = *(_DWORD *)((char *)&v13->xyz.x + v28);
              v30 = (float *)((char *)&v13->xyz.x + v28);
              *(_DWORD *)v14 = v29;
              v14[1] = v30[1];
              v14[2] = v30[2];
              v14[3] = 1.0;
              v14 = (float *)((int)v14 + (_DWORD)v11);
              v15[2] = v8++;
            }
            vertexBufferOffset += 4;
            v67 += 4;
            v12 = curVertex + 4;
            v15 += 4;
            curVertex += 4;
          }
          while ( curVertex < numVertices - 3 );
        }
        if ( v12 < numVertices )
        {
          vertexBufferOffset = &indexMapping[v12];
          v31 = (const idDrawVert *)((char *)copyMapping - (char *)indexMapping);
          v32 = vertexBufferOffset;
          for ( srcVertData = (const idDrawVert *)((char *)copyMapping - (char *)indexMapping); ; v31 = srcVertData )
          {
            v33 = *(_DWORD *)((char *)&v31->xyz.x + (_DWORD)v32);
            if ( v33 == v12 )
            {
              v34 = v33 << 6;
              v35 = *(_DWORD *)((char *)&v13->xyz.x + v34);
              v36 = (float *)((char *)&v13->xyz.x + v34);
              *(_DWORD *)v14 = v35;
              v14[1] = v36[1];
              v32 = vertexBufferOffset;
              v14[2] = v36[2];
              v14[3] = 1.0;
              v14 = (float *)((int)v14 + (_DWORD)v11);
              *v32 = v8++;
            }
            ++v12;
            vertexBufferOffset = ++v32;
            if ( v12 >= numVertices )
              break;
          }
        }
      }
      v6 = v72;
      v7 = numVertices;
    }
    v63 = 0;
    if ( v7 > 0 )
    {
      v64 = indexMapping;
      v65 = (const idDrawVert *)((char *)copyMapping - (char *)indexMapping);
      srcVertData = (const idDrawVert *)((char *)copyMapping - (char *)indexMapping);
      do
      {
        v66 = *(_DWORD *)((char *)&v65->xyz.x + (_DWORD)v64);
        if ( v66 != v63 )
        {
          v65 = srcVertData;
          *v64 = indexMapping[v66];
        }
        ++v63;
        ++v64;
      }
      while ( v63 < v7 );
    }
    if ( v6->m_lockStatus )
      rvVertexBuffer::Unlock(v6);
    v6->m_numVerticesWritten = v8 + numVertsWritten;
    return v8;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "rvVertexBuffer: attempt to copy vertex data out-of-bounds");
    return 0;
  }
}

// FUNC: public: void __thiscall rvVertexBuffer::CopyData(int,int,class idDrawVert const *)
void __thiscall rvVertexBuffer::CopyData(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        float *numVertices,
        const idDrawVert *srcVertData)
{
  int v4; // esi
  rvVertexBuffer *v5; // ebx
  bool v6; // cc
  int v7; // edx
  unsigned int *v8; // ecx
  float *v9; // ecx
  unsigned int v10; // edi
  float *v11; // eax
  char *v12; // eax
  char *v13; // eax
  char *v14; // eax
  float *v15; // ecx
  int v16; // edi
  unsigned int *v17; // ebp
  float *p_z; // ecx
  unsigned int v19; // edi
  float *v20; // eax
  char *v21; // eax
  char *v22; // eax
  float *v23; // ecx
  int v24; // edi
  int v25; // edx
  unsigned int *v26; // ebp
  float *p_y; // ecx
  unsigned int v28; // edi
  float *v29; // eax
  float *v30; // eax
  char *v31; // eax
  char *v32; // eax
  float *v33; // ecx
  int v34; // edi
  int v35; // edx
  float *v36; // eax
  int v37; // ebp
  float *v38; // ecx
  unsigned int v39; // edi
  float *v40; // eax
  char *v41; // eax
  char *v42; // eax
  float *v43; // ecx
  int v44; // edi
  bool v45; // zf
  float *m_binormalArray; // eax
  int v47; // edx
  bool v48; // al
  unsigned int *v49; // ebp
  float *v50; // ecx
  unsigned int v51; // edi
  float *v52; // eax
  char *v53; // eax
  char *v54; // eax
  float *v55; // ecx
  int v56; // edi
  unsigned int *m_diffuseColorArray; // eax
  int v58; // edi
  unsigned __int8 *color; // ecx
  int v60; // edx
  int v61; // edx
  float *v62; // eax
  int v63; // ebp
  float *v64; // ecx
  unsigned int v65; // edi
  float *v66; // eax
  char *v67; // eax
  char *v68; // eax
  float *v69; // ecx
  int v70; // esi
  int stride; // [esp+8h] [ebp-Ch] BYREF
  unsigned int *dwordPtr; // [esp+Ch] [ebp-8h] BYREF
  rvVertexBuffer *v73; // [esp+10h] [ebp-4h]

  v4 = (int)numVertices;
  v5 = this;
  v6 = (int)numVertices + vertexBufferOffset <= this->m_numVertices;
  v73 = this;
  if ( !v6 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "rvVertexBuffer: attempt to copy vertex data out-of-bounds");
    return;
  }
  if ( (this->m_format.m_flags & 1) != 0 && (this->m_format.m_dimensions & 7) >= 3 )
  {
    rvVertexBuffer::LockPosition(
      this,
      vertexBufferOffset,
      (int)numVertices,
      2u,
      (unsigned __int8 **)&numVertices,
      &stride);
    v7 = stride;
    if ( (v5->m_format.m_dimensions & 7) < 4 )
    {
      v17 = 0;
      if ( v4 < 4 )
      {
        v11 = numVertices;
      }
      else
      {
        p_z = &srcVertData->xyz.z;
        v19 = ((unsigned int)(v4 - 4) >> 2) + 1;
        dwordPtr = (unsigned int *)(4 * v19);
        v11 = numVertices;
        do
        {
          *v11 = *(p_z - 2);
          v11[1] = *(p_z - 1);
          v11[2] = *p_z;
          *(float *)((char *)v11 + v7) = p_z[14];
          *(float *)((char *)v11 + v7 + 4) = p_z[15];
          v20 = (float *)((char *)v11 + v7);
          v20[2] = p_z[16];
          *(float *)((char *)v20 + v7) = p_z[30];
          v21 = (char *)v20 + v7;
          *((float *)v21 + 1) = p_z[31];
          *((float *)v21 + 2) = p_z[32];
          v22 = &v21[v7];
          *(float *)v22 = p_z[46];
          *((float *)v22 + 1) = p_z[47];
          *((float *)v22 + 2) = p_z[48];
          v11 = (float *)&v22[v7];
          p_z += 64;
          --v19;
        }
        while ( v19 );
        v17 = dwordPtr;
        numVertices = v11;
      }
      if ( (int)v17 < v4 )
      {
        v23 = &srcVertData[(_DWORD)v17].xyz.z;
        v24 = v4 - (_DWORD)v17;
        do
        {
          *v11 = *(v23 - 2);
          v11[1] = *(v23 - 1);
          v11[2] = *v23;
          v11 = (float *)((char *)v11 + v7);
          v23 += 16;
          --v24;
        }
        while ( v24 );
        goto LABEL_23;
      }
    }
    else
    {
      v8 = 0;
      dwordPtr = 0;
      if ( v4 < 4 )
      {
        v11 = numVertices;
      }
      else
      {
        v9 = &srcVertData->xyz.z;
        v10 = ((unsigned int)(v4 - 4) >> 2) + 1;
        dwordPtr = (unsigned int *)(4 * v10);
        v11 = numVertices;
        do
        {
          *v11 = *(v9 - 2);
          v11[1] = *(v9 - 1);
          v11[2] = *v9;
          v11[3] = 1.0;
          *(float *)((char *)v11 + v7) = v9[14];
          *(float *)((char *)v11 + v7 + 4) = v9[15];
          *(float *)((char *)v11 + v7 + 8) = v9[16];
          v12 = (char *)v11 + v7;
          *((_DWORD *)v12 + 3) = 1065353216;
          *(float *)&v12[v7] = v9[30];
          v13 = &v12[v7];
          *((float *)v13 + 1) = v9[31];
          *((float *)v13 + 2) = v9[32];
          *((_DWORD *)v13 + 3) = 1065353216;
          v14 = &v13[v7];
          *(float *)v14 = v9[46];
          *((float *)v14 + 1) = v9[47];
          *((float *)v14 + 2) = v9[48];
          *((_DWORD *)v14 + 3) = 1065353216;
          v11 = (float *)&v14[v7];
          v9 += 64;
          --v10;
        }
        while ( v10 );
        v5 = v73;
        v8 = dwordPtr;
        numVertices = v11;
      }
      if ( (int)v8 < v4 )
      {
        v15 = &srcVertData[(_DWORD)v8].xyz.z;
        v16 = v4 - (_DWORD)dwordPtr;
        do
        {
          *v11 = *(v15 - 2);
          v11[1] = *(v15 - 1);
          v11[2] = *v15;
          v11[3] = 1.0;
          v11 = (float *)((char *)v11 + v7);
          v15 += 16;
          --v16;
        }
        while ( v16 );
        v5 = v73;
LABEL_23:
        numVertices = v11;
      }
    }
  }
  if ( (v5->m_format.m_flags & 0x10) != 0 )
  {
    rvVertexBuffer::LockNormal(v5, vertexBufferOffset, v4, 2u, (unsigned __int8 **)&numVertices, &stride);
    v25 = stride;
    v26 = 0;
    if ( v4 < 4 )
    {
      v29 = numVertices;
    }
    else
    {
      p_y = &srcVertData->normal.y;
      v28 = ((unsigned int)(v4 - 4) >> 2) + 1;
      dwordPtr = (unsigned int *)(4 * v28);
      v29 = numVertices;
      do
      {
        *v29 = *(p_y - 1);
        v29[1] = *p_y;
        v29[2] = p_y[1];
        *(float *)((char *)v29 + v25) = p_y[15];
        *(float *)((char *)v29 + v25 + 4) = p_y[16];
        v30 = (float *)((char *)v29 + v25);
        v30[2] = p_y[17];
        *(float *)((char *)v30 + v25) = p_y[31];
        v31 = (char *)v30 + v25;
        *((float *)v31 + 1) = p_y[32];
        *((float *)v31 + 2) = p_y[33];
        v32 = &v31[v25];
        *(float *)v32 = p_y[47];
        *((float *)v32 + 1) = p_y[48];
        *((float *)v32 + 2) = p_y[49];
        v29 = (float *)&v32[v25];
        p_y += 64;
        --v28;
      }
      while ( v28 );
      v26 = dwordPtr;
      numVertices = v29;
    }
    if ( (int)v26 < v4 )
    {
      v33 = &srcVertData[(_DWORD)v26].normal.y;
      v34 = v4 - (_DWORD)v26;
      do
      {
        *v29 = *(v33 - 1);
        v29[1] = *v33;
        v29[2] = v33[1];
        v29 = (float *)((char *)v29 + v25);
        v33 += 16;
        --v34;
      }
      while ( v34 );
      numVertices = v29;
    }
  }
  if ( (v5->m_format.m_flags & 0x20) != 0 )
  {
    rvVertexBuffer::LockTangent(v5, vertexBufferOffset, v4, 2u, (unsigned __int8 **)&numVertices, &stride);
    v35 = stride;
    v36 = numVertices;
    v37 = 0;
    if ( v4 >= 4 )
    {
      v38 = &srcVertData->tangents[0].y;
      v39 = ((unsigned int)(v4 - 4) >> 2) + 1;
      v37 = 4 * v39;
      do
      {
        *v36 = *(v38 - 1);
        v36[1] = *v38;
        v36[2] = v38[1];
        *(float *)((char *)v36 + v35) = v38[15];
        *(float *)((char *)v36 + v35 + 4) = v38[16];
        v40 = (float *)((char *)v36 + v35);
        v40[2] = v38[17];
        *(float *)((char *)v40 + v35) = v38[31];
        v41 = (char *)v40 + v35;
        *((float *)v41 + 1) = v38[32];
        *((float *)v41 + 2) = v38[33];
        v42 = &v41[v35];
        *(float *)v42 = v38[47];
        *((float *)v42 + 1) = v38[48];
        *((float *)v42 + 2) = v38[49];
        v36 = (float *)&v42[v35];
        v38 += 64;
        --v39;
      }
      while ( v39 );
      v5 = v73;
      numVertices = v36;
    }
    if ( v37 < v4 )
    {
      v43 = &srcVertData[v37].tangents[0].y;
      v44 = v4 - v37;
      do
      {
        *v36 = *(v43 - 1);
        v36[1] = *v43;
        v36[2] = v43[1];
        v36 = (float *)((char *)v36 + v35);
        v43 += 16;
        --v44;
      }
      while ( v44 );
      numVertices = v36;
    }
  }
  if ( (v5->m_format.m_flags & 0x40) == 0 )
    goto LABEL_57;
  v45 = (v5->m_flags & 4) == 0;
  v5->m_lockVertexOffset = vertexBufferOffset;
  v5->m_lockVertexCount = v4;
  if ( !v45 )
  {
    m_binormalArray = v5->m_binormalArray;
    v47 = 12;
    v5->m_lockStatus = 2;
    stride = 12;
LABEL_48:
    numVertices = m_binormalArray;
    goto LABEL_49;
  }
  v48 = rvVertexBuffer::LockInterleaved(v5, vertexBufferOffset, v4, 2u, (void **)&numVertices, &stride);
  v47 = stride;
  v45 = !v48;
  m_binormalArray = numVertices;
  if ( !v45 )
  {
    m_binormalArray = (float *)((char *)numVertices + v5->m_format.m_byteOffset[6]);
    goto LABEL_48;
  }
LABEL_49:
  v49 = 0;
  if ( v4 >= 4 )
  {
    v50 = &srcVertData->tangents[1].y;
    v51 = ((unsigned int)(v4 - 4) >> 2) + 1;
    dwordPtr = (unsigned int *)(4 * v51);
    do
    {
      *m_binormalArray = *(v50 - 1);
      m_binormalArray[1] = *v50;
      m_binormalArray[2] = v50[1];
      *(float *)((char *)m_binormalArray + v47) = v50[15];
      *(float *)((char *)m_binormalArray + v47 + 4) = v50[16];
      v52 = (float *)((char *)m_binormalArray + v47);
      v52[2] = v50[17];
      *(float *)((char *)v52 + v47) = v50[31];
      v53 = (char *)v52 + v47;
      *((float *)v53 + 1) = v50[32];
      *((float *)v53 + 2) = v50[33];
      v54 = &v53[v47];
      *(float *)v54 = v50[47];
      *((float *)v54 + 1) = v50[48];
      *((float *)v54 + 2) = v50[49];
      m_binormalArray = (float *)&v54[v47];
      v50 += 64;
      --v51;
    }
    while ( v51 );
    v49 = dwordPtr;
    numVertices = m_binormalArray;
  }
  if ( (int)v49 < v4 )
  {
    v55 = &srcVertData[(_DWORD)v49].tangents[1].y;
    v56 = v4 - (_DWORD)v49;
    do
    {
      *m_binormalArray = *(v55 - 1);
      m_binormalArray[1] = *v55;
      m_binormalArray[2] = v55[1];
      m_binormalArray = (float *)((char *)m_binormalArray + v47);
      v55 += 16;
      --v56;
    }
    while ( v56 );
    numVertices = m_binormalArray;
  }
LABEL_57:
  if ( (v5->m_format.m_flags & 0x80) != 0 )
  {
    v45 = (v5->m_flags & 4) == 0;
    v5->m_lockVertexOffset = vertexBufferOffset;
    v5->m_lockVertexCount = v4;
    if ( v45 )
    {
      v45 = !rvVertexBuffer::LockInterleaved(v5, vertexBufferOffset, v4, 2u, (void **)&dwordPtr, &stride);
      m_diffuseColorArray = dwordPtr;
      if ( !v45 )
        m_diffuseColorArray = (unsigned int *)((char *)dwordPtr + v5->m_format.m_byteOffset[7]);
    }
    else
    {
      m_diffuseColorArray = v5->m_diffuseColorArray;
      v5->m_lockStatus = 2;
      stride = 4;
    }
    if ( v4 > 0 )
    {
      v58 = stride;
      color = srcVertData->color;
      v60 = v4;
      do
      {
        *m_diffuseColorArray = *(_DWORD *)color;
        m_diffuseColorArray = (unsigned int *)((char *)m_diffuseColorArray + v58);
        color += 64;
        --v60;
      }
      while ( v60 );
    }
  }
  if ( (v5->m_format.m_flags & 0x400) != 0 && ((v5->m_format.m_dimensions >> 9) & 7) >= 2 )
  {
    rvVertexBuffer::LockTextureCoordinate(v5, 0, vertexBufferOffset, v4, 2u, (unsigned __int8 **)&numVertices, &stride);
    v61 = stride;
    v62 = numVertices;
    v63 = 0;
    if ( v4 >= 4 )
    {
      v64 = &srcVertData->st.y;
      v65 = ((unsigned int)(v4 - 4) >> 2) + 1;
      v63 = 4 * v65;
      do
      {
        *v62 = *(v64 - 1);
        v62[1] = *v64;
        *(float *)((char *)v62 + v61) = v64[15];
        v66 = (float *)((char *)v62 + v61);
        v66[1] = v64[16];
        *(float *)((char *)v66 + v61) = v64[31];
        v67 = (char *)v66 + v61;
        *((float *)v67 + 1) = v64[32];
        v68 = &v67[v61];
        *(float *)v68 = v64[47];
        *((float *)v68 + 1) = v64[48];
        v62 = (float *)&v68[v61];
        v64 += 64;
        --v65;
      }
      while ( v65 );
      v5 = v73;
    }
    if ( v63 < v4 )
    {
      v69 = &srcVertData[v63].st.y;
      v70 = v4 - v63;
      do
      {
        *v62 = *(v69 - 1);
        v62[1] = *v69;
        v62 = (float *)((char *)v62 + v61);
        v69 += 16;
        --v70;
      }
      while ( v70 );
    }
  }
  if ( v5->m_lockStatus )
    rvVertexBuffer::Unlock(v5);
}

// FUNC: public: void __thiscall rvVertexBuffer::CopyRemappedShadowVolData(int,int,int *,class idDrawVert const *)
void __thiscall rvVertexBuffer::CopyRemappedShadowVolData(
        rvVertexBuffer *this,
        int vertexBufferOffset,
        int numVertices,
        int *copyMapping,
        const idDrawVert *srcVertData)
{
  int v5; // ebp
  rvVertexBuffer *v6; // edi
  int m_numVerticesWritten; // esi
  bool v8; // cc
  int v10; // ecx
  float *v11; // eax
  float v12; // edx
  int v13; // edx
  int v14; // ebp
  float *v15; // edx
  _DWORD *v16; // eax
  float v17; // edx
  int v18; // edx
  int v19; // ebp
  float *v20; // edx
  _DWORD *v21; // eax
  int v22; // edx
  int v23; // ebp
  float *v24; // edx
  _DWORD *v25; // eax
  float v26; // edx
  int v27; // edx
  int v28; // ebp
  float *v29; // edx
  _DWORD *v30; // eax
  int v31; // edx
  int v32; // edx
  int v33; // ebp
  float *v34; // edx
  _DWORD *v35; // eax
  int v37; // ecx
  float *v38; // eax
  int v39; // ebx
  float x; // edx
  int v41; // edx
  int v42; // ebp
  float *v43; // edx
  _DWORD *v44; // eax
  float y; // edx
  int v46; // edx
  int v47; // ebp
  float *v48; // edx
  _DWORD *v49; // eax
  int v50; // edx
  int v51; // ebp
  float *v52; // edx
  _DWORD *v53; // eax
  float v54; // edx
  int v55; // edx
  int v56; // ebp
  float *v57; // edx
  _DWORD *v58; // eax
  int v59; // edx
  int v60; // edx
  int v61; // ebp
  float *v62; // edx
  _DWORD *v63; // eax
  int stride; // [esp+Ch] [ebp-Ch] BYREF
  float *floatPtr; // [esp+10h] [ebp-8h] BYREF
  rvVertexBuffer *v66; // [esp+14h] [ebp-4h]
  int vertexBufferOffseta; // [esp+1Ch] [ebp+4h]
  int vertexBufferOffsetb; // [esp+1Ch] [ebp+4h]
  const idDrawVert *srcVertDataa; // [esp+28h] [ebp+10h]
  const idDrawVert *srcVertDatab; // [esp+28h] [ebp+10h]

  v5 = numVertices;
  v6 = this;
  m_numVerticesWritten = this->m_numVerticesWritten;
  v8 = vertexBufferOffset + 2 * numVertices <= this->m_numVertices;
  v66 = this;
  if ( v8 )
  {
    if ( (this->m_format.m_flags & 1) != 0 )
    {
      if ( (this->m_format.m_dimensions & 7) < 4 )
      {
        rvVertexBuffer::LockPosition(
          this,
          vertexBufferOffset,
          2 * numVertices,
          2u,
          (unsigned __int8 **)&floatPtr,
          &stride);
        v37 = stride;
        v38 = floatPtr;
        v39 = 0;
        if ( numVertices >= 4 )
        {
          vertexBufferOffsetb = 2;
          srcVertDatab = (const idDrawVert *)(copyMapping + 2);
          do
          {
            x = srcVertDatab[-1].st.x;
            if ( LODWORD(x) == v39 )
            {
              v41 = LODWORD(x) << 6;
              *v38 = *(float *)((char *)&srcVertData->xyz.x + v41);
              v42 = *(_DWORD *)((char *)&srcVertData->xyz.y + v41);
              v43 = (float *)((char *)&srcVertData->xyz.x + v41);
              *((_DWORD *)v38 + 1) = v42;
              v38[2] = v43[2];
              v44 = (_DWORD *)((char *)v38 + v37);
              *v44 = *(_DWORD *)v43;
              v44[1] = *((_DWORD *)v43 + 1);
              v44[2] = *((_DWORD *)v43 + 2);
              v38 = (float *)((char *)v44 + v37);
              m_numVerticesWritten += 2;
            }
            y = srcVertDatab[-1].st.y;
            if ( LODWORD(y) == vertexBufferOffsetb - 1 )
            {
              v46 = LODWORD(y) << 6;
              *v38 = *(float *)((char *)&srcVertData->xyz.x + v46);
              v47 = *(_DWORD *)((char *)&srcVertData->xyz.y + v46);
              v48 = (float *)((char *)&srcVertData->xyz.x + v46);
              *((_DWORD *)v38 + 1) = v47;
              v38[2] = v48[2];
              v49 = (_DWORD *)((char *)v38 + v37);
              *v49 = *(_DWORD *)v48;
              v49[1] = *((_DWORD *)v48 + 1);
              v49[2] = *((_DWORD *)v48 + 2);
              v38 = (float *)((char *)v49 + v37);
              m_numVerticesWritten += 2;
            }
            if ( LODWORD(srcVertDatab->xyz.x) == vertexBufferOffsetb )
            {
              v50 = LODWORD(srcVertDatab->xyz.x) << 6;
              *v38 = *(float *)((char *)&srcVertData->xyz.x + v50);
              v51 = *(_DWORD *)((char *)&srcVertData->xyz.y + v50);
              v52 = (float *)((char *)&srcVertData->xyz.x + v50);
              *((_DWORD *)v38 + 1) = v51;
              v38[2] = v52[2];
              v53 = (_DWORD *)((char *)v38 + v37);
              *v53 = *(_DWORD *)v52;
              v53[1] = *((_DWORD *)v52 + 1);
              v53[2] = *((_DWORD *)v52 + 2);
              v38 = (float *)((char *)v53 + v37);
              m_numVerticesWritten += 2;
            }
            v54 = srcVertDatab->xyz.y;
            if ( LODWORD(v54) == vertexBufferOffsetb + 1 )
            {
              v55 = LODWORD(v54) << 6;
              *v38 = *(float *)((char *)&srcVertData->xyz.x + v55);
              v56 = *(_DWORD *)((char *)&srcVertData->xyz.y + v55);
              v57 = (float *)((char *)&srcVertData->xyz.x + v55);
              *((_DWORD *)v38 + 1) = v56;
              v38[2] = v57[2];
              v58 = (_DWORD *)((char *)v38 + v37);
              *v58 = *(_DWORD *)v57;
              v58[1] = *((_DWORD *)v57 + 1);
              v58[2] = *((_DWORD *)v57 + 2);
              v38 = (float *)((char *)v58 + v37);
              m_numVerticesWritten += 2;
            }
            v5 = numVertices;
            srcVertDatab = (const idDrawVert *)((char *)srcVertDatab + 16);
            vertexBufferOffsetb += 4;
            v39 += 4;
          }
          while ( v39 < numVertices - 3 );
        }
        for ( ; v39 < v5; ++v39 )
        {
          v59 = copyMapping[v39];
          if ( v59 == v39 )
          {
            v60 = v59 << 6;
            *v38 = *(float *)((char *)&srcVertData->xyz.x + v60);
            v61 = *(_DWORD *)((char *)&srcVertData->xyz.y + v60);
            v62 = (float *)((char *)&srcVertData->xyz.x + v60);
            *((_DWORD *)v38 + 1) = v61;
            v38[2] = v62[2];
            v63 = (_DWORD *)((char *)v38 + v37);
            *v63 = *(_DWORD *)v62;
            v63[1] = *((_DWORD *)v62 + 1);
            v5 = numVertices;
            v63[2] = *((_DWORD *)v62 + 2);
            v38 = (float *)((char *)v63 + v37);
            m_numVerticesWritten += 2;
          }
        }
      }
      else
      {
        rvVertexBuffer::LockPosition(
          this,
          vertexBufferOffset,
          2 * numVertices,
          2u,
          (unsigned __int8 **)&floatPtr,
          &stride);
        v10 = stride;
        vertexBufferOffseta = 0;
        if ( numVertices < 4 )
        {
          v11 = floatPtr;
        }
        else
        {
          srcVertDataa = (const idDrawVert *)(copyMapping + 2);
          v11 = floatPtr;
          stride = 2;
          do
          {
            v12 = srcVertDataa[-1].st.x;
            if ( LODWORD(v12) == vertexBufferOffseta )
            {
              v13 = LODWORD(v12) << 6;
              *v11 = *(float *)((char *)&srcVertData->xyz.x + v13);
              v14 = *(_DWORD *)((char *)&srcVertData->xyz.y + v13);
              v15 = (float *)((char *)&srcVertData->xyz.x + v13);
              *((_DWORD *)v11 + 1) = v14;
              v11[2] = v15[2];
              v11[3] = 1.0;
              v16 = (_DWORD *)((char *)v11 + v10);
              *v16 = *(_DWORD *)v15;
              v16[1] = *((_DWORD *)v15 + 1);
              v16[2] = *((_DWORD *)v15 + 2);
              v16[3] = 0;
              v11 = (float *)((char *)v16 + v10);
              m_numVerticesWritten += 2;
            }
            v17 = srcVertDataa[-1].st.y;
            if ( LODWORD(v17) == stride - 1 )
            {
              v18 = LODWORD(v17) << 6;
              *v11 = *(float *)((char *)&srcVertData->xyz.x + v18);
              v19 = *(_DWORD *)((char *)&srcVertData->xyz.y + v18);
              v20 = (float *)((char *)&srcVertData->xyz.x + v18);
              *((_DWORD *)v11 + 1) = v19;
              v11[2] = v20[2];
              v11[3] = 1.0;
              v21 = (_DWORD *)((char *)v11 + v10);
              *v21 = *(_DWORD *)v20;
              v21[1] = *((_DWORD *)v20 + 1);
              v21[2] = *((_DWORD *)v20 + 2);
              v21[3] = 0;
              v11 = (float *)((char *)v21 + v10);
              m_numVerticesWritten += 2;
            }
            if ( LODWORD(srcVertDataa->xyz.x) == stride )
            {
              v22 = LODWORD(srcVertDataa->xyz.x) << 6;
              *v11 = *(float *)((char *)&srcVertData->xyz.x + v22);
              v23 = *(_DWORD *)((char *)&srcVertData->xyz.y + v22);
              v24 = (float *)((char *)&srcVertData->xyz.x + v22);
              *((_DWORD *)v11 + 1) = v23;
              v11[2] = v24[2];
              v11[3] = 1.0;
              v25 = (_DWORD *)((char *)v11 + v10);
              *v25 = *(_DWORD *)v24;
              v25[1] = *((_DWORD *)v24 + 1);
              v25[2] = *((_DWORD *)v24 + 2);
              v25[3] = 0;
              v11 = (float *)((char *)v25 + v10);
              m_numVerticesWritten += 2;
            }
            v26 = srcVertDataa->xyz.y;
            if ( LODWORD(v26) == stride + 1 )
            {
              v27 = LODWORD(v26) << 6;
              *v11 = *(float *)((char *)&srcVertData->xyz.x + v27);
              v28 = *(_DWORD *)((char *)&srcVertData->xyz.y + v27);
              v29 = (float *)((char *)&srcVertData->xyz.x + v27);
              *((_DWORD *)v11 + 1) = v28;
              v11[2] = v29[2];
              v11[3] = 1.0;
              v30 = (_DWORD *)((char *)v11 + v10);
              *v30 = *(_DWORD *)v29;
              v30[1] = *((_DWORD *)v29 + 1);
              v30[2] = *((_DWORD *)v29 + 2);
              v30[3] = 0;
              v11 = (float *)((char *)v30 + v10);
              m_numVerticesWritten += 2;
            }
            srcVertDataa = (const idDrawVert *)((char *)srcVertDataa + 16);
            stride += 4;
            vertexBufferOffseta += 4;
          }
          while ( vertexBufferOffseta < numVertices - 3 );
          v5 = numVertices;
        }
        if ( vertexBufferOffseta < v5 )
        {
          do
          {
            v31 = copyMapping[vertexBufferOffseta];
            if ( v31 == vertexBufferOffseta )
            {
              v32 = v31 << 6;
              *v11 = *(float *)((char *)&srcVertData->xyz.x + v32);
              v33 = *(_DWORD *)((char *)&srcVertData->xyz.y + v32);
              v34 = (float *)((char *)&srcVertData->xyz.x + v32);
              *((_DWORD *)v11 + 1) = v33;
              v11[2] = v34[2];
              v11[3] = 1.0;
              v35 = (_DWORD *)((char *)v11 + v10);
              *v35 = *(_DWORD *)v34;
              v35[1] = *((_DWORD *)v34 + 1);
              v35[2] = *((_DWORD *)v34 + 2);
              v35[3] = 0;
              v11 = (float *)((char *)v35 + v10);
              m_numVerticesWritten += 2;
            }
            ++vertexBufferOffseta;
          }
          while ( vertexBufferOffseta < numVertices );
        }
      }
      v6 = v66;
    }
    if ( v6->m_lockStatus )
      rvVertexBuffer::Unlock(v6);
    v6->m_numVerticesWritten = m_numVerticesWritten;
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "rvVertexBuffer: attempt to copy shadow volume vertex data out-of-bounds");
  }
}

// FUNC: public: void __thiscall rvVertexBuffer::CopyShadowVolData(int,int,struct shadowCache_s *)
void __thiscall rvVertexBuffer::CopyShadowVolData(
        rvVertexBuffer *this,
        char *vertexBufferOffset,
        float *numVertices,
        shadowCache_s *srcShadowVertData)
{
  int v4; // esi
  rvVertexBuffer *v5; // edi
  float *v6; // edx
  char *v7; // eax
  int v8; // ebx
  float *v9; // ecx
  unsigned int v10; // edi
  float *v11; // eax
  float *v12; // eax
  char *v13; // eax
  float *v14; // ecx
  int v15; // esi
  float *v16; // edx
  char *v17; // eax
  int v18; // ebx
  float *p_z; // ecx
  unsigned int v20; // edi
  float *v21; // eax
  float *v22; // eax
  char *v23; // eax
  float *v24; // ecx
  int v25; // esi

  v4 = (int)numVertices;
  v5 = this;
  if ( (int)numVertices + (int)vertexBufferOffset <= this->m_numVertices )
  {
    if ( (this->m_format.m_flags & 1) != 0 )
    {
      if ( (this->m_format.m_dimensions & 7) < 4 )
      {
        rvVertexBuffer::LockPosition(
          this,
          (int)vertexBufferOffset,
          (int)numVertices,
          2u,
          (unsigned __int8 **)&vertexBufferOffset,
          (int *)&numVertices);
        v16 = numVertices;
        v17 = vertexBufferOffset;
        v18 = 0;
        if ( v4 >= 4 )
        {
          p_z = &srcShadowVertData->xyz.z;
          v20 = ((unsigned int)(v4 - 4) >> 2) + 1;
          v18 = 4 * v20;
          do
          {
            *(float *)v17 = *(p_z - 2);
            *((float *)v17 + 1) = *(p_z - 1);
            *((float *)v17 + 2) = *p_z;
            *(float *)((char *)v16 + (_DWORD)v17) = p_z[2];
            *(float *)((char *)v16 + (_DWORD)v17 + 4) = p_z[3];
            v21 = (float *)&v17[(_DWORD)v16];
            v21[2] = p_z[4];
            *(float *)((char *)v16 + (_DWORD)v21) = p_z[6];
            v22 = (float *)((int)v21 + (_DWORD)v16);
            v22[1] = p_z[7];
            v22[2] = p_z[8];
            v23 = (char *)v22 + (_DWORD)v16;
            *(float *)v23 = p_z[10];
            *((float *)v23 + 1) = p_z[11];
            *((float *)v23 + 2) = p_z[12];
            v17 = &v23[(_DWORD)v16];
            p_z += 16;
            --v20;
          }
          while ( v20 );
          v5 = this;
        }
        if ( v18 < v4 )
        {
          v24 = &srcShadowVertData[v18].xyz.z;
          v25 = v4 - v18;
          do
          {
            *(float *)v17 = *(v24 - 2);
            *((float *)v17 + 1) = *(v24 - 1);
            *((float *)v17 + 2) = *v24;
            v17 = &v17[(_DWORD)v16];
            v24 += 4;
            --v25;
          }
          while ( v25 );
        }
      }
      else
      {
        rvVertexBuffer::LockPosition(
          this,
          (int)vertexBufferOffset,
          (int)numVertices,
          2u,
          (unsigned __int8 **)&vertexBufferOffset,
          (int *)&numVertices);
        v6 = numVertices;
        v7 = vertexBufferOffset;
        v8 = 0;
        if ( v4 >= 4 )
        {
          v9 = &srcShadowVertData->xyz.z;
          v10 = ((unsigned int)(v4 - 4) >> 2) + 1;
          v8 = 4 * v10;
          do
          {
            *(float *)v7 = *(v9 - 2);
            *((float *)v7 + 1) = *(v9 - 1);
            *((float *)v7 + 2) = *v9;
            *((float *)v7 + 3) = v9[1];
            *(float *)((char *)v6 + (_DWORD)v7) = v9[2];
            *(float *)((char *)v6 + (_DWORD)v7 + 4) = v9[3];
            *(float *)((char *)v6 + (_DWORD)v7 + 8) = v9[4];
            v11 = (float *)&v7[(_DWORD)v6];
            v11[3] = v9[5];
            *(float *)((char *)v6 + (_DWORD)v11) = v9[6];
            *(float *)((char *)v6 + (_DWORD)v11 + 4) = v9[7];
            v12 = (float *)((int)v11 + (_DWORD)v6);
            v12[2] = v9[8];
            v12[3] = v9[9];
            v13 = (char *)v12 + (_DWORD)v6;
            *(float *)v13 = v9[10];
            *((float *)v13 + 1) = v9[11];
            *((float *)v13 + 2) = v9[12];
            *((float *)v13 + 3) = v9[13];
            v7 = &v13[(_DWORD)v6];
            v9 += 16;
            --v10;
          }
          while ( v10 );
          v5 = this;
        }
        if ( v8 < v4 )
        {
          v14 = &srcShadowVertData[v8].xyz.z;
          v15 = v4 - v8;
          do
          {
            *(float *)v7 = *(v14 - 2);
            *((float *)v7 + 1) = *(v14 - 1);
            *((float *)v7 + 2) = *v14;
            *((float *)v7 + 3) = v14[1];
            v7 = &v7[(_DWORD)v6];
            v14 += 4;
            --v15;
          }
          while ( v15 );
        }
      }
    }
    if ( v5->m_lockStatus )
      rvVertexBuffer::Unlock(v5);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "rvVertexBuffer: attempt to copy shadow volume vertex data out-of-bounds");
  }
}

// FUNC: public: __thiscall rvVertexBuffer::~rvVertexBuffer(void)
void __thiscall rvVertexBuffer::~rvVertexBuffer(rvVertexBuffer *this)
{
  rvVertexBuffer::Shutdown(this);
  rvVertexFormat::Shutdown(&this->m_loadFormat);
  rvVertexFormat::Shutdown(&this->m_format);
}

// FUNC: public: void __thiscall rvVertexBuffer::Init(class rvVertexFormat const &,int,unsigned int)
void __thiscall rvVertexBuffer::Init(
        rvVertexBuffer *this,
        const rvVertexFormat *vertexFormat,
        int numVertices,
        unsigned int flagMask)
{
  if ( this->m_format.m_flags )
    rvVertexBuffer::Shutdown(this);
  rvVertexFormat::Init(&this->m_format, vertexFormat);
  rvVertexFormat::Init(&this->m_loadFormat, vertexFormat);
  this->m_numVertices = numVertices;
  this->m_flags = flagMask;
  rvVertexBuffer::CreateVertexStorage(this);
}

// FUNC: public: void __thiscall rvVertexBuffer::Init(class Lexer &)
void __thiscall rvVertexBuffer::Init(rvVertexBuffer *this, Lexer *lex)
{
  bool v3; // zf
  rvVertexFormat *p_m_loadFormat; // ebx
  int m_numVertices; // ecx
  unsigned __int8 *v6; // ebp
  int m_numValues; // ecx
  int i; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // ebp
  int v12; // ebx
  int j; // eax
  unsigned __int8 *v14; // eax
  int v15; // ebx
  int k; // ecx
  bool useLoadVertexFormat; // [esp+Bh] [ebp-185h]
  float **m_texCoordArrays; // [esp+Ch] [ebp-184h]
  int curTexCoord; // [esp+10h] [ebp-180h]
  idToken token; // [esp+14h] [ebp-17Ch] BYREF
  int tokenSubTypeStructElements[72]; // [esp+64h] [ebp-12Ch] BYREF
  int v22; // [esp+18Ch] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v3 = this->m_format.m_flags == 0;
  v22 = 0;
  if ( !v3 )
    rvVertexBuffer::Shutdown(this);
  Lexer::ExpectTokenString(lex, "{");
  Lexer::ExpectTokenString(lex, "VertexFormat");
  rvVertexFormat::Init(&this->m_format, lex);
  p_m_loadFormat = &this->m_loadFormat;
  rvVertexFormat::Init(&this->m_loadFormat, &this->m_format);
  this->m_flags = 0;
  while ( Lexer::ReadToken(lex, &token) )
  {
    if ( idStr::Icmp(token.data, "LoadVertexFormat") )
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
    else
    {
      rvVertexFormat::Init(&this->m_loadFormat, lex);
    }
  }
  rvVertexFormat::BuildDataTypes(&this->m_format, 0);
  if ( p_m_loadFormat->m_flags != this->m_format.m_flags
    || this->m_loadFormat.m_dimensions != this->m_format.m_dimensions
    || (useLoadVertexFormat = 0, !rvVertexFormat::HasSameDataTypes(&this->m_loadFormat, &this->m_format)) )
  {
    useLoadVertexFormat = 1;
  }
  if ( !this->m_flags )
    this->m_flags = 2;
  if ( !idStr::Icmp(token.data, "SoA") )
  {
    if ( useLoadVertexFormat )
      Lexer::Error(lex, "SoA is currently not supported with LoadVertexFormat");
    this->m_flags |= 4u;
    Lexer::ReadToken(lex, &token);
  }
  if ( idStr::Icmp(token.data, "Vertex") )
    Lexer::Error(lex, "Expected vertex header");
  Lexer::ExpectTokenString(lex, "[");
  this->m_numVertices = Lexer::ParseInt(lex);
  Lexer::ExpectTokenString(lex, "]");
  if ( this->m_numVertices > 0 )
  {
    rvVertexBuffer::CreateVertexStorage(this);
    Lexer::ExpectTokenString(lex, "{");
    Lexer::ReadToken(lex, &token);
    if ( idStr::Icmp(token.data, "}") )
    {
      Lexer::UnreadToken(lex, &token);
      m_numVertices = this->m_numVertices;
      this->m_lockStatus = 6;
      this->m_lockVertexOffset = 0;
      this->m_lockVertexCount = m_numVertices;
      if ( useLoadVertexFormat )
      {
        v6 = (unsigned __int8 *)Mem_Alloc16(this->m_loadFormat.m_size * m_numVertices, 0x11u);
        if ( !v6 )
        {
          idLib::common->FatalError(idLib::common, "Ran out of memory trying to allocate temporary vertex storage");
          goto LABEL_71;
        }
        m_numValues = this->m_loadFormat.m_numValues;
        for ( i = 0; i < m_numValues; ++i )
          tokenSubTypeStructElements[i] = p_m_loadFormat->m_tokenSubTypes[i];
        Lexer::ParseNumericStructArray(
          lex,
          this->m_loadFormat.m_numValues,
          tokenSubTypeStructElements,
          this->m_numVertices,
          v6);
        rvVertexBuffer::CopyData(this, 0, this->m_numVertices, v6, this->m_loadFormat.m_size, &this->m_loadFormat, 0);
        Mem_Free16(v6);
      }
      else
      {
        if ( (this->m_flags & 1) != 0 )
        {
          if ( (this->m_flags & 4) != 0 )
          {
            if ( (this->m_format.m_flags & 2) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(
                &this->m_format,
                RV_VERTEX_COMPONENT_SWIZZLED_POSITION,
                tokenSubTypeStructElements);
              v9 = this->m_numVertices + 3;
              LOBYTE(v9) = v9 & 0xFC;
              Lexer::ParseNumericStructArray(
                lex,
                3,
                tokenSubTypeStructElements,
                v9,
                (unsigned __int8 *)this->m_swizzledPositionArray);
            }
            else if ( (this->m_format.m_flags & 1) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(
                &this->m_format,
                RV_VERTEX_COMPONENT_POSITION,
                tokenSubTypeStructElements);
              Lexer::ParseNumericStructArray(
                lex,
                this->m_format.m_dimensions & 7,
                tokenSubTypeStructElements,
                this->m_numVertices,
                (unsigned __int8 *)this->m_positionArray);
            }
            if ( (this->m_format.m_flags & 4) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(
                &this->m_format,
                RV_VERTEX_COMPONENT_BLEND_INDEX,
                tokenSubTypeStructElements);
              Lexer::ParseNumericStructArray(
                lex,
                1,
                tokenSubTypeStructElements,
                this->m_numVertices,
                (unsigned __int8 *)this->m_blendIndexArray);
            }
            if ( (this->m_format.m_flags & 8) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(
                &this->m_format,
                RV_VERTEX_COMPONENT_BLEND_WEIGHT,
                tokenSubTypeStructElements);
              Lexer::ParseNumericStructArray(
                lex,
                (this->m_format.m_dimensions >> 3) & 7,
                tokenSubTypeStructElements,
                this->m_numVertices,
                (unsigned __int8 *)this->m_blendWeightArray);
            }
            if ( (this->m_format.m_flags & 0x10) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_NORMAL, tokenSubTypeStructElements);
              Lexer::ParseNumericStructArray(
                lex,
                3,
                tokenSubTypeStructElements,
                this->m_numVertices,
                (unsigned __int8 *)this->m_normalArray);
            }
            if ( (this->m_format.m_flags & 0x20) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(&this->m_format, RV_VERTEX_COMPONENT_TANGENT, tokenSubTypeStructElements);
              Lexer::ParseNumericStructArray(
                lex,
                3,
                tokenSubTypeStructElements,
                this->m_numVertices,
                (unsigned __int8 *)this->m_tangentArray);
            }
            if ( (this->m_format.m_flags & 0x40) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(
                &this->m_format,
                RV_VERTEX_COMPONENT_BINORMAL,
                tokenSubTypeStructElements);
              Lexer::ParseNumericStructArray(
                lex,
                3,
                tokenSubTypeStructElements,
                this->m_numVertices,
                (unsigned __int8 *)this->m_binormalArray);
            }
            if ( (this->m_format.m_flags & 0x80) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(
                &this->m_format,
                RV_VERTEX_COMPONENT_DIFFUSE_COLOR,
                tokenSubTypeStructElements);
              Lexer::ParseNumericStructArray(
                lex,
                1,
                tokenSubTypeStructElements,
                this->m_numVertices,
                (unsigned __int8 *)this->m_diffuseColorArray);
            }
            if ( (this->m_format.m_flags & 0x100) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(
                &this->m_format,
                RV_VERTEX_COMPONENT_SPECULAR_COLOR,
                tokenSubTypeStructElements);
              Lexer::ParseNumericStructArray(
                lex,
                1,
                tokenSubTypeStructElements,
                this->m_numVertices,
                (unsigned __int8 *)this->m_specularColorArray);
            }
            if ( (this->m_format.m_flags & 0x200) != 0 )
            {
              rvVertexFormat::GetTokenSubTypes(
                &this->m_format,
                RV_VERTEX_COMPONENT_POINT_SIZE,
                tokenSubTypeStructElements);
              Lexer::ParseNumericStructArray(
                lex,
                1,
                tokenSubTypeStructElements,
                this->m_numVertices,
                (unsigned __int8 *)this->m_pointSizeArray);
            }
            if ( (this->m_format.m_flags & 0x400) != 0 )
            {
              curTexCoord = 0;
              v10 = 9;
              m_texCoordArrays = this->m_texCoordArrays;
              do
              {
                v11 = (this->m_format.m_dimensions >> v10) & 7;
                if ( v11 )
                {
                  rvVertexFormat::GetTokenSubTypes(
                    &this->m_format,
                    (Rv_Vertex_Component_t)(curTexCoord + 10),
                    tokenSubTypeStructElements);
                  Lexer::ParseNumericStructArray(
                    lex,
                    v11,
                    tokenSubTypeStructElements,
                    this->m_numVertices,
                    (unsigned __int8 *)*m_texCoordArrays);
                }
                ++curTexCoord;
                ++m_texCoordArrays;
                v10 += 3;
              }
              while ( v10 < 30 );
            }
          }
          else
          {
            v12 = this->m_format.m_numValues;
            for ( j = 0; j < v12; ++j )
              tokenSubTypeStructElements[j] = this->m_format.m_tokenSubTypes[j];
            Lexer::ParseNumericStructArray(
              lex,
              v12,
              tokenSubTypeStructElements,
              m_numVertices,
              this->m_interleavedStorage);
          }
        }
        else
        {
          qglBindBufferARB(0x8892u, this->m_vbID);
          v14 = (unsigned __int8 *)qglMapBufferARB(0x8892u, 0x88B9u);
          this->m_lockedBase = v14;
          if ( !v14 )
          {
            Lexer::Error(lex, "Vertex buffer cannot be mapped for access");
            rvVertexBuffer::Shutdown(this);
            goto LABEL_71;
          }
          v15 = this->m_format.m_numValues;
          for ( k = 0; k < v15; ++k )
            tokenSubTypeStructElements[k] = this->m_format.m_tokenSubTypes[k];
          Lexer::ParseNumericStructArray(lex, v15, tokenSubTypeStructElements, this->m_numVertices, v14);
        }
        rvVertexBuffer::Unlock(this);
      }
      Lexer::ExpectTokenString(lex, "}");
      Lexer::ExpectTokenString(lex, "}");
      goto LABEL_71;
    }
    Lexer::ExpectTokenString(lex, "}");
    this->m_flags |= 0x10u;
  }
  else
  {
    Lexer::Error(lex, "Invalid vertex count");
  }
LABEL_71:
  v22 = -1;
  idStr::FreeData(&token);
}
