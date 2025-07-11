
// FUNC: __vp_global_free
void __cdecl _vp_global_free(vorbis_look_psy_global *look)
{
  if ( look )
  {
    look->ampmax = 0.0;
    look->channels = 0;
    look->gi = 0;
    *(_QWORD *)&look->coupling_pointlimit[0][0] = 0i64;
    look->coupling_pointlimit[0][2] = 0;
    *(_QWORD *)&look->coupling_pointlimit[1][0] = 0i64;
    look->coupling_pointlimit[1][2] = 0;
    _decoder_free(look);
  }
}

// FUNC: __vi_psy_free
void __cdecl _vi_psy_free(vorbis_info_psy *i)
{
  if ( i )
  {
    memset(i, 0, sizeof(vorbis_info_psy));
    _decoder_free(i);
  }
}

// FUNC: min_curve
void __usercall min_curve(float *c@<ecx>, float *c2@<eax>)
{
  float *v3; // ecx
  int v4; // edi
  float *v5; // edx
  int v6; // esi

  v3 = c + 1;
  v4 = (char *)c2 - (char *)c;
  v5 = c2 + 3;
  v6 = 7;
  do
  {
    if ( *(v5 - 3) < (double)*(v3 - 1) )
      *(v3 - 1) = *(v5 - 3);
    if ( *(float *)((char *)v3 + v4) < (double)*v3 )
      *v3 = *(float *)((char *)v3 + v4);
    if ( *(v5 - 1) < (double)v3[1] )
      v3[1] = *(v5 - 1);
    if ( *v5 < (double)v3[2] )
      v3[2] = *v5;
    if ( v5[1] < (double)v3[3] )
      v3[3] = v5[1];
    if ( v5[2] < (double)v3[4] )
      v3[4] = v5[2];
    if ( v5[3] < (double)v3[5] )
      v3[5] = v5[3];
    if ( v5[4] < (double)v3[6] )
      v3[6] = v5[4];
    v3 += 8;
    v5 += 8;
    --v6;
  }
  while ( v6 );
}

// FUNC: max_curve
void __usercall max_curve(float *c@<ecx>, float *c2@<eax>)
{
  float *v3; // ecx
  int v4; // edi
  float *v5; // edx
  int v6; // esi

  v3 = c + 1;
  v4 = (char *)c2 - (char *)c;
  v5 = c2 + 3;
  v6 = 7;
  do
  {
    if ( *(v5 - 3) > (double)*(v3 - 1) )
      *(v3 - 1) = *(v5 - 3);
    if ( *(float *)((char *)v3 + v4) > (double)*v3 )
      *v3 = *(float *)((char *)v3 + v4);
    if ( *(v5 - 1) > (double)v3[1] )
      v3[1] = *(v5 - 1);
    if ( *v5 > (double)v3[2] )
      v3[2] = *v5;
    if ( v5[1] > (double)v3[3] )
      v3[3] = v5[1];
    if ( v5[2] > (double)v3[4] )
      v3[4] = v5[2];
    if ( v5[3] > (double)v3[5] )
      v3[5] = v5[3];
    if ( v5[4] > (double)v3[6] )
      v3[6] = v5[4];
    v3 += 8;
    v5 += 8;
    --v6;
  }
  while ( v6 );
}

// FUNC: attenuate_curve
void __usercall attenuate_curve(float *c@<eax>, float att)
{
  float *v2; // eax
  int v3; // ecx

  v2 = c + 2;
  v3 = 7;
  do
  {
    v2 += 8;
    --v3;
    *(v2 - 10) = att + *(v2 - 10);
    *(v2 - 9) = att + *(v2 - 9);
    *(v2 - 8) = att + *(v2 - 8);
    *(v2 - 7) = att + *(v2 - 7);
    *(v2 - 6) = att + *(v2 - 6);
    *(v2 - 5) = att + *(v2 - 5);
    *(v2 - 4) = att + *(v2 - 4);
    *(v2 - 3) = att + *(v2 - 3);
  }
  while ( v3 );
}

// FUNC: __vp_psy_init
void __cdecl _vp_psy_init(vorbis_look_psy *p, vorbis_info_psy *vi, vorbis_info_psy_global *gi, int n, int rate)
{
  int v6; // ebp
  unsigned __int64 v7; // rax
  double v8; // st7
  double v9; // st5
  int v10; // ecx
  int v11; // ebx
  int v12; // edi
  double v13; // st7
  long double v16; // st6
  int v17; // eax
  double v18; // st7
  int v19; // edi
  int v20; // ecx
  int v21; // edx
  int v22; // ebx
  int v23; // ebx
  int v24; // edx
  double v25; // st7
  int i; // edi
  int v27; // ecx
  long double v28; // st6
  long double v29; // st6
  int v30; // eax
  long double v31; // st6
  float binHz; // [esp+0h] [ebp-44h]
  int lo; // [esp+20h] [ebp-24h]
  int v34; // [esp+24h] [ebp-20h]
  int v35; // [esp+24h] [ebp-20h]
  float bark; // [esp+28h] [ebp-1Ch]
  double v37; // [esp+34h] [ebp-10h]
  double v38; // [esp+3Ch] [ebp-8h]
  float pa; // [esp+48h] [ebp+4h]
  vorbis_look_psy *pb; // [esp+48h] [ebp+4h]
  int inthalfoc; // [esp+50h] [ebp+Ch]
  int inthalfoca; // [esp+50h] [ebp+Ch]
  int inthalfocb; // [esp+50h] [ebp+Ch]
  int inthalfocc; // [esp+50h] [ebp+Ch]
  int ratea; // [esp+58h] [ebp+14h]
  int rateb; // [esp+58h] [ebp+14h]

  memset(p, 0, sizeof(vorbis_look_psy));
  p->eighth_octave_lines = gi->eighth_octave_lines;
  lo = -99;
  v6 = 1;
  v7 = (unsigned __int64)(floor(
                            __FYL2X__((double)gi->eighth_octave_lines * 8.0, 0.69314718055994528623)
                          / __FYL2X__(2.0, 0.69314718055994528623)
                          + 0.5)
                        - 1.0);
  v8 = (double)rate;
  v37 = (double)n;
  p->shiftoc = v7;
  v9 = (double)(1 << (v7 + 1));
  v10 = (unsigned __int64)((__FYL2X__(v8 * 0.25 * 0.5 / v37, 0.69314718055994528623) * 1.442695021629333
                          - 5.965784072875977)
                         * v9
                         - (double)gi->eighth_octave_lines);
  p->firstoc = v10;
  v11 = n;
  p->total_octave_lines = (__int64)((__FYL2X__((v37 + 0.25) * v8 * 0.5 / v37, 0.69314718055994528623)
                                   * 1.442695021629333
                                   - 5.965784072875977)
                                  * v9
                                  + 0.5)
                        - v10
                        + 1;
  p->ath = (float *)_decoder_malloc(4 * n);
  p->octave = (int *)_decoder_malloc(4 * n);
  v38 = v8;
  v12 = 0;
  p->bark = (int *)_decoder_malloc(4 * n);
  p->vi = vi;
  p->n = n;
  p->rate = rate;
  inthalfoc = 0;
  do
  {
    v34 = inthalfoc + 1;
    v13 = ((double)(inthalfoc + 1) * 0.125 - 2.0 + 5.965784072875977) * 0.6931470036506653 * 1.442695040888963387;
    _ST6 = v13;
    __asm { frndint }
    v16 = __FSCALE__(__F2XM1__(v13 - _ST6) + 1.0, _ST6);
    v17 = (int)floor((v16 * v37 + v16 * v37) / v38 + 0.5);
    v18 = ATH[inthalfoc];
    if ( v12 < v17 )
    {
      pa = (ATH[inthalfoc + 1] - v18) / (double)(v17 - v12);
      do
      {
        if ( v12 >= n )
          break;
        p->ath[v12++] = v18 + 100.0;
        v18 = v18 + pa;
      }
      while ( v12 < v17 );
    }
    ++inthalfoc;
  }
  while ( v34 < 87 );
  v19 = 0;
  if ( n > 0 )
  {
    v20 = rate / (2 * n);
    v21 = v20 * v20;
    inthalfoca = 0;
    pb = 0;
    do
    {
      bark = atan2((double)(v19 * (int)pb) * 0.0000000185, 1.0) * 2.240000009536743
           + atan2((double)inthalfoca * 0.00073999999, 1.0) * 13.10000038146973
           + (double)inthalfoca * 0.000099999997;
      if ( lo + vi->noisewindowlomin < v19 )
      {
        v35 = lo + vi->noisewindowlomin;
        v22 = lo * v21;
        ratea = lo * v20;
        do
        {
          if ( atan2((double)(lo * v22) * 0.0000000185, 1.0) * 2.240000009536743
             + atan2((double)ratea * 0.00073999999, 1.0) * 13.10000038146973
             + (double)ratea * 0.000099999997 >= bark - vi->noisewindowlo )
            break;
          ++lo;
          ratea += v20;
          v22 += v21;
          ++v35;
        }
        while ( v35 < v19 );
      }
      if ( v6 <= n )
      {
        rateb = v6 * v20;
        v23 = v6 * v21;
        do
        {
          if ( v6 >= v19 + vi->noisewindowhimin
            && bark + vi->noisewindowhi <= atan2((double)(v6 * v23) * 0.0000000185, 1.0) * 2.240000009536743
                                         + atan2((double)rateb * 0.00073999999, 1.0) * 13.10000038146973
                                         + (double)rateb * 0.000099999997 )
          {
            break;
          }
          rateb += v20;
          ++v6;
          v23 += v21;
        }
        while ( v6 <= n );
      }
      pb = (vorbis_look_psy *)((char *)pb + v21);
      inthalfoca += v20;
      p->bark[v19++] = (lo << 16) + v6 - 65537;
    }
    while ( v19 < n );
    v11 = n;
  }
  v24 = 0;
  for ( inthalfocb = 0;
        v24 < v11;
        p->octave[v24 - 1] = (__int64)((__FYL2X__(v25 * v38 * 0.5 / v37, 0.69314718055994528623) * 1.442695021629333
                                      - 5.965784072875977)
                                     * (double)(1 << (p->shiftoc + 1))
                                     + 0.5) )
  {
    v25 = (double)inthalfocb + 0.25;
    inthalfocb = ++v24;
  }
  binHz = v38 * 0.5 / v37;
  p->tonecurves = setup_tone_curves(binHz, v11, vi->tone_centerboost, vi->tone_decay);
  p->noiseoffset = (float **)_decoder_malloc(0xCu);
  for ( i = 0; i < 3; ++i )
    p->noiseoffset[i] = (float *)_decoder_malloc(4 * v11);
  v27 = 0;
  for ( inthalfocc = 0;
        v27 < v11;
        *(float *)(*((_DWORD *)p->noiseoffset + 2) + 4 * v27 - 4) = v31 * p->vi->noiseoff[2][v30 + 1]
                                                                  + p->vi->noiseoff[2][v30] * (1.0 - v31) )
  {
    v28 = __FYL2X__(((double)inthalfocc + 0.5) * v38 / (v37 + v37), 0.69314718055994528623);
    v29 = v28 * 1.442695021629333 - 5.965784072875977 + v28 * 1.442695021629333 - 5.965784072875977;
    if ( v29 >= 0.0 )
    {
      if ( v29 >= 16.0 )
        v29 = 16.0;
    }
    else
    {
      v29 = 0.0;
    }
    inthalfocc = ++v27;
    v30 = (int)v29;
    v31 = v29 - (double)(int)v29;
    (*p->noiseoffset)[v27 - 1] = v31 * p->vi->noiseoff[0][v30 + 1] + p->vi->noiseoff[0][v30] * (1.0 - v31);
    *(float *)(*((_DWORD *)p->noiseoffset + 1) + 4 * v27 - 4) = v31 * p->vi->noiseoff[1][v30 + 1]
                                                              + p->vi->noiseoff[1][v30] * (1.0 - v31);
  }
}

