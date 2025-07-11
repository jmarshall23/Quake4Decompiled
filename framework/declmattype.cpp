
// FUNC: public: virtual char const * __thiscall rvDeclMatType::DefaultDefinition(void)const
const char *__thiscall rvDeclMatType::DefaultDefinition(rvDeclMatType *this)
{
  return "{ description \"<DEFAULTED>\" rgb 0,0,0 }";
}

// FUNC: class rvDeclMatType const * __cdecl MT_FindMaterialTypeByTint(unsigned long)
const rvDeclMatType *__cdecl MT_FindMaterialTypeByTint(unsigned int tint)
{
  int v1; // edi
  int v2; // esi
  const rvDeclMatType *result; // eax

  v1 = declManager->GetNumDecls(declManager, DECL_MATERIALTYPE);
  v2 = 0;
  if ( v1 <= 0 )
    return 0;
  while ( 1 )
  {
    result = declManager->MaterialTypeByIndex(declManager, v2, 1);
    if ( *(_DWORD *)result->mTint == tint )
      break;
    if ( ++v2 >= v1 )
      return 0;
  }
  return result;
}

// FUNC: class rvDeclMatType const * __cdecl MT_FindMaterialTypeByClosestTint(unsigned long)
const rvDeclMatType *__cdecl MT_FindMaterialTypeByClosestTint(unsigned int tint)
{
  int v1; // ebp
  int v2; // edi
  const rvDeclMatType *v3; // eax
  const rvDeclMatType *bestmt; // [esp+14h] [ebp-14h]
  int count; // [esp+24h] [ebp-4h]

  v1 = 16777217;
  bestmt = 0;
  v2 = 0;
  count = declManager->GetNumDecls(declManager, DECL_MATERIALTYPE);
  if ( count <= 0 )
    return 0;
  do
  {
    v3 = declManager->MaterialTypeByIndex(declManager, v2, 1);
    if ( (HIBYTE(tint) - HIBYTE(*(_DWORD *)v3->mTint)) * (HIBYTE(tint) - HIBYTE(*(_DWORD *)v3->mTint))
       + (BYTE2(tint) - (unsigned __int8)BYTE2(*(_DWORD *)v3->mTint))
       * (BYTE2(tint) - (unsigned __int8)BYTE2(*(_DWORD *)v3->mTint))
       + (BYTE1(tint) - (unsigned __int8)BYTE1(*(_DWORD *)v3->mTint))
       * (BYTE1(tint) - (unsigned __int8)BYTE1(*(_DWORD *)v3->mTint)) < v1 )
    {
      v1 = (HIBYTE(tint) - HIBYTE(*(_DWORD *)v3->mTint)) * (HIBYTE(tint) - HIBYTE(*(_DWORD *)v3->mTint))
         + (BYTE2(tint) - (unsigned __int8)BYTE2(*(_DWORD *)v3->mTint))
         * (BYTE2(tint) - (unsigned __int8)BYTE2(*(_DWORD *)v3->mTint))
         + (BYTE1(tint) - (unsigned __int8)BYTE1(*(_DWORD *)v3->mTint))
         * (BYTE1(tint) - (unsigned __int8)BYTE1(*(_DWORD *)v3->mTint));
      bestmt = v3;
    }
    ++v2;
  }
  while ( v2 < count );
  return bestmt;
}

