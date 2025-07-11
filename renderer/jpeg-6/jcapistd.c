
// FUNC: _jpeg_start_compress
void __cdecl jpeg_start_compress(jpeg_common_struct *cinfo, unsigned __int8 write_all_tables)
{
  bool v2; // zf

  if ( cinfo->global_state != 100 )
  {
    cinfo->err->msg_code = 17;
    cinfo->err->msg_parm.i[0] = cinfo->global_state;
    cinfo->err->error_exit(cinfo);
  }
  if ( write_all_tables )
    jpeg_suppress_tables((jpeg_compress_struct *)cinfo, 0);
  cinfo->err->reset_error_mgr(cinfo);
  cinfo[1].err->output_message(cinfo);
  jinit_compress_master((jpeg_compress_struct *)cinfo);
  ((void (__cdecl *)(jpeg_common_struct *))cinfo[15].mem->alloc_small)(cinfo);
  v2 = LOBYTE(cinfo[8].progress) == 0;
  cinfo[9].global_state = 0;
  cinfo->global_state = !v2 + 101;
}

// FUNC: _jpeg_write_scanlines
jpeg_compress_struct *__cdecl jpeg_write_scanlines(
        jpeg_compress_struct *cinfo,
        unsigned __int8 **scanlines,
        unsigned int num_lines)
{
  jpeg_compress_struct *v3; // esi
  jpeg_progress_mgr *progress; // eax
  jpeg_comp_master *master; // eax
  int v6; // ecx
  jpeg_c_main_controller *main; // edx
  jpeg_compress_struct *result; // eax

  v3 = cinfo;
  if ( cinfo->global_state != 101 )
  {
    cinfo->err->msg_code = 17;
    v3->err->msg_parm.i[0] = v3->global_state;
    v3->err->error_exit((jpeg_common_struct *)v3);
  }
  if ( v3->next_scanline >= v3->image_height )
  {
    v3->err->msg_code = 117;
    v3->err->emit_message((jpeg_common_struct *)v3, -1);
  }
  progress = v3->progress;
  if ( progress )
  {
    progress->pass_counter = v3->next_scanline;
    v3->progress->pass_limit = v3->image_height;
    v3->progress->progress_monitor((jpeg_common_struct *)v3);
  }
  master = v3->master;
  if ( master->call_pass_startup )
    master->pass_startup(v3);
  v6 = num_lines;
  if ( num_lines > v3->image_height - v3->next_scanline )
    v6 = v3->image_height - v3->next_scanline;
  main = v3->main;
  cinfo = 0;
  main->process_data(v3, scanlines, (unsigned int *)&cinfo, v6);
  result = cinfo;
  v3->next_scanline += (unsigned int)cinfo;
  return result;
}
