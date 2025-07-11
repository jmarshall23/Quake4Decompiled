
// FUNC: public: virtual class idVec3 __thiscall idAASFileLocal::EdgeCenter(int)const
idVec3 *__thiscall idAASFileLocal::EdgeCenter(idAASFileLocal *this, idVec3 *result, int edgeNum)
{
  aasEdge_s *list; // eax
  idVec3 *v4; // ecx
  aasEdge_s *v5; // edx
  double x; // st7
  idVec3 *v7; // eax
  int v8; // edx
  double v9; // st7
  idVec3 *v10; // ecx
  double v11; // st6
  double z; // st5
  idVec3 *v13; // eax
  float v14; // [esp+8h] [ebp-4h]

  list = this->edges.list;
  v4 = this->vertices.list;
  v5 = &list[edgeNum];
  x = v4[v5->vertexNum[1]].x;
  v7 = &v4[v5->vertexNum[1]];
  v8 = v5->vertexNum[0];
  v9 = x + v4[v8].x;
  v10 = &v4[v8];
  v11 = v7->y + v10->y;
  z = v7->z;
  v13 = result;
  v14 = z + v10->z;
  result->x = v9 * 0.5;
  result->y = v11 * 0.5;
  result->z = v14 * 0.5;
  return v13;
}

// FUNC: public: virtual class idVec3 __thiscall idAASFileLocal::FaceCenter(int)const
idVec3 *__thiscall idAASFileLocal::FaceCenter(idAASFileLocal *this, idVec3 *result, int faceNum)
{
  double x; // st7
  idAASFileLocal *v4; // eax
  aasFace_s *v5; // edx
  int numEdges; // ecx
  int v7; // edi
  aasEdge_s *list; // ebx
  idVec3 *v9; // ebp
  unsigned int v10; // ecx
  int v11; // esi
  unsigned int v12; // edi
  float *p_x; // eax
  double v14; // st7
  double v15; // st6
  float *v16; // eax
  double v17; // st7
  double v18; // st6
  float *v19; // eax
  float *v20; // eax
  aasEdge_s *v21; // ebx
  idVec3 *v22; // ebp
  int *v23; // esi
  int v24; // edi
  float *v25; // eax
  double v26; // st6
  idVec3 *v27; // eax
  idAASFileLocal *v28; // [esp+4h] [ebp-14h]
  int i; // [esp+8h] [ebp-10h]
  idVec3 center; // [esp+Ch] [ebp-Ch]
  float centera; // [esp+Ch] [ebp-Ch]
  float center_8; // [esp+14h] [ebp-4h]
  float faceNuma; // [esp+20h] [ebp+8h]

  x = vec3_origin.x;
  center.z = vec3_origin.z;
  center.x = vec3_origin.x;
  v4 = this;
  v5 = &this->faces.list[faceNum];
  center.y = vec3_origin.y;
  numEdges = v5->numEdges;
  v28 = v4;
  if ( numEdges > 0 )
  {
    v7 = 0;
    if ( numEdges >= 4 )
    {
      list = v4->edges.list;
      v9 = v4->vertices.list;
      v10 = ((unsigned int)(numEdges - 4) >> 2) + 1;
      v11 = (int)&v4->edgeIndex.list[v5->firstEdge + 2];
      i = 4 * v10;
      do
      {
        v12 = *(_DWORD *)(v11 - 4);
        p_x = &v9[list[abs32(*(_DWORD *)(v11 - 8))].vertexNum[*(_DWORD *)(v11 - 8) >> 31]].x;
        v11 += 16;
        v14 = x + *p_x;
        v15 = center.y + p_x[1];
        center_8 = center.z + p_x[2];
        v16 = &v9[list[abs32(v12)].vertexNum[v12 >> 31]].x;
        centera = v14 + *v16;
        v17 = v15 + v16[1];
        v18 = center_8 + v16[2];
        v19 = &v9[list[abs32(*(_DWORD *)(v11 - 16))].vertexNum[*(_DWORD *)(v11 - 16) >> 31]].x;
        center.x = centera + *v19;
        center.y = v17 + v19[1];
        center.z = v18 + v19[2];
        --v10;
        v20 = &v9[list[abs32(*(_DWORD *)(v11 - 12))].vertexNum[*(_DWORD *)(v11 - 12) >> 31]].x;
        x = center.x + *v20;
        center.y = center.y + v20[1];
        center.z = center.z + v20[2];
      }
      while ( v10 );
      v4 = v28;
      numEdges = v5->numEdges;
      v7 = i;
    }
    if ( v7 < numEdges )
    {
      v21 = v4->edges.list;
      v22 = v4->vertices.list;
      v23 = &v4->edgeIndex.list[v7 + v5->firstEdge];
      v24 = numEdges - v7;
      do
      {
        v25 = &v22[v21[abs32(*v23)].vertexNum[(unsigned int)*v23 >> 31]].x;
        ++v23;
        --v24;
        x = x + *v25;
        center.y = center.y + v25[1];
        center.z = center.z + v25[2];
      }
      while ( v24 );
    }
    v26 = 1.0 / (double)v5->numEdges;
    faceNuma = v26;
    center.x = v26 * x;
    center.y = center.y * faceNuma;
    center.z = center.z * faceNuma;
  }
  v27 = result;
  *result = center;
  return v27;
}

