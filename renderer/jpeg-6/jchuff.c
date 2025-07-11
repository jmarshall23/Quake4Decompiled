
// FUNC: _jpeg_make_c_derived_tbl
void __cdecl jpeg_make_c_derived_tbl(jpeg_common_struct *cinfo, JHUFF_TBL *htbl, c_derived_tbl **pdtbl)
{
  JHUFF_TBL *v3; // ebp
  int v4; // eax
  int i; // edx
  unsigned int v6; // esi
  char *v7; // edi
  int v8; // eax
  int v9; // ebx
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // esi
  char *v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // ecx
  char v17; // dl
  int p; // [esp+10h] [ebp-514h]
  c_derived_tbl *dtbl; // [esp+14h] [ebp-510h]
  int v20; // [esp+18h] [ebp-50Ch]
  char huffsize[257]; // [esp+1Ch] [ebp-508h] BYREF
  unsigned int huffcode[257]; // [esp+120h] [ebp-404h]

  if ( !*pdtbl )
    *pdtbl = (c_derived_tbl *)cinfo->mem->alloc_small(cinfo, 1, 1280);
  v3 = htbl;
  v4 = 0;
  dtbl = *pdtbl;
  p = 0;
  for ( i = 1; i <= 16; ++i )
  {
    v6 = v3->bits[i];
    if ( v3->bits[i] )
    {
      v20 = i;
      BYTE1(i) = i;
      v3 = htbl;
      v7 = &huffsize[v4];
      v8 = i << 16;
      LOWORD(v8) = i;
      i = v20;
      memset32(v7, v8, v6 >> 2);
      memset(&v7[4 * (v6 >> 2)], v8, v6 & 3);
      v4 = v6 + p;
      p += v6;
    }
  }
  huffsize[v4] = 0;
  v9 = v4;
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
  memset(dtbl->ehufsi, 0, sizeof(dtbl->ehufsi));
  if ( v9 > 0 )
  {
    do
    {
      dtbl->ehufco[v3->huffval[v15]] = huffcode[v15];
      v16 = v3->huffval[v15];
      v17 = huffsize[v15++];
      dtbl->ehufsi[v16] = v17;
    }
    while ( v15 < v9 );
  }
}

// FUNC: finish_pass_huff
void __cdecl finish_pass_huff(jpeg_compress_struct *cinfo)
{
  jpeg_destination_mgr *dest; // eax
  unsigned __int8 *next_output_byte; // edx
  unsigned int free_in_buffer; // eax
  int *v4; // edi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int put_buffer; // ecx
  int put_bits; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  working_state state; // [esp+Ch] [ebp-24h] BYREF

  dest = cinfo->dest;
  next_output_byte = dest->next_output_byte;
  free_in_buffer = dest->free_in_buffer;
  v4 = (int *)&cinfo->entropy[1];
  state.next_output_byte = next_output_byte;
  state.free_in_buffer = free_in_buffer;
  v5 = v4[1];
  state.cur.put_buffer = *v4;
  v6 = v4[2];
  state.cur.put_bits = v5;
  v7 = v4[3];
  state.cur.last_dc_val[0] = v6;
  v8 = v4[4];
  state.cur.last_dc_val[1] = v7;
  state.cur.last_dc_val[3] = v4[5];
  state.cur.last_dc_val[2] = v8;
  state.cinfo = cinfo;
  if ( emit_bits(&state, 7, 0x7Fu) )
  {
    put_buffer = 0;
    put_bits = 0;
  }
  else
  {
    cinfo->err->msg_code = 20;
    cinfo->err->error_exit((jpeg_common_struct *)cinfo);
    put_bits = state.cur.put_bits;
    put_buffer = state.cur.put_buffer;
  }
  cinfo->dest->next_output_byte = state.next_output_byte;
  cinfo->dest->free_in_buffer = state.free_in_buffer;
  v11 = state.cur.last_dc_val[2];
  *v4 = put_buffer;
  v12 = state.cur.last_dc_val[1];
  v4[1] = put_bits;
  v4[2] = state.cur.last_dc_val[0];
  v13 = state.cur.last_dc_val[3];
  v4[3] = v12;
  v4[4] = v11;
  v4[5] = v13;
}

