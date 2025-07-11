
// FUNC: public: void __thiscall idDeviceContext::SizeIcon(struct embeddedIcon_s *)
void __thiscall idDeviceContext::SizeIcon(idDeviceContext *this, embeddedIcon_s *icon)
{
  int width; // ebx
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st7
  int ImageWidth; // eax
  int ImageHeight; // eax
  int x; // [esp+8h] [ebp-14h]
  int y; // [esp+Ch] [ebp-10h]
  float v12; // [esp+10h] [ebp-Ch]
  float v13; // [esp+14h] [ebp-8h]
  float v14; // [esp+14h] [ebp-8h]
  float v15; // [esp+14h] [ebp-8h]
  embeddedIcon_s *icona; // [esp+20h] [ebp+4h]

  width = icon->width;
  x = (int)icon->s1;
  y = (int)icon->t1;
  icona = (embeddedIcon_s *)icon->height;
  if ( x == -1 )
  {
    v4 = 0.0;
  }
  else
  {
    v13 = (float)x;
    v4 = v13 / (double)idMaterial::GetImageWidth((idMaterial *)icon->shader);
  }
  icon->s1 = v4;
  if ( y == -1 )
  {
    v5 = 0.0;
  }
  else
  {
    v12 = (float)y;
    v5 = v12 / (double)idMaterial::GetImageHeight((idMaterial *)icon->shader);
  }
  icon->t1 = v5;
  if ( x == -1 )
  {
    v6 = 1.0;
  }
  else
  {
    v14 = (double)width + (double)x;
    v6 = v14 / (double)idMaterial::GetImageWidth((idMaterial *)icon->shader);
  }
  icon->s2 = v6;
  if ( y == -1 )
  {
    v7 = 1.0;
  }
  else
  {
    v15 = (double)(int)icona + (double)y;
    v7 = v15 / (double)idMaterial::GetImageHeight((idMaterial *)icon->shader);
  }
  icon->t2 = v7;
  if ( width == -1 )
    ImageWidth = idMaterial::GetImageWidth((idMaterial *)icon->shader);
  else
    ImageWidth = width;
  icon->width = ImageWidth;
  ImageHeight = (int)icona;
  if ( icona == (embeddedIcon_s *)-1 )
    ImageHeight = idMaterial::GetImageHeight((idMaterial *)icon->shader);
  icon->height = ImageHeight;
}

// FUNC: public: void __thiscall idDeviceContext::SetCursor(int)
void __thiscall idDeviceContext::SetCursor(idDeviceContext *this, unsigned int n)
{
  int v2; // eax

  v2 = n;
  if ( n >= 2 )
    v2 = 0;
  this->cursor = v2;
}

// FUNC: public: void __thiscall idDeviceContext::SetSize(float,float)
void __thiscall idDeviceContext::SetSize(idDeviceContext *this, float width, float height)
{
  this->yScale = 0.0;
  this->xScale = 0.0;
  this->vidWidth = 640.0;
  this->vidHeight = 480.0;
  if ( width != 0.0 && height != 0.0 )
  {
    this->xScale = 1.0 / width * 640.0;
    this->yScale = 1.0 / height * 480.0;
  }
}

// FUNC: public: void __thiscall idDeviceContext::SizeIcons(void)
void __thiscall idDeviceContext::SizeIcons(idDeviceContext *this)
{
  int v2; // ebx
  int tablesize; // edi
  int v4; // ecx
  int v5; // edx
  idHashTable<embeddedIcon_s>::hashnode_s **heads; // esi
  idHashTable<embeddedIcon_s>::hashnode_s *v7; // eax
  embeddedIcon_s *p_value; // eax
  int cnt; // [esp+8h] [ebp-4h]

  v2 = 0;
  cnt = this->icons.numentries;
  if ( cnt > 0 )
  {
    do
    {
      if ( v2 < 0 || v2 > this->icons.numentries || (tablesize = this->icons.tablesize, v4 = 0, v5 = 0, tablesize <= 0) )
      {
LABEL_10:
        p_value = 0;
      }
      else
      {
        heads = this->icons.heads;
        while ( 1 )
        {
          v7 = *heads;
          if ( *heads )
            break;
LABEL_9:
          ++v5;
          ++heads;
          if ( v5 >= tablesize )
            goto LABEL_10;
        }
        while ( v4 != v2 )
        {
          v7 = v7->next;
          ++v4;
          if ( !v7 )
            goto LABEL_9;
        }
        p_value = &v7->value;
      }
      idDeviceContext::SizeIcon(this, p_value);
      ++v2;
    }
    while ( v2 < cnt );
  }
}

// FUNC: public: void __thiscall idDeviceContext::SetFont(int)
void __thiscall idDeviceContext::SetFont(idDeviceContext *this, int num)
{
  if ( num < 0 || num >= idDeviceContext::fonts.num )
    this->activeFont = idDeviceContext::fonts.list;
  else
    this->activeFont = &idDeviceContext::fonts.list[num];
}

// FUNC: public: void __thiscall idDeviceContext::SetTransformInfo(class idVec3 const &,class idMat3 const &)
void __thiscall idDeviceContext::SetTransformInfo(idDeviceContext *this, const idVec3 *org, const idMat3 *m)
{
  float orga; // [esp+4h] [ebp+4h]
  float orgb; // [esp+4h] [ebp+4h]
  float orgc; // [esp+4h] [ebp+4h]
  float orgd; // [esp+4h] [ebp+4h]
  float orge; // [esp+4h] [ebp+4h]
  float orgf; // [esp+4h] [ebp+4h]
  float orgg; // [esp+4h] [ebp+4h]
  float orgh; // [esp+4h] [ebp+4h]
  float orgi; // [esp+4h] [ebp+4h]

  this->origin = *org;
  this->mat = *m;
  orga = this->mat.mat[0].x - mat3_identity.mat[0].x;
  if ( COERCE_FLOAT(LODWORD(orga) & 0x7FFFFFFF) > 0.000001 )
    goto LABEL_11;
  orgb = this->mat.mat[0].y - mat3_identity.mat[0].y;
  if ( COERCE_FLOAT(LODWORD(orgb) & 0x7FFFFFFF) > 0.000001
    || (orgc = this->mat.mat[0].z - mat3_identity.mat[0].z, COERCE_FLOAT(LODWORD(orgc) & 0x7FFFFFFF) > 0.000001)
    || (orgd = this->mat.mat[1].x - mat3_identity.mat[1].x, COERCE_FLOAT(LODWORD(orgd) & 0x7FFFFFFF) > 0.000001)
    || (orge = this->mat.mat[1].y - mat3_identity.mat[1].y, COERCE_FLOAT(LODWORD(orge) & 0x7FFFFFFF) > 0.000001)
    || (orgf = this->mat.mat[1].z - mat3_identity.mat[1].z, COERCE_FLOAT(LODWORD(orgf) & 0x7FFFFFFF) > 0.000001)
    || (orgg = this->mat.mat[2].x - mat3_identity.mat[2].x, COERCE_FLOAT(LODWORD(orgg) & 0x7FFFFFFF) > 0.000001)
    || (orgh = this->mat.mat[2].y - mat3_identity.mat[2].y, COERCE_FLOAT(LODWORD(orgh) & 0x7FFFFFFF) > 0.000001)
    || (orgi = this->mat.mat[2].z - mat3_identity.mat[2].z, COERCE_FLOAT(LODWORD(orgi) & 0x7FFFFFFF) > 0.000001) )
  {
LABEL_11:
    this->isMatIdentity = 0;
  }
  else
  {
    this->isMatIdentity = 1;
  }
}

// FUNC: public: void __thiscall idDeviceContext::GetTransformInfo(class idVec3 &,class idMat3 &)
void __thiscall idDeviceContext::GetTransformInfo(idDeviceContext *this, idVec3 *org, idMat3 *m)
{
  *m = this->mat;
  *org = this->origin;
}

// FUNC: public: void __thiscall idDeviceContext::PopClipRect(void)
void __thiscall idDeviceContext::PopClipRect(idDeviceContext *this)
{
  int num; // eax
  int v2; // esi
  int v3; // eax
  int v4; // edx
  int v5; // esi
  idRectangle *v6; // eax

  num = this->clipRects.num;
  if ( num )
  {
    v2 = num - 1;
    if ( num - 1 >= 0 && v2 < num )
    {
      v3 = num - 1;
      this->clipRects.num = v3;
      v4 = v2;
      if ( v2 < v3 )
      {
        v5 = v2;
        do
        {
          v6 = &this->clipRects.list[v5];
          v6->x = v6[1].x;
          v6->y = v6[1].y;
          v6->w = v6[1].w;
          ++v4;
          v6->h = v6[1].h;
          ++v5;
        }
        while ( v4 < this->clipRects.num );
      }
    }
  }
}

