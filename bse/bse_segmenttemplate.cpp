
// FUNC: public: int __thiscall idImage::GetTexelCount(void)const
int __thiscall idImage::GetTexelCount(idImage *this)
{
  switch ( this->type )
  {
    case TT_2D:
      return this->uploadWidth * this->uploadHeight;
    case TT_3D:
      return this->uploadWidth * this->uploadHeight * this->uploadDepth;
    case TT_CUBIC:
      return 6 * this->uploadWidth * this->uploadHeight;
  }
  return 0;
}

// FUNC: public: void __thiscall rvSegmentTemplate::CreateParticleTemplate(class rvDeclEffect *,class idLexer *,int)
void __thiscall rvSegmentTemplate::CreateParticleTemplate(
        rvSegmentTemplate *this,
        rvDeclEffect *effect,
        idLexer *lexer,
        int particleType)
{
  rvParticleTemplate *p_mParticleTemplate; // esi

  p_mParticleTemplate = &this->mParticleTemplate;
  rvParticleTemplate::Init(&this->mParticleTemplate);
  this->mParticleTemplate.mType = particleType;
  rvParticleTemplate::SetParameterCounts(p_mParticleTemplate);
  rvParticleTemplate::Parse(p_mParticleTemplate, effect, lexer);
}

// FUNC: public: void __thiscall rvSegmentTemplate::Init(class rvDeclEffect *)
void __thiscall rvSegmentTemplate::Init(rvSegmentTemplate *this, rvDeclEffect *decl)
{
  this->mDeclEffect = decl;
  this->mFlags = 1;
  this->mSegType = 0;
  this->mLocalStartTime.y = 0.0;
  this->mLocalStartTime.x = 0.0;
  this->mLocalDuration.y = 0.0;
  this->mLocalDuration.x = 0.0;
  this->mAttenuation.y = 0.0;
  this->mAttenuation.x = 0.0;
  this->mParticleCap = 0.0;
  this->mDetail = 0.0;
  this->mScale = 1.0;
  this->mCount.x = 1.0;
  this->mCount.y = 1.0;
  this->mDensity.y = 0.0;
  this->mDensity.x = 0.0;
  this->mTrailSegmentIndex = -1;
  this->mNumEffects = 0;
  this->mEffects[0] = 0;
  this->mEffects[1] = 0;
  this->mEffects[2] = 0;
  this->mEffects[3] = 0;
  this->mSoundShader = 0;
  this->mSoundVolume.y = 0.0;
  this->mSoundVolume.x = 0.0;
  this->mFreqShift.x = 1.0;
  this->mFreqShift.y = 1.0;
  rvParticleTemplate::Init(&this->mParticleTemplate);
  this->mBSEEffect = 0;
}

// FUNC: public: int __thiscall rvSegmentTemplate::GetTexelCount(void)
int __thiscall rvSegmentTemplate::GetTexelCount(rvSegmentTemplate *this)
{
  idMaterial *mMaterial; // ecx

  mMaterial = (idMaterial *)this->mParticleTemplate.mMaterial;
  if ( mMaterial )
    return idMaterial::GetTexelCount(mMaterial);
  else
    return 0;
}

// FUNC: public: bool __thiscall rvSegmentTemplate::GetSmoker(void)
BOOL __thiscall rvSegmentTemplate::GetSmoker(rvSegmentTemplate *this)
{
  return this->mParticleTemplate.mTrailType == 3;
}

