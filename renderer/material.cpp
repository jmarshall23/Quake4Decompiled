
// FUNC: private: void __thiscall idMaterial::CommonInit(void)
void __thiscall idMaterial::CommonInit(idMaterial *this)
{
  idStr::operator=(&this->desc, "<none>");
  idStr::operator=(&this->renderBump, (char *)&entityFilter);
  this->portalDistanceNear = 262144.0;
  this->portalDistanceFar = 262144.0;
  this->contentFlags = 1;
  this->allowOverlays = 1;
  this->materialType = 0;
  this->materialTypeArray = 0;
  this->MTAWidth = 0;
  this->MTAHeight = 0;
  this->portalImage = 0;
  this->surfaceFlags = 0;
  this->materialFlags = 0;
  this->sort = -1.0;
  this->coverage = MC_BAD;
  this->cullType = CT_FRONT_SIDED;
  this->deform = DFRM_NONE;
  this->numOps = 0;
  this->ops = 0;
  this->numRegisters = 0;
  this->expressionRegisters = 0;
  this->constantRegisters = 0;
  this->numStages = 0;
  this->numAmbientStages = 0;
  this->stages = 0;
  this->editorImage = 0;
  this->lightFalloffImage = 0;
  this->shouldCreateBackSides = 0;
  this->entityGui = 0;
  this->fogLight = 0;
  this->blendLight = 0;
  this->ambientLight = 0;
  this->noFog = 0;
  this->hasSubview = 0;
  this->unsmoothedTangents = 0;
  this->gui = 0;
  this->deformRegisters[0] = 0;
  this->deformRegisters[1] = 0;
  this->deformRegisters[2] = 0;
  this->deformRegisters[3] = 0;
  this->editorAlpha = 1.0;
  this->spectrum = 0;
  this->polygonOffset = 0.0;
  this->suppressInSubview = 0;
  this->refCount = 0;
  this->portalSky = 0;
  this->decalInfo.stayTime = 10000;
  this->decalInfo.maxAngle = 0.1;
  this->useCount = 0;
}

// FUNC: public: int __thiscall idMaterial::GetTexelCount(void)const
int __thiscall idMaterial::GetTexelCount(idMaterial *this)
{
  int v2; // ebp
  int v3; // ebx
  int v4; // edi
  idImage *image; // ecx

  v2 = 0;
  if ( !this->stages )
    return 0;
  v3 = 0;
  if ( this->numStages <= 0 )
    return 0;
  v4 = 0;
  do
  {
    image = this->stages[v4].texture.image;
    if ( image )
      v2 += idImage::GetTexelCount(image);
    ++v3;
    ++v4;
  }
  while ( v3 < this->numStages );
  return v2;
}

// FUNC: private: void __thiscall idMaterial::SortInteractionStages(void)
void __thiscall idMaterial::SortInteractionStages(idMaterial *this)
{
  int numStages; // eax
  int v3; // esi
  int v4; // edx
  mtrParsingData_s *pd; // edi
  stageLighting_t *p_lighting; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  bool *v10; // edx
  void *v11; // ebx
  const void *v12; // esi
  bool v13; // zf
  int v14; // [esp+10h] [ebp-A0h]
  int j; // [esp+14h] [ebp-9Ch]
  int i; // [esp+18h] [ebp-98h]
  int v17; // [esp+1Ch] [ebp-94h]
  int v18; // [esp+20h] [ebp-90h]
  int v19; // [esp+24h] [ebp-8Ch]
  shaderStage_t temp; // [esp+28h] [ebp-88h] BYREF

  numStages = this->numStages;
  v3 = 0;
  i = 0;
  if ( numStages > 0 )
  {
    while ( 1 )
    {
      v4 = v3 + 1;
      j = v3 + 1;
      if ( v3 + 1 < numStages )
      {
        pd = this->pd;
        p_lighting = &pd->parseStages[v4].lighting;
        do
        {
          if ( *p_lighting == SL_BUMP && pd->parseStages[v3].lighting == SL_BUMP )
            break;
          ++v4;
          p_lighting += 33;
        }
        while ( v4 < numStages );
        j = v4;
      }
      v7 = v4 - v3;
      if ( v4 - v3 > 1 )
      {
        v14 = v4 - 1;
        v8 = v7 - 1;
        v19 = v7 - 1;
        v18 = v7 - 1;
        do
        {
          if ( v3 < v14 )
          {
            v9 = v3;
            v17 = v8;
            do
            {
              if ( this->pd->parseStages[v9].lighting > this->pd->parseStages[v9 + 1].lighting )
              {
                v10 = &this->pd->registerIsTemporary[v9 * 132];
                v11 = v10 + 86016;
                qmemcpy(&temp, v10 + 86016, sizeof(temp));
                v12 = v10 + 86148;
                v4 = j;
                qmemcpy(v11, v12, 0x84u);
                qmemcpy(&this->pd->parseStages[v9 + 1], &temp, sizeof(this->pd->parseStages[v9 + 1]));
                v3 = i;
              }
              ++v9;
              --v17;
            }
            while ( v17 );
            v8 = v19;
          }
          --v14;
          --v8;
          v13 = v18-- == 1;
          v19 = v8;
        }
        while ( !v13 );
      }
      numStages = this->numStages;
      i = v4;
      if ( v4 >= numStages )
        break;
      v3 = v4;
    }
  }
}

// FUNC: public: void __thiscall idMaterial::AddReference(void)
void __thiscall idMaterial::AddReference(idMaterial *this)
{
  int v1; // esi
  int v2; // edx
  idImage *image; // eax

  ++this->refCount;
  v1 = 0;
  if ( this->numStages > 0 )
  {
    v2 = 0;
    do
    {
      image = this->stages[v2].texture.image;
      if ( image )
        ++image->refCount;
      ++v1;
      ++v2;
    }
    while ( v1 < this->numStages );
  }
}

// FUNC: public: enum texgen_t __thiscall idMaterial::Texgen(void)const
texgen_t __thiscall idMaterial::Texgen(idMaterial *this)
{
  shaderStage_t *stages; // esi
  int numStages; // edx
  int v3; // eax
  texgen_t *i; // ecx

  stages = this->stages;
  if ( !stages )
    return 0;
  numStages = this->numStages;
  v3 = 0;
  if ( numStages <= 0 )
    return 0;
  for ( i = &stages->texture.texgen; *i == TG_EXPLICIT; i += 33 )
  {
    if ( ++v3 >= numStages )
      return 0;
  }
  return stages[v3].texture.texgen;
}

// FUNC: public: int __thiscall idMaterial::CinematicLength(void)const
int __thiscall idMaterial::CinematicLength(idMaterial *this)
{
  shaderStage_t *stages; // eax

  stages = this->stages;
  if ( stages && stages->texture.cinematic )
    return stages->texture.cinematic->AnimationLength(stages->texture.cinematic);
  else
    return 0;
}

// FUNC: public: void __thiscall idMaterial::UpdateCinematic(int)const
void __thiscall idMaterial::UpdateCinematic(idMaterial *this, int time)
{
  shaderStage_t *stages; // eax
  cinData_t v3; // [esp+0h] [ebp-10h] BYREF

  stages = this->stages;
  if ( stages && stages->texture.cinematic )
  {
    if ( backEnd.viewDef )
      stages->texture.cinematic->ImageForTime(stages->texture.cinematic, &v3, tr.primaryRenderView.time);
  }
}

// FUNC: public: void __thiscall idMaterial::ResetCinematicTime(int)const
void __thiscall idMaterial::ResetCinematicTime(idMaterial *this, int time)
{
  int v3; // ebx
  int v4; // edi
  shaderStage_t *stages; // eax

  v3 = 0;
  if ( this->numStages > 0 )
  {
    v4 = 0;
    do
    {
      stages = this->stages;
      if ( stages[v4].texture.cinematic )
        stages[v4].texture.cinematic->ResetTime(stages[v4].texture.cinematic, time);
      ++v3;
      ++v4;
    }
    while ( v3 < this->numStages );
  }
}

// FUNC: public: void __thiscall idMaterial::SetImageClassifications(int)const
void __thiscall idMaterial::SetImageClassifications(idMaterial *this, int tag)
{
  int v3; // ebx
  int v4; // edi
  idImage *image; // ecx

  v3 = 0;
  if ( this->numStages > 0 )
  {
    v4 = 0;
    do
    {
      image = this->stages[v4].texture.image;
      if ( image )
        idImage::SetClassification(image, tag);
      ++v3;
      ++v4;
    }
    while ( v3 < this->numStages );
  }
}

// FUNC: public: virtual char const * __thiscall idMaterial::DefaultDefinition(void)const
const char *__thiscall idMaterial::DefaultDefinition(idMaterial *this)
{
  return "{\n\t{\n\t\tblend\tblend\n\t\tmap\t\t_default\n\t}\n}";
}

// FUNC: public: struct shaderStage_t const * __thiscall idMaterial::GetBumpStage(void)const
const shaderStage_t *__thiscall idMaterial::GetBumpStage(idMaterial *this)
{
  int numStages; // edx
  int v2; // eax
  shaderStage_t *stages; // esi
  stageLighting_t *i; // ecx

  numStages = this->numStages;
  v2 = 0;
  if ( numStages <= 0 )
    return 0;
  stages = this->stages;
  for ( i = &stages->lighting; *i != SL_BUMP; i += 33 )
  {
    if ( ++v2 >= numStages )
      return 0;
  }
  return &stages[v2];
}

// FUNC: public: void __thiscall idMaterial::ReloadImages(bool)const
void __thiscall idMaterial::ReloadImages(idMaterial *this, BOOL force)
{
  int v2; // esi
  shaderStage_t *stages; // eax
  newShaderStage_t *newStage; // ecx
  int v6; // ebp
  int v7; // edi
  int v8; // ecx
  idImage *image; // ecx
  int i; // [esp+8h] [ebp-4h]

  v2 = 0;
  for ( i = 0; i < this->numStages; ++i )
  {
    stages = this->stages;
    newStage = stages[v2].newStage;
    if ( newStage )
    {
      v6 = 0;
      if ( newStage->numFragmentProgramImages > 0 )
      {
        v7 = 408;
        do
        {
          if ( *(int *)((char *)&stages[v2].newStage->vertexProgram + v7) )
          {
            v8 = *(int *)((char *)&this->stages[v2].newStage->vertexProgram + v7);
            (*(void (__thiscall **)(int, _DWORD, BOOL))(*(_DWORD *)v8 + 16))(v8, 0, force);
          }
          stages = this->stages;
          ++v6;
          v7 += 4;
        }
        while ( v6 < stages[v2].newStage->numFragmentProgramImages );
      }
    }
    else if ( stages[v2].texture.image )
    {
      image = this->stages[v2].texture.image;
      image->Reload(image, 0, force);
    }
    ++v2;
  }
}

// FUNC: public: void __thiscall idMaterial::ResolveUse(void)
void __thiscall idMaterial::ResolveUse(idMaterial *this)
{
  int v1; // ebx
  int v2; // eax
  shaderStage_t *stages; // edx
  newShaderStage_t *newStage; // esi
  int v5; // edi
  int v6; // esi
  int v7; // edx
  rvNewShaderStage *newShaderStage; // esi
  idImage *v9; // esi
  idImage *v10; // edx
  idImage *v11; // edx
  idImage *v12; // edx
  idImage *v13; // edx
  idImage *v14; // edx
  idImage *v15; // edx
  idImage *image; // edx
  idImage *lightFalloffImage; // eax
  idImage *portalImage; // eax

  v1 = 0;
  if ( this->numStages > 0 )
  {
    v2 = 0;
    do
    {
      stages = this->stages;
      newStage = stages[v2].newStage;
      if ( newStage )
      {
        v5 = 0;
        if ( newStage->numFragmentProgramImages > 0 )
        {
          v6 = 408;
          do
          {
            v7 = *(int *)((char *)&stages[v2].newStage->vertexProgram + v6);
            if ( v7 )
              *(_DWORD *)(v7 + 1236) += this->useCount;
            stages = this->stages;
            ++v5;
            v6 += 4;
          }
          while ( v5 < stages[v2].newStage->numFragmentProgramImages );
        }
      }
      else
      {
        newShaderStage = stages[v2].newShaderStage;
        if ( newShaderStage )
        {
          v9 = newShaderStage->textureParmImages[0];
          if ( v9 )
            v9->useCount += this->useCount;
          v10 = this->stages[v2].newShaderStage->textureParmImages[1];
          if ( v10 )
            v10->useCount += this->useCount;
          v11 = this->stages[v2].newShaderStage->textureParmImages[2];
          if ( v11 )
            v11->useCount += this->useCount;
          v12 = this->stages[v2].newShaderStage->textureParmImages[3];
          if ( v12 )
            v12->useCount += this->useCount;
          v13 = this->stages[v2].newShaderStage->textureParmImages[4];
          if ( v13 )
            v13->useCount += this->useCount;
          v14 = this->stages[v2].newShaderStage->textureParmImages[5];
          if ( v14 )
            v14->useCount += this->useCount;
          v15 = this->stages[v2].newShaderStage->textureParmImages[6];
          if ( v15 )
            v15->useCount += this->useCount;
          image = this->stages[v2].newShaderStage->textureParmImages[7];
        }
        else
        {
          image = stages[v2].texture.image;
        }
        if ( image )
          image->useCount += this->useCount;
      }
      ++v1;
      ++v2;
    }
    while ( v1 < this->numStages );
  }
  lightFalloffImage = this->lightFalloffImage;
  if ( lightFalloffImage )
    lightFalloffImage->useCount += this->useCount;
  portalImage = this->portalImage;
  if ( portalImage )
    portalImage->useCount += this->useCount;
}

// FUNC: public: bool __thiscall idMaterial::HasDefaultedImage(void)const
char __thiscall idMaterial::HasDefaultedImage(idMaterial *this)
{
  int numStages; // esi
  int v2; // edx
  idImage **i; // eax

  numStages = this->numStages;
  v2 = 0;
  if ( numStages <= 0 )
    return 0;
  for ( i = &this->stages->texture.image; !*i || !(*i)->defaulted; i += 33 )
  {
    if ( ++v2 >= numStages )
      return 0;
  }
  return 1;
}

