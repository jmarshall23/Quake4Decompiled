
// FUNC: _jpeg_create_compress
void __cdecl jpeg_create_compress(jpeg_common_struct *cinfo)
{
  jpeg_error_mgr *err; // edx

  err = cinfo->err;
  memset(cinfo, 0, 0x158u);
  cinfo->err = err;
  cinfo->is_decompressor = 0;
  jinit_memory_mgr(cinfo);
  cinfo->progress = 0;
  cinfo[1].err = 0;
  cinfo[3].err = 0;
  cinfo[3].mem = 0;
  cinfo[3].progress = 0;
  *(_DWORD *)&cinfo[3].is_decompressor = 0;
  cinfo[3].global_state = 0;
  cinfo[4].err = 0;
  cinfo[4].global_state = 0;
  cinfo[4].mem = 0;
  cinfo[5].err = 0;
  cinfo[4].progress = 0;
  cinfo[5].mem = 0;
  *(_DWORD *)&cinfo[4].is_decompressor = 0;
  cinfo[5].progress = 0;
  *(double *)&cinfo[2].err = 1.0;
  cinfo->global_state = 100;
}

// FUNC: _jpeg_destroy_decompress
// attributes: thunk
void __cdecl jpeg_destroy_decompress(jpeg_common_struct *cinfo)
{
  jpeg_destroy(cinfo);
}

// FUNC: _jpeg_suppress_tables
void __cdecl jpeg_suppress_tables(jpeg_compress_struct *cinfo, unsigned __int8 suppress)
{
  JQUANT_TBL *v2; // ecx
  JQUANT_TBL *v3; // ecx
  JQUANT_TBL *v4; // ecx
  JQUANT_TBL *v5; // ecx
  JHUFF_TBL **ac_huff_tbl_ptrs; // eax
  int v7; // esi
  int v8; // ecx

  v2 = cinfo->quant_tbl_ptrs[0];
  if ( v2 )
    v2->sent_table = suppress;
  v3 = cinfo->quant_tbl_ptrs[1];
  if ( v3 )
    v3->sent_table = suppress;
  v4 = cinfo->quant_tbl_ptrs[2];
  if ( v4 )
    v4->sent_table = suppress;
  v5 = cinfo->quant_tbl_ptrs[3];
  if ( v5 )
    v5->sent_table = suppress;
  ac_huff_tbl_ptrs = cinfo->ac_huff_tbl_ptrs;
  v7 = 4;
  do
  {
    v8 = (int)*(ac_huff_tbl_ptrs - 4);
    if ( v8 )
      *(_BYTE *)(v8 + 273) = suppress;
    if ( *ac_huff_tbl_ptrs )
      (*ac_huff_tbl_ptrs)->sent_table = suppress;
    ++ac_huff_tbl_ptrs;
    --v7;
  }
  while ( v7 );
}

// FUNC: _jpeg_finish_compress
void __cdecl jpeg_finish_compress(jpeg_common_struct *cinfo)
{
  int global_state; // eax
  jpeg_comp_master *i; // eax
  unsigned int j; // edi

  global_state = cinfo->global_state;
  if ( global_state == 101 || global_state == 102 )
  {
    if ( (jpeg_progress_mgr *)cinfo[9].global_state < cinfo[1].progress )
    {
      cinfo->err->msg_code = 64;
      cinfo->err->error_exit(cinfo);
    }
    ((void (__cdecl *)(jpeg_common_struct *))cinfo[15].mem->alloc_sarray)(cinfo);
  }
  else if ( global_state != 103 )
  {
    cinfo->err->msg_code = 17;
    cinfo->err->msg_parm.i[0] = cinfo->global_state;
    cinfo->err->error_exit(cinfo);
  }
  for ( i = (jpeg_comp_master *)cinfo[15].mem; !i->is_last_pass; i = (jpeg_comp_master *)cinfo[15].mem )
  {
    i->prepare_for_pass((jpeg_compress_struct *)cinfo);
    for ( j = 0; j < *(_DWORD *)&cinfo[10].is_decompressor; ++j )
    {
      if ( cinfo->progress )
      {
        cinfo->progress->pass_counter = j;
        cinfo->progress->pass_limit = *(_DWORD *)&cinfo[10].is_decompressor;
        cinfo->progress->progress_monitor(cinfo);
      }
      if ( !(*(unsigned __int8 (__cdecl **)(jpeg_common_struct *, _DWORD))(cinfo[15].global_state + 4))(cinfo, 0) )
      {
        cinfo->err->msg_code = 20;
        cinfo->err->error_exit(cinfo);
      }
    }
    ((void (__cdecl *)(jpeg_common_struct *))cinfo[15].mem->alloc_sarray)(cinfo);
  }
  cinfo[16].err->reset_error_mgr(cinfo);
  cinfo[1].err->reset_error_mgr(cinfo);
  jpeg_abort(cinfo);
}
