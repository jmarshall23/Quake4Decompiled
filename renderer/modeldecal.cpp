
// FUNC: public: static void __cdecl idRenderModelDecal::Free(class idRenderModelDecal *)
void __cdecl idRenderModelDecal::Free(idRenderModelDecal *decal)
{
  --idRenderModelDecal::allocatedDecalCount;
  if ( decal )
    Memory::Free(decal);
}

// FUNC: public: static void __cdecl idRenderModelDecal::GlobalProjectionInfoToLocal(struct decalProjectionInfo_s &,struct decalProjectionInfo_s const &,class idVec3 const &,class idMat3 const &)
void __cdecl idRenderModelDecal::GlobalProjectionInfoToLocal(
        decalProjectionInfo_s *localInfo,
        const decalProjectionInfo_s *info,
        const idVec3 *origin,
        const idMat3 *axis)
{
  int v4; // eax
  idPlane *boundingPlanes; // ebp
  double v6; // st7
  double v7; // st6
  double z; // st7
  double v9; // st6
  double v10; // st5
  double y; // st4
  double v12; // st3
  double v13; // st2
  float v14; // eax
  int v15; // [esp+10h] [ebp-78h]
  float x; // [esp+10h] [ebp-78h]
  float v17; // [esp+20h] [ebp-68h]
  idMat3 v18; // [esp+24h] [ebp-64h] BYREF
  float modelMatrix[16]; // [esp+48h] [ebp-40h] BYREF

  R_AxisToModelMatrix(axis, origin, modelMatrix);
  v4 = (char *)localInfo - (char *)info;
  boundingPlanes = info->boundingPlanes;
  v15 = 6;
  while ( 1 )
  {
    R_GlobalPlaneToLocal(modelMatrix, boundingPlanes, (idPlane *)((char *)boundingPlanes + v4));
    ++boundingPlanes;
    if ( !--v15 )
      break;
    v4 = (char *)localInfo - (char *)info;
  }
  R_GlobalPlaneToLocal(modelMatrix, info->fadePlanes, localInfo->fadePlanes);
  R_GlobalPlaneToLocal(modelMatrix, &info->fadePlanes[1], &localInfo->fadePlanes[1]);
  R_GlobalPlaneToLocal(modelMatrix, info->textureAxis, localInfo->textureAxis);
  R_GlobalPlaneToLocal(modelMatrix, &info->textureAxis[1], &localInfo->textureAxis[1]);
  R_GlobalPointToLocal(modelMatrix, &info->projectionOrigin, &localInfo->projectionOrigin);
  localInfo->projectionBounds = info->projectionBounds;
  v6 = -origin->x;
  v7 = -origin->y;
  v17 = -origin->z;
  localInfo->projectionBounds.b[0].x = localInfo->projectionBounds.b[0].x - origin->x;
  localInfo->projectionBounds.b[0].y = v7 + localInfo->projectionBounds.b[0].y;
  localInfo->projectionBounds.b[0].z = v17 + localInfo->projectionBounds.b[0].z;
  localInfo->projectionBounds.b[1].x = v6 + localInfo->projectionBounds.b[1].x;
  localInfo->projectionBounds.b[1].y = v7 + localInfo->projectionBounds.b[1].y;
  localInfo->projectionBounds.b[1].z = v17 + localInfo->projectionBounds.b[1].z;
  z = axis->mat[2].z;
  x = axis->mat[1].x;
  v9 = axis->mat[1].z;
  v10 = axis->mat[0].z;
  y = axis->mat[2].y;
  v12 = axis->mat[1].y;
  v13 = axis->mat[0].y;
  v14 = axis->mat[0].x;
  v18.mat[0].z = axis->mat[2].x;
  v18.mat[1].x = v13;
  v18.mat[0].x = v14;
  v18.mat[1].y = v12;
  v18.mat[1].z = y;
  v18.mat[2].x = v10;
  v18.mat[0].y = x;
  v18.mat[2].y = v9;
  v18.mat[2].z = z;
  idBounds::FromTransformedBounds(&localInfo->projectionBounds, &localInfo->projectionBounds, &vec3_origin, &v18);
  localInfo->material = info->material;
  localInfo->parallel = info->parallel;
  localInfo->fadeDepth = info->fadeDepth;
  localInfo->startTime = info->startTime;
  localInfo->maxAngle = info->maxAngle;
  localInfo->force = info->force;
}

// FUNC: public: static class idRenderModelDecal * __cdecl idRenderModelDecal::Alloc(void)
idRenderModelDecal *__cdecl idRenderModelDecal::Alloc()
{
  _DWORD *v0; // edx
  idRenderModelDecal *result; // eax

  ++idRenderModelDecal::allocatedDecalCount;
  v0 = Memory::Allocate(0xDDCu);
  result = 0;
  if ( v0 )
  {
    memset(v0 + 1, 0, 0xB4u);
    v0[11] = v0 + 46;
    v0[15] = v0 + 726;
    *v0 = 0;
    v0[886] = 0;
    return (idRenderModelDecal *)v0;
  }
  return result;
}

