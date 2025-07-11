
// FUNC: private: void __thiscall idSoundShader::Init(void)
void __thiscall idSoundShader::Init(idSoundShader *this)
{
  idStr::operator=(&this->desc, "<no description>");
  this->errorDuringParse = 0;
  this->noShakes = 0;
  this->frequentlyUsed = 0;
  this->playCount = 0;
  this->numEntries = 0;
  this->numLeadins = 0;
  this->leadinVolume = 1.0;
  this->altSound = 0;
}

// FUNC: public: virtual char const * __thiscall idSoundShader::DefaultDefinition(void)const
const char *__thiscall idSoundShader::DefaultDefinition(idSoundShader *this)
{
  return "{\n\tsound/_default.wav\n}";
}

// FUNC: public: virtual bool __thiscall idSoundShader::HasDefaultSound(void)const
char __thiscall idSoundShader::HasDefaultSound(idSoundShader *this)
{
  int numEntries; // esi
  int v2; // eax
  rvCommonSample **i; // edx

  numEntries = this->numEntries;
  v2 = 0;
  if ( numEntries <= 0 )
    return 0;
  for ( i = this->entries; !*i || !(*i)->defaultSound; ++i )
  {
    if ( ++v2 >= numEntries )
      return 0;
  }
  return 1;
}

// FUNC: public: virtual int __thiscall idSoundShader::GetNumSounds(void)const
int __thiscall idSoundShader::GetNumSounds(idSoundShader *this)
{
  return this->numLeadins + this->numEntries;
}

// FUNC: public: float __thiscall idSoundShader::GetTimeLength(void)const
double __thiscall idSoundShader::GetTimeLength(idSoundShader *this)
{
  int v2; // esi
  rvCommonSample **entries; // edi
  double v4; // st7
  float longest; // [esp+8h] [ebp-4h]

  v2 = 0;
  longest = 0.0;
  if ( this->numEntries > 0 )
  {
    entries = this->entries;
    do
    {
      if ( *entries )
      {
        v4 = ((double (__thiscall *)(rvCommonSample *))(*entries)->GetDuration)(*entries);
        if ( v4 > longest )
          longest = v4;
      }
      ++v2;
      ++entries;
    }
    while ( v2 < this->numEntries );
  }
  return longest;
}

// FUNC: public: void __thiscall idSoundShader::Purge(bool)
void __thiscall idSoundShader::Purge(idSoundShader *this, bool freeBaseBlocks)
{
  int v3; // edi
  rvCommonSample **leadins; // ebx
  int v5; // ebx
  rvCommonSample **entries; // edi

  v3 = 0;
  if ( this->numLeadins > 0 )
  {
    leadins = this->leadins;
    do
    {
      if ( *leadins )
        (*leadins)->PurgeSoundSample(*leadins);
      ++v3;
      ++leadins;
    }
    while ( v3 < this->numLeadins );
  }
  v5 = 0;
  if ( this->numEntries > 0 )
  {
    entries = this->entries;
    do
    {
      if ( *entries )
        (*entries)->PurgeSoundSample(*entries);
      ++v5;
      ++entries;
    }
    while ( v5 < this->numEntries );
  }
  if ( freeBaseBlocks )
    soundSystem->CleanCache(soundSystem);
}

// FUNC: public: void __thiscall idSoundShader::LoadSampleData(int)
void __thiscall idSoundShader::LoadSampleData(idSoundShader *this, int langIndex)
{
  int v3; // edi
  rvCommonSample **leadins; // ebx
  int v5; // edi
  rvCommonSample **entries; // ebx

  v3 = 0;
  if ( this->numLeadins > 0 )
  {
    leadins = this->leadins;
    do
    {
      (*leadins)->Load(*leadins, langIndex);
      ++v3;
      ++leadins;
    }
    while ( v3 < this->numLeadins );
  }
  v5 = 0;
  if ( this->numEntries > 0 )
  {
    entries = this->entries;
    do
    {
      (*entries)->Load(*entries, langIndex);
      ++v5;
      ++entries;
    }
    while ( v5 < this->numEntries );
  }
}

// FUNC: public: virtual unsigned int __thiscall idSoundShader::Size(void)const
int __thiscall idSoundShader::Size(idSoundShader *this)
{
  if ( this->desc.data == this->desc.baseBuffer )
    return 384;
  else
    return this->desc.alloced + 384;
}

