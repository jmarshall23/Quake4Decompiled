
// FUNC: public: virtual __thiscall idImage::~idImage(void)
void __thiscall idImage::~idImage(idImage *this)
{
  this->__vftable = (idImage_vtbl *)&idImage::`vftable';
  idStr::FreeData(&this->imgName);
  idStr::FreeData(&this->bgl.url.url);
}
