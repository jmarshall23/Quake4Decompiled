
// FUNC: private: void __thiscall idSessionLocal::PreSaveCleanup(char const *)
void __thiscall idSessionLocal::PreSaveCleanup(idSessionLocal *this, const char *name)
{
  soundSystem->SetMute(soundSystem, 1);
}

// FUNC: private: void __thiscall idSessionLocal::PostSaveCleanup(void)
void __thiscall idSessionLocal::PostSaveCleanup(idSessionLocal *this)
{
  idSessionLocal *v1; // eax

  v1 = this;
  this->syncNextGameFrame = 1;
  LOBYTE(v1) = this->insideExecuteMapChange;
  soundSystem->SetMute(soundSystem, (bool)v1);
}

// FUNC: private: bool __thiscall idSessionLocal::WriteGameData(class idFile *,enum saveType_t)
char __thiscall idSessionLocal::WriteGameData(idSessionLocal *this, idFile *fileOut, saveType_t saveType)
{
  const idKeyValue *Key; // eax
  const char *data; // eax
  const idKeyValue *v6; // eax
  const char *v7; // eax
  int v8; // edi
  idDict *persistentPlayerInfo; // ebx
  idDict *v10; // eax

  fileOut->WriteString(fileOut, "Quake4");
  fileOut->WriteInt(fileOut, 1834);
  Key = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_map");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  fileOut->WriteString(fileOut, data);
  v6 = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_entityFilter");
  if ( v6 )
    v7 = v6->value->data;
  else
    v7 = &entityFilter;
  fileOut->WriteString(fileOut, v7);
  v8 = 0;
  persistentPlayerInfo = this->mapSpawnData.persistentPlayerInfo;
  do
  {
    v10 = (idDict *)game->GetPersistentPlayerInfo(game, v8);
    idDict::operator=(persistentPlayerInfo, v10);
    idDict::WriteToFileHandle(persistentPlayerInfo, fileOut);
    ++v8;
    ++persistentPlayerInfo;
  }
  while ( v8 < 32 );
  game->SaveGame(game, fileOut, saveType);
  return 1;
}

// FUNC: private: bool __thiscall idSessionLocal::LoadPersistentGameData(class idFile *,int &,class idStr &,class idStr &,enum saveType_t &)
char __thiscall idSessionLocal::LoadPersistentGameData(
        idSessionLocal *this,
        idFile *fileIn,
        int *savegameVersion,
        idStr *saveMap,
        idStr *entityFilter,
        saveType_t *saveType)
{
  idFile_vtbl *v7; // edx
  idDict *persistentPlayerInfo; // edi
  int v10; // ebx
  idStr gamename; // [esp+10h] [ebp-2Ch] BYREF
  int v12; // [esp+38h] [ebp-4h]

  gamename.len = 0;
  gamename.alloced = 20;
  gamename.data = gamename.baseBuffer;
  gamename.baseBuffer[0] = 0;
  v7 = fileIn->__vftable;
  v12 = 0;
  v7->ReadString(fileIn, &gamename);
  if ( idStr::Cmp(gamename.data, "Quake4") )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Attempted to load an invalid savegame: %s",
      gamename.data);
    v12 = -1;
    idStr::FreeData(&gamename);
    return 0;
  }
  else
  {
    fileIn->ReadInt(fileIn, savegameVersion);
    fileIn->ReadString(fileIn, saveMap);
    fileIn->ReadString(fileIn, entityFilter);
    persistentPlayerInfo = this->mapSpawnData.persistentPlayerInfo;
    v10 = 32;
    do
    {
      idDict::ReadFromFileHandle(persistentPlayerInfo++, fileIn);
      --v10;
    }
    while ( v10 );
    v12 = -1;
    idStr::FreeData(&gamename);
    return 1;
  }
}

// FUNC: private: void __thiscall idSessionLocal::LoadLevelGameData(class idFile *,class idStr &,class idStr &,enum saveType_t)
void __userpurge idSessionLocal::LoadLevelGameData(
        idSessionLocal *this@<ecx>,
        int a2@<ebp>,
        idFile *fileIn,
        idStr *saveMap,
        idStr *entityFilter,
        saveType_t saveType)
{
  mapSpawnData_t *p_mapSpawnData; // esi
  idDict *v8; // eax
  idDict *v9; // eax
  usercmd_t *v10; // eax
  char v11; // [esp+0h] [ebp-34h]
  char v12[40]; // [esp+Ch] [ebp-28h] BYREF

  p_mapSpawnData = &this->mapSpawnData;
  idDict::Clear(&this->mapSpawnData.serverInfo);
  v8 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 1024);
  idDict::operator=(&p_mapSpawnData->serverInfo, v8);
  idDict::Set(&p_mapSpawnData->serverInfo, "si_gameType", "singleplayer");
  idDict::Set(&p_mapSpawnData->serverInfo, "si_map", saveMap->data);
  idDict::Set(&p_mapSpawnData->serverInfo, "si_entityFilter", entityFilter->data);
  idDict::Clear(&this->mapSpawnData.syncedCVars);
  v9 = (idDict *)cvarSystem->MoveCVarsToDict(cvarSystem, 2048);
  idDict::operator=(&this->mapSpawnData.syncedCVars, v9);
  v10 = usercmdGen->TicCmd(usercmdGen, v12, this->latchedTicNumber);
  qmemcpy(this->mapSpawnData.mapSpawnUsercmd, v10, 0x28u);
  this->mapSpawnData.mapSpawnUsercmd[0].buttons = 0;
  idSessionLocal::ExecuteMapChange(
    this,
    (int)this,
    a2,
    (int)&this->mapSpawnData.mapSpawnUsercmd[1],
    (int)&v10[1],
    0,
    0,
    v11);
  this->SetGUI(this, 0, 0);
  soundSystem->SetActiveSoundWorld(soundSystem, 1);
}