// FUNC: __vp_psy_clear
void __cdecl _vp_psy_clear(vorbis_look_psy *p)
{
  int i; // ebx
  int j; // esi
  int k; // esi

  if ( p )
  {
    if ( p->ath )
      _decoder_free(p->ath);
    if ( p->octave )
      _decoder_free(p->octave);
    if ( p->bark )
      _decoder_free(p->bark);
    if ( p->tonecurves )
    {
      for ( i = 0; i < 17; ++i )
      {
        for ( j = 0; j < 8; ++j )
          _decoder_free(p->tonecurves[i][j]);
        _decoder_free(p->tonecurves[i]);
      }
      _decoder_free(p->tonecurves);
    }
    if ( p->noiseoffset )
    {
      for ( k = 0; k < 3; ++k )
        _decoder_free(p->noiseoffset[k]);
      _decoder_free(p->noiseoffset);
    }
    memset(p, 0, sizeof(vorbis_look_psy));
  }
}

// FUNC: seed_curve
void __usercall seed_curve(
        float *seed@<esi>,
        const float **curves@<edx>,
        float amp,
        int oc,
        int n,
        int linesper,
        float dBoffset)
{
  int v7; // eax
  int v8; // eax
  const float *v9; // ebp
  unsigned __int64 v10; // rax
  int v11; // ecx
  float *v12; // edi
  double v13; // st7
  int v14; // ecx
  double v15; // st7
  int v16; // ecx
  double v17; // st7
  int v18; // ecx
  double v19; // st7
  double v20; // st7
  int post1; // [esp+0h] [ebp-8h]

  v7 = (__int64)((amp + dBoffset - 30.0) * 0.1000000014901161);
  v8 = v7 <= 0 ? 0 : v7;
  if ( v8 >= 7 )
    v8 = 7;
  v9 = curves[v8];
  post1 = (int)v9[1];
  v10 = (unsigned __int64)*v9;
  HIDWORD(v10) = v10;
  v11 = (int)((*v9 - 16.0) * (double)linesper + (double)oc - (double)(linesper >> 1));
  if ( post1 - (int)v10 < 4 )
  {
LABEL_22:
    while ( SHIDWORD(v10) < post1 )
    {
      if ( v11 > 0 )
      {
        v20 = amp + v9[HIDWORD(v10) + 2];
        if ( v20 > seed[v11] )
          seed[v11] = v20;
      }
      v11 += linesper;
      if ( v11 >= n )
        break;
      ++HIDWORD(v10);
    }
  }
  else
  {
    v12 = (float *)&v9[v10 + 4];
    while ( 1 )
    {
      if ( v11 > 0 )
      {
        v13 = amp + *(v12 - 2);
        if ( v13 > seed[v11] )
          seed[v11] = v13;
      }
      v14 = linesper + v11;
      if ( v14 >= n )
        break;
      if ( v14 > 0 )
      {
        v15 = amp + *(v12 - 1);
        if ( v15 > seed[v14] )
          seed[v14] = v15;
      }
      v16 = linesper + v14;
      if ( v16 >= n )
        break;
      if ( v16 > 0 )
      {
        v17 = amp + *v12;
        if ( v17 > seed[v16] )
          seed[v16] = v17;
      }
      v18 = linesper + v16;
      if ( v18 >= n )
        break;
      if ( v18 > 0 )
      {
        v19 = amp + v12[1];
        if ( v19 > seed[v18] )
          seed[v18] = v19;
      }
      v11 = linesper + v18;
      if ( v11 >= n )
        break;
      HIDWORD(v10) += 4;
      v12 += 4;
      if ( SHIDWORD(v10) >= post1 - 3 )
        goto LABEL_22;
    }
  }
}

// FUNC: seed_loop
void __usercall seed_loop(
        vorbis_look_psy *p@<ebx>,
        const float ***curves,
        const float *f,
        const float *flr,
        float *seed,
        float specmax)
{
  int v6; // ecx
  int v7; // edi
  double v8; // st7
  int *octave; // ebp
  int v10; // esi
  int v11; // edx
  int *v12; // ecx
  bool v13; // c0
  int v14; // esi
  int n; // [esp+0h] [ebp-8h]
  float dBoffset; // [esp+4h] [ebp-4h]
  float specmaxa; // [esp+1Ch] [ebp+14h]

  v6 = p->n;
  v7 = 0;
  dBoffset = p->vi->max_curve_dB - specmax;
  for ( n = p->n; v7 < n; ++v7 )
  {
    v8 = f[v7];
    octave = p->octave;
    v10 = octave[v7];
    specmaxa = f[v7];
    if ( v7 + 1 < v6 )
    {
      v11 = v7 + 1;
      v12 = &octave[v7 + 1];
      do
      {
        if ( *v12 != v10 )
          break;
        v13 = v8 < f[++v7];
        ++v12;
        ++v11;
        if ( v13 )
          v8 = f[v7];
      }
      while ( v11 < n );
      specmaxa = v8;
    }
    if ( v8 + 6.0 > flr[v7] )
    {
      v14 = v10 >> p->shiftoc;
      if ( v14 < 17 )
      {
        if ( v14 < 0 )
          v14 = 0;
      }
      else
      {
        v14 = 16;
      }
      seed_curve(
        seed,
        curves[v14],
        specmaxa,
        octave[v7] - p->firstoc,
        p->total_octave_lines,
        p->eighth_octave_lines,
        dBoffset);
    }
    v6 = n;
  }
}

