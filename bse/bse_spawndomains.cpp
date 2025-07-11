
// FUNC: public: bool __thiscall rvParticleParms::Compare(class rvParticleParms const &)const
bool __thiscall rvParticleParms::Compare(rvParticleParms *this, const rvParticleParms *comp)
{
  bool result; // al
  float compa; // [esp+4h] [ebp+4h]
  float compb; // [esp+4h] [ebp+4h]
  float compc; // [esp+4h] [ebp+4h]
  float compd; // [esp+4h] [ebp+4h]
  float compe; // [esp+4h] [ebp+4h]
  float compf; // [esp+4h] [ebp+4h]

  if ( this->mSpawnType != comp->mSpawnType || this->mFlags != comp->mFlags )
    return 0;
  compa = this->mMins.x - comp->mMins.x;
  result = 0;
  if ( COERCE_FLOAT(LODWORD(compa) & 0x7FFFFFFF) <= 0.001 )
  {
    compb = this->mMins.y - comp->mMins.y;
    if ( COERCE_FLOAT(LODWORD(compb) & 0x7FFFFFFF) <= 0.001 )
    {
      compc = this->mMins.z - comp->mMins.z;
      if ( COERCE_FLOAT(LODWORD(compc) & 0x7FFFFFFF) <= 0.001 )
      {
        compd = this->mMaxs.x - comp->mMaxs.x;
        if ( COERCE_FLOAT(LODWORD(compd) & 0x7FFFFFFF) <= 0.001 )
        {
          compe = this->mMaxs.y - comp->mMaxs.y;
          if ( COERCE_FLOAT(LODWORD(compe) & 0x7FFFFFFF) <= 0.001 )
          {
            compf = this->mMaxs.z - comp->mMaxs.z;
            if ( COERCE_FLOAT(LODWORD(compf) & 0x7FFFFFFF) <= 0.001 )
              return 1;
          }
        }
      }
    }
  }
  return result;
}

// FUNC: void __cdecl SpawnGetNormal(class idVec3 *,class idVec3 &,class idVec3 const *)
void __cdecl SpawnGetNormal(idVec3 *normal, idVec3 *result, const idVec3 *centre)
{
  double v3; // st7
  double v4; // st6
  long double v5; // st5
  long double v6; // rt0
  double z; // st7
  long double v8; // st4
  long double v9; // st7
  float v10; // [esp+4h] [ebp-8h]

  if ( normal )
  {
    if ( centre )
    {
      v3 = result->x - centre->x;
      v10 = result->y - centre->y;
      v4 = result->z - centre->z;
      normal->y = v10;
      normal->x = v3;
      normal->z = v4;
      v5 = v4 * v4 + v10 * v10 + v3 * v3;
      if ( v5 != 0.0 )
      {
        v6 = 1.0 / sqrt(v5);
        normal->x = v3 * v6;
        normal->y = v10 * v6;
        normal->z = v4 * v6;
      }
    }
    else
    {
      normal->x = result->x;
      normal->y = result->y;
      z = result->z;
      normal->z = result->z;
      v8 = normal->x * normal->x + normal->y * normal->y + z * z;
      if ( v8 != 0.0 )
      {
        v9 = 1.0 / sqrt(v8);
        normal->x = v9 * normal->x;
        normal->y = v9 * normal->y;
        normal->z = v9 * normal->z;
      }
    }
  }
}

// FUNC: void __cdecl SpawnNone1(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnNone1(float *result)
{
  *result = 0.0;
}

// FUNC: void __cdecl SpawnNone2(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnNone2(float *result)
{
  *result = 0.0;
  result[1] = 0.0;
}

// FUNC: void __cdecl SpawnNone3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnNone3(idVec3 *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  result->x = 0.0;
  result->y = 0.0;
  result->z = 0.0;
  SpawnGetNormal(normal, result, centre);
}

// FUNC: void __cdecl SpawnOne1(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnOne1(float *result)
{
  *result = 1.0;
}

// FUNC: void __cdecl SpawnOne2(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnOne2(float *result)
{
  *result = 1.0;
  result[1] = 1.0;
}

// FUNC: void __cdecl SpawnOne3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnOne3(idVec3 *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  result->x = 1.0;
  result->y = 1.0;
  result->z = 1.0;
  SpawnGetNormal(normal, result, centre);
}

// FUNC: void __cdecl SpawnPoint1(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnPoint1(float *result, const rvParticleParms *parms)
{
  *result = parms->mMins.x;
}

// FUNC: void __cdecl SpawnPoint2(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnPoint2(float *result, const rvParticleParms *parms)
{
  *result = parms->mMins.x;
  result[1] = parms->mMins.y;
}

// FUNC: void __cdecl SpawnPoint3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnPoint3(idVec3 *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  *result = parms->mMins;
  SpawnGetNormal(normal, result, centre);
}

