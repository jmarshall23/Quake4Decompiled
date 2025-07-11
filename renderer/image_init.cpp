
// FUNC: void __cdecl R_writeRDF_f(class idCmdArgs const &)
void __cdecl R_writeRDF_f()
{
  globalImages->GenerateRDF(globalImages, 0);
}

// FUNC: R_RampImage
void __cdecl R_RampImage(idImage *image)
{
  int i; // eax
  unsigned __int8 data[256][4]; // [esp+0h] [ebp-400h] BYREF

  for ( i = 0; i < 256; ++i )
  {
    data[i][3] = i;
    data[i][2] = i;
    data[i][1] = i;
    data[i][0] = i;
  }
  idImage::GenerateImage(image, data[0], 256, 1, TF_NEAREST, 0, TR_CLAMP, TD_HIGH_QUALITY, 0);
}

// FUNC: R_SpecularTableImage
void __cdecl R_SpecularTableImage(idImage *image)
{
  int v1; // ecx
  double v2; // st7
  unsigned __int8 v3; // al
  int x; // [esp+0h] [ebp-408h]
  int b; // [esp+4h] [ebp-404h]
  unsigned __int8 data[256][4]; // [esp+8h] [ebp-400h] BYREF

  v1 = 0;
  x = 0;
  do
  {
    v2 = ((double)x * 0.0039215689 - 0.75) * 4.0;
    if ( v2 < 0.0 )
      v2 = 0.0;
    ++v1;
    b = (int)(v2 * v2 * 255.0);
    v3 = b;
    *((_BYTE *)&b + 4 * v1 + 3) = b;
    *((_BYTE *)&b + 4 * v1 + 2) = v3;
    *((_BYTE *)&b + 4 * v1 + 1) = v3;
    data[v1 - 1][0] = v3;
    x = v1;
  }
  while ( v1 < 256 );
  idImage::GenerateImage(image, data[0], 256, 1, TF_LINEAR, 0, TR_CLAMP, TD_HIGH_QUALITY, 0);
}

// FUNC: public: void __thiscall idImage::MakeDefault(void)
void __thiscall idImage::MakeDefault(idImage *this)
{
  unsigned __int8 *v2; // eax
  int v3; // esi
  int v4; // ecx
  int v5; // eax
  unsigned __int8 *v6; // ecx
  unsigned __int8 data[16][16][4]; // [esp+Ch] [ebp-400h] BYREF

  v2 = &data[0][0][1];
  v3 = 16;
  do
  {
    v4 = 16;
    do
    {
      *(v2 - 1) = 32;
      *v2 = 32;
      v2[1] = 32;
      v2[2] = -1;
      v2 += 4;
      --v4;
    }
    while ( v4 );
    --v3;
  }
  while ( v3 );
  v5 = 0;
  v6 = &data[0][0][2];
  do
  {
    data[0][v5][3] = -1;
    data[0][v5][2] = -1;
    data[0][v5][1] = -1;
    data[0][v5][0] = -1;
    data[15][v5][3] = -1;
    data[15][v5][2] = -1;
    data[15][v5][1] = -1;
    data[15][v5][0] = -1;
    v6[1] = -1;
    *v6 = -1;
    *(v6 - 1) = -1;
    *(v6 - 2) = -1;
    v6[61] = -1;
    v6[60] = -1;
    v6[59] = -1;
    v6[58] = -1;
    ++v5;
    v6 += 64;
  }
  while ( v5 < 16 );
  idImage::GenerateImage(this, data[0][0], 16, 16, TF_DEFAULT, 1, TR_REPEAT, TD_DEFAULT, 0);
  this->defaulted = 1;
}

// FUNC: R_DefaultImage
void __cdecl R_DefaultImage(idImage *image)
{
  idImage::MakeDefault(image);
}

// FUNC: R_WhiteImage
void __cdecl R_WhiteImage(idImage *image)
{
  unsigned __int8 data[16][16][4]; // [esp+8h] [ebp-400h] BYREF

  memset(data, 0xFFu, sizeof(data));
  idImage::GenerateImage(image, data[0][0], 16, 16, TF_DEFAULT, 0, TR_REPEAT, TD_DEFAULT, 0);
}

// FUNC: R_BlackImage
void __cdecl R_BlackImage(idImage *image)
{
  unsigned __int8 data[16][16][4]; // [esp+8h] [ebp-400h] BYREF

  memset(data, 0, sizeof(data));
  idImage::GenerateImage(image, data[0][0], 16, 16, TF_DEFAULT, 0, TR_REPEAT, TD_DEFAULT, 0);
}

// FUNC: R_BorderClampImage
void __cdecl R_BorderClampImage(idImage *image)
{
  int v1; // eax
  unsigned __int8 *v2; // ecx
  float v3[4]; // [esp+8h] [ebp-1010h] BYREF
  unsigned __int8 pic[4096]; // [esp+18h] [ebp-1000h] BYREF

  memset(pic, 0xFFu, sizeof(pic));
  v1 = 0;
  v2 = &pic[126];
  do
  {
    pic[4 * v1 + 3] = 0;
    pic[4 * v1 + 2] = 0;
    pic[4 * v1 + 1] = 0;
    pic[4 * v1] = 0;
    pic[4 * v1 + 3971] = 0;
    pic[4 * v1 + 3970] = 0;
    pic[4 * v1 + 3969] = 0;
    pic[4 * v1 + 3968] = 0;
    v2[1] = 0;
    *v2 = 0;
    *(v2 - 1) = 0;
    *(v2 - 2) = 0;
    *(v2 - 123) = 0;
    *(v2 - 124) = 0;
    *(v2 - 125) = 0;
    *(v2 - 126) = 0;
    ++v1;
    v2 += 128;
  }
  while ( v1 < 32 );
  idImage::GenerateImage(image, pic, 32, 32, TF_LINEAR, 0, TR_CLAMP_TO_BORDER, TD_DEFAULT, 0);
  if ( glConfig.isInitialized )
  {
    memset(v3, 0, sizeof(v3));
    qglTexParameterfv(0xDE1u, 0x1004u, v3);
  }
}

// FUNC: R_RGBA8Image
void __cdecl R_RGBA8Image(idImage *image)
{
  unsigned __int8 data[16][16][4]; // [esp+8h] [ebp-400h] BYREF

  memset(data, 0, sizeof(data));
  idImage::GenerateImage(image, data[0][0], 16, 16, TF_DEFAULT, 0, TR_REPEAT, TD_HIGH_QUALITY, 0);
}

// FUNC: R_RGBA8ImageClamped
void __cdecl R_RGBA8ImageClamped(idImage *image)
{
  unsigned __int8 data[16][16][4]; // [esp+8h] [ebp-400h] BYREF

  memset(data, 0, sizeof(data));
  idImage::GenerateImage(image, data[0][0], 16, 16, TF_DEFAULT, 0, TR_CLAMP, TD_HIGH_QUALITY, 0);
}

// FUNC: R_QuickLoadImage
void __cdecl R_QuickLoadImage(idImage *image)
{
  unsigned __int8 *v1; // eax
  int v2; // esi
  int v3; // ecx
  unsigned __int8 data[16][16][4]; // [esp+8h] [ebp-400h] BYREF

  v1 = &data[0][0][1];
  v2 = 16;
  do
  {
    v3 = 16;
    do
    {
      v1[1] = -56;
      *v1 = -56;
      *(v1 - 1) = -56;
      v1[2] = -1;
      v1 += 4;
      --v3;
    }
    while ( v3 );
    --v2;
  }
  while ( v2 );
  idImage::GenerateImage(image, data[0][0], 16, 16, TF_DEFAULT, 1, TR_REPEAT, TD_DEFAULT, 0);
}

// FUNC: R_AlphaNotchImage
void __cdecl R_AlphaNotchImage(idImage *image)
{
  unsigned __int8 data[2][4]; // [esp+0h] [ebp-8h] BYREF

  *(_WORD *)&data[0][1] = -1;
  data[0][0] = -1;
  *(_WORD *)&data[1][1] = -1;
  data[1][0] = -1;
  data[1][3] = -1;
  data[0][3] = 0;
  idImage::GenerateImage(image, data[0], 2, 1, TF_NEAREST, 0, TR_CLAMP, TD_HIGH_QUALITY, 0);
}

// FUNC: getCubeVector
void __usercall getCubeVector(int i@<ecx>, float *vector@<eax>, int cubesize, int x, int y)
{
  double v5; // st7
  long double v6; // st4
  float cubesizeb; // [esp+4h] [ebp+4h]
  float cubesizea; // [esp+4h] [ebp+4h]

  cubesizeb = (float)cubesize;
  v5 = ((double)x + 0.5) / cubesizeb + ((double)x + 0.5) / cubesizeb - 1.0;
  cubesizea = ((double)y + 0.5) / cubesizeb + ((double)y + 0.5) / cubesizeb - 1.0;
  switch ( i )
  {
    case 0:
      *vector = 1.0;
      vector[1] = -cubesizea;
      vector[2] = -v5;
      break;
    case 1:
      *vector = -1.0;
      vector[1] = -cubesizea;
      vector[2] = v5;
      break;
    case 2:
      *vector = v5;
      vector[1] = 1.0;
      vector[2] = cubesizea;
      break;
    case 3:
      *vector = v5;
      vector[1] = -1.0;
      vector[2] = -cubesizea;
      break;
    case 4:
      *vector = v5;
      vector[2] = 1.0;
      vector[1] = -cubesizea;
      break;
    case 5:
      vector[2] = -1.0;
      *vector = -v5;
      vector[1] = -cubesizea;
      break;
    default:
      break;
  }
  v6 = sqrt(*vector * *vector + vector[1] * vector[1] + vector[2] * vector[2]);
  *vector = 1.0 / v6 * *vector;
  vector[1] = 1.0 / v6 * vector[1];
  vector[2] = 1.0 / v6 * vector[2];
}

// FUNC: makeNormalizeVectorCubeMap
void __cdecl makeNormalizeVectorCubeMap(idImage *image)
{
  unsigned __int8 **v1; // edi
  int k; // ebx
  int v3; // ebp
  int v4; // esi
  double v5; // st7
  unsigned __int64 v6; // rax
  double v7; // st7
  int i; // [esp+10h] [ebp-2Ch]
  int j; // [esp+14h] [ebp-28h]
  float vector[3]; // [esp+18h] [ebp-24h] BYREF
  unsigned __int8 *pixels[6]; // [esp+24h] [ebp-18h] BYREF

  pixels[0] = (unsigned __int8 *)Mem_Alloc(24576, 0xCu);
  i = 0;
  v1 = pixels;
  for ( j = 0; j < 24576; j += 4096 )
  {
    *v1 = &pixels[0][j];
    for ( k = 0; k < 32; ++k )
    {
      v3 = 0;
      v4 = k << 7;
      do
      {
        getCubeVector(i, vector, 32, v3, k);
        v5 = vector[1] * 127.0;
        (*v1)[v4] = (unsigned __int64)(vector[0] * 127.0 + 128.0);
        v6 = (unsigned __int64)(v5 + 128.0);
        v7 = vector[2] * 127.0;
        (*v1)[v4 + 1] = v6;
        (*v1)[v4 + 2] = (unsigned __int64)(v7 + 128.0);
        (*v1)[v4 + 3] = -1;
        ++v3;
        v4 += 4;
      }
      while ( v3 < 32 );
    }
    ++i;
    ++v1;
  }
  idImage::GenerateCubeImage(image, (const unsigned __int8 **)pixels, 32, TF_LINEAR, 0, TD_HIGH_QUALITY);
  Mem_Free(pixels[0]);
}

// FUNC: void __cdecl makeEmptyCubeMap(class idImage *)
void __cdecl makeEmptyCubeMap(idImage *image)
{
  int v1; // ebx
  int v2; // esi
  int v3; // eax
  unsigned __int8 **v4; // edi
  int v5; // esi
  int j; // ebp
  double v7; // st7
  unsigned __int64 v8; // rax
  double v9; // st7
  bool v10; // cc
  int y; // [esp+10h] [ebp-38h]
  int v12; // [esp+14h] [ebp-34h]
  int i; // [esp+18h] [ebp-30h]
  int v14; // [esp+1Ch] [ebp-2Ch]
  int v15; // [esp+20h] [ebp-28h]
  float vector[3]; // [esp+24h] [ebp-24h] BYREF
  unsigned __int8 *pixels[6]; // [esp+30h] [ebp-18h] BYREF

  v1 = emptyCubeSize;
  v2 = emptyCubeSize * emptyCubeSize;
  pixels[0] = (unsigned __int8 *)Mem_Alloc(24 * emptyCubeSize * emptyCubeSize, 0xCu);
  v3 = 0;
  i = 0;
  v4 = pixels;
  v14 = 0;
  v15 = 4 * v2;
  do
  {
    *v4 = &pixels[0][v3];
    y = 0;
    if ( v1 > 0 )
    {
      v12 = 0;
      do
      {
        v5 = v12;
        for ( j = 0; j < v1; ++j )
        {
          getCubeVector(i, vector, v1, j, y);
          v7 = vector[1] * 127.0;
          (*v4)[v5] = (unsigned __int64)(vector[0] * 127.0 + 128.0);
          v8 = (unsigned __int64)(v7 + 128.0);
          v9 = vector[2] * 127.0;
          (*v4)[v5 + 1] = v8;
          (*v4)[v5 + 2] = (unsigned __int64)(v9 + 128.0);
          (*v4)[v5 + 3] = -1;
          v5 += 4;
        }
        v12 += 4 * v1;
        ++y;
      }
      while ( y < v1 );
    }
    v3 = v15 + v14;
    ++v4;
    v10 = ++i < 6;
    v14 += v15;
  }
  while ( v10 );
  idImage::GenerateCubeImage(image, (const unsigned __int8 **)pixels, v1, TF_LINEAR, 0, 4);
  Mem_Free(pixels[0]);
}

// FUNC: R_CreateNoFalloffImage
void __cdecl R_CreateNoFalloffImage(idImage *image)
{
  unsigned __int8 *v1; // esi
  int v2; // edi
  unsigned __int8 *v3; // eax
  int v4; // ecx
  unsigned __int8 pic[4096]; // [esp+8h] [ebp-1000h] BYREF

  memset(pic, 0, sizeof(pic));
  v1 = &pic[261];
  v2 = 62;
  do
  {
    v3 = v1;
    v4 = 14;
    do
    {
      *(v3 - 1) = -1;
      *v3 = -1;
      v3[1] = -1;
      v3[2] = -1;
      v3 += 256;
      --v4;
    }
    while ( v4 );
    v1 += 4;
    --v2;
  }
  while ( v2 );
  idImage::GenerateImage(image, pic, 64, 16, TF_DEFAULT, 0, TR_CLAMP_TO_ZERO, TD_HIGH_QUALITY, 0);
}

// FUNC: void __cdecl R_FogImage(class idImage *)
void __cdecl R_FogImage(idImage *image)
{
  double v1; // st7
  int i; // eax
  int v3; // ebx
  char *v4; // esi
  int j; // edi
  int v6; // eax
  unsigned __int64 v7; // rax
  char *v8; // [esp+0h] [ebp-10408h]
  float v9[256]; // [esp+8h] [ebp-10400h]
  unsigned __int8 pic; // [esp+408h] [ebp-10000h] BYREF
  char v11; // [esp+409h] [ebp-FFFFh] BYREF

  v1 = 1.0;
  for ( i = 0; i < 256; ++i )
  {
    v9[i] = v1;
    v1 = v1 * 0.98199999;
  }
  v3 = 0;
  v8 = &v11;
  do
  {
    v4 = v8;
    for ( j = 0; j < 128; ++j )
    {
      v6 = (unsigned __int8)(unsigned __int64)(sqrt((double)((v3 - 64) * (v3 - 64) + (j - 64) * (j - 64)))
                                             * 0.015873017
                                             * 255.0);
      if ( !(_BYTE)v6 )
        v6 = 0;
      v7 = (unsigned __int64)((1.0 - v9[v6]) * 255.0);
      if ( !v3 || v3 == 127 || !j || j == 127 )
        LOBYTE(v7) = -1;
      v4[1] = -1;
      *v4 = -1;
      *(v4 - 1) = -1;
      v4[2] = v7;
      v4 += 512;
    }
    v8 += 4;
    ++v3;
  }
  while ( v3 < 128 );
  idImage::GenerateImage(image, &pic, 128, 128, TF_LINEAR, 0, TR_CLAMP, TD_HIGH_QUALITY, 0);
}

// FUNC: void __cdecl R_FogEnterImage(class idImage *)
void __cdecl R_FogEnterImage(idImage *image)
{
  int v1; // ebp
  char *v2; // esi
  int i; // edi
  unsigned __int64 v4; // rax
  float targetHeight; // [esp+0h] [ebp-4020h]
  char *v6; // [esp+18h] [ebp-4008h]
  float viewHeight; // [esp+1Ch] [ebp-4004h]
  unsigned __int8 pic; // [esp+20h] [ebp-4000h] BYREF
  char v9; // [esp+21h] [ebp-3FFFh] BYREF

  v1 = 0;
  v6 = &v9;
  do
  {
    v2 = v6;
    for ( i = 0; i < 64; ++i )
    {
      targetHeight = (float)(i - 32);
      viewHeight = (float)(v1 - 32);
      v4 = (unsigned __int64)(FogFraction(viewHeight, targetHeight) * 255.0);
      if ( !(_BYTE)v4 )
        LOBYTE(v4) = 0;
      v2[1] = -1;
      *v2 = -1;
      *(v2 - 1) = -1;
      v2[2] = v4;
      v2 += 256;
    }
    v6 += 4;
    ++v1;
  }
  while ( v1 < 64 );
  idImage::GenerateImage(image, &pic, 64, 64, TF_LINEAR, 0, TR_CLAMP, TD_HIGH_QUALITY, 0);
}

