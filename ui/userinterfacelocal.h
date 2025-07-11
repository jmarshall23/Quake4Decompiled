
// FUNC: public: virtual float __thiscall idUserInterfaceLocal::CursorX(void)
double __thiscall idUserInterfaceLocal::CursorX(idUserInterfaceLocal *this)
{
  return this->cursorX;
}

// FUNC: public: virtual float __thiscall idUserInterfaceLocal::CursorY(void)
double __thiscall idUserInterfaceLocal::CursorY(idUserInterfaceLocal *this)
{
  return this->cursorY;
}

// FUNC: public: virtual class idVec4 __thiscall idUserInterfaceLocal::GetLightColor(void)
idVec4 *__thiscall idUserInterfaceLocal::GetLightColor(idUserInterfaceLocal *this, idVec4 *result)
{
  idWinVec4 *lightColorVar; // eax
  idVec4 *p_data; // ecx
  idVec4 *v4; // eax

  lightColorVar = this->lightColorVar;
  p_data = &lightColorVar->data;
  if ( !lightColorVar )
    p_data = &vec4_origin;
  v4 = result;
  *result = *p_data;
  return v4;
}
