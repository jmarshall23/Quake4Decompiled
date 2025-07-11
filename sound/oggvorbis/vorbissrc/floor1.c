
// FUNC: floor1_free_info
void __cdecl floor1_free_info(void *i)
{
  if ( i )
  {
    memset(i, 0, 0x460u);
    _decoder_free(i);
  }
}

// FUNC: floor1_free_look
void __cdecl floor1_free_look(void *i)
{
  if ( i )
  {
    memset(i, 0, 0x520u);
    _decoder_free(i);
  }
}

// FUNC: floor1_pack
void __cdecl floor1_pack(_DWORD *i, oggpack_buffer *opb)
{
  int *v2; // ebp
  int v3; // esi
  int v4; // edi
  unsigned int *v5; // esi
  int v6; // eax
  unsigned int *v7; // esi
  int v8; // edi
  _DWORD *v9; // ebp
  unsigned int v10; // eax
  unsigned int v11; // ecx
  int v12; // ecx
  unsigned int v13; // eax
  int v14; // eax
  int v15; // esi
  unsigned int *v16; // edi
  int k; // [esp+10h] [ebp-10h]
  char *ka; // [esp+10h] [ebp-10h]
  int count; // [esp+14h] [ebp-Ch]
  int j; // [esp+18h] [ebp-8h]
  int ja; // [esp+18h] [ebp-8h]
  int maxposit; // [esp+1Ch] [ebp-4h]
  int maxposita; // [esp+1Ch] [ebp-4h]
  _DWORD *ia; // [esp+24h] [ebp+4h]

  v2 = i;
  v3 = i[210];
  v4 = 0;
  count = 0;
  maxposit = v3;
  k = -1;
  oggpack_write(opb, *i, 5);
  if ( (int)*i > 0 )
  {
    v5 = i + 1;
    do
    {
      oggpack_write(opb, *v5, 4);
      if ( k < (int)*v5 )
        k = *v5;
      ++v4;
      ++v5;
    }
    while ( v4 < *i );
    v3 = maxposit;
  }
  v6 = k + 1;
  if ( k + 1 > 0 )
  {
    ka = (char *)(i + 80);
    v7 = i + 48;
    j = v6;
    do
    {
      oggpack_write(opb, *(v7 - 16) - 1, 3);
      oggpack_write(opb, *v7, 2);
      if ( *v7 )
        oggpack_write(opb, v7[16], 8);
      v8 = 0;
      if ( 1 << *v7 > 0 )
      {
        v9 = ka;
        do
        {
          oggpack_write(opb, *v9 + 1, 8);
          ++v8;
          ++v9;
        }
        while ( v8 < 1 << *v7 );
        v2 = i;
      }
      ka += 32;
      ++v7;
      --j;
    }
    while ( j );
    v3 = maxposit;
  }
  oggpack_write(opb, v2[208] - 1, 2);
  v10 = 0;
  if ( v3 )
  {
    v11 = v3 - 1;
    if ( v3 != 1 )
    {
      do
      {
        ++v10;
        v11 >>= 1;
      }
      while ( v11 );
    }
  }
  oggpack_write(opb, v10, 4);
  v12 = 0;
  maxposita = 0;
  if ( v3 )
  {
    v13 = v3 - 1;
    if ( v3 != 1 )
    {
      do
      {
        ++v12;
        v13 >>= 1;
      }
      while ( v13 );
      maxposita = v12;
    }
  }
  v14 = 0;
  ja = 0;
  if ( *v2 > 0 )
  {
    ia = v2 + 1;
    do
    {
      count += v2[*ia + 32];
      if ( v14 < count )
      {
        v15 = count - v14;
        v16 = (unsigned int *)&v2[v14 + 211];
        do
        {
          oggpack_write(opb, *v16++, maxposita);
          --v15;
        }
        while ( v15 );
        v14 = count;
      }
      ++ia;
      ++ja;
    }
    while ( ja < *v2 );
  }
}

