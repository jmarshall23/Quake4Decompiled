
// FUNC: emit_marker
void __usercall emit_marker(jpeg_common_struct *cinfo@<esi>, JPEG_MARKER mark)
{
  jpeg_destination_mgr *err; // eax
  bool v3; // zf
  jpeg_destination_mgr *v4; // eax

  err = (jpeg_destination_mgr *)cinfo[1].err;
  *err->next_output_byte++ = -1;
  v3 = err->free_in_buffer-- == 1;
  if ( v3 && !err->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v4 = (jpeg_destination_mgr *)cinfo[1].err;
  *v4->next_output_byte++ = mark;
  v3 = v4->free_in_buffer-- == 1;
  if ( v3 && !v4->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
}

// FUNC: emit_2bytes
void __usercall emit_2bytes(jpeg_common_struct *cinfo@<esi>, __int16 value@<bx>)
{
  jpeg_destination_mgr *err; // eax
  bool v3; // zf
  jpeg_destination_mgr *v4; // eax

  err = (jpeg_destination_mgr *)cinfo[1].err;
  *err->next_output_byte++ = HIBYTE(value);
  v3 = err->free_in_buffer-- == 1;
  if ( v3 && !err->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v4 = (jpeg_destination_mgr *)cinfo[1].err;
  *v4->next_output_byte++ = value;
  v3 = v4->free_in_buffer-- == 1;
  if ( v3 && !v4->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
}

// FUNC: emit_dht
void __usercall emit_dht(jpeg_common_struct *cinfo@<eax>, int index, unsigned __int8 is_ac)
{
  JHUFF_TBL *v4; // edi
  int v5; // ebp
  unsigned __int8 *v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // edi
  jpeg_destination_mgr *err; // eax
  bool v11; // zf
  jpeg_destination_mgr *v12; // eax
  jpeg_destination_mgr *v13; // eax
  int i; // edi
  jpeg_destination_mgr *v15; // eax
  int j; // edi
  jpeg_destination_mgr *v17; // eax
  JHUFF_TBL *is_aca; // [esp+10h] [ebp+8h]

  if ( is_ac )
  {
    v4 = (JHUFF_TBL *)*(&cinfo[4].global_state + index);
    is_aca = v4;
    index += 16;
  }
  else
  {
    is_aca = (JHUFF_TBL *)*((_DWORD *)&cinfo[4].err + index);
    v4 = is_aca;
  }
  if ( !v4 )
  {
    cinfo->err->msg_code = 47;
    cinfo->err->msg_parm.i[0] = index;
    cinfo->err->error_exit(cinfo);
  }
  if ( !v4->sent_table )
  {
    emit_marker(cinfo, M_DHT);
    v5 = 0;
    v6 = &v4->bits[3];
    v7 = 4;
    do
    {
      v8 = v6[1] + *(v6 - 1) + *(v6 - 2);
      v9 = v5 + *v6;
      v6 += 4;
      --v7;
      v5 = v9 + v8;
    }
    while ( v7 );
    err = (jpeg_destination_mgr *)cinfo[1].err;
    *err->next_output_byte++ = (unsigned __int16)(v5 + 19) >> 8;
    v11 = err->free_in_buffer-- == 1;
    if ( v11 && !err->empty_output_buffer((jpeg_compress_struct *)cinfo) )
    {
      cinfo->err->msg_code = 20;
      cinfo->err->error_exit(cinfo);
    }
    v12 = (jpeg_destination_mgr *)cinfo[1].err;
    *v12->next_output_byte++ = v5 + 19;
    v11 = v12->free_in_buffer-- == 1;
    if ( v11 && !v12->empty_output_buffer((jpeg_compress_struct *)cinfo) )
    {
      cinfo->err->msg_code = 20;
      cinfo->err->error_exit(cinfo);
    }
    v13 = (jpeg_destination_mgr *)cinfo[1].err;
    *v13->next_output_byte++ = index;
    v11 = v13->free_in_buffer-- == 1;
    if ( v11 && !v13->empty_output_buffer((jpeg_compress_struct *)cinfo) )
    {
      cinfo->err->msg_code = 20;
      cinfo->err->error_exit(cinfo);
    }
    for ( i = 1; i <= 16; ++i )
    {
      v15 = (jpeg_destination_mgr *)cinfo[1].err;
      *v15->next_output_byte++ = is_aca->bits[i];
      v11 = v15->free_in_buffer-- == 1;
      if ( v11 && !v15->empty_output_buffer((jpeg_compress_struct *)cinfo) )
      {
        cinfo->err->msg_code = 20;
        cinfo->err->error_exit(cinfo);
      }
    }
    for ( j = 0; j < v5; ++j )
    {
      v17 = (jpeg_destination_mgr *)cinfo[1].err;
      *v17->next_output_byte++ = is_aca->huffval[j];
      v11 = v17->free_in_buffer-- == 1;
      if ( v11 && !v17->empty_output_buffer((jpeg_compress_struct *)cinfo) )
      {
        cinfo->err->msg_code = 20;
        cinfo->err->error_exit(cinfo);
      }
    }
    is_aca->sent_table = 1;
  }
}

// FUNC: emit_sof
void __usercall emit_sof(jpeg_common_struct *cinfo@<ecx>, JPEG_MARKER code@<eax>)
{
  jpeg_destination_mgr *err; // eax
  bool v4; // zf
  jpeg_destination_mgr *v5; // eax
  jpeg_component_info *v6; // edi
  int i; // ebx
  jpeg_destination_mgr *v8; // eax
  jpeg_destination_mgr *v9; // eax
  jpeg_destination_mgr *v10; // eax

  emit_marker(cinfo, code);
  emit_2bytes(cinfo, 3 * *(_WORD *)&cinfo[2].is_decompressor + 8);
  if ( (int)cinfo[1].progress > 0xFFFF || (int)cinfo[1].mem > 0xFFFF )
  {
    cinfo->err->msg_code = 38;
    cinfo->err->msg_parm.i[0] = 0xFFFF;
    cinfo->err->error_exit(cinfo);
  }
  err = (jpeg_destination_mgr *)cinfo[1].err;
  *err->next_output_byte++ = (unsigned __int8)cinfo[2].progress;
  v4 = err->free_in_buffer-- == 1;
  if ( v4 && !err->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  emit_2bytes(cinfo, (__int16)cinfo[1].progress);
  emit_2bytes(cinfo, (__int16)cinfo[1].mem);
  v5 = (jpeg_destination_mgr *)cinfo[1].err;
  *v5->next_output_byte++ = cinfo[2].is_decompressor;
  v4 = v5->free_in_buffer-- == 1;
  if ( v4 && !v5->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v6 = (jpeg_component_info *)cinfo[3].err;
  for ( i = 0; i < *(_DWORD *)&cinfo[2].is_decompressor; ++v6 )
  {
    v8 = (jpeg_destination_mgr *)cinfo[1].err;
    *v8->next_output_byte++ = v6->component_id;
    v4 = v8->free_in_buffer-- == 1;
    if ( v4 && !v8->empty_output_buffer((jpeg_compress_struct *)cinfo) )
    {
      cinfo->err->msg_code = 20;
      cinfo->err->error_exit(cinfo);
    }
    v9 = (jpeg_destination_mgr *)cinfo[1].err;
    *v9->next_output_byte++ = LOBYTE(v6->v_samp_factor) + 16 * LOBYTE(v6->h_samp_factor);
    v4 = v9->free_in_buffer-- == 1;
    if ( v4 && !v9->empty_output_buffer((jpeg_compress_struct *)cinfo) )
    {
      cinfo->err->msg_code = 20;
      cinfo->err->error_exit(cinfo);
    }
    v10 = (jpeg_destination_mgr *)cinfo[1].err;
    *v10->next_output_byte++ = v6->quant_tbl_no;
    v4 = v10->free_in_buffer-- == 1;
    if ( v4 && !v10->empty_output_buffer((jpeg_compress_struct *)cinfo) )
    {
      cinfo->err->msg_code = 20;
      cinfo->err->error_exit(cinfo);
    }
    ++i;
  }
}

// FUNC: emit_sos
void __usercall emit_sos(jpeg_common_struct *cinfo@<eax>)
{
  jpeg_destination_mgr *err; // eax
  bool v3; // zf
  int v4; // ebp
  jpeg_component_info **v5; // ebx
  jpeg_component_info *v6; // edi
  jpeg_destination_mgr *v7; // eax
  int dc_tbl_no; // ecx
  int ac_tbl_no; // edx
  jpeg_destination_mgr *v10; // eax
  jpeg_destination_mgr *v11; // eax
  jpeg_destination_mgr *v12; // eax
  jpeg_destination_mgr *v13; // eax

  emit_marker(cinfo, M_SOS);
  emit_2bytes(cinfo, 2 * LOWORD(cinfo[10].global_state) + 6);
  err = (jpeg_destination_mgr *)cinfo[1].err;
  *err->next_output_byte++ = cinfo[10].global_state;
  v3 = err->free_in_buffer-- == 1;
  if ( v3 && !err->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v4 = 0;
  if ( cinfo[10].global_state > 0 )
  {
    v5 = (jpeg_component_info **)&cinfo[11];
    do
    {
      v6 = *v5;
      v7 = (jpeg_destination_mgr *)cinfo[1].err;
      *v7->next_output_byte++ = (*v5)->component_id;
      v3 = v7->free_in_buffer-- == 1;
      if ( v3 && !v7->empty_output_buffer((jpeg_compress_struct *)cinfo) )
      {
        cinfo->err->msg_code = 20;
        cinfo->err->error_exit(cinfo);
      }
      dc_tbl_no = v6->dc_tbl_no;
      ac_tbl_no = v6->ac_tbl_no;
      if ( LOBYTE(cinfo[10].err) )
      {
        if ( cinfo[14].progress || (LOBYTE(ac_tbl_no) = 0, cinfo[14].global_state) && !BYTE1(cinfo[8].progress) )
          LOBYTE(dc_tbl_no) = 0;
      }
      v10 = (jpeg_destination_mgr *)cinfo[1].err;
      *v10->next_output_byte++ = ac_tbl_no + 16 * dc_tbl_no;
      v3 = v10->free_in_buffer-- == 1;
      if ( v3 && !v10->empty_output_buffer((jpeg_compress_struct *)cinfo) )
      {
        cinfo->err->msg_code = 20;
        cinfo->err->error_exit(cinfo);
      }
      ++v4;
      ++v5;
    }
    while ( v4 < cinfo[10].global_state );
  }
  v11 = (jpeg_destination_mgr *)cinfo[1].err;
  *v11->next_output_byte++ = (unsigned __int8)cinfo[14].progress;
  v3 = v11->free_in_buffer-- == 1;
  if ( v3 && !v11->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v12 = (jpeg_destination_mgr *)cinfo[1].err;
  *v12->next_output_byte++ = cinfo[14].is_decompressor;
  v3 = v12->free_in_buffer-- == 1;
  if ( v3 && !v12->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v13 = (jpeg_destination_mgr *)cinfo[1].err;
  *v13->next_output_byte++ = LOBYTE(cinfo[15].err) + 16 * LOBYTE(cinfo[14].global_state);
  v3 = v13->free_in_buffer-- == 1;
  if ( v3 && !v13->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
}

// FUNC: emit_jfif_app0
void __usercall emit_jfif_app0(jpeg_common_struct *cinfo@<eax>)
{
  jpeg_destination_mgr *err; // eax
  bool v3; // zf
  jpeg_destination_mgr *v4; // eax
  jpeg_destination_mgr *v5; // eax
  jpeg_destination_mgr *v6; // eax
  jpeg_destination_mgr *v7; // eax
  jpeg_destination_mgr *v8; // eax
  jpeg_destination_mgr *v9; // eax
  jpeg_destination_mgr *v10; // eax
  jpeg_destination_mgr *v11; // eax
  jpeg_destination_mgr *v12; // eax

  emit_marker(cinfo, M_APP0);
  emit_2bytes(cinfo, 16);
  err = (jpeg_destination_mgr *)cinfo[1].err;
  *err->next_output_byte++ = 74;
  v3 = err->free_in_buffer-- == 1;
  if ( v3 && !err->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v4 = (jpeg_destination_mgr *)cinfo[1].err;
  *v4->next_output_byte++ = 70;
  v3 = v4->free_in_buffer-- == 1;
  if ( v3 && !v4->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v5 = (jpeg_destination_mgr *)cinfo[1].err;
  *v5->next_output_byte++ = 73;
  v3 = v5->free_in_buffer-- == 1;
  if ( v3 && !v5->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v6 = (jpeg_destination_mgr *)cinfo[1].err;
  *v6->next_output_byte++ = 70;
  v3 = v6->free_in_buffer-- == 1;
  if ( v3 && !v6->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v7 = (jpeg_destination_mgr *)cinfo[1].err;
  *v7->next_output_byte++ = 0;
  v3 = v7->free_in_buffer-- == 1;
  if ( v3 && !v7->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v8 = (jpeg_destination_mgr *)cinfo[1].err;
  *v8->next_output_byte++ = 1;
  v3 = v8->free_in_buffer-- == 1;
  if ( v3 && !v8->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v9 = (jpeg_destination_mgr *)cinfo[1].err;
  *v9->next_output_byte++ = 1;
  v3 = v9->free_in_buffer-- == 1;
  if ( v3 && !v9->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v10 = (jpeg_destination_mgr *)cinfo[1].err;
  *v10->next_output_byte++ = BYTE1(cinfo[9].progress);
  v3 = v10->free_in_buffer-- == 1;
  if ( v3 && !v10->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  emit_2bytes(cinfo, HIWORD(cinfo[9].progress));
  emit_2bytes(cinfo, *(_WORD *)&cinfo[9].is_decompressor);
  v11 = (jpeg_destination_mgr *)cinfo[1].err;
  *v11->next_output_byte++ = 0;
  v3 = v11->free_in_buffer-- == 1;
  if ( v3 && !v11->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v12 = (jpeg_destination_mgr *)cinfo[1].err;
  *v12->next_output_byte++ = 0;
  v3 = v12->free_in_buffer-- == 1;
  if ( v3 && !v12->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
}

// FUNC: emit_adobe_app14
void __usercall emit_adobe_app14(jpeg_common_struct *cinfo@<eax>)
{
  jpeg_destination_mgr *err; // eax
  bool v3; // zf
  jpeg_destination_mgr *v4; // eax
  jpeg_destination_mgr *v5; // eax
  jpeg_destination_mgr *v6; // eax
  jpeg_destination_mgr *v7; // eax
  jpeg_destination_mgr *v8; // eax
  unsigned __int8 *next_output_byte; // ecx

  emit_marker(cinfo, M_APP14);
  emit_2bytes(cinfo, 14);
  err = (jpeg_destination_mgr *)cinfo[1].err;
  *err->next_output_byte++ = 65;
  v3 = err->free_in_buffer-- == 1;
  if ( v3 && !err->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v4 = (jpeg_destination_mgr *)cinfo[1].err;
  *v4->next_output_byte++ = 100;
  v3 = v4->free_in_buffer-- == 1;
  if ( v3 && !v4->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v5 = (jpeg_destination_mgr *)cinfo[1].err;
  *v5->next_output_byte++ = 111;
  v3 = v5->free_in_buffer-- == 1;
  if ( v3 && !v5->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v6 = (jpeg_destination_mgr *)cinfo[1].err;
  *v6->next_output_byte++ = 98;
  v3 = v6->free_in_buffer-- == 1;
  if ( v3 && !v6->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v7 = (jpeg_destination_mgr *)cinfo[1].err;
  *v7->next_output_byte++ = 101;
  v3 = v7->free_in_buffer-- == 1;
  if ( v3 && !v7->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  emit_2bytes(cinfo, 100);
  emit_2bytes(cinfo, 0);
  emit_2bytes(cinfo, 0);
  if ( cinfo[2].global_state == 3 )
  {
    v8 = (jpeg_destination_mgr *)cinfo[1].err;
    *v8->next_output_byte = 1;
  }
  else
  {
    v8 = (jpeg_destination_mgr *)cinfo[1].err;
    next_output_byte = v8->next_output_byte;
    if ( cinfo[2].global_state == 5 )
      *next_output_byte = 2;
    else
      *next_output_byte = 0;
  }
  ++v8->next_output_byte;
  v3 = v8->free_in_buffer-- == 1;
  if ( v3 && !v8->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
}

// FUNC: write_any_marker
void __cdecl write_any_marker(
        jpeg_common_struct *cinfo,
        int marker,
        const unsigned __int8 *dataptr,
        unsigned int datalen)
{
  unsigned int v4; // ebp
  jpeg_destination_mgr *err; // eax

  if ( datalen <= 0xFFFD )
  {
    emit_marker(cinfo, (JPEG_MARKER)marker);
    emit_2bytes(cinfo, datalen + 2);
    if ( datalen )
    {
      v4 = datalen;
      do
      {
        err = (jpeg_destination_mgr *)cinfo[1].err;
        *err->next_output_byte++ = *dataptr;
        if ( err->free_in_buffer-- == 1 && !err->empty_output_buffer((jpeg_compress_struct *)cinfo) )
        {
          cinfo->err->msg_code = 20;
          cinfo->err->error_exit(cinfo);
        }
        ++dataptr;
        --v4;
      }
      while ( v4 );
    }
  }
}

// FUNC: write_file_header
void __cdecl write_file_header(jpeg_common_struct *cinfo)
{
  emit_marker(cinfo, M_SOI);
  if ( LOBYTE(cinfo[9].progress) )
    emit_jfif_app0(cinfo);
  if ( *(&cinfo[9].is_decompressor + 2) )
    emit_adobe_app14(cinfo);
}

// FUNC: write_frame_header
void __cdecl write_frame_header(jpeg_common_struct *cinfo)
{
  int v1; // ebx
  int v2; // edi
  int *p_reset_error_mgr; // ebp
  int v4; // ecx
  char v5; // bl
  int *i; // eax
  int prec; // [esp+Ch] [ebp-4h]

  v1 = 0;
  v2 = 0;
  prec = 0;
  if ( *(int *)&cinfo[2].is_decompressor > 0 )
  {
    p_reset_error_mgr = (int *)&cinfo[3].err->reset_error_mgr;
    do
    {
      ++v2;
      v1 += emit_dqt(cinfo, *p_reset_error_mgr);
      p_reset_error_mgr += 21;
    }
    while ( v2 < *(_DWORD *)&cinfo[2].is_decompressor );
    prec = v1;
  }
  if ( BYTE1(cinfo[8].progress) || LOBYTE(cinfo[10].err) || cinfo[2].progress != (jpeg_progress_mgr *)8 )
  {
    v5 = 0;
  }
  else
  {
    v4 = *(_DWORD *)&cinfo[2].is_decompressor;
    v5 = 1;
    if ( v4 > 0 )
    {
      i = cinfo[3].err->msg_parm.i;
      do
      {
        if ( *(i - 1) > 1 || *i > 1 )
          v5 = 0;
        i += 21;
        --v4;
      }
      while ( v4 );
    }
    if ( prec && v5 )
    {
      cinfo->err->msg_code = 72;
      v5 = 0;
      cinfo->err->emit_message(cinfo, 0);
    }
  }
  if ( BYTE1(cinfo[8].progress) )
  {
    emit_sof(cinfo, M_SOF9);
  }
  else if ( LOBYTE(cinfo[10].err) )
  {
    emit_sof(cinfo, M_SOF2);
  }
  else if ( v5 )
  {
    emit_sof(cinfo, M_SOF0);
  }
  else
  {
    emit_sof(cinfo, M_SOF1);
  }
}

// FUNC: write_scan_header
void __cdecl write_scan_header(jpeg_common_struct *cinfo)
{
  int v1; // ebp
  jpeg_component_info **v2; // ebx
  jpeg_component_info *v3; // edi

  if ( !BYTE1(cinfo[8].progress) )
  {
    v1 = 0;
    if ( cinfo[10].global_state > 0 )
    {
      v2 = (jpeg_component_info **)&cinfo[11];
      do
      {
        v3 = *v2;
        if ( LOBYTE(cinfo[10].err) )
        {
          if ( cinfo[14].progress )
          {
            emit_dht(cinfo, v3->ac_tbl_no, 1u);
          }
          else if ( !cinfo[14].global_state )
          {
            emit_dht(cinfo, v3->dc_tbl_no, 0);
          }
        }
        else
        {
          emit_dht(cinfo, v3->dc_tbl_no, 0);
          emit_dht(cinfo, v3->ac_tbl_no, 1u);
        }
        ++v1;
        ++v2;
      }
      while ( v1 < cinfo[10].global_state );
    }
  }
  if ( cinfo[9].err )
  {
    emit_marker(cinfo, M_DRI);
    emit_2bytes(cinfo, 4);
    emit_2bytes(cinfo, (__int16)cinfo[9].err);
  }
  emit_sos(cinfo);
}

// FUNC: write_file_trailer
void __cdecl write_file_trailer(jpeg_common_struct *cinfo)
{
  emit_marker(cinfo, M_EOI);
}

// FUNC: write_tables_only
void __cdecl write_tables_only(jpeg_common_struct *cinfo)
{
  int v1; // edi
  JQUANT_TBL **p_mem; // ebx
  int v3; // edi
  JHUFF_TBL **p_global_state; // ebx
  jpeg_destination_mgr *err; // eax
  bool v6; // zf
  jpeg_destination_mgr *v7; // eax

  emit_marker(cinfo, M_SOI);
  v1 = 0;
  p_mem = (JQUANT_TBL **)&cinfo[3].mem;
  do
  {
    if ( *p_mem )
      emit_dqt(cinfo, v1);
    ++v1;
    ++p_mem;
  }
  while ( v1 < 4 );
  if ( !BYTE1(cinfo[8].progress) )
  {
    v3 = 0;
    p_global_state = (JHUFF_TBL **)&cinfo[4].global_state;
    do
    {
      if ( *(p_global_state - 4) )
        emit_dht(cinfo, v3, 0);
      if ( *p_global_state )
        emit_dht(cinfo, v3, 1u);
      ++v3;
      ++p_global_state;
    }
    while ( v3 < 4 );
  }
  err = (jpeg_destination_mgr *)cinfo[1].err;
  *err->next_output_byte++ = -1;
  v6 = err->free_in_buffer-- == 1;
  if ( v6 && !err->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
  v7 = (jpeg_destination_mgr *)cinfo[1].err;
  *v7->next_output_byte++ = -39;
  v6 = v7->free_in_buffer-- == 1;
  if ( v6 && !v7->empty_output_buffer((jpeg_compress_struct *)cinfo) )
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit(cinfo);
  }
}

// FUNC: _jinit_marker_writer
void __cdecl jinit_marker_writer(jpeg_common_struct *cinfo)
{
  jpeg_marker_writer *v1; // eax

  v1 = (jpeg_marker_writer *)cinfo->mem->alloc_small(cinfo, 1, 24);
  cinfo[16].err = (jpeg_error_mgr *)v1;
  v1->write_any_marker = (void (__cdecl *)(jpeg_compress_struct *, int, const unsigned __int8 *, unsigned int))write_any_marker;
  cinfo[16].err->emit_message = (void (__cdecl *)(jpeg_common_struct *, int))write_file_header;
  cinfo[16].err->output_message = write_frame_header;
  cinfo[16].err->format_message = (void (__cdecl *)(jpeg_common_struct *, char *))write_scan_header;
  cinfo[16].err->reset_error_mgr = write_file_trailer;
  cinfo[16].err->msg_code = (int)write_tables_only;
}