// FUNC: void __cdecl SpawnLinear1(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnLinear1(float *result, const rvParticleParms *parms)
{
  *result = (parms->mMaxs.x - parms->mMins.x) * rvRandom::flrand(0.0, 1.0) + parms->mMins.x;
}

// FUNC: void __cdecl SpawnLinear2(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnLinear2(float *result, const rvParticleParms *parms)
{
  double v2; // st7

  if ( (parms->mFlags & 0x10) != 0 )
    v2 = *result;
  else
    v2 = rvRandom::flrand(0.0, 1.0);
  *result = (parms->mMaxs.x - parms->mMins.x) * v2 + parms->mMins.x;
  result[1] = (parms->mMaxs.y - parms->mMins.y) * v2 + parms->mMins.y;
}

// FUNC: void __cdecl SpawnLinear3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnLinear3(idVec3 *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  double x; // st7

  if ( (parms->mFlags & 0x10) != 0 )
    x = result->x;
  else
    x = rvRandom::flrand(0.0, 1.0);
  result->x = (parms->mMaxs.x - parms->mMins.x) * x + parms->mMins.x;
  result->y = (parms->mMaxs.y - parms->mMins.y) * x + parms->mMins.y;
  result->z = (parms->mMaxs.z - parms->mMins.z) * x + parms->mMins.z;
  SpawnGetNormal(normal, result, centre);
}

// FUNC: void __cdecl SpawnBox2(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnBox2(float *result, const rvParticleParms *parms)
{
  *result = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
  result[1] = rvRandom::flrand(parms->mMins.y, parms->mMaxs.y);
}

// FUNC: void __cdecl SpawnBox3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnBox3(idVec3 *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  result->x = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
  result->y = rvRandom::flrand(parms->mMins.y, parms->mMaxs.y);
  result->z = rvRandom::flrand(parms->mMins.z, parms->mMaxs.z);
  SpawnGetNormal(normal, result, centre);
}

// FUNC: void __cdecl SpawnSurfaceBox1(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSurfaceBox1(float *result, const rvParticleParms *parms)
{
  *result = *(&parms->mMins.x + rvRandom::irand(0, 1));
}

// FUNC: void __cdecl SpawnSurfaceBox2(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSurfaceBox2(float *result, const rvParticleParms *parms)
{
  switch ( rvRandom::irand(0, 3) )
  {
    case 0:
      *result = parms->mMins.x;
      result[1] = rvRandom::flrand(parms->mMins.y, parms->mMaxs.y);
      break;
    case 1:
      *result = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
      result[1] = parms->mMins.y;
      break;
    case 2:
      *result = parms->mMaxs.x;
      result[1] = rvRandom::flrand(parms->mMins.y, parms->mMaxs.y);
      break;
    case 3:
      *result = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
      result[1] = parms->mMaxs.y;
      break;
    default:
      return;
  }
}

// FUNC: void __cdecl SpawnSurfaceBox3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSurfaceBox3(float *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  int v4; // ebx
  const rvParticleParms *v5; // edi
  float y; // ecx
  float z; // edx
  idVec3 *v8; // eax
  double v9; // st7
  long double v10; // st4
  long double v11; // st7

  v4 = rvRandom::irand(0, 5);
  switch ( v4 )
  {
    case 0:
      v5 = parms;
      *result = parms->mMins.x;
      result[1] = rvRandom::flrand(parms->mMins.y, parms->mMaxs.y);
      goto LABEL_8;
    case 1:
      v5 = parms;
      *result = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
      y = parms->mMins.y;
      goto LABEL_7;
    case 2:
      *result = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
      result[1] = rvRandom::flrand(parms->mMins.y, parms->mMaxs.y);
      z = parms->mMins.z;
      goto LABEL_10;
    case 3:
      *result = parms->mMaxs.x;
      result[1] = rvRandom::flrand(parms->mMins.y, parms->mMaxs.y);
      result[2] = rvRandom::flrand(parms->mMins.z, parms->mMaxs.z);
      break;
    case 4:
      v5 = parms;
      *result = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
      y = parms->mMaxs.y;
LABEL_7:
      result[1] = y;
LABEL_8:
      result[2] = rvRandom::flrand(v5->mMins.z, v5->mMaxs.z);
      break;
    case 5:
      *result = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
      result[1] = rvRandom::flrand(parms->mMins.y, parms->mMaxs.y);
      z = parms->mMaxs.z;
LABEL_10:
      result[2] = z;
      break;
    default:
      break;
  }
  if ( normal )
  {
    if ( centre )
    {
      v8 = &rvBSEManagerLocal::mCubeNormals[v4];
      *normal = *v8;
    }
    else
    {
      normal->x = *result;
      normal->y = result[1];
      v9 = result[2];
      normal->z = result[2];
      v10 = normal->x * normal->x + normal->y * normal->y + v9 * v9;
      if ( v10 != 0.0 )
      {
        v11 = 1.0 / sqrt(v10);
        normal->x = v11 * normal->x;
        normal->y = v11 * normal->y;
        normal->z = v11 * normal->z;
      }
    }
  }
}

