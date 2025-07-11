
// FUNC: public: virtual void __thiscall idAASFileManagerLocal::FreeAAS(class idAASFile *)
void __thiscall idAASFileManagerLocal::FreeAAS(idUserInterfaceManagerLocal *this, idListGUI *listgui)
{
  if ( listgui )
    ((void (__thiscall *)(idListGUI *, int))listgui->~idListGUI)(listgui, 1);
}

// FUNC: public: virtual __thiscall idAASFileManagerLocal::~idAASFileManagerLocal(void)
void __thiscall idAASFileManagerLocal::~idAASFileManagerLocal(idAASFileManagerLocal *this)
{
  this->__vftable = (idAASFileManagerLocal_vtbl *)&idAASFileManager::`vftable';
}

// FUNC: public: virtual class idAASFile * __thiscall idAASFileManagerLocal::LoadAAS(char const *,unsigned int)
idAASFile *__thiscall idAASFileManagerLocal::LoadAAS(
        idAASFileManagerLocal *this,
        const char *fileName,
        unsigned int mapFileCRC)
{
  idAASFileLocal *v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // ebp
  const char *v6; // eax
  int v7; // edi
  int v8; // eax
  char *data; // edx
  const char *v10; // ecx
  char v11; // al
  void (__thiscall **v12)(_DWORD *, int); // edx
  bool v13; // bl
  idStr v15; // [esp+Ch] [ebp-2Ch] BYREF
  int v16; // [esp+34h] [ebp-4h]

  v3 = (idAASFileLocal *)Memory::Allocate(0x230u);
  v16 = 0;
  if ( v3 )
  {
    idAASFileLocal::idAASFileLocal(v3);
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  v16 = -1;
  v15.len = 0;
  v15.alloced = 20;
  v15.data = v15.baseBuffer;
  v15.baseBuffer[0] = 0;
  if ( fileName )
  {
    v6 = &fileName[strlen(fileName) + 1];
    v7 = v6 - (fileName + 1);
    v8 = v6 - fileName;
    if ( v8 > 20 )
      idStr::ReAllocate(&v15, v8, 1);
    data = v15.data;
    v10 = fileName;
    do
    {
      v11 = *v10;
      *data++ = *v10++;
    }
    while ( v11 );
    v15.len = v7;
  }
  v12 = (void (__thiscall **)(_DWORD *, int))*v5;
  v16 = 1;
  v13 = ((unsigned __int8 (__thiscall *)(_DWORD *, idStr *, unsigned int))v12[68])(v5, &v15, mapFileCRC) == 0;
  v16 = -1;
  idStr::FreeData(&v15);
  if ( !v13 )
    return (idAASFile *)v5;
  (*(void (__thiscall **)(_DWORD *, int))*v5)(v5, 1);
  return 0;
}