// FUNC: public: __thiscall idMaterial::idMaterial(void)
void __thiscall idMaterial::idMaterial(idMaterial *this)
{
  this->base = 0;
  this->__vftable = (idMaterial_vtbl *)&idMaterial::`vftable';
  this->desc.len = 0;
  this->desc.alloced = 20;
  this->desc.data = this->desc.baseBuffer;
  this->desc.baseBuffer[0] = 0;
  this->renderBump.len = 0;
  this->renderBump.alloced = 20;
  this->renderBump.data = this->renderBump.baseBuffer;
  this->renderBump.baseBuffer[0] = 0;
  this->materialTypeArrayName.len = 0;
  this->materialTypeArrayName.alloced = 20;
  this->materialTypeArrayName.data = this->materialTypeArrayName.baseBuffer;
  this->materialTypeArrayName.baseBuffer[0] = 0;
  this->editorImageName.len = 0;
  this->editorImageName.alloced = 20;
  this->editorImageName.data = this->editorImageName.baseBuffer;
  this->editorImageName.baseBuffer[0] = 0;
  idMaterial::CommonInit(this);
  this->surfaceArea = 0.0;
  this->globalUseCount = 0;
}

// FUNC: public: class rvDeclMatType const * __thiscall idMaterial::GetMaterialType(class idVec2 &)const
const rvDeclMatType *__thiscall idMaterial::GetMaterialType(idMaterial *this, idVec2 *tc)
{
  const rvDeclMatType *result; // eax

  if ( !this->materialTypeArray )
    return this->materialType;
  tc->x = fmod(tc->x, 1.0);
  tc->y = fmod(tc->y, 1.0);
  if ( tc->x < 0.0 )
    tc->x = tc->x + 1.0;
  if ( tc->y < 0.0 )
    tc->y = tc->y + 1.0;
  result = (const rvDeclMatType *)((int (__stdcall *)(int))declManager->DeclByIndex)(6);
  if ( !result )
    return this->materialType;
  return result;
}

// FUNC: public: virtual void __thiscall idMaterial::FreeData(void)
void __thiscall idMaterial::FreeData(idMaterial *this)
{
  int v2; // ebp
  int v3; // edi
  idCinematic *cinematic; // ecx
  shaderStage_t *stages; // ecx
  rvNewShaderStage *newShaderStage; // ecx
  idStr *p_materialTypeArrayName; // esi

  if ( this->stages )
  {
    v2 = 0;
    if ( this->numStages > 0 )
    {
      v3 = 0;
      do
      {
        cinematic = this->stages[v3].texture.cinematic;
        if ( cinematic )
        {
          ((void (__thiscall *)(idCinematic *, int))cinematic->~idCinematic)(cinematic, 1);
          this->stages[v3].texture.cinematic = 0;
        }
        stages = this->stages;
        if ( stages[v3].newStage )
        {
          Mem_Free(stages[v3].newStage);
          this->stages[v3].newStage = 0;
        }
        newShaderStage = this->stages[v3].newShaderStage;
        if ( newShaderStage )
        {
          ((void (__thiscall *)(rvNewShaderStage *, int))newShaderStage->~rvNewShaderStage)(newShaderStage, 1);
          this->stages[v3].newShaderStage = 0;
        }
        ++v2;
        ++v3;
      }
      while ( v2 < this->numStages );
    }
    R_StaticFree(this->stages);
    this->stages = 0;
  }
  if ( this->expressionRegisters )
  {
    R_StaticFree(this->expressionRegisters);
    this->expressionRegisters = 0;
  }
  if ( this->constantRegisters )
  {
    R_StaticFree(this->constantRegisters);
    this->constantRegisters = 0;
  }
  if ( this->ops )
  {
    R_StaticFree(this->ops);
    this->ops = 0;
  }
  if ( this->materialTypeArray )
  {
    Mem_Free(this->materialTypeArray);
    this->materialTypeArray = 0;
    p_materialTypeArrayName = &this->materialTypeArrayName;
    idStr::FreeData(p_materialTypeArrayName);
    p_materialTypeArrayName->len = 0;
    p_materialTypeArrayName->alloced = 20;
    p_materialTypeArrayName->data = p_materialTypeArrayName->baseBuffer;
    p_materialTypeArrayName->baseBuffer[0] = 0;
  }
}

// FUNC: public: class idImage * __thiscall idMaterial::GetEditorImage(void)const
idImage *__thiscall idMaterial::GetEditorImage(idMaterial *this)
{
  idImage *result; // eax
  shaderStage_t *stages; // edi
  int numStages; // edx
  int v5; // eax
  idImage **p_image; // ecx
  int v7; // eax
  stageLighting_t *p_lighting; // ecx

  result = this->editorImage;
  if ( !result )
  {
    if ( this->editorImageName.len )
    {
      this->editorImage = globalImages->ImageFromFile(globalImages, this->editorImageName.data, 2, 1, 0, 2, 0, 0);
    }
    else
    {
      stages = this->stages;
      if ( stages )
      {
        numStages = this->numStages;
        if ( numStages )
        {
          v5 = 0;
          if ( numStages > 0 )
          {
            p_image = &stages->texture.image;
            do
            {
              if ( *(p_image - 10) == (idImage *)2 )
                this->editorImage = *p_image;
              ++v5;
              p_image += 33;
            }
            while ( v5 < this->numStages );
          }
          if ( !this->editorImage )
          {
            v7 = 0;
            if ( numStages > 0 )
            {
              p_lighting = &stages->lighting;
              while ( *p_lighting != SL_DIFFUSE )
              {
                ++v7;
                p_lighting += 33;
                if ( v7 >= this->numStages )
                  goto LABEL_18;
              }
              this->editorImage = stages[v7].texture.image;
            }
LABEL_18:
            if ( !this->editorImage )
              this->editorImage = stages->texture.image;
          }
        }
      }
    }
    if ( !this->editorImage )
      this->editorImage = globalImages->GetDefaultImage(globalImages);
    return this->editorImage;
  }
  return result;
}

// FUNC: private: bool __thiscall idMaterial::CheckSurfaceParm(class idToken *)
char __thiscall idMaterial::CheckSurfaceParm(idMaterial *this, idToken *token)
{
  int v3; // ebx
  infoParm_t *v4; // esi
  int v6; // ebx
  int contentFlags; // eax

  v3 = 0;
  v4 = infoParms;
  while ( idStr::Icmp(token->data, v4->name) )
  {
    ++v4;
    ++v3;
    if ( (int)v4 >= (int)opNames )
      return 0;
  }
  v6 = v3;
  if ( (infoParms[v6].surfaceFlags & 0xF) != 0 )
    this->surfaceFlags &= 0xFFFFFFF0;
  this->surfaceFlags |= infoParms[v6].surfaceFlags;
  this->contentFlags |= infoParms[v6].contents;
  contentFlags = this->contentFlags;
  if ( infoParms[v6].clearSolid )
  {
    LOBYTE(contentFlags) = contentFlags & 0xFE;
    this->contentFlags = contentFlags;
  }
  return 1;
}

// FUNC: private: bool __thiscall idMaterial::MatchToken(class idLexer &,char const *)
char __thiscall idMaterial::MatchToken(idMaterial *this, idLexer *src, const char *match)
{
  if ( idLexer::ExpectTokenString(src, match) )
    return 1;
  this->materialFlags |= 1u;
  return 0;
}

// FUNC: private: void __thiscall idMaterial::ParseSort(class idLexer &)
void __thiscall idMaterial::ParseSort(idMaterial *this, idLexer *src)
{
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v4; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v4 = 0;
  if ( idLexer::ReadTokenOnLine(src, &token) )
  {
    if ( idStr::Icmp(token.data, "subview") )
    {
      if ( idStr::Icmp(token.data, "gui") )
      {
        if ( idStr::Icmp(token.data, "opaque") )
        {
          if ( idStr::Icmp(token.data, "decal") )
          {
            if ( idStr::Icmp(token.data, "far") )
            {
              if ( idStr::Icmp(token.data, "medium") )
              {
                if ( idStr::Icmp(token.data, "close") )
                {
                  if ( idStr::Icmp(token.data, "almostNearest") )
                  {
                    if ( idStr::Icmp(token.data, "nearest") )
                    {
                      if ( idStr::Icmp(token.data, "postProcess") )
                      {
                        if ( idStr::Icmp(token.data, "portalSky") )
                          this->sort = atof(token.data);
                        else
                          this->sort = 1.0;
                      }
                      else
                      {
                        this->sort = 100.0;
                      }
                    }
                    else
                    {
                      this->sort = 7.0;
                    }
                  }
                  else
                  {
                    this->sort = 6.0;
                  }
                }
                else
                {
                  this->sort = 5.0;
                }
              }
              else
              {
                this->sort = 4.0;
              }
            }
            else
            {
              this->sort = 3.0;
            }
          }
          else
          {
            this->sort = 2.0;
          }
        }
        else
        {
          this->sort = 0.0;
        }
      }
      else
      {
        this->sort = -2.0;
      }
    }
    else
    {
      this->sort = -4.0;
    }
  }
  else
  {
    idLexer::Warning(src, "missing sort parameter");
    this->materialFlags |= 1u;
  }
  v4 = -1;
  idStr::FreeData(&token);
}

// FUNC: private: void __thiscall idMaterial::ParseDecalInfo(class idLexer &)
void __thiscall idMaterial::ParseDecalInfo(idMaterial *this, idLexer *src)
{
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v4; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v4 = 0;
  this->decalInfo.stayTime = (int)(idLexer::ParseFloat(src, 0) * 1000.0);
  if ( idLexer::ReadToken(src, &token) )
  {
    if ( idStr::Cmp(token.data, ",") )
      idLexer::UnreadToken(src, &token);
    else
      this->decalInfo.maxAngle = idLexer::ParseFloat(src, 0);
  }
  v4 = -1;
  idStr::FreeData(&token);
}

// FUNC: private: int __thiscall idMaterial::GetExpressionConstant(float)
int __thiscall idMaterial::GetExpressionConstant(idMaterial *this, float f)
{
  int numRegisters; // ebx
  int v4; // ecx
  mtrParsingData_s *pd; // edi
  float *v6; // edx
  int v7; // edi
  const char *v8; // eax

  numRegisters = this->numRegisters;
  v4 = 22;
  if ( numRegisters <= 22 )
  {
LABEL_6:
    if ( numRegisters == 4096 )
    {
      v7 = *(_DWORD *)common.type;
      v8 = this->base->GetName(this->base);
      (*(void (**)(netadrtype_t, const char *, ...))(v7 + 136))(
        common.type,
        "GetExpressionConstant: material '%s' hit MAX_EXPRESSION_REGISTERS",
        v8);
      this->materialFlags |= 1u;
      return 0;
    }
    this->pd->registerIsTemporary[v4] = 0;
    this->pd->shaderRegisters[v4] = f;
    ++this->numRegisters;
  }
  else
  {
    pd = this->pd;
    v6 = &pd->shaderRegisters[22];
    while ( pd->registerIsTemporary[v4] || *v6 != f )
    {
      ++v4;
      ++v6;
      if ( v4 >= this->numRegisters )
        goto LABEL_6;
    }
  }
  return v4;
}

// FUNC: private: int __thiscall idMaterial::GetExpressionTemporary(void)
int __thiscall idMaterial::GetExpressionTemporary(idMaterial *this)
{
  int numRegisters; // eax
  int v3; // edi
  const char *v4; // eax

  numRegisters = this->numRegisters;
  if ( numRegisters == 4096 )
  {
    v3 = *(_DWORD *)common.type;
    v4 = this->base->GetName(this->base);
    (*(void (**)(netadrtype_t, const char *, ...))(v3 + 136))(
      common.type,
      "GetExpressionTemporary: material '%s' hit MAX_EXPRESSION_REGISTERS",
      v4);
    this->materialFlags |= 1u;
    return 0;
  }
  else
  {
    this->pd->registerIsTemporary[numRegisters] = 1;
    return this->numRegisters++;
  }
}

// FUNC: private: struct expOp_t * __thiscall idMaterial::GetExpressionOp(void)
expOp_t *__thiscall idMaterial::GetExpressionOp(idMaterial *this)
{
  int numOps; // ecx
  int v3; // edi
  const char *v4; // eax
  mtrParsingData_s *pd; // eax
  expOp_t *result; // eax

  numOps = this->numOps;
  if ( numOps == 4096 )
  {
    v3 = *(_DWORD *)common.type;
    v4 = this->base->GetName(this->base);
    (*(void (**)(netadrtype_t, const char *, ...))(v3 + 136))(
      common.type,
      "GetExpressionOp: material '%s' hit MAX_EXPRESSION_OPS",
      v4);
    pd = this->pd;
    this->materialFlags |= 1u;
    return pd->shaderOps;
  }
  else
  {
    result = &this->pd->shaderOps[numOps];
    this->numOps = numOps + 1;
  }
  return result;
}

// FUNC: private: int __thiscall idMaterial::EmitOp(int,int,enum expOpType_t)
int __thiscall idMaterial::EmitOp(idMaterial *this, int a, int b, expOpType_t opType)
{
  mtrParsingData_s *pd; // ecx
  bool v7; // dl
  int result; // eax
  mtrParsingData_s *v9; // ecx
  bool v10; // dl
  expOp_t *ExpressionOp; // esi
  float f; // [esp+0h] [ebp-14h]
  float fa; // [esp+0h] [ebp-14h]
  bool aa; // [esp+18h] [ebp+4h]
  bool ab; // [esp+18h] [ebp+4h]

  if ( opType == OP_TYPE_ADD )
  {
    pd = this->pd;
    aa = pd->registerIsTemporary[a];
    if ( aa || pd->shaderRegisters[a] != 0.0 )
    {
      v7 = pd->registerIsTemporary[b];
      if ( v7 || pd->shaderRegisters[b] != 0.0 )
      {
        if ( !aa && !v7 )
        {
          f = this->pd->shaderRegisters[a] + this->pd->shaderRegisters[b];
          return idMaterial::GetExpressionConstant(this, f);
        }
        goto LABEL_22;
      }
      return a;
    }
    return b;
  }
  if ( opType == OP_TYPE_MULTIPLY )
  {
    v9 = this->pd;
    ab = v9->registerIsTemporary[a];
    if ( !ab )
    {
      if ( LODWORD(v9->shaderRegisters[a]) == 1065353216 )
        return b;
      if ( v9->shaderRegisters[a] == 0.0 )
        return a;
    }
    v10 = v9->registerIsTemporary[b];
    if ( !v10 )
    {
      if ( LODWORD(v9->shaderRegisters[b]) == 1065353216 )
        return a;
      if ( v9->shaderRegisters[b] == 0.0 )
        return b;
    }
    if ( !ab && !v10 )
    {
      fa = this->pd->shaderRegisters[a] * this->pd->shaderRegisters[b];
      return idMaterial::GetExpressionConstant(this, fa);
    }
  }
LABEL_22:
  ExpressionOp = idMaterial::GetExpressionOp(this);
  ExpressionOp->opType = opType;
  ExpressionOp->a = a;
  ExpressionOp->b = b;
  result = idMaterial::GetExpressionTemporary(this);
  ExpressionOp->c = result;
  return result;
}

// FUNC: private: int __thiscall idMaterial::ParseEmitOp(class idLexer &,int,enum expOpType_t,int)
int __thiscall idMaterial::ParseEmitOp(idMaterial *this, idLexer *src, int a, expOpType_t opType, int priority)
{
  int v6; // eax

  v6 = idMaterial::ParseExpressionPriority(this, src, priority);
  return idMaterial::EmitOp(this, a, v6, opType);
}

// FUNC: private: int __thiscall idMaterial::ParseTerm(class idLexer &)
int __thiscall idMaterial::ParseTerm(idMaterial *this, idLexer *src)
{
  int v3; // ebx
  int ExpressionConstant; // esi
  int vidWidth; // eax
  expOp_t *ExpressionOp; // edi
  long double floatvalue; // st7
  int i; // ebp
  const idDecl *v10; // ebp
  int v11; // ebx
  int v12; // ebp
  expOp_t *v13; // edi
  float v14; // [esp+0h] [ebp-74h]
  float f; // [esp+4h] [ebp-70h]
  float fa; // [esp+4h] [ebp-70h]
  float fb; // [esp+4h] [ebp-70h]
  float fc; // [esp+4h] [ebp-70h]
  float fd; // [esp+4h] [ebp-70h]
  idToken token; // [esp+18h] [ebp-5Ch] BYREF
  int v21; // [esp+70h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v21 = 0;
  idLexer::ReadToken(src, &token);
  if ( !idStr::Cmp(token.data, "(") )
  {
    v3 = idMaterial::ParseExpressionPriority(this, src, 4);
    if ( !idLexer::ExpectTokenString(src, ")") )
      this->materialFlags |= 1u;
    v21 = -1;
    idStr::FreeData(&token);
    return v3;
  }
  if ( !idStr::Icmp(token.data, "time") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  if ( !idStr::Icmp(token.data, "parm0") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  if ( !idStr::Icmp(token.data, "parm1") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 2;
  }
  if ( !idStr::Icmp(token.data, "parm2") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 3;
  }
  if ( !idStr::Icmp(token.data, "parm3") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 4;
  }
  if ( !idStr::Icmp(token.data, "parm4") )
  {
    this->pd->registersAreConstant = 0;
LABEL_67:
    v21 = -1;
    idStr::FreeData(&token);
    return 5;
  }
  if ( !idStr::Icmp(token.data, "parm5") )
  {
    this->pd->registersAreConstant = 0;
LABEL_70:
    v21 = -1;
    idStr::FreeData(&token);
    return 6;
  }
  if ( !idStr::Icmp(token.data, "parm6") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 7;
  }
  if ( !idStr::Icmp(token.data, "parm7") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 8;
  }
  if ( !idStr::Icmp(token.data, "parm8") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 9;
  }
  if ( !idStr::Icmp(token.data, "parm9") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 10;
  }
  if ( !idStr::Icmp(token.data, "parm10") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 11;
  }
  if ( !idStr::Icmp(token.data, "parm11") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 12;
  }
  if ( !idStr::Icmp(token.data, "global0") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 13;
  }
  if ( !idStr::Icmp(token.data, "global1") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 14;
  }
  if ( !idStr::Icmp(token.data, "global2") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 15;
  }
  if ( !idStr::Icmp(token.data, "global3") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 16;
  }
  if ( !idStr::Icmp(token.data, "global4") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 17;
  }
  if ( !idStr::Icmp(token.data, "global5") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 18;
  }
  if ( !idStr::Icmp(token.data, "global6") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 19;
  }
  if ( !idStr::Icmp(token.data, "global7") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 20;
  }
  if ( !idStr::Icmp(token.data, "IsMultiplayer") )
  {
    f = (float)session->IsMultiplayer(session);
    ExpressionConstant = idMaterial::GetExpressionConstant(this, f);
LABEL_99:
    v21 = -1;
    idStr::FreeData(&token);
    return ExpressionConstant;
  }
  if ( !idStr::Icmp(token.data, "fragmentPrograms") )
  {
    fa = (float)glConfig.ARBFragmentProgramAvailable;
    ExpressionConstant = idMaterial::GetExpressionConstant(this, fa);
    goto LABEL_99;
  }
  if ( !idStr::Icmp(token.data, "POTCorrectionX") )
  {
    vidWidth = glConfig.vidWidth;
LABEL_53:
    fb = (double)vidWidth / (double)MakePowerOfTwo(vidWidth);
    ExpressionConstant = idMaterial::GetExpressionConstant(this, fb);
    goto LABEL_99;
  }
  if ( !idStr::Icmp(token.data, "POTCorrectionY") )
  {
    vidWidth = glConfig.vidHeight;
    goto LABEL_53;
  }
  if ( !idStr::Icmp(token.data, "VideoWidth") )
  {
    fc = (float)glConfig.vidWidth;
    ExpressionConstant = idMaterial::GetExpressionConstant(this, fc);
    goto LABEL_99;
  }
  if ( !idStr::Icmp(token.data, "VideoHeight") )
  {
    fd = (float)glConfig.vidHeight;
    ExpressionConstant = idMaterial::GetExpressionConstant(this, fd);
    goto LABEL_99;
  }
  if ( !idStr::Icmp(token.data, "sound") )
  {
    this->pd->registersAreConstant = 0;
    ExpressionOp = idMaterial::GetExpressionOp(this);
    ExpressionOp->opType = OP_TYPE_SOUND;
LABEL_64:
    ExpressionOp->a = 0;
    ExpressionOp->b = 0;
    ExpressionConstant = idMaterial::GetExpressionTemporary(this);
    ExpressionOp->c = ExpressionConstant;
    goto LABEL_99;
  }
  if ( !idStr::Icmp(token.data, "glslPrograms") )
  {
    this->pd->registersAreConstant = 0;
    ExpressionOp = idMaterial::GetExpressionOp(this);
    ExpressionOp->opType = OP_TYPE_SOUND|OP_TYPE_SUBTRACT;
    goto LABEL_64;
  }
  if ( !idStr::Icmp(token.data, "DecalLife") )
  {
    this->pd->registersAreConstant = 0;
    goto LABEL_67;
  }
  if ( !idStr::Icmp(token.data, "DecalSpawn") )
  {
    this->pd->registersAreConstant = 0;
    goto LABEL_70;
  }
  if ( !idStr::Icmp(token.data, "VertexRandomizer") )
  {
    this->pd->registersAreConstant = 0;
    v21 = -1;
    idStr::FreeData(&token);
    return 21;
  }
  if ( idStr::Cmp(token.data, "-") )
  {
    if ( token.type == 3 )
      goto LABEL_95;
    if ( idStr::Cmp(token.data, ".") && idStr::Cmp(token.data, "-") )
    {
      for ( i = 0; i < 36; ++i )
      {
        if ( !idStr::Icmp(token.data, shaderConstantNames[i]) )
        {
          ExpressionConstant = -1 - i;
          goto LABEL_99;
        }
      }
      v10 = declManager->FindType(declManager, 0, token.data, 0, 0);
      if ( !v10 )
      {
        idLexer::Warning(src, "Bad term '%s'", token.data);
        goto LABEL_77;
      }
      idMaterial::MatchToken(this, src, "[");
      v11 = idMaterial::ParseExpressionPriority(this, src, 4);
      idMaterial::MatchToken(this, src, "]");
      v12 = v10->base->Index(v10->base);
      v13 = idMaterial::GetExpressionOp(this);
      v13->opType = OP_TYPE_TABLE;
      v13->a = v12;
      v13->b = v11;
      ExpressionConstant = idMaterial::GetExpressionTemporary(this);
      v13->c = ExpressionConstant;
      goto LABEL_99;
    }
    if ( token.type == 3 )
    {
LABEL_95:
      if ( (token.subtype & 0x10000) == 0 )
        idToken::NumberValue(&token);
      floatvalue = token.floatvalue;
    }
    else
    {
      floatvalue = 0.0;
    }
    goto LABEL_98;
  }
  idLexer::ReadToken(src, &token);
  if ( token.type == 3 )
    goto LABEL_80;
  if ( !idStr::Cmp(token.data, ".") )
  {
    if ( token.type != 3 )
    {
      floatvalue = -0.0;
LABEL_98:
      v14 = floatvalue;
      ExpressionConstant = idMaterial::GetExpressionConstant(this, v14);
      goto LABEL_99;
    }
LABEL_80:
    if ( (token.subtype & 0x10000) == 0 )
      idToken::NumberValue(&token);
    floatvalue = -token.floatvalue;
    goto LABEL_98;
  }
  idLexer::Warning(src, "Bad negative number '%s'", token.data);
LABEL_77:
  this->materialFlags |= 1u;
  v21 = -1;
  idStr::FreeData(&token);
  return 0;
}

// FUNC: private: int __thiscall idMaterial::ParseExpressionPriority(class idLexer &,int)
int __thiscall idMaterial::ParseExpressionPriority(idMaterial *this, idLexer *src, int priority)
{
  int v4; // esi
  int v6; // ebp
  int v7; // eax
  int v8; // esi
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v10; // [esp+60h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v10 = 0;
  if ( !priority )
  {
    v4 = idMaterial::ParseTerm(this, src);
    v10 = -1;
    idStr::FreeData(&token);
    return v4;
  }
  v6 = idMaterial::ParseExpressionPriority(this, src, priority - 1);
  if ( (this->materialFlags & 1) != 0 )
  {
    v10 = -1;
    idStr::FreeData(&token);
    return 0;
  }
  if ( idLexer::ReadToken(src, &token) )
  {
    switch ( priority )
    {
      case 1:
        if ( !idStr::Cmp(token.data, "*") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_MULTIPLY, 1);
LABEL_36:
          v8 = v7;
          v10 = -1;
          idStr::FreeData(&token);
          return v8;
        }
        if ( !idStr::Cmp(token.data, "/") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_DIVIDE, 1);
          goto LABEL_36;
        }
        if ( !idStr::Cmp(token.data, "%") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_MOD, 1);
          goto LABEL_36;
        }
        break;
      case 2:
        if ( !idStr::Cmp(token.data, "+") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_ADD, 2);
          goto LABEL_36;
        }
        if ( !idStr::Cmp(token.data, "-") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_SUBTRACT, 2);
          goto LABEL_36;
        }
        break;
      case 3:
        if ( !idStr::Cmp(token.data, ">") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_GT, 3);
          goto LABEL_36;
        }
        if ( !idStr::Cmp(token.data, ">=") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_GE, 3);
          goto LABEL_36;
        }
        if ( !idStr::Cmp(token.data, "<") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_LT, 3);
          goto LABEL_36;
        }
        if ( !idStr::Cmp(token.data, "<=") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_LE, 3);
          goto LABEL_36;
        }
        if ( !idStr::Cmp(token.data, "==") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_EQ, 3);
          goto LABEL_36;
        }
        if ( !idStr::Cmp(token.data, "!=") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_NE, 3);
          goto LABEL_36;
        }
        break;
      case 4:
        if ( !idStr::Cmp(token.data, "&&") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_AND, 4);
          goto LABEL_36;
        }
        if ( !idStr::Cmp(token.data, "||") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_OR, 4);
          goto LABEL_36;
        }
        break;
    }
    idLexer::UnreadToken(src, &token);
  }
  v10 = -1;
  idStr::FreeData(&token);
  return v6;
}

// FUNC: private: int __thiscall idMaterial::ParseExpression(class idLexer &)
int __thiscall idMaterial::ParseExpression(idMaterial *this, idLexer *src)
{
  return idMaterial::ParseExpressionPriority(this, src, 4);
}

// FUNC: private: void __thiscall idMaterial::ClearStage(struct shaderStage_t *)
void __thiscall idMaterial::ClearStage(idMaterial *this, shaderStage_t *ss)
{
  int ExpressionConstant; // eax

  ss->drawStateBits = 0;
  ss->mStageRegisterStart = this->numRegisters;
  ss->mNumStageRegisters = 0;
  ss->mStageOpsStart = this->numOps;
  ss->mNumStageOps = 0;
  ss->conditionRegister = idMaterial::GetExpressionConstant(this, 1.0);
  ExpressionConstant = idMaterial::GetExpressionConstant(this, 1.0);
  ss->color.registers[3] = ExpressionConstant;
  ss->color.registers[2] = ExpressionConstant;
  ss->color.registers[1] = ExpressionConstant;
  ss->color.registers[0] = ExpressionConstant;
}

// FUNC: private: int __thiscall idMaterial::NameToSrcBlendMode(class idStr const &)
int __thiscall idMaterial::NameToSrcBlendMode(idMaterial *this, const idStr *name)
{
  char *data; // esi
  int v5; // ebx
  const char *v6; // eax

  if ( idStr::Icmp(name->data, "GL_ONE") )
  {
    if ( !idStr::Icmp(name->data, "GL_ZERO") )
      return 1;
    if ( !idStr::Icmp(name->data, "GL_DST_COLOR") )
      return 3;
    if ( !idStr::Icmp(name->data, "GL_ONE_MINUS_DST_COLOR") )
      return 4;
    if ( !idStr::Icmp(name->data, "GL_SRC_ALPHA") )
      return 5;
    if ( !idStr::Icmp(name->data, "GL_ONE_MINUS_SRC_ALPHA") )
      return 6;
    if ( !idStr::Icmp(name->data, "GL_DST_ALPHA") )
      return 7;
    if ( !idStr::Icmp(name->data, "GL_ONE_MINUS_DST_ALPHA") )
      return 8;
    if ( !idStr::Icmp(name->data, "GL_SRC_ALPHA_SATURATE") )
      return 9;
    if ( !idStr::Icmp(name->data, "GL_SRC_COLOR") )
      return 10;
    if ( !idStr::Icmp(name->data, "GL_ONE_MINUS_SRC_COLOR") )
      return 11;
    data = name->data;
    v5 = *(_DWORD *)common.type;
    v6 = this->base->GetName(this->base);
    (*(void (**)(netadrtype_t, const char *, ...))(v5 + 136))(
      common.type,
      "unknown blend mode '%s' in material '%s'",
      data,
      v6);
    this->materialFlags |= 1u;
  }
  return 0;
}

// FUNC: private: int __thiscall idMaterial::NameToDstBlendMode(class idStr const &)
int __thiscall idMaterial::NameToDstBlendMode(idMaterial *this, const idStr *name)
{
  int result; // eax
  char *data; // esi
  int v5; // ebx
  const char *v6; // eax

  if ( idStr::Icmp(name->data, "GL_ONE") )
  {
    result = idStr::Icmp(name->data, "GL_ZERO");
    if ( !result )
      return result;
    if ( !idStr::Icmp(name->data, "GL_SRC_ALPHA") )
      return 80;
    if ( !idStr::Icmp(name->data, "GL_ONE_MINUS_SRC_ALPHA") )
      return 96;
    if ( !idStr::Icmp(name->data, "GL_DST_ALPHA") )
      return 112;
    if ( !idStr::Icmp(name->data, "GL_ONE_MINUS_DST_ALPHA") )
      return 128;
    if ( !idStr::Icmp(name->data, "GL_SRC_COLOR") )
      return 48;
    if ( !idStr::Icmp(name->data, "GL_ONE_MINUS_SRC_COLOR") )
      return 64;
    if ( !idStr::Icmp(name->data, "GL_DST_COLOR") )
      return 144;
    if ( !idStr::Icmp(name->data, "GL_ONE_MINUS_DST_COLOR") )
      return 160;
    data = name->data;
    v5 = *(_DWORD *)common.type;
    v6 = this->base->GetName(this->base);
    (*(void (**)(netadrtype_t, const char *, ...))(v5 + 136))(
      common.type,
      "unknown blend mode '%s' in material '%s'",
      data,
      v6);
    this->materialFlags |= 1u;
  }
  return 32;
}

// FUNC: private: void __thiscall idMaterial::ParseBlend(class idLexer &,struct shaderStage_t *)
void __thiscall idMaterial::ParseBlend(idMaterial *this, idLexer *src, shaderStage_t *stage)
{
  int v4; // ebx
  idToken token; // [esp+4h] [ebp-5Ch] BYREF
  int v6; // [esp+5Ch] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v6 = 0;
  if ( idLexer::ReadToken(src, &token) )
  {
    if ( idStr::Icmp(token.data, "blend") )
    {
      if ( idStr::Icmp(token.data, "add") )
      {
        if ( idStr::Icmp(token.data, "filter") && idStr::Icmp(token.data, "modulate") )
        {
          if ( idStr::Icmp(token.data, "none") )
          {
            if ( idStr::Icmp(token.data, "bumpmap") )
            {
              if ( idStr::Icmp(token.data, "diffusemap") )
              {
                if ( idStr::Icmp(token.data, "specularmap") )
                {
                  v4 = idMaterial::NameToSrcBlendMode(this, &token);
                  idMaterial::MatchToken(this, src, ",");
                  if ( idLexer::ReadToken(src, &token) )
                    stage->drawStateBits = v4 | idMaterial::NameToDstBlendMode(this, &token);
                }
                else
                {
                  stage->lighting = SL_SPECULAR;
                }
              }
              else
              {
                stage->lighting = SL_DIFFUSE;
              }
            }
            else
            {
              stage->lighting = SL_BUMP;
            }
          }
          else
          {
            stage->drawStateBits = 33;
          }
        }
        else
        {
          stage->drawStateBits = 3;
        }
      }
      else
      {
        stage->drawStateBits = 32;
      }
    }
    else
    {
      stage->drawStateBits = 101;
    }
  }
  v6 = -1;
  idStr::FreeData(&token);
}

// FUNC: private: void __thiscall idMaterial::ParseVertexParm(class idLexer &,struct newShaderStage_t *)
void __thiscall idMaterial::ParseVertexParm(idMaterial *this, idLexer *src, newShaderStage_t *newStage)
{
  int v4; // ebp
  int v5; // ebp
  int v6; // eax
  int *v7; // ebp
  int v8; // ebp
  int v9; // eax
  int *v10; // ebp
  int v11; // ebp
  int v12; // eax
  int v13; // ebp
  int v14; // eax
  int v15; // esi
  int v16; // eax
  unsigned int intvalue; // [esp+8h] [ebp-B0h]
  int *v18; // [esp+8h] [ebp-B0h]
  idToken v19; // [esp+Ch] [ebp-ACh] BYREF
  idToken token; // [esp+5Ch] [ebp-5Ch] BYREF
  int v21; // [esp+B4h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v21 = 0;
  idLexer::ReadTokenOnLine(src, &token);
  if ( token.type == 3 )
  {
    if ( (token.subtype & 0x10000) == 0 )
      idToken::NumberValue(&token);
    intvalue = token.intvalue;
    v4 = token.intvalue;
  }
  else
  {
    v4 = 0;
    intvalue = 0;
  }
  if ( !idStr::IsNumeric(token.data) || (unsigned int)v4 > 0xF )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "bad vertexParm number\n");
    this->materialFlags |= 1u;
    goto LABEL_57;
  }
  if ( v4 >= newStage->numVertexParms )
    newStage->numVertexParms = v4 + 1;
  v19.floatvalue = 0.0;
  v19.len = 0;
  v19.alloced = 20;
  v19.data = v19.baseBuffer;
  v19.baseBuffer[0] = 0;
  LOBYTE(v21) = 1;
  v5 = idMaterial::ParseExpressionPriority(this, src, 3);
  if ( (this->materialFlags & 1) != 0 )
  {
    LOBYTE(v21) = 0;
    idStr::FreeData(&v19);
    v6 = 0;
  }
  else
  {
    if ( idLexer::ReadToken(src, &v19) )
    {
      if ( idStr::Cmp(v19.data, "&&") )
      {
        if ( idStr::Cmp(v19.data, "||") )
          idLexer::UnreadToken(src, &v19);
        else
          v5 = idMaterial::ParseEmitOp(this, src, v5, OP_TYPE_OR, 4);
      }
      else
      {
        v5 = idMaterial::ParseEmitOp(this, src, v5, OP_TYPE_AND, 4);
      }
    }
    LOBYTE(v21) = 0;
    idStr::FreeData(&v19);
    v6 = v5;
  }
  v7 = &newStage->vertexProgram + 4 * intvalue;
  v7[3] = v6;
  v18 = v7;
  idLexer::ReadTokenOnLine(src, &token);
  if ( !*token.data || idStr::Icmp(token.data, ",") )
  {
    v16 = v7[3];
    v7[6] = v16;
    v7[5] = v16;
    v7[4] = v16;
    goto LABEL_57;
  }
  v19.floatvalue = 0.0;
  v19.len = 0;
  v19.alloced = 20;
  v19.data = v19.baseBuffer;
  v19.baseBuffer[0] = 0;
  LOBYTE(v21) = 2;
  v8 = idMaterial::ParseExpressionPriority(this, src, 3);
  if ( (this->materialFlags & 1) != 0 )
  {
    LOBYTE(v21) = 0;
    idStr::FreeData(&v19);
    v9 = 0;
  }
  else
  {
    if ( idLexer::ReadToken(src, &v19) )
    {
      if ( idStr::Cmp(v19.data, "&&") )
      {
        if ( idStr::Cmp(v19.data, "||") )
          idLexer::UnreadToken(src, &v19);
        else
          v8 = idMaterial::ParseEmitOp(this, src, v8, OP_TYPE_OR, 4);
      }
      else
      {
        v8 = idMaterial::ParseEmitOp(this, src, v8, OP_TYPE_AND, 4);
      }
    }
    LOBYTE(v21) = 0;
    idStr::FreeData(&v19);
    v9 = v8;
  }
  v10 = v18;
  v18[4] = v9;
  idLexer::ReadTokenOnLine(src, &token);
  if ( !*token.data || idStr::Icmp(token.data, ",") )
  {
    v18[5] = idMaterial::GetExpressionConstant(this, 0.0);
LABEL_54:
    v10[6] = idMaterial::GetExpressionConstant(this, 1.0);
    goto LABEL_57;
  }
  v19.floatvalue = 0.0;
  v19.len = 0;
  v19.alloced = 20;
  v19.data = v19.baseBuffer;
  v19.baseBuffer[0] = 0;
  LOBYTE(v21) = 3;
  v11 = idMaterial::ParseExpressionPriority(this, src, 3);
  if ( (this->materialFlags & 1) != 0 )
  {
    LOBYTE(v21) = 0;
    idStr::FreeData(&v19);
    v12 = 0;
  }
  else
  {
    if ( idLexer::ReadToken(src, &v19) )
    {
      if ( idStr::Cmp(v19.data, "&&") )
      {
        if ( idStr::Cmp(v19.data, "||") )
          idLexer::UnreadToken(src, &v19);
        else
          v11 = idMaterial::ParseEmitOp(this, src, v11, OP_TYPE_OR, 4);
      }
      else
      {
        v11 = idMaterial::ParseEmitOp(this, src, v11, OP_TYPE_AND, 4);
      }
    }
    LOBYTE(v21) = 0;
    idStr::FreeData(&v19);
    v12 = v11;
  }
  v10 = v18;
  v18[5] = v12;
  idLexer::ReadTokenOnLine(src, &token);
  if ( !*token.data || idStr::Icmp(token.data, ",") )
    goto LABEL_54;
  v19.floatvalue = 0.0;
  v19.len = 0;
  v19.alloced = 20;
  v19.data = v19.baseBuffer;
  v19.baseBuffer[0] = 0;
  LOBYTE(v21) = 4;
  v13 = idMaterial::ParseExpressionPriority(this, src, 3);
  if ( (this->materialFlags & 1) == 0 )
  {
    if ( idLexer::ReadToken(src, &v19) )
    {
      if ( !idStr::Cmp(v19.data, "&&") )
      {
        v14 = idMaterial::ParseEmitOp(this, src, v13, OP_TYPE_AND, 4);
LABEL_50:
        v15 = v14;
        LOBYTE(v21) = 0;
        idStr::FreeData(&v19);
        v18[6] = v15;
        goto LABEL_57;
      }
      if ( !idStr::Cmp(v19.data, "||") )
      {
        v14 = idMaterial::ParseEmitOp(this, src, v13, OP_TYPE_OR, 4);
        goto LABEL_50;
      }
      idLexer::UnreadToken(src, &v19);
    }
    LOBYTE(v21) = 0;
    idStr::FreeData(&v19);
    v18[6] = v13;
    goto LABEL_57;
  }
  LOBYTE(v21) = 0;
  idStr::FreeData(&v19);
  v18[6] = 0;
LABEL_57:
  v21 = -1;
  idStr::FreeData(&token);
}

// FUNC: private: void __thiscall idMaterial::ParseFragmentParm(class idLexer &,struct newShaderStage_t *)
void __thiscall idMaterial::ParseFragmentParm(idMaterial *this, idLexer *src, newShaderStage_t *newStage)
{
  int v4; // ebp
  int v5; // ebp
  int v6; // eax
  int v7; // ebp
  int v8; // eax
  int *v9; // ebp
  int v10; // ebp
  int v11; // eax
  int v12; // ebp
  int v13; // eax
  int v14; // esi
  int *v15; // eax
  int v16; // ecx
  unsigned int intvalue; // [esp+8h] [ebp-B4h]
  int *v18; // [esp+8h] [ebp-B4h]
  idToken v19; // [esp+Ch] [ebp-B0h] BYREF
  int *v20; // [esp+5Ch] [ebp-60h]
  idToken token; // [esp+60h] [ebp-5Ch] BYREF
  int v22; // [esp+B8h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v22 = 0;
  idLexer::ReadTokenOnLine(src, &token);
  if ( token.type == 3 )
  {
    if ( (token.subtype & 0x10000) == 0 )
      idToken::NumberValue(&token);
    intvalue = token.intvalue;
    v4 = token.intvalue;
  }
  else
  {
    v4 = 0;
    intvalue = 0;
  }
  if ( !idStr::IsNumeric(token.data) || (unsigned int)v4 > 7 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "bad fragmentParm number\n");
    this->materialFlags |= 1u;
    goto LABEL_57;
  }
  if ( v4 >= newStage->numFragmentParms )
    newStage->numFragmentParms = v4 + 1;
  v19.floatvalue = 0.0;
  v19.len = 0;
  v19.alloced = 20;
  v19.data = v19.baseBuffer;
  v19.baseBuffer[0] = 0;
  LOBYTE(v22) = 1;
  v5 = idMaterial::ParseExpressionPriority(this, src, 3);
  if ( (this->materialFlags & 1) != 0 )
  {
    LOBYTE(v22) = 0;
    idStr::FreeData(&v19);
    v6 = 0;
  }
  else
  {
    if ( idLexer::ReadToken(src, &v19) )
    {
      if ( idStr::Cmp(v19.data, "&&") )
      {
        if ( idStr::Cmp(v19.data, "||") )
          idLexer::UnreadToken(src, &v19);
        else
          v5 = idMaterial::ParseEmitOp(this, src, v5, OP_TYPE_OR, 4);
      }
      else
      {
        v5 = idMaterial::ParseEmitOp(this, src, v5, OP_TYPE_AND, 4);
      }
    }
    LOBYTE(v22) = 0;
    idStr::FreeData(&v19);
    v6 = v5;
  }
  newStage->fragmentParms[intvalue][0] = v6;
  v20 = newStage->fragmentParms[intvalue];
  idLexer::ReadTokenOnLine(src, &token);
  if ( !*token.data || idStr::Icmp(token.data, ",") )
  {
    v15 = &newStage->vertexProgram + 4 * intvalue;
    v16 = *v20;
    v15[71] = *v20;
    v15[70] = v16;
    v15[69] = v16;
    goto LABEL_57;
  }
  v19.floatvalue = 0.0;
  v19.len = 0;
  v19.alloced = 20;
  v19.data = v19.baseBuffer;
  v19.baseBuffer[0] = 0;
  LOBYTE(v22) = 2;
  v7 = idMaterial::ParseExpressionPriority(this, src, 3);
  if ( (this->materialFlags & 1) != 0 )
  {
    LOBYTE(v22) = 0;
    idStr::FreeData(&v19);
    v8 = 0;
  }
  else
  {
    if ( idLexer::ReadToken(src, &v19) )
    {
      if ( idStr::Cmp(v19.data, "&&") )
      {
        if ( idStr::Cmp(v19.data, "||") )
          idLexer::UnreadToken(src, &v19);
        else
          v7 = idMaterial::ParseEmitOp(this, src, v7, OP_TYPE_OR, 4);
      }
      else
      {
        v7 = idMaterial::ParseEmitOp(this, src, v7, OP_TYPE_AND, 4);
      }
    }
    LOBYTE(v22) = 0;
    idStr::FreeData(&v19);
    v8 = v7;
  }
  v9 = &newStage->vertexProgram + 4 * intvalue;
  v9[69] = v8;
  v18 = v9;
  idLexer::ReadTokenOnLine(src, &token);
  if ( !*token.data || idStr::Icmp(token.data, ",") )
  {
    v9[70] = idMaterial::GetExpressionConstant(this, 0.0);
LABEL_54:
    v9[71] = idMaterial::GetExpressionConstant(this, 1.0);
    goto LABEL_57;
  }
  v19.floatvalue = 0.0;
  v19.len = 0;
  v19.alloced = 20;
  v19.data = v19.baseBuffer;
  v19.baseBuffer[0] = 0;
  LOBYTE(v22) = 3;
  v10 = idMaterial::ParseExpressionPriority(this, src, 3);
  if ( (this->materialFlags & 1) != 0 )
  {
    LOBYTE(v22) = 0;
    idStr::FreeData(&v19);
    v11 = 0;
  }
  else
  {
    if ( idLexer::ReadToken(src, &v19) )
    {
      if ( idStr::Cmp(v19.data, "&&") )
      {
        if ( idStr::Cmp(v19.data, "||") )
          idLexer::UnreadToken(src, &v19);
        else
          v10 = idMaterial::ParseEmitOp(this, src, v10, OP_TYPE_OR, 4);
      }
      else
      {
        v10 = idMaterial::ParseEmitOp(this, src, v10, OP_TYPE_AND, 4);
      }
    }
    LOBYTE(v22) = 0;
    idStr::FreeData(&v19);
    v11 = v10;
  }
  v9 = v18;
  v18[70] = v11;
  idLexer::ReadTokenOnLine(src, &token);
  if ( !*token.data || idStr::Icmp(token.data, ",") )
    goto LABEL_54;
  v19.floatvalue = 0.0;
  v19.len = 0;
  v19.alloced = 20;
  v19.data = v19.baseBuffer;
  v19.baseBuffer[0] = 0;
  LOBYTE(v22) = 4;
  v12 = idMaterial::ParseExpressionPriority(this, src, 3);
  if ( (this->materialFlags & 1) == 0 )
  {
    if ( idLexer::ReadToken(src, &v19) )
    {
      if ( !idStr::Cmp(v19.data, "&&") )
      {
        v13 = idMaterial::ParseEmitOp(this, src, v12, OP_TYPE_AND, 4);
LABEL_50:
        v14 = v13;
        LOBYTE(v22) = 0;
        idStr::FreeData(&v19);
        v18[71] = v14;
        goto LABEL_57;
      }
      if ( !idStr::Cmp(v19.data, "||") )
      {
        v13 = idMaterial::ParseEmitOp(this, src, v12, OP_TYPE_OR, 4);
        goto LABEL_50;
      }
      idLexer::UnreadToken(src, &v19);
    }
    LOBYTE(v22) = 0;
    idStr::FreeData(&v19);
    v18[71] = v12;
    goto LABEL_57;
  }
  LOBYTE(v22) = 0;
  idStr::FreeData(&v19);
  v18[71] = 0;
LABEL_57:
  v22 = -1;
  idStr::FreeData(&token);
}

// FUNC: private: void __thiscall idMaterial::ParseFragmentMap(class idLexer &,struct newShaderStage_t *)
void __thiscall idMaterial::ParseFragmentMap(idMaterial *this, idLexer *src, newShaderStage_t *newStage)
{
  textureRepeat_t v4; // ebp
  int intvalue; // esi
  const char *v6; // eax
  idImage *v7; // eax
  textureDepth_t td; // [esp+8h] [ebp-70h]
  int imageFlags; // [esp+Ch] [ebp-6Ch]
  cubeFiles_t cubeMap; // [esp+10h] [ebp-68h]
  textureFilter_t v11; // [esp+14h] [ebp-64h]
  bool allowPicmip; // [esp+18h] [ebp-60h]
  idToken token; // [esp+1Ch] [ebp-5Ch] BYREF
  int v14; // [esp+74h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v14 = 0;
  v11 = TF_DEFAULT;
  v4 = TR_REPEAT;
  td = TD_DEFAULT;
  allowPicmip = 1;
  cubeMap = CF_2D;
  imageFlags = 0;
  idLexer::ReadTokenOnLine(src, &token);
  if ( token.type == 3 )
  {
    if ( (token.subtype & 0x10000) == 0 )
      idToken::NumberValue(&token);
    intvalue = token.intvalue;
  }
  else
  {
    intvalue = 0;
  }
  if ( idStr::IsNumeric(token.data) && (unsigned int)intvalue <= 7 )
  {
    if ( intvalue == 1 )
      td = TD_BUMP;
    if ( intvalue >= newStage->numFragmentProgramImages )
      newStage->numFragmentProgramImages = intvalue + 1;
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
                                        if ( idStr::Icmp(token.data, "cubeMap") )
                                          break;
                                        cubeMap = CF_NATIVE;
                                      }
                                      if ( idStr::Icmp(token.data, "cameraCubeMap") )
                                        break;
                                      cubeMap = CF_CAMERA;
                                    }
                                    if ( idStr::Icmp(token.data, "nearest") )
                                      break;
                                    v11 = TF_NEAREST;
                                  }
                                  if ( idStr::Icmp(token.data, "linear") )
                                    break;
                                  v11 = TF_LINEAR;
                                }
                                if ( idStr::Icmp(token.data, "clamp") )
                                  break;
                                v4 = TR_CLAMP;
                              }
                              if ( idStr::Icmp(token.data, "noclamp") )
                                break;
                              v4 = TR_REPEAT;
                            }
                            if ( idStr::Icmp(token.data, "zeroclamp") )
                              break;
                            v4 = TR_CLAMP_TO_ZERO;
                          }
                          if ( idStr::Icmp(token.data, "alphazeroclamp") )
                            break;
                          v4 = TR_CLAMP_TO_ZERO_ALPHA;
                        }
                        if ( idStr::Icmp(token.data, "mirroredrepeat") )
                          break;
                        v4 = TR_MIRRORED_REPEAT;
                      }
                      if ( idStr::Icmp(token.data, "nomips") )
                        break;
                      if ( com_makingBuild.internalVar->integerValue > 1 )
                        imageFlags |= 1u;
                    }
                    if ( idStr::Icmp(token.data, "forceHighQuality") )
                      break;
                    td = TD_HIGH_QUALITY;
                  }
                  if ( idStr::Icmp(token.data, "uncompressed") && idStr::Icmp(token.data, "highquality") )
                    break;
                  if ( !image_ignoreHighQuality.internalVar->integerValue )
                    td = TD_HIGH_QUALITY;
                }
                if ( idStr::Icmp(token.data, "nopicmip") )
                  break;
                allowPicmip = 0;
              }
              if ( idStr::Icmp(token.data, "lightfalloffImage") )
                break;
              newStage->fragmentProgramBindings[intvalue] = 1;
              newStage->fragmentProgramImages[intvalue] = 0;
            }
            if ( idStr::Icmp(token.data, "lightImage") )
              break;
            newStage->fragmentProgramBindings[intvalue] = 2;
            newStage->fragmentProgramImages[intvalue] = 0;
          }
          if ( idStr::Icmp(token.data, "ambientNormalMap") )
            break;
          newStage->fragmentProgramBindings[intvalue] = 3;
          newStage->fragmentProgramImages[intvalue] = globalImages->GetAmbientNormalMap(globalImages);
        }
        if ( idStr::Icmp(token.data, "normalCubeMap") )
          break;
        newStage->fragmentProgramBindings[intvalue] = 4;
        newStage->fragmentProgramImages[intvalue] = globalImages->GetNormalCubeMapImage(globalImages);
      }
      if ( idStr::Icmp(token.data, "specularTableImage") )
        break;
      newStage->fragmentProgramBindings[intvalue] = 5;
      newStage->fragmentProgramImages[intvalue] = globalImages->GetSpecularTableImage(globalImages);
    }
    idLexer::UnreadToken(src, &token);
    v6 = R_ParsePastImageProgram(src);
    if ( !newStage->fragmentProgramBindings[intvalue] )
    {
      v7 = globalImages->ImageFromFile(globalImages, v6, v11, allowPicmip, v4, td, cubeMap, imageFlags);
      newStage->fragmentProgramImages[intvalue] = v7;
      if ( !v7 )
        newStage->fragmentProgramImages[intvalue] = globalImages->GetDefaultImage(globalImages);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "bad fragmentMap number\n");
    this->materialFlags |= 1u;
  }
  v14 = -1;
  idStr::FreeData(&token);
}

// FUNC: private: void __thiscall idMaterial::MultiplyTextureMatrix(struct textureStage_t *,int (* const)[3])
void __thiscall idMaterial::MultiplyTextureMatrix(idMaterial *this, textureStage_t *ts, int (*registers)[3])
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // [esp-18h] [ebp-38h]
  int v18; // [esp-18h] [ebp-38h]
  int v19; // [esp-10h] [ebp-30h]
  int v20; // [esp-10h] [ebp-30h]
  int v21; // [esp-10h] [ebp-30h]
  int v22; // [esp-10h] [ebp-30h]
  int v23; // [esp-10h] [ebp-30h]
  int v24; // [esp-10h] [ebp-30h]
  int old[2][3]; // [esp+8h] [ebp-18h] BYREF

  if ( ts->hasMatrix )
  {
    SIMDProcessor->Memcpy(SIMDProcessor, old, ts->matrix, 24);
    v19 = idMaterial::EmitOp(this, old[0][1], (*registers)[3], OP_TYPE_MULTIPLY);
    v4 = idMaterial::EmitOp(this, old[0][0], (*registers)[0], OP_TYPE_MULTIPLY);
    ts->matrix[0][0] = idMaterial::EmitOp(this, v4, v19, OP_TYPE_ADD);
    v20 = idMaterial::EmitOp(this, old[0][1], (*registers)[4], OP_TYPE_MULTIPLY);
    v5 = idMaterial::EmitOp(this, old[0][0], (*registers)[1], OP_TYPE_MULTIPLY);
    v6 = idMaterial::EmitOp(this, v5, v20, OP_TYPE_ADD);
    v7 = old[0][1];
    ts->matrix[0][1] = v6;
    v21 = old[0][2];
    v17 = idMaterial::EmitOp(this, v7, (*registers)[5], OP_TYPE_MULTIPLY);
    v8 = idMaterial::EmitOp(this, old[0][0], (*registers)[2], OP_TYPE_MULTIPLY);
    v9 = idMaterial::EmitOp(this, v8, v17, OP_TYPE_ADD);
    ts->matrix[0][2] = idMaterial::EmitOp(this, v9, v21, OP_TYPE_ADD);
    v22 = idMaterial::EmitOp(this, old[1][1], (*registers)[3], OP_TYPE_MULTIPLY);
    v10 = idMaterial::EmitOp(this, old[1][0], (*registers)[0], OP_TYPE_MULTIPLY);
    v11 = idMaterial::EmitOp(this, v10, v22, OP_TYPE_ADD);
    v12 = old[1][1];
    ts->matrix[1][0] = v11;
    v23 = idMaterial::EmitOp(this, v12, (*registers)[4], OP_TYPE_MULTIPLY);
    v13 = idMaterial::EmitOp(this, old[1][0], (*registers)[1], OP_TYPE_MULTIPLY);
    v14 = idMaterial::EmitOp(this, v13, v23, OP_TYPE_ADD);
    v24 = old[1][2];
    ts->matrix[1][1] = v14;
    v18 = idMaterial::EmitOp(this, old[1][1], (*registers)[5], OP_TYPE_MULTIPLY);
    v15 = idMaterial::EmitOp(this, old[1][0], (*registers)[2], OP_TYPE_MULTIPLY);
    v16 = idMaterial::EmitOp(this, v15, v18, OP_TYPE_ADD);
    ts->matrix[1][2] = idMaterial::EmitOp(this, v16, v24, OP_TYPE_ADD);
  }
  else
  {
    ts->hasMatrix = 1;
    SIMDProcessor->Memcpy(SIMDProcessor, ts->matrix, registers, 24);
  }
}

// FUNC: private: void __thiscall idMaterial::ParseDeform(class idLexer &)
void __thiscall idMaterial::ParseDeform(idMaterial *this, idLexer *src)
{
  int v3; // ebp
  int v4; // eax
  int v5; // edi
  int v6; // ebp
  int v7; // eax
  int v8; // edi
  const idDecl *v9; // eax
  int v10; // ebp
  int v11; // ebp
  int v12; // eax
  int v13; // ebp
  int v14; // eax
  int v15; // edi
  idToken v16; // [esp+10h] [ebp-ACh] BYREF
  idToken token; // [esp+60h] [ebp-5Ch] BYREF
  int v18; // [esp+B8h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v18 = 0;
  if ( idLexer::ExpectAnyToken(src, &token) )
  {
    if ( !idStr::Icmp(token.data, "sprite") )
    {
      this->deform = DFRM_SPRITE;
LABEL_6:
      this->materialFlags |= 4u;
      this->cullType = CT_TWO_SIDED;
      goto LABEL_68;
    }
    if ( !idStr::Icmp(token.data, "rectsprite") )
    {
      this->deform = DFRM_RECTSPRITE;
      goto LABEL_6;
    }
    if ( !idStr::Icmp(token.data, "tube") )
    {
      this->materialFlags |= 4u;
      this->deform = DFRM_TUBE;
      this->cullType = CT_TWO_SIDED;
      goto LABEL_68;
    }
    if ( !idStr::Icmp(token.data, "flare") )
    {
      v16.floatvalue = 0.0;
      this->deform = DFRM_FLARE;
      this->cullType = CT_TWO_SIDED;
      v16.len = 0;
      v16.alloced = 20;
      v16.data = v16.baseBuffer;
      v16.baseBuffer[0] = 0;
      LOBYTE(v18) = 1;
      v3 = idMaterial::ParseExpressionPriority(this, src, 3);
      if ( (this->materialFlags & 1) != 0 )
      {
        LOBYTE(v18) = 0;
        idStr::FreeData(&v16);
        this->materialFlags |= 4u;
        this->deformRegisters[0] = 0;
        goto LABEL_68;
      }
      if ( idLexer::ReadToken(src, &v16) )
      {
        if ( !idStr::Cmp(v16.data, "&&") )
        {
          v4 = idMaterial::ParseEmitOp(this, src, v3, OP_TYPE_AND, 4);
LABEL_17:
          v5 = v4;
          LOBYTE(v18) = 0;
          idStr::FreeData(&v16);
          this->materialFlags |= 4u;
          this->deformRegisters[0] = v5;
          goto LABEL_68;
        }
        if ( !idStr::Cmp(v16.data, "||") )
        {
          v4 = idMaterial::ParseEmitOp(this, src, v3, OP_TYPE_OR, 4);
          goto LABEL_17;
        }
        idLexer::UnreadToken(src, &v16);
      }
      LOBYTE(v18) = 0;
      idStr::FreeData(&v16);
      this->materialFlags |= 4u;
      this->deformRegisters[0] = v3;
      goto LABEL_68;
    }
    if ( !idStr::Icmp(token.data, "expand") )
    {
      v16.floatvalue = 0.0;
      this->deform = DFRM_EXPAND;
      v16.len = 0;
      v16.alloced = 20;
      v16.data = v16.baseBuffer;
      v16.baseBuffer[0] = 0;
      LOBYTE(v18) = 2;
      v6 = idMaterial::ParseExpressionPriority(this, src, 3);
      if ( (this->materialFlags & 1) != 0 )
      {
LABEL_22:
        LOBYTE(v18) = 0;
        idStr::FreeData(&v16);
        this->deformRegisters[0] = 0;
        goto LABEL_68;
      }
LABEL_28:
      if ( idLexer::ReadToken(src, &v16) )
      {
        if ( !idStr::Cmp(v16.data, "&&") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_AND, 4);
          goto LABEL_25;
        }
        if ( !idStr::Cmp(v16.data, "||") )
        {
          v7 = idMaterial::ParseEmitOp(this, src, v6, OP_TYPE_OR, 4);
LABEL_25:
          v8 = v7;
          LOBYTE(v18) = 0;
          idStr::FreeData(&v16);
          this->deformRegisters[0] = v8;
          goto LABEL_68;
        }
        idLexer::UnreadToken(src, &v16);
      }
      LOBYTE(v18) = 0;
      idStr::FreeData(&v16);
      this->deformRegisters[0] = v6;
      goto LABEL_68;
    }
    if ( !idStr::Icmp(token.data, "move") )
    {
      v16.floatvalue = 0.0;
      this->deform = DFRM_MOVE;
      v16.len = 0;
      v16.alloced = 20;
      v16.data = v16.baseBuffer;
      v16.baseBuffer[0] = 0;
      LOBYTE(v18) = 3;
      v6 = idMaterial::ParseExpressionPriority(this, src, 3);
      if ( (this->materialFlags & 1) != 0 )
        goto LABEL_22;
      goto LABEL_28;
    }
    if ( idStr::Icmp(token.data, "turbulent") )
    {
      if ( !idStr::Icmp(token.data, "eyeBall") )
      {
        this->deform = DFRM_EYEBALL;
        goto LABEL_68;
      }
      idLexer::Warning(src, "Bad deform type '%s'", token.data);
LABEL_67:
      this->materialFlags |= 1u;
      goto LABEL_68;
    }
    this->deform = DFRM_TURB;
    if ( !idLexer::ExpectAnyToken(src, &token) )
    {
      idLexer::Warning(src, "deform particle missing particle name");
      goto LABEL_67;
    }
    v9 = declManager->FindType(declManager, 0, token.data, 1, 0);
    v16.floatvalue = 0.0;
    this->deformDecl = v9;
    v16.len = 0;
    v16.alloced = 20;
    v16.data = v16.baseBuffer;
    v16.baseBuffer[0] = 0;
    LOBYTE(v18) = 4;
    v10 = idMaterial::ParseExpressionPriority(this, src, 3);
    if ( (this->materialFlags & 1) != 0 )
    {
      LOBYTE(v18) = 0;
      idStr::FreeData(&v16);
      v10 = 0;
    }
    else
    {
      if ( idLexer::ReadToken(src, &v16) )
      {
        if ( idStr::Cmp(v16.data, "&&") )
        {
          if ( idStr::Cmp(v16.data, "||") )
            idLexer::UnreadToken(src, &v16);
          else
            v10 = idMaterial::ParseEmitOp(this, src, v10, OP_TYPE_OR, 4);
        }
        else
        {
          v10 = idMaterial::ParseEmitOp(this, src, v10, OP_TYPE_AND, 4);
        }
      }
      LOBYTE(v18) = 0;
      idStr::FreeData(&v16);
    }
    v16.floatvalue = 0.0;
    this->deformRegisters[0] = v10;
    v16.len = 0;
    v16.alloced = 20;
    v16.data = v16.baseBuffer;
    v16.baseBuffer[0] = 0;
    LOBYTE(v18) = 5;
    v11 = idMaterial::ParseExpressionPriority(this, src, 3);
    if ( (this->materialFlags & 1) != 0 )
    {
      LOBYTE(v18) = 0;
      idStr::FreeData(&v16);
      v12 = 0;
    }
    else
    {
      if ( idLexer::ReadToken(src, &v16) )
      {
        if ( idStr::Cmp(v16.data, "&&") )
        {
          if ( idStr::Cmp(v16.data, "||") )
            idLexer::UnreadToken(src, &v16);
          else
            v11 = idMaterial::ParseEmitOp(this, src, v11, OP_TYPE_OR, 4);
        }
        else
        {
          v11 = idMaterial::ParseEmitOp(this, src, v11, OP_TYPE_AND, 4);
        }
      }
      LOBYTE(v18) = 0;
      idStr::FreeData(&v16);
      v12 = v11;
    }
    v16.floatvalue = 0.0;
    this->deformRegisters[1] = v12;
    v16.len = 0;
    v16.alloced = 20;
    v16.data = v16.baseBuffer;
    v16.baseBuffer[0] = 0;
    LOBYTE(v18) = 6;
    v13 = idMaterial::ParseExpressionPriority(this, src, 3);
    if ( (this->materialFlags & 1) != 0 )
    {
      LOBYTE(v18) = 0;
      idStr::FreeData(&v16);
      this->deformRegisters[2] = 0;
      goto LABEL_68;
    }
    if ( idLexer::ReadToken(src, &v16) )
    {
      if ( !idStr::Cmp(v16.data, "&&") )
      {
        v14 = idMaterial::ParseEmitOp(this, src, v13, OP_TYPE_AND, 4);
LABEL_61:
        v15 = v14;
        LOBYTE(v18) = 0;
        idStr::FreeData(&v16);
        this->deformRegisters[2] = v15;
        goto LABEL_68;
      }
      if ( !idStr::Cmp(v16.data, "||") )
      {
        v14 = idMaterial::ParseEmitOp(this, src, v13, OP_TYPE_OR, 4);
        goto LABEL_61;
      }
      idLexer::UnreadToken(src, &v16);
    }
    LOBYTE(v18) = 0;
    idStr::FreeData(&v16);
    this->deformRegisters[2] = v13;
  }
LABEL_68:
  v18 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: virtual void __thiscall idMaterial::Print(void)const
void __thiscall idMaterial::Print(idMaterial *this)
{
  int j; // esi
  int v3; // ebx
  expOp_t *ops; // esi
  expOpType_t opType; // eax
  int *v6; // esi
  const idDecl *v7; // eax
  int v8; // eax
  int i; // [esp+1Ch] [ebp-4h]

  for ( j = 22; j < this->numRegisters; ++j )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "register %i: %f\n",
      j,
      this->expressionRegisters[j]);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
  v3 = 0;
  for ( i = 0; i < this->numOps; ++i )
  {
    ops = this->ops;
    opType = ops[v3].opType;
    v6 = (int *)&ops[v3];
    if ( opType == OP_TYPE_TABLE )
    {
      v7 = declManager->DeclByIndex(declManager, 0, v6[1], 1);
      v8 = (int)v7->base->GetName(v7->base);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%i = %s[ %i ]\n",
        v6[3],
        v8,
        v6[2]);
    }
    else
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%i = %i %s %i\n",
        v6[3],
        v6[1],
        opNames[opType],
        v6[2]);
    }
    ++v3;
  }
}

// FUNC: public: int __thiscall idMaterial::GetImageWidth(void)const
int __thiscall idMaterial::GetImageWidth(idMaterial *this)
{
  return this->stages->texture.image->uploadWidth;
}

// FUNC: public: int __thiscall idMaterial::GetImageHeight(void)const
int __thiscall idMaterial::GetImageHeight(idMaterial *this)
{
  return this->stages->texture.image->uploadHeight;
}

// FUNC: public: float const * __thiscall idMaterial::ConstantRegisters(void)const
float *__thiscall idMaterial::ConstantRegisters(idMaterial *this)
{
  if ( r_useConstantMaterials.internalVar->integerValue )
    return this->constantRegisters;
  else
    return 0;
}

// FUNC: public: virtual char const * __thiscall idMaterial::ImageName(void)const
char *__thiscall idMaterial::ImageName(idMaterial *this)
{
  idImage *image; // eax

  if ( this->numStages && (image = this->stages->texture.image) != 0 )
    return image->imgName.data;
  else
    return "_scratch";
}

// FUNC: public: virtual unsigned int __thiscall idMaterial::Size(void)const
int __thiscall idMaterial::Size(idMaterial *this)
{
  int alloced; // eax
  int v2; // esi
  int v3; // eax
  int v4; // esi
  int v5; // eax
  int v6; // esi
  int v7; // edx

  if ( this->desc.data == this->desc.baseBuffer )
    alloced = 0;
  else
    alloced = this->desc.alloced;
  v2 = alloced + 332;
  if ( this->renderBump.data == this->renderBump.baseBuffer )
    v3 = 0;
  else
    v3 = this->renderBump.alloced;
  v4 = v3 + v2;
  if ( this->materialTypeArrayName.data == this->materialTypeArrayName.baseBuffer )
    v5 = 0;
  else
    v5 = this->materialTypeArrayName.alloced;
  v6 = v5 + v4;
  if ( this->editorImageName.data == this->editorImageName.baseBuffer )
    v7 = 0;
  else
    v7 = this->editorImageName.alloced;
  return v6 + v7 + 4 * (this->numRegisters + 33 * this->numStages + 4 * this->numOps);
}

// FUNC: public: virtual bool __thiscall idMaterial::SetDefaultText(void)
char __thiscall idMaterial::SetDefaultText(idMaterial *this)
{
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // ebx
  const char *v5; // edi
  const char *v6; // eax
  const char *v8; // [esp-4h] [ebp-810h]
  char generated[2048]; // [esp+Ch] [ebp-800h] BYREF

  v2 = this->base->GetName(this->base);
  if ( !idStr::Icmpn(v2, "gfx/guis/", 9)
    || (v3 = this->base->GetName(this->base), v4 = &entityFilter, !idStr::Icmpn(v3, "fonts/", 6)) )
  {
    v4 = "nopicmip\n";
  }
  v5 = this->base->GetName(this->base);
  v6 = (const char *)((int (__thiscall *)(idDeclBase *, const char *))this->base->GetName)(this->base, v4);
  idStr::snPrintf(
    generated,
    2048,
    "material %s // IMPLICITLY GENERATED\n{\n{\nblend blend\ncolored\nmap \"%s\"\nclamp\n%s}\n}\n",
    v5,
    v6,
    v8);
  this->base->SetText(this->base, generated);
  return 1;
}

// FUNC: public: class idImage * __thiscall idMaterial::GetDiffuseImage(void)const
idImage *__thiscall idMaterial::GetDiffuseImage(idMaterial *this)
{
  if ( this->numStages <= 0 )
    return idMaterial::GetEditorImage(this);
  else
    return this->stages->texture.image;
}

// FUNC: public: virtual void __thiscall rvMaterialEditLocal::SetGui(class idMaterial *,char const *)
void __thiscall rvMaterialEditLocal::SetGui(rvMaterialEditLocal *this, idMaterial *edit, const char *name)
{
  edit->gui = uiManager->FindGui(uiManager, name, 1, 0, 1);
}

// FUNC: public: virtual int __thiscall rvMaterialEditLocal::GetImageWidth(class idMaterial const *)const
int __thiscall rvMaterialEditLocal::GetImageWidth(rvMaterialEditLocal *this, const idMaterial *edit)
{
  return edit->stages->texture.image->uploadWidth;
}

// FUNC: public: virtual int __thiscall rvMaterialEditLocal::GetImageHeight(class idMaterial const *)const
int __thiscall rvMaterialEditLocal::GetImageHeight(rvMaterialEditLocal *this, const idMaterial *edit)
{
  return edit->stages->texture.image->uploadHeight;
}

// FUNC: public: virtual __thiscall idMaterial::~idMaterial(void)
void __thiscall idMaterial::~idMaterial(idMaterial *this)
{
  this->__vftable = (idMaterial_vtbl *)&idMaterial::`vftable';
  idMaterial::FreeData(this);
  idStr::FreeData(&this->editorImageName);
  idStr::FreeData(&this->materialTypeArrayName);
  idStr::FreeData(&this->renderBump);
  idStr::FreeData(&this->desc);
  this->__vftable = (idMaterial_vtbl *)&idDecl::`vftable';
}

// FUNC: private: bool __thiscall idMaterial::ParseStage(class idLexer &,enum textureRepeat_t)
char __userpurge idMaterial::ParseStage@<al>(
        idMaterial *this@<ecx>,
        int a2@<edi>,
        expOpType_t a3@<esi>,
        idLexer *src,
        textureRepeat_t trpDefault)
{
  bool v6; // cc
  int v7; // edi
  int v8; // eax
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v10; // eax
  const char *v11; // eax
  int v12; // eax
  mtrParsingData_s *pd; // edx
  int v14; // eax
  shaderStage_t *v15; // ebx
  const char *v16; // eax
  unsigned int v17; // eax
  int v18; // edi
  idCinematic *v19; // eax
  int v20; // edi
  idCinematic *v21; // eax
  idCinematic *v22; // edi
  idCinematic *v23; // ecx
  idCinematic_vtbl *v24; // edx
  const char *v25; // eax
  const char *v26; // eax
  int v27; // edi
  int v28; // eax
  int v29; // edi
  int v30; // eax
  int v31; // edi
  int v32; // edi
  const char *v33; // eax
  int v34; // edi
  int ExpressionConstant; // eax
  int v36; // edi
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // edi
  int v42; // eax
  int v43; // eax
  int v44; // edi
  const idDecl *v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // ebx
  int v49; // eax
  int v50; // eax
  int v51; // edi
  int v52; // eax
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // eax
  int v57; // eax
  int v58; // eax
  int v59; // eax
  int v60; // eax
  int v61; // edi
  const char *v62; // eax
  int v63; // eax
  int v64; // eax
  rvNewShaderStage *v65; // edi
  rvGLSLShaderStage *v66; // eax
  rvNewShaderStage *v67; // eax
  bool v68; // zf
  netadrtype_t type; // eax
  char v70; // al
  idMegaTexture *v71; // edi
  int v72; // edi
  int v73; // edi
  newShaderStage_t *v74; // eax
  textureDepth_t v75; // edx
  idImage *v76; // eax
  idImage *v77; // eax
  int v78; // esi
  const char *v79; // eax
  char *data; // esi
  int v82; // edi
  const char *v83; // eax
  int v84; // [esp-10h] [ebp-584h]
  int v85; // [esp-10h] [ebp-584h]
  int v86; // [esp-8h] [ebp-57Ch]
  int v87; // [esp-8h] [ebp-57Ch]
  int v88; // [esp-8h] [ebp-57Ch]
  int v89; // [esp-8h] [ebp-57Ch]
  int v90; // [esp-8h] [ebp-57Ch]
  const char *v91; // [esp-4h] [ebp-578h]
  const char *v92; // [esp-4h] [ebp-578h]
  const char *v93; // [esp-4h] [ebp-578h]
  char *ad; // [esp+10h] [ebp-564h]
  int a; // [esp+10h] [ebp-564h]
  int aa; // [esp+10h] [ebp-564h]
  int ab; // [esp+10h] [ebp-564h]
  char *ae; // [esp+10h] [ebp-564h]
  int ac; // [esp+10h] [ebp-564h]
  bool skipWarning; // [esp+17h] [ebp-55Dh]
  textureRepeat_t trp; // [esp+18h] [ebp-55Ch]
  rvNewShaderStage *newShaderStage; // [esp+1Ch] [ebp-558h]
  int matrix[2][3]; // [esp+20h] [ebp-554h] BYREF
  idToken token; // [esp+38h] [ebp-53Ch] BYREF
  textureDepth_t td; // [esp+88h] [ebp-4ECh]
  int imageFlags; // [esp+8Ch] [ebp-4E8h]
  textureFilter_t v109; // [esp+90h] [ebp-4E4h]
  cubeFiles_t cubeMap; // [esp+94h] [ebp-4E0h]
  BOOL allowPicmip; // [esp+98h] [ebp-4DCh]
  shaderStage_t *v112; // [esp+9Ch] [ebp-4D8h]
  int loop; // [esp+A0h] [ebp-4D4h]
  idToken v114; // [esp+A4h] [ebp-4D0h] BYREF
  idToken v115; // [esp+F4h] [ebp-480h] BYREF
  idToken v116; // [esp+144h] [ebp-430h] BYREF
  idToken v117; // [esp+194h] [ebp-3E0h] BYREF
  idToken v118; // [esp+1E4h] [ebp-390h] BYREF
  idStr programName; // [esp+234h] [ebp-340h] BYREF
  idStr result; // [esp+254h] [ebp-320h] BYREF
  newShaderStage_t newStage; // [esp+274h] [ebp-300h] BYREF
  char imageName[256]; // [esp+468h] [ebp-10Ch] BYREF
  int v123; // [esp+570h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v6 = this->numStages < 256;
  v123 = 0;
  newShaderStage = 0;
  imageFlags = 0;
  skipWarning = 0;
  if ( !v6 )
  {
    this->materialFlags |= 1u;
    v7 = *(_DWORD *)common.type;
    v8 = ((int (__thiscall *)(idDeclBase *, int))this->base->GetName)(this->base, 256);
    (*(void (__cdecl **)(netadrtype_t, const char *, int))(v7 + 136))(
      common.type,
      "material '%s' exceeded %i stages",
      v8);
  }
  base = this->base;
  v10 = base->__vftable;
  v109 = TF_DEFAULT;
  trp = trpDefault;
  v11 = v10->GetName(base);
  v12 = idStr::Icmpn(v11, "lights/", 7);
  pd = this->pd;
  v14 = -(v12 != 0);
  LOBYTE(v14) = v14 & 0xFE;
  LOBYTE(allowPicmip) = 1;
  cubeMap = CF_2D;
  imageName[0] = 0;
  td = v14 + 4;
  memset(&newStage, 0, sizeof(newStage));
  v112 = &pd->parseStages[this->numStages];
  v15 = v112;
  idMaterial::ClearStage(this, v112);
  if ( (this->materialFlags & 1) != 0 )
    goto LABEL_277;
  while ( 1 )
  {
    if ( !idLexer::ExpectAnyToken(src, &token) )
      goto LABEL_276;
    if ( !idStr::Cmp(token.data, "}") )
    {
      if ( newStage.fragmentProgram || newStage.vertexProgram )
      {
        v74 = (newShaderStage_t *)Mem_Alloc(500, 0xDu);
        v15->newStage = v74;
        qmemcpy(v74, &newStage, sizeof(newShaderStage_t));
      }
      if ( newShaderStage )
      {
        v15->newShaderStage = newShaderStage;
        newShaderStage->Resolve(newShaderStage);
      }
      v75 = td;
      ++this->numStages;
      if ( v75 == TD_DEFAULT )
      {
        switch ( v15->lighting )
        {
          case SL_BUMP:
            v75 = TD_BUMP;
            break;
          case SL_DIFFUSE:
            v75 = TD_DIFFUSE;
            break;
          case SL_SPECULAR:
            v75 = TD_SPECULAR;
            break;
        }
      }
      if ( imageName[0] )
      {
        v76 = globalImages->ImageFromFile(globalImages, imageName, v109, allowPicmip, trp, v75, cubeMap, imageFlags);
        v15->texture.image = v76;
        if ( v76 )
        {
LABEL_271:
          v15->mNumStageRegisters = this->numRegisters - v15->mStageRegisterStart;
          v15->mNumStageOps = this->numOps - v15->mStageOpsStart;
          goto LABEL_277;
        }
        v77 = globalImages->GetDefaultImage(globalImages);
      }
      else
      {
        if ( skipWarning || v15->texture.cinematic || v15->texture.dynamic || v15->newStage || v15->newShaderStage )
          goto LABEL_271;
        v78 = *(_DWORD *)common.type;
        v79 = this->base->GetName(this->base);
        (*(void (**)(netadrtype_t, const char *, ...))(v78 + 136))(
          common.type,
          "material '%s' had stage with no image",
          v79);
        v77 = globalImages->GetDefaultImage(globalImages);
      }
      v15->texture.image = v77;
      goto LABEL_271;
    }
    if ( !idStr::Icmp(token.data, "name") )
    {
      idLexer::SkipRestOfLine(src);
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "blend") )
    {
      idMaterial::ParseBlend(this, src, v15);
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "map") )
    {
      v16 = R_ParsePastImageProgram(src);
      idStr::Copynz(imageName, v16, 256);
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "remoteRenderMap") )
    {
      v15->texture.dynamic = DI_REMOTE_RENDER;
      v15->texture.width = idLexer::ParseInt(src);
      v15->texture.height = idLexer::ParseInt(src);
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "mirrorRenderMap") )
    {
      v15->texture.dynamic = DI_MIRROR_RENDER;
      v15->texture.width = idLexer::ParseInt(src);
      v15->texture.height = idLexer::ParseInt(src);
      v15->texture.texgen = TG_SCREEN;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "reflectionRenderMap") )
    {
      v15->texture.dynamic = DI_REFLECTION_RENDER;
      v15->texture.width = idLexer::ParseInt(src);
      v15->texture.height = idLexer::ParseInt(src);
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "refractionRenderMap") )
    {
      v15->texture.dynamic = DI_REFRACTION_RENDER;
      v15->texture.width = idLexer::ParseInt(src);
      v15->texture.height = idLexer::ParseInt(src);
      v15->texture.texgen = TG_SCREEN;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "screen") )
    {
      v15->texture.texgen = TG_SCREEN;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "cubeRenderMap") )
    {
      v15->texture.dynamic = DI_CUBE_RENDER;
      v17 = idLexer::ParseInt(src);
      v15->texture.width = v17;
      v15->texture.height = v17;
      v15->texture.texgen = TG_REFLECT_CUBE;
      emptyCubeSize = v17;
      v15->texture.image = globalImages->ImageFromFunction(globalImages, "_emptyCubeMap", makeEmptyCubeMap);
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "screen2") )
    {
      v15->texture.texgen = TG_SCREEN2;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "glassWarp") )
    {
      v15->texture.texgen = TG_GLASSWARP;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "nomips") )
    {
      if ( com_makingBuild.internalVar->integerValue > 1 )
        imageFlags |= 1u;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "videomap") )
    {
      if ( idLexer::ReadToken(src, &token)
        && ((LOBYTE(loop) = 0, idStr::Icmp(token.data, "loop")) || (LOBYTE(loop) = 1, idLexer::ReadToken(src, &token))) )
      {
        v19 = idCinematic::Alloc();
        v86 = loop;
        v15->texture.cinematic = v19;
        v19->InitFromFile(v19, token.data, v86, 2);
      }
      else
      {
        v18 = *(_DWORD *)common.type;
        v91 = this->base->GetName(this->base);
        (*(void (__cdecl **)(netadrtype_t, const char *, const char *))(v18 + 136))(
          common.type,
          "missing parameter for 'videoMap' keyword in material '%s'",
          v91);
      }
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "soundmap") )
    {
      if ( idLexer::ReadToken(src, &token) )
      {
        v21 = (idCinematic *)Memory::Allocate(0x10u);
        v22 = v21;
        LOBYTE(v123) = 1;
        if ( v21 )
        {
          idCinematic::idCinematic(v21);
          v22->__vftable = (idCinematic_vtbl *)&idSndWindow::`vftable';
          LOBYTE(v22[1].__vftable) = 0;
          v23 = v22;
        }
        else
        {
          v23 = 0;
        }
        v15->texture.cinematic = v23;
        v24 = v23->__vftable;
        LOBYTE(v123) = 0;
        v24->InitFromFile(v23, token.data, 1, 2);
      }
      else
      {
        v20 = *(_DWORD *)common.type;
        v92 = this->base->GetName(this->base);
        (*(void (__cdecl **)(netadrtype_t, const char *, const char *))(v20 + 136))(
          common.type,
          "missing parameter for 'soundmap' keyword in material '%s'",
          v92);
      }
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "cubeMap") )
    {
      v25 = R_ParsePastImageProgram(src);
      idStr::Copynz(imageName, v25, 256);
      cubeMap = CF_NATIVE;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "cameraCubeMap") )
    {
      v26 = R_ParsePastImageProgram(src);
      idStr::Copynz(imageName, v26, 256);
      cubeMap = CF_CAMERA;
      gWriteProgramFlag = 1;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "ignoreAlphaTest") )
    {
      v15->ignoreAlphaTest = 1;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "nearest") )
    {
      v109 = TF_NEAREST;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "linear") )
    {
      v109 = TF_LINEAR;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "clamp") )
    {
      trp = TR_CLAMP;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "noclamp") )
    {
      trp = TR_REPEAT;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "zeroclamp") )
    {
      trp = TR_CLAMP_TO_ZERO;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "alphazeroclamp") )
    {
      trp = TR_CLAMP_TO_ZERO_ALPHA;
      goto LABEL_247;
    }
    if ( !idStr::Icmp(token.data, "mirroredrepeat") )
    {
      trp = TR_MIRRORED_REPEAT;
      goto LABEL_247;
    }
    if ( idStr::Icmp(token.data, "uncompressed") && idStr::Icmp(token.data, "highquality") )
      break;
    if ( !image_ignoreHighQuality.internalVar->integerValue )
