
// FUNC: send_bits
void __usercall send_bits(deflate_state_s *s@<eax>, const unsigned int val@<ecx>, const unsigned int len@<edi>)
{
  unsigned int bi_valid; // ecx
  __int16 v5; // dx
  unsigned int v6; // edx

  bi_valid = s->bi_valid;
  if ( bi_valid <= 16 - len )
  {
    s->bi_valid = len + bi_valid;
    s->bi_buf |= val << bi_valid;
  }
  else
  {
    v5 = s->bi_buf | (val << bi_valid);
    s->pending_buf[s->pending] = v5;
    s->pending_buf[++s->pending] = HIBYTE(v5);
    v6 = s->bi_valid;
    ++s->pending;
    s->bi_valid = v6 + len - 16;
    s->bi_buf = val >> (16 - v6);
  }
}

// FUNC: init_block
void __fastcall init_block(int a1, deflate_state_s *s)
{
  ct_data_s *dyn_ltree; // eax
  int v3; // ecx
  ct_data_s *dyn_dtree; // eax
  int v5; // ecx
  ct_data_s *bl_tree; // eax
  int v7; // ecx

  dyn_ltree = s->dyn_ltree;
  v3 = 286;
  do
  {
    dyn_ltree->fc.freq = 0;
    ++dyn_ltree;
    --v3;
  }
  while ( v3 );
  dyn_dtree = s->dyn_dtree;
  v5 = 30;
  do
  {
    dyn_dtree->fc.freq = 0;
    ++dyn_dtree;
    --v5;
  }
  while ( v5 );
  bl_tree = s->bl_tree;
  v7 = 19;
  do
  {
    bl_tree->fc.freq = 0;
    ++bl_tree;
    --v7;
  }
  while ( v7 );
  s->opt_len = 0;
  s->static_len = 0;
  s->last_lit = 0;
  s->matches = 0;
  s->dyn_ltree[256].fc.freq = 1;
}

// FUNC: pqdownheap
void __usercall pqdownheap(deflate_state_s *s@<eax>, ct_data_s *tree@<edi>, unsigned int node)
{
  unsigned int heap_len; // edx
  unsigned int v4; // ebp
  unsigned int v5; // ecx
  bool v6; // cf
  unsigned int v7; // esi
  unsigned int v8; // ebp
  unsigned __int16 freq; // dx
  unsigned __int16 v10; // bx
  unsigned int v11; // esi
  unsigned __int16 v12; // dx
  unsigned __int16 v13; // bx
  unsigned int v14; // edx
  unsigned int base; // [esp+8h] [ebp-4h]

  heap_len = s->heap_len;
  v4 = s->heap[node];
  v5 = 2 * node;
  v6 = 2 * node < heap_len;
  base = v4;
  if ( 2 * node > heap_len )
  {
    s->heap[node] = v4;
  }
  else
  {
    while ( 1 )
    {
      if ( v6 )
      {
        v7 = s->heap[v5];
        v8 = s->heap[v5 + 1];
        freq = tree[v8].fc.freq;
        v10 = tree[v7].fc.freq;
        if ( freq < v10 || freq == v10 && s->depth[v8] <= s->depth[v7] )
          ++v5;
        v4 = base;
      }
      v11 = s->heap[v5];
      v12 = tree[v4].fc.freq;
      v13 = tree[v11].fc.freq;
      if ( v12 < v13 )
      {
LABEL_12:
        s->heap[node] = v4;
        return;
      }
      if ( v12 == v13 && s->depth[v4] <= s->depth[v11] )
        break;
      s->heap[node] = v11;
      v14 = s->heap_len;
      node = v5;
      v5 *= 2;
      v6 = v5 < v14;
      if ( v5 > v14 )
        goto LABEL_12;
    }
    s->heap[node] = v4;
  }
}

