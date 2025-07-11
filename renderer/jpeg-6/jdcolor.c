
// FUNC: build_ycc_rgb_table
void __usercall build_ycc_rgb_table(jpeg_common_struct *cinfo@<eax>)
{
  jpeg_color_deconverter *global_state; // esi
  int v3; // eax
  int v4; // edi
  int v5; // edx
  int v6; // ecx
  int v7; // [esp+10h] [ebp-4h]

  global_state = (jpeg_color_deconverter *)cinfo[20].global_state;
  global_state[1].start_pass = (void (__cdecl *)(jpeg_decompress_struct *))cinfo->mem->alloc_small(cinfo, 1, 1024);
  global_state[1].color_convert = (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 ***, unsigned int, unsigned __int8 **, int))cinfo->mem->alloc_small(cinfo, 1, 1024);
  global_state[2].start_pass = (void (__cdecl *)(jpeg_decompress_struct *))cinfo->mem->alloc_small(cinfo, 1, 1024);
  global_state[2].color_convert = (void (__cdecl *)(jpeg_decompress_struct *, unsigned __int8 ***, unsigned int, unsigned __int8 **, int))cinfo->mem->alloc_small(cinfo, 1, 1024);
  v3 = 0;
  v7 = 5990656;
  v4 = -14831872;
  v5 = -11728000;
  v6 = 2919680;
  do
  {
    *(_DWORD *)((char *)global_state[1].start_pass + v3) = v5 >> 16;
    *(_DWORD *)((char *)global_state[1].color_convert + v3) = v4 >> 16;
    *(_DWORD *)((char *)global_state[2].start_pass + v3) = v7;
    *(_DWORD *)((char *)global_state[2].color_convert + v3) = v6;
    v6 -= 22554;
    v5 += 91881;
    v4 += 116130;
    v3 += 4;
    v7 -= 46802;
  }
  while ( v6 >= -2831590 );
}

// FUNC: ycc_rgb_convert
void __cdecl ycc_rgb_convert(
        jpeg_decompress_struct *cinfo,
        unsigned __int8 ***input_buf,
        unsigned int input_row,
        unsigned __int8 **output_buf,
        int num_rows)
{
  jpeg_color_deconverter *cconvert; // eax
  unsigned __int8 *sample_range_limit; // edx
  unsigned __int8 ***v7; // esi
  unsigned int v8; // edi
  int v9; // ebx
  char *v10; // eax
  _BYTE *v11; // ecx
  int v12; // esi
  int v13; // ebx
  int v14; // ebp
  int v15; // esi
  int v16; // edi
  unsigned int num_cols; // [esp+0h] [ebp-24h]
  int v18; // [esp+4h] [ebp-20h]
  int v19; // [esp+8h] [ebp-1Ch]
  int *Crrtab; // [esp+Ch] [ebp-18h]
  int *Cbgtab; // [esp+10h] [ebp-14h]
  int *Crgtab; // [esp+14h] [ebp-10h]
  unsigned __int8 *range_limit; // [esp+18h] [ebp-Ch]
  int *Cbbtab; // [esp+1Ch] [ebp-8h]
  unsigned int v25; // [esp+20h] [ebp-4h]
  jpeg_decompress_struct *cinfoa; // [esp+28h] [ebp+4h]
  jpeg_decompress_struct *cinfob; // [esp+28h] [ebp+4h]

  cconvert = cinfo->cconvert;
  num_cols = cinfo->output_width;
  sample_range_limit = cinfo->sample_range_limit;
  Crrtab = (int *)cconvert[1].start_pass;
  Cbbtab = (int *)cconvert[1].color_convert;
  Cbgtab = (int *)cconvert[2].color_convert;
  range_limit = sample_range_limit;
  Crgtab = (int *)cconvert[2].start_pass;
  if ( num_rows - 1 >= 0 )
  {
    v7 = input_buf;
    v8 = 4 * input_row;
    do
    {
      v9 = *(int *)((char *)*v7 + v8);
      v10 = *(char **)((char *)v7[1] + v8);
      cinfoa = *(jpeg_decompress_struct **)((char *)v7[2] + v8);
      v11 = *output_buf++;
      v8 += 4;
      v25 = v8;
      if ( num_cols )
      {
        v12 = v9 - (_DWORD)v10;
        v13 = (char *)cinfoa - v10;
        v18 = v12;
        v19 = (char *)cinfoa - v10;
        cinfob = (jpeg_decompress_struct *)num_cols;
        while ( 1 )
        {
          v14 = (unsigned __int8)v10[v13];
          v15 = (unsigned __int8)v10[v12];
          v16 = (unsigned __int8)*v10;
          *v11 = sample_range_limit[v15 + Crrtab[v14]];
          sample_range_limit = range_limit;
          v11[1] = range_limit[v15 + ((Crgtab[v14] + Cbgtab[v16]) >> 16)];
          v11[2] = range_limit[v15 + Cbbtab[v16]];
          v11 += 4;
          ++v10;
          cinfob = (jpeg_decompress_struct *)((char *)cinfob - 1);
          if ( !cinfob )
            break;
          v12 = v18;
          v13 = v19;
        }
        v7 = input_buf;
        v8 = v25;
      }
      --num_rows;
    }
    while ( num_rows );
  }
}