// FUNC: render_line
void __usercall render_line(int x0@<eax>, int y1@<ecx>, int x1, int y0, float *d)
{
  int v6; // edi
  int v7; // ecx
  unsigned int v8; // ebp
  int v9; // esi
  int v10; // eax
  unsigned int v11; // ebp
  int v12; // ebx
  float *v13; // eax
  int v14; // ecx
  float *v15; // eax
  int v16; // ecx
  int v17; // edi
  int v18; // ecx
  int v19; // edi
  int v20; // ecx
  int v21; // edi
  bool v22; // zf
  float *v23; // edi
  double v24; // st7
  int sy; // [esp+10h] [ebp-8h]
  int base; // [esp+14h] [ebp-4h]
  int y0a; // [esp+20h] [ebp+8h]

  v6 = y0;
  v7 = y1 - y0;
  v8 = abs32(v7);
  v9 = x1 - x0;
  v10 = v7 / (x1 - x0);
  base = v10;
  if ( v7 >= 0 )
    sy = v10 + 1;
  else
    sy = v10 - 1;
  v11 = v8 - abs32(v9 * v10);
  v12 = x0 + 1;
  v13 = d;
  v14 = 0;
  d[v12 - 1] = FLOOR1_fromdB_LOOKUP[y0] * d[v12 - 1];
  if ( x1 - v12 >= 4 )
  {
    v15 = &d[v12 + 2];
    y0a = ((unsigned int)(x1 - v12 - 4) >> 2) + 1;
    v12 += 4 * y0a;
    do
    {
      v16 = v11 + v14;
      if ( v16 < v9 )
      {
        v17 = base + v6;
      }
      else
      {
        v16 -= v9;
        v17 = sy + v6;
      }
      v18 = v11 + v16;
      *(v15 - 2) = FLOOR1_fromdB_LOOKUP[v17] * *(v15 - 2);
      if ( v18 < v9 )
      {
        v19 = base + v17;
      }
      else
      {
        v18 -= v9;
        v19 = sy + v17;
      }
      v20 = v11 + v18;
      *(v15 - 1) = FLOOR1_fromdB_LOOKUP[v19] * *(v15 - 1);
      if ( v20 < v9 )
      {
        v21 = base + v19;
      }
      else
      {
        v20 -= v9;
        v21 = sy + v19;
      }
      v14 = v11 + v20;
      *v15 = FLOOR1_fromdB_LOOKUP[v21] * *v15;
      if ( v14 < v9 )
      {
        v6 = base + v21;
      }
      else
      {
        v14 -= v9;
        v6 = sy + v21;
      }
      v15 += 4;
      v22 = y0a-- == 1;
      *(v15 - 3) = FLOOR1_fromdB_LOOKUP[v6] * *(v15 - 3);
    }
    while ( !v22 );
    v13 = d;
  }
  if ( v12 < x1 )
  {
    v23 = &FLOOR1_fromdB_LOOKUP[v6];
    do
    {
      v14 += v11;
      if ( v14 < v9 )
      {
        v23 += base;
      }
      else
      {
        v14 -= v9;
        v23 += sy;
      }
      v24 = v13[v12++];
      v13[v12 - 1] = v24 * *v23;
    }
    while ( v12 < x1 );
  }
}

// FUNC: render_line0
void __usercall render_line0(int y0@<ecx>, int y1@<eax>, int x0, int x1, int *d)
{
  int v6; // ebx
  int v7; // edi
  unsigned int v8; // esi
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  unsigned int v12; // esi
  int v13; // eax
  int v14; // edx
  int base; // [esp+14h] [ebp-4h]
  int x0a; // [esp+1Ch] [ebp+4h]

  v6 = y0;
  v7 = y1 - y0;
  v8 = abs32(y1 - y0);
  v9 = x1 - x0;
  v10 = v7 / (x1 - x0);
  base = v10;
  v11 = v10 - 1;
  if ( v7 >= 0 )
    v11 = v10 + 1;
  x0a = v11;
  v12 = v8 - abs32(v9 * v10);
  v13 = x0 + 1;
  d[x0] = v6;
  if ( x0 + 1 < x1 )
  {
    v14 = 0;
    do
    {
      v14 += v12;
      if ( v14 < v9 )
      {
        v6 += base;
      }
      else
      {
        v14 -= v9;
        v6 += x0a;
      }
      d[v13++] = v6;
    }
    while ( v13 < x1 );
  }
}

