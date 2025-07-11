
// FUNC: private: virtual bool __thiscall idFieldWindow::ParseInternalVar(char const *,class idParser *)
bool __thiscall idFieldWindow::ParseInternalVar(idFieldWindow *this, const char *_name, idParser *src)
{
  if ( idStr::Icmp(_name, "cursorvar") )
  {
    if ( idStr::Icmp(_name, "showcursor") )
    {
      return idWindow::ParseInternalVar(this, _name, src);
    }
    else
    {
      this->showCursor = idParser::ParseBool(src);
      return 1;
    }
  }
  else
  {
    idWindow::ParseString(this, src, &this->cursorVar);
    return 1;
  }
}

// FUNC: public: __thiscall idFieldWindow::idFieldWindow(class idDeviceContext *,class idUserInterfaceLocal *)
void __thiscall idFieldWindow::idFieldWindow(idFieldWindow *this, idDeviceContext *d, idUserInterfaceLocal *g)
{
  idWindow::idWindow(this, d, g);
  this->__vftable = (idFieldWindow_vtbl *)&idFieldWindow::`vftable';
  this->cursorVar.len = 0;
  this->cursorVar.alloced = 20;
  this->cursorVar.data = this->cursorVar.baseBuffer;
  this->cursorVar.baseBuffer[0] = 0;
  this->gui = g;
  this->dc = d;
  this->cursorPos = 0;
  this->lastTextLength = 0;
  this->lastCursorPos = 0;
  this->paintOffset = 0;
  this->showCursor = 0;
}

// FUNC: public: virtual __thiscall idFieldWindow::~idFieldWindow(void)
void __thiscall idFieldWindow::~idFieldWindow(idFieldWindow *this)
{
  this->__vftable = (idFieldWindow_vtbl *)&idFieldWindow::`vftable';
  idStr::FreeData(&this->cursorVar);
  idWindow::~idWindow(this);
}

// FUNC: private: void __thiscall idFieldWindow::CalcPaintOffset(int)
void __thiscall idFieldWindow::CalcPaintOffset(idFieldWindow *this, int len)
{
  int cursorPos; // eax
  double textSpacing; // st7
  float data; // ecx
  int v6; // edi
  char *v7; // ecx
  int v8; // eax
  float scale; // [esp+Ch] [ebp-4h]

  cursorPos = this->cursorPos;
  textSpacing = this->textSpacing;
  data = this->textScale.data;
  v6 = len;
  this->lastCursorPos = cursorPos;
  scale = data;
  v7 = this->text.data.data;
  this->lastTextLength = len;
  this->paintOffset = 0;
  if ( (double)idDeviceContext::TextWidth(this->dc, v7, scale, -1, (int)textSpacing) > this->textRect.w )
  {
    do
    {
      if ( v6 <= 0 )
        break;
      v8 = idDeviceContext::TextWidth(
             this->dc,
             this->text.data.data,
             this->textScale.data,
             --v6,
             (int)this->textSpacing);
      ++this->paintOffset;
    }
    while ( (double)v8 > this->textRect.w );
  }
}

// FUNC: public: virtual void __thiscall idFieldWindow::Draw(int,float,float)
void __thiscall idFieldWindow::Draw(idFieldWindow *this, int time, float x, float y)
{
  int v5; // eax
  char *data; // ebx
  int v7; // edi
  idDict *v8; // eax
  const idKeyValue *Key; // eax
  const char *v10; // eax
  int v11; // eax
  bool v12; // zf
  int v13; // eax
  float scale; // [esp+Ch] [ebp-4h]

  scale = this->textScale.data;
  v5 = idWinStr::Length(&this->text);
  data = this->cursorVar.data;
  v7 = v5;
  v8 = (idDict *)this->gui->State(this->gui);
  Key = idDict::FindKey(v8, data);
  if ( Key )
    v10 = Key->value->data;
  else
    v10 = "0";
  v11 = atoi(v10);
  v12 = v7 == this->lastTextLength;
  this->cursorPos = v11;
  if ( !v12 || v11 != this->lastCursorPos )
    idFieldWindow::CalcPaintOffset(this, v7);
  if ( this->paintOffset >= v7 )
    this->paintOffset = 0;
  if ( this->cursorPos > v7 )
    this->cursorPos = v7;
  if ( (this->flags & 0x20) != 0 || this->showCursor )
    v13 = this->cursorPos - this->paintOffset;
  else
    v13 = -1;
  idDeviceContext::DrawTextA(
    this->dc,
    &this->text.data.data[this->paintOffset],
    scale,
    0,
    this->textStyle,
    this->foreColor.data,
    this->textRect,
    0,
    v13,
    0,
    0,
    0,
    0,
    0);
}
