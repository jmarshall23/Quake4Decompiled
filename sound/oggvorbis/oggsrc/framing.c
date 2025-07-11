
// FUNC: _ogg_page_continued
int __cdecl ogg_page_continued(ogg_page *og)
{
  return og->header[5] & 1;
}

// FUNC: _ogg_page_eos
int __cdecl ogg_page_eos(ogg_page *og)
{
  return og->header[5] & 4;
}

// FUNC: _ogg_page_granulepos
int __cdecl ogg_page_granulepos(ogg_page *og)
{
  return og->header[6] | ((og->header[7] | ((og->header[8] | ((og->header[9] | ((og->header[10] | ((og->header[11] | (*((unsigned __int16 *)og->header + 6) << 8)) << 8)) << 8)) << 8)) << 8)) << 8);
}

// FUNC: _ogg_page_serialno
int __cdecl ogg_page_serialno(ogg_page *og)
{
  return ((og->header[15] | (*((unsigned __int16 *)og->header + 8) << 8)) << 8) | og->header[14];
}

// FUNC: _ogg_stream_init
int __cdecl ogg_stream_init(ogg_stream_state *os, int serialno)
{
  if ( !os )
    return -1;
  memset(os, 0, sizeof(ogg_stream_state));
  os->body_storage = 0x2000;
  os->body_data = (unsigned __int8 *)_decoder_malloc(0x2000u);
  os->lacing_storage = 1024;
  os->lacing_vals = (int *)_decoder_malloc(0x1000u);
  os->granule_vals = (__int64 *)_decoder_malloc(8 * os->lacing_storage);
  os->serialno = serialno;
  return 0;
}

// FUNC: _ogg_stream_clear
int __cdecl ogg_stream_clear(ogg_stream_state *os)
{
  if ( os )
  {
    if ( os->body_data )
      _decoder_free(os->body_data);
    if ( os->lacing_vals )
      _decoder_free(os->lacing_vals);
    if ( os->granule_vals )
      _decoder_free(os->granule_vals);
    memset(os, 0, sizeof(ogg_stream_state));
  }
  return 0;
}

// FUNC: _os_lacing_expand
void __usercall os_lacing_expand(ogg_stream_state *os@<esi>, int needed@<ecx>)
{
  int lacing_storage; // eax
  int v3; // eax
  int *lacing_vals; // ecx
  int *v5; // eax
  unsigned int v6; // edx

  lacing_storage = os->lacing_storage;
  if ( lacing_storage <= needed + os->lacing_fill )
  {
    v3 = lacing_storage + needed + 32;
    lacing_vals = os->lacing_vals;
    os->lacing_storage = v3;
    v5 = (int *)_decoder_realloc(lacing_vals, 4 * v3);
    v6 = 8 * os->lacing_storage;
    os->lacing_vals = v5;
    os->granule_vals = (__int64 *)_decoder_realloc(os->granule_vals, v6);
  }
}

// FUNC: _ogg_page_checksum_set
void __cdecl ogg_page_checksum_set(ogg_page *og)
{
  int v1; // edx
  int header_len; // esi
  unsigned int v3; // eax
  int body_len; // esi

  v1 = 0;
  if ( og )
  {
    og->header[22] = 0;
    og->header[23] = 0;
    og->header[24] = 0;
    og->header[25] = 0;
    header_len = og->header_len;
    v3 = 0;
    if ( header_len > 0 )
    {
      do
        v3 = crc_lookup[HIBYTE(v3) ^ og->header[v1++]] ^ (v3 << 8);
      while ( v1 < header_len );
      v1 = 0;
    }
    body_len = og->body_len;
    if ( body_len > 0 )
    {
      do
        v3 = crc_lookup[HIBYTE(v3) ^ og->body[v1++]] ^ (v3 << 8);
      while ( v1 < body_len );
    }
    *(_DWORD *)(og->header + 22) = v3;
  }
}

