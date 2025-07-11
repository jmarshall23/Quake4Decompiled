
// FUNC: public: int __thiscall rvElectricityParticle::GetBoltCount(float)
int __thiscall rvElectricityParticle::GetBoltCount(rvElectricityParticle *this, float length)
{
  int result; // eax

  result = (int)ceil(length * 0.0625);
  if ( result < 3 )
    return 3;
  if ( result > 200 )
    return 200;
  return result;
}

// FUNC: public: virtual int __thiscall rvElectricityParticle::Update(float)
int __thiscall rvElectricityParticle::Update(rvElectricityParticle *this, float time)
{
  int result; // eax
  float v4; // [esp+4h] [ebp-18h]
  float v5; // [esp+8h] [ebp-14h]
  idVec3 length; // [esp+10h] [ebp-Ch] BYREF

  v4 = time - this->mStartTime;
  ((void (__thiscall *)(rvElectricityParticle *, _DWORD, idVec3 *))this->EvaluateLength)(this, LODWORD(v4), &length);
  v5 = sqrt(length.z * length.z + length.y * length.y + length.x * length.x);
  result = rvElectricityParticle::GetBoltCount(this, v5);
  this->mNumBolts = result;
  return result;
}

// FUNC: public: void __thiscall rvElectricityParticle::RenderLineSegment(class rvBSE const *,struct SElecWork *,class idVec3,float)
void __thiscall rvElectricityParticle::RenderLineSegment(
        rvElectricityParticle *this,
        const rvBSE *effect,
        SElecWork *work,
        idVec3 start,
        float startFraction)
{
  idDrawVert *v6; // edi
  int v7; // ecx
  double v8; // st7
  long double v9; // st7
  double v10; // st7
  idDrawVert *v11; // edi
  float v12; // [esp+8h] [ebp-18h]
  float v13; // [esp+Ch] [ebp-14h]
  float v14; // [esp+10h] [ebp-10h]
  float v15; // [esp+10h] [ebp-10h]
  float offset_4; // [esp+18h] [ebp-8h]
  float offset_4a; // [esp+18h] [ebp-8h]
  float offset_8; // [esp+1Ch] [ebp-4h]
  float offset_8a; // [esp+1Ch] [ebp-4h]
  float worka; // [esp+28h] [ebp+8h]
  float workb; // [esp+28h] [ebp+8h]
  float workc; // [esp+28h] [ebp+8h]

  v6 = &work->tri->verts[work->tri->numVerts];
  v7 = rvParticle::HandleTint(this, effect, &work->tint, work->alpha);
  v8 = work->length.y * work->viewPos.z - work->length.z * work->viewPos.y;
  v12 = v8;
  v13 = work->length.z * work->viewPos.x - work->viewPos.z * work->length.x;
  offset_4 = v13;
  v14 = work->viewPos.y * work->length.x - work->length.y * work->viewPos.x;
  offset_8 = v14;
  worka = v14 * v14 + v13 * v13 + v12 * v12;
  if ( worka != 0.0 )
  {
    v9 = 1.0 / sqrt(worka);
    workb = v9;
    v8 = v9 * v12;
    offset_4 = v13 * workb;
    offset_8 = v14 * workb;
  }
  workc = work->size;
  v10 = v8 * workc;
  v11 = v6 + 1;
  offset_4a = offset_4 * workc;
  offset_8a = offset_8 * workc;
  v15 = start.z + offset_8a;
  v11[-1].xyz.z = v15;
  v11[-1].xyz.x = start.x + v10;
  v11[-1].xyz.y = start.y + offset_4a;
  v11[-1].st.x = startFraction * work->step + work->fraction;
  v11[-1].st.y = 0.0;
  *(_DWORD *)v11[-1].color = v7;
  start.z = start.z - offset_8a;
  v11->xyz.z = start.z;
  v11->xyz.x = start.x - v10;
  v11->xyz.y = start.y - offset_4a;
  v11->st.x = startFraction * work->step + work->fraction;
  v11->st.y = 1.0;
  *(_DWORD *)v11->color = v7;
  work->tri->numVerts += 2;
}

