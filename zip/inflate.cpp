
// FUNC: inflate_blocks_reset
void __usercall inflate_blocks_reset(inflate_blocks_state_s *s@<esi>, z_stream_s *z)
{
  if ( s->mode == BTREE || s->mode == DTREE )
    Mem_Free(s->trees.blens);
  if ( s->mode == CODES )
    Mem_Free(s->decode.codes);
  s->mode = TYPE;
  s->bitk = 0;
  s->bitb = 0;
  s->write = s->window;
  s->read = s->window;
  z->istate->adler = 1;
}

// FUNC: inflate_flush_copy
void __usercall inflate_flush_copy(z_stream_s *z@<ebx>, inflate_blocks_state_s *s, unsigned int count)
{
  unsigned int avail_out; // ebp
  inflate_state_s *istate; // eax

  avail_out = count;
  if ( count > z->avail_out )
    avail_out = z->avail_out;
  if ( avail_out && z->error == Z_BUF_ERROR )
    z->error = Z_OK;
  istate = z->istate;
  if ( !istate->nowrap )
    z->istate->adler = adler32(istate->adler, s->read, avail_out);
  qmemcpy(z->next_out, s->read, avail_out);
  z->avail_out -= avail_out;
  z->total_out += avail_out;
  z->next_out += avail_out;
  s->read += avail_out;
}

// FUNC: inflate_flush
void __usercall inflate_flush(z_stream_s *z@<eax>, inflate_blocks_state_s *s@<esi>)
{
  unsigned __int8 *read; // ecx
  unsigned __int8 *write; // eax
  unsigned __int8 *end; // eax
  bool v6; // zf
  unsigned __int8 *window; // ecx

  read = s->read;
  write = s->write;
  if ( read > write )
    write = s->end;
  inflate_flush_copy(z, s, write - read);
  end = s->end;
  if ( s->read == end )
  {
    v6 = s->write == end;
    window = s->window;
    s->read = s->window;
    if ( v6 )
      s->write = window;
    inflate_flush_copy(z, s, s->write - window);
  }
}

// FUNC: getbits
char __usercall getbits@<al>(z_stream_s *z@<eax>, inflate_blocks_state_s *s@<ecx>, unsigned int bits@<edx>)
{
  unsigned int avail_in; // ecx
  unsigned __int8 *next_in; // ecx

  if ( s->bitk >= bits )
    return 1;
  while ( 1 )
  {
    avail_in = z->avail_in;
    if ( !avail_in )
      break;
    ++z->total_in;
    z->avail_in = avail_in - 1;
    next_in = z->next_in;
    z->error = Z_OK;
    s->bitb |= *next_in << s->bitk;
    ++z->next_in;
    s->bitk += 8;
    if ( s->bitk >= bits )
      return 1;
  }
  inflate_flush(z, s);
  return 0;
}

