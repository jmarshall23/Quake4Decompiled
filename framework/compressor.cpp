
// FUNC: public: virtual void __thiscall idCompressor_None::Init(class idFile *,bool,int)
void __thiscall idCompressor_None::Init(idCompressor_None *this, idFile *f, bool compress, int wordLength)
{
  this->file = f;
  this->compress = compress;
}

// FUNC: public: virtual char const * __thiscall idCompressor_None::GetName(void)
const char *__thiscall idCompressor_None::GetName(idCompressor_None *this)
{
  if ( this->file )
    return this->file->GetName(this->file);
  else
    return &entityFilter;
}

// FUNC: public: virtual char const * __thiscall idCompressor_None::GetFullPath(void)
const char *__thiscall idCompressor_None::GetFullPath(idCompressor_None *this)
{
  if ( this->file )
    return this->file->GetFullPath(this->file);
  else
    return &entityFilter;
}

// FUNC: public: virtual int __thiscall idCompressor_None::Write(void const *,int)
int __thiscall idCompressor_None::Write(idCompressor_None *this, const void *inData, int inLength)
{
  if ( this->compress && inLength > 0 )
    return this->file->Write(this->file, inData, inLength);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idCompressor_None::Read(void *,int)
int __thiscall idCompressor_None::Read(idCompressor_None *this, void *outData, int outLength)
{
  if ( this->compress || outLength <= 0 )
    return 0;
  else
    return this->file->Read(this->file, outData, outLength);
}

// FUNC: public: virtual int __thiscall idCompressor_None::Length(void)
int __thiscall idCompressor_None::Length(idCompressor_None *this)
{
  if ( this->file )
    return this->file->Length(this->file);
  else
    return 0;
}

// FUNC: public: virtual unsigned int __thiscall idCompressor_None::Timestamp(void)
unsigned int __thiscall idCompressor_None::Timestamp(idCompressor_None *this)
{
  if ( this->file )
    return this->file->Timestamp(this->file);
  else
    return 0;
}

// FUNC: public: virtual int __thiscall idCompressor_None::Tell(void)
int __thiscall idCompressor_None::Tell(idCompressor_None *this)
{
  if ( this->file )
    return this->file->Tell(this->file);
  else
    return 0;
}

// FUNC: public: virtual void __thiscall idCompressor_None::ForceFlush(void)
void __thiscall idCompressor_None::ForceFlush(idCompressor_None *this)
{
  if ( this->file )
    this->file->ForceFlush(this->file);
}

// FUNC: public: virtual int __thiscall idCompressor_None::Seek(long,enum fsOrigin_t)
int __thiscall idCompressor_None::Seek(idCompressor_None *this, int offset, fsOrigin_t origin)
{
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
    common.type,
    "cannot seek on idCompressor");
  return -1;
}

// FUNC: public: virtual void __thiscall idCompressor_BitStream::Init(class idFile *,bool,int)
void __thiscall idCompressor_BitStream::Init(idCompressor_BitStream *this, idFile *f, bool compress, int wordLength)
{
  this->file = f;
  this->wordLength = wordLength;
  this->compress = compress;
  this->readTotalBytes = 0;
  this->readLength = 0;
  this->readByte = 0;
  this->readBit = 0;
  this->readData = 0;
  this->writeTotalBytes = 0;
  this->writeLength = 0;
  this->writeByte = 0;
  this->writeBit = 0;
  this->writeData = 0;
}

// FUNC: protected: void __thiscall idCompressor_BitStream::WriteBits(int,int)
void __thiscall idCompressor_BitStream::WriteBits(idCompressor_BitStream *this, int value, int numBits)
{
  int v4; // edi
  int writeByte; // eax
  unsigned __int8 *writeData; // ecx
  int v7; // eax
  int writeBit; // edx
  int v9; // eax
  unsigned __int8 *v10; // ebp
  char v11; // bl
  int v12; // edi

  v4 = numBits;
  if ( this->writeBit || numBits != 8 )
  {
    if ( !numBits )
      return;
    while ( 1 )
    {
LABEL_6:
      if ( !this->writeBit )
      {
        if ( this->writeByte >= this->writeLength )
        {
          if ( this->writeData != this->buffer )
          {
            this->writeBit = v4 & 7;
            v12 = ((v4 & 7) != 0) + (v4 >> 3);
            this->writeByte += v12;
            this->writeTotalBytes += v12;
            return;
          }
          ((void (__stdcall *)(unsigned __int8 *, int))this->file->Write)(this->buffer, this->writeByte);
          this->writeByte = 0;
        }
        this->writeData[this->writeByte++] = 0;
        ++this->writeTotalBytes;
      }
      writeBit = this->writeBit;
      v9 = 8 - writeBit;
      if ( 8 - writeBit > v4 )
        v9 = v4;
      v10 = &this->writeData[this->writeByte - 1];
      v4 -= v9;
      v11 = ((unsigned __int8)value & (unsigned __int8)((1 << v9) - 1)) << writeBit;
      value >>= v9;
      *v10 |= v11;
      this->writeBit = ((_BYTE)v9 + (unsigned __int8)this->writeBit) & 7;
      if ( !v4 )
        return;
    }
  }
  writeByte = this->writeByte;
  if ( writeByte >= this->writeLength )
    goto LABEL_6;
  writeData = this->writeData;
  v7 = writeByte + 1;
  ++this->writeTotalBytes;
  this->writeByte = v7;
  writeData[v7 - 1] = value;
}

// FUNC: protected: int __thiscall idCompressor_BitStream::ReadBits(int)
int __thiscall idCompressor_BitStream::ReadBits(idCompressor_BitStream *this, int numBits)
{
  int v2; // ebx
  int v3; // edi
  int readByte; // eax
  const unsigned __int8 *readData; // ecx
  int v7; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // ebx
  int v12; // ebx
  int v13; // ebx
  int v14; // eax
  int value; // [esp+10h] [ebp-8h]

  v2 = numBits;
  v3 = 0;
  value = 0;
  if ( !this->readBit && numBits == 8 )
  {
    readByte = this->readByte;
    if ( readByte >= this->readLength )
      goto LABEL_6;
    readData = this->readData;
    v7 = readByte + 1;
    ++this->readTotalBytes;
    this->readByte = v7;
    return readData[v7 - 1];
  }
  if ( numBits <= 0 )
    return value;
LABEL_6:
  while ( this->readBit )
  {
LABEL_11:
    v9 = 8 - this->readBit;
    v10 = v2 - v3;
    if ( v9 > v10 )
      v9 = v10;
    v11 = this->readData[this->readByte - 1] >> this->readBit;
    this->readBit = ((_BYTE)v9 + (unsigned __int8)this->readBit) & 7;
    v12 = (((1 << v9) - 1) & v11) << v3;
    v3 += v9;
    value |= v12;
    v2 = numBits;
    if ( v3 >= numBits )
      return value;
  }
  if ( this->readByte < this->readLength )
  {
LABEL_10:
    ++this->readByte;
    ++this->readTotalBytes;
    goto LABEL_11;
  }
  if ( this->readData == this->buffer )
  {
    this->readLength = this->file->Read(this->file, this->buffer, 0x10000);
    this->readByte = 0;
    goto LABEL_10;
  }
  v13 = v2 - v3;
  this->readBit = v13 & 7;
  v14 = ((v13 & 7) != 0) + (v13 >> 3);
  this->readByte += v14;
  this->readTotalBytes += v14;
  return value;
}

