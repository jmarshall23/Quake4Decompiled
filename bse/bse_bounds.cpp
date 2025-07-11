
// FUNC: public: void __thiscall rvParticleTemplate::EvaluateSimplePosition(class idVec3 &,float,float,class idVec3 &,class idVec3 &,class idVec3 &,class idVec3 &)
void __thiscall rvParticleTemplate::EvaluateSimplePosition(
        rvParticleTemplate *this,
        idVec3 *pos,
        float time,
        float lifeTime,
        idVec3 *initPos,
        idVec3 *velocity,
        idVec3 *acceleration,
        idVec3 *friction)
{
  double v8; // st7
  double v9; // st6
  long double v12; // st7

  pos->x = time * velocity->x + initPos->x;
  pos->y = time * velocity->y + initPos->y;
  pos->z = time * velocity->z + initPos->z;
  v8 = time * time * 0.5;
  pos->x = v8 * acceleration->x + pos->x;
  pos->y = v8 * acceleration->y + pos->y;
  pos->z = v8 * acceleration->z + pos->z;
  v9 = (lifeTime - v8) / lifeTime * 1.442695040888963387;
  _ST5 = v9;
  __asm { frndint }
  v12 = v8 * ((__FSCALE__(__F2XM1__(v9 - _ST5) + 1.0, _ST5) - 1.0) * v8) * 0.33333334;
  pos->x = v12 * friction->x + pos->x;
  pos->y = v12 * friction->y + pos->y;
  pos->z = v12 * friction->z + pos->z;
}

// FUNC: public: float __thiscall rvParticleTemplate::GetMaxParmValue(class rvParticleParms &,class rvParticleParms &,class rvEnvParms &)
long double __thiscall rvParticleTemplate::GetMaxParmValue(
        rvParticleTemplate *this,
        rvParticleParms *spawn,
        rvParticleParms *death,
        rvEnvParms *envelope)
{
  double v4; // st7
  long double result; // st7
  long double v6; // st6
  float min; // [esp+0h] [ebp-34h] BYREF
  idBounds sbounds; // [esp+4h] [ebp-30h] BYREF
  idBounds dbounds; // [esp+1Ch] [ebp-18h] BYREF

  rvParticleParms::GetMinsMaxs(spawn, sbounds.b, &sbounds.b[1]);
  if ( rvEnvParms::GetMinMax(envelope, &min, (float *)&spawn) )
  {
    sbounds.b[0].x = sbounds.b[0].x * min;
    sbounds.b[0].y = sbounds.b[0].y * min;
    sbounds.b[0].z = sbounds.b[0].z * min;
    sbounds.b[1].x = sbounds.b[1].x * *(float *)&spawn;
    sbounds.b[1].y = sbounds.b[1].y * *(float *)&spawn;
    sbounds.b[1].z = sbounds.b[1].z * *(float *)&spawn;
    rvParticleParms::GetMinsMaxs(death, dbounds.b, &dbounds.b[1]);
    v4 = dbounds.b[0].x * min;
    dbounds.b[0].y = dbounds.b[0].y * min;
    dbounds.b[0].z = dbounds.b[0].z * min;
    dbounds.b[1].x = dbounds.b[1].x * *(float *)&spawn;
    dbounds.b[1].y = dbounds.b[1].y * *(float *)&spawn;
    dbounds.b[1].z = dbounds.b[1].z * *(float *)&spawn;
    if ( v4 < sbounds.b[0].x )
      sbounds.b[0].x = v4;
    if ( dbounds.b[0].y < (double)sbounds.b[0].y )
      sbounds.b[0].y = dbounds.b[0].y;
    if ( dbounds.b[0].z < (double)sbounds.b[0].z )
      sbounds.b[0].z = dbounds.b[0].z;
    if ( dbounds.b[1].x > (double)sbounds.b[1].x )
      sbounds.b[1].x = dbounds.b[1].x;
    if ( dbounds.b[1].y > (double)sbounds.b[1].y )
      sbounds.b[1].y = dbounds.b[1].y;
    if ( dbounds.b[1].z > (double)sbounds.b[1].z )
      sbounds.b[1].z = dbounds.b[1].z;
  }
  result = sqrt(sbounds.b[0].z * sbounds.b[0].z + sbounds.b[0].y * sbounds.b[0].y + sbounds.b[0].x * sbounds.b[0].x);
  v6 = sqrt(sbounds.b[1].z * sbounds.b[1].z + sbounds.b[1].y * sbounds.b[1].y + sbounds.b[1].x * sbounds.b[1].x);
  *(float *)&spawn = v6;
  if ( v6 > result )
    return *(float *)&spawn;
  return result;
}