// FUNC: inflate_codes
void __usercall inflate_codes(inflate_blocks_state_s *s@<eax>, z_stream_s *z)
{
  unsigned __int8 *write; // eax
  unsigned __int8 *read; // ebx
  unsigned int left; // edi
  unsigned __int8 *v6; // ebx
  int v7; // eax
  z_stream_s *v8; // ebp
  int v9; // eax
  unsigned __int8 *v10; // edx
  unsigned __int8 *v11; // ecx
  int v12; // eax
  unsigned int bitb; // edx
  unsigned __int8 *v14; // eax
  int v15; // ecx
  z_stream_s *v16; // ebp
  int v17; // ecx
  int v18; // edx
  unsigned int v19; // edx
  unsigned __int8 *v20; // eax
  int v21; // ecx
  int v22; // ecx
  unsigned __int8 *v23; // ebp
  unsigned int v24; // eax
  unsigned __int8 *window; // ebp
  unsigned __int8 *v26; // ebx
  unsigned __int8 *v27; // eax
  unsigned int bitk; // eax

  write = s->write;
  read = s->read;
  left = s->left;
  if ( write >= read )
    v6 = (unsigned __int8 *)(s->end - write);
  else
    v6 = (unsigned __int8 *)(read - write - 1);
  v7 = *(_DWORD *)left;
  while ( 2 )
  {
    switch ( v7 )
    {
      case 0:
        v8 = z;
        if ( (unsigned int)v6 >= 0x102 && z->avail_in >= 0xA )
        {
          v9 = inflate_fast(
                 inflate_mask[*(unsigned __int8 *)(left + 16)],
                 inflate_mask[*(unsigned __int8 *)(left + 17)],
                 *(inflate_huft_s **)(left + 20),
                 *(inflate_huft_s **)(left + 24),
                 s,
                 z);
          z->error = v9;
          v10 = s->write;
          v11 = s->read;
          v6 = (unsigned __int8 *)(v10 >= v11 ? s->end - v10 : v11 - v10 - 1);
          if ( v9 )
          {
            *(_DWORD *)left = 2 * (v9 != 1) + 7;
            goto LABEL_46;
          }
        }
        v12 = *(_DWORD *)(left + 20);
        *(_DWORD *)(left + 12) = *(unsigned __int8 *)(left + 16);
        *(_DWORD *)(left + 8) = v12;
        *(_DWORD *)left = 1;
        goto LABEL_15;
      case 1:
        v8 = z;
LABEL_15:
        if ( getbits(v8, s, *(_DWORD *)(left + 12)) )
        {
          bitb = s->bitb;
          v14 = (unsigned __int8 *)(*(_DWORD *)(left + 8) + 8 * (bitb & inflate_mask[*(_DWORD *)(left + 12)]));
          s->bitb = bitb >> v14[1];
          s->bitk -= v14[1];
          v15 = *v14;
          if ( *v14 )
          {
            if ( (v15 & 0x10) != 0 )
            {
              *(_DWORD *)(left + 8) = v15 & 0xF;
              *(_DWORD *)(left + 4) = *((_DWORD *)v14 + 1);
              *(_DWORD *)left = 2;
            }
            else if ( (v15 & 0x40) != 0 )
            {
              if ( (v15 & 0x20) == 0 )
              {
                *(_DWORD *)left = 9;
                inflate_error = "Inflate data: Invalid literal/length code";
                v8->error = Z_DATA_ERROR;
                inflate_flush(v8, s);
                return;
              }
              *(_DWORD *)left = 7;
            }
            else
            {
              *(_DWORD *)(left + 12) = v15;
              *(_DWORD *)(left + 8) = &v14[8 * *((_DWORD *)v14 + 1)];
            }
          }
          else
          {
            *(_DWORD *)(left + 8) = *((_DWORD *)v14 + 1);
            *(_DWORD *)left = 6;
          }
LABEL_46:
          v7 = *(_DWORD *)left;
          if ( *(_DWORD *)left > 9u )
          {
LABEL_47:
            z->error = Z_STREAM_ERROR;
            inflate_flush(z, s);
            return;
          }
          continue;
        }
        if ( v8->status == Z_BUF_ERROR )
          v8->error = Z_STREAM_END;
        return;
      case 2:
        v16 = z;
        if ( !getbits(z, s, *(_DWORD *)(left + 8)) )
          return;
        v17 = *(_DWORD *)(left + 8);
        *(_DWORD *)(left + 4) += s->bitb & inflate_mask[v17];
        s->bitb >>= v17;
        s->bitk -= *(_DWORD *)(left + 8);
        v18 = *(_DWORD *)(left + 24);
        *(_DWORD *)(left + 12) = *(unsigned __int8 *)(left + 17);
        *(_DWORD *)(left + 8) = v18;
        *(_DWORD *)left = 3;
LABEL_27:
        if ( !getbits(v16, s, *(_DWORD *)(left + 12)) )
          return;
        v19 = s->bitb;
        v20 = (unsigned __int8 *)(*(_DWORD *)(left + 8) + 8 * (v19 & inflate_mask[*(_DWORD *)(left + 12)]));
        s->bitb = v19 >> v20[1];
        s->bitk -= v20[1];
        v21 = *v20;
        if ( (v21 & 0x10) != 0 )
        {
          *(_DWORD *)(left + 8) = v21 & 0xF;
          *(_DWORD *)(left + 12) = *((_DWORD *)v20 + 1);
          *(_DWORD *)left = 4;
        }
        else
        {
          if ( (v21 & 0x40) != 0 )
          {
            *(_DWORD *)left = 9;
            inflate_error = "Inflate data: Invalid distance code";
            v16->error = Z_DATA_ERROR;
            inflate_flush(v16, s);
            return;
          }
          *(_DWORD *)(left + 12) = v21;
          *(_DWORD *)(left + 8) = &v20[8 * *((_DWORD *)v20 + 1)];
        }
        goto LABEL_46;
      case 3:
        v16 = z;
        goto LABEL_27;
      case 4:
        if ( !getbits(z, s, *(_DWORD *)(left + 8)) )
          return;
        v22 = *(_DWORD *)(left + 8);
        *(_DWORD *)(left + 12) += s->bitb & inflate_mask[v22];
        s->bitb >>= v22;
        s->bitk -= *(_DWORD *)(left + 8);
        *(_DWORD *)left = 5;
$L107063:
        v23 = s->write;
        v24 = *(_DWORD *)(left + 12);
        if ( v23 - (unsigned __int8 *)s - 40 >= v24 )
          window = &v23[-v24];
        else
          window = &v23[&s->end[-v24] - (unsigned __int8 *)s - 40];
        if ( !*(_DWORD *)(left + 4) )
          goto LABEL_45;
        do
        {
          v26 = needout(z, s, v6);
          if ( !v26 )
            return;
          *s->write++ = *window++;
          v6 = v26 - 1;
          if ( window == s->end )
            window = s->window;
          --*(_DWORD *)(left + 4);
        }
        while ( *(_DWORD *)(left + 4) );
LABEL_45:
        *(_DWORD *)left = 0;
        goto LABEL_46;
      case 5:
        goto $L107063;
      case 6:
        v27 = needout(z, s, v6);
        if ( !v27 )
          return;
        *s->write++ = *(_BYTE *)(left + 8);
        v6 = v27 - 1;
        goto LABEL_45;
      case 7:
        bitk = s->bitk;
        if ( bitk > 7 )
        {
          s->bitk = bitk - 8;
          ++z->avail_in;
          --z->total_in;
          --z->next_in;
        }
        inflate_flush(z, s);
        if ( s->read == s->write )
        {
          *(_DWORD *)left = 8;
          z->error = Z_STREAM_END;
        }
        else
        {
          inflate_error = "Inflate data: read != write while in WASH";
        }
        inflate_flush(z, s);
        return;
      case 8:
        z->error = Z_STREAM_END;
        inflate_flush(z, s);
        return;
      case 9:
        z->error = Z_DATA_ERROR;
        inflate_flush(z, s);
        return;
      default:
        goto LABEL_47;
    }
  }
}

