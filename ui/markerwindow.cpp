
// FUNC: public: virtual class idWinVar * __thiscall idMarkerWindow::GetWinVarByName(char const *,bool)
idWinVar *__thiscall idMarkerWindow::GetWinVarByName(idMarkerWindow *this, const char *_name, bool fixup)
{
  return idWindow::GetWinVarByName(this, _name, fixup, 0);
}

// FUNC: private: void __thiscall idMarkerWindow::Line(int,int,int,int,unsigned int *,unsigned int)
void __thiscall idMarkerWindow::Line(
        idMarkerWindow *this,
        int x1,
        int y1,
        int x2,
        int y2,
        unsigned int *out,
        unsigned int color)
{
  int v7; // ebp
  int v8; // edi
  int v9; // ecx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // esi
  unsigned int v14; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // esi
  int v18; // ecx
  int v19; // ebx
  int v20; // eax
  int v21; // eax
  int incy; // [esp+10h] [ebp-8h]
  int v23; // [esp+14h] [ebp-4h]
  int x1a; // [esp+1Ch] [ebp+4h]
  int x1b; // [esp+1Ch] [ebp+4h]
  int right; // [esp+20h] [ebp+8h]
  int incx; // [esp+24h] [ebp+Ch]
  int incxa; // [esp+24h] [ebp+Ch]
  int up; // [esp+28h] [ebp+10h]
  int upa; // [esp+28h] [ebp+10h]

  v7 = y1;
  v8 = x1;
  v9 = abs32(x2 - x1);
  v10 = abs32(y2 - y1);
  right = 2 * (x1 <= x2) - 1;
  v11 = 2 * (v7 <= y2) - 1;
  incy = v11;
  if ( v9 <= v10 )
  {
    v16 = 2 * v9;
    v17 = v16 - v10;
    x1b = v16;
    incxa = v16 - 2 * v10;
    if ( v10 >= 0 )
    {
      v18 = -512 * v11;
      v19 = (63 - v7) << 9;
      v23 = v18;
      upa = v10 + 1;
      do
      {
        v20 = v19 + v8;
        if ( v19 + v8 < 0 || v20 >= 0x8000 )
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "Out of bounds on point %i : %i",
            v8,
            v7);
        else
          out[v20] = color;
        v21 = incxa;
        v7 += incy;
        v19 += v23;
        v8 += v17 <= 0 ? 0 : right;
        if ( v17 <= 0 )
          v21 = x1b;
        v17 += v21;
        --upa;
      }
      while ( upa );
    }
  }
  else
  {
    v12 = 2 * v10;
    v13 = v12 - v9;
    x1a = v12;
    incx = v12 - 2 * v9;
    if ( v9 >= 0 )
    {
      up = v9 + 1;
      do
      {
        v14 = v8 + ((63 - v7) << 9);
        if ( v14 > 0x7FFF )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "Out of bounds on point %i : %i",
            v8,
            v7);
          v11 = incy;
        }
        else
        {
          out[v14] = color;
        }
        v8 += right;
        v15 = incx;
        v7 += v13 <= 0 ? 0 : v11;
        if ( v13 <= 0 )
          v15 = x1a;
        v13 += v15;
        --up;
      }
      while ( up );
    }
  }
}

// FUNC: public: virtual void __thiscall idMarkerWindow::MouseExit(void)
// attributes: thunk
void __thiscall idMarkerWindow::MouseExit(idMarkerWindow *this)
{
  idWindow::MouseExit(this);
}

// FUNC: public: virtual void __thiscall idMarkerWindow::MouseEnter(void)
// attributes: thunk
void __thiscall idMarkerWindow::MouseEnter(idMarkerWindow *this)
{
  idWindow::MouseEnter(this);
}