// FUNC: private: void __thiscall idSessionLocal::GenerateSaveFileName(class idStr &,enum saveType_t)
void __thiscall idSessionLocal::GenerateSaveFileName(idSessionLocal *this, idStr *saveName, saveType_t saveType)
{
  mapSpawnData_t *p_mapSpawnData; // esi
  const idKeyValue *Key; // eax
  const char *data; // ebx
  const idKeyValue *v7; // eax
  const char *v8; // ecx
  int v9; // eax
  char *v10; // eax
  char *v11; // eax
  idStr *v12; // eax
  int v13; // ebp
  idStr *v14; // esi
  unsigned int len; // edi
  int v16; // eax
  bool v17; // cc
  const char *v18; // eax
  char *v19; // esi
  int v20; // edi
  char v21; // cl
  int i; // eax
  char *v23; // eax
  int v24; // [esp-4h] [ebp-5Ch]
  idStr result; // [esp+Ch] [ebp-4Ch] BYREF
  idStr v26; // [esp+2Ch] [ebp-2Ch] BYREF
  int v27; // [esp+54h] [ebp-4h]

  p_mapSpawnData = &this->mapSpawnData;
  Key = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_map");
  if ( Key )
    data = Key->value->data;
  else
    data = &entityFilter;
  v7 = idDict::FindKey(&p_mapSpawnData->serverInfo, "si_entityFilter");
  if ( v7 )
    v8 = v7->value->data;
  else
    v8 = &entityFilter;
  if ( saveType == ST_AUTO )
  {
    v9 = 0;
    if ( *v8 )
    {
      do
        ++v9;
      while ( v8[v9] );
      if ( v9 )
      {
        v10 = va("Autosave %s %s", data, v8);
        idStr::operator=(saveName, v10);
        return;
      }
    }
    v11 = va("Autosave %s", data);
    goto LABEL_13;
  }
  if ( saveType == ST_CHECKPOINT )
  {
    v24 = ((unsigned __int8)this->lastCheckPoint - 1) & 1;
    this->lastCheckPoint = v24;
    v11 = va("Checkpoint%d", v24);
LABEL_13:
    idStr::operator=(saveName, v11);
    return;
  }
  idStr::operator=(saveName, (char *)idSessionLocal::com_lastQuicksave.internalVar->value);
  v12 = idStr::Right(saveName, &result, 1);
  v13 = ((unsigned __int8)atol(v12->data) + 1) & 3;
  idStr::FreeData(&result);
  v14 = idStr::Left(saveName, &v26, saveName->len - 1);
  len = v14->len;
  v16 = v14->len + 1;
  v17 = v16 <= saveName->alloced;
  v27 = 0;
  if ( !v17 )
    idStr::ReAllocate(saveName, v16, 0);
  qmemcpy(saveName->data, v14->data, len);
  saveName->data[len] = 0;
  saveName->len = len;
  v27 = -1;
  idStr::FreeData(&v26);
  v18 = va("%d", v13);
  v19 = (char *)v18;
  if ( v18 )
  {
    v20 = strlen(v18) + saveName->len;
    if ( v20 + 1 > saveName->alloced )
      idStr::ReAllocate(saveName, v20 + 1, 1);
    v21 = *v19;
    for ( i = 0; v21; v21 = v19[i] )
    {
      ++i;
      saveName->data[saveName->len - 1 + i] = v21;
    }
    v23 = saveName->data;
    saveName->len = v20;
    v23[v20] = 0;
  }
  idSessionLocal::com_lastQuicksave.internalVar->InternalSetString(
    idSessionLocal::com_lastQuicksave.internalVar,
    saveName->data);
}