// FUNC: public: virtual void __thiscall idSoundShader::SetReferencedThisLevel(void)
void __thiscall idSoundShader::SetReferencedThisLevel(idSoundShader *this)
{
  int v2; // eax
  rvCommonSample **leadins; // ecx
  int v4; // eax
  rvCommonSample **entries; // ecx

  this->base->SetReferencedThisLevel(this->base);
  v2 = 0;
  if ( this->numLeadins > 0 )
  {
    leadins = this->leadins;
    do
    {
      ++v2;
      (*leadins++)->levelLoadReferenced = 1;
    }
    while ( v2 < this->numLeadins );
  }
  v4 = 0;
  if ( this->numEntries > 0 )
  {
    entries = this->entries;
    do
    {
      ++v4;
      (*entries++)->levelLoadReferenced = 1;
    }
    while ( v4 < this->numEntries );
  }
}

// FUNC: public: virtual bool __thiscall idSoundShader::SetDefaultText(void)
char __thiscall idSoundShader::SetDefaultText(idSoundShader *this)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v3; // edx
  char *v4; // eax
  const char *v5; // eax
  const char *v7; // [esp-4h] [ebp-834h]
  idStr wavname; // [esp+4h] [ebp-82Ch] BYREF
  char generated[2048]; // [esp+24h] [ebp-80Ch] BYREF
  int v10; // [esp+82Ch] [ebp-4h]

  wavname.len = 0;
  wavname.alloced = 20;
  wavname.data = wavname.baseBuffer;
  wavname.baseBuffer[0] = 0;
  base = this->base;
  v3 = base->__vftable;
  v10 = 0;
  v4 = (char *)v3->GetName(base);
  idStr::operator=(&wavname, v4);
  idStr::DefaultFileExtension(&wavname, ".wav");
  v5 = (const char *)((int (__thiscall *)(idDeclBase *, char *))this->base->GetName)(this->base, wavname.data);
  idStr::snPrintf(generated, 2048, "sound %s // IMPLICITLY GENERATED\n{\n%s\n}\n", v5, v7);
  this->base->SetText(this->base, generated);
  v10 = -1;
  idStr::FreeData(&wavname);
  return 1;
}

// FUNC: public: virtual char const * __thiscall idSoundShader::GetSound(int)const
char *__thiscall idSoundShader::GetSound(idSoundShader *this, int index)
{
  int numLeadins; // edx

  if ( index < 0 )
    return (char *)&entityFilter;
  numLeadins = this->numLeadins;
  if ( index < numLeadins )
    return this->leadins[index]->name.data;
  if ( index - numLeadins >= this->numEntries )
    return (char *)&entityFilter;
  else
    return this->entries[index - numLeadins]->name.data;
}

