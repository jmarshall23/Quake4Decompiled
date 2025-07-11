
// FUNC: public: virtual __thiscall rvGLSLShader::~rvGLSLShader(void)
void __thiscall rvGLSLShader::~rvGLSLShader(rvGLSLShader *this)
{
  this->__vftable = (rvGLSLShader_vtbl *)&rvGLSLShader::`vftable';
  qglDetachObjectARB(this->program, this->vertexShader);
  qglDetachObjectARB(this->program, this->fragmentShader);
  qglDeleteObjectARB(this->vertexShader);
  qglDeleteObjectARB(this->fragmentShader);
  qglDeleteObjectARB(this->program);
  this->__vftable = (rvGLSLShader_vtbl *)&rvShader::`vftable';
}

// FUNC: void __cdecl ErrorWithInfoLog(unsigned int,char const *)
void __cdecl ErrorWithInfoLog(unsigned int obj, const char *name)
{
  const char *v2; // esi
  int v3; // eax
  void *v4; // esp
  const char *v5; // edi
  char v6[12]; // [esp+0h] [ebp-18h] BYREF
  int charsWritten; // [esp+Ch] [ebp-Ch] BYREF
  int objectSubtype; // [esp+10h] [ebp-8h] BYREF
  int infologLength; // [esp+14h] [ebp-4h] BYREF

  v2 = 0;
  infologLength = 0;
  objectSubtype = 0;
  charsWritten = 0;
  qglGetObjectParameterivARB(obj, 0x8B84u, &infologLength);
  if ( infologLength > 0 )
  {
    v3 = infologLength + 3;
    LOBYTE(v3) = (infologLength + 3) & 0xFC;
    v4 = alloca(v3);
    v2 = v6;
    if ( v6 )
      qglGetInfoLogARB(obj, infologLength, &charsWritten, v6);
  }
  qglGetObjectParameterivARB(obj, 0x8B4Fu, &objectSubtype);
  if ( objectSubtype == 35633 )
  {
    v5 = "vertex";
  }
  else
  {
    v5 = "fragment";
    if ( objectSubtype != 35632 )
      v5 = "unknown";
  }
  if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 96))(common.type) )
  {
    if ( !v2 )
      v2 = "Unknown error";
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Failed to compile %s shader %s:\n%s",
      v5,
      name,
      v2);
  }
  else
  {
    if ( !v2 )
      v2 = "Unknown error";
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
      common.type,
      "Failed to compile %s shader %s:\n%s",
      v5,
      name,
      v2);
  }
}

// FUNC: public: virtual unsigned int __thiscall rvGLSLShader::GetVariablePosition(char const *)
int __thiscall rvGLSLShader::GetVariablePosition(rvGLSLShader *this, const char *Name)
{
  return qglGetUniformLocationARB(this->program, Name);
}

// FUNC: public: virtual void __thiscall rvGLSLShader::Bind(void)
void __thiscall rvGLSLShader::Bind(rvGLSLShader *this)
{
  qglUseProgramObjectARB(this->program);
}

// FUNC: public: virtual void __thiscall rvGLSLShader::SetTexture(int,int,class idImage *)
void __thiscall rvGLSLShader::SetTexture(rvGLSLShader *this, int Position, int Unit, idImage *Image)
{
  GL_SelectTexture(Unit);
  Image->Bind(Image);
  qglUniform1iARB(Position, Unit);
}

// FUNC: public: virtual void __thiscall rvGLSLShader::UnBindTexture(int,int,class idImage *)
void __thiscall rvGLSLShader::UnBindTexture(rvGLSLShader *this, int Position, int Unit, idImage *Image)
{
  GL_SelectTexture(Unit);
  Image->UnBind(Image);
  globalImages->BindNull(globalImages);
}

// FUNC: public: virtual void __thiscall rvGLSLShader::UnBind(void)
void __thiscall rvGLSLShader::UnBind(rvGLSLShader *this)
{
  qglUseProgramObjectARB(0);
}

