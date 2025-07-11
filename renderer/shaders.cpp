
// FUNC: public: __thiscall rvShader::rvShader(unsigned int,char const *)
void __thiscall rvShader::rvShader(rvShader *this, unsigned int initTarget, const char *initName)
{
  this->__vftable = (rvShader_vtbl *)&rvShader::`vftable';
  this->target = initTarget;
  this->ident = rvNewShaderStage::NumShaders;
  strcpy(this->name, initName);
}

// FUNC: public: static bool __cdecl rvNewShaderStage::AddShaderProgram(class rvShader *)
int __cdecl rvNewShaderStage::AddShaderProgram(rvShader *shaderProg)
{
  int v1; // eax

  v1 = rvNewShaderStage::NumShaders;
  rvNewShaderStage::ShaderList[rvNewShaderStage::NumShaders] = shaderProg;
  rvNewShaderStage::NumShaders = v1 + 1;
  return ((int (__thiscall *)(rvShader *))shaderProg->LoadProgram)(shaderProg);
}

// FUNC: public: virtual void __thiscall rvNewShaderStage::UnBind(void)
void __thiscall rvNewShaderStage::UnBind(rvNewShaderStage *this)
{
  int v2; // esi
  int *textureParmLocations; // edi
  char (*textureParmNames)[32]; // ebp

  v2 = 0;
  textureParmLocations = this->textureParmLocations;
  textureParmNames = this->textureParmNames;
  do
  {
    if ( !*(_BYTE *)textureParmNames )
      break;
    this->shaderProgram->UnBindTexture(
      this->shaderProgram,
      *textureParmLocations,
      v2++,
      (idImage *)*(textureParmLocations - 8));
    ++textureParmLocations;
    ++textureParmNames;
  }
  while ( v2 < 8 );
  GL_SelectTexture(0);
  this->shaderProgram->UnBind(this->shaderProgram);
}

// FUNC: public: virtual void __thiscall rvNewShaderStage::Shutdown(void)
void __thiscall rvNewShaderStage::Shutdown(rvNewShaderStage *this)
{
  this->shaderProgram = 0;
}

// FUNC: public: void __thiscall rvNewShaderStage::BindShaderTextureConstant(int,int,struct drawInteraction_t const *)
void __thiscall rvNewShaderStage::BindShaderTextureConstant(
        rvNewShaderStage *this,
        int slot,
        int bindingType,
        const drawInteraction_t *din)
{
  idImage *lightFalloffImage; // edx

  if ( din )
  {
    if ( bindingType == 1 )
    {
      lightFalloffImage = din->lightFalloffImage;
      if ( !lightFalloffImage )
        return;
      goto LABEL_7;
    }
    if ( bindingType == 2 )
    {
      lightFalloffImage = din->lightImage;
      if ( lightFalloffImage )
LABEL_7:
        this->shaderProgram->SetTexture(this->shaderProgram, this->textureParmLocations[slot], slot, lightFalloffImage);
    }
  }
}

// FUNC: public: void __thiscall rvNewShaderStage::SetTextureParm(char const *,class idImage *)
void __thiscall rvNewShaderStage::SetTextureParm(rvNewShaderStage *this, const char *Name, idImage *Image)
{
  int v4; // esi
  char (*i)[32]; // edi

  v4 = 0;
  for ( i = this->textureParmNames; idStr::Icmp(Name, (const char *)i); ++i )
  {
    if ( ++v4 >= 8 )
      return;
  }
  this->textureParmImages[v4] = Image;
}

// FUNC: public: int __thiscall rvNewShaderStage::FindShaderParameter(char const *)
int __thiscall rvNewShaderStage::FindShaderParameter(rvNewShaderStage *this, const char *Name)
{
  int v2; // esi
  char (*i)[32]; // edi

  v2 = 0;
  for ( i = this->shaderParmNames; idStr::Icmp(Name, (const char *)i); ++i )
  {
    if ( ++v2 >= 96 )
      return -1;
  }
  return v2;
}

// FUNC: public: void __thiscall rvNewShaderStage::SetShaderParameter(int,float *,float const *,int)
void __thiscall rvNewShaderStage::SetShaderParameter(
        rvNewShaderStage *this,
        int Index,
        float *Registers,
        const float *floatVector,
        int arraySize)
{
  int v5; // eax
  const float *v6; // edx
  int v7; // edi
  int v8; // esi
  const float *v9; // edx
  unsigned int v10; // edi
  int *v11; // eax
  int v12; // ecx
  float v13; // ebp
  int *v14; // eax
  float v15; // ebp
  int v16; // ecx
  rvNewShaderStage *v17; // [esp+0h] [ebp-4h]

  v5 = Index;
  v17 = this;
  if ( Index >= 0 )
  {
    v6 = floatVector;
    v7 = arraySize;
    v8 = 0;
    if ( arraySize >= 4 )
    {
      v9 = floatVector + 2;
      v10 = ((unsigned int)(arraySize - 4) >> 2) + 1;
      v11 = &this->shaderParmRegisters[Index][1];
      v8 = 4 * v10;
      do
      {
        Registers[*(v11 - 1)] = *(v9 - 2);
        Registers[*v11] = *(v9 - 1);
        Registers[v11[1]] = *v9;
        v12 = v11[2];
        v13 = v9[1];
        v11 += 4;
        v9 += 4;
        --v10;
        Registers[v12] = v13;
      }
      while ( v10 );
      this = v17;
      v7 = arraySize;
      v6 = floatVector;
      v5 = Index;
    }
    if ( v8 < v7 )
    {
      v14 = &this->shaderParmRegisters[v5][v8];
      do
      {
        v15 = v6[v8];
        v16 = *v14;
        ++v8;
        ++v14;
        Registers[v16] = v15;
      }
      while ( v8 < v7 );
    }
  }
}

// FUNC: void __cdecl CalculateGaussianCoefficients(int,int,float)
void __cdecl CalculateGaussianCoefficients(int width, int height, float multiplier)
{
  int v3; // eax
  double v4; // st7
  int v5; // edi
  double v6; // st7
  int v7; // ebx
  unsigned int v8; // esi
  int v9; // ecx
  double v10; // st6
  idVec4 *v11; // eax
  double v12; // st5
  idVec4 *v13; // edx
  double v14; // st3
  bool v17; // zf
  bool v18; // sf
  bool v19; // of
  int v20; // edx
  double v21; // st6
  unsigned int v22; // ecx
  float *p_z; // eax
  double v24; // st7
  float *v25; // eax
  int v26; // edi
  float tu; // [esp+0h] [ebp-28h]
  float tv; // [esp+4h] [ebp-24h]
  float v29; // [esp+8h] [ebp-20h]
  float v30; // [esp+Ch] [ebp-1Ch]
  float v31; // [esp+18h] [ebp-10h]
  int widtha; // [esp+2Ch] [ebp+4h]
  int x; // [esp+30h] [ebp+8h]

  v3 = -2;
  v4 = 1.0 / (double)width;
  v5 = 0;
  widtha = -2;
  tu = v4;
  tv = 1.0 / (double)height;
  v6 = 0.0;
  do
  {
    v7 = -2;
    v8 = abs32(v3);
    x = -2;
    v9 = v5;
    do
    {
      if ( (int)(v8 + abs32(v7)) <= 2 )
      {
        v10 = (double)widtha;
        v11 = &gaussianSampleOffsets[v9];
        ++v5;
        v29 = tu * v10;
        v12 = (double)x;
        v11->x = v29;
        v30 = tv * v12;
        v11->y = v30;
        v11->z = 0.0;
        v11->w = 0.0;
        v13 = &gaussianSampleWeights[v9++];
        v14 = (v10 * v10 + v12 * v12) * -0.5 * 1.442695040888963387;
        _ST2 = v14;
        __asm { frndint }
        v31 = __FSCALE__(__F2XM1__(v14 - _ST2) + 1.0, _ST2) * (1.0 / sqrt(3.1415927 + 3.1415927));
        v13->x = v31;
        v13->y = v31;
        v13->z = v31;
        v13->w = v31;
        v6 = v6 + v13->x;
      }
      x = ++v7;
    }
    while ( v7 <= 2 );
    v3 = widtha + 1;
    v19 = __OFSUB__(widtha + 1, 2);
    v17 = widtha == 1;
    v18 = widtha++ - 1 < 0;
  }
  while ( v18 ^ v19 | v17 );
  v20 = 0;
  if ( v5 >= 4 )
  {
    v21 = 1.0 / v6;
    v22 = ((unsigned int)(v5 - 4) >> 2) + 1;
    p_z = &gaussianSampleWeights[0].z;
    v20 = 4 * v22;
    do
    {
      *(p_z - 2) = v21 * *(p_z - 2);
      *(p_z - 1) = v21 * *(p_z - 1);
      *p_z = v21 * *p_z;
      p_z[1] = v21 * p_z[1];
      *(p_z - 2) = multiplier * *(p_z - 2);
      *(p_z - 1) = multiplier * *(p_z - 1);
      *p_z = multiplier * *p_z;
      p_z[1] = multiplier * p_z[1];
      p_z[2] = v21 * p_z[2];
      p_z[3] = v21 * p_z[3];
      p_z[4] = v21 * p_z[4];
      p_z[5] = v21 * p_z[5];
      p_z[2] = multiplier * p_z[2];
      p_z[3] = multiplier * p_z[3];
      p_z[4] = multiplier * p_z[4];
      p_z[5] = multiplier * p_z[5];
      p_z[6] = v21 * p_z[6];
      p_z[7] = v21 * p_z[7];
      p_z[8] = v21 * p_z[8];
      p_z[9] = v21 * p_z[9];
      p_z[6] = multiplier * p_z[6];
      p_z[7] = multiplier * p_z[7];
      p_z[8] = multiplier * p_z[8];
      p_z[9] = multiplier * p_z[9];
      p_z[10] = v21 * p_z[10];
      p_z[11] = v21 * p_z[11];
      p_z[12] = v21 * p_z[12];
      p_z += 16;
      --v22;
      *(p_z - 3) = v21 * *(p_z - 3);
      *(p_z - 6) = multiplier * *(p_z - 6);
      *(p_z - 5) = multiplier * *(p_z - 5);
      *(p_z - 4) = multiplier * *(p_z - 4);
      *(p_z - 3) = multiplier * *(p_z - 3);
    }
    while ( v22 );
  }
  if ( v20 < v5 )
  {
    v24 = 1.0 / v6;
    v25 = &gaussianSampleWeights[v20].z;
    v26 = v5 - v20;
    do
    {
      v25 += 4;
      --v26;
      *(v25 - 6) = v24 * *(v25 - 6);
      *(v25 - 5) = v24 * *(v25 - 5);
      *(v25 - 4) = v24 * *(v25 - 4);
      *(v25 - 3) = v24 * *(v25 - 3);
      *(v25 - 6) = multiplier * *(v25 - 6);
      *(v25 - 5) = multiplier * *(v25 - 5);
      *(v25 - 4) = multiplier * *(v25 - 4);
      *(v25 - 3) = multiplier * *(v25 - 3);
    }
    while ( v26 );
  }
}

// FUNC: void __cdecl CalculateGaussianCoefficients1D(int,float,float,float *,class idVec4 *)
void __cdecl CalculateGaussianCoefficients1D(
        int size,
        float multiplier,
        float deviation,
        float *sampleOffsets,
        idVec4 *sampleWeights)
{
  double v6; // st6
  int v9; // eax
  float *v10; // ebp
  int v11; // ecx
  bool v12; // cc
  idVec4 *v13; // edx
  double v14; // st7
  double v15; // st6
  int v18; // ebx
  int v19; // esi
  float *v20; // ebp
  idVec4 *v21; // edx
  idVec4 *v22; // esi
  unsigned int v23; // ecx
  _DWORD *p_x; // ebx
  _DWORD *v25; // ebx
  float *v26; // edx
  idVec4 *v27; // ecx
  idVec4 *v28; // eax
  float tu; // [esp+0h] [ebp-14h]
  float *tua; // [esp+0h] [ebp-14h]
  float v31; // [esp+4h] [ebp-10h]
  float v32; // [esp+4h] [ebp-10h]
  int sizea; // [esp+18h] [ebp+4h]
  int sizeb; // [esp+18h] [ebp+4h]
  int sizec; // [esp+18h] [ebp+4h]
  idVec4 *sampleWeightsa; // [esp+28h] [ebp+14h]

  tu = 1.0 / (double)size;
  if ( sampleWeights )
  {
    v6 = 0.0 / (deviation * deviation + deviation * deviation) * 1.442695040888963387;
    _ST5 = v6;
    __asm { frndint }
    v31 = 1.0
        / sqrt(3.1415927 * deviation * deviation + 3.1415927 * deviation * deviation)
        * __FSCALE__(__F2XM1__(v6 - _ST5) + 1.0, _ST5)
        * multiplier;
    sampleWeights->x = v31;
    sampleWeights->y = v31;
    sampleWeights->z = v31;
    sampleWeights->w = 1.0;
  }
  v9 = halfMaxSamples;
  v10 = sampleOffsets;
  v11 = 1;
  v12 = halfMaxSamples <= 1;
  *sampleOffsets = 0.0;
  sizea = 1;
  if ( !v12 )
  {
    v13 = sampleWeights + 1;
    do
    {
      v14 = (double)sizea;
      sampleOffsets[v11] = tu * v14;
      if ( sampleWeights )
      {
        v15 = -(v14 * v14 / (deviation * deviation + deviation * deviation)) * 1.442695040888963387;
        _ST5 = v15;
        __asm { frndint }
        v32 = __FSCALE__(__F2XM1__(v15 - _ST5) + 1.0, _ST5)
            * (1.0
             / sqrt(3.1415927 * deviation * deviation + 3.1415927 * deviation * deviation))
            * multiplier;
        v13->x = v32;
        v13->y = v32;
        v13->z = v32;
        v13->w = 1.0;
      }
      ++v11;
      ++v13;
      sizea = v11;
    }
    while ( v11 < v9 );
  }
  if ( (_S9_1 & 1) == 0 )
  {
    _S9_1 |= 1u;
    halfMinusOne = v9 - 1;
  }
  v18 = v9;
  if ( 15 - v9 >= 4 )
  {
    sampleWeightsa = (idVec4 *)&sampleOffsets[v9 + 2];
    v19 = v9 - halfMinusOne + 2;
    v20 = &sampleOffsets[v19];
    v21 = &sampleWeights[v9 + 2];
    v22 = &sampleWeights[v19];
    v23 = ((unsigned int)(11 - v9) >> 2) + 1;
    v18 = v9 + 4 * v23;
    tua = v20;
    sizeb = v18;
    do
    {
      sampleWeightsa[-1].z = -*(v20 - 2);
      if ( sampleWeights )
      {
        p_x = (_DWORD *)&v21[-2].x;
        *p_x = LODWORD(v22[-2].x);
        p_x[1] = LODWORD(v22[-2].y);
        p_x[2] = LODWORD(v22[-2].z);
        p_x[3] = LODWORD(v22[-2].w);
        v18 = sizeb;
      }
      sampleWeightsa[-1].w = -*(tua - 1);
      if ( sampleWeights )
      {
        v25 = (_DWORD *)&v21[-1].x;
        *v25 = LODWORD(v22[-1].x);
        v25[1] = LODWORD(v22[-1].y);
        v25[2] = LODWORD(v22[-1].z);
        v25[3] = LODWORD(v22[-1].w);
        v18 = sizeb;
      }
      sampleWeightsa->x = -*tua;
      if ( sampleWeights )
      {
        v21->x = v22->x;
        v21->y = v22->y;
        v21->z = v22->z;
        v21->w = v22->w;
        v18 = sizeb;
      }
      sampleWeightsa->y = -tua[1];
      if ( sampleWeights )
      {
        v21[1].x = v22[1].x;
        v21[1].y = v22[1].y;
        v21[1].z = v22[1].z;
        v21[1].w = v22[1].w;
        v18 = sizeb;
      }
      ++sampleWeightsa;
      v20 = tua + 4;
      v21 += 4;
      v22 += 4;
      --v23;
      tua += 4;
    }
    while ( v23 );
    v10 = sampleOffsets;
  }
  if ( v18 < 15 )
  {
    v26 = &v10[v18 - halfMinusOne];
    v27 = &sampleWeights[v18];
    v28 = &sampleWeights[v18 - halfMinusOne];
    sizec = (int)v26;
    while ( 1 )
    {
      v10[v18] = -*v26;
      if ( sampleWeights )
      {
        v27->x = v28->x;
        v27->y = v28->y;
        v27->z = v28->z;
        v27->w = v28->w;
      }
      ++v18;
      v26 = (float *)(sizec + 4);
      ++v28;
      ++v27;
      sizec += 4;
      if ( v18 >= 15 )
        break;
      v10 = sampleOffsets;
    }
  }
}

// FUNC: public: static class rvShader * __cdecl rvNewShaderStage::FindShaderProgram(char const *)
rvShader *__cdecl rvNewShaderStage::FindShaderProgram(const char *program)
{
  const char *v1; // eax
  int v2; // edi
  int v3; // eax
  char *data; // edx
  const char *v5; // ecx
  char v6; // al
  const char *v7; // eax
  int v8; // edi
  int v9; // eax
  char *v10; // edx
  const char *v11; // ecx
  char v12; // al
  int v13; // ebp
  rvShader *v14; // esi
  bool v15; // zf
  const char *name; // esi
  unsigned int v17; // eax
  int v18; // edi
  int v19; // eax
  char *v20; // edx
  const char *v21; // ecx
  char v22; // al
  int v23; // eax
  rvShader *v25; // esi
  idStr compare; // [esp+10h] [ebp-6Ch] BYREF
  idStr stripped; // [esp+30h] [ebp-4Ch] BYREF
  idStr full; // [esp+50h] [ebp-2Ch] BYREF
  int v29; // [esp+78h] [ebp-4h]

  stripped.len = 0;
  stripped.alloced = 20;
  stripped.data = stripped.baseBuffer;
  stripped.baseBuffer[0] = 0;
  if ( program )
  {
    v1 = &program[strlen(program) + 1];
    v2 = v1 - (program + 1);
    v3 = v1 - program;
    if ( v3 > 20 )
      idStr::ReAllocate(&stripped, v3, 1);
    data = stripped.data;
    v5 = program;
    do
    {
      v6 = *v5;
      *data++ = *v5++;
    }
    while ( v6 );
    stripped.len = v2;
  }
  v29 = 0;
  full.len = 0;
  full.alloced = 20;
  full.data = full.baseBuffer;
  full.baseBuffer[0] = 0;
  if ( program )
  {
    v7 = &program[strlen(program) + 1];
    v8 = v7 - (program + 1);
    v9 = v7 - program;
    if ( v9 > 20 )
      idStr::ReAllocate(&full, v9, 1);
    v10 = full.data;
    v11 = program;
    do
    {
      v12 = *v11;
      *v10++ = *v11++;
    }
    while ( v12 );
    full.len = v8;
  }
  LOBYTE(v29) = 1;
  idStr::StripFileExtension(&stripped);
  v13 = 0;
  if ( rvNewShaderStage::NumShaders > 0 )
  {
    do
    {
      v14 = rvNewShaderStage::ShaderList[v13];
      v15 = v14->name == 0;
      name = v14->name;
      compare.len = 0;
      compare.alloced = 20;
      compare.data = compare.baseBuffer;
      compare.baseBuffer[0] = 0;
      if ( !v15 )
      {
        v17 = (unsigned int)&name[strlen(name) + 1];
        v18 = v17 - (_DWORD)(name + 1);
        v19 = v17 - (_DWORD)name;
        if ( v19 > 20 )
          idStr::ReAllocate(&compare, v19, 1);
        v20 = compare.data;
        v21 = name;
        do
        {
          v22 = *v21;
          *v20++ = *v21++;
        }
        while ( v22 );
        compare.len = v18;
      }
      LOBYTE(v29) = 2;
      idStr::StripFileExtension(&compare);
      v23 = idStr::Icmp(stripped.data, compare.data);
      LOBYTE(v29) = 1;
      if ( !v23 )
      {
        v25 = rvNewShaderStage::ShaderList[v13];
        idStr::FreeData(&compare);
        LOBYTE(v29) = 0;
        idStr::FreeData(&full);
        v29 = -1;
        idStr::FreeData(&stripped);
        return v25;
      }
      idStr::FreeData(&compare);
      ++v13;
    }
    while ( v13 < rvNewShaderStage::NumShaders );
    if ( v13 == 200 )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "R_FindShaderProgram: MAX_SHADER_PROGS");
  }
  LOBYTE(v29) = 0;
  idStr::FreeData(&full);
  v29 = -1;
  idStr::FreeData(&stripped);
  return 0;
}

// FUNC: public: static void __cdecl rvNewShaderStage::R_Shaders_Init(void)
void __usercall rvNewShaderStage::R_Shaders_Init(int a1@<edi>)
{
  int v1; // ebp
  int v2; // esi
  int v3; // edi
  int v4; // ebx
  int v5; // eax

  v1 = 0;
  rvNewShaderStage::NumShaders = 0;
  if ( declManager->GetNumDecls(declManager, DECL_MATERIAL) > 0 )
  {
    do
    {
      v2 = ((int (__thiscall *)(idDeclManager *, int, int, _DWORD, int))declManager->DeclByIndex)(
             declManager,
             1,
             v1,
             0,
             a1);
      v3 = 0;
      if ( *(int *)(v2 + 264) > 0 )
      {
        v4 = 0;
        do
        {
          v5 = v4 + *(_DWORD *)(v2 + 272);
          if ( *(_DWORD *)(v5 + 112) )
            (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(v5 + 112) + 4))(*(_DWORD *)(v5 + 112));
          ++v3;
          v4 += 132;
        }
        while ( v3 < *(_DWORD *)(v2 + 264) );
      }
      a1 = 1;
      ++v1;
    }
    while ( v1 < ((int (__thiscall *)(idDeclManager *))declManager->GetNumDecls)(declManager) );
  }
}

// FUNC: public: static void __cdecl rvNewShaderStage::R_Shaders_Shutdown(void)
void __usercall rvNewShaderStage::R_Shaders_Shutdown(int a1@<edi>)
{
  int v1; // ebp
  int i; // esi
  rvShader *v3; // ecx
  int v4; // esi
  int v5; // edi
  int v6; // ebx
  int v7; // eax

  v1 = 0;
  for ( i = 0; i < rvNewShaderStage::NumShaders; ++i )
  {
    v3 = rvNewShaderStage::ShaderList[i];
    if ( v3 )
      ((void (__thiscall *)(rvShader *, int))v3->~rvShader)(v3, 1);
    rvNewShaderStage::ShaderList[i] = 0;
  }
  rvNewShaderStage::NumShaders = 0;
  if ( declManager->GetNumDecls(declManager, DECL_MATERIAL) > 0 )
  {
    do
    {
      v4 = ((int (__thiscall *)(idDeclManager *, int, int, _DWORD, int))declManager->DeclByIndex)(
             declManager,
             1,
             v1,
             0,
             a1);
      v5 = 0;
      if ( *(int *)(v4 + 264) > 0 )
      {
        v6 = 0;
        do
        {
          v7 = v6 + *(_DWORD *)(v4 + 272);
          if ( *(_DWORD *)(v7 + 112) )
            (*(void (__thiscall **)(_DWORD))(**(_DWORD **)(v7 + 112) + 20))(*(_DWORD *)(v7 + 112));
          ++v5;
          v6 += 132;
        }
        while ( v5 < *(_DWORD *)(v4 + 264) );
      }
      a1 = 1;
      ++v1;
    }
    while ( v1 < ((int (__thiscall *)(idDeclManager *))declManager->GetNumDecls)(declManager) );
  }
}

// FUNC: public: virtual bool __thiscall rvNewShaderStage::ParseProgram(class idLexer &,class idMaterial *)
bool __thiscall rvNewShaderStage::ParseProgram(rvNewShaderStage *this, idLexer *src, idMaterial *material)
{
  rvNewShaderStage_vtbl *v5; // edx
  bool v6; // bl
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v8; // [esp+5Ch] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v8 = 0;
  if ( idLexer::ReadToken(src, &token) )
  {
    strncpy(this->shaderName, token.data, 0x100u);
    v5 = this->__vftable;
    this->shaderName[255] = 0;
    v6 = v5->IsSupported(this);
    v8 = -1;
    idStr::FreeData(&token);
    return v6;
  }
  else
  {
    v8 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: virtual bool __thiscall rvNewShaderStage::ParseShaderParm(class idLexer &,class idMaterial *)
char __thiscall rvNewShaderStage::ParseShaderParm(rvNewShaderStage *this, idLexer *src, idMaterial *material)
{
  int v4; // edi
  char *v5; // eax
  char *v7; // esi
  int v8; // esi
  int v9; // eax
  int v10; // esi
  int v11; // ebx
  int v12; // eax
  int v13; // ebx
  char *v14; // esi
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v17; // [esp+64h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v17 = 0;
  v4 = 0;
  v5 = this->shaderParmNames[1];
  while ( *(v5 - 32) )
  {
    if ( !*v5 )
    {
      ++v4;
      break;
    }
    if ( !v5[32] )
    {
      v4 += 2;
      break;
    }
    if ( !v5[64] )
    {
      v4 += 3;
      break;
    }
    if ( !v5[96] )
    {
      v4 += 4;
      break;
    }
    if ( !v5[128] )
    {
      v4 += 5;
      break;
    }
    v4 += 6;
    v5 += 192;
    if ( v4 >= 96 )
      goto LABEL_17;
  }
  if ( v4 >= 96 || !idLexer::ReadToken(src, &token) )
  {
LABEL_17:
    v17 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  v7 = (char *)this + 32 * v4;
  strncpy(v7 + 260, token.data, 0x20u);
  v7[291] = 0;
  v8 = 0;
  while ( 1 )
  {
    v9 = idMaterial::ParseExpression(material, src);
    if ( !v8 && v9 < 0 )
      break;
    this->shaderParmRegisters[v4][v8] = v9;
    if ( v8 < 3 )
    {
      if ( !idLexer::ReadToken(src, &token) )
        goto LABEL_34;
      if ( idStr::Cmp(token.data, ",") )
      {
        idLexer::UnreadToken(src, &token);
LABEL_34:
        ++v8;
        goto LABEL_35;
      }
    }
    if ( ++v8 >= 4 )
      goto LABEL_35;
  }
  this->shaderParmRegisters[v4][0] = v9;
  v10 = shaderConstantsNumRegisters[-v9 - 1] - 1;
  v11 = v10 + v4;
  if ( v10 + v4 > 96 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "Shader constant takes more registers than are allowed.");
  if ( v10 )
  {
    v12 = v11 + 1;
    if ( ++v4 < v11 + 1 )
    {
      v13 = v12 - v4;
      v14 = this->shaderParmNames[v4];
      v4 = v12;
      do
      {
        idStr::snPrintf(v14, 32, "x");
        v14 += 32;
        --v13;
      }
      while ( v13 );
    }
  }
  v8 = 1;
LABEL_35:
  this->shaderParmNumRegisters[v4] = v8;
  v17 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: virtual bool __thiscall rvNewShaderStage::ParseTextureParm(class idLexer &,class idMaterial *,enum textureRepeat_t)
char __thiscall rvNewShaderStage::ParseTextureParm(
        rvNewShaderStage *this,
        idLexer *src,
        idMaterial *material,
        textureRepeat_t trpDefault)
{
  int v5; // edi
  char (*textureParmNames)[32]; // eax
  char *v8; // esi
  const char *v10; // eax
  const char *v11; // eax
  idImage *v12; // eax
  textureFilter_t v13; // [esp+8h] [ebp-170h]
  int imageFlags; // [esp+Ch] [ebp-16Ch]
  textureDepth_t td; // [esp+10h] [ebp-168h]
  cubeFiles_t cubeMap; // [esp+14h] [ebp-164h]
  bool allowPicmip; // [esp+18h] [ebp-160h]
  idToken token; // [esp+1Ch] [ebp-15Ch] BYREF
  char imageName[256]; // [esp+6Ch] [ebp-10Ch] BYREF
  int v20; // [esp+174h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v20 = 0;
  v5 = 0;
  textureParmNames = this->textureParmNames;
  while ( *(_BYTE *)textureParmNames )
  {
    ++v5;
    ++textureParmNames;
    if ( v5 >= 8 )
      goto LABEL_6;
  }
  if ( !idLexer::ReadToken(src, &token) )
  {
LABEL_6:
    v20 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  v8 = (char *)this + 32 * v5;
  strncpy(v8 + 5252, token.data, 0x20u);
  v8[5283] = 0;
  imageName[0] = 0;
  v13 = TF_DEFAULT;
  td = TD_DEFAULT;
  allowPicmip = 1;
  cubeMap = CF_2D;
  imageFlags = 0;
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( 1 )
          {
            while ( 1 )
            {
              while ( 1 )
              {
                while ( 1 )
                {
                  while ( 1 )
                  {
                    while ( 1 )
                    {
                      while ( 1 )
                      {
                        while ( 1 )
                        {
                          while ( 1 )
                          {
                            idLexer::ReadTokenOnLine(src, &token);
                            if ( idStr::Icmp(token.data, "nearest") )
                              break;
                            v13 = TF_NEAREST;
                          }
                          if ( idStr::Icmp(token.data, "linear") )
                            break;
                          v13 = TF_LINEAR;
                        }
                        if ( idStr::Icmp(token.data, "clamp") )
                          break;
                        trpDefault = TR_CLAMP;
                      }
                      if ( idStr::Icmp(token.data, "noclamp") )
                        break;
                      trpDefault = TR_REPEAT;
                    }
                    if ( idStr::Icmp(token.data, "zeroclamp") )
                      break;
                    trpDefault = TR_CLAMP_TO_ZERO;
                  }
                  if ( idStr::Icmp(token.data, "alphazeroclamp") )
                    break;
                  trpDefault = TR_CLAMP_TO_ZERO_ALPHA;
                }
                if ( idStr::Icmp(token.data, "mirroredrepeat") )
                  break;
                trpDefault = TR_MIRRORED_REPEAT;
              }
              if ( idStr::Icmp(token.data, "uncompressed") && idStr::Icmp(token.data, "highquality") )
                break;
              if ( !image_ignoreHighQuality.internalVar->integerValue )
                td = TD_HIGH_QUALITY;
            }
            if ( idStr::Icmp(token.data, "forceHighQuality") )
              break;
            td = TD_HIGH_QUALITY;
          }
          if ( idStr::Icmp(token.data, "nopicmip") )
            break;
          allowPicmip = 0;
        }
        if ( idStr::Icmp(token.data, "cubeMap") )
          break;
        cubeMap = CF_NATIVE;
      }
      if ( idStr::Icmp(token.data, "cameraCubeMap") )
        break;
      v10 = R_ParsePastImageProgram(src);
      idStr::Copynz(imageName, v10, 256);
      cubeMap = CF_CAMERA;
    }
    if ( idStr::Icmp(token.data, "nomips") )
      break;
    if ( com_makingBuild.internalVar->integerValue > 1 )
      imageFlags |= 1u;
  }
  if ( idStr::Icmp(token.data, "lightfalloffImage") )
  {
    if ( idStr::Icmp(token.data, "lightImage") )
    {
      if ( idStr::Icmp(token.data, "ambientNormalMap") )
      {
        if ( idStr::Icmp(token.data, "normalCubeMap") )
        {
          if ( idStr::Icmp(token.data, "specularTableImage") )
          {
            idLexer::UnreadToken(src, &token);
            v11 = R_ParsePastImageProgram(src);
            v12 = globalImages->ImageFromFile(globalImages, v11, v13, allowPicmip, trpDefault, td, cubeMap, imageFlags);
            this->textureParmImages[v5] = v12;
            if ( !v12 )
              this->textureParmImages[v5] = globalImages->GetDefaultImage(globalImages);
          }
          else
          {
            this->textureParmLocations[v5] = -5;
            this->textureParmImages[v5] = 0;
          }
        }
        else
        {
          this->textureParmLocations[v5] = -4;
          this->textureParmImages[v5] = 0;
        }
      }
      else
      {
        this->textureParmLocations[v5] = -3;
        this->textureParmImages[v5] = 0;
      }
    }
    else
    {
      this->textureParmLocations[v5] = -2;
      this->textureParmImages[v5] = 0;
    }
  }
  else
  {
    this->textureParmLocations[v5] = -1;
    this->textureParmImages[v5] = 0;
  }
  v20 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: virtual void __thiscall rvNewShaderStage::Bind(float const *,struct drawInteraction_t const *)
void __thiscall rvNewShaderStage::Bind(rvNewShaderStage *this, const float *Registers, const drawInteraction_t *din)
{
  int v4; // edi
  int *textureParmLocations; // ebx
  int v6; // eax
  char (*Registersa)[32]; // [esp+14h] [ebp+4h]

  if ( this->shaderProgram || (this->Resolve(this), !this->invalidShader) )
  {
    this->shaderProgram->Bind(this->shaderProgram);
    this->UpdateShaderParms(this, Registers, din);
    v4 = 0;
    textureParmLocations = this->textureParmLocations;
    Registersa = this->textureParmNames;
    do
    {
      if ( !*(_BYTE *)Registersa )
        break;
      v6 = *textureParmLocations;
      if ( *textureParmLocations >= 0 || *(textureParmLocations - 8) )
        this->shaderProgram->SetTexture(this->shaderProgram, v6, v4, (idImage *)*(textureParmLocations - 8));
      else
        rvNewShaderStage::BindShaderTextureConstant(this, v4, -v6, din);
      ++Registersa;
      ++v4;
      ++textureParmLocations;
    }
    while ( v4 < 8 );
  }
}

// FUNC: public: void __thiscall rvNewShaderStage::BindShaderParameterConstant(int,int,struct drawInteraction_t const *)
void __thiscall rvNewShaderStage::BindShaderParameterConstant(
        rvNewShaderStage *this,
        int slot,
        int bindingType,
        const drawInteraction_t *din)
{
  stageVertexColor_t vertexColor; // eax
  __int32 v6; // eax
  stageVertexColor_t v7; // eax
  __int32 v8; // eax
  double v9; // st7
  int v10; // edi
  double v11; // st7
  int v12; // edi
  double v13; // st7
  int v14; // edi
  float *p_y; // ecx
  float *v16; // eax
  double v17; // st7
  int v18; // edi
  float *v19; // ecx
  float *v20; // eax
  int v21; // edi
  double v22; // st7
  int v23; // edi
  int v24; // [esp+4h] [ebp-104h]
  int v25; // [esp+4h] [ebp-104h]
  int v26; // [esp+4h] [ebp-104h]
  int v27; // [esp+4h] [ebp-104h]
  int v28; // [esp+4h] [ebp-104h]
  idVec4 samples[16]; // [esp+8h] [ebp-100h] BYREF

  switch ( bindingType )
  {
    case 0:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->localLightOrigin, 1);
      return;
    case 1:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->localViewOrigin, 1);
      return;
    case 2:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)din->lightProjection, 1);
      return;
    case 3:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->lightProjection[1], 1);
      return;
    case 4:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->lightProjection[2], 1);
      return;
    case 5:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->lightProjection[3], 1);
      return;
    case 6:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)din->bumpMatrix, 1);
      return;
    case 7:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->bumpMatrix[1], 1);
      return;
    case 8:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)din->diffuseMatrix, 1);
      return;
    case 9:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->diffuseMatrix[1], 1);
      return;
    case 10:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)din->specularMatrix, 1);
      return;
    case 11:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->specularMatrix[1], 1);
      return;
    case 12:
      if ( din )
      {
        vertexColor = din->vertexColor;
        if ( vertexColor == SVC_IGNORE )
          goto LABEL_36;
        v6 = vertexColor - 1;
        if ( !v6 )
          goto LABEL_35;
        if ( v6 == 1 )
          this->BindShaderParameter(this, slot, 4, negOne, 1);
      }
      return;
    case 13:
      if ( !din )
        return;
      v7 = din->vertexColor;
      if ( v7 == SVC_IGNORE )
        goto LABEL_35;
      v8 = v7 - 1;
      if ( v8 )
      {
        if ( v8 == 1 )
LABEL_35:
          this->BindShaderParameter(this, slot, 4, one, 1);
      }
      else
      {
LABEL_36:
        this->BindShaderParameter(this, slot, 4, zero, 1);
      }
      return;
    case 14:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->diffuseColor, 1);
      return;
    case 15:
      if ( din )
        this->BindShaderParameter(this, slot, 4, (const float *)&din->specularColor, 1);
      return;
    case 16:
      this->BindShaderParameter(this, slot, 4, (const float *)&colorMatrix, 1);
      return;
    case 17:
      this->BindShaderParameter(this, slot, 4, (const float *)&colorMatrix.mat[1], 1);
      return;
    case 18:
      this->BindShaderParameter(this, slot, 4, (const float *)&colorMatrix.mat[2], 1);
      return;
    case 19:
      parm[0] = backEnd.viewDef->projectionMatrix[0];
      parm[1] = backEnd.viewDef->projectionMatrix[4];
      parm[2] = backEnd.viewDef->projectionMatrix[8];
      dword_110DAA14 = LODWORD(backEnd.viewDef->projectionMatrix[12]);
      this->BindShaderParameter(this, slot, 4, parm, 1);
      return;
    case 20:
      parm[0] = backEnd.viewDef->projectionMatrix[1];
      parm[1] = backEnd.viewDef->projectionMatrix[5];
      parm[2] = backEnd.viewDef->projectionMatrix[9];
      dword_110DAA14 = LODWORD(backEnd.viewDef->projectionMatrix[13]);
      this->BindShaderParameter(this, slot, 4, parm, 1);
      return;
    case 21:
      parm[0] = backEnd.viewDef->projectionMatrix[2];
      parm[1] = backEnd.viewDef->projectionMatrix[6];
      parm[2] = backEnd.viewDef->projectionMatrix[10];
      dword_110DAA14 = LODWORD(backEnd.viewDef->projectionMatrix[14]);
      this->BindShaderParameter(this, slot, 4, parm, 1);
      return;
    case 22:
      parm[0] = backEnd.viewDef->projectionMatrix[3];
      parm[1] = backEnd.viewDef->projectionMatrix[7];
      parm[2] = backEnd.viewDef->projectionMatrix[11];
      dword_110DAA14 = LODWORD(backEnd.viewDef->projectionMatrix[15]);
      this->BindShaderParameter(this, slot, 4, parm, 1);
      return;
    case 23:
      parm[0] = backEnd.currentSpace->modelMatrix[0];
      parm[1] = backEnd.currentSpace->modelMatrix[4];
      parm[2] = backEnd.currentSpace->modelMatrix[8];
      dword_110DAA14 = LODWORD(backEnd.currentSpace->modelMatrix[12]);
      this->BindShaderParameter(this, slot, 4, parm, 1);
      return;
    case 24:
      parm[0] = backEnd.currentSpace->modelMatrix[1];
      parm[1] = backEnd.currentSpace->modelMatrix[5];
      parm[2] = backEnd.currentSpace->modelMatrix[9];
      dword_110DAA14 = LODWORD(backEnd.currentSpace->modelMatrix[13]);
      this->BindShaderParameter(this, slot, 4, parm, 1);
      return;
    case 25:
      parm[0] = backEnd.currentSpace->modelMatrix[2];
      parm[1] = backEnd.currentSpace->modelMatrix[6];
      parm[2] = backEnd.currentSpace->modelMatrix[10];
      dword_110DAA14 = LODWORD(backEnd.currentSpace->modelMatrix[14]);
      this->BindShaderParameter(this, slot, 4, parm, 1);
      return;
    case 26:
      *(idVec3 *)parm = backEnd.viewDef->renderView.vieworg;
      dword_110DAA14 = 1065353216;
      this->BindShaderParameter(this, slot, 4, parm, 1);
      return;
    case 31:
      if ( !gaussianCoefficientsAlreadyComputed || lastWidth != (double)(backEnd.viewDef->viewport.x2 + 1) )
      {
        v24 = backEnd.viewDef->viewport.x2 + 1;
        gaussianCoefficientsAlreadyComputed = 1;
        v9 = (double)v24;
        lastWidth = v9;
        v10 = (unsigned __int64)v9;
        CalculateGaussianCoefficients(v10, backEnd.viewDef->viewport.y2 + 1, 1.0);
        CalculateGaussianCoefficients1D(v10, 1.0, 3.0, gaussianSampleOffsetsHorizontal, gaussianSampleWeights2);
        CalculateGaussianCoefficients1D(v10, 1.0, 3.0, gaussianSampleOffsetsVertical, 0);
      }
      this->BindShaderParameter(this, slot, 4, (const float *)gaussianSampleOffsets, 15);
      return;
    case 32:
      if ( !gaussianCoefficientsAlreadyComputed || lastWidth != (double)(backEnd.viewDef->viewport.x2 + 1) )
      {
        v25 = backEnd.viewDef->viewport.x2 + 1;
        gaussianCoefficientsAlreadyComputed = 1;
        v11 = (double)v25;
        lastWidth = v11;
        v12 = (unsigned __int64)v11;
        CalculateGaussianCoefficients(v12, backEnd.viewDef->viewport.y2 + 1, 1.0);
        CalculateGaussianCoefficients1D(v12, 1.0, 3.0, gaussianSampleOffsetsHorizontal, gaussianSampleWeights2);
        CalculateGaussianCoefficients1D(v12, 1.0, 3.0, gaussianSampleOffsetsVertical, 0);
      }
      this->BindShaderParameter(this, slot, 4, (const float *)gaussianSampleWeights, 15);
      return;
    case 33:
      if ( !gaussianCoefficientsAlreadyComputed || lastWidth != (double)(backEnd.viewDef->viewport.x2 + 1) )
      {
        v26 = backEnd.viewDef->viewport.x2 + 1;
        gaussianCoefficientsAlreadyComputed = 1;
        v13 = (double)v26;
        lastWidth = v13;
        v14 = (unsigned __int64)v13;
        CalculateGaussianCoefficients(v14, backEnd.viewDef->viewport.y2 + 1, 1.0);
        CalculateGaussianCoefficients1D(v14, 1.0, 3.0, gaussianSampleOffsetsHorizontal, gaussianSampleWeights2);
        CalculateGaussianCoefficients1D(v14, 1.0, 3.0, gaussianSampleOffsetsVertical, 0);
      }
      `vector constructor iterator'(samples, 0x10u, 16, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
      p_y = &samples[0].y;
      v16 = gaussianSampleOffsetsHorizontal;
      do
      {
        *(p_y - 1) = *v16;
        *p_y = 0.0;
        ++v16;
        p_y += 4;
      }
      while ( (int)v16 < (int)&gaussianCoefficientsAlreadyComputed );
      goto LABEL_65;
    case 34:
      if ( !gaussianCoefficientsAlreadyComputed || lastWidth != (double)(backEnd.viewDef->viewport.x2 + 1) )
      {
        v27 = backEnd.viewDef->viewport.x2 + 1;
        gaussianCoefficientsAlreadyComputed = 1;
        v17 = (double)v27;
        lastWidth = v17;
        v18 = (unsigned __int64)v17;
        CalculateGaussianCoefficients(v18, backEnd.viewDef->viewport.y2 + 1, 1.0);
        CalculateGaussianCoefficients1D(v18, 1.0, 3.0, gaussianSampleOffsetsHorizontal, gaussianSampleWeights2);
        CalculateGaussianCoefficients1D(v18, 1.0, 3.0, gaussianSampleOffsetsVertical, 0);
      }
      `vector constructor iterator'(samples, 0x10u, 16, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
      v19 = &samples[0].y;
      v20 = gaussianSampleOffsetsVertical;
      do
      {
        v21 = *(_DWORD *)v20;
        *(v19 - 1) = 0.0;
        *(_DWORD *)v19 = v21;
        ++v20;
        v19 += 4;
      }
      while ( (int)v20 < (int)gaussianSampleOffsetsHorizontal );
LABEL_65:
      this->BindShaderParameter(this, slot, 4, (const float *)samples, 15);
      return;
    case 35:
      if ( !gaussianCoefficientsAlreadyComputed || lastWidth != (double)(backEnd.viewDef->viewport.x2 + 1) )
      {
        v28 = backEnd.viewDef->viewport.x2 + 1;
        gaussianCoefficientsAlreadyComputed = 1;
        v22 = (double)v28;
        lastWidth = v22;
        v23 = (unsigned __int64)v22;
        CalculateGaussianCoefficients(v23, backEnd.viewDef->viewport.y2 + 1, 1.0);
        CalculateGaussianCoefficients1D(v23, 1.0, 3.0, gaussianSampleOffsetsHorizontal, gaussianSampleWeights2);
        CalculateGaussianCoefficients1D(v23, 1.0, 3.0, gaussianSampleOffsetsVertical, 0);
      }
      this->BindShaderParameter(this, slot, 4, (const float *)gaussianSampleWeights2, 15);
      return;
    default:
      return;
  }
}

// FUNC: public: virtual void __thiscall rvNewShaderStage::UpdateShaderParms(float const *,struct drawInteraction_t const *)
void __thiscall rvNewShaderStage::UpdateShaderParms(
        rvNewShaderStage *this,
        const float *Registers,
        const drawInteraction_t *din)
{
  rvNewShaderStage *v3; // edi
  int (*shaderParmRegisters)[4]; // ebp
  int v5; // ebx
  int v6; // eax
  bool v7; // sf
  int v8; // edx
  int v9; // eax
  int *v10; // ecx
  int *v11; // ecx
  char (*shaderParmNames)[32]; // [esp+10h] [ebp-20h]
  int *shaderParmNumRegisters; // [esp+14h] [ebp-1Ch]
  int (*v14)[4]; // [esp+18h] [ebp-18h]
  float data[4]; // [esp+20h] [ebp-10h] BYREF

  v3 = this;
  shaderParmRegisters = this->shaderParmRegisters;
  v5 = 0;
  shaderParmNumRegisters = this->shaderParmNumRegisters;
  v14 = this->shaderParmRegisters;
  shaderParmNames = this->shaderParmNames;
  do
  {
    if ( !*(_BYTE *)shaderParmNames )
      break;
    v6 = (*shaderParmRegisters)[0];
    v7 = (*shaderParmRegisters)[0] < 0;
    memset(data, 0, sizeof(data));
    if ( v7 )
    {
      rvNewShaderStage::BindShaderParameterConstant(v3, v5, -1 - v6, din);
    }
    else
    {
      v8 = *shaderParmNumRegisters;
      v9 = 0;
      if ( *shaderParmNumRegisters >= 4 )
      {
        v10 = &(*shaderParmRegisters)[1];
        do
        {
          data[v9] = Registers[*(v10 - 1)];
          data[v9 + 1] = Registers[*v10];
          data[v9 + 2] = Registers[v10[1]];
          data[v9 + 3] = Registers[v10[2]];
          v9 += 4;
          v10 += 4;
        }
        while ( v9 < v8 - 3 );
        v3 = this;
      }
      if ( v9 < v8 )
      {
        v11 = &v3->shaderParmRegisters[v5][v9];
        do
          data[v9++] = Registers[*v11++];
        while ( v9 < v8 );
      }
      v3->BindShaderParameter(v3, v5, v9, data, 1);
      shaderParmRegisters = v14;
    }
    ++shaderParmNames;
    ++shaderParmNumRegisters;
    ++v5;
    v14 = ++shaderParmRegisters;
  }
  while ( v5 < 96 );
}
