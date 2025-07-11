
// FUNC: _vorbis_block_init
int __cdecl vorbis_block_init(vorbis_dsp_state *v, vorbis_block *vb)
{
  _DWORD *v2; // edi

  memset(vb, 0, sizeof(vorbis_block));
  vb->vd = v;
  vb->localalloc = 0;
  vb->localstore = 0;
  if ( v->analysisp )
  {
    v2 = _decoder_calloc(1u, 0x48u);
    vb->internal = v2;
    oggpack_writeinit(&vb->opb);
    v2[1] = -971228160;
  }
  return 0;
}

// FUNC: __vorbis_block_alloc
char *__cdecl _vorbis_block_alloc(vorbis_block *vb, int bytes)
{
  unsigned int v2; // edi
  alloc_chain *v3; // eax
  alloc_chain *reap; // edx
  int localtop; // ecx
  char *result; // eax

  v2 = (bytes + 7) & 0xFFFFFFF8;
  if ( (signed int)(v2 + vb->localtop) > vb->localalloc )
  {
    if ( vb->localstore )
    {
      v3 = (alloc_chain *)_decoder_malloc(8u);
      reap = vb->reap;
      vb->totaluse += vb->localtop;
      v3->next = reap;
      v3->ptr = vb->localstore;
      vb->reap = v3;
    }
    vb->localalloc = v2;
    vb->localstore = _decoder_malloc(v2);
    vb->localtop = 0;
  }
  localtop = vb->localtop;
  result = (char *)vb->localstore + localtop;
  vb->localtop = v2 + localtop;
  return result;
}

// FUNC: __vorbis_block_ripcord
void __cdecl _vorbis_block_ripcord(vorbis_block *vb)
{
  alloc_chain *reap; // esi
  alloc_chain *next; // ebx
  int totaluse; // eax

  reap = vb->reap;
  if ( reap )
  {
    do
    {
      next = reap->next;
      _decoder_free(reap->ptr);
      reap->ptr = 0;
      reap->next = 0;
      _decoder_free(reap);
      reap = next;
    }
    while ( next );
  }
  totaluse = vb->totaluse;
  if ( totaluse )
  {
    vb->localstore = _decoder_realloc(vb->localstore, totaluse + vb->localalloc);
    vb->localalloc += vb->totaluse;
    vb->totaluse = 0;
  }
  vb->localtop = 0;
  vb->reap = 0;
}

// FUNC: _vorbis_block_clear
int __cdecl vorbis_block_clear(vorbis_block *vb)
{
  vorbis_dsp_state *vd; // eax
  int result; // eax

  vd = vb->vd;
  if ( vd && vd->analysisp )
    oggpack_writeclear(&vb->opb);
  _vorbis_block_ripcord(vb);
  if ( vb->localstore )
    _decoder_free(vb->localstore);
  if ( vb->internal )
    _decoder_free(vb->internal);
  result = 0;
  memset(vb, 0, sizeof(vorbis_block));
  return result;
}

