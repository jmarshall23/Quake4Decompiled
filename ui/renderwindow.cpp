
// FUNC: public: virtual class idWinVar * __thiscall idRenderWindow::GetWinVarByName(char const *,bool,struct drawWin_t * *)
idWinStr *__thiscall idRenderWindow::GetWinVarByName(
        idRenderWindow *this,
        const char *_name,
        bool fixup,
        drawWin_t **owner)
{
  int i; // esi
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  const char *v10; // eax
  int j; // esi
  const char *v12; // eax
  const char *v13; // eax

  if ( !idStr::Icmp(_name, "model") )
    return this->modelName;
  if ( !idStr::Icmp(_name, "anim") )
    return this->animName;
  if ( !idStr::Icmp(_name, "animClass") )
    return this->animClass;
  for ( i = 1; i < 3; ++i )
  {
    v7 = va("model%d", i);
    if ( !idStr::Icmp(_name, v7) )
      return &this->modelName[i];
    v8 = va("joint%d", i);
    if ( !idStr::Icmp(_name, v8) )
      return &this->jointName[i];
    v9 = va("anim%d", i);
    if ( !idStr::Icmp(_name, v9) )
      return &this->animName[i];
    v10 = va("animClass%d", i);
    if ( !idStr::Icmp(_name, v10) )
      return &this->animClass[i];
  }
  for ( j = 0; j < 5; ++j )
  {
    v12 = va("lightOrigin%d", j);
    if ( !idStr::Icmp(_name, v12) )
    {
      this->useLight[j] = 1;
      return (idWinStr *)&this->lightOrigins[j];
    }
    v13 = va("lightColor%d", j);
    if ( !idStr::Icmp(_name, v13) )
    {
      this->useLight[j] = 1;
      return (idWinStr *)&this->lightColors[j];
    }
  }
  if ( !idStr::Icmp(_name, "modelOrigin") )
    return (idWinStr *)&this->modelOrigin;
  if ( !idStr::Icmp(_name, "modelRotate") )
    return (idWinStr *)&this->modelRotate;
  if ( !idStr::Icmp(_name, "viewOffset") )
    return (idWinStr *)&this->viewOffset;
  if ( !idStr::Icmp(_name, "customShader") )
    return &this->customShader;
  if ( idStr::Icmp(_name, "skin") )
    return (idWinStr *)idWindow::GetWinVarByName(this, _name, fixup, owner);
  return &this->customSkin;
}

// FUNC: private: virtual bool __thiscall idRenderWindow::ParseInternalVar(char const *,class idParser *)
bool __thiscall idRenderWindow::ParseInternalVar(idRenderWindow *this, const char *_name, idParser *src)
{
  if ( idStr::Icmp(_name, "needUpdate") )
    return idWindow::ParseInternalVar(this, _name, src);
  idWindow::ParseString(this, src, &this->needUpdate);
  return 1;
}

// FUNC: public: virtual __thiscall idRenderWindow::~idRenderWindow(void)
void __thiscall idRenderWindow::~idRenderWindow(idRenderWindow *this)
{
  char *v2; // [esp-Ch] [ebp-24h]
  char *v3; // [esp-8h] [ebp-20h]
  char *name; // [esp-4h] [ebp-1Ch]

  this->__vftable = (idRenderWindow_vtbl *)&idRenderWindow::`vftable';
  renderSystem->FreeRenderWorld(renderSystem, this->world);
  idWinStr::~idWinStr(&this->customShader);
  idWinStr::~idWinStr(&this->customSkin);
  name = this->viewOffset.name;
  this->viewOffset.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(name);
  this->viewOffset.name = 0;
  v3 = this->modelRotate.name;
  this->modelRotate.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v3);
  this->modelRotate.name = 0;
  v2 = this->modelOrigin.name;
  this->modelOrigin.__vftable = (idWinVec4_vtbl *)&idWinVar::`vftable';
  Memory::Free(v2);
  this->modelOrigin.name = 0;
  `eh vector destructor iterator'(this->lightColors, 0x20u, 5, (void (__thiscall *)(void *))idWinFloat::~idWinFloat);
  `eh vector destructor iterator'(this->lightOrigins, 0x20u, 5, (void (__thiscall *)(void *))idWinFloat::~idWinFloat);
  idStr::FreeData(&this->needUpdate);
  `eh vector destructor iterator'(this->animClass, 0x30u, 3, (void (__thiscall *)(void *))idWinStr::~idWinStr);
  `eh vector destructor iterator'(this->animName, 0x30u, 3, (void (__thiscall *)(void *))idWinStr::~idWinStr);
  `eh vector destructor iterator'(this->jointName, 0x30u, 3, (void (__thiscall *)(void *))idWinStr::~idWinStr);
  `eh vector destructor iterator'(this->modelName, 0x30u, 3, (void (__thiscall *)(void *))idWinStr::~idWinStr);
  idWindow::~idWindow(this);
}

