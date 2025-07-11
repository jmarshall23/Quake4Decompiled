
// FUNC: public: bool __thiscall idEFXFile::GetEffectName(int,class idStr * *)
char __thiscall idEFXFile::GetEffectName(idEFXFile *this, int index, idStr **name)
{
  if ( index < 0 || index >= this->effects.num )
    return 0;
  *name = &this->effects.list[index]->name;
  return 1;
}

// FUNC: public: bool __thiscall idEFXFile::FindEffect(class idStr &,class idSoundEffect * *,int *)
char __thiscall idEFXFile::FindEffect(idEFXFile *this, idStr *name, idSoundEffect **effect, int *index)
{
  int v5; // esi
  idSoundEffect *v6; // eax

  v5 = 0;
  if ( this->effects.num <= 0 )
    return 0;
  while ( 1 )
  {
    v6 = this->effects.list[v5];
    if ( v6 )
    {
      if ( !idStr::Cmp(v6->name.data, name->data) )
        break;
    }
    if ( ++v5 >= this->effects.num )
      return 0;
  }
  *effect = this->effects.list[v5];
  *index = v5;
  return 1;
}

// FUNC: public: __thiscall idEFXFile::idEFXFile(void)
void __thiscall idEFXFile::idEFXFile(idEFXFile *this)
{
  this->effects.granularity = 16;
  this->effects.list = 0;
  this->effects.num = 0;
  this->effects.size = 0;
}

