
// FUNC: _res0_free_info
void __cdecl res0_free_info(void *i)
{
  if ( i )
  {
    memset(i, 0, 0x714u);
    _decoder_free(i);
  }
}

// FUNC: _res0_free_look
void __cdecl res0_free_look(void *i)
{
  int j; // edi
  int k; // edi

  if ( i )
  {
    for ( j = 0; j < *((_DWORD *)i + 1); ++j )
    {
      if ( *(_DWORD *)(*((_DWORD *)i + 5) + 4 * j) )
        _decoder_free(*(void **)(*((_DWORD *)i + 5) + 4 * j));
    }
    _decoder_free(*((void **)i + 5));
    for ( k = 0; k < *((_DWORD *)i + 6); ++k )
      _decoder_free(*(void **)(*((_DWORD *)i + 7) + 4 * k));
    _decoder_free(*((void **)i + 7));
    memset(i, 0, 0x2Cu);
    _decoder_free(i);
  }
}

// FUNC: _res0_pack
void __cdecl res0_pack(unsigned int *vr, oggpack_buffer *opb)
{
  int v2; // ebx
  signed int v3; // ebp
  unsigned int *v4; // ebx
  unsigned int v5; // ecx
  unsigned int v6; // eax
  int v7; // edx
  unsigned int v8; // eax
  int i; // ecx
  unsigned int *v10; // edi
  int acc; // [esp+10h] [ebp-4h]

  v2 = 0;
  acc = 0;
  oggpack_write(opb, *vr, 24);
  oggpack_write(opb, vr[1], 24);
  oggpack_write(opb, vr[2] - 1, 24);
  oggpack_write(opb, vr[3] - 1, 6);
  oggpack_write(opb, vr[4], 8);
  v3 = 0;
  if ( (int)vr[3] > 0 )
  {
    v4 = vr + 5;
    do
    {
      v5 = *v4;
      v6 = *v4;
      v7 = 0;
      if ( !*v4 )
        goto LABEL_7;
      do
      {
        ++v7;
        v6 >>= 1;
      }
      while ( v6 );
      if ( v7 > 3 )
      {
        oggpack_write(opb, v5, 3);
        oggpack_write(opb, 1u, 1);
        oggpack_write(opb, (int)*v4 >> 3, 5);
      }
      else
      {
LABEL_7:
        oggpack_write(opb, v5, 4);
      }
      v8 = *v4;
      for ( i = 0; v8; v8 >>= 1 )
        i += v8 & 1;
      acc += i;
      ++v3;
      ++v4;
    }
    while ( v3 < (int)vr[3] );
    v2 = acc;
  }
  if ( v2 > 0 )
  {
    v10 = vr + 69;
    do
    {
      oggpack_write(opb, *v10++, 8);
      --v2;
    }
    while ( v2 );
  }
}

