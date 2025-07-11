
// FUNC: _seek_helper
void __usercall seek_helper(OggVorbis_File *vf@<eax>, __int64 offset)
{
  void *datasource; // eax

  datasource = vf->datasource;
  if ( datasource )
  {
    ((void (__cdecl *)(void *, _DWORD, _DWORD, _DWORD))vf->callbacks.seek_func)(datasource, offset, HIDWORD(offset), 0);
    vf->offset = offset;
    ogg_sync_reset(&vf->oy);
  }
}

// FUNC: _prefetch_all_headers
void __usercall prefetch_all_headers(OggVorbis_File *vf@<eax>, __int64 dataoffset)
{
  vorbis_info *v3; // eax
  unsigned int v4; // edx
  vorbis_comment *v5; // eax
  __int64 *v6; // eax
  __int64 *v7; // eax
  int v8; // ebp
  __int64 *offsets; // edx
  int v10; // edi
  int v11; // ebx
  __int64 *v12; // eax
  __int64 *dataoffsets; // ecx
  int v14; // edi
  int v15; // edx
  int v16; // eax
  bool v17; // cc
  int v18; // eax
  int v19; // eax
  __int64 v20; // rax
  int v21; // edx
  __int64 *v22; // ecx
  int v23; // edi
  int v24; // ebx
  __int64 prev_page; // rax
  int v26; // edi
  int v27; // ebx
  __int64 v28; // rax
  __int64 v29; // rax
  __int64 *v30; // edi
  unsigned int v31; // [esp-18h] [ebp-58h]
  unsigned int v32; // [esp-14h] [ebp-54h]
  __int64 accumulated; // [esp+8h] [ebp-38h]
  ogg_page og; // [esp+10h] [ebp-30h] BYREF
  ogg_packet op; // [esp+20h] [ebp-20h] BYREF

  v3 = (vorbis_info *)_decoder_realloc(vf->vi, 32 * vf->links);
  v4 = 16 * vf->links;
  vf->vi = v3;
  v5 = (vorbis_comment *)_decoder_realloc(vf->vc, v4);
  v32 = 8 * vf->links;
  vf->vc = v5;
  v6 = (__int64 *)_decoder_malloc(v32);
  v31 = 16 * vf->links;
  vf->dataoffsets = v6;
  v7 = (__int64 *)_decoder_malloc(v31);
  v8 = 0;
  v17 = vf->links <= 0;
  vf->pcmlengths = v7;
  if ( !v17 )
  {
    do
    {
      if ( v8 )
      {
        offsets = vf->offsets;
        v10 = offsets[v8];
        v11 = HIDWORD(offsets[v8]);
        if ( vf->datasource )
        {
          ((void (__cdecl *)(void *, int, int, _DWORD))vf->callbacks.seek_func)(vf->datasource, v10, v11, 0);
          LODWORD(vf->offset) = v10;
          HIDWORD(vf->offset) = v11;
          ogg_sync_reset(&vf->oy);
        }
        if ( fetch_headers(vf, 0, &vf->vi[v8], &vf->vc[v8], 0) >= 0 )
        {
          dataoffsets = vf->dataoffsets;
          LODWORD(dataoffsets[v8]) = vf->offset;
          HIDWORD(dataoffsets[v8]) = HIDWORD(vf->offset);
        }
        else
        {
          v12 = vf->dataoffsets;
          LODWORD(v12[v8]) = -1;
          HIDWORD(v12[v8]) = -1;
        }
      }
      else
      {
        *vf->dataoffsets = dataoffset;
        if ( vf->datasource )
        {
          ((void (__cdecl *)(void *, _DWORD, _DWORD, _DWORD))vf->callbacks.seek_func)(
            vf->datasource,
            dataoffset,
            HIDWORD(dataoffset),
            0);
          vf->offset = dataoffset;
          ogg_sync_reset(&vf->oy);
        }
      }
      if ( (HIDWORD(vf->dataoffsets[v8]) & vf->dataoffsets[v8]) != -1 )
      {
        accumulated = 0i64;
        v14 = -1;
        ogg_stream_reset_serialno(&vf->os, vf->serialnos[v8]);
        get_next_page(vf, &og, -1i64);
        if ( v15 >= 0 )
        {
          while ( ogg_page_serialno(&og) == vf->serialnos[v8] )
          {
            ogg_stream_pagein(&vf->os, &og);
            v16 = ogg_stream_packetout(&vf->os, &op);
            v17 = v16 <= 0;
            if ( v16 )
            {
              do
              {
                if ( !v17 )
                {
                  v18 = vorbis_packet_blocksize(&vf->vi[v8], &op);
                  if ( v14 != -1 )
                    accumulated += (v18 + v14) >> 2;
                  v14 = v18;
                }
                v19 = ogg_stream_packetout(&vf->os, &op);
                v17 = v19 <= 0;
              }
              while ( v19 );
            }
            v20 = ogg_page_granulepos(&og);
            if ( (HIDWORD(v20) & (unsigned int)v20) != -1 )
            {
              accumulated = ogg_page_granulepos(&og) - accumulated;
              break;
            }
            get_next_page(vf, &og, -1i64);
            if ( v21 < 0 )
              break;
          }
          if ( accumulated < 0 )
            accumulated = 0i64;
        }
        vf->pcmlengths[2 * v8] = accumulated;
      }
      v22 = vf->offsets;
      v23 = v22[v8 + 1];
      v24 = HIDWORD(v22[v8 + 1]);
      if ( vf->datasource )
      {
        ((void (__cdecl *)(void *, int, int, _DWORD))vf->callbacks.seek_func)(vf->datasource, v23, v24, 0);
        LODWORD(vf->offset) = v23;
        HIDWORD(vf->offset) = v24;
        ogg_sync_reset(&vf->oy);
      }
      prev_page = get_prev_page(vf, &og);
      v26 = HIDWORD(prev_page);
      v27 = prev_page;
      if ( prev_page < 0 )
      {
LABEL_31:
        vorbis_info_clear(&vf->vi[v8]);
        vorbis_comment_clear(&vf->vc[v8]);
      }
      else
      {
        while ( 1 )
        {
          v28 = ogg_page_granulepos(&og);
          if ( (HIDWORD(v28) & (unsigned int)v28) != -1 )
            break;
          LODWORD(vf->offset) = v27;
          HIDWORD(vf->offset) = v26;
          v29 = get_prev_page(vf, &og);
          v26 = HIDWORD(v29);
          v27 = v29;
          if ( v29 < 0 )
            goto LABEL_31;
        }
        v30 = &vf->pcmlengths[2 * v8];
        v30[1] = ogg_page_granulepos(&og) - *v30;
      }
      ++v8;
    }
    while ( v8 < vf->links );
  }
}

