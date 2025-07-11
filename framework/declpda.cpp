
// FUNC: public: virtual char const * __thiscall idDeclPDA::DefaultDefinition(void)const
const char *__thiscall idDeclPDA::DefaultDefinition(idDeclPDA *this)
{
  return "{\n\tname  \"default pda\"\n}";
}

// FUNC: public: virtual void __thiscall idDeclPDA::SetSecurity(char const *)const
void __thiscall idDeclPDA::SetSecurity(idDeclPDA *this, char *sec)
{
  idStr::operator=(&this->security, sec);
}

// FUNC: public: virtual void __thiscall idDeclAudio::Print(void)const
void __thiscall idDeclAudio::Print(idDeclAudio *this)
{
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Implement me\n");
}

// FUNC: public: virtual char const * __thiscall idDeclEmail::DefaultDefinition(void)const
const char *__thiscall idDeclEmail::DefaultDefinition(idDeclEmail *this)
{
  return "{\n\t{\n\t\tto\t5Mail recipient\n\t\tsubject\t5Nothing\n\t\tfrom\t5No one\n\t}\n}";
}

// FUNC: public: virtual char const * __thiscall idDeclVideo::DefaultDefinition(void)const
const char *__thiscall idDeclVideo::DefaultDefinition(idDeclVideo *this)
{
  return "{\n\t{\n\t\tname\t5Default Video\n\t}\n}";
}

// FUNC: public: virtual char const * __thiscall idDeclAudio::DefaultDefinition(void)const
const char *__thiscall idDeclAudio::DefaultDefinition(idDeclAudio *this)
{
  return "{\n\t{\n\t\tname\t5Default Audio\n\t}\n}";
}

// FUNC: public: virtual unsigned int __thiscall idDeclPDA::Size(void)const
unsigned int __thiscall idDeclPDA::Size(idDeclPDA *this)
{
  int alloced; // edx
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  unsigned int result; // eax

  if ( this->pdaName.data == this->pdaName.baseBuffer )
    alloced = 0;
  else
    alloced = this->pdaName.alloced;
  v2 = alloced + 32 * (this->audios.size + this->emails.size + this->videos.size + 9);
  if ( this->fullName.data == this->fullName.baseBuffer )
    v3 = 0;
  else
    v3 = this->fullName.alloced;
  v4 = v3 + v2;
  if ( this->icon.data == this->icon.baseBuffer )
    v5 = 0;
  else
    v5 = this->icon.alloced;
  v6 = v5 + v4;
  if ( this->id.data == this->id.baseBuffer )
    v7 = 0;
  else
    v7 = this->id.alloced;
  v8 = v7 + v6;
  if ( this->post.data == this->post.baseBuffer )
    v9 = 0;
  else
    v9 = this->post.alloced;
  v10 = v9 + v8;
  if ( this->title.data == this->title.baseBuffer )
    v11 = 0;
  else
    v11 = this->title.alloced;
  result = v11 + v10;
  if ( this->security.data != this->security.baseBuffer )
    result += this->security.alloced;
  return result;
}

// FUNC: public: virtual int const __thiscall idDeclPDA::GetNumAudios(void)const
int __thiscall idDeclPDA::GetNumAudios(idDeclPDA *this)
{
  return this->audios.num;
}

// FUNC: public: virtual class idDeclVideo const * __thiscall idDeclPDA::GetVideoByIndex(int)const
const idDeclVideo *__thiscall idDeclPDA::GetVideoByIndex(idDeclPDA *this, int index)
{
  if ( index < 0 || index >= this->videos.num )
    return 0;
  else
    return (const idDeclVideo *)declManager->FindType(declManager, 13, this->videos.list[index].data, 0, 0);
}

// FUNC: public: virtual class idDeclAudio const * __thiscall idDeclPDA::GetAudioByIndex(int)const
const idDeclAudio *__thiscall idDeclPDA::GetAudioByIndex(idDeclPDA *this, int index)
{
  if ( index < 0 || index >= this->audios.num )
    return 0;
  else
    return (const idDeclAudio *)declManager->FindType(declManager, 14, this->audios.list[index].data, 0, 0);
}

// FUNC: public: virtual class idDeclEmail const * __thiscall idDeclPDA::GetEmailByIndex(int)const
const idDeclEmail *__thiscall idDeclPDA::GetEmailByIndex(idDeclPDA *this, int index)
{
  if ( index < 0 || index >= this->emails.num )
    return 0;
  else
    return (const idDeclEmail *)declManager->FindType(declManager, 15, this->emails.list[index].data, 0, 0);
}

// FUNC: public: virtual unsigned int __thiscall idDeclEmail::Size(void)const
unsigned int __thiscall idDeclEmail::Size(idDeclEmail *this)
{
  int alloced; // eax
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  unsigned int result; // eax

  if ( this->text.data == this->text.baseBuffer )
    alloced = 0;
  else
    alloced = this->text.alloced;
  v2 = alloced + 200;
  if ( this->subject.data == this->subject.baseBuffer )
    v3 = 0;
  else
    v3 = this->subject.alloced;
  v4 = v3 + v2;
  if ( this->date.data == this->date.baseBuffer )
    v5 = 0;
  else
    v5 = this->date.alloced;
  v6 = v5 + v4;
  if ( this->to.data == this->to.baseBuffer )
    v7 = 0;
  else
    v7 = this->to.alloced;
  v8 = v7 + v6;
  if ( this->from.data == this->from.baseBuffer )
    v9 = 0;
  else
    v9 = this->from.alloced;
  result = v9 + v8;
  if ( this->image.data != this->image.baseBuffer )
    result += this->image.alloced;
  return result;
}