// FUNC: gen_bitlen
void __usercall gen_bitlen(deflate_state_s *s@<eax>, tree_desc_s *desc@<ebx>)
{
  static_tree_desc_s *stat_desc; // ecx
  const ct_data_s *static_tree; // ebp
  unsigned int v4; // edi
  unsigned int v5; // ecx
  unsigned int v6; // edx
  unsigned int v7; // ecx
  unsigned int v8; // esi
  int freq; // edi
  unsigned int v10; // ebp
  unsigned __int16 *v11; // esi
  unsigned int v12; // ecx
  _WORD *i; // edx
  unsigned int v14; // edx
  unsigned int v15; // esi
  unsigned int *v16; // ebp
  unsigned int v17; // ecx
  int dad; // edi
  unsigned int max_length; // [esp+Ch] [ebp-1Ch]
  unsigned int *v20; // [esp+10h] [ebp-18h]
  unsigned int n; // [esp+14h] [ebp-14h]
  unsigned int na; // [esp+14h] [ebp-14h]
  unsigned int heapIdx; // [esp+18h] [ebp-10h]
  unsigned int v24; // [esp+1Ch] [ebp-Ch]
  unsigned __int16 *v25; // [esp+1Ch] [ebp-Ch]
  unsigned int base; // [esp+20h] [ebp-8h]
  const unsigned int *extra; // [esp+24h] [ebp-4h]

  stat_desc = desc->stat_desc;
  extra = stat_desc->extra_bits;
  base = stat_desc->extra_base;
  static_tree = stat_desc->static_tree;
  v4 = stat_desc->max_length;
  *(_DWORD *)s->bl_count = 0;
  *(_DWORD *)&s->bl_count[2] = 0;
  *(_DWORD *)&s->bl_count[4] = 0;
  *(_DWORD *)&s->bl_count[6] = 0;
  *(_DWORD *)&s->bl_count[8] = 0;
  *(_DWORD *)&s->bl_count[10] = 0;
  *(_DWORD *)&s->bl_count[12] = 0;
  *(_DWORD *)&s->bl_count[14] = 0;
  n = 0;
  desc->dyn_tree[s->heap[s->heap_max]].dl.dad = 0;
  v5 = s->heap_max + 1;
  max_length = v4;
  if ( v5 < 0x23D )
  {
    v20 = &s->heap[v5];
    v24 = 573 - v5;
    heapIdx = 573;
    do
    {
      v6 = *v20;
      v7 = desc->dyn_tree[desc->dyn_tree[*v20].dl.dad].dl.dad + 1;
      if ( v7 > v4 )
      {
        ++n;
        v7 = v4;
        v4 = max_length;
      }
      desc->dyn_tree[v6].dl.dad = v7;
      if ( v6 <= desc->max_code )
      {
        ++s->bl_count[v7];
        v8 = 0;
        if ( v6 >= base )
          v8 = extra[v6 - base];
        freq = desc->dyn_tree[v6].fc.freq;
        s->opt_len += freq * (v8 + v7);
        if ( static_tree )
          s->static_len += freq * (v8 + static_tree[v6].dl.dad);
        v4 = max_length;
      }
      ++v20;
      --v24;
    }
    while ( v24 );
    v10 = n;
    if ( n )
    {
      v11 = &s->bl_count[v4];
      do
      {
        v12 = v4 - 1;
        for ( i = (_WORD *)&s->bl_desc.stat_desc + v4 + 1; !*i; --v12 )
          --i;
        --s->bl_count[v12];
        s->bl_count[v12 + 1] += 2;
        --*v11;
        v10 -= 2;
      }
      while ( v10 );
      v14 = v4;
      if ( v4 )
      {
        v25 = &s->bl_count[v4];
        do
        {
          v15 = *v11;
          na = v15;
          if ( v15 )
          {
            v16 = &s->heap[heapIdx];
            do
            {
              v17 = *(v16 - 1);
              --heapIdx;
              --v16;
              if ( v17 <= desc->max_code )
              {
                dad = desc->dyn_tree[v17].dl.dad;
                if ( dad != v14 )
                {
                  s->opt_len += desc->dyn_tree[v17].fc.freq * (v14 - dad);
                  desc->dyn_tree[v17].dl.dad = v14;
                }
                v15 = --na;
              }
            }
            while ( v15 );
          }
          --v14;
          v11 = --v25;
        }
        while ( v14 );
      }
    }
  }
}