// FUNC: protected: void __thiscall idCompressor_BitStream::UnreadBits(int)
void __thiscall idCompressor_BitStream::UnreadBits(idCompressor_BitStream *this, int numBits)
{
  int readBit; // eax
  int readByte; // esi
  int v4; // edx
  int readTotalBytes; // edi
  int v6; // eax
  int v7; // eax

  this->readByte -= numBits >> 3;
  this->readTotalBytes -= numBits >> 3;
  readBit = this->readBit;
  readByte = this->readByte;
  v4 = numBits & 7;
  readTotalBytes = this->readTotalBytes;
  if ( readBit )
  {
    v7 = readBit - v4;
    this->readBit = v7;
    if ( v7 > 0 )
      goto LABEL_6;
    this->readByte = readByte - 1;
    this->readTotalBytes = readTotalBytes - 1;
    v6 = v7 & 7;
  }
  else
  {
    v6 = 8 - v4;
  }
  this->readBit = v6;
LABEL_6:
  if ( this->readByte < 0 )
  {
    this->readByte = 0;
    this->readBit = 0;
  }
}

// FUNC: public: virtual void __thiscall idCompressor_BitStream::FinishCompress(void)
void __thiscall idCompressor_BitStream::FinishCompress(idCompressor_BitStream *this)
{
  if ( this->compress )
  {
    if ( this->writeByte )
      this->file->Write(this->file, this->buffer, this->writeByte);
    this->writeLength = 0;
    this->writeByte = 0;
    this->writeBit = 0;
  }
}

// FUNC: public: virtual float __thiscall idCompressor_BitStream::GetCompressionRatio(void)const
double __thiscall idCompressor_BitStream::GetCompressionRatio(idCompressor_BitStream *this)
{
  if ( this->compress )
    return (double)(this->readTotalBytes - this->writeTotalBytes) * 100.0 / (double)this->readTotalBytes;
  else
    return (double)(this->writeTotalBytes - this->readTotalBytes) * 100.0 / (double)this->writeTotalBytes;
}

// FUNC: public: virtual int __thiscall idCompressor_RunLength_ZeroBased::Write(void const *,int)
int __thiscall idCompressor_RunLength_ZeroBased::Write(
        idCompressor_RunLength_ZeroBased *this,
        const unsigned __int8 *inData,
        int inLength)
{
  bool v4; // zf
  int v5; // edi
  int Bits; // eax

  if ( !this->compress || inLength <= 0 )
    return 0;
  v4 = this->writeLength == 0;
  this->readLength = inLength;
  this->readByte = 0;
  this->readBit = 0;
  this->readData = inData;
  if ( v4 )
  {
    this->writeLength = 0x10000;
    this->writeByte = 0;
    this->writeBit = 0;
    this->writeData = this->buffer;
  }
  do
  {
    v5 = 0;
    Bits = idCompressor_BitStream::ReadBits(this, this->wordLength);
    if ( Bits )
      goto LABEL_10;
    do
    {
      if ( v5 >= 1 << this->wordLength )
        break;
      ++v5;
      Bits = idCompressor_BitStream::ReadBits(this, this->wordLength);
    }
    while ( !Bits );
    if ( !v5 )
    {
LABEL_10:
      idCompressor_BitStream::WriteBits(this, Bits, this->wordLength);
    }
    else
    {
      idCompressor_BitStream::WriteBits(this, 0, this->wordLength);
      idCompressor_BitStream::WriteBits(this, v5 - 1, this->wordLength);
      idCompressor_BitStream::UnreadBits(this, this->wordLength);
    }
  }
  while ( this->readByte <= this->readLength );
  return inLength;
}

// FUNC: public: virtual int __thiscall idCompressor_RunLength_ZeroBased::Read(void *,int)
int __thiscall idCompressor_RunLength_ZeroBased::Read(
        idCompressor_RunLength_ZeroBased *this,
        unsigned __int8 *outData,
        int outLength)
{
  int Bits; // eax
  int v5; // eax
  int v6; // edi

  if ( this->compress || outLength <= 0 )
    return 0;
  if ( !this->readLength )
  {
    this->readLength = this->file->Read(this->file, this->buffer, 0x10000);
    this->readByte = 0;
    this->readBit = 0;
    this->readData = this->buffer;
  }
  this->writeLength = outLength;
  this->writeByte = 0;
  this->writeBit = 0;
  this->writeData = outData;
  do
  {
    if ( this->readLength < 0 )
      break;
    Bits = idCompressor_BitStream::ReadBits(this, this->wordLength);
    if ( Bits )
    {
      idCompressor_BitStream::WriteBits(this, Bits, this->wordLength);
    }
    else
    {
      v5 = idCompressor_BitStream::ReadBits(this, this->wordLength) + 1;
      if ( v5 > 0 )
      {
        v6 = v5;
        do
        {
          idCompressor_BitStream::WriteBits(this, 0, this->wordLength);
          --v6;
        }
        while ( v6 );
      }
    }
  }
  while ( this->writeByte <= this->writeLength );
  return this->writeByte;
}

// FUNC: public: virtual void __thiscall idCompressor_Huffman::Init(class idFile *,bool,int)
void __thiscall idCompressor_Huffman::Init(idCompressor_Huffman *this, idFile *f, bool compress, int wordLength)
{
  nodetype **nodePtrs; // eax
  nodetype *nodeList; // ecx
  int v7; // esi
  int blocNode; // eax
  nodetype *v9; // ecx
  int v10; // ecx
  nodetype *v11; // eax

  this->file = f;
  this->compress = compress;
  this->bloc = 0;
  this->blocMax = 0;
  this->blocIn = 0;
  this->blocNode = 0;
  this->blocPtrs = 0;
  this->compressedSize = 0;
  this->unCompressedSize = 0;
  this->tree = 0;
  this->lhead = 0;
  this->ltail = 0;
  memset(this->loc, 0, sizeof(this->loc));
  this->freelist = 0;
  nodePtrs = this->nodePtrs;
  nodeList = this->nodeList;
  v7 = 768;
  do
  {
    nodeList->left = 0;
    nodeList->right = 0;
    nodeList->parent = 0;
    nodeList->next = 0;
    nodeList->prev = 0;
    nodeList->head = 0;
    nodeList->weight = 0;
    nodeList->symbol = 0;
    *nodePtrs++ = 0;
    ++nodeList;
    --v7;
  }
  while ( v7 );
  if ( compress )
  {
    blocNode = this->blocNode;
    v9 = &this->nodeList[blocNode];
    this->tree = v9;
    this->lhead = v9;
    this->blocNode = blocNode + 1;
    v9->symbol = 256;
    this->tree->weight = 0;
    this->lhead->prev = 0;
    this->lhead->next = 0;
    this->tree->right = 0;
    this->tree->left = 0;
    this->tree->parent = 0;
    this->loc[256] = this->tree;
  }
  else
  {
    v10 = this->blocNode;
    v11 = &this->nodeList[v10];
    this->tree = v11;
    this->lhead = v11;
    this->loc[256] = v11;
    this->ltail = v11;
    this->blocNode = v10 + 1;
    v11->symbol = 256;
    this->tree->weight = 0;
    this->lhead->prev = 0;
    this->lhead->next = 0;
    this->tree->right = 0;
    this->tree->left = 0;
    this->tree->parent = 0;
  }
}

