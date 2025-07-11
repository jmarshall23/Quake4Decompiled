
// FUNC: _vorbis_lsp_to_curve
void __cdecl vorbis_lsp_to_curve(float *curve, int *map, int n, int ln, float *lsp, int m, float amp, float ampoffset)
{
  int v8; // eax
  int v9; // esi
  int v10; // edx
  int v11; // edi
  int v12; // ecx
  float *v13; // eax
  double v14; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st6
  double v18; // st7
  double v19; // st6
  int v20; // eax
  double v21; // st7
  float *v22; // eax
  double wa; // [esp+1Ch] [ebp-40h]
  float w; // [esp+1Ch] [ebp-40h]
  long double wb; // [esp+1Ch] [ebp-40h]
  int qexp; // [esp+28h] [ebp-34h] BYREF
  float p; // [esp+2Ch] [ebp-30h]
  int v28; // [esp+30h] [ebp-2Ch]
  int v29; // [esp+34h] [ebp-28h]
  int v30; // [esp+38h] [ebp-24h]
  float wdel; // [esp+3Ch] [ebp-20h]
  float q; // [esp+40h] [ebp-1Ch]
  double v33; // [esp+44h] [ebp-18h]
  double v34; // [esp+4Ch] [ebp-10h]
  double v35; // [esp+54h] [ebp-8h]

  v8 = 0;
  for ( wdel = 3.1415927 / (double)ln;
        v8 < m;
        lsp[v8 - 1] = (COS_LOOKUP[(int)v33 + 1] - COS_LOOKUP[(int)v33]) * (v34 - (double)(int)v33)
                    + COS_LOOKUP[(int)v33] )
  {
    v34 = lsp[v8] * 40.74366592;
    v33 = v34 - 0.5;
    LODWORD(p) = (int)v33;
    ++v8;
  }
  v9 = 0;
  if ( n > 0 )
  {
    v10 = m >> 1;
    v30 = m >> 1;
    LODWORD(v33) = m & 1;
    while ( 1 )
    {
      v11 = map[v9];
      p = 0.70710677;
      q = 0.70710677;
      wa = (double)v11 * wdel * 40.74366592;
      v35 = wa - 0.5;
      v28 = (int)v35;
      v12 = v10;
      v13 = lsp;
      w = (COS_LOOKUP[(int)v35 + 1] - COS_LOOKUP[(int)v35]) * (wa - (double)(int)v35) + COS_LOOKUP[(int)v35];
      v14 = 0.70710677;
      v15 = 0.70710677;
      do
      {
        v16 = *v13;
        v13 += 2;
        --v12;
        v14 = v14 * (v16 - w);
        v15 = v15 * (*(v13 - 1) - w);
      }
      while ( v12 );
      p = v15;
      if ( LODWORD(v33) )
      {
        v17 = v14 * (*v13 - w);
        v18 = v17 * v17;
        v19 = 1.0 - w * w;
      }
      else
      {
        v18 = v14 * ((w + 1.0) * v14);
        v19 = 1.0 - w;
      }
      wb = frexp(v18 + v19 * p * p, &qexp) * 64.0 - 32.0;
      v35 = wb - 0.5;
      v29 = (int)v35;
      v35 = (((INVSQ_LOOKUP[(int)v35 + 1] - INVSQ_LOOKUP[(int)v35]) * (wb - (double)(int)v35) + INVSQ_LOOKUP[(int)v35])
           * INVSQ2EXP_LOOKUP[m + 32 + qexp]
           * amp
           - ampoffset)
          * -8.0
          - 0.5;
      LODWORD(v34) = (int)v35;
      v20 = (int)v35;
      if ( (int)v35 >= 0 )
        v21 = v20 < 1120 ? FROMdB2_LOOKUP_0[(int)v35 & 0x1F] * FROMdB_LOOKUP_0[v20 >> 5] : 0.0;
      else
        v21 = 1.0;
      v22 = &curve[v9];
      do
      {
        ++v22;
        ++v9;
        *(v22 - 1) = v21 * *(v22 - 1);
      }
      while ( *(_DWORD *)((char *)v22 + (char *)map - (char *)curve) == v11 );
      if ( v9 >= n )
        break;
      v10 = v30;
    }
  }
}
