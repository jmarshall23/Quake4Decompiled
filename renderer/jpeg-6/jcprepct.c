
// FUNC: start_pass_prep
void __cdecl start_pass_prep(jpeg_common_struct *cinfo, J_BUF_MODE pass_mode)
{
  jpeg_c_prep_controller *v2; // esi

  v2 = *(jpeg_c_prep_controller **)&cinfo[15].is_decompressor;
  if ( pass_mode )
  {
    cinfo->err->msg_code = 4;
    cinfo->err->error_exit(cinfo);
  }
  v2[6].start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))cinfo[1].progress;
  v2[6].pre_process_data = 0;
  v2[7].start_pass = 0;
  v2[7].pre_process_data = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8 **, unsigned int *, unsigned int, unsigned __int8 ***, unsigned int *, unsigned int))(2 * (int)cinfo[10].progress);
}

// FUNC: pre_process_data
void __cdecl pre_process_data(
        jpeg_compress_struct *cinfo,
        unsigned __int8 **input_buf,
        unsigned int *in_row_ctr,
        unsigned int in_rows_avail,
        unsigned __int8 ***output_buf,
        unsigned int *out_row_group_ctr,
        unsigned int out_row_groups_avail)
{
  jpeg_c_prep_controller *prep; // edi
  unsigned int *v9; // ebp
  unsigned int v10; // esi
  int v11; // eax
  bool v12; // zf
  int v13; // esi
  unsigned __int8 **v14; // ebp
  int *p_v_samp_factor; // edx
  int v16; // eax
  signed int v17; // esi
  unsigned int v18; // ebp
  int v19; // edi
  bool v20; // cc
  unsigned __int8 ***v21; // [esp+8h] [ebp-10h]
  unsigned int num_cols; // [esp+Ch] [ebp-Ch]
  int source_row; // [esp+10h] [ebp-8h]
  int max_v_samp_factor; // [esp+14h] [ebp-4h]
  int v25; // [esp+14h] [ebp-4h]
  jpeg_compress_struct *cinfoa; // [esp+1Ch] [ebp+4h]
  jpeg_compress_struct *cinfob; // [esp+1Ch] [ebp+4h]
  unsigned int *in_row_ctra; // [esp+24h] [ebp+Ch]
  unsigned __int8 **in_rows_availa; // [esp+28h] [ebp+10h]

  prep = cinfo->prep;
  while ( *in_row_ctr < in_rows_avail )
  {
    v9 = out_row_group_ctr;
    if ( *out_row_group_ctr >= out_row_groups_avail )
      break;
    v10 = cinfo->max_v_samp_factor - (unsigned int)prep[6].pre_process_data;
    if ( v10 >= in_rows_avail - *in_row_ctr )
      v10 = in_rows_avail - *in_row_ctr;
    cinfo->cconvert->color_convert(
      cinfo,
      &input_buf[*in_row_ctr],
      (unsigned __int8 ***)&prep[1],
      (unsigned int)prep[6].pre_process_data,
      v10);
    *in_row_ctr += v10;
    prep[6].pre_process_data = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8 **, unsigned int *, unsigned int, unsigned __int8 ***, unsigned int *, unsigned int))((char *)prep[6].pre_process_data + v10);
    v11 = (int)prep[6].pre_process_data;
    v12 = prep[6].start_pass == (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))v10;
    prep[6].start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))((char *)prep[6].start_pass - v10);
    if ( v12 && v11 < cinfo->max_v_samp_factor )
    {
      cinfoa = 0;
      if ( cinfo->num_components > 0 )
      {
        v21 = (unsigned __int8 ***)&prep[1];
        do
        {
          v13 = (int)prep[6].pre_process_data;
          v14 = *v21;
          max_v_samp_factor = cinfo->max_v_samp_factor;
          num_cols = cinfo->image_width;
          if ( v13 < max_v_samp_factor )
          {
            source_row = v13 - 1;
            do
              jcopy_sample_rows(v14, source_row, v14, v13++, 1, num_cols);
            while ( v13 < max_v_samp_factor );
          }
          ++v21;
          cinfoa = (jpeg_compress_struct *)((char *)cinfoa + 1);
        }
        while ( (int)cinfoa < cinfo->num_components );
        v9 = out_row_group_ctr;
      }
      prep[6].pre_process_data = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8 **, unsigned int *, unsigned int, unsigned __int8 ***, unsigned int *, unsigned int))cinfo->max_v_samp_factor;
    }
    if ( prep[6].pre_process_data == (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8 **, unsigned int *, unsigned int, unsigned __int8 ***, unsigned int *, unsigned int))cinfo->max_v_samp_factor )
    {
      cinfo->downsample->downsample(cinfo, (unsigned __int8 ***)&prep[1], 0, output_buf, *v9);
      prep[6].pre_process_data = 0;
      ++*v9;
    }
    if ( !prep[6].start_pass && *v9 < out_row_groups_avail )
    {
      cinfob = 0;
      if ( cinfo->num_components > 0 )
      {
        p_v_samp_factor = &cinfo->comp_info->v_samp_factor;
        in_row_ctra = (unsigned int *)p_v_samp_factor;
        do
        {
          v16 = *p_v_samp_factor * *v9;
          v17 = out_row_groups_avail * *p_v_samp_factor;
          v18 = 8 * p_v_samp_factor[4];
          in_rows_availa = output_buf[(_DWORD)cinfob];
          v19 = v16;
          if ( v16 < v17 )
          {
            v25 = v16 - 1;
            jcopy_sample_rows(output_buf[(_DWORD)cinfob], v16 - 1, output_buf[(_DWORD)cinfob], v16, 1, v18);
            while ( ++v19 < v17 )
              jcopy_sample_rows(in_rows_availa, v25, in_rows_availa, v19, 1, v18);
            p_v_samp_factor = (int *)in_row_ctra;
          }
          v9 = out_row_group_ctr;
          p_v_samp_factor += 21;
          v20 = (int)&cinfob->err + 1 < cinfo->num_components;
          cinfob = (jpeg_compress_struct *)((char *)cinfob + 1);
          in_row_ctra = (unsigned int *)p_v_samp_factor;
        }
        while ( v20 );
      }
      *v9 = out_row_groups_avail;
      return;
    }
  }
}

