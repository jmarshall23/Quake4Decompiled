
// FUNC: _jpg_Error
void jpg_Error(const char *fmt, ...)
{
  char msg[2048]; // [esp+0h] [ebp-800h] BYREF
  va_list ap; // [esp+808h] [ebp+8h] BYREF

  va_start(ap, fmt);
  vsprintf(msg, fmt, ap);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(common.type, "%s", msg);
}

// FUNC: _jpg_Printf
void jpg_Printf(const char *fmt, ...)
{
  char msg[2048]; // [esp+0h] [ebp-800h] BYREF
  va_list ap; // [esp+808h] [ebp+8h] BYREF

  va_start(ap, fmt);
  vsprintf(msg, fmt, ap);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s", msg);
}

// FUNC: LoadTGA
void __usercall LoadTGA(
        unsigned int *timestamp@<eax>,
        const char *name,
        unsigned __int8 **pic,
        int *width,
        int *height)
{
  unsigned __int8 v5; // dl
  unsigned __int8 v6; // bl
  __int16 v7; // ax
  unsigned __int8 *v8; // esi
  __int16 v9; // cx
  __int16 v10; // dx
  __int16 v11; // ax
  __int16 v12; // cx
  unsigned __int16 v13; // di
  __int16 v14; // ax
  unsigned __int8 v15; // cl
  unsigned __int16 v16; // bp
  char *v17; // esi
  unsigned __int8 *v18; // ecx
  char v19; // bl
  int v20; // edi
  int v21; // edx
  unsigned __int8 *v22; // edi
  char v23; // al
  unsigned __int8 v24; // cl
  unsigned __int8 v25; // al
  _BYTE *v26; // esi
  unsigned __int8 v27; // cl
  char *v28; // esi
  unsigned __int8 v29; // cl
  _BYTE *v30; // esi
  unsigned __int8 v31; // al
  unsigned __int8 *v32; // ecx
  unsigned __int8 *v33; // edi
  int v34; // ebp
  unsigned __int8 v35; // al
  _BYTE *v36; // esi
  unsigned __int8 v37; // cl
  char v38; // dl
  _BYTE *v39; // esi
  unsigned __int8 *v40; // edi
  char *v41; // edi
  _BYTE *v42; // esi
  unsigned __int8 *v43; // edi
  int v44; // edi
  unsigned __int8 *v45; // eax
  int v46; // edi
  char v47; // cl
  char v48; // dl
  char *v49; // esi
  unsigned __int8 v50; // bl
  char *v51; // eax
  int v52; // edi
  char v53; // cl
  char v54; // dl
  _BYTE *v55; // esi
  char *v56; // eax
  int v57; // edx
  char v58; // cl
  char *v59; // eax
  unsigned __int8 green; // [esp+Dh] [ebp-31h]
  unsigned __int8 red; // [esp+Eh] [ebp-30h]
  unsigned __int8 red_1; // [esp+Fh] [ebp-2Fh]
  char red_1a; // [esp+Fh] [ebp-2Fh]
  char red_2; // [esp+10h] [ebp-2Eh]
  char red_2a; // [esp+10h] [ebp-2Eh]
  unsigned __int8 red_3; // [esp+11h] [ebp-2Dh]
  int row; // [esp+12h] [ebp-2Ch]
  int columns; // [esp+16h] [ebp-28h]
  int column; // [esp+1Ah] [ebp-24h]
  int columna; // [esp+1Ah] [ebp-24h]
  unsigned __int8 *targa_rgba; // [esp+1Eh] [ebp-20h]
  unsigned __int8 *targa_rgbaa; // [esp+1Eh] [ebp-20h]
  int fileSize; // [esp+22h] [ebp-1Ch]
  int fileSizea; // [esp+22h] [ebp-1Ch]
  unsigned __int8 *buffer; // [esp+26h] [ebp-18h] BYREF
  _TargaHeader targa_header; // [esp+2Ah] [ebp-14h]

  if ( !pic )
  {
    fileSystem->ReadFile(fileSystem, name, 0, timestamp);
    return;
  }
  *pic = 0;
  fileSize = fileSystem->ReadFile(fileSystem, name, (void **)&buffer, timestamp);
  if ( buffer )
  {
    v5 = buffer[1];
    v6 = buffer[2];
    v7 = *(_WORD *)(buffer + 3);
    v8 = buffer + 3;
    targa_header.id_length = *buffer;
    targa_header.colormap_type = v5;
    LittleShort(v7);
    v9 = *((_WORD *)v8 + 1);
    v8 += 2;
    LittleShort(v9);
    v10 = *(_WORD *)(v8 + 3);
    v8 += 3;
    LittleShort(v10);
    v11 = *((_WORD *)v8 + 1);
    v8 += 2;
    LittleShort(v11);
    v12 = *((_WORD *)v8 + 1);
    v8 += 2;
    v13 = LittleShort(v12);
    v14 = LittleShort(*((_WORD *)v8 + 1));
    v8 += 4;
    v15 = v8[1];
    v16 = v14;
    LOBYTE(v14) = *v8;
    v17 = (char *)(v8 + 2);
    targa_header.pixel_size = v14;
    targa_header.attributes = v15;
    if ( v6 != 2 && v6 != 10 && v6 != 3 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "LoadTGA( %s ): Only type 2 (RGB), 3 (gray), and 10 (RGB) TGA images supported\n",
        name);
    if ( targa_header.colormap_type )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "LoadTGA( %s ): colormaps not supported\n",
        name);
    if ( targa_header.pixel_size != 32 && targa_header.pixel_size != 24 && v6 != 3 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "LoadTGA( %s ): Only 32 or 24 bit images supported (no colormaps)\n",
        name);
    if ( (v6 == 2 || v6 == 3) && v13 * v16 * (targa_header.pixel_size >> 3) > fileSize - targa_header.id_length - 18 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "LoadTGA( %s ): incomplete file\n",
        name);
    columns = v13;
    if ( width )
      *width = v13;
    if ( height )
      *height = v16;
    v18 = (unsigned __int8 *)R_StaticAlloc(4 * v13 * v16);
    *pic = v18;
    targa_rgba = v18;
    if ( targa_header.id_length )
      v17 += targa_header.id_length;
    if ( v6 == 2 || v6 == 3 )
    {
      if ( v16 - 1 >= 0 )
      {
        v44 = -4 * v13;
        targa_rgbaa = &v18[4 * columns * (v16 - 1)];
        columna = v16;
        do
        {
          v45 = targa_rgbaa;
          switch ( targa_header.pixel_size )
          {
            case 8u:
              if ( columns > 0 )
              {
                v57 = columns;
                do
                {
                  v58 = *v17;
                  *v45 = *v17;
                  v59 = (char *)(v45 + 1);
                  *v59++ = v58;
                  *v59++ = v58;
                  *v59 = -1;
                  ++v17;
                  v45 = (unsigned __int8 *)(v59 + 1);
                  --v57;
                }
                while ( v57 );
              }
              break;
            case 0x18u:
              if ( columns > 0 )
              {
                v52 = columns;
                do
                {
                  v53 = *v17;
                  v54 = v17[1];
                  v55 = v17 + 1;
                  *v45 = v55[1];
                  v56 = (char *)(v45 + 1);
                  *v56++ = v54;
                  *v56++ = v53;
                  *v56 = -1;
                  v17 = v55 + 2;
                  v45 = (unsigned __int8 *)(v56 + 1);
                  --v52;
                }
                while ( v52 );
                v44 = -4 * columns;
              }
              break;
            case 0x20u:
              if ( columns > 0 )
              {
                v46 = columns;
                do
                {
                  v47 = *v17;
                  v48 = v17[1];
                  v49 = v17 + 1;
                  v50 = v49[1];
                  v49 += 2;
                  red_2a = *v49;
                  *v45 = v50;
                  v51 = (char *)(v45 + 1);
                  *v51++ = v48;
                  *v51++ = v47;
                  *v51 = red_2a;
                  v17 = v49 + 1;
                  v45 = (unsigned __int8 *)(v51 + 1);
                  --v46;
                }
                while ( v46 );
                v44 = -4 * columns;
              }
              break;
            default:
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
                common.type,
                "LoadTGA( %s ): illegal pixel_size '%d'\n",
                name,
                targa_header.pixel_size);
              break;
          }
          targa_rgbaa += v44;
          --columna;
        }
        while ( columna );
      }
    }
    else if ( v6 == 10 )
    {
      v19 = 0;
      v20 = v16 - 1;
      red = 0;
      green = 0;
      red_2 = -1;
      row = v20;
      if ( v20 >= 0 )
      {
        while ( 1 )
        {
          v21 = columns;
          v22 = &v18[4 * columns * v20];
          column = 0;
          if ( columns > 0 )
            break;
breakOut:
          v20 = --row;
          if ( row < 0 )
            goto LABEL_78;
          v18 = targa_rgba;
        }
        while ( 1 )
        {
          v23 = *v17;
          v24 = (*v17++ & 0x7F) + 1;
          red_3 = v24;
          if ( v23 < 0 )
          {
            if ( targa_header.pixel_size == 24 )
            {
              v19 = *v17;
              v29 = v17[1];
              v30 = v17 + 1;
              v31 = v30[1];
              v28 = v30 + 1;
              green = v29;
              red = v31;
              red_2 = -1;
            }
            else
            {
              if ( targa_header.pixel_size != 32 )
              {
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
                  common.type,
                  "LoadTGA( %s ): illegal pixel_size '%d'\n",
                  name,
                  targa_header.pixel_size);
                v21 = columns;
                goto LABEL_38;
              }
              v19 = *v17;
              v25 = v17[1];
              v26 = v17 + 1;
              v27 = v26[1];
              v28 = v26 + 2;
              green = v25;
              red = v27;
              red_2 = *v28;
            }
            v17 = v28 + 1;
LABEL_38:
            red_1 = 0;
            if ( red_3 )
            {
              v32 = &targa_rgba[4 * columns * row];
              do
              {
                *v22 = red;
                v33 = v22 + 1;
                *v33++ = green;
                *v33++ = v19;
                *v33 = red_2;
                v22 = v33 + 1;
                if ( ++column == columns )
                {
                  column = 0;
                  if ( row <= 0 )
                    goto breakOut;
                  --row;
                  v32 -= 4 * v21;
                  v22 = v32;
                }
                ++red_1;
              }
              while ( red_1 < red_3 );
              v21 = columns;
            }
            goto LABEL_57;
          }
          red_1a = 0;
          if ( v24 )
            break;
LABEL_57:
          if ( column >= v21 )
            goto breakOut;
        }
        v34 = -4 * v21;
        fileSizea = (int)&targa_rgba[4 * v21 * row];
        while ( targa_header.pixel_size != 24 )
        {
          if ( targa_header.pixel_size == 32 )
          {
            v19 = *v17;
            v35 = v17[1];
            v36 = v17 + 1;
            v37 = *++v36;
            v38 = v36[1];
            *v22 = v37;
            v39 = v36 + 1;
            v40 = v22 + 1;
            *v40++ = v35;
            *v40 = v19;
            v41 = (char *)(v40 + 1);
            red_2 = v38;
            *v41 = v38;
            v21 = columns;
LABEL_52:
            v17 = v39 + 1;
            green = v35;
            red = v37;
            v22 = (unsigned __int8 *)(v41 + 1);
            goto LABEL_53;
          }
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
            common.type,
            "LoadTGA( %s ): illegal pixel_size '%d'\n",
            name,
            targa_header.pixel_size);
          v21 = columns;
LABEL_53:
          if ( ++column == v21 )
          {
            column = 0;
            if ( row <= 0 )
              goto breakOut;
            --row;
            v22 = (unsigned __int8 *)(v34 + fileSizea);
            fileSizea += v34;
          }
          if ( (unsigned __int8)++red_1a >= red_3 )
            goto LABEL_57;
        }
        v19 = *v17;
        v35 = v17[1];
        v42 = v17 + 1;
        v37 = v42[1];
        v39 = v42 + 1;
        *v22 = v37;
        v43 = v22 + 1;
        *v43++ = v35;
        *v43 = v19;
        v41 = (char *)(v43 + 1);
        *v41 = -1;
        goto LABEL_52;
      }
    }