// FUNC: private: void __thiscall idRenderWindow::CommonInit(void)
void __thiscall idRenderWindow::CommonInit(idRenderWindow *this)
{
  int v2; // edi
  idWinVec4 *lightColors; // ebp
  idDict *guiDict; // ecx
  char *name; // eax
  const idKeyValue *Key; // eax
  char *data; // ebp
  const char *v8; // eax
  idWinStr_vtbl *v9; // eax
  idDict *v10; // [esp+10h] [ebp-24h]
  idVec4 other; // [esp+14h] [ebp-20h] BYREF
  idVec4 v12; // [esp+24h] [ebp-10h] BYREF

  v2 = 0;
  this->world = renderSystem->AllocRenderWorld(renderSystem);
  this->needsRender = 1;
  other.x = -128.0;
  other.y = 0.0;
  other.z = 0.0;
  other.w = 1.0;
  v12.x = 1.0;
  v12.y = 1.0;
  v12.z = 1.0;
  v12.w = 1.0;
  lightColors = this->lightColors;
  do
  {
    idWinVec4::operator=(lightColors - 5, &other);
    idWinVec4::operator=(lightColors, &v12);
    this->useLight[v2++] = 0;
    ++lightColors;
  }
  while ( v2 < 5 );
  this->useLight[0] = 1;
  this->modelOrigin.data.w = 0.0;
  this->modelOrigin.data.z = 0.0;
  this->modelOrigin.data.y = 0.0;
  this->modelOrigin.data.x = 0.0;
  guiDict = this->modelOrigin.guiDict;
  if ( guiDict )
  {
    name = this->modelOrigin.name;
    if ( name )
    {
      if ( *name != 42 )
      {
        data = this->modelOrigin.name;
        goto LABEL_10;
      }
      Key = idDict::FindKey(guiDict, name + 1);
      if ( Key )
      {
        data = Key->value->data;
LABEL_10:
        v10 = this->modelOrigin.guiDict;
        v8 = idVec4::ToString(&this->modelOrigin.data, 2);
        idDict::Set(v10, data, v8);
        goto LABEL_11;
      }
    }
    data = (char *)&entityFilter;
    goto LABEL_10;
  }
LABEL_11:
  v12.x = -128.0;
  v12.y = 0.0;
  v12.z = 0.0;
  v12.w = 1.0;
  idWinVec4::operator=(&this->viewOffset, &v12);
  this->modelAnim[0] = 0;
  this->animLength[0] = 0;
  this->animEndTime[0] = -1;
  this->modelDef[0] = -1;
  this->worldEntity[0].joints = 0;
  this->modelAnim[1] = 0;
  this->animLength[1] = 0;
  this->animEndTime[1] = -1;
  this->modelDef[1] = -1;
  this->worldEntity[1].joints = 0;
  this->modelAnim[2] = 0;
  this->animLength[2] = 0;
  this->animEndTime[2] = -1;
  this->modelDef[2] = -1;
  this->worldEntity[2].joints = 0;
  v9 = this->customShader.__vftable;
  this->updateAnimation = 1;
  v9->Set(&this->customShader, "NONE");
}

