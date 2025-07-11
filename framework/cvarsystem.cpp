
// FUNC: public: virtual bool __thiscall idCVarSystemLocal::IsInitialized(void)const
bool __thiscall idCVarSystemLocal::IsInitialized(idCVarSystemLocal *this)
{
  return this->initialized;
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::SetModifiedFlags(int)
void __thiscall idCVarSystemLocal::SetModifiedFlags(idCVarSystemLocal *this, int flags)
{
  this->modifiedFlags |= flags;
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::ClearModifiedFlags(int)
void __thiscall idCVarSystemLocal::ClearModifiedFlags(idCVarSystemLocal *this, int flags)
{
  this->modifiedFlags &= ~flags;
}

// FUNC: public: virtual __thiscall idInternalCVar::~idInternalCVar(void)
void __thiscall idInternalCVar::~idInternalCVar(idInternalCVar *this)
{
  this->__vftable = (idInternalCVar_vtbl *)&idInternalCVar::`vftable';
  Mem_Free(this->valueStrings);
  this->valueStrings = 0;
  idStr::FreeData(&this->descriptionString);
  idStr::FreeData(&this->valueString);
  idStr::FreeData(&this->resetString);
  idStr::FreeData(&this->nameString);
  this->__vftable = (idInternalCVar_vtbl *)&idCVar::`vftable';
}

// FUNC: public: char const * * __thiscall idInternalCVar::CopyValueStrings(char const * *)
const char **__thiscall idInternalCVar::CopyValueStrings(idInternalCVar *this, const char **strings)
{
  const char **v2; // edi
  const char *v4; // eax
  int v5; // edx
  int i; // esi
  int v7; // ecx
  const char **v8; // ecx
  int v9; // eax
  int v10; // ebx
  const char **v11; // ecx
  const char **v12; // ebp
  const char *v13; // edx
  _BYTE *v14; // esi
  char v15; // cl
  int v16; // ecx
  const char **ptr; // [esp+4h] [ebp-4h]
  const char **stringsa; // [esp+Ch] [ebp+4h]

  v2 = strings;
  if ( !strings )
    return 0;
  v4 = *strings;
  v5 = 0;
  for ( i = 0; v4; v5 += v7 + 1 )
  {
    v7 = 0;
    if ( *v4 )
    {
      do
        ++v7;
      while ( v4[v7] );
    }
    v4 = strings[++i];
  }
  v8 = (const char **)Mem_Alloc(v5 + 4 * i + 4, 9u);
  v9 = 0;
  ptr = v8;
  v10 = (int)&v8[i + 1];
  if ( *strings )
  {
    v11 = (const char **)((char *)v8 - (char *)strings);
    v12 = strings;
    for ( stringsa = v11; ; v11 = stringsa )
    {
      *(const char **)((char *)v2 + (_DWORD)v11) = (const char *)v10;
      v13 = *v12;
      v14 = (_BYTE *)v10;
      do
      {
        v15 = *v13;
        *v14++ = *v13++;
      }
      while ( v15 );
      v16 = 0;
      if ( **v12 )
      {
        do
          ++v16;
        while ( (*v12)[v16] );
      }
      ++v2;
      ++v9;
      v10 += v16 + 1;
      v12 = v2;
      if ( !*v2 )
        break;
    }
    v8 = ptr;
  }
  v8[v9] = 0;
  return v8;
}

// FUNC: char const * __cdecl CreateColumn(char const *,int,char const *,class idStr &)
char *__cdecl CreateColumn(const char *text, int columnWidth, const char *indent, idStr *string)
{
  const char *v4; // ecx
  int v5; // ebp
  int v6; // edi
  char v7; // al
  char v8; // bl
  int v9; // eax
  const char *v10; // edx
  const char *v11; // eax
  int v12; // ebx
  char v13; // cl
  int i; // eax
  char *data; // edx
  char v16; // bl
  int v17; // eax

  idStr::FreeData(string);
  v4 = text;
  string->len = 0;
  string->alloced = 20;
  string->data = string->baseBuffer;
  string->baseBuffer[0] = 0;
  v5 = 0;
  v6 = 0;
  if ( !*text )
    return string->data;
  do
  {
    if ( v5 - v6 >= columnWidth || v4[v5] == 10 )
    {
      for ( ; v5 > 0; --v5 )
      {
        v7 = v4[v5];
        if ( v7 <= 32 )
          break;
        if ( v7 == 47 )
          break;
        if ( v7 == 44 )
          break;
        if ( v7 == 92 )
          break;
      }
      for ( ; v6 < v5; string->data[string->len] = 0 )
      {
        v8 = v4[v6];
        v9 = string->len + 2;
        if ( v9 > string->alloced )
        {
          idStr::ReAllocate(string, v9, 1);
          v4 = text;
        }
        string->data[string->len++] = v8;
        ++v6;
      }
      v10 = indent;
      if ( indent )
      {
        v11 = &indent[strlen(indent) + 1];
        v12 = v11 - (indent + 1) + string->len;
        if ( v11 - indent + string->len > string->alloced )
        {
          idStr::ReAllocate(string, v11 - indent + string->len, 1);
          v10 = indent;
        }
        v13 = *v10;
        for ( i = 0; v13; ++i )
        {
          string->data[i + string->len] = v13;
          v13 = indent[i + 1];
        }
        data = string->data;
        v4 = text;
        string->len = v12;
        data[v12] = 0;
      }
      ++v6;
    }
    ++v5;
  }
  while ( v4[v5] );
  for ( ; v6 < v5; string->data[string->len] = 0 )
  {
    v16 = v4[v6];
    v17 = string->len + 2;
    if ( v17 > string->alloced )
    {
      idStr::ReAllocate(string, v17, 1);
      v4 = text;
    }
    string->data[string->len++] = v16;
    ++v6;
  }
  return string->data;
}

// FUNC: public: virtual class idCVarHelp * __thiscall idCVarSystemLocal::GetHelps(enum cvarHelpCategory_t)
idCVarHelp *__thiscall idCVarSystemLocal::GetHelps(idCVarSystemLocal *this, cvarHelpCategory_t category)
{
  int v2; // edx
  idCVarHelp *result; // eax
  idCVarHelp *i; // edi
  idCVarHelp *v5; // esi

  v2 = 0;
  result = 0;
  for ( i = 0; v2 < this->cvarHelps.num; ++v2 )
  {
    v5 = this->cvarHelps.list[v2];
    if ( (category & v5->category) != 0 )
    {
      if ( result )
        i->next = v5;
      else
        result = this->cvarHelps.list[v2];
      i = this->cvarHelps.list[v2];
      i->next = 0;
    }
  }
  return result;
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::CommandCompletion(void (__cdecl *)(char const *))
void __thiscall idCVarSystemLocal::CommandCompletion(idCVarSystemLocal *this, void (__cdecl *callback)(const char *))
{
  int i; // esi

  for ( i = 0; i < this->cvars.num; ++i )
    callback(this->cvars.list[i]->internalVar->idCVar::name);
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::ArgCompletion(char const *,void (__cdecl *)(char const *))
void __thiscall idCVarSystemLocal::ArgCompletion(
        idCVarSystemLocal *this,
        const char *cmdString,
        void (__cdecl *callback)(const char *))
{
  int v4; // esi
  idInternalCVar *v5; // eax
  const char *data; // eax
  const char *v7; // ecx
  idCmdArgs args; // [esp+8h] [ebp-904h] BYREF

  args.argc = 0;
  idCmdArgs::TokenizeString(&args, cmdString, 0);
  v4 = 0;
  if ( this->cvars.num > 0 )
  {
    while ( 1 )
    {
      v5 = this->cvars.list[v4];
      if ( v5->valueCompletion )
      {
        data = v5->nameString.data;
        v7 = args.argv[0];
        if ( args.argc <= 0 )
          v7 = &entityFilter;
        if ( !idStr::Icmp(v7, data) )
          break;
      }
      if ( ++v4 >= this->cvars.num )
        return;
    }
    this->cvars.list[v4]->valueCompletion(&args, callback);
  }
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::RemoveFlaggedAutoCompletion(int)
void __thiscall idCVarSystemLocal::RemoveFlaggedAutoCompletion(idCVarSystemLocal *this, int flags)
{
  int i; // eax
  idInternalCVar *v3; // edx

  for ( i = 0; i < this->cvars.num; ++i )
  {
    v3 = this->cvars.list[i];
    if ( (flags & v3->internalVar->flags) != 0 )
      v3->valueCompletion = 0;
  }
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::ApplyFlaggedVariables(unsigned char *,unsigned int)
void __thiscall idCVarSystemLocal::ApplyFlaggedVariables(
        idCVarSystemLocal *this,
        unsigned __int8 *buf,
        unsigned int bufSize)
{
  const char *v3; // esi
  unsigned __int8 *v5; // ebx
  const char *v6; // edi
  const char *v7; // esi
  idCVar *v8; // eax
  int flags; // ecx
  idCVar *internalVar; // eax
  idCVar_vtbl *v11; // edx
  int v12; // [esp-8h] [ebp-14h]
  int v13; // [esp-8h] [ebp-14h]

  v3 = (const char *)buf;
  v5 = &buf[bufSize];
  if ( *buf )
  {
    do
    {
      if ( v3 >= (const char *)v5 )
        break;
      v6 = v3;
      v7 = &v3[strlen(v3) + 1];
      if ( v7 >= (const char *)v5 )
        break;
      v8 = this->Find(this, v6);
      if ( !v8 )
        break;
      flags = v8->internalVar->flags;
      internalVar = v8->internalVar;
      v11 = internalVar->__vftable;
      if ( (flags & 1) != 0 )
      {
        LOBYTE(flags) = *v7 & 1;
        v11->InternalSetBool(internalVar, flags);
        v3 = v7 + 1;
      }
      else if ( (flags & 2) != 0 )
      {
        v12 = *(_DWORD *)v7;
        v3 = v7 + 4;
        v11->InternalSetInteger(internalVar, v12);
      }
      else if ( (flags & 4) != 0 )
      {
        v13 = *(_DWORD *)v7;
        v3 = v7 + 4;
        ((void (__thiscall *)(idCVar *, int))v11->InternalSetFloat)(internalVar, v13);
      }
      else
      {
        v11->InternalSetString(internalVar, v7);
        v3 = &v7[strlen(v7) + 1];
      }
    }
    while ( *v3 );
  }
}

// FUNC: public: virtual class idDict const * __thiscall idCVarSystemLocal::MoveCVarsToDict(int)const
const idDict *__thiscall idCVarSystemLocal::MoveCVarsToDict(idCVarSystemLocal *this, int flags)
{
  int i; // esi
  idCVar *internalVar; // ecx

  idDict::Clear(&idCVarSystemLocal::moveCVarsToDict);
  for ( i = 0; i < this->cvars.num; ++i )
  {
    internalVar = this->cvars.list[i]->internalVar;
    if ( (flags & internalVar->flags) != 0 )
      idDict::Set(&idCVarSystemLocal::moveCVarsToDict, internalVar->name, internalVar->value);
  }
  return &idCVarSystemLocal::moveCVarsToDict;
}

// FUNC: int __cdecl idListSortCompare<class idInternalCVar const *>(class idInternalCVar const * const *,class idInternalCVar const * const *)
unsigned int __cdecl idListSortCompare<idInternalCVar const *>(
        const idInternalCVar *const *a,
        const idInternalCVar *const *b)
{
  return idStr::Icmp((*a)->internalVar->idCVar::name, (*b)->internalVar->idCVar::name);
}

// FUNC: public: void __thiscall idInternalCVar::UpdateValue(void)
void __thiscall idInternalCVar::UpdateValue(idInternalCVar *this)
{
  int flags; // eax
  int v3; // eax
  const char *value; // ecx
  char v5; // dl
  bool v6; // cc
  int v7; // eax
  bool v8; // c0
  double v9; // st7
  int v10; // eax
  unsigned int v11; // edi
  int v12; // esi
  char *data; // edx
  char *v14; // ecx
  char v15; // al
  long double v16; // st7
  int v17; // ebx
  int v18; // esi
  char *v19; // edx
  char *v20; // ecx
  char v21; // al
  const char **valueStrings; // eax
  int v23; // esi
  double v24; // st7
  long double v25; // st7
  double floatValue; // [esp+0h] [ebp-ECh]
  int integerValue; // [esp+4h] [ebp-E8h]
  int v28; // [esp+18h] [ebp-D4h]
  int v29; // [esp+1Ch] [ebp-D0h]
  idStr v30; // [esp+20h] [ebp-CCh] BYREF
  idStr v31; // [esp+40h] [ebp-ACh] BYREF
  char dest[64]; // [esp+60h] [ebp-8Ch] BYREF
  char string[64]; // [esp+A0h] [ebp-4Ch] BYREF
  int v34; // [esp+E8h] [ebp-4h]

  flags = this->flags;
  if ( (flags & 1) != 0 )
  {
    v3 = atoi(this->value);
    value = this->value;
    v28 = v3 != 0;
    this->integerValue = v28;
    this->floatValue = (float)v28;
    if ( idStr::Icmp(value, "0") && idStr::Icmp(this->value, "1") )
    {
      v5 = (this->integerValue != 0) + 48;
      v30.alloced = 20;
      v30.data = v30.baseBuffer;
      v30.baseBuffer[0] = v5;
      v30.baseBuffer[1] = 0;
      v30.len = 1;
      v6 = this->valueString.alloced < 2;
      v34 = 0;
      if ( v6 )
        idStr::ReAllocate(&this->valueString, 2, 0);
      *this->valueString.data = *v30.data;
      this->valueString.data[1] = 0;
      this->valueString.len = 1;
      v34 = -1;
      idStr::FreeData(&v30);
      this->value = this->valueString.data;
    }
    return;
  }
  if ( (flags & 2) != 0 )
  {
    v7 = atoi(this->value);
    v8 = this->valueMin < (double)this->valueMax;
    this->integerValue = v7;
    if ( v8 )
    {
      v9 = (double)v7;
      if ( v9 < this->valueMin )
      {
        this->integerValue = (int)this->valueMin;
        goto LABEL_15;
      }
      if ( v9 > this->valueMax )
      {
        this->integerValue = (int)this->valueMax;
        goto LABEL_15;
      }
    }
    if ( idStr::IsNumeric(this->value) && !idStr::FindChar(this->value, 46, 0, -1) )
    {
LABEL_22:
      this->floatValue = (float)this->integerValue;
      return;
    }
LABEL_15:
    integerValue = this->integerValue;
    v30.len = 0;
    v30.alloced = 20;
    v30.data = v30.baseBuffer;
    v30.baseBuffer[0] = 0;
    v10 = sprintf(string, "%d", integerValue);
    v11 = v10;
    v12 = v10 + 1;
    v29 = v10;
    if ( v10 + 1 > 20 )
      idStr::ReAllocate(&v30, v10 + 1, 1);
    data = v30.data;
    v14 = string;
    do
    {
      v15 = *v14;
      *data++ = *v14++;
    }
    while ( v15 );
    v30.len = v11;
    v6 = v12 <= this->valueString.alloced;
    v34 = 1;
    if ( !v6 )
      idStr::ReAllocate(&this->valueString, v12, 0);
    qmemcpy(this->valueString.data, v30.data, v11);
    this->valueString.data[v29] = 0;
    this->valueString.len = v29;
    v34 = -1;
    idStr::FreeData(&v30);
    this->value = this->valueString.data;
    goto LABEL_22;
  }
  if ( (flags & 4) != 0 )
  {
    v16 = atof(this->value);
    this->floatValue = v16;
    if ( this->valueMin < (double)this->valueMax )
    {
      if ( v16 < this->valueMin )
      {
        this->floatValue = this->valueMin;
        goto LABEL_30;
      }
      if ( v16 > this->valueMax )
      {
        this->floatValue = this->valueMax;
        goto LABEL_30;
      }
    }
    if ( idStr::IsNumeric(this->value) )
    {
LABEL_43:
      this->integerValue = (int)this->floatValue;
      return;
    }
LABEL_30:
    floatValue = this->floatValue;
    v31.len = 0;
    v31.alloced = 20;
    v31.data = v31.baseBuffer;
    v31.baseBuffer[0] = 0;
    v17 = idStr::snPrintf(dest, 64, "%f", floatValue);
    if ( v17 > 0 )
    {
      while ( v31.baseBuffer[v17 + 19] == 48 )
      {
        dest[--v17] = 0;
        if ( v17 <= 0 )
          goto LABEL_36;
      }
      do
      {
        if ( v31.baseBuffer[v17 + 19] != 46 )
          break;
        dest[--v17] = 0;
      }
      while ( v17 > 0 );
    }
LABEL_36:
    v18 = v17 + 1;
    if ( v17 + 1 > v31.alloced )
      idStr::ReAllocate(&v31, v17 + 1, 1);
    v19 = v31.data;
    v20 = dest;
    do
    {
      v21 = *v20;
      *v19++ = *v20++;
    }
    while ( v21 );
    v31.len = v17;
    v6 = v18 <= this->valueString.alloced;
    v34 = 2;
    if ( !v6 )
      idStr::ReAllocate(&this->valueString, v18, 0);
    qmemcpy(this->valueString.data, v31.data, v17);
    this->valueString.data[v17] = 0;
    this->valueString.len = v17;
    v34 = -1;
    idStr::FreeData(&v31);
    this->value = this->valueString.data;
    goto LABEL_43;
  }
  valueStrings = this->valueStrings;
  if ( valueStrings && *valueStrings )
  {
    this->integerValue = 0;
    v23 = 0;
    if ( *valueStrings )
    {
      while ( idStr::Icmp(this->valueString.data, this->valueStrings[v23]) )
      {
        if ( !this->valueStrings[++v23] )
          goto LABEL_51;
      }
      this->integerValue = v23;
    }
LABEL_51:
    idStr::operator=(&this->valueString, (char *)this->valueStrings[this->integerValue]);
    v24 = (double)this->integerValue;
    this->value = this->valueString.data;
    this->floatValue = v24;
  }
  else if ( this->valueString.len >= 32 )
  {
    this->floatValue = 0.0;
    this->integerValue = 0;
  }
  else
  {
    v25 = atof(this->value);
    this->floatValue = v25;
    this->integerValue = (int)v25;
  }
}

// FUNC: public: void __thiscall idInternalCVar::Set(char const *,bool,bool)
void __thiscall idInternalCVar::Set(idInternalCVar *this, char *newValue, bool force, bool fromServer)
{
  int flags; // eax
  char *data; // edi
  int v7; // eax

  if ( session && session->IsMultiplayer(session) && !fromServer )
  {
    flags = this->flags;
    if ( (flags & 0x800) != 0 && idAsyncNetwork::client.active )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%s is a synced over the network and cannot be changed on a multiplayer client.\n",
        this->nameString.data);
      return;
    }
    if ( (flags & 0x2000) != 0 && !cvarSystem->GetCVarBool(cvarSystem, "net_allowCheats") )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%s cannot be changed in multiplayer.\n",
        this->nameString.data);
      return;
    }
  }
  data = newValue;
  if ( !newValue )
    data = this->resetString.data;
  if ( force )
    goto LABEL_21;
  v7 = this->flags;
  if ( (v7 & 0x10000) != 0 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%s is read only.\n",
      this->nameString.data);
    return;
  }
  if ( (v7 & 0x8000) == 0 )
  {
LABEL_21:
    if ( idStr::Icmp(this->valueString.data, data) )
    {
      idStr::operator=(&this->valueString, data);
      this->value = this->valueString.data;
      idInternalCVar::UpdateValue(this);
      BYTE2(this->internalVar->flags) |= 4u;
      cvarSystem->SetModifiedFlags(cvarSystem, this->flags);
    }
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%s is write protected.\n",
      this->nameString.data);
  }
}