// FUNC: public: bool __thiscall rvSegmentTemplate::Compare(class rvSegmentTemplate const &)const
char __thiscall rvSegmentTemplate::Compare(rvSegmentTemplate *this, const rvSegmentTemplate *a)
{
  int mSegType; // eax
  int mNumEffects; // edx
  int v6; // ecx
  const rvDeclEffect **mEffects; // eax

  if ( idStr::Cmp(this->mSegmentName.data, a->mSegmentName.data) )
    return 0;
  if ( ((this->mFlags ^ a->mFlags) & 0xFFFFFFFE) != 0 )
    return 0;
  mSegType = this->mSegType;
  if ( mSegType != a->mSegType
    || mSegType != 4
    && (this->mLocalStartTime.x != a->mLocalStartTime.x
     || this->mLocalStartTime.y != a->mLocalStartTime.y
     || this->mLocalDuration.x != a->mLocalDuration.x
     || this->mLocalDuration.y != a->mLocalDuration.y) )
  {
    return 0;
  }
  if ( this->mScale != a->mScale
    || this->mDetail != a->mDetail
    || this->mAttenuation.x != a->mAttenuation.x
    || this->mAttenuation.y != a->mAttenuation.y )
  {
    return 0;
  }
  if ( this->mDensity.y == 0.0 )
  {
    if ( this->mCount.x != a->mCount.x || this->mCount.y != a->mCount.y )
      return 0;
  }
  else if ( this->mDensity.x != a->mDensity.x
         || this->mDensity.y != a->mDensity.y
         || this->mParticleCap != a->mParticleCap )
  {
    return 0;
  }
  if ( this->mTrailSegmentIndex != a->mTrailSegmentIndex )
    return 0;
  mNumEffects = this->mNumEffects;
  if ( mNumEffects != a->mNumEffects )
    return 0;
  v6 = 0;
  if ( mNumEffects > 0 )
  {
    mEffects = this->mEffects;
    while ( *mEffects == *(const rvDeclEffect **)((char *)mEffects + (char *)a - (char *)this) )
    {
      ++v6;
      ++mEffects;
      if ( v6 >= mNumEffects )
        goto LABEL_26;
    }
    return 0;
  }
LABEL_26:
  if ( this->mSoundShader != a->mSoundShader
    || this->mSoundVolume.x != a->mSoundVolume.x
    || this->mSoundVolume.y != a->mSoundVolume.y
    || this->mFreqShift.x != a->mFreqShift.x
    || this->mFreqShift.y != a->mFreqShift.y
    || this->mDetail != a->mDetail )
  {
    return 0;
  }
  return rvParticleTemplate::Compare(&this->mParticleTemplate, &a->mParticleTemplate);
}

// FUNC: public: void __thiscall rvSegmentTemplate::SetMaxDuration(class rvDeclEffect *)
void __thiscall rvSegmentTemplate::SetMaxDuration(rvSegmentTemplate *this, rvDeclEffect *effect)
{
  float duration; // [esp+0h] [ebp-Ch]
  float durationa; // [esp+0h] [ebp-Ch]

  if ( (this->mFlags & 0x10) == 0 )
  {
    duration = this->mLocalStartTime.x + this->mLocalDuration.x;
    rvDeclEffect::SetMaxDuration(effect, duration);
    if ( this->mParticleTemplate.mType )
    {
      durationa = this->mParticleTemplate.mDuration.y + this->mLocalStartTime.x + this->mLocalDuration.x;
      rvDeclEffect::SetMaxDuration(effect, durationa);
    }
  }
}

// FUNC: public: bool __thiscall rvSegmentTemplate::GetSoundLooping(void)
bool __thiscall rvSegmentTemplate::GetSoundLooping(rvSegmentTemplate *this)
{
  const idSoundShader *mSoundShader; // eax
  int v2; // eax

  mSoundShader = this->mSoundShader;
  if ( mSoundShader )
    return ((unsigned int)mSoundShader->parms.soundShaderFlags >> 5) & 1;
  else
    LOBYTE(v2) = 0;
  return v2;
}

