
// FUNC: _jpeg_read_scanlines
jpeg_decompress_struct *__cdecl jpeg_read_scanlines(
        jpeg_decompress_struct *cinfo,
        unsigned __int8 **scanlines,
        unsigned int max_lines)
{
  jpeg_decompress_struct *v3; // esi
  unsigned int output_scanline; // ecx
  jpeg_decompress_struct *result; // eax
  jpeg_progress_mgr *progress; // eax
  jpeg_d_main_controller *main; // eax

  v3 = cinfo;
  if ( cinfo->global_state != 205 )
  {
    cinfo->err->msg_code = 17;
    v3->err->msg_parm.i[0] = v3->global_state;
    v3->err->error_exit((jpeg_common_struct *)v3);
  }
  output_scanline = v3->output_scanline;
  if ( output_scanline < v3->output_height )
  {
    progress = v3->progress;
    if ( progress )
    {
      progress->pass_counter = output_scanline;
      v3->progress->pass_limit = v3->output_height;
      v3->progress->progress_monitor((jpeg_common_struct *)v3);
    }
    main = v3->main;
    cinfo = 0;
    main->process_data(v3, scanlines, (unsigned int *)&cinfo, max_lines);
    result = cinfo;
    v3->output_scanline += (unsigned int)cinfo;
  }
  else
  {
    v3->err->msg_code = 117;
    v3->err->emit_message((jpeg_common_struct *)v3, -1);
    return 0;
  }
  return result;
}

// FUNC: _jpeg_start_decompress
unsigned __int8 __cdecl jpeg_start_decompress(jpeg_decompress_struct *cinfo)
{
  int global_state; // eax

  if ( cinfo->global_state == 202 )
  {
    jinit_master_decompress(cinfo);
    if ( cinfo->buffered_image )
    {
      cinfo->global_state = 207;
      return 1;
    }
    cinfo->global_state = 203;
  }
  global_state = cinfo->global_state;
  if ( global_state == 203 )
  {
    if ( cinfo->inputctl->has_multiple_scans )
    {
      cinfo->err->msg_code = 45;
      cinfo->err->error_exit((jpeg_common_struct *)cinfo);
    }
    cinfo->output_scan_number = cinfo->input_scan_number;
    return output_pass_setup(cinfo);
  }
  else
  {
    if ( global_state != 204 )
    {
      cinfo->err->msg_code = 17;
      cinfo->err->msg_parm.i[0] = cinfo->global_state;
      cinfo->err->error_exit((jpeg_common_struct *)cinfo);
    }
    return output_pass_setup(cinfo);
  }
}