// FUNC: private: int __thiscall idCompressor_Huffman::Get_bit(void)
int __thiscall idCompressor_Huffman::Get_bit(idCompressor_Huffman *this)
{
  int v2; // edi
  int v3; // eax

  v2 = this->bloc >> 3;
  if ( this->bloc >> 19 != this->blocIn )
  {
    this->blocMax += this->file->Read(this->file, this->seq, 0x10000);
    ++this->blocIn;
  }
  v3 = this->seq[(unsigned __int16)v2] >> (this->bloc & 7);
  ++this->bloc;
  return v3 & 1;
}

// FUNC: private: struct nodetype * * __thiscall idCompressor_Huffman::Get_ppnode(void)
nodetype **__thiscall idCompressor_Huffman::Get_ppnode(idCompressor_Huffman *this)
{
  nodetype **result; // eax
  int blocPtrs; // edx

  result = this->freelist;
  if ( result )
  {
    this->freelist = (nodetype **)*result;
  }
  else
  {
    blocPtrs = this->blocPtrs;
    result = &this->nodePtrs[blocPtrs];
    this->blocPtrs = blocPtrs + 1;
  }
  return result;
}

// FUNC: private: void __thiscall idCompressor_Huffman::Swap(struct nodetype *,struct nodetype *)
void __thiscall idCompressor_Huffman::Swap(idCompressor_Huffman *this, nodetype *node1, nodetype *node2)
{
  nodetype *parent; // edx
  nodetype *v4; // esi

  parent = node1->parent;
  v4 = node2->parent;
  if ( parent )
  {
    if ( parent->left == node1 )
      parent->left = node2;
    else
      parent->right = node2;
  }
  else
  {
    this->tree = node2;
  }
  if ( v4 )
  {
    if ( v4->left == node2 )
      v4->left = node1;
    else
      v4->right = node1;
    node1->parent = v4;
    node2->parent = parent;
  }
  else
  {
    this->tree = node1;
    node1->parent = 0;
    node2->parent = parent;
  }
}

// FUNC: private: void __thiscall idCompressor_Huffman::Swaplist(struct nodetype *,struct nodetype *)
void __thiscall idCompressor_Huffman::Swaplist(idCompressor_Huffman *this, nodetype *node1, nodetype *node2)
{
  nodetype *next; // edx
  nodetype *prev; // esi
  nodetype *v5; // edx
  nodetype *v6; // edx
  nodetype *v7; // edx
  nodetype *v8; // edx
  nodetype *v9; // eax

  next = node1->next;
  node1->next = node2->next;
  prev = node2->prev;
  node2->next = next;
  v5 = node1->prev;
  node1->prev = prev;
  node2->prev = v5;
  if ( node1->next == node1 )
    node1->next = node2;
  if ( node2->next == node2 )
    node2->next = node1;
  v6 = node1->next;
  if ( v6 )
    v6->prev = node1;
  v7 = node2->next;
  if ( v7 )
    v7->prev = node2;
  v8 = node1->prev;
  if ( v8 )
    v8->next = node1;
  v9 = node2->prev;
  if ( v9 )
    v9->next = node2;
}

// FUNC: private: void __thiscall idCompressor_Huffman::Increment(struct nodetype *)
void __thiscall idCompressor_Huffman::Increment(idCompressor_Huffman *this, nodetype *node)
{
  nodetype *next; // eax
  nodetype **head; // ecx
  nodetype *v5; // ebx
  nodetype *prev; // eax
  nodetype **v7; // eax
  nodetype *v8; // eax
  nodetype **freelist; // eax
  int blocPtrs; // ecx
  nodetype **v11; // eax

  if ( node )
  {
    next = node->next;
    if ( next && next->weight == node->weight )
    {
      head = node->head;
      v5 = *head;
      if ( *head != node->parent )
        idCompressor_Huffman::Swap(this, v5, node);
      idCompressor_Huffman::Swaplist(this, v5, node);
    }
    prev = node->prev;
    if ( prev && prev->weight == node->weight )
    {
      *node->head = prev;
    }
    else
    {
      *node->head = 0;
      v7 = node->head;
      *v7 = (nodetype *)this->freelist;
      this->freelist = v7;
    }
    ++node->weight;
    v8 = node->next;
    if ( v8 && v8->weight == node->weight )
    {
      node->head = v8->head;
    }
    else
    {
      freelist = this->freelist;
      if ( freelist )
      {
        this->freelist = (nodetype **)*freelist;
      }
      else
      {
        blocPtrs = this->blocPtrs;
        freelist = &this->nodePtrs[blocPtrs];
        this->blocPtrs = blocPtrs + 1;
      }
      node->head = freelist;
      *freelist = node;
    }
    if ( node->parent )
    {
      idCompressor_Huffman::Increment(this, node->parent);
      if ( node->prev == node->parent )
      {
        idCompressor_Huffman::Swaplist(this, node, node->parent);
        v11 = node->head;
        if ( *v11 == node )
          *v11 = node->parent;
      }
    }
  }
}

// FUNC: private: void __thiscall idCompressor_Huffman::AddRef(unsigned char)
void __thiscall idCompressor_Huffman::AddRef(idCompressor_Huffman *this, unsigned __int8 ch)
{
  int blocNode; // eax
  nodetype *v3; // edi
  nodetype *v4; // esi
  nodetype *next; // eax
  nodetype *v6; // eax
  nodetype **freelist; // eax
  int blocPtrs; // edx
  nodetype *v9; // eax
  nodetype *v10; // eax
  nodetype **ppnode; // eax
  nodetype **v12; // eax
  int v13; // edx
  nodetype *lhead; // edx
  nodetype *parent; // eax

  if ( this->loc[ch] )
  {
    idCompressor_Huffman::Increment(this, this->loc[ch]);
    return;
  }
  blocNode = this->blocNode;
  v3 = &this->nodeList[blocNode];
  this->blocNode = blocNode + 2;
  v4 = &this->nodeList[blocNode + 1];
  v4->symbol = 257;
  v4->weight = 1;
  v4->next = this->lhead->next;
  next = this->lhead->next;
  if ( !next )
  {
    freelist = this->freelist;
    if ( freelist )
    {
      this->freelist = (nodetype **)*freelist;
    }
    else
    {
      blocPtrs = this->blocPtrs;
      freelist = &this->nodePtrs[blocPtrs];
      this->blocPtrs = blocPtrs + 1;
    }
    goto LABEL_9;
  }
  next->prev = v4;
  v6 = this->lhead->next;
  if ( v6->weight != 1 )
  {
    freelist = idCompressor_Huffman::Get_ppnode(this);
LABEL_9:
    v4->head = freelist;
    *freelist = v4;
    goto LABEL_10;
  }
  v4->head = v6->head;
LABEL_10:
  this->lhead->next = v4;
  v4->prev = this->lhead;
  v3->symbol = ch;
  v3->weight = 1;
  v3->next = this->lhead->next;
  v9 = this->lhead->next;
  if ( v9 )
  {
    v9->prev = v3;
    v10 = this->lhead->next;
    if ( v10->weight == 1 )
    {
      v3->head = v10->head;
    }
    else
    {
      ppnode = idCompressor_Huffman::Get_ppnode(this);
      v3->head = ppnode;
      *ppnode = v4;
    }
  }
  else
  {
    v12 = this->freelist;
    if ( v12 )
    {
      this->freelist = (nodetype **)*v12;
    }
    else
    {
      v13 = this->blocPtrs;
      v12 = &this->nodePtrs[v13];
      this->blocPtrs = v13 + 1;
    }
    v3->head = v12;
    *v12 = v3;
  }
  this->lhead->next = v3;
  v3->prev = this->lhead;
  v3->right = 0;
  v3->left = 0;
  lhead = this->lhead;
  parent = lhead->parent;
  if ( parent )
  {
    if ( parent->left == lhead )
      parent->left = v4;
    else
      parent->right = v4;
  }
  else
  {
    this->tree = v4;
  }
  v4->right = v3;
  v4->left = this->lhead;
  v4->parent = this->lhead->parent;
  v3->parent = v4;
  this->lhead->parent = v4;
  this->loc[ch] = v3;
  idCompressor_Huffman::Increment(this, v4->parent);
}