// FUNC: public: bool __thiscall rvSegmentTemplate::Finish(class rvDeclEffect *)
char __thiscall rvSegmentTemplate::Finish(rvSegmentTemplate *this, rvDeclEffect *effect)
{
  float y; // eax
  float v4; // ecx
  float v5; // edx
  float v6; // eax
  float v7; // ecx
  int mType; // ecx
  int v10; // eax
  int mFlags; // eax
  int v12; // eax

  if ( this->mLocalStartTime.x >= (double)this->mLocalStartTime.y )
  {
    y = this->mLocalStartTime.y;
    this->mLocalStartTime.y = this->mLocalStartTime.x;
    this->mLocalStartTime.x = y;
  }
  if ( this->mLocalDuration.x >= (double)this->mLocalDuration.y )
  {
    v4 = this->mLocalDuration.y;
    this->mLocalDuration.y = this->mLocalDuration.x;
    this->mLocalDuration.x = v4;
  }
  if ( this->mCount.x >= (double)this->mCount.y )
  {
    v5 = this->mCount.y;
    this->mCount.y = this->mCount.x;
    this->mCount.x = v5;
  }
  if ( this->mDensity.x >= (double)this->mDensity.y )
  {
    v6 = this->mDensity.y;
    this->mDensity.y = this->mDensity.x;
    this->mDensity.x = v6;
  }
  if ( this->mAttenuation.x >= (double)this->mAttenuation.y )
  {
    v7 = this->mAttenuation.y;
    this->mAttenuation.y = this->mAttenuation.x;
    this->mAttenuation.x = v7;
  }
  if ( this->mParticleTemplate.mType )
  {
    rvParticleTemplate::Finish(&this->mParticleTemplate);
    BYTE2(this->mParticleTemplate.mFlags) &= ~8u;
  }
  switch ( this->mSegType )
  {
    case 2:
      this->mFlags |= 4u;
      if ( !this->mParticleTemplate.mType )
        return 0;
      if ( (this->mFlags & 0x20) == 0 )
        goto LABEL_25;
      return 0;
    case 3:
      this->mFlags |= 4u;
      if ( this->mParticleTemplate.mType )
        goto LABEL_25;
      return 0;
    case 4:
      this->mFlags |= 4u;
      this->mLocalStartTime.y = 0.0;
      this->mLocalStartTime.x = 0.0;
      this->mLocalDuration.y = 0.0;
      this->mLocalDuration.x = 0.0;
      if ( !this->mParticleTemplate.mType )
        return 0;
      BYTE2(this->mParticleTemplate.mFlags) |= 8u;
LABEL_25:
      mType = this->mParticleTemplate.mType;
      if ( mType == 9 )
      {
        v10 = this->mFlags & 0xFFFFFFFB;
        BYTE1(v10) |= 1u;
        this->mFlags = v10;
      }
      mFlags = this->mFlags;
      if ( (mFlags & 0x20) != 0
        || this->mParticleTemplate.mTrailType == 3
        || (this->mParticleTemplate.mFlags & 0x200) != 0
        || this->mParticleTemplate.mNumTimeoutEffects )
      {
        BYTE1(mFlags) |= 2u;
        this->mFlags = mFlags;
      }
      if ( mType == 7 || mType == 6 )
        BYTE1(this->mFlags) |= 2u;
      return 1;
    case 5:
      this->mFlags |= 0x10u;
      goto LABEL_25;
    case 6:
      v12 = this->mFlags & 0xFFFFFFFB;
      BYTE1(v12) |= 1u;
      this->mFlags = v12;
      goto LABEL_25;
    case 9:
    case 0xA:
    case 0xB:
      if ( this->mAttenuation.y > 0.0 )
        this->mFlags |= 0x40u;
      goto LABEL_24;
    default:
LABEL_24:
      this->mFlags &= ~4u;
      goto LABEL_25;
  }
}

// FUNC: public: void __thiscall rvSegmentTemplate::EvaluateTrailSegment(class rvDeclEffect *)
void __thiscall rvSegmentTemplate::EvaluateTrailSegment(rvSegmentTemplate *this, rvDeclEffect *et)
{
  if ( idStr::Cmp(this->mParticleTemplate.mTrailTypeName.data, &entityFilter) )
  {
    if ( this->mParticleTemplate.mTrailType )
      this->mTrailSegmentIndex = rvDeclEffect::GetTrailSegmentIndex(et, &this->mParticleTemplate.mTrailTypeName);
  }
}

// FUNC: public: bool __thiscall rvSegmentTemplate::DetailCull(void)const
bool __thiscall rvSegmentTemplate::DetailCull(rvSegmentTemplate *this)
{
  return this->mDetail != 0.0 && bse_scale.internalVar->floatValue < (double)this->mDetail;
}

// FUNC: public: void __thiscall rvSegmentTemplate::SetMinDuration(class rvDeclEffect *)
void __thiscall rvSegmentTemplate::SetMinDuration(rvSegmentTemplate *this, rvDeclEffect *effect)
{
  const idSoundShader *mSoundShader; // eax
  float duration; // [esp+0h] [ebp-4h]

  if ( (this->mFlags & 0x10) == 0 )
  {
    mSoundShader = this->mSoundShader;
    if ( !mSoundShader || (mSoundShader->parms.soundShaderFlags & 0x20) == 0 )
    {
      duration = this->mLocalDuration.x + this->mLocalStartTime.x;
      rvDeclEffect::SetMinDuration(effect, duration);
    }
  }
}

