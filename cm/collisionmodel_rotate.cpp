
// FUNC: private: int __thiscall idCollisionModelManagerLocal::CollisionBetweenEdgeBounds(struct cm_traceWork_t *,class idVec3 const &,class idVec3 const &,class idVec3 const &,class idVec3 const &,float,class idVec3 &,class idVec3 &)
int __thiscall idCollisionModelManagerLocal::CollisionBetweenEdgeBounds(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        const idVec3 *va,
        const idVec3 *vb,
        const idVec3 *vc,
        const idVec3 *vd,
        float tanHalfAngle,
        idVec3 *collisionPoint,
        idVec3 *collisionNormal)
{
  double v10; // st7
  double v11; // st6
  double v12; // st7
  double v13; // st6
  double v14; // st5
  double v15; // st4
  double v16; // st4
  double v17; // st6
  double v18; // st5
  double v19; // st6
  double v20; // st5
  double v21; // st4
  double v22; // st6
  double v23; // st5
  double v26; // st7
  double v27; // st6
  double v28; // st5
  double v29; // st4
  unsigned __int8 v31; // c0
  unsigned __int8 v32; // c3
  unsigned __int8 v34; // c0
  unsigned __int8 v35; // c3
  double v36; // st7
  double v37; // st6
  double v38; // st5
  double v39; // st7
  double v40; // st7
  double v42; // st7
  double v43; // st7
  double v44; // st6
  double v45; // st7
  double v46; // st6
  double v47; // st6
  double v48; // st7
  double v49; // st6
  double v50; // st6
  double v51; // st7
  float v52; // [esp+0h] [ebp-60h]
  float v53; // [esp+4h] [ebp-5Ch]
  float v54; // [esp+8h] [ebp-58h]
  idVec3 at; // [esp+Ch] [ebp-54h]
  float at_8; // [esp+14h] [ebp-4Ch]
  idVec3 bt; // [esp+18h] [ebp-48h]
  float bt_8; // [esp+20h] [ebp-40h]
  float v59; // [esp+24h] [ebp-3Ch]
  float v60; // [esp+24h] [ebp-3Ch]
  float v61; // [esp+24h] [ebp-3Ch]
  float v62; // [esp+28h] [ebp-38h]
  float v63; // [esp+28h] [ebp-38h]
  float v64; // [esp+28h] [ebp-38h]
  float v65; // [esp+2Ch] [ebp-34h]
  float v66; // [esp+2Ch] [ebp-34h]
  float v67; // [esp+2Ch] [ebp-34h]
  float v68; // [esp+30h] [ebp-30h]
  float v69; // [esp+30h] [ebp-30h]
  float v70; // [esp+30h] [ebp-30h]
  float v71; // [esp+34h] [ebp-2Ch]
  float v72; // [esp+34h] [ebp-2Ch]
  float v73; // [esp+38h] [ebp-28h]
  float v74; // [esp+38h] [ebp-28h]
  float v75; // [esp+38h] [ebp-28h]
  float v76; // [esp+3Ch] [ebp-24h]
  float v77; // [esp+3Ch] [ebp-24h]
  float v78; // [esp+3Ch] [ebp-24h]
  float v79; // [esp+40h] [ebp-20h]
  float v80; // [esp+40h] [ebp-20h]
  float v81; // [esp+40h] [ebp-20h]
  float v82; // [esp+44h] [ebp-1Ch]
  float v83; // [esp+44h] [ebp-1Ch]
  float v84; // [esp+44h] [ebp-1Ch]
  float v85; // [esp+44h] [ebp-1Ch]
  float dira; // [esp+48h] [ebp-18h]
  float dirb; // [esp+48h] [ebp-18h]
  float dirc; // [esp+48h] [ebp-18h]
  float dird; // [esp+48h] [ebp-18h]
  float dir; // [esp+48h] [ebp-18h]
  float dir_4; // [esp+4Ch] [ebp-14h]
  float dir_4a; // [esp+4Ch] [ebp-14h]
  float dir_4b; // [esp+4Ch] [ebp-14h]
  float dir_8; // [esp+50h] [ebp-10h]
  float dir_8a; // [esp+50h] [ebp-10h]
  float dir_8b; // [esp+50h] [ebp-10h]
  float dir_8c; // [esp+50h] [ebp-10h]
  float dir_8d; // [esp+50h] [ebp-10h]
  float dir_8e; // [esp+50h] [ebp-10h]
  float dir_8f; // [esp+50h] [ebp-10h]
  float twa; // [esp+64h] [ebp+4h]
  float vca; // [esp+70h] [ebp+10h]
  float vda; // [esp+74h] [ebp+14h]
  float tanHalfAngleb; // [esp+78h] [ebp+18h]
  float tanHalfAnglea; // [esp+78h] [ebp+18h]

  at = *va;
  bt = *vb;
  if ( tanHalfAngle != 0.0 )
  {
    v10 = tanHalfAngle * tanHalfAngle;
    v11 = 1.0 / (v10 + 1.0);
    tanHalfAngleb = tanHalfAngle * v11 + tanHalfAngle * v11;
    v12 = v11 * (1.0 - v10);
    v13 = at.x - tw->origin.x;
    v14 = at.y - tw->origin.y;
    v15 = at.z - tw->origin.z;
    at_8 = v15;
    v16 = v15 * tw->axis.z + v14 * tw->axis.y + v13 * tw->axis.x;
    v59 = v16 * tw->axis.x;
    v62 = v16 * tw->axis.y;
    v65 = v16 * tw->axis.z;
    v76 = v13 - v59;
    v17 = v14 - v62;
    v18 = at_8 - v65;
    dir_8 = v17 * tw->axis.x - v76 * tw->axis.y;
    v68 = (v18 * tw->axis.y - v17 * tw->axis.z) * tanHalfAngleb;
    v71 = (v76 * tw->axis.z - v18 * tw->axis.x) * tanHalfAngleb;
    v73 = dir_8 * tanHalfAngleb;
    v77 = v76 * v12;
    v79 = v17 * v12;
    v80 = v79 - v71;
    v82 = v18 * v12 - v73;
    v72 = v80 + v62;
    v74 = v82 + v65;
    dir_8a = v74 + tw->origin.z;
    at.z = dir_8a;
    at.x = v77 - v68 + v59 + tw->origin.x;
    at.y = v72 + tw->origin.y;
    v19 = bt.x - tw->origin.x;
    v20 = bt.y - tw->origin.y;
    bt_8 = bt.z - tw->origin.z;
    v21 = v19 * tw->axis.x + bt_8 * tw->axis.z + v20 * tw->axis.y;
    v60 = v21 * tw->axis.x;
    v63 = v21 * tw->axis.y;
    v66 = v21 * tw->axis.z;
    v69 = v19 - v60;
    v22 = v20 - v63;
    v23 = bt_8 - v66;
    v75 = v23;
    dir_8b = v22 * tw->axis.x - v69 * tw->axis.y;
    v78 = (v23 * tw->axis.y - v22 * tw->axis.z) * tanHalfAngleb;
    v81 = (v69 * tw->axis.z - v75 * tw->axis.x) * tanHalfAngleb;
    v83 = dir_8b * tanHalfAngleb;
    dira = v69 * v12;
    dir_8c = v75 * v12;
    v70 = dira - v78;
    dirb = v70 + v60;
    dir_4 = v22 * v12 - v81 + v63;
    dir_8d = dir_8c - v83 + v66 + tw->origin.z;
    bt.z = dir_8d;
    bt.x = dirb + tw->origin.x;
    bt.y = dir_4 + tw->origin.y;
  }
  v26 = vd->x - vc->x;
  v27 = vd->y - vc->y;
  v28 = vd->z - vc->z;
  v52 = bt.x - at.x;
  v53 = bt.y - at.y;
  v29 = bt.z - at.z;
  vda = v53 * v28 - v29 * v27;
  collisionNormal->x = vda;
  vca = v29 * v26 - v28 * v52;
  collisionNormal->y = vca;
  twa = v27 * v52 - v53 * v26;
  collisionNormal->z = twa;
  if ( !(v31 | v32) )
    return 0;
  if ( !(v34 | v35) )
    return 0;
  v36 = vd->x - vc->x;
  v37 = vd->y - vc->y;
  v38 = vd->z - vc->z;
  dirc = vca * v38 - v37 * twa;
  dir_4a = twa * v36 - v38 * vda;
  v39 = v37 * vda - vca * v36;
  tanHalfAnglea = v39 * at.z + dir_4a * at.y + dirc * at.x - (dirc * vc->x + dir_4a * vc->y + v39 * vc->z);
  v40 = v39 * bt.z + dir_4a * bt.y + dirc * bt.x - (dirc * vc->x + dir_4a * vc->y + v39 * vc->z);
  if ( tanHalfAnglea == v40 )
    return 0;
  v42 = tanHalfAnglea / (tanHalfAnglea - v40);
  dir_4b = v53 * v42;
  v54 = v29;
  dir_8e = v54 * v42;
  v43 = v52 * v42 + at.x;
  v44 = dir_4b + at.y;
  v84 = dir_8e + at.z;
  collisionPoint->x = v43;
  collisionPoint->y = v44;
  collisionPoint->z = v84;
  dird = v43 - tw->origin.x;
  v45 = v44 - tw->origin.y;
  v46 = v84 - tw->origin.z;
  v61 = v45 * tw->axis.z - v46 * tw->axis.y;
  v64 = v46 * tw->axis.x - dird * tw->axis.z;
  v47 = dird;
  dir = v61;
  v67 = v47 * tw->axis.y - v45 * tw->axis.x;
  v48 = v64;
  v49 = v67;
  if ( tw->angle < 0.0 )
  {
    v85 = -v67;
    v48 = -v64;
    dir = -v61;
    v49 = v85;
  }
  if ( v49 * collisionNormal->z + v48 * collisionNormal->y + dir * collisionNormal->x > 0.0 )
  {
    dir_8f = -collisionNormal->z;
    v50 = -collisionNormal->x;
    v51 = -collisionNormal->y;
    collisionNormal->z = dir_8f;
    collisionNormal->x = v50;
    collisionNormal->y = v51;
  }
  return 1;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::RotateTrmEdgeThroughPolygon(struct cm_traceWork_t *,struct cm_polygon_t *,struct cm_trmEdge_t *)
void __thiscall idCollisionModelManagerLocal::RotateTrmEdgeThroughPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_polygon_t *poly,
        cm_trmEdge_t *trmEdge)
{
  int v4; // eax
  cm_polygon_t *v5; // esi
  int v6; // eax
  bool v7; // cc
  int v9; // ecx
  idCollisionModelLocal *model; // esi
  unsigned int v11; // edx
  bool v12; // zf
  cm_vertex_t *vertices; // eax
  cm_vertex_t *v14; // esi
  __m128 v15; // xmm1
  __m128 v16; // xmm0
  __m128 v17; // xmm1
  __m128 v18; // xmm2
  __m128 v19; // xmm3
  __m128 v20; // xmm2
  __m128 v21; // xmm0
  __m128 v22; // xmm5
  double v23; // st7
  double v24; // st6
  double v25; // st5
  double v26; // st6
  double v27; // st7
  double v28; // st6
  double v29; // st5
  double v30; // rt2
  double v31; // st6
  double v32; // rtt
  double v33; // st6
  double x; // st7
  double v35; // st7
  double y; // st6
  double v37; // st6
  double v38; // st5
  double v39; // st7
  double v40; // st7
  double v41; // st7
  double v42; // st6
  long double v43; // st6
  double v44; // st6
  double v45; // rt2
  double v46; // st6
  double v47; // st7
  double v48; // st6
  double v49; // st5
  double v50; // st7
  double v51; // st7
  double v52; // st6
  double v53; // st7
  double v54; // st6
  char v55; // fps^1
  double angle; // st5
  bool v57; // c0
  char v58; // c2
  bool v59; // c3
  char v60; // ah
  bool v61; // c0
  bool v62; // c3
  double v63; // st6
  double v64; // st6
  double v65; // st5
  long double v66; // st5
  double v67; // st5
  double v68; // rt1
  double v69; // st5
  long double v70; // st7
  double v71; // st7
  double v72; // st7
  double v73; // st6
  double v74; // st5
  double v75; // st7
  double v76; // st7
  double v77; // st6
  double v78; // st7
  double v79; // st7
  double v80; // st6
  long double v81; // st6
  double v82; // st6
  double v83; // rt0
  double v84; // st6
  long double v85; // st7
  const idVec3 *p_p; // edi
  double v87; // st7
  double v88; // st7
  float v89; // ecx
  float v90; // edx
  long double v91; // st4
  long double v92; // st7
  double v93; // st7
  int v94; // edx
  idCollisionModelManagerLocal *v95; // ecx
  float v96; // edx
  float v97; // eax
  float z; // edx
  float v99; // [esp+10h] [ebp-170h]
  float v100; // [esp+14h] [ebp-16Ch]
  float v101; // [esp+24h] [ebp-15Ch]
  float v102; // [esp+28h] [ebp-158h]
  idVec3 collisionNormal; // [esp+2Ch] [ebp-154h] BYREF
  float v104; // [esp+38h] [ebp-148h]
  float v105; // [esp+3Ch] [ebp-144h]
  float v106; // [esp+40h] [ebp-140h]
  float v107; // [esp+44h] [ebp-13Ch]
  float v108; // [esp+48h] [ebp-138h]
  float v109; // [esp+4Ch] [ebp-134h]
  float v110; // [esp+50h] [ebp-130h]
  float v111; // [esp+54h] [ebp-12Ch]
  float v112; // [esp+58h] [ebp-128h]
  float v113; // [esp+5Ch] [ebp-124h]
  float v114; // [esp+60h] [ebp-120h]
  float v115; // [esp+64h] [ebp-11Ch]
  float v116; // [esp+68h] [ebp-118h]
  float v117; // [esp+6Ch] [ebp-114h]
  float v118; // [esp+70h] [ebp-110h]
  float v119; // [esp+74h] [ebp-10Ch]
  float v120; // [esp+78h] [ebp-108h]
  float v121; // [esp+7Ch] [ebp-104h]
  idVec3 *vd; // [esp+80h] [ebp-100h]
  float v123; // [esp+84h] [ebp-FCh]
  float v124; // [esp+88h] [ebp-F8h]
  float v125; // [esp+8Ch] [ebp-F4h]
  float v126; // [esp+90h] [ebp-F0h]
  float v127; // [esp+94h] [ebp-ECh]
  float v128; // [esp+98h] [ebp-E8h]
  float v129; // [esp+9Ch] [ebp-E4h]
  float v130; // [esp+A0h] [ebp-E0h]
  float v131; // [esp+A4h] [ebp-DCh]
  float v132; // [esp+A8h] [ebp-D8h]
  float v133; // [esp+ACh] [ebp-D4h]
  float v134; // [esp+B0h] [ebp-D0h]
  int edgeNum; // [esp+B4h] [ebp-CCh]
  float v136; // [esp+B8h] [ebp-C8h]
  float v137; // [esp+BCh] [ebp-C4h]
  float v138; // [esp+C0h] [ebp-C0h]
  float v139; // [esp+C4h] [ebp-BCh]
  float v140; // [esp+C8h] [ebp-B8h]
  float v141; // [esp+CCh] [ebp-B4h]
  float v142; // [esp+D0h] [ebp-B0h]
  float v143; // [esp+D4h] [ebp-ACh]
  float v144; // [esp+DCh] [ebp-A4h]
  float v145; // [esp+E0h] [ebp-A0h]
  float v146; // [esp+E4h] [ebp-9Ch]
  float v147; // [esp+E8h] [ebp-98h]
  float v148; // [esp+ECh] [ebp-94h]
  float v149; // [esp+F0h] [ebp-90h]
  float v150; // [esp+F4h] [ebp-8Ch]
  float v151; // [esp+F8h] [ebp-88h]
  float v152; // [esp+FCh] [ebp-84h]
  float v153; // [esp+100h] [ebp-80h]
  float v154; // [esp+104h] [ebp-7Ch]
  float v155; // [esp+108h] [ebp-78h]
  float v156; // [esp+10Ch] [ebp-74h]
  float v157; // [esp+110h] [ebp-70h]
  float v158; // [esp+118h] [ebp-68h]
  float v159; // [esp+11Ch] [ebp-64h]
  idVec3 *vc; // [esp+124h] [ebp-5Ch]
  idVec3 collisionPoint; // [esp+128h] [ebp-58h] BYREF
  idCollisionModelManagerLocal *v162; // [esp+134h] [ebp-4Ch]
  int *v163; // [esp+138h] [ebp-48h]
  int i; // [esp+13Ch] [ebp-44h]
  double v165; // [esp+140h] [ebp-40h]
  double v166; // [esp+148h] [ebp-38h]
  double v167; // [esp+150h] [ebp-30h]
  idPluecker epsPl; // [esp+158h] [ebp-28h]
  bool v169; // [esp+173h] [ebp-Dh]
  double v170; // [esp+174h] [ebp-Ch]
  float tanHalfAngle; // [esp+17Ch] [ebp-4h]
  float startTan; // [esp+188h] [ebp+8h]
  float startTana; // [esp+188h] [ebp+8h]

  v162 = this;
  i = (int)&trmEdge->rotationBounds;
  v4 = _mm_movemask_ps(
         _mm_and_ps(
           _mm_cmpnlt_ps(
             _mm_loadh_ps((const double *)&trmEdge->rotationBounds.b[1].y),
             _mm_loadh_ps((const double *)&poly->bounds.b[0].y)),
           _mm_cmple_ps(
             _mm_loadh_ps((const double *)&trmEdge->rotationBounds.b[0].y),
             _mm_loadh_ps((const double *)&poly->bounds.b[1].y)))) ^ 0xF;
  v169 = v4 == 0;
  if ( !v4 )
  {
    v5 = poly;
    if ( idBounds::PlaneSide(&trmEdge->rotationBounds, &poly->plane, 0.1) == 3 )
    {
      v6 = 0;
      v7 = poly->numEdges <= 0;
      i = 0;
      if ( !v7 )
      {
        v163 = (int *)&tw->polygonEdgePlueckerCache[0].p[5];
        do
        {
          v9 = v5->edges[v6];
          model = tw->model;
          v11 = (unsigned int)&model->edges[abs32(v9)];
          v12 = *(_DWORD *)v11 == v162->checkCount;
          edgeNum = v9;
          if ( v12 )
            goto LABEL_75;
          if ( *(_WORD *)(v11 + 4) )
            goto LABEL_75;
          vertices = model->vertices;
          v14 = &vertices[*(_DWORD *)(v11 + 4 * ((unsigned int)v9 >> 31) + 16)];
          vd = &vertices[*(_DWORD *)(v11 + 4 * (v9 >= 0) + 16)].p;
          HIDWORD(v166) = vd;
          vc = &v14->p;
          HIDWORD(v167) = &v14->p;
          HIDWORD(v170) = &trmEdge->rotationBounds;
          v15 = _mm_loadh_ps((const double *)&trmEdge->rotationBounds.b[1].y);
          v16 = _mm_mul_ps(
                  _mm_add_ps(_mm_loadh_ps((const double *)&trmEdge->rotationBounds.b[0].y), v15),
                  *(__m128 *)SIMD_SP_half_0);
          v17 = _mm_sub_ps(v15, v16);
          v18 = _mm_loadh_ps((const double *)&v14->p.y);
          v19 = _mm_mul_ps(_mm_sub_ps(_mm_loadh_ps((const double *)&vd->y), v18), *(__m128 *)SIMD_SP_half_0);
          v20 = _mm_sub_ps(_mm_add_ps(v18, v19), v16);
          v21 = _mm_and_ps(v19, *(__m128 *)SIMD_SP_absMask_0);
          v22 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(v20, v20, 54), v19), _mm_mul_ps(_mm_shuffle_ps(v19, v19, 54), v20));
          if ( _mm_movemask_ps(
                 _mm_and_ps(
                   _mm_cmple_ps(_mm_sub_ps(_mm_and_ps(v20, *(__m128 *)SIMD_SP_absMask_0), v21), v17),
                   _mm_cmple_ps(
                     _mm_and_ps(_mm_shuffle_ps(v22, v22, 54), *(__m128 *)SIMD_SP_absMask_0),
                     _mm_add_ps(
                       _mm_mul_ps(_mm_shuffle_ps(v17, v17, 6), _mm_shuffle_ps(v21, v21, 183)),
                       _mm_mul_ps(_mm_shuffle_ps(v17, v17, 183), _mm_shuffle_ps(v21, v21, 6)))))) != 0xF )
            goto LABEL_75;
          v23 = *(float *)(v11 + 24) * 0.25009999;
          v24 = *(float *)(v11 + 28) * 0.25009999;
          v125 = *((float *)v163 - 3);
          v25 = *(float *)(v11 + 32) * 0.25009999;
          v127 = *((float *)v163 - 1);
          v128 = *(float *)v163;
          v123 = v24 * *((float *)v163 - 3) + v23 * *(float *)v163 + *((float *)v163 - 5);
          epsPl.p[0] = v123;
          v124 = *((float *)v163 - 4) - v23 * *((float *)v163 - 1) + v25 * *((float *)v163 - 3);
          epsPl.p[1] = v124;
          v26 = v24 * *((float *)v163 - 1);
          epsPl.p[2] = v125;
          v126 = *((float *)v163 - 2) - v26 - v25 * *(float *)v163;
          epsPl.p[3] = v126;
          epsPl.p[4] = v127;
          epsPl.p[5] = v128;
          if ( (v128 * trmEdge->pl.p[1]
              + v126 * trmEdge->pl.p[2]
              + v125 * trmEdge->pl.p[3]
              + v124 * trmEdge->pl.p[5]
              + v123 * trmEdge->pl.p[4]
              + v127 * trmEdge->pl.p[0])
             * (trmEdge->pl.p[5] * *((float *)v163 - 4)
              + trmEdge->pl.p[1] * *(float *)v163
              + trmEdge->pl.p[4] * *((float *)v163 - 5)
              + trmEdge->pl.p[3] * *((float *)v163 - 3)
              + trmEdge->pl.p[2] * *((float *)v163 - 2)
              + *((float *)v163 - 1) * trmEdge->pl.p[0]) > 0.0 )
          {
            v27 = *(float *)(v11 + 24) * 0.25;
            v120 = *((float *)v163 - 1);
            v28 = *(float *)(v11 + 28) * 0.25;
            v29 = *(float *)(v11 + 32);
            v118 = *((float *)v163 - 3);
            v116 = v28 * *((float *)v163 - 3) + v27 * *(float *)v163 + *((float *)v163 - 5);
            v30 = v29 * 0.25;
            epsPl.p[0] = v116;
            v117 = *((float *)v163 - 4) - v27 * *((float *)v163 - 1) + v30 * *((float *)v163 - 3);
            epsPl.p[1] = v117;
            v31 = v28 * *((float *)v163 - 1);
            epsPl.p[4] = v120;
            v32 = *((float *)v163 - 2) - v31;
            v33 = v30 * *(float *)v163;
            v121 = *(float *)v163;
            epsPl.p[2] = v118;
            epsPl.p[5] = v121;
            v119 = v32 - v33;
            x = tw->origin.x;
            epsPl.p[3] = v119;
            v35 = -x;
            y = tw->origin.y;
            tanHalfAngle = tw->maxTan;
            v37 = -y;
            v38 = -tw->origin.z;
            v156 = v37 * v118 + v121 * v35 + v116;
            v157 = v117 - v120 * v35 + v38 * v118;
            v39 = v119 - v37 * v120 - v38 * v121;
            v104 = v39 * tw->matrix.mat[0].z - v157 * tw->matrix.mat[1].z + v156 * tw->matrix.mat[2].z;
            v144 = v104;
            v105 = v157 * tw->matrix.mat[1].y - v39 * tw->matrix.mat[0].y - v156 * tw->matrix.mat[2].y;
            v145 = v105;
            v106 = v118 * tw->matrix.mat[0].x - v121 * tw->matrix.mat[1].x + v120 * tw->matrix.mat[2].x;
            v146 = v106;
            v107 = v39 * tw->matrix.mat[0].x - v157 * tw->matrix.mat[1].x + v156 * tw->matrix.mat[2].x;
            v147 = v107;
            v108 = v118 * tw->matrix.mat[0].z - v121 * tw->matrix.mat[1].z + v120 * tw->matrix.mat[2].z;
            v148 = v108;
            v109 = v121 * tw->matrix.mat[1].y - v118 * tw->matrix.mat[0].y - v120 * tw->matrix.mat[2].y;
            v149 = v109;
            v165 = v104 * trmEdge->plzaxis.p[4] + v108 * trmEdge->plzaxis.p[0];
            v167 = v107 * trmEdge->plzaxis.p[2]
                 + v109 * trmEdge->plzaxis.p[1]
                 + v106 * trmEdge->plzaxis.p[3]
                 + v105 * trmEdge->plzaxis.p[5];
            v170 = v165 - v167;
            v40 = v105 * trmEdge->plzaxis.p[2]
                - v106 * trmEdge->plzaxis.p[1]
                + v109 * trmEdge->plzaxis.p[3]
                - v107 * trmEdge->plzaxis.p[5];
            v167 = v167 + v165;
            if ( v170 == 0.0 )
            {
              if ( v40 == 0.0 )
                goto LABEL_75;
              v41 = -(v167 / (v40 + v40));
              v42 = 1.0e10;
            }
            else
            {
              v43 = v40 * v40 - v167 * v170;
              if ( v43 <= 0.0 )
                goto LABEL_75;
              v44 = sqrt(v43);
              if ( v40 <= 0.0 )
              {
                v45 = v44;
                v46 = v40;
                v40 = v45;
                v44 = -v46;
              }
              v166 = v44 - v40;
              v41 = v166 / v170;
              v42 = v167 / v166;
            }
            v170 = v42;
            if ( tw->angle < 0.0 )
            {
              v41 = -v41;
              v170 = -v170;
            }
            if ( v41 >= 0.0 && v41 < tanHalfAngle )
              tanHalfAngle = v41;
            if ( v170 >= 0.0 && tanHalfAngle > v170 )
              tanHalfAngle = v170;
            if ( tw->angle < 0.0 )
              tanHalfAngle = -tanHalfAngle;
            goto LABEL_69;
          }
          v47 = -tw->origin.x;
          v48 = -tw->origin.y;
          v49 = -tw->origin.z;
          v158 = v47 * *(float *)v163 + v48 * *((float *)v163 - 3) + *((float *)v163 - 5);
          v159 = *((float *)v163 - 4) - v47 * *((float *)v163 - 1) + v49 * *((float *)v163 - 3);
          v50 = *((float *)v163 - 2) - v48 * *((float *)v163 - 1) - v49 * *(float *)v163;
          v110 = v50 * tw->matrix.mat[0].z - v159 * tw->matrix.mat[1].z + v158 * tw->matrix.mat[2].z;
          v136 = v110;
          v111 = v159 * tw->matrix.mat[1].y - v50 * tw->matrix.mat[0].y - v158 * tw->matrix.mat[2].y;
          v112 = *((float *)v163 - 3) * tw->matrix.mat[0].x
               - tw->matrix.mat[1].x * *(float *)v163
               + *((float *)v163 - 1) * tw->matrix.mat[2].x;
          v113 = v50 * tw->matrix.mat[0].x - v159 * tw->matrix.mat[1].x + v158 * tw->matrix.mat[2].x;
          v114 = *((float *)v163 - 3) * tw->matrix.mat[0].z
               - *(float *)v163 * tw->matrix.mat[1].z
               + *((float *)v163 - 1) * tw->matrix.mat[2].z;
          v115 = tw->matrix.mat[1].y * *(float *)v163
               - tw->matrix.mat[0].y * *((float *)v163 - 3)
               - tw->matrix.mat[2].y * *((float *)v163 - 1);
          v137 = v111;
          v51 = v111 * trmEdge->plzaxis.p[2];
          v138 = v112;
          v52 = v112 * trmEdge->plzaxis.p[1];
          v141 = v115;
          v139 = v113;
          v140 = v114;
          v53 = v51 - v52 + v115 * trmEdge->plzaxis.p[3] - v113 * trmEdge->plzaxis.p[5];
          v170 = v53;
          v165 = v113 * trmEdge->plzaxis.p[2]
               + v115 * trmEdge->plzaxis.p[1]
               + v112 * trmEdge->plzaxis.p[3]
               + v111 * trmEdge->plzaxis.p[5];
          v54 = v165 + v110 * trmEdge->plzaxis.p[4] + v114 * trmEdge->plzaxis.p[0];
          angle = tw->angle;
          v57 = angle < 0.0;
          v58 = 0;
          v59 = angle == 0.0;
          v60 = v55;
          v61 = v54 < 0.0;
          v62 = v54 == 0.0;
          if ( (v60 & 0x41) != 0 )
          {
            if ( !v61 && !v62 )
LABEL_30:
              v53 = -v53;
          }
          else if ( v61 || v62 )
          {
            goto LABEL_30;
          }
          if ( v53 <= 0.0 )
            goto LABEL_53;
          v167 = -v170;
          v63 = -v165;
          if ( v167 == 0.0 )
          {
            if ( v63 == 0.0 )
              goto LABEL_75;
            v64 = -(v170 / (-v165 - v165));
            v65 = 1.0e10;
          }
          else
          {
            v66 = v63 * v63 - v167 * v170;
            if ( v66 <= 0.0 )
              goto LABEL_75;
            v67 = sqrt(v66);
            if ( v63 <= 0.0 )
            {
              v68 = v67;
              v69 = v63;
              v63 = v68;
              v67 = -v69;
            }
            v166 = v67 - v63;
            v64 = v166 / v167;
            v65 = v170 / v166;
          }
          v170 = v65;
          if ( tw->angle < 0.0 )
          {
            v64 = -v64;
            v170 = -v170;
          }
          if ( v64 < 0.0 && v170 < 0.0 )
            goto LABEL_75;
          if ( v64 <= v170 )
            startTan = v170;
          else
            startTan = v64;
          if ( tw->angle < 0.0 )
            startTan = -startTan;
          if ( v53 <= 0.0 )
          {
LABEL_53:
            tanHalfAngle = 0.0;
            goto LABEL_69;
          }
          v70 = fabs(startTan);
          if ( v70 >= tw->maxTan )
            goto LABEL_75;
          *((float *)&v166 + 1) = v70;
          v71 = tw->origin.x;
          tanHalfAngle = tw->maxTan;
          v72 = -v71;
          v73 = -tw->origin.y;
          v74 = -tw->origin.z;
          v142 = v73 * epsPl.p[2] + epsPl.p[5] * v72 + epsPl.p[0];
          v143 = epsPl.p[1] - epsPl.p[4] * v72 + v74 * epsPl.p[2];
          v75 = epsPl.p[3] - v73 * epsPl.p[4] - v74 * epsPl.p[5];
          v129 = v75 * tw->matrix.mat[0].z - v143 * tw->matrix.mat[1].z + v142 * tw->matrix.mat[2].z;
          v130 = v143 * tw->matrix.mat[1].y - v75 * tw->matrix.mat[0].y - v142 * tw->matrix.mat[2].y;
          v131 = epsPl.p[2] * tw->matrix.mat[0].x - epsPl.p[5] * tw->matrix.mat[1].x + epsPl.p[4] * tw->matrix.mat[2].x;
          v132 = v75 * tw->matrix.mat[0].x - v143 * tw->matrix.mat[1].x + v142 * tw->matrix.mat[2].x;
          v133 = epsPl.p[2] * tw->matrix.mat[0].z - epsPl.p[5] * tw->matrix.mat[1].z + epsPl.p[4] * tw->matrix.mat[2].z;
          v134 = epsPl.p[5] * tw->matrix.mat[1].y - epsPl.p[2] * tw->matrix.mat[0].y - epsPl.p[4] * tw->matrix.mat[2].y;
          v151 = v130;
          v150 = v129;
          v76 = v129 * trmEdge->plzaxis.p[4];
          v154 = v133;
          v77 = v133 * trmEdge->plzaxis.p[0];
          v152 = v131;
          v155 = v134;
          v153 = v132;
          v165 = v76 + v77;
          v167 = v134 * trmEdge->plzaxis.p[1]
               + v131 * trmEdge->plzaxis.p[3]
               + v130 * trmEdge->plzaxis.p[5]
               + v132 * trmEdge->plzaxis.p[2];
          v170 = v165 - v167;
          v78 = v130 * trmEdge->plzaxis.p[2]
              - v131 * trmEdge->plzaxis.p[1]
              + v134 * trmEdge->plzaxis.p[3]
              - v132 * trmEdge->plzaxis.p[5];
          v167 = v167 + v165;
          if ( v170 == 0.0 )
          {
            if ( v78 == 0.0 )
              goto LABEL_68;
            v79 = -(v167 / (v78 + v78));
            v80 = 1.0e10;
          }
          else
          {
            v81 = v78 * v78 - v167 * v170;
            if ( v81 <= 0.0 )
            {
LABEL_68:
              tanHalfAngle = startTan;
              goto LABEL_69;
            }
            v82 = sqrt(v81);
            if ( v78 <= 0.0 )
            {
              v83 = v82;
              v84 = v78;
              v78 = v83;
              v82 = -v84;
            }
            v165 = v82 - v78;
            v79 = v165 / v170;
            v80 = v167 / v165;
          }
          v170 = v80;
          if ( tw->angle < 0.0 )
          {
            v79 = -v79;
            v170 = -v170;
          }
          if ( v79 >= *((float *)&v166 + 1) && v79 < tanHalfAngle )
            tanHalfAngle = v79;
          if ( *((float *)&v166 + 1) <= v170 && tanHalfAngle > v170 )
            tanHalfAngle = v170;
          if ( tw->angle < 0.0 )
            tanHalfAngle = -tanHalfAngle;
LABEL_69:
          v85 = fabs(tanHalfAngle);
          startTana = v85;
          if ( v85 < tw->maxTan )
          {
            p_p = &tw->vertices[trmEdge->vertexNum[0]].p;
            if ( idCollisionModelManagerLocal::CollisionBetweenEdgeBounds(
                   v162,
                   tw,
                   p_p,
                   &tw->vertices[trmEdge->vertexNum[1]].p,
                   vc,
                   vd,
                   tanHalfAngle,
                   &collisionPoint,
                   &collisionNormal) )
            {
              v87 = (collisionPoint.z - tw->origin.z) * tw->axis.z
                  + (collisionPoint.y - tw->origin.y) * tw->axis.y
                  + (collisionPoint.x - tw->origin.x) * tw->axis.x;
              v101 = v87 * tw->axis.y;
              v102 = v87 * tw->axis.z;
              v99 = v102 + tw->origin.z;
              v100 = collisionPoint.x - (v87 * tw->axis.x + tw->origin.x);
              v88 = collisionPoint.y - (v101 + tw->origin.y);
              if ( (collisionPoint.z - v99) * (collisionPoint.z - v99) + v88 * v88 + v100 * v100 >= 0.0000062499998 )
              {
                v89 = collisionNormal.x;
                v90 = collisionNormal.y;
                tw->maxTan = startTana;
                tw->trace.c.normal.z = collisionNormal.z;
                tw->trace.c.normal.x = v89;
                tw->trace.c.normal.y = v90;
                v91 = tw->trace.c.normal.x * tw->trace.c.normal.x
                    + tw->trace.c.normal.y * tw->trace.c.normal.y
                    + tw->trace.c.normal.z * tw->trace.c.normal.z;
                if ( v91 != 0.0 )
                {
                  v92 = 1.0 / sqrt(v91);
                  tw->trace.c.normal.x = v92 * tw->trace.c.normal.x;
                  tw->trace.c.normal.y = v92 * tw->trace.c.normal.y;
                  tw->trace.c.normal.z = v92 * tw->trace.c.normal.z;
                }
                v93 = vc->z * tw->trace.c.normal.z + vc->y * tw->trace.c.normal.y + vc->x * tw->trace.c.normal.x;
                tw->trace.c.dist = v93;
                tw->trace.c.separation = tw->trace.c.normal.z * p_p->z
                                       + tw->trace.c.normal.y * p_p->y
                                       + p_p->x * tw->trace.c.normal.x
                                       - v93;
                tw->trace.c.contents = poly->contents;
                v94 = edgeNum;
                tw->trace.c.material = poly->material;
                v95 = v162;
                tw->trace.c.modelFeature = v94;
                v96 = collisionPoint.x;
                tw->trace.c.trmFeature = ((char *)trmEdge - (char *)tw - 3072) / 96;
                v97 = collisionPoint.y;
                tw->trace.c.type = CONTACT_EDGE;
                tw->trace.c.point.x = v96;
                z = collisionPoint.z;
                tw->trace.c.point.y = v97;
                tw->trace.c.point.z = z;
                idCollisionModelManagerLocal::CM_GetMaterialType(v95, tw, poly);
                if ( tw->maxTan == 0.0 )
                  return;
              }
            }
          }
LABEL_75:
          v5 = poly;
          v163 += 6;
          v6 = i + 1;
          v7 = ++i < poly->numEdges;
        }
        while ( v7 );
      }
    }
  }
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::RotatePointThroughEpsilonPlane(struct cm_traceWork_t const *,class idVec3 const &,class idVec3 const &,class idPlane const &,float,class idVec3 const &,float &,class idVec3 &,class idVec3 &)
int __thiscall idCollisionModelManagerLocal::RotatePointThroughEpsilonPlane(
        idCollisionModelManagerLocal *this,
        const cm_traceWork_t *tw,
        const idVec3 *point,
        const idVec3 *endPoint,
        const idPlane *plane,
        float angle,
        const idVec3 *origin,
        float *tanHalfAngle,
        idVec3 *collisionPoint,
        idVec3 *endDir)
{
  const idPlane *v10; // edi
  unsigned __int8 v12; // c0
  unsigned __int8 v13; // c2
  double v14; // st6
  double v15; // st5
  double v16; // st7
  double v17; // st6
  double v18; // st7
  double v19; // st6
  double v20; // st5
  double v21; // rt2
  double v22; // st6
  double v23; // st7
  float *v24; // edi
  double v25; // st7
  double v26; // st6
  double v27; // st5
  double v28; // st7
  double v29; // st7
  double v30; // st6
  long double v31; // st6
  double v32; // st6
  double v33; // rtt
  double v34; // st6
  double v35; // st7
  double v36; // st7
  double v37; // st6
  double v38; // st5
  double v39; // st7
  double v40; // st6
  double v41; // st5
  double v42; // st7
  double v43; // st6
  double v44; // st7
  double v45; // st7
  double v46; // st6
  long double v47; // st6
  double v48; // st6
  double v49; // rt2
  double v50; // st6
  long double v51; // st7
  int result; // eax
  double v53; // st7
  double v54; // st6
  double v55; // st5
  double v56; // st7
  double v57; // st7
  double v58; // st6
  long double v59; // st6
  double v60; // st6
  double v61; // rt2
  double v62; // st6
  double v63; // st7
  double v64; // st5
  double v65; // st4
  double v66; // st3
  double v67; // st4
  double v68; // st4
  double v69; // st6
  double v70; // st7
  double v71; // st6
  double v72; // st7
  float dir; // [esp+Ch] [ebp-5Ch]
  float dira; // [esp+Ch] [ebp-5Ch]
  float dirb; // [esp+Ch] [ebp-5Ch]
  float startTanc; // [esp+10h] [ebp-58h]
  double startTan; // [esp+10h] [ebp-58h]
  double startTand; // [esp+10h] [ebp-58h]
  float startTana; // [esp+10h] [ebp-58h]
  double startTane; // [esp+10h] [ebp-58h]
  double startTanb; // [esp+10h] [ebp-58h]
  float startTanf; // [esp+10h] [ebp-58h]
  float startTan_4; // [esp+14h] [ebp-54h]
  float v84; // [esp+20h] [ebp-48h]
  double v85; // [esp+20h] [ebp-48h]
  double v86; // [esp+20h] [ebp-48h]
  double v87; // [esp+20h] [ebp-48h]
  double v88; // [esp+20h] [ebp-48h]
  float v89; // [esp+20h] [ebp-48h]
  double v90; // [esp+28h] [ebp-40h]
  double v91; // [esp+28h] [ebp-40h]
  double v92; // [esp+28h] [ebp-40h]
  double v93; // [esp+28h] [ebp-40h]
  float epsPlane; // [esp+30h] [ebp-38h]
  double epsPlaneb; // [esp+30h] [ebp-38h]
  double epsPlanec; // [esp+30h] [ebp-38h]
  double epsPlanea; // [esp+30h] [ebp-38h]
  float epsPlaned; // [esp+30h] [ebp-38h]
  float epsPlane_4; // [esp+34h] [ebp-34h]
  float epsPlane_4a; // [esp+34h] [ebp-34h]
  float epsPlane_8; // [esp+38h] [ebp-30h]
  float epsPlane_8a; // [esp+38h] [ebp-30h]
  float epsPlane_12; // [esp+3Ch] [ebp-2Ch]
  float v104; // [esp+40h] [ebp-28h]
  __int64 v105; // [esp+40h] [ebp-28h]
  float v106; // [esp+40h] [ebp-28h]
  double v107; // [esp+40h] [ebp-28h]
  float v108; // [esp+40h] [ebp-28h]
  float v109; // [esp+44h] [ebp-24h]
  float v110; // [esp+44h] [ebp-24h]
  float v111; // [esp+44h] [ebp-24h]
  float v112; // [esp+48h] [ebp-20h]
  float v113; // [esp+48h] [ebp-20h]
  float v114; // [esp+50h] [ebp-18h]
  float v115; // [esp+54h] [ebp-14h]
  float v116; // [esp+54h] [ebp-14h]
  float v117; // [esp+58h] [ebp-10h]
  float v118; // [esp+58h] [ebp-10h]
  float v119; // [esp+58h] [ebp-10h]
  float v120; // [esp+58h] [ebp-10h]
  float startDir; // [esp+5Ch] [ebp-Ch]
  float startDira; // [esp+5Ch] [ebp-Ch]
  float startDirb; // [esp+5Ch] [ebp-Ch]
  float startDirc; // [esp+5Ch] [ebp-Ch]
  float startDird; // [esp+5Ch] [ebp-Ch]
  float startDir_4; // [esp+60h] [ebp-8h]
  float startDir_4a; // [esp+60h] [ebp-8h]
  float startDir_4b; // [esp+60h] [ebp-8h]
  float startDir_8; // [esp+64h] [ebp-4h]
  float startDir_8a; // [esp+64h] [ebp-4h]
  float startDir_8b; // [esp+64h] [ebp-4h]
  float startDir_8c; // [esp+64h] [ebp-4h]

  v10 = plane;
  epsPlane = plane->a;
  epsPlane_4 = plane->b;
  epsPlane_8 = plane->c;
  epsPlane_12 = -(0.25 - plane->d);
  v84 = point->x - origin->x;
  if ( v12 | v13 )
    return 0;
  v14 = point->y - origin->y;
  v15 = point->z - origin->z;
  v104 = v14 * tw->axis.z - v15 * tw->axis.y;
  startDir = v104;
  v109 = v15 * tw->axis.x - v84 * tw->axis.z;
  v112 = v84 * tw->axis.y - v14 * tw->axis.x;
  v16 = v109;
  v17 = v112;
  if ( angle < 0.0 )
  {
    v117 = -v112;
    v16 = -v109;
    startDir = -v104;
    v17 = v117;
  }
  if ( v16 * epsPlane_4 + v17 * epsPlane_8 + startDir * epsPlane >= 0.0 )
  {
    if ( epsPlane_4 * endPoint->y + epsPlane_8 * endPoint->z + epsPlane * endPoint->x + epsPlane_12 >= 0.0 )
      return 0;
    v18 = endPoint->x - origin->x;
    v19 = endPoint->y - origin->y;
    v20 = endPoint->z - origin->z;
    *(float *)&v105 = v19 * tw->axis.z - v20 * tw->axis.y;
    *((float *)&v105 + 1) = v20 * tw->axis.x - v18 * tw->axis.z;
    v21 = v18 * tw->axis.y;
    v22 = v19 * tw->axis.x;
    *(_QWORD *)&endDir->x = v105;
    v23 = v21 - v22;
    endDir->z = v21 - v22;
    if ( angle < 0.0 )
    {
      startDir_8 = -v23;
      endDir->z = startDir_8;
      endDir->x = -*(float *)&v105;
      endDir->y = -*((float *)&v105 + 1);
    }
    if ( epsPlane_4 * endDir->y + epsPlane * endDir->x + epsPlane_8 * endDir->z > 0.0 )
      return 0;
    v10 = plane;
  }
  if ( epsPlane * point->x + epsPlane_4 * point->y + epsPlane_8 * point->z + epsPlane_12 <= 0.000099999997 )
  {
    v36 = point->x - tw->origin.x;
    v37 = point->y - tw->origin.y;
    v38 = point->z - tw->origin.z;
    startDira = v38 * tw->matrix.mat[2].x + v37 * tw->matrix.mat[1].x + v36 * tw->matrix.mat[0].x;
    v39 = v38 * tw->matrix.mat[2].y + v37 * tw->matrix.mat[1].y + v36 * tw->matrix.mat[0].y;
    v40 = tw->matrix.mat[2].x * v10->c + tw->matrix.mat[1].x * v10->b + tw->matrix.mat[0].x * v10->a;
    v41 = tw->matrix.mat[2].y * v10->c + tw->matrix.mat[1].y * v10->b + tw->matrix.mat[0].y * v10->a;
    v87 = v39 * v40 - v41 * startDira;
    v42 = v39 * v41 + v40 * startDira;
    if ( angle >= 0.0 )
      v43 = v87;
    else
      v43 = -v87;
    dira = v43;
    if ( v43 <= 0.0 )
      goto LABEL_53;
    v92 = -v87;
    v44 = -v42;
    if ( v92 == 0.0 )
    {
      if ( v44 == 0.0 )
        return 0;
      v45 = -(v87 / (v44 + v44));
      v46 = 1.0e10;
    }
    else
    {
      v47 = v44 * v44 - v92 * v87;
      if ( v47 <= 0.0 )
        return 0;
      v48 = sqrt(v47);
      if ( v44 <= 0.0 )
      {
        v49 = v48;
        v50 = v44;
        v44 = v49;
        v48 = -v50;
      }
      startTand = v48 - v44;
      v45 = startTand / v92;
      v46 = v87 / startTand;
    }
    v88 = v46;
    if ( angle < 0.0 )
    {
      v45 = -v45;
      v88 = -v46;
    }
    if ( v45 < 0.0 && v88 < 0.0 )
      return 0;
    if ( v45 <= v88 )
      startTana = v88;
    else
      startTana = v45;
    if ( angle < 0.0 )
      startTana = -startTana;
    if ( dira <= 0.0 )
    {
LABEL_53:
      v24 = tanHalfAngle;
      *tanHalfAngle = 0.0;
      goto LABEL_70;
    }
    v51 = fabs(startTana);
    if ( v51 >= tw->maxTan )
      return 0;
    v89 = v51;
    v24 = tanHalfAngle;
    dirb = tw->maxTan;
    *tanHalfAngle = dirb;
    v53 = point->x - tw->origin.x;
    v54 = point->y - tw->origin.y;
    v55 = point->z - tw->origin.z;
    startDirb = v55 * tw->matrix.mat[2].x + v54 * tw->matrix.mat[1].x + v53 * tw->matrix.mat[0].x;
    startDir_4 = v55 * tw->matrix.mat[2].y + v54 * tw->matrix.mat[1].y + v53 * tw->matrix.mat[0].y;
    v114 = epsPlane_4 * tw->matrix.mat[1].x + epsPlane_8 * tw->matrix.mat[2].x + epsPlane * tw->matrix.mat[0].x;
    v115 = epsPlane_4 * tw->matrix.mat[1].y + epsPlane_8 * tw->matrix.mat[2].y + epsPlane * tw->matrix.mat[0].y;
    epsPlanec = epsPlane_4 * tw->origin.y
              + epsPlane_8 * tw->origin.z
              + epsPlane * tw->origin.x
              + epsPlane_12
              + (epsPlane_4 * tw->matrix.mat[1].z + epsPlane_8 * tw->matrix.mat[2].z + epsPlane * tw->matrix.mat[0].z)
              * (v55 * tw->matrix.mat[2].z + v54 * tw->matrix.mat[1].z + v53 * tw->matrix.mat[0].z);
    v107 = v115 * startDir_4 + v114 * startDirb;
    v93 = epsPlanec - v107;
    v56 = startDir_4 * v114 - v115 * startDirb;
    epsPlanea = v107 + epsPlanec;
    if ( v93 == 0.0 )
    {
      if ( v56 != 0.0 )
      {
        v57 = -(epsPlanea / (v56 + v56));
        v58 = 1.0e10;
LABEL_61:
        startTanb = v58;
        if ( angle < 0.0 )
        {
          v57 = -v57;
          startTanb = -v58;
        }
        if ( v57 >= v89 && v57 < dirb )
          *tanHalfAngle = v57;
        if ( v89 > startTanb || *tanHalfAngle <= startTanb )
          goto LABEL_27;
        v35 = startTanb;
        goto LABEL_26;
      }
    }
    else
    {
      v59 = v56 * v56 - epsPlanea * v93;
      if ( v59 > 0.0 )
      {
        v60 = sqrt(v59);
        if ( v56 <= 0.0 )
        {
          v61 = v60;
          v62 = v56;
          v56 = v61;
          v60 = -v62;
        }
        startTane = v60 - v56;
        v57 = startTane / v93;
        v58 = epsPlanea / startTane;
        goto LABEL_61;
      }
    }
    *tanHalfAngle = startTana;
    goto LABEL_70;
  }
  v24 = tanHalfAngle;
  dir = tw->maxTan;
  *tanHalfAngle = dir;
  v25 = point->x - tw->origin.x;
  v26 = point->y - tw->origin.y;
  v27 = point->z - tw->origin.z;
  startTanc = v27 * tw->matrix.mat[2].x + v26 * tw->matrix.mat[1].x + v25 * tw->matrix.mat[0].x;
  startTan_4 = v25 * tw->matrix.mat[0].y + v27 * tw->matrix.mat[2].y + v26 * tw->matrix.mat[1].y;
  v106 = epsPlane_4 * tw->matrix.mat[1].x + epsPlane_8 * tw->matrix.mat[2].x + epsPlane * tw->matrix.mat[0].x;
  v110 = epsPlane_4 * tw->matrix.mat[1].y + epsPlane_8 * tw->matrix.mat[2].y + epsPlane * tw->matrix.mat[0].y;
  epsPlaneb = epsPlane_4 * tw->origin.y
            + epsPlane_8 * tw->origin.z
            + epsPlane * tw->origin.x
            + epsPlane_12
            + (epsPlane_4 * tw->matrix.mat[1].z + epsPlane_8 * tw->matrix.mat[2].z + epsPlane * tw->matrix.mat[0].z)
            * (v25 * tw->matrix.mat[0].z + v27 * tw->matrix.mat[2].z + v26 * tw->matrix.mat[1].z);
  v90 = v110 * startTan_4 + v106 * startTanc;
  v85 = epsPlaneb - v90;
  v28 = startTan_4 * v106 - v110 * startTanc;
  startTan = v90 + epsPlaneb;
  if ( v85 != 0.0 )
  {
    v31 = v28 * v28 - startTan * v85;
    if ( v31 > 0.0 )
    {
      v32 = sqrt(v31);
      if ( v28 <= 0.0 )
      {
        v33 = v32;
        v34 = v28;
        v28 = v33;
        v32 = -v34;
      }
      v91 = v32 - v28;
      v29 = v91 / v85;
      v30 = startTan / v91;
      goto LABEL_18;
    }
    return 0;
  }
  if ( v28 == 0.0 )
    return 0;
  v29 = -(startTan / (v28 + v28));
  v30 = 1.0e10;
LABEL_18:
  v86 = v30;
  if ( angle < 0.0 )
  {
    v29 = -v29;
    v86 = -v30;
  }
  if ( v29 >= 0.0 && v29 < dir )
    *tanHalfAngle = v29;
  if ( v86 < 0.0 || *tanHalfAngle <= v86 )
    goto LABEL_27;
  v35 = v86;
LABEL_26:
  *v24 = v35;
LABEL_27:
  if ( angle < 0.0 )
    *v24 = -*v24;
LABEL_70:
  if ( fabs(*v24) >= tw->maxTan )
    return 0;
  *collisionPoint = *point;
  if ( *v24 != 0.0 )
  {
    v63 = *v24;
    v64 = 1.0 / (v63 * v63 + 1.0);
    collisionPoint->x = collisionPoint->x - tw->origin.x;
    collisionPoint->y = collisionPoint->y - tw->origin.y;
    v65 = collisionPoint->z - tw->origin.z;
    collisionPoint->z = v65;
    v66 = tw->axis.x * collisionPoint->x + v65 * tw->axis.z + collisionPoint->y * tw->axis.y;
    epsPlaned = v66 * tw->axis.x;
    epsPlane_4a = v66 * tw->axis.y;
    epsPlane_8a = v66 * tw->axis.z;
    v108 = collisionPoint->x - epsPlaned;
    v111 = collisionPoint->y - epsPlane_4a;
    v67 = v65 - epsPlane_8a;
    v113 = v67;
    v118 = v111 * tw->axis.x - v108 * tw->axis.y;
    startTanf = v64 * v63 + v64 * v63;
    startDirc = (v67 * tw->axis.y - v111 * tw->axis.z) * startTanf;
    startDir_4a = (v108 * tw->axis.z - v113 * tw->axis.x) * startTanf;
    startDir_8a = v118 * startTanf;
    v68 = (1.0 - v63 * v63) * v64;
    v116 = v111 * v68;
    v119 = v113 * v68;
    v120 = v119 - startDir_8a;
    startDird = v108 * v68 - startDirc + epsPlaned;
    startDir_4b = v116 - startDir_4a + epsPlane_4a;
    v69 = startDird + tw->origin.x;
    v70 = startDir_4b + tw->origin.y;
    startDir_8b = v120 + epsPlane_8a + tw->origin.z;
    collisionPoint->z = startDir_8b;
    collisionPoint->x = v69;
    collisionPoint->y = v70;
  }
  result = 1;
  startDir_8c = -plane->c;
  v71 = -plane->a;
  v72 = -plane->b;
  endDir->z = startDir_8c;
  endDir->x = v71;
  endDir->y = v72;
  return result;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::RotateTrmVertexThroughPolygon(struct cm_traceWork_t *,struct cm_polygon_t *,struct cm_trmVertex_t *,int)
void __thiscall idCollisionModelManagerLocal::RotateTrmVertexThroughPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_polygon_t *poly,
        cm_trmVertex_t *v,
        int vertexNum)
{
  cm_trmVertex_t *v6; // ebp
  cm_polygon_t *v7; // edx
  idBounds *p_rotationBounds; // ecx
  const idPlane *p_plane; // esi
  bool v10; // cc
  int *edges; // edi
  float *v12; // edx
  double v13; // st7
  idCollisionModelLocal *model; // eax
  float x; // edx
  float y; // eax
  float z; // edx
  idVec3 endDir; // [esp+Ch] [ebp-30h] BYREF
  idVec3 collisionPoint; // [esp+18h] [ebp-24h] BYREF
  idPluecker pl; // [esp+24h] [ebp-18h]
  cm_traceWork_t *twa; // [esp+40h] [ebp+4h]

  v6 = v;
  if ( tw->isConvex && tw->axisIntersectsTrm )
  {
    v7 = poly;
    if ( poly->plane.c * v->p.z + poly->plane.b * v->p.y + poly->plane.a * v->p.x + poly->plane.d < 0.0 )
      return;
  }
  else
  {
    v7 = poly;
  }
  p_rotationBounds = &v->rotationBounds;
  v = (cm_trmVertex_t *)((char *)v + 72);
  if ( _mm_movemask_ps(
         _mm_and_ps(
           _mm_cmpnlt_ps(
             _mm_loadh_ps((const double *)&v6->rotationBounds.b[1].y),
             _mm_loadh_ps((const double *)&poly->bounds.b[0].y)),
           _mm_cmple_ps(
             _mm_loadh_ps((const double *)&v6->rotationBounds.b[0].y),
             _mm_loadh_ps((const double *)&poly->bounds.b[1].y)))) == 0xF )
  {
    p_plane = &v7->plane;
    if ( idBounds::PlaneSide(p_rotationBounds, &v7->plane, 0.1) == 3 )
    {
      if ( idCollisionModelManagerLocal::RotatePointThroughEpsilonPlane(
             this,
             tw,
             &v6->p,
             &v6->endp,
             p_plane,
             tw->angle,
             &v6->rotationOrigin,
             (float *)&v,
             &collisionPoint,
             &endDir) )
      {
        v10 = poly->numEdges <= 0;
        twa = 0;
        pl.p[0] = endDir.y * collisionPoint.x - collisionPoint.y * endDir.x;
        pl.p[1] = endDir.z * collisionPoint.x - collisionPoint.z * endDir.x;
        pl.p[2] = -endDir.x;
        pl.p[3] = endDir.z * collisionPoint.y - collisionPoint.z * endDir.y;
        pl.p[4] = -endDir.z;
        if ( !v10 )
        {
          edges = poly->edges;
          v12 = &tw->polygonEdgePlueckerCache[0].p[2];
          do
          {
            v13 = pl.p[0] * v12[2]
                + pl.p[4] * *(v12 - 2)
                + pl.p[2] * v12[1]
                + pl.p[1] * v12[3]
                + endDir.y * *(v12 - 1)
                + pl.p[3] * *v12;
            if ( *edges >= 0 )
            {
              if ( v13 < 0.0 )
                return;
            }
            else if ( v13 > 0.0 )
            {
              return;
            }
            twa = (cm_traceWork_t *)((char *)twa + 1);
            ++edges;
            v12 += 6;
          }
          while ( (int)twa < poly->numEdges );
        }
        tw->maxTan = fabs(*(float *)&v);
        tw->trace.c.normal.x = p_plane->a;
        tw->trace.c.normal.y = p_plane->b;
        tw->trace.c.normal.z = p_plane->c;
        tw->trace.c.dist = -poly->plane.d;
        tw->trace.c.separation = p_plane->c * v6->p.z + p_plane->b * v6->p.y + p_plane->a * v6->p.x + p_plane->d;
        tw->trace.c.contents = poly->contents;
        tw->trace.c.material = poly->material;
        model = tw->model;
        tw->trace.c.type = CONTACT_TRMVERTEX;
        tw->trace.c.modelFeature = poly - model->polygons;
        x = collisionPoint.x;
        tw->trace.c.trmFeature = ((char *)v6 - (char *)tw) / 96;
        y = collisionPoint.y;
        tw->trace.c.point.x = x;
        z = collisionPoint.z;
        tw->trace.c.point.y = y;
        tw->trace.c.point.z = z;
        idCollisionModelManagerLocal::CM_GetMaterialType(this, tw, poly);
      }
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::RotateVertexThroughTrmPolygon(struct cm_traceWork_t *,struct cm_trmPolygon_t *,struct cm_polygon_t *,struct cm_vertex_t *,class idVec3 &)
void __thiscall idCollisionModelManagerLocal::RotateVertexThroughTrmPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_trmPolygon_t *trmpoly,
        cm_polygon_t *poly,
        cm_vertex_t *v,
        idVec3 *rotationOrigin)
{
  cm_traceWork_t *v6; // ebx
  cm_trmPolygon_t *v7; // ebp
  cm_vertex_t *v8; // ecx
  cm_trmPolygon_t *p_p; // ecx
  __m128 v10; // xmm2
  int v11; // eax
  const idVec3 *v12; // edi
  unsigned __int8 v14; // c0
  unsigned __int8 v15; // c2
  bool v16; // zf
  float b; // eax
  float c; // edx
  float *p_x; // esi
  double v20; // st7
  double v21; // st6
  double v22; // st5
  double v23; // st7
  double v24; // st6
  double v25; // st5
  double v26; // st7
  int v27; // edi
  bool v28; // cc
  int *edges; // esi
  float *p_used; // eax
  double v31; // st7
  cm_polygon_t *v32; // esi
  double a; // st7
  double v34; // st6
  cm_trmPolygon_t *v35; // ecx
  idCollisionModelLocal *model; // edx
  cm_vertex_t *v37; // eax
  unsigned int v38; // edx
  float angle; // [esp+0h] [ebp-60h]
  cm_polygon_t *v40; // [esp+10h] [ebp-50h]
  idVec3 endDir; // [esp+30h] [ebp-30h] BYREF
  idPluecker pl; // [esp+3Ch] [ebp-24h] BYREF
  idVec3 collisionPoint; // [esp+54h] [ebp-Ch] BYREF

  v6 = tw;
  v7 = trmpoly;
  if ( tw->isConvex && tw->axisIntersectsTrm )
  {
    v8 = v;
    if ( v->p.z * trmpoly->plane.c + v->p.y * trmpoly->plane.b + trmpoly->plane.a * v->p.x + trmpoly->plane.d < 0.0 )
      return;
  }
  else
  {
    v8 = v;
  }
  p_p = (cm_trmPolygon_t *)&v8->p;
  trmpoly = p_p;
  LOBYTE(tw) = 0;
  v10 = _mm_loadh_ps((const double *)&p_p->plane.b);
  v11 = _mm_movemask_ps(
          _mm_and_ps(
            _mm_cmpnlt_ps(v10, _mm_loadh_ps((const double *)&v7->rotationBounds.b[0].y)),
            _mm_cmple_ps(v10, _mm_loadh_ps((const double *)&v7->rotationBounds.b[1].y)))) ^ 0xF;
  LOBYTE(tw) = v11 == 0;
  if ( !v11 )
  {
    v12 = rotationOrigin;
    if ( !(v14 | v15) )
    {
      v16 = !v6->modelVertexRotation.axisValid;
      b = p_p->plane.b;
      pl.p[0] = p_p->plane.a;
      c = p_p->plane.c;
      p_x = &v6->modelVertexRotation.origin.x;
      pl.p[1] = b;
      pl.p[2] = c;
      if ( v16 )
      {
        idRotation::ToMat3(&v6->modelVertexRotation);
        p_p = trmpoly;
      }
      v20 = pl.p[0] - *p_x;
      v21 = pl.p[1] - v6->modelVertexRotation.origin.y;
      v22 = pl.p[2] - v6->modelVertexRotation.origin.z;
      collisionPoint.x = v22 * v6->modelVertexRotation.axis.mat[2].x
                       + v21 * v6->modelVertexRotation.axis.mat[1].x
                       + v20 * v6->modelVertexRotation.axis.mat[0].x;
      collisionPoint.y = v22 * v6->modelVertexRotation.axis.mat[2].y
                       + v21 * v6->modelVertexRotation.axis.mat[1].y
                       + v20 * v6->modelVertexRotation.axis.mat[0].y;
      v23 = v22 * v6->modelVertexRotation.axis.mat[2].z
          + v21 * v6->modelVertexRotation.axis.mat[1].z
          + v20 * v6->modelVertexRotation.axis.mat[0].z;
      v24 = collisionPoint.x + *p_x;
      v25 = v23;
      v26 = collisionPoint.y + v6->modelVertexRotation.origin.y;
      collisionPoint.z = v25 + v6->modelVertexRotation.origin.z;
      pl.p[2] = collisionPoint.z;
      pl.p[0] = v24;
      pl.p[1] = v26;
      angle = -v6->angle;
      if ( idCollisionModelManagerLocal::RotatePointThroughEpsilonPlane(
             this,
             v6,
             (const idVec3 *)p_p,
             (const idVec3 *)&pl,
             &v7->plane,
             angle,
             v12,
             (float *)&tw,
             &collisionPoint,
             &endDir) )
      {
        v27 = 0;
        v28 = v7->numEdges <= 0;
        pl.p[0] = endDir.y * collisionPoint.x - collisionPoint.y * endDir.x;
        pl.p[1] = endDir.z * collisionPoint.x - collisionPoint.z * endDir.x;
        pl.p[2] = -endDir.x;
        pl.p[3] = endDir.z * collisionPoint.y - collisionPoint.z * endDir.y;
        pl.p[4] = -endDir.z;
        if ( !v28 )
        {
          edges = v7->edges;
          do
          {
            p_used = (float *)&v6->edges[abs32(*edges)].used;
            v31 = pl.p[3] * p_used[8]
                + pl.p[2] * p_used[9]
                + pl.p[1] * p_used[11]
                + endDir.y * p_used[7]
                + pl.p[0] * p_used[10]
                + pl.p[4] * p_used[6];
            if ( *edges >= 0 )
            {
              if ( v31 < 0.0 )
                return;
            }
            else if ( v31 > 0.0 )
            {
              return;
            }
            ++v27;
            ++edges;
          }
          while ( v27 < v7->numEdges );
        }
        v32 = poly;
        v40 = poly;
        v6->maxTan = fabs(*(float *)&tw);
        a = v7->plane.a;
        v34 = -v7->plane.b;
        collisionPoint.z = -v7->plane.c;
        v6->trace.c.normal.z = collisionPoint.z;
        v35 = trmpoly;
        v6->trace.c.normal.x = -a;
        v6->trace.c.normal.y = v34;
        v6->trace.c.dist = v35->plane.c * v6->trace.c.normal.z
                         + v35->plane.b * v6->trace.c.normal.y
                         + v35->plane.a * v6->trace.c.normal.x;
        v6->trace.c.separation = v35->plane.b * v7->plane.b
                               + v35->plane.c * v7->plane.c
                               + v7->plane.a * v35->plane.a
                               + v7->plane.d;
        v6->trace.c.contents = v32->contents;
        model = v6->model;
        v6->trace.c.material = v32->material;
        v37 = v;
        v6->trace.c.type = CONTACT_MODELVERTEX;
        v38 = (int)((unsigned __int64)(715827883i64 * ((char *)v37 - (char *)model->vertices)) >> 32) >> 2;
        v6->trace.c.modelFeature = v38 + (v38 >> 31);
        v6->trace.c.trmFeature = ((char *)v7 - (char *)v6 - 6240) / 112;
        v6->trace.c.point.x = v35->plane.a;
        v6->trace.c.point.y = v35->plane.b;
        v6->trace.c.point.z = v35->plane.c;
        idCollisionModelManagerLocal::CM_GetMaterialType(this, v6, v40);
      }
    }
  }
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::RotateTrmThroughPolygon(struct cm_traceWork_t *,struct cm_polygon_t *)
bool __thiscall idCollisionModelManagerLocal::RotateTrmThroughPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_polygon_t *p)
{
  int checkCount; // eax
  cm_polygon_t *v4; // ebx
  int v6; // eax
  int v7; // edi
  float *v8; // esi
  idCollisionModelLocal *model; // ecx
  __int64 v10; // rax
  cm_vertex_t *vertices; // ecx
  float *p_x; // ecx
  int v13; // esi
  cm_traceWork_t *v14; // edi
  int v15; // edi
  cm_trmEdge_t *v16; // esi
  int v17; // esi
  unsigned int v18; // ecx
  cm_edge_t *v19; // edx
  int v20; // eax
  bool v21; // zf
  int v22; // eax
  unsigned int v23; // ecx
  cm_vertex_t *v24; // ebx
  int v25; // eax
  __m128 v26; // xmm2
  int v27; // edi
  bool v28; // cc
  double v29; // st7
  double v30; // st6
  double v31; // st5
  double v32; // st7
  cm_trmPolygon_t *polys; // esi
  int k; // [esp+8h] [ebp-3Ch]
  int i; // [esp+Ch] [ebp-38h]
  unsigned int j; // [esp+10h] [ebp-34h]
  cm_edge_t *e; // [esp+1Ch] [ebp-28h]
  float v39; // [esp+20h] [ebp-24h]
  float v40; // [esp+24h] [ebp-20h]
  idVec3 rotationOrigin; // [esp+2Ch] [ebp-18h] BYREF
  float v42; // [esp+40h] [ebp-4h]

  checkCount = this->checkCount;
  v4 = p;
  if ( p->checkcount == checkCount )
    return 0;
  p->checkcount = checkCount;
  if ( (tw->contents & p->contents) == 0 )
    return 0;
  if ( _mm_movemask_ps(
         _mm_and_ps(
           _mm_cmpnlt_ps(
             _mm_loadh_ps((const double *)&tw->traceBounds.b[1].y),
             _mm_loadh_ps((const double *)&p->bounds.b[0].y)),
           _mm_cmple_ps(
             _mm_loadh_ps((const double *)&tw->traceBounds.b[0].y),
             _mm_loadh_ps((const double *)&p->bounds.b[1].y)))) != 0xF
    || tw->isConvex
    && tw->start.z * p->plane.c + tw->start.y * p->plane.b + tw->start.x * p->plane.a + p->plane.d < 0.0
    && tw->axisIntersectsTrm
    || fabs(idBounds::PlaneDistance(&p->bounds, &tw->heartPlane1)) > tw->maxDistFromHeartPlane1 )
  {
    return 0;
  }
  v6 = idBounds::PlaneSide(&tw->traceBounds, &p->plane, 0.1);
  if ( !v6 )
  {
    if ( tw->model->isConvex )
    {
      tw->quickExit = 1;
      return 1;
    }
    return 0;
  }
  if ( v6 != 3 )
    return 0;
  v7 = 0;
  if ( p->numEdges > 0 )
  {
    v8 = &tw->polygonEdgePlueckerCache[0].p[2];
    do
    {
      model = tw->model;
      v10 = p->edges[v7];
      HIDWORD(v10) = 9 * ((HIDWORD(v10) ^ v10) - HIDWORD(v10));
      LODWORD(v10) = model->edges;
      vertices = model->vertices;
      HIDWORD(v10) = v10 + 4 * HIDWORD(v10);
      LODWORD(v10) = &vertices[*(_DWORD *)(HIDWORD(v10) + 20)].p;
      p_x = &vertices[*(_DWORD *)(HIDWORD(v10) + 16)].p.x;
      ++v7;
      v8 += 6;
      *(v8 - 8) = *(float *)(v10 + 4) * *p_x - p_x[1] * *(float *)v10;
      *(v8 - 7) = *p_x * *(float *)(v10 + 8) - p_x[2] * *(float *)v10;
      *(v8 - 6) = *p_x - *(float *)v10;
      *(v8 - 5) = p_x[1] * *(float *)(v10 + 8) - *(float *)(v10 + 4) * p_x[2];
      *(v8 - 4) = p_x[2] - *(float *)(v10 + 8);
      *(v8 - 3) = *(float *)(v10 + 4) - p_x[1];
    }
    while ( v7 < p->numEdges );
  }
  if ( tw->pointTrace )
  {
    idCollisionModelManagerLocal::RotateTrmVertexThroughPolygon(this, tw, p, tw->vertices, 0);
  }
  else
  {
    v13 = 0;
    if ( tw->numVerts > 0 )
    {
      v14 = tw;
      do
      {
        if ( v14->vertices[0].used )
          idCollisionModelManagerLocal::RotateTrmVertexThroughPolygon(this, tw, p, v14->vertices, v13);
        ++v13;
        v14 = (cm_traceWork_t *)((char *)v14 + 96);
      }
      while ( v13 < tw->numVerts );
    }
    v15 = 1;
    if ( tw->numEdges >= 1 )
    {
      v16 = &tw->edges[1];
      do
      {
        if ( v16->used )
          idCollisionModelManagerLocal::RotateTrmEdgeThroughPolygon(this, tw, p, v16);
        ++v15;
        ++v16;
      }
      while ( v15 <= tw->numEdges );
    }
    v17 = 0;
    i = 0;
    if ( p->numEdges > 0 )
    {
      do
      {
        v18 = v4->edges[v17];
        v19 = &tw->model->edges[abs32(v18)];
        v20 = this->checkCount;
        e = v19;
        if ( v19->checkcount != v20 )
        {
          v21 = v19->internal == 0;
          v19->checkcount = v20;
          if ( v21 )
          {
            v22 = 0;
            v23 = v18 >> 31;
            k = 0;
            for ( j = v23; ; v23 = j )
            {
              v24 = &tw->model->vertices[v19->vertexNum[v22 ^ v23]];
              v25 = this->checkCount;
              if ( v24->checkcount != v25 )
              {
                v24->checkcount = v25;
                v26 = _mm_loadh_ps((const double *)&v24->p.y);
                if ( _mm_movemask_ps(
                       _mm_and_ps(
                         _mm_cmpnlt_ps(v26, _mm_loadh_ps((const double *)&tw->traceBounds.b[0].y)),
                         _mm_cmple_ps(v26, _mm_loadh_ps((const double *)&tw->traceBounds.b[1].y)))) == 0xF )
                {
                  v27 = 0;
                  v28 = tw->numPolys <= 0;
                  v29 = (v24->p.z - tw->origin.z) * tw->axis.z
                      + (v24->p.y - tw->origin.y) * tw->axis.y
                      + (v24->p.x - tw->origin.x) * tw->axis.x;
                  v39 = v29 * tw->axis.x;
                  v40 = v29 * tw->axis.y;
                  v30 = v39 + tw->origin.x;
                  v31 = v29 * tw->axis.z;
                  v32 = v40 + tw->origin.y;
                  v42 = v31 + tw->origin.z;
                  rotationOrigin.z = v42;
                  rotationOrigin.x = v30;
                  rotationOrigin.y = v32;
                  if ( !v28 )
                  {
                    polys = tw->polys;
                    do
                    {
                      if ( polys->used )
                      {
                        idCollisionModelManagerLocal::RotateVertexThroughTrmPolygon(
                          this,
                          tw,
                          polys,
                          p,
                          v24,
                          &rotationOrigin);
                        v19 = e;
                      }
                      ++v27;
                      ++polys;
                    }
                    while ( v27 < tw->numPolys );
                  }
                }
              }
              v22 = ++k;
              if ( k >= 2 )
                break;
            }
            v4 = p;
            v17 = i;
          }
        }
        i = ++v17;
      }
      while ( v17 < v4->numEdges );
    }
  }
  return tw->maxTan == 0.0;
}

// FUNC: bool __cdecl CM_RayIntersectsConvexTraceModel(struct cm_traceWork_t const *,class idVec3 const &,class idVec3 const &)
char __cdecl CM_RayIntersectsConvexTraceModel(
        const cm_traceWork_t *tw,
        const cm_trmPolygon_t *start,
        const idVec3 *dir)
{
  const idVec3 *v3; // ecx
  bool v5; // cc
  cm_trmPolygon_t *polys; // edx
  int numEdges; // ebp
  int v8; // ebx
  int *v9; // ecx
  idPluecker *v10; // eax
  idPluecker *v11; // eax
  idPluecker *v12; // eax
  idPluecker *v13; // eax
  int *v14; // edi
  idPluecker *p_pl; // eax
  int i; // [esp+10h] [ebp-1Ch]
  float plray; // [esp+14h] [ebp-18h]
  float plray_4; // [esp+18h] [ebp-14h]
  float plray_8; // [esp+1Ch] [ebp-10h]
  float plray_12; // [esp+20h] [ebp-Ch]
  float plray_16; // [esp+24h] [ebp-8h]
  float plray_20; // [esp+28h] [ebp-4h]
  cm_trmPolygon_t *twa; // [esp+30h] [ebp+4h]
  float poly; // [esp+34h] [ebp+8h]
  float polya; // [esp+34h] [ebp+8h]
  float polyb; // [esp+34h] [ebp+8h]
  float polyc; // [esp+34h] [ebp+8h]
  float polyd; // [esp+34h] [ebp+8h]

  v3 = dir;
  v5 = tw->numPolys <= 0;
  polys = tw->polys;
  twa = tw->polys;
  plray = start->plane.a * dir->y - dir->x * start->plane.b;
  i = 0;
  plray_4 = dir->z * start->plane.a - start->plane.c * dir->x;
  plray_8 = -dir->x;
  plray_20 = dir->y;
  plray_12 = dir->z * start->plane.b - start->plane.c * plray_20;
  plray_16 = -dir->z;
  if ( v5 )
    return 0;
  while ( polys->plane.c * v3->z + polys->plane.b * v3->y + polys->plane.a * v3->x >= 0.0 )
  {
LABEL_20:
    ++polys;
    v5 = ++i < tw->numPolys;
    twa = polys;
    if ( !v5 )
      return 0;
  }
  numEdges = polys->numEdges;
  v8 = 0;
  if ( numEdges < 4 )
  {
LABEL_10:
    if ( v8 >= numEdges )
      return 1;
    v14 = &twa->edges[v8];
    do
    {
      p_pl = &tw->edges[abs32(*v14)].pl;
      polyd = plray_20 * p_pl->p[1]
            + plray_12 * p_pl->p[2]
            + plray_8 * p_pl->p[3]
            + plray * p_pl->p[4]
            + plray_4 * p_pl->p[5]
            + plray_16 * p_pl->p[0];
      if ( (*v14 ^ LODWORD(polyd)) < 0 )
        break;
      ++v8;
      ++v14;
    }
    while ( v8 < numEdges );
  }
  else
  {
    v9 = &polys->edges[1];
    while ( 1 )
    {
      v10 = &tw->edges[abs32(*(v9 - 1))].pl;
      poly = plray_20 * v10->p[1]
           + plray_12 * v10->p[2]
           + plray_8 * v10->p[3]
           + plray * v10->p[4]
           + plray_4 * v10->p[5]
           + plray_16 * v10->p[0];
      if ( (*(v9 - 1) ^ LODWORD(poly)) < 0 )
        break;
      v11 = &tw->edges[abs32(*v9)].pl;
      polya = plray_20 * v11->p[1]
            + plray_12 * v11->p[2]
            + plray_8 * v11->p[3]
            + plray * v11->p[4]
            + plray_4 * v11->p[5]
            + plray_16 * v11->p[0];
      if ( (*v9 ^ LODWORD(polya)) < 0 )
      {
        ++v8;
        break;
      }
      v12 = &tw->edges[abs32(v9[1])].pl;
      polyb = plray_20 * v12->p[1]
            + plray_12 * v12->p[2]
            + plray_8 * v12->p[3]
            + plray * v12->p[4]
            + plray_4 * v12->p[5]
            + plray_16 * v12->p[0];
      if ( (v9[1] ^ LODWORD(polyb)) < 0 )
      {
        v8 += 2;
        break;
      }
      v13 = &tw->edges[abs32(v9[2])].pl;
      polyc = plray_20 * v13->p[1]
            + plray_12 * v13->p[2]
            + plray_8 * v13->p[3]
            + plray * v13->p[4]
            + plray_4 * v13->p[5]
            + plray_16 * v13->p[0];
      if ( (v9[2] ^ LODWORD(polyc)) < 0 )
      {
        v8 += 3;
        break;
      }
      v8 += 4;
      v9 += 4;
      if ( v8 >= numEdges - 3 )
        goto LABEL_10;
    }
  }
  v3 = dir;
  if ( v8 < numEdges )
  {
    polys = twa;
    goto LABEL_20;
  }
  return 1;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::Rotation180(struct trace_t *,class idVec3 const &,class idVec3 const &,float,float,class idVec3 const &,class idTraceModel const *,class idMat3 const &,int,class idCollisionModel *,class idVec3 const &,class idMat3 const &)
void __thiscall idCollisionModelManagerLocal::Rotation180(
        idCollisionModelManagerLocal *this,
        trace_t *results,
        const idVec3 *rorg,
        const idVec3 *axis,
        float startAngle,
        float endAngle,
        const idVec3 *start,
        const idTraceModel *trm,
        const idMat3 *trmAxis,
        int contentMask,
        idCollisionModelLocal *model,
        const idVec3 *modelOrigin,
        const idMat3 *modelAxis)
{
  double v13; // st7
  double v14; // st6
  double v15; // st5
  long double v16; // st4
  long double v17; // st6
  double z; // st7
  double v19; // st6
  double y; // st5
  double x; // st4
  double v22; // st3
  double v23; // st2
  long double v24; // st7
  double v25; // st7
  double v26; // st6
  const idTraceModel *v27; // edi
  double v28; // st7
  double v29; // st6
  double v30; // st5
  double v31; // st7
  double v32; // st6
  double v33; // st5
  double v34; // st7
  __m128 v35; // xmm0
  __m128 v36; // xmm1
  __m128 v37; // xmm2
  __m128 v38; // xmm3
  __m128 v39; // xmm4
  __m128 v40; // xmm5
  __m128 v41; // xmm4
  __m128 v42; // xmm7
  __m128 v43; // xmm5
  __m128 v44; // xmm4
  __m128 v45; // xmm6
  __m128 v46; // xmm7
  __m128 v47; // xmm3
  __m128 v48; // xmm4
  __m128 v49; // xmm7
  __m128 v50; // xmm5
  __m128 v51; // xmm6
  __m128 v52; // xmm5
  __m128 v53; // xmm6
  double v54; // st7
  float v55; // ecx
  float v56; // edx
  double v57; // st7
  float v58; // ecx
  float v59; // edx
  float v60; // eax
  double v61; // st7
  double v62; // st6
  double v63; // st5
  double v64; // st7
  double v65; // st6
  double v66; // st5
  double v67; // st7
  double v69; // st7
  double v70; // st6
  double v71; // st7
  double v72; // st6
  double v73; // st7
  double v74; // st6
  float v75; // edx
  double v76; // st6
  double v77; // st6
  float v78; // edx
  float v79; // edx
  float v80; // edx
  bool v81; // zf
  double v82; // st7
  double v83; // st6
  double v84; // st7
  double v85; // st6
  double v86; // st5
  double v87; // rt2
  double v88; // st5
  double v89; // st6
  double v90; // st5
  double v91; // st6
  double v92; // st5
  double v93; // st6
  double v94; // st5
  double v95; // st7
  double v96; // st6
  double v97; // st5
  double v98; // st7
  double v99; // st6
  double v100; // st5
  cm_traceWork_t *v101; // esi
  float *p_y; // eax
  double v103; // st7
  float *p_x; // edi
  float v105; // ecx
  double v106; // st7
  double v107; // st6
  double v108; // st5
  double v109; // st7
  double v110; // st6
  double v111; // st5
  double v112; // st7
  double v113; // st7
  double v114; // st6
  double v115; // st5
  double v116; // st4
  double v117; // st6
  double v118; // st7
  double v119; // st7
  double v120; // st7
  double v121; // st6
  double v122; // st5
  double v123; // st7
  float *v124; // ecx
  double v125; // st7
  double v126; // st5
  double v127; // st6
  __m128 v128; // xmm0
  __m128 v129; // xmm1
  __m128 v130; // xmm2
  __m128 v131; // xmm3
  __m128 v132; // xmm4
  __m128 v133; // xmm5
  __m128 v134; // xmm4
  __m128 v135; // xmm7
  __m128 v136; // xmm5
  __m128 v137; // xmm4
  __m128 v138; // xmm6
  __m128 v139; // xmm7
  __m128 v140; // xmm3
  __m128 v141; // xmm4
  __m128 v142; // xmm7
  __m128 v143; // xmm5
  __m128 v144; // xmm6
  __m128 v145; // xmm5
  __m128 v146; // xmm6
  unsigned __int8 v148; // c0
  unsigned __int8 v149; // c3
  char v150; // cc
  int *v151; // ecx
  float *v152; // eax
  int v153; // edx
  int v154; // ecx
  int v155; // esi
  idVec3 *v156; // edx
  idVec3 *v157; // edi
  double v158; // st7
  double v159; // st7
  float *v160; // esi
  float *v161; // edi
  float *p_b; // ecx
  cm_trmVertex_t *v163; // eax
  int v164; // esi
  int v165; // edx
  traceModel_t *v166; // esi
  traceModel_t type; // edi
  double v168; // st7
  double v169; // st7
  unsigned int v170; // eax
  float *v171; // eax
  double v172; // st7
  double v173; // st6
  unsigned int v174; // eax
  int v175; // ecx
  float v176; // xmm0_4
  float v177; // xmm1_4
  float v178; // xmm2_4
  float v179; // xmm3_4
  float v180; // xmm4_4
  float v181; // xmm5_4
  unsigned int v182; // eax
  float *v183; // edi
  __m128 v184; // xmm0
  __m128 v185; // xmm1
  __m128 v186; // xmm2
  __m128 v187; // xmm3
  __m128 v188; // xmm1
  double v189; // st7
  float v190; // ecx
  float v191; // edx
  double v192; // st7
  float v193; // ecx
  float v194; // edx
  float v195; // eax
  double v196; // st7
  double v197; // st6
  double v198; // st5
  double v199; // st7
  double v200; // st6
  double v201; // st5
  double v202; // st7
  float *v203; // eax
  float *v204; // ecx
  float *v205; // edx
  int v206; // esi
  double v207; // st7
  double v208; // st6
  float v209; // eax
  float v210; // edx
  float v211; // eax
  float v212; // edx
  float v213; // eax
  float v214; // edx
  float v215; // eax
  float v216; // edx
  double v218; // st7
  double v219; // st6
  double v220; // st7
  double v221; // st6
  idVec3 zverts[32]; // [esp+0h] [ebp-2E0h] BYREF
  float v223; // [esp+188h] [ebp-158h]
  float v224; // [esp+194h] [ebp-14Ch]
  float v225; // [esp+1A0h] [ebp-140h]
  float v226; // [esp+1ACh] [ebp-134h]
  float v227; // [esp+1B0h] [ebp-130h]
  float initialTan; // [esp+1B4h] [ebp-12Ch]
  idCollisionModelManagerLocal *v229; // [esp+1B8h] [ebp-128h]
  idRotation startRotation; // [esp+1BCh] [ebp-124h] BYREF
  idVec3 *p_rotationOrigin; // [esp+200h] [ebp-E0h]
  idBounds *p_rotationBounds; // [esp+204h] [ebp-DCh]
  float v233; // [esp+208h] [ebp-D8h]
  idMat3x4 trmTransform; // [esp+20Ch] [ebp-D4h] BYREF
  float v235; // [esp+23Ch] [ebp-A4h]
  idRotation endRotation; // [esp+240h] [ebp-A0h] BYREF
  float v237; // [esp+284h] [ebp-5Ch]
  idMat3 invModelAxis; // [esp+288h] [ebp-58h] BYREF
  float v239; // [esp+2ACh] [ebp-34h]
  float v240; // [esp+2B0h] [ebp-30h]
  float v241; // [esp+2B4h] [ebp-2Ch]
  float v242; // [esp+2B8h] [ebp-28h]
  float v243; // [esp+2BCh] [ebp-24h]
  float v244; // [esp+2C0h] [ebp-20h]
  float v245; // [esp+2C4h] [ebp-1Ch]
  idVec3 v246; // [esp+2C8h] [ebp-18h]
  idVec3 v247; // [esp+2D4h] [ebp-Ch]
  float ic; // [esp+2F8h] [ebp+18h]
  int i; // [esp+2F8h] [ebp+18h]
  int ia; // [esp+2F8h] [ebp+18h]
  int ib; // [esp+2F8h] [ebp+18h]
  const idTraceModel *trma; // [esp+300h] [ebp+20h]
  float *trmb; // [esp+300h] [ebp+20h]
  float trmc; // [esp+300h] [ebp+20h]
  float *i1; // [esp+304h] [ebp+24h]
  int i1b; // [esp+304h] [ebp+24h]
  float *i1a; // [esp+304h] [ebp+24h]
  char model_rotated_3; // [esp+30Bh] [ebp+2Bh]
  float vertc; // [esp+30Ch] [ebp+2Ch]
  cm_traceWork_t *vert; // [esp+30Ch] [ebp+2Ch]
  cm_trmVertex_t *verta; // [esp+30Ch] [ebp+2Ch]
  cm_trmVertex_t *vertb; // [esp+30Ch] [ebp+2Ch]

  v229 = this;
  if ( (_S5_40 & 1) == 0 )
    _S5_40 |= 1u;
  ++this->checkCount;
  tw_0.contents = contentMask;
  v227 = endAngle - startAngle;
  tw_0.model = model;
  tw_0.angle = v227;
  tw_0.trace.fraction = 1.0;
  tw_0.isConvex = 1;
  tw_0.rotation = 1;
  tw_0.trace.c.contents = 0;
  tw_0.trace.c.type = CONTACT_NONE;
  tw_0.trace.c.material = 0;
  tw_0.trace.c.materialType = 0;
  tw_0.positionTest = 0;
  tw_0.axisIntersectsTrm = 0;
  tw_0.quickExit = 0;
  initialTan = fabs(tan(3.1415927 * 0.0027777778 * v227));
  tw_0.maxTan = initialTan;
  v246.x = start->x - modelOrigin->x;
  v246.y = start->y - modelOrigin->y;
  v246.z = start->z - modelOrigin->z;
  tw_0.start = v246;
  tw_0.axis = *axis;
  v13 = rorg->x - modelOrigin->x;
  v14 = rorg->y - modelOrigin->y;
  v241 = rorg->z - modelOrigin->z;
  v15 = tw_0.axis.z * v241
      + tw_0.axis.y * v14
      + v13 * tw_0.axis.x
      - (tw_0.axis.z * v246.z
       + tw_0.axis.y * v246.y
       + v246.x * tw_0.axis.x);
  v243 = tw_0.axis.y * v15;
  v244 = tw_0.axis.z * v15;
  v247.x = v13 - tw_0.axis.x * v15;
  v247.y = v14 - v243;
  v247.z = v241 - v244;
  tw_0.origin = v247;
  v16 = sqrt(
          (v246.z - v247.z) * (v246.z - v247.z)
        + (v246.y - v247.y) * (v246.y - v247.y)
        + (v246.x - v247.x) * (v246.x - v247.x));
  tw_0.radius = v16;
  v17 = v16 * v16 - 1024.0;
  if ( v17 <= 0.0 )
    tw_0.maxErr = v16;
  else
    tw_0.maxErr = v16 - sqrt(v17);
  if ( LODWORD(modelAxis->mat[0].x) == 1065353216
    && LODWORD(modelAxis->mat[1].y) == 1065353216
    && LODWORD(modelAxis->mat[2].z) == 1065353216 )
  {
    model_rotated_3 = 0;
  }
  else
  {
    z = modelAxis->mat[2].z;
    v19 = modelAxis->mat[0].z;
    v233 = modelAxis->mat[1].z;
    y = modelAxis->mat[0].y;
    x = modelAxis->mat[0].x;
    v235 = modelAxis->mat[2].y;
    invModelAxis.mat[0].x = x;
    vertc = modelAxis->mat[1].y;
    invModelAxis.mat[1].x = y;
    v245 = modelAxis->mat[2].x;
    invModelAxis.mat[2].x = v19;
    v237 = modelAxis->mat[1].x;
    invModelAxis.mat[2].z = z;
    invModelAxis.mat[0].y = v237;
    invModelAxis.mat[0].z = v245;
    invModelAxis.mat[1].y = vertc;
    invModelAxis.mat[1].z = v235;
    model_rotated_3 = 1;
    invModelAxis.mat[2].y = v233;
    v22 = tw_0.axis.x * x + tw_0.axis.y * y + tw_0.axis.z * v19;
    v23 = v237 * tw_0.axis.x + tw_0.axis.y * vertc + tw_0.axis.z * v233;
    tw_0.axis.z = v245 * tw_0.axis.x + tw_0.axis.y * v235 + tw_0.axis.z * z;
    tw_0.axis.x = v22;
    tw_0.axis.y = v23;
    tw_0.origin.z = v247.y * v235 + v247.z * z + v245 * v247.x;
    tw_0.origin.x = v247.y * y + v247.z * v19 + x * v247.x;
    tw_0.origin.y = v247.y * vertc + v247.z * v233 + v237 * v247.x;
  }
  startRotation.origin = tw_0.origin;
  v24 = tw_0.axis.x * tw_0.axis.x + tw_0.axis.y * tw_0.axis.y;
  startRotation.vec = tw_0.axis;
  startRotation.angle = startAngle;
  endRotation.origin = tw_0.origin;
  endRotation.vec = tw_0.axis;
  endRotation.angle = endAngle;
  startRotation.axisValid = 0;
  endRotation.axisValid = 0;
  if ( v24 == 0.0 )
  {
    v25 = 1.0;
    v26 = 0.0;
  }
  else
  {
    ic = 1.0 / sqrt(v24);
    v25 = -(tw_0.axis.y * ic);
    v26 = ic * tw_0.axis.x;
  }
  v27 = trm;
  tw_0.matrix.mat[0].z = tw_0.axis.x;
  tw_0.matrix.mat[1].z = tw_0.axis.y;
  tw_0.matrix.mat[2].x = 0.0;
  tw_0.matrix.mat[2].z = tw_0.axis.z;
  v247.x = tw_0.axis.z * v26 - tw_0.axis.y * 0.0;
  v247.y = tw_0.axis.x * 0.0 - tw_0.axis.z * v25;
  v247.z = tw_0.axis.y * v25 - v26 * tw_0.axis.x;
  tw_0.matrix.mat[0].x = v25;
  tw_0.matrix.mat[1].x = v26;
  tw_0.matrix.mat[0].y = -v247.x;
  tw_0.matrix.mat[1].y = -v247.y;
  tw_0.matrix.mat[2].y = -v247.z;
  if ( trm )
  {
    tw_0.pointTrace = 0;
    tw_0.isConvex = trm->isConvex;
    v73 = start->x - modelOrigin->x;
    trmTransform.mat[0] = trmAxis->mat[0].x;
    trmTransform.mat[1] = trmAxis->mat[1].x;
    v247.x = v73;
    v74 = start->y - modelOrigin->y;
    trmTransform.mat[2] = trmAxis->mat[2].x;
    LODWORD(v235) = &trmAxis->mat[0].y;
    v75 = trmAxis->mat[0].y;
    v247.y = v74;
    v76 = start->z;
    trmTransform.mat[4] = v75;
    v77 = v76 - modelOrigin->z;
    trmTransform.mat[5] = trmAxis->mat[1].y;
    v78 = trmAxis->mat[2].y;
    v247.z = v77;
    trmTransform.mat[6] = v78;
    v79 = trmAxis->mat[0].z;
    trmTransform.mat[3] = v73;
    trmTransform.mat[8] = v79;
    trmTransform.mat[9] = trmAxis->mat[1].z;
    v80 = trmAxis->mat[2].z;
    trmTransform.mat[7] = v247.y;
    trmTransform.mat[10] = v80;
    v81 = LODWORD(trmAxis->mat[0].x) == 1065353216;
    trmTransform.mat[11] = v247.z;
    if ( v81 && LODWORD(trmAxis->mat[1].y) == 1065353216 && LODWORD(trmAxis->mat[2].z) == 1065353216 )
    {
      tw_0.start.x = v246.x + trm->offset.x;
      tw_0.start.y = v246.y + trm->offset.y;
      v84 = v246.z + trm->offset.z;
    }
    else
    {
      v82 = trmAxis->mat[2].x * trm->offset.z + trmAxis->mat[0].x * trm->offset.x + trm->offset.y * trmAxis->mat[1].x;
      v83 = trmAxis->mat[1].y * trm->offset.y
          + trm->offset.z * trmAxis->mat[2].y
          + *(float *)LODWORD(v235) * trm->offset.x;
      v241 = trmAxis->mat[1].z * trm->offset.y + trmAxis->mat[2].z * trm->offset.z + trmAxis->mat[0].z * trm->offset.x;
      tw_0.start.x = v82 + v246.x;
      tw_0.start.y = v83 + v246.y;
      v84 = v241 + v246.z;
    }
    tw_0.start.z = v84;
    if ( model_rotated_3 )
    {
      v85 = invModelAxis.mat[2].x * v84 + tw_0.start.y * invModelAxis.mat[1].x + invModelAxis.mat[0].x * tw_0.start.x;
      v86 = v84 * invModelAxis.mat[2].z + tw_0.start.y * invModelAxis.mat[1].z + invModelAxis.mat[0].z * tw_0.start.x;
      tw_0.start.z = v86;
      v87 = v86;
      v88 = v84 * invModelAxis.mat[2].y + tw_0.start.y * invModelAxis.mat[1].y + invModelAxis.mat[0].y * tw_0.start.x;
      v84 = v87;
      tw_0.start.x = v85;
      tw_0.start.y = v88;
      v89 = trmTransform.mat[8] * invModelAxis.mat[2].x
          + trmTransform.mat[0] * invModelAxis.mat[0].x
          + trmTransform.mat[4] * invModelAxis.mat[1].x;
      v90 = trmTransform.mat[8] * invModelAxis.mat[2].y
          + trmTransform.mat[0] * invModelAxis.mat[0].y
          + trmTransform.mat[4] * invModelAxis.mat[1].y;
      trmTransform.mat[8] = trmTransform.mat[8] * invModelAxis.mat[2].z
                          + trmTransform.mat[0] * invModelAxis.mat[0].z
                          + trmTransform.mat[4] * invModelAxis.mat[1].z;
      trmTransform.mat[4] = v90;
      trmTransform.mat[0] = v89;
      v91 = trmTransform.mat[9] * invModelAxis.mat[2].x
          + trmTransform.mat[5] * invModelAxis.mat[1].x
          + trmTransform.mat[1] * invModelAxis.mat[0].x;
      v92 = trmTransform.mat[9] * invModelAxis.mat[2].y
          + trmTransform.mat[5] * invModelAxis.mat[1].y
          + trmTransform.mat[1] * invModelAxis.mat[0].y;
      trmTransform.mat[9] = trmTransform.mat[9] * invModelAxis.mat[2].z
                          + trmTransform.mat[5] * invModelAxis.mat[1].z
                          + trmTransform.mat[1] * invModelAxis.mat[0].z;
      trmTransform.mat[5] = v92;
      trmTransform.mat[1] = v91;
      v93 = trmTransform.mat[10] * invModelAxis.mat[2].x
          + trmTransform.mat[6] * invModelAxis.mat[1].x
          + trmTransform.mat[2] * invModelAxis.mat[0].x;
      v94 = trmTransform.mat[10] * invModelAxis.mat[2].y
          + trmTransform.mat[6] * invModelAxis.mat[1].y
          + trmTransform.mat[2] * invModelAxis.mat[0].y;
      trmTransform.mat[10] = trmTransform.mat[10] * invModelAxis.mat[2].z
                           + trmTransform.mat[6] * invModelAxis.mat[1].z
                           + trmTransform.mat[2] * invModelAxis.mat[0].z;
      trmTransform.mat[6] = v94;
      trmTransform.mat[2] = v93;
      trmTransform.mat[11] = v247.x * invModelAxis.mat[0].z
                           + v247.z * invModelAxis.mat[2].z
                           + v247.y * invModelAxis.mat[1].z;
      trmTransform.mat[7] = v247.x * invModelAxis.mat[0].y
                          + v247.z * invModelAxis.mat[2].y
                          + v247.y * invModelAxis.mat[1].y;
      trmTransform.mat[3] = v247.x * invModelAxis.mat[0].x
                          + v247.z * invModelAxis.mat[2].x
                          + v247.y * invModelAxis.mat[1].x;
    }
    tw_0.end.z = v84;
    tw_0.end.x = tw_0.start.x;
    tw_0.end.y = tw_0.start.y;
    idRotation::ToMat3(&endRotation);
    v95 = tw_0.end.x - endRotation.origin.x;
    v96 = tw_0.end.y - endRotation.origin.y;
    v97 = tw_0.end.z - endRotation.origin.z;
    v242 = v95 * endRotation.axis.mat[0].x + endRotation.axis.mat[2].x * v97 + v96 * endRotation.axis.mat[1].x;
    v243 = v95 * endRotation.axis.mat[0].y + v96 * endRotation.axis.mat[1].y + v97 * endRotation.axis.mat[2].y;
    v241 = v95 * endRotation.axis.mat[0].z
         + v96 * endRotation.axis.mat[1].z
         + v97 * endRotation.axis.mat[2].z
         + endRotation.origin.z;
    tw_0.end.z = v241;
    tw_0.end.x = endRotation.origin.x + v242;
    tw_0.end.y = v243 + endRotation.origin.y;
    if ( startAngle != 0.0 )
    {
      idRotation::ToMat3(&startRotation);
      v98 = tw_0.start.x - startRotation.origin.x;
      v99 = tw_0.start.y - startRotation.origin.y;
      v100 = tw_0.start.z - startRotation.origin.z;
      v242 = startRotation.axis.mat[2].x * v100 + startRotation.axis.mat[1].x * v99 + startRotation.axis.mat[0].x * v98;
      v243 = startRotation.axis.mat[2].y * v100 + startRotation.axis.mat[1].y * v99 + startRotation.axis.mat[0].y * v98;
      v241 = startRotation.axis.mat[2].z * v100
           + startRotation.axis.mat[1].z * v99
           + startRotation.axis.mat[0].z * v98
           + startRotation.origin.z;
      tw_0.start.z = v241;
      tw_0.start.x = startRotation.origin.x + v242;
      tw_0.start.y = v243 + startRotation.origin.y;
    }
    tw_0.heartPlane1.a = tw_0.axis.x;
    tw_0.heartPlane1.b = tw_0.axis.y;
    tw_0.heartPlane1.c = tw_0.axis.z;
    tw_0.maxDistFromHeartPlane1 = 0.0;
    v101 = &tw_0;
    vert = &tw_0;
    i = 0;
    tw_0.heartPlane1.d = -(tw_0.axis.x * tw_0.start.x + tw_0.axis.z * tw_0.start.z + tw_0.axis.y * tw_0.start.y);
    tw_0.numVerts = trm->numVerts;
    if ( tw_0.numVerts > 0 )
    {
      v245 = COERCE_FLOAT((idVec3 *)&zverts[0].z);
      p_y = &trm->verts[0].y;
      i1 = &trm->verts[0].y;
      while ( 1 )
      {
        v81 = !endRotation.axisValid;
        v103 = trmTransform.mat[0] * *(p_y - 1);
        p_x = &v101->vertices[0].endp.x;
        LODWORD(v237) = &v101->vertices[0].endp;
        v101->vertices[0].p.x = v103 + trmTransform.mat[2] * p_y[1] + trmTransform.mat[1] * *p_y + trmTransform.mat[3];
        v105 = v101->vertices[0].p.x;
        v101->vertices[0].p.y = trmTransform.mat[6] * p_y[1]
                              + trmTransform.mat[4] * *(p_y - 1)
                              + trmTransform.mat[5] * *p_y
                              + trmTransform.mat[7];
        v101->vertices[0].p.z = trmTransform.mat[10] * p_y[1]
                              + trmTransform.mat[8] * *(p_y - 1)
                              + trmTransform.mat[9] * *p_y
                              + trmTransform.mat[11];
        v101->vertices[0].endp.x = v105;
        v101->vertices[0].endp.y = v101->vertices[0].p.y;
        v101->vertices[0].endp.z = v101->vertices[0].p.z;
        if ( v81 )
          idRotation::ToMat3(&endRotation);
        v106 = *p_x - endRotation.origin.x;
        v107 = v101->vertices[0].endp.y - endRotation.origin.y;
        v108 = v101->vertices[0].endp.z - endRotation.origin.z;
        v242 = v106 * endRotation.axis.mat[0].x + endRotation.axis.mat[2].x * v108 + v107 * endRotation.axis.mat[1].x;
        v243 = v106 * endRotation.axis.mat[0].y + v107 * endRotation.axis.mat[1].y + v108 * endRotation.axis.mat[2].y;
        v109 = v106 * endRotation.axis.mat[0].z + v107 * endRotation.axis.mat[1].z + v108 * endRotation.axis.mat[2].z;
        v110 = endRotation.origin.x + v242;
        v111 = v109;
        v112 = v243 + endRotation.origin.y;
        v225 = v111 + endRotation.origin.z;
        v101->vertices[0].endp.z = v225;
        *p_x = v110;
        v101->vertices[0].endp.y = v112;
        if ( startAngle != 0.0 )
        {
          if ( !startRotation.axisValid )
            idRotation::ToMat3(&startRotation);
          v113 = v101->vertices[0].p.x - startRotation.origin.x;
          v114 = v101->vertices[0].p.y - startRotation.origin.y;
          v115 = v101->vertices[0].p.z - startRotation.origin.z;
          v246.x = startRotation.axis.mat[2].x * v115
                 + startRotation.axis.mat[1].x * v114
                 + startRotation.axis.mat[0].x * v113;
          v246.y = startRotation.axis.mat[2].y * v115
                 + startRotation.axis.mat[1].y * v114
                 + startRotation.axis.mat[0].y * v113;
          v116 = startRotation.axis.mat[2].z * v115
               + startRotation.axis.mat[1].z * v114
               + startRotation.axis.mat[0].z * v113;
          v117 = startRotation.origin.x + v246.x;
          v118 = v246.y + startRotation.origin.y;
          v224 = v116 + startRotation.origin.z;
          v101->vertices[0].p.z = v224;
          v101->vertices[0].p.x = v117;
          v101->vertices[0].p.y = v118;
        }
        v119 = v101->vertices[0].p.x - tw_0.origin.x;
        p_rotationOrigin = &v101->vertices[0].rotationOrigin;
        v120 = v119 * tw_0.axis.x
             + (v101->vertices[0].p.z - tw_0.origin.z) * tw_0.axis.z
             + (v101->vertices[0].p.y - tw_0.origin.y) * tw_0.axis.y;
        v239 = tw_0.axis.x * v120;
        v240 = tw_0.axis.y * v120;
        v121 = v239 + tw_0.origin.x;
        v122 = v120 * tw_0.axis.z;
        v123 = v240 + tw_0.origin.y;
        v223 = v122 + tw_0.origin.z;
        v101->vertices[0].rotationOrigin.z = v223;
        v101->vertices[0].rotationOrigin.x = v121;
        v124 = (float *)LODWORD(v245);
        v101->vertices[0].rotationOrigin.y = v123;
        v125 = v101->vertices[0].p.x - tw_0.origin.x;
        v247.y = v101->vertices[0].p.y - tw_0.origin.y;
        v247.z = v101->vertices[0].p.z - tw_0.origin.z;
        v226 = tw_0.matrix.mat[0].z * v125 + v247.z * tw_0.matrix.mat[2].z + v247.y * tw_0.matrix.mat[1].z;
        v126 = tw_0.matrix.mat[0].x * v125 + v247.z * tw_0.matrix.mat[2].x + v247.y * tw_0.matrix.mat[1].x;
        v127 = tw_0.matrix.mat[0].y * v125 + v247.z * tw_0.matrix.mat[2].y + v247.y * tw_0.matrix.mat[1].y;
        *v124 = v226;
        *(v124 - 2) = v126;
        *(v124 - 1) = v127;
        tw_0.maxDistFromHeartPlane1 = fmaxf(
                                        COERCE_FLOAT(COERCE_UNSIGNED_INT(
                                                       (float)((float)(tw_0.heartPlane1.a * vert->vertices[0].p.x)
                                                             + tw_0.heartPlane1.d)
                                                     + (float)((float)(tw_0.heartPlane1.b * vert->vertices[0].p.y)
                                                             + (float)(tw_0.heartPlane1.c * vert->vertices[0].p.z))) & SIMD_SP_absMask_0[0]),
                                        tw_0.maxDistFromHeartPlane1);
        LODWORD(v233) = &vert->vertices[0].rotationBounds;
        p_rotationBounds = (idBounds *)LODWORD(v237);
        LODWORD(v237) = &v101->vertices[0].rotationOrigin;
        v128 = _mm_loadh_ps((const double *)&vert->vertices[0].p.y);
        v129 = _mm_loadh_ps((const double *)&p_rotationBounds->b[0].y);
        v130 = _mm_loadh_ps((const double *)&v101->vertices[0].rotationOrigin.y);
        v131 = _mm_loadh_ps((const double *)&tw_0.axis.y);
        v132 = _mm_sub_ps(v129, v130);
        v133 = _mm_sub_ps(
                 _mm_mul_ps(_mm_shuffle_ps(v131, v131, 54), v132),
                 _mm_mul_ps(_mm_shuffle_ps(v132, v132, 54), v131));
        v134 = _mm_sub_ps(v128, v130);
        v135 = _mm_sub_ps(
                 _mm_mul_ps(_mm_shuffle_ps(v131, v131, 54), v134),
                 _mm_mul_ps(_mm_shuffle_ps(v134, v134, 54), v131));
        v136 = _mm_xor_ps(
                 _mm_cmplt_ps(_mm_shuffle_ps(v133, v133, 54), *(__m128 *)SIMD_SP_zero_0),
                 _mm_cmplt_ps(_mm_shuffle_ps(v135, v135, 54), *(__m128 *)SIMD_SP_zero_0));
        v137 = _mm_mul_ps(v134, v134);
        v137.m128_f32[0] = v137.m128_f32[0] + _mm_shuffle_ps(v137, v137, 2).m128_f32[0];
        v137.m128_f32[0] = v137.m128_f32[0] + _mm_shuffle_ps(v137, v137, 3).m128_f32[0];
        v138 = _mm_cmplt_ps(_mm_mul_ps(_mm_add_ps(v129, v128), *(__m128 *)SIMD_SP_half_0), v130);
        v139 = _mm_mul_ps(
                 _mm_shuffle_ps(v137, v137, 0),
                 _mm_and_ps(_mm_sub_ps(_mm_mul_ps(v131, v131), *(__m128 *)SIMD_SP_one_0), *(__m128 *)SIMD_SP_absMask_0));
        v140 = _mm_rsqrt_ps(v139);
        v141 = _mm_add_ps(
                 _mm_xor_ps(
                   _mm_mul_ps(
                     _mm_mul_ps(
                       _mm_sub_ps(_mm_mul_ps(_mm_mul_ps(v139, v140), v140), *(__m128 *)SIMD_SP_rsqrt_c0_0),
                       _mm_mul_ps(v140, *(__m128 *)SIMD_SP_rsqrt_c1_0)),
                     v139),
                   _mm_and_ps(v138, *(__m128 *)SIMD_SP_signBit_0)),
                 v130);
        v142 = v136;
        v143 = _mm_and_ps(v136, v138);
        v144 = _mm_andnot_ps(v138, v142);
        v145 = _mm_sub_ps(
                 _mm_or_ps(_mm_andnot_ps(v143, _mm_min_ps(v128, v129)), _mm_and_ps(v141, v143)),
                 *(__m128 *)SIMD_SP_boxEpsilon_0);
        v146 = _mm_add_ps(
                 _mm_or_ps(_mm_andnot_ps(v144, _mm_max_ps(v129, v128)), _mm_and_ps(v141, v144)),
                 *(__m128 *)SIMD_SP_boxEpsilon_0);
        vert->vertices[0].rotationBounds.b[0].x = v145.m128_f32[0];
        _mm_storeh_ps((double *)&vert->vertices[0].rotationBounds.b[0].y, v145);
        vert->vertices[0].rotationBounds.b[1].x = v146.m128_f32[0];
        _mm_storeh_ps((double *)&vert->vertices[0].rotationBounds.b[1].y, v146);
        vert->vertices[0].used = (v148 | v149) == 0;
        i1 += 3;
        LODWORD(v245) += 12;
        v150 = ++i < tw_0.numVerts;
        vert = (cm_traceWork_t *)((char *)vert + 96);
        if ( !v150 )
          break;
        p_y = i1;
        v101 = vert;
      }
      v27 = trm;
    }
    ia = 1;
    tw_0.maxDistFromHeartPlane1 = tw_0.maxDistFromHeartPlane1 + 1.0;
    tw_0.numEdges = v27->numEdges;
    if ( tw_0.numEdges >= 1 )
    {
      v151 = &v27->edges[1].v[1];
      v152 = &tw_0.edges[1].pl.p[2];
      verta = (cm_trmVertex_t *)&v27->edges[1].v[1];
      do
      {
        v153 = *(v151 - 1);
        v154 = *v151;
        *((_DWORD *)v152 - 3) = v154;
        *((_DWORD *)v152 - 4) = v153;
        i1b = v154;
        v155 = v153;
        v154 *= 96;
        *((_WORD *)v152 - 16) = *(_WORD *)((char *)&tw_0.vertices[0].used + v154) | LOWORD(tw_0.vertices[v153].used);
        v156 = &zverts[v153];
        v157 = &zverts[i1b];
        *(v152 - 2) = tw_0.vertices[v155].p.x * *(float *)((char *)&tw_0.vertices[0].p.y + v154)
                    - tw_0.vertices[v155].p.y * *(float *)((char *)&tw_0.vertices[0].p.x + v154);
        *(v152 - 1) = tw_0.vertices[v155].p.x * *(float *)((char *)&tw_0.vertices[0].p.z + v154)
                    - *(float *)((char *)&tw_0.vertices[0].p.x + v154) * tw_0.vertices[v155].p.z;
        *v152 = tw_0.vertices[v155].p.x - *(float *)((char *)&tw_0.vertices[0].p.x + v154);
        v152[1] = tw_0.vertices[v155].p.y * *(float *)((char *)&tw_0.vertices[0].p.z + v154)
                - *(float *)((char *)&tw_0.vertices[0].p.y + v154) * tw_0.vertices[v155].p.z;
        v152[2] = tw_0.vertices[v155].p.z - *(float *)((char *)&tw_0.vertices[0].p.z + v154);
        v158 = *(float *)((char *)&tw_0.vertices[0].p.y + v154) - tw_0.vertices[v155].p.y;
        p_rotationOrigin = (idVec3 *)((char *)tw_0.vertices[0].rotationBounds.b + v154);
        v152[3] = v158;
        v152[4] = v156->x * v157->y - v157->x * v156->y;
        v152[5] = v157->z * v156->x - v157->x * v156->z;
        v152[6] = v156->x - v157->x;
        v152[7] = v157->z * v156->y - v156->z * v157->y;
        v152[8] = v156->z - v157->z;
        v159 = v157->y - v156->y;
        p_rotationBounds = &tw_0.vertices[v155].rotationBounds;
        v152[9] = v159;
        v160 = (float *)p_rotationBounds;
        v161 = &p_rotationOrigin->x;
        v152[10] = fminf(p_rotationBounds->b[0].x, p_rotationOrigin->x);
        v152[11] = fminf(v160[1], v161[1]);
        v152[12] = fminf(v160[2], v161[2]);
        v152[13] = fmaxf(v160[3], v161[3]);
        v152[14] = fmaxf(v160[4], v161[4]);
        v152[15] = fmaxf(v160[5], v161[5]);
        ++ia;
        v151 = (int *)&verta->endp.y;
        v152 += 24;
        verta = (cm_trmVertex_t *)((char *)verta + 20);
      }
      while ( ia <= tw_0.numEdges );
      v27 = trm;
    }
    tw_0.traceBounds.b[1].z = -1.0e30;
    tw_0.traceBounds.b[1].y = -1.0e30;
    tw_0.traceBounds.b[0].z = idMath::INFINITY;
    tw_0.traceBounds.b[1].x = -1.0e30;
    tw_0.traceBounds.b[0].y = idMath::INFINITY;
    tw_0.traceBounds.b[0].x = idMath::INFINITY;
    tw_0.numPolys = v27->numPolys;
    ib = 0;
    if ( tw_0.numPolys > 0 )
    {
      p_b = &tw_0.polys[0].plane.b;
      v163 = (cm_trmVertex_t *)&v27->polys[0].normal.y;
      i1a = &tw_0.polys[0].plane.b;
      vertb = (cm_trmVertex_t *)&v27->polys[0].normal.y;
      while ( 1 )
      {
        *((_DWORD *)p_b + 3) = 1;
        v164 = LODWORD(v163->pl.p[1]);
        v165 = 0;
        *((_DWORD *)p_b + 4) = v164;
        if ( v164 > 0 )
        {
          v166 = (traceModel_t *)(p_b + 5);
          trma = (const idTraceModel *)&v163->pl.p[2];
          do
          {
            type = trma->type;
            trma = (const idTraceModel *)((char *)trma + 4);
            *v166 = type;
            ++v165;
            ++v166;
          }
          while ( v165 < *((_DWORD *)p_b + 4) );
        }
        v168 = trmTransform.mat[0] * v163[-1].rotationBounds.b[1].z;
        p_rotationBounds = (idBounds *)(p_b + 5);
        *(p_b - 1) = v168 + trmTransform.mat[2] * v163->p.y + trmTransform.mat[1] * v163->p.x;
        *p_b = trmTransform.mat[6] * v163->p.y
             + trmTransform.mat[4] * v163[-1].rotationBounds.b[1].z
             + trmTransform.mat[5] * v163->p.x;
        v169 = trmTransform.mat[10] * v163->p.y
             + trmTransform.mat[8] * v163[-1].rotationBounds.b[1].z
             + trmTransform.mat[9] * v163->p.x;
        v170 = abs32(*((_DWORD *)p_b + 5));
        p_b[1] = v169;
        v171 = &tw_0.vertices[tw_0.edges[v170].vertexNum[0]].p.x;
        v172 = v171[1] * *p_b + v169 * v171[2];
        v173 = *v171 * *(p_b - 1);
        p_rotationOrigin = (idVec3 *)*((_DWORD *)p_b + 4);
        LODWORD(v245) = p_b + 21;
        trmb = p_b + 21;
        p_b[2] = -(v172 + v173);
        v174 = abs32(LODWORD(p_rotationBounds->b[0].x));
        v175 = -4 * (_DWORD)p_rotationOrigin + 4;
        v176 = tw_0.edges[v174].rotationBounds.b[0].x;
        v177 = tw_0.edges[v174].rotationBounds.b[0].y;
        v178 = tw_0.edges[v174].rotationBounds.b[0].z;
        v179 = tw_0.edges[v174].rotationBounds.b[1].x;
        v180 = tw_0.edges[v174].rotationBounds.b[1].y;
        v181 = tw_0.edges[v174].rotationBounds.b[1].z;
        if ( v175 < 0 != __OFADD__(4, -4 * (_DWORD)p_rotationOrigin) )
        {
          do
          {
            v182 = abs32(*(_DWORD *)((char *)&p_rotationBounds->b[0].x + 4 * (_DWORD)p_rotationOrigin + v175));
            v150 = (v175 + 4 < 0) ^ __OFADD__(4, v175);
            v175 += 4;
            v176 = fminf(v176, tw_0.edges[v182].rotationBounds.b[0].x);
            v177 = fminf(v177, tw_0.edges[v182].rotationBounds.b[0].y);
            v178 = fminf(v178, tw_0.edges[v182].rotationBounds.b[0].z);
            v179 = fmaxf(v179, tw_0.edges[v182].rotationBounds.b[1].x);
            v180 = fmaxf(v180, tw_0.edges[v182].rotationBounds.b[1].y);
            v181 = fmaxf(v181, tw_0.edges[v182].rotationBounds.b[1].z);
          }
          while ( v150 );
        }
        *trmb = v176;
        trmb[1] = v177;
        trmb[2] = v178;
        trmb[3] = v179;
        trmb[4] = v180;
        trmb[5] = v181;
        v183 = (float *)LODWORD(v245);
        tw_0.traceBounds.b[0].x = fminf(tw_0.traceBounds.b[0].x, *(float *)LODWORD(v245));
        tw_0.traceBounds.b[0].y = fminf(tw_0.traceBounds.b[0].y, *(float *)(LODWORD(v245) + 4));
        tw_0.traceBounds.b[0].z = fminf(tw_0.traceBounds.b[0].z, v183[2]);
        tw_0.traceBounds.b[1].x = fmaxf(tw_0.traceBounds.b[1].x, v183[3]);
        tw_0.traceBounds.b[1].y = fmaxf(tw_0.traceBounds.b[1].y, v183[4]);
        tw_0.traceBounds.b[1].z = fmaxf(tw_0.traceBounds.b[1].z, v183[5]);
        vertb = (cm_trmVertex_t *)((char *)vertb + 108);
        i1a += 28;
        if ( ++ib >= tw_0.numPolys )
          break;
        v163 = vertb;
        p_b = i1a;
      }
    }
    trmc = tw_0.maxErr;
    v184 = _mm_loadh_ps((const double *)&tw_0.start.y);
    v185 = _mm_sub_ps(_mm_loadh_ps((const double *)&tw_0.traceBounds.b[0].y), v184);
    v186 = _mm_sub_ps(_mm_loadh_ps((const double *)&tw_0.traceBounds.b[1].y), v184);
    tw_0.trmBounds.b[0].x = v185.m128_f32[0];
    _mm_storeh_ps((double *)&tw_0.trmBounds.b[0].y, v185);
    tw_0.trmBounds.b[1].x = v186.m128_f32[0];
    _mm_storeh_ps((double *)&tw_0.trmBounds.b[1].y, v186);
    v187 = (__m128)LODWORD(trmc);
    v187.m128_f32[0] = trmc + SIMD_SP_boxEpsilon_0[0];
    v188 = _mm_add_ps(
             _mm_max_ps(_mm_and_ps(v185, *(__m128 *)SIMD_SP_absMask_0), _mm_and_ps(v186, *(__m128 *)SIMD_SP_absMask_0)),
             _mm_shuffle_ps(v187, v187, 0));
    tw_0.trmExtents.x = v188.m128_f32[0];
    _mm_storeh_ps((double *)&tw_0.trmExtents.y, v188);
    if ( tw_0.isConvex )
      tw_0.axisIntersectsTrm = tw_0.start.x == tw_0.origin.x
                            && tw_0.start.y == tw_0.origin.y
                            && tw_0.start.z == tw_0.origin.z
                            || CM_RayIntersectsConvexTraceModel(&tw_0, &tw_0.origin, &tw_0.axis);
    tw_0.modelVertexRotation.angle = -tw_0.angle;
    tw_0.modelVertexRotation.origin = tw_0.origin;
    tw_0.modelVertexRotation.vec = tw_0.axis;
    tw_0.modelVertexRotation.axisValid = 0;
    idCollisionModelManagerLocal::TraceThroughModel(v229, &tw_0);
    *results = tw_0.trace;
    results->endpos.x = start->x;
    v189 = initialTan;
    results->endpos.y = start->y;
    results->endpos.z = start->z;
    if ( tw_0.maxTan == v189 )
      results->fraction = 1.0;
    else
      results->fraction = fabs(atan2(tw_0.maxTan, 1.0) * (360.0 / 3.1415927 / tw_0.angle));
    v190 = rorg->x;
    v191 = rorg->y;
    v192 = v227 * results->fraction + startAngle;
    endRotation.origin.z = rorg->z;
    endRotation.origin.x = v190;
    v193 = axis->x;
    endRotation.angle = v192;
    endRotation.origin.y = v191;
    v194 = axis->y;
    v195 = axis->z;
    endRotation.vec.x = v193;
    endRotation.vec.y = v194;
    endRotation.vec.z = v195;
    endRotation.axisValid = 0;
    idRotation::ToMat3(&endRotation);
    v196 = results->endpos.x - endRotation.origin.x;
    v197 = results->endpos.y - endRotation.origin.y;
    v198 = results->endpos.z - endRotation.origin.z;
    v239 = v196 * endRotation.axis.mat[0].x + endRotation.axis.mat[2].x * v198 + v197 * endRotation.axis.mat[1].x;
    v240 = v196 * endRotation.axis.mat[0].y + v197 * endRotation.axis.mat[1].y + v198 * endRotation.axis.mat[2].y;
    v199 = v196 * endRotation.axis.mat[0].z + v197 * endRotation.axis.mat[1].z + v198 * endRotation.axis.mat[2].z;
    v200 = v239 + endRotation.origin.x;
    v201 = v199;
    v202 = v240 + endRotation.origin.y;
    v226 = v201 + endRotation.origin.z;
    results->endpos.z = v226;
    results->endpos.x = v200;
    results->endpos.y = v202;
    v203 = (float *)idRotation::ToMat3(&endRotation);
    v204 = (float *)LODWORD(v235);
    v205 = &trmTransform.mat[3];
    v206 = 3;
    do
    {
      v207 = v203[3] * *v204;
      v205 += 3;
      v208 = *v203 * *(v204 - 1);
      v204 += 3;
      --v206;
      *(v205 - 3) = v207 + v208 + v203[6] * *(v204 - 2);
      *(v205 - 2) = *(v204 - 2) * v203[7] + v203[4] * *(v204 - 3) + v203[1] * *(v204 - 4);
      *(v205 - 1) = v203[5] * *(v204 - 3) + v203[8] * *(v204 - 2) + v203[2] * *(v204 - 4);
    }
    while ( v206 );
    qmemcpy(&invModelAxis, &trmTransform.mat[3], sizeof(invModelAxis));
    v209 = invModelAxis.mat[0].y;
    results->endAxis.mat[0].x = invModelAxis.mat[0].x;
    v210 = invModelAxis.mat[0].z;
    results->endAxis.mat[0].y = v209;
    v211 = invModelAxis.mat[1].x;
    results->endAxis.mat[0].z = v210;
    v212 = invModelAxis.mat[1].y;
    results->endAxis.mat[1].x = v211;
    v213 = invModelAxis.mat[1].z;
    results->endAxis.mat[1].y = v212;
    v214 = invModelAxis.mat[2].x;
    results->endAxis.mat[1].z = v213;
    v215 = invModelAxis.mat[2].y;
    results->endAxis.mat[2].x = v214;
    v216 = invModelAxis.mat[2].z;
    results->endAxis.mat[2].y = v215;
    results->endAxis.mat[2].z = v216;
    if ( results->fraction < 1.0 )
    {
      if ( model_rotated_3 )
      {
        v218 = results->c.normal.x * modelAxis->mat[0].x
             + results->c.normal.y * modelAxis->mat[1].x
             + modelAxis->mat[2].x * results->c.normal.z;
        v219 = modelAxis->mat[0].y * results->c.normal.x
             + modelAxis->mat[1].y * results->c.normal.y
             + results->c.normal.z * modelAxis->mat[2].y;
        results->c.normal.z = results->c.normal.x * modelAxis->mat[0].z
                            + results->c.normal.z * modelAxis->mat[2].z
                            + modelAxis->mat[1].z * results->c.normal.y;
        results->c.normal.x = v218;
        results->c.normal.y = v219;
        v220 = modelAxis->mat[2].x * results->c.point.z
             + modelAxis->mat[1].x * results->c.point.y
             + results->c.point.x * modelAxis->mat[0].x;
        v221 = modelAxis->mat[1].y * results->c.point.y
             + modelAxis->mat[0].y * results->c.point.x
             + results->c.point.z * modelAxis->mat[2].y;
        results->c.point.z = modelAxis->mat[1].z * results->c.point.y
                           + results->c.point.x * modelAxis->mat[0].z
                           + results->c.point.z * modelAxis->mat[2].z;
        results->c.point.x = v220;
        results->c.point.y = v221;
      }
      results->c.point.x = modelOrigin->x + results->c.point.x;
      results->c.point.y = modelOrigin->y + results->c.point.y;
      results->c.point.z = results->c.point.z + modelOrigin->z;
      results->c.dist = results->c.normal.z * modelOrigin->z
                      + results->c.normal.y * modelOrigin->y
                      + modelOrigin->x * results->c.normal.x
                      + results->c.dist;
    }
  }
  else
  {
    if ( model_rotated_3 )
    {
      tw_0.start.z = invModelAxis.mat[2].z * v246.z + invModelAxis.mat[1].z * v246.y + invModelAxis.mat[0].z * v246.x;
      tw_0.start.x = invModelAxis.mat[2].x * v246.z + invModelAxis.mat[1].x * v246.y + invModelAxis.mat[0].x * v246.x;
      tw_0.start.y = invModelAxis.mat[2].y * v246.z + invModelAxis.mat[1].y * v246.y + invModelAxis.mat[0].y * v246.x;
    }
    tw_0.end = tw_0.start;
    if ( startAngle == 0.0 )
      goto LABEL_19;
    idRotation::ToMat3(&startRotation);
    v28 = tw_0.start.x - startRotation.origin.x;
    v29 = tw_0.start.y - startRotation.origin.y;
    v30 = tw_0.start.z - startRotation.origin.z;
    v242 = startRotation.axis.mat[2].x * v30 + startRotation.axis.mat[1].x * v29 + startRotation.axis.mat[0].x * v28;
    v243 = startRotation.axis.mat[2].y * v30 + startRotation.axis.mat[1].y * v29 + startRotation.axis.mat[0].y * v28;
    v241 = startRotation.axis.mat[2].z * v30
         + startRotation.axis.mat[1].z * v29
         + startRotation.axis.mat[0].z * v28
         + startRotation.origin.z;
    tw_0.start.z = v241;
    tw_0.start.x = v242 + startRotation.origin.x;
    tw_0.start.y = v243 + startRotation.origin.y;
    if ( !endRotation.axisValid )
LABEL_19:
      idRotation::ToMat3(&endRotation);
    v31 = tw_0.end.x - endRotation.origin.x;
    v32 = tw_0.end.y - endRotation.origin.y;
    tw_0.vertices[0].p = tw_0.start;
    v33 = tw_0.end.z - endRotation.origin.z;
    tw_0.numVerts = 1;
    tw_0.vertices[0].used = 1;
    v247.x = v31 * endRotation.axis.mat[0].x + endRotation.axis.mat[2].x * v33 + v32 * endRotation.axis.mat[1].x;
    v247.y = v31 * endRotation.axis.mat[0].y + v32 * endRotation.axis.mat[1].y + v33 * endRotation.axis.mat[2].y;
    v247.z = v31 * endRotation.axis.mat[0].z + v32 * endRotation.axis.mat[1].z + v33 * endRotation.axis.mat[2].z;
    v241 = v247.z + endRotation.origin.z;
    tw_0.vertices[0].endp.z = v241;
    tw_0.end.x = v247.x + endRotation.origin.x;
    tw_0.end.y = v247.y + endRotation.origin.y;
    tw_0.end.z = v241;
    tw_0.vertices[0].endp.x = tw_0.end.x;
    tw_0.vertices[0].endp.y = tw_0.end.y;
    v34 = (tw_0.start.z - tw_0.origin.z) * tw_0.axis.z
        + (tw_0.start.y - tw_0.origin.y) * tw_0.axis.y
        + (tw_0.start.x - tw_0.origin.x) * tw_0.axis.x;
    v242 = tw_0.axis.x * v34;
    v243 = tw_0.axis.y * v34;
    v241 = v34 * tw_0.axis.z + tw_0.origin.z;
    tw_0.vertices[0].rotationOrigin.z = v241;
    tw_0.vertices[0].rotationOrigin.x = v242 + tw_0.origin.x;
    tw_0.vertices[0].rotationOrigin.y = v243 + tw_0.origin.y;
    v35 = _mm_loadh_ps((const double *)&tw_0.start.y);
    v36 = _mm_loadh_ps((const double *)&tw_0.end.y);
    v37 = _mm_loadh_ps((const double *)&tw_0.vertices[0].rotationOrigin.y);
    v38 = _mm_loadh_ps((const double *)&tw_0.axis.y);
    v39 = _mm_sub_ps(v36, v37);
    v40 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(v38, v38, 54), v39), _mm_mul_ps(_mm_shuffle_ps(v39, v39, 54), v38));
    v41 = _mm_sub_ps(v35, v37);
    v42 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(v38, v38, 54), v41), _mm_mul_ps(_mm_shuffle_ps(v41, v41, 54), v38));
    v43 = _mm_xor_ps(
            _mm_cmplt_ps(_mm_shuffle_ps(v40, v40, 54), *(__m128 *)SIMD_SP_zero_0),
            _mm_cmplt_ps(_mm_shuffle_ps(v42, v42, 54), *(__m128 *)SIMD_SP_zero_0));
    v44 = _mm_mul_ps(v41, v41);
    v44.m128_f32[0] = v44.m128_f32[0] + _mm_shuffle_ps(v44, v44, 2).m128_f32[0];
    v44.m128_f32[0] = v44.m128_f32[0] + _mm_shuffle_ps(v44, v44, 3).m128_f32[0];
    v45 = _mm_cmplt_ps(_mm_mul_ps(_mm_add_ps(v36, v35), *(__m128 *)SIMD_SP_half_0), v37);
    v46 = _mm_mul_ps(
            _mm_shuffle_ps(v44, v44, 0),
            _mm_and_ps(_mm_sub_ps(_mm_mul_ps(v38, v38), *(__m128 *)SIMD_SP_one_0), *(__m128 *)SIMD_SP_absMask_0));
    v47 = _mm_rsqrt_ps(v46);
    v48 = _mm_add_ps(
            _mm_xor_ps(
              _mm_mul_ps(
                _mm_mul_ps(
                  _mm_sub_ps(_mm_mul_ps(_mm_mul_ps(v46, v47), v47), *(__m128 *)SIMD_SP_rsqrt_c0_0),
                  _mm_mul_ps(v47, *(__m128 *)SIMD_SP_rsqrt_c1_0)),
                v46),
              _mm_and_ps(v45, *(__m128 *)SIMD_SP_signBit_0)),
            v37);
    v49 = v43;
    v50 = _mm_and_ps(v43, v45);
    v51 = _mm_andnot_ps(v45, v49);
    v52 = _mm_sub_ps(
            _mm_or_ps(_mm_andnot_ps(v50, _mm_min_ps(v35, v36)), _mm_and_ps(v48, v50)),
            *(__m128 *)SIMD_SP_boxEpsilon_0);
    v53 = _mm_add_ps(
            _mm_or_ps(_mm_andnot_ps(v51, _mm_max_ps(v36, v35)), _mm_and_ps(v48, v51)),
            *(__m128 *)SIMD_SP_boxEpsilon_0);
    tw_0.vertices[0].rotationBounds.b[0].x = v52.m128_f32[0];
    _mm_storeh_ps((double *)&tw_0.vertices[0].rotationBounds.b[0].y, v52);
    tw_0.vertices[0].rotationBounds.b[1].x = v53.m128_f32[0];
    _mm_storeh_ps((double *)&tw_0.vertices[0].rotationBounds.b[1].y, v53);
    tw_0.traceBounds = tw_0.vertices[0].rotationBounds;
    tw_0.trmExtents.z = tw_0.maxErr + 1.0;
    tw_0.trmExtents.y = tw_0.trmExtents.z;
    tw_0.trmExtents.x = tw_0.trmExtents.z;
    tw_0.pointTrace = 1;
    tw_0.numPolys = 0;
    tw_0.numEdges = 0;
    tw_0.heartPlane1.b = tw_0.axis.y;
    tw_0.heartPlane1.d = -(tw_0.axis.x * tw_0.start.x + tw_0.axis.z * tw_0.start.z + tw_0.axis.y * tw_0.start.y);
    tw_0.heartPlane1.a = tw_0.axis.x;
    tw_0.heartPlane1.c = tw_0.axis.z;
    tw_0.maxDistFromHeartPlane1 = 1.0;
    idCollisionModelManagerLocal::TraceThroughModel(v229, &tw_0);
    trace_t::operator=(results, &tw_0.trace.fraction);
    v54 = initialTan;
    results->endpos = *start;
    if ( tw_0.maxTan == v54 )
      results->fraction = 1.0;
    else
      results->fraction = fabs(atan2(tw_0.maxTan, 1.0) * (360.0 / 3.1415927 / tw_0.angle));
    v55 = rorg->x;
    v56 = rorg->y;
    v57 = v227 * results->fraction + startAngle;
    endRotation.origin.z = rorg->z;
    endRotation.origin.x = v55;
    v58 = axis->x;
    endRotation.angle = v57;
    endRotation.origin.y = v56;
    v59 = axis->y;
    v60 = axis->z;
    endRotation.vec.x = v58;
    endRotation.vec.y = v59;
    endRotation.vec.z = v60;
    endRotation.axisValid = 0;
    idRotation::ToMat3(&endRotation);
    v61 = results->endpos.x - endRotation.origin.x;
    v62 = results->endpos.y - endRotation.origin.y;
    v63 = results->endpos.z - endRotation.origin.z;
    v242 = endRotation.axis.mat[2].x * v63 + v61 * endRotation.axis.mat[0].x + v62 * endRotation.axis.mat[1].x;
    v243 = v62 * endRotation.axis.mat[1].y + v63 * endRotation.axis.mat[2].y + v61 * endRotation.axis.mat[0].y;
    v64 = v62 * endRotation.axis.mat[1].z + v63 * endRotation.axis.mat[2].z + v61 * endRotation.axis.mat[0].z;
    v65 = v242 + endRotation.origin.x;
    v66 = v64;
    v67 = v243 + endRotation.origin.y;
    v241 = v66 + endRotation.origin.z;
    results->endpos.z = v241;
    results->endpos.x = v65;
    results->endpos.y = v67;
    results->endAxis = mat3_identity;
    if ( results->fraction < 1.0 )
    {
      if ( model_rotated_3 )
      {
        v69 = modelAxis->mat[2].x * results->c.normal.z
            + results->c.normal.x * modelAxis->mat[0].x
            + modelAxis->mat[1].x * results->c.normal.y;
        v70 = modelAxis->mat[1].y * results->c.normal.y
            + results->c.normal.x * modelAxis->mat[0].y
            + results->c.normal.z * modelAxis->mat[2].y;
        results->c.normal.z = modelAxis->mat[1].z * results->c.normal.y
                            + results->c.normal.x * modelAxis->mat[0].z
                            + results->c.normal.z * modelAxis->mat[2].z;
        results->c.normal.x = v69;
        results->c.normal.y = v70;
        v71 = modelAxis->mat[0].x * results->c.point.x
            + modelAxis->mat[2].x * results->c.point.z
            + modelAxis->mat[1].x * results->c.point.y;
        v72 = modelAxis->mat[1].y * results->c.point.y
            + results->c.point.z * modelAxis->mat[2].y
            + modelAxis->mat[0].y * results->c.point.x;
        results->c.point.z = modelAxis->mat[0].z * results->c.point.x
                           + modelAxis->mat[1].z * results->c.point.y
                           + results->c.point.z * modelAxis->mat[2].z;
        results->c.point.x = v71;
        results->c.point.y = v72;
      }
      results->c.point.x = results->c.point.x + modelOrigin->x;
      results->c.point.y = modelOrigin->y + results->c.point.y;
      results->c.point.z = results->c.point.z + modelOrigin->z;
      results->c.dist = results->c.normal.z * modelOrigin->z
                      + results->c.normal.y * modelOrigin->y
                      + results->c.normal.x * modelOrigin->x
                      + results->c.dist;
    }
  }
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::Rotation(struct trace_t *,class idVec3 const &,class idRotation const &,class idTraceModel const *,class idMat3 const &,int,class idCollisionModel *,class idVec3 const &,class idMat3 const &)
void __thiscall idCollisionModelManagerLocal::Rotation(
        idCollisionModelManagerLocal *this,
        trace_t *results,
        const idVec3 *start,
        idRotation *rotation,
        const idTraceModel *trm,
        const idMat3 *trmAxis,
        int contentMask,
        idCollisionModelLocal *model,
        cm_trmVertex_t *modelOrigin,
        const idMat3 *modelAxis)
{
  float *v12; // eax
  char *v13; // edx
  float *p_y; // ecx
  int v15; // esi
  double v16; // st7
  double v17; // st6
  float v18; // edx
  float v19; // eax
  float v20; // ecx
  float v21; // edx
  float v22; // eax
  float v23; // ecx
  float v24; // edx
  float v25; // eax
  double v26; // st7
  double v27; // st6
  double v28; // st5
  double v29; // st7
  double v30; // st6
  double v31; // st5
  double v32; // st7
  long double angle; // st7
  long double v35; // st7
  float lasta; // [esp+10h] [ebp-5Ch]
  float v37; // [esp+14h] [ebp-58h]
  float v38; // [esp+18h] [ebp-54h]
  float v39; // [esp+1Ch] [ebp-50h]
  float v40; // [esp+20h] [ebp-4Ch]
  int v41[9]; // [esp+24h] [ebp-48h] BYREF
  char v42[36]; // [esp+48h] [ebp-24h] BYREF
  float rotationa; // [esp+78h] [ebp+Ch]
  float modela; // [esp+88h] [ebp+1Ch]

  if ( model )
  {
    if ( rotation->angle == 0.0 )
    {
      idCollisionModelManagerLocal::ContentsTrm(
        this,
        results,
        start,
        trm,
        trmAxis,
        contentMask,
        model,
        modelOrigin,
        modelAxis);
    }
    else if ( rotation->angle >= 180.0 || rotation->angle <= -180.0 )
    {
      if ( rotation->angle < 360.0 )
      {
        if ( rotation->angle > -360.0 )
        {
          angle = rotation->angle;
          rotationa = angle * 0.5;
        }
        else
        {
          angle = -360.0;
          rotationa = -120.0;
        }
      }
      else
      {
        angle = 360.0;
        rotationa = 120.0;
      }
      modela = rotationa;
      lasta = 0.0;
      v37 = fabs(angle) + 1.0;
      if ( fabs(rotationa) >= v37 )
      {
LABEL_20:
        results->fraction = 1.0;
      }
      else
      {
        while ( 1 )
        {
          idCollisionModelManagerLocal::Rotation180(
            this,
            results,
            &rotation->origin,
            &rotation->vec,
            lasta,
            modela,
            start,
            trm,
            trmAxis,
            contentMask,
            model,
            &modelOrigin->p,
            modelAxis);
          if ( results->fraction < 1.0 )
            break;
          v35 = modela + rotationa;
          lasta = modela;
          modela = v35;
          if ( fabs(v35) >= v37 )
            goto LABEL_20;
        }
        results->fraction = (rotationa * results->fraction + lasta) / rotation->angle;
      }
    }
    else
    {
      idCollisionModelManagerLocal::Rotation180(
        this,
        results,
        &rotation->origin,
        &rotation->vec,
        0.0,
        rotation->angle,
        start,
        trm,
        trmAxis,
        contentMask,
        model,
        &modelOrigin->p,
        modelAxis);
    }
  }
  else
  {
    results->fraction = 1.0;
    results->endpos = *start;
    v12 = (float *)idRotation::ToMat3(rotation);
    v13 = v42;
    p_y = &trmAxis->mat[0].y;
    v15 = 3;
    do
    {
      v16 = v12[6] * p_y[1];
      v13 += 12;
      v17 = v12[3] * *p_y;
      p_y += 3;
      --v15;
      *((float *)v13 - 3) = v16 + v17 + *v12 * *(p_y - 4);
      *((float *)v13 - 2) = v12[1] * *(p_y - 4) + *(p_y - 3) * v12[4] + v12[7] * *(p_y - 2);
      *((float *)v13 - 1) = v12[8] * *(p_y - 2) + v12[2] * *(p_y - 4) + v12[5] * *(p_y - 3);
    }
    while ( v15 );
    qmemcpy(v41, v42, sizeof(v41));
    v18 = *(float *)&v41[1];
    v19 = *(float *)&v41[2];
    LODWORD(results->endAxis.mat[0].x) = v41[0];
    v20 = *(float *)&v41[3];
    results->endAxis.mat[0].y = v18;
    v21 = *(float *)&v41[4];
    results->endAxis.mat[0].z = v19;
    v22 = *(float *)&v41[5];
    results->endAxis.mat[1].x = v20;
    v23 = *(float *)&v41[6];
    results->endAxis.mat[1].y = v21;
    v24 = *(float *)&v41[7];
    results->endAxis.mat[1].z = v22;
    v25 = *(float *)&v41[8];
    results->endAxis.mat[2].x = v23;
    results->endAxis.mat[2].y = v24;
    results->endAxis.mat[2].z = v25;
    if ( !rotation->axisValid )
      idRotation::ToMat3(rotation);
    v26 = results->endpos.x - rotation->origin.x;
    v27 = results->endpos.y - rotation->origin.y;
    v28 = results->endpos.z - rotation->origin.z;
    v38 = v28 * rotation->axis.mat[2].x + v27 * rotation->axis.mat[1].x + v26 * rotation->axis.mat[0].x;
    v39 = v28 * rotation->axis.mat[2].y + v27 * rotation->axis.mat[1].y + v26 * rotation->axis.mat[0].y;
    v29 = v28 * rotation->axis.mat[2].z + v27 * rotation->axis.mat[1].z + v26 * rotation->axis.mat[0].z;
    v30 = v38 + rotation->origin.x;
    v31 = v29;
    v32 = v39 + rotation->origin.y;
    v40 = v31 + rotation->origin.z;
    results->endpos.z = v40;
    results->endpos.x = v30;
    results->endpos.y = v32;
  }
}
