
// FUNC: public: virtual __thiscall idDecl::~idDecl(void)
void __thiscall idDecl::~idDecl(idDecl *this)
{
  this->__vftable = (idDecl_vtbl *)&idDecl::`vftable';
}

// FUNC: public: virtual bool __thiscall idDecl::SetDefaultText(void)
int __thiscall idDecl::SetDefaultText(idDecl *this)
{
  return ((int (__thiscall *)(idDeclBase *))this->base->SetDefaultText)(this->base);
}

// FUNC: public: virtual char const * __thiscall idDecl::DefaultDefinition(void)const
const char *__thiscall idDecl::DefaultDefinition(idDecl *this)
{
  return this->base->DefaultDefinition(this->base);
}

// FUNC: public: virtual bool __thiscall idDecl::Parse(char const *,int,bool)
int __thiscall idDecl::Parse(idDecl *this, const char *text, int textLength, int noCaching)
{
  return ((int (__thiscall *)(idDeclBase *, const char *, int, int))this->base->Parse)(
           this->base,
           text,
           textLength,
           noCaching);
}

// FUNC: public: virtual void __thiscall idDecl::FreeData(void)
void __thiscall idDecl::FreeData(idDecl *this)
{
  this->base->FreeData(this->base);
}

// FUNC: public: virtual unsigned int __thiscall idDecl::Size(void)const
unsigned int __thiscall idDecl::Size(idDecl *this)
{
  return this->base->Size(this->base);
}

// FUNC: public: virtual void __thiscall idDecl::List(void)const
void __thiscall idDecl::List(idDecl *this)
{
  this->base->List(this->base);
}

// FUNC: public: virtual void __thiscall idDecl::Print(void)const
void __thiscall idDecl::Print(idDecl *this)
{
  this->base->Print(this->base);
}

// FUNC: public: virtual bool __thiscall idDecl::RebuildTextSource(void)
int __thiscall idDecl::RebuildTextSource(idDecl *this)
{
  return ((int (__thiscall *)(idDeclBase *))this->base->RebuildTextSource)(this->base);
}

// FUNC: public: virtual void __thiscall idDecl::SetReferencedThisLevel(void)
void __thiscall idDecl::SetReferencedThisLevel(idDecl *this)
{
  this->base->SetReferencedThisLevel(this->base);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idDeclTable>(void)
void __cdecl idDeclAllocator<idDeclTable>()
{
  idDeclTable *v0; // eax

  v0 = (idDeclTable *)Memory::Allocate(0x24u);
  if ( v0 )
    idDeclTable::idDeclTable(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idMaterial>(void)
void __cdecl idDeclAllocator<idMaterial>()
{
  idMaterial *v0; // eax

  v0 = (idMaterial *)Memory::Allocate(0x14Cu);
  if ( v0 )
    idMaterial::idMaterial(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idDeclSkin>(void)
void __cdecl idDeclAllocator<idDeclSkin>()
{
  idDeclSkin *v0; // eax

  v0 = (idDeclSkin *)Memory::Allocate(0x28u);
  if ( v0 )
    idDeclSkin::idDeclSkin(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idDeclEntityDef>(void)
void __cdecl idDeclAllocator<idDeclEntityDef>()
{
  idDeclEntityDef *v0; // eax

  v0 = (idDeclEntityDef *)Memory::Allocate(0x34u);
  if ( v0 )
    idDeclEntityDef::idDeclEntityDef(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class rvDeclPlayback>(void)
void __cdecl idDeclAllocator<rvDeclPlayback>()
{
  rvDeclPlayback *v0; // eax

  v0 = (rvDeclPlayback *)Memory::Allocate(0xB8u);
  if ( v0 )
    rvDeclPlayback::rvDeclPlayback(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idDeclAF>(void)
void __cdecl idDeclAllocator<idDeclAF>()
{
  idDeclAF *v0; // eax

  v0 = (idDeclAF *)Memory::Allocate(0xB0u);
  if ( v0 )
    idDeclAF::idDeclAF(v0);
}

// FUNC: void __cdecl idListDecls_f<0>(class idCmdArgs const &)
void __cdecl idListDecls_f<0>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_TABLE);
}

// FUNC: void __cdecl idListDecls_f<1>(class idCmdArgs const &)
void __cdecl idListDecls_f<1>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_MATERIAL);
}

// FUNC: void __cdecl idListDecls_f<2>(class idCmdArgs const &)
void __cdecl idListDecls_f<2>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_SKIN);
}

// FUNC: void __cdecl idListDecls_f<3>(class idCmdArgs const &)
void __cdecl idListDecls_f<3>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_SOUND);
}

// FUNC: void __cdecl idListDecls_f<4>(class idCmdArgs const &)
void __cdecl idListDecls_f<4>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_ENTITYDEF);
}

// FUNC: void __cdecl idListDecls_f<11>(class idCmdArgs const &)
void __cdecl idListDecls_f<11>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_AF);
}

// FUNC: void __cdecl idListDecls_f<12>(class idCmdArgs const &)
void __cdecl idListDecls_f<12>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_PDA);
}

// FUNC: void __cdecl idListDecls_f<15>(class idCmdArgs const &)
void __cdecl idListDecls_f<15>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_EMAIL);
}

// FUNC: void __cdecl idListDecls_f<13>(class idCmdArgs const &)
void __cdecl idListDecls_f<13>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_VIDEO);
}

// FUNC: void __cdecl idListDecls_f<14>(class idCmdArgs const &)
void __cdecl idListDecls_f<14>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_AUDIO);
}

// FUNC: void __cdecl idListDecls_f<6>(class idCmdArgs const &)
void __cdecl idListDecls_f<6>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_MATERIALTYPE);
}

// FUNC: void __cdecl idListDecls_f<7>(class idCmdArgs const &)
void __cdecl idListDecls_f<7>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_LIPSYNC);
}

// FUNC: void __cdecl idListDecls_f<8>(class idCmdArgs const &)
void __cdecl idListDecls_f<8>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_PLAYBACK);
}

// FUNC: void __cdecl idListDecls_f<9>(class idCmdArgs const &)
void __cdecl idListDecls_f<9>(const idCmdArgs *args)
{
  declManager->ListType(declManager, args, DECL_EFFECT);
}

// FUNC: void __cdecl idPrintDecls_f<0>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<0>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_TABLE);
}

// FUNC: void __cdecl idPrintDecls_f<1>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<1>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_MATERIAL);
}

// FUNC: void __cdecl idPrintDecls_f<2>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<2>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_SKIN);
}

// FUNC: void __cdecl idPrintDecls_f<3>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<3>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_SOUND);
}

// FUNC: void __cdecl idPrintDecls_f<4>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<4>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_ENTITYDEF);
}

// FUNC: void __cdecl idPrintDecls_f<11>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<11>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_AF);
}

// FUNC: void __cdecl idPrintDecls_f<12>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<12>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_PDA);
}

// FUNC: void __cdecl idPrintDecls_f<15>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<15>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_EMAIL);
}

// FUNC: void __cdecl idPrintDecls_f<13>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<13>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_VIDEO);
}

// FUNC: void __cdecl idPrintDecls_f<14>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<14>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_AUDIO);
}

// FUNC: void __cdecl idPrintDecls_f<6>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<6>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_MATERIALTYPE);
}

// FUNC: void __cdecl idPrintDecls_f<7>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<7>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_LIPSYNC);
}

// FUNC: void __cdecl idPrintDecls_f<8>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<8>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_PLAYBACK);
}

// FUNC: void __cdecl idPrintDecls_f<9>(class idCmdArgs const &)
void __cdecl idPrintDecls_f<9>(const idCmdArgs *args)
{
  declManager->PrintType(declManager, args, DECL_EFFECT);
}

// FUNC: public: virtual __thiscall idDeclBase::~idDeclBase(void)
void __thiscall idDeclBase::~idDeclBase(idDeclBase *this)
{
  this->__vftable = (idDeclBase_vtbl *)&idDeclBase::`vftable';
}