// FUNC: public: static bool __cdecl idRenderModelDecal::CreateProjectionInfo(struct decalProjectionInfo_s &,class idFixedWinding const &,class idVec3 const &,bool,float,class idMaterial const *,int)
bool __cdecl idRenderModelDecal::CreateProjectionInfo(
        decalProjectionInfo_s *info,
        const idFixedWinding *winding,
        const idVec3 *projectionOrigin,
        bool parallel,
        float fadeDepth,
        const idMaterial *material,
        int startTime)
{
  bool result; // al
  float z; // edx
  idBounds *p_projectionBounds; // esi
  int v10; // edx
  int v11; // ecx
  idVec5 *p; // eax
  double v13; // st7
  idVec5 *v14; // eax
  idVec5 *v15; // eax
  double x; // st7
  idVec5 *v17; // eax
  double v18; // st7
  int v19; // eax
  int v20; // edi
  int v21; // ebp
  float *v22; // ecx
  idVec5 *v23; // esi
  int v24; // ebx
  float *p_x; // eax
  double v26; // st7
  double v27; // st6
  double v28; // st5
  long double v29; // st4
  long double v30; // st7
  unsigned __int8 v32; // c2
  unsigned __int8 v33; // c3
  idVec5 *v34; // eax
  double y; // st7
  float *v36; // eax
  double v37; // st7
  double v38; // st7
  double v39; // st6
  int numPoints; // ebp
  int v41; // edi
  float *p_b; // ecx
  idVec5 *v43; // esi
  int v44; // eax
  double v45; // st7
  idVec5 *v46; // eax
  double v47; // st7
  float *p_y; // edx
  double v49; // st6
  double v50; // st5
  double v51; // st4
  double v52; // st7
  long double v53; // st6
  long double v54; // st7
  long double v55; // st5
  unsigned __int8 v57; // c2
  unsigned __int8 v58; // c3
  float b; // edx
  float c; // esi
  float d; // edi
  float a; // eax
  double v63; // st6
  double v64; // st5
  double v65; // st5
  idVec5 *v66; // eax
  double v67; // st7
  double v68; // st6
  double v69; // st5
  double v70; // st5
  double v71; // st4
  long double v72; // st3
  long double v73; // st3
  long double v74; // rt1
  idVec5 *v75; // eax
  double v76; // st7
  double v77; // st6
  long double v78; // st5
  long double v79; // st5
  long double v80; // st3
  idVec5 *v81; // eax
  double v82; // st7
  float inva; // [esp+4h] [ebp-74h]
  float invaa; // [esp+4h] [ebp-74h]
  float v85; // [esp+8h] [ebp-70h]
  float v86; // [esp+8h] [ebp-70h]
  float v87; // [esp+8h] [ebp-70h]
  int temp; // [esp+Ch] [ebp-6Ch]
  float tempa; // [esp+Ch] [ebp-6Ch]
  float temp_4a; // [esp+10h] [ebp-68h]
  float temp_4; // [esp+10h] [ebp-68h]
  float temp_8; // [esp+14h] [ebp-64h]
  float temp_8a; // [esp+14h] [ebp-64h]
  float temp_8b; // [esp+14h] [ebp-64h]
  float v95; // [esp+18h] [ebp-60h]
  float v96; // [esp+18h] [ebp-60h]
  float v97; // [esp+1Ch] [ebp-5Ch]
  float v98; // [esp+1Ch] [ebp-5Ch]
  float v99; // [esp+20h] [ebp-58h]
  float transToProj; // [esp+24h] [ebp-54h]
  float transToProj_4; // [esp+28h] [ebp-50h]
  float transToProj_4a; // [esp+28h] [ebp-50h]
  float transToProj_8; // [esp+2Ch] [ebp-4Ch]
  float transToProj_8a; // [esp+2Ch] [ebp-4Ch]
  float transToFade; // [esp+30h] [ebp-48h]
  float transToFadea; // [esp+30h] [ebp-48h]
  float transToFadeb; // [esp+30h] [ebp-48h]
  float transToFadec; // [esp+30h] [ebp-48h]
  float transToFade_4; // [esp+34h] [ebp-44h]
  float transToFade_4b; // [esp+34h] [ebp-44h]
  float transToFade_4c; // [esp+34h] [ebp-44h]
  float transToFade_4a; // [esp+34h] [ebp-44h]
  float transToFade_8; // [esp+38h] [ebp-40h]
  float transToFade_8a; // [esp+38h] [ebp-40h]
  idPlane windingPlane; // [esp+40h] [ebp-38h] BYREF
  idVec5 d0; // [esp+50h] [ebp-28h]
  idVec5 d1; // [esp+64h] [ebp-14h]

  if ( winding->numPoints != 4 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idRenderModelDecal::CreateProjectionInfo: winding must have %d points\n",
      4);
    return 0;
  }
  temp_4a = material->decalInfo.maxAngle;
  info->projectionOrigin.x = projectionOrigin->x;
  info->projectionOrigin.y = projectionOrigin->y;
  z = projectionOrigin->z;
  info->material = material;
  info->fadeDepth = fadeDepth;
  info->projectionOrigin.z = z;
  info->parallel = parallel;
  info->startTime = startTime;
  info->maxAngle = temp_4a;
  info->force = 0;
  idWinding::GetPlane(&winding->idWinding, &windingPlane);
  p_projectionBounds = &info->projectionBounds;
  inva = windingPlane.a * projectionOrigin->x
       + windingPlane.b * projectionOrigin->y
       + windingPlane.c * projectionOrigin->z
       + windingPlane.d;
  idWinding::GetBounds(&winding->idWinding, &info->projectionBounds);
  if ( info->parallel )
  {
    v10 = 0;
    transToProj = windingPlane.a * inva;
    transToProj_4 = windingPlane.b * inva;
    transToProj_8 = windingPlane.c * inva;
    transToFade = windingPlane.a * fadeDepth;
    transToFade_4 = windingPlane.b * fadeDepth;
    transToFade_8 = windingPlane.c * fadeDepth;
    if ( winding->numPoints > 0 )
    {
      v11 = 0;
      do
      {
        p = winding->p;
        v13 = transToProj + p[v11].x;
        v14 = &p[v11];
        temp_4 = transToProj_4 + v14->y;
        temp_8 = transToProj_8 + v14->z;
        if ( v13 < p_projectionBounds->b[0].x )
          p_projectionBounds->b[0].x = v13;
        if ( v13 > info->projectionBounds.b[1].x )
          info->projectionBounds.b[1].x = v13;
        if ( temp_4 < (double)info->projectionBounds.b[0].y )
          info->projectionBounds.b[0].y = temp_4;
        if ( temp_4 > (double)info->projectionBounds.b[1].y )
          info->projectionBounds.b[1].y = temp_4;
        if ( temp_8 < (double)info->projectionBounds.b[0].z )
          info->projectionBounds.b[0].z = temp_8;
        if ( temp_8 > (double)info->projectionBounds.b[1].z )
          info->projectionBounds.b[1].z = temp_8;
        v15 = winding->p;
        x = v15[v11].x;
        v17 = &v15[v11];
        v18 = x - transToFade;
        v97 = v17->y - transToFade_4;
        v99 = v17->z - transToFade_8;
        if ( v18 < p_projectionBounds->b[0].x )
          p_projectionBounds->b[0].x = v18;
        if ( v18 > info->projectionBounds.b[1].x )
          info->projectionBounds.b[1].x = v18;
        if ( v97 < (double)info->projectionBounds.b[0].y )
          info->projectionBounds.b[0].y = v97;
        if ( v97 > (double)info->projectionBounds.b[1].y )
          info->projectionBounds.b[1].y = v97;
        if ( v99 < (double)info->projectionBounds.b[0].z )
          info->projectionBounds.b[0].z = v99;
        if ( v99 > (double)info->projectionBounds.b[1].z )
          info->projectionBounds.b[1].z = v99;
        ++v10;
        ++v11;
      }
      while ( v10 < winding->numPoints );
    }
  }
  else
  {
    if ( projectionOrigin->x < (double)p_projectionBounds->b[0].x )
      p_projectionBounds->b[0].x = projectionOrigin->x;
    if ( projectionOrigin->x > (double)info->projectionBounds.b[1].x )
      info->projectionBounds.b[1].x = projectionOrigin->x;
    if ( projectionOrigin->y < (double)info->projectionBounds.b[0].y )
      info->projectionBounds.b[0].y = projectionOrigin->y;
    if ( projectionOrigin->y > (double)info->projectionBounds.b[1].y )
      info->projectionBounds.b[1].y = projectionOrigin->y;
    if ( projectionOrigin->z < (double)info->projectionBounds.b[0].z )
      info->projectionBounds.b[0].z = projectionOrigin->z;
    if ( projectionOrigin->z > (double)info->projectionBounds.b[1].z )
      info->projectionBounds.b[1].z = projectionOrigin->z;
  }
  v19 = 0;
  if ( !info->parallel )
  {
    numPoints = winding->numPoints;
    if ( numPoints <= 0 )
      goto LABEL_125;
    v41 = 0;
    p_b = &info->boundingPlanes[0].b;
    while ( 1 )
    {
      v43 = winding->p;
      temp = v19 + 1;
      v44 = (v19 + 1) % numPoints;
      v45 = v43[v44].x;
      v46 = &v43[v44];
      v47 = v45 - v43[v41].x;
      p_y = &v43[v41].y;
      v49 = v46->y - *p_y;
      v50 = v46->z - v43[v41].z;
      transToFadea = projectionOrigin->x - v43[v41].x;
      transToFade_4b = projectionOrigin->y - *p_y;
      v51 = projectionOrigin->z - v43[v41].z;
      v95 = transToFade_4b * v50 - v51 * v49;
      *(p_b - 1) = v95;
      v98 = v51 * v47 - v50 * transToFadea;
      *p_b = v98;
      v52 = v49 * transToFadea - transToFade_4b * v47;
      p_b[1] = v52;
      v53 = v95 * v95 + v52 * v52 + v98 * v98;
      if ( v53 == 0.0 )
      {
        v54 = 0.0;
      }
      else
      {
        v55 = 1.0 / sqrt(v53);
        *(p_b - 1) = v95 * v55;
        *p_b = v98 * v55;
        p_b[1] = v52 * v55;
        v54 = v55 * v53;
      }
      if ( v58 | v57 )
      {
        if ( *p_b == 0.0 )
        {
          if ( p_b[1] <= 0.0 )
          {
            if ( *((_DWORD *)p_b + 1) != -1082130432 )
              p_b[1] = -1.0;
          }
          else if ( *((_DWORD *)p_b + 1) != 1065353216 )
          {
            p_b[1] = 1.0;
          }
          goto LABEL_122;
        }
        if ( p_b[1] == 0.0 )
        {
          if ( *p_b <= 0.0 )
          {
            if ( *(_DWORD *)p_b != -1082130432 )
              *p_b = -1.0;
          }
          else if ( *(_DWORD *)p_b != 1065353216 )
          {
            *p_b = 1.0;
          }
          goto LABEL_122;
        }
      }
      else if ( *p_b == 0.0 && p_b[1] == 0.0 )
      {
        if ( *(p_b - 1) <= 0.0 )
        {
          if ( *((_DWORD *)p_b - 1) != -1082130432 )
            *(p_b - 1) = -1.0;
        }
        else if ( *((_DWORD *)p_b - 1) != 1065353216 )
        {
          *(p_b - 1) = 1.0;
        }
        goto LABEL_122;
      }
      if ( COERCE_FLOAT(*(_DWORD *)(p_b - 1) & 0x7FFFFFFF) == 1.0 )
        break;
      if ( COERCE_FLOAT(*(_DWORD *)p_b & 0x7FFFFFFF) == 1.0 )
      {
        if ( *(p_b - 1) != 0.0 || p_b[1] != 0.0 )
        {
          p_b[1] = 0.0;
          *(p_b - 1) = 0.0;
        }
        goto LABEL_122;
      }
      if ( COERCE_FLOAT((_DWORD)p_b[1] & 0x7FFFFFFF) == 1.0 && (*(p_b - 1) != 0.0 || *p_b != 0.0) )
      {
        *(p_b - 1) = 0.0;
LABEL_121:
        *p_b = 0.0;
      }
LABEL_122:
      if ( v54 != 0.0 )
        p_b[2] = -(p_b[1] * v43[v41].z + *(p_b - 1) * v43[v41].x + *p_y * *p_b);
      v19 = temp;
      numPoints = winding->numPoints;
      ++v41;
      p_b += 4;
      if ( temp >= numPoints )
        goto LABEL_125;
    }
    if ( *p_b == 0.0 && p_b[1] == 0.0 )
      goto LABEL_122;
    p_b[1] = 0.0;
    goto LABEL_121;
  }
  v20 = winding->numPoints;
  if ( v20 > 0 )
  {
    v21 = 0;
    v22 = &info->boundingPlanes[0].b;
    while ( 1 )
    {
      v23 = winding->p;
      v24 = v19 + 1;
      p_x = &v23[(v19 + 1) % v20].x;
      v26 = *p_x - v23[v21].x;
      v27 = p_x[1] - v23[v21].y;
      v28 = p_x[2] - v23[v21].z;
      *(v22 - 1) = windingPlane.b * v28 - v27 * windingPlane.c;
      *v22 = windingPlane.c * v26 - v28 * windingPlane.a;
      v22[1] = v27 * windingPlane.a - windingPlane.b * v26;
      v29 = *(v22 - 1) * *(v22 - 1) + v22[1] * v22[1] + *v22 * *v22;
      if ( v29 != 0.0 )
      {
        v30 = 1.0 / sqrt(v29);
        *(v22 - 1) = v30 * *(v22 - 1);
        *v22 = v30 * *v22;
        v22[1] = v30 * v22[1];
      }
      if ( v33 | v32 )
      {
        if ( *v22 == 0.0 )
        {
          if ( v22[1] <= 0.0 )
          {
            if ( *((_DWORD *)v22 + 1) != -1082130432 )
              v22[1] = -1.0;
          }
          else if ( *((_DWORD *)v22 + 1) != 1065353216 )
          {
            v22[1] = 1.0;
          }
          goto LABEL_82;
        }
        if ( v22[1] == 0.0 )
        {
          if ( *v22 <= 0.0 )
          {
            if ( *(_DWORD *)v22 != -1082130432 )
              *v22 = -1.0;
          }
          else if ( *(_DWORD *)v22 != 1065353216 )
          {
            *v22 = 1.0;
          }
          goto LABEL_82;
        }
      }
      else if ( *v22 == 0.0 && v22[1] == 0.0 )
      {
        if ( *(v22 - 1) <= 0.0 )
        {
          if ( *((_DWORD *)v22 - 1) != -1082130432 )
            *(v22 - 1) = -1.0;
        }
        else if ( *((_DWORD *)v22 - 1) != 1065353216 )
        {
          *(v22 - 1) = 1.0;
        }
        goto LABEL_82;
      }
      if ( COERCE_FLOAT(*(_DWORD *)(v22 - 1) & 0x7FFFFFFF) == 1.0 )
        break;
      if ( COERCE_FLOAT(*(_DWORD *)v22 & 0x7FFFFFFF) == 1.0 )
      {
        if ( *(v22 - 1) != 0.0 || v22[1] != 0.0 )
        {
          v22[1] = 0.0;
          *(v22 - 1) = 0.0;
        }
        goto LABEL_82;
      }
      if ( COERCE_FLOAT((_DWORD)v22[1] & 0x7FFFFFFF) == 1.0 && (*(v22 - 1) != 0.0 || *v22 != 0.0) )
      {
        *(v22 - 1) = 0.0;
LABEL_81:
        *v22 = 0.0;
      }
LABEL_82:
      v34 = winding->p;
      y = v34[v21].y;
      v36 = &v34[v21].x;
      v37 = y * *v22;
      ++v21;
      v22 += 4;
      v38 = v37 + v36[2] * *(v22 - 3);
      v39 = *v36;
      v19 = v24;
      *(v22 - 2) = -(v38 + v39 * *(v22 - 5));
      v20 = winding->numPoints;
      if ( v24 >= v20 )
        goto LABEL_125;
    }
    if ( *v22 == 0.0 && v22[1] == 0.0 )
      goto LABEL_82;
    v22[1] = 0.0;
    goto LABEL_81;
  }
