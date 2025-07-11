
// FUNC: public: virtual void __thiscall idRenderModelStatic::InitEmptyFromArgs(char const *,class idDict &)
void __thiscall idRenderModelStatic::InitEmptyFromArgs(idRenderModelStatic *this, const char *name, idDict *Args)
{
  this->InitEmpty(this, name);
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::SetHasSky(bool)
void __thiscall idRenderModelStatic::SetHasSky(idRenderModelStatic *this, bool on)
{
  this->hasSky = on;
}

// FUNC: public: virtual bool __thiscall idRenderModelStatic::GetHasSky(void)const
bool __thiscall idRenderModelStatic::GetHasSky(idRenderModelStatic *this)
{
  return this->hasSky;
}

// FUNC: public: virtual void __thiscall idRenderModelMD5::SetViewEntity(struct viewEntity_s const *)
void __thiscall idRenderModelMD5::SetViewEntity(idRenderModelMD5 *this, const viewEntity_s *ve)
{
  this->viewEnt = ve;
}

// FUNC: public: __thiscall rvRenderModelBSE::rvRenderModelBSE(void)
void __thiscall rvRenderModelBSE::rvRenderModelBSE(rvRenderModelBSE *this)
{
  idRenderModelStatic::idRenderModelStatic(this);
  this->__vftable = (rvRenderModelBSE_vtbl *)&rvRenderModelBSE::`vftable';
  this->bounds.b[0].z = idMath::INFINITY;
  this->bounds.b[0].y = idMath::INFINITY;
  this->bounds.b[0].x = idMath::INFINITY;
  this->bounds.b[1].z = -1.0e30;
  this->bounds.b[1].y = -1.0e30;
  this->bounds.b[1].x = -1.0e30;
}

// FUNC: public: virtual void __thiscall rvRenderModelBSE::InitFromFile(char const *)
void __thiscall rvRenderModelBSE::InitFromFile(rvRenderModelBSE *this, char *fileName)
{
  idStr::operator=(&this->name, fileName);
}

// FUNC: public: virtual __thiscall rvRenderModelBSE::~rvRenderModelBSE(void)
void __thiscall rvRenderModelBSE::~rvRenderModelBSE(rvRenderModelBSE *this)
{
  this->__vftable = (rvRenderModelBSE_vtbl *)&rvRenderModelBSE::`vftable';
  idRenderModelStatic::~idRenderModelStatic(this);
}
