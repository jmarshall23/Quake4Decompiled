
// FUNC: _mdct_init
void __cdecl mdct_init(mdct_lookup *lookup, int n)
{
  int v3; // esi
  long double v4; // st7
  float *v5; // edi
  int v6; // eax
  float *v7; // ecx
  double v8; // st5
  long double v9; // st5
  double v10; // st5
  long double v11; // st5
  int v12; // eax
  float *v13; // edi
  int v14; // ecx
  double v15; // st6
  long double v16; // st6
  int v17; // edi
  int i; // esi
  int v19; // ebx
  char v20; // cl
  int v21; // edx
  int v22; // [esp+18h] [ebp-10h]
  float v23; // [esp+1Ch] [ebp-Ch]
  int v24; // [esp+1Ch] [ebp-Ch]
  int v25; // [esp+1Ch] [ebp-Ch]
  int v26; // [esp+20h] [ebp-8h]
  int *bitrev; // [esp+24h] [ebp-4h]
  int na; // [esp+30h] [ebp+8h]

  v3 = n / 4;
  bitrev = (int *)_decoder_malloc(4 * (n / 4));
  v4 = (double)n;
  v5 = (float *)_decoder_malloc(4 * (n / 4 + n));
  *(float *)&na = v4;
  v23 = floor(__FYL2X__(v4, 0.69314718055994528623) / __FYL2X__(2.0, 0.69314718055994528623) + 0.5);
  v26 = (int)v23;
  lookup->log2n = v26;
  lookup->n = n;
  lookup->trig = v5;
  lookup->bitrev = bitrev;
  v6 = 0;
  if ( v3 > 0 )
  {
    v22 = 0;
    v7 = &v5[n >> 1];
    v24 = 1;
    do
    {
      v8 = (double)v22;
      v22 += 4;
      ++v6;
      v7 += 2;
      v9 = v8 * (3.1415927 / *(float *)&na);
      v5[2 * v6 - 2] = cos(v9);
      v5[2 * v6 - 1] = -sin(v9);
      v10 = (double)v24;
      v24 += 2;
      v11 = v10 * (3.1415927 / (double)(2 * n));
      *(v7 - 2) = cos(v11);
      *(v7 - 1) = sin(v11);
    }
    while ( v6 < v3 );
  }
  v12 = n / 8;
  if ( n / 8 > 0 )
  {
    v25 = 2;
    v13 = &v5[n];
    v14 = n / 8;
    do
    {
      v15 = (double)v25;
      v25 += 4;
      v13 += 2;
      --v14;
      v16 = v15 * (3.1415927 / *(float *)&na);
      *(v13 - 2) = cos(v16) * 0.5;
      *(v13 - 1) = sin(v16) * -0.5;
    }
    while ( v14 );
  }
  v17 = 1 << (v26 - 2);
  for ( i = 0; i < v12; ++i )
  {
    v19 = 0;
    v20 = 0;
    if ( v17 )
    {
      v21 = 1 << (v26 - 2);
      do
      {
        if ( (v21 & i) != 0 )
          v19 |= 1 << v20;
        v21 = v17 >> ++v20;
      }
      while ( v17 >> v20 );
    }
    bitrev[2 * i] = (((1 << (v26 - 1)) - 1) & ~v19) - 1;
    bitrev[2 * i + 1] = v19;
  }
  lookup->scale = 4.0 / *(float *)&na;
}

// FUNC: mdct_butterfly_8
void __usercall mdct_butterfly_8(float *x@<eax>)
{
  double v1; // st7
  double v2; // st6
  double v3; // st5
  double v4; // st7
  double v5; // st6
  double v6; // st7
  double v7; // st6
  float r2; // [esp+0h] [ebp-8h]
  float r3; // [esp+4h] [ebp-4h]

  v1 = x[2] + x[6];
  v2 = x[6] - x[2];
  v3 = *x + x[4];
  r3 = x[4] - *x;
  x[6] = v3 + v1;
  x[4] = v1 - v3;
  v4 = v2;
  v5 = x[5] - x[1];
  r2 = x[7] - x[3];
  *x = v4 + v5;
  x[2] = v4 - v5;
  v6 = x[1] + x[5];
  v7 = x[3] + x[7];
  x[3] = r3 + r2;
  x[1] = r2 - r3;
  x[7] = v7 + v6;
  x[5] = v7 - v6;
}

