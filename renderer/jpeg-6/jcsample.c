
// FUNC: expand_right_edge
void __usercall expand_right_edge(
        int a1@<ebx>,
        unsigned __int8 **image_data,
        int num_rows,
        unsigned int input_cols,
        unsigned int output_cols)
{
  unsigned int v5; // ebp
  int v6; // esi
  unsigned __int8 *v7; // edi
  int v8; // eax

  v5 = output_cols - input_cols;
  if ( (int)(output_cols - input_cols) > 0 )
  {
    v6 = 0;
    while ( v6 < num_rows )
    {
      v7 = &image_data[v6][input_cols];
      LOBYTE(a1) = *(v7 - 1);
      BYTE1(a1) = a1;
      ++v6;
      v8 = a1 << 16;
      LOWORD(v8) = a1;
      memset32(v7, v8, v5 >> 2);
      memset(&v7[4 * (v5 >> 2)], a1, v5 & 3);
    }
  }
}

// FUNC: sep_downsample
void __cdecl sep_downsample(
        jpeg_compress_struct *cinfo,
        unsigned __int8 ***input_buf,
        unsigned int in_row_index,
        unsigned __int8 ***output_buf,
        unsigned int out_row_group_index)
{
  bool v6; // cc
  jpeg_downsampler *downsample; // ebp
  jpeg_component_info *comp_info; // edi
  unsigned __int8 ***v9; // esi
  void (__cdecl **v10)(jpeg_compress_struct *, jpeg_component_info *, unsigned int, unsigned int); // ebp
  int i; // eax
  jpeg_compress_struct *cinfoa; // [esp+18h] [ebp+4h]

  v6 = cinfo->num_components <= 0;
  downsample = cinfo->downsample;
  comp_info = cinfo->comp_info;
  cinfoa = 0;
  if ( !v6 )
  {
    v9 = input_buf;
    v10 = (void (__cdecl **)(jpeg_compress_struct *, jpeg_component_info *, unsigned int, unsigned int))&downsample[1];
    for ( i = (char *)output_buf - (char *)input_buf; ; i = (char *)output_buf - (char *)input_buf )
    {
      (*v10)(
        cinfo,
        comp_info,
        (unsigned int)&(*v9)[in_row_index],
        (unsigned int)&(*(unsigned __int8 ***)((char *)v9 + i))[out_row_group_index * comp_info->v_samp_factor]);
      ++v9;
      ++v10;
      ++comp_info;
      cinfoa = (jpeg_compress_struct *)((char *)cinfoa + 1);
      if ( (int)cinfoa >= cinfo->num_components )
        break;
    }
  }
}

// FUNC: int_downsample
void __cdecl int_downsample(
        jpeg_compress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 **output_data)
{
  int v4; // edi
  int v5; // ebp
  int v6; // ecx
  int v7; // ebx
  int v8; // edx
  jpeg_compress_struct *v9; // esi
  unsigned __int8 *v10; // eax
  int v11; // ecx
  bool v12; // zf
  unsigned int output_cols; // [esp+10h] [ebp-20h]
  int v14; // [esp+14h] [ebp-1Ch]
  unsigned __int8 *outptr; // [esp+18h] [ebp-18h]
  unsigned int v16; // [esp+1Ch] [ebp-14h]
  int outrow; // [esp+20h] [ebp-10h]
  int v_expand; // [esp+24h] [ebp-Ch]
  int numpix2; // [esp+28h] [ebp-8h]
  int numpix; // [esp+2Ch] [ebp-4h]
  jpeg_compress_struct *cinfoa; // [esp+34h] [ebp+4h]

  output_cols = 8 * compptr->width_in_blocks;
  v4 = cinfo->max_h_samp_factor / compptr->h_samp_factor;
  v5 = cinfo->max_v_samp_factor / compptr->v_samp_factor;
  numpix = v4 * v5;
  numpix2 = v4 * v5 / 2;
  v_expand = v5;
  expand_right_edge((int)compptr, input_data, cinfo->max_v_samp_factor, cinfo->image_width, output_cols * v4);
  v6 = 0;
  outrow = 0;
  if ( compptr->v_samp_factor > 0 )
  {
    cinfoa = (jpeg_compress_struct *)input_data;
    do
    {
      outptr = output_data[v6];
      v7 = 0;
      if ( output_cols )
      {
        v16 = output_cols;
        do
        {
          v8 = 0;
          if ( v5 > 0 )
          {
            v9 = cinfoa;
            v14 = v5;
            do
            {
              v10 = (unsigned __int8 *)v9->err + v7;
              if ( v4 > 0 )
              {
                v11 = v4;
                do
                {
                  v8 += *v10++;
                  --v11;
                }
                while ( v11 );
                v5 = v_expand;
              }
              v9 = (jpeg_compress_struct *)((char *)v9 + 4);
              --v14;
            }
            while ( v14 );
          }
          v7 += v4;
          v12 = v16-- == 1;
          *outptr++ = (v8 + numpix2) / numpix;
        }
        while ( !v12 );
        v6 = outrow;
      }
      cinfoa = (jpeg_compress_struct *)((char *)cinfoa + 4 * v5);
      outrow = ++v6;
    }
    while ( v6 < compptr->v_samp_factor );
  }
}