// FUNC: void __cdecl R_QuadraticImage(class idImage *)
void __cdecl R_QuadraticImage(idImage *image)
{
  unsigned __int8 *v1; // ebx
  unsigned __int8 *v2; // esi
  int v3; // edi
  unsigned __int64 v4; // rax
  int x; // [esp+10h] [ebp-20Ch]
  float v6; // [esp+14h] [ebp-208h]
  unsigned __int8 data[4][32][4]; // [esp+1Ch] [ebp-200h] BYREF

  x = 0;
  v1 = &data[0][0][1];
  do
  {
    v2 = v1;
    v3 = 4;
    do
    {
      v6 = (double)x - 15.5;
      v4 = (unsigned __int64)((1.0 - (COERCE_FLOAT(LODWORD(v6) & 0x7FFFFFFF) - 0.5) * 0.0625)
                            * (1.0 - (COERCE_FLOAT(LODWORD(v6) & 0x7FFFFFFF) - 0.5) * 0.0625)
                            * 255.0);
      if ( !(_BYTE)v4 )
        LOBYTE(v4) = 0;
      v2[1] = v4;
      *v2 = v4;
      *(v2 - 1) = v4;
      v2[2] = -1;
      v2 += 128;
      --v3;
    }
    while ( v3 );
    v1 += 4;
    ++x;
  }
  while ( x < 32 );
  idImage::GenerateImage(image, data[0][0], 32, 4, TF_DEFAULT, 0, TR_CLAMP, TD_HIGH_QUALITY, 0);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::SetNormalPalette(void)
void __thiscall idImageManagerLocal::SetNormalPalette(idImageManagerLocal *this)
{
  int v2; // esi
  int *v3; // edi
  unsigned __int64 v4; // rax
  int v5; // esi
  int v6; // edi
  int i; // ecx
  int v8; // eax
  unsigned __int8 *v9; // ebx
  int v10; // ebp
  _BYTE *v11; // esi
  int v12; // edi
  double v13; // st7
  double v14; // st7
  long double v15; // st7
  unsigned __int8 *temptable; // [esp+20h] [ebp-50h]
  float temptablea; // [esp+20h] [ebp-50h]
  float v; // [esp+24h] [ebp-4Ch]
  float v_4; // [esp+28h] [ebp-48h]
  float v_8; // [esp+2Ch] [ebp-44h]
  int compressedToOriginal[16]; // [esp+30h] [ebp-40h] BYREF

  temptable = this->compressedPalette;
  v2 = 0;
  v3 = &compressedToOriginal[7];
  do
  {
    v4 = (unsigned __int64)((1.0
                           - sqrt(1.0 - (double)(v2 + 1) * 0.1176470588235294 * ((double)(v2 + 1) * 0.1176470588235294)))
                          * 127.0
                          + 0.5);
    compressedToOriginal[v2 + 8] = v4 + 128;
    *v3 = 127 - v4;
    ++v2;
    --v3;
  }
  while ( v2 < 8 );
  v5 = compressedToOriginal[15];
  v6 = compressedToOriginal[0];
  for ( i = 0; i < 256; ++i )
  {
    if ( i > v6 )
    {
      if ( i < v5 )
      {
        v8 = 0;
        while ( i > compressedToOriginal[v8 + 1] )
        {
          if ( i <= compressedToOriginal[v8 + 2] )
          {
            ++v8;
            break;
          }
          v8 += 2;
          if ( v8 >= 14 )
            break;
        }
        if ( i - compressedToOriginal[v8] >= compressedToOriginal[v8 + 1] - i )
          LOBYTE(v8) = v8 + 1;
        this->originalToCompressed[i] = v8;
      }
      else
      {
        this->originalToCompressed[i] = 15;
      }
    }
    else
    {
      this->originalToCompressed[i] = 0;
    }
  }
  v9 = temptable;
  v10 = 0;
  v11 = temptable + 2;
  do
  {
    v12 = 0;
    v13 = ((double)compressedToOriginal[v10] - 127.5) * 0.0078125;
    v = v13;
    temptablea = v13 * v;
    do
    {
      v14 = ((double)compressedToOriginal[v12] - 127.5) * 0.0078125;
      v_4 = v14;
      v15 = 1.0 - (v14 * v_4 + temptablea);
      if ( v15 < 0.0 )
        v15 = 0.0;
      v_8 = sqrt(v15);
      *(v11 - 2) = (unsigned __int64)(floor(v * 127.0 + 0.5) + 128.0);
      *(v11 - 1) = (unsigned __int64)(floor(v_4 * 127.0) + 128.0);
      *v11 = (unsigned __int64)(floor(v_8 * 127.0) + 128.0);
      ++v12;
      v11 += 3;
    }
    while ( v12 < 16 );
    ++v10;
  }
  while ( v10 < 16 );
  v9[767] = 0x80;
  v9[766] = 0x80;
  v9[765] = 0x80;
  if ( glConfig.sharedTexturePaletteAvailable )
  {
    qglColorTableEXT(33275, 6407, 256, 6407, 5121, v9);
    qglEnable(0x81FBu);
  }
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::BindNull(void)
void __thiscall idImageManagerLocal::BindNull(idImageManagerLocal *this)
{
  textureType_t textureType; // eax
  tmu_t *v2; // esi

  textureType = backEnd.glState.tmu[backEnd.glState.currenttmu].textureType;
  v2 = &backEnd.glState.tmu[backEnd.glState.currenttmu];
  if ( textureType == TT_CUBIC )
  {
    qglDisable(0x8513u);
    v2->textureType = TT_DISABLED;
  }
  else if ( textureType == TT_3D )
  {
    qglDisable(0x806Fu);
    v2->textureType = TT_DISABLED;
  }
  else
  {
    if ( textureType == TT_2D )
      qglDisable(0xDE1u);
    v2->textureType = TT_DISABLED;
  }
}

// FUNC: void __cdecl R_writeProgramImages_f(class idCmdArgs const &)
void __usercall R_writeProgramImages_f(int a1@<esi>, const idCmdArgs *args)
{
  int v2; // esi
  const char *v3; // eax
  const char *v4; // eax
  const char *v5; // esi
  char *v6; // edi
  _BYTE *alloced; // ecx
  char v8; // al
  idFile *v9; // esi
  const char *v10; // eax
  idStr strReport; // [esp+90h] [ebp-2Ch] BYREF
  int v13; // [esp+B8h] [ebp-4h]
  void *retaddr; // [esp+BCh] [ebp+0h]

  v2 = Sys_Milliseconds();
  (*(void (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 100))(
    common.type,
    "running R_writeProgramImages",
    a1);
  fileSystem->ReadFile(fileSystem, "ProgramImagesLog.txt", 0, &ProgramImagesTimestamp);
  cvarSystem->SetCVarBool(cvarSystem, "image_writeProgramImages", 1, 0);
  cvarSystem->SetCVarBool(cvarSystem, "image_preload", 1, 0);
  cvarSystem->SetCVarBool(cvarSystem, "image_writeTGA", 0, 0);
  cvarSystem->SetCVarBool(cvarSystem, "image_writeNormalTGA", 0, 0);
  cvarSystem->SetCVarInteger(cvarSystem, "image_usePrecompressedTextures", 2, 0);
  declManager->RegisterDeclFolderWrapper(declManager, "materials", ".mtr", DECL_MATERIAL, 0, 0);
  *(float *)&strReport.len = (double)(Sys_Milliseconds() - v2) * 0.001;
  v3 = Timer_ReportShort(*(float *)&strReport.len);
  v4 = va("\nTime elapsed: %s\n", v3);
  v5 = v4;
  strReport.data = 0;
  *(_DWORD *)strReport.baseBuffer = 20;
  strReport.alloced = (int)&strReport.baseBuffer[4];
  strReport.baseBuffer[4] = 0;
  if ( v4 )
  {
    v6 = (char *)strlen(v4);
    if ( (int)(v6 + 1) > 20 )
      idStr::ReAllocate((idStr *)&strReport.data, (int)(v6 + 1), 1);
    alloced = (_BYTE *)strReport.alloced;
    do
    {
      v8 = *v5;
      *alloced++ = *v5++;
    }
    while ( v8 );
    strReport.data = v6;
  }
  retaddr = 0;
  v9 = (idFile *)((int (__thiscall *)(idFileSystem *, const char *, const char *))fileSystem->OpenFileWrite)(
                   fileSystem,
                   "ProgramImagesLog.txt",
                   "fs_savepath");
  v9->Printf(v9, strReport.data);
  fileSystem->CloseFile(fileSystem, v9);
  cvarSystem->SetCVarBool(cvarSystem, "image_writeProgramImages", 0, 0);
  cvarSystem->SetCVarInteger(cvarSystem, "image_usePrecompressedTextures", 1, 0);
  if ( args->argc <= 1 )
    v10 = &entityFilter;
  else
    v10 = args->argv[1];
  if ( !idStr::Icmp(v10, "quit") )
  {
    (*(void (__thiscall **)(netadrtype_t, _DWORD))(*(_DWORD *)common.type + 148))(common.type, 0);
    (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 12))(common.type);
  }
  (*(void (__thiscall **)(netadrtype_t, _DWORD))(*(_DWORD *)common.type + 100))(common.type, 0);
  v13 = -1;
  idStr::FreeData(&strReport);
}

// FUNC: R_Specular2DTableImage
void __cdecl R_Specular2DTableImage(idImage *image)
{
  int v1; // edi
  unsigned __int8 *v2; // esi
  int v3; // edx
  unsigned __int8 *v4; // ecx
  unsigned int v5; // eax
  double v6; // st7
  double i; // st6
  int v8; // eax
  int v9; // [esp+8h] [ebp-40010h]
  float v10; // [esp+14h] [ebp-40004h]
  unsigned __int8 pic[262144]; // [esp+18h] [ebp-40000h] BYREF

  memset(pic, 0, sizeof(pic));
  v1 = 0;
  v9 = 0;
  v2 = &pic[2];
  do
  {
    v3 = 0;
    v4 = v2;
    do
    {
      v5 = v3;
      if ( v3 < 0 )
        v5 = -v3;
      v6 = 1.0;
      v10 = (double)v9 * 0.0039215689;
      for ( i = v10; ; i = i * i )
      {
        if ( (v5 & 1) != 0 )
          v6 = v6 * i;
        v5 >>= 1;
        if ( !v5 )
          break;
      }
      if ( v3 < 0 )
        v6 = 1.0 / v6;
      v8 = (int)(255.0 * v6);
      if ( !v8 )
        break;
      v4[1] = v8;
      *v4 = v8;
      *(v4 - 1) = v8;
      *(v4 - 2) = v8;
      ++v3;
      v4 += 1024;
    }
    while ( v3 < 256 );
    ++v1;
    v2 += 4;
    v9 = v1;
  }
  while ( v1 < 256 );
  idImage::GenerateImage(image, pic, 256, 256, TF_LINEAR, 0, TR_CLAMP, TD_HIGH_QUALITY, 0);
}

// FUNC: R_FlatNormalImage
void __cdecl R_FlatNormalImage(idImage *image)
{
  int v1; // eax
  int v2; // edx
  int v3; // esi
  unsigned __int8 *v4; // ecx
  int v5; // edi
  int v6; // eax
  unsigned __int8 data[16][16][4]; // [esp+8h] [ebp-400h] BYREF

  v1 = -((image_useNormalCompression.internalVar->integerValue != 1 ? 3 : 0) != 0);
  LOBYTE(v1) = v1 & 0xFD;
  v1 += 3;
  v2 = (image_useNormalCompression.internalVar->integerValue != 1 ? 3 : 0) - v1;
  v3 = 1 - v1;
  v4 = &data[0][0][v1];
  v5 = 2 - v1;
  v6 = 4;
  do
  {
    v4[v2] = 0x80;
    v4[v3] = 0x80;
    v4[v5] = -1;
    *v4 = -1;
    v4 += 4;
    --v6;
  }
  while ( v6 );
  idImage::GenerateImage(image, data[0][0], 2, 2, TF_DEFAULT, 1, TR_REPEAT, TD_HIGH_QUALITY, 0);
}

// FUNC: R_AmbientNormalImage
void __cdecl R_AmbientNormalImage(idImage *image)
{
  int v1; // esi
  unsigned __int8 v2; // bl
  int v3; // edi
  int v4; // edx
  unsigned __int8 *v5; // ecx
  int v6; // ebp
  int v7; // esi
  unsigned __int8 v8; // [esp+12h] [ebp-41Ah]
  unsigned __int8 v9; // [esp+13h] [ebp-419h]
  const unsigned __int8 *pics[6]; // [esp+14h] [ebp-418h] BYREF
  unsigned __int8 data[16][16][4]; // [esp+2Ch] [ebp-400h] BYREF

  v1 = (image_useNormalCompression.internalVar->integerValue != 1 ? 3 : 0) != 0 ? 0 : 3;
  v2 = (unsigned __int64)(tr.ambientLightVector.x * 255.0);
  v9 = (unsigned __int64)(tr.ambientLightVector.y * 255.0);
  v3 = (image_useNormalCompression.internalVar->integerValue != 1 ? 3 : 0) - v1;
  v4 = 1 - v1;
  v5 = &data[0][0][v1];
  v6 = 2 - v1;
  v8 = (unsigned __int64)(tr.ambientLightVector.z * 255.0);
  v7 = 4;
  do
  {
    v5[v3] = v2;
    v5[v4] = v9;
    v5[v6] = v8;
    *v5 = -1;
    v5 += 4;
    --v7;
  }
  while ( v7 );
  pics[0] = data[0][0];
  pics[3] = data[0][0];
  pics[1] = data[0][0];
  pics[2] = data[0][0];
  pics[4] = data[0][0];
  pics[5] = data[0][0];
  idImage::GenerateCubeImage(image, pics, 2, TF_DEFAULT, 1, TD_HIGH_QUALITY);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::ChangeTextureFilter(void)
void __thiscall idImageManagerLocal::ChangeTextureFilter(idImageManagerLocal *this)
{
  const char *value; // ebx
  int v3; // edi
  filterName_t *v4; // esi
  double floatValue; // st7
  unsigned __int8 v7; // c0
  unsigned __int8 v8; // c2
  int v9; // ebx
  bool v10; // cc
  idImage *v11; // edi
  unsigned int v12; // esi
  float v13; // [esp+0h] [ebp-18h]
  float v14; // [esp+0h] [ebp-18h]
  float v15; // [esp+0h] [ebp-18h]
  float v16; // [esp+0h] [ebp-18h]

  image_filter.internalVar->flags &= ~0x40000u;
  image_anisotropy.internalVar->flags &= ~0x40000u;
  image_lodbias.internalVar->flags &= ~0x40000u;
  value = image_filter.internalVar->value;
  v3 = 0;
  v4 = textureFilters;
  do
  {
    if ( !idStr::Icmp(v4->name, value) )
      break;
    ++v4;
    ++v3;
  }
  while ( (int)v4 < (int)&firstTime );
  if ( v3 == 6 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "bad r_textureFilter: '%s'",
      value);
    v3 = 0;
  }
  this->textureMinFilter = dword_102F99E4[3 * v3];
  this->textureMaxFilter = dword_102F99E8[3 * v3];
  floatValue = image_anisotropy.internalVar->floatValue;
  this->textureAnisotropy = image_anisotropy.internalVar->floatValue;
  if ( v7 | v8 )
  {
    this->textureAnisotropy = 1.0;
  }
  else if ( floatValue > glConfig.maxTextureAnisotropy )
  {
    this->textureAnisotropy = glConfig.maxTextureAnisotropy;
  }
  v9 = 0;
  v10 = this->images.num <= 0;
  this->textureLODBias = image_lodbias.internalVar->floatValue;
  if ( !v10 )
  {
    do
    {
      v11 = this->images.list[v9];
      v12 = 3553;
      switch ( v11->type )
      {
        case TT_2D:
          v12 = 3553;
          break;
        case TT_3D:
          v12 = 32879;
          break;
        case TT_CUBIC:
          v12 = 34067;
          break;
      }
      if ( v11->texnum != -1 )
      {
        v11->Bind(this->images.list[v9]);
        if ( v11->filter == TF_DEFAULT )
        {
          v13 = (float)globalImages->GetTextureMinFilter(globalImages);
          qglTexParameterf(v12, 0x2801u, v13);
          v14 = (float)globalImages->GetTextureMaxFilter(globalImages);
          qglTexParameterf(v12, 0x2800u, v14);
        }
        if ( glConfig.anisotropicAvailable )
        {
          v15 = globalImages->GetTextureAnisotropy(globalImages);
          qglTexParameterf(v12, 0x84FEu, v15);
        }
        if ( glConfig.textureLODBiasAvailable )
        {
          v16 = globalImages->GetTextureLODBias(globalImages);
          qglTexParameterf(v12, 0x8501u, v16);
        }
      }
      ++v9;
    }
    while ( v9 < this->images.num );
  }
}

// FUNC: public: virtual void __thiscall idImage::Reload(bool,bool)
void __thiscall idImage::Reload(idImage *this, bool checkPrecompressed, unsigned int force)
{
  cubeFiles_t cubeFiles; // eax

  if ( this->generatorFunction )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "regenerating %s.\n",
      this->imgName.data);
    this->generatorFunction(this);
  }
  else
  {
    if ( (_BYTE)force )
      goto LABEL_8;
    cubeFiles = this->cubeFiles;
    if ( cubeFiles )
      R_LoadCubeImages(this->imgName.data, cubeFiles, 0, 0, &force);
    else
      R_LoadImageProgram(this->imgName.data, 0, 0, 0, &force, 0);
    if ( force > this->timestamp )
    {
LABEL_8:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "reloading %s.\n",
        this->imgName.data);
      this->PurgeImage(this);
      idImage::ActuallyLoadImage(this, checkPrecompressed, 0);
    }
  }
}

// FUNC: void __cdecl R_ReloadImages_f(class idCmdArgs const &)
void __usercall R_ReloadImages_f(int a1@<edi>, const idCmdArgs *args)
{
  int i; // edi
  idImage *v3; // eax
  idImage *v4; // esi
  int v5; // eax
  char *v6; // eax
  const char *v7; // eax
  const char *v8; // esi
  const char *v9; // [esp-Ah] [ebp-1Ch]
  char all_3; // [esp+Dh] [ebp-5h]
  char checkPrecompressed; // [esp+Eh] [ebp-4h]
  BOOL retaddr; // [esp+12h] [ebp+0h]
  int v13; // [esp+1Ah] [ebp+8h]

  globalImages->ChangeTextureFilter(globalImages);
  checkPrecompressed = 1;
  if ( args->argc == 2 && idStr::Icmp(args->argv[1], "all") )
  {
    if ( args->argc <= 1 )
      v7 = &entityFilter;
    else
      v7 = args->argv[1];
    if ( idStr::Icmp(v7, "reload") )
    {
      if ( args->argc <= 1 )
        v8 = &entityFilter;
      else
        v8 = args->argv[1];
      if ( idStr::Icmp(v8, "rebuild") )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "USAGE: reloadImages <all|reload|rebuild>\n");
        return;
      }
      checkPrecompressed = 0;
    }
    else
    {
      checkPrecompressed = 1;
    }
  }
  ((void (__thiscall *)(idFileSystem *, int, int))fileSystem->SetIsFileLoadingAllowed)(fileSystem, 1, a1);
  for ( i = 0; i < globalImages->GetNumImages(globalImages); ++i )
  {
    v3 = globalImages->GetImageByIndex(globalImages, i);
    v4 = v3;
    if ( !all_3 || v3->levelLoadReferenced )
    {
      v3->Reload(v3, retaddr, checkPrecompressed);
      v13 = **(_DWORD **)common.ip;
      v5 = ((int (__thiscall *)(idImageManager *, char *))globalImages->GetNumImages)(globalImages, v4->imgName.data);
      v6 = va("%d/%d: %s\n", i + 1, v5, v9);
      (*(void (__thiscall **)(_DWORD, char *))(v13 + 40))(*(_DWORD *)common.ip, v6);
    }
  }
  (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 120))(*(_DWORD *)common.ip);
  fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
}

// FUNC: void __cdecl R_ListRenderEntityWithShader(class idMaterial const *)
void __usercall R_ListRenderEntityWithShader(int a1@<edi>, const idMaterial *shader, int a3)
{
  idRenderWorldLocal *primaryWorld; // ecx
  int v4; // eax
  idRenderEntityLocal *v5; // ebp
  idRenderModel *hModel; // esi
  char v7; // bl
  int v8; // eax
  idRenderModel_vtbl *v9; // edx
  int v10; // esi
  int v11; // edi
  int v12; // esi
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int i; // [esp+18h] [ebp-8h]

  primaryWorld = tr.primaryWorld;
  if ( tr.primaryWorld )
  {
    v4 = 0;
    for ( i = 0; i < tr.primaryWorld->entityDefs.num; v4 = ++i )
    {
      v5 = primaryWorld->entityDefs.list[v4];
      if ( !v5 )
        goto LABEL_13;
      hModel = v5->parms.hModel;
      if ( !hModel->IsLoaded(hModel) )
        goto LABEL_13;
      v7 = 0;
      v8 = hModel->IsDynamicModel(hModel);
      v9 = hModel->__vftable;
      if ( v8 )
      {
        v10 = ((int (__thiscall *)(idRenderModel *, renderEntity_s *, _DWORD, _DWORD, int, int))v9->InstantiateDynamicModel)(
                hModel,
                &v5->parms,
                0,
                0,
                -65,
                a1);
        v11 = 0;
        if ( (*(int (__thiscall **)(int))(*(_DWORD *)v10 + 84))(v10) > 0 )
        {
          while ( a3 != *(_DWORD *)((*(int (__thiscall **)(int, int))(*(_DWORD *)v10 + 92))(v10, v11) + 4) )
          {
            if ( ++v11 >= (*(int (__thiscall **)(int))(*(_DWORD *)v10 + 84))(v10) )
              goto LABEL_11;
          }
          v7 = 1;
        }
LABEL_11:
        a1 = 1;
        (*(void (__thiscall **)(int))(*(_DWORD *)v10 + 4))(v10);
        if ( !v7 )
          goto LABEL_13;
      }
      else
      {
        v14 = 0;
        if ( v9->NumSurfaces(hModel) <= 0 )
          goto LABEL_13;
        while ( 1 )
        {
          v15 = (int)hModel->Surface(hModel, v14);
          if ( shader == R_RemapShaderBySkin(
                           *(const idMaterial **)(v15 + 4),
                           v5->parms.customSkin,
                           v5->parms.customShader) )
            break;
          if ( ++v14 >= hModel->NumSurfaces(hModel) )
            goto LABEL_13;
        }
      }
      v12 = *(_DWORD *)common.type;
      v13 = (int)v5->parms.hModel->Name(v5->parms.hModel);
      (*(void (**)(netadrtype_t, const char *, ...))(v12 + 124))(common.type, "\t\tFound model %s\n", v13);
LABEL_13:
      primaryWorld = tr.primaryWorld;
    }
  }
}

// FUNC: void __cdecl R_ListImageReferences_f(class idCmdArgs const &)
void __usercall R_ListImageReferences_f(int a1@<esi>, idCmdArgs *args, int j)
{
  int v3; // edi
  bool v4; // cc
  char *v5; // eax
  int v6; // ebp
  idImage *v7; // ebx
  int v8; // esi
  const idMaterial *v9; // ebp
  int v10; // edi
  newShaderStage_t **p_newStage; // esi
  newShaderStage_t *v12; // ecx
  int numFragmentProgramImages; // edx
  int v14; // eax
  idImage **fragmentProgramImages; // ecx
  int v16; // esi
  int type; // [esp+0h] [ebp-4Ch]
  int i; // [esp+18h] [ebp-34h]
  int count; // [esp+1Ch] [ebp-30h]
  idStr match; // [esp+20h] [ebp-2Ch] BYREF
  int v22; // [esp+48h] [ebp-4h]

  v3 = 0;
  match.len = 0;
  match.alloced = 20;
  match.data = match.baseBuffer;
  match.baseBuffer[0] = 0;
  v4 = args->argc < 2;
  v22 = 0;
  if ( v4 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "ListImageReferences <image pattern>\n");
    v22 = -1;
    idStr::FreeData(&match);
    return;
  }
  v5 = (char *)idCmdArgs::Args(args, 1, -1, 0);
  idStr::operator=(&match, v5);
  idStr::Replace(&match, " ", &entityFilter);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "Searching for '%s'\n\n",
    match.data);
  v6 = 0;
  i = 0;
  if ( globalImages->GetNumImages(globalImages) <= 0 )
    goto LABEL_23;
  do
  {
    v7 = globalImages->GetImageByIndex(globalImages, v6);
    if ( !idStr::Filter(match.data, v7->imgName.data, 0) )
      goto LABEL_22;
    count = ++v3;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%d.\tFound image %s\n",
      v3,
      v7->imgName.data);
    v8 = 0;
    if ( declManager->GetNumDecls(declManager, DECL_MATERIAL) <= 0 )
      goto LABEL_21;
    do
    {
      v9 = (const idMaterial *)((int (__thiscall *)(idDeclManager *, int, int, _DWORD, int))declManager->DeclByIndex)(
                                 declManager,
                                 1,
                                 v8,
                                 0,
                                 a1);
      if ( !v9->base->IsValid(v9->base) )
        goto LABEL_19;
      v10 = 0;
      if ( v9->numStages <= 0 )
        goto LABEL_19;
      p_newStage = &v9->stages->newStage;
      while ( 1 )
      {
        v12 = *p_newStage;
        if ( *p_newStage )
          break;
        if ( *(p_newStage - 16) == (newShaderStage_t *)v7 )
          goto LABEL_18;
LABEL_16:
        ++v10;
        p_newStage += 33;
        if ( v10 >= v9->numStages )
          goto LABEL_19;
      }
      numFragmentProgramImages = v12->numFragmentProgramImages;
      v14 = 0;
      if ( numFragmentProgramImages <= 0 )
        goto LABEL_16;
      fragmentProgramImages = v12->fragmentProgramImages;
      while ( *fragmentProgramImages != v7 )
      {
        ++v14;
        ++fragmentProgramImages;
        if ( v14 >= numFragmentProgramImages )
          goto LABEL_16;
      }
LABEL_18:
      v16 = *(_DWORD *)common.type;
      v9->base->GetName(v9->base);
      type = common.type;
      (*(void (**)(void))(v16 + 124))();
      R_ListRenderEntityWithShader(v10, v9, type);
LABEL_19:
      a1 = 1;
      v8 = ++j;
    }
    while ( j < ((int (__thiscall *)(idDeclManager *))declManager->GetNumDecls)(declManager) );
    v3 = count;
    v6 = i;
