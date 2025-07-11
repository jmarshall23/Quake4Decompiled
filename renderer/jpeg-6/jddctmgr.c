
// FUNC: start_pass
void __cdecl start_pass(jpeg_common_struct *cinfo)
{
  bool v2; // cc
  jpeg_inverse_dct *progress; // ebp
  jpeg_component_info *global_state; // ebx
  int *p_DCT_scaled_size; // ebx
  _DWORD *p_start_pass; // ebp
  int v7; // esi
  int v8; // ecx
  double *v9; // edx
  const int *v10; // eax
  const int *v11; // eax
  int v12; // ecx
  double v13; // st7
  void (__cdecl *method_ptr)(jpeg_decompress_struct *, jpeg_component_info *, __int16 *, unsigned __int8 **, unsigned int); // [esp+Ch] [ebp-10h]
  int ci; // [esp+10h] [ebp-Ch]
  _DWORD *v16; // [esp+14h] [ebp-8h]
  int v17; // [esp+18h] [ebp-4h]
  int v18; // [esp+18h] [ebp-4h]
  int v19; // [esp+18h] [ebp-4h]
  int cinfoa; // [esp+20h] [ebp+4h]

  v2 = *(_DWORD *)&cinfo[1].is_decompressor <= 0;
  progress = (jpeg_inverse_dct *)cinfo[20].progress;
  global_state = (jpeg_component_info *)cinfo[9].global_state;
  cinfoa = 0;
  method_ptr = 0;
  ci = 0;
  if ( !v2 )
  {
    p_DCT_scaled_size = &global_state->DCT_scaled_size;
    p_start_pass = &progress[1].start_pass;
    v16 = p_start_pass;
    do
    {
      if ( *p_DCT_scaled_size == 8 )
      {
        if ( cinfo[3].progress == (jpeg_progress_mgr *)2 )
        {
          method_ptr = jpeg_idct_float;
          cinfoa = 2;
        }
        else
        {
          cinfo->err->msg_code = 45;
          cinfo->err->error_exit(cinfo);
        }
      }
      else
      {
        cinfo->err->msg_code = 6;
        cinfo->err->msg_parm.i[0] = *p_DCT_scaled_size;
        cinfo->err->error_exit(cinfo);
      }
      *(p_start_pass - 10) = method_ptr;
      if ( *((_BYTE *)p_DCT_scaled_size + 12) )
      {
        if ( *p_start_pass != cinfoa )
        {
          v7 = p_DCT_scaled_size[10];
          if ( v7 )
          {
            *p_start_pass = cinfoa;
            if ( cinfoa == 2 )
            {
              v8 = p_DCT_scaled_size[11];
              v9 = (double *)aanscalefactor_0;
              v10 = jpeg_zigzag_order;
              do
              {
                v17 = *(unsigned __int16 *)(v7 + 2 * *v10);
                v11 = v10 + 3;
                v12 = v8 + 12;
                *(float *)(v12 - 12) = (double)v17 * *v9;
                v18 = *(unsigned __int16 *)(v7 + 2 * *(v11 - 2));
                v11 += 4;
                v12 += 16;
                v13 = (double)v18 * *v9++ * 1.387039845;
                *(float *)(v12 - 24) = v13;
                v19 = *(unsigned __int16 *)(v7 + 2 * *(v11 - 5));
                v10 = v11 + 1;
                v8 = v12 + 4;
                *(float *)(v8 - 24) = (double)v19 * *(v9 - 1) * 1.306562965;
                *(float *)(v8 - 20) = (double)*(unsigned __int16 *)(v7 + 2 * *(v10 - 5)) * *(v9 - 1) * 1.175875602;
                *(float *)(v8 - 16) = (double)*(unsigned __int16 *)(v7 + 2 * *(v10 - 4)) * *(v9 - 1);
                *(float *)(v8 - 12) = (double)*(unsigned __int16 *)(v7 + 2 * *(v10 - 3)) * *(v9 - 1) * 0.785694958;
                *(float *)(v8 - 8) = (double)*(unsigned __int16 *)(v7 + 2 * *(v10 - 2)) * *(v9 - 1) * 0.5411961;
                *(float *)(v8 - 4) = (double)*(unsigned __int16 *)(v7 + 2 * *(v10 - 1)) * *(v9 - 1) * 0.275899379;
              }
              while ( (int)v9 < (int)&DOUBLE_0_275899379 );
              p_start_pass = v16;
            }
            else
            {
              cinfo->err->msg_code = 45;
              cinfo->err->error_exit(cinfo);
            }
          }
        }
      }
      ++p_start_pass;
      p_DCT_scaled_size += 21;
      v2 = ++ci < *(_DWORD *)&cinfo[1].is_decompressor;
      v16 = p_start_pass;
    }
    while ( v2 );
  }
}

// FUNC: _jinit_inverse_dct
void __cdecl jinit_inverse_dct(jpeg_common_struct *cinfo)
{
  jpeg_inverse_dct *v2; // eax
  int v3; // ebx
  jpeg_inverse_dct *v4; // ebp
  jpeg_error_mgr *v5; // edi
  jpeg_decompress_struct *cinfoa; // [esp+Ch] [ebp+4h]

  v2 = (jpeg_inverse_dct *)cinfo->mem->alloc_small(cinfo, 1, 84);
  cinfo[20].progress = (jpeg_progress_mgr *)v2;
  v2->start_pass = (void (__cdecl *)(jpeg_decompress_struct *))start_pass;
  v3 = 0;
  if ( *(int *)&cinfo[1].is_decompressor > 0 )
  {
    cinfoa = (jpeg_decompress_struct *)(cinfo[9].global_state + 80);
    v4 = v2 + 1;
    do
    {
      v5 = (jpeg_error_mgr *)cinfo->mem->alloc_small(cinfo, 1, 256);
      cinfoa->err = v5;
      memset(v5, 0, 0x100u);
      v4->start_pass = (void (__cdecl *)(jpeg_decompress_struct *))-1;
      ++v3;
      v4 = (jpeg_inverse_dct *)((char *)v4 + 4);
      cinfoa = (jpeg_decompress_struct *)((char *)cinfoa + 84);
    }
    while ( v3 < *(_DWORD *)&cinfo[1].is_decompressor );
  }
}
