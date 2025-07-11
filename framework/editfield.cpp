
// FUNC: FindMatches
void __cdecl FindMatches(const char *s)
{
  const char *v1; // esi
  int v2; // edi
  int v3; // ebx

  v1 = s;
  if ( !idStr::Icmpn(s, globalAutoComplete.completionString, strlen(globalAutoComplete.completionString)) )
  {
    if ( ++globalAutoComplete.matchCount == 1 )
    {
      idStr::Copynz(globalAutoComplete.currentMatch, s, 256);
    }
    else
    {
      v2 = 0;
      if ( *s )
      {
        while ( 1 )
        {
          v3 = tolower(v1[globalAutoComplete.currentMatch - s]);
          if ( v3 != tolower(*v1) )
            break;
          ++v1;
          ++v2;
          if ( !*v1 )
          {
            globalAutoComplete.currentMatch[v2] = 0;
            return;
          }
        }
        globalAutoComplete.currentMatch[v2] = 0;
      }
      globalAutoComplete.currentMatch[v2] = 0;
    }
  }
}

// FUNC: FindIndexMatch
void __cdecl FindIndexMatch(const char *s)
{
  if ( !idStr::Icmpn(s, globalAutoComplete.completionString, strlen(globalAutoComplete.completionString)) )
  {
    if ( globalAutoComplete.findMatchIndex == globalAutoComplete.matchIndex )
      idStr::Copynz(globalAutoComplete.currentMatch, s, 256);
    ++globalAutoComplete.findMatchIndex;
  }
}

// FUNC: PrintMatches
void __cdecl PrintMatches(const char *s)
{
  if ( !idStr::Icmpn(s, globalAutoComplete.currentMatch, strlen(globalAutoComplete.currentMatch)) )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "    %s\n", s);
}

// FUNC: PrintCvarMatches
void __cdecl PrintCvarMatches(const char *s)
{
  int v1; // edi
  const char *v2; // eax

  if ( !idStr::Icmpn(s, globalAutoComplete.currentMatch, strlen(globalAutoComplete.currentMatch)) )
  {
    v1 = *(_DWORD *)common.type;
    v2 = cvarSystem->GetCVarString(cvarSystem, s);
    (*(void (**)(netadrtype_t, const char *, ...))(v1 + 124))(common.type, "    %s^7 = \"%s\"\n", s, v2);
  }
}

// FUNC: public: void __thiscall idEditField::Clear(void)
void __thiscall idEditField::Clear(idEditField *this)
{
  this->buffer[0] = 0;
  this->cursor = 0;
  this->scroll = 0;
  this->autoComplete.length = 0;
  this->autoComplete.valid = 0;
}

// FUNC: public: void __thiscall idEditField::SetWidthInChars(int)
void __thiscall idEditField::SetWidthInChars(idEditField *this, int w)
{
  this->widthInChars = w;
}

// FUNC: public: void __thiscall idEditField::SetCursor(int)
void __thiscall idEditField::SetCursor(idEditField *this, int c)
{
  this->cursor = c;
}

// FUNC: public: int __thiscall idEditField::GetCursor(void)const
int __thiscall idEditField::GetCursor(idCmdArgs *this)
{
  return this->argc;
}

// FUNC: public: void __thiscall idEditField::ClearAutoComplete(void)
void __thiscall idEditField::ClearAutoComplete(idEditField *this)
{
  int length; // esi
  int v2; // eax
  bool v3; // cc

  length = this->autoComplete.length;
  if ( length <= 0 || length > (int)strlen(this->buffer) )
  {
    this->autoComplete.length = 0;
    this->autoComplete.valid = 0;
  }
  else
  {
    this->buffer[length] = 0;
    v2 = this->autoComplete.length;
    v3 = this->cursor <= v2;
    this->autoComplete.valid = 0;
    this->autoComplete.length = 0;
    if ( !v3 )
      this->cursor = v2;
  }
}