// FUNC: _res0_unpack
_DWORD *__cdecl res0_unpack(vorbis_info *vi, oggpack_buffer *opb)
{
  int v2; // ebx
  _DWORD *v3; // esi
  int v4; // eax
  int v5; // ebp
  bool v6; // cc
  int v7; // ebx
  int v8; // eax
  unsigned int v9; // ecx
  int v10; // ebp
  _DWORD *v11; // ebx
  int books; // edx
  int v13; // eax
  int *i; // ecx
  int acc; // [esp+10h] [ebp-8h]
  codec_setup_info *ci; // [esp+14h] [ebp-4h]
  vorbis_info *via; // [esp+1Ch] [ebp+4h]

  v2 = 0;
  acc = 0;
  v3 = _decoder_calloc(1u, 0x714u);
  ci = (codec_setup_info *)vi->codec_setup;
  *v3 = oggpack_read(opb, 24);
  v3[1] = oggpack_read(opb, 24);
  v3[2] = oggpack_read(opb, 24) + 1;
  v3[3] = oggpack_read(opb, 6) + 1;
  v4 = oggpack_read(opb, 8);
  v5 = 0;
  v6 = v3[3] <= 0;
  v3[4] = v4;
  if ( !v6 )
  {
    via = (vorbis_info *)(v3 + 5);
    do
    {
      v7 = oggpack_read(opb, 3);
      if ( oggpack_read(opb, 1) )
        v7 |= 8 * oggpack_read(opb, 5);
      via->version = v7;
      v8 = 0;
      v9 = v7;
      if ( v7 )
      {
        do
        {
          v8 += v9 & 1;
          v9 >>= 1;
        }
        while ( v9 );
      }
      acc += v8;
      via = (vorbis_info *)((char *)via + 4);
      ++v5;
    }
    while ( v5 < v3[3] );
    v2 = acc;
  }
  if ( v2 > 0 )
  {
    v10 = acc;
    v11 = v3 + 69;
    do
    {
      *v11++ = oggpack_read(opb, 8);
      --v10;
    }
    while ( v10 );
    v2 = acc;
  }
  books = ci->books;
  if ( v3[4] < books )
  {
    v13 = 0;
    if ( v2 <= 0 )
      return v3;
    for ( i = v3 + 69; *i < books; ++i )
    {
      if ( ++v13 >= v2 )
        return v3;
    }
  }
  memset(v3, 0, 0x714u);
  _decoder_free(v3);
  return 0;
}

// FUNC: _res0_look
_DWORD *__cdecl res0_look(vorbis_dsp_state *vd, _DWORD *vr)
{
  _DWORD *v2; // ebx
  _DWORD *v3; // esi
  codec_setup_info *codec_setup; // ecx
  int *p_dim; // eax
  unsigned int v6; // edx
  int v7; // edi
  void *v8; // eax
  bool v9; // cc
  unsigned int analysisp; // eax
  signed int v11; // ebp
  void *v12; // eax
  signed int v13; // ecx
  _DWORD *v14; // edx
  int v15; // eax
  void *v16; // eax
  int v17; // ebp
  int v18; // edi
  int i; // ecx
  int v20; // ebx
  int acc; // [esp+18h] [ebp-10h]
  int maxstage; // [esp+1Ch] [ebp-Ch]
  int dim; // [esp+20h] [ebp-8h]
  codec_setup_info *ci; // [esp+24h] [ebp-4h]
  vorbis_dsp_state *vda; // [esp+2Ch] [ebp+4h]
  float vrb; // [esp+30h] [ebp+8h]
  int vra; // [esp+30h] [ebp+8h]

  v2 = vr;
  v3 = _decoder_calloc(1u, 0x2Cu);
  codec_setup = (codec_setup_info *)vd->vi->codec_setup;
  *v3 = vr;
  v3[1] = vr[3];
  v3[3] = codec_setup->fullbooks;
  p_dim = &codec_setup->fullbooks[vr[4]].dim;
  v6 = v3[1];
  ci = codec_setup;
  v3[4] = p_dim;
  v7 = 0;
  acc = 0;
  maxstage = 0;
  dim = *p_dim;
  v8 = _decoder_calloc(v6, 4u);
  v9 = v3[1] <= 0;
  v3[5] = v8;
  if ( !v9 )
  {
    vda = (vorbis_dsp_state *)(vr + 5);
    do
    {
      analysisp = vda->analysisp;
      v11 = 0;
      if ( vda->analysisp )
      {
        do
        {
          ++v11;
          analysisp >>= 1;
        }
        while ( analysisp );
        if ( v11 )
        {
          if ( v11 > maxstage )
            maxstage = v11;
          v12 = _decoder_calloc(v11, 4u);
          v13 = 0;
          *(_DWORD *)(v3[5] + 4 * v7) = v12;
          if ( v11 > 0 )
          {
            v14 = &v2[acc + 69];
            do
            {
              if ( ((1 << v13) & vda->analysisp) != 0 )
              {
                ++acc;
                *(_DWORD *)(*(_DWORD *)(v3[5] + 4 * v7) + 4 * v13) = &ci->fullbooks[*v14++];
              }
              ++v13;
            }
            while ( v13 < v11 );
            v2 = vr;
          }
        }
      }
      vda = (vorbis_dsp_state *)((char *)vda + 4);
      ++v7;
    }
    while ( v7 < v3[1] );
  }
  vrb = floor(pow((double)(int)v3[1], (double)dim) + 0.5);
  v15 = (int)vrb;
  v3[6] = v15;
  v3[2] = maxstage;
  v16 = _decoder_malloc(4 * v15);
  v17 = 0;
  v9 = v3[6] <= 0;
  v3[7] = v16;
  if ( !v9 )
  {
    do
    {
      vra = v17;
      v18 = v3[6] / v3[1];
      *(_DWORD *)(v3[7] + 4 * v17) = _decoder_malloc(4 * dim);
      for ( i = 0; i < dim; *(_DWORD *)(*(_DWORD *)(v3[7] + 4 * v17) + 4 * i - 4) = v20 )
      {
        ++i;
        v20 = vra / v18;
        vra %= v18;
        v18 /= (int)v3[1];
      }
      ++v17;
    }
    while ( v17 < v3[6] );
  }
  return v3;
}

