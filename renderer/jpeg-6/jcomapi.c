
// FUNC: _jpeg_abort
void __cdecl jpeg_abort(jpeg_common_struct *cinfo)
{
  cinfo->mem->free_pool(cinfo, 1);
  cinfo->global_state = cinfo->is_decompressor != 0 ? 200 : 100;
}

// FUNC: _jpeg_destroy
void __cdecl jpeg_destroy(jpeg_common_struct *cinfo)
{
  jpeg_memory_mgr *mem; // eax

  mem = cinfo->mem;
  if ( mem )
    mem->self_destruct(cinfo);
  cinfo->mem = 0;
  cinfo->global_state = 0;
}

// FUNC: _jpeg_alloc_quant_table
JQUANT_TBL *__cdecl jpeg_alloc_quant_table(jpeg_common_struct *cinfo)
{
  JQUANT_TBL *result; // eax

  result = (JQUANT_TBL *)cinfo->mem->alloc_small(cinfo, 0, 130);
  result->sent_table = 0;
  return result;
}

// FUNC: _jpeg_alloc_huff_table
JHUFF_TBL *__cdecl jpeg_alloc_huff_table(jpeg_common_struct *cinfo)
{
  JHUFF_TBL *result; // eax

  result = (JHUFF_TBL *)cinfo->mem->alloc_small(cinfo, 0, 274);
  result->sent_table = 0;
  return result;
}