// FUNC: private: void __thiscall idRenderWindow::BuildAnimation(int)
void __userpurge idRenderWindow::BuildAnimation(
        idRenderWindow *this@<ecx>,
        idDict *a2@<edi>,
        idDict *a3@<esi>,
        int time)
{
  idRenderWindow *v4; // ebp
  int *animLength; // esi
  renderEntity_s *worldEntity; // ebx
  idDict **p_guiDict; // edi
  idDict *v8; // eax
  const char *Name; // eax
  const idKeyValue *Key; // eax
  char *data; // eax
  int v12; // eax
  idDict *v13; // eax
  idDict *v14; // ebp
  const idKeyValue *i; // esi
  const idMD5Anim *v16; // eax
  int v17; // eax
  int v21; // [esp+20h] [ebp-4h]

  v4 = this;
  if ( this->updateAnimation )
  {
    animLength = this->animLength;
    worldEntity = this->worldEntity;
    p_guiDict = &this->animName[0].guiDict;
    v21 = 3;
    do
    {
      if ( worldEntity->hModel )
      {
        if ( *p_guiDict )
        {
          v8 = p_guiDict[1];
          if ( v8 )
          {
            if ( LOBYTE(v8->args.num) )
            {
              Name = idWinVar::GetName((idWinVar *)(p_guiDict - 1));
              Key = idDict::FindKey(*p_guiDict, Name);
              if ( Key )
                data = Key->value->data;
              else
                data = (char *)&entityFilter;
              idStr::operator=((idStr *)(p_guiDict + 3), data);
            }
          }
        }
        if ( p_guiDict[3] && idWinStr::Length((idWinStr *)(p_guiDict + 35)) )
        {
          v12 = ((int (__thiscall *)(idRenderModel *, idDict *, idDict *))worldEntity->hModel->NumJoints)(
                  worldEntity->hModel,
                  a2,
                  a3);
          worldEntity->numJoints = v12;
          worldEntity->joints = (idJointMat *)Mem_Alloc16(48 * v12, 0x16u);
          v13 = (idDict *)gameEdit->FindEntityDefDict(gameEdit, p_guiDict[40], 1);
          v14 = v13;
          if ( v13 )
          {
            for ( i = idDict::MatchPrefix(v13, "hidesurface", 0); i; i = idDict::MatchPrefix(v14, "hidesurface", i) )
            {
              if ( i->value->data )
                worldEntity->suppressSurfaceMask |= worldEntity->hModel->GetSurfaceMask(
                                                      worldEntity->hModel,
                                                      i->value->data);
            }
            animLength = (int *)v21;
          }
          a3 = p_guiDict[4];
          a2 = p_guiDict[40];
          v16 = (const idMD5Anim *)((int (__thiscall *)(idGameEdit *))gameEdit->ANIM_GetAnimFromEntityDef)(gameEdit);
          *(animLength - 271) = (int)v16;
          if ( v16 )
          {
            v17 = gameEdit->ANIM_GetLength(gameEdit, v16);
            *animLength = v17;
            animLength[3] = time + v17;
          }
          v4 = this;
        }
      }
      ++animLength;
      ++worldEntity;
      p_guiDict += 12;
      --v21;
    }
    while ( v21 );
    v4->updateAnimation = 0;
  }
}

