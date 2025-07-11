
// FUNC: public: void __thiscall rvEnvParms1::Evaluate(float,float *)
void __thiscall rvEnvParms1::Evaluate(rvEnvParms1 *this, float time, float *dest)
{
  const idDeclTable *mTable; // ecx
  float v5; // [esp+0h] [ebp-8h]

  mTable = this->mTable;
  if ( mTable )
  {
    v5 = time * this->mRate + this->mEnvOffset;
    *dest = (this->mEnd - this->mStart) * ((double (__stdcall *)(_DWORD))mTable->TableLookup)(LODWORD(v5))
          + this->mStart;
  }
  else
  {
    *dest = this->mStart;
  }
}

// FUNC: public: void __thiscall rvEnvParms::SetDefaultType(void)
void __thiscall rvEnvParms::SetDefaultType(rvEnvParms *this)
{
  if ( !this->mTable )
  {
    this->mTable = (const idDeclTable *)declManager->FindType(declManager, 0, "linear", 1, 0);
    this->mIsCount = 1;
  }
}

// FUNC: public: void __thiscall rvEnvParms2::Evaluate(float,float *)
void __thiscall rvEnvParms2::Evaluate(rvEnvParms2 *this, float time, float *dest)
{
  const idDeclTable *mTable; // ecx
  double v5; // st7
  double v6; // st7
  float v7; // [esp+4h] [ebp-Ch]
  float v8; // [esp+4h] [ebp-Ch]
  float v9; // [esp+8h] [ebp-8h]

  mTable = this->mTable;
  if ( mTable )
  {
    v5 = time * this->mRate.x + this->mEnvOffset.x;
    if ( this->mFixedRateAndOffset )
    {
      v9 = v5;
      v6 = ((double (__stdcall *)(_DWORD))mTable->TableLookup)(LODWORD(v9));
      *dest = (this->mEnd.x - this->mStart.x) * v6 + this->mStart.x;
      dest[1] = (this->mEnd.y - this->mStart.y) * v6 + this->mStart.y;
    }
    else
    {
      v7 = v5;
      *dest = (this->mEnd.x - this->mStart.x) * ((double (__stdcall *)(_DWORD))mTable->TableLookup)(LODWORD(v7))
            + this->mStart.x;
      v8 = time * this->mRate.y + this->mEnvOffset.y;
      dest[1] = (this->mEnd.y - this->mStart.y) * ((double (__stdcall *)(_DWORD))this->mTable->TableLookup)(LODWORD(v8))
              + this->mStart.y;
    }
  }
  else
  {
    *dest = this->mStart.x;
    dest[1] = this->mStart.y;
  }
}

// FUNC: public: void __thiscall rvEnvParms3::Evaluate(float,float *)
void __thiscall rvEnvParms3::Evaluate(rvEnvParms3 *this, float time, float *dest)
{
  const idDeclTable *mTable; // ecx
  double v5; // st7
  double v6; // st7
  float v7; // [esp+8h] [ebp-Ch]
  float v8; // [esp+8h] [ebp-Ch]
  float v9; // [esp+8h] [ebp-Ch]
  float v10; // [esp+Ch] [ebp-8h]

  mTable = this->mTable;
  if ( mTable )
  {
    v5 = time * this->mRate.x + this->mEnvOffset.x;
    if ( this->mFixedRateAndOffset )
    {
      v10 = v5;
      v6 = ((double (__stdcall *)(_DWORD))mTable->TableLookup)(LODWORD(v10));
      *dest = (this->mEnd.x - this->mStart.x) * v6 + this->mStart.x;
      dest[1] = (this->mEnd.y - this->mStart.y) * v6 + this->mStart.y;
      dest[2] = (this->mEnd.z - this->mStart.z) * v6 + this->mStart.z;
    }
    else
    {
      v7 = v5;
      *dest = (this->mEnd.x - this->mStart.x) * ((double (__stdcall *)(_DWORD))mTable->TableLookup)(LODWORD(v7))
            + this->mStart.x;
      v8 = time * this->mRate.y + this->mEnvOffset.y;
      dest[1] = (this->mEnd.y - this->mStart.y) * ((double (__stdcall *)(_DWORD))this->mTable->TableLookup)(LODWORD(v8))
              + this->mStart.y;
      v9 = time * this->mRate.z + this->mEnvOffset.z;
      dest[2] = (this->mEnd.z - this->mStart.z) * ((double (__stdcall *)(_DWORD))this->mTable->TableLookup)(LODWORD(v9))
              + this->mStart.z;
    }
  }
  else
  {
    *dest = this->mStart.x;
    dest[1] = this->mStart.y;
    dest[2] = this->mStart.z;
  }
}

