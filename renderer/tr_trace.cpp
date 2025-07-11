
// FUNC: class rvDeclMatType const * __cdecl R_GetMaterialType(class idMaterial const *,struct srfTriangles_s const *,int,class idVec3 &)
const rvDeclMatType *__cdecl R_GetMaterialType(idMaterial *shader, const srfTriangles_s *tri, int i, idVec3 *point)
{
  int *indexes; // esi
  idDrawVert *verts; // eax
  int v7; // ecx
  float v8; // edi
  float *v9; // ecx
  int v10; // ecx
  float v11; // edi
  float *v12; // ecx
  int v13; // ecx
  float v14; // edi
  float *v15; // ecx
  idVec2 result; // [esp+4h] [ebp-50h] BYREF
  idVec3 normal; // [esp+Ch] [ebp-48h] BYREF
  idVec2 tc[3]; // [esp+18h] [ebp-3Ch] BYREF
  idVec3 t[3]; // [esp+30h] [ebp-24h] BYREF
  float shadera; // [esp+58h] [ebp+4h]

  if ( !shader->materialTypeArray )
    return shader->materialType;
  indexes = tri->indexes;
  normal = *(idVec3 *)&tri->facePlanes[i].a;
  verts = tri->verts;
  v7 = indexes[3 * i] << 6;
  v8 = *(float *)((char *)&verts->xyz.x + v7);
  v9 = (float *)((char *)&verts->xyz.x + v7);
  t[0].x = v8;
  t[0].y = v9[1];
  t[0].z = v9[2];
  v10 = indexes[3 * i + 1] << 6;
  v11 = *(float *)((char *)&verts->xyz.x + v10);
  v12 = (float *)((char *)&verts->xyz.x + v10);
  t[1].x = v11;
  t[1].y = v12[1];
  t[1].z = v12[2];
  v13 = indexes[3 * i + 2] << 6;
  v14 = *(float *)((char *)&verts->xyz.x + v13);
  v15 = (float *)((char *)&verts->xyz.x + v13);
  t[2].x = v14;
  t[2].y = v15[1];
  t[2].z = v15[2];
  tc[0] = verts[indexes[3 * i]].st;
  tc[1] = verts[indexes[3 * i + 1]].st;
  tc[2] = verts[indexes[3 * i + 2]].st;
  shadera = idMath::BarycentricTriangleArea(&normal, t, &t[1], &t[2]);
  if ( shadera == 0.0 )
    return shader->materialType;
  idMath::BarycentricEvaluate(&result, point, &normal, shadera, t, tc);
  return idMaterial::GetMaterialType(shader, &result);
}

