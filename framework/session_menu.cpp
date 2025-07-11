
// FUNC: public: virtual void __thiscall idSessionLocal::ExitMenu(void)
void __thiscall idSessionLocal::ExitMenu(idSessionLocal *this)
{
  this->guiActive = 0;
  game->UpdatePlayerPostMainMenu(game);
  soundSystem->SetActiveSoundWorld(soundSystem, 1);
  cvarSystem->SetCVarBool(cvarSystem, "ui_chat", 0, 0);
}

// FUNC: public: virtual int __thiscall idSessionLocal::GetDesiredSoundWorld(bool,bool &)
int __thiscall idSessionLocal::GetDesiredSoundWorld(idSessionLocal *this, bool on, bool *hitchReqd)
{
  bool v5; // al
  idUserInterface *guiActive; // ecx

  if ( !(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 2112) )
  {
    if ( !on )
      return 0;
    if ( (*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 64))(common.type) )
      return 3;
    v5 = sys->IsAppActive(sys);
    guiActive = this->guiActive;
    if ( !v5 )
    {
      *hitchReqd = guiActive == this->guiMainMenu;
      return 0;
    }
    if ( guiActive == this->guiMainMenu )
    {
      *hitchReqd = 1;
      return 2;
    }
    *hitchReqd = 0;
  }
  return 1;
}

// FUNC: int __cdecl idListSaveGameCompare(struct fileTime_t const *,struct fileTime_t const *)
unsigned int __cdecl idListSaveGameCompare(const fileTime_t *a, const fileTime_t *b)
{
  return b->timeStamp - a->timeStamp;
}

// FUNC: public: void __thiscall idSessionLocal::SetPbMenuGuiVars(void)
void __thiscall idSessionLocal::SetPbMenuGuiVars(idSessionLocal *this)
{
  bool v2; // zf
  const char *v3; // eax
  const char *v4; // eax

  v2 = isPbClEnabled() == 0;
  v3 = "1";
  if ( v2 )
    v3 = "0";
  this->guiMainMenu->SetStateString(this->guiMainMenu, "gui_cl_punkbuster", v3);
  v2 = isPbSvEnabled() == 0;
  v4 = "1";
  if ( v2 )
    v4 = "0";
  this->guiMainMenu->SetStateString(this->guiMainMenu, "gui_sv_punkbuster", v4);
}

// FUNC: private: bool __thiscall idSessionLocal::BoxDialogSanityCheck(void)
char __thiscall idSessionLocal::BoxDialogSanityCheck(idSessionLocal *this)
{
  if ( !(*(unsigned __int8 (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 16))(common.type) )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "message box sanity check: !common->IsInitialized()\n");
    return 0;
  }
  if ( !this->guiMsg )
    return 0;
  if ( this->guiMsgRestore )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "message box sanity check: recursed\n");
    return 0;
  }
  if ( cvarSystem->GetCVarInteger(cvarSystem, "net_serverDedicated") )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "message box sanity check: not compatible with dedicated server\n");
    return 0;
  }
  return 1;
}

// FUNC: public: virtual void __thiscall idSessionLocal::SetCDKeyGuiVars(void)
void __thiscall idSessionLocal::SetCDKeyGuiVars(idSessionLocal *this)
{
  int v2; // ebx
  idUserInterface_vtbl *v3; // edi
  char *v4; // eax
  int v5; // eax

  if ( this->guiMainMenu )
  {
    v2 = *(_DWORD *)common.type;
    v3 = this->guiMainMenu->__vftable;
    v4 = va("#str_1071%d", this->cdkey_state + 86);
    v5 = (*(int (__thiscall **)(netadrtype_t, char *, int))(v2 + 168))(common.type, v4, -1);
    v3->SetStateString(this->guiMainMenu, "str_d3key_state", (const char *)v5);
  }
}

// FUNC: public: void __thiscall idSessionLocal::HandleIntroMenuCommands(char const *)
void __thiscall idSessionLocal::HandleIntroMenuCommands(idSessionLocal *this, const char *menuCommand)
{
  idSessionLocal *v2; // ebp
  int argc; // eax
  int i; // edi
  const char *v5; // esi
  const char *v6; // esi
  unsigned int v7; // eax
  int v8; // ebp
  int v9; // eax
  char *data; // edx
  const char *v11; // ecx
  char v12; // al
  idSoundSystem_vtbl *v13; // eax
  idStr snd; // [esp+10h] [ebp-930h] BYREF
  idCmdArgs args; // [esp+30h] [ebp-910h] BYREF
  int v17; // [esp+93Ch] [ebp-4h]

  v2 = this;
  args.argc = 0;
  idCmdArgs::TokenizeString(&args, menuCommand, 0);
  argc = args.argc;
  for ( i = 0; i < args.argc; argc = args.argc )
  {
    if ( i < 0 || i >= argc )
      v5 = &entityFilter;
    else
      v5 = args.argv[i];
    ++i;
    if ( idStr::Icmp(v5, "startGame") )
    {
      if ( !idStr::Icmp(v5, "play") && args.argc - i >= 1 )
      {
        if ( i < 0 || i >= args.argc )
          v6 = &entityFilter;
        else
          v6 = args.argv[i];
        snd.len = 0;
        snd.alloced = 20;
        snd.data = snd.baseBuffer;
        snd.baseBuffer[0] = 0;
        if ( v6 )
        {
          v7 = (unsigned int)&v6[strlen(v6) + 1];
          v8 = v7 - (_DWORD)(v6 + 1);
          v9 = v7 - (_DWORD)v6;
          if ( v9 > 20 )
            idStr::ReAllocate(&snd, v9, 1);
          data = snd.data;
          v11 = v6;
          do
          {
            v12 = *v11;
            *data++ = *v11++;
          }
          while ( v12 );
          snd.len = v8;
          v2 = this;
        }
        v13 = soundSystem->__vftable;
        v17 = 0;
        ++i;
        v13->PlayShaderDirectly(soundSystem, 2, snd.data, -1);
        v17 = -1;
        idStr::FreeData(&snd);
      }
    }
    else
    {
      soundSystem->StopAllSounds(soundSystem, 2);
      v2->ExitMenu(v2);
    }
  }
}

// FUNC: public: void __thiscall idSessionLocal::UpdateMPLevelShot(void)
void __thiscall idSessionLocal::UpdateMPLevelShot(idSessionLocal *this)
{
  idFileSystem_vtbl *v1; // edi
  int v3; // eax
  char screenshot[1024]; // [esp+18h] [ebp-400h] BYREF

  v1 = fileSystem->__vftable;
  v3 = ((int (__thiscall *)(idCVarSystem *, const char *, char *, int))cvarSystem->GetCVarString)(
         cvarSystem,
         "si_map",
         screenshot,
         1024);
  ((void (__thiscall *)(idFileSystem *, int))v1->FindMapScreenshot)(fileSystem, v3);
  this->guiMainMenu->SetStateString(this->guiMainMenu, "current_levelshot", screenshot);
  declManager->FindMaterial(declManager, screenshot, 1)->sort = -2.0;
}

// FUNC: public: void __thiscall idSessionLocal::HandleInGameCommands(char const *)
void __thiscall idSessionLocal::HandleInGameCommands(idSessionLocal *this, const char *menuCommand)
{
  idSessionLocal *v2; // ebp
  int argc; // eax
  int i; // edi
  const char *v5; // esi
  idUserInterface *guiActive; // ecx
  const char *v7; // esi
  int v8; // eax
  unsigned int v9; // eax
  int v10; // ebp
  int v11; // eax
  char *data; // edx
  const char *v13; // ecx
  char v14; // al
  int v15; // esi
  char *v16; // eax
  const char *v17; // eax
  idStr snd; // [esp+10h] [ebp-944h] BYREF
  sysEvent_s ev; // [esp+30h] [ebp-924h] BYREF
  idCmdArgs args; // [esp+44h] [ebp-910h] BYREF
  int v22; // [esp+950h] [ebp-4h]

  v2 = this;
  args.argc = 0;
  idCmdArgs::TokenizeString(&args, menuCommand, 0);
  argc = args.argc;
  for ( i = 0; i < args.argc; argc = args.argc )
  {
    if ( i < 0 || i >= argc )
      v5 = &entityFilter;
    else
      v5 = args.argv[i];
    ++i;
    if ( idStr::Icmp(v5, "unmute") )
    {
      if ( idStr::Icmp(v5, "close") )
      {
        if ( idStr::Icmp(v5, "play") )
        {
          if ( !idStr::Icmp(v5, "exec") )
          {
            if ( i < 0 || i >= args.argc )
              v17 = &entityFilter;
            else
              v17 = args.argv[i];
            cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, v17);
            ++i;
          }
        }
        else if ( args.argc - i >= 1 )
        {
          if ( i < 0 || i >= args.argc )
            v7 = &entityFilter;
          else
            v7 = args.argv[i];
          v8 = 0;
          snd.len = 0;
          snd.alloced = 20;
          snd.data = snd.baseBuffer;
          snd.baseBuffer[0] = 0;
          if ( v7 )
          {
            v9 = (unsigned int)&v7[strlen(v7) + 1];
            v10 = v9 - (_DWORD)(v7 + 1);
            v11 = v9 - (_DWORD)v7;
            if ( v11 > 20 )
              idStr::ReAllocate(&snd, v11, 1);
            data = snd.data;
            v13 = v7;
            do
            {
              v14 = *v13;
              *data++ = *v13++;
            }
            while ( v14 );
            v8 = v10;
            v2 = this;
            snd.len = v8;
          }
          v15 = 1;
          ++i;
          v22 = 0;
          if ( v8 == 1 )
          {
            v15 = atoi(snd.data);
            if ( i < 0 || i >= args.argc )
              v16 = (char *)&entityFilter;
            else
              v16 = args.argv[i];
            idStr::operator=(&snd, v16);
            ++i;
          }
          soundSystem->PlayShaderDirectly(soundSystem, 1, snd.data, v15);
          v22 = -1;
          idStr::FreeData(&snd);
        }
      }
      else
      {
        guiActive = v2->guiActive;
        if ( guiActive )
        {
          ev.evType = SE_NONE;
          guiActive->HandleEvent(guiActive, &ev, com_frameTime, 0);
          v2->guiActive->Activate(v2->guiActive, 0, com_frameTime);
          v2->guiActive = 0;
        }
      }
    }
    else
    {
      soundSystem->SetMute(soundSystem, 0);
    }
  }
}

// FUNC: private: void __thiscall idSessionLocal::UpdateMPSettingsModel(void)
void __usercall idSessionLocal::UpdateMPSettingsModel(idSessionLocal *this@<ecx>, int a2@<esi>)
{
  const char *v3; // eax
  const idDecl *v4; // eax
  idDict *v5; // esi
  const idKeyValue *Key; // eax
  const char *data; // eax
  const idKeyValue *v8; // eax
  const char *v9; // eax

  v3 = cvarSystem->GetCVarString(cvarSystem, "ui_model");
  v4 = declManager->FindType(declManager, 4, v3, 0, 0);
  if ( v4 )
  {
    v5 = (idDict *)&v4[1];
    Key = idDict::FindKey((idDict *)&v4[1], "model");
    if ( Key )
      data = Key->value->data;
    else
      data = &entityFilter;
    ((void (__thiscall *)(idUserInterface *, const char *, const char *, int))this->guiActive->SetStateString)(
      this->guiActive,
      "player_model_name",
      data,
      a2);
    idDict::FindKey(v5, "def_head");
    ((void (__thiscall *)(idUserInterface *, const char *))this->guiActive->SetStateString)(
      this->guiActive,
      "player_head_model_name");
    v8 = idDict::FindKey(v5, "skin");
    if ( v8 )
      v9 = v8->value->data;
    else
      v9 = &entityFilter;
    this->guiActive->SetStateString(this->guiActive, "player_skin_name", v9);
    this->guiActive->SetStateBool(this->guiActive, "need_update", 1);
  }
}

// FUNC: public: void __thiscall idSessionLocal::HandleMsgCommands(char const *)
void __thiscall idSessionLocal::HandleMsgCommands(idSessionLocal *this, const char *menuCommand)
{
  int argc; // eax
  int v4; // ebx
  const char *v5; // edi
  idUserInterface *guiActive; // ecx
  idUserInterface *guiMsgRestore; // eax
  bool v8; // zf
  const char *v9; // edi
  int v10; // eax
  unsigned int v11; // eax
  int v12; // ebp
  int v13; // eax
  char *v14; // edx
  const char *v15; // ecx
  char v16; // al
  int v17; // edi
  char *v18; // eax
  idUserInterface *v19; // [esp-10h] [ebp-94Ch]
  char *data; // [esp-Ch] [ebp-948h]
  idStr snd; // [esp+Ch] [ebp-930h] BYREF
  idCmdArgs args; // [esp+2Ch] [ebp-910h] BYREF
  int v23; // [esp+938h] [ebp-4h]

  args.argc = 0;
  idCmdArgs::TokenizeString(&args, menuCommand, 0);
  argc = args.argc;
  v4 = 0;
  while ( v4 < argc )
  {
    if ( v4 < 0 || v4 >= argc )
      v5 = &entityFilter;
    else
      v5 = args.argv[v4];
    ++v4;
    if ( !idStr::Icmp(menuCommand, "stop") )
    {
      this->guiActive = this->guiMsgRestore;
      this->guiMsgRestore = 0;
      this->msgRunning = 0;
      this->msgRetIndex = -1;
    }
    if ( this->msgIgnoreButtons )
    {
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
        common.type,
        "MessageBox HandleMsgCommands 1st frame ignore\n");
      return;
    }
    if ( idStr::Icmp(v5, "mid") && idStr::Icmp(v5, "left") )
    {
      if ( idStr::Icmp(v5, "right") )
        goto LABEL_15;
      this->guiActive = this->guiMsgRestore;
      guiActive = this->guiActive;
      data = this->msgFireBack[1].data;
      this->msgRetIndex = 1;
      v19 = guiActive;
    }
    else
    {
      data = this->msgFireBack[0].data;
      guiMsgRestore = this->guiMsgRestore;
      this->guiActive = guiMsgRestore;
      this->msgRetIndex = 0;
      v19 = guiMsgRestore;
    }
    this->msgRunning = 0;
    this->guiMsgRestore = 0;
    idSessionLocal::DispatchCommand(this, v19, data, 1);
LABEL_15:
    v8 = idStr::Icmp(v5, "play") == 0;
    argc = args.argc;
    if ( v8 && args.argc - v4 >= 1 )
    {
      if ( v4 < 0 || v4 >= args.argc )
        v9 = &entityFilter;
      else
        v9 = args.argv[v4];
      v10 = 0;
      snd.len = 0;
      snd.alloced = 20;
      snd.data = snd.baseBuffer;
      snd.baseBuffer[0] = 0;
      if ( v9 )
      {
        v11 = (unsigned int)&v9[strlen(v9) + 1];
        v12 = v11 - (_DWORD)(v9 + 1);
        v13 = v11 - (_DWORD)v9;
        if ( v13 > 20 )
          idStr::ReAllocate(&snd, v13, 1);
        v14 = snd.data;
        v15 = v9;
        do
        {
          v16 = *v15;
          *v14++ = *v15++;
        }
        while ( v16 );
        v10 = v12;
        snd.len = v12;
      }
      v17 = 1;
      ++v4;
      v23 = 0;
      if ( v10 == 1 )
      {
        v17 = atoi(snd.data);
        if ( v4 < 0 || v4 >= args.argc )
          v18 = (char *)&entityFilter;
        else
          v18 = args.argv[v4];
        idStr::operator=(&snd, v18);
        ++v4;
      }
      soundSystem->PlayShaderDirectly(soundSystem, 2, snd.data, v17);
      v23 = -1;
      idStr::FreeData(&snd);
      argc = args.argc;
    }
  }
}

// FUNC: public: void __thiscall idSessionLocal::PopulateMPMapList(char const *,class idListGUI *,char const *,class idListGUI *)
void __userpurge idSessionLocal::PopulateMPMapList(
        idSessionLocal *this@<ecx>,
        int a2@<ebp>,
        int a3@<esi>,
        const char *listname,
        idListGUI *guiList,
        const char *mapCycle,
        idListGUI *guiMapCycle)
{
  const char *v8; // ecx
  int v9; // ebp
  const char *v10; // esi
  const idDecl *v11; // eax
  const idKeyValue *v12; // eax
  const char *v13; // eax
  idUserInterface_vtbl *v14; // ebp
  char *v15; // eax
  unsigned int v16; // eax
  int v17; // ebp
  int v18; // eax
  char *data; // ecx
  char v20; // al
  bool v21; // cc
  idUserInterface_vtbl *v22; // ebp
  char *v23; // eax
  idUserInterface_vtbl *v24; // ebp
  char *v25; // eax
  int v26; // [esp+30h] [ebp-34h]
  const char *gm; // [esp+34h] [ebp-30h]
  int v28; // [esp+38h] [ebp-2Ch]
  char *key; // [esp+3Ch] [ebp-28h]
  idStr v30; // [esp+40h] [ebp-24h] BYREF

  if ( this->guiActive )
  {
    key = (char *)((int (__thiscall *)(idCVarSystem *, const char *, int, int))cvarSystem->GetCVarString)(
                    cvarSystem,
                    "si_gametype",
                    a3,
                    a2);
    guiMapCycle->Clear(guiMapCycle);
    v8 = 0;
    v26 = 0;
    gm = 0;
    if ( this->masterMapList.num > 0 )
    {
      v9 = 0;
      v28 = 0;
      do
      {
        if ( !idStr::FindText(*(const char **)((char *)&sessLocal.masterMapList.list->data + v9), "mp/", 1, 0, -1) )
        {
          v10 = *(char **)((char *)&this->masterMapList.list->data + v9);
          v11 = declManager->FindType(declManager, 17, v10, 0, 0);
          if ( v11 )
          {
            v12 = idDict::FindKey((idDict *)&v11[1], key);
            v13 = v12 ? v12->value->data : "0";
            if ( atoi(v13) )
            {
              v14 = this->guiActive->__vftable;
              v15 = va("%s_item_%i", mapCycle, v26);
              v14->SetStateString(this->guiActive, v15, v10);
              v30.len = 0;
              v30.alloced = 20;
              v30.data = v30.baseBuffer;
              v30.baseBuffer[0] = 0;
              if ( v10 )
              {
                v16 = (unsigned int)&v10[strlen(v10) + 1];
                v17 = v16 - (_DWORD)(v10 + 1);
                v18 = v16 - (_DWORD)v10;
                if ( v18 > 20 )
                  idStr::ReAllocate(&v30, v18, 1);
                data = v30.data;
                do
                {
                  v20 = *v10;
                  *data++ = *v10++;
                }
                while ( v20 );
                v30.len = v17;
              }
              guiMapCycle->Add(guiMapCycle, v26, &v30, 0);
              idStr::FreeData(&v30);
              v9 = v28;
              ++v26;
            }
          }
        }
        v8 = gm + 1;
        v9 += 32;
        v21 = (int)++gm < this->masterMapList.num;
        v28 = v9;
      }
      while ( v21 );
    }
    v22 = this->guiActive->__vftable;
    v23 = va("%s_item_%i", mapCycle, v8);
    v22->DeleteState(this->guiActive, v23);
    v24 = this->guiActive->__vftable;
    v25 = va("%s_sel_0", mapCycle);
    ((void (__thiscall *)(idUserInterface *, char *))v24->SetStateInt)(this->guiActive, v25);
    this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
  }
}

// FUNC: public: void __thiscall idSessionLocal::PopulateEditCVarGUI(enum cvarHelpCategory_t)
void __thiscall idSessionLocal::PopulateEditCVarGUI(idSessionLocal *this, cvarHelpCategory_t filter)
{
  idCVarHelp *v3; // ebx
  int v4; // edi
  idUserInterface_vtbl *v5; // ebp
  char *v6; // eax
  idUserInterface_vtbl *v7; // ebp
  char *v8; // eax
  idUserInterface_vtbl *v9; // ebp
  char *v10; // eax
  idUserInterface_vtbl *v11; // ebp
  char *v12; // eax
  idUserInterface_vtbl *v13; // ebp
  char *v14; // eax
  idUserInterface_vtbl *v15; // ebx
  char *v16; // eax
  const char *cvarName; // [esp-8h] [ebp-14h]
  const char *friendlyName; // [esp-8h] [ebp-14h]
  const char *choices; // [esp-8h] [ebp-14h]
  const char *values; // [esp-8h] [ebp-14h]

  v3 = cvarSystem->GetHelps(cvarSystem, filter);
  v4 = 1;
  if ( !v3 )
    goto LABEL_8;
  do
  {
    v5 = this->guiActive->__vftable;
    cvarName = v3->cvarName;
    v6 = va("cvar%d", v4);
    v5->SetStateString(this->guiActive, v6, cvarName);
    v7 = this->guiActive->__vftable;
    friendlyName = v3->friendlyName;
    v8 = va("cvar%dFriendly", v4);
    v7->SetStateString(this->guiActive, v8, friendlyName);
    v9 = this->guiActive->__vftable;
    choices = v3->choices;
    v10 = va("cvar%dChoices", v4);
    v9->SetStateString(this->guiActive, v10, choices);
    v11 = this->guiActive->__vftable;
    values = v3->values;
    v12 = va("cvar%dValues", v4);
    v11->SetStateString(this->guiActive, v12, values);
    v13 = this->guiActive->__vftable;
    v14 = va("cvar%dVisible", v4);
    v13->SetStateBool(this->guiActive, v14, 1);
    v3 = (idCVarHelp *)v3->next;
    ++v4;
  }
  while ( v3 );
  if ( v4 <= 22 )
  {
LABEL_8:
    do
    {
      v15 = this->guiActive->__vftable;
      v16 = va("cvar%dVisible", v4);
      v15->SetStateBool(this->guiActive, v16, 0);
      ++v4;
    }
    while ( v4 <= 22 );
  }
  this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
}

// FUNC: public: __thiscall rvSpawnDef::rvSpawnDef(char const *,char const *)
void __thiscall rvSpawnDef::rvSpawnDef(rvSpawnDef *this, const char *name, const char *spawn)
{
  const char *v4; // eax
  int v5; // ebx
  int v6; // eax
  char *data; // edx
  const char *v8; // ecx
  char v9; // al
  const char *v10; // eax
  int v11; // ebp
  int v12; // eax
  char *v13; // edx
  const char *v14; // ecx
  char v15; // al

  this->nameString.len = 0;
  this->nameString.alloced = 20;
  this->nameString.data = this->nameString.baseBuffer;
  this->nameString.baseBuffer[0] = 0;
  if ( name )
  {
    v4 = &name[strlen(name) + 1];
    v5 = v4 - (name + 1);
    v6 = v4 - name;
    if ( v6 > this->nameString.alloced )
      idStr::ReAllocate(&this->nameString, v6, 1);
    data = this->nameString.data;
    v8 = name;
    do
    {
      v9 = *v8;
      *data++ = *v8++;
    }
    while ( v9 );
    this->nameString.len = v5;
  }
  this->spawnString.len = 0;
  this->spawnString.alloced = 20;
  this->spawnString.data = this->spawnString.baseBuffer;
  this->spawnString.baseBuffer[0] = 0;
  if ( spawn )
  {
    v10 = &spawn[strlen(spawn) + 1];
    v11 = v10 - (spawn + 1);
    v12 = v10 - spawn;
    if ( v12 > this->spawnString.alloced )
      idStr::ReAllocate(&this->spawnString, v12, 1);
    v13 = this->spawnString.data;
    v14 = spawn;
    do
    {
      v15 = *v14;
      *v13++ = *v14++;
    }
    while ( v15 );
    this->spawnString.len = v11;
  }
}

// FUNC: int __cdecl rvSpawnSortCompare<class rvSpawnDef *>(class rvSpawnDef * const *,class rvSpawnDef * const *)
unsigned int __cdecl rvSpawnSortCompare<rvSpawnDef *>(rvSpawnDef *const *a, rvSpawnDef *const *b)
{
  return idStr::Icmp((*a)->nameString.data, (*b)->nameString.data);
}

// FUNC: public: void __thiscall idSessionLocal::SetMainMenuCrosshairVars(void)
void __thiscall idSessionLocal::SetMainMenuCrosshairVars(idSessionLocal *this)
{
  const idDecl *v1; // ebp
  const char *v2; // esi
  unsigned int v3; // eax
  int v4; // edi
  int v5; // eax
  char *data; // edx
  const char *v7; // ecx
  char v8; // al
  const idKeyValue *matched; // esi
  int *p_len; // esi
  int v11; // edi
  int v12; // eax
  char *v13; // ecx
  char *v14; // edx
  char v15; // al
  idUserInterface *guiMainMenu; // ecx
  idUserInterface_vtbl *v17; // edx
  const idMaterial *v18; // eax
  idStr newCrosshair; // [esp+30h] [ebp-4Ch] BYREF
  idStr currentCrosshair; // [esp+50h] [ebp-2Ch] BYREF
  int v22; // [esp+78h] [ebp-4h]

  v1 = declManager->FindType(declManager, 4, "player_marine_mp_ui", 0, 1);
  v2 = cvarSystem->GetCVarString(cvarSystem, "g_crosshairCustomFile");
  currentCrosshair.len = 0;
  currentCrosshair.alloced = 20;
  currentCrosshair.data = currentCrosshair.baseBuffer;
  currentCrosshair.baseBuffer[0] = 0;
  if ( v2 )
  {
    v3 = (unsigned int)&v2[strlen(v2) + 1];
    v4 = v3 - (_DWORD)(v2 + 1);
    v5 = v3 - (_DWORD)v2;
    if ( v5 > 20 )
      idStr::ReAllocate(&currentCrosshair, v5, 1);
    data = currentCrosshair.data;
    v7 = v2;
    do
    {
      v8 = *v7;
      *data++ = *v7++;
    }
    while ( v8 );
    currentCrosshair.len = v4;
  }
  v22 = 0;
  matched = idDict::MatchPrefix((idDict *)&v1[1], "mtr_crosshair", 0);
  if ( matched )
  {
    while ( idStr::Cmp(matched->value->data, currentCrosshair.data) )
    {
      matched = idDict::MatchPrefix((idDict *)&v1[1], "mtr_crosshair", matched);
      if ( !matched )
        goto LABEL_10;
    }
  }
  else
  {
LABEL_10:
    matched = idDict::MatchPrefix((idDict *)&v1[1], "mtr_crosshair", 0);
  }
  p_len = &matched->value->len;
  newCrosshair.data = newCrosshair.baseBuffer;
  newCrosshair.len = 0;
  newCrosshair.alloced = 20;
  newCrosshair.baseBuffer[0] = 0;
  v11 = *p_len;
  v12 = *p_len + 1;
  if ( v12 > 20 )
    idStr::ReAllocate(&newCrosshair, v12, 1);
  v13 = (char *)p_len[1];
  v14 = newCrosshair.data;
  do
  {
    v15 = *v13;
    *v14++ = *v13++;
  }
  while ( v15 );
  newCrosshair.len = v11;
  guiMainMenu = this->guiMainMenu;
  v17 = guiMainMenu->__vftable;
  LOBYTE(v22) = 1;
  v17->SetStateString(guiMainMenu, "crossImage", newCrosshair.data);
  v18 = declManager->FindMaterial(declManager, newCrosshair.data, 1);
  if ( v18 )
    v18->sort = -2.0;
  cvarSystem->SetCVarString(cvarSystem, "g_crosshairCustomFile", newCrosshair.data, 0);
  LOBYTE(v22) = 0;
  idStr::FreeData(&newCrosshair);
  v22 = -1;
  idStr::FreeData(&currentCrosshair);
}

// FUNC: public: void __thiscall idSessionLocal::SetMainMenuMPModelVars(void)
void __thiscall idSessionLocal::SetMainMenuMPModelVars(idSessionLocal *this)
{
  idSessionLocal *v1; // ebp
  const idDecl *v2; // edi
  int v3; // esi
  const char *v4; // eax
  const idKeyValue *Key; // eax
  const char *data; // edi
  int v7; // esi
  int v8; // eax
  char v9; // cl
  char *v10; // edx
  int v11; // esi
  int v12; // eax
  char v13; // cl
  char *v14; // edx
  int v15; // esi
  char v16; // cl
  int j; // eax
  char *v18; // edx
  const idDecl *v19; // eax
  const idKeyValue *v20; // eax
  const char *v21; // eax
  const char *v22; // eax
  const char *v23; // esi
  int v24; // edi
  char v25; // cl
  int m; // eax
  char *v27; // edx
  int v28; // esi
  char v29; // cl
  int k; // eax
  char *v31; // edx
  char v32; // cl
  int n; // eax
  char *v34; // edx
  const char *v35; // eax
  const idDecl *v36; // eax
  const idKeyValue *v37; // eax
  const char *v38; // eax
  idDict *v39; // esi
  const idKeyValue *v40; // eax
  const char *v41; // eax
  const idKeyValue *v42; // eax
  const char *v43; // eax
  const idKeyValue *v44; // eax
  const char *v45; // eax
  int i; // [esp+28h] [ebp-58h]
  const idDeclEntityDef *def; // [esp+2Ch] [ebp-54h]
  idStr buildNames; // [esp+34h] [ebp-4Ch] BYREF
  idStr buildValues; // [esp+54h] [ebp-2Ch] BYREF
  int v51; // [esp+7Ch] [ebp-4h]

  v1 = this;
  v2 = declManager->FindType(declManager, 4, "player_marine_mp_ui", 0, 1);
  def = (const idDeclEntityDef *)v2;
  if ( !v2 )
    goto LABEL_43;
  buildValues.len = 0;
  buildValues.alloced = 20;
  buildValues.data = buildValues.baseBuffer;
  buildValues.baseBuffer[0] = 0;
  v51 = 1;
  buildNames.len = 0;
  buildNames.alloced = 20;
  buildNames.data = buildNames.baseBuffer;
  buildNames.baseBuffer[0] = 0;
  v3 = 0;
  while ( 1 )
  {
    i = v3;
    v4 = va("def_model%d", v3);
    Key = idDict::FindKey((idDict *)&v2[1], v4);
    if ( !Key )
      break;
    data = Key->value->data;
    if ( !data || !*data )
    {
      v2 = def;
      break;
    }
    if ( v3 )
    {
      v7 = buildValues.len + 1;
      if ( buildValues.len + 2 > buildValues.alloced )
        idStr::ReAllocate(&buildValues, buildValues.len + 2, 1);
      v8 = 0;
      v9 = 59;
      do
      {
        v10 = &buildValues.data[v8++];
        v10[buildValues.len] = v9;
        v9 = asc_102A5CB4[v8];
      }
      while ( v9 );
      buildValues.len = v7;
      buildValues.data[v7] = 0;
      v11 = buildNames.len + 1;
      if ( buildNames.len + 2 > buildNames.alloced )
        idStr::ReAllocate(&buildNames, buildNames.len + 2, 1);
      v12 = 0;
      v13 = 59;
      do
      {
        v14 = &buildNames.data[v12++];
        v14[buildNames.len] = v13;
        v13 = asc_102A5CB4[v12];
      }
      while ( v13 );
      buildNames.len = v11;
      buildNames.data[v11] = 0;
    }
    v15 = strlen(data) + buildValues.len;
    if ( v15 + 1 > buildValues.alloced )
      idStr::ReAllocate(&buildValues, v15 + 1, 1);
    v16 = *data;
    for ( j = 0; v16; v16 = data[j] )
    {
      v18 = &buildValues.data[j++];
      v18[buildValues.len] = v16;
    }
    buildValues.len = v15;
    buildValues.data[v15] = 0;
    v19 = declManager->FindType(declManager, 4, data, 0, 1);
    if ( v19 )
    {
      v20 = idDict::FindKey((idDict *)&v19[1], "description");
      if ( v20 )
        v21 = v20->value->data;
      else
        v21 = &entityFilter;
      v22 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                            common.type,
                            v21,
                            -1);
      v23 = v22;
      if ( !v22 || !*v22 )
      {
        v28 = strlen(data) + buildNames.len;
        if ( v28 + 1 > buildNames.alloced )
          idStr::ReAllocate(&buildNames, v28 + 1, 1);
        v29 = *data;
        for ( k = 0; v29; v29 = data[k] )
        {
          v31 = &buildNames.data[k++];
          v31[buildNames.len] = v29;
        }
        goto LABEL_40;
      }
      v24 = strlen(v22) + buildNames.len;
      if ( v24 + 1 > buildNames.alloced )
        idStr::ReAllocate(&buildNames, v24 + 1, 1);
      v25 = *v23;
      for ( m = 0; v25; v25 = v23[m] )
      {
        v27 = &buildNames.data[m++];
        v27[buildNames.len] = v25;
      }
      v1 = this;
      buildNames.len = v24;
      buildNames.data[v24] = 0;
      v2 = def;
      v3 = i + 1;
    }
    else
    {
      v28 = strlen(data) + buildNames.len;
      if ( v28 + 1 > buildNames.alloced )
        idStr::ReAllocate(&buildNames, v28 + 1, 1);
      v32 = *data;
      for ( n = 0; v32; v32 = data[n] )
      {
        v34 = &buildNames.data[n++];
        v34[buildNames.len] = v32;
      }
LABEL_40:
      v1 = this;
      v2 = def;
      buildNames.len = v28;
      buildNames.data[v28] = 0;
      v3 = i + 1;
    }
  }
  v1->guiMainMenu->SetStateString(v1->guiMainMenu, "model_values", buildValues.data);
  v1->guiMainMenu->SetStateString(v1->guiMainMenu, "model_names", buildNames.data);
  v1->guiMainMenu->SetStateBool(v1->guiMainMenu, "player_model_updated", 1);
  LOBYTE(v51) = 0;
  idStr::FreeData(&buildNames);
  v51 = -1;
  idStr::FreeData(&buildValues);
LABEL_43:
  v35 = cvarSystem->GetCVarString(cvarSystem, "ui_model");
  v36 = declManager->FindType(declManager, 4, v35, 0, 1);
  if ( v36
    || ((v37 = idDict::FindKey((idDict *)&v2[1], "def_default_model")) == 0
      ? (v38 = &entityFilter)
      : (v38 = v37->value->data),
        (v36 = declManager->FindType(declManager, 4, v38, 0, 1)) != 0) )
  {
    v39 = (idDict *)&v36[1];
    v40 = idDict::FindKey((idDict *)&v36[1], "model");
    if ( v40 )
      v41 = v40->value->data;
    else
      v41 = &entityFilter;
    v1->guiMainMenu->SetStateString(v1->guiMainMenu, "player_model_name", v41);
    v42 = idDict::FindKey(v39, "def_head");
    if ( v42 )
      v43 = v42->value->data;
    else
      v43 = &entityFilter;
    v1->guiMainMenu->SetStateString(v1->guiMainMenu, "player_head_model_name", v43);
    v44 = idDict::FindKey(v39, "skin");
    if ( v44 )
      v45 = v44->value->data;
    else
      v45 = &entityFilter;
    v1->guiMainMenu->SetStateString(v1->guiMainMenu, "player_skin_name", v45);
    v1->guiMainMenu->SetStateBool(v1->guiMainMenu, "need_update", 1);
  }
}

// FUNC: public: virtual char const * __thiscall idSessionLocal::MessageBoxA(enum msgBoxType_t,char const *,char const *,bool,char const *,char const *,bool)
const char *__thiscall idSessionLocal::MessageBoxA(
        idSessionLocal *this,
        msgBoxType_t type,
        const char *message,
        const char *title,
        bool wait,
        char *fire_yes,
        char *fire_no,
        int network)
{
  const char *v9; // edx
  const char *v10; // ecx
  const char *v11; // eax
  const char *v12; // eax
  idUserInterface_vtbl *v13; // eax
  idUserInterface_vtbl *v14; // esi
  int v15; // eax
  idUserInterface_vtbl *v16; // esi
  int v17; // eax
  idUserInterface_vtbl *v18; // esi
  int v19; // eax
  idUserInterface_vtbl *v20; // esi
  int v21; // eax
  idUserInterface_vtbl *v22; // esi
  int v23; // eax
  idUserInterface_vtbl *v24; // esi
  int v25; // eax
  idUserInterface_vtbl *v26; // esi
  int v27; // eax
  idUserInterface_vtbl *v28; // esi
  int v29; // eax
  idUserInterface *guiMsg; // ecx
  char *v31; // eax
  char *v32; // eax
  idUserInterface *v33; // ecx
  bool v34; // zf
  int msgRetIndex; // eax
  idDict *v36; // eax
  const idKeyValue *v37; // eax
  const idPoolStr *value; // esi
  unsigned int len; // ebx
  int v40; // eax
  idDict *v42; // eax
  const idKeyValue *Key; // eax
  int v44; // [esp+38h] [ebp-10h]
  const char *v45; // [esp+38h] [ebp-10h]
  const char *v46; // [esp+38h] [ebp-10h]

  v9 = message;
  if ( !message )
    v9 = &entityFilter;
  v10 = title;
  if ( !title )
    v10 = &entityFilter;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
    common.type,
    "MessageBox: %s - %s\n",
    v10,
    v9);
  if ( !idSessionLocal::BoxDialogSanityCheck(this) )
    return 0;
  v11 = title;
  if ( !title )
    v11 = &entityFilter;
  this->guiMsg->SetStateString(this->guiMsg, "title", v11);
  v12 = message;
  if ( !message )
    v12 = &entityFilter;
  this->guiMsg->SetStateString(this->guiMsg, "message", v12);
  v13 = this->guiMsg->__vftable;
  if ( type == MSG_WAIT )
  {
    ((void (__stdcall *)(const char *, const char *, int))v13->SetStateString)("visible_msgbox", "0", v44);
    v45 = "1";
  }
  else
  {
    ((void (__stdcall *)(const char *, const char *, int))v13->SetStateString)("visible_msgbox", "1", v44);
    v45 = "0";
  }
  ((void (__thiscall *)(idUserInterface *, const char *))this->guiMsg->SetStateString)(this->guiMsg, "visible_waitbox");
  this->guiMsg->SetStateString(this->guiMsg, "visible_entry", "0");
  this->guiMsg->SetStateString(this->guiMsg, "visible_cdkey", "0");
  this->guiMsg->SetStateString(this->guiMsg, "visible_left", "0");
  this->guiMsg->SetStateString(this->guiMsg, "visible_right", "0");
  this->guiMsg->SetStateString(this->guiMsg, "visible_mid", "0");
  switch ( type )
  {
    case MSG_OK:
      v14 = this->guiMsg->__vftable;
      v15 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104339",
              -1);
      goto LABEL_17;
    case MSG_ABORT:
      v14 = this->guiMsg->__vftable;
      v15 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104340",
              -1);
LABEL_17:
      v14->SetStateString(this->guiMsg, "mid", (const char *)v15);
      this->guiMsg->SetStateString(this->guiMsg, "visible_mid", "1");
      this->guiMsg->SetStateString(this->guiMsg, "visible_left", "0");
      this->guiMsg->SetStateString(this->guiMsg, "visible_right", "0");
      this->guiMsg->HandleNamedEvent(this->guiMsg, "msgbox_FocusMid");
      break;
    case MSG_OKCANCEL:
      v16 = this->guiMsg->__vftable;
      v17 = (*(int (__thiscall **)(netadrtype_t, const char *, int, const char *))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104339",
              -1,
              v45);
      v16->SetStateString(this->guiMsg, "left", (const char *)v17);
      v46 = "#str_104340";
      goto LABEL_20;
    case MSG_YESNO:
      v18 = this->guiMsg->__vftable;
      v19 = (*(int (__thiscall **)(netadrtype_t, const char *, int, const char *))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104341",
              -1,
              v45);
      v18->SetStateString(this->guiMsg, "left", (const char *)v19);
      v46 = "#str_104342";
LABEL_20:
      v20 = this->guiMsg->__vftable;
      v21 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              v46,
              -1);
      v20->SetStateString(this->guiMsg, "right", (const char *)v21);
      this->guiMsg->SetStateString(this->guiMsg, "visible_mid", "0");
      this->guiMsg->SetStateString(this->guiMsg, "visible_left", "1");
      this->guiMsg->SetStateString(this->guiMsg, "visible_right", "1");
      this->guiMsg->HandleNamedEvent(this->guiMsg, "msgbox_FocusLeft");
      break;
    case MSG_PROMPT:
      v22 = this->guiMsg->__vftable;
      v23 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104339",
              -1);
      v22->SetStateString(this->guiMsg, "left", (const char *)v23);
      v24 = this->guiMsg->__vftable;
      v25 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104340",
              -1);
      v24->SetStateString(this->guiMsg, "right", (const char *)v25);
      this->guiMsg->SetStateString(this->guiMsg, "visible_mid", "0");
      this->guiMsg->SetStateString(this->guiMsg, "visible_left", "1");
      this->guiMsg->SetStateString(this->guiMsg, "visible_right", "1");
      this->guiMsg->SetStateString(this->guiMsg, "visible_entry", "1");
      this->guiMsg->HandleNamedEvent(this->guiMsg, "msgbox_FocusLeft");
      this->guiMsg->HandleNamedEvent(this->guiMsg, "Prompt");
      break;
    case MSG_CDKEY:
      v26 = this->guiMsg->__vftable;
      v27 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104339",
              -1);
      v26->SetStateString(this->guiMsg, "left", (const char *)v27);
      v28 = this->guiMsg->__vftable;
      v29 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
              common.type,
              "#str_104340",
              -1);
      v28->SetStateString(this->guiMsg, "right", (const char *)v29);
      this->guiMsg->SetStateString(this->guiMsg, "visible_left", "1");
      this->guiMsg->SetStateString(this->guiMsg, "visible_right", "1");
      this->guiMsg->SetStateString(this->guiMsg, "visible_mid", "0");
      this->guiMsg->SetStateString(this->guiMsg, "visible_cdkey", "1");
      guiMsg = this->guiMsg;
      if ( this->cdkey_state == CDKEY_OK )
        ((void (__thiscall *)(idUserInterface *, const char *, char *, const char *))guiMsg->SetStateString)(
          guiMsg,
          "str_cdkey",
          this->cdkey,
          v45);
      else
        ((void (__thiscall *)(idUserInterface *, const char *, const char *, const char *))guiMsg->SetStateString)(
          guiMsg,
          "str_cdkey",
          &entityFilter,
          v45);
      ((void (__thiscall *)(idUserInterface *, const char *))this->guiMsg->SetStateString)(
        this->guiMsg,
        "visible_cdchk");
      this->guiMsg->SetStateString(this->guiMsg, "str_cdchk", &entityFilter);
      this->guiMsg->HandleNamedEvent(this->guiMsg, "CDKey");
      break;
    case MSG_INFO:
      this->guiMsg->SetStateString(this->guiMsg, "mid", &entityFilter);
      this->guiMsg->SetStateString(this->guiMsg, "visible_mid", "0");
      this->guiMsg->SetStateString(this->guiMsg, "visible_left", "0");
      this->guiMsg->SetStateString(this->guiMsg, "visible_right", "0");
      break;
    case MSG_WAIT:
      break;
    default:
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
        common.type,
        "idSessionLocal::MessageBox: unknown msg box type\n");
      break;
  }
  v31 = fire_yes;
  if ( !fire_yes )
    v31 = (char *)&entityFilter;
  idStr::operator=(this->msgFireBack, v31);
  v32 = fire_no;
  if ( !fire_no )
    v32 = (char *)&entityFilter;
  idStr::operator=(&this->msgFireBack[1], v32);
  v33 = this->guiMsg;
  this->guiMsgRestore = this->guiActive;
  this->guiActive = v33;
  ((void (__thiscall *)(idUserInterface *, int, int))v33->SetCursor)(v33, 1134723072, 1133576192);
  this->guiActive->Activate(this->guiActive, 1, com_frameTime);
  this->msgRunning = 1;
  this->msgRetIndex = -1;
  if ( !wait )
    return 0;
  this->msgIgnoreButtons = 1;
  (*(void (__thiscall **)(netadrtype_t, int, int))(*(_DWORD *)common.type + 24))(common.type, 1, network);
  v34 = !this->msgRunning;
  this->msgIgnoreButtons = 0;
  if ( !v34 )
  {
    do
      (*(void (__thiscall **)(netadrtype_t, int, int))(*(_DWORD *)common.type + 24))(common.type, 1, network);
    while ( this->msgRunning );
  }
  msgRetIndex = this->msgRetIndex;
  if ( msgRetIndex < 0 )
    return 0;
  if ( type != MSG_PROMPT )
  {
    if ( type != MSG_CDKEY )
      return this->msgFireBack[msgRetIndex].data;
    if ( !msgRetIndex )
    {
      v42 = (idDict *)this->guiMsg->State(this->guiMsg);
      Key = idDict::FindKey(v42, "str_cdkey");
      if ( Key )
        return Key->value->data;
      else
        return &entityFilter;
    }
    return 0;
  }
  if ( msgRetIndex )
    return 0;
  v36 = (idDict *)this->guiMsg->State(this->guiMsg);
  v37 = idDict::FindKey(v36, "str_entry");
  if ( v37 )
  {
    value = v37->value;
    len = value->len;
    v40 = value->len + 1;
    if ( v40 > this->msgFireBack[0].alloced )
      idStr::ReAllocate(this->msgFireBack, v40, 0);
    qmemcpy(this->msgFireBack[0].data, value->data, len);
    this->msgFireBack[0].data[len] = 0;
    this->msgFireBack[0].len = len;
    return this->msgFireBack[0].data;
  }
  else
  {
    idStr::operator=(this->msgFireBack, (char *)&entityFilter);
    return this->msgFireBack[0].data;
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::DownloadProgressBox(struct backgroundDownload_s *,char const *,int,int)
void __thiscall idSessionLocal::DownloadProgressBox(
        idSessionLocal *this,
        backgroundDownload_s *bgl,
        const char *title,
        int progress_start,
        int progress_end)
{
  int dltotal; // edi
  idUserInterface *guiMsg; // ecx
  backgroundDownload_s *v8; // ecx
  int v9; // esi
  idUserInterface_vtbl *v10; // esi
  char *v11; // eax
  int len; // esi
  idUserInterface *v13; // edx
  float v14; // [esp+58h] [ebp-E0h]
  int dlnow; // [esp+70h] [ebp-C8h]
  int lapsed; // [esp+74h] [ebp-C4h]
  float value; // [esp+78h] [ebp-C0h]
  float v18; // [esp+7Ch] [ebp-BCh]
  int startTime; // [esp+84h] [ebp-B4h]
  idStr sMsg; // [esp+88h] [ebp-B0h] BYREF
  idStr sNow; // [esp+A8h] [ebp-90h] BYREF
  idStr sBW; // [esp+C8h] [ebp-70h] BYREF
  idStr sTotal; // [esp+E8h] [ebp-50h] BYREF
  idStr sETA; // [esp+108h] [ebp-30h] BYREF
  int v25; // [esp+134h] [ebp-4h]

  dlnow = 0;
  dltotal = 0;
  startTime = Sys_Milliseconds();
  sNow.len = 0;
  sNow.alloced = 20;
  sNow.data = sNow.baseBuffer;
  sNow.baseBuffer[0] = 0;
  v25 = 4;
  sTotal.len = 0;
  sTotal.alloced = 20;
  sTotal.data = sTotal.baseBuffer;
  sTotal.baseBuffer[0] = 0;
  sBW.len = 0;
  sBW.alloced = 20;
  sBW.data = sBW.baseBuffer;
  sBW.baseBuffer[0] = 0;
  sETA.len = 0;
  sETA.alloced = 20;
  sETA.data = sETA.baseBuffer;
  sETA.baseBuffer[0] = 0;
  sMsg.alloced = 20;
  sMsg.len = 0;
  sMsg.data = sMsg.baseBuffer;
  sMsg.baseBuffer[0] = 0;
  if ( idSessionLocal::BoxDialogSanityCheck(this) )
  {
    this->guiMsg->SetStateString(this->guiMsg, "visible_msgbox", "1");
    this->guiMsg->SetStateString(this->guiMsg, "visible_waitbox", "0");
    this->guiMsg->SetStateString(this->guiMsg, "visible_entry", "0");
    this->guiMsg->SetStateString(this->guiMsg, "visible_cdkey", "0");
    this->guiMsg->SetStateString(this->guiMsg, "mid", "Cancel");
    this->guiMsg->SetStateString(this->guiMsg, "visible_mid", "1");
    this->guiMsg->SetStateString(this->guiMsg, "visible_left", "0");
    this->guiMsg->SetStateString(this->guiMsg, "visible_right", "0");
    this->guiMsg->SetStateString(this->guiMsg, "title", title);
    this->guiMsg->SetStateString(this->guiMsg, "message", "Connecting..");
    guiMsg = this->guiMsg;
    this->guiMsgRestore = this->guiActive;
    this->guiActive = guiMsg;
LABEL_3:
    this->msgRunning = 1;
    while ( 1 )
    {
      (*(void (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 24))(common.type, 1, 0);
      v8 = bgl;
      if ( bgl->completed )
        break;
      if ( bgl->url.dltotal != dltotal || bgl->url.dlnow != dlnow )
      {
        dltotal = bgl->url.dltotal;
        dlnow = bgl->url.dlnow;
        v9 = Sys_Milliseconds() - startTime;
        value = (float)dlnow;
        idStr::BestUnit(&sNow, "%.2f", value, MEASURE_SIZE);
        if ( v9 <= 2000 )
        {
          idStr::operator=(&sBW, "-- KB/s");
        }
        else
        {
          v14 = value * 1000.0 / (double)v9;
          idStr::BestUnit(&sBW, "%.1f", v14, MEASURE_BANDWIDTH);
        }
        if ( dltotal )
        {
          v18 = (float)dltotal;
          idStr::BestUnit(&sTotal, "%.2f", v18, MEASURE_SIZE);
          if ( v9 >= 2000 )
          {
            sprintf(&sETA, "%.0f sec", (v18 / value - 1.0) * (double)v9 * 0.001);
            sprintf(&sMsg, "%s / %s ( %s - %s )", sNow.data, sTotal.data, sBW.data, sETA.data);
          }
          else
          {
            sprintf(&sMsg, "%s / %s", sNow.data, sTotal.data);
          }
          v10 = this->guiMsg->__vftable;
          v11 = va("%d", progress_start + dlnow * (progress_end - progress_start) / dltotal);
          v10->SetStateString(this->guiMsg, "progress", v11);
        }
        else
        {
          if ( v9 >= 2000 )
          {
            sprintf(&sMsg, "%s - %s", sNow.data, sBW.data);
          }
          else
          {
            len = sNow.len;
            lapsed = sNow.len;
            if ( sNow.len + 1 > sMsg.alloced )
              idStr::ReAllocate(&sMsg, sNow.len + 1, 0);
            qmemcpy(sMsg.data, sNow.data, len);
            sMsg.data[lapsed] = 0;
            sMsg.len = lapsed;
          }
          this->guiMsg->SetStateString(this->guiMsg, "progress", "0");
        }
        this->guiMsg->SetStateString(this->guiMsg, "message", sMsg.data);
        v8 = bgl;
      }
      if ( !this->msgRunning )
      {
        v8->url.status = DL_ABORTING;
        this->guiMsg->SetStateString(this->guiMsg, "title", "Aborting..");
        this->guiMsg->SetStateString(this->guiMsg, "visible_mid", "0");
        v13 = this->guiMsg;
        this->guiMsgRestore = this->guiActive;
        this->guiActive = v13;
        goto LABEL_3;
      }
    }
    this->guiActive = this->guiMsgRestore;
    this->guiMsgRestore = 0;
  }
  LOBYTE(v25) = 3;
  idStr::FreeData(&sMsg);
  LOBYTE(v25) = 2;
  idStr::FreeData(&sETA);
  LOBYTE(v25) = 1;
  idStr::FreeData(&sBW);
  LOBYTE(v25) = 0;
  idStr::FreeData(&sTotal);
  v25 = -1;
  idStr::FreeData(&sNow);
}

// FUNC: public: virtual void __thiscall idSessionLocal::StopBox(void)
void __thiscall idSessionLocal::StopBox(idSessionLocal *this)
{
  if ( this->guiActive == this->guiMsg )
    idSessionLocal::HandleMsgCommands(this, "stop");
}

// FUNC: void __cdecl ParseChoicesIntoList(class idUserInterface *,class idStr &,bool,char const *)
void __cdecl ParseChoicesIntoList(idUserInterface *GUI, idStr *Choices, bool AllowEmptyVal, const char *ListName)
{
  int v4; // edi
  idUserInterface *v5; // esi
  idUserInterface_vtbl *v6; // ebp
  char *v7; // eax
  int v8; // esi
  int v9; // eax
  char v10; // cl
  char *v11; // edx
  int v12; // esi
  int i; // eax
  char v14; // cl
  char *v15; // edx
  int v16; // esi
  int v17; // eax
  char v18; // cl
  char *v19; // edx
  idUserInterface_vtbl *v20; // ebp
  char *v21; // eax
  char *v22; // [esp-10h] [ebp-174h]
  char *v23; // [esp-10h] [ebp-174h]
  bool negNum; // [esp+7h] [ebp-15Dh]
  idStr str2; // [esp+8h] [ebp-15Ch] BYREF
  idStr str3; // [esp+28h] [ebp-13Ch] BYREF
  idToken token; // [esp+48h] [ebp-11Ch] BYREF
  idParser src; // [esp+98h] [ebp-CCh] BYREF
  int v29; // [esp+160h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v29 = 2;
  str2.len = 0;
  str2.alloced = 20;
  str2.data = str2.baseBuffer;
  str2.baseBuffer[0] = 0;
  str3.alloced = 20;
  str3.len = 0;
  str3.data = str3.baseBuffer;
  str3.baseBuffer[0] = 0;
  idParser::idParser(&src);
  LOBYTE(v29) = 3;
  v4 = 0;
  idParser::FreeSource(&src, 0);
  idParser::SetFlags(&src, 6272);
  idParser::LoadMemory(&src, Choices->data, Choices->len, "<ChoiceVals>");
  idStr::operator=(&str2, (char *)&entityFilter);
  negNum = 0;
  if ( src.loaded )
  {
    v5 = GUI;
    while ( idParser::ReadToken(&src, &token) )
    {
      if ( idStr::Cmp(token.data, "-") )
      {
        if ( idStr::Cmp(token.data, ";") )
        {
          if ( negNum )
          {
            v8 = str2.len + 1;
            if ( str2.len + 2 > str2.alloced )
              idStr::ReAllocate(&str2, str2.len + 2, 1);
            v9 = 0;
            v10 = 45;
            do
            {
              v11 = &str2.data[v9++];
              v11[str2.len] = v10;
              v10 = asc_1029DD84[v9];
            }
            while ( v10 );
            str2.len = v8;
            str2.data[v8] = 0;
            negNum = 0;
          }
          v12 = str2.len + token.len;
          if ( str2.len + token.len + 1 > str2.alloced )
            idStr::ReAllocate(&str2, str2.len + token.len + 1, 1);
          for ( i = 0; i < token.len; v15[str2.len] = v14 )
          {
            v14 = token.data[i];
            v15 = &str2.data[i++];
          }
          str2.len = v12;
          str2.data[v12] = 0;
          v16 = str2.len + 1;
          if ( str2.len + 2 > str2.alloced )
            idStr::ReAllocate(&str2, str2.len + 2, 1);
          v17 = 0;
          v18 = 32;
          do
          {
            v19 = &str2.data[v17++];
            v19[str2.len] = v18;
            v18 = ::src[v17];
          }
          while ( v18 );
          str2.len = v16;
          str2.data[v16] = 0;
          v5 = GUI;
        }
        else if ( str2.len || AllowEmptyVal )
        {
          idStr::StripTrailingWhitespace(&str2);
          v6 = v5->__vftable;
          v22 = va("%s", str2.data);
          v7 = va("%s_item_%i", ListName, v4);
          v6->SetStateString(v5, v7, v22);
          ++v4;
          idStr::operator=(&str2, (char *)&entityFilter);
        }
      }
      else
      {
        negNum = 1;
      }
    }
    if ( str2.len || AllowEmptyVal )
    {
      idStr::StripTrailingWhitespace(&str2);
      v20 = v5->__vftable;
      v23 = va("%s", str2.data);
      v21 = va("%s_item_%i", ListName, v4);
      v20->SetStateString(v5, v21, v23);
    }
  }
  LOBYTE(v29) = 2;
  idParser::~idParser(&src);
  LOBYTE(v29) = 1;
  idStr::FreeData(&str3);
  LOBYTE(v29) = 0;
  idStr::FreeData(&str2);
  v29 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: void __thiscall idSessionLocal::SaveNote(char const *)
void __userpurge idSessionLocal::SaveNote(idSessionLocal *this@<ecx>, int a2@<ebx>, int a3@<esi>, char *overwriteName)
{
  idGame_vtbl *v5; // eax
  const idKeyValue *Key; // eax
  const char *data; // esi
  int v8; // ebx
  char v9; // cl
  int i; // eax
  char *v11; // edx
  const idStr *v12; // eax
  const idStr *v13; // esi
  idCVarSystem_vtbl *v14; // edx
  const char *v15; // eax
  const idStr *v16; // eax
  const idStr *v17; // esi
  const char *v18; // eax
  const idStr *v19; // eax
  idStr *v20; // esi
  unsigned int len; // ebx
  int v22; // eax
  int j; // ebx
  int v24; // ebp
  const char *v25; // eax
  const char *v26; // esi
  int v27; // edi
  char v28; // cl
  int k; // eax
  char *v30; // edx
  int v31; // ebp
  const tm *v32; // eax
  char *v33; // eax
  idDict *v34; // eax
  const idKeyValue *v35; // eax
  const char *v36; // eax
  bool v37; // bl
  idDict *v38; // eax
  const idKeyValue *v39; // eax
  char *v40; // eax
  idFile *v41; // esi
  idDict *v42; // eax
  idDict *v43; // eax
  const char *v44; // eax
  idDict *v45; // eax
  const idKeyValue *v46; // eax
  const char *v47; // edi
  idUserInterface *guiActive; // ecx
  idUserInterface_vtbl *v49; // edx
  idDict *v50; // eax
  const idKeyValue *v51; // eax
  const char *value; // esi
  idGame_vtbl *v53; // eax
  int v54; // ebx
  const char *v55; // eax
  const char *v56; // eax
  char *v57; // eax
  idUserInterface *v58; // esi
  idRenderSystem_vtbl *v59; // edi
  int v60; // eax
  int v61; // eax
  const char *v62; // [esp+54h] [ebp-1C8h]
  const char *v63; // [esp+58h] [ebp-1C4h]
  const char *v64; // [esp+58h] [ebp-1C4h]
  int v65; // [esp+5Ch] [ebp-1C0h]
  const char *v66; // [esp+5Ch] [ebp-1C0h]
  const char *v67; // [esp+60h] [ebp-1BCh]
  const char *v68; // [esp+64h] [ebp-1B8h]
  const char *v69; // [esp+68h] [ebp-1B4h]
  const char *v70; // [esp+6Ch] [ebp-1B0h]
  const char *v72; // [esp+70h] [ebp-1ACh]
  const char *v74; // [esp+88h] [ebp-194h]
  int v75; // [esp+8Ch] [ebp-190h]
  const char *saveGShowHud; // [esp+90h] [ebp-18Ch]
  BOOL saveConNoPrint; // [esp+94h] [ebp-188h]
  idStr fileName; // [esp+98h] [ebp-184h] BYREF
  idStr tempFileName; // [esp+B8h] [ebp-164h] BYREF
  idStr mapName; // [esp+D8h] [ebp-144h] BYREF
  int aclock; // [esp+F8h] [ebp-124h] BYREF
  int ltime; // [esp+FCh] [ebp-120h] BYREF
  idStr timestr; // [esp+100h] [ebp-11Ch] BYREF
  idStr comments; // [esp+120h] [ebp-FCh] BYREF
  idVec3 origin; // [esp+140h] [ebp-DCh] BYREF
  idVec3 v86; // [esp+14Ch] [ebp-D0h] BYREF
  int v87; // [esp+16Ch] [ebp-B0h] BYREF
  idStr v88; // [esp+174h] [ebp-A8h] BYREF
  idStr result; // [esp+194h] [ebp-88h] BYREF
  idStr v90; // [esp+1B4h] [ebp-68h] BYREF
  idStr v91; // [esp+1D4h] [ebp-48h] BYREF
  idMat3 v92; // [esp+1F8h] [ebp-24h] BYREF

  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  v92.mat[2].z = 0.0;
  mapName.len = 0;
  mapName.alloced = 20;
  mapName.data = mapName.baseBuffer;
  mapName.baseBuffer[0] = 0;
  timestr.len = 0;
  timestr.alloced = 20;
  timestr.data = timestr.baseBuffer;
  timestr.baseBuffer[0] = 0;
  comments.len = 0;
  comments.alloced = 20;
  comments.data = comments.baseBuffer;
  comments.baseBuffer[0] = 0;
  v5 = game->__vftable;
  LOBYTE(v92.mat[2].z) = 3;
  if ( !v5->GetPlayerInfo(game, &origin, (idMat3 *)&v91.baseBuffer[12], -1, 0, -1) )
  {
    LOBYTE(v92.mat[2].z) = 2;
    idStr::FreeData(&comments);
    LOBYTE(v92.mat[2].z) = 1;
    idStr::FreeData(&timestr);
    LOBYTE(v92.mat[2].z) = 0;
    idStr::FreeData(&mapName);
    v92.mat[2].z = NAN;
    idStr::FreeData(&fileName);
    return;
  }
  time(&ltime);
  Key = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_map");
  if ( !Key )
  {
    data = &entityFilter;
    goto LABEL_5;
  }
  data = Key->value->data;
  if ( data )
  {
LABEL_5:
    v8 = strlen(data) + mapName.len;
    if ( v8 + 1 > mapName.alloced )
      idStr::ReAllocate(&mapName, v8 + 1, 1);
    v9 = *data;
    for ( i = 0; v9; v9 = data[i] )
    {
      v11 = &mapName.data[i++];
      v11[mapName.len] = v9;
    }
    mapName.len = v8;
    mapName.data[v8] = 0;
  }
  idStr::StripFileExtension(&mapName);
  if ( overwriteName )
  {
    idStr::operator=(&fileName, overwriteName);
  }
  else
  {
    v12 = operator+((idStr *)&result.baseBuffer[12], "viewnotes/", &mapName);
    LOBYTE(v92.mat[2].z) = 4;
    v13 = operator+((idStr *)&v87, v12, "/");
    v14 = cvarSystem->__vftable;
    LOBYTE(v92.mat[2].z) = 5;
    v15 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, int, int))v14->GetCVarString)(
                          cvarSystem,
                          "win_username",
                          a3,
                          a2);
    v16 = operator+(&v91, v13, v15);
    v17 = operator+((idStr *)&v86.z, v16, "-");
    v18 = va("%lx", timestr.data);
    v19 = operator+(&result, v17, v18);
    v20 = operator+((idStr *)&tempFileName.alloced, v19, ".txt");
    len = v20->len;
    v22 = v20->len + 1;
    if ( v22 > *(int *)&fileName.baseBuffer[4] )
      idStr::ReAllocate((idStr *)&fileName.alloced, v22, 0);
    qmemcpy(*(void **)fileName.baseBuffer, v20->data, len);
    *(_BYTE *)(*(_DWORD *)fileName.baseBuffer + len) = 0;
    fileName.alloced = len;
    idStr::FreeData((idStr *)&tempFileName.alloced);
    idStr::FreeData(&result);
    idStr::FreeData((idStr *)&v86.z);
    idStr::FreeData(&v91);
    idStr::FreeData(&v88);
    idStr::FreeData(&v90);
    a2 = 0;
    a3 = 0;
    if ( ((int (__thiscall *)(idFileSystem *, _DWORD))fileSystem->ReadFile)(fileSystem, *(_DWORD *)fileName.baseBuffer) != -1 )
    {
      for ( j = 1; ; ++j )
      {
        tempFileName.len = 0;
        tempFileName.alloced = 20;
        tempFileName.data = tempFileName.baseBuffer;
        tempFileName.baseBuffer[0] = 0;
        v24 = fileName.len;
        LOBYTE(v92.mat[2].z) = 10;
        if ( fileName.len + 1 > 20 )
          idStr::ReAllocate(&tempFileName, fileName.len + 1, 0);
        qmemcpy(tempFileName.data, fileName.data, v24);
        tempFileName.data[v24] = 0;
        tempFileName.len = v24;
        idStr::StripFileExtension(&tempFileName);
        v25 = va("-%u.txt", j);
        v26 = v25;
        if ( v25 )
        {
          v27 = strlen(v25) + tempFileName.len;
          if ( v27 + 1 > tempFileName.alloced )
            idStr::ReAllocate(&tempFileName, v27 + 1, 1);
          v28 = *v26;
          for ( k = 0; v28; v28 = v26[k] )
          {
            v30 = &tempFileName.data[k++];
            v30[tempFileName.len] = v28;
          }
          tempFileName.len = v27;
          tempFileName.data[v27] = 0;
        }
        if ( fileSystem->ReadFile(fileSystem, tempFileName.data, 0, 0) == -1 )
        {
          v31 = tempFileName.len;
          if ( tempFileName.len + 1 > fileName.alloced )
            idStr::ReAllocate(&fileName, tempFileName.len + 1, 0);
          qmemcpy(fileName.data, tempFileName.data, v31);
          fileName.data[v31] = 0;
          fileName.len = v31;
        }
        LOBYTE(v92.mat[2].z) = 3;
        idStr::FreeData(&tempFileName);
      }
    }
  }
  time(&aclock);
  v32 = localtime(&aclock);
  v33 = asctime(v32);
  idStr::operator=(&timestr, v33);
  idStr::Replace(&timestr, "\n", &entityFilter);
  v34 = (idDict *)((int (__thiscall *)(idUserInterface *, int, int))this->guiActive->State)(this->guiActive, a3, a2);
  v35 = idDict::FindKey(v34, "completed");
  if ( v35 )
    v36 = v35->value->data;
  else
    v36 = &entityFilter;
  v37 = idStr::Cmp(v36, &entityFilter) != 0;
  HIBYTE(v75) = v37;
  v38 = (idDict *)this->guiActive->State(this->guiActive);
  v39 = idDict::FindKey(v38, "note");
  if ( v39 )
    v40 = v39->value->data;
  else
    v40 = (char *)&entityFilter;
  idStr::operator=((idStr *)&comments.alloced, v40);
  idStr::ReplaceChar((idStr *)&comments.alloced, 34, 39);
  v41 = fileSystem->OpenFileWrite(fileSystem, *(_DWORD *)fileName.baseBuffer, "fs_cdpath", 0);
  if ( v41 )
  {
    v42 = (idDict *)this->guiActive->State(this->guiActive);
    idDict::FindKey(v42, "assignedTo");
    v43 = (idDict *)this->guiActive->State(this->guiActive);
    idDict::FindKey(v43, "category");
    v65 = ((int (__thiscall *)(idCVarSystem *, const char *, _DWORD))cvarSystem->GetCVarString)(
            cvarSystem,
            "win_username",
            *(_DWORD *)timestr.baseBuffer);
    v63 = idMat3::ToString(&v92, 2);
    v44 = idVec3::ToString(&v86, 2);
    (*(void (**)(idFile *, const char *, ...))(v75 + 56))(
      v41,
      "\"view\"\t( %s )\t( %s )\r\n"
      "\"user\"\t\"%s\"\r\n"
      "\"date\"\t\"%s\"\r\n"
      "\"version\"\t\"%s\"\r\n"
      "\"category\"\t\"%s\"\r\n"
      "\"assigned_to\"\t\"%s\"\r\n"
      "\"completed\"\t\"%s\"\r\n"
      "\"map\"\t\"%s\"\r\n"
      "\"comments\"\t\"%s\"\r\n",
      v44,
      v63,
      v65);
    fileSystem->CloseFile(fileSystem, v41);
  }
  v74 = ", Completed";
  if ( !v37 )
    v74 = &entityFilter;
  v45 = (idDict *)this->guiActive->State(this->guiActive);
  v46 = idDict::FindKey(v45, "assignedTo");
  if ( v46 )
    v47 = v46->value->data;
  else
    v47 = &entityFilter;
  guiActive = this->guiActive;
  v49 = guiActive->__vftable;
  fileName.len = *(_DWORD *)mapName.baseBuffer;
  v50 = (idDict *)v49->State(guiActive);
  v51 = idDict::FindKey(v50, "category");
  if ( v51 )
    saveGShowHud = v51->value->data;
  else
    saveGShowHud = &entityFilter;
  value = com_version.internalVar->value;
  v53 = game->__vftable;
  v54 = *(_DWORD *)timestr.baseBuffer;
  fileName.data = *(char **)fileName.baseBuffer;
  saveConNoPrint = (BOOL)v53;
  v55 = idVec3::ToString((idVec3 *)&origin.z, 2);
  v56 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, int, const char *, const char *, const char *, int, const char *, const char *))cvarSystem->GetCVarString)(
                        cvarSystem,
                        "win_username",
                        v54,
                        value,
                        saveGShowHud,
                        v74,
                        fileName.len,
                        v55,
                        v47);
  v57 = va(
          "File: %s\n"
          "Submitter: %s\n"
          "Date: %s\n"
          "Version: %s\n"
          "Category: %s%s\n"
          "Location: %s  :  %s\n"
          "Assigned To: %s\n"
          "Note: %s\n",
          (const char *)fileName.len,
          v56,
          v62,
          v64,
          v66,
          v67,
          v68,
          v69,
          v70,
          v72);
  (*((void (__thiscall **)(idGame *, char *))saveGShowHud + 57))(game, v57);
  idStr::SetFileExtension(&fileName, ".jpg");
  v58 = this->guiActive;
  this->guiActive = 0;
  LOBYTE(saveConNoPrint) = cvarSystem->GetCVarBool(cvarSystem, "con_noPrint");
  LOBYTE(saveGShowHud) = cvarSystem->GetCVarBool(cvarSystem, "g_showhud");
  cvarSystem->SetCVarBool(cvarSystem, "con_noPrint", 1, 0);
  cvarSystem->SetCVarBool(cvarSystem, "g_showhud", 1, 0);
  this->UpdateScreen(this, 1);
  v59 = renderSystem->__vftable;
  v60 = ((int (__thiscall *)(idRenderSystem *, char *, int, _DWORD, const char *))renderSystem->GetScreenHeight)(
          renderSystem,
          fileName.data,
          1,
          0,
          "fs_cdpath");
  v61 = ((int (__thiscall *)(idRenderSystem *, int))renderSystem->GetScreenWidth)(renderSystem, v60);
  ((void (__thiscall *)(idRenderSystem *, int))v59->TakeJPGScreenshot)(renderSystem, v61);
  cvarSystem->SetCVarBool(cvarSystem, "con_noPrint", saveConNoPrint, 0);
  cvarSystem->SetCVarBool(cvarSystem, "g_showhud", (const bool)saveGShowHud, 0);
  game->SetViewComments(game, 0);
  this->guiActive = v58;
  LOBYTE(v92.mat[2].z) = 2;
  idStr::FreeData(&comments);
  LOBYTE(v92.mat[2].z) = 1;
  idStr::FreeData(&timestr);
  LOBYTE(v92.mat[2].z) = 0;
  idStr::FreeData(&mapName);
  v92.mat[2].z = NAN;
  idStr::FreeData(&fileName);
}

// FUNC: public: bool __thiscall idSessionLocal::ReadNoteFile(char const *,class idVec3 &,class idMat3 &,class idStr &,class idStr &,class idStr &,class idStr &,class idStr &,bool &,class idStr &)
char __thiscall idSessionLocal::ReadNoteFile(
        idSessionLocal *this,
        const char *fileName,
        idVec3 *origin,
        idMat3 *axis,
        idStr *user,
        idStr *date,
        idStr *version,
        idStr *category,
        idStr *assignedTo,
        bool *completed,
        idStr *comments)
{
  idStr *v11; // edi
  idStr *v12; // esi
  int v14; // eax
  int len; // ebp
  int v16; // ebp
  int v17; // ebp
  int v18; // ebp
  int v19; // ebp
  int v20; // ebp
  idToken token; // [esp+Ch] [ebp-124h] BYREF
  idLexer parser; // [esp+5Ch] [ebp-D4h] BYREF
  int v23; // [esp+12Ch] [ebp-4h]

  idLexer::idLexer(&parser, 156);
  token.floatvalue = 0.0;
  v23 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v11 = assignedTo;
  *completed = 0;
  LOBYTE(v23) = 1;
  idStr::operator=(assignedTo, (char *)&entityFilter);
  v12 = category;
  idStr::operator=(category, (char *)&entityFilter);
  idStr::operator=(version, (char *)&entityFilter);
  idStr::operator=(date, (char *)&entityFilter);
  idStr::operator=(user, (char *)&entityFilter);
  if ( idLexer::LoadFile(&parser, fileName, 0) )
  {
    if ( !idLexer::ReadToken(&parser, &token) )
    {
LABEL_3:
      LOBYTE(v23) = 0;
      idStr::FreeData(&token);
      v23 = -1;
      idLexer::~idLexer(&parser);
      return 1;
    }
    while ( 1 )
    {
      if ( idStr::Cmp(token.data, "view") )
      {
        if ( !idStr::Cmp(token.data, "user") )
        {
          if ( !idLexer::ReadToken(&parser, &token) )
            break;
          len = token.len;
          if ( token.len + 1 > user->alloced )
            idStr::ReAllocate(user, token.len + 1, 0);
          qmemcpy(user->data, token.data, len);
          user->data[len] = 0;
          user->len = len;
          goto LABEL_44;
        }
        if ( !idStr::Cmp(token.data, aDate_0) )
        {
          if ( !idLexer::ReadToken(&parser, &token) )
            break;
          v16 = token.len;
          if ( token.len + 1 > date->alloced )
            idStr::ReAllocate(date, token.len + 1, 0);
          qmemcpy(date->data, token.data, v16);
          date->data[v16] = 0;
          date->len = v16;
          goto LABEL_44;
        }
        if ( !idStr::Cmp(token.data, "version") )
        {
          if ( !idLexer::ReadToken(&parser, &token) )
            break;
          v17 = token.len;
          if ( token.len + 1 > version->alloced )
            idStr::ReAllocate(version, token.len + 1, 0);
          qmemcpy(version->data, token.data, v17);
          version->data[v17] = 0;
          version->len = v17;
          goto LABEL_44;
        }
        if ( !idStr::Cmp(token.data, "category") )
        {
          if ( !idLexer::ReadToken(&parser, &token) )
            break;
          v18 = token.len;
          if ( token.len + 1 > v12->alloced )
            idStr::ReAllocate(v12, token.len + 1, 0);
          qmemcpy(category->data, token.data, v18);
          category->data[v18] = 0;
          category->len = v18;
          goto LABEL_44;
        }
        if ( !idStr::Cmp(token.data, "assigned_to") )
        {
          if ( !idLexer::ReadToken(&parser, &token) )
            break;
          v19 = token.len;
          if ( token.len + 1 > v11->alloced )
            idStr::ReAllocate(v11, token.len + 1, 0);
          qmemcpy(v11->data, token.data, v19);
          assignedTo->data[v19] = 0;
          assignedTo->len = v19;
          goto LABEL_44;
        }
        if ( !idStr::Cmp(token.data, "comments") )
        {
          if ( !idLexer::ReadToken(&parser, &token) )
            break;
          v20 = token.len;
          if ( token.len + 1 > comments->alloced )
            idStr::ReAllocate(comments, token.len + 1, 0);
          qmemcpy(comments->data, token.data, v20);
          comments->data[v20] = 0;
          comments->len = v20;
          goto LABEL_44;
        }
        if ( !idStr::Cmp(token.data, "completed") )
        {
          if ( !idLexer::ReadToken(&parser, &token) )
            break;
          *completed = idStr::Cmp(token.data, "yes") == 0;
          goto LABEL_44;
        }
        if ( idStr::Cmp(token.data, "map") )
          break;
        v14 = idLexer::ReadToken(&parser, &token);
      }
      else
      {
        if ( !idLexer::Parse1DMatrix(&parser, 3, &origin->x) )
          break;
        v14 = idLexer::Parse1DMatrix(&parser, 9, (float *)axis);
      }
      if ( !v14 )
        break;
LABEL_44:
      if ( !idLexer::ReadToken(&parser, &token) )
        goto LABEL_3;
      v11 = assignedTo;
      v12 = category;
    }
  }
  LOBYTE(v23) = 0;
  idStr::FreeData(&token);
  v23 = -1;
  idLexer::~idLexer(&parser);
  return 0;
}

// FUNC: public: void __thiscall idSessionLocal::HandleEditCVarCommands(char const *)
void __thiscall idSessionLocal::HandleEditCVarCommands(idSessionLocal *this, const char *menuCommand)
{
  idDict *v3; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax

  if ( this->mapSpawned )
  {
    if ( idStr::Icmp(menuCommand, "init") )
    {
      if ( idStr::Icmp(menuCommand, "SelectGame") )
      {
        if ( idStr::Icmp(menuCommand, "SelectPhysics") )
        {
          if ( idStr::Icmp(menuCommand, "SelectRenderer") )
          {
            if ( idStr::Icmp(menuCommand, "SelectSound") )
            {
              if ( idStr::Icmp(menuCommand, "SelectAI") )
              {
                if ( !idStr::Icmp(menuCommand, "close") )
                {
                  this->guiActive = 0;
                  idKeyInput::ClearStates();
                }
              }
              else
              {
                idSessionLocal::PopulateEditCVarGUI(this, CVARHELP_AI);
              }
            }
            else
            {
              idSessionLocal::PopulateEditCVarGUI(this, CVARHELP_SOUND);
            }
          }
          else
          {
            idSessionLocal::PopulateEditCVarGUI(this, CVARHELP_RENDERER);
          }
        }
        else
        {
          idSessionLocal::PopulateEditCVarGUI(this, CVARHELP_PHYSICS);
        }
      }
      else
      {
        idSessionLocal::PopulateEditCVarGUI(this, CVARHELP_GAME);
      }
    }
    else
    {
      v3 = (idDict *)this->guiActive->State(this->guiActive);
      Key = idDict::FindKey(v3, "init");
      if ( Key )
        data = Key->value->data;
      else
        data = "0";
      if ( !atoi(data) )
      {
        this->guiActive->SetStateInt(this->guiActive, "init", 1);
        this->guiActive->HandleNamedEvent(this->guiActive, "ActivateGame");
        idSessionLocal::DispatchCommand(this, this->guiActive, "SelectGame", 0);
      }
    }
  }
  else
  {
    this->guiActive = 0;
  }
}

// FUNC: public: void __thiscall idSessionLocal::PopulateSpawnGUI(char const *)
void __thiscall idSessionLocal::PopulateSpawnGUI(idSessionLocal *this, const char *filter)
{
  void *v2; // edi
  idSessionLocal *v3; // ebx
  signed int v4; // ebp
  const idDecl *v5; // esi
  const idKeyValue *v6; // eax
  rvSpawnDef *v7; // eax
  rvSpawnDef *v8; // ebx
  const char *v9; // eax
  const idKeyValue *v10; // eax
  int v11; // ecx
  signed int j; // eax
  int v13; // edx
  int v14; // eax
  _BYTE *v15; // esi
  _DWORD *v16; // eax
  int v17; // ecx
  signed int v18; // edx
  const char *v19; // eax
  const idKeyValue *v20; // eax
  int v21; // ecx
  signed int k; // eax
  int v23; // edx
  int v24; // eax
  _DWORD *v25; // eax
  int v26; // ecx
  signed int v27; // edx
  int v28; // eax
  int v29; // esi
  char *v30; // eax
  char *v31; // eax
  char *v32; // eax
  char *v33; // eax
  int v34; // [esp+30h] [ebp-48h]
  const char *v35; // [esp+30h] [ebp-48h]
  bool useDeclName; // [esp+47h] [ebp-31h]
  int i; // [esp+48h] [ebp-30h]
  int ia; // [esp+48h] [ebp-30h]
  const idKeyValue *key; // [esp+50h] [ebp-28h]
  const char *keyb; // [esp+50h] [ebp-28h]
  const idKeyValue *keya; // [esp+50h] [ebp-28h]
  const char *keyc; // [esp+50h] [ebp-28h]
  int numDecls; // [esp+54h] [ebp-24h]
  int numDeclsa; // [esp+54h] [ebp-24h]
  idUserInterface_vtbl *numDeclsb; // [esp+54h] [ebp-24h]
  idUserInterface_vtbl *numDeclsc; // [esp+54h] [ebp-24h]
  int numDeclsd; // [esp+54h] [ebp-24h]
  int spawns_4; // [esp+60h] [ebp-18h]
  char filtera; // [esp+7Ch] [ebp+4h]

  v2 = 0;
  v3 = this;
  v4 = 0;
  spawns_4 = 0;
  (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 104))(common.type);
  (*(void (__thiscall **)(_DWORD, int, _DWORD))(**(_DWORD **)common.ip + 20))(*(_DWORD *)common.ip, 0x80000, 0);
  useDeclName = cvarSystem->GetCVarBool(cvarSystem, "sg_declname");
  numDecls = declManager->GetNumDecls(declManager, DECL_ENTITYDEF);
  i = 0;
  if ( numDecls <= 0 )
    goto LABEL_53;
  do
  {
    v5 = declManager->DeclByIndex(declManager, 4, i, 1);
    v6 = idDict::FindKey((idDict *)&v5[1], "sg_category");
    if ( v6 )
    {
      if ( !idStr::Icmp(v6->value->data, filter) )
      {
        key = idDict::FindKey((idDict *)&v5[1], "sg_name");
        if ( key )
        {
          v7 = (rvSpawnDef *)Memory::Allocate(0x40u);
          v8 = v7;
          if ( useDeclName )
          {
            if ( v7 )
            {
              keyb = v5->base->GetName(v5->base);
              v9 = v5->base->GetName(v5->base);
              rvSpawnDef::rvSpawnDef(v8, keyb, v9);
              keya = v10;
            }
            else
            {
              keya = 0;
            }
            if ( !v2 )
            {
              v11 = spawns_4;
              if ( spawns_4 == 16 )
              {
LABEL_16:
                if ( v4 == v11 )
                {
                  v13 = (v11 + 16) % 16;
                  v14 = v11 + 16 - v13;
                  if ( v14 <= 0 )
                  {
LABEL_18:
                    if ( v2 )
                      Memory::Free(v2);
                    v4 = 0;
                    v2 = 0;
                    spawns_4 = 0;
                    goto LABEL_48;
                  }
                  if ( v14 != v11 )
                  {
                    v15 = v2;
                    spawns_4 = v11 + 16 - v13;
                    if ( v14 < v4 )
                      v4 = v11 + 16 - v13;
                    v16 = Memory::Allocate(4 * v14);
                    v2 = v16;
                    if ( v4 > 0 )
                    {
                      v17 = v15 - (_BYTE *)v16;
                      v18 = v4;
                      do
                      {
                        *v16 = *(_DWORD *)((char *)v16 + v17);
                        ++v16;
                        --v18;
                      }
                      while ( v18 );
                    }
LABEL_46:
                    if ( v15 )
                      Memory::Free(v15);
                    goto LABEL_48;
                  }
                }
                goto LABEL_48;
              }
              spawns_4 = 16;
              if ( v4 > 16 )
                v4 = 16;
              v2 = Memory::Allocate(0x40u);
              for ( j = 0; j < v4; ++j )
                *((_DWORD *)v2 + j) = *(_DWORD *)(4 * j);
            }
            v11 = spawns_4;
            goto LABEL_16;
          }
          if ( v7 )
          {
            keyc = key->value->data;
            v19 = v5->base->GetName(v5->base);
            rvSpawnDef::rvSpawnDef(v8, keyc, v19);
            keya = v20;
          }
          else
          {
            keya = 0;
          }
          if ( !v2 )
          {
            v21 = spawns_4;
            if ( spawns_4 == 16 )
            {
LABEL_38:
              if ( v4 == v21 )
              {
                v23 = (v21 + 16) % 16;
                v24 = v21 + 16 - v23;
                if ( v24 <= 0 )
                  goto LABEL_18;
                if ( v24 != v21 )
                {
                  v15 = v2;
                  spawns_4 = v21 + 16 - v23;
                  if ( v24 < v4 )
                    v4 = v21 + 16 - v23;
                  v25 = Memory::Allocate(4 * v24);
                  v2 = v25;
                  if ( v4 > 0 )
                  {
                    v26 = v15 - (_BYTE *)v25;
                    v27 = v4;
                    do
                    {
                      *v25 = *(_DWORD *)((char *)v25 + v26);
                      ++v25;
                      --v27;
                    }
                    while ( v27 );
                  }
                  goto LABEL_46;
                }
              }
LABEL_48:
              *((_DWORD *)v2 + v4++) = keya;
              goto LABEL_49;
            }
            spawns_4 = 16;
            if ( v4 > 16 )
              v4 = 16;
            v2 = Memory::Allocate(0x40u);
            for ( k = 0; k < v4; ++k )
              *((_DWORD *)v2 + k) = *(_DWORD *)(4 * k);
          }
          v21 = spawns_4;
          goto LABEL_38;
        }
      }
    }
LABEL_49:
    ++i;
  }
  while ( i < numDecls );
  if ( v2 )
    qsort(v2, v4, 4u, (int (__cdecl *)(const void *, const void *))rvSpawnSortCompare<rvSpawnDef *>);
  v3 = this;
LABEL_53:
  v28 = 0;
  ia = 0;
  v29 = 1;
  filtera = 0;
  if ( v4 <= 0 )
  {
    do
    {
      do
      {
LABEL_57:
        numDeclsd = (int)v3->guiActive->__vftable;
        v33 = va("spawn%dVisible", v29);
        v3 = this;
        (*(void (__thiscall **)(idUserInterface *, char *, _DWORD))(numDeclsd + 60))(this->guiActive, v33, 0);
        ++v29;
      }
      while ( v29 % 50 <= 22 );
      v29 += 27;
    }
    while ( v29 / 50 < 2 );
  }
  else
  {
    while ( 1 )
    {
      v34 = *(_DWORD *)(*((_DWORD *)v2 + v28) + 4);
      numDeclsa = (int)v3->guiActive->__vftable;
      v30 = va("spawn%dFriendly", v29);
      v3 = this;
      (*(void (__thiscall **)(idUserInterface *, char *, int))(numDeclsa + 56))(this->guiActive, v30, v34);
      v35 = *(const char **)(*((_DWORD *)v2 + ia) + 36);
      numDeclsb = this->guiActive->__vftable;
      v31 = va("spawn%dDef", v29);
      numDeclsb->SetStateString(this->guiActive, v31, v35);
      numDeclsc = this->guiActive->__vftable;
      v32 = va("spawn%dVisible", v29);
      numDeclsc->SetStateBool(this->guiActive, v32, 1);
      if ( ++v29 % 50 > 22 )
      {
        v29 += 28;
        if ( v29 / 50 >= 2 )
          break;
      }
      v28 = ++ia;
      if ( ia >= v4 )
        goto LABEL_57;
    }
    filtera = 1;
  }
  (*(void (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 24))(*(_DWORD *)common.ip, 0x80000);
  v3->guiActive->StateChanged(v3->guiActive, com_frameTime, 0);
  if ( filtera )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idSessionLocal::PopulateSpawnGUI: %d definitions not added\n",
      v4 - ia);
  if ( v2 )
    Memory::Free(v2);
}

// FUNC: public: void __thiscall idSessionLocal::GetSaveGameList(class idList<class idStr> &,class idList<struct fileTime_t> &)
void __thiscall idSessionLocal::GetSaveGameList(
        idSessionLocal *this,
        idList<idStr> *fileList,
        idList<fileTime_t> *fileTimes)
{
  const char *v3; // esi
  int v4; // eax
  int v5; // edi
  unsigned int v6; // eax
  int v7; // ebx
  int v8; // eax
  char *data; // edx
  const char *v10; // ecx
  char v11; // al
  idFileSystem_vtbl *v12; // edx
  idFileList *v13; // ebp
  idStr *list; // eax
  char *v16; // esi
  int size; // eax
  int v18; // esi
  int *v19; // eax
  idStr *v20; // edi
  idStr *v21; // eax
  bool v22; // cc
  idList<idStr> *v23; // eax
  idStr *v24; // esi
  unsigned int v25; // edi
  const void **v26; // esi
  idStr *v27; // ebp
  idList<fileTime_t> *v28; // esi
  idStr *v29; // eax
  idFileSystem_vtbl *v30; // edx
  int granularity; // eax
  int i; // eax
  fileTime_t *v33; // edx
  int v34; // ecx
  int v35; // ecx
  fileTime_t *v36; // ebp
  int j; // eax
  fileTime_t *v38; // ecx
  int num; // ecx
  fileTime_t *v40; // edx
  fileTime_t *v41; // eax
  char *v42; // [esp+0h] [ebp-78h]
  idFileList *files; // [esp+1Ch] [ebp-5Ch]
  int v44; // [esp+20h] [ebp-58h]
  idList<fileTime_t> *ft_4; // [esp+28h] [ebp-50h]
  idStr game; // [esp+2Ch] [ebp-4Ch] BYREF
  idStr result; // [esp+4Ch] [ebp-2Ch] BYREF
  int v48; // [esp+74h] [ebp-4h]
  idList<idStr> *fileLista; // [esp+7Ch] [ebp+4h]
  idList<idStr> *fileListb; // [esp+7Ch] [ebp+4h]

  v3 = cvarSystem->GetCVarString(cvarSystem, "fs_game");
  v4 = 0;
  v5 = 0;
  game.len = 0;
  game.alloced = 20;
  game.data = game.baseBuffer;
  game.baseBuffer[0] = 0;
  if ( v3 )
  {
    v6 = (unsigned int)&v3[strlen(v3) + 1];
    v7 = v6 - (_DWORD)(v3 + 1);
    v8 = v6 - (_DWORD)v3;
    if ( v8 > 20 )
      idStr::ReAllocate(&game, v8, 1);
    data = game.data;
    v10 = v3;
    do
    {
      v11 = *v10;
      *data++ = *v10++;
    }
    while ( v11 );
    v4 = v7;
    game.len = v7;
  }
  v12 = fileSystem->__vftable;
  v48 = 0;
  if ( v4 )
  {
    v13 = (idFileList *)((int (__stdcall *)(const char *, const char *, _DWORD, _DWORD, char *))v12->ListFiles)(
                          "savegames",
                          ".save",
                          0,
                          0,
                          game.data);
    files = v13;
  }
  else
  {
    files = (idFileList *)((int (__stdcall *)(const char *, const char *, _DWORD, _DWORD, _DWORD))v12->ListFiles)(
                            "savegames",
                            ".save",
                            0,
                            0,
                            0);
    v13 = files;
  }
  list = fileList->list;
  if ( list )
  {
    v16 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v16);
  }
  fileList->num = 0;
  fileList->size = 0;
  fileList->list = 0;
  fileList->num = v13->list.num;
  size = v13->list.size;
  fileList->size = size;
  v18 = size;
  fileList->granularity = v13->list.granularity;
  if ( size )
  {
    v19 = (int *)Memory::Allocate(32 * size + 4);
    LOBYTE(v48) = 1;
    if ( v19 )
    {
      v20 = (idStr *)(v19 + 1);
      *v19 = v18;
      `eh vector constructor iterator'(
        v19 + 1,
        0x20u,
        v18,
        (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      v21 = v20;
      v5 = 0;
    }
    else
    {
      v21 = 0;
    }
    v22 = fileList->num <= 0;
    LOBYTE(v48) = 0;
    fileList->list = v21;
    v44 = 0;
    if ( !v22 )
    {
      v23 = 0;
      for ( fileLista = 0; ; v23 = fileLista )
      {
        v24 = v13->list.list;
        v25 = *(int *)((char *)&v23->num + (_DWORD)v24);
        v26 = (const void **)((char *)v24 + (_DWORD)v23);
        v27 = (idStr *)((char *)v23 + (unsigned int)fileList->list);
        if ( (signed int)(v25 + 1) > v27->alloced )
          idStr::ReAllocate(v27, v25 + 1, 0);
        fileLista += 2;
        qmemcpy(v27->data, v26[1], v25);
        v27->data[v25] = 0;
        v27->len = v25;
        v13 = files;
        if ( ++v44 >= fileList->num )
          break;
      }
      v5 = 0;
    }
  }
  fileSystem->FreeFileList(fileSystem, v13);
  v28 = fileTimes;
  for ( fileListb = 0; (int)fileListb < fileList->num; fileListb = (idList<idStr> *)((char *)fileListb + 1) )
  {
    v29 = operator+(&result, "savegames/", &fileList->list[v5]);
    v30 = fileSystem->__vftable;
    v42 = v29->data;
    LOBYTE(v48) = 2;
    v30->ReadFile(fileSystem, v42, 0, (unsigned int *)&fileTimes);
    LOBYTE(v48) = 0;
    idStr::FreeData(&result);
    idStr::StripLeading(&fileList->list[v5], 47);
    idStr::StripFileExtension(&fileList->list[v5]);
    ft_4 = fileTimes;
    if ( !v28->list )
    {
      granularity = v28->granularity;
      if ( granularity > 0 )
      {
        if ( granularity != v28->size )
        {
          v22 = granularity < v28->num;
          v28->size = granularity;
          if ( v22 )
            v28->num = granularity;
          v28->list = (fileTime_t *)Memory::Allocate(8 * granularity);
          for ( i = 0; i < v28->num; ++i )
          {
            v33 = v28->list;
            v33[i].index = *(_DWORD *)(8 * i);
            v33[i].timeStamp = *(_DWORD *)(8 * i + 4);
          }
        }
      }
      else
      {
        v28->list = 0;
        v28->num = 0;
        v28->size = 0;
      }
    }
    v34 = v28->size;
    if ( v28->num == v34 )
    {
      if ( !v28->granularity )
        v28->granularity = 16;
      v35 = v28->granularity + v34 - (v28->granularity + v34) % v28->granularity;
      if ( v35 > 0 )
      {
        if ( v35 != v28->size )
        {
          v22 = v35 < v28->num;
          v36 = v28->list;
          v28->size = v35;
          if ( v22 )
            v28->num = v35;
          v28->list = (fileTime_t *)Memory::Allocate(8 * v35);
          for ( j = 0; j < v28->num; ++j )
          {
            v38 = v28->list;
            v38[j].index = v36[j].index;
            v38[j].timeStamp = v36[j].timeStamp;
          }
          if ( v36 )
            Memory::Free(v36);
        }
      }
      else
      {
        if ( v28->list )
          Memory::Free(v28->list);
        v28->list = 0;
        v28->num = 0;
        v28->size = 0;
      }
    }
    num = v28->num;
    v40 = v28->list;
    v40[num].index = (int)fileListb;
    v40[num].timeStamp = (unsigned int)ft_4;
    ++v28->num;
    ++v5;
  }
  v41 = v28->list;
  if ( v41 )
    qsort(v41, v28->num, 8u, (int (__cdecl *)(const void *, const void *))idListSaveGameCompare);
  v48 = -1;
  idStr::FreeData(&game);
}

// FUNC: public: void __thiscall idSessionLocal::ParseNotes(void)
void __thiscall idSessionLocal::ParseNotes(idSessionLocal *this)
{
  const idKeyValue *Key; // eax
  char *data; // eax
  idStr *v3; // esi
  unsigned int len; // ebp
  int v5; // eax
  idSessionLocal *v6; // edi
  idDict *v7; // eax
  const idKeyValue *v8; // eax
  idDict *v9; // eax
  const idKeyValue *v10; // eax
  idDict *v11; // eax
  const idKeyValue *v12; // eax
  const char *v13; // esi
  idFileList *v14; // esi
  int num; // eax
  int v16; // ebp
  const char *v17; // edi
  bool v18; // zf
  idUserInterface *guiActive; // esi
  char *v20; // eax
  idUserInterface *v21; // esi
  int v22; // ebp
  char *v23; // eax
  idUserInterface *v25; // esi
  idUserInterface_vtbl *v26; // edi
  char *v27; // eax
  idSessionLocal *v28; // edi
  idFileList **v29; // esi
  char *v30; // eax
  char *v31; // [esp+10h] [ebp-178h]
  bool completed; // [esp+27h] [ebp-161h] BYREF
  idSessionLocal *v33; // [esp+28h] [ebp-160h]
  const char *categoryFilter; // [esp+2Ch] [ebp-15Ch]
  const char *assignedToFilter; // [esp+30h] [ebp-158h]
  idFileList *files; // [esp+34h] [ebp-154h]
  idUserInterface_vtbl *v37; // [esp+38h] [ebp-150h]
  unsigned int v38; // [esp+3Ch] [ebp-14Ch]
  int count; // [esp+40h] [ebp-148h]
  int i; // [esp+44h] [ebp-144h]
  int completedValue; // [esp+48h] [ebp-140h]
  idStr comments; // [esp+4Ch] [ebp-13Ch] BYREF
  idStr user; // [esp+6Ch] [ebp-11Ch] BYREF
  idStr assignedTo; // [esp+8Ch] [ebp-FCh] BYREF
  idStr category; // [esp+ACh] [ebp-DCh] BYREF
  idStr fileName; // [esp+CCh] [ebp-BCh] BYREF
  idStr date; // [esp+ECh] [ebp-9Ch] BYREF
  idStr version; // [esp+10Ch] [ebp-7Ch] BYREF
  idStr mapName; // [esp+12Ch] [ebp-5Ch] BYREF
  idVec3 origin; // [esp+14Ch] [ebp-3Ch] BYREF
  idMat3 axis; // [esp+158h] [ebp-30h] BYREF
  int v52; // [esp+184h] [ebp-4h]

  v33 = this;
  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  mapName.alloced = 20;
  v52 = 1;
  mapName.len = 0;
  mapName.data = mapName.baseBuffer;
  mapName.baseBuffer[0] = 0;
  Key = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_map");
  if ( Key )
    data = Key->value->data;
  else
    data = (char *)&entityFilter;
  idStr::operator=(&mapName, data);
  idStr::StripFileExtension(&mapName);
  v3 = operator+(&user, "viewnotes/", &mapName);
  len = v3->len;
  v5 = v3->len + 1;
  LOBYTE(v52) = 2;
  if ( v5 > fileName.alloced )
    idStr::ReAllocate(&fileName, v5, 0);
  qmemcpy(fileName.data, v3->data, len);
  fileName.data[len] = 0;
  fileName.len = len;
  LOBYTE(v52) = 1;
  idStr::FreeData(&user);
  v6 = v33;
  v7 = (idDict *)v33->guiActive->State(v33->guiActive);
  v8 = idDict::FindKey(v7, "filterCategoryText");
  if ( v8 )
    categoryFilter = v8->value->data;
  else
    categoryFilter = &entityFilter;
  if ( !idStr::Icmp(categoryFilter, "none") )
    categoryFilter = 0;
  v9 = (idDict *)v33->guiActive->State(v33->guiActive);
  v10 = idDict::FindKey(v9, "filterAssignedToText");
  if ( v10 )
    assignedToFilter = v10->value->data;
  else
    assignedToFilter = &entityFilter;
  if ( !idStr::Icmp(assignedToFilter, "none") )
    assignedToFilter = 0;
  v11 = (idDict *)v33->guiActive->State(v33->guiActive);
  v12 = idDict::FindKey(v11, "filterCompletedText");
  if ( v12 )
    v13 = v12->value->data;
  else
    v13 = &entityFilter;
  if ( idStr::Icmp(v13, "none") )
    completedValue = idStr::Icmp(v13, "completed") == 0;
  else
    completedValue = -1;
  v14 = fileSystem->ListFilesTree(fileSystem, fileName.data, ".txt", 0, 0);
  num = v14->list.num;
  v16 = 0;
  files = v14;
  i = 0;
  count = 0;
  if ( num > 0 )
  {
    v38 = 0;
    do
    {
      user.len = 0;
      user.alloced = 20;
      user.data = user.baseBuffer;
      user.baseBuffer[0] = 0;
      date.len = 0;
      date.alloced = 20;
      date.data = date.baseBuffer;
      date.baseBuffer[0] = 0;
      version.len = 0;
      version.alloced = 20;
      version.data = version.baseBuffer;
      version.baseBuffer[0] = 0;
      category.len = 0;
      category.alloced = 20;
      category.data = category.baseBuffer;
      category.baseBuffer[0] = 0;
      assignedTo.len = 0;
      assignedTo.alloced = 20;
      assignedTo.data = assignedTo.baseBuffer;
      assignedTo.baseBuffer[0] = 0;
      comments.len = 0;
      comments.alloced = 20;
      comments.data = comments.baseBuffer;
      comments.baseBuffer[0] = 0;
      v17 = v14->list.list[v38 / 0x20].data;
      v18 = *v17 == 46;
      LOBYTE(v52) = 8;
      if ( !v18
        && idSessionLocal::ReadNoteFile(
             v33,
             v17,
             &origin,
             &axis,
             &user,
             &date,
             &version,
             &category,
             &assignedTo,
             &completed,
             &comments)
        && (!categoryFilter || !idStr::Icmp(category.data, categoryFilter))
        && (!assignedToFilter || !idStr::Icmp(assignedTo.data, assignedToFilter))
        && (completedValue == -1 || completed == (completedValue != 0)) )
      {
        if ( !idStr::Cmp(comments.data, &entityFilter) )
          idStr::operator=(&comments, "< Empty >");
        guiActive = v33->guiActive;
        v31 = comments.data;
        v37 = guiActive->__vftable;
        v20 = va("notes_item_%i", v16);
        v37->SetStateString(guiActive, v20, v31);
        v21 = v33->guiActive;
        v22 = count;
        v37 = v21->__vftable;
        v23 = va("notes_file_%i", count);
        v37->SetStateString(v21, v23, v17);
        v14 = files;
        v16 = v22 + 1;
        count = v16;
      }
      LOBYTE(v52) = 7;
      idStr::FreeData(&comments);
      LOBYTE(v52) = 6;
      idStr::FreeData(&assignedTo);
      LOBYTE(v52) = 5;
      idStr::FreeData(&category);
      LOBYTE(v52) = 4;
      idStr::FreeData(&version);
      LOBYTE(v52) = 3;
      idStr::FreeData(&date);
      LOBYTE(v52) = 1;
      idStr::FreeData(&user);
      v38 += 32;
    }
    while ( ++i < v14->list.num );
    v6 = v33;
  }
  fileSystem->FreeFileList(fileSystem, v14);
  v25 = v6->guiActive;
  v26 = v25->__vftable;
  v27 = va("notes_item_%i", v16);
  v26->DeleteState(v25, v27);
  v28 = v33;
  v29 = (idFileList **)v33->guiActive;
  files = *v29;
  v30 = va("notes_file_%i", v16);
  ((void (__thiscall *)(idFileList **, char *))files[1].list.size)(v29, v30);
  v28->guiActive->SetStateInt(v28->guiActive, "notes_sel_0", -1);
  v28->guiActive->StateChanged(v28->guiActive, com_frameTime, 0);
  LOBYTE(v52) = 0;
  idStr::FreeData(&mapName);
  v52 = -1;
  idStr::FreeData(&fileName);
}

// FUNC: public: void __thiscall idSessionLocal::ExportNotes(void)
void __thiscall idSessionLocal::ExportNotes(idSessionLocal *this)
{
  const idKeyValue *Key; // eax
  const char *data; // esi
  int v3; // edi
  char v4; // cl
  int j; // eax
  char *v6; // edx
  const idStr *v7; // eax
  idStr *v8; // esi
  unsigned int len; // ebp
  int v10; // eax
  idFile *v11; // eax
  idFile *v12; // ebx
  idSessionLocal *v13; // edi
  idDict *v14; // eax
  const idKeyValue *v15; // eax
  const char *v16; // eax
  const char *v17; // esi
  idDict *v18; // eax
  const idKeyValue *v19; // eax
  const char *v20; // eax
  char *v21; // esi
  char *v22; // edi
  char *v23; // ebp
  const char *v24; // eax
  char *v25; // [esp-4h] [ebp-170h]
  bool completed; // [esp+13h] [ebp-159h] BYREF
  int i; // [esp+14h] [ebp-158h]
  const char *v28; // [esp+18h] [ebp-154h]
  idSessionLocal *v29; // [esp+1Ch] [ebp-150h]
  int numSel; // [esp+20h] [ebp-14Ch]
  idFile v31; // [esp+24h] [ebp-148h]
  char *v32; // [esp+28h] [ebp-144h]
  idFile *file; // [esp+2Ch] [ebp-140h]
  idStr mapName; // [esp+30h] [ebp-13Ch] BYREF
  idStr fileName; // [esp+50h] [ebp-11Ch] BYREF
  idStr user; // [esp+70h] [ebp-FCh] BYREF
  idStr version; // [esp+90h] [ebp-DCh] BYREF
  idStr assignedTo; // [esp+B0h] [ebp-BCh] BYREF
  idStr date; // [esp+D0h] [ebp-9Ch] BYREF
  idStr category; // [esp+F0h] [ebp-7Ch] BYREF
  idStr comments; // [esp+110h] [ebp-5Ch] BYREF
  idVec3 origin; // [esp+130h] [ebp-3Ch] BYREF
  idMat3 axis; // [esp+13Ch] [ebp-30h] BYREF
  int v44; // [esp+168h] [ebp-4h]

  v29 = this;
  fileName.len = 0;
  fileName.alloced = 20;
  fileName.data = fileName.baseBuffer;
  fileName.baseBuffer[0] = 0;
  mapName.alloced = 20;
  v44 = 1;
  mapName.len = 0;
  mapName.data = mapName.baseBuffer;
  mapName.baseBuffer[0] = 0;
  Key = idDict::FindKey(&this->mapSpawnData.serverInfo, "si_map");
  if ( Key )
  {
    data = Key->value->data;
    if ( !data )
      goto LABEL_8;
  }
  else
  {
    data = &entityFilter;
  }
  v3 = strlen(data) + mapName.len;
  if ( v3 + 1 > mapName.alloced )
    idStr::ReAllocate(&mapName, v3 + 1, 1);
  v4 = *data;
  for ( j = 0; v4; v4 = data[j] )
  {
    v6 = &mapName.data[j++];
    v6[mapName.len] = v4;
  }
  mapName.len = v3;
  mapName.data[v3] = 0;
LABEL_8:
  idStr::StripFileExtension(&mapName);
  v7 = operator+(&user, "viewnotes/", &mapName);
  LOBYTE(v44) = 2;
  v8 = operator+(&version, v7, ".txt");
  len = v8->len;
  v10 = v8->len + 1;
  LOBYTE(v44) = 3;
  if ( v10 > fileName.alloced )
    idStr::ReAllocate(&fileName, v10, 0);
  qmemcpy(fileName.data, v8->data, len);
  fileName.data[len] = 0;
  fileName.len = len;
  LOBYTE(v44) = 2;
  idStr::FreeData(&version);
  LOBYTE(v44) = 1;
  idStr::FreeData(&user);
  v11 = fileSystem->OpenFileWrite(fileSystem, fileName.data, "fs_savepath", 0);
  v12 = v11;
  file = v11;
  if ( v11 )
  {
    v11->WriteFloatString(v11, "Assigned To\tReporter\tCategory\tCompleted\tDate\tLocation\tComments\r\n");
    v13 = v29;
    v14 = (idDict *)v29->guiActive->State(v29->guiActive);
    v15 = idDict::FindKey(v14, "notes_num");
    if ( v15 )
      v16 = v15->value->data;
    else
      v16 = "-1";
    numSel = atoi(v16);
    i = 0;
    if ( numSel > 0 )
    {
      while ( 1 )
      {
        v17 = va("notes_file_%i", i);
        v18 = (idDict *)v13->guiActive->State(v13->guiActive);
        v19 = idDict::FindKey(v18, v17);
        if ( !v19 )
          break;
        v20 = v19->value->data;
        if ( v20 )
          goto LABEL_18;
LABEL_23:
        if ( ++i >= numSel )
          goto LABEL_24;
      }
      v20 = &entityFilter;
LABEL_18:
      user.len = 0;
      user.alloced = 20;
      user.data = user.baseBuffer;
      user.baseBuffer[0] = 0;
      date.len = 0;
      date.alloced = 20;
      date.data = date.baseBuffer;
      date.baseBuffer[0] = 0;
      version.len = 0;
      version.alloced = 20;
      version.data = version.baseBuffer;
      version.baseBuffer[0] = 0;
      category.len = 0;
      category.alloced = 20;
      category.data = category.baseBuffer;
      category.baseBuffer[0] = 0;
      assignedTo.len = 0;
      assignedTo.alloced = 20;
      assignedTo.data = assignedTo.baseBuffer;
      assignedTo.baseBuffer[0] = 0;
      comments.alloced = 20;
      comments.len = 0;
      comments.data = comments.baseBuffer;
      comments.baseBuffer[0] = 0;
      LOBYTE(v44) = 9;
      if ( idSessionLocal::ReadNoteFile(
             v13,
             v20,
             &origin,
             &axis,
             &user,
             &date,
             &version,
             &category,
             &assignedTo,
             &completed,
             &comments) )
      {
        v28 = "yes";
        if ( !completed )
          v28 = "no";
        v21 = date.data;
        v22 = category.data;
        v23 = user.data;
        v25 = comments.data;
        v32 = assignedTo.data;
        v31.__vftable = v12->__vftable;
        v24 = idVec3::ToString(&origin, 2);
        v12 = file;
        v31.WriteFloatString(file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\r\n", v32, v23, v22, v28, v21, v24, v25);
        v13 = v29;
      }
      LOBYTE(v44) = 8;
      idStr::FreeData(&comments);
      LOBYTE(v44) = 7;
      idStr::FreeData(&assignedTo);
      LOBYTE(v44) = 6;
      idStr::FreeData(&category);
      LOBYTE(v44) = 5;
      idStr::FreeData(&version);
      LOBYTE(v44) = 4;
      idStr::FreeData(&date);
      LOBYTE(v44) = 1;
      idStr::FreeData(&user);
      goto LABEL_23;
    }
LABEL_24:
    fileSystem->CloseFile(fileSystem, v12);
  }
  LOBYTE(v44) = 0;
  idStr::FreeData(&mapName);
  v44 = -1;
  idStr::FreeData(&fileName);
}

// FUNC: public: void __thiscall idSessionLocal::SetSaveGameGuiVars(bool)
void __userpurge idSessionLocal::SetSaveGameGuiVars(idSessionLocal *this@<ecx>, int a2@<edi>, bool isSaveList)
{
  idStr *list; // eax
  char *v5; // esi
  bool v6; // zf
  int size; // esi
  idStr *v8; // eax
  char *v9; // edi
  bool v10; // cc
  idStr *v11; // edi
  int *v12; // eax
  idStr *v13; // ebx
  idStr *v14; // eax
  int v15; // esi
  unsigned int v16; // edi
  idStr *v17; // ebx
  idStr *v18; // ebx
  int v19; // esi
  unsigned int v20; // edi
  int v21; // eax
  const char *v22; // eax
  char *data; // ebx
  idStr *v24; // esi
  char *len; // ebx
  idStr *v26; // esi
  idUserInterface_vtbl *v27; // edi
  char *v28; // eax
  idUserInterface_vtbl *v29; // edi
  char *v30; // eax
  char *v31; // esi
  int alloced; // [esp+24h] [ebp-184h]
  int i; // [esp+38h] [ebp-170h]
  int ia; // [esp+38h] [ebp-170h]
  idStr *v35; // [esp+3Ch] [ebp-16Ch]
  int v36; // [esp+3Ch] [ebp-16Ch]
  idList<idStr> fileList; // [esp+40h] [ebp-168h] BYREF
  int v38; // [esp+50h] [ebp-158h]
  idList<fileTime_t> fileTimes; // [esp+54h] [ebp-154h] BYREF
  idStr name; // [esp+64h] [ebp-144h] BYREF
  idToken tok; // [esp+84h] [ebp-124h] BYREF
  idLexer src; // [esp+D4h] [ebp-D4h] BYREF
  int v43; // [esp+1A4h] [ebp-4h]
  void *retaddr; // [esp+1A8h] [ebp+0h]

  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  v43 = 0;
  fileList.granularity = 16;
  fileList.list = 0;
  fileList.size = 0;
  fileTimes.granularity = 16;
  fileTimes.list = 0;
  fileTimes.num = 0;
  fileTimes.size = 0;
  list = this->loadGameList.list;
  LOBYTE(v43) = 2;
  if ( list )
  {
    v5 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v5);
  }
  this->loadGameList.list = 0;
  this->loadGameList.num = 0;
  this->loadGameList.size = 0;
  v6 = this->guiActive == 0;
  fileList.list = 0;
  fileList.size = 0;
  fileTimes.list = 0;
  fileTimes.num = 0;
  fileTimes.size = 0;
  if ( !v6 )
  {
    ((void (__thiscall *)(idUserInterface *, const char *, const char *, int))this->guiActive->SetStateString)(
      this->guiActive,
      "saveGameName",
      &entityFilter,
      a2);
    this->guiActive->SetStateString(this->guiActive, "saveGameDescription", &entityFilter);
    this->guiActive->SetStateString(this->guiActive, "saveGameDate", &entityFilter);
    this->guiActive->SetStateString(this->guiActive, "saveGameTime", &entityFilter);
    idSessionLocal::GetSaveGameList(this, (idList<idStr> *)&fileList.size, (idList<fileTime_t> *)&fileTimes.size);
    size = fileList.size;
    if ( fileList.size > 0 )
    {
      if ( fileList.size != this->loadGameList.size )
      {
        v10 = fileList.size < this->loadGameList.num;
        v11 = this->loadGameList.list;
        v35 = v11;
        this->loadGameList.size = fileList.size;
        if ( v10 )
          this->loadGameList.num = size;
        v12 = (int *)Memory::Allocate(32 * size + 4);
        LOBYTE(retaddr) = 3;
        if ( v12 )
        {
          v13 = (idStr *)(v12 + 1);
          *v12 = size;
          `eh vector constructor iterator'(
            v12 + 1,
            0x20u,
            size,
            (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          v14 = v13;
        }
        else
        {
          v14 = 0;
        }
        v10 = this->loadGameList.num <= 0;
        LOBYTE(retaddr) = 2;
        this->loadGameList.list = v14;
        fileTimes.num = 0;
        if ( !v10 )
        {
          v15 = 0;
          for ( i = 0; ; v15 = i )
          {
            v16 = *(int *)((char *)&v11->len + v15);
            v17 = (idStr *)((char *)this->loadGameList.list + v15);
            fileList.num = v16;
            if ( (signed int)(v16 + 1) > v17->alloced )
              idStr::ReAllocate(v17, v16 + 1, 0);
            i += 32;
            qmemcpy(v17->data, *(const void **)((char *)&v35->data + v15), v16);
            v11 = v35;
            v17->data[fileList.num] = 0;
            v17->len = fileList.num;
            v10 = ++fileTimes.num < this->loadGameList.num;
            if ( !v10 )
              break;
          }
          size = fileList.size;
        }
        if ( v11 )
        {
          `eh vector destructor iterator'(
            v11,
            0x20u,
            *(_DWORD *)&v11[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(&v11[-1].baseBuffer[16]);
        }
      }
    }
    else
    {
      v8 = this->loadGameList.list;
      if ( v8 )
      {
        v9 = &v8[-1].baseBuffer[16];
        `eh vector destructor iterator'(
          v8,
          0x20u,
          *(_DWORD *)&v8[-1].baseBuffer[16],
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        Memory::Free(v9);
      }
      this->loadGameList.list = 0;
      this->loadGameList.num = 0;
      this->loadGameList.size = 0;
    }
    this->loadGameList.num = size;
    v36 = 0;
    if ( size > 0 )
    {
      ia = 0;
      do
      {
        v18 = &this->loadGameList.list[ia];
        v19 = v38 + 32 * *(_DWORD *)(name.len + 8 * v36);
        v20 = *(_DWORD *)v19;
        v21 = *(_DWORD *)v19 + 1;
        fileList.num = *(_DWORD *)v19;
        if ( v21 > v18->alloced )
          idStr::ReAllocate(v18, v21, 0);
        qmemcpy(v18->data, *(const void **)(v19 + 4), v20);
        v18->data[fileList.num] = 0;
        v18->len = fileList.num;
        idLexer::idLexer((idLexer *)&src.filename, 9);
        LOBYTE(retaddr) = 4;
        v22 = va("savegames/%s.txt", this->loadGameList.list[ia].data);
        if ( idLexer::LoadFile((idLexer *)&src.filename, v22, 0) )
        {
          *(double *)((char *)&tok.floatvalue + 4) = 0.0;
          tok.data = 0;
          *(_DWORD *)tok.baseBuffer = 20;
          tok.alloced = (int)&tok.baseBuffer[4];
          tok.baseBuffer[4] = 0;
          LOBYTE(retaddr) = 5;
          idLexer::ReadToken((idLexer *)&src.filename, (idToken *)&tok.data);
          idLexer::ReadToken((idLexer *)&src.filename, (idToken *)&tok.data);
          data = tok.data;
          if ( (int)(tok.data + 1) > *(int *)name.baseBuffer )
            idStr::ReAllocate((idStr *)&name.data, (int)(tok.data + 1), 0);
          qmemcpy((void *)name.alloced, (const void *)tok.alloced, (unsigned int)data);
          data[name.alloced] = 0;
          name.data = data;
          LOBYTE(retaddr) = 4;
          idStr::FreeData((idStr *)&tok.data);
        }
        else
        {
          v24 = this->loadGameList.list;
          len = (char *)v24[ia].len;
          v26 = &v24[ia];
          if ( (int)(len + 1) > *(int *)name.baseBuffer )
            idStr::ReAllocate((idStr *)&name.data, (int)(len + 1), 0);
          qmemcpy((void *)name.alloced, v26->data, (unsigned int)len);
          len[name.alloced] = 0;
          name.data = len;
        }
        v27 = this->guiActive->__vftable;
        alloced = name.alloced;
        v28 = va("loadgame_item_%i", v36);
        v27->SetStateString(this->guiActive, v28, (const char *)alloced);
        LOBYTE(retaddr) = 2;
        idLexer::~idLexer((idLexer *)&src.filename);
        ++ia;
        ++v36;
      }
      while ( v36 < fileList.size );
      size = fileList.size;
    }
    v29 = this->guiActive->__vftable;
    v30 = va("loadgame_item_%i", size);
    v29->DeleteStateVar(this->guiActive, v30);
    this->guiActive->SetStateInt(this->guiActive, "loadgame_listdef_count", size);
    this->guiActive->SetStateString(this->guiActive, "loadgame_sel_0", "-1");
    this->guiActive->SetStateString(this->guiActive, "loadgame_shot", "gfx/guis/loadscreens/generic");
    declManager->FindMaterial(declManager, "gfx/guis/loadscreens/generic", 1)->sort = -2.0;
    LOBYTE(v43) = 1;
    if ( fileTimes.list )
      Memory::Free(fileTimes.list);
    LOBYTE(v43) = 0;
    if ( fileList.list )
    {
      v31 = &fileList.list[-1].baseBuffer[16];
      `eh vector destructor iterator'(
        fileList.list,
        0x20u,
        *(_DWORD *)&fileList.list[-1].baseBuffer[16],
        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
      Memory::Free(v31);
    }
  }
  v43 = -1;
  idStr::FreeData(&name);
}

// FUNC: public: void __thiscall idSessionLocal::SetModsMenuGuiVars(void)
void __usercall idSessionLocal::SetModsMenuGuiVars(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        int a4@<esi>)
{
  idModList *v5; // esi
  int num; // ebx
  int v7; // eax
  int v8; // ebx
  idUserInterface_vtbl *v9; // ebp
  char *v10; // eax
  idUserInterface_vtbl *v11; // ebx
  char *v12; // eax
  char *data; // [esp+0h] [ebp-Ch]
  int v14; // [esp+14h] [ebp+8h]

  if ( this->guiActive )
  {
    v5 = (idModList *)((int (__thiscall *)(idFileSystem *, int, int, int))fileSystem->ListMods)(fileSystem, a4, a3, a2);
    num = v5->mods.num;
    idList<idStr>::Resize(&this->modsList, v5->mods.num);
    v7 = 0;
    this->modsList.num = num;
    v14 = 0;
    if ( v5->mods.num > 0 )
    {
      v8 = 0;
      do
      {
        v9 = this->guiActive->__vftable;
        data = v5->descriptions.list[v8].data;
        v10 = va("modsList_item_%i", v7);
        v9->SetStateString(this->guiActive, v10, data);
        idStr::operator=(&this->modsList.list[v8], v5->mods.list[v8].data);
        v7 = v14 + 1;
        ++v8;
        ++v14;
      }
      while ( v14 < v5->mods.num );
    }
    v11 = this->guiActive->__vftable;
    v12 = va("modsList_item_%i", v5->mods.num);
    v11->DeleteStateVar(this->guiActive, v12);
    this->guiActive->SetStateString(this->guiActive, "modsList_sel_0", "-1");
    fileSystem->FreeModList(fileSystem, v5);
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::SetMainMenuGuiVars(void)
void __usercall idSessionLocal::SetMainMenuGuiVars(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        int a4@<edi>)
{
  bool v5; // zf
  const char *v6; // eax
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  const char *v10; // eax
  idUserInterface *guiMainMenu; // edi
  idUserInterface_vtbl *v12; // ebx
  int v13; // eax
  idUserInterface *v14; // edi
  idUserInterface_vtbl *v15; // ebx
  int v16; // eax
  const char *v17; // eax
  const char *v18; // edi
  unsigned int v19; // ebp
  _BYTE *v20; // ecx
  char v21; // al
  const char *v22; // edi
  unsigned int v23; // eax
  unsigned int v24; // ebp
  int v25; // eax
  _BYTE *v26; // edx
  const char *v27; // ecx
  char v28; // al
  float z; // ebx
  const char *v30; // eax
  int v31; // ecx
  const char *v32; // eax
  const char *v33; // edi
  unsigned int v34; // ebp
  char v35; // cl
  int v36; // eax
  int v37; // edx
  int v38; // [esp+9Ch] [ebp-68h]
  idVec4 hitscanTint; // [esp+A8h] [ebp-5Ch] BYREF
  idStr deviceNames; // [esp+B8h] [ebp-4Ch] BYREF
  idStr hitScanValue; // [esp+D8h] [ebp-2Ch] BYREF
  int v42; // [esp+100h] [ebp-4h]

  if ( this->guiMainMenu )
  {
    this->guiMainMenu->SetStateString(this->guiMainMenu, "serverlist_sel_0", "-1");
    this->guiMainMenu->SetStateString(this->guiMainMenu, "serverlist_selid_0", "-1");
    this->guiMainMenu->SetStateInt(this->guiMainMenu, "com_machineSpec", com_machineSpec.internalVar->integerValue);
    this->guiMainMenu->SetStateString(this->guiMainMenu, "sys_lang", (const char *)*((_DWORD *)off_102F2378 + 2));
    this->guiMainMenu->SetStateString(this->guiMainMenu, "inetGame", &entityFilter);
    idSessionLocal::SetMainMenuCrosshairVars(this);
    this->guiMainMenu->SetKeyBindingNames(this->guiMainMenu);
    if ( this->mapSpawned )
    {
      v5 = !this->IsMultiplayer(this);
      v6 = "2";
      if ( v5 )
        v6 = "1";
      this->guiMainMenu->SetStateString(this->guiMainMenu, "inGame", v6);
    }
    else
    {
      this->guiMainMenu->SetStateString(this->guiMainMenu, "inGame", "0");
    }
    this->SetCDKeyGuiVars(this);
    v5 = !cvarSystem->GetCVarBool(cvarSystem, "g_nightmare");
    v7 = "1";
    if ( v5 )
      v7 = "0";
    this->guiMainMenu->SetStateString(this->guiMainMenu, "nightmare", v7);
    this->guiMainMenu->SetStateString(this->guiMainMenu, "browser_levelshot", "gfx/guis/loadscreens/generic");
    idSessionLocal::SetModsMenuGuiVars(this, a2, a3, (int)this);
    this->guiMainMenu->SetStateString(this->guiMainMenu, "driver_prompt", "0");
    v5 = !cvarSystem->GetCVarBool(cvarSystem, "si_isBuyingEnabled");
    v8 = "1";
    if ( v5 )
      v8 = "0";
    this->guiMainMenu->SetStateString(this->guiMainMenu, "si_isBuyingEnabled", v8);
    v5 = !cvarSystem->GetCVarBool(cvarSystem, "si_usepass");
    v9 = "1";
    if ( v5 )
      v9 = "0";
    this->guiMainMenu->SetStateString(this->guiMainMenu, "si_usepass", v9);
    v5 = !cvarSystem->GetCVarBool(cvarSystem, "g_crosshairCustom");
    v10 = "1";
    if ( v5 )
      v10 = "0";
    ((void (__thiscall *)(idUserInterface *, const char *, const char *, int, int, int))this->guiMainMenu->SetStateString)(
      this->guiMainMenu,
      "g_crosshairCustom",
      v10,
      a4,
      a3,
      a2);
    guiMainMenu = this->guiMainMenu;
    v12 = guiMainMenu->__vftable;
    v13 = ((int (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarBool)(cvarSystem, "s_useOpenAL");
    v12->SetStateBool(guiMainMenu, "s_useOpenAL", v13);
    v14 = this->guiMainMenu;
    v15 = v14->__vftable;
    v16 = ((int (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarBool)(cvarSystem, "s_loadOpenALFailed");
    v15->SetStateBool(v14, "s_loadOpenALFailed", v16);
    v17 = cvarSystem->GetCVarString(cvarSystem, "ui_hitscanTint");
    v18 = v17;
    *(_DWORD *)hitScanValue.baseBuffer = 0;
    *(_DWORD *)&hitScanValue.baseBuffer[8] = 20;
    *(_DWORD *)&hitScanValue.baseBuffer[4] = &hitScanValue.baseBuffer[12];
    hitScanValue.baseBuffer[12] = 0;
    if ( v17 )
    {
      v19 = strlen(v17);
      if ( (int)(v19 + 1) > 20 )
        idStr::ReAllocate((idStr *)hitScanValue.baseBuffer, v19 + 1, 1);
      v20 = *(_BYTE **)&hitScanValue.baseBuffer[4];
      do
      {
        v21 = *v18;
        *v20++ = *v18++;
      }
      while ( v21 );
      *(_DWORD *)hitScanValue.baseBuffer = v19;
    }
    sscanf(
      *(const char **)&hitScanValue.baseBuffer[4],
      "%f %f %f %f",
      &hitscanTint.w,
      &deviceNames,
      &deviceNames.data,
      &deviceNames.alloced);
    ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))this->guiMainMenu->SetStateFloat)(
      this->guiMainMenu,
      "ui_hitscanTint",
      LODWORD(hitscanTint.w));
    idSessionLocal::SetPbMenuGuiVars(this);
    idSessionLocal::SetMainMenuMPModelVars(this);
    v22 = soundSystem->GetDeviceName(soundSystem, 0);
    *(_DWORD *)deviceNames.baseBuffer = 0;
    *(_DWORD *)&deviceNames.baseBuffer[8] = 20;
    *(_DWORD *)&deviceNames.baseBuffer[4] = &deviceNames.baseBuffer[12];
    deviceNames.baseBuffer[12] = 0;
    if ( v22 )
    {
      v23 = (unsigned int)&v22[strlen(v22) + 1];
      v24 = v23 - (_DWORD)(v22 + 1);
      v25 = v23 - (_DWORD)v22;
      if ( v25 > 20 )
        idStr::ReAllocate((idStr *)deviceNames.baseBuffer, v25, 1);
      v26 = *(_BYTE **)&deviceNames.baseBuffer[4];
      v27 = v22;
      do
      {
        v28 = *v27;
        *v26++ = *v27++;
      }
      while ( v28 );
      *(_DWORD *)deviceNames.baseBuffer = v24;
    }
    LODWORD(z) = 1;
    LODWORD(hitscanTint.z) = 1;
    if ( soundSystem->GetDeviceName(soundSystem, 1) )
    {
      do
      {
        v30 = soundSystem->GetDeviceName(soundSystem, LODWORD(z));
        v31 = 0;
        if ( !*v30 )
          break;
        do
          ++v31;
        while ( v30[v31] );
        if ( !v31 )
          break;
        if ( deviceNames.alloced + 2 > *(int *)&deviceNames.baseBuffer[4] )
          idStr::ReAllocate((idStr *)&deviceNames.alloced, deviceNames.alloced + 2, 1);
        *(_BYTE *)(*(_DWORD *)deviceNames.baseBuffer + deviceNames.alloced++) = 59;
        *(_BYTE *)(*(_DWORD *)deviceNames.baseBuffer + deviceNames.alloced) = 0;
        v32 = (const char *)((int (__thiscall *)(idSoundSystem *, _DWORD, int))soundSystem->GetDeviceName)(
                              soundSystem,
                              LODWORD(z),
                              v38);
        v33 = v32;
        if ( v32 )
        {
          v34 = strlen(v32) + *(_DWORD *)deviceNames.baseBuffer;
          if ( (int)(v34 + 1) > *(int *)&deviceNames.baseBuffer[8] )
            idStr::ReAllocate((idStr *)deviceNames.baseBuffer, v34 + 1, 1);
          v35 = *v33;
          v36 = 0;
          if ( *v33 )
          {
            do
            {
              v37 = v36 + *(_DWORD *)&deviceNames.baseBuffer[4];
              ++v36;
              *(_BYTE *)(v37 + *(_DWORD *)deviceNames.baseBuffer) = v35;
              v35 = v33[v36];
            }
            while ( v35 );
            z = hitscanTint.z;
          }
          *(_DWORD *)deviceNames.baseBuffer = v34;
          *(_BYTE *)(*(_DWORD *)&deviceNames.baseBuffer[4] + v34) = 0;
        }
        v38 = ++LODWORD(z);
        hitscanTint.z = z;
      }
      while ( ((int (__thiscall *)(idSoundSystem *))soundSystem->GetDeviceName)(soundSystem) );
    }
    this->guiMainMenu->SetStateString(this->guiMainMenu, "device_name", *(const char **)deviceNames.baseBuffer);
    LOBYTE(v42) = 0;
    idStr::FreeData(&deviceNames);
    v42 = -1;
    idStr::FreeData(&hitScanValue);
  }
}

// FUNC: public: bool __thiscall idSessionLocal::HandleSaveGameMenuCommand(class idCmdArgs &,int &)
char __userpurge idSessionLocal::HandleSaveGameMenuCommand@<al>(
        idSessionLocal *this@<ecx>,
        int a2@<ebp>,
        idCmdArgs *args,
        int *icmd)
{
  int v4; // eax
  char *v5; // edi
  const char *v7; // esi
  idDict *v8; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int v11; // eax
  idDict *v13; // eax
  const idKeyValue *v14; // eax
  const char *v15; // esi
  unsigned int v16; // eax
  int v17; // ebp
  int v18; // eax
  char *v19; // edx
  const char *v20; // ecx
  char v21; // al
  char *v22; // ebp
  int v23; // eax
  const char *v24; // eax
  unsigned int v25; // eax
  int v26; // esi
  int v27; // eax
  char *v28; // edx
  char *v29; // ecx
  char v30; // al
  idStr *v31; // esi
  unsigned int len; // ebp
  int v33; // eax
  char *v34; // esi
  char *v35; // edi
  char *v36; // edi
  int v37; // ecx
  const char *v38; // esi
  char *v39; // eax
  unsigned int v40; // eax
  int v41; // eax
  _BYTE *alloced; // edx
  const char *v43; // ecx
  char v44; // al
  int v45; // eax
  idDict *v46; // eax
  const idKeyValue *v47; // eax
  const char *v48; // eax
  int v49; // eax
  idDict *v50; // eax
  const idKeyValue *v51; // eax
  const char *v52; // eax
  int v53; // eax
  int v54; // esi
  int v55; // esi
  const char *v56; // eax
  int v57; // ebp
  int v58; // ebp
  int v59; // ebp
  idStr *v60; // esi
  unsigned int v61; // ebp
  int v62; // eax
  const void **v63; // esi
  unsigned int v64; // ebp
  int v65; // eax
  char *v66; // eax
  idMaterial *v67; // eax
  idMaterial *v68; // esi
  char *v69; // eax
  idUserInterface *guiActive; // ecx
  idFileSystem_vtbl *v71; // esi
  char *v72; // eax
  const char *v73; // esi
  int v74; // eax
  unsigned int v75; // eax
  char *v76; // edi
  int v77; // eax
  _BYTE *v78; // edx
  const char *v79; // ecx
  char v80; // al
  int Char; // esi
  char *v82; // [esp+8h] [ebp-32Ch]
  int v84; // [esp+10h] [ebp-324h]
  char *saveGameName; // [esp+20h] [ebp-314h]
  const char *saveGameNamea; // [esp+20h] [ebp-314h]
  idStr saveFileName; // [esp+24h] [ebp-310h] BYREF
  idStr saveName; // [esp+44h] [ebp-2F0h] BYREF
  idStr description; // [esp+64h] [ebp-2D0h] BYREF
  idStr screenshot; // [esp+88h] [ebp-2ACh] BYREF
  idStr saveGameCleaned; // [esp+A8h] [ebp-28Ch] BYREF
  idStr date; // [esp+C8h] [ebp-26Ch] BYREF
  idStr game; // [esp+E8h] [ebp-24Ch] BYREF
  idToken tok; // [esp+108h] [ebp-22Ch] BYREF
  idStr time; // [esp+158h] [ebp-1DCh] BYREF
  idStr v96; // [esp+178h] [ebp-1BCh] BYREF
  idLexer v97; // [esp+198h] [ebp-19Ch] BYREF
  idLexer v98; // [esp+260h] [ebp-D4h] BYREF
  int v99; // [esp+330h] [ebp-4h]
  void *retaddr; // [esp+334h] [ebp+0h]

  v4 = *icmd - 1;
  v5 = (char *)args;
  if ( v4 < 0 || v4 >= args->argc )
    v7 = &entityFilter;
  else
    v7 = args->argv[v4];
  if ( !idStr::Icmp(v7, "loadGame") )
  {
    v8 = (idDict *)this->guiActive->State(this->guiActive);
    Key = idDict::FindKey(v8, "loadgame_sel_0");
    if ( Key )
      data = Key->value->data;
    else
      data = "0";
    v11 = atoi(data);
    if ( v11 >= 0 && v11 < this->loadGameList.num )
      idSessionLocal::LoadGame(&sessLocal, this->loadGameList.list[v11].data);
    return 1;
  }
  if ( !idStr::Icmp(v7, "saveGame") )
  {
    v13 = (idDict *)this->guiActive->State(this->guiActive);
    v14 = idDict::FindKey(v13, "saveGameName");
    if ( v14 )
      v15 = v14->value->data;
    else
      v15 = &entityFilter;
    saveGameCleaned.len = 0;
    saveGameCleaned.alloced = 20;
    saveGameCleaned.data = saveGameCleaned.baseBuffer;
    saveGameCleaned.baseBuffer[0] = 0;
    if ( v15 )
    {
      v16 = (unsigned int)&v15[strlen(v15) + 1];
      v17 = v16 - (_DWORD)(v15 + 1);
      v18 = v16 - (_DWORD)v15;
      if ( v18 > 20 )
        idStr::ReAllocate(&saveGameCleaned, v18, 1);
      v19 = saveGameCleaned.data;
      v20 = v15;
      do
      {
        v21 = *v20;
        *v19++ = *v20++;
      }
      while ( v21 );
      saveGameCleaned.len = v17;
    }
    v99 = 0;
    idStr::ReplaceChar(&saveGameCleaned, 34, 39);
    v22 = saveGameCleaned.data;
    saveGameName = saveGameCleaned.data;
    if ( !saveGameCleaned.data || !*saveGameCleaned.data )
      goto LABEL_47;
    v23 = *icmd;
    if ( *icmd == args->argc || (*icmd = v23 + 1, v24 = idCmdArgs::Argv(args, v23), !atoi(v24)) )
    {
      saveFileName.data = saveFileName.baseBuffer;
      saveFileName.len = 0;
      saveFileName.alloced = 20;
      saveFileName.baseBuffer[0] = 0;
      v25 = (unsigned int)&v22[strlen(v22) + 1];
      v26 = v25 - (_DWORD)(v22 + 1);
      v27 = v25 - (_DWORD)v22;
      if ( v27 > 20 )
        idStr::ReAllocate(&saveFileName, v27, 1);
      v28 = saveFileName.data;
      v29 = v22;
      do
      {
        v30 = *v29;
        *v28++ = *v29++;
      }
      while ( v30 );
      saveFileName.len = v26;
      LOBYTE(v99) = 1;
      idSessionLocal::ScrubSaveGameFileName(&sessLocal, &saveFileName);
      v31 = operator+(&time, "savegames/", &saveFileName);
      len = v31->len;
      v33 = v31->len + 1;
      LOBYTE(v99) = 2;
      if ( v33 > saveFileName.alloced )
        idStr::ReAllocate(&saveFileName, v33, 0);
      v34 = v31->data;
      v35 = saveFileName.data;
      qmemcpy(saveFileName.data, v34, 4 * (len >> 2));
      v36 = &v35[4 * (len >> 2)];
      v37 = len & 3;
      qmemcpy(v36, &v34[4 * (len >> 2)], v37);
      v5 = &v36[v37];
      saveFileName.data[len] = 0;
      saveFileName.len = len;
      LOBYTE(v99) = 1;
      idStr::FreeData(&time);
      idStr::SetFileExtension(&saveFileName, ".save");
      v38 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, int))cvarSystem->GetCVarString)(
                            cvarSystem,
                            "fs_game",
                            a2);
      v39 = 0;
      game.data = 0;
      *(_DWORD *)game.baseBuffer = 20;
      game.alloced = (int)&game.baseBuffer[4];
      game.baseBuffer[4] = 0;
      if ( v38 )
      {
        v40 = (unsigned int)&v38[strlen(v38) + 1];
        v5 = (char *)(v40 - (_DWORD)(v38 + 1));
        v41 = v40 - (_DWORD)v38;
        if ( v41 > 20 )
          idStr::ReAllocate((idStr *)&game.data, v41, 1);
        alloced = (_BYTE *)game.alloced;
        v43 = v38;
        do
        {
          v44 = *v43;
          *alloced++ = *v43++;
        }
        while ( v44 );
        v39 = v5;
        game.data = v5;
      }
      LOBYTE(retaddr) = 3;
      if ( v39 )
        v84 = game.alloced;
      else
        v84 = 0;
      v45 = ((int (__stdcall *)(int, int))fileSystem->OpenFileRead)(saveFileName.alloced, 1);
      if ( v45 )
      {
        ((void (__thiscall *)(idFileSystem *, int, int))fileSystem->CloseFile)(fileSystem, v45, v84);
        idStr::SetFileExtension((idStr *)&saveFileName.data, ".txt");
        idLexer::idLexer((idLexer *)&v97.filename, 9);
        LOBYTE(retaddr) = 4;
        if ( idLexer::LoadFile((idLexer *)&v97.filename, (const char *)saveFileName.alloced, 0) )
        {
          *(double *)((char *)&tok.floatvalue + 4) = 0.0;
          tok.data = 0;
          *(_DWORD *)tok.baseBuffer = 20;
          tok.alloced = (int)&tok.baseBuffer[4];
          tok.baseBuffer[4] = 0;
          LOBYTE(retaddr) = 5;
          idLexer::ReadToken((idLexer *)&v97.filename, (idToken *)&tok.data);
          idLexer::ReadToken((idLexer *)&v97.filename, (idToken *)&tok.data);
          idLexer::ReadToken((idLexer *)&v97.filename, (idToken *)&tok.data);
          idLexer::ReadToken((idLexer *)&v97.filename, (idToken *)&tok.data);
          if ( !idStr::Icmp((const char *)tok.alloced, "nooverwrite") )
          {
            this->guiActive->HandleNamedEvent(this->guiActive, "autosaveOverwriteError");
            LOBYTE(v99) = 4;
            idStr::FreeData(&tok);
LABEL_46:
            LOBYTE(v99) = 3;
            idLexer::~idLexer(&v97);
            LOBYTE(v99) = 1;
            idStr::FreeData(&game);
            LOBYTE(v99) = 0;
            idStr::FreeData(&saveFileName);
LABEL_47:
            v99 = -1;
            idStr::FreeData(&saveGameCleaned);
            return 1;
          }
          LOBYTE(retaddr) = 4;
          idStr::FreeData((idStr *)&tok.data);
        }
        this->guiActive->HandleNamedEvent(this->guiActive, "saveGameOverwrite");
        goto LABEL_46;
      }
      LOBYTE(v99) = 1;
      idStr::FreeData(&game);
      LOBYTE(v99) = 0;
      idStr::FreeData(&saveFileName);
      v22 = saveGameName;
    }
    idSessionLocal::SaveGame(&sessLocal, v22, ST_REGULAR);
    idSessionLocal::SetSaveGameGuiVars(this, (int)v5, 0);
    this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
    goto LABEL_47;
  }
  if ( !idStr::Icmp(v7, "deleteGame") )
  {
    v46 = (idDict *)this->guiActive->State(this->guiActive);
    v47 = idDict::FindKey(v46, "loadgame_sel_0");
    if ( v47 )
      v48 = v47->value->data;
    else
      v48 = "0";
    v49 = atoi(v48);
    if ( v49 >= 0 && v49 < this->loadGameList.num )
    {
      idSessionLocal::DeleteGame(&sessLocal, this->loadGameList.list[v49].data);
      idSessionLocal::SetSaveGameGuiVars(this, (int)args, 0);
      this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
      return 1;
    }
    return 1;
  }
  if ( idStr::Icmp(v7, "updateSaveGameInfo") )
    return 0;
  v50 = (idDict *)this->guiActive->State(this->guiActive);
  v51 = idDict::FindKey(v50, "loadgame_sel_0");
  if ( v51 )
    v52 = v51->value->data;
  else
    v52 = "0";
  v53 = atoi(v52);
  v54 = v53;
  if ( v53 < 0 || v53 >= this->loadGameList.num )
    return 1;
  saveName.len = 0;
  saveName.alloced = 20;
  saveName.data = saveName.baseBuffer;
  saveName.baseBuffer[0] = 0;
  v99 = 8;
  description.len = 0;
  description.alloced = 20;
  description.data = description.baseBuffer;
  description.baseBuffer[0] = 0;
  screenshot.len = 0;
  screenshot.alloced = 20;
  screenshot.data = screenshot.baseBuffer;
  screenshot.baseBuffer[0] = 0;
  idLexer::idLexer(&v98, 9);
  v55 = v54;
  v82 = this->loadGameList.list[v55].data;
  LOBYTE(v99) = 9;
  saveGameNamea = (const char *)(v55 * 32);
  v56 = va("savegames/%s.txt", v82);
  if ( idLexer::LoadFile(&v98, v56, 0) )
  {
    tok.floatvalue = 0.0;
    tok.len = 0;
    tok.alloced = 20;
    tok.data = tok.baseBuffer;
    tok.baseBuffer[0] = 0;
    LOBYTE(v99) = 10;
    idLexer::ReadToken(&v98, &tok);
    v57 = tok.len;
    if ( tok.len + 1 > saveName.alloced )
      idStr::ReAllocate(&saveName, tok.len + 1, 0);
    qmemcpy(saveName.data, tok.data, v57);
    saveName.data[v57] = 0;
    saveName.len = v57;
    idLexer::ReadToken(&v98, &tok);
    v58 = tok.len;
    if ( tok.len + 1 > description.alloced )
      idStr::ReAllocate(&description, tok.len + 1, 0);
    qmemcpy(description.data, tok.data, v58);
    description.data[v58] = 0;
    description.len = v58;
    idLexer::ReadToken(&v98, &tok);
    v59 = tok.len;
    if ( tok.len + 1 > screenshot.alloced )
      idStr::ReAllocate(&screenshot, tok.len + 1, 0);
    qmemcpy(screenshot.data, tok.data, v59);
    screenshot.data[v59] = 0;
    screenshot.len = v59;
    LOBYTE(v99) = 9;
    idStr::FreeData(&tok);
  }
  else
  {
    v60 = &this->loadGameList.list[v55];
    v61 = v60->len;
    v62 = v60->len + 1;
    if ( v62 > saveName.alloced )
      idStr::ReAllocate(&saveName, v62, 0);
    qmemcpy(saveName.data, v60->data, v61);
    saveName.data[v61] = 0;
    v63 = (const void **)&saveGameNamea[(unsigned int)this->loadGameList.list];
    saveName.len = v61;
    v64 = (unsigned int)*v63;
    v65 = (int)*v63 + 1;
    if ( v65 > description.alloced )
      idStr::ReAllocate(&description, v65, 0);
    qmemcpy(description.data, v63[1], v64);
    description.data[v64] = 0;
    description.len = v64;
    idStr::operator=(&screenshot, (char *)&entityFilter);
  }
  if ( !screenshot.len )
  {
    v66 = va("savegames/%s.tga", *(const char **)((char *)&this->loadGameList.list->data + (unsigned int)saveGameNamea));
    idStr::operator=(&screenshot, v66);
  }
  v67 = (idMaterial *)((int (__thiscall *)(idDeclManager *, char *, int, int))declManager->FindMaterial)(
                        declManager,
                        screenshot.data,
                        1,
                        a2);
  v68 = v67;
  if ( v67 )
    idMaterial::ReloadImages(v67, 0);
  this->guiActive->SetStateString(this->guiActive, "loadgame_shot", (const char *)screenshot.alloced);
  v68->sort = -2.0;
  idStr::RemoveEscapes((char *)saveName.alloced, 30);
  v69 = 0;
  if ( *(_BYTE *)saveName.alloced )
  {
    do
      ++v69;
    while ( v69[saveName.alloced] );
  }
  guiActive = this->guiActive;
  saveName.data = v69;
  guiActive->SetStateString(guiActive, "saveGameName", (const char *)saveName.alloced);
  this->guiActive->SetStateString(this->guiActive, "saveGameDescription", (const char *)description.alloced);
  v71 = fileSystem->__vftable;
  v72 = va("savegames/%s.save", *(const char **)((char *)&this->loadGameList.list->data + saveFileName.len));
  v71->ReadFile(fileSystem, v72, 0, (unsigned int *)&screenshot);
  v73 = Sys_TimeStampToStr(screenshot.len);
  v74 = 0;
  date.data = 0;
  *(_DWORD *)date.baseBuffer = 20;
  date.alloced = (int)&date.baseBuffer[4];
  date.baseBuffer[4] = 0;
  if ( v73 )
  {
    v75 = (unsigned int)&v73[strlen(v73) + 1];
    v76 = (char *)(v75 - (_DWORD)(v73 + 1));
    v77 = v75 - (_DWORD)v73;
    if ( v77 > 20 )
      idStr::ReAllocate((idStr *)&date.data, v77, 1);
    v78 = (_BYTE *)date.alloced;
    v79 = v73;
    do
    {
      v80 = *v79;
      *v78++ = *v79++;
    }
    while ( v80 );
    v74 = (int)v76;
    date.data = v76;
  }
  Char = idStr::FindChar((const char *)date.alloced, 9, 0, v74);
  idStr::Right((idStr *)&date.data, (idStr *)&time.data, (int)&date.data[-Char - 1]);
  idStr::Left((idStr *)&date.data, (idStr *)&v96.data, Char);
  LOBYTE(retaddr) = 13;
  ((void (__thiscall *)(idUserInterface *, const char *))this->guiActive->SetStateString)(
    this->guiActive,
    "saveGameDate");
  LOBYTE(v99) = 12;
  idStr::FreeData(&v96);
  this->guiActive->SetStateString(this->guiActive, "saveGameTime", time.data);
  LOBYTE(v99) = 11;
  idStr::FreeData(&time);
  LOBYTE(v99) = 9;
  idStr::FreeData(&date);
  LOBYTE(v99) = 8;
  idLexer::~idLexer(&v98);
  LOBYTE(v99) = 7;
  idStr::FreeData(&screenshot);
  LOBYTE(v99) = 6;
  idStr::FreeData(&description);
  v99 = -1;
  idStr::FreeData(&saveName);
  return 1;
}

// FUNC: public: void __thiscall idSessionLocal::HandleRestartMenuCommands(char const *)
void __userpurge idSessionLocal::HandleRestartMenuCommands(
        idSessionLocal *this@<ecx>,
        const char *a2@<ebp>,
        const char *menuCommand)
{
  int v3; // edi
  idSessionLocal *v4; // ebx
  int argc; // ecx
  const char *v6; // esi
  idDict *p_serverInfo; // esi
  const idKeyValue *Key; // eax
  const char *v9; // ebx
  const idKeyValue *v10; // eax
  const char *v11; // esi
  unsigned int v12; // eax
  int v13; // edi
  int v14; // eax
  char *v15; // edx
  const char *v16; // ecx
  char v17; // al
  idSessionLocal *v18; // esi
  int lastCheckPoint; // eax
  char *v20; // eax
  const char *v21; // esi
  unsigned int v22; // eax
  int v23; // eax
  char *data; // edx
  const char *v25; // ecx
  char v26; // al
  idSoundSystem_vtbl *v27; // edx
  int icmd; // [esp+8h] [ebp-958h] BYREF
  idSessionLocal *v29; // [esp+Ch] [ebp-954h]
  idStr loadName; // [esp+10h] [ebp-950h] BYREF
  idStr snd; // [esp+30h] [ebp-930h] BYREF
  idCmdArgs args; // [esp+50h] [ebp-910h] BYREF
  int v33; // [esp+95Ch] [ebp-4h]

  v3 = 0;
  v4 = this;
  v29 = this;
  args.argc = 0;
  idCmdArgs::TokenizeString(&args, menuCommand, 0);
  argc = args.argc;
  if ( args.argc > 0 )
  {
    do
    {
      icmd = v3 + 1;
      if ( v3 < 0 || v3 >= argc )
        v6 = &entityFilter;
      else
        v6 = args.argv[v3];
      if ( !idSessionLocal::HandleSaveGameMenuCommand(v4, (int)a2, &args, &icmd) )
      {
        if ( idStr::Icmp(v6, "restart") )
        {
          if ( !idStr::Icmp(v6, "quit") )
          {
            v4->ExitMenu(v4);
            (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 12))(common.type);
            return;
          }
          if ( !idStr::Icmp(v6, "exec") )
          {
            v3 = icmd + 1;
            if ( icmd < 0 || icmd >= args.argc )
              cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, &entityFilter);
            else
              cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, args.argv[icmd]);
            goto LABEL_26;
          }
          if ( !idStr::Icmp(v6, "play") )
          {
            v3 = icmd;
            if ( args.argc - icmd >= 1 )
            {
              v3 = icmd + 1;
              if ( icmd < 0 || icmd >= args.argc )
                v21 = &entityFilter;
              else
                v21 = args.argv[icmd];
              snd.len = 0;
              snd.alloced = 20;
              snd.data = snd.baseBuffer;
              snd.baseBuffer[0] = 0;
              if ( v21 )
              {
                v22 = (unsigned int)&v21[strlen(v21) + 1];
                a2 = (const char *)(v22 - (_DWORD)(v21 + 1));
                v23 = v22 - (_DWORD)v21;
                if ( v23 > 20 )
                  idStr::ReAllocate(&snd, v23, 1);
                data = snd.data;
                v25 = v21;
                do
                {
                  v26 = *v25;
                  *data++ = *v25++;
                }
                while ( v26 );
                v4 = v29;
                snd.len = (int)a2;
              }
              v27 = soundSystem->__vftable;
              v33 = 1;
              v27->PlayShaderDirectly(soundSystem, 1, snd.data, -1);
              v33 = -1;
              idStr::FreeData(&snd);
            }
            goto LABEL_26;
          }
          if ( idStr::Icmp(v6, "disconnect") )
          {
            if ( !idStr::Icmp(v6, "mainMenu") )
            {
              v3 = icmd;
              if ( args.argc - icmd < 1 || (v3 = icmd + 1, icmd < 0) || icmd >= args.argc )
                v4->StartMenu(v4, &entityFilter);
              else
                v4->StartMenu(v4, args.argv[icmd]);
              goto LABEL_26;
            }
          }
          else
          {
            cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "disconnect\n");
          }
        }
        else
        {
          p_serverInfo = &v4->mapSpawnData.serverInfo;
          Key = idDict::FindKey(&v4->mapSpawnData.serverInfo, "si_map");
          if ( Key )
            v9 = Key->value->data;
          else
            v9 = &entityFilter;
          v10 = idDict::FindKey(p_serverInfo, "si_entityFilter");
          if ( v10 )
            a2 = v10->value->data;
          else
            a2 = &entityFilter;
          v11 = va("Autosave %s %s", v9, a2);
          loadName.len = 0;
          loadName.alloced = 20;
          loadName.data = loadName.baseBuffer;
          loadName.baseBuffer[0] = 0;
          if ( v11 )
          {
            v12 = (unsigned int)&v11[strlen(v11) + 1];
            v13 = v12 - (_DWORD)(v11 + 1);
            v14 = v12 - (_DWORD)v11;
            if ( v14 > 20 )
              idStr::ReAllocate(&loadName, v14, 1);
            v15 = loadName.data;
            v16 = v11;
            do
            {
              v17 = *v16;
              *v15++ = *v16++;
            }
            while ( v17 );
            loadName.len = v13;
          }
          v18 = v29;
          lastCheckPoint = v29->lastCheckPoint;
          v33 = 0;
          if ( lastCheckPoint == -1
            || (v20 = va("Checkpoint%d", lastCheckPoint),
                idStr::operator=(&loadName, v20),
                !idSessionLocal::LoadGame(v18, loadName.data)) )
          {
            if ( !idSessionLocal::LoadGame(v18, loadName.data) )
              idSessionLocal::MoveToNewMap(v18, (int)a2, v9, a2);
          }
          v33 = -1;
          idStr::FreeData(&loadName);
          v4 = v29;
        }
      }
      v3 = icmd;
LABEL_26:
      argc = args.argc;
    }
    while ( v3 < args.argc );
  }
}

// FUNC: public: void __thiscall idSessionLocal::HandleMainMenuCommands(char const *)
// local variable allocation has failed, the output may be wrong!
void __userpurge idSessionLocal::HandleMainMenuCommands(
        idSessionLocal *this@<ecx>,
        int matched@<esi>,
        const char *menuCommand)
{
  idSessionLocal *v3; // edi
  int argc; // edx
  int v5; // ecx
  const char *v6; // ebp
  const char *v7; // eax
  int v8; // ecx
  const char *v9; // ebx
  int v10; // eax
  int v11; // eax
  bool v12; // sf
  char *v13; // eax
  int v14; // eax
  char *v15; // eax
  const char *v16; // esi
  unsigned int v17; // eax
  int v18; // ebx
  int v19; // eax
  char *data; // edx
  const char *v21; // ecx
  char v22; // al
  const idKeyValue *Key; // eax
  const char *v24; // esi
  int v25; // edi
  int v26; // eax
  char v27; // cl
  char *v28; // edx
  int v29; // edi
  char v30; // cl
  int i; // eax
  char *v32; // edx
  idUserInterface_vtbl *v33; // ebx
  char *v34; // eax
  idDict *v35; // eax
  const idKeyValue *v36; // eax
  const char *v37; // eax
  int v38; // eax
  int v39; // eax
  idDict *v40; // eax
  const idKeyValue *v41; // eax
  const char *v42; // eax
  int v43; // eax
  idDict *v44; // eax
  const idKeyValue *v45; // eax
  const char *v46; // eax
  idDict *v47; // eax
  const idKeyValue *v48; // eax
  const char *v49; // eax
  int v50; // eax
  idDict *v51; // eax
  const idKeyValue *v52; // eax
  const char *v53; // eax
  int v54; // eax
  bool IsAFavorite; // al
  rvServerScanGUI *p_serverScanGUI; // ecx
  idDict *v57; // eax
  const idKeyValue *v58; // eax
  const char *v59; // eax
  int v60; // eax
  int v61; // eax
  bool v62; // al
  int v63; // edx
  int v64; // eax
  idDict *v65; // eax
  const idKeyValue *v66; // eax
  const char *v67; // eax
  int v68; // eax
  idSessionLocal_vtbl *v69; // ebx
  int v70; // eax
  int v71; // eax
  const char *v72; // eax
  idCmdSystem_vtbl *v73; // edi
  char *v74; // eax
  const char *v75; // eax
  const char *v76; // eax
  int v77; // ebx
  char *v78; // edx
  char *v79; // ecx
  char v80; // al
  idListGUI *guiMainMenu_MapList; // ecx
  idListGUI_vtbl *v82; // edx
  int j; // ebx
  idDict *v84; // eax
  idDict *v85; // ebp
  const idKeyValue *v86; // eax
  const char *v87; // eax
  const idKeyValue *v88; // eax
  const char *v89; // eax
  const idKeyValue *v90; // eax
  unsigned int v91; // eax
  int v92; // ebx
  int v93; // eax
  char *v94; // edx
  char *v95; // ecx
  char v96; // al
  idListGUI *v97; // ecx
  idListGUI_vtbl *v98; // edx
  const idKeyValue *v99; // eax
  const char *v100; // eax
  int v101; // eax
  int v102; // eax
  idDict *v103; // eax
  const idKeyValue *v104; // eax
  const char *v105; // eax
  int v106; // eax
  idDict *v107; // eax
  const idKeyValue *v108; // eax
  const char *v109; // eax
  idDict *v110; // eax
  const idKeyValue *v111; // eax
  const char *v112; // eax
  int v113; // eax
  const char *v114; // eax
  char *v115; // eax
  idDict *v116; // eax
  const idKeyValue *v117; // eax
  const char *v118; // eax
  int v119; // eax
  idDict *v120; // eax
  const idKeyValue *v121; // eax
  const char *v122; // eax
  int v123; // eax
  idUserInterface *guiActive; // ecx
  idDict *v125; // eax
  const idKeyValue *v126; // eax
  idDict *v127; // eax
  const idKeyValue *v128; // eax
  const char *v129; // eax
  int v130; // eax
  idFileSystem_vtbl *v131; // edx
  idFileList *v132; // ebp
  idStr *v133; // ebx
  int v134; // esi
  const char **p_data; // edi
  int v136; // edi
  _DWORD *v137; // eax
  idStr *v138; // esi
  idStr *v139; // eax
  char **v140; // ebp
  unsigned int v141; // ebx
  int v142; // edx
  int v143; // ecx
  int v144; // esi
  int v145; // ebx
  int *v146; // eax
  idStr *v147; // edi
  idStr *v148; // eax
  char **v149; // ebp
  unsigned int v150; // ebx
  int v151; // eax
  int v152; // esi
  unsigned int v153; // ebp
  idStr *v154; // ebx
  int v155; // eax
  idFileList *v156; // ebx
  int v157; // ebp
  int *v158; // esi
  int v159; // edi
  int v160; // eax
  char *v161; // esi
  char *v162; // ecx
  char v163; // al
  int v164; // esi
  const char **v165; // edi
  int v166; // edi
  _DWORD *v167; // eax
  idStr *v168; // esi
  idStr *v169; // eax
  char **v170; // ebp
  unsigned int v171; // ebx
  int v172; // edx
  int v173; // ecx
  int v174; // esi
  int v175; // ebx
  int *v176; // eax
  idStr *v177; // edi
  idStr *v178; // eax
  char **v179; // ebp
  unsigned int v180; // ebx
  int v181; // eax
  int len; // ebp
  idStr *v183; // ebx
  const char *v184; // eax
  const char *v185; // esi
  int v186; // edi
  char *v187; // edx
  char *v188; // ecx
  char v189; // al
  int v190; // esi
  const char **v191; // edi
  int v192; // edi
  int v193; // ebx
  _DWORD *v194; // eax
  idStr *v195; // esi
  idStr *v196; // eax
  char **v197; // ebp
  unsigned int v198; // ebx
  int v199; // edx
  int v200; // esi
  int v201; // ebx
  int *v202; // eax
  idStr *v203; // edi
  idStr *v204; // eax
  char **v205; // ebp
  unsigned int v206; // ebx
  int v207; // eax
  idStr *v208; // ebx
  int v209; // ebp
  idFileList *v210; // eax
  int *v211; // esi
  int v212; // edi
  int v213; // eax
  char *v214; // esi
  char *v215; // ecx
  char v216; // al
  const char *v217; // eax
  const char *v218; // esi
  int v219; // edi
  char *v220; // edx
  char *v221; // ecx
  char v222; // al
  int v223; // esi
  const char **v224; // edi
  int v225; // edi
  int v226; // ebx
  _DWORD *v227; // eax
  idStr *v228; // esi
  idStr *v229; // eax
  char **v230; // ebp
  unsigned int v231; // ebx
  int v232; // edx
  int v233; // esi
  int v234; // ebx
  int *v235; // eax
  idStr *v236; // edi
  idStr *v237; // eax
  char **v238; // ebp
  unsigned int v239; // ebx
  int v240; // eax
  idStr *v241; // ebx
  int v242; // ebp
  const char *v243; // esi
  unsigned int v244; // eax
  int v245; // edi
  int v246; // eax
  char *v247; // edx
  const char *v248; // ecx
  char v249; // al
  int v250; // esi
  const char **v251; // edi
  int v252; // edi
  int v253; // ebx
  _DWORD *v254; // eax
  idStr *v255; // esi
  idStr *v256; // eax
  char **v257; // ebp
  unsigned int v258; // ebx
  int v259; // edx
  int v260; // esi
  int v261; // ebx
  int *v262; // eax
  idStr *v263; // edi
  idStr *v264; // eax
  char **v265; // ebp
  unsigned int v266; // ebx
  int v267; // eax
  idStr *v268; // ebx
  int v269; // ebp
  idFileList *v270; // eax
  int *v271; // esi
  int v272; // edi
  int v273; // eax
  char *v274; // esi
  char *v275; // ecx
  char v276; // al
  const char *v277; // eax
  const char *v278; // esi
  int v279; // edi
  char *v280; // edx
  char *v281; // ecx
  char v282; // al
  int v283; // esi
  const char **v284; // edi
  int v285; // edi
  int v286; // ebx
  _DWORD *v287; // eax
  idStr *v288; // esi
  idStr *v289; // eax
  char **v290; // ebp
  unsigned int v291; // ebx
  int v292; // edx
  int v293; // esi
  int v294; // ebx
  int *v295; // eax
  idStr *v296; // edi
  idStr *v297; // eax
  char **v298; // ebp
  unsigned int v299; // ebx
  int v300; // eax
  idStr *v301; // ebx
  int v302; // ebp
  const char *v303; // esi
  unsigned int v304; // eax
  int v305; // edi
  int v306; // eax
  char *v307; // edx
  const char *v308; // ecx
  char v309; // al
  int v310; // esi
  const char **v311; // edi
  int v312; // edi
  int v313; // ebx
  _DWORD *v314; // eax
  idStr *v315; // esi
  idStr *v316; // eax
  char **v317; // ebp
  unsigned int v318; // ebx
  int v319; // edx
  int v320; // esi
  int v321; // ebx
  int *v322; // eax
  idStr *v323; // edi
  idStr *v324; // eax
  char **v325; // ebp
  unsigned int v326; // ebx
  int v327; // eax
  idStr *v328; // ebx
  int v329; // ebp
  int *v330; // esi
  int v331; // edi
  int v332; // eax
  char *v333; // esi
  char *v334; // ecx
  char v335; // al
  const char *v336; // esi
  unsigned int v337; // eax
  int v338; // edi
  int v339; // eax
  char *v340; // edx
  const char *v341; // ecx
  char v342; // al
  int v343; // esi
  const char **v344; // edi
  int v345; // edi
  _DWORD *v346; // eax
  idStr *v347; // esi
  idStr *v348; // eax
  char **v349; // ebp
  unsigned int v350; // ebx
  int v351; // edx
  int v352; // ecx
  int v353; // esi
  int v354; // ebx
  int *v355; // eax
  idStr *v356; // edi
  idStr *v357; // eax
  char **v358; // ebp
  unsigned int v359; // ebx
  int v360; // eax
  idStr *v361; // ebx
  int v362; // ebp
  int v363; // esi
  void *v364; // eax
  int v365; // ecx
  idStr *v366; // edx
  idStr *v367; // ecx
  int v368; // ebp
  int *v369; // eax
  idStr *v370; // ebx
  int v371; // edx
  int v372; // ebx
  idStr *v373; // ebp
  int *v374; // eax
  idStr *v375; // esi
  idStr *v376; // eax
  char **v377; // ebx
  unsigned int v378; // ebp
  int v379; // eax
  char **v380; // ebx
  int v381; // esi
  unsigned int v382; // ebp
  int v383; // eax
  int v384; // ecx
  idStr *v385; // esi
  idStr *v386; // ebp
  idSessionLocal *v387; // ebx
  int v388; // eax
  idUserInterface_vtbl *v389; // ebp
  char *v390; // eax
  char *v391; // eax
  idDict *v392; // eax
  const idKeyValue *v393; // eax
  const char *v394; // eax
  int v395; // eax
  idDict *v396; // eax
  const idKeyValue *v397; // eax
  const char *v398; // eax
  idDict *v399; // eax
  const idKeyValue *v400; // eax
  const char *v401; // eax
  idCmdSystem_vtbl *v402; // esi
  char *v403; // eax
  const char *v404; // eax
  int v405; // ebx
  char *v406; // edx
  char *v407; // ecx
  char v408; // al
  const idDecl *v409; // ebx
  int v410; // eax
  const char *v411; // eax
  const char *v412; // eax
  const char *v413; // esi
  int v414; // ebp
  char *v415; // ecx
  char v416; // al
  idDict *v417; // ebx
  const idKeyValue *v418; // ebp
  const idKeyValue *v419; // edi
  const idKeyValue *v420; // eax
  const idKeyValue *k; // eax
  int v422; // edi
  int v423; // eax
  char *v424; // ecx
  char *v425; // edx
  char v426; // al
  idUserInterface *guiMainMenu; // ecx
  idUserInterface_vtbl *v428; // eax
  BOOL v429; // ebp
  const char *v430; // eax
  const char *v431; // eax
  int v432; // ebx
  int v433; // eax
  idSessionLocal_vtbl *v434; // ebx
  int v435; // eax
  const char *v436; // eax
  char *v437; // eax
  const idDecl *v438; // edi
  int v439; // ebx
  int v440; // ebp
  idDeclBase *v441; // esi
  long double v442; // st7
  const idDecl *v443; // edi
  int v444; // ebx
  idDeclBase *v445; // esi
  long double v446; // st7
  const char *v447; // eax
  idSessionLocal_vtbl *v448; // edi
  int v449; // eax
  const char *v450; // eax
  char *v451; // eax
  int v452; // eax
  idUserInterface_vtbl *v453; // esi
  char *v454; // eax
  int v455; // eax
  char *v456; // esi
  unsigned int v457; // eax
  int v458; // edi
  int v459; // eax
  char *v460; // ecx
  char v461; // al
  idStr *v462; // esi
  unsigned int v463; // ebx
  int v464; // eax
  unsigned int v465; // eax
  int v466; // ebx
  int v467; // eax
  char *v468; // edx
  char *v469; // ecx
  char v470; // al
  idCmdSystem_vtbl *v471; // edx
  int v472; // esi
  const char *v473; // eax
  int v474; // ebp
  const char *v475; // eax
  int v476; // ebx
  char *v477; // edx
  char *v478; // ecx
  char v479; // al
  int v480; // ecx
  const char *v481; // esi
  int v482; // eax
  unsigned int v483; // eax
  int v484; // ebx
  int v485; // eax
  char *v486; // edx
  const char *v487; // ecx
  char v488; // al
  int v489; // eax
  char *v490; // eax
  int v491; // ecx
  const char *v492; // eax
  int v493; // ebx
  char *v494; // edx
  char *v495; // ecx
  char v496; // al
  idSoundSystem_vtbl *v497; // edx
  int v498; // ecx
  char *v499; // eax
  int v500; // eax
  int v501; // eax
  int v502; // ecx
  char *v503; // eax
  int v504; // eax
  int v505; // eax
  char v506; // cl
  const char *v507; // eax
  int v508; // edi
  int v509; // eax
  char v510; // cl
  int v511; // edi
  char v512; // cl
  int m; // eax
  int v514; // ecx
  const char *v515; // eax
  idDict *v516; // eax
  const idKeyValue *v517; // eax
  const char *v518; // esi
  int v519; // edi
  unsigned int v520; // eax
  int v521; // eax
  char *v522; // edx
  const char *v523; // ecx
  char v524; // al
  int v525; // eax
  char v526; // cl
  char *v527; // edx
  const char *v528; // eax
  const char *v529; // esi
  int v530; // ebx
  char *v531; // edx
  char *v532; // ecx
  char v533; // al
  idCVarSystem_vtbl *v534; // edx
  const char *v535; // esi
  unsigned int v536; // eax
  int v537; // ebx
  int v538; // eax
  char *v539; // edx
  const char *v540; // ecx
  char v541; // al
  idCmdSystem_vtbl *v542; // ebp
  int v543; // ebx
  const char *v544; // eax
  const char *v545; // eax
  int v546; // eax
  int v547; // eax
  bool v548; // bl
  const char *v549; // ecx
  bool v550; // zf
  int v551; // eax
  int v552; // eax
  bool v553; // bl
  const char *v554; // ecx
  idUserInterface *v555; // ecx
  int v556; // eax
  bool v557; // bl
  const char *v558; // ecx
  idUserInterface *v559; // ecx
  int v560; // eax
  bool v561; // bl
  const char *v562; // ecx
  int v563; // ecx
  char *v564; // eax
  const char *v565; // eax
  const char *v566; // eax
  idCVarSystem_vtbl *v567; // esi
  int v568; // eax
  netadr_t v569; // [esp+FCh] [ebp-D00h]
  int v570; // [esp+FCh] [ebp-D00h]
  int v571; // [esp+FCh] [ebp-D00h]
  int v572; // [esp+100h] [ebp-CFCh]
  int v573; // [esp+100h] [ebp-CFCh]
  char *v574; // [esp+104h] [ebp-CF8h]
  int v575; // [esp+104h] [ebp-CF8h]
  int v576; // [esp+104h] [ebp-CF8h]
  int v577; // [esp+104h] [ebp-CF8h]
  int v578; // [esp+104h] [ebp-CF8h]
  const char *maxPlayers; // [esp+118h] [ebp-CE4h]
  int maxPlayersa; // [esp+118h] [ebp-CE4h]
  int maxPlayersb; // [esp+118h] [ebp-CE4h]
  unsigned int *maxPlayersc; // [esp+118h] [ebp-CE4h]
  int maxPlayersd; // [esp+118h] [ebp-CE4h]
  unsigned int *maxPlayerse; // [esp+118h] [ebp-CE4h]
  int maxPlayersf; // [esp+118h] [ebp-CE4h]
  unsigned int *maxPlayersg; // [esp+118h] [ebp-CE4h]
  int maxPlayersh; // [esp+118h] [ebp-CE4h]
  unsigned int *maxPlayersi; // [esp+118h] [ebp-CE4h]
  int maxPlayersj; // [esp+118h] [ebp-CE4h]
  unsigned int *maxPlayersk; // [esp+118h] [ebp-CE4h]
  int maxPlayersl; // [esp+118h] [ebp-CE4h]
  unsigned int *maxPlayersm; // [esp+118h] [ebp-CE4h]
  int maxPlayersn; // [esp+118h] [ebp-CE4h]
  unsigned int *maxPlayerso; // [esp+118h] [ebp-CE4h]
  unsigned int *maxPlayersp; // [esp+118h] [ebp-CE4h]
  int maxPlayersq; // [esp+118h] [ebp-CE4h]
  char **maxPlayersr; // [esp+118h] [ebp-CE4h]
  int maxPlayerss; // [esp+118h] [ebp-CE4h]
  int fileList; // [esp+11Ch] [ebp-CE0h]
  int fileLista; // [esp+11Ch] [ebp-CE0h]
  int fileList_4; // [esp+120h] [ebp-CDCh]
  idStr *fileList_12; // [esp+128h] [ebp-CD4h]
  int dedicated; // [esp+12Ch] [ebp-CD0h]
  int dedicateda; // [esp+12Ch] [ebp-CD0h]
  int dedicatedb; // [esp+12Ch] [ebp-CD0h]
  int dedicatedc; // [esp+12Ch] [ebp-CD0h]
  int dedicatedd; // [esp+12Ch] [ebp-CD0h]
  int dedicatede; // [esp+12Ch] [ebp-CD0h]
  int dedicatedf; // [esp+12Ch] [ebp-CD0h]
  int dedicatedg; // [esp+12Ch] [ebp-CD0h]
  int dedicatedh; // [esp+12Ch] [ebp-CD0h]
  int dedicatedi; // [esp+12Ch] [ebp-CD0h]
  int dedicatedj; // [esp+12Ch] [ebp-CD0h]
  int dedicatedk; // [esp+12Ch] [ebp-CD0h]
  int dedicatedl; // [esp+12Ch] [ebp-CD0h]
  int dedicatedm; // [esp+12Ch] [ebp-CD0h]
  int dedicatedn; // [esp+12Ch] [ebp-CD0h]
  int dedicatedo; // [esp+12Ch] [ebp-CD0h]
  int dedicatedp; // [esp+12Ch] [ebp-CD0h]
  int dedicatedq; // [esp+12Ch] [ebp-CD0h]
  int dedicatedr; // [esp+12Ch] [ebp-CD0h]
  int maxUpstream; // [esp+130h] [ebp-CCCh]
  int maxUpstreama; // [esp+130h] [ebp-CCCh]
  int maxUpstreamb; // [esp+130h] [ebp-CCCh]
  int maxUpstreamc; // [esp+130h] [ebp-CCCh]
  idFileList *maxUpstreamd; // [esp+130h] [ebp-CCCh]
  int maxUpstreame; // [esp+130h] [ebp-CCCh]
  idFileList *maxUpstreamf; // [esp+130h] [ebp-CCCh]
  int maxUpstreamg; // [esp+130h] [ebp-CCCh]
  idFileList *maxUpstreamh; // [esp+130h] [ebp-CCCh]
  idFileList *maxUpstreami; // [esp+130h] [ebp-CCCh]
  int maxUpstreamj; // [esp+130h] [ebp-CCCh]
  int maxBandPlayers; // [esp+134h] [ebp-CC8h]
  int maxBandPlayersa; // [esp+134h] [ebp-CC8h]
  int maxBandPlayersb; // [esp+134h] [ebp-CC8h]
  int maxBandPlayersc; // [esp+134h] [ebp-CC8h]
  int maxBandPlayersd; // [esp+134h] [ebp-CC8h]
  int maxBandPlayerse; // [esp+134h] [ebp-CC8h]
  int maxBandPlayersf; // [esp+134h] [ebp-CC8h]
  int maxBandPlayersg; // [esp+134h] [ebp-CC8h]
  int maxBandPlayersh; // [esp+134h] [ebp-CC8h]
  char maxBandPlayersi; // [esp+134h] [ebp-CC8h]
  int maxBandPlayersj; // [esp+134h] [ebp-CC8h]
  int v644; // [esp+138h] [ebp-CC4h]
  unsigned int *v645; // [esp+138h] [ebp-CC4h]
  unsigned int *v646; // [esp+138h] [ebp-CC4h]
  unsigned int *v647; // [esp+138h] [ebp-CC4h]
  unsigned int *v648; // [esp+138h] [ebp-CC4h]
  unsigned int *v649; // [esp+138h] [ebp-CC4h]
  unsigned int *v650; // [esp+138h] [ebp-CC4h]
  unsigned int *v651; // [esp+138h] [ebp-CC4h]
  unsigned int *v652; // [esp+138h] [ebp-CC4h]
  int ptr; // [esp+13Ch] [ebp-CC0h]
  idStr *ptra; // [esp+13Ch] [ebp-CC0h]
  idStr *ptrb; // [esp+13Ch] [ebp-CC0h]
  idStr *ptrc; // [esp+13Ch] [ebp-CC0h]
  idStr *ptrd; // [esp+13Ch] [ebp-CC0h]
  idStr *ptre; // [esp+13Ch] [ebp-CC0h]
  idStr *ptrf; // [esp+13Ch] [ebp-CC0h]
  idStr *ptrg; // [esp+13Ch] [ebp-CC0h]
  idStr *ptrh; // [esp+13Ch] [ebp-CC0h]
  int icmd; // [esp+140h] [ebp-CBCh] BYREF
  long double bright; // [esp+144h] [ebp-CB8h] OVERLAPPED
  idSessionLocal *v664; // [esp+14Ch] [ebp-CB0h]
  int minPlayers; // [esp+150h] [ebp-CACh]
  int v666; // [esp+154h] [ebp-CA8h]
  int v667; // [esp+158h] [ebp-CA4h]
  int v668; // [esp+15Ch] [ebp-CA0h]
  idStr *v669; // [esp+160h] [ebp-C9Ch]
  int v670; // [esp+164h] [ebp-C98h]
  int v671; // [esp+168h] [ebp-C94h]
  int v672; // [esp+16Ch] [ebp-C90h]
  void *v673; // [esp+170h] [ebp-C8Ch]
  idStr mapName; // [esp+174h] [ebp-C88h] BYREF
  idStr guid; // [esp+194h] [ebp-C68h] BYREF
  idStr temp; // [esp+1B4h] [ebp-C48h] BYREF
  idStr fixedExtension; // [esp+1D4h] [ebp-C28h] BYREF
  idStr bind; // [esp+1F4h] [ebp-C08h] BYREF
  idStr v679; // [esp+214h] [ebp-BE8h] BYREF
  idStr v680; // [esp+234h] [ebp-BC8h] BYREF
  idStr v681; // [esp+254h] [ebp-BA8h] BYREF
  idStr snd; // [esp+274h] [ebp-B88h] BYREF
  idStr v683; // [esp+294h] [ebp-B68h] BYREF
  idStr v684; // [esp+2B4h] [ebp-B48h] BYREF
  idStr v685; // [esp+2D4h] [ebp-B28h] BYREF
  idStr v686; // [esp+2F4h] [ebp-B08h] BYREF
  idStr sStr; // [esp+314h] [ebp-AE8h] BYREF
  idStr v688; // [esp+334h] [ebp-AC8h] BYREF
  idStr v689; // [esp+354h] [ebp-AA8h] BYREF
  idStr v690; // [esp+374h] [ebp-A88h] BYREF
  idStr newCrosshair; // [esp+394h] [ebp-A68h] BYREF
  netadr_t friendServer; // [esp+3B4h] [ebp-A48h] BYREF
  idStr currentCrosshair; // [esp+3C0h] [ebp-A3Ch] BYREF
  idStr v694; // [esp+3E0h] [ebp-A1Ch] BYREF
  idStr vcmd; // [esp+400h] [ebp-9FCh] BYREF
  idStr si_map; // [esp+420h] [ebp-9DCh] BYREF
  idStr v697; // [esp+440h] [ebp-9BCh] BYREF
  idStr lastQuickSave; // [esp+460h] [ebp-99Ch] BYREF
  idStr lang; // [esp+480h] [ebp-97Ch] BYREF
  idStr v700; // [esp+4A0h] [ebp-95Ch] BYREF
  idStr v701; // [esp+4C0h] [ebp-93Ch] BYREF
  netadr_t result; // [esp+4E0h] [ebp-91Ch] BYREF
  idCmdArgs args; // [esp+4ECh] [ebp-910h] BYREF
  int v704; // [esp+DF8h] [ebp-4h]

  v3 = this;
  v664 = this;
  args.argc = 0;
  idCmdArgs::TokenizeString(&args, menuCommand, 0);
  argc = args.argc;
  v5 = 0;
  if ( args.argc <= 0 )
    return;
  while ( 1 )
  {
    icmd = v5 + 1;
    if ( v5 < 0 || v5 >= argc )
      v6 = &entityFilter;
    else
      v6 = args.argv[v5];
    maxUpstream = (int)v6;
    if ( idSessionLocal::HandleSaveGameMenuCommand(v3, (int)v6, &args, &icmd) )
      goto LABEL_952;
    if ( !idStr::Icmp(v6, "CopyCVar") )
    {
      if ( icmd < 0 || icmd >= args.argc )
        v7 = &entityFilter;
      else
        v7 = args.argv[icmd];
      v8 = icmd + 1;
      icmd += 2;
      if ( v8 < 0 || v8 >= args.argc )
        v9 = &entityFilter;
      else
        v9 = args.argv[v8];
      matched = (int)cvarSystem->__vftable;
      v10 = ((int (__thiscall *)(idCVarSystem *, const char *, _DWORD))cvarSystem->GetCVarString)(cvarSystem, v7, 0);
      (*(void (__thiscall **)(idCVarSystem *, const char *, int))(matched + 32))(cvarSystem, v9, v10);
    }
    if ( !idStr::Icmp(v6, "SetActiveMapScreenshot") )
    {
      v11 = icmd;
      v12 = icmd++ < 0;
      if ( v12 || v11 >= args.argc )
        matched = (int)&entityFilter;
      else
        matched = (int)args.argv[v11];
      v13 = va("%s_sel_0", (const char *)matched);
      v14 = v3->guiActive->GetStateInt(v3->guiActive, v13, "-1");
      if ( v14 >= 0 )
      {
        v15 = va("%s_item_%i", (const char *)matched, v14);
        v16 = v3->guiActive->GetStateString(v3->guiActive, v15, &entityFilter);
        mapName.len = 0;
        mapName.alloced = 20;
        mapName.data = mapName.baseBuffer;
        mapName.baseBuffer[0] = 0;
        if ( v16 )
        {
          v17 = (unsigned int)&v16[strlen(v16) + 1];
          v18 = v17 - (_DWORD)(v16 + 1);
          v19 = v17 - (_DWORD)v16;
          if ( v19 > 20 )
            idStr::ReAllocate(&mapName, v19, 1);
          data = mapName.data;
          v21 = v16;
          do
          {
            v22 = *v21;
            *data++ = *v21++;
          }
          while ( v22 );
          mapName.len = v18;
        }
        v704 = 0;
        idStr::StripFileExtension(&mapName);
        Key = idDict::FindKey(&v3->mapSpawnData.serverInfo, "si_entityFilter");
        if ( Key )
        {
          v24 = Key->value->data;
          if ( !v24 )
          {
LABEL_43:
            matched = MapManager::FindByFileName(mapName.data);
            if ( MapManager::ValidIndex(matched) )
            {
              v33 = v3->guiActive->__vftable;
              v34 = MapManager::Thumbnail(matched);
              v33->SetStateString(v3->guiActive, "current_levelshot", v34);
            }
            else
            {
              v3->guiActive->SetStateString(v3->guiActive, "current_levelshot", "gfx/guis/loadscreens/generic");
            }
            v704 = -1;
            idStr::FreeData(&mapName);
            goto LABEL_48;
          }
        }
        else
        {
          v24 = &entityFilter;
        }
        if ( strlen(v24) > 1 )
        {
          v25 = mapName.len + 1;
          if ( mapName.len + 2 > mapName.alloced )
            idStr::ReAllocate(&mapName, mapName.len + 2, 1);
          v26 = 0;
          v27 = 95;
          do
          {
            v28 = &mapName.data[v26++];
            v28[mapName.len] = v27;
            v27 = asc_1029F57C[v26];
          }
          while ( v27 );
          mapName.len = v25;
          mapName.data[v25] = 0;
          v29 = strlen(v24) + mapName.len;
          if ( v29 + 1 > mapName.alloced )
            idStr::ReAllocate(&mapName, v29 + 1, 1);
          v30 = *v24;
          for ( i = 0; v30; v30 = v24[i] )
          {
            v32 = &mapName.data[i++];
            v32[mapName.len] = v30;
          }
          mapName.len = v29;
          mapName.data[v29] = 0;
          v3 = v664;
        }
        goto LABEL_43;
      }
    }
LABEL_48:
    if ( !idStr::Icmp(v6, "startGame") )
    {
      v35 = (idDict *)v3->guiMainMenu->State(v3->guiMainMenu);
      v36 = idDict::FindKey(v35, "skill");
      if ( v36 )
        v37 = v36->value->data;
      else
        v37 = "0";
      matched = (int)cvarSystem->__vftable;
      v38 = atoi(v37);
      (*(void (__thiscall **)(idCVarSystem *, const char *, int, _DWORD))(matched + 40))(cvarSystem, "g_skill", v38, 0);
      if ( icmd >= args.argc )
      {
        idSessionLocal::StartNewGame(v3, (int)v6, (int)v3, "game/mars_city1", 0, &entityFilter, 1);
      }
      else
      {
        v39 = icmd++;
        if ( v39 < 0 || v39 >= args.argc )
          idSessionLocal::StartNewGame(v3, (int)v6, (int)v3, &entityFilter, 0, &entityFilter, 1);
        else
          idSessionLocal::StartNewGame(v3, (int)v6, (int)v3, args.argv[v39], 0, &entityFilter, 1);
      }
      (*(void (__thiscall **)(netadrtype_t, _DWORD, _DWORD))(*(_DWORD *)common.type + 24))(common.type, 0, 0);
      v3->SetGUI(v3, v3->guiIntro, 0);
      v3->guiIntro->StateChanged(v3->guiIntro, com_frameTime, 1);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "quit") )
    {
      v3->ExitMenu(v3);
      (*(void (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 12))(common.type);
      return;
    }
    if ( !idStr::Icmp(v6, "loadMod") )
    {
      v40 = (idDict *)v3->guiActive->State(v3->guiActive);
      v41 = idDict::FindKey(v40, "modsList_sel_0");
      v42 = v41 ? v41->value->data : "0";
      v43 = atoi(v42);
      if ( v43 >= 0 && v43 < v3->modsList.num )
      {
        cvarSystem->SetCVarString(cvarSystem, "fs_game", v3->modsList.list[v43].data, 0);
        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "reloadEngine menu\n");
      }
    }
    if ( !idStr::Icmp(v6, "updateServers") )
    {
      v44 = (idDict *)v3->guiActive->State(v3->guiActive);
      v45 = idDict::FindKey(v44, "lanSet");
      if ( v45 )
        v46 = v45->value->data;
      else
        v46 = "0";
      if ( atoi(v46) )
        rvServerScan::LanScan(&idAsyncNetwork::client.serverList, (int)v6);
      else
        rvServerScan::NetScan(&idAsyncNetwork::client.serverList, (int)v6, &entityFilter, &entityFilter);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "refreshServers") )
    {
      rvServerScan::Refresh(&idAsyncNetwork::client.serverList);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "click_ServerList") )
    {
      v47 = (idDict *)v3->guiActive->State(v3->guiActive);
      v48 = idDict::FindKey(v47, "serverList_sel_0");
      if ( v48 )
        v49 = v48->value->data;
      else
        v49 = "0";
      v50 = atoi(v49);
      if ( v50 != -1 )
        rvServerScanGUI::ServerSelected(&v3->serverScanGUI, v50);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "ToggleFavorite") )
    {
      v51 = (idDict *)v3->guiActive->State(v3->guiActive);
      v52 = idDict::FindKey(v51, "serverList_sel_0");
      if ( v52 )
        v53 = v52->value->data;
      else
        v53 = "0";
      v54 = atoi(v53);
      matched = v54;
      if ( v54 != -1 )
      {
        IsAFavorite = rvServerScanGUI::IsAFavorite(&v3->serverScanGUI, v54);
        p_serverScanGUI = &v3->serverScanGUI;
        if ( IsAFavorite )
          rvServerScanGUI::RemoveFromFavoritesList(p_serverScanGUI, matched);
        else
          rvServerScanGUI::AddToFavoritesList(p_serverScanGUI, matched);
      }
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "InitServerBrowser") )
    {
      v57 = (idDict *)v3->guiActive->State(v3->guiActive);
      v58 = idDict::FindKey(v57, "serverList_sel_0");
      if ( v58 )
        v59 = v58->value->data;
      else
        v59 = "0";
      v60 = atoi(v59);
      if ( v60 == -1 )
      {
        matched = (int)v3->guiActive->__vftable;
        v61 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                common.type,
                "#str_200292",
                -1);
        (*(void (__thiscall **)(idUserInterface *, const char *, int))(matched + 56))(
          v3->guiActive,
          "favoriteStatus",
          v61);
        goto LABEL_952;
      }
      v62 = rvServerScanGUI::IsAFavorite(&v3->serverScanGUI, v60);
      v63 = *(_DWORD *)common.type;
      matched = (int)v3->guiActive->__vftable;
      if ( v62 )
        v64 = (*(int (__stdcall **)(const char *, int))(v63 + 168))("#str_200293", -1);
      else
        v64 = (*(int (__stdcall **)(const char *, int))(v63 + 168))("#str_200292", -1);
      (*(void (__thiscall **)(idUserInterface *, const char *, int))(matched + 56))(
        v3->guiActive,
        "favoriteStatus",
        v64);
    }
    if ( !idStr::Icmp(v6, "sortServerName") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_NAME);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "sortPlayers") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_PLAYERS);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "sortPing") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_PING);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "sortGameType") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_GAMETYPE);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "sortMap") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_MAP);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "sortFavorite") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_FAVORITE);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "sortDed") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_DEDICATED);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "sortLocked") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_LOCKED);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "sortPB") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_PB);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "server_clearSort") )
    {
      rvServerScanGUI::Sort(&v3->serverScanGUI, SC_NONE);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "connect") )
      break;
    if ( !idStr::Icmp(v6, "MAPScan") )
    {
      v75 = cvarSystem->GetCVarString(cvarSystem, "si_gameType");
      maxPlayers = v75;
      if ( !v75 || !*v75 || !idStr::Icmp(v75, "singleplayer") )
        maxPlayers = "DM";
      v76 = cvarSystem->GetCVarString(cvarSystem, "si_map");
      matched = (int)v76;
      si_map.len = 0;
      si_map.alloced = 20;
      si_map.data = si_map.baseBuffer;
      si_map.baseBuffer[0] = 0;
      if ( v76 )
      {
        v77 = strlen(v76);
        if ( v77 + 1 > 20 )
          idStr::ReAllocate(&si_map, v77 + 1, 1);
        v78 = si_map.data;
        v79 = (char *)matched;
        do
        {
          v80 = *v79;
          *v78++ = *v79++;
        }
        while ( v80 );
        si_map.len = v77;
      }
      guiMainMenu_MapList = v3->guiMainMenu_MapList;
      v82 = guiMainMenu_MapList->__vftable;
      v704 = 1;
      v82->Clear(guiMainMenu_MapList);
      v3->guiMainMenu_MapList->SetSelection(v3->guiMainMenu_MapList, 0);
      dedicated = fileSystem->GetNumMaps(fileSystem);
      maxUpstreama = 0;
      if ( dedicated > 0 )
      {
        for ( j = 0; j < dedicated; maxUpstreama = j )
        {
          v84 = (idDict *)fileSystem->GetMapDecl(fileSystem, j);
          v85 = v84;
          if ( v84 )
          {
            v86 = idDict::FindKey(v84, maxPlayers);
            v87 = v86 ? v86->value->data : "0";
            if ( atoi(v87) )
            {
              v88 = idDict::FindKey(v85, "name");
              if ( !v88 || (v89 = v88->value->data, !*v89) )
              {
                v90 = idDict::FindKey(v85, "path");
                if ( v90 )
                  v89 = v90->value->data;
                else
                  v89 = &entityFilter;
              }
              matched = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
                          common.type,
                          v89,
                          -1);
              v700.len = 0;
              v700.alloced = 20;
              v700.data = v700.baseBuffer;
              v700.baseBuffer[0] = 0;
              if ( matched )
              {
                v91 = matched + strlen((const char *)matched) + 1;
                v92 = v91 - (matched + 1);
                v93 = v91 - matched;
                if ( v93 > 20 )
                  idStr::ReAllocate(&v700, v93, 1);
                v94 = v700.data;
                v95 = (char *)matched;
                do
                {
                  v96 = *v95;
                  *v94++ = *v95++;
                }
                while ( v96 );
                v700.len = v92;
                j = maxUpstreama;
              }
              v97 = v3->guiMainMenu_MapList;
              v98 = v97->__vftable;
              LOBYTE(v704) = 2;
              v98->Add(v97, j, &v700, 0);
              LOBYTE(v704) = 1;
              idStr::FreeData(&v700);
              v99 = idDict::FindKey(v85, "path");
              if ( v99 )
                v100 = v99->value->data;
              else
                v100 = &entityFilter;
              if ( !idStr::Icmp(si_map.data, v100) )
              {
                matched = (int)v3->guiMainMenu_MapList->__vftable;
                v101 = (*(int (**)(void))(matched + 24))();
                (*(void (__thiscall **)(idListGUI *, int))(matched + 32))(v3->guiMainMenu_MapList, v101 - 1);
              }
            }
          }
          ++j;
        }
      }
      v102 = v3->guiMainMenu_MapList->GetSelection(v3->guiMainMenu_MapList, 0, 0, 0);
      if ( v102 >= 0
        && (v103 = (idDict *)fileSystem->GetMapDecl(fileSystem, v102)) != 0
        && (v104 = idDict::FindKey(v103, "path")) != 0 )
      {
        v105 = v104->value->data;
      }
      else
      {
        v105 = &entityFilter;
      }
      cvarSystem->SetCVarString(cvarSystem, "si_map", v105, 0);
      idSessionLocal::UpdateMPLevelShot(v3);
      v704 = -1;
      idStr::FreeData(&si_map);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "click_mapList") )
    {
      v106 = v3->guiMainMenu_MapList->GetSelection(v3->guiMainMenu_MapList, 0, 0, 0);
      v107 = (idDict *)fileSystem->GetMapDecl(fileSystem, v106);
      if ( v107 )
      {
        v108 = idDict::FindKey(v107, "path");
        if ( v108 )
          v109 = v108->value->data;
        else
          v109 = &entityFilter;
        cvarSystem->SetCVarString(cvarSystem, "si_map", v109, 0);
      }
      idSessionLocal::UpdateMPLevelShot(v3);
      goto LABEL_952;
    }
    if ( !idStr::Icmp(v6, "updateFriends") )
    {
      if ( !v3->CDKeysAreValid(v3, 1) && (!idSessionLocal::MaybeWaitOnCDKey(v3) || !v3->CDKeysAreValid(v3, 1)) )
      {
        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "promptKey force");
        cmdSystem->ExecuteCommandBuffer(cmdSystem);
      }
      v3->guiActive->SetStateString(v3->guiActive, "friendslist_sel_0", "-1");
      rvServerScan::FriendScan(&idAsyncNetwork::client.serverList, (int)v3);
      goto LABEL_952;
    }
    if ( idStr::Icmp(v6, "friendConnect") )
    {
      if ( idStr::Icmp(v6, "removeFriend") )
      {
        if ( !idStr::Icmp(v6, "playerClanSearch") )
        {
          v120 = (idDict *)v3->guiActive->State(v3->guiActive);
          v121 = idDict::FindKey(v120, "player_search");
          if ( v121 )
            v122 = v121->value->data;
          else
            v122 = "0";
          v123 = atoi(v122);
          guiActive = v3->guiActive;
          if ( v123 )
          {
            v125 = (idDict *)guiActive->State(guiActive);
            v126 = idDict::FindKey(v125, "playerclan_search");
            if ( v126 )
              rvServerScan::NetScan(&idAsyncNetwork::client.serverList, (int)v6, v126->value->data, &entityFilter);
            else
              rvServerScan::NetScan(&idAsyncNetwork::client.serverList, (int)v6, &entityFilter, &entityFilter);
          }
          else
          {
            v127 = (idDict *)guiActive->State(guiActive);
            v128 = idDict::FindKey(v127, "playerclan_search");
            if ( v128 )
              v129 = v128->value->data;
            else
              v129 = &entityFilter;
            rvServerScan::NetScan(&idAsyncNetwork::client.serverList, (int)v6, &entityFilter, v129);
          }
        }
        if ( !idStr::Icmp(v6, "checkMinPlayers") )
        {
          matched = cvarSystem->GetCVarInteger(cvarSystem, "si_maxPlayers");
          if ( matched < cvarSystem->GetCVarInteger(cvarSystem, "si_minPlayers") )
            cvarSystem->SetCVarInteger(cvarSystem, "si_minPlayers", matched, 0);
          goto LABEL_952;
        }
        if ( !idStr::Icmp(v6, "checkMaxPlayers") )
        {
          matched = cvarSystem->GetCVarInteger(cvarSystem, "si_maxPlayers");
          v130 = cvarSystem->GetCVarInteger(cvarSystem, "si_minPlayers");
          if ( v130 > matched )
            cvarSystem->SetCVarInteger(cvarSystem, "si_maxPlayers", v130, 0);
          goto LABEL_952;
        }
        if ( !idStr::Icmp(v6, "mapDir") )
        {
          fileList_12 = 0;
          fileList = 0;
          fileList_4 = 0;
          v131 = fileSystem->__vftable;
          v704 = 3;
          v132 = v131->ListFiles(fileSystem, "maps", ".map", 0, 0, 0);
          maxUpstreamb = (int)v132;
          maxBandPlayers = 0;
          if ( v132->list.num > 0 )
          {
            maxPlayersa = 0;
            do
            {
              v133 = &v132->list.list[maxPlayersa];
              v134 = 0;
              LODWORD(bright) = v133;
              if ( fileList <= 0 )
                goto LABEL_227;
              p_data = (const char **)&fileList_12->data;
              while ( idStr::Cmp(*p_data, v133->data) )
              {
                ++v134;
                p_data += 8;
                if ( v134 >= fileList )
                  goto LABEL_227;
              }
              if ( v134 < 0 )
              {
LABEL_227:
                if ( !fileList_12 && fileList_4 != 16 )
                {
                  v136 = fileList;
                  fileList_4 = 16;
                  if ( fileList > 16 )
                  {
                    v136 = 16;
                    fileList = 16;
                  }
                  v137 = Memory::Allocate(0x204u);
                  minPlayers = (int)v137;
                  LOBYTE(v704) = 4;
                  if ( v137 )
                  {
                    v138 = (idStr *)(v137 + 1);
                    *v137 = 16;
                    `eh vector constructor iterator'(
                      v137 + 1,
                      0x20u,
                      16,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    v139 = v138;
                  }
                  else
                  {
                    v139 = 0;
                  }
                  LOBYTE(v704) = 3;
                  fileList_12 = v139;
                  if ( v136 > 0 )
                  {
                    ptr = 4;
                    v140 = &v139->data;
                    dedicateda = -4 - (_DWORD)v139;
                    v644 = fileList;
                    do
                    {
                      v141 = *(unsigned int *)((char *)v140 + dedicateda);
                      if ( (int)(v141 + 1) > (int)v140[1] )
                        idStr::ReAllocate((idStr *)(v140 - 1), v141 + 1, 0);
                      qmemcpy(*v140, *(const void **)ptr, v141);
                      (*v140)[v141] = 0;
                      *(v140 - 1) = (char *)v141;
                      v140 += 8;
                      v550 = v644-- == 1;
                      ptr += 32;
                    }
                    while ( !v550 );
                  }
                }
                v142 = fileList_4;
                if ( fileList == fileList_4 )
                {
                  v143 = (fileList_4 + 16) % 16;
                  v144 = fileList_4 + 16 - v143;
                  if ( v144 > 0 )
                  {
                    if ( v144 != fileList_4 )
                    {
                      v145 = fileList;
                      ptra = fileList_12;
                      fileList_4 = fileList_4 + 16 - v143;
                      if ( v144 < fileList )
                      {
                        v145 = v142 + 16 - v143;
                        fileList = v145;
                      }
                      v146 = (int *)Memory::Allocate(32 * v144 + 4);
                      minPlayers = (int)v146;
                      LOBYTE(v704) = 5;
                      if ( v146 )
                      {
                        v147 = (idStr *)(v146 + 1);
                        *v146 = v144;
                        `eh vector constructor iterator'(
                          v146 + 1,
                          0x20u,
                          v144,
                          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        v148 = v147;
                      }
                      else
                      {
                        v148 = 0;
                      }
                      LOBYTE(v704) = 3;
                      fileList_12 = v148;
                      if ( v145 > 0 )
                      {
                        v645 = (unsigned int *)ptra;
                        v149 = &v148->data;
                        minPlayers = (char *)ptra - (char *)v148;
                        dedicatedb = fileList;
                        do
                        {
                          v150 = *v645;
                          v151 = *v645 + 1;
                          if ( v151 > (int)v149[1] )
                            idStr::ReAllocate((idStr *)(v149 - 1), v151, 0);
                          v645 += 8;
                          qmemcpy(*v149, *(char **)((char *)v149 + minPlayers), v150);
                          (*v149)[v150] = 0;
                          *(v149 - 1) = (char *)v150;
                          v149 += 8;
                          --dedicatedb;
                        }
                        while ( dedicatedb );
                      }
                      if ( ptra )
                      {
                        `eh vector destructor iterator'(
                          ptra,
                          0x20u,
                          *(_DWORD *)&ptra[-1].baseBuffer[16],
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        Memory::Free(&ptra[-1].baseBuffer[16]);
                      }
                    }
                  }
                  else
                  {
                    if ( fileList_12 )
                    {
                      `eh vector destructor iterator'(
                        fileList_12,
                        0x20u,
                        *(_DWORD *)&fileList_12[-1].baseBuffer[16],
                        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                      Memory::Free(&fileList_12[-1].baseBuffer[16]);
                    }
                    fileList_12 = 0;
                    fileList = 0;
                    fileList_4 = 0;
                  }
                }
                v152 = LODWORD(bright);
                v153 = *(_DWORD *)LODWORD(bright);
                v154 = &fileList_12[fileList];
                v155 = *(_DWORD *)LODWORD(bright) + 1;
                if ( v155 > v154->alloced )
                  idStr::ReAllocate(&fileList_12[fileList], v155, 0);
                qmemcpy(v154->data, *(const void **)(v152 + 4), v153);
                ++fileList;
                v154->data[v153] = 0;
                v154->len = v153;
                v132 = (idFileList *)maxUpstreamb;
              }
              ++maxPlayersa;
              ++maxBandPlayers;
            }
            while ( maxBandPlayers < v132->list.num );
          }
          fileSystem->FreeFileList(fileSystem, v132);
          v156 = fileSystem->ListFiles(fileSystem, "maps", ".mapc", 0, 0, 0);
          maxUpstreamc = (int)v156;
          maxBandPlayersa = 0;
          if ( v156->list.num > 0 )
          {
            v157 = fileList;
            v646 = 0;
            do
            {
              v158 = (int *)((char *)v646 + (unsigned int)v156->list.list);
              fixedExtension.len = 0;
              fixedExtension.alloced = 20;
              fixedExtension.data = fixedExtension.baseBuffer;
              fixedExtension.baseBuffer[0] = 0;
              v159 = *v158;
              v160 = *v158 + 1;
              if ( v160 > 20 )
                idStr::ReAllocate(&fixedExtension, v160, 1);
              v161 = (char *)v158[1];
              v162 = fixedExtension.data;
              do
              {
                v163 = *v161;
                *v162++ = *v161++;
              }
              while ( v163 );
              fixedExtension.len = v159;
              LOBYTE(v704) = 6;
              idStr::SetFileExtension(&fixedExtension, "map");
              v164 = 0;
              if ( v157 <= 0 )
                goto LABEL_273;
              v165 = (const char **)&fileList_12->data;
              while ( idStr::Cmp(*v165, fixedExtension.data) )
              {
                ++v164;
                v165 += 8;
                if ( v164 >= v157 )
                  goto LABEL_273;
              }
              if ( v164 < 0 )
              {
LABEL_273:
                if ( !fileList_12 && fileList_4 != 16 )
                {
                  v166 = fileList;
                  fileList_4 = 16;
                  if ( fileList > 16 )
                  {
                    v166 = 16;
                    fileList = 16;
                  }
                  v167 = Memory::Allocate(0x204u);
                  LODWORD(bright) = v167;
                  LOBYTE(v704) = 7;
                  if ( v167 )
                  {
                    v168 = (idStr *)(v167 + 1);
                    *v167 = 16;
                    `eh vector constructor iterator'(
                      v167 + 1,
                      0x20u,
                      16,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    v169 = v168;
                  }
                  else
                  {
                    v169 = 0;
                  }
                  LOBYTE(v704) = 6;
                  fileList_12 = v169;
                  if ( v166 > 0 )
                  {
                    LODWORD(bright) = -4 - (_DWORD)v169;
                    dedicatedc = 4;
                    v170 = &v169->data;
                    maxPlayersb = fileList;
                    do
                    {
                      v171 = *(unsigned int *)((char *)v170 + LODWORD(bright));
                      if ( (int)(v171 + 1) > (int)v170[1] )
                        idStr::ReAllocate((idStr *)(v170 - 1), v171 + 1, 0);
                      qmemcpy(*v170, *(const void **)dedicatedc, v171);
                      (*v170)[v171] = 0;
                      *(v170 - 1) = (char *)v171;
                      v170 += 8;
                      v550 = maxPlayersb-- == 1;
                      dedicatedc += 32;
                    }
                    while ( !v550 );
                  }
                }
                v172 = fileList_4;
                if ( fileList == fileList_4 )
                {
                  v173 = (fileList_4 + 16) % 16;
                  v174 = fileList_4 + 16 - v173;
                  if ( v174 > 0 )
                  {
                    if ( v174 != fileList_4 )
                    {
                      v175 = fileList;
                      ptrb = fileList_12;
                      fileList_4 = fileList_4 + 16 - v173;
                      if ( v174 < fileList )
                      {
                        v175 = v172 + 16 - v173;
                        fileList = v175;
                      }
                      v176 = (int *)Memory::Allocate(32 * v174 + 4);
                      LODWORD(bright) = v176;
                      LOBYTE(v704) = 8;
                      if ( v176 )
                      {
                        v177 = (idStr *)(v176 + 1);
                        *v176 = v174;
                        `eh vector constructor iterator'(
                          v176 + 1,
                          0x20u,
                          v174,
                          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        v178 = v177;
                      }
                      else
                      {
                        v178 = 0;
                      }
                      LOBYTE(v704) = 6;
                      fileList_12 = v178;
                      if ( v175 > 0 )
                      {
                        maxPlayersc = (unsigned int *)ptrb;
                        v179 = &v178->data;
                        LODWORD(bright) = (char *)ptrb - (char *)v178;
                        dedicatedd = fileList;
                        do
                        {
                          v180 = *maxPlayersc;
                          v181 = *maxPlayersc + 1;
                          if ( v181 > (int)v179[1] )
                            idStr::ReAllocate((idStr *)(v179 - 1), v181, 0);
                          maxPlayersc += 8;
                          qmemcpy(*v179, *(char **)((char *)v179 + LODWORD(bright)), v180);
                          (*v179)[v180] = 0;
                          *(v179 - 1) = (char *)v180;
                          v179 += 8;
                          --dedicatedd;
                        }
                        while ( dedicatedd );
                      }
                      if ( ptrb )
                      {
                        `eh vector destructor iterator'(
                          ptrb,
                          0x20u,
                          *(_DWORD *)&ptrb[-1].baseBuffer[16],
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        Memory::Free(&ptrb[-1].baseBuffer[16]);
                      }
                    }
                  }
                  else
                  {
                    if ( fileList_12 )
                    {
                      `eh vector destructor iterator'(
                        fileList_12,
                        0x20u,
                        *(_DWORD *)&fileList_12[-1].baseBuffer[16],
                        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                      Memory::Free(&fileList_12[-1].baseBuffer[16]);
                    }
                    fileList_12 = 0;
                    fileList = 0;
                    fileList_4 = 0;
                  }
                }
                len = fixedExtension.len;
                v183 = &fileList_12[fileList];
                if ( fixedExtension.len + 1 > v183->alloced )
                  idStr::ReAllocate(&fileList_12[fileList], fixedExtension.len + 1, 0);
                qmemcpy(v183->data, fixedExtension.data, len);
                ++fileList;
                v183->data[len] = 0;
                v183->len = len;
                v156 = (idFileList *)maxUpstreamc;
                v157 = fileList;
              }
              LOBYTE(v704) = 3;
              idStr::FreeData(&fixedExtension);
              v646 += 8;
              ++maxBandPlayersa;
            }
            while ( maxBandPlayersa < v156->list.num );
          }
          fileSystem->FreeFileList(fileSystem, v156);
          maxUpstreamd = fileSystem->ListFiles(fileSystem, "maps/game", ".map", 0, 0, 0);
          maxBandPlayersb = 0;
          if ( maxUpstreamd->list.num > 0 )
          {
            v647 = 0;
            do
            {
              v184 = va("game/%s", *(char **)((char *)&maxUpstreamd->list.list->data + (unsigned int)v647));
              v185 = v184;
              v680.len = 0;
              v680.alloced = 20;
              v680.data = v680.baseBuffer;
              v680.baseBuffer[0] = 0;
              if ( v184 )
              {
                v186 = strlen(v184);
                if ( v186 + 1 > 20 )
                  idStr::ReAllocate(&v680, v186 + 1, 1);
                v187 = v680.data;
                v188 = (char *)v185;
                do
                {
                  v189 = *v188;
                  *v187++ = *v188++;
                }
                while ( v189 );
                v680.len = v186;
              }
              v190 = 0;
              LOBYTE(v704) = 9;
              if ( fileList <= 0 )
                goto LABEL_321;
              v191 = (const char **)&fileList_12->data;
              while ( idStr::Cmp(*v191, v680.data) )
              {
                ++v190;
                v191 += 8;
                if ( v190 >= fileList )
                  goto LABEL_321;
              }
              if ( v190 < 0 )
              {
LABEL_321:
                v192 = fileList_4;
                if ( !fileList_12 && fileList_4 != 16 )
                {
                  v193 = fileList;
                  v192 = 16;
                  fileList_4 = 16;
                  if ( fileList > 16 )
                  {
                    v193 = 16;
                    fileList = 16;
                  }
                  v194 = Memory::Allocate(0x204u);
                  LODWORD(bright) = v194;
                  LOBYTE(v704) = 10;
                  if ( v194 )
                  {
                    v195 = (idStr *)(v194 + 1);
                    *v194 = 16;
                    `eh vector constructor iterator'(
                      v194 + 1,
                      0x20u,
                      16,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    v196 = v195;
                  }
                  else
                  {
                    v196 = 0;
                  }
                  LOBYTE(v704) = 9;
                  fileList_12 = v196;
                  if ( v193 > 0 )
                  {
                    dedicatede = 4;
                    v197 = &v196->data;
                    LODWORD(bright) = -4 - (_DWORD)v196;
                    maxPlayersd = v193;
                    do
                    {
                      v198 = *(unsigned int *)((char *)v197 + LODWORD(bright));
                      if ( (int)(v198 + 1) > (int)v197[1] )
                        idStr::ReAllocate((idStr *)(v197 - 1), v198 + 1, 0);
                      qmemcpy(*v197, *(const void **)dedicatede, v198);
                      (*v197)[v198] = 0;
                      *(v197 - 1) = (char *)v198;
                      v197 += 8;
                      v550 = maxPlayersd-- == 1;
                      dedicatede += 32;
                    }
                    while ( !v550 );
                    v192 = 16;
                  }
                }
                if ( fileList == v192 )
                {
                  v199 = (v192 + 16) % 16;
                  v200 = v192 + 16 - v199;
                  if ( v200 > 0 )
                  {
                    if ( v200 != v192 )
                    {
                      v201 = fileList;
                      ptrc = fileList_12;
                      fileList_4 = v192 + 16 - v199;
                      if ( v200 < fileList )
                      {
                        v201 = v192 + 16 - v199;
                        fileList = v201;
                      }
                      v202 = (int *)Memory::Allocate(32 * v200 + 4);
                      LODWORD(bright) = v202;
                      LOBYTE(v704) = 11;
                      if ( v202 )
                      {
                        v203 = (idStr *)(v202 + 1);
                        *v202 = v200;
                        `eh vector constructor iterator'(
                          v202 + 1,
                          0x20u,
                          v200,
                          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        v204 = v203;
                      }
                      else
                      {
                        v204 = 0;
                      }
                      LOBYTE(v704) = 9;
                      fileList_12 = v204;
                      if ( v201 > 0 )
                      {
                        maxPlayerse = (unsigned int *)ptrc;
                        LODWORD(bright) = (char *)ptrc - (char *)v204;
                        v205 = &v204->data;
                        dedicatedf = fileList;
                        do
                        {
                          v206 = *maxPlayerse;
                          v207 = *maxPlayerse + 1;
                          if ( v207 > (int)v205[1] )
                            idStr::ReAllocate((idStr *)(v205 - 1), v207, 0);
                          maxPlayerse += 8;
                          qmemcpy(*v205, *(char **)((char *)v205 + LODWORD(bright)), v206);
                          (*v205)[v206] = 0;
                          *(v205 - 1) = (char *)v206;
                          v205 += 8;
                          --dedicatedf;
                        }
                        while ( dedicatedf );
                      }
                      if ( ptrc )
                      {
                        `eh vector destructor iterator'(
                          ptrc,
                          0x20u,
                          *(_DWORD *)&ptrc[-1].baseBuffer[16],
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        Memory::Free(&ptrc[-1].baseBuffer[16]);
                      }
                    }
                  }
                  else
                  {
                    if ( fileList_12 )
                    {
                      `eh vector destructor iterator'(
                        fileList_12,
                        0x20u,
                        *(_DWORD *)&fileList_12[-1].baseBuffer[16],
                        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                      Memory::Free(&fileList_12[-1].baseBuffer[16]);
                    }
                    fileList_12 = 0;
                    fileList = 0;
                    fileList_4 = 0;
                  }
                }
                v208 = &fileList_12[fileList];
                v209 = v680.len;
                if ( v680.len + 1 > v208->alloced )
                  idStr::ReAllocate(&fileList_12[fileList], v680.len + 1, 0);
                qmemcpy(v208->data, v680.data, v209);
                ++fileList;
                v208->data[v209] = 0;
                v208->len = v209;
              }
              LOBYTE(v704) = 3;
              idStr::FreeData(&v680);
              v647 += 8;
              ++maxBandPlayersb;
            }
            while ( maxBandPlayersb < maxUpstreamd->list.num );
          }
          fileSystem->FreeFileList(fileSystem, maxUpstreamd);
          v210 = fileSystem->ListFiles(fileSystem, "maps/game", ".mapc", 0, 0, 0);
          maxUpstreame = (int)v210;
          maxBandPlayersc = 0;
          if ( v210->list.num > 0 )
          {
            v648 = 0;
            while ( 1 )
            {
              v211 = (int *)((char *)v648 + (unsigned int)v210->list.list);
              v689.data = v689.baseBuffer;
              v689.len = 0;
              v689.alloced = 20;
              v689.baseBuffer[0] = 0;
              v212 = *v211;
              v213 = *v211 + 1;
              if ( v213 > 20 )
                idStr::ReAllocate(&v689, v213, 1);
              v214 = (char *)v211[1];
              v215 = v689.data;
              do
              {
                v216 = *v214;
                *v215++ = *v214++;
              }
              while ( v216 );
              v689.len = v212;
              LOBYTE(v704) = 12;
              idStr::SetFileExtension(&v689, "map");
              v217 = va("game/%s", v689.data);
              v218 = v217;
              v686.len = 0;
              v686.alloced = 20;
              v686.data = v686.baseBuffer;
              v686.baseBuffer[0] = 0;
              if ( v217 )
              {
                v219 = strlen(v217);
                if ( v219 + 1 > 20 )
                  idStr::ReAllocate(&v686, v219 + 1, 1);
                v220 = v686.data;
                v221 = (char *)v218;
                do
                {
                  v222 = *v221;
                  *v220++ = *v221++;
                }
                while ( v222 );
                v686.len = v219;
              }
              v223 = 0;
              LOBYTE(v704) = 13;
              if ( fileList <= 0 )
                goto LABEL_375;
              v224 = (const char **)&fileList_12->data;
              while ( idStr::Cmp(*v224, v686.data) )
              {
                ++v223;
                v224 += 8;
                if ( v223 >= fileList )
                  goto LABEL_375;
              }
              if ( v223 < 0 )
              {
LABEL_375:
                v225 = fileList_4;
                if ( !fileList_12 && fileList_4 != 16 )
                {
                  v226 = fileList;
                  v225 = 16;
                  fileList_4 = 16;
                  if ( fileList > 16 )
                  {
                    v226 = 16;
                    fileList = 16;
                  }
                  v227 = Memory::Allocate(0x204u);
                  LODWORD(bright) = v227;
                  LOBYTE(v704) = 14;
                  if ( v227 )
                  {
                    v228 = (idStr *)(v227 + 1);
                    *v227 = 16;
                    `eh vector constructor iterator'(
                      v227 + 1,
                      0x20u,
                      16,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    v229 = v228;
                  }
                  else
                  {
                    v229 = 0;
                  }
                  LOBYTE(v704) = 13;
                  fileList_12 = v229;
                  if ( v226 > 0 )
                  {
                    dedicatedg = 4;
                    v230 = &v229->data;
                    LODWORD(bright) = -4 - (_DWORD)v229;
                    maxPlayersf = v226;
                    do
                    {
                      v231 = *(unsigned int *)((char *)v230 + LODWORD(bright));
                      if ( (int)(v231 + 1) > (int)v230[1] )
                        idStr::ReAllocate((idStr *)(v230 - 1), v231 + 1, 0);
                      qmemcpy(*v230, *(const void **)dedicatedg, v231);
                      (*v230)[v231] = 0;
                      *(v230 - 1) = (char *)v231;
                      v230 += 8;
                      v550 = maxPlayersf-- == 1;
                      dedicatedg += 32;
                    }
                    while ( !v550 );
                    v225 = 16;
                  }
                }
                if ( fileList == v225 )
                {
                  v232 = (v225 + 16) % 16;
                  v233 = v225 + 16 - v232;
                  if ( v233 > 0 )
                  {
                    if ( v233 != v225 )
                    {
                      v234 = fileList;
                      ptrd = fileList_12;
                      fileList_4 = v225 + 16 - v232;
                      if ( v233 < fileList )
                      {
                        v234 = v225 + 16 - v232;
                        fileList = v234;
                      }
                      v235 = (int *)Memory::Allocate(32 * v233 + 4);
                      LODWORD(bright) = v235;
                      LOBYTE(v704) = 15;
                      if ( v235 )
                      {
                        v236 = (idStr *)(v235 + 1);
                        *v235 = v233;
                        `eh vector constructor iterator'(
                          v235 + 1,
                          0x20u,
                          v233,
                          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        v237 = v236;
                      }
                      else
                      {
                        v237 = 0;
                      }
                      LOBYTE(v704) = 13;
                      fileList_12 = v237;
                      if ( v234 > 0 )
                      {
                        maxPlayersg = (unsigned int *)ptrd;
                        LODWORD(bright) = (char *)ptrd - (char *)v237;
                        v238 = &v237->data;
                        dedicatedh = fileList;
                        do
                        {
                          v239 = *maxPlayersg;
                          v240 = *maxPlayersg + 1;
                          if ( v240 > (int)v238[1] )
                            idStr::ReAllocate((idStr *)(v238 - 1), v240, 0);
                          maxPlayersg += 8;
                          qmemcpy(*v238, *(char **)((char *)v238 + LODWORD(bright)), v239);
                          (*v238)[v239] = 0;
                          *(v238 - 1) = (char *)v239;
                          v238 += 8;
                          --dedicatedh;
                        }
                        while ( dedicatedh );
                      }
                      if ( ptrd )
                      {
                        `eh vector destructor iterator'(
                          ptrd,
                          0x20u,
                          *(_DWORD *)&ptrd[-1].baseBuffer[16],
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        Memory::Free(&ptrd[-1].baseBuffer[16]);
                      }
                    }
                  }
                  else
                  {
                    if ( fileList_12 )
                    {
                      `eh vector destructor iterator'(
                        fileList_12,
                        0x20u,
                        *(_DWORD *)&fileList_12[-1].baseBuffer[16],
                        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                      Memory::Free(&fileList_12[-1].baseBuffer[16]);
                    }
                    fileList_12 = 0;
                    fileList = 0;
                    fileList_4 = 0;
                  }
                }
                v241 = &fileList_12[fileList];
                v242 = v686.len;
                if ( v686.len + 1 > v241->alloced )
                  idStr::ReAllocate(&fileList_12[fileList], v686.len + 1, 0);
                qmemcpy(v241->data, v686.data, v242);
                ++fileList;
                v241->data[v242] = 0;
                v241->len = v242;
              }
              LOBYTE(v704) = 12;
              idStr::FreeData(&v686);
              LOBYTE(v704) = 3;
              idStr::FreeData(&v689);
              v648 += 8;
              if ( ++maxBandPlayersc >= *(_DWORD *)(maxUpstreame + 32) )
                break;
              v210 = (idFileList *)maxUpstreame;
            }
          }
          maxUpstreamf = fileSystem->ListFiles(fileSystem, "maps/ai", ".map", 0, 0, 0);
          maxBandPlayersd = 0;
          if ( maxUpstreamf->list.num > 0 )
          {
            v649 = 0;
            do
            {
              v243 = va("ai/%s", *(const char **)((char *)v649 + (unsigned int)maxUpstreamf->list.list + 4));
              v684.len = 0;
              v684.alloced = 20;
              v684.data = v684.baseBuffer;
              v684.baseBuffer[0] = 0;
              if ( v243 )
              {
                v244 = (unsigned int)&v243[strlen(v243) + 1];
                v245 = v244 - (_DWORD)(v243 + 1);
                v246 = v244 - (_DWORD)v243;
                if ( v246 > 20 )
                  idStr::ReAllocate(&v684, v246, 1);
                v247 = v684.data;
                v248 = v243;
                do
                {
                  v249 = *v248;
                  *v247++ = *v248++;
                }
                while ( v249 );
                v684.len = v245;
              }
              v250 = 0;
              LOBYTE(v704) = 16;
              if ( fileList <= 0 )
                goto LABEL_424;
              v251 = (const char **)&fileList_12->data;
              while ( idStr::Cmp(*v251, v684.data) )
              {
                ++v250;
                v251 += 8;
                if ( v250 >= fileList )
                  goto LABEL_424;
              }
              if ( v250 < 0 )
              {
LABEL_424:
                v252 = fileList_4;
                if ( !fileList_12 && fileList_4 != 16 )
                {
                  v253 = fileList;
                  v252 = 16;
                  fileList_4 = 16;
                  if ( fileList > 16 )
                  {
                    v253 = 16;
                    fileList = 16;
                  }
                  v254 = Memory::Allocate(0x204u);
                  LODWORD(bright) = v254;
                  LOBYTE(v704) = 17;
                  if ( v254 )
                  {
                    v255 = (idStr *)(v254 + 1);
                    *v254 = 16;
                    `eh vector constructor iterator'(
                      v254 + 1,
                      0x20u,
                      16,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    v256 = v255;
                  }
                  else
                  {
                    v256 = 0;
                  }
                  LOBYTE(v704) = 16;
                  fileList_12 = v256;
                  if ( v253 > 0 )
                  {
                    dedicatedi = 4;
                    v257 = &v256->data;
                    LODWORD(bright) = -4 - (_DWORD)v256;
                    maxPlayersh = v253;
                    do
                    {
                      v258 = *(unsigned int *)((char *)v257 + LODWORD(bright));
                      if ( (int)(v258 + 1) > (int)v257[1] )
                        idStr::ReAllocate((idStr *)(v257 - 1), v258 + 1, 0);
                      qmemcpy(*v257, *(const void **)dedicatedi, v258);
                      (*v257)[v258] = 0;
                      *(v257 - 1) = (char *)v258;
                      v257 += 8;
                      v550 = maxPlayersh-- == 1;
                      dedicatedi += 32;
                    }
                    while ( !v550 );
                    v252 = 16;
                  }
                }
                if ( fileList == v252 )
                {
                  v259 = (v252 + 16) % 16;
                  v260 = v252 + 16 - v259;
                  if ( v260 > 0 )
                  {
                    if ( v260 != v252 )
                    {
                      v261 = fileList;
                      ptre = fileList_12;
                      fileList_4 = v252 + 16 - v259;
                      if ( v260 < fileList )
                      {
                        v261 = v252 + 16 - v259;
                        fileList = v261;
                      }
                      v262 = (int *)Memory::Allocate(32 * v260 + 4);
                      LODWORD(bright) = v262;
                      LOBYTE(v704) = 18;
                      if ( v262 )
                      {
                        v263 = (idStr *)(v262 + 1);
                        *v262 = v260;
                        `eh vector constructor iterator'(
                          v262 + 1,
                          0x20u,
                          v260,
                          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        v264 = v263;
                      }
                      else
                      {
                        v264 = 0;
                      }
                      LOBYTE(v704) = 16;
                      fileList_12 = v264;
                      if ( v261 > 0 )
                      {
                        maxPlayersi = (unsigned int *)ptre;
                        LODWORD(bright) = (char *)ptre - (char *)v264;
                        v265 = &v264->data;
                        dedicatedj = fileList;
                        do
                        {
                          v266 = *maxPlayersi;
                          v267 = *maxPlayersi + 1;
                          if ( v267 > (int)v265[1] )
                            idStr::ReAllocate((idStr *)(v265 - 1), v267, 0);
                          maxPlayersi += 8;
                          qmemcpy(*v265, *(char **)((char *)v265 + LODWORD(bright)), v266);
                          (*v265)[v266] = 0;
                          *(v265 - 1) = (char *)v266;
                          v265 += 8;
                          --dedicatedj;
                        }
                        while ( dedicatedj );
                      }
                      if ( ptre )
                      {
                        `eh vector destructor iterator'(
                          ptre,
                          0x20u,
                          *(_DWORD *)&ptre[-1].baseBuffer[16],
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        Memory::Free(&ptre[-1].baseBuffer[16]);
                      }
                    }
                  }
                  else
                  {
                    if ( fileList_12 )
                    {
                      `eh vector destructor iterator'(
                        fileList_12,
                        0x20u,
                        *(_DWORD *)&fileList_12[-1].baseBuffer[16],
                        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                      Memory::Free(&fileList_12[-1].baseBuffer[16]);
                    }
                    fileList_12 = 0;
                    fileList = 0;
                    fileList_4 = 0;
                  }
                }
                v268 = &fileList_12[fileList];
                v269 = v684.len;
                if ( v684.len + 1 > v268->alloced )
                  idStr::ReAllocate(&fileList_12[fileList], v684.len + 1, 0);
                qmemcpy(v268->data, v684.data, v269);
                ++fileList;
                v268->data[v269] = 0;
                v268->len = v269;
              }
              LOBYTE(v704) = 3;
              idStr::FreeData(&v684);
              v649 += 8;
              ++maxBandPlayersd;
            }
            while ( maxBandPlayersd < maxUpstreamf->list.num );
          }
          fileSystem->FreeFileList(fileSystem, maxUpstreamf);
          v270 = fileSystem->ListFiles(fileSystem, "maps/ai", ".mapc", 0, 0, 0);
          maxUpstreamg = (int)v270;
          maxBandPlayerse = 0;
          if ( v270->list.num > 0 )
          {
            v650 = 0;
            while ( 1 )
            {
              v271 = (int *)((char *)v650 + (unsigned int)v270->list.list);
              v690.data = v690.baseBuffer;
              v690.len = 0;
              v690.alloced = 20;
              v690.baseBuffer[0] = 0;
              v272 = *v271;
              v273 = *v271 + 1;
              if ( v273 > 20 )
                idStr::ReAllocate(&v690, v273, 1);
              v274 = (char *)v271[1];
              v275 = v690.data;
              do
              {
                v276 = *v274;
                *v275++ = *v274++;
              }
              while ( v276 );
              v690.len = v272;
              LOBYTE(v704) = 19;
              idStr::SetFileExtension(&v690, "map");
              v277 = va("ai/%s", v690.data);
              v278 = v277;
              v681.len = 0;
              v681.alloced = 20;
              v681.data = v681.baseBuffer;
              v681.baseBuffer[0] = 0;
              if ( v277 )
              {
                v279 = strlen(v277);
                if ( v279 + 1 > 20 )
                  idStr::ReAllocate(&v681, v279 + 1, 1);
                v280 = v681.data;
                v281 = (char *)v278;
                do
                {
                  v282 = *v281;
                  *v280++ = *v281++;
                }
                while ( v282 );
                v681.len = v279;
              }
              v283 = 0;
              LOBYTE(v704) = 20;
              if ( fileList <= 0 )
                goto LABEL_478;
              v284 = (const char **)&fileList_12->data;
              while ( idStr::Cmp(*v284, v681.data) )
              {
                ++v283;
                v284 += 8;
                if ( v283 >= fileList )
                  goto LABEL_478;
              }
              if ( v283 < 0 )
              {
LABEL_478:
                v285 = fileList_4;
                if ( !fileList_12 && fileList_4 != 16 )
                {
                  v286 = fileList;
                  v285 = 16;
                  fileList_4 = 16;
                  if ( fileList > 16 )
                  {
                    v286 = 16;
                    fileList = 16;
                  }
                  v287 = Memory::Allocate(0x204u);
                  LODWORD(bright) = v287;
                  LOBYTE(v704) = 21;
                  if ( v287 )
                  {
                    v288 = (idStr *)(v287 + 1);
                    *v287 = 16;
                    `eh vector constructor iterator'(
                      v287 + 1,
                      0x20u,
                      16,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    v289 = v288;
                  }
                  else
                  {
                    v289 = 0;
                  }
                  LOBYTE(v704) = 20;
                  fileList_12 = v289;
                  if ( v286 > 0 )
                  {
                    dedicatedk = 4;
                    v290 = &v289->data;
                    LODWORD(bright) = -4 - (_DWORD)v289;
                    maxPlayersj = v286;
                    do
                    {
                      v291 = *(unsigned int *)((char *)v290 + LODWORD(bright));
                      if ( (int)(v291 + 1) > (int)v290[1] )
                        idStr::ReAllocate((idStr *)(v290 - 1), v291 + 1, 0);
                      qmemcpy(*v290, *(const void **)dedicatedk, v291);
                      (*v290)[v291] = 0;
                      *(v290 - 1) = (char *)v291;
                      v290 += 8;
                      v550 = maxPlayersj-- == 1;
                      dedicatedk += 32;
                    }
                    while ( !v550 );
                    v285 = 16;
                  }
                }
                if ( fileList == v285 )
                {
                  v292 = (v285 + 16) % 16;
                  v293 = v285 + 16 - v292;
                  if ( v293 > 0 )
                  {
                    if ( v293 != v285 )
                    {
                      v294 = fileList;
                      ptrf = fileList_12;
                      fileList_4 = v285 + 16 - v292;
                      if ( v293 < fileList )
                      {
                        v294 = v285 + 16 - v292;
                        fileList = v294;
                      }
                      v295 = (int *)Memory::Allocate(32 * v293 + 4);
                      LODWORD(bright) = v295;
                      LOBYTE(v704) = 22;
                      if ( v295 )
                      {
                        v296 = (idStr *)(v295 + 1);
                        *v295 = v293;
                        `eh vector constructor iterator'(
                          v295 + 1,
                          0x20u,
                          v293,
                          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        v297 = v296;
                      }
                      else
                      {
                        v297 = 0;
                      }
                      LOBYTE(v704) = 20;
                      fileList_12 = v297;
                      if ( v294 > 0 )
                      {
                        maxPlayersk = (unsigned int *)ptrf;
                        LODWORD(bright) = (char *)ptrf - (char *)v297;
                        v298 = &v297->data;
                        dedicatedl = fileList;
                        do
                        {
                          v299 = *maxPlayersk;
                          v300 = *maxPlayersk + 1;
                          if ( v300 > (int)v298[1] )
                            idStr::ReAllocate((idStr *)(v298 - 1), v300, 0);
                          maxPlayersk += 8;
                          qmemcpy(*v298, *(char **)((char *)v298 + LODWORD(bright)), v299);
                          (*v298)[v299] = 0;
                          *(v298 - 1) = (char *)v299;
                          v298 += 8;
                          --dedicatedl;
                        }
                        while ( dedicatedl );
                      }
                      if ( ptrf )
                      {
                        `eh vector destructor iterator'(
                          ptrf,
                          0x20u,
                          *(_DWORD *)&ptrf[-1].baseBuffer[16],
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        Memory::Free(&ptrf[-1].baseBuffer[16]);
                      }
                    }
                  }
                  else
                  {
                    if ( fileList_12 )
                    {
                      `eh vector destructor iterator'(
                        fileList_12,
                        0x20u,
                        *(_DWORD *)&fileList_12[-1].baseBuffer[16],
                        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                      Memory::Free(&fileList_12[-1].baseBuffer[16]);
                    }
                    fileList_12 = 0;
                    fileList = 0;
                    fileList_4 = 0;
                  }
                }
                v301 = &fileList_12[fileList];
                v302 = v681.len;
                if ( v681.len + 1 > v301->alloced )
                  idStr::ReAllocate(&fileList_12[fileList], v681.len + 1, 0);
                qmemcpy(v301->data, v681.data, v302);
                ++fileList;
                v301->data[v302] = 0;
                v301->len = v302;
              }
              LOBYTE(v704) = 19;
              idStr::FreeData(&v681);
              LOBYTE(v704) = 3;
              idStr::FreeData(&v690);
              v650 += 8;
              if ( ++maxBandPlayerse >= *(_DWORD *)(maxUpstreamg + 32) )
                break;
              v270 = (idFileList *)maxUpstreamg;
            }
          }
          maxUpstreamh = fileSystem->ListFiles(fileSystem, "maps/mp", ".map", 0, 0, 0);
          maxBandPlayersf = 0;
          if ( maxUpstreamh->list.num > 0 )
          {
            v651 = 0;
            do
            {
              v303 = va("mp/%s", *(char **)((char *)&maxUpstreamh->list.list->data + (unsigned int)v651));
              v683.len = 0;
              v683.alloced = 20;
              v683.data = v683.baseBuffer;
              v683.baseBuffer[0] = 0;
              if ( v303 )
              {
                v304 = (unsigned int)&v303[strlen(v303) + 1];
                v305 = v304 - (_DWORD)(v303 + 1);
                v306 = v304 - (_DWORD)v303;
                if ( v306 > 20 )
                  idStr::ReAllocate(&v683, v306, 1);
                v307 = v683.data;
                v308 = v303;
                do
                {
                  v309 = *v308;
                  *v307++ = *v308++;
                }
                while ( v309 );
                v683.len = v305;
              }
              v310 = 0;
              LOBYTE(v704) = 23;
              if ( fileList <= 0 )
                goto LABEL_527;
              v311 = (const char **)&fileList_12->data;
              while ( idStr::Cmp(*v311, v683.data) )
              {
                ++v310;
                v311 += 8;
                if ( v310 >= fileList )
                  goto LABEL_527;
              }
              if ( v310 < 0 )
              {
LABEL_527:
                v312 = fileList_4;
                if ( !fileList_12 && fileList_4 != 16 )
                {
                  v313 = fileList;
                  v312 = 16;
                  fileList_4 = 16;
                  if ( fileList > 16 )
                  {
                    v313 = 16;
                    fileList = 16;
                  }
                  v314 = Memory::Allocate(0x204u);
                  LODWORD(bright) = v314;
                  LOBYTE(v704) = 24;
                  if ( v314 )
                  {
                    v315 = (idStr *)(v314 + 1);
                    *v314 = 16;
                    `eh vector constructor iterator'(
                      v314 + 1,
                      0x20u,
                      16,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    v316 = v315;
                  }
                  else
                  {
                    v316 = 0;
                  }
                  LOBYTE(v704) = 23;
                  fileList_12 = v316;
                  if ( v313 > 0 )
                  {
                    dedicatedm = 4;
                    v317 = &v316->data;
                    LODWORD(bright) = -4 - (_DWORD)v316;
                    maxPlayersl = v313;
                    do
                    {
                      v318 = *(unsigned int *)((char *)v317 + LODWORD(bright));
                      if ( (int)(v318 + 1) > (int)v317[1] )
                        idStr::ReAllocate((idStr *)(v317 - 1), v318 + 1, 0);
                      qmemcpy(*v317, *(const void **)dedicatedm, v318);
                      (*v317)[v318] = 0;
                      *(v317 - 1) = (char *)v318;
                      v317 += 8;
                      v550 = maxPlayersl-- == 1;
                      dedicatedm += 32;
                    }
                    while ( !v550 );
                    v312 = 16;
                  }
                }
                if ( fileList == v312 )
                {
                  v319 = (v312 + 16) % 16;
                  v320 = v312 + 16 - v319;
                  if ( v320 > 0 )
                  {
                    if ( v320 != v312 )
                    {
                      v321 = fileList;
                      ptrg = fileList_12;
                      fileList_4 = v312 + 16 - v319;
                      if ( v320 < fileList )
                      {
                        v321 = v312 + 16 - v319;
                        fileList = v321;
                      }
                      v322 = (int *)Memory::Allocate(32 * v320 + 4);
                      LODWORD(bright) = v322;
                      LOBYTE(v704) = 25;
                      if ( v322 )
                      {
                        v323 = (idStr *)(v322 + 1);
                        *v322 = v320;
                        `eh vector constructor iterator'(
                          v322 + 1,
                          0x20u,
                          v320,
                          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        v324 = v323;
                      }
                      else
                      {
                        v324 = 0;
                      }
                      LOBYTE(v704) = 23;
                      fileList_12 = v324;
                      if ( v321 > 0 )
                      {
                        maxPlayersm = (unsigned int *)ptrg;
                        LODWORD(bright) = (char *)ptrg - (char *)v324;
                        v325 = &v324->data;
                        dedicatedn = fileList;
                        do
                        {
                          v326 = *maxPlayersm;
                          v327 = *maxPlayersm + 1;
                          if ( v327 > (int)v325[1] )
                            idStr::ReAllocate((idStr *)(v325 - 1), v327, 0);
                          maxPlayersm += 8;
                          qmemcpy(*v325, *(char **)((char *)v325 + LODWORD(bright)), v326);
                          (*v325)[v326] = 0;
                          *(v325 - 1) = (char *)v326;
                          v325 += 8;
                          --dedicatedn;
                        }
                        while ( dedicatedn );
                      }
                      if ( ptrg )
                      {
                        `eh vector destructor iterator'(
                          ptrg,
                          0x20u,
                          *(_DWORD *)&ptrg[-1].baseBuffer[16],
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        Memory::Free(&ptrg[-1].baseBuffer[16]);
                      }
                    }
                  }
                  else
                  {
                    if ( fileList_12 )
                    {
                      `eh vector destructor iterator'(
                        fileList_12,
                        0x20u,
                        *(_DWORD *)&fileList_12[-1].baseBuffer[16],
                        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                      Memory::Free(&fileList_12[-1].baseBuffer[16]);
                    }
                    fileList_12 = 0;
                    fileList = 0;
                    fileList_4 = 0;
                  }
                }
                v328 = &fileList_12[fileList];
                v329 = v683.len;
                if ( v683.len + 1 > v328->alloced )
                  idStr::ReAllocate(&fileList_12[fileList], v683.len + 1, 0);
                qmemcpy(v328->data, v683.data, v329);
                ++fileList;
                v328->data[v329] = 0;
                v328->len = v329;
              }
              LOBYTE(v704) = 3;
              idStr::FreeData(&v683);
              v651 += 8;
              ++maxBandPlayersf;
            }
            while ( maxBandPlayersf < maxUpstreamh->list.num );
          }
          fileSystem->FreeFileList(fileSystem, maxUpstreamh);
          maxUpstreami = fileSystem->ListFiles(fileSystem, "maps/mp", ".mapc", 0, 0, 0);
          maxBandPlayersg = 0;
          if ( maxUpstreami->list.num > 0 )
          {
            v652 = 0;
            do
            {
              v330 = (int *)((char *)v652 + (unsigned int)maxUpstreami->list.list);
              v688.len = 0;
              v688.alloced = 20;
              v688.data = v688.baseBuffer;
              v688.baseBuffer[0] = 0;
              v331 = *v330;
              v332 = *v330 + 1;
              if ( v332 > 20 )
                idStr::ReAllocate(&v688, v332, 1);
              v333 = (char *)v330[1];
              v334 = v688.data;
              do
              {
                v335 = *v333;
                *v334++ = *v333++;
              }
              while ( v335 );
              v688.len = v331;
              LOBYTE(v704) = 26;
              idStr::SetFileExtension(&v688, "map");
              v336 = va("mp/%s", v688.data);
              v685.len = 0;
              v685.alloced = 20;
              v685.data = v685.baseBuffer;
              v685.baseBuffer[0] = 0;
              if ( v336 )
              {
                v337 = (unsigned int)&v336[strlen(v336) + 1];
                v338 = v337 - (_DWORD)(v336 + 1);
                v339 = v337 - (_DWORD)v336;
                if ( v339 > 20 )
                  idStr::ReAllocate(&v685, v339, 1);
                v340 = v685.data;
                v341 = v336;
                do
                {
                  v342 = *v341;
                  *v340++ = *v341++;
                }
                while ( v342 );
                v685.len = v338;
              }
              v343 = 0;
              LOBYTE(v704) = 27;
              if ( fileList <= 0 )
                goto LABEL_580;
              v344 = (const char **)&fileList_12->data;
              while ( idStr::Cmp(*v344, v685.data) )
              {
                ++v343;
                v344 += 8;
                if ( v343 >= fileList )
                  goto LABEL_580;
              }
              if ( v343 < 0 )
              {
LABEL_580:
                if ( !fileList_12 && fileList_4 != 16 )
                {
                  v345 = fileList;
                  fileList_4 = 16;
                  if ( fileList > 16 )
                  {
                    v345 = 16;
                    fileList = 16;
                  }
                  v346 = Memory::Allocate(0x204u);
                  LODWORD(bright) = v346;
                  LOBYTE(v704) = 28;
                  if ( v346 )
                  {
                    v347 = (idStr *)(v346 + 1);
                    *v346 = 16;
                    `eh vector constructor iterator'(
                      v346 + 1,
                      0x20u,
                      16,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    v348 = v347;
                  }
                  else
                  {
                    v348 = 0;
                  }
                  LOBYTE(v704) = 27;
                  fileList_12 = v348;
                  if ( v345 > 0 )
                  {
                    dedicatedo = 4;
                    v349 = &v348->data;
                    LODWORD(bright) = -4 - (_DWORD)v348;
                    maxPlayersn = v345;
                    do
                    {
                      v350 = *(unsigned int *)((char *)v349 + LODWORD(bright));
                      if ( (int)(v350 + 1) > (int)v349[1] )
                        idStr::ReAllocate((idStr *)(v349 - 1), v350 + 1, 0);
                      qmemcpy(*v349, *(const void **)dedicatedo, v350);
                      (*v349)[v350] = 0;
                      *(v349 - 1) = (char *)v350;
                      v349 += 8;
                      v550 = maxPlayersn-- == 1;
                      dedicatedo += 32;
                    }
                    while ( !v550 );
                  }
                }
                v351 = fileList_4;
                if ( fileList == fileList_4 )
                {
                  v352 = (fileList_4 + 16) % 16;
                  v353 = fileList_4 + 16 - v352;
                  if ( v353 > 0 )
                  {
                    if ( v353 != fileList_4 )
                    {
                      v354 = fileList;
                      ptrh = fileList_12;
                      fileList_4 = fileList_4 + 16 - v352;
                      if ( v353 < fileList )
                      {
                        v354 = v351 + 16 - v352;
                        fileList = v354;
                      }
                      v355 = (int *)Memory::Allocate(32 * v353 + 4);
                      LODWORD(bright) = v355;
                      LOBYTE(v704) = 29;
                      if ( v355 )
                      {
                        v356 = (idStr *)(v355 + 1);
                        *v355 = v353;
                        `eh vector constructor iterator'(
                          v355 + 1,
                          0x20u,
                          v353,
                          (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        v357 = v356;
                      }
                      else
                      {
                        v357 = 0;
                      }
                      LOBYTE(v704) = 27;
                      fileList_12 = v357;
                      if ( v354 > 0 )
                      {
                        maxPlayerso = (unsigned int *)ptrh;
                        v358 = &v357->data;
                        LODWORD(bright) = (char *)ptrh - (char *)v357;
                        dedicatedp = fileList;
                        do
                        {
                          v359 = *maxPlayerso;
                          v360 = *maxPlayerso + 1;
                          if ( v360 > (int)v358[1] )
                            idStr::ReAllocate((idStr *)(v358 - 1), v360, 0);
                          maxPlayerso += 8;
                          qmemcpy(*v358, *(char **)((char *)v358 + LODWORD(bright)), v359);
                          (*v358)[v359] = 0;
                          *(v358 - 1) = (char *)v359;
                          v358 += 8;
                          --dedicatedp;
                        }
                        while ( dedicatedp );
                      }
                      if ( ptrh )
                      {
                        `eh vector destructor iterator'(
                          ptrh,
                          0x20u,
                          *(_DWORD *)&ptrh[-1].baseBuffer[16],
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        Memory::Free(&ptrh[-1].baseBuffer[16]);
                      }
                    }
                  }
                  else
                  {
                    if ( fileList_12 )
                    {
                      `eh vector destructor iterator'(
                        fileList_12,
                        0x20u,
                        *(_DWORD *)&fileList_12[-1].baseBuffer[16],
                        (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                      Memory::Free(&fileList_12[-1].baseBuffer[16]);
                    }
                    fileList_12 = 0;
                    fileList = 0;
                    fileList_4 = 0;
                  }
                }
                v361 = &fileList_12[fileList];
                v362 = v685.len;
                if ( v685.len + 1 > v361->alloced )
                  idStr::ReAllocate(&fileList_12[fileList], v685.len + 1, 0);
                qmemcpy(v361->data, v685.data, v362);
                ++fileList;
                v361->data[v362] = 0;
                v361->len = v362;
              }
              LOBYTE(v704) = 26;
              idStr::FreeData(&v685);
              LOBYTE(v704) = 3;
              idStr::FreeData(&v688);
              v652 += 8;
              ++maxBandPlayersg;
            }
            while ( maxBandPlayersg < maxUpstreami->list.num );
          }
          v363 = fileList;
          if ( fileList )
          {
            v668 = 16;
            v669 = 0;
            v666 = 0;
            v667 = 0;
            v672 = 16;
            v673 = 0;
            v670 = 0;
            LOBYTE(v704) = 31;
            if ( fileList > 0 )
            {
              v671 = fileList;
              v364 = Memory::Allocate(4 * fileList);
            }
            else
            {
              v364 = 0;
              v671 = 0;
            }
            v365 = 0;
            v673 = v364;
            v670 = fileList;
            if ( fileList > 0 )
            {
              v366 = fileList_12;
              do
                *((_DWORD *)v364 + v365++) = v366++;
              while ( v365 < fileList );
            }
            if ( v364 )
              qsort(
                v364,
                fileList,
                4u,
                (int (__cdecl *)(const void *, const void *))idListSortCompare<idPoolStr const *>);
            if ( fileList > 0 )
            {
              v368 = fileList;
              v667 = fileList;
              v369 = (int *)Memory::Allocate(32 * fileList + 4);
              LODWORD(bright) = v369;
              LOBYTE(v704) = 32;
              if ( v369 )
              {
                v370 = (idStr *)(v369 + 1);
                *v369 = fileList;
                `eh vector constructor iterator'(
                  v369 + 1,
                  0x20u,
                  fileList,
                  (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                v367 = v370;
              }
              else
              {
                v367 = 0;
              }
              LOBYTE(v704) = 31;
            }
            else
            {
              v367 = 0;
              v368 = 0;
              v667 = 0;
            }
            v669 = v367;
            v666 = fileList;
            v668 = 16;
            if ( v367 )
            {
              v371 = (fileList + 15) % 16;
              v372 = fileList + 15 - v371;
              if ( v372 != v368 )
              {
                if ( v372 > 0 )
                {
                  v373 = v367;
                  minPlayers = (int)v367;
                  v667 = fileList + 15 - v371;
                  if ( v372 < fileList )
                    v666 = fileList + 15 - v371;
                  v374 = (int *)Memory::Allocate(32 * v372 + 4);
                  LODWORD(bright) = v374;
                  LOBYTE(v704) = 33;
                  if ( v374 )
                  {
                    v375 = (idStr *)(v374 + 1);
                    *v374 = v372;
                    `eh vector constructor iterator'(
                      v374 + 1,
                      0x20u,
                      v372,
                      (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                    v376 = v375;
                  }
                  else
                  {
                    v376 = 0;
                  }
                  LOBYTE(v704) = 31;
                  v669 = v376;
                  if ( v666 > 0 )
                  {
                    maxPlayersp = (unsigned int *)v373;
                    v377 = &v376->data;
                    LODWORD(bright) = (char *)v373 - (char *)v376;
                    dedicatedq = v666;
                    do
                    {
                      v378 = *maxPlayersp;
                      v379 = *maxPlayersp + 1;
                      if ( v379 > (int)v377[1] )
                        idStr::ReAllocate((idStr *)(v377 - 1), v379, 0);
                      maxPlayersp += 8;
                      qmemcpy(*v377, *(char **)((char *)v377 + LODWORD(bright)), v378);
                      (*v377)[v378] = 0;
                      *(v377 - 1) = (char *)v378;
                      v377 += 8;
                      --dedicatedq;
                    }
                    while ( dedicatedq );
                    v373 = (idStr *)minPlayers;
                  }
                  if ( v373 )
                    idStr::`vector deleting destructor'(v373, 3);
                }
                else
                {
                  idStr::`vector deleting destructor'(v367, 3);
                  v669 = 0;
                  v666 = 0;
                  v667 = 0;
                }
              }
            }
            maxPlayersq = 0;
            if ( v666 > 0 )
            {
              v380 = &v669->data;
              do
              {
                v381 = *((_DWORD *)v673 + maxPlayersq);
                v382 = *(_DWORD *)v381;
                v383 = *(_DWORD *)v381 + 1;
                if ( v383 > (int)v380[1] )
                  idStr::ReAllocate((idStr *)(v380 - 1), v383, 0);
                qmemcpy(*v380, *(const void **)(v381 + 4), v382);
                (*v380)[v382] = 0;
                *(v380 - 1) = (char *)v382;
                v380 += 8;
                ++maxPlayersq;
              }
              while ( maxPlayersq < v666 );
            }
            v384 = v666;
            v385 = fileList_12;
            v386 = v669;
            v666 = fileList;
            v667 = fileList_4;
            v668 = 16;
            fileLista = v384;
            fileList_12 = v669;
            v669 = v385;
            LOBYTE(v704) = 30;
            if ( v673 )
              Memory::Free(v673);
            v673 = 0;
            v670 = 0;
            v671 = 0;
            LOBYTE(v704) = 3;
            if ( v385 )
            {
              `eh vector destructor iterator'(
                v385,
                0x20u,
                *(_DWORD *)&v385[-1].baseBuffer[16],
                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
              Memory::Free(&v385[-1].baseBuffer[16]);
            }
            v363 = fileLista;
            v669 = 0;
            v666 = 0;
            v667 = 0;
          }
          else
          {
            v386 = fileList_12;
          }
          v387 = v664;
          v388 = 0;
          maxBandPlayersh = 0;
          if ( v363 > 0 )
          {
            maxPlayersr = &v386->data;
            do
            {
              v389 = v387->guiActive->__vftable;
              v574 = *maxPlayersr;
              v390 = va("mapList_item_%i", v388);
              v389->SetStateString(v387->guiActive, v390, v574);
              maxPlayersr += 8;
              v388 = ++maxBandPlayersh;
            }
            while ( maxBandPlayersh < v363 );
            v386 = fileList_12;
          }
          matched = (int)v387->guiActive->__vftable;
          v391 = va("mapList_item_%i", v388);
          (*(void (__thiscall **)(idUserInterface *, char *))(matched + 84))(v387->guiActive, v391);
          v387->guiActive->SetStateInt(v387->guiActive, "mapList_sel_0", 0);
          v387->guiActive->StateChanged(v387->guiActive, com_frameTime, 0);
          v704 = -1;
          if ( v386 )
            idStr::`vector deleting destructor'(v386, 3);
          v3 = v664;
          goto LABEL_952;
        }
        if ( !idStr::Icmp(v6, "click_mapload") )
        {
          v392 = (idDict *)v3->guiActive->State(v3->guiActive);
          v393 = idDict::FindKey(v392, "mapList_sel_0");
          if ( v393 )
            v394 = v393->value->data;
          else
            v394 = "-1";
          v395 = atoi(v394);
          if ( v395 != -1 )
          {
            matched = (int)va("mapList_item_%i", v395);
            v396 = (idDict *)v3->guiActive->State(v3->guiActive);
            v397 = idDict::FindKey(v396, (const char *)matched);
            if ( v397 )
              v398 = v397->value->data;
            else
              v398 = &entityFilter;
            idSessionLocal::StartNewGame(v3, (int)v6, (int)v3, v398, 0, &entityFilter, 1);
          }
          goto LABEL_952;
        }
        if ( !idStr::Icmp(v6, "inetConnect") )
        {
          v399 = (idDict *)v3->guiMainMenu->State(v3->guiMainMenu);
          v400 = idDict::FindKey(v399, "inetGame");
          if ( v400 )
          {
            v401 = v400->value->data;
            if ( v401 )
            {
              if ( *v401 )
              {
                v402 = cmdSystem->__vftable;
                v403 = va("connect %s", v401);
                v402->BufferCommandText(cmdSystem, CMD_EXEC_NOW, v403);
                return;
              }
            }
          }
          goto LABEL_952;
        }
        if ( !idStr::Icmp(v6, "getClientIP") )
        {
          v569 = *Net_GetInterface(&result, 0);
          v404 = Sys_NetAdrToString(v569);
          matched = (int)v404;
          sStr.len = 0;
          sStr.alloced = 20;
          sStr.data = sStr.baseBuffer;
          sStr.baseBuffer[0] = 0;
          if ( v404 )
          {
            v405 = strlen(v404);
            if ( v405 + 1 > 20 )
              idStr::ReAllocate(&sStr, v405 + 1, 1);
            v406 = sStr.data;
            v407 = (char *)matched;
            do
            {
              v408 = *v407;
              *v406++ = *v407++;
            }
            while ( v408 );
            sStr.len = v405;
          }
          v704 = 34;
          idStr::StripLeading(&sStr, ":0");
          idStr::StripTrailing(&sStr, ":0");
          v3->guiMainMenu->SetStateString(v3->guiMainMenu, "net_ip", sStr.data);
          v704 = -1;
          idStr::FreeData(&sStr);
        }
        if ( !idStr::Icmp(v6, "chooseCrosshair") )
        {
          v409 = declManager->FindType(declManager, 4, "player_marine_mp", 0, 1);
          v410 = icmd++;
          v411 = idCmdArgs::Argv(&args, v410);
          maxBandPlayersi = atol(v411);
          v412 = cvarSystem->GetCVarString(cvarSystem, "g_crosshairCustomFile");
          v413 = v412;
          currentCrosshair.len = 0;
          currentCrosshair.alloced = 20;
          currentCrosshair.data = currentCrosshair.baseBuffer;
          currentCrosshair.baseBuffer[0] = 0;
          if ( v412 )
          {
            v414 = strlen(v412);
            if ( v414 + 1 > 20 )
              idStr::ReAllocate(&currentCrosshair, v414 + 1, 1);
            v415 = currentCrosshair.data;
            do
            {
              v416 = *v413;
              *v415++ = *v413++;
            }
            while ( v416 );
            currentCrosshair.len = v414;
            v6 = (const char *)maxUpstream;
          }
          v417 = (idDict *)&v409[1];
          v704 = 35;
          matched = (int)idDict::MatchPrefix(v417, "mtr_crosshair", 0);
          if ( matched )
          {
            v418 = 0;
            while ( 1 )
            {
              v419 = idDict::MatchPrefix(v417, "mtr_crosshair", (const idKeyValue *)matched);
              if ( !idStr::Cmp(*(const char **)(*(_DWORD *)(matched + 4) + 4), currentCrosshair.data) )
                break;
              v418 = (const idKeyValue *)matched;
              matched = (int)v419;
              if ( !v419 )
                goto LABEL_701;
            }
            v420 = v419;
            if ( maxBandPlayersi < 1 )
              v420 = v418;
            if ( !v420 )
            {
LABEL_701:
              if ( maxBandPlayersi < 1 )
              {
                if ( !v418 )
                {
                  for ( k = idDict::MatchPrefix(v417, "mtr_crosshair", 0);
                        k;
                        k = idDict::MatchPrefix(v417, "mtr_crosshair", k) )
                  {
                    v418 = k;
                  }
                }
                v420 = v418;
              }
              else
              {
                v420 = idDict::MatchPrefix(v417, "mtr_crosshair", 0);
              }
            }
            matched = (int)v420->value;
            newCrosshair.len = 0;
            newCrosshair.alloced = 20;
            newCrosshair.data = newCrosshair.baseBuffer;
            newCrosshair.baseBuffer[0] = 0;
            v422 = *(_DWORD *)matched;
            v423 = *(_DWORD *)matched + 1;
            if ( v423 > 20 )
              idStr::ReAllocate(&newCrosshair, v423, 1);
            v424 = *(char **)(matched + 4);
            v425 = newCrosshair.data;
            do
            {
              v426 = *v424;
              *v425++ = *v424++;
            }
            while ( v426 );
            newCrosshair.len = v422;
            guiMainMenu = v664->guiMainMenu;
            v428 = guiMainMenu->__vftable;
            LOBYTE(v704) = 36;
            v428->SetStateString(guiMainMenu, "crossImage", newCrosshair.data);
            cvarSystem->SetCVarString(cvarSystem, "g_crosshairCustomFile", newCrosshair.data, 0);
            LOBYTE(v704) = 35;
            idStr::FreeData(&newCrosshair);
            v3 = v664;
            v6 = (const char *)maxUpstream;
          }
          v704 = -1;
          idStr::FreeData(&currentCrosshair);
        }
        if ( !idStr::Icmp(v6, "startMultiplayer") )
        {
          v429 = cvarSystem->GetCVarBool(cvarSystem, "net_serverMenuDedicated");
          dedicatedr = v429;
          v430 = cvarSystem->GetCVarString(cvarSystem, "si_name");
          if ( !idStr::Icmp(&entityFilter, v430) )
            cvarSystem->SetCVarString(cvarSystem, "si_name", "www.quake4game.com", 0);
          if ( cvarSystem->GetCVarBool(cvarSystem, "si_usePass") )
          {
            v431 = cvarSystem->GetCVarString(cvarSystem, "g_password");
            if ( !idStr::Icmp(&entityFilter, v431) )
              cvarSystem->SetCVarBool(cvarSystem, "si_usePass", 0, 0);
          }
          matched = 16;
          maxBandPlayersj = 16;
          v432 = cvarSystem->GetCVarInteger(cvarSystem, "si_maxPlayers");
          maxPlayerss = cvarSystem->GetCVarInteger(cvarSystem, "si_maxPlayers");
          v433 = cvarSystem->GetCVarInteger(cvarSystem, "si_minPlayers");
          v550 = idSessionLocal::gui_configServerRate.internalVar->integerValue == 5;
          minPlayers = v433;
          maxUpstreamj = 0;
          if ( v550 || cvarSystem->GetCVarBool(cvarSystem, "net_menuLANServer") )
          {
            cvarSystem->SetCVarInteger(cvarSystem, "net_serverMaxClientRate", 25600, 0);
          }
          else
          {
            switch ( idSessionLocal::gui_configServerRate.internalVar->integerValue )
            {
              case 0:
                maxUpstreamj = 0x4000;
                matched = 4;
                goto LABEL_727;
              case 1:
                maxUpstreamj = 0x8000;
                matched = 6;
                goto LABEL_727;
              case 2:
                maxUpstreamj = 49152;
                matched = 10;
                goto LABEL_727;
              case 3:
                maxUpstreamj = 0x10000;
                matched = 10;
                goto LABEL_727;
              case 4:
                maxUpstreamj = 98304;
                matched = 12;
LABEL_727:
                maxBandPlayersj = matched;
                break;
              default:
                break;
            }
            if ( v432 > matched )
            {
              if ( !v429 )
                ++matched;
              v434 = v3->__vftable;
              v435 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                       common.type,
                       "#str_104314",
                       -1,
                       1,
                       "OK",
                       0,
                       0);
              v436 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int, int))(*(_DWORD *)common.type + 168))(
                                     common.type,
                                     "#str_104315",
                                     -1,
                                     matched,
                                     v435);
              v437 = va(v436);
              if ( !*(_BYTE *)((int (__thiscall *)(idSessionLocal *, int, char *, int, int, int))v434->MessageBoxA)(
                                v3,
                                2,
                                v437,
                                v570,
                                v572,
                                v575) )
                goto LABEL_952;
              cvarSystem->SetCVarInteger(cvarSystem, "si_maxPlayers", matched, 0);
            }
            LODWORD(bright) = (int)(((double)maxUpstreamj - 0.1 * (double)maxUpstreamj) / (double)maxBandPlayersj);
            cvarSystem->SetCVarInteger(cvarSystem, "net_serverMaxClientRate", LODWORD(bright), 0);
          }
          if ( v429 )
            goto LABEL_957;
          bright = Sys_ClockTicksPerSecond() * 0.000000001;
          if ( (Sys_GetProcessorId() & 8) != 0 )
          {
            v438 = declManager->FindType(declManager, 4, "MPCPUAMDPlayerLimit", 0, 0);
            v439 = 0;
            v440 = 4;
            if ( (int)v438[1].__vftable > 0 )
            {
              do
              {
                if ( v439 < 0 || v439 >= (int)v438[1].__vftable )
                  v441 = 0;
                else
                  v441 = &v438[2].base[2 * v439];
                if ( idStr::Icmp((const char *)v441->GetName, "classname") )
                {
                  v442 = atof((const char *)v441->GetName);
                  if ( v442 > bright )
                    goto LABEL_756;
                  v440 = atoi((const char *)v441[1].GetName);
                }
                ++v439;
              }
              while ( v439 < (int)v438[1].__vftable );
              goto LABEL_756;
            }
          }
          else
          {
            v443 = declManager->FindType(declManager, 4, "MPCPUIntelPlayerLimit", 0, 0);
            v444 = 0;
            v440 = 4;
            if ( (int)v443[1].__vftable > 0 )
            {
              do
              {
                if ( v444 < 0 || v444 >= (int)v443[1].__vftable )
                  v445 = 0;
                else
                  v445 = &v443[2].base[2 * v444];
                if ( idStr::Icmp((const char *)v445->GetName, "classname") )
                {
                  v446 = atof((const char *)v445->GetName);
                  if ( v446 > bright )
                    break;
                  v440 = atoi((const char *)v445[1].GetName);
                }
                ++v444;
              }
              while ( v444 < (int)v443[1].__vftable );
LABEL_756:
              if ( v440 >= 12 )
              {
                v447 = cvarSystem->GetCVarString(cvarSystem, "r_actualRenderer");
                if ( idStr::Icmp(v447, "ARB2") )
                  v440 -= 4;
              }
            }
          }
          if ( maxPlayerss <= v440 )
            goto LABEL_957;
          matched = (int)v664;
          v448 = v664->__vftable;
          v449 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, const char *, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                   common.type,
                   "#str_100626",
                   -1,
                   1,
                   "yes",
                   0,
                   0);
          v450 = (const char *)(*(int (__thiscall **)(netadrtype_t, const char *, int, int, int))(*(_DWORD *)common.type
                                                                                                + 168))(
                                 common.type,
                                 "#str_100625",
                                 -1,
                                 v440,
                                 v449);
          v451 = va(v450);
          if ( *(_BYTE *)((int (__thiscall *)(int, int, char *, int, int, int))v448->MessageBoxA)(
                           matched,
                           3,
                           v451,
                           v571,
                           v573,
                           v576) )
          {
            maxPlayerss = v440;
LABEL_957:
            cvarSystem->SetCVarInteger(cvarSystem, "si_maxPlayers", maxPlayerss, 0);
            if ( minPlayers > maxPlayerss )
              cvarSystem->SetCVarInteger(cvarSystem, "si_minPlayers", maxPlayerss, 0);
            cvarSystem->SetCVarInteger(cvarSystem, "net_serverDedicated", dedicatedr != 0, 0);
            v567 = cvarSystem->__vftable;
            v568 = ((int (__thiscall *)(idCVarSystem *, const char *, _DWORD))cvarSystem->GetCVarBool)(
                     cvarSystem,
                     "net_menuLANServer",
                     0);
            ((void (__thiscall *)(idCVarSystem *, const char *, int))v567->SetCVarBool)(
              cvarSystem,
              "net_LANServer",
              v568);
            cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "SpawnServer\n");
            return;
          }
          v3 = (idSessionLocal *)matched;
          goto LABEL_952;
        }
        if ( !idStr::Icmp(v6, "populateBanList") )
        {
          game->PopulateBanList(game, v3->guiActive);
          goto LABEL_952;
        }
        if ( idStr::Icmp(v6, "handleServerAdminRemoveBan") )
        {
          if ( idStr::Icmp(v6, "close") )
          {
            if ( idStr::Icmp(v6, "resetdefaults") )
            {
              if ( idStr::Icmp(v6, "bind") )
              {
                if ( idStr::Icmp(v6, "play") )
                {
                  if ( idStr::Icmp(v6, "music") )
                  {
                    if ( idStr::Icmp(v6, "sound") )
                    {
                      if ( idStr::Icmp(v6, "video") )
                      {
                        if ( !idStr::Icmp(v6, "mainMenu") )
                        {
                          if ( (_S6_6 & 1) == 0 )
                          {
                            _S6_6 |= 1u;
                            menuCmd.len = 0;
                            menuCmd.alloced = 20;
                            menuCmd.data = menuCmd.baseBuffer;
                            menuCmd.baseBuffer[0] = 0;
                            atexit(_E7_12);
                          }
                          idStr::FreeData(&menuCmd);
                          v505 = 0;
                          menuCmd.len = 0;
                          menuCmd.alloced = 20;
                          menuCmd.data = menuCmd.baseBuffer;
                          menuCmd.baseBuffer[0] = 0;
                          v506 = 109;
                          do
                          {
                            matched = menuCmd.len;
                            menuCmd.data[menuCmd.len + v505] = v506;
                            v506 = byte_102A66A5[v505++];
                          }
                          while ( v506 );
                          menuCmd.len = 4;
                          menuCmd.data[4] = 0;
                          if ( args.argc - icmd >= 1 )
                          {
                            v577 = icmd++;
                            v507 = idCmdArgs::Argv(&args, v577);
                            v508 = menuCmd.len + 1;
                            matched = (int)v507;
                            if ( menuCmd.len + 2 > menuCmd.alloced )
                              idStr::ReAllocate(&menuCmd, menuCmd.len + 2, 1);
                            v509 = 0;
                            v510 = 32;
                            do
                            {
                              menuCmd.data[menuCmd.len + v509] = v510;
                              v510 = src[++v509];
                            }
                            while ( v510 );
                            menuCmd.len = v508;
                            menuCmd.data[v508] = 0;
                            if ( matched )
                            {
                              v511 = strlen((const char *)matched) + menuCmd.len;
                              if ( v511 + 1 > menuCmd.alloced )
                                idStr::ReAllocate(&menuCmd, v511 + 1, 1);
                              v512 = *(_BYTE *)matched;
                              for ( m = 0; v512; ++m )
                              {
                                menuCmd.data[menuCmd.len + m] = v512;
                                v512 = *(_BYTE *)(m + matched + 1);
                              }
                              menuCmd.len = v511;
                              menuCmd.data[v511] = 0;
                            }
                          }
                          idSessionLocal::HandleMainMenuCommands(v664, menuCmd.data);
                          v3 = v664;
                          v6 = (const char *)maxUpstream;
                        }
                        if ( idStr::Icmp(v6, "clearBind") )
                        {
                          if ( idStr::Icmp(v6, "chatdone") )
                          {
                            if ( idStr::Icmp(v6, "exec") )
                            {
                              if ( !idStr::Icmp(v6, "loadBinds") )
                              {
                                v3->guiMainMenu->SetKeyBindingNames(v3->guiMainMenu);
                                goto LABEL_952;
                              }
                              if ( !idStr::Icmp(v6, "systemCvars") )
                              {
                                v3->guiActive->HandleNamedEvent(v3->guiActive, "cvar read render");
                                v3->guiActive->HandleNamedEvent(v3->guiActive, "cvar read sound");
                                goto LABEL_952;
                              }
                              if ( !idStr::Icmp(v6, "SetCDKey") )
                              {
                                cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "promptKey\n");
                                goto LABEL_952;
                              }
                              if ( !idStr::Icmp(v6, "CheckUpdate") )
                              {
                                idAsyncClient::SendVersionCheck(&idAsyncNetwork::client, 0);
                                idSessionLocal::SetPbMenuGuiVars(v3);
                                goto LABEL_952;
                              }
                              if ( !idStr::Icmp(v6, "CheckUpdate2") )
                              {
                                idAsyncClient::SendVersionCheck(&idAsyncNetwork::client, 1);
                                goto LABEL_952;
                              }
                              if ( idStr::Icmp(v6, "checkKeys") )
                              {
                                if ( !idStr::Icmp(v6, "update_model") )
                                {
                                  idSessionLocal::UpdateMPSettingsModel(v3, matched);
                                  goto LABEL_952;
                                }
                                if ( !idStr::Icmp(v6, "initMPSettings") )
                                {
                                  matched = (int)cvarSystem->__vftable;
                                  v546 = ((int (__thiscall *)(idCVarSystem *, const char *, _DWORD))cvarSystem->GetCVarString)(
                                           cvarSystem,
                                           "ui_name",
                                           0);
                                  (*(void (__thiscall **)(idCVarSystem *, const char *, int))(matched + 32))(
                                    cvarSystem,
                                    "gui_ui_name",
                                    v546);
                                  v547 = isPbClEnabled();
                                  v548 = v547 != 0;
                                  v549 = "ENABLED";
                                  if ( !v547 )
                                    v549 = "DISABLED";
                                  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                                    common.type,
                                    "PB client is %s\n",
                                    v549);
                                  v550 = !v548;
LABEL_922:
                                  v555 = v3->guiActive;
                                  if ( v550 )
                                    v555->SetStateString(v555, "mp_set_punkbuster_val_sel", "0");
                                  else
                                    v555->SetStateString(v555, "mp_set_punkbuster_val_sel", "1");
                                  v3->guiActive->StateChanged(v3->guiActive, com_frameTime, 0);
                                  goto LABEL_952;
                                }
                                if ( !idStr::Icmp(v6, "exitMPSettings") )
                                {
                                  matched = (int)cvarSystem->__vftable;
                                  v551 = ((int (__thiscall *)(idCVarSystem *, const char *, _DWORD))cvarSystem->GetCVarString)(
                                           cvarSystem,
                                           "gui_ui_name",
                                           0);
                                  (*(void (__thiscall **)(idCVarSystem *, const char *, int))(matched + 32))(
                                    cvarSystem,
                                    "ui_name",
                                    v551);
                                  goto LABEL_952;
                                }
                                if ( !idStr::Icmp(v6, "punkbusterToggle") )
                                {
                                  v552 = isPbClEnabled();
                                  v553 = v552 != 0;
                                  v554 = "ENABLED";
                                  if ( !v552 )
                                    v554 = "DISABLED";
                                  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                                    common.type,
                                    "PB client is %s, now toggling\n",
                                    v554);
                                  if ( v553 )
                                    DisablePbCl();
                                  else
                                    EnablePbCl();
                                  v550 = isPbClEnabled() == 0;
                                  goto LABEL_922;
                                }
                                if ( !idStr::Icmp(v6, "initCreateServerSettings") )
                                {
                                  v556 = isPbSvEnabled();
                                  v557 = v556 != 0;
                                  v558 = "ENABLED";
                                  if ( !v556 )
                                    v558 = "DISABLED";
                                  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                                    common.type,
                                    "PB server is %s\n",
                                    v558);
                                  v559 = v3->guiActive;
                                  if ( v557 )
                                    v559->SetStateString(v559, "mp_create_val11_sel", "1");
                                  else
                                    v559->SetStateString(v559, "mp_create_val11_sel", "0");
                                  v3->guiActive->StateChanged(v3->guiActive, com_frameTime, 0);
                                  if ( game )
                                    game->HandleMainMenuCommands(game, v6, v3->guiActive);
                                }
                                if ( !idStr::Icmp(v6, "punkbusterServerToggle") )
                                {
                                  v560 = isPbSvEnabled();
                                  v561 = v560 != 0;
                                  v562 = "ENABLED";
                                  if ( !v560 )
                                    v562 = "DISABLED";
                                  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                                    common.type,
                                    "PB server is %s, now toggling\n",
                                    v562);
                                  if ( v561 )
                                    DisablePbSv();
                                  else
                                    EnablePbSv();
                                }
                                if ( idStr::Icmp(v6, "punkbuster") )
                                {
                                  if ( game )
                                    game->HandleMainMenuCommands(game, v6, v3->guiActive);
                                }
                                else
                                {
                                  v701.len = 0;
                                  v701.alloced = 20;
                                  v701.data = v701.baseBuffer;
                                  v701.baseBuffer[0] = 0;
                                  v563 = icmd;
                                  v704 = 47;
                                  if ( args.argc - icmd >= 1 )
                                  {
                                    ++icmd;
                                    v564 = (char *)idCmdArgs::Argv(&args, v563);
                                    idStr::operator=(&v701, v564);
                                  }
                                  if ( !idStr::Icmp(v701.data, "client") )
                                  {
                                    v565 = v3->guiMainMenu->GetStateString(
                                             v3->guiMainMenu,
                                             "gui_cl_punkbuster",
                                             &entityFilter);
                                    if ( idStr::Icmp(v565, "1") )
                                      DisablePbCl();
                                    else
                                      EnablePbCl();
                                  }
                                  if ( !idStr::Icmp(v701.data, "server") )
                                  {
                                    v566 = v3->guiMainMenu->GetStateString(
                                             v3->guiMainMenu,
                                             "gui_sv_punkbuster",
                                             &entityFilter);
                                    if ( idStr::Icmp(v566, "1") )
                                      DisablePbSv();
                                    else
                                      EnablePbSv();
                                  }
                                  idSessionLocal::SetPbMenuGuiVars(v3);
                                  v704 = -1;
                                  idStr::FreeData(&v701);
                                }
                              }
                            }
                            else
                            {
                              v528 = cvarSystem->GetCVarString(cvarSystem, "sys_lang");
                              v529 = v528;
                              lang.len = 0;
                              lang.alloced = 20;
                              lang.data = lang.baseBuffer;
                              lang.baseBuffer[0] = 0;
                              if ( v528 )
                              {
                                v530 = strlen(v528);
                                if ( v530 + 1 > 20 )
                                  idStr::ReAllocate(&lang, v530 + 1, 1);
                                v531 = lang.data;
                                v532 = (char *)v529;
                                do
                                {
                                  v533 = *v532;
                                  *v531++ = *v532++;
                                }
                                while ( v533 );
                                lang.len = v530;
                              }
                              v534 = cvarSystem->__vftable;
                              v704 = 45;
                              v535 = v534->GetCVarString(cvarSystem, "com_lastQuicksave");
                              v697.len = 0;
                              v697.alloced = 20;
                              v697.data = v697.baseBuffer;
                              v697.baseBuffer[0] = 0;
                              if ( v535 )
                              {
                                v536 = (unsigned int)&v535[strlen(v535) + 1];
                                v537 = v536 - (_DWORD)(v535 + 1);
                                v538 = v536 - (_DWORD)v535;
                                if ( v538 > 20 )
                                  idStr::ReAllocate(&v697, v538, 1);
                                v539 = v697.data;
                                v540 = v535;
                                do
                                {
                                  v541 = *v540;
                                  *v539++ = *v540++;
                                }
                                while ( v541 );
                                v697.len = v537;
                              }
                              matched = (int)cmdSystem;
                              v542 = cmdSystem->__vftable;
                              v578 = icmd;
                              LOBYTE(v704) = 46;
                              v543 = ++icmd;
                              v544 = idCmdArgs::Argv(&args, v578);
                              v542->BufferCommandText((idCmdSystem *)matched, CMD_EXEC_NOW, v544);
                              v545 = idCmdArgs::Argv(&args, v543 - 1);
                              if ( !idStr::Icmp("cvar_restart", v545) )
                              {
                                cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "exec default.cfg");
                                cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "setMachineSpec\n");
                                *(float *)&bright = cvarSystem->GetCVarFloat(cvarSystem, "r_brightness");
                                ((void (__thiscall *)(idCVarSystem *, const char *, _DWORD, _DWORD))cvarSystem->SetCVarFloat)(
                                  cvarSystem,
                                  "r_brightness",
                                  0,
                                  0);
                                ((void (__thiscall *)(idCVarSystem *, const char *, _DWORD, _DWORD))cvarSystem->SetCVarFloat)(
                                  cvarSystem,
                                  "r_brightness",
                                  LODWORD(bright),
                                  0);
                                cvarSystem->SetModifiedFlags(cvarSystem, 512);
                                v3->guiActive->SetStateInt(
                                  v3->guiActive,
                                  "com_machineSpec",
                                  com_machineSpec.internalVar->integerValue);
                                cvarSystem->SetCVarString(cvarSystem, "sys_lang", lang.data, 0);
                                cvarSystem->SetCVarString(cvarSystem, "com_lastQuicksave", v697.data, 0);
                              }
                              LOBYTE(v704) = 45;
                              idStr::FreeData(&v697);
                              v704 = -1;
                              idStr::FreeData(&lang);
                            }
                          }
                          else
                          {
                            v516 = (idDict *)v3->guiActive->State(v3->guiActive);
                            v517 = idDict::FindKey(v516, "chattext");
                            if ( v517 )
                              v518 = v517->value->data;
                            else
                              v518 = &entityFilter;
                            v519 = 0;
                            temp.len = 0;
                            temp.alloced = 20;
                            temp.data = temp.baseBuffer;
                            temp.baseBuffer[0] = 0;
                            if ( v518 )
                            {
                              v520 = (unsigned int)&v518[strlen(v518) + 1];
                              v519 = v520 - (_DWORD)(v518 + 1);
                              v521 = v520 - (_DWORD)v518;
                              if ( v521 > 20 )
                                idStr::ReAllocate(&temp, v521, 1);
                              v522 = temp.data;
                              v523 = v518;
                              do
                              {
                                v524 = *v523;
                                *v522++ = *v523++;
                              }
                              while ( v524 );
                              temp.len = v519;
                            }
                            matched = v519 + 1;
                            v704 = 44;
                            if ( v519 + 2 > temp.alloced )
                              idStr::ReAllocate(&temp, v519 + 2, 1);
                            v525 = 0;
                            v526 = 13;
                            do
                            {
                              v527 = &temp.data[v525++];
                              v527[temp.len] = v526;
                              v526 = asc_102A667C[v525];
                            }
                            while ( v526 );
                            temp.len = v519 + 1;
                            temp.data[matched] = 0;
                            v664->guiActive->SetStateString(v664->guiActive, "chattext", &entityFilter);
                            v704 = -1;
                            idStr::FreeData(&temp);
                            v3 = v664;
                          }
                        }
                        else
                        {
                          v514 = icmd;
                          if ( args.argc - icmd >= 1 )
                          {
                            ++icmd;
                            v515 = idCmdArgs::Argv(&args, v514);
                            idKeyInput::UnbindBinding(v515);
                            v3->guiMainMenu->SetKeyBindingNames(v3->guiMainMenu);
                          }
                        }
                      }
                      else
                      {
                        v679.len = 0;
                        v679.alloced = 20;
                        v679.data = v679.baseBuffer;
                        v679.baseBuffer[0] = 0;
                        v502 = icmd;
                        v704 = 43;
                        if ( args.argc - icmd >= 1 )
                        {
                          ++icmd;
                          v503 = (char *)idCmdArgs::Argv(&args, v502);
                          idStr::operator=(&v679, v503);
                        }
                        if ( idStr::Icmp(v679.data, "low") )
                        {
                          if ( idStr::Icmp(v679.data, "medium") )
                          {
                            if ( idStr::Icmp(v679.data, "high") )
                            {
                              if ( idStr::Icmp(v679.data, "ultra") )
                              {
                                if ( !idStr::Icmp(v679.data, "recommended") )
                                  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "setMachineSpec\n");
                              }
                              else
                              {
                                com_machineSpec.internalVar->InternalSetInteger(com_machineSpec.internalVar, 3);
                              }
                            }
                            else
                            {
                              com_machineSpec.internalVar->InternalSetInteger(com_machineSpec.internalVar, 2);
                            }
                          }
                          else
                          {
                            com_machineSpec.internalVar->InternalSetInteger(com_machineSpec.internalVar, 1);
                          }
                        }
                        else
                        {
                          com_machineSpec.internalVar->InternalSetInteger(com_machineSpec.internalVar, 0);
                        }
                        v3->guiActive->SetStateInt(
                          v3->guiActive,
                          "com_machineSpec",
                          com_machineSpec.internalVar->integerValue);
                        v3->guiActive->StateChanged(v3->guiActive, com_frameTime, 0);
                        matched = (int)cvarSystem->__vftable;
                        v504 = (*(int (__thiscall **)(netadrtype_t, int, _DWORD))(*(_DWORD *)common.type + 192))(
                                 common.type,
                                 com_machineSpec.internalVar->integerValue,
                                 0);
                        (*(void (__thiscall **)(idCVarSystem *, const char *, int))(matched + 40))(
                          cvarSystem,
                          "r_mode",
                          v504);
                        (*(void (__thiscall **)(netadrtype_t, int))(*(_DWORD *)common.type + 196))(
                          common.type,
                          com_machineSpec.internalVar->integerValue);
                        if ( !idStr::Icmp(v679.data, "restart") )
                        {
                          v3->guiActive->HandleNamedEvent(v3->guiActive, "cvar write render");
                          cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "vid_restart\n");
                        }
                        v704 = -1;
                        idStr::FreeData(&v679);
                      }
                    }
                    else
                    {
                      vcmd.len = 0;
                      vcmd.alloced = 20;
                      vcmd.data = vcmd.baseBuffer;
                      vcmd.baseBuffer[0] = 0;
                      v498 = icmd;
                      v704 = 42;
                      if ( args.argc - icmd < 1
                        || (++icmd, v499 = (char *)idCmdArgs::Argv(&args, v498),
                                    idStr::operator=(&vcmd, v499),
                                    !vcmd.len)
                        || !idStr::Icmp(vcmd.data, "speakers") )
                      {
                        matched = cvarSystem->GetCVarInteger(cvarSystem, "s_numberOfSpeakers");
                        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "s_restart\n");
                        if ( matched != cvarSystem->GetCVarInteger(cvarSystem, "s_numberOfSpeakers") )
                        {
                          matched = (int)v3->__vftable;
                          v500 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)common.type + 168))(
                                   common.type,
                                   "#str_104141",
                                   -1,
                                   1,
                                   0,
                                   0,
                                   0);
                          v501 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type
                                                                                             + 168))(
                                   common.type,
                                   "#str_104142",
                                   -1,
                                   v500);
                          (*(void (__thiscall **)(idSessionLocal *, _DWORD, int))(matched + 76))(v3, 0, v501);
                        }
                      }
                      if ( !idStr::Icmp(vcmd.data, "drivar") )
                        cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "s_restart\n");
                      v704 = -1;
                      idStr::FreeData(&vcmd);
                    }
                  }
                  else
                  {
                    v491 = icmd;
                    if ( args.argc - icmd >= 1 )
                    {
                      ++icmd;
                      v492 = idCmdArgs::Argv(&args, v491);
                      matched = (int)v492;
                      v694.len = 0;
                      v694.alloced = 20;
                      v694.data = v694.baseBuffer;
                      v694.baseBuffer[0] = 0;
                      if ( v492 )
                      {
                        v493 = strlen(v492);
                        if ( v493 + 1 > 20 )
                          idStr::ReAllocate(&v694, v493 + 1, 1);
                        v494 = v694.data;
                        v495 = (char *)matched;
                        do
                        {
                          v496 = *v495;
                          *v494++ = *v495++;
                        }
                        while ( v496 );
                        v694.len = v493;
                      }
                      v497 = soundSystem->__vftable;
                      v704 = 41;
                      v497->PlayShaderDirectly(soundSystem, 2, v694.data, 2);
                      v704 = -1;
                      idStr::FreeData(&v694);
                    }
                  }
                }
                else
                {
                  v480 = icmd;
                  if ( args.argc - icmd >= 1 )
                  {
                    ++icmd;
                    v481 = idCmdArgs::Argv(&args, v480);
                    v482 = 0;
                    snd.len = 0;
                    snd.alloced = 20;
                    snd.data = snd.baseBuffer;
                    snd.baseBuffer[0] = 0;
                    if ( v481 )
                    {
                      v483 = (unsigned int)&v481[strlen(v481) + 1];
                      v484 = v483 - (_DWORD)(v481 + 1);
                      v485 = v483 - (_DWORD)v481;
                      if ( v485 > 20 )
                        idStr::ReAllocate(&snd, v485, 1);
                      v486 = snd.data;
                      v487 = v481;
                      do
                      {
                        v488 = *v487;
                        *v486++ = *v487++;
                      }
                      while ( v488 );
                      v482 = v484;
                      snd.len = v484;
                    }
                    matched = 1;
                    v704 = 40;
                    if ( v482 == 1 )
                    {
                      matched = atoi(snd.data);
                      v489 = icmd++;
                      v490 = (char *)idCmdArgs::Argv(&args, v489);
                      idStr::operator=(&snd, v490);
                    }
                    soundSystem->PlayShaderDirectly(soundSystem, 2, snd.data, matched);
                    v704 = -1;
                    idStr::FreeData(&snd);
                  }
                }
              }
              else if ( args.argc - icmd >= 2 )
              {
                v472 = icmd + 1;
                v473 = idCmdArgs::Argv(&args, icmd);
                v474 = atoi(v473);
                icmd = v472 + 1;
                v475 = idCmdArgs::Argv(&args, v472);
                matched = (int)v475;
                bind.len = 0;
                bind.alloced = 20;
                bind.data = bind.baseBuffer;
                bind.baseBuffer[0] = 0;
                if ( v475 )
                {
                  v476 = strlen(v475);
                  if ( v476 + 1 > 20 )
                    idStr::ReAllocate(&bind, v476 + 1, 1);
                  v477 = bind.data;
                  v478 = (char *)matched;
                  do
                  {
                    v479 = *v478;
                    *v477++ = *v478++;
                  }
                  while ( v479 );
                  bind.len = v476;
                }
                v704 = 39;
                if ( idKeyInput::NumBinds(bind.data) >= 2 && !idKeyInput::KeyIsBoundTo(v474, bind.data) )
                  idKeyInput::UnbindBinding(bind.data);
                idKeyInput::SetBinding(v474, bind.data);
                v3->guiMainMenu->SetKeyBindingNames(v3->guiMainMenu);
                v704 = -1;
                idStr::FreeData(&bind);
              }
            }
            else
            {
              matched = (int)cvarSystem->GetCVarString(cvarSystem, "com_lastQuicksave");
              lastQuickSave.len = 0;
              lastQuickSave.alloced = 20;
              lastQuickSave.data = lastQuickSave.baseBuffer;
              lastQuickSave.baseBuffer[0] = 0;
              if ( matched )
              {
                v465 = matched + strlen((const char *)matched) + 1;
                v466 = v465 - (matched + 1);
                v467 = v465 - matched;
                if ( v467 > 20 )
                  idStr::ReAllocate(&lastQuickSave, v467, 1);
                v468 = lastQuickSave.data;
                v469 = (char *)matched;
                do
                {
                  v470 = *v469;
                  *v468++ = *v469++;
                }
                while ( v470 );
                lastQuickSave.len = v466;
              }
              v471 = cmdSystem->__vftable;
              v704 = 38;
              v471->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "exec default.cfg");
              v3->guiMainMenu->SetKeyBindingNames(v3->guiMainMenu);
              cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, "setPMCVars");
              cvarSystem->SetCVarString(cvarSystem, "com_lastQuicksave", lastQuickSave.data, 0);
              v704 = -1;
              idStr::FreeData(&lastQuickSave);
            }
          }
          else if ( v3->mapSpawned )
          {
            idKeyInput::ClearStates();
            v3->ExitMenu(v3);
          }
        }
        else
        {
          v452 = v3->guiActive->GetStateInt(v3->guiActive, "sa_banList_sel_0", "0");
          if ( v452 != -1 )
          {
            v453 = v3->guiActive->__vftable;
            v454 = va("sa_banList_item_%d", v452);
            v455 = (int)v453->GetStateString(v3->guiActive, v454, &entityFilter);
            v456 = (char *)(v455 + 4);
            guid.len = 0;
            guid.alloced = 20;
            guid.data = guid.baseBuffer;
            guid.baseBuffer[0] = 0;
            if ( v455 != -4 )
            {
              v457 = v455 + 4 + strlen((const char *)(v455 + 4)) + 1;
              v458 = v457 - (_DWORD)(v456 + 1);
              v459 = v457 - (_DWORD)v456;
              if ( v459 > 20 )
                idStr::ReAllocate(&guid, v459, 1);
              v460 = guid.data;
              do
              {
                v461 = *v456;
                *v460++ = *v456++;
              }
              while ( v461 );
              guid.len = v458;
            }
            v704 = 37;
            v462 = idStr::ReplaceChar(&guid, 9, 0);
            v463 = v462->len;
            v464 = v462->len + 1;
            if ( v464 > guid.alloced )
              idStr::ReAllocate(&guid, v464, 0);
            qmemcpy(guid.data, v462->data, v463);
            guid.data[v463] = 0;
            guid.len = v463;
            matched = (int)(guid.data + 1);
            idStr::operator=(&guid, &guid.data[strlen(guid.data) + 1]);
            game->RemoveGuidFromBanList(game, guid.data);
            game->PopulateBanList(game, v664->guiActive);
            v704 = -1;
            idStr::FreeData(&guid);
            v3 = v664;
          }
        }
      }
      else
      {
        v116 = (idDict *)v3->guiActive->State(v3->guiActive);
        v117 = idDict::FindKey(v116, "friendslist_sel_0");
        if ( v117 )
          v118 = v117->value->data;
        else
          v118 = "0";
        v119 = atoi(v118);
        if ( v119 < 0 || v119 >= v3->serverScanGUI.friendsList.num )
        {
LABEL_192:
          v3->guiActive->SetStateString(v3->guiActive, "friendslist_sel_0", "-1");
          goto LABEL_952;
        }
        rvServerScanGUI::RemoveFromFriendsList(&v3->serverScanGUI, (int)v6, (signed int)v3, v119);
      }
    }
    else
    {
      v110 = (idDict *)v3->guiActive->State(v3->guiActive);
      v111 = idDict::FindKey(v110, "friendslist_sel_0");
      if ( v111 )
        v112 = v111->value->data;
      else
        v112 = "0";
      v113 = atoi(v112);
      if ( v113 < 0 || v113 >= v3->serverScanGUI.friendsList.num )
        goto LABEL_192;
      rvServerScanGUI::GetFriendServer(&v3->serverScanGUI, &friendServer, v113);
      if ( friendServer.type )
      {
        matched = (int)cmdSystem->__vftable;
        v114 = Sys_NetAdrToString(friendServer);
        v115 = va("connect %s\n", v114);
        (*(void (__thiscall **)(idCmdSystem *, _DWORD, char *))(matched + 32))(cmdSystem, 0, v115);
      }
    }
LABEL_952:
    argc = args.argc;
    if ( icmd >= args.argc )
      return;
    v5 = icmd;
  }
  v65 = (idDict *)v3->guiActive->State(v3->guiActive);
  v66 = idDict::FindKey(v65, "serverList_sel_0");
  if ( v66 )
    v67 = v66->value->data;
  else
    v67 = "0";
  v68 = atoi(v67);
  matched = v68;
  if ( v68 == -1 )
    goto LABEL_952;
  if ( !rvServerScanGUI::IsPerformanceFiltered(&v3->serverScanGUI, v68) || com_machineSpec.internalVar->integerValue )
  {
    v73 = cmdSystem->__vftable;
  }
  else
  {
    v69 = v3->__vftable;
    v70 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int, const char *, const char *, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_104314",
            -1,
            1,
            "yes",
            "no",
            1);
    v71 = (*(int (__thiscall **)(netadrtype_t, const char *, int, int))(*(_DWORD *)common.type + 168))(
            common.type,
            "#str_106781",
            -1,
            v70);
    v72 = (const char *)((int (__thiscall *)(idSessionLocal *, int, int))v69->MessageBoxA)(v3, 3, v71);
    if ( idStr::Icmp("yes", v72) )
      return;
    v73 = cmdSystem->__vftable;
  }
  v74 = va("Connect %d\n", matched);
  v73->BufferCommandText(cmdSystem, CMD_EXEC_NOW, v74);
}

// FUNC: public: void __thiscall idSessionLocal::AddMapFunc(char const *,class idListGUI *,char const *,class idListGUI *)
void __thiscall idSessionLocal::AddMapFunc(
        idSessionLocal *this,
        const char *availList,
        idListGUI *availGUI,
        const char *cycleList,
        idListGUI *cycleGUI)
{
  const char *v6; // esi
  idDict *v7; // eax
  const idKeyValue *Key; // eax
  idStr *v9; // ebx
  const char *data; // eax
  int v11; // eax
  int v12; // eax
  idStr *v13; // edi
  int granularity; // esi
  bool v15; // cc
  int *v16; // eax
  int v17; // esi
  unsigned int v18; // edi
  idStr *v19; // ebx
  int v20; // eax
  int num; // ebx
  int size; // esi
  int v23; // esi
  idStr *v24; // eax
  char *v25; // esi
  idStr *list; // edi
  int *v27; // eax
  idStr *v28; // ebx
  int v29; // esi
  unsigned int v30; // edi
  idStr *v31; // ebx
  int len; // esi
  idStr *v33; // ebx
  int v34; // eax
  unsigned int v35; // ecx
  char *v36; // esi
  char *v37; // edi
  char v38; // al
  char *v39; // edi
  char *v40; // esi
  int v41; // ecx
  int v42; // esi
  int v43; // ecx
  int v44; // ecx
  idStr *v45; // eax
  int v46; // esi
  idStr *v47; // ebx
  char *v48; // edi
  unsigned int v49; // ecx
  char *v50; // esi
  char v51; // dl
  char *v52; // edi
  char *v53; // esi
  int v54; // ecx
  const idStr *v55; // eax
  idStr *v56; // esi
  unsigned int v57; // ebx
  int v58; // eax
  char *v59; // esi
  char *v60; // edi
  char *v61; // esi
  int v62; // ecx
  const char *v63; // esi
  idDict *v64; // eax
  const idKeyValue *v65; // eax
  const char *v66; // eax
  int j; // [esp+Ch] [ebp-88h]
  int k; // [esp+Ch] [ebp-88h]
  int v69; // [esp+10h] [ebp-84h]
  idStr *v70; // [esp+10h] [ebp-84h]
  idStr *v71; // [esp+14h] [ebp-80h]
  int v72; // [esp+14h] [ebp-80h]
  int v73; // [esp+14h] [ebp-80h]
  int i; // [esp+18h] [ebp-7Ch]
  int ia; // [esp+18h] [ebp-7Ch]
  int ib; // [esp+18h] [ebp-7Ch]
  int ic; // [esp+18h] [ebp-7Ch]
  int v78; // [esp+1Ch] [ebp-78h]
  int currentSel; // [esp+20h] [ebp-74h]
  int v80; // [esp+24h] [ebp-70h]
  int v81; // [esp+24h] [ebp-70h]
  idStr mapList; // [esp+28h] [ebp-6Ch] BYREF
  idStr v83; // [esp+48h] [ebp-4Ch] BYREF
  idStr result; // [esp+68h] [ebp-2Ch] BYREF
  int v85; // [esp+90h] [ebp-4h]

  v6 = va("%s_sel_0", availList);
  v7 = (idDict *)this->guiActive->State(this->guiActive);
  Key = idDict::FindKey(v7, v6);
  v9 = 0;
  if ( Key )
    data = Key->value->data;
  else
    data = "-1";
  v11 = atoi(data);
  currentSel = v11;
  if ( v11 > -1 && this->mpAvailMapList.num )
  {
    v12 = v11;
    v13 = &this->mpAvailMapList.list[v12];
    v80 = v12 * 32;
    v71 = v13;
    if ( !this->mpCycleMapList.list )
    {
      granularity = this->mpCycleMapList.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->mpCycleMapList.size )
        {
          v15 = granularity < this->mpCycleMapList.num;
          this->mpCycleMapList.size = granularity;
          if ( v15 )
            this->mpCycleMapList.num = granularity;
          v16 = (int *)Memory::Allocate(32 * granularity + 4);
          v85 = 0;
          if ( v16 )
          {
            v9 = (idStr *)(v16 + 1);
            *v16 = granularity;
            `eh vector constructor iterator'(
              v16 + 1,
              0x20u,
              granularity,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          v15 = this->mpCycleMapList.num <= 0;
          v85 = -1;
          this->mpCycleMapList.list = v9;
          v69 = 0;
          if ( !v15 )
          {
            v17 = 0;
            for ( j = 0; ; v17 = j )
            {
              v18 = *(_DWORD *)v17;
              v19 = (idStr *)((char *)this->mpCycleMapList.list + v17);
              v20 = *(_DWORD *)v17 + 1;
              i = *(_DWORD *)v17;
              if ( v20 > v19->alloced )
                idStr::ReAllocate(v19, v20, 0);
              j += 32;
              qmemcpy(v19->data, *(const void **)(v17 + 4), v18);
              v19->data[i] = 0;
              v19->len = i;
              if ( ++v69 >= this->mpCycleMapList.num )
                break;
            }
            v13 = v71;
          }
        }
      }
      else
      {
        this->mpCycleMapList.list = 0;
        this->mpCycleMapList.num = 0;
        this->mpCycleMapList.size = 0;
      }
    }
    num = this->mpCycleMapList.num;
    size = this->mpCycleMapList.size;
    if ( num == size )
    {
      if ( !this->mpCycleMapList.granularity )
        this->mpCycleMapList.granularity = 16;
      v23 = this->mpCycleMapList.granularity
          + size
          - (this->mpCycleMapList.granularity + size) % this->mpCycleMapList.granularity;
      if ( v23 > 0 )
      {
        if ( v23 != this->mpCycleMapList.size )
        {
          list = this->mpCycleMapList.list;
          v70 = list;
          this->mpCycleMapList.size = v23;
          if ( v23 < num )
            this->mpCycleMapList.num = v23;
          v27 = (int *)Memory::Allocate(32 * v23 + 4);
          v85 = 1;
          if ( v27 )
          {
            v28 = (idStr *)(v27 + 1);
            *v27 = v23;
            `eh vector constructor iterator'(
              v27 + 1,
              0x20u,
              v23,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v28 = 0;
          }
          v29 = 0;
          v15 = this->mpCycleMapList.num <= 0;
          v85 = -1;
          this->mpCycleMapList.list = v28;
          ia = 0;
          if ( !v15 )
          {
            for ( k = 0; ; v29 = k )
            {
              v30 = *(int *)((char *)&list->len + v29);
              v31 = (idStr *)((char *)this->mpCycleMapList.list + v29);
              if ( (signed int)(v30 + 1) > v31->alloced )
                idStr::ReAllocate(v31, v30 + 1, 0);
              k += 32;
              qmemcpy(v31->data, *(const void **)((char *)&v70->data + v29), v30);
              v31->data[v30] = 0;
              v31->len = v30;
              v15 = ++ia < this->mpCycleMapList.num;
              list = v70;
              if ( !v15 )
                break;
            }
          }
          if ( list )
          {
            `eh vector destructor iterator'(
              list,
              0x20u,
              *(_DWORD *)&list[-1].baseBuffer[16],
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(&list[-1].baseBuffer[16]);
          }
          v13 = v71;
        }
      }
      else
      {
        v24 = this->mpCycleMapList.list;
        if ( v24 )
        {
          v25 = &v24[-1].baseBuffer[16];
          `eh vector destructor iterator'(
            v24,
            0x20u,
            *(_DWORD *)&v24[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(v25);
        }
        this->mpCycleMapList.list = 0;
        this->mpCycleMapList.num = 0;
        this->mpCycleMapList.size = 0;
      }
    }
    len = v13->len;
    v33 = &this->mpCycleMapList.list[this->mpCycleMapList.num];
    v34 = v13->len + 1;
    v78 = v13->len;
    if ( v34 > v33->alloced )
      idStr::ReAllocate(v33, v34, 0);
    v35 = len;
    v36 = v13->data;
    v37 = v33->data;
    v38 = v35;
    v35 >>= 2;
    qmemcpy(v37, v36, 4 * v35);
    v40 = &v36[4 * v35];
    v39 = &v37[4 * v35];
    v41 = v38 & 3;
    qmemcpy(v39, v40, v41);
    v42 = (int)&v40[v41];
    v33->data[v78] = 0;
    v33->len = v78;
    ++this->mpCycleMapList.num;
    if ( currentSel >= 0 )
    {
      v43 = this->mpAvailMapList.num;
      if ( currentSel < v43 )
      {
        v44 = v43 - 1;
        this->mpAvailMapList.num = v44;
        ib = currentSel;
        if ( currentSel < v44 )
        {
          v72 = v80;
          do
          {
            v45 = this->mpAvailMapList.list;
            v46 = *(int *)((char *)&v45[1].len + v72);
            v47 = (idStr *)((char *)v45 + v72);
            v81 = v46;
            if ( v46 + 1 > *(int *)((char *)&v45->alloced + v72) )
              idStr::ReAllocate(v47, v46 + 1, 0);
            v48 = v47->data;
            v72 += 32;
            v49 = v46;
            v50 = v47[1].data;
            v51 = v49;
            v49 >>= 2;
            qmemcpy(v48, v50, 4 * v49);
            v53 = &v50[4 * v49];
            v52 = &v48[4 * v49];
            v54 = v51 & 3;
            qmemcpy(v52, v53, v54);
            v42 = (int)&v53[v54];
            v47->data[v81] = 0;
            v47->len = v81;
            ++ib;
          }
          while ( ib < this->mpAvailMapList.num );
        }
      }
    }
    mapList.len = 0;
    mapList.alloced = 20;
    mapList.data = mapList.baseBuffer;
    mapList.baseBuffer[0] = 0;
    v15 = this->mpCycleMapList.num <= 0;
    v85 = 2;
    ic = 0;
    if ( !v15 )
    {
      v73 = 0;
      do
      {
        v55 = operator+(&result, &mapList, &this->mpCycleMapList.list[v73]);
        LOBYTE(v85) = 3;
        v56 = operator+(&v83, v55, ";");
        v57 = v56->len;
        v58 = v56->len + 1;
        LOBYTE(v85) = 4;
        if ( v58 > mapList.alloced )
          idStr::ReAllocate(&mapList, v58, 0);
        v59 = v56->data;
        v60 = mapList.data;
        qmemcpy(mapList.data, v59, 4 * (v57 >> 2));
        v61 = &v59[4 * (v57 >> 2)];
        v62 = v57 & 3;
        qmemcpy(&v60[4 * (v57 >> 2)], v61, v62);
        v42 = (int)&v61[v62];
        mapList.data[v57] = 0;
        mapList.len = v57;
        LOBYTE(v85) = 3;
        idStr::FreeData(&v83);
        LOBYTE(v85) = 2;
        idStr::FreeData(&result);
        ++v73;
        ++ic;
      }
      while ( ic < this->mpCycleMapList.num );
    }
    cvarSystem->SetCVarString(cvarSystem, "si_mapList", mapList.data, 0);
    idSessionLocal::PopulateMPMapList(this, (int)this, v42, availList, availGUI, cycleList, cycleGUI);
    v85 = -1;
    idStr::FreeData(&mapList);
  }
  if ( this->mpCycleMapList.num > 1 )
    this->guiActive->SetStateInt(this->guiActive, "noMaps", 0);
  v63 = va("%s_item_0", cycleList);
  v64 = (idDict *)this->guiActive->State(this->guiActive);
  v65 = idDict::FindKey(v64, v63);
  if ( v65 )
    v66 = v65->value->data;
  else
    v66 = &entityFilter;
  cvarSystem->SetCVarString(cvarSystem, "si_map", v66, 0);
}

// FUNC: public: void __thiscall idSessionLocal::RemoveMapFunc(char const *,class idListGUI *,char const *,class idListGUI *)
void __thiscall idSessionLocal::RemoveMapFunc(
        idSessionLocal *this,
        const char *availList,
        idListGUI *availGUI,
        const char *cycleList,
        idListGUI *cycleGUI)
{
  const char *v6; // esi
  idDict *v7; // eax
  const idKeyValue *Key; // eax
  idStr *v9; // ebx
  const char *data; // eax
  int v11; // eax
  int v12; // eax
  idStr *v13; // edi
  int granularity; // esi
  bool v15; // cc
  int *v16; // eax
  int v17; // esi
  unsigned int v18; // edi
  idStr *v19; // ebx
  int v20; // eax
  int num; // ebx
  int size; // esi
  int v23; // esi
  idStr *v24; // eax
  char *v25; // esi
  idStr *list; // edi
  int *v27; // eax
  idStr *v28; // ebx
  int v29; // esi
  unsigned int v30; // edi
  idStr *v31; // ebx
  int len; // esi
  idStr *v33; // ebx
  int v34; // eax
  unsigned int v35; // ecx
  char *v36; // esi
  char *v37; // edi
  char v38; // al
  char *v39; // edi
  char *v40; // esi
  int v41; // ecx
  int v42; // esi
  int v43; // ecx
  int v44; // ecx
  idStr *v45; // eax
  int v46; // esi
  idStr *v47; // ebx
  char *v48; // edi
  unsigned int v49; // ecx
  char *v50; // esi
  char v51; // dl
  char *v52; // edi
  char *v53; // esi
  int v54; // ecx
  const idStr *v55; // eax
  idStr *v56; // esi
  unsigned int v57; // ebx
  int v58; // eax
  char *v59; // esi
  char *v60; // edi
  char *v61; // esi
  int v62; // ecx
  const char *v63; // esi
  idDict *v64; // eax
  const idKeyValue *v65; // eax
  const char *v66; // eax
  int j; // [esp+Ch] [ebp-88h]
  int k; // [esp+Ch] [ebp-88h]
  int v69; // [esp+10h] [ebp-84h]
  idStr *v70; // [esp+10h] [ebp-84h]
  idStr *v71; // [esp+14h] [ebp-80h]
  int v72; // [esp+14h] [ebp-80h]
  int v73; // [esp+14h] [ebp-80h]
  int i; // [esp+18h] [ebp-7Ch]
  int ia; // [esp+18h] [ebp-7Ch]
  int ib; // [esp+18h] [ebp-7Ch]
  int ic; // [esp+18h] [ebp-7Ch]
  int v78; // [esp+1Ch] [ebp-78h]
  int currentSel; // [esp+20h] [ebp-74h]
  int v80; // [esp+24h] [ebp-70h]
  int v81; // [esp+24h] [ebp-70h]
  idStr mapList; // [esp+28h] [ebp-6Ch] BYREF
  idStr v83; // [esp+48h] [ebp-4Ch] BYREF
  idStr result; // [esp+68h] [ebp-2Ch] BYREF
  int v85; // [esp+90h] [ebp-4h]

  v6 = va("%s_sel_0", cycleList);
  v7 = (idDict *)this->guiActive->State(this->guiActive);
  Key = idDict::FindKey(v7, v6);
  v9 = 0;
  if ( Key )
    data = Key->value->data;
  else
    data = "-1";
  v11 = atoi(data);
  currentSel = v11;
  if ( v11 > -1 )
  {
    if ( this->mpCycleMapList.num <= 1 )
      goto LABEL_60;
    v12 = v11;
    v13 = &this->mpCycleMapList.list[v12];
    v80 = v12 * 32;
    v71 = v13;
    if ( !this->mpAvailMapList.list )
    {
      granularity = this->mpAvailMapList.granularity;
      if ( granularity > 0 )
      {
        if ( granularity != this->mpAvailMapList.size )
        {
          v15 = granularity < this->mpAvailMapList.num;
          this->mpAvailMapList.size = granularity;
          if ( v15 )
            this->mpAvailMapList.num = granularity;
          v16 = (int *)Memory::Allocate(32 * granularity + 4);
          v85 = 0;
          if ( v16 )
          {
            v9 = (idStr *)(v16 + 1);
            *v16 = granularity;
            `eh vector constructor iterator'(
              v16 + 1,
              0x20u,
              granularity,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          v15 = this->mpAvailMapList.num <= 0;
          v85 = -1;
          this->mpAvailMapList.list = v9;
          v69 = 0;
          if ( !v15 )
          {
            v17 = 0;
            for ( j = 0; ; v17 = j )
            {
              v18 = *(_DWORD *)v17;
              v19 = (idStr *)((char *)this->mpAvailMapList.list + v17);
              v20 = *(_DWORD *)v17 + 1;
              i = *(_DWORD *)v17;
              if ( v20 > v19->alloced )
                idStr::ReAllocate(v19, v20, 0);
              j += 32;
              qmemcpy(v19->data, *(const void **)(v17 + 4), v18);
              v19->data[i] = 0;
              v19->len = i;
              if ( ++v69 >= this->mpAvailMapList.num )
                break;
            }
            v13 = v71;
          }
        }
      }
      else
      {
        this->mpAvailMapList.list = 0;
        this->mpAvailMapList.num = 0;
        this->mpAvailMapList.size = 0;
      }
    }
    num = this->mpAvailMapList.num;
    size = this->mpAvailMapList.size;
    if ( num == size )
    {
      if ( !this->mpAvailMapList.granularity )
        this->mpAvailMapList.granularity = 16;
      v23 = this->mpAvailMapList.granularity
          + size
          - (this->mpAvailMapList.granularity + size) % this->mpAvailMapList.granularity;
      if ( v23 > 0 )
      {
        if ( v23 != this->mpAvailMapList.size )
        {
          list = this->mpAvailMapList.list;
          v70 = list;
          this->mpAvailMapList.size = v23;
          if ( v23 < num )
            this->mpAvailMapList.num = v23;
          v27 = (int *)Memory::Allocate(32 * v23 + 4);
          v85 = 1;
          if ( v27 )
          {
            v28 = (idStr *)(v27 + 1);
            *v27 = v23;
            `eh vector constructor iterator'(
              v27 + 1,
              0x20u,
              v23,
              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v28 = 0;
          }
          v29 = 0;
          v15 = this->mpAvailMapList.num <= 0;
          v85 = -1;
          this->mpAvailMapList.list = v28;
          ia = 0;
          if ( !v15 )
          {
            for ( k = 0; ; v29 = k )
            {
              v30 = *(int *)((char *)&list->len + v29);
              v31 = (idStr *)((char *)this->mpAvailMapList.list + v29);
              if ( (signed int)(v30 + 1) > v31->alloced )
                idStr::ReAllocate(v31, v30 + 1, 0);
              k += 32;
              qmemcpy(v31->data, *(const void **)((char *)&v70->data + v29), v30);
              v31->data[v30] = 0;
              v31->len = v30;
              v15 = ++ia < this->mpAvailMapList.num;
              list = v70;
              if ( !v15 )
                break;
            }
          }
          if ( list )
          {
            `eh vector destructor iterator'(
              list,
              0x20u,
              *(_DWORD *)&list[-1].baseBuffer[16],
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(&list[-1].baseBuffer[16]);
          }
          v13 = v71;
        }
      }
      else
      {
        v24 = this->mpAvailMapList.list;
        if ( v24 )
        {
          v25 = &v24[-1].baseBuffer[16];
          `eh vector destructor iterator'(
            v24,
            0x20u,
            *(_DWORD *)&v24[-1].baseBuffer[16],
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(v25);
        }
        this->mpAvailMapList.list = 0;
        this->mpAvailMapList.num = 0;
        this->mpAvailMapList.size = 0;
      }
    }
    len = v13->len;
    v33 = &this->mpAvailMapList.list[this->mpAvailMapList.num];
    v34 = v13->len + 1;
    v78 = v13->len;
    if ( v34 > v33->alloced )
      idStr::ReAllocate(v33, v34, 0);
    v35 = len;
    v36 = v13->data;
    v37 = v33->data;
    v38 = v35;
    v35 >>= 2;
    qmemcpy(v37, v36, 4 * v35);
    v40 = &v36[4 * v35];
    v39 = &v37[4 * v35];
    v41 = v38 & 3;
    qmemcpy(v39, v40, v41);
    v42 = (int)&v40[v41];
    v33->data[v78] = 0;
    v33->len = v78;
    ++this->mpAvailMapList.num;
    if ( currentSel >= 0 )
    {
      v43 = this->mpCycleMapList.num;
      if ( currentSel < v43 )
      {
        v44 = v43 - 1;
        this->mpCycleMapList.num = v44;
        ib = currentSel;
        if ( currentSel < v44 )
        {
          v72 = v80;
          do
          {
            v45 = this->mpCycleMapList.list;
            v46 = *(int *)((char *)&v45[1].len + v72);
            v47 = (idStr *)((char *)v45 + v72);
            v81 = v46;
            if ( v46 + 1 > *(int *)((char *)&v45->alloced + v72) )
              idStr::ReAllocate(v47, v46 + 1, 0);
            v48 = v47->data;
            v72 += 32;
            v49 = v46;
            v50 = v47[1].data;
            v51 = v49;
            v49 >>= 2;
            qmemcpy(v48, v50, 4 * v49);
            v53 = &v50[4 * v49];
            v52 = &v48[4 * v49];
            v54 = v51 & 3;
            qmemcpy(v52, v53, v54);
            v42 = (int)&v53[v54];
            v47->data[v81] = 0;
            v47->len = v81;
            ++ib;
          }
          while ( ib < this->mpCycleMapList.num );
        }
      }
    }
    mapList.len = 0;
    mapList.alloced = 20;
    mapList.data = mapList.baseBuffer;
    mapList.baseBuffer[0] = 0;
    v15 = this->mpCycleMapList.num <= 0;
    v85 = 2;
    ic = 0;
    if ( !v15 )
    {
      v73 = 0;
      do
      {
        v55 = operator+(&result, &mapList, &this->mpCycleMapList.list[v73]);
        LOBYTE(v85) = 3;
        v56 = operator+(&v83, v55, ";");
        v57 = v56->len;
        v58 = v56->len + 1;
        LOBYTE(v85) = 4;
        if ( v58 > mapList.alloced )
          idStr::ReAllocate(&mapList, v58, 0);
        v59 = v56->data;
        v60 = mapList.data;
        qmemcpy(mapList.data, v59, 4 * (v57 >> 2));
        v61 = &v59[4 * (v57 >> 2)];
        v62 = v57 & 3;
        qmemcpy(&v60[4 * (v57 >> 2)], v61, v62);
        v42 = (int)&v61[v62];
        mapList.data[v57] = 0;
        mapList.len = v57;
        LOBYTE(v85) = 3;
        idStr::FreeData(&v83);
        LOBYTE(v85) = 2;
        idStr::FreeData(&result);
        ++v73;
        ++ic;
      }
      while ( ic < this->mpCycleMapList.num );
    }
    cvarSystem->SetCVarString(cvarSystem, "si_mapList", mapList.data, 0);
    idSessionLocal::PopulateMPMapList(this, (int)this, v42, availList, availGUI, cycleList, cycleGUI);
    v85 = -1;
    idStr::FreeData(&mapList);
  }
  if ( this->mpCycleMapList.num > 1 )
    this->guiActive->SetStateInt(this->guiActive, "noMaps", 1);
LABEL_60:
  v63 = va("%s_item_0", cycleList);
  v64 = (idDict *)this->guiActive->State(this->guiActive);
  v65 = idDict::FindKey(v64, v63);
  if ( v65 )
    v66 = v65->value->data;
  else
    v66 = &entityFilter;
  cvarSystem->SetCVarString(cvarSystem, "si_map", v66, 0);
}

// FUNC: public: void __thiscall idSessionLocal::InitNotes(bool,char const *)
void __userpurge idSessionLocal::InitNotes(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<edi>,
        int a4@<esi>,
        bool Force,
        const char *DefaultCategory,
        int a7,
        int a8,
        char *s1)
{
  idDict *v10; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  bool v13; // al
  int v14; // eax
  char v15; // cl
  idCVarSystem_vtbl *v16; // edx
  const char *v17; // eax
  const char *v18; // esi
  unsigned int v19; // edi
  char v20; // cl
  int i; // eax
  int v22; // edx
  char *v23; // eax
  idStr *v24; // esi
  unsigned int len; // ebx
  int v26; // eax
  int v27; // eax
  idUserInterface *guiActive; // ecx
  idDict *v29; // eax
  const idKeyValue *v30; // eax
  const char *v31; // eax
  int v32; // eax
  const char *v33; // esi
  idDict *v34; // eax
  idStr names; // [esp+B0h] [ebp-6Ch] BYREF
  idStr filter; // [esp+D0h] [ebp-4Ch] BYREF
  idStr result; // [esp+FCh] [ebp-20h] BYREF

  v10 = (idDict *)this->guiActive->State(this->guiActive);
  Key = idDict::FindKey(v10, "init");
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  v13 = atoi(data) != 0;
  if ( Force || !v13 )
  {
    this->guiActive->SetStateInt(this->guiActive, "init", 1);
    this->guiActive->SetStateString(this->guiActive, "description", &entityFilter);
    this->guiActive->SetStateString(this->guiActive, "submitter", &entityFilter);
    this->guiActive->SetStateString(this->guiActive, aDate_0, &entityFilter);
    this->guiActive->SetStateString(this->guiActive, "version", &entityFilter);
    this->guiActive->SetStateString(this->guiActive, "categoryText", &entityFilter);
    this->guiActive->SetStateString(this->guiActive, "location", &entityFilter);
    this->guiActive->SetStateString(this->guiActive, "assignedToText", &entityFilter);
    this->guiActive->SetStateString(this->guiActive, "note", &entityFilter);
    this->guiActive->SetStateString(this->guiActive, "completed", &entityFilter);
    names.alloced = 20;
    names.data = names.baseBuffer;
    names.baseBuffer[0] = 0;
    v14 = 0;
    do
    {
      v15 = asc_102A5CB4[v14];
      names.baseBuffer[v14++] = v15;
    }
    while ( v15 );
    names.len = 1;
    v16 = cvarSystem->__vftable;
    *(_DWORD *)&result.baseBuffer[16] = 0;
    v17 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, int, int, int))v16->GetCVarString)(
                          cvarSystem,
                          "viewnotes_names",
                          a3,
                          a4,
                          a2);
    v18 = v17;
    if ( v17 )
    {
      v19 = strlen(v17) + *(_DWORD *)names.baseBuffer;
      if ( (int)(v19 + 1) > *(int *)&names.baseBuffer[8] )
        idStr::ReAllocate((idStr *)names.baseBuffer, v19 + 1, 1);
      v20 = *v18;
      for ( i = 0; v20; v20 = v18[i] )
      {
        v22 = i + *(_DWORD *)&names.baseBuffer[4];
        ++i;
        *(_BYTE *)(v22 + *(_DWORD *)names.baseBuffer) = v20;
      }
      *(_DWORD *)names.baseBuffer = v19;
      *(_BYTE *)(*(_DWORD *)&names.baseBuffer[4] + v19) = 0;
    }
    operator+((idStr *)filter.baseBuffer, "None", (const idStr *)names.baseBuffer);
    ParseChoicesIntoList(this->guiActive, (idStr *)filter.baseBuffer, 1, "pop_assignedTo");
    ParseChoicesIntoList(this->guiActive, (idStr *)filter.baseBuffer, 1, "pop_filterAssignedTo");
    this->guiActive->SetStateString(this->guiActive, "filterAssignedToText", "None");
    this->guiActive->SetStateInt(this->guiActive, "pop_filterAssignedTo_sel_0", 0);
    this->guiActive->SetStateString(this->guiActive, "assignedTo", &entityFilter);
    this->guiActive->SetStateInt(this->guiActive, "pop_assignedTo_sel_0", 0);
    v23 = (char *)cvarSystem->GetCVarString(cvarSystem, "viewnotes_categories");
    idStr::operator=((idStr *)names.baseBuffer, v23);
    v24 = operator+(&result, "None;", (const idStr *)names.baseBuffer);
    len = v24->len;
    v26 = v24->len + 1;
    if ( v26 > *(int *)&filter.baseBuffer[8] )
      idStr::ReAllocate((idStr *)filter.baseBuffer, v26, 0);
    qmemcpy(*(void **)&filter.baseBuffer[4], v24->data, len);
    *(_BYTE *)(*(_DWORD *)&filter.baseBuffer[4] + len) = 0;
    *(_DWORD *)filter.baseBuffer = len;
    idStr::FreeData(&result);
    ParseChoicesIntoList(this->guiActive, (idStr *)names.baseBuffer, 1, "pop_category");
    ParseChoicesIntoList(this->guiActive, (idStr *)filter.baseBuffer, 1, "pop_filterCategory");
    this->guiActive->SetStateString(this->guiActive, "filterCategoryText", s1);
    this->guiActive->SetStateInt(this->guiActive, "pop_filterCategory_sel_0", 0);
    if ( !HIBYTE(names.alloced) )
      this->guiActive->SetStateInt(this->guiActive, "pop_category_sel_0", 0);
    idStr::operator=((idStr *)filter.baseBuffer, "None;Not Completed;Completed");
    ParseChoicesIntoList(this->guiActive, (idStr *)filter.baseBuffer, 1, "pop_filterCompleted");
    this->guiActive->SetStateString(this->guiActive, "filterCompletedText", "None");
    this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
    v27 = idStr::Icmp(s1, "QA");
    guiActive = this->guiActive;
    if ( v27 )
    {
      v29 = (idDict *)guiActive->State(guiActive);
      v30 = idDict::FindKey(v29, "pop_category_sel_0");
      if ( v30 )
        v31 = v30->value->data;
      else
        v31 = "0";
      v32 = atoi(v31);
      v33 = va("pop_category_item_%d", v32);
      v34 = (idDict *)this->guiActive->State(this->guiActive);
      idDict::FindKey(v34, v33);
      ((void (__thiscall *)(idUserInterface *, const char *))this->guiActive->SetStateString)(
        this->guiActive,
        "category");
    }
    else
    {
      ((void (__thiscall *)(idUserInterface *, const char *))guiActive->SetStateString)(guiActive, "category");
    }
    this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
    idSessionLocal::ParseNotes(this);
    result.baseBuffer[16] = 0;
    idStr::FreeData(&filter);
    *(_DWORD *)&result.baseBuffer[16] = -1;
    idStr::FreeData(&names);
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::SetGUI(class idUserInterface *,char const * (__cdecl *)(char const *))
void __thiscall idSessionLocal::SetGUI(
        idSessionLocal *this,
        idUserInterface *gui,
        const char *(__cdecl *handle)(const char *))
{
  const char *v4; // eax
  bool v5; // zf
  idUserInterface *guiActive; // eax
  idUserInterface *v7; // ecx
  sysEvent_s ev; // [esp+8h] [ebp-14h] BYREF

  if ( this->guiActive == this->guiMsg )
  {
    if ( gui )
      v4 = gui->Name(gui);
    else
      v4 = aNull_1;
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
      common.type,
      "idSessionLocal::SetGUI %s: guiActive == guiMsg",
      v4);
  }
  v5 = this->guiMsgRestore == 0;
  this->guiActive = gui;
  this->guiHandle = handle;
  if ( !v5 )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 132))(
      common.type,
      "idSessionLocal::SetGUI: cleared an active message box\n");
    this->guiMsgRestore = 0;
  }
  guiActive = this->guiActive;
  if ( guiActive )
  {
    if ( guiActive == this->guiMainMenu )
    {
      idSessionLocal::SetSaveGameGuiVars(this, (int)gui, 0);
      this->SetMainMenuGuiVars(this);
    }
    else if ( guiActive == this->guiRestartMenu )
    {
      idSessionLocal::SetSaveGameGuiVars(this, (int)gui, 0);
    }
    v7 = this->guiActive;
    memset(&ev, 0, sizeof(ev));
    v7->HandleEvent(v7, &ev, com_frameTime, 0);
    this->guiActive->Activate(this->guiActive, 1, com_frameTime);
    this->msgRunning = 0;
  }
}

// FUNC: public: bool __thiscall idSessionLocal::HandleXboxMainMenuCommands(char const *)
char __thiscall idSessionLocal::HandleXboxMainMenuCommands(idSessionLocal *this, const char *menuCommand)
{
  int v2; // edi
  int argc; // eax
  const char *v5; // esi
  idDict *v6; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int v9; // esi
  int v10; // edi
  idUserInterface_vtbl *v11; // ebx
  char *v12; // eax
  idUserInterface_vtbl *v13; // edi
  char *v14; // eax
  idDict *v15; // eax
  const idKeyValue *v16; // eax
  const char *v17; // eax
  int v18; // eax
  const char *v19; // esi
  idDict *v20; // eax
  const idKeyValue *v21; // eax
  const char *v22; // eax
  int granularity; // esi
  bool v24; // cc
  int *v25; // eax
  idStr *v26; // edi
  idStr *v27; // ebx
  const void *v28; // esi
  int num; // edi
  int size; // eax
  int v31; // esi
  idStr *v32; // eax
  char *v33; // esi
  int *v34; // eax
  idStr *v35; // edi
  idStr *v36; // ebx
  char *v37; // esi
  idStr *v38; // edi
  int v39; // esi
  idStr *v40; // ebx
  int v41; // eax
  unsigned int v42; // ecx
  char *v43; // esi
  char *v44; // edi
  char v45; // al
  char *v46; // edi
  char *v47; // esi
  int v48; // ecx
  int v49; // esi
  int v50; // eax
  int v51; // eax
  idStr *v52; // edx
  unsigned int *v53; // ebx
  char *v54; // esi
  char *v55; // edi
  char *v56; // esi
  int v57; // ecx
  const idStr *v58; // eax
  idStr *v59; // esi
  unsigned int v60; // ebx
  int v61; // eax
  char *v62; // esi
  char *v63; // edi
  char *v64; // esi
  int v65; // ecx
  int v66; // eax
  idUserInterface_vtbl *v67; // ebx
  char *Binding; // eax
  int v69; // eax
  idUserInterface_vtbl *v70; // ebx
  char *v71; // eax
  int v72; // eax
  idUserInterface_vtbl *v73; // ebx
  char *v74; // eax
  int v75; // eax
  idUserInterface_vtbl *v76; // ebx
  char *v77; // eax
  int v78; // eax
  idUserInterface_vtbl *v79; // ebx
  char *v80; // eax
  int v81; // eax
  idUserInterface_vtbl *v82; // ebx
  char *v83; // eax
  int v84; // eax
  idUserInterface_vtbl *v85; // ebx
  char *v86; // eax
  int v87; // eax
  idUserInterface_vtbl *v88; // ebx
  char *v89; // eax
  int v90; // eax
  idUserInterface_vtbl *v91; // ebx
  char *v92; // eax
  int v93; // eax
  idUserInterface_vtbl *v94; // ebx
  char *v95; // eax
  const char *v96; // eax
  int v97; // ebx
  bool v98; // sf
  int v99; // eax
  const char *v100; // esi
  unsigned int v101; // eax
  int v102; // edi
  int v103; // eax
  char *v104; // edx
  const char *v105; // ecx
  char v106; // al
  idDict *v108; // eax
  const idKeyValue *v109; // eax
  const char *v110; // eax
  int v111; // eax
  idCmdSystem_vtbl *v112; // esi
  char *v113; // eax
  char *v114; // [esp+62h] [ebp-9C4h]
  bool handled; // [esp+79h] [ebp-9ADh]
  char *ptr; // [esp+7Ah] [ebp-9ACh]
  idStr *ptra; // [esp+7Ah] [ebp-9ACh]
  char *ptrb; // [esp+7Ah] [ebp-9ACh]
  char *ptrc; // [esp+7Ah] [ebp-9ACh]
  int i; // [esp+7Eh] [ebp-9A8h]
  int ia; // [esp+7Eh] [ebp-9A8h]
  int ib; // [esp+7Eh] [ebp-9A8h]
  int ic; // [esp+7Eh] [ebp-9A8h]
  int *v124; // [esp+82h] [ebp-9A4h]
  int v125; // [esp+82h] [ebp-9A4h]
  int icmd; // [esp+86h] [ebp-9A0h]
  int icmda; // [esp+86h] [ebp-9A0h]
  idStr *list; // [esp+8Ah] [ebp-99Ch]
  int v129; // [esp+8Ah] [ebp-99Ch]
  unsigned int v130; // [esp+8Ah] [ebp-99Ch]
  unsigned int len; // [esp+8Eh] [ebp-998h]
  const char *cmd; // [esp+92h] [ebp-994h]
  idStr bind; // [esp+96h] [ebp-990h] BYREF
  idStr mapList; // [esp+B6h] [ebp-970h] BYREF
  idStr v135; // [esp+D6h] [ebp-950h] BYREF
  idStr result; // [esp+F6h] [ebp-930h] BYREF
  idCmdArgs args; // [esp+116h] [ebp-910h] BYREF
  int v138; // [esp+A22h] [ebp-4h]

  v2 = 0;
  args.argc = 0;
  handled = 0;
  idCmdArgs::TokenizeString(&args, menuCommand, 0);
  argc = args.argc;
  if ( args.argc <= 0 )
  {
LABEL_111:
    this->guiActive->SetKeyBindingNames(this->guiActive);
    return handled;
  }
  while ( 1 )
  {
    if ( v2 < 0 || v2 >= argc )
      v5 = &entityFilter;
    else
      v5 = args.argv[v2];
    ++v2;
    cmd = v5;
    icmd = v2;
    if ( !idStr::Icmp(v5, "Init") )
    {
      handled = 1;
      v6 = (idDict *)this->guiActive->State(this->guiActive);
      Key = idDict::FindKey(v6, "MpMapListPopulated");
      if ( Key )
        data = Key->value->data;
      else
        data = "0";
      if ( !atoi(data) )
      {
        idSessionLocal::PopulateMPMapList(
          this,
          (int)this,
          (int)v5,
          "availmaplist",
          this->guiAvailableMapList,
          "mapcyclelist",
          this->guiCycleMapList);
        idSessionLocal::PopulateMPMapList(
          this,
          (int)this,
          (int)v5,
          "syslinkavailmaplist",
          this->guiSysLinkAvailableMapList,
          "syslinkmapcyclelist",
          this->guiSysLinkCycleMapList);
        this->guiActive->SetStateBool(this->guiActive, "MpMapListPopulated", 1);
      }
      cvarSystem->SetCVarBool(cvarSystem, "si_pure", 0, 0);
      rvServerScanGUI::Sort(&this->serverScanGUI, SC_PING);
    }
    if ( !idStr::Icmp(v5, "LANConnect") )
      break;
    if ( idStr::Icmp(v5, "mapDir") )
    {
      if ( !idStr::Icmp(v5, "click_mapload") )
      {
        handled = 1;
        v15 = (idDict *)this->guiActive->State(this->guiActive);
        v16 = idDict::FindKey(v15, "mapList_sel_0");
        if ( v16 )
          v17 = v16->value->data;
        else
          v17 = "-1";
        v18 = atoi(v17);
        if ( v18 != -1 )
        {
          v19 = va("mapList_item_%i", v18);
          v20 = (idDict *)this->guiActive->State(this->guiActive);
          v21 = idDict::FindKey(v20, v19);
          if ( v21 )
            v22 = v21->value->data;
          else
            v22 = &entityFilter;
          idSessionLocal::StartNewGame(this, (int)this, v2, v22, 0, &entityFilter, 1);
        }
        goto LABEL_110;
      }
      if ( !idStr::Icmp(v5, "AddMap") )
      {
        handled = 1;
        idSessionLocal::AddMapFunc(
          this,
          "syslinkavailmaplist",
          this->guiSysLinkAvailableMapList,
          "syslinkmapcyclelist",
          this->guiSysLinkCycleMapList);
      }
      if ( !idStr::Icmp(v5, "RemoveMap") )
      {
        handled = 1;
        idSessionLocal::RemoveMapFunc(
          this,
          "syslinkavailmaplist",
          this->guiSysLinkAvailableMapList,
          "syslinkmapcyclelist",
          this->guiSysLinkCycleMapList);
      }
      if ( !idStr::Icmp(v5, "FilterMPMapList") )
      {
        idSessionLocal::PopulateMPMapList(
          this,
          (int)this,
          (int)v5,
          "availmaplist",
          this->guiAvailableMapList,
          "mapcyclelist",
          this->guiCycleMapList);
        idSessionLocal::PopulateMPMapList(
          this,
          (int)this,
          (int)v5,
          "syslinkavailmaplist",
          this->guiSysLinkAvailableMapList,
          "syslinkmapcyclelist",
          this->guiSysLinkCycleMapList);
        if ( !this->mpCycleMapList.num && this->mpAvailMapList.num > 0 )
        {
          list = this->mpAvailMapList.list;
          if ( !this->mpCycleMapList.list )
          {
            granularity = this->mpCycleMapList.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->mpCycleMapList.size )
              {
                v24 = granularity < this->mpCycleMapList.num;
                this->mpCycleMapList.size = granularity;
                if ( v24 )
                  this->mpCycleMapList.num = granularity;
                v25 = (int *)Memory::Allocate(32 * granularity + 4);
                v138 = 0;
                if ( v25 )
                {
                  v26 = (idStr *)(v25 + 1);
                  *v25 = granularity;
                  `eh vector constructor iterator'(
                    v25 + 1,
                    0x20u,
                    granularity,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v26 = 0;
                }
                v24 = this->mpCycleMapList.num <= 0;
                v138 = -1;
                this->mpCycleMapList.list = v26;
                ptr = 0;
                if ( !v24 )
                {
                  v124 = 0;
                  do
                  {
                    v27 = (idStr *)((char *)v124 + (unsigned int)this->mpCycleMapList.list);
                    i = *v124;
                    if ( *v124 + 1 > v27->alloced )
                      idStr::ReAllocate(v27, i + 1, 0);
                    v28 = (const void *)v124[1];
                    v124 += 8;
                    qmemcpy(v27->data, v28, i);
                    v27->data[i] = 0;
                    v27->len = i;
                    ++ptr;
                  }
                  while ( (int)ptr < this->mpCycleMapList.num );
                }
              }
            }
            else
            {
              this->mpCycleMapList.list = 0;
              this->mpCycleMapList.num = 0;
              this->mpCycleMapList.size = 0;
            }
          }
          num = this->mpCycleMapList.num;
          size = this->mpCycleMapList.size;
          if ( num == size )
          {
            if ( !this->mpCycleMapList.granularity )
              this->mpCycleMapList.granularity = 16;
            v31 = size
                + this->mpCycleMapList.granularity
                - (size + this->mpCycleMapList.granularity) % this->mpCycleMapList.granularity;
            if ( v31 > 0 )
            {
              if ( v31 != this->mpCycleMapList.size )
              {
                ptra = this->mpCycleMapList.list;
                this->mpCycleMapList.size = v31;
                if ( v31 < num )
                  this->mpCycleMapList.num = v31;
                v34 = (int *)Memory::Allocate(32 * v31 + 4);
                v138 = 1;
                if ( v34 )
                {
                  v35 = (idStr *)(v34 + 1);
                  *v34 = v31;
                  `eh vector constructor iterator'(
                    v34 + 1,
                    0x20u,
                    v31,
                    (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                }
                else
                {
                  v35 = 0;
                }
                v24 = this->mpCycleMapList.num <= 0;
                v138 = -1;
                this->mpCycleMapList.list = v35;
                ia = 0;
                if ( !v24 )
                {
                  v125 = 0;
                  do
                  {
                    v36 = &this->mpCycleMapList.list[v125];
                    len = ptra[v125].len;
                    if ( (signed int)(len + 1) > v36->alloced )
                      idStr::ReAllocate(v36, len + 1, 0);
                    v37 = ptra[v125++].data;
                    qmemcpy(v36->data, v37, len);
                    v36->data[len] = 0;
                    v36->len = len;
                    ++ia;
                  }
                  while ( ia < this->mpCycleMapList.num );
                }
                if ( ptra )
                {
                  `eh vector destructor iterator'(
                    ptra,
                    0x20u,
                    *(_DWORD *)&ptra[-1].baseBuffer[16],
                    (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                  Memory::Free(&ptra[-1].baseBuffer[16]);
                }
              }
            }
            else
            {
              v32 = this->mpCycleMapList.list;
              if ( v32 )
              {
                v33 = &v32[-1].baseBuffer[16];
                `eh vector destructor iterator'(
                  v32,
                  0x20u,
                  *(_DWORD *)&v32[-1].baseBuffer[16],
                  (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                Memory::Free(v33);
              }
              this->mpCycleMapList.list = 0;
              this->mpCycleMapList.num = 0;
              this->mpCycleMapList.size = 0;
            }
          }
          v38 = list;
          v39 = list->len;
          v40 = &this->mpCycleMapList.list[this->mpCycleMapList.num];
          v41 = list->len + 1;
          v129 = list->len;
          if ( v41 > v40->alloced )
            idStr::ReAllocate(v40, v41, 0);
          v42 = v39;
          v43 = v38->data;
          v44 = v40->data;
          v45 = v42;
          v42 >>= 2;
          qmemcpy(v44, v43, 4 * v42);
          v47 = &v43[4 * v42];
          v46 = &v44[4 * v42];
          v48 = v45 & 3;
          qmemcpy(v46, v47, v48);
          v49 = (int)&v47[v48];
          v40->data[v129] = 0;
          v40->len = v129;
          ++this->mpCycleMapList.num;
          v50 = this->mpAvailMapList.num;
          if ( v50 > 0 )
          {
            v51 = v50 - 1;
            this->mpAvailMapList.num = v51;
            ib = 0;
            if ( v51 > 0 )
            {
              ptrb = 0;
              do
              {
                v52 = this->mpAvailMapList.list;
                v53 = (unsigned int *)((char *)v52 + (_DWORD)ptrb);
                v130 = *(int *)((char *)&v52[1].len + (_DWORD)ptrb);
                if ( (signed int)(v130 + 1) > *(int *)((char *)&v52->alloced + (_DWORD)ptrb) )
                  idStr::ReAllocate((idStr *)((char *)v52 + (_DWORD)ptrb), v130 + 1, 0);
                v54 = (char *)v53[9];
                v55 = (char *)v53[1];
                ptrb += 32;
                qmemcpy(v55, v54, 4 * (v130 >> 2));
                v56 = &v54[4 * (v130 >> 2)];
                v57 = v130 & 3;
                qmemcpy(&v55[4 * (v130 >> 2)], v56, v57);
                v49 = (int)&v56[v57];
                *(_BYTE *)(v130 + v53[1]) = 0;
                *v53 = v130;
                ++ib;
              }
              while ( ib < this->mpAvailMapList.num );
            }
          }
          mapList.len = 0;
          mapList.alloced = 20;
          mapList.data = mapList.baseBuffer;
          mapList.baseBuffer[0] = 0;
          v24 = this->mpCycleMapList.num <= 0;
          v138 = 2;
          ic = 0;
          if ( !v24 )
          {
            ptrc = 0;
            do
            {
              v58 = operator+(&result, &mapList, (const idStr *)&ptrc[(unsigned int)this->mpCycleMapList.list]);
              LOBYTE(v138) = 3;
              v59 = operator+(&v135, v58, ";");
              v60 = v59->len;
              v61 = v59->len + 1;
              LOBYTE(v138) = 4;
              if ( v61 > mapList.alloced )
                idStr::ReAllocate(&mapList, v61, 0);
              v62 = v59->data;
              v63 = mapList.data;
              qmemcpy(mapList.data, v62, 4 * (v60 >> 2));
              v64 = &v62[4 * (v60 >> 2)];
              v65 = v60 & 3;
              qmemcpy(&v63[4 * (v60 >> 2)], v64, v65);
              v49 = (int)&v64[v65];
              mapList.data[v60] = 0;
              mapList.len = v60;
              LOBYTE(v138) = 3;
              idStr::FreeData(&v135);
              LOBYTE(v138) = 2;
              idStr::FreeData(&result);
              ptrc += 32;
              ++ic;
            }
            while ( ic < this->mpCycleMapList.num );
          }
          cvarSystem->SetCVarString(cvarSystem, "si_mapList", mapList.data, 0);
          idSessionLocal::PopulateMPMapList(
            this,
            (int)this,
            v49,
            "availmaplist",
            this->guiAvailableMapList,
            "mapcyclelist",
            this->guiCycleMapList);
          idSessionLocal::PopulateMPMapList(
            this,
            (int)this,
            v49,
            "syslinkavailmaplist",
            this->guiSysLinkAvailableMapList,
            "syslinkmapcyclelist",
            this->guiSysLinkCycleMapList);
          this->guiActive->SetStateInt(this->guiActive, "noMaps", 1);
          v138 = -1;
          idStr::FreeData(&mapList);
          v5 = cmd;
          v2 = icmd;
        }
      }
      if ( !idStr::Icmp(v5, "AddMapLive") )
        idSessionLocal::AddMapFunc(
          this,
          "availmaplist",
          this->guiAvailableMapList,
          "mapcyclelist",
          this->guiCycleMapList);
      if ( !idStr::Icmp(v5, "RemoveMapLive") )
        idSessionLocal::RemoveMapFunc(
          this,
          "availmaplist",
          this->guiAvailableMapList,
          "mapcyclelist",
          this->guiCycleMapList);
      if ( !idStr::Icmp(v5, "refreshKeyBindings") )
      {
        handled = 1;
        this->guiActive->SetKeyBindingNames(this->guiActive);
        v66 = idKeyInput::StringToKeyNum("JOY1");
        v67 = this->guiActive->__vftable;
        Binding = idKeyInput::GetBinding(v66);
        v67->SetStateString(this->guiActive, "leftShoulder", Binding);
        v69 = idKeyInput::StringToKeyNum("JOY2");
        v70 = this->guiActive->__vftable;
        v71 = idKeyInput::GetBinding(v69);
        v70->SetStateString(this->guiActive, "rightShoulder", v71);
        v72 = idKeyInput::StringToKeyNum("JOY3");
        v73 = this->guiActive->__vftable;
        v74 = idKeyInput::GetBinding(v72);
        v73->SetStateString(this->guiActive, "aButton", v74);
        v75 = idKeyInput::StringToKeyNum("JOY4");
        v76 = this->guiActive->__vftable;
        v77 = idKeyInput::GetBinding(v75);
        v76->SetStateString(this->guiActive, "bButton", v77);
        v78 = idKeyInput::StringToKeyNum("JOY5");
        v79 = this->guiActive->__vftable;
        v80 = idKeyInput::GetBinding(v78);
        v79->SetStateString(this->guiActive, "yButton", v80);
        v81 = idKeyInput::StringToKeyNum("JOY6");
        v82 = this->guiActive->__vftable;
        v83 = idKeyInput::GetBinding(v81);
        v82->SetStateString(this->guiActive, "xButton", v83);
        v84 = idKeyInput::StringToKeyNum("JOY13");
        v85 = this->guiActive->__vftable;
        v86 = idKeyInput::GetBinding(v84);
        v85->SetStateString(this->guiActive, "leftAxis", v86);
        v87 = idKeyInput::StringToKeyNum("JOY14");
        v88 = this->guiActive->__vftable;
        v89 = idKeyInput::GetBinding(v87);
        v88->SetStateString(this->guiActive, "rightAxis", v89);
        v90 = idKeyInput::StringToKeyNum("JOY16");
        v91 = this->guiActive->__vftable;
        v92 = idKeyInput::GetBinding(v90);
        v91->SetStateString(this->guiActive, "leftTrigger", v92);
        v93 = idKeyInput::StringToKeyNum("JOY15");
        v94 = this->guiActive->__vftable;
        v95 = idKeyInput::GetBinding(v93);
        v94->SetStateString(this->guiActive, "rightTrigger", v95);
      }
      if ( idStr::Icmp(v5, "bind") )
        goto LABEL_110;
      handled = 1;
      if ( args.argc - v2 < 2 )
        goto LABEL_110;
      if ( v2 < 0 || v2 >= args.argc )
        v96 = &entityFilter;
      else
        v96 = args.argv[v2];
      v97 = atoi(v96);
      v98 = icmd + 1 < 0;
      v99 = icmd + 1;
      icmda = icmd + 1;
      if ( v98 || v99 >= args.argc )
        v100 = &entityFilter;
      else
        v100 = args.argv[v99];
      bind.len = 0;
      bind.alloced = 20;
      bind.data = bind.baseBuffer;
      bind.baseBuffer[0] = 0;
      if ( v100 )
      {
        v101 = (unsigned int)&v100[strlen(v100) + 1];
        v102 = v101 - (_DWORD)(v100 + 1);
        v103 = v101 - (_DWORD)v100;
        if ( v103 > 20 )
          idStr::ReAllocate(&bind, v103, 1);
        v104 = bind.data;
        v105 = v100;
        do
        {
          v106 = *v105;
          *v104++ = *v105++;
        }
        while ( v106 );
        bind.len = v102;
      }
      icmd = icmda + 1;
      v138 = 5;
      if ( idKeyInput::NumBinds(bind.data) >= 1 && !idKeyInput::KeyIsBoundTo(v97, bind.data) )
        idKeyInput::UnbindBinding(bind.data);
      idKeyInput::SetBinding(v97, bind.data);
      v138 = -1;
      idStr::FreeData(&bind);
    }
    else
    {
      v9 = 0;
      handled = 1;
      if ( this->masterMapList.num > 0 )
      {
        v10 = 0;
        do
        {
          v11 = this->guiActive->__vftable;
          v114 = this->masterMapList.list[v10].data;
          v12 = va("mapList_item_%i", v9);
          v11->SetStateString(this->guiActive, v12, v114);
          ++v9;
          ++v10;
        }
        while ( v9 < this->masterMapList.num );
      }
      v13 = this->guiActive->__vftable;
      v14 = va("mapList_item_%i", v9);
      v13->DeleteState(this->guiActive, v14);
      this->guiActive->SetStateInt(this->guiActive, "mapList_sel_0", 0);
      this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
    }
    v2 = icmd;
LABEL_110:
    argc = args.argc;
    if ( v2 >= args.argc )
      goto LABEL_111;
  }
  v108 = (idDict *)this->guiActive->State(this->guiActive);
  v109 = idDict::FindKey(v108, "serverlist_sel_0");
  if ( v109 )
    v110 = v109->value->data;
  else
    v110 = "0";
  v111 = atoi(v110);
  if ( v111 != -1 )
  {
    v112 = cmdSystem->__vftable;
    v113 = va("Connect %d\n", v111);
    v112->BufferCommandText(cmdSystem, CMD_EXEC_NOW, v113);
  }
  return 1;
}

// FUNC: public: void __thiscall idSessionLocal::HandleNoteCommands(char const *)
void __userpurge idSessionLocal::HandleNoteCommands(
        idSessionLocal *this@<ecx>,
        int a2@<ebp>,
        int a3@<edi>,
        const char *menuCommand)
{
  idDict *v5; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int v8; // edi
  idDict *v9; // eax
  const idKeyValue *v10; // eax
  const char *v11; // eax
  const char *v12; // ebp
  idDict *v13; // eax
  const idKeyValue *v14; // eax
  const char *v15; // ebx
  char *baseBuffer; // edx
  const char *v17; // ecx
  char v18; // al
  int v20; // ebp
  const char *v21; // ebx
  idDict *v22; // eax
  const idKeyValue *v23; // eax
  const char *v24; // eax
  idUserInterface_vtbl *v25; // ebx
  char *v26; // eax
  const char *v27; // ebx
  idDict *v28; // eax
  const idKeyValue *v29; // eax
  const char *v30; // eax
  idUserInterface_vtbl *v31; // ebx
  char *v32; // eax
  idUserInterface_vtbl *v33; // ebx
  char *v34; // eax
  idUserInterface_vtbl *v35; // ebx
  char *v36; // eax
  idStr *p_fileName; // ecx
  idDict *v38; // eax
  const idKeyValue *v39; // eax
  const char *v40; // eax
  int v41; // edi
  idDict *v42; // eax
  const idKeyValue *v43; // eax
  const char *v44; // eax
  idDict *v45; // eax
  const idKeyValue *v46; // eax
  const char *v47; // eax
  int v48; // eax
  idDict *v49; // eax
  const idKeyValue *v50; // eax
  const char *v51; // eax
  int v52; // ebp
  const char *v53; // edi
  idDict *v54; // eax
  const idKeyValue *v55; // eax
  char *v56; // eax
  idDict *v57; // eax
  idUserInterface_vtbl *v58; // edi
  char *v59; // eax
  idDict *v60; // eax
  const idKeyValue *v61; // eax
  const char *v62; // eax
  int v63; // eax
  const char *v64; // edi
  idDict *v65; // eax
  idDict *v66; // eax
  const idKeyValue *v67; // eax
  const char *v68; // eax
  int v69; // eax
  const char *v70; // edi
  idDict *v71; // eax
  idDict *v72; // eax
  const idKeyValue *v73; // eax
  const char *v74; // eax
  int v75; // eax
  const char *v76; // edi
  idDict *v77; // eax
  idDict *v78; // eax
  const idKeyValue *v79; // eax
  const char *v80; // eax
  int v81; // eax
  const char *v82; // edi
  idDict *v83; // eax
  const idKeyValue *v84; // eax
  const char *v85; // eax
  idDict *v86; // eax
  const idKeyValue *v87; // eax
  const char *v88; // eax
  int v89; // eax
  const char *v90; // edi
  idDict *v91; // eax
  const idKeyValue *v92; // eax
  idDict *v93; // eax
  const idKeyValue *v94; // eax
  const char *v95; // eax
  int v96; // eax
  idUserInterface *guiActive; // ecx
  idDict *v98; // eax
  const idKeyValue *v99; // eax
  const char *v100; // eax
  int v101; // eax
  const char *v102; // edi
  idDict *v103; // eax
  const idKeyValue *v104; // eax
  const char *v105; // eax
  int len; // edi
  char *v107; // ecx
  char *v108; // edx
  char v109; // al
  bool v110; // bl
  int v111; // edi
  int v112; // eax
  char v113; // cl
  char *v114; // edx
  idUserInterface_vtbl *v115; // edi
  const char *v116; // eax
  const char *v117; // eax
  idDict *v118; // eax
  const idKeyValue *v119; // eax
  const char *v120; // eax
  int v121; // ebx
  int v122; // ebp
  const char *v123; // edi
  idDict *v124; // eax
  const idKeyValue *v125; // eax
  const char *v126; // eax
  idDict *v127; // eax
  const idKeyValue *v128; // eax
  const char *v129; // eax
  int v130; // ebx
  int v131; // ebp
  const char *v132; // edi
  idDict *v133; // eax
  const idKeyValue *v134; // eax
  const char *v135; // eax
  const char *v136; // [esp+6Ch] [ebp-15Ch]
  const char *v139; // [esp+74h] [ebp-154h]
  const char *v140; // [esp+74h] [ebp-154h]
  char *v141; // [esp+78h] [ebp-150h]
  char *v142; // [esp+7Ch] [ebp-14Ch]
  bool completed; // [esp+83h] [ebp-145h] BYREF
  int v144; // [esp+84h] [ebp-144h]
  int numSel; // [esp+88h] [ebp-140h]
  idStr textCategory; // [esp+8Ch] [ebp-13Ch] BYREF
  idStr fileName; // [esp+ACh] [ebp-11Ch] BYREF
  idStr category; // [esp+CCh] [ebp-FCh] BYREF
  idStr assignedTo; // [esp+ECh] [ebp-DCh] BYREF
  idStr comments; // [esp+10Ch] [ebp-BCh] BYREF
  idStr version; // [esp+12Ch] [ebp-9Ch] BYREF
  idStr date; // [esp+14Ch] [ebp-7Ch] BYREF
  idStr user; // [esp+16Ch] [ebp-5Ch] BYREF
  idVec3 origin; // [esp+18Ch] [ebp-3Ch] BYREF
  idMat3 axis; // [esp+198h] [ebp-30h] BYREF
  int v156; // [esp+1C4h] [ebp-4h]

  if ( !this->mapSpawned )
  {
    this->guiActive = 0;
    return;
  }
  if ( !idStr::Icmp(menuCommand, "reset") )
  {
    idSessionLocal::InitNotes(this, 0, (int)menuCommand, (int)this, 1, "None", a3, (int)v141, v142);
    return;
  }
  if ( !idStr::Icmp(menuCommand, "init") )
  {
    idSessionLocal::InitNotes(this, 0, (int)menuCommand, (int)this, 0, "None", a3, (int)v141, v142);
    return;
  }
  if ( !idStr::Icmp(menuCommand, "init2") )
  {
    idSessionLocal::InitNotes(this, 0, (int)menuCommand, (int)this, 0, "Build Notes", a3, (int)v141, v142);
    return;
  }
  if ( !idStr::Icmp(menuCommand, "initQA") )
  {
    idSessionLocal::InitNotes(this, 0, (int)menuCommand, (int)this, 0, "QA", a3, (int)v141, v142);
    return;
  }
  if ( !idStr::Icmp(menuCommand, "close") )
  {
    this->guiActive = 0;
    idKeyInput::ClearStates();
    return;
  }
  if ( !idStr::Icmp(menuCommand, "remove") )
  {
    if ( !*this->MessageBoxA(
             this,
             3,
             "Are you sure you want to delete this view note?",
             "Delete View Note",
             1,
             "yes",
             0,
             0) )
      return;
    v5 = (idDict *)this->guiActive->State(this->guiActive);
    Key = idDict::FindKey(v5, "notes_sel_0");
    if ( Key )
      data = Key->value->data;
    else
      data = "-1";
    v8 = atoi(data);
    v9 = (idDict *)this->guiActive->State(this->guiActive);
    v10 = idDict::FindKey(v9, "notes_num");
    if ( v10 )
      v11 = v10->value->data;
    else
      v11 = "-1";
    numSel = atoi(v11);
    v12 = va("notes_file_%i", v8);
    v13 = (idDict *)this->guiActive->State(this->guiActive);
    v14 = idDict::FindKey(v13, v12);
    if ( v14 )
      v15 = v14->value->data;
    else
      v15 = &entityFilter;
    baseBuffer = fileName.baseBuffer;
    fileName.len = 0;
    fileName.alloced = 20;
    fileName.data = fileName.baseBuffer;
    fileName.baseBuffer[0] = 0;
    if ( v15 )
    {
      v144 = strlen(v15);
      if ( v144 + 1 > 20 )
      {
        idStr::ReAllocate(&fileName, v144 + 1, 1);
        baseBuffer = fileName.data;
      }
      v17 = v15;
      do
      {
        v18 = *v17;
        *baseBuffer++ = *v17++;
      }
      while ( v18 );
      fileName.len = v144;
      baseBuffer = fileName.data;
    }
    v156 = 0;
    if ( baseBuffer )
    {
      ((void (__thiscall *)(idFileSystem *, char *, const char *, int, int))fileSystem->RemoveFile)(
        fileSystem,
        baseBuffer,
        "fs_cdpath",
        a2,
        a3);
      idStr::SetFileExtension((idStr *)&fileName.alloced, ".jpg");
      fileSystem->RemoveFile(fileSystem, *(const char **)fileName.baseBuffer, "fs_cdpath");
      if ( v8 < (int)--textCategory.data )
      {
        do
        {
          v20 = v8 + 1;
          v21 = va("notes_item_%i", v8 + 1);
          v22 = (idDict *)this->guiActive->State(this->guiActive);
          v23 = idDict::FindKey(v22, v21);
          if ( v23 )
            v24 = v23->value->data;
          else
            v24 = &entityFilter;
          v25 = this->guiActive->__vftable;
          v139 = v24;
          v26 = va("notes_item_%i", v8);
          v25->SetStateString(this->guiActive, v26, v139);
          v27 = va("notes_file_%i", v8 + 1);
          v28 = (idDict *)this->guiActive->State(this->guiActive);
          v29 = idDict::FindKey(v28, v27);
          if ( v29 )
            v30 = v29->value->data;
          else
            v30 = &entityFilter;
          v31 = this->guiActive->__vftable;
          v140 = v30;
          v32 = va("notes_file_%i", v8);
          v31->SetStateString(this->guiActive, v32, v140);
          ++v8;
        }
        while ( v20 < (int)textCategory.data );
      }
      v33 = this->guiActive->__vftable;
      v34 = va("notes_item_%i", v8);
      v33->DeleteState(this->guiActive, v34);
      v35 = this->guiActive->__vftable;
      v36 = va("notes_file_%i", v8);
      v35->DeleteState(this->guiActive, v36);
      this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
      idSessionLocal::HandleNoteCommands(this, "notes");
    }
    p_fileName = &fileName;
LABEL_163:
    v156 = -1;
    idStr::FreeData(p_fileName);
    return;
  }
  if ( idStr::Icmp(menuCommand, "next") )
  {
    if ( idStr::Icmp(menuCommand, "previous") )
    {
      if ( !idStr::Icmp(menuCommand, "add") )
      {
        idSessionLocal::SaveNote(this, 0, (int)this, 0);
        idSessionLocal::InitNotes(this, 0, (int)menuCommand, (int)this, 1, "None", a2, a3, v141);
        this->guiActive = 0;
        idKeyInput::ClearStates();
        return;
      }
      if ( !idStr::Icmp(menuCommand, "update") )
      {
        v49 = (idDict *)this->guiActive->State(this->guiActive);
        v50 = idDict::FindKey(v49, "notes_sel_0");
        if ( v50 )
          v51 = v50->value->data;
        else
          v51 = "-1";
        v52 = atoi(v51);
        if ( v52 >= 0
          && *this->MessageBoxA(
                this,
                3,
                "Are you sure you want to update this view note?",
                "Update View Note",
                1,
                "yes",
                0,
                0) )
        {
          v53 = va("notes_file_%i", v52);
          v54 = (idDict *)((int (__thiscall *)(idUserInterface *, int, int))this->guiActive->State)(
                            this->guiActive,
                            a2,
                            a3);
          v55 = idDict::FindKey(v54, v53);
          if ( v55 )
            v56 = v55->value->data;
          else
            v56 = (char *)&entityFilter;
          idSessionLocal::SaveNote(this, 0, (int)this, v56);
          v57 = (idDict *)this->guiActive->State(this->guiActive);
          idDict::FindKey(v57, "note");
          v58 = this->guiActive->__vftable;
          v59 = va("notes_item_%i", v52);
          ((void (__thiscall *)(idUserInterface *, char *))v58->SetStateString)(this->guiActive, v59);
          this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
        }
        return;
      }
      if ( !idStr::Icmp(menuCommand, "export") )
      {
        idSessionLocal::ExportNotes(this);
        return;
      }
      if ( idStr::Icmp(menuCommand, "update_filterCategory") )
      {
        if ( idStr::Icmp(menuCommand, "update_filterCompleted") )
        {
          if ( idStr::Icmp(menuCommand, "update_filterAssigned") )
          {
            if ( idStr::Icmp(menuCommand, "update_assignedTo") )
            {
              if ( idStr::Icmp(menuCommand, "update_category") )
              {
                if ( idStr::Icmp(menuCommand, "completed") )
                {
                  if ( idStr::Icmp(menuCommand, "notes") )
                    return;
                  v98 = (idDict *)this->guiActive->State(this->guiActive);
                  v99 = idDict::FindKey(v98, "notes_sel_0");
                  if ( v99 )
                    v100 = v99->value->data;
                  else
                    v100 = "-1";
                  v101 = atoi(v100);
                  v102 = va("notes_file_%i", v101);
                  v103 = (idDict *)this->guiActive->State(this->guiActive);
                  v104 = idDict::FindKey(v103, v102);
                  if ( v104 )
                  {
                    v105 = v104->value->data;
                    if ( !v105 )
                      return;
                  }
                  else
                  {
                    v105 = &entityFilter;
                  }
                  user.len = 0;
                  user.alloced = 20;
                  user.data = user.baseBuffer;
                  user.baseBuffer[0] = 0;
                  v156 = 6;
                  date.len = 0;
                  date.alloced = 20;
                  date.data = date.baseBuffer;
                  date.baseBuffer[0] = 0;
                  version.len = 0;
                  version.alloced = 20;
                  version.data = version.baseBuffer;
                  version.baseBuffer[0] = 0;
                  category.len = 0;
                  category.alloced = 20;
                  category.data = category.baseBuffer;
                  category.baseBuffer[0] = 0;
                  assignedTo.len = 0;
                  assignedTo.alloced = 20;
                  assignedTo.data = assignedTo.baseBuffer;
                  assignedTo.baseBuffer[0] = 0;
                  comments.len = 0;
                  comments.alloced = 20;
                  comments.data = comments.baseBuffer;
                  comments.baseBuffer[0] = 0;
                  if ( idSessionLocal::ReadNoteFile(
                         this,
                         v105,
                         &origin,
                         &axis,
                         &user,
                         &date,
                         &version,
                         &category,
                         &assignedTo,
                         &completed,
                         &comments) )
                  {
                    len = category.len;
                    textCategory.len = 0;
                    textCategory.alloced = 20;
                    textCategory.data = textCategory.baseBuffer;
                    textCategory.baseBuffer[0] = 0;
                    if ( category.len + 1 > 20 )
                      idStr::ReAllocate(&textCategory, category.len + 1, 1);
                    v107 = category.data;
                    v108 = textCategory.data;
                    do
                    {
                      v109 = *v107;
                      *v108++ = *v107++;
                    }
                    while ( v109 );
                    textCategory.len = len;
                    v110 = completed;
                    LOBYTE(v156) = 7;
                    if ( completed )
                    {
                      v111 = len + 11;
                      if ( v111 + 1 > textCategory.alloced )
                        idStr::ReAllocate(&textCategory, v111 + 1, 1);
                      v112 = 0;
                      v113 = 44;
                      do
                      {
                        v114 = &textCategory.data[v112++];
                        v114[textCategory.len] = v113;
                        v113 = aCompleted_0[v112];
                      }
                      while ( v113 );
                      textCategory.len = v111;
                      textCategory.data[v111] = 0;
                    }
                    ((void (__thiscall *)(idUserInterface *, const char *, char *, int, int))this->guiActive->SetStateString)(
                      this->guiActive,
                      "submitter",
                      user.data,
                      a2,
                      a3);
                    this->guiActive->SetStateString(this->guiActive, aDate_0, *(const char **)date.baseBuffer);
                    this->guiActive->SetStateString(this->guiActive, "version", *(const char **)version.baseBuffer);
                    this->guiActive->SetStateString(
                      this->guiActive,
                      "categoryText",
                      *(const char **)textCategory.baseBuffer);
                    this->guiActive->SetStateString(
                      this->guiActive,
                      "assignedToText",
                      *(const char **)assignedTo.baseBuffer);
                    v115 = this->guiActive->__vftable;
                    v116 = idVec3::ToString((idVec3 *)&origin.z, 2);
                    v115->SetStateString(this->guiActive, "location", v116);
                    this->guiActive->SetStateString(this->guiActive, "description", *(const char **)comments.baseBuffer);
                    game->SetPlayerInfo(game, (idVec3 *)&origin.z, (idMat3 *)&axis.mat[0].z, -1);
                    this->guiActive->SetStateString(this->guiActive, "category", *(const char **)category.baseBuffer);
                    this->guiActive->SetStateString(
                      this->guiActive,
                      "assignedTo",
                      *(const char **)assignedTo.baseBuffer);
                    this->guiActive->SetStateString(this->guiActive, "note", *(const char **)comments.baseBuffer);
                    v117 = "X";
                    if ( !v110 )
                      v117 = &entityFilter;
                    this->guiActive->SetStateString(this->guiActive, "completed", v117);
                    this->guiActive->SetStateInt(this->guiActive, "pop_assignedTo_sel_0", 0);
                    v118 = (idDict *)this->guiActive->State(this->guiActive);
                    v119 = idDict::FindKey(v118, "pop_assignedTo_num");
                    if ( v119 )
                      v120 = v119->value->data;
                    else
                      v120 = "-1";
                    v121 = atoi(v120);
                    v122 = 0;
                    if ( v121 > 0 )
                    {
                      while ( 1 )
                      {
                        v123 = va("pop_assignedTo_item_%i", v122);
                        v124 = (idDict *)this->guiActive->State(this->guiActive);
                        v125 = idDict::FindKey(v124, v123);
                        v126 = v125 ? v125->value->data : &entityFilter;
                        if ( !idStr::Cmp(v126, *(const char **)assignedTo.baseBuffer) )
                          break;
                        if ( ++v122 >= v121 )
                          goto LABEL_150;
                      }
                      this->guiActive->SetStateInt(this->guiActive, "pop_assignedTo_sel_0", v122);
                    }
LABEL_150:
                    this->guiActive->SetStateInt(this->guiActive, "pop_category_sel_0", 0);
                    v127 = (idDict *)this->guiActive->State(this->guiActive);
                    v128 = idDict::FindKey(v127, "pop_category_num");
                    if ( v128 )
                      v129 = v128->value->data;
                    else
                      v129 = "-1";
                    v130 = atoi(v129);
                    v131 = 0;
                    if ( v130 > 0 )
                    {
                      while ( 1 )
                      {
                        v132 = va("pop_category_item_%i", v131);
                        v133 = (idDict *)this->guiActive->State(this->guiActive);
                        v134 = idDict::FindKey(v133, v132);
                        v135 = v134 ? v134->value->data : &entityFilter;
                        if ( !idStr::Cmp(v135, *(const char **)category.baseBuffer) )
                          break;
                        if ( ++v131 >= v130 )
                          goto LABEL_161;
                      }
                      this->guiActive->SetStateInt(this->guiActive, "pop_category_sel_0", v131);
                    }
LABEL_161:
                    this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
                    LOBYTE(v156) = 6;
                    idStr::FreeData(&textCategory);
                  }
                  LOBYTE(v156) = 5;
                  idStr::FreeData(&comments);
                  LOBYTE(v156) = 4;
                  idStr::FreeData(&assignedTo);
                  LOBYTE(v156) = 3;
                  idStr::FreeData(&category);
                  LOBYTE(v156) = 2;
                  idStr::FreeData(&version);
                  LOBYTE(v156) = 1;
                  idStr::FreeData(&date);
                  p_fileName = &user;
                  goto LABEL_163;
                }
                v93 = (idDict *)((int (__thiscall *)(idUserInterface *, int, int))this->guiActive->State)(
                                  this->guiActive,
                                  a2,
                                  a3);
                v94 = idDict::FindKey(v93, "completed");
                if ( v94 )
                  v95 = v94->value->data;
                else
                  v95 = &entityFilter;
                v96 = idStr::Cmp(v95, &entityFilter);
                guiActive = this->guiActive;
                if ( v96 )
                  guiActive->SetStateString(guiActive, "completed", &entityFilter);
                else
                  guiActive->SetStateString(guiActive, "completed", "X");
                this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
                return;
              }
              v86 = (idDict *)this->guiActive->State(this->guiActive);
              v87 = idDict::FindKey(v86, "pop_category_sel_0");
              if ( v87 )
                v88 = v87->value->data;
              else
                v88 = "-1";
              v89 = atoi(v88);
              if ( v89 < 0 )
                return;
              v90 = va("pop_category_item_%i", v89);
              v91 = (idDict *)this->guiActive->State(this->guiActive);
              v92 = idDict::FindKey(v91, v90);
              if ( v92 )
                v136 = v92->value->data;
              else
                v136 = &entityFilter;
              this->guiActive->SetStateString(this->guiActive, "category", v136);
            }
            else
            {
              v78 = (idDict *)this->guiActive->State(this->guiActive);
              v79 = idDict::FindKey(v78, "pop_assignedTo_sel_0");
              if ( v79 )
                v80 = v79->value->data;
              else
                v80 = "-1";
              v81 = atoi(v80);
              if ( v81 <= 0 )
              {
                if ( v81 )
                  return;
                this->guiActive->SetStateString(this->guiActive, "assignedTo", &entityFilter);
              }
              else
              {
                v82 = va("pop_assignedTo_item_%i", v81);
                v83 = (idDict *)this->guiActive->State(this->guiActive);
                v84 = idDict::FindKey(v83, v82);
                if ( v84 )
                  v85 = v84->value->data;
                else
                  v85 = &entityFilter;
                this->guiActive->SetStateString(this->guiActive, "assignedTo", v85);
              }
            }
            this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
            return;
          }
          v72 = (idDict *)this->guiActive->State(this->guiActive);
          v73 = idDict::FindKey(v72, "pop_filterAssignedTo_sel_0");
          if ( v73 )
            v74 = v73->value->data;
          else
            v74 = "-1";
          v75 = atoi(v74);
          if ( v75 < 0 )
            return;
          v76 = va("pop_filterAssignedTo_item_%i", v75);
          v77 = (idDict *)((int (__thiscall *)(idUserInterface *, int, int))this->guiActive->State)(
                            this->guiActive,
                            a2,
                            a3);
          idDict::FindKey(v77, v76);
        }
        else
        {
          v66 = (idDict *)this->guiActive->State(this->guiActive);
          v67 = idDict::FindKey(v66, "pop_filterCompleted_sel_0");
          if ( v67 )
            v68 = v67->value->data;
          else
            v68 = "-1";
          v69 = atoi(v68);
          if ( v69 < 0 )
            return;
          v70 = va("pop_filterCompleted_item_%i", v69);
          v71 = (idDict *)((int (__thiscall *)(idUserInterface *, int, int))this->guiActive->State)(
                            this->guiActive,
                            a2,
                            a3);
          idDict::FindKey(v71, v70);
        }
      }
      else
      {
        v60 = (idDict *)this->guiActive->State(this->guiActive);
        v61 = idDict::FindKey(v60, "pop_filterCategory_sel_0");
        if ( v61 )
          v62 = v61->value->data;
        else
          v62 = "-1";
        v63 = atoi(v62);
        if ( v63 < 0 )
          return;
        v64 = va("pop_filterCategory_item_%i", v63);
        v65 = (idDict *)((int (__thiscall *)(idUserInterface *, int, int))this->guiActive->State)(
                          this->guiActive,
                          a2,
                          a3);
        idDict::FindKey(v65, v64);
      }
      ((void (__thiscall *)(idUserInterface *))this->guiActive->SetStateString)(this->guiActive);
      this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
      idSessionLocal::ParseNotes(this);
      return;
    }
    v45 = (idDict *)this->guiActive->State(this->guiActive);
    v46 = idDict::FindKey(v45, "notes_sel_0");
    if ( v46 )
      v47 = v46->value->data;
    else
      v47 = "-1";
    v48 = atoi(v47) - 1;
    if ( v48 >= 0 )
    {
      this->guiActive->SetStateInt(this->guiActive, "notes_sel_0", v48);
      goto LABEL_50;
    }
  }
  else
  {
    v38 = (idDict *)this->guiActive->State(this->guiActive);
    v39 = idDict::FindKey(v38, "notes_sel_0");
    if ( v39 )
      v40 = v39->value->data;
    else
      v40 = "-1";
    v41 = atoi(v40) + 1;
    v42 = (idDict *)this->guiActive->State(this->guiActive);
    v43 = idDict::FindKey(v42, "notes_num");
    if ( v43 )
      v44 = v43->value->data;
    else
      v44 = "-1";
    if ( v41 < atoi(v44) )
    {
      this->guiActive->SetStateInt(this->guiActive, "notes_sel_0", v41);
LABEL_50:
      this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
      idSessionLocal::HandleNoteCommands(this, "notes");
    }
  }
}

// FUNC: public: void __thiscall idSessionLocal::DispatchCommand(class idUserInterface *,char const *,bool)
void __userpurge idSessionLocal::DispatchCommand(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        const char *a3@<ebp>,
        idUserInterface *gui,
        const char *menuCommand,
        bool doIngame)
{
  int v6; // esi
  int argc; // eax
  const char *v8; // edi
  const char *v9; // eax
  int v10; // esi
  const char *v11; // edi
  idUserInterface_vtbl *v12; // ebp
  const char *v13; // eax
  const char *v14; // eax
  int v15; // esi
  const char *v16; // edi
  idCVarSystem_vtbl *v17; // ebx
  int v18; // eax
  const char *v19; // ebp
  int v20; // esi
  const char *v21; // eax
  int v22; // esi
  const char *v23; // ebx
  unsigned int v24; // edi
  const char *v25; // eax
  char *v26; // eax
  const char *v27; // ebx
  int v28; // esi
  const char *v29; // ebp
  int v30; // esi
  const char *v31; // eax
  unsigned int v32; // edi
  const char *v33; // eax
  const char *v34; // eax
  idCVarSystem_vtbl *v35; // edi
  char *v36; // eax
  const char *v37; // ebx
  int v38; // esi
  const char *v39; // ebp
  idCVar *v40; // edi
  idCVar *v41; // eax
  const char *v42; // eax
  int v43; // esi
  const char *v44; // ebp
  const char *v45; // edi
  int v46; // ebx
  int v47; // ecx
  const char *v48; // eax
  idUserInterface *guiActive; // ecx
  idDict *v50; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  const char *v53; // eax
  int v54; // esi
  const char *v55; // esi
  const char *(__cdecl *guiHandle)(const char *); // eax
  float v57; // [esp+30h] [ebp-93Ch]
  idUserInterface_vtbl *destGUIVar; // [esp+40h] [ebp-92Ch]
  float v61; // [esp+48h] [ebp-924h] BYREF
  float v62; // [esp+4Ch] [ebp-920h] BYREF
  float v63; // [esp+50h] [ebp-91Ch] BYREF
  float v64; // [esp+54h] [ebp-918h] BYREF
  float vals[4]; // [esp+58h] [ebp-914h] BYREF
  idCmdArgs args; // [esp+68h] [ebp-904h] BYREF

  v6 = 0;
  if ( !gui )
  {
    gui = this->guiActive;
    if ( !gui )
      return;
  }
  args.argc = 0;
  idCmdArgs::TokenizeString(&args, menuCommand, 0);
  argc = args.argc;
  if ( args.argc > 0 )
  {
    v57 = *(float *)&a3;
    do
    {
      if ( v6 < 0 || v6 >= argc )
        v8 = &entityFilter;
      else
        v8 = args.argv[v6];
      ++v6;
      if ( idStr::Icmp(v8, "GetCVarValue") )
      {
        if ( idStr::Icmp(v8, "SetCVarValue") )
        {
          if ( idStr::Icmp(v8, "GetVecCVarValue") )
          {
            if ( idStr::Icmp(v8, "SetVecCVarValue") )
            {
              if ( idStr::Icmp(v8, "DupCVar") )
              {
                if ( !idStr::Icmp(v8, "CVarStrcmp") )
                {
                  if ( v6 < 0 || v6 >= args.argc )
                    v42 = &entityFilter;
                  else
                    v42 = args.argv[v6];
                  v43 = v6 + 2;
                  v44 = (const char *)((int (__thiscall *)(idCVarSystem *, const char *, _DWORD, int))cvarSystem->GetCVarString)(
                                        cvarSystem,
                                        v42,
                                        LODWORD(v57),
                                        a2);
                  if ( v43 < 0 || v43 >= (int)args.argv[1] )
                    v45 = &entityFilter;
                  else
                    v45 = *(const char **)&args.tokenized[4 * v43 - 248];
                  v6 = v43 + 1;
                  v46 = 0;
                  if ( !strstr(v45, ";") )
                  {
                    while ( v6 < (int)args.argv[1] )
                    {
                      if ( !idStr::Icmp(v45, v44) )
                      {
                        v47 = *(_DWORD *)(LODWORD(v62) + 9508828);
                        a2 = v46;
                        goto LABEL_90;
                      }
                      ++v46;
                      if ( v6 < 0 || v6 >= (int)args.argv[1] )
                        v45 = &entityFilter;
                      else
                        v45 = *(const char **)&args.tokenized[4 * v6 - 248];
                      ++v6;
                      if ( strstr(v45, ";") )
                        break;
                    }
                  }
                  v47 = *(_DWORD *)(LODWORD(v62) + 9508828);
                  a2 = -1;
LABEL_90:
                  v57 = v61;
                  (*(void (__thiscall **)(int))(*(_DWORD *)v47 + 64))(v47);
                }
              }
              else
              {
                if ( v6 < 0 || v6 >= args.argc )
                  v37 = &entityFilter;
                else
                  v37 = args.argv[v6];
                v38 = v6 + 1;
                if ( v38 < 0 || v38 >= args.argc )
                  v39 = &entityFilter;
                else
                  v39 = args.argv[v38];
                v6 = v38 + 1;
                v40 = cvarSystem->Find(cvarSystem, v37);
                v41 = cvarSystem->Find(cvarSystem, v39);
                if ( v40 && v41 )
                  v41->internalVar->InternalSetString(v41->internalVar, v40->internalVar->value);
                else
                  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
                    common.type,
                    "Bad cvar %s, %s\n",
                    v39,
                    v37);
              }
            }
            else
            {
              if ( v6 < 0 || v6 >= args.argc )
                v27 = &entityFilter;
              else
                v27 = args.argv[v6];
              v28 = v6 + 1;
              if ( v28 < 0 || v28 >= args.argc )
                v29 = &entityFilter;
              else
                v29 = args.argv[v28];
              v30 = v28 + 1;
              if ( v30 < 0 || v30 >= args.argc )
                v31 = &entityFilter;
              else
                v31 = args.argv[v30];
              v6 = v30 + 1;
              v32 = atoi(v31);
              if ( v32 <= 3 )
              {
                v33 = cvarSystem->GetCVarString(cvarSystem, v27);
                v61 = 0.0;
                v62 = 0.0;
                v63 = 0.0;
                v64 = 0.0;
                sscanf(v33, "%f %f %f %f", &v61, &v62, &v63, &v64);
                v34 = gui->GetStateString(gui, v27, &entityFilter);
                *(&v61 + v32) = atof(v34);
                v35 = cvarSystem->__vftable;
                v36 = va("%f %f %f %f", v61, v62, v63, v64);
                v35->SetCVarString(cvarSystem, v29, v36, 0);
              }
            }
          }
          else
          {
            if ( v6 < 0 || v6 >= args.argc )
              v19 = &entityFilter;
            else
              v19 = args.argv[v6];
            v20 = v6 + 1;
            if ( v20 < 0 || v20 >= args.argc )
              v21 = &entityFilter;
            else
              v21 = args.argv[v20];
            v22 = v20 + 1;
            if ( v22 < 0 || v22 >= args.argc )
              v23 = &entityFilter;
            else
              v23 = args.argv[v22];
            v6 = v22 + 1;
            v24 = atoi(v21);
            if ( v24 <= 3 )
            {
              v25 = cvarSystem->GetCVarString(cvarSystem, v19);
              memset(vals, 0, sizeof(vals));
              sscanf(v25, "%f %f %f %f", vals, &vals[1], &vals[2], &vals[3]);
              destGUIVar = gui->__vftable;
              v26 = va("%f", vals[v24]);
              destGUIVar->SetStateString(gui, v23, v26);
            }
          }
        }
        else
        {
          if ( v6 < 0 || v6 >= args.argc )
            v14 = &entityFilter;
          else
            v14 = args.argv[v6];
          v15 = v6 + 1;
          if ( v15 < 0 || v15 >= args.argc )
            v16 = &entityFilter;
          else
            v16 = args.argv[v15];
          v17 = cvarSystem->__vftable;
          v6 = v15 + 1;
          v18 = ((int (__thiscall *)(idUserInterface *, const char *, const char *, _DWORD))gui->GetStateString)(
                  gui,
                  v14,
                  &entityFilter,
                  0);
          ((void (__thiscall *)(idCVarSystem *, const char *, int))v17->SetCVarString)(cvarSystem, v16, v18);
        }
      }
      else
      {
        if ( v6 < 0 || v6 >= args.argc )
          v9 = &entityFilter;
        else
          v9 = args.argv[v6];
        v10 = v6 + 1;
        if ( v10 < 0 || v10 >= args.argc )
          v11 = &entityFilter;
        else
          v11 = args.argv[v10];
        v12 = gui->__vftable;
        v6 = v10 + 1;
        v13 = cvarSystem->GetCVarString(cvarSystem, v9);
        v12->SetStateString(gui, v11, v13);
      }
      argc = args.argc;
    }
    while ( v6 < args.argc );
    a3 = (const char *)LODWORD(v57);
  }
  if ( gui != this->guiMainMenu )
  {
    if ( gui == this->guiIntro )
    {
      idSessionLocal::HandleIntroMenuCommands(this, menuCommand);
    }
    else if ( gui == this->guiMsg )
    {
      idSessionLocal::HandleMsgCommands(this, menuCommand);
    }
    else if ( gui == this->guiTakeNotes || gui == this->guiBuildNotes || gui == this->guiQANotes )
    {
      idSessionLocal::HandleNoteCommands(this, (int)a3, (int)this, menuCommand);
    }
    else if ( gui == this->guiEditCVars )
    {
      idSessionLocal::HandleEditCVarCommands(this, menuCommand);
    }
    else if ( gui == this->guiSpawn )
    {
      idSessionLocal::HandleSpawnGUICommands(this, menuCommand);
    }
    else if ( gui == this->guiRestartMenu )
    {
      idSessionLocal::HandleRestartMenuCommands(this, a3, menuCommand);
    }
    else if ( game
           && (guiActive = this->guiActive) != 0
           && ((v50 = (idDict *)guiActive->State(guiActive), (Key = idDict::FindKey(v50, "gameDraw")) == 0)
             ? (data = "0")
             : (data = Key->value->data),
               atoi(data)) )
    {
      v53 = game->HandleGuiCommands(game, menuCommand);
      v54 = (int)v53;
      if ( v53 )
      {
        if ( idStr::Icmpn(v53, aM, 4) )
        {
          if ( strstr((const char *)v54, "sound ") == (char *)v54
            || strstr((const char *)v54, "FilterMPMapList") == (char *)v54
            || strstr((const char *)v54, "AddMapLive") == (char *)v54
            || strstr((const char *)v54, "RemoveMapLive") == (char *)v54 )
          {
            idSessionLocal::HandleMainMenuCommands(this, v54, (const char *)v54);
          }
        }
        else if ( *(_BYTE *)(v54 + 4) && (v55 = (const char *)(v54 + 5), *v55) )
        {
          this->StartMenu(this, v55);
        }
        else
        {
          this->StartMenu(this, &entityFilter);
        }
      }
      else
      {
        this->guiActive = 0;
      }
    }
    else
    {
      guiHandle = this->guiHandle;
      if ( !guiHandle )
      {
        if ( !doIngame )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 132))(
            common.type,
            "idSessionLocal::DispatchCommand: no dispatch found for command '%s'\n",
            menuCommand);
          return;
        }
LABEL_136:
        idSessionLocal::HandleInGameCommands(this, menuCommand);
        return;
      }
      if ( (int)guiHandle(menuCommand) )
        return;
    }
    if ( !doIngame )
      return;
    goto LABEL_136;
  }
  v48 = cvarSystem->GetCVarString(cvarSystem, "fs_game");
  if ( idStr::Icmp(v48, "q4basexenon") || !idSessionLocal::HandleXboxMainMenuCommands(this, menuCommand) )
    idSessionLocal::HandleMainMenuCommands(this, v6, menuCommand);
}

// FUNC: public: void __thiscall idSessionLocal::MenuEvent(struct sysEvent_s const *)
void __userpurge idSessionLocal::MenuEvent(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        const char *a3@<ebp>,
        const sysEvent_s *event)
{
  const char *v5; // eax
  int evValue; // edi

  if ( this->guiActive )
  {
    v5 = this->guiActive->HandleEvent(this->guiActive, event, com_frameTime, 0);
    if ( v5 && *v5 )
    {
      idSessionLocal::DispatchCommand(this, a2, a3, this->guiActive, v5, 1);
    }
    else if ( event->evType == SE_KEY && event->evValue2 == 1 )
    {
      evValue = event->evValue;
      if ( evValue >= 149 && evValue <= 160 )
        idKeyInput::ExecKeyBinding(evValue);
    }
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::GuiFrameEvents(void)
void __usercall idSessionLocal::GuiFrameEvents(idSessionLocal *this@<ecx>, const char *a2@<ebp>, int a3@<edi>)
{
  bool v4; // zf
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  idUserInterface_vtbl *v8; // edi
  int v9; // eax
  const char *v10; // eax
  const char *v11; // edi
  char *v12; // kr00_4
  _BYTE *alloced; // edx
  const char *v14; // ecx
  char v15; // al
  idUserInterface_vtbl *v16; // edi
  int v17; // eax
  idUserInterface_vtbl *v18; // edi
  int v19; // eax
  idUserInterface_vtbl *v20; // edi
  int v21; // eax
  idUserInterface_vtbl *v22; // edi
  int v23; // eax
  idUserInterface_vtbl *v24; // edi
  const char *v25; // eax
  float v26; // [esp+7Ch] [ebp-60h]
  idVec4 hitscanTint; // [esp+8Ch] [ebp-50h] BYREF
  sysEvent_s ev; // [esp+9Ch] [ebp-40h] BYREF
  idStr hitScanValue; // [esp+B0h] [ebp-2Ch] BYREF
  int v30; // [esp+D8h] [ebp-4h]
  void *retaddr; // [esp+DCh] [ebp+0h]

  if ( console->Active(console) || this->guiActive )
    usercmdGen->InhibitUsercmd(usercmdGen, INHIBIT_SESSION, 1);
  else
    usercmdGen->InhibitUsercmd(usercmdGen, INHIBIT_SESSION, 0);
  if ( this->guiTest || this->guiActive )
  {
    v4 = !cvarSystem->GetCVarBool(cvarSystem, "si_isBuyingEnabled");
    v5 = "1";
    if ( v4 )
      v5 = "0";
    this->guiMainMenu->SetStateString(this->guiMainMenu, "si_isBuyingEnabled", v5);
    v4 = !cvarSystem->GetCVarBool(cvarSystem, "si_usepass");
    v6 = "1";
    if ( v4 )
      v6 = "0";
    this->guiMainMenu->SetStateString(this->guiMainMenu, "si_usepass", v6);
    v4 = !cvarSystem->GetCVarBool(cvarSystem, "g_crosshairCustom");
    v7 = "1";
    if ( v4 )
      v7 = "0";
    ((void (__thiscall *)(idUserInterface *, const char *, const char *, int))this->guiMainMenu->SetStateString)(
      this->guiMainMenu,
      "g_crosshairCustom",
      v7,
      a3);
    v8 = this->guiMainMenu->__vftable;
    v9 = ((int (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarBool)(cvarSystem, "s_useOpenAL");
    v8->SetStateBool(this->guiMainMenu, "s_useOpenAL", v9);
    v10 = cvarSystem->GetCVarString(cvarSystem, "ui_hitscanTint");
    v11 = v10;
    hitScanValue.data = 0;
    *(_DWORD *)hitScanValue.baseBuffer = 20;
    hitScanValue.alloced = (int)&hitScanValue.baseBuffer[4];
    hitScanValue.baseBuffer[4] = 0;
    if ( v10 )
    {
      v12 = (char *)strlen(v10);
      if ( (int)(v12 + 1) > 20 )
        idStr::ReAllocate((idStr *)&hitScanValue.data, (int)(v12 + 1), 1);
      alloced = (_BYTE *)hitScanValue.alloced;
      v14 = v11;
      do
      {
        v15 = *v14;
        *alloced++ = *v14++;
      }
      while ( v15 );
      hitScanValue.data = v12;
    }
    retaddr = 0;
    sscanf((const char *)hitScanValue.alloced, "%f %f %f %f", &hitscanTint.y, &hitscanTint.z, &hitscanTint.w, &ev);
    ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))this->guiMainMenu->SetStateFloat)(
      this->guiMainMenu,
      "ui_hitscanTint",
      LODWORD(hitscanTint.y));
    if ( this->guiMPSettings )
    {
      v16 = this->guiMPSettings->__vftable;
      v17 = ((int (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarBool)(cvarSystem, "si_voiceChat");
      v16->SetStateBool(this->guiMPSettings, "si_voiceChat", v17);
      v18 = this->guiMPSettings->__vftable;
      v19 = ((int (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarBool)(cvarSystem, "s_voiceChatEcho");
      v18->SetStateBool(this->guiMPSettings, "s_voiceChatEcho", v19);
      v20 = this->guiMPSettings->__vftable;
      v21 = ((int (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarBool)(cvarSystem, "s_voiceChatSend");
      v20->SetStateBool(this->guiMPSettings, "s_voiceChatSend", v21);
      v22 = this->guiMPSettings->__vftable;
      v23 = ((int (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarBool)(
              cvarSystem,
              "s_voiceChatReceive");
      v22->SetStateBool(this->guiMPSettings, "s_voiceChatReceive", v23);
      v24 = this->guiMPSettings->__vftable;
      v26 = cvarSystem->GetCVarFloat(cvarSystem, "s_volumeVoice");
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))v24->SetStateFloat)(
        this->guiMPSettings,
        "s_volumeVoice",
        LODWORD(v26));
      ((void (__thiscall *)(idUserInterface *, const char *, _DWORD))this->guiMPSettings->SetStateFloat)(
        this->guiMPSettings,
        "ui_hitscanTint",
        LODWORD(hitscanTint.y));
    }
    hitScanValue.len = 0;
    memset(&ev.evValue, 0, 16);
    v25 = (const char *)(*(int (__thiscall **)(_DWORD, int *, unsigned int))(*(_DWORD *)LODWORD(hitscanTint.x) + 32))(
                          LODWORD(hitscanTint.x),
                          &ev.evValue,
                          com_frameTime);
    if ( v25 )
    {
      if ( *v25 )
        idSessionLocal::DispatchCommand(this, 0, a2, this->guiActive, v25, 1);
    }
    v30 = -1;
    idStr::FreeData(&hitScanValue);
  }
}

// FUNC: public: void __thiscall idSessionLocal::HandleSpawnGUICommands(char const *)
void __userpurge idSessionLocal::HandleSpawnGUICommands(
        idSessionLocal *this@<ecx>,
        const char *a2@<ebp>,
        const char *menuCommand)
{
  const char *v4; // eax
  int v5; // ebp
  int v6; // eax
  char *data; // edx
  const char *v8; // ecx
  char v9; // al
  idStr command; // [esp+8h] [ebp-2Ch] BYREF
  int v11; // [esp+30h] [ebp-4h]

  if ( !this->mapSpawned )
  {
    this->guiActive = 0;
    return;
  }
  if ( !idStr::Icmp(menuCommand, "init") )
  {
    this->guiActive->SetStateBool(this->guiActive, "spawnListVisible", 1);
    this->guiActive->SetStateBool(this->guiActive, "spawningVisible", 0);
    this->guiActive->SetStateInt(this->guiActive, "init", 1);
    this->guiActive->HandleNamedEvent(this->guiActive, "ActivateMonsters");
    idSessionLocal::DispatchCommand(this, 0, a2, this->guiActive, "select Monster", 0);
    return;
  }
  if ( idStr::Icmpn(menuCommand, "select", 6) )
  {
    if ( idStr::Icmpn(menuCommand, "spawn", 5) )
    {
      if ( idStr::Icmp(menuCommand, "close") )
        return;
    }
    else
    {
      this->guiActive->SetStateBool(this->guiActive, "spawnListVisible", 0);
      this->guiActive->SetStateBool(this->guiActive, "spawningVisible", 1);
      this->guiActive->StateChanged(this->guiActive, com_frameTime, 0);
      this->UpdateScreen(this, 1);
      cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_NOW, menuCommand);
    }
    this->guiActive = 0;
    idKeyInput::ClearStates();
  }
  else
  {
    command.len = 0;
    command.alloced = 20;
    command.data = command.baseBuffer;
    command.baseBuffer[0] = 0;
    if ( menuCommand )
    {
      v4 = &menuCommand[strlen(menuCommand) + 1];
      v5 = v4 - (menuCommand + 1);
      v6 = v4 - menuCommand;
      if ( v6 > 20 )
        idStr::ReAllocate(&command, v6, 1);
      data = command.data;
      v8 = menuCommand;
      do
      {
        v9 = *v8;
        *data++ = *v8++;
      }
      while ( v9 );
      command.len = v5;
    }
    v11 = 0;
    idStr::StripLeading(&command, "select ");
    idSessionLocal::PopulateSpawnGUI(this, command.data);
    v11 = -1;
    idStr::FreeData(&command);
  }
}

// FUNC: public: virtual void __thiscall idSessionLocal::StartMenu(char const *)
void __userpurge idSessionLocal::StartMenu(
        idSessionLocal *this@<ecx>,
        int a2@<ebx>,
        const char *a3@<ebp>,
        const char *namedEvent)
{
  const char *v5; // eax
  idUserInterface_vtbl *v6; // edi
  int v7; // eax
  idCVarSystem_vtbl *v8; // esi
  int v9; // eax

  if ( this->guiActive != this->guiMainMenu )
  {
    if ( this->readDemo )
      idSessionLocal::UnloadMap(this);
    this->SetGUI(this, this->guiMainMenu, 0);
    soundSystem->SetActiveSoundWorld(soundSystem, 1);
    v5 = (const char *)((int (__thiscall *)(idCVarSystem *))cvarSystem->GetCVarString)(cvarSystem);
    if ( !idStr::Icmp(v5, "fs_game") )
      idSessionLocal::DispatchCommand(this, a2, a3, this->guiActive, "Init", 0);
    this->guiMainMenu->HandleNamedEvent(this->guiMainMenu, namedEvent);
    v6 = this->guiMainMenu->__vftable;
    v7 = (*(int (__thiscall **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 168))(
           common.type,
           "#str_107212",
           -1);
    v6->SetStateString(this->guiMainMenu, "game_list", (const char *)v7);
    console->Close(console);
    cvarSystem->SetCVarBool(cvarSystem, "ui_chat", 1, 0);
    v8 = cvarSystem->__vftable;
    v9 = ((int (__thiscall *)(idCVarSystem *, const char *, _DWORD))cvarSystem->GetCVarString)(cvarSystem, "ui_name", 0);
    ((void (__thiscall *)(idCVarSystem *, const char *, int))v8->SetCVarString)(cvarSystem, "gui_ui_name", v9);
  }
}
