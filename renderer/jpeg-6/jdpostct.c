
// FUNC: post_process_1pass
void __cdecl post_process_1pass(
        jpeg_decompress_struct *cinfo,
        unsigned __int8 ***input_buf,
        unsigned int *in_row_group_ctr,
        unsigned int in_row_groups_avail,
        unsigned __int8 **output_buf,
        unsigned int *out_row_ctr,
        unsigned int out_rows_avail)
{
  unsigned int *v7; // ebx
  void (__cdecl *start_pass)(jpeg_decompress_struct *, J_BUF_MODE); // eax
  jpeg_decompress_struct *v9; // esi
  jpeg_d_post_controller *post; // edi
  jpeg_upsampler *upsample; // ecx

  v7 = out_row_ctr;
  start_pass = (void (__cdecl *)(jpeg_decompress_struct *, J_BUF_MODE))(out_rows_avail - *out_row_ctr);
  v9 = cinfo;
  post = cinfo->post;
  if ( (char *)start_pass > (char *)post[2].start_pass )
    start_pass = post[2].start_pass;
  upsample = cinfo->upsample;
  cinfo = 0;
  upsample->upsample(
    v9,
    input_buf,
    in_row_group_ctr,
    in_row_groups_avail,
    (unsigned __int8 **)post[1].post_process_data,
    (unsigned int *)&cinfo,
    (unsigned int)start_pass);
  v9->cquantize->color_quantize(v9, (unsigned __int8 **)post[1].post_process_data, &output_buf[*v7], (int)cinfo);
  *v7 += (unsigned int)cinfo;
}

// FUNC: start_pass_dpost
void __cdecl start_pass_dpost(jpeg_common_struct *cinfo, J_BUF_MODE pass_mode)
{
  jpeg_d_post_controller *v2; // esi
  bool v3; // zf
  unsigned __int8 **v4; // eax

  v2 = *(jpeg_d_post_controller **)&cinfo[19].is_decompressor;
  if ( pass_mode )
  {
    cinfo->err->msg_code = 4;
    cinfo->err->error_exit(cinfo);
    v2[3].start_pass = 0;
    v2[2].post_process_data = 0;
    return;
  }
  if ( *(&cinfo[3].is_decompressor + 2) )
  {
    v3 = v2[1].post_process_data == 0;
    v2->post_process_data = post_process_1pass;
    if ( v3 )
    {
      v4 = cinfo->mem->access_virt_sarray(cinfo, v2[1].start_pass, 0, v2[2].start_pass, 1);
      v2[3].start_pass = 0;
      v2[2].post_process_data = 0;
      v2[1].post_process_data = (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 ***, unsigned int *, unsigned int, unsigned __int8 **, unsigned int *, unsigned int))v4;
      return;
    }
  }
  else
  {
    v2->post_process_data = *(void (__cdecl **)(jpeg_decompress_struct *, unsigned __int8 ***, unsigned int *, unsigned int, unsigned __int8 **, unsigned int *, unsigned int))(*(_DWORD *)&cinfo[20].is_decompressor + 4);
  }
  v2[3].start_pass = 0;
  v2[2].post_process_data = 0;
}

// FUNC: _jinit_d_post_controller
void __cdecl jinit_d_post_controller(jpeg_common_struct *cinfo, unsigned __int8 need_full_buffer)
{
  jpeg_d_post_controller *v2; // edi
  int v3; // eax

  v2 = (jpeg_d_post_controller *)cinfo->mem->alloc_small(cinfo, 1, 28);
  *(_DWORD *)&cinfo[19].is_decompressor = v2;
  v2->start_pass = (void (__cdecl *)(jpeg_decompress_struct *, J_BUF_MODE))start_pass_dpost;
  v2[1].start_pass = 0;
  v2[1].post_process_data = 0;
  if ( *(&cinfo[3].is_decompressor + 2) )
  {
    v3 = *(_DWORD *)&cinfo[13].is_decompressor;
    v2[2].start_pass = (void (__cdecl *)(jpeg_decompress_struct *, J_BUF_MODE))v3;
    if ( need_full_buffer )
    {
      cinfo->err->msg_code = 4;
      cinfo->err->error_exit(cinfo);
    }
    else
    {
      v2[1].post_process_data = (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 ***, unsigned int *, unsigned int, unsigned __int8 **, unsigned int *, unsigned int))cinfo->mem->alloc_sarray(cinfo, 1, *(_DWORD *)&cinfo[4].is_decompressor * (int)cinfo[5].err, v3);
    }
  }
}
