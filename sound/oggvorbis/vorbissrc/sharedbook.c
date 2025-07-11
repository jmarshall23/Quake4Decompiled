
// FUNC: __ilog
int __cdecl _ilog(unsigned int v)
{
  unsigned int v1; // ecx
  int result; // eax

  v1 = v;
  for ( result = 0; v1; v1 >>= 1 )
    ++result;
  return result;
}

// FUNC: __make_words
unsigned int *__cdecl _make_words(int *l, int n, int sparsecount)
{
  int v3; // esi
  int v4; // eax
  int *v5; // ebp
  unsigned int *v6; // edx
  int v7; // eax
  int v8; // edi
  unsigned int *v9; // ebx
  int v10; // ecx
  unsigned int v11; // esi
  int v12; // eax
  unsigned int v13; // edx
  int i; // eax
  int v15; // ebx
  int *v16; // edi
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  unsigned int v20; // ebp
  unsigned int *r; // [esp+10h] [ebp-88h]
  unsigned int marker[33]; // [esp+14h] [ebp-84h] BYREF

  v3 = sparsecount;
  v4 = sparsecount;
  if ( !sparsecount )
    v4 = n;
  v5 = l;
  v6 = (unsigned int *)_decoder_malloc(4 * v4);
  memset(marker, 0, sizeof(marker));
  v7 = n;
  v8 = 0;
  r = v6;
  if ( n > 0 )
  {
    v9 = v6;
    while ( 1 )
    {
      v10 = l[v8];
      if ( v10 <= 0 )
      {
        if ( !v3 )
          ++v9;
      }
      else
      {
        v11 = marker[v10];
        if ( v10 < 32 && v11 >> v10 )
        {
          _decoder_free(r);
          return 0;
        }
        *v9++ = v11;
        v12 = v10;
        while ( 1 )
        {
          v13 = marker[v12];
          if ( (v13 & 1) != 0 )
            break;
          marker[v12--] = v13 + 1;
          if ( v12 <= 0 )
            goto LABEL_16;
        }
        if ( v12 == 1 )
          ++marker[1];
        else
          marker[v12] = 2 * marker[v12 - 1];
LABEL_16:
        for ( i = v10 + 1; i < 33; ++i )
        {
          if ( marker[i] >> 1 != v11 )
            break;
          v11 = marker[i];
          marker[i] = 2 * marker[i - 1];
        }
      }
      v7 = n;
      if ( ++v8 >= n )
      {
        v6 = r;
        break;
      }
      v3 = sparsecount;
    }
  }
  v15 = 0;
  if ( v7 > 0 )
  {
    v16 = (int *)v6;
    do
    {
      v17 = v5[v15];
      v18 = 0;
      v19 = 0;
      if ( v17 > 0 )
      {
        do
        {
          v20 = (unsigned int)*v16 >> v19++;
          v18 = v20 & 1 | (2 * v18);
        }
        while ( v19 < v17 );
        v5 = l;
      }
      if ( !sparsecount || v17 )
        *v16++ = v18;
      ++v15;
    }
    while ( v15 < n );
    return r;
  }
  return v6;
}

// FUNC: __book_maptype1_quantvals
int __cdecl _book_maptype1_quantvals(const static_codebook *b)
{
  double v1; // st7
  int dim; // ebx
  int entries; // esi
  int result; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // esi
  const static_codebook *ba; // [esp+20h] [ebp+4h]

  v1 = floor(pow((double)b->entries, 1.0 / (double)b->dim));
  dim = b->dim;
  entries = b->entries;
  result = (int)v1;
  ba = (const static_codebook *)entries;
  while ( 1 )
  {
    while ( 1 )
    {
      v5 = 1;
      v6 = 1;
      if ( dim > 0 )
      {
        v7 = dim;
        do
        {
          v5 *= result;
          v6 *= result + 1;
          --v7;
        }
        while ( v7 );
        entries = (int)ba;
      }
      if ( v5 <= entries )
        break;
      --result;
    }
    if ( v6 > entries )
      break;
    ++result;
  }
  return result;
}