// FUNC: public: virtual class idVec3 __thiscall idAASFileLocal::AreaCenter(int)const
idVec3 *__thiscall idAASFileLocal::AreaCenter(idAASFileLocal *this, idVec3 *result, int areaNum)
{
  aasArea_s *v4; // ebx
  int v5; // edi
  __int64 v6; // rax
  idVec3 *v7; // eax
  double v8; // st7
  idVec3 *v9; // eax
  idVec3 center; // [esp+8h] [ebp-18h]
  char v11[12]; // [esp+14h] [ebp-Ch] BYREF

  center = vec3_origin;
  v4 = &this->areas.list[areaNum];
  if ( v4->numFaces > 0 )
  {
    v5 = 0;
    do
    {
      v6 = this->faceIndex.list[v5 + v4->firstFace];
      v7 = this->FaceCenter(this, v11, (HIDWORD(v6) ^ v6) - HIDWORD(v6));
      ++v5;
      center.x = center.x + v7->x;
      center.y = center.y + v7->y;
      center.z = center.z + v7->z;
    }
    while ( v5 < v4->numFaces );
    v8 = 1.0 / (double)v4->numFaces;
    center.x = center.x * v8;
    center.y = center.y * v8;
    center.z = center.z * v8;
  }
  v9 = result;
  *result = center;
  return v9;
}