// FUNC: private: void __thiscall idRenderWindow::Render(int)
void __thiscall idRenderWindow::Render(idRenderWindow *this, int time)
{
  int v3; // ebp
  float *p_z; // esi
  float *v5; // edi
  int v6; // ecx
  int v7; // eax
  int v8; // edi
  const idMD5Anim *v9; // eax
  float y; // edx
  idWinVec4_vtbl *v11; // eax
  int *v12; // esi
  float *v13; // ebp
  const idRenderModel *v14; // eax
  jointHandle_t v15; // eax
  idJointMat *joints; // ecx
  int v17; // eax
  double v18; // st7
  idJointMat *v19; // eax
  double v20; // st6
  double v21; // st5
  float v22; // ecx
  double v23; // st4
  double v24; // st3
  double v25; // st2
  double v26; // st1
  float v27; // ecx
  float v28; // edx
  float *p_y; // eax
  int v30; // edx
  double v31; // st7
  double v32; // st7
  double v33; // st6
  idMat3 *p_result; // ecx
  double v35; // st7
  double v36; // st6
  int v37; // eax
  int v38; // ecx
  int v39; // edx
  int v40; // eax
  int v41; // ecx
  int v42; // edx
  int v43; // eax
  int v44; // ecx
  bool v45; // zf
  int *lightDefs; // [esp+54h] [ebp-A4h]
  char **p_data; // [esp+54h] [ebp-A4h]
  idAngles v48; // [esp+58h] [ebp-A0h] BYREF
  float z; // [esp+64h] [ebp-94h]
  float v50; // [esp+68h] [ebp-90h]
  const idMD5Anim *v51; // [esp+6Ch] [ebp-8Ch]
  float v52; // [esp+70h] [ebp-88h]
  float v53; // [esp+78h] [ebp-80h]
  float v54; // [esp+7Ch] [ebp-7Ch]
  idMat3 axis; // [esp+80h] [ebp-78h] BYREF
  int v56[9]; // [esp+A4h] [ebp-54h] BYREF
  float v57; // [esp+D0h] [ebp-28h]
  idMat3 result; // [esp+D4h] [ebp-24h] BYREF

  v3 = 0;
  lightDefs = this->lightDefs;
  p_z = &this->rLights[0].origin.z;
  v5 = &this->lightOrigins[0].data.z;
  do
  {
    if ( this->useLight[v3] )
    {
      *(p_z - 2) = *(v5 - 2);
      *(p_z - 1) = *(v5 - 1);
      *p_z = *v5;
      p_z[30] = ((double (__thiscall *)(float *))*(_DWORD *)(*((_DWORD *)v5 + 34) + 48))(v5 + 34);
      v6 = *((_DWORD *)v5 + 40);
      p_z[31] = v5[39];
      v7 = *lightDefs;
      *((_DWORD *)p_z + 32) = v6;
      this->world->UpdateLightDef(this->world, v7, (const renderLight_s *)(p_z - 11));
    }
    ++lightDefs;
    ++v3;
    v5 += 8;
    p_z += 54;
  }
  while ( v3 < 5 );
  if ( this->worldEntity[0].hModel )
  {
    v8 = time;
    idRenderWindow::BuildAnimation(this, time);
    v9 = this->modelAnim[0];
    if ( v9 )
    {
      if ( time > this->animEndTime[0] )
        this->animEndTime[0] = time + this->animLength[0];
      gameEdit->ANIM_CreateAnimFrame(
        gameEdit,
        this->worldEntity[0].hModel,
        v9,
        this->worldEntity[0].numJoints,
        this->worldEntity[0].joints,
        time + this->animLength[0] - this->animEndTime[0],
        &vec3_origin,
        0);
    }
    y = this->modelRotate.data.y;
    v11 = this->modelRotate.__vftable;
    z = this->modelRotate.data.z;
    v50 = y;
    v48.pitch = v11->x(&this->modelRotate);
    v48.yaw = v50;
    v48.roll = z;
    this->worldEntity[0].axis = *idAngles::ToMat3(&v48, &result);
    this->world->UpdateEntityDef(this->world, this->modelDef[0], this->worldEntity);
    v12 = &this->animEndTime[1];
    p_data = &this->jointName[1].data.data;
    LODWORD(z) = &this->animEndTime[1];
    v13 = &this->worldEntity[1].axis.mat[1].z;
    LODWORD(v50) = 2;
    do
    {
      v14 = (const idRenderModel *)*((_DWORD *)v13 - 24);
      if ( v14 )
      {
        v51 = (const idMD5Anim *)*(v12 - 274);
        if ( v51 )
        {
          if ( v8 > *v12 )
            *v12 = v8 + *(v12 - 3);
          gameEdit->ANIM_CreateAnimFrame(
            gameEdit,
            v14,
            v51,
            *((_DWORD *)v13 + 25),
            (idJointMat *)*((_DWORD *)v13 + 26),
            time + *(v12 - 3) - *v12,
            &vec3_origin,
            0);
          v8 = time;
        }
        v15 = this->worldEntity[0].hModel->GetJointHandle(this->worldEntity[0].hModel, *p_data);
        if ( v15 != INVALID_JOINT )
        {
          joints = this->worldEntity[0].joints;
          v17 = v15;
          v18 = joints[v17].mat[10];
          v19 = &joints[v17];
          v20 = v19->mat[6];
          v21 = v19->mat[2];
          v22 = v19->mat[7];
          v23 = v19->mat[9];
          v48.pitch = v19->mat[3];
          v24 = v19->mat[5];
          v25 = v19->mat[1];
          v48.roll = v19->mat[11];
          v26 = v19->mat[8];
          v48.yaw = v22;
          axis.mat[0].z = v26;
          v27 = v19->mat[4];
          v28 = v19->mat[0];
          axis.mat[1].x = v25;
          v52 = v27;
          axis.mat[1].y = v24;
          axis.mat[0].x = v28;
          axis.mat[0].y = v27;
          axis.mat[1].z = v23;
          p_y = &axis.mat[0].y;
          v30 = 3;
          axis.mat[2].x = v21;
          axis.mat[2].y = v20;
          axis.mat[2].z = v18;
          v31 = v48.roll * this->worldEntity[0].axis.mat[2].x
              + v48.yaw * this->worldEntity[0].axis.mat[1].x
              + v48.pitch * this->worldEntity[0].axis.mat[0].x;
          v53 = v48.roll * this->worldEntity[0].axis.mat[2].y
              + v48.yaw * this->worldEntity[0].axis.mat[1].y
              + v48.pitch * this->worldEntity[0].axis.mat[0].y;
          v54 = v48.roll * this->worldEntity[0].axis.mat[2].z
              + v48.yaw * this->worldEntity[0].axis.mat[1].z
              + v48.pitch * this->worldEntity[0].axis.mat[0].z;
          v32 = v31 + this->worldEntity[0].origin.x;
          v33 = v53 + this->worldEntity[0].origin.y;
          v57 = v54 + this->worldEntity[0].origin.z;
          *(v13 - 6) = v57;
          *(v13 - 8) = v32;
          p_result = &result;
          *(v13 - 7) = v33;
          do
          {
            v35 = this->worldEntity[0].axis.mat[2].x * p_y[1];
            p_result = (idMat3 *)((char *)p_result + 12);
            v36 = *p_y * this->worldEntity[0].axis.mat[1].x;
            p_y += 3;
            --v30;
            p_result[-1].mat[2].x = v35 + v36 + this->worldEntity[0].axis.mat[0].x * *(p_y - 4);
            p_result[-1].mat[2].y = this->worldEntity[0].axis.mat[0].y * *(p_y - 4)
                                  + *(p_y - 3) * this->worldEntity[0].axis.mat[1].y
                                  + this->worldEntity[0].axis.mat[2].y * *(p_y - 2);
            p_result[-1].mat[2].z = this->worldEntity[0].axis.mat[2].z * *(p_y - 2)
                                  + this->worldEntity[0].axis.mat[0].z * *(p_y - 4)
                                  + *(p_y - 3) * this->worldEntity[0].axis.mat[1].z;
          }
          while ( v30 );
          qmemcpy(v56, &result, sizeof(v56));
          v37 = v56[1];
          v38 = v56[2];
          *(float *)&v12 = z;
          v8 = time;
          *(v13 - 5) = *(float *)v56;
          v39 = v56[3];
          *((_DWORD *)v13 - 4) = v37;
          v40 = v56[4];
          *((_DWORD *)v13 - 3) = v38;
          v41 = v56[5];
          *((_DWORD *)v13 - 2) = v39;
          v42 = v56[6];
          *((_DWORD *)v13 - 1) = v40;
          v43 = v56[7];
          *(_DWORD *)v13 = v41;
          v44 = v56[8];
          *((_DWORD *)v13 + 1) = v42;
          *((_DWORD *)v13 + 2) = v43;
          *((_DWORD *)v13 + 3) = v44;
        }
        this->world->UpdateEntityDef(this->world, *(v12 - 265), (const renderEntity_s *)(v13 - 24));
      }
      p_data += 12;
      ++v12;
      v13 += 56;
      v45 = LODWORD(v50)-- == 1;
      z = *(float *)&v12;
    }
    while ( !v45 );
    this->world->PushMarkedDefs(this->world);
  }
}

