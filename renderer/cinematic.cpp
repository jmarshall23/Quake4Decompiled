
// FUNC: public: static void __cdecl idCinematic::InitCinematic(void)
void __cdecl idCinematic::InitCinematic()
{
  int v0; // edx
  int v1; // ecx
  double v2; // st7
  int v3; // [esp+4h] [ebp-8h]

  v0 = -255;
  v1 = 0;
  v3 = -255;
  do
  {
    v2 = (double)v3;
    v0 += 2;
    ROQ_UB_tab[v1] = (int)(57.203999 * v2 + 32.0);
    ROQ_VR_tab[v1] = (int)(45.363998 * v2 + 32.0);
    ROQ_UG_tab[v1] = (int)(-11.51248 * v2);
    ROQ_YY_tab[v1] = (v1 >> 2) | (v1 << 6);
    ROQ_VR_tab[++v1 + 255] = (int)(-23.35248 * v2 + 32.0);
    v3 = v0;
  }
  while ( v0 < 257 );
  file = (unsigned __int8 *)Mem_Alloc(0x10000, 0xCu);
  vq2 = (unsigned __int16 *)Mem_Alloc(0x8000, 0xCu);
  vq4 = (unsigned __int16 *)Mem_Alloc(0x20000, 0xCu);
  vq8 = (unsigned __int16 *)Mem_Alloc(0x80000, 0xCu);
}

// FUNC: public: static void __cdecl idCinematic::ShutdownCinematic(void)
void __cdecl idCinematic::ShutdownCinematic()
{
  Mem_Free(file);
  file = 0;
  Mem_Free(vq2);
  vq2 = 0;
  Mem_Free(vq4);
  vq4 = 0;
  Mem_Free(vq8);
  vq8 = 0;
}

