
// FUNC: public: bool __thiscall rvParticle::GetEvaluationTime(float,float &,bool)
bool __thiscall rvParticle::GetEvaluationTime(rvParticle *this, float time, float *evalTime, bool infinite)
{
  *evalTime = time - this->mStartTime;
  if ( this->mEndTime - 0.0020000001 <= time )
    *evalTime = this->mEndTime - this->mStartTime - 0.0020000001;
  if ( infinite )
    return 1;
  return this->mStartTime - 0.0020000001 < time && time < (double)this->mEndTime;
}

// FUNC: public: int __thiscall rvParticle::HandleTint(class rvBSE const *,class idVec4 &,float)
char __thiscall rvParticle::HandleTint(rvParticle *this, const rvBSE *effect, idVec4 *colour, float alpha)
{
  double x; // st7
  double v5; // st7
  float tint; // [esp+4h] [ebp-10h]

  x = effect->mTint.x;
  if ( (this->mFlags & 0x8000) != 0 )
    v5 = x * colour->w * colour->x * alpha;
  else
    v5 = x * colour->x;
  tint = v5 * effect->mBrightness;
  return (int)(tint * 255.0);
}

// FUNC: public: void __thiscall rvParticle::RenderQuadTrail(class rvBSE const *,struct srfTriangles_s *,class idVec3,float,class idVec4 &,class idVec3 &,bool)
void __thiscall rvParticle::RenderQuadTrail(
        rvParticle *this,
        const rvBSE *effect,
        srfTriangles_s *tri,
        idVec3 offset,
        float fraction,
        idVec4 *colour,
        idVec3 *pos,
        bool first)
{
  int v8; // eax
  double v9; // st7
  double v10; // st6
  idDrawVert *v11; // ecx
  double v12; // st6
  double v13; // st7
  float v14; // [esp+10h] [ebp-4h]

  LOBYTE(v8) = rvParticle::HandleTint(this, effect, colour, 1.0);
  v9 = offset.x + pos->x;
  v10 = offset.y + pos->y;
  v11 = &tri->verts[tri->numVerts + 1];
  v14 = offset.z + pos->z;
  v11[-1].xyz.z = v14;
  v11[-1].xyz.x = v9;
  v11[-1].xyz.y = v10;
  v11[-1].st.x = 0.0;
  v11[-1].st.y = fraction;
  *(_DWORD *)v11[-1].color = v8;
  offset.z = pos->z - offset.z;
  v12 = pos->x - offset.x;
  v13 = pos->y - offset.y;
  v11->xyz.z = offset.z;
  v11->xyz.x = v12;
  v11->xyz.y = v13;
  v11->st.x = 1.0;
  v11->st.y = fraction;
  *(_DWORD *)v11->color = v8;
  if ( !first )
  {
    tri->indexes[tri->numIndexes] = tri->numVerts - 2;
    tri->indexes[tri->numIndexes + 1] = tri->numVerts - 1;
    tri->indexes[tri->numIndexes + 2] = tri->numVerts;
    tri->indexes[tri->numIndexes + 3] = tri->numVerts - 1;
    tri->indexes[tri->numIndexes + 4] = tri->numVerts;
    tri->indexes[tri->numIndexes + 5] = tri->numVerts + 1;
    tri->numIndexes += 6;
  }
  tri->numVerts += 2;
}

