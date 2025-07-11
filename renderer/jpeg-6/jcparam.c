
// FUNC: _jpeg_add_quant_table
void __cdecl jpeg_add_quant_table(
        jpeg_common_struct *cinfo,
        int which_tbl,
        const unsigned int *basic_table,
        int scale_factor,
        unsigned __int8 force_baseline)
{
  int v5; // esi
  const unsigned int *v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax

  if ( cinfo->global_state != 100 )
  {
    cinfo->err->msg_code = 17;
    cinfo->err->msg_parm.i[0] = cinfo->global_state;
    cinfo->err->error_exit(cinfo);
  }
  if ( !*((_DWORD *)&cinfo[3].mem + which_tbl) )
    *((_DWORD *)&cinfo[3].mem + which_tbl) = jpeg_alloc_quant_table(cinfo);
  v5 = 0;
  v6 = basic_table + 2;
  do
  {
    v7 = (signed int)(scale_factor * *(v6 - 2) + 50) / 100;
    if ( v7 > 0 )
    {
      if ( v7 > 0x7FFF )
        v7 = 0x7FFF;
    }
    else
    {
      v7 = 1;
    }
    if ( force_baseline && v7 > 255 )
      LOWORD(v7) = 255;
    *(_WORD *)(v5 + *((_DWORD *)&cinfo[3].mem + which_tbl)) = v7;
    v8 = (signed int)(scale_factor * *(v6 - 1) + 50) / 100;
    if ( v8 > 0 )
    {
      if ( v8 > 0x7FFF )
        v8 = 0x7FFF;
    }
    else
    {
      v8 = 1;
    }
    if ( force_baseline && v8 > 255 )
      LOWORD(v8) = 255;
    *(_WORD *)(*((_DWORD *)&cinfo[3].mem + which_tbl) + v5 + 2) = v8;
    v9 = (signed int)(scale_factor * *v6 + 50) / 100;
    if ( v9 > 0 )
    {
      if ( v9 > 0x7FFF )
        v9 = 0x7FFF;
    }
    else
    {
      v9 = 1;
    }
    if ( force_baseline && v9 > 255 )
      LOWORD(v9) = 255;
    *(_WORD *)(*((_DWORD *)&cinfo[3].mem + which_tbl) + v5 + 4) = v9;
    v10 = (signed int)(scale_factor * v6[1] + 50) / 100;
    if ( v10 > 0 )
    {
      if ( v10 > 0x7FFF )
        v10 = 0x7FFF;
    }
    else
    {
      v10 = 1;
    }
    if ( force_baseline && v10 > 255 )
      LOWORD(v10) = 255;
    *(_WORD *)(v5 + *((_DWORD *)&cinfo[3].mem + which_tbl) + 6) = v10;
    v5 += 8;
    v6 += 4;
  }
  while ( v5 < 128 );
  *(_BYTE *)(*((_DWORD *)&cinfo[3].mem + which_tbl) + 128) = 0;
}

// FUNC: _jpeg_set_quality
void __cdecl jpeg_set_quality(jpeg_common_struct *cinfo, int quality, unsigned __int8 force_baseline)
{
  int v3; // ecx
  int v4; // esi

  v3 = quality;
  if ( quality > 0 )
  {
    if ( quality <= 100 )
    {
      if ( quality < 50 )
      {
        v4 = 5000 / quality;
        goto LABEL_6;
      }
    }
    else
    {
      v3 = 100;
    }
    v4 = 2 * (100 - v3);
  }
  else
  {
    v4 = 5000;
  }
LABEL_6:
  jpeg_add_quant_table(cinfo, 0, &basic_table, v4, force_baseline);
  jpeg_add_quant_table(cinfo, 1, &dword_102C7E10, v4, force_baseline);
}