// FUNC: _ogg_sync_init
int __cdecl ogg_sync_init(ogg_sync_state *oy)
{
  if ( oy )
  {
    oy->data = 0;
    oy->storage = 0;
    oy->fill = 0;
    oy->returned = 0;
    oy->unsynced = 0;
    oy->headerbytes = 0;
    oy->bodybytes = 0;
  }
  return 0;
}

// FUNC: _ogg_sync_clear
int __cdecl ogg_sync_clear(ogg_sync_state *oy)
{
  if ( oy )
  {
    if ( oy->data )
      _decoder_free(oy->data);
    oy->data = 0;
    oy->storage = 0;
    oy->fill = 0;
    oy->returned = 0;
    oy->unsynced = 0;
    oy->headerbytes = 0;
    oy->bodybytes = 0;
  }
  return 0;
}

// FUNC: _ogg_sync_buffer
char *__cdecl ogg_sync_buffer(ogg_sync_state *oy, int size)
{
  int returned; // eax
  int fill; // eax
  int v4; // edi
  unsigned __int8 *v5; // eax
  unsigned __int8 *v7; // eax

  returned = oy->returned;
  if ( returned )
  {
    oy->fill -= returned;
    if ( oy->fill > 0 )
      memmove(oy->data, &oy->data[returned], oy->fill);
    oy->returned = 0;
  }
  fill = oy->fill;
  if ( size > oy->storage - fill )
  {
    v4 = fill + size + 4096;
    if ( oy->data )
    {
      v5 = (unsigned __int8 *)_decoder_realloc(oy->data, v4);
      oy->storage = v4;
      oy->data = v5;
      return (char *)&v5[oy->fill];
    }
    v7 = (unsigned __int8 *)_decoder_malloc(fill + size + 4096);
    oy->storage = v4;
    oy->data = v7;
  }
  return (char *)&oy->data[oy->fill];
}

// FUNC: _ogg_sync_wrote
int __cdecl ogg_sync_wrote(ogg_sync_state *oy, int bytes)
{
  int v2; // ecx

  v2 = bytes + oy->fill;
  if ( v2 > oy->storage )
    return -1;
  oy->fill = v2;
  return 0;
}

// FUNC: _ogg_sync_pageseek
int __cdecl ogg_sync_pageseek(ogg_sync_state *oy, ogg_page *og)
{
  int returned; // eax
  unsigned __int8 *v3; // edi
  int v4; // ebx
  int v5; // ebp
  int result; // eax
  int v7; // ebp
  int bodybytes; // ecx
  unsigned __int8 *v9; // ecx
  unsigned __int8 *v10; // eax
  ogg_page log; // [esp+10h] [ebp-10h] BYREF

  returned = oy->returned;
  v3 = &oy->data[returned];
  v4 = oy->fill - returned;
  if ( !oy->headerbytes )
  {
    if ( v4 < 27 )
      return 0;
    if ( *(_DWORD *)v3 != *(_DWORD *)"OggS" )
      goto sync_fail;
    v5 = v3[26] + 27;
    result = 0;
    if ( v4 < v5 )
      return result;
    if ( v3[26] )
    {
      do
        oy->bodybytes += v3[result++ + 27];
      while ( result < v3[26] );
    }
    oy->headerbytes = v5;
  }
  if ( oy->bodybytes + oy->headerbytes > v4 )
    return 0;
  v7 = *(_DWORD *)(v3 + 22);
  *(_DWORD *)(v3 + 22) = 0;
  bodybytes = oy->bodybytes;
  log.header_len = oy->headerbytes;
  log.header = v3;
  log.body = &v3[log.header_len];
  log.body_len = bodybytes;
  ogg_page_checksum_set(&log);
  if ( v7 != *(_DWORD *)(v3 + 22) )
  {
    *(_DWORD *)(v3 + 22) = v7;
sync_fail:
    oy->headerbytes = 0;
    oy->bodybytes = 0;
    v9 = (unsigned __int8 *)memchr(v3 + 1, 79, v4 - 1);
    if ( !v9 )
      v9 = &oy->data[oy->fill];
    oy->returned = v9 - oy->data;
    return v3 - v9;
  }
  v10 = &oy->data[oy->returned];
  if ( og )
  {
    og->header = v10;
    og->header_len = oy->headerbytes;
    og->body = &v10[oy->headerbytes];
    og->body_len = oy->bodybytes;
  }
  result = oy->bodybytes + oy->headerbytes;
  oy->unsynced = 0;
  oy->returned += result;
  oy->headerbytes = 0;
  oy->bodybytes = 0;
  return result;
}