// FUNC: public: virtual void __thiscall rvParticle::RenderMotion(class rvBSE *,struct srfTriangles_s *,struct renderEffect_s const *,float)
void __thiscall rvParticle::RenderMotion(
        rvParticle *this,
        rvBSE *effect,
        srfTriangles_s *tri,
        const renderEffect_s *owner,
        float time)
{
  double mStartTime; // st7
  double v7; // st7
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st7
  double v13; // st7
  long double v14; // st6
  long double v15; // st6
  int v16; // edi
  double v17; // st7
  float v18; // [esp+4h] [ebp-7Ch]
  float v19; // [esp+8h] [ebp-78h]
  float v20; // [esp+8h] [ebp-78h]
  float v21; // [esp+1Ch] [ebp-64h]
  float fade; // [esp+2Ch] [ebp-54h]
  float delta; // [esp+30h] [ebp-50h]
  idVec3 offset; // [esp+34h] [ebp-4Ch]
  float offset_4; // [esp+38h] [ebp-48h]
  float offset_8; // [esp+3Ch] [ebp-44h]
  float v27; // [esp+40h] [ebp-40h]
  float v28; // [esp+44h] [ebp-3Ch]
  float v29; // [esp+48h] [ebp-38h]
  float v30; // [esp+4Ch] [ebp-34h]
  float v31; // [esp+4Ch] [ebp-34h]
  float v32; // [esp+50h] [ebp-30h]
  float v33; // [esp+50h] [ebp-30h]
  float v34; // [esp+50h] [ebp-30h]
  float v35; // [esp+54h] [ebp-2Ch]
  float v36; // [esp+54h] [ebp-2Ch]
  idVec3 position; // [esp+58h] [ebp-28h] BYREF
  idVec3 size; // [esp+64h] [ebp-1Ch] BYREF
  idVec4 colour; // [esp+70h] [ebp-10h] BYREF
  float effectb; // [esp+84h] [ebp+4h]
  rvBSE *effecta; // [esp+84h] [ebp+4h]
  float effectc; // [esp+84h] [ebp+4h]
  const renderEffect_s *ownera; // [esp+8Ch] [ebp+Ch]

  if ( this->mTrailCount )
  {
    mStartTime = time - this->mTrailTime;
    if ( mStartTime < this->mStartTime )
      mStartTime = this->mStartTime;
    v7 = time - mStartTime;
    delta = v7;
    if ( v7 > 0.0020000001 )
    {
      v21 = time - this->mStartTime;
      rvEnvParms3::Evaluate(&this->mTintEnv, v21, &colour.x);
      rvEnvParms1::Evaluate(&this->mFadeEnv, v21, &colour.w);
      v18 = time - this->mStartTime;
      ((void (__thiscall *)(rvParticle *, _DWORD, idVec3 *))this->EvaluateSize)(this, LODWORD(v18), &size);
      v19 = time - this->mMotionStartTime;
      rvParticle::EvaluatePosition(this, effect, &position, v19);
      v9 = effect->mViewOrg.x - owner->origin.x;
      v10 = effect->mViewOrg.y - owner->origin.y;
      v11 = effect->mViewOrg.z - owner->origin.z;
      fade = colour.w;
      v30 = v10 * owner->axis.mat[0].y + v11 * owner->axis.mat[0].z + owner->axis.mat[0].x * v9;
      v32 = v10 * owner->axis.mat[1].y + v11 * owner->axis.mat[1].z + owner->axis.mat[1].x * v9;
      v27 = v30 - this->mInitPos.x;
      v28 = v32 - this->mInitPos.y;
      v12 = v10 * owner->axis.mat[2].y + v11 * owner->axis.mat[2].z + owner->axis.mat[2].x * v9 - this->mInitPos.z;
      v29 = v12;
      v13 = v12 * this->mVelocity.y - v28 * this->mVelocity.z;
      v31 = v13;
      v33 = v27 * this->mVelocity.z - v29 * this->mVelocity.x;
      offset_4 = v33;
      v35 = v28 * this->mVelocity.x - v27 * this->mVelocity.y;
      offset_8 = v35;
      if ( 0.0 == v35 * v35 + v33 * v33 + v31 * v31 )
      {
        v34 = v27 * 0.0 - v29 * 0.0;
        v13 = v29 - v28 * 0.0;
        offset_4 = v34;
        v36 = v28 * 0.0 - v27;
        offset_8 = v36;
      }
      v14 = offset_8 * offset_8 + offset_4 * offset_4 + v13 * v13;
      if ( v14 != 0.0 )
      {
        v15 = 1.0 / sqrt(v14);
        v13 = v13 * v15;
        offset_4 = offset_4 * v15;
        offset_8 = offset_8 * v15;
      }
      v16 = 0;
      ownera = (const renderEffect_s *)this->mTrailCount;
      effectb = size.x * 0.5;
      offset.x = v13 * effectb;
      offset.y = offset_4 * effectb;
      v17 = offset_8 * effectb;
      effecta = 0;
      offset.z = v17;
      if ( (int)ownera > 0 )
      {
        do
        {
          effectc = (double)(int)effecta / (double)(int)ownera;
          colour.w = (1.0 - effectc) * fade;
          rvParticle::RenderQuadTrail(this, effect, tri, offset, effectc, &colour, &position, v16 == 0);
          v20 = time - effectc * delta - this->mMotionStartTime;
          rvParticle::EvaluatePosition(this, effect, &position, v20);
          effecta = (rvBSE *)++v16;
          ownera = (const renderEffect_s *)this->mTrailCount;
        }
        while ( v16 < (int)ownera );
      }
      if ( this->mTrailCount )
      {
        colour.w = 0.0;
        rvParticle::RenderQuadTrail(this, effect, tri, offset, 1.0, &colour, &position, 0);
      }
    }
  }
}

