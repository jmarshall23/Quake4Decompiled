
// FUNC: R_ImageScale
void __usercall R_ImageScale(unsigned __int8 *data@<edi>, int width@<eax>, int height, float *scale)
{
  int v4; // ebx
  int i; // esi

  v4 = 4 * height * width;
  for ( i = 0; i < v4; ++i )
    data[i] = (unsigned __int64)((double)data[i] * scale[i & 3]);
}

// FUNC: R_InvertAlpha
void __usercall R_InvertAlpha(int width@<eax>, unsigned __int8 *data, int height)
{
  int v3; // eax
  unsigned int v4; // ecx
  unsigned __int8 *v5; // eax
  unsigned int v6; // ecx
  unsigned __int8 v7; // dl

  v3 = 4 * height * width;
  if ( v3 > 0 )
  {
    v4 = (unsigned int)(v3 - 1) >> 2;
    v5 = data + 3;
    v6 = v4 + 1;
    do
    {
      v7 = -1 - *v5;
      v5 += 4;
      --v6;
      *(v5 - 4) = v7;
    }
    while ( v6 );
  }
}

// FUNC: R_InvertColor
void __usercall R_InvertColor(int width@<eax>, unsigned __int8 *data, int height)
{
  int v3; // eax
  unsigned int v4; // ecx
  unsigned __int8 *v5; // eax
  unsigned int v6; // ecx
  unsigned __int8 v7; // dl

  v3 = 4 * height * width;
  if ( v3 > 0 )
  {
    v4 = (unsigned int)(v3 - 1) >> 2;
    v5 = data + 1;
    v6 = v4 + 1;
    do
    {
      v7 = -1 - *(v5 - 1);
      v5 += 4;
      *(v5 - 5) = v7;
      *(v5 - 4) = -1 - *(v5 - 4);
      --v6;
      *(v5 - 3) = -1 - *(v5 - 3);
    }
    while ( v6 );
  }
}

// FUNC: R_ImageAdd
void __usercall R_ImageAdd(
        unsigned __int8 *data2@<ecx>,
        int width2@<eax>,
        int height2@<edx>,
        unsigned __int8 *data1,
        int width1,
        int height1)
{
  unsigned __int8 *v6; // eax
  int v7; // esi
  unsigned __int8 *v8; // edx
  int v9; // edi
  int v10; // ecx

  if ( width2 == width1 && height2 == height1 )
  {
    v6 = 0;
  }
  else
  {
    v6 = R_Dropsample(data2, width2, height2, width1, height1);
    data2 = v6;
  }
  v7 = 4 * height1 * width1;
  if ( v7 > 0 )
  {
    v8 = data1;
    v9 = data2 - data1;
    do
    {
      v10 = *v8 + v8[v9];
      if ( v10 > 255 )
        LOBYTE(v10) = -1;
      *v8++ = v10;
      --v7;
    }
    while ( v7 );
  }
  if ( v6 )
    R_StaticFree(v6);
}

// FUNC: MatchAndAppendToken
void __usercall MatchAndAppendToken(idLexer *src@<ecx>, const char *match@<esi>)
{
  if ( idLexer::ExpectTokenString(src, match) )
    idStr::Append(parseBuffer, 256, match);
}