// FUNC: private: class idFile * __thiscall idSessionLocal::BeginSave(char const *,enum saveType_t)
idFile *__userpurge idSessionLocal::BeginSave@<eax>(
        idSessionLocal *this@<ecx>,
        int a2@<edi>,
        const char *saveName,
        char *saveType)
{
  bool v5; // zf
  const char *v7; // eax
  idSessionLocal_vtbl *v8; // edi
  int v9; // eax
  int v10; // eax
  idStr *v11; // esi
  char *len; // ebp
  int v13; // eax
  int v14; // esi
  idStr gameFile; // [esp+30h] [ebp-4Ch] BYREF
  idStr result; // [esp+54h] [ebp-28h] BYREF
  int v17; // [esp+78h] [ebp-4h]
  void *retaddr; // [esp+7Ch] [ebp+0h]

  gameFile.len = 0;
  gameFile.alloced = 20;
  gameFile.data = gameFile.baseBuffer;
  gameFile.baseBuffer[0] = 0;
  v5 = !this->mapSpawned;
  v17 = 0;
  if ( v5 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Not playing a game.\n");
    v17 = -1;
    idStr::FreeData(&gameFile);
    return 0;
  }
  else
  {
    v7 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->GetCVarString)(
                         cvarSystem,
                         "fs_savepath",
                         a2);
    if ( Sys_GetDriveFreeSpace(v7) >= 25 )
    {
      idStr::operator=((idStr *)&gameFile.data, saveType);
      idSessionLocal::ScrubSaveGameFileName(this, (idStr *)&gameFile.data);
      v11 = operator+(&result, "savegames/", (const idStr *)&gameFile.data);
      len = (char *)v11->len;
      v13 = v11->len + 1;
      LOBYTE(retaddr) = 1;
      if ( v13 > *(int *)gameFile.baseBuffer )
        idStr::ReAllocate((idStr *)&gameFile.data, v13, 0);
      qmemcpy((void *)gameFile.alloced, v11->data, (unsigned int)len);
      len[gameFile.alloced] = 0;
      gameFile.data = len;
      LOBYTE(retaddr) = 0;
      idStr::FreeData(&result);
      idStr::SetFileExtension((idStr *)&gameFile.data, ".save");
      v14 = ((int (__thiscall *)(idFileSystem *, int, const char *))fileSystem->OpenFileWrite)(
              fileSystem,
              gameFile.alloced,
              "fs_savepath");
      if ( !v14 )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "Failed to open save file '%s'\n",
          gameFile.data);
      v17 = -1;
      idStr::FreeData(&gameFile);
      return (idFile *)v14;
    }
    else
    {
      v8 = this->__vftable;
      v9 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
             common.type,
             "#str_104314",
             -1,
             1,
             0,
             0);
      v10 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104313",
              -1,
              v9);
      ((void (__thiscall *)(idSessionLocal *, _DWORD, int))v8->MessageBoxA)(this, 0, v10);
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "Not enough drive space to save the game\n");
      v17 = -1;
      idStr::FreeData(&gameFile);
      return 0;
    }
  }
}

// FUNC: private: bool __thiscall idSessionLocal::WriteScreenshot(char const *,enum saveType_t)
char __thiscall idSessionLocal::WriteScreenshot(idSessionLocal *this, const char *saveName, saveType_t saveType)
{
  const char *v4; // eax
  int v5; // edi
  int v6; // eax
  char *data; // edx
  const char *v8; // ecx
  char v9; // al
  idStr *v10; // esi
  unsigned int len; // ebp
  int v12; // eax
  idStr previewFile; // [esp+20h] [ebp-4Ch] BYREF
  idStr result; // [esp+40h] [ebp-2Ch] BYREF
  int v16; // [esp+68h] [ebp-4h]

  if ( saveType != ST_AUTO )
  {
    previewFile.len = 0;
    previewFile.alloced = 20;
    previewFile.data = previewFile.baseBuffer;
    previewFile.baseBuffer[0] = 0;
    if ( saveName )
    {
      v4 = &saveName[strlen(saveName) + 1];
      v5 = v4 - (saveName + 1);
      v6 = v4 - saveName;
      if ( v6 > 20 )
        idStr::ReAllocate(&previewFile, v6, 1);
      data = previewFile.data;
      v8 = saveName;
      do
      {
        v9 = *v8;
        *data++ = *v8++;
      }
      while ( v9 );
      previewFile.len = v5;
    }
    v16 = 0;
    idSessionLocal::ScrubSaveGameFileName(this, &previewFile);
    v10 = operator+(&result, "savegames/", &previewFile);
    len = v10->len;
    v12 = v10->len + 1;
    LOBYTE(v16) = 1;
    if ( v12 > previewFile.alloced )
      idStr::ReAllocate(&previewFile, v12, 0);
    qmemcpy(previewFile.data, v10->data, len);
    previewFile.data[len] = 0;
    previewFile.len = len;
    LOBYTE(v16) = 0;
    idStr::FreeData(&result);
    idStr::SetFileExtension(&previewFile, ".tga");
    renderSystem->CropRenderSize(renderSystem, 320, 240, 0, 1);
    session->rw->PushMarkedDefs(session->rw);
    (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 52))(common.type, 1);
    game->Draw(game, 0);
    renderSystem->CaptureRenderToFile(renderSystem, previewFile.data, 1);
    renderSystem->UnCrop(renderSystem);
    v16 = -1;
    idStr::FreeData(&previewFile);
  }
  return 1;
}