// FUNC: public: virtual bool __thiscall rvSpriteParticle::Render(class rvBSE const *,class idMat3 const &,struct srfTriangles_s *,float,float)
char __thiscall rvSpriteParticle::Render(
        rvSpriteParticle *this,
        const rvBSE *effect,
        const idMat3 *view,
        srfTriangles_s *tri,
        float time,
        float override)
{
  idDrawVert *v8; // esi
  int v9; // eax
  float y; // edx
  float v11; // ecx
  double v12; // st7
  double v13; // st6
  double v14; // st5
  double v15; // st7
  double v16; // st6
  double v17; // st5
  double v18; // st4
  double v19; // st3
  double v20; // st7
  double v21; // st6
  double v22; // st5
  idDrawVert *v23; // esi
  double v24; // st6
  double v25; // st5
  double v26; // st6
  double v27; // st5
  double v28; // st6
  double v29; // st7
  float v30; // [esp+10h] [ebp-74h]
  float c; // [esp+24h] [ebp-60h]
  float s; // [esp+28h] [ebp-5Ch]
  float evalTime; // [esp+2Ch] [ebp-58h] BYREF
  idVec2 size; // [esp+30h] [ebp-54h] BYREF
  idVec2 spriteSize; // [esp+38h] [ebp-4Ch]
  float v36; // [esp+40h] [ebp-44h]
  idVec3 position; // [esp+44h] [ebp-40h] BYREF
  float v38; // [esp+50h] [ebp-34h]
  float v39; // [esp+54h] [ebp-30h]
  float v40; // [esp+58h] [ebp-2Ch]
  idVec3 left; // [esp+5Ch] [ebp-28h]
  float v42; // [esp+68h] [ebp-1Ch]
  float v43; // [esp+70h] [ebp-14h]
  idVec4 tint; // [esp+74h] [ebp-10h] BYREF

  evalTime = time - this->mStartTime;
  if ( this->mEndTime - 0.0020000001 <= time )
    evalTime = this->mEndTime - this->mStartTime - 0.0020000001;
  if ( this->mStartTime - 0.0020000001 >= time || time >= (double)this->mEndTime )
    return 0;
  rvEnvParms3::Evaluate(&this->mTintEnv, evalTime, &tint.x);
  rvEnvParms1::Evaluate(&this->mFadeEnv, evalTime, &tint.w);
  ((void (__thiscall *)(rvSpriteParticle *, _DWORD, idVec2 *))this->EvaluateSize)(this, LODWORD(evalTime), &size);
  ((void (__thiscall *)(rvSpriteParticle *, _DWORD, float *))this->EvaluateRotation)(this, LODWORD(evalTime), &evalTime);
  v30 = time - this->mMotionStartTime;
  rvParticle::EvaluatePosition(this, effect, &position, v30);
  v8 = &tri->verts[tri->numVerts];
  v9 = rvParticle::HandleTint(this, effect, &tint, override);
  y = effect->mSpriteSize.y;
  spriteSize.x = effect->mSpriteSize.x;
  spriteSize.y = y;
  if ( spriteSize.x > 0.00000011920929 || spriteSize.y > 0.00000011920929 )
  {
    v11 = effect->mSpriteSize.y;
    size.x = effect->mSpriteSize.x;
    size.y = v11;
  }
  c = cos(evalTime);
  s = sin(evalTime);
  v12 = s * view->mat[2].x;
  v13 = s * view->mat[2].y;
  v40 = s * view->mat[2].z;
  v14 = c * view->mat[1].x;
  left.y = c * view->mat[1].y;
  left.z = c * view->mat[1].z;
  v42 = v14 - v12;
  v15 = left.y - v13;
  v16 = left.z - v40;
  v17 = c * view->mat[2].x;
  v18 = c * view->mat[2].y;
  v36 = c * view->mat[2].z;
  v19 = s * view->mat[1].x;
  left.y = s * view->mat[1].y;
  left.z = s * view->mat[1].z;
  v38 = v19 + v17;
  v39 = left.y + v18;
  v40 = left.z + v36;
  left.x = size.x * v42;
  left.y = size.x * v15;
  v20 = size.x * v16;
  spriteSize.x = size.y * v38;
  spriteSize.y = size.y * v39;
  v36 = size.y * v40;
  v21 = position.x - left.x;
  v22 = position.y - left.y;
  v43 = position.z - v20;
  v8->xyz.z = v43;
  v8->xyz.x = v21;
  v23 = v8 + 1;
  v23[-1].xyz.y = v22;
  v23[-1].st.x = 0.0;
  v23[-1].st.y = 0.0;
  v23[-1].normal = position;
  *(_DWORD *)v23[-1].color = v9;
  v24 = position.x - spriteSize.x;
  v25 = position.y - spriteSize.y;
  v23 += 2;
  v43 = position.z - v36;
  v23[-2].xyz.z = v43;
  v23[-2].xyz.x = v24;
  v23[-2].xyz.y = v25;
  v23[-2].st.x = 1.0;
  v23[-2].st.y = 0.0;
  v23[-2].normal = position;
  *(_DWORD *)v23[-2].color = v9;
  v26 = position.x + left.x;
  v27 = position.y + left.y;
  v43 = position.z + v20;
  v23[-1].xyz.z = v43;
  v23[-1].xyz.x = v26;
  v23[-1].xyz.y = v27;
  v23[-1].st.x = 1.0;
  v23[-1].st.y = 1.0;
  v23[-1].normal = position;
  *(_DWORD *)v23[-1].color = v9;
  v43 = position.z + v36;
  v28 = position.x + spriteSize.x;
  v29 = position.y + spriteSize.y;
  v23->xyz.z = v43;
  v23->xyz.x = v28;
  v23->xyz.y = v29;
  v23->st.x = 0.0;
  v23->st.y = 1.0;
  v23->normal = position;
  *(_DWORD *)v23->color = v9;
  tri->indexes[tri->numIndexes] = tri->numVerts;
  tri->indexes[tri->numIndexes + 1] = tri->numVerts + 1;
  tri->indexes[tri->numIndexes + 2] = tri->numVerts + 2;
  tri->indexes[tri->numIndexes + 3] = tri->numVerts;
  tri->indexes[tri->numIndexes + 4] = tri->numVerts + 2;
  tri->indexes[tri->numIndexes + 5] = tri->numVerts + 3;
  tri->numVerts += 4;
  tri->numIndexes += 6;
  return 1;
}

