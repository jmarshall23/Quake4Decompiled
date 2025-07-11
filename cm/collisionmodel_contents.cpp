
// FUNC: private: bool __thiscall idCollisionModelManagerLocal::TestTrmVertsInBrush(struct cm_traceWork_t *,struct cm_brush_t *)
char __thiscall idCollisionModelManagerLocal::TestTrmVertsInBrush(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_brush_t *b)
{
  int checkCount; // eax
  float *i; // ebp
  int v8; // edi
  int v9; // ecx
  idPlane *planes; // ebx
  double v11; // st7
  idPlane *v12; // eax
  float bestd; // [esp+4h] [ebp-Ch]
  float v14; // [esp+8h] [ebp-8h]
  cm_traceWork_t *twa; // [esp+14h] [ebp+4h]
  int j; // [esp+18h] [ebp+8h]

  checkCount = this->checkCount;
  if ( b->checkcount == checkCount )
    return 0;
  b->checkcount = checkCount;
  if ( (tw->contents & b->contents) == 0
    || tw->traceBounds.b[1].x < (double)b->bounds.b[0].x
    || tw->traceBounds.b[1].y < (double)b->bounds.b[0].y
    || tw->traceBounds.b[1].z < (double)b->bounds.b[0].z
    || tw->traceBounds.b[0].x > (double)b->bounds.b[1].x
    || tw->traceBounds.b[0].y > (double)b->bounds.b[1].y
    || tw->traceBounds.b[0].z > (double)b->bounds.b[1].z )
  {
    return 0;
  }
  if ( tw->pointTrace )
    j = 1;
  else
    j = tw->numVerts;
  twa = 0;
  if ( j <= 0 )
    return 0;
  for ( i = &tw->vertices[0].p.y; ; i += 24 )
  {
    v8 = 0;
    v9 = 0;
    v14 = -1.0e30;
    bestd = v14;
    if ( b->numPlanes <= 0 )
      break;
    planes = b->planes;
    do
    {
      v11 = planes->c * i[1] + planes->b * *i + *(i - 1) * planes->a + planes->d;
      if ( v11 >= 0.0 )
        break;
      if ( v11 > bestd )
      {
        bestd = v11;
        v9 = v8;
      }
      ++v8;
      ++planes;
    }
    while ( v8 < b->numPlanes );
    if ( v8 >= b->numPlanes )
      break;
    twa = (cm_traceWork_t *)((char *)twa + 1);
    if ( (int)twa >= j )
      return 0;
  }
  tw->trace.fraction = 0.0;
  tw->trace.c.type = CONTACT_TRMVERTEX;
  v12 = b->planes;
  tw->trace.c.normal.x = v12[v9].a;
  tw->trace.c.normal.y = v12[v9].b;
  tw->trace.c.normal.z = v12[v9].c;
  tw->trace.c.dist = -b->planes[v9].d;
  tw->trace.c.contents = b->contents;
  tw->trace.c.material = b->material;
  tw->trace.c.point.x = *(i - 1);
  tw->trace.c.point.y = *i;
  tw->trace.c.point.z = i[1];
  tw->trace.c.trmFeature = (int)twa;
  tw->trace.c.modelFeature = 0;
  idCollisionModelManagerLocal::CM_GetMaterialType(this, tw, 0);
  return 1;
}

