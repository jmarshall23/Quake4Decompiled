
// FUNC: emit_bits
unsigned __int8 __usercall emit_bits@<al>(working_state *state@<esi>, int size@<eax>, unsigned int code)
{
  int put_bits; // ebp
  int v5; // ebp
  int v6; // edi
  bool v7; // zf
  jpeg_destination_mgr *dest; // ebx
  jpeg_destination_mgr *v9; // ebx
  unsigned __int8 code_2; // [esp+12h] [ebp+6h]

  put_bits = state->cur.put_bits;
  if ( !size )
  {
    state->cinfo->err->msg_code = 37;
    state->cinfo->err->error_exit((jpeg_common_struct *)state->cinfo);
  }
  v5 = size + put_bits;
  v6 = state->cur.put_buffer | ((code & ((1 << size) - 1)) << (24 - v5));
  code_2 = BYTE2(v6);
  if ( v5 < 8 )
  {
LABEL_12:
    state->cur.put_buffer = v6;
    state->cur.put_bits = v5;
    return 1;
  }
  while ( 1 )
  {
    *state->next_output_byte++ = code_2;
    v7 = state->free_in_buffer-- == 1;
    if ( v7 )
    {
      dest = state->cinfo->dest;
      if ( !dest->empty_output_buffer(state->cinfo) )
        return 0;
      state->next_output_byte = dest->next_output_byte;
      state->free_in_buffer = dest->free_in_buffer;
    }
    if ( code_2 == 255 )
    {
      *state->next_output_byte++ = 0;
      v7 = state->free_in_buffer-- == 1;
      if ( v7 )
        break;
    }
LABEL_11:
    v6 <<= 8;
    v5 -= 8;
    code_2 = BYTE2(v6);
    if ( v5 < 8 )
      goto LABEL_12;
  }
  v9 = state->cinfo->dest;
  if ( v9->empty_output_buffer(state->cinfo) )
  {
    state->next_output_byte = v9->next_output_byte;
    state->free_in_buffer = v9->free_in_buffer;
    goto LABEL_11;
  }
  return 0;
}

// FUNC: emit_restart
unsigned __int8 __usercall emit_restart@<al>(working_state *state@<eax>, char restart_num)
{
  bool v3; // zf
  jpeg_destination_mgr *dest; // edi
  jpeg_destination_mgr *v5; // edi
  int v6; // eax
  int *last_dc_val; // ecx

  if ( !emit_bits(state, 7, 0x7Fu) )
    return 0;
  state->cur.put_buffer = 0;
  state->cur.put_bits = 0;
  *state->next_output_byte++ = -1;
  v3 = state->free_in_buffer-- == 1;
  if ( v3 )
  {
    dest = state->cinfo->dest;
    if ( !dest->empty_output_buffer(state->cinfo) )
      return 0;
    state->next_output_byte = dest->next_output_byte;
    state->free_in_buffer = dest->free_in_buffer;
  }
  *state->next_output_byte++ = restart_num - 48;
  v3 = state->free_in_buffer-- == 1;
  if ( v3 )
  {
    v5 = state->cinfo->dest;
    if ( v5->empty_output_buffer(state->cinfo) )
    {
      state->next_output_byte = v5->next_output_byte;
      state->free_in_buffer = v5->free_in_buffer;
      goto LABEL_8;
    }
    return 0;
  }
LABEL_8:
  v6 = 0;
  if ( state->cinfo->comps_in_scan > 0 )
  {
    last_dc_val = state->cur.last_dc_val;
    do
    {
      *last_dc_val = 0;
      ++v6;
      ++last_dc_val;
    }
    while ( v6 < state->cinfo->comps_in_scan );
  }
  return 1;
}

// FUNC: emit_buffered_bits
void __usercall emit_buffered_bits(
        phuff_entropy_encoder *entropy@<edx>,
        char *bufstart@<ecx>,
        unsigned int nbits@<eax>)
{
  unsigned int v4; // ebx

  v4 = nbits;
  if ( !entropy->gather_statistics && nbits )
  {
    do
    {
      emit_bits_0(entropy, *bufstart++, 1);
      --v4;
    }
    while ( v4 );
  }
}

