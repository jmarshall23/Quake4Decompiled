
// FUNC: floor0_free_info
void __cdecl floor0_free_info(void *i)
{
  if ( i )
  {
    memset(i, 0, 0x60u);
    _decoder_free(i);
  }
}

// FUNC: floor0_free_look
void __cdecl floor0_free_look(void *i)
{
  void **v1; // eax
  void *v2; // eax

  if ( i )
  {
    v1 = (void **)*((_DWORD *)i + 2);
    if ( v1 )
    {
      v2 = *v1;
      if ( v2 )
        _decoder_free(v2);
      if ( *(_DWORD *)(*((_DWORD *)i + 2) + 4) )
        _decoder_free(*(void **)(*((_DWORD *)i + 2) + 4));
      _decoder_free(*((void **)i + 2));
    }
    *(_DWORD *)i = 0;
    *((_DWORD *)i + 1) = 0;
    *((_DWORD *)i + 2) = 0;
    *((_DWORD *)i + 3) = 0;
    *((_DWORD *)i + 4) = 0;
    *((_DWORD *)i + 5) = 0;
    *((_DWORD *)i + 6) = 0;
    *((_DWORD *)i + 7) = 0;
    _decoder_free(i);
  }
}

// FUNC: floor0_map_lazy_init
void __usercall floor0_map_lazy_init(vorbis_block *vb@<eax>, vorbis_look_floor0 *look@<esi>, int *infoX)
{
  int W; // ebx
  int v4; // edi
  int v5; // ebx
  double v6; // st5
  int v7; // eax
  int j; // [esp+14h] [ebp-14h]
  int n; // [esp+18h] [ebp-10h]
  float na; // [esp+18h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-Ch]
  float scale; // [esp+20h] [ebp-8h]

  W = vb->W;
  v11 = W;
  if ( !look->linearmap[W] )
  {
    n = *((_DWORD *)vb->vd->vi->codec_setup + W) / 2;
    v4 = n;
    scale = (double)look->ln
          / (atan2((double)infoX[1] * 0.5 * ((double)infoX[1] * 0.5) * 0.0000000185, 1.0) * 2.240000009536743
           + atan2((double)infoX[1] * 0.5 * 0.00073999999, 1.0) * 13.10000038146973
           + (double)infoX[1] * 0.5 * 0.000099999997);
    look->linearmap[W] = (int *)_decoder_malloc(4 * n + 4);
    v5 = 0;
    j = 0;
    if ( n > 0 )
    {
      na = (float)n;
      do
      {
        v6 = (double)infoX[1] * 0.5 / na * (double)j;
        v7 = (int)floor(
                    (atan2(v6 * v6 * 0.0000000185, 1.0) * 2.240000009536743
                   + atan2(v6 * 0.00073999999, 1.0) * 13.10000038146973
                   + v6 * 0.000099999997)
                  * scale);
        if ( v7 >= look->ln )
          v7 = look->ln - 1;
        look->linearmap[v11][v5++] = v7;
        j = v5;
      }
      while ( v5 < v4 );
    }
    look->linearmap[v11][v5] = -1;
    look->n[v11] = v4;
  }
}