// FUNC: pre_process_context
void __cdecl pre_process_context(
        jpeg_compress_struct *cinfo,
        unsigned __int8 **input_buf,
        unsigned int *in_row_ctr,
        unsigned int in_rows_avail,
        unsigned __int8 ***output_buf,
        unsigned int *out_row_group_ctr,
        unsigned int out_row_groups_avail)
{
  jpeg_c_prep_controller *prep; // ebx
  unsigned int *v9; // edi
  int v10; // edx
  unsigned int pre_process_data; // ecx
  unsigned int v12; // ebp
  int max_v_samp_factor; // eax
  int v14; // edi
  int v15; // ebp
  int v16; // edi
  unsigned __int8 **v17; // ebp
  int *p_v_samp_factor; // edx
  int v19; // eax
  signed int v20; // edi
  unsigned int v21; // ebp
  int v22; // ebx
  bool v23; // cc
  int numrows; // [esp+Ch] [ebp-14h]
  int numrowsa; // [esp+Ch] [ebp-14h]
  unsigned __int8 ***v26; // [esp+10h] [ebp-10h]
  unsigned __int8 ***v27; // [esp+10h] [ebp-10h]
  int *v28; // [esp+10h] [ebp-10h]
  int source_row; // [esp+14h] [ebp-Ch]
  int v30; // [esp+18h] [ebp-8h]
  int v31; // [esp+18h] [ebp-8h]
  int buf_height; // [esp+1Ch] [ebp-4h]
  unsigned __int8 **buf_heighta; // [esp+1Ch] [ebp-4h]
  jpeg_compress_struct *cinfoa; // [esp+24h] [ebp+4h]
  jpeg_compress_struct *cinfob; // [esp+24h] [ebp+4h]
  jpeg_compress_struct *cinfoc; // [esp+24h] [ebp+4h]

  prep = cinfo->prep;
  v9 = out_row_group_ctr;
  buf_height = 3 * cinfo->max_v_samp_factor;
  if ( *out_row_group_ctr < out_row_groups_avail )
  {
    while ( 1 )
    {
      v10 = *in_row_ctr;
      if ( *in_row_ctr >= in_rows_avail )
      {
        if ( prep[6].start_pass )
          return;
      }
      else
      {
        pre_process_data = (unsigned int)prep[6].pre_process_data;
        v12 = (unsigned int)prep[7].pre_process_data - pre_process_data;
        numrows = v12;
        if ( v12 >= in_rows_avail - v10 )
        {
          numrows = in_rows_avail - v10;
          v12 = in_rows_avail - v10;
        }
        cinfo->cconvert->color_convert(cinfo, &input_buf[v10], (unsigned __int8 ***)&prep[1], pre_process_data, v12);
        if ( prep[6].start_pass == (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))cinfo->image_height )
        {
          cinfoa = 0;
          if ( cinfo->num_components > 0 )
          {
            max_v_samp_factor = cinfo->max_v_samp_factor;
            v26 = (unsigned __int8 ***)&prep[1];
            do
            {
              v14 = 1;
              if ( max_v_samp_factor >= 1 )
              {
                v15 = -1;
                do
                {
                  jcopy_sample_rows(*v26, 0, *v26, v15, 1, cinfo->image_width);
                  max_v_samp_factor = cinfo->max_v_samp_factor;
                  ++v14;
                  --v15;
                }
                while ( v14 <= max_v_samp_factor );
                v12 = numrows;
              }
              ++v26;
              cinfoa = (jpeg_compress_struct *)((char *)cinfoa + 1);
            }
            while ( (int)cinfoa < cinfo->num_components );
          }
        }
        *in_row_ctr += v12;
        prep[6].pre_process_data = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8 **, unsigned int *, unsigned int, unsigned __int8 ***, unsigned int *, unsigned int))((char *)prep[6].pre_process_data + v12);
        prep[6].start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))((char *)prep[6].start_pass - v12);
        v9 = out_row_group_ctr;
      }
      if ( !prep[6].start_pass && (int)prep[6].pre_process_data < (int)prep[7].pre_process_data )
      {
        cinfob = 0;
        if ( cinfo->num_components > 0 )
        {
          v27 = (unsigned __int8 ***)&prep[1];
          do
          {
            v16 = (int)prep[6].pre_process_data;
            v17 = *v27;
            v30 = (int)prep[7].pre_process_data;
            numrowsa = cinfo->image_width;
            if ( v16 < v30 )
            {
              source_row = v16 - 1;
              do
                jcopy_sample_rows(v17, source_row, v17, v16++, 1, numrowsa);
              while ( v16 < v30 );
            }
            ++v27;
            cinfob = (jpeg_compress_struct *)((char *)cinfob + 1);
          }
          while ( (int)cinfob < cinfo->num_components );
          v9 = out_row_group_ctr;
        }
        prep[6].pre_process_data = prep[7].pre_process_data;
      }
      if ( prep[6].pre_process_data == prep[7].pre_process_data )
      {
        cinfo->downsample->downsample(
          cinfo,
          (unsigned __int8 ***)&prep[1],
          (unsigned int)prep[7].start_pass,
          output_buf,
          *v9);
        ++*v9;
        prep[7].start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))((char *)prep[7].start_pass
                                                                                  + cinfo->max_v_samp_factor);
        if ( (int)prep[7].start_pass >= buf_height )
          prep[7].start_pass = 0;
        if ( (int)prep[6].pre_process_data >= buf_height )
          prep[6].pre_process_data = 0;
        prep[7].pre_process_data = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8 **, unsigned int *, unsigned int, unsigned __int8 ***, unsigned int *, unsigned int))((char *)prep[6].pre_process_data + cinfo->max_v_samp_factor);
      }
      if ( !prep[6].start_pass && *v9 < out_row_groups_avail )
        break;
      if ( *v9 >= out_row_groups_avail )
        return;
    }
    cinfoc = 0;
    if ( cinfo->num_components > 0 )
    {
      p_v_samp_factor = &cinfo->comp_info->v_samp_factor;
      v28 = p_v_samp_factor;
      do
      {
        v19 = *p_v_samp_factor * *out_row_group_ctr;
        v20 = out_row_groups_avail * *p_v_samp_factor;
        v21 = 8 * p_v_samp_factor[4];
        buf_heighta = output_buf[(_DWORD)cinfoc];
        v22 = v19;
        if ( v19 < v20 )
        {
          v31 = v19 - 1;
          jcopy_sample_rows(output_buf[(_DWORD)cinfoc], v19 - 1, output_buf[(_DWORD)cinfoc], v19, 1, v21);
          while ( ++v22 < v20 )
            jcopy_sample_rows(buf_heighta, v31, buf_heighta, v22, 1, v21);
          p_v_samp_factor = v28;
        }
        p_v_samp_factor += 21;
        v23 = (int)&cinfoc->err + 1 < cinfo->num_components;
        cinfoc = (jpeg_compress_struct *)((char *)cinfoc + 1);
        v28 = p_v_samp_factor;
      }
      while ( v23 );
      v9 = out_row_group_ctr;
    }
    *v9 = out_row_groups_avail;
  }
}