// FUNC: _ogg_stream_pagein
int __cdecl ogg_stream_pagein(ogg_stream_state *os, ogg_page *og)
{
  unsigned __int8 *header; // ebp
  unsigned __int8 v4; // al
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int lacing_returned; // esi
  int body_returned; // eax
  bool v11; // zf
  int v12; // ecx
  int v14; // edx
  int v15; // eax
  int *v16; // ecx
  int v17; // eax
  int body_storage; // eax
  int v19; // edx
  int v20; // eax
  int lacing_fill; // ecx
  __int64 *granule_vals; // esi
  __int64 *v23; // eax
  int v24; // eax
  unsigned __int8 *body_data; // [esp-8h] [ebp-44h]
  int v26; // [esp-4h] [ebp-40h]
  int segments; // [esp+10h] [ebp-2Ch]
  unsigned __int8 *body; // [esp+14h] [ebp-28h]
  int segptr; // [esp+18h] [ebp-24h]
  int bos; // [esp+1Ch] [ebp-20h]
  int pageno; // [esp+20h] [ebp-1Ch]
  int serialno; // [esp+24h] [ebp-18h]
  int version; // [esp+28h] [ebp-14h]
  int continued; // [esp+2Ch] [ebp-10h]
  int eos; // [esp+30h] [ebp-Ch]
  int granulepos; // [esp+34h] [ebp-8h]
  int granulepos_4; // [esp+38h] [ebp-4h]
  int osa; // [esp+40h] [ebp+4h]
  int oga; // [esp+44h] [ebp+8h]

  header = og->header;
  body = og->body;
  version = og->header[4];
  v4 = og->header[5];
  oga = og->body_len;
  continued = v4 & 1;
  v5 = 0;
  segptr = 0;
  bos = v4 & 2;
  eos = v4 & 4;
  v6 = ogg_page_granulepos(og);
  granulepos_4 = v7;
  granulepos = v6;
  lacing_returned = os->lacing_returned;
  serialno = header[14] | ((header[15] | (*((unsigned __int16 *)header + 8) << 8)) << 8);
  body_returned = os->body_returned;
  pageno = header[18] | ((header[19] | (*((unsigned __int16 *)header + 10) << 8)) << 8);
  segments = header[26];
  if ( body_returned )
  {
    v11 = os->body_fill == body_returned;
    os->body_fill -= body_returned;
    if ( !v11 )
      memmove(os->body_data, &os->body_data[body_returned], os->body_fill);
    os->body_returned = 0;
  }
  if ( lacing_returned )
  {
    v12 = os->lacing_fill - lacing_returned;
    if ( v12 )
    {
      memmove((unsigned __int8 *)os->lacing_vals, (unsigned __int8 *)&os->lacing_vals[lacing_returned], 4 * v12);
      memmove(
        (unsigned __int8 *)os->granule_vals,
        (unsigned __int8 *)&os->granule_vals[lacing_returned],
        8 * (os->lacing_fill - lacing_returned));
    }
    os->lacing_fill -= lacing_returned;
    os->lacing_packet -= lacing_returned;
    os->lacing_returned = 0;
  }
  if ( serialno != os->serialno || version > 0 )
    return -1;
  os_lacing_expand(os, segments + 1);
  v14 = os->pageno;
  if ( pageno != v14 )
  {
    osa = os->lacing_packet;
    v15 = osa;
    if ( osa < os->lacing_fill )
    {
      v16 = &os->lacing_vals[osa];
      do
      {
        os->body_fill -= (unsigned __int8)*v16;
        ++v15;
        ++v16;
      }
      while ( v15 < os->lacing_fill );
      v15 = osa;
    }
    os->lacing_fill = v15;
    if ( v14 != -1 )
    {
      os->lacing_vals[v15] = 1024;
      ++os->lacing_fill;
      ++os->lacing_packet;
    }
    if ( continued )
    {
      bos = 0;
      if ( segments > 0 )
      {
        do
        {
          v17 = header[v5 + 27];
          body += v17;
          oga -= v17;
          ++v5;
        }
        while ( v17 >= 255 && v5 < segments );
        segptr = v5;
      }
    }
  }
  if ( oga )
  {
    body_storage = os->body_storage;
    if ( body_storage <= oga + os->body_fill )
    {
      v26 = body_storage + oga + 1024;
      body_data = os->body_data;
      os->body_storage = v26;
      os->body_data = (unsigned __int8 *)_decoder_realloc(body_data, v26);
    }
    qmemcpy(&os->body_data[os->body_fill], body, oga);
    os->body_fill += oga;
    v5 = segptr;
  }
  v19 = -1;
  if ( v5 < segments )
  {
    do
    {
      v20 = header[v5 + 27];
      os->lacing_vals[os->lacing_fill] = v20;
      lacing_fill = os->lacing_fill;
      granule_vals = os->granule_vals;
      LODWORD(granule_vals[lacing_fill]) = -1;
      HIDWORD(granule_vals[lacing_fill]) = -1;
      if ( bos )
      {
        BYTE1(os->lacing_vals[os->lacing_fill]) |= 1u;
        bos = 0;
      }
      if ( v20 < 255 )
        v19 = os->lacing_fill;
      ++os->lacing_fill;
      ++v5;
      if ( v20 < 255 )
        os->lacing_packet = os->lacing_fill;
    }
    while ( v5 < segments );
    if ( v19 != -1 )
    {
      v23 = os->granule_vals;
      LODWORD(v23[v19]) = granulepos;
      HIDWORD(v23[v19]) = granulepos_4;
    }
  }
  if ( eos )
  {
    v24 = os->lacing_fill;
    os->e_o_s = 1;
    if ( v24 > 0 )
      BYTE1(os->lacing_vals[v24 - 1]) |= 2u;
  }
  os->pageno = pageno + 1;
  return 0;
}

