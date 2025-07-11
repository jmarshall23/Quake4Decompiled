
// FUNC: public: virtual unsigned int __thiscall idEditWindow::Allocated(void)
// attributes: thunk
unsigned int __thiscall idEditWindow::Allocated(idBindWindow *this)
{
  return idWindow::Allocated(this);
}

// FUNC: public: virtual class idWindow * __thiscall idSliderWindow::GetBuddy(void)
idWindow *__thiscall idSliderWindow::GetBuddy(idSliderWindow *this)
{
  return this->buddyWin;
}