// FUNC: htest_one_block
void __usercall htest_one_block(int *dc_counts@<edx>, int *ac_counts@<edi>, __int16 *block, int last_dc_val)
{
  int v4; // eax
  int i; // ecx
  int v6; // ecx
  _DWORD *v7; // ebx
  int v8; // edx
  unsigned int v9; // eax
  int v10; // edx
  int j; // eax

  v4 = *block - last_dc_val;
  if ( v4 < 0 )
    v4 = last_dc_val - *block;
  for ( i = 0; v4; v4 >>= 1 )
    ++i;
  ++dc_counts[i];
  v6 = 0;
  v7 = &unk_102C95DC;
  do
  {
    v8 = block[*v7];
    if ( block[*v7] )
    {
      if ( v6 > 15 )
      {
        v9 = ((unsigned int)(v6 - 16) >> 4) + 1;
        v6 += -16 * v9;
        ac_counts[240] += v9;
      }
      if ( v8 < 0 )
        v8 = -v8;
      v10 = v8 >> 1;
      for ( j = 1; v10; v10 >>= 1 )
        ++j;
      ++ac_counts[16 * v6 + j];
      v6 = 0;
    }
    else
    {
      ++v6;
    }
    ++v7;
  }
  while ( (int)v7 < (int)&unk_102C96D8 );
  if ( v6 > 0 )
    ++*ac_counts;
}

// FUNC: _jpeg_gen_optimal_table
void __cdecl jpeg_gen_optimal_table(jpeg_common_struct *cinfo, JHUFF_TBL *htbl, int *freq)
{
  int v3; // eax
  int v4; // esi
  int i; // ecx
  int v6; // edx
  int v7; // edx
  int v8; // edi
  int j; // ecx
  int v10; // esi
  bool v11; // sf
  int *v12; // ecx
  int *v13; // eax
  int v14; // eax
  int k; // edi
  int v16; // esi
  int v17; // esi
  int v18; // ecx
  int v19; // edx
  int m; // eax
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // ecx
  int n; // edx
  int ii; // eax
  unsigned __int8 bits[33]; // [esp+Ch] [ebp-834h] BYREF
  int codesize[257]; // [esp+30h] [ebp-810h] BYREF
  int others[257]; // [esp+438h] [ebp-408h] BYREF

  memset(bits, 0, sizeof(bits));
  memset(codesize, 0, sizeof(codesize));
  memset(others, 0xFFu, sizeof(others));
  freq[256] = 1;
  while ( 1 )
  {
    v3 = -1;
    v4 = 1000000000;
    for ( i = 0; i <= 256; ++i )
    {
      v6 = freq[i];
      if ( v6 && v6 <= v4 )
      {
        v4 = freq[i];
        v3 = i;
      }
    }
    v7 = -1;
    v8 = 1000000000;
    for ( j = 0; j <= 256; ++j )
    {
      v10 = freq[j];
      if ( v10 && v10 <= v8 && j != v3 )
      {
        v8 = freq[j];
        v7 = j;
      }
    }
    if ( v7 < 0 )
      break;
    freq[v3] += freq[v7];
    ++codesize[v3];
    v11 = others[v3] < 0;
    v12 = &others[v3];
    freq[v7] = 0;
    if ( !v11 )
    {
      do
      {
        v3 = *v12;
        ++codesize[v3];
        v12 = &others[v3];
      }
      while ( *v12 >= 0 );
    }
    ++codesize[v7];
    others[v3] = v7;
    v13 = &others[v7];
    if ( *v13 >= 0 )
    {
      do
      {
        v14 = *v13;
        ++codesize[v14];
        v11 = others[v14] < 0;
        v13 = &others[v14];
      }
      while ( !v11 );
    }
  }
  for ( k = 0; k <= 256; ++k )
  {
    v16 = codesize[k];
    if ( v16 )
    {
      if ( v16 > 32 )
      {
        cinfo->err->msg_code = 36;
        cinfo->err->error_exit(cinfo);
      }
      ++bits[v16];
    }
  }
  v17 = 16;
  v18 = 30;
  v19 = 16;
  do
  {
    for ( ; bits[v18 + 2]; --bits[m] )
    {
      for ( m = v18; !bits[m]; --m )
        ;
      bits[v18 + 2] -= 2;
      ++bits[v18 + 1];
      bits[m + 1] += 2;
    }
    --v18;
    --v17;
  }
  while ( v17 );
  if ( !bits[16] )
  {
    do
      --v19;
    while ( !bits[v19] );
  }
  --bits[v19];
  v21 = *(_DWORD *)&bits[4];
  *(_DWORD *)htbl->bits = *(_DWORD *)bits;
  v22 = *(_DWORD *)&bits[8];
  *(_DWORD *)&htbl->bits[4] = v21;
  v23 = *(_DWORD *)&bits[12];
  *(_DWORD *)&htbl->bits[8] = v22;
  LOBYTE(v22) = bits[16];
  *(_DWORD *)&htbl->bits[12] = v23;
  htbl->bits[16] = v22;
  v24 = 0;
  for ( n = 1; n <= 32; ++n )
  {
    for ( ii = 0; ii <= 255; ++ii )
    {
      if ( codesize[ii] == n )
        htbl->huffval[v24++] = ii;
    }
  }
  htbl->sent_table = 0;
}

