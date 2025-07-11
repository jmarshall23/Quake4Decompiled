
// FUNC: _jpeg_make_d_derived_tbl
void __cdecl jpeg_make_d_derived_tbl(jpeg_common_struct *cinfo, JHUFF_TBL *htbl, d_derived_tbl **pdtbl)
{
  d_derived_tbl *v3; // ebx
  JHUFF_TBL *v4; // esi
  unsigned int v5; // eax
  int j; // edx
  unsigned int v7; // ebp
  char *v8; // edi
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // edi
  char *v13; // edx
  int v14; // edx
  int v15; // edx
  int v16; // ecx
  int *v17; // eax
  unsigned int v18; // edi
  int v19; // edx
  int v20; // ecx
  int v21; // edi
  int v22; // ebx
  unsigned __int8 *v23; // ebp
  unsigned int v24; // eax
  unsigned __int8 *v25; // edx
  int *v26; // eax
  int v27; // esi
  int p; // [esp+10h] [ebp-518h]
  int pa; // [esp+10h] [ebp-518h]
  int i; // [esp+14h] [ebp-514h]
  d_derived_tbl *dtbl; // [esp+18h] [ebp-510h]
  int v32; // [esp+1Ch] [ebp-50Ch]
  char huffsize[257]; // [esp+20h] [ebp-508h] BYREF
  unsigned int huffcode[257]; // [esp+124h] [ebp-404h]

  if ( !*pdtbl )
    *pdtbl = (d_derived_tbl *)cinfo->mem->alloc_small(cinfo, 1, 1492);
  v3 = *pdtbl;
  v4 = htbl;
  v5 = 0;
  dtbl = v3;
  v3->pub = htbl;
  p = 0;
  for ( j = 1; j <= 16; ++j )
  {
    v7 = v4->bits[j];
    if ( v4->bits[j] )
    {
      v8 = &huffsize[v5];
      LOBYTE(v3) = j;
      BYTE1(v3) = j;
      v9 = (_DWORD)v3 << 16;
      LOWORD(v9) = (_WORD)v3;
      v3 = dtbl;
      memset32(v8, v9, v7 >> 2);
      v4 = htbl;
      memset(&v8[4 * (v7 >> 2)], v9, v7 & 3);
      v5 = v7 + p;
      p += v7;
    }
  }
  huffsize[v5] = 0;
  v10 = 0;
  v11 = 0;
  v12 = huffsize[0];
  if ( huffsize[0] )
  {
    v13 = huffsize;
    do
    {
      if ( *v13 == v12 )
      {
        do
        {
          v14 = huffsize[v11 + 1];
          huffcode[v11++] = v10++;
        }
        while ( v14 == v12 );
      }
      v13 = &huffsize[v11];
      v10 *= 2;
      ++v12;
    }
    while ( huffsize[v11] );
  }
  v15 = 0;
  v16 = 1;
  v17 = &v3->maxcode[1];
  do
  {
    if ( v4->bits[v16] )
    {
      v18 = huffcode[v15];
      v17[18] = v15;
      *(v17 - 17) = v18;
      v15 += v4->bits[v16];
      *v17 = *(_DWORD *)&huffsize[4 * v15 + 256];
    }
    else
    {
      *v17 = -1;
    }
    ++v16;
    ++v17;
  }
  while ( v16 <= 16 );
  v3->maxcode[17] = 0xFFFFF;
  memset(v3->look_nbits, 0, sizeof(v3->look_nbits));
  v19 = 0;
  v20 = 7;
  pa = 0;
  v21 = 1;
  v32 = 7;
  do
  {
    i = 1;
    if ( v4->bits[v21] )
    {
      v22 = 1 << v20;
      v23 = &v4->huffval[v19];
      do
      {
        v24 = huffcode[v19] << v20;
        if ( v22 > 0 )
        {
          v25 = &dtbl->look_sym[v24];
          v26 = &dtbl->look_nbits[v24];
          v27 = v22;
          do
          {
            *v26 = v21;
            *v25 = *v23;
            ++v26;
            ++v25;
            --v27;
          }
          while ( v27 );
          v19 = pa;
          v20 = v32;
        }
        v4 = htbl;
        ++i;
        ++v19;
        ++v23;
        pa = v19;
      }
      while ( i <= htbl->bits[v21] );
    }
    ++v21;
    v32 = --v20;
  }
  while ( v20 >= 0 );
}