LABEL_125:
  b = windingPlane.b;
  c = windingPlane.c;
  d = windingPlane.d;
  a = windingPlane.a;
  info->boundingPlanes[4].a = windingPlane.a;
  info->boundingPlanes[4].b = b;
  info->boundingPlanes[4].c = c;
  info->boundingPlanes[4].d = d;
  info->boundingPlanes[4].d = info->boundingPlanes[4].d - inva;
  transToFadeb = -windingPlane.a;
  v63 = windingPlane.b;
  info->boundingPlanes[5].a = transToFadeb;
  transToFade_4c = -v63;
  v64 = windingPlane.c;
  info->boundingPlanes[5].b = transToFade_4c;
  tempa = -v64;
  v65 = windingPlane.d;
  info->boundingPlanes[5].c = tempa;
  v85 = -v65;
  info->boundingPlanes[5].d = v85;
  info->fadePlanes[0].a = a;
  info->fadePlanes[0].b = b;
  info->fadePlanes[0].c = c;
  info->fadePlanes[0].d = d;
  info->fadePlanes[0].d = info->fadePlanes[0].d - fadeDepth;
  info->fadePlanes[1].a = transToFadeb;
  info->fadePlanes[1].b = transToFade_4c;
  info->fadePlanes[1].c = tempa;
  info->fadePlanes[1].d = v85;
  info->fadePlanes[1].d = inva - fadeDepth + info->fadePlanes[1].d;
  v66 = winding->p;
  v67 = v66[1].x - v66->x;
  transToProj_4a = v66[1].y - v66->y;
  transToProj_8a = v66[1].z - v66->z;
  d0.s = v66[1].s - v66->s;
  d0.t = v66[1].t - v66->t;
  v68 = v66[2].x - v66->x;
  transToFade_4a = v66[2].y - v66->y;
  transToFade_8a = v66[2].z - v66->z;
  d1.s = v66[2].s - v66->s;
  v69 = v66[2].t - v66->t;
  d1.t = v69;
  invaa = 1.0 / (v69 * d0.s - d1.s * d0.t);
  v70 = (v67 * d1.t - v68 * d0.t) * invaa;
  v71 = (transToProj_4a * d1.t - transToFade_4a * d0.t) * invaa;
  temp_8a = (transToProj_8a * d1.t - transToFade_8a * d0.t) * invaa;
  v72 = v70 * v70 + temp_8a * temp_8a + v71 * v71;
  if ( v72 == 0.0 )
  {
    v73 = 0.0;
  }
  else
  {
    v74 = 1.0 / sqrt(v72);
    v70 = v70 * v74;
    v71 = v71 * v74;
    temp_8a = temp_8a * v74;
    v73 = v72 * v74;
  }
  v86 = 1.0 / v73;
  v96 = v86 * v70;
  info->textureAxis[0].a = v96;
  info->textureAxis[0].b = v71 * v86;
  info->textureAxis[0].c = temp_8a * v86;
  v75 = winding->p;
  info->textureAxis[0].d = v75->s
                         - (info->textureAxis[0].c * v75->z
                          + info->textureAxis[0].b * v75->y
                          + info->textureAxis[0].a * v75->x);
  v76 = (v68 * d0.s - v67 * d1.s) * invaa;
  v77 = (transToFade_4a * d0.s - transToProj_4a * d1.s) * invaa;
  temp_8b = (transToFade_8a * d0.s - transToProj_8a * d1.s) * invaa;
  v78 = v76 * v76 + temp_8b * temp_8b + v77 * v77;
  if ( v78 == 0.0 )
  {
    v79 = 0.0;
  }
  else
  {
    v80 = 1.0 / sqrt(v78);
    v76 = v76 * v80;
    v77 = v77 * v80;
    temp_8b = temp_8b * v80;
    v79 = v78 * v80;
  }
  v87 = 1.0 / v79;
  transToFadec = v87 * v76;
  info->textureAxis[1].a = transToFadec;
  info->textureAxis[1].b = v77 * v87;
  info->textureAxis[1].c = temp_8b * v87;
  v81 = winding->p;
  v82 = v81->t - (info->textureAxis[1].c * v81->z + info->textureAxis[1].b * v81->y + info->textureAxis[1].a * v81->x);
  result = 1;
  info->textureAxis[1].d = v82;
  return result;
}