// FUNC: public: virtual unsigned int __thiscall idDeclVideo::Size(void)const
int __thiscall idDeclVideo::Size(idDeclVideo *this)
{
  int alloced; // eax
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int result; // eax

  if ( this->preview.data == this->preview.baseBuffer )
    alloced = 0;
  else
    alloced = this->preview.alloced;
  v2 = alloced + 168;
  if ( this->video.data == this->video.baseBuffer )
    v3 = 0;
  else
    v3 = this->video.alloced;
  v4 = v3 + v2;
  if ( this->videoName.data == this->videoName.baseBuffer )
    v5 = 0;
  else
    v5 = this->videoName.alloced;
  v6 = v5 + v4;
  if ( this->info.data == this->info.baseBuffer )
    v7 = 0;
  else
    v7 = this->info.alloced;
  result = v7 + v6;
  if ( this->audio.data != this->audio.baseBuffer )
    result += this->audio.alloced;
  return result;
}

// FUNC: public: virtual unsigned int __thiscall idDeclAudio::Size(void)const
int __thiscall idDeclAudio::Size(idDeclAudio *this)
{
  int alloced; // eax
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int result; // eax

  if ( this->audio.data == this->audio.baseBuffer )
    alloced = 0;
  else
    alloced = this->audio.alloced;
  v2 = alloced + 136;
  if ( this->audioName.data == this->audioName.baseBuffer )
    v3 = 0;
  else
    v3 = this->audioName.alloced;
  v4 = v3 + v2;
  if ( this->info.data == this->info.baseBuffer )
    v5 = 0;
  else
    v5 = this->info.alloced;
  result = v5 + v4;
  if ( this->preview.data != this->preview.baseBuffer )
    result += this->preview.alloced;
  return result;
}