// FUNC: fullsize_downsample
void __usercall fullsize_downsample(
        int a1@<ebx>,
        jpeg_compress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 **output_data)
{
  jcopy_sample_rows(input_data, 0, output_data, 0, cinfo->max_v_samp_factor, cinfo->image_width);
  expand_right_edge(a1, output_data, cinfo->max_v_samp_factor, cinfo->image_width, 8 * compptr->width_in_blocks);
}

// FUNC: h2v1_downsample
void __cdecl h2v1_downsample(
        jpeg_compress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 **output_data)
{
  jpeg_component_info *v4; // ebx
  unsigned __int8 **v5; // ebp
  unsigned int v6; // edi
  int v7; // edx
  _BYTE *v8; // ecx
  unsigned __int8 *v9; // eax
  int v10; // esi
  unsigned int output_cols; // [esp+Ch] [ebp-8h]
  jpeg_compress_struct *cinfoa; // [esp+18h] [ebp+4h]

  v4 = compptr;
  v5 = input_data;
  v6 = 8 * compptr->width_in_blocks;
  output_cols = v6;
  expand_right_edge(
    (int)compptr,
    input_data,
    cinfo->max_v_samp_factor,
    cinfo->image_width,
    16 * compptr->width_in_blocks);
  cinfoa = 0;
  if ( compptr->v_samp_factor > 0 )
  {
    v7 = (char *)output_data - (char *)input_data;
    do
    {
      v8 = *(unsigned __int8 **)((char *)v5 + v7);
      v9 = *v5;
      v10 = 0;
      if ( v6 )
      {
        do
        {
          *v8++ = (v10 + v9[1] + *v9) >> 1;
          v10 ^= 1u;
          v9 += 2;
          --v6;
        }
        while ( v6 );
        v4 = compptr;
        v6 = output_cols;
        v7 = (char *)output_data - (char *)input_data;
      }
      ++v5;
      cinfoa = (jpeg_compress_struct *)((char *)cinfoa + 1);
    }
    while ( (int)cinfoa < v4->v_samp_factor );
  }
}

// FUNC: h2v2_downsample
void __usercall h2v2_downsample(
        int a1@<ebx>,
        jpeg_compress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 **output_data)
{
  jpeg_component_info *v5; // ebp
  int v6; // ebx
  unsigned __int8 **v7; // edx
  unsigned __int8 *v8; // esi
  unsigned __int8 *v9; // eax
  unsigned __int8 *v10; // ecx
  int v11; // edi
  unsigned int output_cols; // [esp+Ch] [ebp-10h]
  unsigned __int8 **v13; // [esp+10h] [ebp-Ch]
  int outrow; // [esp+14h] [ebp-8h]
  jpeg_compress_struct *cinfoa; // [esp+20h] [ebp+4h]

  v5 = compptr;
  output_cols = 8 * compptr->width_in_blocks;
  expand_right_edge(a1, input_data, cinfo->max_v_samp_factor, cinfo->image_width, 16 * compptr->width_in_blocks);
  v6 = 0;
  outrow = 0;
  if ( compptr->v_samp_factor > 0 )
  {
    v7 = input_data;
    v13 = input_data;
    do
    {
      v8 = output_data[v6];
      v9 = *v7;
      v10 = v7[1];
      v11 = 1;
      if ( output_cols )
      {
        cinfoa = (jpeg_compress_struct *)output_cols;
        do
        {
          *v8++ = (v9[1] + v10[1] + v11 + *v10 + *v9) >> 2;
          v11 ^= 3u;
          v9 += 2;
          v10 += 2;
          cinfoa = (jpeg_compress_struct *)((char *)cinfoa - 1);
        }
        while ( cinfoa );
        v5 = compptr;
        v6 = outrow;
        v7 = v13;
      }
      ++v6;
      v7 += 2;
      v13 = v7;
      outrow = v6;
    }
    while ( v6 < v5->v_samp_factor );
  }
}

