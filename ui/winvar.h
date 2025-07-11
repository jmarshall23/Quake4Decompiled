
// FUNC: public: virtual float __thiscall idWinVar::GetMember(int)const
double __thiscall idWinVar::GetMember(idWinVar *this, int memberIndex)
{
  return 0.0;
}

// FUNC: public: virtual unsigned int __thiscall idWinVar::Size(void)
unsigned int __thiscall idWinVar::Size(idWinVar *this)
{
  char *name; // eax

  name = this->name;
  if ( name )
    return strlen(name) + 16;
  else
    return 16;
}

// FUNC: public: virtual void __thiscall idWinVar::SetEval(bool)
void __thiscall idWinVar::SetEval(idWinVar *this, bool b)
{
  this->eval = b;
}

// FUNC: public: char const * __thiscall idWinVar::GetName(void)const
char *__thiscall idWinVar::GetName(idWinVar *this)
{
  char *result; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax

  result = this->name;
  if ( !result )
    return (char *)&entityFilter;
  guiDict = this->guiDict;
  if ( guiDict && *result == 42 )
  {
    Key = idDict::FindKey(guiDict, result + 1);
    if ( Key )
      return Key->value->data;
    return (char *)&entityFilter;
  }
  return result;
}

// FUNC: public: __thiscall idWinStr::idWinStr(void)
void __thiscall idWinStr::idWinStr(idWinStr *this)
{
  char *baseBuffer; // ecx

  this->guiDict = 0;
  this->name = 0;
  this->eval = 1;
  this->__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  baseBuffer = this->data.baseBuffer;
  this->data.len = 0;
  this->data.alloced = 20;
  this->data.data = baseBuffer;
  *baseBuffer = 0;
}