// FUNC: public: float __thiscall rvParticleTemplate::GetFurthestDistance(void)
long double __usercall rvParticleTemplate::GetFurthestDistance@<st0>(rvParticleTemplate *this@<ecx>, double a2@<st0>)
{
  bool v3; // al
  double x; // st7
  int v5; // ebx
  double y; // st7
  double v7; // st5
  float z; // edi
  long double v9; // st7
  long double v10; // st6
  float v11; // [esp-18h] [ebp-C4h]
  idVec3 pos; // [esp+8h] [ebp-A4h] BYREF
  float v13; // [esp+14h] [ebp-98h]
  idBounds result; // [esp+18h] [ebp-94h] BYREF
  int i; // [esp+30h] [ebp-7Ch] BYREF
  idBounds accel; // [esp+34h] [ebp-78h] BYREF
  idBounds velocity; // [esp+4Ch] [ebp-60h] BYREF
  idBounds spawn; // [esp+64h] [ebp-48h] BYREF
  idBounds friction; // [esp+7Ch] [ebp-30h] BYREF
  idBounds offset; // [esp+94h] [ebp-18h] BYREF

  rvParticleParms::GetMinsMaxs(&this->mSpawnPosition, spawn.b, &spawn.b[1]);
  rvParticleParms::GetMinsMaxs(&this->mSpawnVelocity, velocity.b, &velocity.b[1]);
  rvParticleParms::GetMinsMaxs(&this->mSpawnAcceleration, accel.b, &accel.b[1]);
  rvParticleParms::GetMinsMaxs(&this->mSpawnFriction, friction.b, &friction.b[1]);
  rvParticleParms::GetMinsMaxs(&this->mSpawnOffset, offset.b, &offset.b[1]);
  v3 = game->IsMultiplayer(game);
  pos.z = 0.0;
  pos.y = 0.0;
  if ( v3 )
    cvarSystem->GetCVarFloat(cvarSystem, "g_mp_gravity");
  else
    a2 = ((double (__thiscall *)(idCVarSystem *, const char *))cvarSystem->GetCVarFloat)(cvarSystem, "g_gravity");
  pos.z = -a2;
  x = this->mGravity.x;
  v13 = pos.x;
  result.b[0].x = pos.y;
  result.b[0].y = pos.z;
  v5 = 0;
  pos.y = pos.y * x;
  pos.z = pos.z * x;
  *(float *)&i = *(float *)&i - pos.x * x;
  accel.b[0].x = accel.b[0].x - pos.y;
  accel.b[0].y = accel.b[0].y - pos.z;
  y = this->mGravity.y;
  v13 = 0.0;
  v7 = result.b[0].x;
  memset(&result, 0, sizeof(result));
  pos.y = v7 * y;
  pos.z = result.b[0].y * y;
  accel.b[0].z = pos.x * y + accel.b[0].z;
  accel.b[1].x = accel.b[1].x + pos.y;
  accel.b[1].y = accel.b[1].y + pos.z;
  do
  {
    v11 = this->mDuration.y;
    result.b[1].z = (double)SLODWORD(result.b[1].z) * v11 * 0.125;
    z = result.b[1].z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      result.b[1].z,
      v11,
      (idVec3 *)&velocity.b[1].z,
      (idVec3 *)&accel.b[1].z,
      (idVec3 *)&i,
      (idVec3 *)&spawn.b[1].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&velocity.b[1].z,
      (idVec3 *)&accel.b[1].z,
      (idVec3 *)&i,
      (idVec3 *)&friction.b[0].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&velocity.b[1].z,
      (idVec3 *)&accel.b[1].z,
      (idVec3 *)&accel.b[0].z,
      (idVec3 *)&spawn.b[1].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&velocity.b[1].z,
      (idVec3 *)&accel.b[1].z,
      (idVec3 *)&accel.b[0].z,
      (idVec3 *)&friction.b[0].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&velocity.b[1].z,
      (idVec3 *)&velocity.b[0].z,
      (idVec3 *)&i,
      (idVec3 *)&spawn.b[1].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&velocity.b[1].z,
      (idVec3 *)&velocity.b[0].z,
      (idVec3 *)&i,
      (idVec3 *)&friction.b[0].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&velocity.b[1].z,
      (idVec3 *)&velocity.b[0].z,
      (idVec3 *)&accel.b[0].z,
      (idVec3 *)&spawn.b[1].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&velocity.b[1].z,
      (idVec3 *)&velocity.b[0].z,
      (idVec3 *)&accel.b[0].z,
      (idVec3 *)&friction.b[0].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&spawn.b[0].z,
      (idVec3 *)&accel.b[1].z,
      (idVec3 *)&i,
      (idVec3 *)&spawn.b[1].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&spawn.b[0].z,
      (idVec3 *)&accel.b[1].z,
      (idVec3 *)&i,
      (idVec3 *)&friction.b[0].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&spawn.b[0].z,
      (idVec3 *)&accel.b[1].z,
      (idVec3 *)&accel.b[0].z,
      (idVec3 *)&spawn.b[1].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&spawn.b[0].z,
      (idVec3 *)&accel.b[1].z,
      (idVec3 *)&accel.b[0].z,
      (idVec3 *)&friction.b[0].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&spawn.b[0].z,
      (idVec3 *)&velocity.b[0].z,
      (idVec3 *)&i,
      (idVec3 *)&spawn.b[1].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&spawn.b[0].z,
      (idVec3 *)&velocity.b[0].z,
      (idVec3 *)&i,
      (idVec3 *)&friction.b[0].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&spawn.b[0].z,
      (idVec3 *)&velocity.b[0].z,
      (idVec3 *)&accel.b[0].z,
      (idVec3 *)&spawn.b[1].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    rvParticleTemplate::EvaluateSimplePosition(
      this,
      &pos,
      z,
      this->mDuration.y,
      (idVec3 *)&spawn.b[0].z,
      (idVec3 *)&velocity.b[0].z,
      (idVec3 *)&accel.b[0].z,
      (idVec3 *)&friction.b[0].z);
    if ( pos.x < (double)v13 )
      v13 = pos.x;
    if ( pos.x > (double)result.b[0].z )
      result.b[0].z = pos.x;
    if ( pos.y < (double)result.b[0].x )
      result.b[0].x = pos.y;
    if ( pos.y > (double)result.b[1].x )
      result.b[1].x = pos.y;
    if ( pos.z < (double)result.b[0].y )
      result.b[0].y = pos.z;
    if ( pos.z > (double)result.b[1].y )
      result.b[1].y = pos.z;
    LODWORD(result.b[1].z) = ++v5;
  }
  while ( v5 < 8 );
  v9 = sqrt(v13 * v13 + result.b[0].x * result.b[0].x + result.b[0].y * result.b[0].y) * 0.5;
  v10 = sqrt(result.b[0].z * result.b[0].z + result.b[1].x * result.b[1].x + result.b[1].y * result.b[1].y) * 0.5;
  result.b[1].z = v10;
  if ( v10 > v9 )
    return result.b[1].z;
  return v9;
}