// FUNC: unsigned char * __cdecl MT_GetMaterialTypeArray(class idStr,int &,int &)
unsigned __int8 *__cdecl MT_GetMaterialTypeArray(idStr image, int *width, int *height)
{
  bool v3; // zf
  idFile *v4; // eax
  idFile *v5; // esi
  int *v6; // edi
  int v7; // eax
  int *v8; // ebx
  int v9; // eax
  int v10; // edi
  void *v11; // ebx
  int *v13; // esi
  int *v14; // edi
  int v15; // edi
  unsigned __int8 *v16; // eax
  unsigned __int8 *v17; // ebp
  unsigned __int8 *v18; // ebx
  unsigned int v19; // esi
  const rvDeclMatType *MaterialTypeByTint; // eax
  idFile *v21; // esi
  unsigned int v22; // [esp+18h] [ebp-2Ch]
  unsigned __int8 *pic; // [esp+2Ch] [ebp-18h] BYREF
  int v24; // [esp+30h] [ebp-14h]
  unsigned __int8 *array; // [esp+34h] [ebp-10h]
  int v26; // [esp+40h] [ebp-4h]

  v3 = mat_useHitMaterials.internalVar->integerValue == 0;
  v26 = 0;
  if ( !v3 )
  {
    idStr::SetFileExtension(&image, ".hit");
    v4 = fileSystem->OpenFileRead(fileSystem, image.data, 1, 0);
    v5 = v4;
    if ( v4 )
    {
      v6 = height;
      v4->Read(v4, height, 4);
      v7 = LittleLong(*v6);
      v8 = width;
      *v6 = v7;
      v5->Read(v5, v8, 4);
      v9 = LittleLong(*v8);
      *v8 = v9;
      v10 = v9 * *v6;
      v11 = Mem_ClearedAlloc(v10, 0xAu);
      v5->Read(v5, v11, v10);
      fileSystem->CloseFile(fileSystem, v5);
      v26 = -1;
      idStr::FreeData(&image);
      return (unsigned __int8 *)v11;
    }
    idStr::StripFileExtension(&image);
  }
  v13 = height;
  v14 = width;
  pic = 0;
  R_LoadImage(image.data, &pic, width, height, 0, 0);
  if ( pic )
  {
    v15 = *v13 * *v14;
    v16 = (unsigned __int8 *)Mem_ClearedAlloc(v15, 0xAu);
    v17 = pic;
    array = v16;
    v18 = v16;
    if ( v15 > 0 )
    {
      v24 = v15;
      do
      {
        v19 = *(_DWORD *)v17;
        v22 = *(_DWORD *)v17;
        v17 += 4;
        MaterialTypeByTint = MT_FindMaterialTypeByTint(v22);
        if ( !MaterialTypeByTint )
          MaterialTypeByTint = MT_FindMaterialTypeByClosestTint(v19);
        *v18++ = MaterialTypeByTint->base->Index(MaterialTypeByTint->base);
        --v24;
      }
      while ( v24 );
    }
    R_StaticFree(pic);
    if ( mat_writeHitMaterials.internalVar->integerValue )
    {
      idStr::SetFileExtension(&image, ".hit");
      v21 = fileSystem->OpenFileWrite(fileSystem, image.data, "fs_savepath", 0);
      if ( v21 )
      {
        v21->Write(v21, height, 4);
        v21->Write(v21, width, 4);
        v21->Write(v21, array, v15);
        fileSystem->CloseFile(fileSystem, v21);
      }
    }
    v26 = -1;
    idStr::FreeData(&image);
    return array;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Failed to load hit material image %s",
      image.data);
    v26 = -1;
    idStr::FreeData(&image);
    return 0;
  }
}

// FUNC: public: virtual void __thiscall rvDeclMatType::FreeData(void)
void __thiscall rvDeclMatType::FreeData(rvDeclMatType *this)
{
  idStr *p_mDescription; // esi

  p_mDescription = &this->mDescription;
  idStr::FreeData(&this->mDescription);
  p_mDescription->len = 0;
  p_mDescription->alloced = 20;
  p_mDescription->data = p_mDescription->baseBuffer;
  p_mDescription->baseBuffer[0] = 0;
}

// FUNC: public: virtual unsigned int __thiscall rvDeclMatType::Size(void)const
int __thiscall rvDeclMatType::Size(rvDeclMatType *this)
{
  if ( this->mDescription.data == this->mDescription.baseBuffer )
    return 44;
  else
    return this->mDescription.alloced + 44;
}

// FUNC: public: virtual bool __thiscall rvDeclMatType::Parse(char const *,int,bool)
char __thiscall rvDeclMatType::Parse(rvDeclMatType *this, const char *text, int textLength, bool noCaching)
{
  rvDeclMatType *v4; // ebp
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // edx
  const char *v7; // esi
  int v8; // eax
  int len; // ebx
  idStr *p_mDescription; // ebp
  unsigned __int8 tint[4]; // [esp+10h] [ebp-12Ch]
  idToken token; // [esp+18h] [ebp-124h] BYREF
  idLexer src; // [esp+68h] [ebp-D4h] BYREF
  int v16; // [esp+138h] [ebp-4h]

  v4 = this;
  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v16 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  base = v4->base;
  v6 = base->__vftable;
  LOBYTE(v16) = 1;
  v7 = v6->GetFileName(base);
  v8 = v4->base->GetLineNum(v4->base);
  idLexer::LoadMemory(&src, text, textLength, v7, v8);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  if ( idLexer::ReadToken(&src, &token) )
  {
    while ( idStr::Icmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "rgb") )
      {
        if ( !idStr::Icmp(token.data, "description") )
        {
          idLexer::ReadToken(&src, &token);
          len = token.len;
          p_mDescription = &v4->mDescription;
          if ( token.len + 1 > p_mDescription->alloced )
            idStr::ReAllocate(p_mDescription, token.len + 1, 0);
          qmemcpy(p_mDescription->data, token.data, len);
          p_mDescription->data[len] = 0;
          p_mDescription->len = len;
          v4 = this;
        }
      }
      else
      {
        tint[0] = idLexer::ParseInt(&src);
        idLexer::ExpectTokenString(&src, ",");
        tint[1] = idLexer::ParseInt(&src);
        idLexer::ExpectTokenString(&src, ",");
        tint[2] = idLexer::ParseInt(&src);
        tint[3] = -1;
        *(_DWORD *)v4->mTint = *(_DWORD *)tint;
      }
      if ( !idLexer::ReadToken(&src, &token) )
        goto LABEL_10;
    }
    LOBYTE(v16) = 0;
    idStr::FreeData(&token);
    v16 = -1;
    idLexer::~idLexer(&src);
    return 1;
  }
  else
  {
LABEL_10:
    LOBYTE(v16) = 0;
    idStr::FreeData(&token);
    v16 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
}