LABEL_21:
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
LABEL_22:
    i = ++v6;
  }
  while ( v6 < globalImages->GetNumImages(globalImages) );
LABEL_23:
  v22 = -1;
  idStr::FreeData(&match);
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::ImageFromFunction(char const *,void (__cdecl *)(class idImage *))
idImage *__thiscall idImageManagerLocal::ImageFromFunction(
        idImageManagerLocal *this,
        char *_name,
        void (__cdecl *generatorFunction)(idImage *))
{
  idImage *v4; // esi
  idImage *v5; // eax
  idStr name; // [esp+8h] [ebp-2Ch] BYREF
  int v8; // [esp+30h] [ebp-4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v8 = 0;
  idStr::operator=(&name, _name);
  idStr::Replace(&name, ".tga", &entityFilter);
  idStr::BackSlashesToSlashes(&name);
  v4 = this->imageHashTable[idStr::FileNameHash(&name)];
  if ( v4 )
  {
    while ( idStr::Icmp(name.data, v4->imgName.data) )
    {
      v4 = v4->hashNext;
      if ( !v4 )
        goto LABEL_4;
    }
    if ( v4->generatorFunction != generatorFunction )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
        common.type,
        "WARNING: reused image %s with mixed generators\n",
        name.data);
  }
  else
  {
LABEL_4:
    v5 = this->AllocImage(this, name.data);
    v4 = v5;
    v5->generatorFunction = generatorFunction;
    if ( image_preload.internalVar->integerValue )
    {
      v5->referencedOutsideLevelLoad = 1;
      idImage::ActuallyLoadImage(v5, 1, 0);
    }
  }
  v8 = -1;
  idStr::FreeData(&name);
  return v4;
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetImage(char const *)const
idImage *__thiscall idImageManagerLocal::GetImage(idImageManagerLocal *this, char *_name)
{
  idImage *v3; // esi
  idImage *defaultImage; // edi
  idStr name; // [esp+8h] [ebp-2Ch] BYREF
  int v7; // [esp+30h] [ebp-4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v7 = 0;
  if ( _name
    && *_name
    && idStr::Icmp(_name, "default")
    && idStr::Icmp(_name, "_default")
    && idStr::Icmp(_name, "_emptyName") )
  {
    idStr::operator=(&name, _name);
    idStr::Replace(&name, ".tga", &entityFilter);
    idStr::BackSlashesToSlashes(&name);
    v3 = this->imageHashTable[idStr::FileNameHash(&name)];
    if ( v3 )
    {
      while ( idStr::Icmp(name.data, v3->imgName.data) )
      {
        v3 = v3->hashNext;
        if ( !v3 )
          goto LABEL_9;
      }
      v7 = -1;
      idStr::FreeData(&name);
      return v3;
    }
    else
    {
LABEL_9:
      v7 = -1;
      idStr::FreeData(&name);
      return 0;
    }
  }
  else
  {
    declManager->MediaPrint(declManager, "DEFAULTED\n");
    defaultImage = this->defaultImage;
    v7 = -1;
    idStr::FreeData(&name);
    return defaultImage;
  }
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::PurgeAllImages(void)
void __thiscall idImageManagerLocal::PurgeAllImages(idImageManagerLocal *this)
{
  int i; // esi
  idImage *v3; // ecx

  for ( i = 0; i < this->images.num; ++i )
  {
    v3 = this->images.list[i];
    v3->PurgeImage(v3);
  }
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::ReloadAllImages(void)
void __thiscall idImageManagerLocal::ReloadAllImages(idImageManagerLocal *this)
{
  idCmdArgs args; // [esp+0h] [ebp-904h] BYREF

  ((void (__thiscall *)(idImageManagerLocal *, _DWORD))this->SetNormalPalette)(this, 0);
  idCmdArgs::TokenizeString(&args, "reloadImages reload", 0);
  R_ReloadImages_f(&args);
}

// FUNC: void __cdecl R_CombineCubeImages_f(class idCmdArgs const &)
void __usercall R_CombineCubeImages_f(int a1@<edi>, const idCmdArgs *args)
{
  const char *v2; // esi
  unsigned int v3; // eax
  int v4; // edi
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  int v9; // eax
  int v10; // ebp
  int v11; // esi
  unsigned __int8 *len; // ecx
  unsigned __int8 *v13; // edi
  int i; // esi
  int height; // [esp+10h] [ebp-160h] BYREF
  unsigned __int8 *pics[6]; // [esp+14h] [ebp-15Ch] BYREF
  idStr baseName; // [esp+2Ch] [ebp-144h] BYREF
  int orderRemap[6]; // [esp+4Ch] [ebp-124h]
  char filename[256]; // [esp+64h] [ebp-10Ch] BYREF
  int v21; // [esp+16Ch] [ebp-4h]

  if ( args->argc == 2 )
  {
    v2 = args->argv[1];
    baseName.len = 0;
    baseName.alloced = 20;
    baseName.data = baseName.baseBuffer;
    baseName.baseBuffer[0] = 0;
    if ( v2 )
    {
      v3 = (unsigned int)&v2[strlen(v2) + 1];
      v4 = v3 - (_DWORD)(v2 + 1);
      v5 = v3 - (_DWORD)v2;
      if ( v5 > 20 )
        idStr::ReAllocate(&baseName, v5, 1);
      data = baseName.data;
      v7 = v2;
      do
      {
        v8 = *v7;
        *data++ = *v7++;
      }
      while ( v8 );
      baseName.len = v4;
    }
    v9 = *(_DWORD *)common.type;
    v10 = 1;
    v21 = 0;
    (*(void (__thiscall **)(netadrtype_t, int, int))(v9 + 120))(common.type, 1, a1);
    orderRemap[1] = 1;
    orderRemap[2] = 3;
    orderRemap[3] = 4;
    orderRemap[4] = 2;
    orderRemap[5] = 5;
    *(_DWORD *)filename = 6;
    while ( 1 )
    {
      height = 0;
      pics[0] = 0;
      v11 = 0;
      while ( 1 )
      {
        sprintf(&filename[4], "%s%i%04i.tga", (const char *)baseName.alloced, orderRemap[v11 + 1], v10);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "reading %s\n",
          &filename[4]);
        R_LoadImage(&filename[4], &pics[v11 + 1], &height, (int *)pics, 0, 1);
        if ( !pics[v11 + 1] )
          break;
        switch ( v11 )
        {
          case 0:
            len = pics[1];
            goto LABEL_19;
          case 1:
            R_RotatePic(pics[2], height);
            R_HorizontalFlip(pics[2], height, (int)pics[0]);
            R_VerticalFlip(pics[2], height, (int)pics[0]);
            break;
          case 2:
            R_VerticalFlip(pics[3], height, (int)pics[0]);
            break;
          case 3:
            R_HorizontalFlip(pics[4], height, (int)pics[0]);
            break;
          case 4:
            R_RotatePic(pics[5], height);
            break;
          case 5:
            len = (unsigned __int8 *)baseName.len;
LABEL_19:
            R_RotatePic(len, height);
            break;
          default:
            break;
        }
        if ( ++v11 >= 6 )
          goto LABEL_23;
      }
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "not found.\n");
LABEL_23:
      if ( v11 != 6 )
        break;
      v13 = (unsigned __int8 *)Mem_Alloc(24 * height * (int)pics[0], 0xCu);
      for ( i = 0; i < 6; ++i )
      {
        SIMDProcessor->Memcpy(
          SIMDProcessor,
          &v13[4 * height * (int)pics[0] * i],
          pics[i + 1],
          4 * height * (int)pics[0]);
        Mem_Free(pics[i + 1]);
      }
      sprintf(&filename[4], "%sCM%04i.tga", (const char *)baseName.alloced, v10);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "writing %s\n",
        &filename[4]);
      R_WriteTGA(&filename[4], v13, height, 6 * (int)pics[0], 0);
      Mem_Free(v13);
      if ( ++v10 >= 10000 )
        goto LABEL_30;
    }
    for ( ; v11 > 0; ++v11 )
      Mem_Free(pics[v11 + 1]);
LABEL_30:
    (*(void (__thiscall **)(netadrtype_t, _DWORD))(*(_DWORD *)common.type + 120))(common.type, 0);
    v21 = -1;
    idStr::FreeData(&baseName);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: combineCubeImages <baseName>\n");
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      " combines basename[1-6][0001-9999].tga to basenameCM[0001-9999].tga\n");
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      " 1: forward 2:right 3:back 4:left 5:up 6:down\n");
  }
}

// FUNC: public: void __thiscall idImage::StartBackgroundImageLoad(void)
void __thiscall idImage::StartBackgroundImageLoad(idImage *this)
{
  bool v2; // zf
  idFile *v3; // eax
  unsigned int v4; // eax
  int v5; // ebp
  idImage *i; // edi
  int v7; // eax
  int j; // edi
  idImage *v9; // eax
  idImage *v10; // esi
  char filename[256]; // [esp+18h] [ebp-100h] BYREF

  if ( imageManagerLocal.numActiveBackgroundImageLoads < 8 )
  {
    if ( image_showBackgroundLoads.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "idImage::StartBackgroundImageLoad: %s\n",
        this->imgName.data);
    v2 = !this->precompressedFile;
    this->backgroundLoadInProgress = 1;
    if ( v2 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "idImageManagerLocal::StartBackgroundImageLoad: %s wasn't a precompressed file",
        this->imgName.data);
    }
    else
    {
      this->bglNext = imageManagerLocal.backgroundImageLoads;
      globalImages->SetBackgroundImageLoads(globalImages, this);
      idImage::ImageProgramStringToCompressedFileName(this, this->imgName.data, filename);
      this->bgl.completed = 0;
      v3 = fileSystem->OpenFileRead(fileSystem, filename, 1, 0);
      this->bgl.f = v3;
      if ( v3 )
      {
        this->bgl.file.position = 0;
        v4 = v3->Length(v3);
        this->bgl.file.length = v4;
        if ( v4 >= 0x7C )
        {
          this->bgl.file.buffer = R_StaticAlloc(v4);
          fileSystem->BackgroundDownload(fileSystem, &this->bgl);
          ++imageManagerLocal.numActiveBackgroundImageLoads;
          v5 = 0;
          for ( i = globalImages->GetCacheUsageNext(globalImages); i != globalImages->GetCacheHead(globalImages); v5 += v7 )
          {
            v7 = idImage::StorageSize(i);
            i = i->cacheUsageNext;
          }
          for ( j = idImage::StorageSize(this);
                image_cacheMegs.internalVar->floatValue * 1048576.0 < (double)(j + v5);
                v10->cacheUsagePrev = 0 )
          {
            v9 = globalImages->GetCacheUsagePrev(globalImages);
            v10 = v9;
            if ( v9->texnum != -1 )
            {
              v5 -= idImage::StorageSize(v9);
              if ( image_showBackgroundLoads.internalVar->integerValue )
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "purging %s\n",
                  v10->imgName.data);
              v10->PurgeImage(v10);
            }
            v10->cacheUsageNext->cacheUsagePrev = v10->cacheUsagePrev;
            v10->cacheUsagePrev->cacheUsageNext = v10->cacheUsageNext;
            v10->cacheUsageNext = 0;
          }
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "idImageManagerLocal::StartBackgroundImageLoad: %s had a bad file length",
            this->imgName.data);
        }
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "idImageManagerLocal::StartBackgroundImageLoad: Couldn't load %s",
          this->imgName.data);
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::CompleteBackgroundImageLoads(void)
void __thiscall idImageManagerLocal::CompleteBackgroundImageLoads(idImageManagerLocal *this)
{
  idImage *backgroundImageLoads; // esi
  idImage *v3; // ecx
  idImage *bglNext; // ebp
  idImage *partialImage; // eax
  int v6; // edx
  idImage *remainingList; // [esp+Ch] [ebp-4h]

  backgroundImageLoads = this->backgroundImageLoads;
  v3 = 0;
  remainingList = 0;
  if ( backgroundImageLoads )
  {
    do
    {
      bglNext = backgroundImageLoads->bglNext;
      if ( backgroundImageLoads->bgl.completed )
      {
        --this->numActiveBackgroundImageLoads;
        fileSystem->CloseFile(fileSystem, backgroundImageLoads->bgl.f);
        partialImage = backgroundImageLoads->partialImage;
        backgroundImageLoads->backgroundLoadInProgress = 0;
        if ( partialImage->generatorFunction )
        {
          partialImage->generatorFunction = 0;
          idImage::UploadPrecompressedImage(
            backgroundImageLoads->partialImage,
            (unsigned __int8 *)backgroundImageLoads->bgl.file.buffer,
            backgroundImageLoads->bgl.file.length,
            3553,
            0);
        }
        idImage::UploadPrecompressedImage(
          backgroundImageLoads,
          (unsigned __int8 *)backgroundImageLoads->bgl.file.buffer,
          backgroundImageLoads->bgl.file.length,
          3553,
          0);
        R_StaticFree(backgroundImageLoads->bgl.file.buffer);
        if ( image_showBackgroundLoads.internalVar->integerValue )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "R_CompleteBackgroundImageLoad: %s\n",
            backgroundImageLoads->imgName.data);
      }
      else
      {
        backgroundImageLoads->bglNext = v3;
        remainingList = backgroundImageLoads;
      }
      v3 = remainingList;
      backgroundImageLoads = bglNext;
    }
    while ( bglNext );
  }
  if ( !image_showBackgroundLoads.internalVar->integerValue || this->numActiveBackgroundImageLoads == prev )
  {
    this->backgroundImageLoads = v3;
  }
  else
  {
    v6 = *(_DWORD *)common.type;
    prev = this->numActiveBackgroundImageLoads;
    (*(void (**)(netadrtype_t, const char *, ...))(v6 + 124))(common.type, "background Loads: %i\n", prev);
    this->backgroundImageLoads = remainingList;
  }
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::CheckCvars(void)
void __thiscall idImageManagerLocal::CheckCvars(idImageManagerLocal *this)
{
  if ( (image_filter.internalVar->flags & 0x40000) != 0
    || (image_anisotropy.internalVar->flags & 0x40000) != 0
    || (image_lodbias.internalVar->flags & 0x40000) != 0 )
  {
    this->ChangeTextureFilter(this);
    image_filter.internalVar->flags &= ~0x40000u;
    image_anisotropy.internalVar->flags &= ~0x40000u;
    image_lodbias.internalVar->flags &= ~0x40000u;
  }
}

// FUNC: public: virtual int __thiscall idImageManagerLocal::SumOfUsedImages(void)
int __thiscall idImageManagerLocal::SumOfUsedImages(idImageManagerLocal *this)
{
  int v2; // esi
  int i; // ebx
  idImage *v4; // ecx

  v2 = 0;
  for ( i = 0; v2 < this->images.num; ++v2 )
  {
    v4 = this->images.list[v2];
    if ( v4->internalFormat && v4->frameUsed == backEnd.frameCount )
      i += idImage::StorageSize(v4);
  }
  return i;
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::BeginLevelLoad(void)
void __thiscall idImageManagerLocal::BeginLevelLoad(idImageManagerLocal *this)
{
  int v2; // ebp
  bool v3; // cc
  idImage *v4; // esi
  bool v5; // zf

  v2 = 0;
  v3 = this->images.num <= 0;
  this->insideLevelLoad = 1;
  if ( !v3 )
  {
    do
    {
      v4 = this->images.list[v2];
      v5 = v4->generatorFunction == 0;
      v4->useCount = 0;
      if ( v5 )
      {
        if ( com_purgeAll.internalVar->integerValue )
          v4->PurgeImage(v4);
        v4->levelLoadReferenced = 0;
      }
      ++v2;
    }
    while ( v2 < this->images.num );
  }
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::EndLevelLoad(void)
void __thiscall idImageManagerLocal::EndLevelLoad(idImageManagerLocal *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // ebp
  idImage *v6; // ecx
  int i; // edi
  idImage *v8; // ecx
  int v9; // esi
  int keepCount; // [esp+18h] [ebp-Ch]
  int backgroundloadcount; // [esp+1Ch] [ebp-8h]
  int start; // [esp+20h] [ebp-4h]

  v2 = Sys_Milliseconds();
  this->insideLevelLoad = 0;
  start = v2;
  v3 = 0;
  if ( !idAsyncNetwork::serverDedicated.internalVar->integerValue )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "----- idImageManagerLocal::EndLevelLoad -----\n");
    v4 = 0;
    v5 = 0;
    keepCount = 0;
    backgroundloadcount = 0;
    if ( this->images.num > 0 )
    {
      do
      {
        v6 = this->images.list[v3];
        if ( !v6->generatorFunction )
        {
          if ( v6->levelLoadReferenced || v6->referencedOutsideLevelLoad )
          {
            if ( v6->texnum == -1 )
            {
              if ( v6->partialImage )
                ++backgroundloadcount;
            }
            else
            {
              ++keepCount;
            }
          }
          else
          {
            ++v5;
            v6->PurgeImage(v6);
          }
        }
        ++v3;
      }
      while ( v3 < this->images.num );
    }
    for ( i = 0; i < this->images.num; ++i )
    {
      v8 = this->images.list[i];
      if ( !v8->generatorFunction && v8->levelLoadReferenced && v8->texnum == -1 && !v8->partialImage )
      {
        ++v4;
        idImage::ActuallyLoadImage(v8, 1, 0);
        if ( (v4 & 0xF) == 0 )
          session->PacifierUpdate(session);
      }
    }
    v9 = Sys_Milliseconds();
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%5i purged from previous\n",
      v5);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%5i kept from previous\n",
      keepCount);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%5i new loaded\n", v4);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "all images loaded in %5.1f seconds\n",
      (double)(v9 - start) * 0.001);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%5i deferred loading\n",
      backgroundloadcount);
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "---------------------------------------------\n");
  }
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::GetEditorImageDimensions(class idMaterial const *,int &,int &)
void __thiscall idImageManagerLocal::GetEditorImageDimensions(
        idImageManagerLocal *this,
        idMaterial *mat,
        int *w,
        int *h)
{
  idImage *EditorImage; // edi
  int v5; // edi
  const char *v6; // eax

  EditorImage = idMaterial::GetEditorImage(mat);
  if ( EditorImage->texnum == -1 )
    globalImages->ActuallyLoadImage(globalImages, EditorImage, 1, 0);
  *w = EditorImage->uploadWidth << image_downSize.internalVar->integerValue;
  v5 = EditorImage->uploadHeight << image_downSize.internalVar->integerValue;
  *h = v5;
  if ( !*w || !v5 )
  {
    v6 = mat->base->GetName(mat->base);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "GetEditorImageDimensions: Editor image for '%s' is %dx%d",
      v6,
      *w,
      *h);
    *w = 2;
    *h = 2;
  }
}

// FUNC: public: virtual unsigned int __thiscall idImageManagerLocal::ListImageSummary(void)
int __thiscall idImageManagerLocal::ListImageSummary(idImageManagerLocal *this)
{
  int v2; // esi
  int i; // ebx
  int v4; // eax

  v2 = 0;
  for ( i = 0; v2 < this->images.num; i += v4 )
    v4 = idImage::StorageSize(this->images.list[v2++]);
  return i;
}

