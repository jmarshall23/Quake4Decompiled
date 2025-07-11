
// FUNC: _jpeg_create_decompress
void __cdecl jpeg_create_decompress(jpeg_common_struct *cinfo)
{
  jpeg_error_mgr *err; // edx

  err = cinfo->err;
  memset(cinfo, 0, 0x1A8u);
  cinfo->err = err;
  cinfo->is_decompressor = 1;
  jinit_memory_mgr(cinfo);
  cinfo->progress = 0;
  cinfo[1].err = 0;
  cinfo[7].mem = 0;
  cinfo[7].progress = 0;
  *(_DWORD *)&cinfo[7].is_decompressor = 0;
  cinfo[7].global_state = 0;
  cinfo[8].err = 0;
  cinfo[8].global_state = 0;
  cinfo[8].mem = 0;
  cinfo[9].err = 0;
  cinfo[8].progress = 0;
  cinfo[9].mem = 0;
  *(_DWORD *)&cinfo[8].is_decompressor = 0;
  cinfo[9].progress = 0;
  jinit_marker_reader((jpeg_decompress_struct *)cinfo);
  jinit_input_controller((jpeg_decompress_struct *)cinfo);
  cinfo->global_state = 200;
}

// FUNC: default_decompress_parms
void __usercall default_decompress_parms(jpeg_common_struct *cinfo@<esi>)
{
  jpeg_component_info *global_state; // eax
  int component_id; // ecx
  int v3; // edx
  int v4; // edi
  $985051285AB838B711572F193DE40719 *p_msg_parm; // eax

  switch ( *(_DWORD *)&cinfo[1].is_decompressor )
  {
    case 1:
      cinfo[1].global_state = 1;
      cinfo[2].err = (jpeg_error_mgr *)1;
      break;
    case 3:
      if ( LOBYTE(cinfo[12].global_state) )
        goto LABEL_16;
      if ( BYTE2(cinfo[13].err) )
      {
        if ( HIBYTE(cinfo[13].err) )
        {
          if ( HIBYTE(cinfo[13].err) != 1 )
          {
            cinfo->err->msg_code = 108;
            cinfo->err->msg_parm.i[0] = HIBYTE(cinfo[13].err);
            cinfo->err->emit_message(cinfo, -1);
            cinfo[1].global_state = 3;
            cinfo[2].err = (jpeg_error_mgr *)2;
            break;
          }
LABEL_16:
          cinfo[1].global_state = 3;
          cinfo[2].err = (jpeg_error_mgr *)2;
          break;
        }
LABEL_17:
        cinfo[1].global_state = 2;
        cinfo[2].err = (jpeg_error_mgr *)2;
        break;
      }
      global_state = (jpeg_component_info *)cinfo[9].global_state;
      component_id = global_state->component_id;
      v3 = global_state[1].component_id;
      v4 = global_state[2].component_id;
      if ( global_state->component_id == 1 )
      {
        if ( v3 == 2 && v4 == 3 )
        {
          cinfo[1].global_state = 3;
          cinfo[2].err = (jpeg_error_mgr *)2;
          break;
        }
      }
      else if ( component_id == 82 && v3 == 71 && v4 == 66 )
      {
        goto LABEL_17;
      }
      p_msg_parm = &cinfo->err->msg_parm;
      p_msg_parm->i[0] = component_id;
      p_msg_parm->i[1] = v3;
      p_msg_parm->i[2] = v4;
      cinfo->err->msg_code = 105;
      cinfo->err->emit_message(cinfo, 1);
      cinfo[1].global_state = 3;
      cinfo[2].err = (jpeg_error_mgr *)2;
      break;
    case 4:
      if ( BYTE2(cinfo[13].err) && HIBYTE(cinfo[13].err) )
      {
        if ( HIBYTE(cinfo[13].err) != 2 )
        {
          cinfo->err->msg_code = 108;
          cinfo->err->msg_parm.i[0] = HIBYTE(cinfo[13].err);
          cinfo->err->emit_message(cinfo, -1);
        }
        cinfo[1].global_state = 5;
        cinfo[2].err = (jpeg_error_mgr *)4;
      }
      else
      {
        cinfo[1].global_state = 4;
        cinfo[2].err = (jpeg_error_mgr *)4;
      }
      break;
    default:
      cinfo[1].global_state = 0;
      cinfo[2].err = 0;
      break;
  }
  cinfo[2].mem = (jpeg_memory_mgr *)1;
  *(double *)&cinfo[2].global_state = 1.0;
  cinfo[2].progress = (jpeg_progress_mgr *)1;
  LOBYTE(cinfo[3].mem) = 0;
  BYTE1(cinfo[3].mem) = 0;
  *(&cinfo[3].is_decompressor + 2) = 0;
  LOBYTE(cinfo[4].err) = 0;
  cinfo[5].global_state = 0;
  LOBYTE(cinfo[4].progress) = 0;
  BYTE1(cinfo[4].progress) = 0;
  BYTE2(cinfo[4].progress) = 0;
  cinfo[3].progress = (jpeg_progress_mgr *)2;
  cinfo[3].is_decompressor = 1;
  *(&cinfo[3].is_decompressor + 1) = 1;
  cinfo[3].global_state = 2;
  cinfo[4].mem = (jpeg_memory_mgr *)256;
}

