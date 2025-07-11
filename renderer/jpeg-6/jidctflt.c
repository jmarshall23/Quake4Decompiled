
// FUNC: _jpeg_idct_float
void __usercall jpeg_idct_float(
        int a1@<ebx>,
        int a2@<ebp>,
        int a3@<edi>,
        jpeg_decompress_struct *cinfo,
        jpeg_component_info *compptr,
        __int16 *coef_block,
        unsigned __int8 **output_buf,
        unsigned int output_col)
{
  float *dct_table; // ecx
  unsigned __int8 *v10; // esi
  float *v11; // eax
  int v12; // ebp
  int v13; // ebp
  int v14; // ebp
  int v15; // ebp
  double v16; // st7
  double v17; // st7
  double v18; // st6
  double v19; // st5
  double v20; // st7
  double v21; // st6
  double v22; // st5
  double v23; // st4
  double v24; // st3
  double v25; // rt1
  int v26; // edi
  float *v27; // ecx
  double v28; // st7
  unsigned __int8 *v29; // edx
  double v30; // st6
  double v31; // st5
  double v32; // st7
  double v33; // st6
  double v34; // st5
  double v35; // st5
  int tmp12; // [esp+10h] [ebp-128h]
  float tmp12a; // [esp+10h] [ebp-128h]
  float z12; // [esp+14h] [ebp-124h]
  float z12a; // [esp+14h] [ebp-124h]
  float tmp2; // [esp+18h] [ebp-120h]
  float tmp2a; // [esp+18h] [ebp-120h]
  float tmp11; // [esp+1Ch] [ebp-11Ch]
  float tmp11a; // [esp+1Ch] [ebp-11Ch]
  float tmp11b; // [esp+1Ch] [ebp-11Ch]
  float tmp11c; // [esp+1Ch] [ebp-11Ch]
  float tmp11d; // [esp+1Ch] [ebp-11Ch]
  float z11; // [esp+20h] [ebp-118h]
  float z11a; // [esp+20h] [ebp-118h]
  float z11b; // [esp+20h] [ebp-118h]
  float z11c; // [esp+20h] [ebp-118h]
  float z13; // [esp+24h] [ebp-114h]
  float tmp7; // [esp+28h] [ebp-110h]
  float tmp7a; // [esp+28h] [ebp-110h]
  float tmp7b; // [esp+28h] [ebp-110h]
  float tmp13; // [esp+2Ch] [ebp-10Ch]
  float tmp13a; // [esp+2Ch] [ebp-10Ch]
  float tmp13b; // [esp+2Ch] [ebp-10Ch]
  float tmp3; // [esp+30h] [ebp-108h]
  float tmp3a; // [esp+30h] [ebp-108h]
  float tmp3b; // [esp+30h] [ebp-108h]
  float tmp10; // [esp+34h] [ebp-104h]
  float tmp10a; // [esp+34h] [ebp-104h]
  float workspace[64]; // [esp+38h] [ebp-100h] BYREF

  dct_table = (float *)compptr->dct_table;
  v10 = cinfo->sample_range_limit + 128;
  v11 = workspace;
  tmp12 = 8;
  do
  {
    LOWORD(a1) = coef_block[16];
    LOWORD(a2) = coef_block[8];
    LOWORD(a3) = coef_block[56];
    v12 = a1 | a2;
    LOWORD(a1) = coef_block[24];
    v13 = a1 | v12;
    LOWORD(a1) = coef_block[32];
    v14 = a1 | v13;
    LOWORD(a1) = coef_block[40];
    v15 = a1 | v14;
    LOWORD(a1) = coef_block[48];
    a2 = a3 | a1 | v15;
    if ( (_WORD)a2 )
    {
      a2 = coef_block[32];
      v17 = (double)*coef_block * *dct_table;
      v18 = (double)coef_block[16] * dct_table[16];
      a3 = (__int16)a3;
      v19 = (double)a2 * dct_table[32];
      tmp3 = (double)(__int16)a1 * dct_table[48];
      tmp10 = v19 + v17;
      tmp11 = v17 - v19;
      tmp13 = tmp3 + v18;
      v20 = (v18 - tmp3) * 1.4142135 - tmp13;
      v21 = tmp13 + tmp10;
      tmp3a = tmp10 - tmp13;
      tmp13a = v20 + tmp11;
      tmp2 = tmp11 - v20;
      a1 = coef_block[40];
      v22 = (double)coef_block[8] * dct_table[8];
      v23 = (double)coef_block[24] * dct_table[24];
      v24 = (double)a1 * dct_table[40];
      tmp7 = (double)(__int16)a3 * dct_table[56];
      z13 = v24 + v23;
      z11 = tmp7 + v22;
      v25 = v24 - v23;
      z12 = v22 - tmp7;
      tmp7a = z11 + z13;
      tmp11a = (z12 + v25) * 1.847759;
      tmp10a = tmp11a - v25 * 2.613126 - tmp7a;
      z11a = (z11 - z13) * 1.4142135 - tmp10a;
      tmp11b = z12 * 1.0823922 - tmp11a + z11a;
      *v11 = tmp7a + v21;
      v11[56] = v21 - tmp7a;
      v11[8] = tmp10a + tmp13a;
      v11[48] = tmp13a - tmp10a;
      v11[16] = z11a + tmp2;
      v11[40] = tmp2 - z11a;
      v11[32] = tmp11b + tmp3a;
      v11[24] = tmp3a - tmp11b;
    }
    else
    {
      a3 = *coef_block;
      v16 = (double)a3 * *dct_table;
      *v11 = v16;
      v11[8] = v16;
      v11[16] = v16;
      v11[24] = v16;
      v11[32] = v16;
      v11[40] = v16;
      v11[48] = v16;
      v11[56] = v16;
    }
    ++dct_table;
    ++coef_block;
    ++v11;
    --tmp12;
  }
  while ( tmp12 );
  v26 = 0;
  v27 = &workspace[2];
  do
  {
    v28 = v27[2] + *(v27 - 2);
    v29 = &output_buf[v26][output_col];
    v30 = *(v27 - 2) - v27[2];
    v31 = v27[4] + *v27;
    tmp12a = (*v27 - v27[4]) * 1.4142135 - v31;
    tmp2a = v31 + v28;
    tmp3b = v28 - v31;
    tmp13b = tmp12a + v30;
    v32 = v30 - tmp12a;
    v33 = v27[3] + v27[1];
    v34 = v27[3] - v27[1];
    z11b = v27[5] + *(v27 - 1);
    z12a = *(v27 - 1) - v27[5];
    tmp7b = z11b + v33;
    tmp11c = (z12a + v34) * 1.847759;
    v35 = tmp11c - v34 * 2.613126 - tmp7b;
    z11c = (z11b - v33) * 1.4142135 - v35;
    tmp11d = z12a * 1.0823922 - tmp11c + z11c;
    *v29 = v10[(((int)(tmp7b + tmp2a) + 4) >> 3) & 0x3FF];
    v29[7] = v10[(((int)(tmp2a - tmp7b) + 4) >> 3) & 0x3FF];
    v29[1] = v10[(((int)(tmp13b + v35) + 4) >> 3) & 0x3FF];
    v29[6] = v10[(((int)(tmp13b - v35) + 4) >> 3) & 0x3FF];
    v29[2] = v10[(((int)(z11c + v32) + 4) >> 3) & 0x3FF];
    v29[5] = v10[(((int)(v32 - z11c) + 4) >> 3) & 0x3FF];
    v29[4] = v10[(((int)(tmp11d + tmp3b) + 4) >> 3) & 0x3FF];
    ++v26;
    v27 += 8;
    v29[3] = v10[(((int)(tmp3b - tmp11d) + 4) >> 3) & 0x3FF];
  }
  while ( v26 < 8 );
}
