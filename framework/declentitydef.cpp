
// FUNC: public: virtual unsigned int __thiscall idDeclEntityDef::Size(void)const
unsigned int __thiscall idDeclEntityDef::Size(idDeclEntityDef *this)
{
  return idDict::Allocated(&this->dict) + 52;
}

// FUNC: public: virtual char const * __thiscall idDeclEntityDef::DefaultDefinition(void)const
const char *__thiscall idDeclEntityDef::DefaultDefinition(idDeclEntityDef *this)
{
  return "{\n\t\"DEFAULTED\"\t\"1\"\n}";
}

// FUNC: public: virtual void __thiscall idDeclEntityDef::Print(void)
void __thiscall idDeclEntityDef::Print(idDeclEntityDef *this)
{
  idDict::Print(&this->dict);
}

// FUNC: public: virtual bool __thiscall idDeclEntityDef::Parse(char const *,int,bool)
char __thiscall idDeclEntityDef::Parse(idDeclEntityDef *this, const char *text, int textLength, BOOL noCaching)
{
  int v5; // ebp
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v7; // eax
  const char *v8; // esi
  int v9; // eax
  idDict *p_dict; // ebx
  const char *v11; // eax
  _DWORD *v12; // edi
  int v13; // esi
  const idKeyValue *matched; // ebx
  const char *data; // ebp
  const char *v16; // eax
  int v17; // ecx
  int i; // eax
  int v19; // edx
  int v20; // eax
  _BYTE *v21; // ebp
  _DWORD *v22; // eax
  int v23; // ecx
  int v24; // edx
  int defList_4; // [esp+14h] [ebp-190h]
  idDict *v27; // [esp+20h] [ebp-184h]
  const idDeclEntityDef *copy; // [esp+24h] [ebp-180h]
  _BYTE *v30; // [esp+2Ch] [ebp-178h]
  idToken token; // [esp+30h] [ebp-174h] BYREF
  idToken token2; // [esp+80h] [ebp-124h] BYREF
  idLexer src; // [esp+D0h] [ebp-D4h] BYREF
  int v34; // [esp+1A0h] [ebp-4h]

  idLexer::idLexer(&src);
  v5 = 0;
  token.floatvalue = 0.0;
  v34 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  token2.floatvalue = 0.0;
  token2.len = 0;
  token2.alloced = 20;
  token2.data = token2.baseBuffer;
  token2.baseBuffer[0] = 0;
  base = this->base;
  v7 = base->__vftable;
  LOBYTE(v34) = 2;
  v8 = v7->GetFileName(base);
  v9 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&src, text, textLength, v8, v9);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  if ( idLexer::ReadToken(&src, &token) )
  {
    while ( 1 )
    {
      if ( !idStr::Icmp(token.data, "}") )
        goto LABEL_8;
      if ( token.type != 1 )
        break;
      if ( !idLexer::ReadToken(&src, &token2) )
      {
        idLexer::Warning(&src, "Unexpected end of file");
        this->base->MakeDefault(this->base);
        goto LABEL_45;
      }
      if ( idDict::FindKey(&this->dict, token.data) )
        idLexer::Warning(&src, "'%s' already defined", token.data);
      idDict::Set(&this->dict, token.data, token2.data);
      if ( !idLexer::ReadToken(&src, &token) )
        goto LABEL_8;
    }
    idLexer::Warning(&src, "Expected quoted string, but found '%s'", token.data);
    this->base->MakeDefault(this->base);
LABEL_45:
    LOBYTE(v34) = 1;
    idStr::FreeData(&token2);
    LOBYTE(v34) = 0;
    idStr::FreeData(&token);
    v34 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
LABEL_8:
  p_dict = &this->dict;
  v27 = &this->dict;
  v11 = this->base->GetName(this->base);
  idDict::Set(&this->dict, "classname", v11);
  v12 = 0;
  v13 = 0;
  defList_4 = 0;
  LOBYTE(v34) = 3;
  matched = idDict::MatchPrefix(p_dict, "inherit", 0);
  if ( !matched )
    goto LABEL_35;
  do
  {
    copy = (const idDeclEntityDef *)declManager->FindType(declManager, 4, matched->value->data, 1, noCaching);
    if ( !copy )
    {
      data = matched->value->data;
      v16 = this->base->GetName(this->base);
      idLexer::Warning(&src, "Unknown entityDef '%s' inherited by '%s'", data, v16);
      goto LABEL_33;
    }
    if ( v12 )
      goto LABEL_17;
    v17 = defList_4;
    if ( defList_4 != 16 )
    {
      defList_4 = 16;
      if ( v13 > 16 )
        v13 = 16;
      v12 = Memory::Allocate(0x40u);
      for ( i = 0; i < v13; ++i )
        v12[i] = *(_DWORD *)(4 * i);
LABEL_17:
      v17 = defList_4;
    }
    if ( v13 == v17 )
    {
      v19 = (v17 + 16) % 16;
      v20 = v17 + 16 - v19;
      if ( v20 > 0 )
      {
        if ( v20 != v17 )
        {
          v21 = v12;
          v30 = v12;
          defList_4 = v17 + 16 - v19;
          if ( v20 < v13 )
            v13 = v17 + 16 - v19;
          v22 = Memory::Allocate(4 * v20);
          v12 = v22;
          if ( v13 > 0 )
          {
            v23 = v21 - (_BYTE *)v22;
            v24 = v13;
            do
            {
              *v22 = *(_DWORD *)((char *)v22 + v23);
              ++v22;
              --v24;
            }
            while ( v24 );
            v21 = v30;
          }
          if ( v21 )
            Memory::Free(v21);
        }
      }
      else
      {
        if ( v12 )
          Memory::Free(v12);
        v12 = 0;
        v13 = 0;
        defList_4 = 0;
      }
    }
    v12[v13++] = copy;
LABEL_33:
    idDict::Delete(v27, matched->key->data);
    matched = idDict::MatchPrefix(v27, "inherit", 0);
  }
  while ( matched );
  v5 = 0;
LABEL_35:
  if ( v13 > 0 )
  {
    do
      idDict::SetDefaults(v27, (const idDict *)(v12[v5++] + 8));
    while ( v5 < v13 );
  }
  if ( !noCaching && !(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 1712130) )
    game->CacheDictionaryMedia(game, v27);
  LOBYTE(v34) = 2;
  if ( v12 )
    Memory::Free(v12);
  LOBYTE(v34) = 1;
  idStr::FreeData(&token2);
  LOBYTE(v34) = 0;
  idStr::FreeData(&token);
  v34 = -1;
  idLexer::~idLexer(&src);
  return 1;
}

