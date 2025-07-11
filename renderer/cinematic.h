
// FUNC: public: virtual __thiscall idSndWindow::~idSndWindow(void)
void __thiscall idSndWindow::~idSndWindow(idSndWindow *this)
{
  this->__vftable = (idSndWindow_vtbl *)&idSndWindow::`vftable';
  idCinematic::~idCinematic((WMVCinematic *)this);
}