// FUNC: void __cdecl RB_DrawExpandedTriangles(struct srfTriangles_s const *,float,class idVec3 const &)
void __cdecl RB_DrawExpandedTriangles(const srfTriangles_s *tri, float radius, const idVec3 *vieworg)
{
  const srfTriangles_s *v3; // esi
  int v4; // ecx
  bool v5; // cc
  int *indexes; // eax
  idDrawVert *verts; // edx
  float *p_x; // edi
  float v9; // ebx
  int v10; // edi
  int v11; // eax
  float *v12; // edi
  float v13; // ebx
  float v14; // edi
  float *v15; // eax
  float v16; // edx
  float v17; // edx
  float v18; // eax
  double v19; // st7
  double v20; // st6
  long double v21; // st5
  long double v22; // st5
  long double v23; // st7
  long double v24; // st7
  long double v25; // st7
  long double v26; // st7
  int v27; // eax
  float *p_z; // edi
  int v29; // ebp
  int v30; // ecx
  double v31; // st7
  idVec3 *v32; // ebx
  double v33; // st6
  double v34; // st7
  double v35; // st6
  long double v36; // st5
  long double v37; // st5
  double v38; // st7
  double v39; // st6
  double v40; // st7
  double v41; // st6
  long double v42; // st5
  long double v43; // st5
  double v44; // st7
  double v45; // st6
  double v46; // st7
  double v47; // st6
  long double v48; // st5
  long double v49; // st5
  idVec3 *v50; // esi
  double v51; // st7
  double v52; // st6
  double v53; // st7
  double v54; // st6
  float v55; // [esp+4h] [ebp-184h]
  float v56; // [esp+8h] [ebp-180h]
  float v57; // [esp+Ch] [ebp-17Ch]
  _BYTE v58[12]; // [esp+10h] [ebp-178h]
  _BYTE v59[12]; // [esp+1Ch] [ebp-16Ch]
  _BYTE v60[12]; // [esp+28h] [ebp-160h]
  _BYTE v61[12]; // [esp+34h] [ebp-154h]
  _BYTE v62[12]; // [esp+40h] [ebp-148h]
  idVec3 dir[6]; // [esp+4Ch] [ebp-13Ch] BYREF
  idVec3 p[3]; // [esp+94h] [ebp-F4h] BYREF
  int i; // [esp+B8h] [ebp-D0h]
  float v66; // [esp+BCh] [ebp-CCh]
  float v67; // [esp+C0h] [ebp-C8h]
  float v68; // [esp+C4h] [ebp-C4h]
  float v69; // [esp+C8h] [ebp-C0h]
  float v70; // [esp+CCh] [ebp-BCh]
  float v71; // [esp+D0h] [ebp-B8h]
  float v72; // [esp+D4h] [ebp-B4h]
  float v73; // [esp+D8h] [ebp-B0h]
  float v74; // [esp+DCh] [ebp-ACh]
  float v75; // [esp+E0h] [ebp-A8h]
  float v76; // [esp+E4h] [ebp-A4h]
  float v77; // [esp+E8h] [ebp-A0h]
  float v78; // [esp+ECh] [ebp-9Ch]
  float v79; // [esp+F0h] [ebp-98h]
  float v80; // [esp+F4h] [ebp-94h]
  float v81; // [esp+FCh] [ebp-8Ch]
  float v82; // [esp+104h] [ebp-84h]
  float v83; // [esp+110h] [ebp-78h]
  float v84; // [esp+11Ch] [ebp-6Ch]
  float v85; // [esp+130h] [ebp-58h]
  float v86; // [esp+13Ch] [ebp-4Ch]
  float v87; // [esp+148h] [ebp-40h]
  float v88; // [esp+154h] [ebp-34h]
  float v89; // [esp+160h] [ebp-28h]
  float v90; // [esp+16Ch] [ebp-1Ch]
  float v91; // [esp+178h] [ebp-10h]
  float v92; // [esp+184h] [ebp-4h]

  v3 = tri;
  v4 = 0;
  v5 = tri->numIndexes <= 0;
  i = 0;
  if ( !v5 )
  {
    do
    {
      indexes = v3->indexes;
      verts = v3->verts;
      p_x = &verts[indexes[v4]].xyz.x;
      p[0].x = *p_x;
      v9 = p_x[1];
      p[0].z = p_x[2];
      v10 = indexes[v4 + 1];
      v11 = indexes[v4 + 2];
      v12 = &verts[v10].xyz.x;
      p[0].y = v9;
      p[1].x = *v12;
      v13 = v12[1];
      v14 = v12[2];
      *(float *)v58 = p[0].x - p[1].x;
      p[1].y = v13;
      v15 = &verts[v11].xyz.x;
      v16 = *v15;
      p[1].z = v14;
      *(float *)&v58[4] = p[0].y - v13;
      p[2].x = v16;
      v17 = v15[1];
      v18 = v15[2];
      p[2].y = v17;
      p[2].z = v18;
      *(float *)&v58[8] = p[0].z - v14;
      dir[0] = *(idVec3 *)v58;
      *(float *)v59 = p[1].x - p[2].x;
      *(float *)&v59[4] = v13 - v17;
      *(float *)&v59[8] = v14 - v18;
      dir[1] = *(idVec3 *)v59;
      *(float *)v62 = p[2].x - p[0].x;
      *(float *)&v62[4] = v17 - p[0].y;
      *(float *)&v62[8] = v18 - p[0].z;
      dir[2] = *(idVec3 *)v62;
      v55 = *(float *)&v59[8] * *(float *)&v58[4] - *(float *)&v59[4] * *(float *)&v58[8];
      v56 = *(float *)&v58[8] * *(float *)v59 - *(float *)&v59[8] * *(float *)v58;
      v57 = *(float *)&v59[4] * *(float *)v58 - *(float *)&v58[4] * *(float *)v59;
      if ( v57 * vieworg->z + v56 * vieworg->y + v55 * vieworg->x <= v55 * p[0].x + v56 * p[0].y + v57 * p[0].z )
      {
        v19 = v56 * *(float *)&v58[8] - v57 * *(float *)&v58[4];
        v81 = v57 * *(float *)v58 - *(float *)&v58[8] * v55;
        dir[0].y = v81;
        v20 = *(float *)&v58[4] * v55 - v56 * *(float *)v58;
        dir[0].x = v19;
        dir[0].z = v20;
        *(float *)v61 = v56 * *(float *)&v59[8] - v57 * *(float *)&v59[4];
        *(float *)&v61[4] = v57 * *(float *)v59 - *(float *)&v59[8] * v55;
        *(float *)&v61[8] = *(float *)&v59[4] * v55 - v56 * *(float *)v59;
        dir[1] = *(idVec3 *)v61;
        *(float *)v60 = v56 * *(float *)&v62[8] - v57 * *(float *)&v62[4];
        *(float *)&v60[4] = v57 * *(float *)v62 - *(float *)&v62[8] * v55;
        *(float *)&v60[8] = *(float *)&v62[4] * v55 - v56 * *(float *)v62;
        dir[2] = *(idVec3 *)v60;
        v21 = v19 * v19 + v20 * v20 + v81 * v81;
        if ( v21 != 0.0 )
        {
          v22 = 1.0 / sqrt(v21);
          dir[0].x = v22 * v19;
          dir[0].y = v81 * v22;
          dir[0].z = v20 * v22;
        }
        v23 = *(float *)v61 * *(float *)v61
            + *(float *)&v61[8] * *(float *)&v61[8]
            + *(float *)&v61[4] * *(float *)&v61[4];
        if ( v23 != 0.0 )
        {
          v24 = 1.0 / sqrt(v23);
          dir[1].x = *(float *)v61 * v24;
          dir[1].y = *(float *)&v61[4] * v24;
          dir[1].z = *(float *)&v61[8] * v24;
        }
        v25 = *(float *)v60 * *(float *)v60
            + *(float *)&v60[8] * *(float *)&v60[8]
            + *(float *)&v60[4] * *(float *)&v60[4];
        if ( v25 != 0.0 )
        {
          v26 = 1.0 / sqrt(v25);
          dir[2].x = *(float *)v60 * v26;
          dir[2].y = *(float *)&v60[4] * v26;
          dir[2].z = *(float *)&v60[8] * v26;
        }
        qglBegin(2u);
        v27 = 0;
        p_z = &dir[0].z;
        do
        {
          v29 = v27 + 1;
          v30 = (v27 + 1) % 3;
          v31 = *(p_z - 2) + dir[v30].x;
          v32 = &dir[v30];
          v33 = dir[v30].y + *(p_z - 1);
          v91 = dir[v30].z + *p_z;
          v84 = v31 * 0.5;
          dir[4].x = v84;
          v34 = v33 * 0.5;
          v35 = v91 * 0.5;
          dir[4].y = v34;
          dir[4].z = v35;
          v36 = v84 * v84 + v35 * v35 + v34 * v34;
          if ( v36 != 0.0 )
          {
            v37 = 1.0 / sqrt(v36);
            dir[4].x = v84 * v37;
            dir[4].y = v34 * v37;
            dir[4].z = v35 * v37;
          }
          v38 = dir[4].x + *(p_z - 2);
          v39 = dir[4].y + *(p_z - 1);
          v90 = dir[4].z + *p_z;
          v83 = v38 * 0.5;
          dir[3].x = v83;
          v40 = v39 * 0.5;
          v41 = v90 * 0.5;
          dir[3].y = v40;
          dir[3].z = v41;
          v42 = v83 * v83 + v41 * v41 + v40 * v40;
          if ( v42 != 0.0 )
          {
            v43 = 1.0 / sqrt(v42);
            dir[3].x = v83 * v43;
            dir[3].y = v40 * v43;
            dir[3].z = v41 * v43;
          }
          v44 = dir[4].x + v32->x;
          v45 = dir[4].y + v32->y;
          v92 = dir[4].z + v32->z;
          v82 = v44 * 0.5;
          dir[5].x = v82;
          v46 = v45 * 0.5;
          v47 = v92 * 0.5;
          dir[5].y = v46;
          dir[5].z = v47;
          v48 = v47 * v47 + v46 * v46 + v82 * v82;
          if ( v48 != 0.0 )
          {
            v49 = 1.0 / sqrt(v48);
            dir[5].x = v82 * v49;
            dir[5].y = v46 * v49;
            dir[5].z = v47 * v49;
          }
          v50 = &p[v30];
          v51 = radius * *(p_z - 2);
          v52 = radius * *(p_z - 1);
          v87 = radius * *p_z;
          v78 = v51 + p[v30].x;
          v79 = v52 + p[v30].y;
          v80 = v87 + p[v30].z;
          qglVertex3f(v78, v79, v80);
          v85 = dir[3].z * radius;
          v72 = dir[3].x * radius + v50->x;
          v73 = dir[3].y * radius + v50->y;
          v74 = v85 + v50->z;
          qglVertex3f(v72, v73, v74);
          v89 = dir[4].z * radius;
          v66 = dir[4].x * radius + v50->x;
          v67 = dir[4].y * radius + v50->y;
          v68 = v89 + v50->z;
          qglVertex3f(v66, v67, v68);
          v86 = dir[5].z * radius;
          v75 = dir[5].x * radius + v50->x;
          v76 = dir[5].y * radius + v50->y;
          v77 = v86 + v50->z;
          qglVertex3f(v75, v76, v77);
          v53 = radius * v32->x;
          v54 = radius * v32->y;
          v88 = radius * v32->z;
          v69 = v53 + v50->x;
          v70 = v54 + v50->y;
          v71 = v88 + v50->z;
          qglVertex3f(v69, v70, v71);
          v27 = v29;
          p_z += 3;
        }
        while ( v29 < 3 );
        qglEnd();
        v3 = tri;
        v4 = i;
      }
      v4 += 3;
      v5 = v4 < v3->numIndexes;
      i = v4;
    }
    while ( v5 );
  }
}