// FUNC: std_huff_tables
void __cdecl std_huff_tables(jpeg_common_struct *cinfo)
{
  JHUFF_TBL *err; // eax
  JHUFF_TBL *global_state; // eax
  JHUFF_TBL *mem; // eax
  JHUFF_TBL *v4; // eax

  if ( !cinfo[4].err )
    cinfo[4].err = (jpeg_error_mgr *)jpeg_alloc_huff_table(cinfo);
  err = (JHUFF_TBL *)cinfo[4].err;
  *(_DWORD *)err->bits = *(_DWORD *)bits_dc_luminance;
  *(_DWORD *)&err->bits[4] = 16843009;
  *(_DWORD *)&err->bits[8] = 257;
  *(_DWORD *)&err->bits[12] = 0;
  err->bits[16] = 0;
  qmemcpy((char *)&cinfo[4].err->reset_error_mgr + 1, val_dc_luminance, 0x100u);
  BYTE1(cinfo[4].err[2].output_message) = 0;
  if ( !cinfo[4].global_state )
    cinfo[4].global_state = (int)jpeg_alloc_huff_table(cinfo);
  global_state = (JHUFF_TBL *)cinfo[4].global_state;
  *(_DWORD *)global_state->bits = *(_DWORD *)bits_ac_luminance;
  *(_DWORD *)&global_state->bits[4] = 67240707;
  *(_DWORD *)&global_state->bits[8] = 67437827;
  *(_DWORD *)&global_state->bits[12] = 16777220;
  global_state->bits[16] = 125;
  qmemcpy((void *)(cinfo[4].global_state + 17), val_ac_luminance, 0x100u);
  *(_BYTE *)(cinfo[4].global_state + 273) = 0;
  if ( !cinfo[4].mem )
    cinfo[4].mem = (jpeg_memory_mgr *)jpeg_alloc_huff_table(cinfo);
  mem = (JHUFF_TBL *)cinfo[4].mem;
  *(_DWORD *)mem->bits = *(_DWORD *)bits_dc_chrominance;
  *(_DWORD *)&mem->bits[4] = 16843009;
  *(_DWORD *)&mem->bits[8] = 16843009;
  *(_DWORD *)&mem->bits[12] = 0;
  mem->bits[16] = 0;
  qmemcpy((char *)&cinfo[4].mem->request_virt_sarray + 1, val_dc_chrominance, 0x100u);
  BYTE1(cinfo[4].mem[5].access_virt_barray) = 0;
  if ( !cinfo[5].err )
    cinfo[5].err = (jpeg_error_mgr *)jpeg_alloc_huff_table(cinfo);
  v4 = (JHUFF_TBL *)cinfo[5].err;
  *(_DWORD *)v4->bits = *(_DWORD *)bits_ac_chrominance;
  *(_DWORD *)&v4->bits[4] = 50594818;
  *(_DWORD *)&v4->bits[8] = 67438340;
  *(_DWORD *)&v4->bits[12] = 33619972;
  v4->bits[16] = 119;
  qmemcpy((char *)&cinfo[5].err->reset_error_mgr + 1, val_ac_chrominance, 0x100u);
  BYTE1(cinfo[5].err[2].output_message) = 0;
}