// FUNC: bi_windup
void __usercall bi_windup(deflate_state_s *s@<eax>)
{
  unsigned int bi_valid; // edx
  unsigned __int16 bi_buf; // cx

  bi_valid = s->bi_valid;
  if ( bi_valid <= 8 )
  {
    if ( bi_valid )
      s->pending_buf[s->pending++] = s->bi_buf;
    s->bi_buf = 0;
    s->bi_valid = 0;
  }
  else
  {
    bi_buf = s->bi_buf;
    s->pending_buf[s->pending] = bi_buf;
    s->pending_buf[++s->pending] = HIBYTE(bi_buf);
    ++s->pending;
    s->bi_buf = 0;
    s->bi_valid = 0;
  }
}

// FUNC: gen_codes
void __usercall gen_codes(ct_data_s *tree@<edi>, unsigned int max_code@<ebx>, char *bl_count@<edx>)
{
  __int16 v3; // cx
  unsigned int v4; // eax
  int v5; // edx
  __int16 v6; // si
  unsigned int v7; // esi
  int dad; // eax
  unsigned __int16 v9; // dx
  unsigned int v10; // ecx
  int v11; // edx
  unsigned int v12; // eax
  int v13; // ebp
  unsigned __int16 next_code[16]; // [esp+8h] [ebp-20h] BYREF

  v3 = 0;
  v4 = 1;
  v5 = bl_count - (char *)&next_code[1];
  do
  {
    v6 = v3 + *(unsigned __int16 *)((char *)&next_code[v4++] + v5);
    v3 = 2 * v6;
    next_code[v4 - 1] = 2 * v6;
  }
  while ( v4 <= 0xF );
  v7 = 0;
  do
  {
    dad = tree[v7].dl.dad;
    if ( tree[v7].dl.dad )
    {
      v9 = next_code[dad];
      v10 = v9;
      next_code[dad] = v9 + 1;
      v11 = dad;
      v12 = 0;
      do
      {
        v13 = v10 & 1;
        v10 >>= 1;
        v12 = 2 * (v13 | v12);
        --v11;
      }
      while ( v11 );
      tree[v7].fc.freq = v12 >> 1;
    }
    ++v7;
  }
  while ( v7 <= max_code );
}

// FUNC: build_tree
void __usercall build_tree(deflate_state_s *s@<eax>, tree_desc_s *desc)
{
  ct_data_s *dyn_tree; // edi
  static_tree_desc_s *stat_desc; // ecx
  unsigned int v4; // edx
  const ct_data_s *static_tree; // esi
  unsigned int v6; // ebp
  unsigned int v7; // ecx
  unsigned int v8; // edx
  unsigned int v9; // ecx
  unsigned int i; // esi
  unsigned int v11; // ebx
  unsigned int heap_len; // ecx
  unsigned int v13; // esi
  deflate_state_s *v14; // eax
  unsigned int v15; // ebp
  unsigned __int8 v16; // cl
  unsigned __int8 v17; // dl
  int v18; // eax
  unsigned int max_code; // [esp+10h] [ebp-8h]
  unsigned int elems; // [esp+14h] [ebp-4h]

  dyn_tree = desc->dyn_tree;
  stat_desc = desc->stat_desc;
  v4 = stat_desc->elems;
  static_tree = stat_desc->static_tree;
  v6 = 0;
  v7 = 0;
  elems = v4;
  max_code = 0;
  s->heap_len = 0;
  for ( s->heap_max = 573; v7 < v4; ++v7 )
  {
    if ( dyn_tree[v7].fc.freq )
    {
      s->heap[++s->heap_len] = v7;
      max_code = v7;
      s->depth[v7] = 0;
      v6 = v7;
    }
    else
    {
      dyn_tree[v7].dl.dad = 0;
    }
  }
  if ( s->heap_len < 2 )
  {
    do
    {
      if ( v6 >= 2 )
        v8 = 0;
      else
        v8 = ++v6;
      s->heap[++s->heap_len] = v8;
      v9 = s->heap[s->heap_len];
      dyn_tree[v9].fc.freq = 1;
      s->depth[v9] = 0;
      --s->opt_len;
      if ( static_tree )
        s->static_len -= static_tree[v9].dl.dad;
    }
    while ( s->heap_len < 2 );
    max_code = v6;
  }
  desc->max_code = v6;
  for ( i = s->heap_len >> 1; i; --i )
    pqdownheap(s, dyn_tree, i);
  v11 = elems;
  do
  {
    heap_len = s->heap_len;
    v13 = s->heap[1];
    s->heap[1] = s->heap[heap_len];
    s->heap_len = heap_len - 1;
    pqdownheap(s, dyn_tree, 1u);
    v15 = v14->heap[1];
    --v14->heap_max;
    v14->heap[v14->heap_max--] = v13;
    v14->heap[v14->heap_max] = v15;
    dyn_tree[v11].fc.freq = dyn_tree[v13].fc.freq + dyn_tree[v15].fc.freq;
    v16 = v14->depth[v15];
    v17 = v14->depth[v13];
    if ( v17 <= v16 )
      v14->depth[v11] = v16 + 1;
    else
      v14->depth[v11] = v17;
    dyn_tree[v15].dl.dad = v11;
    dyn_tree[v13].dl.dad = v11;
    v14->heap[1] = v11++;
    pqdownheap(v14, dyn_tree, 1u);
  }
  while ( s->heap_len >= 2 );
  s->heap[--s->heap_max] = s->heap[1];
  gen_bitlen(s, desc);
  gen_codes(dyn_tree, max_code, (char *)(v18 + 264956));
}