// FUNC: private: virtual bool __thiscall idMarkerWindow::ParseInternalVar(char const *,class idParser *)
bool __thiscall idMarkerWindow::ParseInternalVar(idMarkerWindow *this, const char *_name, idParser *src)
{
  const idMaterial *v4; // eax
  const idMaterial *v6; // eax
  idStr str; // [esp+8h] [ebp-4Ch] BYREF
  idStr out; // [esp+28h] [ebp-2Ch] BYREF
  int v9; // [esp+50h] [ebp-4h]

  if ( idStr::Icmp(_name, "markerMat") )
  {
    if ( idStr::Icmp(_name, "markerStop") )
    {
      if ( idStr::Icmp(_name, "markerColor") )
      {
        return idWindow::ParseInternalVar(this, _name, src);
      }
      else
      {
        idWindow::ParseVec4(this, src, &this->markerColor);
        return 1;
      }
    }
    else
    {
      out.len = 0;
      out.alloced = 20;
      out.data = out.baseBuffer;
      out.baseBuffer[0] = 0;
      v9 = 1;
      idWindow::ParseString(this, src, &out);
      v6 = declManager->FindMaterial(declManager, out.data, 1);
      this->markerStop = v6;
      v6->sort = -2.0;
      v9 = -1;
      idStr::FreeData(&out);
      return 1;
    }
  }
  else
  {
    str.len = 0;
    str.alloced = 20;
    str.data = str.baseBuffer;
    str.baseBuffer[0] = 0;
    v9 = 0;
    idWindow::ParseString(this, src, &str);
    v4 = declManager->FindMaterial(declManager, str.data, 1);
    this->markerMat = v4;
    v4->sort = -2.0;
    v9 = -1;
    idStr::FreeData(&str);
    return 1;
  }
}

