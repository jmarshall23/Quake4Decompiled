
// FUNC: realize_virt_arrays
void __cdecl realize_virt_arrays(jpeg_common_struct *cinfo)
{
  jpeg_memory_mgr *mem; // edx
  jvirt_sarray_control *(__cdecl *request_virt_sarray)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int); // eax
  int v4; // esi
  int v5; // edi
  int v6; // ecx
  jvirt_barray_control *(__cdecl *i)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int); // eax
  int v8; // ecx
  int v9; // eax
  int v10; // ebp
  jpeg_memory_mgr *j; // esi
  void *(__cdecl *alloc_large)(jpeg_common_struct *, int, unsigned int); // edi
  __int16 (**(__cdecl *alloc_barray)(jpeg_common_struct *, int, unsigned int, unsigned int))[64]; // ecx
  jpeg_progress_mgr *k; // esi
  int pass_counter; // edi
  unsigned int completed_passes; // ecx
  int v17; // eax
  int v18; // [esp-4h] [ebp-14h]
  jpeg_common_struct *cinfoa; // [esp+14h] [ebp+4h]

  mem = cinfo->mem;
  request_virt_sarray = mem[1].request_virt_sarray;
  v4 = 0;
  v5 = 0;
  for ( cinfoa = (jpeg_common_struct *)mem;
        request_virt_sarray;
        request_virt_sarray = (jvirt_sarray_control *(__cdecl *)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int))*((_DWORD *)request_virt_sarray + 9) )
  {
    if ( !*(_DWORD *)request_virt_sarray )
    {
      v6 = *((_DWORD *)request_virt_sarray + 2);
      v4 += v6 * *((_DWORD *)request_virt_sarray + 3);
      v5 += v6 * *((_DWORD *)request_virt_sarray + 1);
    }
  }
  for ( i = mem[1].request_virt_barray;
        i;
        i = (jvirt_barray_control *(__cdecl *)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int))*((_DWORD *)i + 9) )
  {
    if ( !*(_DWORD *)i )
    {
      v8 = *((_DWORD *)i + 2);
      v4 += (v8 * *((_DWORD *)i + 3)) << 7;
      v5 += (v8 * *((_DWORD *)i + 1)) << 7;
    }
  }
  if ( v4 > 0 )
  {
    v9 = jpeg_mem_available(cinfo, v4, v5, (int)mem[1].realize_virt_arrays);
    if ( v9 < v5 )
    {
      v10 = v9 / v4;
      if ( v9 / v4 <= 0 )
        v10 = 1;
    }
    else
    {
      v10 = 1000000000;
    }
    for ( j = cinfoa[3].mem; j; j = (jpeg_memory_mgr *)j->free_pool )
    {
      if ( !j->alloc_small )
      {
        alloc_large = j->alloc_large;
        alloc_barray = j->alloc_barray;
        if ( (int)(((unsigned int)alloc_large - 1) / (unsigned int)alloc_barray + 1) > v10 )
        {
          v18 = (_DWORD)alloc_large * (int)j->alloc_sarray;
          j->request_virt_sarray = (jvirt_sarray_control *(__cdecl *)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int))(v10 * (_DWORD)alloc_barray);
          jpeg_open_backing_store(cinfo, (backing_store_struct *)&j->self_destruct, v18);
          BYTE2(j->access_virt_barray) = 1;
        }
        else
        {
          j->request_virt_sarray = (jvirt_sarray_control *(__cdecl *)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int))alloc_large;
        }
        j->alloc_small = (void *(__cdecl *)(jpeg_common_struct *, int, unsigned int))alloc_sarray(
                                                                                       cinfo,
                                                                                       1,
                                                                                       (unsigned int)j->alloc_sarray,
                                                                                       (signed int)j->request_virt_sarray);
        j->request_virt_barray = (jvirt_barray_control *(__cdecl *)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int))cinfoa[3].global_state;
        j->realize_virt_arrays = 0;
        j->access_virt_sarray = 0;
        BYTE1(j->access_virt_barray) = 0;
      }
    }
    for ( k = cinfoa[3].progress; k; k = (jpeg_progress_mgr *)k[1].total_passes )
    {
      if ( !k->progress_monitor )
      {
        pass_counter = k->pass_counter;
        completed_passes = k->completed_passes;
        if ( (int)((pass_counter - 1) / completed_passes + 1) > v10 )
        {
          v17 = (pass_counter * k->pass_limit) << 7;
          k->total_passes = v10 * completed_passes;
          jpeg_open_backing_store(cinfo, (backing_store_struct *)&k[2], v17);
          BYTE2(k[1].completed_passes) = 1;
        }
        else
        {
          k->total_passes = pass_counter;
        }
        k->progress_monitor = (void (__cdecl *)(jpeg_common_struct *))::alloc_barray(
                                                                        cinfo,
                                                                        1,
                                                                        k->pass_limit,
                                                                        k->total_passes);
        k[1].progress_monitor = (void (__cdecl *)(jpeg_common_struct *))cinfoa[3].global_state;
        k[1].pass_counter = 0;
        k[1].pass_limit = 0;
        BYTE1(k[1].completed_passes) = 0;
      }
    }
  }
}