LABEL_246:
      td = TD_HIGH_QUALITY;
LABEL_247:
    if ( (this->materialFlags & 1) != 0 )
      goto LABEL_277;
  }
  if ( !idStr::Icmp(token.data, "forceHighQuality") )
    goto LABEL_246;
  if ( !idStr::Icmp(token.data, "nopicmip") )
  {
    LOBYTE(allowPicmip) = 0;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "vertexColor") )
  {
    v15->vertexColor = SVC_MODULATE;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "inverseVertexColor") )
  {
    v15->vertexColor = SVC_INVERSE_MODULATE;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "privatePolygonOffset") )
  {
    if ( idLexer::ReadTokenOnLine(src, &token) )
    {
      idLexer::UnreadToken(src, &token);
      v15->privatePolygonOffset = idLexer::ParseFloat(src, 0);
    }
    else
    {
      v15->privatePolygonOffset = 1.0;
    }
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "texGen") )
  {
    idLexer::ExpectAnyToken(src, &token);
    if ( idStr::Icmp(token.data, "normal") )
    {
      if ( idStr::Icmp(token.data, "reflect") )
      {
        if ( idStr::Icmp(token.data, "skybox") )
        {
          if ( idStr::Icmp(token.data, "wobbleSky") )
          {
            if ( idStr::Icmp(token.data, "potCorrection") )
            {
              v32 = *(_DWORD *)common.type;
              ad = token.data;
              v33 = this->base->GetName(this->base);
              (*(void (**)(netadrtype_t, const char *, ...))(v32 + 136))(
                common.type,
                "bad texGen '%s' in material %s",
                ad,
                v33);
              this->materialFlags |= 1u;
            }
            else if ( !glConfig.textureNonPowerOfTwoAvailable )
            {
              v15->texture.texgen = TG_POT_CORRECTION;
            }
          }
          else
          {
            v117.floatvalue = 0.0;
            v15->texture.texgen = TG_WOBBLESKY_CUBE;
            v117.len = 0;
            v117.alloced = 20;
            v117.data = v117.baseBuffer;
            v117.baseBuffer[0] = 0;
            LOBYTE(v123) = 2;
            v27 = idMaterial::ParseExpressionPriority(this, src, 3);
            if ( (this->materialFlags & 1) != 0 )
            {
              LOBYTE(v123) = 0;
              idStr::FreeData(&v117);
              v28 = 0;
            }
            else
            {
              if ( idLexer::ReadToken(src, &v117) )
              {
                if ( idStr::Cmp(v117.data, "&&") )
                {
                  if ( idStr::Cmp(v117.data, "||") )
                    idLexer::UnreadToken(src, &v117);
                  else
                    v27 = idMaterial::ParseEmitOp(this, src, v27, OP_TYPE_OR, 4);
                }
                else
                {
                  v27 = idMaterial::ParseEmitOp(this, src, v27, OP_TYPE_AND, 4);
                }
              }
              LOBYTE(v123) = 0;
              idStr::FreeData(&v117);
              v28 = v27;
            }
            this->texGenRegisters[0] = v28;
            v114.floatvalue = 0.0;
            v114.len = 0;
            v114.alloced = 20;
            v114.data = v114.baseBuffer;
            v114.baseBuffer[0] = 0;
            LOBYTE(v123) = 3;
            v29 = idMaterial::ParseExpressionPriority(this, src, 3);
            if ( (this->materialFlags & 1) != 0 )
            {
              LOBYTE(v123) = 0;
              idStr::FreeData(&v114);
              v30 = 0;
            }
            else
            {
              if ( idLexer::ReadToken(src, &v114) )
              {
                if ( idStr::Cmp(v114.data, "&&") )
                {
                  if ( idStr::Cmp(v114.data, "||") )
                    idLexer::UnreadToken(src, &v114);
                  else
                    v29 = idMaterial::ParseEmitOp(this, src, v29, OP_TYPE_OR, 4);
                }
                else
                {
                  v29 = idMaterial::ParseEmitOp(this, src, v29, OP_TYPE_AND, 4);
                }
              }
              LOBYTE(v123) = 0;
              idStr::FreeData(&v114);
              v30 = v29;
            }
            v115.floatvalue = 0.0;
            this->texGenRegisters[1] = v30;
            v115.len = 0;
            v115.alloced = 20;
            v115.data = v115.baseBuffer;
            v115.baseBuffer[0] = 0;
            LOBYTE(v123) = 4;
            v31 = idMaterial::ParseExpressionPriority(this, src, 3);
            if ( (this->materialFlags & 1) != 0 )
            {
              LOBYTE(v123) = 0;
              idStr::FreeData(&v115);
              this->texGenRegisters[2] = 0;
            }
            else
            {
              if ( idLexer::ReadToken(src, &v115) )
              {
                if ( idStr::Cmp(v115.data, "&&") )
                {
                  if ( idStr::Cmp(v115.data, "||") )
                    idLexer::UnreadToken(src, &v115);
                  else
                    v31 = idMaterial::ParseEmitOp(this, src, v31, OP_TYPE_OR, 4);
                }
                else
                {
                  v31 = idMaterial::ParseEmitOp(this, src, v31, OP_TYPE_AND, 4);
                }
              }
              LOBYTE(v123) = 0;
              idStr::FreeData(&v115);
              this->texGenRegisters[2] = v31;
            }
          }
        }
        else
        {
          v15->texture.texgen = TG_SKYBOX_CUBE;
        }
      }
      else
      {
        v15->texture.texgen = TG_REFLECT_CUBE;
      }
    }
    else
    {
      v15->texture.texgen = TG_DIFFUSE_CUBE;
    }
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "scroll") || !idStr::Icmp(token.data, "translate") )
  {
    v116.floatvalue = 0.0;
    v116.len = 0;
    v116.alloced = 20;
    v116.data = v116.baseBuffer;
    v116.baseBuffer[0] = 0;
    LOBYTE(v123) = 5;
    v72 = idMaterial::ParseExpressionPriority(this, src, 3);
    if ( (this->materialFlags & 1) != 0 )
    {
      LOBYTE(v123) = 0;
      idStr::FreeData(&v116);
      ac = 0;
    }
    else
    {
      if ( idLexer::ReadToken(src, &v116) )
      {
        if ( idStr::Cmp(v116.data, "&&") )
        {
          if ( idStr::Cmp(v116.data, "||") )
            idLexer::UnreadToken(src, &v116);
          else
            v72 = idMaterial::ParseEmitOp(this, src, v72, OP_TYPE_OR, 4);
        }
        else
        {
          v72 = idMaterial::ParseEmitOp(this, src, v72, OP_TYPE_AND, 4);
        }
      }
      LOBYTE(v123) = 0;
      idStr::FreeData(&v116);
      ac = v72;
    }
    if ( !idLexer::ExpectTokenString(src, ",") )
      this->materialFlags |= 1u;
    v118.floatvalue = 0.0;
    v118.len = 0;
    v118.alloced = 20;
    v118.data = v118.baseBuffer;
    v118.baseBuffer[0] = 0;
    LOBYTE(v123) = 6;
    v73 = idMaterial::ParseExpressionPriority(this, src, 3);
    if ( (this->materialFlags & 1) != 0 )
    {
      LOBYTE(v123) = 0;
      idStr::FreeData(&v118);
      v73 = 0;
    }
    else
    {
      if ( idLexer::ReadToken(src, &v118) )
      {
        if ( idStr::Cmp(v118.data, "&&") )
        {
          if ( idStr::Cmp(v118.data, "||") )
            idLexer::UnreadToken(src, &v118);
          else
            v73 = idMaterial::ParseEmitOp(this, src, v73, OP_TYPE_OR, 4);
        }
        else
        {
          v73 = idMaterial::ParseEmitOp(this, src, v73, OP_TYPE_AND, 4);
        }
      }
      LOBYTE(v123) = 0;
      idStr::FreeData(&v118);
    }
    matrix[0][0] = idMaterial::GetExpressionConstant(this, 1.0);
    *(_QWORD *)&matrix[0][1] = __PAIR64__(ac, idMaterial::GetExpressionConstant(this, 0.0));
    matrix[1][0] = idMaterial::GetExpressionConstant(this, 0.0);
    *(_QWORD *)&matrix[1][1] = __PAIR64__(v73, idMaterial::GetExpressionConstant(this, 1.0));
    idMaterial::MultiplyTextureMatrix(this, &v15->texture, matrix);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "scale") )
  {
    a = idMaterial::ParseExpressionPriority(this, src, 4);
    if ( !idLexer::ExpectTokenString(src, ",") )
      this->materialFlags |= 1u;
    v34 = idMaterial::ParseExpressionPriority(this, src, 4);
    matrix[0][0] = a;
    matrix[0][1] = idMaterial::GetExpressionConstant(this, 0.0);
    matrix[0][2] = idMaterial::GetExpressionConstant(this, 0.0);
    *(_QWORD *)&matrix[1][0] = __PAIR64__(v34, idMaterial::GetExpressionConstant(this, 0.0));
    ExpressionConstant = idMaterial::GetExpressionConstant(this, 0.0);
LABEL_122:
    matrix[1][2] = ExpressionConstant;
    idMaterial::MultiplyTextureMatrix(this, &v15->texture, matrix);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "centerScale") )
  {
    aa = idMaterial::ParseExpressionPriority(this, src, 4);
    if ( !idLexer::ExpectTokenString(src, ",") )
      this->materialFlags |= 1u;
    v36 = idMaterial::ParseExpressionPriority(this, src, 4);
    matrix[0][0] = aa;
    matrix[0][1] = idMaterial::GetExpressionConstant(this, 0.0);
    v37 = idMaterial::GetExpressionConstant(this, 0.5);
    v87 = idMaterial::EmitOp(this, v37, aa, OP_TYPE_MULTIPLY);
    v38 = idMaterial::GetExpressionConstant(this, 0.5);
    matrix[0][2] = idMaterial::EmitOp(this, v38, v87, OP_TYPE_SUBTRACT);
    *(_QWORD *)&matrix[1][0] = __PAIR64__(v36, idMaterial::GetExpressionConstant(this, 0.0));
    v39 = idMaterial::GetExpressionConstant(this, 0.5);
    v88 = idMaterial::EmitOp(this, v39, v36, OP_TYPE_MULTIPLY);
    v40 = idMaterial::GetExpressionConstant(this, 0.5);
    matrix[1][2] = idMaterial::EmitOp(this, v40, v88, OP_TYPE_SUBTRACT);
    idMaterial::MultiplyTextureMatrix(this, &v15->texture, matrix);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "shear") )
  {
    ab = idMaterial::ParseExpressionPriority(this, src, 4);
    if ( !idLexer::ExpectTokenString(src, ",") )
      this->materialFlags |= 1u;
    v41 = idMaterial::ParseExpressionPriority(this, src, 4);
    *(_QWORD *)&matrix[0][0] = __PAIR64__(ab, idMaterial::GetExpressionConstant(this, 1.0));
    v42 = idMaterial::GetExpressionConstant(this, -0.5);
    matrix[0][2] = idMaterial::EmitOp(this, v42, ab, OP_TYPE_MULTIPLY);
    matrix[1][0] = v41;
    matrix[1][1] = idMaterial::GetExpressionConstant(this, 1.0);
    v43 = idMaterial::GetExpressionConstant(this, -0.5);
    ExpressionConstant = idMaterial::EmitOp(this, v43, v41, OP_TYPE_MULTIPLY);
    goto LABEL_122;
  }
  if ( !idStr::Icmp(token.data, "rotate") )
  {
    v44 = idMaterial::ParseExpressionPriority(this, src, 4);
    v45 = declManager->FindType(declManager, 0, "sinTable", 0, 0);
    if ( !v45 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "no sinTable for rotate defined");
      goto LABEL_276;
    }
    v46 = ((int (__thiscall *)(idDeclBase *, int, int))v45->base->Index)(v45->base, v44, 5);
    v47 = idMaterial::EmitOp(this, v46, a2, a3);
    a3 = OP_TYPE_ADD;
    a2 = 0;
    v48 = v47;
    v49 = ((int (__thiscall *)(idDeclManager *, _DWORD, const char *))declManager->FindType)(declManager, 0, "cosTable");
    if ( !v49 )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
        common.type,
        "no cosTable for rotate defined");
      goto LABEL_276;
    }
    v50 = (*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v49 + 4) + 36))(*(_DWORD *)(v49 + 4));
    v51 = idMaterial::EmitOp(this, v50, v44, OP_TYPE_TABLE);
    matrix[0][0] = v51;
    v52 = idMaterial::GetExpressionConstant(this, 0.0);
    matrix[0][1] = idMaterial::EmitOp(this, v52, v48, OP_TYPE_SUBTRACT);
    v89 = idMaterial::GetExpressionConstant(this, 0.5);
    v53 = idMaterial::GetExpressionConstant(this, 0.5);
    v84 = idMaterial::EmitOp(this, v53, v48, OP_TYPE_MULTIPLY);
    v54 = idMaterial::GetExpressionConstant(this, -0.5);
    v55 = idMaterial::EmitOp(this, v54, v51, OP_TYPE_MULTIPLY);
    v56 = idMaterial::EmitOp(this, v55, v84, OP_TYPE_ADD);
    matrix[0][2] = idMaterial::EmitOp(this, v56, v89, OP_TYPE_ADD);
    *(_QWORD *)&matrix[1][0] = __PAIR64__(v51, v48);
    v90 = idMaterial::GetExpressionConstant(this, 0.5);
    v57 = idMaterial::GetExpressionConstant(this, -0.5);
    v85 = idMaterial::EmitOp(this, v57, v51, OP_TYPE_MULTIPLY);
    v58 = idMaterial::GetExpressionConstant(this, -0.5);
    v59 = idMaterial::EmitOp(this, v58, v48, OP_TYPE_MULTIPLY);
    v60 = idMaterial::EmitOp(this, v59, v85, OP_TYPE_ADD);
    matrix[1][2] = idMaterial::EmitOp(this, v60, v90, OP_TYPE_ADD);
    idMaterial::MultiplyTextureMatrix(this, &v112->texture, matrix);
    v15 = v112;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "maskRed") )
  {
    BYTE1(v15->drawStateBits) |= 2u;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "maskGreen") )
  {
    BYTE1(v15->drawStateBits) |= 4u;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "maskBlue") )
  {
    BYTE1(v15->drawStateBits) |= 8u;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "maskAlpha") )
  {
    BYTE1(v15->drawStateBits) |= 0x10u;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "maskColor") )
  {
    BYTE1(v15->drawStateBits) |= 0xEu;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "maskDepth") )
  {
    BYTE1(v15->drawStateBits) |= 1u;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "alphaTest") )
  {
    v15->hasAlphaTest = 1;
    v15->alphaTestRegister = idMaterial::ParseExpressionPriority(this, src, 4);
    this->coverage = MC_PERFORATED;
    if ( !v15->hasAlphaFunc )
      v15->alphaTestMode = 516;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "alphaFunc") )
  {
    v15->hasAlphaFunc = 1;
    v15->hasAlphaTest = 1;
    v15->alphaTestMode = 516;
    if ( idLexer::ReadToken(src, &token) )
    {
      if ( idStr::Icmp(token.data, "less") )
      {
        if ( idStr::Icmp(token.data, "equal") )
        {
          if ( idStr::Icmp(token.data, "greater") )
          {
            v61 = *(_DWORD *)common.type;
            ae = token.data;
            v62 = this->base->GetName(this->base);
            (*(void (**)(netadrtype_t, const char *, ...))(v61 + 136))(
              common.type,
              "unknown alpha func '%s' in material '%s'",
              ae,
              v62);
          }
          else
          {
            v15->alphaTestMode = 516;
          }
        }
        else
        {
          v15->alphaTestMode = 514;
        }
      }
      else
      {
        v15->alphaTestMode = 513;
      }
    }
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "colored") )
  {
    v15->color.registers[0] = 1;
    v15->color.registers[1] = 2;
    v15->color.registers[2] = 3;
    v15->color.registers[3] = 4;
    this->pd->registersAreConstant = 0;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "color") )
  {
    v15->color.registers[0] = idMaterial::ParseExpressionPriority(this, src, 4);
    if ( !idLexer::ExpectTokenString(src, ",") )
      this->materialFlags |= 1u;
    v15->color.registers[1] = idMaterial::ParseExpressionPriority(this, src, 4);
    if ( !idLexer::ExpectTokenString(src, ",") )
      this->materialFlags |= 1u;
    v15->color.registers[2] = idMaterial::ParseExpressionPriority(this, src, 4);
    if ( !idLexer::ExpectTokenString(src, ",") )
      this->materialFlags |= 1u;
LABEL_176:
    v15->color.registers[3] = idMaterial::ParseExpressionPriority(this, src, 4);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "red") )
  {
    v15->color.registers[0] = idMaterial::ParseExpressionPriority(this, src, 4);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "green") )
  {
    v15->color.registers[1] = idMaterial::ParseExpressionPriority(this, src, 4);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "blue") )
  {
    v15->color.registers[2] = idMaterial::ParseExpressionPriority(this, src, 4);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "alpha") )
    goto LABEL_176;
  if ( !idStr::Icmp(token.data, "rgb") )
  {
    v63 = idMaterial::ParseExpressionPriority(this, src, 4);
    v15->color.registers[2] = v63;
    v15->color.registers[1] = v63;
    v15->color.registers[0] = v63;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "rgba") )
  {
    v64 = idMaterial::ParseExpressionPriority(this, src, 4);
    v15->color.registers[3] = v64;
    v15->color.registers[2] = v64;
    v15->color.registers[1] = v64;
    v15->color.registers[0] = v64;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "if") )
  {
    v15->conditionRegister = idMaterial::ParseExpressionPriority(this, src, 4);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "program") )
  {
    if ( idLexer::ReadTokenOnLine(src, &token) )
    {
      newStage.vertexProgram = R_FindARBProgram(0x8620u, token.data);
      newStage.fragmentProgram = R_FindARBProgram(0x8804u, token.data);
      if ( !newStage.fragmentProgram )
      {
        newStage.vertexProgram = 0;
        skipWarning = 1;
      }
      operator+(&programName, "md5r", &token);
      LOBYTE(v123) = 7;
      newStage.md5rVertexProgram = R_FindARBProgram(0x8620u, programName.data);
      LOBYTE(v123) = 0;
      idStr::FreeData(&programName);
    }
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "glslProgram") )
  {
    v65 = newShaderStage;
    if ( newShaderStage )
    {
      v68 = (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 96))(common.type) == 0;
      type = common.type;
      if ( !v68 )
        goto LABEL_274;
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(
        common.type,
        "ParseStage - glslProgram: Shader program already set!");
    }
    else
    {
      v66 = (rvGLSLShaderStage *)Memory::Allocate(0x174Cu);
      LOBYTE(v123) = 8;
      if ( v66 )
      {
        rvGLSLShaderStage::rvGLSLShaderStage(v66);
        v65 = v67;
        LOBYTE(v123) = 0;
        newShaderStage = v67;
      }
      else
      {
        v65 = 0;
        LOBYTE(v123) = 0;
        newShaderStage = 0;
      }
    }
    if ( !v65->ParseProgram(v65, src, this) )
      skipWarning = 1;
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "shaderParm") )
  {
    if ( newShaderStage )
    {
      newShaderStage->ParseShaderParm(newShaderStage, src, this);
      goto LABEL_247;
    }
    v70 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 96))(common.type);
    v93 = "ParseStage: shaderParm set before shader type declared.";
    goto LABEL_204;
  }
  if ( !idStr::Icmp(token.data, "shaderTexture") )
  {
    if ( newShaderStage )
    {
      newShaderStage->ParseTextureParm(newShaderStage, src, this, trpDefault);
      goto LABEL_247;
    }
    v70 = (*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 96))(common.type);
    v93 = "ParseStage: shaderTexture set before shader type declared.";