// FUNC: public: bool __thiscall idDeviceContext::ClippedCoords(float *,float *,float *,float *,float *,float *,float *,float *)
bool __thiscall idDeviceContext::ClippedCoords(
        idDeviceContext *this,
        float *x,
        float *y,
        float *w,
        float *h,
        float *s1,
        float *t1,
        float *s2,
        float *t2)
{
  idDeviceContext *v9; // edx
  int num; // eax
  int v12; // eax
  int v16; // eax
  float *v18; // edx
  double v20; // st7
  unsigned __int8 v21; // c0
  unsigned __int8 v22; // c3
  double v23; // st7
  double v25; // st7
  unsigned __int8 v26; // c0
  unsigned __int8 v27; // c3
  double v28; // st7
  double v29; // st7
  double v30; // st6
  double v31; // st5
  double v32; // st4
  double v33; // st5
  double v34; // rt0
  float oy; // [esp+0h] [ebp-10h]
  int c; // [esp+4h] [ebp-Ch]
  float nt2; // [esp+Ch] [ebp-4h]
  float xa; // [esp+14h] [ebp+4h]
  float oh; // [esp+18h] [ebp+8h]
  float oha; // [esp+18h] [ebp+8h]
  int nt1; // [esp+1Ch] [ebp+Ch]
  float ha; // [esp+20h] [ebp+10h]
  float t2a; // [esp+30h] [ebp+20h]

  v9 = this;
  if ( !this->enableClipping )
    return 0;
  num = this->clipRects.num;
  if ( !num )
    return 0;
  v12 = num - 1;
  c = v12;
  if ( v12 > 0 )
  {
    v16 = 16 * v12;
    nt1 = v16;
    while ( 1 )
    {
      v18 = (float *)((char *)&v9->clipRects.list->x + v16);
      t2a = *x;
      oy = *y;
      ha = *w;
      xa = *h;
      if ( *w <= 0.0 || xa <= 0.0 )
        break;
      if ( *x >= (double)*v18 )
      {
        if ( v18[2] + *v18 < *x )
        {
          *h = 0.0;
          *y = 0.0;
          *w = 0.0;
          *x = 0.0;
        }
      }
      else
      {
        *w = *w - (*v18 - *x);
        *x = *v18;
      }
      if ( *y >= (double)v18[1] )
      {
        if ( v18[3] + v18[1] < *y )
        {
          *h = 0.0;
          *y = 0.0;
          *w = 0.0;
          *x = 0.0;
        }
      }
      else
      {
        *h = *h - (v18[1] - *y);
        *y = v18[1];
      }
      v20 = v18[2];
      if ( v21 | v22 )
      {
        v23 = v20 + *v18;
        if ( *w + *x > v23 )
          *w = v23 - *x;
      }
      else
      {
        *w = v20 - *x + *v18;
      }
      v25 = v18[3];
      if ( v26 | v27 )
      {
        v28 = v25 + v18[1];
        if ( *h + *y > v28 )
          *h = v28 - *y;
      }
      else
      {
        *h = v25 - *y + v18[1];
      }
      if ( s1 && s2 && t1 && t2 && ha > 0.0 )
      {
        oh = 1.0 / ha;
        v29 = (*x - t2a) * oh;
        v30 = (*w + *x - t2a) * oh;
        v31 = 1.0 / xa;
        v32 = (*y - oy) * v31;
        oha = (1.0 - v32) * *t1 + v32 * *t2;
        v33 = v31 * (*h + *y - oy);
        nt2 = (1.0 - v33) * *t1 + v33 * *t2;
        v34 = (1.0 - v30) * *s1 + v30 * *s2;
        *s1 = (1.0 - v29) * *s1 + v29 * *s2;
        *s2 = v34;
        *t1 = oha;
        *t2 = nt2;
      }
      nt1 -= 16;
      if ( --c <= 0 )
        break;
      v16 = nt1;
      v9 = this;
    }
  }
  return *w == 0.0 || *h == 0.0;
}

// FUNC: public: void __thiscall idDeviceContext::DrawStretchPic(float,float,float,float,float,float,float,float,class idMaterial const *)
void __thiscall idDeviceContext::DrawStretchPic(
        idDeviceContext *this,
        float x,
        int y,
        float w,
        float h,
        int s1,
        int t1,
        int s2,
        int t2,
        const idMaterial *shader)
{
  idDeviceContext *v10; // eax
  double v11; // st7
  double v12; // st7
  double v13; // st6
  double v14; // st7
  double v15; // st7
  double v16; // st6
  double v17; // st7
  double v18; // st7
  double v19; // st6
  double v20; // st7
  double v21; // st7
  double v22; // st6

  v10 = this;
  rectVerts[0].xyz.x = x;
  flt_103DE7B0 = x + w;
  dword_103DE774 = y;
  flt_103DE7F0 = flt_103DE7B0;
  dword_103DE7A8 = s1;
  dword_103DE7AC = t1;
  flt_103DE7F4 = *(float *)&y + h;
  dword_103DE7B4 = y;
  flt_103DE834 = flt_103DE7F4;
  dword_103DE7E8 = s2;
  dword_103DE7EC = t1;
  dword_103DE828 = s2;
  dword_103DE82C = t2;
  dword_103DE830 = LODWORD(x);
  dword_103DE778 = 0;
  dword_103DE7B8 = 0;
  dword_103DE7F8 = 0;
  dword_103DE838 = 0;
  dword_103DE868 = s1;
  dword_103DE86C = t2;
  if ( !this->isMatIdentity )
  {
    rectVerts[0].xyz.x = x - this->origin.x;
    *(float *)&dword_103DE774 = *(float *)&y - this->origin.y;
    v11 = -this->origin.z;
    *(float *)&dword_103DE778 = v11;
    v12 = v11 * this->mat.mat[2].x
        + *(float *)&dword_103DE774 * this->mat.mat[1].x
        + rectVerts[0].xyz.x * this->mat.mat[0].x;
    v13 = *(float *)&dword_103DE778 * this->mat.mat[2].y
        + *(float *)&dword_103DE774 * this->mat.mat[1].y
        + rectVerts[0].xyz.x * this->mat.mat[0].y;
    *(float *)&dword_103DE778 = *(float *)&dword_103DE778 * this->mat.mat[2].z
                              + *(float *)&dword_103DE774 * this->mat.mat[1].z
                              + rectVerts[0].xyz.x * this->mat.mat[0].z;
    rectVerts[0].xyz.x = v12;
    *(float *)&dword_103DE774 = v13;
    rectVerts[0].xyz.x = v12 + this->origin.x;
    *(float *)&dword_103DE774 = v13 + this->origin.y;
    *(float *)&dword_103DE778 = *(float *)&dword_103DE778 + this->origin.z;
    flt_103DE7B0 = flt_103DE7B0 - this->origin.x;
    *(float *)&dword_103DE7B4 = *(float *)&y - this->origin.y;
    v14 = -this->origin.z;
    *(float *)&dword_103DE7B8 = v14;
    v15 = v14 * this->mat.mat[2].x + *(float *)&dword_103DE7B4 * this->mat.mat[1].x + flt_103DE7B0 * this->mat.mat[0].x;
    v16 = *(float *)&dword_103DE7B8 * this->mat.mat[2].y
        + *(float *)&dword_103DE7B4 * this->mat.mat[1].y
        + flt_103DE7B0 * this->mat.mat[0].y;
    *(float *)&dword_103DE7B8 = *(float *)&dword_103DE7B8 * this->mat.mat[2].z
                              + *(float *)&dword_103DE7B4 * this->mat.mat[1].z
                              + flt_103DE7B0 * this->mat.mat[0].z;
    flt_103DE7B0 = v15;
    *(float *)&dword_103DE7B4 = v16;
    flt_103DE7B0 = v15 + this->origin.x;
    *(float *)&dword_103DE7B4 = v16 + this->origin.y;
    *(float *)&dword_103DE7B8 = *(float *)&dword_103DE7B8 + this->origin.z;
    flt_103DE7F0 = flt_103DE7F0 - this->origin.x;
    flt_103DE7F4 = flt_103DE7F4 - this->origin.y;
    v17 = -this->origin.z;
    *(float *)&dword_103DE7F8 = v17;
    v18 = v17 * this->mat.mat[2].x + flt_103DE7F4 * this->mat.mat[1].x + flt_103DE7F0 * this->mat.mat[0].x;
    v19 = *(float *)&dword_103DE7F8 * this->mat.mat[2].y
        + flt_103DE7F4 * this->mat.mat[1].y
        + flt_103DE7F0 * this->mat.mat[0].y;
    *(float *)&dword_103DE7F8 = *(float *)&dword_103DE7F8 * this->mat.mat[2].z
                              + flt_103DE7F4 * this->mat.mat[1].z
                              + flt_103DE7F0 * this->mat.mat[0].z;
    flt_103DE7F0 = v18;
    flt_103DE7F4 = v19;
    flt_103DE7F0 = v18 + this->origin.x;
    flt_103DE7F4 = v19 + this->origin.y;
    *(float *)&dword_103DE7F8 = *(float *)&dword_103DE7F8 + this->origin.z;
    *(float *)&dword_103DE830 = x - this->origin.x;
    flt_103DE834 = flt_103DE834 - this->origin.y;
    v20 = -this->origin.z;
    *(float *)&dword_103DE838 = v20;
    v21 = v20 * this->mat.mat[2].x + flt_103DE834 * this->mat.mat[1].x + *(float *)&dword_103DE830 * this->mat.mat[0].x;
    v22 = *(float *)&dword_103DE838 * this->mat.mat[2].y
        + flt_103DE834 * this->mat.mat[1].y
        + *(float *)&dword_103DE830 * this->mat.mat[0].y;
    *(float *)&dword_103DE838 = *(float *)&dword_103DE838 * this->mat.mat[2].z
                              + flt_103DE834 * this->mat.mat[1].z
                              + *(float *)&dword_103DE830 * this->mat.mat[0].z;
    *(float *)&dword_103DE830 = v21;
    flt_103DE834 = v22;
    *(float *)&dword_103DE830 = v21 + this->origin.x;
    flt_103DE834 = v22 + this->origin.y;
    *(float *)&dword_103DE838 = *(float *)&dword_103DE838 + this->origin.z;
  }
  LOBYTE(v10) = !this->isMatIdentity;
  ((void (__stdcall *)(idDrawVert *, int *, int, int, const idMaterial *, idDeviceContext *, _DWORD, _DWORD, int, int))renderSystem->DrawStretchPic)(
    rectVerts,
    rectIndexes,
    4,
    6,
    shader,
    v10,
    0,
    0,
    1142947840,
    1139802112);
}