// FUNC: ycck_cmyk_convert
void __cdecl ycck_cmyk_convert(
        jpeg_decompress_struct *cinfo,
        unsigned __int8 ***input_buf,
        unsigned int input_row,
        unsigned __int8 **output_buf,
        int num_rows)
{
  jpeg_color_deconverter *cconvert; // eax
  unsigned __int8 *sample_range_limit; // edx
  unsigned int v7; // esi
  unsigned __int8 ***v8; // edi
  int v9; // ebx
  char *v10; // eax
  _BYTE *v11; // ecx
  int v12; // esi
  int v13; // ebx
  int v14; // ebp
  int v15; // esi
  int v16; // edi
  unsigned int num_cols; // [esp+0h] [ebp-28h]
  unsigned __int8 *inptr3; // [esp+4h] [ebp-24h]
  unsigned __int8 *inptr3a; // [esp+4h] [ebp-24h]
  int v20; // [esp+8h] [ebp-20h]
  int v21; // [esp+Ch] [ebp-1Ch]
  int *Crrtab; // [esp+10h] [ebp-18h]
  int *Cbgtab; // [esp+14h] [ebp-14h]
  int *Crgtab; // [esp+18h] [ebp-10h]
  unsigned __int8 *range_limit; // [esp+1Ch] [ebp-Ch]
  int *Cbbtab; // [esp+20h] [ebp-8h]
  unsigned int v27; // [esp+24h] [ebp-4h]
  jpeg_decompress_struct *cinfoa; // [esp+2Ch] [ebp+4h]
  jpeg_decompress_struct *cinfob; // [esp+2Ch] [ebp+4h]

  cconvert = cinfo->cconvert;
  num_cols = cinfo->output_width;
  sample_range_limit = cinfo->sample_range_limit;
  Crrtab = (int *)cconvert[1].start_pass;
  Cbbtab = (int *)cconvert[1].color_convert;
  Cbgtab = (int *)cconvert[2].color_convert;
  range_limit = sample_range_limit;
  Crgtab = (int *)cconvert[2].start_pass;
  if ( num_rows - 1 >= 0 )
  {
    v7 = 4 * input_row;
    v8 = input_buf;
    do
    {
      v9 = *(int *)((char *)*v8 + v7);
      v10 = *(char **)((char *)v8[1] + v7);
      cinfoa = *(jpeg_decompress_struct **)((char *)v8[2] + v7);
      inptr3 = *(unsigned __int8 **)((char *)v8[3] + v7);
      v11 = *output_buf++;
      v7 += 4;
      v27 = v7;
      if ( num_cols )
      {
        v12 = v9 - (_DWORD)v10;
        v13 = (char *)cinfoa - v10;
        v20 = v12;
        v21 = (char *)cinfoa - v10;
        inptr3a = (unsigned __int8 *)(inptr3 - (unsigned __int8 *)v10);
        cinfob = (jpeg_decompress_struct *)num_cols;
        while ( 1 )
        {
          v14 = (unsigned __int8)v10[v13];
          v15 = (unsigned __int8)v10[v12];
          v16 = (unsigned __int8)*v10;
          *v11 = sample_range_limit[-Crrtab[v14] - v15 + 255];
          sample_range_limit = range_limit;
          v11[1] = range_limit[-((Crgtab[v14] + Cbgtab[v16]) >> 16) - v15 + 255];
          v11 += 4;
          *(v11 - 2) = range_limit[-Cbbtab[v16] - v15 + 255];
          *(v11 - 1) = (v10++)[(_DWORD)inptr3a];
          cinfob = (jpeg_decompress_struct *)((char *)cinfob - 1);
          if ( !cinfob )
            break;
          v12 = v20;
          v13 = v21;
        }
        v8 = input_buf;
        v7 = v27;
      }
      --num_rows;
    }
    while ( num_rows );
  }
}