// FUNC: _ogg_sync_reset
int __cdecl ogg_sync_reset(ogg_sync_state *oy)
{
  oy->fill = 0;
  oy->returned = 0;
  oy->unsynced = 0;
  oy->headerbytes = 0;
  oy->bodybytes = 0;
  return 0;
}

// FUNC: _ogg_stream_reset
int __cdecl ogg_stream_reset(ogg_stream_state *os)
{
  os->body_fill = 0;
  os->body_returned = 0;
  os->lacing_fill = 0;
  os->lacing_packet = 0;
  os->lacing_returned = 0;
  os->header_fill = 0;
  os->e_o_s = 0;
  os->b_o_s = 0;
  os->pageno = -1;
  os->packetno = 0i64;
  os->granulepos = 0i64;
  return 0;
}

// FUNC: _ogg_stream_reset_serialno
int __cdecl ogg_stream_reset_serialno(ogg_stream_state *os, int serialno)
{
  os->body_fill = 0;
  os->body_returned = 0;
  os->lacing_fill = 0;
  os->lacing_packet = 0;
  os->lacing_returned = 0;
  os->header_fill = 0;
  os->e_o_s = 0;
  os->b_o_s = 0;
  os->packetno = 0i64;
  os->granulepos = 0i64;
  os->pageno = -1;
  os->serialno = serialno;
  return 0;
}

// FUNC: _ogg_stream_packetout
int __cdecl ogg_stream_packetout(ogg_stream_state *os, ogg_packet *op)
{
  return packetout(os, op, 1);
}

// FUNC: _ogg_stream_packetpeek
int __cdecl ogg_stream_packetpeek(ogg_stream_state *os, ogg_packet *op)
{
  return packetout(os, op, 0);
}
