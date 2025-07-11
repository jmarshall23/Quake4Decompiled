
// FUNC: start_pass_coef
void __cdecl start_pass_coef(jpeg_common_struct *cinfo, J_BUF_MODE pass_mode)
{
  jpeg_c_coef_controller *global_state; // esi
  jpeg_c_coef_controller *v3; // ecx
  jpeg_component_info *err; // ebx
  unsigned __int8 (__cdecl *last_row_height)(jpeg_compress_struct *, unsigned __int8 ***); // ebx

  global_state = (jpeg_c_coef_controller *)cinfo[15].global_state;
  global_state[1].start_pass = 0;
  v3 = (jpeg_c_coef_controller *)cinfo[15].global_state;
  if ( cinfo[10].global_state <= 1 )
  {
    err = (jpeg_component_info *)cinfo[11].err;
    if ( (char *)v3[1].start_pass >= (char *)(*(_DWORD *)&cinfo[10].is_decompressor - 1) )
      last_row_height = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))err->last_row_height;
    else
      last_row_height = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))err->v_samp_factor;
    v3[2].compress_data = last_row_height;
  }
  else
  {
    v3[2].compress_data = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))1;
  }
  v3[1].compress_data = 0;
  v3[2].start_pass = 0;
  if ( pass_mode )
  {
    if ( pass_mode == JBUF_CRANK_DEST )
    {
      if ( !global_state[8].start_pass )
      {
        cinfo->err->msg_code = 4;
        cinfo->err->error_exit(cinfo);
      }
      global_state->compress_data = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))compress_output;
    }
    else if ( pass_mode == JBUF_SAVE_AND_PASS )
    {
      if ( !global_state[8].start_pass )
      {
        cinfo->err->msg_code = 4;
        cinfo->err->error_exit(cinfo);
      }
      global_state->compress_data = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))compress_first_pass;
    }
    else
    {
      cinfo->err->msg_code = 4;
      cinfo->err->error_exit(cinfo);
    }
  }
  else
  {
    if ( global_state[8].start_pass )
    {
      cinfo->err->msg_code = 4;
      cinfo->err->error_exit(cinfo);
    }
    global_state->compress_data = compress_data;
  }
}

// FUNC: _jinit_c_coef_controller
void __cdecl jinit_c_coef_controller(jpeg_common_struct *cinfo, unsigned __int8 need_full_buffer)
{
  jpeg_c_coef_controller *v2; // eax
  jpeg_c_coef_controller *v3; // ebx
  int *p_format_message; // esi
  jpeg_c_coef_controller *v5; // ebx
  jpeg_memory_mgr *mem; // ebp
  int v7; // eax
  char *v8; // eax
  int v9; // [esp-10h] [ebp-18h]
  int need_full_buffera; // [esp+10h] [ebp+8h]

  v2 = (jpeg_c_coef_controller *)cinfo->mem->alloc_small(cinfo, 1, 104);
  v3 = v2;
  cinfo[15].global_state = (int)v2;
  v2->start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))start_pass_coef;
  if ( need_full_buffer )
  {
    need_full_buffera = 0;
    if ( *(int *)&cinfo[2].is_decompressor > 0 )
    {
      p_format_message = (int *)&cinfo[3].err->format_message;
      v5 = v2 + 8;
      do
      {
        mem = cinfo->mem;
        v9 = jround_up(p_format_message[5], *p_format_message);
        v7 = jround_up(p_format_message[4], *(p_format_message - 1));
        v5->start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))((int (__cdecl *)(jpeg_common_struct *, int, _DWORD, int, int))mem->request_virt_barray)(
                                                                                 cinfo,
                                                                                 1,
                                                                                 0,
                                                                                 v7,
                                                                                 v9);
        v5 = (jpeg_c_coef_controller *)((char *)v5 + 4);
        p_format_message += 21;
        ++need_full_buffera;
      }
      while ( need_full_buffera < *(_DWORD *)&cinfo[2].is_decompressor );
    }
  }
  else
  {
    v8 = (char *)cinfo->mem->alloc_large(cinfo, 1, 1280);
    v3[3].compress_data = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))(v8 + 128);
    v3[4].start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))(v8 + 256);
    v3[4].compress_data = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))(v8 + 384);
    v3[5].start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))(v8 + 512);
    v3[5].compress_data = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))(v8 + 640);
    v3[6].start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))(v8 + 768);
    v3[3].start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))v8;
    v3[6].compress_data = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))(v8 + 896);
    v3[7].start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))(v8 + 1024);
    v3[7].compress_data = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, unsigned __int8 ***))(v8 + 1152);
    v3[8].start_pass = 0;
  }
}
