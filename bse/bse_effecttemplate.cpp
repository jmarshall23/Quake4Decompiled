
// FUNC: public: virtual char const * __thiscall rvDeclEffect::DefaultDefinition(void)const
const char *__thiscall rvDeclEffect::DefaultDefinition(rvDeclEffect *this)
{
  return "{\n}\n";
}

// FUNC: public: void __thiscall rvDeclEffect::SetMinDuration(float)
void __thiscall rvDeclEffect::SetMinDuration(rvDeclEffect *this, float duration)
{
  if ( duration > (double)this->mMinDuration )
    this->mMinDuration = duration;
}

// FUNC: public: void __thiscall rvDeclEffect::SetMaxDuration(float)
void __thiscall rvDeclEffect::SetMaxDuration(rvDeclEffect *this, float duration)
{
  if ( duration > (double)this->mMaxDuration )
    this->mMaxDuration = duration;
}

// FUNC: public: void __thiscall rvDeclEffect::DeleteEditorOriginal(void)
void __thiscall rvDeclEffect::DeleteEditorOriginal(rvDeclEffect *this)
{
  rvDeclEffect *mEditorOriginal; // ecx

  mEditorOriginal = this->mEditorOriginal;
  if ( mEditorOriginal )
    ((void (__thiscall *)(rvDeclEffect *, int))mEditorOriginal->~rvDeclEffect)(mEditorOriginal, 1);
  this->mEditorOriginal = 0;
}

// FUNC: public: virtual bool __thiscall rvDeclEffect::SetDefaultText(void)
char __thiscall rvDeclEffect::SetDefaultText(rvDeclEffect *this)
{
  const char *v2; // edi
  const char *v3; // eax
  char generated[1024]; // [esp+8h] [ebp-400h] BYREF

  v2 = this->base->GetName(this->base);
  v3 = this->DefaultDefinition(this);
  idStr::snPrintf(generated, 1024, "effect %s // IMPLICITLY GENERATED\n%s", v2, v3);
  this->base->SetText(this->base, generated);
  return 1;
}

// FUNC: public: class rvSegmentTemplate * __thiscall rvDeclEffect::GetSegmentTemplate(char const *)
rvSegmentTemplate *__thiscall rvDeclEffect::GetSegmentTemplate(rvDeclEffect *this, const char *name)
{
  int v3; // esi
  int i; // edi

  v3 = this->mSegmentTemplates.num - 1;
  if ( v3 < 0 )
    return 0;
  for ( i = v3; idStr::Icmp(this->mSegmentTemplates.list[i].mSegmentName.data, name); --i )
  {
    if ( --v3 < 0 )
      return 0;
  }
  return &this->mSegmentTemplates.list[v3];
}

// FUNC: public: class rvSegmentTemplate * __thiscall rvDeclEffect::GetSegmentTemplate(int)
rvSegmentTemplate *__thiscall rvDeclEffect::GetSegmentTemplate(rvDeclEffect *this, int i)
{
  if ( i >= this->mSegmentTemplates.num )
    return 0;
  else
    return &this->mSegmentTemplates.list[i];
}

// FUNC: private: bool __thiscall rvDeclEffect::Compare(class rvDeclEffect const &)const
char __thiscall rvDeclEffect::Compare(rvDeclEffect *this, const rvDeclEffect *comp)
{
  int num; // eax
  int v5; // ebx
  int i; // esi

  num = this->mSegmentTemplates.num;
  if ( num != comp->mSegmentTemplates.num )
    return 0;
  v5 = 0;
  if ( num <= 0 )
    return 1;
  for ( i = 0; rvSegmentTemplate::Compare(&this->mSegmentTemplates.list[i], &comp->mSegmentTemplates.list[i]); ++i )
  {
    if ( ++v5 >= this->mSegmentTemplates.num )
      return 1;
  }
  return 0;
}

// FUNC: public: int __thiscall rvDeclEffect::GetTrailSegmentIndex(class idStr const &)
int __thiscall rvDeclEffect::GetTrailSegmentIndex(rvDeclEffect *this, const idStr *name)
{
  int v3; // esi
  int v4; // ebx
  rvSegmentTemplate *v5; // eax

  v3 = 0;
  if ( this->mSegmentTemplates.num <= 0 )
  {
LABEL_6:
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "^4BSE:^1 Unable to find segment '%s'",
      name->data);
    return -1;
  }
  else
  {
    v4 = 0;
    while ( 1 )
    {
      v5 = &this->mSegmentTemplates.list[v4];
      if ( v5 )
      {
        if ( !idStr::Icmp(name->data, v5->mSegmentName.data) )
          return v3;
      }
      ++v3;
      ++v4;
      if ( v3 >= this->mSegmentTemplates.num )
        goto LABEL_6;
    }
  }
}