// FUNC: public: bool __thiscall rvSegmentTemplate::Parse(class rvDeclEffect *,int,class idLexer *)
char __thiscall rvSegmentTemplate::Parse(
        rvSegmentTemplate *this,
        rvDeclEffect *effect,
        int segmentType,
        idLexer *lexer)
{
  rvDeclEffect *v6; // esi
  char *v7; // eax
  int len; // esi
  idSoundShader *v9; // eax
  double TimeLength; // st7
  idToken token; // [esp+8h] [ebp-5Ch] BYREF
  int v12; // [esp+60h] [ebp-4h]
  int segmentTypea; // [esp+6Ch] [ebp+8h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v12 = 0;
  this->mSegType = segmentType;
  if ( !idLexer::ReadToken(lexer, &token) )
    goto LABEL_2;
  if ( idStr::Icmp(token.data, "{") )
  {
    len = token.len;
    segmentTypea = token.len;
    if ( token.len + 1 > this->mSegmentName.alloced )
      idStr::ReAllocate(&this->mSegmentName, token.len + 1, 0);
    qmemcpy(this->mSegmentName.data, token.data, len);
    v6 = effect;
    this->mSegmentName.data[segmentTypea] = 0;
    this->mSegmentName.len = segmentTypea;
  }
  else
  {
    v6 = effect;
    v7 = va("unnamed%d", effect->mSegmentTemplates.num);
    idStr::operator=(&this->mSegmentName, v7);
    idLexer::UnreadToken(lexer, &token);
  }
  if ( idLexer::ExpectTokenString(lexer, "{") && idLexer::ReadToken(lexer, &token) )
  {
    while ( idStr::Cmp(token.data, "}") )
    {
      if ( idStr::Icmp(token.data, "count") && idStr::Icmp(token.data, "rate") )
      {
        if ( idStr::Icmp(token.data, "density") )
        {
          if ( idStr::Icmp(token.data, "particleCap") )
          {
            if ( idStr::Icmp(token.data, "start") )
            {
              if ( idStr::Icmp(token.data, "duration") )
              {
                if ( idStr::Icmp(token.data, "detail") )
                {
                  if ( idStr::Icmp(token.data, "soundShader") )
                  {
                    if ( idStr::Icmp(token.data, "volume") )
                    {
                      if ( idStr::Icmp(token.data, "freqShift") )
                      {
                        if ( idStr::Icmp(token.data, "effect") )
                        {
                          if ( idStr::Icmp(token.data, "channel") )
                          {
                            if ( idStr::Icmp(token.data, "scale") )
                            {
                              if ( idStr::Icmp(token.data, "attenuateEmitter") )
                              {
                                if ( idStr::Icmp(token.data, "inverseAttenuateEmitter") )
                                {
                                  if ( idStr::Icmp(token.data, "attenuation") )
                                  {
                                    if ( idStr::Icmp(token.data, "locked") )
                                    {
                                      if ( idStr::Icmp(token.data, "constant") )
                                      {
                                        if ( idStr::Icmp(token.data, "sprite") )
                                        {
                                          if ( idStr::Icmp(token.data, "line") )
                                          {
                                            if ( idStr::Icmp(token.data, "oriented") )
                                            {
                                              if ( idStr::Icmp(token.data, "decal") )
                                              {
                                                if ( idStr::Icmp(token.data, "model") )
                                                {
                                                  if ( idStr::Icmp(token.data, "light") )
                                                  {
                                                    if ( idStr::Icmp(token.data, "electricity") )
                                                    {
                                                      if ( idStr::Icmp(token.data, "linked") )
                                                      {
                                                        if ( idStr::Icmp(token.data, "debris") )
                                                          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
                                                            common.type,
                                                            "^4BSE:^1 Invalid segment parameter '%s' (file: %s, line: %d)",
                                                            token.data,
                                                            lexer->filename.data,
                                                            lexer->line);
                                                        else
                                                          rvSegmentTemplate::CreateParticleTemplate(this, v6, lexer, 9);
                                                      }
                                                      else
                                                      {
                                                        rvSegmentTemplate::CreateParticleTemplate(this, v6, lexer, 8);
                                                      }
                                                    }
                                                    else
                                                    {
                                                      rvSegmentTemplate::CreateParticleTemplate(this, v6, lexer, 7);
                                                    }
                                                  }
                                                  else
                                                  {
                                                    rvSegmentTemplate::CreateParticleTemplate(this, v6, lexer, 6);
                                                  }
                                                }
                                                else
                                                {
                                                  rvSegmentTemplate::CreateParticleTemplate(this, v6, lexer, 5);
                                                }
                                              }
                                              else
                                              {
                                                rvSegmentTemplate::CreateParticleTemplate(this, v6, lexer, 4);
                                              }
                                            }
                                            else
                                            {
                                              rvSegmentTemplate::CreateParticleTemplate(this, v6, lexer, 3);
                                            }
                                          }
                                          else
                                          {
                                            rvSegmentTemplate::CreateParticleTemplate(this, v6, lexer, 2);
                                          }
                                        }
                                        else
                                        {
                                          rvSegmentTemplate::CreateParticleTemplate(this, v6, lexer, 1);
                                        }
                                      }
                                      else
                                      {
                                        this->mFlags |= 0x20u;
                                      }
                                    }
                                    else
                                    {
                                      this->mFlags |= 2u;
                                    }
                                  }
                                  else
                                  {
                                    this->mAttenuation.x = idLexer::ParseFloat(lexer, 0);
                                    idLexer::ExpectTokenString(lexer, ",");
                                    this->mAttenuation.y = idLexer::ParseFloat(lexer, 0);
                                  }
                                }
                                else
                                {
                                  LOBYTE(this->mFlags) |= 0xC0u;
                                }
                              }
                              else
                              {
                                this->mFlags |= 0x40u;
                              }
                            }
                            else
                            {
                              this->mScale = idLexer::ParseFloat(lexer, 0);
                            }
                          }
                          else
                          {
                            idLexer::ReadToken(lexer, &token);
                          }
                        }
                        else
                        {
                          idLexer::ReadToken(lexer, &token);
                          if ( this->mNumEffects >= 4 )
                            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
                              common.type,
                              "Unable to add effect '%s' - too many effects",
                              token.data);
                          else
                            this->mEffects[this->mNumEffects++] = declManager->FindEffect(declManager, token.data, 1);
                        }
                      }
                      else
                      {
                        this->mFreqShift.x = idLexer::ParseFloat(lexer, 0);
                        idLexer::ExpectTokenString(lexer, ",");
                        this->mFreqShift.y = idLexer::ParseFloat(lexer, 0);
                      }
                    }
                    else
                    {
                      this->mSoundVolume.x = idLexer::ParseFloat(lexer, 0);
                      idLexer::ExpectTokenString(lexer, ",");
                      this->mSoundVolume.y = idLexer::ParseFloat(lexer, 0);
                    }
                  }
                  else
                  {
                    idLexer::ReadToken(lexer, &token);
                    v9 = (idSoundShader *)declManager->FindSound(declManager, token.data, 1);
                    this->mSoundShader = v9;
                    TimeLength = idSoundShader::GetTimeLength(v9);
                    this->mLocalDuration.x = TimeLength;
                    this->mLocalDuration.y = TimeLength;
                  }
                }
                else
                {
                  this->mDetail = idLexer::ParseFloat(lexer, 0);
                }
              }
              else
              {
                this->mLocalDuration.x = idLexer::ParseFloat(lexer, 0);
                idLexer::ExpectTokenString(lexer, ",");
                this->mLocalDuration.y = idLexer::ParseFloat(lexer, 0);
              }
            }
            else
            {
              this->mLocalStartTime.x = idLexer::ParseFloat(lexer, 0);
              idLexer::ExpectTokenString(lexer, ",");
              this->mLocalStartTime.y = idLexer::ParseFloat(lexer, 0);
            }
          }
          else
          {
            this->mParticleCap = idLexer::ParseFloat(lexer, 0);
          }
        }
        else
        {
          this->mDensity.x = idLexer::ParseFloat(lexer, 0);
          idLexer::ExpectTokenString(lexer, ",");
          this->mDensity.y = idLexer::ParseFloat(lexer, 0);
        }
      }
      else
      {
        this->mCount.x = idLexer::ParseFloat(lexer, 0);
        idLexer::ExpectTokenString(lexer, ",");
        this->mCount.y = idLexer::ParseFloat(lexer, 0);
      }
      if ( !idLexer::ReadToken(lexer, &token) )
        goto LABEL_2;
    }
    v12 = -1;
    idStr::FreeData(&token);
    return 1;
  }
  else
  {
LABEL_2:
    v12 = -1;
    idStr::FreeData(&token);
    return 0;
  }
}