// FUNC: public: void __thiscall rvEnvParms::Init(void)
void __thiscall rvEnvParms::Init(rvEnvParms *this)
{
  this->mTable = 0;
  this->mIsCount = 1;
  this->mEnvOffset.z = 0.0;
  this->mEnvOffset.y = 0.0;
  this->mEnvOffset.x = 0.0;
  this->mRate.x = 1.0;
  this->mRate.y = 1.0;
  this->mRate.z = 1.0;
}

// FUNC: public: void __thiscall rvEnvParms1::Init(class rvEnvParms const &,float)
void __thiscall rvEnvParms1::Init(rvEnvParms1 *this, const rvEnvParms *copy, float duration)
{
  this->mTable = copy->mTable;
  this->mEnvOffset = copy->mEnvOffset.x;
  if ( copy->mIsCount )
    this->mRate = copy->mRate.x / duration;
  else
    this->mRate = copy->mRate.x;
}

// FUNC: public: void __thiscall rvEnvParms2::Init(class rvEnvParms const &,float)
void __thiscall rvEnvParms2::Init(rvEnvParms2 *this, const rvEnvParms *copy, float duration)
{
  double v3; // st7

  this->mTable = copy->mTable;
  this->mEnvOffset.x = copy->mEnvOffset.x;
  this->mEnvOffset.y = copy->mEnvOffset.y;
  if ( copy->mIsCount )
  {
    v3 = 1.0 / duration;
    this->mRate.x = v3 * copy->mRate.x;
    this->mRate.y = v3 * copy->mRate.y;
  }
  else
  {
    this->mRate.x = copy->mRate.x;
    this->mRate.y = copy->mRate.y;
  }
  this->mFixedRateAndOffset = this->mRate.x == this->mRate.y && this->mEnvOffset.x == this->mEnvOffset.y;
}

// FUNC: public: void __thiscall rvEnvParms3::Init(class rvEnvParms const &,float)
void __thiscall rvEnvParms3::Init(rvEnvParms3 *this, const rvEnvParms *copy, float duration)
{
  double v3; // st7

  this->mTable = copy->mTable;
  this->mEnvOffset = copy->mEnvOffset;
  if ( copy->mIsCount )
  {
    v3 = 1.0 / duration;
    this->mRate.x = v3 * copy->mRate.x;
    this->mRate.y = v3 * copy->mRate.y;
    this->mRate.z = v3 * copy->mRate.z;
  }
  else
  {
    this->mRate = copy->mRate;
  }
  this->mFixedRateAndOffset = this->mRate.x == this->mRate.y
                           && this->mRate.x == this->mRate.z
                           && this->mEnvOffset.x == this->mEnvOffset.y
                           && this->mEnvOffset.x == this->mEnvOffset.z;
}

// FUNC: public: void __thiscall rvEnvParms3::Rotate(class rvAngles const &)
void __thiscall rvEnvParms3::Rotate(rvEnvParms3 *this, const rvAngles *angles)
{
  this->mStart.x = angles->pitch + this->mStart.x;
  this->mStart.y = angles->yaw + this->mStart.y;
  this->mStart.z = angles->roll + this->mStart.z;
  this->mEnd.x = angles->pitch + this->mEnd.x;
  this->mEnd.y = angles->yaw + this->mEnd.y;
  this->mEnd.z = angles->roll + this->mEnd.z;
}

