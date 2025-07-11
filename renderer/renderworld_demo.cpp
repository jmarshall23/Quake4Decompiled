
// FUNC: public: void __thiscall idRenderWorldLocal::ReadRenderView(struct renderView_s *)
void __thiscall idRenderWorldLocal::ReadRenderView(idRenderWorldLocal *this, renderView_s *renderView)
{
  float *shaderParms; // edi
  int v3; // ebx
  idDeclManager_vtbl *v4; // edi
  char *HashString; // eax

  session->readDemo->ReadInt(session->readDemo, (int *)renderView);
  session->readDemo->ReadInt(session->readDemo, &renderView->x);
  session->readDemo->ReadInt(session->readDemo, &renderView->y);
  session->readDemo->ReadInt(session->readDemo, &renderView->width);
  session->readDemo->ReadInt(session->readDemo, &renderView->height);
  session->readDemo->ReadFloat(session->readDemo, &renderView->fov_x);
  session->readDemo->ReadFloat(session->readDemo, &renderView->fov_y);
  session->readDemo->ReadVec3(session->readDemo, &renderView->vieworg);
  session->readDemo->ReadMat3(session->readDemo, &renderView->viewaxis);
  session->readDemo->ReadBool(session->readDemo, &renderView->cramZNear);
  session->readDemo->ReadBool(session->readDemo, &renderView->forceUpdate);
  session->readDemo->ReadInt(session->readDemo, &renderView->time);
  shaderParms = renderView->shaderParms;
  v3 = 12;
  do
  {
    session->readDemo->ReadFloat(session->readDemo, shaderParms++);
    --v3;
  }
  while ( v3 );
  session->readDemo->ReadInt(session->readDemo, (int *)&renderView->globalMaterial);
  if ( renderView->globalMaterial )
  {
    v4 = declManager->__vftable;
    HashString = idDemoFile::ReadHashString(session->readDemo);
    renderView->globalMaterial = v4->FindMaterial(declManager, HashString, 1);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteLoadMap(void)
void __usercall idRenderWorldLocal::WriteLoadMap(idRenderWorldLocal *this@<ecx>, int a2@<esi>)
{
  int v3; // eax
  int i; // esi
  demoHeader_t header; // [esp+20h] [ebp-10Ch] BYREF

  if ( this == session->rw )
  {
    ((void (__thiscall *)(idDemoFile *, int, int))session->writeDemo->WriteChar)(session->writeDemo, 1, a2);
    session->writeDemo->WriteChar(session->writeDemo, 13);
    strncpy(&header.mapname[4], this->mapName.data, 0xFFu);
    session->writeDemo->WriteInt(session->writeDemo, 1834);
    session->writeDemo->WriteInt(session->writeDemo, 224);
    v3 = session->writeDemo->WriteInt(session->writeDemo, 216);
    for ( i = 0; i < 256; ++i )
    {
      LOBYTE(v3) = header.mapname[i + 4];
      v3 = session->writeDemo->WriteChar(session->writeDemo, v3);
    }
    *(float *)&header.version = 1000.0 * tr.frameShaderTime;
    session->writeDemo->WriteInt(session->writeDemo, (int)*(float *)&header.version);
    if ( r_showDemo.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_LOADMAP: %s\n",
        this->mapName.data);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteRenderView(char,struct renderView_s const *)
void __userpurge idRenderWorldLocal::WriteRenderView(
        idRenderWorldLocal *this@<ecx>,
        int a2@<edi>,
        char command,
        const renderView_s *renderView,
        int a5)
{
  int v5; // eax
  int v6; // eax
  _DWORD *v7; // edi
  int v8; // ebx
  int v9; // eax
  const char *v10; // eax

  if ( this == session->rw )
  {
    ((void (__thiscall *)(idDemoFile *, int, int))session->writeDemo->WriteChar)(session->writeDemo, 1, a2);
    session->writeDemo->WriteChar(session->writeDemo, (const char)renderView);
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)a5);
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 4));
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 8));
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 12));
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 16));
    ((void (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(
      session->writeDemo,
      *(_DWORD *)(a5 + 20));
    ((void (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(
      session->writeDemo,
      *(_DWORD *)(a5 + 24));
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a5 + 28));
    v5 = session->writeDemo->WriteMat3(session->writeDemo, (const idMat3 *)(a5 + 40));
    LOBYTE(v5) = *(_BYTE *)(a5 + 76);
    v6 = session->writeDemo->WriteBool(session->writeDemo, v5);
    LOBYTE(v6) = *(_BYTE *)(a5 + 77);
    session->writeDemo->WriteBool(session->writeDemo, v6);
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 80));
    v7 = (_DWORD *)(a5 + 84);
    v8 = 12;
    do
    {
      ((void (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(session->writeDemo, *v7++);
      --v8;
    }
    while ( v8 );
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 132));
    v9 = *(_DWORD *)(a5 + 132);
    if ( v9 )
    {
      v10 = (const char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v9 + 4) + 4))(*(_DWORD *)(v9 + 4));
      idDemoFile::WriteHashString(session->writeDemo, v10);
    }
    if ( r_showDemo.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_RENDERVIEW: %i\n",
        *(_DWORD *)(a5 + 80));
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteFreeEntityDef(int)
void __thiscall idRenderWorldLocal::WriteFreeEntityDef(idRenderWorldLocal *this, int handle)
{
  if ( this == session->rw )
  {
    session->writeDemo->WriteChar(session->writeDemo, 1);
    session->writeDemo->WriteChar(session->writeDemo, 4);
    session->writeDemo->WriteInt(session->writeDemo, handle);
    if ( (r_showDemo.internalVar->integerValue & 8) != 0 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_DELETE_ENTITYDEF: %i\n",
        handle);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteUpdateEntityDef(int)
void __thiscall idRenderWorldLocal::WriteUpdateEntityDef(idRenderWorldLocal *this, int handle)
{
  if ( this == session->rw )
  {
    session->writeDemo->WriteChar(session->writeDemo, 1);
    session->writeDemo->WriteChar(session->writeDemo, 3);
    session->writeDemo->WriteInt(session->writeDemo, handle);
    if ( (r_showDemo.internalVar->integerValue & 8) != 0 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_UPDATE_ENTITYDEF: %i\n",
        handle);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteFreeLightDef(int)
void __thiscall idRenderWorldLocal::WriteFreeLightDef(idRenderWorldLocal *this, int handle)
{
  if ( this == session->rw )
  {
    session->writeDemo->WriteChar(session->writeDemo, 1);
    session->writeDemo->WriteChar(session->writeDemo, 7);
    session->writeDemo->WriteInt(session->writeDemo, handle);
    if ( (r_showDemo.internalVar->integerValue & 2) != 0 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_DELETE_LIGHTDEF: %i\n",
        handle);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteUpdateLightDef(int)
void __thiscall idRenderWorldLocal::WriteUpdateLightDef(idRenderWorldLocal *this, int handle)
{
  if ( this == session->rw )
  {
    session->writeDemo->WriteChar(session->writeDemo, 1);
    session->writeDemo->WriteChar(session->writeDemo, 6);
    session->writeDemo->WriteInt(session->writeDemo, handle);
    if ( (r_showDemo.internalVar->integerValue & 2) != 0 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_UPDATE_LIGHTDEF: %i\n",
        handle);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteFreeEffectDef(int)
void __thiscall idRenderWorldLocal::WriteFreeEffectDef(idRenderWorldLocal *this, int handle)
{
  if ( this == session->rw )
  {
    session->writeDemo->WriteChar(session->writeDemo, 1);
    session->writeDemo->WriteChar(session->writeDemo, 11);
    session->writeDemo->WriteInt(session->writeDemo, handle);
    if ( (r_showDemo.internalVar->integerValue & 4) != 0 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_DELETE_EFFECTDEF: %i\n",
        handle);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteStopEffectDef(int)
void __thiscall idRenderWorldLocal::WriteStopEffectDef(idRenderWorldLocal *this, int handle)
{
  if ( this == session->rw )
  {
    session->writeDemo->WriteChar(session->writeDemo, 1);
    session->writeDemo->WriteChar(session->writeDemo, 10);
    session->writeDemo->WriteInt(session->writeDemo, handle);
    if ( (r_showDemo.internalVar->integerValue & 4) != 0 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_STOP_EFFECTDEF: %i\n",
        handle);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteUpdateEffectDef(int)
void __thiscall idRenderWorldLocal::WriteUpdateEffectDef(idRenderWorldLocal *this, int handle)
{
  if ( this == session->rw )
  {
    session->writeDemo->WriteChar(session->writeDemo, 1);
    session->writeDemo->WriteChar(session->writeDemo, 9);
    session->writeDemo->WriteInt(session->writeDemo, handle);
    if ( (r_showDemo.internalVar->integerValue & 4) != 0 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_UPDATE_EFFECTDEF: %i\n",
        handle);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteRenderLight(int,struct renderLight_s const *)
void __userpurge idRenderWorldLocal::WriteRenderLight(
        idRenderWorldLocal *this@<ecx>,
        int a2@<edi>,
        int handle,
        const renderLight_s *light,
        int a5)
{
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD *v9; // edi
  int v10; // ebx
  const char *v11; // eax
  int v12; // esi
  const char *v13; // eax

  if ( this == session->rw )
  {
    ((void (__thiscall *)(idDemoFile *, int, int))session->writeDemo->WriteChar)(session->writeDemo, 1, a2);
    session->writeDemo->WriteChar(session->writeDemo, 8);
    session->writeDemo->WriteInt(session->writeDemo, (const int)light);
    session->writeDemo->WriteMat3(session->writeDemo, (const idMat3 *)a5);
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a5 + 36));
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 48));
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 52));
    v5 = ((int (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(
           session->writeDemo,
           *(_DWORD *)(a5 + 56));
    LOBYTE(v5) = *(_BYTE *)(a5 + 60);
    v6 = session->writeDemo->WriteBool(session->writeDemo, v5);
    LOBYTE(v6) = *(_BYTE *)(a5 + 61);
    v7 = session->writeDemo->WriteBool(session->writeDemo, v6);
    LOBYTE(v7) = *(_BYTE *)(a5 + 63);
    v8 = session->writeDemo->WriteBool(session->writeDemo, v7);
    LOBYTE(v8) = *(_BYTE *)(a5 + 64);
    session->writeDemo->WriteBool(session->writeDemo, v8);
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a5 + 68));
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a5 + 80));
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a5 + 92));
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a5 + 104));
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a5 + 116));
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a5 + 128));
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a5 + 140));
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 152));
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 156));
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 160));
    v9 = (_DWORD *)(a5 + 164);
    v10 = 12;
    do
    {
      ((void (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(session->writeDemo, *v9++);
      --v10;
    }
    while ( v10 );
    session->writeDemo->WriteInt(session->writeDemo, *(_DWORD *)(a5 + 212));
    if ( *(_DWORD *)(a5 + 152) )
    {
      v11 = (const char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(a5 + 152) + 64))(*(_DWORD *)(a5 + 152));
      idDemoFile::WriteHashString(session->writeDemo, v11);
    }
    v12 = *(_DWORD *)(a5 + 160);
    if ( v12 )
    {
      v13 = (const char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v12 + 4) + 4))(*(_DWORD *)(v12 + 4));
      idDemoFile::WriteHashString(session->writeDemo, v13);
    }
    if ( (r_showDemo.internalVar->integerValue & 2) != 0 )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_LIGHTDEF: %i\n",
        light);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteRenderEntity(int,struct renderEntity_s const *)