// FUNC: public: void __thiscall idDeviceContext::DrawMaterial(float,float,float,float,class idMaterial const *,class idVec4 const &,float,float)
void __thiscall idDeviceContext::DrawMaterial(
        idDeviceContext *this,
        float x,
        int y,
        float w,
        float h,
        const idMaterial *mat,
        const idVec4 *color,
        float scalex,
        float scaley)
{
  double v10; // st7
  float s0; // [esp+4h] [ebp-4h] BYREF

  renderSystem->SetColor(renderSystem, color);
  if ( scalex < 0.0 )
  {
    w = w * -1.0;
    scalex = scalex * -1.0;
  }
  v10 = scaley;
  if ( scaley < 0.0 )
  {
    h = h * -1.0;
    v10 = v10 * -1.0;
  }
  if ( w >= 0.0 )
  {
    s0 = 0.0;
    color = (const idVec4 *)LODWORD(scalex);
  }
  else
  {
    s0 = scalex;
    w = -w;
    color = 0;
  }
  if ( h >= 0.0 )
  {
    scalex = v10;
    scaley = 0.0;
  }
  else
  {
    scalex = 0.0;
    h = -h;
    scaley = v10;
  }
  if ( !idDeviceContext::ClippedCoords(this, &x, (float *)&y, &w, &h, &s0, &scaley, (float *)&color, &scalex) )
  {
    x = x * this->xScale;
    *(float *)&y = *(float *)&y * this->yScale;
    w = w * this->xScale;
    h = h * this->yScale;
    idDeviceContext::DrawStretchPic(this, x, y, w, h, SLODWORD(s0), SLODWORD(scaley), (int)color, SLODWORD(scalex), mat);
  }
}

// FUNC: public: void __thiscall idDeviceContext::DrawFilledRect(float,float,float,float,class idVec4 const &)
void __thiscall idDeviceContext::DrawFilledRect(
        idDeviceContext *this,
        float x,
        int y,
        float w,
        float h,
        const idVec4 *color)
{
  const idMaterial *whiteImage; // [esp-4h] [ebp-8h]

  if ( color->w != 0.0 )
  {
    renderSystem->SetColor(renderSystem, color);
    if ( !idDeviceContext::ClippedCoords(this, &x, (float *)&y, &w, &h, 0, 0, 0, 0) )
    {
      whiteImage = this->whiteImage;
      x = x * this->xScale;
      *(float *)&y = *(float *)&y * this->yScale;
      w = w * this->xScale;
      h = h * this->yScale;
      idDeviceContext::DrawStretchPic(this, x, y, w, h, 0, 0, 0, 0, whiteImage);
    }
  }
}

// FUNC: public: void __thiscall idDeviceContext::DrawRect(float,float,float,float,float,class idVec4 const &)
void __thiscall idDeviceContext::DrawRect(
        idDeviceContext *this,
        float x,
        int y,
        float w,
        float h,
        float size,
        const idVec4 *color)
{
  const idMaterial *whiteImage; // edx
  float v9; // edi
  float v10; // ebp
  int v11; // ebx
  float v12; // [esp+4h] [ebp-34h]
  int v13; // [esp+8h] [ebp-30h]

  if ( color->w != 0.0 )
  {
    renderSystem->SetColor(renderSystem, color);
    if ( !idDeviceContext::ClippedCoords(this, &x, (float *)&y, &w, &h, 0, 0, 0, 0) )
    {
      whiteImage = this->whiteImage;
      x = x * this->xScale;
      v9 = size;
      v10 = x;
      *(float *)&y = *(float *)&y * this->yScale;
      v11 = y;
      w = w * this->xScale;
      h = h * this->yScale;
      idDeviceContext::DrawStretchPic(this, x, y, size, h, 0, 0, 0, 0, whiteImage);
      v12 = x + w - size;
      idDeviceContext::DrawStretchPic(this, v12, v11, v9, h, 0, 0, 0, 0, this->whiteImage);
      idDeviceContext::DrawStretchPic(this, v10, v11, w, v9, 0, 0, 0, 0, this->whiteImage);
      *(float *)&v13 = *(float *)&y + h - size;
      idDeviceContext::DrawStretchPic(this, v10, v13, w, v9, 0, 0, 0, 0, this->whiteImage);
    }
  }
}

// FUNC: public: void __thiscall idDeviceContext::DrawCursor(float *,float *,float)
void __thiscall idDeviceContext::DrawCursor(idDeviceContext *this, float *x, float *y, float size)
{
  int xa; // [esp+10h] [ebp+4h]
  float sizea; // [esp+18h] [ebp+Ch]

  if ( *x < 0.0 )
    *x = 0.0;
  if ( *x >= (double)this->vidWidth )
    *x = this->vidWidth;
  if ( *y < 0.0 )
    *y = 0.0;
  if ( *y >= (double)this->vidHeight )
    *y = this->vidHeight;
  renderSystem->SetColor(renderSystem, &idDeviceContext::colorWhite);
  *x = *x * this->xScale;
  *(float *)&xa = *y * this->yScale;
  *y = *(float *)&xa;
  sizea = size * this->xScale * this->yScale;
  idDeviceContext::DrawStretchPic(
    this,
    *x,
    xa,
    sizea,
    sizea,
    0,
    0,
    1065353216,
    1065353216,
    this->cursorImages[this->cursor]);
}

// FUNC: private: void __thiscall idDeviceContext::PaintChar(float,float,float,float,float,float,float,float,float,class idMaterial const *)
void __thiscall idDeviceContext::PaintChar(
        idDeviceContext *this,
        float x,
        int y,
        float width,
        float height,
        float scale,
        int s,
        int t,
        int s2,
        int t2,
        const idMaterial *hShader)
{
  width = width * scale;
  scale = height * scale;
  if ( !idDeviceContext::ClippedCoords(
          this,
          &x,
          (float *)&y,
          &width,
          &scale,
          (float *)&s,
          (float *)&t,
          (float *)&s2,
          (float *)&t2) )
  {
    x = x * this->xScale;
    *(float *)&y = *(float *)&y * this->yScale;
    width = width * this->xScale;
    scale = scale * this->yScale;
    idDeviceContext::DrawStretchPic(this, x, y, width, scale, s, t, s2, t2, hShader);
  }
}

// FUNC: private: void __thiscall idDeviceContext::SetFontByScale(float)
void __thiscall idDeviceContext::SetFontByScale(idDeviceContext *this, float scale)
{
  fontInfoEx_t *v2; // eax
  fontInfoEx_t *activeFont; // eax
  fontInfoEx_t *v4; // ecx
  float maxWidthLarge; // eax

  if ( scale > (double)gui_smallFontLimit.internalVar->floatValue )
  {
    activeFont = this->activeFont;
    if ( scale > (double)gui_mediumFontLimit.internalVar->floatValue )
    {
      this->useFont = &activeFont->fontInfoLarge;
      activeFont->maxHeight = activeFont->maxHeightLarge;
      v4 = this->activeFont;
      maxWidthLarge = v4->maxWidthLarge;
    }
    else
    {
      this->useFont = &activeFont->fontInfoMedium;
      activeFont->maxHeight = activeFont->maxHeightMedium;
      v4 = this->activeFont;
      maxWidthLarge = v4->maxWidthMedium;
    }
    v4->maxWidth = maxWidthLarge;
  }
  else
  {
    v2 = this->activeFont;
    this->useFont = &v2->fontInfoSmall;
    v2->maxHeight = v2->maxHeightSmall;
    this->activeFont->maxWidth = this->activeFont->maxWidthSmall;
  }
}

// FUNC: public: int __thiscall idDeviceContext::CharWidth(char,float,int)
int __thiscall idDeviceContext::CharWidth(idDeviceContext *this, unsigned __int8 c, float scale, int adjust)
{
  fontInfo_s *useFont; // ecx

  idDeviceContext::SetFontByScale(this, scale);
  useFont = this->useFont;
  if ( useFont->pointSize == 0.0 )
    return 0;
  return (int)(float)((double)(adjust + (int)ceil(useFont->glyphs[c].horiAdvance))
                    / this->useFont->pointSize
                    * scale
                    * 48.0);
}

// FUNC: public: int __thiscall idDeviceContext::MaxCharWidth(float)
int __thiscall idDeviceContext::MaxCharWidth(idDeviceContext *this, float scale)
{
  fontInfo_s *useFont; // ecx

  idDeviceContext::SetFontByScale(this, scale);
  useFont = this->useFont;
  if ( useFont->pointSize == 0.0 )
    return 0;
  return (int)(float)(scale / useFont->pointSize * 48.0 * this->activeFont->maxWidth);
}

// FUNC: public: int __thiscall idDeviceContext::MaxCharHeight(float)
int __thiscall idDeviceContext::MaxCharHeight(idDeviceContext *this, float scale)
{
  fontInfo_s *useFont; // ecx

  idDeviceContext::SetFontByScale(this, scale);
  useFont = this->useFont;
  if ( useFont->pointSize == 0.0 )
    return 0;
  return (int)(float)(scale / useFont->pointSize * 48.0 * this->activeFont->maxHeight);
}

// FUNC: public: void __thiscall idDeviceContext::DrawEditCursor(float,float,float)
void __thiscall idDeviceContext::DrawEditCursor(idDeviceContext *this, float x, float y, float scale)
{
  fontInfo_s *useFont; // ecx
  glyphInfo_s *v6; // eax
  int v7; // [esp+0h] [ebp-28h]
  float scalea; // [esp+34h] [ebp+Ch]

  if ( (com_ticNumber & 0x10) == 0 )
  {
    idDeviceContext::SetFontByScale(this, scale);
    useFont = this->useFont;
    if ( useFont->pointSize != 0.0 )
    {
      v6 = &useFont->glyphs[this->overStrikeMode ? 95 : 124];
      scalea = scale / useFont->pointSize * 48.0;
      *(float *)&v7 = y - (scalea * v6->horiBearingY - 1.0);
      idDeviceContext::PaintChar(
        this,
        x,
        v7,
        v6->width,
        v6->height,
        scalea,
        LODWORD(v6->s1),
        LODWORD(v6->t1),
        LODWORD(v6->s2),
        LODWORD(v6->t2),
        useFont->material);
    }
  }
}