// FUNC: void __cdecl R_ListImages_f(class idCmdArgs const &)
void __cdecl R_ListImages_f(const idCmdArgs *args)
{
  const char *v1; // eax
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // eax
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  idImageManager_vtbl *v10; // eax
  int v11; // edi
  int v12; // eax
  void *v13; // esp
  idImageManager_vtbl *v14; // edx
  idImage *v15; // eax
  idImage *v16; // esi
  int internalFormat; // eax
  int j; // edi
  idImage *v19; // eax
  bool v20; // zf
  int v21; // eax
  const char *v22; // eax
  const char *v23; // esi
  int v24; // eax
  int v25; // esi
  int v26; // edi
  int v27; // edi
  int v28; // eax
  int v29; // esi
  idList<int> *v30; // esi
  int granularity; // eax
  bool v32; // cc
  int k; // eax
  int num; // ebx
  int size; // ecx
  int v36; // ecx
  int *list; // edi
  int m; // eax
  int v39; // esi
  int *v40; // edi
  int v41; // ebx
  int v42; // eax
  int *v43; // ecx
  int v44; // edx
  idImage *image; // eax
  int v46; // eax
  int v47; // edx
  int v48; // eax
  int *v49; // ebx
  int *v50; // eax
  int v51; // ecx
  int v52; // edx
  int n; // ebx
  _BYTE v54[12]; // [esp+18h] [ebp-15Ch] BYREF
  idList<int> classifications[17]; // [esp+24h] [ebp-150h] BYREF
  int *v56; // [esp+134h] [ebp-40h]
  int *v57; // [esp+138h] [ebp-3Ch]
  idList<int> overSizedList; // [esp+13Ch] [ebp-38h]
  sortedImage_t *sortedArray; // [esp+14Ch] [ebp-28h]
  int matchTag; // [esp+150h] [ebp-24h]
  int totalSize; // [esp+154h] [ebp-20h]
  bool partial; // [esp+158h] [ebp-1Ch]
  bool inview; // [esp+159h] [ebp-1Bh]
  bool touched; // [esp+15Ah] [ebp-1Ah]
  bool cached; // [esp+15Bh] [ebp-19h]
  bool uncached; // [esp+15Ch] [ebp-18h]
  bool uncompressedOnly; // [esp+15Dh] [ebp-17h]
  bool unloaded; // [esp+15Eh] [ebp-16h]
  bool duplicated; // [esp+15Fh] [ebp-15h]
  int count; // [esp+160h] [ebp-14h]
  bool overSized; // [esp+165h] [ebp-Fh]
  bool byClassification; // [esp+166h] [ebp-Eh]
  bool sorted; // [esp+167h] [ebp-Dh]
  int v74; // [esp+170h] [ebp-4h]
  int i; // [esp+17Ch] [ebp+8h]
  int ia; // [esp+17Ch] [ebp+8h]
  idList<int> *ib; // [esp+17Ch] [ebp+8h]

  count = 0;
  matchTag = 0;
  uncompressedOnly = 0;
  unloaded = 0;
  partial = 0;
  cached = 0;
  uncached = 0;
  touched = 0;
  sorted = 0;
  duplicated = 0;
  byClassification = 0;
  overSized = 0;
  inview = 0;
  if ( args->argc == 1 )
    goto LABEL_50;
  if ( args->argc != 2 )
    goto LABEL_89;
  if ( idStr::Icmp(args->argv[1], "uncompressed") )
  {
    if ( args->argc <= 1 )
      v1 = &entityFilter;
    else
      v1 = args->argv[1];
    if ( !idStr::Icmp(v1, "sorted") )
      goto LABEL_49;
    if ( args->argc <= 1 )
      v2 = &entityFilter;
    else
      v2 = args->argv[1];
    if ( !idStr::Icmp(v2, "partial") )
    {
      partial = 1;
      goto LABEL_50;
    }
    if ( args->argc <= 1 )
      v3 = &entityFilter;
    else
      v3 = args->argv[1];
    if ( !idStr::Icmp(v3, "unloaded") )
    {
      unloaded = 1;
      goto LABEL_50;
    }
    if ( args->argc <= 1 )
      v4 = &entityFilter;
    else
      v4 = args->argv[1];
    if ( !idStr::Icmp(v4, "cached") )
    {
      cached = 1;
      goto LABEL_50;
    }
    if ( args->argc <= 1 )
      v5 = &entityFilter;
    else
      v5 = args->argv[1];
    if ( !idStr::Icmp(v5, "uncached") )
    {
      uncached = 1;
      goto LABEL_50;
    }
    if ( args->argc <= 1 )
      v6 = &entityFilter;
    else
      v6 = args->argv[1];
    if ( !idStr::Icmp(v6, "tagged") )
    {
      matchTag = 1;
      goto LABEL_50;
    }
    if ( args->argc <= 1 )
      v7 = &entityFilter;
    else
      v7 = args->argv[1];
    if ( !idStr::Icmp(v7, "duplicated") )
    {
      duplicated = 1;
      goto LABEL_50;
    }
    if ( args->argc <= 1 )
      v8 = &entityFilter;
    else
      v8 = args->argv[1];
    if ( !idStr::Icmp(v8, "touched") )
    {
      touched = 1;
      goto LABEL_50;
    }
    if ( args->argc <= 1 )
      v9 = &entityFilter;
    else
      v9 = args->argv[1];
    if ( !idStr::Icmp(v9, "classify") )
    {
      byClassification = 1;
LABEL_49:
      sorted = 1;
      goto LABEL_50;
    }
    if ( args->argc <= 1 )
      v22 = &entityFilter;
    else
      v22 = args->argv[1];
    if ( !idStr::Icmp(v22, "oversized") )
    {
      byClassification = 1;
      overSized = 1;
      goto LABEL_49;
    }
    if ( args->argc <= 1 )
      v23 = &entityFilter;
    else
      v23 = args->argv[1];
    if ( !idStr::Icmp(v23, "inview") )
    {
      inview = 1;
      goto LABEL_50;
    }
LABEL_89:
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: listImages [ sorted | partial | unloaded | cached | uncached | tagged | duplicated | touched | classify | s"
      "howOverSized | inview ]\n");
    return;
  }
  uncompressedOnly = 1;
LABEL_50:
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "\n%s",
    "       -w-- -h-- filt -fmt- wrap   use  size  --name-------\n");
  v10 = globalImages->__vftable;
  v11 = 0;
  totalSize = 0;
  v12 = 8 * v10->GetNumImages(globalImages) + 3;
  LOBYTE(v12) = v12 & 0xFC;
  v13 = alloca(v12);
  v14 = globalImages->__vftable;
  sortedArray = (sortedImage_t *)v54;
  i = 0;
  if ( v14->GetNumImages(globalImages) > 0 )
  {
    while ( 1 )
    {
      v15 = globalImages->GetImageByIndex(globalImages, v11);
      v16 = v15;
      if ( uncompressedOnly )
      {
        internalFormat = v15->internalFormat;
        if ( internalFormat >= 33776 && internalFormat <= 33779 )
          goto LABEL_92;
        if ( internalFormat == 32997 )
          goto LABEL_92;
      }
      if ( matchTag && v16->classification != matchTag
        || unloaded && v16->texnum != -1
        || partial && !v16->isPartialImage
        || cached && (!v16->partialImage || v16->texnum == -1)
        || uncached && (!v16->partialImage || v16->texnum != -1)
        || inview && v16->frameUsed != backEnd.frameCount )
      {
        goto LABEL_92;
      }
      if ( duplicated )
      {
        for ( j = i + 1; j < globalImages->GetNumImages(globalImages); ++j )
        {
          v19 = globalImages->GetImageByIndex(globalImages, j);
          if ( !idStr::Icmp(v16->imgName.data, v19->imgName.data) )
            break;
        }
        v20 = j == globalImages->GetNumImages(globalImages);
        v11 = i;
        if ( v20 )
          goto LABEL_92;
      }
      if ( !touched )
        goto LABEL_77;
      if ( v16->bindCount )
        break;
LABEL_92:
      i = ++v11;
      if ( v11 >= globalImages->GetNumImages(globalImages) )
        goto LABEL_93;
    }
    v16->bindCount = 0;
LABEL_77:
    if ( sorted )
    {
      *(_DWORD *)&v54[8 * count] = v16;
      v21 = idImage::StorageSize(v16);
      *(_DWORD *)&v54[8 * count + 4] = v21;
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%4i:", v11);
      idImage::Print(v16);
    }
    v24 = idImage::StorageSize(v16);
    totalSize += v24;
    ++count;
    goto LABEL_92;
  }
