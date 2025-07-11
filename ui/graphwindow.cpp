
// FUNC: public: virtual __thiscall idGraphWindow::~idGraphWindow(void)
void __thiscall idGraphWindow::~idGraphWindow(idGraphWindow *this)
{
  float *storage; // eax

  this->__vftable = (idGraphWindow_vtbl *)&idGraphWindow::`vftable';
  storage = this->storage;
  if ( storage )
  {
    Mem_Free(storage);
    this->storage = 0;
  }
  `eh vector destructor iterator'(this->watchColors, 0x20u, 4, (void (__thiscall *)(void *))idWinFloat::~idWinFloat);
  `eh vector destructor iterator'(this->watchNames, 0x14u, 4, (void (__thiscall *)(void *))idWinFloat::~idWinFloat);
  idWindow::~idWindow(this);
}

// FUNC: private: virtual bool __thiscall idGraphWindow::ParseInternalVar(char const *,class idParser *)
bool __thiscall idGraphWindow::ParseInternalVar(idGraphWindow *this, const char *_name, idParser *src)
{
  bool result; // al

  if ( idStr::Icmp(_name, "statSize") )
  {
    if ( idStr::Icmp(_name, "scale") )
    {
      if ( idStr::Icmp(_name, "axis") && idStr::Icmp(_name, "axis1") )
      {
        if ( idStr::Icmp(_name, "axis2") )
        {
          if ( idStr::Icmp(_name, "axis3") )
          {
            if ( idStr::Icmp(_name, "axis4") )
            {
              if ( idStr::Icmp(_name, "axisColor") && idStr::Icmp(_name, "axisColor1") )
              {
                if ( idStr::Icmp(_name, "axisColor2") )
                {
                  if ( idStr::Icmp(_name, "axisColor3") )
                  {
                    if ( idStr::Icmp(_name, "axisColor4") )
                    {
                      return idWindow::ParseInternalVar(this, _name, src);
                    }
                    else
                    {
                      idWindow::ParseVec4(this, src, &this->axisColors[3]);
                      return 1;
                    }
                  }
                  else
                  {
                    idWindow::ParseVec4(this, src, &this->axisColors[2]);
                    return 1;
                  }
                }
                else
                {
                  idWindow::ParseVec4(this, src, &this->axisColors[1]);
                  return 1;
                }
              }
              else
              {
                idWindow::ParseVec4(this, src, this->axisColors);
                return 1;
              }
            }
            else
            {
              this->axisPositions[3] = idParser::ParseFloat(src);
              result = 1;
              this->axisUsed[3] = 1;
            }
          }
          else
          {
            this->axisPositions[2] = idParser::ParseFloat(src);
            result = 1;
            this->axisUsed[2] = 1;
          }
        }
        else
        {
          this->axisPositions[1] = idParser::ParseFloat(src);
          result = 1;
          this->axisUsed[1] = 1;
        }
      }
      else
      {
        this->axisPositions[0] = idParser::ParseFloat(src);
        result = 1;
        this->axisUsed[0] = 1;
      }
    }
    else
    {
      this->scale = idParser::ParseFloat(src);
      return 1;
    }
  }
  else
  {
    this->statSize = idParser::ParseInt(src);
    return 1;
  }
  return result;
}

// FUNC: public: virtual class idWinVar * __thiscall idGraphWindow::GetWinVarByName(char const *,bool,struct drawWin_t * *)
idWinVec4 *__thiscall idGraphWindow::GetWinVarByName(
        idGraphWindow *this,
        const char *_name,
        bool fixup,
        drawWin_t **owner)
{
  if ( idStr::Icmp(_name, "watch") && idStr::Icmp(_name, "watch1") )
  {
    if ( idStr::Icmp(_name, "watch2") )
    {
      if ( idStr::Icmp(_name, "watch3") )
      {
        if ( idStr::Icmp(_name, "watch4") )
        {
          if ( idStr::Icmp(_name, "watchcolor") && idStr::Icmp(_name, "watchcolor1") )
          {
            if ( idStr::Icmp(_name, "watchcolor2") )
            {
              if ( idStr::Icmp(_name, "watchcolor3") )
              {
                if ( idStr::Icmp(_name, "watchcolor4") )
                  return (idWinVec4 *)idWindow::GetWinVarByName(this, _name, fixup, owner);
                else
                  return &this->watchColors[3];
              }
              else
              {
                return &this->watchColors[2];
              }
            }
            else
            {
              return &this->watchColors[1];
            }
          }
          else
          {
            return this->watchColors;
          }
        }
        else
        {
          if ( this->numGraphWatches < 4 )
            this->numGraphWatches = 4;
          return (idWinVec4 *)&this->watchNames[3];
        }
      }
      else
      {
        if ( this->numGraphWatches < 3 )
          this->numGraphWatches = 3;
        return (idWinVec4 *)&this->watchNames[2];
      }
    }
    else
    {
      if ( this->numGraphWatches < 2 )
        this->numGraphWatches = 2;
      return (idWinVec4 *)&this->watchNames[1];
    }
  }
  else
  {
    if ( this->numGraphWatches < 1 )
      this->numGraphWatches = 1;
    return (idWinVec4 *)this->watchNames;
  }
}

// FUNC: public: virtual void __thiscall idGraphWindow::PostParse(void)
void __thiscall idGraphWindow::PostParse(idGraphWindow *this)
{
  int statSize; // eax
  const idCmdArgs *v3; // [esp+0h] [ebp-4h]

  SpawnStub(v3);
  if ( !this->storage )
  {
    statSize = this->statSize;
    if ( statSize )
      this->storage = (float *)Mem_Alloc(4 * statSize * this->numGraphWatches, 0x13u);
  }
  BYTE1(this->flags) |= 8u;
}

// FUNC: public: virtual void __thiscall idGraphWindow::Draw(int,float,float)
void __thiscall idGraphWindow::Draw(idGraphWindow *this, int time, float x, float y)
{
  idRectangle *p_textRect; // ecx
  float v6; // edx
  int statSize; // edi
  float v8; // edx
  int v9; // eax
  void *v10; // esp
  bool v11; // cc
  float v12; // eax
  int storageHead; // edi
  int v14; // ebx
  double v15; // st7
  float *v16; // ebx
  double v17; // st6
  int v18; // edi
  float *axisPositions; // ebx
  double v20; // st6
  float v21; // [esp+0h] [ebp-4Ch]
  float v22; // [esp+4h] [ebp-48h]
  float v23; // [esp+4h] [ebp-48h]
  float w; // [esp+8h] [ebp-44h]
  float X; // [esp+Ch] [ebp-40h]
  idVec4 *X_4; // [esp+10h] [ebp-3Ch]
  _BYTE v27[12]; // [esp+14h] [ebp-38h] BYREF
  idRectangle rect; // [esp+20h] [ebp-2Ch]
  float v29; // [esp+30h] [ebp-1Ch]
  float *lastScaleY; // [esp+34h] [ebp-18h]
  int i; // [esp+38h] [ebp-14h]
  float x1; // [esp+3Ch] [ebp-10h]
  idVec4 *color; // [esp+40h] [ebp-Ch]
  int j; // [esp+44h] [ebp-8h]
  float scaleY; // [esp+48h] [ebp-4h]

  this->dc->enableClipping = 0;
  p_textRect = &this->textRect;
  v6 = p_textRect->x;
  statSize = this->statSize;
  rect.y = p_textRect->y;
  rect.x = v6;
  v8 = p_textRect->w;
  rect.h = p_textRect->h;
  statSize *= 4;
  v9 = statSize + 3;
  LOBYTE(v9) = (statSize + 3) & 0xFC;
  rect.w = v8;
  v10 = alloca(v9);
  lastScaleY = (float *)v27;
  memset(v27, 0, statSize);
  v11 = this->numGraphWatches <= 0;
  j = 0;
  if ( !v11 )
  {
    v12 = *(float *)&this->statSize;
    x1 = v12;
    color = &this->watchColors[0].data;
    do
    {
      storageHead = this->storageHead;
      v14 = 0;
      i = 0;
      if ( SLODWORD(v12) > 0 )
      {
        v29 = rect.y + rect.h;
        do
        {
          if ( storageHead >= SLODWORD(v12) )
            storageHead = 0;
          x1 = floor((double)i * rect.w / (double)SLODWORD(x1));
          i = v14 + 1;
          v15 = floor((double)(v14 + 1) * rect.w / (double)this->statSize);
          v16 = lastScaleY;
          v17 = this->storage[storageHead + j * this->statSize] * this->scale + lastScaleY[storageHead];
          scaleY = v17;
          if ( v17 > rect.h )
            scaleY = rect.h;
          X = scaleY - lastScaleY[storageHead];
          w = v15 - x1;
          v22 = v29 - scaleY;
          v21 = rect.x + x1;
          idDeviceContext::DrawFilledRect(this->dc, v21, v22, w, X, color);
          v16[storageHead++] = scaleY;
          v14 = i;
          x1 = *(float *)&this->statSize;
          v12 = x1;
        }
        while ( i < SLODWORD(x1) );
      }
      color += 2;
      v11 = ++j < this->numGraphWatches;
    }
    while ( v11 );
  }
  v18 = 0;
  axisPositions = this->axisPositions;
  color = this->axisColors;
  do
  {
    if ( this->axisUsed[v18] )
    {
      v20 = this->scale * *axisPositions;
      X_4 = color;
      v23 = rect.y + rect.h - v20;
      idDeviceContext::DrawFilledRect(this->dc, rect.x, v23, rect.w, 1.0, color);
    }
    ++color;
    ++v18;
    ++axisPositions;
  }
  while ( v18 < 4 );
  this->dc->enableClipping = 1;
}

// FUNC: private: void __thiscall idGraphWindow::UpdateValue(void)
void __thiscall idGraphWindow::UpdateValue(idGraphWindow *this)
{
  int v1; // eax
  float *p_data; // edx
  int v3; // esi

  if ( this->storage )
  {
    v1 = 0;
    if ( this->numGraphWatches > 0 )
    {
      p_data = &this->watchNames[0].data;
      do
      {
        v3 = this->storageHead + v1 * this->statSize;
        ++v1;
        this->storage[v3] = *p_data;
        p_data += 5;
      }
      while ( v1 < this->numGraphWatches );
    }
    if ( ++this->storageHead >= this->statSize )
      this->storageHead = 0;
  }
}

// FUNC: private: void __thiscall idGraphWindow::CommonInit(void)
void __thiscall idGraphWindow::CommonInit(idGraphWindow *this)
{
  int v2; // esi
  idVec4 *axisColors; // ebx
  char **p_name; // edi
  idDict *v5; // ecx
  const char *v6; // eax
  const idKeyValue *v7; // eax
  const char *v8; // eax
  idVec4 *v9; // edx
  char *key; // [esp+1Ch] [ebp-2Ch]
  idWinVec4 *watchColors; // [esp+20h] [ebp-28h]
  idDict *v12; // [esp+24h] [ebp-24h]
  idVec4 other; // [esp+38h] [ebp-10h] BYREF

  v2 = 0;
  this->storage = 0;
  this->statSize = 0;
  this->storageHead = 0;
  this->scale = 1.0;
  this->numGraphWatches = 0;
  other.x = 1.0;
  other.y = 1.0;
  other.z = 1.0;
  other.w = 1.0;
  axisColors = this->axisColors;
  watchColors = this->watchColors;
  p_name = &this->watchNames[0].name;
  do
  {
    idWinVec4::operator=(watchColors, &other);
    v5 = (idDict *)*(p_name - 1);
    p_name[2] = 0;
    if ( !v5 )
      goto LABEL_11;
    v6 = *p_name;
    if ( !*p_name )
    {
      key = (char *)&entityFilter;
      goto LABEL_10;
    }
    if ( *v6 != 42 )
      goto LABEL_8;
    v7 = idDict::FindKey(v5, v6 + 1);
    if ( !v7 )
    {
      v6 = &entityFilter;
LABEL_8:
      key = (char *)v6;
      goto LABEL_10;
    }
    key = v7->value->data;
LABEL_10:
    v12 = (idDict *)*(p_name - 1);
    v8 = va("%f", *((float *)p_name + 2));
    idDict::Set(v12, key, v8);
LABEL_11:
    ++watchColors;
    this->axisUsed[v2] = 0;
    v9 = axisColors;
    axisColors->x = 1.0;
    axisColors->y = 1.0;
    ++v2;
    axisColors->z = 1.0;
    p_name += 5;
    ++axisColors;
    v9->w = 1.0;
  }
  while ( v2 < 4 );
}

// FUNC: public: __thiscall idGraphWindow::idGraphWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idGraphWindow::idGraphWindow(idGraphWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idWindow::idWindow(this, d, g);
  this->__vftable = (idGraphWindow_vtbl *)&idGraphWindow::`vftable';
  `eh vector constructor iterator'(
    this->watchNames,
    0x14u,
    4,
    (void (__thiscall *)(void *))idWinFloat::idWinFloat,
    (void (__thiscall *)(void *))idWinFloat::~idWinFloat);
  `eh vector constructor iterator'(
    this->watchColors,
    0x20u,
    4,
    (void (__thiscall *)(void *))idWinVec4::idWinVec4,
    (void (__thiscall *)(void *))idWinFloat::~idWinFloat);
  this->dc = d;
  this->gui = g;
  idGraphWindow::CommonInit(this);
}