// FUNC: public: int __thiscall idDeviceContext::FindFont(char const *)
int __thiscall idDeviceContext::FindFont(idDeviceContext *this, char *name)
{
  int num; // edi
  int v3; // esi
  int v5; // ebp
  const char *v6; // eax
  int v7; // esi
  int v8; // eax
  char *data; // edx
  char *v10; // ecx
  char v11; // al
  const char *v12; // eax
  fontInfoEx_t *list; // ebp
  int granularity; // ecx
  int v15; // edi
  int size; // ebx
  int v17; // eax
  idMaterial *material; // ecx
  idMaterial *v19; // ecx
  idMaterial *v20; // eax
  fontInfoEx_t *v22; // eax
  int v23; // edx
  char *v24; // eax
  int v25; // eax
  fontInfoEx_t *v26; // ebx
  fontInfoEx_t *v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // edi
  int v31; // esi
  char *v32; // [esp-4h] [ebp-6CDCh]
  idStr v33; // [esp+10h] [ebp-6CC8h] BYREF
  char v34[27804]; // [esp+30h] [ebp-6CA8h] BYREF
  int v35; // [esp+6CD4h] [ebp-4h]

  num = idDeviceContext::fonts.num;
  v3 = 0;
  if ( idDeviceContext::fonts.num <= 0 )
  {
LABEL_5:
    v33.len = 0;
    v33.alloced = 20;
    v33.data = v33.baseBuffer;
    v33.baseBuffer[0] = 0;
    if ( name )
    {
      v6 = &name[strlen(name) + 1];
      v7 = v6 - (name + 1);
      v8 = v6 - name;
      if ( v8 > 20 )
        idStr::ReAllocate(&v33, v8, 1);
      data = v33.data;
      v10 = name;
      do
      {
        v11 = *v10;
        *data++ = *v10++;
      }
      while ( v11 );
      v33.len = v7;
    }
    v32 = this->fontLang.data;
    v35 = 0;
    v12 = va("fonts/%s", v32);
    idStr::Replace(&v33, "fonts", v12);
    list = idDeviceContext::fonts.list;
    granularity = idDeviceContext::fonts.granularity;
    if ( !idDeviceContext::fonts.list )
    {
      if ( idDeviceContext::fonts.granularity <= 0 )
      {
        v15 = 0;
        size = 0;
        idDeviceContext::fonts.num = 0;
        idDeviceContext::fonts.size = 0;
        goto LABEL_29;
      }
      if ( idDeviceContext::fonts.granularity != idDeviceContext::fonts.size )
      {
        idDeviceContext::fonts.size = idDeviceContext::fonts.granularity;
        if ( idDeviceContext::fonts.granularity < idDeviceContext::fonts.num )
          idDeviceContext::fonts.num = idDeviceContext::fonts.granularity;
        v22 = (fontInfoEx_t *)Memory::Allocate(27804 * idDeviceContext::fonts.granularity);
        v23 = 0;
        list = v22;
        idDeviceContext::fonts.list = v22;
        if ( idDeviceContext::fonts.num > 0 )
        {
          v24 = 0;
          do
          {
            qmemcpy((char *)list + (_DWORD)v24, v24, sizeof(fontInfoEx_t));
            list = idDeviceContext::fonts.list;
            ++v23;
            v24 += 27804;
          }
          while ( v23 < idDeviceContext::fonts.num );
        }
        granularity = idDeviceContext::fonts.granularity;
      }
    }
    v15 = idDeviceContext::fonts.num;
    size = idDeviceContext::fonts.size;
    if ( idDeviceContext::fonts.num != idDeviceContext::fonts.size )
    {
LABEL_43:
      qmemcpy(&list[idDeviceContext::fonts.num++], v34, sizeof(fontInfoEx_t));
      v30 = idDeviceContext::fonts.num - 1;
      v31 = idDeviceContext::fonts.num - 1;
      if ( renderSystem->RegisterFont(renderSystem, v33.data, &idDeviceContext::fonts.list[v31]) )
      {
        idStr::Copynz(idDeviceContext::fonts.list[v31].name, name, 64);
        v35 = -1;
        idStr::FreeData(&v33);
        return v30;
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "Could not register font %s [%s]\n",
          name,
          v33.data);
        v35 = -1;
        idStr::FreeData(&v33);
        return -1;
      }
    }
LABEL_29:
    if ( !granularity )
    {
      granularity = 16;
      idDeviceContext::fonts.granularity = 16;
    }
    v25 = size + granularity - (size + granularity) % granularity;
    if ( v25 > 0 )
    {
      if ( v25 != size )
      {
        v26 = list;
        idDeviceContext::fonts.size = v25;
        if ( v25 < v15 )
          idDeviceContext::fonts.num = v25;
        v27 = (fontInfoEx_t *)Memory::Allocate(27804 * v25);
        v28 = 0;
        list = v27;
        idDeviceContext::fonts.list = v27;
        if ( idDeviceContext::fonts.num > 0 )
        {
          v29 = 0;
          do
          {
            qmemcpy(&list[v29], &v26[v29], sizeof(fontInfoEx_t));
            list = idDeviceContext::fonts.list;
            ++v28;
            ++v29;
          }
          while ( v28 < idDeviceContext::fonts.num );
        }
        if ( v26 )
        {
          Memory::Free(v26);
          list = idDeviceContext::fonts.list;
        }
      }
    }
    else
    {
      if ( list )
        Memory::Free(list);
      list = 0;
      idDeviceContext::fonts.list = 0;
      idDeviceContext::fonts.num = 0;
      idDeviceContext::fonts.size = 0;
    }
    goto LABEL_43;
  }
  v5 = 0;
  while ( idStr::Icmp(name, idDeviceContext::fonts.list[v5].name) )
  {
    ++v3;
    ++v5;
    if ( v3 >= num )
      goto LABEL_5;
  }
  v17 = v3;
  material = idDeviceContext::fonts.list[v3].fontInfoSmall.material;
  if ( material )
    material->sort = -2.0;
  v19 = idDeviceContext::fonts.list[v17].fontInfoMedium.material;
  if ( v19 )
    v19->sort = -2.0;
  v20 = idDeviceContext::fonts.list[v17].fontInfoLarge.material;
  if ( v20 )
    v20->sort = -2.0;
  return v3;
}

// FUNC: public: void __thiscall idDeviceContext::SetupFonts(void)
void __thiscall idDeviceContext::SetupFonts(idDeviceContext *this)
{
  fontInfoEx_t *list; // ebx
  fontInfoEx_t *v3; // eax
  int v4; // edx
  int v5; // eax
  char *v6; // eax

  list = idDeviceContext::fonts.list;
  idDeviceContext::fonts.granularity = 1;
  if ( idDeviceContext::fonts.list && idDeviceContext::fonts.num != idDeviceContext::fonts.size )
  {
    if ( idDeviceContext::fonts.num > 0 )
    {
      idDeviceContext::fonts.size = idDeviceContext::fonts.num;
      v3 = (fontInfoEx_t *)Memory::Allocate(27804 * idDeviceContext::fonts.num);
      v4 = 0;
      idDeviceContext::fonts.list = v3;
      if ( idDeviceContext::fonts.num > 0 )
      {
        v5 = 0;
        do
        {
          ++v4;
          qmemcpy(&idDeviceContext::fonts.list[v5], &list[v5], sizeof(idDeviceContext::fonts.list[v5]));
          ++v5;
        }
        while ( v4 < idDeviceContext::fonts.num );
      }
      if ( list )
        Memory::Free(list);
    }
    else
    {
      Memory::Free(idDeviceContext::fonts.list);
      idDeviceContext::fonts.list = 0;
      idDeviceContext::fonts.num = 0;
      idDeviceContext::fonts.size = 0;
    }
  }
  v6 = (char *)cvarSystem->GetCVarString(cvarSystem, "sys_lang");
  idStr::operator=(&this->fontLang, v6);
  if ( !idStr::Cmp(this->fontLang.data, "french")
    || !idStr::Cmp(this->fontLang.data, "german")
    || !idStr::Cmp(this->fontLang.data, "spanish")
    || !idStr::Cmp(this->fontLang.data, "italian") )
  {
    idStr::operator=(&this->fontLang, "english");
  }
  idDeviceContext::FindFont(this, "fonts/chain");
}