// FUNC: fit_line
void __cdecl fit_line(lsfit_acc *a, int fits, int *y0, int *y1)
{
  int v4; // eax
  int v5; // ebp
  int v6; // edx
  int v7; // esi
  int v8; // edi
  int v9; // ebx
  int v10; // ecx
  int *p_ya; // eax
  int v12; // ebp
  double v13; // st7
  double v14; // st6
  double v15; // st5
  double v16; // st4
  long double v17; // st3
  int x; // [esp+18h] [ebp-28h]
  int y; // [esp+1Ch] [ebp-24h]
  int fx2; // [esp+20h] [ebp-20h]
  long double fx2a; // [esp+20h] [ebp-20h]
  int xy; // [esp+28h] [ebp-18h]
  long double xya; // [esp+28h] [ebp-18h]
  int b; // [esp+30h] [ebp-10h]
  long double ba; // [esp+30h] [ebp-10h]
  int x1; // [esp+38h] [ebp-8h]
  int x0; // [esp+3Ch] [ebp-4h]

  x0 = a->x0;
  v4 = a[fits - 1].x1;
  v5 = fits;
  v6 = 0;
  v7 = 0;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  x = 0;
  y = 0;
  fx2 = 0;
  xy = 0;
  b = 0;
  x1 = v4;
  if ( fits > 0 )
  {
    p_ya = &a->ya;
    do
    {
      v6 += *(p_ya - 1);
      v7 += *p_ya;
      v8 += p_ya[1];
      v9 += p_ya[3];
      v10 += p_ya[4];
      p_ya += 8;
      --v5;
    }
    while ( v5 );
    v4 = a[fits - 1].x1;
    b = v10;
    xy = v9;
    fx2 = v8;
    y = v7;
    x = v6;
  }
  if ( *y0 >= 0 )
  {
    v7 += *y0;
    v8 += x0 * x0;
    v6 += x0;
    v4 = a[fits - 1].x1;
    v9 += x0 * *y0;
    ++v10;
    x = v6;
    y = v7;
    fx2 = v8;
    xy = v9;
    b = v10;
  }
  v12 = *y1;
  if ( *y1 >= 0 )
  {
    x = v4 + v6;
    ++v10;
    y = v12 + v7;
    fx2 = v4 * v4 + v8;
    xy = v4 * v12 + v9;
    b = v10;
  }
  if ( v10 )
  {
    v13 = (double)x;
    v14 = (double)y;
    fx2a = (double)fx2;
    v15 = (double)xy;
    v16 = (double)b;
    v17 = 1.0 / (fx2a * v16 - v13 * v13);
    xya = (fx2a * v14 - v15 * v13) * v17;
    ba = (v16 * v15 - v14 * v13) * v17;
    *y0 = (int)floor((double)x0 * ba + xya + 0.5);
    *y1 = (int)floor((double)x1 * ba + xya + 0.5);
    if ( *y0 > 1023 )
      *y0 = 1023;
    if ( *y1 > 1023 )
      *y1 = 1023;
    if ( *y0 < 0 )
      *y0 = 0;
    if ( *y1 < 0 )
      *y1 = 0;
  }
  else
  {
    *y0 = 0;
    *y1 = 0;
  }
}