// FUNC: public: void __thiscall rvElectricityParticle::ApplyShape(class rvBSE const *,struct SElecWork *,class idVec3,class idVec3,int,float,float)
void __thiscall rvElectricityParticle::ApplyShape(
        rvElectricityParticle *this,
        const rvBSE *effect,
        SElecWork *work,
        idVec3 start,
        idVec3 end,
        int count,
        float startFraction,
        float endFraction)
{
  const rvBSE *v8; // ebx
  rvElectricityParticle *v9; // ebp
  SElecWork *v10; // edi
  int v11; // esi
  double v12; // st7
  double v13; // st6
  long double v14; // st5
  long double v15; // st6
  long double v16; // st5
  long double v17; // st5
  double v18; // st6
  double v19; // st4
  double v20; // st4
  double v21; // st5
  double v22; // st5
  float min; // [esp+0h] [ebp-13Ch]
  float mina; // [esp+0h] [ebp-13Ch]
  float max; // [esp+4h] [ebp-138h]
  float maxa; // [esp+4h] [ebp-138h]
  float v27; // [esp+18h] [ebp-124h]
  float v28; // [esp+18h] [ebp-124h]
  float v29; // [esp+1Ch] [ebp-120h]
  float v30; // [esp+1Ch] [ebp-120h]
  float v31; // [esp+20h] [ebp-11Ch]
  float v32; // [esp+20h] [ebp-11Ch]
  float length; // [esp+24h] [ebp-118h]
  float v34; // [esp+28h] [ebp-114h]
  float v35; // [esp+2Ch] [ebp-110h]
  float v36; // [esp+30h] [ebp-10Ch]
  float left; // [esp+34h] [ebp-108h]
  float left_4; // [esp+38h] [ebp-104h]
  float forward_4; // [esp+44h] [ebp-F8h]
  float forward_8; // [esp+48h] [ebp-F4h]
  float point1; // [esp+4Ch] [ebp-F0h]
  idVec3 point1a; // [esp+4Ch] [ebp-F0h]
  float point2; // [esp+58h] [ebp-E4h]
  idVec3 point2a; // [esp+58h] [ebp-E4h]
  float down; // [esp+70h] [ebp-CCh]
  float down_4; // [esp+74h] [ebp-C8h]
  float v48; // [esp+80h] [ebp-BCh]
  float v49; // [esp+90h] [ebp-ACh]
  float shapea; // [esp+ACh] [ebp-90h]
  float v51; // [esp+BCh] [ebp-80h]
  float v52; // [esp+C0h] [ebp-7Ch]
  float v53; // [esp+C8h] [ebp-74h]
  float v54; // [esp+CCh] [ebp-70h]
  float v55; // [esp+D4h] [ebp-68h]
  float v56; // [esp+D8h] [ebp-64h]
  float v57; // [esp+E0h] [ebp-5Ch]
  float v58; // [esp+E4h] [ebp-58h]
  float v59; // [esp+ECh] [ebp-50h]
  float v60; // [esp+F0h] [ebp-4Ch]
  float v61; // [esp+F8h] [ebp-44h]
  float v62; // [esp+FCh] [ebp-40h]
  float v63; // [esp+104h] [ebp-38h]
  float v64; // [esp+108h] [ebp-34h]
  float v65; // [esp+110h] [ebp-2Ch]
  float v66; // [esp+114h] [ebp-28h]
  float v67; // [esp+120h] [ebp-1Ch]
  float v68; // [esp+12Ch] [ebp-10h]
  float v69; // [esp+138h] [ebp-4h]

  v8 = effect;
  v9 = this;
  v10 = work;
  v11 = count - 1;
  while ( count >= 1 )
  {
    v31 = rvRandom::flrand(0.050000001, 0.090000004);
    v29 = rvRandom::flrand(0.050000001, 0.090000004);
    shapea = rvRandom::flrand(0.56, 0.75999999);
    max = 0.02 - v31;
    min = -v31 - 0.02;
    v48 = rvRandom::flrand(min, max);
    maxa = 0.02 - v29;
    mina = -v29 - 0.02;
    v49 = rvRandom::flrand(mina, maxa);
    v12 = rvRandom::flrand(0.23, 0.43000001);
    v13 = end.x - start.x;
    v34 = v13;
    v35 = end.y - start.y;
    forward_4 = v35;
    v36 = end.z - start.z;
    forward_8 = v36;
    v14 = v36 * v36 + v35 * v35 + v34 * v34;
    length = sqrt(v14) * 0.69999999;
    v27 = v14;
    if ( v27 != 0.0 )
    {
      v15 = 1.0 / sqrt(v27);
      v28 = v15;
      v13 = v15 * v34;
      forward_4 = v35 * v28;
      forward_8 = v36 * v28;
    }
    v16 = forward_4 * forward_4 + v13 * v13;
    if ( v16 == 0.0 )
    {
      left = 1.0;
      left_4 = 0.0;
    }
    else
    {
      v17 = 1.0 / sqrt(v16);
      left = -(forward_4 * v17);
      left_4 = v17 * v13;
    }
    v67 = forward_4 * left - left_4 * v13;
    down = left_4 * forward_8 - forward_4 * 0.0;
    down_4 = v13 * 0.0 - forward_8 * left;
    v18 = 1.0 - shapea;
    v51 = end.y * v18;
    v52 = end.z * v18;
    v65 = start.y * shapea;
    v66 = start.z * shapea;
    v68 = v66 + v52;
    v19 = v29 * length;
    v57 = left_4 * v19;
    v58 = 0.0 * v19;
    point1 = left * v19 + start.x * shapea + end.x * v18;
    v20 = v31 * length;
    v63 = down_4 * v20;
    v64 = v67 * v20;
    point1a.x = down * v20 + point1;
    point1a.y = v63 + v57 + v65 + v51;
    point1a.z = v64 + v58 + v68;
    v53 = end.y * (1.0 - v12);
    v54 = end.z * (1.0 - v12);
    v61 = start.y * v12;
    v62 = start.z * v12;
    v69 = v62 + v54;
    v21 = v49 * length;
    v55 = left_4 * v21;
    v56 = 0.0 * v21;
    point2 = left * v21 + start.x * v12 + end.x * (1.0 - v12);
    v22 = v48 * length;
    v59 = down_4 * v22;
    v10 = work;
    v8 = effect;
    v60 = v67 * v22;
    v9 = this;
    point2a.x = down * v22 + point2;
    point2a.y = v59 + v55 + v61 + v53;
    point2a.z = v60 + v56 + v69;
    v32 = startFraction * 0.66666669 + endFraction * 0.33333334;
    rvElectricityParticle::ApplyShape(this, effect, work, start, point1a, v11, startFraction, v32);
    v30 = startFraction * 0.33333334 + endFraction * 0.66666669;
    rvElectricityParticle::ApplyShape(this, effect, work, point1a, point2a, v11, v32, v30);
    --count;
    startFraction = v30;
    start = point2a;
    --v11;
  }
  rvElectricityParticle::RenderLineSegment(v9, v8, v10, start, startFraction);
}

