
// FUNC: start_output_pass
void __cdecl start_output_pass(jpeg_decompress_struct *cinfo)
{
  cinfo->output_iMCU_row = 0;
}

// FUNC: _jinit_d_coef_controller
void __cdecl jinit_d_coef_controller(jpeg_common_struct *cinfo, unsigned __int8 need_full_buffer)
{
  jpeg_d_coef_controller *v2; // esi
  char *v3; // eax

  v2 = (jpeg_d_coef_controller *)cinfo->mem->alloc_small(cinfo, 1, 72);
  cinfo[19].progress = (jpeg_progress_mgr *)v2;
  v2->start_input_pass = start_input_pass;
  v2->start_output_pass = start_output_pass;
  if ( need_full_buffer )
  {
    cinfo->err->msg_code = 45;
    cinfo->err->error_exit(cinfo);
  }
  else
  {
    v3 = (char *)cinfo->mem->alloc_large(cinfo, 1, 1280);
    v2[1].coef_arrays = (jvirt_barray_control **)(v3 + 128);
    v2[2].start_input_pass = (void (__cdecl *)(jpeg_decompress_struct *))(v3 + 256);
    v2[2].consume_data = (int (__cdecl *)(jpeg_decompress_struct *))(v3 + 384);
    v2[2].start_output_pass = (void (__cdecl *)(jpeg_decompress_struct *))(v3 + 512);
    v2[2].decompress_data = (int (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 ***))(v3 + 640);
    v2[2].coef_arrays = (jvirt_barray_control **)(v3 + 768);
    v2[1].decompress_data = (int (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 ***))v3;
    v2[3].start_input_pass = (void (__cdecl *)(jpeg_decompress_struct *))(v3 + 896);
    v2[3].consume_data = (int (__cdecl *)(jpeg_decompress_struct *))(v3 + 1024);
    v2[3].start_output_pass = (void (__cdecl *)(jpeg_decompress_struct *))(v3 + 1152);
    v2->consume_data = (int (__cdecl *)(jpeg_decompress_struct *))idFile_Common::Timestamp;
    v2->decompress_data = decompress_onepass;
    v2->coef_arrays = 0;
  }
}