void __userpurge idRenderWorldLocal::WriteRenderEntity(
        idRenderWorldLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        int a4@<edi>,
        int a5@<esi>,
        int handle,
        const renderEntity_s *ent,
        int i,
        int a9,
        int a10,
        _DWORD *a11)
{
  _DWORD *v11; // edi
  int v12; // ebx
  const int *v13; // edi
  int v14; // ebx
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // ebp
  const char *v20; // eax
  int v21; // eax
  const char *v22; // eax
  int v23; // eax
  const char *v24; // eax
  int v25; // eax
  const char *v26; // eax
  int v27; // eax
  const char *v28; // eax
  int v29; // eax
  int v30; // ebx
  int j; // edi
  const char *v32; // eax
  const renderEntity_s *enta; // [esp+94h] [ebp+8h]

  if ( this == session->rw )
  {
    ((void (__thiscall *)(idDemoFile *, int, int, int, int, int))session->writeDemo->WriteChar)(
      session->writeDemo,
      1,
      a4,
      a5,
      a3,
      a2);
    session->writeDemo->WriteChar(session->writeDemo, 5);
    session->writeDemo->WriteInt(session->writeDemo, a10);
    session->writeDemo->WriteInt(session->writeDemo, *a11);
    session->writeDemo->WriteInt(session->writeDemo, a11[1]);
    session->writeDemo->WriteInt(session->writeDemo, a11[2]);
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a11 + 3));
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a11 + 6));
    session->writeDemo->WriteInt(session->writeDemo, a11[9]);
    session->writeDemo->WriteInt(session->writeDemo, a11[10]);
    session->writeDemo->WriteInt(session->writeDemo, a11[11]);
    session->writeDemo->WriteInt(session->writeDemo, a11[12]);
    session->writeDemo->WriteInt(session->writeDemo, a11[13]);
    session->writeDemo->WriteInt(session->writeDemo, a11[14]);
    session->writeDemo->WriteInt(session->writeDemo, a11[15]);
    session->writeDemo->WriteVec3(session->writeDemo, (const idVec3 *)(a11 + 16));
    session->writeDemo->WriteMat3(session->writeDemo, (const idMat3 *)(a11 + 19));
    session->writeDemo->WriteInt(session->writeDemo, a11[28]);
    session->writeDemo->WriteInt(session->writeDemo, a11[29]);
    session->writeDemo->WriteInt(session->writeDemo, a11[30]);
    session->writeDemo->WriteInt(session->writeDemo, a11[31]);
    session->writeDemo->WriteInt(session->writeDemo, a11[32]);
    v11 = a11 + 33;
    v12 = 12;
    do
    {
      ((void (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(session->writeDemo, *v11++);
      --v12;
    }
    while ( v12 );
    v13 = a11 + 45;
    v14 = 3;
    do
    {
      session->writeDemo->WriteInt(session->writeDemo, *v13++);
      --v14;
    }
    while ( v14 );
    session->writeDemo->WriteInt(session->writeDemo, a11[48]);
    session->writeDemo->WriteInt(session->writeDemo, a11[49]);
    session->writeDemo->WriteInt(session->writeDemo, a11[50]);
    v15 = ((int (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(session->writeDemo, a11[51]);
    LOBYTE(v15) = *((_BYTE *)a11 + 208);
    v16 = session->writeDemo->WriteBool(session->writeDemo, v15);
    LOBYTE(v16) = *((_BYTE *)a11 + 209);
    v17 = session->writeDemo->WriteBool(session->writeDemo, v16);
    LOBYTE(v17) = *((_BYTE *)a11 + 210);
    v18 = session->writeDemo->WriteBool(session->writeDemo, v17);
    LOBYTE(v18) = *((_BYTE *)a11 + 211);
    session->writeDemo->WriteBool(session->writeDemo, v18);
    session->writeDemo->WriteInt(session->writeDemo, a11[53]);
    ((void (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(session->writeDemo, a11[54]);
    session->writeDemo->WriteInt(session->writeDemo, a11[55]);
    v19 = 0;
    if ( *a11 )
    {
      v20 = (const char *)(*(int (__thiscall **)(_DWORD))(*(_DWORD *)*a11 + 64))(*a11);
      idDemoFile::WriteHashString(session->writeDemo, v20);
    }
    v21 = a11[28];
    if ( v21 )
    {
      v22 = (const char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v21 + 4) + 4))(*(_DWORD *)(v21 + 4));
      idDemoFile::WriteHashString(session->writeDemo, v22);
    }
    v23 = a11[29];
    if ( v23 )
    {
      v24 = (const char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v23 + 4) + 4))(*(_DWORD *)(v23 + 4));
      idDemoFile::WriteHashString(session->writeDemo, v24);
    }
    v25 = a11[30];
    if ( v25 )
    {
      v26 = (const char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v25 + 4) + 4))(*(_DWORD *)(v25 + 4));
      idDemoFile::WriteHashString(session->writeDemo, v26);
    }
    v27 = a11[31];
    if ( v27 )
    {
      v28 = (const char *)(*(int (__thiscall **)(_DWORD))(**(_DWORD **)(v27 + 4) + 4))(*(_DWORD *)(v27 + 4));
      idDemoFile::WriteHashString(session->writeDemo, v28);
    }
    v29 = a11[49];
    if ( v29 )
    {
      enta = 0;
      if ( v29 > 0 )
      {
        do
        {
          v30 = v19 + a11[50];
          for ( j = 0; j < 12; ++j )
            ((void (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(
              session->writeDemo,
              *(_DWORD *)(v30 + 4 * j));
          v19 += 48;
          enta = (const renderEntity_s *)((char *)enta + 1);
        }
        while ( (int)enta < a11[49] );
      }
    }
    if ( (r_showDemo.internalVar->integerValue & 8) != 0 )
    {
      if ( *a11 )
        v32 = (const char *)(*(int (__thiscall **)(_DWORD))(*(_DWORD *)*a11 + 64))(*a11);
      else
        v32 = aNull_1;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_ENTITYDEF: %i = %s\n",
        handle,
        v32);
    }
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteRenderEffect(int,struct renderEffect_s const *)
void __thiscall idRenderWorldLocal::WriteRenderEffect(
        idRenderWorldLocal *this,
        int handle,
        const renderEffect_s *effect)
{
  int v3; // eax
  int v4; // eax
  float *shaderParms; // edi
  int v6; // ebx
  const char *v7; // eax
  int v8; // esi
  const char *v9; // eax

  if ( this == session->rw )
  {
    session->writeDemo->WriteChar(session->writeDemo, 1);
    session->writeDemo->WriteChar(session->writeDemo, 12);
    session->writeDemo->WriteInt(session->writeDemo, handle);
    session->writeDemo->WriteInt(session->writeDemo, (const int)effect->declEffect);
    session->writeDemo->WriteInt(session->writeDemo, effect->suppressSurfaceInViewID);
    session->writeDemo->WriteInt(session->writeDemo, effect->allowSurfaceInViewID);
    session->writeDemo->WriteInt(session->writeDemo, effect->groupID);
    session->writeDemo->WriteVec3(session->writeDemo, &effect->origin);
    session->writeDemo->WriteMat3(session->writeDemo, &effect->axis);
    session->writeDemo->WriteVec3(session->writeDemo, &effect->gravity);
    session->writeDemo->WriteVec3(session->writeDemo, &effect->endOrigin);
    v3 = ((int (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(
           session->writeDemo,
           LODWORD(effect->attenuation));
    LOBYTE(v3) = effect->hasEndOrigin;
    v4 = session->writeDemo->WriteBool(session->writeDemo, v3);
    LOBYTE(v4) = effect->loop;
    session->writeDemo->WriteBool(session->writeDemo, v4);
    session->writeDemo->WriteInt(session->writeDemo, effect->weaponDepthHackInViewID);
    ((void (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(
      session->writeDemo,
      LODWORD(effect->modelDepthHack));
    session->writeDemo->WriteInt(session->writeDemo, effect->referenceSoundHandle);
    shaderParms = effect->shaderParms;
    v6 = 12;
    do
    {
      ((void (__thiscall *)(idDemoFile *, _DWORD))session->writeDemo->WriteFloat)(
        session->writeDemo,
        *(_DWORD *)shaderParms++);
      --v6;
    }
    while ( v6 );
    if ( effect->declEffect )
    {
      v7 = effect->declEffect->base->GetName(effect->declEffect->base);
      idDemoFile::WriteHashString(session->writeDemo, v7);
    }
    if ( (r_showDemo.internalVar->integerValue & 4) != 0 )
    {
      v8 = *(_DWORD *)common.type;
      v9 = effect->declEffect->base->GetName(effect->declEffect->base);
      (*(void (**)(netadrtype_t, const char *, ...))(v8 + 124))(common.type, "DC_EFFECTDEF: %i = %s\n", handle, v9);
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderWorldLocal::StartWritingDemo(class idDemoFile *)
void __thiscall idRenderWorldLocal::StartWritingDemo(idRenderWorldLocal *this, idDemoFile *demo)
{
  int v3; // edi
  int v4; // ebp
  int i; // eax
  idRenderLightLocal **list; // ecx
  int j; // eax
  idRenderEntityLocal **v8; // edx
  int k; // eax
  rvRenderEffectLocal **v10; // ecx

  idRenderWorldLocal::WriteLoadMap(this, (int)this);
  v3 = 0;
  if ( this->numInterAreaPortals > 0 )
  {
    v4 = 0;
    do
    {
      if ( this->doublePortals[v4].blockingBits )
        this->SetPortalState(this, v3 + 1, this->doublePortals[v4].blockingBits);
      ++v3;
      ++v4;
    }
    while ( v3 < this->numInterAreaPortals );
  }
  for ( i = 0; i < this->lightDefs.num; ++i )
  {
    list = this->lightDefs.list;
    if ( list[i] )
    {
      list[i]->writeToDemo = 1;
      this->lightDefs.list[i]->archived = 0;
    }
  }
  for ( j = 0; j < this->entityDefs.num; ++j )
  {
    v8 = this->entityDefs.list;
    if ( v8[j] )
    {
      v8[j]->writeToDemo = 1;
      this->entityDefs.list[j]->archived = 0;
    }
  }
  for ( k = 0; k < this->effectDefs.num; ++k )
  {
    v10 = this->effectDefs.list;
    if ( v10[k] )
    {
      v10[k]->writeToDemo = 1;
      this->effectDefs.list[k]->archived = 0;
    }
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::WriteVisibleDefs(struct viewDef_s const *)
void __userpurge idRenderWorldLocal::WriteVisibleDefs(
        idRenderWorldLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<edi>,
        int a4@<esi>,
        const viewDef_s *viewDef)
{
  viewEntity_s *i; // edi
  int entityDef; // esi
  viewLight_s *j; // edi
  idRenderLightLocal *lightDef; // esi
  viewEffect_s *k; // edi
  rvRenderEffectLocal *effectDef; // esi
  int v12; // [esp-Ch] [ebp-10h]
  int v13; // [esp-8h] [ebp-Ch]
  int v14; // [esp-4h] [ebp-8h]
  _DWORD *v15; // [esp+0h] [ebp-4h]

  if ( this == session->rw )
  {
    v14 = a2;
    v13 = a4;
    v12 = a3;
    for ( i = viewDef->viewEntitys; i; i = i->next )
    {
      entityDef = (int)i->entityDef;
      if ( *(_BYTE *)(entityDef + 304) )
      {
        idRenderWorldLocal::WriteRenderEntity(
          this,
          0,
          (int)this,
          (int)i,
          entityDef,
          *(_DWORD *)(entityDef + 296),
          (const renderEntity_s *)(entityDef + 4),
          v12,
          v13,
          v14,
          v15);
        *(_BYTE *)(entityDef + 304) = 0;
        *(_BYTE *)(entityDef + 305) = 1;
      }
    }
    for ( j = viewDef->viewLights; j; j = j->next )
    {
      lightDef = j->lightDef;
      if ( lightDef->writeToDemo )
      {
        idRenderWorldLocal::WriteRenderLight(this, (int)j, lightDef->index, &lightDef->parms, v12);
        lightDef->writeToDemo = 0;
        lightDef->archived = 1;
      }
    }
    for ( k = viewDef->viewEffects; k; k = k->next )
    {
      effectDef = k->effectDef;
      if ( effectDef->writeToDemo )
      {
        idRenderWorldLocal::WriteRenderEffect(this, effectDef->index, &effectDef->parms);
        effectDef->writeToDemo = 0;
        effectDef->archived = 1;
      }
    }
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::ReadRenderLight(void)
void __usercall idRenderWorldLocal::ReadRenderLight(idRenderWorldLocal *this@<ecx>, int a2@<edi>)
{
  float *v3; // esi
  int v4; // edi
  idRenderModelManager_vtbl *v5; // esi
  char *HashString; // eax
  idDeclManager_vtbl *v7; // esi
  char *v8; // eax
  int index; // [esp+6Ch] [ebp-DCh] BYREF
  renderLight_s light; // [esp+70h] [ebp-D8h] BYREF
  void *retaddr; // [esp+148h] [ebp+0h] BYREF

  session->readDemo->ReadInt(session->readDemo, &index);
  if ( index < 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "ReadRenderLight: index < 0 ");
  ((void (__thiscall *)(idDemoFile *, renderLight_s *, int))session->readDemo->ReadMat3)(session->readDemo, &light, a2);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&light.origin.y);
  session->readDemo->ReadInt(session->readDemo, &light.allowLightInViewID);
  session->readDemo->ReadInt(session->readDemo, (int *)&light.detailLevel);
  session->readDemo->ReadFloat(session->readDemo, (float *)&light.noShadows);
  session->readDemo->ReadBool(session->readDemo, &light.parallel);
  session->readDemo->ReadBool(session->readDemo, &light.globalLight);
  session->readDemo->ReadBool(session->readDemo, &light.globalLight + 2);
  session->readDemo->ReadBool(session->readDemo, (bool *)&light.lightRadius);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&light.lightRadius.y);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&light.lightCenter.y);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&light.target.y);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&light.right.y);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&light.up.y);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&light.start.y);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&light.end.y);
  session->readDemo->ReadInt(session->readDemo, &light.lightId);
  session->readDemo->ReadInt(session->readDemo, (int *)&light.shader);
  session->readDemo->ReadInt(session->readDemo, (int *)light.shaderParms);
  v3 = &light.shaderParms[1];
  v4 = 12;
  do
  {
    session->readDemo->ReadFloat(session->readDemo, v3++);
    --v4;
  }
  while ( v4 );
  session->readDemo->ReadInt(session->readDemo, (int *)&retaddr);
  if ( light.prelightModel )
  {
    v5 = renderModelManager->__vftable;
    HashString = idDemoFile::ReadHashString(session->readDemo);
    light.prelightModel = v5->FindModel(renderModelManager, HashString);
  }
  if ( light.shader )
  {
    v7 = declManager->__vftable;
    v8 = idDemoFile::ReadHashString(session->readDemo);
    light.shader = v7->FindMaterial(declManager, v8, 1);
  }
  this->UpdateLightDef(this, index, &light);
  if ( (r_showDemo.internalVar->integerValue & 2) != 0 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "DC_LIGHTDEF: %i\n",
      index);
}

// FUNC: public: void __thiscall idRenderWorldLocal::ReadRenderEntity(void)
void __usercall idRenderWorldLocal::ReadRenderEntity(idRenderWorldLocal *this@<ecx>, int a2@<edi>)
{
  idDemoFile *readDemo; // ecx
  idDemoFile_vtbl *v4; // edx
  int v5; // ebp
  float *v6; // esi
  int v7; // edi
  int *v8; // esi
  int v9; // edi
  idRenderModelManager_vtbl *v10; // esi
  char *HashString; // eax
  idDeclManager_vtbl *v12; // esi
  char *v13; // eax
  idDeclManager_vtbl *v14; // esi
  char *v15; // eax
  idDeclManager_vtbl *v16; // esi
  char *v17; // eax
  idDeclManager_vtbl *v18; // esi
  char *v19; // eax
  int v20; // ebx
  idJointMat *v21; // esi
  int v22; // edi
  int i; // esi
  const char *v24; // eax
  int index; // [esp+B4h] [ebp-E8h] BYREF
  idRenderWorldLocal *v26; // [esp+B8h] [ebp-E4h]
  renderEntity_s ent; // [esp+BCh] [ebp-E0h] BYREF

  readDemo = session->readDemo;
  v4 = readDemo->__vftable;
  v26 = this;
  v4->ReadInt(readDemo, &index);
  v5 = 0;
  if ( index < 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "ReadRenderEntity: index < 0");
  ((void (__thiscall *)(idDemoFile *, renderEntity_s *, int))session->readDemo->ReadInt)(session->readDemo, &ent, a2);
  session->readDemo->ReadInt(session->readDemo, &ent.bodyId);
  session->readDemo->ReadInt(session->readDemo, (int *)&ent.bounds);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&ent.bounds.b[0].y);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&ent.bounds.b[1].y);
  session->readDemo->ReadInt(session->readDemo, (int *)&ent.callbackData);
  session->readDemo->ReadInt(session->readDemo, &ent.suppressSurfaceInViewID);
  session->readDemo->ReadInt(session->readDemo, &ent.suppressShadowInViewID);
  session->readDemo->ReadInt(session->readDemo, &ent.suppressShadowInLightID);
  session->readDemo->ReadInt(session->readDemo, &ent.allowSurfaceInViewID);
  session->readDemo->ReadInt(session->readDemo, &ent.suppressSurfaceMask);
  session->readDemo->ReadInt(session->readDemo, (int *)&ent.origin);
  session->readDemo->ReadVec3(session->readDemo, (idVec3 *)&ent.origin.y);
  session->readDemo->ReadMat3(session->readDemo, (idMat3 *)&ent.axis.mat[0].y);
  session->readDemo->ReadInt(session->readDemo, (int *)&ent.referenceShader);
  session->readDemo->ReadInt(session->readDemo, (int *)&ent.overlayShader);
  session->readDemo->ReadInt(session->readDemo, (int *)&ent.customSkin);
  session->readDemo->ReadInt(session->readDemo, &ent.referenceSoundHandle);
  session->readDemo->ReadInt(session->readDemo, (int *)ent.shaderParms);
  v6 = &ent.shaderParms[1];
  v7 = 12;
  do
  {
    session->readDemo->ReadFloat(session->readDemo, v6++);
    --v7;
  }
  while ( v7 );
  v8 = (int *)&ent.gui[1];
  v9 = 3;
  do
  {
    session->readDemo->ReadInt(session->readDemo, v8++);
    --v9;
  }
  while ( v9 );
  session->readDemo->ReadInt(session->readDemo, &ent.numJoints);
  session->readDemo->ReadInt(session->readDemo, &ent.numJoints);
  session->readDemo->ReadInt(session->readDemo, (int *)&ent.joints);
  session->readDemo->ReadFloat(session->readDemo, &ent.modelDepthHack);
  session->readDemo->ReadBool(session->readDemo, &ent.noSelfShadow);
  session->readDemo->ReadBool(session->readDemo, &ent.noShadow);
  session->readDemo->ReadBool(session->readDemo, &ent.noDynamicInteractions);
  session->readDemo->ReadBool(session->readDemo, &ent.forceUpdate);
  session->readDemo->ReadInt(session->readDemo, &ent.weaponDepthHackInViewID);
  session->readDemo->ReadFloat(session->readDemo, &ent.shadowLODDistance);
  session->readDemo->ReadInt(session->readDemo, &ent.suppressLOD);
  ent.callback = 0;
  if ( ent.hModel )
  {
    v10 = renderModelManager->__vftable;
    HashString = idDemoFile::ReadHashString(session->readDemo);
    ent.hModel = v10->FindModel(renderModelManager, HashString);
  }
  if ( ent.customShader )
  {
    v12 = declManager->__vftable;
    v13 = idDemoFile::ReadHashString(session->readDemo);
    ent.customShader = v12->FindMaterial(declManager, v13, 1);
  }
  if ( ent.referenceShader )
  {
    v14 = declManager->__vftable;
    v15 = idDemoFile::ReadHashString(session->readDemo);
    ent.referenceShader = v14->FindMaterial(declManager, v15, 1);
  }
  if ( ent.overlayShader )
  {
    v16 = declManager->__vftable;
    v17 = idDemoFile::ReadHashString(session->readDemo);
    ent.overlayShader = v16->FindMaterial(declManager, v17, 1);
  }
  if ( ent.customSkin )
  {
    v18 = declManager->__vftable;
    v19 = idDemoFile::ReadHashString(session->readDemo);
    ent.customSkin = v18->FindSkin(declManager, v19, 1);
  }
  if ( ent.numJoints )
  {
    ent.joints = (idJointMat *)Mem_Alloc16(48 * ent.numJoints, 0x10u);
    if ( ent.numJoints > 0 )
    {
      v20 = 0;
      do
      {
        v21 = &ent.joints[v20];
        v22 = 12;
        do
        {
          session->readDemo->ReadFloat(session->readDemo, (float *)v21);
          v21 = (idJointMat *)((char *)v21 + 4);
          --v22;
        }
        while ( v22 );
        ++v5;
        ++v20;
      }
      while ( v5 < ent.numJoints );
      this = v26;
    }
  }
  ent.callbackData = 0;
  for ( i = 0; i < 3; ++i )
  {
    if ( ent.gui[i] )
      ent.gui[i] = uiManager->Alloc(uiManager);
  }
  this->UpdateEntityDef(this, index, &ent);
  if ( (r_showDemo.internalVar->integerValue & 8) != 0 )
  {
    if ( ent.hModel )
      v24 = ent.hModel->Name(ent.hModel);
    else
      v24 = aNull_1;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "DC_ENTITYDEF: %i = %s\n",
      index,
      v24);
  }
}

// FUNC: public: void __thiscall idRenderWorldLocal::ReadRenderEffect(struct renderView_s const *)
void __thiscall idRenderWorldLocal::ReadRenderEffect(idRenderWorldLocal *this, const renderView_s *renderView)
{
  float *shaderParms; // esi
  int v4; // edi
  idDeclManager_vtbl *v5; // esi
  char *HashString; // eax
  int v7; // esi
  const char *v8; // eax
  int index; // [esp+58h] [ebp-A4h] BYREF
  renderEffect_s effect; // [esp+5Ch] [ebp-A0h] BYREF

  session->readDemo->Read(session->readDemo, &index, 4);
  if ( index < 0 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "ReadRenderEffect: index < 0");
  session->readDemo->ReadInt(session->readDemo, (int *)&effect);
  session->readDemo->ReadInt(session->readDemo, &effect.suppressSurfaceInViewID);
  session->readDemo->ReadInt(session->readDemo, &effect.allowSurfaceInViewID);
  session->readDemo->ReadInt(session->readDemo, &effect.groupID);
  session->readDemo->ReadVec3(session->readDemo, &effect.origin);
  session->readDemo->ReadMat3(session->readDemo, &effect.axis);
  session->readDemo->ReadVec3(session->readDemo, &effect.gravity);
  session->readDemo->ReadVec3(session->readDemo, &effect.endOrigin);
  session->readDemo->ReadFloat(session->readDemo, &effect.attenuation);
  session->readDemo->ReadBool(session->readDemo, &effect.hasEndOrigin);
  session->readDemo->ReadBool(session->readDemo, &effect.loop);
  session->readDemo->ReadInt(session->readDemo, &effect.weaponDepthHackInViewID);
  session->readDemo->ReadFloat(session->readDemo, &effect.modelDepthHack);
  session->readDemo->ReadInt(session->readDemo, &effect.referenceSoundHandle);
  shaderParms = effect.shaderParms;
  v4 = 12;
  do
  {
    session->readDemo->ReadFloat(session->readDemo, shaderParms++);
    --v4;
  }
  while ( v4 );
  if ( effect.declEffect )
  {
    v5 = declManager->__vftable;
    HashString = idDemoFile::ReadHashString(session->readDemo);
    effect.declEffect = v5->FindEffect(declManager, HashString, 1);
  }
  this->UpdateEffectDef(this, index, &effect, renderView->time);
  if ( (r_showDemo.internalVar->integerValue & 4) != 0 )
  {
    v7 = *(_DWORD *)common.type;
    v8 = effect.declEffect->base->GetName(effect.declEffect->base);
    (*(void (**)(netadrtype_t, const char *, ...))(v7 + 124))(common.type, "DC_EFFECTDEF: %i = %s\n", index, v8);
  }
}

// FUNC: public: virtual bool __thiscall idRenderWorldLocal::ProcessDemoCommand(class idDemoFile *,struct renderView_s *,struct renderView_s *,int *)
bool __userpurge idRenderWorldLocal::ProcessDemoCommand@<al>(
        idRenderWorldLocal *this@<ecx>,
        int a2@<ebx>,
        idDemoFile *readDemo,
        renderView_s *demoRenderView,
        renderView_s *portalSkyRenderView,
        int *demoTimeOffset)
{
  bool result; // al
  int i; // ebx
  idRenderSystem_vtbl *v9; // esi
  char *HashString; // eax
  int v11; // eax
  idRenderModel *v12; // ebp
  int granularity; // eax
  bool v14; // cc
  int j; // eax
  int num; // ebx
  int v17; // eax
  int v18; // ecx
  idRenderModel **list; // edi
  int k; // eax
  int h; // [esp+Ch] [ebp-128h] BYREF
  int v22; // [esp+10h] [ebp-124h] BYREF
  int data[2]; // [esp+14h] [ebp-120h] BYREF
  int size[3]; // [esp+1Ch] [ebp-118h] BYREF
  demoHeader_t header; // [esp+28h] [ebp-10Ch] BYREF

  if ( !readDemo || !readDemo->ReadChar(readDemo, (char *)&v22 + 3) )
    return 0;
  switch ( HIBYTE(v22) )
  {
    case 1:
      idRenderWorldLocal::ReadRenderView(this, demoRenderView);
      if ( !r_showDemo.internalVar->integerValue )
        goto LABEL_86;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_RENDERVIEW: %i\n",
        demoRenderView->time);
      result = 0;
      break;
    case 2:
      idRenderWorldLocal::ReadRenderView(this, portalSkyRenderView);
      if ( !r_showDemo.internalVar->integerValue )
        goto LABEL_86;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_PORTALSKY_RENDERVIEW: %i\n",
        portalSkyRenderView->time);
      result = 0;
      break;
    case 3:
      if ( !readDemo->ReadInt(readDemo, &h) || (r_showDemo.internalVar->integerValue & 8) == 0 )
        goto LABEL_86;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_UPDATE_ENTITYDEF: %i\n",
        h);
      result = 0;
      break;
    case 4:
      if ( !readDemo->ReadInt(readDemo, &h) )
        goto LABEL_86;
      if ( (r_showDemo.internalVar->integerValue & 8) != 0 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_DELETE_ENTITYDEF: %i\n",
          h);
      this->FreeEntityDef(this, h);
      result = 0;
      break;
    case 5:
      idRenderWorldLocal::ReadRenderEntity(this, (int)readDemo);
      result = 0;
      break;
    case 6:
      if ( !readDemo->ReadInt(readDemo, &h) || (r_showDemo.internalVar->integerValue & 2) == 0 )
        goto LABEL_86;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_UPDATE_LIGHTDEF: %i\n",
        h);
      result = 0;
      break;
    case 7:
      if ( !readDemo->ReadInt(readDemo, &h) )
        goto LABEL_86;
      if ( (r_showDemo.internalVar->integerValue & 2) != 0 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_DELETE_LIGHTDEF: %i\n",
          h);
      this->FreeLightDef(this, h);
      result = 0;
      break;
    case 8:
      idRenderWorldLocal::ReadRenderLight(this, (int)readDemo);
      result = 0;
      break;
    case 9:
      if ( !readDemo->Read(readDemo, &h, 4) || (r_showDemo.internalVar->integerValue & 4) == 0 )
        goto LABEL_86;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_UPDATE_EFFECTDEF: %i\n",
        h);
      result = 0;
      break;
    case 0xA:
      if ( !readDemo->Read(readDemo, &h, 4) )
        goto LABEL_86;
      if ( (r_showDemo.internalVar->integerValue & 4) != 0 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_STOP_EFFECTDEF: %i\n",
          h);
      this->StopEffectDef(this, h);
      result = 0;
      break;
    case 0xB:
      if ( !readDemo->Read(readDemo, &h, 4) )
        goto LABEL_86;
      if ( (r_showDemo.internalVar->integerValue & 4) != 0 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_DELETE_EFFECTDEF: %i\n",
          h);
      this->FreeEffectDef(this, h);
      result = 0;
      break;
    case 0xC:
      idRenderWorldLocal::ReadRenderEffect(this, demoRenderView);
      result = 0;
      break;
    case 0xD:
      ((void (__thiscall *)(idDemoFile *, demoHeader_t *, int))readDemo->ReadInt)(readDemo, &header, a2);
      readDemo->ReadInt(readDemo, &header.sizeofRenderLight);
      readDemo->ReadInt(readDemo, (int *)header.mapname);
      for ( i = 0; i < 256; ++i )
        readDemo->ReadChar(readDemo, &header.mapname[i + 4]);
      if ( header.sizeofRenderEntity != 1834 )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "Demo version mismatch.\n");
      readDemo->ReadInt(readDemo, &portalSkyRenderView->time);
      if ( r_showDemo.internalVar->integerValue )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_LOADMAP: %s\n",
          &header.mapname[4]);
      this->InitFromMap(this, &header.mapname[4]);
      result = 0;
      break;
    case 0xE:
      if ( r_showDemo.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_CROP_RENDER\n");
      readDemo->ReadInt(readDemo, size);
      readDemo->ReadInt(readDemo, &size[1]);
      v11 = readDemo->ReadInt(readDemo, &size[2]);
      LOBYTE(v11) = size[2] != 0;
      renderSystem->CropRenderSize(renderSystem, size[0], size[1], v11, 0);
      result = 0;
      break;
    case 0xF:
      if ( r_showDemo.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "DC_UNCROP\n");
      renderSystem->UnCrop(renderSystem);
      result = 0;
      break;
    case 0x10:
      if ( r_showDemo.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_CAPTURE_RENDER\n");
      v9 = renderSystem->__vftable;
      HashString = idDemoFile::ReadHashString(readDemo);
      v9->CaptureRenderToImage(renderSystem, HashString);
      result = 0;
      break;
    case 0x11:
      if ( r_showDemo.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "DC_END_FRAME\n\n");
      this->PushMarkedDefs(this);
      result = 1;
      break;
    case 0x12:
      v12 = renderModelManager->AllocModel(renderModelManager);
      v12->ReadFromDemoFile(v12, session->readDemo);
      renderModelManager->AddModel(renderModelManager, v12);
      if ( !this->localModels.list )
      {
        granularity = this->localModels.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->localModels.size )
          {
            v14 = granularity < this->localModels.num;
            this->localModels.size = granularity;
            if ( v14 )
              this->localModels.num = granularity;
            this->localModels.list = (idRenderModel **)Memory::Allocate(4 * granularity);
            for ( j = 0; j < this->localModels.num; ++j )
              this->localModels.list[j] = *(idRenderModel **)(4 * j);
          }
        }
        else
        {
          this->localModels.list = 0;
          this->localModels.num = 0;
          this->localModels.size = 0;
        }
      }
      num = this->localModels.num;
      v17 = this->localModels.size;
      if ( num == v17 )
      {
        if ( !this->localModels.granularity )
          this->localModels.granularity = 16;
        v18 = v17
            + this->localModels.granularity
            - (v17 + this->localModels.granularity) % this->localModels.granularity;
        if ( v18 > 0 )
        {
          if ( v18 != this->localModels.size )
          {
            list = this->localModels.list;
            this->localModels.size = v18;
            if ( v18 < num )
              this->localModels.num = v18;
            this->localModels.list = (idRenderModel **)Memory::Allocate(4 * v18);
            for ( k = 0; k < this->localModels.num; ++k )
              this->localModels.list[k] = list[k];
            if ( list )
              Memory::Free(list);
          }
        }
        else
        {
          if ( this->localModels.list )
            Memory::Free(this->localModels.list);
          this->localModels.list = 0;
          this->localModels.num = 0;
          this->localModels.size = 0;
        }
      }
      this->localModels.list[this->localModels.num++] = v12;
      if ( !r_showDemo.internalVar->integerValue )
        goto LABEL_86;
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "DC_DEFINE_MODEL\n");
      result = 0;
      break;
    case 0x13:
      readDemo->ReadInt(readDemo, data);
      readDemo->ReadInt(readDemo, &data[1]);
      this->SetPortalState(this, data[0], data[1]);
      if ( !r_showDemo.internalVar->integerValue )
        goto LABEL_86;
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "DC_SET_PORTAL_STATE: %i %i\n",
        data[0],
        data[1]);
      result = 0;
      break;
    case 0x14:
      if ( r_showDemo.internalVar->integerValue )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "DC_GUI_MODEL\n");
      idGuiModel::ReadFromDemo(tr.demoGuiModel, readDemo);
      result = 0;
      break;
    default:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "Bad token in demo stream");
LABEL_86:
      result = 0;
      break;
  }
  return result;
}