// FUNC: public: virtual bool __thiscall idDeclEmail::Parse(char const *,int,bool)
char __thiscall idDeclEmail::Parse(idDeclEmail *this, const char *_text, int textLength, bool noCaching)
{
  idDeclEmail *v4; // ebx
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // edx
  const char *v7; // esi
  int v8; // eax
  idStr *p_text; // ebp
  idStr *p_to; // ebx
  int v11; // esi
  int i; // eax
  char *data; // eax
  int len; // esi
  int v16; // [esp-4h] [ebp-140h]
  int v17; // [esp+10h] [ebp-12Ch]
  idToken token; // [esp+18h] [ebp-124h] BYREF
  idLexer src; // [esp+68h] [ebp-D4h] BYREF
  int v21; // [esp+138h] [ebp-4h]

  v4 = this;
  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v21 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  base = v4->base;
  v6 = base->__vftable;
  LOBYTE(v21) = 1;
  v7 = v6->GetFileName(base);
  v8 = v4->base->GetLineNum(v4->base);
  idLexer::LoadMemory(&src, _text, textLength, v7, v8);
  src.flags = 6284;
  idLexer::SkipUntilString(&src, "{");
  p_text = &v4->text;
  idStr::operator=(&v4->text, (char *)&entityFilter);
  if ( idLexer::ReadToken(&src, &token) )
  {
    while ( 1 )
    {
      if ( !idStr::Cmp(token.data, "}") )
        goto LABEL_27;
      if ( !idStr::Icmp(token.data, "subject") )
        break;
      if ( !idStr::Icmp(token.data, "to") )
      {
        idLexer::ReadToken(&src, &token);
        p_to = &v4->to;
        goto LABEL_23;
      }
      if ( !idStr::Icmp(token.data, "from") )
      {
        idLexer::ReadToken(&src, &token);
        p_to = &v4->from;
        goto LABEL_23;
      }
      if ( !idStr::Icmp(token.data, aDate_0) )
      {
        idLexer::ReadToken(&src, &token);
        p_to = &v4->date;
        goto LABEL_23;
      }
      if ( !idStr::Icmp(token.data, "text") )
      {
        idLexer::ReadToken(&src, &token);
        if ( idStr::Cmp(token.data, "{") )
          goto LABEL_29;
        for ( ; idLexer::ReadToken(&src, &token); data[v11] = 0 )
        {
          if ( !idStr::Cmp(token.data, "}") )
            break;
          v11 = token.len + p_text->len;
          if ( v11 + 1 > p_text->alloced )
            idStr::ReAllocate(p_text, v11 + 1, 1);
          for ( i = 0; i < token.len; ++i )
            p_text->data[p_text->len + i] = token.data[i];
          data = p_text->data;
          p_text->len = v11;
        }
        goto LABEL_26;
      }
      if ( !idStr::Icmp(token.data, "image") )
      {
        idLexer::ReadToken(&src, &token);
        p_to = &v4->image;
        goto LABEL_23;
      }
LABEL_26:
      if ( !idLexer::ReadToken(&src, &token) )
        goto LABEL_27;
    }
    idLexer::ReadToken(&src, &token);
    p_to = &v4->subject;
LABEL_23:
    len = token.len;
    v17 = token.len;
    if ( token.len + 1 > p_to->alloced )
      idStr::ReAllocate(p_to, token.len + 1, 0);
    qmemcpy(p_to->data, token.data, len);
    p_to->data[v17] = 0;
    p_to->len = v17;
    v4 = this;
    goto LABEL_26;
  }
LABEL_27:
  if ( idLexer::HadError(&src) )
  {
LABEL_29:
    v16 = (int)v4->base->GetName(v4->base);
    idLexer::Warning(&src, "Email decl '%s' had a parse error", v16);
    LOBYTE(v21) = 0;
    idStr::FreeData(&token);
    v21 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
  else
  {
    LOBYTE(v21) = 0;
    idStr::FreeData(&token);
    v21 = -1;
    idLexer::~idLexer(&src);
    return 1;
  }
}

// FUNC: public: virtual bool __thiscall idDeclVideo::Parse(char const *,int,bool)
char __thiscall idDeclVideo::Parse(idDeclVideo *this, const char *text, int textLength, bool noCaching)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // edx
  const char *v7; // esi
  int v8; // eax
  int len; // esi
  idStr *p_videoName; // ebp
  int v11; // esi
  int v12; // esi
  const char *v13; // eax
  int v15; // [esp+8h] [ebp-128h]
  int v16; // [esp+8h] [ebp-128h]
  int v17; // [esp+8h] [ebp-128h]
  idToken token; // [esp+Ch] [ebp-124h] BYREF
  idLexer src; // [esp+5Ch] [ebp-D4h] BYREF
  int v20; // [esp+12Ch] [ebp-4h]

  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v20 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  base = this->base;
  v6 = base->__vftable;
  LOBYTE(v20) = 1;
  v7 = v6->GetFileName(base);
  v8 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&src, text, textLength, v7, v8);
  src.flags = 6284;
  idLexer::SkipUntilString(&src, "{");
  if ( idLexer::ReadToken(&src, &token) )
  {
    while ( 1 )
    {
      if ( !idStr::Cmp(token.data, "}") )
        goto LABEL_22;
      if ( idStr::Icmp(token.data, "name") )
        break;
      idLexer::ReadToken(&src, &token);
      len = token.len;
      p_videoName = &this->videoName;
      v15 = token.len;
      if ( token.len + 1 <= this->videoName.alloced )
        goto LABEL_9;
      idStr::ReAllocate(&this->videoName, token.len + 1, 0);
      qmemcpy(this->videoName.data, token.data, len);
      this->videoName.data[len] = 0;
      p_videoName->len = len;
LABEL_21:
      if ( !idLexer::ReadToken(&src, &token) )
        goto LABEL_22;
    }
    if ( idStr::Icmp(token.data, "preview") )
    {
      if ( !idStr::Icmp(token.data, "video") )
      {
        idLexer::ReadToken(&src, &token);
        v11 = token.len;
        v16 = token.len;
        if ( token.len + 1 > this->video.alloced )
          idStr::ReAllocate(&this->video, token.len + 1, 0);
        qmemcpy(this->video.data, token.data, v11);
        this->video.data[v16] = 0;
        this->video.len = v16;
        declManager->FindMaterial(declManager, this->video.data, 1);
        goto LABEL_21;
      }
      if ( idStr::Icmp(token.data, "info") )
      {
        if ( !idStr::Icmp(token.data, "audio") )
        {
          idLexer::ReadToken(&src, &token);
          v12 = token.len;
          v17 = token.len;
          if ( token.len + 1 > this->audio.alloced )
            idStr::ReAllocate(&this->audio, token.len + 1, 0);
          qmemcpy(this->audio.data, token.data, v12);
          this->audio.data[v17] = 0;
          this->audio.len = v17;
          declManager->FindSound(declManager, this->audio.data, 1);
        }
        goto LABEL_21;
      }
      idLexer::ReadToken(&src, &token);
      len = token.len;
      p_videoName = &this->info;
      v15 = token.len;
      if ( token.len + 1 > this->info.alloced )
      {
        idStr::ReAllocate(&this->info, token.len + 1, 0);
        qmemcpy(this->info.data, token.data, len);
        this->info.data[len] = 0;
        p_videoName->len = len;
        goto LABEL_21;
      }
    }
    else
    {
      idLexer::ReadToken(&src, &token);
      len = token.len;
      p_videoName = &this->preview;
      v15 = token.len;
      if ( token.len + 1 > this->preview.alloced )
        idStr::ReAllocate(&this->preview, token.len + 1, 0);
    }
LABEL_9:
    qmemcpy(p_videoName->data, token.data, len);
    p_videoName->data[v15] = 0;
    p_videoName->len = v15;
    goto LABEL_21;
  }
LABEL_22:
  if ( idLexer::HadError(&src) )
  {
    v13 = this->base->GetName(this->base);
    idLexer::Warning(&src, "Video decl '%s' had a parse error", v13);
    LOBYTE(v20) = 0;
    idStr::FreeData(&token);
    v20 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
  else
  {
    LOBYTE(v20) = 0;
    idStr::FreeData(&token);
    v20 = -1;
    idLexer::~idLexer(&src);
    return 1;
  }
}