// FUNC: private: bool __thiscall idSessionLocal::WriteDesc(char const *,enum saveType_t,char const *)
char __thiscall idSessionLocal::WriteDesc(
        idSessionLocal *this,
        const char *saveName,
        saveType_t saveType,
        const char *origSaveFileName)
{
  const char *v5; // eax
  int v6; // esi
  int v7; // eax
  char *data; // edx
  const char *v9; // ecx
  char v10; // al
  idStr *v11; // esi
  unsigned int len; // ebp
  int v13; // eax
  const char *v15; // eax
  int v16; // esi
  int v17; // eax
  const char *v18; // ecx
  char *v19; // edx
  char v20; // al
  const idKeyValue *Key; // eax
  const char *v22; // esi
  unsigned int v23; // eax
  int v24; // ebp
  int v25; // eax
  char *v26; // edx
  const char *v27; // ecx
  char v28; // al
  const idKeyValue *v29; // eax
  const char *v30; // esi
  int v31; // eax
  int v32; // edi
  int v33; // eax
  char v34; // cl
  char *v35; // edx
  int v36; // edi
  char v37; // cl
  int i; // eax
  char *v39; // edx
  const idDecl *v40; // eax
  const idDecl *v41; // edi
  char *v42; // esi
  const idKeyValue *v43; // eax
  char *v44; // eax
  char *v45; // eax
  idFile *v46; // ebx
  int v47; // edx
  idFile_vtbl *v48; // ebp
  int v49; // eax
  idFile_vtbl *v50; // edi
  int v51; // eax
  idFile_vtbl *v52; // ebp
  int v53; // eax
  const idKeyValue *v54; // eax
  char *v55; // [esp+1Ch] [ebp-A4h]
  idStr mapDeclName; // [esp+30h] [ebp-90h] BYREF
  idStr descriptionFile; // [esp+50h] [ebp-70h] BYREF
  idFile *fileDesc; // [esp+70h] [ebp-50h]
  idStr description; // [esp+74h] [ebp-4Ch] BYREF
  idStr result; // [esp+94h] [ebp-2Ch] BYREF
  int v61; // [esp+BCh] [ebp-4h]

  descriptionFile.len = 0;
  descriptionFile.alloced = 20;
  descriptionFile.data = descriptionFile.baseBuffer;
  descriptionFile.baseBuffer[0] = 0;
  if ( saveName )
  {
    v5 = &saveName[strlen(saveName) + 1];
    v6 = v5 - (saveName + 1);
    v7 = v5 - saveName;
    if ( v7 > 20 )
      idStr::ReAllocate(&descriptionFile, v7, 1);
    data = descriptionFile.data;
    v9 = saveName;
    do
    {
      v10 = *v9;
      *data++ = *v9++;
    }
    while ( v10 );
    descriptionFile.len = v6;
  }
  v61 = 0;
  idSessionLocal::ScrubSaveGameFileName(this, &descriptionFile);
  v11 = operator+(&result, "savegames/", &descriptionFile);
  len = v11->len;
  v13 = v11->len + 1;
  LOBYTE(v61) = 1;
  if ( v13 > descriptionFile.alloced )
    idStr::ReAllocate(&descriptionFile, v13, 0);
  qmemcpy(descriptionFile.data, v11->data, len);
  descriptionFile.data[len] = 0;
  descriptionFile.len = len;
  LOBYTE(v61) = 0;
  idStr::FreeData(&result);
  idStr::SetFileExtension(&descriptionFile, ".txt");
  fileDesc = fileSystem->OpenFileWrite(fileSystem, descriptionFile.data, "fs_savepath", 0);
  if ( !fileDesc )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Failed to open description file '%s'\n",
      descriptionFile.data);
    v61 = -1;
    idStr::FreeData(&descriptionFile);
    return 0;
  }
  description.data = description.baseBuffer;
  description.len = 0;
  description.alloced = 20;
  description.baseBuffer[0] = 0;
  if ( saveName )
  {
    v15 = &saveName[strlen(saveName) + 1];
    v16 = v15 - (saveName + 1);
    v17 = v15 - saveName;
    if ( v17 > 20 )
      idStr::ReAllocate(&description, v17, 1);
    v18 = saveName;
    v19 = description.data;
    do
    {
      v20 = *v18;
      *v19++ = *v18++;
    }
    while ( v20 );
    description.len = v16;
  }
  LOBYTE(v61) = 2;
  idStr::Replace(&description, "\\", asc_102A7384);
  idStr::Replace(&description, "\"", "\\\"");
  Key = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_map");
  if ( Key )
    v22 = Key->value->data;
  else
    v22 = &entityFilter;
  idDict::FindKey(&this->mapSpawnData.serverInfo, "si_entityFilter");
  mapDeclName.len = 0;
  mapDeclName.alloced = 20;
  mapDeclName.data = mapDeclName.baseBuffer;
  mapDeclName.baseBuffer[0] = 0;
  if ( v22 )
  {
    v23 = (unsigned int)&v22[strlen(v22) + 1];
    v24 = v23 - (_DWORD)(v22 + 1);
    v25 = v23 - (_DWORD)v22;
    if ( v25 > 20 )
      idStr::ReAllocate(&mapDeclName, v25, 1);
    v26 = mapDeclName.data;
    v27 = v22;
    do
    {
      v28 = *v27;
      *v26++ = *v27++;
    }
    while ( v28 );
    mapDeclName.len = v24;
  }
  LOBYTE(v61) = 3;
  v29 = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_entityFilter");
  if ( v29 )
    v30 = v29->value->data;
  else
    v30 = &entityFilter;
  v31 = 0;
  if ( *v30 )
  {
    do
      ++v31;
    while ( v30[v31] );
    if ( v31 )
    {
      v32 = mapDeclName.len + 1;
      if ( mapDeclName.len + 2 > mapDeclName.alloced )
        idStr::ReAllocate(&mapDeclName, mapDeclName.len + 2, 1);
      v33 = 0;
      v34 = 95;
      do
      {
        v35 = &mapDeclName.data[v33++];
        v35[mapDeclName.len] = v34;
        v34 = asc_1029F57C[v33];
      }
      while ( v34 );
      mapDeclName.len = v32;
      mapDeclName.data[v32] = 0;
      v36 = strlen(v30) + mapDeclName.len;
      if ( v36 + 1 > mapDeclName.alloced )
        idStr::ReAllocate(&mapDeclName, v36 + 1, 1);
      v37 = *v30;
      for ( i = 0; v37; v37 = v30[i] )
      {
        v39 = &mapDeclName.data[i++];
        v39[mapDeclName.len] = v37;
      }
      mapDeclName.len = v36;
      mapDeclName.data[v36] = 0;
    }
  }
  v40 = declManager->FindType(declManager, 17, mapDeclName.data, 0, 0);
  v41 = v40;
  if ( v40 )
  {
    v42 = mapDeclName.data;
    v43 = idDict::FindKey((idDict *)&v40[1], "name");
    if ( v43 )
      v44 = v43->value->data;
    else
      v44 = v42;
    v45 = (char *)(*(int (__thiscall **)(netadrtype_t, char *, int))(*(_DWORD *)common.type + 168))(
                    common.type,
                    v44,
                    -1);
    idStr::operator=(&mapDeclName, v45);
  }
  v46 = fileDesc;
  fileDesc->Printf(fileDesc, "\"%s\"\n", saveName);
  if ( origSaveFileName )
  {
    v46->Printf(v46, "\"^:%s\t^0%s\"\n", saveName, mapDeclName.data);
  }
  else
  {
    v47 = *(_DWORD *)common.type;
    v55 = mapDeclName.data;
    if ( saveType == ST_AUTO )
    {
      v48 = v46->__vftable;
      v49 = (*(int (__stdcall **)(const char *, int))(v47 + 168))("#str_107240", -1);
      v48->Printf(v46, "\"^:%s\t^0%s\"\n", v49, v55);
      goto LABEL_58;
    }
    if ( saveType == ST_CHECKPOINT )
    {
      v50 = v46->__vftable;
      v51 = (*(int (__stdcall **)(const char *, int))(v47 + 168))("#str_107656", -1);
      v50->Printf(v46, "\"^:%s\t^0%s\"\n", v51, v55);
LABEL_52:
      v46->Printf(v46, "\"\"\n");
      if ( saveType != ST_AUTO && saveType != ST_CHECKPOINT )
        goto LABEL_55;
      goto LABEL_54;
    }
    v52 = v46->__vftable;
    v53 = (*(int (__stdcall **)(const char *, int))(v47 + 168))("#str_107241", -1);
    v52->Printf(v46, "\"^:%s\t^0%s\"\n", v53, v55);
  }
  if ( saveType != ST_AUTO )
    goto LABEL_52;
