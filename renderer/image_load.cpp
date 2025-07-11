
// FUNC: FormatIsDXT
bool __usercall FormatIsDXT@<al>(int internalFormat@<eax>)
{
  return internalFormat >= 33776 && internalFormat <= 33779;
}

// FUNC: int __cdecl MakePowerOfTwo(int)
int __cdecl MakePowerOfTwo(int num)
{
  int result; // eax

  for ( result = 1; result < num; result *= 2 )
    ;
  return result;
}

// FUNC: public: int __thiscall idImage::BitsForInternalFormat(int)const
int __thiscall idImage::BitsForInternalFormat(idImage *this, int internalFormat)
{
  if ( internalFormat <= 32849 )
  {
    if ( internalFormat != 32849 )
    {
      if ( internalFormat > 32828 )
      {
        switch ( internalFormat )
        {
          case 32832:
          case 32843:
            return 8;
          case 32837:
          case 32848:
            return 16;
          default:
            goto LABEL_9;
        }
      }
      if ( internalFormat == 32828 )
        return 8;
      if ( internalFormat > 3 )
      {
        if ( internalFormat != 4 )
        {
          if ( internalFormat != 6400 )
            goto LABEL_9;
          return 8;
        }
      }
      else if ( internalFormat != 3 )
      {
        if ( internalFormat != 1 )
        {
          if ( internalFormat != 2 )
          {
LABEL_9:
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
              common.type,
              "R_BitsForInternalFormat: BAD FORMAT:%i",
              internalFormat);
            return 0;
          }
          return 16;
        }
        return 8;
      }
    }
    return 32;
  }
  if ( internalFormat > 33777 )
  {
    switch ( internalFormat )
    {
      case 33778:
      case 33779:
      case 34030:
        return 8;
      case 34029:
        return 4;
      default:
        goto LABEL_9;
    }
  }
  if ( internalFormat != 33777 )
  {
    if ( internalFormat <= 32997 )
    {
      if ( internalFormat == 32997 )
        return 8;
      if ( internalFormat == 32854 )
        return 16;
      if ( internalFormat != 32856 )
        goto LABEL_9;
      return 32;
    }
    if ( internalFormat != 33776 )
      goto LABEL_9;
  }
  return 4;
}

// FUNC: public: void __thiscall idImage::UploadPalettisedNormalMap(int,int,unsigned char const *,int)
void __thiscall idImage::UploadPalettisedNormalMap(
        idImage *this,
        int width,
        int height,
        const unsigned __int8 *rgba,
        int mipLevel)
{
  int v5; // edi
  int v6; // eax
  void *v7; // esp
  unsigned __int8 *v8; // ecx
  int v9; // eax
  int v10; // esi
  const unsigned __int8 *v11; // edi
  int v12; // eax
  int v13; // ecx
  int v14; // ebx
  int v15; // ebx
  _BYTE v16[12]; // [esp+0h] [ebp-3Ch] BYREF
  int y; // [esp+Ch] [ebp-30h]
  int v18; // [esp+10h] [ebp-2Ch]
  unsigned __int8 *out; // [esp+14h] [ebp-28h]
  unsigned __int8 *normals; // [esp+18h] [ebp-24h]
  const unsigned __int8 *in; // [esp+1Ch] [ebp-20h]
  int row; // [esp+20h] [ebp-1Ch]
  CPPEH_RECORD ms_exc; // [esp+24h] [ebp-18h]

  v5 = width;
  row = 4;
  if ( width >= 4 )
    row = width;
  v6 = height * row + 3;
  LOBYTE(v6) = v6 & 0xFC;
  v7 = alloca(v6);
  ms_exc.old_esp = (DWORD)v16;
  normals = v16;
  ms_exc.registration.TryLevel = -1;
  in = rgba;
  v8 = v16;
  out = v16;
  v9 = height;
  if ( height > 0 )
  {
    v18 = height;
    do
    {
      v10 = 0;
      if ( v5 > 0 )
      {
        v11 = in + 2;
        do
        {
          v12 = *(v11 - 2);
          v13 = *(v11 - 1);
          y = v13;
          if ( v12 == 128 && v13 == 128 && *v11 == 0x80 )
          {
            LOBYTE(v14) = -1;
          }
          else
          {
            v15 = 16 * globalImages->GetOriginalToCompressed(globalImages, v12);
            v14 = globalImages->GetOriginalToCompressed(globalImages, y) | v15;
            if ( v14 == 255 )
              LOBYTE(v14) = -2;
          }
          v8 = out;
          out[v10++] = v14;
          v11 += 4;
        }
        while ( v10 < width );
        v5 = width;
      }
      v8 += row;
      out = v8;
      in += 4 * v5;
      --v18;
    }
    while ( v18 );
    v9 = height;
  }
  if ( glConfig.sharedTexturePaletteAvailable )
    qglTexImage2D(0xDE1u, mipLevel, 32997, v5, v9, 0, 0x1900u, 0x1401u, normals);
}

// FUNC: public: void __thiscall idImage::DeswizzleAndUploadPalettisedNormalMap(int,int,int)
void __thiscall idImage::DeswizzleAndUploadPalettisedNormalMap(idImage *this, int width, int height, int mipLevel)
{
  void *v4; // edi
  _BYTE *v5; // ecx
  int v6; // edx
  int i; // eax

  v4 = R_StaticAlloc(4 * height * width);
  qglGetTexImage(0xDE1u, mipLevel, 0x1908u, 0x1401u, v4);
  v5 = v4;
  if ( height > 0 )
  {
    v6 = height;
    do
    {
      for ( i = 0; i < width; ++i )
        v5[4 * i] = v5[4 * i + 3];
      v5 += 4 * width;
      --v6;
    }
    while ( v6 );
  }
  idImage::UploadPalettisedNormalMap(this, width, height, (const unsigned __int8 *)v4, mipLevel);
  R_StaticFree(v4);
}

// FUNC: public: void __thiscall idImage::SetImageFilterAndRepeat(void)const
void __thiscall idImage::SetImageFilterAndRepeat(idImage *this)
{
  textureFilter_t filter; // eax
  __int32 v3; // eax
  float v4; // [esp+0h] [ebp-Ch]
  float v5; // [esp+0h] [ebp-Ch]
  float v6; // [esp+0h] [ebp-Ch]
  float v7; // [esp+0h] [ebp-Ch]

  filter = this->filter;
  if ( filter )
  {
    v3 = filter - 1;
    if ( v3 )
    {
      if ( v3 == 1 )
      {
        v4 = (float)globalImages->GetTextureMinFilter(globalImages);
        qglTexParameterf(0xDE1u, 0x2801u, v4);
        v5 = (float)globalImages->GetTextureMaxFilter(globalImages);
        qglTexParameterf(0xDE1u, 0x2800u, v5);
      }
      else
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
          common.type,
          "R_CreateImage: bad texture filter");
      }
    }
    else
    {
      qglTexParameterf(0xDE1u, 0x2801u, 9728.0);
      qglTexParameterf(0xDE1u, 0x2800u, 9728.0);
    }
  }
  else
  {
    qglTexParameterf(0xDE1u, 0x2801u, 9729.0);
    qglTexParameterf(0xDE1u, 0x2800u, 9729.0);
  }
  if ( glConfig.anisotropicAvailable )
  {
    if ( this->filter == TF_DEFAULT )
    {
      v6 = globalImages->GetTextureAnisotropy(globalImages);
      qglTexParameterf(0xDE1u, 0x84FEu, v6);
    }
    else
    {
      qglTexParameterf(0xDE1u, 0x84FEu, 1.0);
    }
  }
  if ( glConfig.textureLODBiasAvailable )
  {
    v7 = globalImages->GetTextureLODBias(globalImages);
    qglTexParameterf(0xDE1u, 0x8501u, v7);
  }
  switch ( this->repeat )
  {
    case TR_REPEAT:
      qglTexParameterf(0xDE1u, 0x2802u, 10497.0);
      qglTexParameterf(0xDE1u, 0x2803u, 10497.0);
      break;
    case TR_CLAMP:
    case TR_CLAMP_TO_ZERO:
    case TR_CLAMP_TO_ZERO_ALPHA:
      qglTexParameterf(0xDE1u, 0x2802u, 33071.0);
      qglTexParameterf(0xDE1u, 0x2803u, 33071.0);
      break;
    case TR_CLAMP_TO_BORDER:
      qglTexParameterf(0xDE1u, 0x2802u, 33069.0);
      qglTexParameterf(0xDE1u, 0x2803u, 33069.0);
      break;
    case TR_MIRRORED_REPEAT:
      qglTexParameterf(0xDE1u, 0x2802u, 33648.0);
      qglTexParameterf(0xDE1u, 0x2803u, 33648.0);
      break;
    default:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "R_CreateImage: bad texture repeat");
      break;
  }
}

// FUNC: public: virtual void __thiscall idImage::PurgeImage(void)
void __thiscall idImage::PurgeImage(idImage *this)
{
  unsigned int *p_texnum; // edi

  p_texnum = &this->texnum;
  if ( this->texnum != -1 )
  {
    if ( qglDeleteTextures )
      qglDeleteTextures(1, p_texnum);
    *p_texnum = -1;
  }
  backEnd.glState.tmu[0].current2DMap = -1;
  backEnd.glState.tmu[0].current3DMap = -1;
  backEnd.glState.tmu[0].currentCubeMap = -1;
  backEnd.glState.tmu[1].current2DMap = -1;
  backEnd.glState.tmu[1].current3DMap = -1;
  backEnd.glState.tmu[1].currentCubeMap = -1;
  backEnd.glState.tmu[2].current2DMap = -1;
  backEnd.glState.tmu[2].current3DMap = -1;
  backEnd.glState.tmu[2].currentCubeMap = -1;
  backEnd.glState.tmu[3].current2DMap = -1;
  backEnd.glState.tmu[3].current3DMap = -1;
  backEnd.glState.tmu[3].currentCubeMap = -1;
  backEnd.glState.tmu[4].current2DMap = -1;
  backEnd.glState.tmu[4].current3DMap = -1;
  backEnd.glState.tmu[4].currentCubeMap = -1;
  backEnd.glState.tmu[5].current2DMap = -1;
  backEnd.glState.tmu[5].current3DMap = -1;
  backEnd.glState.tmu[5].currentCubeMap = -1;
  backEnd.glState.tmu[6].current2DMap = -1;
  backEnd.glState.tmu[6].current3DMap = -1;
  backEnd.glState.tmu[6].currentCubeMap = -1;
  backEnd.glState.tmu[7].current2DMap = -1;
  backEnd.glState.tmu[7].current3DMap = -1;
  backEnd.glState.tmu[7].currentCubeMap = -1;
}

// FUNC: public: void __thiscall idImage::UploadScratch(unsigned char const *,int,int)
void __thiscall idImage::UploadScratch(idImage *this, const unsigned __int8 *data, int cols, int rows)
{
  int v5; // esi
  int i; // ebx
  int j; // ebx

  if ( rows == 6 * cols )
  {
    if ( this->type != TT_CUBIC )
    {
      this->type = TT_CUBIC;
      this->uploadWidth = -1;
    }
    this->Bind(this);
    v5 = rows / 6;
    if ( cols == this->uploadWidth && v5 == this->uploadHeight )
    {
      for ( i = 0; i < 6; ++i )
      {
        qglTexSubImage2D(i + 34069, 0, 0, 0, cols, v5, 0x1908u, 0x1401u, data);
        data += 4 * v5 * cols;
      }
    }
    else
    {
      this->uploadWidth = cols;
      this->uploadHeight = v5;
      for ( j = 0; j < 6; ++j )
      {
        qglTexImage2D(j + 34069, 0, 32849, cols, v5, 0, 0x1908u, 0x1401u, data);
        data += 4 * v5 * cols;
      }
    }
    qglTexParameterf(0xDE1u, 0x2801u, 9729.0);
    qglTexParameterf(0xDE1u, 0x2800u, 9729.0);
    qglTexParameteri(0x8513u, 0x2802u, 33071);
    qglTexParameteri(0x8513u, 0x2803u, 33071);
  }
  else
  {
    if ( this->type != TT_2D )
    {
      this->type = TT_2D;
      this->uploadWidth = -1;
    }
    this->Bind(this);
    if ( cols == this->uploadWidth && rows == this->uploadHeight )
    {
      qglTexSubImage2D(0xDE1u, 0, 0, 0, cols, rows, 0x1908u, 0x1401u, data);
    }
    else
    {
      this->uploadWidth = cols;
      this->uploadHeight = rows;
      qglTexImage2D(0xDE1u, 0, 32849, cols, rows, 0, 0x1908u, 0x1401u, data);
    }
    qglTexParameterf(0xDE1u, 0x2801u, 9729.0);
    qglTexParameterf(0xDE1u, 0x2800u, 9729.0);
    qglTexParameterf(0xDE1u, 0x2802u, 10497.0);
    qglTexParameterf(0xDE1u, 0x2803u, 10497.0);
  }
}

