
// FUNC: _jpeg_free_small
void __cdecl jpeg_free_small(jpeg_common_struct *cinfo, void *object)
{
  free(object);
}

// FUNC: _jpeg_get_small
void *__cdecl jpeg_get_small(jpeg_common_struct *cinfo, unsigned int sizeofobject)
{
  return malloc(sizeofobject);
}

// FUNC: _jpeg_mem_available
int __cdecl jpeg_mem_available(jpeg_common_struct *cinfo, int min_bytes_needed, int max_bytes_needed)
{
  return max_bytes_needed;
}

// FUNC: _jpeg_open_backing_store
void __cdecl jpeg_open_backing_store(jpeg_common_struct *cinfo)
{
  cinfo->err->msg_code = 46;
  cinfo->err->error_exit(cinfo);
}