// FUNC: private: class idVec3 __thiscall idAASFileLocal::AreaReachableGoal(int)const
idVec3 *__thiscall idAASFileLocal::AreaReachableGoal(idAASFileLocal *this, idVec3 *result, int areaNum)
{
  int v4; // ebx
  aasArea_s *v6; // edi
  unsigned __int16 flags; // ax
  int i; // ebx
  int v9; // edi
  __int64 v10; // rax
  int v11; // eax
  idVec3 *v12; // eax
  idAASFileLocal_vtbl *v13; // eax
  double v14; // st7
  idVec3 *v15; // eax
  int j; // ebx
  int v17; // edi
  double y; // st7
  double z; // st7
  float v20; // [esp+10h] [ebp-68h]
  float v21; // [esp+14h] [ebp-64h]
  float v22; // [esp+14h] [ebp-64h]
  float v23; // [esp+18h] [ebp-60h]
  idVec3 center; // [esp+1Ch] [ebp-5Ch] BYREF
  idVec3 testPoint; // [esp+28h] [ebp-50h] BYREF
  idVec3 end; // [esp+34h] [ebp-44h] BYREF
  aasTrace_s trace; // [esp+40h] [ebp-38h] BYREF
  int areaNuma; // [esp+80h] [ebp+8h]
  int areaNumb; // [esp+80h] [ebp+8h]
  int areaNumc; // [esp+80h] [ebp+8h]

  v4 = 0;
  v6 = &this->areas.list[areaNum];
  trace.areas = 0;
  trace.points = 0;
  memset(&trace, 0, 16);
  flags = v6->flags;
  if ( (flags & 1) == 0 )
  {
    memset(&center, 0, sizeof(center));
    for ( areaNuma = 0; areaNuma < 2; ++areaNuma )
    {
      for ( i = 0; i < 2; ++i )
      {
        v9 = 0;
        do
        {
          v21 = (float)(areaNuma != 0 ? 0x20000 : -131072);
          testPoint.x = v21;
          v20 = (float)(i != 0 ? 0x20000 : -131072);
          testPoint.y = v20;
          testPoint.z = (float)(v9 != 0 ? 0x20000 : -131072);
          this->PushPointIntoAreaNum(this, areaNum, &testPoint);
          ++v9;
          center.x = testPoint.x + center.x;
          center.y = testPoint.y + center.y;
          center.z = testPoint.z + center.z;
        }
        while ( v9 < 2 );
      }
    }
LABEL_23:
    v15 = result;
    center.x = center.x * 0.125;
    y = center.y;
    result->x = center.x;
    center.y = y * 0.125;
    z = center.z;
    result->y = center.y;
    center.z = z * 0.125;
    result->z = center.z;
    return v15;
  }
  if ( (flags & 0xC0) != 0 && (flags & 0x10) == 0 )
  {
    center = vec3_origin;
    areaNumb = 0;
    if ( v6->numFaces > 0 )
    {
      do
      {
        v10 = this->faceIndex.list[v4 + v6->firstFace];
        v11 = (HIDWORD(v10) ^ v10) - HIDWORD(v10);
        if ( (this->faces.list[v11].flags & 4) != 0 )
        {
          v12 = this->FaceCenter(this, &testPoint, v11);
          ++areaNumb;
          center.x = center.x + v12->x;
          center.y = center.y + v12->y;
          center.z = center.z + v12->z;
        }
        ++v4;
      }
      while ( v4 < v6->numFaces );
      if ( areaNumb > 0 )
      {
        v13 = this->__vftable;
        v14 = 1.0 / (double)areaNumb;
        center.x = center.x * v14;
        end.x = center.x;
        center.y = center.y * v14;
        end.y = center.y;
        center.z = v14 * center.z + 1.0;
        end.z = center.z - 1024.0;
        v13->Trace(this, &trace, &center, &end);
        v15 = result;
        *result = trace.endpos;
        return v15;
      }
    }
    memset(&center, 0, sizeof(center));
    for ( areaNumc = 0; areaNumc < 2; ++areaNumc )
    {
      for ( j = 0; j < 2; ++j )
      {
        v17 = 0;
        do
        {
          v22 = (float)(areaNumc != 0 ? 0x20000 : -131072);
          testPoint.x = v22;
          v23 = (float)(j != 0 ? 0x20000 : -131072);
          testPoint.y = v23;
          testPoint.z = (float)(v17 != 0 ? 0x20000 : -131072);
          this->PushPointIntoAreaNum(this, areaNum, &testPoint);
          ++v17;
          center.x = testPoint.x + center.x;
          center.y = testPoint.y + center.y;
          center.z = testPoint.z + center.z;
        }
        while ( v17 < 2 );
      }
    }
    goto LABEL_23;
  }
  this->AreaCenter(this, result, areaNum);
  return result;
}

// FUNC: public: virtual class idBounds __thiscall idAASFileLocal::EdgeBounds(int)const
idBounds *__thiscall idAASFileLocal::EdgeBounds(idAASFileLocal *this, idBounds *result, int edgeNum)
{
  aasEdge_s *list; // edx
  idVec3 *v4; // ecx
  aasEdge_s *v5; // edx
  float *p_x; // eax
  int v7; // edx
  float v8; // esi
  double v9; // st7
  idVec3 *v10; // eax
  idBounds *v11; // eax
  float bounds; // [esp+4h] [ebp-18h]
  float bounds_4; // [esp+8h] [ebp-14h]
  float bounds_12; // [esp+10h] [ebp-Ch]
  float bounds_20; // [esp+18h] [ebp-4h]
  float edgeNuma; // [esp+24h] [ebp+8h]

  list = this->edges.list;
  v4 = this->vertices.list;
  v5 = &list[abs32(edgeNum)];
  p_x = &v4[v5->vertexNum[0]].x;
  v7 = v5->vertexNum[1];
  v8 = p_x[1];
  v9 = *p_x + v4[v7].x;
  bounds_20 = p_x[2];
  v10 = &v4[v7];
  bounds = v9;
  bounds_4 = v8 + v10->y;
  edgeNuma = bounds_20 + v10->z;
  v11 = result;
  bounds_12 = v9;
  result->b[0].x = bounds;
  result->b[0].y = bounds_4;
  result->b[0].z = edgeNuma;
  result->b[1].x = bounds_12;
  result->b[1].y = bounds_4;
  result->b[1].z = edgeNuma;
  return v11;
}

