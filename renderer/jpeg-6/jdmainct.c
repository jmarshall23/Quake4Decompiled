
// FUNC: alloc_funny_pointers
void __usercall alloc_funny_pointers(jpeg_common_struct *cinfo@<esi>)
{
  int global_state; // ebp
  jpeg_d_main_controller *mem; // edi
  int v3; // eax
  int v4; // ebx
  int *v5; // ebp
  int v6; // edi
  int v7; // eax
  int v8; // [esp+Ch] [ebp-Ch]
  int rgroup; // [esp+10h] [ebp-8h]
  my_main_controller *main; // [esp+14h] [ebp-4h]

  global_state = cinfo[13].global_state;
  mem = (jpeg_d_main_controller *)cinfo[19].mem;
  main = (my_main_controller *)mem;
  v3 = cinfo->mem->alloc_small(cinfo, 1, 8 * *(_DWORD *)&cinfo[1].is_decompressor);
  mem[7].start_pass = (void (__cdecl *)(jpeg_decompress_struct *, J_BUF_MODE))v3;
  mem[7].process_data = (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 **, unsigned int *, unsigned int))(v3 + 4 * *(_DWORD *)&cinfo[1].is_decompressor);
  v4 = 0;
  if ( *(int *)&cinfo[1].is_decompressor > 0 )
  {
    v8 = global_state + 4;
    v5 = (int *)(cinfo[9].global_state + 12);
    do
    {
      v6 = *v5 * v5[6] / cinfo[13].global_state * v8;
      rgroup = *v5 * v5[6] / cinfo[13].global_state;
      v7 = cinfo->mem->alloc_small(cinfo, 1, 8 * v6) + 4 * rgroup;
      main->buffer[8][v4] = (unsigned __int8 *)v7;
      main->buffer[9][v4++] = (unsigned __int8 *)(v7 + 4 * v6);
      v5 += 21;
    }
    while ( v4 < *(_DWORD *)&cinfo[1].is_decompressor );
  }
}