// FUNC: emit_eobrun
void __usercall emit_eobrun(phuff_entropy_encoder *entropy@<eax>)
{
  signed int EOBRUN; // eax
  int v3; // edi
  int i; // eax
  int ac_tbl_no; // eax
  unsigned int BE; // eax
  char *bit_buffer; // ecx

  EOBRUN = entropy->EOBRUN;
  if ( EOBRUN )
  {
    v3 = 0;
    for ( i = EOBRUN >> 1; i; i >>= 1 )
      ++v3;
    ac_tbl_no = entropy->ac_tbl_no;
    if ( entropy->gather_statistics )
      ++entropy->count_ptrs[ac_tbl_no][16 * v3];
    else
      emit_bits_0(
        entropy,
        entropy->derived_tbls[ac_tbl_no]->ehufco[16 * v3],
        entropy->derived_tbls[ac_tbl_no]->ehufsi[16 * v3]);
    if ( v3 )
      emit_bits_0(entropy, entropy->EOBRUN, v3);
    BE = entropy->BE;
    bit_buffer = entropy->bit_buffer;
    entropy->EOBRUN = 0;
    emit_buffered_bits(entropy, bit_buffer, BE);
    entropy->BE = 0;
  }
}

// FUNC: finish_pass_phuff
void __cdecl finish_pass_phuff(jpeg_compress_struct *cinfo)
{
  phuff_entropy_encoder *entropy; // esi
  unsigned __int8 *next_output_byte; // edx

  entropy = (phuff_entropy_encoder *)cinfo->entropy;
  entropy->next_output_byte = cinfo->dest->next_output_byte;
  entropy->free_in_buffer = cinfo->dest->free_in_buffer;
  emit_eobrun(entropy);
  emit_bits_0(entropy, 0x7Fu, 7);
  next_output_byte = entropy->next_output_byte;
  entropy->put_buffer = 0;
  entropy->put_bits = 0;
  cinfo->dest->next_output_byte = next_output_byte;
  cinfo->dest->free_in_buffer = entropy->free_in_buffer;
}

// FUNC: finish_pass_gather_phuff
void __cdecl finish_pass_gather_phuff(jpeg_common_struct *cinfo)
{
  bool v2; // zf
  bool v3; // cl
  jpeg_component_info *v4; // eax
  int dc_tbl_no; // ebp
  JHUFF_TBL **v6; // edi
  jpeg_component_info **i; // [esp+4h] [ebp-10h]
  int ci; // [esp+8h] [ebp-Ch]
  unsigned __int8 did[4]; // [esp+Ch] [ebp-8h]
  phuff_entropy_encoder *entropy; // [esp+10h] [ebp-4h]
  bool cinfoa; // [esp+18h] [ebp+4h]

  entropy = (phuff_entropy_encoder *)cinfo[16].global_state;
  emit_eobrun(entropy);
  v2 = cinfo[14].progress == 0;
  *(_DWORD *)did = 0;
  v3 = v2;
  cinfoa = v2;
  ci = 0;
  if ( cinfo[10].global_state > 0 )
  {
    for ( i = (jpeg_component_info **)&cinfo[11]; ; ++i )
    {
      v4 = *i;
      if ( !v3 )
        break;
      if ( !cinfo[14].global_state )
      {
        dc_tbl_no = v4->dc_tbl_no;
        goto LABEL_7;
      }
LABEL_13:
      if ( ++ci >= cinfo[10].global_state )
        return;
    }
    dc_tbl_no = v4->ac_tbl_no;
LABEL_7:
    if ( !did[dc_tbl_no] )
    {
      v6 = (JHUFF_TBL **)(&cinfo[4].err + dc_tbl_no);
      if ( !v3 )
        v6 = (JHUFF_TBL **)(&cinfo[4].global_state + dc_tbl_no);
      if ( !*v6 )
        *v6 = jpeg_alloc_huff_table(cinfo);
      jpeg_gen_optimal_table((jpeg_compress_struct *)cinfo, *v6, entropy->count_ptrs[dc_tbl_no]);
      v3 = cinfoa;
      did[dc_tbl_no] = 1;
    }
    goto LABEL_13;
  }
}