// FUNC: _jpeg_set_colorspace
void __cdecl jpeg_set_colorspace(jpeg_common_struct *cinfo, int colorspace)
{
  jpeg_component_info *err; // esi
  jpeg_component_info *v3; // eax
  jpeg_component_info *v4; // eax
  jpeg_component_info *v5; // esi
  jpeg_component_info *v6; // eax
  jpeg_component_info *v7; // eax
  jpeg_component_info *v8; // esi
  jpeg_component_info *v9; // eax
  jpeg_component_info *v10; // eax
  jpeg_component_info *v11; // eax
  jpeg_component_info *p_addon_message_table; // esi
  jpeg_component_info *v13; // eax
  jpeg_component_info *v14; // eax
  jpeg_component_info *v15; // eax
  jpeg_component_info *v16; // esi
  int v17; // eax
  int v18; // ecx
  int v19; // edx
  jpeg_component_info *v20; // eax

  if ( cinfo->global_state != 100 )
  {
    cinfo->err->msg_code = 17;
    cinfo->err->msg_parm.i[0] = cinfo->global_state;
    cinfo->err->error_exit(cinfo);
  }
  cinfo[2].global_state = colorspace;
  LOBYTE(cinfo[9].progress) = 0;
  *(&cinfo[9].is_decompressor + 2) = 0;
  switch ( colorspace )
  {
    case 0:
      v17 = *(_DWORD *)&cinfo[1].is_decompressor;
      *(_DWORD *)&cinfo[2].is_decompressor = v17;
      if ( v17 < 1 || v17 > 10 )
      {
        cinfo->err->msg_code = 22;
        cinfo->err->msg_parm.i[0] = *(_DWORD *)&cinfo[2].is_decompressor;
        cinfo->err->msg_parm.i[1] = 10;
        cinfo->err->error_exit(cinfo);
      }
      v18 = 0;
      if ( *(int *)&cinfo[2].is_decompressor > 0 )
      {
        v19 = 0;
        do
        {
          v20 = (jpeg_component_info *)((char *)cinfo[3].err + v19);
          v20->component_id = v18++;
          v20->h_samp_factor = 1;
          v20->v_samp_factor = 1;
          v20->quant_tbl_no = 0;
          v20->dc_tbl_no = 0;
          v20->ac_tbl_no = 0;
          v19 += 84;
        }
        while ( v18 < *(_DWORD *)&cinfo[2].is_decompressor );
      }
      break;
    case 1:
      LOBYTE(cinfo[9].progress) = 1;
      *(_DWORD *)&cinfo[2].is_decompressor = 1;
      err = (jpeg_component_info *)cinfo[3].err;
      err->component_id = 1;
      err->h_samp_factor = 1;
      err->v_samp_factor = 1;
      err->quant_tbl_no = 0;
      err->dc_tbl_no = 0;
      err->ac_tbl_no = 0;
      break;
    case 2:
      v3 = (jpeg_component_info *)cinfo[3].err;
      *(_DWORD *)&cinfo[2].is_decompressor = 3;
      *(&cinfo[9].is_decompressor + 2) = 1;
      v3->h_samp_factor = 1;
      v3->v_samp_factor = 1;
      v3->component_id = 82;
      v3->quant_tbl_no = 0;
      v3->dc_tbl_no = 0;
      v3->ac_tbl_no = 0;
      v4 = (jpeg_component_info *)&cinfo[3].err->msg_parm.s[60];
      v4->h_samp_factor = 1;
      v4->v_samp_factor = 1;
      v4->component_id = 71;
      v4->quant_tbl_no = 0;
      v4->dc_tbl_no = 0;
      v4->ac_tbl_no = 0;
      v5 = (jpeg_component_info *)&cinfo[3].err[1].msg_parm.s[12];
      v5->h_samp_factor = 1;
      v5->v_samp_factor = 1;
      v5->component_id = 66;
      v5->quant_tbl_no = 0;
      v5->dc_tbl_no = 0;
      v5->ac_tbl_no = 0;
      break;
    case 3:
      v6 = (jpeg_component_info *)cinfo[3].err;
      *(_DWORD *)&cinfo[2].is_decompressor = 3;
      LOBYTE(cinfo[9].progress) = 1;
      v6->component_id = 1;
      v6->quant_tbl_no = 0;
      v6->dc_tbl_no = 0;
      v6->ac_tbl_no = 0;
      v6->h_samp_factor = 2;
      v6->v_samp_factor = 2;
      v7 = (jpeg_component_info *)&cinfo[3].err->msg_parm.s[60];
      v7->h_samp_factor = 1;
      v7->v_samp_factor = 1;
      v7->quant_tbl_no = 1;
      v7->dc_tbl_no = 1;
      v7->ac_tbl_no = 1;
      v7->component_id = 2;
      v8 = (jpeg_component_info *)&cinfo[3].err[1].msg_parm.s[12];
      v8->h_samp_factor = 1;
      v8->v_samp_factor = 1;
      v8->quant_tbl_no = 1;
      v8->dc_tbl_no = 1;
      v8->ac_tbl_no = 1;
      v8->component_id = 3;
      break;
    case 4:
      v9 = (jpeg_component_info *)cinfo[3].err;
      *(_DWORD *)&cinfo[2].is_decompressor = 4;
      *(&cinfo[9].is_decompressor + 2) = 1;
      v9->h_samp_factor = 1;
      v9->v_samp_factor = 1;
      v9->component_id = 67;
      v9->quant_tbl_no = 0;
      v9->dc_tbl_no = 0;
      v9->ac_tbl_no = 0;
      v10 = (jpeg_component_info *)cinfo[3].err;
      v10[1].h_samp_factor = 1;
      v10[1].v_samp_factor = 1;
      v10[1].component_id = 77;
      v10[1].quant_tbl_no = 0;
      v10[1].dc_tbl_no = 0;
      v10[1].ac_tbl_no = 0;
      v11 = (jpeg_component_info *)&cinfo[3].err[1].msg_parm.s[12];
      v11->h_samp_factor = 1;
      v11->v_samp_factor = 1;
      v11->component_id = 89;
      v11->quant_tbl_no = 0;
      v11->dc_tbl_no = 0;
      v11->ac_tbl_no = 0;
      p_addon_message_table = (jpeg_component_info *)&cinfo[3].err[1].addon_message_table;
      p_addon_message_table->h_samp_factor = 1;
      p_addon_message_table->v_samp_factor = 1;
      p_addon_message_table->component_id = 75;
      p_addon_message_table->quant_tbl_no = 0;
      p_addon_message_table->dc_tbl_no = 0;
      p_addon_message_table->ac_tbl_no = 0;
      break;
    case 5:
      v13 = (jpeg_component_info *)cinfo[3].err;
      *(_DWORD *)&cinfo[2].is_decompressor = 4;
      *(&cinfo[9].is_decompressor + 2) = 1;
      v13->component_id = 1;
      v13->quant_tbl_no = 0;
      v13->dc_tbl_no = 0;
      v13->ac_tbl_no = 0;
      v13->h_samp_factor = 2;
      v13->v_samp_factor = 2;
      v14 = (jpeg_component_info *)cinfo[3].err;
      v14[1].h_samp_factor = 1;
      v14[1].v_samp_factor = 1;
      v14[1].quant_tbl_no = 1;
      v14[1].dc_tbl_no = 1;
      v14[1].ac_tbl_no = 1;
      v14[1].component_id = 2;
      v15 = (jpeg_component_info *)&cinfo[3].err[1].msg_parm.s[12];
      v15->h_samp_factor = 1;
      v15->v_samp_factor = 1;
      v15->quant_tbl_no = 1;
      v15->dc_tbl_no = 1;
      v15->ac_tbl_no = 1;
      v15->component_id = 3;
      v16 = (jpeg_component_info *)&cinfo[3].err[1].addon_message_table;
      v16->component_id = 4;
      v16->h_samp_factor = 2;
      v16->v_samp_factor = 2;
      v16->quant_tbl_no = 0;
      v16->dc_tbl_no = 0;
      v16->ac_tbl_no = 0;
      break;
    default:
      cinfo->err->msg_code = 8;
      cinfo->err->error_exit(cinfo);
      break;
  }
}