// FUNC: private: int __thiscall idCompressor_Huffman::Receive(struct nodetype *,int *)
int __thiscall idCompressor_Huffman::Receive(idCompressor_Huffman *this, nodetype *node, int *ch)
{
  nodetype *v3; // ebx
  int v5; // edi
  char bloc; // cl
  unsigned int v7; // edx
  int result; // eax

  v3 = node;
  if ( !node )
    return 0;
  while ( v3->symbol == 257 )
  {
    v5 = this->bloc >> 3;
    if ( this->bloc >> 19 != this->blocIn )
    {
      this->blocMax += this->file->Read(this->file, this->seq, 0x10000);
      ++this->blocIn;
    }
    bloc = this->bloc;
    v7 = this->seq[(unsigned __int16)v5];
    ++this->bloc;
    if ( ((v7 >> (bloc & 7)) & 1) != 0 )
      v3 = v3->right;
    else
      v3 = v3->left;
    if ( !v3 )
      return 0;
  }
  result = v3->symbol;
  *ch = result;
  return result;
}

// FUNC: private: void __thiscall idCompressor_Huffman::Send(struct nodetype *,struct nodetype *,unsigned char *)
void __thiscall idCompressor_Huffman::Send(
        idCompressor_Huffman *this,
        nodetype *node,
        nodetype *child,
        unsigned __int8 *fout)
{
  nodetype *parent; // eax
  int bloc; // eax
  char v7; // dl

  parent = node->parent;
  if ( parent )
    idCompressor_Huffman::Send(this, parent, node, fout);
  if ( child )
  {
    bloc = this->bloc;
    if ( node->right == child )
    {
      if ( (bloc & 7) == 0 )
        fout[bloc >> 3] = 0;
      v7 = 1;
    }
    else
    {
      if ( (bloc & 7) == 0 )
        fout[bloc >> 3] = 0;
      v7 = 0;
    }
    fout[this->bloc >> 3] |= v7 << (this->bloc & 7);
    ++this->bloc;
  }
}

// FUNC: private: void __thiscall idCompressor_Huffman::Transmit(int,unsigned char *)
void __thiscall idCompressor_Huffman::Transmit(idCompressor_Huffman *this, int ch, unsigned __int8 *fout)
{
  nodetype *v4; // eax
  int bloc; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  nodetype *parent; // ecx

  v4 = this->loc[ch];
  if ( v4 )
  {
    parent = v4->parent;
    if ( parent )
      idCompressor_Huffman::Send(this, parent, v4, fout);
  }
  else
  {
    idCompressor_Huffman::Transmit(this, 256, fout);
    bloc = this->bloc;
    if ( (bloc & 7) == 0 )
      fout[bloc >> 3] = 0;
    fout[this->bloc++ >> 3] |= ((ch >> 7) & 1) << (this->bloc & 7);
    v6 = this->bloc;
    if ( (v6 & 7) == 0 )
      fout[v6 >> 3] = 0;
    fout[this->bloc++ >> 3] |= ((ch >> 6) & 1) << (this->bloc & 7);
    v7 = this->bloc;
    if ( (v7 & 7) == 0 )
      fout[v7 >> 3] = 0;
    fout[this->bloc++ >> 3] |= ((ch >> 5) & 1) << (this->bloc & 7);
    v8 = this->bloc;
    if ( (v8 & 7) == 0 )
      fout[v8 >> 3] = 0;
    fout[this->bloc++ >> 3] |= ((ch >> 4) & 1) << (this->bloc & 7);
    v9 = this->bloc;
    if ( (v9 & 7) == 0 )
      fout[v9 >> 3] = 0;
    fout[this->bloc++ >> 3] |= ((ch >> 3) & 1) << (this->bloc & 7);
    v10 = this->bloc;
    if ( (v10 & 7) == 0 )
      fout[v10 >> 3] = 0;
    fout[this->bloc++ >> 3] |= ((ch >> 2) & 1) << (this->bloc & 7);
    v11 = this->bloc;
    if ( (v11 & 7) == 0 )
      fout[v11 >> 3] = 0;
    fout[this->bloc++ >> 3] |= ((ch >> 1) & 1) << (this->bloc & 7);
    v12 = this->bloc;
    if ( (v12 & 7) == 0 )
      fout[v12 >> 3] = 0;
    fout[this->bloc >> 3] |= (ch & 1) << (this->bloc & 7);
    ++this->bloc;
  }
}

// FUNC: public: virtual int __thiscall idCompressor_Huffman::Write(void const *,int)
int __thiscall idCompressor_Huffman::Write(idCompressor_Huffman *this, _BYTE *inData, int inLength)
{
  int v4; // ebp
  unsigned __int8 *seq; // ebx
  unsigned __int8 v6; // di
  int v7; // edi
  unsigned __int8 v8; // al

  if ( !this->compress || inLength <= 0 )
    return 0;
  v4 = 0;
  seq = this->seq;
  do
  {
    v6 = inData[v4];
    idCompressor_Huffman::Transmit(this, v6, this->seq);
    idCompressor_Huffman::AddRef(this, v6);
    v7 = this->bloc >> 3;
    if ( v7 > 0x8000 )
    {
      this->file->Write(this->file, this->seq, this->bloc >> 3);
      v8 = seq[v7];
      this->bloc &= 7u;
      this->compressedSize += v7;
      *seq = v8;
    }
    ++v4;
  }
  while ( v4 < inLength );
  this->unCompressedSize += v4;
  return v4;
}

// FUNC: public: virtual void __thiscall idCompressor_Huffman::FinishCompress(void)
void __thiscall idCompressor_Huffman::FinishCompress(idCompressor_Huffman *this)
{
  int v2; // edi

  if ( this->compress )
  {
    this->bloc += 7;
    v2 = this->bloc >> 3;
    if ( v2 )
    {
      this->file->Write(this->file, this->seq, v2);
      this->compressedSize += v2;
    }
  }
}