// FUNC: private: void __thiscall idRenderModelDecal::AddWinding(class idWinding const &,class idMaterial const *,class idPlane const * const,float,int)
void __thiscall idRenderModelDecal::AddWinding(
        idRenderModelDecal *this,
        const idWinding *w,
        const idMaterial *decalMaterial,
        const idPlane *fadePlanes,
        float fadeDepth,
        int startTime)
{
  int numPoints; // eax
  int v8; // ecx
  int v9; // ebx
  idVec5 *v10; // ebp
  double v11; // st7
  idVec5 *p; // edx
  float x; // ebp
  idVec5 *v14; // edx
  idDrawVert *v15; // eax
  int v16; // eax
  int i; // eax
  float decalMateriala; // [esp+8h] [ebp+8h]
  float startTimea; // [esp+14h] [ebp+14h]

  startTimea = (float)startTime;
  while ( 1 )
  {
    if ( !this->material || this->material == decalMaterial )
    {
      numPoints = w->numPoints;
      if ( numPoints + this->tri.numVerts < 40 && this->tri.numIndexes + 3 * numPoints - 6 < 60 )
        break;
    }
    if ( !this->nextDecal )
      this->nextDecal = idRenderModelDecal::Alloc();
    this = this->nextDecal;
  }
  this->material = decalMaterial;
  ++AddCount;
  v8 = 0;
  decalMateriala = -1.0 / fadeDepth;
  if ( w->numPoints > 0 )
  {
    v9 = 0;
    do
    {
      v10 = &w->p[v9];
      v11 = (v10->y * fadePlanes->b + v10->z * fadePlanes->c + v10->x * fadePlanes->a + fadePlanes->d) * decalMateriala;
      if ( v11 >= 0.0
        || (v11 = (v10->z * fadePlanes[1].c + v10->y * fadePlanes[1].b + fadePlanes[1].a * v10->x + fadePlanes[1].d)
                * decalMateriala,
            v11 >= 0.0) )
      {
        if ( v11 > 0.99000001 )
          v11 = 1.0;
      }
      else
      {
        v11 = 0.0;
      }
      this->vertDepthFade[v8 + this->tri.numVerts] = 1.0 - v11;
      p = w->p;
      x = p[v9].x;
      v14 = &p[v9];
      v15 = &this->tri.verts[v8 + this->tri.numVerts];
      ++v9;
      v15->xyz.x = x;
      v15->xyz.y = v14->y;
      v15->xyz.z = v14->z;
      this->tri.verts[v8 + this->tri.numVerts].st.x = w->p[v9 - 1].s;
      this->tri.verts[v8 + this->tri.numVerts].st.y = w->p[v9 - 1].t;
      v16 = v8 + this->tri.numVerts;
      ++v8;
      this->vertLifeSpan[v16] = 0.0;
    }
    while ( v8 < w->numPoints );
  }
  for ( i = 2; i < w->numPoints; this->tri.numIndexes += 3 )
  {
    this->tri.indexes[this->tri.numIndexes] = this->tri.numVerts;
    this->tri.indexes[this->tri.numIndexes + 1] = i + this->tri.numVerts - 1;
    this->tri.indexes[this->tri.numIndexes + 2] = i + this->tri.numVerts;
    this->indexStartTime[this->tri.numIndexes + 2] = startTimea;
    ++i;
    this->indexStartTime[this->tri.numIndexes + 1] = startTimea;
    this->indexStartTime[this->tri.numIndexes] = startTimea;
  }
  this->tri.numVerts += w->numPoints;
}