// FUNC: public: virtual char const * __thiscall idGraphWindow::HandleEvent(struct sysEvent_s const *,bool *)
const char *__thiscall idGraphWindow::HandleEvent(idGraphWindow *this, const sysEvent_s *event, bool *updateVisuals)
{
  char v4; // dl
  char v5; // bl
  int evValue; // eax

  v4 = 0;
  v5 = 0;
  if ( event->evType != SE_KEY )
  {
    if ( event->evType != SE_CHAR )
      return &entityFilter;
    v5 = 1;
LABEL_18:
    this->RunScript(this, 2);
    goto LABEL_19;
  }
  evValue = event->evValue;
  if ( evValue == 136 || evValue == 170 || evValue == 187 )
  {
    if ( !event->evValue2 )
    {
      this->RunScript(this, 9);
      return this->cmd.data;
    }
    v4 = 1;
  }
  if ( evValue == 135 || evValue == 168 || evValue == 188 )
  {
    if ( !event->evValue2 )
    {
LABEL_20:
      this->RunScript(this, 9);
      return this->cmd.data;
    }
    v4 = 1;
  }
  if ( !event->evValue2 )
    return &entityFilter;
  if ( v4 )
    goto LABEL_18;
LABEL_19:
  idGraphWindow::UpdateValue(this);
  if ( v5 )
    goto LABEL_20;
  return this->cmd.data;
}

// FUNC: public: virtual void __thiscall idGraphWindow::StateChanged(bool)
void __thiscall idGraphWindow::StateChanged(idGraphWindow *this, bool redraw)
{
  int statSize; // eax

  idWindow::StateChanged(this, redraw);
  if ( !this->storage )
  {
    statSize = this->statSize;
    if ( statSize )
      this->storage = (float *)Mem_Alloc(4 * statSize * this->numGraphWatches, 0x13u);
  }
  idGraphWindow::UpdateValue(this);
}