// FUNC: public: virtual __thiscall idWinStr::~idWinStr(void)
void __thiscall idWinStr::~idWinStr(idWinStr *this)
{
  char *name; // [esp-4h] [ebp-18h]

  this->__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  idStr::FreeData(&this->data);
  name = this->name;
  this->__vftable = (idWinStr_vtbl *)&idWinVar::`vftable';
  Memory::Free(name);
  this->name = 0;
}

// FUNC: public: virtual void __thiscall idWinStr::Init(char const *,class idWindow *)
void __thiscall idWinStr::Init(idWinStr *this, const char *_name, idWindow *win)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  const idKeyValue *v7; // eax

  varEdit->Init(varEdit, this, _name, win);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( !name )
      goto LABEL_6;
    if ( *name != 42 )
      goto LABEL_7;
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
      name = Key->value->data;
    else
LABEL_6:
      name = (char *)&entityFilter;
LABEL_7:
    v7 = idDict::FindKey(this->guiDict, name);
    if ( v7 )
      idStr::operator=(&this->data, v7->value->data);
    else
      idStr::operator=(&this->data, (char *)&entityFilter);
  }
}

// FUNC: public: int __thiscall idWinStr::Length(void)
int __thiscall idWinStr::Length(idWinStr *this)
{
  char *name; // eax
  const char *v3; // eax
  const idKeyValue *Key; // eax

  if ( this->guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name )
      {
        v3 = idWinVar::GetName(this);
        Key = idDict::FindKey(this->guiDict, v3);
        if ( Key )
        {
          idStr::operator=(&this->data, Key->value->data);
          return this->data.len;
        }
        idStr::operator=(&this->data, (char *)&entityFilter);
      }
    }
  }
  return this->data.len;
}

// FUNC: public: virtual void __thiscall idWinStr::Set(char const *)
void __thiscall idWinStr::Set(idWinStr *this, char *val)
{
  idDict *guiDict; // ecx
  char *name; // eax
  char *data; // edi
  const idKeyValue *Key; // eax

  idStr::operator=(&this->data, val);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    data = this->data.data;
    if ( name )
    {
      if ( *name != 42 )
      {
LABEL_7:
        idDict::Set(this->guiDict, name, data);
        return;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        idDict::Set(this->guiDict, Key->value->data, data);
        return;
      }
    }
    name = (char *)&entityFilter;
    goto LABEL_7;
  }
}

// FUNC: public: virtual void __thiscall idWinStr::Update(void)
void __thiscall idWinStr::Update(idWinStr *this)
{
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  idDict *v5; // ecx
  const idKeyValue *v6; // eax

  name = this->name;
  if ( !name )
    goto LABEL_6;
  guiDict = this->guiDict;
  if ( guiDict && *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
LABEL_6:
    name = (char *)&entityFilter;
  }
LABEL_7:
  v5 = this->guiDict;
  if ( v5 && *name )
  {
    v6 = idDict::FindKey(v5, name);
    if ( v6 )
      idStr::operator=(&this->data, v6->value->data);
    else
      idStr::operator=(&this->data, (char *)&entityFilter);
  }
}

// FUNC: public: virtual unsigned int __thiscall idWinStr::Size(void)
int __thiscall idWinStr::Size(idWinStr *this)
{
  char *name; // eax
  unsigned int v2; // eax

  name = this->name;
  if ( name )
    v2 = strlen(name);
  else
    v2 = 0;
  if ( this->data.data == this->data.baseBuffer )
    return v2 + 16;
  else
    return this->data.alloced + v2 + 16;
}

// FUNC: public: virtual void __thiscall idWinStr::WriteToSaveGame(class idFile *)
void __thiscall idWinStr::WriteToSaveGame(idWinStr *this, idFile *savefile)
{
  idFile *v2; // esi
  idFile_vtbl *v4; // eax

  v2 = savefile;
  savefile->Write(savefile, &this->eval, 1);
  v4 = v2->__vftable;
  savefile = (idFile *)this->data.len;
  v4->Write(v2, &savefile, 4);
  if ( (int)savefile > 0 )
    v2->Write(v2, this->data.data, (int)savefile);
}

// FUNC: public: virtual void __thiscall idWinStr::ReadFromSaveGame(class idFile *)
void __thiscall idWinStr::ReadFromSaveGame(idWinStr *this, idFile *savefile)
{
  idFile *v2; // ebx
  idFile *v4; // edi

  v2 = savefile;
  savefile->Read(savefile, &this->eval, 1);
  v2->Read(v2, &savefile, 4);
  if ( (int)savefile > 0 )
  {
    v4 = savefile;
    if ( (int)&savefile->__vftable + 1 > this->data.alloced )
      idStr::ReAllocate(&this->data, (int)&savefile->__vftable + 1, 1);
    this->data.len = (int)v4;
    memset(this->data.data, 0x20u, (unsigned int)v4);
    this->data.data[this->data.len] = 0;
    v2->Read(v2, this->data.data, (int)savefile);
  }
}

// FUNC: public: virtual float __thiscall idWinStr::x(void)const
double __thiscall idWinStr::x(idWinStr *this)
{
  if ( *this->data.data )
    return 1.0;
  else
    return 0.0;
}

// FUNC: public: class idStr & __thiscall idWinStr::operator=(class idStr const &)
idStr *__thiscall idWinStr::operator=(idWinStr *this, const idStr *other)
{
  int len; // ebp
  idStr *p_data; // ebx
  int v4; // eax
  idDict *guiDict; // ecx
  char *name; // eax
  char *data; // edi
  const idKeyValue *Key; // eax

  len = other->len;
  p_data = &this->data;
  v4 = other->len + 1;
  if ( v4 > this->data.alloced )
    idStr::ReAllocate(&this->data, v4, 0);
  qmemcpy(p_data->data, other->data, len);
  p_data->data[len] = 0;
  p_data->len = len;
  guiDict = this->guiDict;
  if ( !guiDict )
    return p_data;
  name = this->name;
  data = this->data.data;
  if ( !name )
    goto LABEL_8;
  if ( *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      idDict::Set(this->guiDict, Key->value->data, data);
      return p_data;
    }
LABEL_8:
    name = (char *)&entityFilter;
  }
  idDict::Set(this->guiDict, name, data);
  return p_data;
}

// FUNC: public: virtual char const * __thiscall idWinBool::c_str(void)const
char *__thiscall idWinBool::c_str(idWinBool *this)
{
  return va("%i", this->data);
}

// FUNC: public: virtual void __thiscall idWinBool::WriteToSaveGame(class idFile *)
void __thiscall idWinBool::WriteToSaveGame(idWinBool *this, idFile *savefile)
{
  savefile->Write(savefile, &this->eval, 1);
  savefile->Write(savefile, &this->data, 1);
}

// FUNC: public: virtual void __thiscall idWinBool::ReadFromSaveGame(class idFile *)
void __thiscall idWinBool::ReadFromSaveGame(idWinBool *this, idFile *savefile)
{
  savefile->Read(savefile, &this->eval, 1);
  savefile->Read(savefile, &this->data, 1);
}

// FUNC: public: virtual float __thiscall idWinBool::x(void)const
double __thiscall idWinBool::x(idWinBool *this)
{
  if ( this->data )
    return 1.0;
  else
    return 0.0;
}

// FUNC: public: virtual void __thiscall idWinBool::Init(char const *,class idWindow *)
void __thiscall idWinBool::Init(idWinBool *this, const char *_name, idWindow *win)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  const idKeyValue *v7; // eax
  const char *data; // eax

  varEdit->Init(varEdit, this, _name, win);
  guiDict = this->guiDict;
  if ( !guiDict )
    return;
  name = this->name;
  if ( !name )
    goto LABEL_6;
  if ( *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
LABEL_6:
    name = (char *)&entityFilter;
  }
LABEL_7:
  v7 = idDict::FindKey(this->guiDict, name);
  if ( v7 )
    data = v7->value->data;
  else
    data = "0";
  this->data = atoi(data) != 0;
}

// FUNC: public: bool & __thiscall idWinBool::operator=(bool const &)
bool *__thiscall idWinBool::operator=(idWinBool *this, bool *other)
{
  bool *p_data; // edi
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // ebx
  idDict *v8; // esi
  const char *v9; // eax

  p_data = &this->data;
  this->data = *other;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v8 = this->guiDict;
        v9 = va("%i", *p_data);
        idDict::Set(v8, data, v9);
        return p_data;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
  return p_data;
}

// FUNC: public: virtual void __thiscall idWinBool::Set(char const *)
void __thiscall idWinBool::Set(idWinBool *this, const char *val)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // edi
  bool v7; // al
  idDict *v8; // esi
  const char *v9; // eax

  this->data = atoi(val) != 0;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v7 = this->data;
        v8 = this->guiDict;
        v9 = va("%i", v7);
        idDict::Set(v8, data, v9);
        return;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
}

// FUNC: public: virtual void __thiscall idWinBool::Update(void)
void __thiscall idWinBool::Update(idWinBool *this)
{
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  idDict *v5; // ecx
  const idKeyValue *v6; // eax

  name = this->name;
  if ( !name )
    goto LABEL_6;
  guiDict = this->guiDict;
  if ( guiDict && *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
LABEL_6:
    name = (char *)&entityFilter;
  }
LABEL_7:
  v5 = this->guiDict;
  if ( v5 && *name )
  {
    v6 = idDict::FindKey(v5, name);
    if ( v6 )
      this->data = atoi(v6->value->data) != 0;
    else
      this->data = atoi("0") != 0;
  }
}

// FUNC: public: __thiscall idWinFloat::idWinFloat(void)
void __thiscall idWinFloat::idWinFloat(idWinFloat *this)
{
  this->guiDict = 0;
  this->name = 0;
  this->eval = 1;
  this->__vftable = (idWinFloat_vtbl *)&idWinFloat::`vftable';
}