// FUNC: public: virtual __thiscall idDeclManager::~idDeclManager(void)
void __thiscall idDeclManager::~idDeclManager(idDeclManager *this)
{
  this->__vftable = (idDeclManager_vtbl *)&idDeclManager::`vftable';
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class rvDeclMatType>(void)
idDecl *__cdecl idDeclAllocator<rvDeclMatType>()
{
  idDecl *result; // eax

  result = (idDecl *)Memory::Allocate(0x2Cu);
  if ( !result )
    return 0;
  result->base = 0;
  result->__vftable = (idDecl_vtbl *)&rvDeclMatType::`vftable';
  result[1].__vftable = 0;
  result[2].__vftable = (idDecl_vtbl *)20;
  result[1].base = (idDeclBase *)&result[2].base;
  LOBYTE(result[2].base) = 0;
  result[5].__vftable = 0;
  return result;
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idDeclEmail>(void)
void __cdecl idDeclAllocator<idDeclEmail>()
{
  idDeclEmail *v0; // eax

  v0 = (idDeclEmail *)Memory::Allocate(0xC8u);
  if ( v0 )
    idDeclEmail::idDeclEmail(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idDeclVideo>(void)
void __cdecl idDeclAllocator<idDeclVideo>()
{
  idDeclVideo *v0; // eax

  v0 = (idDeclVideo *)Memory::Allocate(0xA8u);
  if ( v0 )
    idDeclVideo::idDeclVideo(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idDeclAudio>(void)
idDecl *__cdecl idDeclAllocator<idDeclAudio>()
{
  idDecl *result; // eax

  result = (idDecl *)Memory::Allocate(0x88u);
  if ( !result )
    return 0;
  result->base = 0;
  result->__vftable = (idDecl_vtbl *)&idDeclAudio::`vftable';
  result[1].__vftable = 0;
  result[2].__vftable = (idDecl_vtbl *)20;
  result[1].base = (idDeclBase *)&result[2].base;
  LOBYTE(result[2].base) = 0;
  result[6].__vftable = (idDecl_vtbl *)20;
  result[5].__vftable = 0;
  result[5].base = (idDeclBase *)&result[6].base;
  LOBYTE(result[6].base) = 0;
  result[10].__vftable = (idDecl_vtbl *)20;
  result[9].__vftable = 0;
  result[9].base = (idDeclBase *)&result[10].base;
  LOBYTE(result[10].base) = 0;
  result[14].__vftable = (idDecl_vtbl *)20;
  result[13].__vftable = 0;
  result[13].base = (idDeclBase *)&result[14].base;
  LOBYTE(result[14].base) = 0;
  return result;
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class rvDeclLipSync>(void)
void __cdecl idDeclAllocator<rvDeclLipSync>()
{
  rvDeclLipSync *v0; // eax

  v0 = (rvDeclLipSync *)Memory::Allocate(0x94u);
  if ( v0 )
    rvDeclLipSync::rvDeclLipSync(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idSoundShader>(void)
void __cdecl idDeclAllocator<idSoundShader>()
{
  idSoundShader *v0; // eax

  v0 = (idSoundShader *)Memory::Allocate(0x180u);
  if ( v0 )
    idSoundShader::idSoundShader(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class rvDeclEffect>(void)
void __cdecl idDeclAllocator<rvDeclEffect>()
{
  rvDeclEffect *v0; // eax

  v0 = (rvDeclEffect *)Memory::Allocate(0x34u);
  if ( v0 )
    rvDeclEffect::rvDeclEffect(v0);
}

// FUNC: class idDecl * __cdecl idDeclAllocator<class idDeclPDA>(void)
void __cdecl idDeclAllocator<idDeclPDA>()
{
  idDeclPDA *v0; // eax

  v0 = (idDeclPDA *)Memory::Allocate(0x120u);
  if ( v0 )
    idDeclPDA::idDeclPDA(v0);
}