// FUNC: public: void __thiscall idImage::SetClassification(int)
void __thiscall idImage::SetClassification(idImage *this, int tag)
{
  this->classification = tag;
}

// FUNC: public: int __thiscall idImage::StorageSize(void)const
int __thiscall idImage::StorageSize(idImage *this)
{
  int internalFormat; // edx
  int uploadHeight; // esi
  int v4; // esi

  if ( this->texnum == -1 )
    return 0;
  internalFormat = this->internalFormat;
  if ( !internalFormat )
    return 0;
  if ( this->type == TT_3D )
  {
    uploadHeight = this->uploadHeight * this->uploadDepth;
    goto LABEL_9;
  }
  if ( this->type != TT_CUBIC )
  {
    uploadHeight = this->uploadHeight;
LABEL_9:
    v4 = this->uploadWidth * uploadHeight;
    return 4 * (v4 * idImage::BitsForInternalFormat(this, internalFormat) / 8) / 3;
  }
  v4 = 6 * this->uploadWidth * this->uploadHeight;
  return 4 * (v4 * idImage::BitsForInternalFormat(this, internalFormat) / 8) / 3;
}

// FUNC: public: char const * __thiscall idImage::GetNameForInternalFormat(void)
const char *__thiscall idImage::GetNameForInternalFormat(idImage *this)
{
  int internalFormat; // eax
  const char *result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax

  internalFormat = this->internalFormat;
  if ( internalFormat > 6400 )
  {
    if ( internalFormat > 32856 )
    {
      if ( internalFormat > 33778 )
      {
        v5 = internalFormat - 33779;
        if ( !v5 )
          return "DXT5";
        v6 = v5 - 250;
        if ( !v6 )
          return "RGBC";
        if ( v6 == 1 )
          return "RGBAC";
      }
      else
      {
        if ( internalFormat == 33778 )
          return "DXT3";
        v3 = internalFormat - 32997;
        if ( !v3 )
          return "CI8";
        v4 = v3 - 779;
        if ( !v4 )
          return "DXT1";
        if ( v4 == 1 )
          return "DXT1A";
      }
      return "<BAD>";
    }
    if ( internalFormat == 32856 )
    {
      return "RGBA8";
    }
    else
    {
      switch ( internalFormat )
      {
        case 32828:
          result = "A";
          break;
        case 32832:
          result = "L";
          break;
        case 32837:
$L114793:
          result = "LA";
          break;
        case 32843:
$L114791:
          result = "I";
          break;
        case 32848:
          result = "RGB5";
          break;
        case 32849:
          result = "RGB8";
          break;
        case 32854:
          result = "RGBA4";
          break;
        default:
          return "<BAD>";
      }
    }
  }
  else if ( internalFormat == 6400 )
  {
    return "CI";
  }
  else
  {
    switch ( internalFormat )
    {
      case 0:
        result = &entityFilter;
        break;
      case 1:
        goto $L114791;
      case 2:
        goto $L114793;
      case 3:
        result = "RGB";
        break;
      case 4:
        result = "RGBA";
        break;
      default:
        return "<BAD>";
    }
  }
  return result;
}

// FUNC: public: virtual void __thiscall idPBufferImage::Bind(void)
void __thiscall idPBufferImage::Bind(idPBufferImage *this)
{
  rvTexRenderTarget *mRenderTarget; // ecx

  mRenderTarget = this->mRenderTarget;
  if ( mRenderTarget )
    rvTexRenderTarget::BeginTexture(mRenderTarget, this->texnum, 9728, 9728, 33071);
}

// FUNC: public: virtual void __thiscall idPBufferImage::UnBind(void)
void __thiscall idPBufferImage::UnBind(idPBufferImage *this)
{
  rvTexRenderTarget *mRenderTarget; // ecx

  mRenderTarget = this->mRenderTarget;
  if ( mRenderTarget )
    rvTexRenderTarget::EndTexture(mRenderTarget);
}

// FUNC: public: virtual void __thiscall idPBufferImage::PurgeImage(void)
void __thiscall idPBufferImage::PurgeImage(idPBufferImage *this)
{
  rvTexRenderTarget *mRenderTarget; // ecx
  unsigned int *p_texnum; // esi

  mRenderTarget = this->mRenderTarget;
  if ( mRenderTarget )
    rvTexRenderTarget::Release(mRenderTarget);
  p_texnum = &this->texnum;
  if ( *p_texnum != -1 )
  {
    if ( qglDeleteTextures )
      qglDeleteTextures(1, p_texnum);
    *p_texnum = -1;
  }
}

// FUNC: public: virtual void __thiscall idPBufferImage::Reload(bool,bool)
void __thiscall idPBufferImage::Reload(idPBufferImage *this, bool checkPrecompressed, bool force)
{
  rvTexRenderTarget *mRenderTarget; // ecx

  mRenderTarget = this->mRenderTarget;
  if ( mRenderTarget )
  {
    rvTexRenderTarget::Restore(mRenderTarget);
    rvTexRenderTarget::DefaultD3GL(this->mRenderTarget);
    qglGenTextures(1, &this->texnum);
  }
}

// FUNC: public: void __thiscall idImage::GenerateCubeImage(unsigned char const * * const,int,enum textureFilter_t,bool,enum textureDepth_t)
void __thiscall idImage::GenerateCubeImage(
        idImage *this,
        const unsigned __int8 **pic,
        int size,
        textureFilter_t filterParm,
        bool allowDownSizeParm,
        int depthParm)
{
  int v7; // eax
  idImage_vtbl *v8; // edx
  textureFilter_t filter; // eax
  __int32 v10; // eax
  int i; // edi
  int j; // edi
  int v13; // esi
  int v14; // ebp
  int k; // eax
  unsigned __int8 *v16; // edi
  float v17; // [esp+0h] [ebp-2Ch]
  float v18; // [esp+0h] [ebp-2Ch]
  unsigned __int8 *shrunk[6]; // [esp+14h] [ebp-18h] BYREF
  unsigned __int8 *pica; // [esp+30h] [ebp+4h]
  int filterParma; // [esp+38h] [ebp+Ch]
  int scaled_height; // [esp+3Ch] [ebp+10h]
  int scaled_width; // [esp+40h] [ebp+14h]

  this->PurgeImage(this);
  this->filter = filterParm;
  this->allowDownSize = allowDownSizeParm;
  this->depth = depthParm;
  this->type = TT_CUBIC;
  if ( glConfig.isInitialized && glConfig.cubeMapAvailable )
  {
    qglGenTextures(1, &this->texnum);
    v7 = idImage::SelectInternalFormat(this, pic, 6, size, size, this->depth, 0, &this->isMonochrome);
    v8 = this->__vftable;
    this->internalFormat = v7;
    scaled_height = size;
    filterParma = size;
    this->uploadHeight = size;
    this->uploadWidth = size;
    v8->Bind(this);
    qglTexParameteri(0x8513u, 0x2802u, 33071);
    qglTexParameteri(0x8513u, 0x2803u, 33071);
    filter = this->filter;
    if ( filter )
    {
      v10 = filter - 1;
      if ( v10 )
      {
        if ( v10 == 1 )
        {
          v17 = (float)globalImages->GetTextureMinFilter(globalImages);
          qglTexParameterf(0x8513u, 0x2801u, v17);
          v18 = (float)globalImages->GetTextureMaxFilter(globalImages);
          qglTexParameterf(0x8513u, 0x2800u, v18);
        }
        else
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
            common.type,
            "R_CreateImage: bad texture filter");
        }
      }
      else
      {
        qglTexParameterf(0x8513u, 0x2801u, 9728.0);
        qglTexParameterf(0x8513u, 0x2800u, 9728.0);
      }
    }
    else
    {
      qglTexParameterf(0x8513u, 0x2801u, 9729.0);
      qglTexParameterf(0x8513u, 0x2800u, 9729.0);
    }
    for ( i = 0; i < 6; ++i )
      qglTexImage2D(i + 34069, 0, this->internalFormat, size, size, 0, 0x1908u, 0x1401u, pic[i]);
    for ( j = 0; j < 6; ++j )
      shrunk[j] = R_MipMap(*(unsigned __int8 **)((char *)&shrunk[j] + (char *)pic - (char *)shrunk), size, size, 0);
    scaled_width = 1;
    if ( size > 1 )
    {
      do
      {
        v13 = 0;
        v14 = filterParma / 2;
        for ( k = scaled_height / 2; ; k = scaled_height / 2 )
        {
          v16 = shrunk[v13];
          qglTexImage2D(v13 + 34069, scaled_width, this->internalFormat, k, v14, 0, 0x1908u, 0x1401u, v16);
          pica = scaled_height <= 2 ? 0 : R_MipMap(v16, scaled_height / 2, v14, 0);
          R_StaticFree(v16);
          shrunk[v13++] = pica;
          if ( v13 >= 6 )
            break;
        }
        filterParma >>= 1;
        ++scaled_width;
        scaled_height >>= 1;
      }
      while ( scaled_height > 1 );
    }
    GL_CheckErrors();
  }
}

// FUNC: public: void __thiscall idImage::UploadPrecompressedImage(unsigned char *,int,int,bool)
void __thiscall idImage::UploadPrecompressedImage(
        idImage *this,
        unsigned __int8 *data,
        int len,
        int target,
        bool deswizzle)
{
  idImage *v5; // edi
  unsigned __int8 *v6; // esi
  int v7; // eax
  int uploadHeight; // ebx
  int uploadWidth; // ebp
  int v10; // eax
  int v11; // eax
  int internalFormat; // eax
  int v13; // esi
  int v14; // eax
  int externalFormat; // [esp+8h] [ebp-18h]
  int skipMip; // [esp+Ch] [ebp-14h]
  unsigned __int8 *imagedata; // [esp+14h] [ebp-Ch]
  int i; // [esp+18h] [ebp-8h]
  int numMipmaps; // [esp+1Ch] [ebp-4h]

  v5 = this;
  if ( this->texnum == -1 )
    qglGenTextures(1, &this->texnum);
  v6 = data;
  v5->precompressedFile = 1;
  v5->uploadWidth = LittleLong(*((_DWORD *)data + 4));
  v5->uploadHeight = LittleLong(*((_DWORD *)data + 3));
  if ( (LittleLong(*((_DWORD *)data + 20)) & 4) != 0 )
  {
    v7 = LittleLong(*((_DWORD *)data + 21));
    if ( v7 > 894720068 )
    {
      if ( v7 != 1111971922 )
        goto LABEL_14;
    }
    else if ( v7 != 894720068 )
    {
      if ( v7 == 827611204 )
      {
        if ( (LittleLong(*((_DWORD *)data + 20)) & 1) != 0 )
          v5->internalFormat = 33777;
        else
          v5->internalFormat = 33776;
        externalFormat = v5->internalFormat;
        goto LABEL_28;
      }
      if ( v7 == 861165636 )
      {
        v5->internalFormat = 33778;
        externalFormat = v5->internalFormat;
        goto LABEL_28;
      }
LABEL_14:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "Invalid compressed internal format\n");
      return;
    }
    v5->internalFormat = 33779;
    externalFormat = v5->internalFormat;
    goto LABEL_28;
  }
  if ( (LittleLong(*((_DWORD *)data + 20)) & 0x41) != 0 && LittleLong(*((_DWORD *)data + 22)) == 32
    || (LittleLong(*((_DWORD *)data + 20)) & 0x40) != 0 && LittleLong(*((_DWORD *)data + 22)) == 32 )
  {
    externalFormat = 32993;
    v5->internalFormat = 32856;
  }
  else if ( (LittleLong(*((_DWORD *)data + 20)) & 0x40) != 0 && LittleLong(*((_DWORD *)data + 22)) == 24 )
  {
    if ( (LittleLong(*((_DWORD *)data + 20)) & 0x10000000) != 0 )
    {
      externalFormat = 6400;
      v5->internalFormat = 32997;
    }
    else
    {
      externalFormat = 32992;
      v5->internalFormat = 32849;
    }
  }
  else
  {
    if ( LittleLong(*((_DWORD *)data + 22)) != 8 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "Invalid uncompressed internal format\n");
      return;
    }
    externalFormat = 6406;
    v5->internalFormat = 32828;
  }