// FUNC: __book_unquantize
const static_codebook *__cdecl _book_unquantize(const static_codebook *b, float *n, int *sparsemap)
{
  int maptype; // eax
  int v5; // edi
  int q_min; // ecx
  long double x; // st7
  long double v9; // st7
  int q_delta; // ecx
  long double v11; // st7
  int v12; // edx
  int *v13; // ebx
  int v14; // eax
  int v15; // ecx
  long double v16; // st7
  int v17; // ebp
  int dim; // ecx
  int v19; // edi
  int i; // ebx
  long double v21; // st7
  int count; // [esp+1Ch] [ebp-14h]
  float counta; // [esp+1Ch] [ebp-14h]
  float delta; // [esp+20h] [ebp-10h]
  float mindel; // [esp+24h] [ebp-Ch]
  float last; // [esp+28h] [ebp-8h]
  int quantvals; // [esp+2Ch] [ebp-4h]
  const static_codebook *ba; // [esp+34h] [ebp+4h]

  maptype = b->maptype;
  v5 = 0;
  count = 0;
  if ( maptype != 1 && maptype != 2 )
    return 0;
  q_min = b->q_min;
  x = (double)(q_min & 0x1FFFFF);
  if ( q_min < 0 )
    x = -x;
  v9 = ldexp(x, ((q_min >> 21) & 0x3FFu) - 788);
  q_delta = b->q_delta;
  mindel = v9;
  v11 = (double)(q_delta & 0x1FFFFF);
  if ( q_delta < 0 )
    v11 = -v11;
  delta = ldexp(v11, ((q_delta >> 21) & 0x3FFu) - 788);
  ba = (const static_codebook *)_decoder_calloc((_DWORD)n * b->dim, 4u);
  if ( b->maptype == 1 )
  {
    v17 = 0;
    for ( quantvals = _book_maptype1_quantvals(b); v17 < b->entries; ++v17 )
    {
      if ( !sparsemap || b->lengthlist[v17] )
      {
        dim = b->dim;
        v19 = 0;
        last = 0.0;
        for ( i = 1; v19 < b->dim; ++v19 )
        {
          v21 = fabs((double)b->quantlist[v17 / i % quantvals]) * delta + last + mindel;
          if ( b->q_sequencep )
            last = v21;
          if ( sparsemap )
            *((float *)&ba->dim + v19 + dim * sparsemap[count]) = v21;
          else
            *((float *)&ba->dim + v19 + count * dim) = v21;
          dim = b->dim;
          i *= quantvals;
        }
        ++count;
      }
    }
    return ba;
  }
  if ( b->maptype != 2 )
    return ba;
  v12 = 0;
  if ( b->entries <= 0 )
    return ba;
  v13 = sparsemap;
  do
  {
    if ( !v13 || b->lengthlist[v12] )
    {
      v14 = b->dim;
      v15 = 0;
      for ( counta = 0.0; v15 < b->dim; ++v15 )
      {
        v16 = fabs((double)b->quantlist[v15 + v12 * v14]) * delta + counta + mindel;
        if ( b->q_sequencep )
          counta = v16;
        v13 = sparsemap;
        if ( sparsemap )
          *((float *)&ba->dim + v15 + v14 * sparsemap[v5]) = v16;
        else
          *((float *)&ba->dim + v15 + v5 * v14) = v16;
        v14 = b->dim;
      }
      ++v5;
    }
    ++v12;
  }
  while ( v12 < b->entries );
  return ba;
}

// FUNC: _vorbis_staticbook_clear
void __cdecl vorbis_staticbook_clear(static_codebook *b)
{
  encode_aux_nearestmatch *nearest_tree; // eax
  encode_aux_nearestmatch *v2; // edx
  encode_aux_threshmatch *thresh_tree; // eax
  encode_aux_threshmatch *v4; // edx

  if ( b->allocedp )
  {
    if ( b->quantlist )
      _decoder_free(b->quantlist);
    if ( b->lengthlist )
      _decoder_free(b->lengthlist);
    nearest_tree = b->nearest_tree;
    if ( nearest_tree )
    {
      _decoder_free(nearest_tree->ptr0);
      _decoder_free(b->nearest_tree->ptr1);
      _decoder_free(b->nearest_tree->p);
      _decoder_free(b->nearest_tree->q);
      v2 = b->nearest_tree;
      v2->ptr0 = 0;
      v2->ptr1 = 0;
      v2->p = 0;
      v2->q = 0;
      v2->aux = 0;
      v2->alloc = 0;
      _decoder_free(b->nearest_tree);
    }
    thresh_tree = b->thresh_tree;
    if ( thresh_tree )
    {
      _decoder_free(thresh_tree->quantthresh);
      _decoder_free(b->thresh_tree->quantmap);
      v4 = b->thresh_tree;
      v4->quantthresh = 0;
      v4->quantmap = 0;
      v4->quantvals = 0;
      v4->threshvals = 0;
      _decoder_free(b->thresh_tree);
    }
    memset(b, 0, sizeof(static_codebook));
  }
}

