
// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::Init(void)
void __thiscall idUserInterfaceManagerLocal::Init(idUserInterfaceManagerLocal *this)
{
  this->screenRect.x = 0.0;
  this->screenRect.y = 0.0;
  this->screenRect.w = 640.0;
  this->screenRect.h = 480.0;
  idDeviceContext::Init(&this->dc);
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::Touch(char const *)
void __thiscall idUserInterfaceManagerLocal::Touch(idUserInterfaceManagerLocal *this, const char *name)
{
  idUserInterface *v2; // eax

  v2 = this->Alloc(this);
  v2->InitFromFile(v2, name, 1, 1);
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::SetSize(float,float)
void __thiscall idUserInterfaceManagerLocal::SetSize(idUserInterfaceManagerLocal *this, float width, float height)
{
  idDeviceContext::SetSize(&this->dc, width, height);
}

// FUNC: public: virtual bool __thiscall idUserInterfaceManagerLocal::CheckGui(char const *)const
char __thiscall idUserInterfaceManagerLocal::CheckGui(idUserInterfaceManagerLocal *this, const char *qpath)
{
  idFile *v2; // eax

  v2 = fileSystem->OpenFileRead(fileSystem, qpath, 1, 0);
  if ( !v2 )
    return 0;
  fileSystem->CloseFile(fileSystem, v2);
  return 1;
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::RegisterIcon(char const *,char const *,int,int,int,int)
void __thiscall idUserInterfaceManagerLocal::RegisterIcon(
        idUserInterfaceManagerLocal *this,
        const char *code,
        const char *shader,
        int x,
        int y,
        int w,
        int h)
{
  idDeviceContext::RegisterIcon(&this->dc, code, shader, x, y, w, h);
}

// FUNC: public: virtual bool __thiscall idUserInterfaceLocal::IsInteractive(void)const
bool __thiscall idUserInterfaceLocal::IsInteractive(idUserInterfaceLocal *this)
{
  return this->interactive;
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::SetInteractive(bool)
void __thiscall idUserInterfaceLocal::SetInteractive(idUserInterfaceLocal *this, bool _interactive)
{
  this->interactive = _interactive;
}

// FUNC: public: virtual char const * __thiscall idUserInterfaceLocal::HandleEvent(struct sysEvent_s const *,int,bool *)
const char *__thiscall idUserInterfaceLocal::HandleEvent(
        idUserInterfaceLocal *this,
        const sysEvent_s *event,
        int _time,
        bool *updateVisuals)
{
  idWindow *bindHandler; // ecx
  const char *result; // eax
  double v7; // st7
  double v8; // st7
  idWindow *desktop; // ecx

  bindHandler = this->bindHandler;
  this->time = _time;
  if ( bindHandler && event->evType == SE_KEY && event->evValue2 == 1 )
  {
    result = bindHandler->HandleEvent(bindHandler, event, updateVisuals);
    this->bindHandler = 0;
  }
  else
  {
    if ( event->evType == SE_JOYSTICK_AXIS )
    {
      if ( !event->evValue )
      {
        v7 = (double)(*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type)
           * 0.001
           * 210.0
           * (double)event->evValue2
           * 0.0078740157
           + this->cursorX;
        this->cursorX = v7;
        if ( v7 < 0.0 )
          this->cursorX = 0.0;
      }
      if ( event->evValue == 1 )
      {
        v8 = (double)(*(int (__thiscall **)(netadrtype_t))(*(_DWORD *)common.type + 40))(common.type)
           * 0.001
           * 210.0
           * (double)event->evValue2
           * 0.0078740157
           + this->cursorY;
        this->cursorY = v8;
        if ( v8 < 0.0 )
          this->cursorY = 0.0;
      }
    }
    if ( event->evType == SE_MOUSE )
    {
      this->cursorX = (double)event->evValue + this->cursorX;
      this->cursorY = (double)event->evValue2 + this->cursorY;
      if ( this->cursorX < 0.0 )
        this->cursorX = 0.0;
      if ( this->cursorY < 0.0 )
        this->cursorY = 0.0;
    }
    desktop = this->desktop;
    if ( desktop )
      return desktop->HandleEvent(desktop, event, updateVisuals);
    else
      return &entityFilter;
  }
  return result;
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::HandleNamedEvent(char const *)
void __thiscall idUserInterfaceLocal::HandleNamedEvent(idUserInterfaceLocal *this, const char *eventName)
{
  this->desktop->RunNamedEvent(this->desktop, eventName);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::DrawCursor(void)
void __thiscall idUserInterfaceLocal::DrawCursor(idUserInterfaceLocal *this)
{
  idWindow *desktop; // eax

  desktop = this->desktop;
  if ( !desktop || (desktop->flags & 0x100000) != 0 )
    idDeviceContext::DrawCursor(&uiManagerLocal.dc, &this->cursorX, &this->cursorY, 32.0);
  else
    idDeviceContext::DrawCursor(&uiManagerLocal.dc, &this->cursorX, &this->cursorY, 64.0);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::DeleteState(char const *)
void __thiscall idUserInterfaceLocal::DeleteState(idUserInterfaceLocal *this, const char *varName)
{
  idDict::Delete(&this->state, varName);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::SetStateString(char const *,char const *)
void __thiscall idUserInterfaceLocal::SetStateString(
        idUserInterfaceLocal *this,
        const char *varName,
        const char *value)
{
  idDict::Set(&this->state, varName, value);
}

// FUNC: public: virtual void __thiscall idDeclEntityDef::FreeData(void)
void __thiscall idDeclEntityDef::FreeData(idDeclEntityDef *this)
{
  idDict::Clear(&this->dict);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::Trigger(int)
void __thiscall idUserInterfaceLocal::Trigger(idUserInterfaceLocal *this, int _time)
{
  idWindow *desktop; // ecx

  this->time = _time;
  desktop = this->desktop;
  if ( desktop )
    desktop->Trigger(desktop);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::SetCursor(float,float)
void __thiscall idUserInterfaceLocal::SetCursor(idUserInterfaceLocal *this, float x, float y)
{
  this->cursorX = x;
  this->cursorY = y;
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::Shutdown(void)
void __thiscall idUserInterfaceManagerLocal::Shutdown(idUserInterfaceManagerLocal *this)
{
  int i; // edi
  idUserInterfaceLocal *v3; // ecx
  int j; // edi
  idUserInterfaceLocal *v5; // ecx

  for ( i = 0; i < this->guis.num; ++i )
  {
    v3 = this->guis.list[i];
    if ( v3 )
      ((void (__thiscall *)(idUserInterfaceLocal *, int))v3->~idUserInterface)(v3, 1);
    this->guis.list[i] = 0;
  }
  if ( this->guis.list )
    Memory::Free(this->guis.list);
  this->guis.list = 0;
  this->guis.num = 0;
  this->guis.size = 0;
  if ( this->alwaysThinkGUIs.list )
    Memory::Free(this->alwaysThinkGUIs.list);
  this->alwaysThinkGUIs.list = 0;
  this->alwaysThinkGUIs.num = 0;
  this->alwaysThinkGUIs.size = 0;
  for ( j = 0; j < this->demoGuis.num; ++j )
  {
    v5 = this->demoGuis.list[j];
    if ( v5 )
      ((void (__thiscall *)(idUserInterfaceLocal *, int))v5->~idUserInterface)(v5, 1);
    this->demoGuis.list[j] = 0;
  }
  if ( this->demoGuis.list )
    Memory::Free(this->demoGuis.list);
  this->demoGuis.list = 0;
  this->demoGuis.num = 0;
  this->demoGuis.size = 0;
  idDeviceContext::Shutdown(&this->dc);
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::WritePrecacheCommands(class idFile *)
void __thiscall idUserInterfaceManagerLocal::WritePrecacheCommands(idUserInterfaceManagerLocal *this, idFile *f)
{
  int num; // ebp
  int i; // esi
  idUserInterfaceLocal *v5; // ecx
  const char *v6; // eax
  char str[1024]; // [esp+Ch] [ebp-400h] BYREF

  num = this->guis.num;
  for ( i = 0; i < num; ++i )
  {
    v5 = this->guis.list[i];
    v6 = v5->Name(v5);
    sprintf(str, "touchGui %s\n", v6);
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s", str);
    f->Printf(f, "%s", str);
  }
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::BeginLevelLoad(void)
void __thiscall idUserInterfaceManagerLocal::BeginLevelLoad(idUserInterfaceManagerLocal *this)
{
  int num; // ebx
  int i; // esi
  idUserInterfaceLocal *v4; // ecx

  num = this->guis.num;
  for ( i = 0; i < num; ++i )
  {
    v4 = this->guis.list[i];
    if ( (v4->GetDesktop(v4)->flags & 0x100000) == 0 )
      this->guis.list[i]->refs = 0;
  }
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::Reload(bool)
void __thiscall idUserInterfaceManagerLocal::Reload(idUserInterfaceManagerLocal *this, unsigned int all)
{
  int num; // ebp
  int v4; // esi
  char v5; // bl
  idUserInterfaceLocal *v6; // ecx
  idUserInterfaceLocal *v7; // ecx

  num = this->guis.num;
  v4 = 0;
  if ( num > 0 )
  {
    v5 = all;
    do
    {
      if ( v5
        || (fileSystem->ReadFile(fileSystem, this->guis.list[v4]->source.data, 0, &all),
            all > this->guis.list[v4]->timeStamp) )
      {
        v6 = this->guis.list[v4];
        v6->InitFromFile(v6, v6->source.data, 1, 1);
        v7 = this->guis.list[v4];
        v7->StateChanged(v7, v7->time, 1);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
          common.type,
          "reloading %s.\n",
          this->guis.list[v4]->source.data);
      }
      ++v4;
    }
    while ( v4 < num );
  }
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::DeAlloc(class idUserInterface *)
void __thiscall idUserInterfaceManagerLocal::DeAlloc(idUserInterfaceManagerLocal *this, idUserInterfaceLocal *gui)
{
  int num; // ecx
  int v4; // edi
  idUserInterfaceLocal **i; // eax
  idUserInterfaceLocal *v6; // ecx
  int v7; // eax
  bool v8; // cc
  int v9; // eax
  idUserInterfaceLocal **list; // ecx
  idUserInterfaceLocal *v11; // edx
  idUserInterfaceLocal **v12; // ecx
  int v13; // edx
  int v14; // eax
  idUserInterfaceLocal **j; // ecx
  int v16; // ecx
  int v17; // ecx
  idUserInterfaceLocal **v18; // ecx
  idUserInterfaceLocal *v19; // edx
  idUserInterfaceLocal **v20; // ecx

  if ( gui )
  {
    num = this->guis.num;
    v4 = 0;
    if ( num > 0 )
    {
      for ( i = this->guis.list; *i != gui; ++i )
      {
        if ( ++v4 >= num )
          return;
      }
      v6 = this->guis.list[v4];
      if ( v6 )
        ((void (__thiscall *)(idUserInterfaceLocal *, int))v6->~idUserInterface)(v6, 1);
      if ( v4 >= 0 )
      {
        v7 = this->guis.num;
        if ( v4 < v7 )
        {
          v8 = v4 < v7 - 1;
          this->guis.num = v7 - 1;
          v9 = v4;
          if ( v8 )
          {
            do
            {
              list = this->guis.list;
              v11 = list[v9 + 1];
              v12 = &list[v9++];
              *v12 = v11;
            }
            while ( v9 < this->guis.num );
          }
        }
      }
      v13 = this->alwaysThinkGUIs.num;
      v14 = 0;
      if ( v13 > 0 )
      {
        for ( j = this->alwaysThinkGUIs.list; *j != gui; ++j )
        {
          if ( ++v14 >= v13 )
            return;
        }
        if ( v14 >= 0 )
        {
          v16 = this->alwaysThinkGUIs.num;
          if ( v14 < v16 )
          {
            v17 = v16 - 1;
            for ( this->alwaysThinkGUIs.num = v17; v14 < this->alwaysThinkGUIs.num; *v20 = v19 )
            {
              v18 = this->alwaysThinkGUIs.list;
              v19 = v18[v14 + 1];
              v20 = &v18[v14++];
            }
          }
        }
      }
    }
  }
}

// FUNC: public: virtual class idUserInterface * __thiscall idUserInterfaceManagerLocal::FindGui(char const *,bool,bool,bool)
idUserInterfaceLocal *__thiscall idUserInterfaceManagerLocal::FindGui(
        idUserInterfaceManagerLocal *this,
        const char *qpath,
        bool autoLoad,
        int needUnique,
        bool forceNOTUnique)
{
  int num; // ebx
  int v7; // edi
  idUserInterfaceLocal *v8; // ebp
  idUserInterfaceLocal *v9; // ecx
  idUserInterfaceLocal *v10; // ecx
  idUserInterface *v11; // esi
  int v12; // eax
  idUserInterface_vtbl *v13; // edx

  num = this->guis.num;
  v7 = 0;
  if ( num <= 0 )
  {
LABEL_8:
    if ( autoLoad )
    {
      v11 = this->Alloc(this);
      v12 = ((int (__thiscall *)(idUserInterface *, const char *, int, int))v11->InitFromFile)(v11, qpath, 1, 1);
      v13 = v11->__vftable;
      if ( (_BYTE)v12 )
      {
        LOBYTE(v12) = forceNOTUnique - 1;
        v13->SetUniqued(v11, needUnique & v12);
        return (idUserInterfaceLocal *)v11;
      }
      ((void (__thiscall *)(idUserInterface *, int))v13->~idUserInterface)(v11, 1);
    }
    return 0;
  }
  else
  {
    while ( 1 )
    {
      v8 = this->guis.list[v7];
      if ( !idStr::Icmp(v8->source.data, qpath) )
      {
        if ( forceNOTUnique )
          break;
        if ( !(_BYTE)needUnique )
        {
          v9 = this->guis.list[v7];
          if ( !v9->IsInteractive(v9) )
          {
            v10 = this->guis.list[v7];
            if ( !v10->IsUniqued(v10) )
              break;
          }
        }
      }
      if ( ++v7 >= num )
        goto LABEL_8;
    }
    ++v8->refs;
    return v8;
  }
}

// FUNC: public: virtual class idUserInterface * __thiscall idUserInterfaceManagerLocal::FindDemoGui(char const *)
idUserInterfaceLocal *__thiscall idUserInterfaceManagerLocal::FindDemoGui(
        idUserInterfaceManagerLocal *this,
        const char *qpath)
{
  int num; // ebx
  int v4; // esi

  num = this->demoGuis.num;
  v4 = 0;
  if ( num <= 0 )
    return 0;
  while ( idStr::Icmp(this->demoGuis.list[v4]->source.data, qpath) )
  {
    if ( ++v4 >= num )
      return 0;
  }
  return this->demoGuis.list[v4];
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::RunAlwaysThinkGUIs(int)
void __thiscall idUserInterfaceManagerLocal::RunAlwaysThinkGUIs(idUserInterfaceManagerLocal *this, int time)
{
  int num; // ebp
  int i; // esi

  num = this->alwaysThinkGUIs.num;
  for ( i = 0; i < num; ++i )
  {
    this->alwaysThinkGUIs.list[i]->time = time;
    idWindow::RunTimeEvents(this->alwaysThinkGUIs.list[i]->desktop, time);
  }
}

// FUNC: public: virtual char const * __thiscall idUserInterfaceLocal::Comment(void)const
char *__thiscall idUserInterfaceLocal::Comment(idUserInterfaceLocal *this)
{
  idWindow *desktop; // eax

  desktop = this->desktop;
  if ( desktop )
    return desktop->comment.data;
  else
    return (char *)&entityFilter;
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::Redraw(int)
void __thiscall idUserInterfaceLocal::Redraw(idUserInterfaceLocal *this, int _time)
{
  idUserInterfaceLocal_vtbl *v3; // edi
  double v4; // st7
  idUserInterfaceLocal_vtbl *v5; // edi
  idWindow *desktop; // ecx
  bool v7; // zf
  idWindow *v8; // eax
  idWindow *focusedChild; // ecx
  int v10; // [esp+Ch] [ebp-4h]

  v3 = this->__vftable;
  v4 = ((double (__thiscall *)(idUserInterfaceLocal *))this->CursorX)(this);
  v3->SetStateInt(this, "mousex", (int)v4);
  v5 = this->__vftable;
  v10 = (int)this->CursorY(this);
  v5->SetStateInt(this, "mousey", v10);
  if ( r_skipGuiShaders.internalVar->integerValue <= 5 && !this->loading )
  {
    desktop = this->desktop;
    if ( desktop )
    {
      v7 = !this->initialized;
      this->time = _time;
      if ( v7 )
      {
        this->initialized = 1;
        desktop->Init(desktop);
      }
      if ( Sys_IsJoystickEnabled() )
      {
        v8 = this->desktop;
        if ( (v8->flags & 0x80000) != 0 )
        {
          focusedChild = v8->focusedChild;
          if ( !focusedChild || !idWindow::IsVisible(focusedChild) )
            this->desktop->RouteJoystickChange(this->desktop, 0, 0);
        }
      }
      idDeviceContext::PushClipRect(&uiManagerLocal.dc, uiManagerLocal.screenRect);
      ((void (__thiscall *)(idWindow *, _DWORD, _DWORD))this->desktop->Redraw)(this->desktop, 0, 0);
      idDeviceContext::PopClipRect(&uiManagerLocal.dc);
    }
  }
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::SetStateBool(char const *,bool)
void __thiscall idUserInterfaceLocal::SetStateBool(idUserInterfaceLocal *this, const char *varName, bool value)
{
  const char *v4; // eax

  v4 = va("%i", value);
  idDict::Set(&this->state, varName, v4);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::SetStateInt(char const *,int)
void __thiscall idUserInterfaceLocal::SetStateInt(idUserInterfaceLocal *this, const char *varName, int value)
{
  const char *v4; // eax

  v4 = va("%i", value);
  idDict::Set(&this->state, varName, v4);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::SetStateFloat(char const *,float)
void __thiscall idUserInterfaceLocal::SetStateFloat(idUserInterfaceLocal *this, const char *varName, float value)
{
  const char *v4; // eax

  v4 = va("%f", value);
  idDict::Set(&this->state, varName, v4);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::SetStateVector(char const *,class idVec3 const &)
void __thiscall idUserInterfaceLocal::SetStateVector(idUserInterfaceLocal *this, const char *varName, idVec3 *vector)
{
  const char *v4; // eax

  v4 = idVec3::ToString(vector, 2);
  idDict::Set(&this->state, varName, v4);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::SetStateVec4(char const *,class idVec4 const &)
void __thiscall idUserInterfaceLocal::SetStateVec4(idUserInterfaceLocal *this, const char *varName, idVec4 *vector)
{
  const char *v4; // eax

  v4 = idVec4::ToString(vector, 2);
  idDict::Set(&this->state, varName, v4);
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::StateChanged(int,bool)
void __thiscall idUserInterfaceLocal::StateChanged(idUserInterfaceLocal *this, int _time, BOOL redraw)
{
  idWindow *desktop; // ecx
  const idKeyValue *Key; // eax
  const char *data; // eax
  idWindow *v7; // ecx

  desktop = this->desktop;
  this->time = _time;
  if ( desktop )
    desktop->StateChanged(desktop, redraw);
  Key = idDict::FindKey(&this->state, "noninteractive");
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  this->interactive = !atoi(data) && (v7 = this->desktop) != 0 && idWindow::Interactive(v7);
}

// FUNC: public: virtual char const * __thiscall idUserInterfaceLocal::Activate(bool,int)
char *__thiscall idUserInterfaceLocal::Activate(idUserInterfaceLocal *this, BOOL activate, int _time)
{
  bool v4; // zf

  v4 = this->desktop == 0;
  this->time = _time;
  this->active = activate;
  if ( v4 )
    return (char *)&entityFilter;
  idStr::operator=(&this->activateStr, (char *)&entityFilter);
  this->desktop->Activate(this->desktop, activate, &this->activateStr);
  return this->activateStr.data;
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::WriteToDemoFile(class idDemoFile *)
void __thiscall idUserInterfaceLocal::WriteToDemoFile(idUserInterfaceLocal *this, idDemoFile *f)
{
  idStr work; // [esp+Ch] [ebp-2Ch] BYREF
  int v4; // [esp+34h] [ebp-4h]

  work.len = 0;
  work.alloced = 20;
  work.data = work.baseBuffer;
  work.baseBuffer[0] = 0;
  v4 = 0;
  idDemoFile::WriteDict(f, &this->state);
  if ( this->desktop )
    this->desktop->WriteToDemoFile(this->desktop, f);
  ((void (__thiscall *)(idDemoFile *, _DWORD))f->WriteFloat)(f, LODWORD(this->cursorX));
  ((void (__thiscall *)(idDemoFile *, _DWORD))f->WriteFloat)(f, LODWORD(this->cursorY));
  v4 = -1;
  idStr::FreeData(&work);
}

// FUNC: public: virtual bool __thiscall idUserInterfaceLocal::WriteToSaveGame(class idFile *)const
char __thiscall idUserInterfaceLocal::WriteToSaveGame(idUserInterfaceLocal *this, idFile *savefile)
{
  idFile *v2; // esi
  idFile_vtbl *v3; // edx
  int i; // ebp
  idKeyValue *v6; // ebx
  idFile_vtbl *v7; // eax
  idFile_vtbl *v8; // edx
  char *data; // ebx
  idFile_vtbl *v10; // edx
  idFile_vtbl *v11; // eax
  idFile_vtbl *v12; // eax
  int num; // [esp+94h] [ebp-8h] BYREF
  const char *string; // [esp+98h] [ebp-4h]

  v2 = savefile;
  v3 = savefile->__vftable;
  num = this->state.args.num;
  v3->Write(savefile, &num, 4);
  for ( i = 0; i < num; ++i )
  {
    if ( i < 0 || i >= this->state.args.num )
      v6 = 0;
    else
      v6 = &this->state.args.list[i];
    savefile = (idFile *)v6->key->len;
    v7 = v2->__vftable;
    string = v6->key->data;
    v7->Write(v2, &savefile, 4);
    v2->Write(v2, string, (int)savefile);
    v8 = v2->__vftable;
    savefile = (idFile *)v6->value->len;
    data = v6->value->data;
    v8->Write(v2, &savefile, 4);
    v2->Write(v2, data, (int)savefile);
  }
  v2->Write(v2, &this->active, 1);
  v2->Write(v2, &this->loading, 1);
  v2->Write(v2, &this->interactive, 1);
  v2->Write(v2, &this->uniqued, 1);
  v2->Write(v2, &this->timeStamp, 4);
  v2->Write(v2, &this->initialized, 1);
  v2->Write(v2, &this->cursorX, 4);
  v2->Write(v2, &this->cursorY, 4);
  v2->Write(v2, &this->time, 4);
  v2->Write(v2, &this->refs, 4);
  v10 = v2->__vftable;
  savefile = (idFile *)this->activateStr.len;
  v10->Write(v2, &savefile, 4);
  v2->Write(v2, this->activateStr.data, (int)savefile);
  v11 = v2->__vftable;
  savefile = (idFile *)this->pendingCmd.len;
  v11->Write(v2, &savefile, 4);
  v2->Write(v2, this->pendingCmd.data, (int)savefile);
  v12 = v2->__vftable;
  savefile = (idFile *)this->returnCmd.len;
  v12->Write(v2, &savefile, 4);
  v2->Write(v2, this->returnCmd.data, (int)savefile);
  this->desktop->WriteToSaveGame(this->desktop, v2);
  return 1;
}

// FUNC: public: virtual bool __thiscall idUserInterfaceLocal::ReadFromSaveGame(class idFile *)
char __thiscall idUserInterfaceLocal::ReadFromSaveGame(idUserInterfaceLocal *this, idFile *savefile)
{
  int v3; // ebx
  idFile *v4; // esi
  idFile_vtbl *v5; // eax
  idFile *v6; // edi
  idFile *v7; // edi
  idFile *v8; // edi
  idFile *v9; // edi
  idFile *v10; // edi
  int num; // [esp+A8h] [ebp-50h] BYREF
  idStr value; // [esp+ACh] [ebp-4Ch] BYREF
  idStr key; // [esp+CCh] [ebp-2Ch] BYREF
  int v15; // [esp+F4h] [ebp-4h]

  v3 = 0;
  key.len = 0;
  key.alloced = 20;
  key.data = key.baseBuffer;
  key.baseBuffer[0] = 0;
  v15 = 0;
  value.len = 0;
  value.alloced = 20;
  value.data = value.baseBuffer;
  value.baseBuffer[0] = 0;
  v4 = savefile;
  v5 = savefile->__vftable;
  LOBYTE(v15) = 1;
  v5->Read(savefile, &num, 4);
  idDict::Clear(&this->state);
  if ( num > 0 )
  {
    do
    {
      v4->Read(v4, &savefile, 4);
      v6 = savefile;
      if ( (int)&savefile->__vftable + 1 > key.alloced )
        idStr::ReAllocate(&key, (int)&savefile->__vftable + 1, 1);
      key.len = (int)v6;
      memset(key.data, 0x20u, (unsigned int)v6);
      key.data[key.len] = 0;
      v4->Read(v4, key.data, (int)savefile);
      v4->Read(v4, &savefile, 4);
      v7 = savefile;
      if ( (int)&savefile->__vftable + 1 > value.alloced )
        idStr::ReAllocate(&value, (int)&savefile->__vftable + 1, 1);
      value.len = (int)v7;
      memset(value.data, 0x20u, (unsigned int)v7);
      value.data[value.len] = 0;
      v4->Read(v4, value.data, (int)savefile);
      idDict::Set(&this->state, key.data, value.data);
      ++v3;
    }
    while ( v3 < num );
  }
  v4->Read(v4, &this->active, 1);
  v4->Read(v4, &this->loading, 1);
  v4->Read(v4, &this->interactive, 1);
  v4->Read(v4, &this->uniqued, 1);
  v4->Read(v4, &this->timeStamp, 4);
  v4->Read(v4, &this->initialized, 1);
  v4->Read(v4, &this->cursorX, 4);
  v4->Read(v4, &this->cursorY, 4);
  v4->Read(v4, &this->time, 4);
  v4->Read(v4, &this->refs, 4);
  v4->Read(v4, &savefile, 4);
  v8 = savefile;
  if ( (int)&savefile->__vftable + 1 > this->activateStr.alloced )
    idStr::ReAllocate(&this->activateStr, (int)&savefile->__vftable + 1, 1);
  this->activateStr.len = (int)v8;
  memset(this->activateStr.data, 0x20u, (unsigned int)v8);
  this->activateStr.data[this->activateStr.len] = 0;
  v4->Read(v4, this->activateStr.data, (int)savefile);
  v4->Read(v4, &savefile, 4);
  v9 = savefile;
  if ( (int)&savefile->__vftable + 1 > this->pendingCmd.alloced )
    idStr::ReAllocate(&this->pendingCmd, (int)&savefile->__vftable + 1, 1);
  this->pendingCmd.len = (int)v9;
  memset(this->pendingCmd.data, 0x20u, (unsigned int)v9);
  this->pendingCmd.data[this->pendingCmd.len] = 0;
  v4->Read(v4, this->pendingCmd.data, (int)savefile);
  v4->Read(v4, &savefile, 4);
  v10 = savefile;
  if ( (int)&savefile->__vftable + 1 > this->returnCmd.alloced )
    idStr::ReAllocate(&this->returnCmd, (int)&savefile->__vftable + 1, 1);
  this->returnCmd.len = (int)v10;
  memset(this->returnCmd.data, 0x20u, (unsigned int)v10);
  this->returnCmd.data[this->returnCmd.len] = 0;
  v4->Read(v4, this->returnCmd.data, (int)savefile);
  this->desktop->ReadFromSaveGame(this->desktop, v4);
  LOBYTE(v15) = 0;
  idStr::FreeData(&value);
  v15 = -1;
  idStr::FreeData(&key);
  return 1;
}

// FUNC: public: void __thiscall idUserInterfaceLocal::RecurseSetKeyBindingNames(class idUserInterfaceLocal *,class idWindow *)
void __thiscall idUserInterfaceLocal::RecurseSetKeyBindingNames(
        idUserInterfaceLocal *this,
        idUserInterfaceLocal *iface,
        idWindow *window)
{
  idWinVar *v5; // eax
  idWinVar *v6; // esi
  const char *name; // eax
  idDict *guiDict; // ecx
  const idKeyValue *Key; // eax
  const char *data; // edi
  char *v11; // eax
  idDict *v12; // ecx
  const idKeyValue *v13; // eax
  const char *v14; // esi
  char *v15; // eax
  int i; // esi
  idWindow *Child; // eax
  idWindow *windowa; // [esp+18h] [ebp+8h]

  v5 = window->GetWinVarByName(window, "bind", 0, 0);
  v6 = v5;
  if ( v5 )
  {
    name = v5->name;
    if ( name )
    {
      guiDict = v6->guiDict;
      if ( guiDict && *name == 42 )
      {
        Key = idDict::FindKey(guiDict, name + 1);
        if ( Key )
        {
          data = Key->value->data;
          goto LABEL_10;
        }
        name = &entityFilter;
      }
      data = name;
    }
    else
    {
      data = &entityFilter;
    }
LABEL_10:
    v11 = v6->name;
    if ( v11 )
    {
      v12 = v6->guiDict;
      if ( !v12 || *v11 != 42 )
      {
        v14 = v6->name;
        goto LABEL_17;
      }
      v13 = idDict::FindKey(v12, v11 + 1);
      if ( v13 )
      {
        v14 = v13->value->data;
LABEL_17:
        windowa = (idWindow *)this->__vftable;
        v15 = idKeyInput::KeysFromBinding(data);
        ((void (__thiscall *)(idUserInterfaceLocal *, const char *, char *))LODWORD(windowa->drawRect.x))(
          this,
          v14,
          v15);
        goto LABEL_18;
      }
    }
    v14 = &entityFilter;
    goto LABEL_17;
  }
LABEL_18:
  for ( i = 0; i < idWindow::GetChildCount(window); ++i )
  {
    Child = idWindow::GetChild(window, i);
    if ( Child )
      idUserInterfaceLocal::RecurseSetKeyBindingNames(this, iface, Child);
  }
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::SetKeyBindingNames(void)
void __thiscall idUserInterfaceLocal::SetKeyBindingNames(idUserInterfaceLocal *this)
{
  if ( this->desktop )
    idUserInterfaceLocal::RecurseSetKeyBindingNames(this, this, this->desktop);
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::EndLevelLoad(void)
void __thiscall idUserInterfaceManagerLocal::EndLevelLoad(idUserInterfaceManagerLocal *this)
{
  int num; // ebp
  int i; // edi
  int v4; // ebx
  idUserInterfaceLocal *v5; // ecx
  int v6; // eax
  bool v7; // cc
  int v8; // eax
  idUserInterfaceLocal **list; // ecx
  idUserInterfaceLocal *v10; // edx
  idUserInterfaceLocal **v11; // ecx
  int v12; // edx
  int v13; // edi
  int v14; // eax
  idUserInterfaceLocal **v15; // ecx
  int v16; // eax
  int v17; // eax
  idUserInterfaceLocal **v18; // ecx
  idUserInterfaceLocal *v19; // edi
  idUserInterfaceLocal **v20; // ecx
  int c; // [esp+18h] [ebp-4h]

  num = this->guis.num;
  for ( i = 0; i < num; ++i )
  {
    if ( !this->guis.list[i]->refs )
    {
      v4 = 0;
      if ( declManager->GetNumDecls(declManager, DECL_MATERIAL) <= 0 )
      {
LABEL_6:
        v5 = this->guis.list[i];
        if ( v5 )
          ((void (__thiscall *)(idUserInterfaceLocal *, int))v5->~idUserInterface)(v5, 1);
        if ( i >= 0 )
        {
          v6 = this->guis.num;
          if ( i < v6 )
          {
            v7 = i < v6 - 1;
            this->guis.num = v6 - 1;
            v8 = i;
            if ( v7 )
            {
              do
              {
                list = this->guis.list;
                v10 = list[v8 + 1];
                v11 = &list[v8++];
                *v11 = v10;
              }
              while ( v8 < this->guis.num );
            }
          }
        }
        --i;
        --num;
      }
      else
      {
        while ( declManager->DeclByIndex(declManager, 1, v4, 0)[10].__vftable != (idDecl_vtbl *)this->guis.list[i] )
        {
          if ( ++v4 >= declManager->GetNumDecls(declManager, DECL_MATERIAL) )
            goto LABEL_6;
        }
      }
    }
  }
  v12 = 0;
  c = this->alwaysThinkGUIs.num;
  if ( c > 0 )
  {
    do
    {
      v13 = this->guis.num;
      v14 = 0;
      if ( v13 <= 0 )
        goto LABEL_22;
      v15 = this->guis.list;
      while ( *v15 != this->alwaysThinkGUIs.list[v12] )
      {
        ++v14;
        ++v15;
        if ( v14 >= v13 )
          goto LABEL_22;
      }
      if ( v14 < 0 || !&this->guis.list[v14] )
      {
LABEL_22:
        if ( v12 >= 0 )
        {
          v16 = this->alwaysThinkGUIs.num;
          if ( v12 < v16 )
          {
            v7 = v12 < v16 - 1;
            this->alwaysThinkGUIs.num = v16 - 1;
            v17 = v12;
            if ( v7 )
            {
              do
              {
                v18 = this->alwaysThinkGUIs.list;
                v19 = v18[v17 + 1];
                v20 = &v18[v17++];
                *v20 = v19;
              }
              while ( v17 < this->alwaysThinkGUIs.num );
            }
          }
        }
        --v12;
        --c;
      }
      ++v12;
    }
    while ( v12 < c );
  }
  idDeviceContext::SizeIcons(&this->dc);
}

// FUNC: public: virtual void __thiscall idUserInterfaceManagerLocal::ListGuis(void)const
void __thiscall idUserInterfaceManagerLocal::ListGuis(idUserInterfaceManagerLocal *this)
{
  idUserInterfaceManagerLocal *v1; // ebp
  int num; // edi
  int v3; // esi
  idUserInterfaceLocal *v4; // ebx
  int alloced; // edi
  unsigned int v6; // eax
  idWindow *desktop; // ecx
  int v8; // edi
  idUserInterfaceLocal *v9; // eax
  char *data; // ebx
  int v11; // ebp
  int v12; // eax
  unsigned int total; // [esp+2Ch] [ebp-1Ch]
  int unique; // [esp+30h] [ebp-18h]
  int copies; // [esp+34h] [ebp-14h]
  const char *v16; // [esp+38h] [ebp-10h]
  int refs; // [esp+40h] [ebp-8h]
  int c; // [esp+44h] [ebp-4h]

  v1 = this;
  num = this->guis.num;
  c = num;
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "\n   size   refs   name\n");
  v3 = 0;
  total = 0;
  copies = 0;
  unique = 0;
  if ( num > 0 )
  {
    while ( 1 )
    {
      v4 = v1->guis.list[v3];
      if ( v4->source.data == v4->source.baseBuffer )
        alloced = 0;
      else
        alloced = v4->source.alloced;
      v6 = idDict::Allocated(&v4->state);
      desktop = v4->desktop;
      v8 = v6 + alloced + 260;
      if ( desktop )
        v8 += idWindow::Size(desktop);
      if ( v1->guis.list[v3]->interactive )
      {
        ++unique;
        v16 = "unique";
      }
      else
      {
        ++copies;
        v16 = "copy";
      }
      v9 = v1->guis.list[v3];
      data = v9->source.data;
      v11 = *(_DWORD *)common.type;
      refs = v9->refs;
      v12 = idWindow::NumTransitions(v9->desktop);
      (*(void (**)(netadrtype_t, const char *, ...))(v11 + 124))(
        common.type,
        "%6.1fk %4i (%s) %s ( %i transitions )\n",
        (double)(unsigned int)v8 * 0.0009765625,
        refs,
        v16,
        data,
        v12);
      total += v8;
      num = c;
      if ( ++v3 >= c )
        break;
      v1 = this;
    }
  }
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "===========\n  %i total Guis ( %i copies, %i unique ), %.2f total Mbytes",
    num,
    copies,
    unique,
    (double)total * 0.00000095367432);
}

// FUNC: public: __thiscall idUserInterfaceLocal::idUserInterfaceLocal(void)
void __thiscall idUserInterfaceLocal::idUserInterfaceLocal(idUserInterfaceLocal *this)
{
  idDict *p_state; // edi
  idHashIndex *p_argHash; // ebp
  idKeyValue *list; // ecx
  int v5; // eax
  bool v6; // cc
  int i; // eax
  idKeyValue *v8; // ecx
  idKeyValue *ptr; // [esp+10h] [ebp-18h]

  p_state = &this->state;
  this->__vftable = (idUserInterfaceLocal_vtbl *)&idUserInterfaceLocal::`vftable';
  this->state.args.granularity = 16;
  this->state.args.list = 0;
  this->state.args.num = 0;
  this->state.args.size = 0;
  p_argHash = &this->state.argHash;
  idHashIndex::Init(&this->state.argHash, 1024, 1024);
  list = p_state->args.list;
  p_state->args.granularity = 16;
  ptr = list;
  if ( list )
  {
    v5 = p_state->args.num + 15 - (p_state->args.num + 15) % 16;
    if ( v5 != p_state->args.size )
    {
      if ( v5 > 0 )
      {
        v6 = v5 < p_state->args.num;
        p_state->args.size = v5;
        if ( v6 )
          p_state->args.num = v5;
        p_state->args.list = (idKeyValue *)Memory::Allocate(8 * v5);
        for ( i = 0; i < p_state->args.num; ++i )
        {
          v8 = p_state->args.list;
          v8[i].key = ptr[i].key;
          v8[i].value = ptr[i].value;
        }
        if ( ptr )
          Memory::Free(ptr);
      }
      else
      {
        Memory::Free(list);
        p_state->args.list = 0;
        p_state->args.num = 0;
        p_state->args.size = 0;
      }
    }
  }
  p_state->argHash.granularity = 16;
  idHashIndex::Free(p_argHash);
  p_argHash->hashSize = 128;
  p_argHash->indexSize = 16;
  this->source.len = 0;
  this->source.alloced = 20;
  this->source.data = this->source.baseBuffer;
  this->source.baseBuffer[0] = 0;
  this->activateStr.len = 0;
  this->activateStr.alloced = 20;
  this->activateStr.data = this->activateStr.baseBuffer;
  this->activateStr.baseBuffer[0] = 0;
  this->pendingCmd.len = 0;
  this->pendingCmd.alloced = 20;
  this->pendingCmd.data = this->pendingCmd.baseBuffer;
  this->pendingCmd.baseBuffer[0] = 0;
  this->returnCmd.len = 0;
  this->returnCmd.alloced = 20;
  this->returnCmd.data = this->returnCmd.baseBuffer;
  this->returnCmd.baseBuffer[0] = 0;
  this->cursorY = 0.0;
  this->cursorX = 0.0;
  this->desktop = 0;
  this->loading = 0;
  this->active = 0;
  this->interactive = 0;
  this->uniqued = 0;
  this->bindHandler = 0;
  this->time = 0;
  this->lightColorVar = 0;
  this->initialized = 0;
  this->refs = 1;
}

// FUNC: public: virtual __thiscall idUserInterfaceLocal::~idUserInterfaceLocal(void)
void __thiscall idUserInterfaceLocal::~idUserInterfaceLocal(idUserInterfaceLocal *this)
{
  idWindow *desktop; // ecx
  idKeyValue *list; // eax

  this->__vftable = (idUserInterfaceLocal_vtbl *)&idUserInterfaceLocal::`vftable';
  desktop = this->desktop;
  if ( desktop )
    ((void (__thiscall *)(idWindow *, int))desktop->~idWindow)(desktop, 1);
  this->desktop = 0;
  idStr::FreeData(&this->returnCmd);
  idStr::FreeData(&this->pendingCmd);
  idStr::FreeData(&this->activateStr);
  idStr::FreeData(&this->source);
  idDict::Clear(&this->state);
  idHashIndex::Free(&this->state.argHash);
  list = this->state.args.list;
  if ( list )
    Memory::Free(list);
  this->state.args.list = 0;
  this->state.args.num = 0;
  this->state.args.size = 0;
  this->__vftable = (idUserInterfaceLocal_vtbl *)&idUserInterface::`vftable';
}

// FUNC: public: virtual bool __thiscall idUserInterfaceLocal::InitFromFile(char const *,bool,bool)
char __userpurge idUserInterfaceLocal::InitFromFile@<al>(
        idUserInterfaceLocal *this@<ecx>,
        int a2@<ebx>,
        int a3@<edi>,
        char *qpath,
        BOOL rebuild,
        int cache)
{
  idWindow *desktop; // ecx
  idWindow *v8; // eax
  idWindow *v9; // eax
  idFileSystem_vtbl *v10; // edx
  const char *v11; // eax
  const char *v12; // edi
  int v13; // ebx
  char *data; // edx
  char *v15; // ecx
  char v16; // al
  idWindow *v17; // ecx
  idWindow *v18; // eax
  idRectangle *p_data; // ecx
  float x; // edx
  idWindow *v21; // ecx
  idWindow *v22; // ecx
  int num; // edi
  idUserInterfaceLocal **list; // ecx
  int v25; // eax
  int granularity; // eax
  int v27; // ebx
  idUserInterfaceLocal **v28; // eax
  int v29; // eax
  int v30; // eax
  idUserInterfaceLocal **v31; // ebp
  idUserInterfaceLocal **v32; // eax
  int v33; // eax
  idUserInterfaceLocal **v34; // ecx
  int v35; // ebp
  int size; // ebx
  int v37; // eax
  int v38; // edx
  int v39; // eax
  idUserInterfaceLocal **v40; // edi
  int v41; // eax
  idStr other; // [esp+18h] [ebp-138h] BYREF
  idStr v44; // [esp+3Ch] [ebp-114h] BYREF
  double v45; // [esp+74h] [ebp-DCh]
  idParser src; // [esp+84h] [ebp-CCh] BYREF
  int v47; // [esp+14Ch] [ebp-4h]

  if ( qpath && *qpath )
  {
    this->loading = 1;
    if ( rebuild )
    {
      desktop = this->desktop;
      if ( desktop )
        ((void (__thiscall *)(idWindow *, int))desktop->~idWindow)(desktop, 1);
      v8 = (idWindow *)Memory::Allocate(0x418u);
      *(_DWORD *)&other.baseBuffer[12] = v8;
      v47 = 0;
    }
    else
    {
      if ( this->desktop )
      {
LABEL_13:
        idStr::operator=(&this->source, qpath);
        idDict::Set(&this->state, "text", "Test Text!");
        idParser::idParser(&src, 6156);
        v10 = fileSystem->__vftable;
        v47 = 2;
        ((void (__thiscall *)(idFileSystem *, char *, _DWORD, unsigned int *, int, int))v10->ReadFile)(
          fileSystem,
          qpath,
          0,
          &this->timeStamp,
          a3,
          a2);
        idParser::LoadFile((idParser *)&src.filename.data, qpath, 0);
        if ( src.filename.data )
        {
          v45 = 0.0;
          v44.len = 0;
          v44.alloced = 20;
          v44.data = v44.baseBuffer;
          v44.baseBuffer[0] = 0;
          while ( idParser::ReadToken((idParser *)&src.filename.data, (idToken *)&v44) )
          {
            if ( !idStr::Icmp(v44.data, "windowDef") )
            {
              idWindow::SetDC(this->desktop, &uiManagerLocal.dc);
              if ( this->desktop->Parse(this->desktop, (idParser *)&src.filename.data, rebuild) )
              {
                idWindow::SetFlag(this->desktop, 0x10000000u);
                idWindow::FixupParms(this->desktop);
              }
            }
          }
          idDict::Set(&this->state, "name", qpath);
          idStr::FreeData(&v44);
        }
        else
        {
          idWindow::SetDC(this->desktop, &uiManagerLocal.dc);
          idWindow::SetFlag(this->desktop, 0x10000000u);
          idStr::operator=(&this->desktop->name, "Desktop");
          v11 = va("Invalid GUI: %s", qpath);
          v12 = v11;
          other.len = 0;
          other.alloced = 20;
          other.data = other.baseBuffer;
          other.baseBuffer[0] = 0;
          if ( v11 )
          {
            v13 = strlen(v11);
            if ( v13 + 1 > 20 )
              idStr::ReAllocate(&other, v13 + 1, 1);
            data = other.data;
            v15 = (char *)v12;
            do
            {
              v16 = *v15;
              *data++ = *v15++;
            }
            while ( v16 );
            other.len = v13;
          }
          idWinStr::operator=(&this->desktop->text, &other);
          idStr::FreeData(&other);
          v17 = this->desktop;
          other.len = 0;
          other.data = 0;
          other.alloced = 1142947840;
          *(_DWORD *)other.baseBuffer = 1139802112;
          idWinRectangle::operator=(&v17->rect, (const idRectangle *)&other);
          v18 = this->desktop;
          p_data = &v18->rect.data;
          x = v18->rect.data.x;
          v18 = (idWindow *)((char *)v18 + 56);
          *(float *)&v18->__vftable = x;
          v18->cmd.len = LODWORD(p_data->y);
          v18->cmd.data = (char *)LODWORD(p_data->w);
          v18->cmd.alloced = LODWORD(p_data->h);
          v21 = this->desktop;
          other.len = 1065353216;
          other.data = (char *)1065353216;
          other.alloced = 1065353216;
          *(_DWORD *)other.baseBuffer = 1065353216;
          idWinVec4::operator=(&v21->foreColor, (const idVec4 *)&other);
          v22 = this->desktop;
          memset(&other, 0, 12);
          *(_DWORD *)other.baseBuffer = 1065353216;
          idWinVec4::operator=(&v22->backColor, (const idVec4 *)&other);
          idWindow::SetupFromState(this->desktop);
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "Couldn't load gui: '%s'",
            qpath);
        }
        this->interactive = idWindow::Interactive(this->desktop);
        num = uiManagerLocal.guis.num;
        list = uiManagerLocal.guis.list;
        v25 = 0;
        if ( uiManagerLocal.guis.num > 0 )
        {
          while ( uiManagerLocal.guis.list[v25] != this )
          {
            if ( ++v25 >= uiManagerLocal.guis.num )
              goto LABEL_33;
          }
          if ( v25 >= 0 && &uiManagerLocal.guis.list[v25] )
            goto LABEL_81;
        }
LABEL_33:
        if ( !uiManagerLocal.guis.list )
        {
          granularity = uiManagerLocal.guis.granularity;
          if ( uiManagerLocal.guis.granularity <= 0 )
          {
            num = 0;
            v27 = 0;
            uiManagerLocal.guis.num = 0;
            uiManagerLocal.guis.size = 0;
LABEL_43:
            if ( !granularity )
            {
              granularity = 16;
              uiManagerLocal.guis.granularity = 16;
            }
            v30 = v27 + granularity - (v27 + granularity) % uiManagerLocal.guis.granularity;
            if ( v30 > 0 )
            {
              if ( v30 != v27 )
              {
                v31 = list;
                uiManagerLocal.guis.size = v30;
                if ( v30 < num )
                  uiManagerLocal.guis.num = v30;
                v32 = (idUserInterfaceLocal **)Memory::Allocate(4 * v30);
                num = uiManagerLocal.guis.num;
                list = v32;
                v33 = 0;
                for ( uiManagerLocal.guis.list = list; v33 < uiManagerLocal.guis.num; ++v33 )
                {
                  list[v33] = v31[v33];
                  num = uiManagerLocal.guis.num;
                  list = uiManagerLocal.guis.list;
                }
                if ( v31 )
                {
                  Memory::Free(v31);
                  list = uiManagerLocal.guis.list;
                  num = uiManagerLocal.guis.num;
                }
              }
            }
            else
            {
              num = 0;
              if ( list )
                Memory::Free(list);
              list = 0;
              uiManagerLocal.guis.list = 0;
              uiManagerLocal.guis.num = 0;
              uiManagerLocal.guis.size = 0;
            }
LABEL_56:
            list[num] = this;
            ++uiManagerLocal.guis.num;
            if ( (this->desktop->flags & 0x8000000) == 0 )
            {
LABEL_81:
              this->loading = 0;
              this->lightColorVar = 0;
              ((void (__thiscall *)(idFileSystem *, int))fileSystem->ReadFile)(fileSystem, cache);
              this->initialized = 0;
              v47 = -1;
              idParser::~idParser(&src);
              return 1;
            }
            v34 = uiManagerLocal.alwaysThinkGUIs.list;
            v35 = uiManagerLocal.alwaysThinkGUIs.granularity;
            size = 0;
            if ( !uiManagerLocal.alwaysThinkGUIs.list )
            {
              if ( uiManagerLocal.alwaysThinkGUIs.granularity <= 0 )
              {
                v34 = 0;
                uiManagerLocal.alwaysThinkGUIs.list = 0;
                uiManagerLocal.alwaysThinkGUIs.num = 0;
                uiManagerLocal.alwaysThinkGUIs.size = 0;
                goto LABEL_67;
              }
              if ( uiManagerLocal.alwaysThinkGUIs.granularity != uiManagerLocal.alwaysThinkGUIs.size )
              {
                uiManagerLocal.alwaysThinkGUIs.size = uiManagerLocal.alwaysThinkGUIs.granularity;
                if ( uiManagerLocal.alwaysThinkGUIs.granularity < uiManagerLocal.alwaysThinkGUIs.num )
                  uiManagerLocal.alwaysThinkGUIs.num = uiManagerLocal.alwaysThinkGUIs.granularity;
                v34 = (idUserInterfaceLocal **)Memory::Allocate(4 * uiManagerLocal.alwaysThinkGUIs.granularity);
                v37 = 0;
                for ( uiManagerLocal.alwaysThinkGUIs.list = v34; v37 < uiManagerLocal.alwaysThinkGUIs.num; ++v37 )
                {
                  v34[v37] = *(idUserInterfaceLocal **)(4 * v37);
                  v34 = uiManagerLocal.alwaysThinkGUIs.list;
                }
                v35 = uiManagerLocal.alwaysThinkGUIs.granularity;
              }
            }
            size = uiManagerLocal.alwaysThinkGUIs.size;
            if ( uiManagerLocal.alwaysThinkGUIs.num != uiManagerLocal.alwaysThinkGUIs.size )
            {
LABEL_80:
              v34[uiManagerLocal.alwaysThinkGUIs.num++] = this;
              goto LABEL_81;
            }
LABEL_67:
            if ( !v35 )
            {
              v35 = 16;
              uiManagerLocal.alwaysThinkGUIs.granularity = 16;
            }
            v38 = (size + v35) % v35;
            v39 = size + v35 - v38;
            if ( v39 > 0 )
            {
              if ( v39 != size )
              {
                v40 = v34;
                uiManagerLocal.alwaysThinkGUIs.size = size + v35 - v38;
                if ( v39 < uiManagerLocal.alwaysThinkGUIs.num )
                  uiManagerLocal.alwaysThinkGUIs.num = size + v35 - v38;
                v34 = (idUserInterfaceLocal **)Memory::Allocate(4 * v39);
                v41 = 0;
                for ( uiManagerLocal.alwaysThinkGUIs.list = v34; v41 < uiManagerLocal.alwaysThinkGUIs.num; ++v41 )
                {
                  v34[v41] = v40[v41];
                  v34 = uiManagerLocal.alwaysThinkGUIs.list;
                }
                if ( v40 )
                {
                  Memory::Free(v40);
                  v34 = uiManagerLocal.alwaysThinkGUIs.list;
                }
              }
            }
            else
            {
              if ( v34 )
                Memory::Free(v34);
              v34 = 0;
              uiManagerLocal.alwaysThinkGUIs.list = 0;
              uiManagerLocal.alwaysThinkGUIs.num = 0;
              uiManagerLocal.alwaysThinkGUIs.size = 0;
            }
            goto LABEL_80;
          }
          v27 = uiManagerLocal.guis.size;
          if ( uiManagerLocal.guis.granularity == uiManagerLocal.guis.size )
          {
LABEL_42:
            if ( num != v27 )
              goto LABEL_56;
            goto LABEL_43;
          }
          uiManagerLocal.guis.size = uiManagerLocal.guis.granularity;
          if ( uiManagerLocal.guis.granularity < uiManagerLocal.guis.num )
            uiManagerLocal.guis.num = uiManagerLocal.guis.granularity;
          v28 = (idUserInterfaceLocal **)Memory::Allocate(4 * uiManagerLocal.guis.granularity);
          num = uiManagerLocal.guis.num;
          list = v28;
          v29 = 0;
          for ( uiManagerLocal.guis.list = list; v29 < uiManagerLocal.guis.num; ++v29 )
          {
            list[v29] = *(idUserInterfaceLocal **)(4 * v29);
            num = uiManagerLocal.guis.num;
            list = uiManagerLocal.guis.list;
          }
        }
        v27 = uiManagerLocal.guis.size;
        granularity = uiManagerLocal.guis.granularity;
        goto LABEL_42;
      }
      v8 = (idWindow *)Memory::Allocate(0x418u);
      *(_DWORD *)&other.baseBuffer[12] = v8;
      v47 = 1;
    }
    if ( v8 )
      idWindow::idWindow(v8, this);
    else
      v9 = 0;
    v47 = -1;
    this->desktop = v9;
    goto LABEL_13;
  }
  return 0;
}

// FUNC: public: virtual void __thiscall idUserInterfaceLocal::ReadFromDemoFile(class idDemoFile *)
void __thiscall idUserInterfaceLocal::ReadFromDemoFile(idUserInterfaceLocal *this, idDemoFile *f)
{
  idDict *p_state; // ebp
  const idKeyValue *Key; // eax
  char *data; // eax
  idWindow *v6; // eax
  idWindow *v7; // eax
  int num; // ecx
  idUserInterfaceLocal **list; // esi
  int v10; // eax
  int granularity; // ebp
  idUserInterfaceLocal **v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // eax
  idUserInterfaceLocal **v16; // edi
  idUserInterfaceLocal **v17; // eax
  int v18; // eax
  idStr work; // [esp+10h] [ebp-2Ch] BYREF
  int v20; // [esp+38h] [ebp-4h]

  work.len = 0;
  work.alloced = 20;
  work.data = work.baseBuffer;
  work.baseBuffer[0] = 0;
  p_state = &this->state;
  v20 = 0;
  idDemoFile::ReadDict(f, &this->state);
  Key = idDict::FindKey(p_state, "name");
  if ( Key )
    data = Key->value->data;
  else
    data = (char *)&entityFilter;
  idStr::operator=(&this->source, data);
  if ( this->desktop )
  {
    idDemoFile::Log(f, "re-using gui\n");
    this->desktop->ReadFromDemoFile(this->desktop, f, 0);
  }
  else
  {
    idDemoFile::Log(f, "creating new gui\n");
    v6 = (idWindow *)Memory::Allocate(0x418u);
    LOBYTE(v20) = 1;
    if ( v6 )
      idWindow::idWindow(v6, this);
    else
      v7 = 0;
    LOBYTE(v20) = 0;
    this->desktop = v7;
    idWindow::SetFlag(v7, 0x10000000u);
    idWindow::SetDC(this->desktop, &uiManagerLocal.dc);
    this->desktop->ReadFromDemoFile(this->desktop, f, 1);
  }
  f->ReadFloat(f, &this->cursorX);
  f->ReadFloat(f, &this->cursorY);
  num = uiManagerLocal.demoGuis.num;
  list = uiManagerLocal.demoGuis.list;
  v10 = 0;
  if ( uiManagerLocal.demoGuis.num <= 0 )
  {
LABEL_13:
    if ( !uiManagerLocal.demoGuis.list )
    {
      granularity = uiManagerLocal.demoGuis.granularity;
      if ( uiManagerLocal.demoGuis.granularity <= 0 )
      {
        list = 0;
        num = 0;
        uiManagerLocal.demoGuis.list = 0;
        uiManagerLocal.demoGuis.num = 0;
        uiManagerLocal.demoGuis.size = 0;
        goto LABEL_23;
      }
      if ( uiManagerLocal.demoGuis.granularity == uiManagerLocal.demoGuis.size )
      {
LABEL_22:
        if ( num != uiManagerLocal.demoGuis.size )
        {
LABEL_36:
          list[num] = this;
          ++uiManagerLocal.demoGuis.num;
          goto LABEL_37;
        }
LABEL_23:
        if ( !granularity )
        {
          granularity = 16;
          uiManagerLocal.demoGuis.granularity = 16;
        }
        v14 = (uiManagerLocal.demoGuis.size + granularity) % granularity;
        v15 = uiManagerLocal.demoGuis.size + granularity - v14;
        if ( v15 > 0 )
        {
          if ( v15 != uiManagerLocal.demoGuis.size )
          {
            v16 = list;
            uiManagerLocal.demoGuis.size = uiManagerLocal.demoGuis.size + granularity - v14;
            if ( v15 < num )
              uiManagerLocal.demoGuis.num = v15;
            v17 = (idUserInterfaceLocal **)Memory::Allocate(4 * v15);
            num = uiManagerLocal.demoGuis.num;
            list = v17;
            v18 = 0;
            for ( uiManagerLocal.demoGuis.list = list; v18 < uiManagerLocal.demoGuis.num; ++v18 )
            {
              list[v18] = v16[v18];
              num = uiManagerLocal.demoGuis.num;
              list = uiManagerLocal.demoGuis.list;
            }
            if ( v16 )
            {
              Memory::Free(v16);
              list = uiManagerLocal.demoGuis.list;
              num = uiManagerLocal.demoGuis.num;
            }
          }
        }
        else
        {
          if ( list )
            Memory::Free(list);
          list = 0;
          num = 0;
          uiManagerLocal.demoGuis.list = 0;
          uiManagerLocal.demoGuis.num = 0;
          uiManagerLocal.demoGuis.size = 0;
        }
        goto LABEL_36;
      }
      uiManagerLocal.demoGuis.size = uiManagerLocal.demoGuis.granularity;
      if ( uiManagerLocal.demoGuis.granularity < uiManagerLocal.demoGuis.num )
        uiManagerLocal.demoGuis.num = uiManagerLocal.demoGuis.granularity;
      v12 = (idUserInterfaceLocal **)Memory::Allocate(4 * uiManagerLocal.demoGuis.granularity);
      num = uiManagerLocal.demoGuis.num;
      list = v12;
      v13 = 0;
      for ( uiManagerLocal.demoGuis.list = list; v13 < uiManagerLocal.demoGuis.num; ++v13 )
      {
        list[v13] = *(idUserInterfaceLocal **)(4 * v13);
        num = uiManagerLocal.demoGuis.num;
        list = uiManagerLocal.demoGuis.list;
      }
    }
    granularity = uiManagerLocal.demoGuis.granularity;
    goto LABEL_22;
  }
  while ( uiManagerLocal.demoGuis.list[v10] != this )
  {
    if ( ++v10 >= uiManagerLocal.demoGuis.num )
      goto LABEL_13;
  }
LABEL_37:
  v20 = -1;
  idStr::FreeData(&work);
}

// FUNC: public: virtual class idUserInterface * __thiscall idUserInterfaceManagerLocal::Alloc(void)const
void __thiscall idUserInterfaceManagerLocal::Alloc(idUserInterfaceManagerLocal *this)
{
  idUserInterfaceLocal *v1; // eax

  v1 = (idUserInterfaceLocal *)Memory::Allocate(0xD8u);
  if ( v1 )
    idUserInterfaceLocal::idUserInterfaceLocal(v1);
}

// FUNC: public: virtual class idListGUI * __thiscall idUserInterfaceManagerLocal::AllocListGUI(void)const
void __thiscall idUserInterfaceManagerLocal::AllocListGUI(idUserInterfaceManagerLocal *this)
{
  idListGUILocal *v1; // eax

  v1 = (idListGUILocal *)Memory::Allocate(0x60u);
  if ( v1 )
    idListGUILocal::idListGUILocal(v1);
}