// FUNC: public: void __thiscall idInternalCVar::Reset(void)
void __thiscall idInternalCVar::Reset(idInternalCVar *this)
{
  int len; // esi
  idStr *p_valueString; // ebp

  len = this->resetString.len;
  p_valueString = &this->valueString;
  if ( len + 1 > this->valueString.alloced )
    idStr::ReAllocate(&this->valueString, len + 1, 0);
  qmemcpy(p_valueString->data, this->resetString.data, len);
  p_valueString->data[len] = 0;
  p_valueString->len = len;
  this->value = this->valueString.data;
  idInternalCVar::UpdateValue(this);
}

// FUNC: private: virtual void __thiscall idInternalCVar::InternalSetString(char const *)
void __thiscall idInternalCVar::InternalSetString(idInternalCVar *this, char *newValue)
{
  idInternalCVar::Set(this, newValue, 1, 0);
}

// FUNC: private: virtual void __thiscall idInternalCVar::InternalServerSetString(char const *)
void __thiscall idInternalCVar::InternalServerSetString(idInternalCVar *this, char *newValue)
{
  char *data; // edi

  data = newValue;
  if ( session )
    session->IsMultiplayer(session);
  if ( !newValue )
    data = this->resetString.data;
  if ( idStr::Icmp(this->valueString.data, data) )
  {
    idStr::operator=(&this->valueString, data);
    this->value = this->valueString.data;
    idInternalCVar::UpdateValue(this);
    BYTE2(this->internalVar->flags) |= 4u;
    cvarSystem->SetModifiedFlags(cvarSystem, this->flags);
  }
}