LABEL_78:
    if ( (targa_header.attributes & 0x20) != 0 )
      R_VerticalFlip(*pic, *width, *height);
    fileSystem->FreeFile(fileSystem, buffer);
  }
}

// FUNC: LoadJPG
void __usercall LoadJPG(
        unsigned int *timestamp@<eax>,
        int a2@<edi>,
        const char *filename,
        unsigned __int8 **pic,
        int *width,
        int *height)
{
  idFile *v7; // eax
  idFile *v8; // esi
  int v9; // edi
  unsigned __int8 *v10; // ebx
  unsigned int v11; // esi
  unsigned __int8 *v12; // edi
  unsigned int output_width; // eax
  unsigned int output_height; // eax
  unsigned int output_scanline; // ecx
  int v16; // edx
  signed int v17; // eax
  int i; // ecx
  unsigned __int8 *bbuf; // [esp+18h] [ebp-230h] BYREF
  jpeg_decompress_struct cinfo; // [esp+1Ch] [ebp-22Ch] BYREF
  jpeg_error_mgr jerr; // [esp+1C4h] [ebp-84h] BYREF

  if ( pic )
    *pic = 0;
  v7 = fileSystem->OpenFileRead(fileSystem, filename, 1, 0);
  v8 = v7;
  if ( v7 )
  {
    v9 = ((int (__thiscall *)(idFile *, int))v7->Length)(v7, a2);
    if ( timestamp )
      *timestamp = v8->Timestamp(v8);
    if ( pic )
    {
      v10 = (unsigned __int8 *)Mem_ClearedAlloc(v9 + 4096, 0xCu);
      ((void (__thiscall *)(idFile *, unsigned __int8 *))v8->Read)(v8, v10);
      fileSystem->CloseFile(fileSystem, v8);
      cinfo.err = jpeg_std_error(&jerr);
      jpeg_create_decompress(&cinfo);
      jpeg_stdio_src(&cinfo, v10);
      jpeg_read_header(&cinfo, 1u);
      jpeg_start_decompress(&cinfo);
      v11 = cinfo.output_width * cinfo.output_components;
      if ( cinfo.output_components != 4 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 140))(
          common.type,
          "JPG %s is unsupported color depth (%d)",
          filename,
          cinfo.output_components);
      v12 = (unsigned __int8 *)R_StaticAlloc(4 * cinfo.output_width * cinfo.output_height);
      output_width = cinfo.output_width;
      *pic = v12;
      *width = output_width;
      output_height = cinfo.output_height;
      *height = cinfo.output_height;
      output_scanline = cinfo.output_scanline;
      if ( cinfo.output_scanline < output_height )
      {
        do
        {
          bbuf = &v12[v11 * output_scanline];
          jpeg_read_scanlines(&cinfo, &bbuf, 1u);
          output_scanline = cinfo.output_scanline;
          output_height = cinfo.output_height;
        }
        while ( cinfo.output_scanline < cinfo.output_height );
      }
      v16 = (int)*pic;
      v17 = 4 * cinfo.output_width * output_height;
      for ( i = 3; i < v17; i += 4 )
        *(_BYTE *)(i + v16) = -1;
      jpeg_finish_decompress(&cinfo);
      jpeg_destroy_decompress((jpeg_compress_struct *)&cinfo);
      Mem_Free(v10);
    }
    else
    {
      fileSystem->CloseFile(fileSystem, v8);
    }
  }
}