// FUNC: finish_pass_gather
void __cdecl finish_pass_gather(jpeg_common_struct *cinfo)
{
  bool v2; // cc
  int dc_tbl_no; // edi
  int ac_tbl_no; // ebp
  huff_entropy_encoder *entropy; // [esp+4h] [ebp-10h]
  int ci; // [esp+8h] [ebp-Ch]
  unsigned __int8 did_dc[4]; // [esp+Ch] [ebp-8h]
  unsigned __int8 did_ac[4]; // [esp+10h] [ebp-4h]
  jpeg_component_info **cinfoa; // [esp+18h] [ebp+4h]

  entropy = (huff_entropy_encoder *)cinfo[16].global_state;
  v2 = cinfo[10].global_state <= 0;
  *(_DWORD *)did_dc = 0;
  *(_DWORD *)did_ac = 0;
  ci = 0;
  if ( !v2 )
  {
    cinfoa = (jpeg_component_info **)&cinfo[11];
    do
    {
      dc_tbl_no = (*cinfoa)->dc_tbl_no;
      ac_tbl_no = (*cinfoa)->ac_tbl_no;
      if ( !did_dc[dc_tbl_no] )
      {
        if ( !*((_DWORD *)&cinfo[4].err + dc_tbl_no) )
          *((_DWORD *)&cinfo[4].err + dc_tbl_no) = jpeg_alloc_huff_table(cinfo);
        jpeg_gen_optimal_table(
          (jpeg_compress_struct *)cinfo,
          *((JHUFF_TBL **)&cinfo[4].err + dc_tbl_no),
          entropy->dc_count_ptrs[dc_tbl_no]);
        did_dc[dc_tbl_no] = 1;
      }
      if ( !did_ac[ac_tbl_no] )
      {
        if ( !*(&cinfo[4].global_state + ac_tbl_no) )
          *(&cinfo[4].global_state + ac_tbl_no) = (int)jpeg_alloc_huff_table(cinfo);
        jpeg_gen_optimal_table(
          (jpeg_compress_struct *)cinfo,
          *((JHUFF_TBL **)&cinfo[4].global_state + ac_tbl_no),
          entropy->ac_count_ptrs[ac_tbl_no]);
        did_ac[ac_tbl_no] = 1;
      }
      ++cinfoa;
      ++ci;
    }
    while ( ci < cinfo[10].global_state );
  }
}