// FUNC: private: virtual void __thiscall idInternalCVar::InternalSetBool(bool)
void __thiscall idInternalCVar::InternalSetBool(idInternalCVar *this, bool newValue)
{
  idStr v2; // [esp+0h] [ebp-2Ch] BYREF
  int v3; // [esp+28h] [ebp-4h]

  v2.data = v2.baseBuffer;
  v2.alloced = 20;
  v2.baseBuffer[0] = newValue + 48;
  v2.baseBuffer[1] = 0;
  v2.len = 1;
  v3 = 0;
  idInternalCVar::Set(this, v2.baseBuffer, 1, 0);
  v3 = -1;
  idStr::FreeData(&v2);
}

// FUNC: private: virtual void __thiscall idInternalCVar::InternalSetInteger(int)
void __thiscall idInternalCVar::InternalSetInteger(idInternalCVar *this, int newValue)
{
  int v3; // esi
  char *data; // edx
  char *v5; // ecx
  char v6; // al
  idStr v7; // [esp+8h] [ebp-6Ch] BYREF
  char string[64]; // [esp+28h] [ebp-4Ch] BYREF
  int v9; // [esp+70h] [ebp-4h]

  v7.len = 0;
  v7.alloced = 20;
  v7.data = v7.baseBuffer;
  v7.baseBuffer[0] = 0;
  v3 = sprintf(string, "%d", newValue);
  if ( v3 + 1 > 20 )
    idStr::ReAllocate(&v7, v3 + 1, 1);
  data = v7.data;
  v5 = string;
  do
  {
    v6 = *v5;
    *data++ = *v5++;
  }
  while ( v6 );
  v7.len = v3;
  v9 = 0;
  idInternalCVar::Set(this, v7.data, 1, 0);
  v9 = -1;
  idStr::FreeData(&v7);
}

// FUNC: private: virtual void __thiscall idInternalCVar::InternalSetFloat(float)
void __thiscall idInternalCVar::InternalSetFloat(idInternalCVar *this, float newValue)
{
  int v3; // esi
  char *data; // edx
  char *v5; // ecx
  char v6; // al
  idStr v7; // [esp+14h] [ebp-6Ch] BYREF
  char dest[64]; // [esp+34h] [ebp-4Ch] BYREF
  int v9; // [esp+7Ch] [ebp-4h]

  v7.len = 0;
  v7.alloced = 20;
  v7.data = v7.baseBuffer;
  v7.baseBuffer[0] = 0;
  v3 = idStr::snPrintf(dest, 64, "%f", newValue);
  if ( v3 > 0 )
  {
    while ( v7.baseBuffer[v3 + 19] == 48 )
    {
      dest[--v3] = 0;
      if ( v3 <= 0 )
        goto LABEL_7;
    }
    do
    {
      if ( v7.baseBuffer[v3 + 19] != 46 )
        break;
      dest[--v3] = 0;
    }
    while ( v3 > 0 );
  }
LABEL_7:
  if ( v3 + 1 > v7.alloced )
    idStr::ReAllocate(&v7, v3 + 1, 1);
  data = v7.data;
  v5 = dest;
  do
  {
    v6 = *v5;
    *data++ = *v5++;
  }
  while ( v6 );
  v7.len = v3;
  v9 = 0;
  idInternalCVar::Set(this, v7.data, 1, 0);
  v9 = -1;
  idStr::FreeData(&v7);
}

// FUNC: public: virtual __thiscall idCVarSystemLocal::~idCVarSystemLocal(void)
void __thiscall idCVarSystemLocal::~idCVarSystemLocal(idCVarSystemLocal *this)
{
  idCVarHelp **list; // eax
  idInternalCVar **v3; // eax

  this->__vftable = (idCVarSystemLocal_vtbl *)&idCVarSystemLocal::`vftable';
  list = this->cvarHelps.list;
  if ( list )
    Memory::Free(list);
  this->cvarHelps.list = 0;
  this->cvarHelps.num = 0;
  this->cvarHelps.size = 0;
  idHashIndex::Free(&this->cvarHash);
  v3 = this->cvars.list;
  if ( v3 )
    Memory::Free(v3);
  this->cvars.list = 0;
  this->cvars.num = 0;
  this->cvars.size = 0;
  this->__vftable = (idCVarSystemLocal_vtbl *)&idCVarSystem::`vftable';
}

// FUNC: public: class idInternalCVar * __thiscall idCVarSystemLocal::FindInternal(char const *)const
idInternalCVar *__thiscall idCVarSystemLocal::FindInternal(idCVarSystemLocal *this, const char *name)
{
  unsigned __int8 v4; // al
  int v5; // ebx
  const char *i; // ecx
  int v7; // edx
  int v8; // esi

  if ( !name )
    return 0;
  v4 = *name;
  v5 = 0;
  for ( i = name; v4; v5 += v7 )
  {
    if ( idStr::lowerCaseCharacter[v4] )
      v4 = idStr::lowerCaseCharacter[v4];
    v7 = (char)v4 * (_DWORD)&i[119 - (_DWORD)name];
    v4 = *++i;
  }
  v8 = this->cvarHash.hash[v5 & this->cvarHash.hashMask & this->cvarHash.lookupMask];
  if ( v8 == -1 )
    return 0;
  while ( idStr::Icmp(this->cvars.list[v8]->nameString.data, name) )
  {
    v8 = this->cvarHash.indexChain[v8 & this->cvarHash.lookupMask];
    if ( v8 == -1 )
      return 0;
  }
  return this->cvars.list[v8];
}