// FUNC: public: void __thiscall idRenderModelDecal::AddDepthFadedWinding(class idWinding const &,class idMaterial const *,class idPlane const * const,float,int)
void __thiscall idRenderModelDecal::AddDepthFadedWinding(
        idRenderModelDecal *this,
        const idWinding *w,
        const idMaterial *decalMaterial,
        const idPlane *fadePlanes,
        float fadeDepth,
        int startTime)
{
  int numPoints; // eax
  int v7; // ecx
  int v8; // eax
  idVec5 *v9; // edx
  idVec5 *v10; // edi
  idFixedWinding front; // [esp+14h] [ebp-A2Ch] BYREF
  idFixedWinding back; // [esp+524h] [ebp-51Ch] BYREF
  int v14; // [esp+A3Ch] [ebp-4h]

  front.p = front.data;
  front.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  front.numPoints = 0;
  front.allocedSize = 64;
  v14 = 0;
  back.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  back.numPoints = 0;
  back.p = back.data;
  back.allocedSize = 64;
  numPoints = w->numPoints;
  LOBYTE(v14) = 1;
  if ( numPoints <= 64 || idFixedWinding::ReAllocate(&front, numPoints, 0) )
  {
    v7 = 0;
    if ( w->numPoints > 0 )
    {
      v8 = 0;
      do
      {
        v9 = &w->p[v8];
        v10 = &front.p[v8];
        v10->x = v9->x;
        v10->y = v9->y;
        v10->z = v9->z;
        v10->s = v9->s;
        ++v7;
        v10->t = v9->t;
        ++v8;
      }
      while ( v7 < w->numPoints );
    }
    front.numPoints = w->numPoints;
  }
  else
  {
    front.numPoints = 0;
  }
  if ( idFixedWinding::Split(&front, &back, fadePlanes, 0.1) == 3 )
    idRenderModelDecal::AddWinding(this, &back, decalMaterial, fadePlanes, fadeDepth, startTime);
  if ( idFixedWinding::Split(&front, &back, fadePlanes + 1, 0.1) == 3 )
    idRenderModelDecal::AddWinding(this, &back, decalMaterial, fadePlanes, fadeDepth, startTime);
  idRenderModelDecal::AddWinding(this, &front, decalMaterial, fadePlanes, fadeDepth, startTime);
  LOBYTE(v14) = 0;
  back.p = 0;
  back.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
  back.p = 0;
  v14 = -1;
  front.p = 0;
  front.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  Memory::Free(0);
}

