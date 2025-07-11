
// FUNC: _crc32
int __cdecl crc32(unsigned int crc, const unsigned __int8 *buf, unsigned int len)
{
  const unsigned __int8 *v3; // ecx
  unsigned int v5; // esi
  unsigned int i; // eax
  char v7; // dl

  v3 = buf;
  if ( !buf )
    return 0;
  v5 = len;
  for ( i = ~crc; v5; --v5 )
  {
    v7 = *v3++;
    i = crc_table[(unsigned __int8)(i ^ v7)] ^ (i >> 8);
  }
  return ~i;
}

// FUNC: _adler32
int __cdecl adler32(unsigned int adler, const unsigned __int8 *buf, unsigned int len)
{
  const unsigned __int8 *v3; // edi
  unsigned int v5; // ebx
  unsigned int v6; // ecx
  unsigned int i; // esi
  int v8; // eax

  v3 = buf;
  if ( !buf )
    return 1;
  v5 = len;
  v6 = (unsigned __int16)adler;
  for ( i = HIWORD(adler); v5; i %= 0xFFF1u )
  {
    v8 = v5;
    if ( v5 >= 0x15B0 )
      v8 = 5552;
    for ( v5 -= v8; v8; --v8 )
    {
      v6 += *v3++;
      i += v6;
    }
    v6 %= 0xFFF1u;
  }
  return v6 | (i << 16);
}
