
// FUNC: public: virtual class idUserInterface * __thiscall idSessionLocal::GetActiveGUI(void)
idUserInterface *__thiscall idSessionLocal::GetActiveGUI(idSessionLocal *this)
{
  return this->guiActive;
}

// FUNC: public: virtual bool __thiscall idSessionLocal::GetMapSpawned(void)
bool __thiscall idSessionLocal::GetMapSpawned(idSessionLocal *this)
{
  return this->mapSpawned;
}

// FUNC: public: virtual bool __thiscall idSessionLocal::GetLoadingSaveGame(void)
bool __thiscall idSessionLocal::GetLoadingSaveGame(idSessionLocal *this)
{
  return this->loadingSaveGame;
}

// FUNC: public: char const * __thiscall rvLanguage::GetLanguage(void)const
char *__thiscall rvLanguage::GetLanguage(rvLanguage *this)
{
  return this->language.data;
}