// FUNC: public: __thiscall idCinematic::idCinematic(void)
void __thiscall idCinematic::idCinematic(idCinematic *this)
{
  this->__vftable = (idCinematic_vtbl *)&idCinematic::`vftable';
  this->mode = 2;
  this->PIMPL = 0;
}

// FUNC: public: virtual int __thiscall idCinematic::AnimationLength(void)
int __thiscall idCinematic::AnimationLength(idCinematic *this)
{
  if ( this->PIMPL )
    return this->PIMPL->AnimationLength(this->PIMPL);
  else
    return 0;
}

// FUNC: public: virtual void __thiscall idCinematic::ResetTime(int)
void __thiscall idCinematic::ResetTime(idCinematic *this, int milliseconds)
{
  if ( this->PIMPL )
    this->PIMPL->ResetTime(this->PIMPL, milliseconds);
}

// FUNC: public: virtual struct cinData_t __thiscall idCinematic::ImageForTime(int)
cinData_t *__thiscall idCinematic::ImageForTime(idCinematic *this, cinData_t *result, int milliseconds)
{
  cinData_t *v3; // eax

  if ( this->PIMPL )
  {
    this->PIMPL->ImageForTime(this->PIMPL, result, milliseconds);
    return result;
  }
  else
  {
    v3 = result;
    result->imageWidth = 0;
    result->imageHeight = 0;
    result->image = 0;
    result->status = 0;
  }
  return v3;
}

// FUNC: public: virtual void __thiscall idCinematic::Close(void)
void __thiscall idCinematic::Close(idCinematic *this)
{
  idCinematic *PIMPL; // ecx

  PIMPL = this->PIMPL;
  if ( PIMPL )
    PIMPL->Close(PIMPL);
  this->mode = 2;
}

// FUNC: public: virtual void __thiscall idCinematic::Draw(void)
void __thiscall idCinematic::Draw(idCinematic *this)
{
  if ( this->PIMPL )
    this->PIMPL->Draw(this->PIMPL);
}

// FUNC: public: virtual void __thiscall idCinematic::SetScreenRect(int,int,int,int)
void __thiscall idCinematic::SetScreenRect(idCinematic *this, int left, int right, int bottom, int top)
{
  if ( this->PIMPL )
    this->PIMPL->SetScreenRect(this->PIMPL, left, right, bottom, top);
}

// FUNC: public: virtual void __thiscall idCinematic::GetScreenRect(int &,int &,int &,int &)
void __thiscall idCinematic::GetScreenRect(idCinematic *this, int *left, int *right, int *bottom, int *top)
{
  if ( this->PIMPL )
    this->PIMPL->GetScreenRect(this->PIMPL, left, right, bottom, top);
}

// FUNC: public: virtual bool __thiscall idCinematic::IsPlaying(void)
bool __thiscall idCinematic::IsPlaying(idCinematic *this)
{
  return this->PIMPL && this->PIMPL->IsPlaying(this->PIMPL);
}

// FUNC: public: virtual struct cinData_t __thiscall WMVCinematic::ImageForTime(int)
cinData_t *__thiscall WMVCinematic::ImageForTime(WMVCinematic *this, cinData_t *result, int milliseconds)
{
  cinData_t *v3; // eax

  v3 = result;
  result->imageWidth = 0;
  result->imageHeight = 0;
  result->image = 0;
  result->status = 0;
  return v3;
}

// FUNC: public: virtual void __thiscall ROQCinematic::ResetTime(int)
void __thiscall ROQCinematic::ResetTime(ROQCinematic *this, int time)
{
  this->startTime = -1;
  this->status = FMV_PLAY;
}

// FUNC: private: void __thiscall ROQCinematic::move8_32(unsigned char *,unsigned char *,int)
void __thiscall ROQCinematic::move8_32(ROQCinematic *this, unsigned __int8 *src, unsigned __int8 *dst, int spl)
{
  int v4; // edx
  int v5; // esi
  int v6; // esi
  int v7; // esi
  int v8; // esi
  int v9; // esi

  v4 = spl >> 2;
  *(_DWORD *)dst = *(_DWORD *)src;
  *((_DWORD *)dst + 1) = *((_DWORD *)src + 1);
  *((_DWORD *)dst + 2) = *((_DWORD *)src + 2);
  *((_DWORD *)dst + 3) = *((_DWORD *)src + 3);
  *((_DWORD *)dst + 4) = *((_DWORD *)src + 4);
  *((_DWORD *)dst + 5) = *((_DWORD *)src + 5);
  *((_DWORD *)dst + 6) = *((_DWORD *)src + 6);
  *((_DWORD *)dst + 7) = *((_DWORD *)src + 7);
  *(_DWORD *)&dst[4 * v4] = *(_DWORD *)&src[4 * v4];
  *(_DWORD *)&dst[4 * v4 + 4] = *(_DWORD *)&src[4 * v4 + 4];
  *(_DWORD *)&dst[4 * v4 + 8] = *(_DWORD *)&src[4 * v4 + 8];
  *(_DWORD *)&dst[4 * v4 + 12] = *(_DWORD *)&src[4 * v4 + 12];
  *(_DWORD *)&dst[4 * v4 + 16] = *(_DWORD *)&src[4 * v4 + 16];
  *(_DWORD *)&dst[4 * v4 + 20] = *(_DWORD *)&src[4 * v4 + 20];
  *(_DWORD *)&dst[4 * v4 + 24] = *(_DWORD *)&src[4 * v4 + 24];
  *(_DWORD *)&dst[4 * v4 + 28] = *(_DWORD *)&src[4 * v4 + 28];
  *(_DWORD *)&dst[8 * v4] = *(_DWORD *)&src[8 * v4];
  *(_DWORD *)&dst[8 * v4 + 4] = *(_DWORD *)&src[8 * v4 + 4];
  *(_DWORD *)&dst[8 * v4 + 8] = *(_DWORD *)&src[8 * v4 + 8];
  *(_DWORD *)&dst[8 * v4 + 12] = *(_DWORD *)&src[8 * v4 + 12];
  *(_DWORD *)&dst[8 * v4 + 16] = *(_DWORD *)&src[8 * v4 + 16];
  *(_DWORD *)&dst[8 * v4 + 20] = *(_DWORD *)&src[8 * v4 + 20];
  *(_DWORD *)&dst[8 * v4 + 24] = *(_DWORD *)&src[8 * v4 + 24];
  *(_DWORD *)&dst[8 * v4 + 28] = *(_DWORD *)&src[8 * v4 + 28];
  v5 = 12 * (spl >> 2);
  *(_DWORD *)&dst[v5] = *(_DWORD *)&src[v5];
  *(_DWORD *)&dst[v5 + 4] = *(_DWORD *)&src[v5 + 4];
  *(_DWORD *)&dst[v5 + 8] = *(_DWORD *)&src[v5 + 8];
  *(_DWORD *)&dst[v5 + 12] = *(_DWORD *)&src[v5 + 12];
  *(_DWORD *)&dst[v5 + 16] = *(_DWORD *)&src[v5 + 16];
  *(_DWORD *)&dst[v5 + 20] = *(_DWORD *)&src[v5 + 20];
  *(_DWORD *)&dst[12 * (spl >> 2) + 24] = *(_DWORD *)&src[12 * (spl >> 2) + 24];
  *(_DWORD *)&dst[v5 + 28] = *(_DWORD *)&src[v5 + 28];
  v6 = 16 * (spl >> 2);
  *(_DWORD *)&dst[v6] = *(_DWORD *)&src[v6];
  *(_DWORD *)&dst[v6 + 4] = *(_DWORD *)&src[v6 + 4];
  *(_DWORD *)&dst[v6 + 8] = *(_DWORD *)&src[v6 + 8];
  *(_DWORD *)&dst[v6 + 12] = *(_DWORD *)&src[v6 + 12];
  *(_DWORD *)&dst[v6 + 16] = *(_DWORD *)&src[v6 + 16];
  *(_DWORD *)&dst[v6 + 20] = *(_DWORD *)&src[v6 + 20];
  *(_DWORD *)&dst[v6 + 24] = *(_DWORD *)&src[v6 + 24];
  *(_DWORD *)&dst[v6 + 28] = *(_DWORD *)&src[v6 + 28];
  v7 = 20 * (spl >> 2);
  *(_DWORD *)&dst[v7] = *(_DWORD *)&src[v7];
  *(_DWORD *)&dst[v7 + 4] = *(_DWORD *)&src[v7 + 4];
  *(_DWORD *)&dst[v7 + 8] = *(_DWORD *)&src[v7 + 8];
  *(_DWORD *)&dst[v7 + 12] = *(_DWORD *)&src[v7 + 12];
  *(_DWORD *)&dst[v7 + 16] = *(_DWORD *)&src[v7 + 16];
  *(_DWORD *)&dst[v7 + 20] = *(_DWORD *)&src[v7 + 20];
  *(_DWORD *)&dst[v7 + 24] = *(_DWORD *)&src[v7 + 24];
  *(_DWORD *)&dst[v7 + 28] = *(_DWORD *)&src[v7 + 28];
  v8 = 24 * (spl >> 2);
  *(_DWORD *)&dst[v8] = *(_DWORD *)&src[v8];
  *(_DWORD *)&dst[v8 + 4] = *(_DWORD *)&src[v8 + 4];
  *(_DWORD *)&dst[v8 + 8] = *(_DWORD *)&src[v8 + 8];
  *(_DWORD *)&dst[v8 + 12] = *(_DWORD *)&src[v8 + 12];
  *(_DWORD *)&dst[v8 + 16] = *(_DWORD *)&src[v8 + 16];
  *(_DWORD *)&dst[v8 + 20] = *(_DWORD *)&src[v8 + 20];
  *(_DWORD *)&dst[v8 + 24] = *(_DWORD *)&src[v8 + 24];
  *(_DWORD *)&dst[v8 + 28] = *(_DWORD *)&src[v8 + 28];
  v9 = 28 * (spl >> 2);
  *(_DWORD *)&dst[v9] = *(_DWORD *)&src[v9];
  *(_DWORD *)&dst[v9 + 4] = *(_DWORD *)&src[v9 + 4];
  *(_DWORD *)&dst[v9 + 8] = *(_DWORD *)&src[v9 + 8];
  *(_DWORD *)&dst[v9 + 12] = *(_DWORD *)&src[v9 + 12];
  *(_DWORD *)&dst[v9 + 16] = *(_DWORD *)&src[v9 + 16];
  *(_DWORD *)&dst[v9 + 20] = *(_DWORD *)&src[v9 + 20];
  *(_DWORD *)&dst[v9 + 24] = *(_DWORD *)&src[v9 + 24];
  *(_DWORD *)&dst[v9 + 28] = *(_DWORD *)&src[v9 + 28];
}

// FUNC: private: void __thiscall ROQCinematic::move4_32(unsigned char *,unsigned char *,int)
void __thiscall ROQCinematic::move4_32(ROQCinematic *this, unsigned __int8 *src, unsigned __int8 *dst, int spl)
{
  int v4; // eax
  int v5; // eax

  *(_DWORD *)dst = *(_DWORD *)src;
  *((_DWORD *)dst + 1) = *((_DWORD *)src + 1);
  *((_DWORD *)dst + 2) = *((_DWORD *)src + 2);
  *((_DWORD *)dst + 3) = *((_DWORD *)src + 3);
  v4 = spl >> 2;
  *(_DWORD *)&dst[4 * v4] = *(_DWORD *)&src[4 * v4];
  *(_DWORD *)&dst[4 * v4 + 4] = *(_DWORD *)&src[4 * v4 + 4];
  *(_DWORD *)&dst[4 * v4 + 8] = *(_DWORD *)&src[4 * v4 + 8];
  *(_DWORD *)&dst[4 * v4 + 12] = *(_DWORD *)&src[4 * v4 + 12];
  *(_DWORD *)&dst[8 * v4] = *(_DWORD *)&src[8 * v4];
  *(_DWORD *)&dst[8 * v4 + 4] = *(_DWORD *)&src[8 * v4 + 4];
  *(_DWORD *)&dst[8 * v4 + 8] = *(_DWORD *)&src[8 * v4 + 8];
  *(_DWORD *)&dst[8 * v4 + 12] = *(_DWORD *)&src[8 * v4 + 12];
  v5 = 12 * (spl >> 2);
  *(_DWORD *)&dst[v5] = *(_DWORD *)&src[v5];
  *(_DWORD *)&dst[v5 + 4] = *(_DWORD *)&src[v5 + 4];
  *(_DWORD *)&dst[v5 + 8] = *(_DWORD *)&src[v5 + 8];
  *(_DWORD *)&dst[v5 + 12] = *(_DWORD *)&src[v5 + 12];
}

// FUNC: private: void __thiscall ROQCinematic::blit8_32(unsigned char *,unsigned char *,int)
void __thiscall ROQCinematic::blit8_32(ROQCinematic *this, unsigned __int8 *src, unsigned __int8 *dst, int spl)
{
  int v4; // ecx
  unsigned __int8 *v5; // esi
  unsigned __int8 *v6; // esi
  int v7; // esi
  unsigned __int8 *v8; // esi
  unsigned __int8 *v9; // esi
  unsigned __int8 *v10; // ecx

  *(_DWORD *)dst = *(_DWORD *)src;
  *((_DWORD *)dst + 1) = *((_DWORD *)src + 1);
  *((_DWORD *)dst + 2) = *((_DWORD *)src + 2);
  *((_DWORD *)dst + 3) = *((_DWORD *)src + 3);
  *((_DWORD *)dst + 4) = *((_DWORD *)src + 4);
  *((_DWORD *)dst + 5) = *((_DWORD *)src + 5);
  *((_DWORD *)dst + 6) = *((_DWORD *)src + 6);
  *((_DWORD *)dst + 7) = *((_DWORD *)src + 7);
  v4 = spl >> 2;
  *(_DWORD *)&dst[4 * v4] = *((_DWORD *)src + 8);
  *(_DWORD *)&dst[4 * v4 + 4] = *((_DWORD *)src + 9);
  *(_DWORD *)&dst[4 * v4 + 8] = *((_DWORD *)src + 10);
  *(_DWORD *)&dst[4 * v4 + 12] = *((_DWORD *)src + 11);
  *(_DWORD *)&dst[4 * v4 + 16] = *((_DWORD *)src + 12);
  *(_DWORD *)&dst[4 * v4 + 20] = *((_DWORD *)src + 13);
  *(_DWORD *)&dst[4 * v4 + 24] = *((_DWORD *)src + 14);
  *(_DWORD *)&dst[4 * v4 + 28] = *((_DWORD *)src + 15);
  *(_DWORD *)&dst[8 * v4] = *((_DWORD *)src + 16);
  *(_DWORD *)&dst[8 * v4 + 4] = *((_DWORD *)src + 17);
  *(_DWORD *)&dst[8 * v4 + 8] = *((_DWORD *)src + 18);
  *(_DWORD *)&dst[8 * v4 + 12] = *((_DWORD *)src + 19);
  *(_DWORD *)&dst[8 * v4 + 16] = *((_DWORD *)src + 20);
  *(_DWORD *)&dst[8 * v4 + 20] = *((_DWORD *)src + 21);
  *(_DWORD *)&dst[8 * v4 + 24] = *((_DWORD *)src + 22);
  *(_DWORD *)&dst[8 * v4 + 28] = *((_DWORD *)src + 23);
  *(_DWORD *)&dst[12 * v4] = *((_DWORD *)src + 24);
  v5 = &dst[12 * (spl >> 2)];
  *((_DWORD *)v5 + 1) = *((_DWORD *)src + 25);
  *((_DWORD *)v5 + 2) = *((_DWORD *)src + 26);
  *((_DWORD *)v5 + 3) = *((_DWORD *)src + 27);
  *((_DWORD *)v5 + 4) = *((_DWORD *)src + 28);
  *((_DWORD *)v5 + 5) = *((_DWORD *)src + 29);
  *(_DWORD *)&dst[12 * v4 + 24] = *((_DWORD *)src + 30);
  *((_DWORD *)v5 + 7) = *((_DWORD *)src + 31);
  v6 = &dst[16 * (spl >> 2)];
  *(_DWORD *)v6 = *((_DWORD *)src + 32);
  *((_DWORD *)v6 + 1) = *((_DWORD *)src + 33);
  *((_DWORD *)v6 + 2) = *((_DWORD *)src + 34);
  *((_DWORD *)v6 + 3) = *((_DWORD *)src + 35);
  *((_DWORD *)v6 + 4) = *((_DWORD *)src + 36);
  *((_DWORD *)v6 + 5) = *((_DWORD *)src + 37);
  *((_DWORD *)v6 + 6) = *((_DWORD *)src + 38);
  *((_DWORD *)v6 + 7) = *((_DWORD *)src + 39);
  v7 = 5 * (spl >> 2);
  *(_DWORD *)&dst[4 * v7] = *((_DWORD *)src + 40);
  *(_DWORD *)&dst[4 * v7 + 4] = *((_DWORD *)src + 41);
  *(_DWORD *)&dst[4 * v7 + 8] = *((_DWORD *)src + 42);
  v8 = &dst[20 * (spl >> 2)];
  *((_DWORD *)v8 + 3) = *((_DWORD *)src + 43);
  *((_DWORD *)v8 + 4) = *((_DWORD *)src + 44);
  *((_DWORD *)v8 + 5) = *((_DWORD *)src + 45);
  *((_DWORD *)v8 + 6) = *((_DWORD *)src + 46);
  *((_DWORD *)v8 + 7) = *((_DWORD *)src + 47);
  v9 = &dst[24 * (spl >> 2)];
  *(_DWORD *)v9 = *((_DWORD *)src + 48);
  *((_DWORD *)v9 + 1) = *((_DWORD *)src + 49);
  *((_DWORD *)v9 + 2) = *((_DWORD *)src + 50);
  *((_DWORD *)v9 + 3) = *((_DWORD *)src + 51);
  *((_DWORD *)v9 + 4) = *((_DWORD *)src + 52);
  *((_DWORD *)v9 + 5) = *((_DWORD *)src + 53);
  *((_DWORD *)v9 + 6) = *((_DWORD *)src + 54);
  *((_DWORD *)v9 + 7) = *((_DWORD *)src + 55);
  v10 = &dst[28 * (spl >> 2)];
  *(_DWORD *)v10 = *((_DWORD *)src + 56);
  *((_DWORD *)v10 + 1) = *((_DWORD *)src + 57);
  *((_DWORD *)v10 + 2) = *((_DWORD *)src + 58);
  *((_DWORD *)v10 + 3) = *((_DWORD *)src + 59);
  *((_DWORD *)v10 + 4) = *((_DWORD *)src + 60);
  *((_DWORD *)v10 + 5) = *((_DWORD *)src + 61);
  *((_DWORD *)v10 + 6) = *((_DWORD *)src + 62);
  *((_DWORD *)v10 + 7) = *((_DWORD *)src + 63);
}

// FUNC: private: void __thiscall ROQCinematic::blit4_32(unsigned char *,unsigned char *,int)
void __thiscall ROQCinematic::blit4_32(ROQCinematic *this, unsigned __int8 *src, unsigned __int8 *dst, int spl)
{
  int v4; // ecx
  unsigned __int8 *v5; // ecx

  *(_DWORD *)dst = *(_DWORD *)src;
  *((_DWORD *)dst + 1) = *((_DWORD *)src + 1);
  *((_DWORD *)dst + 2) = *((_DWORD *)src + 2);
  *((_DWORD *)dst + 3) = *((_DWORD *)src + 3);
  v4 = spl >> 2;
  *(_DWORD *)&dst[4 * v4] = *((_DWORD *)src + 4);
  *(_DWORD *)&dst[4 * v4 + 4] = *((_DWORD *)src + 5);
  *(_DWORD *)&dst[4 * v4 + 8] = *((_DWORD *)src + 6);
  *(_DWORD *)&dst[4 * v4 + 12] = *((_DWORD *)src + 7);
  *(_DWORD *)&dst[8 * v4] = *((_DWORD *)src + 8);
  *(_DWORD *)&dst[8 * v4 + 4] = *((_DWORD *)src + 9);
  *(_DWORD *)&dst[8 * v4 + 8] = *((_DWORD *)src + 10);
  *(_DWORD *)&dst[8 * v4 + 12] = *((_DWORD *)src + 11);
  v5 = &dst[12 * (spl >> 2)];
  *(_DWORD *)v5 = *((_DWORD *)src + 12);
  *((_DWORD *)v5 + 1) = *((_DWORD *)src + 13);
  *((_DWORD *)v5 + 2) = *((_DWORD *)src + 14);
  *((_DWORD *)v5 + 3) = *((_DWORD *)src + 15);
}

// FUNC: private: void __thiscall ROQCinematic::blitVQQuad32fs(unsigned char * *,unsigned char *)
void __userpurge ROQCinematic::blitVQQuad32fs(
        ROQCinematic *this@<ecx>,
        int a2@<eax>,
        unsigned __int8 **status,
        unsigned __int8 *data)
{
  unsigned __int8 **v4; // ebp
  ROQCinematic *v6; // edi
  int v7; // ebx
  unsigned __int8 *v8; // ecx
  unsigned __int16 *v9; // eax
  int v10; // edx
  int samplesPerLine; // edx
  unsigned __int8 *v12; // ecx
  unsigned __int16 *v13; // eax
  unsigned __int8 *v14; // esi
  int v15; // eax
  int v16; // ecx
  unsigned __int16 *v17; // eax
  unsigned __int8 *v18; // edx
  int v19; // eax
  int v20; // ecx
  unsigned __int16 *v21; // eax
  unsigned __int8 *v22; // edx
  int newd; // [esp+10h] [ebp-8h]
  int celdata; // [esp+14h] [ebp-4h]
  int dataa; // [esp+20h] [ebp+8h]

  v4 = status;
  v6 = this;
  newd = 0;
  celdata = 0;
  v7 = 0;
  do
  {
    if ( (_WORD)newd )
    {
      newd += 0xFFFF;
    }
    else
    {
      LOWORD(a2) = data[1];
      LOWORD(this) = *data;
      newd = 7;
      celdata = (int)this + 256 * a2;
      data += 2;
    }
    a2 = celdata & 0xC000;
    this = (ROQCinematic *)(4 * celdata);
    celdata *= 4;
    if ( a2 > 0x8000 )
    {
      if ( a2 != 49152 )
        continue;
      ++v7;
      dataa = 4;
      while ( 1 )
      {
        if ( (_WORD)newd )
        {
          newd += 0xFFFF;
        }
        else
        {
          LOWORD(a2) = data[1];
          LOWORD(this) = *data;
          newd = 7;
          celdata = (int)this + 256 * a2;
          data += 2;
        }
        a2 = celdata & 0xC000;
        this = (ROQCinematic *)(4 * celdata);
        celdata *= 4;
        if ( a2 == 0x4000 )
        {
          ROQCinematic::move4_32(v6, &v4[v7][v6->mcomp[*data]], v4[v7], v6->samplesPerLine);
          goto LABEL_23;
        }
        if ( a2 == 0x8000 )
          break;
        if ( a2 == 49152 )
        {
          v8 = v4[v7];
          v9 = &vq2[8 * *data];
          v10 = v6->samplesPerLine >> 2;
          *(_DWORD *)v8 = *(_DWORD *)v9;
          *((_DWORD *)v8 + 1) = *((_DWORD *)v9 + 1);
          *(_DWORD *)&v8[4 * v10] = *((_DWORD *)v9 + 2);
          *(_DWORD *)&v8[4 * v10 + 4] = *((_DWORD *)v9 + 3);
          samplesPerLine = v6->samplesPerLine;
          v12 = status[v7];
          v13 = &vq2[8 * data[1]];
          v14 = data + 1;
          *((_DWORD *)v12 + 2) = *(_DWORD *)v13;
          *((_DWORD *)v12 + 3) = *((_DWORD *)v13 + 1);
          v12 += 8;
          samplesPerLine >>= 2;
          *(_DWORD *)&v12[4 * samplesPerLine] = *((_DWORD *)v13 + 2);
          *(_DWORD *)&v12[4 * samplesPerLine + 4] = *((_DWORD *)v13 + 3);
          v15 = v14[1];
          v16 = v6->samplesPerLine;
          ++v14;
          v17 = &vq2[8 * v15];
          v18 = &status[v7][2 * v16];
          *(_DWORD *)v18 = *(_DWORD *)v17;
          *((_DWORD *)v18 + 1) = *((_DWORD *)v17 + 1);
          v16 >>= 2;
          *(_DWORD *)&v18[4 * v16] = *((_DWORD *)v17 + 2);
          *(_DWORD *)&v18[4 * v16 + 4] = *((_DWORD *)v17 + 3);
          v19 = v14[1];
          v20 = v6->samplesPerLine;
          data = v14 + 1;
          v21 = &vq2[8 * v19];
          v22 = &status[v7][2 * v20 + 8];
          *(_DWORD *)v22 = *(_DWORD *)v21;
          *((_DWORD *)v22 + 1) = *((_DWORD *)v21 + 1);
          this = (ROQCinematic *)(v20 >> 2);
          *(_DWORD *)&v22[4 * (_DWORD)this] = *((_DWORD *)v21 + 2);
          a2 = *((_DWORD *)v21 + 3);
          v4 = status;
          *(_DWORD *)&v22[4 * (_DWORD)this + 4] = a2;
LABEL_23:
          ++data;
        }
        ++v7;
        if ( !--dataa )
          goto LABEL_25;
      }
      ROQCinematic::blit4_32(v6, (unsigned __int8 *)&vq4[32 * *data], v4[v7], v6->samplesPerLine);
      goto LABEL_23;
    }
    switch ( a2 )
    {
      case 0x8000:
        ROQCinematic::blit8_32(v6, (unsigned __int8 *)&vq8[128 * *data++], v4[v7], v6->samplesPerLine);
LABEL_11:
        v7 += 5;
        break;
      case 0:
        goto LABEL_11;
      case 0x4000:
        ROQCinematic::move8_32(v6, &v4[v7][v6->mcomp[*data++]], v4[v7], v6->samplesPerLine);
        v7 += 5;
        break;
    }
LABEL_25:
    ;
  }
  while ( v4[v7] );
}

// FUNC: private: unsigned int __thiscall ROQCinematic::yuv_to_rgb24(long,long,long)
int __thiscall ROQCinematic::yuv_to_rgb24(ROQCinematic *this, int y, int u, int v)
{
  int v4; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // eax

  v4 = ROQ_YY_tab[y];
  v5 = (v4 + ROQ_VR_tab[v]) >> 6;
  v6 = (v4 + ROQ_VG_tab[v] + ROQ_UG_tab[u]) >> 6;
  v7 = (v4 + ROQ_UB_tab[u]) >> 6;
  if ( v5 < 0 )
    v5 = 0;
  if ( v6 < 0 )
    v6 = 0;
  if ( v7 < 0 )
    v7 = 0;
  if ( v5 > 255 )
    v5 = 255;
  if ( v6 > 255 )
    v6 = 255;
  if ( v7 > 255 )
    v7 = 255;
  return LittleLong(v5 + ((v6 + (v7 << 8)) << 8));
}

// FUNC: private: void __thiscall ROQCinematic::decodeCodeBook(unsigned char *,unsigned short)
void __thiscall ROQCinematic::decodeCodeBook(ROQCinematic *this, unsigned __int8 *input, unsigned __int16 roq_flags)
{
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  unsigned __int16 *v7; // ebp
  unsigned __int8 *v8; // esi
  unsigned __int16 *v9; // edi
  int v10; // eax
  int v11; // ecx
  unsigned __int8 *v12; // esi
  unsigned __int8 *v13; // edx
  int v14; // ebp
  int v15; // ecx
  int *v16; // edi
  unsigned __int16 *v17; // edi
  unsigned __int16 *v18; // eax
  unsigned __int16 *v19; // ecx
  unsigned __int16 *v20; // edx
  int v21; // ebx
  _DWORD *v22; // eax
  unsigned __int16 *v23; // edi
  unsigned __int8 *v24; // edi
  unsigned __int16 *v25; // esi
  int v26; // eax
  int v27; // edx
  unsigned __int8 *v28; // edi
  int v29; // ecx
  int v30; // ebp
  int v31; // edx
  int *v32; // esi
  unsigned __int16 *v33; // esi
  unsigned __int16 *v34; // eax
  unsigned __int16 *v35; // ecx
  unsigned __int16 *v36; // edx
  int v37; // ebx
  _DWORD *v38; // eax
  _DWORD *v39; // esi
  int v40; // ebp
  _DWORD *v41; // ecx
  _DWORD *v42; // edx
  unsigned __int16 *v43; // edx
  unsigned __int8 *v44; // esi
  unsigned __int16 *v45; // edi
  int v46; // eax
  unsigned __int8 *v47; // ecx
  unsigned __int8 *v48; // esi
  int v49; // ebp
  int *v50; // edi
  unsigned __int16 *v51; // edi
  unsigned __int16 *v52; // eax
  unsigned __int16 *v53; // ecx
  unsigned __int16 *v54; // edx
  int v55; // ebx
  _DWORD *v56; // eax
  int y1; // [esp+10h] [ebp-14h]
  int y1a; // [esp+10h] [ebp-14h]
  int y3; // [esp+14h] [ebp-10h]
  int y3a; // [esp+14h] [ebp-10h]
  int four; // [esp+18h] [ebp-Ch]
  int y0; // [esp+1Ch] [ebp-8h]
  int y0a; // [esp+1Ch] [ebp-8h]
  int v64; // [esp+20h] [ebp-4h]
  int v65; // [esp+20h] [ebp-4h]
  unsigned __int8 *inputa; // [esp+28h] [ebp+4h]
  int inputb; // [esp+28h] [ebp+4h]
  unsigned __int8 *inputc; // [esp+28h] [ebp+4h]
  int y2c; // [esp+2Ch] [ebp+8h]
  int y2; // [esp+2Ch] [ebp+8h]
  int y2d; // [esp+2Ch] [ebp+8h]
  int y2a; // [esp+2Ch] [ebp+8h]
  int y2e; // [esp+2Ch] [ebp+8h]
  int y2b; // [esp+2Ch] [ebp+8h]

  if ( roq_flags )
  {
    v4 = HIBYTE(roq_flags);
    if ( !v4 )
      v4 = 256;
    v5 = (unsigned __int8)roq_flags;
  }
  else
  {
    v4 = 256;
    v5 = 256;
  }
  v6 = 2 * v5;
  four = v6;
  if ( this->half )
  {
    v43 = vq2;
    v44 = input;
    v45 = vq2;
    if ( v4 > 0 )
    {
      v65 = v4;
      do
      {
        v46 = *v44;
        v47 = (unsigned __int8 *)v44[2];
        v48 = v44 + 2;
        v49 = v48[2];
        v48 += 2;
        inputc = v47;
        y2e = v48[1];
        v44 = v48 + 2;
        *(_DWORD *)v45 = ROQCinematic::yuv_to_rgb24(this, v46, v49, y2e);
        v50 = (int *)(v45 + 2);
        *v50 = ROQCinematic::yuv_to_rgb24(this, (int)inputc, v49, y2e);
        v45 = (unsigned __int16 *)(v50 + 1);
        --v65;
      }
      while ( v65 );
      v43 = vq2;
      v6 = four;
    }
    v51 = vq4;
    v52 = vq8;
    if ( v6 > 0 )
    {
      y2b = v6;
      while ( 1 )
      {
        v53 = &v43[4 * *v44];
        v54 = &v43[4 * v44[1]];
        v44 += 2;
        v55 = 2;
        do
        {
          *(_DWORD *)v51 = *(_DWORD *)v53;
          *(_DWORD *)v52 = *(_DWORD *)v53;
          *((_DWORD *)v52 + 1) = *(_DWORD *)v53;
          v56 = v52 + 2;
          *((_DWORD *)v51 + 1) = *(_DWORD *)v54;
          v56[1] = *(_DWORD *)v54;
          ++v56;
          v56[1] = *(_DWORD *)v54;
          ++v56;
          v56[1] = *(_DWORD *)v53;
          v56 += 2;
          *v56++ = *(_DWORD *)v53;
          *v56++ = *(_DWORD *)v54;
          *v56 = *(_DWORD *)v54;
          v51 += 4;
          v52 = (unsigned __int16 *)(v56 + 1);
          v53 += 2;
          v54 += 2;
          --v55;
        }
        while ( v55 );
        if ( !--y2b )
          break;
        v43 = vq2;
      }
    }
  }
  else
  {
    v7 = vq2;
    if ( this->smootheddouble )
    {
      v24 = input;
      v25 = vq2;
      if ( v4 > 0 )
      {
        v64 = v4;
        do
        {
          v26 = *v24;
          v27 = v24[1];
          v28 = v24 + 1;
          v29 = v28[1];
          v28 += 2;
          v30 = v28[1];
          y1a = v27;
          v31 = *v28++;
          inputb = v29;
          y2d = v28[1];
          y0a = v26;
          y3a = v31;
          v24 = v28 + 2;
          *(_DWORD *)v25 = ROQCinematic::yuv_to_rgb24(this, v26, v30, y2d);
          v32 = (int *)(v25 + 2);
          *v32++ = ROQCinematic::yuv_to_rgb24(this, y1a, v30, y2d);
          *v32++ = ROQCinematic::yuv_to_rgb24(this, (y0a + inputb + 2 * y0a) / 4, v30, y2d);
          *v32++ = ROQCinematic::yuv_to_rgb24(this, (y1a + y3a + 2 * y1a) / 4, v30, y2d);
          *v32++ = ROQCinematic::yuv_to_rgb24(this, (inputb + y0a + 2 * inputb) / 4, v30, y2d);
          *v32++ = ROQCinematic::yuv_to_rgb24(this, (y3a + y1a + 2 * y3a) / 4, v30, y2d);
          *v32++ = ROQCinematic::yuv_to_rgb24(this, inputb, v30, y2d);
          *v32 = ROQCinematic::yuv_to_rgb24(this, y3a, v30, y2d);
          v25 = (unsigned __int16 *)(v32 + 1);
          --v64;
        }
        while ( v64 );
        v7 = vq2;
        v6 = four;
      }
      v33 = vq4;
      v34 = vq8;
      if ( v6 > 0 )
      {
        y2a = v6;
        while ( 1 )
        {
          v35 = &v7[16 * *v24];
          v36 = &v7[16 * v24[1]];
          v24 += 2;
          v37 = 2;
          do
          {
            *(_DWORD *)v33 = *(_DWORD *)v35;
            *(_DWORD *)v34 = *(_DWORD *)v35;
            *((_DWORD *)v34 + 1) = *(_DWORD *)v35;
            *((_DWORD *)v33 + 1) = *((_DWORD *)v35 + 1);
            v38 = v34 + 2;
            v38[1] = *((_DWORD *)v35 + 1);
            ++v38;
            v38[1] = *((_DWORD *)v35 + 1);
            ++v38;
            v39 = v33 + 2;
            v39[1] = *(_DWORD *)v36;
            v38[1] = *(_DWORD *)v36;
            ++v38;
            v38[1] = *(_DWORD *)v36;
            ++v38;
            ++v39;
            v39[1] = *((_DWORD *)v36 + 1);
            v38[1] = *((_DWORD *)v36 + 1);
            ++v38;
            v38[1] = *((_DWORD *)v36 + 1);
            ++v38;
            v38[1] = *(_DWORD *)v35;
            ++v39;
            ++v38;
            v38[1] = *(_DWORD *)v35;
            ++v38;
            v38[1] = *((_DWORD *)v35 + 1);
            ++v38;
            v38[1] = *((_DWORD *)v35 + 1);
            ++v38;
            v38[1] = *(_DWORD *)v36;
            ++v38;
            v38[1] = *(_DWORD *)v36;
            ++v38;
            v38[1] = *((_DWORD *)v36 + 1);
            ++v38;
            v38[1] = *((_DWORD *)v36 + 1);
            v39[1] = *((_DWORD *)v35 + 2);
            v40 = *((_DWORD *)v35 + 2);
            ++v38;
            v41 = v35 + 4;
            v38[1] = v40;
            ++v39;
            ++v38;
            v38[1] = *v41;
            v39[1] = v41[1];
            v38 += 2;
            *v38++ = v41[1];
            v42 = v36 + 4;
            *v38 = v41[1];
            v39 += 2;
            ++v38;
            *v39 = *v42;
            *v38 = *v42;
            v38[1] = *v42;
            v39[1] = v42[1];
            ++v38;
            v38[1] = v42[1];
            ++v38;
            v38[1] = v42[1];
            ++v38;
            v38[1] = *v41;
            ++v38;
            v38[1] = *v41;
            ++v38;
            v38[1] = v41[1];
            ++v38;
            v38[1] = v41[1];
            ++v38;
            v38[1] = *v42;
            v38 += 2;
            *v38++ = *v42;
            *v38++ = v42[1];
            *v38 = v42[1];
            v33 = (unsigned __int16 *)(v39 + 2);
            v34 = (unsigned __int16 *)(v38 + 1);
            v35 = (unsigned __int16 *)(v41 + 2);
            v36 = (unsigned __int16 *)(v42 + 2);
            --v37;
          }
          while ( v37 );
          if ( !--y2a )
            break;
          v7 = vq2;
        }
      }
    }
    else
    {
      v8 = input;
      v9 = vq2;
      if ( v4 > 0 )
      {
        y0 = v4;
        do
        {
          v10 = *v8;
          v11 = v8[1];
          v12 = v8 + 1;
          v13 = (unsigned __int8 *)v12[1];
          v12 += 2;
          v14 = v12[1];
          y1 = v11;
          v15 = *v12++;
          y3 = v15;
          y2c = v12[1];
          inputa = v13;
          v8 = v12 + 2;
          *(_DWORD *)v9 = ROQCinematic::yuv_to_rgb24(this, v10, v14, y2c);
          v16 = (int *)(v9 + 2);
          *v16++ = ROQCinematic::yuv_to_rgb24(this, y1, v14, y2c);
          *v16++ = ROQCinematic::yuv_to_rgb24(this, (int)inputa, v14, y2c);
          *v16 = ROQCinematic::yuv_to_rgb24(this, y3, v14, y2c);
          v9 = (unsigned __int16 *)(v16 + 1);
          --y0;
        }
        while ( y0 );
        v7 = vq2;
        v6 = four;
      }
      v17 = vq4;
      v18 = vq8;
      if ( v6 > 0 )
      {
        y2 = v6;
        while ( 1 )
        {
          v19 = &v7[8 * *v8];
          v20 = &v7[8 * v8[1]];
          v8 += 2;
          v21 = 2;
          do
          {
            *(_DWORD *)v17 = *(_DWORD *)v19;
            *(_DWORD *)v18 = *(_DWORD *)v19;
            *((_DWORD *)v18 + 1) = *(_DWORD *)v19;
            *((_DWORD *)v17 + 1) = *((_DWORD *)v19 + 1);
            v22 = v18 + 2;
            v22[1] = *((_DWORD *)v19 + 1);
            ++v22;
            v22[1] = *((_DWORD *)v19 + 1);
            ++v22;
            v23 = v17 + 2;
            *((_DWORD *)v23 + 1) = *(_DWORD *)v20;
            v22[1] = *(_DWORD *)v20;
            ++v22;
            v22[1] = *(_DWORD *)v20;
            ++v22;
            v23 += 2;
            *((_DWORD *)v23 + 1) = *((_DWORD *)v20 + 1);
            v22[1] = *((_DWORD *)v20 + 1);
            ++v22;
            v22[1] = *((_DWORD *)v20 + 1);
            ++v22;
            v22[1] = *(_DWORD *)v19;
            ++v22;
            v22[1] = *(_DWORD *)v19;
            ++v22;
            v22[1] = *((_DWORD *)v19 + 1);
            ++v22;
            v22[1] = *((_DWORD *)v19 + 1);
            ++v22;
            v22[1] = *(_DWORD *)v20;
            v22 += 2;
            *v22++ = *(_DWORD *)v20;
            *v22++ = *((_DWORD *)v20 + 1);
            *v22 = *((_DWORD *)v20 + 1);
            v17 = v23 + 4;
            v18 = (unsigned __int16 *)(v22 + 1);
            v19 += 4;
            v20 += 4;
            --v21;
          }
          while ( v21 );
          if ( !--y2 )
            break;
          v7 = vq2;
        }
      }
    }
  }
}

// FUNC: private: void __thiscall ROQCinematic::recurseQuad(long,long,long,long,long)
void __thiscall ROQCinematic::recurseQuad(ROQCinematic *this, int startX, int startY, int quadSize, int xOff, int yOff)
{
  int xsize; // ecx
  int CIN_HEIGHT; // eax
  unsigned __int8 *v12; // eax
  int startYa; // [esp+18h] [ebp+8h]
  int offset; // [esp+1Ch] [ebp+Ch]

  while ( 1 )
  {
    xsize = this->xsize;
    startYa = this->screenDelta;
    offset = this->ysize;
    if ( xsize > this->CIN_WIDTH )
      xsize = this->CIN_WIDTH;
    CIN_HEIGHT = this->CIN_HEIGHT;
    if ( (signed int)this->ysize > CIN_HEIGHT )
      offset = this->CIN_HEIGHT;
    if ( startX >= 0 && quadSize + startX <= xsize && startY + quadSize <= offset && startY >= 0 && quadSize <= 8 )
    {
      v12 = &this->image[4 * xOff + 4 * startX + this->samplesPerLine * (yOff + startY + ((CIN_HEIGHT - offset) >> 1))];
      this->qStatus[0][this->onQuad] = v12;
      this->qStatus[1][this->onQuad++] = &v12[startYa];
    }
    if ( quadSize == 4 )
      break;
    quadSize >>= 1;
    ROQCinematic::recurseQuad(this, startX, startY, quadSize, xOff, yOff);
    ROQCinematic::recurseQuad(this, quadSize + startX, startY, quadSize, xOff, yOff);
    startY += quadSize;
    ROQCinematic::recurseQuad(this, startX, startY, quadSize, xOff, yOff);
    startX += quadSize;
  }
}

// FUNC: private: void __thiscall ROQCinematic::setupQuad(long,long)
void __thiscall ROQCinematic::setupQuad(ROQCinematic *this, int xOff, int yOff)
{
  signed int ysize; // edi
  int v5; // ebx
  signed int v6; // ecx
  int v7; // edi
  signed int i; // eax
  int numQuadCels; // [esp+Ch] [ebp-4h]

  ysize = this->ysize;
  v5 = 0;
  v6 = ((ysize * this->xsize) >> 4) + (int)((ysize * this->xsize) >> 4) / 4 + 64;
  numQuadCels = v6;
  this->onQuad = 0;
  if ( ysize > 0 )
  {
    do
    {
      v7 = 0;
      if ( (int)this->xsize > 0 )
      {
        do
        {
          ROQCinematic::recurseQuad(this, v7, v5, 16, xOff, yOff);
          v7 += 16;
        }
        while ( v7 < (signed int)this->xsize );
        v6 = numQuadCels;
      }
      v5 += 16;
    }
    while ( v5 < (signed int)this->ysize );
  }
  for ( i = v6 - 64; i < v6; ++i )
  {
    this->qStatus[0][i] = 0;
    this->qStatus[1][i] = 0;
  }
}

// FUNC: private: void __thiscall ROQCinematic::readQuadInfo(unsigned char *)
void __thiscall ROQCinematic::readQuadInfo(ROQCinematic *this, unsigned __int8 *qData)
{
  int xsize; // eax
  int ysize; // edx
  bool v5; // zf
  int screenDelta; // eax
  int CIN_HEIGHT; // ecx
  int CIN_WIDTH; // eax

  this->xsize = *qData + (qData[1] << 8);
  this->ysize = qData[2] + (qData[3] << 8);
  this->maxsize = qData[4] + (qData[5] << 8);
  xsize = this->xsize;
  ysize = this->ysize;
  this->minsize = qData[6] + (qData[7] << 8);
  this->samplesPerLine = 4 * xsize;
  v5 = this->image == 0;
  this->CIN_HEIGHT = ysize;
  this->CIN_WIDTH = xsize;
  this->screenDelta = ysize * 4 * xsize;
  if ( v5 )
    this->image = (unsigned __int8 *)Mem_Alloc(8 * ysize * xsize, 0xCu);
  screenDelta = this->screenDelta;
  CIN_HEIGHT = this->CIN_HEIGHT;
  this->t[0] = screenDelta;
  this->t[1] = -screenDelta;
  CIN_WIDTH = this->CIN_WIDTH;
  this->half = 0;
  this->smootheddouble = 0;
  this->drawX = CIN_WIDTH;
  this->drawY = CIN_HEIGHT;
}

// FUNC: private: void __thiscall ROQCinematic::RoQPrepMcomp(long,long)
void __thiscall ROQCinematic::RoQPrepMcomp(ROQCinematic *this, int xoff, int yoff)
{
  int samplesPerLine; // edx
  int v4; // ebx
  int v5; // eax
  int v6; // esi
  unsigned int *mcomp; // edx
  int v8; // edi
  bool v9; // zf
  int i; // [esp+10h] [ebp-8h]
  int v11; // [esp+14h] [ebp-4h]
  unsigned int *xoffa; // [esp+1Ch] [ebp+4h]
  int yoffa; // [esp+20h] [ebp+8h]

  samplesPerLine = this->samplesPerLine;
  i = samplesPerLine;
  v4 = 4;
  if ( this->xsize == 4 * this->ysize && !this->half )
  {
    samplesPerLine *= 2;
    v4 = 8;
    i = samplesPerLine;
  }
  v5 = v4 * (xoff - 8);
  v6 = samplesPerLine * (yoff - 8);
  mcomp = this->mcomp;
  v11 = v5;
  xoffa = this->mcomp;
  yoffa = 16;
  while ( 1 )
  {
    v8 = 16;
    do
    {
      *mcomp = this->normalBuffer0 - v6 - v5;
      v5 += v4;
      mcomp += 16;
      --v8;
    }
    while ( v8 );
    v6 += i;
    mcomp = xoffa + 1;
    v9 = yoffa-- == 1;
    ++xoffa;
    if ( v9 )
      break;
    v5 = v11;
  }
}

// FUNC: void __cdecl jpeg_memory_src(struct jpeg_decompress_struct *,unsigned char *,int)
void __cdecl jpeg_memory_src(
        jpeg_common_struct *cinfo,
        unsigned __int8 *infile,
        unsigned __int8 (__cdecl *size)(jpeg_decompress_struct *))
{
  jpeg_source_mgr *v3; // eax
  jpeg_memory_mgr *mem; // ecx
  jpeg_source_mgr *err; // eax

  if ( !cinfo[1].err )
  {
    v3 = (jpeg_source_mgr *)cinfo->mem->alloc_small(cinfo, 0, 44);
    mem = cinfo->mem;
    cinfo[1].err = (jpeg_error_mgr *)v3;
    v3[1].bytes_in_buffer = (int)mem->alloc_small(cinfo, 0, 0x8000u);
  }
  err = (jpeg_source_mgr *)cinfo[1].err;
  err->init_source = init_source;
  err->fill_input_buffer = fill_input_buffer;
  err->skip_input_data = skip_input_data;
  err->resync_to_restart = jpeg_resync_to_restart;
  err->term_source = (void (__cdecl *)(jpeg_decompress_struct *))SpawnStub;
  err[1].next_input_byte = infile;
  err[1].fill_input_buffer = size;
  err->bytes_in_buffer = 0;
  err->next_input_byte = 0;
}

// FUNC: int __cdecl JPEGBlit(unsigned char *,unsigned char *,int)
int __cdecl JPEGBlit(
        unsigned __int8 *wStatus,
        unsigned __int8 *data,
        unsigned __int8 (__cdecl *datasize)(jpeg_decompress_struct *))
{
  int v3; // esi
  unsigned __int8 **v4; // ebx
  unsigned __int8 *i; // edi
  jpeg_decompress_struct cinfo; // [esp+Ch] [ebp-1A8h] BYREF

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  jpeg_memory_src((jpeg_common_struct *)&cinfo, data, datasize);
  jpeg_read_header(&cinfo, 1u);
  cinfo.dct_method = JDCT_FLOAT;
  cinfo.dither_mode = JDITHER_NONE;
  cinfo.do_fancy_upsampling = 0;
  jpeg_start_decompress(&cinfo);
  v3 = cinfo.output_width * cinfo.output_components;
  v4 = cinfo.mem->alloc_sarray(&cinfo, 1, cinfo.output_width * cinfo.output_components, 1);
  for ( i = &wStatus[v3 * (cinfo.output_height - 1)]; cinfo.output_scanline < cinfo.output_height; i -= v3 )
  {
    jpeg_read_scanlines(&cinfo, v4, 1u);
    SIMDProcessor->Memcpy(SIMDProcessor, i, *v4, v3);
  }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress((jpeg_compress_struct *)&cinfo);
  return 1;
}

// FUNC: private: void __thiscall ROQCinematic::RoQ_init(void)
void __thiscall ROQCinematic::RoQ_init(ROQCinematic *this)
{
  unsigned __int8 *v1; // eax
  int v2; // esi
  int v3; // edx

  v1 = file;
  this->RoQPlayed = 24;
  v2 = v1[6];
  v3 = v1[7] << 8;
  this->roqFPS = v2 + v3;
  if ( !(v2 + v3) )
    this->roqFPS = 30;
  this->numQuads = -1;
  this->roq_id = v1[8] + (v1[9] << 8);
  this->RoQFrameSize = v1[10] + ((v1[11] + (v1[12] << 8)) << 8);
  this->roq_flags = v1[14] + (v1[15] << 8);
}

// FUNC: private: void __thiscall ROQCinematic::RoQShutdown(void)
void __thiscall ROQCinematic::RoQShutdown(ROQCinematic *this)
{
  idFile *iFile; // eax

  if ( this->status )
  {
    iFile = this->iFile;
    this->status = FMV_IDLE;
    if ( iFile )
    {
      fileSystem->CloseFile(fileSystem, iFile);
      this->iFile = 0;
    }
    idStr::operator=(&this->fileName, (char *)&entityFilter);
  }
}

// FUNC: public: virtual struct cinData_t __thiscall idSndWindow::ImageForTime(int)
cinData_t *__thiscall idSndWindow::ImageForTime(idSndWindow *this, cinData_t *result, int milliseconds)
{
  idSndWindow *v3; // eax

  v3 = this;
  LOBYTE(v3) = this->showWaveform;
  soundSystem->ImageForTime(soundSystem, result, milliseconds, (const bool)v3);
  return result;
}

// FUNC: public: virtual int __thiscall idSndWindow::AnimationLength(void)
int __thiscall idSndWindow::AnimationLength(idSndWindow *this)
{
  return -1;
}

// FUNC: public: static class idCinematic * __cdecl idCinematic::Alloc(void)
idCinematic *__cdecl idCinematic::Alloc()
{
  idCinematic *result; // eax

  result = (idCinematic *)Memory::Allocate(0xCu);
  if ( !result )
    return 0;
  result->__vftable = (idCinematic_vtbl *)&idCinematic::`vftable';
  result->mode = 2;
  result->PIMPL = 0;
  return result;
}