LABEL_28:
  if ( (LittleLong(*((_DWORD *)data + 2)) & 0x20000000) != 0 )
    v5->isMonochrome = 1;
  if ( target < 34069 || target > 34074 )
    v5->type = TT_2D;
  else
    v5->type = TT_CUBIC;
  v5->Bind(v5);
  numMipmaps = 1;
  if ( (LittleLong(*((_DWORD *)data + 2)) & 0x20000) != 0 )
    numMipmaps = LittleLong(*((_DWORD *)data + 7));
  uploadHeight = v5->uploadHeight;
  uploadWidth = v5->uploadWidth;
  skipMip = 0;
  idImage::GetDownsize(v5, &v5->uploadWidth, &v5->uploadHeight);
  if ( v5->isPartialImage )
  {
    while ( 1 )
    {
      v10 = v5->uploadWidth;
      if ( v10 <= 16 && v5->uploadHeight <= 16 )
        break;
      if ( v10 > 1 )
        v5->uploadWidth = v10 >> 1;
      v11 = v5->uploadHeight;
      if ( v11 > 1 )
        v5->uploadHeight = v11 >> 1;
    }
  }
  if ( v5->uploadWidth < 1 )
    v5->uploadWidth = 1;
  if ( v5->uploadHeight < 1 )
    v5->uploadHeight = 1;
  imagedata = data + 128;
  i = 0;
  if ( numMipmaps > 0 )
  {
    while ( 1 )
    {
      internalFormat = v5->internalFormat;
      if ( internalFormat < 33776 || internalFormat > 33779 )
      {
        v13 = uploadWidth * uploadHeight * (LittleLong(*((_DWORD *)v6 + 22)) / 8);
      }
      else
      {
        v5 = this;
        v13 = (uploadWidth + 3) / 4 * (uploadHeight + 3) / 4 * (8 * (internalFormat > 33777) + 8);
      }
      if ( uploadWidth > v5->uploadWidth || uploadHeight > v5->uploadHeight )
      {
        ++skipMip;
      }
      else
      {
        v14 = v5->internalFormat;
        if ( v14 < 33776 || v14 > 33779 )
        {
          qglTexImage2D(target, i - skipMip, v14, uploadWidth, uploadHeight, 0, externalFormat, 0x1401u, imagedata);
        }
        else
        {
          qglCompressedTexImage2DARB(target, i - skipMip, v14, uploadWidth, uploadHeight, 0, v13, imagedata);
          if ( deswizzle )
            idImage::DeswizzleAndUploadPalettisedNormalMap(this, uploadWidth, uploadHeight, i - skipMip);
          v5 = this;
        }
      }
      imagedata += v13;
      uploadWidth /= 2;
      uploadHeight /= 2;
      if ( uploadWidth < 1 )
        uploadWidth = 1;
      if ( uploadHeight < 1 )
        uploadHeight = 1;
      if ( ++i >= numMipmaps )
        break;
      v6 = data;
    }
  }
  idImage::SetImageFilterAndRepeat(v5);
}

// FUNC: public: void __thiscall idImage::CopyFramebuffer(int,int,int,int,bool)
void __thiscall idImage::CopyFramebuffer(
        idImage *this,
        int x,
        int y,
        int imageWidth,
        int imageHeight,
        void *useOversizedBuffer)
{
  idImage_vtbl *v7; // eax
  int v8; // ebx
  int v9; // ebp
  int v10; // edi
  int v11; // esi
  int i; // eax
  int j; // eax
  idImage *v14; // eax
  int v15; // esi
  int v16; // edi
  int v17; // esi
  void *v18; // [esp-4h] [ebp-20h]
  int potWidth; // [esp+10h] [ebp-Ch] BYREF
  int potHeight; // [esp+14h] [ebp-8h] BYREF
  idImage *v21; // [esp+18h] [ebp-4h]

  v7 = this->__vftable;
  v21 = this;
  ((void (__fastcall *)(idImage *))v7->Bind)(this);
  if ( cvarSystem->GetCVarBool(cvarSystem, "g_lowresFullscreenFX") )
  {
    v8 = 512;
    v9 = 512;
    imageWidth = 512;
    imageHeight = 512;
  }
  else
  {
    v9 = imageHeight;
    v8 = imageWidth;
  }
  if ( glConfig.textureNonPowerOfTwoAvailable )
  {
    v10 = v8;
    v11 = v9;
    potWidth = v8;
    potHeight = v9;
  }
  else
  {
    for ( i = 1; i < v8; i *= 2 )
      ;
    potWidth = i;
    for ( j = 1; j < v9; j *= 2 )
      ;
    potHeight = j;
    idImage::GetDownsize(this, &imageWidth, &imageHeight);
    idImage::GetDownsize(this, &potWidth, &potHeight);
    v9 = imageHeight;
    v8 = imageWidth;
    v11 = potHeight;
    v10 = potWidth;
  }
  qglReadBuffer(0x405u);
  if ( (_BYTE)useOversizedBuffer )
  {
    v14 = v21;
    if ( v21->uploadWidth >= v10 && v21->uploadHeight >= v11 )
    {
LABEL_14:
      v15 = y;
      v16 = x;
      qglCopyTexSubImage2D(0xDE1u, 0, 0, 0, x, y, v8, v9);
      goto LABEL_15;
    }
  }
  else
  {
    if ( v21->uploadWidth == v10 && v21->uploadHeight == v11 )
      goto LABEL_14;
    v14 = v21;
  }
  v14->uploadWidth = v10;
  v14->uploadHeight = v11;
  if ( v10 == v8 && v11 == v9 )
  {
    v15 = y;
    v16 = x;
    qglCopyTexImage2D(0xDE1u, 0, 0x8058u, x, y, v8, v9, 0);
  }
  else
  {
    v17 = 4 * v10 * v11;
    v18 = Mem_Alloc(v17, 0xCu);
    memset(v18, 0, v17);
    useOversizedBuffer = v18;
    qglTexImage2D(0xDE1u, 0, 6408, potWidth, potHeight, 0, 0x1908u, 0x1401u, v18);
    Mem_Free(useOversizedBuffer);
    v15 = y;
    v16 = x;
    qglCopyTexSubImage2D(0xDE1u, 0, 0, 0, x, y, v8, v9);
    v8 = potWidth;
    v9 = potHeight;
  }
LABEL_15:
  if ( !glConfig.textureNonPowerOfTwoAvailable )
  {
    if ( v8 != potWidth )
      qglCopyTexSubImage2D(0xDE1u, 0, v8, 0, v16 + v8 - 1, v15, 1, v9);
    if ( v9 != potHeight )
      qglCopyTexSubImage2D(0xDE1u, 0, 0, v9, v16, v15 + v9 - 1, v8, 1);
  }
  idImage::SetImageFilterAndRepeat(v21);
  qglTexParameterf(0xDE1u, 0x2801u, 9729.0);
  qglTexParameterf(0xDE1u, 0x2800u, 9729.0);
  ++backEnd.c_copyFrameBuffer;
}

// FUNC: public: void __thiscall idImage::Print(void)const
void __thiscall idImage::Print(idImage *this)
{
  textureFilter_t filter; // eax
  __int32 v3; // eax
  int internalFormat; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax

  if ( this->precompressedFile )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "P");
  }
  else if ( this->generatorFunction )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "F");
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " ");
  }
  switch ( this->type )
  {
    case TT_2D:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " ");
      break;
    case TT_3D:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "3");
      break;
    case TT_CUBIC:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "C");
      break;
    case TT_RECT:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "R");
      break;
    default:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "<BAD TYPE:%i>",
        this->type);
      break;
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%4i %4i ",
    this->uploadWidth,
    this->uploadHeight);
  filter = this->filter;
  if ( filter )
  {
    v3 = filter - 1;
    if ( v3 )
    {
      if ( v3 == 1 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "dflt ");
      else
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "<BAD FILTER:%i>",
          this->filter);
    }
    else
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "nrst ");
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "linr ");
  }
  internalFormat = this->internalFormat;
  if ( internalFormat > 6400 )
  {
    if ( internalFormat > 32856 )
    {
      if ( internalFormat > 33778 )
      {
        v7 = internalFormat - 33779;
        if ( !v7 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "DXT5  ");
          goto LABEL_53;
        }
        v8 = v7 - 250;
        if ( !v8 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "RGBC  ");
          goto LABEL_53;
        }
        if ( v8 == 1 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "RGBAC ");
          goto LABEL_53;
        }
      }
      else
      {
        if ( internalFormat == 33778 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "DXT3  ");
          goto LABEL_53;
        }
        v5 = internalFormat - 32997;
        if ( !v5 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "CI8   ");
          goto LABEL_53;
        }
        v6 = v5 - 779;
        if ( !v6 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "DXT1  ");
          goto LABEL_53;
        }
        if ( v6 == 1 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "DXT1A ");
          goto LABEL_53;
        }
      }
LABEL_49:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "<BAD FORMAT:%i>",
        this->internalFormat);
      goto LABEL_53;
    }
    if ( internalFormat == 32856 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "RGBA8 ");
    }
    else
    {
      switch ( internalFormat )
      {
        case 32828:
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "A     ");
          break;
        case 32832:
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "L     ");
          break;
        case 32837:
$L114728:
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "LA    ");
          break;
        case 32843:
$L114726:
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "I     ");
          break;
        case 32848:
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "RGB5  ");
          break;
        case 32849:
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "RGB8  ");
          break;
        case 32854:
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "RGBA4 ");
          break;
        default:
          goto LABEL_49;
      }
    }
  }
  else if ( internalFormat == 6400 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "CI    ");
  }
  else
  {
    switch ( internalFormat )
    {
      case 0:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "      ");
        break;
      case 1:
        goto $L114726;
      case 2:
        goto $L114728;
      case 3:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "RGB   ");
        break;
      case 4:
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "RGBA  ");
        break;
      default:
        goto LABEL_49;
    }
  }
LABEL_53:
  switch ( this->repeat )
  {
    case TR_REPEAT:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "rept ");
      break;
    case TR_CLAMP:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "clmp ");
      break;
    case TR_CLAMP_TO_ZERO:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "zero ");
      break;
    case TR_CLAMP_TO_ZERO_ALPHA:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "azro ");
      break;
    default:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "<BAD REPEAT:%i>",
        this->repeat);
      break;
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%5i ", this->useCount);
  v9 = *(_DWORD *)common.type;
  v10 = idImage::StorageSize(this);
  (*(void (**)(netadrtype_t, const char *, ...))(v9 + 124))(common.type, "%4ik ", v10 / 1024);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    " %s\n",
    this->imgName.data);
}

