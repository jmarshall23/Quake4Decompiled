
// FUNC: latch_quant_tables
void __usercall latch_quant_tables(jpeg_common_struct *cinfo@<ebx>)
{
  jpeg_component_info *v1; // ebp
  unsigned int quant_tbl_no; // esi
  JQUANT_TBL *v3; // eax
  jpeg_component_info **p_is_decompressor; // [esp+0h] [ebp-8h]
  int ci; // [esp+4h] [ebp-4h]

  ci = 0;
  if ( (int)cinfo[14].progress > 0 )
  {
    p_is_decompressor = (jpeg_component_info **)&cinfo[14].is_decompressor;
    do
    {
      v1 = *p_is_decompressor;
      if ( !(*p_is_decompressor)->quant_table )
      {
        quant_tbl_no = v1->quant_tbl_no;
        if ( quant_tbl_no > 3 || !*((_DWORD *)&cinfo[7].mem + quant_tbl_no) )
        {
          cinfo->err->msg_code = 49;
          cinfo->err->msg_parm.i[0] = quant_tbl_no;
          cinfo->err->error_exit(cinfo);
        }
        v3 = (JQUANT_TBL *)cinfo->mem->alloc_small(cinfo, 1, 130);
        qmemcpy(v3, *((const void **)&cinfo[7].mem + quant_tbl_no), sizeof(JQUANT_TBL));
        v1->quant_table = v3;
      }
      ++p_is_decompressor;
      ++ci;
    }
    while ( ci < (int)cinfo[14].progress );
  }
}

// FUNC: reset_input_controller
void __cdecl reset_input_controller(jpeg_common_struct *cinfo)
{
  jpeg_input_controller *global_state; // eax

  global_state = (jpeg_input_controller *)cinfo[19].global_state;
  global_state->consume_input = consume_markers;
  global_state->has_multiple_scans = 0;
  global_state->eoi_reached = 0;
  LOBYTE(global_state[1].consume_input) = 1;
  cinfo->err->reset_error_mgr(cinfo);
  cinfo[20].err->error_exit(cinfo);
  cinfo[7].err = 0;
}

// FUNC: finish_input_pass
void __cdecl finish_input_pass(jpeg_decompress_struct *cinfo)
{
  cinfo->inputctl->consume_input = consume_markers;
}

// FUNC: _jinit_input_controller
void __cdecl jinit_input_controller(jpeg_common_struct *cinfo)
{
  int v1; // eax

  v1 = cinfo->mem->alloc_small(cinfo, 0, 24);
  cinfo[19].global_state = v1;
  *(_DWORD *)v1 = consume_markers;
  *(_DWORD *)(v1 + 4) = reset_input_controller;
  *(_DWORD *)(v1 + 8) = start_input_pass_0;
  *(_DWORD *)(v1 + 12) = finish_input_pass;
  *(_BYTE *)(v1 + 16) = 0;
  *(_BYTE *)(v1 + 17) = 0;
  *(_BYTE *)(v1 + 20) = 1;
}