// FUNC: public: virtual __thiscall idWinFloat::~idWinFloat(void)
void __thiscall idWinFloat::~idWinFloat(idWinVar *this)
{
  char *name; // [esp-4h] [ebp-8h]

  name = this->name;
  this->__vftable = (idWinVar_vtbl *)&idWinVar::`vftable';
  Memory::Free(name);
  this->name = 0;
}

// FUNC: public: virtual char const * __thiscall idWinFloat::c_str(void)const
char *__thiscall idWinFloat::c_str(idWinFloat *this)
{
  return va("%f", this->data);
}

// FUNC: public: virtual void __thiscall idWinInt::WriteToSaveGame(class idFile *)
void __thiscall idWinInt::WriteToSaveGame(idWinFloat *this, idFile *savefile)
{
  savefile->Write(savefile, &this->eval, 1);
  savefile->Write(savefile, &this->data, 4);
}

// FUNC: public: virtual void __thiscall idWinInt::ReadFromSaveGame(class idFile *)
void __thiscall idWinInt::ReadFromSaveGame(idWinFloat *this, idFile *savefile)
{
  savefile->Read(savefile, &this->eval, 1);
  savefile->Read(savefile, &this->data, 4);
}

// FUNC: public: virtual float __thiscall idWinRectangle::x(void)const
double __thiscall idWinRectangle::x(idWinVec4 *this)
{
  return this->data.x;
}

// FUNC: public: virtual void __thiscall idWinFloat::Init(char const *,class idWindow *)
void __thiscall idWinFloat::Init(idWinFloat *this, const char *_name, idWindow *win)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  const idKeyValue *v7; // eax

  varEdit->Init(varEdit, this, _name, win);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( !name )
      goto LABEL_6;
    if ( *name != 42 )
      goto LABEL_7;
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
      name = Key->value->data;
    else
LABEL_6:
      name = (char *)&entityFilter;
LABEL_7:
    v7 = idDict::FindKey(this->guiDict, name);
    if ( v7 )
      this->data = atof(v7->value->data);
    else
      this->data = atof("0");
  }
}

// FUNC: public: float & __thiscall idWinFloat::operator=(float const &)
float *__thiscall idWinFloat::operator=(idWinFloat *this, float *other)
{
  float *p_data; // ebx
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // edi
  idDict *v8; // esi
  const char *v9; // eax

  p_data = &this->data;
  this->data = *other;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v8 = this->guiDict;
        v9 = va("%f", *p_data);
        idDict::Set(v8, data, v9);
        return p_data;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
  return p_data;
}

// FUNC: public: virtual void __thiscall idWinFloat::Set(float)
void __thiscall idWinFloat::Set(idWinFloat *this, float val)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // edi
  double v7; // st7
  idDict *v8; // esi
  const char *v9; // eax

  guiDict = this->guiDict;
  this->data = val;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v7 = this->data;
        v8 = this->guiDict;
        v9 = va("%f", v7);
        idDict::Set(v8, data, v9);
        return;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
}

// FUNC: public: virtual void __thiscall idWinFloat::Update(void)
void __thiscall idWinFloat::Update(idWinFloat *this)
{
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  idDict *v5; // ecx
  const idKeyValue *v6; // eax

  name = this->name;
  if ( !name )
    goto LABEL_6;
  guiDict = this->guiDict;
  if ( guiDict && *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
LABEL_6:
    name = (char *)&entityFilter;
  }
LABEL_7:
  v5 = this->guiDict;
  if ( v5 && *name )
  {
    v6 = idDict::FindKey(v5, name);
    if ( v6 )
      this->data = atof(v6->value->data);
    else
      this->data = atof("0");
  }
}

// FUNC: public: __thiscall idWinVec4::idWinVec4(void)
void __thiscall idWinVec4::idWinVec4(idWinVec4 *this)
{
  this->guiDict = 0;
  this->name = 0;
  this->eval = 1;
  this->__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
}

// FUNC: public: virtual void __thiscall idWinVec4::Set(char const *)
void __thiscall idWinVec4::Set(idWinVec4 *this, const char *val)
{
  bool v3; // zf
  idVec4 *p_data; // [esp-10h] [ebp-1Ch]
  float *p_y; // [esp-Ch] [ebp-18h]
  float *p_z; // [esp-8h] [ebp-14h]
  float *p_w; // [esp-4h] [ebp-10h]

  v3 = strchr(val, 44) == 0;
  p_w = &this->data.w;
  p_z = &this->data.z;
  p_y = &this->data.y;
  p_data = &this->data;
  if ( v3 )
    sscanf(val, "%f %f %f %f", p_data, p_y, p_z, p_w);
  else
    sscanf(val, "%f,%f,%f,%f", p_data, p_y, p_z, p_w);
  (*(void (__thiscall **)(idWinVec4 *, idVec4 *))&this->gap8[4])(this, &this->data);
}

// FUNC: public: virtual void __thiscall idWinVec4::Init(char const *,class idWindow *)
void __thiscall idWinVec4::Init(idWinVec4 *this, const char *_name, idWindow *win)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  float y; // eax
  float z; // ecx
  idVec4 *p_data; // esi
  float w; // edx
  idVec4 out; // [esp+Ch] [ebp-10h] BYREF

  varEdit->Init(varEdit, this, _name, win);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
LABEL_7:
        idDict::GetVec4(this->guiDict, name, 0, &out);
        y = out.y;
        z = out.z;
        p_data = &this->data;
        p_data->x = out.x;
        w = out.w;
        p_data->y = y;
        p_data->z = z;
        p_data->w = w;
        return;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        name = Key->value->data;
        goto LABEL_7;
      }
    }
    name = (char *)&entityFilter;
    goto LABEL_7;
  }
}

// FUNC: public: class idVec4 & __thiscall idWinVec4::operator=(class idVec4 const &)
idVec4 *__thiscall idWinVec4::operator=(idWinVec4 *this, const idVec4 *other)
{
  idVec4 *p_data; // ebx
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // edi
  idDict *v8; // esi
  const char *v9; // eax

  p_data = &this->data;
  this->data = *other;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v8 = this->guiDict;
        v9 = idVec4::ToString(p_data, 2);
        idDict::Set(v8, data, v9);
        return p_data;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
  return p_data;
}

// FUNC: public: virtual void __thiscall idWinVec4::Set(class idVec4 const &)
void __thiscall idWinVec4::Set(idWinVec4 *this, const idVec4 *val)
{
  idVec4 *p_data; // ebx
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // edi
  idDict *v8; // esi
  const char *v9; // eax

  p_data = &this->data;
  this->data = *val;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v8 = this->guiDict;
        v9 = idVec4::ToString(p_data, 2);
        idDict::Set(v8, data, v9);
        return;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
}

// FUNC: public: virtual void __thiscall idWinVec4::SetMember(int,float)
void __thiscall idWinVec4::SetMember(idWinVec4 *this, int index, float val)
{
  *(&this->data.x + index) = val;
  (*(void (__stdcall **)(idVec4 *))&this->gap8[4])(&this->data);
}

// FUNC: public: virtual float __thiscall idWinVec4::GetMember(int)const
double __thiscall idWinVec4::GetMember(idWinVec4 *this, int index)
{
  return *(&this->data.x + index);
}

// FUNC: public: virtual void __thiscall idWinVec4::Update(void)
void __thiscall idWinVec4::Update(idWinVec4 *this)
{
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  idDict *v5; // ecx
  float y; // ecx
  float z; // edx
  idVec4 *p_data; // esi
  float w; // eax
  idVec4 out; // [esp+4h] [ebp-10h] BYREF

  name = this->name;
  if ( !name )
  {
LABEL_6:
    name = (char *)&entityFilter;
    goto LABEL_7;
  }
  guiDict = this->guiDict;
  if ( guiDict && *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
    goto LABEL_6;
  }
LABEL_7:
  v5 = this->guiDict;
  if ( v5 )
  {
    if ( *name )
    {
      idDict::GetVec4(v5, name, 0, &out);
      y = out.y;
      z = out.z;
      p_data = &this->data;
      p_data->x = out.x;
      w = out.w;
      p_data->y = y;
      p_data->z = z;
      p_data->w = w;
    }
  }
}

// FUNC: public: virtual char const * __thiscall idWinInt::c_str(void)const
char *__thiscall idWinInt::c_str(idWinInt *this)
{
  return va("%i", this->data);
}

// FUNC: public: virtual void __thiscall idWinInt::Init(char const *,class idWindow *)
void __thiscall idWinInt::Init(idWinInt *this, const char *_name, idWindow *win)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  const idKeyValue *v7; // eax

  varEdit->Init(varEdit, this, _name, win);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( !name )
      goto LABEL_6;
    if ( *name != 42 )
      goto LABEL_7;
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
      name = Key->value->data;
    else
LABEL_6:
      name = (char *)&entityFilter;
LABEL_7:
    v7 = idDict::FindKey(this->guiDict, name);
    if ( v7 )
      this->data = atoi(v7->value->data);
    else
      this->data = atoi("0");
  }
}

// FUNC: public: virtual void __thiscall idWinInt::Set(char const *)
void __thiscall idWinInt::Set(idWinInt *this, const char *val)
{
  int v3; // eax
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // edi
  int v8; // eax
  idDict *v9; // esi
  const char *v10; // eax

  v3 = atoi(val);
  guiDict = this->guiDict;
  this->data = v3;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v8 = this->data;
        v9 = this->guiDict;
        v10 = va("%i", v8);
        idDict::Set(v9, data, v10);
        return;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
}

// FUNC: public: virtual void __thiscall idWinInt::Update(void)
void __thiscall idWinInt::Update(idWinInt *this)
{
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  idDict *v5; // ecx
  const idKeyValue *v6; // eax

  name = this->name;
  if ( !name )
    goto LABEL_6;
  guiDict = this->guiDict;
  if ( guiDict && *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
LABEL_6:
    name = (char *)&entityFilter;
  }
LABEL_7:
  v5 = this->guiDict;
  if ( v5 && *name )
  {
    v6 = idDict::FindKey(v5, name);
    if ( v6 )
      this->data = atoi(v6->value->data);
    else
      this->data = atoi("0");
  }
}

// FUNC: public: class idRectangle & __thiscall idWinRectangle::operator=(class idVec4 const &)
idRectangle *__thiscall idWinRectangle::operator=(idWinRectangle *this, idVec4 *other)
{
  idRectangle *p_data; // esi
  float y; // ecx
  float z; // edx
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // ebx
  idDict *v10; // edi
  const char *v11; // eax
  float w; // [esp+18h] [ebp-4h]

  p_data = &this->data;
  y = other->y;
  w = other->w;
  z = other->z;
  p_data->x = other->x;
  this->data.y = y;
  this->data.w = z;
  this->data.h = w;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v10 = this->guiDict;
        v11 = idVec4::ToString(other, 2);
        idDict::Set(v10, data, v11);
        return p_data;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
  return p_data;
}

// FUNC: public: int & __thiscall idWinInt::operator=(int const &)
int *__thiscall idWinInt::operator=(idWinInt *this, int *other)
{
  int *p_data; // edi
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // ebx
  idDict *v8; // esi
  const char *v9; // eax

  p_data = &this->data;
  this->data = *other;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v8 = this->guiDict;
        v9 = va("%i", *p_data);
        idDict::Set(v8, data, v9);
        return p_data;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
  return p_data;
}

// FUNC: public: class idRectangle & __thiscall idWinRectangle::operator=(class idRectangle const &)
idRectangle *__thiscall idWinRectangle::operator=(idWinRectangle *this, const idRectangle *other)
{
  idRectangle *p_data; // ebx
  idDict *guiDict; // ecx
  float w; // edx
  char *name; // eax
  const idKeyValue *Key; // eax
  const char *data; // edi
  idDict *v9; // esi
  const char *v10; // eax
  idVec4 v; // [esp+Ch] [ebp-10h] BYREF

  p_data = &this->data;
  this->data = *other;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    v.x = other->x;
    v.y = other->y;
    w = other->w;
    v.w = other->h;
    name = this->name;
    v.z = w;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v9 = this->guiDict;
        v10 = idVec4::ToString(&v, 2);
        idDict::Set(v9, data, v10);
        return p_data;
      }
    }
    data = &entityFilter;
    goto LABEL_8;
  }
  return p_data;
}

// FUNC: public: class idVec2 & __thiscall idWinVec2::operator=(class idVec2 const &)
idVec2 *__thiscall idWinVec2::operator=(idWinVec2 *this, const idVec2 *other)
{
  idVec2 *p_data; // esi
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // ebx
  idDict *v8; // edi
  const char *v9; // eax

  p_data = &this->data;
  this->data.x = other->x;
  guiDict = this->guiDict;
  this->data.y = other->y;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v8 = this->guiDict;
        v9 = idVec2::ToString(p_data, 2);
        idDict::Set(v8, data, v9);
        return p_data;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
  return p_data;
}

// FUNC: public: class idVec3 & __thiscall idWinVec3::operator=(class idVec3 const &)
idVec3 *__thiscall idWinVec3::operator=(idWinVec3 *this, const idVec3 *other)
{
  idVec3 *p_data; // esi
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // ebx
  idDict *v8; // edi
  const char *v9; // eax

  p_data = &this->data;
  this->data = *other;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v8 = this->guiDict;
        v9 = idVec3::ToString(p_data, 2);
        idDict::Set(v8, data, v9);
        return p_data;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
  return p_data;
}

// FUNC: public: void __thiscall idWinVec4::Zero(void)
void __thiscall idWinVec4::Zero(idWinVec4 *this)
{
  idVec4 *p_data; // esi
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // ebx
  idDict *v7; // edi
  const char *v8; // eax

  p_data = &this->data;
  this->data.w = 0.0;
  this->data.z = 0.0;
  this->data.y = 0.0;
  this->data.x = 0.0;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v7 = this->guiDict;
        v8 = idVec4::ToString(p_data, 2);
        idDict::Set(v7, data, v8);
        return;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
}

// FUNC: public: void __thiscall idWinVar::SetName(char const *)
void __thiscall idWinVar::SetName(idWinVar *this, const char *_name)
{
  char *v3; // eax
  const char *v4; // ecx
  char *v5; // edx
  char v6; // al

  Memory::Free(this->name);
  this->name = 0;
  if ( _name )
  {
    v3 = (char *)Memory::Allocate(strlen(_name) + 1);
    this->name = v3;
    v4 = _name;
    v5 = v3;
    do
    {
      v6 = *v4;
      *v5++ = *v4++;
    }
    while ( v6 );
  }
}

// FUNC: public: virtual char const * __thiscall idWinVec4::c_str(void)const
const char *__thiscall idWinVec4::c_str(idWinVec4 *this)
{
  return idVec4::ToString(&this->data, 2);
}

// FUNC: public: virtual void __thiscall idWinRectangle::WriteToSaveGame(class idFile *)
void __thiscall idWinRectangle::WriteToSaveGame(idWinVec4 *this, idFile *savefile)
{
  savefile->Write(savefile, &this->eval, 1);
  savefile->Write(savefile, &this->data, 16);
}

// FUNC: public: virtual void __thiscall idWinVec4::ReadFromSaveGame(class idFile *)
void __thiscall idWinVec4::ReadFromSaveGame(idWinVec4 *this, idFile *savefile)
{
  savefile->Read(savefile, &this->eval, 1);
  savefile->Read(savefile, &this->data, 16);
}

// FUNC: public: virtual void __thiscall idWinFloatMember::Init(char const *,class idWindow *)
void __thiscall idWinFloatMember::Init(idWinFloatMember *this, const char *_name, idWindow *win)
{
  varEdit->Init(varEdit, this, _name, win);
}

// FUNC: public: virtual void __thiscall idWinFloatMember::Set(char const *)
void __thiscall idWinFloatMember::Set(idWinFloat *this, const char *val)
{
  idWinFloat_vtbl *v3; // edi
  float v4; // [esp+0h] [ebp-Ch]

  v3 = this->__vftable;
  v4 = atof(val);
  (*(void (__thiscall **)(idWinFloat *, _DWORD))v3->gap8)(this, LODWORD(v4));
}

// FUNC: public: virtual void __thiscall idWinFloat::Set(class idVec4 const &)
void __thiscall idWinFloat::Set(idWinFloat *this, const idVec4 *val)
{
  (*(void (__thiscall **)(idWinFloat *, _DWORD))this->gap8)(this, LODWORD(val->x));
}

// FUNC: public: virtual void __thiscall idWinFloatMember::Set(float)
void __thiscall idWinFloatMember::Set(idWinFloatMember *this, float val)
{
  ((void (__thiscall *)(idWinVar *, int, _DWORD))this->parentVar->SetMember)(
    this->parentVar,
    this->memberIndex,
    LODWORD(val));
}

// FUNC: public: virtual char const * __thiscall idWinFloatMember::c_str(void)const
char *__thiscall idWinFloatMember::c_str(idWinFloatMember *this)
{
  double v1; // st7

  v1 = ((double (__thiscall *)(idWinVar *, int))this->parentVar->GetMember)(this->parentVar, this->memberIndex);
  return va("%f", v1);
}

// FUNC: public: virtual void __thiscall idWinFloatMember::SetEval(bool)
void __thiscall idWinFloatMember::SetEval(idWinFloatMember *this, BOOL b)
{
  this->eval = b;
  this->parentVar->SetEval(this->parentVar, b);
}

// FUNC: public: virtual float __thiscall idWinFloatMember::x(void)const
void __thiscall idWinFloatMember::x(idWinFloatMember *this)
{
  this->parentVar->GetMember(this->parentVar, this->memberIndex);
}

// FUNC: public: virtual void __thiscall idWinRectangle::Init(char const *,class idWindow *)
void __thiscall idWinRectangle::Init(idWinRectangle *this, const char *_name, idWindow *win)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  float y; // ecx
  float z; // edx
  float v_12; // [esp+18h] [ebp-14h]
  idVec4 out; // [esp+1Ch] [ebp-10h] BYREF

  varEdit->Init(varEdit, this, _name, win);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
LABEL_7:
        idDict::GetVec4(this->guiDict, name, 0, &out);
        y = out.y;
        v_12 = out.w;
        z = out.z;
        this->data.x = out.x;
        this->data.y = y;
        this->data.w = z;
        this->data.h = v_12;
        return;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        name = Key->value->data;
        goto LABEL_7;
      }
    }
    name = (char *)&entityFilter;
    goto LABEL_7;
  }
}

// FUNC: public: virtual void __thiscall idWinRectangle::Set(class idVec4 const &)
void __thiscall idWinRectangle::Set(idWinRectangle *this, const idVec4 *val)
{
  idVec4 *p_data; // esi
  float y; // ecx
  float z; // edx
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // ebx
  idDict *v10; // edi
  const char *v11; // eax
  float w; // [esp+14h] [ebp-4h]

  p_data = (idVec4 *)&this->data;
  y = val->y;
  w = val->w;
  z = val->z;
  p_data->x = val->x;
  this->data.y = y;
  this->data.w = z;
  this->data.h = w;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_8:
        v10 = this->guiDict;
        v11 = idVec4::ToString(p_data, 2);
        idDict::Set(v10, data, v11);
        return;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_8;
  }
}

// FUNC: public: virtual void __thiscall idWinRectangle::Set(float)
void __thiscall idWinRectangle::Set(idWinVec4 *this, int val)
{
  int v2[4]; // [esp+0h] [ebp-10h] BYREF

  v2[1] = val;
  v2[3] = val;
  v2[0] = val;
  v2[2] = val;
  (*(void (__thiscall **)(idWinVec4 *, int *))&this->gap8[4])(this, v2);
}

// FUNC: public: virtual void __thiscall idWinRectangle::SetMember(int,float)
void __thiscall idWinRectangle::SetMember(idWinRectangle *this, int index, float val)
{
  float h; // eax
  idVec4 temp; // [esp+0h] [ebp-10h] BYREF

  temp.x = this->data.x;
  temp.y = this->data.y;
  h = this->data.h;
  temp.z = this->data.w;
  temp.w = h;
  *(&temp.x + index) = val;
  (*(void (__thiscall **)(idWinRectangle *, idVec4 *))&this->gap8[4])(this, &temp);
}

// FUNC: public: virtual void __thiscall idWinRectangle::Update(void)
void __thiscall idWinRectangle::Update(idWinRectangle *this)
{
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  idDict *v5; // ecx
  float y; // edx
  float z; // eax
  float v_12; // [esp+10h] [ebp-14h]
  idVec4 out; // [esp+14h] [ebp-10h] BYREF

  name = this->name;
  if ( !name )
  {
LABEL_6:
    name = (char *)&entityFilter;
    goto LABEL_7;
  }
  guiDict = this->guiDict;
  if ( guiDict && *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
    goto LABEL_6;
  }
LABEL_7:
  v5 = this->guiDict;
  if ( v5 )
  {
    if ( *name )
    {
      idDict::GetVec4(v5, name, 0, &out);
      y = out.y;
      v_12 = out.w;
      z = out.z;
      this->data.x = out.x;
      this->data.y = y;
      this->data.w = z;
      this->data.h = v_12;
    }
  }
}

// FUNC: public: virtual char const * __thiscall idWinVec2::c_str(void)const
const char *__thiscall idWinVec2::c_str(idWinVec2 *this)
{
  return idVec2::ToString(&this->data, 2);
}

// FUNC: public: virtual void __thiscall idWinVec2::WriteToSaveGame(class idFile *)
void __thiscall idWinVec2::WriteToSaveGame(idWinVec2 *this, idFile *savefile)
{
  savefile->Write(savefile, &this->eval, 1);
  savefile->Write(savefile, &this->data, 8);
}

// FUNC: public: virtual void __thiscall idWinVec2::ReadFromSaveGame(class idFile *)
void __thiscall idWinVec2::ReadFromSaveGame(idWinVec2 *this, idFile *savefile)
{
  savefile->Read(savefile, &this->eval, 1);
  savefile->Read(savefile, &this->data, 8);
}

// FUNC: public: virtual void __thiscall idWinVec2::Init(char const *,class idWindow *)
void __thiscall idWinVec2::Init(idWinVec2 *this, const char *_name, idWindow *win)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  float y; // eax
  idVec2 out; // [esp+Ch] [ebp-8h] BYREF

  varEdit->Init(varEdit, this, _name, win);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
LABEL_7:
        idDict::GetVec2(this->guiDict, name, 0, &out);
        y = out.y;
        this->data.x = out.x;
        this->data.y = y;
        return;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        name = Key->value->data;
        goto LABEL_7;
      }
    }
    name = (char *)&entityFilter;
    goto LABEL_7;
  }
}

// FUNC: public: virtual void __thiscall idWinVec2::Set(char const *)
void __thiscall idWinVec2::Set(idWinVec2 *this, const char *val)
{
  idVec2 *p_data; // ebx
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // edi
  idDict *v8; // esi
  const char *v9; // eax

  p_data = &this->data;
  if ( strchr(val, 44) )
    sscanf(val, "%f,%f", &this->data, &this->data.y);
  else
    sscanf(val, "%f %f", &this->data, &this->data.y);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->name;
        goto LABEL_11;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_11:
        v8 = this->guiDict;
        v9 = idVec2::ToString(p_data, 2);
        idDict::Set(v8, data, v9);
        return;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_11;
  }
}

// FUNC: public: virtual void __thiscall idWinVec2::Update(void)
void __thiscall idWinVec2::Update(idWinVec2 *this)
{
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  idDict *v5; // ecx
  float y; // ecx
  idVec2 out; // [esp+4h] [ebp-8h] BYREF

  name = this->name;
  if ( !name )
  {
LABEL_6:
    name = (char *)&entityFilter;
    goto LABEL_7;
  }
  guiDict = this->guiDict;
  if ( guiDict && *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
    goto LABEL_6;
  }
LABEL_7:
  v5 = this->guiDict;
  if ( v5 )
  {
    if ( *name )
    {
      idDict::GetVec2(v5, name, 0, &out);
      y = out.y;
      this->data.x = out.x;
      this->data.y = y;
    }
  }
}

// FUNC: public: virtual __thiscall idWinBackground::~idWinBackground(void)
void __thiscall idWinBackground::~idWinBackground(idWinBackground *this)
{
  this->__vftable = (idWinBackground_vtbl *)&idWinBackground::`vftable';
  idStr::FreeData(&this->data);
  idWinStr::~idWinStr(this);
}