// FUNC: public: static unsigned long __cdecl idImage::ImageNameCRC32(char const *)
unsigned int __cdecl idImage::ImageNameCRC32(const char *fullImageName)
{
  char *baseBuffer; // ecx
  const char *v2; // eax
  int v3; // esi
  const char *v4; // edx
  char v5; // al
  unsigned __int8 v6; // al
  int v7; // esi
  bool v8; // zf
  unsigned int v9; // esi
  idStr fixed; // [esp+8h] [ebp-2Ch] BYREF
  int v12; // [esp+30h] [ebp-4h]

  baseBuffer = fixed.baseBuffer;
  fixed.len = 0;
  fixed.alloced = 20;
  fixed.data = fixed.baseBuffer;
  fixed.baseBuffer[0] = 0;
  if ( fullImageName )
  {
    v2 = &fullImageName[strlen(fullImageName) + 1];
    v3 = v2 - (fullImageName + 1);
    if ( v2 - fullImageName > 20 )
    {
      idStr::ReAllocate(&fixed, v2 - fullImageName, 1);
      baseBuffer = fixed.data;
    }
    v4 = fullImageName;
    do
    {
      v5 = *v4;
      *baseBuffer++ = *v4++;
    }
    while ( v5 );
    baseBuffer = fixed.data;
    fixed.len = v3;
  }
  v6 = *baseBuffer;
  v7 = 0;
  v8 = *baseBuffer == 0;
  v12 = 0;
  if ( !v8 )
  {
    do
    {
      if ( idStr::lowerCaseCharacter[v6] )
        v6 = idStr::lowerCaseCharacter[v6];
      *baseBuffer = v6;
      baseBuffer = &fixed.data[++v7];
      v6 = fixed.data[v7];
    }
    while ( v6 );
  }
  idStr::Replace(&fixed, " ", &entityFilter);
  v9 = CRC32_BlockChecksum(fixed.data, fixed.len);
  v12 = -1;
  idStr::FreeData(&fixed);
  return v9;
}

// FUNC: public: static void __cdecl idImage::ImageNamePlusCRC32(char const *,unsigned long,char *)
void __cdecl idImage::ImageNamePlusCRC32(const char *filename, unsigned int crc32, char *dest)
{
  const char *v3; // eax
  int v4; // edi
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  const char *v9; // eax
  int v10; // edi
  int v11; // eax
  char *v12; // edx
  const char *v13; // ecx
  char v14; // al
  const idStr *v15; // eax
  const idStr *v16; // esi
  const char *v17; // eax
  char *v18; // eax
  int v19; // edx
  char v20; // cl
  idStr v21; // [esp+10h] [ebp-ACh] BYREF
  idStr file; // [esp+30h] [ebp-8Ch] BYREF
  idStr path; // [esp+50h] [ebp-6Ch] BYREF
  idStr final; // [esp+70h] [ebp-4Ch] BYREF
  idStr result; // [esp+90h] [ebp-2Ch] BYREF
  int v26; // [esp+B8h] [ebp-4h]

  path.len = 0;
  path.alloced = 20;
  path.data = path.baseBuffer;
  path.baseBuffer[0] = 0;
  v26 = 1;
  file.len = 0;
  file.alloced = 20;
  file.data = file.baseBuffer;
  file.baseBuffer[0] = 0;
  v21.len = 0;
  v21.alloced = 20;
  v21.data = v21.baseBuffer;
  v21.baseBuffer[0] = 0;
  if ( filename )
  {
    v3 = &filename[strlen(filename) + 1];
    v4 = v3 - (filename + 1);
    v5 = v3 - filename;
    if ( v5 > 20 )
      idStr::ReAllocate(&v21, v5, 1);
    data = v21.data;
    v7 = filename;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    v21.len = v4;
  }
  LOBYTE(v26) = 2;
  idStr::ExtractFilePath(&v21, &path);
  LOBYTE(v26) = 1;
  idStr::FreeData(&v21);
  v21.len = 0;
  v21.alloced = 20;
  v21.data = v21.baseBuffer;
  v21.baseBuffer[0] = 0;
  if ( filename )
  {
    v9 = &filename[strlen(filename) + 1];
    v10 = v9 - (filename + 1);
    v11 = v9 - filename;
    if ( v11 > 20 )
      idStr::ReAllocate(&v21, v11, 1);
    v12 = v21.data;
    v13 = filename;
    do
    {
      v14 = *v13;
      *v12++ = *v13++;
    }
    while ( v14 );
    v21.len = v10;
  }
  LOBYTE(v26) = 3;
  idStr::ExtractFileName(&v21, &file);
  LOBYTE(v26) = 1;
  idStr::FreeData(&v21);
  idStr::StripAbsoluteFileExtension(&file);
  v15 = idStr::Left(&file, &result, 33);
  LOBYTE(v26) = 4;
  v16 = operator+(&v21, &path, v15);
  LOBYTE(v26) = 5;
  v17 = va("_%08x", crc32);
  operator+(&final, v16, v17);
  LOBYTE(v26) = 8;
  idStr::FreeData(&v21);
  LOBYTE(v26) = 7;
  idStr::FreeData(&result);
  v18 = final.data;
  v19 = dest - final.data;
  do
  {
    v20 = *v18;
    v18[v19] = *v18;
    ++v18;
  }
  while ( v20 );
  LOBYTE(v26) = 1;
  idStr::FreeData(&final);
  LOBYTE(v26) = 0;
  idStr::FreeData(&file);
  v26 = -1;
  idStr::FreeData(&path);
}

// FUNC: public: void __thiscall idImage::WritePrecompressedImage(char const *,int,int)
void __thiscall idImage::WritePrecompressedImage(
        idImage *this,
        const char *imageName,
        char *textureTarget,
        unsigned __int8 *cubeFlag)
{
  int v5; // eax
  int uploadWidth; // ecx
  int internalFormat; // ecx
  int v8; // ebx
  int integerValue; // eax
  bool v10; // zf
  int v11; // kr04_4
  char *v12; // edx
  char *v13; // ecx
  char v14; // al
  idFile *v15; // ebx
  char *v16; // eax
  char *v17; // eax
  unsigned int v18; // kr14_4
  int v19; // eax
  void *v20; // esp
  int uploadHeight; // eax
  int v22; // ecx
  char *v23; // ebx
  char *v24; // eax
  int v25; // edx
  char *v26; // ecx
  char v27; // al
  _BYTE *v28; // eax
  int v29; // ebx
  int v30; // eax
  char *v31; // edx
  char *v32; // ecx
  char v33; // al
  int len; // edi
  char *v35; // ecx
  char *v36; // edx
  char v37; // al
  idImageManager_vtbl *v38; // eax
  const char *v39; // esi
  int v40; // eax
  unsigned int v41; // eax
  int v42; // ebx
  int v43; // eax
  char *v44; // edx
  const char *v45; // ecx
  char v46; // al
  int v47; // esi
  int v48; // eax
  char *v49; // ecx
  char *v50; // edx
  char v51; // al
  idImageManager_vtbl *v52; // esi
  char *v53; // eax
  int v54; // kr18_4
  char *v55; // edx
  char *v56; // ecx
  char v57; // al
  idFile *v58; // ebx
  char *v59; // eax
  char *v60; // eax
  unsigned int v61; // kr1C_4
  int v62; // eax
  void *v63; // esp
  int v64; // eax
  char v65; // cl
  int v66; // ecx
  int v67; // edx
  char *v68; // ebx
  char *v69; // eax
  int v70; // edi
  int v71; // eax
  char *v72; // edx
  char *v73; // ecx
  char v74; // al
  _BYTE *v75; // eax
  int v76; // ebx
  int v77; // eax
  char *v78; // edx
  char *v79; // ecx
  char v80; // al
  int v81; // edi
  char *v82; // ecx
  char *v83; // edx
  char v84; // al
  idImageManager_vtbl *v85; // edx
  int v86; // eax
  int v87; // ecx
  int v88; // edi
  bool IsDXT; // al
  int v90; // ecx
  int v91; // edi
  int v92; // ecx
  unsigned int v93; // eax
  int v94; // ebx
  int v95; // ebx
  int v96; // ebx
  netadrtype_t type; // eax
  int v98; // ecx
  idFile *v99; // edi
  int v100; // edi
  int v101; // ebx
  int v102; // ecx
  int v103; // esi
  unsigned __int8 *v104; // eax
  idStr v105; // [esp-70h] [ebp-228h] BYREF
  idStr v106; // [esp-50h] [ebp-208h] BYREF
  idStr v107; // [esp-30h] [ebp-1E8h] BYREF
  int v108; // [esp-10h] [ebp-1C8h]
  int v109; // [esp-Ch] [ebp-1C4h]
  const char *v110; // [esp-8h] [ebp-1C0h]
  char *v111; // [esp-4h] [ebp-1BCh]
  char v112; // [esp+0h] [ebp-1B8h] BYREF
  _BYTE v113[11]; // [esp+1h] [ebp-1B7h] BYREF
  char filename[256]; // [esp+Ch] [ebp-1ACh] BYREF
  ddsFileHeader_t header; // [esp+10Ch] [ebp-ACh] BYREF
  idStr v116; // [esp+188h] [ebp-30h] BYREF
  idStr format; // [esp+1A8h] [ebp-10h] BYREF
  idFile *f; // [esp+1C8h] [ebp+10h]
  idStr source; // [esp+1CCh] [ebp+14h] BYREF
  idStr relative; // [esp+1ECh] [ebp+34h] BYREF
  int numLevels; // [esp+20Ch] [ebp+54h]
  int bitSize; // [esp+210h] [ebp+58h]
  int level; // [esp+214h] [ebp+5Ch]
  int v124; // [esp+220h] [ebp+68h]
  int altInternalFormat; // [esp+22Ch] [ebp+74h]
  unsigned __int8 *data; // [esp+234h] [ebp+7Ch]
  unsigned __int8 *dataa; // [esp+234h] [ebp+7Ch]

  if ( !com_Bundler.internalVar->integerValue
    && (!image_writePrecompressedTextures.internalVar->integerValue
     || !image_usePrecompressedTextures.internalVar->integerValue)
    || !glConfig.isInitialized )
  {
    return;
  }
  if ( imageName )
  {
    idImage::ImageProgramStringToCompressedFileName(this, imageName, filename);
    v111 = (char *)imageName;
  }
  else
  {
    idImage::ImageProgramStringToCompressedFileName(this, this->imgName.data, filename);
    v111 = this->imgName.data;
  }
  v5 = idImage::ImageNameCRC32(v111);
  uploadWidth = this->uploadWidth;
  level = v5;
  numLevels = idImage::NumLevelsForImageSize(this, uploadWidth, this->uploadHeight);
  if ( numLevels > 14 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "R_WritePrecompressedImage: level > MAX_TEXTURE_LEVELS for image %s",
      filename);
    return;
  }
  internalFormat = this->internalFormat;
  bitSize = 0;
  if ( internalFormat > 32832 )
  {
    switch ( internalFormat )
    {
      case 32837:
      case 32856:
        goto $L114184;
      case 32843:
      case 32849:
        goto $L114183;
      case 32997:
        goto $L114182;
      default:
        goto LABEL_16;
    }
  }
  if ( internalFormat == 32832 )
    goto $L114183;
  if ( internalFormat > 4 )
  {
    if ( internalFormat == 6400 )
    {
$L114182:
      v8 = 6400;
      bitSize = 24;
      goto LABEL_32;
    }
    if ( internalFormat == 32828 )
    {
      v8 = 6406;
      bitSize = 8;
      goto LABEL_32;
    }
    goto LABEL_16;
  }
  if ( internalFormat == 4 )
  {
$L114184:
    v8 = 32993;
    bitSize = 32;
    goto LABEL_32;
  }
  if ( internalFormat == 1 || internalFormat == 3 )
  {
$L114183:
    v8 = 32992;
    bitSize = 24;
    goto LABEL_32;
  }
