
// FUNC: void __cdecl lwListAdd(void * *,void *)
void __cdecl lwListAdd(void **list, _DWORD *node)
{
  _DWORD *v2; // eax
  _DWORD *v3; // ecx

  v2 = *list;
  if ( *list )
  {
    do
    {
      v3 = v2;
      v2 = (_DWORD *)*v2;
    }
    while ( v2 );
    *v3 = node;
    node[1] = v3;
  }
  else
  {
    *list = node;
  }
}

// FUNC: void __cdecl lwListInsert(void * *,void *,int (__cdecl *)(void *,void *))
void __cdecl lwListInsert(void **vlist, _DWORD *vitem, int (__cdecl *compare)(void *, void *))
{
  _DWORD *v3; // esi
  _DWORD *v4; // ebx

  v3 = *vlist;
  if ( *vlist )
  {
    v4 = 0;
    do
    {
      if ( compare(v3, vitem) > 0 )
        break;
      v4 = v3;
      v3 = (_DWORD *)*v3;
    }
    while ( v3 );
    if ( v4 )
    {
      if ( v3 )
      {
        *vitem = v3;
        vitem[1] = v4;
        *v4 = vitem;
        v3[1] = vitem;
      }
      else
      {
        *v4 = vitem;
        vitem[1] = v4;
      }
    }
    else
    {
      *vlist = vitem;
      v3[1] = vitem;
      *vitem = v3;
    }
  }
  else
  {
    *vlist = vitem;
  }
}

// FUNC: void * __cdecl getbytes(class idFile *,int)
void *__cdecl getbytes(idFile *fp, int size)
{
  void *result; // eax
  void *v3; // esi

  if ( flen == -9999 )
    return 0;
  if ( size >= 0 )
  {
    result = Mem_ClearedAlloc(size, 0xEu);
    v3 = result;
    if ( result )
    {
      if ( size == fp->Read(fp, result, size) )
      {
        flen += size;
        return v3;
      }
      else
      {
        flen = -9999;
        Mem_Free(v3);
        return 0;
      }
    }
    else
    {
      flen = -9999;
    }
  }
  else
  {
    flen = -9999;
    return 0;
  }
  return result;
}

// FUNC: unsigned short __cdecl getU2(class idFile *)
// local variable allocation has failed, the output may be wrong!
unsigned __int16 __cdecl getU2(idFile *fp)
{
  int v1; // ecx
  unsigned __int16 result; // ax
  int i; // [esp+8h] [ebp-4h] OVERLAPPED BYREF

  i = v1;
  if ( flen == -9999 )
    return 0;
  if ( fp->Read(fp, &i, 2) != 2 )
  {
    flen = -9999;
    return 0;
  }
  BigRevBytes(&i, 2, 1);
  result = i;
  flen += 2;
  return result;
}

// FUNC: unsigned int __cdecl getU4(class idFile *)
unsigned int __cdecl getU4(idFile *fp)
{
  unsigned int v1; // ecx
  unsigned int result; // eax
  unsigned int i; // [esp+8h] [ebp-4h] BYREF

  i = v1;
  if ( flen == -9999 )
    return 0;
  if ( fp->Read(fp, &i, 4) != 4 )
  {
    flen = -9999;
    return 0;
  }
  BigRevBytes(&i, 4, 1);
  result = i;
  flen += 4;
  return result;
}

// FUNC: unsigned char __cdecl getU1(class idFile *)
unsigned __int8 __cdecl getU1(idFile *fp)
{
  int v1; // ecx
  idFile_vtbl *v2; // eax
  int c; // [esp+8h] [ebp-4h] BYREF

  c = v1;
  if ( flen == -9999 )
    return 0;
  v2 = fp->__vftable;
  c = 0;
  if ( v2->Read(fp, &c, 1) < 0 )
  {
    flen = -9999;
    return 0;
  }
  ++flen;
  return c;
}

// FUNC: int __cdecl getVX(class idFile *)
int __cdecl getVX(idFile *fp)
{
  int v1; // ecx
  idFile_vtbl *v3; // eax
  unsigned __int8 v4; // al
  bool v5; // zf
  unsigned __int16 v6; // dx
  int v7; // edi
  idFile_vtbl *v8; // edx
  int v9; // edi
  idFile_vtbl *v10; // edx
  unsigned __int16 v11; // cx
  int v12; // edi
  unsigned __int8 c; // [esp+21h] [ebp-1h] BYREF

  c = HIBYTE(v1);
  if ( flen == -9999 )
    return 0;
  v3 = fp->__vftable;
  c = 0;
  if ( v3->Read(fp, &c, 1) == -1 )
    return 0;
  v4 = c;
  v5 = c == 0xFF;
  c = 0;
  if ( v5 )
  {
    if ( fp->Read(fp, &c, 1) == -1 )
      return 0;
    v8 = fp->__vftable;
    v9 = c << 16;
    c = 0;
    if ( v8->Read(fp, &c, 1) == -1 )
      return 0;
    v10 = fp->__vftable;
    LOBYTE(v11) = 0;
    HIBYTE(v11) = c;
    c = 0;
    v12 = v11 | v9;
    if ( v10->Read(fp, &c, 1) == -1 )
      return 0;
    flen += 4;
    return c | v12;
  }
  else
  {
    LOBYTE(v6) = 0;
    HIBYTE(v6) = v4;
    v7 = v6;
    if ( fp->Read(fp, &c, 1) == -1 )
      return 0;
    flen += 2;
    return c | v7;
  }
}

// FUNC: float __cdecl getF4(class idFile *)
double __cdecl getF4(idFile *fp)
{
  float v1; // ecx
  float f; // [esp+8h] [ebp-4h] BYREF

  f = v1;
  if ( flen == -9999 )
    return 0.0;
  if ( fp->Read(fp, &f, 4) != 4 )
  {
    flen = -9999;
    return 0.0;
  }
  BigRevBytes(&f, 4, 1);
  flen += 4;
  if ( (LODWORD(f) & 0x7F800000) != 0 || (LODWORD(f) & 0x7FFFFF) == 0 )
    return f;
  else
    return 0.0;
}

// FUNC: char * __cdecl getS0(class idFile *)
char *__cdecl getS0(idFile *fp)
{
  int v2; // eax
  idFile_vtbl *v3; // edx
  int v4; // edi
  int v5; // ebx
  idFile_vtbl *v6; // edx
  int v7; // edi
  void *v8; // ebx
  int c; // [esp+8h] [ebp-8h] BYREF
  int pos; // [esp+Ch] [ebp-4h]

  if ( flen == -9999 )
    return 0;
  v2 = fp->Tell(fp);
  v3 = fp->__vftable;
  v4 = v2;
  v5 = 1;
  pos = v2;
  c = 0;
  if ( v3->Read(fp, &c, 1) == -1 )
    goto LABEL_6;
  while ( c )
  {
    v6 = fp->__vftable;
    ++v5;
    c = 0;
    if ( v6->Read(fp, &c, 1) == -1 )
      goto LABEL_6;
  }
  if ( v5 != 1 )
  {
    v7 = v5 + (v5 & 1);
    v8 = Mem_ClearedAlloc(v7, 0xEu);
    if ( v8 && !fp->Seek(fp, pos, FS_SEEK_SET) && v7 == fp->Read(fp, v8, v7) )
    {
      flen += v7;
      return (char *)v8;
    }
LABEL_6:
    flen = -9999;
    return 0;
  }
  if ( fp->Seek(fp, v4 + 2, FS_SEEK_SET) )
    flen = -9999;
  else
    flen += 2;
  return 0;
}

// FUNC: unsigned int __cdecl sgetU4(unsigned char * *)
unsigned int __cdecl sgetU4(unsigned __int8 **bp)
{
  unsigned int v1; // ecx
  unsigned int result; // eax
  unsigned int i; // [esp+0h] [ebp-4h] BYREF

  i = v1;
  if ( flen == -9999 )
    return 0;
  i = *(_DWORD *)*bp;
  BigRevBytes(&i, 4, 1);
  flen += 4;
  result = i;
  *bp += 4;
  return result;
}

// FUNC: int __cdecl sgetVX(unsigned char * *)
int __cdecl sgetVX(unsigned __int8 **bp)
{
  _BYTE *v1; // ecx
  char v3; // al
  unsigned __int16 v4; // dx
  unsigned __int8 *v5; // ecx
  int v6; // edx
  unsigned __int16 v7; // ax
  unsigned __int8 *v8; // ecx

  v1 = *bp;
  if ( flen == -9999 )
    return 0;
  v3 = *v1;
  if ( *v1 == 0xFF )
  {
    v6 = (unsigned __int8)v1[3];
    flen += 4;
    HIBYTE(v7) = v1[1];
    v8 = v1 + 4;
    LOBYTE(v7) = *(v8 - 2);
    *bp = v8;
    return v6 | (v7 << 8);
  }
  else
  {
    flen += 2;
    HIBYTE(v4) = v3;
    v5 = v1 + 2;
    LOBYTE(v4) = *(v5 - 1);
    *bp = v5;
    return v4;
  }
}

// FUNC: char * __cdecl sgetS0(unsigned char * *)
char *__cdecl sgetS0(unsigned __int8 **bp)
{
  unsigned __int8 *v1; // esi
  char *result; // eax
  unsigned int v3; // eax
  int v4; // ebx

  v1 = *bp;
  if ( flen == -9999 )
    return 0;
  v3 = strlen((const char *)*bp);
  if ( v3 )
  {
    v4 = (((_BYTE)v3 + 1) & 1) + v3 + 1;
    result = (char *)Mem_ClearedAlloc(v4, 0xEu);
    if ( result )
    {
      flen += v4;
      qmemcpy(result, v1, v4);
      *bp += v4;
    }
    else
    {
      flen = -9999;
    }
  }
  else
  {
    flen += 2;
    *bp = v1 + 2;
    return 0;
  }
  return result;
}

// FUNC: void __cdecl lwFreePoints(struct st_lwPointList *)
void __cdecl lwFreePoints(st_lwPointList *point)
{
  int v1; // ebx
  int v2; // edi
  st_lwPoint *pt; // ecx

  if ( point )
  {
    if ( point->pt )
    {
      v1 = 0;
      if ( point->count > 0 )
      {
        v2 = 0;
        do
        {
          if ( point->pt[v2].pol )
            Mem_Free(point->pt[v2].pol);
          pt = point->pt;
          if ( pt[v2].vm )
            Mem_Free(pt[v2].vm);
          ++v1;
          ++v2;
        }
        while ( v1 < point->count );
      }
      Mem_Free(point->pt);
    }
    point->count = 0;
    point->offset = 0;
    point->pt = 0;
  }
}

// FUNC: void __cdecl lwFreePolygons(struct st_lwPolygonList *)
void __cdecl lwFreePolygons(st_lwPolygonList *plist)
{
  int v2; // esi
  st_lwPolygon *pol; // eax
  bool v4; // cc
  int v5; // edi
  int v6; // ebx
  st_lwVMapPt *vm; // eax
  st_lwPolygon *v8; // ecx
  st_lwPolygonList *plista; // [esp+Ch] [ebp+4h]

  v2 = 0;
  if ( plist )
  {
    pol = plist->pol;
    if ( pol )
    {
      v4 = plist->count <= 0;
      plista = 0;
      if ( !v4 )
      {
        do
        {
          if ( pol[v2].v )
          {
            v5 = 0;
            if ( pol[v2].nverts > 0 )
            {
              v6 = 0;
              do
              {
                vm = pol[v2].v[v6].vm;
                if ( vm )
                  Mem_Free(vm);
                pol = plist->pol;
                ++v5;
                ++v6;
              }
              while ( v5 < pol[v2].nverts );
            }
          }
          ++v2;
          plista = (st_lwPolygonList *)((char *)plista + 1);
        }
        while ( (int)plista < plist->count );
      }
      v8 = plist->pol;
      if ( v8->v )
        Mem_Free(v8->v);
      Mem_Free(plist->pol);
    }
    plist->count = 0;
    plist->offset = 0;
    plist->vcount = 0;
    plist->voffset = 0;
    plist->pol = 0;
  }
}

// FUNC: int __cdecl lwGetPoints(class idFile *,int,struct st_lwPointList *)
int __cdecl lwGetPoints(idFile *fp, int cksize, int point)
{
  int v3; // esi
  int v5; // eax
  int v6; // ebp
  int v7; // eax
  st_lwPoint *v8; // edi
  st_lwPoint *v9; // eax
  float *v10; // eax
  float *v11; // esi
  int v12; // edx
  int v13; // ecx
  float *v14; // eax
  unsigned int v15; // edx
  int v16; // eax
  float *v17; // ecx
  int v18; // ebp
  int i; // [esp+4h] [ebp-8h]
  float *f; // [esp+8h] [ebp-4h]
  int cksizea; // [esp+14h] [ebp+8h]

  v3 = cksize;
  if ( cksize == 1 )
    return 1;
  v5 = *(_DWORD *)point;
  v6 = cksize / 12;
  *(_DWORD *)(point + 4) = *(_DWORD *)point;
  v7 = cksize / 12 + v5;
  v8 = *(st_lwPoint **)(point + 8);
  *(_DWORD *)point = v7;
  v9 = (st_lwPoint *)Mem_Alloc(28 * v7, 0xEu);
  *(_DWORD *)(point + 8) = v9;
  if ( !v9 )
    return 0;
  if ( v8 )
  {
    qmemcpy(v9, v8, 28 * *(_DWORD *)(point + 4));
    Mem_Free(v8);
    v3 = cksize;
  }
  memset((void *)(*(_DWORD *)(point + 8) + 28 * *(_DWORD *)(point + 4)), 0, 4 * ((unsigned int)(28 * v6) >> 2));
  v10 = (float *)getbytes(fp, v3);
  v11 = v10;
  f = v10;
  if ( !v10 )
    return 0;
  BigRevBytes(v10, 4, 3 * v6);
  v12 = 0;
  v13 = 0;
  if ( v6 >= 4 )
  {
    v14 = v11 + 2;
    v15 = ((unsigned int)(v6 - 4) >> 2) + 1;
    i = 4 * v15;
    cksizea = 12 * v15;
    do
    {
      *(float *)(v13 + *(_DWORD *)(point + 8)) = *(v14 - 2);
      *(float *)(*(_DWORD *)(point + 8) + v13 + 4) = *(v14 - 1);
      *(float *)(*(_DWORD *)(point + 8) + v13 + 8) = *v14;
      *(float *)(*(_DWORD *)(point + 8) + v13 + 28) = v14[1];
      *(float *)(*(_DWORD *)(point + 8) + v13 + 32) = v14[2];
      *(float *)(*(_DWORD *)(point + 8) + v13 + 36) = v14[3];
      *(float *)(*(_DWORD *)(point + 8) + v13 + 56) = v14[4];
      *(float *)(*(_DWORD *)(point + 8) + v13 + 60) = v14[5];
      *(float *)(*(_DWORD *)(point + 8) + v13 + 64) = v14[6];
      *(float *)(v13 + *(_DWORD *)(point + 8) + 84) = v14[7];
      *(float *)(*(_DWORD *)(point + 8) + v13 + 88) = v14[8];
      *(float *)(*(_DWORD *)(point + 8) + v13 + 92) = v14[9];
      v14 += 12;
      v13 += 112;
      --v15;
    }
    while ( v15 );
    v13 = cksizea;
    v12 = i;
    v11 = f;
  }
  if ( v12 < v6 )
  {
    v16 = 28 * v12;
    v17 = &v11[v13 + 2];
    v18 = v6 - v12;
    do
    {
      *(float *)(v16 + *(_DWORD *)(point + 8)) = *(v17 - 2);
      *(float *)(*(_DWORD *)(point + 8) + v16 + 4) = *(v17 - 1);
      *(float *)(*(_DWORD *)(point + 8) + v16 + 8) = *v17;
      v17 += 3;
      v16 += 28;
      --v18;
    }
    while ( v18 );
  }
  Mem_Free(v11);
  return 1;
}

// FUNC: void __cdecl lwGetBoundingBox(struct st_lwPointList *,float * const)
void __cdecl lwGetBoundingBox(st_lwPointList *point, float *bbox)
{
  int v2; // edx
  int v3; // ebx
  int v4; // edx
  st_lwPoint *v5; // edi
  st_lwPoint *v6; // edi
  float *v7; // edi
  float *v8; // edi
  float *v9; // edi
  float *v10; // edi

  if ( point->count )
  {
    v2 = 0;
    while ( bbox[v2] == 0.0 )
    {
      if ( ++v2 >= 6 )
      {
        bbox[2] = 1.0e20;
        bbox[1] = 1.0e20;
        *bbox = 1.0e20;
        v3 = 0;
        bbox[5] = -1.0e20;
        bbox[4] = -1.0e20;
        bbox[3] = -1.0e20;
        if ( point->count > 0 )
        {
          v4 = 0;
          do
          {
            v5 = &point->pt[v4];
            if ( *bbox > (double)v5->pos[0] )
              *bbox = v5->pos[0];
            v6 = &point->pt[v4];
            if ( bbox[3] < (double)v6->pos[0] )
              bbox[3] = v6->pos[0];
            v7 = &point->pt[v4].pos[1];
            if ( bbox[1] > (double)*v7 )
              bbox[1] = *v7;
            v8 = &point->pt[v4].pos[1];
            if ( bbox[4] < (double)*v8 )
              bbox[4] = *v8;
            v9 = &point->pt[v4].pos[2];
            if ( bbox[2] > (double)*v9 )
              bbox[2] = *v9;
            v10 = &point->pt[v4].pos[2];
            if ( bbox[5] < (double)*v10 )
              bbox[5] = *v10;
            ++v3;
            ++v4;
          }
          while ( v3 < point->count );
        }
        return;
      }
    }
  }
}

