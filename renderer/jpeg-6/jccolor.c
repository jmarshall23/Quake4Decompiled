
// FUNC: rgb_ycc_start
void __cdecl rgb_ycc_start(jpeg_common_struct *cinfo)
{
  jpeg_color_converter *mem; // esi
  int v2; // eax
  int v3; // edx
  int v4; // ebx
  int v5; // edi
  int v6; // esi
  int v7; // ecx
  int *v8; // eax
  int v9; // ebp
  int v10; // ebp
  int v11; // ebp
  int v12; // [esp+10h] [ebp-8h]
  int v13; // [esp+14h] [ebp-4h]
  int cinfoa; // [esp+1Ch] [ebp+4h]

  mem = (jpeg_color_converter *)cinfo[16].mem;
  v2 = cinfo->mem->alloc_small(cinfo, 1, 0x2000);
  v3 = 0;
  mem[1].start_pass = (void (__cdecl *)(jpeg_compress_struct *))v2;
  v4 = 0;
  v5 = 0;
  v6 = 0;
  v13 = 0;
  v12 = 0;
  cinfoa = 8421375;
  v7 = 0x8000;
  v8 = (int *)(v2 + 2048);
  do
  {
    v9 = cinfoa;
    cinfoa += 0x8000;
    v8[768] = v9;
    v10 = v12;
    v12 -= 27439;
    v8[1024] = v10;
    v11 = v13;
    v13 -= 5329;
    *v8 = v7;
    *(v8 - 512) = v3;
    *(v8 - 256) = v6;
    v8[256] = v5;
    v8[512] = v4;
    v8[1280] = v11;
    v7 += 7471;
    v3 += 19595;
    ++v8;
    v6 += 38470;
    v5 -= 11059;
    v4 -= 21709;
  }
  while ( v7 <= 1937873 );
}

// FUNC: rgb_ycc_convert
void __cdecl rgb_ycc_convert(
        jpeg_compress_struct *cinfo,
        unsigned __int8 **input_buf,
        unsigned __int8 ***output_buf,
        unsigned int output_row,
        int num_rows)
{
  void (__cdecl *start_pass)(jpeg_compress_struct *); // eax
  unsigned int v6; // edx
  unsigned __int8 ***v7; // edi
  unsigned __int8 *v8; // esi
  unsigned __int8 *v9; // ebx
  unsigned __int8 *v10; // ecx
  int v11; // ebp
  int v12; // edi
  bool v13; // zf
  unsigned int num_cols; // [esp+0h] [ebp-14h]
  int v15; // [esp+4h] [ebp-10h]
  int b; // [esp+8h] [ebp-Ch]
  char *v17; // [esp+Ch] [ebp-8h]
  jpeg_compress_struct *cinfoa; // [esp+18h] [ebp+4h]
  jpeg_compress_struct *cinfob; // [esp+18h] [ebp+4h]

  start_pass = cinfo->cconvert[1].start_pass;
  num_cols = cinfo->image_width;
  if ( num_rows - 1 >= 0 )
  {
    v6 = output_row;
    v7 = output_buf;
    do
    {
      v8 = *input_buf++;
      v9 = (*v7)[v6];
      v10 = v7[1][v6];
      cinfoa = (jpeg_compress_struct *)v7[2][v6++];
      if ( num_cols )
      {
        v15 = v9 - v10;
        v17 = (char *)((char *)cinfoa - (char *)v10);
        cinfob = (jpeg_compress_struct *)num_cols;
        do
        {
          v11 = v8[1];
          v12 = *v8;
          b = v8[2];
          v8 += 3;
          ++v10;
          v10[v15 - 1] = (unsigned int)(*((_DWORD *)start_pass + v12)
                                      + *((_DWORD *)start_pass + v11 + 256)
                                      + *((_DWORD *)start_pass + b + 512)) >> 16;
          *(v10 - 1) = (unsigned int)(*((_DWORD *)start_pass + v12 + 768)
                                    + *((_DWORD *)start_pass + v11 + 1024)
                                    + *((_DWORD *)start_pass + b + 1280)) >> 16;
          v13 = cinfob == (jpeg_compress_struct *)1;
          cinfob = (jpeg_compress_struct *)((char *)cinfob - 1);
          v10[(_DWORD)v17 - 1] = (unsigned int)(*((_DWORD *)start_pass + v12 + 1280)
                                              + *((_DWORD *)start_pass + v11 + 1536)
                                              + *((_DWORD *)start_pass + b + 1792)) >> 16;
        }
        while ( !v13 );
        v7 = output_buf;
      }
      --num_rows;
    }
    while ( num_rows );
  }
}