// FUNC: scan_tree
void __usercall scan_tree(ct_data_s *tree@<eax>, unsigned int max_code@<ecx>, deflate_state_s *s)
{
  unsigned int dad; // edi
  unsigned int v4; // edx
  unsigned int v6; // ecx
  unsigned int v7; // esi
  unsigned int v8; // eax
  $2467CA9704E0472D4CCF1296A763D23A *p_dl; // [esp+10h] [ebp-Ch]
  unsigned int prevlen; // [esp+14h] [ebp-8h]
  int v11; // [esp+18h] [ebp-4h]

  dad = tree->dl.dad;
  v4 = 0;
  prevlen = 0xFFFF;
  v6 = 7;
  v7 = 4;
  if ( !tree->dl.dad )
  {
    v6 = 138;
    v7 = 3;
  }
  tree[max_code + 1].dl.dad = -1;
  v11 = max_code + 1;
  p_dl = &tree[1].dl;
  do
  {
    v8 = dad;
    dad = p_dl->dad;
    if ( ++v4 >= v6 || v8 != dad )
    {
      if ( v4 >= v7 )
      {
        if ( v8 )
        {
          if ( v8 != prevlen )
            ++s->bl_tree[v8].fc.freq;
          ++s->bl_tree[16].fc.freq;
        }
        else if ( v4 > 0xA )
        {
          ++s->bl_tree[18].fc.freq;
        }
        else
        {
          ++s->bl_tree[17].fc.freq;
        }
      }
      else
      {
        s->bl_tree[v8].fc.freq += v4;
      }
      v4 = 0;
      prevlen = v8;
      if ( dad )
      {
        if ( v8 == dad )
        {
          v6 = 6;
          v7 = 3;
        }
        else
        {
          v6 = 7;
          v7 = 4;
        }
      }
      else
      {
        v6 = 138;
        v7 = 3;
      }
    }
    p_dl += 2;
    --v11;
  }
  while ( v11 );
}

