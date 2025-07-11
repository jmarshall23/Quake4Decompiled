
// FUNC: public: __thiscall idDeviceContext::~idDeviceContext(void)
void __thiscall idDeviceContext::~idDeviceContext(idDeviceContext *this)
{
  int i; // ebx
  idHashTable<embeddedIcon_s>::hashnode_s *v3; // esi
  idStr *p_key; // ebp
  idRectangle *list; // eax
  idHashTable<embeddedIcon_s>::hashnode_s **heads; // [esp-4h] [ebp-20h]

  for ( i = 0; i < this->icons.tablesize; ++i )
  {
    v3 = this->icons.heads[i];
    while ( v3 )
    {
      p_key = &v3->key;
      v3 = v3->next;
      idStr::FreeData(p_key);
      Memory::Free(p_key);
    }
    this->icons.heads[i] = 0;
  }
  heads = this->icons.heads;
  this->icons.numentries = 0;
  Memory::Free(heads);
  idStr::FreeData(&this->fontLang);
  list = this->clipRects.list;
  if ( list )
    Memory::Free(list);
  this->clipRects.list = 0;
  this->clipRects.num = 0;
  this->clipRects.size = 0;
  idStr::FreeData(&this->fontName);
}