// FUNC: public: void __thiscall idRenderModelDecal::CreateDecal(class idRenderModel const *,struct decalProjectionInfo_s const &)
void __thiscall idRenderModelDecal::CreateDecal(idRenderModelDecal *this, idRenderModel *model, float localInfo)
{
  const idRenderModel *ebx1; // ebx
  idRenderModel_vtbl *v4; // eax
  const decalProjectionInfo_s *v5; // esi
  int v6; // eax
  int v7; // edi
  int v8; // eax
  rvMesh *v9; // ecx
  int v10; // eax
  void *v11; // esp
  idSIMDProcessor_vtbl *v12; // eax
  _BYTE *p_fw; // ebx
  bool v14; // cc
  int v15; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  bool v20; // zf
  float *v21; // eax
  int v22; // eax
  float *v23; // eax
  int v24; // eax
  float *v25; // eax
  float *v26; // eax
  idVec5 *v27; // edx
  double v28; // st7
  double v29; // st6
  double v30; // st5
  double v31; // st7
  double v32; // st6
  double v33; // rtt
  double v34; // st6
  int v35; // eax
  char v36; // cl
  float *p_c; // ebx
  double v38; // st7
  double v39; // st6
  double v40; // st5
  idRenderModel_vtbl *v41; // eax
  int v42; // edi
  const idDrawVert *v43; // [esp-8h] [ebp-510h]
  idFixedWinding fw; // [esp+Ch] [ebp-4FCh] BYREF
  idPlane plane; // [esp+51Ch] [ebp+14h] BYREF
  int v3; // [esp+52Ch] [ebp+24h]
  idVec3 v47; // [esp+530h] [ebp+28h]
  int v48; // [esp+53Ch] [ebp+34h]
  idVec3 dir; // [esp+540h] [ebp+38h]
  idRenderModelDecal *decalModel; // [esp+54Ch] [ebp+44h]
  unsigned __int8 *cullBits; // [esp+550h] [ebp+48h]
  int orBits; // [esp+554h] [ebp+4Ch]
  int index; // [esp+558h] [ebp+50h]
  int surfNum; // [esp+55Ch] [ebp+54h]
  int v55; // [esp+560h] [ebp+58h]
  float v56; // [esp+564h] [ebp+5Ch]
  int j; // [esp+568h] [ebp+60h]
  int v58; // [esp+574h] [ebp+6Ch]

  ebx1 = model;
  v4 = model->__vftable;
  decalModel = this;
  surfNum = 0;
  if ( v4->NumSurfaces(model) > 0 )
  {
    v5 = (const decalProjectionInfo_s *)LODWORD(localInfo);
    do
    {
      v6 = (int)ebx1->Surface(ebx1, surfNum);
      v7 = *(_DWORD *)(v6 + 8);
      if ( v7 )
      {
        v8 = *(_DWORD *)(v6 + 4);
        if ( v8 )
        {
          if ( (v5->force || *(_BYTE *)(v8 + 242))
            && v5->projectionBounds.b[0].x <= (double)*(float *)(v7 + 12)
            && v5->projectionBounds.b[0].y <= (double)*(float *)(v7 + 16)
            && v5->projectionBounds.b[0].z <= (double)*(float *)(v7 + 20)
            && v5->projectionBounds.b[1].x >= (double)*(float *)v7
            && v5->projectionBounds.b[1].y >= (double)*(float *)(v7 + 4)
            && v5->projectionBounds.b[1].z >= (double)*(float *)(v7 + 8) )
          {
            v9 = *(rvMesh **)(v7 + 136);
            if ( v9 )
            {
              if ( *(_BYTE *)(v7 + 30) )
                rvMesh::CreateDecalTriangles(
                  v9,
                  decalModel,
                  v5,
                  *(const idPlane **)(v7 + 88),
                  *(const rvSilTraceVertT **)(v7 + 44));
              else
                rvMesh::CreateDecalTriangles(v9, decalModel, v5, 0, *(const rvSilTraceVertT **)(v7 + 44));
            }
            else
            {
              j = *(_DWORD *)(v7 + 36);
              v10 = j + 18;
              LOBYTE(v10) = (j + 18) & 0xFC;
              v11 = alloca(v10);
              v12 = SIMDProcessor->__vftable;
              v43 = *(const idDrawVert **)(v7 + 40);
              p_fw = &fw;
              cullBits = (unsigned __int8 *)&fw;
              v12->DecalPointCull(SIMDProcessor, (unsigned __int8 *)&fw, v5->boundingPlanes, v43, j);
              v14 = *(_DWORD *)(v7 + 52) <= 0;
              index = 0;
              if ( !v14 )
              {
                v55 = 0;
                do
                {
                  v15 = *(_DWORD *)(v7 + 56);
                  v16 = 4 * index;
                  j = *(_DWORD *)(4 * index + v15);
                  v17 = *(_DWORD *)(4 * index + v15 + 4);
                  v3 = *(_DWORD *)(4 * index + v15 + 8);
                  LOBYTE(v15) = p_fw[v17] & p_fw[v3];
                  orBits = v17;
                  if ( ((unsigned __int8)v15 & p_fw[j]) == 0 )
                  {
                    v18 = *(_DWORD *)(v7 + 88);
                    if ( !v18
                      || !*(_BYTE *)(v7 + 30)
                      || v5->boundingPlanes[4].c * *(float *)(v18 + v55 + 8)
                       + v5->boundingPlanes[4].b * *(float *)(v18 + v55 + 4)
                       + v5->boundingPlanes[4].a * *(float *)(v18 + v55) >= v5->maxAngle )
                    {
                      fw.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
                      fw.p = fw.data;
                      fw.allocedSize = 64;
                      v19 = 0;
                      v20 = !v5->parallel;
                      v58 = 0;
                      fw.numPoints = 3;
                      if ( v20 )
                      {
                        v48 = 4 * index;
                        do
                        {
                          v26 = (float *)(*(_DWORD *)(v7 + 40) + (*(_DWORD *)(v16 + *(_DWORD *)(v7 + 56)) << 6));
                          v27 = &fw.p[v19];
                          v27->x = *v26;
                          v27->y = v26[1];
                          v27->z = v26[2];
                          v27->t = 0.0;
                          v27->s = 0.0;
                          v28 = fw.p[v19].z - v5->projectionOrigin.z;
                          v29 = fw.p[v19].y - v5->projectionOrigin.y;
                          v30 = fw.p[v19].x - v5->projectionOrigin.x;
                          dir.x = v30;
                          dir.y = v29;
                          dir.z = v28;
                          v56 = fw.p[v19].z * v5->boundingPlanes[5].c
                              + fw.p[v19].y * v5->boundingPlanes[5].b
                              + v5->boundingPlanes[5].a * fw.p[v19].x
                              + v5->boundingPlanes[5].d;
                          v31 = v29 * v5->boundingPlanes[5].b
                              + v30 * v5->boundingPlanes[5].a
                              + v28 * v5->boundingPlanes[5].c;
                          if ( v31 != 0.0 )
                            localInfo = -(v56 / v31);
                          v47 = dir;
                          v56 = dir.z * localInfo + fw.p[v19++].z;
                          v32 = dir.y * localInfo + fw.p[v19 - 1].y;
                          dir.z = v56;
                          v33 = v32;
                          v34 = dir.x * localInfo + fw.p[v19 - 1].x;
                          dir.x = v34;
                          dir.y = v33;
                          fw.p[v19 - 1].s = v33 * v5->textureAxis[0].b
                                          + v56 * v5->textureAxis[0].c
                                          + v34 * v5->textureAxis[0].a
                                          + v5->textureAxis[0].d;
                          fw.p[v19 - 1].t = v34 * v5->textureAxis[1].a
                                          + v33 * v5->textureAxis[1].b
                                          + v56 * v5->textureAxis[1].c
                                          + v5->textureAxis[1].d;
                          v16 = v48 + 4;
                          v48 += 4;
                        }
                        while ( v19 < 3 );
                        p_fw = cullBits;
                      }
                      else
                      {
                        v21 = (float *)(*(_DWORD *)(v7 + 40) + (*(_DWORD *)(*(_DWORD *)(v7 + 56) + 4 * index) << 6));
                        fw.data[0].x = *v21;
                        fw.data[0].y = v21[1];
                        fw.data[0].z = v21[2];
                        v22 = *(_DWORD *)(v7 + 56);
                        fw.data[0].s = fw.data[0].z * v5->textureAxis[0].c
                                     + fw.data[0].y * v5->textureAxis[0].b
                                     + fw.data[0].x * v5->textureAxis[0].a
                                     + v5->textureAxis[0].d;
                        fw.data[0].t = fw.data[0].z * v5->textureAxis[1].c
                                     + fw.data[0].y * v5->textureAxis[1].b
                                     + fw.data[0].x * v5->textureAxis[1].a
                                     + v5->textureAxis[1].d;
                        v23 = (float *)(*(_DWORD *)(v7 + 40) + (*(_DWORD *)(v22 + v16 + 4) << 6));
                        fw.data[1].x = *v23;
                        fw.data[1].y = v23[1];
                        fw.data[1].z = v23[2];
                        v24 = *(_DWORD *)(v7 + 56);
                        fw.data[1].s = fw.data[1].z * v5->textureAxis[0].c
                                     + fw.data[1].y * v5->textureAxis[0].b
                                     + fw.data[1].x * v5->textureAxis[0].a
                                     + v5->textureAxis[0].d;
                        fw.data[1].t = fw.data[1].z * v5->textureAxis[1].c
                                     + fw.data[1].y * v5->textureAxis[1].b
                                     + fw.data[1].x * v5->textureAxis[1].a
                                     + v5->textureAxis[1].d;
                        v25 = (float *)(*(_DWORD *)(v7 + 40) + (*(_DWORD *)(v24 + v16 + 8) << 6));
                        fw.data[2].x = *v25;
                        fw.data[2].y = v25[1];
                        fw.data[2].z = v25[2];
                        fw.data[2].s = fw.data[2].z * v5->textureAxis[0].c
                                     + fw.data[2].y * v5->textureAxis[0].b
                                     + fw.data[2].x * v5->textureAxis[0].a
                                     + v5->textureAxis[0].d;
                        fw.data[2].t = fw.data[2].z * v5->textureAxis[1].c
                                     + fw.data[2].y * v5->textureAxis[1].b
                                     + fw.data[2].x * v5->textureAxis[1].a
                                     + v5->textureAxis[1].d;
                      }
                      v35 = (unsigned __int8)p_fw[orBits] | (unsigned __int8)p_fw[j] | (unsigned __int8)p_fw[v3];
                      v36 = 0;
                      orBits = v35;
                      j = 0;
                      p_c = &v5->boundingPlanes[0].c;
                      do
                      {
                        if ( ((1 << v36) & v35) != 0 )
                        {
                          v38 = -p_c[1];
                          v39 = -*p_c;
                          v40 = -*(p_c - 1);
                          plane.a = -*(p_c - 2);
                          plane.b = v40;
                          plane.c = v39;
                          plane.d = v38;
                          if ( !idWinding::ClipInPlace(&fw, &plane, 0.1, 0) )
                            break;
                          v35 = orBits;
                        }
                        v36 = j + 1;
                        p_c += 4;
                        ++j;
                      }
                      while ( j < 6 );
                      if ( fw.numPoints )
                        idRenderModelDecal::AddDepthFadedWinding(
                          decalModel,
                          &fw,
                          v5->material,
                          v5->fadePlanes,
                          v5->fadeDepth,
                          v5->startTime);
                      fw.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
                      fw.p = 0;
                      v58 = -1;
                      Memory::Free(0);
                      fw.p = 0;
                      p_fw = cullBits;
                    }
                  }
                  v55 += 16;
                  v14 = index + 3 < *(_DWORD *)(v7 + 52);
                  index += 3;
                }
                while ( v14 );
              }
              ebx1 = model;
            }
          }
        }
      }
      v41 = ebx1->__vftable;
      v42 = ++surfNum;
    }
    while ( v42 < v41->NumSurfaces((idRenderModel *)ebx1) );
  }
}