// FUNC: mdct_butterfly_16
void __usercall mdct_butterfly_16(float *x@<eax>)
{
  double v1; // st7
  double v2; // st6
  double v3; // st7
  double v4; // st6
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  float *v9; // ecx

  v1 = x[1] - x[9];
  v2 = *x - x[8];
  x[8] = x[8] + *x;
  x[9] = x[9] + x[1];
  *x = (v2 + v1) * 0.70710677;
  x[1] = (v1 - v2) * 0.70710677;
  v3 = x[3] - x[11];
  v4 = x[10] - x[2];
  x[10] = x[2] + x[10];
  x[11] = x[3] + x[11];
  x[2] = v3;
  x[3] = v4;
  v5 = x[12] - x[4];
  v6 = x[13] - x[5];
  x[12] = x[12] + x[4];
  x[13] = x[5] + x[13];
  x[4] = (v5 - v6) * 0.70710677;
  x[5] = (v6 + v5) * 0.70710677;
  v7 = x[14] - x[6];
  v8 = x[15] - x[7];
  x[14] = x[14] + x[6];
  x[15] = x[7] + x[15];
  x[6] = v7;
  x[7] = v8;
  mdct_butterfly_8(x);
  mdct_butterfly_8(v9);
}

// FUNC: mdct_butterfly_32
void __usercall mdct_butterfly_32(float *x@<eax>)
{
  double v1; // st7
  double v2; // st6
  double v3; // st7
  double v4; // st6
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st6
  double v11; // st7
  double v12; // st6
  double v13; // st7
  double v14; // st6
  double v15; // st7
  double v16; // st6
  float *v17; // edx

  v1 = x[30] - x[14];
  v2 = x[31] - x[15];
  x[30] = x[14] + x[30];
  x[31] = x[31] + x[15];
  x[14] = v1;
  x[15] = v2;
  v3 = x[28] - x[12];
  v4 = x[29] - x[13];
  x[28] = x[12] + x[28];
  x[29] = x[29] + x[13];
  x[12] = v3 * 0.9238795 - v4 * 0.38268343;
  x[13] = v4 * 0.9238795 + v3 * 0.38268343;
  v5 = x[26] - x[10];
  v6 = x[27] - x[11];
  x[26] = x[10] + x[26];
  x[27] = x[27] + x[11];
  x[10] = (v5 - v6) * 0.70710677;
  x[11] = (v6 + v5) * 0.70710677;
  v7 = x[24] - x[8];
  v8 = x[25] - x[9];
  x[24] = x[8] + x[24];
  x[25] = x[25] + x[9];
  x[8] = v7 * 0.38268343 - v8 * 0.9238795;
  x[9] = v8 * 0.38268343 + v7 * 0.9238795;
  v9 = x[22] - x[6];
  v10 = x[7] - x[23];
  x[22] = x[6] + x[22];
  x[23] = x[7] + x[23];
  x[6] = v10;
  x[7] = v9;
  v11 = x[4] - x[20];
  v12 = x[5] - x[21];
  x[20] = x[20] + x[4];
  x[21] = x[5] + x[21];
  x[4] = 0.9238795 * v12 + v11 * 0.38268343;
  x[5] = v12 * 0.38268343 - v11 * 0.9238795;
  v13 = x[2] - x[18];
  v14 = x[3] - x[19];
  x[18] = x[18] + x[2];
  x[19] = x[19] + x[3];
  x[2] = (v14 + v13) * 0.70710677;
  x[3] = (v14 - v13) * 0.70710677;
  v15 = *x - x[16];
  v16 = x[1] - x[17];
  x[16] = x[16] + *x;
  x[17] = x[17] + x[1];
  *x = 0.38268343 * v16 + v15 * 0.9238795;
  x[1] = v16 * 0.9238795 - v15 * 0.38268343;
  mdct_butterfly_16(x);
  mdct_butterfly_16(v17);
}

