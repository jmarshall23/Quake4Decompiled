
// FUNC: void __cdecl Script_EvalRegs(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_EvalRegs(idWindow *window)
{
  idWindow::EvalRegs(window, 0xFFFFFFFF, 1);
}

// FUNC: void __cdecl Script_EndGame(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_EndGame()
{
  cvarSystem->SetCVarBool(cvarSystem, "g_nightmare", 1, 0);
  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, "disconnect\n");
}

// FUNC: void __cdecl Script_ResetCinematics(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_ResetCinematics(idWindow *window)
{
  idWindow::ResetCinematics(window);
}

// FUNC: void __cdecl Script_SetFocus(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_SetFocus(idWindow *window, idList<idGSWinVar> *src)
{
  char *v2; // eax
  idWindow *v3; // eax
  drawWin_t *ChildByName; // eax
  idWindow **p_win; // esi
  idWindow *win; // eax
  char *v7; // eax
  const char *v8; // [esp-Ch] [ebp-10h]

  v2 = __RTDynamicCast(
         (void **)src->list->var,
         0,
         (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
         (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
         0);
  if ( v2 )
  {
    v8 = (const char *)*((_DWORD *)v2 + 5);
    v3 = window->gui->GetDesktop(window->gui);
    ChildByName = idWindow::FindChildByName(v3, v8);
    p_win = &ChildByName->win;
    if ( ChildByName )
    {
      win = ChildByName->win;
      if ( *p_win )
      {
        idWindow::SetFocus(window, win, 1);
        if ( src->num > 1 )
        {
          v7 = __RTDynamicCast(
                 (void **)&src->list[1].var->__vftable,
                 0,
                 (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
                 (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
                 0);
          if ( v7 )
          {
            if ( !idStr::Icmp(*((const char **)v7 + 5), "st") )
              idWindow::ClearTransitions(*p_win);
          }
        }
      }
    }
  }
}

// FUNC: void __cdecl Script_ShowCursor(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_ShowCursor(idWindow *window, idList<idGSWinVar> *src)
{
  char *v2; // eax
  bool v3; // zf
  idUserInterfaceLocal_vtbl *v4; // edx
  idWindow *v5; // eax
  idWindow *v6; // eax

  v2 = __RTDynamicCast(
         (void **)src->list->var,
         0,
         (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
         (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
         0);
  if ( v2 )
  {
    v3 = atoi(*((const char **)v2 + 5)) == 0;
    v4 = window->gui->__vftable;
    if ( v3 )
    {
      v6 = (idWindow *)((int (*)(void))v4->GetDesktop)();
      idWindow::SetFlag(v6, 0x80000u);
    }
    else
    {
      v5 = (idWindow *)((int (*)(void))v4->GetDesktop)();
      idWindow::ClearFlag(v5, 0x80000u);
    }
  }
}

// FUNC: void __cdecl Script_LocalSound(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_LocalSound(idWindow *window, idList<idGSWinVar> *src)
{
  char *v2; // eax

  v2 = __RTDynamicCast(
         (void **)src->list->var,
         0,
         (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
         (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
         0);
  if ( v2 )
    soundSystem->PlayShaderDirectly(soundSystem, 1, (const char *)*((_DWORD *)v2 + 5), -1);
}

// FUNC: void __cdecl Script_SetLightColor(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_SetLightColor(idWindow *window, idList<idGSWinVar> *src)
{
  idUserInterfaceLocal *gui; // esi

  gui = window->gui;
  gui->lightColorVar = (idWinVec4 *)__RTDynamicCast(
                                      (void **)src->list->var,
                                      0,
                                      (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
                                      (TypeDescriptor *)&idWinVec4 `RTTI Type Descriptor',
                                      0);
}

// FUNC: void __cdecl Script_NonInteractive(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_NonInteractive(idWindow *window, idList<idGSWinVar> *src)
{
  char *v2; // eax
  idUserInterfaceLocal *gui; // esi
  idUserInterfaceLocal_vtbl *v4; // edi
  const char *v5; // eax
  int v6; // eax

  v2 = __RTDynamicCast(
         (void **)src->list->var,
         0,
         (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
         (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
         0);
  if ( v2 )
  {
    gui = window->gui;
    v4 = gui->__vftable;
    v5 = (const char *)(*(int (__thiscall **)(char *))(*(_DWORD *)v2 + 32))(v2);
    v6 = atoi(v5);
    LOBYTE(v6) = v6 == 0;
    v4->SetInteractive(gui, v6);
  }
  else
  {
    window->gui->SetInteractive(window->gui, 0);
  }
}

// FUNC: void __cdecl Script_ResetTime(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_ResetTime(idWindow *window, idList<idGSWinVar> *src)
{
  char *v2; // eax
  idWindow *v3; // eax
  drawWin_t *ChildByName; // esi
  int v5; // eax
  int v6; // eax
  const char *v7; // [esp-4h] [ebp-10h]

  v2 = __RTDynamicCast(
         (void **)src->list->var,
         0,
         (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
         (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
         0);
  if ( v2
    && src->num > 1
    && (v7 = (const char *)*((_DWORD *)v2 + 5),
        v3 = window->gui->GetDesktop(window->gui),
        ChildByName = idWindow::FindChildByName(v3, v7),
        v2 = __RTDynamicCast(
               (void **)&src->list[1].var->__vftable,
               0,
               (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
               (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
               0),
        ChildByName)
    && ChildByName->win )
  {
    v5 = atoi(*((const char **)v2 + 5));
    idWindow::ResetTime(ChildByName->win, v5);
    idWindow::EvalRegs(ChildByName->win, 0xFFFFFFFF, 1);
  }
  else
  {
    v6 = atoi(*((const char **)v2 + 5));
    idWindow::ResetTime(window, v6);
    idWindow::EvalRegs(window, 0xFFFFFFFF, 1);
  }
}

// FUNC: void __cdecl Script_ResetVideo(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_ResetVideo(idWindow *window, idList<idGSWinVar> *src)
{
  idWindow *v2; // eax
  drawWin_t *ChildByName; // eax
  idWindow **p_win; // esi
  idSimpleWindow *simp; // ecx
  const char *v6; // [esp-4h] [ebp-Ch]

  v6 = (const char *)*((_DWORD *)__RTDynamicCast(
                                   (void **)src->list->var,
                                   0,
                                   (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
                                   (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
                                   0)
                     + 5);
  v2 = window->gui->GetDesktop(window->gui);
  ChildByName = idWindow::FindChildByName(v2, v6);
  p_win = &ChildByName->win;
  if ( !ChildByName )
    goto LABEL_6;
  if ( ChildByName->win )
  {
    idWindow::ResetCinematics(ChildByName->win);
    idWindow::EvalRegs(*p_win, 0xFFFFFFFF, 1);
    return;
  }
  simp = ChildByName->simp;
  if ( simp )
  {
    idSimpleWindow::ResetCinematics(simp);
  }
  else
  {
LABEL_6:
    idWindow::ResetCinematics(window);
    idWindow::EvalRegs(window, 0xFFFFFFFF, 1);
  }
}

// FUNC: void __cdecl Script_Transition(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_Transition(idWindow *window, idList<idGSWinVar> *src)
{
  idGSWinVar *list; // eax
  int v4; // edi
  double v5; // st7
  float ac; // [esp+Ch] [ebp-24h]
  idVec4 from; // [esp+10h] [ebp-20h]
  idVec4 to; // [esp+20h] [ebp-10h]
  idList<idGSWinVar> *srca; // [esp+38h] [ebp+8h]

  if ( src->num >= 4 )
  {
    list = src->list;
    v4 = (int)list[3].var[1].__vftable;
    if ( src->num <= 5 )
    {
      ac = 0.0;
      srca = 0;
    }
    else
    {
      ac = *(float *)&list[4].var[1].__vftable;
      srca = (idList<idGSWinVar> *)list[5].var[1].__vftable;
    }
    if ( __RTDynamicCast(
           (void **)&list[1].var->__vftable,
           0,
           (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
           (TypeDescriptor *)&idWinVec4 `RTTI Type Descriptor',
           0) )
    {
      from = (idVec4)src->list[1].var[1];
    }
    else
    {
      if ( __RTDynamicCast(
             (void **)&src->list[1].var->__vftable,
             0,
             (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
             (TypeDescriptor *)&idWinFloat `RTTI Type Descriptor',
             0) )
      {
        v5 = *(float *)&src->list[1].var[1].__vftable;
      }
      else
      {
        v5 = ((double (__thiscall *)(idWinVar_vtbl *, idDict *))*((_DWORD *)src->list[1].var[1].~idWinVar + 6))(
               src->list[1].var[1].__vftable,
               src->list[1].var[1].guiDict);
      }
      from.y = v5;
      from.z = v5;
      from.w = v5;
      from.x = v5;
    }
    if ( __RTDynamicCast(
           (void **)&src->list[2].var->__vftable,
           0,
           (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
           (TypeDescriptor *)&idWinVec4 `RTTI Type Descriptor',
           0) )
    {
      to = (idVec4)src->list[2].var[1];
    }
    else if ( __RTDynamicCast(
                (void **)&src->list[2].var->__vftable,
                0,
                (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
                (TypeDescriptor *)&idWinFloat `RTTI Type Descriptor',
                0) )
    {
      to.w = *(float *)&src->list[2].var[1].__vftable;
      to.z = to.w;
      to.y = to.w;
      to.x = to.w;
    }
    else
    {
      from.w = ((double (__thiscall *)(idWinVar_vtbl *, idDict *))*((_DWORD *)src->list[2].var[1].~idWinVar + 6))(
                 src->list[2].var[1].__vftable,
                 src->list[2].var[1].guiDict);
      from.z = from.w;
      from.y = from.w;
      from.x = from.w;
    }
    src->list->var->SetEval(src->list->var, 0);
    idWindow::AddTransition(window, src->list->var, from, to, v4, ac, *(float *)&srca);
    idWindow::StartTransition(window);
  }
}

// FUNC: public: void __thiscall idGuiScript::WriteToSaveGame(class idFile *)
void __thiscall idGuiScript::WriteToSaveGame(idGuiScript *this, idFile *savefile)
{
  idGuiScriptList *ifList; // esi
  int i; // edi
  idGuiScriptList *elseList; // edi
  int j; // esi
  int k; // esi
  idGSWinVar *list; // eax
  bool v9; // zf
  idGSWinVar *v10; // eax

  ifList = this->ifList;
  if ( ifList )
  {
    for ( i = 0; i < ifList->list.num; ++i )
      idGuiScript::WriteToSaveGame(ifList->list.list[i], savefile);
  }
  elseList = this->elseList;
  if ( elseList )
  {
    for ( j = 0; j < elseList->list.num; ++j )
      idGuiScript::WriteToSaveGame(elseList->list.list[j], savefile);
  }
  savefile->Write(savefile, this, 4);
  for ( k = 0; k < this->parms.num; ++k )
  {
    list = this->parms.list;
    v9 = !list[k].own;
    v10 = &list[k];
    if ( !v9 )
      v10->var->WriteToSaveGame(v10->var, savefile);
  }
}

// FUNC: public: void __thiscall idGuiScript::ReadFromSaveGame(class idFile *)
void __thiscall idGuiScript::ReadFromSaveGame(idGuiScript *this, idFile *savefile)
{
  idGuiScriptList *ifList; // esi
  int i; // edi
  idGuiScriptList *elseList; // edi
  int j; // esi
  int k; // esi
  idGSWinVar *list; // eax
  bool v9; // zf
  idGSWinVar *v10; // eax

  ifList = this->ifList;
  if ( ifList )
  {
    for ( i = 0; i < ifList->list.num; ++i )
      idGuiScript::ReadFromSaveGame(ifList->list.list[i], savefile);
  }
  elseList = this->elseList;
  if ( elseList )
  {
    for ( j = 0; j < elseList->list.num; ++j )
      idGuiScript::ReadFromSaveGame(elseList->list.list[j], savefile);
  }
  savefile->Read(savefile, this, 4);
  for ( k = 0; k < this->parms.num; ++k )
  {
    list = this->parms.list;
    v9 = !list[k].own;
    v10 = &list[k];
    if ( !v9 )
      v10->var->ReadFromSaveGame(v10->var, savefile);
  }
}

// FUNC: public: void __thiscall idGuiScriptList::Execute(class idWindow *)
void __thiscall idGuiScriptList::Execute(idGuiScriptList *this, idWindow *win)
{
  int num; // esi
  int v4; // ebx
  idGuiScript *v5; // esi
  idGuiScriptList *v6; // eax
  void (__cdecl *handler)(idWindow *, idList<idGSWinVar> *); // eax
  int c; // [esp+10h] [ebp-4h]

  num = this->list.num;
  c = this->list.num;
  if ( gui_debugScript.internalVar->integerValue )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "GUI: %s: commands:\n",
      win->name.data);
  v4 = 0;
  if ( num > 0 )
  {
    do
    {
      v5 = this->list.list[v4];
      if ( v5->conditionReg >= 0 && win->ops.num > 0 )
      {
        v6 = 0.0 == idWindow::EvalRegs(win, v5->conditionReg, 0) ? v5->elseList : v5->ifList;
        if ( v6 )
          idWindow::RunScriptList(win, v6);
      }
      handler = v5->handler;
      if ( handler )
        handler(win, &v5->parms);
      ++v4;
    }
    while ( v4 < c );
  }
}

// FUNC: public: void __thiscall idGuiScriptList::WriteToSaveGame(class idFile *)
void __thiscall idGuiScriptList::WriteToSaveGame(idGuiScriptList *this, idFile *savefile)
{
  int i; // esi

  for ( i = 0; i < this->list.num; ++i )
    idGuiScript::WriteToSaveGame(this->list.list[i], savefile);
}

// FUNC: public: void __thiscall idGuiScriptList::ReadFromSaveGame(class idFile *)
void __thiscall idGuiScriptList::ReadFromSaveGame(idGuiScriptList *this, idFile *savefile)
{
  int i; // esi

  for ( i = 0; i < this->list.num; ++i )
    idGuiScript::ReadFromSaveGame(this->list.list[i], savefile);
}

// FUNC: void __cdecl Script_Set(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_Set(idWindow *window, idList<idGSWinVar> *src)
{
  idList<idGSWinVar> *v2; // ebp
  bool v3; // cc
  const char *v4; // eax
  const char *v5; // esi
  char *v6; // eax
  char **v7; // eax
  char **v8; // esi
  char *v9; // eax
  int v10; // esi
  int v11; // eax
  char v12; // cl
  char *v13; // edx
  idWinVar *v14; // ecx
  const char *v15; // eax
  const char *v16; // esi
  int v17; // edi
  char v18; // cl
  int v19; // eax
  char *v20; // edx
  int v21; // esi
  int v22; // eax
  char v23; // cl
  char *v24; // edx
  int v25; // ebp
  char *v26; // edi
  int v27; // eax
  idGSWinVar *v28; // eax
  idWinVar *v29; // ecx
  idWinVar *v30; // edi
  char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *v33; // eax
  const char *data; // esi
  int v35; // eax
  idGSWinVar *list; // eax
  idWinVar *var; // esi
  idWinVar_vtbl *v38; // edi
  int v39; // eax
  int i; // [esp+10h] [ebp-54h]
  int parmCount; // [esp+14h] [ebp-50h]
  idStr val; // [esp+18h] [ebp-4Ch] BYREF
  idStr key; // [esp+38h] [ebp-2Ch] BYREF
  int v44; // [esp+60h] [ebp-4h]
  idList<idGSWinVar> *srca; // [esp+6Ch] [ebp+8h]

  key.len = 0;
  key.alloced = 20;
  key.data = key.baseBuffer;
  key.baseBuffer[0] = 0;
  v44 = 0;
  val.len = 0;
  val.alloced = 20;
  val.data = val.baseBuffer;
  val.baseBuffer[0] = 0;
  v2 = src;
  v3 = src->num < 2;
  LOBYTE(v44) = 1;
  if ( v3 )
  {
    v4 = src->list->var->c_str(src->list->var);
    v5 = v4;
    if ( !v4 || !*v4 )
      v5 = "unknown";
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Script_Set: src < %s > on window < %s > does not contain value to set to",
      v5,
      window->name.data);
    (*(void (**)(_DWORD, const char *, ...))(**(_DWORD **)common.ip + 148))(
      *(_DWORD *)common.ip,
      "Script_Set: src < %s > on window < %s > does not contain value to set to",
      v5,
      window->name.data);
    goto LABEL_40;
  }
  v6 = __RTDynamicCast(
         (void **)src->list->var,
         0,
         (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
         (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
         0);
  if ( !v6 || idStr::Icmp(*((const char **)v6 + 5), "cmd") )
  {
    if ( !gui_debugScript.internalVar->integerValue )
    {
LABEL_39:
      list = v2->list;
      var = list->var;
      v38 = list->var->__vftable;
      v39 = (int)list[1].var->c_str(list[1].var);
      v38->Set(var, (const char *)v39);
      v2->list->var->SetEval(v2->list->var, 0);
      goto LABEL_40;
    }
    v28 = src->list;
    v29 = v28->var;
    v30 = v28[1].var;
    name = v28->var->name;
    if ( name )
    {
      guiDict = v29->guiDict;
      if ( !guiDict || *name != 42 )
      {
        data = name;
        goto LABEL_38;
      }
      v33 = idDict::FindKey(guiDict, name + 1);
      if ( v33 )
      {
        data = v33->value->data;
LABEL_38:
        srca = *(idList<idGSWinVar> **)common.type;
        v35 = (int)v30->c_str(v30);
        ((void (*)(netadrtype_t, const char *, ...))srca[7].list)(common.type, "   %s = %s\n", data, v35);
        goto LABEL_39;
      }
    }
    data = &entityFilter;
    goto LABEL_38;
  }
  v7 = (char **)__RTDynamicCast(
                  (void **)&src->list[1].var->__vftable,
                  0,
                  (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
                  (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
                  0);
  v8 = v7;
  parmCount = src->num;
  if ( src->num <= 2 )
  {
    idWindow::AddCommand(window, v7[5]);
    if ( gui_debugScript.internalVar->integerValue )
    {
      v25 = *(_DWORD *)common.type;
      v26 = window->name.data;
      v27 = (*((int (__thiscall **)(char **))*v8 + 8))(v8);
      (*(void (**)(netadrtype_t, const char *, ...))(v25 + 124))(common.type, "   %s cmd %s\n", v26, v27);
    }
  }
  else
  {
    v9 = (char *)(*((int (__thiscall **)(char **))*v7 + 8))(v7);
    idStr::operator=(&val, v9);
    i = 2;
    do
    {
      v10 = val.len + 2;
      if ( val.len + 3 > val.alloced )
        idStr::ReAllocate(&val, val.len + 3, 1);
      v11 = 0;
      v12 = 32;
      do
      {
        v13 = &val.data[v11++];
        v13[val.len] = v12;
        v12 = asc_102CF7E0[v11];
      }
      while ( v12 );
      val.len = v10;
      val.data[v10] = 0;
      v14 = v2->list[i].var;
      v15 = v14->c_str(v14);
      v16 = v15;
      if ( v15 )
      {
        v17 = strlen(v15) + val.len;
        if ( v17 + 1 > val.alloced )
          idStr::ReAllocate(&val, v17 + 1, 1);
        v18 = *v16;
        v19 = 0;
        if ( *v16 )
        {
          do
          {
            v20 = &val.data[v19++];
            v20[val.len] = v18;
            v18 = v16[v19];
          }
          while ( v18 );
          v2 = src;
        }
        val.len = v17;
        val.data[v17] = 0;
      }
      v21 = val.len + 1;
      if ( val.len + 2 > val.alloced )
        idStr::ReAllocate(&val, val.len + 2, 1);
      v22 = 0;
      v23 = 34;
      do
      {
        v24 = &val.data[v22++];
        v24[val.len] = v23;
        v23 = asc_102A737C[v22];
      }
      while ( v23 );
      val.len = v21;
      val.data[v21] = 0;
      ++i;
    }
    while ( i < parmCount );
    idWindow::AddCommand(window, val.data);
    if ( gui_debugScript.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "   %s cmd %s\n",
        window->name.data,
        val.data);
  }
LABEL_40:
  LOBYTE(v44) = 0;
  idStr::FreeData(&val);
  v44 = -1;
  idStr::FreeData(&key);
}

// FUNC: void __cdecl Script_RunScript(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_RunScript(idWindow *window, idList<idGSWinVar> *src)
{
  int len; // esi
  idStr *p_cmd; // edi
  char *data; // ecx
  char *v5; // edx
  char v6; // al
  int v7; // esi
  int v8; // eax
  char v9; // cl
  char *v10; // edx
  const char *v11; // eax
  const char *v12; // esi
  int v13; // edi
  char v14; // cl
  int i; // eax
  char *v16; // edx
  int v17; // ebp
  char *parm; // [esp+0h] [ebp-30h]
  idStr str; // [esp+4h] [ebp-2Ch] BYREF
  int v20; // [esp+2Ch] [ebp-4h]

  parm = __RTDynamicCast(
           (void **)src->list->var,
           0,
           (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
           (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
           0);
  if ( parm )
  {
    len = window->cmd.len;
    p_cmd = &window->cmd;
    str.data = str.baseBuffer;
    str.len = 0;
    str.alloced = 20;
    str.baseBuffer[0] = 0;
    if ( len + 1 > 20 )
      idStr::ReAllocate(&str, len + 1, 1);
    data = window->cmd.data;
    v5 = str.data;
    do
    {
      v6 = *data;
      *v5++ = *data++;
    }
    while ( v6 );
    str.len = len;
    v7 = len + 13;
    v20 = 0;
    if ( v7 + 1 > str.alloced )
      idStr::ReAllocate(&str, v7 + 1, 1);
    v8 = 0;
    v9 = 32;
    do
    {
      v10 = &str.data[v8++];
      v10[str.len] = v9;
      v9 = aRunscript[v8];
    }
    while ( v9 );
    str.len = v7;
    str.data[v7] = 0;
    v11 = (const char *)(*(int (__thiscall **)(char *))(*(_DWORD *)parm + 32))(parm);
    v12 = v11;
    if ( v11 )
    {
      v13 = strlen(v11) + str.len;
      if ( v13 + 1 > str.alloced )
        idStr::ReAllocate(&str, v13 + 1, 1);
      v14 = *v12;
      for ( i = 0; v14; v14 = v12[i] )
      {
        v16 = &str.data[i++];
        v16[str.len] = v14;
      }
      str.len = v13;
      str.data[v13] = 0;
      p_cmd = &window->cmd;
    }
    v17 = str.len;
    if ( str.len + 1 > p_cmd->alloced )
      idStr::ReAllocate(p_cmd, str.len + 1, 0);
    qmemcpy(p_cmd->data, str.data, v17);
    window->cmd.data[v17] = 0;
    window->cmd.len = v17;
    v20 = -1;
    idStr::FreeData(&str);
  }
}

// FUNC: void __cdecl Script_NamedEvent(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_NamedEvent(idWindow *window, idList<idGSWinVar> *src)
{
  char *v2; // eax
  char *v3; // edi
  int v4; // esi
  char *v5; // ecx
  char *data; // edx
  char v7; // al
  int Text; // eax
  int v9; // esi
  idUserInterfaceLocal *gui; // ecx
  idUserInterfaceLocal_vtbl *v11; // eax
  idWindow *v12; // eax
  drawWin_t *ChildByName; // eax
  char *v14; // [esp-8h] [ebp-7Ch]
  idStr event; // [esp+8h] [ebp-6Ch] BYREF
  idStr winEvent; // [esp+28h] [ebp-4Ch] BYREF
  idStr winName; // [esp+48h] [ebp-2Ch] BYREF
  int v18; // [esp+70h] [ebp-4h]

  v2 = __RTDynamicCast(
         (void **)src->list->var,
         0,
         (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
         (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
         0);
  v3 = v2;
  if ( v2 )
  {
    v4 = *((_DWORD *)v2 + 4);
    event.data = event.baseBuffer;
    event.len = 0;
    event.alloced = 20;
    event.baseBuffer[0] = 0;
    if ( v4 + 1 > 20 )
      idStr::ReAllocate(&event, v4 + 1, 1);
    v5 = (char *)*((_DWORD *)v3 + 5);
    data = event.data;
    do
    {
      v7 = *v5;
      *data++ = *v5++;
    }
    while ( v7 );
    event.len = v4;
    v18 = 0;
    Text = idStr::FindText(event.data, "::", 1, 0, v4);
    v9 = Text;
    if ( Text <= 0 )
    {
      window->gui->HandleNamedEvent(window->gui, (const char *)*((_DWORD *)v3 + 5));
    }
    else
    {
      idStr::Left(&event, &winName, Text);
      LOBYTE(v18) = 1;
      idStr::Right(&event, &winEvent, event.len - v9 - 2);
      gui = window->gui;
      v11 = gui->__vftable;
      v14 = winName.data;
      LOBYTE(v18) = 2;
      v12 = v11->GetDesktop(gui);
      ChildByName = idWindow::FindChildByName(v12, v14);
      if ( ChildByName && ChildByName->win )
      {
        ChildByName->win->RunNamedEvent(ChildByName->win, winEvent.data);
      }
      else if ( gui_debugScript.internalVar->integerValue )
      {
        if ( !ChildByName )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
            common.type,
            "GUI: %s: unknown window %s for named event %s\n",
            window->name.data,
            winName.data,
            winEvent.data);
      }
      LOBYTE(v18) = 1;
      idStr::FreeData(&winEvent);
      LOBYTE(v18) = 0;
      idStr::FreeData(&winName);
    }
    v18 = -1;
    idStr::FreeData(&event);
  }
}

// FUNC: void __cdecl Script_StopTransitions(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_StopTransitions(idWindow *window, idList<idGSWinVar> *src)
{
  char *v2; // eax
  char *v3; // esi
  int v4; // edi
  char *v5; // ecx
  char *data; // edx
  char v7; // al
  idUserInterfaceLocal *gui; // ecx
  idUserInterfaceLocal_vtbl *v9; // eax
  idWindow *v10; // eax
  drawWin_t *ChildByName; // eax
  char *v12; // [esp-8h] [ebp-38h]
  idStr winName; // [esp+4h] [ebp-2Ch] BYREF
  int v14; // [esp+2Ch] [ebp-4h]

  v2 = __RTDynamicCast(
         (void **)src->list->var,
         0,
         (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
         (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
         0);
  v3 = v2;
  if ( v2 )
  {
    v4 = *((_DWORD *)v2 + 4);
    winName.data = winName.baseBuffer;
    winName.len = 0;
    winName.alloced = 20;
    winName.baseBuffer[0] = 0;
    if ( v4 + 1 > 20 )
      idStr::ReAllocate(&winName, v4 + 1, 1);
    v5 = (char *)*((_DWORD *)v3 + 5);
    data = winName.data;
    do
    {
      v7 = *v5;
      *data++ = *v5++;
    }
    while ( v7 );
    winName.len = v4;
    gui = window->gui;
    v9 = gui->__vftable;
    v12 = winName.data;
    v14 = 0;
    v10 = v9->GetDesktop(gui);
    ChildByName = idWindow::FindChildByName(v10, v12);
    if ( ChildByName && ChildByName->win )
    {
      idWindow::ClearTransitions(ChildByName->win);
    }
    else if ( gui_debugScript.internalVar->integerValue )
    {
      if ( !ChildByName )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "GUI: %s %s: unknown window for Script_StopTransitions\n",
          window->name.data,
          winName.data);
    }
    v14 = -1;
    idStr::FreeData(&winName);
  }
}

// FUNC: void __cdecl Script_ConsoleCmd(class idWindow *,class idList<struct idGSWinVar> *)
void __cdecl Script_ConsoleCmd(idWindow *window, idList<idGSWinVar> *src)
{
  char *v2; // eax
  int v3; // edx
  char *v4; // eax
  int v5; // esi
  int v6; // eax
  char v7; // cl
  char *v8; // edx
  int v9; // esi
  int v10; // eax
  char v11; // cl
  char *v12; // edx
  idStr val; // [esp+8h] [ebp-2Ch] BYREF
  int v14; // [esp+30h] [ebp-4h]

  v2 = __RTDynamicCast(
         (void **)src->list->var,
         0,
         (TypeDescriptor *)&idWinVar `RTTI Type Descriptor',
         (TypeDescriptor *)&idWinStr `RTTI Type Descriptor',
         0);
  val.len = 0;
  val.alloced = 20;
  val.data = val.baseBuffer;
  val.baseBuffer[0] = 0;
  v3 = *(_DWORD *)v2;
  v14 = 0;
  v4 = (char *)(*(int (__thiscall **)(char *))(v3 + 32))(v2);
  idStr::operator=(&val, v4);
  v5 = val.len + 1;
  if ( val.len + 2 > val.alloced )
    idStr::ReAllocate(&val, val.len + 2, 1);
  v6 = 0;
  v7 = 32;
  do
  {
    v8 = &val.data[v6++];
    v8[val.len] = v7;
    v7 = ::src[v6];
  }
  while ( v7 );
  val.len = v5;
  val.data[v5] = 0;
  v9 = val.len + 1;
  if ( val.len + 2 > val.alloced )
    idStr::ReAllocate(&val, val.len + 2, 1);
  v10 = 0;
  v11 = 10;
  do
  {
    v12 = &val.data[v10++];
    v12[val.len] = v11;
    v11 = pMsg[v10];
  }
  while ( v11 );
  val.len = v9;
  val.data[v9] = 0;
  cmdSystem->BufferCommandText(cmdSystem, CMD_EXEC_APPEND, val.data);
  v14 = -1;
  idStr::FreeData(&val);
}

// FUNC: public: __thiscall idGuiScript::idGuiScript(void)
void __thiscall idGuiScript::idGuiScript(idGuiScript *this)
{
  idGSWinVar *list; // ebp
  int num; // eax
  int v4; // edi
  idGSWinVar *v5; // eax
  idGSWinVar *v6; // ebx
  int v7; // eax
  bool v8; // cc
  idGSWinVar *v9; // ecx

  this->parms.granularity = 16;
  this->parms.list = 0;
  this->parms.num = 0;
  this->parms.size = 0;
  this->ifList = 0;
  this->elseList = 0;
  this->conditionReg = -1;
  this->handler = 0;
  list = this->parms.list;
  this->parms.granularity = 2;
  if ( list )
  {
    num = this->parms.num;
    v4 = num + 1 - (num + 1) % 2;
    if ( v4 != this->parms.size )
    {
      if ( v4 > 0 )
      {
        this->parms.size = v4;
        if ( v4 < num )
          this->parms.num = v4;
        v5 = (idGSWinVar *)Memory::Allocate(8 * v4);
        v6 = v5;
        if ( v5 )
          `vector constructor iterator'(v5, 8u, v4, (void *(__thiscall *)(void *))idGSWinVar::idGSWinVar);
        else
          v6 = 0;
        v7 = 0;
        v8 = this->parms.num <= 0;
        this->parms.list = v6;
        if ( !v8 )
        {
          do
          {
            v9 = this->parms.list;
            v9[v7].var = list[v7].var;
            *(_DWORD *)&v9[v7].own = *(_DWORD *)&list[v7].own;
            ++v7;
          }
          while ( v7 < this->parms.num );
        }
        Memory::Free(list);
      }
      else
      {
        Memory::Free(list);
        this->parms.list = 0;
        this->parms.num = 0;
        this->parms.size = 0;
      }
    }
  }
}

// FUNC: public: __thiscall idGuiScript::~idGuiScript(void)
void __thiscall idGuiScript::~idGuiScript(idGuiScript *this)
{
  idGuiScriptList *ifList; // edi
  idGuiScriptList *elseList; // edi
  int num; // ebp
  int i; // edi
  idGSWinVar *list; // eax
  bool v7; // zf
  idGSWinVar *v8; // eax
  idWinVar *var; // eax
  idGSWinVar *v10; // eax

  ifList = this->ifList;
  if ( ifList )
  {
    idGuiScriptList::~idGuiScriptList(ifList);
    Memory::Free(ifList);
  }
  elseList = this->elseList;
  if ( elseList )
  {
    idGuiScriptList::~idGuiScriptList(this->elseList);
    Memory::Free(elseList);
  }
  num = this->parms.num;
  for ( i = 0; i < num; ++i )
  {
    list = this->parms.list;
    v7 = !list[i].own;
    v8 = &list[i];
    if ( !v7 )
    {
      var = v8->var;
      if ( var )
        ((void (__thiscall *)(idWinVar *, int))var->~idWinVar)(var, 1);
    }
  }
  v10 = this->parms.list;
  if ( v10 )
    Memory::Free(v10);
  this->parms.list = 0;
  this->parms.num = 0;
  this->parms.size = 0;
}

// FUNC: public: bool __thiscall idGuiScript::Parse(class idParser *)
char __thiscall idGuiScript::Parse(idGuiScript *this, idParser *src)
{
  idParser *v3; // edi
  int v5; // ebx
  guiCommandDef_t *v6; // edi
  idWinStr *v7; // eax
  int granularity; // edi
  bool v9; // cc
  idGSWinVar *v10; // eax
  idGSWinVar *v11; // ecx
  int v12; // edx
  int j; // eax
  idGSWinVar *list; // ecx
  int num; // ebx
  int size; // eax
  int v17; // edi
  idGSWinVar *v18; // ebp
  idGSWinVar *v19; // eax
  idGSWinVar *v20; // ecx
  int v21; // edx
  int k; // eax
  idGSWinVar *v23; // ecx
  int v24; // eax
  idGSWinVar *v25; // ecx
  int v26; // esi
  unsigned int v27; // ebx
  int i; // [esp+8h] [ebp-6Ch]
  idWinStr *v29; // [esp+Ch] [ebp-68h]
  int wv_4; // [esp+14h] [ebp-60h]
  idToken token; // [esp+18h] [ebp-5Ch] BYREF
  int v32; // [esp+70h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v3 = src;
  v32 = 0;
  if ( idParser::ReadToken(src, &token) )
  {
    v5 = 0;
    this->handler = 0;
    i = 0;
    if ( scriptCommandCount > 0 )
    {
      v6 = commandList;
      while ( idStr::Icmp(token.data, v6->name) )
      {
        ++v5;
        ++v6;
        if ( v5 >= scriptCommandCount )
          goto LABEL_9;
      }
      this->handler = (void (__cdecl *)(idWindow *, idList<idGSWinVar> *))*(&off_103DE914 + 4 * v5);
LABEL_9:
      v3 = src;
      i = v5;
    }
    if ( !this->handler )
      idParser::Error(v3, "Uknown script call %s", token.data);
    if ( idParser::ReadToken(v3, &token) )
    {
      while ( idStr::Icmp(token.data, ";") )
      {
        if ( !idStr::Icmp(token.data, "}") )
        {
          idParser::UnreadToken(v3, &token);
          break;
        }
        v7 = (idWinStr *)Memory::Allocate(0x30u);
        if ( v7 )
        {
          v7->guiDict = 0;
          v7->name = 0;
          v7->eval = 1;
          v7->__vftable = (idWinStr_vtbl *)&idWinStr::`vftable';
          v7->data.len = 0;
          v7->data.alloced = 20;
          v7->data.data = v7->data.baseBuffer;
          v7->data.baseBuffer[0] = 0;
          v29 = v7;
          idWinStr::operator=(v7, &token);
        }
        else
        {
          v29 = 0;
          idWinStr::operator=(0, &token);
        }
        LOBYTE(wv_4) = 1;
        if ( !this->parms.list )
        {
          granularity = this->parms.granularity;
          if ( granularity > 0 )
          {
            if ( granularity != this->parms.size )
            {
              v9 = granularity < this->parms.num;
              this->parms.size = granularity;
              if ( v9 )
                this->parms.num = granularity;
              v10 = (idGSWinVar *)Memory::Allocate(8 * granularity);
              if ( v10 )
              {
                v11 = v10;
                if ( granularity - 1 >= 0 )
                {
                  v12 = granularity;
                  do
                  {
                    v11->var = 0;
                    v11->own = 0;
                    ++v11;
                    --v12;
                  }
                  while ( v12 );
                }
              }
              else
              {
                v10 = 0;
              }
              this->parms.list = v10;
              for ( j = 0; j < this->parms.num; ++j )
              {
                list = this->parms.list;
                list[j].var = *(idWinVar **)(8 * j);
                *(_DWORD *)&list[j].own = *(_DWORD *)(8 * j + 4);
              }
            }
          }
          else
          {
            this->parms.list = 0;
            this->parms.num = 0;
            this->parms.size = 0;
          }
        }
        num = this->parms.num;
        size = this->parms.size;
        if ( num == size )
        {
          if ( !this->parms.granularity )
            this->parms.granularity = 16;
          v17 = size + this->parms.granularity - (size + this->parms.granularity) % this->parms.granularity;
          if ( v17 > 0 )
          {
            if ( v17 != this->parms.size )
            {
              v18 = this->parms.list;
              this->parms.size = v17;
              if ( v17 < num )
                this->parms.num = v17;
              v19 = (idGSWinVar *)Memory::Allocate(8 * v17);
              if ( v19 )
              {
                v20 = v19;
                if ( v17 - 1 >= 0 )
                {
                  v21 = v17;
                  do
                  {
                    v20->var = 0;
                    v20->own = 0;
                    ++v20;
                    --v21;
                  }
                  while ( v21 );
                }
              }
              else
              {
                v19 = 0;
              }
              this->parms.list = v19;
              for ( k = 0; k < this->parms.num; ++k )
              {
                v23 = this->parms.list;
                v23[k].var = v18[k].var;
                *(_DWORD *)&v23[k].own = *(_DWORD *)&v18[k].own;
              }
              if ( v18 )
                Memory::Free(v18);
            }
          }
          else
          {
            if ( this->parms.list )
              Memory::Free(this->parms.list);
            this->parms.list = 0;
            this->parms.num = 0;
            this->parms.size = 0;
          }
        }
        v24 = this->parms.num;
        v25 = this->parms.list;
        v25[v24].var = v29;
        *(_DWORD *)&v25[v24].own = wv_4;
        ++this->parms.num;
        v3 = src;
        if ( !idParser::ReadToken(src, &token) )
          goto LABEL_55;
        v5 = i;
      }
      if ( this->handler )
      {
        v26 = this->parms.num;
        v27 = 4 * v5;
        if ( v26 < dword_103DE918[v27] || v26 > dword_103DE91C[v27] )
          idParser::Error(v3, "incorrect number of parameters for script %s", commandList[v27 / 4].name);
      }
      v32 = -1;
      idStr::FreeData(&token);
      return 1;
    }
    else
    {
LABEL_55:
      idParser::Error(v3, "Unexpected end of file");
      v32 = -1;
      idStr::FreeData(&token);
      return 0;
    }
  }
  else
  {
    idParser::Error(src, "Unexpected end of file");
    v32 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: void __thiscall idGuiScript::FixupParms(class idWindow *)
void __thiscall idGuiScript::FixupParms(idGuiScript *this, idWindow *win)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void (__cdecl *handler)(idWindow *, idList<idGSWinVar> *); // eax
  const char **v5; // ebx
  idWinVar *v6; // edi
  idWinVar *v7; // ecx
  const char *v8; // eax
  int v9; // ebx
  idWinStr *v10; // edi
  idWinVar *v11; // eax
  idWinVar *v12; // ebx
  int num; // edx
  int v14; // eax
  idWinVar **list; // ecx
  int granularity; // eax
  int j; // eax
  int v18; // ebx
  int size; // ecx
  int v20; // ecx
  idWinVar **v21; // edi
  int k; // eax
  idWinVar *v23; // ecx
  idWindow *v24; // eax
  idWinVar *v25; // edi
  idWinVar *v26; // ecx
  const char *v27; // eax
  int v28; // ebx
  int v29; // eax
  int v30; // eax
  int v31; // eax
  const char *v32; // eax
  const char **v33; // edi
  idWinVar *v34; // esi
  char *v35; // esi
  int v36; // eax
  idWinVar *v37; // ecx
  idWinStr *v38; // edi
  char *v39; // eax
  idWinVar *v40; // eax
  idWinVar *v41; // edi
  idSimpleWindow *simp; // eax
  idWindow *mParent; // esi
  idSimpleWindow *v44; // eax
  idWinVar *v45; // eax
  idWinVar *v46; // esi
  int v47; // eax
  void (__thiscall ***v48)(void *, int); // edi
  idWinVar *v49; // eax
  char *v50; // esi
  int v51; // edi
  int v52; // eax
  int i; // esi
  void (__thiscall ***v54)(void *, int); // edi
  idWinVar *v55; // eax
  idWinVar *v56; // ecx
  const char **v57; // esi
  idWinVar *v58; // ebx
  idWinVar *var; // ecx
  char *data; // ebx
  char *v61; // edi
  int v62; // ebp
  int v63; // eax
  int v64; // edi
  idWinVar *v65; // esi
  idWinVar_vtbl *v66; // ebx
  int v67; // eax
  int v68; // [esp+8h] [ebp-160h]
  int c; // [esp+20h] [ebp-148h]
  int ca; // [esp+20h] [ebp-148h]
  __int16 v71; // [esp+26h] [ebp-142h]
  idWinVar *desta; // [esp+28h] [ebp-140h]
  idWinVar *dest; // [esp+28h] [ebp-140h]
  char *destb; // [esp+28h] [ebp-140h]
  char *destc; // [esp+28h] [ebp-140h]
  int parmCount; // [esp+2Ch] [ebp-13Ch]
  int parmCountb; // [esp+2Ch] [ebp-13Ch]
  idWindow *parmCounta; // [esp+2Ch] [ebp-13Ch]
  int parmCountc; // [esp+2Ch] [ebp-13Ch]
  idWinStr *str; // [esp+30h] [ebp-138h]
  idWinStr *stra; // [esp+30h] [ebp-138h]
  drawWin_t *parmOwner; // [esp+34h] [ebp-134h] BYREF
  idRectangle rect; // [esp+38h] [ebp-130h] BYREF
  drawWin_t *destOwner; // [esp+48h] [ebp-120h] BYREF
  idToken token; // [esp+4Ch] [ebp-11Ch] BYREF
  idParser parser; // [esp+9Ch] [ebp-CCh] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v87; // [esp+15Ch] [ebp-Ch]
  void *v88; // [esp+160h] [ebp-8h]
  int v89; // [esp+164h] [ebp-4h]

  v89 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v88 = &_ehhandler__FixupParms_idGuiScript__QAEXPAVidWindow___Z;
  v87 = ExceptionList;
  handler = this->handler;
  if ( handler != Script_Set )
  {
    if ( handler != Script_Transition )
    {
      if ( handler == Script_SetLightColor )
      {
        v57 = (const char **)__RTDynamicCast(
                               this->parms.list->var,
                               0,
                               &idWinVar `RTTI Type Descriptor',
                               &idWinStr `RTTI Type Descriptor',
                               0);
        v58 = win->GetWinVarByName(win, v57[5], 1, 0);
        if ( v58 )
        {
          var = this->parms.list->var;
          if ( var )
            ((void (__thiscall *)(idWinVar *, int))var->~idWinVar)(var, 1);
          this->parms.list->var = v58;
          this->parms.list->own = 0;
        }
        else
        {
          data = win->gui->source.data;
          v61 = win->name.data;
          v62 = *(_DWORD *)common.type;
          v63 = (*((int (__thiscall **)(const char **))*v57 + 8))(v57);
          (*(void (**)(netadrtype_t, const char *, ...))(v62 + 136))(
            common.type,
            "Window %s in gui %s: setLightColor command does not specify a valid var %s",
            v61,
            data,
            v63);
        }
      }
      else
      {
        v64 = 0;
        parmOwner = (drawWin_t *)this->parms.num;
        if ( (int)parmOwner > 0 )
        {
          do
          {
            v65 = this->parms.list[v64].var;
            v66 = v65->__vftable;
            v67 = ((int (__thiscall *)(idWinVar *, idWindow *))v65->c_str)(v65, win);
            ((void (__thiscall *)(idWinVar *, int))v66->Init)(v65, v67);
            ++v64;
          }
          while ( v64 < (int)parmOwner );
        }
      }
      return;
    }
    if ( this->parms.num < 4 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "Window %s in gui %s has a bad transition definition",
        win->name.data,
        win->gui->source.data);
      this->handler = 0;
      return;
    }
    v33 = (const char **)__RTDynamicCast(
                           this->parms.list->var,
                           0,
                           &idWinVar `RTTI Type Descriptor',
                           &idWinStr `RTTI Type Descriptor',
                           0);
    v34 = win->GetWinVarByName(win, v33[5], 1, &destOwner);
    dest = v34;
    if ( !__RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinVec4 `RTTI Type Descriptor', 0)
      && !__RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinFloat `RTTI Type Descriptor', 0)
      && !__RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinRectangle `RTTI Type Descriptor', 0)
      && !__RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinFloatMember `RTTI Type Descriptor', 0) )
    {
      v35 = win->gui->source.data;
      destb = win->name.data;
      parmCountb = *(_DWORD *)common.type;
      v36 = (*((int (__thiscall **)(const char **))*v33 + 8))(v33);
      (*(void (**)(netadrtype_t, const char *, ...))(parmCountb + 136))(
        common.type,
        "Window %s in gui %s: a transition does not have a valid destination var %s",
        destb,
        v35,
        v36);
      this->handler = 0;
      return;
    }
    v37 = this->parms.list->var;
    if ( v37 )
      ((void (__thiscall *)(idWinVar *, int))v37->~idWinVar)(v37, 1);
    this->parms.list->var = v34;
    this->parms.list->own = 0;
    ca = 1;
    while ( 1 )
    {
      v38 = (idWinStr *)__RTDynamicCast(
                          this->parms.list[ca].var,
                          0,
                          &idWinVar `RTTI Type Descriptor',
                          &idWinStr `RTTI Type Descriptor',
                          0);
      v39 = v38->data.data;
      stra = v38;
      if ( *v39 == 36 )
      {
        v41 = win->GetWinVarByName(win, v39 + 1, 1, &parmOwner);
        if ( (!__RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinVec4 `RTTI Type Descriptor', 0)
           || !__RTDynamicCast(v41, 0, &idWinVar `RTTI Type Descriptor', &idWinVec4 `RTTI Type Descriptor', 0))
          && (!__RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinFloat `RTTI Type Descriptor', 0)
           || !__RTDynamicCast(v41, 0, &idWinVar `RTTI Type Descriptor', &idWinFloat `RTTI Type Descriptor', 0))
          && (!__RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinRectangle `RTTI Type Descriptor', 0)
           || !__RTDynamicCast(v41, 0, &idWinVar `RTTI Type Descriptor', &idWinVec4 `RTTI Type Descriptor', 0)
           && !__RTDynamicCast(v41, 0, &idWinVar `RTTI Type Descriptor', &idWinRectangle `RTTI Type Descriptor', 0))
          && (!__RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinFloatMember `RTTI Type Descriptor', 0)
           || !__RTDynamicCast(v41, 0, &idWinVar `RTTI Type Descriptor', &idWinFloat `RTTI Type Descriptor', 0)
           && !__RTDynamicCast(v41, 0, &idWinVar `RTTI Type Descriptor', &idWinFloatMember `RTTI Type Descriptor', 0)) )
        {
          v50 = win->gui->source.data;
          v51 = *(_DWORD *)common.type;
          destc = win->name.data;
          v52 = (int)stra->c_str(stra);
          (*(void (**)(netadrtype_t, const char *, ...))(v51 + 136))(
            common.type,
            "Window %s in gui %s: transition has an invalid parameter %d (%s)",
            destc,
            v50,
            ca,
            v52);
          this->handler = 0;
          return;
        }
        if ( __RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinRectangle `RTTI Type Descriptor', 0)
          && __RTDynamicCast(v41, 0, &idWinVar `RTTI Type Descriptor', &idWinRectangle `RTTI Type Descriptor', 0) )
        {
          simp = destOwner->simp;
          if ( simp )
            mParent = simp->mParent;
          else
            mParent = destOwner->win->parent;
          v44 = parmOwner->simp;
          if ( v44 )
            parmCounta = v44->mParent;
          else
            parmCounta = parmOwner->win->parent;
          v45 = (idWinVar *)Memory::Allocate(0x20u);
          if ( v45 )
          {
            v45->guiDict = 0;
            v45->name = 0;
            v45->eval = 1;
            v45->__vftable = (idWinVar_vtbl *)&idWinVec4::`vftable';
          }
          else
          {
            v45 = 0;
          }
          this->parms.list[ca].var = v45;
          this->parms.list[ca].own = 1;
          if ( mParent && parmCounta )
          {
            memset(&rect, 0, sizeof(rect));
            rect = (idRectangle)*((_OWORD *)__RTDynamicCast(
                                              v41,
                                              0,
                                              &idWinVar `RTTI Type Descriptor',
                                              &idWinRectangle `RTTI Type Descriptor',
                                              0)
                                + 1);
            idWindow::ClientToScreen(parmCounta, &rect);
            idWindow::ScreenToClient(mParent, &rect);
            idWinRectangle::operator=((idWinRectangle *)this->parms.list[ca].var, (idVec4 *)&rect);
            v34 = dest;
          }
          else
          {
            v46 = this->parms.list[ca].var;
            parmCountc = (int)v46->__vftable;
            v47 = (int)v41->c_str(v41);
            (*(void (__thiscall **)(idWinVar *, int))(parmCountc + 16))(v46, v47);
            v34 = dest;
          }
        }
        else
        {
          this->parms.list[ca].var = v41;
          this->parms.list[ca].own = 0;
        }
        v38 = stra;
        goto LABEL_113;
      }
      if ( __RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinVec4 `RTTI Type Descriptor', 0)
        || __RTDynamicCast(v34, 0, &idWinVar `RTTI Type Descriptor', &idWinRectangle `RTTI Type Descriptor', 0) )
      {
        v40 = (idWinVar *)Memory::Allocate(0x20u);
        if ( !v40 )
        {
LABEL_84:
          v40 = 0;
          goto LABEL_85;
        }
        v40->guiDict = 0;
        v40->name = 0;
        v40->eval = 1;
        v40->__vftable = (idWinVar_vtbl *)&idWinVec4::`vftable';
      }
      else
      {
        v40 = (idWinVar *)Memory::Allocate(0x14u);
        if ( !v40 )
          goto LABEL_84;
        v40->guiDict = 0;
        v40->name = 0;
        v40->eval = 1;
        v40->__vftable = (idWinVar_vtbl *)&idWinFloat::`vftable';
      }
LABEL_85:
      this->parms.list[ca].var = v40;
      this->parms.list[ca].own = 1;
      v40->Set(v40, v38->data.data);
LABEL_113:
      ((void (__thiscall *)(idWinStr *, int))v38->~idWinStr)(v38, 1);
      if ( ++ca >= 3 )
      {
        v48 = (void (__thiscall ***)(void *, int))__RTDynamicCast(
                                                    this->parms.list[3].var,
                                                    0,
                                                    &idWinVar `RTTI Type Descriptor',
                                                    &idWinStr `RTTI Type Descriptor',
                                                    0);
        v49 = (idWinVar *)Memory::Allocate(0x14u);
        if ( v49 )
        {
          v49->guiDict = 0;
          v49->name = 0;
          v49->eval = 1;
          v49->__vftable = (idWinVar_vtbl *)&idWinInt::`vftable';
        }
        else
        {
          v49 = 0;
        }
        this->parms.list[3].var = v49;
        this->parms.list[3].own = 1;
        this->parms.list[3].var->Set(this->parms.list[3].var, (const char *)v48[5]);
        (**v48)(v48, 1);
        for ( i = 4; i < this->parms.num; ++i )
        {
          if ( i >= 6 )
            break;
          v54 = (void (__thiscall ***)(void *, int))__RTDynamicCast(
                                                      this->parms.list[i].var,
                                                      0,
                                                      &idWinVar `RTTI Type Descriptor',
                                                      &idWinStr `RTTI Type Descriptor',
                                                      0);
          v55 = (idWinVar *)Memory::Allocate(0x14u);
          if ( v55 )
          {
            v55->guiDict = 0;
            v55->name = 0;
            v55->eval = 1;
            v55->__vftable = (idWinVar_vtbl *)&idWinFloat::`vftable';
          }
          else
          {
            v55 = 0;
          }
          this->parms.list[i].var = v55;
          this->parms.list[3].own = 1;
          v56 = this->parms.list[i].var;
          v56->Set(v56, (const char *)v54[5]);
          (**v54)(v54, 1);
        }
        return;
      }
    }
  }
  v71 = 0;
  v5 = (const char **)__RTDynamicCast(
                        this->parms.list->var,
                        0,
                        &idWinVar `RTTI Type Descriptor',
                        &idWinStr `RTTI Type Descriptor',
                        0);
  v6 = win->GetWinVarByName(win, v5[5], 1, 0);
  if ( v6 )
  {
    v7 = this->parms.list->var;
    if ( v7 )
      ((void (__thiscall *)(idWinVar *, int))v7->~idWinVar)(v7, 1);
    this->parms.list->var = v6;
    this->parms.list->own = 0;
    if ( __RTDynamicCast(v6, 0, &idWinVar `RTTI Type Descriptor', &idWinBackground `RTTI Type Descriptor', 0) )
      HIBYTE(v71) = 1;
  }
  else
  {
    v8 = (const char *)(*((int (__thiscall **)(const char **))*v5 + 8))(v5);
    if ( !idStr::Icmp(v8, "cmd") )
      LOBYTE(v71) = 1;
  }
  v9 = 1;
  parmCount = this->parms.num;
  c = 1;
  if ( parmCount > 1 )
  {
    do
    {
      v10 = (idWinStr *)__RTDynamicCast(
                          this->parms.list[v9].var,
                          0,
                          &idWinVar `RTTI Type Descriptor',
                          &idWinStr `RTTI Type Descriptor',
                          0);
      if ( idStr::Icmpn(v10->data.data, "$gui::", 6) )
      {
        if ( *v10->data.data == 36 )
        {
          v24 = win->gui->GetDesktop(win->gui);
          v25 = v24->GetWinVarByName(v24, (const char *)v10->data.data + 1, 1, 0);
          if ( v25 )
          {
            v26 = this->parms.list[v9].var;
            if ( v26 )
              ((void (__thiscall *)(idWinVar *, int))v26->~idWinVar)(v26, 1);
            this->parms.list[v9].var = v25;
            this->parms.list[v9].own = 0;
          }
        }
        else
        {
          v27 = v10->c_str(v10);
          if ( idStr::Cmpn(v27, "#str_", 5) )
          {
            if ( HIBYTE(v71) )
            {
              v31 = ((int (__thiscall *)(idWinStr *, int))v10->c_str)(v10, 1);
              *(_DWORD *)((*(int (__thiscall **)(idDeclManager *, int))(parmCount + 136))(declManager, v31) + 184) = -1073741824;
            }
            else if ( (_BYTE)v71 )
            {
              token.floatvalue = 0.0;
              token.len = 0;
              token.alloced = 20;
              token.data = token.baseBuffer;
              token.baseBuffer[0] = 0;
              v89 = 0;
              idParser::idParser(&parser, 6152);
              LOBYTE(v89) = 1;
              v68 = idWinStr::Length(v10);
              v32 = v10->c_str(v10);
              idParser::LoadMemory(&parser, v32, v68, "command");
              while ( idParser::ReadToken(&parser, &token) )
              {
                if ( (!idStr::Icmp(token.data, "play") || !idStr::Icmp(token.data, "music"))
                  && idParser::ReadToken(&parser, &token)
                  && idStr::Cmp(token.data, &entityFilter) )
                {
                  declManager->FindSound(declManager, token.data, 1);
                }
              }
              LOBYTE(v89) = 0;
              idParser::~idParser(&parser);
              v89 = -1;
              idStr::FreeData(&token);
            }
          }
          else
          {
            v28 = *(_DWORD *)common.type;
            desta = (idWinVar *)v10->__vftable;
            v29 = ((int (__thiscall *)(idWinStr *, int))v10->c_str)(v10, -1);
            v30 = (*(int (__thiscall **)(netadrtype_t, int))(v28 + 168))(common.type, v29);
            ((void (__thiscall *)(idWinStr *, int))desta[1].__vftable)(v10, v30);
            v9 = c;
          }
        }
      }
      else
      {
        v11 = (idWinVar *)Memory::Allocate(0x30u);
        if ( v11 )
        {
          v11->guiDict = 0;
          v11->name = 0;
          v11->eval = 1;
          v11->__vftable = (idWinVar_vtbl *)&idWinStr::`vftable';
          v11[1].__vftable = 0;
          v11[1].name = (char *)20;
          v11[1].guiDict = (idDict *)&v11[1].eval;
          v11[1].eval = 0;
          v12 = v11;
        }
        else
        {
          v12 = 0;
        }
        str = (idWinStr *)v12;
        v12->Init(v12, (const char *)v10->data.data + 1, win);
        num = win->definedVars.num;
        v14 = 0;
        if ( num <= 0 )
          goto LABEL_20;
        list = win->definedVars.list;
        while ( *list != v12 )
        {
          ++v14;
          ++list;
          if ( v14 >= win->definedVars.num )
            goto LABEL_20;
        }
        if ( v14 < 0 )
        {
LABEL_20:
          if ( !win->definedVars.list )
          {
            granularity = win->definedVars.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != win->definedVars.size )
              {
                win->definedVars.size = granularity;
                if ( granularity < num )
                  win->definedVars.num = granularity;
                win->definedVars.list = (idWinVar **)Memory::Allocate(4 * granularity);
                for ( j = 0; j < win->definedVars.num; ++j )
                  win->definedVars.list[j] = *(idWinVar **)(4 * j);
              }
            }
            else
            {
              win->definedVars.list = 0;
              win->definedVars.num = 0;
              win->definedVars.size = 0;
            }
          }
          v18 = win->definedVars.num;
          size = win->definedVars.size;
          if ( v18 == size )
          {
            if ( !win->definedVars.granularity )
              win->definedVars.granularity = 16;
            v20 = win->definedVars.granularity
                + size
                - (win->definedVars.granularity + size) % win->definedVars.granularity;
            if ( v20 > 0 )
            {
              if ( v20 != win->definedVars.size )
              {
                v21 = win->definedVars.list;
                win->definedVars.size = v20;
                if ( v20 < v18 )
                  win->definedVars.num = v20;
                win->definedVars.list = (idWinVar **)Memory::Allocate(4 * v20);
                for ( k = 0; k < win->definedVars.num; ++k )
                  win->definedVars.list[k] = v21[k];
                if ( v21 )
                  Memory::Free(v21);
              }
            }
            else
            {
              if ( win->definedVars.list )
                Memory::Free(win->definedVars.list);
              win->definedVars.list = 0;
              win->definedVars.num = 0;
              win->definedVars.size = 0;
            }
          }
          win->definedVars.list[win->definedVars.num++] = str;
          v12 = str;
        }
        v23 = this->parms.list[c].var;
        if ( v23 )
          ((void (__thiscall *)(idWinVar *, int))v23->~idWinVar)(v23, 1);
        this->parms.list[c].var = v12;
        v9 = c;
        this->parms.list[c].own = 0;
      }
      c = ++v9;
    }
    while ( v9 < parmCount );
  }
}

// FUNC: public: void __thiscall idGuiScriptList::FixupParms(class idWindow *)
void __thiscall idGuiScriptList::FixupParms(idGuiScriptList *this, idWindow *win)
{
  int v3; // edi
  idGuiScript *v4; // esi
  idGuiScriptList *ifList; // ecx
  idGuiScriptList *elseList; // ecx
  int c; // [esp+8h] [ebp-4h]

  v3 = 0;
  for ( c = this->list.num; v3 < c; ++v3 )
  {
    v4 = this->list.list[v3];
    idGuiScript::FixupParms(v4, win);
    ifList = v4->ifList;
    if ( ifList )
      idGuiScriptList::FixupParms(ifList, win);
    elseList = v4->elseList;
    if ( elseList )
      idGuiScriptList::FixupParms(elseList, win);
  }
}