// FUNC: private: bool __thiscall idCollisionModelManagerLocal::TestTrmInPolygon(struct cm_traceWork_t *,struct cm_polygon_t *)
bool __thiscall idCollisionModelManagerLocal::TestTrmInPolygon(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_polygon_t *p)
{
  int checkCount; // eax
  cm_polygon_t *v5; // edi
  bool result; // al
  idBounds *p_traceBounds; // ecx
  int v8; // eax
  int v9; // ebp
  unsigned int v10; // eax
  bool v11; // zf
  cm_edge_t *v12; // eax
  int *vertexNum; // eax
  cm_vertex_t *v14; // ebx
  int v15; // ecx
  int v16; // ebp
  float *p_b; // edx
  double v18; // st7
  bool v19; // cc
  int v20; // eax
  float *v21; // ebx
  unsigned int v22; // ebp
  unsigned int v23; // edx
  cm_edge_t *v24; // ecx
  int v25; // eax
  cm_edge_t *v26; // edx
  cm_vertex_t *vertices; // ecx
  float *p_x; // eax
  double x; // st7
  float *v30; // ecx
  cm_vertex_t *v31; // eax
  int v32; // ecx
  int numVerts; // ebx
  float *p_y; // edx
  int v35; // eax
  float *v36; // eax
  double v37; // st7
  double v38; // st6
  int v39; // ecx
  int *v40; // ebp
  unsigned int v41; // eax
  int v42; // edi
  float *v43; // ebx
  cm_edge_t *v44; // eax
  unsigned int sideSet; // edx
  int v46; // ebp
  int v47; // edi
  int v48; // ecx
  float *v49; // ebx
  int v50; // eax
  float v51; // edi
  float *v52; // eax
  cm_edge_t *v53; // ebp
  int v54; // eax
  cm_vertex_t *v55; // edi
  int v56; // edx
  unsigned int v57; // ecx
  cm_vertex_t *v58; // ecx
  unsigned int side; // edi
  unsigned int v60; // edi
  unsigned int v61; // ecx
  int v62; // edx
  float *v63; // eax
  double v64; // st7
  double v65; // st6
  idCollisionModelLocal *model; // edi
  int j; // [esp+8h] [ebp-B8h]
  int ja; // [esp+8h] [ebp-B8h]
  int jb; // [esp+8h] [ebp-B8h]
  int i; // [esp+Ch] [ebp-B4h]
  int ia; // [esp+Ch] [ebp-B4h]
  int ib; // [esp+Ch] [ebp-B4h]
  int ic; // [esp+Ch] [ebp-B4h]
  int v74; // [esp+10h] [ebp-B0h]
  float *v75; // [esp+10h] [ebp-B0h]
  int k; // [esp+14h] [ebp-ACh]
  int *ka; // [esp+14h] [ebp-ACh]
  int kb; // [esp+14h] [ebp-ACh]
  int *flip; // [esp+18h] [ebp-A8h]
  int flipa; // [esp+18h] [ebp-A8h]
  int flipb; // [esp+18h] [ebp-A8h]
  cm_edge_t *fl; // [esp+20h] [ebp-A0h]
  float flb; // [esp+20h] [ebp-A0h]
  unsigned int fla; // [esp+20h] [ebp-A0h]
  float flc; // [esp+20h] [ebp-A0h]
  cm_edge_t *edges; // [esp+24h] [ebp-9Ch]
  int v88; // [esp+24h] [ebp-9Ch]
  float *v89; // [esp+24h] [ebp-9Ch]
  float bestd; // [esp+28h] [ebp-98h]
  unsigned int bestda; // [esp+28h] [ebp-98h]
  int bestdb; // [esp+28h] [ebp-98h]
  int *v93; // [esp+2Ch] [ebp-94h]
  unsigned int trmEdgeNum; // [esp+30h] [ebp-90h]
  float v95; // [esp+3Ch] [ebp-84h]
  float v96; // [esp+3Ch] [ebp-84h]
  int sides[32]; // [esp+40h] [ebp-80h]

  checkCount = this->checkCount;
  v5 = p;
  if ( p->checkcount == checkCount )
    return 0;
  p->checkcount = checkCount;
  if ( (tw->contents & p->contents) == 0 )
    return 0;
  p_traceBounds = &tw->traceBounds;
  if ( tw->traceBounds.b[1].x < (double)p->bounds.b[0].x
    || tw->traceBounds.b[1].y < (double)p->bounds.b[0].y
    || tw->traceBounds.b[1].z < (double)p->bounds.b[0].z
    || p_traceBounds->b[0].x > (double)p->bounds.b[1].x
    || tw->traceBounds.b[0].y > (double)p->bounds.b[1].y
    || tw->traceBounds.b[0].z > (double)p->bounds.b[1].z )
  {
    return 0;
  }
  v8 = idBounds::PlaneSide(p_traceBounds, &p->plane, 0.1);
  if ( !v8 )
  {
    if ( tw->model->isConvex )
    {
      result = 1;
      tw->quickExit = 1;
      return result;
    }
    return 0;
  }
  if ( v8 != 3 )
    return 0;
  if ( tw->isConvex )
  {
    i = 0;
    if ( p->numEdges > 0 )
    {
      v9 = this->checkCount;
      edges = tw->model->edges;
      v74 = v9;
      flip = p->edges;
      do
      {
        v10 = abs32(*flip);
        v11 = edges[v10].checkcount == v9;
        v12 = &edges[v10];
        fl = v12;
        if ( !v11 )
        {
          vertexNum = v12->vertexNum;
          j = 0;
          k = (int)vertexNum;
          do
          {
            v14 = &tw->model->vertices[*vertexNum];
            if ( v14->checkcount != v9 )
            {
              v15 = 0;
              v16 = 0;
              bestd = -1.0e30;
              if ( tw->numPolys > 0 )
              {
                p_b = &tw->polys[0].plane.b;
                do
                {
                  v18 = p_b[1] * v14->p.z + *(p_b - 1) * v14->p.x + v14->p.y * *p_b + p_b[2];
                  if ( v18 >= 0.0 )
                    break;
                  if ( v18 > bestd )
                  {
                    bestd = v18;
                    v16 = v15;
                  }
                  ++v15;
                  p_b += 28;
                }
                while ( v15 < tw->numPolys );
              }
              if ( v15 >= tw->numPolys )
              {
                tw->trace.c.type = CONTACT_MODELVERTEX;
                tw->trace.fraction = 0.0;
                v36 = (float *)((char *)tw + 112 * v16);
                v37 = -v36[1560];
                v38 = -v36[1561];
                v95 = -v36[1562];
                tw->trace.c.normal.z = v95;
                tw->trace.c.normal.x = v37;
                tw->trace.c.normal.y = v38;
                tw->trace.c.dist = v36[1563];
                tw->trace.c.contents = p->contents;
                tw->trace.c.material = p->material;
                tw->trace.c.point = v14->p;
                tw->trace.c.modelFeature = fl->vertexNum[j];
                tw->trace.c.trmFeature = 0;
                idCollisionModelManagerLocal::CM_GetMaterialType(this, tw, p);
                return 1;
              }
              v9 = v74;
            }
            vertexNum = (int *)(k + 4);
            v19 = ++j < 2;
            k += 4;
          }
          while ( v19 );
        }
        ++flip;
        ++i;
      }
      while ( i < p->numEdges );
    }
  }
  v20 = 0;
  ia = 0;
  if ( p->numEdges > 0 )
  {
    v21 = &tw->polygonEdgePlueckerCache[0].p[2];
    do
    {
      v22 = v5->edges[v20];
      v23 = abs32(v22);
      v24 = tw->model->edges;
      v25 = v24[v23].checkcount;
      v26 = &v24[v23];
      if ( v25 != this->checkCount )
        v26->sideSet = 0;
      vertices = tw->model->vertices;
      p_x = &vertices[v26->vertexNum[1]].p.x;
      x = vertices[v26->vertexNum[0]].p.x;
      v30 = &vertices[v26->vertexNum[0]].p.x;
      *(v21 - 2) = x * p_x[1] - *p_x * v30[1];
      *(v21 - 1) = *v30 * p_x[2] - *p_x * v30[2];
      *v21 = *v30 - *p_x;
      v21[1] = v30[1] * p_x[2] - p_x[1] * v30[2];
      v21[2] = v30[2] - p_x[2];
      v21[3] = p_x[1] - v30[1];
      v31 = &tw->model->vertices[v26->vertexNum[v22 >> 31]];
      if ( v31->checkcount != this->checkCount )
        v31->sideSet = 0;
      v5 = p;
      v31->checkcount = this->checkCount;
      v20 = ia + 1;
      v21 += 6;
      ++ia;
    }
    while ( ia < p->numEdges );
  }
  v32 = 0;
  if ( tw->numVerts > 0 )
  {
    numVerts = tw->numVerts;
    p_y = &tw->vertices[0].p.y;
    do
    {
      if ( p_y[1] * v5->plane.c + *(p_y - 1) * v5->plane.a + *p_y * v5->plane.b + v5->plane.d >= 0.0 )
        v35 = 1;
      else
        v35 = -1;
      sides[v32++] = v35;
      p_y += 24;
    }
    while ( v32 < numVerts );
  }
  v39 = 1;
  ib = 1;
  if ( tw->numEdges >= 1 )
  {
    v40 = tw->edges[1].vertexNum;
    ka = tw->edges[1].vertexNum;
    do
    {
      v41 = sides[*v40];
      if ( v41 != sides[v40[1]] )
      {
        flipa = v41 >> 31;
        ja = 0;
        if ( v5->numEdges > 0 )
        {
          v42 = 1 << v39;
          v43 = &tw->polygonEdgePlueckerCache[0].p[2];
          v88 = 1 << v39;
          do
          {
            bestda = p->edges[ja];
            v44 = &tw->model->edges[abs32(bestda)];
            sideSet = v44->sideSet;
            if ( (sideSet & v42) == 0 )
            {
              flb = *((float *)v40 + 6) * *(v43 - 2)
                  + *((float *)v40 + 7) * *(v43 - 1)
                  + *((float *)v40 + 3) * v43[3]
                  + *((float *)v40 + 4) * v43[1]
                  + *((float *)v40 + 5) * *v43
                  + v43[2] * *((float *)v40 + 2);
              v46 = LODWORD(flb) >> 31 << v39;
              v39 = ib;
              v47 = v46 | v44->side & ~v42;
              v40 = ka;
              v44->side = v47;
              v42 = v88;
              v44->sideSet = v88 | sideSet;
            }
            if ( flipa ^ (bestda >> 31) ^ (v44->side >> v39) & 1 )
              break;
            v43 += 6;
            ++ja;
          }
          while ( ja < p->numEdges );
        }
        if ( ja >= p->numEdges )
        {
          tw->trace.fraction = 0.0;
          tw->trace.c.type = CONTACT_EDGE;
          tw->trace.c.normal.x = p->plane.a;
          tw->trace.c.normal.y = p->plane.b;
          tw->trace.c.normal.z = p->plane.c;
          tw->trace.c.dist = -p->plane.d;
          tw->trace.c.contents = p->contents;
          tw->trace.c.material = p->material;
          v50 = tw->edges[v39].vertexNum[flipa == 0];
          v51 = tw->vertices[v50].p.x;
          v52 = (float *)((char *)tw + v50 * 96);
          tw->trace.c.point.x = v51;
          tw->trace.c.point.y = v52[1];
          tw->trace.c.point.z = v52[2];
          tw->trace.c.modelFeature = (int)p;
          tw->trace.c.trmFeature = v39;
          idCollisionModelManagerLocal::CM_GetMaterialType(this, tw, p);
          return 1;
        }
        v5 = p;
      }
      ++v39;
      v40 += 24;
      ib = v39;
      ka = v40;
    }
    while ( v39 <= tw->numEdges );
  }
  v48 = 0;
  ic = 0;
  if ( v5->numEdges <= 0 )
    return 0;
  v49 = &tw->polygonEdgePlueckerCache[0].p[2];
  v89 = &tw->polygonEdgePlueckerCache[0].p[2];
  while ( 1 )
  {
    bestdb = v5->edges[v48];
    v53 = &tw->model->edges[abs32(bestdb)];
    v54 = this->checkCount;
    if ( v53->checkcount != v54 )
    {
      v53->checkcount = v54;
      jb = 0;
      if ( tw->numPolys > 0 )
        break;
    }
LABEL_83:
    ++v48;
    v49 += 6;
    ic = v48;
    v89 = v49;
    if ( v48 >= p->numEdges )
      return 0;
    v5 = p;
  }
  v75 = &tw->polys[0].plane.b;
  while ( 1 )
  {
    v55 = &tw->model->vertices[v53->vertexNum[0]];
    v56 = 1 << jb;
    v57 = v55->sideSet;
    if ( (v57 & (1 << jb)) == 0 )
    {
      if ( v75[1] * v55->p.z + v55->p.y * *v75 + *(v75 - 1) * v55->p.x + v75[2] >= 0.0 )
        v55->side &= ~v56;
      else
        v55->side |= v56;
      v55->sideSet = v56 | v57;
    }
    v58 = &tw->model->vertices[v53->vertexNum[1]];
    fla = v58->sideSet;
    if ( (fla & v56) == 0 )
    {
      if ( v75[1] * v58->p.z + v58->p.y * *v75 + *(v75 - 1) * v58->p.x + v75[2] >= 0.0 )
        v58->side &= ~v56;
      else
        v58->side |= v56;
      v58->sideSet = v56 | fla;
    }
    side = v55->side;
    if ( (((side ^ v58->side) >> jb) & 1) != 0 )
    {
      kb = 0;
      flipb = (side >> jb) & 1;
      if ( *((int *)v75 + 4) > 0 )
      {
        v93 = (int *)(v75 + 5);
        do
        {
          v60 = v53->sideSet;
          trmEdgeNum = *v93;
          v61 = abs32(*v93);
          v62 = 1 << v61;
          if ( (v60 & (1 << v61)) == 0 )
          {
            flc = *(v49 - 1) * tw->edges[v61].pl.p[5]
                + *(v49 - 2) * tw->edges[v61].pl.p[4]
                + v49[3] * tw->edges[v61].pl.p[1]
                + v49[1] * tw->edges[v61].pl.p[2]
                + tw->edges[v61].pl.p[3] * *v49
                + v49[2] * tw->edges[v61].pl.p[0];
            v49 = v89;
            v53->side = (LODWORD(flc) >> 31 << v61) | v53->side & ~v62;
            v53->sideSet = v62 | v60;
          }
          if ( flipb ^ (trmEdgeNum >> 31) ^ (v53->side >> v61) & 1 )
            break;
          ++v93;
          ++kb;
        }
        while ( kb < *((_DWORD *)v75 + 4) );
      }
      if ( kb >= *((_DWORD *)v75 + 4) )
        break;
    }
    v75 += 28;
    if ( ++jb >= tw->numPolys )
    {
      v48 = ic;
      goto LABEL_83;
    }
  }
  tw->trace.fraction = 0.0;
  tw->trace.c.type = CONTACT_EDGE;
  v63 = (float *)((char *)tw + 112 * jb);
  v64 = -v63[1560];
  v65 = -v63[1561];
  v96 = -v63[1562];
  tw->trace.c.normal.z = v96;
  tw->trace.c.normal.x = v64;
  tw->trace.c.normal.y = v65;
  model = tw->model;
  tw->trace.c.dist = v63[1563];
  tw->trace.c.contents = p->contents;
  tw->trace.c.material = p->material;
  tw->trace.c.point = model->vertices[v53->vertexNum[flipb == 0]].p;
  tw->trace.c.modelFeature = bestdb;
  tw->trace.c.trmFeature = jb;
  idCollisionModelManagerLocal::CM_GetMaterialType(this, tw, p);
  return 1;
}

