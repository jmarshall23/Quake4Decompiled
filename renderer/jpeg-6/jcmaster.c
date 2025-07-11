
// FUNC: validate_script
void __usercall validate_script(jpeg_common_struct *cinfo@<esi>)
{
  const jpeg_scan_info *mem; // ebx
  bool v2; // cc
  int comps_in_scan; // eax
  int i; // edi
  int v5; // ebx
  signed int Ss; // edi
  int v7; // eax
  unsigned int Ah; // ecx
  unsigned int Al; // edx
  int v10; // eax
  int *v11; // ebx
  int *v12; // ebx
  int v13; // eax
  bool v14; // zf
  int *component_index; // ebx
  unsigned __int8 *v16; // edi
  int v17; // edi
  int (*v18)[64]; // ebx
  int scanno; // [esp+Ch] [ebp-A2Ch]
  int ncomps; // [esp+10h] [ebp-A28h]
  int ncompsa; // [esp+10h] [ebp-A28h]
  const jpeg_scan_info *scanptr; // [esp+14h] [ebp-A24h]
  int v23; // [esp+18h] [ebp-A20h]
  int v24; // [esp+18h] [ebp-A20h]
  int Se; // [esp+1Ch] [ebp-A1Ch]
  int v26; // [esp+20h] [ebp-A18h]
  unsigned int v27; // [esp+24h] [ebp-A14h]
  unsigned int v28; // [esp+28h] [ebp-A10h]
  unsigned __int8 component_sent[10]; // [esp+2Ch] [ebp-A0Ch] BYREF
  int last_bitpos[10][64]; // [esp+38h] [ebp-A00h] BYREF

  if ( (int)cinfo[8].err <= 0 )
  {
    cinfo->err->msg_code = 16;
    cinfo->err->msg_parm.i[0] = 0;
    cinfo->err->error_exit(cinfo);
  }
  mem = (const jpeg_scan_info *)cinfo[8].mem;
  scanptr = mem;
  if ( mem->Ss || mem->Se != 63 )
  {
    v2 = *(_DWORD *)&cinfo[2].is_decompressor <= 0;
    LOBYTE(cinfo[10].err) = 1;
    if ( !v2 )
      memset(last_bitpos, 0xFFu, *(_DWORD *)&cinfo[2].is_decompressor << 8);
  }
  else
  {
    v2 = *(_DWORD *)&cinfo[2].is_decompressor <= 0;
    LOBYTE(cinfo[10].err) = 0;
    if ( !v2 )
      memset(component_sent, 0, *(_DWORD *)&cinfo[2].is_decompressor);
  }
  scanno = 1;
  if ( (int)cinfo[8].err >= 1 )
  {
    do
    {
      comps_in_scan = mem->comps_in_scan;
      ncomps = mem->comps_in_scan;
      if ( mem->comps_in_scan <= 0 || comps_in_scan > 4 )
      {
        cinfo->err->msg_code = 22;
        cinfo->err->msg_parm.i[0] = comps_in_scan;
        cinfo->err->msg_parm.i[1] = 4;
        cinfo->err->error_exit(cinfo);
      }
      for ( i = 0; i < ncomps; ++i )
      {
        v5 = mem->component_index[i];
        if ( v5 < 0 || v5 >= *(_DWORD *)&cinfo[2].is_decompressor )
        {
          cinfo->err->msg_code = 16;
          cinfo->err->msg_parm.i[0] = scanno;
          cinfo->err->error_exit(cinfo);
        }
        if ( i > 0 && v5 <= *(&scanptr->comps_in_scan + i) )
        {
          cinfo->err->msg_code = 16;
          cinfo->err->msg_parm.i[0] = scanno;
          cinfo->err->error_exit(cinfo);
        }
        mem = scanptr;
      }
      Ss = mem->Ss;
      v7 = mem->Se;
      Ah = mem->Ah;
      Al = mem->Al;
      v26 = Ss;
      Se = v7;
      v27 = Ah;
      v28 = Al;
      if ( !LOBYTE(cinfo[10].err) )
      {
        if ( Ss || v7 != 63 || Ah || Al )
        {
          cinfo->err->msg_code = 14;
          cinfo->err->msg_parm.i[0] = scanno;
          cinfo->err->error_exit(cinfo);
        }
        if ( ncomps > 0 )
        {
          component_index = mem->component_index;
          v24 = ncomps;
          do
          {
            v16 = &component_sent[*component_index];
            if ( *v16 )
            {
              cinfo->err->msg_code = 16;
              cinfo->err->msg_parm.i[0] = scanno;
              cinfo->err->error_exit(cinfo);
            }
            ++component_index;
            v14 = v24-- == 1;
            *v16 = 1;
          }
          while ( !v14 );
LABEL_59:
          mem = scanptr;
        }
        goto LABEL_60;
      }
      if ( (unsigned int)Ss > 0x3F || v7 < Ss || v7 >= 64 || Ah > 0xD || Al >= 0xE )
      {
        cinfo->err->msg_code = 14;
        cinfo->err->msg_parm.i[0] = scanno;
        cinfo->err->error_exit(cinfo);
        v7 = Se;
      }
      if ( Ss )
      {
        if ( ncomps == 1 )
          goto LABEL_33;
      }
      else if ( !v7 )
      {
        goto LABEL_33;
      }
      cinfo->err->msg_code = 14;
      cinfo->err->msg_parm.i[0] = scanno;
      cinfo->err->error_exit(cinfo);
LABEL_33:
      v10 = ncomps;
      if ( ncomps > 0 )
      {
        v11 = mem->component_index;
        ncompsa = (int)v11;
        v23 = v10;
        while ( 1 )
        {
          v12 = last_bitpos[*v11];
          if ( Ss && *v12 < 0 )
          {
            cinfo->err->msg_code = 14;
            cinfo->err->msg_parm.i[0] = scanno;
            cinfo->err->error_exit(cinfo);
          }
          if ( v26 <= Se )
            break;
LABEL_47:
          v11 = (int *)(ncompsa + 4);
          v14 = v23-- == 1;
          ncompsa += 4;
          if ( v14 )
            goto LABEL_59;
          Ss = v26;
        }
        while ( 2 )
        {
          v13 = v12[Ss];
          if ( v13 >= 0 )
          {
            if ( v27 != v13 || v28 != v27 - 1 )
            {
LABEL_45:
              cinfo->err->msg_code = 14;
              cinfo->err->msg_parm.i[0] = scanno;
              cinfo->err->error_exit(cinfo);
            }
          }
          else if ( v27 )
          {
            goto LABEL_45;
          }
          v12[Ss++] = v28;
          if ( Ss > Se )
            goto LABEL_47;
          continue;
        }
      }
LABEL_60:
      ++mem;
      v2 = scanno + 1 <= (int)cinfo[8].err;
      scanptr = mem;
      ++scanno;
    }
    while ( v2 );
  }
  v17 = 0;
  if ( LOBYTE(cinfo[10].err) )
  {
    if ( *(int *)&cinfo[2].is_decompressor > 0 )
    {
      v18 = last_bitpos;
      do
      {
        if ( (*v18)[0] < 0 )
        {
          cinfo->err->msg_code = 42;
          cinfo->err->error_exit(cinfo);
        }
        ++v17;
        ++v18;
      }
      while ( v17 < *(_DWORD *)&cinfo[2].is_decompressor );
    }
  }
  else if ( *(int *)&cinfo[2].is_decompressor > 0 )
  {
    do
    {
      if ( !component_sent[v17] )
      {
        cinfo->err->msg_code = 42;
        cinfo->err->error_exit(cinfo);
      }
      ++v17;
    }
    while ( v17 < *(_DWORD *)&cinfo[2].is_decompressor );
  }
}