// FUNC: _jpeg_consume_input
int __cdecl jpeg_consume_input(jpeg_decompress_struct *cinfo)
{
  int v1; // edi
  int result; // eax

  v1 = 0;
  switch ( cinfo->global_state )
  {
    case 0xC8:
      cinfo->inputctl->reset_input_controller(cinfo);
      cinfo->src->init_source(cinfo);
      cinfo->global_state = 201;
      goto $L2764;
    case 0xC9:
$L2764:
      v1 = cinfo->inputctl->consume_input(cinfo);
      if ( v1 != 1 )
        goto LABEL_8;
      default_decompress_parms((jpeg_common_struct *)cinfo);
      result = 1;
      cinfo->global_state = 202;
      break;
    case 0xCA:
      return 1;
    case 0xCB:
    case 0xCC:
    case 0xCD:
    case 0xCE:
    case 0xCF:
    case 0xD0:
    case 0xD2:
      return cinfo->inputctl->consume_input(cinfo);
    default:
      cinfo->err->msg_code = 17;
      cinfo->err->msg_parm.i[0] = cinfo->global_state;
      cinfo->err->error_exit((jpeg_common_struct *)cinfo);
LABEL_8:
      result = v1;
      break;
  }
  return result;
}

// FUNC: _jpeg_finish_decompress
unsigned __int8 __cdecl jpeg_finish_decompress(jpeg_common_struct *cinfo)
{
  int global_state; // eax

  global_state = cinfo->global_state;
  if ( (global_state == 205 || global_state == 206) && !LOBYTE(cinfo[3].mem) )
  {
    if ( cinfo[6].err < (jpeg_error_mgr *)cinfo[4].global_state )
    {
      cinfo->err->msg_code = 64;
      cinfo->err->error_exit(cinfo);
    }
    ((void (__cdecl *)(jpeg_common_struct *))cinfo[19].err->emit_message)(cinfo);
    cinfo->global_state = 210;
  }
  else if ( global_state == 207 )
  {
    cinfo->global_state = 210;
  }
  else if ( global_state != 210 )
  {
    cinfo->err->msg_code = 17;
    cinfo->err->msg_parm.i[0] = cinfo->global_state;
    cinfo->err->error_exit(cinfo);
  }
  if ( *(_BYTE *)(cinfo[19].global_state + 17) )
  {
LABEL_14:
    ((void (__cdecl *)(jpeg_common_struct *))cinfo[1].err->msg_parm.i[0])(cinfo);
    jpeg_abort(cinfo);
    return 1;
  }
  else
  {
    while ( (*(int (__cdecl **)(jpeg_common_struct *))cinfo[19].global_state)(cinfo) )
    {
      if ( *(_BYTE *)(cinfo[19].global_state + 17) )
        goto LABEL_14;
    }
    return 0;
  }
}

// FUNC: _jpeg_read_header
int __cdecl jpeg_read_header(jpeg_common_struct *cinfo, unsigned __int8 require_image)
{
  int global_state; // eax
  int result; // eax

  global_state = cinfo->global_state;
  if ( global_state != 200 && global_state != 201 )
  {
    cinfo->err->msg_code = 17;
    cinfo->err->msg_parm.i[0] = cinfo->global_state;
    cinfo->err->error_exit(cinfo);
  }
  result = jpeg_consume_input((jpeg_decompress_struct *)cinfo);
  if ( result == 1 )
    return 1;
  if ( result == 2 )
  {
    if ( require_image )
    {
      cinfo->err->msg_code = 48;
      cinfo->err->error_exit(cinfo);
    }
    jpeg_abort(cinfo);
    return 2;
  }
  return result;
}