// FUNC: _vorbis_staticbook_destroy
void __cdecl vorbis_staticbook_destroy(static_codebook *b)
{
  if ( b->allocedp )
  {
    vorbis_staticbook_clear(b);
    _decoder_free(b);
  }
}

// FUNC: _vorbis_book_clear
void __cdecl vorbis_book_clear(codebook *b)
{
  if ( b->valuelist )
    _decoder_free(b->valuelist);
  if ( b->codelist )
    _decoder_free(b->codelist);
  if ( b->dec_index )
    _decoder_free(b->dec_index);
  if ( b->dec_codelengths )
    _decoder_free(b->dec_codelengths);
  if ( b->dec_firsttable )
    _decoder_free(b->dec_firsttable);
  memset(b, 0, sizeof(codebook));
}

// FUNC: _vorbis_book_init_encode
int __cdecl vorbis_book_init_encode(codebook *c, const static_codebook *s)
{
  memset(c, 0, sizeof(codebook));
  c->c = s;
  c->entries = s->entries;
  c->used_entries = s->entries;
  c->dim = s->dim;
  c->codelist = _make_words(s->lengthlist, s->entries, 0);
  c->valuelist = (float *)_book_unquantize(s, (float *)s->entries, 0);
  return 0;
}

// FUNC: _vorbis_book_init_decode
int __cdecl vorbis_book_init_decode(codebook *c, const static_codebook *s)
{
  const static_codebook *v3; // edi
  int entries; // eax
  int v5; // ebx
  int *lengthlist; // ecx
  int v7; // eax
  void *v8; // esp
  unsigned int *v9; // edx
  unsigned int **v10; // eax
  unsigned int v12; // ecx
  unsigned int v13; // eax
  unsigned int v14; // eax
  unsigned int v15; // eax
  int v16; // eax
  void *v17; // esp
  int v18; // eax
  int *v19; // eax
  int v20; // ecx
  int v21; // edx
  unsigned int v22; // ecx
  unsigned int *codelist; // edi
  bool v24; // zf
  float *v25; // eax
  int v26; // eax
  unsigned int i; // ecx
  char *v28; // eax
  int v29; // ecx
  int *v30; // eax
  bool v31; // cc
  char *v32; // eax
  int v33; // edx
  unsigned int used_entries; // ecx
  int j; // eax
  int v36; // eax
  int v37; // ebx
  int v38; // edi
  char *v39; // eax
  int v40; // ecx
  int v41; // ebx
  unsigned __int64 v42; // rax
  int v43; // edx
  int v44; // eax
  char *v45; // edi
  unsigned int v46; // edi
  unsigned int v47; // ecx
  int v48; // ebx
  unsigned int v49; // edx
  int v50; // ebx
  unsigned int v51; // edx
  int v52; // ebx
  int v53; // eax
  int v54; // eax
  unsigned int v55; // edi
  unsigned int v56; // eax
  unsigned int v57; // ecx
  unsigned int v58; // eax
  unsigned int v59; // [esp-14h] [ebp-34h]
  int v60[3]; // [esp+0h] [ebp-20h] BYREF
  unsigned int mask; // [esp+Ch] [ebp-14h]
  int tabn; // [esp+10h] [ebp-10h]
  unsigned int **codep; // [esp+14h] [ebp-Ch]
  unsigned int size; // [esp+18h] [ebp-8h]
  int hi; // [esp+1Ch] [ebp-4h]
  int lo; // [esp+28h] [ebp+8h]
  int loa; // [esp+28h] [ebp+8h]
  int lob; // [esp+28h] [ebp+8h]
  int n; // [esp+2Ch] [ebp+Ch]

  memset(c, 0, sizeof(codebook));
  v3 = s;
  entries = s->entries;
  v5 = 0;
  if ( entries > 0 )
  {
    lengthlist = s->lengthlist;
    do
    {
      if ( *lengthlist > 0 )
        ++v5;
      ++lengthlist;
      --entries;
    }
    while ( entries );
  }
  c->entries = s->entries;
  c->used_entries = v5;
  c->dim = s->dim;
  hi = (int)_make_words(s->lengthlist, s->entries, v5);
  size = 4 * v5;
  v7 = 4 * v5 + 3;
  LOBYTE(v7) = v7 & 0xFC;
  v8 = alloca(v7);
  v9 = (unsigned int *)hi;
  v10 = (unsigned int **)v60;
  codep = (unsigned int **)v60;
  if ( hi )
  {
    if ( v5 > 0 )
    {
      tabn = (int)v60 - hi;
      lo = v5;
      do
      {
        v12 = (*v9 << 16) | ((unsigned __int64)*v9 >> 16);
        v13 = (v12 << 8) ^ ((v12 << 8) ^ (v12 >> 8)) & 0xFF00FF;
        v14 = (16 * v13) ^ ((16 * v13) ^ (v13 >> 4)) & 0xF0F0F0F;
        v15 = (4 * v14) ^ ((4 * v14) ^ (v14 >> 2)) & 0x33333333;
        *v9 = (2 * v15) ^ ((2 * v15) ^ (v15 >> 1)) & 0x55555555;
        *(unsigned int *)((char *)v9 + tabn) = (unsigned int)v9;
        ++v9;
        --lo;
      }
      while ( lo );
      v3 = s;
      v10 = codep;
    }
    qsort(v10, v5, 4u, (int (__cdecl *)(const void *, const void *))sort32a);
    v16 = size + 3;
    LOBYTE(v16) = (size + 3) & 0xFC;
    v17 = alloca(v16);
    c->codelist = (unsigned int *)_decoder_malloc(size);
    v18 = 0;
    if ( v5 > 0 )
    {
      do
      {
        v60[((int)codep[v18] - hi) >> 2] = v18;
        ++v18;
      }
      while ( v18 < v5 );
      v19 = v60;
      v20 = hi - (_DWORD)v60;
      tabn = hi - (_DWORD)v60;
      codep = (unsigned int **)v5;
      while ( 1 )
      {
        v21 = *v19;
        v22 = *(int *)((char *)v19 + v20);
        codelist = c->codelist;
        ++v19;
        v24 = codep == (unsigned int **)1;
        codep = (unsigned int **)((char *)codep - 1);
        codelist[v21] = v22;
        if ( v24 )
          break;
        v20 = tabn;
      }
      v3 = s;
    }
    _decoder_free((void *)hi);
    v25 = (float *)_book_unquantize(v3, (float *)v5, v60);
    v59 = size;
    c->valuelist = v25;
    c->dec_index = (int *)_decoder_malloc(v59);
    v26 = 0;
    for ( i = 0; v26 < v3->entries; ++v26 )
    {
      if ( v3->lengthlist[v26] > 0 )
        c->dec_index[v60[i++]] = v26;
    }
    v28 = (char *)_decoder_malloc(i);
    v29 = 0;
    c->dec_codelengths = v28;
    for ( n = 0; v29 < v3->entries; ++v29 )
    {
      v30 = v3->lengthlist;
      v31 = v30[v29] <= 0;
      v32 = (char *)&v30[v29];
      if ( !v31 )
      {
        v33 = v60[n++];
        c->dec_codelengths[v33] = *v32;
      }
    }
    used_entries = c->used_entries;
    for ( j = 0; used_entries; used_entries >>= 1 )
      ++j;
    v36 = j - 4;
    c->dec_firsttablen = v36;
    if ( v36 < 5 )
      c->dec_firsttablen = 5;
    if ( c->dec_firsttablen > 8 )
      c->dec_firsttablen = 8;
    tabn = 1 << c->dec_firsttablen;
    v37 = tabn;
    v38 = 0;
    c->dec_firsttable = (unsigned int *)_decoder_calloc(tabn, 4u);
    c->dec_maxlength = 0;
    if ( n > 0 )
    {
      do
      {
        v39 = &c->dec_codelengths[v38];
        v40 = *v39;
        if ( c->dec_maxlength < v40 )
          c->dec_maxlength = v40;
        v41 = *v39;
        if ( v41 <= c->dec_firsttablen )
        {
          v42 = (unsigned __int64)c->codelist[v38] << 16;
          LODWORD(v42) = (((unsigned int)v42 | HIDWORD(v42)) << 8) ^ ((HIDWORD(v42) << 8) ^ (((unsigned int)v42 | HIDWORD(v42)) >> 8)) & 0xFF00FF;
          HIDWORD(v42) = (16 * v42) ^ ((16 * v42) ^ ((unsigned int)v42 >> 4)) & 0xF0F0F0F;
          LODWORD(v42) = (4 * HIDWORD(v42)) ^ ((4 * HIDWORD(v42)) ^ (HIDWORD(v42) >> 2)) & 0x33333333;
          v43 = (2 * v42) ^ ((2 * v42) ^ ((unsigned int)v42 >> 1)) & 0x55555555;
          v44 = 0;
          loa = 0;
          if ( 1 << (LOBYTE(c->dec_firsttablen) - v41) > 0 )
          {
            do
            {
              c->dec_firsttable[v43 | (v44 << c->dec_codelengths[v38])] = v38 + 1;
              v44 = loa + 1;
              loa = v44;
            }
            while ( v44 < 1 << (LOBYTE(c->dec_firsttablen) - c->dec_codelengths[v38]) );
          }
        }
        ++v38;
      }
      while ( v38 < n );
      v37 = tabn;
    }
    v45 = 0;
    lob = 0;
    mask = -2 << (31 - LOBYTE(c->dec_firsttablen));
    hi = 0;
    codep = 0;
    if ( v37 > 0 )
    {
      do
      {
        v46 = (_DWORD)v45 << (32 - LOBYTE(c->dec_firsttablen));
        v47 = (v46 << 16) | HIWORD(v46);
        v48 = 16 * ((v47 << 8) ^ ((v47 << 8) ^ (v47 >> 8)) & 0xFF00FF);
        v49 = v48 ^ (v48 ^ (((v47 << 8) ^ ((v47 << 8) ^ (v47 >> 8)) & 0xFF00FF) >> 4)) & 0xF0F0F0F;
        v50 = 2 * ((4 * v49) ^ ((4 * v49) ^ (v49 >> 2)) & 0x33333333);
        if ( !c->dec_firsttable[v50 ^ (v50 ^ (((4 * v49) ^ ((4 * v49) ^ (v49 >> 2)) & 0x33333333) >> 1)) & 0x55555555] )
        {
          v51 = lob;
          v52 = n;
          v53 = lob + 1;
          if ( lob + 1 < n )
          {
            v52 = n;
            size = (unsigned int)&c->codelist[lob + 1];
            do
            {
              if ( *(_DWORD *)size > v46 )
                break;
              ++lob;
              size += 4;
              ++v53;
            }
            while ( v53 < n );
            v51 = lob;
          }
          v54 = hi;
          if ( hi < v52 )
          {
            size = (unsigned int)&c->codelist[hi];
            do
            {
              if ( v46 < (mask & *(_DWORD *)size) )
                break;
              size += 4;
              ++v54;
            }
            while ( v54 < v52 );
            v51 = lob;
            hi = v54;
          }
          v55 = v52 - v54;
          if ( v51 > 0x7FFF )
            LOWORD(v51) = 0x7FFF;
          if ( v55 > 0x7FFF )
            v55 = 0x7FFF;
          v56 = (v47 << 8) ^ ((v47 << 8) ^ (v47 >> 8)) & 0xFF00FF;
          v57 = (16 * v56) ^ ((16 * v56) ^ (v56 >> 4)) & 0xF0F0F0F;
          v58 = (4 * v57) ^ ((4 * v57) ^ (v57 >> 2)) & 0x33333333;
          c->dec_firsttable[(2 * v58) ^ ((2 * v58) ^ (v58 >> 1)) & 0x55555555] = v55 | ((v51 | 0xFFFF0000) << 15);
        }
        v45 = (char *)codep + 1;
        codep = (unsigned int **)((char *)codep + 1);
      }
      while ( (int)codep < tabn );
    }
    return 0;
  }
  else
  {
    vorbis_book_clear(c);
    return -1;
  }
}