// FUNC: public: __thiscall idDeclEntityDef::idDeclEntityDef(void)
void __thiscall idDeclEntityDef::idDeclEntityDef(idDeclEntityDef *this)
{
  idDict *p_dict; // esi
  idHashIndex *p_argHash; // ebp
  idKeyValue *list; // edi
  int num; // ecx
  int v5; // eax
  int i; // eax
  idKeyValue *v7; // ecx

  this->base = 0;
  p_dict = &this->dict;
  this->__vftable = (idDeclEntityDef_vtbl *)&idDeclEntityDef::`vftable';
  this->dict.args.granularity = 16;
  this->dict.args.list = 0;
  this->dict.args.num = 0;
  this->dict.args.size = 0;
  p_argHash = &this->dict.argHash;
  idHashIndex::Init(&this->dict.argHash, 1024, 1024);
  p_dict->args.granularity = 16;
  list = p_dict->args.list;
  if ( list )
  {
    num = p_dict->args.num;
    v5 = p_dict->args.num + 15 - (p_dict->args.num + 15) % 16;
    if ( v5 != p_dict->args.size )
    {
      if ( v5 > 0 )
      {
        p_dict->args.size = v5;
        if ( v5 < num )
          p_dict->args.num = v5;
        p_dict->args.list = (idKeyValue *)Memory::Allocate(8 * v5);
        for ( i = 0; i < p_dict->args.num; ++i )
        {
          v7 = p_dict->args.list;
          v7[i].key = list[i].key;
          v7[i].value = list[i].value;
        }
        Memory::Free(list);
      }
      else
      {
        Memory::Free(list);
        p_dict->args.list = 0;
        p_dict->args.num = 0;
        p_dict->args.size = 0;
      }
    }
  }
  p_dict->argHash.granularity = 16;
  idHashIndex::Free(p_argHash);
  p_argHash->indexSize = 16;
  p_argHash->hashSize = 128;
}