// FUNC: public: virtual __thiscall idCinematic::~idCinematic(void)
void __thiscall idCinematic::~idCinematic(WMVCinematic *this)
{
  idCinematic *PIMPL; // ecx
  idCinematic *v3; // ecx

  PIMPL = this->PIMPL;
  this->__vftable = (WMVCinematic_vtbl *)&idCinematic::`vftable';
  if ( PIMPL )
    PIMPL->Close(PIMPL);
  v3 = this->PIMPL;
  this->mode = 2;
  if ( v3 )
  {
    ((void (__thiscall *)(idCinematic *, int))v3->~idCinematic)(v3, 1);
    this->PIMPL = 0;
  }
}

// FUNC: public: virtual bool __thiscall WMVCinematic::InitFromFile(char const *,bool,int)
bool __thiscall WMVCinematic::InitFromFile(WMVCinematic *this, const char *qpath, bool looping, int options)
{
  this->Close(this);
  return 0;
}

// FUNC: public: __thiscall ROQCinematic::ROQCinematic(void)
void __thiscall ROQCinematic::ROQCinematic(ROQCinematic *this)
{
  this->mode = 2;
  this->PIMPL = 0;
  this->__vftable = (ROQCinematic_vtbl *)&ROQCinematic::`vftable';
  this->fileName.len = 0;
  this->fileName.alloced = 20;
  this->fileName.data = this->fileName.baseBuffer;
  this->fileName.baseBuffer[0] = 0;
  this->image = 0;
  this->status = FMV_EOF;
  this->buf = 0;
  this->iFile = 0;
  this->qStatus[0] = (unsigned __int8 **)Mem_Alloc(0x20000, 0xCu);
  this->qStatus[1] = (unsigned __int8 **)Mem_Alloc(0x20000, 0xCu);
}