// FUNC: public: virtual char const * __thiscall idMarkerWindow::HandleEvent(struct sysEvent_s const *,bool *)
const char *__thiscall idMarkerWindow::HandleEvent(idMarkerWindow *this, const sysEvent_s *event, bool *updateVisuals)
{
  int v4; // ebp
  int evValue; // eax
  idWindow *v6; // eax
  markerData_t *v7; // edi
  idUserInterfaceLocal *gui; // ebx
  idUserInterfaceLocal *v9; // ecx
  idUserInterfaceLocal *v10; // ebx
  idWindow *v11; // eax
  idWindow *v12; // eax
  idWindow *v13; // eax
  idWindow *v14; // eax
  idDeclBase *base; // ecx
  idUserInterfaceLocal *v16; // edi
  idWindow *v17; // eax
  idUserInterfaceLocal *v18; // ecx
  int v19; // ecx
  idUserInterfaceLocal *v20; // edi
  idWindow *v21; // eax
  idWindow *v22; // eax
  idWindow *v23; // eax
  idWindow *v24; // eax
  idDict *v25; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  idDict *v28; // eax
  const idKeyValue *v29; // eax
  const char *v30; // eax
  const char *result; // eax
  idUserInterfaceLocal *v32; // ecx
  idWindow *v33; // eax
  bool v34; // zf
  float xt; // [esp+0h] [ebp-20h]
  float yt; // [esp+4h] [ebp-1Ch]
  const char *yta; // [esp+4h] [ebp-1Ch]
  const char *ytb; // [esp+4h] [ebp-1Ch]
  int currentTime; // [esp+8h] [ebp-18h]
  const char *v40; // [esp+8h] [ebp-18h]
  const char *v41; // [esp+10h] [ebp-10h]
  const char *v42; // [esp+14h] [ebp-Ch]
  int pct; // [esp+18h] [ebp-8h]
  float pcta; // [esp+18h] [ebp-8h]
  const sysEvent_s *eventa; // [esp+24h] [ebp+4h]

  if ( event->evType != SE_KEY )
    return &entityFilter;
  v4 = 0;
  if ( !event->evValue2 )
    return &entityFilter;
  evValue = event->evValue;
  if ( evValue == 187 )
  {
    v6 = this->gui->GetDesktop(this->gui);
    idWindow::SetChildWinVarVal(v6, "markerText", "text", &entityFilter);
    pct = this->markerTimes.num;
    if ( pct > 0 )
    {
      eventa = 0;
      while ( 1 )
      {
        v7 = (markerData_t *)((char *)eventa + (unsigned int)this->markerTimes.list);
        gui = this->gui;
        yt = ((double (*)(void))gui->CursorY)();
        xt = gui->CursorX(gui);
        if ( idRectangle::Contains(&v7->rect, xt, yt) )
          break;
        eventa = (const sysEvent_s *)((char *)eventa + 24);
        if ( ++v4 >= pct )
          goto LABEL_10;
      }
      v9 = this->gui;
      this->currentMarker = v4;
      v9->SetStateInt(v9, "currentMarker", v7->time);
      this->stopTime = v7->time;
      v10 = this->gui;
      yta = va("Marker set at %.2i:%.2i", v7->time / 60 / 60, v7->time / 60 % 60);
      v11 = v10->GetDesktop(v10);
      idWindow::SetChildWinVarVal(v11, "markerText", "text", yta);
      v12 = this->gui->GetDesktop(this->gui);
      idWindow::SetChildWinVarVal(v12, "markerText", "visible", "1");
      v13 = this->gui->GetDesktop(this->gui);
      idWindow::SetChildWinVarVal(v13, "markerBackground", "matcolor", "1 1 1 1");
      v14 = this->gui->GetDesktop(this->gui);
      idWindow::SetChildWinVarVal(v14, "markerBackground", "text", &entityFilter);
      base = v7->mat->base;
      v16 = this->gui;
      ytb = base->GetName(base);
      v17 = v16->GetDesktop(v16);
      idWindow::SetChildWinVarVal(v17, "markerBackground", "background", ytb);
    }
LABEL_10:
    if ( v4 == pct )
    {
      v18 = this->gui;
      currentTime = this->currentTime;
      this->currentMarker = -1;
      v18->SetStateInt(v18, "currentMarker", currentTime);
      v19 = this->currentTime;
      this->stopTime = v19;
      v20 = this->gui;
      v40 = va("Marker set at %.2i:%.2i", v19 / 60 / 60, v19 / 60 % 60);
      v21 = v20->GetDesktop(v20);
      idWindow::SetChildWinVarVal(v21, "markerText", "text", v40);
      v22 = this->gui->GetDesktop(this->gui);
      idWindow::SetChildWinVarVal(v22, "markerText", "visible", "1");
      v23 = this->gui->GetDesktop(this->gui);
      idWindow::SetChildWinVarVal(v23, "markerBackground", "matcolor", "0 0 0 0");
      v24 = this->gui->GetDesktop(this->gui);
      idWindow::SetChildWinVarVal(v24, "markerBackground", "text", "No Preview");
    }
    v25 = (idDict *)this->gui->State(this->gui);
    Key = idDict::FindKey(v25, "loadPct");
    if ( Key )
      data = Key->value->data;
    else
      data = "0";
    pcta = atof(data);
    v28 = (idDict *)this->gui->State(this->gui);
    v29 = idDict::FindKey(v28, "loadLength");
    if ( v29 )
      v30 = v29->value->data;
    else
      v30 = "0";
    if ( (double)atoi(v30) * pcta < (double)this->stopTime )
      return "cmdDemoGotoMarker";
    return &entityFilter;
  }
  if ( evValue == 188 )
  {
    v32 = this->gui;
    this->stopTime = -1;
    v33 = (idWindow *)((int (__thiscall *)(idUserInterfaceLocal *, const char *, const char *))v32->GetDesktop)(
                        v32,
                        "markerText",
                        "text");
    idWindow::SetChildWinVarVal(v33, &entityFilter, v41, v42);
    this->gui->SetStateInt(this->gui, "currentMarker", -1);
    return "cmdDemoGotoMarker";
  }
  v34 = evValue == 32;
  result = "cmdDemoPauseFrame";
  if ( !v34 )
    return &entityFilter;
  return result;
}