// FUNC: _decode_clear
void __usercall decode_clear(OggVorbis_File *vf@<esi>)
{
  vorbis_dsp_clear(&vf->vd);
  vorbis_block_clear(&vf->vb);
  vf->ready_state = 2;
}

// FUNC: _ov_clear
int __cdecl ov_clear(OggVorbis_File *vf)
{
  int links; // eax
  int v2; // ebp
  int v3; // ebx
  int v4; // esi

  if ( vf )
  {
    vorbis_block_clear(&vf->vb);
    vorbis_dsp_clear(&vf->vd);
    ogg_stream_clear(&vf->os);
    if ( vf->vi )
    {
      links = vf->links;
      if ( links )
      {
        v2 = 0;
        if ( links > 0 )
        {
          v3 = 0;
          v4 = 0;
          do
          {
            vorbis_info_clear(&vf->vi[v4]);
            vorbis_comment_clear(&vf->vc[v3]);
            ++v2;
            ++v4;
            ++v3;
          }
          while ( v2 < vf->links );
        }
        _decoder_free(vf->vi);
        _decoder_free(vf->vc);
      }
    }
    if ( vf->dataoffsets )
      _decoder_free(vf->dataoffsets);
    if ( vf->pcmlengths )
      _decoder_free(vf->pcmlengths);
    if ( vf->serialnos )
      _decoder_free(vf->serialnos);
    if ( vf->offsets )
      _decoder_free(vf->offsets);
    ogg_sync_clear(&vf->oy);
    if ( vf->datasource )
      vf->callbacks.close_func(vf->datasource);
    memset(vf, 0, sizeof(OggVorbis_File));
  }
  return 0;
}

// FUNC: _ov_pcm_total
int __cdecl ov_pcm_total(OggVorbis_File *vf, int i)
{
  int links; // eax
  unsigned int v3; // ebx
  unsigned int v4; // ebp
  int v5; // esi
  unsigned __int64 v6; // kr00_8
  __int64 v7; // rax

  if ( vf->ready_state >= 2 && vf->seekable && (links = vf->links, i < links) )
  {
    if ( i >= 0 )
    {
      return vf->pcmlengths[2 * i + 1];
    }
    else
    {
      v3 = 0;
      v4 = 0;
      v5 = 0;
      if ( links > 0 )
      {
        do
        {
          v6 = ov_pcm_total(vf, v5) + __PAIR64__(v4, v3);
          v4 = HIDWORD(v6);
          v3 = v6;
          ++v5;
        }
        while ( v5 < vf->links );
      }
      LODWORD(v7) = v3;
    }
  }
  else
  {
    LODWORD(v7) = -131;
  }
  return v7;
}

