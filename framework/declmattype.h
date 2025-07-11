
// FUNC: public: virtual __thiscall rvDeclMatType::~rvDeclMatType(void)
void __thiscall rvDeclMatType::~rvDeclMatType(rvDeclMatType *this)
{
  this->__vftable = (rvDeclMatType_vtbl *)&rvDeclMatType::`vftable';
  idStr::FreeData(&this->mDescription);
  this->__vftable = (rvDeclMatType_vtbl *)&idDecl::`vftable';
}
