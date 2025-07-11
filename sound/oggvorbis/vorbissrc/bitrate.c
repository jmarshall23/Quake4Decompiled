
// FUNC: _vorbis_bitrate_clear
void __cdecl vorbis_bitrate_clear(bitrate_manager_state *bm)
{
  int queue_size; // eax
  int v2; // esi
  int v3; // ebx

  if ( bm )
  {
    if ( bm->queue_binned )
      _decoder_free(bm->queue_binned);
    if ( bm->queue_actual )
      _decoder_free(bm->queue_actual);
    if ( bm->avg_binacc )
      _decoder_free(bm->avg_binacc);
    if ( bm->minmax_binstack )
      _decoder_free(bm->minmax_binstack);
    if ( bm->minmax_posstack )
      _decoder_free(bm->minmax_posstack);
    if ( bm->minmax_limitstack )
      _decoder_free(bm->minmax_limitstack);
    if ( bm->packetbuffers )
    {
      queue_size = bm->queue_size;
      if ( queue_size )
      {
        v2 = 0;
        if ( queue_size > 0 )
        {
          v3 = 0;
          do
          {
            oggpack_writeclear(&bm->packetbuffers[v3]);
            ++v2;
            ++v3;
          }
          while ( v2 < bm->queue_size );
        }
      }
      else
      {
        oggpack_writeclear(bm->packetbuffers);
      }
      _decoder_free(bm->packetbuffers);
    }
    if ( bm->packets )
      _decoder_free(bm->packets);
    memset(bm, 0, sizeof(bitrate_manager_state));
  }
}

// FUNC: _vorbis_bitrate_managed
BOOL __cdecl vorbis_bitrate_managed(vorbis_block *vb)
{
  return *((_DWORD *)vb->vd->backend_state + 20) != 0;
}