// FUNC: seed_chase
void __cdecl seed_chase(float *seeds, int linesper, int n)
{
  int v3; // eax
  float *v4; // edi
  void *v5; // esp
  int v6; // eax
  _BYTE *v7; // esi
  void *v8; // esp
  int v9; // edx
  int v10; // ecx
  float *v11; // ebx
  double v12; // st7
  float *v13; // edi
  _DWORD *v14; // esi
  bool v15; // c0
  int v16; // eax
  int *v17; // edx
  int v18; // esi
  int v19; // eax
  bool v20; // cc
  _BYTE v21[12]; // [esp+0h] [ebp-24h] BYREF
  int i; // [esp+Ch] [ebp-18h]
  float *v23; // [esp+10h] [ebp-14h]
  float v24; // [esp+14h] [ebp-10h]
  int v25; // [esp+18h] [ebp-Ch]
  float *v26; // [esp+1Ch] [ebp-8h]
  _BYTE *v27; // [esp+20h] [ebp-4h]

  v3 = 4 * n + 3;
  LOBYTE(v3) = v3 & 0xFC;
  v4 = seeds;
  v5 = alloca(v3);
  v6 = 4 * n + 3;
  LOBYTE(v6) = (4 * n + 3) & 0xFC;
  v7 = v21;
  v27 = v21;
  v8 = alloca(v6);
  v9 = 0;
  v10 = 0;
  v11 = (float *)v21;
  v23 = (float *)v21;
  for ( i = 0; v9 < n; ++v10 )
  {
    if ( v10 >= 2 )
    {
      v12 = v4[v9];
      v24 = v4[v9];
      v26 = &v11[v10 - 1];
      if ( v12 < *v26 )
      {
LABEL_12:
        *(_DWORD *)&v7[4 * v10] = v9;
      }
      else
      {
        v13 = v26;
        v14 = &v7[4 * v10 - 8];
        v25 = (char *)v11 - v27;
        while ( v9 < linesper + v14[1]
             && v10 > 1
             && *v26 <= (double)*(float *)((char *)v14 + v25)
             && v9 < linesper + *v14 )
        {
          v15 = v24 < (double)*--v13;
          --v10;
          --v14;
          v26 = v13;
          if ( v15 )
          {
            v4 = seeds;
            v11 = v23;
            v7 = v27;
            goto LABEL_12;
          }
        }
        v16 = (int)v27;
        v4 = seeds;
        v11 = v23;
        *(_DWORD *)&v27[4 * v10] = v9;
        v7 = (_BYTE *)v16;
      }
    }
    else
    {
      *(_DWORD *)&v7[4 * v10] = v9;
    }
    v11[v10] = v4[v9++];
  }
  v26 = 0;
  if ( v10 > 0 )
  {
    v17 = (int *)(v7 + 4);
    v23 = (float *)(v7 + 4);
    v25 = (char *)v11 - v7;
    do
    {
      if ( (int)v26 >= v10 - 1 || *(float *)((char *)v17 + v25) <= (double)*v11 )
        v18 = *(v17 - 1) + linesper + 1;
      else
        v18 = *v17;
      if ( v18 > n )
        v18 = n;
      v19 = i;
      if ( i < v18 )
      {
        do
          v4[v19++] = *v11;
        while ( v19 < v18 );
        v17 = (int *)v23;
        i = v19;
      }
      ++v17;
      ++v11;
      v20 = (int)v26 + 1 < v10;
      v26 = (float *)((char *)v26 + 1);
      v23 = (float *)v17;
    }
    while ( v20 );
  }
}

// FUNC: max_seeds
void __usercall max_seeds(vorbis_look_psy *p@<edi>, float *seed, float *flr)
{
  int eighth_octave_lines; // ebx
  int v5; // esi
  int v6; // edx
  int v7; // ecx
  vorbis_info_psy *vi; // ebx
  int i; // ebx
  double v10; // st7
  int j; // ebx
  float seeda; // [esp+10h] [ebp+4h]
  float seedb; // [esp+10h] [ebp+4h]

  eighth_octave_lines = p->eighth_octave_lines;
  v5 = 0;
  seed_chase(seed, eighth_octave_lines, p->total_octave_lines);
  v6 = *p->octave - (eighth_octave_lines >> 1) - p->firstoc;
  if ( p->n > 1 )
  {
    do
    {
      seeda = seed[v6];
      v7 = ((p->octave[v5] + p->octave[v5 + 1]) >> 1) - p->firstoc;
      vi = p->vi;
      if ( seeda > (double)vi->tone_abs_limit )
        seeda = vi->tone_abs_limit;
      for ( i = v6 + 1; i <= v7; ++i )
      {
        v10 = seed[++v6];
        if ( v10 > -9999.0 && seed[v6] < (double)seeda || seeda == -9999.0 )
          seeda = seed[v6];
      }
      for ( j = p->firstoc + v6; v5 < p->n; ++v5 )
      {
        if ( p->octave[v5] > j )
          break;
        if ( flr[v5] < (double)seeda )
          flr[v5] = seeda;
      }
    }
    while ( v5 + 1 < p->n );
  }
  for ( seedb = seed[p->total_octave_lines - 1]; v5 < p->n; ++v5 )
  {
    if ( flr[v5] < (double)seedb )
      flr[v5] = seedb;
  }
}