// FUNC: select_scan_parameters
void __usercall select_scan_parameters(jpeg_common_struct *cinfo@<esi>)
{
  const jpeg_scan_info *mem; // ecx
  int v2; // edi
  int *p_comps_in_scan; // edx
  jpeg_component_info **v4; // ebp
  _DWORD *v5; // ebx
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  jpeg_component_info **v9; // eax

  mem = (const jpeg_scan_info *)cinfo[8].mem;
  v2 = 0;
  if ( mem )
  {
    p_comps_in_scan = &mem[(int)cinfo[15].mem->access_virt_sarray].comps_in_scan;
    cinfo[10].global_state = *p_comps_in_scan;
    if ( *p_comps_in_scan > 0 )
    {
      v4 = (jpeg_component_info **)&cinfo[11];
      v5 = p_comps_in_scan + 1;
      do
      {
        *v4 = (jpeg_component_info *)((char *)cinfo[3].err + 84 * *v5);
        ++v2;
        ++v5;
        ++v4;
      }
      while ( v2 < *p_comps_in_scan );
    }
    cinfo[14].progress = (jpeg_progress_mgr *)p_comps_in_scan[5];
    *(_DWORD *)&cinfo[14].is_decompressor = p_comps_in_scan[6];
    cinfo[14].global_state = p_comps_in_scan[7];
    cinfo[15].err = (jpeg_error_mgr *)p_comps_in_scan[8];
  }
  else
  {
    if ( *(int *)&cinfo[2].is_decompressor > 4 )
    {
      cinfo->err->msg_code = 22;
      cinfo->err->msg_parm.i[0] = *(_DWORD *)&cinfo[2].is_decompressor;
      cinfo->err->msg_parm.i[1] = 4;
      cinfo->err->error_exit(cinfo);
    }
    v6 = *(_DWORD *)&cinfo[2].is_decompressor;
    v7 = 0;
    cinfo[10].global_state = v6;
    if ( v6 > 0 )
    {
      v8 = 0;
      v9 = (jpeg_component_info **)&cinfo[11];
      do
      {
        *v9 = (jpeg_component_info *)((char *)cinfo[3].err + v8);
        ++v7;
        ++v9;
        v8 += 84;
      }
      while ( v7 < *(_DWORD *)&cinfo[2].is_decompressor );
    }
    cinfo[14].progress = 0;
    cinfo[14].global_state = 0;
    cinfo[15].err = 0;
    *(_DWORD *)&cinfo[14].is_decompressor = 63;
  }
}

