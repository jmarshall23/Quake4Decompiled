
// FUNC: R_EmptyLevelImage
None

// FUNC: public: void __thiscall idMegaTexture::Unbind(void)
void __thiscall idMegaTexture::Unbind(idMegaTexture *this)
{
  int v2; // eax
  int v3; // esi

  v2 = 0;
  if ( this->numLevels > 0 )
  {
    do
    {
      v3 = v2 + 1;
      GL_SelectTexture(v2 + 1);
      globalImages->BindNull(globalImages);
      v2 = v3;
    }
    while ( v3 < this->numLevels );
  }
}

// FUNC: public: void __thiscall idTextureLevel::Invalidate(void)
void __thiscall idTextureLevel::Invalidate(idTextureLevel *this)
{
  int *p_y; // eax
  int v2; // esi
  int v3; // ecx

  p_y = &this->tileMap[0][0].y;
  v2 = 4;
  do
  {
    v3 = 4;
    do
    {
      *p_y = -99999;
      *(p_y - 1) = -99999;
      p_y += 2;
      --v3;
    }
    while ( v3 );
    --v2;
  }
  while ( v2 );
}

// FUNC: private: static void __cdecl idMegaTexture::GenerateMegaMipMaps(struct megaTextureHeader_t *,class idFile *)
void __cdecl idMegaTexture::GenerateMegaMipMaps(megaTextureHeader_t *header, idFile *outFile)
{
  idFileSystem_vtbl *v2; // edi
  int v3; // eax
  idFile *v4; // esi
  int tilesWide; // ecx
  int tilesHigh; // edx
  int v7; // edi
  int v8; // eax
  void *v9; // esp
  int v10; // eax
  unsigned __int8 *v11; // ebx
  void *v12; // esp
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // eax
  unsigned __int8 *v17; // edi
  unsigned __int8 *v18; // eax
  unsigned __int8 *v19; // ecx
  int v20; // esi
  bool v21; // zf
  bool v22; // cc
  _BYTE v23[12]; // [esp+0h] [ebp-64h] BYREF
  int tileSize; // [esp+Ch] [ebp-58h]
  int ty; // [esp+10h] [ebp-54h]
  int yy; // [esp+14h] [ebp-50h]
  int v27; // [esp+18h] [ebp-4Ch]
  int v28; // [esp+1Ch] [ebp-48h]
  int v29; // [esp+20h] [ebp-44h]
  unsigned __int8 *v30; // [esp+24h] [ebp-40h]
  int v31; // [esp+28h] [ebp-3Ch]
  int v32; // [esp+2Ch] [ebp-38h]
  int v33; // [esp+30h] [ebp-34h]
  int x; // [esp+34h] [ebp-30h]
  unsigned __int8 *v35; // [esp+38h] [ebp-2Ch]
  int v36; // [esp+3Ch] [ebp-28h]
  unsigned __int8 *v37; // [esp+40h] [ebp-24h]
  unsigned __int8 *newBlock; // [esp+44h] [ebp-20h]
  int newWidth; // [esp+48h] [ebp-1Ch]
  int tileOffset; // [esp+4Ch] [ebp-18h]
  int y; // [esp+50h] [ebp-14h]
  unsigned __int8 *oldBlock; // [esp+54h] [ebp-10h]
  idFile *inFile; // [esp+58h] [ebp-Ch]
  int newHeight; // [esp+5Ch] [ebp-8h]
  int height; // [esp+60h] [ebp-4h]
  int width; // [esp+6Ch] [ebp+8h]

  outFile->Flush(outFile);
  v2 = fileSystem->__vftable;
  v3 = ((int (__thiscall *)(idFile *, int, _DWORD))outFile->GetName)(outFile, 1, 0);
  v4 = (idFile *)((int (__thiscall *)(idFileSystem *, int))v2->OpenFileRead)(fileSystem, v3);
  tilesWide = header->tilesWide;
  tilesHigh = header->tilesHigh;
  v7 = 4 * header->tileSize * header->tileSize;
  v8 = v7 + 3;
  LOBYTE(v8) = (v7 + 3) & 0xFC;
  inFile = v4;
  tileOffset = 1;
  width = tilesWide;
  height = tilesHigh;
  tileSize = v7;
  v9 = alloca(v8);
  v10 = v7 + 3;
  LOBYTE(v10) = (v7 + 3) & 0xFC;
  v11 = v23;
  oldBlock = v23;
  v12 = alloca(v10);
  newBlock = v23;
  while ( width > 1 || height > 1 )
  {
    v13 = (height + 1) >> 1;
    newHeight = v13;
    if ( v13 < 1 )
    {
      newHeight = 1;
      v13 = 1;
    }
    v14 = (width + 1) >> 1;
    newWidth = v14;
    if ( width < 1 )
      width = 1;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "generating %i x %i block mip level\n",
      v14,
      v13);
    y = 0;
    if ( newHeight > 0 )
    {
      v31 = 0;
      v32 = 0;
      do
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "row %i\n", y);
        session->UpdateScreen(session, 1);
        x = 0;
        if ( newWidth > 0 )
        {
          v33 = v7 * (tileOffset + v31 + width * height);
          do
          {
            v36 = v32;
            v15 = 0;
            yy = 0;
            v35 = newBlock + 6;
            while ( 1 )
            {
              ty = v15 + 2 * y;
              v16 = 2 * x;
              v28 = 2 * x;
              v37 = v35;
              v27 = 2;
              while ( 1 )
              {
                if ( v16 > width || ty > height )
                {
                  *(_DWORD *)newBlock = 0;
                }
                else
                {
                  v4->Seek(v4, v7 * (tileOffset + v16 + v36), FS_SEEK_SET);
                  v4->Read(v4, v11, v7);
                }
                v17 = v37;
                v18 = v11 + 520;
                v30 = v11 + 520;
                v29 = 64;
                do
                {
                  v19 = v17;
                  v20 = 16;
                  do
                  {
                    *(v19 - 6) = (*(v18 - 4) + *(v18 - 8) + *(v18 - 516) + *(v18 - 520)) >> 2;
                    *(v19 - 5) = (*(v18 - 3) + *(v18 - 7) + *(v18 - 515) + *(v18 - 519)) >> 2;
                    *(v19 - 4) = (*(v18 - 2) + *(v18 - 6) + *(v18 - 514) + *(v18 - 518)) >> 2;
                    *(v19 - 3) = (*(v18 - 1) + *(v18 - 5) + *(v18 - 513) + *(v18 - 517)) >> 2;
                    *(v19 - 2) = (*v18 + v18[4] + *(v18 - 508) + *(v18 - 512)) >> 2;
                    *(v19 - 1) = (v18[1] + v18[5] + *(v18 - 507) + *(v18 - 511)) >> 2;
                    *v19 = (v18[2] + v18[6] + *(v18 - 506) + *(v18 - 510)) >> 2;
                    v19[1] = (v18[3] + v18[7] + *(v18 - 505) + *(v18 - 509)) >> 2;
                    v19[2] = (v18[8] + v18[12] + *(v18 - 500) + *(v18 - 504)) >> 2;
                    v19[3] = (v18[9] + v18[13] + *(v18 - 499) + *(v18 - 503)) >> 2;
                    v19[4] = (v18[10] + v18[14] + *(v18 - 498) + *(v18 - 502)) >> 2;
                    v19[5] = (v18[11] + v18[15] + *(v18 - 497) + *(v18 - 501)) >> 2;
                    v19[6] = (v18[16] + v18[20] + *(v18 - 492) + *(v18 - 496)) >> 2;
                    v19[7] = (v18[17] + v18[21] + *(v18 - 491) + *(v18 - 495)) >> 2;
                    v19[8] = (v18[18] + v18[22] + *(v18 - 490) + *(v18 - 494)) >> 2;
                    v19[9] = (v18[19] + v18[23] + *(v18 - 489) + *(v18 - 493)) >> 2;
                    v18 += 32;
                    v19 += 16;
                    --v20;
                  }
                  while ( v20 );
                  v18 = v30 + 1024;
                  v17 += 512;
                  v21 = v29-- == 1;
                  v30 += 1024;
                }
                while ( !v21 );
                outFile->Seek(outFile, v33, FS_SEEK_SET);
                v7 = tileSize;
                outFile->Write(outFile, newBlock, tileSize);
                v37 += 256;
                v4 = inFile;
                v16 = v28 + 1;
                v21 = v27-- == 1;
                ++v28;
                if ( v21 )
                  break;
                v11 = oldBlock;
              }
              v36 += width;
              v35 += 0x8000;
              v15 = ++yy;
              if ( yy >= 2 )
                break;
              v11 = oldBlock;
            }
            v33 += v7;
            v22 = x + 1 < newWidth;
            v11 = oldBlock;
            ++x;
          }
          while ( v22 );
        }
        v31 += newWidth;
        v32 += 2 * width;
        ++y;
      }
      while ( y < newHeight );
    }
    tileOffset += width * height;
    width = newWidth;
    height = newHeight;
  }
  if ( v4 )
    ((void (__thiscall *)(idFile *, int))v4->~idFile)(v4, 1);
}

