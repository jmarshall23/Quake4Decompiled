
// FUNC: unsigned char * __cdecl R_ResampleTexture(unsigned char const *,int,int,int,int)
char *__cdecl R_ResampleTexture(const unsigned __int8 *in, int inwidth, int inheight, int outwidth, int outheight)
{
  int v5; // ebx
  int v6; // ebp
  char *v7; // edi
  unsigned int v8; // eax
  int v9; // ecx
  unsigned int i; // esi
  int v11; // ecx
  unsigned int j; // edx
  double v13; // st7
  const unsigned __int8 *v14; // edx
  double v15; // st6
  double v16; // st5
  const unsigned __int8 *v17; // esi
  int v18; // ecx
  const unsigned __int8 *v19; // edi
  _BYTE *v20; // ebp
  int v21; // eax
  int v22; // ecx
  int v23; // edx
  int v25; // [esp+10h] [ebp-8014h]
  int v26; // [esp+18h] [ebp-800Ch]
  char *v27; // [esp+1Ch] [ebp-8008h]
  void *v28; // [esp+20h] [ebp-8004h]
  int v29[8192]; // [esp+24h] [ebp-8000h]

  v5 = outwidth;
  if ( outwidth > 4096 )
  {
    v5 = 4096;
    outwidth = 4096;
  }
  if ( outheight > 4096 )
    outheight = 4096;
  v6 = inwidth;
  v7 = (char *)R_StaticAlloc(4 * outheight * v5);
  v8 = (inwidth << 16) / v5;
  v9 = 0;
  v28 = v7;
  v27 = v7;
  for ( i = v8 >> 2; v9 < v5; i += v8 )
    v29[v9++] = 4 * HIWORD(i);
  v11 = 0;
  for ( j = 3 * ((unsigned int)((inwidth << 16) / v5) >> 2); v11 < v5; j += v8 )
    v29[v11++ + 4096] = 4 * HIWORD(j);
  v26 = 0;
  if ( outheight <= 0 )
    return v7;
  v13 = (double)inheight;
  v14 = in;
  v15 = (double)outheight;
  do
  {
    v16 = (double)v26;
    v17 = &v14[4 * v6 * (int)((v16 + 0.25) * v13 / v15)];
    v18 = 0;
    v19 = &v14[4 * v6 * (int)((v16 + 0.75) * v13 / v15)];
    v25 = 0;
    if ( v5 > 0 )
    {
      v20 = v27 + 2;
      do
      {
        v21 = v29[v18];
        v22 = v29[v18 + 4096];
        *(v20 - 2) = (v17[v21] + v17[v22] + v19[v21] + v19[v22]) >> 2;
        *(v20 - 1) = (v17[v21 + 1] + v17[v22 + 1] + v19[v21 + 1] + v19[v22 + 1]) >> 2;
        *v20 = (v17[v21 + 2] + v17[v22 + 2] + v19[v21 + 2] + v19[v22 + 2]) >> 2;
        v5 = outwidth;
        v23 = (v17[v21 + 3] + v17[v22 + 3] + v19[v21 + 3] + v19[v22 + 3]) >> 2;
        v18 = v25 + 1;
        v20[1] = v23;
        v20 += 4;
        v25 = v18;
      }
      while ( v18 < outwidth );
      v6 = inwidth;
      v14 = in;
    }
    v27 += 4 * v5;
    ++v26;
  }
  while ( v26 < outheight );
  return (char *)v28;
}