// FUNC: public: virtual bool __thiscall rvLineParticle::Render(class rvBSE const *,class idMat3 const &,struct srfTriangles_s *,float,float)
char __thiscall rvLineParticle::Render(
        rvLineParticle *this,
        const rvBSE *effect,
        const idMat3 *view,
        srfTriangles_s *tri,
        float time,
        float override)
{
  float v8; // esi
  int mFlags; // eax
  double v10; // st7
  double v11; // st6
  long double v12; // st7
  long double v13; // st7
  long double v14; // st7
  idDrawVert *v15; // esi
  int v16; // eax
  double v17; // st7
  double v18; // st6
  double y; // st6
  double x; // st6
  double v21; // st6
  idDrawVert *v22; // esi
  double v23; // st5
  double v24; // st4
  double v25; // st5
  double v26; // st4
  double v27; // st4
  double v28; // st4
  double v29; // st3
  double v30; // st3
  double v31; // st7
  double v32; // st6
  double v33; // st5
  float v34; // [esp+10h] [ebp-BCh]
  float v35; // [esp+10h] [ebp-BCh]
  idVec3 len; // [esp+24h] [ebp-A8h] BYREF
  idVec3 velocity; // [esp+30h] [ebp-9Ch] BYREF
  idVec3 position; // [esp+3Ch] [ebp-90h] BYREF
  idVec3 offset; // [esp+48h] [ebp-84h]
  float evalTime; // [esp+54h] [ebp-78h] BYREF
  float v41; // [esp+58h] [ebp-74h]
  float v42; // [esp+64h] [ebp-68h]
  float v43; // [esp+6Ch] [ebp-60h]
  float v44; // [esp+70h] [ebp-5Ch]
  float v45[9]; // [esp+74h] [ebp-58h] BYREF
  float v46[9]; // [esp+98h] [ebp-34h] BYREF
  idVec4 tint; // [esp+BCh] [ebp-10h] BYREF

  evalTime = time - this->mStartTime;
  if ( this->mEndTime - 0.0020000001 <= time )
    evalTime = this->mEndTime - this->mStartTime - 0.0020000001;
  if ( this->mStartTime - 0.0020000001 >= time || time >= (double)this->mEndTime )
    return 0;
  v8 = evalTime;
  rvEnvParms3::Evaluate(&this->mTintEnv, evalTime, &tint.x);
  rvEnvParms1::Evaluate(&this->mFadeEnv, evalTime, &tint.w);
  ((void (__thiscall *)(rvLineParticle *, _DWORD, float *))this->EvaluateSize)(this, LODWORD(evalTime), &evalTime);
  ((void (__thiscall *)(rvLineParticle *, _DWORD, idVec3 *))this->EvaluateLength)(this, LODWORD(v8), &len);
  v34 = time - this->mMotionStartTime;
  rvParticle::EvaluatePosition(this, effect, &position, v34);
  mFlags = this->mFlags;
  if ( (mFlags & 2) == 0 )
  {
    v46[0] = this->mInitAxis.mat[0].y * effect->mCurrentAxis.mat[0].y
           + this->mInitAxis.mat[0].x * effect->mCurrentAxis.mat[0].x
           + effect->mCurrentAxis.mat[0].z * this->mInitAxis.mat[0].z;
    v46[1] = this->mInitAxis.mat[0].x * effect->mCurrentAxis.mat[1].x
           + effect->mCurrentAxis.mat[1].z * this->mInitAxis.mat[0].z
           + this->mInitAxis.mat[0].y * effect->mCurrentAxis.mat[1].y;
    v46[2] = effect->mCurrentAxis.mat[2].z * this->mInitAxis.mat[0].z
           + this->mInitAxis.mat[0].x * effect->mCurrentAxis.mat[2].x
           + effect->mCurrentAxis.mat[2].y * this->mInitAxis.mat[0].y;
    v46[3] = this->mInitAxis.mat[1].z * effect->mCurrentAxis.mat[0].z
           + this->mInitAxis.mat[1].x * effect->mCurrentAxis.mat[0].x
           + this->mInitAxis.mat[1].y * effect->mCurrentAxis.mat[0].y;
    v46[4] = this->mInitAxis.mat[1].z * effect->mCurrentAxis.mat[1].z
           + this->mInitAxis.mat[1].y * effect->mCurrentAxis.mat[1].y
           + this->mInitAxis.mat[1].x * effect->mCurrentAxis.mat[1].x;
    v46[5] = this->mInitAxis.mat[1].x * effect->mCurrentAxis.mat[2].x
           + effect->mCurrentAxis.mat[2].z * this->mInitAxis.mat[1].z
           + effect->mCurrentAxis.mat[2].y * this->mInitAxis.mat[1].y;
    v46[6] = this->mInitAxis.mat[2].z * effect->mCurrentAxis.mat[0].z
           + this->mInitAxis.mat[2].x * effect->mCurrentAxis.mat[0].x
           + this->mInitAxis.mat[2].y * effect->mCurrentAxis.mat[0].y;
    v46[7] = this->mInitAxis.mat[2].z * effect->mCurrentAxis.mat[1].z
           + this->mInitAxis.mat[2].y * effect->mCurrentAxis.mat[1].y
           + this->mInitAxis.mat[2].x * effect->mCurrentAxis.mat[1].x;
    v46[8] = this->mInitAxis.mat[2].x * effect->mCurrentAxis.mat[2].x
           + effect->mCurrentAxis.mat[2].z * this->mInitAxis.mat[2].z
           + effect->mCurrentAxis.mat[2].y * this->mInitAxis.mat[2].y;
    qmemcpy(v45, v46, sizeof(v45));
    v10 = v45[0] * len.x + len.z * v45[6] + len.y * v45[3];
    v11 = v45[1] * len.x + v45[7] * len.z + v45[4] * len.y;
    len.z = v45[2] * len.x + v45[8] * len.z + v45[5] * len.y;
    len.x = v10;
    len.y = v11;
  }
  if ( (mFlags & 0x10000) != 0 )
  {
    v35 = time - this->mMotionStartTime;
    rvParticle::EvaluateVelocity(this, effect, &velocity, v35);
    v12 = velocity.x * velocity.x + velocity.z * velocity.z + velocity.y * velocity.y;
    if ( v12 != 0.0 )
    {
      v13 = 1.0 / sqrt(v12);
      velocity.x = velocity.x * v13;
      velocity.y = velocity.y * v13;
      velocity.z = velocity.z * v13;
    }
    v14 = sqrt(len.x * len.x + len.z * len.z + len.y * len.y);
    v44 = velocity.z * v14;
    len.z = v44;
    len.x = velocity.x * v14;
    len.y = velocity.y * v14;
  }
  v15 = &tri->verts[tri->numVerts];
  v16 = rvParticle::HandleTint(this, effect, &tint, override);
  v17 = position.x + len.x;
  v43 = position.y + len.y;
  v44 = position.z + len.z;
  offset.z = len.z * 0.5;
  velocity.x = len.x * 0.5 + position.x;
  offset.x = view->mat[0].x - velocity.x;
  offset.y = view->mat[0].y - (len.y * 0.5 + position.y);
  v18 = view->mat[0].z - (offset.z + position.z);
  velocity.x = len.y * v18 - offset.y * len.z;
  velocity.y = len.z * offset.x - v18 * len.x;
  y = offset.y;
  offset.y = velocity.y;
  velocity.z = y * len.x - len.y * offset.x;
  x = velocity.x;
  offset.z = velocity.z;
  v41 = velocity.z * velocity.z + velocity.y * velocity.y + velocity.x * velocity.x;
  if ( v41 != 0.0 )
  {
    v41 = 1.0 / sqrt(v41);
    x = velocity.x * v41;
    offset.y = velocity.y * v41;
    offset.z = velocity.z * v41;
  }
  v21 = x * evalTime;
  v22 = v15 + 3;
  offset.y = offset.y * evalTime;
  offset.z = offset.z * evalTime;
  v23 = position.x + v21;
  v24 = offset.y + position.y;
  v42 = offset.z + position.z;
  v22[-3].xyz.z = v42;
  v22[-3].xyz.x = v23;
  v22[-3].xyz.y = v24;
  v22[-3].st.x = 0.0;
  v22[-3].st.y = 0.0;
  v22[-3].normal = position;
  *(_DWORD *)v22[-3].color = v16;
  v25 = position.x - v21;
  v26 = position.y - offset.y;
  v42 = position.z - offset.z;
  v22[-2].xyz.z = v42;
  v22[-2].xyz.x = v25;
  v22[-2].xyz.y = v26;
  v22[-2].st.x = 0.0;
  v22[-2].st.y = 1.0;
  v27 = v43;
  v22[-2].normal.x = position.x;
  v28 = v27 - offset.y;
  v29 = v44;
  v22[-2].normal.y = position.y;
  v30 = v29 - offset.z;
  v22[-2].normal.z = position.z;
  *(_DWORD *)v22[-2].color = v16;
  v42 = v30;
  v22[-1].xyz.z = v42;
  v22[-1].xyz.x = v17 - v21;
  v22[-1].xyz.y = v28;
  v22[-1].st.x = this->mTextureScale;
  v22[-1].st.y = 1.0;
  v31 = v17 + v21;
  v32 = offset.y + v43;
  v22[-1].normal.x = position.x;
  v33 = offset.z + v44;
  v22[-1].normal.y = position.y;
  v22[-1].normal.z = position.z;
  *(_DWORD *)v22[-1].color = v16;
  v42 = v33;
  v22->xyz.z = v42;
  v22->xyz.x = v31;
  v22->xyz.y = v32;
  v22->st.x = this->mTextureScale;
  v22->st.y = 0.0;
  v22->normal = position;
  *(_DWORD *)v22->color = v16;
  tri->indexes[tri->numIndexes] = tri->numVerts;
  tri->indexes[tri->numIndexes + 1] = tri->numVerts + 1;
  tri->indexes[tri->numIndexes + 2] = tri->numVerts + 2;
  tri->indexes[tri->numIndexes + 3] = tri->numVerts;
  tri->indexes[tri->numIndexes + 4] = tri->numVerts + 2;
  tri->indexes[tri->numIndexes + 5] = tri->numVerts + 3;
  tri->numVerts += 4;
  tri->numIndexes += 6;
  return 1;
}