// FUNC: void __cdecl SpawnBox1(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnBox1(float *result, const rvParticleParms *parms)
{
  *result = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
}

// FUNC: void __cdecl SpawnSphere2(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSphere2(float *result, const rvParticleParms *parms)
{
  double v2; // st7
  long double v3; // st6
  float direction; // [esp+4h] [ebp-18h]
  float directiona; // [esp+4h] [ebp-18h]
  float direction_4; // [esp+8h] [ebp-14h]
  float radius; // [esp+Ch] [ebp-10h]
  float radius_4; // [esp+10h] [ebp-Ch]
  float origin; // [esp+14h] [ebp-8h]
  float origin_4; // [esp+18h] [ebp-4h]

  origin = (parms->mMaxs.x + parms->mMins.x) * 0.5;
  origin_4 = (parms->mMaxs.y + parms->mMins.y) * 0.5;
  radius = (parms->mMaxs.x - parms->mMins.x) * 0.5;
  radius_4 = (parms->mMaxs.y - parms->mMins.y) * 0.5;
  direction = rvRandom::flrand(-1.0, 1.0);
  v2 = rvRandom::flrand(-1.0, 1.0);
  v3 = 1.0 / sqrt(v2 * v2 + direction * direction);
  directiona = direction * v3;
  direction_4 = v2 * v3;
  *result = rvRandom::flrand(0.0, radius) * directiona + origin;
  result[1] = rvRandom::flrand(0.0, radius_4) * direction_4 + origin_4;
}

// FUNC: void __cdecl SpawnSphere3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSphere3(idVec3 *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  double v4; // st7
  long double v5; // st7
  long double v6; // st7
  float direction; // [esp+0h] [ebp-24h]
  float direction_4; // [esp+4h] [ebp-20h]
  float direction_8; // [esp+8h] [ebp-1Ch]
  float radius; // [esp+Ch] [ebp-18h]
  float radius_4; // [esp+10h] [ebp-14h]
  float radius_8; // [esp+14h] [ebp-10h]
  float origin; // [esp+18h] [ebp-Ch]
  float origin_4; // [esp+1Ch] [ebp-8h]
  float origin_8; // [esp+20h] [ebp-4h]

  origin = (parms->mMaxs.x + parms->mMins.x) * 0.5;
  origin_4 = (parms->mMaxs.y + parms->mMins.y) * 0.5;
  origin_8 = (parms->mMaxs.z + parms->mMins.z) * 0.5;
  radius = (parms->mMaxs.x - parms->mMins.x) * 0.5;
  radius_4 = (parms->mMaxs.y - parms->mMins.y) * 0.5;
  radius_8 = (parms->mMaxs.z - parms->mMins.z) * 0.5;
  direction = rvRandom::flrand(-1.0, 1.0);
  direction_4 = rvRandom::flrand(-1.0, 1.0);
  v4 = rvRandom::flrand(-1.0, 1.0);
  direction_8 = v4;
  v5 = v4 * direction_8 + direction_4 * direction_4 + direction * direction;
  if ( v5 != 0.0 )
  {
    v6 = 1.0 / sqrt(v5);
    direction = direction * v6;
    direction_4 = direction_4 * v6;
    direction_8 = direction_8 * v6;
  }
  result->x = rvRandom::flrand(0.0, radius) * direction + origin;
  result->y = rvRandom::flrand(0.0, radius_4) * direction_4 + origin_4;
  result->z = rvRandom::flrand(0.0, radius_8) * direction_8 + origin_8;
  SpawnGetNormal(normal, result, centre);
}

// FUNC: void __cdecl SpawnSurfaceSphere2(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSurfaceSphere2(float *result, const rvParticleParms *parms)
{
  double v2; // st7
  long double v3; // st6
  float direction; // [esp+0h] [ebp-18h]
  float directiona; // [esp+0h] [ebp-18h]
  float radius; // [esp+8h] [ebp-10h]
  float radius_4; // [esp+Ch] [ebp-Ch]
  float origin; // [esp+10h] [ebp-8h]
  float origin_4; // [esp+14h] [ebp-4h]

  origin = (parms->mMaxs.x + parms->mMins.x) * 0.5;
  origin_4 = (parms->mMaxs.y + parms->mMins.y) * 0.5;
  radius = (parms->mMaxs.x - parms->mMins.x) * 0.5;
  radius_4 = (parms->mMaxs.y - parms->mMins.y) * 0.5;
  direction = rvRandom::flrand(-1.0, 1.0);
  v2 = rvRandom::flrand(-1.0, 1.0);
  v3 = 1.0 / sqrt(v2 * v2 + direction * direction);
  directiona = direction * v3;
  *result = radius * directiona + origin;
  result[1] = v2 * v3 * radius_4 + origin_4;
}