// FUNC: _floor1_fit
int *__cdecl floor1_fit(vorbis_block *vb, vorbis_look_floor1 *look, const float *logmdct, const float *logmask)
{
  vorbis_look_floor1 *v4; // ebp
  int v5; // ebx
  vorbis_info_floor1 *vi; // edx
  int n; // esi
  bool v8; // zf
  int v9; // eax
  int v10; // edi
  lsfit_acc *v11; // esi
  int v12; // esi
  int v13; // edi
  int v14; // edi
  int v15; // esi
  int v16; // ecx
  int v17; // eax
  int v18; // ebx
  int v19; // ebp
  int v20; // edx
  int v21; // ecx
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // ebp
  int v28; // eax
  int j; // eax
  int v30; // edx
  int k; // eax
  int v32; // eax
  char *v33; // eax
  int v34; // ecx
  bool v35; // sf
  int *v36; // ebp
  int v37; // eax
  int v38; // ebx
  int v39; // esi
  __int64 v40; // rax
  int v41; // eax
  int v42; // esi
  int v43; // ecx
  int v44; // eax
  int v45; // edx
  int y1; // [esp+10h] [ebp-D38h] BYREF
  int i; // [esp+14h] [ebp-D34h]
  int sortpos; // [esp+18h] [ebp-D30h] BYREF
  vorbis_info_floor1 *info; // [esp+1Ch] [ebp-D2Ch]
  int posts; // [esp+20h] [ebp-D28h]
  int hy0; // [esp+24h] [ebp-D24h] BYREF
  int hy1; // [esp+28h] [ebp-D20h] BYREF
  int ly0; // [esp+2Ch] [ebp-D1Ch] BYREF
  int ly1; // [esp+30h] [ebp-D18h] BYREF
  int fit_valueB[65]; // [esp+34h] [ebp-D14h] BYREF
  int fit_valueA[65]; // [esp+138h] [ebp-C10h] BYREF
  int loneighbor[65]; // [esp+23Ch] [ebp-B0Ch] BYREF
  int hineighbor[65]; // [esp+340h] [ebp-A08h] BYREF
  int memo[65]; // [esp+444h] [ebp-904h] BYREF
  lsfit_acc fits[64]; // [esp+548h] [ebp-800h] BYREF

  v4 = look;
  v5 = look->posts;
  vi = look->vi;
  n = look->n;
  info = vi;
  posts = v5;
  i = 0;
  y1 = 0;
  if ( v5 > 0 )
    memset32(fit_valueA, -200, v5);
  v8 = v5 == 0;
  if ( v5 > 0 )
  {
    memset32(fit_valueB, -200, v5);
    memset(loneighbor, 0, 4 * v5);
    memset32(hineighbor, 1, v5);
    memset(memo, 0xFFu, 4 * v5);
    v8 = v5 == 0;
  }
  if ( v8 )
  {
    v9 = accumulate_fit(0, fits, logmask, logmdct, n, n, vi);
  }
  else
  {
    v10 = 0;
    if ( v5 - 1 <= 0 )
      return (int *)y1;
    v11 = fits;
    while ( 1 )
    {
      i += accumulate_fit(look->sorted_index[v10], v11, logmask, logmdct, look->sorted_index[v10 + 1], look->n, vi);
      ++v10;
      ++v11;
      if ( v10 >= v5 - 1 )
        break;
      vi = info;
    }
    v9 = i;
  }
  if ( v9 )
  {
    sortpos = -200;
    y1 = -200;
    fit_line(fits, v5 - 1, &sortpos, &y1);
    v12 = sortpos;
    v13 = sortpos;
    fit_valueA[0] = sortpos;
    fit_valueB[0] = sortpos;
    fit_valueB[1] = y1;
    fit_valueA[1] = y1;
    i = 2;
    if ( v5 > 2 )
    {
      y1 = (int)&look->reverse_index[2];
      do
      {
        v14 = loneighbor[*(_DWORD *)y1];
        v15 = hineighbor[*(_DWORD *)y1];
        v8 = memo[v14] == v15;
        sortpos = *(_DWORD *)y1;
        if ( !v8 )
        {
          v16 = fit_valueA[v14];
          v17 = info->postlist[v15];
          v18 = v4->reverse_index[v14];
          v19 = v4->reverse_index[v15];
          hy0 = info->postlist[v14];
          v20 = fit_valueB[v14];
          memo[v14] = v15;
          hy1 = v17;
          if ( v16 >= 0 )
          {
            if ( v20 >= 0 )
              v20 = (v16 + v20) >> 1;
            else
              v20 = v16;
          }
          v21 = fit_valueA[v15];
          if ( v21 >= 0 )
          {
            v22 = fit_valueB[v15];
            if ( v22 >= 0 )
              v21 = (v22 + v21) >> 1;
          }
          else
          {
            v21 = fit_valueB[v15];
          }
          if ( v20 == -1 || v21 == -1 )
            exit(1);
          if ( inspect_error(hy0, hy1, v20, v21, logmask, logmdct, info) )
          {
            ly0 = -200;
            ly1 = -200;
            hy0 = -200;
            hy1 = -200;
            fit_line(&fits[v18], sortpos - v18, &ly0, &ly1);
            v23 = sortpos;
            fit_line(&fits[sortpos], v19 - sortpos, &hy0, &hy1);
            v24 = ly0;
            fit_valueB[v14] = ly0;
            if ( !v14 )
              fit_valueA[0] = v24;
            v25 = i;
            v26 = ly1;
            v27 = hy0;
            v28 = hy1;
            fit_valueA[i] = ly1;
            fit_valueB[v25] = v27;
            fit_valueA[v15] = v28;
            if ( v15 == 1 )
              fit_valueB[1] = v28;
            if ( v26 >= 0 || v27 >= 0 )
            {
              for ( j = v23 - 1; j >= 0; hineighbor[j + 1] = v25 )
              {
                if ( hineighbor[j] != v15 )
                  break;
                --j;
              }
              v30 = posts;
              for ( k = v23 + 1; k < v30; loneighbor[k++] = v25 )
              {
                if ( loneighbor[k] != v14 )
                  break;
              }
            }
          }
          else
          {
            v32 = i;
            fit_valueA[i] = -200;
            fit_valueB[v32] = -200;
          }
          v4 = look;
          v5 = posts;
        }
        y1 += 4;
        ++i;
      }
      while ( i < v5 );
      v13 = fit_valueB[0];
      v12 = fit_valueA[0];
    }
    v33 = _vorbis_block_alloc(vb, 4 * v5);
    y1 = (int)v33;
    if ( v12 >= 0 )
    {
      if ( v13 >= 0 )
        v12 = (v13 + v12) >> 1;
    }
    else
    {
      v12 = v13;
    }
    v34 = fit_valueA[1];
    v35 = fit_valueA[1] < 0;
    *(_DWORD *)v33 = v12;
    if ( v35 )
    {
      v34 = fit_valueB[1];
    }
    else if ( fit_valueB[1] >= 0 )
    {
      v34 = (fit_valueB[1] + v34) >> 1;
    }
    *((_DWORD *)v33 + 1) = v34;
    i = 2;
    if ( v5 > 2 )
    {
      sortpos = (int)&info->postlist[2];
      v36 = v4->hineighbor;
      do
      {
        v37 = v36[63];
        v38 = info->postlist[v37];
        v39 = *(_DWORD *)(y1 + 4 * v37) & 0x7FFF;
        v40 = (*(_DWORD *)(y1 + 4 * *v36) & 0x7FFF) - v39;
        v41 = (int)((*(_DWORD *)sortpos - v38) * ((HIDWORD(v40) ^ v40) - HIDWORD(v40))) / (info->postlist[*v36] - v38);
        if ( (*(_DWORD *)(y1 + 4 * *v36) & 0x7FFF) - v39 >= 0 )
          v42 = v41 + v39;
        else
          v42 = v39 - v41;
        v43 = i;
        v44 = fit_valueA[i];
        if ( v44 >= 0 )
        {
          v45 = fit_valueB[i];
          if ( v45 >= 0 )
            v44 = (v45 + v44) >> 1;
        }
        else
        {
          v44 = fit_valueB[i];
        }
        if ( v44 < 0 || v42 == v44 )
          *(_DWORD *)(y1 + 4 * i) = v42 | 0x8000;
        else
          *(_DWORD *)(y1 + 4 * i) = v44;
        sortpos += 4;
        ++v36;
        i = v43 + 1;
      }
      while ( v43 + 1 < posts );
    }
  }
  return (int *)y1;
}