// FUNC: inflate_trees_bits
void __usercall inflate_trees_bits(
        z_stream_s *z@<edi>,
        unsigned int *bb@<esi>,
        inflate_huft_s *hp@<edx>,
        unsigned int *c,
        inflate_huft_s **tb)
{
  int v5; // eax
  unsigned int hn; // [esp+0h] [ebp-50h] BYREF
  unsigned int workspace[19]; // [esp+4h] [ebp-4Ch] BYREF

  hn = 0;
  v5 = huft_build(bb, c, 0x13u, 0x13u, 0, 0, tb, hp, &hn, workspace);
  z->error = v5;
  if ( v5 == -1 )
  {
    inflate_error = "Inflate data: Oversubscribed dynamic bit lengths tree";
  }
  else if ( v5 == -2 || !*bb )
  {
    inflate_error = "Inflate data: Incomplete dynamic bit lengths tree";
    z->error = Z_DATA_ERROR;
  }
}

// FUNC: inflate_trees_dynamic
void __usercall inflate_trees_dynamic(
        unsigned int numLiteral@<esi>,
        unsigned int *c@<ebx>,
        inflate_huft_s **tl@<edx>,
        inflate_huft_s *hp@<eax>,
        z_stream_s *z,
        unsigned int numDist,
        unsigned int *bl,
        unsigned int *bd,
        inflate_huft_s **td)
{
  int v10; // eax
  int v11; // eax
  unsigned int hn; // [esp+8h] [ebp-484h] BYREF
  unsigned int workspace[288]; // [esp+Ch] [ebp-480h] BYREF

  hn = 0;
  v10 = huft_build(bl, c, numLiteral, 0x101u, cplens, cplext, tl, hp, &hn, workspace);
  z->error = v10;
  if ( v10 || !*bl )
  {
    inflate_error = "Inflate data: Erroneous literal/length tree";
    z->error = Z_DATA_ERROR;
  }
  else
  {
    v11 = huft_build(bd, &c[numLiteral], numDist, 0, cpdist, extra_dbits, td, hp, &hn, workspace);
    z->error = v11;
    if ( v11 || !*bd && numLiteral > 0x101 )
    {
      z->error = Z_DATA_ERROR;
      inflate_error = "Inflate data: Erroneous distance tree";
    }
  }
}