// FUNC: public: virtual int __thiscall ROQCinematic::AnimationLength(void)
int __thiscall ROQCinematic::AnimationLength(ROQCinematic *this)
{
  return this->animationLength;
}

// FUNC: public: virtual void __thiscall ROQCinematic::Close(void)
void __thiscall ROQCinematic::Close(ROQCinematic *this)
{
  idFile *iFile; // eax

  if ( this->image )
  {
    Mem_Free(this->image);
    this->image = 0;
    this->buf = 0;
    this->status = FMV_EOF;
  }
  if ( this->status )
  {
    iFile = this->iFile;
    this->status = FMV_IDLE;
    if ( iFile )
    {
      fileSystem->CloseFile(fileSystem, iFile);
      this->iFile = 0;
    }
    idStr::operator=(&this->fileName, (char *)&entityFilter);
  }
}

// FUNC: private: void __thiscall ROQCinematic::RoQReset(void)
void __thiscall ROQCinematic::RoQReset(ROQCinematic *this)
{
  this->iFile->Seek(this->iFile, 0, FS_SEEK_SET);
  this->iFile->Read(this->iFile, file, 16);
  ROQCinematic::RoQ_init(this);
  this->status = FMV_LOOPED;
}

// FUNC: private: void __thiscall ROQCinematic::RoQInterrupt(void)
void __thiscall ROQCinematic::RoQInterrupt(ROQCinematic *this)
{
  unsigned __int8 *i; // edi
  int v3; // eax
  ROQCinematic *v4; // ecx
  unsigned __int8 *image; // eax
  int v6; // eax
  unsigned __int8 *v7; // edi
  bool v8; // cc
  bool v9; // zf
  unsigned __int8 *v10; // [esp-18h] [ebp-1Ch]
  int roqF0; // [esp-14h] [ebp-18h]
  int roqF1; // [esp-10h] [ebp-14h]
  int RoQFrameSize; // [esp-10h] [ebp-14h]

  this->iFile->Read(this->iFile, file, this->RoQFrameSize + 8);
  if ( this->RoQPlayed < this->ROQSize )
  {
    for ( i = file; ; i = v7 + 8 )
    {
      switch ( this->roq_id )
      {
        case 0x1001u:
          if ( this->numQuads == -1 )
          {
            ROQCinematic::readQuadInfo(this, i);
            ROQCinematic::setupQuad(this, 0, 0);
          }
          if ( this->numQuads != 1 )
            this->numQuads = 0;
          break;
        case 0x1002u:
          ROQCinematic::decodeCodeBook(this, i, this->roq_flags);
          break;
        case 0x1011u:
          roqF1 = this->roqF1;
          roqF0 = this->roqF0;
          if ( (this->numQuads & 1) != 0 )
          {
            this->normalBuffer0 = this->t[1];
            ROQCinematic::RoQPrepMcomp(this, roqF0, roqF1);
            ROQCinematic::blitVQQuad32fs(v4, v3, this->qStatus[1], i);
            image = this->image;
            this->buf = &image[this->screenDelta];
          }
          else
          {
            this->normalBuffer0 = this->t[0];
            ROQCinematic::RoQPrepMcomp(this, roqF0, roqF1);
            ROQCinematic::blitVQQuad32fs(this, v6, this->qStatus[0], i);
            image = this->image;
            this->buf = image;
          }
          if ( !this->numQuads )
            SIMDProcessor->Memcpy(SIMDProcessor, &image[this->screenDelta], image, this->samplesPerLine * this->ysize);
          ++this->numQuads;
          this->dirty = 1;
          break;
        case 0x1012u:
          if ( !this->numQuads )
          {
            RoQFrameSize = this->RoQFrameSize;
            v10 = this->image;
            this->normalBuffer0 = this->t[0];
            JPEGBlit(v10, i, RoQFrameSize);
            SIMDProcessor->Memcpy(
              SIMDProcessor,
              &this->image[this->screenDelta],
              this->image,
              this->samplesPerLine * this->ysize);
            ++this->numQuads;
          }
          break;
        case 0x1013u:
          goto $L115518;
        case 0x1020u:
        case 0x1021u:
          break;
        case 0x1030u:
          this->inMemory = this->roq_flags != 0;
$L115518:
          this->RoQFrameSize = 0;
          break;
        default:
          this->status = FMV_EOF;
          break;
      }
      if ( this->RoQPlayed >= this->ROQSize )
      {
        if ( this->looping )
          goto LABEL_33;
        this->status = FMV_EOF;
        return;
      }
      v7 = &i[this->RoQFrameSize];
      this->roq_id = *v7 + (v7[1] << 8);
      this->RoQFrameSize = v7[2] + ((v7[3] + (v7[4] << 8)) << 8);
      v8 = this->RoQFrameSize <= 0x10000;
      this->roq_flags = v7[6] + (v7[7] << 8);
      this->roqF0 = (char)v7[7];
      this->roqF1 = (char)v7[6];
      if ( !v8 || this->roq_id == 4228 )
        break;
      if ( !this->inMemory || this->status == FMV_EOF )
      {
        this->RoQPlayed += this->RoQFrameSize + 8;
        return;
      }
      this->inMemory = 0;
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "roq_size > 65536 || roq_id == 0x1084\n");
    v9 = !this->looping;
    this->status = FMV_EOF;
    if ( v9 )
      return;
  }
  else if ( !this->looping )
  {
    this->status = FMV_EOF;
    return;
  }
LABEL_33:
  ROQCinematic::RoQReset(this);
}