// FUNC: public: virtual void __thiscall idMarkerWindow::Draw(int,float,float)
void __thiscall idMarkerWindow::Draw(idMarkerWindow *this, int time, float x, float y)
{
  idRectangle *p_clientRect; // eax
  float v6; // edx
  idUserInterfaceLocal *gui; // ecx
  float h; // edx
  idUserInterfaceLocal_vtbl *v9; // eax
  idDict *v10; // eax
  const idKeyValue *Key; // eax
  const char *data; // eax
  int num; // ebx
  int v14; // edi
  markerData_t *list; // ecx
  double w; // st6
  markerData_t *v17; // ecx
  double v18; // st7
  idUserInterfaceLocal *v19; // edi
  double v20; // st7
  idUserInterfaceLocal *v21; // ecx
  double v22; // st7
  idUserInterfaceLocal *v23; // ecx
  double v24; // st7
  idUserInterfaceLocal *v25; // ecx
  double v26; // st7
  int currentTime; // ecx
  const char *v28; // eax
  const idMaterial *markerStop; // eax
  idVec4 v30; // [esp-34h] [ebp-78h]
  idRectangle v31; // [esp-24h] [ebp-68h]
  float xt; // [esp+0h] [ebp-44h]
  float yt; // [esp+4h] [ebp-40h]
  int len; // [esp+1Ch] [ebp-28h]
  int stopTime; // [esp+20h] [ebp-24h]
  idRectangle r; // [esp+24h] [ebp-20h] BYREF
  idVec4 color; // [esp+34h] [ebp-10h] BYREF

  p_clientRect = &this->clientRect;
  v6 = this->clientRect.y;
  r.x = this->clientRect.x;
  r.w = this->clientRect.w;
  gui = this->gui;
  r.y = v6;
  h = p_clientRect->h;
  v9 = gui->__vftable;
  r.h = h;
  v10 = (idDict *)v9->State(gui);
  Key = idDict::FindKey(v10, "loadLength");
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  len = atoi(data);
  if ( !len )
    len = 1;
  if ( this->numStats > 1 )
  {
    num = this->markerTimes.num;
    if ( num > 0 )
    {
      v14 = 0;
      do
      {
        list = this->markerTimes.list;
        w = list[v14].rect.w;
        v17 = &list[v14];
        if ( w == 0.0 )
        {
          v18 = (double)v17->time;
          v17->rect.w = 16.0;
          v17->rect.h = 16.0;
          v17->rect.x = v18 / (double)len * r.w + r.x - 8.0;
          v17->rect.y = r.h + r.y - 20.0;
        }
        idDeviceContext::DrawMaterial(
          this->dc,
          v17->rect.x,
          v17->rect.y,
          v17->rect.w,
          v17->rect.h,
          this->markerMat,
          &this->markerColor,
          1.0,
          1.0);
        ++v14;
        --num;
      }
      while ( num );
    }
  }
  r.y = r.y + 10.0;
  if ( r.w > 0.0 )
  {
    v19 = this->gui;
    yt = v19->CursorY(v19);
    xt = v19->CursorX(v19);
    if ( idRectangle::Contains(&r, xt, yt) )
    {
      v20 = ((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorX)(this->gui);
      v21 = this->gui;
      this->currentTime = (int)((v20 - r.x) / r.w * (double)len);
      v22 = ((double (__thiscall *)(idUserInterfaceLocal *))v21->CursorX)(v21);
      v23 = this->gui;
      if ( r.w + r.x - 40.0 >= v22 )
        v24 = ((double (__thiscall *)(idUserInterfaceLocal *))v23->CursorX)(v23);
      else
        v24 = ((double (__thiscall *)(idUserInterfaceLocal *))v23->CursorX)(v23) - 40.0;
      v25 = this->gui;
      r.x = v24;
      v26 = ((double (__thiscall *)(idUserInterfaceLocal *))v25->CursorY)(v25);
      currentTime = this->currentTime;
      r.y = v26 - 15.0;
      *(_QWORD *)&v31.x = *(_QWORD *)&r.x;
      r.w = 40.0;
      *(_QWORD *)&v31.w = 0x41A0000042200000i64;
      r.h = 20.0;
      v30 = idDeviceContext::colorWhite;
      v28 = va("%.2i:%.2i", currentTime / 60 / 60, currentTime / 60 % 60);
      idDeviceContext::DrawTextA(this->dc, v28, 0.25, 0, 0, v30, v31, 0, -1, 0, 0, 0, 0, 0);
    }
  }
  stopTime = this->stopTime;
  if ( stopTime >= 0 )
  {
    markerStop = this->markerStop;
    if ( markerStop )
    {
      r = this->clientRect;
      r.y = (r.h - 32.0) * 0.5 + r.y;
      color.x = 1.0;
      color.y = 1.0;
      color.z = 1.0;
      color.w = 0.64999998;
      r.x = (double)stopTime / (double)len * r.w - 16.0 + r.x;
      idDeviceContext::DrawMaterial(this->dc, r.x, r.y, 32.0, 32.0, markerStop, &color, 1.0, 1.0);
    }
  }
}

// FUNC: public: virtual char const * __thiscall idMarkerWindow::RouteMouseCoords(float,float)
const char *__thiscall idMarkerWindow::RouteMouseCoords(idMarkerWindow *this, float xd, float yd)
{
  const char *v4; // eax
  int num; // ebp
  idDict *v6; // eax
  const idKeyValue *Key; // eax
  int v8; // ebx
  const char *data; // eax
  markerData_t *v10; // edi
  double v11; // st7
  idDeclBase *base; // ecx
  idUserInterfaceLocal *gui; // edi
  idWindow *v14; // eax
  idWindow *v15; // eax
  idWindow *v16; // eax
  int currentMarker; // eax
  idWindow *v18; // eax
  idWindow *v19; // eax
  idUserInterfaceLocal *v21; // edi
  idDeclBase *v22; // ecx
  idWindow *v23; // eax
  idWindow *v24; // eax
  idWindow *v25; // eax
  const char *v26; // [esp-4h] [ebp-18h]
  const char *v27; // [esp-4h] [ebp-18h]
  float v28; // [esp+10h] [ebp-4h]
  const char *xda; // [esp+18h] [ebp+4h]
  const char *ret; // [esp+1Ch] [ebp+8h]

  v4 = idWindow::RouteMouseCoords(this, xd, yd);
  num = this->markerTimes.num;
  xda = v4;
  v6 = (idDict *)this->gui->State(this->gui);
  Key = idDict::FindKey(v6, "loadLength");
  v8 = 0;
  if ( Key )
    data = Key->value->data;
  else
    data = "0";
  atoi(data);
  if ( num <= 0 )
    goto LABEL_13;
  ret = 0;
  while ( 1 )
  {
    v10 = (markerData_t *)&ret[(unsigned int)this->markerTimes.list];
    v11 = ((double (__thiscall *)(idUserInterfaceLocal *))this->gui->CursorX)(this->gui);
    v28 = v11;
    this->gui->CursorY(this->gui);
    if ( (0.0 != v10->rect.w || 0.0 != v10->rect.h)
      && v11 >= v10->rect.x
      && v11 <= v10->rect.x + v10->rect.w
      && v28 >= (double)v10->rect.y
      && v10->rect.h + v10->rect.y >= v28 )
    {
      break;
    }
    ret += 24;
    if ( ++v8 >= num )
      goto LABEL_13;
  }
  base = v10->mat->base;
  gui = this->gui;
  v26 = base->GetName(base);
  v14 = gui->GetDesktop(gui);
  idWindow::SetChildWinVarVal(v14, "markerBackground", "background", v26);
  v15 = this->gui->GetDesktop(this->gui);
  idWindow::SetChildWinVarVal(v15, "markerBackground", "matcolor", "1 1 1 1");
  v16 = this->gui->GetDesktop(this->gui);
  idWindow::SetChildWinVarVal(v16, "markerBackground", "text", &entityFilter);
  if ( v8 >= num )
  {
LABEL_13:
    currentMarker = this->currentMarker;
    if ( currentMarker == -1 )
    {
      v18 = this->gui->GetDesktop(this->gui);
      idWindow::SetChildWinVarVal(v18, "markerBackground", "matcolor", "0 0 0 0");
      v19 = this->gui->GetDesktop(this->gui);
      idWindow::SetChildWinVarVal(v19, "markerBackground", "text", "No Preview");
      return xda;
    }
    v21 = this->gui;
    v22 = this->markerTimes.list[currentMarker].mat->base;
    v27 = v22->GetName(v22);
    v23 = v21->GetDesktop(v21);
    idWindow::SetChildWinVarVal(v23, "markerBackground", "background", v27);
    v24 = this->gui->GetDesktop(this->gui);
    idWindow::SetChildWinVarVal(v24, "markerBackground", "matcolor", "1 1 1 1");
    v25 = this->gui->GetDesktop(this->gui);
    idWindow::SetChildWinVarVal(v25, "markerBackground", "text", &entityFilter);
  }
  return xda;
}

// FUNC: public: __thiscall idMarkerWindow::idMarkerWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idMarkerWindow::idMarkerWindow(idMarkerWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idWindow::idWindow(this, d, g);
  this->__vftable = (idMarkerWindow_vtbl *)&idMarkerWindow::`vftable';
  this->markerTimes.list = 0;
  this->markerTimes.num = 0;
  this->markerTimes.size = 0;
  this->markerTimes.granularity = 16;
  this->statData.len = 0;
  this->statData.alloced = 20;
  this->statData.data = this->statData.baseBuffer;
  this->statData.baseBuffer[0] = 0;
  this->gui = g;
  this->numStats = 0;
  this->imageBuff = 0;
  this->markerMat = 0;
  this->markerStop = 0;
  this->dc = d;
  this->currentTime = -1;
  this->currentMarker = -1;
  this->stopTime = -1;
}

// FUNC: public: virtual __thiscall idMarkerWindow::~idMarkerWindow(void)
void __thiscall idMarkerWindow::~idMarkerWindow(idMarkerWindow *this)
{
  markerData_t *list; // eax

  this->__vftable = (idMarkerWindow_vtbl *)&idMarkerWindow::`vftable';
  idStr::FreeData(&this->statData);
  list = this->markerTimes.list;
  if ( list )
    Memory::Free(list);
  this->markerTimes.list = 0;
  this->markerTimes.num = 0;
  this->markerTimes.size = 0;
  idWindow::~idWindow(this);
}