// FUNC: public: virtual int __thiscall idCompressor_Huffman::Read(void *,int)
int __thiscall idCompressor_Huffman::Read(idCompressor_Huffman *this, _BYTE *outData, int outLength)
{
  int v4; // ebp
  int v5; // edi
  bool v6; // cc
  unsigned __int8 v7; // bl
  int v8; // ebp
  int v9; // ecx
  int result; // eax
  unsigned __int8 v11[4]; // [esp+Ch] [ebp-4h] BYREF

  if ( this->compress )
    return 0;
  v4 = outLength;
  v5 = 0;
  if ( outLength <= 0 )
    return 0;
  if ( !this->bloc )
  {
    this->blocMax = this->file->Read(this->file, this->seq, 0x10000);
    this->blocIn = 0;
  }
  do
  {
    v6 = this->bloc >> 3 <= this->blocMax;
    *(_DWORD *)v11 = 0;
    if ( !v6 )
      break;
    idCompressor_Huffman::Receive(this, this->tree, (int *)v11);
    v7 = v11[0];
    if ( *(_DWORD *)v11 == 256 )
    {
      v7 = 0;
      v8 = 8;
      do
      {
        --v8;
        v7 = idCompressor_Huffman::Get_bit(this) + 2 * v7;
      }
      while ( v8 );
      v4 = outLength;
    }
    outData[v5] = v7;
    idCompressor_Huffman::AddRef(this, v7);
    ++v5;
  }
  while ( v5 < v4 );
  v9 = this->bloc >> 3;
  this->unCompressedSize += v5;
  result = v5;
  this->compressedSize = v9;
  return result;
}

// FUNC: public: virtual float __thiscall idCompressor_Huffman::GetCompressionRatio(void)const
double __thiscall idCompressor_Huffman::GetCompressionRatio(idCompressor_Huffman *this)
{
  return (double)(this->unCompressedSize - this->compressedSize) * 100.0 / (double)this->unCompressedSize;
}

// FUNC: public: virtual void __thiscall idCompressor_LZSS::Init(class idFile *,bool,int)
void __thiscall idCompressor_LZSS::Init(idCompressor_LZSS *this, idFile *f, bool compress, int wordLength)
{
  this->file = f;
  this->compress = compress;
  this->wordLength = wordLength;
  this->readTotalBytes = 0;
  this->readLength = 0;
  this->readByte = 0;
  this->readBit = 0;
  this->readData = 0;
  this->writeTotalBytes = 0;
  this->writeLength = 0;
  this->writeByte = 0;
  this->writeBit = 0;
  this->writeData = 0;
  this->blockSize = 0;
  this->blockIndex = 0;
  this->offsetBits = 11;
  this->lengthBits = 5;
  this->minMatchWords = (wordLength + 16) / wordLength;
}

// FUNC: protected: int __thiscall idCompressor_LZSS::GetWordFromBlock(int)const
int __thiscall idCompressor_LZSS::GetWordFromBlock(idCompressor_LZSS *this, int wordOffset)
{
  idCompressor_LZSS *v2; // ebp
  int v3; // ebx
  int v4; // eax
  int v5; // esi
  int wordLength; // edi
  int v7; // edx
  char v8; // cl
  int v9; // eax
  int blockByte; // [esp+10h] [ebp-8h]
  int wordOffseta; // [esp+1Ch] [ebp+4h]

  v2 = this;
  v3 = ((_BYTE)wordOffset * LOBYTE(this->wordLength)) & 7;
  v4 = (wordOffset * this->wordLength) >> 3;
  v5 = 0;
  blockByte = v4;
  if ( (((_BYTE)wordOffset * LOBYTE(this->wordLength)) & 7) != 0 )
    blockByte = ++v4;
  wordLength = this->wordLength;
  wordOffseta = 0;
  if ( wordLength > 0 )
  {
    while ( 1 )
    {
      if ( !v3 )
      {
        if ( v4 >= 0xFFFF )
          return wordOffseta;
        blockByte = ++v4;
      }
      v7 = 8 - v3;
      if ( 8 - v3 > wordLength - v5 )
        v7 = wordLength - v5;
      v8 = v5;
      v5 += v7;
      v9 = (((1 << v7) - 1) & (*((unsigned __int8 *)&v2->minMatchWords + v4 + 3) >> v3)) << v8;
      v3 = ((_BYTE)v7 + (_BYTE)v3) & 7;
      wordOffseta |= v9;
      if ( v5 >= wordLength )
        break;
      v4 = blockByte;
      v2 = this;
    }
  }
  return wordOffseta;
}

// FUNC: public: virtual int __thiscall idCompressor_LZSS::Write(void const *,int)
int __thiscall idCompressor_LZSS::Write(idCompressor_LZSS *this, char *inData, int inLength)
{
  int result; // eax
  int i; // ebx
  int v6; // ebp
  idSIMDProcessor_vtbl *v7; // eax
  int v8; // edi
  int v9; // ebp
  idCompressor_LZSS_vtbl *v10; // edx

  if ( !this->compress )
    return 0;
  result = inLength;
  if ( inLength <= 0 )
    return 0;
  for ( i = 0; i < inLength; i += v8 )
  {
    v6 = result;
    v7 = SIMDProcessor->__vftable;
    v8 = 0xFFFF - this->blockSize;
    v9 = v6 - i;
    if ( v9 < v8 )
    {
      ((void (__stdcall *)(char *, int))v7->Memcpy)(&inData[i], v9);
      v8 = v9;
      this->blockSize += v9;
    }
    else
    {
      ((void (__stdcall *)(char *, int))v7->Memcpy)(&inData[i], v8);
      v10 = this->__vftable;
      this->blockSize = 0xFFFF;
      v10->CompressBlock(this);
      this->blockSize = 0;
    }
    result = inLength;
  }
  return result;
}

// FUNC: public: virtual void __thiscall idCompressor_LZSS::FinishCompress(void)
void __thiscall idCompressor_LZSS::FinishCompress(idCompressor_LZSS *this)
{
  if ( this->compress )
  {
    if ( this->blockSize )
      this->CompressBlock(this);
    if ( this->compress )
    {
      if ( this->writeByte )
        this->file->Write(this->file, this->buffer, this->writeByte);
      this->writeLength = 0;
      this->writeByte = 0;
      this->writeBit = 0;
    }
  }
}

// FUNC: public: virtual int __thiscall idCompressor_LZSS::Read(void *,int)
int __thiscall idCompressor_LZSS::Read(idCompressor_LZSS *this, char *outData, int outLength)
{
  int v4; // ebx
  int v5; // ebp
  int blockSize; // edi
  int blockIndex; // eax
  int v8; // edi
  int v9; // ebx

  if ( this->compress )
    return 0;
  v4 = outLength;
  if ( outLength <= 0 )
    return 0;
  if ( !this->blockSize )
    this->DecompressBlock(this);
  v5 = 0;
  while ( 1 )
  {
    blockSize = this->blockSize;
    if ( !blockSize )
      break;
    blockIndex = this->blockIndex;
    v8 = blockSize - blockIndex;
    v9 = v4 - v5;
    if ( v9 < v8 )
    {
      SIMDProcessor->Memcpy(SIMDProcessor, &outData[v5], &this->block[blockIndex], v9);
      v8 = v9;
      this->blockIndex += v9;
    }
    else
    {
      SIMDProcessor->Memcpy(SIMDProcessor, &outData[v5], &this->block[blockIndex], v8);
      this->DecompressBlock(this);
      this->blockIndex = 0;
    }
    v4 = outLength;
    v5 += v8;
    if ( v5 >= outLength )
      return outLength;
  }
  return v5;
}