// FUNC: _jpeg_fill_bit_buffer
unsigned __int8 __cdecl jpeg_fill_bit_buffer(bitread_working_state *state, int get_buffer, int bits_left, int nbits)
{
  int v4; // ebp
  unsigned int bytes_in_buffer; // ebx
  const unsigned __int8 *next_input_byte; // edi
  jpeg_source_mgr *v7; // eax
  int v8; // eax
  jpeg_source_mgr *src; // eax
  int v10; // eax

  v4 = bits_left;
  bytes_in_buffer = state->bytes_in_buffer;
  next_input_byte = state->next_input_byte;
  if ( bits_left >= 25 )
  {
LABEL_19:
    state->next_input_byte = next_input_byte;
    state->bytes_in_buffer = bytes_in_buffer;
    state->bits_left = v4;
    state->get_buffer = get_buffer;
    return 1;
  }
  while ( 1 )
  {
    if ( state->unread_marker )
      goto no_more_data;
    if ( !bytes_in_buffer )
      break;
LABEL_6:
    v8 = *next_input_byte;
    --bytes_in_buffer;
    ++next_input_byte;
    if ( v8 == 255 )
    {
      do
      {
        if ( !bytes_in_buffer )
        {
          if ( !state->cinfo->src->fill_input_buffer(state->cinfo) )
            return 0;
          src = state->cinfo->src;
          next_input_byte = src->next_input_byte;
          bytes_in_buffer = src->bytes_in_buffer;
        }
        v10 = *next_input_byte;
        --bytes_in_buffer;
        ++next_input_byte;
      }
      while ( v10 == 255 );
      if ( v10 )
      {
        state->unread_marker = v10;
no_more_data:
        if ( v4 >= nbits )
          goto LABEL_19;
        if ( !*state->printed_eod_ptr )
        {
          state->cinfo->err->msg_code = 111;
          state->cinfo->err->emit_message((jpeg_common_struct *)state->cinfo, -1);
          *state->printed_eod_ptr = 1;
        }
        v8 = 0;
        goto LABEL_18;
      }
      v8 = 255;
    }
LABEL_18:
    v4 += 8;
    get_buffer = v8 | (get_buffer << 8);
    if ( v4 >= 25 )
      goto LABEL_19;
  }
  if ( state->cinfo->src->fill_input_buffer(state->cinfo) )
  {
    v7 = state->cinfo->src;
    next_input_byte = v7->next_input_byte;
    bytes_in_buffer = v7->bytes_in_buffer;
    goto LABEL_6;
  }
  return 0;
}

// FUNC: _jpeg_huff_decode
int __cdecl jpeg_huff_decode(
        bitread_working_state *state,
        int get_buffer,
        int bits_left,
        d_derived_tbl *htbl,
        int min_bits)
{
  int v5; // eax
  int v7; // edx
  int v8; // eax
  d_derived_tbl *v9; // ecx
  int *v10; // edi
  int v11; // esi
  int v12; // esi

  v5 = bits_left;
  if ( bits_left >= min_bits )
  {
    v7 = get_buffer;
  }
  else
  {
    if ( !jpeg_fill_bit_buffer(state, get_buffer, bits_left, min_bits) )
      return -1;
    v7 = state->get_buffer;
    v5 = state->bits_left;
  }
  v8 = v5 - min_bits;
  v9 = htbl;
  v10 = &htbl->maxcode[min_bits];
  v11 = ((1 << min_bits) - 1) & (v7 >> v8);
  if ( v11 > *v10 )
  {
    while ( 1 )
    {
      v12 = 2 * v11;
      if ( v8 < 1 )
      {
        if ( !jpeg_fill_bit_buffer(state, v7, v8, 1) )
          return -1;
        v7 = state->get_buffer;
        v8 = state->bits_left;
      }
      ++min_bits;
      --v8;
      ++v10;
      v11 = (v7 >> v8) & 1 | v12;
      if ( v11 <= *v10 )
      {
        v9 = htbl;
        break;
      }
    }
  }
  state->bits_left = v8;
  state->get_buffer = v7;
  if ( min_bits <= 16 )
    return v9->pub->huffval[v9->valptr[min_bits] - v9->mincode[min_bits] + v11];
  state->cinfo->err->msg_code = 112;
  state->cinfo->err->emit_message((jpeg_common_struct *)state->cinfo, -1);
  return 0;
}