// FUNC: void __cdecl SpawnSurfaceSphere3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSurfaceSphere3(idVec3 *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  double v4; // st7
  long double v5; // st6
  long double v6; // st5
  long double v7; // st4
  long double v8; // rt0
  float radius; // [esp+0h] [ebp-24h]
  float radius_4; // [esp+4h] [ebp-20h]
  float radius_8; // [esp+8h] [ebp-1Ch]
  float origin; // [esp+Ch] [ebp-18h]
  float origin_4; // [esp+10h] [ebp-14h]
  float origin_8; // [esp+14h] [ebp-10h]
  float direction; // [esp+18h] [ebp-Ch]
  float direction_4; // [esp+1Ch] [ebp-8h]

  origin = (parms->mMaxs.x + parms->mMins.x) * 0.5;
  origin_4 = (parms->mMaxs.y + parms->mMins.y) * 0.5;
  origin_8 = (parms->mMaxs.z + parms->mMins.z) * 0.5;
  radius = (parms->mMaxs.x - parms->mMins.x) * 0.5;
  radius_4 = (parms->mMaxs.y - parms->mMins.y) * 0.5;
  radius_8 = (parms->mMaxs.z - parms->mMins.z) * 0.5;
  direction = rvRandom::flrand(-1.0, 1.0);
  direction_4 = rvRandom::flrand(-1.0, 1.0);
  v4 = rvRandom::flrand(-1.0, 1.0);
  v5 = direction;
  v6 = direction_4;
  v7 = v4 * v4 + v6 * v6 + v5 * v5;
  if ( v7 != 0.0 )
  {
    v8 = 1.0 / sqrt(v7);
    v5 = v5 * v8;
    v6 = v6 * v8;
    v4 = v4 * v8;
  }
  result->x = radius * v5 + origin;
  result->y = v6 * radius_4 + origin_4;
  result->z = v4 * radius_8 + origin_8;
  SpawnGetNormal(normal, result, centre);
}

// FUNC: void __cdecl SpawnCylinder3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnCylinder3(idVec3 *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  double v5; // st7
  long double v6; // st6
  double v7; // st7
  float max; // [esp+0h] [ebp-24h]
  float maxa; // [esp+0h] [ebp-24h]
  float taper; // [esp+8h] [ebp-1Ch]
  float directiona; // [esp+Ch] [ebp-18h]
  float direction; // [esp+Ch] [ebp-18h]
  float direction_4; // [esp+10h] [ebp-14h]
  float radius; // [esp+14h] [ebp-10h]
  float radius_4; // [esp+18h] [ebp-Ch]
  float origin; // [esp+1Ch] [ebp-8h]
  float origin_4; // [esp+20h] [ebp-4h]
  float parmsa; // [esp+2Ch] [ebp+8h]

  origin = (parms->mMaxs.y + parms->mMins.y) * 0.5;
  origin_4 = (parms->mMaxs.z + parms->mMins.z) * 0.5;
  radius = (parms->mMaxs.y - parms->mMins.y) * 0.5;
  radius_4 = (parms->mMaxs.z - parms->mMins.z) * 0.5;
  directiona = rvRandom::flrand(-1.0, 1.0);
  v5 = rvRandom::flrand(-1.0, 1.0);
  v6 = 1.0 / sqrt(v5 * v5 + directiona * directiona);
  direction = directiona * v6;
  direction_4 = v5 * v6;
  parmsa = parms->mMaxs.x - parms->mMins.x;
  v7 = rvRandom::flrand(0.0, parmsa);
  taper = 1.0;
  if ( parmsa != 0.0 && (parms->mFlags & 4) != 0 )
    taper = v7 / parmsa;
  result->x = v7 + parms->mMins.x;
  max = radius * taper;
  result->y = rvRandom::flrand(0.0, max) * direction + origin;
  maxa = radius_4 * taper;
  result->z = rvRandom::flrand(0.0, maxa) * direction_4 + origin_4;
  SpawnGetNormal(normal, result, centre);
}

