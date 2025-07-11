
// FUNC: private: void __thiscall idCollisionModelManagerLocal::TraceTrmThroughNode(struct cm_traceWork_t *,struct cm_node_t *)
void __thiscall idCollisionModelManagerLocal::TraceTrmThroughNode(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_node_t *node)
{
  cm_brushRef_t *brushes; // esi
  cm_polygonRef_t *i; // esi
  cm_polygonRef_t *j; // esi
  cm_polygonRef_t *k; // esi

  if ( tw->positionTest )
  {
    if ( tw->trace.fraction != 0.0 )
    {
      brushes = node->brushes;
      if ( brushes )
      {
        while ( !idCollisionModelManagerLocal::TestTrmVertsInBrush(this, tw, brushes->b) )
        {
          brushes = brushes->next;
          if ( !brushes )
            goto LABEL_6;
        }
      }
      else
      {
LABEL_6:
        if ( !tw->pointTrace )
        {
          for ( i = node->polygons; i; i = i->next )
          {
            if ( idCollisionModelManagerLocal::TestTrmInPolygon(this, tw, i->p) )
              break;
          }
        }
      }
    }
  }
  else if ( tw->rotation )
  {
    for ( j = node->polygons; j; j = j->next )
    {
      if ( idCollisionModelManagerLocal::RotateTrmThroughPolygon(this, tw, j->p) )
        break;
    }
  }
  else
  {
    for ( k = node->polygons; k; k = k->next )
    {
      if ( idCollisionModelManagerLocal::TranslateTrmThroughPolygon(this, tw, k->p) )
        break;
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::TraceThroughAxialBSPTree_r(struct cm_traceWork_t *,struct cm_node_t *,float,float,class idVec3 &,class idVec3 &)
void __thiscall idCollisionModelManagerLocal::TraceThroughAxialBSPTree_r(
        idCollisionModelManagerLocal *this,
        cm_traceWork_t *tw,
        cm_node_t *node,
        float p1f,
        float p2f,
        idVec3 *p1,
        idVec3 *p2)
{
  int planeType; // eax
  double v11; // st7
  double v13; // st7
  unsigned __int8 v14; // c0
  unsigned __int8 v15; // c2
  int v16; // ebp
  double v17; // st7
  double v18; // st6
  double v19; // st7
  double v20; // st7
  float p1fa; // [esp+0h] [ebp-30h]
  float v22; // [esp+4h] [ebp-2Ch]
  idVec3 mid; // [esp+24h] [ebp-Ch] BYREF
  float nodea; // [esp+38h] [ebp+8h]
  float nodeb; // [esp+38h] [ebp+8h]
  float p1a; // [esp+44h] [ebp+14h]
  float offset; // [esp+48h] [ebp+18h]
  float offseta; // [esp+48h] [ebp+18h]

  if ( !node || tw->quickExit || tw->trace.fraction <= (double)p1f )
    return;
  if ( node->polygons )
    goto LABEL_7;
  if ( !tw->positionTest )
    goto LABEL_10;
  if ( node->brushes )
LABEL_7:
    idCollisionModelManagerLocal::TraceTrmThroughNode(this, tw, node);
  if ( tw->positionTest && tw->trace.fraction == 0.0 )
    return;
LABEL_10:
  planeType = node->planeType;
  if ( node->planeType == -1 )
    return;
  nodea = *(&p1->x + planeType) - node->planeDist;
  offset = *(&p2->x + planeType) - node->planeDist;
  p1a = *(&tw->trmExtents.x + planeType);
  if ( nodea >= (double)p1a && offset >= (double)p1a )
  {
    idCollisionModelManagerLocal::TraceThroughAxialBSPTree_r(this, tw, node->children[0], p1f, p2f, p1, p2);
    return;
  }
  v11 = -p1a;
  if ( nodea < v11 && offset < v11 )
  {
    idCollisionModelManagerLocal::TraceThroughAxialBSPTree_r(this, tw, node->children[1], p1f, p2f, p1, p2);
    return;
  }
  v13 = nodea;
  if ( v14 | v15 )
  {
    v16 = 1;
    v17 = 1.0 / (v13 - offset);
    offseta = (p1a + nodea) * v17;
    v18 = nodea - p1a;
  }
  else
  {
    v16 = 0;
    if ( v13 <= offset )
    {
      offseta = 0.0;
      goto LABEL_25;
    }
    v17 = 1.0 / (nodea - offset);
    offseta = (nodea - p1a) * v17;
    v18 = p1a + nodea;
  }
  v19 = v17 * v18;
  if ( v19 >= 0.0 )
  {
    if ( v19 <= 1.0 )
      goto LABEL_26;
LABEL_25:
    v19 = 1.0;
    goto LABEL_26;
  }
  v19 = 0.0;
LABEL_26:
  mid.x = (p2->x - p1->x) * v19 + p1->x;
  mid.y = (p2->y - p1->y) * v19 + p1->y;
  mid.z = (p2->z - p1->z) * v19 + p1->z;
  nodeb = p2f - p1f;
  v22 = nodeb * v19 + p1f;
  idCollisionModelManagerLocal::TraceThroughAxialBSPTree_r(this, tw, node->children[v16], p1f, v22, p1, &mid);
  v20 = offseta;
  if ( offseta >= 0.0 )
  {
    if ( v20 > 1.0 )
      v20 = 1.0;
  }
  else
  {
    v20 = 0.0;
  }
  mid.x = (p2->x - p1->x) * v20 + p1->x;
  mid.y = (p2->y - p1->y) * v20 + p1->y;
  mid.z = (p2->z - p1->z) * v20 + p1->z;
  p1fa = nodeb * v20 + p1f;
  idCollisionModelManagerLocal::TraceThroughAxialBSPTree_r(this, tw, node->children[v16 ^ 1], p1fa, p2f, &mid, p2);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::TraceThroughModel(struct cm_traceWork_t *)
void __thiscall idCollisionModelManagerLocal::TraceThroughModel(idCollisionModelManagerLocal *this, cm_traceWork_t *tw)
{
  double v3; // st7
  float v4; // edx
  int v5; // eax
  int v6; // ebx
  int v7; // edi
  float v8; // edx
  float v9; // ecx
  float x; // edx
  float v11; // ecx
  float v12; // edx
  double v13; // st7
  double v14; // st6
  double v15; // st5
  idCollisionModelLocal *model; // eax
  float y; // eax
  float z; // ecx
  float v19; // [esp+8h] [ebp-7Ch]
  idVec3 start; // [esp+10h] [ebp-74h] BYREF
  idVec3 end; // [esp+1Ch] [ebp-68h] BYREF
  float v22; // [esp+28h] [ebp-5Ch]
  float v23; // [esp+2Ch] [ebp-58h]
  float v24; // [esp+3Ch] [ebp-48h]
  idRotation rot; // [esp+40h] [ebp-44h] BYREF

  if ( !tw->rotation )
  {
    idCollisionModelManagerLocal::TraceThroughAxialBSPTree_r(this, tw, tw->model->node, 0.0, 1.0, &tw->start, &tw->end);
    return;
  }
  v3 = idMath::M_DEG2RAD * tw->angle * tw->radius;
  if ( v3 <= 64.0 )
  {
    y = tw->start.y;
    z = tw->start.z;
    start.x = tw->start.x;
    start.y = y;
    start.z = z;
    goto LABEL_10;
  }
  v4 = tw->start.y;
  start.x = tw->start.x;
  start.y = v4;
  start.z = tw->start.z;
  v5 = 0;
  v6 = (int)(0.015625 * v3);
  if ( v6 <= 0 )
  {
LABEL_10:
    idCollisionModelManagerLocal::TraceThroughAxialBSPTree_r(this, tw, tw->model->node, 0.0, 1.0, &start, &tw->end);
    return;
  }
  v19 = (float)(int)(0.015625 * v3);
  while ( 1 )
  {
    v7 = v5 + 1;
    v8 = tw->origin.y;
    rot.origin.x = tw->origin.x;
    v9 = tw->origin.z;
    rot.origin.y = v8;
    x = tw->axis.x;
    rot.origin.z = v9;
    v11 = tw->axis.y;
    rot.vec.x = x;
    v12 = tw->axis.z;
    rot.vec.y = v11;
    rot.vec.z = v12;
    rot.axisValid = 0;
    rot.angle = (double)(v5 + 1) / v19 * tw->angle;
    idRotation::ToMat3(&rot);
    v13 = start.x - rot.origin.x;
    v14 = start.y - rot.origin.y;
    v15 = start.z - rot.origin.z;
    v22 = rot.axis.mat[2].x * v15 + rot.axis.mat[1].x * v14 + rot.axis.mat[0].x * v13;
    v23 = rot.axis.mat[2].y * v15 + rot.axis.mat[1].y * v14 + rot.axis.mat[0].y * v13;
    v24 = rot.axis.mat[2].z * v15 + rot.axis.mat[1].z * v14 + rot.axis.mat[0].z * v13 + rot.origin.z;
    end.z = v24;
    model = tw->model;
    end.x = v22 + rot.origin.x;
    end.y = v23 + rot.origin.y;
    idCollisionModelManagerLocal::TraceThroughAxialBSPTree_r(this, tw, model->node, 0.0, 1.0, &start, &end);
    if ( tw->trace.fraction < 1.0 )
      break;
    start = end;
    v5 = v7;
    if ( v7 >= v6 )
      goto LABEL_10;
  }
}