// FUNC: public: virtual void __thiscall idCompressor_LZW::FinishCompress(void)
void __thiscall idCompressor_LZW::FinishCompress(idCompressor_LZW *this)
{
  idCompressor_BitStream::WriteBits(this, this->w, this->codeBits);
  if ( this->compress )
  {
    if ( this->writeByte )
      this->file->Write(this->file, this->buffer, this->writeByte);
    this->writeLength = 0;
    this->writeByte = 0;
    this->writeBit = 0;
  }
}

// FUNC: protected: int __thiscall idCompressor_LZW::WriteChain(int)
int __thiscall idCompressor_LZW::WriteChain(idCompressor_LZW *this, int code)
{
  int v4; // esi
  char k; // cl
  int v6; // ebx
  int i; // esi
  char v9[4097]; // [esp+Bh] [ebp-1001h]

  v4 = 0;
  do
  {
    k = this->dictionary[code].k;
    code = this->dictionary[code].w;
    v9[++v4] = k;
  }
  while ( code >= 0 );
  v6 = (unsigned __int8)v9[v4];
  for ( i = v4 - 1; i >= 0; --i )
    idCompressor_BitStream::WriteBits(this, (unsigned __int8)v9[i + 1], 8);
  return v6;
}

// FUNC: protected: bool __thiscall idCompressor_LZSS::FindMatch(int,int,int &,int &)
BOOL __thiscall idCompressor_LZSS::FindMatch(
        idCompressor_LZSS *this,
        int startWord,
        __int16 startValue,
        int *wordOffset,
        int *numWords)
{
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // edi
  int wordLength; // ebx
  int v12; // eax
  int maxBits; // [esp+Ch] [ebp-8h]
  int bottom; // [esp+10h] [ebp-4h]
  int startWorda; // [esp+18h] [ebp+4h]

  *wordOffset = startWord;
  v7 = this->minMatchWords - 1;
  *numWords = v7;
  v8 = startWord - (1 << this->offsetBits);
  v9 = 8 * this->blockSize - startWord * this->wordLength;
  v10 = this->hashTable[startValue & 0x3FF];
  bottom = v8 + 1 < 0 ? 0 : v8 + 1;
  maxBits = v9;
  if ( v10 >= bottom )
  {
    startWorda = v7;
    while ( 1 )
    {
      wordLength = this->wordLength;
      if ( v9 >= wordLength * (startWord - v10) )
        v9 = wordLength * (startWord - v10);
      v12 = idCompressor_BitStream::Compare(
              this,
              this->block,
              v10 * this->wordLength,
              this->block,
              startWord * this->wordLength,
              v9);
      if ( v12 > wordLength * startWorda )
      {
        *numWords = v12 / wordLength;
        *wordOffset = v10;
        startWorda = *numWords;
        if ( *numWords > (1 << this->lengthBits) + this->minMatchWords - 2 )
          break;
      }
      v10 = this->hashNext[v10];
      if ( v10 < bottom )
        return *numWords >= this->minMatchWords;
      v9 = maxBits;
    }
    *numWords = (1 << this->lengthBits) + this->minMatchWords - 2;
  }
  return *numWords >= this->minMatchWords;
}

// FUNC: protected: virtual void __thiscall idCompressor_LZSS::CompressBlock(void)
void __thiscall idCompressor_LZSS::CompressBlock(idCompressor_LZSS *this)
{
  bool v2; // zf
  int v3; // edi
  int Bits; // ebx
  int v5; // ebp
  int *v6; // ebx
  int v7; // eax
  int v8; // ebx
  int wordOffset; // [esp+Ch] [ebp-8h] BYREF
  int numWords; // [esp+10h] [ebp-4h] BYREF

  v2 = this->writeLength == 0;
  this->readLength = this->blockSize;
  this->readByte = 0;
  this->readBit = 0;
  this->readData = this->block;
  if ( v2 )
  {
    this->writeLength = 0x10000;
    this->writeByte = 0;
    this->writeBit = 0;
    this->writeData = this->buffer;
  }
  memset(this->hashTable, 0xFFu, sizeof(this->hashTable));
  memset(this->hashNext, 0xFFu, sizeof(this->hashNext));
  v3 = 0;
  while ( this->readByte < this->readLength )
  {
    Bits = idCompressor_BitStream::ReadBits(this, this->wordLength);
    if ( idCompressor_LZSS::FindMatch(this, v3, Bits, &wordOffset, &numWords) )
    {
      idCompressor_BitStream::WriteBits(this, 1, 1);
      idCompressor_BitStream::WriteBits(this, v3 - wordOffset, this->offsetBits);
      v5 = numWords;
      idCompressor_BitStream::WriteBits(this, numWords - this->minMatchWords, this->lengthBits);
      idCompressor_BitStream::UnreadBits(this, this->wordLength);
      if ( v5 > 0 )
      {
        v6 = &this->hashNext[v3];
        do
        {
          v7 = idCompressor_BitStream::ReadBits(this, this->wordLength) & 0x3FF;
          *v6 = this->hashTable[v7];
          this->hashTable[v7] = v3++;
          ++v6;
          --v5;
        }
        while ( v5 );
      }
    }
    else
    {
      idCompressor_BitStream::WriteBits(this, 0, 1);
      idCompressor_BitStream::WriteBits(this, Bits, this->wordLength);
      v8 = Bits & 0x3FF;
      this->hashNext[v3] = this->hashTable[v8];
      this->hashTable[v8] = v3++;
    }
  }
  this->blockSize = 0;
}

// FUNC: protected: virtual void __thiscall idCompressor_LZSS::DecompressBlock(void)
void __thiscall idCompressor_LZSS::DecompressBlock(idCompressor_LZSS *this)
{
  int v2; // ebx
  int v3; // ebp
  int v4; // edi
  int WordFromBlock; // eax
  int Bits; // eax
  int writeByte; // eax
  int wordLength; // [esp-4h] [ebp-18h]
  int v9; // [esp-4h] [ebp-18h]
  int startWord; // [esp+10h] [ebp-4h]

  v2 = 0;
  if ( !this->readLength )
  {
    this->readLength = this->file->Read(this->file, this->buffer, 0x10000);
    this->readByte = 0;
    this->readBit = 0;
    this->readData = this->buffer;
  }
  this->writeLength = 0xFFFF;
  this->writeByte = 0;
  this->writeBit = 0;
  this->writeData = this->block;
  startWord = 0;
  while ( this->readLength >= 0 )
  {
    if ( idCompressor_BitStream::ReadBits(this, 1) )
    {
      v3 = startWord - idCompressor_BitStream::ReadBits(this, this->offsetBits);
      v4 = this->minMatchWords + idCompressor_BitStream::ReadBits(this, this->lengthBits);
      if ( v4 > 0 )
      {
        startWord += v4;
        do
        {
          wordLength = this->wordLength;
          WordFromBlock = idCompressor_LZSS::GetWordFromBlock(this, v2 + v3);
          idCompressor_BitStream::WriteBits(this, WordFromBlock, wordLength);
          ++v2;
        }
        while ( v2 < v4 );
      }
    }
    else
    {
      v9 = this->wordLength;
      Bits = idCompressor_BitStream::ReadBits(this, v9);
      idCompressor_BitStream::WriteBits(this, Bits, v9);
      ++startWord;
    }
    if ( this->writeByte >= this->writeLength )
      break;
    v2 = 0;
  }
  writeByte = this->writeByte;
  if ( writeByte >= 0xFFFF )
    writeByte = 0xFFFF;
  this->blockSize = writeByte;
}