// FUNC: do_sarray_io
void __usercall do_sarray_io(jvirt_sarray_control *ptr@<esi>, jpeg_common_struct *cinfo, unsigned __int8 writing)
{
  signed int rows_in_mem; // eax
  unsigned int samplesperrow; // ebp
  int v5; // ebx
  signed int v6; // edi
  signed int rowsperchunk; // eax
  unsigned int v8; // ecx
  int v9; // ebp
  int bytesperrow; // [esp+Ch] [ebp-4h]

  rows_in_mem = ptr->rows_in_mem;
  samplesperrow = ptr->samplesperrow;
  v5 = samplesperrow * ptr->cur_start_row;
  v6 = 0;
  bytesperrow = samplesperrow;
  if ( rows_in_mem > 0 )
  {
    while ( 1 )
    {
      rowsperchunk = rows_in_mem - v6;
      if ( (signed int)ptr->rowsperchunk < rowsperchunk )
        rowsperchunk = ptr->rowsperchunk;
      v8 = v6 + ptr->cur_start_row;
      if ( rowsperchunk >= (int)(ptr->first_undef_row - v8) )
        rowsperchunk = ptr->first_undef_row - v8;
      if ( rowsperchunk >= (int)(ptr->rows_in_array - v8) )
        rowsperchunk = ptr->rows_in_array - v8;
      if ( rowsperchunk <= 0 )
        break;
      v9 = samplesperrow * rowsperchunk;
      if ( writing )
        ptr->b_s_info.write_backing_store(cinfo, &ptr->b_s_info, ptr->mem_buffer[v6], v5, v9);
      else
        ptr->b_s_info.read_backing_store(cinfo, &ptr->b_s_info, ptr->mem_buffer[v6], v5, v9);
      v6 += ptr->rowsperchunk;
      rows_in_mem = ptr->rows_in_mem;
      v5 += v9;
      if ( v6 >= rows_in_mem )
        break;
      samplesperrow = bytesperrow;
    }
  }
}

// FUNC: do_barray_io
void __usercall do_barray_io(jvirt_barray_control *ptr@<esi>, jpeg_common_struct *cinfo, unsigned __int8 writing)
{
  signed int rows_in_mem; // eax
  unsigned int v4; // ebp
  int v5; // ebx
  signed int v6; // edi
  signed int rowsperchunk; // eax
  unsigned int v8; // ecx
  int v9; // ebp
  int bytesperrow; // [esp+Ch] [ebp-4h]

  rows_in_mem = ptr->rows_in_mem;
  v4 = ptr->blocksperrow << 7;
  v5 = v4 * ptr->cur_start_row;
  v6 = 0;
  bytesperrow = v4;
  if ( rows_in_mem > 0 )
  {
    while ( 1 )
    {
      rowsperchunk = rows_in_mem - v6;
      if ( (signed int)ptr->rowsperchunk < rowsperchunk )
        rowsperchunk = ptr->rowsperchunk;
      v8 = v6 + ptr->cur_start_row;
      if ( rowsperchunk >= (int)(ptr->first_undef_row - v8) )
        rowsperchunk = ptr->first_undef_row - v8;
      if ( rowsperchunk >= (int)(ptr->rows_in_array - v8) )
        rowsperchunk = ptr->rows_in_array - v8;
      if ( rowsperchunk <= 0 )
        break;
      v9 = v4 * rowsperchunk;
      if ( writing )
        ptr->b_s_info.write_backing_store(cinfo, &ptr->b_s_info, ptr->mem_buffer[v6], v5, v9);
      else
        ptr->b_s_info.read_backing_store(cinfo, &ptr->b_s_info, ptr->mem_buffer[v6], v5, v9);
      v6 += ptr->rowsperchunk;
      rows_in_mem = ptr->rows_in_mem;
      v5 += v9;
      if ( v6 >= rows_in_mem )
        break;
      v4 = bytesperrow;
    }
  }
}

