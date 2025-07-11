
// FUNC: start_pass_upsample
void __cdecl start_pass_upsample(jpeg_decompress_struct *cinfo)
{
  jpeg_upsampler *upsample; // ecx

  upsample = cinfo->upsample;
  *(_DWORD *)&upsample[7].need_context_rows = cinfo->max_v_samp_factor;
  upsample[8].start_pass = (void (__cdecl *)(jpeg_decompress_struct *))cinfo->output_height;
}

// FUNC: sep_upsample
void __cdecl sep_upsample(
        jpeg_decompress_struct *cinfo,
        unsigned __int8 ***input_buf,
        unsigned int *in_row_group_ctr,
        unsigned int in_row_groups_avail,
        unsigned __int8 **output_buf,
        unsigned int *out_row_ctr,
        unsigned int out_rows_avail)
{
  jpeg_upsampler *upsample; // ebp
  int v9; // ebx
  bool v10; // cc
  jpeg_upsampler *v11; // esi
  unsigned int start_pass; // esi
  jpeg_component_info *cinfoa; // [esp+14h] [ebp+4h]

  upsample = cinfo->upsample;
  if ( *(_DWORD *)&upsample[7].need_context_rows >= cinfo->max_v_samp_factor )
  {
    v9 = 0;
    v10 = cinfo->num_components <= 0;
    cinfoa = cinfo->comp_info;
    if ( !v10 )
    {
      v11 = upsample + 1;
      do
      {
        ((void (__cdecl *)(jpeg_decompress_struct *, jpeg_component_info *, unsigned __int8 **, jpeg_upsampler *))v11[3].upsample)(
          cinfo,
          cinfoa++,
          &input_buf[v9++][*in_row_group_ctr * (unsigned int)v11[7].upsample],
          v11);
        v11 = (jpeg_upsampler *)((char *)v11 + 4);
      }
      while ( v9 < cinfo->num_components );
    }
    *(_DWORD *)&upsample[7].need_context_rows = 0;
  }
  start_pass = cinfo->max_v_samp_factor - *(_DWORD *)&upsample[7].need_context_rows;
  if ( (char *)start_pass > (char *)upsample[8].start_pass )
    start_pass = (unsigned int)upsample[8].start_pass;
  if ( start_pass > out_rows_avail - *out_row_ctr )
    start_pass = out_rows_avail - *out_row_ctr;
  cinfo->cconvert->color_convert(
    cinfo,
    (unsigned __int8 ***)&upsample[1],
    *(_DWORD *)&upsample[7].need_context_rows,
    &output_buf[*out_row_ctr],
    start_pass);
  *out_row_ctr += start_pass;
  upsample[8].start_pass = (void (__cdecl *)(jpeg_decompress_struct *))((char *)upsample[8].start_pass - start_pass);
  *(_DWORD *)&upsample[7].need_context_rows += start_pass;
  if ( *(_DWORD *)&upsample[7].need_context_rows >= cinfo->max_v_samp_factor )
    ++*in_row_group_ctr;
}

// FUNC: fullsize_upsample
void __cdecl fullsize_upsample(
        jpeg_decompress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 ***output_data_ptr)
{
  *output_data_ptr = input_data;
}

// FUNC: noop_upsample
void __cdecl noop_upsample(
        jpeg_decompress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 ***output_data_ptr)
{
  *output_data_ptr = 0;
}