LABEL_204:
    v68 = v70 == 0;
    type = common.type;
    if ( !v68 )
    {
LABEL_274:
      (*(void (**)(void))(*(_DWORD *)type + 136))();
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(common.type, "(FatalError)\n");
      v123 = -1;
      idStr::FreeData(&token);
      return 0;
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 156))(common.type, v93);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "fragmentProgram") )
  {
    if ( idLexer::ReadTokenOnLine(src, &token) )
      newStage.fragmentProgram = R_FindARBProgram(0x8804u, token.data);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "vertexProgram") )
  {
    if ( idLexer::ReadTokenOnLine(src, &token) )
    {
      newStage.vertexProgram = R_FindARBProgram(0x8620u, token.data);
      operator+(&result, "md5r", &token);
      LOBYTE(v123) = 9;
      newStage.md5rVertexProgram = R_FindARBProgram(0x8620u, result.data);
      LOBYTE(v123) = 0;
      idStr::FreeData(&result);
    }
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "megaTexture") && idLexer::ReadTokenOnLine(src, &token) )
  {
    v71 = (idMegaTexture *)Memory::Allocate(0x7F4u);
    newStage.megaTexture = v71;
    if ( idMegaTexture::InitFromMegaFile(v71, token.data) )
    {
      newStage.vertexProgram = R_FindARBProgram(0x8620u, "megaTexture.vfp");
      newStage.fragmentProgram = R_FindARBProgram(0x8804u, "megaTexture.vfp");
    }
    else
    {
      Memory::Free(v71);
      this->materialFlags |= 1u;
    }
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "vertexParm") )
  {
    idMaterial::ParseVertexParm(this, src, &newStage);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "fragmentParm") )
  {
    idMaterial::ParseFragmentParm(this, src, &newStage);
    goto LABEL_247;
  }
  if ( !idStr::Icmp(token.data, "fragmentMap") )
  {
    idMaterial::ParseFragmentMap(this, src, &newStage);
    goto LABEL_247;
  }
  data = token.data;
  v82 = *(_DWORD *)common.type;
  v83 = this->base->GetName(this->base);
  (*(void (**)(netadrtype_t, const char *, ...))(v82 + 136))(
    common.type,
    "unknown token '%s' in material '%s'",
    data,
    v83);