// FUNC: public: virtual class idBounds __thiscall idAASFileLocal::FaceBounds(int)const
idBounds *__thiscall idAASFileLocal::FaceBounds(idAASFileLocal *this, idBounds *result, int faceNum)
{
  double v3; // st7
  aasFace_s *v4; // edx
  int numEdges; // eax
  int v6; // ebp
  aasEdge_s *list; // ebx
  idVec3 *v8; // ebp
  int *v9; // edi
  float *p_x; // edx
  float *v11; // edx
  float *v12; // edx
  float *v13; // edx
  aasEdge_s *v14; // edi
  idVec3 *v15; // ebx
  int *v16; // esi
  int v17; // ebp
  float *v18; // ecx
  idBounds *v19; // eax
  int i; // [esp+0h] [ebp-24h]
  const aasFace_s *face; // [esp+4h] [ebp-20h]
  idBounds bounds; // [esp+Ch] [ebp-18h]
  int faceNuma; // [esp+2Ch] [ebp+8h]

  v3 = -1.0e30;
  bounds.b[1].z = -1.0e30;
  v4 = &this->faces.list[faceNum];
  bounds.b[1].y = bounds.b[1].z;
  bounds.b[1].x = bounds.b[1].z;
  bounds.b[0].z = idMath::INFINITY;
  bounds.b[0].y = idMath::INFINITY;
  bounds.b[0].x = idMath::INFINITY;
  numEdges = v4->numEdges;
  v6 = 0;
  face = v4;
  if ( numEdges >= 4 )
  {
    list = this->edges.list;
    v8 = this->vertices.list;
    faceNuma = ((unsigned int)(numEdges - 4) >> 2) + 1;
    v9 = &this->edgeIndex.list[v4->firstEdge + 2];
    i = 4 * faceNuma;
    do
    {
      p_x = &v8[list[abs32(*(v9 - 2))].vertexNum[(unsigned int)*(v9 - 2) >> 31]].x;
      if ( *p_x < (double)bounds.b[0].x )
        bounds.b[0].x = *p_x;
      if ( *p_x > (double)bounds.b[1].x )
        bounds.b[1].x = *p_x;
      if ( p_x[1] < (double)bounds.b[0].y )
        bounds.b[0].y = p_x[1];
      if ( p_x[1] > (double)bounds.b[1].y )
        bounds.b[1].y = p_x[1];
      if ( p_x[2] < (double)bounds.b[0].z )
        bounds.b[0].z = p_x[2];
      if ( v3 < p_x[2] )
        v3 = p_x[2];
      v11 = &v8[list[abs32(*(v9 - 1))].vertexNum[(unsigned int)*(v9 - 1) >> 31]].x;
      if ( *v11 < (double)bounds.b[0].x )
        bounds.b[0].x = *v11;
      if ( *v11 > (double)bounds.b[1].x )
        bounds.b[1].x = *v11;
      if ( v11[1] < (double)bounds.b[0].y )
        bounds.b[0].y = v11[1];
      if ( v11[1] > (double)bounds.b[1].y )
        bounds.b[1].y = v11[1];
      if ( v11[2] < (double)bounds.b[0].z )
        bounds.b[0].z = v11[2];
      if ( v3 < v11[2] )
        v3 = v11[2];
      v12 = &v8[list[abs32(*v9)].vertexNum[(unsigned int)*v9 >> 31]].x;
      if ( *v12 < (double)bounds.b[0].x )
        bounds.b[0].x = *v12;
      if ( *v12 > (double)bounds.b[1].x )
        bounds.b[1].x = *v12;
      if ( v12[1] < (double)bounds.b[0].y )
        bounds.b[0].y = v12[1];
      if ( v12[1] > (double)bounds.b[1].y )
        bounds.b[1].y = v12[1];
      if ( v12[2] < (double)bounds.b[0].z )
        bounds.b[0].z = v12[2];
      if ( v3 < v12[2] )
        v3 = v12[2];
      v13 = &v8[list[abs32(v9[1])].vertexNum[(unsigned int)v9[1] >> 31]].x;
      if ( *v13 < (double)bounds.b[0].x )
        bounds.b[0].x = *v13;
      if ( *v13 > (double)bounds.b[1].x )
        bounds.b[1].x = *v13;
      if ( v13[1] < (double)bounds.b[0].y )
        bounds.b[0].y = v13[1];
      if ( v13[1] > (double)bounds.b[1].y )
        bounds.b[1].y = v13[1];
      if ( v13[2] < (double)bounds.b[0].z )
        bounds.b[0].z = v13[2];
      if ( v3 < v13[2] )
        v3 = v13[2];
      v9 += 4;
      --faceNuma;
    }
    while ( faceNuma );
    v6 = i;
    bounds.b[1].z = v3;
    v4 = (aasFace_s *)face;
  }
  if ( v6 < numEdges )
  {
    v14 = this->edges.list;
    v15 = this->vertices.list;
    v16 = &this->edgeIndex.list[v6 + v4->firstEdge];
    v17 = numEdges - v6;
    do
    {
      v18 = &v15[v14[abs32(*v16)].vertexNum[(unsigned int)*v16 >> 31]].x;
      if ( *v18 < (double)bounds.b[0].x )
        bounds.b[0].x = *v18;
      if ( *v18 > (double)bounds.b[1].x )
        bounds.b[1].x = *v18;
      if ( v18[1] < (double)bounds.b[0].y )
        bounds.b[0].y = v18[1];
      if ( v18[1] > (double)bounds.b[1].y )
        bounds.b[1].y = v18[1];
      if ( v18[2] < (double)bounds.b[0].z )
        bounds.b[0].z = v18[2];
      if ( v3 < v18[2] )
        v3 = v18[2];
      ++v16;
      --v17;
    }
    while ( v17 );
    bounds.b[1].z = v3;
  }
  v19 = result;
  *result = bounds;
  return v19;
}