// FUNC: _ov_raw_seek
int __cdecl ov_raw_seek(OggVorbis_File *vf, __int64 pos)
{
  int v3; // edi
  vorbis_info *v4; // eax
  int v5; // eax
  int v6; // ebx
  int v7; // edx
  int v8; // eax
  int links; // edi
  int v10; // ecx
  int *serialnos; // edx
  int current_link; // edx
  __int64 *pcmlengths; // eax
  int v14; // ecx
  int v15; // edi
  _QWORD *v16; // eax
  unsigned __int64 v17; // kr08_8
  int v18; // eax
  int v19; // edx
  int lastblock; // [esp+4h] [ebp-1A4h]
  int accblock; // [esp+8h] [ebp-1A0h]
  int eosflag; // [esp+Ch] [ebp-19Ch]
  ogg_page og; // [esp+10h] [ebp-198h] BYREF
  ogg_packet op; // [esp+20h] [ebp-188h] BYREF
  ogg_stream_state work_os; // [esp+40h] [ebp-168h] BYREF

  if ( vf->ready_state < 2 )
    return -131;
  if ( !vf->seekable )
    return -138;
  if ( pos < 0 || pos > vf->end )
    return -131;
  vf->pcm_offset = -1i64;
  ogg_stream_reset_serialno(&vf->os, vf->current_serialno);
  vorbis_synthesis_restart(&vf->vd);
  seek_helper(vf, pos);
  v3 = 0;
  lastblock = 0;
  accblock = 0;
  ogg_stream_init(&work_os, vf->current_serialno);
  ogg_stream_reset(&work_os);
  while ( 1 )
  {
    while ( vf->ready_state < 3 || ogg_stream_packetout(&work_os, &op) <= 0 )
    {
LABEL_20:
      if ( v3 )
      {
        v18 = -1;
        HIDWORD(vf->pcm_offset) = -1;
        goto LABEL_42;
      }
      get_next_page(vf, &og, -1i64);
      if ( v7 < 0 )
      {
        v18 = ov_pcm_total(vf, -1);
        HIDWORD(vf->pcm_offset) = v19;
LABEL_42:
        LODWORD(vf->pcm_offset) = v18;
        goto LABEL_43;
      }
      if ( vf->ready_state < 3 )
        goto LABEL_26;
      if ( vf->current_serialno != ogg_page_serialno(&og) )
      {
        decode_clear(vf);
        ogg_stream_clear(&work_os);
      }
      if ( vf->ready_state < 3 )
      {
LABEL_26:
        v8 = ogg_page_serialno(&og);
        links = vf->links;
        v10 = 0;
        vf->current_serialno = v8;
        if ( links > 0 )
        {
          serialnos = vf->serialnos;
          do
          {
            if ( *serialnos == v8 )
              break;
            ++v10;
            ++serialnos;
          }
          while ( v10 < vf->links );
        }
        if ( v10 == links )
        {
          vf->pcm_offset = -1i64;
          ogg_stream_clear(&work_os);
          vorbis_dsp_clear(&vf->vd);
          vorbis_block_clear(&vf->vb);
          vf->ready_state = 2;
          return -137;
        }
        vf->current_link = v10;
        ogg_stream_reset_serialno(&vf->os, v8);
        ogg_stream_reset_serialno(&work_os, vf->current_serialno);
        v3 = lastblock;
        vf->ready_state = 3;
      }
      ogg_stream_pagein(&vf->os, &og);
      ogg_stream_pagein(&work_os, &og);
      eosflag = ogg_page_eos(&og);
    }
    v4 = &vf->vi[vf->current_link];
    if ( !v4->codec_setup )
    {
      ogg_stream_packetout(&vf->os, 0);
      goto LABEL_20;
    }
    v5 = vorbis_packet_blocksize(v4, &op);
    v6 = v5;
    if ( v5 >= 0 )
    {
      if ( eosflag )
      {
        ogg_stream_packetout(&vf->os, 0);
      }
      else if ( v3 )
      {
        accblock += (v5 + v3) >> 2;
      }
    }
    else
    {
      ogg_stream_packetout(&vf->os, 0);
      v6 = 0;
    }
    if ( (HIDWORD(op.granulepos) & op.granulepos) != -1 )
      break;
    lastblock = v6;
    v3 = v6;
  }
  current_link = vf->current_link;
  pcmlengths = vf->pcmlengths;
  v14 = (unsigned __int64)(op.granulepos - pcmlengths[2 * current_link]) >> 32;
  v15 = LODWORD(op.granulepos) - LODWORD(pcmlengths[2 * current_link]);
  if ( v14 < 0 )
  {
    v15 = 0;
    v14 = 0;
  }
  if ( current_link > 0 )
  {
    v16 = pcmlengths + 1;
    do
    {
      v17 = *v16 + __PAIR64__(v14, v15);
      v14 = HIDWORD(v17);
      v15 = v17;
      v16 += 2;
      --current_link;
    }
    while ( current_link );
  }
  vf->pcm_offset = __PAIR64__(v14, v15) - accblock;
LABEL_43:
  ogg_stream_clear(&work_os);
  vf->bittrack = 0.0;
  vf->samptrack = 0.0;
  return 0;
}