// FUNC: unsigned char * __cdecl R_Dropsample(unsigned char const *,int,int,int,int)
unsigned __int8 *__cdecl R_Dropsample(
        const unsigned __int8 *in,
        int inwidth,
        int inheight,
        int outwidth,
        int outheight)
{
  int v5; // esi
  unsigned __int8 *v6; // ecx
  const unsigned __int8 *v7; // ebx
  int v8; // esi
  _BYTE *v9; // ecx
  int v10; // ebp
  int v11; // eax
  unsigned __int8 v12; // dl
  int i; // [esp+8h] [ebp-14h]
  unsigned __int8 *out_p; // [esp+Ch] [ebp-10h]
  unsigned __int8 *out; // [esp+18h] [ebp-4h]

  v5 = outheight;
  v6 = (unsigned __int8 *)R_StaticAlloc(4 * outheight * outwidth);
  out = v6;
  out_p = v6;
  for ( i = 0; i < v5; ++i )
  {
    v7 = &in[4 * inwidth * (__int64)(((double)i + 0.25) * (double)inheight / (double)outheight)];
    if ( outwidth > 0 )
    {
      v8 = 0;
      v9 = out_p + 2;
      v10 = outwidth;
      do
      {
        v11 = v8 / outwidth;
        v12 = v7[4 * (v8 / outwidth)];
        v8 += inwidth;
        *(v9 - 2) = v12;
        *(v9 - 1) = v7[4 * v11 + 1];
        *v9 = v7[4 * v11 + 2];
        v9 += 4;
        --v10;
        *(v9 - 3) = v7[4 * v11 + 3];
      }
      while ( v10 );
      v5 = outheight;
      v6 = out;
    }
    out_p += 4 * outwidth;
  }
  return v6;
}

// FUNC: void __cdecl R_SetBorderTexels(unsigned char *,int,int,unsigned char const * const)
void __cdecl R_SetBorderTexels(unsigned __int8 *inBase, int width, int height, unsigned __int8 *border)
{
  unsigned __int8 *v4; // ecx
  int v5; // ebp
  int v6; // esi
  unsigned __int8 *v7; // ecx
  int v8; // edi
  unsigned __int8 *v9; // ecx
  int v10; // esi
  unsigned __int8 *v11; // ecx

  v4 = inBase;
  v5 = width;
  if ( height > 0 )
  {
    v6 = height;
    do
    {
      *v4 = *border;
      v4[1] = border[1];
      v4[2] = border[2];
      v4[3] = border[3];
      v4 += 4 * width;
      --v6;
    }
    while ( v6 );
  }
  v7 = &inBase[4 * width - 4];
  if ( height > 0 )
  {
    v8 = height;
    do
    {
      *v7 = *border;
      v7[1] = border[1];
      v7[2] = border[2];
      v7[3] = border[3];
      v7 += 4 * width;
      --v8;
    }
    while ( v8 );
  }
  if ( width > 0 )
  {
    v9 = inBase + 2;
    v10 = width;
    do
    {
      *(v9 - 2) = *border;
      *(v9 - 1) = border[1];
      *v9 = border[2];
      v9[1] = border[3];
      v9 += 4;
      --v10;
    }
    while ( v10 );
  }
  v11 = &inBase[4 * width * (height - 1)];
  if ( width > 0 )
  {
    do
    {
      *v11 = *border;
      v11[1] = border[1];
      v11[2] = border[2];
      v11[3] = border[3];
      v11 += 4;
      --v5;
    }
    while ( v5 );
  }
}

