
// FUNC: public: bool __thiscall rvEnvParms::operator!=(class rvEnvParms const &)const
BOOL __thiscall rvEnvParms::operator!=(rvEnvParms *this, const rvEnvParms *comp)
{
  return !rvEnvParms::Compare(this, comp);
}

// FUNC: public: int __thiscall rvEnvParms::GetType(void)const
int __thiscall rvEnvParms::GetType(rvEnvParms *this)
{
  if ( this->mTable )
    return this->mTable->base->Index(this->mTable->base);
  else
    return 0;
}

// FUNC: public: void __thiscall rvEnvParms3::Scale(float)
void __thiscall rvEnvParms3::Scale(rvEnvParms3 *this, float constant)
{
  this->mStart.x = constant * this->mStart.x;
  this->mStart.y = constant * this->mStart.y;
  this->mStart.z = constant * this->mStart.z;
  this->mEnd.x = constant * this->mEnd.x;
  this->mEnd.y = constant * this->mEnd.y;
  this->mEnd.z = constant * this->mEnd.z;
}

// FUNC: public: void __thiscall rvEnvParms3::Transform(class idVec3)
void __thiscall rvEnvParms3::Transform(rvEnvParms3 *this, idVec3 normal)
{
  float *v3; // eax
  double v4; // st7
  double v5; // st6
  float *v6; // eax
  double v7; // st7
  double v8; // st6
  idMat3 result; // [esp+4h] [ebp-24h] BYREF

  v3 = (float *)idVec3::ToMat3(&normal, &result);
  v4 = v3[6] * this->mStart.z + v3[3] * this->mStart.y + this->mStart.x * *v3;
  v5 = v3[1] * this->mStart.x + v3[7] * this->mStart.z + v3[4] * this->mStart.y;
  this->mStart.z = v3[2] * this->mStart.x + v3[8] * this->mStart.z + v3[5] * this->mStart.y;
  this->mStart.x = v4;
  this->mStart.y = v5;
  v6 = (float *)idVec3::ToMat3(&normal, &result);
  v7 = v6[6] * this->mEnd.z + v6[3] * this->mEnd.y + this->mEnd.x * *v6;
  v8 = v6[1] * this->mEnd.x + v6[7] * this->mEnd.z + v6[4] * this->mEnd.y;
  this->mEnd.z = v6[2] * this->mEnd.x + v6[8] * this->mEnd.z + v6[5] * this->mEnd.y;
  this->mEnd.x = v7;
  this->mEnd.y = v8;
}
