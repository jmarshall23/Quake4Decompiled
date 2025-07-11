
// FUNC: _jpeg_calc_output_dimensions
void __cdecl jpeg_calc_output_dimensions(jpeg_common_struct *cinfo)
{
  J_COLOR_SPACE err; // eax
  unsigned int progress; // edx
  bool v3; // zf
  int v4; // eax

  if ( cinfo->global_state != 202 )
  {
    cinfo->err->msg_code = 17;
    cinfo->err->msg_parm.i[0] = cinfo->global_state;
    cinfo->err->error_exit(cinfo);
  }
  err = (J_COLOR_SPACE)cinfo[2].err;
  progress = (unsigned int)cinfo[1].progress;
  *(_DWORD *)&cinfo[4].is_decompressor = cinfo[1].mem;
  cinfo[4].global_state = progress;
  switch ( err )
  {
    case JCS_GRAYSCALE:
      cinfo[5].err = (jpeg_error_mgr *)1;
      break;
    case JCS_RGB:
    case JCS_CMYK:
    case JCS_YCCK:
      cinfo[5].err = (jpeg_error_mgr *)4;
      break;
    case JCS_YCbCr:
      cinfo[5].err = (jpeg_error_mgr *)3;
      break;
    default:
      cinfo[5].err = *(jpeg_error_mgr **)&cinfo[1].is_decompressor;
      break;
  }
  v3 = *(&cinfo[3].is_decompressor + 2) == 0;
  cinfo[5].progress = (jpeg_progress_mgr *)1;
  v4 = 1;
  if ( v3 )
    v4 = (int)cinfo[5].err;
  cinfo[5].mem = (jpeg_memory_mgr *)v4;
}

// FUNC: prepare_range_limit_table
void __usercall prepare_range_limit_table(jpeg_common_struct *cinfo@<eax>)
{
  unsigned __int8 *v2; // edx
  int v3; // eax
  unsigned __int8 *v4; // edx

  v2 = (unsigned __int8 *)(cinfo->mem->alloc_small(cinfo, 1, 1408) + 256);
  v3 = 0;
  cinfo[14].mem = (jpeg_memory_mgr *)v2;
  memset(v2 - 256, 0, 0x100u);
  do
  {
    v2[v3] = v3;
    ++v3;
  }
  while ( v3 <= 255 );
  v4 = v2 + 128;
  memset(v4 + 128, 0xFFu, 0x180u);
  memset(v4 + 512, 0, 0x180u);
  qmemcpy(v4 + 896, cinfo[14].mem, 0x80u);
}

// FUNC: master_selection
void __usercall master_selection(jpeg_common_struct *cinfo@<esi>)
{
  jpeg_decomp_master *err; // edi
  unsigned __int8 v2; // al
  jpeg_decompress_struct *v3; // [esp+0h] [ebp-10h]
  unsigned __int8 use_c_buffer; // [esp+Ch] [ebp-4h]

  err = (jpeg_decomp_master *)cinfo[19].err;
  jpeg_calc_output_dimensions(v3);
  prepare_range_limit_table(cinfo);
  err[1].prepare_for_output_pass = 0;
  LOBYTE(err[1].finish_output_pass) = 0;
  *(_DWORD *)&err[1].is_dummy_pass = 0;
  err[2].prepare_for_output_pass = 0;
  v2 = *(&cinfo[3].is_decompressor + 2);
  if ( !v2 || !LOBYTE(cinfo[3].mem) )
  {
    LOBYTE(cinfo[4].progress) = 0;
    BYTE1(cinfo[4].progress) = 0;
    BYTE2(cinfo[4].progress) = 0;
  }
  if ( v2 )
  {
    if ( BYTE1(cinfo[3].mem) )
    {
      cinfo->err->msg_code = 44;
      cinfo->err->error_exit(cinfo);
    }
    if ( cinfo[5].err == (jpeg_error_mgr *)3 )
    {
      if ( cinfo[5].global_state )
      {
        BYTE1(cinfo[4].progress) = 1;
        goto LABEL_10;
      }
      if ( LOBYTE(cinfo[4].err) )
      {
        BYTE2(cinfo[4].progress) = 1;
        goto LABEL_10;
      }
    }
    else
    {
      BYTE1(cinfo[4].progress) = 0;
      BYTE2(cinfo[4].progress) = 0;
      cinfo[5].global_state = 0;
    }
    LOBYTE(cinfo[4].progress) = 1;
LABEL_10:
    if ( LOBYTE(cinfo[4].progress) )
    {
      cinfo->err->msg_code = 45;
      cinfo->err->error_exit(cinfo);
    }
    if ( BYTE2(cinfo[4].progress) || BYTE1(cinfo[4].progress) )
    {
      cinfo->err->msg_code = 45;
      cinfo->err->error_exit(cinfo);
    }
  }
  if ( !BYTE1(cinfo[3].mem) )
  {
    if ( LOBYTE(err[1].finish_output_pass) )
    {
      cinfo->err->msg_code = 45;
      cinfo->err->error_exit(cinfo);
    }
    else
    {
      jinit_color_deconverter((jpeg_decompress_struct *)cinfo);
      jinit_upsampler((jpeg_decompress_struct *)cinfo);
    }
    jinit_d_post_controller((jpeg_decompress_struct *)cinfo, BYTE2(cinfo[4].progress));
  }
  jinit_inverse_dct((jpeg_decompress_struct *)cinfo);
  if ( BYTE1(cinfo[10].err) )
  {
    cinfo->err->msg_code = 1;
    cinfo->err->error_exit(cinfo);
  }
  else if ( LOBYTE(cinfo[10].err) )
  {
    cinfo->err->msg_code = 45;
    cinfo->err->error_exit(cinfo);
  }
  else
  {
    jinit_huff_decoder((jpeg_decompress_struct *)cinfo);
  }
  if ( *(_BYTE *)(cinfo[19].global_state + 16) || (use_c_buffer = 0, LOBYTE(cinfo[3].mem)) )
    use_c_buffer = 1;
  jinit_d_coef_controller((jpeg_decompress_struct *)cinfo, use_c_buffer);
  if ( !BYTE1(cinfo[3].mem) )
    jinit_d_main_controller((jpeg_decompress_struct *)cinfo, 0);
  cinfo->mem->realize_virt_arrays(cinfo);
  (*(void (__cdecl **)(jpeg_common_struct *))(cinfo[19].global_state + 8))(cinfo);
}