// FUNC: free_pool
void __cdecl free_pool(jpeg_common_struct *cinfo, unsigned int pool_id)
{
  unsigned int v2; // ebp
  jpeg_memory_mgr *mem; // esi
  jvirt_sarray_control *(__cdecl *i)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int); // edi
  jvirt_barray_control *(__cdecl *request_virt_barray)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int); // edi
  _DWORD *v6; // eax
  _DWORD *v7; // edi
  unsigned int v8; // ebp
  _DWORD *v9; // eax
  _DWORD *v10; // edi
  unsigned int v11; // ebp

  v2 = pool_id;
  mem = cinfo->mem;
  if ( pool_id >= 2 )
  {
    cinfo->err->msg_code = 11;
    cinfo->err->msg_parm.i[0] = pool_id;
    cinfo->err->error_exit(cinfo);
  }
  if ( pool_id == 1 )
  {
    for ( i = mem[1].request_virt_sarray;
          i;
          i = (jvirt_sarray_control *(__cdecl *)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int))*((_DWORD *)i + 9) )
    {
      if ( *((_BYTE *)i + 34) )
      {
        *((_BYTE *)i + 34) = 0;
        (*((void (__cdecl **)(jpeg_common_struct *, int))i + 12))(cinfo, (int)i + 40);
      }
    }
    request_virt_barray = mem[1].request_virt_barray;
    for ( mem[1].request_virt_sarray = 0;
          request_virt_barray;
          request_virt_barray = (jvirt_barray_control *(__cdecl *)(jpeg_common_struct *, int, unsigned __int8, unsigned int, unsigned int, unsigned int))*((_DWORD *)request_virt_barray + 9) )
    {
      if ( *((_BYTE *)request_virt_barray + 34) )
      {
        *((_BYTE *)request_virt_barray + 34) = 0;
        (*((void (__cdecl **)(jpeg_common_struct *, int))request_virt_barray + 12))(
          cinfo,
          (int)request_virt_barray + 40);
      }
    }
    mem[1].request_virt_barray = 0;
  }
  v6 = (_DWORD *)*((_DWORD *)&mem[1].alloc_sarray + pool_id);
  *((_DWORD *)&mem[1].alloc_sarray + pool_id) = 0;
  if ( v6 )
  {
    do
    {
      v7 = (_DWORD *)*v6;
      v8 = v6[2] + v6[1] + 16;
      jpeg_free_small(cinfo, v6, v8);
      mem[1].realize_virt_arrays = (void (__cdecl *)(jpeg_common_struct *))((char *)mem[1].realize_virt_arrays - v8);
      v6 = v7;
    }
    while ( v7 );
    v2 = pool_id;
  }
  v9 = (_DWORD *)*((_DWORD *)&mem[1].alloc_small + v2);
  *((_DWORD *)&mem[1].alloc_small + v2) = 0;
  if ( v9 )
  {
    do
    {
      v10 = (_DWORD *)*v9;
      v11 = v9[2] + v9[1] + 16;
      jpeg_free_small(cinfo, v9, v11);
      mem[1].realize_virt_arrays = (void (__cdecl *)(jpeg_common_struct *))((char *)mem[1].realize_virt_arrays - v11);
      v9 = v10;
    }
    while ( v10 );
  }
}

// FUNC: self_destruct
void __cdecl self_destruct(jpeg_common_struct *cinfo)
{
  signed int i; // esi

  for ( i = 1; i >= 0; --i )
    free_pool(cinfo, i);
  jpeg_free_small(cinfo, cinfo->mem, 0x50u);
  cinfo->mem = 0;
  SpawnStub((const idCmdArgs *)cinfo);
}

// FUNC: _jinit_memory_mgr
void __cdecl jinit_memory_mgr(jpeg_common_struct *cinfo)
{
  idFile_Common *v1; // ecx
  jpeg_common_struct *v2; // edi
  int (__cdecl **small)(jpeg_common_struct *, unsigned int, unsigned int); // esi
  const char *v4; // eax
  int v5; // eax
  int max_to_use; // [esp+Ch] [ebp-4h] BYREF

  v2 = cinfo;
  cinfo->mem = 0;
  max_to_use = idFile_Common::Timestamp(v1);
  small = (int (__cdecl **)(jpeg_common_struct *, unsigned int, unsigned int))jpeg_get_small(v2, 0x50u);
  if ( !small )
  {
    SpawnStub();
    v2->err->msg_code = 51;
    v2->err->msg_parm.i[0] = 0;
    ((void (__cdecl *)(jpeg_common_struct *, jpeg_common_struct *))v2->err->error_exit)(v2, v2);
  }
  *small = alloc_small;
  small[1] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))alloc_large;
  small[2] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))alloc_sarray;
  small[3] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))alloc_barray;
  small[4] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))request_virt_sarray;
  small[5] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))request_virt_barray;
  small[6] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))realize_virt_arrays;
  small[7] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))access_virt_sarray;
  small[8] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))access_virt_barray;
  small[9] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))free_pool;
  small[10] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))self_destruct;
  small[11] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))max_to_use;
  small[13] = 0;
  small[15] = 0;
  small[12] = 0;
  small[14] = 0;
  small[16] = 0;
  small[17] = 0;
  small[18] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))80;
  v2->mem = (jpeg_memory_mgr *)small;
  v4 = getenv("JPEGMEM");
  if ( v4 )
  {
    LOBYTE(cinfo) = 120;
    if ( sscanf(v4, "%ld%c", &max_to_use, &cinfo) > 0 )
    {
      if ( (_BYTE)cinfo == 109 || (_BYTE)cinfo == 77 )
        v5 = 1000 * max_to_use;
      else
        v5 = max_to_use;
      small[11] = (int (__cdecl *)(jpeg_common_struct *, unsigned int, unsigned int))(1000 * v5);
    }
  }
}
