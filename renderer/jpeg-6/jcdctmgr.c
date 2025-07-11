
// FUNC: start_pass_fdctmgr
void __cdecl start_pass_fdctmgr(jpeg_common_struct *cinfo)
{
  jpeg_forward_dct *v2; // ebp
  int v3; // ebx
  JQUANT_TBL *v4; // esi
  int v5; // ecx
  double *v6; // edx
  const int *v7; // eax
  _DWORD *v8; // eax
  int v9; // ecx
  int ci; // [esp+8h] [ebp-8h]
  int v11; // [esp+Ch] [ebp-4h]
  int v12; // [esp+Ch] [ebp-4h]
  int *cinfoa; // [esp+14h] [ebp+4h]

  v2 = *(jpeg_forward_dct **)&cinfo[16].is_decompressor;
  ci = 0;
  if ( *(int *)&cinfo[2].is_decompressor > 0 )
  {
    cinfoa = (int *)&cinfo[3].err->reset_error_mgr;
    do
    {
      v3 = *cinfoa;
      if ( *cinfoa < 0 || v3 >= 4 || !*((_DWORD *)&cinfo[3].mem + v3) )
      {
        cinfo->err->msg_code = 49;
        cinfo->err->msg_parm.i[0] = v3;
        cinfo->err->error_exit(cinfo);
      }
      v4 = (JQUANT_TBL *)*((_DWORD *)&cinfo[3].mem + v3);
      if ( cinfo[8].global_state == 2 )
      {
        if ( !*((_DWORD *)&v2[4].start_pass + v3) )
          *((_DWORD *)&v2[4].start_pass + v3) = cinfo->mem->alloc_small(cinfo, 1, 256);
        v5 = *((_DWORD *)&v2[4].start_pass + v3);
        v6 = (double *)aanscalefactor;
        v7 = jpeg_zigzag_order;
        do
        {
          v11 = v4->quantval[*v7];
          v8 = v7 + 6;
          v9 = v5 + 24;
          *(float *)(v9 - 24) = 1.0 / ((double)v11 * *v6 * 8.0);
          *(float *)(v9 - 20) = 1.0 / ((double)v4->quantval[*(v8 - 5)] * *v6 * 11.09631876);
          *(float *)(v9 - 16) = 1.0 / ((double)v4->quantval[*(v8 - 4)] * *v6 * 10.45250372);
          *(float *)(v9 - 12) = 1.0 / ((double)v4->quantval[*(v8 - 3)] * *v6 * 9.407004816000001);
          *(float *)(v9 - 8) = 1.0 / ((double)v4->quantval[*(v8 - 2)] * *v6 * 8.0);
          *(float *)(v9 - 4) = 1.0 / ((double)v4->quantval[*(v8 - 1)] * *v6 * 6.285559664);
          v12 = v4->quantval[*v8];
          ++v6;
          v7 = v8 + 2;
          v5 = v9 + 8;
          *(float *)(v5 - 8) = 1.0 / ((double)v12 * *(v6 - 1) * 4.3295688);
          *(float *)(v5 - 4) = 1.0 / ((double)v4->quantval[*(v7 - 1)] * *(v6 - 1) * 2.207195032);
        }
        while ( (int)v6 < (int)&DOUBLE_2_207195032 );
      }
      else
      {
        cinfo->err->msg_code = 45;
        cinfo->err->error_exit(cinfo);
      }
      cinfoa += 21;
      ++ci;
    }
    while ( ci < *(_DWORD *)&cinfo[2].is_decompressor );
  }
}