// FUNC: _jpeg_default_colorspace
void __cdecl jpeg_default_colorspace(jpeg_common_struct *cinfo)
{
  jpeg_component_info *err; // esi
  jpeg_component_info *v2; // edx
  jpeg_component_info *v3; // ecx
  jpeg_component_info *v4; // esi
  jpeg_component_info *v5; // edx
  jpeg_component_info *v6; // edx
  jpeg_component_info *v7; // edx
  jpeg_component_info *p_addon_message_table; // esi
  jpeg_component_info *v9; // edx
  jpeg_component_info *v10; // edx
  jpeg_component_info *v11; // edx
  jpeg_component_info *v12; // esi

  switch ( cinfo[1].global_state )
  {
    case 0:
      jpeg_set_colorspace(cinfo, 0);
      break;
    case 1:
      if ( cinfo->global_state != 100 )
      {
        cinfo->err->msg_code = 17;
        cinfo->err->msg_parm.i[0] = cinfo->global_state;
        cinfo->err->error_exit(cinfo);
      }
      cinfo[2].global_state = 1;
      LOBYTE(cinfo[9].progress) = 1;
      *(_DWORD *)&cinfo[2].is_decompressor = 1;
      *(&cinfo[9].is_decompressor + 2) = 0;
      err = (jpeg_component_info *)cinfo[3].err;
      err->component_id = 1;
      err->h_samp_factor = 1;
      err->v_samp_factor = 1;
      err->quant_tbl_no = 0;
      err->dc_tbl_no = 0;
      err->ac_tbl_no = 0;
      break;
    case 2:
      if ( cinfo->global_state == 100 )
        goto LABEL_9;
      goto LABEL_8;
    case 3:
      if ( cinfo->global_state != 100 )
      {
LABEL_8:
        cinfo->err->msg_code = 17;
        cinfo->err->msg_parm.i[0] = cinfo->global_state;
        cinfo->err->error_exit(cinfo);
      }
LABEL_9:
      v2 = (jpeg_component_info *)cinfo[3].err;
      LOBYTE(cinfo[9].progress) = 1;
      *(&cinfo[9].is_decompressor + 2) = 0;
      cinfo[2].global_state = 3;
      *(_DWORD *)&cinfo[2].is_decompressor = 3;
      v2->component_id = 1;
      v2->h_samp_factor = 2;
      v2->v_samp_factor = 2;
      v2->quant_tbl_no = 0;
      v2->dc_tbl_no = 0;
      v2->ac_tbl_no = 0;
      v3 = (jpeg_component_info *)cinfo[3].err;
      v3[1].component_id = 2;
      v3[1].h_samp_factor = 1;
      ++v3;
      v3->v_samp_factor = 1;
      v3->quant_tbl_no = 1;
      v3->dc_tbl_no = 1;
      v3->ac_tbl_no = 1;
      v4 = (jpeg_component_info *)&cinfo[3].err[1].msg_parm.s[12];
      v4->component_id = 3;
      v4->h_samp_factor = 1;
      v4->v_samp_factor = 1;
      v4->quant_tbl_no = 1;
      v4->dc_tbl_no = 1;
      v4->ac_tbl_no = 1;
      break;
    case 4:
      if ( cinfo->global_state != 100 )
      {
        cinfo->err->msg_code = 17;
        cinfo->err->msg_parm.i[0] = cinfo->global_state;
        cinfo->err->error_exit(cinfo);
      }
      v5 = (jpeg_component_info *)cinfo[3].err;
      LOBYTE(cinfo[9].progress) = 0;
      *(&cinfo[9].is_decompressor + 2) = 1;
      cinfo[2].global_state = 4;
      *(_DWORD *)&cinfo[2].is_decompressor = 4;
      v5->component_id = 67;
      v5->h_samp_factor = 1;
      v5->v_samp_factor = 1;
      v5->quant_tbl_no = 0;
      v5->dc_tbl_no = 0;
      v5->ac_tbl_no = 0;
      v6 = (jpeg_component_info *)cinfo[3].err;
      v6[1].component_id = 77;
      v6[1].h_samp_factor = 1;
      v6[1].v_samp_factor = 1;
      v6[1].quant_tbl_no = 0;
      v6[1].dc_tbl_no = 0;
      v6[1].ac_tbl_no = 0;
      v7 = (jpeg_component_info *)&cinfo[3].err[1].msg_parm.s[12];
      v7->component_id = 89;
      v7->h_samp_factor = 1;
      v7->v_samp_factor = 1;
      v7->quant_tbl_no = 0;
      v7->dc_tbl_no = 0;
      v7->ac_tbl_no = 0;
      p_addon_message_table = (jpeg_component_info *)&cinfo[3].err[1].addon_message_table;
      p_addon_message_table->component_id = 75;
      p_addon_message_table->h_samp_factor = 1;
      p_addon_message_table->v_samp_factor = 1;
      p_addon_message_table->quant_tbl_no = 0;
      p_addon_message_table->dc_tbl_no = 0;
      p_addon_message_table->ac_tbl_no = 0;
      break;
    case 5:
      if ( cinfo->global_state != 100 )
      {
        cinfo->err->msg_code = 17;
        cinfo->err->msg_parm.i[0] = cinfo->global_state;
        cinfo->err->error_exit(cinfo);
      }
      v9 = (jpeg_component_info *)cinfo[3].err;
      cinfo[2].global_state = 5;
      *(&cinfo[9].is_decompressor + 2) = 1;
      LOBYTE(cinfo[9].progress) = 0;
      *(_DWORD *)&cinfo[2].is_decompressor = 4;
      v9->h_samp_factor = 2;
      v9->v_samp_factor = 2;
      v9->component_id = 1;
      v9->quant_tbl_no = 0;
      v9->dc_tbl_no = 0;
      v9->ac_tbl_no = 0;
      v10 = (jpeg_component_info *)cinfo[3].err;
      v10[1].component_id = 2;
      v10[1].h_samp_factor = 1;
      v10[1].v_samp_factor = 1;
      v10[1].quant_tbl_no = 1;
      v10[1].dc_tbl_no = 1;
      v10[1].ac_tbl_no = 1;
      v11 = (jpeg_component_info *)&cinfo[3].err[1].msg_parm.s[12];
      v11->component_id = 3;
      v11->h_samp_factor = 1;
      v11->v_samp_factor = 1;
      v11->quant_tbl_no = 1;
      v11->dc_tbl_no = 1;
      v11->ac_tbl_no = 1;
      v12 = (jpeg_component_info *)&cinfo[3].err[1].addon_message_table;
      v12->h_samp_factor = 2;
      v12->v_samp_factor = 2;
      v12->component_id = 4;
      v12->quant_tbl_no = 0;
      v12->dc_tbl_no = 0;
      v12->ac_tbl_no = 0;
      break;
    default:
      cinfo->err->msg_code = 7;
      cinfo->err->error_exit(cinfo);
      break;
  }
}