// FUNC: bool __cdecl R_LoadCubeImages(char const *,enum cubeFiles_t,unsigned char * * const,int *,unsigned int *)
char __cdecl R_LoadCubeImages(
        const char *imgName,
        cubeFiles_t extensions,
        unsigned __int8 **pics,
        int *outSize,
        unsigned int *timestamp)
{
  int v5; // ebp
  int i; // esi
  int v7; // eax
  int v8; // ecx
  int j; // ebx
  bool bWriteProgramFlag; // [esp+13h] [ebp-145h]
  int width; // [esp+14h] [ebp-144h] BYREF
  int height; // [esp+18h] [ebp-140h] BYREF
  int size; // [esp+1Ch] [ebp-13Ch]
  char **sides; // [esp+20h] [ebp-138h]
  unsigned int thisTime; // [esp+24h] [ebp-134h] BYREF
  char *cameraSides[6]; // [esp+28h] [ebp-130h] BYREF
  char *axisSides[6]; // [esp+40h] [ebp-118h] BYREF
  char fullName[256]; // [esp+58h] [ebp-100h] BYREF

  v5 = 0;
  cameraSides[0] = "_forward.tga";
  cameraSides[1] = "_back.tga";
  cameraSides[2] = "_left.tga";
  cameraSides[3] = "_right.tga";
  cameraSides[4] = "_up.tga";
  cameraSides[5] = "_down.tga";
  axisSides[0] = "_px.tga";
  axisSides[1] = "_nx.tga";
  axisSides[2] = "_py.tga";
  axisSides[3] = "_ny.tga";
  axisSides[4] = "_pz.tga";
  axisSides[5] = "_nz.tga";
  size = 0;
  if ( extensions == CF_CAMERA )
    sides = cameraSides;
  else
    sides = axisSides;
  if ( pics )
  {
    *pics = 0;
    pics[1] = 0;
    pics[2] = 0;
    pics[3] = 0;
    pics[4] = 0;
    pics[5] = 0;
  }
  if ( timestamp )
    *timestamp = 0;
  bWriteProgramFlag = gWriteProgramFlag;
  for ( i = 0; i < 6; ++i )
  {
    idStr::snPrintf(fullName, 256, "%s%s", imgName, sides[i]);
    if ( pics )
      R_LoadImageProgram(fullName, &pics[i], &width, &height, &thisTime, 0);
    else
      R_LoadImageProgram(fullName, 0, &width, &height, &thisTime, 0);
    if ( thisTime == -1 )
      break;
    v7 = width;
    if ( i )
    {
      if ( width != v5 )
        goto LABEL_29;
    }
    else
    {
      v5 = width;
      size = width;
    }
    v8 = height;
    if ( height != v5 )
    {
LABEL_29:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "Mismatched sizes on cube map '%s'",
        imgName);
      break;
    }
    if ( timestamp && thisTime > *timestamp )
      *timestamp = thisTime;
    if ( pics && extensions == CF_CAMERA )
    {
      switch ( i )
      {
        case 0:
        case 4:
        case 5:
          R_RotatePic(pics[i], v7);
          break;
        case 1:
          R_RotatePic(pics[i], v7);
          R_HorizontalFlip(pics[i], width, height);
          R_VerticalFlip(pics[i], width, height);
          break;
        case 2:
          R_VerticalFlip(pics[i], v7, v8);
          break;
        case 3:
          R_HorizontalFlip(pics[i], v7, v8);
          break;
        default:
          break;
      }
    }
    v5 = size;
  }
  if ( *timestamp > ProgramImagesTimestamp )
    gWriteProgramFlag = bWriteProgramFlag;
  if ( i == 6 )
  {
    if ( outSize )
      *outSize = v5;
    return 1;
  }
  else
  {
    if ( pics )
    {
      for ( j = 0; j < i; ++j )
        R_StaticFree(pics[j]);
    }
    *timestamp = 0;
    return 0;
  }
}