// FUNC: int_upsample
void __cdecl int_upsample(
        jpeg_decompress_struct *cinfo,
        jpeg_component_info *compptr,
        char **input_data,
        unsigned __int8 ***output_data_ptr)
{
  jpeg_decompress_struct *v4; // edx
  unsigned __int8 **v5; // eax
  char *v6; // ecx
  int v7; // edi
  int v8; // ebx
  unsigned __int8 *v9; // esi
  char *v10; // ecx
  unsigned __int8 *v11; // ebp
  char v12; // al
  int v13; // eax
  jpeg_component_info *v14; // ecx
  unsigned __int8 **output_data; // [esp+Ch] [ebp-10h]
  int outrow; // [esp+10h] [ebp-Ch]
  int h_expand; // [esp+14h] [ebp-8h]
  jpeg_component_info *compptra; // [esp+24h] [ebp+8h]

  v4 = cinfo;
  v5 = *output_data_ptr;
  v6 = (char *)cinfo->upsample + compptr->component_index;
  v7 = (unsigned __int8)v6[140];
  v8 = 0;
  output_data = *output_data_ptr;
  h_expand = v7;
  compptra = (jpeg_component_info *)(unsigned __int8)v6[150];
  for ( outrow = 0; v8 < v4->max_v_samp_factor; outrow = v8 )
  {
    v9 = v5[v8];
    v10 = *input_data;
    v11 = &v9[v4->output_width];
    if ( v9 < v11 )
    {
      do
      {
        v12 = *v10++;
        if ( v7 > 0 )
        {
          LOBYTE(v8) = v12;
          BYTE1(v8) = v12;
          v13 = v8 << 16;
          LOWORD(v13) = v8;
          v8 = outrow;
          memset32(v9, v13, (unsigned int)v7 >> 2);
          v4 = cinfo;
          memset(&v9[4 * ((unsigned int)v7 >> 2)], v13, v7 & 3);
          v7 = h_expand;
          v9 += h_expand;
        }
      }
      while ( v9 < v11 );
      v5 = output_data;
    }
    v14 = compptra;
    if ( (int)compptra > 1 )
    {
      jcopy_sample_rows(v5, v8, v5, v8 + 1, (int)&compptra[-1].dct_table + 3, v4->output_width);
      v4 = cinfo;
      v5 = output_data;
      v14 = compptra;
    }
    ++input_data;
    v8 += (int)v14;
  }
}

// FUNC: h2v1_upsample
void __cdecl h2v1_upsample(
        jpeg_decompress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 ***output_data_ptr)
{
  int v4; // ebp
  char *v5; // edi
  unsigned __int8 ***v6; // edx
  char *v7; // eax
  char *v8; // esi
  unsigned int v9; // ecx
  char v10; // dl
  _BYTE *v11; // eax
  unsigned __int8 ***output_data_ptra; // [esp+1Ch] [ebp+10h]

  v4 = 0;
  v5 = (char *)*output_data_ptr;
  if ( cinfo->max_v_samp_factor > 0 )
  {
    v6 = (unsigned __int8 ***)((char *)input_data - v5);
    output_data_ptra = (unsigned __int8 ***)((char *)input_data - v5);
    do
    {
      v7 = *(char **)v5;
      v8 = *(char **)&v5[(_DWORD)v6];
      v9 = *(_DWORD *)v5 + cinfo->output_width;
      if ( *(_DWORD *)v5 < v9 )
      {
        do
        {
          v10 = *v8;
          *v7 = *v8;
          v11 = v7 + 1;
          *v11 = v10;
          v7 = v11 + 1;
          ++v8;
        }
        while ( (unsigned int)v7 < v9 );
        v6 = output_data_ptra;
      }
      ++v4;
      v5 += 4;
    }
    while ( v4 < cinfo->max_v_samp_factor );
  }
}

// FUNC: h2v2_upsample
void __cdecl h2v2_upsample(
        jpeg_decompress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 ***output_data_ptr)
{
  unsigned __int8 **v4; // ebx
  int i; // esi
  unsigned __int8 *v6; // eax
  unsigned __int8 *v7; // edi
  unsigned __int8 *j; // ecx
  unsigned __int8 v9; // dl
  unsigned __int8 *v10; // eax

  v4 = *output_data_ptr;
  for ( i = 0; i < cinfo->max_v_samp_factor; i += 2 )
  {
    v6 = v4[i];
    v7 = *input_data;
    for ( j = &v6[cinfo->output_width]; v6 < j; ++v7 )
    {
      v9 = *v7;
      *v6 = *v7;
      v10 = v6 + 1;
      *v10 = v9;
      v6 = v10 + 1;
    }
    jcopy_sample_rows(v4, i, v4, i + 1, 1, cinfo->output_width);
    ++input_data;
  }
}