// FUNC: _res0_inverse
int __cdecl res0_inverse(vorbis_block *vb, void *vl, float **in, int *nonzero, int ch)
{
  int v5; // esi
  int v6; // ecx
  float **v7; // eax

  v5 = ch;
  v6 = 0;
  if ( ch <= 0 )
    return 0;
  v7 = in;
  do
  {
    if ( *(float **)((char *)v7 + (char *)nonzero - (char *)in) )
      in[v6++] = *v7;
    ++v7;
    --v5;
  }
  while ( v5 );
  if ( v6 )
    return 01inverse(vb, vl, in, v6, vorbis_book_decodevs_add);
  else
    return 0;
}

// FUNC: _res1_forward
int __cdecl res1_forward(
        vorbis_block *vb,
        vorbis_info_residue0 **vl,
        float **in,
        float **out,
        int *nonzero,
        vorbis_block *ch,
        int **partword)
{
  int v7; // ebx
  int v8; // ebp
  float **v9; // edi
  float **v10; // esi
  int v11; // edx
  float **v12; // ecx
  _DWORD *v13; // edx
  int v14; // eax
  float *v15; // edi
  double v16; // st7
  float *v17; // edi
  double v18; // st7
  float **v19; // edx
  int v20; // ecx
  float *v21; // edi
  double v22; // st7
  float *v23; // edi
  double v24; // st7
  int used; // [esp+10h] [ebp-10h]
  int v27; // [esp+14h] [ebp-Ch]
  int v28; // [esp+18h] [ebp-8h]
  int ret; // [esp+1Ch] [ebp-4h]
  vorbis_block *vba; // [esp+24h] [ebp+4h]

  v7 = 0;
  v8 = vb->pcmend / 2;
  used = 0;
  if ( (int)ch <= 0 )
    return 0;
  v9 = out;
  v10 = in;
  v28 = (char *)nonzero - (char *)out;
  v11 = (char *)out - (char *)in;
  v12 = in;
  v27 = (int)ch;
  while ( 1 )
  {
    v13 = (float **)((char *)v12 + v11);
    if ( *(_DWORD *)((char *)v13 + v28) )
    {
      if ( v9 )
      {
        v14 = 0;
        if ( v8 >= 4 )
        {
          do
          {
            *(float *)(*v13 + 4 * v14) = (*v12)[v14] + *(float *)(*v13 + 4 * v14);
            *(float *)(*v13 + 4 * v14 + 4) = (*v12)[v14 + 1] + *(float *)(*v13 + 4 * v14 + 4);
            *(float *)(*v13 + 4 * v14 + 8) = (*v12)[v14 + 2] + *(float *)(*v13 + 4 * v14 + 8);
            v15 = (float *)(*v13 + 4 * v14 + 12);
            v16 = (*v12)[v14 + 3];
            v14 += 4;
            *v15 = v16 + *v15;
          }
          while ( v14 < v8 - 3 );
          v10 = in;
          v9 = out;
        }
        if ( v14 < v8 )
        {
          do
          {
            v17 = (float *)(*v13 + 4 * v14);
            v18 = (*v12)[v14++] + *v17;
            *v17 = v18;
          }
          while ( v14 < v8 );
          v9 = out;
        }
      }
      v10[used] = *v12;
      v7 = ++used;
    }
    ++v12;
    if ( !--v27 )
      break;
    v11 = (char *)out - (char *)in;
  }
  if ( !v7 )
    return 0;
  ret = 01forward(
          vl,
          vb,
          v10,
          v7,
          partword,
          (int (__cdecl *)(oggpack_buffer *, float *, int, codebook *, int *))encodepart);
  if ( v9 )
  {
    v19 = v9;
    vba = ch;
    do
    {
      if ( *(float **)((char *)v19 + v28) )
      {
        v20 = 0;
        if ( v8 >= 4 )
        {
          do
          {
            (*v19)[v20] = (*v19)[v20] - (*v10)[v20];
            (*v19)[v20 + 1] = (*v19)[v20 + 1] - (*v10)[v20 + 1];
            (*v19)[v20 + 2] = (*v19)[v20 + 2] - (*v10)[v20 + 2];
            v21 = &(*v19)[v20 + 3];
            v22 = *v21 - (*v10)[v20 + 3];
            v20 += 4;
            *v21 = v22;
          }
          while ( v20 < v8 - 3 );
        }
        for ( ; v20 < v8; *v23 = v24 )
        {
          v23 = &(*v19)[v20];
          v24 = *v23 - (*v10)[v20++];
        }
        ++v10;
      }
      ++v19;
      vba = (vorbis_block *)((char *)vba - 1);
    }
    while ( vba );
  }
  return ret;
}