// FUNC: public: void __thiscall idEditField::CharEvent(int)
void __thiscall idEditField::CharEvent(idEditField *this, int ch)
{
  int v3; // edi
  int v4; // eax
  int scroll; // eax

  if ( ch == 22 )
  {
    idEditField::Paste(this);
    return;
  }
  if ( ch == 3 )
  {
    this->buffer[0] = 0;
    this->cursor = 0;
    this->scroll = 0;
    this->autoComplete.length = 0;
    this->autoComplete.valid = 0;
    return;
  }
  v3 = strlen(this->buffer);
  switch ( ch )
  {
    case 8:
    case 127:
      if ( this->cursor > 0 )
      {
        memmove(
          (unsigned __int8 *)&this->widthInChars + this->cursor + 3,
          (unsigned __int8 *)&this->buffer[this->cursor],
          v3 - this->cursor + 1);
        --this->cursor;
        scroll = this->scroll;
        if ( this->cursor < scroll )
          this->scroll = scroll - 1;
      }
      break;
    case 1:
      this->cursor = 0;
      this->scroll = 0;
      return;
    case 5:
      this->cursor = v3;
      this->scroll = v3 - this->widthInChars;
      return;
    default:
      if ( ch >= 32 )
      {
        if ( idKeyInput::GetOverstrikeMode() )
        {
          if ( this->cursor == 255 )
            return;
          this->buffer[this->cursor] = ch;
        }
        else
        {
          if ( v3 == 255 )
            return;
          memmove(
            (unsigned __int8 *)&this->buffer[this->cursor + 1],
            (unsigned __int8 *)&this->buffer[this->cursor],
            v3 - this->cursor + 1);
          this->buffer[this->cursor] = ch;
        }
        v4 = ++this->cursor;
        if ( this->cursor >= this->widthInChars )
          ++this->scroll;
        if ( v4 == v3 + 1 )
          this->buffer[v4] = 0;
      }
      break;
  }
}

// FUNC: public: void __thiscall idEditField::Paste(void)
void __thiscall idEditField::Paste(idEditField *this)
{
  const char *ClipboardData; // eax
  char *v3; // ebx
  signed int v4; // edi
  signed int i; // esi

  ClipboardData = Sys_GetClipboardData();
  v3 = (char *)ClipboardData;
  if ( ClipboardData )
  {
    v4 = strlen(ClipboardData);
    for ( i = 0; i < v4; ++i )
      idEditField::CharEvent(this, v3[i]);
    Mem_Free(v3);
  }
}

// FUNC: public: char * __thiscall idEditField::GetBuffer(void)
char *__thiscall idEditField::GetBuffer(idEditField *this)
{
  return this->buffer;
}

// FUNC: public: void __thiscall idEditField::SetBuffer(char const *)
void __thiscall idEditField::SetBuffer(idEditField *this, const char *buf)
{
  char *buffer; // edi

  buffer = this->buffer;
  this->buffer[0] = 0;
  this->cursor = 0;
  this->scroll = 0;
  this->autoComplete.length = 0;
  this->autoComplete.valid = 0;
  idStr::Copynz(this->buffer, buf, 256);
  this->cursor = strlen(buffer);
}

