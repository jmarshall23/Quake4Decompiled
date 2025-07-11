
// FUNC: private: void __thiscall idCollisionModelManagerLocal::CM_GetCollisionPointTexCoords(class idVec2 &,struct cm_traceWork_t *,struct cm_polygon_t *)
void __thiscall idCollisionModelManagerLocal::CM_GetCollisionPointTexCoords(
        idCollisionModelManagerLocal *this,
        idVec2 *tc,
        cm_traceWork_t *tw,
        cm_polygon_t *poly)
{
  double v5; // st7
  int v6; // ecx
  float y; // edx
  float z; // eax
  float x; // edx
  float v10; // eax
  float v11; // edx
  float v12; // eax
  float v13; // edx
  float v14; // eax
  float v15[2]; // [esp+Ch] [ebp-30h]
  float v16; // [esp+14h] [ebp-28h]
  idVec3 t[3]; // [esp+18h] [ebp-24h] BYREF
  float tca; // [esp+40h] [ebp+4h]

  tc->x = 0.5;
  tc->y = 0.5;
  v15[0] = poly->bounds.b[1].x - poly->bounds.b[0].x;
  v5 = poly->bounds.b[1].y - poly->bounds.b[0].y;
  v15[1] = v5;
  v16 = poly->bounds.b[1].z - poly->bounds.b[0].z;
  v6 = v5 > v15[0];
  if ( v16 > (double)v15[v6] )
    v6 = 2;
  y = poly->bounds.b[0].y;
  t[0].x = poly->bounds.b[0].x;
  z = poly->bounds.b[0].z;
  t[0].y = y;
  x = poly->bounds.b[1].x;
  t[0].z = z;
  v10 = poly->bounds.b[1].y;
  t[1].x = x;
  v11 = poly->bounds.b[1].z;
  t[1].y = v10;
  v12 = poly->bounds.b[0].x;
  t[1].z = v11;
  v13 = poly->bounds.b[0].y;
  t[2].x = v12;
  v14 = poly->bounds.b[0].z;
  t[2].y = v13;
  t[2].z = v14;
  *((_DWORD *)&t[2].x + v6) = *((_DWORD *)&poly->bounds.b[1].x + v6);
  tca = idMath::BarycentricTriangleArea((const idVec3 *)&poly->plane, t, &t[1], &t[2]);
  if ( tca != 0.0 )
    idMath::BarycentricEvaluate(tc, &tw->trace.c.point, (const idVec3 *)&poly->plane, tca, t, poly->texBounds);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::CM_GetMaterialType(struct cm_traceWork_t *,struct cm_polygon_t *)
void __thiscall idCollisionModelManagerLocal::CM_GetMaterialType(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_polygon_t *poly)
{
  idMaterial *material; // edi
  idVec2 tc; // [esp+8h] [ebp-8h] BYREF

  material = (idMaterial *)tw->trace.c.material;
  tw->trace.c.materialType = 0;
  if ( material )
  {
    if ( poly && material->materialTypeArray )
    {
      idCollisionModelManagerLocal::CM_GetCollisionPointTexCoords(this, &tc, tw, poly);
      tw->trace.c.materialType = idMaterial::GetMaterialType(material, &tc);
    }
    else
    {
      tw->trace.c.materialType = material->materialType;
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::TranslateTrmEdgeThroughPolygon(struct cm_traceWork_t *,struct cm_polygon_t *,struct cm_trmEdge_t *)
void __thiscall idCollisionModelManagerLocal::TranslateTrmEdgeThroughPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_polygon_t *poly,
        cm_trmEdge_t *trmEdge)
{
  cm_polygon_t *v4; // ecx
  int v5; // eax
  float *v6; // ebx
  int v7; // ecx
  cm_edge_t *v8; // edx
  cm_vertex_t *v9; // edi
  int v10; // eax
  cm_vertex_t *v11; // edx
  int v12; // eax
  int v13; // ecx
  cm_edge_t *v14; // eax
  int v15; // ecx
  int v16; // edx
  double v17; // st7
  double v18; // st7
  double v19; // st6
  double v20; // st5
  double v21; // st7
  double v22; // st7
  int v23; // eax
  int v24; // ecx
  double v25; // st7
  float *v26; // eax
  double v27; // st7
  float *v28; // ecx
  long double v29; // st4
  long double v30; // st7
  double v31; // st6
  double v32; // st7
  double v33; // st7
  const idMaterial *material; // eax
  double v35; // st7
  double v36; // st5
  double v37; // st4
  double v38; // rt0
  double v39; // st7
  double v40; // st6
  double v41; // st5
  double v42; // st7
  int numContacts; // ecx
  idPluecker *p_pl; // [esp+0h] [ebp-B0h]
  float v45; // [esp+0h] [ebp-B0h]
  idPluecker *v46; // [esp+0h] [ebp-B0h]
  float v47; // [esp+0h] [ebp-B0h]
  float f1b; // [esp+4h] [ebp-ACh]
  unsigned int f1; // [esp+4h] [ebp-ACh]
  float f1a; // [esp+4h] [ebp-ACh]
  float v51; // [esp+8h] [ebp-A8h]
  unsigned int sideSet; // [esp+8h] [ebp-A8h]
  unsigned int v2; // [esp+Ch] [ebp-A4h]
  cm_vertex_t *v2a; // [esp+Ch] [ebp-A4h]
  cm_edge_t *edge; // [esp+10h] [ebp-A0h]
  float v56; // [esp+14h] [ebp-9Ch]
  float v57; // [esp+18h] [ebp-98h]
  float v58; // [esp+1Ch] [ebp-94h]
  int i; // [esp+24h] [ebp-8Ch]
  int edgeNum; // [esp+28h] [ebp-88h]
  float epsPl_8; // [esp+34h] [ebp-7Ch]
  float epsPl_16; // [esp+3Ch] [ebp-74h]
  float v64; // [esp+50h] [ebp-60h]
  float v65; // [esp+54h] [ebp-5Ch]
  float v66; // [esp+5Ch] [ebp-54h]
  float v67; // [esp+68h] [ebp-48h]
  float v68; // [esp+6Ch] [ebp-44h]
  float v69; // [esp+70h] [ebp-40h]
  float v70; // [esp+78h] [ebp-38h]
  float v71; // [esp+7Ch] [ebp-34h]
  float v72; // [esp+80h] [ebp-30h]
  float v73; // [esp+84h] [ebp-2Ch]
  float v74; // [esp+94h] [ebp-1Ch]
  float v75; // [esp+A0h] [ebp-10h]
  float v76; // [esp+ACh] [ebp-4h]

  v4 = poly;
  v5 = 0;
  i = 0;
  if ( poly->numEdges > 0 )
  {
    v6 = &tw->polygonVertexPlueckerCache[1].p[2];
    do
    {
      v7 = v4->edges[v5];
      v8 = &tw->model->edges[abs32(v7)];
      edgeNum = v7;
      edge = v8;
      if ( v8->checkcount != this->checkCount && !v8->internal )
      {
        v9 = &tw->model->vertices[v8->vertexNum[(unsigned int)v7 >> 31]];
        v10 = 1 << trmEdge->bitNum;
        v2 = v9->sideSet;
        if ( (v2 & v10) == 0 )
        {
          f1b = *(v6 - 7) * trmEdge->pl.p[5]
              + *(v6 - 8) * trmEdge->pl.p[4]
              + *(v6 - 6) * trmEdge->pl.p[3]
              + *(v6 - 5) * trmEdge->pl.p[2]
              + *(v6 - 3) * trmEdge->pl.p[1]
              + *(v6 - 4) * trmEdge->pl.p[0];
          v9->side = (LODWORD(f1b) >> 31 << trmEdge->bitNum) | v9->side & ~v10;
          v9->sideSet = v10 | v2;
        }
        v11 = &tw->model->vertices[v8->vertexNum[v7 >= 0]];
        v12 = 1 << trmEdge->bitNum;
        v2a = v11;
        f1 = v11->sideSet;
        if ( (f1 & v12) == 0 )
        {
          v51 = *(v6 - 1) * trmEdge->pl.p[5]
              + *(v6 - 2) * trmEdge->pl.p[4]
              + v6[3] * trmEdge->pl.p[1]
              + v6[1] * trmEdge->pl.p[2]
              + trmEdge->pl.p[3] * *v6
              + v6[2] * trmEdge->pl.p[0];
          v11->side = (LODWORD(v51) >> 31 << trmEdge->bitNum) | v11->side & ~v12;
          v11->sideSet = v12 | f1;
        }
        if ( ((v9->side ^ v11->side) & (1 << LOBYTE(trmEdge->bitNum))) != 0 )
        {
          v13 = trmEdge->vertexNum[0];
          v14 = edge;
          sideSet = edge->sideSet;
          if ( (sideSet & (1 << v13)) == 0 )
          {
            p_pl = &tw->vertices[v13].pl;
            v45 = *(v6 - 391) * p_pl->p[5]
                + *(v6 - 392) * p_pl->p[4]
                + *(v6 - 390) * p_pl->p[3]
                + *(v6 - 389) * p_pl->p[2]
                + *(v6 - 387) * p_pl->p[1]
                + *(v6 - 388) * p_pl->p[0];
            v14 = edge;
            edge->side = (LODWORD(v45) >> 31 << trmEdge->vertexNum[0]) | edge->side & ~(1 << v13);
            edge->sideSet = (1 << v13) | sideSet;
          }
          v15 = trmEdge->vertexNum[1];
          if ( ((1 << v15) & v14->sideSet) == 0 )
          {
            v46 = &tw->vertices[v15].pl;
            v47 = *(v6 - 391) * v46->p[5]
                + *(v6 - 392) * v46->p[4]
                + *(v6 - 390) * v46->p[3]
                + *(v6 - 389) * v46->p[2]
                + *(v6 - 387) * v46->p[1]
                + *(v6 - 388) * v46->p[0];
            v16 = (LODWORD(v47) >> 31 << trmEdge->vertexNum[1]) | v14->side & ~(1 << v15);
            v14 = edge;
            edge->side = v16;
            edge->sideSet |= 1 << v15;
          }
          if ( (((unsigned __int8)(v14->side >> trmEdge->vertexNum[1]) ^ (unsigned __int8)(v14->side >> trmEdge->vertexNum[0])) & 1) != 0 )
          {
            v17 = trmEdge->cross.z * *(v6 - 390) + trmEdge->cross.y * *(v6 - 387) + trmEdge->cross.x * *(v6 - 388);
            if ( v17 != 0.0 )
            {
              f1a = (trmEdge->pl.p[5] * *(v6 - 391)
                   + trmEdge->pl.p[3] * *(v6 - 390)
                   + trmEdge->pl.p[1] * *(v6 - 387)
                   + trmEdge->pl.p[4] * *(v6 - 392)
                   + trmEdge->pl.p[2] * *(v6 - 389)
                   + trmEdge->pl.p[0] * *(v6 - 388))
                  / v17;
              if ( f1a >= 0.0 )
              {
                v18 = edge->normal.x * 0.25;
                v19 = edge->normal.y * 0.25;
                v20 = edge->normal.z * 0.25;
                epsPl_8 = *(v6 - 390);
                v64 = v19 * epsPl_8 + v18 * *(v6 - 387) + *(v6 - 392);
                v65 = *(v6 - 391) - v18 * *(v6 - 388) + v20 * epsPl_8;
                epsPl_16 = *(v6 - 388);
                v21 = epsPl_8 * trmEdge->cross.z + *(v6 - 387) * trmEdge->cross.y + epsPl_16 * trmEdge->cross.x;
                if ( v21 != 0.0 )
                {
                  v66 = *(v6 - 389) - v19 * *(v6 - 388) - v20 * *(v6 - 387);
                  v22 = (v64 * trmEdge->pl.p[4]
                       + v66 * trmEdge->pl.p[2]
                       + v65 * trmEdge->pl.p[5]
                       + epsPl_8 * trmEdge->pl.p[3]
                       + *(v6 - 387) * trmEdge->pl.p[1]
                       + epsPl_16 * trmEdge->pl.p[0])
                      / v21;
                  if ( v22 <= 1.0 && f1a >= v22 )
                  {
                    if ( v22 < 0.0 )
                      v22 = 0.0;
                    if ( v22 < tw->trace.fraction )
                    {
                      v23 = trmEdge->vertexNum[1];
                      v24 = trmEdge->vertexNum[0];
                      tw->trace.fraction = v22;
                      v23 *= 96;
                      v25 = *(float *)((char *)&tw->vertices[0].p.x + v23);
                      v26 = (float *)((char *)tw + v23);
                      v24 *= 96;
                      v27 = v25 - *(float *)((char *)&tw->vertices[0].p.x + v24);
                      v28 = (float *)((char *)tw + v24);
                      v70 = v26[1] - v28[1];
                      v71 = v26[2] - v28[2];
                      v56 = v9->p.x - v2a->p.x;
                      v57 = v9->p.y - v2a->p.y;
                      v58 = v9->p.z - v2a->p.z;
                      v75 = v70 * v56 - v57 * v27;
                      tw->trace.c.normal.z = v75;
                      tw->trace.c.normal.x = v57 * v71 - v58 * v70;
                      tw->trace.c.normal.y = v58 * v27 - v71 * v56;
                      v29 = tw->trace.c.normal.x * tw->trace.c.normal.x
                          + tw->trace.c.normal.y * tw->trace.c.normal.y
                          + tw->trace.c.normal.z * tw->trace.c.normal.z;
                      if ( v29 != 0.0 )
                      {
                        v30 = 1.0 / sqrt(v29);
                        tw->trace.c.normal.x = v30 * tw->trace.c.normal.x;
                        tw->trace.c.normal.y = v30 * tw->trace.c.normal.y;
                        tw->trace.c.normal.z = v30 * tw->trace.c.normal.z;
                      }
                      if ( tw->dir.z * tw->trace.c.normal.z
                         + tw->dir.y * tw->trace.c.normal.y
                         + tw->dir.x * tw->trace.c.normal.x > 0.0 )
                      {
                        v74 = -tw->trace.c.normal.z;
                        v31 = -tw->trace.c.normal.x;
                        v32 = -tw->trace.c.normal.y;
                        tw->trace.c.normal.z = v74;
                        tw->trace.c.normal.x = v31;
                        tw->trace.c.normal.y = v32;
                      }
                      v33 = v9->p.z * tw->trace.c.normal.z
                          + v9->p.y * tw->trace.c.normal.y
                          + v9->p.x * tw->trace.c.normal.x;
                      tw->trace.c.dist = v33;
                      tw->trace.c.separation = tw->trace.c.normal.y * v28[1]
                                             + tw->trace.c.normal.z * v28[2]
                                             + *v28 * tw->trace.c.normal.x
                                             - v33;
                      tw->trace.c.contents = poly->contents;
                      material = poly->material;
                      tw->trace.c.modelFeature = edgeNum;
                      tw->trace.c.material = material;
                      tw->trace.c.type = CONTACT_EDGE;
                      tw->trace.c.trmFeature = ((char *)trmEdge - (char *)tw - 3072) / 96;
                      v35 = -trmEdge->cross.z;
                      v36 = -trmEdge->cross.x;
                      v37 = trmEdge->cross.y * v28[1] + v36 * v28[2] + v35 * *v28;
                      v67 = v2a->p.x - v9->p.x;
                      v68 = v2a->p.y - v9->p.y;
                      v69 = v2a->p.z - v9->p.z;
                      v38 = v36 * v9->p.z + trmEdge->cross.y * v9->p.y + v35 * v9->p.x - v37;
                      v39 = v38 / (v38 - (v36 * v2a->p.z + trmEdge->cross.y * v2a->p.y + v35 * v2a->p.x - v37));
                      v72 = v67 * v39;
                      v73 = v68 * v39;
                      v40 = v72 + v9->p.x;
                      v41 = v39 * v69;
                      v42 = v73 + v9->p.y;
                      v76 = v41 + v9->p.z;
                      tw->trace.c.point.z = v76;
                      tw->trace.c.point.x = v40;
                      tw->trace.c.point.y = v42;
                      idCollisionModelManagerLocal::CM_GetMaterialType(this, tw, poly);
                      if ( tw->getContacts )
                      {
                        numContacts = tw->numContacts;
                        if ( numContacts < tw->maxContacts )
                        {
                          contactInfo_t::operator=(&tw->contacts[numContacts], &tw->trace.c);
                          ++tw->numContacts;
                          tw->trace.fraction = 1.0;
                        }
                      }
                      else if ( tw->trace.fraction == 0.0 )
                      {
                        return;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      v4 = poly;
      v5 = i + 1;
      v6 += 6;
      ++i;
    }
    while ( i < poly->numEdges );
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::TranslateTrmVertexThroughPolygon(struct cm_traceWork_t *,struct cm_polygon_t *,struct cm_trmVertex_t *,int)
void __thiscall idCollisionModelManagerLocal::TranslateTrmVertexThroughPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_polygon_t *poly,
        cm_trmVertex_t *v,
        char bitNum)
{
  double v7; // st7
  double v8; // st7
  double v9; // st7
  float *v11; // ebp
  cm_edge_t *v12; // eax
  bool v13; // cc
  idCollisionModelLocal *model; // edx
  double fraction; // st7
  double v16; // st6
  double v17; // st5
  double v18; // st7
  int numContacts; // ecx
  float v20; // [esp+Ch] [ebp-24h]
  unsigned int sideSet; // [esp+10h] [ebp-20h]
  unsigned int edgeNum; // [esp+14h] [ebp-1Ch]
  float v23; // [esp+18h] [ebp-18h]
  float v24; // [esp+18h] [ebp-18h]
  float v25; // [esp+1Ch] [ebp-14h]
  float v26; // [esp+1Ch] [ebp-14h]
  float v27; // [esp+20h] [ebp-10h]
  float v28; // [esp+2Ch] [ebp-4h]
  cm_traceWork_t *twa; // [esp+34h] [ebp+4h]
  float polya; // [esp+38h] [ebp+8h]
  int polyb; // [esp+38h] [ebp+8h]
  float va; // [esp+3Ch] [ebp+Ch]
  cm_trmVertex_t *vb; // [esp+3Ch] [ebp+Ch]

  v7 = v->endp.y * poly->plane.b + v->endp.z * poly->plane.c + v->endp.x * poly->plane.a + poly->plane.d;
  polya = v7;
  if ( v7 < 0.25 )
  {
    v9 = v->p.y * poly->plane.b + v->p.z * poly->plane.c + v->p.x * poly->plane.a + poly->plane.d;
    va = v9;
    if ( v9 >= 0.0 )
    {
      if ( va > (double)polya )
        v8 = (va - 0.25) / (va - polya);
      else
        v8 = 1.0;
    }
    else
    {
      v8 = 1.0;
    }
  }
  else
  {
    v8 = 1.0;
  }
  if ( v8 < tw->trace.fraction )
  {
    vb = 0;
    if ( poly->numEdges <= 0 )
    {
LABEL_15:
      if ( v8 < 0.0 )
        v8 = 0.0;
      tw->trace.fraction = v8;
      tw->trace.c.normal.x = poly->plane.a;
      tw->trace.c.normal.y = poly->plane.b;
      tw->trace.c.normal.z = poly->plane.c;
      model = tw->model;
      tw->trace.c.dist = -poly->plane.d;
      tw->trace.c.separation = poly->plane.c * v->p.z + poly->plane.b * v->p.y + poly->plane.a * v->p.x + poly->plane.d;
      tw->trace.c.contents = poly->contents;
      tw->trace.c.material = poly->material;
      tw->trace.c.type = CONTACT_TRMVERTEX;
      tw->trace.c.modelFeature = poly - model->polygons;
      tw->trace.c.trmFeature = ((char *)v - (char *)tw) / 96;
      v23 = v->endp.x - v->p.x;
      v25 = v->endp.y - v->p.y;
      v27 = v->endp.z - v->p.z;
      fraction = tw->trace.fraction;
      v24 = v23 * fraction;
      v26 = v25 * fraction;
      v16 = v24 + v->p.x;
      v17 = fraction * v27;
      v18 = v26 + v->p.y;
      v28 = v17 + v->p.z;
      tw->trace.c.point.z = v28;
      tw->trace.c.point.x = v16;
      tw->trace.c.point.y = v18;
      if ( tw->getContacts )
      {
        numContacts = tw->numContacts;
        if ( numContacts < tw->maxContacts )
        {
          contactInfo_t::operator=(&tw->contacts[numContacts], &tw->trace.c);
          ++tw->numContacts;
          tw->trace.fraction = 1.0;
        }
        v->used = 0;
      }
    }
    else
    {
      v11 = &tw->polygonEdgePlueckerCache[0].p[2];
      twa = (cm_traceWork_t *)&tw->polygonEdgePlueckerCache[0].p[2];
      polyb = 1 << bitNum;
      while ( 1 )
      {
        edgeNum = poly->edges[(_DWORD)vb];
        v12 = &tw->model->edges[abs32(edgeNum)];
        sideSet = v12->sideSet;
        if ( (sideSet & polyb) == 0 )
        {
          v20 = *(v11 - 1) * v->pl.p[5]
              + *(v11 - 2) * v->pl.p[4]
              + v11[3] * v->pl.p[1]
              + v11[1] * v->pl.p[2]
              + v11[2] * v->pl.p[0]
              + v->pl.p[3] * *v11;
          v11 = (float *)twa;
          v12->side = (LODWORD(v20) >> 31 << bitNum) | v12->side & ~polyb;
          v12->sideSet = polyb | sideSet;
        }
        if ( edgeNum >> 31 != ((v12->side >> bitNum) & 1) )
          break;
        v11 += 6;
        v13 = (int)&vb->p.x + 1 < poly->numEdges;
        vb = (cm_trmVertex_t *)((char *)vb + 1);
        twa = (cm_traceWork_t *)v11;
        if ( !v13 )
          goto LABEL_15;
      }
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::TranslatePointThroughPolygon(struct cm_traceWork_t *,struct cm_polygon_t *,struct cm_trmVertex_t *)
void __thiscall idCollisionModelManagerLocal::TranslatePointThroughPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_polygon_t *poly,
        cm_trmVertex_t *v)
{
  double y; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  unsigned int v10; // ebx
  cm_edge_t *v11; // ecx
  int v12; // eax
  cm_vertex_t *vertices; // edx
  float *p_x; // eax
  double x; // st6
  float *v16; // edx
  double v17; // st6
  double v18; // st5
  double v19; // st4
  double v20; // st3
  double v21; // st2
  double v22; // st1
  idCollisionModelLocal *model; // edx
  unsigned int v24; // edx
  double v25; // st7
  double z; // st7
  double fraction; // st7
  double v28; // st6
  double v29; // st5
  double v30; // st7
  idMaterial *material; // ebx
  int numContacts; // ecx
  idVec2 tc; // [esp+Ch] [ebp-2Ch] BYREF
  float v34; // [esp+14h] [ebp-24h]
  float v35; // [esp+18h] [ebp-20h]
  float v36; // [esp+1Ch] [ebp-1Ch]
  idPluecker pl; // [esp+20h] [ebp-18h]
  int edgeNum; // [esp+40h] [ebp+8h]
  float edgeNuma; // [esp+40h] [ebp+8h]
  float fl; // [esp+44h] [ebp+Ch]
  int fla; // [esp+44h] [ebp+Ch]

  y = v->endp.y;
  LODWORD(tc.x) = this;
  v7 = y * poly->plane.b + v->endp.z * poly->plane.c + poly->plane.a * v->endp.x + poly->plane.d;
  *(float *)&edgeNum = v7;
  if ( v7 < 0.25 )
  {
    v9 = v->p.y * poly->plane.b + v->p.z * poly->plane.c + poly->plane.a * v->p.x + poly->plane.d;
    fl = v9;
    if ( v9 >= 0.0 )
    {
      if ( fl > (double)*(float *)&edgeNum )
        v8 = (fl - 0.25) / (fl - *(float *)&edgeNum);
      else
        v8 = 1.0;
    }
    else
    {
      v8 = 1.0;
    }
  }
  else
  {
    v8 = 1.0;
  }
  if ( v8 < tw->trace.fraction )
  {
    fla = 0;
    if ( poly->numEdges <= 0 )
    {
LABEL_14:
      if ( v8 < 0.0 )
        v8 = 0.0;
      tw->trace.fraction = v8;
      tw->trace.c.normal = *(idVec3 *)&poly->plane.a;
      model = tw->model;
      tw->trace.c.dist = -poly->plane.d;
      tw->trace.c.separation = poly->plane.c * v->p.z + poly->plane.b * v->p.y + poly->plane.a * v->p.x + poly->plane.d;
      tw->trace.c.contents = poly->contents;
      tw->trace.c.material = poly->material;
      tw->trace.c.type = CONTACT_TRMVERTEX;
      v24 = (int)((unsigned __int64)(780903145i64 * ((char *)poly - (char *)model->polygons)) >> 32) >> 4;
      tw->trace.c.modelFeature = v24 + (v24 >> 31);
      tw->trace.c.trmFeature = ((char *)v - (char *)tw) / 96;
      v34 = v->endp.x - v->p.x;
      v25 = v->endp.y;
      pl.p[0] = v34;
      v35 = v25 - v->p.y;
      z = v->endp.z;
      pl.p[1] = v35;
      v36 = z - v->p.z;
      fraction = tw->trace.fraction;
      pl.p[2] = v36;
      v34 = v34 * fraction;
      v35 = v35 * fraction;
      v28 = v34 + v->p.x;
      v29 = fraction * v36;
      v30 = v35 + v->p.y;
      pl.p[2] = v29 + v->p.z;
      tw->trace.c.point.z = pl.p[2];
      tw->trace.c.point.x = v28;
      tw->trace.c.point.y = v30;
      material = (idMaterial *)tw->trace.c.material;
      tw->trace.c.materialType = 0;
      if ( material )
      {
        if ( material->materialTypeArray )
        {
          idCollisionModelManagerLocal::CM_GetCollisionPointTexCoords(
            (idCollisionModelManagerLocal *)LODWORD(tc.x),
            &tc,
            tw,
            poly);
          tw->trace.c.materialType = idMaterial::GetMaterialType(material, &tc);
        }
        else
        {
          tw->trace.c.materialType = material->materialType;
        }
      }
      if ( tw->getContacts )
      {
        numContacts = tw->numContacts;
        if ( numContacts < tw->maxContacts )
        {
          contactInfo_t::operator=(&tw->contacts[numContacts], &tw->trace.c);
          ++tw->numContacts;
          tw->trace.fraction = 1.0;
        }
        v->used = 0;
      }
    }
    else
    {
      while ( 1 )
      {
        v10 = poly->edges[fla];
        v11 = &tw->model->edges[abs32(v10)];
        v12 = *(_DWORD *)(LODWORD(tc.x) + 60);
        if ( v11->checkcount != v12 )
        {
          v11->checkcount = v12;
          vertices = tw->model->vertices;
          p_x = &vertices[v11->vertexNum[1]].p.x;
          x = vertices[v11->vertexNum[0]].p.x;
          v16 = &vertices[v11->vertexNum[0]].p.x;
          v17 = x * p_x[1] - v16[1] * *p_x;
          v18 = p_x[2] * *v16 - *p_x * v16[2];
          v19 = *v16 - *p_x;
          v20 = p_x[2] * v16[1] - p_x[1] * v16[2];
          v21 = v16[2] - p_x[2];
          v22 = p_x[1] - v16[1];
          pl.p[5] = v22;
          edgeNuma = v22 * v->pl.p[1]
                   + v20 * v->pl.p[2]
                   + v19 * v->pl.p[3]
                   + v18 * v->pl.p[5]
                   + v17 * v->pl.p[4]
                   + v21 * v->pl.p[0];
          v11->side = LODWORD(edgeNuma) >> 31;
        }
        if ( v11->side != v10 >> 31 )
          break;
        if ( ++fla >= poly->numEdges )
          goto LABEL_14;
      }
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::TranslateVertexThroughTrmPolygon(struct cm_traceWork_t *,struct cm_trmPolygon_t *,struct cm_polygon_t *,struct cm_vertex_t *,class idVec3 &,class idPluecker &)
void __thiscall idCollisionModelManagerLocal::TranslateVertexThroughTrmPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_trmPolygon_t *trmpoly,
        cm_polygon_t *poly,
        cm_vertex_t *v,
        idVec3 *endp,
        idPluecker *pl)
{
  double v8; // st7
  double v9; // st6
  double v11; // st7
  double v12; // st7
  double v13; // st7
  idPluecker *v15; // ebp
  unsigned int v16; // eax
  __int16 x_high; // cx
  float *v18; // eax
  double v19; // st7
  double v20; // st6
  idCollisionModelLocal *model; // eax
  idMaterial *material; // edi
  const rvDeclMatType *MaterialType; // eax
  int numContacts; // ecx
  unsigned int edgeNum; // [esp+10h] [ebp-18h]
  idVec2 tc; // [esp+14h] [ebp-14h] BYREF
  float v27; // [esp+24h] [ebp-4h]
  unsigned int twa; // [esp+2Ch] [ebp+4h]
  float trmpolya; // [esp+30h] [ebp+8h]
  cm_trmPolygon_t *trmpolyb; // [esp+30h] [ebp+8h]
  float va; // [esp+38h] [ebp+10h]
  cm_vertex_t *vb; // [esp+38h] [ebp+10h]
  float endpa; // [esp+3Ch] [ebp+14h]

  v8 = endp->z * trmpoly->plane.c;
  v9 = endp->y * trmpoly->plane.b;
  LODWORD(tc.x) = this;
  v11 = v8 + v9 + trmpoly->plane.a * endp->x + trmpoly->plane.d;
  trmpolya = v11;
  if ( v11 < 0.25 )
  {
    v13 = v->p.z * trmpoly->plane.c + v->p.y * trmpoly->plane.b + v->p.x * trmpoly->plane.a + trmpoly->plane.d;
    va = v13;
    if ( v13 >= 0.0 )
    {
      if ( va > (double)trmpolya )
        v12 = (va - 0.25) / (va - trmpolya);
      else
        v12 = 1.0;
    }
    else
    {
      v12 = 1.0;
    }
  }
  else
  {
    v12 = 1.0;
  }
  if ( v12 < tw->trace.fraction )
  {
    trmpolyb = 0;
    if ( trmpoly->numEdges <= 0 )
    {
LABEL_15:
      if ( v12 < 0.0 )
        v12 = 0.0;
      tw->trace.fraction = v12;
      v19 = -trmpoly->plane.a;
      v20 = -trmpoly->plane.b;
      v27 = -trmpoly->plane.c;
      tw->trace.c.normal.z = v27;
      tw->trace.c.normal.x = v19;
      tw->trace.c.normal.y = v20;
      model = tw->model;
      tw->trace.c.dist = v->p.z * tw->trace.c.normal.z + v->p.y * tw->trace.c.normal.y + tw->trace.c.normal.x * v->p.x;
      tw->trace.c.separation = v->p.z * trmpoly->plane.c
                             + v->p.y * trmpoly->plane.b
                             + trmpoly->plane.a * v->p.x
                             + trmpoly->plane.d;
      tw->trace.c.contents = poly->contents;
      tw->trace.c.material = poly->material;
      tw->trace.c.type = CONTACT_MODELVERTEX;
      tw->trace.c.modelFeature = v - model->vertices;
      tw->trace.c.trmFeature = ((char *)trmpoly - (char *)tw - 6240) / 112;
      tw->trace.c.point.x = v->p.x;
      tw->trace.c.point.y = v->p.y;
      tw->trace.c.point.z = v->p.z;
      material = (idMaterial *)tw->trace.c.material;
      tw->trace.c.materialType = 0;
      if ( material )
      {
        if ( material->materialTypeArray )
        {
          idCollisionModelManagerLocal::CM_GetCollisionPointTexCoords(
            (idCollisionModelManagerLocal *)LODWORD(tc.x),
            &tc,
            tw,
            poly);
          MaterialType = idMaterial::GetMaterialType(material, &tc);
        }
        else
        {
          MaterialType = material->materialType;
        }
        tw->trace.c.materialType = MaterialType;
      }
      if ( tw->getContacts )
      {
        numContacts = tw->numContacts;
        if ( numContacts < tw->maxContacts )
        {
          contactInfo_t::operator=(&tw->contacts[numContacts], &tw->trace.c);
          ++tw->numContacts;
          tw->trace.fraction = 1.0;
        }
      }
    }
    else
    {
      v15 = pl;
      vb = (cm_vertex_t *)trmpoly->edges;
      while ( 1 )
      {
        edgeNum = vb->checkcount;
        v16 = abs32(vb->checkcount) + 32;
        x_high = HIWORD(tw->vertices[v16].p.x);
        v18 = (float *)((char *)tw + v16 * 96);
        twa = v->sideSet;
        if ( (twa & (1 << x_high)) == 0 )
        {
          endpa = v18[7] * v15->p[5]
                + v18[8] * v15->p[3]
                + v18[11] * v15->p[1]
                + v18[9] * v15->p[2]
                + v18[10] * v15->p[0]
                + v15->p[4] * v18[6];
          v15 = pl;
          v->side = (LODWORD(endpa) >> 31 << *((_WORD *)v18 + 1)) | v->side & ~(1 << x_high);
          v->sideSet = (1 << x_high) | twa;
        }
        if ( edgeNum >> 31 != ((v->side >> *((_BYTE *)v18 + 2)) & 1) )
          break;
        vb = (cm_vertex_t *)((char *)vb + 4);
        trmpolyb = (cm_trmPolygon_t *)((char *)trmpolyb + 1);
        if ( (int)trmpolyb >= trmpoly->numEdges )
          goto LABEL_15;
      }
    }
  }
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::TranslateTrmThroughPolygon(struct cm_traceWork_t *,struct cm_polygon_t *)
bool __thiscall idCollisionModelManagerLocal::TranslateTrmThroughPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_polygon_t *p)
{
  int checkCount; // eax
  cm_polygon_t *v4; // ebx
  int v6; // eax
  int v7; // eax
  float *v8; // esi
  unsigned int v9; // edi
  unsigned int v10; // edx
  cm_edge_t *edges; // ecx
  int v12; // eax
  cm_edge_t *v13; // edx
  cm_vertex_t *vertices; // ecx
  float *p_x; // eax
  double v16; // st7
  float *v17; // ecx
  cm_vertex_t *v18; // eax
  double v19; // st7
  double v20; // st6
  double v21; // st5
  double v22; // rt0
  double v23; // st5
  double v24; // st4
  idPluecker *v25; // edx
  int v26; // esi
  cm_traceWork_t *v27; // edi
  int v28; // edi
  cm_trmEdge_t *v29; // esi
  int v30; // esi
  unsigned int v31; // ecx
  cm_edge_t *v32; // edx
  int v33; // eax
  bool v34; // zf
  int v35; // eax
  unsigned int v36; // ecx
  cm_vertex_t *v37; // ebx
  int v38; // eax
  __m128 v39; // xmm2
  int v40; // edi
  bool v41; // cc
  double v42; // st7
  double v43; // st6
  cm_trmPolygon_t *polys; // esi
  double fraction; // st7
  float y; // edx
  float z; // eax
  double v48; // st7
  double v49; // st7
  double v50; // st7
  double v51; // st7
  int i; // [esp+8h] [ebp-3Ch]
  int ia; // [esp+8h] [ebp-3Ch]
  idPluecker *pl; // [esp+Ch] [ebp-38h]
  idPluecker *polygonVertexPlueckerCache; // [esp+10h] [ebp-34h]
  int k; // [esp+14h] [ebp-30h]
  unsigned int v58; // [esp+18h] [ebp-2Ch]
  cm_edge_t *e; // [esp+24h] [ebp-20h]
  float previousFraction; // [esp+28h] [ebp-1Ch]
  idVec3 endp; // [esp+2Ch] [ebp-18h] BYREF
  float v62; // [esp+3Ch] [ebp-8h]
  float v63; // [esp+40h] [ebp-4h]

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
    || tw->dir.z * p->plane.c + tw->dir.y * p->plane.b + tw->dir.x * p->plane.a > 0.0
    || fabs(idBounds::PlaneDistance(&p->bounds, &tw->heartPlane1)) > tw->maxDistFromHeartPlane1
    || fabs(idBounds::PlaneDistance(&p->bounds, &tw->heartPlane2)) > tw->maxDistFromHeartPlane2 )
  {
    return 0;
  }
  previousFraction = tw->trace.fraction;
  if ( !tw->pointTrace )
  {
    v6 = idBounds::PlaneSide(&tw->traceBounds, &p->plane, 0.1);
    if ( v6 )
    {
      if ( v6 == 3 )
      {
        v7 = 0;
        i = 0;
        if ( p->numEdges > 0 )
        {
          v8 = &tw->polygonEdgePlueckerCache[0].p[2];
          do
          {
            v9 = v4->edges[v7];
            v10 = abs32(v9);
            edges = tw->model->edges;
            v12 = edges[v10].checkcount;
            v13 = &edges[v10];
            if ( v12 != this->checkCount )
              v13->sideSet = 0;
            vertices = tw->model->vertices;
            p_x = &vertices[v13->vertexNum[1]].p.x;
            v16 = vertices[v13->vertexNum[1]].p.y * vertices[v13->vertexNum[0]].p.x;
            v17 = &vertices[v13->vertexNum[0]].p.x;
            *(v8 - 2) = v16 - v17[1] * *p_x;
            *(v8 - 1) = *v17 * p_x[2] - *p_x * v17[2];
            *v8 = *v17 - *p_x;
            v8[1] = v17[1] * p_x[2] - p_x[1] * v17[2];
            v8[2] = v17[2] - p_x[2];
            v8[3] = p_x[1] - v17[1];
            v18 = &tw->model->vertices[v13->vertexNum[v9 >> 31]];
            if ( v18->checkcount != this->checkCount )
              v18->sideSet = 0;
            v4 = p;
            v19 = -tw->dir.x;
            v8 += 6;
            v20 = -tw->dir.y;
            v21 = -tw->dir.z;
            v8[376] = v20 * v18->p.x - v19 * v18->p.y;
            v8[377] = v21 * v18->p.x - v19 * v18->p.z;
            v22 = v21;
            v8[378] = -v19;
            v23 = v21 * v18->p.y;
            v24 = v20 * v18->p.z;
            v7 = ++i;
            v8[379] = v23 - v24;
            v8[380] = -v22;
            v8[381] = v20;
          }
          while ( i < p->numEdges );
        }
        v25 = &tw->polygonVertexPlueckerCache[v4->numEdges];
        v25->p[0] = tw->polygonVertexPlueckerCache[0].p[0];
        v25->p[1] = tw->polygonVertexPlueckerCache[0].p[1];
        v25->p[2] = tw->polygonVertexPlueckerCache[0].p[2];
        v25->p[3] = tw->polygonVertexPlueckerCache[0].p[3];
        v25->p[4] = tw->polygonVertexPlueckerCache[0].p[4];
        v26 = 0;
        v25->p[5] = tw->polygonVertexPlueckerCache[0].p[5];
        if ( tw->numVerts > 0 )
        {
          v27 = tw;
          do
          {
            if ( v27->vertices[0].used )
              idCollisionModelManagerLocal::TranslateTrmVertexThroughPolygon(this, tw, v4, v27->vertices, v26);
            ++v26;
            v27 = (cm_traceWork_t *)((char *)v27 + 96);
          }
          while ( v26 < tw->numVerts );
        }
        v28 = 1;
        if ( tw->numEdges >= 1 )
        {
          v29 = &tw->edges[1];
          do
          {
            if ( v29->used )
              idCollisionModelManagerLocal::TranslateTrmEdgeThroughPolygon(this, tw, v4, v29);
            ++v28;
            ++v29;
          }
          while ( v28 <= tw->numEdges );
        }
        v30 = 0;
        ia = 0;
        if ( v4->numEdges > 0 )
        {
          polygonVertexPlueckerCache = tw->polygonVertexPlueckerCache;
          do
          {
            v31 = v4->edges[v30];
            v32 = &tw->model->edges[abs32(v31)];
            v33 = this->checkCount;
            e = v32;
            if ( v32->checkcount != v33 )
            {
              v34 = v32->internal == 0;
              v32->checkcount = v33;
              if ( v34 )
              {
                v35 = 0;
                v36 = v31 >> 31;
                k = 0;
                v58 = v36;
                pl = polygonVertexPlueckerCache;
                while ( 1 )
                {
                  v37 = &tw->model->vertices[v32->vertexNum[v35 ^ v36]];
                  v38 = this->checkCount;
                  if ( v37->checkcount != v38 )
                  {
                    v37->checkcount = v38;
                    v39 = _mm_loadh_ps((const double *)&v37->p.y);
                    if ( _mm_movemask_ps(
                           _mm_and_ps(
                             _mm_cmpnlt_ps(v39, _mm_loadh_ps((const double *)&tw->traceBounds.b[0].y)),
                             _mm_cmple_ps(v39, _mm_loadh_ps((const double *)&tw->traceBounds.b[1].y)))) == 0xF )
                    {
                      v40 = 0;
                      v41 = tw->numPolys <= 0;
                      v42 = v37->p.x - tw->dir.x;
                      v43 = v37->p.y - tw->dir.y;
                      v63 = v37->p.z - tw->dir.z;
                      endp.z = v63;
                      endp.x = v42;
                      endp.y = v43;
                      if ( !v41 )
                      {
                        polys = tw->polys;
                        do
                        {
                          if ( polys->used )
                          {
                            idCollisionModelManagerLocal::TranslateVertexThroughTrmPolygon(
                              this,
                              tw,
                              polys,
                              p,
                              v37,
                              &endp,
                              pl);
                            v32 = e;
                          }
                          ++v40;
                          ++polys;
                        }
                        while ( v40 < tw->numPolys );
                      }
                    }
                  }
                  ++pl;
                  v35 = ++k;
                  if ( k >= 2 )
                    break;
                  v36 = v58;
                }
                v4 = p;
                v30 = ia;
              }
            }
            ++polygonVertexPlueckerCache;
            ia = ++v30;
          }
          while ( v30 < v4->numEdges );
        }
        goto LABEL_46;
      }
    }
    else if ( tw->model->isConvex )
    {
      tw->quickExit = 1;
      return 1;
    }
    return 0;
  }
  idCollisionModelManagerLocal::TranslatePointThroughPolygon(this, tw, p, tw->vertices);
LABEL_46:
  if ( tw->trace.fraction < (double)previousFraction && !tw->getContacts )
  {
    fraction = tw->trace.fraction;
    y = tw->dir.y;
    z = tw->dir.z;
    endp.x = tw->dir.x;
    endp.y = y;
    endp.z = z;
    v62 = y * fraction;
    v63 = z * fraction;
    v48 = endp.x * fraction + tw->start.x;
    endp.y = v62 + tw->start.y;
    endp.z = v63 + tw->start.z;
    if ( v48 <= tw->start.x )
    {
      tw->traceBounds.b[0].x = v48 + tw->trmBounds.b[0].x - 1.0;
      v49 = tw->trmBounds.b[1].x + tw->start.x;
    }
    else
    {
      tw->traceBounds.b[0].x = tw->trmBounds.b[0].x + tw->start.x - 1.0;
      v49 = v48 + tw->trmBounds.b[1].x;
    }
    tw->traceBounds.b[1].x = v49 + 1.0;
    if ( tw->start.y >= (double)endp.y )
    {
      tw->traceBounds.b[0].y = endp.y + tw->trmBounds.b[0].y - 1.0;
      v50 = tw->trmBounds.b[1].y + tw->start.y;
    }
    else
    {
      tw->traceBounds.b[0].y = tw->trmBounds.b[0].y + tw->start.y - 1.0;
      v50 = endp.y + tw->trmBounds.b[1].y;
    }
    tw->traceBounds.b[1].y = v50 + 1.0;
    if ( tw->start.z >= (double)endp.z )
    {
      tw->traceBounds.b[0].z = endp.z + tw->trmBounds.b[0].z - 1.0;
      v51 = tw->trmBounds.b[1].z + tw->start.z;
    }
    else
    {
      tw->traceBounds.b[0].z = tw->trmBounds.b[0].z + tw->start.z - 1.0;
      v51 = endp.z + tw->trmBounds.b[1].z;
    }
    tw->traceBounds.b[1].z = v51 + 1.0;
  }
  return tw->trace.fraction == 0.0;
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::Translation(struct trace_t *,class idVec3 const &,class idVec3 const &,class idTraceModel const *,class idMat3 const &,int,class idCollisionModel *,class idVec3 const &,class idMat3 const &)
void __userpurge idCollisionModelManagerLocal::Translation(
        idCollisionModelManagerLocal *this@<ecx>,
        __m128 a2@<xmm1>,
        trace_t *results,
        const idVec3 *start,
        const idVec3 *end,
        const idTraceModel *trm,
        const idMat3 *trmAxis,
        int contentMask,
        idCollisionModelLocal *model,
        cm_trmVertex_t *modelOrigin,
        cm_trmVertex_t *modelAxis)
{
  double v12; // st7
  __m128 v13; // xmm0
  __m128 v14; // xmm1
  __m128 v15; // xmm2
  __m128 v16; // xmm3
  __m128 v17; // xmm4
  __m128 v18; // xmm0
  __m128 v19; // xmm2
  __m128 v20; // xmm2
  __m128 v21; // xmm0
  __m128 v22; // xmm1
  __m128 v23; // xmm5
  __m128 v24; // xmm5
  __m128 v25; // xmm2
  __m128 v26; // xmm4
  __m128 v27; // xmm7
  __m128 v28; // xmm0
  __m128 v29; // xmm3
  __m128 v30; // xmm4
  __m128 v31; // xmm0
  __m128 v32; // xmm0
  __m128 v33; // xmm5
  __m128 v34; // xmm5
  __m128 v35; // xmm0
  __m128 v36; // xmm5
  double v37; // st7
  double v38; // st6
  double v39; // st5
  double v40; // st7
  double v41; // st7
  double v42; // st6
  double v43; // st7
  double v44; // st6
  bool isConvex; // al
  double v46; // st7
  double v47; // st6
  double v48; // st7
  double v49; // st6
  double v50; // st7
  double v51; // st6
  double v52; // st7
  double v53; // st6
  double v54; // st7
  double v55; // st6
  double v56; // st7
  double v57; // st6
  int v58; // eax
  int *p_used; // ecx
  int v60; // eax
  cm_trmEdge_t *v61; // ecx
  float *p_y; // eax
  double v63; // st7
  BOOL v64; // eax
  int v65; // eax
  unsigned int *v66; // edi
  unsigned int v67; // ecx
  unsigned int v68; // eax
  __m128 v69; // xmm2
  __m128 v70; // xmm0
  __m128 v71; // xmm1
  __m128 v72; // xmm5
  __m128 v73; // xmm5
  __m128 v74; // xmm2
  __m128 v75; // xmm4
  __m128 v76; // xmm7
  __m128 v77; // xmm0
  __m128 v78; // xmm3
  __m128 v79; // xmm4
  __m128 v80; // xmm0
  __m128 v81; // xmm0
  __m128 v82; // xmm5
  __m128 v83; // xmm5
  __m128 v84; // xmm0
  __m128 v85; // xmm5
  cm_traceWork_t *v86; // eax
  float *v87; // edx
  double v88; // st7
  double v89; // st6
  double v90; // st5
  double v91; // st7
  float x; // xmm1_4
  float y; // xmm3_4
  float z; // xmm5_4
  bool v95; // cc
  int v96; // edi
  float *v97; // eax
  int *v98; // esi
  int v99; // ecx
  int v100; // edx
  float *p_x; // ecx
  float *v102; // edx
  int v103; // edi
  float *p_c; // esi
  float *v105; // ecx
  unsigned int v106; // edx
  double v107; // st7
  __m128 v108; // xmm0
  __m128 v109; // xmm1
  __m128 v110; // xmm2
  __m128 v111; // xmm3
  __m128 v112; // xmm4
  __m128 v113; // xmm0
  __m128 v114; // xmm2
  int numContacts; // eax
  int v116; // edx
  int v117; // ecx
  idVec3 *p_normal; // eax
  double v119; // st7
  double v120; // st6
  idVec3 *p_point; // eax
  double v122; // st7
  double v123; // st6
  int v124; // edi
  int v125; // ecx
  idVec3 *v126; // eax
  float *p_dist; // esi
  double v128; // st7
  double fraction; // st7
  double v130; // st6
  double v131; // st5
  double v132; // st7
  double v133; // st7
  double v134; // st6
  double v135; // st7
  double v136; // st6
  float v137; // [esp+10h] [ebp-A4h]
  float v138; // [esp+10h] [ebp-A4h]
  float v139; // [esp+10h] [ebp-A4h]
  float v140; // [esp+10h] [ebp-A4h]
  float v141; // [esp+10h] [ebp-A4h]
  int j; // [esp+14h] [ebp-A0h]
  unsigned int *v144; // [esp+1Ch] [ebp-98h]
  float trmTransform; // [esp+20h] [ebp-94h]
  float trmTransform_4; // [esp+24h] [ebp-90h]
  float trmTransform_8; // [esp+28h] [ebp-8Ch]
  float trmTransform_12; // [esp+2Ch] [ebp-88h]
  float trmTransform_16; // [esp+30h] [ebp-84h]
  float trmTransform_20; // [esp+34h] [ebp-80h]
  float trmTransform_24; // [esp+38h] [ebp-7Ch]
  float trmTransform_28; // [esp+3Ch] [ebp-78h]
  float trmTransform_32; // [esp+40h] [ebp-74h]
  float trmTransform_36; // [esp+44h] [ebp-70h]
  float trmTransform_40; // [esp+48h] [ebp-6Ch]
  float trmTransform_44; // [esp+4Ch] [ebp-68h]
  _BYTE v157[12]; // [esp+50h] [ebp-64h]
  _BYTE v158[12]; // [esp+5Ch] [ebp-58h]
  int i; // [esp+68h] [ebp-4Ch]
  int ia; // [esp+68h] [ebp-4Ch]
  float v161; // [esp+6Ch] [ebp-48h]
  float v162; // [esp+70h] [ebp-44h]
  float v163; // [esp+74h] [ebp-40h]
  float trmDira; // [esp+78h] [ebp-3Ch]
  float trmDirb; // [esp+78h] [ebp-3Ch]
  float trmDir; // [esp+78h] [ebp-3Ch]
  float trmDirc; // [esp+78h] [ebp-3Ch]
  float trmDird; // [esp+78h] [ebp-3Ch]
  float trmDir_4a; // [esp+7Ch] [ebp-38h]
  float trmDir_4b; // [esp+7Ch] [ebp-38h]
  float trmDir_4; // [esp+7Ch] [ebp-38h]
  float trmDir_4c; // [esp+7Ch] [ebp-38h]
  float trmDir_4d; // [esp+7Ch] [ebp-38h]
  float trmDir_8a; // [esp+80h] [ebp-34h]
  float trmDir_8; // [esp+80h] [ebp-34h]
  float trmDir_8b; // [esp+80h] [ebp-34h]
  float invModelAxis; // [esp+84h] [ebp-30h]
  float invModelAxis_4; // [esp+88h] [ebp-2Ch]
  float invModelAxis_8; // [esp+8Ch] [ebp-28h]
  float invModelAxis_12; // [esp+90h] [ebp-24h]
  float invModelAxis_16; // [esp+94h] [ebp-20h]
  float invModelAxis_20; // [esp+98h] [ebp-1Ch]
  float invModelAxis_24; // [esp+9Ch] [ebp-18h]
  float invModelAxis_28; // [esp+A0h] [ebp-14h]
  float invModelAxis_32; // [esp+A4h] [ebp-10h]
  _BYTE v186[12]; // [esp+A8h] [ebp-Ch]
  char model_rotated_3; // [esp+D3h] [ebp+1Fh]
  float *modela; // [esp+D4h] [ebp+20h]
  int *vert; // [esp+DCh] [ebp+28h]
  cm_traceWork_t *verta; // [esp+DCh] [ebp+28h]

  if ( (_S5_41 & 1) == 0 )
    _S5_41 |= 1u;
  if ( model )
  {
    if ( start->x == end->x && start->y == end->y && start->z == end->z )
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
        (const idMat3 *)modelAxis);
    }
    else
    {
      ++this->checkCount;
      tw_1.contents = contentMask;
      tw_1.trace.fraction = 1.0;
      tw_1.trace.c.contents = 0;
      tw_1.trace.c.type = CONTACT_NONE;
      tw_1.trace.c.material = 0;
      tw_1.trace.c.materialType = 0;
      tw_1.isConvex = 1;
      tw_1.rotation = 0;
      tw_1.positionTest = 0;
      tw_1.quickExit = 0;
      tw_1.getContacts = this->getContacts;
      tw_1.contacts = this->contacts;
      tw_1.maxContacts = this->maxContacts;
      tw_1.model = model;
      tw_1.numContacts = 0;
      *(float *)v158 = start->x - modelOrigin->p.x;
      *(float *)&v158[4] = start->y - modelOrigin->p.y;
      *(float *)&v158[8] = start->z - modelOrigin->p.z;
      tw_1.start = *(idVec3 *)v158;
      *(float *)v157 = end->x - modelOrigin->p.x;
      *(float *)&v157[4] = end->y - modelOrigin->p.y;
      *(float *)&v157[8] = end->z - modelOrigin->p.z;
      tw_1.end = *(idVec3 *)v157;
      *(float *)v186 = end->x - start->x;
      *(float *)&v186[4] = end->y - start->y;
      v12 = end->z - start->z;
      *(float *)&v186[8] = v12;
      tw_1.dir = *(idVec3 *)v186;
      if ( LODWORD(modelAxis->p.x) == 1065353216
        && LODWORD(modelAxis->endp.x) == 1065353216
        && LODWORD(modelAxis->pl.p[0]) == 1065353216 )
      {
        model_rotated_3 = 0;
      }
      else
      {
        invModelAxis = modelAxis->p.x;
        model_rotated_3 = 1;
        invModelAxis_8 = modelAxis->endp.z;
        invModelAxis_4 = *(float *)&modelAxis->used;
        invModelAxis_12 = modelAxis->p.y;
        invModelAxis_16 = modelAxis->endp.x;
        invModelAxis_20 = *(float *)&modelAxis->pad0;
        invModelAxis_24 = modelAxis->p.z;
        invModelAxis_28 = modelAxis->endp.y;
        invModelAxis_32 = modelAxis->pl.p[0];
      }
      if ( trm )
      {
        tw_1.pointTrace = 0;
        isConvex = trm->isConvex;
        tw_1.trmBounds.b[1].z = -1.0e30;
        tw_1.isConvex = isConvex;
        tw_1.trmBounds.b[1].y = tw_1.trmBounds.b[1].z;
        tw_1.trmBounds.b[0].z = idMath::INFINITY;
        tw_1.trmBounds.b[1].x = tw_1.trmBounds.b[1].z;
        tw_1.trmBounds.b[0].x = idMath::INFINITY;
        tw_1.trmBounds.b[0].y = idMath::INFINITY;
        trmTransform = trmAxis->mat[0].x;
        v161 = start->x - modelOrigin->p.x;
        trmTransform_4 = trmAxis->mat[1].x;
        trmTransform_8 = trmAxis->mat[2].x;
        trmTransform_16 = trmAxis->mat[0].y;
        v162 = start->y - modelOrigin->p.y;
        trmTransform_20 = trmAxis->mat[1].y;
        trmTransform_24 = trmAxis->mat[2].y;
        v163 = start->z - modelOrigin->p.z;
        trmTransform_32 = trmAxis->mat[0].z;
        trmTransform_36 = trmAxis->mat[1].z;
        trmTransform_40 = trmAxis->mat[2].z;
        trmTransform_28 = v162;
        trmDir = *(float *)v186;
        trmTransform_12 = v161;
        trmDir_8 = v12;
        trmTransform_44 = v163;
        trmDir_4 = *(float *)&v186[4];
        if ( LODWORD(trmAxis->mat[0].x) == 1065353216
          && LODWORD(trmAxis->mat[1].y) == 1065353216
          && LODWORD(trmAxis->mat[2].z) == 1065353216 )
        {
          tw_1.start.x = *(float *)v158 + trm->offset.x;
          tw_1.start.y = *(float *)&v158[4] + trm->offset.y;
          tw_1.start.z = *(float *)&v158[8] + trm->offset.z;
          tw_1.end.x = *(float *)v157 + trm->offset.x;
          tw_1.end.y = *(float *)&v157[4] + trm->offset.y;
          tw_1.end.z = *(float *)&v157[8] + trm->offset.z;
        }
        else
        {
          v46 = trm->offset.y * trmAxis->mat[1].x
              + trmAxis->mat[0].x * trm->offset.x
              + trm->offset.z * trmAxis->mat[2].x;
          v47 = trmAxis->mat[1].y * trm->offset.y
              + trm->offset.z * trmAxis->mat[2].y
              + trm->offset.x * trmAxis->mat[0].y;
          v139 = trmAxis->mat[0].z * trm->offset.x
               + trmAxis->mat[2].z * trm->offset.z
               + trm->offset.y * trmAxis->mat[1].z;
          tw_1.start.x = v46 + *(float *)v158;
          tw_1.start.y = *(float *)&v158[4] + v47;
          tw_1.start.z = v139 + *(float *)&v158[8];
          tw_1.end.x = v46 + *(float *)v157;
          tw_1.end.y = v47 + *(float *)&v157[4];
          tw_1.end.z = v139 + *(float *)&v157[8];
          trmDir_8 = trmAxis->mat[2].x * *(float *)v186
                   + trmAxis->mat[2].y * *(float *)&v186[4]
                   + trmAxis->mat[2].z * *(float *)&v186[8];
          trmDir = trmAxis->mat[0].x * *(float *)v186
                 + trmAxis->mat[0].y * *(float *)&v186[4]
                 + trmAxis->mat[0].z * *(float *)&v186[8];
          trmDir_4 = trmAxis->mat[1].x * *(float *)v186
                   + trmAxis->mat[1].y * *(float *)&v186[4]
                   + trmAxis->mat[1].z * *(float *)&v186[8];
        }
        if ( model_rotated_3 )
        {
          v48 = invModelAxis_24 * tw_1.start.z + invModelAxis_12 * tw_1.start.y + invModelAxis * tw_1.start.x;
          v49 = invModelAxis_28 * tw_1.start.z + invModelAxis_16 * tw_1.start.y + invModelAxis_4 * tw_1.start.x;
          tw_1.start.z = invModelAxis_32 * tw_1.start.z + invModelAxis_20 * tw_1.start.y + invModelAxis_8 * tw_1.start.x;
          tw_1.start.x = v48;
          tw_1.start.y = v49;
          v50 = invModelAxis_24 * tw_1.end.z + invModelAxis_12 * tw_1.end.y + invModelAxis * tw_1.end.x;
          v51 = invModelAxis_28 * tw_1.end.z + invModelAxis_16 * tw_1.end.y + invModelAxis_4 * tw_1.end.x;
          tw_1.end.z = invModelAxis_32 * tw_1.end.z + invModelAxis_20 * tw_1.end.y + invModelAxis_8 * tw_1.end.x;
          tw_1.end.x = v50;
          tw_1.end.y = v51;
          tw_1.dir.z = invModelAxis_8 * *(float *)v186
                     + invModelAxis_32 * *(float *)&v186[8]
                     + invModelAxis_20 * *(float *)&v186[4];
          tw_1.dir.x = invModelAxis * *(float *)v186
                     + invModelAxis_24 * *(float *)&v186[8]
                     + invModelAxis_12 * *(float *)&v186[4];
          tw_1.dir.y = invModelAxis_4 * *(float *)v186
                     + invModelAxis_28 * *(float *)&v186[8]
                     + invModelAxis_16 * *(float *)&v186[4];
          v52 = trmTransform * invModelAxis + trmTransform_32 * invModelAxis_24 + trmTransform_16 * invModelAxis_12;
          v53 = trmTransform * invModelAxis_4 + trmTransform_32 * invModelAxis_28 + trmTransform_16 * invModelAxis_16;
          trmTransform_32 = trmTransform * invModelAxis_8
                          + trmTransform_32 * invModelAxis_32
                          + trmTransform_16 * invModelAxis_20;
          trmTransform_16 = v53;
          trmTransform = v52;
          v54 = trmTransform_36 * invModelAxis_24 + trmTransform_20 * invModelAxis_12 + trmTransform_4 * invModelAxis;
          v55 = trmTransform_36 * invModelAxis_28 + trmTransform_20 * invModelAxis_16 + trmTransform_4 * invModelAxis_4;
          trmTransform_36 = trmTransform_36 * invModelAxis_32
                          + trmTransform_20 * invModelAxis_20
                          + trmTransform_4 * invModelAxis_8;
          trmTransform_20 = v55;
          trmTransform_4 = v54;
          v56 = trmTransform_40 * invModelAxis_24 + trmTransform_24 * invModelAxis_12 + trmTransform_8 * invModelAxis;
          v57 = trmTransform_40 * invModelAxis_28 + trmTransform_24 * invModelAxis_16 + trmTransform_8 * invModelAxis_4;
          trmTransform_40 = trmTransform_40 * invModelAxis_32
                          + trmTransform_24 * invModelAxis_20
                          + trmTransform_8 * invModelAxis_8;
          trmTransform_24 = v57;
          trmTransform_8 = v56;
          trmTransform_44 = v161 * invModelAxis_8 + v163 * invModelAxis_32 + v162 * invModelAxis_20;
          trmTransform_28 = v161 * invModelAxis_4 + v163 * invModelAxis_28 + v162 * invModelAxis_16;
          trmTransform_12 = v161 * invModelAxis + v163 * invModelAxis_24 + v162 * invModelAxis_12;
        }
        tw_1.numVerts = trm->numVerts;
        v58 = 0;
        if ( trm->numVerts > 0 )
        {
          p_used = &tw_1.vertices[0].used;
          do
          {
            *p_used = 0;
            ++v58;
            p_used += 24;
          }
          while ( v58 < trm->numVerts );
        }
        v60 = 1;
        tw_1.numEdges = trm->numEdges;
        if ( trm->numEdges >= 1 )
        {
          v61 = &tw_1.edges[1];
          do
          {
            v61->used = 0;
            ++v60;
            ++v61;
          }
          while ( v60 <= trm->numEdges );
        }
        tw_1.numPolys = trm->numPolys;
        i = 0;
        if ( tw_1.numPolys > 0 )
        {
          p_y = &trm->polys[0].normal.y;
          vert = &tw_1.polys[0].numEdges;
          for ( modela = &trm->polys[0].normal.y; ; p_y = modela )
          {
            v63 = trmDir * *(p_y - 1) + trmDir_8 * p_y[1] + trmDir_4 * *p_y;
            v64 = v63 > 0.0 || v63 == 0.0 && !trm->isConvex;
            *(vert - 1) = v64;
            if ( v64 )
            {
              v65 = *((_DWORD *)modela + 9);
              *vert = v65;
              j = 0;
              if ( v65 > 0 )
              {
                v144 = (unsigned int *)(vert + 1);
                v66 = (unsigned int *)(modela + 10);
                do
                {
                  v67 = *v66;
                  *v144++ = *v66;
                  v68 = abs32(v67);
                  tw_1.edges[v68].used = 1;
                  tw_1.vertices[trm->edges[v68].v[v67 >> 31]].used = 1;
                  ++v66;
                  ++j;
                }
                while ( j < *vert );
              }
            }
            modela += 27;
            vert += 28;
            if ( ++i >= tw_1.numPolys )
              break;
          }
        }
        v69 = _mm_loadh_ps((const double *)&tw_1.dir.y);
        v70 = _mm_mul_ps(v69, v69);
        v71 = _mm_movehl_ps(a2, v70);
        v70.m128_f32[0] = v70.m128_f32[0] + v71.m128_f32[0];
        v72 = _mm_shuffle_ps(v70, v70, 87);
        v72.m128_f32[0] = v72.m128_f32[0] + v70.m128_f32[0];
        v71.m128_f32[0] = fsqrt(v72.m128_f32[0]);
        v72.m128_f32[0] = (float)((float)((float)(v72.m128_f32[0] * (float)(1.0 / v71.m128_f32[0]))
                                        * (float)(1.0 / v71.m128_f32[0]))
                                - SIMD_SP_rsqrt_c0_1[0])
                        * (float)((float)(1.0 / v71.m128_f32[0]) * SIMD_SP_rsqrt_c1_1[0]);
        v73 = _mm_shuffle_ps(v72, v72, 0);
        v74 = _mm_mul_ps(v69, v73);
        v70.m128_f32[0] = (float)(v70.m128_f32[0] * v73.m128_f32[0]) * v73.m128_f32[0];
        v75 = _mm_cmpneq_ps(_mm_shuffle_ps(v70, v70, 0), *(__m128 *)SIMD_SP_zero_1);
        v76 = _mm_xor_ps(_mm_loadh_ps((const double *)&tw_1.start.y), *(__m128 *)SIMD_SP_signBit_1);
        v77 = _mm_and_ps(v70, v75);
        v78 = _mm_and_ps(_mm_xor_ps(_mm_shuffle_ps(v74, v74, 70), *(__m128 *)SIMD_SP_firstSignBit_1), v75);
        v79 = _mm_andnot_ps(v75, *(__m128 *)SIMD_SP_firstOnePlusTwoUlps_1);
        v80 = _mm_or_ps(v77, v79);
        v71.m128_f32[0] = 1.0 / fsqrt(v80.m128_f32[0]);
        v80.m128_f32[0] = (float)((float)(v80.m128_f32[0] * v71.m128_f32[0]) * v71.m128_f32[0]) - SIMD_SP_rsqrt_c0_1[0];
        v71.m128_f32[0] = v71.m128_f32[0] * SIMD_SP_rsqrt_c1_1[0];
        v80.m128_f32[0] = v80.m128_f32[0] * v71.m128_f32[0];
        v81 = _mm_mul_ps(_mm_shuffle_ps(v80, v80, 68), _mm_or_ps(v78, v79));
        tw_1.heartPlane1.a = v81.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.heartPlane1.b, v81);
        v82 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(v74, v74, 54), v81), _mm_mul_ps(_mm_shuffle_ps(v81, v81, 54), v74));
        v83 = _mm_shuffle_ps(v82, v82, 54);
        tw_1.heartPlane2.a = v83.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.heartPlane2.b, v83);
        v84 = _mm_mul_ps(v81, v76);
        v85 = _mm_mul_ps(v83, v76);
        v84.m128_f32[0] = v84.m128_f32[0] + _mm_movehl_ps(v71, v84).m128_f32[0];
        v85.m128_f32[0] = v85.m128_f32[0] + _mm_movehl_ps(v79, v85).m128_f32[0];
        tw_1.heartPlane1.d = v84.m128_f32[0] + _mm_shuffle_ps(v84, v84, 87).m128_f32[0];
        tw_1.heartPlane2.d = v85.m128_f32[0] + _mm_shuffle_ps(v85, v85, 87).m128_f32[0];
        v86 = &tw_1;
        tw_1.maxDistFromHeartPlane1 = 0.0;
        tw_1.maxDistFromHeartPlane2 = 0.0;
        verta = &tw_1;
        ia = 0;
        if ( tw_1.numVerts > 0 )
        {
          v87 = &trm->verts[0].y;
          do
          {
            if ( v86->vertices[0].used )
            {
              v86->vertices[0].p.x = trmTransform_4 * *v87
                                   + trmTransform * *(v87 - 1)
                                   + trmTransform_8 * v87[1]
                                   + trmTransform_12;
              v86->vertices[0].p.y = trmTransform_20 * *v87
                                   + trmTransform_24 * v87[1]
                                   + trmTransform_16 * *(v87 - 1)
                                   + trmTransform_28;
              v88 = trmTransform_36 * *v87 + trmTransform_40 * v87[1] + trmTransform_32 * *(v87 - 1) + trmTransform_44;
              v86->vertices[0].p.z = v88;
              v89 = tw_1.dir.x + v86->vertices[0].p.x;
              v90 = v88;
              v91 = tw_1.dir.y + v86->vertices[0].p.y;
              v140 = v90 + tw_1.dir.z;
              v86->vertices[0].endp.z = v140;
              v86->vertices[0].endp.x = v89;
              v86->vertices[0].endp.y = v91;
              v86->vertices[0].pl.p[0] = tw_1.dir.y * v86->vertices[0].p.x - tw_1.dir.x * v86->vertices[0].p.y;
              v86->vertices[0].pl.p[1] = tw_1.dir.z * v86->vertices[0].p.x - tw_1.dir.x * v86->vertices[0].p.z;
              v86->vertices[0].pl.p[2] = -tw_1.dir.x;
              v86->vertices[0].pl.p[3] = tw_1.dir.z * v86->vertices[0].p.y - tw_1.dir.y * v86->vertices[0].p.z;
              v86->vertices[0].pl.p[4] = -tw_1.dir.z;
              v86->vertices[0].pl.p[5] = tw_1.dir.y;
              tw_1.maxDistFromHeartPlane1 = fmaxf(
                                              COERCE_FLOAT(COERCE_UNSIGNED_INT(
                                                             (float)((float)(tw_1.heartPlane1.a * verta->vertices[0].p.x)
                                                                   + tw_1.heartPlane1.d)
                                                           + (float)((float)(tw_1.heartPlane1.b * verta->vertices[0].p.y)
                                                                   + (float)(tw_1.heartPlane1.c * verta->vertices[0].p.z))) & SIMD_SP_absMask_1[0]),
                                              tw_1.maxDistFromHeartPlane1);
              tw_1.maxDistFromHeartPlane2 = fmaxf(
                                              COERCE_FLOAT(COERCE_UNSIGNED_INT(
                                                             (float)((float)(tw_1.heartPlane2.a * verta->vertices[0].p.x)
                                                                   + tw_1.heartPlane2.d)
                                                           + (float)((float)(tw_1.heartPlane2.b * verta->vertices[0].p.y)
                                                                   + (float)(tw_1.heartPlane2.c * verta->vertices[0].p.z))) & SIMD_SP_absMask_1[0]),
                                              tw_1.maxDistFromHeartPlane2);
              x = verta->vertices[0].p.x;
              tw_1.trmBounds.b[0].x = fminf(tw_1.trmBounds.b[0].x, verta->vertices[0].p.x);
              y = verta->vertices[0].p.y;
              tw_1.trmBounds.b[0].y = fminf(tw_1.trmBounds.b[0].y, y);
              z = verta->vertices[0].p.z;
              tw_1.trmBounds.b[0].z = fminf(tw_1.trmBounds.b[0].z, z);
              tw_1.trmBounds.b[1].x = fmaxf(x, tw_1.trmBounds.b[1].x);
              tw_1.trmBounds.b[1].y = fmaxf(y, tw_1.trmBounds.b[1].y);
              tw_1.trmBounds.b[1].z = fmaxf(z, tw_1.trmBounds.b[1].z);
            }
            v86 = (cm_traceWork_t *)((char *)v86 + 96);
            v87 += 3;
            v95 = ++ia < tw_1.numVerts;
            verta = v86;
          }
          while ( v95 );
        }
        v96 = 1;
        tw_1.maxDistFromHeartPlane1 = tw_1.maxDistFromHeartPlane1 + 1.0;
        tw_1.maxDistFromHeartPlane2 = tw_1.maxDistFromHeartPlane2 + 1.0;
        tw_1.trmBounds.b[0].x = tw_1.trmBounds.b[0].x - tw_1.start.x;
        tw_1.trmBounds.b[0].y = tw_1.trmBounds.b[0].y - tw_1.start.y;
        tw_1.trmBounds.b[0].z = tw_1.trmBounds.b[0].z - tw_1.start.z;
        tw_1.trmBounds.b[1].x = tw_1.trmBounds.b[1].x - tw_1.start.x;
        tw_1.trmBounds.b[1].y = tw_1.trmBounds.b[1].y - tw_1.start.y;
        tw_1.trmBounds.b[1].z = tw_1.trmBounds.b[1].z - tw_1.start.z;
        if ( tw_1.numEdges >= 1 )
        {
          v97 = &tw_1.edges[1].pl.p[2];
          v98 = &trm->edges[1].v[1];
          do
          {
            if ( *((_WORD *)v97 - 16) )
            {
              v99 = *v98;
              v100 = *(v98 - 1);
              *((_DWORD *)v97 - 3) = *v98;
              *((_DWORD *)v97 - 4) = v100;
              p_x = &tw_1.vertices[v99].p.x;
              v102 = &tw_1.vertices[v100].p.x;
              *(v97 - 2) = *v102 * p_x[1] - *p_x * v102[1];
              *(v97 - 1) = *v102 * p_x[2] - *p_x * v102[2];
              *v97 = *v102 - *p_x;
              v97[1] = p_x[2] * v102[1] - v102[2] * p_x[1];
              v97[2] = v102[2] - p_x[2];
              v97[3] = p_x[1] - v102[1];
              *(v97 - 7) = -(tw_1.dir.y * *v97) - tw_1.dir.x * v97[3];
              *(v97 - 6) = tw_1.dir.x * v97[2] - tw_1.dir.z * *v97;
              *(v97 - 5) = tw_1.dir.y * v97[2] + tw_1.dir.z * v97[3];
              *((_WORD *)v97 - 15) = v96;
            }
            ++v96;
            v98 += 5;
            v97 += 24;
          }
          while ( v96 <= tw_1.numEdges );
        }
        v103 = 0;
        if ( tw_1.numPolys > 0 )
        {
          p_c = &tw_1.polys[0].plane.c;
          v105 = &trm->polys[0].normal.y;
          do
          {
            if ( *((_DWORD *)p_c + 2) )
            {
              v106 = abs32(*((_DWORD *)p_c + 4));
              *(p_c - 2) = trmTransform_4 * *v105 + trmTransform * *(v105 - 1) + trmTransform_8 * v105[1];
              *(p_c - 1) = trmTransform_20 * *v105 + trmTransform_24 * v105[1] + trmTransform_16 * *(v105 - 1);
              v107 = trmTransform_36 * *v105 + trmTransform_40 * v105[1] + trmTransform_32 * *(v105 - 1);
              *p_c = v107;
              p_c[1] = -(v107 * tw_1.vertices[tw_1.edges[v106].vertexNum[0]].p.z
                       + tw_1.vertices[tw_1.edges[v106].vertexNum[0]].p.y * *(p_c - 1)
                       + tw_1.vertices[tw_1.edges[v106].vertexNum[0]].p.x * *(p_c - 2));
            }
            ++v103;
            v105 += 27;
            p_c += 28;
          }
          while ( v103 < tw_1.numPolys );
        }
        v108 = _mm_loadh_ps((const double *)&tw_1.start.y);
        v109 = _mm_loadh_ps((const double *)&tw_1.end.y);
        v110 = _mm_loadh_ps((const double *)&tw_1.trmBounds.b[0].y);
        v111 = _mm_loadh_ps((const double *)&tw_1.trmBounds.b[1].y);
        v112 = _mm_sub_ps(_mm_add_ps(_mm_min_ps(v108, v109), v110), *(__m128 *)SIMD_SP_boxEpsilon_1);
        v113 = _mm_add_ps(_mm_add_ps(_mm_max_ps(v108, v109), v111), *(__m128 *)SIMD_SP_boxEpsilon_1);
        tw_1.traceBounds.b[0].x = v112.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.traceBounds.b[0].y, v112);
        tw_1.traceBounds.b[1].x = v113.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.traceBounds.b[1].y, v113);
        v114 = _mm_add_ps(
                 _mm_max_ps(
                   _mm_and_ps(v110, *(__m128 *)SIMD_SP_absMask_1),
                   _mm_and_ps(v111, *(__m128 *)SIMD_SP_absMask_1)),
                 *(__m128 *)SIMD_SP_boxEpsilon_1);
        tw_1.trmExtents.x = v114.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.trmExtents.y, v114);
        idCollisionModelManagerLocal::TraceThroughModel(this, &tw_1);
        if ( tw_1.getContacts )
        {
          numContacts = tw_1.numContacts;
          if ( model_rotated_3 )
          {
            v116 = 0;
            if ( tw_1.numContacts > 0 )
            {
              v117 = 0;
              do
              {
                p_normal = &tw_1.contacts[v117].normal;
                ++v116;
                v119 = *(float *)&modelAxis->used * tw_1.contacts[v117].normal.y
                     + p_normal->x * modelAxis->p.x
                     + tw_1.contacts[v117].normal.z * modelAxis->endp.z;
                v120 = *(float *)&modelAxis->pad0 * tw_1.contacts[v117].normal.z
                     + p_normal->x * modelAxis->p.y
                     + modelAxis->endp.x * tw_1.contacts[v117].normal.y;
                p_normal->z = modelAxis->pl.p[0] * tw_1.contacts[v117].normal.z
                            + p_normal->x * modelAxis->p.z
                            + tw_1.contacts[v117].normal.y * modelAxis->endp.y;
                p_normal->x = v119;
                p_normal->y = v120;
                p_point = &tw_1.contacts[v117++].point;
                v122 = p_point->x * modelAxis->p.x
                     + *(float *)&modelAxis->used * p_point->y
                     + p_point->z * modelAxis->endp.z;
                v123 = p_point->x * modelAxis->p.y
                     + *(float *)&modelAxis->pad0 * p_point->z
                     + modelAxis->endp.x * p_point->y;
                p_point->z = modelAxis->pl.p[0] * p_point->z
                           + modelAxis->p.z * p_point->x
                           + p_point->y * modelAxis->endp.y;
                p_point->x = v122;
                p_point->y = v123;
                numContacts = tw_1.numContacts;
              }
              while ( v116 < tw_1.numContacts );
            }
          }
          if ( ((LODWORD(modelOrigin->p.x) | LODWORD(modelOrigin->p.y) | LODWORD(modelOrigin->p.z)) & 0x7FFFFFFF) != 0 )
          {
            v124 = 0;
            if ( numContacts > 0 )
            {
              v125 = 0;
              do
              {
                v126 = &tw_1.contacts[v125].point;
                ++v124;
                v126->x = modelOrigin->p.x + v126->x;
                v126->y = modelOrigin->p.y + v126->y;
                v126->z = modelOrigin->p.z + v126->z;
                p_dist = &tw_1.contacts[v125].dist;
                v128 = tw_1.contacts[v125++].normal.z * modelOrigin->p.z;
                *p_dist = v128
                        + tw_1.contacts[v125 - 1].normal.y * modelOrigin->p.y
                        + tw_1.contacts[v125 - 1].normal.x * modelOrigin->p.x
                        + *p_dist;
                numContacts = tw_1.numContacts;
              }
              while ( v124 < tw_1.numContacts );
            }
          }
          this->numContacts = numContacts;
        }
        else
        {
          *results = tw_1.trace;
          trmDirc = end->x - start->x;
          trmDir_4c = end->y - start->y;
          trmDir_8b = end->z - start->z;
          fraction = results->fraction;
          trmDird = trmDirc * fraction;
          trmDir_4d = trmDir_4c * fraction;
          v130 = trmDird + start->x;
          v131 = fraction * trmDir_8b;
          v132 = trmDir_4d + start->y;
          v141 = v131 + start->z;
          results->endpos.z = v141;
          results->endpos.x = v130;
          results->endpos.y = v132;
          results->endAxis = *trmAxis;
          if ( results->fraction < 1.0 )
          {
            if ( results->fraction > 0.0
              && results->endpos.x == start->x
              && results->endpos.y == start->y
              && results->endpos.z == start->z )
            {
              results->fraction = 0.0;
            }
            if ( model_rotated_3 )
            {
              v133 = *(float *)&modelAxis->used * results->c.normal.y
                   + results->c.normal.x * modelAxis->p.x
                   + results->c.normal.z * modelAxis->endp.z;
              v134 = *(float *)&modelAxis->pad0 * results->c.normal.z
                   + results->c.normal.x * modelAxis->p.y
                   + modelAxis->endp.x * results->c.normal.y;
              results->c.normal.z = modelAxis->pl.p[0] * results->c.normal.z
                                  + results->c.normal.x * modelAxis->p.z
                                  + results->c.normal.y * modelAxis->endp.y;
              results->c.normal.x = v133;
              results->c.normal.y = v134;
              v135 = results->c.point.x * modelAxis->p.x
                   + results->c.point.z * modelAxis->endp.z
                   + results->c.point.y * *(float *)&modelAxis->used;
              v136 = results->c.point.x * modelAxis->p.y
                   + results->c.point.z * *(float *)&modelAxis->pad0
                   + results->c.point.y * modelAxis->endp.x;
              results->c.point.z = results->c.point.z * modelAxis->pl.p[0]
                                 + results->c.point.y * modelAxis->endp.y
                                 + modelAxis->p.z * results->c.point.x;
              results->c.point.x = v135;
              results->c.point.y = v136;
            }
            if ( ((LODWORD(modelOrigin->p.x) | LODWORD(modelOrigin->p.y) | LODWORD(modelOrigin->p.z)) & 0x7FFFFFFF) != 0 )
            {
              results->c.point.x = results->c.point.x + modelOrigin->p.x;
              results->c.point.y = modelOrigin->p.y + results->c.point.y;
              results->c.point.z = modelOrigin->p.z + results->c.point.z;
              results->c.dist = results->c.normal.z * modelOrigin->p.z
                              + results->c.normal.y * modelOrigin->p.y
                              + results->c.normal.x * modelOrigin->p.x
                              + results->c.dist;
            }
          }
        }
      }
      else
      {
        if ( model_rotated_3 )
        {
          tw_1.start.z = invModelAxis_8 * *(float *)v158
                       + invModelAxis_32 * *(float *)&v158[8]
                       + invModelAxis_20 * *(float *)&v158[4];
          tw_1.start.x = invModelAxis * *(float *)v158
                       + invModelAxis_24 * *(float *)&v158[8]
                       + invModelAxis_12 * *(float *)&v158[4];
          tw_1.start.y = invModelAxis_4 * *(float *)v158
                       + invModelAxis_28 * *(float *)&v158[8]
                       + invModelAxis_16 * *(float *)&v158[4];
          tw_1.end.z = invModelAxis_8 * *(float *)v157
                     + invModelAxis_32 * *(float *)&v157[8]
                     + invModelAxis_20 * *(float *)&v157[4];
          tw_1.end.x = invModelAxis * *(float *)v157
                     + invModelAxis_24 * *(float *)&v157[8]
                     + invModelAxis_12 * *(float *)&v157[4];
          tw_1.end.y = invModelAxis_4 * *(float *)v157
                     + invModelAxis_28 * *(float *)&v157[8]
                     + invModelAxis_16 * *(float *)&v157[4];
          tw_1.dir.z = invModelAxis_8 * *(float *)v186
                     + invModelAxis_32 * *(float *)&v186[8]
                     + invModelAxis_20 * *(float *)&v186[4];
          tw_1.dir.x = invModelAxis * *(float *)v186
                     + invModelAxis_24 * *(float *)&v186[8]
                     + invModelAxis_12 * *(float *)&v186[4];
          tw_1.dir.y = invModelAxis_4 * *(float *)v186
                     + invModelAxis_28 * *(float *)&v186[8]
                     + invModelAxis_16 * *(float *)&v186[4];
        }
        tw_1.trmBounds.b[1].z = 0.0;
        tw_1.trmBounds.b[1].y = 0.0;
        tw_1.trmBounds.b[1].x = 0.0;
        tw_1.trmBounds.b[0].z = 0.0;
        tw_1.trmBounds.b[0].y = 0.0;
        tw_1.trmBounds.b[0].x = 0.0;
        v13 = _mm_loadh_ps((const double *)&tw_1.start.y);
        v14 = _mm_loadh_ps((const double *)&tw_1.end.y);
        v15 = _mm_loadh_ps((const double *)&tw_1.trmBounds.b[0].y);
        v16 = _mm_loadh_ps((const double *)&tw_1.trmBounds.b[1].y);
        v17 = _mm_sub_ps(_mm_add_ps(_mm_min_ps(v13, v14), v15), *(__m128 *)SIMD_SP_boxEpsilon_1);
        v18 = _mm_add_ps(_mm_add_ps(_mm_max_ps(v13, v14), v16), *(__m128 *)SIMD_SP_boxEpsilon_1);
        tw_1.traceBounds.b[0].x = v17.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.traceBounds.b[0].y, v17);
        tw_1.traceBounds.b[1].x = v18.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.traceBounds.b[1].y, v18);
        v19 = _mm_add_ps(
                _mm_max_ps(_mm_and_ps(v15, *(__m128 *)SIMD_SP_absMask_1), _mm_and_ps(v16, *(__m128 *)SIMD_SP_absMask_1)),
                *(__m128 *)SIMD_SP_boxEpsilon_1);
        tw_1.trmExtents.x = v19.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.trmExtents.y, v19);
        v20 = _mm_loadh_ps((const double *)&tw_1.dir.y);
        v21 = _mm_mul_ps(v20, v20);
        v22 = _mm_movehl_ps(v14, v21);
        v21.m128_f32[0] = v21.m128_f32[0] + v22.m128_f32[0];
        v23 = _mm_shuffle_ps(v21, v21, 87);
        v23.m128_f32[0] = v23.m128_f32[0] + v21.m128_f32[0];
        v22.m128_f32[0] = fsqrt(v23.m128_f32[0]);
        v23.m128_f32[0] = (float)((float)((float)(v23.m128_f32[0] * (float)(1.0 / v22.m128_f32[0]))
                                        * (float)(1.0 / v22.m128_f32[0]))
                                - SIMD_SP_rsqrt_c0_1[0])
                        * (float)((float)(1.0 / v22.m128_f32[0]) * SIMD_SP_rsqrt_c1_1[0]);
        v24 = _mm_shuffle_ps(v23, v23, 0);
        v25 = _mm_mul_ps(v20, v24);
        v21.m128_f32[0] = (float)(v21.m128_f32[0] * v24.m128_f32[0]) * v24.m128_f32[0];
        v26 = _mm_cmpneq_ps(_mm_shuffle_ps(v21, v21, 0), *(__m128 *)SIMD_SP_zero_1);
        v27 = _mm_xor_ps(_mm_loadh_ps((const double *)&tw_1.start.y), *(__m128 *)SIMD_SP_signBit_1);
        v28 = _mm_and_ps(v21, v26);
        v29 = _mm_and_ps(_mm_xor_ps(_mm_shuffle_ps(v25, v25, 70), *(__m128 *)SIMD_SP_firstSignBit_1), v26);
        v30 = _mm_andnot_ps(v26, *(__m128 *)SIMD_SP_firstOnePlusTwoUlps_1);
        v31 = _mm_or_ps(v28, v30);
        v22.m128_f32[0] = 1.0 / fsqrt(v31.m128_f32[0]);
        v31.m128_f32[0] = (float)((float)(v31.m128_f32[0] * v22.m128_f32[0]) * v22.m128_f32[0]) - SIMD_SP_rsqrt_c0_1[0];
        v22.m128_f32[0] = v22.m128_f32[0] * SIMD_SP_rsqrt_c1_1[0];
        v31.m128_f32[0] = v31.m128_f32[0] * v22.m128_f32[0];
        v32 = _mm_mul_ps(_mm_shuffle_ps(v31, v31, 68), _mm_or_ps(v29, v30));
        tw_1.heartPlane1.a = v32.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.heartPlane1.b, v32);
        v33 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(v25, v25, 54), v32), _mm_mul_ps(_mm_shuffle_ps(v32, v32, 54), v25));
        v34 = _mm_shuffle_ps(v33, v33, 54);
        tw_1.heartPlane2.a = v34.m128_f32[0];
        _mm_storeh_ps((double *)&tw_1.heartPlane2.b, v34);
        v35 = _mm_mul_ps(v32, v27);
        v36 = _mm_mul_ps(v34, v27);
        v35.m128_f32[0] = v35.m128_f32[0] + _mm_movehl_ps(v22, v35).m128_f32[0];
        v36.m128_f32[0] = v36.m128_f32[0] + _mm_movehl_ps(v30, v36).m128_f32[0];
        tw_1.heartPlane1.d = v35.m128_f32[0] + _mm_shuffle_ps(v35, v35, 87).m128_f32[0];
        tw_1.heartPlane2.d = v36.m128_f32[0] + _mm_shuffle_ps(v36, v36, 87).m128_f32[0];
        tw_1.vertices[0].p = tw_1.start;
        v137 = tw_1.dir.z + tw_1.start.z;
        tw_1.vertices[0].endp.x = tw_1.dir.x + tw_1.start.x;
        tw_1.vertices[0].endp.z = v137;
        tw_1.vertices[0].endp.y = tw_1.dir.y + tw_1.start.y;
        tw_1.maxDistFromHeartPlane1 = 1.0;
        tw_1.maxDistFromHeartPlane2 = 1.0;
        tw_1.numVerts = 1;
        tw_1.vertices[0].pl.p[5] = tw_1.dir.y;
        tw_1.numPolys = 0;
        tw_1.numEdges = 0;
        tw_1.pointTrace = 1;
        tw_1.vertices[0].pl.p[0] = tw_1.dir.y * tw_1.start.x - tw_1.start.y * tw_1.dir.x;
        tw_1.vertices[0].pl.p[1] = tw_1.dir.z * tw_1.start.x - tw_1.start.z * tw_1.dir.x;
        tw_1.vertices[0].pl.p[2] = -tw_1.dir.x;
        tw_1.vertices[0].pl.p[3] = tw_1.dir.z * tw_1.start.y - tw_1.dir.y * tw_1.start.z;
        tw_1.vertices[0].pl.p[4] = -tw_1.dir.z;
        idCollisionModelManagerLocal::TraceThroughModel(this, &tw_1);
        trace_t::operator=(results, &tw_1.trace.fraction);
        trmDira = end->x - start->x;
        trmDir_4a = end->y - start->y;
        trmDir_8a = end->z - start->z;
        v37 = results->fraction;
        trmDirb = trmDira * v37;
        trmDir_4b = trmDir_4a * v37;
        v38 = trmDirb + start->x;
        v39 = v37 * trmDir_8a;
        v40 = trmDir_4b + start->y;
        v138 = v39 + start->z;
        results->endpos.z = v138;
        results->endpos.x = v38;
        results->endpos.y = v40;
        results->endAxis = mat3_identity;
        if ( results->fraction < 1.0 )
        {
          if ( model_rotated_3 )
          {
            v41 = results->c.normal.z * modelAxis->endp.z
                + results->c.normal.y * *(float *)&modelAxis->used
                + results->c.normal.x * modelAxis->p.x;
            v42 = results->c.normal.z * *(float *)&modelAxis->pad0
                + results->c.normal.y * modelAxis->endp.x
                + results->c.normal.x * modelAxis->p.y;
            results->c.normal.z = results->c.normal.z * modelAxis->pl.p[0]
                                + results->c.normal.y * modelAxis->endp.y
                                + modelAxis->p.z * results->c.normal.x;
            results->c.normal.x = v41;
            results->c.normal.y = v42;
            v43 = results->c.point.z * modelAxis->endp.z
                + results->c.point.y * *(float *)&modelAxis->used
                + modelAxis->p.x * results->c.point.x;
            v44 = results->c.point.z * *(float *)&modelAxis->pad0
                + results->c.point.y * modelAxis->endp.x
                + modelAxis->p.y * results->c.point.x;
            results->c.point.z = results->c.point.z * modelAxis->pl.p[0]
                               + results->c.point.y * modelAxis->endp.y
                               + modelAxis->p.z * results->c.point.x;
            results->c.point.x = v43;
            results->c.point.y = v44;
          }
          results->c.point.x = results->c.point.x + modelOrigin->p.x;
          results->c.point.y = modelOrigin->p.y + results->c.point.y;
          results->c.point.z = modelOrigin->p.z + results->c.point.z;
          results->c.dist = results->c.normal.z * modelOrigin->p.z
                          + results->c.normal.y * modelOrigin->p.y
                          + results->c.normal.x * modelOrigin->p.x
                          + results->c.dist;
        }
        this->numContacts = tw_1.numContacts;
      }
    }
  }
  else
  {
    results->fraction = 1.0;
    results->endpos = *end;
    results->endAxis = *trmAxis;
  }
}