// FUNC: send_tree
void __usercall send_tree(deflate_state_s *s@<eax>, ct_data_s *tree@<ecx>, unsigned int max_code)
{
  int dad; // ebp
  unsigned int v5; // ebx
  int v6; // edi
  unsigned int v7; // ecx
  unsigned int v8; // edx
  int v9; // esi
  deflate_state_s *v10; // eax
  unsigned int v11; // ecx
  unsigned int v12; // edi
  $2467CA9704E0472D4CCF1296A763D23A *p_dl; // [esp+10h] [ebp-4h]
  unsigned int max_codea; // [esp+18h] [ebp+4h]

  dad = tree->dl.dad;
  v5 = 0;
  v6 = 0xFFFF;
  v7 = 7;
  v8 = 4;
  if ( !dad )
  {
    v7 = 138;
    v8 = 3;
  }
  p_dl = &tree[1].dl;
  max_codea = max_code + 1;
  do
  {
    v9 = dad;
    dad = p_dl->dad;
    if ( ++v5 >= v7 || v9 != dad )
    {
      if ( v5 >= v8 )
      {
        if ( v9 )
        {
          if ( v9 != v6 )
          {
            send_bits(s, s->bl_tree[v9].fc.freq, s->bl_tree[v9].dl.dad);
            --v5;
          }
          send_bits(s, s->bl_tree[16].fc.freq, s->bl_tree[16].dl.dad);
          v11 = v5 - 3;
          v12 = 2;
        }
        else if ( v5 > 0xA )
        {
          send_bits(s, s->bl_tree[18].fc.freq, s->bl_tree[18].dl.dad);
          v11 = v5 - 11;
          v12 = 7;
        }
        else
        {
          send_bits(s, s->bl_tree[17].fc.freq, s->bl_tree[17].dl.dad);
          v11 = v5 - 3;
          v12 = 3;
        }
        send_bits(v10, v11, v12);
      }
      else
      {
        do
        {
          send_bits(s, s->bl_tree[v9].fc.freq, s->bl_tree[v9].dl.dad);
          --v5;
        }
        while ( v5 );
      }
      v5 = 0;
      v6 = v9;
      if ( dad )
      {
        if ( v9 == dad )
        {
          v7 = 6;
          v8 = 3;
        }
        else
        {
          v7 = 7;
          v8 = 4;
        }
      }
      else
      {
        v7 = 138;
        v8 = 3;
      }
    }
    p_dl += 2;
    --max_codea;
  }
  while ( max_codea );
}

// FUNC: send_all_trees
void __usercall send_all_trees(
        deflate_state_s *s@<eax>,
        unsigned int blcodes@<ebx>,
        unsigned int lcodes,
        unsigned int dcodes)
{
  deflate_state_s *v4; // eax
  deflate_state_s *v5; // eax
  deflate_state_s *v6; // eax
  unsigned int i; // esi
  deflate_state_s *v8; // eax

  send_bits(s, lcodes - 257, 5u);
  send_bits(v4, dcodes - 1, 5u);
  send_bits(v5, blcodes - 4, 4u);
  for ( i = 0; i < blcodes; ++i )
    send_bits(v6, v6->bl_tree[bl_order[i]].dl.dad, 3u);
  send_tree(v6, v6->dyn_ltree, lcodes - 1);
  send_tree(v8, v8->dyn_dtree, dcodes - 1);
}

// FUNC: compress_block
void __usercall compress_block(deflate_state_s *s@<eax>, const ct_data_s *ltree, const ct_data_s *dtree)
{
  unsigned int v3; // esi
  unsigned __int16 *i; // ecx
  int v5; // ebp
  int v6; // ebx
  int v7; // esi
  deflate_state_s *v8; // eax
  unsigned int v9; // edi
  unsigned int v10; // ebp
  unsigned __int8 v11; // cl
  int v12; // esi
  unsigned int v13; // edi
  int v14; // eax
  unsigned int lenIdx; // [esp+8h] [ebp-8h]
  unsigned __int16 *v16; // [esp+Ch] [ebp-4h]

  v3 = 0;
  if ( s->last_lit )
  {
    for ( i = s->d_buf; ; i = v16 )
    {
      v5 = *i;
      v6 = s->l_buf[v3++];
      v16 = i + 1;
      lenIdx = v3;
      if ( *i )
      {
        v7 = tr_length_code[v6];
        send_bits(s, ltree[v7 + 257].fc.freq, ltree[v7 + 257].dl.dad);
        v9 = extra_lbits[v7];
        if ( v9 )
          send_bits(v8, v6 - base_length[v7], v9);
        v10 = v5 - 1;
        v11 = v10 >= 0x100 ? tr_dist_code[(v10 >> 7) + 256] : tr_dist_code[v10];
        v12 = v11;
        send_bits(v8, dtree[v11].fc.freq, dtree[v11].dl.dad);
        v13 = extra_dbits[v12];
        if ( v13 )
          send_bits(s, v10 - base_dist[v12], v13);
        v3 = lenIdx;
      }
      else
      {
        send_bits(s, ltree[v6].fc.freq, ltree[v6].dl.dad);
      }
      if ( v3 >= s->last_lit )
        break;
    }
  }
  send_bits(s, ltree[256].fc.freq, ltree[256].dl.dad);
  *(_DWORD *)(v14 + 317032) = ltree[256].dl.dad;
}