// FUNC: public: void __thiscall rvElectricityParticle::RenderBranch(class rvBSE const *,struct SElecWork *,class idVec3,class idVec3)
void __thiscall rvElectricityParticle::RenderBranch(
        rvElectricityParticle *this,
        const rvBSE *effect,
        SElecWork *work,
        idVec3 start,
        idVec3 end)
{
  long double v6; // st4
  long double v7; // st7
  long double v8; // st7
  long double v9; // st7
  int numVerts; // ebp
  idVec3 *coords; // ecx
  double x; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  idVec3 *v17; // eax
  srfTriangles_s *tri; // ecx
  int numIndexes; // eax
  int v20; // ecx
  int v21; // eax
  float min; // [esp+0h] [ebp-C4h]
  float mina; // [esp+0h] [ebp-C4h]
  float minb; // [esp+0h] [ebp-C4h]
  bool eval; // [esp+1Bh] [ebp-A9h]
  float fraction; // [esp+1Ch] [ebp-A8h]
  idVec3 current; // [esp+20h] [ebp-A4h]
  float offset; // [esp+2Ch] [ebp-98h]
  float offset_4; // [esp+30h] [ebp-94h]
  float offset_8; // [esp+34h] [ebp-90h]
  int count; // [esp+38h] [ebp-8Ch]
  idVec3 old; // [esp+3Ch] [ebp-88h]
  float left; // [esp+48h] [ebp-7Ch]
  float left_4; // [esp+4Ch] [ebp-78h]
  float pos; // [esp+54h] [ebp-70h]
  float pos_4; // [esp+58h] [ebp-6Ch]
  float pos_8; // [esp+5Ch] [ebp-68h]
  float pos_8a; // [esp+5Ch] [ebp-68h]
  float v39; // [esp+60h] [ebp-64h]
  float v40; // [esp+64h] [ebp-60h]
  float v41; // [esp+68h] [ebp-5Ch]
  float v42; // [esp+6Ch] [ebp-58h]
  float v43; // [esp+70h] [ebp-54h]
  float v44; // [esp+74h] [ebp-50h]
  idVec3 *v45; // [esp+78h] [ebp-4Ch]
  float v46; // [esp+7Ch] [ebp-48h]
  float v47; // [esp+80h] [ebp-44h]
  float v48; // [esp+84h] [ebp-40h]
  float v49; // [esp+8Ch] [ebp-38h]
  float v50; // [esp+90h] [ebp-34h]
  float v51; // [esp+98h] [ebp-2Ch]
  float v52; // [esp+9Ch] [ebp-28h]
  float v53; // [esp+A0h] [ebp-24h]
  float v54; // [esp+A8h] [ebp-1Ch]
  float v55; // [esp+B0h] [ebp-14h]
  float v56; // [esp+B4h] [ebp-10h]
  float v57; // [esp+C0h] [ebp-4h]

  v6 = work->forward.x * work->forward.x + work->forward.y * work->forward.y + work->forward.z * work->forward.z;
  if ( v6 != 0.0 )
  {
    v7 = 1.0 / sqrt(v6);
    work->forward.x = v7 * work->forward.x;
    work->forward.y = v7 * work->forward.y;
    work->forward.z = v7 * work->forward.z;
  }
  v8 = work->forward.x * work->forward.x + work->forward.y * work->forward.y;
  if ( v8 == 0.0 )
  {
    left = 1.0;
    left_4 = 0.0;
  }
  else
  {
    v9 = 1.0 / sqrt(v8);
    left = -(v9 * work->forward.y);
    left_4 = v9 * work->forward.x;
  }
  fraction = work->step;
  numVerts = work->tri->numVerts;
  *(_QWORD *)&old.y = *(_QWORD *)&start.y;
  eval = 1;
  count = 0;
  v42 = left_4 * work->forward.z - work->forward.y * 0.0;
  offset_8 = 0.0;
  offset_4 = 0.0;
  offset = 0.0;
  coords = work->coords;
  v43 = work->forward.x * 0.0 - left * work->forward.z;
  v44 = left * work->forward.y - left_4 * work->forward.x;
  x = start.x;
  old.x = start.x;
  while ( 1 )
  {
    ++count;
    coords->x = x;
    v45 = coords + 1;
    *(_QWORD *)&coords->y = *(_QWORD *)&old.y;
    if ( 1.0 - work->step * 0.5 <= fraction )
    {
      fraction = 1.0;
      eval = 0;
    }
    min = -this->mJitterSize.x;
    v13 = rvRandom::flrand(min, this->mJitterSize.x);
    v39 = v13 * work->forward.x;
    v40 = v13 * work->forward.y;
    v41 = v13 * work->forward.z;
    mina = -this->mJitterSize.y;
    v14 = rvRandom::flrand(mina, this->mJitterSize.y);
    v49 = left_4 * v14;
    v50 = v14 * 0.0;
    pos = left * v14 + v39;
    pos_4 = v49 + v40;
    pos_8 = v50 + v41;
    minb = -this->mJitterSize.z;
    v15 = rvRandom::flrand(minb, this->mJitterSize.z);
    v55 = v43 * v15;
    v56 = v44 * v15;
    pos_8a = v56 + pos_8;
    offset = v42 * v15 + pos + offset;
    offset_4 = v55 + pos_4 + offset_4;
    offset_8 = pos_8a + offset_8;
    v16 = ((double (__thiscall *)(const idDeclTable *, _DWORD))this->mJitterTable->TableLookup)(
            this->mJitterTable,
            LODWORD(fraction));
    v48 = end.z - start.z;
    v57 = v48 * fraction;
    v46 = end.x - start.x;
    v53 = v46 * fraction + start.x;
    v54 = v57 + start.z;
    v51 = offset_4 * v16;
    v52 = offset_8 * v16;
    current.x = offset * v16 + v53;
    v47 = end.y - start.y;
    current.y = v51 + v47 * fraction + start.y;
    current.z = v52 + v54;
    work->fraction = fraction - work->step;
    rvElectricityParticle::ApplyShape(this, effect, work, old, current, 2, 0.0, 1.0);
    x = current.x;
    old.x = current.x;
    *(_QWORD *)&old.y = *(_QWORD *)&current.y;
    fraction = fraction + work->step;
    if ( !eval )
      break;
    coords = v45;
  }
  if ( numVerts != work->tri->numVerts )
  {
    v17 = &work->coords[count];
    v17->y = current.y;
    v17->x = current.x;
    v17->z = current.z;
    rvElectricityParticle::RenderLineSegment(this, effect, work, current, 1.0);
    tri = work->tri;
    numIndexes = tri->numIndexes;
    if ( numVerts < tri->numVerts - 2 )
    {
      v20 = numVerts + 3;
      do
      {
        work->tri->indexes[numIndexes] = numVerts;
        v21 = numIndexes + 1;
        work->tri->indexes[v21] = v20 - 2;
        work->tri->indexes[++v21] = v20;
        work->tri->indexes[++v21] = numVerts;
        work->tri->indexes[v21 + 1] = v20;
        v21 += 2;
        work->tri->indexes[v21] = v20 - 1;
        numVerts += 2;
        numIndexes = v21 + 1;
        v20 += 2;
      }
      while ( numVerts < work->tri->numVerts - 2 );
    }
    work->tri->numIndexes = numIndexes;
  }
}