// FUNC: forward_DCT_float
void __cdecl forward_DCT_float(
        jpeg_compress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **sample_data,
        __int16 (*coef_blocks)[64],
        unsigned int start_row,
        unsigned int start_col,
        unsigned int num_blocks)
{
  jpeg_forward_dct *fdct; // eax
  unsigned __int8 *v9; // eax
  unsigned __int8 *v10; // eax
  unsigned __int8 *v11; // eax
  int v12; // edx
  unsigned __int8 *v13; // eax
  int v14; // edx
  unsigned __int8 *v15; // eax
  int v16; // edx
  unsigned __int8 *v17; // eax
  int v18; // edx
  unsigned __int8 *v19; // eax
  int v20; // edx
  unsigned __int8 *v21; // eax
  int v22; // edx
  unsigned __int8 *v23; // eax
  int i; // edi
  unsigned __int64 v25; // rax
  int v26; // [esp+8h] [ebp-114h]
  int v27; // [esp+8h] [ebp-114h]
  int v28; // [esp+8h] [ebp-114h]
  int v29; // [esp+8h] [ebp-114h]
  int v30; // [esp+8h] [ebp-114h]
  int v31; // [esp+8h] [ebp-114h]
  int v32; // [esp+8h] [ebp-114h]
  int v33; // [esp+8h] [ebp-114h]
  int v34; // [esp+8h] [ebp-114h]
  int v35; // [esp+8h] [ebp-114h]
  int v36; // [esp+8h] [ebp-114h]
  int v37; // [esp+8h] [ebp-114h]
  int v38; // [esp+8h] [ebp-114h]
  unsigned int v40; // [esp+10h] [ebp-10Ch]
  void (__cdecl *do_dct)(float *); // [esp+14h] [ebp-108h]
  float *divisors; // [esp+18h] [ebp-104h]
  float workspace[64]; // [esp+1Ch] [ebp-100h] BYREF

  fdct = cinfo->fdct;
  do_dct = (void (__cdecl *)(float *))fdct[3].forward_DCT;
  divisors = (float *)*((_DWORD *)&fdct[4].start_pass + compptr->quant_tbl_no);
  if ( num_blocks )
  {
    v40 = num_blocks;
    do
    {
      v9 = sample_data[start_row];
      v26 = v9[start_col] - 128;
      v10 = &v9[start_col + 5];
      workspace[0] = (float)v26;
      v27 = *(v10 - 4) - 128;
      ++v10;
      workspace[1] = (float)v27;
      workspace[2] = (float)(*(v10 - 4) - 128);
      workspace[3] = (float)(*(v10 - 3) - 128);
      workspace[4] = (float)(*(v10 - 2) - 128);
      workspace[5] = (float)(*(v10 - 1) - 128);
      workspace[6] = (float)(*v10 - 128);
      v28 = v10[1] - 128;
      v11 = &sample_data[start_row + 1][start_col + 3];
      workspace[7] = (float)v28;
      v29 = *(v11 - 3) - 128;
      ++v11;
      workspace[8] = (float)v29;
      workspace[9] = (float)(*(v11 - 3) - 128);
      workspace[10] = (float)(*(v11 - 2) - 128);
      workspace[11] = (float)(*(v11 - 1) - 128);
      v30 = *v11++ - 128;
      workspace[12] = (float)v30;
      v31 = *v11++ - 128;
      workspace[13] = (float)v31;
      workspace[14] = (float)(*v11 - 128);
      v12 = v11[1];
      v13 = &sample_data[start_row + 2][start_col + 4];
      workspace[15] = (float)(v12 - 128);
      v32 = *(v13 - 4) - 128;
      v13 += 2;
      workspace[16] = (float)v32;
      workspace[17] = (float)(*(v13 - 5) - 128);
      workspace[18] = (float)(*(v13 - 4) - 128);
      workspace[19] = (float)(*(v13 - 3) - 128);
      workspace[20] = (float)(*(v13 - 2) - 128);
      workspace[21] = (float)(*(v13 - 1) - 128);
      workspace[22] = (float)(*v13 - 128);
      v14 = v13[1];
      v15 = &sample_data[start_row + 3][start_col + 2];
      workspace[23] = (float)(v14 - 128);
      workspace[24] = (float)(*(v15 - 2) - 128);
      workspace[25] = (float)(*(v15 - 1) - 128);
      workspace[26] = (float)(*v15 - 128);
      v33 = v15[1] - 128;
      v15 += 4;
      workspace[27] = (float)v33;
      workspace[28] = (float)(*(v15 - 2) - 128);
      workspace[29] = (float)(*(v15 - 1) - 128);
      workspace[30] = (float)(*v15 - 128);
      v16 = v15[1];
      v17 = &sample_data[start_row + 4][start_col + 4];
      workspace[31] = (float)(v16 - 128);
      v34 = *(v17 - 4) - 128;
      v17 += 2;
      workspace[32] = (float)v34;
      workspace[33] = (float)(*(v17 - 5) - 128);
      workspace[34] = (float)(*(v17 - 4) - 128);
      workspace[35] = (float)(*(v17 - 3) - 128);
      workspace[36] = (float)(*(v17 - 2) - 128);
      workspace[37] = (float)(*(v17 - 1) - 128);
      workspace[38] = (float)(*v17 - 128);
      v18 = v17[1];
      v19 = &sample_data[start_row + 5][start_col];
      workspace[39] = (float)(v18 - 128);
      v35 = *v19 - 128;
      v19 += 3;
      workspace[40] = (float)v35;
      v36 = *(v19 - 2) - 128;
      v19 += 3;
      workspace[41] = (float)v36;
      workspace[42] = (float)(*(v19 - 4) - 128);
      workspace[43] = (float)(*(v19 - 3) - 128);
      workspace[44] = (float)(*(v19 - 2) - 128);
      workspace[45] = (float)(*(v19 - 1) - 128);
      workspace[46] = (float)(*v19 - 128);
      v20 = v19[1];
      v21 = &sample_data[start_row + 6][start_col + 4];
      workspace[47] = (float)(v20 - 128);
      v37 = *(v21 - 4) - 128;
      ++v21;
      workspace[48] = (float)v37;
      workspace[49] = (float)(*(v21 - 4) - 128);
      workspace[50] = (float)(*(v21 - 3) - 128);
      workspace[51] = (float)(*(v21 - 2) - 128);
      workspace[52] = (float)(*(v21 - 1) - 128);
      workspace[53] = (float)(*v21 - 128);
      workspace[54] = (float)(v21[1] - 128);
      v22 = v21[2];
      v23 = &sample_data[start_row + 7][start_col + 4];
      workspace[55] = (float)(v22 - 128);
      v38 = *(v23 - 4) - 128;
      v23 += 2;
      workspace[56] = (float)v38;
      workspace[57] = (float)(*(v23 - 5) - 128);
      workspace[58] = (float)(*(v23 - 4) - 128);
      workspace[59] = (float)(*(v23 - 3) - 128);
      workspace[60] = (float)(*(v23 - 2) - 128);
      workspace[61] = (float)(*(v23 - 1) - 128);
      workspace[62] = (float)(*v23 - 128);
      workspace[63] = (float)(v23[1] - 128);
      do_dct(workspace);
      for ( i = 0; i < 64; (*coef_blocks)[i - 1] = v25 - 0x4000 )
      {
        v25 = (unsigned __int64)(divisors[i] * workspace[i] + 16384.5);
        ++i;
      }
      ++coef_blocks;
      start_col += 8;
      --v40;
    }
    while ( v40 );
  }
}

// FUNC: _jinit_forward_dct
void __cdecl jinit_forward_dct(jpeg_common_struct *cinfo)
{
  jpeg_forward_dct *v1; // esi

  v1 = (jpeg_forward_dct *)cinfo->mem->alloc_small(cinfo, 1, 48);
  *(_DWORD *)&cinfo[16].is_decompressor = v1;
  v1->start_pass = (void (__cdecl *)(jpeg_compress_struct *))start_pass_fdctmgr;
  if ( cinfo[8].global_state == 2 )
  {
    v1->forward_DCT = forward_DCT_float;
    v1[3].forward_DCT = (void (__cdecl *)(jpeg_compress_struct *, jpeg_component_info *, unsigned __int8 **, __int16 (*)[64], unsigned int, unsigned int, unsigned int))jpeg_fdct_float;
  }
  else
  {
    cinfo->err->msg_code = 45;
    cinfo->err->error_exit(cinfo);
  }
  v1[1].forward_DCT = 0;
  v1[4].start_pass = 0;
  v1[2].start_pass = 0;
  v1[4].forward_DCT = 0;
  v1[2].forward_DCT = 0;
  v1[5].start_pass = 0;
  v1[3].start_pass = 0;
  v1[5].forward_DCT = 0;
}