// FUNC: public: void __thiscall idDeviceContext::Init(void)
void __thiscall idDeviceContext::Init(idDeviceContext *this)
{
  const idMaterial *v2; // eax

  this->xScale = 0.0;
  idDeviceContext::SetSize(this, 640.0, 480.0);
  v2 = declManager->FindMaterial(declManager, "gfx/guis/white.tga", 1);
  this->whiteImage = v2;
  v2->sort = -2.0;
  this->mbcs = 0;
  idDeviceContext::SetupFonts(this);
  this->activeFont = idDeviceContext::fonts.list;
  idDeviceContext::colorPurple.x = 1.0;
  idDeviceContext::colorPurple.y = 0.0;
  idDeviceContext::colorPurple.w = 1.0;
  idDeviceContext::colorOrange.x = 1.0;
  idDeviceContext::colorPurple.z = 1.0;
  idDeviceContext::colorOrange.z = 0.0;
  idDeviceContext::colorOrange.w = 1.0;
  idDeviceContext::colorOrange.y = 1.0;
  idDeviceContext::colorYellow.y = 1.0;
  idDeviceContext::colorYellow.z = 1.0;
  idDeviceContext::colorYellow.x = 0.0;
  idDeviceContext::colorGreen.x = 0.0;
  idDeviceContext::colorGreen.y = 1.0;
  idDeviceContext::colorYellow.w = 1.0;
  idDeviceContext::colorGreen.w = 1.0;
  idDeviceContext::colorBlue.x = 0.0;
  idDeviceContext::colorGreen.z = 0.0;
  idDeviceContext::colorBlue.y = 0.0;
  idDeviceContext::colorBlue.z = 1.0;
  idDeviceContext::colorBlue.w = 1.0;
  idDeviceContext::colorRed.x = 1.0;
  idDeviceContext::colorRed.z = 0.0;
  idDeviceContext::colorRed.y = 0.0;
  idDeviceContext::colorWhite.y = 1.0;
  idDeviceContext::colorRed.w = 1.0;
  idDeviceContext::colorWhite.x = 1.0;
  idDeviceContext::colorBlack.x = 0.0;
  idDeviceContext::colorWhite.z = 1.0;
  idDeviceContext::colorWhite.w = 1.0;
  idDeviceContext::colorBlack.w = 1.0;
  idDeviceContext::colorBlack.y = 0.0;
  idDeviceContext::colorNone.x = 0.0;
  idDeviceContext::colorNone.w = 0.0;
  idDeviceContext::colorBlack.z = 0.0;
  idDeviceContext::colorNone.y = 0.0;
  idDeviceContext::colorNone.z = 0.0;
  this->cursorImages[0] = declManager->FindMaterial(declManager, "gfx/guis/guicursor_arrow.tga", 1);
  this->cursorImages[1] = declManager->FindMaterial(declManager, "gfx/guis/guicursor_hand.tga", 1);
  this->scrollBarImages[0] = declManager->FindMaterial(declManager, "gfx/guis/scrollbarh.tga", 1);
  this->scrollBarImages[1] = declManager->FindMaterial(declManager, "gfx/guis/scrollbarv.tga", 1);
  this->scrollBarImages[2] = declManager->FindMaterial(declManager, "gfx/guis/scrollbar_thumb.tga", 1);
  this->scrollBarImages[3] = declManager->FindMaterial(declManager, "gfx/guis/scrollbar_right.tga", 1);
  this->scrollBarImages[4] = declManager->FindMaterial(declManager, "gfx/guis/scrollbar_left.tga", 1);
  this->scrollBarImages[5] = declManager->FindMaterial(declManager, "gfx/guis/scrollbar_up.tga", 1);
  this->scrollBarImages[6] = declManager->FindMaterial(declManager, "gfx/guis/scrollbar_down.tga", 1);
  this->cursorImages[0]->sort = -2.0;
  this->cursorImages[1]->sort = -2.0;
  this->scrollBarImages[0]->sort = -2.0;
  this->scrollBarImages[1]->sort = -2.0;
  this->scrollBarImages[2]->sort = -2.0;
  this->scrollBarImages[3]->sort = -2.0;
  this->scrollBarImages[4]->sort = -2.0;
  this->scrollBarImages[5]->sort = -2.0;
  this->scrollBarImages[6]->sort = -2.0;
  this->cursor = 0;
  this->enableClipping = 1;
  this->overStrikeMode = 1;
  this->mat = mat3_identity;
  this->isMatIdentity = 1;
  this->origin.z = 0.0;
  this->origin.y = 0.0;
  this->origin.x = 0.0;
  this->initialized = 1;
}

// FUNC: public: void __thiscall idDeviceContext::PushClipRect(class idRectangle)
void __thiscall idDeviceContext::PushClipRect(idDeviceContext *this, idRectangle r)
{
  idList<idRectangle> *p_clipRects; // esi
  int size; // eax

  p_clipRects = &this->clipRects;
  if ( !this->clipRects.list )
    idList<idRectangle>::Resize(&this->clipRects, this->clipRects.granularity);
  size = p_clipRects->size;
  if ( p_clipRects->num == size )
  {
    if ( !p_clipRects->granularity )
      p_clipRects->granularity = 16;
    idList<idRectangle>::Resize(
      p_clipRects,
      size + p_clipRects->granularity - (size + p_clipRects->granularity) % p_clipRects->granularity);
  }
  p_clipRects->list[p_clipRects->num++] = r;
}

// FUNC: public: void __thiscall idDeviceContext::RegisterIcon(char const *,char const *,int,int,int,int)
void __thiscall idDeviceContext::RegisterIcon(
        idDeviceContext *this,
        const char *code,
        const char *shader,
        int x,
        int y,
        int w,
        int h)
{
  char v8; // cl
  int v9; // edx
  idHashTable<embeddedIcon_s> *p_icons; // edi
  char *i; // eax
  int v12; // ebx
  idHashTable<embeddedIcon_s>::hashnode_s *v13; // esi
  int v14; // eax
  embeddedIcon_s icon; // [esp+8h] [ebp-20h] BYREF

  strcpy(icon.code, code);
  icon.shader = declManager->FindMaterial(declManager, shader, 1);
  icon.shader->base->EnsureNotPurged(icon.shader->base);
  icon.shader->sort = -2.0;
  icon.s1 = (float)x;
  icon.width = w;
  icon.height = h;
  icon.t1 = (float)y;
  icon.s2 = icon.s1;
  icon.t2 = icon.t1;
  if ( idMaterial::GetImageHeight((idMaterial *)icon.shader) && idMaterial::GetImageWidth((idMaterial *)icon.shader) )
    idDeviceContext::SizeIcon(this, &icon);
  v8 = icon.code[0];
  v9 = 0;
  p_icons = &this->icons;
  for ( i = icon.code; v8; v9 += v12 )
  {
    v12 = v8 * (_DWORD)&i[119 - (_DWORD)icon.code];
    v8 = *++i;
  }
  v13 = this->icons.heads[v9 & this->icons.tablesizemask];
  if ( v13 )
  {
    while ( 1 )
    {
      v14 = idStr::Cmp(v13->key.data, icon.code);
      if ( !v14 )
        break;
      if ( v14 <= 0 )
      {
        v13 = v13->next;
        if ( v13 )
          continue;
      }
      goto LABEL_10;
    }
    qmemcpy(&v13->value, &icon, sizeof(v13->value));
  }
  else
  {
LABEL_10:
    idHashTable<embeddedIcon_s>::Set(p_icons, icon.code, &icon);
  }
}