// FUNC: public: virtual void __thiscall idWinBackground::Init(char const *,class idWindow *)
void __thiscall idWinBackground::Init(idWinBackground *this, const char *_name, idWindow *win)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  const idKeyValue *v7; // eax

  varEdit->Init(varEdit, this, _name, win);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    if ( !name )
      goto LABEL_6;
    if ( *name != 42 )
      goto LABEL_7;
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
      name = Key->value->data;
    else
LABEL_6:
      name = (char *)&entityFilter;
LABEL_7:
    v7 = idDict::FindKey(this->guiDict, name);
    if ( v7 )
      idStr::operator=(&this->data, v7->value->data);
    else
      idStr::operator=(&this->data, (char *)&entityFilter);
  }
}

// FUNC: public: int __thiscall idWinBackground::Length(void)
int __thiscall idWinBackground::Length(idWinBackground *this)
{
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  const idKeyValue *v5; // eax

  guiDict = this->guiDict;
  if ( !guiDict )
    return this->data.len;
  name = this->name;
  if ( !name )
    goto LABEL_6;
  if ( *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
LABEL_6:
    name = (char *)&entityFilter;
  }
LABEL_7:
  v5 = idDict::FindKey(this->guiDict, name);
  if ( v5 )
  {
    idStr::operator=(&this->data, v5->value->data);
    return this->data.len;
  }
  idStr::operator=(&this->data, (char *)&entityFilter);
  return this->data.len;
}