// FUNC: bark_noise_hybridmp
void __cdecl bark_noise_hybridmp(int n, char *b, const float *f, float *noise, const float offset, const int fixed)
{
  int v6; // eax
  void *v7; // esp
  int v8; // eax
  void *v9; // esp
  int v10; // eax
  void *v11; // esp
  int v12; // eax
  void *v13; // esp
  int v14; // eax
  void *v15; // esp
  double v16; // st7
  double v17; // st7
  int v18; // ecx
  double v19; // st6
  double v20; // st6
  double v21; // st7
  double v22; // st6
  double v23; // st6
  float *v24; // eax
  double v25; // st7
  double v26; // st7
  int v27; // edx
  double v28; // st6
  double v29; // st4
  double v30; // st7
  double v31; // st6
  double v32; // st5
  double v33; // st3
  float v34; // eax
  double v35; // st5
  double v36; // st7
  int v37; // eax
  double v38; // st7
  double v39; // st6
  float v40; // edx
  float v41; // eax
  double v42; // st6
  int v43; // eax
  bool v44; // zf
  const int *v45; // edx
  double v46; // st6
  int v47; // eax
  double v48; // st4
  int v49; // eax
  double v50; // st7
  int v51; // edx
  int v52; // edx
  double v53; // st6
  double v54; // st5
  double v55; // st3
  double v56; // st2
  double v57; // st6
  float v58; // eax
  int v59; // eax
  int v60; // eax
  double v61; // st6
  double v62; // st3
  double v63; // st2
  double v64; // st6
  float v65; // eax
  int v66; // edx
  int v67; // edx
  double v68; // st6
  double v69; // st5
  double v70; // st7
  int v71; // edx
  int v72; // eax
  double v73; // st6
  double v74; // st5
  double v75; // st3
  double v76; // st2
  int v77; // edx
  double v78; // st6
  double v79; // st5
  bool v80; // sf
  int v81; // edx
  int v82; // eax
  double v83; // st6
  double v84; // st3
  double v85; // st2
  int v86; // edx
  double v87; // st5
  bool v88; // cc
  int v89; // ecx
  double v90; // st6
  double v91; // st5
  _DWORD v92[2]; // [esp+0h] [ebp-80h] BYREF
  int v93; // [esp+8h] [ebp-78h] BYREF
  const int *v94; // [esp+Ch] [ebp-74h] BYREF
  int v95; // [esp+10h] [ebp-70h] BYREF
  int v96; // [esp+14h] [ebp-6Ch]
  int v97; // [esp+18h] [ebp-68h]
  int v98; // [esp+1Ch] [ebp-64h]
  int v99; // [esp+20h] [ebp-60h]
  int v100; // [esp+24h] [ebp-5Ch]
  int v101; // [esp+28h] [ebp-58h]
  int v102; // [esp+2Ch] [ebp-54h]
  unsigned int v103; // [esp+30h] [ebp-50h]
  float *v104; // [esp+34h] [ebp-4Ch]
  int v105; // [esp+38h] [ebp-48h]
  unsigned int v106; // [esp+3Ch] [ebp-44h]
  int v107; // [esp+40h] [ebp-40h]
  int v108; // [esp+44h] [ebp-3Ch]
  float *v109; // [esp+48h] [ebp-38h]
  float *v110; // [esp+4Ch] [ebp-34h]
  char *v111; // [esp+50h] [ebp-30h]
  float v112; // [esp+54h] [ebp-2Ch]
  float *v113; // [esp+58h] [ebp-28h]
  float v114; // [esp+5Ch] [ebp-24h]
  float v115; // [esp+60h] [ebp-20h]
  float v116; // [esp+64h] [ebp-1Ch]
  float v117; // [esp+68h] [ebp-18h]
  float v118; // [esp+6Ch] [ebp-14h]
  float v119; // [esp+70h] [ebp-10h]
  int v120; // [esp+74h] [ebp-Ch]
  float v121; // [esp+78h] [ebp-8h]
  float v122; // [esp+7Ch] [ebp-4h]
  int v123; // [esp+8Ch] [ebp+Ch]
  int v124; // [esp+90h] [ebp+10h]
  int v125; // [esp+90h] [ebp+10h]
  int v126; // [esp+90h] [ebp+10h]
  int v127; // [esp+90h] [ebp+10h]
  int v128; // [esp+90h] [ebp+10h]

  v6 = 4 * n + 3;
  LOBYTE(v6) = v6 & 0xFC;
  v7 = alloca(v6);
  v8 = 4 * n + 3;
  LOBYTE(v8) = (4 * n + 3) & 0xFC;
  v9 = alloca(v8);
  v10 = 4 * n + 3;
  LOBYTE(v10) = (4 * n + 3) & 0xFC;
  v11 = alloca(v10);
  v12 = 4 * n + 3;
  LOBYTE(v12) = v12 & 0xFC;
  v13 = alloca(v12);
  v14 = 4 * n + 3;
  LOBYTE(v14) = v14 & 0xFC;
  v104 = (float *)v92;
  v15 = alloca(v14);
  v16 = offset + *f;
  v111 = (char *)v92;
  v114 = 0.0;
  v121 = v16;
  v117 = 0.0;
  if ( v16 < 1.0 )
    v121 = 1.0;
  v120 = 1;
  v122 = 1.0;
  v17 = v121 * v121 * 0.5;
  v116 = v17;
  *(float *)&v103 = v17;
  v119 = *(float *)&v103;
  v18 = (int)v104;
  v118 = v116 * v121;
  *v104 = v118;
  v92[0] = 0;
  if ( n - 1 >= 4 )
  {
    v110 = (float *)(v18 + 4);
    v109 = (float *)&v95;
    v112 = COERCE_FLOAT(&v94);
    v113 = (float *)&v93;
    v108 = (char *)f - (char *)v92;
    v107 = 0;
    v106 = 0;
    v105 = v18 - (_DWORD)v92;
    v104 = 0;
    v100 = (char *)f - (char *)v92;
    v99 = 0;
    v98 = v18 - (_DWORD)v92;
    v97 = 0;
    v96 = (char *)f - (char *)v92;
    v95 = v18 - (_DWORD)v92;
    *(float *)&v94 = 0.0;
    v102 = (int)f - v18;
    v101 = (int)v92 - v18;
    v103 = ((unsigned int)(n - 5) >> 2) + 1;
    v120 = 4 * v103 + 1;
    do
    {
      v19 = offset + *(float *)((char *)v110 + v102);
      v121 = v19;
      if ( v19 < 1.0 )
        v121 = 1.0;
      v20 = v121 * v121;
      v116 = v20;
      v115 = v20 + v17;
      *(v113 - 1) = v115;
      v21 = v122 * v116;
      v119 = v119 + v21;
      v22 = v122 * v122;
      *(float *)(LODWORD(v112) - 8) = v119;
      v117 = v22 * v116 + v117;
      v23 = v116 * v121;
      *(v109 - 3) = v117;
      v24 = v110;
      v118 = v23 + v118;
      v25 = v21 * v121;
      *v110 = v118;
      v26 = v25 + v114;
      *(float *)((char *)v24 + v101) = v26;
      v27 = (int)v113;
      v122 = v122 + 1.0;
      v28 = offset + *(float *)((char *)v113 + v108);
      if ( v28 < 1.0 )
        v28 = 1.0;
      v115 = v115 + v28 * v28;
      v29 = v122 * (v28 * v28);
      *v113 = v115;
      v116 = v29;
      v119 = v29 + v119;
      v117 = v122 * v122 * (v28 * v28) + v117;
      v118 = v28 * v28 * v28 + v118;
      v30 = v26 + v116 * v28;
      *(float *)(v107 + v27) = v119;
      *(float *)(v106 + v27) = v117;
      *(float *)(v105 + v27) = v118;
      *(float *)((char *)v104 + v27) = v30;
      v31 = v122 + 1.0;
      v32 = offset + *(float *)(v100 + LODWORD(v112));
      if ( v32 < 1.0 )
        v32 = 1.0;
      v115 = v115 + v32 * v32;
      v33 = v31 * (v32 * v32);
      v113[1] = v115;
      v34 = v112;
      v116 = v33;
      v119 = v33 + v119;
      *(float *)LODWORD(v112) = v119;
      v117 = v31 * v31 * (v32 * v32) + v117;
      v118 = v32 * v32 * v32 + v118;
      v35 = v32 * v116 + v30;
      v114 = v35;
      *(float *)(v99 + LODWORD(v34)) = v117;
      *(float *)(v98 + LODWORD(v34)) = v118;
      *(float *)(v97 + LODWORD(v34)) = v35;
      v122 = v31 + 1.0;
      v36 = offset + *(float *)((char *)v109 + v96);
      v121 = v36;
      if ( v36 < 1.0 )
        v121 = 1.0;
      v37 = (int)v113;
      v38 = v121 * v121;
      v113 += 4;
      v110 += 4;
      v116 = v38;
      v17 = v38 + v115;
      v39 = v122 * v116;
      v119 = v119 + v39;
      v40 = v119;
      v117 = v122 * v122 * v116 + v117;
      v118 = v116 * v121 + v118;
      v114 = v39 * v121 + v114;
      *(float *)(v37 + 8) = v17;
      v41 = v112;
      v42 = v118;
      LODWORD(v112) += 16;
      *(float *)(LODWORD(v41) + 4) = v40;
      v43 = (int)v109;
      *v109 = v117;
      *(float *)(v95 + v43) = v42;
      v43 += 16;
      v44 = v103-- == 1;
      *(float *)((char *)v94 + v43 - 16) = v114;
      v109 = (float *)v43;
      v122 = v122 + 1.0;
    }
    while ( !v44 );
  }
  if ( v120 < n )
  {
    v94 = &v92[v120];
    v108 = (char *)f - (char *)v92;
    v107 = 0;
    v106 = 0;
    v105 = v18 - (_DWORD)v92;
    v104 = (float *)(v111 - (char *)v92);
    v45 = v94;
    v124 = n - v120;
    do
    {
      v46 = offset + *(float *)((char *)v45 + v108);
      if ( v46 < 1.0 )
        v46 = 1.0;
      v47 = v107;
      ++v45;
      v44 = v124-- == 1;
      v17 = v17 + v46 * v46;
      v48 = v122 * (v46 * v46);
      v116 = v48;
      v119 = v48 + v119;
      v117 = v122 * v122 * (v46 * v46) + v117;
      v118 = v46 * v46 * v46 + v118;
      v114 = v116 * v46 + v114;
      *((float *)v45 - 1) = v17;
      *(float *)((char *)v45 + v47 - 4) = v119;
      *(float *)((char *)v45 + v106 - 4) = v117;
      *(float *)((char *)v45 + v105 - 4) = v118;
      *(float *)((char *)v45 + (_DWORD)v104 - 4) = v114;
      v122 = v122 + 1.0;
    }
    while ( !v44 );
  }
  v49 = *(_DWORD *)b;
  v50 = 0.0;
  v51 = *(int *)b >> 16;
  v120 = 0;
  if ( v51 < 0 )
  {
    v94 = (const int *)v49;
    v103 = (unsigned int)b;
    v104 = (float *)((char *)noise - b);
    do
    {
      v52 = -1 * v51;
      v53 = *(float *)&v92[(unsigned __int16)v49] + *(float *)&v92[v52];
      v54 = *(float *)&v92[(unsigned __int16)v49] - *(float *)&v92[v52];
      v55 = *(float *)(v18 + 4 * (unsigned __int16)v49) + *(float *)(v52 * 4 + v18);
      v56 = *(float *)&v111[4 * (unsigned __int16)v49] - *(float *)&v111[v52 * 4];
      v117 = v55 * v53 - v56 * v54;
      v116 = v56 * v53 - v55 * v54;
      v112 = v53 * v53 - v54 * v54;
      v57 = (v116 * v50 + v117) / v112;
      if ( v57 < 0.0 )
        v57 = 0.0;
      v58 = *(float *)&v103;
      ++v120;
      *(float *)((char *)v104 + v103) = v57 - offset;
      v103 = LODWORD(v58) + 4;
      v49 = *(_DWORD *)(LODWORD(v58) + 4);
      v50 = v50 + 1.0;
      v51 = v49 >> 16;
    }
    while ( v49 >> 16 < 0 );
  }
  v94 = (const int *)&b[4 * v120];
  v59 = (unsigned __int16)*v94;
  v125 = *v94 >> 16;
  v95 = v59;
  if ( v59 < n )
  {
    v103 = (unsigned int)v94;
    v104 = (float *)((char *)noise - b);
    v60 = v95;
    do
    {
      v61 = *(float *)&v92[v60] - *(float *)&v92[v125];
      v62 = *(float *)(v18 + 4 * v60) - *(float *)(v18 + 4 * v125);
      v63 = *(float *)&v111[4 * v60] - *(float *)&v111[4 * v125];
      v117 = v62 * v61 - v63 * v61;
      v116 = v63 * v61 - v62 * v61;
      v112 = v61 * v61 - v61 * v61;
      v64 = (v116 * v50 + v117) / v112;
      if ( v64 < 0.0 )
        v64 = 0.0;
      v65 = *(float *)&v103;
      ++v120;
      *(float *)((char *)v104 + v103) = v64 - offset;
      v103 = LODWORD(v65) + 4;
      v60 = *(_DWORD *)(LODWORD(v65) + 4);
      v50 = v50 + 1.0;
      v66 = v60 >> 16;
      v60 = (unsigned __int16)v60;
      v125 = v66;
    }
    while ( (unsigned __int16)v60 < n );
  }
  v67 = v120;
  if ( v120 < n )
  {
    v68 = 1.0 / v112;
    do
    {
      v69 = (v116 * v50 + v117) * v68;
      if ( v69 < 0.0 )
        v69 = 0.0;
      noise[v67++] = v69 - offset;
      v50 = v50 + 1.0;
    }
    while ( v67 < n );
  }
  if ( fixed > 0 )
  {
    v70 = 0.0;
    v123 = fixed / 2;
    v120 = 0;
    v126 = fixed / 2 - fixed;
    if ( v126 >= 0 )
    {
      v78 = v112;
    }
    else
    {
      v94 = (const int *)(4 * v123);
      v105 = v123 - fixed;
      v104 = (float *)(4 * v123);
      v127 = -4 * v126;
      v71 = v127;
      v103 = 4 * (fixed - v123);
      v72 = 4 * v123;
      do
      {
        v73 = *(float *)((char *)v92 + v71) + *(float *)((char *)v92 + v72);
        v74 = *(float *)((char *)v92 + v72) - *(float *)((char *)v92 + v71);
        v75 = *(float *)(v71 + v18) + *(float *)(v72 + v18);
        v76 = *(float *)&v111[v72] - *(float *)&v111[v127];
        v77 = v120;
        v117 = v75 * v73 - v76 * v74;
        v116 = v76 * v73 - v75 * v74;
        v78 = v73 * v73 - v74 * v74;
        v79 = (v116 * v70 + v117) / v78 - offset;
        if ( v79 < noise[v120] )
          noise[v120] = v79;
        v72 = (int)++v104;
        v70 = v70 + 1.0;
        v120 = v77 + 1;
        v71 = v103 - 4;
        v80 = ++v105 < 0;
        v103 = v71;
        v127 = v71;
      }
      while ( v80 );
    }
    v81 = n;
    v94 = (const int *)(v123 + v120);
    v82 = v123 + v120;
    if ( v123 + v120 < n )
    {
      v105 = v123 + v120;
      v104 = (float *)(4 * (v123 + v120 - fixed));
      v103 = 4 * v82;
      v106 = 4 * v82;
      v128 = 4 * (v120 + v123 - fixed);
      do
      {
        v83 = *(float *)((char *)v92 + v106) - *(float *)((char *)v92 + (_DWORD)v104);
        v84 = *(float *)(v106 + v18) - *(float *)((char *)v104 + v18);
        v85 = *(float *)&v111[v106] - *(float *)&v111[(_DWORD)v104];
        v86 = v120;
        v117 = v84 * v83 - v85 * v83;
        v116 = v85 * v83 - v84 * v83;
        v78 = v83 * v83 - v83 * v83;
        v87 = (v116 * v70 + v117) / v78 - offset;
        if ( v87 < noise[v120] )
          noise[v120] = v87;
        v128 += 4;
        v70 = v70 + 1.0;
        v120 = v86 + 1;
        v88 = v105 + 1 < n;
        v103 += 4;
        v106 = v103;
        ++v105;
        v104 = (float *)v128;
      }
      while ( v88 );
      v81 = n;
    }
    v89 = v120;
    if ( v120 < v81 )
    {
      v90 = 1.0 / v78;
      do
      {
        v91 = (v116 * v70 + v117) * v90 - offset;
        if ( v91 < noise[v89] )
          noise[v89] = v91;
        ++v89;
        v70 = v70 + 1.0;
      }
      while ( v89 < v81 );
    }
  }
}