// FUNC: public: void __thiscall idEditField::Draw(int,int,int,bool,class idMaterial const *)
void __thiscall idEditField::Draw(
        idEditField *this,
        int x,
        int y,
        int width,
        bool showCursor,
        const idMaterial *shader)
{
  int widthInChars; // ebp
  signed int v8; // ebx
  int scroll; // edi
  int IsEscape; // eax
  idRenderSystem *v11; // ecx
  int v12; // ebp
  int v13; // eax
  int cursorChar; // [esp+20h] [ebp-104h]
  char str[256]; // [esp+24h] [ebp-100h] BYREF

  widthInChars = this->widthInChars;
  v8 = strlen(this->buffer) + 1;
  if ( v8 > widthInChars )
  {
    if ( widthInChars + this->scroll > v8 )
    {
      this->scroll = v8 - widthInChars;
      if ( v8 - widthInChars < 0 )
        this->scroll = 0;
    }
    scroll = this->scroll;
    IsEscape = idStr::IsEscape(&this->buffer[scroll], 0);
    if ( IsEscape )
      scroll += IsEscape;
  }
  else
  {
    scroll = 0;
  }
  if ( scroll + widthInChars > v8 )
    widthInChars = v8 - scroll;
  if ( widthInChars >= 256 )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "drawLen >= MAX_EDIT_LINE");
  SIMDProcessor->Memcpy(SIMDProcessor, str, &this->buffer[scroll], widthInChars);
  v11 = renderSystem;
  str[widthInChars] = 0;
  v11->DrawSmallStringExt(v11, x, y, str, &colorWhite, 0, shader);
  if ( showCursor && (com_ticNumber & 0x10) == 0 )
  {
    v12 = 0;
    for ( cursorChar = idKeyInput::GetOverstrikeMode() + 10; v12 < this->cursor; ++v12 )
    {
      v13 = idStr::IsEscape(&str[v12], 0);
      if ( v13 )
      {
        ++v12;
        scroll += v13;
      }
    }
    renderSystem->DrawSmallChar(renderSystem, x + 8 * (this->cursor - scroll), y, cursorChar, shader);
  }
}

// FUNC: public: __thiscall idEditField::idEditField(void)
void __thiscall idEditField::idEditField(idEditField *this)
{
  this->widthInChars = 0;
  this->buffer[0] = 0;
  this->cursor = 0;
  this->scroll = 0;
  this->autoComplete.length = 0;
  this->autoComplete.valid = 0;
}

