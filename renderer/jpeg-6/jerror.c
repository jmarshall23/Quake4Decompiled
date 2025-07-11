
// FUNC: error_exit
void __cdecl error_exit(jpeg_common_struct *cinfo)
{
  char buffer[200]; // [esp+4h] [ebp-C8h] BYREF

  cinfo->err->format_message(cinfo, buffer);
  jpeg_destroy(cinfo);
  jpg_Error("%s\n", buffer);
}

// FUNC: output_message
void __cdecl output_message(jpeg_common_struct *cinfo)
{
  char buffer[200]; // [esp+0h] [ebp-C8h] BYREF

  cinfo->err->format_message(cinfo, buffer);
  jpg_Printf("%s\n", buffer);
}

// FUNC: emit_message
void __cdecl emit_message(jpeg_common_struct *cinfo, int msg_level)
{
  jpeg_error_mgr *err; // esi

  err = cinfo->err;
  if ( msg_level >= 0 )
  {
    if ( err->trace_level >= msg_level )
      err->output_message(cinfo);
  }
  else
  {
    if ( !err->num_warnings || err->trace_level >= 3 )
      err->output_message(cinfo);
    ++err->num_warnings;
  }
}

// FUNC: format_message
void __cdecl format_message(jpeg_common_struct *cinfo, char *buffer)
{
  jpeg_error_mgr *err; // eax
  int msg_code; // ecx
  const char *v4; // esi
  const char *const *addon_message_table; // esi
  int first_addon_message; // edx
  char v7; // cl
  char *v8; // edx

  err = cinfo->err;
  msg_code = cinfo->err->msg_code;
  if ( msg_code <= 0 || msg_code > err->last_jpeg_message )
  {
    addon_message_table = err->addon_message_table;
    if ( !addon_message_table )
      goto LABEL_9;
    first_addon_message = err->first_addon_message;
    if ( msg_code < first_addon_message || msg_code > err->last_addon_message )
      goto LABEL_9;
    v4 = addon_message_table[msg_code - first_addon_message];
  }
  else
  {
    v4 = err->jpeg_message_table[msg_code];
  }
  if ( !v4 )
  {
LABEL_9:
    err->msg_parm.i[0] = msg_code;
    v4 = *err->jpeg_message_table;
  }
  v7 = *v4;
  v8 = (char *)v4;
  if ( !*v4 )
    goto LABEL_13;
  while ( 1 )
  {
    ++v8;
    if ( v7 == 37 )
      break;
    v7 = *v8;
    if ( !*v8 )
      goto LABEL_13;
  }
  if ( *v8 == 115 )
    sprintf(buffer, v4, &err->msg_parm);
  else
LABEL_13:
    sprintf(
      buffer,
      v4,
      err->msg_parm.i[0],
      err->msg_parm.i[1],
      err->msg_parm.i[2],
      err->msg_parm.i[3],
      err->msg_parm.i[4],
      err->msg_parm.i[5],
      err->msg_parm.i[6],
      err->msg_parm.i[7]);
}

// FUNC: reset_error_mgr
void __cdecl reset_error_mgr(jpeg_common_struct *cinfo)
{
  cinfo->err->num_warnings = 0;
  cinfo->err->msg_code = 0;
}

// FUNC: _jpeg_std_error
jpeg_error_mgr *__cdecl jpeg_std_error(jpeg_error_mgr *err)
{
  jpeg_error_mgr *result; // eax

  result = err;
  err->error_exit = error_exit;
  err->emit_message = emit_message;
  err->output_message = output_message;
  err->format_message = format_message;
  err->reset_error_mgr = reset_error_mgr;
  err->trace_level = 0;
  err->num_warnings = 0;
  err->msg_code = 0;
  err->jpeg_message_table = jpeg_std_message_table;
  err->last_jpeg_message = 117;
  err->addon_message_table = 0;
  err->first_addon_message = 0;
  err->last_addon_message = 0;
  return result;
}