// FUNC: h2v1_fancy_upsample
void __cdecl h2v1_fancy_upsample(
        jpeg_decompress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 ***output_data_ptr)
{
  int v4; // ebx
  char *v5; // edi
  unsigned __int8 ***v6; // eax
  unsigned __int8 *v7; // ecx
  int v8; // edx
  _BYTE *v9; // eax
  int v10; // esi
  unsigned __int8 *v11; // ecx
  _BYTE *v12; // eax
  unsigned int v13; // ebp
  int v14; // esi
  int v15; // edx
  _BYTE *v16; // eax
  int v17; // edx
  unsigned __int8 ***output_data_ptra; // [esp+18h] [ebp+10h]

  v4 = 0;
  v5 = (char *)*output_data_ptr;
  if ( cinfo->max_v_samp_factor > 0 )
  {
    v6 = (unsigned __int8 ***)((char *)input_data - v5);
    for ( output_data_ptra = (unsigned __int8 ***)((char *)input_data - v5); ; v6 = output_data_ptra )
    {
      v7 = *(unsigned __int8 **)&v5[(_DWORD)v6];
      v8 = *v7;
      v9 = *(_BYTE **)v5;
      *v9 = v8;
      v10 = v7[1];
      v11 = v7 + 1;
      *++v9 = (3 * v8 + v10 + 2) >> 2;
      v12 = v9 + 1;
      if ( compptr->downsampled_width != 2 )
      {
        v13 = compptr->downsampled_width - 2;
        do
        {
          v14 = 3 * *v11;
          v15 = *(v11++ - 1);
          *v12 = (v15 + v14 + 1) >> 2;
          v16 = v12 + 1;
          *v16 = (*v11 + v14 + 2) >> 2;
          v12 = v16 + 1;
          --v13;
        }
        while ( v13 );
      }
      v17 = *v11;
      *v12 = (*(v11 - 1) + 3 * v17 + 1) >> 2;
      v12[1] = v17;
      ++v4;
      v5 += 4;
      if ( v4 >= cinfo->max_v_samp_factor )
        break;
    }
  }
}

// FUNC: h2v2_fancy_upsample
void __cdecl h2v2_fancy_upsample(
        jpeg_decompress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 ***output_data_ptr)
{
  int v4; // eax
  unsigned __int8 **v5; // esi
  int v6; // ecx
  unsigned __int8 *v7; // ebp
  unsigned __int8 *v8; // edi
  int v9; // esi
  unsigned __int8 *v10; // ecx
  unsigned __int8 *v11; // ebp
  int v12; // esi
  int v13; // eax
  unsigned __int8 *v14; // edi
  unsigned __int8 *v15; // ebp
  _BYTE *v16; // ecx
  int v17; // ebx
  int v18; // esi
  _BYTE *v19; // ecx
  bool v20; // zf
  unsigned int v21; // [esp+0h] [ebp-10h]
  int v; // [esp+4h] [ebp-Ch]
  int outrow; // [esp+8h] [ebp-8h]
  unsigned __int8 **output_data; // [esp+Ch] [ebp-4h]
  unsigned __int8 ***output_data_ptra; // [esp+20h] [ebp+10h]

  v4 = 0;
  output_data = *output_data_ptr;
  if ( cinfo->max_v_samp_factor > 0 )
  {
    v5 = input_data;
    output_data_ptra = (unsigned __int8 ***)input_data;
    do
    {
      v6 = 0;
      for ( v = 0; v < 2; ++v )
      {
        v7 = *v5;
        if ( v6 )
          v8 = v5[1];
        else
          v8 = *(v5 - 1);
        v9 = *v7;
        v10 = output_data[v4];
        v11 = v7 + 1;
        outrow = v4 + 1;
        v12 = *v8 + 3 * v9;
        v13 = v8[1] + 3 * *v11;
        *v10++ = (4 * v12 + 8) >> 4;
        *v10 = (v12 + v13 + 2 * v12 + 7) >> 4;
        v14 = v8 + 2;
        v15 = v11 + 1;
        v16 = v10 + 1;
        v17 = v12;
        v18 = v13;
        if ( compptr->downsampled_width != 2 )
        {
          v21 = compptr->downsampled_width - 2;
          do
          {
            v13 = *v14 + 3 * *v15;
            *v16 = (3 * v18 + v17 + 8) >> 4;
            v19 = v16 + 1;
            *v19 = (3 * v18 + v13 + 7) >> 4;
            ++v14;
            ++v15;
            v16 = v19 + 1;
            v20 = v21-- == 1;
            v17 = v18;
            v18 = v13;
          }
          while ( !v20 );
        }
        v5 = (unsigned __int8 **)output_data_ptra;
        *v16 = (v13 + v17 + 2 * v13 + 8) >> 4;
        v16[1] = (4 * v13 + 7) >> 4;
        v4 = outrow;
        v6 = v + 1;
      }
      v5 = (unsigned __int8 **)++output_data_ptra;
    }
    while ( outrow < cinfo->max_v_samp_factor );
  }
}