// FUNC: _vorbis_dsp_clear
void __cdecl vorbis_dsp_clear(vorbis_dsp_state *v)
{
  vorbis_dsp_state *v1; // edi
  vorbis_info *v2; // ecx
  _DWORD *codec_setup; // ebp
  char *backend_state; // esi
  mdct_lookup **v5; // eax
  mdct_lookup **v6; // eax
  int v7; // ebx
  _DWORD *v8; // edi
  int v9; // ebx
  _DWORD *v10; // edi
  int v11; // ebx
  int v12; // edi
  int i; // ebx
  vorbis_info *vi; // [esp+4h] [ebp-4h]

  v1 = v;
  if ( v )
  {
    v2 = v->vi;
    vi = v2;
    if ( v2 )
      codec_setup = v2->codec_setup;
    else
      codec_setup = 0;
    backend_state = (char *)v->backend_state;
    if ( backend_state )
    {
      if ( *(_DWORD *)backend_state )
      {
        _ve_envelope_clear(*(envelope_lookup **)backend_state);
        _decoder_free(*(void **)backend_state);
      }
      v5 = (mdct_lookup **)*((_DWORD *)backend_state + 3);
      if ( v5 )
      {
        mdct_clear(*v5);
        _decoder_free(**((void ***)backend_state + 3));
        _decoder_free(*((void **)backend_state + 3));
      }
      v6 = (mdct_lookup **)*((_DWORD *)backend_state + 4);
      if ( v6 )
      {
        mdct_clear(*v6);
        _decoder_free(**((void ***)backend_state + 4));
        _decoder_free(*((void **)backend_state + 4));
      }
      if ( *((_DWORD *)backend_state + 12) )
      {
        v7 = 0;
        if ( (int)codec_setup[4] > 0 )
        {
          v8 = codec_setup + 200;
          do
            _floor_P[*v8++]->free_look(*(void **)(*((_DWORD *)backend_state + 12) + 4 * v7++));
          while ( v7 < codec_setup[4] );
        }
        _decoder_free(*((void **)backend_state + 12));
        v1 = v;
      }
      if ( *((_DWORD *)backend_state + 13) )
      {
        v9 = 0;
        if ( (int)codec_setup[5] > 0 )
        {
          v10 = codec_setup + 328;
          do
            _residue_P[*v10++]->free_look(*(void **)(*((_DWORD *)backend_state + 13) + 4 * v9++));
          while ( v9 < codec_setup[5] );
        }
        _decoder_free(*((void **)backend_state + 13));
        v1 = v;
      }
      if ( *((_DWORD *)backend_state + 14) )
      {
        v11 = 0;
        if ( (int)codec_setup[7] > 0 )
        {
          v12 = 0;
          do
          {
            _vp_psy_clear((vorbis_look_psy *)(v12 + *((_DWORD *)backend_state + 14)));
            ++v11;
            v12 += 48;
          }
          while ( v11 < codec_setup[7] );
        }
        _decoder_free(*((void **)backend_state + 14));
        v1 = v;
      }
      if ( *((_DWORD *)backend_state + 15) )
        _vp_global_free(*((vorbis_look_psy_global **)backend_state + 15));
      vorbis_bitrate_clear((bitrate_manager_state *)(backend_state + 80));
      drft_clear((drft_lookup *)(backend_state + 20));
      drft_clear((drft_lookup *)(backend_state + 32));
      v2 = vi;
    }
    if ( v1->pcm )
    {
      for ( i = 0; i < v2->channels; ++i )
      {
        if ( v1->pcm[i] )
        {
          _decoder_free(v1->pcm[i]);
          v2 = vi;
        }
      }
      _decoder_free(v1->pcm);
      if ( v1->pcmret )
        _decoder_free(v1->pcmret);
    }
    if ( backend_state )
    {
      if ( *((_DWORD *)backend_state + 16) )
        _decoder_free(*((void **)backend_state + 16));
      if ( *((_DWORD *)backend_state + 17) )
        _decoder_free(*((void **)backend_state + 17));
      if ( *((_DWORD *)backend_state + 18) )
        _decoder_free(*((void **)backend_state + 18));
      _decoder_free(backend_state);
    }
    memset(v1, 0, sizeof(vorbis_dsp_state));
  }
}

// FUNC: _vorbis_synthesis_restart
int __cdecl vorbis_synthesis_restart(vorbis_dsp_state *v)
{
  vorbis_info *vi; // ecx
  _DWORD *backend_state; // edi
  _DWORD *codec_setup; // edx
  int v5; // esi
  int v6; // edx

  vi = v->vi;
  backend_state = v->backend_state;
  if ( !backend_state )
    return -1;
  if ( !vi )
    return -1;
  codec_setup = vi->codec_setup;
  if ( !codec_setup )
    return -1;
  v5 = codec_setup[926];
  v6 = (int)codec_setup[1] >> (v5 + 1);
  v->eofflag = 0;
  v->centerW = v6;
  v->pcm_returned = -1;
  LODWORD(v->granulepos) = -1;
  v->pcm_current = v6 >> v5;
  HIDWORD(v->granulepos) = -1;
  v->sequence = -1i64;
  backend_state[46] = -1;
  backend_state[47] = -1;
  return 0;
}

// FUNC: _vorbis_synthesis_init
int __cdecl vorbis_synthesis_init(vorbis_dsp_state *v, vorbis_info *vi)
{
  if ( vds_shared_init(v, vi, 0) )
    return 1;
  vorbis_synthesis_restart(v);
  return 0;
}