// FUNC: public: int __thiscall idDeviceContext::DrawTextA(float,float,float,class idVec4,char const *,float,int,int,int,bool)
int __userpurge idDeviceContext::DrawTextA@<eax>(
        idDeviceContext *this@<ecx>,
        float *p_y@<esi>,
        float x,
        float y,
        float scale,
        idVec4 color,
        const char *text,
        float adjust,
        int limit,
        int style,
        int cursor,
        bool resetEscapes)
{
  fontInfo_s *useFont; // ecx
  const char *v15; // ebp
  float v16; // ecx
  float z; // edx
  int v18; // eax
  bool v19; // zf
  float *p_width; // esi
  int IsEscape; // edx
  float v22; // edx
  float v23; // eax
  float w; // ecx
  double v25; // st7
  double v26; // st7
  int v27; // eax
  float v28; // ecx
  float v29; // edx
  float v30; // eax
  char v31; // cl
  fontInfo_s *v32; // ebx
  const glyphInfo_s *v33; // ebx
  int v34; // edx
  char *v35; // eax
  int v36; // ebx
  idHashTable<embeddedIcon_s>::hashnode_s *v37; // esi
  int v38; // eax
  double v39; // st7
  float s2; // eax
  float t1; // ecx
  float s1; // edx
  idMaterial *material; // edx
  float v44; // eax
  float v45; // ecx
  float v46; // ebx
  idMaterial *v47; // eax
  float v48; // ecx
  float v49; // edx
  idMaterial *v50; // ecx
  float v51; // edx
  float v52; // eax
  double v53; // st7
  float v54; // [esp+8h] [ebp-DCh]
  float v55; // [esp+Ch] [ebp-D8h]
  float v56; // [esp+Ch] [ebp-D8h]
  float width; // [esp+10h] [ebp-D4h]
  float height; // [esp+14h] [ebp-D0h]
  float X; // [esp+28h] [ebp-BCh]
  const idMaterial *X_4; // [esp+2Ch] [ebp-B8h]
  int yy; // [esp+40h] [ebp-A4h]
  float yya; // [esp+40h] [ebp-A4h]
  const glyphInfo_s *refglyph; // [esp+44h] [ebp-A0h]
  float useScale; // [esp+48h] [ebp-9Ch]
  int esc; // [esp+4Ch] [ebp-98h]
  idVec4 newColor; // [esp+50h] [ebp-94h] BYREF
  int count; // [esp+60h] [ebp-84h]
  float xx; // [esp+64h] [ebp-80h]
  char code[4]; // [esp+68h] [ebp-7Ch] BYREF
  int len; // [esp+70h] [ebp-74h]
  float v72; // [esp+74h] [ebp-70h]
  float v73; // [esp+78h] [ebp-6Ch]
  float v74; // [esp+7Ch] [ebp-68h]
  float v75; // [esp+80h] [ebp-64h]
  float v76; // [esp+84h] [ebp-60h]
  float v77; // [esp+88h] [ebp-5Ch]
  float v78; // [esp+8Ch] [ebp-58h]
  float v79; // [esp+90h] [ebp-54h]
  float v80; // [esp+98h] [ebp-4Ch]
  float v81; // [esp+9Ch] [ebp-48h]
  float v82; // [esp+A0h] [ebp-44h]
  float v83; // [esp+A8h] [ebp-3Ch]
  float v84; // [esp+ACh] [ebp-38h]
  float v85; // [esp+B0h] [ebp-34h]
  int v86[4]; // [esp+B4h] [ebp-30h] BYREF
  int v87[4]; // [esp+C4h] [ebp-20h] BYREF
  int v88[4]; // [esp+D4h] [ebp-10h] BYREF

  idDeviceContext::SetFontByScale(this, scale);
  useFont = this->useFont;
  if ( useFont->pointSize == 0.0 )
    return 0;
  useScale = scale / useFont->pointSize * 48.0;
  if ( resetEscapes )
  {
    this->drawTextColor = color;
    this->drawTextColorAdjust = 0.0;
  }
  v15 = text;
  count = 0;
  if ( text && color.w != 0.0 )
  {
    renderSystem->SetColor(renderSystem, &this->drawTextColor);
    v16 = this->drawTextColor.y;
    z = this->drawTextColor.z;
    newColor.x = this->drawTextColor.x;
    newColor.w = this->drawTextColor.w;
    *(float *)&v18 = 0.0;
    v19 = *text == 0;
    newColor.y = v16;
    newColor.z = z;
    if ( !v19 )
    {
      do
        ++v18;
      while ( text[v18] );
    }
    len = v18;
    if ( limit > 0 && v18 > limit )
      len = limit;
    while ( 1 )
    {
      if ( !*v15 || count >= len )
      {
LABEL_55:
        if ( cursor != -1 && cursor <= count )
          idDeviceContext::DrawEditCursor(this, x, y, scale);
        return count;
      }
      p_width = &this->useFont->glyphs[*(unsigned __int8 *)v15].width;
      IsEscape = idStr::IsEscape(v15, 0);
      esc = IsEscape;
      if ( IsEscape )
      {
        yy = 0;
        while ( 1 )
        {
          switch ( v15[1] )
          {
            case '+':
              v25 = this->drawTextColorAdjust + 0.1;
              this->drawTextColorAdjust = v25;
              v83 = v25;
              v84 = v25;
              v85 = v25;
              v72 = v25 + this->drawTextColor.x;
              newColor.x = v72;
              v73 = v83 + this->drawTextColor.y;
              newColor.y = v73;
              v74 = v84 + this->drawTextColor.z;
              newColor.z = v74;
              v75 = v85 + this->drawTextColor.w;
              newColor.w = color.w;
              renderSystem->SetColor(renderSystem, &newColor);
              goto LABEL_38;
            case '-':
              v26 = this->drawTextColorAdjust - 0.1;
              this->drawTextColorAdjust = v26;
              v80 = v26;
              v81 = v26;
              v82 = v26;
              v76 = v26 + this->drawTextColor.x;
              newColor.x = v76;
              v77 = v80 + this->drawTextColor.y;
              newColor.y = v77;
              v78 = v81 + this->drawTextColor.z;
              newColor.z = v78;
              v79 = v82 + this->drawTextColor.w;
              newColor.w = color.w;
              renderSystem->SetColor(renderSystem, &newColor);
              goto LABEL_38;
            case '0':
            case 'R':
            case 'r':
              v23 = color.z;
              this->drawTextColor = color;
              newColor.x = color.x;
              newColor.y = color.y;
              newColor.w = color.w;
              goto LABEL_27;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case ':':
              this->drawTextColor = *idStr::ColorForIndex(*((unsigned __int8 *)v15 + 1));
              this->drawTextColor.w = color.w;
              v22 = this->drawTextColor.y;
              newColor.x = this->drawTextColor.x;
              v23 = this->drawTextColor.z;
              w = this->drawTextColor.w;
              newColor.y = v22;
              newColor.w = w;
LABEL_27:
              newColor.z = v23;
              goto LABEL_28;
            case 'C':
            case 'c':
              this->drawTextColor.x = (double)(*((unsigned __int8 *)v15 + 2) - 48) * 0.11111111;
              this->drawTextColor.y = (double)(*((unsigned __int8 *)v15 + 3) - 48) * 0.11111111;
              refglyph = (const glyphInfo_s *)(*((unsigned __int8 *)v15 + 4) - 48);
              this->drawTextColor.z = (double)(int)refglyph * 0.11111111;
              v28 = this->drawTextColor.y;
              newColor.x = this->drawTextColor.x;
              v29 = this->drawTextColor.z;
              v30 = this->drawTextColor.w;
              newColor.y = v28;
              newColor.z = v29;
              newColor.w = v30;
LABEL_28:
              this->drawTextColorAdjust = 0.0;
              renderSystem->SetColor(renderSystem, &newColor);
              goto LABEL_38;
            case 'I':
            case 'i':
              v31 = v15[2];
              v32 = this->useFont;
              code[0] = v31;
              code[1] = v15[3];
              v33 = &v32->glyphs[87];
              v34 = 0;
              code[2] = v15[4];
              refglyph = v33;
              code[3] = 0;
              v35 = code;
              if ( v31 )
              {
                do
                {
                  v36 = v31 * (_DWORD)&v35[119 - (_DWORD)code];
                  v31 = *++v35;
                  v34 += v36;
                }
                while ( v31 );
                v33 = refglyph;
              }
              v37 = this->icons.heads[v34 & this->icons.tablesizemask];
              if ( !v37 )
                goto LABEL_38;
              break;
            case 'N':
            case 'n':
              v27 = *((unsigned __int8 *)v15 + 2) - 48;
              if ( v27 >= 9 )
                v27 = 9;
              yy += v27;
              v15 += IsEscape;
              esc = idStr::IsEscape(v15, 0);
              if ( !esc )
                goto LABEL_24;
              goto LABEL_38;
            default:
LABEL_24:
              yy = 0;
              goto LABEL_38;
          }
          while ( 1 )
          {
            v38 = idStr::Cmp(v37->key.data, code);
            if ( !v38 )
              break;
            if ( v38 <= 0 )
            {
              v37 = v37->next;
              if ( v37 )
                continue;
            }
            goto LABEL_38;
          }
          v39 = (double)v37->value.height;
          s2 = v37->value.s2;
          X_4 = v37->value.shader;
          t1 = v37->value.t1;
          X = v37->value.t2;
          s1 = v37->value.s1;
          xx = v33->height / v39;
          height = v39 * xx;
          width = (double)v37->value.width * xx;
          v55 = y - useScale * v33->horiBearingY - 1.0;
          idDeviceContext::PaintChar(this, x, v55, width, height, useScale, s1, t1, s2, X, X_4);
          x = (double)v37->value.width * xx + x;
LABEL_38:
          if ( --yy < 0 )
            break;
          IsEscape = esc;
        }
        v15 += esc;
        count += esc;
        goto LABEL_54;
      }
      xx = useScale * p_width[3] + x;
      yya = y - useScale * p_width[4] - 1.0;
      if ( style == 1 )
      {
        v88[3] = LODWORD(newColor.w);
        memset(v88, 0, 12);
        renderSystem->SetColor(renderSystem, (const idVec4 *)v88);
        v56 = yya + 1.0;
        v54 = xx + 1.0;
        idDeviceContext::PaintChar(
          this,
          v54,
          v56,
          *p_width,
          p_width[1],
          useScale,
          p_width[5],
          p_width[6],
          p_width[7],
          p_width[8],
          this->useFont->material);
        renderSystem->SetColor(renderSystem, &newColor);
      }
      else if ( style == 2 )
      {
        if ( newColor.x >= 0.2 || newColor.y >= 0.2 || newColor.z >= 0.2 )
        {
          v87[3] = LODWORD(newColor.w);
          memset(v87, 0, 12);
          ((void (__thiscall *)(idRenderSystem *, int *, float *))renderSystem->SetColor)(renderSystem, v87, p_y);
        }
        else
        {
          v86[3] = LODWORD(newColor.w);
          v86[0] = 1065353216;
          v86[1] = 1065353216;
          v86[2] = 1065353216;
          ((void (__thiscall *)(idRenderSystem *, int *, float *))renderSystem->SetColor)(renderSystem, v86, p_y);
        }
        material = this->useFont->material;
        v44 = p_width[8];
        v45 = p_width[7];
        v46 = 0.0;
        newColor.x = *(float *)&refglyph + 1.0;
        useScale = *(float *)code + 1.0;
        idDeviceContext::PaintChar(
          this,
          useScale,
          newColor.x,
          *p_width,
          p_width[1],
          0.0,
          p_width[5],
          p_width[6],
          v45,
          v44,
          material);
        v47 = this->useFont->material;
        v48 = p_width[8];
        v49 = p_width[7];
        *(float *)&len = *(float *)code - 1.0;
        idDeviceContext::PaintChar(
          this,
          *(float *)&len,
          newColor.x,
          *p_width,
          p_width[1],
          0.0,
          p_width[5],
          p_width[6],
          v49,
          v48,
          v47);
        v50 = this->useFont->material;
        v51 = p_width[8];
        v52 = p_width[7];
        newColor.x = *(float *)&refglyph - 1.0;
        idDeviceContext::PaintChar(
          this,
          *(float *)&len,
          newColor.x,
          *p_width,
          p_width[1],
          0.0,
          p_width[5],
          p_width[6],
          v52,
          v51,
          v50);
        idDeviceContext::PaintChar(
          this,
          useScale,
          newColor.x,
          *p_width,
          p_width[1],
          0.0,
          p_width[5],
          p_width[6],
          p_width[7],
          p_width[8],
          this->useFont->material);
        p_y = &newColor.y;
        ((void (__thiscall *)(idRenderSystem *))renderSystem->SetColor)(renderSystem);
        goto LABEL_50;
      }
      v46 = useScale;
LABEL_50:
      idDeviceContext::PaintChar(
        this,
        xx,
        yya,
        *p_width,
        p_width[1],
        v46,
        p_width[5],
        p_width[6],
        p_width[7],
        p_width[8],
        this->useFont->material);
      if ( cursor != -1 && cursor <= count )
      {
        idDeviceContext::DrawEditCursor(this, x, y, scale);
        cursor = -1;
      }
      v53 = ceil((adjust + p_width[2]) * useScale);
      ++count;
      ++v15;
      x = v53 + x;
LABEL_54:
      if ( !v15 )
        goto LABEL_55;
    }
  }
  return count;
}