// FUNC: R_HeightmapToNormalMapFast
void __cdecl R_HeightmapToNormalMapFast(unsigned __int8 *data, int width, int height, float scale, const char *name)
{
  int v5; // ebx
  int v6; // ebp
  int v7; // esi
  unsigned __int8 *v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  unsigned __int8 *v12; // esi
  int v13; // eax
  int v14; // ecx
  int v15; // ebp
  unsigned __int8 *v16; // ecx
  int v17; // edi
  unsigned __int8 *v18; // ecx
  unsigned __int8 *v19; // edx
  int v20; // eax
  double v21; // st7
  double v22; // st6
  bool v23; // zf
  float scaleInv2; // [esp+2h] [ebp-34h]
  int v25; // [esp+Ah] [ebp-2Ch]
  float v26; // [esp+Ah] [ebp-2Ch]
  float v27; // [esp+Ah] [ebp-2Ch]
  float v28; // [esp+Ah] [ebp-2Ch]
  float v29; // [esp+Ah] [ebp-2Ch]
  unsigned __int8 *row1; // [esp+Eh] [ebp-28h]
  unsigned __int8 *v31; // [esp+12h] [ebp-24h]
  int v32; // [esp+16h] [ebp-20h]
  unsigned __int8 *v33; // [esp+1Ah] [ebp-1Ch]
  unsigned __int8 *depth; // [esp+1Eh] [ebp-18h]
  float v35; // [esp+22h] [ebp-14h]
  int v36; // [esp+26h] [ebp-10h]
  float dir; // [esp+2Ah] [ebp-Ch]
  float dir_4; // [esp+2Eh] [ebp-8h]
  float dir_8; // [esp+32h] [ebp-4h]

  v5 = width;
  if ( scale <= 0.000001 )
  {
    scaleInv2 = 512000000.0;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Redundant bumpmap (flat, scale <= 0) : %s",
      name);
  }
  else
  {
    scaleInv2 = 2.0 / (scale * 0.00390625);
  }
  v6 = height;
  v7 = height * width;
  v8 = (unsigned __int8 *)R_StaticAlloc(height * width);
  v9 = 0;
  for ( depth = v8; v9 < v7; ++v9 )
    v8[v9] = data[4 * v9];
  v10 = 1;
  if ( v7 <= 1 )
    goto LABEL_11;
  while ( v8[v10] == *v8 )
  {
    if ( ++v10 >= v7 )
      goto LABEL_11;
  }
  if ( v10 >= v7 )
LABEL_11:
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Redundant bumpmap (flat) : %s",
      name);
  v11 = 0;
  if ( height > 0 )
  {
    v12 = v8;
    v33 = v8;
    v31 = &data[4 * width];
    while ( 1 )
    {
      v13 = v11 + 1;
      v14 = v5 * (v13 & (v6 - 1));
      v15 = v8[v14];
      v16 = &v8[v14];
      v17 = *v12;
      v36 = v13;
      v18 = &v16[v5 - 1];
      row1 = &v12[v5 - 1];
      v19 = v31;
      if ( v5 - 1 >= 0 )
      {
        v32 = v5;
        do
        {
          v20 = *row1;
          v21 = (double)(v20 + *v18 - v15 - v17);
          v22 = (double)(v17 + v20 - *v18 - v15);
          v19 -= 4;
          v15 = *v18;
          v35 = scaleInv2 * scaleInv2;
          *(float *)&v25 = v22 * v22 + v21 * v21 + v35;
          --row1;
          --v18;
          v17 = v20;
          v26 = (1.5
               - *(float *)&v25 * 0.5 * COERCE_FLOAT(1597463007 - (v25 >> 1)) * COERCE_FLOAT(1597463007 - (v25 >> 1)))
              * COERCE_FLOAT(1597463007 - (v25 >> 1));
          dir = v21 * v26;
          dir_4 = v22 * v26;
          dir_8 = v26 * scaleInv2;
          v27 = dir * 127.0 + 128.0;
          *v19 = (int)fminf(fmaxf(v27, 0.0), 255.0);
          v28 = dir_4 * 127.0 + 128.0;
          v19[1] = (int)fminf(fmaxf(v28, 0.0), 255.0);
          v29 = dir_8 * 127.0 + 128.0;
          v23 = v32-- == 1;
          v19[2] = (int)fminf(fmaxf(v29, 0.0), 255.0);
          v19[3] = -1;
        }
        while ( !v23 );
        v5 = width;
        v12 = v33;
      }
      v11 = v36;
      v8 = depth;
      v31 += 4 * v5;
      v12 += v5;
      v33 = v12;
      if ( v36 >= height )
        break;
      v6 = height;
    }
  }
  R_StaticFree(v8);
}