// FUNC: void __cdecl R_WriteTGA(char const *,unsigned char const *,int,int,bool)
void __cdecl R_WriteTGA(const char *filename, const unsigned __int8 *data, int width, int height, bool flipVertical)
{
  int v5; // ebp
  char *v6; // esi
  const unsigned __int8 *v7; // eax
  unsigned __int8 *v8; // ecx
  unsigned int v9; // edi
  idFileSystem_vtbl *v10; // edx

  v5 = 4 * height * width + 18;
  v6 = (char *)Mem_Alloc(v5, 0xCu);
  *(_DWORD *)v6 = 0;
  *((_DWORD *)v6 + 1) = 0;
  *((_DWORD *)v6 + 2) = 0;
  *((_DWORD *)v6 + 3) = 0;
  *((_WORD *)v6 + 8) = 0;
  v6[14] = height;
  v6[12] = width;
  v6[15] = BYTE1(height);
  v6[2] = 2;
  v6[13] = BYTE1(width);
  v6[16] = 32;
  if ( !flipVertical )
    v6[17] = 32;
  if ( v5 > 18 )
  {
    v7 = data + 1;
    v8 = (unsigned __int8 *)(v6 + 19);
    v9 = ((unsigned int)(4 * height * width - 1) >> 2) + 1;
    do
    {
      *(v8 - 1) = v7[1];
      *v8 = *v7;
      v8[1] = *(v7 - 1);
      v8[2] = v7[2];
      v7 += 4;
      v8 += 4;
      --v9;
    }
    while ( v9 );
  }
  v10 = fileSystem->__vftable;
  if ( image_writeProgramImages.internalVar->integerValue )
    ((void (__stdcall *)(const char *, char *, int, const char *))v10->WriteFile)(filename, v6, v5, "fs_devpath");
  else
    ((void (__stdcall *)(const char *, char *, int, const char *))v10->WriteFile)(filename, v6, v5, "fs_savepath");
  Mem_Free(v6);
}