// FUNC: tr_stored_block
void __usercall tr_stored_block(
        deflate_state_s *s@<eax>,
        unsigned int stored_len@<ebx>,
        bool eof@<cl>,
        const unsigned __int8 *buf)
{
  deflate_state_s *v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  unsigned int v9; // edi

  send_bits(s, eof, 3u);
  bi_windup(v5);
  v7 = *(_DWORD *)(v6 + 65560);
  *(_DWORD *)(v6 + 317032) = 8;
  *(_BYTE *)(v7 + v6 + 16) = stored_len;
  *(_BYTE *)(++*(_DWORD *)(v6 + 65560) + v6 + 16) = BYTE1(stored_len);
  *(_BYTE *)(++*(_DWORD *)(v6 + 65560) + v6 + 16) = ~(_BYTE)stored_len;
  *(_BYTE *)(++*(_DWORD *)(v6 + 65560) + v6 + 16) = (unsigned __int16)~(_WORD)stored_len >> 8;
  v8 = ++*(_DWORD *)(v6 + 65560);
  if ( stored_len )
  {
    v9 = stored_len;
    do
    {
      *(_BYTE *)(v8 + v6 + 16) = *buf;
      v8 = ++*(_DWORD *)(v6 + 65560);
      ++buf;
      --v9;
    }
    while ( v9 );
  }
}

// FUNC: tr_flush_block
void __usercall tr_flush_block(
        deflate_state_s *s@<edx>,
        const unsigned __int8 *buf@<ecx>,
        unsigned int stored_len@<eax>,
        bool eof)
{
  unsigned int v5; // ebp
  unsigned int v8; // ecx
  unsigned int v9; // eax
  int v10; // ecx
  deflate_state_s *v11; // eax

  v5 = 0;
  if ( s->level <= Z_STORE_COMPRESSION )
  {
    v9 = stored_len + 5;
LABEL_5:
    v8 = v9;
    goto LABEL_6;
  }
  build_tree(s, &s->l_desc);
  build_tree(s, &s->d_desc);
  v5 = build_bl_tree(s);
  v8 = (s->opt_len + 10) >> 3;
  v9 = (s->static_len + 10) >> 3;
  if ( v9 <= v8 )
    goto LABEL_5;
LABEL_6:
  if ( stored_len + 4 <= v8 && buf )
  {
    tr_stored_block(s, stored_len, eof, buf);
  }
  else if ( v9 == v8 )
  {
    send_bits(s, eof + 2, 3u);
    compress_block(v11, static_ltree, static_dtree);
  }
  else
  {
    send_bits(s, eof + 4, 3u);
    send_all_trees(s, v5 + 1, s->l_desc.max_code + 1, s->d_desc.max_code + 1);
    compress_block(s, s->dyn_ltree, s->dyn_dtree);
  }
  init_block(v10, s);
  if ( eof )
    bi_windup(s);
}

// FUNC: bool __cdecl tr_tally_lit(struct deflate_state_s *,unsigned char)
bool __cdecl tr_tally_lit(deflate_state_s *s, unsigned __int8 c)
{
  s->d_buf[s->last_lit] = 0;
  s->l_buf[s->last_lit++] = c;
  ++s->dyn_ltree[c].fc.freq;
  return s->last_lit == 0x3FFF;
}

// FUNC: bool __cdecl tr_tally_dist(struct deflate_state_s *,unsigned long,unsigned long)
bool __cdecl tr_tally_dist(deflate_state_s *s, unsigned __int16 dist, unsigned __int8 len)
{
  unsigned int v3; // ecx
  unsigned __int8 v4; // cl

  s->d_buf[s->last_lit] = dist;
  s->l_buf[s->last_lit++] = len;
  ++s->dyn_ltree[tr_length_code[len] + 257].fc.freq;
  v3 = dist - 1;
  if ( v3 >= 0x100 )
    v4 = tr_dist_code[(v3 >> 7) + 256];
  else
    v4 = tr_dist_code[v3];
  ++s->dyn_dtree[v4].fc.freq;
  return s->last_lit == 0x3FFF;
}