// FUNC: public: __thiscall idRenderWindow::idRenderWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idRenderWindow::idRenderWindow(idRenderWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idWindow::idWindow(this, d, g);
  this->__vftable = (idRenderWindow_vtbl *)&idRenderWindow::`vftable';
  `eh vector constructor iterator'(
    this->modelName,
    0x30u,
    3,
    (void (__thiscall *)(void *))idWinStr::idWinStr,
    (void (__thiscall *)(void *))idWinStr::~idWinStr);
  `eh vector constructor iterator'(
    this->jointName,
    0x30u,
    3,
    (void (__thiscall *)(void *))idWinStr::idWinStr,
    (void (__thiscall *)(void *))idWinStr::~idWinStr);
  `eh vector constructor iterator'(
    this->animName,
    0x30u,
    3,
    (void (__thiscall *)(void *))idWinStr::idWinStr,
    (void (__thiscall *)(void *))idWinStr::~idWinStr);
  `eh vector constructor iterator'(
    this->animClass,
    0x30u,
    3,
    (void (__thiscall *)(void *))idWinStr::idWinStr,
    (void (__thiscall *)(void *))idWinStr::~idWinStr);
  this->needUpdate.len = 0;
  this->needUpdate.alloced = 20;
  this->needUpdate.data = this->needUpdate.baseBuffer;
  this->needUpdate.baseBuffer[0] = 0;
  `eh vector constructor iterator'(
    this->lightOrigins,
    0x20u,
    5,
    (void (__thiscall *)(void *))idWinVec4::idWinVec4,
    (void (__thiscall *)(void *))idWinFloat::~idWinFloat);
  `eh vector constructor iterator'(
    this->lightColors,
    0x20u,
    5,
    (void (__thiscall *)(void *))idWinVec4::idWinVec4,
    (void (__thiscall *)(void *))idWinFloat::~idWinFloat);
  this->modelOrigin.guiDict = 0;
  this->modelOrigin.name = 0;
  this->modelOrigin.eval = 1;
  this->modelOrigin.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->modelRotate.guiDict = 0;
  this->modelRotate.name = 0;
  this->modelRotate.eval = 1;
  this->modelRotate.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->viewOffset.guiDict = 0;
  this->viewOffset.name = 0;
  this->viewOffset.eval = 1;
  this->viewOffset.__vftable = (idWinVec4_vtbl *)&idWinVec4::`vftable';
  this->customSkin.guiDict = 0;
  this->customSkin.name = 0;
  this->customSkin.eval = 1;
  this->customSkin.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->customSkin.data.len = 0;
  this->customSkin.data.alloced = 20;
  this->customSkin.data.data = this->customSkin.data.baseBuffer;
  this->customSkin.data.baseBuffer[0] = 0;
  this->customShader.guiDict = 0;
  this->customShader.name = 0;
  this->customShader.eval = 1;
  this->customShader.__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
  this->customShader.data.len = 0;
  this->customShader.data.alloced = 20;
  this->customShader.data.data = this->customShader.data.baseBuffer;
  this->customShader.data.baseBuffer[0] = 0;
  this->dc = d;
  this->gui = g;
  idRenderWindow::CommonInit(this);
}

