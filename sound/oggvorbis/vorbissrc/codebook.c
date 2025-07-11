
// FUNC: _vorbis_staticbook_unpack
int __cdecl vorbis_staticbook_unpack(oggpack_buffer *opb, static_codebook *s)
{
  int v2; // eax
  int v3; // eax
  int v4; // ebp
  int *v5; // eax
  int v6; // edi
  bool v7; // cc
  int v8; // eax
  int v9; // eax
  int i; // ecx
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int *v16; // eax
  int v17; // ebp
  bool v18; // zf

  memset(s, 0, sizeof(static_codebook));
  s->allocedp = 1;
  if ( oggpack_read(opb, 24) != 5653314 )
    goto _errout;
  s->dim = oggpack_read(opb, 16);
  v2 = oggpack_read(opb, 24);
  s->entries = v2;
  if ( v2 == -1 )
    goto _errout;
  v3 = oggpack_read(opb, 1);
  if ( v3 )
  {
    if ( v3 != 1 )
      return -1;
    v4 = oggpack_read(opb, 5) + 1;
    v5 = (int *)_decoder_malloc(4 * s->entries);
    v6 = 0;
    v7 = s->entries <= 0;
    s->lengthlist = v5;
    if ( !v7 )
    {
      do
      {
        v8 = _ilog(s->entries - v6);
        v9 = oggpack_read(opb, v8);
        if ( v9 == -1 )
          goto _errout;
        for ( i = 0; i < v9; ++v6 )
        {
          if ( v6 >= s->entries )
            break;
          s->lengthlist[v6] = v4;
          ++i;
        }
        ++v4;
      }
      while ( v6 < s->entries );
    }
  }
  else
  {
    s->lengthlist = (int *)_decoder_malloc(4 * s->entries);
    v11 = 0;
    if ( oggpack_read(opb, 1) )
    {
      if ( s->entries > 0 )
      {
        do
        {
          if ( oggpack_read(opb, 1) )
          {
            v12 = oggpack_read(opb, 5);
            if ( v12 == -1 )
              goto _errout;
            s->lengthlist[v11] = v12 + 1;
          }
          else
          {
            s->lengthlist[v11] = 0;
          }
          ++v11;
        }
        while ( v11 < s->entries );
      }
    }
    else if ( s->entries > 0 )
    {
      do
      {
        v13 = oggpack_read(opb, 5);
        if ( v13 == -1 )
          goto _errout;
        s->lengthlist[v11++] = v13 + 1;
      }
      while ( v11 < s->entries );
    }
  }
  v14 = oggpack_read(opb, 4);
  s->maptype = v14;
  if ( v14 )
  {
    if ( v14 <= 0 || v14 > 2 )
      goto _errout;
    s->q_min = oggpack_read(opb, 32);
    s->q_delta = oggpack_read(opb, 32);
    s->q_quant = oggpack_read(opb, 4) + 1;
    s->q_sequencep = oggpack_read(opb, 1);
    v15 = 0;
    if ( s->maptype == 1 )
    {
      v15 = _book_maptype1_quantvals(s);
    }
    else if ( s->maptype == 2 )
    {
      v15 = s->entries * s->dim;
    }
    v16 = (int *)_decoder_malloc(4 * v15);
    v17 = 0;
    v18 = v15 == 0;
    s->quantlist = v16;
    if ( v15 > 0 )
    {
      do
        s->quantlist[v17++] = oggpack_read(opb, s->q_quant);
      while ( v17 < v15 );
      v18 = v15 == 0;
    }
    if ( !v18 && s->quantlist[v15 - 1] == -1 )
    {
_errout:
      vorbis_staticbook_clear(s);
      return -1;
    }
  }
  return 0;
}

// FUNC: _vorbis_book_encode
int __cdecl vorbis_book_encode(codebook *book, int a, oggpack_buffer *b)
{
  oggpack_write(b, book->codelist[a], book->c->lengthlist[a]);
  return book->c->lengthlist[a];
}