// FUNC: public: virtual void __thiscall idWinBackground::Set(char const *)
void __thiscall idWinBackground::Set(idWinBackground *this, char *val)
{
  idDict *guiDict; // ecx
  char *name; // eax
  char *data; // edi
  const idKeyValue *Key; // eax

  idStr::operator=(&this->data, val);
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    data = this->data.data;
    if ( name )
    {
      if ( *name != 42 )
      {
LABEL_7:
        idDict::Set(this->guiDict, name, data);
        goto LABEL_8;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        name = Key->value->data;
        goto LABEL_7;
      }
    }
    name = (char *)&entityFilter;
    goto LABEL_7;
  }
LABEL_8:
  if ( this->mat )
  {
    if ( idStr::Cmp(this->data.data, &entityFilter) )
      *this->mat = declManager->FindMaterial(declManager, this->data.data, 1);
    else
      *this->mat = 0;
  }
}

// FUNC: public: virtual void __thiscall idWinBackground::Update(void)
void __thiscall idWinBackground::Update(idWinBackground *this)
{
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  idDict *v5; // ecx
  const idKeyValue *v6; // eax
  char *data; // eax

  name = this->name;
  if ( !name )
    goto LABEL_6;
  guiDict = this->guiDict;
  if ( guiDict && *name == 42 )
  {
    Key = idDict::FindKey(guiDict, name + 1);
    if ( Key )
    {
      name = Key->value->data;
      goto LABEL_7;
    }
LABEL_6:
    name = (char *)&entityFilter;
  }
LABEL_7:
  v5 = this->guiDict;
  if ( v5 && *name )
  {
    v6 = idDict::FindKey(v5, name);
    if ( v6 )
      data = v6->value->data;
    else
      data = (char *)&entityFilter;
    idStr::operator=(&this->data, data);
    if ( this->mat )
    {
      if ( idStr::Cmp(this->data.data, &entityFilter) )
        *this->mat = declManager->FindMaterial(declManager, this->data.data, 1);
      else
        *this->mat = 0;
    }
  }
}