// FUNC: public: bool __thiscall rvEnvParms::GetMinMax(float &,float &)
char __thiscall rvEnvParms::GetMinMax(rvEnvParms *this, float *min, float *max)
{
  if ( this->mTable )
  {
    *min = this->mTable->minValue;
    *max = this->mTable->maxValue;
    return 1;
  }
  else
  {
    *min = 0.0;
    *max = 0.0;
    return 0;
  }
}

// FUNC: private: bool __thiscall rvEnvParms::Compare(class rvEnvParms const &)const
bool __thiscall rvEnvParms::Compare(rvEnvParms *this, const rvEnvParms *comp)
{
  return this->mTable == comp->mTable && this->mIsCount == comp->mIsCount;
}

// FUNC: public: void __thiscall rvEnvParms::CalcRate(float *,float,int)
void __thiscall rvEnvParms::CalcRate(rvEnvParms *this, float *rate, float duration, int count)
{
  float *v4; // edx
  int v5; // edi
  float *v6; // edx
  unsigned int v7; // esi
  float *p_y; // eax
  float *v9; // eax

  v4 = rate;
  v5 = 0;
  if ( count >= 4 )
  {
    v6 = rate + 2;
    v7 = ((unsigned int)(count - 4) >> 2) + 1;
    p_y = &this->mRate.y;
    v5 = 4 * v7;
    do
    {
      if ( this->mIsCount )
        *(v6 - 2) = *(p_y - 1) / duration;
      else
        *(v6 - 2) = *(p_y - 1);
      if ( this->mIsCount )
        *(v6 - 1) = *p_y / duration;
      else
        *(v6 - 1) = *p_y;
      if ( this->mIsCount )
        *v6 = p_y[1] / duration;
      else
        *v6 = p_y[1];
      if ( this->mIsCount )
        v6[1] = p_y[2] / duration;
      else
        v6[1] = p_y[2];
      p_y += 4;
      v6 += 4;
      --v7;
    }
    while ( v7 );
    v4 = rate;
  }
  if ( v5 < count )
  {
    v9 = &this->mRate.x + v5;
    do
    {
      if ( this->mIsCount )
        v4[v5] = *v9 / duration;
      else
        v4[v5] = *v9;
      ++v5;
      ++v9;
    }
    while ( v5 < count );
  }
}

// FUNC: public: void __thiscall rvEnvParms::Evaluate3(float,float const *,float const *,float const *,float *)
void __thiscall rvEnvParms::Evaluate3(
        rvEnvParms *this,
        float time,
        const float *start,
        const float *rate,
        const float *end,
        float *dest)
{
  const idDeclTable *mTable; // ecx
  float v8; // [esp+8h] [ebp-14h]
  float v9; // [esp+8h] [ebp-14h]
  float v10; // [esp+8h] [ebp-14h]

  mTable = this->mTable;
  if ( mTable )
  {
    v8 = time * *rate + this->mEnvOffset.x;
    *dest = (*end - *start) * ((double (__stdcall *)(_DWORD))mTable->TableLookup)(LODWORD(v8)) + *start;
    v9 = time * rate[1] + this->mEnvOffset.y;
    dest[1] = (end[1] - start[1]) * ((double (__stdcall *)(_DWORD))this->mTable->TableLookup)(LODWORD(v9)) + start[1];
    v10 = time * rate[2] + this->mEnvOffset.z;
    dest[2] = (end[2] - start[2]) * ((double (__stdcall *)(_DWORD))this->mTable->TableLookup)(LODWORD(v10)) + start[2];
  }
  else
  {
    *dest = *start;
    dest[1] = start[1];
    dest[2] = start[2];
  }
}