// FUNC: public: virtual void __thiscall rvElectricityParticle::SetupElectricity(class rvParticleTemplate *)
void __thiscall rvElectricityParticle::SetupElectricity(rvElectricityParticle *this, rvParticleTemplate *pt)
{
  this->mNumForks = pt->mNumForks;
  this->mSeed = rvRandom::Init();
  this->mForkSizeMins = pt->mForkSizeMins;
  this->mForkSizeMaxs = pt->mForkSizeMaxs;
  this->mJitterSize = pt->mJitterSize;
  this->mLastJitter = 0.0;
  this->mJitterRate = pt->mJitterRate;
  this->mJitterTable = pt->mJitterTable;
}

// FUNC: public: virtual bool __thiscall rvElectricityParticle::Render(class rvBSE const *,class idMat3 const &,struct srfTriangles_s *,float,float)
char __thiscall rvElectricityParticle::Render(
        rvElectricityParticle *this,
        const rvBSE *effect,
        const idMat3 *view,
        srfTriangles_s *tri,
        float time,
        float override)
{
  const rvBSE *v7; // esi
  int mFlags; // eax
  double v9; // st7
  double v10; // st6
  long double v11; // st7
  long double v12; // st7
  long double v13; // st7
  long double v14; // st7
  unsigned int v16; // eax
  double v17; // st7
  double v18; // st7
  float y; // edx
  float z; // eax
  float *p_z; // edi
  int v22; // eax
  float x; // ecx
  float v24; // edx
  float *v25; // edi
  double v26; // st7
  float v27; // edx
  double v28; // st6
  double v29; // st7
  float v30; // ecx
  double v31; // st7
  float v32; // eax
  double v33; // st7
  double v34; // st7
  double v35; // st6
  double v36; // st5
  long double v37; // st7
  idVec3 v38; // [esp+0h] [ebp-B38h]
  float v39; // [esp+4h] [ebp-B34h]
  float v40; // [esp+Ch] [ebp-B2Ch]
  float v41; // [esp+14h] [ebp-B24h]
  float v42; // [esp+14h] [ebp-B24h]
  float v43; // [esp+14h] [ebp-B24h]
  float forkLengthb; // [esp+28h] [ebp-B10h]
  float forkLength; // [esp+28h] [ebp-B10h]
  int forkLengtha; // [esp+28h] [ebp-B10h]
  int i; // [esp+2Ch] [ebp-B0Ch]
  int ia; // [esp+2Ch] [ebp-B0Ch]
  idVec3 velocity; // [esp+34h] [ebp-B04h] BYREF
  float evalTime; // [esp+40h] [ebp-AF8h] BYREF
  idVec3 point; // [esp+44h] [ebp-AF4h]
  idVec3 position; // [esp+50h] [ebp-AE8h] BYREF
  float v53; // [esp+5Ch] [ebp-ADCh]
  float v54; // [esp+60h] [ebp-AD8h]
  float v55; // [esp+64h] [ebp-AD4h]
  unsigned int seed; // [esp+68h] [ebp-AD0h]
  float length; // [esp+6Ch] [ebp-ACCh]
  float v58[9]; // [esp+70h] [ebp-AC8h] BYREF
  float v59[9]; // [esp+94h] [ebp-AA4h] BYREF
  float v60; // [esp+B8h] [ebp-A80h]
  float v61; // [esp+CCh] [ebp-A6Ch]
  SElecWork work; // [esp+D0h] [ebp-A68h] BYREF
  idVec3 forkPoints[16]; // [esp+A78h] [ebp-C0h] BYREF

  if ( !rvParticle::GetEvaluationTime(this, time, &evalTime, 0) )
    return 0;
  forkLengthb = evalTime;
  rvEnvParms3::Evaluate(&this->mTintEnv, evalTime, &work.tint.x);
  rvEnvParms1::Evaluate(&this->mFadeEnv, forkLengthb, &work.tint.w);
  ((void (__thiscall *)(rvElectricityParticle *, _DWORD, float *))this->EvaluateSize)(
    this,
    LODWORD(evalTime),
    &work.size);
  ((void (__thiscall *)(rvElectricityParticle *, _DWORD, idVec3 *))this->EvaluateLength)(
    this,
    LODWORD(evalTime),
    &work.length);
  v7 = effect;
  v41 = time - this->mMotionStartTime;
  rvParticle::EvaluatePosition(this, effect, &position, v41);
  mFlags = this->mFlags;
  if ( (mFlags & 2) == 0 )
  {
    v59[0] = this->mInitAxis.mat[0].x * effect->mCurrentAxis.mat[0].x
           + this->mInitAxis.mat[0].y * effect->mCurrentAxis.mat[0].y
           + effect->mCurrentAxis.mat[0].z * this->mInitAxis.mat[0].z;
    v59[1] = this->mInitAxis.mat[0].y * effect->mCurrentAxis.mat[1].y
           + effect->mCurrentAxis.mat[1].z * this->mInitAxis.mat[0].z
           + effect->mCurrentAxis.mat[1].x * this->mInitAxis.mat[0].x;
    v59[2] = this->mInitAxis.mat[0].y * effect->mCurrentAxis.mat[2].y
           + this->mInitAxis.mat[0].x * effect->mCurrentAxis.mat[2].x
           + effect->mCurrentAxis.mat[2].z * this->mInitAxis.mat[0].z;
    v59[3] = this->mInitAxis.mat[1].y * effect->mCurrentAxis.mat[0].y
           + this->mInitAxis.mat[1].z * effect->mCurrentAxis.mat[0].z
           + this->mInitAxis.mat[1].x * effect->mCurrentAxis.mat[0].x;
    v59[4] = effect->mCurrentAxis.mat[1].z * this->mInitAxis.mat[1].z
           + effect->mCurrentAxis.mat[1].y * this->mInitAxis.mat[1].y
           + effect->mCurrentAxis.mat[1].x * this->mInitAxis.mat[1].x;
    v59[5] = this->mInitAxis.mat[1].z * effect->mCurrentAxis.mat[2].z
           + this->mInitAxis.mat[1].y * effect->mCurrentAxis.mat[2].y
           + this->mInitAxis.mat[1].x * effect->mCurrentAxis.mat[2].x;
    v59[6] = this->mInitAxis.mat[2].y * effect->mCurrentAxis.mat[0].y
           + this->mInitAxis.mat[2].z * effect->mCurrentAxis.mat[0].z
           + this->mInitAxis.mat[2].x * effect->mCurrentAxis.mat[0].x;
    v59[7] = effect->mCurrentAxis.mat[1].z * this->mInitAxis.mat[2].z
           + effect->mCurrentAxis.mat[1].y * this->mInitAxis.mat[2].y
           + effect->mCurrentAxis.mat[1].x * this->mInitAxis.mat[2].x;
    v59[8] = this->mInitAxis.mat[2].z * effect->mCurrentAxis.mat[2].z
           + this->mInitAxis.mat[2].y * effect->mCurrentAxis.mat[2].y
           + this->mInitAxis.mat[2].x * effect->mCurrentAxis.mat[2].x;
    qmemcpy(v58, v59, sizeof(v58));
    v9 = v58[0] * work.length.x + work.length.z * v58[6] + work.length.y * v58[3];
    v7 = effect;
    v10 = v58[1] * work.length.x + v58[7] * work.length.z + v58[4] * work.length.y;
    work.length.z = v58[2] * work.length.x + v58[8] * work.length.z + v58[5] * work.length.y;
    work.length.x = v9;
    work.length.y = v10;
  }
  if ( (mFlags & 0x10000) != 0 )
  {
    v42 = time - this->mMotionStartTime;
    rvParticle::EvaluateVelocity(this, v7, &velocity, v42);
    v11 = velocity.x * velocity.x + velocity.z * velocity.z + velocity.y * velocity.y;
    if ( v11 != 0.0 )
    {
      v12 = 1.0 / sqrt(v11);
      velocity.x = velocity.x * v12;
      velocity.y = velocity.y * v12;
      velocity.z = velocity.z * v12;
    }
    v13 = sqrt(work.length.x * work.length.x + work.length.z * work.length.z + work.length.y * work.length.y);
    v55 = velocity.z * v13;
    work.length.z = v55;
    work.length.x = velocity.x * v13;
    work.length.y = velocity.y * v13;
  }
  v14 = sqrt(work.length.x * work.length.x + work.length.z * work.length.z + work.length.y * work.length.y);
  length = v14;
  if ( v14 < 0.1 )
    return 0;
  v16 = rvRandom::irand(0, 0x7FFF);
  v17 = this->mJitterRate + this->mLastJitter;
  seed = v16;
  if ( v17 <= time )
  {
    this->mLastJitter = time;
    this->mSeed = rvRandom::Init();
  }
  rvRandom::mSeed = this->mSeed;
  v18 = this->mTextureScale / (double)this->mNumBolts;
  y = view->mat[0].y;
  z = view->mat[0].z;
  work.viewPos.x = view->mat[0].x;
  work.viewPos.y = y;
  work.viewPos.z = z;
  work.tri = tri;
  work.alpha = override;
  work.forward = work.length;
  work.step = v18;
  point.x = position.x + work.length.x;
  point.y = position.y + work.length.y;
  point.z = position.z + work.length.z;
  rvElectricityParticle::RenderBranch(this, v7, &work, position, point);
  i = 0;
  if ( this->mNumForks > 0 )
  {
    p_z = &forkPoints[0].z;
    do
    {
      v22 = rvRandom::irand(1, this->mNumBolts - 1);
      x = work.coords[v22].x;
      v24 = work.coords[v22].y;
      *p_z = work.coords[v22].z;
      *(p_z - 2) = x;
      *(p_z - 1) = v24;
      p_z += 3;
      ++i;
    }
    while ( i < this->mNumForks );
  }
  ia = 0;
  if ( this->mNumForks > 0 )
  {
    v25 = &forkPoints[0].z;
    do
    {
      v26 = position.x + *(v25 - 2);
      v27 = this->mForkSizeMins.x;
      v43 = this->mForkSizeMaxs.x;
      v28 = position.y + *(v25 - 1);
      v61 = position.z + *v25;
      v60 = v26 + work.length.x;
      v53 = v60 * 0.5;
      v54 = (v28 + work.length.y) * 0.5;
      v55 = (v61 + work.length.z) * 0.5;
      v29 = rvRandom::flrand(v27, v43);
      v30 = this->mForkSizeMins.y;
      v40 = this->mForkSizeMaxs.y;
      point.x = v29 + v53;
      v31 = rvRandom::flrand(v30, v40);
      v32 = this->mForkSizeMins.z;
      v39 = this->mForkSizeMaxs.z;
      point.y = v31 + v54;
      v33 = rvRandom::flrand(v32, v39);
      point.z = v33 + v55;
      v34 = point.x - *(v25 - 2);
      v35 = point.y - *(v25 - 1);
      v36 = point.z - *v25;
      work.forward.x = v34;
      work.forward.y = v35;
      work.forward.z = v36;
      v37 = sqrt(v36 * v36 + v35 * v35 + v34 * v34);
      forkLength = v37;
      if ( v37 > 1.0 && forkLength < (double)length )
      {
        forkLengtha = (int)ceil(forkLength * 0.0625);
        if ( forkLengtha >= 3 )
        {
          if ( forkLengtha > 200 )
            forkLengtha = 200;
        }
        else
        {
          forkLengtha = 3;
        }
        v38 = *(idVec3 *)(v25 - 2);
        work.step = 1.0 / (double)forkLengtha;
        rvElectricityParticle::RenderBranch(this, v7, &work, v38, point);
      }
      v25 += 3;
      ++ia;
    }
    while ( ia < this->mNumForks );
  }
  rvRandom::mSeed = seed;
  return 1;
}