// FUNC: mdct_butterfly_first
void __usercall mdct_butterfly_first(float *T@<edx>, float *x@<edi>, int points@<ecx>)
{
  float *v3; // eax
  float *v4; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st6
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // st4

  v3 = &x[(points >> 1) - 8];
  v4 = &v3[points - (points >> 1) + 7];
  do
  {
    v5 = *(v4 - 1) - v3[6];
    v6 = *v4 - v3[7];
    *(v4 - 1) = *(v4 - 1) + v3[6];
    *v4 = v3[7] + *v4;
    v3[6] = v6 * T[1] + v5 * *T;
    v3[7] = v6 * *T - v5 * T[1];
    v7 = *(v4 - 3) - v3[4];
    v8 = *(v4 - 2) - v3[5];
    *(v4 - 3) = *(v4 - 3) + v3[4];
    *(v4 - 2) = *(v4 - 2) + v3[5];
    v3[4] = v8 * T[5] + v7 * T[4];
    v3[5] = v8 * T[4] - v7 * T[5];
    v9 = *(v4 - 5) - v3[2];
    v10 = *(v4 - 4) - v3[3];
    *(v4 - 5) = v3[2] + *(v4 - 5);
    *(v4 - 4) = v3[3] + *(v4 - 4);
    v3[2] = v10 * T[9] + v9 * T[8];
    v3[3] = v10 * T[8] - v9 * T[9];
    v11 = *(v4 - 7) - *v3;
    v12 = *(v4 - 6) - v3[1];
    *(v4 - 7) = *(v4 - 7) + *v3;
    *(v4 - 6) = v3[1] + *(v4 - 6);
    v13 = v12 * T[13];
    v3 -= 8;
    v14 = v11 * T[12];
    v4 -= 8;
    T += 16;
    v3[8] = v13 + v14;
    v3[9] = v12 * *(T - 4) - v11 * *(T - 3);
  }
  while ( v3 >= x );
}

// FUNC: mdct_butterfly_generic
void __usercall mdct_butterfly_generic(float *T@<edx>, float *x@<ebx>, int points@<ecx>, int trigint)
{
  unsigned int v4; // esi
  float *v5; // eax
  float *v6; // ecx
  double v7; // st7
  double v8; // st6
  double v9; // rt0
  double v10; // st6
  float *v11; // edx
  double v12; // st7
  double v13; // st6
  double v14; // rt1
  double v15; // st6
  float *v16; // edx
  double v17; // st7
  double v18; // st6
  double v19; // rt2
  double v20; // st6
  float *v21; // edx
  double v22; // st7
  double v23; // st6
  double v24; // rtt
  double v25; // st6

  v4 = trigint;
  v5 = &x[(points >> 1) - 8];
  v6 = &v5[points - (points >> 1) + 7];
  do
  {
    v7 = *(v6 - 1) - v5[6];
    v8 = *v6 - v5[7];
    *(v6 - 1) = *(v6 - 1) + v5[6];
    *v6 = v5[7] + *v6;
    v5[6] = v8 * T[1] + v7 * *T;
    v9 = v8 * *T;
    v10 = v7 * T[1];
    v11 = &T[v4];
    v5[7] = v9 - v10;
    v12 = *(v6 - 3) - v5[4];
    v13 = *(v6 - 2) - v5[5];
    *(v6 - 3) = v5[4] + *(v6 - 3);
    *(v6 - 2) = v5[5] + *(v6 - 2);
    v5[4] = v13 * v11[1] + v12 * *v11;
    v14 = v13 * *v11;
    v15 = v12 * v11[1];
    v16 = &v11[v4];
    v5[5] = v14 - v15;
    v17 = *(v6 - 5) - v5[2];
    v18 = *(v6 - 4) - v5[3];
    *(v6 - 5) = v5[2] + *(v6 - 5);
    *(v6 - 4) = v5[3] + *(v6 - 4);
    v5[2] = v18 * v16[1] + v17 * *v16;
    v19 = v18 * *v16;
    v20 = v17 * v16[1];
    v21 = &v16[v4];
    v5[3] = v19 - v20;
    v22 = *(v6 - 7) - *v5;
    v23 = *(v6 - 6) - v5[1];
    *(v6 - 7) = *v5 + *(v6 - 7);
    *(v6 - 6) = *(v6 - 6) + v5[1];
    v5 -= 8;
    v6 -= 8;
    v5[8] = v23 * v21[1] + v22 * *v21;
    v24 = v23 * *v21;
    v25 = v22 * v21[1];
    T = &v21[v4];
    v5[9] = v24 - v25;
  }
  while ( v5 >= x );
}