// FUNC: __vp_remove_floor
void __cdecl _vp_remove_floor(vorbis_look_psy *p, float *mdct, int *codedflr, float *residue, int sliding_lowpass)
{
  int n; // eax
  int v6; // esi
  bool v7; // cc
  float *v8; // ecx
  int v9; // edx
  float *v10; // esi
  float *v11; // eax
  double v12; // st7
  double v13; // st7
  int v14; // esi
  float *v15; // eax
  int v16; // ebx
  vorbis_look_psy *pa; // [esp+1Ch] [ebp+4h]

  n = p->n;
  v6 = sliding_lowpass;
  v7 = sliding_lowpass <= p->n;
  pa = (vorbis_look_psy *)p->n;
  if ( !v7 )
  {
    v6 = n;
    sliding_lowpass = n;
  }
  v8 = residue;
  v9 = 0;
  if ( v6 >= 4 )
  {
    v10 = residue + 2;
    v11 = mdct + 1;
    do
    {
      v12 = FLOOR1_fromdB_INV_LOOKUP[codedflr[v9]];
      v9 += 4;
      v13 = v12 * *(v11 - 1);
      v11 += 4;
      v10 += 4;
      *(v10 - 6) = v13;
      *(float *)((char *)v11 + (char *)residue - (char *)mdct - 16) = FLOOR1_fromdB_INV_LOOKUP[*(_DWORD *)((char *)v11 + (char *)codedflr - (char *)mdct - 16)]
                                                                    * *(v11 - 4);
      *(v10 - 4) = FLOOR1_fromdB_INV_LOOKUP[*(_DWORD *)((char *)v10 + (char *)codedflr - (char *)residue - 16)]
                 * *(v11 - 3);
      *(v10 - 3) = FLOOR1_fromdB_INV_LOOKUP[codedflr[v9 - 1]] * *(v11 - 2);
    }
    while ( v9 < sliding_lowpass - 3 );
    v8 = residue;
    v6 = sliding_lowpass;
    n = (int)pa;
  }
  if ( v9 < v6 )
  {
    v14 = v6 - v9;
    v15 = &mdct[v9];
    v9 += v14;
    do
    {
      v16 = *(_DWORD *)((char *)v15++ + (char *)codedflr - (char *)mdct);
      --v14;
      *(float *)((char *)v15 + (char *)v8 - (char *)mdct - 4) = FLOOR1_fromdB_INV_LOOKUP[v16] * *(v15 - 1);
    }
    while ( v14 );
    n = (int)pa;
  }
  if ( v9 < n )
    memset(&v8[v9], 0, 4 * (n - v9));
}

// FUNC: __vp_noisemask
void __cdecl _vp_noisemask(vorbis_look_psy *p, float *logmdct, float *logmask)
{
  int v3; // edi
  int v4; // eax
  void *v5; // esp
  float *v6; // ebx
  int *bark; // edx
  int v8; // edx
  float *v9; // ecx
  float *v10; // eax
  int v11; // ebx
  double v12; // st7
  float *v13; // eax
  int v14; // ecx
  double v15; // st7
  int v16; // eax
  float *v17; // eax
  unsigned int v18; // edx
  int v19; // ebx
  float *v20; // ecx
  double v21; // st7
  float *v22; // edx
  int v23; // esi
  int v24; // ecx
  float *v25; // eax
  double v26; // st7
  int v27; // edx
  int v28; // eax
  int v29; // [esp+0h] [ebp-24h] BYREF
  __int64 v30; // [esp+Ch] [ebp-18h]
  int v31; // [esp+14h] [ebp-10h]
  int v32; // [esp+18h] [ebp-Ch]
  int v33; // [esp+1Ch] [ebp-8h]
  float *v34; // [esp+20h] [ebp-4h]

  v4 = 4 * p->n + 3;
  LOBYTE(v4) = v4 & 0xFC;
  HIDWORD(v30) = p->n;
  v3 = HIDWORD(v30);
  v5 = alloca(v4);
  v6 = logmask;
  bark = p->bark;
  v34 = (float *)&v29;
  bark_noise_hybridmp(SHIDWORD(v30), (char *)bark, logmdct, logmask, 140.0, -1);
  v8 = 0;
  if ( v3 >= 4 )
  {
    v33 = (char *)logmdct - (char *)logmask;
    v32 = (char *)v34 - (char *)logmask;
    v9 = v34 + 2;
    v10 = logmask + 1;
    v31 = (char *)logmdct - (char *)v34;
    v3 = HIDWORD(v30);
    do
    {
      v11 = v33;
      v12 = logmdct[v8] - *(v10 - 1);
      v8 += 4;
      v10 += 4;
      v9 += 4;
      *(v9 - 6) = v12;
      *(float *)((char *)v10 + v32 - 16) = *(float *)((char *)v10 + v11 - 16) - *(v10 - 4);
      *(v9 - 4) = *(float *)((char *)v9 + v31 - 16) - *(v10 - 3);
      *(v9 - 3) = logmdct[v8 - 1] - *(v10 - 2);
    }
    while ( v8 < v3 - 3 );
    v6 = logmask;
  }
  if ( v8 < v3 )
  {
    v33 = (char *)logmdct - (char *)v6;
    v32 = (char *)v34 - (char *)v6;
    v13 = &v6[v8];
    v14 = v3 - v8;
    do
    {
      v15 = *(float *)((char *)v13 + v33) - *v13;
      ++v13;
      --v14;
      *(float *)((char *)v13 + v32 - 4) = v15;
    }
    while ( v14 );
  }
  bark_noise_hybridmp(v3, (char *)p->bark, v34, v6, 0.0, p->vi->noisewindowfixed);
  v16 = 0;
  v32 = 0;
  if ( v3 >= 4 )
  {
    v17 = v34 + 1;
    v31 = (char *)logmdct - (char *)v34;
    v18 = ((unsigned int)(v3 - 4) >> 2) + 1;
    v32 = 4 * v18;
    v19 = (char *)logmdct - (char *)v34;
    v20 = logmdct + 3;
    do
    {
      v17 += 4;
      v21 = *(v20 - 3) - *(v17 - 5);
      v20 += 4;
      --v18;
      *(v17 - 5) = v21;
      *(v17 - 4) = *(float *)((char *)v17 + v19 - 16) - *(v17 - 4);
      *(v17 - 3) = *(v20 - 5) - *(v17 - 3);
      *(v17 - 2) = *(v20 - 4) - *(v17 - 2);
    }
    while ( v18 );
    v16 = v32;
    v6 = logmask;
  }
  v22 = v34;
  if ( v16 < v3 )
  {
    v23 = (char *)logmdct - (char *)v34;
    v24 = v3 - v32;
    v25 = &v34[v16];
    do
    {
      v26 = *(float *)((char *)v25++ + v23);
      --v24;
      *(v25 - 1) = v26 - *(v25 - 1);
    }
    while ( v24 );
  }
  if ( v3 > 0 )
  {
    v27 = (char *)v22 - (char *)v6;
    do
    {
      v30 = (__int64)(*v6 + 0.5);
      v28 = v30;
      if ( (int)v30 < 40 )
      {
        if ( (int)v30 < 0 )
          v28 = 0;
      }
      else
      {
        v28 = 39;
      }
      ++v6;
      --v3;
      *(v6 - 1) = p->vi->noisecompand[v28] + *(float *)((char *)v6 + v27 - 4);
    }
    while ( v3 );
  }
}