// FUNC: public: void __thiscall idTextureLevel::UpdateTile(int,int,int,int)
void __thiscall idTextureLevel::UpdateTile(idTextureLevel *this, int localX, int localY, int globalX, int globalY)
{
  int v5; // edx
  int v7; // ecx
  bool v8; // zf
  idTextureTile *v9; // ebx
  int v10; // ecx
  int tilesWide; // eax
  char *v12; // edx
  int v13; // edi
  char *v14; // eax
  int v15; // ecx
  int v16; // edi
  bool v17; // cc
  unsigned __int8 *v18; // eax
  char *v19; // esi
  unsigned __int8 *v20; // ecx
  int v21; // [esp+Ch] [ebp-1001Ch]
  int v22; // [esp+Ch] [ebp-1001Ch]
  char *v23; // [esp+10h] [ebp-10018h]
  int v24; // [esp+14h] [ebp-10014h]
  int v25; // [esp+18h] [ebp-10010h]
  unsigned __int8 *v26; // [esp+1Ch] [ebp-1000Ch]
  char *v27; // [esp+20h] [ebp-10008h]
  int v28; // [esp+24h] [ebp-10004h]
  char v29[65536]; // [esp+28h] [ebp-10000h] BYREF

  v5 = localX;
  v7 = localY + 4 * localX;
  v8 = this->tileMap[0][v7].x == globalX;
  v9 = &this->tileMap[0][v7];
  v10 = globalY;
  if ( !v8 || v9->y != globalY )
  {
    if ( (globalX & 3) != localX || (globalY & 3) != localY )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "idTextureLevel::UpdateTile: bad coordinate mod");
      v5 = localX;
      v10 = globalY;
    }
    v9->x = globalX;
    v9->y = v10;
    tilesWide = this->tilesWide;
    if ( globalX >= tilesWide || globalX < 0 || v10 >= this->tilesHigh || v10 < 0 )
    {
      memset(v29, 0, sizeof(v29));
    }
    else
    {
      this->mega->fileHandle->Seek(
        this->mega->fileHandle,
        (globalX + this->tileOffset + v10 * tilesWide) << 16,
        FS_SEEK_SET);
      memset(v29, 0x80u, sizeof(v29));
      this->mega->fileHandle->Read(this->mega->fileHandle, v29, 0x10000);
      v5 = localX;
    }
    if ( idMegaTexture::r_showMegaTextureLabels.internalVar->integerValue )
    {
      LOBYTE(v21) = 255 * v5 / 4;
      *(_WORD *)((char *)&v21 + 1) = (unsigned __int8)(255 * localY / 4);
      HIBYTE(v21) = 0;
      v12 = &v29[30960];
      v13 = 8;
      do
      {
        v14 = v12;
        v15 = 8;
        do
        {
          *(_DWORD *)v14 = v21;
          v14 += 512;
          --v15;
        }
        while ( v15 );
        v12 += 4;
        --v13;
      }
      while ( v13 );
      v5 = localX;
    }
    qglTexSubImage2D(0xDE1u, 0, v5 << 7, localY << 7, 128, 128, 0x1908u, 0x1401u, v29);
    v16 = 64;
    v25 = 1;
    v17 = 0;
    do
    {
      if ( !v17 )
      {
        v28 = 16 * v16;
        v18 = (unsigned __int8 *)&v29[4];
        v19 = &v29[2];
        v20 = (unsigned __int8 *)&v29[8 * v16 + 1];
        v27 = &v29[4];
        v23 = &v29[2];
        v26 = v20;
        v24 = v16;
        do
        {
          v22 = v16;
          do
          {
            *(v19 - 2) = (*v18 + *(v20 - 1) + *(v18 - 4) + v18[8 * v16]) >> 2;
            *(v19 - 1) = (*v20 + v20[4] + v18[1] + *(v18 - 3)) >> 2;
            *v19 = (v20[1] + v20[5] + v18[2] + *(v18 - 2)) >> 2;
            v19[1] = (v20[2] + v20[6] + *(v18 - 1) + v18[3]) >> 2;
            v20 += 8;
            v18 += 8;
            v19 += 4;
            --v22;
          }
          while ( v22 );
          v20 = &v26[v28];
          v18 = (unsigned __int8 *)&v27[v28];
          v19 = &v23[4 * v16];
          v8 = v24-- == 1;
          v26 += v28;
          v27 += v28;
          v23 = v19;
        }
        while ( !v8 );
      }
      qglTexSubImage2D(0xDE1u, v25, localX * v16, localY * v16, v16, v16, 0x1908u, 0x1401u, v29);
      v16 >>= 1;
      v17 = v16 <= 0;
      ++v25;
    }
    while ( v16 );
  }
}