// FUNC: _vorbis_synthesis_blockin
int __cdecl vorbis_synthesis_blockin(vorbis_dsp_state *v, vorbis_block *vb)
{
  private_state *backend_state; // ebx
  int pcm_returned; // eax
  unsigned int sequence_high; // ecx
  unsigned int sequence; // eax
  int v8; // ebp
  int v9; // ebx
  __int64 glue_bits; // rax
  bool v11; // cf
  int v12; // edi
  float *v13; // eax
  int v14; // edx
  float *v15; // edi
  float *v16; // ecx
  float *v17; // ebx
  int v18; // ebp
  double v19; // st7
  float *v20; // eax
  double v21; // st6
  int v22; // ebx
  int v23; // eax
  float *v24; // ecx
  char *v25; // ebx
  double v26; // st7
  double v27; // st6
  double v28; // st6
  float *v29; // ebx
  int v30; // ecx
  float *v31; // edx
  float *v32; // edi
  float *v33; // eax
  char *k; // ebx
  double v35; // st7
  float *v36; // ebp
  double v37; // st6
  double v38; // st7
  float *v39; // eax
  float *v40; // edx
  float *v41; // ebx
  int v42; // edx
  float *v43; // ecx
  double v44; // st6
  int v45; // ecx
  int v46; // eax
  int v47; // edx
  float *v48; // edi
  float *v49; // ebx
  float *v50; // ecx
  int m; // eax
  double v52; // st7
  float *v53; // ebp
  double v54; // st6
  double v55; // st7
  int v56; // eax
  int v57; // ebx
  float *v58; // ecx
  float *v59; // eax
  double v60; // st6
  int v61; // ecx
  float *v62; // eax
  int v63; // ecx
  float *v64; // eax
  float *v65; // ecx
  int v66; // edx
  float *v67; // edi
  float *v68; // ebx
  float *v69; // ecx
  char *ii; // eax
  double v71; // st7
  float *v72; // ebp
  double v73; // st6
  double v74; // st7
  int v75; // ebx
  float *v76; // eax
  float *v77; // ecx
  int v78; // ebx
  double v79; // st7
  double v80; // st6
  double v81; // st6
  float *v82; // ecx
  float *v83; // ebx
  int v84; // edx
  _DWORD *v85; // edx
  unsigned int v86; // ebx
  _DWORD *v87; // eax
  float *v88; // eax
  int v89; // ebx
  int v90; // ecx
  bool v91; // zf
  int v92; // edx
  __int64 v93; // rax
  int granulepos; // eax
  int granulepos_high; // ecx
  __int64 sample_count; // rax
  unsigned int v97; // ecx
  unsigned int v98; // edi
  int pcm_current; // eax
  __int64 v100; // rax
  unsigned int v101; // eax
  int v102; // ecx
  unsigned int v103; // edi
  int v104; // ebx
  int v105; // eax
  int v106; // [esp-Ch] [ebp-54h]
  int hs; // [esp+8h] [ebp-40h]
  int j; // [esp+Ch] [ebp-3Ch]
  private_state *b; // [esp+10h] [ebp-38h]
  int v110; // [esp+14h] [ebp-34h]
  int v111; // [esp+14h] [ebp-34h]
  float *v112; // [esp+14h] [ebp-34h]
  float *v113; // [esp+14h] [ebp-34h]
  int v114; // [esp+14h] [ebp-34h]
  int prevCenter; // [esp+18h] [ebp-30h]
  float *p; // [esp+1Ch] [ebp-2Ch]
  float *pa; // [esp+1Ch] [ebp-2Ch]
  float *pb; // [esp+1Ch] [ebp-2Ch]
  float *pc; // [esp+1Ch] [ebp-2Ch]
  float *pd; // [esp+1Ch] [ebp-2Ch]
  float *pcm; // [esp+20h] [ebp-28h]
  float *pcma; // [esp+20h] [ebp-28h]
  float *pcmb; // [esp+20h] [ebp-28h]
  float *pcmc; // [esp+20h] [ebp-28h]
  float *pcmd; // [esp+20h] [ebp-28h]
  int n0; // [esp+24h] [ebp-24h]
  int n; // [esp+28h] [ebp-20h]
  codec_setup_info *ci; // [esp+2Ch] [ebp-1Ch]
  float *w; // [esp+30h] [ebp-18h]
  float *wa; // [esp+30h] [ebp-18h]
  float *wb; // [esp+30h] [ebp-18h]
  float *wc; // [esp+30h] [ebp-18h]
  int thisCenter; // [esp+34h] [ebp-14h]
  int i; // [esp+38h] [ebp-10h]
  float *ia; // [esp+38h] [ebp-10h]
  float *ib; // [esp+38h] [ebp-10h]
  int ic; // [esp+38h] [ebp-10h]
  float *v138; // [esp+3Ch] [ebp-Ch]
  int v139; // [esp+40h] [ebp-8h]
  int v140; // [esp+40h] [ebp-8h]
  float *v141; // [esp+40h] [ebp-8h]
  float *v142; // [esp+40h] [ebp-8h]
  int v143; // [esp+40h] [ebp-8h]
  vorbis_info *vi; // [esp+44h] [ebp-4h]
  int va; // [esp+4Ch] [ebp+4h]

  backend_state = (private_state *)v->backend_state;
  vi = v->vi;
  ci = (codec_setup_info *)vi->codec_setup;
  b = backend_state;
  hs = ci->halfrate_flag;
  if ( !vb )
    return -131;
  pcm_returned = v->pcm_returned;
  if ( v->pcm_current > pcm_returned && pcm_returned != -1 )
    return -131;
  v->lW = v->W;
  sequence_high = HIDWORD(v->sequence);
  v->W = vb->W;
  sequence = v->sequence;
  v->nW = -1;
  if ( (sequence_high & sequence) == -1 || __PAIR64__(sequence_high, sequence) + 1 != vb->sequence )
  {
    v->granulepos = -1i64;
    LODWORD(backend_state->sample_count) = -1;
    HIDWORD(backend_state->sample_count) = -1;
  }
  v->sequence = vb->sequence;
  if ( vb->pcm )
  {
    v8 = ci->blocksizes[0] >> (hs + 1);
    v9 = ci->blocksizes[1] >> (hs + 1);
    n = ci->blocksizes[v->W] >> (hs + 1);
    glue_bits = vb->glue_bits;
    v11 = __CFADD__((_DWORD)glue_bits, v->glue_bits);
    LODWORD(v->glue_bits) += glue_bits;
    n0 = v8;
    va = v9;
    HIDWORD(v->glue_bits) += HIDWORD(glue_bits) + v11;
    v->time_bits += vb->time_bits;
    v->floor_bits += vb->floor_bits;
    v->res_bits += vb->res_bits;
    v12 = 0;
    if ( v->centerW )
    {
      thisCenter = v9;
      prevCenter = 0;
    }
    else
    {
      thisCenter = 0;
      prevCenter = v9;
    }
    j = 0;
    if ( vi->channels > 0 )
    {
      do
      {
        if ( v->lW )
        {
          if ( v->W )
          {
            v13 = _vorbis_window_get(b->window[1] - hs);
            pcm = &v->pcm[v12][prevCenter];
            v14 = 0;
            w = v13;
            p = vb->pcm[v12];
            if ( va >= 4 )
            {
              v15 = v13 + 2;
              v16 = pcm + 1;
              v17 = &v13[va - 2];
              v18 = (char *)p - (char *)v13;
              v110 = (char *)v13 - (char *)pcm;
              do
              {
                v19 = p[v14] * *(v15 - 2);
                v20 = (float *)((char *)v16 + v110);
                v14 += 4;
                v21 = v17[1] * *(v16 - 1);
                v16 += 4;
                v15 += 4;
                v17 -= 4;
                *(v16 - 5) = v19 + v21;
                *(v16 - 4) = *(float *)((char *)v20 + v18) * *v20 + v17[4] * *(v16 - 4);
                *(v16 - 3) = *(float *)((char *)v15 + v18 - 16) * *(v15 - 4) + v17[3] * *(v16 - 3);
                *(v16 - 2) = p[v14 - 1] * *(v15 - 3) + v17[2] * *(v16 - 2);
              }
              while ( v14 < va - 3 );
              v12 = j;
              v8 = n0;
              v13 = w;
            }
            if ( v14 < va )
            {
              wa = &v13[va - v14 - 1];
              v22 = (char *)p - (char *)v13;
              v23 = (char *)v13 - (char *)pcm;
              v139 = v22;
              v24 = &pcm[v14];
              v111 = v23;
              v25 = (char *)(va - v14);
              while ( 1 )
              {
                v26 = *(float *)((char *)v24 + v23 + v139) * *(float *)((char *)v24 + v23);
                v27 = *v24++;
                --v25;
                v28 = v27 * *wa--;
                *(v24 - 1) = v26 + v28;
                if ( !v25 )
                  break;
                v23 = v111;
              }
            }
          }
          else
          {
            v29 = _vorbis_window_get(b->window[0] - hs);
            v112 = &v->pcm[v12][prevCenter + va / 2 - v8 / 2];
            pa = vb->pcm[v12];
            v30 = 0;
            i = (int)v29;
            if ( v8 >= 4 )
            {
              v31 = v29 + 2;
              v32 = &v29[v8 - 2];
              v33 = v112 + 1;
              pcma = (float *)((char *)v29 - (char *)v112);
              for ( k = (char *)((char *)pa - (char *)v29); ; k = (char *)pa - i )
              {
                v35 = pa[v30] * *(v31 - 2);
                v36 = (float *)((int)pcma + (_DWORD)v33);
                v30 += 4;
                v37 = v32[1] * *(v33 - 1);
                v33 += 4;
                v31 += 4;
                v32 -= 4;
                *(v33 - 5) = v35 + v37;
                v38 = *(float *)((char *)v36 + (_DWORD)k) * *v36;
                v8 = n0;
                *(v33 - 4) = v38 + v32[4] * *(v33 - 4);
                *(v33 - 3) = *(float *)((char *)v31 + (_DWORD)k - 16) * *(v31 - 4) + v32[3] * *(v33 - 3);
                *(v33 - 2) = pa[v30 - 1] * *(v31 - 3) + v32[2] * *(v33 - 2);
                if ( v30 >= n0 - 3 )
                  break;
              }
              v12 = j;
              v29 = (float *)i;
            }
            if ( v30 < v8 )
            {
              v39 = &v112[v30];
              ia = &v29[v8 - v30 - 1];
              v40 = (float *)((char *)pa - (char *)v29);
              v41 = (float *)((char *)v29 - (char *)v112);
              wb = v40;
              pcmb = v41;
              v42 = v8 - v30;
              while ( 1 )
              {
                v43 = (float *)((int)v41 + (_DWORD)v39++);
                --v42;
                v44 = *(v39 - 1) * *ia--;
                *(v39 - 1) = *(float *)((char *)wb + (_DWORD)v43) * *v43 + v44;
                if ( !v42 )
                  break;
                v41 = pcmb;
              }
            }
          }
        }
        else
        {
          v106 = b->window[0] - hs;
          if ( v->W )
          {
            pcmc = _vorbis_window_get(v106);
            v113 = &v->pcm[v12][prevCenter];
            v45 = va / 2;
            v46 = v8 / 2;
            pb = &vb->pcm[v12][va / 2 - v8 / 2];
            v47 = 0;
            v140 = v8 / 2;
            if ( v8 >= 4 )
            {
              v48 = pcmc + 2;
              v49 = &pcmc[v8 - 2];
              v50 = v113 + 1;
              for ( m = (char *)pb - (char *)pcmc; ; m = (char *)pb - (char *)pcmc )
              {
                v52 = pb[v47] * *(v48 - 2);
                v53 = (float *)((char *)v50 + (char *)pcmc - (char *)v113);
                v47 += 4;
                v54 = v49[1] * *(v50 - 1);
                v50 += 4;
                v48 += 4;
                v49 -= 4;
                *(v50 - 5) = v52 + v54;
                v55 = *(float *)((char *)v53 + m) * *v53;
                v8 = n0;
                *(v50 - 4) = v55 + v49[4] * *(v50 - 4);
                *(v50 - 3) = *(float *)((char *)v48 + m - 16) * *(v48 - 4) + v49[3] * *(v50 - 3);
                *(v50 - 2) = pb[v47 - 1] * *(v48 - 3) + v49[2] * *(v50 - 2);
                if ( v47 >= n0 - 3 )
                  break;
              }
              v46 = v140;
              v45 = va / 2;
              v12 = j;
            }
            if ( v47 < v8 )
            {
              ib = &pcmc[v8 - v47 - 1];
              v56 = (char *)pcmc - (char *)v113;
              v57 = v8 - v47;
              v58 = &v113[v47];
              v47 = v8;
              while ( 1 )
              {
                v59 = (float *)((char *)v58++ + v56);
                --v57;
                v60 = *(v58 - 1) * *ib--;
                *(v58 - 1) = *(float *)((char *)v59 + (char *)pb - (char *)pcmc) * *v59 + v60;
                if ( !v57 )
                  break;
                v56 = (char *)pcmc - (char *)v113;
              }
              v45 = va / 2;
              v12 = j;
              v46 = v140;
            }
            v61 = v46 + v45;
            if ( v47 < v61 )
            {
              v62 = &v113[v47];
              v63 = v61 - v47;
              do
              {
                *v62 = *(float *)((char *)v62 + (char *)pb - (char *)v113);
                ++v62;
                --v63;
              }
              while ( v63 );
            }
          }
          else
          {
            v64 = _vorbis_window_get(v106);
            v65 = &v->pcm[v12][prevCenter];
            pcmd = vb->pcm[v12];
            v66 = 0;
            v141 = v64;
            wc = v65;
            if ( v8 >= 4 )
            {
              v67 = v64 + 2;
              v68 = &v64[v8 - 2];
              v69 = v65 + 1;
              pc = (float *)((char *)v64 - (char *)wc);
              for ( ii = (char *)((char *)pcmd - (char *)v64); ; ii = (char *)((char *)pcmd - (char *)v141) )
              {
                v71 = pcmd[v66] * *(v67 - 2);
                v72 = (float *)((int)pc + (_DWORD)v69);
                v66 += 4;
                v73 = v68[1] * *(v69 - 1);
                v69 += 4;
                v67 += 4;
                v68 -= 4;
                *(v69 - 5) = v71 + v73;
                v74 = *(float *)((char *)v72 + (_DWORD)ii) * *v72;
                v8 = n0;
                *(v69 - 4) = v74 + v68[4] * *(v69 - 4);
                *(v69 - 3) = *(float *)((char *)v67 + (_DWORD)ii - 16) * *(v67 - 4) + v68[3] * *(v69 - 3);
                *(v69 - 2) = pcmd[v66 - 1] * *(v67 - 3) + v68[2] * *(v69 - 2);
                if ( v66 >= n0 - 3 )
                  break;
              }
              v64 = v141;
              v12 = j;
              v65 = wc;
            }
            if ( v66 < v8 )
            {
              v142 = &v64[v8 - v66 - 1];
              v75 = (char *)pcmd - (char *)v64;
              v76 = (float *)((char *)v64 - (char *)wc);
              v114 = v75;
              v77 = &v65[v66];
              pd = v76;
              v78 = v8 - v66;
              while ( 1 )
              {
                v79 = *(float *)((char *)v77 + (_DWORD)v76 + v114) * *(float *)((char *)v77 + (_DWORD)v76);
                v80 = *v77++;
                --v78;
                v81 = v80 * *v142--;
                *(v77 - 1) = v79 + v81;
                if ( !v78 )
                  break;
                v76 = pd;
              }
            }
          }
        }
        v82 = &v->pcm[v12][thisCenter];
        v83 = &vb->pcm[v12][n];
        v84 = 0;
        v138 = v83;
        if ( n >= 4 )
        {
          v85 = v83 + 3;
          v143 = (char *)v83 - (char *)v82;
          v86 = ((unsigned int)(n - 4) >> 2) + 1;
          v87 = v82 + 1;
          ic = 4 * v86;
          do
          {
            *(v87 - 1) = *(v85 - 3);
            *v87 = *(_DWORD *)((char *)v87 + v143);
            v87[1] = *(v85 - 1);
            v87[2] = *v85;
            v87 += 4;
            v85 += 4;
            --v86;
          }
          while ( v86 );
          v83 = v138;
          v12 = j;
          v84 = ic;
        }
        if ( v84 < n )
        {
          v88 = &v82[v84];
          v89 = (char *)v83 - (char *)v82;
          v90 = n - v84;
          do
          {
            *v88 = *(float *)((char *)v88 + v89);
            ++v88;
            --v90;
          }
          while ( v90 );
        }
        j = ++v12;
      }
      while ( v12 < vi->channels );
    }
    v91 = v->pcm_returned == -1;
    v->centerW = v->centerW == 0 ? va : 0;
    if ( v91 )
    {
      v->pcm_returned = thisCenter;
      v->pcm_current = thisCenter;
    }
    else
    {
      v92 = v->W;
      v->pcm_returned = prevCenter;
      v->pcm_current = prevCenter + ((ci->blocksizes[v->lW] / 4 + ci->blocksizes[v92] / 4) >> hs);
    }
  }
  if ( (HIDWORD(b->sample_count) & b->sample_count) == -1 )
  {
    LODWORD(b->sample_count) = 0;
    HIDWORD(b->sample_count) = 0;
  }
  else
  {
    v93 = ci->blocksizes[v->W];
    b->sample_count += (((BYTE4(v93) & 3) + (int)v93) >> 2) + ci->blocksizes[v->lW] / 4;
  }
  if ( (HIDWORD(v->granulepos) & v->granulepos) == -1 )
  {
    granulepos = vb->granulepos;
    granulepos_high = HIDWORD(vb->granulepos);
    if ( (granulepos_high & granulepos) != -1 )
    {
      HIDWORD(v->granulepos) = granulepos_high;
      LODWORD(v->granulepos) = granulepos;
      sample_count = b->sample_count;
      v97 = HIDWORD(v->granulepos);
      v98 = v->granulepos;
      if ( sample_count > __SPAIR64__(v97, v98) )
      {
        if ( vb->eofflag )
        {
          v->pcm_current -= (__int64)(sample_count - __PAIR64__(v97, v98)) >> hs;
        }
        else
        {
          v->pcm_returned += (__int64)(sample_count - __PAIR64__(v97, v98)) >> hs;
          pcm_current = v->pcm_current;
          if ( v->pcm_returned > pcm_current )
            v->pcm_returned = pcm_current;
        }
      }
    }
  }
  else
  {
    v100 = ci->blocksizes[v->W];
    v->granulepos += (((BYTE4(v100) & 3) + (int)v100) >> 2) + ci->blocksizes[v->lW] / 4;
    v101 = vb->granulepos;
    v102 = HIDWORD(vb->granulepos);
    if ( (v102 & v101) != -1 )
    {
      v103 = v->granulepos;
      v104 = HIDWORD(v->granulepos);
      if ( v103 != v101 || v104 != v102 )
      {
        if ( v104 >= v102 && (v104 > v102 || v103 > v101) )
        {
          v105 = LODWORD(v->granulepos) - LODWORD(vb->granulepos);
          if ( v105 )
          {
            if ( vb->eofflag )
              v->pcm_current -= v105 >> hs;
          }
        }
        v->granulepos = vb->granulepos;
      }
    }
  }
  if ( vb->eofflag )
    v->eofflag = 1;
  return 0;
}

// FUNC: _vorbis_synthesis_pcmout
int __cdecl vorbis_synthesis_pcmout(vorbis_dsp_state *v, float ***pcm)
{
  int pcm_returned; // eax
  vorbis_info *vi; // edx
  int i; // eax

  pcm_returned = v->pcm_returned;
  vi = v->vi;
  if ( pcm_returned <= -1 || pcm_returned >= v->pcm_current )
    return 0;
  if ( pcm )
  {
    for ( i = 0; i < vi->channels; ++i )
      v->pcmret[i] = &v->pcm[i][v->pcm_returned];
    *pcm = v->pcmret;
  }
  return v->pcm_current - v->pcm_returned;
}

// FUNC: _vorbis_synthesis_read
int __cdecl vorbis_synthesis_read(vorbis_dsp_state *v, int n)
{
  if ( n && n + v->pcm_returned > v->pcm_current )
    return -131;
  v->pcm_returned += n;
  return 0;
}