// FUNC: __vp_tonemask
void __cdecl _vp_tonemask(vorbis_look_psy *p, float *logfft, float *logmask, float global_specmax, float local_specmax)
{
  int total_octave_lines; // ebx
  int v7; // esi
  int v8; // eax
  void *v9; // esp
  double ath_maxatt; // st7
  float *v11; // ecx
  int v12; // eax
  vorbis_info_psy *vi; // edx
  int v14; // ebx
  bool v15; // cc
  float *v16; // esi
  int v17; // edx
  unsigned int v18; // ecx
  float *v19; // eax
  char *v20; // edx
  int v21; // esi
  char *v22; // edx
  int i; // eax
  double v24; // st6
  _DWORD v25[3]; // [esp+0h] [ebp-18h] BYREF
  int v26; // [esp+Ch] [ebp-Ch]
  float *seed; // [esp+10h] [ebp-8h]
  int n; // [esp+14h] [ebp-4h]
  int pa; // [esp+20h] [ebp+8h]

  total_octave_lines = p->total_octave_lines;
  v7 = p->n;
  v8 = 4 * total_octave_lines + 3;
  LOBYTE(v8) = v8 & 0xFC;
  n = p->n;
  v9 = alloca(v8);
  ath_maxatt = local_specmax + p->vi->ath_adjatt;
  v11 = (float *)v25;
  v12 = 0;
  seed = (float *)v25;
  if ( total_octave_lines > 0 )
  {
    do
      v25[v12++] = -971228160;
    while ( v12 < p->total_octave_lines );
  }
  vi = p->vi;
  if ( ath_maxatt < vi->ath_maxatt )
    ath_maxatt = vi->ath_maxatt;
  v14 = 0;
  v15 = v7 < 4;
  v16 = logmask;
  if ( !v15 )
  {
    v26 = 4 - (_DWORD)logmask;
    v17 = -8 - (_DWORD)logmask;
    v18 = ((unsigned int)(n - 4) >> 2) + 1;
    pa = 8;
    v19 = logmask + 2;
    v14 = 4 * v18;
    while ( 1 )
    {
      v20 = (char *)v19 + v17;
      *(v19 - 2) = ath_maxatt + *(float *)&v20[(unsigned int)p->ath];
      v21 = pa;
      pa += 16;
      *(v19 - 1) = ath_maxatt + *(float *)&v20[(unsigned int)p->ath + 4];
      v22 = (char *)v19 + v26;
      v19 += 4;
      --v18;
      *(v19 - 4) = ath_maxatt + *(float *)((char *)p->ath + v21);
      *(v19 - 3) = ath_maxatt + *(float *)&v22[(unsigned int)p->ath];
      if ( !v18 )
        break;
      v17 = -8 - (_DWORD)logmask;
    }
    v16 = logmask;
    v11 = seed;
  }
  for ( i = n; v14 < i; v16[v14 - 1] = v24 )
    v24 = ath_maxatt + p->ath[v14++];
  seed_loop(p, (const float ***)p->tonecurves, logfft, v16, v11, global_specmax);
  max_seeds(p, seed, v16);
}

// FUNC: __vp_offset_and_mix
void __cdecl _vp_offset_and_mix(vorbis_look_psy *p, float *noise, float *tone, int offset_select, float *logmask)
{
  float *v6; // eax
  int v7; // ebp
  int v8; // esi
  float *v9; // edi
  float *v10; // edx
  double noisemaxsupp; // st7
  vorbis_info_psy *vi; // ebp
  double v13; // st7
  vorbis_info_psy *v14; // ebp
  vorbis_info_psy *v15; // ebp
  double v16; // st7
  vorbis_info_psy *v17; // ebp
  double v18; // st7
  float *v19; // edx
  vorbis_info_psy *v20; // ebx
  double v21; // st7
  float v22; // [esp+8h] [ebp-1Ch]
  float v23; // [esp+8h] [ebp-1Ch]
  float v24; // [esp+8h] [ebp-1Ch]
  float v25; // [esp+8h] [ebp-1Ch]
  int v26; // [esp+Ch] [ebp-18h]
  float v27; // [esp+Ch] [ebp-18h]
  int n; // [esp+20h] [ebp-4h]
  float pa; // [esp+28h] [ebp+4h]

  v6 = logmask;
  pa = p->vi->tone_masteratt[offset_select];
  v7 = p->n;
  v8 = 0;
  n = p->n;
  if ( p->n >= 4 )
  {
    v26 = -4 - (_DWORD)tone;
    v9 = logmask + 2;
    v10 = tone + 1;
    do
    {
      noisemaxsupp = *(float *)((char *)v10 + v26 + (unsigned int)p->noiseoffset[offset_select]) + noise[v8];
      vi = p->vi;
      if ( noisemaxsupp > vi->noisemaxsupp )
        noisemaxsupp = vi->noisemaxsupp;
      v22 = pa + *(v10 - 1);
      if ( noisemaxsupp <= v22 )
        noisemaxsupp = v22;
      *(v9 - 2) = noisemaxsupp;
      v13 = *(float *)((char *)v10 + v26 + (unsigned int)p->noiseoffset[offset_select] + 4)
          + *(float *)((char *)v10 + (char *)noise - (char *)tone);
      v14 = p->vi;
      if ( v13 > v14->noisemaxsupp )
        v13 = v14->noisemaxsupp;
      v23 = pa + *v10;
      if ( v13 <= v23 )
        v13 = v23;
      *(float *)((char *)v10 + (char *)logmask - (char *)tone) = v13;
      v15 = p->vi;
      v16 = *(float *)((char *)p->noiseoffset[offset_select] + 4 - (_DWORD)tone + (unsigned int)v10)
          + *(float *)((char *)v9 + (char *)noise - (char *)logmask);
      if ( v16 > v15->noisemaxsupp )
        v16 = v15->noisemaxsupp;
      v24 = pa + v10[1];
      if ( v16 <= v24 )
        v16 = v24;
      *v9 = v16;
      v17 = p->vi;
      v18 = *(float *)((char *)p->noiseoffset[offset_select] + 8 - (_DWORD)tone + (unsigned int)v10) + noise[v8 + 3];
      if ( v18 > v17->noisemaxsupp )
        v18 = v17->noisemaxsupp;
      v25 = pa + v10[2];
      if ( v18 <= v25 )
        v18 = v25;
      v7 = n;
      v9[1] = v18;
      v8 += 4;
      v10 += 4;
      v9 += 4;
    }
    while ( v8 < n - 3 );
    v6 = logmask;
  }
  if ( v8 < v7 )
  {
    v19 = &tone[v8];
    do
    {
      v20 = p->vi;
      v21 = p->noiseoffset[offset_select][v8] + *(float *)((char *)v19 + (char *)noise - (char *)tone);
      if ( v21 > v20->noisemaxsupp )
        v21 = v20->noisemaxsupp;
      v27 = pa + *v19;
      if ( v21 <= v27 )
        v21 = v27;
      *(float *)((char *)v19 + (char *)v6 - (char *)tone) = v21;
      ++v8;
      ++v19;
    }
    while ( v8 < v7 );
  }
}

// FUNC: couple_lossless
void __fastcall couple_lossless(float *qB, float *qA, float A, float B)
{
  long double v4; // st7
  long double v5; // st6
  int v6; // esi
  double v7; // st7
  double v8; // st7
  double v9; // st6
  long double v10; // st7

  v4 = fabs(*qA);
  v5 = fabs(*qB);
  v6 = (v4 > v5) - (v4 < v5);
  if ( !v6 )
    v6 = 2 * (fabs(B) < fabs(A)) - 1;
  if ( v6 == 1 )
  {
    if ( *qA <= 0.0 )
      v7 = *qB - *qA;
    else
      v7 = *qA - *qB;
    *qB = v7;
  }
  else
  {
    v8 = *qB;
    if ( v8 <= 0.0 )
      v9 = *qB - *qA;
    else
      v9 = *qA - *qB;
    *qB = v9;
    *qA = v8;
  }
  v10 = fabs(*qA);
  if ( v10 * 1.999899983406067 < *qB )
  {
    *qB = v10 * -2.0;
    *qA = -*qA;
  }
}