LABEL_16:
  if ( internalFormat < 33776 || internalFormat > 33779 )
  {
    type = common.type;
    v98 = *(_DWORD *)common.type;
    v111 = filename;
    v110 = "Unknown or unsupported format for %s";
    goto LABEL_157;
  }
  if ( !com_Bundler.internalVar->integerValue
    || internalFormat != 33779
    || idStr::Cmpn(this->imgName.data, "fonts", 5)
    && idStr::Cmpn(this->imgName.data, "gfx/2d", 6)
    && idStr::Cmpn(this->imgName.data, "gfx/guis", 8) )
  {
    v8 = this->internalFormat;
  }
  else
  {
    v8 = 33778;
    this->internalFormat = 33778;
  }
LABEL_32:
  integerValue = com_Bundler.internalVar->integerValue;
  altInternalFormat = v8;
  if ( (integerValue || image_useOffLineCompression.internalVar->integerValue) && v8 >= 33776 && v8 <= 33779 )
  {
    format.len = 0;
    format.alloced = 20;
    format.data = format.baseBuffer;
    format.baseBuffer[0] = 0;
    v10 = this->depth == TD_BUMP;
    v124 = 0;
    if ( v10 )
    {
      if ( com_Bundler.internalVar->integerValue )
        v111 = "DXN";
      else
        v111 = "RXGB +red 0.0 +green 0.5 +blue 0.5";
LABEL_45:
      idStr::operator=(&format, v111);
    }
    else
    {
      switch ( v8 )
      {
        case 33776:
          v111 = "DXT1";
          goto LABEL_45;
        case 33777:
          v111 = "DXT1 -alpha_threshold";
          goto LABEL_45;
        case 33778:
          v111 = "DXT3";
          goto LABEL_45;
        case 33779:
          v111 = "DXT5";
          goto LABEL_45;
        default:
          break;
      }
    }
    if ( com_Bundler.internalVar->integerValue )
    {
      source.len = 0;
      source.alloced = 20;
      source.data = source.baseBuffer;
      source.baseBuffer[0] = 0;
      relative.data = relative.baseBuffer;
      LOBYTE(v124) = 1;
      relative.len = 0;
      relative.alloced = 20;
      relative.baseBuffer[0] = 0;
      v11 = strlen(filename);
      if ( v11 + 1 > 20 )
        idStr::ReAllocate(&relative, v11 + 1, 1);
      v12 = relative.data;
      v13 = filename;
      do
      {
        v14 = *v13;
        *v12++ = *v13++;
      }
      while ( v14 );
      relative.len = v11;
      LOBYTE(v124) = 2;
      idStr::StripFileExtension(&relative);
      idStr::SetFileExtension(&relative, "tga");
      v15 = fileSystem->OpenFileRead(fileSystem, relative.data, 0, 0);
      if ( v15 )
      {
        v16 = (char *)v15->GetFullPath(v15);
        idStr::operator=(&source, v16);
        fileSystem->CloseFile(fileSystem, v15);
      }
      else
      {
        v17 = (char *)fileSystem->RelativePathToOSPath(fileSystem, relative.data, "fs_savepath");
        idStr::operator=(&source, v17);
      }
      idStr::StripFileExtension(&source);
      v18 = strlen(filename);
      v19 = v18 + 19;
      LOBYTE(v19) = (v18 + 19) & 0xFC;
      v20 = alloca(v19);
      idImage::ImageNamePlusCRC32(filename, level, &v112);
      uploadHeight = this->uploadHeight;
      v22 = this->uploadWidth;
      v23 = format.data;
      v111 = (char *)cubeFlag;
      v110 = (const char *)uploadHeight;
      v109 = v22;
      v108 = numLevels;
      v107.len = 0;
      v107.alloced = 20;
      v107.data = v107.baseBuffer;
      v107.baseBuffer[0] = 0;
      if ( format.data )
      {
        v24 = &format.data[strlen(format.data) + 1];
        v25 = v24 - (format.data + 1);
        data = (unsigned __int8 *)v25;
        if ( v24 - format.data > v107.alloced )
        {
          idStr::ReAllocate(&v107, v24 - format.data, 1);
          v25 = (int)data;
        }
        v26 = v107.data;
        do
        {
          v27 = *v23;
          *v26++ = *v23++;
        }
        while ( v27 );
        v107.len = v25;
      }
      v106.len = 0;
      v106.alloced = 20;
      v106.data = v106.baseBuffer;
      LOBYTE(v124) = 3;
      v106.baseBuffer[0] = 0;
      if ( &v112 )
      {
        v28 = &v113[strlen(&v112)];
        v29 = v28 - v113;
        v30 = v28 - &v112;
        if ( v30 > v106.alloced )
          idStr::ReAllocate(&v106, v30, 1);
        v31 = v106.data;
        v32 = &v112;
        do
        {
          v33 = *v32;
          *v31++ = *v32++;
        }
        while ( v33 );
        v106.len = v29;
      }
      v105.alloced = 20;
      v105.data = v105.baseBuffer;
      v105.len = 0;
      v105.baseBuffer[0] = 0;
      len = source.len;
      LOBYTE(v124) = 4;
      if ( source.len + 1 > 20 )
        idStr::ReAllocate(&v105, source.len + 1, 1);
      v35 = source.data;
      v36 = v105.data;
      do
      {
        v37 = *v35;
        *v36++ = *v35++;
      }
      while ( v37 );
      v105.len = len;
      v38 = globalImages->__vftable;
      LOBYTE(v124) = 2;
      ((void (__fastcall *)(idImageManager *, char *, int, char *, int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int, char *, int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int, char *, int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int, int, const char *, char *))v38->AddXMLElement)(
        globalImages,
        v36,
        len,
        v105.data,
        v105.alloced,
        *(_DWORD *)v105.baseBuffer,
        *(_DWORD *)&v105.baseBuffer[4],
        *(_DWORD *)&v105.baseBuffer[8],
        *(_DWORD *)&v105.baseBuffer[12],
        *(_DWORD *)&v105.baseBuffer[16],
        v106.len,
        v106.data,
        v106.alloced,
        *(_DWORD *)v106.baseBuffer,
        *(_DWORD *)&v106.baseBuffer[4],
        *(_DWORD *)&v106.baseBuffer[8],
        *(_DWORD *)&v106.baseBuffer[12],
        *(_DWORD *)&v106.baseBuffer[16],
        v107.len,
        v107.data,
        v107.alloced,
        *(_DWORD *)v107.baseBuffer,
        *(_DWORD *)&v107.baseBuffer[4],
        *(_DWORD *)&v107.baseBuffer[8],
        *(_DWORD *)&v107.baseBuffer[12],
        *(_DWORD *)&v107.baseBuffer[16],
        v108,
        v109,
        v110,
        v111);
      LOBYTE(v124) = 1;
    }
    else
    {
      v39 = fileSystem->RelativePathToOSPath(fileSystem, filename, "fs_savepath");
      v40 = 0;
      source.len = 0;
      source.alloced = 20;
      source.data = source.baseBuffer;
      source.baseBuffer[0] = 0;
      if ( v39 )
      {
        v41 = (unsigned int)&v39[strlen(v39) + 1];
        v42 = v41 - (_DWORD)(v39 + 1);
        v43 = v41 - (_DWORD)v39;
        if ( v43 > 20 )
          idStr::ReAllocate(&source, v43, 1);
        v44 = source.data;
        v45 = v39;
        do
        {
          v46 = *v45;
          *v44++ = *v45++;
        }
        while ( v46 );
        v40 = v42;
        source.len = v42;
      }
      v47 = v40;
      v48 = v40 + 1;
      LOBYTE(v124) = 5;
      relative.len = 0;
      relative.alloced = 20;
      relative.data = relative.baseBuffer;
      relative.baseBuffer[0] = 0;
      if ( v48 > 20 )
        idStr::ReAllocate(&relative, v48, 1);
      v49 = source.data;
      v50 = relative.data;
      do
      {
        v51 = *v49;
        *v50++ = *v49++;
      }
      while ( v51 );
      relative.len = v47;
      LOBYTE(v124) = 6;
      idStr::StripFileExtension(&relative);
      idStr::SetFileExtension(&relative, "tga");
      v52 = globalImages->__vftable;
      v53 = va("thecompressonator -convert \"%s\" \"%s\" %s -mipmaps", relative.data, source.data, format.data);
      v52->AddDDSCommand(globalImages, v53);
      LOBYTE(v124) = 5;
    }
    idStr::FreeData(&relative);
    LOBYTE(v124) = 0;
    idStr::FreeData(&source);
    v124 = -1;
    idStr::FreeData(&format);
    return;
  }
  if ( integerValue )
  {
    source.len = 0;
    source.alloced = 20;
    source.data = source.baseBuffer;
    source.baseBuffer[0] = 0;
    relative.len = 0;
    relative.baseBuffer[0] = 0;
    relative.data = relative.baseBuffer;
    v124 = 7;
    relative.alloced = 20;
    v54 = strlen(filename);
    if ( v54 + 1 > 20 )
      idStr::ReAllocate(&relative, v54 + 1, 1);
    v55 = relative.data;
    v56 = filename;
    do
    {
      v57 = *v56;
      *v55++ = *v56++;
    }
    while ( v57 );
    relative.len = v54;
    LOBYTE(v124) = 8;
    idStr::StripFileExtension(&relative);
    idStr::SetFileExtension(&relative, "tga");
    v58 = fileSystem->OpenFileRead(fileSystem, relative.data, 0, 0);
    if ( v58 )
    {
      v59 = (char *)v58->GetFullPath(v58);
      idStr::operator=(&source, v59);
      fileSystem->CloseFile(fileSystem, v58);
    }
    else
    {
      v60 = (char *)fileSystem->RelativePathToOSPath(fileSystem, relative.data, "fs_savepath");
      idStr::operator=(&source, v60);
    }
    idStr::StripFileExtension(&source);
    v61 = strlen(filename);
    v62 = v61 + 19;
    LOBYTE(v62) = (v61 + 19) & 0xFC;
    v63 = alloca(v62);
    idImage::ImageNamePlusCRC32(filename, level, &v112);
    v116.alloced = 20;
    v116.data = v116.baseBuffer;
    v116.baseBuffer[0] = 0;
    v64 = 0;
    do
    {
      v65 = aA8r8g8b8[v64];
      v116.baseBuffer[v64++] = v65;
    }
    while ( v65 );
    v116.len = 8;
    v66 = this->uploadHeight;
    v67 = this->uploadWidth;
    v68 = v116.data;
    v111 = (char *)cubeFlag;
    v110 = (const char *)v66;
    v109 = v67;
    v108 = numLevels;
    v107.len = 0;
    v107.alloced = 20;
    v107.data = v107.baseBuffer;
    LOBYTE(v124) = 9;
    v107.baseBuffer[0] = 0;
    if ( v116.data )
    {
      v69 = &v116.data[strlen(v116.data) + 1];
      v70 = v69 - (v116.data + 1);
      v71 = v69 - v116.data;
      if ( v71 > v107.alloced )
        idStr::ReAllocate(&v107, v71, 1);
      v72 = v107.data;
      v73 = v68;
      do
      {
        v74 = *v73;
        *v72++ = *v73++;
      }
      while ( v74 );
      v107.len = v70;
    }
    v106.len = 0;
    v106.alloced = 20;
    v106.data = v106.baseBuffer;
    LOBYTE(v124) = 10;
    v106.baseBuffer[0] = 0;
    if ( &v112 )
    {
      v75 = &v113[strlen(&v112)];
      v76 = v75 - v113;
      v77 = v75 - &v112;
      if ( v77 > v106.alloced )
        idStr::ReAllocate(&v106, v77, 1);
      v78 = v106.data;
      v79 = &v112;
      do
      {
        v80 = *v79;
        *v78++ = *v79++;
      }
      while ( v80 );
      v106.len = v76;
    }
    v105.alloced = 20;
    v105.data = v105.baseBuffer;
    v105.len = 0;
    v105.baseBuffer[0] = 0;
    v81 = source.len;
    LOBYTE(v124) = 11;
    if ( source.len + 1 > 20 )
      idStr::ReAllocate(&v105, source.len + 1, 1);
    v82 = source.data;
    v83 = v105.data;
    do
    {
      v84 = *v82;
      *v83++ = *v82++;
    }
    while ( v84 );
    v105.len = v81;
    v85 = globalImages->__vftable;
    LOBYTE(v124) = 9;
    ((void (__thiscall *)(idImageManager *, int, char *, int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int, char *, int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int, char *, int, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int, int, const char *, char *))v85->AddXMLElement)(
      globalImages,
      v81,
      v105.data,
      v105.alloced,
      *(_DWORD *)v105.baseBuffer,
      *(_DWORD *)&v105.baseBuffer[4],
      *(_DWORD *)&v105.baseBuffer[8],
      *(_DWORD *)&v105.baseBuffer[12],
      *(_DWORD *)&v105.baseBuffer[16],
      v106.len,
      v106.data,
      v106.alloced,
      *(_DWORD *)v106.baseBuffer,
      *(_DWORD *)&v106.baseBuffer[4],
      *(_DWORD *)&v106.baseBuffer[8],
      *(_DWORD *)&v106.baseBuffer[12],
      *(_DWORD *)&v106.baseBuffer[16],
      v107.len,
      v107.data,
      v107.alloced,
      *(_DWORD *)v107.baseBuffer,
      *(_DWORD *)&v107.baseBuffer[4],
      *(_DWORD *)&v107.baseBuffer[8],
      *(_DWORD *)&v107.baseBuffer[12],
      *(_DWORD *)&v107.baseBuffer[16],
      v108,
      v109,
      v110,
      v111);
    LOBYTE(v124) = 8;
    idStr::FreeData(&v116);
    LOBYTE(v124) = 7;
    idStr::FreeData(&relative);
    v124 = -1;
    idStr::FreeData(&source);
    return;
  }
  v10 = !this->isMonochrome;
  memset(&header, 0, sizeof(header));
  v86 = this->uploadHeight;
  v87 = this->uploadWidth;
  header.dwSize = 124;
  v88 = 4103;
  header.dwHeight = v86;
  header.dwWidth = v87;
  if ( !v10 )
    v88 = 536875015;
  IsDXT = FormatIsDXT(v8);
  if ( IsDXT )
  {
    v91 = v88 | 0x80000;
    v92 = (8 * (v8 > 33777) + 8) * (this->uploadHeight + 3) / 4 * ((v90 + 3) / 4);
  }
  else
  {
    v91 = v88 | 8;
    v92 = ((bitSize * v90 + 31) >> 3) & 0xFFFFFFFC;
  }
  header.dwPitchOrLinearSize = v92;
  header.dwFlags = v91;
  header.dwCaps1 = 4096;
  if ( numLevels > 1 )
  {
    header.dwMipMapCount = numLevels;
    header.dwFlags = v91 | 0x20000;
    header.dwCaps1 = 4198408;
  }
  header.ddspf.dwSize = 32;
  if ( !IsDXT )
  {
    v93 = this->internalFormat != 32997 ? 64 : 268435520;
    header.ddspf.dwFlags = v93;
    header.ddspf.dwRGBBitCount = bitSize;
    if ( v8 > 6410 )
    {
      v96 = v8 - 32992;
      if ( !v96 )
        goto LABEL_134;
      if ( v96 != 1 )
        goto LABEL_132;
    }
    else if ( v8 != 6410 )
    {
      v94 = v8 - 6400;
      if ( v94 )
      {
        v95 = v94 - 6;
        if ( !v95 )
        {
          header.ddspf.dwFlags = 1;
          header.ddspf.dwABitMask = -16777216;
          goto LABEL_135;
        }
        if ( v95 != 3 )
        {
LABEL_132:
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "Unknown or unsupported format for %s",
            filename);
          return;
        }
      }
LABEL_134:
      header.ddspf.dwRBitMask = 16711680;
      header.ddspf.dwGBitMask = 65280;
      header.ddspf.dwBBitMask = 255;
      goto LABEL_135;
    }
    LOBYTE(v93) = v93 | 1;
    header.ddspf.dwABitMask = -16777216;
    header.ddspf.dwFlags = v93;
    goto LABEL_134;
  }
  header.ddspf.dwFlags = 4;
  switch ( v8 )
  {
    case 33776:
      header.ddspf.dwFourCC = 827611204;
      break;
    case 33777:
      header.ddspf.dwFlags = 5;
      header.ddspf.dwFourCC = 827611204;
      break;
    case 33778:
      header.ddspf.dwFourCC = 861165636;
      break;
    case 33779:
      header.ddspf.dwFourCC = 894720068;
      break;
    default:
      break;
  }