// FUNC: rgb_gray_convert
void __cdecl rgb_gray_convert(
        jpeg_compress_struct *cinfo,
        unsigned __int8 **input_buf,
        unsigned __int8 ***output_buf,
        unsigned int output_row,
        jpeg_compress_struct *num_rows)
{
  unsigned int image_width; // edx
  void (__cdecl *start_pass)(jpeg_compress_struct *); // esi
  unsigned int v7; // edi
  unsigned __int8 *v8; // eax
  unsigned int v9; // ecx
  unsigned int num_cols; // [esp+4h] [ebp-8h]
  jpeg_compress_struct *cinfoa; // [esp+10h] [ebp+4h]
  unsigned __int8 *num_rowsa; // [esp+20h] [ebp+14h]

  image_width = cinfo->image_width;
  start_pass = cinfo->cconvert[1].start_pass;
  num_cols = image_width;
  if ( (int)&num_rows[-1].entropy + 7 >= 0 )
  {
    v7 = output_row;
    cinfoa = num_rows;
    do
    {
      v8 = *input_buf++;
      num_rowsa = (*output_buf)[v7++];
      v9 = 0;
      if ( image_width )
      {
        do
        {
          num_rowsa[v9++] = (unsigned int)(*((_DWORD *)start_pass + *v8)
                                         + *((_DWORD *)start_pass + v8[1] + 256)
                                         + *((_DWORD *)start_pass + v8[2] + 512)) >> 16;
          image_width = num_cols;
          v8 += 3;
        }
        while ( v9 < num_cols );
      }
      cinfoa = (jpeg_compress_struct *)((char *)cinfoa - 1);
    }
    while ( cinfoa );
  }
}

// FUNC: cmyk_ycck_convert
void __cdecl cmyk_ycck_convert(
        jpeg_compress_struct *cinfo,
        unsigned __int8 **input_buf,
        unsigned __int8 ***output_buf,
        unsigned int output_row,
        int num_rows)
{
  void (__cdecl *start_pass)(jpeg_compress_struct *); // eax
  unsigned __int8 ***v6; // esi
  unsigned int v7; // ecx
  unsigned __int8 *v8; // edx
  _BYTE *v9; // ebp
  int v10; // edi
  int v11; // ecx
  int v12; // esi
  int v13; // edi
  bool v14; // zf
  int v15; // [esp+0h] [ebp-18h]
  unsigned int num_cols; // [esp+4h] [ebp-14h]
  unsigned __int8 *outptr2; // [esp+8h] [ebp-10h]
  unsigned __int8 *outptr2a; // [esp+8h] [ebp-10h]
  int v19; // [esp+Ch] [ebp-Ch]
  int v20; // [esp+10h] [ebp-8h]
  unsigned int v21; // [esp+14h] [ebp-4h]
  jpeg_compress_struct *cinfoa; // [esp+1Ch] [ebp+4h]
  int num_rowsa; // [esp+2Ch] [ebp+14h]
  int num_rowsb; // [esp+2Ch] [ebp+14h]

  start_pass = cinfo->cconvert[1].start_pass;
  num_cols = cinfo->image_width;
  if ( num_rows - 1 >= 0 )
  {
    v6 = output_buf;
    v7 = 4 * output_row;
    v15 = num_rows;
    do
    {
      v8 = *input_buf++;
      v9 = *(unsigned __int8 **)((char *)*v6 + v7);
      v10 = *(int *)((char *)v6[1] + v7);
      outptr2 = *(unsigned __int8 **)((char *)v6[2] + v7);
      num_rowsa = *(int *)((char *)v6[3] + v7);
      v7 += 4;
      cinfoa = (jpeg_compress_struct *)v8;
      v21 = v7;
      if ( num_cols )
      {
        v19 = num_rowsa - (_DWORD)v9;
        v20 = v10 - (_DWORD)v9;
        outptr2a = (unsigned __int8 *)(outptr2 - v9);
        num_rowsb = num_cols;
        while ( 1 )
        {
          v11 = 255 - *v8;
          v12 = 255 - v8[1];
          v13 = 255 - v8[2];
          v9[v19] = v8[3];
          cinfoa = (jpeg_compress_struct *)((char *)cinfoa + 4);
          *v9++ = (unsigned int)(*((_DWORD *)start_pass + v11)
                               + *((_DWORD *)start_pass + v12 + 256)
                               + *((_DWORD *)start_pass + v13 + 512)) >> 16;
          v9[v20 - 1] = (unsigned int)(*((_DWORD *)start_pass + v11 + 768)
                                     + *((_DWORD *)start_pass + v12 + 1024)
                                     + *((_DWORD *)start_pass + v13 + 1280)) >> 16;
          v14 = num_rowsb-- == 1;
          v9[(_DWORD)outptr2a - 1] = (unsigned int)(*((_DWORD *)start_pass + v11 + 1280)
                                                  + *((_DWORD *)start_pass + v12 + 1536)
                                                  + *((_DWORD *)start_pass + v13 + 1792)) >> 16;
          if ( v14 )
            break;
          v8 = (unsigned __int8 *)cinfoa;
        }
        v6 = output_buf;
        v7 = v21;
      }
      --v15;
    }
    while ( v15 );
  }
}