// FUNC: mdct_butterflies
void __usercall mdct_butterflies(mdct_lookup *init@<eax>, float *x, int points)
{
  int v3; // esi
  int v4; // ebx
  int v5; // ecx
  int v6; // ebx
  float *v7; // ebx
  int v8; // edi
  int v9; // esi
  int v10; // ebp
  bool v11; // zf
  float *v12; // edi
  unsigned int v13; // esi
  int i; // [esp+Ch] [ebp-Ch]
  int v15; // [esp+10h] [ebp-8h]
  float *T; // [esp+14h] [ebp-4h]

  v3 = points;
  v4 = init->log2n - 6;
  T = init->trig;
  if ( v4 > 0 )
    mdct_butterfly_first(init->trig, x, points);
  v5 = 1;
  v6 = v4 - 1;
  i = 1;
  if ( v6 > 0 )
  {
    v15 = v6;
    do
    {
      if ( 1 << v5 > 0 )
      {
        v7 = x;
        v8 = 4 << v5;
        v9 = v3 >> v5;
        v10 = 1 << v5;
        do
        {
          mdct_butterfly_generic(T, v7, v9, v8);
          v7 += v9;
          --v10;
        }
        while ( v10 );
        v3 = points;
        v5 = i;
      }
      ++v5;
      v11 = v15-- == 1;
      i = v5;
    }
    while ( !v11 );
  }
  if ( v3 > 0 )
  {
    v12 = x;
    v13 = ((unsigned int)(v3 - 1) >> 5) + 1;
    do
    {
      mdct_butterfly_32(v12);
      v12 += 32;
      --v13;
    }
    while ( v13 );
  }
}

// FUNC: _mdct_clear
void __cdecl mdct_clear(mdct_lookup *l)
{
  if ( l )
  {
    if ( l->trig )
      _decoder_free(l->trig);
    if ( l->bitrev )
      _decoder_free(l->bitrev);
    l->n = 0;
    l->log2n = 0;
    l->trig = 0;
    l->bitrev = 0;
    l->scale = 0.0;
  }
}

// FUNC: mdct_bitreverse
void __usercall mdct_bitreverse(mdct_lookup *init@<eax>, float *x@<edx>)
{
  int *bitrev; // esi
  float *v3; // ebp
  float *v4; // eax
  float *v5; // ecx
  int v6; // ebx
  double v7; // st7
  float *v8; // edi
  double v9; // st6
  float *v10; // ebx
  double v11; // st6
  double v12; // st7
  double v13; // st6
  int v14; // edi
  int v15; // ebx
  double v16; // st7
  float *v17; // edi
  double v18; // st6
  float *v19; // ebx
  double v20; // st6
  double v21; // st7
  double v22; // st6
  float r2; // [esp+10h] [ebp-8h]
  float r2a; // [esp+10h] [ebp-8h]
  float r1; // [esp+14h] [ebp-4h]
  float r1a; // [esp+14h] [ebp-4h]

  bitrev = init->bitrev;
  v3 = &x[init->n >> 1];
  v4 = &init->trig[init->n];
  v5 = v3 + 3;
  do
  {
    v6 = bitrev[1];
    v7 = v3[*bitrev + 1] - v3[v6 + 1];
    v8 = &v3[*bitrev];
    v9 = v3[v6];
    v10 = &v3[v6];
    v11 = v9 + *v8;
    v5 -= 4;
    r2 = v11 * *v4 + v7 * v4[1];
    v12 = v11 * v4[1] - v7 * *v4;
    v13 = (v10[1] + v8[1]) * 0.5;
    r1 = (*v8 - *v10) * 0.5;
    *x = r2 + v13;
    *(v5 - 1) = v13 - r2;
    x[1] = r1 + v12;
    *v5 = v12 - r1;
    v14 = bitrev[2];
    v15 = bitrev[3];
    v16 = v3[v14 + 1] - v3[v15 + 1];
    v17 = &v3[v14];
    v18 = v3[v15];
    v19 = &v3[v15];
    v20 = v18 + *v17;
    r2a = v20 * v4[2] + v16 * v4[3];
    v21 = v20 * v4[3] - v16 * v4[2];
    v22 = (v19[1] + v17[1]) * 0.5;
    r1a = (*v17 - *v19) * 0.5;
    x[2] = r2a + v22;
    *(v5 - 3) = v22 - r2a;
    x[3] = r1a + v21;
    x += 4;
    v4 += 4;
    bitrev += 4;
    *(v5 - 2) = v21 - r1a;
  }
  while ( x < v5 - 3 );
}