// FUNC: inflate_blocks
void __cdecl inflate_blocks(inflate_blocks_state_s *s, z_stream_s *z)
{
  inflate_blocks_state_s *v2; // ebp
  unsigned __int8 *write; // ecx
  unsigned __int8 *read; // eax
  inflate_blocks_state_s *v5; // eax
  inflate_block_mode mode; // eax
  z_stream_s *v7; // eax
  z_stream_s *v8; // edi
  unsigned int v9; // eax
  unsigned int bitk; // eax
  int v11; // ecx
  unsigned int v12; // edx
  char v13; // bl
  _BYTE *v14; // eax
  char v15; // cl
  z_stream_s *v16; // edi
  unsigned int bitb; // ecx
  z_stream_s *v18; // ebx
  unsigned __int8 *v19; // edx
  unsigned int left; // eax
  z_stream_s *v21; // ecx
  bool v22; // zf
  unsigned int v23; // eax
  unsigned int v24; // ecx
  unsigned int v25; // eax
  unsigned int *v26; // eax
  inflate_huft_s *hufts; // edx
  unsigned int bb; // esi
  unsigned int v29; // ecx
  inflate_huft_s *tb; // edx
  inflate_blocks_state_s *v31; // edi
  int Bits; // esi
  unsigned int v33; // eax
  int v34; // edi
  unsigned int v35; // edx
  unsigned int v36; // eax
  BOOL v37; // ecx
  unsigned int v38; // eax
  int v39; // esi
  int v40; // ecx
  unsigned int index; // edx
  unsigned int v42; // ecx
  unsigned int v43; // esi
  inflate_huft_s *v44; // eax
  unsigned int *v45; // ebx
  z_stream_s *v46; // edi
  _BYTE *v47; // eax
  char v48; // dl
  inflate_huft_s *v49; // ecx
  inflate_huft_s *v50; // edx
  unsigned __int8 *v51; // ecx
  unsigned __int8 *v52; // eax
  inflate_blocks_state_s *v53; // eax
  z_stream_s *v54; // eax
  z_stream_s *v55; // [esp-14h] [ebp-30h]
  unsigned int *blens; // [esp-8h] [ebp-24h]
  unsigned int bd; // [esp+10h] [ebp-Ch] BYREF
  inflate_huft_s *lengthTree; // [esp+14h] [ebp-8h] BYREF
  inflate_huft_s *distTree; // [esp+18h] [ebp-4h] BYREF

  v2 = s;
  write = s->write;
  read = s->read;
  lengthTree = 0;
  distTree = 0;
  if ( write >= read )
    v5 = (inflate_blocks_state_s *)(s->end - write);
  else
    v5 = (inflate_blocks_state_s *)(read - write - 1);
  s = v5;
  mode = v2->mode;
  while ( 2 )
  {
    switch ( mode )
    {
      case TYPE:
        v8 = z;
        if ( getbits(z, v2, 3u) )
        {
          v9 = (v2->bitb & 7) >> 1;
          v2->last = v2->bitb & 1;
          switch ( v9 )
          {
            case 0u:
              v2->bitk -= 3;
              bitk = v2->bitk;
              v2->bitb >>= 3;
              v11 = bitk & 7;
              v12 = v2->bitb >> v11;
              v2->bitk = bitk - v11;
              v2->mode = LENS;
              v2->bitb = v12;
              goto LABEL_64;
            case 1u:
              v13 = fixed_bl;
              bd = fixed_bd;
              lengthTree = fixed_tl;
              distTree = fixed_td;
              v8->error = Z_OK;
              v14 = Mem_Alloc(28, 2u);
              v15 = bd;
              *(_DWORD *)v14 = 0;
              v14[16] = v13;
              v14[17] = v15;
              *((_DWORD *)v14 + 5) = fixed_tl;
              *((_DWORD *)v14 + 6) = fixed_td;
              v2->bitb >>= 3;
              v2->bitk -= 3;
              v2->left = (unsigned int)v14;
              v2->mode = CODES;
              goto LABEL_64;
            case 2u:
              v2->bitb >>= 3;
              v2->bitk -= 3;
              v2->mode = TABLE;
              goto LABEL_64;
            case 3u:
              v2->bitb >>= 3;
              v2->bitk -= 3;
              v2->mode = BAD;
              inflate_error = "Inflate data: Invalid block type";
              v8->error = Z_DATA_ERROR;
              inflate_flush(v8, v2);
              break;
            default:
              goto LABEL_64;
          }
        }
        return;
      case LENS:
        v16 = z;
        if ( getbits(z, v2, 0x20u) )
        {
          bitb = (unsigned __int16)v2->bitb;
          if ( ~v2->bitb >> 16 == bitb )
          {
            v2->left = bitb;
            v2->bitb = 0;
            v2->bitk = 0;
            if ( bitb )
              v2->mode = STORED;
            else
              v2->mode = v2->last ? DRY : TYPE;
            goto LABEL_64;
          }
          v2->mode = BAD;
          inflate_error = "Inflate data: Invalid stored block lengths";
          v16->error = Z_DATA_ERROR;
          inflate_flush(v16, v2);
        }
        return;
      case STORED:
        v18 = z;
        if ( !z->avail_in )
          goto LABEL_71;
        v19 = needout(z, v2, (unsigned __int8 *)s);
        if ( v19 )
        {
          left = v2->left;
          if ( left > v18->avail_in )
            left = v18->avail_in;
          if ( left > (unsigned int)v19 )
            left = (unsigned int)v19;
          qmemcpy(v2->write, v18->next_in, left);
          v21 = z;
          z->next_in += left;
          v21->avail_in -= left;
          v21->total_in += left;
          v2->write += left;
          v22 = v2->left == left;
          v2->left -= left;
          s = (inflate_blocks_state_s *)&v19[-left];
          if ( v22 )
            v2->mode = v2->last ? DRY : TYPE;
          goto LABEL_64;
        }
        return;
      case TABLE:
        v18 = z;
        if ( getbits(z, v2, 0xEu) )
        {
          v23 = v2->bitb & 0x3FFF;
          v24 = v2->bitb & 0x1F;
          v2->left = v23;
          if ( v24 <= 0x1D )
          {
            v25 = (v23 >> 5) & 0x1F;
            if ( v25 <= 0x1D )
            {
              v26 = (unsigned int *)Mem_Alloc(4 * (v24 + v25) + 1032, 2u);
              v2->bitb >>= 14;
              v2->bitk -= 14;
              v2->trees.blens = v26;
              v2->trees.index = 0;
              v2->mode = BTREE;
              goto LABEL_31;
            }
          }
          v2->mode = BAD;
          inflate_error = "Inflate data: Too many length or distance symbols";
          v18->error = Z_DATA_ERROR;
          inflate_flush(v18, v2);
        }
        return;
      case BTREE:
        v18 = z;
LABEL_31:
        if ( v2->trees.index >= (v2->left >> 10) + 4 )
          goto LABEL_34;
        while ( getbits(v18, v2, 3u) )
        {
          v2->trees.blens[border[v2->trees.index++]] = v2->bitb & 7;
          v2->bitb >>= 3;
          v2->bitk -= 3;
          if ( v2->trees.index >= (v2->left >> 10) + 4 )
          {
LABEL_34:
            while ( v2->trees.index < 0x13 )
              v2->trees.blens[border[v2->trees.index++]] = 0;
            hufts = v2->hufts;
            blens = v2->trees.blens;
            v2->trees.bb = 7;
            inflate_trees_bits(v18, &v2->trees.bb, hufts, blens, &v2->trees.tb);
            if ( v18->error == Z_OK )
            {
              v2->trees.index = 0;
              v2->mode = DTREE;
              goto LABEL_39;
            }
            Mem_Free(v2->trees.blens);
            v2->mode = BAD;
            inflate_flush(v18, v2);
            return;
          }
        }
        return;
      case DTREE:
        v18 = z;
LABEL_39:
        if ( v2->trees.index >= ((v2->left >> 5) & 0x1F) + (v2->left & 0x1F) + 258 )
          goto LABEL_55;
        break;
      case CODES:
        v46 = z;
LABEL_58:
        inflate_codes(v2, v46);
        if ( v46->error != Z_STREAM_END )
          goto LABEL_79;
        v46->error = Z_OK;
        Mem_Free(v2->decode.codes);
        v51 = v2->write;
        v52 = v2->read;
        if ( v51 >= v52 )
          v53 = (inflate_blocks_state_s *)(v2->end - v51);
        else
          v53 = (inflate_blocks_state_s *)(v52 - v51 - 1);
        v22 = !v2->last;
        s = v53;
        if ( !v22 )
        {
          v2->mode = DRY;
          goto LABEL_75;
        }
        v2->mode = TYPE;
LABEL_64:
        mode = v2->mode;
        if ( v2->mode <= (unsigned int)DONE )
          continue;
        goto LABEL_5;
      case DRY:
        v46 = z;
LABEL_75:
        inflate_flush(v46, v2);
        if ( v2->read == v2->write )
        {
          v2->mode = DONE;
          v46->error = Z_STREAM_END;
        }
        else
        {
          inflate_error = "Inflate data: read != write in DRY";
        }
        goto LABEL_79;
      case DONE:
        v46 = z;
        z->error = Z_STREAM_END;
LABEL_79:
        inflate_flush(v46, v2);
        return;
      default:
LABEL_5:
        v7 = z;
        z->error = Z_DATA_ERROR;
        inflate_flush(v7, v2);
        return;
    }
    break;
  }
  while ( 1 )
  {
    bb = v2->trees.bb;
    if ( !getbits(v18, v2, bb) )
      break;
    v29 = v2->bitb & inflate_mask[bb];
    tb = v2->trees.tb;
    Bits = tb[v29].Bits;
    s = (inflate_blocks_state_s *)tb[v29].base;
    v31 = s;
    if ( (unsigned int)s >= 0x10 )
    {
      if ( s == (inflate_blocks_state_s *)18 )
        v34 = 7;
      else
        v34 = (int)&s[-1].end + 2;
      if ( !getbits(v18, v2, v34 + Bits) )
        return;
      v2->bitk -= Bits;
      v2->bitb >>= Bits;
      v35 = v2->bitb;
      v36 = v35 & inflate_mask[v34];
      v37 = s == (inflate_blocks_state_s *)18;
      v2->bitk -= v34;
      v38 = 8 * v37 + 3 + v36;
      v39 = (v2->left >> 5) & 0x1F;
      v40 = v2->left & 0x1F;
      v2->bitb = v35 >> v34;
      index = v2->trees.index;
      if ( v38 + index > v39 + v40 + 258 )
      {
LABEL_70:
        Mem_Free(v2->trees.blens);
        v2->mode = BAD;
        inflate_error = "Inflate data: Invalid bit length repeat";
        v18->error = Z_DATA_ERROR;
LABEL_71:
        inflate_flush(v18, v2);
        return;
      }
      if ( s == (inflate_blocks_state_s *)16 )
      {
        if ( !index )
          goto LABEL_70;
        v42 = v2->trees.blens[index - 1];
      }
      else
      {
        v42 = 0;
      }
      do
      {
        v2->trees.blens[index++] = v42;
        --v38;
      }
      while ( v38 );
      v2->trees.index = index;
    }
    else
    {
      v33 = v2->trees.index;
      v2->bitk -= Bits;
      v2->bitb >>= Bits;
      v2->trees.blens[v33] = (unsigned int)v31;
      ++v2->trees.index;
    }
    if ( v2->trees.index >= ((v2->left >> 5) & 0x1F) + (v2->left & 0x1F) + 258 )
    {
LABEL_55:
      v43 = v2->left;
      v44 = v2->hufts;
      v55 = v18;
      v45 = v2->trees.blens;
      v2->trees.tb = 0;
      s = (inflate_blocks_state_s *)9;
      bd = 6;
      inflate_trees_dynamic(
        (v43 & 0x1F) + 257,
        v45,
        &lengthTree,
        v44,
        v55,
        ((v43 >> 5) & 0x1F) + 1,
        (unsigned int *)&s,
        &bd,
        &distTree);
      Mem_Free(v2->trees.blens);
      v46 = z;
      if ( z->error == Z_OK )
      {
        v47 = Mem_Alloc(28, 2u);
        v48 = bd;
        v47[16] = (_BYTE)s;
        v49 = lengthTree;
        v47[17] = v48;
        v50 = distTree;
        *(_DWORD *)v47 = 0;
        *((_DWORD *)v47 + 5) = v49;
        *((_DWORD *)v47 + 6) = v50;
        v2->left = (unsigned int)v47;
        v2->mode = CODES;
        goto LABEL_58;
      }
      v54 = z;
      v2->mode = BAD;
      inflate_flush(v54, v2);
      return;
    }
  }
}