LABEL_58:
  if ( !v41 )
    goto LABEL_52;
  v54 = idDict::FindKey((idDict *)&v41[1], "loadimage");
  if ( v54 )
    v46->Printf(v46, "\"%s\"\n", v54->value->data);
  else
    v46->Printf(v46, "\"%s\"\n", "gfx/guis/loadscreens/generic");
LABEL_54:
  v46->Printf(v46, "nooverwrite");
LABEL_55:
  fileSystem->CloseFile(fileSystem, v46);
  LOBYTE(v61) = 2;
  idStr::FreeData(&mapDeclName);
  LOBYTE(v61) = 0;
  idStr::FreeData(&description);
  v61 = -1;
  idStr::FreeData(&descriptionFile);
  return 1;
}

// FUNC: public: bool __thiscall idSessionLocal::SaveGame(char const *,enum saveType_t)
char __userpurge idSessionLocal::SaveGame@<al>(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<edi>,
        char *saveFileName,
        char *saveType)
{
  idDict *v7; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  idSessionLocal_vtbl *v10; // edi
  int v11; // eax
  int v12; // eax
  const char *v13; // eax
  idSessionLocal_vtbl *v14; // edi
  int v15; // eax
  int v16; // eax
  idSessionLocal_vtbl *v17; // edi
  int v18; // eax
  int v19; // eax
  idFile *v20; // ebp
  char v21; // bl
  int v22; // [esp+8h] [ebp-38h]
  idStr saveName; // [esp+14h] [ebp-2Ch] BYREF
  int v25; // [esp+3Ch] [ebp-4h]

  if ( this->mapSpawned )
  {
    if ( this->IsMultiplayer(this) )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "Can't save during net play.\n");
      return 0;
    }
    else
    {
      v7 = (idDict *)((int (__thiscall *)(idGame *, _DWORD, int))game->GetPersistentPlayerInfo)(game, 0, a2);
      Key = idDict::FindKey(v7, "health");
      if ( Key )
        data = Key->value->data;
      else
        data = "0";
      if ( atoi(data) > 0 )
      {
        v13 = cvarSystem->GetCVarString(cvarSystem, "fs_savepath");
        if ( Sys_GetDriveFreeSpace(v13) >= 25 )
        {
          if ( this->objectiveFailed )
          {
            v17 = this->__vftable;
            v18 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD, int, int))(*(_DWORD *)common.type + 168))(
                    common.type,
                    "#str_104312",
                    -1,
                    1,
                    0,
                    0,
                    0,
                    v22,
                    a3);
            v19 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                    common.type,
                    "#str_107654",
                    -1,
                    v18);
            ((void (__thiscall *)(idSessionLocal *, _DWORD, int))v17->MessageBoxA)(this, 0, v19);
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
              common.type,
              "Can't save after failed mission.\n");
            return 0;
          }
          else if ( !game->InCinematic(game) || saveType == (char *)2 )
          {
            saveName.len = 0;
            saveName.alloced = 20;
            saveName.data = saveName.baseBuffer;
            saveName.baseBuffer[0] = 0;
            v25 = 0;
            if ( saveFileName )
              idStr::operator=(&saveName, saveFileName);
            else
              idSessionLocal::GenerateSaveFileName(this, &saveName, (saveType_t)saveType);
            idSessionLocal::PreSaveCleanup(this, saveName.data);
            v20 = idSessionLocal::BeginSave(this, (int)saveType, saveName.data, saveType);
            if ( v20 )
            {
              v21 = idSessionLocal::WriteScreenshot(this, saveName.data, (saveType_t)saveType);
              if ( v21 )
              {
                v21 = idSessionLocal::WriteDesc(this, saveName.data, (saveType_t)saveType, saveFileName);
                if ( v21 )
                  v21 = idSessionLocal::WriteGameData(this, v20, (saveType_t)saveType);
              }
              fileSystem->CloseFile(fileSystem, v20);
              idSessionLocal::PostSaveCleanup(this);
              if ( v21 )
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                  common.type,
                  "Saved '%s'\n",
                  saveName.data);
              v25 = -1;
              idStr::FreeData(&saveName);
              return v21;
            }
            else
            {
              idSessionLocal::PostSaveCleanup(this);
              v25 = -1;
              idStr::FreeData(&saveName);
              return 0;
            }
          }
          else
          {
            (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
              common.type,
              "Can't save during a cinematic.\n");
            return 0;
          }
        }
        else
        {
          v14 = this->__vftable;
          v15 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD, int, int))(*(_DWORD *)common.type + 168))(
                  common.type,
                  "#str_104314",
                  -1,
                  1,
                  0,
                  0,
                  0,
                  v22,
                  a3);
          v16 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                  common.type,
                  "#str_104313",
                  -1,
                  v15);
          ((void (__thiscall *)(idSessionLocal *, _DWORD, int))v14->MessageBoxA)(this, 0, v16);
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
            common.type,
            "Not enough drive space to save the game.\n");
          return 0;
        }
      }
      else
      {
        v10 = this->__vftable;
        v11 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD, int))(*(_DWORD *)common.type + 168))(
                common.type,
                "#str_104312",
                -1,
                1,
                0,
                0,
                0,
                a3);
        v12 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
                common.type,
                "#str_104311",
                -1,
                v11);
        ((void (__thiscall *)(idSessionLocal *, _DWORD, int))v10->MessageBoxA)(this, 0, v12);
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
          common.type,
          "You must be alive to save the game.\n");
        return 0;
      }
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Not playing a game.\n");
    return 0;
  }
}

