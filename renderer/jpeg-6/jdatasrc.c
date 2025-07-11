
// FUNC: _jpeg_stdio_src
void __cdecl jpeg_stdio_src(jpeg_common_struct *cinfo, unsigned __int8 *infile)
{
  jpeg_source_mgr *v2; // eax
  jpeg_memory_mgr *mem; // ecx
  jpeg_source_mgr *err; // eax

  if ( !cinfo[1].err )
  {
    v2 = (jpeg_source_mgr *)cinfo->mem->alloc_small(cinfo, 0, 40);
    mem = cinfo->mem;
    cinfo[1].err = (jpeg_error_mgr *)v2;
    v2[1].bytes_in_buffer = (int)mem->alloc_small(cinfo, 0, 4096u);
  }
  err = (jpeg_source_mgr *)cinfo[1].err;
  err->init_source = init_source;
  err->fill_input_buffer = fill_input_buffer_0;
  err->skip_input_data = skip_input_data_0;
  err->resync_to_restart = jpeg_resync_to_restart;
  err->term_source = (void (__cdecl *)(jpeg_decompress_struct *))SpawnStub;
  err[1].next_input_byte = infile;
  err->bytes_in_buffer = 0;
  err->next_input_byte = 0;
}
