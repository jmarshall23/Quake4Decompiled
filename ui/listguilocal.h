
// FUNC: public: __thiscall idListGUILocal::idListGUILocal(void)
void __thiscall idListGUILocal::idListGUILocal(idListGUILocal *this)
{
  this->granularity = 16;
  this->list = 0;
  this->num = 0;
  this->size = 0;
  this->__vftable = (idListGUILocal_vtbl *)&idListGUILocal::`vftable';
  this->m_name.len = 0;
  this->m_name.alloced = 20;
  this->m_name.data = this->m_name.baseBuffer;
  this->m_name.baseBuffer[0] = 0;
  this->m_ids.granularity = 16;
  this->m_ids.list = 0;
  this->m_ids.num = 0;
  this->m_ids.size = 0;
  this->m_greyed.list = 0;
  this->m_greyed.num = 0;
  this->m_greyed.size = 0;
  this->m_greyed.granularity = 16;
  this->m_pGUI = 0;
  this->m_water = 0;
  this->m_stateUpdates = 1;
}

// FUNC: public: virtual void __thiscall idListGUILocal::Config(class idUserInterface *,char const *)
void __thiscall idListGUILocal::Config(idListGUILocal *this, idUserInterface *pGUI, char *name)
{
  this->m_pGUI = pGUI;
  idStr::operator=(&this->m_name, name);
}