// FUNC: _jpeg_set_defaults
void __cdecl jpeg_set_defaults(jpeg_common_struct *cinfo)
{
  unsigned __int8 *p_progress; // eax
  int v2; // ecx
  bool v3; // cc

  if ( cinfo->global_state != 100 )
  {
    cinfo->err->msg_code = 17;
    cinfo->err->msg_parm.i[0] = cinfo->global_state;
    cinfo->err->error_exit(cinfo);
  }
  if ( !cinfo[3].err )
    cinfo[3].err = (jpeg_error_mgr *)cinfo->mem->alloc_small(cinfo, 0, 840);
  cinfo[2].progress = (jpeg_progress_mgr *)8;
  jpeg_add_quant_table(cinfo, 0, &basic_table, 50, 1u);
  jpeg_add_quant_table(cinfo, 1, &dword_102C7E10, 50, 1u);
  std_huff_tables(cinfo);
  p_progress = (unsigned __int8 *)&cinfo[6].progress;
  v2 = 16;
  do
  {
    *(p_progress - 16) = 0;
    *p_progress = 1;
    p_progress[16] = 5;
    ++p_progress;
    --v2;
  }
  while ( v2 );
  v3 = (int)cinfo[2].progress <= 8;
  cinfo[8].mem = 0;
  cinfo[8].err = 0;
  LOBYTE(cinfo[8].progress) = 0;
  BYTE1(cinfo[8].progress) = 0;
  BYTE2(cinfo[8].progress) = 0;
  if ( !v3 )
    BYTE2(cinfo[8].progress) = 1;
  HIBYTE(cinfo[8].progress) = 0;
  *(_DWORD *)&cinfo[8].is_decompressor = 0;
  cinfo[8].global_state = 2;
  cinfo[9].err = 0;
  cinfo[9].mem = 0;
  BYTE1(cinfo[9].progress) = 0;
  HIWORD(cinfo[9].progress) = 1;
  *(_WORD *)&cinfo[9].is_decompressor = 1;
  jpeg_default_colorspace(cinfo);
}