// FUNC: public: virtual bool __thiscall idSoundShader::RebuildTextSource(void)
char __thiscall idSoundShader::RebuildTextSource(idSoundShader *this)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v3; // eax
  int v4; // ebp
  const char *v5; // eax
  double v6; // st7
  const idSoundShader *altSound; // eax
  const char *v8; // eax
  int v9; // edi
  rvCommonSample **leadins; // ebx
  int v11; // edi
  rvCommonSample **entries; // ebx
  idFile_Memory f; // [esp+28h] [ebp-4Ch] BYREF
  int v15; // [esp+70h] [ebp-4h]

  idFile_Memory::idFile_Memory(&f);
  base = this->base;
  v3 = base->__vftable;
  v4 = 0;
  v15 = 0;
  v5 = v3->GetName(base);
  idFile_Common::WriteFloatString(&f, "\r\n\r\nsound %s\r\n{\r\n", v5);
  if ( this->desc.len && idStr::Icmp(this->desc.data, "<no description>") )
    idFile_Common::WriteFloatString(&f, "\tdescription\t\"%s\"\r\n\r\n", this->desc.data);
  idFile_Common::WriteFloatString(&f, "\tminDistance\t%d\r\n", (int)this->parms.minDistance);
  idFile_Common::WriteFloatString(&f, "\tmaxDistance\t%d\r\n", (int)this->parms.maxDistance);
  v6 = idMath::ScaleToDb(this->parms.volume);
  idFile_Common::WriteFloatString(&f, "\tvolumeDb\t%.2g\r\n", v6);
  if ( LODWORD(this->minFrequencyShift) != 1065353216 || LODWORD(this->maxFrequencyShift) != 1065353216 )
    idFile_Common::WriteFloatString(
      &f,
      "\tfrequencyshift\t%.4g,%.4g\r\n",
      this->minFrequencyShift,
      this->maxFrequencyShift);
  if ( this->parms.shakes != 0.0 )
    idFile_Common::WriteFloatString(&f, "\tshakes\t\t%.2g\r\n", this->parms.shakes);
  altSound = this->altSound;
  if ( altSound )
  {
    v8 = altSound->base->GetName(altSound->base);
    idFile_Common::WriteFloatString(&f, "\taltSound\t%s\r\n", v8);
  }
  if ( (this->parms.soundShaderFlags & 1) != 0 )
    idFile_Common::WriteFloatString(&f, "\tprivate\r\n");
  if ( (this->parms.soundShaderFlags & 2) != 0 )
    idFile_Common::WriteFloatString(&f, "\tantiPrivate\r\n");
  if ( (this->parms.soundShaderFlags & 4) != 0 )
    idFile_Common::WriteFloatString(&f, "\tno_occlusion\r\n");
  if ( (this->parms.soundShaderFlags & 8) != 0 )
    idFile_Common::WriteFloatString(&f, "\tglobal\r\n");
  if ( (this->parms.soundShaderFlags & 0x10) != 0 )
    idFile_Common::WriteFloatString(&f, "\tomnidirectional\r\n");
  if ( (this->parms.soundShaderFlags & 0x20) != 0 )
    idFile_Common::WriteFloatString(&f, "\tlooping\r\n");
  if ( (this->parms.soundShaderFlags & 0x40) != 0 )
    idFile_Common::WriteFloatString(&f, "\tplayOnce\r\n");
  if ( (this->parms.soundShaderFlags & 0x80) != 0 )
    idFile_Common::WriteFloatString(&f, "\tunclamped\r\n");
  if ( (this->parms.soundShaderFlags & 0x100) != 0 )
    idFile_Common::WriteFloatString(&f, "\tno_flicker\r\n");
  if ( (this->parms.soundShaderFlags & 0x200) != 0 )
    idFile_Common::WriteFloatString(&f, "\tno_dups\r\n");
  if ( (this->parms.soundShaderFlags & 0x800) != 0 )
    idFile_Common::WriteFloatString(&f, "\tnoRandomStart\r\n");
  if ( this->noShakes )
    idFile_Common::WriteFloatString(&f, "\tno_shakes\r\n");
  idFile_Common::WriteFloatString(&f, "\r\n");
  v9 = 0;
  if ( this->numLeadins > 0 )
  {
    leadins = this->leadins;
    do
    {
      idFile_Common::WriteFloatString(&f, "\tleadin\t%s\r\n", (*leadins)->name.data);
      ++v9;
      ++leadins;
    }
    while ( v9 < this->numLeadins );
  }
  v11 = 0;
  if ( this->numEntries > 0 )
  {
    entries = this->entries;
    do
    {
      idFile_Common::WriteFloatString(&f, "\t%s\r\n", (*entries)->name.data);
      if ( v11 < this->shakes.num )
        idFile_Common::WriteFloatString(&f, "\tshakeData %d %s\r\n", v11, this->shakes.list[v4].data);
      ++v11;
      ++entries;
      ++v4;
    }
    while ( v11 < this->numEntries );
  }
  idFile_Common::WriteFloatString(&f, "}\r\n");
  this->base->SetText(this->base, f.filePtr);
  v15 = -1;
  idFile_Memory::~idFile_Memory(&f);
  return 1;
}

// FUNC: public: void __thiscall idSoundShader::ExpandSmallOggs(bool)
void __thiscall idSoundShader::ExpandSmallOggs(idSoundShader *this, BOOL force)
{
  int v4; // ebp
  rvCommonSample **leadins; // esi
  int v6; // ebp
  rvCommonSample **entries; // esi
  float forcea; // [esp+14h] [ebp+4h]
  float forceb; // [esp+14h] [ebp+4h]

  v4 = 0;
  if ( this->numLeadins > 0 )
  {
    leadins = this->leadins;
    do
    {
      if ( !(*leadins)->purged )
      {
        if ( ((unsigned __int8 (*)(void))(*leadins)->IsOgg)() )
        {
          if ( force
            || this->frequentlyUsed
            || (forcea = s_decompressionLimit.internalVar->floatValue,
                ((double (__thiscall *)(rvCommonSample *))(*leadins)->GetDuration)(*leadins) < forcea) )
          {
            (*leadins)->Expand(*leadins, force);
          }
        }
      }
      ++v4;
      ++leadins;
    }
    while ( v4 < this->numLeadins );
  }
  v6 = 0;
  if ( this->numEntries > 0 )
  {
    entries = this->entries;
    do
    {
      if ( !(*entries)->purged && (*entries)->IsOgg(*entries) )
      {
        if ( force
          || this->frequentlyUsed
          || (forceb = s_decompressionLimit.internalVar->floatValue,
              ((double (__thiscall *)(rvCommonSample *))(*entries)->GetDuration)(*entries) < forceb) )
        {
          (*entries)->Expand(*entries, force);
        }
      }
      ++v6;
      ++entries;
    }
    while ( v6 < this->numEntries );
  }
}