// FUNC: create_context_buffer
void __cdecl create_context_buffer(jpeg_common_struct *cinfo)
{
  int progress; // ebx
  jpeg_c_prep_controller *v3; // edi
  int v4; // eax
  jpeg_component_info *err; // edx
  unsigned int v6; // esi
  int *p_h_samp_factor; // ecx
  unsigned __int8 **v8; // eax
  unsigned __int8 **v9; // ecx
  unsigned __int8 **v10; // edx
  int v11; // esi
  bool v12; // cc
  char *v13; // [esp+Ch] [ebp-1Ch]
  int *v14; // [esp+10h] [ebp-18h]
  int v15; // [esp+14h] [ebp-14h]
  int ci; // [esp+18h] [ebp-10h]
  jpeg_c_prep_controller *v17; // [esp+1Ch] [ebp-Ch]
  int v18; // [esp+24h] [ebp-4h]
  jpeg_compress_struct *cinfoa; // [esp+2Ch] [ebp+4h]

  progress = (int)cinfo[10].progress;
  v3 = *(jpeg_c_prep_controller **)&cinfo[15].is_decompressor;
  v4 = cinfo->mem->alloc_small(cinfo, 1, 20 * progress * *(_DWORD *)&cinfo[2].is_decompressor);
  err = (jpeg_component_info *)cinfo[3].err;
  cinfoa = (jpeg_compress_struct *)v4;
  ci = 0;
  if ( *(int *)&cinfo[2].is_decompressor > 0 )
  {
    v6 = 12 * progress;
    v18 = 20 * progress;
    p_h_samp_factor = &err->h_samp_factor;
    v14 = &err->h_samp_factor;
    v13 = (char *)(v4 + 4 * progress);
    v17 = v3 + 1;
    while ( 1 )
    {
      v8 = cinfo->mem->alloc_sarray(
             cinfo,
             1,
             8 * (int)cinfo[10].mem * p_h_samp_factor[5] / *p_h_samp_factor,
             3 * progress);
      qmemcpy(v13, v8, v6);
      if ( progress > 0 )
      {
        v9 = (unsigned __int8 **)((char *)cinfoa + 16 * progress);
        v10 = &v8[2 * progress];
        v11 = (char *)cinfoa - (char *)v8;
        v15 = progress;
        do
        {
          *(unsigned __int8 **)((char *)v8 + v11) = *v10;
          *v9 = *v8;
          ++v10;
          ++v8;
          ++v9;
          --v15;
        }
        while ( v15 );
      }
      cinfoa = (jpeg_compress_struct *)((char *)cinfoa + v18);
      v14 += 21;
      v17->start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))v13;
      v13 += v18;
      v12 = ++ci < *(_DWORD *)&cinfo[2].is_decompressor;
      v17 = (jpeg_c_prep_controller *)((char *)v17 + 4);
      if ( !v12 )
        break;
      p_h_samp_factor = v14;
      v6 = 12 * progress;
    }
  }
}

