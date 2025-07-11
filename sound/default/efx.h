
// FUNC: public: __thiscall idSoundEffect::~idSoundEffect(void)
void __thiscall idSoundEffect::~idSoundEffect(idSoundEffect *this)
{
  void *data; // eax

  data = this->data;
  if ( data && this->datasize )
  {
    Mem_Free(data);
    this->data = 0;
  }
  idStr::FreeData(&this->name);
}
