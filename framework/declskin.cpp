
// FUNC: public: virtual char const * __thiscall idDeclSkin::DefaultDefinition(void)const
const char *__thiscall idDeclSkin::DefaultDefinition(idDeclSkin *this)
{
  return "{\n\t\"*\"\t\"_default\"\n}";
}

// FUNC: public: virtual unsigned int __thiscall idDeclSkin::Size(void)const
int __thiscall idDeclSkin::Size(idDeclSkin *this)
{
  return 8 * (this->mappings.size + 4 * this->associatedModels.size) + 40;
}

// FUNC: public: virtual void __thiscall idDeclSkin::FreeData(void)
void __thiscall idDeclSkin::FreeData(idDeclSkin *this)
{
  if ( this->mappings.list )
    Memory::Free(this->mappings.list);
  this->mappings.list = 0;
  this->mappings.num = 0;
  this->mappings.size = 0;
}

// FUNC: public: virtual bool __thiscall idDeclSkin::SetDefaultText(void)
char __thiscall idDeclSkin::SetDefaultText(idDeclSkin *this)
{
  idDeclManager_vtbl *v1; // edi
  int v3; // eax
  const char *v4; // edi
  const char *v5; // eax
  char generated[2048]; // [esp+10h] [ebp-800h] BYREF

  v1 = declManager->__vftable;
  v3 = ((int (__thiscall *)(idDeclBase *, _DWORD, _DWORD))this->base->GetName)(this->base, 0, 0);
  if ( !((int (__thiscall *)(idDeclManager *, int, int))v1->FindType)(declManager, 1, v3) )
    return 0;
  v4 = this->base->GetName(this->base);
  v5 = this->base->GetName(this->base);
  idStr::snPrintf(generated, 2048, "skin %s // IMPLICITLY GENERATED\n{\n_default %s\n}\n", v4, v5);
  this->base->SetText(this->base, generated);
  return 1;
}

// FUNC: public: class idMaterial const * __thiscall idDeclSkin::RemapShaderBySkin(class idMaterial const *)const
const idMaterial *__thiscall idDeclSkin::RemapShaderBySkin(idDeclSkin *this, const idMaterial *shader)
{
  const idMaterial *result; // eax
  int num; // edi
  int v4; // edx
  skinMapping_t *i; // ecx

  result = shader;
  if ( shader && (shader->numStages > 0 || shader->entityGui || shader->gui) )
  {
    num = this->mappings.num;
    v4 = 0;
    if ( num > 0 )
    {
      for ( i = this->mappings.list; i->from && i->from != shader; ++i )
      {
        if ( ++v4 >= num )
          return result;
      }
      return i->to;
    }
  }
  return result;
}