// FUNC: public: virtual bool __thiscall rvOrientedParticle::Render(class rvBSE const *,class idMat3 const &,struct srfTriangles_s *,float,float)
char __thiscall rvOrientedParticle::Render(
        rvOrientedParticle *this,
        const rvBSE *effect,
        const idMat3 *view,
        srfTriangles_s *tri,
        float time,
        float override)
{
  float v8; // esi
  idDrawVert *v9; // esi
  int v10; // eax
  double v11; // st7
  double v12; // st6
  double v13; // st7
  double v14; // st6
  double v15; // st7
  double v16; // st6
  double v17; // st7
  float v18; // [esp+10h] [ebp-98h]
  idVec3 position; // [esp+24h] [ebp-84h] BYREF
  float evalTime; // [esp+30h] [ebp-78h] BYREF
  float v21; // [esp+34h] [ebp-74h]
  float v22; // [esp+38h] [ebp-70h]
  float v23; // [esp+3Ch] [ebp-6Ch]
  float v24; // [esp+40h] [ebp-68h]
  float v25; // [esp+44h] [ebp-64h]
  float v26; // [esp+48h] [ebp-60h]
  float v27; // [esp+4Ch] [ebp-5Ch]
  float v28; // [esp+58h] [ebp-50h]
  idVec3 rotation; // [esp+5Ch] [ebp-4Ch] BYREF
  rvAngles angles; // [esp+68h] [ebp-40h] BYREF
  idMat3 transform; // [esp+74h] [ebp-34h] BYREF
  idVec4 tint; // [esp+98h] [ebp-10h] BYREF

  evalTime = time - this->mStartTime;
  if ( this->mEndTime - 0.0020000001 <= time )
    evalTime = this->mEndTime - this->mStartTime - 0.0020000001;
  if ( this->mStartTime - 0.0020000001 >= time || time >= (double)this->mEndTime )
    return 0;
  v8 = evalTime;
  rvEnvParms3::Evaluate(&this->mTintEnv, evalTime, &tint.x);
  rvEnvParms1::Evaluate(&this->mFadeEnv, evalTime, &tint.w);
  ((void (__thiscall *)(rvOrientedParticle *, _DWORD, float *))this->EvaluateSize)(this, LODWORD(evalTime), &evalTime);
  ((void (__thiscall *)(rvOrientedParticle *, _DWORD, idVec3 *))this->EvaluateRotation)(this, LODWORD(v8), &rotation);
  v18 = time - this->mMotionStartTime;
  rvParticle::EvaluatePosition(this, effect, &position, v18);
  angles = (rvAngles)rotation;
  rvAngles::ToMat3(&angles, &transform);
  v9 = &tri->verts[tri->numVerts];
  v24 = -transform.mat[1].z;
  v25 = evalTime * -transform.mat[1].x;
  v26 = evalTime * -transform.mat[1].y;
  v27 = evalTime * v24;
  v22 = transform.mat[2].x * v21;
  v23 = transform.mat[2].y * v21;
  v24 = transform.mat[2].z * v21;
  v10 = rvParticle::HandleTint(this, effect, &tint, override);
  v11 = position.x - v25;
  v9 += 2;
  v12 = position.y - v26;
  v28 = position.z - v27;
  v9[-2].xyz.z = v28;
  v9[-2].xyz.x = v11;
  ++v9;
  v9[-3].xyz.y = v12;
  v9[-3].st.x = 0.0;
  v9[-3].st.y = 0.0;
  v9[-3].normal = position;
  *(_DWORD *)v9[-3].color = v10;
  v13 = position.x - v22;
  v14 = position.y - v23;
  v28 = position.z - v24;
  v9[-2].xyz.z = v28;
  v9[-2].xyz.x = v13;
  v9[-2].xyz.y = v14;
  v9[-2].st.x = 1.0;
  v9[-2].st.y = 0.0;
  v9[-2].normal = position;
  *(_DWORD *)v9[-2].color = v10;
  v15 = position.x + v25;
  v16 = position.y + v26;
  v28 = position.z + v27;
  v9[-1].xyz.z = v28;
  v9[-1].xyz.x = v15;
  v9[-1].xyz.y = v16;
  v9[-1].st.x = 1.0;
  v9[-1].st.y = 1.0;
  v9[-1].normal = position;
  *(_DWORD *)v9[-1].color = v10;
  v28 = position.z + v24;
  v17 = position.y + v23;
  v9->xyz.x = position.x + v22;
  v9->xyz.y = v17;
  v9->xyz.z = v28;
  v9->st.x = 0.0;
  v9->st.y = 1.0;
  v9->normal = position;
  *(_DWORD *)v9->color = v10;
  tri->indexes[tri->numIndexes] = tri->numVerts;
  tri->indexes[tri->numIndexes + 1] = tri->numVerts + 1;
  tri->indexes[tri->numIndexes + 2] = tri->numVerts + 2;
  tri->indexes[tri->numIndexes + 3] = tri->numVerts;
  tri->indexes[tri->numIndexes + 4] = tri->numVerts + 2;
  tri->indexes[tri->numIndexes + 5] = tri->numVerts + 3;
  tri->numVerts += 4;
  tri->numIndexes += 6;
  return 1;
}

