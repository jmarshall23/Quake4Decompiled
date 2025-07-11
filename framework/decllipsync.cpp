
// FUNC: public: virtual char const * __thiscall rvDeclLipSync::DefaultDefinition(void)const
const char *__thiscall rvDeclLipSync::DefaultDefinition(rvDeclLipSync *this)
{
  return "{ description \"<DEFAULTED>\" }";
}

// FUNC: public: virtual void __thiscall rvDeclLipSync::FreeData(void)
void __thiscall rvDeclLipSync::FreeData(rvDeclLipSync *this)
{
  idStr *p_mDescription; // esi

  p_mDescription = &this->mDescription;
  idStr::FreeData(&this->mDescription);
  p_mDescription->len = 0;
  p_mDescription->alloced = 20;
  p_mDescription->data = p_mDescription->baseBuffer;
  p_mDescription->baseBuffer[0] = 0;
  idStr::FreeData(&this->mTranscribeText);
  this->mTranscribeText.len = 0;
  this->mTranscribeText.alloced = 20;
  this->mTranscribeText.data = this->mTranscribeText.baseBuffer;
  this->mTranscribeText.baseBuffer[0] = 0;
  idStr::FreeData(&this->mHMM);
  this->mHMM.len = 0;
  this->mHMM.alloced = 20;
  this->mHMM.data = this->mHMM.baseBuffer;
  this->mHMM.baseBuffer[0] = 0;
  idDict::Clear(&this->mLipSyncData);
}

// FUNC: public: void __thiscall rvDeclLipSync::SetLipSyncData(char const *,char const *)
void __thiscall rvDeclLipSync::SetLipSyncData(rvDeclLipSync *this, const char *lsd, const char *lang)
{
  idDeclBase *base; // ecx
  int v5; // esi
  int v6; // eax

  if ( strchr(lsd, 37) )
  {
    base = this->base;
    v5 = *(_DWORD *)common.type;
    v6 = (int)base->GetName(base);
    (*(void (**)(netadrtype_t, const char *, ...))(v5 + 136))(
      common.type,
      "SetLipSyncData: language %s for lipsync '%s' has invalid character %% in it",
      lang,
      v6);
  }
  else
  {
    idDict::Set(&this->mLipSyncData, lang, lsd);
  }
}

// FUNC: public: virtual bool __thiscall rvDeclLipSync::RebuildTextSource(void)
char __thiscall rvDeclLipSync::RebuildTextSource(rvDeclLipSync *this)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v3; // eax
  const char *v4; // eax
  int i; // esi
  idKeyValue *v6; // eax
  idFile_Memory f; // [esp+8h] [ebp-4Ch] BYREF
  int v9; // [esp+50h] [ebp-4h]

  idFile_Memory::idFile_Memory(&f);
  base = this->base;
  v3 = base->__vftable;
  v9 = 0;
  v4 = v3->GetName(base);
  idFile_Common::WriteFloatString(&f, "\r\nlipSync %s\r\n{\r\n", v4);
  if ( this->mDescription.len )
    idFile_Common::WriteFloatString(&f, "\tdescription\t\"%s\"\r\n", this->mDescription.data);
  if ( this->mTranscribeText.len )
    idFile_Common::WriteFloatString(&f, "\ttext\t\t\"%s\"\r\n", this->mTranscribeText.data);
  if ( idStr::Icmp(this->mHMM.data, "male") )
    idFile_Common::WriteFloatString(&f, "\thmm\t\t\"%s\"\r\n", this->mHMM.data);
  for ( i = 0; i < this->mLipSyncData.args.num; ++i )
  {
    if ( i < 0 || i >= this->mLipSyncData.args.num )
      v6 = 0;
    else
      v6 = &this->mLipSyncData.args.list[i];
    idFile_Common::WriteFloatString(&f, "\tvisemes\t\"%s\"\t\"%s\"\r\n", v6->key->data, v6->value->data);
  }
  idFile_Common::WriteFloatString(&f, "}\r\n\r\n");
  this->base->SetText(this->base, f.filePtr);
  v9 = -1;
  idFile_Memory::~idFile_Memory(&f);
  return 1;
}

// FUNC: public: virtual unsigned int __thiscall rvDeclLipSync::Size(void)const
unsigned int __thiscall rvDeclLipSync::Size(rvDeclLipSync *this)
{
  int alloced; // eax
  int v2; // edi
  int v3; // eax
  int v4; // edi
  int v5; // esi

  if ( this->mDescription.data == this->mDescription.baseBuffer )
    alloced = 0;
  else
    alloced = this->mDescription.alloced;
  v2 = alloced + 148;
  if ( this->mTranscribeText.data == this->mTranscribeText.baseBuffer )
    v3 = 0;
  else
    v3 = this->mTranscribeText.alloced;
  v4 = v3 + v2;
  if ( this->mHMM.data == this->mHMM.baseBuffer )
    return v4 + idDict::Allocated(&this->mLipSyncData);
  v5 = this->mHMM.alloced;
  return v4 + v5 + idDict::Allocated(&this->mLipSyncData);
}