// FUNC: public: static class idRenderModelDecal * __cdecl idRenderModelDecal::RemoveFadedDecals(class idRenderModelDecal *,int)
idRenderModelDecal *__cdecl idRenderModelDecal::RemoveFadedDecals(idRenderModelDecal *decals, int time)
{
  idRenderModelDecal *v3; // ebx
  const idMaterial *material; // eax
  bool v5; // zf
  int numIndexes; // edi
  int v7; // ecx
  float *indexStartTime; // edx
  int v9; // ebx
  int v10; // edx
  double v11; // st7
  float *v12; // edi
  int v13; // ecx
  float *v14; // ebx
  int v15; // edx
  char *v16; // ecx
  int v17; // ebp
  idRenderModelDecal *nextDecal; // edi
  int *indexes; // eax
  int v20; // ecx
  int v21; // edx
  int v22; // eax
  float *vertDepthFade; // edi
  int v24; // ebx
  int v25; // eax
  bool v26; // cc
  int *v27; // ecx
  int v28; // edx
  int *v29; // ecx
  int minTime; // [esp+4h] [ebp-BCh]
  int minTimea; // [esp+4h] [ebp-BCh]
  int minTimeb; // [esp+4h] [ebp-BCh]
  float *v33; // [esp+8h] [ebp-B8h]
  float *v34; // [esp+8h] [ebp-B8h]
  int i; // [esp+Ch] [ebp-B4h]
  int ia; // [esp+Ch] [ebp-B4h]
  float v37; // [esp+10h] [ebp-B0h]
  float *v38; // [esp+10h] [ebp-B0h]
  int newNumIndexes; // [esp+14h] [ebp-ACh]
  int inUse[40]; // [esp+20h] [ebp-A0h] BYREF

  if ( !decals )
    return 0;
  v3 = idRenderModelDecal::RemoveFadedDecals(decals->nextDecal, time);
  material = decals->material;
  v5 = decals->material == 0;
  decals->nextDecal = v3;
  if ( v5 )
  {
    --idRenderModelDecal::allocatedDecalCount;
    Memory::Free(decals);
    return v3;
  }
  else
  {
    minTime = time - material->decalInfo.stayTime;
    numIndexes = decals->tri.numIndexes;
    v7 = 0;
    if ( numIndexes > 0 )
    {
      indexStartTime = decals->indexStartTime;
      do
      {
        v37 = (float)minTime;
        if ( *indexStartTime <= (double)v37 )
          break;
        v7 += 3;
        indexStartTime += 3;
      }
      while ( v7 < decals->tri.numIndexes );
    }
    if ( v7 == numIndexes )
    {
      return decals;
    }
    else
    {
      v9 = 0;
      v10 = 0;
      newNumIndexes = 0;
      i = 0;
      if ( decals->tri.numIndexes <= 0 )
        goto LABEL_21;
      v11 = (double)minTime;
      v12 = decals->indexStartTime;
      v13 = -3144 - (_DWORD)decals;
      v38 = decals->indexStartTime;
      v33 = decals->indexStartTime;
      do
      {
        if ( v11 < *v12 )
        {
          if ( v10 != v9 )
          {
            v14 = v33;
            v15 = v10;
            v16 = (char *)v12 + v13;
            minTimea = 3;
            do
            {
              decals->tri.indexes[v15] = *(_DWORD *)&v16[(unsigned int)decals->tri.indexes];
              *v14 = *v12;
              v16 += 4;
              ++v15;
              ++v12;
              ++v14;
              --minTimea;
            }
            while ( minTimea );
            v12 = v38;
            v10 = newNumIndexes;
            v9 = i;
            v13 = -3144 - (_DWORD)decals;
          }
          v10 += 3;
          v33 += 3;
          newNumIndexes = v10;
        }
        v9 += 3;
        v12 += 3;
        i = v9;
        v38 = v12;
      }
      while ( v9 < decals->tri.numIndexes );
      v17 = 0;
      if ( v10 )
      {
        decals->tri.numIndexes = v10;
        memset(inUse, 0, sizeof(inUse));
        if ( v10 > 0 )
        {
          indexes = decals->tri.indexes;
          v20 = v10;
          do
          {
            v21 = *indexes++;
            --v20;
            inUse[v21] = 1;
          }
          while ( v20 );
        }
        v22 = 0;
        minTimeb = 0;
        ia = 0;
        if ( decals->tri.numVerts > 0 )
        {
          vertDepthFade = decals->vertDepthFade;
          v24 = 0;
          v34 = decals->vertDepthFade;
          do
          {
            if ( inUse[v22] )
            {
              idDrawVert::operator=(&decals->tri.verts[v24].xyz.x, (int)&decals->tri.verts[v17]);
              *vertDepthFade = *v34;
              inUse[ia] = minTimeb++;
              ++vertDepthFade;
              ++v24;
              v22 = ia;
            }
            ++v34;
            ++v22;
            ++v17;
            ia = v22;
          }
          while ( v22 < decals->tri.numVerts );
        }
        v25 = 0;
        v26 = decals->tri.numIndexes <= 0;
        decals->tri.numVerts = minTimeb;
        if ( !v26 )
        {
          do
          {
            v27 = decals->tri.indexes;
            v28 = inUse[v27[v25]];
            v29 = &v27[v25++];
            *v29 = v28;
          }
          while ( v25 < decals->tri.numIndexes );
        }
        return decals;
      }
      else
      {
LABEL_21:
        nextDecal = decals->nextDecal;
        --idRenderModelDecal::allocatedDecalCount;
        Memory::Free(decals);
        return nextDecal;
      }
    }
  }
}