// FUNC: public: virtual bool __thiscall rvModelParticle::Render(class rvBSE const *,class idMat3 const &,struct srfTriangles_s *,float,float)
// local variable allocation has failed, the output may be wrong!
char __userpurge rvModelParticle::Render@<al>(
        rvModelParticle *this@<ecx>,
        int a2@<edi>,
        const rvBSE *effect,
        const idMat3 *view,
        srfTriangles_s *tri,
        float time,
        float override,
        float alpha)
{
  float v10; // eax
  float v11; // ebx
  idVec3 *v12; // ecx
  int v13; // edx
  double x; // st7
  int v15; // eax
  double z; // st6
  double y; // st5
  const modelSurface_s *v18; // eax
  const modelSurface_s *v19; // ebp
  srfTriangles_s *geometry; // eax
  rvMesh *primBatchMesh; // edi
  int numIndexes; // ecx
  int verts; // ebx
  idDrawVert *v24; // esi
  bool v25; // cc
  double v26; // st7
  int v27; // eax
  double v28; // st6
  double v29; // st7
  double v30; // st6
  srfTriangles_s *v31; // ecx
  int i; // eax
  idDrawVert *v33; // [esp-4h] [ebp-104h]
  int *v34; // [esp+0h] [ebp-100h]
  int numVerts; // [esp+10h] [ebp-F0h]
  float v36; // [esp+14h] [ebp-ECh]
  unsigned __int8 colorAdd[4]; // [esp+24h] [ebp-DCh] BYREF
  idVec3 size; // [esp+28h] [ebp-D8h] BYREF
  idMat3 transform; // [esp+34h] [ebp-CCh] BYREF
  idVec3 position; // [esp+58h] [ebp-A8h] BYREF
  int t; // [esp+64h] [ebp-9Ch]
  rvAngles rotation; // [esp+68h] [ebp-98h] BYREF
  idVec3 rot; // [esp+74h] [ebp-8Ch] BYREF
  float v44[3]; // [esp+80h] [ebp-80h]
  idMat4 v45; // [esp+8Ch] [ebp-74h] BYREF
  _BYTE v46[45]; // [esp+D0h] [ebp-30h] OVERLAPPED BYREF

  *(float *)colorAdd = time - this->mStartTime;
  if ( this->mEndTime - 0.0020000001 <= time )
    *(float *)colorAdd = this->mEndTime - this->mStartTime - 0.0020000001;
  if ( this->mStartTime - 0.0020000001 >= time || time >= (double)this->mEndTime || !this->mModel )
    return 0;
  rvEnvParms3::Evaluate(&this->mTintEnv, *(float *)colorAdd, (float *)&v46[32]);
  rvEnvParms1::Evaluate(&this->mFadeEnv, *(float *)colorAdd, (float *)&v46[44]);
  ((void (__thiscall *)(rvModelParticle *, _DWORD, idVec3 *, int))this->EvaluateSize)(
    this,
    *(_DWORD *)colorAdd,
    &size,
    a2);
  ((void (__thiscall *)(rvModelParticle *, _DWORD, float *))this->EvaluateRotation)(this, *(_DWORD *)colorAdd, &rot.y);
  v36 = override - this->mMotionStartTime;
  rvParticle::EvaluatePosition(this, (const rvBSE *)view, (idVec3 *)&position.y, v36);
  v10 = COERCE_FLOAT(rvParticle::HandleTint(this, (const rvBSE *)view, (idVec4 *)&v46[36], alpha));
  rotation.yaw = rot.y;
  v11 = v10;
  rotation.pitch = v10;
  rotation.roll = rot.z;
  rot.x = v44[0];
  rvAngles::ToMat3((rvAngles *)&rotation.yaw, (idMat3 *)&transform.mat[0].y);
  if ( (this->mFlags & 2) == 0 )
  {
    *(float *)v46 = this->mInitAxis.mat[0].z * view[7].mat[0].z
                  + view[7].mat[0].y * this->mInitAxis.mat[0].y
                  + this->mInitAxis.mat[0].x * view[7].mat[0].x;
    *(float *)&v46[4] = this->mInitAxis.mat[0].z * view[7].mat[1].z
                      + this->mInitAxis.mat[0].y * view[7].mat[1].y
                      + view[7].mat[1].x * this->mInitAxis.mat[0].x;
    *(float *)&v46[8] = this->mInitAxis.mat[0].z * view[7].mat[2].z
                      + view[7].mat[2].y * this->mInitAxis.mat[0].y
                      + view[7].mat[2].x * this->mInitAxis.mat[0].x;
    *(float *)&v46[12] = view[7].mat[0].y * this->mInitAxis.mat[1].y
                       + this->mInitAxis.mat[1].x * view[7].mat[0].x
                       + this->mInitAxis.mat[1].z * view[7].mat[0].z;
    *(float *)&v46[16] = this->mInitAxis.mat[1].x * view[7].mat[1].x
                       + this->mInitAxis.mat[1].z * view[7].mat[1].z
                       + this->mInitAxis.mat[1].y * view[7].mat[1].y;
    *(float *)&v46[20] = view[7].mat[2].z * this->mInitAxis.mat[1].z
                       + view[7].mat[2].y * this->mInitAxis.mat[1].y
                       + view[7].mat[2].x * this->mInitAxis.mat[1].x;
    *(float *)&v46[24] = view[7].mat[0].y * this->mInitAxis.mat[2].y
                       + this->mInitAxis.mat[2].x * view[7].mat[0].x
                       + this->mInitAxis.mat[2].z * view[7].mat[0].z;
    *(float *)&v46[28] = this->mInitAxis.mat[2].x * view[7].mat[1].x
                       + this->mInitAxis.mat[2].z * view[7].mat[1].z
                       + this->mInitAxis.mat[2].y * view[7].mat[1].y;
    *(float *)&v46[32] = view[7].mat[2].z * this->mInitAxis.mat[2].z
                       + view[7].mat[2].y * this->mInitAxis.mat[2].y
                       + view[7].mat[2].x * this->mInitAxis.mat[2].x;
    qmemcpy(&v45.mat[0].y, v46, 0x24u);
    v12 = &transform.mat[1];
    v13 = 3;
    do
    {
      x = v12->x;
      v15 = 0;
      z = v12[-1].z;
      y = v12[-1].y;
      do
      {
        ++v15;
        v44[v15] = y * *(float *)((char *)&v45.mat[0].x + v15 * 4)
                 + x * *(float *)((char *)&v45.mat[1].z + v15 * 4)
                 + z * *(float *)((char *)&v45.mat[0].w + v15 * 4);
      }
      while ( v15 < 3 );
      v12[-1].y = v44[1];
      v12[-1].z = v44[2];
      v12->x = v45.mat[0].x;
      ++v12;
      --v13;
    }
    while ( v13 );
  }
  v18 = this->mModel->Surface(this->mModel, 0);
  v19 = v18;
  if ( v18 )
  {
    geometry = v18->geometry;
    primBatchMesh = geometry->primBatchMesh;
    if ( primBatchMesh )
    {
      v45.mat[0].w = position.x;
      transform.mat[0].x = transform.mat[0].x * size.x;
      v45.mat[1].w = position.y;
      *(_WORD *)colorAdd = LOWORD(v11);
      memset(&v45.mat[3], 0, 12);
      transform.mat[0].y = transform.mat[0].y * size.y;
      v45.mat[3].w = 1.0;
      transform.mat[0].z = transform.mat[0].z * size.z;
      transform.mat[1].x = transform.mat[1].x * size.x;
      transform.mat[1].y = transform.mat[1].y * size.y;
      v45.mat[1].y = transform.mat[1].y;
      v45.mat[2].x = transform.mat[0].z;
      transform.mat[1].z = transform.mat[1].z * size.z;
      v45.mat[2].w = position.z;
      transform.mat[2].x = transform.mat[2].x * size.x;
      transform.mat[2].y = transform.mat[2].y * size.y;
      v45.mat[1].z = transform.mat[2].y;
      v45.mat[2].y = transform.mat[1].z;
      transform.mat[2].z = transform.mat[2].z * size.z;
      v45.mat[2].z = transform.mat[2].z;
      v45.mat[0].x = transform.mat[0].x;
      colorAdd[2] = BYTE2(v11);
      v45.mat[0].y = transform.mat[1].x;
      numVerts = tri->numVerts;
      v45.mat[0].z = transform.mat[2].x;
      numIndexes = tri->numIndexes;
      v45.mat[1].x = transform.mat[0].y;
      v34 = &tri->indexes[numIndexes];
      v33 = &tri->verts[numVerts];
      colorAdd[3] = HIBYTE(v11);
      rvMesh::TransformTriangles(primBatchMesh, v33, v34, &v45, 32, colorAdd, numVerts);
      tri->numVerts += primBatchMesh->m_numDrawVertices;
      tri->numIndexes += primBatchMesh->m_numDrawIndices;
      return 1;
    }
    verts = (int)geometry->verts;
    v24 = &tri->verts[tri->numVerts];
    v25 = geometry->numVerts <= 0;
    *(float *)colorAdd = 0.0;
    if ( !v25 )
    {
      do
      {
        idDrawVert::operator=(v24, verts);
        *(_DWORD *)v24->color = t;
        v26 = transform.mat[0].x * v24->xyz.x;
        v28 = transform.mat[2].x * v24->xyz.z;
        verts += 64;
        ++v24;
        v27 = ++*(_DWORD *)colorAdd;
        v29 = v26 + v28 + transform.mat[1].x * v24[-1].xyz.y;
        v30 = transform.mat[0].y * v24[-1].xyz.x
            + transform.mat[2].y * v24[-1].xyz.z
            + transform.mat[1].y * v24[-1].xyz.y;
        v24[-1].xyz.z = transform.mat[0].z * v24[-1].xyz.x
                      + transform.mat[2].z * v24[-1].xyz.z
                      + transform.mat[1].z * v24[-1].xyz.y;
        v24[-1].xyz.x = v29;
        v24[-1].xyz.y = v30;
        v24[-1].xyz.x = size.x * v24[-1].xyz.x;
        v24[-1].xyz.y = size.y * v24[-1].xyz.y;
        v24[-1].xyz.z = size.z * v24[-1].xyz.z;
        v24[-1].xyz.x = position.x + v24[-1].xyz.x;
        v24[-1].xyz.y = position.y + v24[-1].xyz.y;
        v24[-1].xyz.z = position.z + v24[-1].xyz.z;
      }
      while ( v27 < v19->geometry->numVerts );
    }
    v31 = v19->geometry;
    for ( i = 0; i < v31->numIndexes; ++i )
    {
      tri->indexes[i + tri->numIndexes] = tri->numVerts + v31->indexes[i];
      v31 = v19->geometry;
    }
    tri->numVerts += v19->geometry->numVerts;
    tri->numIndexes += v19->geometry->numIndexes;
  }
  return 1;
}