// FUNC: _mdct_backward
void __cdecl mdct_backward(mdct_lookup *init, float *in, float *out)
{
  int v4; // eax
  int v5; // esi
  float *v6; // edx
  unsigned int v7; // ebp
  float *trig; // eax
  float *v10; // ecx
  float *v11; // eax
  double v12; // st7
  mdct_lookup *v13; // edx
  float *v14; // ecx
  float *v15; // eax
  double v16; // st7
  float *p_n; // edx
  float *v19; // eax
  mdct_lookup *v20; // edi
  float *v21; // ecx
  double v22; // st7
  double v23; // st6
  float *v24; // eax
  float *v25; // ecx
  float *v26; // edx
  double v27; // st7
  double v28; // st7
  double v29; // st7
  double v30; // st7
  mdct_lookup *v31; // ecx
  mdct_lookup *v32; // eax
  int *n; // edx
  mdct_lookup *inita; // [esp+14h] [ebp+4h]
  float *ina; // [esp+18h] [ebp+8h]
  float *outa; // [esp+1Ch] [ebp+Ch]

  v4 = init->n >> 2;
  v5 = init->n >> 1;
  v6 = &out[v4 + v5];
  v7 = v4;
  trig = init->trig;
  v10 = &in[v5 - 7];
  inita = (mdct_lookup *)v6;
  ina = (float *)(v7 * 4);
  v11 = &trig[v7];
  do
  {
    v6 -= 4;
    v12 = v10[2] * v11[3];
    v10 -= 8;
    v11 += 4;
    *v6 = -v12 - v10[8] * *(v11 - 2);
    v6[1] = v10[8] * *(v11 - 1) - v10[10] * *(v11 - 2);
    v6[2] = -(*(v11 - 3) * v10[14]) - v10[12] * *(v11 - 4);
    v6[3] = *(v11 - 3) * v10[12] - *(v11 - 4) * v10[14];
  }
  while ( v10 >= in );
  v13 = inita;
  v14 = &in[v5 - 8];
  v15 = &init->trig[v7];
  do
  {
    v15 -= 4;
    v16 = v14[4] * v15[3];
    v14 -= 8;
    v13 = (mdct_lookup *)((char *)v13 + 16);
    *(float *)&v13[-1].log2n = v16 + v15[2] * v14[14];
    *(float *)&v13[-1].trig = v14[12] * v15[2] - v15[3] * v14[14];
    *(float *)&v13[-1].bitrev = v14[10] * *v15 + v14[8] * v15[1];
    v13[-1].scale = v14[8] * *v15 - v15[1] * v14[10];
  }
  while ( v14 >= in );
  outa = &out[v5];
  mdct_butterflies(init, outa, v5);
  mdct_bitreverse(init, out);
  p_n = (float *)&inita->n;
  v19 = &init->trig[v5];
  v20 = inita;
  v21 = out + 3;
  do
  {
    p_n -= 4;
    v22 = v19[1] * *(v21 - 3);
    v21 += 8;
    v23 = *v19 * *(v21 - 10);
    v20 = (mdct_lookup *)((char *)v20 + 16);
    v19 += 8;
    p_n[3] = v22 - v23;
    *(float *)&v20[-1].log2n = -(*(v19 - 7) * *(v21 - 10) + *(v21 - 11) * *(v19 - 8));
    p_n[2] = *(v21 - 9) * *(v19 - 5) - *(v21 - 8) * *(v19 - 6);
    *(float *)&v20[-1].trig = -(*(v21 - 9) * *(v19 - 6) + *(v21 - 8) * *(v19 - 5));
    p_n[1] = *(v21 - 7) * *(v19 - 3) - *(v21 - 6) * *(v19 - 4);
    *(float *)&v20[-1].bitrev = -(*(v21 - 6) * *(v19 - 3) + *(v21 - 7) * *(v19 - 4));
    *p_n = *(v21 - 5) * *(v19 - 1) - *(v21 - 4) * *(v19 - 2);
    v20[-1].scale = -(*(v21 - 4) * *(v19 - 1) + *(v21 - 5) * *(v19 - 2));
  }
  while ( v21 - 3 < p_n );
  v24 = (float *)&inita->n;
  v25 = (float *)((int)out + (_DWORD)ina + 8);
  v26 = (float *)(&inita->n + 2 - v5);
  do
  {
    v27 = *(v24 - 1);
    v24 -= 4;
    *(v26 - 3) = v27;
    v26 -= 4;
    v25 += 4;
    *(v25 - 6) = -v27;
    v28 = v24[2];
    *v26 = v24[2];
    *(v25 - 5) = -v28;
    v29 = v24[1];
    *(v26 - 1) = v24[1];
    *(v25 - 4) = -v29;
    v30 = *v24;
    *(v26 - 2) = *v24;
    *(v25 - 3) = -v30;
  }
  while ( v25 - 2 < v24 );
  v31 = inita;
  v32 = inita;
  do
  {
    v32 = (mdct_lookup *)((char *)v32 - 16);
    v32->n = (int)v31->bitrev;
    v32->log2n = (int)v31->trig;
    v32->trig = (float *)v31->log2n;
    n = (int *)v31->n;
    v31 = (mdct_lookup *)((char *)v31 + 16);
    v32->bitrev = n;
  }
  while ( v32 > (mdct_lookup *)outa );
}