// FUNC: private: void __thiscall idRenderWindow::PreRender(void)
void __usercall idRenderWindow::PreRender(idRenderWindow *this@<ecx>, int a2@<ebp>, int a3@<edi>)
{
  int v4; // ebx
  renderLight_s *rLights; // ebp
  idVec4 *p_data; // edi
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  void **p_joints; // edi
  int v11; // ebx
  const char *v12; // eax
  float y; // edx
  float z; // eax
  const char *v15; // eax
  idDeclManager_vtbl *v16; // ebp
  int v17; // eax
  int v18; // eax
  idRenderWorld *world; // ecx
  char **v20; // ebp
  float *p_z; // edi
  float v22; // eax
  float v23; // ecx
  const char *v24; // eax
  idWinStr_vtbl *v25; // edx
  int v26; // eax
  bool v27; // zf
  const char *p_granularity; // [esp+28h] [ebp-88h]
  int *v29; // [esp+38h] [ebp-78h]
  char **v30; // [esp+3Ch] [ebp-74h]
  int *lightDefs; // [esp+40h] [ebp-70h]
  int v32; // [esp+40h] [ebp-70h]
  idVec3 v; // [esp+48h] [ebp-68h] BYREF
  idMat3 result; // [esp+54h] [ebp-5Ch] BYREF
  idDict spawnArgs; // [esp+78h] [ebp-38h] BYREF
  int v36; // [esp+ACh] [ebp-4h]

  if ( this->needsRender )
  {
    v4 = 0;
    ((void (__thiscall *)(idRenderWorld *, _DWORD, int, int))this->world->InitFromMap)(this->world, 0, a3, a2);
    spawnArgs.argHash.hash = 0;
    spawnArgs.args.granularity = 0;
    spawnArgs.args.list = 0;
    idHashIndex::Init((idHashIndex *)&spawnArgs.argHash.indexSize, 1024, 1024);
    spawnArgs.argHash.hashSize = 16;
    spawnArgs.argHash.lookupMask = 16;
    idHashIndex::Free((idHashIndex *)&spawnArgs.argHash.indexSize);
    spawnArgs.argHash.indexSize = 128;
    spawnArgs.argHash.granularity = 16;
    lightDefs = this->lightDefs;
    rLights = this->rLights;
    p_data = &this->lightColors[0].data;
    do
    {
      if ( this->useLight[v4] )
      {
        idDict::Set((idDict *)&spawnArgs.args.granularity, "classname", "light");
        v7 = va("light_%d", v4);
        idDict::Set((idDict *)&spawnArgs.args.granularity, "name", v7);
        v8 = idVec3::ToString((idVec3 *)&p_data[-10], 2);
        idDict::Set((idDict *)&spawnArgs.args.granularity, "origin", v8);
        v9 = idVec3::ToString((idVec3 *)p_data, 2);
        idDict::Set((idDict *)&spawnArgs.args.granularity, "_color", v9);
        gameEdit->ParseSpawnArgsToRenderLight(gameEdit, (const idDict *)&spawnArgs.args.granularity, rLights);
        *lightDefs = this->world->AddLightDef(this->world, rLights);
      }
      ++lightDefs;
      ++v4;
      p_data += 2;
      ++rLights;
    }
    while ( v4 < 5 );
    if ( !*this->modelName[0].data.data )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "Window '%s' in gui '%s': no model set",
        this->name.data,
        this->gui->source.data);
    p_joints = (void **)&this->worldEntity[0].joints;
    v11 = 3;
    do
    {
      if ( *p_joints )
        Mem_Free16(*p_joints);
      p_joints += 56;
      --v11;
    }
    while ( v11 );
    memset(this->worldEntity, 0, sizeof(this->worldEntity));
    idDict::Clear((idDict *)&spawnArgs.args.granularity);
    idDict::Set((idDict *)&spawnArgs.args.granularity, "classname", "func_static");
    idDict::Set((idDict *)&spawnArgs.args.granularity, "model", this->modelName[0].data.data);
    idDict::Set((idDict *)&spawnArgs.args.granularity, "skin", this->customSkin.data.data);
    v12 = this->modelOrigin.c_str(&this->modelOrigin);
    idDict::Set((idDict *)&spawnArgs.args.granularity, "origin", v12);
    p_granularity = (const char *)&spawnArgs.args.granularity;
    ((void (__thiscall *)(idGameEdit *))gameEdit->ParseSpawnArgsToRenderEntity)(gameEdit);
    if ( this->worldEntity[0].hModel )
    {
      y = this->modelRotate.data.y;
      z = this->modelRotate.data.z;
      v.x = this->modelRotate.data.x;
      v.y = y;
      v.z = z;
      this->worldEntity[0].axis = *idVec3::ToMat3(&v, &result);
      this->worldEntity[0].shaderParms[0] = 1.0;
      this->worldEntity[0].shaderParms[1] = 1.0;
      this->worldEntity[0].shaderParms[2] = 1.0;
      this->worldEntity[0].shaderParms[3] = 1.0;
      v15 = (const char *)((int (__thiscall *)(idWinStr *, const char *))this->customShader.c_str)(
                            &this->customShader,
                            "NONE");
      if ( idStr::Cmp(v15, (const char *)&spawnArgs.args.granularity) )
      {
        v16 = declManager->__vftable;
        v17 = ((int (__thiscall *)(idWinStr *, int))this->customShader.c_str)(&this->customShader, 1);
        this->worldEntity[0].customShader = (const idMaterial *)((int (__thiscall *)(idDeclManager *, int))v16->FindMaterial)(
                                                                  declManager,
                                                                  v17);
      }
      p_granularity = (const char *)this->worldEntity;
      v18 = ((int (__thiscall *)(idRenderWorld *))this->world->AddEntityDef)(this->world);
      world = this->world;
      this->modelDef[0] = v18;
      world->PushMarkedDefs(world);
    }
    v20 = &this->modelName[1].data.data;
    v29 = &this->modelDef[1];
    v30 = &this->modelName[1].data.data;
    p_z = &this->worldEntity[1].axis.mat[1].z;
    v32 = 2;
    do
    {
      if ( **v20 )
      {
        idDict::Clear(&spawnArgs);
        idDict::Set(&spawnArgs, "classname", "func_static");
        idDict::Set(&spawnArgs, "model", *v20);
        idDict::Set(&spawnArgs, "origin", "0 0 0");
        gameEdit->ParseSpawnArgsToRenderEntity(gameEdit, &spawnArgs, (renderEntity_s *)(p_z - 24));
        if ( *((_DWORD *)p_z - 24) )
        {
          v22 = this->modelRotate.data.y;
          v23 = this->modelRotate.data.z;
          v.x = this->modelRotate.data.x;
          v.z = v23;
          v.y = v22;
          *(idMat3 *)(p_z - 5) = *idVec3::ToMat3(&v, &result);
          p_z[9] = 1.0;
          p_z[10] = 1.0;
          p_z[11] = 1.0;
          p_z[12] = 1.0;
          v24 = (const char *)((int (__thiscall *)(idWinStr *, const char *))this->customShader.c_str)(
                                &this->customShader,
                                "NONE");
          if ( idStr::Cmp(v24, p_granularity) )
          {
            v25 = this->customShader.__vftable;
            LODWORD(v.x) = (idDeclManager)declManager->__vftable;
            v26 = ((int (__thiscall *)(idWinStr *, int))v25->c_str)(&this->customShader, 1);
            *((_DWORD *)p_z + 4) = (*(int (__thiscall **)(idDeclManager *, int))(LODWORD(v.y) + 136))(declManager, v26);
          }
          p_granularity = (const char *)(p_z - 24);
          v20 = v30;
          *v29 = ((int (__thiscall *)(idRenderWorld *))this->world->AddEntityDef)(this->world);
        }
      }
      ++v29;
      v20 += 12;
      p_z += 56;
      v27 = v32-- == 1;
      v30 = v20;
    }
    while ( !v27 );
    this->world->PushMarkedDefs(this->world);
    this->needsRender = 0;
    v36 = 4;
    idDict::Clear(&spawnArgs);
    LOBYTE(v36) = 3;
    idHashIndex::Free(&spawnArgs.argHash);
    v36 = -1;
    if ( spawnArgs.args.list )
      Memory::Free(spawnArgs.args.list);
  }
}