// FUNC: h2v2_smooth_downsample
void __cdecl h2v2_smooth_downsample(
        jpeg_compress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 **output_data)
{
  unsigned int v4; // esi
  unsigned __int8 **v5; // ebx
  int smoothing_factor; // eax
  int v7; // ecx
  unsigned __int8 **v8; // eax
  unsigned __int8 *v9; // ebx
  unsigned __int8 *v10; // esi
  unsigned __int8 *v11; // edx
  unsigned __int8 *v12; // ecx
  unsigned __int8 *v13; // eax
  unsigned __int8 *v14; // eax
  unsigned __int8 *v15; // esi
  unsigned __int8 *v16; // ecx
  unsigned __int8 *v17; // edi
  bool v18; // zf
  bool v19; // cc
  unsigned __int8 *outptr; // [esp+10h] [ebp-28h]
  int v21; // [esp+20h] [ebp-18h]
  unsigned __int8 *v22; // [esp+24h] [ebp-14h]
  unsigned int v23; // [esp+24h] [ebp-14h]
  unsigned __int8 **v24; // [esp+28h] [ebp-10h]
  int outrow; // [esp+2Ch] [ebp-Ch]
  unsigned int colctr; // [esp+34h] [ebp-4h]
  jpeg_compress_struct *cinfoa; // [esp+3Ch] [ebp+4h]
  unsigned __int8 **input_dataa; // [esp+44h] [ebp+Ch]

  v4 = 8 * compptr->width_in_blocks;
  v5 = input_data - 1;
  expand_right_edge(
    (int)(input_data - 1),
    input_data - 1,
    cinfo->max_v_samp_factor + 2,
    cinfo->image_width,
    16 * compptr->width_in_blocks);
  smoothing_factor = cinfo->smoothing_factor;
  cinfoa = (jpeg_compress_struct *)(0x4000 - 80 * smoothing_factor);
  v7 = 0;
  input_dataa = (unsigned __int8 **)(16 * smoothing_factor);
  outrow = 0;
  if ( compptr->v_samp_factor > 0 )
  {
    v8 = v5;
    colctr = v4 - 2;
    v24 = v5;
    do
    {
      v9 = v8[2];
      v10 = output_data[v7];
      v11 = v8[1];
      v12 = *v8;
      v13 = v8[3];
      v22 = v13 + 2;
      *v10 = ((_DWORD)input_dataa
            * (*v13 + *v12 + v12[2] + 2 * (*v13 + *v12 + *v9 + v12[1] + v13[1] + *v11 + v9[2] + v11[2]) + v13[2])
            + (unsigned int)cinfoa * (*v9 + *v11 + v9[1] + v11[1])
            + 0x8000) >> 16;
      v14 = v11 + 2;
      outptr = v10 + 1;
      v15 = v12 + 2;
      v16 = v9 + 2;
      v17 = v22;
      if ( colctr )
      {
        v23 = colctr;
        do
        {
          *outptr = ((_DWORD)input_dataa
                   * (v17[2]
                    + v15[2]
                    + *(v15 - 1)
                    + *(v17 - 1)
                    + 2 * (v14[2] + *v15 + v16[2] + *v17 + *(v14 - 1) + *(v16 - 1) + v15[1] + v17[1]))
                   + (unsigned int)cinfoa * (*v14 + *v16 + v14[1] + v16[1])
                   + 0x8000) >> 16;
          v14 += 2;
          v16 += 2;
          v15 += 2;
          v17 += 2;
          v18 = v23-- == 1;
          ++outptr;
        }
        while ( !v18 );
      }
      v21 = v16[1];
      *outptr = ((_DWORD)input_dataa
               * (v17[1]
                + v15[1]
                + *(v17 - 1)
                + 2 * (v17[1] + v15[1] + v21 + *(v14 - 1) + *(v16 - 1) + v14[1] + *v17 + *v15)
                + *(v15 - 1))
               + (unsigned int)cinfoa * (v21 + v14[1] + *v16 + *v14)
               + 0x8000) >> 16;
      v7 = outrow + 1;
      v8 = v24 + 2;
      v19 = outrow + 1 < compptr->v_samp_factor;
      v24 += 2;
      ++outrow;
    }
    while ( v19 );
  }
}