LABEL_135:
  f = fileSystem->OpenFileWrite(fileSystem, filename, "fs_savepath", 0);
  type = common.type;
  v98 = *(_DWORD *)common.type;
  v111 = filename;
  if ( !f )
  {
    v110 = "Could not open %s trying to write precompressed image";
LABEL_157:
    (*(void (__cdecl **)(netadrtype_t, const char *, char *))(v98 + 136))(type, v110, v111);
    return;
  }
  (*(void (**)(netadrtype_t, const char *, ...))(v98 + 124))(common.type, "Writing precompressed image: %s\n", v111);
  v99 = f;
  f->Write(f, "DDS ", 4);
  v99->Write(v99, &header, 124);
  this->Bind(this);
  qglPixelStorei(0xD05u, 1);
  v100 = this->uploadWidth;
  v101 = this->uploadHeight;
  dataa = 0;
  level = 0;
  if ( numLevels > 0 )
  {
    do
    {
      v102 = altInternalFormat;
      if ( altInternalFormat < 33776 || altInternalFormat > 33779 )
        v103 = v100 * v101 * (bitSize / 8);
      else
        v103 = (8 * (altInternalFormat > 33777) + 8) * (v100 + 3) / 4 * ((v101 + 3) / 4);
      if ( !dataa )
      {
        v104 = (unsigned __int8 *)R_StaticAlloc(v103);
        v102 = altInternalFormat;
        dataa = v104;
      }
      if ( v102 < 33776 || v102 > 33779 )
        qglGetTexImage((unsigned int)textureTarget, level, altInternalFormat, 0x1401u, dataa);
      else
        qglGetCompressedTexImageARB((unsigned int)textureTarget, level, dataa);
      f->Write(f, dataa, v103);
      v100 /= 2;
      v101 /= 2;
      if ( v100 < 1 )
        v100 = 1;
      if ( v101 < 1 )
        v101 = 1;
      ++level;
    }
    while ( level < numLevels );
    if ( dataa )
      R_StaticFree(dataa);
  }
  fileSystem->CloseFile(fileSystem, f);
}

// FUNC: public: void __thiscall idImage::WritePrecompressedCubeImages(char const *,enum cubeFiles_t,unsigned char * * const)
void __thiscall idImage::WritePrecompressedCubeImages(
        idImage *this,
        const char *imgName,
        cubeFiles_t extensions,
        unsigned __int8 **pics)
{
  char **v5; // eax
  const unsigned __int8 **v6; // edi
  int v7; // ebx
  int v8; // ebp
  char *v9; // eax
  char *axisSides[6]; // [esp+4h] [ebp-230h] BYREF
  char *cameraSides[6]; // [esp+1Ch] [ebp-218h] BYREF
  char fileName[256]; // [esp+34h] [ebp-200h] BYREF
  char fullName[256]; // [esp+134h] [ebp-100h] BYREF

  if ( !com_makingBuild.internalVar->integerValue
    || com_Bundler.internalVar->integerValue
    || image_writePrecompressedTextures.internalVar->integerValue
    && image_usePrecompressedTextures.internalVar->integerValue
    || image_writeProgramImages.internalVar->integerValue && gWriteProgramFlag )
  {
    cameraSides[0] = "_forward";
    cameraSides[1] = "_back";
    cameraSides[2] = "_left";
    cameraSides[3] = "_right";
    cameraSides[4] = "_up";
    cameraSides[5] = "_down";
    axisSides[0] = "_px";
    axisSides[1] = "_nx";
    axisSides[2] = "_py";
    axisSides[3] = "_ny";
    axisSides[4] = "_pz";
    axisSides[5] = "_nz";
    v5 = cameraSides;
    if ( extensions != CF_CAMERA )
      v5 = axisSides;
    v6 = (const unsigned __int8 **)pics;
    v7 = 0;
    v8 = (char *)v5 - (char *)pics;
    do
    {
      idStr::snPrintf(fullName, 256, "%s%s", imgName, *(const char **)((char *)v6 + v8));
      idImage::WritePrecompressedImage(
        this,
        fullName,
        (char *)(v7 + 34069),
        (unsigned __int8 *)(com_Bundler.internalVar->integerValue != 0));
      if ( !this->generatorFunction
        && (this->depth != TD_BUMP && image_writeTGA.internalVar->integerValue
         || image_writeProgramImages.internalVar->integerValue && gWriteProgramFlag) )
      {
        idImage::ImageProgramStringToCompressedFileName(this, fullName, fileName);
        strrchr((unsigned __int8 *)fileName, 0x2Eu);
        if ( v9 )
          strcpy(v9, ".tga");
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "Writing tga image: %s\n",
          fileName);
        R_WriteTGA(fileName, *v6, this->uploadWidth, this->uploadHeight, 0);
      }
      ++v7;
      ++v6;
    }
    while ( v7 < 6 );
  }
}

// FUNC: public: bool __thiscall idImage::ShouldImageBePartialCached(void)
bool __thiscall idImage::ShouldImageBePartialCached(idImage *this)
{
  unsigned int *p_timestamp; // esi
  idFile *v4; // eax
  idFile *v5; // esi
  int v6; // edi
  char filename[256]; // [esp+Ch] [ebp-100h] BYREF

  if ( !image_useCache.internalVar->integerValue )
    return 0;
  if ( !this->allowDownSize )
    return 0;
  if ( image_cacheMinK.internalVar->integerValue <= 0 )
    return 0;
  if ( fileSystem->PerformingCopyFiles(fileSystem) )
    return 0;
  idImage::ImageProgramStringToCompressedFileName(this, this->imgName.data, filename);
  p_timestamp = &this->timestamp;
  fileSystem->ReadFile(fileSystem, filename, 0, p_timestamp);
  if ( *p_timestamp == -1 )
    return 0;
  v4 = fileSystem->OpenFileRead(fileSystem, filename, 1, 0);
  v5 = v4;
  if ( !v4 )
    return 0;
  v6 = v4->Length(v4);
  fileSystem->CloseFile(fileSystem, v5);
  return v6 > image_cacheMinK.internalVar->integerValue << 10;
}