// FUNC: struct localTrace_s __cdecl R_LocalTrace(class idVec3 const &,class idVec3 const &,float,struct srfTriangles_s const *,class idMaterial const *)
localTrace_s *__cdecl R_LocalTrace(
        localTrace_s *result,
        const idVec3 *start,
        const idVec3 *end,
        float radius,
        srfTriangles_s *tri,
        idMaterial *shader)
{
  const idVec3 *v6; // ebx
  double x; // st7
  double v8; // st7
  double z; // st6
  long double v10; // st6
  long double v11; // st6
  double v12; // st6
  double v13; // st5
  double v14; // st3
  double v15; // st7
  double v16; // st6
  double v17; // st5
  srfTriangles_s *v18; // esi
  double v19; // st4
  char *v20; // eax
  void *v21; // esp
  bool v22; // zf
  rvMesh *primBatchMesh; // ecx
  double v24; // st7
  double v25; // st6
  int v26; // edi
  bool v27; // cc
  int *indexes; // eax
  int v29; // edx
  unsigned __int8 v30; // al
  double y; // st7
  idVec3 *v32; // ecx
  double v33; // st7
  int *v34; // eax
  idDrawVert *verts; // edx
  int v36; // eax
  double v37; // st7
  float *v38; // eax
  double v39; // st7
  float *p_x; // eax
  double v41; // st7
  double v42; // st7
  int v43; // eax
  double v44; // st7
  float *v45; // eax
  double v46; // st7
  double v47; // st6
  double v48; // st5
  double v49; // st7
  idDrawVert *v50; // edx
  int v51; // eax
  double v52; // st7
  double v53; // st6
  idDrawVert *v54; // edx
  int v55; // eax
  float *v56; // eax
  double v57; // st7
  double v58; // st7
  idDrawVert *v59; // edx
  int v60; // eax
  double v61; // st7
  float *v62; // eax
  double v63; // st7
  double v64; // st6
  double v65; // st5
  double v66; // st7
  idDrawVert *v67; // edx
  double v68; // st7
  double v69; // st6
  idDrawVert *v70; // edx
  int v71; // eax
  double v72; // st7
  idDrawVert *v73; // edx
  int v74; // eax
  double v75; // st7
  float *v76; // eax
  double v77; // st7
  double v78; // st6
  double v79; // st5
  double v80; // st7
  int *v81; // edx
  int v82; // eax
  idDrawVert *v83; // ebx
  int v84; // edx
  double v85; // st7
  float *v86; // edx
  double v87; // st7
  float *v88; // eax
  double v89; // st7
  double v90; // st6
  idDrawVert *v91; // edx
  int *v92; // eax
  localTrace_s *v93; // eax
  int v94; // [esp+4h] [ebp-F0h] BYREF
  float v95; // [esp+14h] [ebp-E0h]
  localTrace_s hit; // [esp+18h] [ebp-DCh] BYREF
  idPlane planes[4]; // [esp+74h] [ebp-80h] BYREF
  idVec3 point; // [esp+B4h] [ebp-40h] BYREF
  unsigned __int8 *cullBits; // [esp+C0h] [ebp-34h]
  int c_testPlanes; // [esp+C4h] [ebp-30h] BYREF
  float v101; // [esp+C8h] [ebp-2Ch]
  float v102; // [esp+CCh] [ebp-28h]
  float v103; // [esp+D0h] [ebp-24h]
  int c_intersect; // [esp+D4h] [ebp-20h] BYREF
  int c_testEdges; // [esp+D8h] [ebp-1Ch] BYREF
  float v106; // [esp+DCh] [ebp-18h]
  float v107; // [esp+E0h] [ebp-14h]
  float v108; // [esp+E4h] [ebp-10h]
  idVec3 v109; // [esp+E8h] [ebp-Ch]
  float v110; // [esp+F4h] [ebp+0h]
  float v111; // [esp+F8h] [ebp+4h]
  float v112; // [esp+FCh] [ebp+8h]
  float v113; // [esp+100h] [ebp+Ch]
  idVec3 startDir; // [esp+104h] [ebp+10h]
  int j; // [esp+110h] [ebp+1Ch]
  float v116; // [esp+114h] [ebp+20h]
  float v117; // [esp+118h] [ebp+24h]
  float v118; // [esp+11Ch] [ebp+28h]
  float v119; // [esp+120h] [ebp+2Ch]
  float v120; // [esp+124h] [ebp+30h]
  float v121; // [esp+128h] [ebp+34h]
  float v122; // [esp+12Ch] [ebp+38h]
  float v123; // [esp+130h] [ebp+3Ch]
  float v124; // [esp+134h] [ebp+40h]
  float v125; // [esp+138h] [ebp+44h]
  float v126; // [esp+13Ch] [ebp+48h]
  float v127; // [esp+140h] [ebp+4Ch]
  float radiusSqr; // [esp+144h] [ebp+50h]
  float f; // [esp+148h] [ebp+54h]
  float *v130; // [esp+14Ch] [ebp+58h]
  float d2; // [esp+150h] [ebp+5Ch]

  v6 = start;
  x = end->x;
  hit.fraction = 1.0;
  v8 = x - start->x;
  v116 = v8;
  v117 = end->y - start->y;
  z = end->z;
  startDir.y = v117;
  v118 = z - start->z;
  startDir.z = v118;
  v113 = v118 * v118 + v117 * v117 + v116 * v116;
  if ( v113 != 0.0 )
  {
    *(float *)&j = 1.0 / sqrt(v113);
    v8 = v116 * *(float *)&j;
    startDir.y = v117 * *(float *)&j;
    startDir.z = v118 * *(float *)&j;
  }
  planes[0].c = 0.0;
  v10 = startDir.y * startDir.y + v8 * v8;
  if ( v10 == 0.0 )
  {
    planes[0].a = 1.0;
    planes[0].b = 0.0;
  }
  else
  {
    v11 = 1.0 / sqrt(v10);
    planes[0].a = -(startDir.y * v11);
    planes[0].b = v11 * v8;
  }
  planes[2].b = startDir.y;
  planes[2].c = startDir.z;
  v12 = planes[0].b * startDir.z - startDir.y * 0.0;
  v111 = v8 * 0.0 - startDir.z * planes[0].a;
  v112 = startDir.y * planes[0].a - planes[0].b * v8;
  planes[1].a = v12;
  planes[1].b = v111;
  planes[1].c = v112;
  v13 = -start->x;
  v109.x = v13;
  v109.y = -start->y;
  v14 = -start->z;
  planes[0].d = v109.x * planes[0].a + v109.y * planes[0].b + v14 * 0.0;
  v109.x = v13;
  planes[1].d = v109.x * v12 + v14 * v112 + v109.y * v111;
  planes[2].a = v8;
  planes[2].d = v13 * v8 + -start->z * startDir.z + -start->y * startDir.y;
  v15 = -v8;
  v16 = -startDir.y;
  v17 = -startDir.z;
  planes[3].a = v15;
  planes[3].b = v16;
  planes[3].c = v17;
  v18 = tri;
  v19 = -end->x;
  tri = (srfTriangles_s *)tri->numVerts;
  v20 = (char *)&tri->bounds.b[1].y + 2;
  LOBYTE(v20) = ((_BYTE)tri + 18) & 0xFC;
  planes[3].d = v19 * v15 + -end->z * v17 + -end->y * v16;
  v21 = alloca((int)v20);
  v22 = v18->primBatchMesh == 0;
  cullBits = (unsigned __int8 *)&v94;
  if ( v22 )
    ((void (__thiscall *)(idSIMDProcessor *, char *, _DWORD, idPlane *, idDrawVert *, srfTriangles_s *))SIMDProcessor->TracePointCull)(
      SIMDProcessor,
      (char *)&tri + 3,
      LODWORD(radius),
      planes,
      v18->verts,
      tri);
  else
    (*(void (__thiscall **)(idSIMDProcessor *, char *, _DWORD, idPlane *, rvSilTraceVertT *, srfTriangles_s *))SIMDProcessor->gap120)(
      SIMDProcessor,
      (char *)&tri + 3,
      LODWORD(radius),
      planes,
      v18->silTraceVerts,
      tri);
  if ( ((HIBYTE(tri) ^ (HIBYTE(tri) >> 4)) & 3) == 0 && ((HIBYTE(tri) ^ (HIBYTE(tri) >> 1)) & 4) == 0 )
  {
    if ( !v18->facePlanes || !v18->facePlanesCalculated )
      R_DeriveFacePlanes(v18);
    primBatchMesh = v18->primBatchMesh;
    if ( primBatchMesh )
    {
      rvMesh::LocalTrace(
        primBatchMesh,
        &hit,
        &c_testPlanes,
        &c_testEdges,
        &c_intersect,
        start,
        end,
        cullBits,
        v18->facePlanes,
        v18->silTraceVerts,
        radius,
        shader);
      goto LABEL_58;
    }
    c_testPlanes = 0;
    c_testEdges = 0;
    c_intersect = 0;
    radiusSqr = radius * radius;
    *(float *)&j = 0.0;
    v24 = end->x - start->x;
    v25 = end->y - start->y;
    v26 = 0;
    v27 = v18->numIndexes <= 0;
    point.z = end->z - start->z;
    startDir.z = point.z;
    startDir.x = v24;
    startDir.y = v25;
    if ( v27 )
    {
LABEL_57:
      backEnd.pc.c_renderPolysTraceTested += j;
      goto LABEL_58;
    }
    v113 = 0.0;
    while ( 1 )
    {
      indexes = v18->indexes;
      v29 = indexes[v26 + 2];
      f = *(float *)&indexes[v26 + 1];
      v30 = cullBits[v18->indexes[v26]] | cullBits[LODWORD(f)] | cullBits[v29];
      if ( ((v30 ^ (v30 >> 4)) & 3) != 0 )
        goto LABEL_56;
      if ( ((v30 ^ (v30 >> 1)) & 4) != 0 )
        goto LABEL_56;
      y = v6->y;
      v32 = (idVec3 *)((char *)v18->facePlanes + LODWORD(v113));
      ++c_testPlanes;
      f = y * v32->y + v6->x * v32->x + v32->z * v6->z + v32[1].x;
      d2 = end->z * v32->z + v32->y * end->y + end->x * v32->x + v32[1].x;
      if ( f <= (double)d2 )
        goto LABEL_56;
      if ( f < 0.0 )
        goto LABEL_56;
      if ( d2 > 0.0 )
        goto LABEL_56;
      v33 = f / (f - d2);
      f = v33;
      if ( v33 < 0.0 || f >= (double)hit.fraction )
        goto LABEL_56;
      ++c_testEdges;
      v109 = startDir;
      v95 = startDir.z * f;
      v116 = startDir.x * f + v6->x;
      point.x = v116;
      v117 = startDir.y * f + v6->y;
      point.y = v117;
      v34 = v18->indexes;
      v118 = v95 + v6->z;
      point.z = v118;
      verts = v18->verts;
      v36 = v34[v26] << 6;
      v37 = *(float *)((char *)&verts->xyz.x + v36);
      v38 = (float *)((char *)&verts->xyz.x + v36);
      v119 = v37 - v116;
      v120 = v38[1] - v117;
      v39 = v38[2];
      p_x = &verts[v18->indexes[v26 + 1]].xyz.x;
      v121 = v39 - v118;
      v122 = *p_x - v116;
      v123 = p_x[1] - v117;
      v41 = p_x[2] - v118;
      v124 = v41;
      v101 = v41 * v120 - v123 * v121;
      v102 = v121 * v122 - v124 * v119;
      v42 = v123 * v119 - v120 * v122;
      v103 = v42;
      if ( v42 * v32->z + v102 * v32->y + v101 * v32->x > 0.0 )
      {
        if ( radiusSqr <= 0.0 )
          goto LABEL_56;
        LODWORD(d2) = &v18->indexes[v26];
        v130 = &verts[*(_DWORD *)(LODWORD(d2) + 4)].xyz.x;
        v43 = *(_DWORD *)LODWORD(d2) << 6;
        v44 = *(float *)((char *)&verts->xyz.x + v43);
        v45 = (float *)((char *)&verts->xyz.x + v43);
        v46 = v44 - *v130;
        v47 = v45[1] - v130[1];
        v48 = v45[2] - v130[2];
        d2 = v46 * v46 + v48 * v48 + v47 * v47;
        if ( d2 * radiusSqr < v101 * v101 + v103 * v103 + v102 * v102 )
          goto LABEL_56;
        v49 = v46 * v119 + v48 * v121 + v47 * v120;
        if ( v49 >= 0.0 )
        {
          if ( v49 <= d2 )
            goto LABEL_35;
          v54 = v18->verts;
          v130 = &v54[v18->indexes[v26 + 2]].xyz.x;
          v55 = v18->indexes[v26 + 1] << 6;
          if ( (*(float *)((char *)&v54->xyz.x + v55) - *v130) * v122
             + (*(float *)((char *)&v54->xyz.z + v55) - v130[2]) * v124
             + (*(float *)((char *)&v54->xyz.y + v55) - v130[1]) * v123 >= 0.0 )
            goto LABEL_35;
          v52 = v122 * v122 + v124 * v124;
          v53 = v123 * v123;
        }
        else
        {
          v50 = v18->verts;
          v130 = &v50[v18->indexes[v26 + 2]].xyz.x;
          v51 = v18->indexes[v26] << 6;
          if ( (*(float *)((char *)&v50->xyz.x + v51) - *v130) * v119
             + (*(float *)((char *)&v50->xyz.z + v51) - v130[2]) * v121
             + (*(float *)((char *)&v50->xyz.y + v51) - v130[1]) * v120 >= 0.0 )
            goto LABEL_35;
          v52 = v119 * v119 + v121 * v121;
          v53 = v120 * v120;
        }
        if ( v52 + v53 > radiusSqr )
          goto LABEL_56;
      }
LABEL_35:
      v56 = &v18->verts[v18->indexes[v26 + 2]].xyz.x;
      v125 = *v56 - v116;
      v126 = v56[1] - v117;
      v57 = v56[2] - v118;
      v127 = v57;
      v106 = v57 * v123 - v126 * v124;
      v107 = v124 * v125 - v127 * v122;
      v58 = v126 * v122 - v123 * v125;
      v108 = v58;
      if ( v58 * v32->z + v107 * v32->y + v106 * v32->x > 0.0 )
      {
        if ( radiusSqr <= 0.0 )
          goto LABEL_56;
        v59 = v18->verts;
        v130 = &v59[v18->indexes[v26 + 2]].xyz.x;
        v60 = v18->indexes[v26 + 1] << 6;
        v61 = *(float *)((char *)&v59->xyz.x + v60);
        v62 = (float *)((char *)&v59->xyz.x + v60);
        v63 = v61 - *v130;
        v64 = v62[1] - v130[1];
        v65 = v62[2] - v130[2];
        d2 = v63 * v63 + v65 * v65 + v64 * v64;
        if ( d2 * radiusSqr < v106 * v106 + v108 * v108 + v107 * v107 )
          goto LABEL_56;
        v66 = v63 * v122 + v65 * v124 + v64 * v123;
        if ( v66 >= 0.0 )
        {
          if ( v66 > d2 )
          {
            v70 = v18->verts;
            v130 = &v70[v18->indexes[v26]].xyz.x;
            v71 = v18->indexes[v26 + 2] << 6;
            if ( (*(float *)((char *)&v70->xyz.x + v71) - *v130) * v125
               + (*(float *)((char *)&v70->xyz.z + v71) - v130[2]) * v127
               + (*(float *)((char *)&v70->xyz.y + v71) - v130[1]) * v126 < 0.0 )
            {
              v68 = v125 * v125 + v127 * v127;
              v69 = v126 * v126;
LABEL_44:
              if ( v68 + v69 > radiusSqr )
                goto LABEL_56;
            }
          }
        }
        else
        {
          v67 = v18->verts;
          v130 = (float *)&v18->indexes[v26];
          LODWORD(d2) = &v67[*(_DWORD *)v130];
          if ( (v67[*((_DWORD *)v130 + 1)].xyz.x - *(float *)LODWORD(d2)) * v122
             + (v67[*((_DWORD *)v130 + 1)].xyz.z - *(float *)(LODWORD(d2) + 8)) * v124
             + (v67[*((_DWORD *)v130 + 1)].xyz.y - *(float *)(LODWORD(d2) + 4)) * v123 < 0.0 )
          {
            v68 = v122 * v122 + v124 * v124;
            v69 = v123 * v123;
            goto LABEL_44;
          }
        }
      }
      v110 = v126 * v121 - v127 * v120;
      v111 = v127 * v119 - v121 * v125;
      v72 = v120 * v125 - v126 * v119;
      v112 = v72;
      if ( v72 * v32->z + v111 * v32->y + v110 * v32->x <= 0.0 )
        goto LABEL_55;
      if ( radiusSqr <= 0.0 )
        goto LABEL_56;
      v73 = v18->verts;
      v130 = &v73[v18->indexes[v26]].xyz.x;
      v74 = v18->indexes[v26 + 2] << 6;
      v75 = *(float *)((char *)&v73->xyz.x + v74);
      v76 = (float *)((char *)&v73->xyz.x + v74);
      v77 = v75 - *v130;
      v78 = v76[1] - v130[1];
      v79 = v76[2] - v130[2];
      d2 = v77 * v77 + v79 * v79 + v78 * v78;
      if ( d2 * radiusSqr < v110 * v110 + v112 * v112 + v111 * v111 )
        goto LABEL_56;
      v80 = v77 * v125 + v79 * v127 + v78 * v126;
      if ( v80 >= 0.0 )
      {
        if ( v80 <= d2
          || (v91 = v18->verts,
              v130 = (float *)&v18->indexes[v26],
              LODWORD(d2) = &v91[*((_DWORD *)v130 + 1)],
              (v91[*(_DWORD *)v130].xyz.x - *(float *)LODWORD(d2)) * v119
            + (v91[*(_DWORD *)v130].xyz.z - *(float *)(LODWORD(d2) + 8)) * v121
            + (v91[*(_DWORD *)v130].xyz.y - *(float *)(LODWORD(d2) + 4)) * v120 >= 0.0) )
        {
LABEL_55:
          ++c_intersect;
          hit.fraction = f;
          hit.normal = *v32;
          hit.point.z = v118;
          v92 = v18->indexes;
          hit.point.x = v116;
          hit.point.y = v117;
          hit.indexes[0] = v92[v26];
          hit.indexes[1] = v92[v26 + 1];
          hit.indexes[2] = v92[v26 + 2];
          hit.materialType = R_GetMaterialType(shader, v18, j, &point);
          goto LABEL_56;
        }
        v89 = v119 * v119 + v121 * v121;
        v90 = v120 * v120;
      }
      else
      {
        v81 = v18->indexes;
        v82 = v81[v26 + 1];
        v83 = v18->verts;
        v84 = v81[v26 + 2] << 6;
        v85 = *(float *)((char *)&v83->xyz.x + v84);
        v86 = (float *)((char *)&v83->xyz.x + v84);
        v82 <<= 6;
        v87 = v85 - *(float *)((char *)&v83->xyz.x + v82);
        v88 = (float *)((char *)&v83->xyz.x + v82);
        v6 = start;
        if ( v87 * v125 + (v86[2] - v88[2]) * v127 + (v86[1] - v88[1]) * v126 >= 0.0 )
          goto LABEL_55;
        v89 = v125 * v125 + v127 * v127;
        v90 = v126 * v126;
      }
      if ( v89 + v90 <= radiusSqr )
        goto LABEL_55;
LABEL_56:
      ++j;
      LODWORD(v113) += 16;
      v26 += 3;
      if ( v26 >= v18->numIndexes )
        goto LABEL_57;
    }
  }
LABEL_58:
  v93 = result;
  qmemcpy(result, &hit, sizeof(localTrace_s));
  return v93;
}