// FUNC: _ov_pcm_seek_page
int __cdecl ov_pcm_seek_page(OggVorbis_File *vf, __int64 pos)
{
  int links; // eax
  int v3; // ebx
  int v4; // ebp
  int v5; // edi
  __int64 v6; // rax
  int v7; // eax
  int v8; // ecx
  __int64 *v9; // eax
  signed __int64 v10; // kr08_8
  __int64 *offsets; // edx
  unsigned int v12; // ebx
  unsigned int offset_high; // ebp
  __int64 *v14; // eax
  int v15; // ecx
  unsigned __int8 *v16; // edx
  __int64 *pcmlengths; // eax
  unsigned int v18; // edi
  __int64 *v19; // eax
  unsigned int v20; // ecx
  unsigned __int8 *header; // ebx
  signed int header_len; // edi
  signed __int64 v23; // kr18_8
  __int64 v24; // rax
  int v25; // eax
  void *datasource; // eax
  __int64 v27; // rax
  int v28; // edx
  __int64 v29; // rax
  __int64 prev_page; // rax
  unsigned int v31; // edi
  unsigned int v32; // ebx
  int v33; // edx
  __int64 v34; // rax
  __int64 v35; // kr30_8
  bool v36; // cf
  __int64 v37; // rax
  vorbis_dsp_state *p_vd; // [esp-4h] [ebp-98h]
  __int64 result; // [esp+10h] [ebp-84h]
  __int64 total; // [esp+18h] [ebp-7Ch]
  __int64 end; // [esp+20h] [ebp-74h]
  unsigned __int8 *begin; // [esp+28h] [ebp-6Ch]
  int link; // [esp+30h] [ebp-64h]
  __int64 target; // [esp+34h] [ebp-60h]
  unsigned __int64 best; // [esp+3Ch] [ebp-58h]
  __int64 begintime; // [esp+44h] [ebp-50h]
  __int64 endtime; // [esp+4Ch] [ebp-48h]
  ogg_page v48; // [esp+54h] [ebp-40h] BYREF
  ogg_page og; // [esp+64h] [ebp-30h] BYREF
  ogg_packet op; // [esp+74h] [ebp-20h] BYREF

  if ( vf->ready_state >= 2 && vf->seekable && (links = vf->links, links > -1) )
  {
    v3 = 0;
    v4 = 0;
    v5 = 0;
    if ( links > 0 )
    {
      do
      {
        LODWORD(v6) = ov_pcm_total(vf, v5);
        v4 = (v6 + __PAIR64__(v4, v3)) >> 32;
        v3 += v6;
        ++v5;
      }
      while ( v5 < vf->links );
    }
    total = __PAIR64__(v4, v3);
  }
  else
  {
    v4 = -1;
    total = -131i64;
    v3 = -131;
  }
  if ( vf->ready_state < 2 )
    return -131;
  if ( !vf->seekable )
    return -138;
  if ( pos < 0 || pos > __SPAIR64__(v4, v3) )
    return -131;
  v8 = vf->links - 1;
  link = v8;
  if ( v8 >= 0 )
  {
    v9 = &vf->pcmlengths[2 * v8 + 1];
    do
    {
      v10 = __PAIR64__(v4, v3) - *v9;
      v4 = HIDWORD(v10);
      v3 = v10;
      if ( pos >= v10 )
        break;
      --v8;
      v9 -= 2;
    }
    while ( v8 >= 0 );
    link = v8;
    total = v10;
  }
  offsets = vf->offsets;
  v12 = HIDWORD(offsets[v8 + 1]);
  offset_high = HIDWORD(offsets[v8]);
  v14 = &offsets[v8];
  v15 = 2 * v8;
  LODWORD(end) = *((_DWORD *)v14 + 2);
  v16 = *(unsigned __int8 **)v14;
  pcmlengths = vf->pcmlengths;
  v18 = pcmlengths[v15];
  v19 = &pcmlengths[v15];
  v20 = *((_DWORD *)v19 + 1);
  begin = v16;
  HIDWORD(end) = v12;
  begintime = __PAIR64__(v20, v18);
  endtime = __PAIR64__(v20, v18) + v19[1];
  target = pos + __PAIR64__(v20, v18) - total;
  best = __PAIR64__(offset_high, (unsigned int)v16);
  if ( __SPAIR64__(offset_high, (unsigned int)v16) < __SPAIR64__(v12, end) )
  {
LABEL_19:
    if ( (__int64)(end - __PAIR64__(offset_high, (unsigned int)begin)) >= 8500 )
    {
      v23 = __PAIR64__(offset_high, (unsigned int)begin)
          + (__int64)((target - begintime) * (end - __PAIR64__(offset_high, (unsigned int)begin)))
          / (endtime - begintime)
          - 8500;
      header_len = HIDWORD(v23);
      header = (unsigned __int8 *)v23;
      if ( v23 <= __SPAIR64__(offset_high, (unsigned int)begin) )
      {
        header = begin + 1;
        header_len = __CFADD__(begin, 1) + offset_high;
      }
    }
    else
    {
      header = begin;
      header_len = offset_high;
    }
    if ( vf->datasource )
    {
      ((void (__cdecl *)(void *, unsigned __int8 *, signed int, _DWORD))vf->callbacks.seek_func)(
        vf->datasource,
        header,
        header_len,
        0);
      LODWORD(vf->offset) = header;
      HIDWORD(vf->offset) = header_len;
      ogg_sync_reset(&vf->oy);
    }
    do
    {
      LODWORD(v24) = get_next_page(vf, &og, end - vf->offset);
      result = v24;
      if ( v24 == -128 )
        goto seek_error_0;
      if ( v24 >= 0 )
      {
        LODWORD(v27) = ogg_page_granulepos(&og);
        if ( (HIDWORD(v27) & (unsigned int)v27) != -1 )
        {
          if ( v27 >= target )
          {
            v48.header = begin + 1;
            v48.header_len = __CFADD__(begin, 1) + offset_high;
            if ( __SPAIR64__(header_len, (unsigned int)header) <= (__int64)(__PAIR64__(offset_high, (unsigned int)begin)
                                                                          + 1) )
              break;
            if ( end != vf->offset )
            {
              end = result;
              endtime = v27;
LABEL_48:
              if ( __SPAIR64__(offset_high, (unsigned int)begin) < end )
                goto LABEL_19;
              break;
            }
            header_len = (__PAIR64__(header_len, (unsigned int)header) - 8500) >> 32;
            header -= 8500;
            end = result;
            if ( __SPAIR64__(header_len, (unsigned int)header) <= __SPAIR64__(offset_high, (unsigned int)begin) )
            {
              header = v48.header;
              header_len = v48.header_len;
            }
            datasource = vf->datasource;
            if ( vf->datasource )
            {
LABEL_44:
              ((void (__cdecl *)(void *, unsigned __int8 *, signed int, _DWORD))vf->callbacks.seek_func)(
                datasource,
                header,
                header_len,
                0);
              HIDWORD(vf->offset) = header_len;
              LODWORD(vf->offset) = header;
              ogg_sync_reset(&vf->oy);
            }
          }
          else
          {
            header = (unsigned __int8 *)vf->offset;
            offset_high = HIDWORD(vf->offset);
            best = result;
            begintime = v27;
            begin = header;
            if ( target - v27 > 44100 )
              goto LABEL_48;
            header_len = HIDWORD(vf->offset);
          }
        }
      }
      else
      {
        v25 = __CFADD__(begin, 1) + offset_high;
        if ( header_len < v25 || header_len <= v25 && header <= begin + 1 )
          break;
        if ( !(header_len | (unsigned int)header) )
          goto seek_error_0;
        header_len = (__PAIR64__(header_len, (unsigned int)header) - 8500) >> 32;
        header -= 8500;
        if ( __SPAIR64__(header_len, (unsigned int)header) <= __SPAIR64__(offset_high, (unsigned int)begin) )
        {
          header = begin + 1;
          header_len = __CFADD__(begin, 1) + offset_high;
        }
        datasource = vf->datasource;
        if ( vf->datasource )
          goto LABEL_44;
      }
    }
    while ( __SPAIR64__(offset_high, (unsigned int)begin) < end );
  }
  if ( vf->datasource )
  {
    ((void (__cdecl *)(void *, _DWORD, _DWORD, _DWORD))vf->callbacks.seek_func)(vf->datasource, best, HIDWORD(best), 0);
    vf->offset = best;
    ogg_sync_reset(&vf->oy);
  }
  vf->pcm_offset = -1i64;
  get_next_page(vf, &v48, -1i64);
  if ( v28 < 0 )
    return -2;
  p_vd = &vf->vd;
  if ( link == vf->current_link )
  {
    vorbis_synthesis_restart(p_vd);
  }
  else
  {
    vorbis_dsp_clear(p_vd);
    vorbis_block_clear(&vf->vb);
    vf->ready_state = 2;
    vf->current_link = link;
    vf->current_serialno = ogg_page_serialno(&v48);
    vf->ready_state = 3;
  }
  ogg_stream_reset_serialno(&vf->os, vf->current_serialno);
  ogg_stream_pagein(&vf->os, &v48);
  v29 = ogg_stream_packetpeek(&vf->os, &op);
  if ( (_DWORD)v29 )
  {
    while ( 1 )
    {
      if ( v29 < 0 )
      {
        LODWORD(result) = -136;
        goto seek_error_0;
      }
      if ( (HIDWORD(op.granulepos) & op.granulepos) != -1 )
        break;
      ogg_stream_packetout(&vf->os, 0);
      v29 = ogg_stream_packetpeek(&vf->os, &op);
      if ( !(_DWORD)v29 )
        goto LABEL_60;
    }
    v35 = op.granulepos - vf->pcmlengths[2 * vf->current_link];
    vf->pcm_offset = v35;
    if ( v35 < 0 )
      vf->pcm_offset = 0i64;
    v36 = __CFADD__((_DWORD)total, vf->pcm_offset);
    LODWORD(vf->pcm_offset) += total;
    HIDWORD(vf->pcm_offset) += HIDWORD(total) + v36;
    if ( vf->pcm_offset <= pos )
    {
      LODWORD(v37) = ov_pcm_total(vf, -1);
      if ( pos <= v37 )
      {
        vf->bittrack = 0.0;
        v7 = 0;
        vf->samptrack = 0.0;
        return v7;
      }
    }
    LODWORD(result) = -129;
    goto seek_error_0;
  }
LABEL_60:
  if ( vf->datasource )
  {
    ((void (__cdecl *)(void *, _DWORD, _DWORD, _DWORD))vf->callbacks.seek_func)(vf->datasource, best, HIDWORD(best), 0);
    vf->offset = best;
    ogg_sync_reset(&vf->oy);
  }
  prev_page = get_prev_page(vf, &v48);
  v31 = HIDWORD(prev_page);
  v32 = prev_page;
  LODWORD(result) = prev_page;
  if ( prev_page < 0 )
  {
seek_error_0:
    vf->pcm_offset = -1i64;
    vorbis_dsp_clear(&vf->vd);
    vorbis_block_clear(&vf->vb);
    v7 = result;
    vf->ready_state = 2;
    return v7;
  }
  while ( 1 )
  {
    ogg_page_granulepos(&v48);
    if ( v33 > -1 || !ogg_page_continued(&v48) )
      return ov_raw_seek(vf, __SPAIR64__(v31, v32));
    LODWORD(vf->offset) = v32;
    HIDWORD(vf->offset) = v31;
    v34 = get_prev_page(vf, &v48);
    v31 = HIDWORD(v34);
    v32 = v34;
    if ( v34 < 0 )
    {
      LODWORD(result) = v34;
      goto seek_error_0;
    }
  }
}

