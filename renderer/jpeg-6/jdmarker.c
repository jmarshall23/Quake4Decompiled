
// FUNC: _jpeg_resync_to_restart
unsigned __int8 __cdecl jpeg_resync_to_restart(jpeg_common_struct *cinfo, int desired)
{
  int global_state; // edi
  int v3; // ebx
  int v4; // ebx
  int v5; // ebx

  global_state = cinfo[18].global_state;
  cinfo->err->msg_code = 115;
  cinfo->err->msg_parm.i[0] = global_state;
  cinfo->err->msg_parm.i[1] = desired;
  cinfo->err->emit_message(cinfo, -1);
  while ( 1 )
  {
    if ( global_state < 192 )
    {
LABEL_3:
      v3 = 2;
      goto LABEL_12;
    }
    if ( global_state < 208
      || global_state > 215
      || global_state == (((_BYTE)desired + 1) & 7) + 208
      || global_state == (((_BYTE)desired + 2) & 7) + 208 )
    {
      v3 = 3;
    }
    else
    {
      if ( global_state == (((_BYTE)desired - 1) & 7) + 208 || global_state == (((_BYTE)desired - 2) & 7) + 208 )
        goto LABEL_3;
      v3 = 1;
    }
LABEL_12:
    cinfo->err->msg_code = 94;
    cinfo->err->msg_parm.i[0] = global_state;
    cinfo->err->msg_parm.i[1] = v3;
    cinfo->err->emit_message(cinfo, 4);
    v4 = v3 - 1;
    if ( !v4 )
      break;
    v5 = v4 - 1;
    if ( v5 )
    {
      if ( v5 == 1 )
        return 1;
    }
    else
    {
      if ( !next_marker(cinfo) )
        return 0;
      global_state = cinfo[18].global_state;
    }
  }
  cinfo[18].global_state = 0;
  return 1;
}

// FUNC: reset_marker_reader
void __cdecl reset_marker_reader(jpeg_decompress_struct *cinfo)
{
  jpeg_marker_reader *marker; // edx

  marker = cinfo->marker;
  cinfo->comp_info = 0;
  cinfo->input_scan_number = 0;
  cinfo->unread_marker = 0;
  marker->saw_SOI = 0;
  cinfo->marker->saw_SOF = 0;
  cinfo->marker->discarded_bytes = 0;
}

// FUNC: _jinit_marker_reader
void __cdecl jinit_marker_reader(jpeg_common_struct *cinfo)
{
  jpeg_marker_reader *v1; // eax
  int i; // eax
  jpeg_marker_reader *err; // ecx

  v1 = (jpeg_marker_reader *)cinfo->mem->alloc_small(cinfo, 0, 92);
  cinfo[20].err = (jpeg_error_mgr *)v1;
  v1->reset_marker_reader = reset_marker_reader;
  cinfo[20].err->emit_message = (void (__cdecl *)(jpeg_common_struct *, int))read_markers;
  cinfo[20].err->output_message = (void (__cdecl *)(jpeg_common_struct *))read_restart_marker;
  cinfo[20].err->format_message = (void (__cdecl *)(jpeg_common_struct *, char *))skip_variable;
  for ( i = 16; i < 80; i += 4 )
    *(void (__cdecl **)(jpeg_common_struct *))((char *)&cinfo[20].err->error_exit + i) = (void (__cdecl *)(jpeg_common_struct *))skip_variable;
  cinfo[20].err->reset_error_mgr = (void (__cdecl *)(jpeg_common_struct *))get_app0;
  *(_DWORD *)&cinfo[20].err->msg_parm.s[48] = get_app14;
  err = (jpeg_marker_reader *)cinfo[20].err;
  cinfo[9].global_state = 0;
  cinfo[6].mem = 0;
  cinfo[18].global_state = 0;
  err->saw_SOI = 0;
  cinfo[20].err->msg_parm.s[57] = 0;
  *(_DWORD *)&cinfo[20].err->msg_parm.s[64] = 0;
}