// FUNC: private: struct cm_node_t * __thiscall idCollisionModelManagerLocal::PointNode(class idVec3 const &,class idCollisionModelLocal *)
cm_node_t *__thiscall idCollisionModelManagerLocal::PointNode(
        idCollisionModelManagerLocal *this,
        const idVec3 *p,
        idCollisionModelLocal *model)
{
  cm_node_t *node; // ecx
  int i; // eax

  node = model->node;
  for ( i = node->planeType; node->planeType != -1; i = node->planeType )
  {
    if ( *(&p->x + i) <= (double)node->planeDist )
      node = node->children[1];
    else
      node = node->children[0];
  }
  return node;
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::PointContents(class idVec3,class idCollisionModelLocal *)
int __thiscall idCollisionModelManagerLocal::PointContents(
        idCollisionModelManagerLocal *this,
        idVec3 p,
        idCollisionModelLocal *model)
{
  cm_brushRef_t *brushes; // ebx
  cm_brush_t *b; // edi
  int i; // ecx
  int v6; // edx
  bool v7; // c0
  float *v8; // edx
  int numPlanes; // esi
  float *p_a; // ecx
  int v11; // edx

  brushes = idCollisionModelManagerLocal::PointNode(this, &p, model)->brushes;
  if ( brushes )
  {
    while ( 2 )
    {
      b = brushes->b;
      for ( i = 0; i < 3; ++i )
      {
        v6 = (char *)brushes->b - (char *)&p + 4 * i;
        v7 = *(&p.x + i) < (double)*(float *)((char *)&p.x + v6);
        v8 = (float *)((char *)&p.x + v6);
        if ( v7 || *(&p.x + i) > (double)v8[3] )
          goto LABEL_22;
      }
      numPlanes = b->numPlanes;
      p_a = &b->planes->a;
      v11 = 0;
      if ( numPlanes < 4 )
      {
LABEL_14:
        if ( v11 >= numPlanes )
          return b->contents;
        do
        {
          if ( p.y * p_a[1] + p.z * p_a[2] + p.x * *p_a + p_a[3] >= 0.0 )
            break;
          ++v11;
          p_a += 4;
        }
        while ( v11 < numPlanes );
      }
      else
      {
        while ( p.y * p_a[1] + p.z * p_a[2] + p.x * *p_a + p_a[3] < 0.0 )
        {
          if ( p.y * p_a[5] + p.z * p_a[6] + p.x * p_a[4] + p_a[7] >= 0.0 )
          {
            ++v11;
            break;
          }
          if ( p.y * p_a[9] + p.z * p_a[10] + p.x * p_a[8] + p_a[11] >= 0.0 )
          {
            v11 += 2;
            break;
          }
          if ( p.y * p_a[13] + p.z * p_a[14] + p.x * p_a[12] + p_a[15] >= 0.0 )
          {
            v11 += 3;
            break;
          }
          v11 += 4;
          p_a += 16;
          if ( v11 >= numPlanes - 3 )
            goto LABEL_14;
        }
      }
      if ( v11 < numPlanes )
      {
LABEL_22:
        brushes = brushes->next;
        if ( brushes )
          continue;
        return 0;
      }
      return b->contents;
    }
  }
  return 0;
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::TransformedPointContents(class idVec3 const &,class idCollisionModelLocal *,class idVec3 const &,class idMat3 const &)
int __thiscall idCollisionModelManagerLocal::TransformedPointContents(
        idCollisionModelManagerLocal *this,
        const idVec3 *p,
        idCollisionModelLocal *model,
        const idVec3 *origin,
        const idMat3 *modelAxis)
{
  double v5; // st7
  __int64 v7; // [esp+4h] [ebp-14h]
  idVec3 p_l; // [esp+Ch] [ebp-Ch]

  v5 = p->x - origin->x;
  *(float *)&v7 = p->y - origin->y;
  *((float *)&v7 + 1) = p->z - origin->z;
  *(_QWORD *)&p_l.y = v7;
  p_l.x = v5;
  if ( LODWORD(modelAxis->mat[0].x) != 1065353216
    || LODWORD(modelAxis->mat[1].y) != 1065353216
    || LODWORD(modelAxis->mat[2].z) != 1065353216 )
  {
    p_l.z = *((float *)&v7 + 1) * modelAxis->mat[2].z + v5 * modelAxis->mat[0].z + *(float *)&v7 * modelAxis->mat[1].z;
    p_l.x = *((float *)&v7 + 1) * modelAxis->mat[2].x + *(float *)&v7 * modelAxis->mat[1].x + v5 * modelAxis->mat[0].x;
    p_l.y = *((float *)&v7 + 1) * modelAxis->mat[2].y + v5 * modelAxis->mat[0].y + *(float *)&v7 * modelAxis->mat[1].y;
  }
  return idCollisionModelManagerLocal::PointContents(this, p_l, model);
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::ContentsTrm(struct trace_t *,class idVec3 const &,class idTraceModel const *,class idMat3 const &,int,class idCollisionModel *,class idVec3 const &,class idMat3 const &)
int __thiscall idCollisionModelManagerLocal::ContentsTrm(
        idCollisionModelManagerLocal *this,
        trace_t *results,
        const idVec3 *start,
        const idTraceModel *trm,
        const idMat3 *trmAxis,
        int contentMask,
        idCollisionModelLocal *model,
        cm_trmVertex_t *modelOrigin,
        const idMat3 *modelAxis)
{
  const idTraceModel *v10; // ecx
  int v11; // eax
  double v13; // st7
  double v15; // st6
  double z; // st7
  double y; // st6
  double x; // st5
  double v20; // st4
  double v21; // st3
  double v22; // st4
  double v23; // st3
  double v24; // st4
  double v25; // st3
  double v26; // st4
  double v27; // st3
  double v28; // st4
  double v29; // st3
  cm_traceWork_t *v30; // edx
  float *p_y; // eax
  float v32; // xmm1_4
  float v33; // xmm3_4
  float v34; // xmm5_4
  bool v35; // cc
  int v36; // edi
  float *v37; // edx
  int *v38; // esi
  int v39; // ecx
  int v40; // eax
  float *p_x; // ecx
  float *v42; // eax
  int *p_numEdges; // ecx
  float *v44; // esi
  int v45; // edx
  int v46; // eax
  traceModel_t *v47; // edx
  traceModel_t type; // edi
  unsigned int v49; // edx
  double v50; // st7
  double v51; // st7
  __m128 v52; // xmm0
  __m128 v53; // xmm1
  __m128 v54; // xmm2
  __m128 v55; // xmm3
  __m128 v56; // xmm4
  __m128 v57; // xmm0
  __m128 v58; // xmm2
  float trmTransform; // [esp+0h] [ebp-5Ch]
  float trmTransform_4; // [esp+4h] [ebp-58h]
  float trmTransform_8; // [esp+8h] [ebp-54h]
  float trmTransform_12; // [esp+Ch] [ebp-50h]
  float trmTransform_16; // [esp+10h] [ebp-4Ch]
  float trmTransform_20; // [esp+14h] [ebp-48h]
  float trmTransform_24; // [esp+18h] [ebp-44h]
  float trmTransform_28; // [esp+1Ch] [ebp-40h]
  float trmTransform_32; // [esp+20h] [ebp-3Ch]
  float trmTransform_36; // [esp+24h] [ebp-38h]
  float trmTransform_40; // [esp+28h] [ebp-34h]
  float trmTransform_44; // [esp+2Ch] [ebp-30h]
  float v71; // [esp+34h] [ebp-28h]
  float v72; // [esp+38h] [ebp-24h]
  float v73; // [esp+40h] [ebp-1Ch]
  float v74; // [esp+44h] [ebp-18h]
  float v75; // [esp+48h] [ebp-14h]
  float v76; // [esp+4Ch] [ebp-10h]
  float v77; // [esp+50h] [ebp-Ch]
  float v79; // [esp+58h] [ebp-4h]
  const idTraceModel *trma; // [esp+6Ch] [ebp+10h]
  float trmAxisa; // [esp+70h] [ebp+14h]
  int contentMaska; // [esp+74h] [ebp+18h]
  float ib; // [esp+78h] [ebp+1Ch]
  int ic; // [esp+78h] [ebp+1Ch]
  int i; // [esp+78h] [ebp+1Ch]
  int ia; // [esp+78h] [ebp+1Ch]
  float verta; // [esp+7Ch] [ebp+20h]
  cm_traceWork_t *vert; // [esp+7Ch] [ebp+20h]
  float modelAxisa; // [esp+80h] [ebp+24h]

  if ( (_S5_39 & 1) == 0 )
    _S5_39 |= 1u;
  v10 = trm;
  if ( trm )
  {
    ++this->checkCount;
    tw.contents = contentMask;
    tw.trace.fraction = 1.0;
    tw.trace.c.contents = 0;
    tw.trace.c.type = CONTACT_NONE;
    tw.trace.c.material = 0;
    tw.trace.c.materialType = 0;
    tw.isConvex = trm->isConvex;
    tw.model = model;
    tw.rotation = 0;
    tw.positionTest = 1;
    tw.pointTrace = 0;
    tw.quickExit = 0;
    tw.numContacts = 0;
    v13 = start->x - modelOrigin->p.x;
    v73 = start->y - modelOrigin->p.y;
    v15 = start->z - modelOrigin->p.z;
    tw.start.y = v73;
    v74 = v15;
    tw.start.z = v74;
    tw.start.x = v13;
    tw.end.y = v73;
    tw.end.x = v13;
    tw.end.z = v74;
    trmTransform = trmAxis->mat[0].x;
    v75 = start->x - modelOrigin->p.x;
    trmTransform_4 = trmAxis->mat[1].x;
    trmTransform_8 = trmAxis->mat[2].x;
    trmTransform_16 = trmAxis->mat[0].y;
    v76 = start->y - modelOrigin->p.y;
    trmTransform_20 = trmAxis->mat[1].y;
    trmTransform_24 = trmAxis->mat[2].y;
    v77 = start->z - modelOrigin->p.z;
    trmTransform_32 = trmAxis->mat[0].z;
    trmTransform_12 = v75;
    trmTransform_44 = v77;
    trmTransform_36 = trmAxis->mat[1].z;
    trmTransform_40 = trmAxis->mat[2].z;
    trmTransform_28 = v76;
    if ( LODWORD(trmAxis->mat[0].x) == 1065353216
      && LODWORD(trmAxis->mat[1].y) == 1065353216
      && LODWORD(trmAxis->mat[2].z) == 1065353216 )
    {
      tw.start.x = v13 + trm->offset.x;
      tw.start.y = v73 + trm->offset.y;
      tw.start.z = v74 + trm->offset.z;
      tw.end.x = v13 + trm->offset.x;
      tw.end.y = v73 + trm->offset.y;
      tw.end.z = v74 + trm->offset.z;
    }
    else
    {
      v71 = trm->offset.y * trmAxis->mat[1].y + trm->offset.z * trmAxis->mat[2].y + trm->offset.x * trmAxis->mat[0].y;
      v72 = trm->offset.z * trmAxis->mat[2].z + trmAxis->mat[0].z * trm->offset.x + trm->offset.y * trmAxis->mat[1].z;
      tw.start.x = v13
                 + trm->offset.z * trmAxis->mat[2].x
                 + trmAxis->mat[0].x * trm->offset.x
                 + trm->offset.y * trmAxis->mat[1].x;
      tw.start.y = v71 + v73;
      ib = v72 + v74;
      tw.start.z = ib;
      tw.end.z = ib;
      tw.end.x = tw.start.x;
      tw.end.y = tw.start.y;
    }
    if ( LODWORD(modelAxis->mat[0].x) != 1065353216
      || LODWORD(modelAxis->mat[1].y) != 1065353216
      || LODWORD(modelAxis->mat[2].z) != 1065353216 )
    {
      z = modelAxis->mat[0].z;
      y = modelAxis->mat[0].y;
      v79 = modelAxis->mat[2].z;
      x = modelAxis->mat[0].x;
      trmAxisa = modelAxis->mat[1].z;
      contentMaska = SLODWORD(modelAxis->mat[2].y);
      verta = modelAxis->mat[1].y;
      modelAxisa = modelAxis->mat[2].x;
      ic = SLODWORD(modelAxis->mat[1].x);
      v20 = z * tw.start.z + y * tw.start.y + x * tw.start.x;
      v21 = trmAxisa * tw.start.z + verta * tw.start.y + *(float *)&ic * tw.start.x;
      tw.start.z = v79 * tw.start.z + *(float *)&contentMaska * tw.start.y + modelAxisa * tw.start.x;
      tw.start.x = v20;
      tw.start.y = v21;
      v22 = z * tw.end.z + y * tw.end.y + x * tw.end.x;
      v23 = trmAxisa * tw.end.z + verta * tw.end.y + *(float *)&ic * tw.end.x;
      tw.end.z = v79 * tw.end.z + *(float *)&contentMaska * tw.end.y + modelAxisa * tw.end.x;
      tw.end.x = v22;
      tw.end.y = v23;
      v24 = trmTransform * x + trmTransform_32 * z + trmTransform_16 * y;
      v25 = *(float *)&ic * trmTransform + trmTransform_32 * trmAxisa + trmTransform_16 * verta;
      trmTransform_32 = modelAxisa * trmTransform + trmTransform_32 * v79 + trmTransform_16 * *(float *)&contentMaska;
      trmTransform_16 = v25;
      trmTransform = v24;
      v26 = trmTransform_36 * z + trmTransform_20 * y + trmTransform_4 * x;
      v27 = trmTransform_36 * trmAxisa + trmTransform_20 * verta + trmTransform_4 * *(float *)&ic;
      trmTransform_36 = trmTransform_36 * v79 + trmTransform_20 * *(float *)&contentMaska + trmTransform_4 * modelAxisa;
      trmTransform_20 = v27;
      trmTransform_4 = v26;
      v28 = trmTransform_40 * z + trmTransform_24 * y + trmTransform_8 * x;
      v29 = trmTransform_40 * trmAxisa + trmTransform_24 * verta + trmTransform_8 * *(float *)&ic;
      trmTransform_40 = trmTransform_40 * v79 + trmTransform_24 * *(float *)&contentMaska + trmTransform_8 * modelAxisa;
      trmTransform_24 = v29;
      trmTransform_8 = v28;
      trmTransform_44 = modelAxisa * v75 + v76 * *(float *)&contentMaska + v77 * v79;
      trmTransform_28 = *(float *)&ic * v75 + v76 * verta + v77 * trmAxisa;
      trmTransform_12 = x * v75 + v76 * y + v77 * z;
    }
    tw.trmBounds.b[0].y = idMath::INFINITY;
    tw.trmBounds.b[1].z = -1.0e30;
    tw.trmBounds.b[0].z = idMath::INFINITY;
    tw.trmBounds.b[0].x = idMath::INFINITY;
    tw.trmBounds.b[1].y = tw.trmBounds.b[1].z;
    tw.trmBounds.b[1].x = tw.trmBounds.b[1].z;
    v30 = &tw;
    tw.numVerts = trm->numVerts;
    vert = &tw;
    i = 0;
    if ( tw.numVerts > 0 )
    {
      p_y = &trm->verts[0].y;
      do
      {
        v30->vertices[0].used = 1;
        v30->vertices[0].p.x = trmTransform * *(p_y - 1)
                             + trmTransform_8 * p_y[1]
                             + trmTransform_4 * *p_y
                             + trmTransform_12;
        v30->vertices[0].p.y = trmTransform_24 * p_y[1]
                             + trmTransform_16 * *(p_y - 1)
                             + trmTransform_20 * *p_y
                             + trmTransform_28;
        v30->vertices[0].p.z = trmTransform_40 * p_y[1]
                             + trmTransform_32 * *(p_y - 1)
                             + trmTransform_36 * *p_y
                             + trmTransform_44;
        v32 = vert->vertices[0].p.x;
        tw.trmBounds.b[0].x = fminf(tw.trmBounds.b[0].x, vert->vertices[0].p.x);
        v33 = vert->vertices[0].p.y;
        tw.trmBounds.b[0].y = fminf(tw.trmBounds.b[0].y, v33);
        v34 = vert->vertices[0].p.z;
        tw.trmBounds.b[0].z = fminf(tw.trmBounds.b[0].z, v34);
        tw.trmBounds.b[1].x = fmaxf(v32, tw.trmBounds.b[1].x);
        tw.trmBounds.b[1].y = fmaxf(v33, tw.trmBounds.b[1].y);
        tw.trmBounds.b[1].z = fmaxf(v34, tw.trmBounds.b[1].z);
        v30 = (cm_traceWork_t *)((char *)v30 + 96);
        p_y += 3;
        v35 = ++i < tw.numVerts;
        vert = v30;
      }
      while ( v35 );
    }
    v36 = 1;
    tw.trmBounds.b[0].x = tw.trmBounds.b[0].x - tw.start.x;
    tw.trmBounds.b[0].y = tw.trmBounds.b[0].y - tw.start.y;
    tw.trmBounds.b[0].z = tw.trmBounds.b[0].z - tw.start.z;
    tw.trmBounds.b[1].x = tw.trmBounds.b[1].x - tw.start.x;
    tw.trmBounds.b[1].y = tw.trmBounds.b[1].y - tw.start.y;
    tw.trmBounds.b[1].z = tw.trmBounds.b[1].z - tw.start.z;
    tw.numEdges = trm->numEdges;
    if ( tw.numEdges >= 1 )
    {
      v37 = &tw.edges[1].pl.p[2];
      v38 = &trm->edges[1].v[1];
      do
      {
        *((_WORD *)v37 - 16) = 1;
        v39 = *(v38 - 1);
        v40 = *v38;
        *((_DWORD *)v37 - 4) = v39;
        *((_DWORD *)v37 - 3) = v40;
        p_x = &tw.vertices[v39].p.x;
        v42 = &tw.vertices[v40].p.x;
        ++v36;
        v38 += 5;
        v37 += 24;
        *(v37 - 26) = *p_x * v42[1] - p_x[1] * *v42;
        *(v37 - 25) = *p_x * v42[2] - *v42 * p_x[2];
        *(v37 - 24) = *p_x - *v42;
        *(v37 - 23) = p_x[1] * v42[2] - v42[1] * p_x[2];
        *(v37 - 22) = p_x[2] - v42[2];
        *(v37 - 21) = v42[1] - p_x[1];
      }
      while ( v36 <= tw.numEdges );
      v10 = trm;
    }
    tw.numPolys = v10->numPolys;
    ia = 0;
    if ( tw.numPolys > 0 )
    {
      p_numEdges = &tw.polys[0].numEdges;
      v44 = &trm->polys[0].normal.y;
      do
      {
        *(p_numEdges - 1) = 1;
        v45 = *((_DWORD *)v44 + 9);
        v46 = 0;
        *p_numEdges = v45;
        if ( v45 > 0 )
        {
          v47 = (traceModel_t *)(p_numEdges + 1);
          trma = (const idTraceModel *)(v44 + 10);
          do
          {
            type = trma->type;
            trma = (const idTraceModel *)((char *)trma + 4);
            *v47 = type;
            ++v46;
            ++v47;
          }
          while ( v46 < *p_numEdges );
        }
        v49 = abs32(p_numEdges[1]);
        v50 = trmTransform_4 * *v44 + trmTransform_8 * v44[1];
        v44 += 27;
        p_numEdges += 28;
        *((float *)p_numEdges - 33) = v50 + trmTransform * *(v44 - 28);
        *((float *)p_numEdges - 32) = trmTransform_20 * *(v44 - 27)
                                    + trmTransform_24 * *(v44 - 26)
                                    + trmTransform_16 * *(v44 - 28);
        v51 = trmTransform_36 * *(v44 - 27) + trmTransform_40 * *(v44 - 26) + trmTransform_32 * *(v44 - 28);
        *((float *)p_numEdges - 31) = v51;
        ++ia;
        *((float *)p_numEdges - 30) = -(v51 * tw.vertices[tw.edges[v49].vertexNum[0]].p.z
                                      + tw.vertices[tw.edges[v49].vertexNum[0]].p.y * *((float *)p_numEdges - 32)
                                      + *((float *)p_numEdges - 33) * tw.vertices[tw.edges[v49].vertexNum[0]].p.x);
      }
      while ( ia < tw.numPolys );
    }
    v52 = _mm_loadh_ps((const double *)&tw.start.y);
    v53 = _mm_loadh_ps((const double *)&tw.end.y);
    v54 = _mm_loadh_ps((const double *)&tw.trmBounds.b[0].y);
    v55 = _mm_loadh_ps((const double *)&tw.trmBounds.b[1].y);
    v56 = _mm_sub_ps(_mm_add_ps(_mm_min_ps(v52, v53), v54), *(__m128 *)SIMD_SP_boxEpsilon);
    v57 = _mm_add_ps(_mm_add_ps(_mm_max_ps(v52, v53), v55), *(__m128 *)SIMD_SP_boxEpsilon);
    tw.traceBounds.b[0].x = v56.m128_f32[0];
    _mm_storeh_ps((double *)&tw.traceBounds.b[0].y, v56);
    tw.traceBounds.b[1].x = v57.m128_f32[0];
    _mm_storeh_ps((double *)&tw.traceBounds.b[1].y, v57);
    v58 = _mm_add_ps(
            _mm_max_ps(_mm_and_ps(v54, *(__m128 *)SIMD_SP_absMask), _mm_and_ps(v55, *(__m128 *)SIMD_SP_absMask)),
            *(__m128 *)SIMD_SP_boxEpsilon);
    tw.trmExtents.x = v58.m128_f32[0];
    _mm_storeh_ps((double *)&tw.trmExtents.y, v58);
    idCollisionModelManagerLocal::TraceThroughModel(this, &tw);
    *results = tw.trace;
    results->fraction = (float)(results->c.contents == 0);
    results->endpos = *start;
    results->endAxis = *trmAxis;
    return results->c.contents;
  }
  else
  {
    v11 = idCollisionModelManagerLocal::TransformedPointContents(this, start, model, &modelOrigin->p, modelAxis);
    results->c.contents = v11;
    results->fraction = (float)(v11 == 0);
    results->endpos = *start;
    results->endAxis = *trmAxis;
    return results->c.contents;
  }
}

// FUNC: public: virtual int __thiscall idCollisionModelManagerLocal::Contents(class idVec3 const &,class idTraceModel const *,class idMat3 const &,int,class idCollisionModel *,class idVec3 const &,class idMat3 const &)
idCollisionModelLocal *__thiscall idCollisionModelManagerLocal::Contents(
        idCollisionModelManagerLocal *this,
        const idVec3 *start,
        const idTraceModel *trm,
        const idMat3 *trmAxis,
        int contentMask,
        idCollisionModelLocal *model,
        cm_trmVertex_t *modelOrigin,
        const idMat3 *modelAxis)
{
  idCollisionModelLocal *result; // eax
  trace_t results; // [esp+0h] [ebp-74h] BYREF

  result = model;
  if ( model )
    return (idCollisionModelLocal *)idCollisionModelManagerLocal::ContentsTrm(
                                      this,
                                      &results,
                                      start,
                                      trm,
                                      trmAxis,
                                      contentMask,
                                      model,
                                      modelOrigin,
                                      modelAxis);
  return result;
}