// FUNC: void __cdecl R_LoadImage(char const *,unsigned char * *,int *,int *,unsigned int *,bool)
void __cdecl R_LoadImage(
        const char *cname,
        unsigned __int8 **pic,
        int *width,
        int *height,
        unsigned int *timestamp,
        bool makePowerOf2)
{
  int v6; // edi
  const char *v7; // eax
  int v8; // eax
  char *data; // edx
  const char *v10; // ecx
  char v11; // al
  char *v12; // ecx
  unsigned __int8 v13; // al
  int i; // esi
  int *v15; // edi
  int v16; // eax
  int v17; // ecx
  int j; // edi
  int k; // esi
  bool v20; // cc
  unsigned __int8 *v21; // ebp
  idStr name; // [esp+10h] [ebp-4Ch] BYREF
  idStr ext; // [esp+30h] [ebp-2Ch] BYREF
  int v24; // [esp+58h] [ebp-4h]

  v6 = 0;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  if ( cname )
  {
    v7 = &cname[strlen(cname) + 1];
    v6 = v7 - (cname + 1);
    v8 = v7 - cname;
    if ( v8 > 20 )
      idStr::ReAllocate(&name, v8, 1);
    data = name.data;
    v10 = cname;
    do
    {
      v11 = *v10;
      *data++ = *v10++;
    }
    while ( v11 );
    name.len = v6;
  }
  v24 = 0;
  if ( pic )
    *pic = 0;
  if ( timestamp )
    *timestamp = -1;
  if ( width )
    *width = 0;
  if ( height )
    *height = 0;
  if ( v6 >= 1 )
  {
    idStr::DefaultFileExtension(&name, ".tga");
    v12 = name.data;
    v13 = *name.data;
    for ( i = 0; v13; v13 = name.data[i] )
    {
      if ( idStr::lowerCaseCharacter[v13] )
        v13 = idStr::lowerCaseCharacter[v13];
      *v12 = v13;
      v12 = &name.data[++i];
    }
    ext.len = 0;
    ext.alloced = 20;
    ext.data = ext.baseBuffer;
    ext.baseBuffer[0] = 0;
    LOBYTE(v24) = 1;
    idStr::ExtractFileExtension(&name, &ext);
    if ( idStr::Cmp(ext.data, "tga") )
    {
      if ( !idStr::Cmp(ext.data, "jpg") )
        LoadJPG(timestamp, v6, name.data, pic, width, height);
      v15 = width;
    }
    else
    {
      v15 = width;
      LoadTGA(timestamp, name.data, pic, width, height);
      if ( pic && !*pic || timestamp && *timestamp == -1 )
      {
        idStr::StripFileExtension(&name);
        idStr::DefaultFileExtension(&name, ".jpg");
        LoadJPG(timestamp, (int)width, name.data, pic, width, height);
      }
    }
    if ( v15 && *v15 < 1 || height && *height < 1 )
    {
      if ( !pic )
        goto LABEL_51;
      if ( *pic )
      {
        R_StaticFree(*pic);
        *pic = 0;
      }
    }
    if ( pic && *pic && makePowerOf2 )
    {
      v16 = *v15;
      v17 = *height;
      for ( j = 1; j < v16; j *= 2 )
        ;
      for ( k = 1; k < v17; k *= 2 )
        ;
      v20 = j <= v16;
      if ( j != v16 )
        goto LABEL_46;
      if ( k != v17 )
      {
        v20 = j <= v16;
LABEL_46:
        if ( !v20 )
          j >>= 1;
        if ( k > v17 )
          k >>= 1;
        v21 = R_ResampleTexture(*pic, v16, v17, j, k);
        R_StaticFree(*pic);
        *pic = v21;
        *width = j;
        *height = k;
      }
    }
LABEL_51:
    LOBYTE(v24) = 0;
    idStr::FreeData(&ext);
  }
  v24 = -1;
  idStr::FreeData(&name);
}