// FUNC: public: float __thiscall rvSegmentTemplate::CalculateBounds(void)
long double __thiscall rvSegmentTemplate::CalculateBounds(rvSegmentTemplate *this)
{
  rvParticleTemplate *p_mParticleTemplate; // esi
  long double MaxParmValue; // st7
  int mType; // eax
  long double result; // st7
  float maxLength; // [esp+0h] [ebp-Ch]
  float maxDist; // [esp+4h] [ebp-8h]
  float maxSize; // [esp+8h] [ebp-4h]

  switch ( this->mSegType )
  {
    case 2:
    case 3:
    case 7:
      p_mParticleTemplate = &this->mParticleTemplate;
      MaxParmValue = rvParticleTemplate::GetMaxParmValue(
                       &this->mParticleTemplate,
                       &this->mParticleTemplate.mSpawnSize,
                       &this->mParticleTemplate.mDeathSize,
                       &this->mParticleTemplate.mSizeEnvelope);
      maxSize = MaxParmValue;
      maxDist = rvParticleTemplate::GetFurthestDistance(p_mParticleTemplate, MaxParmValue);
      mType = p_mParticleTemplate->mType;
      if ( mType == 2 || mType == 7 )
        maxLength = rvParticleTemplate::GetMaxParmValue(
                      p_mParticleTemplate,
                      &p_mParticleTemplate->mSpawnLength,
                      &p_mParticleTemplate->mDeathLength,
                      &p_mParticleTemplate->mLengthEnvelope);
      else
        maxLength = 0.0;
      result = rvParticleTemplate::GetMaxParmValue(
                 p_mParticleTemplate,
                 &p_mParticleTemplate->mSpawnOffset,
                 &p_mParticleTemplate->mDeathOffset,
                 &p_mParticleTemplate->mOffsetEnvelope)
             + maxLength
             + maxDist
             + maxSize;
      break;
    case 6:
      result = rvParticleTemplate::GetMaxParmValue(
                 &this->mParticleTemplate,
                 &this->mParticleTemplate.mSpawnSize,
                 &this->mParticleTemplate.mDeathSize,
                 &this->mParticleTemplate.mSizeEnvelope);
      break;
    default:
      result = 8.0;
      break;
  }
  return result;
}

// FUNC: public: float __thiscall rvDeclEffect::CalculateBounds(void)
double __thiscall rvDeclEffect::CalculateBounds(rvDeclEffect *this)
{
  int v2; // esi
  int v3; // ebx
  long double v4; // st7
  float size; // [esp+10h] [ebp-4h]

  v2 = 0;
  size = 0.0;
  if ( this->mSegmentTemplates.num > 0 )
  {
    v3 = 0;
    do
    {
      v4 = rvSegmentTemplate::CalculateBounds(&this->mSegmentTemplates.list[v3]);
      if ( v4 > size )
        size = v4;
      ++v2;
      ++v3;
    }
    while ( v2 < this->mSegmentTemplates.num );
  }
  return ceil(size);
}