// FUNC: _mdct_forward
void __cdecl mdct_forward(mdct_lookup *init, float *in, float *out)
{
  int n; // ebx
  int v5; // eax
  int v6; // ebx
  void *v7; // esp
  float *v8; // esi
  float *v9; // edx
  float *v10; // eax
  int v11; // ecx
  double v12; // st7
  double v13; // st6
  float *v14; // edx
  float *v15; // ebx
  double v16; // st7
  double v17; // st6
  double v18; // st6
  float *v19; // edx
  bool v20; // cc
  float *v21; // ebx
  float *v22; // edx
  double v23; // st7
  double v24; // st6
  float *v25; // ebx
  double v26; // st6
  unsigned int v27; // ebx
  float *v28; // eax
  float *v29; // ecx
  int v30; // edx
  float *v31; // edx
  unsigned int v32; // ebx
  float *v33; // esi
  double v34; // st7
  double v35; // st6
  double v36; // st7
  double v37; // st6
  float v38[3]; // [esp+0h] [ebp-24h] BYREF
  unsigned int v39; // [esp+Ch] [ebp-18h]
  float *v40; // [esp+10h] [ebp-14h]
  unsigned int v41; // [esp+14h] [ebp-10h]
  int n4; // [esp+18h] [ebp-Ch]
  int n2; // [esp+1Ch] [ebp-8h]
  float *x1; // [esp+20h] [ebp-4h]
  int i; // [esp+2Ch] [ebp+8h]
  int ia; // [esp+2Ch] [ebp+8h]
  int ib; // [esp+2Ch] [ebp+8h]

  n = init->n;
  n2 = init->n >> 1;
  v39 = 4 * n;
  v5 = 4 * n + 3;
  LOBYTE(v5) = v5 & 0xFC;
  n4 = n >> 2;
  v6 = n >> 3;
  v7 = alloca(v5);
  v8 = v38;
  v40 = &v38[n2];
  v9 = &in[n2 + n4];
  x1 = v9 + 1;
  v10 = &init->trig[n2];
  v41 = 4 * n2;
  v11 = 0;
  i = (int)v9;
  if ( v6 > 0 )
  {
    while ( 1 )
    {
      i = (int)(v9 - 4);
      v12 = *(v9 - 2) + *x1;
      v10 -= 2;
      v13 = x1[2] + *(v9 - 4);
      v14 = v40;
      x1 += 4;
      v11 += 2;
      v40[v11 - 2] = v13 * v10[1] + v12 * *v10;
      v14[v11 - 1] = v13 * *v10 - v12 * v10[1];
      if ( v11 >= v6 )
        break;
      v9 = (float *)i;
    }
  }
  x1 = in + 1;
  v40 = (float *)(n2 - v6);
  if ( v11 < n2 - v6 )
  {
    v15 = x1;
    do
    {
      v16 = *(float *)(i - 8) - *v15;
      v10 -= 2;
      v17 = *(float *)(i - 16);
      i -= 16;
      v18 = v17 - v15[2];
      v19 = &v38[v41 / 4];
      v11 += 2;
      v15 += 4;
      v20 = v11 < (int)v40;
      v19[v11 - 2] = v18 * v10[1] + v16 * *v10;
      v19[v11 - 1] = v18 * *v10 - v16 * v10[1];
    }
    while ( v20 );
    x1 = v15;
  }
  v21 = &in[v39 / 4];
  if ( v11 < n2 )
  {
    v22 = x1;
    while ( 1 )
    {
      v10 -= 2;
      v23 = -*(v21 - 2) - *v22;
      ia = (int)(v21 - 4);
      v24 = *(v21 - 4);
      v25 = &v38[v41 / 4];
      v26 = -v24 - v22[2];
      v11 += 2;
      v22 += 4;
      v20 = v11 < n2;
      v25[v11 - 2] = v26 * v10[1] + v23 * *v10;
      v25[v11 - 1] = v26 * *v10 - v23 * v10[1];
      if ( !v20 )
        break;
      v21 = (float *)ia;
    }
  }
  v27 = v41;
  mdct_butterflies(init, &v38[v41 / 4], n2);
  mdct_bitreverse(init, v38);
  v28 = (float *)((char *)init->trig + v27);
  v29 = (float *)((char *)out + v27);
  v30 = 0;
  if ( n4 >= 4 )
  {
    v31 = out + 2;
    ib = 4 * (((unsigned int)(n4 - 4) >> 2) + 1);
    v32 = ((unsigned int)(n4 - 4) >> 2) + 1;
    do
    {
      v33 = v8 + 2;
      v34 = *v28 * *(v33 - 2);
      v33 += 4;
      v35 = v28[1] * *(v33 - 5);
      v8 = v33 + 2;
      v29 -= 4;
      v28 += 8;
      v31 += 4;
      --v32;
      *(v31 - 6) = (v34 + v35) * init->scale;
      v29[3] = (*(v28 - 7) * *(v8 - 8) - *(v28 - 8) * *(v8 - 7)) * init->scale;
      *(v31 - 5) = (*(v28 - 6) * *(v8 - 6) + *(v28 - 5) * *(v8 - 5)) * init->scale;
      v29[2] = (*(v28 - 5) * *(v8 - 6) - *(v28 - 6) * *(v8 - 5)) * init->scale;
      *(v31 - 4) = (*(v8 - 3) * *(v28 - 3) + *(v28 - 4) * *(v8 - 4)) * init->scale;
      v29[1] = (*(v28 - 3) * *(v8 - 4) - *(v8 - 3) * *(v28 - 4)) * init->scale;
      *(v31 - 3) = (*(v28 - 2) * *(v8 - 2) + *(v28 - 1) * *(v8 - 1)) * init->scale;
      *v29 = (*(v28 - 1) * *(v8 - 2) - *(v28 - 2) * *(v8 - 1)) * init->scale;
    }
    while ( v32 );
    v30 = ib;
  }
  if ( v30 < n4 )
  {
    do
    {
      v36 = *v28 * *v8;
      --v29;
      ++v30;
      v37 = v28[1] * v8[1];
      v8 += 2;
      v28 += 2;
      v20 = v30 < n4;
      out[v30 - 1] = (v36 + v37) * init->scale;
      *v29 = (*(v28 - 1) * *(v8 - 2) - *(v28 - 2) * *(v8 - 1)) * init->scale;
    }
    while ( v20 );
  }
}