// FUNC: _jinit_color_deconverter
void __cdecl jinit_color_deconverter(jpeg_common_struct *cinfo)
{
  jpeg_color_deconverter *v1; // edi
  J_COLOR_SPACE global_state; // eax
  bool v3; // zf
  J_COLOR_SPACE v4; // eax
  int v5; // eax
  int v6; // ecx

  v1 = (jpeg_color_deconverter *)cinfo->mem->alloc_small(cinfo, 1, 24);
  cinfo[20].global_state = (int)v1;
  v1->start_pass = (void (__cdecl *)(jpeg_decompress_struct *))SpawnStub;
  switch ( cinfo[1].global_state )
  {
    case 1:
      if ( *(_DWORD *)&cinfo[1].is_decompressor != 1 )
        goto LABEL_9;
      break;
    case 2:
    case 3:
      if ( *(_DWORD *)&cinfo[1].is_decompressor != 3 )
        goto LABEL_9;
      break;
    case 4:
    case 5:
      if ( *(_DWORD *)&cinfo[1].is_decompressor != 4 )
        goto LABEL_9;
      break;
    default:
      if ( *(int *)&cinfo[1].is_decompressor < 1 )
      {
LABEL_9:
        cinfo->err->msg_code = 8;
        cinfo->err->error_exit(cinfo);
      }
      break;
  }
  if ( cinfo[2].err != (jpeg_error_mgr *)1 )
  {
    if ( cinfo[2].err == (jpeg_error_mgr *)2 )
    {
      v3 = cinfo[1].global_state == 3;
      cinfo[5].err = (jpeg_error_mgr *)4;
      if ( v3 )
      {
        v1->color_convert = ycc_rgb_convert;
        build_ycc_rgb_table(cinfo);
        goto LABEL_29;
      }
    }
    else if ( cinfo[2].err == (jpeg_error_mgr *)4 )
    {
      global_state = cinfo[1].global_state;
      cinfo[5].err = (jpeg_error_mgr *)4;
      if ( global_state == JCS_YCCK )
      {
        v1->color_convert = ycck_cmyk_convert;
        build_ycc_rgb_table(cinfo);
        goto LABEL_29;
      }
      if ( global_state == JCS_CMYK )
      {
        v1->color_convert = null_convert_0;
        goto LABEL_29;
      }
    }
    else if ( cinfo[2].err == (jpeg_error_mgr *)cinfo[1].global_state )
    {
      cinfo[5].err = *(jpeg_error_mgr **)&cinfo[1].is_decompressor;
      v1->color_convert = null_convert_0;
      goto LABEL_29;
    }
    goto LABEL_25;
  }
  v4 = cinfo[1].global_state;
  cinfo[5].err = (jpeg_error_mgr *)1;
  if ( v4 != JCS_GRAYSCALE && v4 != JCS_YCbCr )
  {
LABEL_25:
    cinfo->err->msg_code = 23;
    cinfo->err->error_exit(cinfo);
    goto LABEL_29;
  }
  v1->color_convert = grayscale_convert_0;
  v5 = 1;
  if ( *(int *)&cinfo[1].is_decompressor > 1 )
  {
    v6 = 84;
    do
    {
      *(_BYTE *)(v6 + cinfo[9].global_state + 48) = 0;
      ++v5;
      v6 += 84;
    }
    while ( v5 < *(_DWORD *)&cinfo[1].is_decompressor );
  }
LABEL_29:
  if ( *(&cinfo[3].is_decompressor + 2) )
    cinfo[5].mem = (jpeg_memory_mgr *)1;
  else
    cinfo[5].mem = (jpeg_memory_mgr *)cinfo[5].err;
}