// FUNC: public: virtual unsigned int __thiscall rvDeclEffect::Size(void)const
int __thiscall rvDeclEffect::Size(rvDeclEffect *this)
{
  return 1484 * this->mSegmentTemplates.size + 52;
}

// FUNC: public: bool __thiscall rvDeclEffect::CompareToEditorOriginal(void)
bool __thiscall rvDeclEffect::CompareToEditorOriginal(rvDeclEffect *this)
{
  return rvDeclEffect::Compare(this, this->mEditorOriginal);
}

// FUNC: public: virtual void __thiscall rvDeclEffect::FreeData(void)
void __thiscall rvDeclEffect::FreeData(rvDeclEffect *this)
{
  rvSegmentTemplate *list; // eax
  rvBSE **p_mBSEEffect; // edi

  list = this->mSegmentTemplates.list;
  if ( list )
  {
    p_mBSEEffect = &list[-1].mBSEEffect;
    `eh vector destructor iterator'(
      list,
      0x5CCu,
      (int)list[-1].mBSEEffect,
      (void (__thiscall *)(void *))rvSegmentTemplate::~rvSegmentTemplate);
    Memory::Free(p_mBSEEffect);
  }
  this->mSegmentTemplates.list = 0;
  this->mSegmentTemplates.num = 0;
  this->mSegmentTemplates.size = 0;
}

// FUNC: public: void __thiscall rvDeclEffect::Init(void)
void __thiscall rvDeclEffect::Init(rvDeclEffect *this)
{
  rvSegmentTemplate *list; // eax
  rvBSE **p_mBSEEffect; // ebx

  this->mEditorOriginal = 0;
  this->mFlags = 0;
  this->mMinDuration = 0.0;
  this->mMaxDuration = 0.0;
  this->mSize = 512.0;
  this->mPlayCount = 0;
  this->mLoopCount = 0;
  list = this->mSegmentTemplates.list;
  if ( list )
  {
    p_mBSEEffect = &list[-1].mBSEEffect;
    `eh vector destructor iterator'(
      list,
      0x5CCu,
      (int)list[-1].mBSEEffect,
      (void (__thiscall *)(void *))rvSegmentTemplate::~rvSegmentTemplate);
    Memory::Free(p_mBSEEffect);
  }
  this->mSegmentTemplates.list = 0;
  this->mSegmentTemplates.num = 0;
  this->mSegmentTemplates.size = 0;
}