// FUNC: start_pass_huff_decoder
void __cdecl start_pass_huff_decoder(jpeg_common_struct *cinfo)
{
  jpeg_entropy_decoder *mem; // ebx
  unsigned int dc_tbl_no; // edi
  unsigned int ac_tbl_no; // ebp
  bool v5; // cc
  int ci; // [esp+Ch] [ebp-8h]
  unsigned __int8 (__cdecl **p_decode_mcu)(jpeg_decompress_struct *, __int16 (**)[64]); // [esp+10h] [ebp-4h]
  jpeg_component_info **cinfoa; // [esp+18h] [ebp+4h]

  mem = (jpeg_entropy_decoder *)cinfo[20].mem;
  if ( cinfo[18].err
    || cinfo[18].mem != (jpeg_memory_mgr *)63
    || cinfo[18].progress
    || *(_DWORD *)&cinfo[18].is_decompressor )
  {
    cinfo->err->msg_code = 116;
    cinfo->err->emit_message(cinfo, -1);
  }
  ci = 0;
  if ( (int)cinfo[14].progress > 0 )
  {
    p_decode_mcu = &mem[2].decode_mcu;
    cinfoa = (jpeg_component_info **)&cinfo[14].is_decompressor;
    do
    {
      dc_tbl_no = (*cinfoa)->dc_tbl_no;
      ac_tbl_no = (*cinfoa)->ac_tbl_no;
      if ( dc_tbl_no > 3 || !*((_DWORD *)&cinfo[8].err + dc_tbl_no) )
      {
        cinfo->err->msg_code = 47;
        cinfo->err->msg_parm.i[0] = dc_tbl_no;
        cinfo->err->error_exit(cinfo);
      }
      if ( ac_tbl_no > 3 || !*(&cinfo[8].global_state + ac_tbl_no) )
      {
        cinfo->err->msg_code = 47;
        cinfo->err->msg_parm.i[0] = ac_tbl_no;
        cinfo->err->error_exit(cinfo);
      }
      jpeg_make_d_derived_tbl(
        (jpeg_decompress_struct *)cinfo,
        *((JHUFF_TBL **)&cinfo[8].err + dc_tbl_no),
        (d_derived_tbl **)&mem[5].start_pass + dc_tbl_no);
      jpeg_make_d_derived_tbl(
        (jpeg_decompress_struct *)cinfo,
        *((JHUFF_TBL **)&cinfo[8].global_state + ac_tbl_no),
        (d_derived_tbl **)&mem[7].start_pass + ac_tbl_no);
      ++cinfoa;
      *p_decode_mcu = 0;
      v5 = ++ci < (int)cinfo[14].progress;
      ++p_decode_mcu;
    }
    while ( v5 );
  }
  mem[1].decode_mcu = 0;
  mem[1].start_pass = 0;
  LOBYTE(mem[2].start_pass) = 0;
  mem[4].decode_mcu = *(unsigned __int8 (__cdecl **)(jpeg_decompress_struct *, __int16 (**)[64]))&cinfo[12].is_decompressor;
}

// FUNC: _jinit_huff_decoder
void __cdecl jinit_huff_decoder(jpeg_common_struct *cinfo)
{
  jpeg_entropy_decoder *v1; // eax

  v1 = (jpeg_entropy_decoder *)cinfo->mem->alloc_small(cinfo, 1, 72);
  cinfo[20].mem = (jpeg_memory_mgr *)v1;
  v1->start_pass = (void (__cdecl *)(jpeg_decompress_struct *))start_pass_huff_decoder;
  v1->decode_mcu = decode_mcu;
  v1[7].start_pass = 0;
  v1[5].start_pass = 0;
  v1[7].decode_mcu = 0;
  v1[5].decode_mcu = 0;
  v1[8].start_pass = 0;
  v1[6].start_pass = 0;
  v1[8].decode_mcu = 0;
  v1[6].decode_mcu = 0;
}
