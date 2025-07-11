
// FUNC: _jinit_compress_master
void __cdecl jinit_compress_master(jpeg_compress_struct *cinfo)
{
  bool v1; // al

  jinit_c_master_control(cinfo, 0);
  if ( !cinfo->raw_data_in )
  {
    jinit_color_converter((jpeg_common_struct *)cinfo);
    jinit_downsampler(cinfo);
    jinit_c_prep_controller(cinfo, 0);
  }
  jinit_forward_dct((jpeg_common_struct *)cinfo);
  if ( cinfo->arith_code )
  {
    cinfo->err->msg_code = 1;
    cinfo->err->error_exit((jpeg_common_struct *)cinfo);
  }
  else if ( cinfo->progressive_mode )
  {
    jinit_phuff_encoder(cinfo);
  }
  else
  {
    jinit_huff_encoder((jpeg_common_struct *)cinfo);
  }
  v1 = cinfo->num_scans > 1 || cinfo->optimize_coding;
  jinit_c_coef_controller((jpeg_common_struct *)cinfo, v1);
  jinit_c_main_controller(cinfo, 0);
  jinit_marker_writer(cinfo);
  cinfo->mem->realize_virt_arrays((jpeg_common_struct *)cinfo);
  cinfo->marker->write_file_header(cinfo);
}
