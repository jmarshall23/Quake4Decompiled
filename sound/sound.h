
// FUNC: public: __thiscall idSoundShader::idSoundShader(void)
void __thiscall idSoundShader::idSoundShader(idSoundShader *this)
{
  this->base = 0;
  this->__vftable = (idSoundShader_vtbl *)&idSoundShader::`vftable';
  this->desc.len = 0;
  this->desc.alloced = 20;
  this->desc.data = this->desc.baseBuffer;
  this->desc.baseBuffer[0] = 0;
  this->shakes.granularity = 16;
  this->shakes.list = 0;
  this->shakes.num = 0;
  this->shakes.size = 0;
  idSoundShader::Init(this);
}

// FUNC: public: virtual int __thiscall idSoundSample::GetMemoryUsed(void)const
char *__thiscall idSoundSample::GetMemoryUsed(idSoundShader *this)
{
  return this->desc.data;
}

// FUNC: public: virtual float __thiscall idSoundShader::GetMinDistance(void)const
double __thiscall idSoundShader::GetMinDistance(idSoundShader *this)
{
  return this->parms.minDistance;
}

// FUNC: public: virtual float __thiscall idSoundShader::GetMaxDistance(void)const
double __thiscall idSoundShader::GetMaxDistance(idSoundShader *this)
{
  return this->parms.maxDistance;
}

// FUNC: public: virtual struct soundShaderParms_t const * __thiscall idSoundShader::GetParms(void)const
const soundShaderParms_t *__thiscall idSoundShader::GetParms(idSoundShader *this)
{
  return &this->parms;
}

// FUNC: public: virtual __thiscall idSoundShader::~idSoundShader(void)
void __thiscall idSoundShader::~idSoundShader(idSoundShader *this)
{
  idStr *list; // eax
  char *v3; // edi

  this->__vftable = (idSoundShader_vtbl *)&idSoundShader::`vftable';
  list = this->shakes.list;
  if ( list )
  {
    v3 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v3);
  }
  this->shakes.list = 0;
  this->shakes.num = 0;
  this->shakes.size = 0;
  idStr::FreeData(&this->desc);
  this->__vftable = (idSoundShader_vtbl *)&idDecl::`vftable';
}

// FUNC: public: virtual float __thiscall rvCommonSample::GetDuration(void)const
double __thiscall rvCommonSample::GetDuration(idCompressor_None *this)
{
  return 0.0;
}

// FUNC: public: virtual __thiscall rvCommonSample::~rvCommonSample(void)
void __thiscall rvCommonSample::~rvCommonSample(rvCommonSample *this)
{
  this->__vftable = (rvCommonSample_vtbl *)&rvCommonSample::`vftable';
  idStr::FreeData(&this->name);
}

// FUNC: public: virtual __thiscall idSoundEmitter::~idSoundEmitter(void)
void __thiscall idSoundEmitter::~idSoundEmitter(idSoundEmitter *this)
{
  this->__vftable = (idSoundEmitter_vtbl *)&idSoundEmitter::`vftable';
}

// FUNC: public: virtual __thiscall idSoundSystem::~idSoundSystem(void)
void __thiscall idSoundSystem::~idSoundSystem(idSoundSystem *this)
{
  this->__vftable = (idSoundSystem_vtbl *)&idSoundSystem::`vftable';
}