// FUNC: start_pass_phuff
void __cdecl start_pass_phuff(jpeg_common_struct *cinfo, unsigned __int8 gather_statistics)
{
  jpeg_entropy_encoder *global_state; // ebp
  bool v4; // al
  jpeg_component_info **v5; // ebx
  jpeg_component_info *v6; // eax
  unsigned int dc_tbl_no; // edi
  bool v8; // zf
  unsigned int err; // edx
  jpeg_entropy_encoder *v10; // [esp+10h] [ebp-8h]
  int ci; // [esp+14h] [ebp-4h]
  bool cinfoa; // [esp+1Ch] [ebp+4h]

  global_state = (jpeg_entropy_encoder *)cinfo[16].global_state;
  global_state[2].finish_pass = (void (__cdecl *)(jpeg_compress_struct *))cinfo;
  LOBYTE(global_state[1].start_pass) = gather_statistics;
  v4 = cinfo[14].progress == 0;
  v8 = cinfo[14].global_state == 0;
  cinfoa = v4;
  if ( v8 )
  {
    if ( v4 )
      global_state->encode_mcu = encode_mcu_DC_first;
    else
      global_state->encode_mcu = encode_mcu_AC_first;
  }
  else if ( v4 )
  {
    global_state->encode_mcu = encode_mcu_DC_refine;
  }
  else
  {
    v8 = global_state[5].encode_mcu == 0;
    global_state->encode_mcu = encode_mcu_AC_refine;
    if ( v8 )
      global_state[5].encode_mcu = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, __int16 (**)[64]))cinfo->mem->alloc_small(cinfo, 1, 1000);
  }
  if ( gather_statistics )
    global_state->finish_pass = (void (__cdecl *)(jpeg_compress_struct *))finish_pass_gather_phuff;
  else
    global_state->finish_pass = finish_pass_phuff;
  ci = 0;
  if ( cinfo[10].global_state > 0 )
  {
    v10 = global_state + 3;
    v5 = (jpeg_component_info **)&cinfo[11];
    do
    {
      v6 = *v5;
      v10->start_pass = 0;
      if ( cinfoa )
      {
        if ( cinfo[14].global_state )
          goto LABEL_30;
        dc_tbl_no = v6->dc_tbl_no;
        if ( dc_tbl_no > 3 )
          goto LABEL_22;
        v8 = *((_DWORD *)&cinfo[4].err + dc_tbl_no) == 0;
      }
      else
      {
        dc_tbl_no = v6->ac_tbl_no;
        global_state[4].encode_mcu = (unsigned __int8 (__cdecl *)(jpeg_compress_struct *, __int16 (**)[64]))dc_tbl_no;
        if ( dc_tbl_no > 3 )
          goto LABEL_22;
        v8 = *(&cinfo[4].global_state + dc_tbl_no) == 0;
      }
      if ( v8 )
      {
        if ( gather_statistics )
          goto LABEL_24;
LABEL_22:
        cinfo->err->msg_code = 47;
        cinfo->err->msg_parm.i[0] = dc_tbl_no;
        cinfo->err->error_exit(cinfo);
      }
      if ( gather_statistics )
      {
LABEL_24:
        if ( !*((_DWORD *)&global_state[7].finish_pass + dc_tbl_no) )
          *((_DWORD *)&global_state[7].finish_pass + dc_tbl_no) = cinfo->mem->alloc_small(cinfo, 1, 1028);
        memset(*((void **)&global_state[7].finish_pass + dc_tbl_no), 0, 0x404u);
        goto LABEL_30;
      }
      if ( cinfoa )
        jpeg_make_c_derived_tbl(
          (jpeg_compress_struct *)cinfo,
          *((JHUFF_TBL **)&cinfo[4].err + dc_tbl_no),
          (c_derived_tbl **)&global_state[6].encode_mcu + dc_tbl_no);
      else
        jpeg_make_c_derived_tbl(
          (jpeg_compress_struct *)cinfo,
          *((JHUFF_TBL **)&cinfo[4].global_state + dc_tbl_no),
          (c_derived_tbl **)&global_state[6].encode_mcu + dc_tbl_no);
LABEL_30:
      v10 = (jpeg_entropy_encoder *)((char *)v10 + 4);
      ++v5;
      ++ci;
    }
    while ( ci < cinfo[10].global_state );
  }
  global_state[4].finish_pass = 0;
  global_state[5].start_pass = 0;
  global_state[2].start_pass = 0;
  global_state[2].encode_mcu = 0;
  err = (unsigned int)cinfo[9].err;
  global_state[6].start_pass = 0;
  global_state[5].finish_pass = (void (__cdecl *)(jpeg_compress_struct *))err;
}

// FUNC: _jinit_phuff_encoder
void __cdecl jinit_phuff_encoder(jpeg_common_struct *cinfo)
{
  jpeg_entropy_encoder *v1; // eax

  v1 = (jpeg_entropy_encoder *)cinfo->mem->alloc_small(cinfo, 1, 108);
  cinfo[16].global_state = (int)v1;
  v1->start_pass = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8))start_pass_phuff;
  v1[6].encode_mcu = 0;
  v1[7].finish_pass = 0;
  v1[6].finish_pass = 0;
  v1[8].start_pass = 0;
  v1[7].start_pass = 0;
  v1[8].encode_mcu = 0;
  v1[7].encode_mcu = 0;
  v1[8].finish_pass = 0;
  v1[5].encode_mcu = 0;
}