LABEL_276:
  this->materialFlags |= 1u;
LABEL_277:
  v123 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: private: bool __thiscall idMaterial::AddImplicitStages(enum textureRepeat_t)
char __thiscall idMaterial::AddImplicitStages(idMaterial *this, expOpType_t trpDefault)
{
  int numStages; // esi
  char v4; // bl
  char v5; // dl
  stageLighting_t *p_lighting; // eax
  int v7; // edi
  stageLighting_t v8; // ecx
  bool hasSpecular; // [esp+12h] [ebp-4D6h]
  bool hasReflection; // [esp+13h] [ebp-4D5h]
  idLexer newSrc; // [esp+14h] [ebp-4D4h] BYREF
  char buffer[1024]; // [esp+DCh] [ebp-40Ch] BYREF
  int v14; // [esp+4E4h] [ebp-4h]

  idLexer::idLexer(&newSrc);
  numStages = this->numStages;
  v4 = 0;
  v5 = 0;
  v14 = 0;
  hasSpecular = 0;
  hasReflection = 0;
  if ( numStages > 0 )
  {
    p_lighting = &this->pd->parseStages[0].lighting;
    v7 = numStages;
    do
    {
      v8 = *p_lighting;
      if ( *p_lighting == SL_BUMP )
        v5 = 1;
      if ( v8 == SL_DIFFUSE )
        v4 = 1;
      if ( v8 == SL_SPECULAR )
        hasSpecular = 1;
      if ( *((_DWORD *)p_lighting + 11) == 2 )
        hasReflection = 1;
      p_lighting += 33;
      --v7;
    }
    while ( v7 );
    if ( (v5 || v4 || hasSpecular) && numStages != 256 )
    {
      if ( !v5 )
      {
        idStr::snPrintf(buffer, 1024, "blend bumpmap\nmap _flat\n}\n");
        idLexer::LoadMemory(&newSrc, buffer, strlen(buffer), "bumpmap", 1);
        newSrc.flags = 156;
        if ( !idMaterial::ParseStage(this, 156, trpDefault, &newSrc, (textureRepeat_t)trpDefault) )
        {
LABEL_23:
          v14 = -1;
          idLexer::~idLexer(&newSrc);
          return 0;
        }
        idLexer::FreeSource(&newSrc);
      }
      if ( !v4 && !hasSpecular && !hasReflection )
      {
        idStr::snPrintf(buffer, 1024, "blend diffusemap\nmap _white\n}\n");
        idLexer::LoadMemory(&newSrc, buffer, strlen(buffer), "diffusemap", 1);
        newSrc.flags = 156;
        if ( !idMaterial::ParseStage(this, 156, trpDefault, &newSrc, (textureRepeat_t)trpDefault) )
          goto LABEL_23;
        idLexer::FreeSource(&newSrc);
      }
    }
  }
  v14 = -1;
  idLexer::~idLexer(&newSrc);
  return 1;
}