// FUNC: public: void __thiscall idEditField::AutoComplete(void)
void __thiscall idEditField::AutoComplete(idEditField *this)
{
  char v2; // al
  char *buffer; // ebx
  BOOL v4; // eax
  const char *v5; // esi
  const char *v6; // eax
  const char *v7; // eax
  int v8; // eax
  const char *v9; // edi
  int v10; // eax
  bool v11; // zf
  int matchCount; // eax
  char *dest; // [esp+18h] [ebp-B18h]
  char completionArgString[256]; // [esp+20h] [ebp-B10h] BYREF
  char pbbuf[265]; // [esp+120h] [ebp-A10h] BYREF
  idCmdArgs args; // [esp+22Ch] [ebp-904h] BYREF

  v2 = this->buffer[0];
  buffer = this->buffer;
  args.argc = 0;
  dest = this->buffer;
  v4 = v2 == 47 || v2 == 92;
  v5 = &this->buffer[v4];
  if ( idStr::Icmpn(v5, "pb_", 3) )
  {
    if ( this->autoComplete.valid )
    {
      matchCount = this->autoComplete.matchCount;
      if ( matchCount != 1 )
      {
        if ( ++this->autoComplete.matchIndex == matchCount )
          this->autoComplete.matchIndex = 0;
        this->autoComplete.findMatchIndex = 0;
        qmemcpy(&globalAutoComplete, &this->autoComplete, sizeof(globalAutoComplete));
        cmdSystem->CommandCompletion(cmdSystem, FindIndexMatch);
        cmdSystem->ArgCompletion(cmdSystem, this->autoComplete.completionString, FindIndexMatch);
        cvarSystem->CommandCompletion(cvarSystem, FindIndexMatch);
        cvarSystem->ArgCompletion(cvarSystem, this->autoComplete.completionString, FindIndexMatch);
        qmemcpy(&this->autoComplete, &globalAutoComplete, sizeof(this->autoComplete));
        idStr::snPrintf(dest, 256, this->autoComplete.currentMatch);
        if ( this->autoComplete.length > (signed int)strlen(dest) )
          this->autoComplete.length = strlen(dest);
        this->cursor = this->autoComplete.length;
      }
    }
    else
    {
      idCmdArgs::TokenizeString(&args, buffer, 0);
      v6 = args.argv[0];
      if ( args.argc <= 0 )
        v6 = &entityFilter;
      idStr::Copynz(this->autoComplete.completionString, v6, 256);
      v7 = idCmdArgs::Args(&args, 1, -1, 0);
      idStr::Copynz(completionArgString, v7, 256);
      this->autoComplete.matchCount = 0;
      this->autoComplete.matchIndex = 0;
      this->autoComplete.currentMatch[0] = 0;
      if ( strlen(this->autoComplete.completionString) )
      {
        qmemcpy(&globalAutoComplete, &this->autoComplete, sizeof(globalAutoComplete));
        cmdSystem->CommandCompletion(cmdSystem, FindMatches);
        cvarSystem->CommandCompletion(cvarSystem, FindMatches);
        qmemcpy(&this->autoComplete, &globalAutoComplete, sizeof(this->autoComplete));
        v8 = this->autoComplete.matchCount;
        if ( v8 )
        {
          if ( v8 == 1 || completionArgString[0] )
          {
            idStr::Append(this->autoComplete.completionString, 256, " ");
            idStr::Append(this->autoComplete.completionString, 256, completionArgString);
            this->autoComplete.matchCount = 0;
            qmemcpy(&globalAutoComplete, &this->autoComplete, sizeof(globalAutoComplete));
            cmdSystem->ArgCompletion(cmdSystem, this->autoComplete.completionString, FindMatches);
            cvarSystem->ArgCompletion(cvarSystem, this->autoComplete.completionString, FindMatches);
            qmemcpy(&this->autoComplete, &globalAutoComplete, sizeof(this->autoComplete));
            idStr::snPrintf(dest, 256, "%s", this->autoComplete.currentMatch);
            if ( !this->autoComplete.matchCount )
            {
              idStr::Append(dest, 256, " ");
              idStr::Append(dest, 256, completionArgString);
              this->cursor = strlen(dest);
              return;
            }
            v9 = dest;
          }
          else
          {
            v9 = dest;
            idStr::snPrintf(dest, 256, "%s", this->autoComplete.currentMatch);
            if ( strlen(completionArgString) )
            {
              idStr::Append(dest, 256, " ");
              idStr::Append(dest, 256, completionArgString);
            }
          }
          v10 = strlen(v9);
          v11 = this->autoComplete.matchCount == 1;
          this->autoComplete.length = v10;
          this->autoComplete.valid = !v11;
          this->cursor = v10;
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "]%s\n", v9);
          qmemcpy(&globalAutoComplete, &this->autoComplete, sizeof(globalAutoComplete));
          cmdSystem->CommandCompletion(cmdSystem, PrintMatches);
          cmdSystem->ArgCompletion(cmdSystem, this->autoComplete.completionString, PrintMatches);
          cvarSystem->CommandCompletion(cvarSystem, PrintCvarMatches);
          cvarSystem->ArgCompletion(cvarSystem, this->autoComplete.completionString, PrintMatches);
        }
      }
    }
  }
  else
  {
    strncpy(pbbuf, v5, 0xFFu);
    pbbuf[255] = 0;
    if ( idStr::Icmpn(pbbuf, "pb_sv_", 6) )
      PbClientCompleteCommand(pbbuf, 255);
    else
      PbServerCompleteCommand(pbbuf, 255);
    idStr::snPrintf(buffer, 256, "%s", pbbuf);
    this->cursor = strlen(buffer);
  }
}