// FUNC: public: __thiscall idCVarSystemLocal::idCVarSystemLocal(void)
void __thiscall idCVarSystemLocal::idCVarSystemLocal(idCVarSystemLocal *this)
{
  this->__vftable = (idCVarSystemLocal_vtbl *)&idCVarSystemLocal::`vftable';
  this->cvars.granularity = 16;
  this->cvars.list = 0;
  this->cvars.num = 0;
  this->cvars.size = 0;
  idHashIndex::Init(&this->cvarHash, 1024, 1024);
  this->cvarHelps.list = 0;
  this->cvarHelps.num = 0;
  this->cvarHelps.size = 0;
  this->cvarHelps.granularity = 16;
  this->initialized = 0;
  this->modifiedFlags = 0;
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::Shutdown(void)
void __thiscall idCVarSystemLocal::Shutdown(idCVarSystemLocal *this)
{
  int i; // edi
  idInternalCVar *v3; // ecx
  int j; // edi

  for ( i = 0; i < this->cvars.num; ++i )
  {
    v3 = this->cvars.list[i];
    if ( v3 )
      ((void (__thiscall *)(idInternalCVar *, int))v3->~idInternalCVar)(v3, 1);
    this->cvars.list[i] = 0;
  }
  if ( this->cvars.list )
    Memory::Free(this->cvars.list);
  this->cvars.list = 0;
  this->cvars.num = 0;
  this->cvars.size = 0;
  idHashIndex::Free(&this->cvarHash);
  idDict::Clear(&idCVarSystemLocal::moveCVarsToDict);
  this->initialized = 0;
  for ( j = 0; j < this->cvarHelps.num; ++j )
  {
    Memory::Free(this->cvarHelps.list[j]);
    this->cvarHelps.list[j] = 0;
  }
  if ( this->cvarHelps.list )
    Memory::Free(this->cvarHelps.list);
  this->cvarHelps.list = 0;
  this->cvarHelps.num = 0;
  this->cvarHelps.size = 0;
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::Register(class idCVarHelp const *)
void __thiscall idCVarSystemLocal::Register(idCVarSystemLocal *this, const idCVarHelp *cvarHelp)
{
  idCVarHelp *v3; // eax
  int granularity; // eax
  bool v5; // cc
  int i; // eax
  int num; // ebx
  int size; // eax
  int v9; // ecx
  idCVarHelp **list; // edi
  int j; // eax
  idCVarHelp *cvarHelpa; // [esp+10h] [ebp+4h]

  v3 = (idCVarHelp *)Memory::Allocate(0x18u);
  if ( v3 )
  {
    v3->cvarName = cvarHelp->cvarName;
    v3->friendlyName = cvarHelp->friendlyName;
    v3->choices = cvarHelp->choices;
    v3->values = cvarHelp->values;
    v3->category = cvarHelp->category;
    v3->next = 0;
    cvarHelpa = v3;
  }
  else
  {
    cvarHelpa = 0;
  }
  if ( !this->cvarHelps.list )
  {
    granularity = this->cvarHelps.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->cvarHelps.size )
      {
        v5 = granularity < this->cvarHelps.num;
        this->cvarHelps.size = granularity;
        if ( v5 )
          this->cvarHelps.num = granularity;
        this->cvarHelps.list = (idCVarHelp **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->cvarHelps.num; ++i )
          this->cvarHelps.list[i] = *(idCVarHelp **)(4 * i);
      }
    }
    else
    {
      this->cvarHelps.list = 0;
      this->cvarHelps.num = 0;
      this->cvarHelps.size = 0;
    }
  }
  num = this->cvarHelps.num;
  size = this->cvarHelps.size;
  if ( num == size )
  {
    if ( !this->cvarHelps.granularity )
      this->cvarHelps.granularity = 16;
    v9 = size + this->cvarHelps.granularity - (size + this->cvarHelps.granularity) % this->cvarHelps.granularity;
    if ( v9 > 0 )
    {
      if ( v9 != this->cvarHelps.size )
      {
        list = this->cvarHelps.list;
        this->cvarHelps.size = v9;
        if ( v9 < num )
          this->cvarHelps.num = v9;
        this->cvarHelps.list = (idCVarHelp **)Memory::Allocate(4 * v9);
        for ( j = 0; j < this->cvarHelps.num; ++j )
          this->cvarHelps.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->cvarHelps.list )
        Memory::Free(this->cvarHelps.list);
      this->cvarHelps.list = 0;
      this->cvarHelps.num = 0;
      this->cvarHelps.size = 0;
    }
  }
  this->cvarHelps.list[this->cvarHelps.num++] = cvarHelpa;
}

// FUNC: public: virtual class idCVar * __thiscall idCVarSystemLocal::Find(char const *)
// attributes: thunk
idInternalCVar *__thiscall idCVarSystemLocal::Find(idCVarSystemLocal *this, const char *name)
{
  return idCVarSystemLocal::FindInternal(this, name);
}

// FUNC: public: virtual char const * __thiscall idCVarSystemLocal::GetCVarString(char const *)const
const char *__thiscall idCVarSystemLocal::GetCVarString(idCVarSystemLocal *this, const char *name)
{
  idInternalCVar *Internal; // eax

  Internal = idCVarSystemLocal::FindInternal(this, name);
  if ( Internal )
    return Internal->internalVar->value;
  else
    return &entityFilter;
}

// FUNC: public: virtual bool __thiscall idCVarSystemLocal::GetCVarBool(char const *)const
bool __thiscall idCVarSystemLocal::GetCVarBool(idCVarSystemLocal *this, const char *name)
{
  idInternalCVar *Internal; // eax

  Internal = idCVarSystemLocal::FindInternal(this, name);
  return Internal && Internal->internalVar->integerValue != 0;
}

// FUNC: public: virtual int __thiscall idCVarSystemLocal::GetCVarInteger(char const *)const
int __thiscall idCVarSystemLocal::GetCVarInteger(idCVarSystemLocal *this, const char *name)
{
  idInternalCVar *Internal; // eax

  Internal = idCVarSystemLocal::FindInternal(this, name);
  if ( Internal )
    return Internal->internalVar->integerValue;
  else
    return 0;
}

// FUNC: public: virtual float __thiscall idCVarSystemLocal::GetCVarFloat(char const *)const
double __thiscall idCVarSystemLocal::GetCVarFloat(idCVarSystemLocal *this, const char *name)
{
  idInternalCVar *Internal; // eax

  Internal = idCVarSystemLocal::FindInternal(this, name);
  if ( Internal )
    return Internal->internalVar->floatValue;
  else
    return 0.0;
}

// FUNC: public: virtual bool __thiscall idCVarSystemLocal::Command(class idCmdArgs const &)
char __thiscall idCVarSystemLocal::Command(idCVarSystemLocal *this, idCmdArgs *args)
{
  const char *v2; // eax
  idInternalCVar *Internal; // esi
  const char *description; // ecx
  int v6; // eax
  char *v7; // eax

  if ( args->argc <= 0 )
    v2 = &entityFilter;
  else
    v2 = args->argv[0];
  Internal = idCVarSystemLocal::FindInternal(this, v2);
  if ( !Internal )
    return 0;
  if ( args->argc == 1 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "\"%s\" is:\"%s\"^7 default:\"%s\"\n",
      Internal->nameString.data,
      Internal->valueString.data,
      Internal->resetString.data);
    description = Internal->internalVar->description;
    v6 = 0;
    if ( *description )
    {
      do
        ++v6;
      while ( description[v6] );
      if ( v6 > 0 )
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "^7%s\n",
          Internal->internalVar->description);
        return 1;
      }
    }
  }
  else
  {
    v7 = (char *)idCmdArgs::Args(args, 1, -1, 0);
    idInternalCVar::Set(Internal, v7, 0, 0);
  }
  return 1;
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::ResetFlaggedVariables(int)
void __thiscall idCVarSystemLocal::ResetFlaggedVariables(idCVarSystemLocal *this, int flags)
{
  int i; // ebx
  idInternalCVar *v4; // esi
  char *data; // edi

  for ( i = 0; i < this->cvars.num; ++i )
  {
    v4 = this->cvars.list[i];
    if ( (flags & v4->internalVar->flags) != 0 )
    {
      if ( session )
        session->IsMultiplayer(session);
      data = v4->resetString.data;
      if ( idStr::Icmp(v4->valueString.data, data) )
      {
        idStr::operator=(&v4->valueString, data);
        v4->value = v4->valueString.data;
        idInternalCVar::UpdateValue(v4);
        BYTE2(v4->internalVar->flags) |= 4u;
        cvarSystem->SetModifiedFlags(cvarSystem, v4->flags);
      }
    }
  }
}

// FUNC: public: virtual class idStr __thiscall idCVarSystemLocal::WriteFlaggedVariables(int)const
idStr *__thiscall idCVarSystemLocal::WriteFlaggedVariables(idCVarSystemLocal *this, idStr *result, int flags)
{
  int v3; // ebp
  idCVarSystemLocal *v4; // edx
  int v5; // eax
  char v6; // cl
  bool v7; // cc
  idInternalCVar *v8; // esi
  int v9; // eax
  char v10; // cl
  int v11; // eax
  char v12; // cl
  const idStr *v13; // eax
  const idStr *v14; // eax
  idStr *v15; // esi
  int v16; // edi
  int v17; // eax
  char v18; // cl
  char *v19; // edx
  int len; // edi
  char *data; // ecx
  char *v22; // edx
  char v23; // al
  const char *value; // [esp-1Ch] [ebp-104h]
  const char *name; // [esp-4h] [ebp-ECh]
  int i; // [esp+10h] [ebp-D8h]
  idStr infoString; // [esp+1Ch] [ebp-CCh] BYREF
  idStr a; // [esp+3Ch] [ebp-ACh] BYREF
  idStr b; // [esp+5Ch] [ebp-8Ch] BYREF
  idStr v32; // [esp+7Ch] [ebp-6Ch] BYREF
  idStr v33; // [esp+9Ch] [ebp-4Ch] BYREF
  idStr v34; // [esp+BCh] [ebp-2Ch] BYREF
  int v35; // [esp+E4h] [ebp-4h]

  v3 = 0;
  v4 = this;
  infoString.data = infoString.baseBuffer;
  infoString.alloced = 20;
  infoString.baseBuffer[0] = 0;
  v5 = 0;
  do
  {
    v6 = *(&entityFilter + v5);
    infoString.baseBuffer[v5++] = v6;
  }
  while ( v6 );
  infoString.len = 0;
  v7 = v4->cvars.num <= 0;
  v35 = 1;
  i = 0;
  if ( !v7 )
  {
    do
    {
      v8 = v4->cvars.list[v3];
      if ( (flags & v8->internalVar->flags) != 0 )
      {
        b.alloced = 20;
        b.data = b.baseBuffer;
        b.baseBuffer[0] = 0;
        v9 = 0;
        do
        {
          v10 = Source[v9];
          b.baseBuffer[v9++] = v10;
        }
        while ( v10 );
        b.len = 1;
        a.data = a.baseBuffer;
        a.alloced = 20;
        a.baseBuffer[0] = 0;
        v11 = 0;
        do
        {
          v12 = Source[v11];
          a.baseBuffer[v11++] = v12;
        }
        while ( v12 );
        a.len = 1;
        name = v8->internalVar->idCVar::name;
        LOBYTE(v35) = 3;
        v13 = operator+(&v34, &a, name);
        LOBYTE(v35) = 4;
        v14 = operator+(&v33, v13, &b);
        value = v8->internalVar->value;
        LOBYTE(v35) = 5;
        v15 = operator+(&v32, v14, value);
        v16 = v15->len + infoString.len;
        LOBYTE(v35) = 6;
        if ( v16 + 1 > infoString.alloced )
          idStr::ReAllocate(&infoString, v16 + 1, 1);
        v17 = 0;
        if ( v15->len > 0 )
        {
          do
          {
            v18 = v15->data[v17];
            v19 = &infoString.data[v17++];
            v19[infoString.len] = v18;
          }
          while ( v17 < v15->len );
          v3 = i;
        }
        infoString.len = v16;
        infoString.data[v16] = 0;
        LOBYTE(v35) = 5;
        idStr::FreeData(&v32);
        LOBYTE(v35) = 4;
        idStr::FreeData(&v33);
        LOBYTE(v35) = 3;
        idStr::FreeData(&v34);
        LOBYTE(v35) = 2;
        idStr::FreeData(&a);
        LOBYTE(v35) = 1;
        idStr::FreeData(&b);
        v4 = this;
      }
      i = ++v3;
    }
    while ( v3 < v4->cvars.num );
  }
  result->alloced = 20;
  result->data = result->baseBuffer;
  result->len = 0;
  result->baseBuffer[0] = 0;
  len = infoString.len;
  if ( infoString.len + 1 > result->alloced )
    idStr::ReAllocate(result, infoString.len + 1, 1);
  data = infoString.data;
  v22 = result->data;
  do
  {
    v23 = *data;
    *v22++ = *data++;
  }
  while ( v23 );
  result->len = len;
  LOBYTE(v35) = 0;
  idStr::FreeData(&infoString);
  return result;
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::SetCVarsFromDict(class idDict const &)
void __thiscall idCVarSystemLocal::SetCVarsFromDict(idCVarSystemLocal *this, const idDict *dict)
{
  int num; // eax
  int i; // esi
  idKeyValue *v5; // edi
  idInternalCVar *Internal; // eax

  num = dict->args.num;
  for ( i = 0; i < dict->args.num; ++i )
  {
    if ( i < 0 || i >= num )
      v5 = 0;
    else
      v5 = &dict->args.list[i];
    Internal = idCVarSystemLocal::FindInternal(this, v5->key->data);
    if ( Internal )
      Internal->InternalServerSetString(Internal, v5->value->data);
    num = dict->args.num;
  }
}

// FUNC: private: static void __cdecl idCVarSystemLocal::Toggle_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::Toggle_f(const idCmdArgs *args)
{
  int argc; // edi
  const char *v3; // eax
  idInternalCVar *Internal; // eax
  const char *v5; // eax
  idCVar *internalVar; // eax
  int v7; // esi
  char **v8; // ebp
  const char *v9; // eax
  const char *v10; // edx
  const char *v11; // ecx
  const char *v12; // esi
  char *v13; // eax
  long double v14; // st7
  const char *v15; // ecx
  int v16; // esi
  char *data; // edx
  char *v18; // ecx
  char v19; // al
  idInternalCVar *cvar; // [esp+14h] [ebp-70h]
  idStr v21; // [esp+18h] [ebp-6Ch] BYREF
  char dest[64]; // [esp+38h] [ebp-4Ch] BYREF
  int v23; // [esp+80h] [ebp-4h]
  const char *argsa; // [esp+88h] [ebp+4h]
  float argsb; // [esp+88h] [ebp+4h]
  float argsc; // [esp+88h] [ebp+4h]

  argc = args->argc;
  if ( args->argc >= 2 )
  {
    if ( argc <= 1 )
      v3 = &entityFilter;
    else
      v3 = args->argv[1];
    Internal = idCVarSystemLocal::FindInternal(&localCVarSystem, v3);
    cvar = Internal;
    if ( Internal )
    {
      internalVar = Internal->internalVar;
      if ( argc <= 3 )
      {
        argsb = internalVar->floatValue;
        if ( argc == 3 )
        {
          if ( args->argc <= 2 )
            v14 = atof(&entityFilter);
          else
            v14 = atof(args->argv[2]);
        }
        else
        {
          v14 = 1.0;
        }
        if ( argsb == 0.0 )
          argsc = v14;
        else
          argsc = 0.0;
        if ( args->argc <= 1 )
          v15 = &entityFilter;
        else
          v15 = args->argv[1];
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "set %s = %f\n",
          v15,
          argsc);
        v21.len = 0;
        v21.alloced = 20;
        v21.data = v21.baseBuffer;
        v21.baseBuffer[0] = 0;
        v16 = idStr::snPrintf(dest, 64, "%f", argsc);
        if ( v16 > 0 )
        {
          while ( v21.baseBuffer[v16 + 19] == 48 )
          {
            dest[--v16] = 0;
            if ( v16 <= 0 )
              goto LABEL_51;
          }
          do
          {
            if ( v21.baseBuffer[v16 + 19] != 46 )
              break;
            dest[--v16] = 0;
          }
          while ( v16 > 0 );
        }
LABEL_51:
        if ( v16 + 1 > v21.alloced )
          idStr::ReAllocate(&v21, v16 + 1, 1);
        data = v21.data;
        v18 = dest;
        do
        {
          v19 = *v18;
          *data++ = *v18++;
        }
        while ( v19 );
        v21.len = v16;
        v23 = 0;
        idInternalCVar::Set(cvar, v21.data, 0, 0);
        v23 = -1;
        idStr::FreeData(&v21);
      }
      else
      {
        v7 = 2;
        argsa = internalVar->value;
        v8 = &args->argv[2];
        while ( 1 )
        {
          v9 = v7 < 0 || v7 >= args->argc ? &entityFilter : *v8;
          ++v7;
          if ( !idStr::Icmp(argsa, v9) )
            break;
          ++v8;
          if ( v7 >= argc )
          {
            v7 = 2;
            goto LABEL_23;
          }
        }
        if ( v7 < argc )
        {
          if ( v7 < 0 )
            goto LABEL_25;
        }
        else
        {
          v7 = 2;
        }
LABEL_23:
        if ( v7 < args->argc )
        {
          v10 = args->argv[v7];
          goto LABEL_26;
        }
LABEL_25:
        v10 = &entityFilter;
LABEL_26:
        if ( args->argc <= 1 )
          v11 = &entityFilter;
        else
          v11 = args->argv[1];
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "set %s = %s\n",
          v11,
          v10);
        if ( v7 < 0 || v7 >= args->argc )
          v12 = &entityFilter;
        else
          v12 = args->argv[v7];
        v13 = va("%s", v12);
        idInternalCVar::Set(cvar, v13, 0, 0);
      }
    }
    else
    {
      if ( args->argc <= 1 )
        v5 = &entityFilter;
      else
        v5 = args->argv[1];
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "Toggle_f: cvar \"%s\" not found",
        v5);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage:\n"
      "   toggle <variable>  - toggles between 0 and 1\n"
      "   toggle <variable> <value> - toggles between 0 and <value>\n"
      "   toggle <variable> [string 1] [string 2]...[string n] - cycles through all strings\n");
  }
}

// FUNC: private: static void __cdecl idCVarSystemLocal::Reset_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::Reset_f(const idCmdArgs *args)
{
  idInternalCVar *Internal; // eax

  if ( args->argc == 2 )
  {
    Internal = idCVarSystemLocal::FindInternal(&localCVarSystem, args->argv[1]);
    if ( Internal )
      idInternalCVar::Reset(Internal);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: reset <variable>\n");
  }
}

// FUNC: private: static void __cdecl idCVarSystemLocal::Restart_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::Restart_f()
{
  int i; // ebx
  idInternalCVar *v1; // edi
  int flags; // eax
  unsigned __int8 *data; // eax
  unsigned __int8 v4; // dl
  int v5; // esi
  int v6; // ebp
  int v7; // ecx
  int v8; // esi
  int j; // eax
  int v10; // ecx
  int v11; // eax
  int *indexChain; // edx
  int v13; // ecx
  int *hash; // edx
  int v15; // eax
  int k; // esi
  int v17; // ecx
  int *v18; // eax
  int m; // ecx
  int v20; // edx
  int n; // ecx

  for ( i = 0; i < localCVarSystem.cvars.num; ++i )
  {
    v1 = localCVarSystem.cvars.list[i];
    flags = v1->flags;
    if ( (flags & 0x18000) == 0 )
    {
      if ( (flags & 0x1000) != 0 )
      {
        idInternalCVar::Reset(localCVarSystem.cvars.list[i]);
      }
      else
      {
        data = (unsigned __int8 *)v1->nameString.data;
        v4 = *data;
        v5 = 0;
        if ( *data )
        {
          v6 = 119 - (_DWORD)data;
          do
          {
            if ( idStr::lowerCaseCharacter[v4] )
              v4 = idStr::lowerCaseCharacter[v4];
            v7 = (char)v4 * (_DWORD)&data[v6];
            v4 = *++data;
            v5 += v7;
          }
          while ( v4 );
        }
        v8 = v5 & localCVarSystem.cvarHash.hashMask;
        ((void (__thiscall *)(idInternalCVar *, int))v1->~idInternalCVar)(v1, 1);
        if ( i >= 0 && i < localCVarSystem.cvars.num )
        {
          --localCVarSystem.cvars.num;
          for ( j = i; j < localCVarSystem.cvars.num; ++j )
            localCVarSystem.cvars.list[j] = localCVarSystem.cvars.list[j + 1];
        }
        v10 = v8 & localCVarSystem.cvarHash.hashMask;
        if ( localCVarSystem.cvarHash.hash != idHashIndex::INVALID_INDEX )
        {
          v11 = localCVarSystem.cvarHash.hash[v10];
          if ( v11 == i )
          {
            localCVarSystem.cvarHash.hash[v10] = localCVarSystem.cvarHash.indexChain[i];
          }
          else if ( v11 != -1 )
          {
            indexChain = localCVarSystem.cvarHash.indexChain;
            while ( 1 )
            {
              v13 = localCVarSystem.cvarHash.indexChain[v11];
              if ( v13 == i )
                break;
              v11 = localCVarSystem.cvarHash.indexChain[v11];
              if ( v13 == -1 )
                goto LABEL_23;
            }
            localCVarSystem.cvarHash.indexChain[v11] = localCVarSystem.cvarHash.indexChain[i];
          }
          indexChain = localCVarSystem.cvarHash.indexChain;
LABEL_23:
          indexChain[i] = -1;
          hash = localCVarSystem.cvarHash.hash;
          if ( localCVarSystem.cvarHash.hash != idHashIndex::INVALID_INDEX )
          {
            v15 = 0;
            for ( k = i; v15 < localCVarSystem.cvarHash.hashSize; ++v15 )
            {
              v17 = hash[v15];
              if ( v17 >= i )
              {
                if ( v17 > k )
                  k = hash[v15];
                --hash[v15];
                hash = localCVarSystem.cvarHash.hash;
              }
            }
            v18 = localCVarSystem.cvarHash.indexChain;
            for ( m = 0; m < localCVarSystem.cvarHash.indexSize; ++m )
            {
              v20 = v18[m];
              if ( v20 >= i )
              {
                if ( v20 > k )
                  k = v18[m];
                --v18[m];
                v18 = localCVarSystem.cvarHash.indexChain;
              }
            }
            for ( n = i; n < k; ++n )
            {
              v18[n] = v18[n + 1];
              v18 = localCVarSystem.cvarHash.indexChain;
            }
            v18[k] = -1;
          }
        }
        --i;
      }
    }
  }
}

// FUNC: public: __thiscall idInternalCVar::idInternalCVar(char const *,char const *,int)
void __thiscall idInternalCVar::idInternalCVar(idInternalCVar *this, char *newName, char *newValue, int newFlags)
{
  idStr *p_nameString; // ecx
  int v6; // eax
  int flags; // eax

  p_nameString = &this->nameString;
  this->__vftable = (idInternalCVar_vtbl *)&idInternalCVar::`vftable';
  p_nameString->len = 0;
  p_nameString->alloced = 20;
  p_nameString->data = p_nameString->baseBuffer;
  p_nameString->baseBuffer[0] = 0;
  this->resetString.len = 0;
  this->resetString.alloced = 20;
  this->resetString.data = this->resetString.baseBuffer;
  this->resetString.baseBuffer[0] = 0;
  this->valueString.len = 0;
  this->valueString.alloced = 20;
  this->valueString.data = this->valueString.baseBuffer;
  this->valueString.baseBuffer[0] = 0;
  this->descriptionString.len = 0;
  this->descriptionString.alloced = 20;
  this->descriptionString.data = this->descriptionString.baseBuffer;
  this->descriptionString.baseBuffer[0] = 0;
  idStr::operator=(p_nameString, newName);
  this->name = this->nameString.data;
  idStr::operator=(&this->valueString, newValue);
  this->value = this->valueString.data;
  idStr::operator=(&this->resetString, newValue);
  idStr::operator=(&this->descriptionString, (char *)&entityFilter);
  v6 = newFlags;
  BYTE1(v6) = BYTE1(newFlags) & 0xEF;
  this->description = this->descriptionString.data;
  this->valueMin = 1.0;
  this->valueMax = -1.0;
  this->flags = v6 | 0x40000;
  this->valueStrings = 0;
  this->valueCompletion = 0;
  idInternalCVar::UpdateValue(this);
  flags = this->flags;
  if ( (flags & 0x3CE00) != 0 )
  {
    BYTE1(flags) &= ~0x20u;
    this->flags = flags;
  }
  else if ( idStr::Icmpn(this->nameString.data, "ua_", 3) )
  {
    BYTE1(this->flags) |= 0x20u;
  }
  else
  {
    BYTE1(this->flags) &= ~0x20u;
  }
  this->internalVar = this;
}

