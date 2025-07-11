
// FUNC: public: bool __thiscall idMaterial::IsDrawn(void)const
BOOL __thiscall idMaterial::IsDrawn(idMaterial *this)
{
  return this->numStages > 0 || this->entityGui || this->gui;
}

// FUNC: public: bool __thiscall idMaterial::SurfaceCastsShadow(void)const
BOOL __thiscall idMaterial::SurfaceCastsShadow(idMaterial *this)
{
  int materialFlags; // eax

  materialFlags = this->materialFlags;
  return (materialFlags & 8) != 0 || (materialFlags & 4) == 0;
}

// FUNC: public: bool __thiscall idMaterial::LightCastsShadows(void)const
BOOL __thiscall idMaterial::LightCastsShadows(idMaterial *this)
{
  return (this->materialFlags & 8) != 0
      || !this->fogLight && !this->ambientLight && !this->blendLight && (this->materialFlags & 4) == 0;
}