// FUNC: public: virtual bool __thiscall idDeclAudio::Parse(char const *,int,bool)
char __thiscall idDeclAudio::Parse(idDeclAudio *this, const char *text, int textLength, bool noCaching)
{
  idDeclAudio *v4; // ebp
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // edx
  const char *v7; // esi
  int v8; // eax
  idStr *p_audioName; // ebx
  int len; // ebp
  int v11; // ebx
  idStr *p_audio; // ebp
  const char *v13; // eax
  idToken token; // [esp+Ch] [ebp-124h] BYREF
  idLexer src; // [esp+5Ch] [ebp-D4h] BYREF
  int v18; // [esp+12Ch] [ebp-4h]

  v4 = this;
  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v18 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  base = v4->base;
  v6 = base->__vftable;
  LOBYTE(v18) = 1;
  v7 = v6->GetFileName(base);
  v8 = v4->base->GetLineNum(v4->base);
  idLexer::LoadMemory(&src, text, textLength, v7, v8);
  src.flags = 6284;
  idLexer::SkipUntilString(&src, "{");
  if ( idLexer::ReadToken(&src, &token) )
  {
    while ( 1 )
    {
      if ( !idStr::Cmp(token.data, "}") )
        goto LABEL_21;
      if ( !idStr::Icmp(token.data, "name") )
      {
        idLexer::ReadToken(&src, &token);
        p_audioName = &v4->audioName;
        len = token.len;
        if ( token.len + 1 <= p_audioName->alloced )
          goto LABEL_17;
        idStr::ReAllocate(p_audioName, token.len + 1, 0);
        qmemcpy(p_audioName->data, token.data, len);
        p_audioName->data[len] = 0;
        goto LABEL_18;
      }
      if ( !idStr::Icmp(token.data, "audio") )
        break;
      if ( !idStr::Icmp(token.data, "info") )
      {
        idLexer::ReadToken(&src, &token);
        p_audioName = &v4->info;
        len = token.len;
        if ( token.len + 1 > p_audioName->alloced )
          idStr::ReAllocate(p_audioName, token.len + 1, 0);
        goto LABEL_17;
      }
      if ( !idStr::Icmp(token.data, "preview") )
      {
        idLexer::ReadToken(&src, &token);
        p_audioName = &v4->preview;
        len = token.len;
        if ( token.len + 1 > p_audioName->alloced )
          idStr::ReAllocate(p_audioName, token.len + 1, 0);
LABEL_17:
        qmemcpy(p_audioName->data, token.data, len);
        p_audioName->data[len] = 0;
LABEL_18:
        p_audioName->len = len;
LABEL_19:
        v4 = this;
      }
      if ( !idLexer::ReadToken(&src, &token) )
        goto LABEL_21;
    }
    idLexer::ReadToken(&src, &token);
    v11 = token.len;
    p_audio = &v4->audio;
    if ( token.len + 1 > p_audio->alloced )
      idStr::ReAllocate(p_audio, token.len + 1, 0);
    qmemcpy(p_audio->data, token.data, v11);
    p_audio->data[v11] = 0;
    p_audio->len = v11;
    declManager->FindSound(declManager, this->audio.data, 1);
    goto LABEL_19;
  }
LABEL_21:
  if ( idLexer::HadError(&src) )
  {
    v13 = v4->base->GetName(v4->base);
    idLexer::Warning(&src, "Audio decl '%s' had a parse error", v13);
    LOBYTE(v18) = 0;
    idStr::FreeData(&token);
    v18 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
  else
  {
    LOBYTE(v18) = 0;
    idStr::FreeData(&token);
    v18 = -1;
    idLexer::~idLexer(&src);
    return 1;
  }
}

// FUNC: public: virtual void __thiscall idDeclPDA::FreeData(void)
void __thiscall idDeclPDA::FreeData(idDeclPDA *this)
{
  idStr *list; // eax
  char *v3; // edi
  idStr *v4; // eax
  char *v5; // edi
  idStr *v6; // eax
  char *v7; // edi

  list = this->videos.list;
  if ( list )
  {
    v3 = &list[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      list,
      0x20u,
      *(_DWORD *)&list[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v3);
  }
  this->videos.list = 0;
  this->videos.num = 0;
  this->videos.size = 0;
  v4 = this->audios.list;
  if ( v4 )
  {
    v5 = &v4[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v4,
      0x20u,
      *(_DWORD *)&v4[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v5);
  }
  this->audios.list = 0;
  this->audios.num = 0;
  this->audios.size = 0;
  v6 = this->emails.list;
  if ( v6 )
  {
    v7 = &v6[-1].baseBuffer[16];
    `eh vector destructor iterator'(
      v6,
      0x20u,
      *(_DWORD *)&v6[-1].baseBuffer[16],
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(v7);
  }
  this->emails.list = 0;
  this->emails.num = 0;
  this->emails.size = 0;
  this->originalEmails = 0;
  this->originalVideos = 0;
}

// FUNC: public: virtual void __thiscall idDeclPDA::RemoveAddedEmailsAndVideos(void)const
void __thiscall idDeclPDA::RemoveAddedEmailsAndVideos(idDeclPDA *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // eax
  idStr *list; // ecx
  unsigned int v7; // esi
  idStr *v8; // ebx
  int v9; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // eax
  idStr *v13; // edx
  unsigned int v14; // esi
  idStr *v15; // ebx
  int i; // [esp+10h] [ebp-10h]
  int j; // [esp+10h] [ebp-10h]
  int num; // [esp+14h] [ebp-Ch]
  int numa; // [esp+14h] [ebp-Ch]
  int v20; // [esp+18h] [ebp-8h]
  int v21; // [esp+18h] [ebp-8h]

  v2 = this->emails.num;
  if ( this->originalEmails < v2 && v2 )
  {
    do
    {
      if ( v2 <= this->originalEmails )
        break;
      num = --v2;
      if ( v2 >= 0 )
      {
        v3 = this->emails.num;
        if ( v2 < v3 )
        {
          v4 = v3 - 1;
          this->emails.num = v4;
          v20 = v2;
          if ( v2 < v4 )
          {
            v5 = 32 * v2;
            for ( i = v5; ; v5 = i )
            {
              list = this->emails.list;
              v7 = *(int *)((char *)&list[1].len + v5);
              v8 = (idStr *)((char *)list + v5);
              if ( (signed int)(v7 + 1) > *(int *)((char *)&list->alloced + v5) )
                idStr::ReAllocate(v8, v7 + 1, 0);
              i += 32;
              qmemcpy(v8->data, v8[1].data, v7);
              v8->data[v7] = 0;
              v8->len = v7;
              if ( ++v20 >= this->emails.num )
                break;
            }
            v2 = num;
          }
        }
      }
    }
    while ( v2 );
  }
  v9 = this->videos.num;
  if ( this->originalVideos < v9 && v9 )
  {
    do
    {
      if ( v9 <= this->originalVideos )
        break;
      numa = --v9;
      if ( v9 >= 0 )
      {
        v10 = this->videos.num;
        if ( v9 < v10 )
        {
          v11 = v10 - 1;
          this->videos.num = v11;
          v21 = v9;
          if ( v9 < v11 )
          {
            v12 = 32 * v9;
            for ( j = v12; ; v12 = j )
            {
              v13 = this->videos.list;
              v14 = *(int *)((char *)&v13[1].len + v12);
              v15 = (idStr *)((char *)v13 + v12);
              if ( (signed int)(v14 + 1) > *(int *)((char *)&v13->alloced + v12) )
                idStr::ReAllocate(v15, v14 + 1, 0);
              j += 32;
              qmemcpy(v15->data, v15[1].data, v14);
              v15->data[v14] = 0;
              v15->len = v14;
              if ( ++v21 >= this->videos.num )
                break;
            }
            v9 = numa;
          }
        }
      }
    }
    while ( v9 );
  }
}

// FUNC: public: virtual bool __thiscall idDeclPDA::Parse(char const *,int,bool)
char __thiscall idDeclPDA::Parse(idDeclPDA *this, const char *text, int textLength, bool noCaching)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // edx
  const char *v7; // esi
  int v8; // eax
  idStr *p_security; // ebx
  int v10; // esi
  bool v11; // cc
  int *v12; // eax
  idStr *v13; // edi
  idStr *v14; // ebx
  const void *v15; // esi
  int v16; // edi
  int v17; // eax
  int v18; // esi
  idStr *v19; // eax
  char *v20; // esi
  int *v21; // eax
  idStr *v22; // edi
  idStr *v23; // ebx
  const void *v24; // esi
  int v25; // esi
  idStr *v26; // ebx
  char *v27; // eax
  int v28; // esi
  int *v29; // eax
  idStr *v30; // ebx
  idStr *v31; // ebx
  const void *v32; // esi
  int v33; // edi
  int v34; // eax
  int v35; // esi
  idStr *v36; // eax
  char *v37; // esi
  int *v38; // eax
  idStr *v39; // edi
  idStr *v40; // ebx
  const void *v41; // esi
  int v42; // esi
  idStr *v43; // ebx
  char *v44; // eax
  int granularity; // esi
  int *v46; // eax
  idStr *v47; // ebx
  idStr *v48; // ebx
  const void *v49; // esi
  int num; // edi
  int size; // eax
  int v52; // esi
  idStr *v53; // eax
  char *v54; // esi
  int *v55; // eax
  idStr *v56; // edi
  idStr *v57; // ebx
  const void *v58; // esi
  int v59; // esi
  idStr *v60; // ebx
  char *data; // eax
  const char *v62; // eax
  int len; // [esp+Ch] [ebp-134h]
  int v65; // [esp+Ch] [ebp-134h]
  unsigned int v66; // [esp+Ch] [ebp-134h]
  int v67; // [esp+Ch] [ebp-134h]
  int v68; // [esp+Ch] [ebp-134h]
  int v69; // [esp+Ch] [ebp-134h]
  int v70; // [esp+Ch] [ebp-134h]
  int v71; // [esp+Ch] [ebp-134h]
  char *ptr; // [esp+10h] [ebp-130h]
  idStr *ptra; // [esp+10h] [ebp-130h]
  unsigned int *ptrb; // [esp+10h] [ebp-130h]
  char *ptrc; // [esp+10h] [ebp-130h]
  unsigned int *ptrd; // [esp+10h] [ebp-130h]
  char *ptre; // [esp+10h] [ebp-130h]
  unsigned int v78; // [esp+14h] [ebp-12Ch]
  int v79; // [esp+14h] [ebp-12Ch]
  unsigned int v80; // [esp+14h] [ebp-12Ch]
  unsigned int v81; // [esp+14h] [ebp-12Ch]
  int v82; // [esp+14h] [ebp-12Ch]
  unsigned int v83; // [esp+14h] [ebp-12Ch]
  unsigned int v84; // [esp+14h] [ebp-12Ch]
  int v85; // [esp+14h] [ebp-12Ch]
  unsigned int *v86; // [esp+18h] [ebp-128h]
  char *v87; // [esp+18h] [ebp-128h]
  idStr *v88; // [esp+18h] [ebp-128h]
  idStr *list; // [esp+18h] [ebp-128h]
  idToken token; // [esp+1Ch] [ebp-124h] BYREF
  idLexer src; // [esp+6Ch] [ebp-D4h] BYREF
  int v92; // [esp+13Ch] [ebp-4h]

  idLexer::idLexer(&src);
  token.floatvalue = 0.0;
  v92 = 0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  base = this->base;
  v6 = base->__vftable;
  LOBYTE(v92) = 1;
  v7 = v6->GetFileName(base);
  v8 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&src, text, textLength, v7, v8);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  while ( idLexer::ReadToken(&src, &token) )
  {
    if ( !idStr::Cmp(token.data, "}") )
      break;
    if ( !idStr::Icmp(token.data, "name") )
    {
      idLexer::ReadToken(&src, &token);
      len = token.len;
      if ( token.len + 1 > this->pdaName.alloced )
        idStr::ReAllocate(&this->pdaName, token.len + 1, 0);
      qmemcpy(this->pdaName.data, token.data, len);
      this->pdaName.data[len] = 0;
      this->pdaName.len = len;
      continue;
    }
    if ( idStr::Icmp(token.data, "fullname") )
    {
      if ( idStr::Icmp(token.data, "icon") )
      {
        if ( idStr::Icmp(token.data, "id") )
        {
          if ( idStr::Icmp(token.data, "post") )
          {
            if ( idStr::Icmp(token.data, "title") )
            {
              if ( idStr::Icmp(token.data, "security") )
              {
                if ( idStr::Icmp(token.data, "pda_email") )
                {
                  if ( idStr::Icmp(token.data, "pda_audio") )
                  {
                    if ( !idStr::Icmp(token.data, "pda_video") )
                    {
                      idLexer::ReadToken(&src, &token);
                      if ( !this->videos.list )
                      {
                        granularity = this->videos.granularity;
                        if ( granularity > 0 )
                        {
                          if ( granularity != this->videos.size )
                          {
                            v11 = granularity < this->videos.num;
                            this->videos.size = granularity;
                            if ( v11 )
                              this->videos.num = granularity;
                            v46 = (int *)Memory::Allocate(32 * granularity + 4);
                            LOBYTE(v92) = 6;
                            if ( v46 )
                            {
                              v47 = (idStr *)(v46 + 1);
                              *v46 = granularity;
                              `eh vector constructor iterator'(
                                v46 + 1,
                                0x20u,
                                granularity,
                                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                            }
                            else
                            {
                              v47 = 0;
                            }
                            v11 = this->videos.num <= 0;
                            LOBYTE(v92) = 1;
                            this->videos.list = v47;
                            v70 = 0;
                            if ( !v11 )
                            {
                              ptrd = 0;
                              do
                              {
                                v48 = (idStr *)((char *)ptrd + (unsigned int)this->videos.list);
                                v83 = *ptrd;
                                if ( (signed int)(*ptrd + 1) > v48->alloced )
                                  idStr::ReAllocate(v48, v83 + 1, 0);
                                v49 = (const void *)ptrd[1];
                                ptrd += 8;
                                qmemcpy(v48->data, v49, v83);
                                v48->data[v83] = 0;
                                v48->len = v83;
                                ++v70;
                              }
                              while ( v70 < this->videos.num );
                            }
                          }
                        }
                        else
                        {
                          this->videos.list = 0;
                          this->videos.num = 0;
                          this->videos.size = 0;
                        }
                      }
                      num = this->videos.num;
                      size = this->videos.size;
                      if ( num == size )
                      {
                        if ( !this->videos.granularity )
                          this->videos.granularity = 16;
                        v52 = size
                            + this->videos.granularity
                            - (size + this->videos.granularity) % this->videos.granularity;
                        if ( v52 > 0 )
                        {
                          if ( v52 != this->videos.size )
                          {
                            list = this->videos.list;
                            this->videos.size = v52;
                            if ( v52 < num )
                              this->videos.num = v52;
                            v55 = (int *)Memory::Allocate(32 * v52 + 4);
                            LOBYTE(v92) = 7;
                            if ( v55 )
                            {
                              v56 = (idStr *)(v55 + 1);
                              *v55 = v52;
                              `eh vector constructor iterator'(
                                v55 + 1,
                                0x20u,
                                v52,
                                (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                                (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                            }
                            else
                            {
                              v56 = 0;
                            }
                            v11 = this->videos.num <= 0;
                            LOBYTE(v92) = 1;
                            this->videos.list = v56;
                            v71 = 0;
                            if ( !v11 )
                            {
                              ptre = 0;
                              do
                              {
                                v57 = (idStr *)&ptre[(unsigned int)this->videos.list];
                                v84 = *(_DWORD *)&ptre[(_DWORD)list];
                                if ( (signed int)(v84 + 1) > v57->alloced )
                                  idStr::ReAllocate(v57, v84 + 1, 0);
                                v58 = *(const void **)&ptre[(_DWORD)list + 4];
                                ptre += 32;
                                qmemcpy(v57->data, v58, v84);
                                v57->data[v84] = 0;
                                v57->len = v84;
                                ++v71;
                              }
                              while ( v71 < this->videos.num );
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
                          }
                        }
                        else
                        {
                          v53 = this->videos.list;
                          if ( v53 )
                          {
                            v54 = &v53[-1].baseBuffer[16];
                            `eh vector destructor iterator'(
                              v53,
                              0x20u,
                              *(_DWORD *)&v53[-1].baseBuffer[16],
                              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                            Memory::Free(v54);
                          }
                          this->videos.list = 0;
                          this->videos.num = 0;
                          this->videos.size = 0;
                        }
                      }
                      v59 = token.len;
                      v60 = &this->videos.list[this->videos.num];
                      v85 = token.len;
                      if ( token.len + 1 > v60->alloced )
                        idStr::ReAllocate(v60, token.len + 1, 0);
                      qmemcpy(v60->data, token.data, v59);
                      v60->data[v85] = 0;
                      v60->len = v85;
                      data = token.data;
                      ++this->videos.num;
                      declManager->FindType(declManager, DECL_VIDEO, data, 1, 0);
                    }
                  }
                  else
                  {
                    idLexer::ReadToken(&src, &token);
                    if ( !this->audios.list )
                    {
                      v28 = this->audios.granularity;
                      if ( v28 > 0 )
                      {
                        if ( v28 != this->audios.size )
                        {
                          v11 = v28 < this->audios.num;
                          this->audios.size = v28;
                          if ( v11 )
                            this->audios.num = v28;
                          v29 = (int *)Memory::Allocate(32 * v28 + 4);
                          LOBYTE(v92) = 4;
                          if ( v29 )
                          {
                            v30 = (idStr *)(v29 + 1);
                            *v29 = v28;
                            `eh vector constructor iterator'(
                              v29 + 1,
                              0x20u,
                              v28,
                              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                          }
                          else
                          {
                            v30 = 0;
                          }
                          v11 = this->audios.num <= 0;
                          LOBYTE(v92) = 1;
                          this->audios.list = v30;
                          v68 = 0;
                          if ( !v11 )
                          {
                            ptrb = 0;
                            do
                            {
                              v31 = (idStr *)((char *)ptrb + (unsigned int)this->audios.list);
                              v80 = *ptrb;
                              if ( (signed int)(*ptrb + 1) > v31->alloced )
                                idStr::ReAllocate(v31, v80 + 1, 0);
                              v32 = (const void *)ptrb[1];
                              ptrb += 8;
                              qmemcpy(v31->data, v32, v80);
                              v31->data[v80] = 0;
                              v31->len = v80;
                              ++v68;
                            }
                            while ( v68 < this->audios.num );
                          }
                        }
                      }
                      else
                      {
                        this->audios.list = 0;
                        this->audios.num = 0;
                        this->audios.size = 0;
                      }
                    }
                    v33 = this->audios.num;
                    v34 = this->audios.size;
                    if ( v33 == v34 )
                    {
                      if ( !this->audios.granularity )
                        this->audios.granularity = 16;
                      v35 = v34 + this->audios.granularity - (v34 + this->audios.granularity) % this->audios.granularity;
                      if ( v35 > 0 )
                      {
                        if ( v35 != this->audios.size )
                        {
                          v88 = this->audios.list;
                          this->audios.size = v35;
                          if ( v35 < v33 )
                            this->audios.num = v35;
                          v38 = (int *)Memory::Allocate(32 * v35 + 4);
                          LOBYTE(v92) = 5;
                          if ( v38 )
                          {
                            v39 = (idStr *)(v38 + 1);
                            *v38 = v35;
                            `eh vector constructor iterator'(
                              v38 + 1,
                              0x20u,
                              v35,
                              (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                          }
                          else
                          {
                            v39 = 0;
                          }
                          v11 = this->audios.num <= 0;
                          LOBYTE(v92) = 1;
                          this->audios.list = v39;
                          v69 = 0;
                          if ( !v11 )
                          {
                            ptrc = 0;
                            do
                            {
                              v40 = (idStr *)&ptrc[(unsigned int)this->audios.list];
                              v81 = *(_DWORD *)&ptrc[(_DWORD)v88];
                              if ( (signed int)(v81 + 1) > v40->alloced )
                                idStr::ReAllocate(v40, v81 + 1, 0);
                              v41 = *(const void **)&ptrc[(_DWORD)v88 + 4];
                              ptrc += 32;
                              qmemcpy(v40->data, v41, v81);
                              v40->data[v81] = 0;
                              v40->len = v81;
                              ++v69;
                            }
                            while ( v69 < this->audios.num );
                          }
                          if ( v88 )
                          {
                            `eh vector destructor iterator'(
                              v88,
                              0x20u,
                              *(_DWORD *)&v88[-1].baseBuffer[16],
                              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                            Memory::Free(&v88[-1].baseBuffer[16]);
                          }
                        }
                      }
                      else
                      {
                        v36 = this->audios.list;
                        if ( v36 )
                        {
                          v37 = &v36[-1].baseBuffer[16];
                          `eh vector destructor iterator'(
                            v36,
                            0x20u,
                            *(_DWORD *)&v36[-1].baseBuffer[16],
                            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                          Memory::Free(v37);
                        }
                        this->audios.list = 0;
                        this->audios.num = 0;
                        this->audios.size = 0;
                      }
                    }
                    v42 = token.len;
                    v43 = &this->audios.list[this->audios.num];
                    v82 = token.len;
                    if ( token.len + 1 > v43->alloced )
                      idStr::ReAllocate(v43, token.len + 1, 0);
                    qmemcpy(v43->data, token.data, v42);
                    v43->data[v82] = 0;
                    v43->len = v82;
                    v44 = token.data;
                    ++this->audios.num;
                    declManager->FindType(declManager, DECL_AUDIO, v44, 1, 0);
                  }
                }
                else
                {
                  idLexer::ReadToken(&src, &token);
                  if ( !this->emails.list )
                  {
                    v10 = this->emails.granularity;
                    if ( v10 > 0 )
                    {
                      if ( v10 != this->emails.size )
                      {
                        v11 = v10 < this->emails.num;
                        this->emails.size = v10;
                        if ( v11 )
                          this->emails.num = v10;
                        v12 = (int *)Memory::Allocate(32 * v10 + 4);
                        LOBYTE(v92) = 2;
                        if ( v12 )
                        {
                          v13 = (idStr *)(v12 + 1);
                          *v12 = v10;
                          `eh vector constructor iterator'(
                            v12 + 1,
                            0x20u,
                            v10,
                            (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        }
                        else
                        {
                          v13 = 0;
                        }
                        v11 = this->emails.num <= 0;
                        LOBYTE(v92) = 1;
                        this->emails.list = v13;
                        ptr = 0;
                        if ( !v11 )
                        {
                          v86 = 0;
                          do
                          {
                            v14 = (idStr *)((char *)v86 + (unsigned int)this->emails.list);
                            v66 = *v86;
                            if ( (signed int)(*v86 + 1) > v14->alloced )
                              idStr::ReAllocate(v14, v66 + 1, 0);
                            v15 = (const void *)v86[1];
                            v86 += 8;
                            qmemcpy(v14->data, v15, v66);
                            v14->data[v66] = 0;
                            v14->len = v66;
                            ++ptr;
                          }
                          while ( (int)ptr < this->emails.num );
                        }
                      }
                    }
                    else
                    {
                      this->emails.list = 0;
                      this->emails.num = 0;
                      this->emails.size = 0;
                    }
                  }
                  v16 = this->emails.num;
                  v17 = this->emails.size;
                  if ( v16 == v17 )
                  {
                    if ( !this->emails.granularity )
                      this->emails.granularity = 16;
                    v18 = v17 + this->emails.granularity - (v17 + this->emails.granularity) % this->emails.granularity;
                    if ( v18 > 0 )
                    {
                      if ( v18 != this->emails.size )
                      {
                        ptra = this->emails.list;
                        this->emails.size = v18;
                        if ( v18 < v16 )
                          this->emails.num = v18;
                        v21 = (int *)Memory::Allocate(32 * v18 + 4);
                        LOBYTE(v92) = 3;
                        if ( v21 )
                        {
                          v22 = (idStr *)(v21 + 1);
                          *v21 = v18;
                          `eh vector constructor iterator'(
                            v21 + 1,
                            0x20u,
                            v18,
                            (void (__thiscall *)(void *))fileInPack_s::fileInPack_s,
                            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        }
                        else
                        {
                          v22 = 0;
                        }
                        v11 = this->emails.num <= 0;
                        LOBYTE(v92) = 1;
                        this->emails.list = v22;
                        v67 = 0;
                        if ( !v11 )
                        {
                          v87 = 0;
                          do
                          {
                            v23 = (idStr *)&v87[(unsigned int)this->emails.list];
                            v78 = *(_DWORD *)&v87[(_DWORD)ptra];
                            if ( (signed int)(v78 + 1) > v23->alloced )
                              idStr::ReAllocate(v23, v78 + 1, 0);
                            v24 = *(const void **)&v87[(_DWORD)ptra + 4];
                            v87 += 32;
                            qmemcpy(v23->data, v24, v78);
                            v23->data[v78] = 0;
                            v23->len = v78;
                            ++v67;
                          }
                          while ( v67 < this->emails.num );
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
                      v19 = this->emails.list;
                      if ( v19 )
                      {
                        v20 = &v19[-1].baseBuffer[16];
                        `eh vector destructor iterator'(
                          v19,
                          0x20u,
                          *(_DWORD *)&v19[-1].baseBuffer[16],
                          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
                        Memory::Free(v20);
                      }
                      this->emails.list = 0;
                      this->emails.num = 0;
                      this->emails.size = 0;
                    }
                  }
                  v25 = token.len;
                  v26 = &this->emails.list[this->emails.num];
                  v79 = token.len;
                  if ( token.len + 1 > v26->alloced )
                    idStr::ReAllocate(v26, token.len + 1, 0);
                  qmemcpy(v26->data, token.data, v25);
                  v26->data[v79] = 0;
                  v26->len = v79;
                  v27 = token.data;
                  ++this->emails.num;
                  declManager->FindType(declManager, DECL_EMAIL, v27, 1, 0);
                }
                continue;
              }
              idLexer::ReadToken(&src, &token);
              v65 = token.len;
              p_security = &this->security;
              if ( token.len + 1 > this->security.alloced )
                idStr::ReAllocate(&this->security, token.len + 1, 0);
LABEL_25:
              qmemcpy(p_security->data, token.data, v65);
              p_security->data[v65] = 0;
              p_security->len = v65;
              continue;
            }
            idLexer::ReadToken(&src, &token);
            v65 = token.len;
            p_security = &this->title;
            if ( token.len + 1 <= this->title.alloced )
              goto LABEL_25;
            idStr::ReAllocate(&this->title, token.len + 1, 0);
            qmemcpy(this->title.data, token.data, v65);
            this->title.data[v65] = 0;
            p_security->len = v65;
          }
          else
          {
            idLexer::ReadToken(&src, &token);
            v65 = token.len;
            p_security = &this->post;
            if ( token.len + 1 <= this->post.alloced )
              goto LABEL_25;
            idStr::ReAllocate(&this->post, token.len + 1, 0);
            qmemcpy(this->post.data, token.data, v65);
            this->post.data[v65] = 0;
            p_security->len = v65;
          }
        }
        else
        {
          idLexer::ReadToken(&src, &token);
          v65 = token.len;
          p_security = &this->id;
          if ( token.len + 1 <= this->id.alloced )
            goto LABEL_25;
          idStr::ReAllocate(&this->id, token.len + 1, 0);
          qmemcpy(this->id.data, token.data, v65);
          this->id.data[v65] = 0;
          p_security->len = v65;
        }
      }
      else
      {
        idLexer::ReadToken(&src, &token);
        v65 = token.len;
        p_security = &this->icon;
        if ( token.len + 1 <= this->icon.alloced )
          goto LABEL_25;
        idStr::ReAllocate(&this->icon, token.len + 1, 0);
        qmemcpy(this->icon.data, token.data, v65);
        this->icon.data[v65] = 0;
        p_security->len = v65;
      }
    }
    else
    {
      idLexer::ReadToken(&src, &token);
      v65 = token.len;
      p_security = &this->fullName;
      if ( token.len + 1 <= this->fullName.alloced )
        goto LABEL_25;
      idStr::ReAllocate(&this->fullName, token.len + 1, 0);
      qmemcpy(this->fullName.data, token.data, v65);
      this->fullName.data[v65] = 0;
      p_security->len = v65;
    }
  }
  if ( idLexer::HadError(&src) )
  {
    v62 = this->base->GetName(this->base);
    idLexer::Warning(&src, "PDA decl '%s' had a parse error", v62);
    LOBYTE(v92) = 0;
    idStr::FreeData(&token);
    v92 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
  else
  {
    this->originalVideos = this->videos.num;
    this->originalEmails = this->emails.num;
    LOBYTE(v92) = 0;
    idStr::FreeData(&token);
    v92 = -1;
    idLexer::~idLexer(&src);
    return 1;
  }
}