// FUNC: unsigned char * __cdecl R_MipMap(unsigned char const *,int,int,bool)
unsigned __int8 *__cdecl R_MipMap(const unsigned __int8 *in, int width, int height, char preserveBorder)
{
  int v4; // ebx
  const unsigned __int8 *v5; // edi
  unsigned __int8 v6; // cl
  unsigned __int8 v7; // al
  int v8; // esi
  int v9; // ebp
  unsigned __int8 v10; // dl
  int v11; // ebx
  int v12; // ecx
  int v13; // eax
  unsigned __int8 *result; // eax
  int v15; // edx
  unsigned __int8 *v16; // ecx
  unsigned __int8 *v17; // eax
  int v18; // edx
  unsigned __int8 *v19; // eax
  unsigned __int8 *v20; // ecx
  unsigned __int8 *v21; // eax
  int v22; // esi
  int v23; // [esp+10h] [ebp-24h]
  int v24; // [esp+14h] [ebp-20h]
  int v25; // [esp+30h] [ebp-4h]
  unsigned __int8 *ina; // [esp+38h] [ebp+4h]

  v4 = height;
  if ( width < 1 || height < 1 || height + width == 2 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
      common.type,
      "R_MipMap called with size %i,%i",
      width,
      height);
  v5 = in;
  v6 = in[2];
  v7 = in[1];
  v8 = 4 * width;
  v9 = width >> 1;
  LOBYTE(height) = *in;
  v10 = in[3];
  BYTE2(height) = v6;
  v11 = v4 >> 1;
  v12 = width >> 1;
  BYTE1(height) = v7;
  HIBYTE(height) = v10;
  v25 = v11;
  v13 = v11;
  if ( !(width >> 1) )
    v12 = 1;
  if ( !v11 )
    v13 = 1;
  result = (unsigned __int8 *)R_StaticAlloc(4 * v12 * v13);
  v15 = width >> 1;
  ina = result;
  v16 = result;
  if ( v9 && v11 )
  {
    if ( v11 > 0 )
    {
      v24 = v11;
      do
      {
        if ( v15 > 0 )
        {
          v17 = (unsigned __int8 *)&v5[v8];
          v23 = v15;
          do
          {
            *v16 = (*v17 + *v5 + v17[4] + v17[4 - v8]) >> 2;
            v16[1] = (v17[1] + v17[5] + v17[5 - v8] + v17[1 - v8]) >> 2;
            v16[2] = (v17[2] + v17[6] + v17[6 - v8] + v17[2 - v8]) >> 2;
            v16[3] = (v17[3] + v17[7] + v17[7 - v8] + v17[3 - v8]) >> 2;
            v16 += 4;
            v5 += 8;
            v17 += 8;
            --v23;
          }
          while ( v23 );
          v15 = width >> 1;
          v11 = v25;
          result = ina;
        }
        v5 += v8;
        --v24;
      }
      while ( v24 );
    }
    if ( preserveBorder )
    {
      R_SetBorderTexels(result, v15, v11, (unsigned __int8 *)&height);
      return ina;
    }
  }
  else
  {
    v18 = v11 + v9;
    if ( preserveBorder )
    {
      if ( v18 > 0 )
      {
        v19 = result + 2;
        do
        {
          *(_DWORD *)(v19 - 2) = height;
          v19 += 4;
          --v18;
        }
        while ( v18 );
        return ina;
      }
    }
    else if ( v18 > 0 )
    {
      v20 = result + 2;
      v21 = (unsigned __int8 *)(v5 + 5);
      v22 = v11 + v9;
      do
      {
        *(v20 - 2) = (*(v21 - 1) + *(v21 - 5)) >> 1;
        *(v20 - 1) = (*v21 + *(v21 - 4)) >> 1;
        *v20 = (v21[1] + *(v21 - 3)) >> 1;
        v20[1] = (v21[2] + *(v21 - 2)) >> 1;
        v20 += 4;
        v21 += 8;
        --v22;
      }
      while ( v22 );
      return ina;
    }
  }
  return result;
}

// FUNC: void __cdecl R_BlendOverTexture(unsigned char *,int,unsigned char const * const)
void __cdecl R_BlendOverTexture(unsigned __int8 *data, int pixelCount, const unsigned __int8 *blend)
{
  int v3; // eax
  int v4; // ebp
  int v5; // esi
  int v6; // edx
  int v7; // edi
  int v8; // ecx

  v3 = blend[3];
  v4 = v3 * blend[2];
  v5 = v3 * *blend;
  v6 = pixelCount;
  v7 = v3 * blend[1];
  v8 = 255 - v3;
  if ( pixelCount > 0 )
  {
    do
    {
      *data = (v5 + v8 * *data) >> 9;
      data[1] = (v7 + v8 * data[1]) >> 9;
      data[2] = (v4 + v8 * data[2]) >> 9;
      data += 4;
      --v6;
    }
    while ( v6 );
  }
}