// FUNC: make_funny_pointers
void __cdecl make_funny_pointers(jpeg_decompress_struct *cinfo)
{
  jpeg_decompress_struct *v1; // ecx
  int v2; // ebp
  jpeg_d_main_controller *v3; // esi
  jpeg_component_info *comp_info; // eax
  int *p_v_samp_factor; // edx
  int v6; // eax
  unsigned __int8 **v7; // edi
  void (__cdecl *start_pass)(jpeg_decompress_struct *, J_BUF_MODE); // ebx
  int v9; // edx
  _DWORD *v10; // ecx
  int v11; // edi
  _DWORD *v12; // esi
  int v13; // edi
  _DWORD *v14; // ecx
  int v15; // edx
  int v16; // ebx
  unsigned __int8 **v17; // ecx
  int ci; // [esp+8h] [ebp-20h]
  jpeg_d_main_controller *v19; // [esp+Ch] [ebp-1Ch]
  int *v20; // [esp+10h] [ebp-18h]
  int v21; // [esp+14h] [ebp-14h]
  int M; // [esp+18h] [ebp-10h]
  unsigned __int8 **xbuf0; // [esp+1Ch] [ebp-Ch]
  my_main_controller *main; // [esp+20h] [ebp-8h]
  char *v25; // [esp+24h] [ebp-4h]

  v1 = cinfo;
  v2 = 0;
  v3 = cinfo->main;
  M = cinfo->min_DCT_scaled_size;
  comp_info = cinfo->comp_info;
  main = (my_main_controller *)v3;
  ci = 0;
  if ( cinfo->num_components > 0 )
  {
    p_v_samp_factor = &comp_info->v_samp_factor;
    v20 = &comp_info->v_samp_factor;
    v19 = v3 + 1;
    while ( 1 )
    {
      v6 = *p_v_samp_factor * p_v_samp_factor[6] / v1->min_DCT_scaled_size;
      v7 = (unsigned __int8 **)*((_DWORD *)v3[7].start_pass + v2);
      start_pass = v19->start_pass;
      v9 = *((_DWORD *)v3[7].process_data + v2);
      xbuf0 = v7;
      if ( v6 * (M + 2) > 0 )
      {
        v10 = (_DWORD *)*((_DWORD *)v3[7].process_data + v2);
        v25 = (char *)v7 - v9;
        v21 = v6 * (M + 2);
        do
        {
          v11 = *(_DWORD *)((char *)start_pass + (_DWORD)v10 - v9);
          *v10 = v11;
          *(_DWORD *)((char *)v10++ + (_DWORD)v25) = v11;
          --v21;
        }
        while ( v21 );
        v7 = xbuf0;
        v2 = ci;
        v1 = cinfo;
      }
      if ( 2 * v6 > 0 )
      {
        v12 = (_DWORD *)(v9 + 4 * M * v6);
        v13 = (int)start_pass - v9;
        v14 = (_DWORD *)((char *)start_pass + 4 * v6 * (M - 2));
        v15 = v9 - (_DWORD)start_pass;
        v16 = 2 * v6;
        do
        {
          *(_DWORD *)((char *)v14 + v15) = *(_DWORD *)((char *)v12 + v13);
          *v12++ = *v14++;
          --v16;
        }
        while ( v16 );
        v7 = xbuf0;
        v2 = ci;
        v1 = cinfo;
      }
      if ( v6 > 0 )
      {
        v17 = &v7[-v6];
        do
        {
          *v17++ = *v7;
          --v6;
        }
        while ( v6 );
        v1 = cinfo;
      }
      v19 = (jpeg_d_main_controller *)((char *)v19 + 4);
      v20 += 21;
      ci = ++v2;
      if ( v2 >= v1->num_components )
        break;
      p_v_samp_factor = v20;
      v3 = (jpeg_d_main_controller *)main;
    }
  }
}

// FUNC: set_wraparound_pointers
void __cdecl set_wraparound_pointers(jpeg_decompress_struct *cinfo)
{
  jpeg_decompress_struct *v1; // ebx
  int v2; // esi
  jpeg_d_main_controller *v3; // edi
  int *p_v_samp_factor; // ebp
  int v5; // eax
  int v6; // ecx
  _DWORD *v7; // edi
  _DWORD *v8; // ebx
  _DWORD *v9; // edx
  _DWORD *v10; // esi
  int v11; // ecx
  int ci; // [esp+10h] [ebp-10h]
  int *v13; // [esp+14h] [ebp-Ch]
  my_main_controller *main; // [esp+18h] [ebp-8h]
  int M; // [esp+1Ch] [ebp-4h]

  v1 = cinfo;
  v2 = 0;
  v3 = cinfo->main;
  main = (my_main_controller *)v3;
  M = cinfo->min_DCT_scaled_size;
  ci = 0;
  if ( cinfo->num_components > 0 )
  {
    p_v_samp_factor = &cinfo->comp_info->v_samp_factor;
    v13 = p_v_samp_factor;
    while ( 1 )
    {
      v5 = *p_v_samp_factor * p_v_samp_factor[6] / v1->min_DCT_scaled_size;
      v6 = *((_DWORD *)v3[7].start_pass + v2);
      v7 = (_DWORD *)*((_DWORD *)v3[7].process_data + v2);
      if ( v5 > 0 )
      {
        v8 = &v7[v5 * (M + 2)];
        v9 = &v7[-v5];
        v10 = &v7[v5 * (M + 1)];
        v11 = v6 - (_DWORD)v7;
        do
        {
          *(_DWORD *)((char *)v9 + v11) = *(_DWORD *)((char *)v10 + v11);
          *v9 = *v10;
          *(_DWORD *)((char *)v8 + v11) = *(_DWORD *)((char *)v7 + v11);
          *v8 = *v7;
          ++v10;
          ++v9;
          ++v7;
          ++v8;
          --v5;
        }
        while ( v5 );
        v2 = ci;
        v1 = cinfo;
        p_v_samp_factor = v13;
      }
      ++v2;
      p_v_samp_factor += 21;
      ci = v2;
      v13 = p_v_samp_factor;
      if ( v2 >= v1->num_components )
        break;
      v3 = (jpeg_d_main_controller *)main;
    }
  }
}