// FUNC: _jinit_color_converter
void __cdecl jinit_color_converter(jpeg_common_struct *cinfo)
{
  jpeg_color_converter *v1; // edi
  J_COLOR_SPACE global_state; // eax
  J_COLOR_SPACE v3; // eax
  J_COLOR_SPACE v4; // eax
  J_COLOR_SPACE v5; // eax

  v1 = (jpeg_color_converter *)cinfo->mem->alloc_small(cinfo, 1, 12);
  cinfo[16].mem = (jpeg_memory_mgr *)v1;
  v1->start_pass = (void (__cdecl *)(jpeg_compress_struct *))SpawnStub;
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
        cinfo->err->msg_code = 7;
        cinfo->err->error_exit(cinfo);
      }
      break;
  }
  global_state = cinfo[2].global_state;
  switch ( global_state )
  {
    case JCS_GRAYSCALE:
      if ( *(_DWORD *)&cinfo[2].is_decompressor != 1 )
      {
        cinfo->err->msg_code = 8;
        cinfo->err->error_exit(cinfo);
      }
      v3 = cinfo[1].global_state;
      switch ( v3 )
      {
        case JCS_GRAYSCALE:
          goto LABEL_17;
        case JCS_RGB:
          v1->start_pass = (void (__cdecl *)(jpeg_compress_struct *))rgb_ycc_start;
          v1->color_convert = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8 **, unsigned __int8 ***, unsigned int, int))rgb_gray_convert;
          break;
        case JCS_YCbCr:
LABEL_17:
          v1->color_convert = (void (__cdecl *)(jpeg_compress_struct *, unsigned __int8 **, unsigned __int8 ***, unsigned int, int))grayscale_convert;
          break;
        default:
          goto LABEL_37;
      }
      return;
    case JCS_RGB:
      if ( *(_DWORD *)&cinfo[2].is_decompressor != 3 )
      {
        cinfo->err->msg_code = 8;
        cinfo->err->error_exit(cinfo);
      }
      if ( cinfo[1].global_state == 2 )
        goto LABEL_41;
      goto LABEL_37;
    case JCS_YCbCr:
      if ( *(_DWORD *)&cinfo[2].is_decompressor != 3 )
      {
        cinfo->err->msg_code = 8;
        cinfo->err->error_exit(cinfo);
      }
      v4 = cinfo[1].global_state;
      if ( v4 == JCS_RGB )
      {
        v1->start_pass = (void (__cdecl *)(jpeg_compress_struct *))rgb_ycc_start;
        v1->color_convert = rgb_ycc_convert;
        return;
      }
      if ( v4 != JCS_YCbCr )
        goto LABEL_37;
      goto LABEL_41;
    case JCS_CMYK:
      if ( *(_DWORD *)&cinfo[2].is_decompressor != 4 )
      {
        cinfo->err->msg_code = 8;
        cinfo->err->error_exit(cinfo);
      }
      if ( cinfo[1].global_state != 4 )
        goto LABEL_37;
      goto LABEL_41;
    case JCS_YCCK:
      if ( *(_DWORD *)&cinfo[2].is_decompressor != 4 )
      {
        cinfo->err->msg_code = 8;
        cinfo->err->error_exit(cinfo);
      }
      v5 = cinfo[1].global_state;
      if ( v5 == JCS_CMYK )
      {
        v1->start_pass = (void (__cdecl *)(jpeg_compress_struct *))rgb_ycc_start;
        v1->color_convert = cmyk_ycck_convert;
      }
      else if ( v5 == JCS_YCCK )
      {
LABEL_41:
        v1->color_convert = null_convert;
      }
      else
      {
LABEL_37:
        cinfo->err->msg_code = 23;
        cinfo->err->error_exit(cinfo);
      }
      return;
    default:
      if ( global_state != cinfo[1].global_state
        || *(_DWORD *)&cinfo[2].is_decompressor != *(_DWORD *)&cinfo[1].is_decompressor )
      {
        cinfo->err->msg_code = 23;
        cinfo->err->error_exit(cinfo);
      }
      goto LABEL_41;
  }
}
