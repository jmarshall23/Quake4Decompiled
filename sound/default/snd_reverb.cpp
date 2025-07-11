
// FUNC: public: virtual char const * __thiscall idSoundSystemLocal::GetReverbName(int)
const char *__thiscall idSoundSystemLocal::GetReverbName(idSoundSystemLocal *this, int reverb)
{
  if ( this->efxloaded && idEFXFile::GetEffectName(&this->EFXDatabase, reverb, (idStr **)&reverb) )
    return *(const char **)(reverb + 4);
  else
    return 0;
}

// FUNC: public: virtual bool __thiscall idSoundSystemLocal::SetReverb(int,char const *,char const *)
char __thiscall idSoundSystemLocal::SetReverb(
        idSoundSystemLocal *this,
        int area,
        const char *reverbName,
        const char *fileName)
{
  int v5; // edi
  const char *v6; // eax

  if ( area < 0 || area >= this->areaReverbs.num )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "Invalid reverb area number %d [0,%d] in '%s'",
      area,
      this->areaReverbs.num,
      fileName);
    return 0;
  }
  else
  {
    v5 = 0;
    if ( this->GetReverbName(this, 0) )
    {
      while ( 1 )
      {
        v6 = this->GetReverbName(this, v5);
        if ( !idStr::Icmp(v6, reverbName) )
          break;
        if ( !this->GetReverbName(this, ++v5) )
          goto LABEL_6;
      }
      this->areaReverbs.list[area] = v5;
      return 1;
    }
    else
    {
LABEL_6:
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "Unknown reverb type '%s' in '%s'",
        reverbName,
        fileName);
      return 0;
    }
  }
}

// FUNC: public: virtual int __thiscall idSoundSystemLocal::GetReverb(int)
int __thiscall idSoundSystemLocal::GetReverb(idSoundSystemLocal *this, int area)
{
  if ( area < 0 || area >= this->areaReverbs.num )
    return 0;
  else
    return this->areaReverbs.list[area];
}

// FUNC: public: void __thiscall idSoundSystemLocal::LoadReverbData(char const *)
void __userpurge idSoundSystemLocal::LoadReverbData(idSoundSystemLocal *this@<ecx>, int a2@<edi>, char *mapName)
{
  int *list; // eax
  idRenderWorld *v5; // eax
  int v6; // eax
  bool v7; // cc
  int granularity; // ecx
  int v9; // edi
  int size; // eax
  int *v11; // ebp
  int i; // eax
  int j; // eax
  int v14; // edi
  idStr reverbName; // [esp+14h] [ebp-148h] BYREF
  int v16; // [esp+34h] [ebp-128h]
  idToken token; // [esp+38h] [ebp-124h] BYREF
  idLexer parser; // [esp+88h] [ebp-D4h] BYREF
  int v19; // [esp+158h] [ebp-4h]

  reverbName.len = 0;
  reverbName.alloced = 20;
  reverbName.data = reverbName.baseBuffer;
  reverbName.baseBuffer[0] = 0;
  token.floatvalue = 0.0;
  v19 = 1;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  idLexer::idLexer(&parser);
  list = this->areaReverbs.list;
  LOBYTE(v19) = 2;
  if ( list )
    Memory::Free(list);
  this->areaReverbs.list = 0;
  this->areaReverbs.num = 0;
  this->areaReverbs.size = 0;
  v5 = session->GetGameRenderWorld(session);
  if ( v5 )
  {
    v6 = v5->NumAreas(v5);
    v7 = v6 <= this->areaReverbs.size;
    v16 = v6;
    if ( !v7 )
    {
      if ( !this->areaReverbs.granularity )
        this->areaReverbs.granularity = 16;
      granularity = this->areaReverbs.granularity;
      v9 = v6 + granularity - 1;
      size = this->areaReverbs.size;
      this->areaReverbs.num = size;
      a2 = v9 - v9 % granularity;
      if ( a2 > 0 )
      {
        if ( a2 != size )
        {
          v7 = a2 < this->areaReverbs.num;
          v11 = this->areaReverbs.list;
          this->areaReverbs.size = a2;
          if ( v7 )
            this->areaReverbs.num = a2;
          this->areaReverbs.list = (int *)Memory::Allocate(4 * a2);
          for ( i = 0; i < this->areaReverbs.num; ++i )
            this->areaReverbs.list[i] = v11[i];
          if ( v11 )
            Memory::Free(v11);
        }
      }
      else
      {
        if ( this->areaReverbs.list )
          Memory::Free(this->areaReverbs.list);
        this->areaReverbs.list = 0;
        this->areaReverbs.num = 0;
        this->areaReverbs.size = 0;
      }
      for ( j = this->areaReverbs.num; j < a2; ++j )
        this->areaReverbs.list[j] = 0;
    }
    this->areaReverbs.num = v16;
  }
  if ( mapName )
  {
    idStr::operator=(&reverbName, mapName);
    idStr::SetFileExtension(&reverbName, ".reverb");
    if ( fileSystem->ReadFile(fileSystem, reverbName.data, 0, 0) >= 0 )
    {
      if ( idLexer::LoadFile(&parser, 0, a2, reverbName.data, 0) )
      {
        idLexer::ReadToken(&parser, &token);
        if ( idStr::Icmp(token.data, "reverb") )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "Malformed reverb file header in '%s'",
            reverbName.data);
        }
        else
        {
          idLexer::SkipUntilString(&parser, "{");
          idLexer::ReadToken(&parser, &token);
          if ( idStr::Cmp(token.data, "}") )
          {
            while ( !idStr::Cmp(token.data, "{") )
            {
              v14 = idLexer::ParseInt(&parser);
              idLexer::ReadToken(&parser, &token);
              this->SetReverb(this, v14, token.data, reverbName.data);
              idLexer::ReadToken(&parser, &token);
              if ( idStr::Cmp(token.data, "}") )
                break;
              idLexer::ReadToken(&parser, &token);
              if ( !idStr::Cmp(token.data, "}") )
                goto LABEL_30;
            }
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
              common.type,
              "Malformed reverb file '%s' line %d",
              reverbName.data,
              parser.line);
          }
          else
          {
LABEL_30:
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
              common.type,
              "Loaded reverb file '%s'\n",
              reverbName.data);
          }
        }
      }
    }
  }
  LOBYTE(v19) = 1;
  idLexer::~idLexer(&parser);
  LOBYTE(v19) = 0;
  idStr::FreeData(&token);
  v19 = -1;
  idStr::FreeData(&reverbName);
}