// FUNC: prepare_for_output_pass
void __cdecl prepare_for_output_pass(jpeg_common_struct *cinfo)
{
  jpeg_decomp_master *err; // edi
  int v2; // edx
  jpeg_progress_mgr *progress; // eax

  err = (jpeg_decomp_master *)cinfo[19].err;
  if ( err->is_dummy_pass )
  {
    cinfo->err->msg_code = 45;
    cinfo->err->error_exit(cinfo);
  }
  else
  {
    if ( *(&cinfo[3].is_decompressor + 2) && !cinfo[5].global_state )
    {
      if ( LOBYTE(cinfo[4].err) && BYTE2(cinfo[4].progress) )
      {
        cinfo[21].err = (jpeg_error_mgr *)err[2].prepare_for_output_pass;
        err->is_dummy_pass = 1;
      }
      else if ( LOBYTE(cinfo[4].progress) )
      {
        cinfo[21].err = *(jpeg_error_mgr **)&err[1].is_dummy_pass;
      }
      else
      {
        cinfo->err->msg_code = 43;
        cinfo->err->error_exit(cinfo);
      }
    }
    cinfo[20].progress->progress_monitor(cinfo);
    ((void (__cdecl *)(jpeg_common_struct *))cinfo[19].progress->pass_limit)(cinfo);
    if ( !BYTE1(cinfo[3].mem) )
    {
      if ( !LOBYTE(err[1].finish_output_pass) )
        (*(void (__cdecl **)(jpeg_common_struct *))cinfo[20].global_state)(cinfo);
      (**(void (__cdecl ***)(jpeg_common_struct *))&cinfo[20].is_decompressor)(cinfo);
      if ( *(&cinfo[3].is_decompressor + 2) )
      {
        LOBYTE(v2) = err->is_dummy_pass;
        ((void (__cdecl *)(jpeg_common_struct *, int))cinfo[21].err->error_exit)(cinfo, v2);
      }
      (**(void (__cdecl ***)(jpeg_common_struct *, int))&cinfo[19].is_decompressor)(
        cinfo,
        err->is_dummy_pass != 0 ? 3 : 0);
      ((void (__cdecl *)(jpeg_common_struct *, _DWORD))cinfo[19].mem->alloc_small)(cinfo, 0);
    }
  }
  progress = cinfo->progress;
  if ( progress )
  {
    progress->completed_passes = (int)err[1].prepare_for_output_pass;
    cinfo->progress->total_passes = (int)err[1].prepare_for_output_pass + (err->is_dummy_pass != 0) + 1;
    if ( LOBYTE(cinfo[3].mem) )
    {
      if ( !*(_BYTE *)(cinfo[19].global_state + 17) )
        cinfo->progress->total_passes += (BYTE2(cinfo[4].progress) != 0) + 1;
    }
  }
}

// FUNC: finish_output_pass
void __cdecl finish_output_pass(jpeg_decompress_struct *cinfo)
{
  jpeg_decomp_master *master; // esi

  master = cinfo->master;
  if ( cinfo->quantize_colors )
    cinfo->cquantize->finish_pass(cinfo);
  ++master[1].prepare_for_output_pass;
}

// FUNC: _jinit_master_decompress
void __cdecl jinit_master_decompress(jpeg_common_struct *cinfo)
{
  jpeg_decomp_master *v1; // eax

  v1 = (jpeg_decomp_master *)cinfo->mem->alloc_small(cinfo, 1, 28);
  cinfo[19].err = (jpeg_error_mgr *)v1;
  v1->prepare_for_output_pass = (void (__cdecl *)(jpeg_decompress_struct *))prepare_for_output_pass;
  v1->finish_output_pass = finish_output_pass;
  v1->is_dummy_pass = 0;
  master_selection(cinfo);
}