// FUNC: public: virtual bool __thiscall rvLinkedParticle::Render(class rvBSE const *,class idMat3 const &,struct srfTriangles_s *,float,float)
char __thiscall rvLinkedParticle::Render(
        rvLinkedParticle *this,
        const rvBSE *effect,
        const idMat3 *view,
        srfTriangles_s *tri,
        float time,
        float override)
{
  int numVerts; // esi
  idDrawVert *v9; // esi
  int v10; // eax
  double v11; // st7
  double v12; // st6
  double v13; // st7
  double v14; // st6
  int v15; // eax
  float v16; // [esp+8h] [ebp-50h]
  float evalTime[2]; // [esp+1Ch] [ebp-3Ch] BYREF
  idVec3 position; // [esp+24h] [ebp-34h] BYREF
  float v19; // [esp+30h] [ebp-28h]
  float v20; // [esp+34h] [ebp-24h]
  float v21; // [esp+38h] [ebp-20h]
  float v22; // [esp+44h] [ebp-14h]
  idVec4 tint; // [esp+48h] [ebp-10h] BYREF

  evalTime[0] = time - this->mStartTime;
  if ( this->mEndTime - 0.0020000001 <= time )
    evalTime[0] = this->mEndTime - this->mStartTime - 0.0020000001;
  if ( this->mStartTime - 0.0020000001 >= time || time >= (double)this->mEndTime )
    return 0;
  rvEnvParms3::Evaluate(&this->mTintEnv, evalTime[0], &tint.x);
  rvEnvParms1::Evaluate(&this->mFadeEnv, evalTime[0], &tint.w);
  ((void (__thiscall *)(rvLinkedParticle *, _DWORD, float *))this->EvaluateSize)(this, LODWORD(evalTime[0]), evalTime);
  v16 = time - this->mMotionStartTime;
  rvParticle::EvaluatePosition(this, effect, &position, v16);
  numVerts = tri->numVerts;
  v19 = evalTime[0] * view->mat[1].x;
  v9 = &tri->verts[numVerts];
  v20 = evalTime[0] * view->mat[1].y;
  v21 = evalTime[0] * view->mat[1].z;
  v10 = rvParticle::HandleTint(this, effect, &tint, override);
  ++v9;
  v11 = position.x + v19;
  v12 = position.y + v20;
  v22 = position.z + v21;
  v9[-1].xyz.z = v22;
  v9[-1].xyz.x = v11;
  v9[-1].xyz.y = v12;
  v9[-1].st.x = this->mFraction * this->mTextureScale;
  v9[-1].st.y = 0.0;
  v9[-1].normal = position;
  *(_DWORD *)v9[-1].color = v10;
  v13 = position.x - v19;
  v14 = position.y - v20;
  v22 = position.z - v21;
  v9->xyz.z = v22;
  v9->xyz.x = v13;
  v9->xyz.y = v14;
  v9->st.x = this->mFraction * this->mTextureScale;
  v9->st.y = 1.0;
  v9->normal = position;
  *(_DWORD *)v9->color = v10;
  v15 = tri->numVerts;
  if ( v15 > 0 )
  {
    tri->indexes[tri->numIndexes] = v15 - 2;
    tri->indexes[tri->numIndexes + 1] = tri->numVerts - 1;
    tri->indexes[tri->numIndexes + 2] = tri->numVerts;
    tri->indexes[tri->numIndexes + 3] = tri->numVerts - 1;
    tri->indexes[tri->numIndexes + 4] = tri->numVerts + 1;
    tri->indexes[tri->numIndexes + 5] = tri->numVerts;
    tri->numIndexes += 6;
  }
  tri->numVerts += 2;
  return 1;
}