// FUNC: int __cdecl lwAllocPolygons(struct st_lwPolygonList *,int,int)
int __cdecl lwAllocPolygons(st_lwPolygonList *plist, st_lwPolygon *npols, int nverts)
{
  int count; // eax
  int v4; // eax
  st_lwPolygon *pol; // esi
  int result; // eax
  int v7; // esi
  int vcount; // eax
  st_lwPolygon *v9; // ecx
  int v10; // eax
  st_lwPolVert *v; // ebp
  st_lwPolVert *v12; // edi
  int v13; // edx
  int v14; // esi

  count = plist->count;
  plist->offset = plist->count;
  v4 = (int)npols + count;
  plist->count = v4;
  pol = plist->pol;
  result = (int)Mem_Alloc(40 * v4, 0xEu);
  plist->pol = (st_lwPolygon *)result;
  if ( result )
  {
    if ( pol )
    {
      qmemcpy((void *)result, pol, 40 * plist->offset);
      Mem_Free(pol);
    }
    v7 = nverts;
    memset(&plist->pol[plist->offset], 0, 4 * ((unsigned int)(40 * (_DWORD)npols) >> 2));
    vcount = plist->vcount;
    v9 = plist->pol;
    plist->voffset = vcount;
    v10 = nverts + vcount;
    plist->vcount = v10;
    v = v9->v;
    plist->pol->v = (st_lwPolVert *)Mem_Alloc(24 * v10, 0xEu);
    v12 = plist->pol->v;
    if ( v12 )
    {
      if ( v )
      {
        qmemcpy(v12, v, 24 * plist->voffset);
        Mem_Free(v);
        v7 = nverts;
      }
      memset(&plist->pol->v[plist->voffset], 0, 4 * ((unsigned int)(24 * v7) >> 2));
      v13 = 1;
      if ( plist->offset > 1 )
      {
        v14 = 1;
        do
        {
          ++v13;
          plist->pol[v14].v = &plist->pol[v14 - 1].v[plist->pol[v14 - 1].nverts];
          ++v14;
        }
        while ( v13 < plist->offset );
      }
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// FUNC: int __cdecl lwGetPolygons(class idFile *,int,struct st_lwPolygonList *,int)
int __cdecl lwGetPolygons(idFile *fp, int cksize, st_lwPolVert *plist, int ptoffset)
{
  int v4; // ebp
  unsigned __int8 *v6; // eax
  int v7; // edx
  unsigned __int8 *v8; // ebx
  st_lwPolygon *i; // edi
  unsigned __int8 *v10; // ecx
  unsigned __int8 *v11; // esi
  __int16 v12; // ax
  int v13; // eax
  st_lwPolygonList *v14; // ebp
  st_lwPolygon *nvmaps; // ecx
  unsigned __int8 *v16; // eax
  int v17; // edx
  _DWORD *p_v; // esi
  unsigned __int8 *v19; // ecx
  __int16 v20; // cx
  __int16 v21; // bx
  int v22; // edi
  bool v23; // zf
  int v24; // ebp
  int v25; // ecx
  unsigned __int16 v26; // bx
  unsigned __int16 v27; // cx
  int v28; // [esp-Ch] [ebp-24h]
  int v29; // [esp+8h] [ebp-10h]
  unsigned __int8 *buf; // [esp+Ch] [ebp-Ch]
  st_lwPolygon *v31; // [esp+10h] [ebp-8h]
  unsigned int type; // [esp+14h] [ebp-4h]
  unsigned int cksizea; // [esp+20h] [ebp+8h]
  int cksizeb; // [esp+20h] [ebp+8h]

  v4 = 0;
  if ( !cksize )
    return 1;
  flen = 0;
  type = getU4(fp);
  v6 = (unsigned __int8 *)getbytes(fp, cksize - 4);
  v7 = flen;
  v8 = v6;
  buf = v6;
  if ( cksize == flen )
  {
    i = 0;
    v10 = v6;
    cksizea = (unsigned int)&v6[cksize - 4];
    if ( (unsigned int)v6 < cksizea )
    {
      do
      {
        v11 = v10;
        if ( v7 == -9999 )
        {
          v12 = 0;
        }
        else
        {
          v7 += 2;
          v10 += 2;
          HIBYTE(v12) = *v11;
          LOBYTE(v12) = v11[1];
        }
        v13 = v12 & 0x3FF;
        v4 += v13;
        for ( i = (st_lwPolygon *)((char *)i + 1); v13; --v13 )
        {
          if ( v7 != -9999 )
          {
            if ( *v10 == 0xFF )
            {
              v7 += 4;
              v10 += 4;
            }
            else
            {
              v7 += 2;
              v10 += 2;
            }
          }
        }
      }
      while ( (unsigned int)v10 < cksizea );
      flen = v7;
    }
    v28 = v4;
    v14 = (st_lwPolygonList *)plist;
    if ( lwAllocPolygons((st_lwPolygonList *)plist, i, v28) )
    {
      nvmaps = (st_lwPolygon *)plist->nvmaps;
      v16 = v8;
      cksizeb = (int)&nvmaps->v[LODWORD(plist->norm[2])];
      if ( (int)i > 0 )
      {
        v17 = flen;
        p_v = &nvmaps[LODWORD(plist->norm[0])].v;
        v31 = i;
        do
        {
          v19 = v16;
          if ( v17 == -9999 )
          {
            v20 = 0;
          }
          else
          {
            v17 += 2;
            v16 += 2;
            HIBYTE(v21) = *v19;
            LOBYTE(v21) = v19[1];
            v20 = v21;
            v8 = buf;
          }
          v22 = v20 & 0x3FF;
          v23 = *p_v == 0;
          *(p_v - 6) = v20 & 0xFC00;
          *(p_v - 1) = v22;
          *(p_v - 5) = type;
          if ( v23 )
            *p_v = cksizeb;
          if ( (v20 & 0x3FF) != 0 )
          {
            v24 = 0;
            v29 = v20 & 0x3FF;
            do
            {
              if ( v17 == -9999 )
              {
                v25 = 0;
              }
              else if ( *v16 == 0xFF )
              {
                HIBYTE(v27) = v16[1];
                v17 += 4;
                LOBYTE(v27) = v16[2];
                v25 = v16[3] | (v27 << 8);
                v16 += 4;
              }
              else
              {
                HIBYTE(v26) = *v16;
                v17 += 2;
                v16 += 2;
                LOBYTE(v26) = *(v16 - 1);
                v25 = v26;
              }
              *(_DWORD *)(*p_v + v24) = ptoffset + v25;
              v24 += 24;
              --v29;
            }
            while ( v29 );
            v8 = buf;
          }
          p_v += 10;
          v23 = v31 == (st_lwPolygon *)1;
          v31 = (st_lwPolygon *)((char *)v31 - 1);
          cksizeb += 24 * v22;
        }
        while ( !v23 );
        flen = v17;
      }
      Mem_Free(v8);
      return 1;
    }
  }
  else
  {
    v14 = (st_lwPolygonList *)plist;
  }
  if ( v8 )
    Mem_Free(v8);
  lwFreePolygons(v14);
  return 0;
}

// FUNC: int __cdecl lwGetPointPolygons(struct st_lwPointList *,struct st_lwPolygonList *)
int __cdecl lwGetPointPolygons(st_lwPointList *point, st_lwPolygonList *polygon)
{
  int v4; // ecx
  st_lwPolygon *pol; // eax
  int v6; // edx
  int v7; // ebx
  int index; // ebp
  int v9; // ebp
  int v10; // ebx
  int npols; // eax
  st_lwPoint *pt; // edx
  st_lwPointList *v13; // ebp
  st_lwPolygon *v14; // ecx
  int v15; // edx
  char *v16; // eax
  int v17; // eax
  bool v18; // cc
  int i; // [esp+10h] [ebp-4h]
  int ia; // [esp+10h] [ebp-4h]
  st_lwPointList *pointa; // [esp+18h] [ebp+4h]
  st_lwPolygonList *polygona; // [esp+1Ch] [ebp+8h]

  v4 = 0;
  i = 0;
  if ( polygon->count > 0 )
  {
    pol = polygon->pol;
    do
    {
      v6 = 0;
      if ( pol[v4].nverts > 0 )
      {
        v7 = 0;
        do
        {
          index = polygon->pol[v4].v[v7].index;
          ++point->pt[index].npols;
          pol = polygon->pol;
          ++v6;
          ++v7;
        }
        while ( v6 < pol[v4].nverts );
      }
      ++v4;
      ++i;
    }
    while ( i < polygon->count );
  }
  v9 = 0;
  if ( point->count > 0 )
  {
    v10 = 0;
    do
    {
      npols = point->pt[v10].npols;
      if ( npols )
      {
        point->pt[v10].pol = (int *)Mem_ClearedAlloc(4 * npols, 0xEu);
        pt = point->pt;
        if ( !pt[v10].pol )
          return 0;
        pt[v10].npols = 0;
      }
      ++v9;
      ++v10;
    }
    while ( v9 < point->count );
  }
  v13 = 0;
  ia = 0;
  if ( polygon->count > 0 )
  {
    v14 = polygon->pol;
    pointa = 0;
    do
    {
      v15 = 0;
      v16 = (char *)v13 + (_DWORD)v14;
      polygona = 0;
      if ( *(int *)((char *)&v13[2].pt + (_DWORD)v14) > 0 )
      {
        do
        {
          v17 = *(_DWORD *)(v15 + *((_DWORD *)v16 + 9));
          point->pt[v17].pol[point->pt[v17].npols++] = ia;
          v13 = pointa;
          v14 = polygon->pol;
          v16 = (char *)pointa + (_DWORD)v14;
          v15 += 24;
          polygona = (st_lwPolygonList *)((char *)polygona + 1);
        }
        while ( (int)polygona < *(int *)((char *)&pointa[2].pt + (_DWORD)v14) );
      }
      v13 = (st_lwPointList *)((char *)v13 + 40);
      v18 = ++ia < polygon->count;
      pointa = v13;
    }
    while ( v18 );
  }
  return 1;
}

// FUNC: void __cdecl lwFreeTags(struct st_lwTagList *)
void __cdecl lwFreeTags(st_lwTagList *tlist)
{
  int i; // edi

  if ( tlist )
  {
    if ( tlist->tag )
    {
      for ( i = 0; i < tlist->count; ++i )
      {
        if ( tlist->tag[i] )
          Mem_Free(tlist->tag[i]);
      }
      Mem_Free(tlist->tag);
    }
    tlist->count = 0;
    tlist->offset = 0;
    tlist->tag = 0;
  }
}

// FUNC: int __cdecl lwGetTags(class idFile *,int,struct st_lwTagList *)
int __cdecl lwGetTags(idFile *fp, char **cksize, st_lwTagList *tlist)
{
  int v3; // edi
  int v4; // ebp
  char *v6; // eax
  char *v7; // esi
  const char *v8; // edi
  const char *i; // ecx
  unsigned int v10; // eax
  st_lwTagList *v11; // ebx
  int count; // eax
  char **tag; // edi
  int v14; // eax
  char **v15; // eax
  char **v16; // esi
  char **v17; // edi
  char **v18; // eax
  int v19; // edi
  char *v20; // eax
  int v21; // ecx
  char *buf; // [esp+8h] [ebp-4h]

  v3 = (int)cksize;
  v4 = 0;
  if ( !cksize )
    return 1;
  flen = 0;
  v6 = (char *)getbytes(fp, (int)cksize);
  v7 = v6;
  buf = v6;
  if ( !v6 )
    return 0;
  v8 = &v6[v3];
  for ( i = v6; i < v8; ++v4 )
  {
    v10 = (unsigned int)&i[strlen(i) + 1];
    i = (const char *)(v10 + (((_BYTE)v10 - (_BYTE)i) & 1));
  }
  v11 = tlist;
  count = tlist->count;
  tag = tlist->tag;
  tlist->offset = tlist->count;
  v14 = v4 + count;
  v11->count = v14;
  cksize = tag;
  v15 = (char **)Mem_Alloc(4 * v14, 0xEu);
  v11->tag = v15;
  if ( v15 )
  {
    if ( tag )
    {
      v16 = tag;
      v17 = v15;
      v18 = cksize;
      qmemcpy(v17, v16, 4 * v11->offset);
      Mem_Free(v18);
      v7 = buf;
    }
    memset(&v11->tag[v11->offset], 0, 4 * v4);
    v19 = 0;
    for ( cksize = (char **)v7; v19 < v4; v11->tag[v21] = v20 )
    {
      v20 = sgetS0((unsigned __int8 **)&cksize);
      v21 = v19 + v11->offset;
      ++v19;
    }
    Mem_Free(v7);
    return 1;
  }
  else
  {
    Mem_Free(v7);
    return 0;
  }
}

// FUNC: int __cdecl lwGetPolygonTags(class idFile *,int,struct st_lwTagList *,struct st_lwPolygonList *)
int __cdecl lwGetPolygonTags(idFile *fp, int cksize, st_lwTagList *tlist, st_lwPolygonList *plist)
{
  unsigned int U4; // ebp
  int v6; // esi
  int VX; // eax
  int v8; // ecx
  st_lwSurface *v9; // eax

  flen = 0;
  U4 = getU4(fp);
  if ( flen < 0 )
    return 0;
  if ( U4 == 1398100550 || U4 == 1346458196 || U4 == 1397573456 )
  {
    if ( flen >= cksize )
    {
      return 1;
    }
    else
    {
      while ( 1 )
      {
        v6 = plist->offset + getVX(fp);
        VX = getVX(fp);
        v8 = flen;
        v9 = (st_lwSurface *)(tlist->offset + VX);
        if ( flen < 0 || flen > cksize )
          break;
        if ( U4 == 1346458196 )
        {
          plist->pol[v6].part = (int)v9;
        }
        else if ( U4 == 1397573456 )
        {
          plist->pol[v6].smoothgrp = (int)v9;
        }
        else
        {
          plist->pol[v6].surf = v9;
        }
        if ( v8 >= cksize )
          return 1;
      }
      return 0;
    }
  }
  else
  {
    fp->Seek(fp, cksize - 4, FS_SEEK_CUR);
    return 1;
  }
}

// FUNC: void __cdecl lwFreePlugin(struct st_lwPlugin *)
void __cdecl lwFreePlugin(st_lwPlugin *p)
{
  if ( p )
  {
    if ( p->ord )
      Mem_Free(p->ord);
    if ( p->name )
      Mem_Free(p->name);
    if ( p->data )
      Mem_Free(p->data);
    Mem_Free(p);
  }
}

// FUNC: void __cdecl lwFreeTexture(struct st_lwTexture *)
void __cdecl lwFreeTexture(st_lwTexture *t)
{
  unsigned int type; // eax
  void *ikey; // eax

  if ( !t )
    return;
  if ( t->ord )
    Mem_Free(t->ord);
  type = t->type;
  switch ( type )
  {
    case 0x47524144u:
      if ( t->param.imap.wraph_type )
        Mem_Free(t->param.proc.data);
      ikey = t->param.grad.ikey;
      goto LABEL_14;
    case 0x494D4150u:
      ikey = t->param.imap.vmap_name;
LABEL_14:
      if ( ikey )
        Mem_Free(ikey);
      break;
    case 0x50524F43u:
      if ( t->param.imap.wrapw_type )
        Mem_Free(t->param.proc.name);
      ikey = t->param.proc.data;
      goto LABEL_14;
  }
  if ( t->tmap.ref_object )
    Mem_Free(t->tmap.ref_object);
  Mem_Free(t);
}

// FUNC: void __cdecl lwFreeSurface(struct st_lwSurface *)
void __cdecl lwFreeSurface(st_lwSurface *surf)
{
  st_lwPlugin *shader; // esi
  st_lwPlugin *next; // edi
  st_lwTexture *tex; // eax
  st_lwTexture *v4; // esi
  st_lwTexture *v5; // eax
  st_lwTexture *v6; // esi
  st_lwTexture *v7; // eax
  st_lwTexture *v8; // esi
  st_lwTexture *v9; // eax
  st_lwTexture *v10; // esi
  st_lwTexture *v11; // eax
  st_lwTexture *v12; // esi
  st_lwTexture *v13; // eax
  st_lwTexture *v14; // esi
  st_lwTexture *v15; // eax
  st_lwTexture *v16; // esi
  st_lwTexture *v17; // eax
  st_lwTexture *v18; // esi
  st_lwTexture *v19; // eax
  st_lwTexture *v20; // esi
  st_lwTexture *v21; // eax
  st_lwTexture *v22; // esi

  if ( surf )
  {
    if ( surf->name )
      Mem_Free(surf->name);
    if ( surf->srcname )
      Mem_Free(surf->srcname);
    shader = surf->shader;
    if ( shader )
    {
      do
      {
        next = shader->next;
        if ( shader->ord )
          Mem_Free(shader->ord);
        if ( shader->name )
          Mem_Free(shader->name);
        if ( shader->data )
          Mem_Free(shader->data);
        Mem_Free(shader);
        shader = next;
      }
      while ( next );
    }
    tex = surf->color.tex;
    if ( tex )
    {
      do
      {
        v4 = tex->next;
        lwFreeTexture(tex);
        tex = v4;
      }
      while ( v4 );
    }
    v5 = surf->luminosity.tex;
    if ( v5 )
    {
      do
      {
        v6 = v5->next;
        lwFreeTexture(v5);
        v5 = v6;
      }
      while ( v6 );
    }
    v7 = surf->diffuse.tex;
    if ( v7 )
    {
      do
      {
        v8 = v7->next;
        lwFreeTexture(v7);
        v7 = v8;
      }
      while ( v8 );
    }
    v9 = surf->specularity.tex;
    if ( v9 )
    {
      do
      {
        v10 = v9->next;
        lwFreeTexture(v9);
        v9 = v10;
      }
      while ( v10 );
    }
    v11 = surf->glossiness.tex;
    if ( v11 )
    {
      do
      {
        v12 = v11->next;
        lwFreeTexture(v11);
        v11 = v12;
      }
      while ( v12 );
    }
    v13 = surf->reflection.val.tex;
    if ( v13 )
    {
      do
      {
        v14 = v13->next;
        lwFreeTexture(v13);
        v13 = v14;
      }
      while ( v14 );
    }
    v15 = surf->transparency.val.tex;
    if ( v15 )
    {
      do
      {
        v16 = v15->next;
        lwFreeTexture(v15);
        v15 = v16;
      }
      while ( v16 );
    }
    v17 = surf->eta.tex;
    if ( v17 )
    {
      do
      {
        v18 = v17->next;
        lwFreeTexture(v17);
        v17 = v18;
      }
      while ( v18 );
    }
    v19 = surf->translucency.tex;
    if ( v19 )
    {
      do
      {
        v20 = v19->next;
        lwFreeTexture(v19);
        v19 = v20;
      }
      while ( v20 );
    }
    v21 = surf->bump.tex;
    if ( v21 )
    {
      do
      {
        v22 = v21->next;
        lwFreeTexture(v21);
        v21 = v22;
      }
      while ( v22 );
    }
    Mem_Free(surf);
  }
}

// FUNC: int __cdecl lwGetTHeader(class idFile *,int,struct st_lwTexture *)
int __cdecl lwGetTHeader(idFile *fp, int hsz, st_lwTexture *tex)
{
  idFile *v3; // esi
  idFile_vtbl *v4; // eax
  char *S0; // eax
  st_lwTexture *v6; // ebp
  unsigned int U4; // edi
  unsigned __int16 U2; // bx
  unsigned __int16 v9; // bx
  int v10; // ecx
  __int16 v11; // ax
  int v12; // eax
  int v13; // edi
  idFile v14; // edx
  bool v15; // zf
  unsigned int v17; // [esp+1Ch] [ebp-Ch] BYREF
  int v18; // [esp+20h] [ebp-8h] BYREF
  int pos; // [esp+24h] [ebp-4h]

  v3 = fp;
  v4 = fp->__vftable;
  flen = 0;
  pos = v4->Tell(fp);
  S0 = getS0(v3);
  v6 = tex;
  tex->ord = S0;
  U4 = getU4(v3);
  U2 = getU2(v3);
  if ( flen < 0 )
    return 0;
  while ( 1 )
  {
    v9 = (U2 & 1) + U2;
    v10 = 0;
    flen = 0;
    if ( U4 > 0x454E4142 )
    {
      if ( U4 == 1313163073 )
      {
        if ( v3->Read(v3, &tex, 2) == 2 )
        {
          BigRevBytes(&tex, 2, 1);
          v11 = (__int16)tex;
          flen += 2;
        }
        else
        {
          flen = -9999;
          v11 = 0;
        }
        v6->negative = v11;
      }
      else
      {
        if ( U4 != 1330659651 )
          goto LABEL_19;
        v6->opac_type = getU2(v3);
        v6->opacity.val = getF4(v3);
        v6->opacity.eindex = getVX(v3);
      }
    }
    else
    {
      switch ( U4 )
      {
        case 0x454E4142u:
          if ( v3->Read(v3, &fp, 2) == 2 )
          {
            BigRevBytes(&fp, 2, 1);
            flen += 2;
            v6->enabled = (__int16)fp;
          }
          else
          {
            flen = -9999;
            v6->enabled = 0;
          }
          break;
        case 0x41584953u:
          v6->axis = getU2(v3);
          break;
        case 0x4348414Eu:
          v6->chan = getU4(v3);
          break;
        default:
          goto LABEL_19;
      }
    }
    v10 = flen;
    if ( flen < 0 )
      return 0;
LABEL_19:
    if ( v10 > v9 )
      return 0;
    if ( v10 < v9 )
      v3->Seek(v3, v9 - v10, FS_SEEK_CUR);
    v12 = v3->Tell(v3);
    v13 = pos;
    v14.__vftable = v3->__vftable;
    if ( hsz <= v12 - pos )
      break;
    flen = 0;
    if ( v14.Read(v3, &v17, 4) != 4 )
      goto LABEL_28;
    BigRevBytes(&v17, 4, 1);
    U4 = v17;
    v15 = flen == -10003;
    flen += 4;
    if ( v15 )
      return 0;
    if ( v3->Read(v3, &v18, 2) != 2 )
    {
LABEL_28:
      flen = -9999;
      return 0;
    }
    BigRevBytes(&v18, 2, 1);
    U2 = v18;
    flen += 2;
    if ( flen != 6 )
      return 0;
  }
  flen = v14.Tell(v3) - v13;
  return 1;
}

// FUNC: int __cdecl lwGetTMap(class idFile *,int,struct st_lwTMap *)
int __cdecl lwGetTMap(idFile *fp, int tmapsz, st_lwTMap *tmap)
{
  int v4; // ebp
  unsigned int U4; // edi
  unsigned __int16 U2; // ax
  unsigned __int16 v8; // ax
  int v9; // ecx
  st_lwVParam *p_falloff; // edi
  int v11; // ebp
  st_lwVParam *p_center; // edi
  int v13; // ebp
  int i; // edi
  st_lwVParam *p_rotate; // edi
  int v16; // ebp
  int pos; // [esp+Ch] [ebp-4h]
  unsigned __int16 fpa; // [esp+14h] [ebp+4h]

  v4 = fp->Tell(fp);
  pos = v4;
  U4 = getU4(fp);
  U2 = getU2(fp);
  if ( flen < 0 )
    return 0;
  do
  {
    v8 = (U2 & 1) + U2;
    v9 = 0;
    fpa = v8;
    flen = 0;
    if ( U4 > 0x4F524546 )
    {
      if ( U4 == 1380930625 )
      {
        p_rotate = &tmap->rotate;
        v16 = 3;
        do
        {
          p_rotate->val[0] = getF4(fp);
          p_rotate = (st_lwVParam *)((char *)p_rotate + 4);
          --v16;
        }
        while ( v16 );
        tmap->rotate.eindex = getVX(fp);
      }
      else
      {
        if ( U4 != 1397316165 )
          goto LABEL_26;
        for ( i = 0; i < 3; ++i )
          tmap->size.val[i] = getF4(fp);
        tmap->size.eindex = getVX(fp);
      }
    }
    else
    {
      switch ( U4 )
      {
        case 0x4F524546u:
          tmap->ref_object = getS0(fp);
          break;
        case 0x434E5452u:
          p_center = &tmap->center;
          v13 = 3;
          do
          {
            p_center->val[0] = getF4(fp);
            p_center = (st_lwVParam *)((char *)p_center + 4);
            --v13;
          }
          while ( v13 );
          tmap->center.eindex = getVX(fp);
          break;
        case 0x43535953u:
          tmap->coord_sys = getU2(fp);
          break;
        case 0x46414C4Cu:
          tmap->fall_type = getU2(fp);
          p_falloff = &tmap->falloff;
          v11 = 3;
          do
          {
            p_falloff->val[0] = getF4(fp);
            p_falloff = (st_lwVParam *)((char *)p_falloff + 4);
            --v11;
          }
          while ( v11 );
          tmap->falloff.eindex = getVX(fp);
          break;
        default:
          goto LABEL_26;
      }
    }
    v9 = flen;
    if ( flen < 0 )
      return 0;
    v8 = fpa;
    v4 = pos;
LABEL_26:
    if ( v9 > v8 )
      break;
    if ( v9 < v8 )
      fp->Seek(fp, v8 - v9, FS_SEEK_CUR);
    if ( tmapsz <= fp->Tell(fp) - v4 )
    {
      flen = fp->Tell(fp) - v4;
      return 1;
    }
    flen = 0;
    U4 = getU4(fp);
    U2 = getU2(fp);
  }
  while ( flen == 6 );
  return 0;
}

// FUNC: int __cdecl lwGetImageMap(class idFile *,int,struct st_lwTexture *)
int __cdecl lwGetImageMap(idFile *fp, int rsz, st_lwTexture *tex)
{
  idFile *v3; // esi
  idFile *U4; // edi
  unsigned __int16 U2; // bx
  st_lwTexture *v7; // ebp
  unsigned __int16 v8; // bx
  int v9; // ecx
  idFile *v10; // edi
  int v11; // eax
  int v12; // edi
  idFile v13; // edx
  bool v14; // zf
  int v15; // [esp+18h] [ebp-8h] BYREF
  int pos; // [esp+1Ch] [ebp-4h]

  v3 = fp;
  pos = fp->Tell(fp);
  U4 = (idFile *)getU4(v3);
  U2 = getU2(v3);
  if ( flen < 0 )
    return 0;
  v7 = tex;
  while ( 1 )
  {
    v8 = (U2 & 1) + U2;
    v9 = 0;
    flen = 0;
    if ( (unsigned int)U4 > 0x54414D50 )
    {
      if ( (unsigned int)U4 > 0x57524150 )
      {
        v10 = U4 - 366253074;
        if ( v10 )
        {
          if ( v10 != (idFile *)15 )
            goto LABEL_33;
          v7->param.imap.wrapw.val = getF4(v3);
          v7->param.imap.wrapw.eindex = getVX(v3);
        }
        else
        {
          v7->param.imap.wraph.val = getF4(v3);
          v7->param.imap.wraph.eindex = getVX(v3);
        }
      }
      else if ( U4 == (idFile *)1465008464 )
      {
        v7->param.imap.wrapw_type = getU2(v3);
        v7->param.imap.wraph_type = getU2(v3);
      }
      else if ( U4 == (idFile *)1414349136 )
      {
        if ( !lwGetTMap(v3, v8, &v7->tmap) )
          return 0;
      }
      else
      {
        if ( U4 != (idFile *)1447903568 )
          goto LABEL_33;
        v7->param.imap.vmap_name = getS0(v3);
      }
    }
    else if ( U4 == (idFile *)1413565776 )
    {
      v7->param.imap.amplitude.val = getF4(v3);
      v7->param.imap.amplitude.eindex = getVX(v3);
    }
    else if ( (unsigned int)U4 > 0x50495842 )
    {
      if ( U4 == (idFile *)1347571530 )
      {
        v7->param.imap.projection = getU2(v3);
      }
      else
      {
        if ( U4 != (idFile *)1398031179 )
          goto LABEL_33;
        v7->param.imap.stck.val = getF4(v3);
        v7->param.imap.stck.eindex = getVX(v3);
      }
    }
    else if ( U4 == (idFile *)1346984002 )
    {
      v7->param.imap.pblend = getU2(v3);
    }
    else if ( U4 == (idFile *)1094800212 )
    {
      v7->param.imap.aas_flags = getU2(v3);
      v7->param.imap.aa_strength = getF4(v3);
    }
    else if ( U4 == (idFile *)1096304979 )
    {
      v7->param.imap.axis = getU2(v3);
    }
    else
    {
      if ( U4 != (idFile *)1229799751 )
        goto LABEL_33;
      v7->param.imap.cindex = getVX(v3);
    }
    v9 = flen;
    if ( flen < 0 )
      return 0;
LABEL_33:
    if ( v9 > v8 )
      return 0;
    if ( v9 < v8 )
      v3->Seek(v3, v8 - v9, FS_SEEK_CUR);
    v11 = v3->Tell(v3);
    v12 = pos;
    v13.__vftable = v3->__vftable;
    if ( rsz <= v11 - pos )
      break;
    flen = 0;
    if ( v13.Read(v3, &fp, 4) != 4 )
      goto LABEL_42;
    BigRevBytes(&fp, 4, 1);
    U4 = fp;
    v14 = flen == -10003;
    flen += 4;
    if ( v14 )
      return 0;
    if ( v3->Read(v3, &v15, 2) != 2 )
    {
LABEL_42:
      flen = -9999;
      return 0;
    }
    BigRevBytes(&v15, 2, 1);
    U2 = v15;
    flen += 2;
    if ( flen != 6 )
      return 0;
  }
  flen = v13.Tell(v3) - v12;
  return 1;
}

// FUNC: int __cdecl lwGetProcedural(class idFile *,int,struct st_lwTexture *)
int __cdecl lwGetProcedural(idFile *fp, int rsz, st_lwTexture *tex)
{
  idFile *v3; // esi
  idFile *U4; // edi
  unsigned __int16 U2; // bx
  st_lwTexture *v7; // ebp
  unsigned __int16 v8; // bx
  int v9; // ecx
  char *S0; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edi
  idFile v14; // edx
  bool v15; // zf
  int v16; // [esp+18h] [ebp-8h] BYREF
  int pos; // [esp+1Ch] [ebp-4h]

  v3 = fp;
  pos = fp->Tell(fp);
  U4 = (idFile *)getU4(v3);
  U2 = getU2(v3);
  if ( flen < 0 )
    return 0;
  v7 = tex;
  while ( 1 )
  {
    v8 = (U2 & 1) + U2;
    v9 = 0;
    flen = 0;
    if ( (unsigned int)U4 > 0x544D4150 )
    {
      if ( U4 != (idFile *)1447119957 )
        goto LABEL_18;
      v7->param.proc.value[0] = getF4(v3);
      if ( v8 >= 8u )
        v7->param.proc.value[1] = getF4(v3);
      if ( v8 >= 0xCu )
        v7->param.proc.value[2] = getF4(v3);
    }
    else if ( U4 == (idFile *)1414349136 )
    {
      if ( !lwGetTMap(v3, v8, &v7->tmap) )
        return 0;
    }
    else if ( U4 == (idFile *)1096304979 )
    {
      v7->param.imap.cindex = getU2(v3);
    }
    else
    {
      if ( U4 != (idFile *)1179995715 )
        goto LABEL_18;
      S0 = getS0(v3);
      v11 = v8 - flen;
      v7->param.imap.wrapw_type = (int)S0;
      v7->param.imap.wraph_type = (int)getbytes(v3, v11);
    }
    v9 = flen;
    if ( flen < 0 )
      return 0;
LABEL_18:
    if ( v9 > v8 )
      return 0;
    if ( v9 < v8 )
      v3->Seek(v3, v8 - v9, FS_SEEK_CUR);
    v12 = v3->Tell(v3);
    v13 = pos;
    v14.__vftable = v3->__vftable;
    if ( rsz <= v12 - pos )
      break;
    flen = 0;
    if ( v14.Read(v3, &fp, 4) != 4 )
      goto LABEL_27;
    BigRevBytes(&fp, 4, 1);
    U4 = fp;
    v15 = flen == -10003;
    flen += 4;
    if ( v15 )
      return 0;
    if ( v3->Read(v3, &v16, 2) != 2 )
    {
LABEL_27:
      flen = -9999;
      return 0;
    }
    BigRevBytes(&v16, 2, 1);
    U2 = v16;
    flen += 2;
    if ( flen != 6 )
      return 0;
  }
  flen = v14.Tell(v3) - v13;
  return 1;
}

// FUNC: int __cdecl lwGetGradient(class idFile *,int,struct st_lwTexture *)
int __cdecl lwGetGradient(idFile *fp, int rsz, st_lwTexture *tex)
{
  int v4; // ebp
  unsigned int U4; // esi
  unsigned __int16 U2; // ax
  unsigned __int16 v8; // ax
  int v9; // ecx
  signed int v10; // esi
  void *v11; // eax
  idFile *v12; // ebp
  idFile *v13; // esi
  int v14; // ebp
  int v15; // esi
  __int16 *v16; // eax
  int i; // ebp
  __int16 v18; // ax
  unsigned __int16 sz; // [esp+Ch] [ebp-10h]
  signed int v20; // [esp+10h] [ebp-Ch]
  __int16 v21; // [esp+14h] [ebp-8h] BYREF
  int pos; // [esp+18h] [ebp-4h]
  idFile *fpa; // [esp+20h] [ebp+4h]

  v4 = fp->Tell(fp);
  pos = v4;
  U4 = getU4(fp);
  U2 = getU2(fp);
  if ( flen < 0 )
    return 0;
  while ( 1 )
  {
    v8 = (U2 & 1) + U2;
    v9 = 0;
    sz = v8;
    flen = 0;
    if ( U4 > 0x494B4559 )
    {
      switch ( U4 )
      {
        case 0x494E414Du:
          tex->param.imap.projection = (int)getS0(fp);
          break;
        case 0x504E414Du:
          tex->param.imap.cindex = (int)getS0(fp);
          break;
        case 0x544D4150u:
          if ( !lwGetTMap(fp, v8, &tex->tmap) )
            return 0;
          break;
        default:
          goto LABEL_39;
      }
    }
    else if ( U4 == 1229669721 )
    {
      v15 = v8 >> 1;
      v16 = (__int16 *)Mem_ClearedAlloc(2 * v15, 0xEu);
      tex->param.grad.ikey = v16;
      if ( !v16 )
        return 0;
      for ( i = 0; i < v15; ++i )
      {
        if ( flen == -9999 )
        {
          v18 = 0;
        }
        else if ( fp->Read(fp, &v21, 2) == 2 )
        {
          BigRevBytes(&v21, 2, 1);
          v18 = v21;
          flen += 2;
        }
        else
        {
          flen = -9999;
          v18 = 0;
        }
        tex->param.grad.ikey[i] = v18;
      }
    }
    else if ( U4 > 0x47525054 )
    {
      if ( U4 != 1196577620 )
        goto LABEL_39;
      tex->param.proc.value[1] = getF4(fp);
    }
    else
    {
      switch ( U4 )
      {
        case 0x47525054u:
          tex->param.imap.wrapw_type = getU2(fp);
          break;
        case 0x464B4559u:
          v10 = v8 / 0x1Cu;
          v11 = Mem_ClearedAlloc(28 * v10, 0xEu);
          tex->param.imap.wraph_type = (int)v11;
          if ( !v11 )
            return 0;
          if ( v10 > 0 )
          {
            v12 = 0;
            fpa = 0;
            v20 = v10;
            while ( 1 )
            {
              *(float *)((char *)&v12[2].__vftable + tex->param.imap.wraph_type) = getF4(fp);
              v13 = v12 + 3;
              v14 = 4;
              do
              {
                *(float *)((char *)&v13->__vftable + tex->param.imap.wraph_type) = getF4(fp);
                ++v13;
                --v14;
              }
              while ( v14 );
              fpa += 7;
              if ( !--v20 )
                break;
              v12 = fpa;
            }
          }
          break;
        case 0x4752454Eu:
          tex->param.proc.value[2] = getF4(fp);
          break;
        default:
          goto LABEL_39;
      }
    }
    v9 = flen;
    if ( flen < 0 )
      return 0;
    v8 = sz;
    v4 = pos;
LABEL_39:
    if ( v9 > v8 )
      return 0;
    if ( v9 < v8 )
      fp->Seek(fp, v8 - v9, FS_SEEK_CUR);
    if ( rsz <= fp->Tell(fp) - v4 )
      break;
    flen = 0;
    U4 = getU4(fp);
    U2 = getU2(fp);
    if ( flen != 6 )
      return 0;
  }
  flen = fp->Tell(fp) - v4;
  return 1;
}

// FUNC: struct st_lwTexture * __cdecl lwGetTexture(class idFile *,int,unsigned int)
st_lwTexture *__cdecl lwGetTexture(idFile *fp, int bloksz, unsigned int type)
{
  st_lwTexture *result; // eax
  st_lwTexture *v4; // esi
  unsigned __int16 U2; // bx
  unsigned __int16 v6; // ax
  int Gradient; // eax

  result = (st_lwTexture *)Mem_ClearedAlloc(180, 0xEu);
  v4 = result;
  if ( result )
  {
    result->type = type;
    result->tmap.size.val[2] = 1.0;
    result->tmap.size.val[1] = 1.0;
    result->tmap.size.val[0] = 1.0;
    result->opacity.val = 1.0;
    result->enabled = 1;
    U2 = getU2(fp);
    if ( lwGetTHeader(fp, U2, v4) )
    {
      v6 = bloksz - U2 - 6;
      switch ( type )
      {
        case 0x47524144u:
          Gradient = lwGetGradient(fp, v6, v4);
          break;
        case 0x494D4150u:
          Gradient = lwGetImageMap(fp, v6, v4);
          break;
        case 0x50524F43u:
          Gradient = lwGetProcedural(fp, v6, v4);
          break;
        default:
          Gradient = fp->Seek(fp, v6, FS_SEEK_CUR) == 0;
          break;
      }
      if ( Gradient )
      {
        result = v4;
        flen = bloksz;
      }
      else
      {
        lwFreeTexture(v4);
        return 0;
      }
    }
    else
    {
      Mem_Free(v4);
      return 0;
    }
  }
  return result;
}

// FUNC: struct st_lwPlugin * __cdecl lwGetShader(class idFile *,int)
st_lwPlugin *__cdecl lwGetShader(idFile *fp, int bloksz)
{
  st_lwPlugin *result; // eax
  st_lwPlugin *v3; // edi
  int U2; // ebx
  unsigned int U4; // edi
  unsigned __int16 v6; // ax
  int v7; // eax
  unsigned int v8; // edi
  unsigned __int16 v9; // bx
  int v10; // ecx
  unsigned __int16 v11; // bx
  void *v12; // eax
  bool v13; // sf
  int v14; // eax
  int v15; // edi
  idFile_vtbl *v16; // edx
  bool v17; // zf
  st_lwPlugin *shdr; // [esp+18h] [ebp-10h]
  unsigned int v19; // [esp+1Ch] [ebp-Ch] BYREF
  unsigned int v20; // [esp+20h] [ebp-8h] BYREF
  int pos; // [esp+24h] [ebp-4h]

  result = (st_lwPlugin *)Mem_ClearedAlloc(24, 0xEu);
  v3 = result;
  shdr = result;
  if ( result )
  {
    pos = fp->Tell(fp);
    flen = 0;
    U2 = getU2(fp);
    v3->ord = getS0(fp);
    U4 = getU4(fp);
    v6 = getU2(fp);
    if ( flen >= 0 )
    {
      if ( U2 > 0 )
      {
        while ( 1 )
        {
          v7 = (unsigned __int16)((v6 & 1) + v6);
          U2 -= v7;
          if ( U4 == 1162756418 )
            break;
          fp->Seek(fp, v7, FS_SEEK_CUR);
          if ( flen == -9999 )
          {
            U4 = 0;
            v6 = 0;
          }
          else if ( fp->Read(fp, &v19, 4) == 4 )
          {
            BigRevBytes(&v19, 4, 1);
            U4 = v19;
            flen += 4;
            if ( flen == -9999 )
            {
              v6 = 0;
            }
            else if ( fp->Read(fp, &v20, 2) == 2 )
            {
              BigRevBytes(&v20, 2, 1);
              v6 = v20;
              flen += 2;
            }
            else
            {
              flen = -9999;
              v6 = 0;
            }
          }
          else
          {
            U4 = 0;
            flen = -9999;
            v6 = 0;
          }
          if ( U2 <= 0 )
            goto LABEL_17;
        }
        shdr->flags = getU2(fp);
      }
LABEL_17:
      v8 = getU4(fp);
      v9 = getU2(fp);
      if ( flen >= 0 )
      {
        do
        {
          v10 = 0;
          flen = 0;
          v11 = (v9 & 1) + v9;
          if ( v8 == 1179995715 )
          {
            shdr->name = getS0(fp);
            v12 = getbytes(fp, v11 - flen);
            v10 = flen;
            v13 = flen < 0;
            shdr->data = v12;
            if ( v13 )
              break;
          }
          if ( v10 > v11 )
            break;
          if ( v10 < v11 )
            fp->Seek(fp, v11 - v10, FS_SEEK_CUR);
          v14 = fp->Tell(fp);
          v15 = pos;
          v16 = fp->__vftable;
          if ( bloksz <= v14 - pos )
          {
            flen = v16->Tell(fp) - v15;
            return shdr;
          }
          flen = 0;
          if ( v16->Read(fp, &v20, 4) != 4 )
            goto LABEL_29;
          BigRevBytes(&v20, 4, 1);
          v8 = v20;
          v17 = flen == -10003;
          flen += 4;
          if ( v17 )
            break;
          if ( fp->Read(fp, &v19, 2) != 2 )
          {
LABEL_29:
            flen = -9999;
            break;
          }
          BigRevBytes(&v19, 2, 1);
          v9 = v19;
          flen += 2;
        }
        while ( flen == 6 );
      }
    }
    lwFreePlugin(shdr);
    return 0;
  }
  return result;
}

// FUNC: struct st_lwSurface * __cdecl lwGetSurface(class idFile *,int)
st_lwSurface *__cdecl lwGetSurface(idFile *fp, int cksize)
{
  st_lwSurface *v2; // eax
  st_lwSurface *v3; // edi
  idFile_vtbl *v4; // eax
  unsigned int U4; // ebp
  unsigned __int16 U2; // bx
  unsigned __int16 v7; // bx
  int v8; // ecx
  unsigned int v9; // eax
  st_lwTexture *Texture; // eax
  st_lwTexture *v11; // ebp
  st_lwPlugin *Shader; // eax
  int v13; // eax
  idFile_vtbl *v14; // edx
  bool v15; // zf
  unsigned int v17; // [esp+14h] [ebp-Ch] BYREF
  int v18; // [esp+18h] [ebp-8h] BYREF
  int pos; // [esp+1Ch] [ebp-4h]

  v2 = (st_lwSurface *)Mem_ClearedAlloc(244, 0xEu);
  v3 = v2;
  if ( !v2 )
    return 0;
  v2->color.rgb[0] = 0.78430998;
  v2->color.rgb[1] = 0.78430998;
  v2->color.rgb[2] = 0.78430998;
  v2->diffuse.val = 1.0;
  v2->glossiness.val = 0.40000001;
  v2->bump.val = 1.0;
  v2->eta.val = 1.0;
  v2->sideflags = 1;
  v4 = fp->__vftable;
  flen = 0;
  pos = v4->Tell(fp);
  v3->name = getS0(fp);
  v3->srcname = getS0(fp);
  U4 = getU4(fp);
  U2 = getU2(fp);
  if ( flen < 0 )
  {
Fail_2:
    lwFreeSurface(v3);
    return 0;
  }
  while ( 1 )
  {
    v7 = (U2 & 1) + U2;
    v8 = 0;
    flen = 0;
    if ( U4 > 0x5245464C )
    {
      if ( U4 > 0x534D414E )
      {
        if ( U4 > 0x5452414E )
        {
          if ( U4 == 1414680140 )
          {
            v3->translucency.val = getF4(fp);
            v3->translucency.eindex = getVX(fp);
          }
          else
          {
            if ( U4 != 1414680400 )
              goto LABEL_78;
            v3->transparency.options = getU2(fp);
          }
        }
        else
        {
          switch ( U4 )
          {
            case 0x5452414Eu:
              v3->transparency.val.val = getF4(fp);
              v3->transparency.val.eindex = getVX(fp);
              break;
            case 0x53504543u:
              v3->specularity.val = getF4(fp);
              v3->specularity.eindex = getVX(fp);
              break;
            case 0x54494D47u:
              v3->transparency.cindex = getVX(fp);
              break;
            default:
              goto LABEL_78;
          }
        }
      }
      else if ( U4 == 1397571918 )
      {
        v3->smooth = getF4(fp);
      }
      else if ( U4 > 0x5253414E )
      {
        if ( U4 == 1397248592 )
        {
          v3->dif_sharp.val = getF4(fp);
          v3->dif_sharp.eindex = getVX(fp);
        }
        else
        {
          if ( U4 != 1397310533 )
            goto LABEL_78;
          v3->sideflags = getU2(fp);
        }
      }
      else
      {
        switch ( U4 )
        {
          case 0x5253414Eu:
            v3->reflection.seam_angle = getF4(fp);
            break;
          case 0x52464F50u:
            v3->reflection.options = getU2(fp);
            break;
          case 0x52494D47u:
            v3->reflection.cindex = getVX(fp);
            break;
          case 0x52494E44u:
            v3->eta.val = getF4(fp);
            v3->eta.eindex = getVX(fp);
            break;
          default:
            goto LABEL_78;
        }
      }
    }
    else if ( U4 == 1380271692 )
    {
      v3->reflection.val.val = getF4(fp);
      v3->reflection.val.eindex = getVX(fp);
    }
    else if ( U4 > 0x434C5248 )
    {
      if ( U4 > 0x4756414C )
      {
        if ( U4 == 1279872581 )
        {
          v3->line.enabled = 1;
          if ( v7 >= 2u )
            v3->line.flags = getU2(fp);
          if ( v7 >= 6u )
            v3->line.size.val = getF4(fp);
          if ( v7 >= 8u )
            v3->line.size.eindex = getVX(fp);
        }
        else
        {
          if ( U4 != 1280658761 )
            goto LABEL_78;
          v3->luminosity.val = getF4(fp);
          v3->luminosity.eindex = getVX(fp);
        }
      }
      else
      {
        switch ( U4 )
        {
          case 0x4756414Cu:
            v3->glow.val = getF4(fp);
            v3->glow.eindex = getVX(fp);
            break;
          case 0x434F4C52u:
            v3->color.rgb[0] = getF4(fp);
            v3->color.rgb[1] = getF4(fp);
            v3->color.rgb[2] = getF4(fp);
            v3->color.eindex = getVX(fp);
            break;
          case 0x44494646u:
            v3->diffuse.val = getF4(fp);
            v3->diffuse.eindex = getVX(fp);
            break;
          case 0x474C4F53u:
            v3->glossiness.val = getF4(fp);
            v3->glossiness.eindex = getVX(fp);
            break;
          default:
            goto LABEL_78;
        }
      }
    }
    else if ( U4 == 1129075272 )
    {
      v3->color_hilite.val = getF4(fp);
      v3->color_hilite.eindex = getVX(fp);
    }
    else if ( U4 > 0x424C4F4B )
    {
      if ( U4 == 1112886608 )
      {
        v3->bump.val = getF4(fp);
        v3->bump.eindex = getVX(fp);
      }
      else
      {
        if ( U4 != 1129075270 )
          goto LABEL_78;
        v3->color_filter.val = getF4(fp);
        v3->color_filter.eindex = getVX(fp);
      }
    }
    else
    {
      switch ( U4 )
      {
        case 0x424C4F4Bu:
          v9 = getU4(fp);
          if ( v9 > 0x50524F43 )
          {
            if ( v9 == 1397245010 )
            {
              Shader = lwGetShader(fp, v7 - 4);
              if ( !Shader )
                goto Fail_2;
              lwListInsert((void **)&v3->shader, Shader, (int (__cdecl *)(void *, void *))compare_shaders);
              ++v3->nshaders;
              flen += 4;
            }
          }
          else if ( v9 == 1347571523 || v9 == 1196572996 || v9 == 1229799760 )
          {
            Texture = lwGetTexture(fp, v7 - 4, v9);
            v11 = Texture;
            if ( !Texture )
              goto Fail_2;
            if ( !add_texture(v3, Texture) )
              lwFreeTexture(v11);
            flen += 4;
          }
          break;
        case 0x41445452u:
          v3->add_trans.val = getF4(fp);
          v3->add_trans.eindex = getVX(fp);
          break;
        case 0x414C5048u:
          v3->alpha_mode = getU2(fp);
          v3->alpha = getF4(fp);
          break;
        case 0x4156414Cu:
          v3->alpha = getF4(fp);
          break;
        default:
          goto LABEL_78;
      }
    }
    v8 = flen;
    if ( flen < 0 )
      goto Fail_2;
LABEL_78:
    if ( v8 > v7 )
      goto Fail_2;
    if ( v8 < v7 )
      fp->Seek(fp, v7 - v8, FS_SEEK_CUR);
    v13 = fp->Tell(fp);
    if ( cksize <= v13 - pos )
      return v3;
    v14 = fp->__vftable;
    flen = 0;
    if ( v14->Read(fp, &v17, 4) != 4 )
      goto LABEL_88;
    BigRevBytes(&v17, 4, 1);
    U4 = v17;
    v15 = flen == -10003;
    flen += 4;
    if ( v15 )
      goto Fail_2;
    if ( fp->Read(fp, &v18, 2) != 2 )
    {
LABEL_88:
      flen = -9999;
      lwFreeSurface(v3);
      return 0;
    }
    BigRevBytes(&v18, 2, 1);
    U2 = v18;
    flen += 2;
    if ( flen != 6 )
      goto Fail_2;
  }
}

// FUNC: void __cdecl lwFreeVMap(struct st_lwVMap *)
void __cdecl lwFreeVMap(st_lwVMap *vmap)
{
  float **val; // eax
  float *v2; // eax

  if ( vmap )
  {
    if ( vmap->name )
      Mem_Free(vmap->name);
    if ( vmap->vindex )
      Mem_Free(vmap->vindex);
    if ( vmap->pindex )
      Mem_Free(vmap->pindex);
    val = vmap->val;
    if ( val )
    {
      v2 = *val;
      if ( v2 )
        Mem_Free(v2);
      Mem_Free(vmap->val);
    }
    Mem_Free(vmap);
  }
}

// FUNC: struct st_lwVMap * __cdecl lwGetVMap(class idFile *,int,int,int,int)
st_lwVMap *__cdecl lwGetVMap(idFile *fp, int cksize, int ptoffset, int poloffset, int perpoly)
{
  int v5; // edi
  unsigned __int8 *v6; // ebp
  st_lwVMap *v8; // eax
  st_lwVMap *v9; // esi
  unsigned int v10; // eax
  bool v11; // zf
  unsigned __int8 *v12; // eax
  unsigned __int16 v13; // ax
  unsigned __int16 v14; // cx
  char *v15; // eax
  int v16; // ecx
  unsigned __int8 *v17; // eax
  unsigned __int8 *v18; // ebx
  int v19; // ebp
  int *v20; // eax
  int *v21; // eax
  float **v22; // eax
  char *v23; // eax
  int i; // ecx
  int v25; // ebp
  int v26; // ebx
  unsigned __int8 *v27; // edi
  double v28; // st7
  unsigned __int8 *v29; // [esp+Ch] [ebp-10h] BYREF
  float v30; // [esp+10h] [ebp-Ch] BYREF
  int rlen; // [esp+14h] [ebp-8h]
  unsigned __int8 *buf; // [esp+18h] [ebp-4h]

  v5 = 0;
  flen = 0;
  v6 = (unsigned __int8 *)getbytes(fp, cksize);
  buf = v6;
  if ( !v6 )
    return 0;
  v8 = (st_lwVMap *)Mem_ClearedAlloc(44, 0xEu);
  v9 = v8;
  if ( !v8 )
  {
    Mem_Free(v6);
    return 0;
  }
  v8->perpoly = perpoly;
  v29 = v6;
  flen = 0;
  v10 = sgetU4(&v29);
  v11 = flen == -9999;
  v9->type = v10;
  v12 = v29;
  if ( v11 )
  {
    v13 = 0;
  }
  else
  {
    flen += 2;
    v29 += 2;
    HIBYTE(v14) = *v12;
    LOBYTE(v14) = v12[1];
    v13 = v14;
  }
  v9->dim = v13;
  v15 = sgetS0(&v29);
  v16 = flen;
  v9->name = v15;
  v17 = v29;
  v18 = &v6[cksize];
  rlen = v16;
  if ( v29 < &v6[cksize] )
  {
    v19 = 4 * v9->dim;
    do
    {
      if ( flen != -9999 )
      {
        if ( *v17 == 0xFF )
        {
          flen += 4;
          v17 += 4;
        }
        else
        {
          flen += 2;
          v17 += 2;
        }
        v29 = v17;
      }
      if ( perpoly )
      {
        sgetVX(&v29);
        v17 = v29;
      }
      v17 += v19;
      ++v5;
      v29 = v17;
    }
    while ( v17 < v18 );
    v6 = buf;
  }
  v9->nverts = v5;
  v20 = (int *)Mem_ClearedAlloc(4 * v5, 0xEu);
  v9->vindex = v20;
  if ( !v20 )
    goto Fail_3;
  if ( perpoly )
  {
    v21 = (int *)Mem_ClearedAlloc(4 * v5, 0xEu);
    v9->pindex = v21;
    if ( !v21 )
      goto Fail_3;
  }
  if ( v9->dim > 0 )
  {
    v22 = (float **)Mem_ClearedAlloc(4 * v5, 0xEu);
    v9->val = v22;
    if ( !v22 || (v23 = (char *)Mem_ClearedAlloc(4 * v5 * v9->dim, 0xEu)) == 0 )
    {
Fail_3:
      Mem_Free(v6);
      lwFreeVMap(v9);
      return 0;
    }
    for ( i = 0; i < v5; ++i )
      v9->val[i] = (float *)&v23[4 * i * v9->dim];
  }
  v29 = &v6[rlen];
  if ( v5 > 0 )
  {
    v25 = 0;
    rlen = v5;
    do
    {
      v9->vindex[v25] = sgetVX(&v29);
      if ( perpoly )
        v9->pindex[v25] = sgetVX(&v29);
      v26 = 0;
      if ( v9->dim > 0 )
      {
        v27 = v29;
        do
        {
          if ( flen == -9999 )
          {
            v28 = 0.0;
          }
          else
          {
            v30 = *(float *)v27;
            BigRevBytes(&v30, 4, 1);
            flen += 4;
            v27 += 4;
            if ( (LODWORD(v30) & 0x7F800000) == 0 && (LODWORD(v30) & 0x7FFFFF) != 0 )
              v30 = 0.0;
            v28 = v30;
          }
          v9->val[v25][v26++] = v28;
        }
        while ( v26 < v9->dim );
        v29 = v27;
      }
      ++v25;
      --rlen;
    }
    while ( rlen );
    v6 = buf;
  }
  Mem_Free(v6);
  return v9;
}

// FUNC: int __cdecl lwGetPointVMaps(struct st_lwPointList *,struct st_lwVMap *)
int __cdecl lwGetPointVMaps(st_lwPointList *point, st_lwVMap *vmap)
{
  st_lwVMap *i; // ecx
  int j; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // edi
  int nvmaps; // eax
  st_lwPoint *pt; // eax
  st_lwVMap *k; // edx
  int m; // ecx
  st_lwPoint *v11; // edi
  int v12; // eax
  int v13; // ebx

  for ( i = vmap; i; i = i->next )
  {
    if ( !i->perpoly )
    {
      for ( j = 0; j < i->nverts; ++j )
      {
        v4 = i->vindex[j];
        ++point->pt[v4].nvmaps;
      }
    }
  }
  v5 = 0;
  if ( point->count > 0 )
  {
    v6 = 0;
    do
    {
      nvmaps = point->pt[v6].nvmaps;
      if ( nvmaps )
      {
        point->pt[v6].vm = (st_lwVMapPt *)Mem_ClearedAlloc(8 * nvmaps, 0xEu);
        pt = point->pt;
        if ( !pt[v6].vm )
          return 0;
        pt[v6].nvmaps = 0;
      }
      ++v5;
      ++v6;
    }
    while ( v5 < point->count );
  }
  for ( k = vmap; k; k = k->next )
  {
    if ( !k->perpoly )
    {
      for ( m = 0; m < k->nverts; ++m )
      {
        v11 = point->pt;
        v12 = k->vindex[m];
        v13 = v11[v12].nvmaps;
        v11[v12].vm[v13].vmap = k;
        point->pt[v12].vm[v13].index = m;
        ++point->pt[v12].nvmaps;
      }
    }
  }
  return 1;
}

// FUNC: int __cdecl lwGetPolyVMaps(struct st_lwPolygonList *,struct st_lwVMap *)
int __cdecl lwGetPolyVMaps(st_lwPolygonList *polygon, st_lwVMap *vmap)
{
  st_lwVMap *j; // esi
  int k; // edi
  st_lwPolygon *v4; // eax
  int nverts; // edx
  int v6; // ecx
  st_lwPolVert *v; // eax
  st_lwPolygonList *v8; // edx
  int v9; // edi
  st_lwPolygon *pol; // eax
  int v11; // ebp
  int v12; // ebx
  st_lwPolVert *v13; // esi
  int nvmaps; // eax
  st_lwPolVert *v15; // esi
  st_lwVMapPt *v16; // eax
  st_lwVMap *m; // esi
  int n; // edi
  int v19; // eax
  int v20; // edx
  int v21; // ecx
  _DWORD *v22; // eax
  int i; // [esp+10h] [ebp-4h]

  for ( j = vmap; j; j = j->next )
  {
    if ( j->perpoly )
    {
      for ( k = 0; k < j->nverts; ++k )
      {
        v4 = &polygon->pol[j->pindex[k]];
        nverts = v4->nverts;
        v6 = 0;
        if ( nverts > 0 )
        {
          v = v4->v;
          while ( j->vindex[k] != v->index )
          {
            ++v6;
            ++v;
            if ( v6 >= nverts )
              goto LABEL_10;
          }
          ++v->nvmaps;
        }
LABEL_10:
        ;
      }
    }
  }
  v8 = polygon;
  i = 0;
  if ( polygon->count > 0 )
  {
    v9 = 0;
    do
    {
      pol = v8->pol;
      v11 = 0;
      if ( pol[v9].nverts > 0 )
      {
        v12 = 0;
        do
        {
          v13 = pol[v9].v;
          nvmaps = v13[v12].nvmaps;
          v15 = &v13[v12];
          if ( nvmaps )
          {
            v16 = (st_lwVMapPt *)Mem_ClearedAlloc(8 * nvmaps, 0xEu);
            v15->vm = v16;
            if ( !v16 )
              return 0;
            v8 = polygon;
            v15->nvmaps = 0;
          }
          pol = v8->pol;
          ++v11;
          ++v12;
        }
        while ( v11 < pol[v9].nverts );
      }
      ++v9;
      ++i;
    }
    while ( i < v8->count );
  }
  for ( m = vmap; m; m = m->next )
  {
    if ( m->perpoly )
    {
      for ( n = 0; n < m->nverts; ++n )
      {
        v19 = (int)&v8->pol[m->pindex[n]];
        v20 = *(_DWORD *)(v19 + 32);
        v21 = 0;
        if ( v20 > 0 )
        {
          v22 = *(_DWORD **)(v19 + 36);
          while ( m->vindex[n] != *v22 )
          {
            ++v21;
            v22 += 6;
            if ( v21 >= v20 )
              goto LABEL_31;
          }
          *(_DWORD *)(v22[5] + 8 * v22[4]) = m;
          *(_DWORD *)(v22[5] + 8 * v22[4]++ + 4) = n;
        }
LABEL_31:
        v8 = polygon;
      }
    }
  }
  return 1;
}

// FUNC: void __cdecl lwFreeClip(struct st_lwClip *)
void __cdecl lwFreeClip(st_lwClip *clip)
{
  st_lwPlugin *ifilter; // esi
  st_lwPlugin *next; // edi
  st_lwPlugin *pfilter; // esi
  st_lwPlugin *v4; // edi
  unsigned int type; // eax

  if ( clip )
  {
    ifilter = clip->ifilter;
    if ( ifilter )
    {
      do
      {
        next = ifilter->next;
        if ( ifilter->ord )
          Mem_Free(ifilter->ord);
        if ( ifilter->name )
          Mem_Free(ifilter->name);
        if ( ifilter->data )
          Mem_Free(ifilter->data);
        Mem_Free(ifilter);
        ifilter = next;
      }
      while ( next );
    }
    pfilter = clip->pfilter;
    if ( pfilter )
    {
      do
      {
        v4 = pfilter->next;
        if ( pfilter->ord )
          Mem_Free(pfilter->ord);
        if ( pfilter->name )
          Mem_Free(pfilter->name);
        if ( pfilter->data )
          Mem_Free(pfilter->data);
        Mem_Free(pfilter);
        pfilter = v4;
      }
      while ( v4 );
    }
    type = clip->type;
    if ( type > 0x53544343 )
    {
      if ( type != 1398032716 && type != 1481786694 )
        goto LABEL_28;
    }
    else if ( type != 1398031171 )
    {
      if ( type != 1095649613 && type != 1230194001 )
        goto LABEL_28;
      if ( clip->source.xref.index )
        Mem_Free(clip->source.seq.suffix);
    }
    if ( clip->source.still.name )
      Mem_Free(clip->source.still.name);
LABEL_28:
    Mem_Free(clip);
  }
}

// FUNC: struct st_lwClip * __cdecl lwGetClip(class idFile *,int)
st_lwClip *__cdecl lwGetClip(idFile *fp, int cksize)
{
  st_lwClip *v2; // eax
  st_lwClip *v3; // edi
  idFile_vtbl *v4; // eax
  int v5; // ebp
  unsigned __int16 U2; // bx
  unsigned int type; // eax
  unsigned __int16 v8; // bx
  int v9; // ecx
  char *v10; // eax
  int v11; // ecx
  char *S0; // eax
  int v13; // ebx
  int v14; // eax
  unsigned int U4; // ebp
  unsigned __int16 v16; // ax
  unsigned __int16 v17; // ax
  int v18; // ecx
  _DWORD *v19; // ebx
  int v20; // edx
  int v21; // eax
  int v22; // eax
  unsigned __int16 sz; // [esp+10h] [ebp-8h]
  int pos; // [esp+14h] [ebp-4h]

  v2 = (st_lwClip *)Mem_ClearedAlloc(116, 0xEu);
  v3 = v2;
  if ( !v2 )
    goto Fail_4;
  v2->contrast.val = 1.0;
  v2->brightness.val = 1.0;
  v2->saturation.val = 1.0;
  v2->gamma.val = 1.0;
  v4 = fp->__vftable;
  flen = 0;
  v5 = v4->Tell(fp);
  pos = v5;
  v3->index = getU4(fp);
  v3->type = getU4(fp);
  U2 = getU2(fp);
  if ( flen < 0 )
    goto Fail_4;
  type = v3->type;
  v8 = (U2 & 1) + U2;
  v9 = 0;
  flen = 0;
  if ( type > 0x53544343 )
  {
    if ( type == 1398032716 )
    {
      S0 = getS0(fp);
    }
    else
    {
      if ( type != 1481786694 )
        goto LABEL_16;
      v3->source.xref.index = getU4(fp);
      S0 = getS0(fp);
    }
    goto LABEL_14;
  }
  switch ( type )
  {
    case 0x53544343u:
      v3->source.xref.index = (__int16)getU2(fp);
      v3->source.seq.digits = (__int16)getU2(fp);
      S0 = getS0(fp);
LABEL_14:
      v3->source.still.name = S0;
LABEL_15:
      v9 = flen;
      if ( flen < 0 )
        goto Fail_4;
      break;
    case 0x414E494Du:
      v3->source.still.name = getS0(fp);
      v10 = getS0(fp);
      v11 = v8 - flen;
      v3->source.xref.index = (int)v10;
      v3->source.seq.digits = (int)getbytes(fp, v11);
      goto LABEL_15;
    case 0x49534551u:
      v3->source.seq.digits = getU1(fp);
      v3->source.seq.flags = getU1(fp);
      v3->source.seq.offset = (__int16)getU2(fp);
      v3->source.seq.start = (__int16)getU2(fp);
      v3->source.seq.end = (__int16)getU2(fp);
      v3->source.still.name = getS0(fp);
      v3->source.xref.index = (int)getS0(fp);
      goto LABEL_15;
  }
LABEL_16:
  if ( v9 <= v8 )
  {
    if ( v9 < v8 )
      fp->Seek(fp, v8 - v9, FS_SEEK_CUR);
    v13 = cksize;
    v14 = fp->Tell(fp) - v5;
    if ( cksize >= v14 )
    {
      if ( cksize == v14 )
        return v3;
      U4 = getU4(fp);
      v16 = getU2(fp);
      if ( flen >= 0 )
      {
        while ( 1 )
        {
          v17 = (v16 & 1) + v16;
          v18 = 0;
          sz = v17;
          flen = 0;
          if ( U4 > 0x49464C54 )
          {
            if ( U4 > 0x53415452 )
            {
              if ( U4 != 1414090053 )
                goto LABEL_47;
              v3->start_time = getF4(fp);
              v3->duration = getF4(fp);
              v3->frame_rate = getF4(fp);
              goto LABEL_45;
            }
            switch ( U4 )
            {
              case 0x53415452u:
                v3->saturation.val = getF4(fp);
                v3->saturation.eindex = getVX(fp);
                break;
              case 0x4E454741u:
                v3->negative = getU2(fp);
                break;
              case 0x50464C54u:
LABEL_37:
                v19 = Mem_ClearedAlloc(24, 0xEu);
                if ( !v19 )
                  goto Fail_4;
                v19[3] = getS0(fp);
                v20 = getU2(fp);
                v21 = sz - flen;
                v19[4] = v20;
                v19[5] = getbytes(fp, v21);
                if ( U4 == 1229343828 )
                {
                  lwListAdd((void **)&v3->ifilter, v19);
                  v13 = cksize;
                  ++v3->nifilters;
                }
                else
                {
                  lwListAdd((void **)&v3->pfilter, v19);
                  v13 = cksize;
                  ++v3->npfilters;
                }
                break;
              default:
                goto LABEL_47;
            }
          }
          else
          {
            if ( U4 == 1229343828 )
              goto LABEL_37;
            if ( U4 > 0x47414D4D )
            {
              if ( U4 != 1213547808 )
                goto LABEL_47;
              v3->hue.val = getF4(fp);
              v3->hue.eindex = getVX(fp);
            }
            else
            {
              switch ( U4 )
              {
                case 0x47414D4Du:
                  v3->gamma.val = getF4(fp);
                  v3->gamma.eindex = getVX(fp);
                  break;
                case 0x42524954u:
                  v3->brightness.val = getF4(fp);
                  v3->brightness.eindex = getVX(fp);
                  break;
                case 0x434F4E54u:
                  v3->contrast.val = getF4(fp);
                  v3->contrast.eindex = getVX(fp);
                  break;
                default:
                  goto LABEL_47;
              }
            }
          }
LABEL_45:
          v18 = flen;
          if ( flen < 0 )
            break;
          v17 = sz;
LABEL_47:
          if ( v18 <= v17 )
          {
            if ( v18 < v17 )
              fp->Seek(fp, v17 - v18, FS_SEEK_CUR);
            v22 = fp->Tell(fp) - pos;
            if ( v13 >= v22 )
            {
              if ( v13 == v22 )
                return v3;
              flen = 0;
              U4 = getU4(fp);
              v16 = getU2(fp);
              if ( flen == 6 )
                continue;
            }
          }
          break;
        }
      }
    }
  }
Fail_4:
  lwFreeClip(v3);
  return 0;
}

// FUNC: void __cdecl lwFreeEnvelope(struct st_lwEnvelope *)
void __cdecl lwFreeEnvelope(st_lwEnvelope *env)
{
  st_lwKey *key; // eax
  st_lwKey *next; // esi
  st_lwPlugin *cfilter; // esi
  st_lwPlugin *v4; // edi

  if ( env )
  {
    if ( env->name )
      Mem_Free(env->name);
    key = env->key;
    if ( key )
    {
      do
      {
        next = key->next;
        Mem_Free(key);
        key = next;
      }
      while ( next );
    }
    cfilter = env->cfilter;
    if ( cfilter )
    {
      do
      {
        v4 = cfilter->next;
        if ( cfilter->ord )
          Mem_Free(cfilter->ord);
        if ( cfilter->name )
          Mem_Free(cfilter->name);
        if ( cfilter->data )
          Mem_Free(cfilter->data);
        Mem_Free(cfilter);
        cfilter = v4;
      }
      while ( v4 );
    }
    Mem_Free(env);
  }
}

// FUNC: struct st_lwEnvelope * __cdecl lwGetEnvelope(class idFile *,int)
st_lwEnvelope *__cdecl lwGetEnvelope(idFile *fp, int cksize)
{
  st_lwEnvelope *v2; // edi
  idFile_vtbl *v3; // eax
  unsigned int U4; // esi
  unsigned __int16 U2; // ax
  unsigned __int16 v6; // ax
  int v7; // ecx
  st_lwKey *v8; // esi
  _DWORD *v9; // esi
  unsigned __int16 v10; // ax
  int v11; // ebp
  int i; // esi
  unsigned int shape; // eax
  unsigned int v14; // eax
  int v15; // eax
  float *v16; // ecx
  float v17; // ecx
  float v18; // edx
  int v19; // eax
  int v21; // [esp-Ch] [ebp-3Ch]
  st_lwKey *key; // [esp+10h] [ebp-20h]
  unsigned __int16 sz; // [esp+14h] [ebp-1Ch]
  st_lwEnvelope *env; // [esp+18h] [ebp-18h]
  int pos; // [esp+1Ch] [ebp-14h]
  float f[4]; // [esp+20h] [ebp-10h] BYREF

  key = 0;
  v2 = (st_lwEnvelope *)Mem_ClearedAlloc(44, 0xEu);
  env = v2;
  if ( v2 )
  {
    v3 = fp->__vftable;
    flen = 0;
    pos = v3->Tell(fp);
    v2->index = getVX(fp);
    U4 = getU4(fp);
    U2 = getU2(fp);
    if ( flen >= 0 )
    {
      do
      {
        v6 = (U2 & 1) + U2;
        v7 = 0;
        sz = v6;
        flen = 0;
        if ( U4 > 0x504F5354 )
        {
          switch ( U4 )
          {
            case 0x50524520u:
              v2->behavior[0] = getU2(fp);
              break;
            case 0x5350414Eu:
              if ( !key )
                goto Fail_5;
              key->shape = getU4(fp);
              v11 = (sz - 4) / 4;
              if ( v11 > 4 )
                v11 = 4;
              for ( i = 0; i < v11; ++i )
                f[i] = getF4(fp);
              shape = key->shape;
              if ( shape > 0x4845524D )
              {
                if ( shape == 1413693984 )
                {
                  v17 = f[1];
                  key->tension = f[0];
                  v18 = f[2];
                  key->continuity = v17;
                  key->bias = v18;
                }
              }
              else if ( shape == 1212502605 || (v14 = shape - 1111841330) == 0 || v14 == 23 )
              {
                v15 = 0;
                if ( v11 >= 4 )
                {
                  v16 = &key->param[1];
                  do
                  {
                    *(v16 - 1) = f[v15];
                    *v16 = f[v15 + 1];
                    v16[1] = f[v15 + 2];
                    v16[2] = f[v15 + 3];
                    v15 += 4;
                    v16 += 4;
                  }
                  while ( v15 < v11 - 3 );
                }
                if ( v15 < v11 )
                {
                  qmemcpy(&key->param[v15], &f[v15], 4 * (v11 - v15));
                  v2 = env;
                }
              }
              break;
            case 0x54595045u:
              v2->type = getU2(fp);
              break;
            default:
              goto LABEL_37;
          }
        }
        else
        {
          switch ( U4 )
          {
            case 0x504F5354u:
              v2->behavior[1] = getU2(fp);
              break;
            case 0x4348414Eu:
              v9 = Mem_ClearedAlloc(24, 0xEu);
              if ( !v9 )
                goto Fail_5;
              v9[3] = getS0(fp);
              v10 = getU2(fp);
              v21 = sz - flen;
              v9[4] = v10;
              v9[5] = getbytes(fp, v21);
              lwListAdd((void **)&v2->cfilter, v9);
              ++v2->ncfilters;
              break;
            case 0x4B455920u:
              v8 = (st_lwKey *)Mem_ClearedAlloc(48, 0xEu);
              key = v8;
              if ( !v8 )
                goto Fail_5;
              v8->time = getF4(fp);
              v8->value = getF4(fp);
              lwListInsert((void **)&v2->key, v8, (int (__cdecl *)(void *, void *))compare_keys);
              ++v2->nkeys;
              break;
            case 0x4E414D45u:
              v2->name = getS0(fp);
              break;
            default:
              goto LABEL_37;
          }
        }
        v7 = flen;
        if ( flen < 0 )
          break;
        v6 = sz;
LABEL_37:
        if ( v7 > v6 )
          break;
        if ( v7 < v6 )
          fp->Seek(fp, v6 - v7, FS_SEEK_CUR);
        v19 = fp->Tell(fp) - pos;
        if ( cksize < v19 )
          break;
        if ( cksize == v19 )
          return v2;
        flen = 0;
        U4 = getU4(fp);
        U2 = getU2(fp);
      }
      while ( flen == 6 );
    }
  }
Fail_5:
  lwFreeEnvelope(v2);
  return 0;
}

// FUNC: void __cdecl lwFreeLayer(struct st_lwLayer *)
void __cdecl lwFreeLayer(st_lwLayer *layer)
{
  st_lwVMap *vmap; // esi
  st_lwVMap *next; // edi
  void **val; // eax
  void *v4; // eax

  if ( layer )
  {
    if ( layer->name )
      Mem_Free(layer->name);
    lwFreePoints(&layer->point);
    lwFreePolygons(&layer->polygon);
    vmap = layer->vmap;
    if ( vmap )
    {
      do
      {
        next = vmap->next;
        if ( vmap->name )
          Mem_Free(vmap->name);
        if ( vmap->vindex )
          Mem_Free(vmap->vindex);
        if ( vmap->pindex )
          Mem_Free(vmap->pindex);
        val = (void **)vmap->val;
        if ( val )
        {
          v4 = *val;
          if ( v4 )
            Mem_Free(v4);
          Mem_Free(vmap->val);
        }
        Mem_Free(vmap);
        vmap = next;
      }
      while ( next );
    }
    Mem_Free(layer);
  }
}

// FUNC: void __cdecl lwFreeObject(struct st_lwObject *)
void __cdecl lwFreeObject(st_lwObject *object)
{
  st_lwLayer *layer; // eax
  st_lwLayer *next; // esi
  st_lwEnvelope *env; // eax
  st_lwEnvelope *v4; // esi
  st_lwClip *clip; // eax
  st_lwClip *v6; // esi
  st_lwSurface *surf; // eax
  st_lwSurface *v8; // esi

  if ( object )
  {
    layer = object->layer;
    if ( layer )
    {
      do
      {
        next = layer->next;
        lwFreeLayer(layer);
        layer = next;
      }
      while ( next );
    }
    env = object->env;
    if ( env )
    {
      do
      {
        v4 = env->next;
        lwFreeEnvelope(env);
        env = v4;
      }
      while ( v4 );
    }
    clip = object->clip;
    if ( clip )
    {
      do
      {
        v6 = clip->next;
        lwFreeClip(clip);
        clip = v6;
      }
      while ( v6 );
    }
    surf = object->surf;
    if ( surf )
    {
      do
      {
        v8 = surf->next;
        lwFreeSurface(surf);
        surf = v8;
      }
      while ( v8 );
    }
    lwFreeTags(&object->taglist);
    Mem_Free(object);
  }
}

// FUNC: struct st_lwSurface * __cdecl lwGetSurface5(class idFile *,int,struct st_lwObject *)
st_lwSurface *__cdecl lwGetSurface5(idFile *fp, int cksize, st_lwObject *obj)
{
  st_lwTexture *texture; // edi
  st_lwSurface *v4; // eax
  st_lwSurface *v5; // ebx
  idFile_vtbl *v6; // eax
  unsigned int U4; // esi
  unsigned __int16 U2; // ax
  unsigned __int16 v9; // ax
  int v10; // edx
  char *v11; // eax
  char *v12; // eax
  char *v13; // eax
  unsigned __int16 v14; // ax
  char *v15; // eax
  char *v16; // eax
  char *v17; // eax
  st_lwPlugin *v18; // esi
  double F4; // st7
  char *v20; // eax
  st_lwTexture *v21; // eax
  st_lwTexture *v22; // ecx
  int *p_projection; // esi
  bool v24; // zf
  float *v25; // esi
  float *v26; // esi
  char v27; // cl
  int v28; // eax
  char *S0; // eax
  float *val; // esi
  char *v31; // eax
  int j; // esi
  int i; // [esp+10h] [ebp-2Ch]
  st_lwTexture *tex; // [esp+14h] [ebp-28h]
  unsigned __int16 sz; // [esp+18h] [ebp-24h]
  st_lwSurface *surf; // [esp+1Ch] [ebp-20h]
  st_lwPlugin *shdr; // [esp+20h] [ebp-1Ch]
  int v39; // [esp+24h] [ebp-18h]
  int v40; // [esp+24h] [ebp-18h]
  int v41; // [esp+24h] [ebp-18h]
  int v42; // [esp+24h] [ebp-18h]
  int U1; // [esp+28h] [ebp-14h]
  int pos; // [esp+2Ch] [ebp-10h]
  float v[3]; // [esp+30h] [ebp-Ch] BYREF

  texture = 0;
  tex = 0;
  shdr = 0;
  i = 0;
  v4 = (st_lwSurface *)Mem_ClearedAlloc(244, 0xEu);
  v5 = v4;
  surf = v4;
  if ( v4 )
  {
    v4->color.rgb[0] = 0.78430998;
    v4->color.rgb[1] = 0.78430998;
    v4->color.rgb[2] = 0.78430998;
    v4->diffuse.val = 1.0;
    v4->glossiness.val = 0.40000001;
    v4->bump.val = 1.0;
    v4->eta.val = 1.0;
    v4->sideflags = 1;
    v6 = fp->__vftable;
    flen = 0;
    pos = v6->Tell(fp);
    v5->name = getS0(fp);
    U4 = getU4(fp);
    U2 = getU2(fp);
    if ( flen >= 0 )
    {
      while ( 1 )
      {
        v9 = (U2 & 1) + U2;
        v10 = 0;
        sz = v9;
        flen = 0;
        if ( U4 <= 0x53544558 )
          break;
        if ( U4 > 0x544F5043 )
        {
          if ( U4 <= 0x5456414C )
          {
            if ( U4 == 1414938956 )
            {
              texture->param.proc.value[0] = (double)(__int16)getU2(fp) * 0.00390625;
            }
            else if ( U4 > 0x5453495A )
            {
              if ( U4 != 1414808920 )
                goto LABEL_145;
              v31 = (char *)getbytes(fp, v9);
              texture = get_texture(v31);
              tex = texture;
              lwListAdd((void **)&v5->transparency.val.tex, texture);
            }
            else
            {
              switch ( U4 )
              {
                case 0x5453495Au:
                  val = texture->tmap.size.val;
                  v42 = 3;
                  i = 3;
                  do
                  {
                    *val++ = getF4(fp);
                    --v42;
                  }
                  while ( v42 );
                  break;
                case 0x5452414Eu:
                  v5->transparency.val.val = (double)(__int16)getU2(fp) * 0.00390625;
                  break;
                case 0x54524546u:
                  texture->tmap.ref_object = (char *)getbytes(fp, v9);
                  break;
                default:
                  goto LABEL_145;
              }
            }
            goto LABEL_143;
          }
          if ( U4 <= 0x564C554D )
          {
            switch ( U4 )
            {
              case 0x564C554Du:
                v5->luminosity.val = getF4(fp);
                break;
              case 0x5456454Cu:
                for ( j = 0; j < 3; ++j )
                  v[j] = getF4(fp);
                i = j;
                texture->tmap.center.eindex = add_tvel(texture->tmap.center.val, v, &obj->env, &obj->nenvs);
                break;
              case 0x56444946u:
                v5->diffuse.val = getF4(fp);
                break;
              default:
                goto LABEL_145;
            }
            goto LABEL_143;
          }
          if ( U4 != 1448300611 )
            goto LABEL_145;
          F4 = getF4(fp);
LABEL_142:
          v5->specularity.val = F4;
          goto LABEL_143;
        }
        if ( U4 == 1414484035 )
        {
          texture->opacity.val = getF4(fp);
        }
        else if ( U4 > 0x5446414C )
        {
          if ( U4 > 0x54465031 )
          {
            if ( U4 != 1414090055 )
              goto LABEL_145;
            S0 = getS0(fp);
            v5 = surf;
            tex->param.imap.cindex = (int)add_clip(S0, &obj->clip, &obj->nclips);
            texture = tex;
          }
          else if ( U4 == 1413894193 )
          {
            if ( texture->type != 1229799760 )
              goto LABEL_145;
            texture->param.imap.wraph.val = getF4(fp);
          }
          else if ( U4 == 1413893191 )
          {
            v27 = getU2(fp);
            if ( (v27 & 1) != 0 )
            {
              v28 = 0;
              i = 0;
            }
            else
            {
              v28 = i;
            }
            if ( (v27 & 2) != 0 )
            {
              v28 = 1;
              i = 1;
            }
            if ( (v27 & 4) != 0 )
            {
              v28 = 2;
              i = 2;
            }
            v24 = texture->type == 1229799760;
            texture->axis = v28;
            if ( v24 )
              texture->param.imap.axis = v28;
            else
              texture->param.imap.cindex = v28;
            if ( (v27 & 8) != 0 )
              texture->tmap.coord_sys = 1;
            if ( (v27 & 0x10) != 0 )
              texture->negative = 1;
            if ( (v27 & 0x20) != 0 )
              texture->param.imap.pblend = 1;
            if ( (v27 & 0x40) != 0 )
            {
              texture->param.imap.aa_strength = 1.0;
              texture->param.imap.aas_flags = 1;
            }
          }
          else
          {
            if ( U4 != 1413894192 || texture->type != 1229799760 )
              goto LABEL_145;
            texture->param.imap.wrapw.val = getF4(fp);
          }
        }
        else if ( U4 == 1413890380 )
        {
          v26 = texture->tmap.falloff.val;
          v41 = 3;
          i = 3;
          do
          {
            *v26++ = getF4(fp);
            --v41;
          }
          while ( v41 );
        }
        else if ( U4 > 0x54434C52 )
        {
          if ( U4 != 1413698642 )
            goto LABEL_145;
          v25 = texture->tmap.center.val;
          v40 = 3;
          i = 3;
          do
          {
            *v25++ = getF4(fp);
            --v40;
          }
          while ( v40 );
        }
        else if ( U4 == 1413696594 )
        {
          if ( texture->type != 1347571523 )
            goto LABEL_145;
          p_projection = &texture->param.imap.projection;
          v39 = 3;
          i = 3;
          do
          {
            U1 = getU1(fp);
            ++p_projection;
            v24 = v39-- == 1;
            *((float *)p_projection - 1) = (double)U1 * 0.0039215689;
          }
          while ( !v24 );
        }
        else if ( U4 == 1413562707 )
        {
          texture->param.imap.aa_strength = getF4(fp);
          texture->param.imap.aas_flags = 1;
        }
        else
        {
          if ( U4 != 1413565776 || texture->type != 1229799760 )
            goto LABEL_145;
          texture->param.imap.amplitude.val = getF4(fp);
        }
LABEL_143:
        v10 = flen;
        if ( flen < 0 )
          goto Fail_6;
        v9 = sz;
LABEL_145:
        if ( v10 > v9 )
          goto Fail_6;
        if ( v10 < v9 )
          fp->Seek(fp, v9 - v10, FS_SEEK_CUR);
        if ( cksize <= fp->Tell(fp) - pos )
          return v5;
        flen = 0;
        U4 = getU4(fp);
        U2 = getU2(fp);
        if ( flen != 6 )
          goto Fail_6;
      }
      if ( U4 == 1398031704 )
      {
        v20 = (char *)getbytes(fp, v9);
        texture = get_texture(v20);
        v21 = v5->specularity.tex;
        tex = texture;
        if ( v21 )
        {
          do
          {
            v22 = v21;
            v21 = v21->next;
          }
          while ( v21 );
          v22->next = texture;
          texture->prev = v22;
        }
        else
        {
          v5->specularity.tex = texture;
        }
        goto LABEL_143;
      }
      if ( U4 <= 0x5245464C )
      {
        if ( U4 == 1380271692 )
        {
          v5->reflection.val.val = (double)(__int16)getU2(fp) * 0.00390625;
        }
        else if ( U4 > 0x44544558 )
        {
          if ( U4 > 0x4C544558 )
          {
            if ( U4 != 1280658761 )
              goto LABEL_145;
            v5->luminosity.val = (double)(__int16)getU2(fp) * 0.00390625;
          }
          else
          {
            switch ( U4 )
            {
              case 0x4C544558u:
                v15 = (char *)getbytes(fp, v9);
                texture = get_texture(v15);
                tex = texture;
                lwListAdd((void **)&v5->luminosity.tex, texture);
                break;
              case 0x464C4147u:
                v14 = getU2(fp);
                if ( (v14 & 4) != 0 )
                  v5->smooth = 1.56207;
                if ( (v14 & 8) != 0 )
                  v5->color_hilite.val = 1.0;
                if ( (v14 & 0x10) != 0 )
                  v5->color_filter.val = 1.0;
                if ( (v14 & 0x80u) != 0 )
                  v5->dif_sharp.val = 0.5;
                if ( (v14 & 0x100) != 0 )
                  v5->sideflags = 3;
                if ( (v14 & 0x200) != 0 )
                  v5->add_trans.val = 1.0;
                break;
              case 0x474C4F53u:
                v5->glossiness.val = __FYL2X__((double)getU2(fp), 0.69314718055994528623) * 0.048089873;
                break;
              default:
                goto LABEL_145;
            }
          }
        }
        else if ( U4 == 1146373464 )
        {
          v13 = (char *)getbytes(fp, v9);
          texture = get_texture(v13);
          tex = texture;
          lwListAdd((void **)&v5->diffuse.tex, texture);
        }
        else if ( U4 > 0x43544558 )
        {
          if ( U4 != 1145652806 )
            goto LABEL_145;
          v5->diffuse.val = (double)(__int16)getU2(fp) * 0.00390625;
        }
        else
        {
          switch ( U4 )
          {
            case 0x43544558u:
              v12 = (char *)getbytes(fp, v9);
              texture = get_texture(v12);
              tex = texture;
              lwListAdd((void **)&v5->color.tex, texture);
              break;
            case 0x42544558u:
              v11 = (char *)getbytes(fp, v9);
              texture = get_texture(v11);
              tex = texture;
              lwListAdd((void **)&v5->bump.tex, texture);
              break;
            case 0x434F4C52u:
              v5->color.rgb[0] = (double)getU1(fp) * 0.0039215689;
              v5->color.rgb[1] = (double)getU1(fp) * 0.0039215689;
              v5->color.rgb[2] = (double)getU1(fp) * 0.0039215689;
              break;
            default:
              goto LABEL_145;
          }
        }
        goto LABEL_143;
      }
      if ( U4 <= 0x52544558 )
      {
        if ( U4 == 1381254488 )
        {
          v17 = (char *)getbytes(fp, v9);
          texture = get_texture(v17);
          tex = texture;
          lwListAdd((void **)&v5->reflection.val.tex, texture);
        }
        else if ( U4 > 0x52494E44 )
        {
          if ( U4 != 1381187918 )
            goto LABEL_145;
          v5->reflection.seam_angle = getF4(fp);
        }
        else
        {
          switch ( U4 )
          {
            case 0x52494E44u:
              v5->eta.val = getF4(fp);
              break;
            case 0x52464C54u:
              v5->reflection.options = getU2(fp);
              break;
            case 0x52494D47u:
              v16 = getS0(fp);
              texture = tex;
              surf->reflection.cindex = (int)add_clip(v16, &obj->clip, &obj->nclips);
              surf->reflection.options = 3;
              v5 = surf;
              break;
            default:
              goto LABEL_145;
          }
        }
        goto LABEL_143;
      }
      if ( U4 <= 0x534D414E )
      {
        switch ( U4 )
        {
          case 0x534D414Eu:
            v5->smooth = getF4(fp);
            break;
          case 0x53444154u:
            shdr->data = getbytes(fp, v9);
            break;
          case 0x53484452u:
            v18 = (st_lwPlugin *)Mem_ClearedAlloc(24, 0xEu);
            shdr = v18;
            if ( !v18 )
              goto Fail_6;
            v18->name = (char *)getbytes(fp, sz);
            lwListAdd((void **)&v5->shader, v18);
            ++v5->nshaders;
            break;
          default:
            goto LABEL_145;
        }
        goto LABEL_143;
      }
      if ( U4 != 1397769539 )
        goto LABEL_145;
      F4 = (double)(__int16)getU2(fp) * 0.00390625;
      goto LABEL_142;
    }
Fail_6:
    lwFreeSurface(v5);
  }
  return 0;
}

// FUNC: int __cdecl lwGetPolygons5(class idFile *,int,struct st_lwPolygonList *,int)
int __cdecl lwGetPolygons5(idFile *fp, st_lwPolVert *cksize, st_lwPolVert *plist, int ptoffset)
{
  int v4; // ebx
  st_lwPolygon *v5; // edi
  unsigned __int8 *v7; // eax
  unsigned __int8 *v8; // ebx
  int v9; // ebp
  unsigned __int8 *v10; // esi
  int v11; // ecx
  int v12; // eax
  __int16 v13; // dx
  st_lwPolygonList *v15; // ebx
  st_lwPolygon *pol; // eax
  unsigned __int8 *v17; // esi
  st_lwPolygon *v18; // edx
  int v19; // ecx
  int v20; // edi
  unsigned __int8 *v21; // eax
  unsigned __int16 v22; // ax
  bool v23; // zf
  int v24; // ebx
  int v25; // ebp
  unsigned __int8 *v26; // eax
  unsigned __int16 v27; // ax
  unsigned __int16 v28; // dx
  int v29; // eax
  st_lwPolygon *pp; // [esp+8h] [ebp-10h]
  unsigned __int8 *buf; // [esp+Ch] [ebp-Ch]
  int v32; // [esp+10h] [ebp-8h] BYREF
  st_lwPolygon *v33; // [esp+14h] [ebp-4h]

  v4 = (int)cksize;
  v5 = 0;
  if ( !cksize )
    return 1;
  flen = 0;
  v7 = (unsigned __int8 *)getbytes(fp, (int)cksize);
  buf = v7;
  if ( v7 )
  {
    v8 = &v7[v4];
    v9 = 0;
    v10 = v7;
    if ( v7 < v8 )
    {
      v11 = flen;
      do
      {
        v12 = (int)v10;
        if ( v11 == -9999 )
        {
          LOWORD(v12) = 0;
        }
        else
        {
          v11 += 2;
          v10 += 2;
          HIBYTE(v13) = *(_BYTE *)v12;
          flen = v11;
          LOBYTE(v13) = *(_BYTE *)(v12 + 1);
          LOWORD(v12) = v13;
        }
        v12 = (unsigned __int16)v12;
        v9 += (unsigned __int16)v12;
        v5 = (st_lwPolygon *)((char *)v5 + 1);
        v10 += 2 * (unsigned __int16)v12;
        if ( v11 != -9999 )
        {
          LOWORD(v12) = *(_WORD *)v10;
          cksize = (st_lwPolVert *)v12;
          BigRevBytes(&cksize, 2, 1);
          v11 = flen + 2;
          v10 += 2;
          flen += 2;
          if ( (__int16)cksize < 0 )
            v10 += 2;
        }
      }
      while ( v10 < v8 );
    }
    v15 = (st_lwPolygonList *)plist;
    if ( lwAllocPolygons((st_lwPolygonList *)plist, v5, v9) )
    {
      pol = v15->pol;
      v17 = buf;
      v18 = &pol[v15->offset];
      v19 = (int)&pol->v[v15->voffset];
      pp = v18;
      cksize = (st_lwPolVert *)v19;
      if ( (int)v5 > 0 )
      {
        v33 = v5;
        v20 = flen;
        do
        {
          v21 = v17;
          if ( v20 == -9999 )
          {
            v22 = 0;
          }
          else
          {
            v20 += 2;
            v17 += 2;
            HIWORD(v19) = 0;
            BYTE1(v19) = *v21;
            flen = v20;
            LOBYTE(v19) = v21[1];
            v22 = v19;
          }
          v23 = v18->v == 0;
          v24 = v22;
          v18->nverts = v22;
          v18->type = 1178682181;
          if ( v23 )
            v18->v = cksize;
          if ( v22 )
          {
            v19 = (int)cksize;
            v25 = v22;
            do
            {
              v26 = v17;
              if ( v20 == -9999 )
              {
                v27 = 0;
              }
              else
              {
                v20 += 2;
                v17 += 2;
                HIBYTE(v28) = *v26;
                LOBYTE(v28) = v26[1];
                v27 = v28;
              }
              v19 += 24;
              --v25;
              *(_DWORD *)(v19 - 24) = ptoffset + v27;
            }
            while ( v25 );
            v18 = pp;
            flen = v20;
          }
          if ( v20 == -9999 )
          {
            LOWORD(v29) = 0;
          }
          else
          {
            LOWORD(v19) = *(_WORD *)v17;
            v32 = v19;
            BigRevBytes(&v32, 2, 1);
            LOWORD(v29) = v32;
            v18 = pp;
            v20 = flen + 2;
            flen += 2;
            v17 += 2;
          }
          v29 = (__int16)v29;
          if ( (v29 & 0x8000u) != 0 )
          {
            v29 = -(__int16)v29;
            v17 += 2;
          }
          v19 = (int)cksize;
          v18->surf = (st_lwSurface *)(v29 - 1);
          ++v18;
          v23 = v33 == (st_lwPolygon *)1;
          v33 = (st_lwPolygon *)((char *)v33 - 1);
          pp = v18;
          cksize = (st_lwPolVert *)(v19 + 24 * v24);
        }
        while ( !v23 );
      }
      Mem_Free(buf);
      return 1;
    }
    else
    {
      Mem_Free(buf);
      lwFreePolygons(v15);
      return 0;
    }
  }
  else
  {
    lwFreePolygons((st_lwPolygonList *)plist);
    return 0;
  }
}

// FUNC: void __cdecl lwGetPolyNormals(struct st_lwPointList *,struct st_lwPolygonList *)
void __cdecl lwGetPolyNormals(st_lwPointList *point, st_lwPolygonList *polygon)
{
  st_lwPolygonList *v2; // esi
  int v3; // edx
  st_lwPolygon *pol; // eax
  float *v5; // edi
  _DWORD *v6; // esi
  int v7; // ebp
  int v8; // ebx
  st_lwPoint *pt; // eax
  double v10; // st7
  int v11; // ebx
  double v12; // st6
  double v13; // st5
  double v14; // st4
  double v15; // st3
  double v16; // st2
  double v17; // st1
  st_lwPolygon *v18; // eax
  float *v19; // ecx
  long double v20; // st4
  bool v21; // cc
  int i; // [esp+4h] [ebp-38h]
  int v23; // [esp+8h] [ebp-34h]
  float p1_4; // [esp+1Ch] [ebp-20h]
  float p1_8; // [esp+20h] [ebp-1Ch]
  float v2_8; // [esp+38h] [ebp-4h]

  v2 = polygon;
  v3 = 0;
  i = 0;
  if ( polygon->count > 0 )
  {
    v23 = 0;
    do
    {
      pol = v2->pol;
      v5 = (float *)((char *)pol + v3);
      if ( *(int *)((char *)&pol->norm[3] + v3) >= 3 )
      {
        v6 = *(st_lwPolVert **)((char *)&pol->v + v3);
        v7 = v6[6];
        v8 = *(_DWORD *)((char *)&pol->norm[3] + v3);
        pt = point->pt;
        v10 = pt[*v6].pos[0];
        v11 = v6[6 * v8 - 6];
        p1_4 = pt[*v6].pos[1];
        p1_8 = pt[*v6].pos[2];
        v3 = v23;
        v2 = polygon;
        v12 = pt[v7].pos[0] - v10;
        v13 = pt[v11].pos[0] - v10;
        v14 = pt[v7].pos[1] - p1_4;
        v15 = pt[v11].pos[1] - p1_4;
        v16 = pt[v7].pos[2] - p1_8;
        v17 = pt[v11].pos[2] - p1_8;
        v2_8 = v17;
        v5[5] = v17 * v14 - v15 * v16;
        v5[6] = v16 * v13 - v2_8 * v12;
        v5[7] = v15 * v12 - v14 * v13;
        v18 = polygon->pol;
        v19 = (float *)((char *)v18->norm + v23);
        v20 = sqrt(
                *v19 * *v19
              + *(float *)((char *)&v18->norm[1] + v23) * *(float *)((char *)&v18->norm[1] + v23)
              + *(float *)((char *)&v18->norm[2] + v3) * *(float *)((char *)&v18->norm[2] + v3));
        if ( v20 > 0.0 )
        {
          *v19 = 1.0 / v20 * *v19;
          *(float *)((char *)&v18->norm[1] + v23) = 1.0 / v20 * *(float *)((char *)&v18->norm[1] + v23);
          *(float *)((char *)&v18->norm[2] + v23) = 1.0 / v20 * *(float *)((char *)&v18->norm[2] + v23);
        }
      }
      v3 += 40;
      v21 = ++i < v2->count;
      v23 = v3;
    }
    while ( v21 );
  }
}

// FUNC: int __cdecl lwResolvePolySurfaces(struct st_lwPolygonList *,struct st_lwTagList *,struct st_lwSurface * *,int *)
int __cdecl lwResolvePolySurfaces(st_lwPolygonList *polygon, st_lwTagList *tlist, st_lwSurface **surf, int *nsurfs)
{
  int result; // eax
  _DWORD *v5; // ebx
  int j; // edi
  st_lwSurface *v7; // esi
  int v8; // edi
  int v9; // esi
  _DWORD *v10; // eax
  _BYTE *v11; // edx
  char *v12; // ecx
  char v13; // al
  st_lwSurface *v14; // eax
  st_lwSurface *v15; // edx
  st_lwSurface *v16; // ecx
  int i; // [esp+4h] [ebp-4h]

  if ( !tlist->count )
    return 1;
  result = (int)Mem_ClearedAlloc(4 * tlist->count, 0xEu);
  v5 = (_DWORD *)result;
  if ( result )
  {
    for ( j = 0; j < tlist->count; ++j )
    {
      v7 = *surf;
      if ( *surf )
      {
        while ( idStr::Cmp(v7->name, tlist->tag[j]) )
        {
          v7 = v7->next;
          if ( !v7 )
            goto LABEL_10;
        }
        v5[j] = v7;
      }
LABEL_10:
      ;
    }
    v8 = 0;
    i = 0;
    if ( polygon->count <= 0 )
    {
LABEL_27:
      Mem_Free(v5);
      return 1;
    }
    else
    {
      while ( 1 )
      {
        v9 = (int)polygon->pol[v8].surf;
        if ( v9 < 0 || v9 > tlist->count )
          return 0;
        if ( !v5[v9] )
        {
          v10 = Mem_ClearedAlloc(244, 0xEu);
          if ( v10 )
          {
            v10[4] = 1061734538;
            v10[5] = 1061734538;
            v10[6] = 1061734538;
            v10[12] = 1065353216;
            v10[18] = 1053609165;
            v10[39] = 1065353216;
            v10[33] = 1065353216;
            v10[43] = 1;
          }
          v5[v9] = v10;
          if ( !v10 )
            return 0;
          *(_DWORD *)(v5[v9] + 8) = Mem_ClearedAlloc(strlen(tlist->tag[v9]) + 1, 0xEu);
          v11 = *(_BYTE **)(v5[v9] + 8);
          if ( !v11 )
            return 0;
          v12 = tlist->tag[v9];
          do
          {
            v13 = *v12;
            *v11++ = *v12++;
          }
          while ( v13 );
          v14 = *surf;
          v15 = (st_lwSurface *)v5[v9];
          if ( *surf )
          {
            do
            {
              v16 = v14;
              v14 = v14->next;
            }
            while ( v14 );
            v16->next = v15;
            v15->prev = v16;
          }
          else
          {
            *surf = v15;
          }
          ++*nsurfs;
        }
        polygon->pol[v8++].surf = (st_lwSurface *)v5[v9];
        if ( ++i >= polygon->count )
          goto LABEL_27;
      }
    }
  }
  return result;
}

// FUNC: void __cdecl lwGetVertNormals(struct st_lwPointList *,struct st_lwPolygonList *)
void __cdecl lwGetVertNormals(st_lwPointList *point, st_lwPolygonList *polygon)
{
  int v3; // ebx
  int v4; // esi
  int v5; // ebp
  st_lwPolygon *v6; // ecx
  int v7; // ecx
  int v8; // edx
  char *v9; // eax
  int v10; // ebx
  st_lwPolygon *pol; // ecx
  double v12; // st7
  long double v13; // st7
  st_lwPolygon *v14; // ecx
  float *v15; // edx
  st_lwPolVert *v; // edx
  float *v17; // ecx
  long double v18; // st4
  bool v19; // cc
  float v20; // [esp+4h] [ebp-18h]
  int j; // [esp+8h] [ebp-14h]
  int v22; // [esp+Ch] [ebp-10h]
  int g; // [esp+10h] [ebp-Ch]
  int n; // [esp+14h] [ebp-8h]
  int v25; // [esp+18h] [ebp-4h]
  st_lwPolygonList *polygona; // [esp+24h] [ebp+8h]

  j = 0;
  if ( polygon->count > 0 )
  {
    v3 = 24;
    v4 = 0;
    v25 = 24;
    do
    {
      n = 0;
      if ( polygon->pol[v4].nverts > 0 )
      {
        polygona = 0;
        v5 = 12;
        do
        {
          *(_DWORD *)((char *)polygon->pol[v4].v + v5 - 8) = *(_DWORD *)((char *)polygon->pol + v3 - 4);
          *(_DWORD *)((char *)polygon->pol[v4].v + v5 - 4) = *(st_lwSurface **)((char *)&polygon->pol->surf + v3);
          *(int *)((char *)&polygon->pol[v4].v->index + v5) = *(int *)((char *)&polygon->pol->part + v3);
          v6 = &polygon->pol[v4];
          if ( v6->surf->smooth > 0.0 )
          {
            v7 = 28 * *(int *)((char *)&polygona->count + (unsigned int)v6->v);
            v8 = 0;
            v9 = (char *)point->pt + v7;
            g = 0;
            v22 = v7;
            if ( *((int *)v9 + 3) > 0 )
            {
              do
              {
                v10 = *(_DWORD *)(*((_DWORD *)v9 + 4) + 4 * v8);
                if ( v10 != j )
                {
                  pol = polygon->pol;
                  if ( pol[v4].smoothgrp == pol[v10].smoothgrp )
                  {
                    v12 = pol[v4].norm[2] * pol[v10].norm[2]
                        + pol[v4].norm[1] * pol[v10].norm[1]
                        + pol[v4].norm[0] * pol[v10].norm[0];
                    v20 = v12;
                    if ( v12 > -1.0 )
                    {
                      if ( v20 < 1.0 )
                        v13 = acos(v20);
                      else
                        v13 = 0.0;
                    }
                    else
                    {
                      v13 = 3.1415927;
                    }
                    if ( v13 <= polygon->pol[v4].surf->smooth )
                    {
                      v14 = polygon->pol;
                      v15 = (float *)((char *)v14[v4].v + v5 - 8);
                      *v15 = v14[v10].norm[0] + *v15;
                      *(float *)((char *)polygon->pol[v4].v + v5 - 4) = polygon->pol[v10].norm[1]
                                                                      + *(float *)((char *)polygon->pol[v4].v + v5 - 4);
                      *(float *)((char *)&polygon->pol[v4].v->index + v5) = polygon->pol[v10].norm[2]
                                                                          + *(float *)((char *)&polygon->pol[v4].v->index
                                                                                     + v5);
                    }
                  }
                  v7 = v22;
                }
                v8 = g + 1;
                v9 = (char *)point->pt + v7;
                ++g;
              }
              while ( g < *((_DWORD *)v9 + 3) );
              v3 = v25;
            }
            v = polygon->pol[v4].v;
            v17 = (float *)((char *)&polygona->offset + (_DWORD)v);
            v18 = sqrt(
                    *v17 * *v17
                  + *(float *)((char *)&polygona->vcount + (_DWORD)v)
                  * *(float *)((char *)&polygona->vcount + (_DWORD)v)
                  + *(float *)((char *)&polygona->voffset + (_DWORD)v)
                  * *(float *)((char *)&polygona->voffset + (_DWORD)v));
            if ( v18 > 0.0 )
            {
              *v17 = 1.0 / v18 * *v17;
              *(float *)((char *)&polygona->vcount + (_DWORD)v) = 1.0
                                                                / v18
                                                                * *(float *)((char *)&polygona->vcount + (_DWORD)v);
              *(float *)((char *)&polygona->voffset + (_DWORD)v) = 1.0
                                                                 / v18
                                                                 * *(float *)((char *)&polygona->voffset + (_DWORD)v);
            }
          }
          polygona = (st_lwPolygonList *)((char *)polygona + 24);
          v5 += 24;
          ++n;
        }
        while ( n < polygon->pol[v4].nverts );
      }
      v3 += 40;
      ++v4;
      v19 = ++j < polygon->count;
      v25 = v3;
    }
    while ( v19 );
  }
}

// FUNC: struct st_lwObject * __cdecl lwGetObject5(char const *,unsigned int *,int *)
st_lwObject *__cdecl lwGetObject5(const char *filename, unsigned int *failID, int *failpos)
{
  idFile *v3; // eax
  idFile *v4; // esi
  unsigned int U4; // ebx
  unsigned int v7; // eax
  st_lwObject *v8; // ebp
  st_lwLayer *v9; // eax
  st_lwLayer *v10; // ebx
  unsigned int v11; // eax
  char **v12; // eax
  st_lwSurface *Surface5; // eax
  st_lwPointList *p_point; // edi
  st_lwPolygonList *p_polygon; // ebx
  int id; // [esp+10h] [ebp-8h]
  int formsize; // [esp+14h] [ebp-4h]

  v3 = fileSystem->OpenFileRead(fileSystem, filename, 1, 0);
  v4 = v3;
  if ( !v3 )
    return 0;
  flen = 0;
  U4 = getU4(v3);
  id = U4;
  formsize = getU4(v4);
  v7 = getU4(v4);
  if ( flen != 12 )
  {
    fileSystem->CloseFile(fileSystem, v4);
    return 0;
  }
  if ( U4 != 1179603533 || v7 != 1280790338 )
  {
    fileSystem->CloseFile(fileSystem, v4);
    if ( failpos )
      *failpos = 12;
    return 0;
  }
  v8 = (st_lwObject *)Mem_ClearedAlloc(48, 0xEu);
  if ( !v8 )
    goto Fail2;
  v9 = (st_lwLayer *)Mem_ClearedAlloc(100, 0xEu);
  v10 = v9;
  if ( !v9 )
    goto Fail2;
  v8->layer = v9;
  v8->nlayers = 1;
  id = getU4(v4);
  v11 = getU4(v4);
  if ( flen < 0 )
    goto Fail2;
  while ( 1 )
  {
    v12 = (char **)((v11 & 1) + v11);
    if ( id > 1397900883 )
    {
      if ( id != 1398100550 )
      {
LABEL_21:
        v4->Seek(v4, (int)v12, FS_SEEK_CUR);
        goto LABEL_24;
      }
      Surface5 = lwGetSurface5(v4, (int)v12, v8);
      if ( !Surface5 )
        goto Fail2;
      lwListAdd((void **)&v8->surf, Surface5);
      ++v8->nsurfs;
    }
    else
    {
      switch ( id )
      {
        case 1397900883:
          if ( !lwGetTags(v4, v12, &v8->taglist) )
            goto Fail2;
          break;
        case 1347310675:
          if ( !lwGetPoints(v4, (int)v12, (int)&v10->point) )
            goto Fail2;
          break;
        case 1347374163:
          if ( !lwGetPolygons5(v4, (st_lwPolVert *)v12, (st_lwPolVert *)&v10->polygon, v10->point.offset) )
            goto Fail2;
          break;
        default:
          goto LABEL_21;
      }
    }
LABEL_24:
    if ( formsize <= v4->Tell(v4) - 8 )
      break;
    flen = 0;
    id = getU4(v4);
    v11 = getU4(v4);
    if ( flen != 8 )
      goto Fail2;
  }
  fileSystem->CloseFile(fileSystem, v4);
  p_point = &v10->point;
  v4 = 0;
  lwGetBoundingBox(&v10->point, v10->bbox);
  p_polygon = &v10->polygon;
  lwGetPolyNormals(p_point, p_polygon);
  if ( lwGetPointPolygons(p_point, p_polygon) && lwResolvePolySurfaces(p_polygon, &v8->taglist, &v8->surf, &v8->nsurfs) )
  {
    lwGetVertNormals(p_point, p_polygon);
    return v8;
  }
Fail2:
  if ( failID )
    *failID = id;
  if ( v4 )
  {
    if ( failpos )
      *failpos = v4->Tell(v4);
    fileSystem->CloseFile(fileSystem, v4);
  }
  lwFreeObject(v8);
  return 0;
}

// FUNC: struct st_lwObject * __cdecl lwGetObject(char const *,unsigned int *,int *,unsigned int *)
st_lwObject *__cdecl lwGetObject(const char *filename, unsigned int *failID, int *failpos, unsigned int *TimeStamp)
{
  idFile *v4; // esi
  idFileSystem_vtbl *v5; // edx
  unsigned int U4; // ebp
  unsigned int v8; // eax
  unsigned int v9; // edi
  int *v10; // eax
  st_lwObject *v11; // ebx
  st_lwLayer *v12; // eax
  st_lwLayer *v13; // ebp
  unsigned int v14; // edi
  char **v15; // edi
  st_lwClip *Clip; // eax
  float *bbox; // ebx
  st_lwEnvelope *Envelope; // eax
  int v19; // eax
  int U2; // edx
  st_lwSurface *Surface; // eax
  st_lwVMap *VMap; // eax
  st_lwLayer *layer; // edi
  int id; // [esp+24h] [ebp-3Ch]
  st_lwObject *object; // [esp+28h] [ebp-38h]
  int v26; // [esp+2Ch] [ebp-34h]
  int formsize; // [esp+30h] [ebp-30h]
  idStr importName; // [esp+34h] [ebp-2Ch] BYREF
  int v29; // [esp+5Ch] [ebp-4h]

  v4 = fileSystem->OpenFileRead(fileSystem, filename, 1, 0);
  if ( !v4 )
  {
    importName.len = 0;
    importName.alloced = 20;
    importName.data = importName.baseBuffer;
    importName.baseBuffer[0] = 0;
    v5 = fileSystem->__vftable;
    v29 = 0;
    v5->OSpathToImportPath(fileSystem, filename, &importName, 0);
    v4 = fileSystem->OpenImportFileRead(fileSystem, importName.data);
    v29 = -1;
    if ( !v4 )
    {
      *TimeStamp = 0;
      idStr::FreeData(&importName);
      return 0;
    }
    idStr::FreeData(&importName);
  }
  *TimeStamp = v4->Timestamp(v4);
  flen = 0;
  U4 = getU4(v4);
  id = U4;
  formsize = getU4(v4);
  v8 = getU4(v4);
  v9 = v8;
  if ( flen != 12 )
  {
    fileSystem->CloseFile(fileSystem, v4);
    return 0;
  }
  if ( U4 != 1179603533 )
  {
    fileSystem->CloseFile(fileSystem, v4);
    v10 = failpos;
LABEL_9:
    if ( !v10 )
      return 0;
    *v10 = 12;
    return 0;
  }
  if ( v8 != 1280790322 )
  {
    fileSystem->CloseFile(fileSystem, v4);
    v10 = failpos;
    if ( v9 == 1280790338 )
      return lwGetObject5(filename, failID, failpos);
    goto LABEL_9;
  }
  v11 = (st_lwObject *)Mem_ClearedAlloc(48, 0xEu);
  object = v11;
  if ( !v11 )
    goto Fail_8;
  v12 = (st_lwLayer *)Mem_ClearedAlloc(100, 0xEu);
  v13 = v12;
  if ( !v12 )
    goto Fail_8;
  v11->layer = v12;
  v11->timeStamp = v4->Timestamp(v4);
  id = getU4(v4);
  v14 = getU4(v4);
  if ( flen < 0 )
    goto Fail_8;
  while ( 1 )
  {
    v15 = (char **)((v14 & 1) + v14);
    if ( id > 1347374163 )
    {
      if ( id > 1413564243 )
      {
        if ( id != 1447903556 && id != 1447903568 )
        {
LABEL_64:
          v4->Seek(v4, (int)v15, FS_SEEK_CUR);
          goto LABEL_32;
        }
        VMap = lwGetVMap(v4, (int)v15, v13->point.offset, v13->polygon.offset, id == 1447903556);
        if ( !VMap )
          goto Fail_8;
        lwListAdd((void **)&v13->vmap, VMap);
        ++v13->nvmaps;
      }
      else
      {
        switch ( id )
        {
          case 1413564243:
            if ( !lwGetTags(v4, v15, &v11->taglist) )
              goto Fail_8;
            break;
          case 1347699015:
            if ( !lwGetPolygonTags(v4, (int)v15, &v11->taglist, &v13->polygon) )
              goto Fail_8;
            break;
          case 1398100550:
            Surface = lwGetSurface(v4, (int)v15);
            if ( !Surface )
              goto Fail_8;
            lwListAdd((void **)&v11->surf, Surface);
            ++v11->nsurfs;
            break;
          default:
            goto LABEL_64;
        }
      }
    }
    else if ( id == 1347374163 )
    {
      if ( !lwGetPolygons(v4, (int)v15, (st_lwPolVert *)&v13->polygon, v13->point.offset) )
        goto Fail_8;
    }
    else if ( id > 1162761804 )
    {
      if ( id == 1279351122 )
      {
        if ( v11->nlayers > 0 )
        {
          v13 = (st_lwLayer *)Mem_ClearedAlloc(100, 0xEu);
          if ( !v13 )
            goto Fail_8;
          lwListAdd((void **)&v11->layer, v13);
        }
        ++v11->nlayers;
        flen = 0;
        v13->index = getU2(v4);
        v13->flags = getU2(v4);
        v13->pivot[0] = getF4(v4);
        v13->pivot[1] = getF4(v4);
        v13->pivot[2] = getF4(v4);
        v13->name = getS0(v4);
        v19 = flen;
        if ( flen < 0 || flen > (int)v15 )
          goto Fail_8;
        if ( flen <= (int)v15 - 2 )
        {
          U2 = getU2(v4);
          v19 = flen;
          v13->parent = U2;
        }
        if ( v19 < (int)v15 )
          v4->Seek(v4, (int)v15 - v19, FS_SEEK_CUR);
      }
      else
      {
        if ( id != 1347310675 )
          goto LABEL_64;
        if ( !lwGetPoints(v4, (int)v15, (int)&v13->point) )
          goto Fail_8;
      }
    }
    else
    {
      switch ( id )
      {
        case 1162761804:
          Envelope = lwGetEnvelope(v4, (int)v15);
          if ( !Envelope )
            goto Fail_8;
          lwListAdd((void **)&v11->env, Envelope);
          ++v11->nenvs;
          break;
        case 1111641944:
          flen = 0;
          bbox = v13->bbox;
          v26 = 6;
          do
          {
            *bbox++ = getF4(v4);
            --v26;
          }
          while ( v26 );
          if ( flen < 0 || flen > (int)v15 )
          {
            v11 = object;
            goto Fail_8;
          }
          if ( flen < (int)v15 )
            v4->Seek(v4, (int)v15 - flen, FS_SEEK_CUR);
          v11 = object;
          break;
        case 1129072976:
          Clip = lwGetClip(v4, (int)v15);
          if ( !Clip )
            goto Fail_8;
          lwListAdd((void **)&v11->clip, Clip);
          ++v11->nclips;
          break;
        default:
          goto LABEL_64;
      }
    }
LABEL_32:
    if ( formsize <= v4->Tell(v4) - 8 )
      break;
    flen = 0;
    id = getU4(v4);
    v14 = getU4(v4);
    if ( flen != 8 )
      goto Fail_8;
  }
  fileSystem->CloseFile(fileSystem, v4);
  v4 = 0;
  if ( !v11->nlayers )
    v11->nlayers = 1;
  layer = v11->layer;
  if ( !layer )
    return v11;
  while ( 1 )
  {
    lwGetBoundingBox(&layer->point, layer->bbox);
    lwGetPolyNormals(&layer->point, &layer->polygon);
    if ( !lwGetPointPolygons(&layer->point, &layer->polygon) )
      break;
    if ( !lwResolvePolySurfaces(&layer->polygon, &v11->taglist, &v11->surf, &v11->nsurfs) )
      break;
    lwGetVertNormals(&layer->point, &layer->polygon);
    if ( !lwGetPointVMaps(&layer->point, layer->vmap) || !lwGetPolyVMaps(&layer->polygon, layer->vmap) )
      break;
    layer = layer->next;
    if ( !layer )
      return v11;
  }
Fail_8:
  if ( failID )
    *failID = id;
  if ( v4 )
  {
    if ( failpos )
      *failpos = v4->Tell(v4);
    fileSystem->CloseFile(fileSystem, v4);
  }
  lwFreeObject(v11);
  return 0;
}