// FUNC: public: virtual void __thiscall idCompressor_LZW::Init(class idFile *,bool,int)
void __thiscall idCompressor_LZW::Init(idCompressor_LZW *this, idFile *f, bool compress, int wordLength)
{
  int v5; // eax
  int *p_w; // ecx
  int *hash; // edi

  this->file = f;
  this->compress = compress;
  this->wordLength = wordLength;
  this->readTotalBytes = 0;
  this->readLength = 0;
  this->readByte = 0;
  this->readBit = 0;
  this->readData = 0;
  this->writeTotalBytes = 0;
  this->writeLength = 0;
  this->writeByte = 0;
  this->writeBit = 0;
  this->writeData = 0;
  v5 = 0;
  p_w = &this->dictionary[0].w;
  do
  {
    *(p_w - 1) = v5;
    *p_w = -1;
    ++v5;
    p_w += 2;
  }
  while ( v5 < 256 );
  hash = this->index.hash;
  if ( hash != idHashIndex::INVALID_INDEX )
    memset(hash, 0xFFu, 4 * this->index.hashSize);
  this->blockSize = 0;
  this->blockIndex = 0;
  this->nextCode = 256;
  this->codeBits = 9;
  this->w = -1;
  this->oldCode = -1;
}

// FUNC: protected: int __thiscall idCompressor_LZW::Lookup(int,int)
int __thiscall idCompressor_LZW::Lookup(idCompressor_LZW *this, int w, int k)
{
  int result; // eax

  if ( w == -1 )
    return k;
  result = this->index.hash[this->index.hashMask & this->index.lookupMask & (k ^ w)];
  if ( result < 0 )
    return -1;
  while ( this->dictionary[result].k != k || this->dictionary[result].w != w )
  {
    result = this->index.indexChain[result & this->index.lookupMask];
    if ( result < 0 )
      return -1;
  }
  return result;
}

// FUNC: protected: int __thiscall idCompressor_LZW::AddToDict(int,int)
int __thiscall idCompressor_LZW::AddToDict(idCompressor_LZW *this, int w, int k)
{
  int nextCode; // ebp
  int indexSize; // eax
  int v6; // ebx
  int result; // eax

  this->dictionary[this->nextCode].k = k;
  this->dictionary[this->nextCode].w = w;
  nextCode = this->nextCode;
  if ( this->index.hash == idHashIndex::INVALID_INDEX )
  {
    indexSize = this->index.indexSize;
    if ( nextCode >= indexSize )
      indexSize = nextCode + 1;
    idHashIndex::Allocate(&this->index, this->index.hashSize, indexSize);
  }
  else if ( nextCode >= this->index.indexSize )
  {
    idHashIndex::ResizeIndex(&this->index, nextCode + 1);
  }
  v6 = this->index.hashMask & (k ^ w);
  this->index.indexChain[nextCode] = this->index.hash[v6];
  this->index.hash[v6] = nextCode;
  result = this->nextCode;
  this->nextCode = result + 1;
  return result;
}

// FUNC: protected: bool __thiscall idCompressor_LZW::BumpBits(void)
char __thiscall idCompressor_LZW::BumpBits(idCompressor_LZW *this)
{
  int codeBits; // ecx
  int v3; // ecx
  int *hash; // edi

  codeBits = this->codeBits;
  if ( this->nextCode != 1 << codeBits )
    return 0;
  v3 = codeBits + 1;
  this->codeBits = v3;
  if ( v3 <= 12 )
    return 0;
  this->nextCode = 256;
  this->codeBits = 9;
  hash = this->index.hash;
  if ( hash != idHashIndex::INVALID_INDEX )
    memset(hash, 0xFFu, 4 * this->index.hashSize);
  return 1;
}

// FUNC: public: virtual int __thiscall idCompressor_LZW::Write(void const *,int)
char *__thiscall idCompressor_LZW::Write(idCompressor_LZW *this, const unsigned __int8 *inData, char *inLength)
{
  char *result; // eax
  bool v5; // zf
  int Bits; // eax
  int w; // ebx
  int v8; // edi
  int v9; // eax
  char *inDataa; // [esp+Ch] [ebp+4h]

  result = inLength;
  v5 = this->writeLength == 0;
  this->readLength = (int)inLength;
  this->readByte = 0;
  this->readBit = 0;
  this->readData = inData;
  if ( v5 )
  {
    this->writeLength = 0x10000;
    this->writeByte = 0;
    this->writeBit = 0;
    this->writeData = this->buffer;
  }
  if ( (int)inLength > 0 )
  {
    inDataa = inLength;
    do
    {
      Bits = idCompressor_BitStream::ReadBits(this, 8);
      w = this->w;
      v8 = Bits;
      v9 = idCompressor_LZW::Lookup(this, w, Bits);
      if ( v9 < 0 )
      {
        idCompressor_BitStream::WriteBits(this, w, this->codeBits);
        if ( !idCompressor_LZW::BumpBits(this) )
          idCompressor_LZW::AddToDict(this, this->w, v8);
        this->w = v8;
      }
      else
      {
        this->w = v9;
      }
      --inDataa;
    }
    while ( inDataa );
    return inLength;
  }
  return result;
}

// FUNC: protected: void __thiscall idCompressor_LZW::DecompressBlock(void)
void __thiscall idCompressor_LZW::DecompressBlock(idCompressor_LZW *this)
{
  int Bits; // ebx
  int writeByte; // eax
  int v4; // edi

  if ( !this->readLength )
  {
    this->readLength = this->file->Read(this->file, this->buffer, 0x10000);
    this->readByte = 0;
    this->readBit = 0;
    this->readData = this->buffer;
  }
  this->writeLength = 0x7FFF;
  this->writeByte = 0;
  this->writeBit = 0;
  this->writeData = this->block;
  do
  {
    if ( this->readLength <= 0 )
      break;
    Bits = idCompressor_BitStream::ReadBits(this, this->codeBits);
    if ( !this->readLength )
      break;
    if ( this->oldCode == -1 )
    {
      idCompressor_BitStream::WriteBits(this, Bits, 8);
    }
    else
    {
      if ( Bits < this->nextCode )
      {
        v4 = idCompressor_LZW::WriteChain(this, Bits);
      }
      else
      {
        v4 = idCompressor_LZW::WriteChain(this, this->oldCode);
        idCompressor_BitStream::WriteBits(this, v4, 8);
      }
      idCompressor_LZW::AddToDict(this, this->oldCode, v4);
      if ( idCompressor_LZW::BumpBits(this) )
      {
        this->oldCode = -1;
        continue;
      }
    }
    this->oldCode = Bits;
  }
  while ( this->writeByte < this->writeLength - 4096 );
  writeByte = this->writeByte;
  if ( writeByte >= 0x7FFF )
    writeByte = 0x7FFF;
  this->blockSize = writeByte;
}