// FUNC: _floor1_interpolate_fit
char *__cdecl floor1_interpolate_fit(vorbis_block *vb, vorbis_look_floor1 *look, int *A, int *B, int del)
{
  int posts; // ebp
  char *result; // eax
  int v7; // esi
  int *v8; // ecx
  int v9; // edi
  int v10; // edx

  posts = look->posts;
  result = 0;
  if ( A )
  {
    if ( B )
    {
      result = _vorbis_block_alloc(vb, 4 * posts);
      if ( posts > 0 )
      {
        v7 = (char *)A - (char *)B;
        v8 = B;
        v9 = result - (char *)B;
        do
        {
          v10 = (del * (*v8 & 0x7FFF) + (0x10000 - del) * (*(int *)((char *)v8 + v7) & 0x7FFF) + 0x8000) >> 16;
          *(int *)((char *)v8 + v9) = v10;
          if ( *((char *)v8 + v7 + 1) < 0 && *((char *)v8 + 1) < 0 )
          {
            BYTE1(v10) |= 0x80u;
            *(int *)((char *)v8 + v9) = v10;
          }
          ++v8;
          --posts;
        }
        while ( posts );
      }
    }
  }
  return result;
}

// FUNC: _floor1_encode
int __cdecl floor1_encode(vorbis_block *vb, vorbis_look_floor1 *look, int *post, int *ilogmask)
{
  vorbis_look_floor1 *v4; // ebp
  int posts; // ebx
  vorbis_block *v6; // esi
  int *v7; // edx
  int v8; // edi
  int v9; // esi
  int v10; // ecx
  int v11; // ecx
  int *hineighbor; // eax
  int v13; // ebp
  int v14; // ebx
  int v15; // esi
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // eax
  bool v23; // zf
  int quant_q; // eax
  unsigned int v25; // edx
  unsigned int v26; // eax
  int k; // ecx
  int m; // eax
  unsigned int v29; // eax
  int v30; // ecx
  vorbis_info_floor1 *v31; // eax
  int *partitionclass; // eax
  int v33; // ebp
  int v34; // ebx
  int v35; // edx
  int v36; // esi
  int v37; // ecx
  int v38; // eax
  int *v39; // edx
  int *v40; // edi
  int v41; // eax
  int v42; // eax
  vorbis_look_floor1 *v43; // ebx
  int v44; // esi
  int *v45; // edi
  int v46; // eax
  int v47; // ebp
  codebook *v48; // eax
  bool v49; // cc
  int v50; // ecx
  int v51; // edi
  int v52; // ebx
  int *v53; // ebp
  int v54; // eax
  int v55; // esi
  int n; // esi
  int result; // eax
  __int64 pcmend; // rax
  vorbis_info_floor1 *info; // [esp+10h] [ebp-168h]
  int *j; // [esp+14h] [ebp-164h]
  int ja; // [esp+14h] [ebp-164h]
  int jb; // [esp+14h] [ebp-164h]
  int *cdim; // [esp+18h] [ebp-160h]
  int cdima; // [esp+18h] [ebp-160h]
  int classa; // [esp+1Ch] [ebp-15Ch]
  int classb; // [esp+1Ch] [ebp-15Ch]
  int classc; // [esp+1Ch] [ebp-15Ch]
  char *cval; // [esp+20h] [ebp-158h]
  int cvala; // [esp+20h] [ebp-158h]
  int *i; // [esp+24h] [ebp-154h]
  int ia; // [esp+24h] [ebp-154h]
  int *v72; // [esp+28h] [ebp-150h]
  codebook *books; // [esp+2Ch] [ebp-14Ch]
  codec_setup_info *ci; // [esp+30h] [ebp-148h]
  int bookas[8]; // [esp+34h] [ebp-144h] BYREF
  int maxval[8]; // [esp+54h] [ebp-124h]
  int out[65]; // [esp+74h] [ebp-104h] BYREF

  v4 = look;
  posts = look->posts;
  v6 = vb;
  info = look->vi;
  v7 = post;
  ci = (codec_setup_info *)vb->vd->vi->codec_setup;
  books = ci->fullbooks;
  if ( post )
  {
    v8 = 0;
    if ( posts > 0 )
    {
      do
      {
        v9 = v7[v8];
        v10 = v9 & 0x7FFF;
        switch ( info->mult )
        {
          case 1:
            v10 >>= 2;
            break;
          case 2:
            v10 >>= 3;
            break;
          case 3:
            v10 /= 12;
            v7 = post;
            break;
          case 4:
            v10 >>= 4;
            break;
          default:
            break;
        }
        v7[v8++] = v10 | v9 & 0x8000;
      }
      while ( v8 < posts );
      v6 = vb;
    }
    v11 = v7[1];
    out[0] = *v7;
    out[1] = v11;
    if ( posts > 2 )
    {
      j = &info->postlist[2];
      i = v7 + 2;
      hineighbor = look->hineighbor;
      cdim = look->hineighbor;
      cval = (char *)((char *)out - (char *)v7);
      classa = posts - 2;
      while ( 1 )
      {
        v13 = hineighbor[63];
        v14 = *hineighbor;
        v15 = post[v13] & 0x7FFF;
        v16 = (post[*hineighbor] & 0x7FFF) - v15;
        v17 = (int)((*j - info->postlist[v13]) * abs32(v16)) / (info->postlist[*hineighbor] - info->postlist[v13]);
        v18 = v16 >= 0 ? v17 + v15 : v15 - v17;
        v19 = *i;
        if ( (BYTE1(*i) & 0x80u) != 0 || v18 == v19 )
        {
          BYTE1(v18) |= 0x80u;
          *(int *)((char *)i + (_DWORD)cval) = 0;
          *i = v18;
        }
        else
        {
          v20 = look->quant_q - v18;
          if ( v20 >= v18 )
            v20 = v18;
          v21 = v19 - v18;
          if ( v21 >= 0 )
            v22 = v21 < v20 ? 2 * v21 : v20 + v21;
          else
            v22 = v21 >= -v20 ? -1 - 2 * v21 : v20 - v21 - 1;
          *(int *)((char *)i + (_DWORD)cval) = v22;
          post[v13] = v15;
          post[v14] &= 0x7FFFu;
        }
        ++cdim;
        ++j;
        v23 = classa-- == 1;
        ++i;
        if ( v23 )
          break;
        hineighbor = cdim;
      }
      v4 = look;
      v6 = vb;
    }
    oggpack_write(&v6->opb, 1u, 1);
    quant_q = v4->quant_q;
    ++v4->frames;
    v25 = quant_q - 1;
    v26 = quant_q - 1;
    for ( k = 0; v26; v26 >>= 1 )
      ++k;
    v4->postbits += 2 * k;
    for ( m = 0; v25; v25 >>= 1 )
      ++m;
    oggpack_write(&v6->opb, out[0], m);
    v29 = v4->quant_q - 1;
    v30 = 0;
    if ( v4->quant_q != 1 )
    {
      do
      {
        ++v30;
        v29 >>= 1;
      }
      while ( v29 );
    }
    oggpack_write(&v6->opb, out[1], v30);
    v31 = info;
    ia = 0;
    ja = 2;
    if ( info->partitions > 0 )
    {
      partitionclass = info->partitionclass;
      v72 = info->partitionclass;
      do
      {
        v33 = *partitionclass;
        v34 = info->class_subs[*partitionclass];
        v35 = 0;
        cdima = info->class_dim[*partitionclass];
        v36 = 1 << v34;
        v37 = 0;
        classb = *partitionclass;
        memset(bookas, 0, sizeof(bookas));
        cvala = 0;
        if ( v34 )
        {
          v38 = 0;
          if ( v36 > 0 )
          {
            v39 = info->class_subbook[v33];
            do
            {
              if ( *v39 >= 0 )
              {
                v33 = classb;
                maxval[v38] = ci->book_param[*v39]->entries;
              }
              else
              {
                maxval[v38] = 1;
              }
              ++v38;
              ++v39;
            }
            while ( v38 < v36 );
            v35 = 0;
          }
          if ( cdima > 0 )
          {
            v40 = &out[ja];
            do
            {
              v41 = 0;
              if ( v36 > 0 )
              {
                while ( *v40 >= maxval[v41] )
                {
                  if ( ++v41 >= v36 )
                    goto LABEL_54;
                }
                bookas[v35] = v41;
              }
LABEL_54:
              v42 = bookas[v35++] << v37;
              v37 += v34;
              ++v40;
              cvala |= v42;
            }
            while ( v35 < cdima );
            v33 = classb;
          }
          v43 = look;
          look->phrasebits += vorbis_book_encode(&books[info->class_book[v33]], cvala, &vb->opb);
        }
        else
        {
          v43 = look;
        }
        v44 = 0;
        if ( cdima > 0 )
        {
          classc = 8 * v33 + 80;
          v45 = &out[ja];
          do
          {
            v46 = *(&info->partitions + classc + bookas[v44]);
            if ( v46 >= 0 )
            {
              v47 = v46;
              v48 = &books[v46];
              if ( *v45 < books[v47].entries )
                v43->postbits += vorbis_book_encode(v48, *v45, &vb->opb);
            }
            ++v44;
            ++v45;
          }
          while ( v44 < cdima );
        }
        ja += cdima;
        partitionclass = v72 + 1;
        v49 = ++ia < info->partitions;
        ++v72;
      }
      while ( v49 );
      v4 = look;
      v31 = info;
    }
    v50 = *post * v31->mult;
    v51 = 0;
    v52 = 0;
    jb = 1;
    if ( v4->posts > 1 )
    {
      v53 = &v4->forward_index[1];
      do
      {
        v54 = post[*v53] & 0x7FFF;
        if ( v54 == post[*v53] )
        {
          v51 = info->postlist[*v53];
          v55 = v54 * info->mult;
          render_line0(v52, v51, v50, v55, ilogmask);
          v52 = v51;
          v50 = v55;
        }
        ++v53;
        ++jb;
      }
      while ( jb < look->posts );
    }
    for ( n = v51; n < vb->pcmend / 2; ++n )
      ilogmask[n] = v50;
    result = 1;
    ++seq_0;
  }
  else
  {
    oggpack_write(&vb->opb, 0, 1);
    pcmend = vb->pcmend;
    ++seq_0;
    memset(ilogmask, 0, 4 * (((int)pcmend - HIDWORD(pcmend)) >> 1));
    return 0;
  }
  return result;
}
