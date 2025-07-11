
// FUNC: public: virtual char const * __thiscall idDeclTable::DefaultDefinition(void)const
const char *__thiscall idDeclTable::DefaultDefinition(idDeclTable *this)
{
  return "{ { 0 } }";
}

// FUNC: public: virtual float __thiscall idDeclTable::TableLookup(float)const
double __thiscall idDeclTable::TableLookup(idDeclTable *this, float fraction)
{
  int v3; // esi
  int v5; // edx
  double v6; // st7
  double v7; // st7
  double v8; // st7
  float offset; // [esp+10h] [ebp-8h]
  float offseta; // [esp+10h] [ebp-8h]
  float v11; // [esp+14h] [ebp-4h]

  v3 = this->values.num - 1;
  if ( v3 <= 1 )
    return 1.0;
  if ( this->clamp )
  {
    if ( fraction < 0.0 )
      return *this->values.list;
    offset = (double)v3 * fraction - fraction;
    v5 = (int)offset;
    if ( (int)offset >= this->values.num - 2 )
      return this->values.list[v3 - 1];
    v6 = offset - (double)(int)offset;
  }
  else
  {
    v7 = (double)v3;
    v11 = v7;
    v8 = v7 * fraction;
    offseta = v8;
    if ( v8 < 0.0 )
      offseta = ceil(-fraction) * v11 + offseta;
    v5 = (int)offseta % v3;
    v6 = offseta - (double)(int)offseta;
    if ( v5 < 0 || v6 < 0.0 )
    {
      v5 = 0;
      v6 = 0.0;
    }
  }
  if ( this->snap )
    return this->values.list[v5];
  else
    return (1.0 - v6) * this->values.list[v5] + v6 * this->values.list[v5 + 1];
}

// FUNC: public: virtual unsigned int __thiscall idDeclTable::Size(void)const
int __thiscall idDeclTable::Size(idDeclTable *this)
{
  return 4 * this->values.size + 36;
}

// FUNC: public: virtual void __thiscall idDeclTable::FreeData(void)
void __thiscall idDeclTable::FreeData(idDeclTable *this)
{
  this->snap = 0;
  this->clamp = 0;
  if ( this->values.list )
    Memory::Free(this->values.list);
  this->values.list = 0;
  this->values.num = 0;
  this->values.size = 0;
}