// FUNC: R_AddNormalMaps
void __usercall R_AddNormalMaps(
        int height1@<edx>,
        int width2@<eax>,
        int height2@<ecx>,
        unsigned __int8 *data1,
        int width1,
        unsigned __int8 *data2)
{
  unsigned __int8 *v7; // ebx
  unsigned __int8 *v8; // ecx
  unsigned __int8 *v9; // edx
  int v10; // edi
  double v11; // st7
  double v12; // st6
  double v13; // st7
  long double v14; // st6
  long double v15; // st6
  bool v16; // zf
  unsigned __int8 *v17; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  unsigned __int8 *newMap; // [esp+14h] [ebp-14h]
  float v20; // [esp+18h] [ebp-10h]
  float v21; // [esp+18h] [ebp-10h]
  float v22; // [esp+18h] [ebp-10h]
  float n_4; // [esp+20h] [ebp-8h]
  float n_4a; // [esp+20h] [ebp-8h]
  float n_8; // [esp+24h] [ebp-4h]

  if ( width2 == width1 && height2 == height1 )
  {
    newMap = 0;
  }
  else
  {
    newMap = R_Dropsample(data2, width2, height2, width1, height1);
    data2 = newMap;
  }
  if ( height1 > 0 )
  {
    v7 = data2;
    v8 = data1 + 1;
    v17 = data1 + 1;
    v18 = height1;
    do
    {
      if ( width1 > 0 )
      {
        v9 = v7;
        v10 = width1;
        do
        {
          v11 = (double)(*(v8 - 1) - 128) * 0.0078740157;
          n_4 = (double)(*v8 - 128) * 0.0078740157;
          n_8 = (double)(v8[1] - 128) * 0.0078740157;
          v12 = n_4 * n_4;
          if ( n_8 * n_8 + v11 * v11 + v12 < 0.95999998 )
            n_8 = sqrt(1.0 - v11 * v11 - v12);
          v13 = v11 + (double)(*v9 - 128) * 0.0078740157;
          n_4a = (double)(v8[data2 - data1] - 128) * 0.0078740157 + n_4;
          v14 = n_8 * n_8 + n_4a * n_4a + v13 * v13;
          if ( v14 != 0.0 )
          {
            v15 = 1.0 / sqrt(v14);
            v13 = v13 * v15;
            n_4a = n_4a * v15;
            n_8 = n_8 * v15;
          }
          v20 = v13 * 127.0 + 128.0;
          *(v8 - 1) = (int)fminf(fmaxf(v20, 0.0), 255.0);
          v21 = n_4a * 127.0 + 128.0;
          *v8 = (int)fminf(fmaxf(v21, 0.0), 255.0);
          v22 = n_8 * 127.0 + 128.0;
          v8[1] = (int)fminf(fmaxf(v22, 0.0), 255.0);
          v8[2] = -1;
          v8 += 4;
          v9 += 4;
          --v10;
        }
        while ( v10 );
      }
      v8 = &v17[4 * width1];
      v7 += 4 * width1;
      v16 = v18-- == 1;
      v17 = v8;
    }
    while ( !v16 );
  }
  if ( newMap )
    R_StaticFree(newMap);
}