// FUNC: void __cdecl SpawnSurfaceCylinder3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSurfaceCylinder3(float *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  double v5; // st7
  long double v6; // st6
  double v7; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st6
  long double v14; // st5
  long double v15; // st5
  double v16; // st7
  long double v17; // st7
  long double v18; // st7
  float taper; // [esp+4h] [ebp-24h]
  float radius; // [esp+8h] [ebp-20h]
  float radiusa; // [esp+8h] [ebp-20h]
  float radius_4; // [esp+Ch] [ebp-1Ch]
  float directiona; // [esp+10h] [ebp-18h]
  float direction; // [esp+10h] [ebp-18h]
  float directionb; // [esp+10h] [ebp-18h]
  float direction_4; // [esp+14h] [ebp-14h]
  float v27; // [esp+18h] [ebp-10h]
  float top; // [esp+1Ch] [ebp-Ch]
  float topa; // [esp+1Ch] [ebp-Ch]
  float top_4; // [esp+20h] [ebp-8h]
  float resulta; // [esp+2Ch] [ebp+4h]
  float parmsa; // [esp+30h] [ebp+8h]

  top = (parms->mMaxs.y + parms->mMins.y) * 0.5;
  top_4 = (parms->mMaxs.z + parms->mMins.z) * 0.5;
  radius = (parms->mMaxs.y - parms->mMins.y) * 0.5;
  radius_4 = (parms->mMaxs.z - parms->mMins.z) * 0.5;
  directiona = rvRandom::flrand(-1.0, 1.0);
  v5 = rvRandom::flrand(-1.0, 1.0);
  v6 = 1.0 / sqrt(v5 * v5 + directiona * directiona);
  direction = directiona * v6;
  direction_4 = v5 * v6;
  parmsa = parms->mMaxs.x - parms->mMins.x;
  v7 = rvRandom::flrand(0.0, parmsa);
  taper = 1.0;
  if ( parmsa != 0.0 && (parms->mFlags & 4) != 0 )
    taper = v7 / parmsa;
  *result = v7 + parms->mMins.x;
  v9 = radius * direction;
  resulta = v9;
  result[1] = v9 * taper + top;
  v10 = direction_4 * radius_4;
  radiusa = v10;
  result[2] = v10 * taper + top_4;
  if ( normal )
  {
    if ( centre )
    {
      if ( taper == 1.0 )
      {
        normal->x = 0.0;
        normal->y = direction;
        normal->z = direction_4;
      }
      else if ( parmsa == 0.0 )
      {
        normal->x = 1.0;
        normal->y = 0.0;
        normal->z = 0.0;
      }
      else
      {
        v11 = -radiusa;
        directionb = resulta * resulta - radiusa * v11;
        v27 = v11 * parmsa - resulta * 0.0;
        topa = -directionb;
        normal->x = topa;
        v12 = -(radiusa * 0.0 - resulta * parmsa);
        v13 = -v27;
        normal->y = v12;
        normal->z = v13;
        v14 = v13 * v13 + v12 * v12 + topa * topa;
        if ( v14 != 0.0 )
        {
          v15 = 1.0 / sqrt(v14);
          normal->x = topa * v15;
          normal->y = v12 * v15;
          normal->z = v13 * v15;
        }
      }
    }
    else
    {
      normal->x = *result;
      normal->y = result[1];
      v16 = result[2];
      normal->z = result[2];
      v17 = v16 * v16 + normal->x * normal->x + normal->y * normal->y;
      if ( v17 != 0.0 )
      {
        v18 = 1.0 / sqrt(v17);
        normal->x = v18 * normal->x;
        normal->y = v18 * normal->y;
        normal->z = v18 * normal->z;
      }
    }
  }
}

// FUNC: void __cdecl SpawnSpiral2(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSpiral2(float *result, const rvParticleParms *parms)
{
  float *v2; // edi
  double v3; // st7

  if ( (parms->mFlags & 0x10) != 0 )
  {
    v2 = result;
    v3 = (parms->mMaxs.x - parms->mMins.x) * *result + parms->mMins.x;
  }
  else
  {
    v3 = rvRandom::flrand(parms->mMins.x, parms->mMaxs.x);
    v2 = result;
  }
  *v2 = v3;
  v2[1] = cos(idMath::TWO_PI * *v2 / parms->mRange) * rvRandom::flrand(parms->mMins.y, parms->mMaxs.y);
}

// FUNC: void __cdecl SpawnSpiral3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnSpiral3(float *result, float parms, idVec3 *normal, const idVec3 *centre)
{
  const rvParticleParms *v4; // esi
  float *v5; // edi
  double v6; // st7
  float v7; // ecx
  double v8; // st7
  double v9; // st7
  idVec3 *v10; // ecx
  bool v11; // zf
  double v12; // st7
  long double v13; // st4
  long double v14; // st7
  float z; // [esp-Ch] [ebp-28h]
  float s; // [esp+8h] [ebp-14h] BYREF
  float left; // [esp+Ch] [ebp-10h]
  float *z_low; // [esp+10h] [ebp-Ch]
  float *p_parms; // [esp+14h] [ebp-8h]
  float fraction; // [esp+18h] [ebp-4h]
  float resulta; // [esp+20h] [ebp+4h]

  v4 = (const rvParticleParms *)LODWORD(parms);
  if ( (*(_BYTE *)(LODWORD(parms) + 4) & 0x10) != 0 )
  {
    v5 = result;
    v6 = (*(float *)(LODWORD(parms) + 28) - *(float *)(LODWORD(parms) + 16)) * *result + *(float *)(LODWORD(parms) + 16);
  }
  else
  {
    v7 = *(float *)(LODWORD(parms) + 16);
    parms = *(float *)(LODWORD(parms) + 28);
    left = v7;
    v6 = rvRandom::flrand(v7, parms);
    v5 = result;
  }
  *v5 = v6;
  left = rvRandom::flrand(v4->mMins.y, v4->mMaxs.y);
  z = v4->mMaxs.z;
  z_low = (float *)LODWORD(v4->mMins.z);
  resulta = rvRandom::flrand(*(float *)&z_low, z);
  v8 = idMath::TWO_PI * *v5;
  p_parms = &parms;
  v9 = v8 / v4->mRange;
  z_low = &s;
  fraction = v9;
  parms = cos(fraction);
  s = sin(fraction);
  v10 = normal;
  v11 = normal == 0;
  v12 = parms * left - s * resulta;
  v5[1] = v12;
  v5[2] = parms * resulta + s * left;
  if ( !v11 )
  {
    v11 = centre == 0;
    v10->y = v12;
    v10->z = v5[2];
    if ( v11 )
      v10->x = *v5;
    else
      v10->x = 0.0;
    v13 = v10->x * v10->x + v10->y * v10->y + v10->z * v10->z;
    if ( v13 != 0.0 )
    {
      v14 = 1.0 / sqrt(v13);
      v10->x = v14 * v10->x;
      v10->y = v14 * v10->y;
      v10->z = v14 * v10->z;
    }
  }
}