// FUNC: public: __thiscall rvGLSLShaderStage::rvGLSLShaderStage(void)
void __thiscall rvGLSLShaderStage::rvGLSLShaderStage(rvGLSLShaderStage *this)
{
  this->__vftable = (rvGLSLShaderStage_vtbl *)&rvGLSLShaderStage::`vftable';
  this->shaderName[0] = 0;
  memset(this->shaderParmNames, 0, sizeof(this->shaderParmNames));
  memset(this->shaderParmLocations, 0, sizeof(this->shaderParmLocations));
  memset(this->shaderParmRegisters, 0xFFu, sizeof(this->shaderParmRegisters));
  memset(this->shaderParmNumRegisters, 0, sizeof(this->shaderParmNumRegisters));
  memset(this->textureParmNames, 0, sizeof(this->textureParmNames));
  this->textureParmLocations[0] = -1;
  this->textureParmLocations[1] = -1;
  this->textureParmLocations[2] = -1;
  this->textureParmLocations[3] = -1;
  this->textureParmLocations[4] = -1;
  this->textureParmLocations[5] = -1;
  this->textureParmLocations[6] = -1;
  this->textureParmLocations[7] = -1;
  this->textureParmImages[0] = 0;
  this->textureParmImages[1] = 0;
  this->textureParmImages[2] = 0;
  this->textureParmImages[3] = 0;
  this->textureParmImages[4] = 0;
  this->textureParmImages[5] = 0;
  this->textureParmImages[6] = 0;
  this->textureParmImages[7] = 0;
  this->shaderProgram = 0;
  this->invalidShader = 0;
}

// FUNC: public: virtual void __thiscall rvGLSLShaderStage::Resolve(void)
void __thiscall rvGLSLShaderStage::Resolve(rvGLSLShaderStage *this)
{
  rvShader *ShaderProgram; // eax
  rvShader *v3; // eax
  rvShader *v4; // edi
  int v5; // ebx
  int *shaderParmLocations; // ebp
  const char *v7; // edi
  int v8; // ebp
  int *textureParmLocations; // ebx
  const char *v10; // edi

  if ( this->IsSupported(this) )
  {
    ShaderProgram = rvNewShaderStage::FindShaderProgram(this->shaderName);
    this->shaderProgram = ShaderProgram;
    if ( ShaderProgram
      || ((v3 = (rvShader *)Memory::Allocate(0x58u), (v4 = v3) == 0)
        ? (v4 = 0)
        : (rvShader *)(rvShader::rvShader(v3, 0, this->shaderName),
                       v4->__vftable = (rvShader_vtbl *)&rvGLSLShader::`vftable'),
          this->shaderProgram = v4,
          rvNewShaderStage::AddShaderProgram(v4)) )
    {
      this->invalidShader = 0;
      v5 = 0;
      shaderParmLocations = this->shaderParmLocations;
      v7 = this->shaderParmNames[0];
      do
      {
        if ( !*v7 )
          break;
        *shaderParmLocations = this->shaderProgram->GetVariablePosition(this->shaderProgram, v7);
        ++v5;
        ++shaderParmLocations;
        v7 += 32;
      }
      while ( v5 < 96 );
      v8 = 0;
      textureParmLocations = this->textureParmLocations;
      v10 = this->textureParmNames[0];
      do
      {
        if ( !*v10 )
          break;
        *textureParmLocations = this->shaderProgram->GetVariablePosition(this->shaderProgram, v10);
        ++v8;
        ++textureParmLocations;
        v10 += 32;
      }
      while ( v8 < 8 );
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "Invalid GLSL shader '%s'\n",
        this->shaderName);
      this->invalidShader = 1;
    }
  }
  else
  {
    this->shaderProgram = 0;
    this->invalidShader = 1;
  }
}

// FUNC: public: virtual void __thiscall rvGLSLShaderStage::BindShaderParameter(int,int,float const *,int)
void __thiscall rvGLSLShaderStage::BindShaderParameter(
        rvGLSLShaderStage *this,
        int slot,
        int numParms,
        const float *floatVector,
        int arraySize)
{
  switch ( numParms )
  {
    case 1:
      qglUniform1fvARB(this->shaderParmLocations[slot], arraySize, floatVector);
      break;
    case 2:
      qglUniform2fvARB(this->shaderParmLocations[slot], arraySize, floatVector);
      break;
    case 3:
      qglUniform3fvARB(this->shaderParmLocations[slot], arraySize, floatVector);
      break;
    case 4:
      qglUniform4fvARB(this->shaderParmLocations[slot], arraySize, floatVector);
      break;
    default:
      return;
  }
}

