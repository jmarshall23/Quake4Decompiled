
// FUNC: public: char const * __thiscall idMapFile::GetName(void)const
char *__thiscall idMapFile::GetName(idMapFile *this)
{
  return this->name.data;
}

// FUNC: public: class idList<class idStr> const & __thiscall idFileList::GetList(void)const
const idList<idStr> *__thiscall idFileList::GetList(idFileList *this)
{
  return &this->list;
}

// FUNC: public: virtual __thiscall idFileSystem::~idFileSystem(void)
void __thiscall idFileSystem::~idFileSystem(idFileSystem *this)
{
  this->__vftable = (idFileSystem_vtbl *)&idFileSystem::`vftable';
}