// FUNC: private: bool __thiscall idMaterial::ParseMaterial(class idLexer &)
char __thiscall idMaterial::ParseMaterial(idMaterial *this, idLexer *src)
{
  textureRepeat_t v2; // ebx
  int v4; // eax
  bool v5; // zf
  idLexer *v6; // esi
  const rvDeclMatType *v7; // eax
  char *data; // ebx
  int v9; // edi
  const char *v10; // eax
  int len; // ebx
  char *v12; // ecx
  char *v13; // edx
  char v14; // al
  int v15; // eax
  char *v16; // eax
  const char *v17; // eax
  const char *v18; // eax
  const char *v19; // eax
  int v20; // ecx
  texgen_t *p_texgen; // eax
  int v22; // edx
  texgen_t v23; // esi
  texgen_t *v24; // eax
  int v25; // esi
  const char *v26; // eax
  char *v28; // esi
  int v29; // edi
  const char *v30; // eax
  idStr v31; // [esp-28h] [ebp-584h] BYREF
  idLexer *p_MTAWidth; // [esp-8h] [ebp-564h]
  int *p_MTAHeight; // [esp-4h] [ebp-560h]
  int v34; // [esp+0h] [ebp-55Ch]
  int v35; // [esp+4h] [ebp-558h]
  textureRepeat_t trpDefault; // [esp+10h] [ebp-54Ch]
  idToken token; // [esp+14h] [ebp-548h] BYREF
  idStr *v38; // [esp+64h] [ebp-4F8h]
  idStr copy; // [esp+68h] [ebp-4F4h] BYREF
  idLexer newSrc; // [esp+88h] [ebp-4D4h] BYREF
  char buffer[1024]; // [esp+150h] [ebp-40Ch] BYREF
  int v42; // [esp+558h] [ebp-4h]

  token.floatvalue = 0.0;
  v2 = TR_REPEAT;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v42 = 0;
  idLexer::idLexer(&newSrc);
  LOBYTE(v42) = 1;
  this->numOps = 0;
  this->numRegisters = 22;
  v4 = 0;
  do
    this->pd->registerIsTemporary[v4++] = 1;
  while ( v4 < this->numRegisters );
  v5 = (this->materialFlags & 1) == 0;
  this->numStages = 0;
  trpDefault = TR_REPEAT;
  if ( !v5 )
    goto LABEL_137;
  v6 = src;
  while ( idLexer::ExpectAnyToken(v6, &token) )
  {
    if ( !idStr::Cmp(token.data, "}") )
    {
      idMaterial::AddImplicitStages(this, OP_TYPE_ADD);
      idMaterial::SortInteractionStages(this);
      if ( this->cullType == CT_TWO_SIDED )
      {
        v20 = 0;
        if ( this->numStages > 0 )
        {
          p_texgen = &this->pd->parseStages[0].texture.texgen;
          while ( !*((_DWORD *)p_texgen - 11) && *p_texgen == TG_EXPLICIT )
          {
            ++v20;
            p_texgen += 33;
            if ( v20 >= this->numStages )
              goto LABEL_125;
          }
          this->cullType = CT_FRONT_SIDED;
          this->shouldCreateBackSides = 1;
        }
      }
LABEL_125:
      v22 = 0;
      v23 = TG_EXPLICIT;
      if ( this->numStages <= 0 )
        goto LABEL_137;
      v24 = &this->pd->parseStages[0].texture.texgen;
      while ( 1 )
      {
        if ( *v24 )
        {
          if ( v23 )
          {
            if ( v23 != *v24 )
            {
              v25 = *(_DWORD *)common.type;
              v26 = this->base->GetName(this->base);
              (*(void (**)(netadrtype_t, const char *, ...))(v25 + 136))(
                common.type,
                "material '%s' has multiple stages with a texgen",
                v26);
              goto LABEL_137;
            }
          }
          else
          {
            v23 = *v24;
          }
        }
        ++v22;
        v24 += 33;
        if ( v22 >= this->numStages )
          goto LABEL_137;
      }
    }
    if ( !idStr::Icmp(token.data, "qer_editorimage") )
    {
      idLexer::ReadTokenOnLine(v6, &token);
      idStr::operator=(&this->editorImageName, token.data);
      idLexer::SkipRestOfLine(v6);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "description") )
    {
      idLexer::ReadTokenOnLine(v6, &token);
      idStr::operator=(&this->desc, token.data);
      goto LABEL_115;
    }
    if ( idMaterial::CheckSurfaceParm(this, &token) )
      goto LABEL_115;
    if ( !idStr::Icmp(token.data, "polygonOffset") )
    {
      this->materialFlags |= 2u;
      if ( idLexer::ReadTokenOnLine(v6, &token) )
      {
        if ( token.type == 3 )
        {
          if ( (token.subtype & 0x10000) == 0 )
            idToken::NumberValue(&token);
          this->polygonOffset = token.floatvalue;
        }
        else
        {
          this->polygonOffset = 0.0;
        }
      }
      else
      {
        this->polygonOffset = 1.0;
      }
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "noShadows") )
    {
      this->materialFlags |= 4u;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "needCurrentRender") )
    {
      BYTE1(this->materialFlags) |= 1u;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "suppressInSubview") )
    {
      this->suppressInSubview = 1;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "portalSky") )
    {
      this->portalSky = 1;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "noSelfShadow") )
    {
      this->materialFlags |= 0x10u;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "noPortalFog") )
    {
      this->materialFlags |= 0x20u;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "forceShadows") )
    {
      this->materialFlags |= 8u;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "materialType") )
    {
      idLexer::ReadTokenOnLine(v6, &token);
      v7 = (const rvDeclMatType *)declManager->FindType(declManager, 6, token.data, 1, 0);
      this->materialType = v7;
      if ( ((unsigned __int8 (__thiscall *)(idDeclBase *, int, int))v7->base->IsImplicit)(v7->base, v34, v35) )
      {
        data = token.data;
        v9 = *(_DWORD *)common.type;
        v10 = this->base->GetName(this->base);
        (*(void (**)(netadrtype_t, const char *, ...))(v9 + 136))(
          common.type,
          "UNKNOWN: materialType '%s' in '%s'",
          data,
          v10);
        v2 = trpDefault;
      }
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "materialImage") )
    {
      idLexer::ReadTokenOnLine(v6, &token);
      p_MTAHeight = &this->MTAHeight;
      p_MTAWidth = (idLexer *)&this->MTAWidth;
      v31.alloced = 20;
      v31.data = v31.baseBuffer;
      v31.len = 0;
      v31.baseBuffer[0] = 0;
      len = token.len;
      v38 = &v31;
      if ( token.len + 1 > 20 )
        idStr::ReAllocate(&v31, token.len + 1, 1);
      v12 = token.data;
      v13 = v31.data;
      do
      {
        v14 = *v12;
        *v13++ = *v12++;
      }
      while ( v14 );
      v31.len = len;
      this->materialTypeArray = MT_GetMaterialTypeArray(v31, &p_MTAWidth->loaded, p_MTAHeight);
      v38 = (idStr *)token.len;
      if ( token.len + 1 > this->materialTypeArrayName.alloced )
        idStr::ReAllocate(&this->materialTypeArrayName, token.len + 1, 0);
      v15 = (int)v38;
      qmemcpy(this->materialTypeArrayName.data, token.data, (unsigned int)v38);
      v6 = src;
      this->materialTypeArrayName.data[v15] = 0;
      this->materialTypeArrayName.len = v15;
      v2 = trpDefault;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "sky") )
    {
      LOBYTE(this->materialFlags) |= 0x80u;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "portalDistanceNear") )
    {
      this->portalDistanceNear = idLexer::ParseFloat(v6, 0);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "portalDistanceFar") )
    {
      this->portalDistanceFar = idLexer::ParseFloat(v6, 0);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "portalImage") )
    {
      idLexer::ReadTokenOnLine(v6, &token);
      this->portalImage = globalImages->ImageFromFile(globalImages, token.data, 2, 1, 1, 2, 0, 0);
      idLexer::SkipRestOfLine(v6);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "noOverlays") )
    {
      this->allowOverlays = 0;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "forceOverlays") )
    {
      this->pd->forceOverlays = 1;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "translucent") )
    {
      this->coverage = MC_TRANSLUCENT;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "zeroclamp") )
    {
      v2 = TR_CLAMP_TO_ZERO;
      trpDefault = TR_CLAMP_TO_ZERO;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "clamp") )
    {
      v2 = TR_CLAMP;
      trpDefault = TR_CLAMP;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "alphazeroclamp") )
    {
      v2 = TR_CLAMP_TO_ZERO;
      trpDefault = TR_CLAMP_TO_ZERO;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "forceOpaque") )
    {
      this->coverage = MC_OPAQUE;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "twoSided") )
    {
      this->materialFlags |= 4u;
      this->cullType = CT_TWO_SIDED;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "backSided") )
    {
      this->materialFlags |= 4u;
      this->cullType = CT_BACK_SIDED;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "fogLight") )
    {
      this->fogLight = 1;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "blendLight") )
    {
      this->blendLight = 1;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "ambientLight") )
    {
      this->ambientLight = 1;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "mirror") )
    {
      this->sort = -4.0;
      this->coverage = MC_OPAQUE;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "noFog") )
    {
      this->noFog = 1;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "unsmoothedTangents") )
    {
      this->unsmoothedTangents = 1;
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "lightFalloffImage") )
    {
      v16 = (char *)R_ParsePastImageProgram(v6);
      copy.len = 0;
      copy.alloced = 20;
      copy.data = copy.baseBuffer;
      copy.baseBuffer[0] = 0;
      LOBYTE(v42) = 2;
      idStr::operator=(&copy, v16);
      this->lightFalloffImage = globalImages->ImageFromFile(globalImages, copy.data, 2, 0, 1, 4, 0, 0);
      LOBYTE(v42) = 1;
      idStr::FreeData(&copy);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "guisurf") )
    {
      idLexer::ReadTokenOnLine(v6, &token);
      if ( idStr::Icmp(token.data, "entity") )
      {
        if ( idStr::Icmp(token.data, "entity2") )
        {
          if ( idStr::Icmp(token.data, "entity3") )
            this->gui = uiManager->FindGui(uiManager, token.data, 1, 0, 0);
          else
            this->entityGui = 3;
        }
        else
        {
          this->entityGui = 2;
        }
      }
      else
      {
        this->entityGui = 1;
      }
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "sort") )
    {
      idMaterial::ParseSort(this, v6);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "spectrum") )
    {
      idLexer::ReadTokenOnLine(v6, &token);
      this->spectrum = atoi(token.data);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "deform") )
    {
      idMaterial::ParseDeform(this, v6);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "decalInfo") )
    {
      idMaterial::ParseDecalInfo(this, v6);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "renderbump") )
    {
      idLexer::ParseRestOfLine(v6, &this->renderBump);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "diffusemap") )
    {
      v17 = R_ParsePastImageProgram(v6);
      idStr::snPrintf(buffer, 1024, "blend diffusemap\nmap %s\n}\n", v17);
      idLexer::LoadMemory(&newSrc, buffer, strlen(buffer), "diffusemap", 1);
      p_MTAHeight = (int *)v2;
      p_MTAWidth = &newSrc;
LABEL_105:
      newSrc.flags = 156;
      if ( !idMaterial::ParseStage(this, 156, (expOpType_t)v6, p_MTAWidth, (textureRepeat_t)p_MTAHeight) )
        goto LABEL_134;
      idLexer::FreeSource(&newSrc);
      goto LABEL_115;
    }
    if ( !idStr::Icmp(token.data, "specularmap") )
    {
      v18 = R_ParsePastImageProgram(v6);
      idStr::snPrintf(buffer, 1024, "blend specularmap\nmap %s\n}\n", v18);
      idLexer::LoadMemory(&newSrc, buffer, strlen(buffer), "specularmap", 1);
      p_MTAHeight = (int *)v2;
      p_MTAWidth = &newSrc;
      goto LABEL_105;
    }
    if ( !idStr::Icmp(token.data, "bumpmap") )
    {
      v19 = R_ParsePastImageProgram(v6);
      idStr::snPrintf(buffer, 1024, "blend bumpmap\nmap %s\n}\n", v19);
      idLexer::LoadMemory(&newSrc, buffer, strlen(buffer), "bumpmap", 1);
      p_MTAHeight = (int *)v2;
      p_MTAWidth = &newSrc;
      goto LABEL_105;
    }
    if ( idStr::Icmp(token.data, "DECAL_MACRO") )
    {
      if ( idStr::Cmp(token.data, "{") )
      {
        v28 = token.data;
        v29 = *(_DWORD *)common.type;
        v30 = this->base->GetName(this->base);
        (*(void (**)(netadrtype_t, const char *, ...))(v29 + 136))(
          common.type,
          "unknown general material parameter '%s' in '%s'",
          v28,
          v30);
        break;
      }
      if ( !idMaterial::ParseStage(this, 156, (expOpType_t)v6, v6, v2) )
      {
LABEL_134:
        LOBYTE(v42) = 0;
        idLexer::~idLexer(&newSrc);
        v42 = -1;
        idStr::FreeData(&token);
        return 0;
      }
    }
    else
    {
      BYTE1(this->surfaceFlags) |= 0x40u;
      this->contentFlags &= ~1u;
      this->materialFlags |= 6u;
      this->polygonOffset = 1.0;
      this->sort = 2.0;
    }