// FUNC: void __cdecl RB_ShowTrace(struct drawSurf_s * *,int)
void __cdecl RB_ShowTrace(drawSurf_s **drawSurfs, int numDrawSurfs)
{
  int integerValue; // eax
  idImage *v3; // eax
  int i; // ebx
  drawSurf_s *v5; // edi
  srfTriangles_s *geo; // esi
  double v7; // st7
  double v8; // st6
  double x; // st5
  double v10; // st4
  localTrace_s *v11; // eax
  float radius; // [esp+0h] [ebp-14Ch]
  idVec3 localStart; // [esp+4h] [ebp-148h] BYREF
  idVec3 end; // [esp+10h] [ebp-13Ch] BYREF
  idVec3 start; // [esp+1Ch] [ebp-130h] BYREF
  idVec3 localEnd; // [esp+28h] [ebp-124h] BYREF
  idBounds bounds; // [esp+34h] [ebp-118h] BYREF
  idBounds v18; // [esp+4Ch] [ebp-100h] BYREF
  float v19; // [esp+6Ch] [ebp-E0h]
  float v20; // [esp+78h] [ebp-D4h]
  float v21; // [esp+84h] [ebp-C8h]
  float v22; // [esp+90h] [ebp-BCh]
  localTrace_s hit; // [esp+94h] [ebp-B8h] BYREF
  localTrace_s result; // [esp+F0h] [ebp-5Ch] BYREF

  integerValue = r_showTrace.internalVar->integerValue;
  if ( integerValue )
  {
    radius = 5.0;
    if ( integerValue != 2 )
      radius = 0.0;
    start = backEnd.viewDef->renderView.vieworg;
    localStart = backEnd.viewDef->renderView.viewaxis.mat[0];
    end.y = localStart.y * 4000.0;
    end.z = localStart.z * 4000.0;
    localEnd.z = end.z + start.z;
    end.z = localEnd.z;
    end.x = localStart.x * 4000.0 + start.x;
    end.y = end.y + start.y;
    GL_DisableTexCoordState();
    GL_TexEnv(8448);
    v3 = globalImages->GetWhiteImage(globalImages);
    v3->Bind(v3);
    for ( i = 0; i < numDrawSurfs; ++i )
    {
      v5 = drawSurfs[i];
      geo = (srfTriangles_s *)v5->geo;
      if ( v5->geo )
      {
        if ( geo->verts )
        {
          R_GlobalPointToLocal(v5->space->modelMatrix, &start, &localStart);
          R_GlobalPointToLocal(v5->space->modelMatrix, &end, &localEnd);
          v7 = radius + geo->bounds.b[1].x;
          v8 = radius + geo->bounds.b[1].y;
          v19 = radius + geo->bounds.b[1].z;
          x = geo->bounds.b[0].x;
          v18.b[1].z = v19;
          v10 = geo->bounds.b[0].y - radius;
          v22 = geo->bounds.b[0].z - radius;
          v18.b[0].z = v22;
          v18.b[0].x = x - radius;
          v18.b[0].y = v10;
          v18.b[1].x = v7;
          v18.b[1].y = v8;
          if ( idBounds::LineIntersection(&v18, &localStart, &localEnd) )
          {
            qglLoadMatrixf(v5->space->modelViewMatrix);
            GL_State(101);
            qglColor4f(1.0, 0.0, 0.0, 0.25);
            RB_DrawElementsImmediate(geo);
            GL_State(0x10000);
            qglColor4f(1.0, 1.0, 1.0, 1.0);
            RB_DrawBounds(&geo->bounds);
            if ( radius != 0.0 )
            {
              qglColor4f(0.5, 0.5, 1.0, 1.0);
              RB_DrawExpandedTriangles(geo, radius, &localStart);
            }
            v11 = R_LocalTrace(&result, &localStart, &localEnd, radius, geo, (idMaterial *)v5->material);
            localTrace_s::operator=(&hit, v11);
            if ( hit.fraction < 1.0 )
            {
              qglColor4f(1.0, 1.0, 1.0, 1.0);
              v21 = hit.point.z + 1.0;
              bounds.b[1].z = v21;
              v20 = hit.point.z - 1.0;
              bounds.b[0].z = v20;
              bounds.b[0].x = hit.point.x - 1.0;
              bounds.b[0].y = hit.point.y - 1.0;
              bounds.b[1].x = hit.point.x + 1.0;
              bounds.b[1].y = hit.point.y + 1.0;
              RB_DrawBounds(&bounds);
            }
          }
        }
      }
    }
  }
}