// FUNC: public: virtual bool __thiscall idDeclSkin::Parse(char const *,int,bool)
bool __thiscall idDeclSkin::Parse(idDeclSkin *this, const char *text, int textLength, bool noCaching)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // eax
  const char *v7; // esi
  int v8; // eax
  idStr *list; // eax
  char *v10; // esi
  int v11; // esi
  bool v12; // cc
  int *v13; // eax
  idStr *v14; // ebx
  int v15; // esi
  unsigned int v16; // edi
  idStr *v17; // ebx
  int v18; // eax
  int v19; // ebx
  int v20; // esi
  int v21; // esi
  idStr *v22; // eax
  char *v23; // esi
  idStr *v24; // edi
  int *v25; // eax
  idStr *v26; // ebx
  int v27; // esi
  unsigned int v28; // edi
  idStr *v29; // ebx
  int len; // esi
  idStr *v31; // ebx
  int granularity; // eax
  int i; // eax
  skinMapping_t *v34; // ecx
  int num; // ebx
  int size; // ecx
  int v37; // ecx
  skinMapping_t *v38; // esi
  int j; // eax
  skinMapping_t *v40; // ecx
  int v41; // eax
  skinMapping_t *v42; // ecx
  int k; // [esp+10h] [ebp-18Ch]
  int m; // [esp+10h] [ebp-18Ch]
  int v46; // [esp+14h] [ebp-188h]
  idStr *v47; // [esp+14h] [ebp-188h]
  int v48; // [esp+18h] [ebp-184h]
  int v49; // [esp+1Ch] [ebp-180h]
  int v50; // [esp+1Ch] [ebp-180h]
  const idMaterial *map; // [esp+20h] [ebp-17Ch]
  const idMaterial *map_4; // [esp+24h] [ebp-178h]
  idToken token; // [esp+28h] [ebp-174h] BYREF
  idToken token2; // [esp+78h] [ebp-124h] BYREF
  idLexer src; // [esp+C8h] [ebp-D4h] BYREF
  int v56; // [esp+198h] [ebp-4h]

  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v56 = 0;
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
  v6 = base->__vftable;
  LOBYTE(v56) = 2;
  v7 = v6->GetFileName(base);
  v8 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&src, text, textLength, v7, v8);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  list = this->associatedModels.list;
  if ( list )
  {
    v10 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v10);
  }
  this->associatedModels.list = 0;
  this->associatedModels.num = 0;
  this->associatedModels.size = 0;
  if ( idLexer::ReadToken(&src, &token) )
  {
    while ( idStr::Icmp(token.data, "}") )
    {
      if ( !idLexer::ReadToken(&src, &token2) )
      {
        idLexer::Warning(&src, "Unexpected end of file");
        this->base->MakeDefault(this->base);
        break;
      }
      if ( idStr::Icmp(token.data, "model") )
      {
        if ( idStr::Icmp(token.data, "*") )
          map = declManager->FindMaterial(declManager, token.data, 1);
        else
          map = 0;
        map_4 = declManager->FindMaterial(declManager, token2.data, 1);
        if ( !this->mappings.list )
        {
          granularity = this->mappings.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->mappings.size )
            {
              v12 = granularity < this->mappings.num;
              this->mappings.size = granularity;
              if ( v12 )
                this->mappings.num = granularity;
              this->mappings.list = (skinMapping_t *)Memory::Allocate(8 * granularity);
              for ( i = 0; i < this->mappings.num; ++i )
              {
                v34 = this->mappings.list;
                v34[i].from = *(const idMaterial **)(8 * i);
                v34[i].to = *(const idMaterial **)(8 * i + 4);
              }
            }
          }
          else
          {
            this->mappings.list = 0;
            this->mappings.num = 0;
            this->mappings.size = 0;
          }
        }
        num = this->mappings.num;
        size = this->mappings.size;
        if ( num == size )
        {
          if ( !this->mappings.granularity )
            this->mappings.granularity = 16;
          v37 = this->mappings.granularity + size - (this->mappings.granularity + size) % this->mappings.granularity;
          if ( v37 > 0 )
          {
            if ( v37 != this->mappings.size )
            {
              v38 = this->mappings.list;
              this->mappings.size = v37;
              if ( v37 < num )
                this->mappings.num = v37;
              this->mappings.list = (skinMapping_t *)Memory::Allocate(8 * v37);
              for ( j = 0; j < this->mappings.num; ++j )
              {
                v40 = this->mappings.list;
                v40[j].from = v38[j].from;
                v40[j].to = v38[j].to;
              }
              if ( v38 )
                Memory::Free(v38);
            }
          }
          else
          {
            if ( this->mappings.list )
              Memory::Free(this->mappings.list);
            this->mappings.list = 0;
            this->mappings.num = 0;
            this->mappings.size = 0;
          }
        }
        v41 = this->mappings.num;
        v42 = this->mappings.list;
        v42[v41].from = map;
        v42[v41].to = map_4;
        ++this->mappings.num;
      }
      else
      {
        if ( !this->associatedModels.list )
        {
          v11 = this->associatedModels.granularity;
          if ( v11 > 0 )
          {
            if ( v11 != this->associatedModels.size )
            {
              v12 = v11 < this->associatedModels.num;
              this->associatedModels.size = v11;
              if ( v12 )
                this->associatedModels.num = v11;
              v13 = (int *)Memory::Allocate(32 * v11 + 4);
              LOBYTE(v56) = 3;
              if ( v13 )
              {
                v14 = (idStr *)(v13 + 1);
                *v13 = v11;
                `eh vector constructor iterator'(
                  v13 + 1,
                  0x20u,
                  v11,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v14 = 0;
              }
              v12 = this->associatedModels.num <= 0;
              LOBYTE(v56) = 2;
              this->associatedModels.list = v14;
              v46 = 0;
              if ( !v12 )
              {
                v15 = 0;
                for ( k = 0; ; v15 = k )
                {
                  v16 = *(_DWORD *)v15;
                  v17 = (idStr *)((char *)this->associatedModels.list + v15);
                  v18 = *(_DWORD *)v15 + 1;
                  v49 = *(_DWORD *)v15;
                  if ( v18 > v17->alloced )
                    idStr::ReAllocate(v17, v18, 0);
                  k += 32;
                  qmemcpy(v17->data, *(const void **)(v15 + 4), v16);
                  v17->data[v49] = 0;
                  v17->len = v49;
                  if ( ++v46 >= this->associatedModels.num )
                    break;
                }
              }
            }
          }
          else
          {
            this->associatedModels.list = 0;
            this->associatedModels.num = 0;
            this->associatedModels.size = 0;
          }
        }
        v19 = this->associatedModels.num;
        v20 = this->associatedModels.size;
        if ( v19 == v20 )
        {
          if ( !this->associatedModels.granularity )
            this->associatedModels.granularity = 16;
          v21 = this->associatedModels.granularity
              + v20
              - (this->associatedModels.granularity + v20) % this->associatedModels.granularity;
          if ( v21 > 0 )
          {
            if ( v21 != this->associatedModels.size )
            {
              v24 = this->associatedModels.list;
              v47 = v24;
              this->associatedModels.size = v21;
              if ( v21 < v19 )
                this->associatedModels.num = v21;
              v25 = (int *)Memory::Allocate(32 * v21 + 4);
              LOBYTE(v56) = 4;
              if ( v25 )
              {
                v26 = (idStr *)(v25 + 1);
                *v25 = v21;
                `eh vector constructor iterator'(
                  v25 + 1,
                  0x20u,
                  v21,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              }
              else
              {
                v26 = 0;
              }
              v27 = 0;
              v12 = this->associatedModels.num <= 0;
              LOBYTE(v56) = 2;
              this->associatedModels.list = v26;
              v50 = 0;
              if ( !v12 )
              {
                for ( m = 0; ; v27 = m )
                {
                  v28 = *(int *)((char *)&v24->len + v27);
                  v29 = (idStr *)((char *)this->associatedModels.list + v27);
                  if ( (signed int)(v28 + 1) > v29->alloced )
                    idStr::ReAllocate(v29, v28 + 1, 0);
                  m += 32;
                  qmemcpy(v29->data, *(const void **)((char *)&v47->data + v27), v28);
                  v29->data[v28] = 0;
                  v29->len = v28;
                  v12 = ++v50 < this->associatedModels.num;
                  v24 = v47;
                  if ( !v12 )
                    break;
                }
              }
              if ( v24 )
              {
                `eh vector destructor iterator'(
                  v24,
                  0x20u,
                  *(_DWORD *)&v24[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(&v24[-1].baseBuffer[16]);
              }
            }
          }
          else
          {
            v22 = this->associatedModels.list;
            if ( v22 )
            {
              v23 = &v22[-1].baseBuffer[16];
              `eh vector destructor iterator'(
                v22,
                0x20u,
                *(_DWORD *)&v22[-1].baseBuffer[16],
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(v23);
            }
            this->associatedModels.list = 0;
            this->associatedModels.num = 0;
            this->associatedModels.size = 0;
          }
        }
        len = token2.len;
        v31 = &this->associatedModels.list[this->associatedModels.num];
        v48 = token2.len;
        if ( token2.len + 1 > v31->alloced )
          idStr::ReAllocate(v31, token2.len + 1, 0);
        qmemcpy(v31->data, token2.data, len);
        v31->data[v48] = 0;
        v31->len = v48;
        ++this->associatedModels.num;
      }
      if ( !idLexer::ReadToken(&src, &token) )
        break;
    }
  }
  LOBYTE(v56) = 1;
  idStr::FreeData(&token2);
  LOBYTE(v56) = 0;
  idStr::FreeData(&token);
  v56 = -1;
  idLexer::~idLexer(&src);
  return 0;
}

// FUNC: public: __thiscall idDeclSkin::idDeclSkin(void)
void __thiscall idDeclSkin::idDeclSkin(idDeclSkin *this)
{
  this->base = 0;
  this->__vftable = (idDeclSkin_vtbl *)&idDeclSkin::`vftable';
  this->mappings.granularity = 16;
  this->mappings.list = 0;
  this->mappings.num = 0;
  this->mappings.size = 0;
  this->associatedModels.list = 0;
  this->associatedModels.num = 0;
  this->associatedModels.size = 0;
  this->associatedModels.granularity = 16;
}