// FUNC: public: virtual unsigned int __thiscall idWinBackground::Size(void)
int __thiscall idWinBackground::Size(idWinBackground *this)
{
  char *name; // eax
  unsigned int v2; // eax

  name = this->name;
  if ( name )
    v2 = strlen(name);
  else
    v2 = 0;
  if ( this->data.data == this->data.baseBuffer )
    return v2 + 16;
  else
    return this->data.alloced + v2 + 16;
}

// FUNC: public: virtual void __thiscall idWinBackground::WriteToSaveGame(class idFile *)
void __thiscall idWinBackground::WriteToSaveGame(idWinBackground *this, idFile *savefile)
{
  idFile *v2; // esi
  idFile_vtbl *v4; // eax

  v2 = savefile;
  savefile->Write(savefile, &this->eval, 1);
  v4 = v2->__vftable;
  savefile = (idFile *)this->data.len;
  v4->Write(v2, &savefile, 4);
  if ( (int)savefile > 0 )
    v2->Write(v2, this->data.data, (int)savefile);
}

// FUNC: public: virtual void __thiscall idWinBackground::ReadFromSaveGame(class idFile *)
void __thiscall idWinBackground::ReadFromSaveGame(idWinBackground *this, idFile *savefile)
{
  idFile *v2; // ebp
  idFile *v4; // eax
  idFile *v5; // edi
  const idMaterial **mat; // ecx

  v2 = savefile;
  savefile->Read(savefile, &this->eval, 1);
  v2->Read(v2, &savefile, 4);
  v4 = savefile;
  if ( (int)savefile > 0 )
  {
    v5 = savefile;
    if ( (int)&savefile->__vftable + 1 > this->data.alloced )
      idStr::ReAllocate(&this->data, (int)&savefile->__vftable + 1, 1);
    this->data.len = (int)v5;
    memset(this->data.data, 0x20u, (unsigned int)v5);
    this->data.data[this->data.len] = 0;
    v2->Read(v2, this->data.data, (int)savefile);
    v4 = savefile;
  }
  mat = this->mat;
  if ( mat )
  {
    if ( (int)v4 <= 0 )
      *mat = 0;
    else
      *this->mat = declManager->FindMaterial(declManager, this->data.data, 1);
  }
}

