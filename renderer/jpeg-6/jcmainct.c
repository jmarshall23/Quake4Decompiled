
// FUNC: _jinit_c_main_controller
void __cdecl jinit_c_main_controller(jpeg_common_struct *cinfo, unsigned __int8 need_full_buffer)
{
  jpeg_c_main_controller *v2; // eax
  int v3; // ebp
  unsigned int *v4; // edi
  jpeg_c_main_controller *v5; // ebx

  v2 = (jpeg_c_main_controller *)cinfo->mem->alloc_small(cinfo, 1, 64);
  cinfo[15].progress = (jpeg_progress_mgr *)v2;
  v2->start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))start_pass_main;
  if ( !LOBYTE(cinfo[8].progress) )
  {
    if ( need_full_buffer )
    {
      cinfo->err->msg_code = 4;
      cinfo->err->error_exit(cinfo);
    }
    else
    {
      v3 = 0;
      if ( *(int *)&cinfo[2].is_decompressor > 0 )
      {
        v4 = (unsigned int *)&cinfo[3].err->msg_parm.i[1];
        v5 = v2 + 3;
        do
        {
          v5->start_pass = (void (__cdecl *)(jpeg_compress_struct *, J_BUF_MODE))cinfo->mem->alloc_sarray(
                                                                                   cinfo,
                                                                                   1,
                                                                                   8 * *v4,
                                                                                   8 * *(v4 - 4));
          ++v3;
          v5 = (jpeg_c_main_controller *)((char *)v5 + 4);
          v4 += 21;
        }
        while ( v3 < *(_DWORD *)&cinfo[2].is_decompressor );
      }
    }
  }
}