// FUNC: fullsize_smooth_downsample
void __cdecl fullsize_smooth_downsample(
        jpeg_compress_struct *cinfo,
        jpeg_component_info *compptr,
        unsigned __int8 **input_data,
        unsigned __int8 **output_data)
{
  unsigned int v4; // esi
  int smoothing_factor; // eax
  int v6; // ecx
  unsigned __int8 **v7; // eax
  unsigned __int8 *v8; // edi
  int v9; // ebx
  unsigned __int8 *v10; // ecx
  int v11; // esi
  int v12; // edx
  unsigned __int8 *v13; // ebp
  unsigned __int8 *v14; // edi
  int v15; // eax
  int v16; // ebx
  unsigned __int8 *v17; // ecx
  int v18; // eax
  _BYTE *v19; // esi
  int v20; // ebx
  int v21; // esi
  int v22; // eax
  bool v23; // zf
  bool v24; // cc
  int neighscale; // [esp+10h] [ebp-18h]
  int memberscale; // [esp+14h] [ebp-14h]
  unsigned int v27; // [esp+18h] [ebp-10h]
  int outrow; // [esp+1Ch] [ebp-Ch]
  unsigned __int8 **v29; // [esp+20h] [ebp-8h]
  unsigned int colctr; // [esp+24h] [ebp-4h]
  jpeg_compress_struct *cinfoa; // [esp+2Ch] [ebp+4h]
  unsigned __int8 **input_datab; // [esp+34h] [ebp+Ch]
  unsigned __int8 **input_dataa; // [esp+34h] [ebp+Ch]

  v4 = 8 * compptr->width_in_blocks;
  expand_right_edge((int)compptr, input_data - 1, cinfo->max_v_samp_factor + 2, cinfo->image_width, v4);
  smoothing_factor = cinfo->smoothing_factor;
  memberscale = (128 - smoothing_factor) << 9;
  v6 = 0;
  neighscale = smoothing_factor << 6;
  outrow = 0;
  if ( compptr->v_samp_factor > 0 )
  {
    v7 = input_data + 1;
    colctr = v4 - 2;
    v29 = input_data + 1;
    do
    {
      v8 = *(v7 - 2);
      v9 = v8[1];
      input_datab = (unsigned __int8 **)output_data[v6];
      v10 = *(v7 - 1);
      v11 = *v10;
      v12 = v11 + **v7 + *v8;
      v13 = *v7 + 1;
      v14 = v8 + 1;
      v15 = v9 + *v13;
      v16 = v10[1];
      v17 = v10 + 1;
      v18 = v16 + v15;
      *(_BYTE *)input_datab = (unsigned int)(neighscale * (v18 + 2 * v12 - v11) + memberscale * v11 + 0x8000) >> 16;
      v19 = (char *)input_datab + 1;
      input_dataa = (unsigned __int8 **)((char *)input_datab + 1);
      cinfoa = (jpeg_compress_struct *)v18;
      if ( colctr )
      {
        v27 = colctr;
        do
        {
          v20 = v14[1];
          v21 = *v17;
          v22 = v13[1];
          ++v14;
          ++v13;
          v18 = *++v17 + v20 + v22;
          *(_BYTE *)input_dataa = (unsigned int)(neighscale * ((_DWORD)cinfoa + v18 + v12 - v21)
                                               + memberscale * v21
                                               + 0x8000) >> 16;
          v12 = (int)cinfoa;
          v19 = (char *)input_dataa + 1;
          v23 = v27-- == 1;
          input_dataa = (unsigned __int8 **)((char *)input_dataa + 1);
          cinfoa = (jpeg_compress_struct *)v18;
        }
        while ( !v23 );
      }
      *v19 = (neighscale * (v12 + 2 * v18 - *v17) + memberscale * (unsigned int)*v17 + 0x8000) >> 16;
      v6 = outrow + 1;
      v7 = v29 + 1;
      v24 = ++outrow < compptr->v_samp_factor;
      ++v29;
    }
    while ( v24 );
  }
}