// FUNC: _ov_pcm_seek
int __cdecl ov_pcm_seek(OggVorbis_File *vf, __int64 pos)
{
  int v2; // ebx
  int result; // eax
  ogg_stream_state *p_os; // edi
  int v5; // eax
  int v6; // eax
  int v7; // ebp
  int current_link; // edi
  __int64 *pcmlengths; // edx
  int v10; // eax
  int v11; // ecx
  _DWORD *v12; // eax
  bool v13; // cf
  int v14; // edx
  int v15; // eax
  int links; // edi
  int v17; // ecx
  int *serialnos; // edx
  unsigned int pcm_offset_high; // eax
  __int64 v20; // kr08_8
  int v21; // ebx
  int v22; // eax
  int v23; // ebx
  int v24; // ebp
  int v25; // edi
  __int64 v26; // rax
  ogg_page og; // [esp+8h] [ebp-30h] BYREF
  ogg_packet op; // [esp+18h] [ebp-20h] BYREF

  v2 = 0;
  result = ov_pcm_seek_page(vf, pos);
  if ( result >= 0 )
  {
    result = make_decode_ready(vf);
    if ( !result )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( 1 )
          {
            p_os = &vf->os;
            v5 = ogg_stream_packetpeek(&vf->os, &op);
            if ( v5 > 0 )
              break;
            if ( v5 < 0 && v5 != -3 )
              goto LABEL_30;
            get_next_page(vf, &og, -1i64);
            if ( v14 < 0 )
              goto LABEL_30;
            if ( vf->current_serialno != ogg_page_serialno(&og) )
            {
              vorbis_dsp_clear(&vf->vd);
              vorbis_block_clear(&vf->vb);
              vf->ready_state = 2;
            }
            if ( vf->ready_state < 3 )
            {
              v15 = ogg_page_serialno(&og);
              links = vf->links;
              v17 = 0;
              vf->current_serialno = v15;
              if ( links > 0 )
              {
                serialnos = vf->serialnos;
                do
                {
                  if ( *serialnos == v15 )
                    break;
                  ++v17;
                  ++serialnos;
                }
                while ( v17 < vf->links );
              }
              if ( v17 == links )
                return -137;
              p_os = &vf->os;
              vf->current_link = v17;
              ogg_stream_reset_serialno(&vf->os, v15);
              vf->ready_state = 3;
              result = make_decode_ready(vf);
              if ( result )
                return result;
              v2 = 0;
            }
            ogg_stream_pagein(p_os, &og);
          }
          v6 = vorbis_packet_blocksize(&vf->vi[vf->current_link], &op);
          v7 = v6;
          if ( v6 >= 0 )
            break;
          ogg_stream_packetout(&vf->os, 0);
        }
        if ( v2 )
          vf->pcm_offset += (v2 + v6) >> 2;
        if ( vf->pcm_offset + ((v6 + vorbis_info_blocksize(vf->vi, 1)) >> 2) >= pos )
          break;
        ogg_stream_packetout(&vf->os, 0);
        vorbis_synthesis_trackonly(&vf->vb, (codec_setup_info *)&op);
        vorbis_synthesis_blockin(&vf->vd, &vf->vb);
        if ( op.granulepos >= 0 )
        {
          current_link = vf->current_link;
          pcmlengths = vf->pcmlengths;
          v10 = (unsigned __int64)(op.granulepos - pcmlengths[2 * current_link]) >> 32;
          LODWORD(vf->pcm_offset) = LODWORD(op.granulepos) - LODWORD(pcmlengths[2 * current_link]);
          v11 = 0;
          HIDWORD(vf->pcm_offset) = v10;
          if ( v10 < 0 )
            vf->pcm_offset = 0i64;
          if ( current_link > 0 )
          {
            v12 = pcmlengths + 1;
            do
            {
              v13 = __CFADD__(*v12, vf->pcm_offset);
              LODWORD(vf->pcm_offset) += *v12;
              HIDWORD(vf->pcm_offset) += v12[1] + v13;
              ++v11;
              v12 += 4;
            }
            while ( v11 < vf->current_link );
          }
        }
        v2 = v7;
      }