// FUNC: R_SmoothNormalMap
void __usercall R_SmoothNormalMap(unsigned __int8 *data@<eax>, int width, int height)
{
  int v3; // ebx
  unsigned __int8 *v5; // ebp
  unsigned __int8 *v6; // edi
  int v7; // ecx
  double x; // st7
  double y; // st6
  double z; // st5
  int v11; // edi
  int v12; // ebp
  int v13; // ebx
  float *v14; // ecx
  int v15; // esi
  unsigned __int8 *v16; // eax
  unsigned __int8 v17; // dl
  unsigned __int8 *v18; // eax
  unsigned __int8 v19; // dl
  unsigned __int8 *v20; // eax
  unsigned __int8 v21; // dl
  long double v22; // st5
  long double v23; // st5
  bool v24; // cc
  unsigned __int8 *orig; // [esp+10h] [ebp-28h]
  int v26; // [esp+14h] [ebp-24h]
  float v27; // [esp+14h] [ebp-24h]
  int v28; // [esp+18h] [ebp-20h]
  int i; // [esp+1Ch] [ebp-1Ch]
  unsigned __int8 *v30; // [esp+20h] [ebp-18h]
  unsigned __int8 *v31; // [esp+24h] [ebp-14h]
  float normal_4; // [esp+30h] [ebp-8h]
  float normal_8; // [esp+34h] [ebp-4h]

  v3 = width;
  v5 = (unsigned __int8 *)R_StaticAlloc(4 * height * width);
  orig = v5;
  SIMDProcessor->Memcpy(SIMDProcessor, v5, data, 4 * height * width);
  i = 0;
  if ( width > 0 )
  {
    v6 = data + 2;
    v31 = v6;
    do
    {
      if ( height > 0 )
      {
        v7 = 1;
        v28 = 1;
        v30 = v6;
        while ( 1 )
        {
          x = vec3_origin.x;
          y = vec3_origin.y;
          z = vec3_origin.z;
          v11 = v3 * ((height - 1) & (v7 - 2));
          v12 = v3 * ((height - 1) & (v7 - 1));
          v13 = width * (v7 & (height - 1));
          v26 = i - 1;
          v14 = &factors[0][1];
          do
          {
            v15 = (width - 1) & v26;
            v16 = &orig[4 * v15 + 4 * v11];
            v17 = *v16;
            if ( (*v16 || v16[1] || v16[2]) && (v17 != 0x80 || v16[1] != v17 || v16[2] != v17) )
            {
              x = x + (double)(v17 - 128) * *(v14 - 1);
              y = y + (double)(v16[1] - 128) * *(v14 - 1);
              z = z + (double)(v16[2] - 128) * *(v14 - 1);
            }
            v18 = &orig[4 * v15 + 4 * v12];
            v19 = *v18;
            if ( (*v18 || v18[1] || v18[2]) && (v19 != 0x80 || v18[1] != v19 || v18[2] != v19) )
            {
              x = x + (double)(v19 - 128) * *v14;
              y = y + (double)(v18[1] - 128) * *v14;
              z = z + (double)(v18[2] - 128) * *v14;
            }
            v20 = &orig[4 * v13 + 4 * v15];
            v21 = *v20;
            if ( (*v20 || v20[1] || v20[2]) && (v21 != 0x80 || v20[1] != v21 || v20[2] != v21) )
            {
              x = x + (double)(v21 - 128) * v14[1];
              y = y + (double)(v20[1] - 128) * v14[1];
              z = z + (double)(v20[2] - 128) * v14[1];
            }
            ++v26;
            v14 += 3;
          }
          while ( (int)v14 < (int)&infoParms[0].clearSolid );
          normal_8 = z;
          normal_4 = y;
          v22 = z * z + y * y + x * x;
          if ( v22 != 0.0 )
          {
            v23 = 1.0 / sqrt(v22);
            v27 = v23;
            x = x * v23;
            normal_4 = y * v27;
            normal_8 = normal_8 * v27;
          }
          *(v30 - 2) = (unsigned __int64)(x * 127.0 + 128.0);
          *(v30 - 1) = (unsigned __int64)(normal_4 * 127.0 + 128.0);
          v3 = width;
          *v30 = (unsigned __int64)(normal_8 * 127.0 + 128.0);
          ++v28;
          v30 += 4 * width;
          if ( v28 - 1 >= height )
            break;
          v7 = v28;
        }
      }
      v6 = v31 + 4;
      v24 = ++i < v3;
      v31 += 4;
    }
    while ( v24 );
    v5 = orig;
  }
  R_StaticFree(v5);
}

// FUNC: AppendToken
void __cdecl AppendToken(idToken *token)
{
  if ( parseBuffer[0] )
    idStr::Append(parseBuffer, 256, " ");
  idStr::Append(parseBuffer, 256, token->data);
}