// FUNC: __vp_quantize_couple_memo
float **__cdecl _vp_quantize_couple_memo(
        vorbis_block *vb,
        vorbis_info_psy_global *g,
        int p,
        vorbis_info_mapping0 *vi,
        float **mdct)
{
  float **result; // eax
  int *coupling_ang; // edi
  float **v8; // esi
  float *v9; // ebp
  float *v10; // ebx
  char *v11; // eax
  int v12; // ecx
  float *v13; // edx
  int v14; // ebx
  long double v15; // st7
  int v16; // ecx
  int v17; // edx
  float *v18; // edx
  long double v19; // st7
  int v20; // ecx
  int v21; // edx
  bool v22; // cc
  int i; // [esp+8h] [ebp-10h]
  int *v24; // [esp+Ch] [ebp-Ch]
  float *mdctA; // [esp+10h] [ebp-8h]
  float **ret; // [esp+14h] [ebp-4h]
  vorbis_info_psy_global *ga; // [esp+20h] [ebp+8h]
  int limit; // [esp+24h] [ebp+Ch]

  limit = *(_DWORD *)p;
  result = (float **)_vorbis_block_alloc(vb, 4 * vi->coupling_steps);
  ret = result;
  ga = (vorbis_info_psy_global *)g->coupling_pointlimit[**(_DWORD **)(p + 4)][7];
  i = 0;
  if ( vi->coupling_steps > 0 )
  {
    coupling_ang = vi->coupling_ang;
    v8 = result;
    v24 = vi->coupling_ang;
    do
    {
      v9 = mdct[*(coupling_ang - 256)];
      v10 = mdct[*coupling_ang];
      mdctA = v10;
      v11 = _vorbis_block_alloc(vb, 4 * limit);
      v12 = 0;
      *v8 = (float *)v11;
      if ( (int)ga > 0 )
      {
        v13 = v9;
        v14 = (char *)v10 - (char *)v9;
        do
        {
          v15 = dipole_hypot(*v13, *(float *)((char *)v13 + v14));
          (*v8)[v16] = v15;
          v12 = v16 + 1;
          v13 = (float *)(v17 + 4);
        }
        while ( v12 < (int)ga );
        v10 = mdctA;
      }
      if ( v12 < limit )
      {
        v18 = &v9[v12];
        do
        {
          v19 = round_hypot(*v18, *(float *)((char *)v18 + (char *)v10 - (char *)v9));
          (*v8)[v20] = v19;
          v18 = (float *)(v21 + 4);
        }
        while ( v20 + 1 < limit );
        coupling_ang = v24;
      }
      ++coupling_ang;
      ++v8;
      v22 = ++i < vi->coupling_steps;
      v24 = coupling_ang;
    }
    while ( v22 );
    return ret;
  }
  return result;
}

// FUNC: __vp_quantize_couple_sort
int **__cdecl _vp_quantize_couple_sort(vorbis_block *vb, vorbis_look_psy *p, vorbis_info_mapping0 *vi, float **mags)
{
  int v4; // eax
  char *v5; // eax
  int normal_partition; // esi
  int v7; // eax
  void *v8; // esp
  int v9; // ebx
  bool v10; // cc
  float **v11; // edi
  char *v12; // eax
  int v13; // eax
  vorbis_look_psy *v14; // ecx
  int v15; // eax
  vorbis_look_psy *v16; // ecx
  _BYTE v18[12]; // [esp+0h] [ebp-20h] BYREF
  int **ret; // [esp+Ch] [ebp-14h]
  int j; // [esp+10h] [ebp-10h]
  float **work; // [esp+14h] [ebp-Ch]
  int n; // [esp+18h] [ebp-8h]
  int **v23; // [esp+1Ch] [ebp-4h]
  vorbis_look_psy *pa; // [esp+2Ch] [ebp+Ch]

  if ( !p->vi->normal_point_p )
    return 0;
  v4 = 4 * vi->coupling_steps;
  n = p->n;
  v5 = _vorbis_block_alloc(vb, v4);
  normal_partition = p->vi->normal_partition;
  ret = (int **)v5;
  v7 = 4 * normal_partition + 3;
  LOBYTE(v7) = v7 & 0xFC;
  v8 = alloca(v7);
  v9 = 0;
  v10 = vi->coupling_steps <= 0;
  v11 = (float **)v18;
  work = (float **)v18;
  if ( !v10 )
  {
    v23 = ret;
    do
    {
      v12 = _vorbis_block_alloc(vb, 4 * n);
      *v23 = (int *)v12;
      j = 0;
      if ( n > 0 )
      {
        pa = 0;
        do
        {
          v13 = 0;
          if ( normal_partition > 0 )
          {
            v14 = pa;
            do
            {
              v11[v13++] = (float *)((int)mags[v9] + (_DWORD)v14);
              v14 = (vorbis_look_psy *)((char *)v14 + 4);
            }
            while ( v13 < normal_partition );
          }
          qsort(v11, normal_partition, 4u, (int (__cdecl *)(const void *, const void *))apsort);
          v15 = 0;
          if ( normal_partition > 0 )
          {
            v16 = pa;
            do
            {
              *(int *)((char *)*v23 + (_DWORD)v16) = v11[v15] - mags[v9];
              v11 = work;
              ++v15;
              v16 = (vorbis_look_psy *)((char *)v16 + 4);
            }
            while ( v15 < normal_partition );
          }
          pa = (vorbis_look_psy *)((char *)pa + 4 * normal_partition);
          j += normal_partition;
        }
        while ( j < n );
      }
      ++v23;
      ++v9;
    }
    while ( v9 < vi->coupling_steps );
  }
  return ret;
}

// FUNC: __vp_noise_normalize_sort
void __cdecl _vp_noise_normalize_sort(vorbis_look_psy *p, float *magnitudes, int *sortedindex)
{
  vorbis_info_psy *vi; // ebx
  signed int normal_partition; // esi
  int v5; // eax
  void *v6; // esp
  int normal_start; // ebx
  int v8; // eax
  signed int v9; // eax
  float *v10; // ecx
  signed int v11; // eax
  int *v12; // ecx
  int v13; // edx
  _DWORD v14[3]; // [esp+0h] [ebp-10h] BYREF
  int start; // [esp+Ch] [ebp-4h]
  int n; // [esp+18h] [ebp+8h]

  vi = p->vi;
  normal_partition = vi->normal_partition;
  v5 = 4 * normal_partition + 3;
  LOBYTE(v5) = v5 & 0xFC;
  n = p->n;
  v6 = alloca(v5);
  normal_start = vi->normal_start;
  v8 = n;
  start = normal_start;
  if ( normal_start < n )
  {
    while ( 1 )
    {
      if ( normal_start + normal_partition > v8 )
        normal_partition = v8 - normal_start;
      v9 = 0;
      if ( normal_partition > 0 )
      {
        v10 = &magnitudes[normal_start];
        do
          v14[v9++] = v10++;
        while ( v9 < normal_partition );
      }
      qsort(v14, normal_partition, 4u, (int (__cdecl *)(const void *, const void *))apsort);
      v11 = 0;
      if ( normal_partition > 0 )
      {
        v12 = &sortedindex[normal_start - start];
        do
        {
          v13 = v14[v11++] - (_DWORD)magnitudes;
          *v12++ = v13 >> 2;
        }
        while ( v11 < normal_partition );
      }
      normal_start += normal_partition;
      if ( normal_start >= n )
        break;
      v8 = n;
    }
  }
}

// FUNC: __vp_noise_normalize
void __cdecl _vp_noise_normalize(vorbis_look_psy *p, float *in, float *out, int *sortedindex)
{
  vorbis_info_psy *v4; // ecx
  int v5; // edi
  int normal_start; // eax
  int v7; // ebx
  float *v8; // esi
  int v9; // ecx
  int v10; // esi
  float *v11; // edi
  long double v12; // st7
  int v13; // edx
  float *v14; // ecx
  unsigned int v15; // eax
  double v16; // st6
  double v17; // st6
  int v18; // edi
  int v19; // esi
  double v20; // st6
  int v21; // eax
  float *v22; // esi
  int v23; // edi
  int *v24; // ecx
  int v25; // eax
  int v26; // edx
  int partition; // [esp+14h] [ebp-24h]
  float acc; // [esp+18h] [ebp-20h]
  int start; // [esp+1Ch] [ebp-1Ch]
  int v30; // [esp+20h] [ebp-18h]
  int *v31; // [esp+24h] [ebp-14h]
  int v32; // [esp+28h] [ebp-10h]
  float *v33; // [esp+28h] [ebp-10h]
  int *v34; // [esp+2Ch] [ebp-Ch]
  int n; // [esp+30h] [ebp-8h]
  vorbis_info_psy *vi; // [esp+34h] [ebp-4h]

  v4 = p->vi;
  v5 = p->n;
  partition = v4->normal_partition;
  normal_start = v4->normal_start;
  v7 = 0;
  n = p->n;
  vi = v4;
  start = normal_start;
  if ( normal_start > p->n )
  {
    start = p->n;
    normal_start = p->n;
  }
  if ( !v4->normal_channel_p )
    goto LABEL_29;
  if ( normal_start > 0 )
  {
    v8 = out;
    v9 = (char *)in - (char *)out;
    v32 = normal_start;
    v7 = normal_start;
    while ( 1 )
    {
      *v8 = floor(*(float *)((char *)v8 + v9) + 0.5);
      ++v8;
      if ( !--v32 )
        break;
      v9 = (char *)in - (char *)out;
    }
    normal_start = start;
  }
  v10 = partition + v7;
  if ( partition + v7 > v5 )
    goto LABEL_29;
  v11 = in;
  v30 = partition + v7;
  v34 = &sortedindex[v7 - normal_start];
  v33 = &in[v7 + 2];
  while ( 2 )
  {
    v12 = 0.0;
    acc = 0.0;
    v13 = v7;
    if ( v10 - v7 >= 4 )
    {
      v14 = v33;
      v15 = ((unsigned int)(v10 - v7 - 4) >> 2) + 1;
      v13 = v7 + 4 * v15;
      do
      {
        v16 = *(v14 - 2);
        v14 += 4;
        --v15;
        v12 = v12 + v16 * v16 + *(v14 - 5) * *(v14 - 5) + *(v14 - 4) * *(v14 - 4) + *(v14 - 3) * *(v14 - 3);
      }
      while ( v15 );
      acc = v12;
    }
    if ( v13 < v10 )
    {
      do
      {
        v17 = v11[v13++];
        v12 = v12 + v17 * v17;
      }
      while ( v13 < v10 );
      acc = v12;
    }
    v18 = 0;
    if ( partition <= 0 )
      goto LABEL_27;
    v31 = v34;
    while ( 1 )
    {
      v19 = *v31;
      v20 = in[*v31];
      if ( v20 * v20 < 0.25 )
        break;
      out[v19] = floor(in[v19] + 0.5);
      v12 = acc - in[v19] * in[v19];
LABEL_25:
      ++v31;
      acc = v12;
      if ( ++v18 >= partition )
        goto LABEL_26;
    }
    if ( v12 >= vi->normal_thresh )
    {
      out[v19] = COERCE_FLOAT(COERCE_UNSIGNED_INT(in[v19]) & 0x80000000 | 0x3F800000);
      v12 = v12 - 1.0;
      goto LABEL_25;
    }
    if ( v18 < partition )
    {
      v24 = &sortedindex[v7 + v18 - start];
      v25 = partition - v18;
      do
      {
        v26 = *v24++;
        --v25;
        out[v26] = 0.0;
      }
      while ( v25 );
    }
LABEL_26:
    v10 = v30;
LABEL_27:
    v10 += partition;
    v7 += partition;
    v33 += partition;
    v34 += partition;
    v30 = v10;
    if ( v10 <= n )
    {
      v11 = in;
      continue;
    }
    break;
  }
  v5 = n;
LABEL_29:
  if ( v7 < v5 )
  {
    v21 = (char *)in - (char *)out;
    v22 = &out[v7];
    v23 = v5 - v7;
    while ( 1 )
    {
      *v22 = floor(*(float *)((char *)v22 + v21) + 0.5);
      ++v22;
      if ( !--v23 )
        break;
      v21 = (char *)in - (char *)out;
    }
  }
}