// FUNC: public: char const * __thiscall idSoundShader::GetShakeData(int)const
char *__thiscall idSoundShader::GetShakeData(idSoundShader *this, int index)
{
  if ( index < 0 || index >= this->shakes.num )
    return (char *)&entityFilter;
  else
    return this->shakes.list[index].data;
}

// FUNC: public: virtual void __thiscall rvSoundShaderEditLocal::LoadSampleData(class idSoundShader *,int)
void __thiscall rvSoundShaderEditLocal::LoadSampleData(
        rvSoundShaderEditLocal *this,
        idSoundShader *sound,
        int langIndex)
{
  idSoundShader::LoadSampleData(sound, langIndex);
}

// FUNC: public: virtual void __thiscall rvSoundShaderEditLocal::Purge(class idSoundShader *,bool)
void __thiscall rvSoundShaderEditLocal::Purge(rvSoundShaderEditLocal *this, idSoundShader *sound, bool freeBaseBlocks)
{
  idSoundShader::Purge(sound, freeBaseBlocks);
}

// FUNC: public: virtual void __thiscall rvSoundShaderEditLocal::ExpandSmallOggs(class idSoundShader *,bool)
void __thiscall rvSoundShaderEditLocal::ExpandSmallOggs(rvSoundShaderEditLocal *this, idSoundShader *sound, BOOL force)
{
  idSoundShader::ExpandSmallOggs(sound, force);
}

// FUNC: public: virtual char const * __thiscall rvSoundShaderEditLocal::GetShakeData(class idSoundShader *,int)
char *__thiscall rvSoundShaderEditLocal::GetShakeData(rvSoundShaderEditLocal *this, idSoundShader *sound, int index)
{
  if ( index < 0 || index >= sound->shakes.num )
    return (char *)&entityFilter;
  else
    return sound->shakes.list[index].data;
}

// FUNC: public: virtual void __thiscall idSoundShader::FreeData(void)
void __thiscall idSoundShader::FreeData(idSoundShader *this)
{
  idStr *list; // eax
  char *v3; // edi

  this->numEntries = 0;
  this->numLeadins = 0;
  list = this->shakes.list;
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
  this->shakes.list = 0;
  this->shakes.num = 0;
  this->shakes.size = 0;
}