// FUNC: public: virtual int __thiscall idAASFileLocal::PointAreaNum(class idVec3 const &)const
int __thiscall idAASFileLocal::PointAreaNum(idAASFileLocal *this, const idVec3 *origin)
{
  aasNode_s *list; // esi
  idPlane *v4; // edi
  int v5; // eax
  aasNode_s *v6; // ecx
  float *p_a; // eax

  if ( this->nodes.num < 2 )
    return 0;
  list = this->nodes.list;
  v4 = this->planeList.list;
  v5 = 1;
  while ( 1 )
  {
    v6 = &list[v5];
    p_a = &v4[v6->planeNum].a;
    v5 = p_a[1] * origin->y + p_a[2] * origin->z + *p_a * origin->x + p_a[3] >= 0.0 ? v6->children[0] : v6->children[1];
    if ( v5 < 0 )
      break;
    if ( !v5 )
      return 0;
  }
  return -v5;
}

// FUNC: private: int __thiscall idAASFileLocal::AreaContentsTravelFlags(int)const
int __thiscall idAASFileLocal::AreaContentsTravelFlags(idAASFileLocal *this, int areaNum)
{
  return (this->areas.list[areaNum].contents & 2) != 0 ? 0x200000 : 0x400000;
}

// FUNC: private: int __thiscall idAASFileLocal::MaxTreeDepth(void)const
int __thiscall idAASFileLocal::MaxTreeDepth(idAASFileLocal *this)
{
  aasNode_s *list; // esi
  int maxDepth; // [esp+8h] [ebp-8h] BYREF
  int depth; // [esp+Ch] [ebp-4h] BYREF

  list = this->nodes.list;
  depth = 1;
  maxDepth = 1;
  idAASFileLocal::MaxTreeDepth_r(this, list[1].children[0], &depth, &maxDepth);
  idAASFileLocal::MaxTreeDepth_r(this, list[1].children[1], &depth, &maxDepth);
  return maxDepth;
}