LABEL_115:
    if ( (this->materialFlags & 1) != 0 )
      goto LABEL_137;
  }
  this->materialFlags |= 1u;
LABEL_137:
  LOBYTE(v42) = 0;
  idLexer::~idLexer(&newSrc);
  v42 = -1;
  idStr::FreeData(&token);
  return 1;
}

// FUNC: public: virtual bool __thiscall idMaterial::Parse(char const *,int,bool)
char __thiscall idMaterial::Parse(idMaterial *this, const char *text, int textLength, bool noCaching)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // edx
  const char *v7; // edi
  int v8; // eax
  int numStages; // edi
  int v10; // eax
  stageLighting_t *p_lighting; // ecx
  int v12; // eax
  dynamicidImage_t *p_dynamic; // ecx
  int v14; // eax
  materialCoverage_t coverage; // eax
  int v16; // ebx
  shaderStage_t *v17; // edi
  newShaderStage_t *newStage; // eax
  int v19; // ebx
  newShaderStage_t *v20; // edi
  int v21; // eax
  int v22; // edi
  int v23; // edx
  int v24; // ecx
  int v25; // eax
  shaderStage_t *v26; // eax
  mtrParsingData_s *pd; // edx
  int v28; // ebx
  int numOps; // eax
  expOp_t *v30; // eax
  mtrParsingData_s *v31; // edx
  int numRegisters; // eax
  float *v33; // eax
  mtrParsingData_s *v34; // edx
  float *v35; // edx
  bool v36; // zf
  int v38; // [esp+0h] [ebp-1D7FCh]
  int v39; // [esp+0h] [ebp-1D7FCh]
  int i; // [esp+10h] [ebp-1D7ECh]
  shaderStage_t *pStage; // [esp+14h] [ebp-1D7E8h]
  int j; // [esp+18h] [ebp-1D7E4h]
  idToken token; // [esp+1Ch] [ebp-1D7E0h] BYREF
  float shaderParms[12]; // [esp+6Ch] [ebp-1D790h] BYREF
  idLexer src; // [esp+9Ch] [ebp-1D760h] BYREF
  viewDef_s view; // [esp+164h] [ebp-1D698h] BYREF
  mtrParsingData_s parsingData; // [esp+3E4h] [ebp-1D418h] BYREF
  int v48; // [esp+1D7F8h] [ebp-4h]

  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v48 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  base = this->base;
  v6 = base->__vftable;
  LOBYTE(v48) = 1;
  v7 = v6->GetFileName(base);
  v8 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&src, text, textLength, v7, v8);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  idMaterial::CommonInit(this);
  memset(&parsingData, 0, sizeof(parsingData));
  this->pd = &parsingData;
  if ( !idMaterial::ParseMaterial(this, &src) )
    goto LABEL_94;
  if ( cvarSystem->GetCVarInteger(cvarSystem, "fs_copyFiles") )
    idMaterial::GetEditorImage(this);
  numStages = this->numStages;
  v10 = 0;
  this->numAmbientStages = 0;
  if ( numStages > 0 )
  {
    p_lighting = &this->pd->parseStages[0].lighting;
    do
    {
      if ( *p_lighting == SL_AMBIENT )
        ++this->numAmbientStages;
      ++v10;
      p_lighting += 33;
    }
    while ( v10 < this->numStages );
  }
  if ( LODWORD(this->sort) == -1065353216 )
  {
    this->hasSubview = 1;
  }
  else
  {
    v12 = 0;
    this->hasSubview = 0;
    if ( numStages > 0 )
    {
      p_dynamic = &this->pd->parseStages[0].texture.dynamic;
      do
      {
        if ( *p_dynamic )
          this->hasSubview = 1;
        ++v12;
        p_dynamic += 33;
      }
      while ( v12 < this->numStages );
    }
  }
  if ( this->coverage )
    goto LABEL_27;
  if ( !numStages )
    goto LABEL_26;
  if ( numStages != this->numAmbientStages )
  {
    this->coverage = MC_OPAQUE;
    goto LABEL_27;
  }
  if ( (this->pd->parseStages[0].drawStateBits & 0xF0) != 0
    || (v14 = this->pd->parseStages[0].drawStateBits & 0xF, v14 == 3)
    || v14 == 4
    || v14 == 7
    || v14 == 8 )
  {
LABEL_26:
    this->coverage = MC_TRANSLUCENT;
  }
  else
  {
    this->coverage = MC_OPAQUE;
  }