// FUNC: _res1_class
int **__cdecl res1_class(vorbis_block *vb, vorbis_info_residue0 **vl, float **in, int *nonzero, int ch)
{
  int v5; // esi
  int v6; // ecx
  float **v7; // eax

  v5 = ch;
  v6 = 0;
  if ( ch <= 0 )
    return 0;
  v7 = in;
  do
  {
    if ( *(float **)((char *)v7 + (char *)nonzero - (char *)in) )
      in[v6++] = *v7;
    ++v7;
    --v5;
  }
  while ( v5 );
  if ( v6 )
    return 01class(vb, vl, in, v6);
  else
    return 0;
}

// FUNC: _res1_inverse
int __cdecl res1_inverse(vorbis_block *vb, void *vl, float **in, int *nonzero, int ch)
{
  int v5; // esi
  int v6; // ecx
  float **v7; // eax

  v5 = ch;
  v6 = 0;
  if ( ch <= 0 )
    return 0;
  v7 = in;
  do
  {
    if ( *(float **)((char *)v7 + (char *)nonzero - (char *)in) )
      in[v6++] = *v7;
    ++v7;
    --v5;
  }
  while ( v5 );
  if ( v6 )
    return 01inverse(vb, vl, in, v6, vorbis_book_decodev_add);
  else
    return 0;
}

// FUNC: _res2_class
int **__cdecl res2_class(vorbis_block *vb, vorbis_info_residue0 **vl, float **in, int *nonzero, int ch)
{
  int v5; // edx
  int v6; // eax

  v5 = 0;
  v6 = 0;
  if ( ch <= 0 )
    return 0;
  do
  {
    if ( nonzero[v6] )
      ++v5;
    ++v6;
  }
  while ( v6 < ch );
  if ( v5 )
    return 2class(vb, vl, in, ch);
  else
    return 0;
}