// FUNC: R_ParseImageProgram_r
char __cdecl R_ParseImageProgram_r(
        idLexer *src,
        unsigned __int8 **pic,
        int *width,
        int *height,
        unsigned int *timestamps,
        textureDepth_t *depth)
{
  bool v6; // al
  long double floatvalue; // st7
  bool v8; // al
  bool v9; // al
  int i; // esi
  long double v12; // st7
  int v13; // ecx
  int j; // eax
  unsigned __int8 *v15; // edi
  int v16; // ebx
  int k; // ecx
  char intvalue; // si
  int v19; // eax
  unsigned __int8 *v20; // eax
  int len; // ebp
  unsigned int v22; // eax
  unsigned __int8 *v23; // [esp-20h] [ebp-A4h]
  unsigned __int8 *pic2; // [esp+8h] [ebp-7Ch] BYREF
  int height2; // [esp+Ch] [ebp-78h] BYREF
  unsigned __int8 *newPic; // [esp+10h] [ebp-74h] BYREF
  unsigned int timestamp; // [esp+14h] [ebp-70h] BYREF
  float scale[4]; // [esp+18h] [ebp-6Ch] BYREF
  idToken token; // [esp+28h] [ebp-5Ch] BYREF
  int v30; // [esp+80h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v30 = 0;
  idLexer::ReadToken(src, &token);
  if ( parseBuffer[0] )
    idStr::Append(parseBuffer, 256, " ");
  idStr::Append(parseBuffer, 256, token.data);
  if ( !idStr::Icmp(token.data, "heightmap") )
  {
    if ( idLexer::ExpectTokenString(src, "(") )
      idStr::Append(parseBuffer, 256, "(");
    gWriteProgramFlag = 1;
    g_psSpecialPassType = "heightmap";
    v6 = R_ParseImageProgram_r(src, pic, width, height, timestamps, depth);
    g_psSpecialPassType = 0;
    if ( v6 )
    {
      if ( idLexer::ExpectTokenString(src, ",") )
        idStr::Append(parseBuffer, 256, ",");
      idLexer::ReadToken(src, &token);
      AppendToken(&token);
      if ( token.type == 3 )
      {
        if ( (token.subtype & 0x10000) == 0 )
          idToken::NumberValue(&token);
        floatvalue = token.floatvalue;
      }
      else
      {
        floatvalue = 0.0;
      }
      *(float *)&pic2 = floatvalue;
      if ( pic )
      {
        R_HeightmapToNormalMapFast(*pic, *width, *height, *(float *)&pic2, tr.lastLoadedImage.data);
        if ( depth )
          *depth = TD_BUMP;
      }
      if ( idLexer::ExpectTokenString(src, ")") )
      {
LABEL_18:
        idStr::Append(parseBuffer, 256, ")");
        v30 = -1;
LABEL_117:
        idStr::FreeData(&token);
        return 1;
      }
LABEL_73:
      v30 = -1;
      goto LABEL_117;
    }
    goto LABEL_49;
  }
  if ( !idStr::Icmp(token.data, "addnormals") )
  {
    if ( idLexer::ExpectTokenString(src, "(") )
      idStr::Append(parseBuffer, 256, "(");
    gWriteProgramFlag = 1;
    g_psSpecialPassType = "addnormals";
    v8 = R_ParseImageProgram_r(src, pic, width, height, timestamps, depth);
    g_psSpecialPassType = 0;
    if ( !v8 )
      goto LABEL_49;
    if ( idLexer::ExpectTokenString(src, ",") )
      idStr::Append(parseBuffer, 256, ",");
    g_psSpecialPassType = "addnormals";
    v9 = R_ParseImageProgram_r(src, pic != 0 ? &pic2 : 0, (int *)&newPic, &height2, timestamps, depth);
    g_psSpecialPassType = 0;
    if ( v9 )
    {
      if ( pic )
      {
        R_AddNormalMaps(*height, (int)newPic, height2, *pic, *width, pic2);
        R_StaticFree(pic2);
        if ( depth )
          *depth = TD_BUMP;
      }
      if ( idLexer::ExpectTokenString(src, ")") )
      {
        idStr::Append(parseBuffer, 256, ")");
        v30 = -1;
        goto LABEL_117;
      }
      goto LABEL_73;
    }
    if ( !pic )
      goto LABEL_49;
LABEL_48:
    R_StaticFree(*pic);
    *pic = 0;
    goto LABEL_49;
  }
  if ( !idStr::Icmp(token.data, "smoothnormals") )
  {
    if ( idLexer::ExpectTokenString(src, "(") )
      idStr::Append(parseBuffer, 256, "(");
    gWriteProgramFlag = 1;
    if ( R_ParseImageProgram_r(src, pic, width, height, timestamps, depth) )
    {
      if ( pic )
      {
        R_SmoothNormalMap(*pic, *width, *height);
        if ( depth )
          *depth = TD_BUMP;
      }
      if ( idLexer::ExpectTokenString(src, ")") )
        goto LABEL_18;
      goto LABEL_73;
    }
LABEL_49:
    v30 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  if ( !idStr::Icmp(token.data, "add") )
  {
    if ( idLexer::ExpectTokenString(src, "(") )
      idStr::Append(parseBuffer, 256, "(");
    gWriteProgramFlag = 1;
    if ( !R_ParseImageProgram_r(src, pic, width, height, timestamps, depth) )
      goto LABEL_49;
    MatchAndAppendToken(src, ",");
    if ( !R_ParseImageProgram_r(src, pic != 0 ? &pic2 : 0, &height2, (int *)&newPic, timestamps, depth) )
    {
      if ( !pic )
        goto LABEL_49;
      goto LABEL_48;
    }
    if ( pic )
    {
      R_ImageAdd(pic2, height2, (int)newPic, *pic, *width, *height);
      R_StaticFree(pic2);
    }
LABEL_72:
    MatchAndAppendToken(src, ")");
    goto LABEL_73;
  }
  if ( !idStr::Icmp(token.data, "scale") )
  {
    MatchAndAppendToken(src, "(");
    gWriteProgramFlag = 1;
    R_ParseImageProgram_r(src, pic, width, height, timestamps, depth);
    for ( i = 0; i < 4; ++i )
    {
      if ( idLexer::ExpectTokenString(src, ",") )
        idStr::Append(parseBuffer, 256, ",");
      idLexer::ReadToken(src, &token);
      AppendToken(&token);
      if ( token.type == 3 )
      {
        if ( (token.subtype & 0x10000) == 0 )
          idToken::NumberValue(&token);
        v12 = token.floatvalue;
      }
      else
      {
        v12 = 0.0;
      }
      scale[i] = v12;
    }
    if ( pic )
      R_ImageScale(*pic, *width, *height, scale);
    if ( idLexer::ExpectTokenString(src, ")") )
    {
      idStr::Append(parseBuffer, 256, ")");
      v30 = -1;
      goto LABEL_117;
    }
    goto LABEL_73;
  }
  if ( !idStr::Icmp(token.data, "invertAlpha") )
  {
    MatchAndAppendToken(src, "(");
    gWriteProgramFlag = 1;
    R_ParseImageProgram_r(src, pic, width, height, timestamps, depth);
    if ( pic )
      R_InvertAlpha(*width, *pic, *height);
    goto LABEL_72;
  }
  if ( !idStr::Icmp(token.data, "invertColor") )
  {
    MatchAndAppendToken(src, "(");
    gWriteProgramFlag = 1;
    R_ParseImageProgram_r(src, pic, width, height, timestamps, depth);
    if ( pic )
      R_InvertColor(*width, *pic, *height);
    goto LABEL_72;
  }
  if ( !idStr::Icmp(token.data, "makeIntensity") )
  {
    MatchAndAppendToken(src, "(");
    gWriteProgramFlag = 1;
    R_ParseImageProgram_r(src, pic, width, height, timestamps, depth);
    if ( pic )
    {
      v13 = 4 * *height * *width;
      for ( j = 0; j < v13; v15[1] = v15[2] )
      {
        (*pic)[j + 3] = (*pic)[j];
        (*pic)[j + 2] = (*pic)[j + 3];
        v15 = &(*pic)[j];
        j += 4;
      }
    }
LABEL_78:
    MatchAndAppendToken(src, ")");
    v30 = -1;
    goto LABEL_117;
  }
  if ( !idStr::Icmp(token.data, "makeAlpha") )
  {
    MatchAndAppendToken(src, "(");
    gWriteProgramFlag = 1;
    R_ParseImageProgram_r(src, pic, width, height, timestamps, depth);
    if ( pic )
    {
      v16 = 4 * *height * *width;
      for ( k = 0; k < v16; k += 4 )
      {
        (*pic)[k + 3] = (char)((*pic)[k] + (*pic)[k + 1] + (*pic)[k + 2]) / 3;
        (*pic)[k + 2] = -1;
        (*pic)[k + 1] = -1;
        (*pic)[k] = -1;
      }
    }
    goto LABEL_78;
  }
  if ( !idStr::Icmp(token.data, "downsize") )
  {
    MatchAndAppendToken(src, "(");
    gWriteProgramFlag = 1;
    if ( !R_ParseImageProgram_r(src, pic, width, height, timestamps, depth) )
      goto LABEL_49;
    MatchAndAppendToken(src, ",");
    idLexer::ReadToken(src, &token);
    AppendToken(&token);
    if ( token.type == 3 )
    {
      if ( (token.subtype & 0x10000) == 0 )
        idToken::NumberValue(&token);
      intvalue = token.intvalue;
    }
    else
    {
      intvalue = 0;
    }
    if ( pic && !r_skipDownsize.internalVar->integerValue )
    {
      v19 = *height;
      pic2 = *(unsigned __int8 **)width;
      v20 = R_ResampleTexture(*pic, (int)pic2, v19, (int)pic2 >> intvalue, v19 >> intvalue);
      v23 = *pic;
      newPic = v20;
      R_StaticFree(v23);
      *pic = newPic;
      *width >>= intvalue;
      *height >>= intvalue;
    }
    MatchAndAppendToken(src, ")");
LABEL_95:
    v30 = -1;
    goto LABEL_117;
  }
  if ( !timestamps && !pic )
    goto LABEL_95;
  idStr::BackSlashesToSlashes(&token);
  len = token.len;
  if ( token.len + 1 > tr.lastLoadedImage.alloced )
    idStr::ReAllocate(&tr.lastLoadedImage, token.len + 1, 0);
  qmemcpy(tr.lastLoadedImage.data, token.data, len);
  tr.lastLoadedImage.data[len] = 0;
  tr.lastLoadedImage.len = len;
  if ( idStr::Cmpn(token.data, "textures/", 9)
    && idStr::Cmpn(token.data, "gfx/", 4)
    && idStr::Cmpn(token.data, "models/", 7)
    && idStr::Cmpn(token.data, "savegames/", 10)
    && idStr::Cmpn(token.data, "fonts/", 6) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Invalid folder for map '%s'",
      token.data);
  }
  R_LoadImage(token.data, pic, width, height, &timestamp, 1);
  v22 = timestamp;
  if ( timestamps && timestamp > *timestamps )
    *timestamps = timestamp;
  if ( v22 != -1 )
  {
    if ( ProgramImagesTimestamp != -1 && ProgramImagesTimestamp > *timestamps )
      gWriteProgramFlag = 0;
    v30 = -1;
    goto LABEL_117;
  }
  gWriteProgramFlag = 0;
  if ( g_psSpecialPassType )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Failed to read \"%s\" during '%s' parse!",
      token.data,
      g_psSpecialPassType);
  v30 = -1;
  idStr::FreeData(&token);
  return 0;
}

// FUNC: void __cdecl R_LoadImageProgram(char const *,unsigned char * *,int *,int *,unsigned int *,enum textureDepth_t *)
void __cdecl R_LoadImageProgram(
        char *name,
        unsigned __int8 **pic,
        int *width,
        int *height,
        unsigned int *timestamps,
        textureDepth_t *depth)
{
  idLexer src; // [esp+0h] [ebp-D4h] BYREF
  int v7; // [esp+D0h] [ebp-4h]

  idLexer::idLexer(&src);
  v7 = 0;
  idLexer::LoadMemory(&src, name, strlen(name), name, 1);
  src.flags = 156;
  parseBuffer[0] = 0;
  if ( timestamps )
    *timestamps = 0;
  R_ParseImageProgram_r(&src, pic, width, height, timestamps, depth);
  idLexer::FreeSource(&src);
  v7 = -1;
  idLexer::~idLexer(&src);
}

// FUNC: char const * __cdecl R_ParsePastImageProgram(class idLexer &)
char *__cdecl R_ParsePastImageProgram(idLexer *src)
{
  parseBuffer[0] = 0;
  R_ParseImageProgram_r(src, 0, 0, 0, 0, 0);
  return parseBuffer;
}