// FUNC: _inflateEnd
EStatus __cdecl inflateEnd(z_stream_s *z)
{
  inflate_blocks_state_s *blocks; // esi

  blocks = z->istate->blocks;
  if ( blocks )
  {
    inflate_blocks_reset(blocks, z);
    Mem_Free(blocks->hufts);
    blocks->hufts = 0;
    Mem_Free(blocks);
    z->istate->blocks = 0;
  }
  if ( z->istate )
  {
    Mem_Free(z->istate);
    z->istate = 0;
  }
  return 0;
}

// FUNC: _inflateInit
EStatus __cdecl inflateInit(z_stream_s *z, EFlush flush, int noWrap)
{
  inflate_state_s *v3; // eax
  inflate_blocks_state_s *v4; // esi
  inflate_state_s *istate; // eax

  inflate_error = "OK";
  v3 = (inflate_state_s *)Mem_Alloc(28, 2u);
  z->istate = v3;
  v3->blocks = 0;
  z->istate->nowrap = noWrap;
  z->istate->wbits = 15;
  v4 = (inflate_blocks_state_s *)Mem_Alloc(32824, 2u);
  v4->hufts = (inflate_huft_s *)Mem_Alloc(11520, 2u);
  v4->end = (unsigned __int8 *)&v4->end;
  v4->mode = TYPE;
  inflate_blocks_reset(v4, z);
  z->istate->blocks = v4;
  z->status = Z_OK;
  if ( flush == Z_FINISH )
    z->status = Z_BUF_ERROR;
  z->istate->mode = imMETHOD;
  istate = z->istate;
  if ( istate->nowrap )
    istate->mode = imDICT4;
  inflate_blocks_reset(z->istate->blocks, z);
  return 0;
}