// FUNC: private: class idFile * __thiscall idSessionLocal::BeginLoad(char const *)
idFile *__thiscall idSessionLocal::BeginLoad(idSessionLocal *this, const char *loadName)
{
  const char *v3; // eax
  int v4; // edi
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  idStr *v9; // esi
  unsigned int len; // ebp
  int v11; // eax
  idFile *v12; // esi
  idStr loadFile; // [esp+10h] [ebp-4Ch] BYREF
  idStr result; // [esp+30h] [ebp-2Ch] BYREF
  int v16; // [esp+58h] [ebp-4h]

  loadFile.len = 0;
  loadFile.alloced = 20;
  loadFile.data = loadFile.baseBuffer;
  loadFile.baseBuffer[0] = 0;
  if ( loadName )
  {
    v3 = &loadName[strlen(loadName) + 1];
    v4 = v3 - (loadName + 1);
    v5 = v3 - loadName;
    if ( v5 > 20 )
      idStr::ReAllocate(&loadFile, v5, 1);
    data = loadFile.data;
    v7 = loadName;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    loadFile.len = v4;
  }
  v16 = 0;
  idSessionLocal::ScrubSaveGameFileName(this, &loadFile);
  idStr::SetFileExtension(&loadFile, ".save");
  v9 = operator+(&result, "savegames/", &loadFile);
  len = v9->len;
  v11 = v9->len + 1;
  LOBYTE(v16) = 1;
  if ( v11 > loadFile.alloced )
    idStr::ReAllocate(&loadFile, v11, 0);
  qmemcpy(loadFile.data, v9->data, len);
  loadFile.data[len] = 0;
  loadFile.len = len;
  LOBYTE(v16) = 0;
  idStr::FreeData(&result);
  v12 = fileSystem->OpenFileRead(fileSystem, loadFile.data, 1, 0);
  if ( v12 )
  {
    v16 = -1;
    idStr::FreeData(&loadFile);
    return v12;
  }
  else
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Couldn't open savegame file %s",
      loadFile.data);
    v16 = -1;
    idStr::FreeData(&loadFile);
    return 0;
  }
}

