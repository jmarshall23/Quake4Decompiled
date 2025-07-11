
// FUNC: public: __thiscall idRegisterList::~idRegisterList(void)
void __thiscall idRegisterList::~idRegisterList(idRegisterList *this)
{
  idRegister **list; // eax

  idHashIndex::Free(&this->regHash);
  list = this->regs.list;
  if ( list )
    Memory::Free(list);
  this->regs.list = 0;
  this->regs.num = 0;
  this->regs.size = 0;
}
