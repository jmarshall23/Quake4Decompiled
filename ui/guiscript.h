
// FUNC: public: __thiscall idGSWinVar::idGSWinVar(void)
void __thiscall idGSWinVar::idGSWinVar(idGSWinVar *this)
{
  this->var = 0;
  this->own = 0;
}

// FUNC: public: __thiscall idGuiScriptList::~idGuiScriptList(void)
void __thiscall idGuiScriptList::~idGuiScriptList(idGuiScriptList *this)
{
  int i; // edi
  idGuiScript **list; // eax
  idGuiScript *v4; // ebx

  for ( i = 0; i < this->list.num; ++i )
  {
    list = this->list.list;
    v4 = list[i];
    if ( v4 )
    {
      idGuiScript::~idGuiScript(list[i]);
      Memory::Free(v4);
    }
    this->list.list[i] = 0;
  }
  if ( this->list.list )
    Memory::Free(this->list.list);
  this->list.list = 0;
  this->list.num = 0;
  this->list.size = 0;
}

// FUNC: public: unsigned int __thiscall idGuiScriptList::Size(void)
int __thiscall idGuiScriptList::Size(idGuiScriptList *this)
{
  int v1; // ebp
  int result; // eax
  idGuiScript *v3; // edi
  int v4; // esi
  int v5; // ebx
  idWinVar *var; // ecx
  int sz; // [esp+4h] [ebp-8h]
  idGuiScriptList *v8; // [esp+8h] [ebp-4h]

  v1 = 0;
  result = 16;
  v8 = this;
  sz = 16;
  if ( this->list.num > 0 )
  {
    do
    {
      v3 = this->list.list[v1];
      v4 = 0;
      v5 = 32;
      if ( v3->parms.num > 0 )
      {
        do
        {
          var = v3->parms.list[v4++].var;
          v5 += var->Size(var);
        }
        while ( v4 < v3->parms.num );
        this = v8;
      }
      sz += v5;
      ++v1;
    }
    while ( v1 < this->list.num );
    return sz;
  }
  return result;
}

// FUNC: public: void __thiscall idGuiScriptList::Append(class idGuiScript *)
void __thiscall idGuiScriptList::Append(idGuiScriptList *this, idGuiScript *gs)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v8; // ecx
  idGuiScript **list; // edi
  int j; // eax

  if ( !this->list.list )
  {
    granularity = this->list.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->list.size )
      {
        v4 = granularity < this->list.num;
        this->list.size = granularity;
        if ( v4 )
          this->list.num = granularity;
        this->list.list = (idGuiScript **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->list.num; ++i )
          this->list.list[i] = *(idGuiScript **)(4 * i);
      }
    }
    else
    {
      this->list.list = 0;
      this->list.num = 0;
      this->list.size = 0;
    }
  }
  num = this->list.num;
  size = this->list.size;
  if ( this->list.num == size )
  {
    if ( !this->list.granularity )
      this->list.granularity = 16;
    v8 = size + this->list.granularity - (size + this->list.granularity) % this->list.granularity;
    if ( v8 > 0 )
    {
      if ( v8 != this->list.size )
      {
        list = this->list.list;
        this->list.size = v8;
        if ( v8 < num )
          this->list.num = v8;
        this->list.list = (idGuiScript **)Memory::Allocate(4 * v8);
        for ( j = 0; j < this->list.num; ++j )
          this->list.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->list.list )
        Memory::Free(this->list.list);
      this->list.list = 0;
      this->list.num = 0;
      this->list.size = 0;
    }
  }
  this->list.list[this->list.num++] = gs;
}