// FUNC: public: bool __thiscall idSessionLocal::LoadGame(char const *)
char __userpurge idSessionLocal::LoadGame@<al>(idSessionLocal *this@<ecx>, int a2@<ebp>, char *loadFileName)
{
  idSessionLocal_vtbl *v4; // edx
  char *v5; // eax
  idFile *v6; // eax
  int *p_savegameVersion; // edi
  char *data; // [esp-4h] [ebp-7Ch]
  idStr loadName; // [esp+Ch] [ebp-6Ch] BYREF
  idStr saveMap; // [esp+2Ch] [ebp-4Ch] BYREF
  idStr entityFilter; // [esp+4Ch] [ebp-2Ch] BYREF
  int v13; // [esp+74h] [ebp-4h]

  loadName.len = 0;
  loadName.alloced = 20;
  loadName.data = loadName.baseBuffer;
  loadName.baseBuffer[0] = 0;
  v4 = this->__vftable;
  v13 = 0;
  if ( v4->IsMultiplayer(this) )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Can't load during net play.\n");
LABEL_9:
    v13 = -1;
    idStr::FreeData(&loadName);
    return 0;
  }
  this->StopBox(this);
  v5 = loadFileName;
  if ( !loadFileName )
    v5 = (char *)cvarSystem->GetCVarString(cvarSystem, "com_lastQuicksave");
  idStr::operator=(&loadName, v5);
  data = loadName.data;
  this->loadingSaveGame = 1;
  v6 = idSessionLocal::BeginLoad(this, data);
  this->savegameFile = v6;
  if ( !v6 )
  {
    this->loadingSaveGame = 0;
    this->savegameFile = 0;
    goto LABEL_9;
  }
  saveMap.len = 0;
  saveMap.alloced = 20;
  saveMap.data = saveMap.baseBuffer;
  saveMap.baseBuffer[0] = 0;
  entityFilter.len = 0;
  entityFilter.alloced = 20;
  entityFilter.data = entityFilter.baseBuffer;
  entityFilter.baseBuffer[0] = 0;
  p_savegameVersion = &this->savegameVersion;
  LOBYTE(v13) = 2;
  if ( !idSessionLocal::LoadPersistentGameData(
          this,
          v6,
          &this->savegameVersion,
          &saveMap,
          &entityFilter,
          (saveType_t *)&loadFileName) )
  {
    fileSystem->CloseFile(fileSystem, this->savegameFile);
    this->loadingSaveGame = 0;
    this->savegameFile = 0;
    LOBYTE(v13) = 1;
    idStr::FreeData(&entityFilter);
    LOBYTE(v13) = 0;
    idStr::FreeData(&saveMap);
    goto LABEL_9;
  }
  if ( !idSessionLocal::com_allowBadSavegameVersion.internalVar->integerValue && *p_savegameVersion != 1834 )
  {
    fileSystem->CloseFile(fileSystem, this->savegameFile);
    this->loadingSaveGame = 0;
    this->savegameFile = 0;
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "loading a v%d savegame\n",
    *p_savegameVersion);
  if ( saveMap.len > 0 )
    idSessionLocal::LoadLevelGameData(this, a2, this->savegameFile, &saveMap, &entityFilter, ST_REGULAR);
  if ( idSessionLocal::com_allowBadSavegameVersion.internalVar->integerValue || *p_savegameVersion == 1834 )
  {
    fileSystem->CloseFile(fileSystem, this->savegameFile);
    this->loadingSaveGame = 0;
    this->savegameFile = 0;
  }
  LOBYTE(v13) = 1;
  idStr::FreeData(&entityFilter);
  LOBYTE(v13) = 0;
  idStr::FreeData(&saveMap);
  v13 = -1;
  idStr::FreeData(&loadName);
  return 1;
}