// FUNC: public: bool __thiscall idImage::CheckPrecompressedImage(bool)
char __thiscall idImage::CheckPrecompressedImage(idImage *this, bool fullLoad)
{
  textureDepth_t depth; // eax
  char v5; // cl
  idFile *v6; // eax
  idFile *v7; // edi
  unsigned int v8; // eax
  int v9; // ebx
  int *v10; // esi
  int v11; // edi
  unsigned int newTimestamp; // [esp+24h] [ebp-10Ch] BYREF
  bool deswizzleDDSforPal; // [esp+28h] [ebp-108h]
  unsigned int precompTimestamp; // [esp+2Ch] [ebp-104h] BYREF
  char filename[256]; // [esp+30h] [ebp-100h] BYREF

  if ( !glConfig.isInitialized || com_Bundler.internalVar->integerValue && fileSystem->PerformingCopyFiles(fileSystem) )
    return 0;
  depth = this->depth;
  v5 = 0;
  deswizzleDDSforPal = 0;
  if ( depth == TD_BUMP
    && image_useNormalCompressionLoadDDSForPal.internalVar->integerValue
    && image_useNormalCompression.internalVar->integerValue == 1 )
  {
    v5 = 1;
    deswizzleDDSforPal = 1;
  }
  if ( depth == TD_BUMP && image_useNormalCompression.internalVar->integerValue != 2 && !v5 )
    return 0;
  idStr::StripFileExtension(&this->imgName);
  idImage::ImageProgramStringToCompressedFileName(this, this->imgName.data, filename);
  fileSystem->ReadFile(fileSystem, filename, 0, &precompTimestamp);
  if ( precompTimestamp == -1 || gWriteProgramFlag && image_usePrecompressedTextures.internalVar->integerValue == 2 )
    return 0;
  if ( !this->generatorFunction && !image_writeProgramImages.internalVar->integerValue )
  {
    R_LoadImageProgram(this->imgName.data, 0, 0, 0, &newTimestamp, 0);
    if ( newTimestamp != -1 && newTimestamp > precompTimestamp && !com_makingBuild.internalVar->integerValue )
      return 0;
  }
  v6 = fileSystem->OpenFileRead(fileSystem, filename, 1, 0);
  v7 = v6;
  if ( !v6 )
    return 0;
  v8 = v6->Length(v6);
  v9 = v8;
  if ( v8 < 0x7C || com_makingBuild.internalVar->integerValue )
  {
    fileSystem->CloseFile(fileSystem, v7);
    return 0;
  }
  if ( !fullLoad )
    return 0;
  v10 = (int *)R_StaticAlloc(v8);
  v7->Read(v7, v10, v9);
  fileSystem->CloseFile(fileSystem, v7);
  v11 = *v10;
  newTimestamp = LittleLong(v10[20]);
  if ( LittleLong(v11) == 542327876 )
  {
    if ( (newTimestamp & 0x10000000) == 0 || glConfig.sharedTexturePaletteAvailable )
    {
      idImage::UploadPrecompressedImage(this, (unsigned __int8 *)v10, v9, 3553, deswizzleDDSforPal);
      R_StaticFree(v10);
      return 1;
    }
    else
    {
      R_StaticFree(v10);
      return 0;
    }
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "CheckPrecompressedImage( %s ): magic != 'DDS '\n",
      this->imgName.data);
    R_StaticFree(v10);
    return 0;
  }
}

// FUNC: public: bool __thiscall idImage::CheckPrecompressedCubeImage(char *,unsigned int *,int,int,enum cubeFiles_t)
char __userpurge idImage::CheckPrecompressedCubeImage@<al>(
        idImage *this@<ecx>,
        int a2@<ebx>,
        char *faceName,
        unsigned int *timestamp,
        int target,
        int index,
        cubeFiles_t extensions)
{
  idFile *v9; // eax
  idFile *v10; // edi
  unsigned int v11; // eax
  int v12; // ebx
  void *v13; // esi
  unsigned int newTimestamp; // [esp+Ch] [ebp-104h] BYREF
  char filename[256]; // [esp+10h] [ebp-100h] BYREF

  if ( !glConfig.isInitialized
    || image_dontUsePrecompressedSkyboxesForCGW.internalVar->integerValue
    || com_Bundler.internalVar->integerValue && fileSystem->PerformingCopyFiles(fileSystem) )
  {
    return 0;
  }
  idImage::ImageProgramStringToCompressedFileName(this, faceName, filename);
  fileSystem->ReadFile(fileSystem, filename, 0, timestamp);
  if ( *timestamp == -1 )
    return 0;
  if ( !this->generatorFunction && image_usePrecompressedTextures.internalVar->integerValue == 1 )
  {
    R_LoadCubeImages(this->imgName.data, this->cubeFiles, 0, 0, &newTimestamp);
    if ( newTimestamp != -1 && newTimestamp > *timestamp && !com_makingBuild.internalVar->integerValue )
      return 0;
  }
  v9 = fileSystem->OpenFileRead(fileSystem, filename, 1, 0);
  v10 = v9;
  if ( !v9 )
    return 0;
  v11 = ((int (__thiscall *)(idFile *, int))v9->Length)(v9, a2);
  v12 = v11;
  if ( v11 >= 0x7C )
  {
    v13 = R_StaticAlloc(v11);
    ((void (__thiscall *)(idFile *, void *))v10->Read)(v10, v13);
    fileSystem->CloseFile(fileSystem, v10);
    if ( LittleLong(*(_DWORD *)v13) == 542327876 )
    {
      if ( (LittleLong(*((_DWORD *)v13 + 20)) & 0x10000000) == 0 || glConfig.sharedTexturePaletteAvailable )
      {
        idImage::UploadPrecompressedImage(this, (unsigned __int8 *)v13, v12, target, 0);
        R_StaticFree(v13);
        return 1;
      }
      else
      {
        R_StaticFree(v13);
        return 0;
      }
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "CheckPrecompressedCubeImage( %s ): magic != 'DDS '\n",
        faceName);
      R_StaticFree(v13);
      return 0;
    }
  }
  else
  {
    fileSystem->CloseFile(fileSystem, v10);
    return 0;
  }
}

// FUNC: public: bool __thiscall idImage::CheckCubeImages(char const *,enum cubeFiles_t,unsigned int *)
char __thiscall idImage::CheckCubeImages(
        idImage *this,
        const char *imgName,
        cubeFiles_t extensions,
        unsigned int *timestamp)
{
  idImage_vtbl *v5; // eax
  int i; // esi
  char **sides; // [esp+8h] [ebp-138h]
  unsigned int thisTime; // [esp+Ch] [ebp-134h] BYREF
  char *cameraSides[6]; // [esp+10h] [ebp-130h] BYREF
  char *axisSides[6]; // [esp+28h] [ebp-118h] BYREF
  char fullName[256]; // [esp+40h] [ebp-100h] BYREF

  cameraSides[0] = "_forward";
  cameraSides[1] = "_back";
  cameraSides[2] = "_left";
  cameraSides[3] = "_right";
  cameraSides[4] = "_up";
  cameraSides[5] = "_down";
  axisSides[0] = "_px";
  axisSides[1] = "_nx";
  axisSides[2] = "_py";
  axisSides[3] = "_ny";
  axisSides[4] = "_pz";
  axisSides[5] = "_nz";
  if ( extensions == CF_CAMERA )
    sides = cameraSides;
  else
    sides = axisSides;
  if ( timestamp )
    *timestamp = 0;
  qglGenTextures(1, &this->texnum);
  v5 = this->__vftable;
  this->type = TT_CUBIC;
  v5->Bind(this);
  for ( i = 0; i < 6; ++i )
  {
    idStr::snPrintf(fullName, 256, "%s%s", imgName, sides[i]);
    thisTime = -1;
    if ( !idImage::CheckPrecompressedCubeImage(this, (int)imgName, fullName, &thisTime, i + 34069, i, extensions)
      || thisTime == -1 )
    {
      break;
    }
    if ( timestamp && thisTime > *timestamp )
      *timestamp = thisTime;
  }
  if ( i != 6 || com_makingBuild.internalVar->integerValue )
  {
    this->PurgeImage(this);
    if ( timestamp )
      *timestamp = 0;
    return 0;
  }
  else
  {
    qglTexParameteri(0x8513u, 0x2802u, 33071);
    qglTexParameteri(0x8513u, 0x2803u, 33071);
    return 1;
  }
}

// FUNC: public: void __thiscall idImage::GenerateImage(unsigned char const *,int,int,enum textureFilter_t,bool,enum textureRepeat_t,enum textureDepth_t,int)
void __thiscall idImage::GenerateImage(
        idImage *this,
        const unsigned __int8 *pic,
        int width,
        int height,
        textureFilter_t filterParm,
        bool allowDownSizeParm,
        textureRepeat_t repeatParm,
        textureDepth_t depthParm,
        int flags)
{
  idImage_vtbl *v10; // edx
  bool v11; // zf
  textureRepeat_t v12; // eax
  textureDepth_t v13; // edx
  int v14; // esi
  int i; // eax
  int v16; // ebp
  int v17; // ecx
  int v18; // eax
  int v19; // eax
  int v20; // ebx
  unsigned __int8 *j; // edi
  idImage *v22; // ecx
  char *v23; // eax
  int v24; // esi
  int k; // eax
  idImage *v26; // ebp
  int internalFormat; // eax
  int v28; // esi
  unsigned __int8 *v29; // ebp
  idImage *v30; // ecx
  int v31; // eax
  unsigned __int8 rgba[4]; // [esp+4h] [ebp-114h] BYREF
  int scaled_height; // [esp+8h] [ebp-110h] BYREF
  idImage *v34; // [esp+Ch] [ebp-10Ch]
  unsigned __int8 *shrunk; // [esp+10h] [ebp-108h]
  BOOL preserveBorder; // [esp+14h] [ebp-104h]
  char filename[256]; // [esp+18h] [ebp-100h] BYREF

  v10 = this->__vftable;
  this->flags |= flags;
  v34 = this;
  ((void (__fastcall *)(idImage *))v10->PurgeImage)(this);
  v11 = (this->flags & 1) == 0;
  this->filter = filterParm;
  if ( !v11 )
    this->filter = TF_NEAREST;
  v12 = repeatParm;
  v13 = depthParm;
  this->allowDownSize = allowDownSizeParm;
  this->repeat = v12;
  this->depth = v13;
  if ( glConfig.isInitialized )
  {
    v14 = width;
    LOBYTE(preserveBorder) = v12 == TR_CLAMP_TO_ZERO;
    for ( i = 1; i < width; i *= 2 )
      ;
    v16 = height;
    v17 = 1;
    for ( *(_DWORD *)rgba = i; v17 < height; v17 *= 2 )
      ;
    scaled_height = v17;
    if ( i != width || v17 != height )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "R_CreateImage: not a power of 2 image");
    idImage::GetDownsize(this, (int *)rgba, &scaled_height);
    qglGenTextures(1, &this->texnum);
    if ( !idStr::Cmpn(this->imgName.data, "fonts", 5)
      || (v18 = idStr::Cmpn(this->imgName.data, "gfx/2d", 6), LOBYTE(shrunk) = 0, !v18) )
    {
      LOBYTE(shrunk) = 1;
    }
    v19 = idImage::SelectInternalFormat(this, &pic, 1, v14, v16, this->depth, (bool)shrunk, &this->isMonochrome);
    v20 = *(_DWORD *)rgba;
    v11 = *(_DWORD *)rgba == v14;
    this->internalFormat = v19;
    if ( v11 && scaled_height == v16 )
    {
      j = (unsigned __int8 *)R_StaticAlloc(4 * v20 * scaled_height);
      SIMDProcessor->Memcpy(SIMDProcessor, j, pic, 4 * v16 * v14);
    }
    else
    {
      for ( j = R_MipMap(pic, v14, v16, preserveBorder); ; j = shrunk )
      {
        v14 >>= 1;
        v16 >>= 1;
        if ( v14 < 1 )
          v14 = 1;
        if ( v16 < 1 )
          v16 = 1;
        if ( v14 <= v20 && v16 <= scaled_height )
          break;
        shrunk = R_MipMap(j, v14, v16, preserveBorder);
        R_StaticFree(j);
      }
      v20 = v14;
      scaled_height = v16;
    }
    v22 = v34;
    v11 = v34->repeat == TR_CLAMP_TO_ZERO;
    v34->uploadHeight = scaled_height;
    v22->uploadWidth = v20;
    v22->type = TT_2D;
    if ( v11 )
    {
      rgba[2] = 0;
      rgba[1] = 0;
      rgba[0] = 0;
      rgba[3] = -1;
      R_SetBorderTexels(j, v14, v16, rgba);
      v22 = v34;
    }
    if ( v22->repeat == TR_CLAMP_TO_ZERO_ALPHA )
    {
      rgba[2] = -1;
      rgba[1] = -1;
      rgba[0] = -1;
      rgba[3] = 0;
      R_SetBorderTexels(j, v14, v16, rgba);
      v22 = v34;
    }
    if ( v22->generatorFunction )
      goto LABEL_41;
    if ( v22->depth == TD_BUMP )
    {
      if ( !image_writeNormalTGA.internalVar->integerValue )
        goto LABEL_35;
    }
    else if ( !image_writeTGA.internalVar->integerValue )
    {
LABEL_35:
      if ( image_writeProgramImages.internalVar->integerValue && gWriteProgramFlag )
        goto LABEL_37;
LABEL_41:
      gWriteProgramFlag = 0;
      if ( v22->depth == TD_BUMP && image_useNormalCompression.internalVar->integerValue != 1 )
      {
        v24 = 4 * v20 * scaled_height;
        for ( k = 0; k < v24; k += 4 )
        {
          j[k + 3] = j[k];
          j[k] = 0;
        }
      }
      v22->Bind(v22);
      v26 = v34;
      internalFormat = v34->internalFormat;
      if ( internalFormat == 32997 )
      {
        v28 = scaled_height;
        idImage::UploadPalettisedNormalMap(v34, v20, scaled_height, j, 0);
      }
      else
      {
        qglTexImage2D(0xDE1u, 0, internalFormat, v20, scaled_height, 0, 0x1908u, 0x1401u, j);
        v28 = scaled_height;
      }
      v11 = (v26->flags & 1) == 0;
      *(_DWORD *)rgba = 0;
      if ( v11 )
      {
        shrunk = mipBlendColors[0];
        do
        {
          if ( v20 <= 1 && v28 <= 1 )
            break;
          v29 = R_MipMap(j, v20, v28, preserveBorder);
          R_StaticFree(j);
          v20 >>= 1;
          v28 >>= 1;
          j = v29;
          if ( v20 < 1 )
            v20 = 1;
          if ( v28 < 1 )
          {
            scaled_height = 1;
            v28 = 1;
          }
          v30 = v34;
          ++*(_DWORD *)rgba;
          shrunk += 4;
          if ( v34->depth == TD_DIFFUSE && image_colorMipLevels.internalVar->integerValue )
          {
            R_BlendOverTexture(v29, v20 * v28, shrunk);
            v30 = v34;
          }
          v31 = v30->internalFormat;
          if ( v31 == 32997 )
            idImage::UploadPalettisedNormalMap(v30, v20, v28, v29, *(int *)rgba);
          else
            qglTexImage2D(0xDE1u, *(int *)rgba, v31, v20, v28, 0, 0x1908u, 0x1401u, v29);
        }
        while ( (v34->flags & 1) == 0 );
      }
      if ( j )
        R_StaticFree(j);
      idImage::SetImageFilterAndRepeat(v34);
      GL_CheckErrors();
      return;
    }
LABEL_37:
    idImage::ImageProgramStringToCompressedFileName(v22, v22->imgName.data, filename);
    strrchr((unsigned __int8 *)filename, 0x2Eu);
    if ( v23 )
    {
      strcpy(v23, ".tga");
      R_WriteTGA(filename, j, v20, scaled_height, 0);
      if ( image_writeProgramImages.internalVar->integerValue )
      {
        R_StaticFree(j);
        gWriteProgramFlag = 0;
        globalImages->PurgeAllImages(globalImages);
        return;
      }
    }
    v22 = v34;
    goto LABEL_41;
  }
}