// FUNC: _res2_forward
int __cdecl res2_forward(
        vorbis_block *vb,
        vorbis_info_residue0 **vl,
        float **in,
        float **out,
        int *nonzero,
        int ch,
        int **partword)
{
  int v8; // ebp
  int v9; // ebx
  float *v10; // edi
  int *v11; // edx
  int v12; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // eax
  float *v16; // ecx
  unsigned int v17; // edx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  float *v21; // eax
  bool v22; // cc
  int v23; // edx
  float **v24; // ebx
  float *v25; // ecx
  float *v26; // ecx
  float *v27; // eax
  int v28; // ebx
  float *v29; // ebx
  float *v30; // ecx
  unsigned int v31; // eax
  double v32; // st7
  int v33; // edx
  double v34; // st7
  int v35; // edx
  double v36; // st7
  int v37; // edx
  double v38; // st7
  int v39; // ecx
  float *v40; // ebx
  int v41; // eax
  float *v42; // edx
  double v43; // st7
  int i; // [esp+10h] [ebp-1Ch]
  int ia; // [esp+10h] [ebp-1Ch]
  float *pcm; // [esp+14h] [ebp-18h]
  float *pcma; // [esp+14h] [ebp-18h]
  float *sofar; // [esp+18h] [ebp-14h]
  float *sofara; // [esp+18h] [ebp-14h]
  float **v51; // [esp+1Ch] [ebp-10h]
  int ret; // [esp+20h] [ebp-Ch]
  int reta; // [esp+20h] [ebp-Ch]
  float *work; // [esp+24h] [ebp-8h] BYREF
  int n; // [esp+28h] [ebp-4h]
  int v56; // [esp+44h] [ebp+18h]
  int v57; // [esp+44h] [ebp+18h]

  v8 = vb->pcmend / 2;
  v9 = 0;
  n = v8;
  pcm = 0;
  v10 = (float *)_vorbis_block_alloc(vb, 4 * ch * v8);
  work = v10;
  i = 0;
  if ( ch <= 0 )
    return 0;
  v11 = nonzero;
  v12 = (char *)in - (char *)nonzero;
  sofar = (float *)nonzero;
  while ( 1 )
  {
    v13 = *(int *)((char *)v11 + v12);
    ret = v13;
    if ( *v11 )
      pcm = (float *)((char *)pcm + 1);
    v14 = 0;
    v15 = v9;
    if ( v8 >= 4 )
    {
      v16 = (float *)(v13 + 8);
      v17 = ((unsigned int)(v8 - 4) >> 2) + 1;
      v56 = 4 * v17;
      do
      {
        v10[v15] = *(v16 - 2);
        v18 = ch + v15;
        v10[v18] = *(v16 - 1);
        v19 = ch + v18;
        v10[v19] = *v16;
        v20 = ch + v19;
        v10[v20] = v16[1];
        v15 = ch + v20;
        v16 += 4;
        --v17;
      }
      while ( v17 );
      v14 = v56;
    }
    if ( v14 < v8 )
    {
      v21 = &v10[v15];
      do
      {
        *v21 = *(float *)(ret + 4 * v14++);
        v21 += ch;
      }
      while ( v14 < v8 );
    }
    v9 = i + 1;
    v11 = (int *)(sofar + 1);
    v22 = ++i < ch;
    ++sofar;
    if ( !v22 )
      break;
    v12 = (char *)in - (char *)nonzero;
  }
  if ( !pcm )
    return 0;
  reta = 01forward(
           vl,
           vb,
           &work,
           1,
           partword,
           (int (__cdecl *)(oggpack_buffer *, float *, int, codebook *, int *))encodepart);
  if ( out )
  {
    v23 = 0;
    v24 = out;
    v25 = (float *)((char *)in - (char *)out);
    ia = 0;
    v51 = out;
    for ( work = (float *)((char *)in - (char *)out); ; v25 = work )
    {
      v26 = *(float **)((char *)v24 + (_DWORD)v25);
      v27 = *v24;
      v28 = 0;
      pcma = v26;
      sofara = v27;
      v57 = 0;
      if ( v8 >= 4 )
      {
        v29 = v26 + 3;
        v30 = v27 + 1;
        v31 = ((unsigned int)(v8 - 4) >> 2) + 1;
        v57 = 4 * v31;
        do
        {
          v30 += 4;
          v32 = *(v29 - 3) - v10[v23];
          v33 = ch + v23;
          v29 += 4;
          *(v30 - 5) = v32 + *(v30 - 5);
          v34 = *(float *)((char *)v30 + (char *)pcma - (char *)sofara - 16) - v10[v33];
          v35 = ch + v33;
          *(v30 - 4) = v34 + *(v30 - 4);
          v36 = *(v29 - 5) - v10[v35];
          v37 = ch + v35;
          *(v30 - 3) = v36 + *(v30 - 3);
          v38 = *(v29 - 4) - v10[v37];
          v23 = ch + v37;
          --v31;
          *(v30 - 2) = v38 + *(v30 - 2);
        }
        while ( v31 );
        v27 = sofara;
        v28 = v57;
        v8 = n;
        v26 = pcma;
      }
      if ( v28 < v8 )
      {
        v39 = (char *)v26 - (char *)v27;
        v40 = &v27[v28];
        v41 = v8 - v57;
        v42 = &v10[v23];
        do
        {
          v43 = *(float *)((char *)v40 + v39) - *v42;
          v42 += ch;
          ++v40;
          --v41;
          *(v40 - 1) = v43 + *(v40 - 1);
        }
        while ( v41 );
      }
      v23 = ia + 1;
      v24 = v51 + 1;
      v22 = ++ia < ch;
      ++v51;
      if ( !v22 )
        break;
    }
  }
  return reta;
}