// FUNC: public: void __thiscall idTextureLevel::UpdateForCenter(float * const)
void __thiscall idTextureLevel::UpdateForCenter(idTextureLevel *this, float *center)
{
  int v3; // esi
  int v4; // ebx
  float *parms; // edi
  int i; // esi
  double v7; // st7
  unsigned __int64 v8; // rax
  int v9; // ebx
  int v10; // esi
  int v11; // edi
  float global[2]; // [esp+10h] [ebp-18h] BYREF
  int localTileOffset[2]; // [esp+18h] [ebp-10h]
  int globalTileCorner[2]; // [esp+20h] [ebp-8h]
  float *centera; // [esp+2Ch] [ebp+4h]

  if ( this->tilesWide > 4 || this->tilesHigh > 4 )
  {
    parms = this->parms;
    for ( i = 0; i < 2; ++i )
    {
      v7 = (*(float *)((char *)&global[i] + (char *)center - (char *)global) * this->parms[3] - 0.5) * 4.0;
      global[i] = v7;
      v8 = (unsigned __int64)(v7 + 0.5);
      globalTileCorner[i] = v8;
      localTileOffset[i] = v8 & 3;
      *parms++ = (double)-(int)v8 * 0.25;
    }
    v4 = localTileOffset[1];
    v3 = localTileOffset[0];
  }
  else
  {
    v3 = 0;
    globalTileCorner[0] = 0;
    globalTileCorner[1] = 0;
    v4 = 0;
    this->parms[0] = 0.25;
    this->parms[1] = 0.25;
    this->parms[3] = 0.25;
  }
  this->image->Bind(this->image);
  v9 = -v4;
  centera = 0;
  localTileOffset[0] = v9;
  LODWORD(global[0]) = -v3;
  while ( 1 )
  {
    v10 = 0;
    v11 = globalTileCorner[0] + (LOBYTE(global[0]) & 3);
    do
    {
      idTextureLevel::UpdateTile(this, (int)centera, v10++, v11, globalTileCorner[1] + (v9 & 3));
      LOBYTE(v9) = v9 + 1;
    }
    while ( v10 < 4 );
    ++LODWORD(global[0]);
    centera = (float *)((char *)centera + 1);
    if ( (int)centera >= 4 )
      break;
    LOBYTE(v9) = localTileOffset[0];
  }
}

// FUNC: public: bool __thiscall idMegaTexture::InitFromMegaFile(char const *)
char __thiscall idMegaTexture::InitFromMegaFile(idMegaTexture *this, const char *fileBase)
{
  int v3; // eax
  char v4; // cl
  unsigned int v5; // kr00_4
  char v6; // cl
  int i; // eax
  char *v8; // edx
  int v9; // esi
  int v10; // eax
  char v11; // cl
  char *v12; // edx
  idFile *v13; // eax
  int tilesWide; // ebx
  int tilesHigh; // eax
  idTextureLevel *v16; // esi
  idImageManager_vtbl *v17; // edx
  int height; // [esp+1Ch] [ebp-438h]
  int tileOffset; // [esp+20h] [ebp-434h]
  idStr name; // [esp+24h] [ebp-430h] BYREF
  int width; // [esp+44h] [ebp-410h]
  char str[1024]; // [esp+48h] [ebp-40Ch] BYREF
  int v24; // [esp+450h] [ebp-4h]

  name.data = name.baseBuffer;
  name.alloced = 20;
  name.baseBuffer[0] = 0;
  v3 = 0;
  do
  {
    v4 = aMegatextures[v3];
    name.baseBuffer[v3++] = v4;
  }
  while ( v4 );
  name.len = 13;
  v24 = 0;
  if ( fileBase )
  {
    v5 = strlen(fileBase);
    if ( (int)(v5 + 14) > name.alloced )
      idStr::ReAllocate(&name, v5 + 14, 1);
    v6 = *fileBase;
    for ( i = 0; v6; v6 = fileBase[i] )
    {
      v8 = &name.data[i++];
      v8[name.len] = v6;
    }
    name.len = v5 + 13;
    name.data[v5 + 13] = 0;
  }
  idStr::StripFileExtension(&name);
  v9 = name.len + 5;
  if ( name.len + 6 > name.alloced )
    idStr::ReAllocate(&name, name.len + 6, 1);
  v10 = 0;
  v11 = 46;
  do
  {
    v12 = &name.data[v10++];
    v12[name.len] = v11;
    v11 = aMega[v10];
  }
  while ( v11 );
  name.len = v9;
  name.data[v9] = 0;
  v13 = fileSystem->OpenFileRead(fileSystem, name.data, 1, 0);
  this->fileHandle = v13;
  if ( !v13 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *, char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idMegaTexture: failed to open %s\n",
      name.data);
LABEL_24:
    v24 = -1;
    idStr::FreeData(&name);
    return 0;
  }
  v13->Read(v13, &this->header, 12);
  if ( this->header.tileSize < 64
    || (tilesWide = this->header.tilesWide, tilesWide < 1)
    || (tilesHigh = this->header.tilesHigh, tilesHigh < 1) )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *, char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idMegaTexture: bad header on %s\n",
      name.data);
    goto LABEL_24;
  }
  this->currentTriMapping = 0;
  this->numLevels = 0;
  height = tilesHigh;
  memset(this->levels, 0, sizeof(this->levels));
  tileOffset = 1;
  while ( 1 )
  {
    v16 = &this->levels[this->numLevels];
    width = tilesWide;
    v16->tileOffset = tileOffset;
    v16->tilesHigh = height;
    v16->mega = this;
    v16->tilesWide = tilesWide;
    v16->parms[3] = (double)tilesWide * 0.25;
    v16->parms[0] = -1.0;
    v16->parms[1] = 0.0;
    v16->parms[2] = 0.0;
    idTextureLevel::Invalidate(v16);
    tileOffset += v16->tilesHigh * v16->tilesWide;
    sprintf(str, "MEGA_%s_%i", fileBase, this->numLevels);
    v17 = globalImages->__vftable;
    fillColor.intVal = *(int *)&colors[this->numLevels + 1][0];
    this->levels[this->numLevels++].image = v17->ImageFromFunction(globalImages, str, R_EmptyLevelImage);
    if ( tilesWide <= 4 && height <= 4 )
      break;
    tilesWide = (tilesWide + 1) >> 1;
    height = (height + 1) >> 1;
  }
  this->currentViewOrigin.x = -100000000.0;
  this->currentViewOrigin.y = -100000000.0;
  this->currentViewOrigin.z = -100000000.0;
  v24 = -1;
  idStr::FreeData(&name);
  return 1;
}