// FUNC: void __cdecl R_HorizontalFlip(unsigned char *,int,int)
void __cdecl R_HorizontalFlip(unsigned __int8 *data, int width, int height)
{
  int v4; // edx
  unsigned __int8 *v5; // ebx
  unsigned __int8 *v6; // edx
  unsigned __int8 *v7; // ecx
  int v8; // edi
  int v9; // esi
  int v10; // [esp+4h] [ebp-8h]
  unsigned __int8 *heighta; // [esp+18h] [ebp+Ch]

  if ( height > 0 )
  {
    v4 = 4 * width;
    v5 = data;
    heighta = &data[4 * width - 4];
    v10 = height;
    do
    {
      if ( width / 2 > 0 )
      {
        v6 = heighta;
        v7 = v5;
        v8 = width / 2;
        do
        {
          v9 = *(_DWORD *)v7;
          *(_DWORD *)v7 = *(_DWORD *)v6;
          *(_DWORD *)v6 = v9;
          v7 += 4;
          v6 -= 4;
          --v8;
        }
        while ( v8 );
        v4 = 4 * width;
      }
      heighta += v4;
      v5 += v4;
      --v10;
    }
    while ( v10 );
  }
}

// FUNC: void __cdecl R_VerticalFlip(unsigned char *,int,int)
void __cdecl R_VerticalFlip(unsigned __int8 *data, int width, int height)
{
  int v4; // esi
  unsigned __int8 *v5; // edx
  int v6; // eax
  unsigned __int8 *v7; // esi
  int v8; // ebx
  int i; // [esp+8h] [ebp-8h]
  unsigned __int8 *widtha; // [esp+18h] [ebp+8h]

  v4 = 0;
  i = 0;
  if ( width > 0 )
  {
    v5 = data;
    v6 = height / 2;
    widtha = data;
    do
    {
      if ( v6 > 0 )
      {
        v7 = &data[4 * v4 + 4 * width * (height - 1)];
        do
        {
          v8 = *(_DWORD *)v5;
          *(_DWORD *)v5 = *(_DWORD *)v7;
          *(_DWORD *)v7 = v8;
          v5 += 4 * width;
          v7 -= 4 * width;
          --v6;
        }
        while ( v6 );
        v4 = i;
        v6 = height / 2;
      }
      ++v4;
      v5 = widtha + 4;
      i = v4;
      widtha += 4;
    }
    while ( v4 < width );
  }
}

// FUNC: void __cdecl R_RotatePic(unsigned char *,int)
void __cdecl R_RotatePic(unsigned __int8 *data, int width)
{
  int v3; // esi
  int *v4; // eax
  int *v5; // ebp
  unsigned __int8 *v6; // ecx
  int v7; // edi
  int *v8; // edx
  int *v9; // eax
  int v10; // esi
  bool v11; // zf
  int v12; // [esp+Ch] [ebp-Ch]
  int *temp; // [esp+10h] [ebp-8h]
  int v14; // [esp+14h] [ebp-4h]
  unsigned __int8 *widtha; // [esp+20h] [ebp+8h]

  v3 = 4 * width * width;
  v14 = v3;
  v4 = (int *)R_StaticAlloc(v3);
  v5 = v4;
  temp = v4;
  if ( width > 0 )
  {
    v6 = data;
    v7 = 4 * width;
    widtha = data;
    v8 = v4;
    v12 = width;
    do
    {
      v9 = v8;
      v10 = width;
      do
      {
        *v9++ = *(_DWORD *)v6;
        v6 += v7;
        --v10;
      }
      while ( v10 );
      v6 = widtha + 4;
      v8 = (int *)((char *)v8 + v7);
      v11 = v12-- == 1;
      widtha += 4;
    }
    while ( !v11 );
    v5 = temp;
    v3 = v14;
  }
  SIMDProcessor->Memcpy(SIMDProcessor, data, v5, v3);
  R_StaticFree(v5);
}