// FUNC: _jinit_upsampler
void __cdecl jinit_upsampler(jpeg_common_struct *cinfo)
{
  jpeg_upsampler *v2; // ebx
  int *v3; // ebp
  _DWORD *p_upsample; // ebx
  int global_state; // edi
  int v6; // edx
  int v7; // ecx
  int progress; // eax
  int v9; // edx
  jpeg_memory_mgr *mem; // edi
  int v11; // eax
  int v12; // [esp-8h] [ebp-24h]
  int ci; // [esp+Ch] [ebp-10h]
  int h_in_group; // [esp+10h] [ebp-Ch]
  int h_in_groupa; // [esp+10h] [ebp-Ch]
  int v_out_group; // [esp+14h] [ebp-8h]
  my_upsampler *upsample; // [esp+18h] [ebp-4h]
  char cinfoa; // [esp+20h] [ebp+4h]

  v2 = (jpeg_upsampler *)cinfo->mem->alloc_small(cinfo, 1, 160);
  *(_DWORD *)&cinfo[20].is_decompressor = v2;
  v2->start_pass = start_pass_upsample;
  v2->upsample = sep_upsample;
  v2->need_context_rows = 0;
  upsample = (my_upsampler *)v2;
  if ( LOBYTE(cinfo[13].mem) )
  {
    cinfo->err->msg_code = 21;
    cinfo->err->error_exit(cinfo);
  }
  if ( !cinfo[3].is_decompressor || (cinfoa = 1, cinfo[13].global_state <= 1) )
    cinfoa = 0;
  ci = 0;
  if ( *(int *)&cinfo[1].is_decompressor > 0 )
  {
    v3 = (int *)(cinfo[9].global_state + 36);
    p_upsample = &v2[4].upsample;
    do
    {
      global_state = cinfo[13].global_state;
      h_in_group = *v3 * *(v3 - 7) / global_state;
      v6 = *(_DWORD *)&cinfo[13].is_decompressor;
      v_out_group = v6;
      v7 = *v3 * *(v3 - 6) / global_state;
      progress = (int)cinfo[13].progress;
      p_upsample[12] = v7;
      if ( *((_BYTE *)v3 + 12) )
      {
        if ( h_in_group != progress || v7 != v6 )
        {
          if ( 2 * h_in_group == progress )
          {
            if ( v7 == v6 )
            {
              if ( cinfoa && (unsigned int)v3[1] > 2 )
                *p_upsample = h2v1_fancy_upsample;
              else
                *p_upsample = h2v1_upsample;
LABEL_29:
              mem = cinfo->mem;
              v12 = *(_DWORD *)&cinfo[13].is_decompressor;
              v11 = jround_up(*(_DWORD *)&cinfo[4].is_decompressor, (int)cinfo[13].progress);
              *(p_upsample - 10) = mem->alloc_sarray(cinfo, 1, v11, v12);
              goto LABEL_30;
            }
            if ( 2 * h_in_group == progress && 2 * v7 == v6 )
            {
              if ( cinfoa && (unsigned int)v3[1] > 2 )
              {
                *p_upsample = h2v2_fancy_upsample;
                upsample->pub.need_context_rows = 1;
              }
              else
              {
                *p_upsample = h2v2_upsample;
              }
              goto LABEL_29;
            }
          }
          v9 = progress % h_in_group;
          h_in_groupa = progress / h_in_group;
          if ( v9 || v_out_group % v7 )
          {
            cinfo->err->msg_code = 35;
            cinfo->err->error_exit(cinfo);
          }
          else
          {
            *p_upsample = int_upsample;
            upsample->h_expand[ci] = h_in_groupa;
            upsample->v_expand[ci] = v_out_group / v7;
          }
          goto LABEL_29;
        }
        *p_upsample = fullsize_upsample;
      }
      else
      {
        *p_upsample = noop_upsample;
      }
LABEL_30:
      ++p_upsample;
      v3 += 21;
      ++ci;
    }
    while ( ci < *(_DWORD *)&cinfo[1].is_decompressor );
  }
}