// FUNC: __vp_couple
void __cdecl _vp_couple(
        int blobno,
        vorbis_info_psy_global *g,
        vorbis_look_psy *p,
        vorbis_info_mapping0 *vi,
        float **res,
        float **mag_memo,
        int **mag_sort,
        int **ifloor,
        int *nonzero,
        int sliding_lowpass)
{
  int v10; // esi
  int *coupling_ang; // edi
  int v12; // eax
  int v13; // ecx
  float *v14; // edi
  vorbis_info_psy *v15; // eax
  int normal_partition; // ebx
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  float *v20; // esi
  int v21; // ecx
  int v22; // edx
  int v23; // ebx
  int v24; // edi
  int v25; // eax
  BOOL v26; // ecx
  unsigned int v27; // eax
  int v28; // esi
  bool v29; // cc
  int partition; // [esp+14h] [ebp-6Ch]
  float acc; // [esp+18h] [ebp-68h]
  int *v32; // [esp+1Ch] [ebp-64h]
  int **v33; // [esp+20h] [ebp-60h]
  int v34; // [esp+24h] [ebp-5Ch]
  int v35; // [esp+28h] [ebp-58h]
  int v36; // [esp+2Ch] [ebp-54h]
  int v37; // [esp+30h] [ebp-50h]
  int v38; // [esp+30h] [ebp-50h]
  float *qM; // [esp+34h] [ebp-4Ch]
  int v40; // [esp+38h] [ebp-48h]
  int n; // [esp+3Ch] [ebp-44h]
  float postpoint; // [esp+40h] [ebp-40h]
  float prepoint; // [esp+44h] [ebp-3Ch]
  float *rA; // [esp+48h] [ebp-38h]
  int k; // [esp+4Ch] [ebp-34h]
  int ka; // [esp+4Ch] [ebp-34h]
  int limit; // [esp+50h] [ebp-30h]
  int *j; // [esp+54h] [ebp-2Ch]
  int ja; // [esp+54h] [ebp-2Ch]
  int i; // [esp+58h] [ebp-28h]
  int *floorA; // [esp+5Ch] [ebp-24h]
  int *floorM; // [esp+60h] [ebp-20h]
  float *rM; // [esp+64h] [ebp-1Ch]
  float *qA; // [esp+68h] [ebp-18h]
  int v55; // [esp+70h] [ebp-10h]

  v10 = p->n;
  n = p->n;
  i = 0;
  if ( vi->coupling_steps > 0 )
  {
    coupling_ang = vi->coupling_ang;
    v33 = mag_sort;
    v32 = vi->coupling_ang;
    do
    {
      j = &nonzero[*(coupling_ang - 256)];
      if ( *j || nonzero[*coupling_ang] )
      {
        v12 = *(coupling_ang - 256);
        v13 = *coupling_ang;
        v14 = res[v13];
        qM = &res[v12][n];
        qA = &v14[n];
        floorM = ifloor[v12];
        floorA = ifloor[v13];
        prepoint = stereo_threshholds[g->coupling_prepointamp[blobno]];
        rM = res[v12];
        v15 = p->vi;
        postpoint = stereo_threshholds[g->coupling_postpointamp[blobno]];
        rA = v14;
        if ( v15->normal_point_p )
        {
          normal_partition = v15->normal_partition;
          partition = normal_partition;
        }
        else
        {
          partition = v10;
          normal_partition = v10;
        }
        v17 = g->coupling_pointlimit[v15->blockflag][blobno];
        *j = 1;
        limit = v17;
        nonzero[*v32] = 1;
        v10 = p->n;
        v18 = 0;
        ja = 0;
        if ( p->n > 0 )
        {
          v19 = 0;
          v40 = 0;
          do
          {
            acc = 0.0;
            if ( normal_partition > 0 )
            {
              v36 = v19;
              v20 = (float *)((char *)v14 + v19);
              v21 = (char *)floorA - (char *)floorM;
              v37 = v18;
              v34 = (char *)rM - (char *)v14;
              v22 = (char *)floorM - (char *)v14;
              v23 = (char *)qM - (char *)v14;
              v35 = (char *)qA - (char *)v14;
              v55 = (char *)floorM - (char *)v14;
              k = partition;
              while ( 1 )
              {
                if ( v37 >= sliding_lowpass )
                {
                  *(float *)((char *)v20 + v23) = 0.0;
                  *(float *)((char *)v20 + v35) = 0.0;
                }
                else if ( (v37 < limit || postpoint <= fabs(*(float *)((char *)v20 + v34)) || postpoint <= fabs(*v20))
                       && (prepoint <= fabs(*(float *)((char *)v20 + v34)) || prepoint <= fabs(*v20)) )
                {
                  couple_lossless(
                    (float *)((char *)v20 + v35),
                    (float *)((char *)v20 + v23),
                    *(float *)((char *)v20 + v34),
                    *v20);
                }
                else
                {
                  v24 = *(_DWORD *)((char *)v20 + v22 + v21);
                  v25 = *(_DWORD *)((char *)v20 + v22);
                  v26 = v25 > v24;
                  v27 = abs32(v25 - v24);
                  *(float *)((char *)v20 + v23) = (hypot_lookup[(31 - v27) & (((int)(31 - v27) < 0) - 1)] + 1.0)
                                                * FLOOR1_fromdB_INV_LOOKUP[(v26 ? 0 : v24) | *(_DWORD *)((_BYTE *)v20 + v22) & ~(v26 - 1)]
                                                * *(float *)(*(char **)((char *)v33 + (char *)mag_memo
                                                                                    - (char *)mag_sort)
                                                           + v36);
                  *(float *)((char *)v20 + v35) = 0.0;
                  v14 = rA;
                  if ( 0.0 == floor(*(float *)((char *)v20 + v23) + 0.5) )
                    acc = *(float *)((char *)v20 + v23) * *(float *)((char *)v20 + v23) + acc;
                }
                v36 += 4;
                ++v37;
                ++v20;
                if ( !--k )
                  break;
                v21 = (char *)floorA - (char *)floorM;
                v22 = v55;
              }
              normal_partition = partition;
            }
            if ( p->vi->normal_point_p )
            {
              ka = 0;
              if ( normal_partition > 0 )
              {
                v38 = v40;
                do
                {
                  if ( acc < p->vi->normal_thresh )
                    break;
                  v28 = *(int *)((char *)*v33 + v38);
                  if ( v28 < sliding_lowpass && v28 >= limit )
                  {
                    normal_partition = partition;
                    if ( 0.0 == floor(qM[v28] + 0.5) )
                    {
                      LODWORD(qM[v28]) = COERCE_UNSIGNED_INT(qM[v28]) & 0x80000000 | 0x3F800000;
                      acc = acc - 1.0;
                    }
                  }
                  v38 += 4;
                  ++ka;
                }
                while ( ka < normal_partition );
              }
            }
            v19 = 4 * normal_partition + v40;
            v10 = p->n;
            v18 = normal_partition + ja;
            v29 = normal_partition + ja < p->n;
            ja += normal_partition;
            v40 = v19;
          }
          while ( v29 );
        }
        coupling_ang = v32;
      }
      ++v33;
      ++coupling_ang;
      v29 = ++i < vi->coupling_steps;
      v32 = coupling_ang;
    }
    while ( v29 );
  }
}