// FUNC: public: virtual void __thiscall idRenderWindow::Draw(int,float,float)
void __thiscall idRenderWindow::Draw(idRenderWindow *this, int time, float x, float y)
{
  idUserInterfaceLocal *gui; // ecx
  char *data; // edx
  double v7; // st7
  long double v8; // st7
  idRenderWorld *world; // ecx
  long double v10; // st7

  if ( this->gui->GetStateBool(this->gui, this->needUpdate.data, "0") )
  {
    gui = this->gui;
    data = this->needUpdate.data;
    this->needsRender = 1;
    this->updateAnimation = 1;
    gui->SetStateBool(gui, data, 0);
  }
  idRenderWindow::PreRender(this);
  idRenderWindow::Render(this, time);
  memset(&this->refdef, 0, sizeof(this->refdef));
  this->refdef.vieworg.x = this->viewOffset.data.x;
  this->refdef.vieworg.y = this->viewOffset.data.y;
  this->refdef.vieworg.z = this->viewOffset.data.z;
  this->refdef.viewaxis = mat3_identity;
  v7 = this->drawRect.x;
  this->refdef.shaderParms[0] = 1.0;
  this->refdef.shaderParms[1] = 1.0;
  this->refdef.shaderParms[2] = 1.0;
  this->refdef.shaderParms[3] = 1.0;
  this->refdef.fov_x = 90.0;
  this->refdef.x = (int)v7;
  this->refdef.y = (int)this->drawRect.y;
  this->refdef.width = (int)this->drawRect.w;
  this->refdef.height = (int)this->drawRect.h;
  v8 = atan2(this->drawRect.h / this->drawRect.w, 1.0);
  world = this->world;
  v10 = v8 * idMath::M_RAD2DEG + v8 * idMath::M_RAD2DEG;
  this->refdef.time = time;
  this->refdef.fov_y = v10;
  world->RenderScene(world, &this->refdef, 0);
}