// FUNC: public: virtual bool __thiscall rvGLSLShader::LoadProgram(void)
char __thiscall rvGLSLShader::LoadProgram(rvGLSLShader *this)
{
  int v2; // eax
  char v3; // cl
  char *v4; // eax
  int v5; // esi
  int v6; // eax
  char v7; // cl
  int i; // eax
  char *v9; // edx
  idStr *v10; // esi
  unsigned int len; // ebx
  int v12; // eax
  idStr *v13; // esi
  unsigned int v14; // ebx
  int v15; // eax
  unsigned int ShaderObjectARB; // eax
  bool v17; // cf
  unsigned int Error; // esi
  unsigned int v19; // esi
  unsigned int ProgramObjectARB; // eax
  unsigned int v21; // esi
  unsigned int vertexShader; // [esp+Ch] [ebp-94h]
  int status; // [esp+20h] [ebp-80h] BYREF
  char *vertexBuffer; // [esp+24h] [ebp-7Ch] BYREF
  char *fragmentBuffer; // [esp+28h] [ebp-78h] BYREF
  int vertexLength; // [esp+2Ch] [ebp-74h] BYREF
  int fragmentLength; // [esp+30h] [ebp-70h] BYREF
  idStr fileName; // [esp+34h] [ebp-6Ch] BYREF
  idStr fullPath; // [esp+54h] [ebp-4Ch] BYREF
  idStr result; // [esp+74h] [ebp-2Ch] BYREF
  int v32; // [esp+9Ch] [ebp-4h]

  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  fullPath.alloced = 20;
  v32 = 0;
  vertexBuffer = 0;
  vertexLength = 0;
  fragmentBuffer = 0;
  fragmentLength = 0;
  fullPath.data = fullPath.baseBuffer;
  fullPath.baseBuffer[0] = 0;
  v2 = 0;
  do
  {
    v3 = aGlprogs[v2];
    fullPath.baseBuffer[v2++] = v3;
  }
  while ( v3 );
  fullPath.len = 8;
  LOBYTE(v32) = 1;
  if ( this != (rvGLSLShader *)-12 )
  {
    v4 = &this->name[strlen(this->name) + 1];
    v5 = v4 - &this->name[1] + 8;
    v6 = v4 - &this->name[1] + 9;
    if ( v6 > fullPath.alloced )
      idStr::ReAllocate(&fullPath, v6, 1);
    v7 = this->name[0];
    for ( i = 0; v7; v7 = this->name[i] )
    {
      v9 = &fullPath.data[i++];
      v9[fullPath.len] = v7;
    }
    fullPath.len = v5;
    fullPath.data[v5] = 0;
  }
  v10 = operator+(&result, &fullPath, "vp");
  len = v10->len;
  v12 = v10->len + 1;
  LOBYTE(v32) = 2;
  if ( v12 > fileName.alloced )
    idStr::ReAllocate(&fileName, v12, 0);
  qmemcpy(fileName.data, v10->data, len);
  fileName.data[len] = 0;
  fileName.len = len;
  LOBYTE(v32) = 1;
  idStr::FreeData(&result);
  fileSystem->ReadFile(fileSystem, fileName.data, (void **)&vertexBuffer, 0);
  if ( !vertexBuffer )
    goto LABEL_15;
  v13 = operator+(&result, &fullPath, "fp");
  v14 = v13->len;
  v15 = v13->len + 1;
  LOBYTE(v32) = 3;
  if ( v15 > fileName.alloced )
    idStr::ReAllocate(&fileName, v15, 0);
  qmemcpy(fileName.data, v13->data, v14);
  fileName.data[v14] = 0;
  fileName.len = v14;
  LOBYTE(v32) = 1;
  idStr::FreeData(&result);
  fileSystem->ReadFile(fileSystem, fileName.data, (void **)&fragmentBuffer, 0);
  if ( fragmentBuffer )
  {
    status = 0;
    this->vertexShader = qglCreateShaderObjectARB(0x8B31u);
    ShaderObjectARB = qglCreateShaderObjectARB(0x8B30u);
    v17 = vertexLength != 0;
    this->fragmentShader = ShaderObjectARB;
    qglShaderSourceARB(this->vertexShader, 1, (const char **)&vertexBuffer, v17 ? &vertexLength : 0);
    qglShaderSourceARB(
      this->fragmentShader,
      1,
      (const char **)&fragmentBuffer,
      fragmentLength != 0 ? &fragmentLength : 0);
    fileSystem->FreeFile(fileSystem, vertexBuffer);
    fileSystem->FreeFile(fileSystem, fragmentBuffer);
    qglGetError();
    qglCompileShaderARB(this->vertexShader);
    Error = qglGetError();
    qglGetObjectParameterivARB(this->vertexShader, 0x8B81u, &status);
    if ( Error || !status )
    {
      ErrorWithInfoLog(this->vertexShader, this->name);
    }
    else
    {
      qglCompileShaderARB(this->fragmentShader);
      v19 = qglGetError();
      qglGetObjectParameterivARB(this->fragmentShader, 0x8B81u, &status);
      if ( v19 || !status )
      {
        ErrorWithInfoLog(this->fragmentShader, this->name);
      }
      else
      {
        ProgramObjectARB = qglCreateProgramObjectARB();
        vertexShader = this->vertexShader;
        this->program = ProgramObjectARB;
        qglAttachObjectARB(ProgramObjectARB, vertexShader);
        qglAttachObjectARB(this->program, this->fragmentShader);
        qglLinkProgramARB(this->program);
        v21 = qglGetError();
        qglGetObjectParameterivARB(this->program, 0x8B82u, &status);
        if ( !v21 && status )
        {
          LOBYTE(v32) = 0;
          idStr::FreeData(&fullPath);
          v32 = -1;
          idStr::FreeData(&fileName);
          return 1;
        }
        ErrorWithInfoLog(this->program, this->name);
      }
    }
  }
  else
  {
LABEL_15:
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, ": File not found\n");
  }
  LOBYTE(v32) = 0;
  idStr::FreeData(&fullPath);
  v32 = -1;
  idStr::FreeData(&fileName);
  return 0;
}