// FUNC: _res2_inverse
int __cdecl res2_inverse(vorbis_block *vb, _DWORD **vl, float **in, int *nonzero, int ch)
{
  _DWORD **v5; // esi
  _DWORD *v6; // ebx
  int v7; // ebp
  int v8; // edi
  int j; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // esi
  int v14; // eax
  codebook *v15; // eax
  int i; // [esp+10h] [ebp-18h]
  int s; // [esp+14h] [ebp-14h]
  char *v19; // [esp+18h] [ebp-10h]
  int partvals; // [esp+1Ch] [ebp-Ch]
  int partitions_per_word; // [esp+20h] [ebp-8h]
  char *partword; // [esp+24h] [ebp-4h]

  v5 = vl;
  v6 = *vl;
  v7 = (*vl)[2];
  partitions_per_word = *vl[4];
  v8 = ((*vl)[1] - **vl) / v7;
  partvals = v8;
  partword = _vorbis_block_alloc(vb, 4 * ((v8 + partitions_per_word - 1) / partitions_per_word));
  for ( j = 0; j < ch; ++j )
  {
    if ( nonzero[j] )
      break;
  }
  if ( j != ch )
  {
    s = 0;
    if ( (int)vl[2] > 0 )
    {
      while ( 1 )
      {
        i = 0;
        if ( v8 > 0 )
          break;
LABEL_21:
        if ( ++s >= (int)v5[2] )
          return 0;
      }
      v19 = partword;
      while ( 1 )
      {
        if ( !s )
        {
          v10 = vorbis_book_decode((codebook *)v5[4], &vb->opb);
          if ( v10 == -1 )
            break;
          v11 = v5[7][v10];
          *(_DWORD *)v19 = v11;
          if ( !v11 )
            break;
        }
        v12 = 0;
        if ( partitions_per_word > 0 )
        {
          v13 = v7 * i;
          do
          {
            if ( i >= partvals )
              break;
            v14 = *(_DWORD *)(*(_DWORD *)v19 + 4 * v12);
            if ( ((1 << s) & v6[v14 + 5]) != 0 )
            {
              v15 = *(codebook **)(vl[5][v14] + 4 * s);
              if ( v15 )
              {
                if ( vorbis_book_decodevv_add(v15, in, v13 + *v6, ch, &vb->opb, v7) == -1 )
                  return 0;
              }
            }
            ++i;
            ++v12;
            v13 += v7;
          }
          while ( v12 < partitions_per_word );
          v5 = vl;
        }
        v19 += 4;
        if ( i >= partvals )
        {
          v8 = partvals;
          goto LABEL_21;
        }
      }
    }
  }
  return 0;
}