// FUNC: public: int __thiscall idDeviceContext::TextWidth(char const *,float,int,int)
int __thiscall idDeviceContext::TextWidth(idDeviceContext *this, const char *text, float scale, int limit, int adjust)
{
  int v6; // edi
  double pointSize; // st6
  fontInfo_s *v8; // eax
  int v11; // ebx
  char v12; // cl
  int v13; // edx
  char *v14; // eax
  int v15; // ebx
  idHashTable<embeddedIcon_s>::hashnode_s *v16; // esi
  int v17; // eax
  double v18; // st7
  int IsEscape; // ebx
  char v20; // cl
  int v21; // edx
  char *v22; // eax
  int v23; // ebx
  idHashTable<embeddedIcon_s>::hashnode_s *v24; // esi
  int v25; // eax
  double v26; // st7
  char code[4]; // [esp+18h] [ebp-18h] BYREF
  int width; // [esp+1Ch] [ebp-14h]
  int type; // [esp+20h] [ebp-10h] BYREF
  idDeviceContext *v30; // [esp+24h] [ebp-Ch]
  const glyphInfo_s *refglyph; // [esp+28h] [ebp-8h]
  fontInfo_s *useFont; // [esp+2Ch] [ebp-4h]
  const char *texta; // [esp+34h] [ebp+4h]
  int limita; // [esp+3Ch] [ebp+Ch]

  v6 = 0;
  v30 = this;
  type = 0;
  idDeviceContext::SetFontByScale(this, scale);
  pointSize = this->useFont->pointSize;
  useFont = this->useFont;
  if ( pointSize == 0.0 )
    return 0;
  v8 = this->useFont;
  refglyph = &v8->glyphs[87];
  if ( v8 == (fontInfo_s *)-3132 )
    return 0;
  if ( !text )
    return 0;
  width = 0;
  if ( limit <= 0 )
  {
    if ( *text )
    {
      do
      {
        IsEscape = idStr::IsEscape(&text[v6], &type);
        limita = IsEscape;
        if ( IsEscape )
        {
          if ( type == 8 )
          {
            v20 = text[v6 + 2];
            code[0] = v20;
            code[1] = text[v6 + 3];
            v21 = 0;
            code[2] = text[v6 + 4];
            code[3] = 0;
            v22 = code;
            if ( v20 )
            {
              do
              {
                v23 = v20 * (_DWORD)&v22[119 - (_DWORD)code];
                v20 = *++v22;
                v21 += v23;
              }
              while ( v20 );
              IsEscape = limita;
            }
            v24 = v30->icons.heads[v21 & v30->icons.tablesizemask];
            if ( v24 )
            {
              while ( 1 )
              {
                v25 = idStr::Cmp(v24->key.data, code);
                if ( !v25 )
                  break;
                if ( v25 > 0 )
                  goto LABEL_36;
                v24 = v24->next;
                if ( !v24 )
                {
                  v6 = v6 + IsEscape - 1;
                  goto LABEL_38;
                }
              }
              width = (int)(refglyph->height / (double)v24->value.height * (double)v24->value.width + (double)width);
            }
          }
LABEL_36:
          v6 = v6 + IsEscape - 1;
        }
        else
        {
          v26 = ceil(useFont->glyphs[(unsigned __int8)text[v6]].horiAdvance);
          width = adjust + (int)(v26 + (double)width);
        }
LABEL_38:
        ++v6;
      }
      while ( text[v6] );
    }
  }
  else if ( *text )
  {
    do
    {
      if ( v6 >= limit )
        break;
      v11 = idStr::IsEscape(&text[v6], &type);
      texta = (const char *)v11;
      if ( v11 )
      {
        if ( type == 8 )
        {
          v12 = text[v6 + 2];
          code[0] = v12;
          code[1] = text[v6 + 3];
          v13 = 0;
          code[2] = text[v6 + 4];
          code[3] = 0;
          v14 = code;
          if ( v12 )
          {
            do
            {
              v15 = v12 * (_DWORD)&v14[119 - (_DWORD)code];
              v12 = *++v14;
              v13 += v15;
            }
            while ( v12 );
            v11 = (int)texta;
          }
          v16 = v30->icons.heads[v13 & v30->icons.tablesizemask];
          if ( v16 )
          {
            while ( 1 )
            {
              v17 = idStr::Cmp(v16->key.data, code);
              if ( !v17 )
                break;
              if ( v17 > 0 )
                goto LABEL_20;
              v16 = v16->next;
              if ( !v16 )
              {
                v6 = v6 + v11 - 1;
                goto LABEL_22;
              }
            }
            width = (int)(refglyph->height / (double)v16->value.height * (double)v16->value.width + (double)width);
          }
        }
LABEL_20:
        v6 = v6 + v11 - 1;
      }
      else
      {
        v18 = ceil(useFont->glyphs[(unsigned __int8)text[v6]].horiAdvance);
        width = adjust + (int)(v18 + (double)width);
      }
LABEL_22:
      ++v6;
    }
    while ( text[v6] );
  }
  return (int)(float)((double)width / v30->useFont->pointSize * scale * 48.0);
}

// FUNC: public: bool __thiscall idDeviceContext::GetMaxTextIndex(char const *,int,float,struct wrapInfo_t &)
char __thiscall idDeviceContext::GetMaxTextIndex(
        idDeviceContext *this,
        const char *text,
        int limit,
        float textScale,
        wrapInfo_t *wrapInfo)
{
  int v6; // edi
  fontInfo_s *useFont; // esi
  double pointSize; // st6
  bool v11; // zf
  int IsEscape; // ebx
  char v13; // cl
  int v14; // edx
  char *v15; // eax
  int v16; // ebx
  idHashTable<embeddedIcon_s>::hashnode_s *v17; // esi
  int v18; // eax
  double v19; // st7
  char code[4]; // [esp+18h] [ebp-18h] BYREF
  int width; // [esp+1Ch] [ebp-14h]
  int type; // [esp+20h] [ebp-10h] BYREF
  idDeviceContext *v23; // [esp+24h] [ebp-Ch]
  fontInfo_s *v24; // [esp+28h] [ebp-8h]
  int v25; // [esp+2Ch] [ebp-4h]
  const char *texta; // [esp+34h] [ebp+4h]
  float textb; // [esp+34h] [ebp+4h]

  v6 = 0;
  v23 = this;
  type = 0;
  idDeviceContext::SetFontByScale(this, textScale);
  useFont = this->useFont;
  pointSize = useFont->pointSize;
  v24 = useFont;
  if ( pointSize == 0.0 )
    return 0;
  if ( !text )
    return 0;
  v11 = *text == 0;
  width = 0;
  if ( v11 )
    return 0;
  while ( 1 )
  {
    IsEscape = idStr::IsEscape(&text[v6], &type);
    texta = (const char *)IsEscape;
    if ( IsEscape )
    {
      if ( type == 8 )
      {
        v13 = text[v6 + 2];
        code[0] = v13;
        code[1] = text[v6 + 3];
        v14 = 0;
        code[2] = text[v6 + 4];
        code[3] = 0;
        v15 = code;
        if ( v13 )
        {
          do
          {
            v16 = v13 * (_DWORD)&v15[119 - (_DWORD)code];
            v13 = *++v15;
            v14 += v16;
          }
          while ( v13 );
          IsEscape = (int)texta;
        }
        v17 = v23->icons.heads[v14 & v23->icons.tablesizemask];
        if ( v17 )
        {
          while ( 1 )
          {
            v18 = idStr::Cmp(v17->key.data, code);
            if ( !v18 )
              break;
            if ( v18 > 0 )
              goto LABEL_17;
            v17 = v17->next;
            if ( !v17 )
            {
              v6 = v6 + IsEscape - 1;
              goto LABEL_19;
            }
          }
          width += v17->value.width;
        }
      }
LABEL_17:
      v6 = v6 + IsEscape - 1;
    }
    else
    {
      v19 = ceil(v24->glyphs[(unsigned __int8)text[v6]].horiAdvance);
      width = (int)(v19 + (double)width);
    }
LABEL_19:
    textb = (double)width / v23->useFont->pointSize * textScale * 48.0;
    v25 = (int)textb;
    if ( v25 > limit )
      break;
    if ( text[v6] == 32 )
      wrapInfo->lastWhitespace = v6;
    if ( !text[++v6] )
      return 0;
  }
  wrapInfo->maxIndex = v6 - 1;
  return 1;
}