LABEL_30:
      pcm_offset_high = HIDWORD(vf->pcm_offset);
      vf->bittrack = 0.0;
      vf->samptrack = 0.0;
      if ( __SPAIR64__(pcm_offset_high, vf->pcm_offset) < pos )
      {
        do
        {
          v20 = pos - vf->pcm_offset;
          v21 = vorbis_synthesis_pcmout(&vf->vd, 0);
          if ( v21 > v20 )
            v21 = v20;
          vorbis_synthesis_read(&vf->vd, v21);
          vf->pcm_offset += v21;
          if ( v21 < v20 && fetch_and_process_packet(vf, 0, 1, 1) <= 0 )
          {
            if ( vf->ready_state >= 2 && vf->seekable && (v22 = vf->links, v22 > -1) )
            {
              v23 = 0;
              v24 = 0;
              v25 = 0;
              if ( v22 > 0 )
              {
                do
                {
                  LODWORD(v26) = ov_pcm_total(vf, v25);
                  v24 = (v26 + __PAIR64__(v24, v23)) >> 32;
                  v23 += v26;
                  ++v25;
                }
                while ( v25 < vf->links );
              }
            }
            else
            {
              v23 = -131;
              v24 = -1;
            }
            LODWORD(vf->pcm_offset) = v23;
            HIDWORD(vf->pcm_offset) = v24;
          }
        }
        while ( vf->pcm_offset < pos );
      }
      return 0;
    }
  }
  return result;
}