// FUNC: public: __thiscall idInternalCVar::idInternalCVar(class idCVar const *)
void __thiscall idInternalCVar::idInternalCVar(idInternalCVar *this, const idCVar *cvar)
{
  idStr *p_nameString; // ecx
  int flags; // eax

  p_nameString = &this->nameString;
  this->__vftable = (idInternalCVar_vtbl *)&idInternalCVar::`vftable';
  p_nameString->len = 0;
  p_nameString->alloced = 20;
  p_nameString->data = p_nameString->baseBuffer;
  p_nameString->baseBuffer[0] = 0;
  this->resetString.len = 0;
  this->resetString.alloced = 20;
  this->resetString.data = this->resetString.baseBuffer;
  this->resetString.baseBuffer[0] = 0;
  this->valueString.len = 0;
  this->valueString.alloced = 20;
  this->valueString.data = this->valueString.baseBuffer;
  this->valueString.baseBuffer[0] = 0;
  this->descriptionString.len = 0;
  this->descriptionString.alloced = 20;
  this->descriptionString.data = this->descriptionString.baseBuffer;
  this->descriptionString.baseBuffer[0] = 0;
  idStr::operator=(p_nameString, (char *)cvar->internalVar->name);
  this->name = this->nameString.data;
  idStr::operator=(&this->valueString, (char *)cvar->internalVar->value);
  this->value = this->valueString.data;
  idStr::operator=(&this->resetString, (char *)cvar->internalVar->value);
  idStr::operator=(&this->descriptionString, (char *)cvar->internalVar->description);
  this->description = this->descriptionString.data;
  this->flags = cvar->internalVar->flags | 0x40000;
  this->valueMin = cvar->internalVar->valueMin;
  this->valueMax = cvar->internalVar->valueMax;
  this->valueStrings = idInternalCVar::CopyValueStrings(this, cvar->valueStrings);
  this->valueCompletion = cvar->valueCompletion;
  idInternalCVar::UpdateValue(this);
  flags = this->flags;
  if ( (flags & 0x3CE00) != 0 )
  {
    BYTE1(flags) &= ~0x20u;
    this->flags = flags;
  }
  else if ( idStr::Icmpn(this->nameString.data, "ua_", 3) )
  {
    BYTE1(this->flags) |= 0x20u;
  }
  else
  {
    BYTE1(this->flags) &= ~0x20u;
  }
  this->internalVar = this;
}

// FUNC: public: void __thiscall idInternalCVar::Update(class idCVar const *)
void __thiscall idInternalCVar::Update(idInternalCVar *this, const idCVar *cvar)
{
  idCVar *internalVar; // eax
  idCVar *v4; // ecx
  int flags; // eax
  idCVar *v6; // ecx
  const char **valueStrings; // [esp-4h] [ebp-Ch]

  internalVar = cvar->internalVar;
  if ( (internalVar->flags & 0x1000) != 0 )
  {
    if ( (this->flags & 0x1000) != 0 )
    {
      if ( idStr::Icmp(this->resetString.data, internalVar->value) )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "CVar '%s' declared multiple times with different initial value",
          this->nameString.data);
      if ( ((LOBYTE(this->flags) ^ LOBYTE(cvar->internalVar->flags)) & 7) != 0 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "CVar '%s' declared multiple times with different type",
          this->nameString.data);
      v4 = cvar->internalVar;
      if ( this->valueMin != v4->valueMin || this->valueMax != v4->valueMax )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "CVar '%s' declared multiple times with different minimum/maximum",
          this->nameString.data);
    }
    idStr::operator=(&this->resetString, (char *)cvar->internalVar->value);
    idStr::operator=(&this->descriptionString, (char *)cvar->internalVar->description);
    this->description = this->descriptionString.data;
    this->valueMin = cvar->internalVar->valueMin;
    valueStrings = this->valueStrings;
    this->valueMax = cvar->internalVar->valueMax;
    Mem_Free(valueStrings);
    this->valueStrings = idInternalCVar::CopyValueStrings(this, cvar->valueStrings);
    this->valueCompletion = cvar->valueCompletion;
    idInternalCVar::UpdateValue(this);
    cvarSystem->SetModifiedFlags(cvarSystem, cvar->internalVar->flags);
  }
  this->flags |= cvar->internalVar->flags;
  flags = this->flags;
  if ( (flags & 0x3CE00) != 0 )
  {
    BYTE1(flags) &= ~0x20u;
    this->flags = flags;
  }
  else if ( idStr::Icmpn(this->nameString.data, "ua_", 3) )
  {
    BYTE1(this->flags) |= 0x20u;
  }
  else
  {
    BYTE1(this->flags) &= ~0x20u;
  }
  if ( this->resetString.len )
  {
    v6 = cvar->internalVar;
    if ( *v6->value )
    {
      if ( idStr::Cmp(this->resetString.data, v6->value) )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "cvar \"%s\" given initial values: \"%s\" and \"%s\"\n",
          this->nameString.data,
          this->resetString.data,
          cvar->internalVar->value);
    }
  }
  else
  {
    idStr::operator=(&this->resetString, (char *)cvar->internalVar->value);
  }
}

// FUNC: public: void __thiscall idCVarSystemLocal::SetInternal(char const *,char const *,int)
void __thiscall idCVarSystemLocal::SetInternal(idCVarSystemLocal *this, char *name, char *value, int flags)
{
  idInternalCVar *Internal; // eax
  idInternalCVar *v6; // edi
  int v7; // edx
  int v8; // eax
  idInternalCVar *v9; // eax
  idInternalCVar *v10; // eax
  unsigned __int8 *data; // eax
  unsigned __int8 v12; // cl
  int v13; // edi
  idHashIndex *p_cvarHash; // ebx
  int v15; // ebp
  int v16; // edx
  int granularity; // eax
  bool v18; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v22; // ecx
  idInternalCVar **list; // edi
  int j; // eax
  int v25; // esi
  int indexSize; // eax
  int v27; // eax
  int valuea; // [esp+20h] [ebp+8h]
  idInternalCVar *hash; // [esp+24h] [ebp+Ch]

  Internal = idCVarSystemLocal::FindInternal(this, name);
  v6 = Internal;
  if ( Internal )
  {
    Internal->InternalSetString(Internal, value);
    v7 = flags;
    BYTE1(v7) = BYTE1(flags) & 0xEF;
    v6->flags |= v7;
    v8 = v6->flags;
    if ( (v8 & 0x3CE00) != 0 )
    {
      BYTE1(v8) &= ~0x20u;
      v6->flags = v8;
    }
    else if ( idStr::Icmpn(v6->nameString.data, "ua_", 3) )
    {
      BYTE1(v6->flags) |= 0x20u;
    }
    else
    {
      BYTE1(v6->flags) &= ~0x20u;
    }
  }
  else
  {
    v9 = (idInternalCVar *)Memory::Allocate(0xB4u);
    if ( v9 )
    {
      idInternalCVar::idInternalCVar(v9, name, value, flags);
      hash = v10;
    }
    else
    {
      hash = 0;
    }
    data = (unsigned __int8 *)hash->nameString.data;
    v12 = *data;
    v13 = 0;
    p_cvarHash = &this->cvarHash;
    if ( *data )
    {
      v15 = 119 - (_DWORD)data;
      do
      {
        if ( idStr::lowerCaseCharacter[v12] )
          v12 = idStr::lowerCaseCharacter[v12];
        v16 = (char)v12 * (_DWORD)&data[v15];
        v12 = *++data;
        v13 += v16;
      }
      while ( v12 );
    }
    valuea = v13 & this->cvarHash.hashMask;
    if ( !this->cvars.list )
    {
      granularity = this->cvars.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->cvars.size )
        {
          v18 = granularity < this->cvars.num;
          this->cvars.size = granularity;
          if ( v18 )
            this->cvars.num = granularity;
          this->cvars.list = (idInternalCVar **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->cvars.num; ++i )
            this->cvars.list[i] = *(idInternalCVar **)(4 * i);
        }
      }
      else
      {
        this->cvars.list = 0;
        this->cvars.num = 0;
        this->cvars.size = 0;
      }
    }
    num = this->cvars.num;
    size = this->cvars.size;
    if ( num == size )
    {
      if ( !this->cvars.granularity )
        this->cvars.granularity = 16;
      v22 = size + this->cvars.granularity - (size + this->cvars.granularity) % this->cvars.granularity;
      if ( v22 > 0 )
      {
        if ( v22 != this->cvars.size )
        {
          list = this->cvars.list;
          this->cvars.size = v22;
          if ( v22 < num )
            this->cvars.num = v22;
          this->cvars.list = (idInternalCVar **)Memory::Allocate(4 * v22);
          for ( j = 0; j < this->cvars.num; ++j )
            this->cvars.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->cvars.list )
          Memory::Free(this->cvars.list);
        this->cvars.list = 0;
        this->cvars.num = 0;
        this->cvars.size = 0;
      }
    }
    this->cvars.list[this->cvars.num++] = hash;
    v25 = this->cvars.num - 1;
    if ( p_cvarHash->hash == idHashIndex::INVALID_INDEX )
    {
      indexSize = p_cvarHash->indexSize;
      if ( v25 >= indexSize )
        indexSize = v25 + 1;
      idHashIndex::Allocate(p_cvarHash, p_cvarHash->hashSize, indexSize);
    }
    else if ( v25 >= p_cvarHash->indexSize )
    {
      idHashIndex::ResizeIndex(p_cvarHash, v25 + 1);
    }
    v27 = valuea & p_cvarHash->hashMask;
    p_cvarHash->indexChain[v25] = p_cvarHash->hash[v27];
    p_cvarHash->hash[v27] = v25;
  }
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::Register(class idCVar *)
void __thiscall idCVarSystemLocal::Register(idCVarSystemLocal *this, idCVar *cvar)
{
  idInternalCVar *Internal; // eax
  idCVar *v4; // edi
  idInternalCVar *v5; // eax
  idInternalCVar *v6; // eax
  unsigned __int8 *data; // eax
  unsigned __int8 v8; // cl
  int v9; // edi
  idHashIndex *p_cvarHash; // ebx
  int v11; // ebp
  int v12; // edx
  int granularity; // eax
  bool v14; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v18; // ecx
  idInternalCVar **list; // edi
  int j; // eax
  int v21; // esi
  int indexSize; // eax
  int v23; // eax
  idInternalCVar *v24; // [esp+0h] [ebp-14h]
  int hash; // [esp+4h] [ebp-10h]

  cvar->internalVar = cvar;
  Internal = idCVarSystemLocal::FindInternal(this, cvar->name);
  v4 = Internal;
  if ( Internal )
  {
    idInternalCVar::Update(Internal, cvar);
    cvar->internalVar = v4;
  }
  else
  {
    v5 = (idInternalCVar *)Memory::Allocate(0xB4u);
    if ( v5 )
    {
      idInternalCVar::idInternalCVar(v5, cvar);
      v24 = v6;
    }
    else
    {
      v24 = 0;
    }
    data = (unsigned __int8 *)v24->nameString.data;
    v8 = *data;
    v9 = 0;
    p_cvarHash = &this->cvarHash;
    if ( *data )
    {
      v11 = 119 - (_DWORD)data;
      do
      {
        if ( idStr::lowerCaseCharacter[v8] )
          v8 = idStr::lowerCaseCharacter[v8];
        v12 = (char)v8 * (_DWORD)&data[v11];
        v8 = *++data;
        v9 += v12;
      }
      while ( v8 );
    }
    hash = v9 & this->cvarHash.hashMask;
    if ( !this->cvars.list )
    {
      granularity = this->cvars.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->cvars.size )
        {
          v14 = granularity < this->cvars.num;
          this->cvars.size = granularity;
          if ( v14 )
            this->cvars.num = granularity;
          this->cvars.list = (idInternalCVar **)Memory::Allocate(4 * granularity);
          for ( i = 0; i < this->cvars.num; ++i )
            this->cvars.list[i] = *(idInternalCVar **)(4 * i);
        }
      }
      else
      {
        this->cvars.list = 0;
        this->cvars.num = 0;
        this->cvars.size = 0;
      }
    }
    num = this->cvars.num;
    size = this->cvars.size;
    if ( num == size )
    {
      if ( !this->cvars.granularity )
        this->cvars.granularity = 16;
      v18 = size + this->cvars.granularity - (size + this->cvars.granularity) % this->cvars.granularity;
      if ( v18 > 0 )
      {
        if ( v18 != this->cvars.size )
        {
          list = this->cvars.list;
          this->cvars.size = v18;
          if ( v18 < num )
            this->cvars.num = v18;
          this->cvars.list = (idInternalCVar **)Memory::Allocate(4 * v18);
          for ( j = 0; j < this->cvars.num; ++j )
            this->cvars.list[j] = list[j];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->cvars.list )
          Memory::Free(this->cvars.list);
        this->cvars.list = 0;
        this->cvars.num = 0;
        this->cvars.size = 0;
      }
    }
    this->cvars.list[this->cvars.num++] = v24;
    v21 = this->cvars.num - 1;
    if ( p_cvarHash->hash == idHashIndex::INVALID_INDEX )
    {
      indexSize = p_cvarHash->indexSize;
      if ( v21 >= indexSize )
        indexSize = v21 + 1;
      idHashIndex::Allocate(p_cvarHash, p_cvarHash->hashSize, indexSize);
    }
    else if ( v21 >= p_cvarHash->indexSize )
    {
      idHashIndex::ResizeIndex(p_cvarHash, v21 + 1);
    }
    v23 = hash & p_cvarHash->hashMask;
    p_cvarHash->indexChain[v21] = p_cvarHash->hash[v23];
    p_cvarHash->hash[v23] = v21;
    cvar->internalVar = v24;
  }
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::SetCVarString(char const *,char const *,int)
// attributes: thunk
void __thiscall idCVarSystemLocal::SetCVarString(idCVarSystemLocal *this, char *name, char *value, int flags)
{
  idCVarSystemLocal::SetInternal(this, name, value, flags);
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::SetCVarBool(char const *,bool,int)
void __thiscall idCVarSystemLocal::SetCVarBool(idCVarSystemLocal *this, char *name, bool value, int flags)
{
  idStr v4; // [esp+0h] [ebp-2Ch] BYREF
  int v5; // [esp+28h] [ebp-4h]

  v4.data = v4.baseBuffer;
  v4.alloced = 20;
  v4.baseBuffer[0] = value + 48;
  v4.baseBuffer[1] = 0;
  v4.len = 1;
  v5 = 0;
  idCVarSystemLocal::SetInternal(this, name, v4.baseBuffer, flags);
  v5 = -1;
  idStr::FreeData(&v4);
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::SetCVarInteger(char const *,int,int)
void __thiscall idCVarSystemLocal::SetCVarInteger(idCVarSystemLocal *this, char *name, int value, int flags)
{
  int v5; // esi
  char *data; // edx
  char *v7; // ecx
  char v8; // al
  idStr v9; // [esp+8h] [ebp-6Ch] BYREF
  char string[64]; // [esp+28h] [ebp-4Ch] BYREF
  int v11; // [esp+70h] [ebp-4h]

  v9.len = 0;
  v9.alloced = 20;
  v9.data = v9.baseBuffer;
  v9.baseBuffer[0] = 0;
  v5 = sprintf(string, "%d", value);
  if ( v5 + 1 > 20 )
    idStr::ReAllocate(&v9, v5 + 1, 1);
  data = v9.data;
  v7 = string;
  do
  {
    v8 = *v7;
    *data++ = *v7++;
  }
  while ( v8 );
  v9.len = v5;
  v11 = 0;
  idCVarSystemLocal::SetInternal(this, name, v9.data, flags);
  v11 = -1;
  idStr::FreeData(&v9);
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::SetCVarFloat(char const *,float,int)
void __thiscall idCVarSystemLocal::SetCVarFloat(idCVarSystemLocal *this, char *name, float value, int flags)
{
  int v5; // esi
  char *data; // edx
  char *v7; // ecx
  char v8; // al
  idStr v9; // [esp+14h] [ebp-6Ch] BYREF
  char dest[64]; // [esp+34h] [ebp-4Ch] BYREF
  int v11; // [esp+7Ch] [ebp-4h]

  v9.len = 0;
  v9.alloced = 20;
  v9.data = v9.baseBuffer;
  v9.baseBuffer[0] = 0;
  v5 = idStr::snPrintf(dest, 64, "%f", value);
  if ( v5 > 0 )
  {
    while ( v9.baseBuffer[v5 + 19] == 48 )
    {
      dest[--v5] = 0;
      if ( v5 <= 0 )
        goto LABEL_7;
    }
    do
    {
      if ( v9.baseBuffer[v5 + 19] != 46 )
        break;
      dest[--v5] = 0;
    }
    while ( v5 > 0 );
  }
LABEL_7:
  if ( v5 + 1 > v9.alloced )
    idStr::ReAllocate(&v9, v5 + 1, 1);
  data = v9.data;
  v7 = dest;
  do
  {
    v8 = *v7;
    *data++ = *v7++;
  }
  while ( v8 );
  v9.len = v5;
  v11 = 0;
  idCVarSystemLocal::SetInternal(this, name, v9.data, flags);
  v11 = -1;
  idStr::FreeData(&v9);
}

// FUNC: private: static void __cdecl idCVarSystemLocal::Increment_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::Increment_f(const idCmdArgs *args)
{
  int argc; // edi
  const char *v3; // eax
  idInternalCVar *Internal; // eax
  double floatValue; // st7
  long double v6; // st7
  const char *v7; // eax
  const char *v8; // ecx
  char *v9; // esi
  float argsa; // [esp+1Ch] [ebp+4h]
  float argsb; // [esp+1Ch] [ebp+4h]

  argc = args->argc;
  if ( args->argc >= 2 )
  {
    argsa = 1.0;
    if ( argc > 2 )
      argsa = atof(args->argv[2]);
    if ( args->argc <= 1 )
      v3 = &entityFilter;
    else
      v3 = args->argv[1];
    Internal = idCVarSystemLocal::FindInternal(&localCVarSystem, v3);
    if ( Internal )
      floatValue = Internal->internalVar->floatValue;
    else
      floatValue = 0.0;
    v6 = floatValue + argsa;
    argsb = v6;
    if ( argc > 3 )
    {
      if ( args->argc <= 3 )
        v7 = &entityFilter;
      else
        v7 = args->argv[3];
      v6 = fmod(v6, atof(v7));
      argsb = v6;
    }
    if ( args->argc <= 1 )
      v8 = &entityFilter;
    else
      v8 = args->argv[1];
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "set %s = %g\n", v8, v6);
    if ( args->argc <= 1 )
      v9 = (char *)&entityFilter;
    else
      v9 = args->argv[1];
    idCVarSystemLocal::SetCVarFloat(&localCVarSystem, v9, argsb, 0);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage:\n"
      "   inc <variable>                  - adds 1 to variable\n"
      "   inc <variable> <amount>         - adds <amount>\n"
      "   inc <variable> <amount> <value> - adds <amount> then mods by <value>\n");
  }
}

// FUNC: private: static void __cdecl idCVarSystemLocal::Decrement_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::Decrement_f(const idCmdArgs *args)
{
  int argc; // edi
  const char *v3; // eax
  idInternalCVar *Internal; // eax
  double floatValue; // st7
  long double v6; // st7
  const char *v7; // eax
  const char *v8; // ecx
  char *v9; // esi
  float argsa; // [esp+1Ch] [ebp+4h]
  float argsb; // [esp+1Ch] [ebp+4h]

  argc = args->argc;
  if ( args->argc >= 2 )
  {
    argsa = 1.0;
    if ( argc > 2 )
      argsa = atof(args->argv[2]);
    if ( args->argc <= 1 )
      v3 = &entityFilter;
    else
      v3 = args->argv[1];
    Internal = idCVarSystemLocal::FindInternal(&localCVarSystem, v3);
    if ( Internal )
      floatValue = Internal->internalVar->floatValue;
    else
      floatValue = 0.0;
    v6 = floatValue - argsa;
    argsb = v6;
    if ( argc > 3 )
    {
      if ( args->argc <= 3 )
        v7 = &entityFilter;
      else
        v7 = args->argv[3];
      v6 = fmod(v6, atof(v7));
      argsb = v6;
    }
    if ( args->argc <= 1 )
      v8 = &entityFilter;
    else
      v8 = args->argv[1];
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "set %s = %g\n", v8, v6);
    if ( args->argc <= 1 )
      v9 = (char *)&entityFilter;
    else
      v9 = args->argv[1];
    idCVarSystemLocal::SetCVarFloat(&localCVarSystem, v9, argsb, 0);
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage:\n"
      "   dec <variable>                  - subtracts 1 to variable\n"
      "   dec <variable> <amount>         - subtracts <amount>\n"
      "   dec <variable> <amount> <value> - subtracts <amount> then mods by <value>\n");
  }
}

// FUNC: private: static void __cdecl idCVarSystemLocal::Set_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::Set_f(idCmdArgs *args)
{
  char *v1; // eax

  v1 = (char *)idCmdArgs::Args(args, 2, args->argc - 1, 0);
  if ( args->argc <= 1 )
    idCVarSystemLocal::SetInternal(&localCVarSystem, (char *)&entityFilter, v1, 0);
  else
    idCVarSystemLocal::SetInternal(&localCVarSystem, args->argv[1], v1, 0);
}

// FUNC: private: static void __cdecl idCVarSystemLocal::SetS_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::SetS_f(idCmdArgs *args)
{
  char *v1; // eax
  char *v2; // ecx
  const char *v3; // esi
  idInternalCVar *Internal; // eax

  v1 = (char *)idCmdArgs::Args(args, 2, args->argc - 1, 0);
  if ( args->argc <= 1 )
    v2 = (char *)&entityFilter;
  else
    v2 = args->argv[1];
  idCVarSystemLocal::SetInternal(&localCVarSystem, v2, v1, 0);
  if ( args->argc <= 1 )
    v3 = &entityFilter;
  else
    v3 = args->argv[1];
  Internal = idCVarSystemLocal::FindInternal(&localCVarSystem, v3);
  if ( Internal )
    Internal->flags |= 0x20400u;
}

// FUNC: private: static void __cdecl idCVarSystemLocal::SetU_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::SetU_f(idCmdArgs *args)
{
  char *v1; // eax
  char *v2; // ecx
  const char *v3; // esi
  idInternalCVar *Internal; // eax

  v1 = (char *)idCmdArgs::Args(args, 2, args->argc - 1, 0);
  if ( args->argc <= 1 )
    v2 = (char *)&entityFilter;
  else
    v2 = args->argv[1];
  idCVarSystemLocal::SetInternal(&localCVarSystem, v2, v1, 0);
  if ( args->argc <= 1 )
    v3 = &entityFilter;
  else
    v3 = args->argv[1];
  Internal = idCVarSystemLocal::FindInternal(&localCVarSystem, v3);
  if ( Internal )
    Internal->flags |= 0x20200u;
}

// FUNC: private: static void __cdecl idCVarSystemLocal::SetT_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::SetT_f(idCmdArgs *args)
{
  char *v1; // eax
  char *v2; // ecx
  const char *v3; // esi
  idInternalCVar *Internal; // eax

  v1 = (char *)idCmdArgs::Args(args, 2, args->argc - 1, 0);
  if ( args->argc <= 1 )
    v2 = (char *)&entityFilter;
  else
    v2 = args->argv[1];
  idCVarSystemLocal::SetInternal(&localCVarSystem, v2, v1, 0);
  if ( args->argc <= 1 )
    v3 = &entityFilter;
  else
    v3 = args->argv[1];
  Internal = idCVarSystemLocal::FindInternal(&localCVarSystem, v3);
  if ( Internal )
    BYTE1(Internal->flags) |= 1u;
}

// FUNC: private: static void __cdecl idCVarSystemLocal::SetA_f(class idCmdArgs const &)
void __cdecl idCVarSystemLocal::SetA_f(idCmdArgs *args)
{
  char *v1; // eax
  char *v2; // ecx

  v1 = (char *)idCmdArgs::Args(args, 2, args->argc - 1, 0);
  if ( args->argc <= 1 )
    v2 = (char *)&entityFilter;
  else
    v2 = args->argv[1];
  idCVarSystemLocal::SetInternal(&localCVarSystem, v2, v1, 0);
  if ( args->argc <= 1 )
    idCVarSystemLocal::FindInternal(&localCVarSystem, &entityFilter);
  else
    idCVarSystemLocal::FindInternal(&localCVarSystem, args->argv[1]);
}

// FUNC: public: virtual void __thiscall idCVarSystemLocal::Init(void)
void __thiscall idCVarSystemLocal::Init(idCVarSystemLocal *this)
{
  this->modifiedFlags = 0;
  cmdSystem->AddCommand(cmdSystem, "toggle", idCVarSystemLocal::Toggle_f, 2, "toggles a cvar", 0);
  cmdSystem->AddCommand(cmdSystem, "set", idCVarSystemLocal::Set_f, 2, "sets a cvar", 0);
  cmdSystem->AddCommand(cmdSystem, "sets", idCVarSystemLocal::SetS_f, 2, "sets a cvar and flags it as server info", 0);
  cmdSystem->AddCommand(cmdSystem, "setu", idCVarSystemLocal::SetU_f, 2, "sets a cvar and flags it as user info", 0);
  cmdSystem->AddCommand(cmdSystem, "sett", idCVarSystemLocal::SetT_f, 2, "sets a cvar and flags it as tool", 0);
  cmdSystem->AddCommand(cmdSystem, "seta", idCVarSystemLocal::SetA_f, 2, "sets a cvar and flags it as archive", 0);
  cmdSystem->AddCommand(cmdSystem, "reset", idCVarSystemLocal::Reset_f, 2, "resets a cvar", 0);
  cmdSystem->AddCommand(cmdSystem, "listCvars", idCVarSystemLocal::List_f, 2, "lists cvars", 0);
  cmdSystem->AddCommand(cmdSystem, "cvar_restart", idCVarSystemLocal::Restart_f, 2, "restart the cvar system", 0);
  this->initialized = 1;
  cmdSystem->AddCommand(cmdSystem, "inc", idCVarSystemLocal::Increment_f, 2, "increments the cvar integer value", 0);
  cmdSystem->AddCommand(cmdSystem, "dec", idCVarSystemLocal::Decrement_f, 2, "decrements the cvar integer value", 0);
}