// FUNC: public: virtual bool __thiscall idCinematic::InitFromFile(char const *,bool,int)
bool __thiscall idCinematic::InitFromFile(idCinematic *this, const char *qpath, BOOL looping, int options)
{
  idCinematic *PIMPL; // ecx
  idCinematic *v6; // eax
  idCinematic_vtbl *v7; // eax
  idCinematic *v8; // ecx
  ROQCinematic *v9; // eax
  idCinematic *v10; // eax
  idCinematic *v11; // ecx

  this->Close(this);
  if ( strstr(qpath, ".wmv") )
  {
    if ( this->mode )
    {
      PIMPL = this->PIMPL;
      if ( PIMPL )
      {
        ((void (__thiscall *)(idCinematic *, int))PIMPL->~idCinematic)(PIMPL, 1);
        this->PIMPL = 0;
      }
      v6 = (idCinematic *)Memory::Allocate(0xCu);
      if ( v6 )
      {
        v6->mode = 2;
        v6->PIMPL = 0;
        v6->__vftable = (idCinematic_vtbl *)&WMVCinematic::`vftable';
        this->PIMPL = v6;
      }
      else
      {
        this->PIMPL = 0;
      }
      this->mode = 0;
      goto LABEL_19;
    }
    v7 = this->__vftable;
    v8 = this;
LABEL_18:
    ((void (__fastcall *)(idCinematic *))v7->Close)(v8);
    goto LABEL_19;
  }
  v8 = this->PIMPL;
  if ( this->mode == 1 )
  {
    v7 = v8->__vftable;
    goto LABEL_18;
  }
  if ( v8 )
  {
    ((void (__thiscall *)(idCinematic *, int))v8->~idCinematic)(v8, 1);
    this->PIMPL = 0;
  }
  v9 = (ROQCinematic *)Memory::Allocate(0x4B8u);
  if ( v9 )
    ROQCinematic::ROQCinematic(v9);
  else
    v10 = 0;
  this->PIMPL = v10;
  this->mode = 1;
LABEL_19:
  v11 = this->PIMPL;
  return v11 && v11->InitFromFile(v11, qpath, looping, options);
}

// FUNC: public: virtual __thiscall ROQCinematic::~ROQCinematic(void)
void __thiscall ROQCinematic::~ROQCinematic(ROQCinematic *this)
{
  idCinematic *PIMPL; // ecx
  idCinematic *v3; // ecx
  unsigned __int8 **v4; // [esp-8h] [ebp-20h]

  this->__vftable = (ROQCinematic_vtbl *)&ROQCinematic::`vftable';
  ROQCinematic::Close(this);
  Mem_Free(this->qStatus[0]);
  v4 = this->qStatus[1];
  this->qStatus[0] = 0;
  Mem_Free(v4);
  this->qStatus[1] = 0;
  idStr::FreeData(&this->fileName);
  PIMPL = this->PIMPL;
  this->__vftable = (ROQCinematic_vtbl *)&idCinematic::`vftable';
  if ( PIMPL )
    PIMPL->Close(PIMPL);
  v3 = this->PIMPL;
  this->mode = 2;
  if ( v3 )
  {
    ((void (__thiscall *)(idCinematic *, int))v3->~idCinematic)(v3, 1);
    this->PIMPL = 0;
  }
}

// FUNC: public: virtual bool __thiscall ROQCinematic::InitFromFile(char const *,bool,int)
bool __userpurge ROQCinematic::InitFromFile@<al>(
        ROQCinematic *this@<ecx>,
        int a2@<ebp>,
        int a3@<edi>,
        int a4@<esi>,
        const char *qpath,
        char amilooping,
        int options,
        char *text)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  idStr *p_fileName; // ebx
  idStr *v11; // esi
  unsigned int len; // edi
  int v13; // eax
  int v14; // esi
  int v15; // eax
  int v16; // eax
  char v17; // cl
  char *data; // eax
  idFile *v19; // eax
  int v20; // eax
  idFile *iFile; // ecx
  unsigned __int8 *v22; // eax
  double v23; // st7
  __int16 v24; // cx
  ROQCinematic_vtbl *v25; // edx
  bool v26; // al
  char v28[28]; // [esp+14h] [ebp-3Ch] BYREF
  idStr result; // [esp+30h] [ebp-20h] BYREF
  char *texta; // [esp+60h] [ebp+10h]

  *(_DWORD *)&result.baseBuffer[16] = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)&result.baseBuffer[12] = &_ehhandler__InitFromFile_idSndWindow__UAE_NPBD_NH_Z;
  *(_DWORD *)&result.baseBuffer[8] = ExceptionList;
  ((void (__thiscall *)(ROQCinematic *, int, int, int))this->Close)(this, a3, a4, a2);
  p_fileName = &this->fileName;
  this->inMemory = 0;
  this->animationLength = 100000;
  idStr::operator=(&this->fileName, text);
  idStr::MakeNameCanonical(&this->fileName);
  if ( idStr::FindChar(this->fileName.data, 47, 0, this->fileName.len) == -1 )
  {
    v11 = operator+(&result, "video/", &this->fileName);
    len = v11->len;
    v13 = v11->len + 1;
    texta = (char *)v11->len;
    if ( v13 > this->fileName.alloced )
      idStr::ReAllocate(&this->fileName, v13, 0);
    qmemcpy(this->fileName.data, v11->data, len);
    texta[(unsigned int)this->fileName.data] = 0;
    p_fileName->len = (int)texta;
    amilooping = -1;
    idStr::FreeData(&result);
  }
  v14 = p_fileName->len + 4;
  v15 = p_fileName->len + 5;
  if ( v15 > this->fileName.alloced )
    idStr::ReAllocate(&this->fileName, v15, 1);
  v16 = 0;
  v17 = 46;
  do
  {
    ++v16;
    this->fileName.data[this->fileName.len - 1 + v16] = v17;
    v17 = aRoq[v16];
  }
  while ( v17 );
  data = this->fileName.data;
  p_fileName->len = v14;
  data[v14] = 0;
  v19 = fileSystem->OpenFileRead(fileSystem, this->fileName.data, 1, 0);
  this->iFile = v19;
  if ( v19 )
  {
    v20 = v19->Length(v19);
    iFile = this->iFile;
    this->ROQSize = v20;
    this->looping = amilooping;
    this->CIN_HEIGHT = 512;
    this->CIN_WIDTH = 512;
    v22 = file;
    this->startTime = 0;
    this->buf = 0;
    iFile->Read(iFile, v22, 16);
    v23 = (double)file[6];
    v24 = *file + (file[1] << 8);
    this->frameRate = v23;
    if ( v23 == 32.0 )
      this->frameRate = 31.25;
    if ( v24 == 4228 )
    {
      ROQCinematic::RoQ_init(this);
      v25 = this->__vftable;
      this->status = FMV_PLAY;
      ((void (__stdcall *)(char *, _DWORD))v25->ImageForTime)(v28, 0);
      v26 = 1;
      this->status = this->looping;
      return v26;
    }
    ROQCinematic::RoQShutdown(this);
  }
  return 0;
}

// FUNC: public: virtual struct cinData_t __thiscall ROQCinematic::ImageForTime(int)
cinData_t *__thiscall ROQCinematic::ImageForTime(ROQCinematic *this, cinData_t *result, int thisTime)
{
  int v3; // ebp
  cinStatus_t v5; // eax
  unsigned __int64 v6; // rax
  bool v7; // zf
  int status; // edi
  int CIN_WIDTH; // ecx
  int CIN_HEIGHT; // edx
  unsigned __int8 *buf; // esi
  cinData_t *v12; // eax

  v3 = thisTime;
  if ( thisTime < 0 )
  {
    thisTime = 0;
    v3 = 0;
  }
  if ( r_skipROQ.internalVar->integerValue || (v5 = this->status, v5 == FMV_EOF) || v5 == FMV_IDLE )
  {
    v12 = result;
    result->imageWidth = 0;
    result->imageHeight = 0;
    result->image = 0;
    result->status = 0;
  }
  else
  {
    if ( !this->buf || this->startTime == -1 )
    {
      if ( this->startTime == -1 )
        ROQCinematic::RoQReset(this);
      this->startTime = v3;
    }
    v6 = (unsigned __int64)((double)(v3 - this->startTime) * this->frameRate * 0.001);
    this->tfps = v6;
    if ( (v6 & 0x80000000) != 0i64 )
      this->tfps = 0;
    if ( this->tfps < this->numQuads )
    {
      ROQCinematic::RoQReset(this);
      this->buf = 0;
      this->status = FMV_PLAY;
    }
    if ( this->buf )
    {
      while ( this->tfps != this->numQuads )
      {
        if ( this->status != FMV_PLAY )
          break;
        ROQCinematic::RoQInterrupt(this);
      }
    }
    else
    {
      do
        ROQCinematic::RoQInterrupt(this);
      while ( !this->buf );
    }
    if ( this->status == FMV_LOOPED )
    {
      v7 = this->buf == 0;
      this->status = FMV_PLAY;
      if ( v7 )
      {
        do
        {
          if ( this->status != FMV_PLAY )
            break;
          ROQCinematic::RoQInterrupt(this);
        }
        while ( !this->buf );
      }
      this->startTime = thisTime;
    }
    if ( this->status == FMV_EOF )
    {
      if ( this->looping )
      {
        ROQCinematic::RoQReset(this);
        v7 = this->status == FMV_LOOPED;
        this->buf = 0;
        if ( v7 )
          this->status = FMV_PLAY;
        do
        {
          if ( this->status != FMV_PLAY )
            break;
          ROQCinematic::RoQInterrupt(this);
        }
        while ( !this->buf );
        this->startTime = thisTime;
      }
      else
      {
        this->status = FMV_IDLE;
        ROQCinematic::RoQShutdown(this);
      }
    }
    status = this->status;
    CIN_WIDTH = this->CIN_WIDTH;
    CIN_HEIGHT = this->CIN_HEIGHT;
    buf = this->buf;
    v12 = result;
    result->imageWidth = CIN_WIDTH;
    result->imageHeight = CIN_HEIGHT;
    result->image = buf;
    result->status = status;
  }
  return v12;
}

// FUNC: public: virtual bool __thiscall idSndWindow::InitFromFile(char const *,bool,int)
char __thiscall idSndWindow::InitFromFile(idSndWindow *this, const char *qpath, bool amilooping, int options)
{
  char *baseBuffer; // edx
  const char *v6; // eax
  int v7; // edi
  const char *v8; // ecx
  char v9; // al
  unsigned __int8 v10; // al
  int v11; // esi
  bool v12; // zf
  char *v13; // ecx
  idStr fname; // [esp+8h] [ebp-2Ch] BYREF
  int v16; // [esp+30h] [ebp-4h]

  baseBuffer = fname.baseBuffer;
  fname.len = 0;
  fname.alloced = 20;
  fname.data = fname.baseBuffer;
  fname.baseBuffer[0] = 0;
  if ( qpath )
  {
    v6 = &qpath[strlen(qpath) + 1];
    v7 = v6 - (qpath + 1);
    if ( v6 - qpath > 20 )
    {
      idStr::ReAllocate(&fname, v6 - qpath, 1);
      baseBuffer = fname.data;
    }
    v8 = qpath;
    do
    {
      v9 = *v8;
      *baseBuffer++ = *v8++;
    }
    while ( v9 );
    baseBuffer = fname.data;
    fname.len = v7;
  }
  v10 = *baseBuffer;
  v11 = 0;
  v12 = *baseBuffer == 0;
  v16 = 0;
  if ( !v12 )
  {
    v13 = baseBuffer;
    do
    {
      if ( idStr::lowerCaseCharacter[v10] )
        v10 = idStr::lowerCaseCharacter[v10];
      *v13 = v10;
      baseBuffer = fname.data;
      v10 = fname.data[++v11];
      v13 = &fname.data[v11];
    }
    while ( v10 );
  }
  this->showWaveform = idStr::Icmp(baseBuffer, "waveform") == 0;
  v16 = -1;
  idStr::FreeData(&fname);
  return 1;
}