// FUNC: set_bottom_pointers
void __cdecl set_bottom_pointers(jpeg_decompress_struct *cinfo)
{
  jpeg_decompress_struct *v1; // esi
  int v2; // ebp
  int *p_v_samp_factor; // ebx
  int v4; // edi
  unsigned int v5; // esi
  int v6; // edx
  int v7; // ecx
  _DWORD *v8; // eax
  jpeg_d_main_controller *main; // [esp+Ch] [ebp-4h]

  v1 = cinfo;
  v2 = 0;
  main = cinfo->main;
  if ( cinfo->num_components > 0 )
  {
    p_v_samp_factor = &cinfo->comp_info->v_samp_factor;
    while ( 1 )
    {
      v4 = *p_v_samp_factor * p_v_samp_factor[6] / v1->min_DCT_scaled_size;
      v5 = p_v_samp_factor[8] % (unsigned int)(*p_v_samp_factor * p_v_samp_factor[6]);
      if ( !v5 )
        v5 = *p_v_samp_factor * p_v_samp_factor[6];
      if ( !v2 )
        main[9].start_pass = (void (__cdecl *)(jpeg_decompress_struct *, J_BUF_MODE))((int)(v5 - 1) / v4 + 1);
      v6 = 2 * v4;
      if ( 2 * v4 > 0 )
      {
        v7 = *(_DWORD *)(*((_DWORD *)&main[7].start_pass + (int)main[8].start_pass) + 4 * v2) + 4 * v5;
        v8 = (_DWORD *)v7;
        do
        {
          *v8++ = *(_DWORD *)(v7 - 4);
          --v6;
        }
        while ( v6 );
      }
      ++v2;
      p_v_samp_factor += 21;
      if ( v2 >= cinfo->num_components )
        break;
      v1 = cinfo;
    }
  }
}

// FUNC: process_data_context_main
void __cdecl process_data_context_main(
        jpeg_decompress_struct *cinfo,
        unsigned __int8 **output_buf,
        unsigned int *out_row_ctr,
        unsigned int out_rows_avail)
{
  jpeg_d_main_controller *main; // esi
  void (__cdecl *process_data)(jpeg_decompress_struct *, unsigned __int8 **, unsigned int *, unsigned int); // eax
  char *v6; // eax
  void (__cdecl *v7)(jpeg_decompress_struct *, unsigned __int8 **, unsigned int *, unsigned int); // edx

  main = cinfo->main;
  if ( !LOBYTE(main[6].start_pass) )
  {
    if ( !cinfo->coef->decompress_data(
            cinfo,
            (unsigned __int8 ***)*((_DWORD *)&main[7].start_pass + (int)main[8].start_pass)) )
      return;
    ++main[9].process_data;
    LOBYTE(main[6].start_pass) = 1;
  }
  process_data = main[8].process_data;
  if ( !process_data )
  {
LABEL_9:
    v7 = main[9].process_data;
    main[6].process_data = 0;
    main[9].start_pass = (void (__cdecl *)(jpeg_decompress_struct *, J_BUF_MODE))(cinfo->min_DCT_scaled_size - 1);
    if ( v7 == (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 **, unsigned int *, unsigned int))cinfo->total_iMCU_rows )
      set_bottom_pointers(cinfo);
    main[8].process_data = (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 **, unsigned int *, unsigned int))1;
    goto LABEL_12;
  }
  v6 = (char *)process_data - 1;
  if ( v6 )
  {
    if ( v6 != (char *)1 )
      return;
    cinfo->post->post_process_data(
      cinfo,
      (unsigned __int8 ***)*((_DWORD *)&main[7].start_pass + (int)main[8].start_pass),
      (unsigned int *)&main[6].process_data,
      (unsigned int)main[9].start_pass,
      output_buf,
      out_row_ctr,
      out_rows_avail);
    if ( (char *)main[6].process_data < (char *)main[9].start_pass )
      return;
    main[8].process_data = 0;
    if ( *out_row_ctr >= out_rows_avail )
      return;
    goto LABEL_9;
  }