LABEL_93:
  if ( sorted )
  {
    qsort(v54, count, 8u, (int (__cdecl *)(const void *, const void *))R_QsortImageSizes);
    v25 = 0;
    v26 = 0;
    while ( v25 < count )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%4i:", v25);
      idImage::Print(*(idImage **)&v54[8 * v25]);
      v26 += idImage::StorageSize(*(idImage **)&v54[8 * v25++]);
      matchTag = v26;
      if ( !(v25 % 10) )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "-------- %5.1f of %5.1f megs --------\n",
          (double)matchTag * 0.00000095367431640625,
          (double)totalSize * 0.00000095367431640625);
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%s",
    "       -w-- -h-- filt -fmt- wrap   use  size  --name-------\n");
  v27 = *(_DWORD *)common.type;
  v28 = globalImages->GetNumImages(globalImages);
  v29 = count;
  (*(void (**)(netadrtype_t, const char *, ...))(v27 + 124))(common.type, " %i images (%i total)\n", count, v28);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " %5.1f total megabytes of images\n\n\n",
    (double)totalSize * 0.00000095367431640625);
  if ( byClassification )
  {
    `eh vector constructor iterator'(
      (char *)classifications,
      0x10u,
      17,
      (void (__thiscall *)(void *))idList<rvServerScanGUI *>::`default constructor closure',
      (void (__thiscall *)(void *))idList<idDeclFolder *>::~idList<idDeclFolder *>);
    v74 = 0;
    ia = 0;
    if ( v29 > 0 )
    {
      do
      {
        v30 = &classifications[ClassifyImage(sortedArray[ia].image->imgName.data)];
        if ( !v30->list )
        {
          granularity = v30->granularity;
          if ( granularity > 0 )
          {
            if ( granularity != v30->size )
            {
              v32 = granularity < v30->num;
              v30->size = granularity;
              if ( v32 )
                v30->num = granularity;
              v30->list = (int *)Memory::Allocate(4 * granularity);
              for ( k = 0; k < v30->num; ++k )
                v30->list[k] = *(_DWORD *)(4 * k);
            }
          }
          else
          {
            v30->list = 0;
            v30->num = 0;
            v30->size = 0;
          }
        }
        num = v30->num;
        size = v30->size;
        if ( v30->num == size )
        {
          if ( !v30->granularity )
            v30->granularity = 16;
          v36 = v30->granularity + size - (v30->granularity + size) % v30->granularity;
          if ( v36 > 0 )
          {
            if ( v36 != v30->size )
            {
              list = v30->list;
              v30->size = v36;
              if ( v36 < num )
                v30->num = v36;
              v30->list = (int *)Memory::Allocate(4 * v36);
              for ( m = 0; m < v30->num; ++m )
                v30->list[m] = list[m];
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( v30->list )
              Memory::Free(v30->list);
            v30->list = 0;
            v30->num = 0;
            v30->size = 0;
          }
        }
        v30->list[v30->num++] = ia++;
      }
      while ( ia < count );
    }
    overSizedList.granularity = 16;
    ib = classifications;
    totalSize = (int)&IC_Info[0].maxHeight;
    do
    {
      v39 = 0;
      v40 = 0;
      matchTag = 0;
      overSizedList.list = 0;
      overSizedList.num = 0;
      overSizedList.size = 0;
      v41 = 0;
      v32 = ib->num <= 0;
      LOBYTE(v74) = 1;
      count = 0;
      if ( !v32 )
      {
        do
        {
          v42 = idImage::StorageSize(sortedArray[ib->list[v41]].image);
          matchTag += v42;
          if ( overSized )
          {
            v43 = ib->list;
            v44 = v43[v41];
            v57 = &v43[v41];
            image = sortedArray[v44].image;
            if ( image->uploadWidth > *(_DWORD *)(totalSize - 4) && image->uploadHeight > *(_DWORD *)totalSize )
            {
              if ( !v40 && overSizedList.size != 16 )
              {
                overSizedList.size = 16;
                if ( v39 > 16 )
                {
                  v39 = 16;
                  overSizedList.num = 16;
                }
                v40 = (int *)Memory::Allocate(0x40u);
                v46 = 0;
                for ( overSizedList.list = v40; v46 < v39; ++v46 )
                  v40[v46] = *(_DWORD *)(4 * v46);
              }
              if ( v39 == overSizedList.size )
              {
                v47 = (overSizedList.size + 16) % 16;
                v48 = overSizedList.size + 16 - v47;
                if ( v48 > 0 )
                {
                  if ( v48 != overSizedList.size )
                  {
                    v49 = v40;
                    v56 = v40;
                    overSizedList.size = overSizedList.size + 16 - v47;
                    if ( v48 < v39 )
                    {
                      v39 = v48;
                      overSizedList.num = v48;
                    }
                    v50 = (int *)Memory::Allocate(4 * v48);
                    v40 = v50;
                    overSizedList.list = v50;
                    if ( v39 > 0 )
                    {
                      v51 = (char *)v49 - (char *)v50;
                      v52 = v39;
                      do
                      {
                        *v50 = *(int *)((char *)v50 + v51);
                        ++v50;
                        --v52;
                      }
                      while ( v52 );
                      v49 = v56;
                    }
                    if ( v49 )
                      Memory::Free(v49);
                  }
                }
                else
                {
                  if ( v40 )
                    Memory::Free(v40);
                  v40 = 0;
                  v39 = 0;
                  overSizedList.list = 0;
                  overSizedList.size = 0;
                }
              }
              v41 = count;
              v40[v39++] = *v57;
              overSizedList.num = v39;
            }
          }
          v32 = ++v41 < ib->num;
          count = v41;
        }
        while ( v32 );
      }
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        " Classification %s contains %i images using %5.1f megabytes\n",
        *(_DWORD *)(totalSize - 12),
        ib->num,
        (double)matchTag * 0.00000095367431640625);
      if ( overSized )
      {
        if ( v39 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "  The following images may be oversized\n");
          for ( n = 0; n < v39; ++n )
          {
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "    ");
            idImage::Print(sortedArray[v40[n]].image);
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
          }
        }
      }
      LOBYTE(v74) = 0;
      if ( v40 )
        Memory::Free(v40);
      ++ib;
      v32 = totalSize + 20 < (int)"World Geometry";
      overSizedList.list = 0;
      overSizedList.num = 0;
      overSizedList.size = 0;
      totalSize += 20;
    }
    while ( v32 );
    v74 = -1;
    `eh vector destructor iterator'(
      (char *)classifications,
      0x10u,
      17,
      (void (__thiscall *)(void *))idList<idDeclFolder *>::~idList<idDeclFolder *>);
  }
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::Shutdown(void)
void __thiscall idImageManagerLocal::Shutdown(idImageManagerLocal *this)
{
  int i; // edi
  idImage *v3; // ecx

  for ( i = 0; i < this->images.num; ++i )
  {
    v3 = this->images.list[i];
    if ( v3 )
      ((void (__thiscall *)(idImage *, int))v3->~idImage)(v3, 1);
    this->images.list[i] = 0;
  }
  if ( this->images.list )
    Memory::Free(this->images.list);
  this->images.list = 0;
  this->images.num = 0;
  this->images.size = 0;
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::GenerateRDF(char const *)
void __userpurge idImageManagerLocal::GenerateRDF(
        idImageManagerLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<edi>,
        const char *forceName)
{
  const char *data; // esi
  const idKeyValue *Key; // eax
  unsigned int v7; // eax
  int v8; // ebx
  int v9; // eax
  char *v10; // edx
  const char *v11; // ecx
  char v12; // al
  const idKeyValue *v13; // eax
  const char *v14; // esi
  int v15; // eax
  unsigned int v16; // eax
  int v17; // ebx
  int v18; // eax
  char *v19; // edx
  const char *v20; // ecx
  char v21; // al
  int v22; // esi
  int v23; // eax
  char v24; // cl
  char *v25; // edx
  int v26; // esi
  int i; // eax
  char v28; // cl
  char *v29; // edx
  idStr *v30; // esi
  unsigned int len; // ebx
  int v32; // eax
  idFileSystem_vtbl *v33; // edx
  idFile *v34; // esi
  int alloced; // edi
  char *v36; // ecx
  _BYTE *v37; // edx
  char v38; // al
  int v39; // edi
  char *v40; // ecx
  _BYTE *v41; // edx
  char v42; // al
  int v43; // eax
  idFile *v44; // esi
  int v45; // edi
  int j; // ebx
  int v47; // edx
  idStr fn; // [esp+20h] [ebp-8Ch] BYREF
  idStr ef; // [esp+40h] [ebp-6Ch] BYREF
  idStr xprFn; // [esp+60h] [ebp-4Ch] BYREF
  idStr rdfFn; // [esp+80h] [ebp-2Ch] BYREF
  int v53; // [esp+A8h] [ebp-4h]

  data = forceName;
  if ( !forceName )
  {
    Key = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_map");
    if ( Key )
      data = Key->value->data;
    else
      data = &entityFilter;
  }
  fn.len = 0;
  fn.alloced = 20;
  fn.data = fn.baseBuffer;
  fn.baseBuffer[0] = 0;
  if ( data )
  {
    v7 = (unsigned int)&data[strlen(data) + 1];
    v8 = v7 - (_DWORD)(data + 1);
    v9 = v7 - (_DWORD)data;
    if ( v9 > 20 )
      idStr::ReAllocate(&fn, v9, 1);
    v10 = fn.data;
    v11 = data;
    do
    {
      v12 = *v11;
      *v10++ = *v11++;
    }
    while ( v12 );
    fn.len = v8;
  }
  v53 = 0;
  v13 = idDict::FindKey(&sessLocal.mapSpawnData.serverInfo, "si_entityFilter");
  if ( v13 )
    v14 = v13->value->data;
  else
    v14 = &entityFilter;
  v15 = 0;
  ef.len = 0;
  ef.alloced = 20;
  ef.data = ef.baseBuffer;
  ef.baseBuffer[0] = 0;
  if ( v14 )
  {
    v16 = (unsigned int)&v14[strlen(v14) + 1];
    v17 = v16 - (_DWORD)(v14 + 1);
    v18 = v16 - (_DWORD)v14;
    if ( v18 > 20 )
      idStr::ReAllocate(&ef, v18, 1);
    v19 = ef.data;
    v20 = v14;
    do
    {
      v21 = *v20;
      *v19++ = *v20++;
    }
    while ( v21 );
    v15 = v17;
    ef.len = v17;
  }
  LOBYTE(v53) = 1;
  if ( fn.len )
  {
    if ( v15 )
    {
      v22 = fn.len + 1;
      if ( fn.len + 2 > fn.alloced )
        idStr::ReAllocate(&fn, fn.len + 2, 1);
      v23 = 0;
      v24 = 45;
      do
      {
        v25 = &fn.data[v23++];
        v25[fn.len] = v24;
        v24 = asc_1029DD84[v23];
      }
      while ( v24 );
      fn.len = v22;
      fn.data[v22] = 0;
      v26 = ef.len + fn.len;
      if ( ef.len + fn.len + 1 > fn.alloced )
        idStr::ReAllocate(&fn, ef.len + fn.len + 1, 1);
      for ( i = 0; i < ef.len; v29[fn.len] = v28 )
      {
        v28 = ef.data[i];
        v29 = &fn.data[i++];
      }
      fn.len = v26;
      fn.data[v26] = 0;
    }
  }
  else
  {
    idStr::operator=(&fn, "common");
  }
  v30 = operator+(&xprFn, "xpr\\", &fn);
  len = v30->len;
  v32 = v30->len + 1;
  LOBYTE(v53) = 2;
  if ( v32 > fn.alloced )
    idStr::ReAllocate(&fn, v32, 0);
  qmemcpy(fn.data, v30->data, len);
  fn.data[len] = 0;
  fn.len = len;
  LOBYTE(v53) = 1;
  idStr::FreeData(&xprFn);
  idStr::SlashesToBackSlashes(&fn);
  v33 = fileSystem->__vftable;
  if ( firstTime )
  {
    firstTime = 0;
    v34 = (idFile *)((int (__stdcall *)(const char *, const char *, _DWORD, int, int))v33->OpenFileWrite)(
                      "makexpr.bat",
                      "fs_savepath",
                      0,
                      a3,
                      a2);
    v34->Printf(v34, "set BUNDLER=Q:\\bin\\xenon\\bundler.exe\n");
    v34->Printf(v34, "if not exist %%BUNDLER%% goto fail\n");
    v34->Printf(v34, "goto start\n");
    v34->Printf(v34, ":fail\n");
    v34->Printf(v34, "echo Can't find bundler!\n");
    v34->Printf(v34, "pause\n\n");
    v34->Printf(v34, ":start\n");
  }
  else
  {
    v34 = (idFile *)((int (__stdcall *)(const char *, _DWORD, const char *, int, int))v33->OpenFileAppend)(
                      "makexpr.bat",
                      0,
                      "fs_basepath",
                      a3,
                      a2);
  }
  if ( v34 )
  {
    *(_DWORD *)xprFn.baseBuffer = &xprFn.baseBuffer[8];
    alloced = fn.alloced;
    xprFn.alloced = 0;
    *(_DWORD *)&xprFn.baseBuffer[4] = 20;
    xprFn.baseBuffer[8] = 0;
    if ( fn.alloced + 1 > 20 )
      idStr::ReAllocate((idStr *)&xprFn.alloced, fn.alloced + 1, 1);
    v36 = *(char **)fn.baseBuffer;
    v37 = *(_BYTE **)xprFn.baseBuffer;
    do
    {
      v38 = *v36;
      *v37++ = *v36++;
    }
    while ( v38 );
    xprFn.alloced = alloced;
    idStr::SetFileExtension((idStr *)&xprFn.alloced, "xpr");
    v39 = fn.alloced;
    rdfFn.alloced = 0;
    *(_DWORD *)&rdfFn.baseBuffer[4] = 20;
    *(_DWORD *)rdfFn.baseBuffer = &rdfFn.baseBuffer[8];
    rdfFn.baseBuffer[8] = 0;
    if ( fn.alloced + 1 > 20 )
      idStr::ReAllocate((idStr *)&rdfFn.alloced, fn.alloced + 1, 1);
    v40 = *(char **)fn.baseBuffer;
    v41 = *(_BYTE **)rdfFn.baseBuffer;
    do
    {
      v42 = *v40;
      *v41++ = *v40++;
    }
    while ( v42 );
    rdfFn.alloced = v39;
    idStr::SetFileExtension((idStr *)&rdfFn.alloced, "rdf");
    v34->Printf(v34, "%%BUNDLER%% %s -a -o %s\n", *(_DWORD *)rdfFn.baseBuffer, *(_DWORD *)xprFn.baseBuffer);
    fileSystem->CloseFile(fileSystem, v34);
    idStr::FreeData((idStr *)&rdfFn.alloced);
    idStr::FreeData((idStr *)&xprFn.alloced);
  }
  idStr::BackSlashesToSlashes((idStr *)&fn.alloced);
  idStr::SetFileExtension((idStr *)&fn.alloced, "rdf");
  v43 = ((int (__thiscall *)(idFileSystem *, _DWORD))fileSystem->OpenFileWrite)(fileSystem, *(_DWORD *)fn.baseBuffer);
  v44 = (idFile *)v43;
  if ( v43 )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)v43 + 48))(v43);
    v44->Printf(v44, "\n<RDF Version=\"XPR2\">\n");
    v45 = 0;
    for ( j = 0; v45 < this->XMLList.num; ++v45 )
    {
      if ( this->XMLList.list[v45]->cubeFlag )
      {
        if ( !j )
        {
          v44->Printf(v44, "\n<CubeMap\n");
          v44->Printf(v44, "\tName\t= \"%s\"\n", this->XMLList.list[v45]->dest.data);
        }
        v44->Printf(v44, "\tSource%d\t= \"%s.tga\"\n", j, this->XMLList.list[v45]->source.data);
        v47 = j++;
        if ( v47 == 5 )
        {
          v44->Printf(v44, "\tFormat\t= \"D3DFMT_%s\"\n", this->XMLList.list[v45]->format.data);
          v44->Printf(v44, "\tSize\t= \"%ld\"\n", this->XMLList.list[v45]->uploadWidth);
          v44->Printf(v44, "\tLevels\t= \"1\"\n");
          v44->Printf(v44, "/>\n");
          j = 0;
        }
      }
      else
      {
        v44->Printf(v44, "\n<Texture\n");
        v44->Printf(v44, "\tName\t= \"%s\"\n", this->XMLList.list[v45]->dest.data);
        v44->Printf(v44, "\tSource\t= \"%s.tga\"\n", this->XMLList.list[v45]->source.data);
        v44->Printf(v44, "\tFormat\t= \"D3DFMT_%s\"\n", this->XMLList.list[v45]->format.data);
        v44->Printf(v44, "\tWidth\t= \"%ld\"\n", this->XMLList.list[v45]->uploadWidth);
        v44->Printf(v44, "\tHeight\t= \"%ld\"\n", this->XMLList.list[v45]->uploadHeight);
        v44->Printf(v44, "\tLevels\t= \"%d\"\n", HIBYTE(fn.len) != 0);
        v44->Printf(v44, "/>\n");
      }
    }
    v44->Printf(v44, "</RDF>");
    fileSystem->CloseFile(fileSystem, v44);
  }
  if ( this->XMLList.list )
    Memory::Free(this->XMLList.list);
  this->XMLList.list = 0;
  this->XMLList.num = 0;
  this->XMLList.size = 0;
  LOBYTE(v53) = 0;
  idStr::FreeData(&ef);
  v53 = -1;
  idStr::FreeData(&fn);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::AddXMLElement(class idStr,class idStr,class idStr,int,int,int,int)
void __thiscall idImageManagerLocal::AddXMLElement(
        idImageManagerLocal *this,
        idStr source,
        idStr dest,
        idStr format,
        int numLevels,
        int uploadWidth,
        int uploadHeight,
        int cubeFlag)
{
  XMLElement_t *v9; // eax
  XMLElement_t *v10; // ebx
  int len; // esi
  int v12; // esi
  int v13; // esi
  char *data; // edi
  unsigned int v15; // ecx
  char *v16; // esi
  char v17; // dl
  char *v18; // edi
  char *v19; // esi
  int v20; // edx
  int v21; // ecx
  int v22; // eax
  int v23; // edx
  int v24; // esi
  int granularity; // eax
  bool v26; // cc
  int i; // eax
  int num; // edi
  int size; // eax
  int v30; // ecx
  XMLElement_t **list; // esi
  int j; // eax
  int v33; // [esp+10h] [ebp-10h]
  int v34; // [esp+10h] [ebp-10h]
  int v35; // [esp+10h] [ebp-10h]

  v9 = (XMLElement_t *)Memory::Allocate(0x70u);
  if ( v9 )
  {
    v9->source.len = 0;
    v9->source.alloced = 20;
    v9->source.data = v9->source.baseBuffer;
    v9->source.baseBuffer[0] = 0;
    v9->dest.len = 0;
    v9->dest.alloced = 20;
    v9->dest.data = v9->dest.baseBuffer;
    v9->dest.baseBuffer[0] = 0;
    v9->format.len = 0;
    v9->format.alloced = 20;
    v9->format.data = v9->format.baseBuffer;
    v9->format.baseBuffer[0] = 0;
    v10 = v9;
  }
  else
  {
    v10 = 0;
  }
  len = source.len;
  v33 = source.len;
  if ( source.len + 1 > v10->source.alloced )
    idStr::ReAllocate(&v10->source, source.len + 1, 0);
  qmemcpy(v10->source.data, source.data, len);
  v10->source.data[v33] = 0;
  v10->source.len = v33;
  v12 = dest.len;
  v34 = dest.len;
  if ( dest.len + 1 > v10->dest.alloced )
    idStr::ReAllocate(&v10->dest, dest.len + 1, 0);
  qmemcpy(v10->dest.data, dest.data, v12);
  v10->dest.data[v34] = 0;
  v10->dest.len = v34;
  v13 = format.len;
  v35 = format.len;
  if ( format.len + 1 > v10->format.alloced )
    idStr::ReAllocate(&v10->format, format.len + 1, 0);
  data = v10->format.data;
  v15 = v13;
  v16 = format.data;
  v17 = v15;
  v15 >>= 2;
  qmemcpy(data, format.data, 4 * v15);
  v19 = &v16[4 * v15];
  v18 = &data[4 * v15];
  LOBYTE(v15) = v17;
  v20 = numLevels;
  qmemcpy(v18, v19, v15 & 3);
  v10->format.data[v35] = 0;
  v21 = uploadHeight;
  v10->format.len = v35;
  v22 = uploadWidth;
  v10->numLevels = v20;
  v23 = cubeFlag;
  v10->uploadWidth = v22;
  v10->uploadHeight = v21;
  v10->cubeFlag = v23;
  v24 = 0;
  if ( this->XMLList.num <= 0 )
  {
LABEL_13:
    if ( !this->XMLList.list )
    {
      granularity = this->XMLList.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->XMLList.size )
        {
          v26 = granularity < this->XMLList.num;
          this->XMLList.size = granularity;
          if ( v26 )
            this->XMLList.num = granularity;
          this->XMLList.list = (XMLElement_t **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->XMLList.num; ++i )
            this->XMLList.list[i] = *(XMLElement_t **)(4 * i);
        }
      }
      else
      {
        this->XMLList.list = 0;
        this->XMLList.num = 0;
        this->XMLList.size = 0;
      }
    }
    num = this->XMLList.num;
    size = this->XMLList.size;
    if ( num == size )
    {
      if ( !this->XMLList.granularity )
        this->XMLList.granularity = 16;
      v30 = size + this->XMLList.granularity - (size + this->XMLList.granularity) % this->XMLList.granularity;
      if ( v30 > 0 )
      {
        if ( v30 != this->XMLList.size )
        {
          list = this->XMLList.list;
          this->XMLList.size = v30;
          if ( v30 < num )
            this->XMLList.num = v30;
          this->XMLList.list = (XMLElement_t **)Memory::Allocate(4 * v30);
          for ( j = 0; j < this->XMLList.num; ++j )
            this->XMLList.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->XMLList.list )
          Memory::Free(this->XMLList.list);
        this->XMLList.list = 0;
        this->XMLList.num = 0;
        this->XMLList.size = 0;
      }
    }
    this->XMLList.list[this->XMLList.num++] = v10;
  }
  else
  {
    while ( idStr::Cmp(this->XMLList.list[v24]->source.data, source.data) )
    {
      if ( ++v24 >= this->XMLList.num )
        goto LABEL_13;
    }
  }
  idStr::FreeData(&source);
  idStr::FreeData(&dest);
  idStr::FreeData(&format);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::PrintMemInfo(class MemInfo *)
void __thiscall idImageManagerLocal::PrintMemInfo(idImageManagerLocal *this, MemInfo *mi)
{
  idStr *v3; // eax
  idFileSystem_vtbl *v4; // edx
  idFile *v5; // ebp
  _DWORD *v6; // ebx
  int j; // eax
  int v8; // esi
  _DWORD *v9; // ecx
  idImage **list; // eax
  idImage **v11; // ebp
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // esi
  int v16; // ecx
  idImage **v17; // edx
  idImage *v18; // esi
  int v19; // eax
  idStr *v20; // eax
  idFile v21; // edx
  idStr *v22; // esi
  idStr *v23; // eax
  idFile_vtbl *v24; // ecx
  char *v25; // [esp-20h] [ebp-CCh]
  char *v26; // [esp-1Ch] [ebp-C8h]
  char *v27; // [esp-18h] [ebp-C4h]
  int refCount; // [esp-14h] [ebp-C0h]
  char *v29; // [esp-10h] [ebp-BCh]
  char *data; // [esp-Ch] [ebp-B8h]
  _DWORD *count; // [esp+Ch] [ebp-A0h]
  int counta; // [esp+Ch] [ebp-A0h]
  int i; // [esp+10h] [ebp-9Ch]
  int ia; // [esp+10h] [ebp-9Ch]
  int total; // [esp+14h] [ebp-98h]
  idFile *f; // [esp+18h] [ebp-94h]
  int v37; // [esp+1Ch] [ebp-90h]
  idStr v38; // [esp+20h] [ebp-8Ch] BYREF
  idStr v39; // [esp+40h] [ebp-6Ch] BYREF
  idStr result; // [esp+60h] [ebp-4Ch] BYREF
  idStr v41; // [esp+80h] [ebp-2Ch] BYREF
  int v42; // [esp+A8h] [ebp-4h]

  total = 0;
  v3 = operator+(&result, &mi->filebase, "_images.txt");
  v4 = fileSystem->__vftable;
  data = v3->data;
  v42 = 0;
  v5 = v4->OpenFileWrite(fileSystem, data, "fs_savepath", 0);
  f = v5;
  v42 = -1;
  idStr::FreeData(&result);
  if ( v5 )
  {
    v6 = Memory::Allocate(4 * this->images.num);
    for ( j = 0; j < this->images.num; ++j )
      v6[j] = j;
    if ( this->images.num - 1 > 0 )
    {
      v8 = 1;
      v9 = v6;
      i = 1;
      count = v6;
      do
      {
        if ( v8 < this->images.num )
        {
          do
          {
            list = this->images.list;
            v11 = &list[v6[v8]];
            v37 = idImage::StorageSize(list[*v9]);
            v12 = idImage::StorageSize(*v11);
            v9 = count;
            if ( v37 < v12 )
            {
              v13 = *count;
              *count = v6[v8];
              v6[v8] = v13;
            }
            ++v8;
          }
          while ( v8 < this->images.num );
          v5 = f;
          v8 = i;
        }
        ++v8;
        ++v9;
        i = v8;
        count = v9;
      }
      while ( v8 - 1 < this->images.num - 1 );
    }
    v14 = 0;
    v15 = 0;
    counta = 0;
    ia = 0;
    if ( this->images.num > 0 )
    {
      do
      {
        v16 = v6[v14];
        v17 = this->images.list;
        v18 = v17[v16];
        if ( v18->levelLoadReferenced )
        {
          v19 = idImage::StorageSize(v17[v16]);
          total += v19;
          ++counta;
          v20 = idStr::FormatNumber(&v38, v19);
          v21.__vftable = v5->__vftable;
          v29 = v18->imgName.data;
          refCount = v18->refCount;
          v27 = v20->data;
          v42 = 1;
          v21.Printf(v5, "%s %3i %s\n", v27, refCount, v29);
          v42 = -1;
          idStr::FreeData(&v38);
          v14 = ia;
        }
        ia = ++v14;
      }
      while ( v14 < this->images.num );
      v15 = counta;
    }
    Memory::Free(v6);
    mi->imageAssetsTotal = total;
    mi->imageAssetsCount = v15;
    v22 = idStr::FormatNumber(&v41, v15);
    v42 = 2;
    v23 = idStr::FormatNumber(&v39, total);
    v24 = v5->__vftable;
    v26 = v22->data;
    v25 = v23->data;
    LOBYTE(v42) = 3;
    v24->Printf(v5, "\nTotal image bytes allocated: %s (%s items)\n", v25, v26);
    LOBYTE(v42) = 2;
    idStr::FreeData(&v39);
    v42 = -1;
    idStr::FreeData(&v41);
    fileSystem->CloseFile(fileSystem, v5);
  }
}

// FUNC: void __cdecl R_ListImagesRaven_f(class idCmdArgs const &)
void __cdecl R_ListImagesRaven_f(idCmdArgs *args)
{
  int argc; // eax
  int v2; // esi
  const char **v3; // ebx
  const char *v4; // eax
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  const char *v10; // eax
  const char *v11; // eax
  const char *v12; // eax
  const char *v13; // eax
  const char *v14; // eax
  const char *v15; // eax
  const char *v16; // eax
  const char *v17; // eax
  const char *v18; // eax
  const char *v19; // eax
  idImageManager_vtbl *v20; // eax
  int v21; // eax
  void *v22; // esp
  idImageManager_vtbl *v23; // edx
  idImage *v24; // eax
  idImage *v25; // esi
  int internalFormat; // eax
  int v27; // eax
  int j; // edi
  idImage *v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // edi
  int k; // esi
  int v34; // esi
  idList<int> *v35; // esi
  int granularity; // eax
  bool v37; // cc
  int m; // eax
  int v39; // ebx
  int size; // ecx
  int v41; // ecx
  int *list; // edi
  int n; // eax
  sortedImage_t *v44; // ebx
  idList<int> *v45; // edi
  int ii; // esi
  idList<int> *v47; // edi
  int v48; // ebx
  int v49; // esi
  int v50; // eax
  int v51; // edi
  int jj; // esi
  sortedImage_t *v53; // edi
  int v54; // esi
  char *data; // edx
  char *v56; // ecx
  char v57; // al
  int v58; // esi
  char *v59; // edx
  char *v60; // ecx
  char v61; // al
  const idStr *v62; // eax
  idStr *v63; // esi
  unsigned int len; // ebx
  int v65; // eax
  idImage *image; // ecx
  int v67; // eax
  int v68; // edi
  const char *v69; // eax
  const char *v70; // esi
  int v71; // ebx
  char *v72; // edx
  char *v73; // ecx
  char v74; // al
  int v75; // esi
  int v76; // eax
  __int64 v77; // [esp+8h] [ebp-220h]
  int uploadHeight; // [esp+Ch] [ebp-21Ch]
  int uploadWidth; // [esp+Ch] [ebp-21Ch]
  _BYTE v80[12]; // [esp+10h] [ebp-218h] BYREF
  idList<int> classifications[17]; // [esp+1Ch] [ebp-20Ch] BYREF
  char v82[64]; // [esp+12Ch] [ebp-FCh] BYREF
  char string[64]; // [esp+16Ch] [ebp-BCh] BYREF
  idStr result; // [esp+1ACh] [ebp-7Ch] BYREF
  idStr v85; // [esp+1CCh] [ebp-5Ch] BYREF
  idStr stringValNext; // [esp+1ECh] [ebp-3Ch] BYREF
  idStr b; // [esp+20Ch] [ebp-1Ch] BYREF
  idStr a; // [esp+22Ch] [ebp+4h] BYREF
  idStr stringValCurr; // [esp+24Ch] [ebp+24h] BYREF
  int totalSize; // [esp+26Ch] [ebp+44h]
  sortedImage_t *sortedArray; // [esp+270h] [ebp+48h]
  int partialSize; // [esp+274h] [ebp+4Ch]
  int num; // [esp+278h] [ebp+50h]
  bool unloaded; // [esp+27Eh] [ebp+56h]
  bool overSized; // [esp+27Fh] [ebp+57h]
  bool uncompressedOnly; // [esp+280h] [ebp+58h]
  bool partial; // [esp+281h] [ebp+59h]
  bool touched; // [esp+282h] [ebp+5Ah]
  bool uncached; // [esp+283h] [ebp+5Bh]
  bool cached; // [esp+284h] [ebp+5Ch]
  bool inview; // [esp+285h] [ebp+5Dh]
  bool duplicated; // [esp+286h] [ebp+5Eh]
  bool brief; // [esp+287h] [ebp+5Fh]
  int count; // [esp+288h] [ebp+60h]
  bool sortByDimensions; // [esp+28Ch] [ebp+64h]
  bool sortByClassification; // [esp+28Dh] [ebp+65h]
  bool sortByMemorySize; // [esp+28Eh] [ebp+66h]
  bool failed; // [esp+28Fh] [ebp+67h]
  int v109; // [esp+298h] [ebp+70h]
  int i; // [esp+2A4h] [ebp+7Ch]
  int ia; // [esp+2A4h] [ebp+7Ch]
  int ib; // [esp+2A4h] [ebp+7Ch]
  const char **ic; // [esp+2A4h] [ebp+7Ch]
  int id; // [esp+2A4h] [ebp+7Ch]

  count = 0;
  brief = 0;
  uncompressedOnly = 0;
  partial = 0;
  unloaded = 0;
  cached = 0;
  uncached = 0;
  num = 0;
  duplicated = 0;
  touched = 0;
  overSized = 0;
  inview = 0;
  failed = 0;
  sortByClassification = 0;
  sortByMemorySize = 0;
  sortByDimensions = 0;
  argc = args->argc;
  v2 = 1;
  if ( args->argc <= 1 )
    goto LABEL_85;
  v3 = (const char **)&args->argv[1];
  while ( !failed )
  {
    if ( v2 < 0 || v2 >= argc )
      v4 = &entityFilter;
    else
      v4 = *v3;
    if ( idStr::Icmp(v4, "brief") )
    {
      if ( v2 < 0 || v2 >= args->argc )
        v5 = &entityFilter;
      else
        v5 = *v3;
      if ( idStr::Icmp(v5, "only") )
      {
        if ( v2 < 0 || v2 >= args->argc )
          v16 = &entityFilter;
        else
          v16 = *v3;
        if ( idStr::Icmp(v16, "sort") )
        {
LABEL_82:
          failed = 1;
          goto LABEL_83;
        }
        ++v2;
        ++v3;
        if ( v2 < 0 || v2 >= args->argc )
          v17 = &entityFilter;
        else
          v17 = *v3;
        if ( idStr::Icmp(v17, "memsize") )
        {
          if ( v2 < 0 || v2 >= args->argc )
            v18 = &entityFilter;
          else
            v18 = *v3;
          if ( idStr::Icmp(v18, "dims") )
          {
            if ( v2 < 0 || v2 >= args->argc )
              v19 = &entityFilter;
            else
              v19 = *v3;
            if ( idStr::Icmp(v19, "class") )
              goto LABEL_82;
            sortByClassification = 1;
          }
          else
          {
            sortByDimensions = 1;
          }
        }
        else
        {
          sortByMemorySize = 1;
        }
      }
      else
      {
        ++v2;
        ++v3;
        if ( v2 < 0 || v2 >= args->argc )
          v6 = &entityFilter;
        else
          v6 = *v3;
        if ( idStr::Icmp(v6, "uncompressed") )
        {
          if ( v2 < 0 || v2 >= args->argc )
            v7 = &entityFilter;
          else
            v7 = *v3;
          if ( idStr::Icmp(v7, "partial") )
          {
            if ( v2 < 0 || v2 >= args->argc )
              v8 = &entityFilter;
            else
              v8 = *v3;
            if ( idStr::Icmp(v8, "unloaded") )
            {
              if ( v2 < 0 || v2 >= args->argc )
                v9 = &entityFilter;
              else
                v9 = *v3;
              if ( idStr::Icmp(v9, "cached") )
              {
                if ( v2 < 0 || v2 >= args->argc )
                  v10 = &entityFilter;
                else
                  v10 = *v3;
                if ( idStr::Icmp(v10, "uncached") )
                {
                  if ( v2 < 0 || v2 >= args->argc )
                    v11 = &entityFilter;
                  else
                    v11 = *v3;
                  if ( idStr::Icmp(v11, "tagged") )
                  {
                    v12 = idCmdArgs::Argv(args, v2);
                    if ( idStr::Icmp(v12, "duplicated") )
                    {
                      v13 = idCmdArgs::Argv(args, v2);
                      if ( idStr::Icmp(v13, "touched") )
                      {
                        v14 = idCmdArgs::Argv(args, v2);
                        if ( idStr::Icmp(v14, "oversized") )
                        {
                          v15 = idCmdArgs::Argv(args, v2);
                          if ( idStr::Icmp(v15, "inview") )
                            goto LABEL_82;
                          inview = 1;
                        }
                        else
                        {
                          overSized = 1;
                        }
                      }
                      else
                      {
                        touched = 1;
                      }
                    }
                    else
                    {
                      duplicated = 1;
                    }
                  }
                  else
                  {
                    num = 1;
                  }
                }
                else
                {
                  uncached = 1;
                }
              }
              else
              {
                cached = 1;
              }
            }
            else
            {
              unloaded = 1;
            }
          }
          else
          {
            partial = 1;
          }
        }
        else
        {
          uncompressedOnly = 1;
        }
      }
    }
    else
    {
      brief = 1;
    }
LABEL_83:
    argc = args->argc;
    ++v2;
    ++v3;
    if ( v2 >= args->argc )
      break;
  }
  if ( !sortByMemorySize )
  {
LABEL_85:
    if ( !sortByDimensions && !sortByClassification )
      sortByMemorySize = 1;
  }
  if ( failed )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: listImagesRaven [ brief ] [ only < uncompressed | partial | unloaded | cached | uncached | tagged | duplica"
      "ted | touched | oversized | inview > ] [ sort < memsize | dims | class > ] \n");
    return;
  }
  v20 = globalImages->__vftable;
  totalSize = 0;
  v21 = 8 * v20->GetNumImages(globalImages) + 3;
  LOBYTE(v21) = v21 & 0xFC;
  v22 = alloca(v21);
  v23 = globalImages->__vftable;
  sortedArray = (sortedImage_t *)v80;
  i = 0;
  if ( v23->GetNumImages(globalImages) > 0 )
  {
    while ( 2 )
    {
      v24 = globalImages->GetImageByIndex(globalImages, i);
      v25 = v24;
      if ( !uncompressedOnly
        || ((internalFormat = v24->internalFormat, internalFormat < 33776) || internalFormat > 33779)
        && internalFormat != 32997 )
      {
        if ( (!num || v25->classification == num)
          && (!unloaded || v25->texnum == -1)
          && (!partial || v25->isPartialImage)
          && (!cached || v25->partialImage && v25->texnum != -1)
          && (!uncached || v25->partialImage && v25->texnum == -1) )
        {
          if ( !overSized
            || (v27 = ClassifyImage(v25->imgName.data), v25->uploadWidth >= IC_Info[v27].maxWidth)
            || v25->uploadHeight >= IC_Info[v27].maxHeight )
          {
            if ( !inview || v25->frameUsed == backEnd.frameCount )
            {
              if ( !duplicated )
                goto LABEL_116;
              for ( j = i + 1; j < globalImages->GetNumImages(globalImages); ++j )
              {
                v29 = globalImages->GetImageByIndex(globalImages, j);
                if ( !idStr::Icmp(v25->imgName.data, v29->imgName.data) )
                  break;
              }
              if ( j != globalImages->GetNumImages(globalImages) )
              {
LABEL_116:
                if ( !touched )
                  goto LABEL_119;
                if ( v25->bindCount )
                {
                  v25->bindCount = 0;
LABEL_119:
                  *(_DWORD *)&v80[8 * count] = v25;
                  v30 = idImage::StorageSize(v25);
                  *(_DWORD *)&v80[8 * count + 4] = v30;
                  v31 = idImage::StorageSize(v25);
                  totalSize += v31;
                  ++count;
                }
              }
            }
          }
        }
      }
      if ( ++i >= globalImages->GetNumImages(globalImages) )
        break;
      continue;
    }
  }
  if ( !brief )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "\n%s",
      "       -w-- -h-- filt -fmt-- wrap  size --name-------\n");
    if ( sortByMemorySize )
    {
      v32 = count;
      qsort(v80, count, 8u, (int (__cdecl *)(const void *, const void *))R_QsortImageSizes);
      for ( k = 0; k < v32; ++k )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%4i:", k);
        idImage::Print(*(idImage **)&v80[8 * k]);
      }
    }
    else if ( sortByClassification )
    {
      v34 = count;
      qsort(v80, count, 8u, (int (__cdecl *)(const void *, const void *))R_QsortImageSizes);
      `eh vector constructor iterator'(
        (char *)classifications,
        0x10u,
        17,
        (void (__thiscall *)(void *))idList<rvServerScanGUI *>::`default constructor closure',
        (void (__thiscall *)(void *))idList<idDeclFolder *>::~idList<idDeclFolder *>);
      v109 = 0;
      ia = 0;
      if ( v34 > 0 )
      {
        do
        {
          v35 = &classifications[ClassifyImage(sortedArray[ia].image->imgName.data)];
          if ( !v35->list )
          {
            granularity = v35->granularity;
            if ( granularity > 0 )
            {
              if ( granularity != v35->size )
              {
                v37 = granularity < v35->num;
                v35->size = granularity;
                if ( v37 )
                  v35->num = granularity;
                v35->list = (int *)Memory::Allocate(4 * granularity);
                for ( m = 0; m < v35->num; ++m )
                  v35->list[m] = *(_DWORD *)(4 * m);
              }
            }
            else
            {
              v35->list = 0;
              v35->num = 0;
              v35->size = 0;
            }
          }
          v39 = v35->num;
          size = v35->size;
          if ( v35->num == size )
          {
            if ( !v35->granularity )
              v35->granularity = 16;
            v41 = v35->granularity + size - (v35->granularity + size) % v35->granularity;
            if ( v41 > 0 )
            {
              if ( v41 != v35->size )
              {
                list = v35->list;
                v35->size = v41;
                if ( v41 < v39 )
                  v35->num = v41;
                v35->list = (int *)Memory::Allocate(4 * v41);
                for ( n = 0; n < v35->num; ++n )
                  v35->list[n] = list[n];
                if ( list )
                  Memory::Free(list);
              }
            }
            else
            {
              if ( v35->list )
                Memory::Free(v35->list);
              v35->list = 0;
              v35->num = 0;
              v35->size = 0;
            }
          }
          v35->list[v35->num++] = ia++;
        }
        while ( ia < count );
      }
      v44 = sortedArray;
      v45 = classifications;
      ib = 17;
      do
      {
        for ( ii = 0; ii < v45->num; ++ii )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "%4i:",
            v45->list[ii]);
          idImage::Print(v44[v45->list[ii]].image);
        }
        ++v45;
        --ib;
      }
      while ( ib );
      ic = &IC_Info[0].desc;
      v47 = classifications;
      do
      {
        if ( v47->num > 0 )
        {
          v48 = 0;
          v49 = 0;
          partialSize = 0;
          do
          {
            v50 = idImage::StorageSize(sortedArray[v47->list[v49++]].image);
            v48 += v50;
          }
          while ( v49 < v47->num );
          partialSize = v48;
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            " Classification %s contains %i images using %5.1f megabytes\n",
            *ic,
            v47->num,
            (double)v48 * 0.00000095367431640625);
        }
        ++v47;
        ic += 5;
      }
      while ( (int)ic < (int)&DEEP_RANGE );
      v109 = -1;
      `eh vector destructor iterator'(
        (char *)classifications,
        0x10u,
        17,
        (void (__thiscall *)(void *))idList<idDeclFolder *>::~idList<idDeclFolder *>);
    }
    else if ( sortByDimensions )
    {
      v51 = count;
      qsort(v80, count, 8u, (int (__cdecl *)(const void *, const void *))R_QsortImageWidthTimesHeight);
      for ( jj = 0; jj < v51; ++jj )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%4i:", jj);
        idImage::Print(*(idImage **)&v80[8 * jj]);
      }
      stringValCurr.len = 0;
      stringValCurr.alloced = 20;
      stringValCurr.data = stringValCurr.baseBuffer;
      stringValCurr.baseBuffer[0] = 0;
      v109 = 1;
      num = 0;
      partialSize = 0;
      id = 0;
      if ( v51 > 0 )
      {
        do
        {
          v53 = sortedArray;
          uploadHeight = sortedArray[id].image->uploadHeight;
          b.len = 0;
          b.alloced = 20;
          b.data = b.baseBuffer;
          b.baseBuffer[0] = 0;
          v54 = sprintf(string, "%d", uploadHeight);
          if ( v54 + 1 > b.alloced )
            idStr::ReAllocate(&b, v54 + 1, 1);
          data = b.data;
          v56 = string;
          do
          {
            v57 = *v56;
            *data++ = *v56++;
          }
          while ( v57 );
          b.len = v54;
          uploadWidth = v53[id].image->uploadWidth;
          LOBYTE(v109) = 2;
          a.len = 0;
          a.alloced = 20;
          a.data = a.baseBuffer;
          a.baseBuffer[0] = 0;
          v58 = sprintf(v82, "%d", uploadWidth);
          if ( v58 + 1 > a.alloced )
            idStr::ReAllocate(&a, v58 + 1, 1);
          v59 = a.data;
          v60 = v82;
          do
          {
            v61 = *v60;
            *v59++ = *v60++;
          }
          while ( v61 );
          a.len = v58;
          LOBYTE(v109) = 3;
          v62 = operator+(&result, &a, "x");
          LOBYTE(v109) = 4;
          v63 = operator+(&v85, v62, &b);
          len = v63->len;
          v65 = v63->len + 1;
          LOBYTE(v109) = 5;
          if ( v65 > stringValCurr.alloced )
            idStr::ReAllocate(&stringValCurr, v65, 0);
          qmemcpy(stringValCurr.data, v63->data, len);
          stringValCurr.data[len] = 0;
          stringValCurr.len = len;
          LOBYTE(v109) = 4;
          idStr::FreeData(&v85);
          LOBYTE(v109) = 3;
          idStr::FreeData(&result);
          LOBYTE(v109) = 2;
          idStr::FreeData(&a);
          LOBYTE(v109) = 1;
          idStr::FreeData(&b);
          image = sortedArray[id].image;
          ++num;
          v67 = idImage::StorageSize(image);
          partialSize += v67;
          v68 = id + 1;
          if ( id + 1 < count )
          {
            v77 = *(_QWORD *)&sortedArray[id + 1].image->uploadWidth;
            v69 = va("%dx%d", (_DWORD)v77, HIDWORD(v77));
            v70 = v69;
            stringValNext.len = 0;
            stringValNext.alloced = 20;
            stringValNext.data = stringValNext.baseBuffer;
            stringValNext.baseBuffer[0] = 0;
            if ( v69 )
            {
              v71 = strlen(v69);
              if ( v71 + 1 > 20 )
                idStr::ReAllocate(&stringValNext, v71 + 1, 1);
              v72 = stringValNext.data;
              v73 = (char *)v70;
              do
              {
                v74 = *v73;
                *v72++ = *v73++;
              }
              while ( v74 );
              stringValNext.len = v71;
            }
            LOBYTE(v109) = 6;
            if ( idStr::Cmp(stringValCurr.data, stringValNext.data) )
            {
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                common.type,
                " %10s : %4i images @ %5.1f megabytes\n",
                stringValCurr.data,
                num,
                (double)partialSize * 0.00000095367431640625);
              num = 0;
              partialSize = 0;
            }
            LOBYTE(v109) = 1;
            idStr::FreeData(&stringValNext);
          }
          ++id;
        }
        while ( v68 < count );
        if ( num > 0 )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            " %10s : %4i images @ %5.1f megabytes\n",
            stringValCurr.data,
            num,
            (double)partialSize * 0.00000095367431640625);
      }
      v109 = -1;
      idStr::FreeData(&stringValCurr);
    }
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
  v75 = *(_DWORD *)common.type;
  v76 = globalImages->GetNumImages(globalImages);
  (*(void (**)(netadrtype_t, const char *, ...))(v75 + 124))(common.type, " %i images (of %i total)\n", count, v76);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " %5.1f total megabytes of images\n\n\n",
    (double)totalSize * 0.00000095367431640625);
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::AllocImage(char const *)
idImage *__thiscall idImageManagerLocal::AllocImage(idImageManagerLocal *this, char *name)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  const char *v4; // eax
  int v5; // ebp
  int v6; // eax
  char *data; // edx
  char *v8; // ecx
  char v9; // al
  idImage *v10; // eax
  char *v11; // ecx
  idImage *v12; // edi
  int granularity; // eax
  bool v14; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v18; // ecx
  idImage **list; // edi
  int j; // eax
  idImage *v22; // [esp+0h] [ebp-34h]
  int hash; // [esp+4h] [ebp-30h]
  idStr v24; // [esp+8h] [ebp-2Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v25; // [esp+28h] [ebp-Ch]
  void *v26; // [esp+2Ch] [ebp-8h]
  int v27; // [esp+30h] [ebp-4h]

  v27 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v26 = &_ehhandler__ImageFromFile_idImageManagerLocal__UAEPAVidImage__PBDW4textureFilter_t___NW4textureRepeat_t__W4textureDepth_t__W4cubeFiles_t__H_Z;
  v25 = ExceptionList;
  if ( strlen(name) >= 0x100 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idImageManagerLocal::AllocImage: \"%s\" is too long\n",
      name);
  v24.len = 0;
  v24.alloced = 20;
  v24.data = v24.baseBuffer;
  v24.baseBuffer[0] = 0;
  if ( name )
  {
    v4 = &name[strlen(name) + 1];
    v5 = v4 - (name + 1);
    v6 = v4 - name;
    if ( v6 > 20 )
      idStr::ReAllocate(&v24, v6, 1);
    data = v24.data;
    v8 = name;
    do
    {
      v9 = *v8;
      *data++ = *v8++;
    }
    while ( v9 );
    v24.len = v5;
  }
  v27 = 0;
  hash = idStr::FileNameHash(&v24);
  v27 = -1;
  idStr::FreeData(&v24);
  v10 = (idImage *)Memory::Allocate(0x4E8u);
  if ( v10 )
  {
    v10->__vftable = (idImage_vtbl *)&idImage::`vftable';
    v10->bgl.url.url.len = 0;
    v10->bgl.url.url.alloced = 20;
    v10->bgl.url.url.data = v10->bgl.url.url.baseBuffer;
    v10->bgl.url.url.baseBuffer[0] = 0;
    v10->imgName.len = 0;
    v10->imgName.alloced = 20;
    v10->imgName.data = v10->imgName.baseBuffer;
    v10->imgName.baseBuffer[0] = 0;
    v11 = v10->imgName.data;
    v10->texnum = -1;
    v10->partialImage = 0;
    v10->type = TT_DISABLED;
    v10->isPartialImage = 0;
    v10->frameUsed = 0;
    v10->classification = 0;
    v10->backgroundLoadInProgress = 0;
    v10->bgl.opcode = DLTYPE_FILE;
    v10->bgl.f = 0;
    v10->bglNext = 0;
    *v11 = 0;
    v12 = v10;
    v10->generatorFunction = 0;
    v10->allowDownSize = 0;
    v10->filter = TF_DEFAULT;
    v10->repeat = TR_REPEAT;
    v10->depth = TD_DEFAULT;
    v10->cubeFiles = CF_2D;
    v10->referencedOutsideLevelLoad = 0;
    v10->levelLoadReferenced = 0;
    v10->precompressedFile = 0;
    v10->defaulted = 0;
    v10->timestamp = 0;
    v10->bindCount = 0;
    v10->uploadDepth = 0;
    v10->uploadHeight = 0;
    v10->uploadWidth = 0;
    v10->internalFormat = 0;
    v10->cacheUsageNext = 0;
    v10->cacheUsagePrev = 0;
    v10->hashNext = 0;
    v10->isMonochrome = 0;
    v10->refCount = 0;
    v10->cubeFaceBound = 0;
    v10->flags = 0;
    v10->useCount = 0;
    v22 = v10;
  }
  else
  {
    v22 = 0;
    v12 = 0;
  }
  if ( !this->images.list )
  {
    granularity = this->images.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->images.size )
      {
        v14 = granularity < this->images.num;
        this->images.size = granularity;
        if ( v14 )
          this->images.num = granularity;
        this->images.list = (idImage **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->images.num; ++i )
          this->images.list[i] = *(idImage **)(4 * i);
      }
    }
    else
    {
      this->images.list = 0;
      this->images.num = 0;
      this->images.size = 0;
    }
  }
  num = this->images.num;
  size = this->images.size;
  if ( num == size )
  {
    if ( !this->images.granularity )
      this->images.granularity = 16;
    v18 = size + this->images.granularity - (size + this->images.granularity) % this->images.granularity;
    if ( v18 > 0 )
    {
      if ( v18 != this->images.size )
      {
        list = this->images.list;
        this->images.size = v18;
        if ( v18 < num )
          this->images.num = v18;
        this->images.list = (idImage **)Memory::Allocate(4 * v18);
        for ( j = 0; j < this->images.num; ++j )
          this->images.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->images.list )
        Memory::Free(this->images.list);
      this->images.list = 0;
      this->images.num = 0;
      this->images.size = 0;
    }
    v12 = v22;
  }
  this->images.list[this->images.num++] = v12;
  v12->hashNext = this->imageHashTable[hash];
  this->imageHashTable[hash] = v12;
  idStr::operator=(&v12->imgName, name);
  return v12;
}

// FUNC: public: virtual class idPBufferImage * __thiscall idImageManagerLocal::AllocPBufferImage(char const *)
idPBufferImage *__thiscall idImageManagerLocal::AllocPBufferImage(idImageManagerLocal *this, char *name)
{
  int v3; // eax
  idImage *v4; // edi
  idImage *v5; // eax
  char *data; // ecx
  idImage *v7; // edi
  int granularity; // eax
  bool v9; // cc
  int i; // eax
  int size; // eax
  int v12; // ecx
  idImage **list; // ebp
  int j; // eax
  rvTexRenderTarget *v15; // eax
  idImage *v16; // esi
  idImage_vtbl *v17; // eax
  int hash; // [esp+10h] [ebp-34h]
  idStr fileName; // [esp+18h] [ebp-2Ch] BYREF
  int v21; // [esp+40h] [ebp-4h]

  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  v21 = 0;
  if ( strlen(name) >= 0x100 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "idImageManagerLocal::idPBufferImage: \"%s\" is too long\n",
      name);
  idStr::operator=(&fileName, name);
  v3 = idStr::FileNameHash(&fileName);
  v4 = this->imageHashTable[v3];
  hash = v3;
  if ( v4 )
  {
    while ( idStr::Icmp(fileName.data, v4->imgName.data) )
    {
      v4 = v4->hashNext;
      if ( !v4 )
        goto LABEL_6;
    }
    v16 = (idImage *)__RTDynamicCast(v4, 0, &idImage `RTTI Type Descriptor', &idPBufferImage `RTTI Type Descriptor', 0);
    if ( !v16 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
        common.type,
        "Trying to attach a pbuffer to an existing image '%s'",
        name);
  }
  else
  {
LABEL_6:
    v5 = (idImage *)Memory::Allocate(0x4ECu);
    if ( v5 )
    {
      v5->bgl.url.url.len = 0;
      v5->bgl.url.url.alloced = 20;
      v5->bgl.url.url.data = v5->bgl.url.url.baseBuffer;
      v5->bgl.url.url.baseBuffer[0] = 0;
      v5->imgName.len = 0;
      v5->imgName.alloced = 20;
      v5->imgName.data = v5->imgName.baseBuffer;
      v5->imgName.baseBuffer[0] = 0;
      data = v5->imgName.data;
      v5->texnum = -1;
      v5->partialImage = 0;
      v5->type = TT_DISABLED;
      v5->isPartialImage = 0;
      v5->frameUsed = 0;
      v5->classification = 0;
      v5->backgroundLoadInProgress = 0;
      v5->bgl.opcode = DLTYPE_FILE;
      v5->bgl.f = 0;
      v5->bglNext = 0;
      *data = 0;
      v5->generatorFunction = 0;
      v5->allowDownSize = 0;
      v5->filter = TF_DEFAULT;
      v5->repeat = TR_REPEAT;
      v5->depth = TD_DEFAULT;
      v5->cubeFiles = CF_2D;
      v5->referencedOutsideLevelLoad = 0;
      v5->levelLoadReferenced = 0;
      v5->precompressedFile = 0;
      v5->defaulted = 0;
      v5->timestamp = 0;
      v5->bindCount = 0;
      v5->uploadDepth = 0;
      v5->uploadHeight = 0;
      v5->uploadWidth = 0;
      v5->internalFormat = 0;
      v5->cacheUsageNext = 0;
      v5->cacheUsagePrev = 0;
      v5->hashNext = 0;
      v5->isMonochrome = 0;
      v5->refCount = 0;
      v5->cubeFaceBound = 0;
      v5->flags = 0;
      v5->useCount = 0;
      v5->__vftable = (idImage_vtbl *)&idPBufferImage::`vftable';
      v5[1].__vftable = 0;
      v7 = v5;
    }
    else
    {
      v7 = 0;
    }
    if ( !this->images.list )
    {
      granularity = this->images.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->images.size )
        {
          v9 = granularity < this->images.num;
          this->images.size = granularity;
          if ( v9 )
            this->images.num = granularity;
          this->images.list = (idImage **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->images.num; ++i )
            this->images.list[i] = *(idImage **)(4 * i);
        }
      }
      else
      {
        this->images.list = 0;
        this->images.num = 0;
        this->images.size = 0;
      }
    }
    size = this->images.size;
    if ( this->images.num == size )
    {
      if ( !this->images.granularity )
        this->images.granularity = 16;
      v12 = size + this->images.granularity - (size + this->images.granularity) % this->images.granularity;
      if ( v12 > 0 )
      {
        if ( v12 != this->images.size )
        {
          v9 = v12 < this->images.num;
          list = this->images.list;
          this->images.size = v12;
          if ( v9 )
            this->images.num = v12;
          this->images.list = (idImage **)Memory::Allocate(4 * v12);
          for ( j = 0; j < this->images.num; ++j )
            this->images.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->images.list )
          Memory::Free(this->images.list);
        this->images.list = 0;
        this->images.num = 0;
        this->images.size = 0;
      }
    }
    this->images.list[this->images.num++] = v7;
    v7->hashNext = this->imageHashTable[hash];
    this->imageHashTable[hash] = v7;
    idStr::operator=(&v7->imgName, name);
    qglGenTextures(1, &v7->texnum);
    v15 = (rvTexRenderTarget *)Memory::Allocate(0x3Cu);
    LOBYTE(v21) = 1;
    if ( v15 )
    {
      rvTexRenderTarget::rvTexRenderTarget(v15);
      v16 = v7;
      v7[1].__vftable = v17;
    }
    else
    {
      v16 = v7;
      v7[1].__vftable = 0;
    }
  }
  v21 = -1;
  idStr::FreeData(&fileName);
  return (idPBufferImage *)v16;
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::ImageFromFile(char const *,enum textureFilter_t,bool,enum textureRepeat_t,enum textureDepth_t,enum cubeFiles_t,int)
idImage *__thiscall idImageManagerLocal::ImageFromFile(
        idImageManagerLocal *this,
        char *_name,
        textureFilter_t filter,
        char allowDownSize,
        textureRepeat_t repeat,
        textureDepth_t depth,
        cubeFiles_t cubeMap,
        int flags)
{
  idImage *v9; // esi
  int integerValue; // eax
  idImage *quickLoadImage; // ebp
  char v13; // cl
  char v14; // al
  textureDepth_t v15; // edi
  idImage *partialImage; // eax
  textureDepth_t v17; // ebp
  idImage *v18; // eax
  idImage *v19; // eax
  char *data; // edx
  idImage *defaultImage; // ebp
  idStr name; // [esp+10h] [ebp-2Ch] BYREF
  int v24; // [esp+38h] [ebp-4h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v24 = 0;
  if ( _name
    && *_name
    && idStr::Icmp(_name, "default")
    && idStr::Icmp(_name, "_default")
    && idStr::Icmp(_name, "_emptyName") )
  {
    idStr::operator=(&name, _name);
    idStr::Replace(&name, ".tga", &entityFilter);
    idStr::BackSlashesToSlashes(&name);
    v9 = this->imageHashTable[idStr::FileNameHash(&name)];
    if ( v9 )
    {
      while ( 1 )
      {
        if ( !idStr::Icmp(name.data, v9->imgName.data) )
        {
          if ( *name.data == 95 )
            goto LABEL_28;
          if ( v9->cubeFiles != cubeMap )
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
              common.type,
              "Image '%s' has been referenced with conflicting cube map states",
              _name);
          if ( v9->filter == filter && v9->repeat == repeat && v9->flags == flags )
            break;
        }
        v9 = v9->hashNext;
        if ( !v9 )
          goto LABEL_15;
      }
      v13 = v9->allowDownSize;
      v14 = allowDownSize;
      v15 = depth;
      if ( v13 == allowDownSize && v9->depth == depth )
        goto LABEL_26;
      if ( !v13 )
        v14 = 0;
      v17 = v9->depth;
      if ( v17 > depth )
        v15 = v9->depth;
      if ( v13 == v14 && v17 == v15 )
      {
LABEL_26:
        partialImage = v9->partialImage;
        v9->levelLoadReferenced = 1;
        if ( partialImage )
          partialImage->levelLoadReferenced = 1;
      }
      else
      {
        v9->allowDownSize = v14;
        v18 = v9->partialImage;
        v9->depth = v15;
        v9->levelLoadReferenced = 1;
        if ( v18 )
          v18->levelLoadReferenced = 1;
        if ( image_preload.internalVar->integerValue && !this->insideLevelLoad )
        {
          v9->referencedOutsideLevelLoad = 1;
          idImage::ActuallyLoadImage(v9, 1, 0);
        }
      }
      goto LABEL_28;
    }
LABEL_15:
    integerValue = com_QuickLoad.internalVar->integerValue;
    if ( ((integerValue == 1 || integerValue == 2) && allowDownSize
       || this->quickLoadImage && idAsyncNetwork::serverDedicated.internalVar->integerValue)
      && (idStr::Icmpn(_name, "gfx/", 4) && idStr::Icmpn(_name, "fonts/", 6) || !idStr::Icmpn(_name, "gfx/env/", 7)) )
    {
      this->quickLoadImage->levelLoadReferenced = 1;
      gWriteProgramFlag = 0;
      quickLoadImage = this->quickLoadImage;
      v24 = -1;
      idStr::FreeData(&name);
      return quickLoadImage;
    }
    v9 = this->AllocImage(this, name.data);
    if ( idStr::FindText(name.data, "fontimage_", 1, 0, name.len) >= 0 )
      allowDownSize = 0;
    v9->repeat = repeat;
    v9->allowDownSize = allowDownSize;
    v9->flags = flags;
    v9->depth = depth;
    v9->type = TT_2D;
    v9->cubeFiles = cubeMap;
    v9->filter = filter;
    v9->levelLoadReferenced = 1;
    if ( idImage::ShouldImageBePartialCached(v9) )
    {
      v19 = (idImage *)Memory::Allocate(0x4E8u);
      if ( v19 )
      {
        v19->__vftable = (idImage_vtbl *)&idImage::`vftable';
        v19->bgl.url.url.len = 0;
        v19->bgl.url.url.alloced = 20;
        v19->bgl.url.url.data = v19->bgl.url.url.baseBuffer;
        v19->bgl.url.url.baseBuffer[0] = 0;
        v19->imgName.len = 0;
        v19->imgName.alloced = 20;
        v19->imgName.data = v19->imgName.baseBuffer;
        v19->imgName.baseBuffer[0] = 0;
        data = v19->imgName.data;
        v19->texnum = -1;
        v19->partialImage = 0;
        v19->type = TT_DISABLED;
        v19->isPartialImage = 0;
        v19->frameUsed = 0;
        v19->classification = 0;
        v19->backgroundLoadInProgress = 0;
        v19->bgl.opcode = DLTYPE_FILE;
        v19->bgl.f = 0;
        v19->bglNext = 0;
        *data = 0;
        v19->generatorFunction = 0;
        v19->allowDownSize = 0;
        v19->filter = TF_DEFAULT;
        v19->repeat = TR_REPEAT;
        v19->depth = TD_DEFAULT;
        v19->cubeFiles = CF_2D;
        v19->referencedOutsideLevelLoad = 0;
        v19->levelLoadReferenced = 0;
        v19->precompressedFile = 0;
        v19->defaulted = 0;
        v19->timestamp = 0;
        v19->bindCount = 0;
        v19->uploadDepth = 0;
        v19->uploadHeight = 0;
        v19->uploadWidth = 0;
        v19->internalFormat = 0;
        v19->cacheUsageNext = 0;
        v19->cacheUsagePrev = 0;
        v19->hashNext = 0;
        v19->isMonochrome = 0;
        v19->refCount = 0;
        v19->cubeFaceBound = 0;
        v19->flags = 0;
        v19->useCount = 0;
      }
      else
      {
        v19 = 0;
      }
      v9->partialImage = v19;
      v19->allowDownSize = allowDownSize;
      v9->partialImage->repeat = repeat;
      v9->partialImage->depth = depth;
      v9->partialImage->type = TT_2D;
      v9->partialImage->cubeFiles = cubeMap;
      v9->partialImage->filter = filter;
      v9->partialImage->levelLoadReferenced = 1;
      globalImages->AppendImage(globalImages, v9->partialImage);
      v9->partialImage->isPartialImage = 1;
      idStr::operator=(&v9->partialImage->imgName, "_black");
      v9->partialImage->generatorFunction = this->blackImage->generatorFunction;
      v9->precompressedFile = 1;
      if ( image_preload.internalVar->integerValue && !this->insideLevelLoad )
      {
        idImage::ActuallyLoadImage(v9->partialImage, 1, 0);
        declManager->MediaPrint(
          declManager,
          "%ix%i %s\n",
          v9->partialImage->uploadWidth,
          v9->partialImage->uploadHeight,
          v9->imgName.data);
LABEL_28:
        gWriteProgramFlag = 0;
        v24 = -1;
        idStr::FreeData(&name);
        return v9;
      }
    }
    else if ( image_preload.internalVar->integerValue && !this->insideLevelLoad )
    {
      v9->referencedOutsideLevelLoad = 1;
      idImage::ActuallyLoadImage(v9, 1, 0);
      declManager->MediaPrint(declManager, "%ix%i %s\n", v9->uploadWidth, v9->uploadHeight, v9->imgName.data);
      goto LABEL_28;
    }
    declManager->MediaPrint(declManager, "%s\n", v9->imgName.data);
    goto LABEL_28;
  }
  declManager->MediaPrint(declManager, "DEFAULTED\n");
  gWriteProgramFlag = 0;
  defaultImage = this->defaultImage;
  v24 = -1;
  idStr::FreeData(&name);
  return defaultImage;
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::Init(void)
void __thiscall idImageManagerLocal::Init(idImageManagerLocal *this)
{
  bool v2; // cc
  idImage **list; // edi
  int i; // eax
  idImage *v5; // eax
  idImageManagerLocal_vtbl *v6; // edx
  idImage *v7; // eax
  idImageManagerLocal_vtbl *v8; // edx
  idImage *v9; // eax
  idImageManagerLocal_vtbl *v10; // edx
  idImage *v11; // eax
  idImageManagerLocal_vtbl *v12; // edx
  idImage *v13; // eax
  idImageManagerLocal_vtbl *v14; // edx
  idImage *v15; // eax
  idImageManagerLocal_vtbl *v16; // edx
  idImage *v17; // eax
  idImageManagerLocal_vtbl *v18; // edx
  idImage *v19; // eax
  idImageManagerLocal_vtbl *v20; // edx
  idImage *v21; // eax
  idImageManagerLocal_vtbl *v22; // edx
  idImage *v23; // eax
  idImageManagerLocal_vtbl *v24; // edx
  idImage *v25; // eax
  idImageManagerLocal_vtbl *v26; // edx
  idImage *v27; // eax
  idImageManagerLocal_vtbl *v28; // edx
  idImage *v29; // eax
  idImageManagerLocal_vtbl *v30; // edx

  memset(this->imageHashTable, 0, sizeof(this->imageHashTable));
  v2 = this->images.num <= 1024;
  list = this->images.list;
  this->images.granularity = 1024;
  this->images.size = 1024;
  if ( !v2 )
    this->images.num = 1024;
  this->images.list = (idImage **)Memory::Allocate(0x1000u);
  for ( i = 0; i < this->images.num; ++i )
    this->images.list[i] = list[i];
  if ( list )
    Memory::Free(list);
  this->cacheLRU.cacheUsageNext = &this->cacheLRU;
  this->cacheLRU.cacheUsagePrev = &this->cacheLRU;
  this->ChangeTextureFilter(this);
  this->defaultImage = this->ImageFromFunction(this, "_default", R_DefaultImage);
  v5 = this->ImageFromFunction(this, "_white", R_WhiteImage);
  v6 = this->__vftable;
  this->whiteImage = v5;
  this->blackImage = v6->ImageFromFunction(this, "_black", R_BlackImage);
  v7 = this->ImageFromFunction(this, "_borderClamp", R_BorderClampImage);
  v8 = this->__vftable;
  this->borderClampImage = v7;
  this->flatNormalMap = v8->ImageFromFunction(this, "_flat", R_FlatNormalImage);
  v9 = this->ImageFromFunction(this, "_ambient", R_AmbientNormalImage);
  v10 = this->__vftable;
  this->ambientNormalMap = v9;
  this->specularTableImage = v10->ImageFromFunction(this, "_specularTable", R_SpecularTableImage);
  v11 = this->ImageFromFunction(this, "_specular2DTable", R_Specular2DTableImage);
  v12 = this->__vftable;
  this->specular2DTableImage = v11;
  this->rampImage = v12->ImageFromFunction(this, "_ramp", R_RampImage);
  v13 = this->ImageFromFunction(this, "_alphaRamp", R_RampImage);
  v14 = this->__vftable;
  this->alphaRampImage = v13;
  this->alphaNotchImage = v14->ImageFromFunction(this, "_alphaNotch", R_AlphaNotchImage);
  v15 = this->ImageFromFunction(this, "_fog", R_FogImage);
  v16 = this->__vftable;
  this->fogImage = v15;
  this->fogEnterImage = v16->ImageFromFunction(this, "_fogEnter", R_FogEnterImage);
  v17 = this->ImageFromFunction(this, "_normalCubeMap", makeNormalizeVectorCubeMap);
  v18 = this->__vftable;
  this->normalCubeMapImage = v17;
  this->noFalloffImage = v18->ImageFromFunction(this, "_noFalloff", R_CreateNoFalloffImage);
  this->ImageFromFunction(this, "_quadratic", R_QuadraticImage);
  this->cinematicImage = this->ImageFromFunction(this, "_cinematic", R_RGBA8Image);
  v19 = this->ImageFromFunction(this, "_accum", R_RGBA8Image);
  v20 = this->__vftable;
  this->accumImage = v19;
  this->scratchImage = v20->ImageFromFunction(this, "_scratch", R_RGBA8Image);
  v21 = this->ImageFromFunction(this, "_scratch2", R_RGBA8Image);
  v22 = this->__vftable;
  this->scratchImage2 = v21;
  this->refractImage = v22->ImageFromFunction(this, "_refract", R_RGBA8Image);
  v23 = this->ImageFromFunction(this, "_screenBlur", R_RGBA8Image);
  v24 = this->__vftable;
  this->blurImage = v23;
  this->scratchRender = v24->ImageFromFunction(this, "_scratchRender", R_RGBA8ImageClamped);
  v25 = this->ImageFromFunction(this, "_scratchRender2", R_RGBA8ImageClamped);
  v26 = this->__vftable;
  this->scratchRender2 = v25;
  this->reflectionImage = v26->ImageFromFunction(this, "_reflectionRender", R_RGBA8Image);
  v27 = this->ImageFromFunction(this, "_refractionRender", R_RGBA8Image);
  v28 = this->__vftable;
  this->refractionImage = v27;
  v28->ImageFromFunction(this, "_prevRender", R_RGBA8Image);
  cmdSystem->AddCommand(cmdSystem, "imageStats", R_ImageStats_f, 0, "areis:fixme", 0);
  this->quickLoadImage = this->ImageFromFunction(this, "_quickload", R_QuickLoadImage);
  v29 = this->ImageFromFunction(this, "_scratchCubeMap", makeNormalizeVectorCubeMap);
  v30 = this->__vftable;
  this->scratchCubeMapImage = v29;
  this->currentRenderImage = v30->ImageFromFunction(this, "_currentRender", R_RGBA8Image);
  cmdSystem->AddCommand(cmdSystem, "reloadImages", R_ReloadImages_f, 4, "reloads images", 0);
  cmdSystem->AddCommand(cmdSystem, "listImages", R_ListImages_f, 4, "lists images", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "listImageReferences",
    R_ListImageReferences_f,
    4,
    "lists materials and models referencing an image pattern",
    0);
  cmdSystem->AddCommand(cmdSystem, "listImagesRaven", R_ListImagesRaven_f, 4, "lists images (Raven)", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "combineCubeImages",
    R_CombineCubeImages_f,
    4,
    "combines six images for roq compression",
    0);
  cmdSystem->AddCommand(
    cmdSystem,
    "writeProgramImages",
    R_writeProgramImages_f,
    4,
    "write program formulated targas to compression dir",
    0);
  cmdSystem->AddCommand(cmdSystem, "writeRDF", R_writeRDF_f, 4, "write RDF file", 0);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::StartBuild(void)
void __thiscall idImageManagerLocal::StartBuild(idImageManagerLocal *this)
{
  idStr *list; // eax
  char *v3; // edi

  list = this->ddsList.list;
  if ( list )
  {
    v3 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v3);
  }
  this->ddsList.list = 0;
  this->ddsList.num = 0;
  this->ddsList.size = 0;
  idHashIndex::Free(&this->ddsHash);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::LoadImageA(char const *,unsigned char * *,int *,int *,unsigned int *,bool)
void __thiscall idImageManagerLocal::LoadImageA(
        idImageManagerLocal *this,
        const char *name,
        unsigned __int8 **pic,
        int *width,
        int *height,
        unsigned int *timestamp,
        bool makePowerOf2)
{
  R_LoadImage(name, pic, width, height, timestamp, makePowerOf2);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::WriteTGA(char const *,unsigned char const *,int,int,bool)
void __thiscall idImageManagerLocal::WriteTGA(
        idImageManagerLocal *this,
        const char *filename,
        const unsigned __int8 *data,
        int width,
        int height,
        bool flipVertical)
{
  R_WriteTGA(filename, data, width, height, flipVertical);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::StaticFree(void *)
void __thiscall idImageManagerLocal::StaticFree(idImageManagerLocal *this, void *pic)
{
  R_StaticFree(pic);
}

// FUNC: public: virtual unsigned int __thiscall idImageManagerLocal::GetTextureMinFilter(void)const
unsigned int __thiscall idImageManagerLocal::GetTextureMinFilter(idImageManagerLocal *this)
{
  return this->textureMinFilter;
}

// FUNC: public: virtual unsigned int __thiscall idImageManagerLocal::GetTextureMaxFilter(void)const
unsigned int __thiscall idImageManagerLocal::GetTextureMaxFilter(idImageManagerLocal *this)
{
  return this->textureMaxFilter;
}

// FUNC: public: virtual float __thiscall idImageManagerLocal::GetTextureAnisotropy(void)const
double __thiscall idImageManagerLocal::GetTextureAnisotropy(idImageManagerLocal *this)
{
  return this->textureAnisotropy;
}

// FUNC: public: virtual float __thiscall idImageManagerLocal::GetTextureLODBias(void)const
double __thiscall idImageManagerLocal::GetTextureLODBias(idImageManagerLocal *this)
{
  return this->textureLODBias;
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::BindEditorImage(class idMaterial const *)
void __thiscall idImageManagerLocal::BindEditorImage(idImageManagerLocal *this, idMaterial *mat)
{
  idImage *EditorImage; // eax

  EditorImage = idMaterial::GetEditorImage(mat);
  EditorImage->Bind(EditorImage);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::ActuallyLoadImage(class idImage *,bool,bool)
void __thiscall idImageManagerLocal::ActuallyLoadImage(
        idImageManagerLocal *this,
        idImage *image,
        bool checkForPrecompressed,
        bool fromBackEnd)
{
  idImage::ActuallyLoadImage(image, checkForPrecompressed, fromBackEnd);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::BindImage(class idImage *)
void __thiscall idImageManagerLocal::BindImage(idImageManagerLocal *this, idImage *image)
{
  image->Bind(image);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::UploadScratch(unsigned char const *,int,int)
void __thiscall idImageManagerLocal::UploadScratch(
        idImageManagerLocal *this,
        const unsigned __int8 *pic,
        int width,
        int height)
{
  idImage *v4; // eax

  v4 = this->GetScratchImage(this);
  idImage::UploadScratch(v4, pic, width, height);
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetCacheUsageNext(void)const
idImage *__thiscall idImageManagerLocal::GetCacheUsageNext(idImageManagerLocal *this)
{
  return this->cacheLRU.cacheUsageNext;
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetCacheHead(void)
idImage *__thiscall idImageManagerLocal::GetCacheHead(idImageManagerLocal *this)
{
  return &this->cacheLRU;
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetCacheUsagePrev(void)const
idImage *__thiscall idImageManagerLocal::GetCacheUsagePrev(idImageManagerLocal *this)
{
  return this->cacheLRU.cacheUsagePrev;
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::SetBackgroundImageLoads(class idImage *)
void __thiscall idImageManagerLocal::SetBackgroundImageLoads(idImageManagerLocal *this, idImage *image)
{
  this->backgroundImageLoads = image;
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetWhiteImage(void)const
idImage *__thiscall idImageManagerLocal::GetWhiteImage(idImageManagerLocal *this)
{
  return this->whiteImage;
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetNormalCubeMapImage(void)const
idImage *__thiscall idImageManagerLocal::GetNormalCubeMapImage(idImageManagerLocal *this)
{
  return this->normalCubeMapImage;
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetDiffuseImage(class idMaterial const *)const
idImage *__thiscall idImageManagerLocal::GetDiffuseImage(idImageManagerLocal *this, idMaterial *material)
{
  return idMaterial::GetDiffuseImage(material);
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetReflectionImage(void)const
idImage *__thiscall idImageManagerLocal::GetReflectionImage(idImageManagerLocal *this)
{
  return this->reflectionImage;
}

// FUNC: public: virtual unsigned char __thiscall idImageManagerLocal::GetOriginalToCompressed(int)const
unsigned __int8 __thiscall idImageManagerLocal::GetOriginalToCompressed(idImageManagerLocal *this, int i)
{
  return this->originalToCompressed[i];
}

// FUNC: public: virtual unsigned char const * __thiscall idImageManagerLocal::GetCompressedPalette(void)const
unsigned __int8 *__thiscall idImageManagerLocal::GetCompressedPalette(idImageManagerLocal *this)
{
  return this->compressedPalette;
}

// FUNC: public: virtual class idImage * __thiscall idImageManagerLocal::GetImageByIndex(int)const
idImage *__thiscall idImageManagerLocal::GetImageByIndex(idImageManagerLocal *this, int index)
{
  return this->images.list[index];
}

// FUNC: public: virtual int __thiscall idImageManagerLocal::GetNumImages(void)const
int __thiscall idImageManagerLocal::GetNumImages(idImageManagerLocal *this)
{
  return this->images.num;
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::AppendImage(class idImage *)
void __thiscall idImageManagerLocal::AppendImage(idImageManagerLocal *this, idImage *image)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v8; // ecx
  idImage **list; // edi
  int j; // eax

  if ( !this->images.list )
  {
    granularity = this->images.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->images.size )
      {
        v4 = granularity < this->images.num;
        this->images.size = granularity;
        if ( v4 )
          this->images.num = granularity;
        this->images.list = (idImage **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->images.num; ++i )
          this->images.list[i] = *(idImage **)(4 * i);
      }
    }
    else
    {
      this->images.list = 0;
      this->images.num = 0;
      this->images.size = 0;
    }
  }
  num = this->images.num;
  size = this->images.size;
  if ( num == size )
  {
    if ( !this->images.granularity )
      this->images.granularity = 16;
    v8 = size + this->images.granularity - (size + this->images.granularity) % this->images.granularity;
    if ( v8 > 0 )
    {
      if ( v8 != this->images.size )
      {
        list = this->images.list;
        this->images.size = v8;
        if ( v8 < num )
          this->images.num = v8;
        this->images.list = (idImage **)Memory::Allocate(4 * v8);
        for ( j = 0; j < this->images.num; ++j )
          this->images.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->images.list )
        Memory::Free(this->images.list);
      this->images.list = 0;
      this->images.num = 0;
      this->images.size = 0;
    }
  }
  this->images.list[this->images.num++] = image;
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::FinishBuild(bool)
void __thiscall idImageManagerLocal::FinishBuild(idImageManagerLocal *this, bool removeDups)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  int v3; // edi
  idStr *list; // eax
  char *v6; // esi
  char *v7; // ebx
  char *v8; // eax
  int v9; // esi
  int v10; // eax
  char *data; // edx
  char *v12; // ecx
  char v13; // al
  int v14; // eax
  int Char; // esi
  int len; // ebx
  int v17; // esi
  int v18; // edi
  int granularity; // esi
  bool v20; // cc
  float v21; // eax
  idStr *v22; // edi
  int v23; // esi
  unsigned int v24; // edi
  idStr *v25; // ebx
  int v26; // eax
  int v27; // eax
  int num; // edi
  int size; // esi
  int v30; // esi
  idStr *v31; // eax
  char *v32; // esi
  idStr *v33; // ebx
  float v34; // eax
  idStr *v35; // edi
  int v36; // esi
  float v37; // edi
  idStr *v38; // ebx
  char *v39; // esi
  float v40; // ecx
  char *v41; // edi
  char v42; // al
  char *v43; // edi
  char *v44; // esi
  float v45; // eax
  int v46; // esi
  idStr *v47; // ebx
  char *v48; // edi
  unsigned int v49; // ecx
  char *v50; // esi
  char v51; // al
  char *v52; // edi
  char *v53; // esi
  float v54; // eax
  const char *v55; // eax
  idFile *v56; // eax
  idFile *v57; // esi
  int v58; // ebx
  idFile_vtbl *v59; // edx
  idStr *v60; // eax
  char *v61; // esi
  int j; // [esp+24h] [ebp-80h]
  int k; // [esp+24h] [ebp-80h]
  int ddsNum; // [esp+28h] [ebp-7Ch]
  int ddsNuma; // [esp+28h] [ebp-7Ch]
  char *buffer; // [esp+2Ch] [ebp-78h] BYREF
  int v67; // [esp+30h] [ebp-74h]
  float v68; // [esp+34h] [ebp-70h]
  idStr str; // [esp+38h] [ebp-6Ch] BYREF
  idStr right; // [esp+58h] [ebp-4Ch] BYREF
  idStr line; // [esp+78h] [ebp-2Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v72; // [esp+98h] [ebp-Ch]
  void *v73; // [esp+9Ch] [ebp-8h]
  int i; // [esp+A0h] [ebp-4h]

  i = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v73 = &_ehhandler__FinishBuild_idImageManagerLocal__UAEX_N_Z;
  v72 = ExceptionList;
  v3 = 0;
  if ( removeDups )
  {
    list = this->ddsList.list;
    if ( list )
    {
      v6 = &list[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        list,
        0x20u,
        *(_DWORD *)&list[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v6);
    }
    this->ddsList.list = 0;
    this->ddsList.num = 0;
    this->ddsList.size = 0;
    buffer = 0;
    fileSystem->ReadFile(fileSystem, "makedds.bat", (void **)&buffer, 0);
    if ( buffer )
    {
      v7 = buffer;
      str.len = 0;
      str.alloced = 20;
      str.data = str.baseBuffer;
      str.baseBuffer[0] = 0;
      v8 = &buffer[strlen(buffer) + 1];
      v9 = v8 - (buffer + 1);
      v10 = v8 - buffer;
      if ( v10 > 20 )
        idStr::ReAllocate(&str, v10, 1);
      data = str.data;
      v12 = v7;
      do
      {
        v13 = *v12;
        *data++ = *v12++;
      }
      while ( v13 );
      v14 = v9;
      str.len = v9;
      for ( i = 0; str.len; v3 = 0 )
      {
        Char = idStr::FindChar(str.data, 10, 0, v14);
        if ( Char <= 0 )
          break;
        idStr::Left(&str, &line, Char + 1);
        right.len = 0;
        right.alloced = 20;
        right.data = right.baseBuffer;
        right.baseBuffer[0] = 0;
        LOBYTE(i) = 2;
        if ( str.len - Char - 1 < str.len )
        {
          idStr::Mid(&str, Char + 1, str.len - Char - 1, &right);
          len = right.len;
        }
        else
        {
          len = str.len;
          if ( str.len + 1 > 20 )
            idStr::ReAllocate(&right, str.len + 1, 0);
          qmemcpy(right.data, str.data, len);
          right.data[len] = 0;
          right.len = len;
        }
        if ( len + 1 > str.alloced )
          idStr::ReAllocate(&str, len + 1, 0);
        qmemcpy(str.data, right.data, len);
        str.data[len] = 0;
        str.len = len;
        v17 = 0;
        if ( this->ddsList.num <= 0 )
          goto LABEL_24;
        v18 = 0;
        while ( idStr::Cmp(this->ddsList.list[v18].data, line.data) )
        {
          ++v17;
          ++v18;
          if ( v17 >= this->ddsList.num )
            goto LABEL_24;
        }
        if ( v17 < 0 )
        {
LABEL_24:
          if ( !this->ddsList.list )
          {
            granularity = this->ddsList.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->ddsList.size )
              {
                v20 = granularity < this->ddsList.num;
                this->ddsList.size = granularity;
                if ( v20 )
                  this->ddsList.num = granularity;
                v21 = COERCE_FLOAT(Memory::Allocate(32 * granularity + 4));
                v68 = v21;
                LOBYTE(i) = 3;
                if ( v21 == 0.0 )
                {
                  v22 = 0;
                }
                else
                {
                  v22 = (idStr *)(LODWORD(v21) + 4);
                  *(_DWORD *)LODWORD(v21) = granularity;
                  `eh vector constructor iterator'(
                    (void *)(LODWORD(v21) + 4),
                    0x20u,
                    granularity,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                v20 = this->ddsList.num <= 0;
                LOBYTE(i) = 2;
                this->ddsList.list = v22;
                ddsNum = 0;
                if ( !v20 )
                {
                  v23 = 0;
                  for ( j = 0; ; v23 = j )
                  {
                    v24 = *(_DWORD *)v23;
                    v25 = (idStr *)((char *)this->ddsList.list + v23);
                    v26 = *(_DWORD *)v23 + 1;
                    v20 = v26 <= v25->alloced;
                    v67 = *(_DWORD *)v23;
                    if ( !v20 )
                      idStr::ReAllocate(v25, v26, 0);
                    v27 = v67;
                    j += 32;
                    qmemcpy(v25->data, *(const void **)(v23 + 4), v24);
                    v25->data[v27] = 0;
                    v25->len = v27;
                    if ( ++ddsNum >= this->ddsList.num )
                      break;
                  }
                }
              }
            }
            else
            {
              this->ddsList.list = 0;
              this->ddsList.num = 0;
              this->ddsList.size = 0;
            }
          }
          num = this->ddsList.num;
          size = this->ddsList.size;
          if ( num == size )
          {
            if ( !this->ddsList.granularity )
              this->ddsList.granularity = 16;
            v30 = this->ddsList.granularity + size - (this->ddsList.granularity + size) % this->ddsList.granularity;
            if ( v30 > 0 )
            {
              if ( v30 != this->ddsList.size )
              {
                v33 = this->ddsList.list;
                ddsNuma = (int)v33;
                this->ddsList.size = v30;
                if ( v30 < num )
                  this->ddsList.num = v30;
                v34 = COERCE_FLOAT(Memory::Allocate(32 * v30 + 4));
                v68 = v34;
                LOBYTE(i) = 4;
                if ( v34 == 0.0 )
                {
                  v35 = 0;
                }
                else
                {
                  v35 = (idStr *)(LODWORD(v34) + 4);
                  *(_DWORD *)LODWORD(v34) = v30;
                  `eh vector constructor iterator'(
                    (void *)(LODWORD(v34) + 4),
                    0x20u,
                    v30,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                v36 = 0;
                v20 = this->ddsList.num <= 0;
                LOBYTE(i) = 2;
                this->ddsList.list = v35;
                v67 = 0;
                if ( !v20 )
                {
                  for ( k = 0; ; v36 = k )
                  {
                    v37 = *(float *)(ddsNuma + v36);
                    v38 = (idStr *)((char *)this->ddsList.list + v36);
                    v20 = LODWORD(v37) + 1 <= v38->alloced;
                    v68 = v37;
                    if ( !v20 )
                      idStr::ReAllocate(v38, LODWORD(v37) + 1, 0);
                    v39 = *(char **)(ddsNuma + v36 + 4);
                    k += 32;
                    v40 = v37;
                    v41 = v38->data;
                    v42 = LOBYTE(v40);
                    LODWORD(v40) >>= 2;
                    qmemcpy(v41, v39, 4 * LODWORD(v40));
                    v44 = &v39[4 * LODWORD(v40)];
                    v43 = &v41[4 * LODWORD(v40)];
                    LOBYTE(v40) = v42;
                    v45 = v68;
                    qmemcpy(v43, v44, LOBYTE(v40) & 3);
                    v38->data[LODWORD(v45)] = 0;
                    *(float *)&v38->len = v45;
                    v20 = ++v67 < this->ddsList.num;
                    if ( !v20 )
                      break;
                  }
                  v33 = (idStr *)ddsNuma;
                }
                if ( v33 )
                {
                  `eh vector destructor iterator'(
                    v33,
                    0x20u,
                    *(_DWORD *)&v33[-1].baseBuffer[16],
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  Memory::Free(&v33[-1].baseBuffer[16]);
                }
              }
            }
            else
            {
              v31 = this->ddsList.list;
              if ( v31 )
              {
                v32 = &v31[-1].baseBuffer[16];
                `eh vector destructor iterator'(
                  v31,
                  0x20u,
                  *(_DWORD *)&v31[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(v32);
              }
              this->ddsList.list = 0;
              this->ddsList.num = 0;
              this->ddsList.size = 0;
            }
          }
          v46 = line.len;
          v47 = &this->ddsList.list[this->ddsList.num];
          v20 = line.len + 1 <= v47->alloced;
          v68 = *(float *)&line.len;
          if ( !v20 )
            idStr::ReAllocate(v47, line.len + 1, 0);
          v48 = v47->data;
          v49 = v46;
          v50 = line.data;
          v51 = v49;
          v49 >>= 2;
          qmemcpy(v48, line.data, 4 * v49);
          v53 = &v50[4 * v49];
          v52 = &v48[4 * v49];
          LOBYTE(v49) = v51;
          v54 = v68;
          qmemcpy(v52, v53, v49 & 3);
          v47->data[LODWORD(v54)] = 0;
          *(float *)&v47->len = v54;
          ++this->ddsList.num;
        }
        LOBYTE(i) = 1;
        idStr::FreeData(&right);
        LOBYTE(i) = 0;
        idStr::FreeData(&line);
        v14 = str.len;
      }
      i = -1;
      idStr::FreeData(&str);
    }
    v55 = "makedds2.bat";
  }
  else
  {
    v55 = "makedds.bat";
  }
  v56 = fileSystem->OpenFileWrite(fileSystem, v55, "fs_savepath", 0);
  v57 = v56;
  if ( v56 )
  {
    ((void (__stdcall *)(idFile *))v56->Printf)(v56);
    v57->Printf(v57, "if exist c:\\ddsfail.bat del /F c:\\ddsfail.bat\n");
    buffer = (char *)this->ddsList.num;
    if ( (int)buffer > 0 )
    {
      v58 = 0;
      v68 = (float)(int)buffer;
      do
      {
        v57->Printf(v57, ":line%d\n", v3);
        v57->Printf(v57, "echo %d / %d\n", v3, this->ddsList.num);
        v57->Printf(v57, "%s\n", this->ddsList.list[v58].data);
        v59 = v57->__vftable;
        str.len = ++v3;
        v59->Printf(v57, "if errorlevel 0 goto line%d\n", v3);
        v57->Printf(v57, "echo %s >> c:\\ddsfail.bat\n", this->ddsList.list[v58].data);
        v57->Printf(
          v57,
          "@echo Finished compressing %d of %d.  %.1f percent done.\n",
          v3,
          buffer,
          (double)str.len / v68 * 100.0);
        ++v58;
      }
      while ( v3 < (int)buffer );
    }
    fileSystem->CloseFile(fileSystem, v57);
  }
  v60 = this->ddsList.list;
  if ( v60 )
  {
    v61 = &v60[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v60,
      0x20u,
      *(_DWORD *)&v60[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v61);
  }
  this->ddsList.list = 0;
  this->ddsList.num = 0;
  this->ddsList.size = 0;
  idHashIndex::Free(&this->ddsHash);
}

// FUNC: public: virtual void __thiscall idImageManagerLocal::AddDDSCommand(char const *)
void __thiscall idImageManagerLocal::AddDDSCommand(idImageManagerLocal *this, const char *cmd)
{
  const char *v3; // eax
  int v4; // esi
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  char *v9; // ecx
  unsigned __int8 v10; // al
  int i; // esi
  unsigned int v12; // edx
  int v13; // esi
  int granularity; // esi
  bool v15; // cc
  int *v16; // eax
  idStr *v17; // ebx
  const char *v18; // esi
  unsigned int v19; // edi
  idStr *v20; // ebx
  int v21; // eax
  int num; // ebx
  int size; // esi
  int v24; // esi
  idStr *v25; // eax
  char *v26; // esi
  idStr *list; // edi
  int *v28; // eax
  idStr *v29; // ebx
  const char *v30; // esi
  unsigned int v31; // edi
  idStr *v32; // ebx
  idStr *v33; // ebx
  int len; // esi
  int v35; // [esp+Ch] [ebp-38h]
  idStr *v36; // [esp+Ch] [ebp-38h]
  int v37; // [esp+10h] [ebp-34h]
  int v38; // [esp+10h] [ebp-34h]
  idStr strCmd; // [esp+18h] [ebp-2Ch] BYREF
  int v40; // [esp+40h] [ebp-4h]
  const char *cmda; // [esp+48h] [ebp+4h]
  const char *cmdb; // [esp+48h] [ebp+4h]
  const char *cmdc; // [esp+48h] [ebp+4h]

  if ( cmd && *cmd )
  {
    strCmd.data = strCmd.baseBuffer;
    strCmd.len = 0;
    strCmd.alloced = 20;
    strCmd.baseBuffer[0] = 0;
    v3 = &cmd[strlen(cmd) + 1];
    v4 = v3 - (cmd + 1);
    v5 = v3 - cmd;
    if ( v5 > 20 )
      idStr::ReAllocate(&strCmd, v5, 1);
    data = strCmd.data;
    v7 = cmd;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    strCmd.len = v4;
    v40 = 0;
    idStr::SlashesToBackSlashes(&strCmd);
    v9 = strCmd.data;
    v10 = *strCmd.data;
    for ( i = 0; v10; i += v12 )
    {
      if ( idStr::lowerCaseCharacter[v10] )
        v10 = idStr::lowerCaseCharacter[v10];
      v12 = (char)v10 * (_DWORD)&v9[119 - (unsigned int)strCmd.data];
      v10 = *++v9;
    }
    v13 = this->ddsHash.hash[i & this->ddsHash.hashMask & this->ddsHash.hashMask & this->ddsHash.lookupMask];
    if ( v13 == -1 )
    {
LABEL_16:
      if ( !this->ddsList.list )
      {
        granularity = this->ddsList.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->ddsList.size )
          {
            v15 = granularity < this->ddsList.num;
            this->ddsList.size = granularity;
            if ( v15 )
              this->ddsList.num = granularity;
            v16 = (int *)Memory::Allocate(32 * granularity + 4);
            LOBYTE(v40) = 1;
            if ( v16 )
            {
              v17 = (idStr *)(v16 + 1);
              *v16 = granularity;
              `eh vector constructor iterator'(
                v16 + 1,
                0x20u,
                granularity,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            }
            else
            {
              v17 = 0;
            }
            v15 = this->ddsList.num <= 0;
            LOBYTE(v40) = 0;
            this->ddsList.list = v17;
            v35 = 0;
            if ( !v15 )
            {
              v18 = 0;
              for ( cmda = 0; ; v18 = cmda )
              {
                v19 = *(_DWORD *)v18;
                v20 = (idStr *)&v18[(unsigned int)this->ddsList.list];
                v21 = *(_DWORD *)v18 + 1;
                v37 = *(_DWORD *)v18;
                if ( v21 > v20->alloced )
                  idStr::ReAllocate(v20, v21, 0);
                cmda += 32;
                qmemcpy(v20->data, *((const void **)v18 + 1), v19);
                v20->data[v37] = 0;
                v20->len = v37;
                if ( ++v35 >= this->ddsList.num )
                  break;
              }
            }
          }
        }
        else
        {
          this->ddsList.list = 0;
          this->ddsList.num = 0;
          this->ddsList.size = 0;
        }
      }
      num = this->ddsList.num;
      size = this->ddsList.size;
      if ( num == size )
      {
        if ( !this->ddsList.granularity )
          this->ddsList.granularity = 16;
        v24 = this->ddsList.granularity + size - (this->ddsList.granularity + size) % this->ddsList.granularity;
        if ( v24 > 0 )
        {
          if ( v24 != this->ddsList.size )
          {
            list = this->ddsList.list;
            v36 = list;
            this->ddsList.size = v24;
            if ( v24 < num )
              this->ddsList.num = v24;
            v28 = (int *)Memory::Allocate(32 * v24 + 4);
            LOBYTE(v40) = 2;
            if ( v28 )
            {
              v29 = (idStr *)(v28 + 1);
              *v28 = v24;
              `eh vector constructor iterator'(
                v28 + 1,
                0x20u,
                v24,
                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            }
            else
            {
              v29 = 0;
            }
            v30 = 0;
            v15 = this->ddsList.num <= 0;
            LOBYTE(v40) = 0;
            this->ddsList.list = v29;
            v38 = 0;
            if ( !v15 )
            {
              for ( cmdb = 0; ; v30 = cmdb )
              {
                v31 = *(int *)((char *)&list->len + (_DWORD)v30);
                v32 = (idStr *)&v30[(unsigned int)this->ddsList.list];
                if ( (signed int)(v31 + 1) > v32->alloced )
                  idStr::ReAllocate(v32, v31 + 1, 0);
                cmdb += 32;
                qmemcpy(v32->data, *(const void **)((char *)&v36->data + (_DWORD)v30), v31);
                v32->data[v31] = 0;
                v32->len = v31;
                v15 = ++v38 < this->ddsList.num;
                list = v36;
                if ( !v15 )
                  break;
              }
            }
            if ( list )
            {
              `eh vector destructor iterator'(
                list,
                0x20u,
                *(_DWORD *)&list[-1].baseBuffer[16],
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(&list[-1].baseBuffer[16]);
            }
          }
        }
        else
        {
          v25 = this->ddsList.list;
          if ( v25 )
          {
            v26 = &v25[-1].baseBuffer[16];
            `eh vector destructor iterator'(
              v25,
              0x20u,
              *(_DWORD *)&v25[-1].baseBuffer[16],
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(v26);
          }
          this->ddsList.list = 0;
          this->ddsList.num = 0;
          this->ddsList.size = 0;
        }
      }
      v33 = &this->ddsList.list[this->ddsList.num];
      len = strCmd.len;
      cmdc = (const char *)strCmd.len;
      if ( strCmd.len + 1 > v33->alloced )
        idStr::ReAllocate(v33, strCmd.len + 1, 0);
      qmemcpy(v33->data, strCmd.data, len);
      cmdc[(unsigned int)v33->data] = 0;
      v33->len = (int)cmdc;
      ++this->ddsList.num;
    }
    else
    {
      while ( idStr::Icmp(this->ddsList.list[v13].data, strCmd.data) )
      {
        v13 = this->ddsHash.indexChain[v13 & this->ddsHash.lookupMask];
        if ( v13 == -1 )
          goto LABEL_16;
      }
    }
    v40 = -1;
    idStr::FreeData(&strCmd);
  }
}