// FUNC: public: void __thiscall rvDeclEffect::CopyData(class rvDeclEffect const &)
void __thiscall rvDeclEffect::CopyData(rvDeclEffect *this, const rvDeclEffect *copy)
{
  idList<rvSegmentTemplate> *p_mSegmentTemplates; // edi
  rvSegmentTemplate *list; // eax
  rvBSE **p_mBSEEffect; // ebp

  p_mSegmentTemplates = &this->mSegmentTemplates;
  this->mFlags = copy->mFlags;
  list = this->mSegmentTemplates.list;
  if ( list )
  {
    p_mBSEEffect = &list[-1].mBSEEffect;
    `eh vector destructor iterator'(
      list,
      0x5CCu,
      (int)list[-1].mBSEEffect,
      (void (__thiscall *)(void *))rvSegmentTemplate::~rvSegmentTemplate);
    Memory::Free(p_mBSEEffect);
  }
  p_mSegmentTemplates->list = 0;
  p_mSegmentTemplates->num = 0;
  p_mSegmentTemplates->size = 0;
  idList<rvSegmentTemplate>::operator=(p_mSegmentTemplates, &copy->mSegmentTemplates.num);
  this->mSize = copy->mSize;
  this->mMinDuration = copy->mMinDuration;
  this->mMaxDuration = copy->mMaxDuration;
}

// FUNC: public: void __thiscall rvDeclEffect::Finish(void)
void __thiscall rvDeclEffect::Finish(rvDeclEffect *this)
{
  int num; // edi
  idList<rvSegmentTemplate> *p_mSegmentTemplates; // ebp
  int v4; // ebx
  rvSegmentTemplate *v5; // edi
  int v6; // [esp+10h] [ebp-4h]

  this->mFlags &= ~1u;
  num = this->mSegmentTemplates.num;
  p_mSegmentTemplates = &this->mSegmentTemplates;
  v4 = 0;
  this->mMinDuration = 0.0;
  this->mMaxDuration = 0.0;
  idList<rvSegmentTemplate>::Resize(&this->mSegmentTemplates, num);
  p_mSegmentTemplates->num = num;
  if ( num > 0 )
  {
    v6 = 0;
    do
    {
      v5 = &this->mSegmentTemplates.list[v6];
      if ( v5 )
      {
        rvSegmentTemplate::Finish(v5, this);
        if ( v5->mSegType == 5 )
          this->mFlags |= 1u;
        if ( rvParticleTemplate::UsesEndOrigin(&v5->mParticleTemplate) )
          this->mFlags |= 2u;
        if ( (v5->mFlags & 0x40) != 0 )
          this->mFlags |= 4u;
        rvSegmentTemplate::EvaluateTrailSegment(v5, this);
        rvSegmentTemplate::SetMinDuration(v5, this);
        rvSegmentTemplate::SetMaxDuration(v5, this);
      }
      ++v6;
      ++v4;
    }
    while ( v4 < p_mSegmentTemplates->num );
  }
  this->mSize = rvDeclEffect::CalculateBounds(this);
}

// FUNC: public: void __thiscall rvDeclEffect::CreateEditorOriginal(void)
void __thiscall rvDeclEffect::CreateEditorOriginal(rvDeclEffect *this)
{
  rvDeclEffect *mEditorOriginal; // ecx
  rvDeclEffect *v3; // eax
  rvDeclEffect *v4; // eax

  mEditorOriginal = this->mEditorOriginal;
  if ( mEditorOriginal )
    ((void (__thiscall *)(rvDeclEffect *, int))mEditorOriginal->~rvDeclEffect)(mEditorOriginal, 1);
  v3 = (rvDeclEffect *)Memory::Allocate(0x34u);
  if ( v3 )
  {
    rvDeclEffect::rvDeclEffect(v3, this);
    this->mEditorOriginal = v4;
  }
  else
  {
    this->mEditorOriginal = 0;
  }
}

// FUNC: public: void __thiscall rvDeclEffect::Revert(void)
void __thiscall rvDeclEffect::Revert(rvDeclEffect *this)
{
  rvDeclEffect *mEditorOriginal; // ecx
  rvDeclEffect *v3; // eax
  rvDeclEffect *v4; // eax

  rvDeclEffect::CopyData(this, this->mEditorOriginal);
  mEditorOriginal = this->mEditorOriginal;
  if ( mEditorOriginal )
    ((void (__thiscall *)(rvDeclEffect *, int))mEditorOriginal->~rvDeclEffect)(mEditorOriginal, 1);
  v3 = (rvDeclEffect *)Memory::Allocate(0x34u);
  if ( v3 )
  {
    rvDeclEffect::rvDeclEffect(v3, this);
    this->mEditorOriginal = v4;
  }
  else
  {
    this->mEditorOriginal = 0;
  }
}

// FUNC: public: virtual bool __thiscall rvDeclEffect::Parse(char const *,int,bool)
char __thiscall rvDeclEffect::Parse(rvDeclEffect *this, const char *text, int textLength, bool noCaching)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // edx
  const char *v7; // edi
  int v8; // eax
  int granularity; // edi
  bool v10; // cc
  int *v11; // eax
  rvSegmentTemplate *v12; // ebp
  int v13; // ebp
  int v14; // edi
  int num; // ebp
  int size; // edi
  int v17; // edi
  rvSegmentTemplate *v18; // eax
  rvBSE **p_mBSEEffect; // edi
  rvSegmentTemplate *list; // ebx
  int *v21; // eax
  rvSegmentTemplate *v22; // ebp
  int v23; // ebp
  int v24; // edi
  idToken token; // [esp+14h] [ebp-710h] BYREF
  idStr filename; // [esp+64h] [ebp-6C0h] BYREF
  idLexer lexer; // [esp+84h] [ebp-6A0h] BYREF
  rvSegmentTemplate segment; // [esp+14Ch] [ebp-5D8h] BYREF
  int v30; // [esp+720h] [ebp-4h]

  filename.len = 0;
  filename.alloced = 20;
  filename.data = filename.baseBuffer;
  filename.baseBuffer[0] = 0;
  v30 = 0;
  idLexer::idLexer(&lexer);
  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  LOBYTE(v30) = 2;
  rvSegmentTemplate::rvSegmentTemplate(&segment);
  base = this->base;
  v6 = base->__vftable;
  LOBYTE(v30) = 3;
  v7 = v6->GetFileName(base);
  v8 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&lexer, text, textLength, v7, v8);
  lexer.flags = 6300;
  idLexer::SkipUntilString(&lexer, "{");
  if ( idLexer::ReadToken(&lexer, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      rvSegmentTemplate::Init(&segment, this);
      if ( idStr::Icmp(token.data, "size") )
      {
        if ( idStr::Icmp(token.data, "effect") )
        {
          if ( idStr::Icmp(token.data, "emitter") )
          {
            if ( idStr::Icmp(token.data, "spawner") )
            {
              if ( idStr::Icmp(token.data, "trail") )
              {
                if ( idStr::Icmp(token.data, "sound") )
                {
                  if ( idStr::Icmp(token.data, "decal") )
                  {
                    if ( idStr::Icmp(token.data, "light") )
                    {
                      if ( idStr::Icmp(token.data, "delay") )
                      {
                        if ( idStr::Icmp(token.data, "doubleVision") )
                        {
                          if ( idStr::Icmp(token.data, "shake") )
                          {
                            if ( idStr::Icmp(token.data, "tunnel") )
                            {
                              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
                                common.type,
                                "^4BSE:^1 Invalid segment type '%s' (file: %s, line: %d)",
                                token.data,
                                lexer.filename.data,
                                lexer.line);
                              idLexer::SkipBracedSection(&lexer, 1);
                            }
                            else
                            {
                              rvSegmentTemplate::Parse(&segment, this, 11, &lexer);
                            }
                          }
                          else
                          {
                            rvSegmentTemplate::Parse(&segment, this, 10, &lexer);
                          }
                        }
                        else
                        {
                          rvSegmentTemplate::Parse(&segment, this, 9, &lexer);
                        }
                      }
                      else
                      {
                        rvSegmentTemplate::Parse(&segment, this, 8, &lexer);
                      }
                    }
                    else
                    {
                      rvSegmentTemplate::Parse(&segment, this, 7, &lexer);
                    }
                  }
                  else
                  {
                    rvSegmentTemplate::Parse(&segment, this, 6, &lexer);
                  }
                }
                else
                {
                  rvSegmentTemplate::Parse(&segment, this, 5, &lexer);
                }
              }
              else
              {
                rvSegmentTemplate::Parse(&segment, this, 4, &lexer);
              }
            }
            else
            {
              rvSegmentTemplate::Parse(&segment, this, 3, &lexer);
            }
          }
          else
          {
            rvSegmentTemplate::Parse(&segment, this, 2, &lexer);
          }
        }
        else
        {
          rvSegmentTemplate::Parse(&segment, this, 1, &lexer);
        }
        if ( rvSegmentTemplate::Finish(&segment, this) )
        {
          if ( !this->mSegmentTemplates.list )
          {
            granularity = this->mSegmentTemplates.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != this->mSegmentTemplates.size )
              {
                v10 = granularity < this->mSegmentTemplates.num;
                this->mSegmentTemplates.size = granularity;
                if ( v10 )
                  this->mSegmentTemplates.num = granularity;
                v11 = (int *)Memory::Allocate(1484 * granularity + 4);
                LOBYTE(v30) = 4;
                if ( v11 )
                {
                  v12 = (rvSegmentTemplate *)(v11 + 1);
                  *v11 = granularity;
                  `eh vector constructor iterator'(
                    v11 + 1,
                    0x5CCu,
                    granularity,
                    (void (__thiscall *)(void *))rvSegmentTemplate::rvSegmentTemplate,
                    (void (__thiscall *)(void *))rvSegmentTemplate::~rvSegmentTemplate);
                }
                else
                {
                  v12 = 0;
                }
                this->mSegmentTemplates.list = v12;
                v13 = 0;
                v10 = this->mSegmentTemplates.num <= 0;
                LOBYTE(v30) = 3;
                if ( !v10 )
                {
                  v14 = 0;
                  do
                  {
                    rvSegmentTemplate::operator=((char *)&this->mSegmentTemplates.list[v14], v14 * 1484);
                    ++v13;
                    ++v14;
                  }
                  while ( v13 < this->mSegmentTemplates.num );
                }
              }
            }
            else
            {
              this->mSegmentTemplates.list = 0;
              this->mSegmentTemplates.num = 0;
              this->mSegmentTemplates.size = 0;
            }
          }
          num = this->mSegmentTemplates.num;
          size = this->mSegmentTemplates.size;
          if ( num == size )
          {
            if ( !this->mSegmentTemplates.granularity )
              this->mSegmentTemplates.granularity = 16;
            v17 = this->mSegmentTemplates.granularity
                + size
                - (this->mSegmentTemplates.granularity + size) % this->mSegmentTemplates.granularity;
            if ( v17 > 0 )
            {
              if ( v17 != this->mSegmentTemplates.size )
              {
                list = this->mSegmentTemplates.list;
                this->mSegmentTemplates.size = v17;
                if ( v17 < num )
                  this->mSegmentTemplates.num = v17;
                v21 = (int *)Memory::Allocate(1484 * v17 + 4);
                LOBYTE(v30) = 5;
                if ( v21 )
                {
                  v22 = (rvSegmentTemplate *)(v21 + 1);
                  *v21 = v17;
                  `eh vector constructor iterator'(
                    v21 + 1,
                    0x5CCu,
                    v17,
                    (void (__thiscall *)(void *))rvSegmentTemplate::rvSegmentTemplate,
                    (void (__thiscall *)(void *))rvSegmentTemplate::~rvSegmentTemplate);
                }
                else
                {
                  v22 = 0;
                }
                this->mSegmentTemplates.list = v22;
                v23 = 0;
                v10 = this->mSegmentTemplates.num <= 0;
                LOBYTE(v30) = 3;
                if ( !v10 )
                {
                  v24 = 0;
                  do
                  {
                    rvSegmentTemplate::operator=((char *)&this->mSegmentTemplates.list[v24], (int)&list[v24]);
                    ++v23;
                    ++v24;
                  }
                  while ( v23 < this->mSegmentTemplates.num );
                }
                if ( list )
                {
                  `eh vector destructor iterator'(
                    list,
                    0x5CCu,
                    (int)list[-1].mBSEEffect,
                    (void (__thiscall *)(void *))rvSegmentTemplate::~rvSegmentTemplate);
                  Memory::Free(&list[-1].mBSEEffect);
                }
              }
            }
            else
            {
              v18 = this->mSegmentTemplates.list;
              if ( v18 )
              {
                p_mBSEEffect = &v18[-1].mBSEEffect;
                `eh vector destructor iterator'(
                  v18,
                  0x5CCu,
                  (int)v18[-1].mBSEEffect,
                  (void (__thiscall *)(void *))rvSegmentTemplate::~rvSegmentTemplate);
                Memory::Free(p_mBSEEffect);
              }
              this->mSegmentTemplates.list = 0;
              this->mSegmentTemplates.num = 0;
              this->mSegmentTemplates.size = 0;
            }
          }
          rvSegmentTemplate::operator=(
            (char *)&this->mSegmentTemplates.list[this->mSegmentTemplates.num],
            (int)&segment);
          ++this->mSegmentTemplates.num;
        }
      }
      else
      {
        this->mSize = idLexer::ParseFloat(&lexer, 0);
      }
      if ( !idLexer::ReadToken(&lexer, &token) )
        goto LABEL_61;
    }
    rvDeclEffect::Finish(this);
    (*(void (__thiscall **)(_DWORD))(**(_DWORD **)common.ip + 108))(*(_DWORD *)common.ip);
    LOBYTE(v30) = 2;
    rvSegmentTemplate::~rvSegmentTemplate(&segment);
    LOBYTE(v30) = 1;
    idStr::FreeData(&token);
    LOBYTE(v30) = 0;
    idLexer::~idLexer(&lexer);
    v30 = -1;
    idStr::FreeData(&filename);
    return 1;
  }
  else
  {
LABEL_61:
    LOBYTE(v30) = 2;
    rvSegmentTemplate::~rvSegmentTemplate(&segment);
    LOBYTE(v30) = 1;
    idStr::FreeData(&token);
    LOBYTE(v30) = 0;
    idLexer::~idLexer(&lexer);
    v30 = -1;
    idStr::FreeData(&filename);
    return 0;
  }
}