// FUNC: public: virtual void __thiscall idSoundShader::List(void)const
void __thiscall idSoundShader::List(idSoundShader *this)
{
  int v1; // ebx
  int v3; // eax
  int v4; // ebp
  int v5; // esi
  const char *v6; // eax
  const char *v7; // eax
  int v8; // esi
  const char *v9; // eax
  rvCommonSample *v10; // esi
  bool v11; // al
  int v12; // ebp
  rvCommonSample_vtbl *v13; // edx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // ebx
  rvCommonSample *v19; // esi
  bool v20; // al
  int v21; // ebp
  rvCommonSample_vtbl *v22; // edx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // [esp-10h] [ebp-40h]
  int v28; // [esp-10h] [ebp-40h]
  int v29; // [esp-10h] [ebp-40h]
  int v30; // [esp-10h] [ebp-40h]
  char *data; // [esp-4h] [ebp-34h]
  char *v32; // [esp-4h] [ebp-34h]
  rvCommonSample **leadins; // [esp+10h] [ebp-20h]
  rvCommonSample **entries; // [esp+10h] [ebp-20h]

  v1 = 0;
  v3 = this->base->Index(this->base);
  v4 = *(_DWORD *)common.type;
  v5 = v3;
  v6 = this->base->GetName(this->base);
  (*(void (**)(netadrtype_t, const char *, ...))(v4 + 124))(common.type, "%4i: %s\n", v5, v6);
  v7 = this->GetDescription(this);
  if ( idStr::Icmp(v7, "<no description>") )
  {
    v8 = *(_DWORD *)common.type;
    v9 = this->GetDescription(this);
    (*(void (**)(netadrtype_t, const char *, ...))(v8 + 124))(common.type, "      description: %s\n", v9);
  }
  if ( this->numLeadins > 0 )
  {
    leadins = this->leadins;
    do
    {
      v10 = *leadins;
      if ( *leadins )
      {
        v11 = v10->IsOgg(*leadins);
        v12 = *(_DWORD *)common.type;
        v13 = v10->__vftable;
        data = v10->name.data;
        if ( v11 )
        {
          v14 = ((int (__thiscall *)(rvCommonSample *, char *))v13->GetNumChannels)(v10, data);
          v15 = ((int (__thiscall *)(rvCommonSample *, int))v10->GetMemoryUsed)(v10, v14);
          v27 = ((int (__thiscall *)(rvCommonSample *, int))v10->GetDurationMS)(v10, v15 / 1024);
          (*(void (__cdecl **)(netadrtype_t, const char *, int))(v12 + 124))(
            common.type,
            "      %5dms %4dKb %d %s.ogg (LEADIN)\n",
            v27);
        }
        else
        {
          v16 = ((int (__thiscall *)(rvCommonSample *, char *))v13->GetNumChannels)(v10, data);
          v17 = ((int (__thiscall *)(rvCommonSample *, int))v10->GetMemoryUsed)(v10, v16);
          v28 = ((int (__thiscall *)(rvCommonSample *, int))v10->GetDurationMS)(v10, v17 / 1024);
          (*(void (__cdecl **)(netadrtype_t, const char *, int))(v12 + 124))(
            common.type,
            "      %5dms %4dKb %d %s.wav (LEADIN)\n",
            v28);
        }
      }
      ++leadins;
      ++v1;
    }
    while ( v1 < this->numLeadins );
  }
  v18 = 0;
  if ( this->numEntries > 0 )
  {
    entries = this->entries;
    do
    {
      v19 = *entries;
      if ( *entries )
      {
        v20 = v19->IsOgg(*entries);
        v21 = *(_DWORD *)common.type;
        v22 = v19->__vftable;
        v32 = v19->name.data;
        if ( v20 )
        {
          v23 = ((int (__thiscall *)(rvCommonSample *, char *))v22->GetNumChannels)(v19, v32);
          v24 = ((int (__thiscall *)(rvCommonSample *, int))v19->GetMemoryUsed)(v19, v23);
          v29 = ((int (__thiscall *)(rvCommonSample *, int))v19->GetDurationMS)(v19, v24 / 1024);
          (*(void (__cdecl **)(netadrtype_t, const char *, int))(v21 + 124))(
            common.type,
            "      %5dms %4dKb %d %s.ogg\n",
            v29);
        }
        else
        {
          v25 = ((int (__thiscall *)(rvCommonSample *, char *))v22->GetNumChannels)(v19, v32);
          v26 = ((int (__thiscall *)(rvCommonSample *, int))v19->GetMemoryUsed)(v19, v25);
          v30 = ((int (__thiscall *)(rvCommonSample *, int))v19->GetDurationMS)(v19, v26 / 1024);
          (*(void (__cdecl **)(netadrtype_t, const char *, int))(v21 + 124))(
            common.type,
            "      %5dms %4dKb %d %s.wav\n",
            v30);
        }
      }
      ++entries;
      ++v18;
    }
    while ( v18 < this->numEntries );
  }
}

// FUNC: public: void __thiscall idSoundShader::SetShakeData(int,char const *)
void __thiscall idSoundShader::SetShakeData(idSoundShader *this, int index, char *ampData)
{
  idList<idStr> *p_shakes; // ebx

  p_shakes = &this->shakes;
  idList<idStr>::Resize(&this->shakes, index + 1);
  p_shakes->num = index + 1;
  idStr::operator=(&this->shakes.list[index], ampData);
}

// FUNC: public: virtual void __thiscall rvSoundShaderEditLocal::SetShakeData(class idSoundShader *,int,char const *)
void __thiscall rvSoundShaderEditLocal::SetShakeData(
        rvSoundShaderEditLocal *this,
        idSoundShader *sound,
        int index,
        char *ampData)
{
  idList<idStr>::Resize(&sound->shakes, index + 1);
  sound->shakes.num = index + 1;
  idStr::operator=(&sound->shakes.list[index], ampData);
}