// FUNC: public: virtual int __thiscall idCompressor_LZW::Read(void *,int)
int __thiscall idCompressor_LZW::Read(idCompressor_LZW *this, char *outData, int outLength)
{
  int v4; // edi
  int result; // eax
  int blockSize; // ebp
  int blockIndex; // esi
  signed int v8; // ebp
  unsigned int v9; // edx
  unsigned __int8 *v10; // esi
  int i; // [esp+8h] [ebp-4h]

  if ( this->compress )
    return 0;
  v4 = outLength;
  if ( outLength <= 0 )
    return 0;
  if ( !this->blockSize )
    idCompressor_LZW::DecompressBlock(this);
  result = 0;
  i = 0;
  while ( 1 )
  {
    blockSize = this->blockSize;
    if ( !blockSize )
      break;
    blockIndex = this->blockIndex;
    v8 = blockSize - blockIndex;
    v9 = v4 - result;
    v10 = &this->block[blockIndex];
    if ( v4 - result < v8 )
    {
      v8 = v4 - result;
      qmemcpy(&outData[result], v10, v9);
      this->blockIndex += v9;
    }
    else
    {
      qmemcpy(&outData[result], v10, v8);
      idCompressor_LZW::DecompressBlock(this);
      result = i;
      this->blockIndex = 0;
    }
    v4 = outLength;
    result += v8;
    i = result;
    if ( result >= outLength )
      return outLength;
  }
  return result;
}

// FUNC: public: __thiscall idCompressor_LZW::idCompressor_LZW(void)
void __thiscall idCompressor_LZW::idCompressor_LZW(idCompressor_LZW *this)
{
  this->file = 0;
  this->compress = 1;
  this->__vftable = (idCompressor_LZW_vtbl *)&idCompressor_LZW::`vftable';
  idHashIndex::Init(&this->index, 1024, 1024);
}

// FUNC: public: static class idCompressor * __cdecl idCompressor::AllocNoCompression(void)
idCompressor *__cdecl idCompressor::AllocNoCompression()
{
  idCompressor *result; // eax

  result = (idCompressor *)Memory::Allocate(0xCu);
  if ( !result )
    return 0;
  result->__vftable = (idCompressor_vtbl *)&idCompressor_None::`vftable';
  result[1].__vftable = 0;
  LOBYTE(result[2].__vftable) = 1;
  return result;
}

// FUNC: public: static class idCompressor * __cdecl idCompressor::AllocRunLength_ZeroBased(void)
idCompressor *__cdecl idCompressor::AllocRunLength_ZeroBased()
{
  idCompressor *result; // eax

  result = (idCompressor *)Memory::Allocate(0x10038u);
  if ( !result )
    return 0;
  result[1].__vftable = 0;
  LOBYTE(result[2].__vftable) = 1;
  result->__vftable = (idCompressor_vtbl *)&idCompressor_RunLength_ZeroBased::`vftable';
  return result;
}

// FUNC: public: static class idCompressor * __cdecl idCompressor::AllocHuffman(void)
idCompressor *__cdecl idCompressor::AllocHuffman()
{
  idCompressor *result; // eax

  result = (idCompressor *)Memory::Allocate(0x1703Cu);
  if ( !result )
    return 0;
  result[1].__vftable = 0;
  LOBYTE(result[2].__vftable) = 1;
  result->__vftable = (idCompressor_vtbl *)&idCompressor_Huffman::`vftable';
  return result;
}

// FUNC: public: static class idCompressor * __cdecl idCompressor::AllocLZSS(void)
idCompressor *__cdecl idCompressor::AllocLZSS()
{
  idCompressor *result; // eax

  result = (idCompressor *)Memory::Allocate(0x22102Cu);
  if ( !result )
    return 0;
  result[1].__vftable = 0;
  LOBYTE(result[2].__vftable) = 1;
  result->__vftable = (idCompressor_vtbl *)&idCompressor_LZSS::`vftable';
  return result;
}

// FUNC: public: static class idCompressor * __cdecl idCompressor::AllocLZW(void)
void __cdecl idCompressor::AllocLZW()
{
  idCompressor_LZW *v0; // eax

  v0 = (idCompressor_LZW *)Memory::Allocate(0x2006Cu);
  if ( v0 )
    idCompressor_LZW::idCompressor_LZW(v0);
}

// FUNC: public: int __thiscall idBitMsg::ReadBits(int)const
int __thiscall idBitMsg::ReadBits(idBitMsg *this, int numBits)
{
  idBitMsg *v2; // ebp
  int v3; // edi
  int result; // eax
  int v5; // esi
  int readBit; // ebx
  int v7; // edx
  char v8; // cl
  int value; // [esp+Ch] [ebp-Ch]
  const unsigned __int8 *readData; // [esp+10h] [ebp-8h]
  char numBitsa; // [esp+1Ch] [ebp+4h]

  v2 = this;
  if ( !this->readData )
    idLib::common->FatalError(idLib::common, "idBitMsg::ReadBits: cannot read from message");
  v3 = numBits;
  if ( !numBits || numBits < -31 || numBits > 32 )
    idLib::common->FatalError(idLib::common, "idBitMsg::ReadBits: bad numBits %i", numBits);
  result = 0;
  v5 = 0;
  value = 0;
  if ( numBits >= 0 )
  {
    numBitsa = 0;
  }
  else
  {
    v3 = -numBits;
    numBitsa = 1;
  }
  if ( v3 > (-v2->readBit & 7) - 8 * v2->readCount + 8 * v2->curSize )
    return -1;
  if ( v3 > 0 )
  {
    readData = v2->readData;
    do
    {
      readBit = v2->readBit;
      if ( !readBit )
        ++v2->readCount;
      v7 = 8 - readBit;
      if ( 8 - readBit > v3 - v5 )
        v7 = v3 - v5;
      v8 = v5;
      v5 += v7;
      result = ((((1 << v7) - 1) & (readData[v2->readCount - 1] >> readBit)) << v8) | value;
      v2 = this;
      value = result;
      this->readBit = ((_BYTE)v7 + (_BYTE)readBit) & 7;
    }
    while ( v5 < v3 );
  }
  if ( numBitsa )
  {
    if ( ((1 << (v3 - 1)) & result) != 0 )
      return ~((1 << v3) - 1) | result;
  }
  return result;
}

// FUNC: public: int __thiscall idBitMsgDelta::ReadBits(int)const
int __thiscall idBitMsgDelta::ReadBits(idBitMsgDelta *this, int numBits)
{
  idBitMsg *base; // ecx
  int Bits; // eax
  idBitMsg *readDelta; // ecx
  int v6; // edi
  idBitMsg *newBase; // ecx
  int v9; // [esp-4h] [ebp-10h]

  base = (idBitMsg *)this->base;
  v9 = numBits;
  if ( !base )
    goto LABEL_5;
  Bits = idBitMsg::ReadBits(base, numBits);
  readDelta = (idBitMsg *)this->readDelta;
  v6 = Bits;
  if ( readDelta && idBitMsg::ReadBits(readDelta, 1) )
  {
    v9 = numBits;
LABEL_5:
    v6 = idBitMsg::ReadBits((idBitMsg *)this->readDelta, v9);
    this->changed = 1;
  }
  newBase = this->newBase;
  if ( newBase )
    idBitMsg::WriteBits(newBase, v6, numBits);
  return v6;
}