// FUNC: public: virtual bool __thiscall idDeclTable::Parse(char const *,int,bool)
char __thiscall idDeclTable::Parse(idDeclTable *this, const char *text, int textLength, bool noCaching)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // edx
  const char *v7; // edi
  int v8; // eax
  float *v9; // edx
  int v10; // eax
  int granularity; // eax
  bool v12; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v16; // ecx
  float *list; // edi
  int j; // eax
  int k; // eax
  int v20; // ebp
  int v21; // eax
  int v22; // ecx
  float *v23; // edi
  int m; // eax
  float v; // [esp+10h] [ebp-12Ch]
  float va; // [esp+10h] [ebp-12Ch]
  bool errorFlag; // [esp+17h] [ebp-125h] BYREF
  idToken token; // [esp+18h] [ebp-124h] BYREF
  idLexer src; // [esp+68h] [ebp-D4h] BYREF
  int v31; // [esp+138h] [ebp-4h]

  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v31 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  base = this->base;
  v6 = base->__vftable;
  LOBYTE(v31) = 1;
  v7 = v6->GetFileName(base);
  v8 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&src, text, textLength, v7, v8);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  this->snap = 0;
  this->clamp = 0;
  this->minValue = idMath::INFINITY;
  this->maxValue = -1.0e30;
  if ( this->values.list )
    Memory::Free(this->values.list);
  this->values.list = 0;
  this->values.num = 0;
  this->values.size = 0;
  if ( idLexer::ReadToken(&src, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "snap") )
      {
        if ( idStr::Icmp(token.data, "clamp") )
        {
          if ( idStr::Icmp(token.data, "{") )
          {
            idLexer::Warning(&src, "unknown token '%s'", token.data);
          }
          else
          {
            while ( 1 )
            {
              va = idLexer::ParseFloat(&src, &errorFlag);
              if ( errorFlag )
                break;
              if ( !this->values.list )
              {
                granularity = this->values.granularity;
                if ( granularity > 0 )
                {
                  if ( granularity != this->values.size )
                  {
                    v12 = granularity < this->values.num;
                    this->values.size = granularity;
                    if ( v12 )
                      this->values.num = granularity;
                    this->values.list = (float *)Memory::Allocate(4 * granularity);
                    for ( i = 0; i < this->values.num; ++i )
                      this->values.list[i] = *(float *)(4 * i);
                  }
                }
                else
                {
                  this->values.list = 0;
                  this->values.num = 0;
                  this->values.size = 0;
                }
              }
              num = this->values.num;
              size = this->values.size;
              if ( num == size )
              {
                if ( !this->values.granularity )
                  this->values.granularity = 16;
                v16 = size + this->values.granularity - (size + this->values.granularity) % this->values.granularity;
                if ( v16 > 0 )
                {
                  if ( v16 != this->values.size )
                  {
                    list = this->values.list;
                    this->values.size = v16;
                    if ( v16 < num )
                      this->values.num = v16;
                    this->values.list = (float *)Memory::Allocate(4 * v16);
                    for ( j = 0; j < this->values.num; ++j )
                      this->values.list[j] = list[j];
                    if ( list )
                      Memory::Free(list);
                  }
                }
                else
                {
                  if ( this->values.list )
                    Memory::Free(this->values.list);
                  this->values.list = 0;
                  this->values.num = 0;
                  this->values.size = 0;
                }
              }
              this->values.list[this->values.num++] = va;
              if ( va < (double)this->minValue )
                this->minValue = va;
              if ( va > (double)this->maxValue )
                this->maxValue = va;
              idLexer::ReadToken(&src, &token);
              if ( !idStr::Cmp(token.data, "}") )
                goto LABEL_7;
              if ( idStr::Cmp(token.data, ",") )
              {
                idLexer::Warning(&src, "expected comma or brace");
                break;
              }
            }
          }
          this->base->MakeDefault(this->base);
          LOBYTE(v31) = 0;
          idStr::FreeData(&token);
          v31 = -1;
          idLexer::~idLexer(&src);
          return 0;
        }
        this->clamp = 1;
      }
      else
      {
        this->snap = 1;
      }
LABEL_7:
      if ( !idLexer::ReadToken(&src, &token) )
        break;
    }
  }
  v9 = this->values.list;
  v = *v9;
  if ( !v9 )
  {
    v10 = this->values.granularity;
    if ( v10 > 0 )
    {
      if ( v10 != this->values.size )
      {
        v12 = v10 < this->values.num;
        this->values.size = v10;
        if ( v12 )
          this->values.num = v10;
        this->values.list = (float *)Memory::Allocate(4 * v10);
        for ( k = 0; k < this->values.num; ++k )
          this->values.list[k] = *(float *)(4 * k);
      }
    }
    else
    {
      this->values.list = 0;
      this->values.num = 0;
      this->values.size = 0;
    }
  }
  v20 = this->values.num;
  v21 = this->values.size;
  if ( v20 == v21 )
  {
    if ( !this->values.granularity )
      this->values.granularity = 16;
    v22 = v21 + this->values.granularity - (v21 + this->values.granularity) % this->values.granularity;
    if ( v22 > 0 )
    {
      if ( v22 != this->values.size )
      {
        v23 = this->values.list;
        this->values.size = v22;
        if ( v22 < v20 )
          this->values.num = v22;
        this->values.list = (float *)Memory::Allocate(4 * v22);
        for ( m = 0; m < this->values.num; ++m )
          this->values.list[m] = v23[m];
        if ( v23 )
          Memory::Free(v23);
      }
    }
    else
    {
      if ( this->values.list )
        Memory::Free(this->values.list);
      this->values.list = 0;
      this->values.num = 0;
      this->values.size = 0;
    }
  }
  this->values.list[this->values.num++] = v;
  LOBYTE(v31) = 0;
  idStr::FreeData(&token);
  v31 = -1;
  idLexer::~idLexer(&src);
  return 1;
}

// FUNC: public: __thiscall idDeclTable::idDeclTable(void)
void __thiscall idDeclTable::idDeclTable(idDeclTable *this)
{
  this->base = 0;
  this->__vftable = (idDeclTable_vtbl *)&idDeclTable::`vftable';
  this->values.list = 0;
  this->values.num = 0;
  this->values.size = 0;
  this->values.granularity = 16;
}