// FUNC: start_pass_huff
void __cdecl start_pass_huff(jpeg_common_struct *cinfo, unsigned __int8 gather_statistics)
{
  jpeg_entropy_encoder *global_state; // ebp
  unsigned int dc_tbl_no; // edi
  unsigned int ac_tbl_no; // ebx
  bool v6; // cc
  int ci; // [esp+8h] [ebp-8h]
  void (__cdecl **p_finish_pass)(jpeg_compress_struct *); // [esp+Ch] [ebp-4h]
  jpeg_component_info **cinfoa; // [esp+14h] [ebp+4h]

  global_state = (jpeg_entropy_encoder *)cinfo[16].global_state;
  if ( gather_statistics )
  {
    global_state->encode_mcu = encode_mcu_gather;
    global_state->finish_pass = (void (__cdecl *)(jpeg_compress_struct *))finish_pass_gather;
  }
  else
  {
    global_state->encode_mcu = encode_mcu_huff;
    global_state->finish_pass = finish_pass_huff;
  }
  ci = 0;
  if ( cinfo[10].global_state > 0 )
  {
    p_finish_pass = &global_state[1].finish_pass;
    cinfoa = (jpeg_component_info **)&cinfo[11];
    do
    {
      dc_tbl_no = (*cinfoa)->dc_tbl_no;
      ac_tbl_no = (*cinfoa)->ac_tbl_no;
      if ( dc_tbl_no > 3 || !*((_DWORD *)&cinfo[4].err + dc_tbl_no) && !gather_statistics )
      {
        cinfo->err->msg_code = 47;
        cinfo->err->msg_parm.i[0] = dc_tbl_no;
        cinfo->err->error_exit(cinfo);
      }
      if ( ac_tbl_no <= 3 )
      {
        if ( *(&cinfo[4].global_state + ac_tbl_no) )
          goto LABEL_14;
        if ( gather_statistics )
          goto LABEL_15;
      }
      cinfo->err->msg_code = 47;
      cinfo->err->msg_parm.i[0] = ac_tbl_no;
      cinfo->err->error_exit(cinfo);
LABEL_14:
      if ( gather_statistics )
      {
LABEL_15:
        if ( !*((_DWORD *)&global_state[6].encode_mcu + dc_tbl_no) )
          *((_DWORD *)&global_state[6].encode_mcu + dc_tbl_no) = cinfo->mem->alloc_small(cinfo, 1, 1028);
        memset(*((void **)&global_state[6].encode_mcu + dc_tbl_no), 0, 0x404u);
        if ( !*((_DWORD *)&global_state[7].finish_pass + ac_tbl_no) )
          *((_DWORD *)&global_state[7].finish_pass + ac_tbl_no) = cinfo->mem->alloc_small(cinfo, 1, 1028);
        memset(*((void **)&global_state[7].finish_pass + ac_tbl_no), 0, 0x404u);
        goto LABEL_21;
      }
      jpeg_make_c_derived_tbl(
        (jpeg_compress_struct *)cinfo,
        *((JHUFF_TBL **)&cinfo[4].err + dc_tbl_no),
        (c_derived_tbl **)&global_state[3].finish_pass + dc_tbl_no);
      jpeg_make_c_derived_tbl(
        (jpeg_compress_struct *)cinfo,
        *((JHUFF_TBL **)&cinfo[4].global_state + ac_tbl_no),
        (c_derived_tbl **)&global_state[5].start_pass + ac_tbl_no);
LABEL_21:
      ++cinfoa;
      *p_finish_pass = 0;
      v6 = ++ci < cinfo[10].global_state;
      ++p_finish_pass;
    }
    while ( v6 );
  }
  global_state[1].start_pass = 0;
  global_state[1].encode_mcu = 0;
  global_state[3].start_pass = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8))cinfo[9].err;
  global_state[3].encode_mcu = 0;
}

// FUNC: _jinit_huff_encoder
void __cdecl jinit_huff_encoder(jpeg_common_struct *cinfo)
{
  jpeg_entropy_encoder *v1; // eax

  v1 = (jpeg_entropy_encoder *)cinfo->mem->alloc_small(cinfo, 1, 108);
  cinfo[16].global_state = (int)v1;
  v1->start_pass = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8))start_pass_huff;
  v1[5].start_pass = 0;
  v1[3].finish_pass = 0;
  v1[7].finish_pass = 0;
  v1[6].encode_mcu = 0;
  v1[5].encode_mcu = 0;
  v1[4].start_pass = 0;
  v1[8].start_pass = 0;
  v1[6].finish_pass = 0;
  v1[5].finish_pass = 0;
  v1[4].encode_mcu = 0;
  v1[8].encode_mcu = 0;
  v1[7].start_pass = 0;
  v1[6].start_pass = 0;
  v1[4].finish_pass = 0;
  v1[8].finish_pass = 0;
  v1[7].encode_mcu = 0;
}