// FUNC: prepare_for_pass
void __cdecl prepare_for_pass(jpeg_common_struct *cinfo)
{
  jpeg_comp_master *mem; // edi
  void (__cdecl *v2)(jpeg_compress_struct *); // eax
  char *v3; // eax
  int v4; // ecx
  int pass_startup; // eax

  mem = (jpeg_comp_master *)cinfo[15].mem;
  v2 = mem[1].prepare_for_pass;
  if ( v2 )
  {
    v3 = (char *)v2 - 1;
    if ( v3 )
    {
      if ( v3 != (char *)1 )
      {
        cinfo->err->msg_code = 45;
        cinfo->err->error_exit(cinfo);
        goto LABEL_18;
      }
    }
    else
    {
      select_scan_parameters(cinfo);
      per_scan_setup(cinfo);
      if ( cinfo[14].progress || !cinfo[14].global_state || BYTE1(cinfo[8].progress) )
      {
        (*(void (__cdecl **)(jpeg_common_struct *, int))cinfo[16].global_state)(cinfo, 1);
        (*(void (__cdecl **)(jpeg_common_struct *, int))cinfo[15].global_state)(cinfo, 2);
        mem->call_pass_startup = 0;
        goto LABEL_18;
      }
      ++mem[1].pass_startup;
      mem[1].prepare_for_pass = (void (__cdecl *)(jpeg_compress_struct *))2;
    }
    if ( !BYTE2(cinfo[8].progress) )
    {
      select_scan_parameters(cinfo);
      per_scan_setup(cinfo);
    }
    (*(void (__cdecl **)(jpeg_common_struct *, _DWORD))cinfo[16].global_state)(cinfo, 0);
    (*(void (__cdecl **)(jpeg_common_struct *, int))cinfo[15].global_state)(cinfo, 2);
    if ( !*(_DWORD *)&mem[1].call_pass_startup )
      cinfo[16].err->output_message(cinfo);
    ((void (__cdecl *)(jpeg_common_struct *))cinfo[16].err->format_message)(cinfo);
    mem->call_pass_startup = 0;
  }
  else
  {
    select_scan_parameters(cinfo);
    per_scan_setup(cinfo);
    if ( !LOBYTE(cinfo[8].progress) )
    {
      ((void (__cdecl *)(jpeg_common_struct *))cinfo[16].mem->alloc_small)(cinfo);
      cinfo[16].progress->progress_monitor(cinfo);
      (**(void (__cdecl ***)(jpeg_common_struct *, _DWORD))&cinfo[15].is_decompressor)(cinfo, 0);
    }
    (**(void (__cdecl ***)(jpeg_common_struct *))&cinfo[16].is_decompressor)(cinfo);
    LOBYTE(v4) = BYTE2(cinfo[8].progress);
    (*(void (__cdecl **)(jpeg_common_struct *, int))cinfo[16].global_state)(cinfo, v4);
    (*(void (__cdecl **)(jpeg_common_struct *, int))cinfo[15].global_state)(cinfo, (int)mem[1].finish_pass <= 1 ? 0 : 3);
    ((void (__cdecl *)(jpeg_common_struct *, _DWORD))cinfo[15].progress->progress_monitor)(cinfo, 0);
    mem->call_pass_startup = BYTE2(cinfo[8].progress) == 0;
  }
LABEL_18:
  pass_startup = (int)mem[1].pass_startup;
  mem->is_last_pass = (void (__cdecl *)(jpeg_compress_struct *))pass_startup == (void (__cdecl *)(jpeg_compress_struct *))((char *)mem[1].finish_pass - 1);
  if ( cinfo->progress )
  {
    cinfo->progress->completed_passes = pass_startup;
    cinfo->progress->total_passes = (int)mem[1].finish_pass;
  }
}

