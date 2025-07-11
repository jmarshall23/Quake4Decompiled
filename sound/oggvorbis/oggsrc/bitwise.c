
// FUNC: _oggpack_writeinit
void __cdecl oggpack_writeinit(oggpack_buffer *b)
{
  unsigned __int8 *v1; // eax

  b->endbyte = 0;
  b->endbit = 0;
  b->buffer = 0;
  b->ptr = 0;
  b->storage = 0;
  v1 = (unsigned __int8 *)_decoder_malloc(0x100u);
  b->buffer = v1;
  b->ptr = v1;
  *v1 = 0;
  b->storage = 256;
}

// FUNC: _oggpack_write
void __cdecl oggpack_write(oggpack_buffer *b, unsigned int value, int bits)
{
  int storage; // eax
  unsigned __int8 *v4; // eax
  int endbyte; // ecx
  unsigned int v6; // eax
  int endbit; // ecx
  int v8; // edi
  int v9; // edx

  storage = b->storage;
  if ( b->endbyte + 4 >= storage )
  {
    v4 = (unsigned __int8 *)_decoder_realloc(b->buffer, storage + 256);
    endbyte = b->endbyte;
    b->storage += 256;
    b->buffer = v4;
    b->ptr = &v4[endbyte];
  }
  v6 = mask[bits] & value;
  endbit = b->endbit;
  v8 = endbit + bits;
  *b->ptr |= (_BYTE)v6 << endbit;
  if ( endbit + bits >= 8 )
  {
    b->ptr[1] = v6 >> (8 - LOBYTE(b->endbit));
    if ( v8 >= 16 )
    {
      b->ptr[2] = v6 >> (16 - LOBYTE(b->endbit));
      if ( v8 >= 24 )
      {
        b->ptr[3] = v6 >> (24 - LOBYTE(b->endbit));
        if ( v8 >= 32 )
        {
          v9 = b->endbit;
          if ( v9 )
            b->ptr[4] = v6 >> (32 - v9);
          else
            b->ptr[4] = 0;
        }
      }
    }
  }
  b->endbyte += v8 / 8;
  b->ptr += v8 / 8;
  b->endbit = v8 & 7;
}

// FUNC: _oggpack_writealign
void __cdecl oggpack_writealign(oggpack_buffer *b)
{
  if ( 8 - b->endbit < 8 )
    oggpack_write(b, 0, 8 - b->endbit);
}

// FUNC: _oggpack_writeclear
void __cdecl oggpack_writeclear(oggpack_buffer *b)
{
  _decoder_free(b->buffer);
  b->endbyte = 0;
  b->endbit = 0;
  b->buffer = 0;
  b->ptr = 0;
  b->storage = 0;
}

// FUNC: _oggpack_readinit
void __cdecl oggpack_readinit(oggpack_buffer *b, unsigned __int8 *buf, int bytes)
{
  b->endbyte = 0;
  b->endbit = 0;
  b->buffer = 0;
  b->ptr = 0;
  b->storage = 0;
  b->ptr = buf;
  b->buffer = buf;
  b->storage = bytes;
}

// FUNC: _oggpack_look
unsigned int __cdecl oggpack_look(oggpack_buffer *b, int bits)
{
  int storage; // esi
  int endbit; // edi
  int v4; // edx
  unsigned __int8 *ptr; // esi
  int v7; // eax

  storage = b->storage;
  endbit = b->endbit;
  v4 = endbit + bits;
  if ( b->endbyte + 4 >= storage && v4 + 8 * b->endbyte > 8 * storage )
    return -1;
  ptr = b->ptr;
  v7 = *ptr >> LOBYTE(b->endbit);
  if ( v4 > 8 )
  {
    v7 |= ptr[1] << (8 - endbit);
    if ( v4 > 16 )
    {
      v7 |= ptr[2] << (16 - endbit);
      if ( v4 > 24 )
      {
        v7 |= ptr[3] << (24 - endbit);
        if ( v4 > 32 )
        {
          if ( endbit )
            v7 |= ptr[4] << (32 - endbit);
        }
      }
    }
  }
  return mask[bits] & v7;
}

// FUNC: _oggpack_adv
void __cdecl oggpack_adv(oggpack_buffer *b, int bits)
{
  int v2; // esi
  int v3; // eax

  v2 = (b->endbit + bits) & 7;
  v3 = (b->endbit + bits) / 8;
  b->ptr += v3;
  b->endbyte += v3;
  b->endbit = v2;
}

// FUNC: _oggpack_read
int __cdecl oggpack_read(oggpack_buffer *b, int bits)
{
  int endbit; // edx
  int storage; // ecx
  int v5; // esi
  int v6; // edi
  unsigned __int8 *ptr; // eax
  int v8; // edi
  int endbyte; // ecx
  int result; // eax
  int bitsa; // [esp+14h] [ebp+8h]

  endbit = b->endbit;
  storage = b->storage;
  bitsa = mask[bits];
  v5 = endbit + bits;
  if ( b->endbyte + 4 < storage || (v6 = -1, v5 + 8 * b->endbyte <= 8 * storage) )
  {
    ptr = b->ptr;
    v8 = *ptr >> LOBYTE(b->endbit);
    if ( v5 > 8 )
    {
      v8 |= ptr[1] << (8 - endbit);
      if ( v5 > 16 )
      {
        v8 |= ptr[2] << (16 - endbit);
        if ( v5 > 24 )
        {
          v8 |= ptr[3] << (24 - endbit);
          if ( v5 > 32 )
          {
            if ( endbit )
              v8 |= ptr[4] << (32 - endbit);
          }
        }
      }
    }
    v6 = bitsa & v8;
  }
  endbyte = b->endbyte;
  b->ptr += v5 / 8;
  b->endbyte = endbyte + v5 / 8;
  result = v6;
  b->endbit = v5 & 7;
  return result;
}

// FUNC: _oggpack_bytes
int __cdecl oggpack_bytes(oggpack_buffer *b)
{
  return b->endbyte + (b->endbit + 7) / 8;
}