// FUNC: _vorbis_book_decode
int __cdecl vorbis_book_decode(codebook *book, oggpack_buffer *b)
{
  int result; // eax

  result = decode_packed_entry_number(book, b);
  if ( result >= 0 )
    return book->dec_index[result];
  return result;
}

// FUNC: _vorbis_book_decodevs_add
int __cdecl vorbis_book_decodevs_add(codebook *book, float *a, oggpack_buffer *b, int n)
{
  codebook *v4; // ebx
  int v5; // edi
  int v6; // eax
  void *v7; // esp
  int v8; // eax
  void *v9; // esp
  _DWORD *v10; // esi
  int v11; // eax
  int v12; // edx
  bool v13; // cc
  int v14; // esi
  int *v15; // eax
  float **v16; // ecx
  unsigned int v17; // edi
  double v18; // st7
  float *v19; // eax
  float *v20; // ecx
  double v21; // st7
  _BYTE v23[12]; // [esp+0h] [ebp-1Ch] BYREF
  int step; // [esp+Ch] [ebp-10h]
  float **t; // [esp+10h] [ebp-Ch]
  int *entry; // [esp+14h] [ebp-8h]
  int o; // [esp+18h] [ebp-4h]
  int i; // [esp+30h] [ebp+14h]
  int ia; // [esp+30h] [ebp+14h]

  v4 = book;
  v5 = n / book->dim;
  v6 = 4 * v5 + 3;
  LOBYTE(v6) = v6 & 0xFC;
  step = v5;
  v7 = alloca(v6);
  v8 = 4 * v5 + 3;
  LOBYTE(v8) = (4 * v5 + 3) & 0xFC;
  entry = (int *)v23;
  v9 = alloca(v8);
  v10 = v23;
  t = (float **)v23;
  i = 0;
  if ( v5 <= 0 )
  {
LABEL_5:
    v12 = 0;
    v13 = book->dim <= 0;
    ia = 0;
    o = 0;
    if ( !v13 )
    {
      entry = (int *)a;
      do
      {
        v14 = 0;
        if ( v5 >= 4 )
        {
          v15 = entry;
          v16 = t + 2;
          v17 = ((unsigned int)(v5 - 4) >> 2) + 1;
          v14 = 4 * v17;
          do
          {
            v15 += 4;
            v18 = (*(v16 - 2))[v12] + *((float *)v15 - 4);
            v16 += 4;
            --v17;
            *((float *)v15 - 4) = v18;
            *((float *)v15 - 3) = (*(v16 - 5))[v12] + *((float *)v15 - 3);
            *((float *)v15 - 2) = (*(v16 - 4))[v12] + *((float *)v15 - 2);
            *((float *)v15 - 1) = (*(v16 - 3))[v12] + *((float *)v15 - 1);
          }
          while ( v17 );
          v4 = book;
          v5 = step;
        }
        if ( v14 < v5 )
        {
          v19 = &a[v14 + o];
          do
          {
            v20 = t[v14++];
            v21 = v20[v12] + *v19++;
            *(v19 - 1) = v21;
          }
          while ( v14 < v5 );
        }
        o += v5;
        entry += v5;
        ++v12;
        ++ia;
      }
      while ( ia < v4->dim );
    }
    return 0;
  }
  else
  {
    entry = (int *)((char *)entry - v23);
    while ( 1 )
    {
      v11 = decode_packed_entry_number(book, b);
      *(_DWORD *)((char *)v10 + (_DWORD)entry) = v11;
      if ( v11 == -1 )
        return -1;
      *v10++ = &book->valuelist[v11 * book->dim];
      if ( ++i >= v5 )
        goto LABEL_5;
    }
  }
}