LABEL_12:
  cinfo->post->post_process_data(
    cinfo,
    (unsigned __int8 ***)*((_DWORD *)&main[7].start_pass + (int)main[8].start_pass),
    (unsigned int *)&main[6].process_data,
    (unsigned int)main[9].start_pass,
    output_buf,
    out_row_ctr,
    out_rows_avail);
  if ( (char *)main[6].process_data >= (char *)main[9].start_pass )
  {
    if ( main[9].process_data == (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 **, unsigned int *, unsigned int))1 )
      set_wraparound_pointers(cinfo);
    main[8].start_pass = (void (__cdecl *)(jpeg_decompress_struct *, J_BUF_MODE))((int)main[8].start_pass ^ 1);
    LOBYTE(main[6].start_pass) = 0;
    main[6].process_data = (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 **, unsigned int *, unsigned int))(cinfo->min_DCT_scaled_size + 1);
    main[9].start_pass = (void (__cdecl *)(jpeg_decompress_struct *, J_BUF_MODE))(cinfo->min_DCT_scaled_size + 2);
    main[8].process_data = (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 **, unsigned int *, unsigned int))2;
  }
}

// FUNC: _jinit_d_main_controller
void __cdecl jinit_d_main_controller(jpeg_common_struct *cinfo, unsigned __int8 need_full_buffer)
{
  jpeg_d_main_controller *v2; // ebx
  int global_state; // eax
  int v4; // ebp
  int *v5; // edi
  jpeg_d_main_controller *v6; // ebx
  int need_full_buffera; // [esp+14h] [ebp+8h]

  v2 = (jpeg_d_main_controller *)cinfo->mem->alloc_small(cinfo, 1, 80);
  cinfo[19].mem = (jpeg_memory_mgr *)v2;
  v2->start_pass = start_pass_main_0;
  if ( need_full_buffer )
  {
    cinfo->err->msg_code = 4;
    cinfo->err->error_exit(cinfo);
  }
  if ( *(_BYTE *)(*(_DWORD *)&cinfo[20].is_decompressor + 8) )
  {
    if ( cinfo[13].global_state < 2 )
    {
      cinfo->err->msg_code = 44;
      cinfo->err->error_exit(cinfo);
    }
    alloc_funny_pointers(cinfo);
    global_state = cinfo[13].global_state + 2;
  }
  else
  {
    global_state = cinfo[13].global_state;
  }
  v4 = 0;
  need_full_buffera = global_state;
  if ( *(int *)&cinfo[1].is_decompressor > 0 )
  {
    v5 = (int *)(cinfo[9].global_state + 36);
    v6 = v2 + 1;
    do
    {
      v6->start_pass = (void (__cdecl *)(jpeg_decompress_struct *, J_BUF_MODE))cinfo->mem->alloc_sarray(
                                                                                 cinfo,
                                                                                 1,
                                                                                 *v5 * *(v5 - 2),
                                                                                 need_full_buffera
                                                                               * (*v5
                                                                                * *(v5 - 6)
                                                                                / cinfo[13].global_state));
      ++v4;
      v6 = (jpeg_d_main_controller *)((char *)v6 + 4);
      v5 += 21;
    }
    while ( v4 < *(_DWORD *)&cinfo[1].is_decompressor );
  }
}