// FUNC: public: void __thiscall idImage::ActuallyLoadImage(bool,bool)
void __thiscall idImage::ActuallyLoadImage(idImage *this, int checkForPrecompressed, bool fromBackEnd)
{
  void (__cdecl *generatorFunction)(idImage *); // eax
  textureDepth_t *p_depth; // edi
  char v6; // al
  cubeFiles_t cubeFiles; // ecx
  int i; // esi
  int v9; // eax
  bool allowDownSize; // cl
  textureFilter_t filter; // edx
  char *data; // [esp-10h] [ebp-34h]
  cubeFiles_t v13; // [esp-Ch] [ebp-30h]
  textureDepth_t v14; // [esp-Ch] [ebp-30h]
  unsigned __int8 *v15; // [esp-8h] [ebp-2Ch]
  unsigned __int8 *pic; // [esp+4h] [ebp-20h] BYREF
  int height; // [esp+8h] [ebp-1Ch] BYREF
  unsigned __int8 *pics[6]; // [esp+Ch] [ebp-18h] BYREF

  generatorFunction = this->generatorFunction;
  if ( generatorFunction )
  {
    generatorFunction(this);
  }
  else if ( this->isPartialImage )
  {
    if ( !idImage::CheckPrecompressedImage(this, 0) )
      idImage::MakeDefault(this);
  }
  else
  {
    p_depth = &this->depth;
    if ( this->depth == TD_HIGH_QUALITY )
      v6 = 0;
    else
      v6 = checkForPrecompressed;
    cubeFiles = this->cubeFiles;
    if ( cubeFiles )
    {
      if ( gWriteProgramFlag && image_usePrecompressedTextures.internalVar->integerValue == 2
        || !v6
        || !image_usePrecompressedTextures.internalVar->integerValue
        || !idImage::CheckCubeImages(this, this->imgName.data, cubeFiles, &this->timestamp) )
      {
        R_LoadCubeImages(this->imgName.data, this->cubeFiles, pics, &checkForPrecompressed, &this->timestamp);
        if ( pics[0] )
        {
          idImage::GenerateCubeImage(
            this,
            (const unsigned __int8 **)pics,
            checkForPrecompressed,
            this->filter,
            this->allowDownSize,
            *p_depth);
          v13 = this->cubeFiles;
          data = this->imgName.data;
          this->precompressedFile = 0;
          idImage::WritePrecompressedCubeImages(this, data, v13, pics);
          for ( i = 0; i < 6; ++i )
          {
            if ( pics[i] )
              R_StaticFree(pics[i]);
          }
        }
        else
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "Couldn't load cube image: %s",
            this->imgName.data);
          idImage::MakeDefault(this);
        }
      }
    }
    else if ( !v6
           || !image_usePrecompressedTextures.internalVar->integerValue
           || !idImage::CheckPrecompressedImage(this, 1) )
    {
      R_LoadImageProgram(this->imgName.data, &pic, &checkForPrecompressed, &height, &this->timestamp, &this->depth);
      if ( pic )
      {
        v9 = MD4_BlockChecksum(pic, 4 * checkForPrecompressed * height);
        allowDownSize = this->allowDownSize;
        v14 = *p_depth;
        filter = this->filter;
        this->imageHash = v9;
        idImage::GenerateImage(this, pic, checkForPrecompressed, height, filter, allowDownSize, this->repeat, v14, 0);
        v15 = pic;
        this->precompressedFile = 0;
        R_StaticFree(v15);
        idImage::WritePrecompressedImage(this, 0, 3553, 0);
      }
      else if ( gWriteProgramFlag && image_writeProgramImages.internalVar->integerValue
             || !image_writeProgramImages.internalVar->integerValue )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "Couldn't load image: %s",
          this->imgName.data);
        idImage::MakeDefault(this);
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idImage::Bind(void)
void __thiscall idImage::Bind(idImage *this)
{
  idImage *cacheUsageNext; // eax
  idImage *v3; // eax
  idImage *v4; // ecx
  unsigned int *p_texnum; // ebx
  idImage *partialImage; // ecx
  int frameCount; // ecx
  textureType_t textureType; // eax
  tmu_t *v9; // edi
  textureType_t type; // eax
  textureType_t v11; // esi
  float priority; // [esp+8h] [ebp-4h] BYREF

  if ( this->partialImage )
  {
    cacheUsageNext = this->cacheUsageNext;
    if ( cacheUsageNext )
    {
      cacheUsageNext->cacheUsagePrev = this->cacheUsagePrev;
      this->cacheUsagePrev->cacheUsageNext = this->cacheUsageNext;
    }
    this->cacheUsageNext = globalImages->GetCacheUsageNext(globalImages);
    v3 = globalImages->GetCacheHead(globalImages);
    v4 = this->cacheUsageNext;
    this->cacheUsagePrev = v3;
    v4->cacheUsagePrev = this;
    this->cacheUsagePrev->cacheUsageNext = this;
  }
  p_texnum = &this->texnum;
  if ( this->texnum == -1 )
  {
    partialImage = this->partialImage;
    if ( partialImage )
    {
      partialImage->Bind(partialImage);
      if ( !this->backgroundLoadInProgress )
        idImage::StartBackgroundImageLoad(this);
      return;
    }
    idImage::ActuallyLoadImage(this, 1, 1);
  }
  frameCount = backEnd.frameCount;
  ++this->bindCount;
  this->frameUsed = frameCount;
  textureType = backEnd.glState.tmu[backEnd.glState.currenttmu].textureType;
  v9 = &backEnd.glState.tmu[backEnd.glState.currenttmu];
  if ( textureType != this->type && backEnd.glState.currenttmu < glConfig.maxTextureUnits )
  {
    switch ( textureType )
    {
      case TT_CUBIC:
        qglDisable(0x8513u);
        break;
      case TT_3D:
        qglDisable(0x806Fu);
        break;
      case TT_2D:
        qglDisable(0xDE1u);
        break;
    }
    type = this->type;
    switch ( type )
    {
      case TT_CUBIC:
        qglEnable(0x8513u);
        break;
      case TT_3D:
        qglEnable(0x806Fu);
        break;
      case TT_2D:
        qglEnable(0xDE1u);
        break;
    }
    v9->textureType = this->type;
  }
  v11 = this->type;
  if ( v11 == TT_2D )
  {
    if ( v9->current2DMap != *p_texnum )
    {
      v9->current2DMap = *p_texnum;
      qglBindTexture(0xDE1u, *p_texnum);
    }
  }
  else if ( v11 == TT_CUBIC )
  {
    if ( v9->currentCubeMap != *p_texnum )
    {
      v9->currentCubeMap = *p_texnum;
      qglBindTexture(0x8513u, *p_texnum);
    }
  }
  else if ( v11 == TT_3D && v9->current3DMap != *p_texnum )
  {
    v9->current3DMap = *p_texnum;
    qglBindTexture(0x806Fu, *p_texnum);
  }
  if ( com_purgeAll.internalVar->integerValue )
  {
    priority = 1.0;
    qglPrioritizeTextures(1, p_texnum, &priority);
  }
}

// FUNC: public: virtual __thiscall idPBufferImage::~idPBufferImage(void)
void __thiscall idPBufferImage::~idPBufferImage(idPBufferImage *this)
{
  rvTexRenderTarget *mRenderTarget; // ecx
  rvTexRenderTarget *v3; // edi

  this->__vftable = (idPBufferImage_vtbl *)&idPBufferImage::`vftable';
  mRenderTarget = this->mRenderTarget;
  if ( mRenderTarget )
    rvTexRenderTarget::Release(mRenderTarget);
  if ( this->texnum != -1 )
  {
    if ( qglDeleteTextures )
      qglDeleteTextures(1, &this->texnum);
    this->texnum = -1;
  }
  v3 = this->mRenderTarget;
  if ( v3 )
  {
    rvTexRenderTarget::~rvTexRenderTarget(this->mRenderTarget);
    Memory::Free(v3);
    this->mRenderTarget = 0;
  }
  idImage::~idImage(this);
}