// FUNC: public: void __thiscall rvParticleParms::HandleRelativeParms(float *,float *,int)
void __thiscall rvParticleParms::HandleRelativeParms(rvParticleParms *this, float *death, float *init, int count)
{
  int v4; // ebx
  float *v5; // ecx
  unsigned int v6; // edx
  float *v7; // eax
  double v8; // st7
  float *v9; // eax
  int v10; // esi
  double v11; // st7

  if ( (this->mFlags & 8) != 0 )
  {
    v4 = 0;
    if ( count >= 4 )
    {
      v5 = init + 3;
      v6 = ((unsigned int)(count - 4) >> 2) + 1;
      v7 = death + 1;
      v4 = 4 * v6;
      do
      {
        v7 += 4;
        v8 = *(v5 - 3) + *(v7 - 5);
        v5 += 4;
        --v6;
        *(v7 - 5) = v8;
        *(v7 - 4) = *(float *)((char *)v7 + (char *)init - (char *)death - 16) + *(v7 - 4);
        *(v7 - 3) = *(v5 - 5) + *(v7 - 3);
        *(v7 - 2) = *(v5 - 4) + *(v7 - 2);
      }
      while ( v6 );
    }
    if ( v4 < count )
    {
      v9 = &death[v4];
      v10 = count - v4;
      do
      {
        v11 = *(float *)((char *)v9++ + (char *)init - (char *)death);
        --v10;
        *(v9 - 1) = v11 + *(v9 - 1);
      }
      while ( v10 );
    }
  }
}

// FUNC: public: void __thiscall rvParticleParms::GetMinsMaxs(class idVec3 &,class idVec3 &)
void __thiscall rvParticleParms::GetMinsMaxs(rvParticleParms *this, idVec3 *mins, idVec3 *maxs)
{
  mins->z = 0.0;
  mins->y = 0.0;
  mins->x = 0.0;
  maxs->z = 0.0;
  maxs->y = 0.0;
  maxs->x = 0.0;
  switch ( this->mSpawnType )
  {
    case 5:
      goto $L117328;
    case 6:
      goto $L117327;
    case 7:
      mins->z = 1.0;
      maxs->z = 1.0;
$L117327:
      mins->y = 1.0;
      maxs->y = 1.0;
$L117328:
      mins->x = 1.0;
      maxs->x = 1.0;
      return;
    case 9:
      goto $L117331;
    case 0xA:
      goto $L117330;
    case 0xB:
      mins->z = this->mMins.z;
      maxs->z = this->mMins.z;
$L117330:
      mins->y = this->mMins.y;
      maxs->y = this->mMins.y;
$L117331:
      mins->x = this->mMins.x;
      maxs->x = this->mMins.x;
      return;
    case 0xD:
    case 0x11:
    case 0x15:
    case 0x19:
    case 0x1D:
    case 0x21:
    case 0x25:
    case 0x29:
    case 0x2D:
      goto $L117334;
    case 0xE:
    case 0x12:
    case 0x16:
    case 0x1A:
    case 0x1E:
    case 0x22:
    case 0x26:
    case 0x2A:
    case 0x2E:
      goto $L117333;
    case 0xF:
    case 0x13:
    case 0x17:
    case 0x1B:
    case 0x1F:
    case 0x23:
    case 0x27:
    case 0x2B:
    case 0x2F:
      mins->z = this->mMins.z;
      maxs->z = this->mMaxs.z;
$L117333:
      mins->y = this->mMins.y;
      maxs->y = this->mMaxs.y;
$L117334:
      mins->x = this->mMins.x;
      maxs->x = this->mMaxs.x;
      break;
    default:
      return;
  }
}