// FUNC: public: void __thiscall idEditField::KeyDownEvent(int)
void __thiscall idEditField::KeyDownEvent(idEditField *this, int key)
{
  int v3; // edi
  bool v4; // cc
  int v5; // eax
  int v6; // eax
  int widthInChars; // ecx
  int cursor; // eax
  bool v9; // sf
  int v10; // eax
  int v11; // eax
  int v12; // eax
  bool OverstrikeMode; // al
  int v14; // eax
  int v15; // ecx
  bool v16; // zf
  idEditField *v17; // ecx

  if ( (key == 143 || key == 175) && (idKeyInput::IsDown(142) || idKeyInput::IsDown(3)) )
  {
    idEditField::ClearAutoComplete(this);
    idEditField::Paste(v17);
    return;
  }
  v3 = strlen(this->buffer);
  switch ( key )
  {
    case 144:
      if ( !this->autoComplete.length )
      {
        if ( this->cursor < v3 )
          memmove(
            (unsigned __int8 *)&this->buffer[this->cursor],
            (unsigned __int8 *)&this->buffer[this->cursor + 1],
            v3 - this->cursor);
        return;
      }
LABEL_60:
      idEditField::ClearAutoComplete(this);
      return;
    case 136:
      if ( idKeyInput::IsDown(141) || idKeyInput::IsDown(2) )
      {
        v4 = this->cursor <= v3;
        if ( this->cursor >= v3 )
          goto LABEL_20;
        do
        {
          if ( this->buffer[this->cursor] == 32 )
            break;
          v5 = this->cursor + 1;
          this->cursor = v5;
        }
        while ( v5 < v3 );
        v4 = this->cursor <= v3;
        if ( this->cursor >= v3 )
          goto LABEL_20;
        do
        {
          if ( this->buffer[this->cursor] != 32 )
            break;
          v6 = this->cursor + 1;
          this->cursor = v6;
        }
        while ( v6 < v3 );
      }
      else
      {
        ++this->cursor;
      }
      v4 = this->cursor <= v3;
LABEL_20:
      if ( !v4 )
        this->cursor = v3;
      widthInChars = this->widthInChars;
      cursor = this->cursor;
      if ( this->cursor >= widthInChars + this->scroll )
        this->scroll = cursor - widthInChars + 1;
      if ( this->autoComplete.length > 0 )
        this->autoComplete.length = cursor;
      return;
    case 135:
      if ( idKeyInput::IsDown(141) || idKeyInput::IsDown(2) )
      {
        v9 = this->cursor < 0;
        if ( this->cursor <= 0 )
          goto LABEL_37;
        do
        {
          if ( *((_BYTE *)&this->widthInChars + this->cursor + 3) != 32 )
            break;
          v10 = this->cursor - 1;
          this->cursor = v10;
        }
        while ( v10 > 0 );
        v9 = this->cursor < 0;
        if ( this->cursor <= 0 )
          goto LABEL_37;
        do
        {
          if ( *((_BYTE *)&this->widthInChars + this->cursor + 3) == 32 )
            break;
          v11 = this->cursor - 1;
          this->cursor = v11;
        }
        while ( v11 > 0 );
      }
      else
      {
        --this->cursor;
      }
      v9 = this->cursor < 0;
LABEL_37:
      if ( v9 )
        this->cursor = 0;
      v12 = this->cursor;
      if ( this->cursor < this->scroll )
        this->scroll = v12;
      if ( this->autoComplete.length )
        this->autoComplete.length = v12;
      return;
  }
  if ( key == 147 || tolower(key) == 97 && (idKeyInput::IsDown(141) || idKeyInput::IsDown(2)) )
  {
    v16 = this->autoComplete.length == 0;
    this->cursor = 0;
    this->scroll = 0;
    if ( !v16 )
    {
      this->autoComplete.length = 0;
      this->autoComplete.valid = 0;
    }
  }
  else if ( key == 148 || tolower(key) == 101 && (idKeyInput::IsDown(141) || idKeyInput::IsDown(2)) )
  {
    v14 = this->widthInChars;
    v15 = v14 + this->scroll;
    this->cursor = v3;
    if ( v3 >= v15 )
      this->scroll = v3 - v14 + 1;
    if ( this->autoComplete.length )
    {
      this->autoComplete.length = v3;
      this->autoComplete.valid = 0;
    }
  }
  else
  {
    if ( key == 143 )
    {
      OverstrikeMode = idKeyInput::GetOverstrikeMode();
      idKeyInput::SetOverstrikeMode(!OverstrikeMode);
      return;
    }
    if ( key != 129 && key != 140 && key != 141 && key != 142 && key != 253 && key != 2 && key != 3 )
      goto LABEL_60;
  }
}