// FUNC: _ov_info
vorbis_info *__cdecl ov_info(OggVorbis_File *vf, int link)
{
  int current_link; // eax

  if ( !vf->seekable )
    return vf->vi;
  current_link = link;
  if ( link < 0 )
  {
    if ( vf->ready_state >= 3 )
    {
      current_link = vf->current_link;
      return &vf->vi[current_link];
    }
    return vf->vi;
  }
  if ( link < vf->links )
    return &vf->vi[current_link];
  return 0;
}

// FUNC: _ov_read
int __cdecl ov_read(OggVorbis_File *vf, char *buffer, int length, int bigendianp, int word, int sgned, int *bitstream)
{
  OggVorbis_File *v7; // esi
  int result; // eax
  int v9; // ebx
  vorbis_info *vi; // eax
  int v11; // ecx
  int v12; // edi
  char *v13; // esi
  int v14; // eax
  int v15; // ecx
  int v16; // edi
  int v17; // edi
  char *v18; // edx
  float *v19; // esi
  int v20; // eax
  int v21; // edi
  int v22; // ecx
  int v23; // ecx
  char *v24; // edx
  int v25; // eax
  int v26; // esi
  int v27; // ecx
  char *v28; // ecx
  int j; // esi
  int v30; // eax
  __int16 v31; // ax
  _BYTE *v32; // ecx
  bool v33; // cf
  float **pcm; // [esp+10h] [ebp-28h] BYREF
  int channels; // [esp+14h] [ebp-24h]
  int i; // [esp+18h] [ebp-20h]
  char *v37; // [esp+1Ch] [ebp-1Ch]
  float *src; // [esp+20h] [ebp-18h]
  double v39; // [esp+24h] [ebp-14h]
  int bytespersample; // [esp+2Ch] [ebp-Ch]
  double v41; // [esp+30h] [ebp-8h]

  v7 = vf;
  if ( vf->ready_state < 2 )
    return -131;
  while ( 1 )
  {
    if ( vf->ready_state == 4 )
    {
      result = vorbis_synthesis_pcmout(&vf->vd, &pcm);
      v9 = result;
      i = result;
      if ( result )
        break;
    }
    result = fetch_and_process_packet(vf, 0, 1, 1);
    if ( result == -2 )
      return 0;
    if ( result <= 0 )
      return result;
  }
  if ( result <= 0 )
    return result;
  if ( vf->seekable && vf->ready_state >= 3 )
    vi = &vf->vi[vf->current_link];
  else
    vi = vf->vi;
  channels = vi->channels;
  v11 = channels;
  bytespersample = word * channels;
  if ( v9 > length / (word * channels) )
  {
    i = length / (word * channels);
    v9 = i;
  }
  if ( v9 <= 0 )
    return -131;
  if ( word == 1 )
  {
    v12 = 0;
    v13 = buffer;
    do
    {
      v14 = 0;
      if ( v11 > 0 )
      {
        do
        {
          v39 = pcm[v14][v12] * 128.0;
          v37 = (char *)(int)v39;
          v15 = (int)v39;
          if ( (int)v39 <= 127 )
          {
            if ( v15 < -128 )
              LOBYTE(v15) = 0x80;
          }
          else
          {
            LOBYTE(v15) = 127;
          }
          *v13 = v15 + (sgned != 0 ? 0 : 0x80);
          ++v14;
          ++v13;
        }
        while ( v14 < channels );
        v9 = i;
        v11 = channels;
      }
      ++v12;
    }
    while ( v12 < v9 );
LABEL_63:
    v7 = vf;
    goto LABEL_64;
  }
  v16 = sgned != 0 ? 0 : 0x8000;
  if ( bigendianp )
  {
    i = 0;
    v28 = buffer;
    do
    {
      for ( j = 0; j < channels; v28 = v32 + 1 )
      {
        v41 = pcm[j][i] * 32768.0;
        LODWORD(v39) = (int)v41;
        v30 = (int)v41;
        if ( (int)v41 <= 0x7FFF )
        {
          if ( v30 < -32768 )
            LOWORD(v30) = 0x8000;
        }
        else
        {
          LOWORD(v30) = 0x7FFF;
        }
        v31 = v16 + v30;
        *v28 = HIBYTE(v31);
        v32 = v28 + 1;
        *v32 = v31;
        ++j;
      }
      ++i;
    }
    while ( i < v9 );
    goto LABEL_63;
  }
  if ( !sgned )
  {
    v23 = 0;
    i = 0;
    if ( channels > 0 )
    {
      v24 = buffer;
      v37 = buffer;
      do
      {
        src = pcm[v23];
        v25 = 0;
        v26 = 2 * channels;
        do
        {
          v41 = src[v25] * 32768.0;
          LODWORD(v39) = (int)v41;
          v27 = (int)v41;
          if ( (int)v41 <= 0x7FFF )
          {
            if ( v27 < -32768 )
              LOWORD(v27) = 0x8000;
          }
          else
          {
            LOWORD(v27) = 0x7FFF;
          }
          *(_WORD *)v24 = v16 + v27;
          ++v25;
          v24 += v26;
        }
        while ( v25 < v9 );
        v7 = vf;
        v23 = i + 1;
        v24 = v37 + 2;
        i = v23;
        v37 += 2;
      }
      while ( v23 < channels );
    }
    goto LABEL_64;
  }
  v17 = 0;
  i = 0;
  if ( channels > 0 )
  {
    v18 = buffer;
    v37 = buffer;
    do
    {
      v19 = pcm[v17];
      v20 = 0;
      v21 = 2 * v11;
      do
      {
        v39 = v19[v20] * 32768.0;
        src = (float *)(int)v39;
        v22 = (int)v39;
        if ( (int)v39 <= 0x7FFF )
        {
          if ( v22 < -32768 )
            LOWORD(v22) = 0x8000;
        }
        else
        {
          LOWORD(v22) = 0x7FFF;
        }
        *(_WORD *)v18 = v22;
        ++v20;
        v18 += v21;
      }
      while ( v20 < v9 );
      v11 = channels;
      v17 = i + 1;
      v18 = v37 + 2;
      i = v17;
      v37 += 2;
    }
    while ( v17 < channels );
    goto LABEL_63;
  }
LABEL_64:
  vorbis_synthesis_read(&v7->vd, v9);
  v33 = __CFADD__(v9, v7->pcm_offset);
  LODWORD(v7->pcm_offset) += v9;
  HIDWORD(v7->pcm_offset) += (v9 >> 31) + v33;
  if ( bitstream )
    *bitstream = v7->current_link;
  return v9 * bytespersample;
}