// FUNC: public: virtual void __thiscall idMarkerWindow::Activate(bool,class idStr &)
void __userpurge idMarkerWindow::Activate(idMarkerWindow *this@<ecx>, int a2@<edi>, bool activate, idStr *act)
{
  idWindow *v5; // eax
  idUserInterfaceLocal *gui; // ecx
  idDict *v7; // eax
  const idKeyValue *Key; // eax
  char *data; // eax
  bool v10; // zf
  int *p_numStats; // edi
  idFile *v12; // eax
  idFile *v13; // ebp
  int v14; // ecx
  __int16 *p_stamina; // eax
  int len; // edi
  char *v17; // ecx
  char *v18; // edx
  char v19; // al
  idFileList *v20; // eax
  int granularity; // edi
  bool v22; // cc
  markerData_t *v23; // eax
  markerData_t *v24; // ebp
  int v25; // ecx
  int *v26; // eax
  markerData_t *v27; // edx
  int num; // ebp
  int size; // eax
  int v30; // edi
  markerData_t *list; // ebx
  markerData_t *v32; // eax
  markerData_t *v33; // ebp
  int v34; // ecx
  int v35; // eax
  markerData_t *v36; // edi
  markerData_t *v37; // edx
  int v38; // ecx
  double v39; // st7
  double v40; // st7
  logStats_t *loggedStats; // edi
  int v42; // ebp
  int v43; // ebx
  shaderStage_t *stages; // eax
  int v45; // [esp+30h] [ebp-7Ch]
  float markers; // [esp+40h] [ebp-6Ch]
  int y1; // [esp+44h] [ebp-68h]
  int md_4; // [esp+4Ch] [ebp-60h]
  const idMaterial *md_8; // [esp+50h] [ebp-5Ch]
  idStr name; // [esp+60h] [ebp-4Ch] BYREF
  idStr markerPath; // [esp+80h] [ebp-2Ch] BYREF
  int v52; // [esp+A8h] [ebp-4h]
  void *retaddr; // [esp+ACh] [ebp+0h]
  int activatea; // [esp+B0h] [ebp+4h]
  int i; // [esp+B4h] [ebp+8h]
  int v56; // [esp+B8h] [ebp+Ch]

  idWindow::Activate(this, activate, act);
  if ( activate )
  {
    v5 = this->gui->GetDesktop(this->gui);
    idWindow::SetChildWinVarVal(v5, "markerText", "text", &entityFilter);
    this->imageBuff = (unsigned int *)Mem_Alloc(0x20000, 0x13u);
    if ( this->markerTimes.list )
      Memory::Free(this->markerTimes.list);
    this->markerTimes.list = 0;
    this->markerTimes.num = 0;
    this->markerTimes.size = 0;
    gui = this->gui;
    this->currentMarker = -1;
    this->currentTime = -1;
    this->stopTime = -1;
    v7 = (idDict *)gui->State(gui);
    Key = idDict::FindKey(v7, "statData");
    if ( Key )
      data = Key->value->data;
    else
      data = (char *)&entityFilter;
    v45 = a2;
    idStr::operator=(&this->statData, data);
    v10 = this->statData.len == 0;
    p_numStats = &this->numStats;
    this->numStats = 0;
    if ( !v10 )
    {
      v12 = fileSystem->OpenFileRead(fileSystem, this->statData.data, 1, 0);
      v13 = v12;
      if ( v12 )
      {
        ((void (__thiscall *)(idFile *, int *, int, int))v12->Read)(v12, &this->numStats, 4, v45);
        v13->Read(v13, this->loggedStats, 8 * *p_numStats);
        v14 = 0;
        if ( *p_numStats > 0 )
        {
          p_stamina = &this->loggedStats[0].stamina;
          do
          {
            if ( *(p_stamina - 2) < 0 )
              *(p_stamina - 2) = 0;
            if ( *p_stamina < 0 )
              *p_stamina = 0;
            if ( *(p_stamina - 1) < 0 )
              *(p_stamina - 1) = 0;
            if ( p_stamina[1] < 0 )
              p_stamina[1] = 0;
            ++v14;
            p_stamina += 4;
          }
          while ( v14 < *p_numStats );
        }
        fileSystem->CloseFile(fileSystem, v13);
      }
    }
    if ( *p_numStats > 1 && this->background )
    {
      len = this->statData.len;
      markerPath.data = markerPath.baseBuffer;
      markerPath.len = 0;
      markerPath.alloced = 20;
      markerPath.baseBuffer[0] = 0;
      if ( len + 1 > 20 )
        idStr::ReAllocate(&markerPath, len + 1, 1);
      v17 = this->statData.data;
      v18 = markerPath.data;
      do
      {
        v19 = *v17;
        *v18++ = *v17++;
      }
      while ( v19 );
      markerPath.len = len;
      v52 = 0;
      idStr::StripFilename(&markerPath);
      v20 = (idFileList *)((int (__thiscall *)(idFileSystem *, char *, const char *, _DWORD, int, _DWORD, int))fileSystem->ListFiles)(
                            fileSystem,
                            markerPath.data,
                            ".tga",
                            0,
                            1,
                            0,
                            v45);
      y1 = (int)v20;
      name.data = 0;
      *(_DWORD *)name.baseBuffer = 20;
      name.alloced = (int)&name.baseBuffer[4];
      name.baseBuffer[4] = 0;
      LOBYTE(retaddr) = 1;
      i = 0;
      if ( v20->list.num > 0 )
      {
        name.len = 0;
        v56 = 0;
        do
        {
          idStr::operator=((idStr *)&name.data, v20->list.list[v56].data);
          md_8 = declManager->FindMaterial(declManager, name.alloced, 1);
          md_8->sort = -2.0;
          idStr::StripPath((idStr *)&name.data);
          idStr::StripFileExtension((idStr *)&name.data);
          md_4 = atoi((const char *)name.alloced);
          if ( !this->markerTimes.list )
          {
            granularity = this->markerTimes.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->markerTimes.size )
              {
                v22 = granularity < this->markerTimes.num;
                this->markerTimes.size = granularity;
                if ( v22 )
                  this->markerTimes.num = granularity;
                v23 = (markerData_t *)Memory::Allocate(24 * granularity);
                v24 = v23;
                LOBYTE(retaddr) = 2;
                if ( v23 )
                  `vector constructor iterator'(
                    v23,
                    0x18u,
                    granularity,
                    (void *(__thiscall *)(void *))markerData_t::markerData_t);
                else
                  v24 = 0;
                v25 = 0;
                v22 = this->markerTimes.num <= 0;
                LOBYTE(retaddr) = 1;
                this->markerTimes.list = v24;
                if ( !v22 )
                {
                  v26 = 0;
                  do
                  {
                    v27 = (markerData_t *)((char *)v26 + (unsigned int)this->markerTimes.list);
                    v27->time = *v26;
                    v27->mat = (const idMaterial *)v26[1];
                    LODWORD(v27->rect.x) = v26[2];
                    LODWORD(v27->rect.y) = v26[3];
                    LODWORD(v27->rect.w) = v26[4];
                    ++v25;
                    LODWORD(v27->rect.h) = v26[5];
                    v26 += 6;
                  }
                  while ( v25 < this->markerTimes.num );
                }
              }
            }
            else
            {
              this->markerTimes.list = 0;
              this->markerTimes.num = 0;
              this->markerTimes.size = 0;
            }
          }
          num = this->markerTimes.num;
          size = this->markerTimes.size;
          if ( num == size )
          {
            if ( !this->markerTimes.granularity )
              this->markerTimes.granularity = 16;
            v30 = size
                + this->markerTimes.granularity
                - (size + this->markerTimes.granularity) % this->markerTimes.granularity;
            if ( v30 > 0 )
            {
              if ( v30 != this->markerTimes.size )
              {
                list = this->markerTimes.list;
                this->markerTimes.size = v30;
                if ( v30 < num )
                  this->markerTimes.num = v30;
                v32 = (markerData_t *)Memory::Allocate(24 * v30);
                v33 = v32;
                LOBYTE(retaddr) = 3;
                if ( v32 )
                  `vector constructor iterator'(
                    v32,
                    0x18u,
                    v30,
                    (void *(__thiscall *)(void *))markerData_t::markerData_t);
                else
                  v33 = 0;
                v34 = 0;
                v22 = this->markerTimes.num <= 0;
                LOBYTE(retaddr) = 1;
                this->markerTimes.list = v33;
                if ( !v22 )
                {
                  v35 = 0;
                  do
                  {
                    v36 = &this->markerTimes.list[v35];
                    v36->time = list[v35].time;
                    v36->mat = list[v35].mat;
                    v36->rect.x = list[v35].rect.x;
                    v36->rect.y = list[v35].rect.y;
                    v36->rect.w = list[v35].rect.w;
                    ++v34;
                    v36->rect.h = list[v35++].rect.h;
                  }
                  while ( v34 < this->markerTimes.num );
                }
                if ( list )
                  Memory::Free(list);
              }
            }
            else
            {
              if ( this->markerTimes.list )
                Memory::Free(this->markerTimes.list);
              this->markerTimes.list = 0;
              this->markerTimes.num = 0;
              this->markerTimes.size = 0;
            }
          }
          ++v56;
          v37 = &this->markerTimes.list[this->markerTimes.num];
          v37->time = md_4;
          v37->mat = md_8;
          v37->rect.x = 0.0;
          v37->rect.y = 0.0;
          v38 = name.len;
          v37->rect.w = 0.0;
          v20 = (idFileList *)y1;
          LODWORD(v37->rect.h) = v38;
          ++this->markerTimes.num;
          ++i;
        }
        while ( i < *(_DWORD *)(y1 + 32) );
      }
      fileSystem->FreeFileList(fileSystem, v20);
      memset(this->imageBuff, 0, 0x20000u);
      activatea = 0;
      v39 = 511.0 / (double)(this->numStats - 1);
      markers = v39;
      v40 = -v39;
      if ( this->numStats - 1 > 0 )
      {
        loggedStats = this->loggedStats;
        do
        {
          v40 = v40 + markers;
          v42 = (unsigned __int64)(markers + v40);
          v43 = (unsigned __int64)v40;
          idMarkerWindow::Line(
            this,
            v43,
            (int)((double)loggedStats->health * 0.0099999998 * 63.0),
            v42,
            (int)((double)loggedStats[1].health * 0.0099999998 * 63.0),
            this->imageBuff,
            0xFF0000FF);
          idMarkerWindow::Line(
            this,
            v43,
            (int)((double)loggedStats->heartRate * 0.0080000004 * 63.0),
            v42,
            (int)((double)loggedStats[1].heartRate * 0.0080000004 * 63.0),
            this->imageBuff,
            0xFF00FF00);
          idMarkerWindow::Line(
            this,
            v43,
            (int)((double)loggedStats->stamina * 0.083333336 * 62.0),
            v42,
            (int)((double)loggedStats[1].stamina * 0.083333336 * 62.0),
            this->imageBuff,
            0xFFFF0000);
          idMarkerWindow::Line(
            this,
            v43,
            (int)((double)loggedStats->combat * 0.0099999998 * 63.0),
            v42,
            (int)((double)loggedStats[1].combat * 0.0099999998 * 63.0),
            this->imageBuff,
            0xFF00FFFF);
          ++loggedStats;
          ++activatea;
        }
        while ( activatea < this->numStats - 1 );
      }
      stages = this->background->stages;
      if ( stages )
        idImage::UploadScratch(stages->texture.image, (const unsigned __int8 *)this->imageBuff, 512, 64);
      Mem_Free(this->imageBuff);
      LOBYTE(v52) = 0;
      idStr::FreeData(&name);
      v52 = -1;
      idStr::FreeData(&markerPath);
    }
  }
}