// FUNC: public: bool __thiscall idEFXFile::ReadEffect(class idLexer &,class idSoundEffect *)
char __thiscall idEFXFile::ReadEffect(idEFXFile *this, idLexer *src, idSoundEffect *effect)
{
  unsigned int *v4; // ebp
  int len; // esi
  bool v6; // cc
  int v7; // eax
  idToken token; // [esp+8h] [ebp-B0h] BYREF
  int v9; // [esp+58h] [ebp-60h]
  idToken name; // [esp+5Ch] [ebp-5Ch] BYREF
  int v11; // [esp+B4h] [ebp-4h]

  name.floatvalue = 0.0;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  token.floatvalue = 0.0;
  v11 = 1;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  if ( !idLexer::ReadToken(src, &token) )
    goto LABEL_2;
  if ( idStr::Cmp(token.data, "reverb") )
  {
    idLexer::Error(src, "idEFXFile::ReadEffect: Unknown effect definition");
    goto LABEL_2;
  }
  v4 = (unsigned int *)Mem_Alloc(112, 0x12u);
  if ( !v4 )
    goto LABEL_2;
  idLexer::ReadTokenOnLine(src, &token);
  idToken::operator=((int)&name, (int)&token);
  if ( !idLexer::ReadToken(src, &token) )
  {
    Mem_Free(v4);
    goto LABEL_2;
  }
  if ( idStr::Cmp(token.data, "{") )
  {
    idLexer::Error(src, "idEFXFile::ReadEffect: { not found, found %s", token.data);
    Mem_Free(v4);
LABEL_2:
    LOBYTE(v11) = 0;
    idStr::FreeData(&token);
    v11 = -1;
    idStr::FreeData(&name);
    return 0;
  }
  if ( idLexer::ReadToken(src, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Cmp(token.data, "environment") )
      {
        if ( idStr::Cmp(token.data, "environment size") )
        {
          if ( idStr::Cmp(token.data, "environment diffusion") )
          {
            if ( idStr::Cmp(token.data, "room") )
            {
              if ( idStr::Cmp(token.data, "room hf") )
              {
                if ( idStr::Cmp(token.data, "room lf") )
                {
                  if ( idStr::Cmp(token.data, "decay time") )
                  {
                    if ( idStr::Cmp(token.data, "decay hf ratio") )
                    {
                      if ( idStr::Cmp(token.data, "decay lf ratio") )
                      {
                        if ( idStr::Cmp(token.data, "reflections") )
                        {
                          if ( idStr::Cmp(token.data, "reflections delay") )
                          {
                            if ( idStr::Cmp(token.data, "reflections pan") )
                            {
                              if ( idStr::Cmp(token.data, "reverb") )
                              {
                                if ( idStr::Cmp(token.data, "reverb delay") )
                                {
                                  if ( idStr::Cmp(token.data, "reverb pan") )
                                  {
                                    if ( idStr::Cmp(token.data, "echo time") )
                                    {
                                      if ( idStr::Cmp(token.data, "echo depth") )
                                      {
                                        if ( idStr::Cmp(token.data, "modulation time") )
                                        {
                                          if ( idStr::Cmp(token.data, "modulation depth") )
                                          {
                                            if ( idStr::Cmp(token.data, "air absorption hf") )
                                            {
                                              if ( idStr::Cmp(token.data, "hf reference") )
                                              {
                                                if ( idStr::Cmp(token.data, "lf reference") )
                                                {
                                                  if ( idStr::Cmp(token.data, "room rolloff factor") )
                                                  {
                                                    if ( idStr::Cmp(token.data, "flags") )
                                                    {
                                                      idLexer::ReadTokenOnLine(src, &token);
                                                      idLexer::Error(
                                                        src,
                                                        "idEFXFile::ReadEffect: Invalid parameter in reverb definition");
                                                      Mem_Free(v4);
                                                    }
                                                    else
                                                    {
                                                      idLexer::ReadTokenOnLine(src, &token);
                                                      if ( token.type == 3 )
                                                      {
                                                        if ( (token.subtype & 0x10000) == 0 )
                                                          idToken::NumberValue(&token);
                                                        v4[27] = token.intvalue;
                                                      }
                                                      else
                                                      {
                                                        v4[27] = 0;
                                                      }
                                                    }
                                                  }
                                                  else
                                                  {
                                                    *((float *)v4 + 26) = idLexer::ParseFloat(src, 0);
                                                  }
                                                }
                                                else
                                                {
                                                  *((float *)v4 + 25) = idLexer::ParseFloat(src, 0);
                                                }
                                              }
                                              else
                                              {
                                                *((float *)v4 + 24) = idLexer::ParseFloat(src, 0);
                                              }
                                            }
                                            else
                                            {
                                              *((float *)v4 + 23) = idLexer::ParseFloat(src, 0);
                                            }
                                          }
                                          else
                                          {
                                            *((float *)v4 + 22) = idLexer::ParseFloat(src, 0);
                                          }
                                        }
                                        else
                                        {
                                          *((float *)v4 + 21) = idLexer::ParseFloat(src, 0);
                                        }
                                      }
                                      else
                                      {
                                        *((float *)v4 + 20) = idLexer::ParseFloat(src, 0);
                                      }
                                    }
                                    else
                                    {
                                      *((float *)v4 + 19) = idLexer::ParseFloat(src, 0);
                                    }
                                  }
                                  else
                                  {
                                    *((float *)v4 + 16) = idLexer::ParseFloat(src, 0);
                                    *((float *)v4 + 17) = idLexer::ParseFloat(src, 0);
                                    *((float *)v4 + 18) = idLexer::ParseFloat(src, 0);
                                  }
                                }
                                else
                                {
                                  *((float *)v4 + 15) = idLexer::ParseFloat(src, 0);
                                }
                              }
                              else
                              {
                                v4[14] = idLexer::ParseInt(src);
                              }
                            }
                            else
                            {
                              *((float *)v4 + 11) = idLexer::ParseFloat(src, 0);
                              *((float *)v4 + 12) = idLexer::ParseFloat(src, 0);
                              *((float *)v4 + 13) = idLexer::ParseFloat(src, 0);
                            }
                          }
                          else
                          {
                            *((float *)v4 + 10) = idLexer::ParseFloat(src, 0);
                          }
                        }
                        else
                        {
                          v4[9] = idLexer::ParseInt(src);
                        }
                      }
                      else
                      {
                        *((float *)v4 + 8) = idLexer::ParseFloat(src, 0);
                      }
                    }
                    else
                    {
                      *((float *)v4 + 7) = idLexer::ParseFloat(src, 0);
                    }
                  }
                  else
                  {
                    *((float *)v4 + 6) = idLexer::ParseFloat(src, 0);
                  }
                }
                else
                {
                  v4[5] = idLexer::ParseInt(src);
                }
              }
              else
              {
                v4[4] = idLexer::ParseInt(src);
              }
            }
            else
            {
              v4[3] = idLexer::ParseInt(src);
            }
          }
          else
          {
            *((float *)v4 + 2) = idLexer::ParseFloat(src, 0);
          }
        }
        else
        {
          *((float *)v4 + 1) = idLexer::ParseFloat(src, 0);
        }
      }
      else
      {
        idLexer::ReadTokenOnLine(src, &token);
        if ( token.type == 3 )
        {
          if ( (token.subtype & 0x10000) == 0 )
            idToken::NumberValue(&token);
          *v4 = token.intvalue;
        }
        else
        {
          *v4 = 0;
        }
      }
      if ( !idLexer::ReadToken(src, &token) )
        goto LABEL_70;
    }
    len = name.len;
    v6 = name.len + 1 <= effect->name.alloced;
    v9 = name.len;
    if ( !v6 )
      idStr::ReAllocate(&effect->name, name.len + 1, 0);
    v7 = v9;
    qmemcpy(effect->name.data, name.data, len);
    effect->name.data[v7] = 0;
    effect->name.len = v7;
    effect->data = v4;
    effect->datasize = 112;
    LOBYTE(v11) = 0;
    idStr::FreeData(&token);
    v11 = -1;
    idStr::FreeData(&name);
    return 1;
  }
  else
  {
LABEL_70:
    idLexer::Error(src, "idEFXFile::ReadEffect: EOF without closing brace");
    Mem_Free(v4);
    LOBYTE(v11) = 0;
    idStr::FreeData(&token);
    v11 = -1;
    idStr::FreeData(&name);
    return 0;
  }
}