// FUNC: pass_startup
void __cdecl pass_startup(jpeg_compress_struct *cinfo)
{
  cinfo->master->call_pass_startup = 0;
  cinfo->marker->write_frame_header(cinfo);
  cinfo->marker->write_scan_header(cinfo);
}

// FUNC: finish_pass_master
void __cdecl finish_pass_master(jpeg_compress_struct *cinfo)
{
  jpeg_comp_master *master; // esi
  void (__cdecl *prepare_for_pass)(jpeg_compress_struct *); // eax
  char *v3; // eax

  master = cinfo->master;
  cinfo->entropy->finish_pass(cinfo);
  prepare_for_pass = master[1].prepare_for_pass;
  if ( prepare_for_pass )
  {
    v3 = (char *)prepare_for_pass - 1;
    if ( !v3 )
    {
      ++master[1].pass_startup;
      master[1].prepare_for_pass = (void (__cdecl *)(jpeg_compress_struct *))2;
      return;
    }
    if ( v3 == (char *)1 )
    {
      if ( cinfo->optimize_coding )
      {
        ++*(_DWORD *)&master[1].call_pass_startup;
        ++master[1].pass_startup;
        master[1].prepare_for_pass = (void (__cdecl *)(jpeg_compress_struct *))1;
        return;
      }
      goto LABEL_8;
    }
  }
  else
  {
    master[1].prepare_for_pass = (void (__cdecl *)(jpeg_compress_struct *))2;
    if ( !cinfo->optimize_coding )
LABEL_8:
      ++*(_DWORD *)&master[1].call_pass_startup;
  }
  ++master[1].pass_startup;
}

// FUNC: _jinit_c_master_control
void __cdecl jinit_c_master_control(jpeg_common_struct *cinfo, unsigned __int8 transcode_only)
{
  int v2; // edi

  v2 = cinfo->mem->alloc_small(cinfo, 1, 32);
  cinfo[15].mem = (jpeg_memory_mgr *)v2;
  *(_DWORD *)v2 = prepare_for_pass;
  *(_DWORD *)(v2 + 4) = pass_startup;
  *(_DWORD *)(v2 + 8) = finish_pass_master;
  *(_BYTE *)(v2 + 13) = 0;
  initial_setup(cinfo);
  if ( cinfo[8].mem )
  {
    validate_script(cinfo);
  }
  else
  {
    LOBYTE(cinfo[10].err) = 0;
    cinfo[8].err = (jpeg_error_mgr *)1;
  }
  if ( LOBYTE(cinfo[10].err) )
    BYTE2(cinfo[8].progress) = 1;
  if ( transcode_only )
    *(_DWORD *)(v2 + 16) = 2 - (BYTE2(cinfo[8].progress) != 0);
  else
    *(_DWORD *)(v2 + 16) = 0;
  *(_DWORD *)(v2 + 28) = 0;
  *(_DWORD *)(v2 + 20) = 0;
  if ( BYTE2(cinfo[8].progress) )
    *(_DWORD *)(v2 + 24) = 2 * (int)cinfo[8].err;
  else
    *(_DWORD *)(v2 + 24) = cinfo[8].err;
}