// FUNC: public: int __thiscall idDeviceContext::DrawTextA(char const *,float,int,int,class idVec4,class idRectangle,bool,int,bool,class idList<int> *,int,int,bool)
int __thiscall idDeviceContext::DrawTextA(
        idDeviceContext *this,
        const char *text,
        float textScale,
        int textAlign,
        int textStyle,
        idVec4 color,
        idRectangle rectDraw,
        bool wrap,
        int cursor,
        bool calcOnly,
        idList<int> *breaks,
        int limit,
        int adjust,
        bool chatWindow)
{
  int v15; // ebp
  bool v16; // zf
  float v17; // eax
  const char *v18; // ebx
  float z; // edx
  float w; // eax
  double v22; // st7
  idList<int> *v23; // esi
  char v24; // al
  int IsEscape; // eax
  int v26; // edi
  double v27; // st7
  int v28; // ecx
  char v29; // dl
  double v30; // st7
  int granularity; // eax
  bool v32; // cc
  int i; // eax
  float v34; // ebp
  int size; // eax
  int v36; // ecx
  int *list; // edi
  int j; // eax
  float v39; // [esp+0h] [ebp-45Ch]
  float v40; // [esp+Ch] [ebp-450h]
  bool lineBreak; // [esp+27h] [ebp-435h]
  int nextCharWidth; // [esp+28h] [ebp-434h]
  bool wordBreak; // [esp+2Fh] [ebp-42Dh]
  int newLine; // [esp+30h] [ebp-42Ch]
  float cursorSkip; // [esp+34h] [ebp-428h]
  float textWidth; // [esp+38h] [ebp-424h]
  int newLineWidth; // [esp+3Ch] [ebp-420h]
  float y; // [esp+40h] [ebp-41Ch]
  float lineSkip; // [esp+44h] [ebp-418h]
  const char *newLinePtr; // [esp+48h] [ebp-414h]
  int count; // [esp+4Ch] [ebp-410h]
  float x; // [esp+54h] [ebp-408h]
  float charSkip; // [esp+58h] [ebp-404h]
  char buff[1024]; // [esp+5Ch] [ebp-400h] BYREF

  charSkip = (float)(idDeviceContext::MaxCharWidth(this, textScale) + 1);
  v15 = 0;
  lineSkip = (float)idDeviceContext::MaxCharHeight(this, textScale);
  if ( cursor < 0 )
    cursorSkip = 0.0;
  else
    cursorSkip = charSkip;
  idDeviceContext::SetFontByScale(this, textScale);
  v16 = !calcOnly;
  v17 = color.y;
  v18 = text;
  this->drawTextColor.x = color.x;
  z = color.z;
  this->drawTextColor.y = v17;
  w = color.w;
  this->drawTextColor.z = z;
  newLinePtr = 0;
  this->drawTextColor.w = w;
  this->drawTextColorAdjust = 0.0;
  if ( !v16 || text && *text )
  {
    if ( textAlign == 3 )
    {
      textAlign = 0;
      v22 = rectDraw.h * 0.5 + lineSkip * 0.5 + rectDraw.y;
    }
    else
    {
      v22 = rectDraw.y + lineSkip;
    }
    y = v22;
    buff[0] = 0;
    newLine = 0;
    newLineWidth = 0;
    count = 0;
    textWidth = 0.0;
    lineBreak = 0;
    wordBreak = 0;
    if ( !text )
      return (int)(float)(rectDraw.w / charSkip);
    v23 = breaks;
    while ( 1 )
    {
      v24 = *v18;
      if ( *v18 == 10 || v24 == 13 || !v24 )
      {
        if ( (lineBreak = 1, v24 == 10) && v18[1] == 13 || v24 == 13 && v18[1] == 10 )
          ++v18;
      }
      IsEscape = idStr::IsEscape(v18, 0);
      v26 = IsEscape;
      if ( IsEscape )
      {
        idStr::Copynz(&buff[v15], v18, IsEscape + 1);
        if ( v26 != 5 )
        {
          if ( v18[v26] )
          {
            v15 += v26;
            v18 += v26;
            goto LABEL_97;
          }
        }
      }
      nextCharWidth = 0;
      if ( chatWindow )
      {
        if ( idStr::printableCharacter[*(unsigned __int8 *)v18] )
          v27 = (double)idDeviceContext::CharWidth(this, *v18, textScale, adjust);
        else
          v27 = cursorSkip;
        nextCharWidth = (int)v27;
      }
      else if ( lineBreak )
      {
        goto LABEL_42;
      }
      if ( (double)nextCharWidth + textWidth <= rectDraw.w )
      {
        if ( !lineBreak && (!wrap || *v18 != 32 && *v18 != 9) )
        {
LABEL_45:
          if ( v26 )
          {
            v15 += v26;
            v18 += v26;
          }
          else
          {
            buff[v15++] = *v18++;
            buff[v15] = 0;
          }
          textWidth = (float)idDeviceContext::TextWidth(this, buff, textScale, -1, adjust);
          goto LABEL_97;
        }
LABEL_42:
        v28 = v15;
        newLinePtr = v18 + 1;
        v29 = wordBreak;
        newLine = v15;
        newLineWidth = (int)textWidth;
        goto LABEL_43;
      }
      v28 = newLine;
      if ( v15 > 0 && !newLine )
      {
        v28 = v15;
        newLine = v15;
        newLinePtr = v18;
        newLineWidth = (int)textWidth;
      }
      v29 = 1;
      wordBreak = 1;
LABEL_43:
      if ( !lineBreak && !v29 )
        goto LABEL_45;
      x = rectDraw.x;
      if ( textAlign == 2 )
      {
        v30 = rectDraw.w + rectDraw.x - (double)newLineWidth;
LABEL_53:
        x = v30;
        goto LABEL_54;
      }
      if ( textAlign == 1 )
      {
        v30 = (rectDraw.w - (double)newLineWidth) * 0.5 + rectDraw.x;
        goto LABEL_53;
      }
LABEL_54:
      if ( wrap || v28 > 0 )
      {
        buff[v28] = 0;
        if ( v29 )
        {
          if ( cursor >= v28 && v28 == v15 )
            ++cursor;
        }
      }
      if ( !calcOnly )
      {
        v39 = (float)adjust;
        count += idDeviceContext::DrawTextA(
                   this,
                   (float *)&v23->num,
                   x,
                   y,
                   textScale,
                   color,
                   buff,
                   v39,
                   0,
                   textStyle,
                   cursor,
                   0);
        v28 = newLine;
      }
      if ( cursor >= v28 )
      {
        if ( cursor >= 0 )
          cursor += -1 - v28;
      }
      else
      {
        cursor = -1;
      }
      if ( !wrap )
        return v28;
      if ( limit && count > limit )
        return (int)(float)(rectDraw.w / charSkip);
      if ( !*v18 )
        return (int)(float)(rectDraw.w / charSkip);
      y = lineSkip * 0.25 + y + lineSkip;
      if ( !calcOnly && rectDraw.h + rectDraw.y < y )
        return (int)(float)(rectDraw.w / charSkip);
      v18 = newLinePtr;
      if ( v23 )
      {
        if ( !v23->list )
        {
          granularity = v23->granularity;
          if ( granularity > 0 )
          {
            if ( granularity != v23->size )
            {
              v32 = granularity < v23->num;
              v23->size = granularity;
              if ( v32 )
                v23->num = granularity;
              v23->list = (int *)Memory::Allocate(4 * granularity);
              for ( i = 0; i < v23->num; ++i )
                v23->list[i] = *(_DWORD *)(4 * i);
            }
          }
          else
          {
            v23->list = 0;
            v23->num = 0;
            v23->size = 0;
          }
        }
        v34 = *(float *)&v23->num;
        size = v23->size;
        if ( v23->num == size )
        {
          if ( !v23->granularity )
            v23->granularity = 16;
          v36 = size + v23->granularity - (size + v23->granularity) % v23->granularity;
          if ( v36 > 0 )
          {
            if ( v36 != v23->size )
            {
              list = v23->list;
              v23->size = v36;
              if ( v36 < SLODWORD(v34) )
                v23->num = v36;
              v23->list = (int *)Memory::Allocate(4 * v36);
              for ( j = 0; j < v23->num; ++j )
                v23->list[j] = list[j];
              if ( list )
                Memory::Free(list);
            }
          }
          else
          {
            if ( v23->list )
              Memory::Free(v23->list);
            v23->list = 0;
            v23->num = 0;
            v23->size = 0;
          }
        }
        v23->list[v23->num++] = newLinePtr - text;
        v18 = newLinePtr;
      }
      v15 = 0;
      newLine = 0;
      newLineWidth = 0;
      textWidth = 0.0;
      lineBreak = 0;
      wordBreak = 0;
LABEL_97:
      if ( !v18 )
        return (int)(float)(rectDraw.w / charSkip);
    }
  }
  if ( !cursor )
  {
    renderSystem->SetColor(renderSystem, &color);
    v40 = rectDraw.y + lineSkip;
    idDeviceContext::DrawEditCursor(this, rectDraw.x, v40, textScale);
  }
  return (int)(float)(rectDraw.w / charSkip);
}

// FUNC: public: void __thiscall idDeviceContext::Shutdown(void)
void __thiscall idDeviceContext::Shutdown(idDeviceContext *this)
{
  idStr *p_fontName; // esi
  int i; // ebx
  idHashTable<embeddedIcon_s>::hashnode_s *v4; // esi
  idPoolStr *v5; // ebp

  p_fontName = &this->fontName;
  idStr::FreeData(&this->fontName);
  p_fontName->len = 0;
  p_fontName->alloced = 20;
  p_fontName->data = p_fontName->baseBuffer;
  p_fontName->baseBuffer[0] = 0;
  if ( this->clipRects.list )
    Memory::Free(this->clipRects.list);
  this->clipRects.list = 0;
  this->clipRects.num = 0;
  this->clipRects.size = 0;
  if ( idDeviceContext::fonts.list )
    Memory::Free(idDeviceContext::fonts.list);
  idDeviceContext::fonts.list = 0;
  idDeviceContext::fonts.num = 0;
  idDeviceContext::fonts.size = 0;
  for ( i = 0; i < this->icons.tablesize; ++i )
  {
    v4 = this->icons.heads[i];
    while ( v4 )
    {
      v5 = (idPoolStr *)v4;
      v4 = v4->next;
      idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s(v5);
      Memory::Free(v5);
    }
    this->icons.heads[i] = 0;
  }
  this->icons.numentries = 0;
  this->useFont = 0;
  this->activeFont = 0;
  this->initialized = 0;
  this->mbcs = 0;
}

// FUNC: public: __thiscall idDeviceContext::idDeviceContext(void)
void __thiscall idDeviceContext::idDeviceContext(idDeviceContext *this)
{
  idHashTable<embeddedIcon_s>::hashnode_s **v2; // eax
  unsigned int v3; // edx
  int tablesize; // eax

  this->fontName.len = 0;
  this->fontName.alloced = 20;
  this->fontName.data = this->fontName.baseBuffer;
  this->fontName.baseBuffer[0] = 0;
  this->clipRects.granularity = 16;
  this->clipRects.list = 0;
  this->clipRects.num = 0;
  this->clipRects.size = 0;
  this->fontLang.len = 0;
  this->fontLang.alloced = 20;
  this->fontLang.data = this->fontLang.baseBuffer;
  this->fontLang.baseBuffer[0] = 0;
  this->icons.tablesize = 256;
  v2 = (idHashTable<embeddedIcon_s>::hashnode_s **)Memory::Allocate(0x400u);
  v3 = 4 * this->icons.tablesize;
  this->icons.heads = v2;
  memset(v2, 0, v3);
  tablesize = this->icons.tablesize;
  this->icons.numentries = 0;
  this->icons.tablesizemask = tablesize - 1;
  this->initialized = 0;
  this->useFont = 0;
  this->activeFont = 0;
  this->mbcs = 0;
}