// FUNC: public: class idWinStr & __thiscall idWinStr::operator=(class idWinStr const &)
idWinVar *__thiscall idWinStr::operator=(idWinVar *this, int a2)
{
  idWinVar_vtbl *v3; // edi

  this->guiDict = *(idDict **)(a2 + 4);
  idWinVar::SetName(this, *(const char **)(a2 + 8));
  v3 = *(idWinVar_vtbl **)(a2 + 16);
  if ( (int)&v3->~idWinVar + 1 > (int)this[1].name )
    idStr::ReAllocate((idStr *)&this[1], (int)&v3->~idWinVar + 1, 0);
  qmemcpy(this[1].guiDict, *(const void **)(a2 + 20), (unsigned int)v3);
  *((_BYTE *)&v3->~idWinVar + (unsigned int)this[1].guiDict) = 0;
  this[1].__vftable = v3;
  return this;
}

// FUNC: public: class idWinBackground & __thiscall idWinBackground::operator=(class idWinBackground const &)
idWinVar *__thiscall idWinBackground::operator=(idWinVar *this, int a2)
{
  idWinVar_vtbl *v3; // edi
  idWinVar_vtbl *v4; // eax

  this->guiDict = *(idDict **)(a2 + 4);
  idWinVar::SetName(this, *(const char **)(a2 + 8));
  v3 = *(idWinVar_vtbl **)(a2 + 48);
  if ( (int)&v3->~idWinVar + 1 > (int)this[3].name )
    idStr::ReAllocate((idStr *)&this[3], (int)&v3->~idWinVar + 1, 0);
  qmemcpy(this[3].guiDict, *(const void **)(a2 + 52), (unsigned int)v3);
  *((_BYTE *)&v3->~idWinVar + (unsigned int)this[3].guiDict) = 0;
  this[3].__vftable = v3;
  v4 = *(idWinVar_vtbl **)(a2 + 80);
  this[5].__vftable = v4;
  if ( v4 )
  {
    if ( !idStr::Cmp((const char *)this[3].guiDict, &entityFilter) )
    {
      this[5].~idWinVar = 0;
      return this;
    }
    this[5].~idWinVar = (void (__thiscall *)(idWinVar *))declManager->FindMaterial(declManager, this[3].guiDict, 1);
  }
  return this;
}

