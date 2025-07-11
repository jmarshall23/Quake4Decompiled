
// FUNC: public: __thiscall idTimeLineEvent::idTimeLineEvent(void)
void __thiscall idTimeLineEvent::idTimeLineEvent(idTimeLineEvent *this)
{
  idGuiScriptList *v2; // eax

  v2 = (idGuiScriptList *)Memory::Allocate(0x10u);
  if ( v2 )
  {
    v2->list.list = 0;
    v2->list.num = 0;
    v2->list.size = 0;
    v2->list.granularity = 4;
    this->event = v2;
  }
  else
  {
    this->event = 0;
  }
}

// FUNC: public: __thiscall rvNamedEvent::rvNamedEvent(char const *)
void __thiscall rvNamedEvent::rvNamedEvent(rvNamedEvent *this, char *name)
{
  idGuiScriptList *v3; // eax

  this->mName.len = 0;
  this->mName.alloced = 20;
  this->mName.data = this->mName.baseBuffer;
  this->mName.baseBuffer[0] = 0;
  v3 = (idGuiScriptList *)Memory::Allocate(0x10u);
  if ( v3 )
  {
    v3->list.list = 0;
    v3->list.num = 0;
    v3->list.size = 0;
    v3->list.granularity = 4;
  }
  else
  {
    v3 = 0;
  }
  this->mEvent = v3;
  idStr::operator=(&this->mName, name);
}

// FUNC: public: __thiscall rvNamedEvent::~rvNamedEvent(void)
void __thiscall rvNamedEvent::~rvNamedEvent(rvNamedEvent *this)
{
  idGuiScriptList *mEvent; // esi

  mEvent = this->mEvent;
  if ( mEvent )
  {
    idGuiScriptList::~idGuiScriptList(mEvent);
    Memory::Free(mEvent);
  }
  idStr::FreeData(&this->mName);
}