// FUNC: public: bool __thiscall idEFXFile::LoadFile(char const *,bool)
char __thiscall idEFXFile::LoadFile(idEFXFile *this, const char *filename, bool OSPath)
{
  idSoundEffect *v5; // eax
  char v6; // al
  int granularity; // eax
  bool v8; // cc
  int i; // eax
  int num; // ebp
  int size; // eax
  int v12; // ecx
  idSoundEffect **list; // edi
  int j; // eax
  idSoundEffect *effect; // [esp+8h] [ebp-128h]
  idToken token; // [esp+Ch] [ebp-124h] BYREF
  idLexer src; // [esp+5Ch] [ebp-D4h] BYREF
  int v18; // [esp+12Ch] [ebp-4h]

  idLexer::idLexer(&src, 8);
  token.floatvalue = 0.0;
  v18 = 1;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  idLexer::LoadFile(&src, filename, OSPath);
  if ( !src.loaded || !idLexer::ExpectTokenString(&src, "Version") )
    goto LABEL_5;
  if ( idLexer::ParseInt(&src) != 1 )
  {
    idLexer::Error(&src, "idEFXFile::LoadFile: Unknown file version");
LABEL_5:
    LOBYTE(v18) = 0;
    idStr::FreeData(&token);
    v18 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
  while ( !idLexer::EndOfFile(&src) )
  {
    v5 = (idSoundEffect *)Memory::Allocate(0x28u);
    if ( v5 )
    {
      v5->name.len = 0;
      v5->name.alloced = 20;
      v5->name.data = v5->name.baseBuffer;
      v5->name.baseBuffer[0] = 0;
      effect = v5;
      v6 = idEFXFile::ReadEffect(this, &src, v5);
    }
    else
    {
      effect = 0;
      v6 = idEFXFile::ReadEffect(this, &src, 0);
    }
    if ( v6 )
    {
      if ( !this->effects.list )
      {
        granularity = this->effects.granularity;
        if ( granularity > 0 )
        {
          if ( granularity != this->effects.size )
          {
            v8 = granularity < this->effects.num;
            this->effects.size = granularity;
            if ( v8 )
              this->effects.num = granularity;
            this->effects.list = (idSoundEffect **)Memory::Allocate(4 * granularity);
            for ( i = 0; i < this->effects.num; ++i )
              this->effects.list[i] = *(idSoundEffect **)(4 * i);
          }
        }
        else
        {
          this->effects.list = 0;
          this->effects.num = 0;
          this->effects.size = 0;
        }
      }
      num = this->effects.num;
      size = this->effects.size;
      if ( this->effects.num == size )
      {
        if ( !this->effects.granularity )
          this->effects.granularity = 16;
        v12 = size + this->effects.granularity - (size + this->effects.granularity) % this->effects.granularity;
        if ( v12 > 0 )
        {
          if ( v12 != this->effects.size )
          {
            list = this->effects.list;
            this->effects.size = v12;
            if ( v12 < num )
              this->effects.num = v12;
            this->effects.list = (idSoundEffect **)Memory::Allocate(4 * v12);
            for ( j = 0; j < this->effects.num; ++j )
              this->effects.list[j] = list[j];
            if ( list )
              Memory::Free(list);
          }
        }
        else
        {
          if ( this->effects.list )
            Memory::Free(this->effects.list);
          this->effects.list = 0;
          this->effects.num = 0;
          this->effects.size = 0;
        }
      }
      this->effects.list[this->effects.num++] = effect;
    }
  }
  LOBYTE(v18) = 0;
  idStr::FreeData(&token);
  v18 = -1;
  idLexer::~idLexer(&src);
  return 1;
}

// FUNC: public: void __thiscall idEFXFile::Clear(void)
void __thiscall idEFXFile::Clear(idEFXFile *this)
{
  int i; // edi
  idSoundEffect **list; // eax
  idSoundEffect *v4; // ebx

  for ( i = 0; i < this->effects.num; ++i )
  {
    list = this->effects.list;
    v4 = list[i];
    if ( v4 )
    {
      idSoundEffect::~idSoundEffect(list[i]);
      Memory::Free(v4);
    }
    this->effects.list[i] = 0;
  }
  if ( this->effects.list )
    Memory::Free(this->effects.list);
  this->effects.list = 0;
  this->effects.num = 0;
  this->effects.size = 0;
}

// FUNC: public: __thiscall idEFXFile::~idEFXFile(void)
void __thiscall idEFXFile::~idEFXFile(idEFXFile *this)
{
  idSoundEffect **list; // eax

  idEFXFile::Clear(this);
  list = this->effects.list;
  if ( list )
    Memory::Free(list);
  this->effects.list = 0;
  this->effects.num = 0;
  this->effects.size = 0;
}

// FUNC: public: void __thiscall idEFXFile::UnloadFile(void)
// attributes: thunk
void __thiscall idEFXFile::UnloadFile(idEFXFile *this)
{
  idEFXFile::Clear(this);
}