// FUNC: _inflate
EStatus __cdecl inflate(z_stream_s *z)
{
  inflate_mode mode; // eax
  inflate_state_s *istate; // ecx
  unsigned int avail_in; // ecx
  unsigned __int8 *next_in; // eax
  int v5; // edx
  inflate_state_s *v6; // ecx
  EStatus error; // eax
  inflate_blocks_state_s *blocks; // edi
  inflate_state_s *v9; // eax
  inflate_state_s *v10; // eax
  inflate_state_s *v11; // eax
  inflate_state_s *v12; // eax
  EStatus result; // eax

  mode = z->istate->mode;
  while ( 2 )
  {
    switch ( mode )
    {
      case imMETHOD:
        if ( !z->avail_in )
          return z->status;
        z->istate->method = *z->next_in++;
        --z->avail_in;
        ++z->total_in;
        istate = z->istate;
        if ( (istate->method & 0xF) == 8 )
        {
          if ( (istate->method >> 4) + 8 <= istate->wbits )
          {
            istate->mode = imFLAG;
            goto LABEL_28;
          }
          result = Z_DATA_ERROR;
          z->istate->mode = imCHECK4;
          inflate_error = "Inflate data: Invalid window size";
        }
        else
        {
          z->istate->mode = imCHECK4;
          result = Z_DATA_ERROR;
          inflate_error = "Inflate data: Unknown compression method";
        }
        return result;
      case imFLAG:
        avail_in = z->avail_in;
        if ( !avail_in )
          return z->status;
        next_in = z->next_in;
        v5 = *z->next_in;
        ++z->total_in;
        z->next_in = next_in + 1;
        z->avail_in = avail_in - 1;
        v6 = z->istate;
        if ( !((v5 + (v6->method << 8)) % 0x1F) )
        {
          v6->mode = imDICT4;
          goto LABEL_28;
        }
        result = Z_DATA_ERROR;
        z->istate->mode = imCHECK4;
        inflate_error = "Inflate data: Incorrect header check";
        return result;
      case imDICT4:
        inflate_blocks(z->istate->blocks, z);
        error = z->error;
        if ( error == Z_DATA_ERROR )
        {
          z->istate->mode = imCHECK4;
          return -1;
        }
        if ( error != Z_STREAM_END )
          return z->status;
        z->istate->calcadler = z->istate->adler;
        blocks = z->istate->blocks;
        if ( blocks->mode == BTREE || blocks->mode == DTREE )
          Mem_Free(blocks->trees.blens);
        if ( blocks->mode == CODES )
          Mem_Free(blocks->decode.codes);
        blocks->mode = TYPE;
        blocks->bitk = 0;
        blocks->bitb = 0;
        blocks->write = blocks->window;
        blocks->read = blocks->window;
        z->istate->adler = 1;
        z->istate->mode = 4 * (z->istate->nowrap != 0) + 3;
        goto LABEL_28;
      case imDICT3:
        if ( !z->avail_in )
          return z->status;
        z->istate->adler = *z->next_in++ << 24;
        --z->avail_in;
        v9 = z->istate;
        ++z->total_in;
        v9->mode = imDICT2;
        goto LABEL_28;
      case imDICT2:
        if ( !z->avail_in )
          return z->status;
        z->istate->adler += *z->next_in++ << 16;
        --z->avail_in;
        v10 = z->istate;
        ++z->total_in;
        v10->mode = imDICT1;
        goto LABEL_28;
      case imDICT1:
        if ( !z->avail_in )
          return z->status;
        z->istate->adler += *z->next_in++ << 8;
        --z->avail_in;
        v11 = z->istate;
        ++z->total_in;
        v11->mode = imDICT0;
        goto LABEL_28;
      case imDICT0:
        if ( z->avail_in )
        {
          z->istate->adler += *z->next_in;
          v12 = z->istate;
          ++z->next_in;
          --z->avail_in;
          ++z->total_in;
          if ( v12->calcadler == v12->adler )
          {
            v12->mode = imBLOCKS;
          }
          else
          {
            inflate_error = "Inflate data: Failed Adler checksum";
            v12->mode = imCHECK4;
          }
LABEL_28:
          mode = z->istate->mode;
          if ( (unsigned int)mode > imCHECK4 )
            return -3;
          continue;
        }
        return z->status;
      case imBLOCKS:
        return 1;
      case imCHECK4:
        return -1;
      default:
        return -3;
    }
  }
}
