
// FUNC: public: virtual __thiscall rvShader::~rvShader(void)
void __thiscall rvShader::~rvShader(rvShader *this)
{
  this->__vftable = (rvShader_vtbl *)&rvShader::`vftable';
}

// FUNC: public: virtual int __thiscall idFile_ASCII::ReadInt(int &)
int __thiscall idFile_ASCII::ReadInt(idFile_ASCII *this, idMat3 *mat)
{
  return 0;
}

// FUNC: void __cdecl SpawnStub(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnStub()
{
  ;
}

// FUNC: public: virtual bool __thiscall rvNewShaderStage::IsValid(void)
BOOL __thiscall rvNewShaderStage::IsValid(rvNewShaderStage *this)
{
  return !this->invalidShader;
}

// FUNC: public: virtual bool __thiscall rvGLSLShaderStage::IsSupported(void)
bool __thiscall rvGLSLShaderStage::IsSupported(rvGLSLShaderStage *this)
{
  return glConfig.GLSLProgramAvailable;
}
