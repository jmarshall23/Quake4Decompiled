
// FUNC: _vorbis_comment_init
void __cdecl vorbis_comment_init(vorbis_comment *vc)
{
  vc->user_comments = 0;
  vc->comment_lengths = 0;
  vc->comments = 0;
  vc->vendor = 0;
}

// FUNC: _vorbis_comment_clear
void __cdecl vorbis_comment_clear(vorbis_comment *vc)
{
  int i; // edi

  if ( vc )
  {
    for ( i = 0; i < vc->comments; ++i )
    {
      if ( vc->user_comments[i] )
        _decoder_free(vc->user_comments[i]);
    }
    if ( vc->user_comments )
      _decoder_free(vc->user_comments);
    if ( vc->comment_lengths )
      _decoder_free(vc->comment_lengths);
    if ( vc->vendor )
      _decoder_free(vc->vendor);
  }
  vc->user_comments = 0;
  vc->comment_lengths = 0;
  vc->comments = 0;
  vc->vendor = 0;
}

// FUNC: _vorbis_info_blocksize
int __cdecl vorbis_info_blocksize(vorbis_info *vi, int zo)
{
  _DWORD *codec_setup; // eax

  codec_setup = vi->codec_setup;
  if ( codec_setup )
    return codec_setup[zo];
  else
    return -1;
}

// FUNC: _vorbis_info_init
void __cdecl vorbis_info_init(vorbis_info *vi)
{
  vi->version = 0;
  vi->channels = 0;
  vi->rate = 0;
  vi->bitrate_upper = 0;
  vi->bitrate_nominal = 0;
  vi->bitrate_lower = 0;
  vi->bitrate_window = 0;
  vi->codec_setup = 0;
  vi->codec_setup = _decoder_calloc(1u, 0xE80u);
}

// FUNC: _vorbis_info_clear
void __cdecl vorbis_info_clear(vorbis_info *vi)
{
  vorbis_info *v1; // ebp
  char *codec_setup; // esi
  int v3; // edi
  void **v4; // ebx
  int v5; // ebx
  void **v6; // edi
  int v7; // ebx
  void **v8; // edi
  int v9; // ebx
  void **v10; // edi
  int v11; // edi
  int v12; // ebp
  static_codebook **v13; // ebx
  int v14; // eax
  int v15; // edi
  vorbis_info_psy **v16; // ebx

  v1 = vi;
  codec_setup = (char *)vi->codec_setup;
  if ( codec_setup )
  {
    v3 = 0;
    if ( *((int *)codec_setup + 2) > 0 )
    {
      v4 = (void **)(codec_setup + 32);
      do
      {
        if ( *v4 )
          _decoder_free(*v4);
        ++v3;
        ++v4;
      }
      while ( v3 < *((_DWORD *)codec_setup + 2) );
    }
    v5 = 0;
    if ( *((int *)codec_setup + 3) > 0 )
    {
      v6 = (void **)(codec_setup + 544);
      do
      {
        _mapping_P[(_DWORD)*(v6 - 64)]->free_info(*v6);
        ++v5;
        ++v6;
      }
      while ( v5 < *((_DWORD *)codec_setup + 3) );
    }
    v7 = 0;
    if ( *((int *)codec_setup + 4) > 0 )
    {
      v8 = (void **)(codec_setup + 1056);
      do
      {
        _floor_P[(_DWORD)*(v8 - 64)]->free_info(*v8);
        ++v7;
        ++v8;
      }
      while ( v7 < *((_DWORD *)codec_setup + 4) );
    }
    v9 = 0;
    if ( *((int *)codec_setup + 5) > 0 )
    {
      v10 = (void **)(codec_setup + 1568);
      do
      {
        _residue_P[(_DWORD)*(v10 - 64)]->free_info(*v10);
        ++v9;
        ++v10;
      }
      while ( v9 < *((_DWORD *)codec_setup + 5) );
    }
    v11 = 0;
    if ( *((int *)codec_setup + 6) > 0 )
    {
      v12 = 0;
      v13 = (static_codebook **)(codec_setup + 1824);
      do
      {
        if ( *v13 )
          vorbis_staticbook_destroy(*v13);
        v14 = *((_DWORD *)codec_setup + 712);
        if ( v14 )
          vorbis_book_clear((codebook *)(v12 + v14));
        ++v11;
        ++v13;
        v12 += 44;
      }
      while ( v11 < *((_DWORD *)codec_setup + 6) );
      v1 = vi;
    }
    if ( *((_DWORD *)codec_setup + 712) )
      _decoder_free(*((void **)codec_setup + 712));
    v15 = 0;
    if ( *((int *)codec_setup + 7) > 0 )
    {
      v16 = (vorbis_info_psy **)(codec_setup + 2852);
      do
      {
        _vi_psy_free(*v16);
        ++v15;
        ++v16;
      }
      while ( v15 < *((_DWORD *)codec_setup + 7) );
    }
    _decoder_free(codec_setup);
  }
  v1->version = 0;
  v1->channels = 0;
  v1->rate = 0;
  v1->bitrate_upper = 0;
  v1->bitrate_nominal = 0;
  v1->bitrate_lower = 0;
  v1->bitrate_window = 0;
  v1->codec_setup = 0;
}

// FUNC: _vorbis_synthesis_headerin
int __cdecl vorbis_synthesis_headerin(vorbis_info *vi, vorbis_comment *vc, ogg_packet *op)
{
  int v3; // ebp
  char *v4; // esi
  int v5; // edi
  int v6; // ecx
  const char *v7; // edi
  char *v8; // esi
  bool v9; // zf
  char buffer[6]; // [esp+4h] [ebp-1Ch] BYREF
  oggpack_buffer opb; // [esp+Ch] [ebp-14h] BYREF

  if ( !op )
    return -133;
  oggpack_readinit(&opb, op->packet, op->bytes);
  memset(buffer, 0, sizeof(buffer));
  v3 = oggpack_read(&opb, 8);
  v4 = buffer;
  v5 = 6;
  do
  {
    *v4++ = oggpack_read(&opb, 8);
    --v5;
  }
  while ( v5 );
  v6 = 3;
  v7 = "vorbis";
  v8 = buffer;
  v9 = 1;
  do
  {
    if ( !v6 )
      break;
    v9 = *(_WORD *)v8 == *(_WORD *)v7;
    v8 += 2;
    v7 += 2;
    --v6;
  }
  while ( v9 );
  if ( !v9 )
    return -132;
  if ( v3 == 1 )
  {
    if ( !op->b_o_s || vi->rate )
      return -133;
    return vorbis_unpack_info(vi, &opb);
  }
  else
  {
    if ( v3 != 3 )
    {
      if ( v3 == 5 && vi->rate && vc->vendor )
        return vorbis_unpack_books(&opb, vi);
      return -133;
    }
    if ( !vi->rate )
      return -133;
    return vorbis_unpack_comment(vc, &opb);
  }
}