// FUNC: public: void __thiscall idRenderModelDecal::AddDecalDrawSurf(struct viewEntity_s *)
void __thiscall idRenderModelDecal::AddDecalDrawSurf(idRenderModelDecal *this, viewEntity_s *space)
{
  int numIndexes; // edx
  float maxAngle; // eax
  int v5; // ecx
  float *indexStartTime; // edx
  double v7; // st7
  double v8; // st7
  unsigned __int8 *v9; // eax
  idDrawVert *verts; // edx
  int v11; // edi
  idSIMDProcessor_vtbl *v12; // ebx
  const idMaterial *material; // edi
  int v14; // eax
  void *v15; // esp
  bool v16; // cc
  int v17; // eax
  int v18; // edi
  float v19; // ecx
  unsigned __int8 v20; // cl
  unsigned __int8 *v21; // eax
  unsigned __int8 v22; // dl
  unsigned __int8 *v23; // eax
  unsigned __int8 v24; // dl
  unsigned __int8 *v25; // eax
  unsigned __int8 v26; // dl
  unsigned __int8 v27; // cl
  int numVerts; // edx
  vertCache_s *v29; // eax
  srfTriangles_s *v30; // ecx
  float v31[3]; // [esp+0h] [ebp-70h] BYREF
  float shaderParms[12]; // [esp+Ch] [ebp-64h] BYREF
  int stayTime; // [esp+3Ch] [ebp-34h]
  srfTriangles_s *newTri; // [esp+40h] [ebp-30h]
  unsigned __int8 *data; // [esp+44h] [ebp-2Ch]
  int v36; // [esp+48h] [ebp-28h]
  float v37; // [esp+4Ch] [ebp-24h]
  const shaderStage_t *shaderStage; // [esp+50h] [ebp-20h]
  float maxTimeFloat; // [esp+54h] [ebp-1Ch]
  float renderTime; // [esp+58h] [ebp-18h]
  idRenderModelDecal *v41; // [esp+5Ch] [ebp-14h]
  int v42; // [esp+60h] [ebp-10h]
  int v43; // [esp+64h] [ebp-Ch]
  int v44; // [esp+68h] [ebp-8h]
  unsigned __int8 *colorCache; // [esp+6Ch] [ebp-4h]

  if ( !r_skipDecals.internalVar->integerValue )
  {
    numIndexes = this->tri.numIndexes;
    if ( numIndexes )
    {
      maxAngle = this->material->decalInfo.maxAngle;
      stayTime = this->material->decalInfo.stayTime;
      newTri = (srfTriangles_s *)LODWORD(maxAngle);
      maxTimeFloat = (float)stayTime;
      v5 = 0;
      renderTime = (float)tr.viewDef->renderView.time;
      if ( numIndexes > 0 )
      {
        indexStartTime = this->indexStartTime;
        do
        {
          v7 = renderTime - *indexStartTime;
          if ( v7 <= maxTimeFloat )
          {
            if ( v7 < 0.0 )
              v7 = 0.0;
            v8 = v7 / maxTimeFloat;
            this->vertLifeSpan[this->tri.indexes[v5]] = v8;
            this->vertLifeSpan[this->tri.indexes[v5 + 1]] = v8;
            this->vertLifeSpan[this->tri.indexes[v5 + 2]] = v8;
          }
          v5 += 3;
          indexStartTime += 3;
        }
        while ( v5 < this->tri.numIndexes );
      }
      tr.pc.c_numDecalIndexes += this->tri.numIndexes;
      newTri = (srfTriangles_s *)R_FrameAlloc(180);
      srfTriangles_s::operator=(newTri, (int)&this->tri);
      v9 = (unsigned __int8 *)R_FrameAlloc(4 * this->tri.numVerts * (this->material->numStages + 16));
      verts = this->tri.verts;
      v11 = this->tri.numVerts << 6;
      colorCache = &v9[v11];
      v12 = SIMDProcessor->__vftable;
      data = v9;
      v12->Memcpy(SIMDProcessor, v9, verts, v11);
      material = this->material;
      v14 = 4 * this->material->numRegisters + 3;
      LOBYTE(v14) = v14 & 0xFC;
      v15 = alloca(v14);
      v16 = this->material->numStages <= 0;
      renderTime = 0.0;
      if ( !v16 )
      {
        v17 = this->tri.numIndexes;
        maxTimeFloat = 0.0;
        do
        {
          shaderStage = (shaderStage_t *)((char *)material->stages + LODWORD(maxTimeFloat));
          v18 = 0;
          if ( v17 > 0 )
          {
            v41 = (idRenderModelDecal *)this->indexStartTime;
            do
            {
              v19 = *(float *)&v41->material;
              shaderParms[4] = this->vertLifeSpan[this->tri.indexes[v18]];
              shaderParms[5] = v19;
              idMaterial::EvaluateStageRegisters(
                (idMaterial *)this->material,
                SLODWORD(renderTime),
                v31,
                shaderParms,
                tr.frameShaderTime);
              v37 = this->vertDepthFade[this->tri.indexes[v18]] * v31[shaderStage->color.registers[0]] * 255.0;
              v36 = (int)v37;
              v37 = this->vertDepthFade[this->tri.indexes[v18]] * v31[shaderStage->color.registers[1]] * 255.0;
              v44 = (int)v37;
              v37 = this->vertDepthFade[this->tri.indexes[v18]] * v31[shaderStage->color.registers[2]] * 255.0;
              v43 = (int)v37;
              v37 = this->vertDepthFade[this->tri.indexes[v18]] * v31[shaderStage->color.registers[3]] * 255.0;
              v42 = (int)v37;
              v20 = v36;
              v21 = &colorCache[4 * this->tri.indexes[v18]];
              v22 = v44;
              *v21 = v36;
              *++v21 = v22;
              v21[1] = v43;
              v21[2] = v42;
              v23 = &colorCache[4 * this->tri.indexes[v18 + 1]];
              v24 = v44;
              *v23 = v20;
              v23[1] = v24;
              v23 += 2;
              *v23 = v43;
              v23[1] = v42;
              v25 = &colorCache[4 * this->tri.indexes[v18 + 2]];
              *v25 = v20;
              v26 = v43;
              v41 = (idRenderModelDecal *)((char *)v41 + 12);
              *++v25 = v44;
              v27 = v42;
              *++v25 = v26;
              v25[1] = v27;
              v17 = this->tri.numIndexes;
              v18 += 3;
            }
            while ( v18 < v17 );
          }
          numVerts = this->tri.numVerts;
          material = this->material;
          LODWORD(maxTimeFloat) += 132;
          v16 = LODWORD(renderTime) + 1 < material->numStages;
          colorCache += 4 * numVerts;
          ++LODWORD(renderTime);
        }
        while ( v16 );
      }
      v29 = idVertexCache::AllocFrameTemp(
              &vertexCache,
              data,
              4 * this->tri.numVerts * (this->material->numStages + 16),
              0);
      v30 = newTri;
      newTri->ambientCache = v29;
      R_AddDrawSurf(v30, space, &space->entityDef->parms, this->material, &space->scissorRect, 1u);
    }
  }
}