// FUNC: _jinit_c_prep_controller
void __cdecl jinit_c_prep_controller(jpeg_common_struct *cinfo, unsigned __int8 need_full_buffer)
{
  jpeg_c_prep_controller *v2; // eax
  int v3; // ebp
  int *p_output_message; // edi
  jpeg_c_prep_controller *v5; // ebx

  if ( need_full_buffer )
  {
    cinfo->err->msg_code = 4;
    cinfo->err->error_exit(cinfo);
  }
  v2 = (jpeg_c_prep_controller *)cinfo->mem->alloc_small(cinfo, 1, 64);
  *(_DWORD *)&cinfo[15].is_decompressor = v2;
  v2->start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))start_pass_prep;
  if ( LOBYTE(cinfo[16].progress->pass_limit) )
  {
    v2->pre_process_data = pre_process_context;
    create_context_buffer(cinfo);
  }
  else
  {
    v2->pre_process_data = pre_process_data;
    v3 = 0;
    if ( *(int *)&cinfo[2].is_decompressor > 0 )
    {
      p_output_message = (int *)&cinfo[3].err->output_message;
      v5 = v2 + 1;
      do
      {
        v5->start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))cinfo->mem->alloc_sarray(
                                                                                 cinfo,
                                                                                 1,
                                                                                 8
                                                                               * (int)cinfo[10].mem
                                                                               * p_output_message[5]
                                                                               / *p_output_message,
                                                                                 cinfo[10].progress);
        ++v3;
        v5 = (jpeg_c_prep_controller *)((char *)v5 + 4);
        p_output_message += 21;
      }
      while ( v3 < *(_DWORD *)&cinfo[2].is_decompressor );
    }
  }
}
