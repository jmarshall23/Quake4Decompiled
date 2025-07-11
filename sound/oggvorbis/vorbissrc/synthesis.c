
// FUNC: _vorbis_synthesis
int __cdecl vorbis_synthesis(vorbis_block *vb, codec_setup_info *op)
{
  vorbis_dsp_state *vd; // eax
  vorbis_info *vi; // ebp
  oggpack_buffer *p_opb; // ebx
  int v8; // eax
  int *v9; // edx
  bool v10; // zf
  int v11; // eax
  int W; // edx
  int v13; // edi
  int v14; // eax
  private_state *b; // [esp+10h] [ebp-4h]
  vorbis_block *vba; // [esp+18h] [ebp+4h]
  codec_setup_info *ci; // [esp+1Ch] [ebp+8h]

  vd = vb->vd;
  vi = vd->vi;
  b = (private_state *)vd->backend_state;
  vba = (vorbis_block *)vi->codec_setup;
  p_opb = &vb->opb;
  _vorbis_block_ripcord(vb);
  oggpack_readinit(p_opb, (unsigned __int8 *)op->blocksizes[0], op->blocksizes[1]);
  if ( oggpack_read(p_opb, 1) )
    return -135;
  v8 = oggpack_read(p_opb, b->modebits);
  ci = (codec_setup_info *)v8;
  if ( v8 == -1 )
    return -136;
  vb->mode = v8;
  v9 = (int *)*(&vba->nW + v8);
  v10 = *v9 == 0;
  vb->W = *v9;
  if ( v10 )
  {
    vb->lW = 0;
    vb->nW = 0;
  }
  else
  {
    vb->lW = oggpack_read(p_opb, 1);
    v11 = oggpack_read(p_opb, 1);
    vb->nW = v11;
    if ( v11 == -1 )
      return -136;
  }
  LODWORD(vb->granulepos) = op->floors;
  HIDWORD(vb->granulepos) = op->residues;
  LODWORD(vb->sequence) = op->books;
  W = vb->W;
  HIDWORD(vb->sequence) = op->psys;
  vb->eofflag = op->maps;
  vb->pcmend = *((_DWORD *)&vba->pcm + W);
  v13 = 0;
  for ( vb->pcm = (float **)_vorbis_block_alloc(vb, 4 * vi->channels); v13 < vi->channels; ++v13 )
    vb->pcm[v13] = (float *)_vorbis_block_alloc(vb, 4 * vb->pcmend);
  v14 = *(_DWORD *)(*(&vba->nW + (_DWORD)ci) + 12);
  return _mapping_P[*((_DWORD *)&vba[2].vd + v14)]->inverse(vb, (void *)*(&vba[4].floor_bits + v14));
}

// FUNC: _vorbis_synthesis_trackonly
int __cdecl vorbis_synthesis_trackonly(vorbis_block *vb, codec_setup_info *op)
{
  vorbis_dsp_state *vd; // eax
  _DWORD *backend_state; // ebp
  oggpack_buffer *p_opb; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int maps; // edx
  vorbis_block *vba; // [esp+14h] [ebp+4h]

  vd = vb->vd;
  backend_state = vd->backend_state;
  vba = (vorbis_block *)vd->vi->codec_setup;
  p_opb = &vb->opb;
  _vorbis_block_ripcord(vb);
  oggpack_readinit(p_opb, (unsigned __int8 *)op->blocksizes[0], op->blocksizes[1]);
  if ( oggpack_read(p_opb, 1) )
    return -135;
  v7 = oggpack_read(p_opb, backend_state[11]);
  if ( v7 == -1 )
    return -136;
  vb->mode = v7;
  v8 = **((_DWORD **)&vba->nW + v7);
  vb->W = v8;
  if ( v8 )
  {
    vb->lW = oggpack_read(p_opb, 1);
    v9 = oggpack_read(p_opb, 1);
    vb->nW = v9;
    if ( v9 == -1 )
      return -136;
  }
  else
  {
    vb->lW = 0;
    vb->nW = 0;
  }
  vb->granulepos = *(_QWORD *)&op->floors;
  vb->sequence = *(_QWORD *)&op->books;
  maps = op->maps;
  vb->pcmend = 0;
  vb->pcm = 0;
  vb->eofflag = maps;
  return 0;
}

// FUNC: _vorbis_packet_blocksize
int __cdecl vorbis_packet_blocksize(vorbis_info *vi, ogg_packet *op)
{
  _DWORD *codec_setup; // esi
  int v4; // eax
  int i; // ecx
  int v6; // eax
  oggpack_buffer opb; // [esp+4h] [ebp-14h] BYREF

  codec_setup = vi->codec_setup;
  oggpack_readinit(&opb, op->packet, op->bytes);
  if ( oggpack_read(&opb, 1) )
    return -135;
  v4 = codec_setup[2];
  for ( i = 0; v4 > 1; ++i )
    v4 >>= 1;
  v6 = oggpack_read(&opb, i);
  if ( v6 == -1 )
    return -136;
  else
    return codec_setup[*(_DWORD *)codec_setup[v6 + 8]];
}