// FUNC: public: void __thiscall idMegaTexture::SetMappingForSurface(struct srfTriangles_s const *)
void __thiscall idMegaTexture::SetMappingForSurface(idMegaTexture *this, const srfTriangles_s *tri)
{
  int v2; // ebx
  bool v3; // cc
  int v4; // ebp
  idDrawVert *verts; // esi
  double x; // st7
  int v7; // esi
  int v8; // edx
  idVec2 *p_st; // esi
  float *v10; // eax
  float *p_z; // ecx
  double v12; // st7
  double v13; // st5
  double v14; // st7
  double v15; // st5
  double v16; // st4
  float scalea; // [esp+4h] [ebp-D0h]
  float scaleb; // [esp+4h] [ebp-D0h]
  float scalec; // [esp+4h] [ebp-D0h]
  float dir_4; // [esp+Ch] [ebp-C8h]
  float dir_8; // [esp+10h] [ebp-C4h]
  idDrawVert origin; // [esp+14h] [ebp-C0h] BYREF
  idDrawVert axis[2]; // [esp+54h] [ebp-80h] BYREF

  if ( tri != this->currentTriMapping )
  {
    this->currentTriMapping = tri;
    if ( tri->verts )
    {
      `vector constructor iterator'(axis, 0x40u, 2, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
      v2 = 0;
      v3 = tri->numVerts <= 0;
      origin.st.x = 1.0;
      origin.st.y = 1.0;
      axis[0].st.x = 0.0;
      axis[0].st.y = 1.0;
      axis[1].st.x = 1.0;
      axis[1].st.y = 0.0;
      if ( !v3 )
      {
        v4 = 0;
        do
        {
          verts = tri->verts;
          x = verts[v4].st.x;
          v7 = (int)&verts[v4];
          if ( x <= origin.st.x && *(float *)(v7 + 60) <= (double)origin.st.y )
            idDrawVert::operator=(&origin, v7);
          if ( *(float *)(v7 + 56) >= (double)axis[0].st.x && *(float *)(v7 + 60) <= (double)axis[0].st.y )
            idDrawVert::operator=(axis, v7);
          if ( *(float *)(v7 + 56) <= (double)axis[1].st.x && *(float *)(v7 + 60) >= (double)axis[1].st.y )
            idDrawVert::operator=(&axis[1].xyz.x, v7);
          ++v2;
          ++v4;
        }
        while ( v2 < tri->numVerts );
      }
      v8 = 0;
      p_st = &axis[0].st;
      v10 = &this->localViewToTextureCenter[0][1];
      p_z = &axis[0].xyz.z;
      do
      {
        ++v8;
        v12 = *(p_z - 2) - origin.xyz.x;
        p_z += 16;
        p_st = (idVec2 *)((char *)p_st + 68);
        v10 += 4;
        v13 = *(p_z - 17) - origin.xyz.y;
        dir_4 = v13;
        scalea = *(p_z - 16) - origin.xyz.z;
        dir_8 = scalea;
        scaleb = sqrt(scalea * scalea + v13 * v13 + v12 * v12);
        scalec = (p_st[-9].y - *(&origin.tangents[1].z + v8)) / (scaleb * scaleb);
        v14 = v12 * scalec;
        v15 = dir_8 * scalec;
        *(v10 - 5) = v14;
        v16 = dir_4 * scalec;
        *(v10 - 4) = v16;
        *(v10 - 3) = v15;
        *(v10 - 2) = -(v16 * origin.xyz.y + v15 * origin.xyz.z + v14 * origin.xyz.x - *(&origin.tangents[1].z + v8));
      }
      while ( v8 < 2 );
    }
  }
}

// FUNC: private: void __thiscall idMegaTexture::SetViewOrigin(class idVec3)
void __thiscall idMegaTexture::SetViewOrigin(idMegaTexture *this, idVec3 viewOrigin)
{
  int v3; // ebp
  bool v4; // cc
  int *p_y; // ebx
  int *v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // edi
  idTextureLevel *levels; // ebx
  float texCenter[2]; // [esp+Ch] [ebp-8h] BYREF

  if ( (idMegaTexture::r_showMegaTextureLabels.internalVar->flags & 0x40000) != 0 )
  {
    BYTE2(idMegaTexture::r_showMegaTextureLabels.internalVar->flags) &= ~4u;
    v3 = 0;
    v4 = this->numLevels <= 0;
    this->currentViewOrigin.x = viewOrigin.x + 0.1;
    if ( !v4 )
    {
      p_y = &this->levels[0].tileMap[0][0].y;
      do
      {
        v6 = p_y;
        v7 = 4;
        do
        {
          v8 = 4;
          do
          {
            *v6 = -99999;
            *(v6 - 1) = -99999;
            v6 += 2;
            --v8;
          }
          while ( v8 );
          --v7;
        }
        while ( v7 );
        ++v3;
        p_y += 41;
      }
      while ( v3 < this->numLevels );
    }
  }
  if ( (viewOrigin.x != this->currentViewOrigin.x
     || viewOrigin.y != this->currentViewOrigin.y
     || viewOrigin.z != this->currentViewOrigin.z)
    && !idMegaTexture::r_skipMegaTexture.internalVar->integerValue )
  {
    this->currentViewOrigin = viewOrigin;
    v9 = 0;
    v4 = this->numLevels <= 0;
    texCenter[0] = viewOrigin.z * this->localViewToTextureCenter[0][2]
                 + viewOrigin.y * this->localViewToTextureCenter[0][1]
                 + viewOrigin.x * this->localViewToTextureCenter[0][0]
                 + this->localViewToTextureCenter[0][3];
    texCenter[1] = viewOrigin.z * this->localViewToTextureCenter[1][2]
                 + viewOrigin.y * this->localViewToTextureCenter[1][1]
                 + viewOrigin.x * this->localViewToTextureCenter[1][0]
                 + this->localViewToTextureCenter[1][3];
    if ( !v4 )
    {
      levels = this->levels;
      do
      {
        idTextureLevel::UpdateForCenter(levels, texCenter);
        ++v9;
        ++levels;
      }
      while ( v9 < this->numLevels );
    }
  }
}

// FUNC: private: static void __cdecl idMegaTexture::GenerateMegaPreview(char const *)
void __cdecl idMegaTexture::GenerateMegaPreview(const char *fileName)
{
  idFile *v1; // edi
  const char *v2; // eax
  int v3; // esi
  int v4; // eax
  char *data; // edx
  const char *v6; // ecx
  char v7; // al
  int v8; // esi
  int v9; // eax
  char v10; // cl
  char *v11; // edx
  int v12; // ecx
  int tilesWide; // edi
  int tilesHigh; // eax
  int v15; // esi
  int v16; // ebx
  int v17; // eax
  void *v18; // esp
  int v19; // edx
  int v20; // ecx
  int v21; // eax
  unsigned __int8 *v22; // edi
  int v23; // ebx
  unsigned __int8 *v24; // esi
  bool v25; // zf
  int v26; // edx
  int v27; // edi
  unsigned __int8 *v28; // esi
  int v29; // [esp+0h] [ebp-80h] BYREF
  idStr outName; // [esp+Ch] [ebp-74h] BYREF
  megaTextureHeader_t header; // [esp+2Ch] [ebp-54h] BYREF
  int v32; // [esp+38h] [ebp-48h]
  int tileBytes; // [esp+3Ch] [ebp-44h]
  unsigned __int8 *pic; // [esp+40h] [ebp-40h]
  int v35; // [esp+44h] [ebp-3Ch]
  int v36; // [esp+48h] [ebp-38h]
  int v37; // [esp+4Ch] [ebp-34h]
  int tileSize; // [esp+50h] [ebp-30h]
  int v39; // [esp+54h] [ebp-2Ch]
  unsigned __int8 *oldBlock; // [esp+58h] [ebp-28h]
  idFile *fileHandle; // [esp+5Ch] [ebp-24h]
  int v42; // [esp+60h] [ebp-20h]
  int v43; // [esp+64h] [ebp-1Ch]
  int x; // [esp+68h] [ebp-18h]
  int width; // [esp+6Ch] [ebp-14h]
  int height; // [esp+70h] [ebp-10h]
  int v47; // [esp+7Ch] [ebp-4h]

  v1 = fileSystem->OpenFileRead(fileSystem, fileName, 1, 0);
  fileHandle = v1;
  if ( v1 )
  {
    outName.len = 0;
    outName.alloced = 20;
    outName.data = outName.baseBuffer;
    outName.baseBuffer[0] = 0;
    if ( fileName )
    {
      v2 = &fileName[strlen(fileName) + 1];
      v3 = v2 - (fileName + 1);
      v4 = v2 - fileName;
      if ( v4 > 20 )
        idStr::ReAllocate(&outName, v4, 1);
      data = outName.data;
      v6 = fileName;
      do
      {
        v7 = *v6;
        *data++ = *v6++;
      }
      while ( v7 );
      outName.len = v3;
    }
    v47 = 0;
    idStr::StripFileExtension(&outName);
    v8 = outName.len + 12;
    if ( outName.len + 13 > outName.alloced )
      idStr::ReAllocate(&outName, outName.len + 13, 1);
    v9 = 0;
    v10 = 95;
    do
    {
      v11 = &outName.data[v9++];
      v11[outName.len] = v10;
      v10 = aPreviewTga[v9];
    }
    while ( v10 );
    outName.len = v8;
    outName.data[v8] = 0;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Creating %s.\n",
      outName.data);
    v1->Read(v1, &header, 12);
    v12 = header.tileSize;
    if ( header.tileSize < 64
      || (tilesWide = header.tilesWide, header.tilesWide < 1)
      || (tilesHigh = header.tilesHigh, header.tilesHigh < 1) )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idMegaTexture: bad header on %s\n",
        fileName);
    }
    else
    {
      v15 = header.tileSize;
      v16 = 4 * header.tileSize * header.tileSize;
      tileSize = header.tileSize;
      width = header.tilesWide;
      height = header.tilesHigh;
      x = 1;
      tileBytes = v16;
      while ( v12 * tilesWide > 2048 || v12 * tilesHigh > 2048 )
      {
        x += tilesWide * tilesHigh;
        tilesWide >>= 1;
        width = tilesWide;
        if ( tilesWide < 1 )
        {
          width = 1;
          tilesWide = 1;
        }
        v12 = header.tileSize;
        tilesHigh >>= 1;
        height = tilesHigh;
        if ( tilesHigh < 1 )
        {
          height = 1;
          tilesHigh = 1;
        }
      }
      pic = (unsigned __int8 *)R_StaticAlloc(tilesWide * tilesHigh * v16);
      v17 = v16 + 3;
      LOBYTE(v17) = (v16 + 3) & 0xFC;
      v18 = alloca(v17);
      v19 = height;
      oldBlock = (unsigned __int8 *)&v29;
      if ( height > 0 )
      {
        v32 = tilesWide * v16;
        v20 = v15 * tilesWide;
        v21 = x * v16;
        v42 = 0;
        v37 = v15 * tilesWide;
        v36 = x * v16;
        v35 = height;
        do
        {
          x = 0;
          if ( tilesWide > 0 )
          {
            v43 = v21;
            do
            {
              fileHandle->Seek(fileHandle, v43, FS_SEEK_SET);
              fileHandle->Read(fileHandle, oldBlock, v16);
              if ( v15 > 0 )
              {
                v22 = oldBlock;
                v23 = 4 * v15;
                v24 = &pic[4 * v15 * (x + v42)];
                v39 = tileSize;
                do
                {
                  SIMDProcessor->Memcpy(SIMDProcessor, v24, v22, v23);
                  v24 += 4 * v37;
                  v22 += v23;
                  --v39;
                }
                while ( v39 );
                v15 = tileSize;
                tilesWide = width;
                v16 = tileBytes;
              }
              v43 += v16;
              ++x;
            }
            while ( x < tilesWide );
            v20 = v37;
            v21 = v36;
          }
          v21 += v32;
          v42 += v20;
          v25 = v35-- == 1;
          v36 = v21;
        }
        while ( !v25 );
        v19 = height;
      }
      v26 = v15 * v19;
      v27 = v15 * tilesWide;
      v28 = pic;
      R_WriteTGA(outName.data, pic, v27, v26, 0);
      R_StaticFree(v28);
      ((void (__thiscall *)(idFile *, int))fileHandle->~idFile)(fileHandle, 1);
    }
    v47 = -1;
    idStr::FreeData(&outName);
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idMegaTexture: failed to open %s\n",
      fileName);
  }
}

// FUNC: public: static void __cdecl idMegaTexture::MakeMegaTexture_f(class idCmdArgs const &)
void __usercall idMegaTexture::MakeMegaTexture_f(
        int a1@<ebx>,
        int a2@<ebp>,
        int a3@<edi>,
        int a4@<esi>,
        const idCmdArgs *args)
{
  int v5; // eax
  char v6; // cl
  bool v7; // cc
  const char *v8; // esi
  unsigned int v9; // kr08_4
  char v10; // cl
  int i; // eax
  char *v12; // edx
  int v13; // esi
  int v14; // eax
  char v15; // cl
  char *v16; // edx
  char *data; // ebx
  int v18; // ecx
  idFile *v19; // eax
  idFile *v20; // edi
  unsigned __int16 v21; // si
  unsigned __int16 v22; // bp
  unsigned __int8 v23; // al
  int v24; // eax
  int v25; // eax
  unsigned int v26; // eax
  unsigned int v27; // esi
  int v28; // eax
  _BYTE *v29; // edx
  char *v30; // ecx
  char v31; // al
  int v32; // esi
  int v33; // eax
  char v34; // cl
  int v35; // edx
  int v36; // esi
  int v37; // eax
  int v38; // edx
  char v39; // bl
  int v40; // ebp
  char *v41; // esi
  idFile_vtbl *v42; // edx
  idFile_vtbl *v43; // edx
  idFile_vtbl *v44; // edx
  int v45; // eax
  char v46; // dl
  char v47; // cl
  char *v48; // esi
  idFile_vtbl *v49; // edx
  idFile_vtbl *v50; // edx
  char v51; // dl
  char v52; // al
  char *v53; // esi
  char *v54; // esi
  idFile_vtbl *v55; // edx
  char v56; // al
  char v57; // cl
  char *v58; // esi
  int v59; // eax
  const char *v60; // ebp
  int tileSize; // ebx
  char *v62; // esi
  char v63; // dl
  char v64; // al
  char v65; // cl
  _BYTE *v66; // esi
  char *v67; // esi
  char v68; // dl
  char v69; // al
  _BYTE *v70; // esi
  _BYTE *v71; // esi
  int v72; // ebp
  int v73; // esi
  int v74; // ebx
  void (__thiscall ***v75)(_DWORD, int); // esi
  int packetSize; // [esp+C2h] [ebp-A8h] BYREF
  unsigned __int8 v80; // [esp+CAh] [ebp-A0h]
  unsigned __int8 v81; // [esp+CBh] [ebp-9Fh]
  unsigned __int8 v82; // [esp+CCh] [ebp-9Eh]
  char v83; // [esp+CDh] [ebp-9Dh]
  char v84; // [esp+CEh] [ebp-9Ch]
  char v85; // [esp+CFh] [ebp-9Bh]
  char v86; // [esp+D0h] [ebp-9Ah] BYREF
  char v87; // [esp+D1h] [ebp-99h]
  unsigned __int8 v88; // [esp+D2h] [ebp-98h]
  char v89[2]; // [esp+D3h] [ebp-97h] BYREF
  char v90; // [esp+D5h] [ebp-95h] BYREF
  int rowBlock; // [esp+D6h] [ebp-94h] BYREF
  int v92; // [esp+DAh] [ebp-90h] BYREF
  const char *v93; // [esp+DEh] [ebp-8Ch] BYREF
  int row; // [esp+E2h] [ebp-88h] BYREF
  int v95; // [esp+E6h] [ebp-84h]
  int v96; // [esp+EAh] [ebp-80h]
  int column; // [esp+EEh] [ebp-7Ch] BYREF
  char v98; // [esp+F2h] [ebp-78h] BYREF
  char v99; // [esp+F3h] [ebp-77h] BYREF
  char v100; // [esp+F4h] [ebp-76h] BYREF
  char v101; // [esp+F5h] [ebp-75h] BYREF
  int v102; // [esp+F6h] [ebp-74h]
  int v103; // [esp+FAh] [ebp-70h] BYREF
  char v104; // [esp+FEh] [ebp-6Ch] BYREF
  char v105; // [esp+FFh] [ebp-6Bh] BYREF
  char v106; // [esp+100h] [ebp-6Ah] BYREF
  char v107; // [esp+101h] [ebp-69h] BYREF
  unsigned __int8 *targa_rgba; // [esp+102h] [ebp-68h] BYREF
  int fileSize; // [esp+106h] [ebp-64h] BYREF
  const char *name; // [esp+10Ah] [ebp-60h]
  int blockRowsRemaining; // [esp+10Eh] [ebp-5Ch]
  megaTextureHeader_t mtHeader; // [esp+112h] [ebp-58h] BYREF
  idStr name_s; // [esp+11Eh] [ebp-4Ch] BYREF
  idStr outName; // [esp+13Eh] [ebp-2Ch] BYREF
  int v115; // [esp+166h] [ebp-4h]

  if ( args->argc != 2 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "USAGE: makeMegaTexture <filebase>\n");
    return;
  }
  name_s.data = name_s.baseBuffer;
  name_s.alloced = 20;
  name_s.baseBuffer[0] = 0;
  v5 = 0;
  do
  {
    v6 = aMegatextures[v5];
    name_s.baseBuffer[v5++] = v6;
  }
  while ( v6 );
  name_s.len = 13;
  v7 = args->argc <= 1;
  v115 = 0;
  if ( v7 )
  {
    v8 = &entityFilter;
  }
  else
  {
    v8 = args->argv[1];
    if ( !v8 )
      goto LABEL_12;
  }
  v9 = strlen(v8);
  if ( (int)(v9 + 14) > name_s.alloced )
    idStr::ReAllocate(&name_s, v9 + 14, 1);
  v10 = *v8;
  for ( i = 0; v10; v10 = v8[i] )
  {
    v12 = &name_s.data[i++];
    v12[name_s.len] = v10;
  }
  name_s.len = v9 + 13;
  name_s.data[v9 + 13] = 0;
LABEL_12:
  idStr::StripFileExtension(&name_s);
  v13 = name_s.len + 4;
  if ( name_s.len + 5 > name_s.alloced )
    idStr::ReAllocate(&name_s, name_s.len + 5, 1);
  v14 = 0;
  v15 = 46;
  do
  {
    v16 = &name_s.data[v14++];
    v16[name_s.len] = v15;
    v15 = aTga[v14];
  }
  while ( v15 );
  name_s.len = v13;
  name_s.data[v13] = 0;
  data = name_s.data;
  v18 = *(_DWORD *)common.type;
  name = name_s.data;
  (*(void (**)(netadrtype_t, const char *, ...))(v18 + 124))(common.type, "Opening %s.\n", name_s.data);
  fileSize = fileSystem->ReadFile(fileSystem, data, 0, 0);
  v19 = fileSystem->OpenFileRead(fileSystem, data, 1, 0);
  v20 = v19;
  if ( !v19 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "Couldn't open %s\n",
      data);
    v115 = -1;
    idStr::FreeData(&name_s);
    return;
  }
  ((void (__thiscall *)(idFile *, int *, int, int, int, int, int))v19->Read)(v19, &packetSize, 1, a2, a3, a4, a1);
  v20->Read(v20, (char *)&rowBlock + 2, 1);
  v20->Read(v20, &v90, 1);
  v20->Read(v20, &v92, 2);
  v20->Read(v20, &v92, 2);
  v20->Read(v20, (char *)&v93 + 2, 1);
  v20->Read(v20, &v92, 2);
  v20->Read(v20, &v92, 2);
  v20->Read(v20, &v92, 2);
  v21 = (unsigned __int8)v92 + (BYTE1(v92) << 8);
  v20->Read(v20, &v92, 2);
  v22 = (unsigned __int8)v92 + (BYTE1(v92) << 8);
  v20->Read(v20, v89, 1);
  v20->Read(v20, (char *)&v93 + 2, 1);
  if ( v90 != 2 && v90 != 10 && v90 != 3 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "LoadTGA( %s ): Only type 2 (RGB), 3 (gray), and 10 (RGB) TGA images supported\n",
      data);
  if ( BYTE2(rowBlock) )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "LoadTGA( %s ): colormaps not supported\n",
      data);
  v23 = v89[0];
  if ( v89[0] != 32 && v89[0] != 24 && v90 != 3 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "LoadTGA( %s ): Only 32 or 24 bit images supported (no colormaps)\n",
      data);
    v23 = v89[0];
  }
  if ( (v90 == 2 || v90 == 3) && v21 * v22 * (v23 >> 3) > mtHeader.tilesWide - v88 - 18 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "LoadTGA( %s ): incomplete file\n",
      data);
  row = v21;
  if ( v88 )
    v20->Seek(v20, v88, FS_SEEK_CUR);
  name_s.data = (char *)128;
  v24 = 1;
  if ( v21 >= 2u )
  {
    do
      v24 *= 2;
    while ( 2 * v24 <= v21 );
  }
  name_s.alloced = v24 / 128;
  v25 = 1;
  if ( v22 >= 2u )
  {
    do
      v25 *= 2;
    while ( 2 * v25 <= v22 );
  }
  *(_DWORD *)name_s.baseBuffer = v25 / 128;
  *(_DWORD *)&outName.baseBuffer[4] = 0;
  *(_DWORD *)&outName.baseBuffer[12] = 20;
  *(_DWORD *)&outName.baseBuffer[8] = &outName.baseBuffer[16];
  outName.baseBuffer[16] = 0;
  if ( data )
  {
    v26 = (unsigned int)&data[strlen(data) + 1];
    v27 = v26 - (_DWORD)(data + 1);
    v28 = v26 - (_DWORD)data;
    if ( v28 > 20 )
      idStr::ReAllocate((idStr *)&outName.baseBuffer[4], v28, 1);
    v29 = *(_BYTE **)&outName.baseBuffer[8];
    v30 = data;
    do
    {
      v31 = *v30;
      *v29++ = *v30++;
    }
    while ( v31 );
    *(_DWORD *)&outName.baseBuffer[4] = v27;
  }
  idStr::StripFileExtension((idStr *)&outName.baseBuffer[4]);
  v32 = *(_DWORD *)&outName.baseBuffer[4] + 5;
  if ( *(_DWORD *)&outName.baseBuffer[4] + 6 > *(int *)&outName.baseBuffer[12] )
    idStr::ReAllocate((idStr *)&outName.baseBuffer[4], *(_DWORD *)&outName.baseBuffer[4] + 6, 1);
  v33 = 0;
  v34 = 46;
  do
  {
    v35 = v33 + *(_DWORD *)&outName.baseBuffer[8];
    ++v33;
    *(_BYTE *)(v35 + *(_DWORD *)&outName.baseBuffer[4]) = v34;
    v34 = aMega[v33];
  }
  while ( v34 );
  *(_DWORD *)&outName.baseBuffer[4] = v32;
  *(_BYTE *)(*(_DWORD *)&outName.baseBuffer[8] + v32) = 0;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "Writing %i x %i size %i tiles to %s.\n",
    name_s.alloced,
    *(_DWORD *)name_s.baseBuffer,
    name_s.data,
    *(_DWORD *)&outName.baseBuffer[8]);
  v36 = ((int (__thiscall *)(idFileSystem *, _DWORD))fileSystem->OpenFileWrite)(
          fileSystem,
          *(_DWORD *)&outName.baseBuffer[8]);
  v37 = *(_DWORD *)v36;
  blockRowsRemaining = v36;
  (*(void (__thiscall **)(int, int *, int))(v37 + 16))(v36, &mtHeader.tilesHigh, 12);
  (*(void (__thiscall **)(int, int, int))(*(_DWORD *)v36 + 40))(v36, 0x10000, 2);
  name = (const char *)R_StaticAlloc(v92 << 9);
  mtHeader.tilesWide = (int)name_s.data;
  if ( name_s.data )
  {
LABEL_50:
    v38 = *(_DWORD *)common.type;
    (*(void (**)(netadrtype_t, const char *, ...))(v38 + 124))(
      common.type,
      "%i blockRowsRemaining\n",
      --mtHeader.tilesWide);
    session->UpdateScreen(session, 1);
    if ( v83 != 2 && v83 != 3 )
    {
      if ( v83 != 10 )
        goto LABEL_98;
      v39 = 0;
      v40 = 0;
      v84 = 0;
      v85 = 0;
      v87 = -1;
      v96 = 0;
      while ( 1 )
      {
        v41 = (char *)&name[4 * v92 * v40];
        v102 = 0;
        if ( v92 > 0 )
          break;
breakOut_0:
        v96 = ++v40;
        if ( v40 >= 128 )
          goto LABEL_98;
      }
      while ( 2 )
      {
        v20->Read(v20, &v107, 1);
        v80 = (v107 & 0x7F) + 1;
        if ( v107 < 0 )
        {
          if ( v81 == 24 )
          {
            v20->Read(v20, (char *)&fileSize + 3, 1);
            v39 = HIBYTE(fileSize);
            v20->Read(v20, (char *)&targa_rgba + 2, 1);
            v44 = v20->__vftable;
            v85 = BYTE2(targa_rgba);
            v44->Read(v20, &v104, 1);
            v84 = v104;
            v87 = -1;
          }
          else if ( v81 == 32 )
          {
            v20->Read(v20, (char *)&column + 3, 1);
            v39 = HIBYTE(column);
            v20->Read(v20, &v98, 1);
            v42 = v20->__vftable;
            v85 = v98;
            v42->Read(v20, &v100, 1);
            v43 = v20->__vftable;
            v84 = v100;
            v43->Read(v20, (char *)&fileSize + 1, 1);
            v87 = BYTE1(fileSize);
          }
          else
          {
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
              common.type,
              "LoadTGA( %s ): illegal pixel_size '%d'\n",
              mtHeader.tileSize,
              v81);
          }
          v82 = 0;
          if ( v80 )
          {
            v45 = v92;
            v95 = -4 * v92;
            v93 = &name[4 * v92 * v40];
            do
            {
              v46 = v85;
              *v41 = v84;
              v47 = v87;
              v48 = v41 + 1;
              *v48++ = v46;
              *v48++ = v39;
              *v48 = v47;
              v41 = v48 + 1;
              if ( ++v102 == v45 )
              {
                (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
                  common.type,
                  "TGA had RLE across columns, probably breaks block");
                v102 = 0;
                if ( v40 <= 0 )
                  goto breakOut_0;
                v45 = v92;
                --v40;
                v41 = (char *)&v93[v95];
                v96 = v40;
                v93 += v95;
              }
              ++v82;
            }
            while ( v82 < v80 );
          }
LABEL_80:
          if ( v102 >= v92 )
            goto breakOut_0;
          continue;
        }
        break;
      }
      v82 = 0;
      if ( !v80 )
        goto LABEL_80;
      v95 = -4 * v92;
      v93 = &name[4 * v92 * v40];
      while ( 2 )
      {
        if ( v81 == 24 )
        {
          v20->Read(v20, &v101, 1);
          v39 = v101;
          v20->Read(v20, &v86, 1);
          v55 = v20->__vftable;
          v85 = v86;
          v55->Read(v20, (char *)&column + 2, 1);
          v56 = BYTE2(column);
          v57 = v86;
          *v41 = BYTE2(column);
          v58 = v41 + 1;
          *v58++ = v57;
          *v58 = v39;
          v54 = v58 + 1;
          v84 = v56;
          *v54 = -1;
        }
        else
        {
          if ( v81 != 32 )
          {
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
              common.type,
              "LoadTGA( %s ): illegal pixel_size '%d'\n",
              mtHeader.tileSize,
              v81);
            goto LABEL_76;
          }
          v20->Read(v20, &v99, 1);
          v39 = v99;
          v20->Read(v20, (char *)&row + 3, 1);
          v49 = v20->__vftable;
          v85 = HIBYTE(row);
          v49->Read(v20, (char *)&rowBlock + 3, 1);
          v50 = v20->__vftable;
          v84 = HIBYTE(rowBlock);
          v50->Read(v20, &v105, 1);
          v51 = HIBYTE(row);
          v52 = v105;
          *v41 = HIBYTE(rowBlock);
          v53 = v41 + 1;
          *v53++ = v51;
          *v53 = v39;
          v54 = v53 + 1;
          v87 = v52;
          *v54 = v52;
        }
        v40 = v96;
        v41 = v54 + 1;
LABEL_76:
        if ( ++v102 == v92 )
        {
          v102 = 0;
          if ( v40 <= 0 )
            goto breakOut_0;
          --v40;
          v41 = (char *)&v93[v95];
          v96 = v40;
          v93 += v95;
        }
        if ( ++v82 >= v80 )
          goto LABEL_80;
        continue;
      }
    }
    v59 = v92;
    v60 = name;
    tileSize = mtHeader.tileSize;
    v96 = 4 * v92;
    v95 = 128;
    while ( 1 )
    {
      v62 = (char *)v60;
      if ( v59 <= 0 )
        goto LABEL_97;
      v93 = (const char *)v59;
      do
      {
        if ( v81 == 8 )
        {
          v20->Read(v20, (char *)&rowBlock + 2, 1);
          v69 = BYTE2(rowBlock);
          *v62 = BYTE2(rowBlock);
          v70 = v62 + 1;
          *v70 = v69;
          goto LABEL_93;
        }
        if ( v81 == 24 )
        {
          v20->Read(v20, &fileSize, 1);
          v20->Read(v20, &targa_rgba, 1);
          v20->Read(v20, (char *)&fileSize + 2, 1);
          v68 = (char)targa_rgba;
          v69 = fileSize;
          *v62 = BYTE2(fileSize);
          v70 = v62 + 1;
          *v70 = v68;
LABEL_93:
          v71 = v70 + 1;
          *v71 = v69;
          v67 = v71 + 1;
          *v67 = -1;
          goto LABEL_94;
        }
        if ( v81 != 32 )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
            common.type,
            "LoadTGA( %s ): illegal pixel_size '%d'\n",
            tileSize,
            v81);
          goto LABEL_95;
        }
        v20->Read(v20, (char *)&targa_rgba + 3, 1);
        v20->Read(v20, (char *)&targa_rgba + 1, 1);
        v20->Read(v20, (char *)&v103 + 3, 1);
        v20->Read(v20, &v106, 1);
        v63 = BYTE1(targa_rgba);
        v64 = HIBYTE(targa_rgba);
        *v62 = HIBYTE(v103);
        v65 = v106;
        v66 = v62 + 1;
        *v66++ = v63;
        *v66 = v64;
        v67 = v66 + 1;
        *v67 = v65;
LABEL_94:
        v62 = v67 + 1;
LABEL_95:
        --v93;
      }
      while ( v93 );
      v59 = v92;
LABEL_97:
      v60 += v96;
      if ( !--v95 )
      {
LABEL_98:
        v93 = 0;
        if ( name_s.len > 0 )
        {
          v72 = blockRowsRemaining;
          v96 = 4 * v92;
          v95 = (int)name;
          do
          {
            v73 = v95;
            v74 = 128;
            do
            {
              (*(void (__thiscall **)(int, int, int))(*(_DWORD *)v72 + 16))(v72, v73, 512);
              v73 += v96;
              --v74;
            }
            while ( v74 );
            v95 += 512;
            ++v93;
          }
          while ( (int)v93 < name_s.len );
        }
        if ( !mtHeader.tilesWide )
          break;
        goto LABEL_50;
      }
    }
  }
  R_StaticFree((void *)name);
  v75 = (void (__thiscall ***)(_DWORD, int))blockRowsRemaining;
  idMegaTexture::GenerateMegaMipMaps((megaTextureHeader_t *)&mtHeader.tilesHigh, (idFile *)blockRowsRemaining);
  (**v75)(v75, 1);
  ((void (__thiscall *)(idFile *, int))v20->~idFile)(v20, 1);
  idMegaTexture::GenerateMegaPreview(outName.data);
  LOBYTE(v115) = 0;
  idStr::FreeData(&outName);
  v115 = -1;
  idStr::FreeData(&name_s);
}

// FUNC: public: void __thiscall idMegaTexture::BindForViewOrigin(class idVec3)
void __thiscall idMegaTexture::BindForViewOrigin(idMegaTexture *this, idVec3 viewOrigin)
{
  idImage *v3; // eax
  signed int v4; // ebx
  int v5; // ebp
  int numLevels; // eax
  idImage *v7; // eax
  char *v8; // esi
  idImage *v9; // eax
  float parms[4]; // [esp+10h] [ebp-10h] BYREF

  idMegaTexture::SetViewOrigin(this, viewOrigin);
  GL_SelectTexture(0);
  v3 = globalImages->GetBorderClampImage(globalImages);
  v3->Bind(v3);
  v4 = 0;
  do
  {
    v5 = v4 + 1;
    GL_SelectTexture(v4 + 1);
    numLevels = this->numLevels;
    if ( v4 < numLevels )
    {
      v8 = (char *)this + 164 * (numLevels - v4) - 108;
      if ( idMegaTexture::r_showMegaTexture.internalVar->integerValue )
      {
        if ( (v4 & 1) != 0 )
          v9 = globalImages->GetBlackImage(globalImages);
        else
          v9 = globalImages->GetWhiteImage(globalImages);
        v9->Bind(v9);
      }
      else
      {
        (*(void (__thiscall **)(_DWORD))(**((_DWORD **)v8 + 4) + 4))(*((_DWORD *)v8 + 4));
      }
      qglProgramLocalParameter4fvARB(0x8620u, v4, (const float *)v8 + 37);
    }
    else
    {
      v7 = globalImages->GetWhiteImage(globalImages);
      v7->Bind(v7);
      qglProgramLocalParameter4fvARB(0x8620u, v4, ::parms);
    }
    ++v4;
  }
  while ( v5 < 7 );
  memset(parms, 0, 12);
  parms[3] = 1.0;
  qglProgramLocalParameter4fvARB(0x8620u, 7u, parms);
  parms[0] = 1.0;
  parms[1] = 1.0;
  parms[2] = idMegaTexture::r_terrainScale.internalVar->floatValue;
  parms[3] = 1.0;
  qglProgramLocalParameter4fvARB(0x8620u, 8u, parms);
}