// FUNC: flush_pending
void __usercall flush_pending(z_stream_s *z@<eax>)
{
  deflate_state_s *dstate; // esi
  unsigned int pending; // edx
  deflate_state_s *v3; // ecx
  deflate_state_s *v4; // eax

  dstate = z->dstate;
  pending = dstate->pending;
  if ( pending > z->avail_out )
    pending = z->avail_out;
  if ( pending )
  {
    qmemcpy(z->next_out, dstate->pending_out, pending);
    v3 = z->dstate;
    z->next_out += pending;
    z->total_out += pending;
    v3->pending_out += pending;
    z->avail_out -= pending;
    z->dstate->pending -= pending;
    v4 = z->dstate;
    if ( !v4->pending )
      v4->pending_out = v4->pending_buf;
  }
}

// FUNC: fill_window
void __usercall fill_window(deflate_state_s *s@<ebx>)
{
  unsigned int strstart; // eax
  unsigned int v2; // edx
  unsigned int *p_ins_h; // eax
  int v4; // esi
  unsigned int v5; // ecx
  __int16 v6; // cx
  unsigned __int16 *head; // eax
  int v8; // esi
  unsigned int v9; // ecx
  unsigned __int16 v10; // cx
  z_stream_s *z; // ebp
  unsigned __int8 *v12; // edi
  unsigned int avail_in; // esi
  unsigned int v14; // eax
  deflate_state_s *dstate; // eax
  unsigned int lookahead; // ecx
  unsigned int v17; // [esp+Ch] [ebp-4h]

  do
  {
    strstart = s->strstart;
    v2 = 0x10000 - strstart - s->lookahead;
    if ( strstart >= 0xFEFA )
    {
      qmemcpy(s->window, &s->window[0x8000], 0x8000u);
      s->match_start -= 0x8000;
      s->strstart -= 0x8000;
      s->block_start -= 0x8000;
      p_ins_h = &s->ins_h;
      v4 = 0x8000;
      do
      {
        v5 = *((unsigned __int16 *)p_ins_h - 1);
        p_ins_h = (unsigned int *)((char *)p_ins_h - 2);
        if ( v5 < 0x8000 )
          v6 = 0;
        else
          v6 = v5 + 0x8000;
        --v4;
        *(_WORD *)p_ins_h = v6;
      }
      while ( v4 );
      head = s->head;
      v8 = 0x8000;
      do
      {
        v9 = *--head;
        if ( v9 < 0x8000 )
          v10 = 0;
        else
          v10 = v9 + 0x8000;
        --v8;
        *head = v10;
      }
      while ( v8 );
      v2 += 0x8000;
    }
    z = s->z;
    if ( !s->z->avail_in )
      break;
    v12 = &s->window[s->lookahead + s->strstart];
    avail_in = z->avail_in;
    v17 = avail_in;
    if ( avail_in > v2 )
    {
      v17 = v2;
      avail_in = v2;
    }
    if ( avail_in )
    {
      z->avail_in -= avail_in;
      dstate = z->dstate;
      if ( !dstate->noheader )
        z->dstate->adler = adler32(dstate->adler, z->next_in, avail_in);
      v14 = v17;
      qmemcpy(v12, z->next_in, avail_in);
      z->next_in += v17;
    }
    else
    {
      v14 = 0;
    }
    s->lookahead += v14;
    lookahead = s->lookahead;
    if ( lookahead >= 3 )
      s->ins_h = (s->window[s->strstart + 1] ^ (unsigned __int16)(32 * s->window[s->strstart])) & 0x7FFF;
  }
  while ( lookahead < 0x106 && s->z->avail_in );
}

// FUNC: void __cdecl flush_block_only(struct deflate_state_s *,bool)
void __cdecl flush_block_only(deflate_state_s *s, bool eof)
{
  int block_start; // ecx

  block_start = s->block_start;
  if ( block_start < 0 )
    tr_flush_block(s, 0, s->strstart - block_start, eof);
  else
    tr_flush_block(s, &s->window[block_start], s->strstart - block_start, eof);
  s->block_start = s->strstart;
  flush_pending(s->z);
}