// FUNC: _vorbis_book_decodev_add
int __cdecl vorbis_book_decodev_add(codebook *book, float *a, oggpack_buffer *b, int n)
{
  int v4; // esi
  int v5; // eax
  float *v6; // edx
  int i; // eax
  double v8; // st7
  double v9; // st7
  int v11; // eax
  float *v12; // ecx
  int v13; // eax
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st7
  double v25; // st7

  v4 = 0;
  if ( book->dim <= 8 )
  {
    if ( n > 0 )
    {
      while ( 1 )
      {
        v11 = decode_packed_entry_number(book, b);
        if ( v11 == -1 )
          return -1;
        v12 = &book->valuelist[v11 * book->dim];
        v13 = 0;
        switch ( book->dim )
        {
          case 1:
            goto $L2558;
          case 2:
            goto $L2557;
          case 3:
            goto $L2556;
          case 4:
            goto $L2555;
          case 5:
            goto $L2554;
          case 6:
            goto $L2553;
          case 7:
            goto $L2552;
          case 8:
            v13 = 1;
            a[v4] = *v12 + a[v4];
            ++v4;
$L2552:
            v14 = v12[v13++];
            v15 = v14 + a[v4++];
            a[v4 - 1] = v15;
$L2553:
            v16 = v12[v13++];
            v17 = v16 + a[v4++];
            a[v4 - 1] = v17;
$L2554:
            v18 = v12[v13++];
            v19 = v18 + a[v4++];
            a[v4 - 1] = v19;
$L2555:
            v20 = v12[v13++];
            v21 = v20 + a[v4++];
            a[v4 - 1] = v21;
$L2556:
            v22 = v12[v13++];
            v23 = v22 + a[v4++];
            a[v4 - 1] = v23;
$L2557:
            v24 = v12[v13++];
            v25 = v24 + a[v4++];
            a[v4 - 1] = v25;
$L2558:
            ++v4;
            a[v4 - 1] = v12[v13] + a[v4 - 1];
            break;
          default:
            break;
        }
        if ( v4 >= n )
          return 0;
      }
    }
    return 0;
  }
  if ( n <= 0 )
    return 0;
  while ( 1 )
  {
    v5 = decode_packed_entry_number(book, b);
    if ( v5 == -1 )
      break;
    v6 = &book->valuelist[v5 * book->dim];
    for ( i = 0; i < book->dim; a[v4 - 1] = v9 )
    {
      v8 = v6[i++];
      v9 = v8 + a[v4++];
    }
    if ( v4 >= n )
      return 0;
  }
  return -1;
}

// FUNC: _vorbis_book_decodev_set
int __cdecl vorbis_book_decodev_set(codebook *book, float *a, oggpack_buffer *b, int n)
{
  int v4; // edi
  int v5; // eax
  float *v6; // edx
  int i; // eax

  v4 = 0;
  if ( n <= 0 )
    return 0;
  while ( 1 )
  {
    v5 = decode_packed_entry_number(book, b);
    if ( v5 == -1 )
      break;
    v6 = &book->valuelist[v5 * book->dim];
    for ( i = 0; i < book->dim; ++v4 )
      a[v4] = v6[i++];
    if ( v4 >= n )
      return 0;
  }
  return -1;
}

// FUNC: _vorbis_book_decodevv_add
int __cdecl vorbis_book_decodevv_add(codebook *book, float **a, int offset, int ch, oggpack_buffer *b, int n)
{
  int v6; // esi
  int v7; // edi
  bool v8; // cc
  int v9; // eax
  float *v10; // ebx
  int i; // ecx
  float *v12; // eax
  int offseta; // [esp+1Ch] [ebp+Ch]

  v6 = 0;
  v7 = offset / ch;
  v8 = offset / ch < (offset + n) / ch;
  offseta = (offset + n) / ch;
  if ( !v8 )
    return 0;
  while ( 1 )
  {
    v9 = decode_packed_entry_number(book, b);
    if ( v9 == -1 )
      break;
    v10 = &book->valuelist[v9 * book->dim];
    for ( i = 0; i < book->dim; ++i )
    {
      v12 = a[v6++];
      v12[v7] = v10[i] + v12[v7];
      if ( v6 == ch )
      {
        v6 = 0;
        ++v7;
      }
    }
    if ( v7 >= offseta )
      return 0;
  }
  return -1;
}