LABEL_27:
  coverage = this->coverage;
  if ( coverage == MC_TRANSLUCENT )
    this->materialFlags |= 4u;
  else
    this->contentFlags |= 2u;
  if ( coverage == MC_TRANSLUCENT )
    this->editorAlpha = 0.5;
  else
    this->editorAlpha = 1.0;
  if ( LODWORD(this->sort) == -1082130432 )
  {
    if ( (this->materialFlags & 2) != 0 )
    {
      this->sort = 2.0;
    }
    else if ( coverage == MC_TRANSLUCENT )
    {
      this->sort = 4.0;
    }
    else
    {
      this->sort = 0.0;
    }
  }
  if ( (this->materialFlags & 0x100) == 0 )
  {
    v16 = 0;
    i = 0;
    if ( numStages > 0 )
    {
      while ( 1 )
      {
        v17 = &this->pd->parseStages[v16];
        pStage = v17;
        if ( v17->texture.image == globalImages->GetCurrentRenderImage(globalImages) )
          break;
        newStage = v17->newStage;
        if ( newStage )
        {
          j = 0;
          if ( newStage->numFragmentProgramImages > 0 )
          {
            v19 = 408;
            while ( 1 )
            {
              v20 = pStage->newStage;
              if ( *(idImage **)((char *)&v20->vertexProgram + v19) == globalImages->GetCurrentRenderImage(globalImages) )
                break;
              v19 += 4;
              if ( ++j >= v20->numFragmentProgramImages )
                goto LABEL_49;
            }
            v21 = this->numStages;
            this->sort = 100.0;
            this->coverage = MC_TRANSLUCENT;
            i = v21;
LABEL_49:
            v16 = i;
            v17 = pStage;
          }
        }
        if ( v17->newShaderStage )
        {
          v16 = 0;
          v22 = 5508;
          while ( *(rvNewShaderStage_vtbl **)((char *)&pStage->newShaderStage->__vftable + v22) != (rvNewShaderStage_vtbl *)globalImages->GetCurrentRenderImage(globalImages) )
          {
            v22 += 4;
            ++v16;
            if ( v22 >= 5540 )
              goto LABEL_58;
          }
          if ( LODWORD(this->sort) != 1065353216 )
          {
            this->sort = 100.0;
            this->coverage = MC_TRANSLUCENT;
          }
          v16 = this->numStages;
        }
LABEL_58:
        i = ++v16;
        if ( v16 >= this->numStages )
          goto LABEL_62;
      }
      if ( LODWORD(this->sort) != 1065353216 )
      {
        this->sort = 100.0;
        this->coverage = MC_TRANSLUCENT;
      }
    }
  }
LABEL_62:
  v23 = 0;
  if ( this->numStages > 0 )
  {
    v24 = 0;
    do
    {
      if ( LODWORD(this->sort) != 1120403456 )
      {
        if ( this->coverage == MC_TRANSLUCENT || this->pd->parseStages[v24].ignoreAlphaTest )
          this->pd->parseStages[v24].drawStateBits |= 0x100u;
        else
          this->pd->parseStages[v24].drawStateBits |= 0x20100u;
      }
      ++v23;
      ++v24;
    }
    while ( v23 < this->numStages );
  }
  if ( this->pd->forceOverlays )
  {
    this->allowOverlays = 1;
  }
  else
  {
    if ( this->numStages <= 0 && !this->entityGui && !this->gui )
      this->allowOverlays = 0;
    if ( this->coverage != MC_OPAQUE )
      this->allowOverlays = 0;
    if ( (this->surfaceFlags & 0x100) != 0 )
      this->allowOverlays = 0;
  }
  if ( (this->portalDistanceNear < 262144.0 || this->portalDistanceFar < 262144.0) && !this->portalImage )
    this->portalImage = globalImages->GetBlackImage(globalImages);
  v25 = this->numStages;
  if ( v25 )
  {
    v26 = (shaderStage_t *)R_StaticAlloc(132 * v25);
    pd = this->pd;
    v28 = 132 * this->numStages;
    this->stages = v26;
    SIMDProcessor->Memcpy(SIMDProcessor, v26, pd->parseStages, v28);
  }
  numOps = this->numOps;
  if ( numOps )
  {
    v30 = (expOp_t *)R_StaticAlloc(16 * numOps);
    v38 = 16 * this->numOps;
    v31 = this->pd;
    this->ops = v30;
    SIMDProcessor->Memcpy(SIMDProcessor, v30, v31->shaderOps, v38);
  }
  numRegisters = this->numRegisters;
  if ( numRegisters )
  {
    v33 = (float *)R_StaticAlloc(4 * numRegisters);
    v39 = 4 * this->numRegisters;
    v34 = this->pd;
    this->expressionRegisters = v33;
    SIMDProcessor->Memcpy(SIMDProcessor, v33, v34->shaderRegisters, v39);
  }
  if ( this->pd->registersAreConstant )
  {
    v35 = (float *)R_ClearedStaticAlloc(4 * this->numRegisters);
    memset(shaderParms, 0, sizeof(shaderParms));
    memset(&view, 0, sizeof(view));
    this->constantRegisters = v35;
    idMaterial::EvaluateRegisters(this, v35, shaderParms, &view, 0, 0);
  }
  v36 = (this->materialFlags & 1) == 0;
  this->pd = 0;
  if ( !v36 )
  {
    this->base->MakeDefault(this->base);
LABEL_94:
    LOBYTE(v48) = 0;
    idStr::FreeData(&token);
    v48 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
  LOBYTE(v48) = 0;
  idStr::FreeData(&token);
  v48 = -1;
  idLexer::~idLexer(&src);
  return 1;
}