// FUNC: _ov_read_float
int __cdecl ov_read_float(OggVorbis_File *vf, float ***pcm_channels, int length, int *bitstream)
{
  OggVorbis_File *v4; // esi
  int result; // eax
  int v6; // edi
  bool v7; // cf
  int *v8; // eax

  v4 = vf;
  if ( vf->ready_state < 2 )
    return -131;
  while ( 1 )
  {
    if ( v4->ready_state == 4 )
    {
      v6 = vorbis_synthesis_pcmout(&v4->vd, (float ***)&vf);
      if ( v6 )
        break;
    }
    result = fetch_and_process_packet(v4, 0, 1, 1);
    if ( result == -2 )
      return 0;
    if ( result <= 0 )
      return result;
  }
  if ( pcm_channels )
    *pcm_channels = (float **)vf;
  if ( v6 > length )
    v6 = length;
  vorbis_synthesis_read(&v4->vd, v6);
  v7 = __CFADD__(v6, v4->pcm_offset);
  LODWORD(v4->pcm_offset) += v6;
  v8 = bitstream;
  HIDWORD(v4->pcm_offset) += (v6 >> 31) + v7;
  if ( v8 )
    *v8 = v4->current_link;
  return v6;
}

// FUNC: _ov_open_callbacks
int __cdecl ov_open_callbacks(void *f, OggVorbis_File *vf, char *initial, int ibytes, ov_callbacks callbacks)
{
  int result; // eax

  result = ov_open1(vf, f, initial, ibytes, callbacks);
  if ( !result )
    return ov_open2(vf);
  return result;
}
