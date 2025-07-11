
// FUNC: public: virtual __thiscall idCVar::~idCVar(void)
void __thiscall idCVar::~idCVar(idCVar *this)
{
  this->__vftable = (idCVar_vtbl *)&idCVar::`vftable';
}

// FUNC: public: bool __thiscall idCVar::IsModified(void)const
unsigned int __thiscall idCVar::IsModified(idCVar *this)
{
  return ((unsigned int)this->internalVar->flags >> 18) & 1;
}

// FUNC: public: void __thiscall idCVar::ClearModified(void)
void __thiscall idCVar::ClearModified(idCVar *this)
{
  BYTE2(this->internalVar->flags) &= ~4u;
}

// FUNC: public: char const * __thiscall idCVar::GetString(void)const
const char *__thiscall idCVar::GetString(idCVar *this)
{
  return this->internalVar->value;
}

// FUNC: public: bool __thiscall idCVar::GetBool(void)const
bool __thiscall idCVar::GetBool(idCVar *this)
{
  return this->internalVar->integerValue != 0;
}

// FUNC: public: int __thiscall idCVar::GetInteger(void)const
int __thiscall idCVar::GetInteger(idCVar *this)
{
  return this->internalVar->integerValue;
}

// FUNC: public: float __thiscall idCVar::GetFloat(void)const
double __thiscall idCVar::GetFloat(idCVar *this)
{
  return this->internalVar->floatValue;
}

// FUNC: public: void __thiscall idCVar::SetString(char const *)
void __thiscall idCVar::SetString(idCVar *this, const char *value)
{
  this->internalVar->InternalSetString(this->internalVar, value);
}

// FUNC: public: void __thiscall idCVar::SetBool(bool)
void __thiscall idCVar::SetBool(idCVar *this, BOOL value)
{
  this->internalVar->InternalSetBool(this->internalVar, value);
}

// FUNC: public: virtual void __thiscall idWindow::SetBuddy(class idWindow *)
void __thiscall idWindow::SetBuddy(idMapPrimitive *this, idVec3 *delta)
{
  ;
}

// FUNC: public: void __thiscall idCVar::SetInteger(int)
void __thiscall idCVar::SetInteger(idCVar *this, int value)
{
  this->internalVar->InternalSetInteger(this->internalVar, value);
}

// FUNC: public: virtual __thiscall idCVarSystem::~idCVarSystem(void)
void __thiscall idCVarSystem::~idCVarSystem(idCVarSystem *this)
{
  this->__vftable = (idCVarSystem_vtbl *)&idCVarSystem::`vftable';
}