// FUNC: public: virtual class idBounds __thiscall idAASFileLocal::AreaBounds(int)const
idBounds *__thiscall idAASFileLocal::AreaBounds(idAASFileLocal *this, idBounds *result, int areaNum)
{
  aasArea_s *list; // ecx
  bool v6; // zf
  aasArea_s *v7; // esi
  int i; // ebx
  int j; // esi
  int k; // ebx
  __int64 v11; // rax
  float *v12; // ecx
  idBounds *v13; // eax
  float v14; // [esp+8h] [ebp-3Ch]
  float v15; // [esp+Ch] [ebp-38h]
  idVec3 testPoint; // [esp+14h] [ebp-30h] BYREF
  idBounds bounds; // [esp+2Ch] [ebp-18h] BYREF
  int areaNuma; // [esp+4Ch] [ebp+8h]

  bounds.b[1].z = -1.0e30;
  bounds.b[1].y = bounds.b[1].z;
  bounds.b[1].x = bounds.b[1].z;
  list = this->areas.list;
  v6 = (list[areaNum].flags & 1) == 0;
  v7 = &list[areaNum];
  bounds.b[0].z = idMath::INFINITY;
  bounds.b[0].y = idMath::INFINITY;
  bounds.b[0].x = idMath::INFINITY;
  if ( v6 )
  {
    memset(&bounds, 0, sizeof(bounds));
    for ( areaNuma = 0; areaNuma < 2; ++areaNuma )
    {
      for ( i = 0; i < 2; ++i )
      {
        for ( j = 0; j < 2; ++j )
        {
          v15 = (float)(areaNuma != 0 ? 0x20000 : -131072);
          testPoint.x = v15;
          v14 = (float)(i != 0 ? 0x20000 : -131072);
          testPoint.y = v14;
          testPoint.z = (float)(j != 0 ? 0x20000 : -131072);
          this->PushPointIntoAreaNum(this, areaNum, &testPoint);
          if ( testPoint.x < (double)bounds.b[0].x )
            bounds.b[0].x = testPoint.x;
          if ( testPoint.x > (double)bounds.b[1].x )
            bounds.b[1].x = testPoint.x;
          if ( testPoint.y < (double)bounds.b[0].y )
            bounds.b[0].y = testPoint.y;
          if ( testPoint.y > (double)bounds.b[1].y )
            bounds.b[1].y = testPoint.y;
          if ( testPoint.z < (double)bounds.b[0].z )
            bounds.b[0].z = testPoint.z;
          if ( testPoint.z > (double)bounds.b[1].z )
            bounds.b[1].z = testPoint.z;
        }
      }
    }
  }
  else
  {
    for ( k = 0; k < v7->numFaces; ++k )
    {
      v11 = this->faceIndex.list[k + v7->firstFace];
      v12 = (float *)this->FaceBounds(this, &testPoint, (HIDWORD(v11) ^ v11) - HIDWORD(v11));
      if ( *v12 < (double)bounds.b[0].x )
        bounds.b[0].x = *v12;
      if ( v12[1] < (double)bounds.b[0].y )
        bounds.b[0].y = v12[1];
      if ( v12[2] < (double)bounds.b[0].z )
        bounds.b[0].z = v12[2];
      if ( v12[3] > (double)bounds.b[1].x )
        bounds.b[1].x = v12[3];
      if ( v12[4] > (double)bounds.b[1].y )
        bounds.b[1].y = v12[4];
      if ( v12[5] > (double)bounds.b[1].z )
        bounds.b[1].z = v12[5];
    }
  }
  v13 = result;
  *result = bounds;
  return v13;
}