// FUNC: public: virtual void __thiscall rvDeclLipSyncEditLocal::SetLipSyncDescription(class rvDeclLipSync *,char const *)
void __thiscall rvDeclLipSyncEditLocal::SetLipSyncDescription(
        rvDeclLipSyncEditLocal *this,
        rvDeclLipSync *edit,
        char *desc)
{
  idStr::operator=(&edit->mDescription, desc);
}

// FUNC: public: virtual void __thiscall rvDeclLipSyncEditLocal::SetLipSyncTranscribeText(class rvDeclLipSync *,char const *)
void __thiscall rvDeclLipSyncEditLocal::SetLipSyncTranscribeText(
        rvDeclLipSyncEditLocal *this,
        rvDeclLipSync *edit,
        char *text)
{
  idStr::operator=(&edit->mTranscribeText, text);
}

// FUNC: public: virtual void __thiscall rvDeclLipSyncEditLocal::SetLipSyncData(class rvDeclLipSync *,char const *,char const *)
void __thiscall rvDeclLipSyncEditLocal::SetLipSyncData(
        rvDeclLipSyncEditLocal *this,
        rvDeclLipSync *edit,
        const char *lsd,
        const char *lang)
{
  rvDeclLipSync::SetLipSyncData(edit, lsd, lang);
}

// FUNC: public: virtual bool __thiscall rvDeclLipSync::Parse(char const *,int,bool)
char __thiscall rvDeclLipSync::Parse(rvDeclLipSync *this, const char *text, int textLength, bool noCaching)
{
  rvDeclLipSync *v4; // ebx
  bool v5; // zf
  const char *v6; // esi
  int v7; // eax
  int len; // esi
  idStr *p_mHMM; // ebp
  int v10; // ebx
  int v12; // [esp+10h] [ebp-17Ch]
  idToken token; // [esp+18h] [ebp-174h] BYREF
  idToken lang; // [esp+68h] [ebp-124h] BYREF
  idLexer src; // [esp+B8h] [ebp-D4h] BYREF
  int v17; // [esp+188h] [ebp-4h]

  v4 = this;
  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v17 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  lang.floatvalue = 0.0;
  lang.len = 0;
  lang.alloced = 20;
  lang.data = lang.baseBuffer;
  lang.baseBuffer[0] = 0;
  v5 = v4->mLipSyncData.args.num == 0;
  LOBYTE(v17) = 2;
  if ( v5 )
  {
    idHashIndex::Free(&v4->mLipSyncData.argHash);
    v4->mLipSyncData.argHash.hashSize = 16;
    v4->mLipSyncData.argHash.indexSize = 16;
  }
  v6 = v4->base->GetFileName(v4->base);
  v7 = v4->base->GetLineNum(v4->base);
  idLexer::LoadMemory(&src, text, textLength, v6, v7);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  idStr::operator=(&token, "male");
  len = token.len;
  p_mHMM = &v4->mHMM;
  v12 = token.len;
  if ( token.len + 1 > v4->mHMM.alloced )
    idStr::ReAllocate(&v4->mHMM, token.len + 1, 0);
  qmemcpy(v4->mHMM.data, token.data, len);
  v4->mHMM.data[v12] = 0;
  p_mHMM->len = v12;
  if ( idLexer::ReadToken(&src, &token) )
  {
    while ( idStr::Icmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "description") )
      {
        if ( idStr::Icmp(token.data, "text") )
        {
          if ( idStr::Icmp(token.data, "hmm") )
          {
            if ( !idStr::Icmp(token.data, "visemes") )
            {
              idLexer::ReadToken(&src, &lang);
              idLexer::ReadToken(&src, &token);
              rvDeclLipSync::SetLipSyncData(v4, token.data, lang.data);
            }
          }
          else
          {
            idLexer::ReadToken(&src, &token);
            v10 = token.len;
            if ( token.len + 1 > p_mHMM->alloced )
              idStr::ReAllocate(p_mHMM, token.len + 1, 0);
            qmemcpy(p_mHMM->data, token.data, v10);
            p_mHMM->data[v10] = 0;
            p_mHMM->len = v10;
            v4 = this;
          }
        }
        else
        {
          idLexer::ReadToken(&src, &token);
          idStr::operator=(&v4->mTranscribeText, token.data);
        }
      }
      else
      {
        if ( !idLexer::ReadToken(&src, &token) )
          goto LABEL_19;
        idStr::operator=(&v4->mDescription, token.data);
      }
      if ( !idLexer::ReadToken(&src, &token) )
        goto LABEL_19;
    }
    LOBYTE(v17) = 1;
    idStr::FreeData(&lang);
    LOBYTE(v17) = 0;
    idStr::FreeData(&token);
    v17 = -1;
    idLexer::~idLexer(&src);
    return 1;
  }
  else
  {
LABEL_19:
    LOBYTE(v17) = 1;
    idStr::FreeData(&lang);
    LOBYTE(v17) = 0;
    idStr::FreeData(&token);
    v17 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
}