// FUNC: void __cdecl SpawnModel3(float *,class rvParticleParms const &,class idVec3 *,class idVec3 const *)
void __cdecl SpawnModel3(float *result, const rvParticleParms *parms, idVec3 *normal, const idVec3 *centre)
{
  int *mMisc; // esi
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // edi
  _DWORD *v10; // ecx
  int v11; // edx
  int v12; // eax
  float v13; // ebp
  int v14; // eax
  float v15; // ebp
  float *v16; // eax
  float v17; // ebp
  int v18; // eax
  float v19; // ecx
  int v20; // eax
  double v21; // st7
  long double v22; // st6
  long double v23; // st5
  long double v24; // st4
  long double v25; // rt0
  long double v26; // st7
  long double v27; // st7
  double v28; // st7
  double v29; // st6
  double v30; // st7
  double v31; // st6
  double v32; // st5
  double v33; // st4
  double v34; // st3
  float worka; // [esp+10h] [ebp-48h]
  idVec3 work; // [esp+10h] [ebp-48h]
  float work_4; // [esp+14h] [ebp-44h]
  float work_8; // [esp+18h] [ebp-40h]
  float scale; // [esp+1Ch] [ebp-3Ch]
  float scalea; // [esp+1Ch] [ebp-3Ch]
  float scale_4; // [esp+20h] [ebp-38h]
  float scale_4a; // [esp+20h] [ebp-38h]
  float scale_8; // [esp+24h] [ebp-34h]
  float scale_8a; // [esp+24h] [ebp-34h]
  float p3; // [esp+28h] [ebp-30h]
  float p3a; // [esp+28h] [ebp-30h]
  float p3_4; // [esp+2Ch] [ebp-2Ch]
  float p3_4a; // [esp+2Ch] [ebp-2Ch]
  float p3_8; // [esp+30h] [ebp-28h]
  float p3_8a; // [esp+30h] [ebp-28h]
  float p2; // [esp+34h] [ebp-24h]
  float p2a; // [esp+34h] [ebp-24h]
  float p2_4; // [esp+38h] [ebp-20h]
  float p2_4a; // [esp+38h] [ebp-20h]
  float p2_4b; // [esp+38h] [ebp-20h]
  float p2_8; // [esp+3Ch] [ebp-1Ch]
  float p2_8a; // [esp+3Ch] [ebp-1Ch]
  float p2_8b; // [esp+3Ch] [ebp-1Ch]
  float v59; // [esp+48h] [ebp-10h]
  float v60; // [esp+4Ch] [ebp-Ch]
  float v61; // [esp+54h] [ebp-4h]

  mMisc = (int *)parms->mMisc;
  v5 = *mMisc;
  v6 = (*(int (__thiscall **)(int *))(*mMisc + 84))(mMisc);
  v7 = rvRandom::irand(0, v6 - 1);
  v8 = *(_DWORD *)((*(int (__thiscall **)(int *, int))(v5 + 92))(mMisc, v7) + 8);
  v9 = rvRandom::irand(0, *(_DWORD *)(v8 + 52) / 3 - 1);
  v10 = (_DWORD *)(*(_DWORD *)(v8 + 56) + 12 * v9);
  v11 = *(_DWORD *)(v8 + 40);
  v12 = *v10 << 6;
  v13 = *(float *)(v12 + v11);
  v14 = v11 + v12;
  scale = v13;
  v15 = *(float *)(v14 + 4);
  scale_8 = *(float *)(v14 + 8);
  v16 = (float *)(v11 + (v10[1] << 6));
  scale_4 = v15;
  p2 = *v16;
  v17 = v16[1];
  p2_8 = v16[2];
  v18 = v10[2] << 6;
  v19 = *(float *)(v18 + v11);
  v20 = v11 + v18;
  p3 = v19;
  p3_4 = *(float *)(v20 + 4);
  p3_8 = *(float *)(v20 + 8);
  worka = rvRandom::flrand(0.0, 1.0);
  work_4 = rvRandom::flrand(0.0, 1.0);
  v21 = rvRandom::flrand(0.0, 1.0);
  v22 = work_4;
  v23 = worka;
  v24 = v23 * v23 + v21 * v21 + v22 * v22;
  if ( v24 != 0.0 )
  {
    v25 = 1.0 / sqrt(v24);
    v23 = v23 * v25;
    v22 = v22 * v25;
    v21 = v21 * v25;
  }
  work.x = v21 * p3 + v22 * p2 + v23 * scale;
  work.y = scale_4 * v23 + v21 * p3_4 + v22 * v17;
  work.z = scale_8 * v23 + v21 * p3_8 + v22 * p2_8;
  if ( normal )
  {
    if ( centre )
    {
      if ( !*(_DWORD *)(v8 + 88) )
        R_DeriveFacePlanes((srfTriangles_s *)v8);
      *normal = *(idVec3 *)(*(_DWORD *)(v8 + 88) + 16 * v9);
    }
    else
    {
      *normal = work;
      v26 = work.x * work.x + work.z * work.z + work.y * work.y;
      if ( v26 != 0.0 )
      {
        v27 = 1.0 / sqrt(v26);
        normal->x = work.x * v27;
        normal->y = work.y * v27;
        normal->z = work.z * v27;
      }
    }
    v28 = rvBSEManagerLocal::mModelToBSE.mat[2].x * normal->z
        + rvBSEManagerLocal::mModelToBSE.mat[1].x * normal->y
        + rvBSEManagerLocal::mModelToBSE.mat[0].x * normal->x;
    v29 = rvBSEManagerLocal::mModelToBSE.mat[2].y * normal->z
        + rvBSEManagerLocal::mModelToBSE.mat[0].y * normal->x
        + rvBSEManagerLocal::mModelToBSE.mat[1].y * normal->y;
    normal->z = rvBSEManagerLocal::mModelToBSE.mat[2].z * normal->z
              + rvBSEManagerLocal::mModelToBSE.mat[0].z * normal->x
              + rvBSEManagerLocal::mModelToBSE.mat[1].z * normal->y;
    normal->x = v28;
    normal->y = v29;
  }
  v30 = work.y * rvBSEManagerLocal::mModelToBSE.mat[1].x
      + work.z * rvBSEManagerLocal::mModelToBSE.mat[2].x
      + work.x * rvBSEManagerLocal::mModelToBSE.mat[0].x;
  v31 = work.y * rvBSEManagerLocal::mModelToBSE.mat[1].y
      + work.z * rvBSEManagerLocal::mModelToBSE.mat[2].y
      + work.x * rvBSEManagerLocal::mModelToBSE.mat[0].y;
  work_8 = work.y * rvBSEManagerLocal::mModelToBSE.mat[1].z
         + work.z * rvBSEManagerLocal::mModelToBSE.mat[2].z
         + work.x * rvBSEManagerLocal::mModelToBSE.mat[0].z;
  v32 = rvBSEManagerLocal::mModelToBSE.mat[1].x * *(float *)(v8 + 4)
      + rvBSEManagerLocal::mModelToBSE.mat[2].x * *(float *)(v8 + 8)
      + rvBSEManagerLocal::mModelToBSE.mat[0].x * *(float *)v8;
  v33 = rvBSEManagerLocal::mModelToBSE.mat[1].y * *(float *)(v8 + 4)
      + rvBSEManagerLocal::mModelToBSE.mat[2].y * *(float *)(v8 + 8)
      + rvBSEManagerLocal::mModelToBSE.mat[0].y * *(float *)v8;
  v59 = rvBSEManagerLocal::mModelToBSE.mat[1].z * *(float *)(v8 + 4)
      + rvBSEManagerLocal::mModelToBSE.mat[2].z * *(float *)(v8 + 8)
      + rvBSEManagerLocal::mModelToBSE.mat[0].z * *(float *)v8;
  v34 = rvBSEManagerLocal::mModelToBSE.mat[0].x * *(float *)(v8 + 12)
      + rvBSEManagerLocal::mModelToBSE.mat[1].x * *(float *)(v8 + 16)
      + rvBSEManagerLocal::mModelToBSE.mat[2].x * *(float *)(v8 + 20);
  p2_4 = rvBSEManagerLocal::mModelToBSE.mat[0].y * *(float *)(v8 + 12)
       + rvBSEManagerLocal::mModelToBSE.mat[1].y * *(float *)(v8 + 16)
       + rvBSEManagerLocal::mModelToBSE.mat[2].y * *(float *)(v8 + 20);
  p2_8a = rvBSEManagerLocal::mModelToBSE.mat[0].z * *(float *)(v8 + 12)
        + rvBSEManagerLocal::mModelToBSE.mat[1].z * *(float *)(v8 + 16)
        + rvBSEManagerLocal::mModelToBSE.mat[2].z * *(float *)(v8 + 20);
  scalea = (parms->mMaxs.x - parms->mMins.x) / (v34 - v32);
  scale_4a = (parms->mMaxs.y - parms->mMins.y) / (p2_4 - v33);
  scale_8a = (parms->mMaxs.z - parms->mMins.z) / (p2_8a - v59);
  v61 = parms->mMins.z + parms->mMaxs.z;
  p3a = (parms->mMins.x + parms->mMaxs.x) * 0.5;
  p3_4a = (parms->mMins.y + parms->mMaxs.y) * 0.5;
  p3_8a = v61 * 0.5;
  v60 = v34 + v32;
  p2a = v60 * 0.5;
  p2_4a = (p2_4 + v33) * 0.5;
  p2_4b = p3_4a - p2_4a;
  p2_8b = p3_8a - (p2_8a + v59) * 0.5;
  *result = scalea * v30 + p3a - p2a;
  result[1] = scale_4a * v31 + p2_4b;
  result[2] = scale_8a * work_8 + p2_8b;
}