// FUNC: public: class idStr & __thiscall idWinBackground::operator=(class idStr const &)
idStr *__thiscall idWinBackground::operator=(idWinBackground *this, const idStr *other)
{
  int len; // ebp
  idStr *p_data; // edi
  int v5; // eax
  idDict *guiDict; // ecx
  char *name; // eax
  char *data; // edi
  const idKeyValue *Key; // eax

  len = other->len;
  p_data = &this->data;
  v5 = other->len + 1;
  if ( v5 > this->data.alloced )
    idStr::ReAllocate(&this->data, v5, 0);
  qmemcpy(p_data->data, other->data, len);
  this->data.data[len] = 0;
  this->data.len = len;
  guiDict = this->guiDict;
  if ( guiDict )
  {
    name = this->name;
    data = this->data.data;
    if ( name )
    {
      if ( *name != 42 )
      {
LABEL_9:
        idDict::Set(this->guiDict, name, data);
        goto LABEL_10;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        name = Key->value->data;
        goto LABEL_9;
      }
    }
    name = (char *)&entityFilter;
    goto LABEL_9;
  }
LABEL_10:
  if ( this->mat )
  {
    if ( !idStr::Cmp(this->data.data, &entityFilter) )
    {
      *this->mat = 0;
      return &this->data;
    }
    *this->mat = declManager->FindMaterial(declManager, this->data.data, 1);
  }
  return &this->data;
}