// FUNC: private: bool __thiscall idSoundShader::ParseShader(class idLexer &)
char __thiscall idSoundShader::ParseShader(idSoundShader *this, idLexer *src)
{
  rvCommonSample **entries; // eax
  int v4; // ecx
  int integerValue; // edi
  signed int v6; // eax
  int v7; // edi
  double v8; // st7
  int v9; // edi
  const char *v10; // eax
  unsigned int v11; // eax
  char *v12; // ebp
  char *v13; // eax
  int v14; // edi
  int v15; // eax
  char *v16; // edx
  char *v17; // ecx
  char v18; // al
  idSoundSystem_vtbl *v19; // edx
  char *data; // ebp
  char *v21; // eax
  int v22; // edi
  int v23; // eax
  char *v24; // edx
  char *v25; // ecx
  char v26; // al
  idSoundSystem_vtbl *v27; // edx
  int numEntries; // eax
  int maxSamples; // [esp+8h] [ebp-A4h]
  idToken token; // [esp+Ch] [ebp-A0h] BYREF
  float volume; // [esp+5Ch] [ebp-50h]
  idStr v33; // [esp+60h] [ebp-4Ch] BYREF
  idStr v34; // [esp+80h] [ebp-2Ch] BYREF
  int v35; // [esp+A8h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  this->parms.minDistance = 0.0;
  this->parms.maxDistance = 0.0;
  this->parms.volume = 0.0;
  this->parms.attenuatedVolume = 0.0;
  this->parms.shakes = 0.0;
  this->parms.soundShaderFlags = 0;
  this->parms.soundClass = 0;
  this->parms.frequencyShift = 0.0;
  this->parms.wetLevel = 0.0;
  this->parms.dryLevel = 0.0;
  this->parms.minDistance = 40.0;
  this->parms.volume = 1.0;
  this->minFrequencyShift = 1.0;
  this->maxFrequencyShift = 1.0;
  this->parms.frequencyShift = 1.0;
  v35 = 0;
  this->parms.maxDistance = 400.0;
  this->altSound = 0;
  entries = this->entries;
  v4 = 32;
  do
  {
    *(entries - 33) = 0;
    *entries++ = 0;
    --v4;
  }
  while ( v4 );
  this->numEntries = 0;
  this->numLeadins = 0;
  integerValue = s_maxSoundsPerShader.internalVar->integerValue;
  maxSamples = integerValue;
  if ( com_makingBuild.internalVar->integerValue || integerValue <= 0 || integerValue > 32 )
  {
    integerValue = 32;
    maxSamples = 32;
  }
  if ( idLexer::ExpectAnyToken(src, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "minSamples") )
      {
        if ( idStr::Icmp(token.data, "frequencyshift") )
        {
          if ( idStr::Icmp(token.data, "description") )
          {
            if ( idStr::Icmp(token.data, "mindistance") )
            {
              if ( idStr::Icmp(token.data, "maxdistance") )
              {
                if ( idStr::Icmp(token.data, "shakes") )
                {
                  if ( idStr::Icmp(token.data, "shakeData") )
                  {
                    if ( idStr::Icmp(token.data, "volumeDb") )
                    {
                      if ( idStr::Icmp(token.data, "leadinVolume") )
                      {
                        if ( idStr::Icmp(token.data, "soundClass") )
                        {
                          if ( idStr::Icmp(token.data, "altSound") )
                          {
                            if ( idStr::Icmp(token.data, "no_dups") )
                            {
                              if ( idStr::Icmp(token.data, "no_flicker") )
                              {
                                if ( idStr::Icmp(token.data, "looping") )
                                {
                                  if ( idStr::Icmp(token.data, "no_occlusion") )
                                  {
                                    if ( idStr::Icmp(token.data, "private") )
                                    {
                                      if ( idStr::Icmp(token.data, "antiPrivate") )
                                      {
                                        if ( idStr::Icmp(token.data, "playonce") )
                                        {
                                          if ( idStr::Icmp(token.data, "global") )
                                          {
                                            if ( idStr::Icmp(token.data, "unclamped") )
                                            {
                                              if ( idStr::Icmp(token.data, "omnidirectional") )
                                              {
                                                if ( idStr::Icmp(token.data, "useDoppler") )
                                                {
                                                  if ( idStr::Icmp(token.data, "noRandomStart") )
                                                  {
                                                    if ( idStr::Icmp(token.data, "voForPlayer") )
                                                    {
                                                      if ( idStr::Icmp(token.data, "no_shakes") )
                                                      {
                                                        if ( idStr::Icmp(token.data, "frequentlyUsed") )
                                                        {
                                                          if ( idStr::Icmp(token.data, "onDemand") )
                                                          {
                                                            if ( idStr::Icmp(token.data, "leadin") )
                                                            {
                                                              if ( soundSystem->HasCache(soundSystem)
                                                                && this->numEntries < maxSamples )
                                                              {
                                                                data = token.data;
                                                                v34.len = 0;
                                                                v34.alloced = 20;
                                                                v34.data = v34.baseBuffer;
                                                                v34.baseBuffer[0] = 0;
                                                                if ( token.data )
                                                                {
                                                                  v21 = &token.data[strlen(token.data) + 1];
                                                                  v22 = v21 - (token.data + 1);
                                                                  v23 = v21 - token.data;
                                                                  if ( v23 > 20 )
                                                                    idStr::ReAllocate(&v34, v23, 1);
                                                                  v24 = v34.data;
                                                                  v25 = data;
                                                                  do
                                                                  {
                                                                    v26 = *v25;
                                                                    *v24++ = *v25++;
                                                                  }
                                                                  while ( v26 );
                                                                  v34.len = v22;
                                                                }
                                                                v27 = soundSystem->__vftable;
                                                                LOBYTE(v35) = 2;
                                                                this->entries[this->numEntries] = v27->FindSample(
                                                                                                    soundSystem,
                                                                                                    &v34);
                                                                LOBYTE(v35) = 0;
                                                                idStr::FreeData(&v34);
                                                                numEntries = this->numEntries;
                                                                if ( this->entries[numEntries] )
                                                                  this->numEntries = numEntries + 1;
                                                              }
                                                            }
                                                            else
                                                            {
                                                              if ( !idLexer::ReadToken(src, &token) )
                                                              {
                                                                idLexer::Warning(src, "Expected sound after leadin");
                                                                goto LABEL_106;
                                                              }
                                                              if ( soundSystem->HasCache(soundSystem)
                                                                && this->numLeadins < maxSamples )
                                                              {
                                                                v12 = token.data;
                                                                v33.len = 0;
                                                                v33.alloced = 20;
                                                                v33.data = v33.baseBuffer;
                                                                v33.baseBuffer[0] = 0;
                                                                if ( token.data )
                                                                {
                                                                  v13 = &token.data[strlen(token.data) + 1];
                                                                  v14 = v13 - (token.data + 1);
                                                                  v15 = v13 - token.data;
                                                                  if ( v15 > 20 )
                                                                    idStr::ReAllocate(&v33, v15, 1);
                                                                  v16 = v33.data;
                                                                  v17 = v12;
                                                                  do
                                                                  {
                                                                    v18 = *v17;
                                                                    *v16++ = *v17++;
                                                                  }
                                                                  while ( v18 );
                                                                  v33.len = v14;
                                                                }
                                                                v19 = soundSystem->__vftable;
                                                                LOBYTE(v35) = 1;
                                                                this->leadins[this->numLeadins] = v19->FindSample(
                                                                                                    soundSystem,
                                                                                                    &v33);
                                                                LOBYTE(v35) = 0;
                                                                idStr::FreeData(&v33);
                                                                ++this->numLeadins;
                                                              }
                                                            }
                                                          }
                                                        }
                                                        else
                                                        {
                                                          this->frequentlyUsed = 1;
                                                        }
                                                      }
                                                      else
                                                      {
                                                        this->noShakes = 1;
                                                      }
                                                    }
                                                    else
                                                    {
                                                      BYTE1(this->parms.soundShaderFlags) |= 0x10u;
                                                    }
                                                  }
                                                  else
                                                  {
                                                    BYTE1(this->parms.soundShaderFlags) |= 8u;
                                                  }
                                                }
                                                else
                                                {
                                                  BYTE1(this->parms.soundShaderFlags) |= 4u;
                                                }
                                              }
                                              else
                                              {
                                                this->parms.soundShaderFlags |= 0x10u;
                                              }
                                            }
                                            else
                                            {
                                              LOBYTE(this->parms.soundShaderFlags) |= 0x80u;
                                            }
                                          }
                                          else
                                          {
                                            this->parms.soundShaderFlags |= 8u;
                                          }
                                        }
                                        else
                                        {
                                          this->parms.soundShaderFlags |= 0x40u;
                                        }
                                      }
                                      else
                                      {
                                        this->parms.soundShaderFlags |= 2u;
                                      }
                                    }
                                    else
                                    {
                                      this->parms.soundShaderFlags |= 1u;
                                    }
                                  }
                                  else
                                  {
                                    this->parms.soundShaderFlags |= 4u;
                                  }
                                }
                                else
                                {
                                  this->parms.soundShaderFlags |= 0x20u;
                                }
                              }
                              else
                              {
                                BYTE1(this->parms.soundShaderFlags) |= 1u;
                              }
                            }
                            else
                            {
                              BYTE1(this->parms.soundShaderFlags) |= 2u;
                            }
                          }
                          else
                          {
                            if ( !idLexer::ExpectAnyToken(src, &token) )
                              goto LABEL_106;
                            this->altSound = declManager->FindSound(declManager, token.data, 1);
                          }
                        }
                        else
                        {
                          v11 = idLexer::ParseInt(src);
                          this->parms.soundClass = v11;
                          if ( v11 >= 4 )
                          {
                            idLexer::Warning(src, "SoundClass out of range");
                            goto LABEL_106;
                          }
                        }
                      }
                      else
                      {
                        this->leadinVolume = idLexer::ParseFloat(src, 0);
                      }
                    }
                    else
                    {
                      v8 = idLexer::ParseFloat(src, 0);
                      volume = v8;
                      if ( v8 > 10.0 )
                      {
                        v9 = *(_DWORD *)common.type;
                        v10 = this->base->GetName(this->base);
                        (*(void (**)(netadrtype_t, const char *, ...))(v9 + 136))(
                          common.type,
                          "Clamping volume of '%s' to +10dB (3 times louder)",
                          v10);
                        volume = 10.0;
                      }
                      this->parms.volume = idMath::dBToScale(volume);
                    }
                  }
                  else
                  {
                    if ( !idLexer::ExpectAnyToken(src, &token) )
                      goto LABEL_106;
                    v7 = atol(token.data);
                    if ( !idLexer::ExpectAnyToken(src, &token) )
                      goto LABEL_106;
                    idSoundShader::SetShakeData(this, v7, token.data);
                  }
                }
                else
                {
                  idLexer::ExpectAnyToken(src, &token);
                  if ( token.type == 3 )
                  {
                    if ( (token.subtype & 0x10000) == 0 )
                      idToken::NumberValue(&token);
                    this->parms.shakes = token.floatvalue;
                  }
                  else
                  {
                    idLexer::UnreadToken(src, &token);
                    this->parms.shakes = 1.0;
                  }
                }
              }
              else
              {
                this->parms.maxDistance = idLexer::ParseFloat(src, 0);
              }
            }
            else
            {
              this->parms.minDistance = idLexer::ParseFloat(src, 0);
            }
          }
          else
          {
            idLexer::ReadTokenOnLine(src, &token);
            idStr::operator=(&this->desc, token.data);
          }
        }
        else
        {
          this->minFrequencyShift = idLexer::ParseFloat(src, 0);
          if ( !idLexer::ExpectTokenString(src, ",") )
          {
            idLexer::FreeSource(src);
            goto LABEL_106;
          }
          this->maxFrequencyShift = idLexer::ParseFloat(src, 0);
        }
      }
      else
      {
        v6 = idLexer::ParseInt(src);
        if ( integerValue >= v6 )
        {
          if ( integerValue > 32 )
            maxSamples = 32;
        }
        else
        {
          maxSamples = v6;
        }
      }
      if ( !idLexer::ExpectAnyToken(src, &token) )
        goto LABEL_106;
      integerValue = maxSamples;
    }
    if ( !soundSystem->GetInsideLevelLoad(soundSystem) )
      soundSystem->ValidateSoundShader(soundSystem, this);
    v35 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_106:
    v35 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}

// FUNC: public: virtual bool __thiscall idSoundShader::Parse(char const *,int,bool)
char __thiscall idSoundShader::Parse(idSoundShader *this, const char *text, int textLength, bool noCaching)
{
  idDeclBase *base; // ecx
  idDeclBase_vtbl *v6; // eax
  const char *v7; // edi
  int v8; // eax
  idLexer src; // [esp+8h] [ebp-D4h] BYREF
  int v11; // [esp+D8h] [ebp-4h]

  idLexer::idLexer(&src);
  base = this->base;
  v6 = base->__vftable;
  v11 = 0;
  v7 = v6->GetFileName(base);
  v8 = this->base->GetLineNum(this->base);
  idLexer::LoadMemory(&src, text, textLength, v7, v8);
  src.flags = 6300;
  idLexer::SkipUntilString(&src, "{");
  this->errorDuringParse = 0;
  if ( !idSoundShader::ParseShader(this, &src) || this->errorDuringParse )
  {
    this->base->MakeDefault(this->base);
    v11 = -1;
    idLexer::~idLexer(&src);
    return 0;
  }
  else
  {
    v11 = -1;
    idLexer::~idLexer(&src);
    return 1;
  }
}