// FUNC: _jinit_downsampler
void __cdecl jinit_downsampler(jpeg_common_struct *cinfo)
{
  jpeg_downsampler *v2; // ebx
  int *p_format_message; // ebp
  jpeg_downsampler *v4; // edi
  int v5; // ecx
  int mem; // eax
  unsigned __int8 smoothok; // [esp+Bh] [ebp-5h]
  int ci; // [esp+Ch] [ebp-4h]
  jpeg_compress_struct *cinfoa; // [esp+14h] [ebp+4h]

  smoothok = 1;
  v2 = (jpeg_downsampler *)cinfo->mem->alloc_small(cinfo, 1, 52);
  cinfo[16].progress = (jpeg_progress_mgr *)v2;
  v2->start_pass = (void (__cdecl *)(jpeg_compress_struct *))SpawnStub;
  v2->downsample = sep_downsample;
  v2->need_context_rows = 0;
  cinfoa = (jpeg_compress_struct *)v2;
  if ( HIBYTE(cinfo[8].progress) )
  {
    cinfo->err->msg_code = 21;
    cinfo->err->error_exit(cinfo);
  }
  ci = 0;
  if ( *(int *)&cinfo[2].is_decompressor > 0 )
  {
    p_format_message = (int *)&cinfo[3].err->format_message;
    v4 = v2 + 1;
    do
    {
      v5 = *(p_format_message - 1);
      mem = (int)cinfo[10].mem;
      if ( v5 == mem && (jpeg_progress_mgr *)*p_format_message == cinfo[10].progress )
      {
        if ( *(_DWORD *)&cinfo[8].is_decompressor )
        {
          v4->start_pass = (void (__cdecl *)(jpeg_compress_struct *))fullsize_smooth_downsample;
          v2->need_context_rows = 1;
        }
        else
        {
          v4->start_pass = (void (__cdecl *)(jpeg_compress_struct *))fullsize_downsample;
        }
      }
      else
      {
        if ( 2 * v5 != mem )
          goto LABEL_18;
        v2 = (jpeg_downsampler *)cinfoa;
        if ( (jpeg_progress_mgr *)*p_format_message == cinfo[10].progress )
        {
          smoothok = 0;
          v4->start_pass = (void (__cdecl *)(jpeg_compress_struct *))h2v1_downsample;
        }
        else
        {
          if ( 2 * v5 != mem || (jpeg_progress_mgr *)(2 * *p_format_message) != cinfo[10].progress )
          {
LABEL_18:
            if ( mem % v5 || (int)cinfo[10].progress % *p_format_message )
            {
              cinfo->err->msg_code = 35;
              cinfo->err->error_exit(cinfo);
            }
            else
            {
              smoothok = 0;
              v4->start_pass = (void (__cdecl *)(jpeg_compress_struct *))int_downsample;
            }
            goto LABEL_22;
          }
          if ( *(_DWORD *)&cinfo[8].is_decompressor )
          {
            v4->start_pass = (void (__cdecl *)(jpeg_compress_struct *))h2v2_smooth_downsample;
            LOBYTE(cinfoa->progress) = 1;
          }
          else
          {
            v4->start_pass = (void (__cdecl *)(jpeg_compress_struct *))h2v2_downsample;
          }
        }
      }
LABEL_22:
      v4 = (jpeg_downsampler *)((char *)v4 + 4);
      p_format_message += 21;
      ++ci;
    }
    while ( ci < *(_DWORD *)&cinfo[2].is_decompressor );
  }
  if ( *(_DWORD *)&cinfo[8].is_decompressor )
  {
    if ( !smoothok )
    {
      cinfo->err->msg_code = 96;
      cinfo->err->emit_message(cinfo, 0);
    }
  }
}