// FUNC: public: bool __thiscall idSessionLocal::DeleteGame(char const *)
char __thiscall idSessionLocal::DeleteGame(idSessionLocal *this, const char *saveName)
{
  const char *value; // esi
  unsigned int v3; // eax
  int v4; // ebx
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  const char *v9; // esi
  idStr *v10; // eax
  int v11; // ebp
  idStr *v12; // esi
  unsigned int len; // ebx
  int v14; // eax
  const char *v15; // eax
  const char *v16; // esi
  unsigned int v17; // kr00_4
  int v18; // edi
  char v19; // cl
  int i; // eax
  char *v21; // edx
  idFileSystem_vtbl *v22; // edi
  char *v23; // eax
  idFileSystem_vtbl *v24; // edi
  char *v25; // eax
  idFileSystem_vtbl *v26; // edi
  char *v27; // eax
  idStr name; // [esp+1Ch] [ebp-4Ch] BYREF
  idStr result; // [esp+3Ch] [ebp-2Ch] BYREF
  int v31; // [esp+64h] [ebp-4h]

  value = idSessionLocal::com_lastQuicksave.internalVar->value;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  if ( value )
  {
    v3 = (unsigned int)&value[strlen(value) + 1];
    v4 = v3 - (_DWORD)(value + 1);
    v5 = v3 - (_DWORD)value;
    if ( v5 > 20 )
      idStr::ReAllocate(&name, v5, 1);
    data = name.data;
    v7 = value;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    name.len = v4;
  }
  v9 = saveName;
  v31 = 0;
  if ( !idStr::Icmp(saveName, name.data) )
  {
    v10 = idStr::Right(&name, &result, 1);
    v11 = ((unsigned __int8)atol(v10->data) - 1) & 3;
    idStr::FreeData(&result);
    v12 = idStr::Left(&name, &result, name.len - 1);
    len = v12->len;
    v14 = v12->len + 1;
    LOBYTE(v31) = 1;
    if ( v14 > name.alloced )
      idStr::ReAllocate(&name, v14, 0);
    qmemcpy(name.data, v12->data, len);
    name.data[len] = 0;
    name.len = len;
    LOBYTE(v31) = 0;
    idStr::FreeData(&result);
    v15 = va("%d", v11);
    v16 = v15;
    if ( v15 )
    {
      v17 = strlen(v15);
      v18 = v17 + name.len;
      if ( (int)(v17 + name.len + 1) > name.alloced )
        idStr::ReAllocate(&name, v17 + name.len + 1, 1);
      v19 = *v16;
      for ( i = 0; v19; v19 = v16[i] )
      {
        v21 = &name.data[i++];
        v21[name.len] = v19;
      }
      name.len = v18;
      name.data[v18] = 0;
    }
    idSessionLocal::com_lastQuicksave.internalVar->InternalSetString(
      idSessionLocal::com_lastQuicksave.internalVar,
      name.data);
    v9 = saveName;
  }
  v22 = fileSystem->__vftable;
  v23 = va("savegames/%s.save", v9);
  v22->RemoveFile(fileSystem, v23, "fs_savepath");
  v24 = fileSystem->__vftable;
  v25 = va("savegames/%s.tga", v9);
  v24->RemoveFile(fileSystem, v25, "fs_savepath");
  v26 = fileSystem->__vftable;
  v27 = va("savegames/%s.txt", v9);
  v26->RemoveFile(fileSystem, v27, "fs_savepath");
  v31 = -1;
  idStr::FreeData(&name);
  return 1;
}
