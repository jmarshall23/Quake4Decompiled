
// FUNC: public: virtual char const * __thiscall idDemoFile::GetName(void)
const char *__thiscall idDemoFile::GetName(idDemoFile *this)
{
  if ( this->f )
    return this->f->GetName(this->f);
  else
    return &entityFilter;
}

// FUNC: public: virtual char const * __thiscall idDemoFile::GetFullPath(void)
const char *__thiscall idDemoFile::GetFullPath(idDemoFile *this)
{
  if ( this->f )
    return this->f->GetFullPath(this->f);
  else
    return &entityFilter;
}
