
// FUNC: R_MirrorPoint
void __usercall R_MirrorPoint(orientation_t *surface@<eax>, orientation_t *camera@<ecx>, idVec3 *out@<edx>, idVec3 in)
{
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st2
  double v8; // st4
  double v9; // st3
  double v10; // st2
  double v11; // rt1
  double v12; // st6
  double v13; // rt2
  double v14; // st6
  float transformed; // [esp+0h] [ebp-18h]
  float transformeda; // [esp+0h] [ebp-18h]
  float transformed_4; // [esp+4h] [ebp-14h]
  float transformed_4a; // [esp+4h] [ebp-14h]
  float transformed_8; // [esp+8h] [ebp-10h]
  float transformed_8a; // [esp+8h] [ebp-10h]
  float v21; // [esp+10h] [ebp-8h]
  float v22; // [esp+10h] [ebp-8h]
  float v23; // [esp+10h] [ebp-8h]
  float v24; // [esp+14h] [ebp-4h]
  float v25; // [esp+14h] [ebp-4h]
  float v26; // [esp+14h] [ebp-4h]
  float in_8; // [esp+24h] [ebp+Ch]

  v4 = in.x - surface->origin.x;
  v5 = in.y - surface->origin.y;
  v6 = in.z - surface->origin.z;
  v7 = v6 * surface->axis.mat[0].z + v5 * surface->axis.mat[0].y + v4 * surface->axis.mat[0].x;
  v21 = camera->axis.mat[0].y * v7;
  v24 = camera->axis.mat[0].z * v7;
  transformed = camera->axis.mat[0].x * v7 + vec3_origin.x;
  v8 = v21 + vec3_origin.y;
  v9 = v24 + vec3_origin.z;
  v10 = v6 * surface->axis.mat[1].z + v5 * surface->axis.mat[1].y + v4 * surface->axis.mat[1].x;
  v22 = camera->axis.mat[1].y * v10;
  v25 = camera->axis.mat[1].z * v10;
  transformeda = camera->axis.mat[1].x * v10 + transformed;
  transformed_4 = v22 + v8;
  transformed_8 = v25 + v9;
  v11 = v6 * surface->axis.mat[2].z + v5 * surface->axis.mat[2].y;
  v12 = v4 * surface->axis.mat[2].x;
  v23 = camera->axis.mat[2].y * (v11 + v12);
  v26 = camera->axis.mat[2].z * (v11 + v12);
  transformed_4a = v23 + transformed_4;
  transformed_8a = v26 + transformed_8;
  in_8 = transformed_8a + camera->origin.z;
  v13 = transformed_4a + camera->origin.y;
  v14 = camera->axis.mat[2].x * (v11 + v12) + transformeda + camera->origin.x;
  out->z = in_8;
  out->x = v14;
  out->y = v13;
}

// FUNC: R_MirrorVector
void __usercall R_MirrorVector(orientation_t *surface@<ecx>, orientation_t *camera@<edx>, idVec3 *out@<eax>, idVec3 in)
{
  idVec3 *v4; // esi
  double v5; // st7
  idVec3 *v6; // edx
  double v7; // st7
  double v8; // st7
  float x; // [esp+0h] [ebp-18h]
  float y; // [esp+4h] [ebp-14h]
  float z; // [esp+8h] [ebp-10h]
  float v12; // [esp+10h] [ebp-8h]
  float v13; // [esp+10h] [ebp-8h]
  float v14; // [esp+10h] [ebp-8h]
  float v15; // [esp+14h] [ebp-4h]
  float v16; // [esp+14h] [ebp-4h]
  float v17; // [esp+14h] [ebp-4h]

  *out = vec3_origin;
  x = camera->axis.mat[0].x;
  y = camera->axis.mat[0].y;
  z = camera->axis.mat[0].z;
  v4 = &camera->axis.mat[1];
  v5 = in.y * surface->axis.mat[0].y + in.z * surface->axis.mat[0].z + in.x * surface->axis.mat[0].x;
  v6 = &camera->axis.mat[2];
  v12 = y * v5;
  v15 = z * v5;
  out->x = x * v5 + out->x;
  out->y = v12 + out->y;
  out->z = v15 + out->z;
  v7 = in.y * surface->axis.mat[1].y + in.z * surface->axis.mat[1].z + in.x * surface->axis.mat[1].x;
  v13 = v4->y * v7;
  v16 = v4->z * v7;
  out->x = v4->x * v7 + out->x;
  out->y = v13 + out->y;
  out->z = v16 + out->z;
  v8 = in.y * surface->axis.mat[2].y + in.z * surface->axis.mat[2].z + in.x * surface->axis.mat[2].x;
  v14 = v6->y * v8;
  v17 = v6->z * v8;
  out->x = v6->x * v8 + out->x;
  out->y = v14 + out->y;
  out->z = v17 + out->z;
}

// FUNC: R_PlaneForSurface
void __usercall R_PlaneForSurface(const srfTriangles_s *tri@<eax>, idPlane *plane@<edx>)
{
  rvMesh *primBatchMesh; // ecx
  int *indexes; // esi
  int v4; // ecx
  idDrawVert *verts; // edi
  int v6; // eax
  int v7; // esi
  double v8; // st7
  float *v9; // esi
  double v10; // st7
  float *v11; // ecx
  double v12; // st6
  float *p_x; // eax
  double v14; // st5
  double v15; // st4
  double v16; // st7
  long double v17; // st6
  long double v18; // st7
  long double v19; // st5
  unsigned __int8 v21; // c2
  unsigned __int8 v22; // c3
  float v23; // [esp+8h] [ebp-18h]
  float v24; // [esp+Ch] [ebp-14h]
  float v25; // [esp+14h] [ebp-Ch]
  float v26; // [esp+18h] [ebp-8h]

  primBatchMesh = tri->primBatchMesh;
  if ( primBatchMesh )
  {
    rvMesh::PlaneForSurface(primBatchMesh, plane, tri->silTraceVerts);
    return;
  }
  indexes = tri->indexes;
  v4 = indexes[1];
  verts = tri->verts;
  v6 = *indexes;
  v7 = indexes[2] << 6;
  v8 = *(float *)((char *)&verts->xyz.x + v7);
  v9 = (float *)((char *)&verts->xyz.x + v7);
  v4 <<= 6;
  v10 = v8 - *(float *)((char *)&verts->xyz.x + v4);
  v11 = (float *)((char *)&verts->xyz.x + v4);
  v12 = v9[1] - v11[1];
  p_x = &verts[v6].xyz.x;
  v14 = v9[2] - v11[2];
  v25 = *p_x - *v11;
  v26 = p_x[1] - v11[1];
  v15 = p_x[2] - v11[2];
  v23 = v26 * v14 - v15 * v12;
  plane->a = v23;
  v24 = v10 * v15 - v25 * v14;
  plane->b = v24;
  v16 = v25 * v12 - v10 * v26;
  plane->c = v16;
  v17 = v16 * v16 + v24 * v24 + v23 * v23;
  if ( v17 == 0.0 )
  {
    v18 = 0.0;
  }
  else
  {
    v19 = 1.0 / sqrt(v17);
    plane->a = v23 * v19;
    plane->b = v24 * v19;
    plane->c = v16 * v19;
    v18 = v19 * v17;
  }
  if ( v22 | v21 )
  {
    if ( plane->b == 0.0 )
    {
      if ( plane->c <= 0.0 )
      {
        if ( LODWORD(plane->c) != -1082130432 )
          plane->c = -1.0;
      }
      else if ( LODWORD(plane->c) != 1065353216 )
      {
        plane->c = 1.0;
      }
      goto LABEL_39;
    }
    if ( plane->c == 0.0 )
    {
      if ( plane->b <= 0.0 )
      {
        if ( LODWORD(plane->b) != -1082130432 )
          plane->b = -1.0;
      }
      else if ( LODWORD(plane->b) != 1065353216 )
      {
        plane->b = 1.0;
      }
      goto LABEL_39;
    }
  }
  else if ( plane->b == 0.0 && plane->c == 0.0 )
  {
    if ( plane->a <= 0.0 )
    {
      if ( LODWORD(plane->a) != -1082130432 )
        plane->a = -1.0;
    }
    else if ( LODWORD(plane->a) != 1065353216 )
    {
      plane->a = 1.0;
    }
    goto LABEL_39;
  }
  if ( COERCE_FLOAT(LODWORD(plane->a) & 0x7FFFFFFF) == 1.0 )
  {
    if ( plane->b == 0.0 && plane->c == 0.0 )
      goto LABEL_39;
    plane->c = 0.0;
    goto LABEL_38;
  }
  if ( COERCE_FLOAT(LODWORD(plane->b) & 0x7FFFFFFF) == 1.0 )
  {
    if ( plane->a != 0.0 || plane->c != 0.0 )
    {
      plane->c = 0.0;
      plane->a = 0.0;
    }
    goto LABEL_39;
  }
  if ( COERCE_FLOAT(LODWORD(plane->c) & 0x7FFFFFFF) == 1.0 && (plane->a != 0.0 || plane->b != 0.0) )
  {
    plane->a = 0.0;
LABEL_38:
    plane->b = 0.0;
  }
LABEL_39:
  if ( v18 != 0.0 )
    plane->d = -(*v11 * plane->a + v11[1] * plane->b + v11[2] * plane->c);
}

// FUNC: bool __cdecl R_PreciseCullSurface(struct drawSurf_s const *,class idBounds &)
char __cdecl R_PreciseCullSurface(const drawSurf_s *drawSurf, idBounds *ndcBounds)
{
  int v2; // esi
  const srfTriangles_s *geo; // ebx
  int v4; // edi
  int v5; // ecx
  int v6; // ecx
  const rvSilTraceVertT *silTraceVerts; // eax
  char v9; // al
  int v10; // edx
  bool v11; // c0
  int *indexes; // eax
  idDrawVert *verts; // ecx
  const idVec3 *p_xyz; // esi
  const idVec3 *v15; // edi
  const idVec3 *v16; // ebp
  double v17; // st7
  double v18; // st6
  double v19; // st5
  double v20; // st4
  int v21; // edi
  int j; // esi
  double v23; // st7
  double v24; // st6
  double v25; // st5
  int k; // esi
  int i; // [esp+10h] [ebp-578h]
  int ia; // [esp+10h] [ebp-578h]
  idPlane clip; // [esp+14h] [ebp-574h] BYREF
  idVec3 screen; // [esp+24h] [ebp-564h] BYREF
  float v31; // [esp+30h] [ebp-558h]
  float v32; // [esp+34h] [ebp-554h]
  float v33; // [esp+38h] [ebp-550h]
  float v34; // [esp+3Ch] [ebp-54Ch]
  idVec3 localView; // [esp+40h] [ebp-548h] BYREF
  idPlane plane; // [esp+4Ch] [ebp-53Ch] BYREF
  idPlane eye; // [esp+5Ch] [ebp-52Ch] BYREF
  idFixedWinding w; // [esp+6Ch] [ebp-51Ch] BYREF
  int v39; // [esp+584h] [ebp-4h]

  v2 = 0;
  w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
  w.numPoints = 0;
  w.p = w.data;
  w.allocedSize = 64;
  geo = drawSurf->geo;
  ndcBounds->b[0].z = idMath::INFINITY;
  ndcBounds->b[0].y = idMath::INFINITY;
  ndcBounds->b[0].x = idMath::INFINITY;
  v4 = 0;
  ndcBounds->b[1].z = -1.0e30;
  v39 = 0;
  ndcBounds->b[1].y = -1.0e30;
  i = -1;
  ndcBounds->b[1].x = -1.0e30;
  if ( geo->silTraceVerts )
  {
    if ( geo->numVerts > 0 )
    {
      do
      {
        R_TransformModelToClip(
          (const idVec3 *)&geo->silTraceVerts[v2],
          drawSurf->space->modelViewMatrix,
          tr.viewDef->projectionMatrix,
          &eye,
          &clip);
        v5 = 0;
        if ( clip.a < (double)clip.d )
        {
          if ( -clip.d >= clip.a )
            v5 = 2;
        }
        else
        {
          v5 = 1;
        }
        if ( clip.b < (double)clip.d )
        {
          if ( -clip.d >= clip.b )
            v5 |= 8u;
        }
        else
        {
          v5 |= 4u;
        }
        if ( clip.c < (double)clip.d )
        {
          if ( -clip.d >= clip.c )
            v5 |= 0x20u;
        }
        else
        {
          v5 |= 0x10u;
        }
        i &= v5;
        ++v4;
        ++v2;
      }
      while ( v4 < geo->numVerts );
      goto LABEL_31;
    }
LABEL_32:
    v39 = -1;
    w.p = 0;
    w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    Memory::Free(0);
    return 1;
  }
  if ( geo->numVerts <= 0 )
    goto LABEL_32;
  do
  {
    R_TransformModelToClip(
      (const idVec3 *)((char *)&geo->verts->xyz + v2 * 16),
      drawSurf->space->modelViewMatrix,
      tr.viewDef->projectionMatrix,
      &eye,
      &clip);
    v6 = 0;
    if ( clip.a < (double)clip.d )
    {
      if ( -clip.d >= clip.a )
        v6 = 2;
    }
    else
    {
      v6 = 1;
    }
    if ( clip.b < (double)clip.d )
    {
      if ( -clip.d >= clip.b )
        v6 |= 8u;
    }
    else
    {
      v6 |= 4u;
    }
    if ( clip.c < (double)clip.d )
    {
      if ( -clip.d >= clip.c )
        v6 |= 0x20u;
    }
    else
    {
      v6 |= 0x10u;
    }
    i &= v6;
    ++v4;
    v2 += 4;
  }
  while ( v4 < geo->numVerts );
LABEL_31:
  if ( i )
    goto LABEL_32;
  R_GlobalPointToLocal(drawSurf->space->modelMatrix, &tr.viewDef->renderView.vieworg, &localView);
  silTraceVerts = geo->silTraceVerts;
  if ( silTraceVerts )
  {
    v9 = rvMesh::PreciseCullSurface(
           geo->primBatchMesh,
           ndcBounds,
           silTraceVerts,
           &localView,
           drawSurf->space->modelMatrix);
    w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    w.p = 0;
    v39 = -1;
    if ( v9 || ndcBounds->b[1].x < (double)ndcBounds->b[0].x )
      goto LABEL_66;
LABEL_39:
    Memory::Free(0);
    return 0;
  }
  v10 = 0;
  ia = 0;
  if ( geo->numIndexes > 0 )
  {
    while ( 1 )
    {
      indexes = geo->indexes;
      verts = geo->verts;
      p_xyz = &verts[indexes[v10]].xyz;
      v15 = &verts[indexes[v10 + 1]].xyz;
      v16 = &verts[indexes[v10 + 2]].xyz;
      if ( !tr.guiRecursionLevel )
      {
        v17 = v15->z - p_xyz->z;
        v18 = v15->y - p_xyz->y;
        v19 = v15->x - p_xyz->x;
        v32 = v16->z - p_xyz->z;
        v31 = v16->y - p_xyz->y;
        v20 = v16->x - p_xyz->x;
        v33 = v20 * v18 - v31 * v19;
        v34 = v32 * v19 - v20 * v17;
        if ( (v17 * v31 - v32 * v18) * (p_xyz->x - localView.x)
           + (p_xyz->y - localView.y) * v34
           + (p_xyz->z - localView.z) * v33 >= 0.0 )
          break;
      }
      if ( w.allocedSize >= 3 || w.ReAllocate(&w, 3, 1) )
        w.numPoints = 3;
      R_LocalPointToGlobal(drawSurf->space->modelMatrix, p_xyz, (idVec3 *)w.p);
      R_LocalPointToGlobal(drawSurf->space->modelMatrix, v15, (idVec3 *)&w.p[1]);
      R_LocalPointToGlobal(drawSurf->space->modelMatrix, v16, (idVec3 *)&w.p[2]);
      v21 = 0;
      w.p[2].t = 0.0;
      w.p[2].s = 0.0;
      w.p[1].t = 0.0;
      w.p[1].s = 0.0;
      w.p->t = 0.0;
      w.p->s = 0.0;
      for ( j = 480; j < 544; j += 16 )
      {
        v23 = -*(float *)((char *)&tr.viewDef->renderView.width + j);
        v24 = -*(float *)((char *)&tr.viewDef->renderView.y + j);
        v25 = -*(float *)((char *)&tr.viewDef->renderView.x + j);
        plane.a = -*(float *)((char *)&tr.viewDef->renderView.viewID + j);
        plane.b = v25;
        plane.c = v24;
        plane.d = v23;
        if ( !idWinding::ClipInPlace(&w, &plane, 0.1, 0) )
          break;
      }
      for ( k = 0; k < w.numPoints; ++v21 )
      {
        R_GlobalToNormalizedDeviceCoordinates(
          tr.viewDef->worldSpace.modelViewMatrix,
          tr.viewDef->projectionMatrix,
          (const idVec3 *)&w.p[v21],
          &screen);
        if ( screen.x < (double)ndcBounds->b[0].x )
          ndcBounds->b[0].x = screen.x;
        if ( screen.x > (double)ndcBounds->b[1].x )
          ndcBounds->b[1].x = screen.x;
        if ( screen.y < (double)ndcBounds->b[0].y )
          ndcBounds->b[0].y = screen.y;
        if ( screen.y > (double)ndcBounds->b[1].y )
          ndcBounds->b[1].y = screen.y;
        if ( screen.z < (double)ndcBounds->b[0].z )
          ndcBounds->b[0].z = screen.z;
        if ( screen.z > (double)ndcBounds->b[1].z )
          ndcBounds->b[1].z = screen.z;
        ++k;
      }
      ia += 3;
      if ( ia >= geo->numIndexes )
        goto LABEL_38;
      v10 = ia;
    }
    v39 = -1;
    w.p = 0;
    w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
    goto LABEL_66;
  }
LABEL_38:
  v11 = ndcBounds->b[1].x < (double)ndcBounds->b[0].x;
  w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
  w.p = 0;
  v39 = -1;
  if ( !v11 )
    goto LABEL_39;
LABEL_66:
  Memory::Free(0);
  return 1;
}

// FUNC: R_RemoteRender
void __usercall R_RemoteRender(textureStage_t *stage@<edi>, drawSurf_s *surf)
{
  viewDef_s *v2; // esi
  int height; // eax
  int width; // ebp
  __int16 v5; // cx
  bool v6; // zf

  if ( stage->dynamicFrameCount != tr.frameCount && surf->space->entityDef->parms.remoteRenderView )
  {
    v2 = (viewDef_s *)R_FrameAlloc(636);
    viewDef_s::operator=(tr.viewDef);
    v2->isSubview = 1;
    v2->isMirror = 0;
    renderView_s::operator=(surf->space->entityDef->parms.remoteRenderView);
    v2->renderView.viewID = 0;
    v2->initialViewAreaOrigin.x = v2->renderView.vieworg.x;
    v2->initialViewAreaOrigin.y = v2->renderView.vieworg.y;
    v2->initialViewAreaOrigin.z = v2->renderView.vieworg.z;
    if ( image_downSize.internalVar->integerValue )
    {
      height = stage->height;
      width = stage->width;
      if ( height <= width )
        idRenderSystemLocal::CropRenderSize(
          &tr,
          image_downSizeLimit.internalVar->integerValue,
          image_downSizeLimit.internalVar->integerValue,
          1,
          0);
      else
        idRenderSystemLocal::CropRenderSize(
          &tr,
          width / (height / image_downSizeLimit.internalVar->integerValue),
          image_downSizeLimit.internalVar->integerValue,
          1,
          0);
    }
    else
    {
      idRenderSystemLocal::CropRenderSize(&tr, stage->width, stage->height, 1, 0);
    }
    v2->renderView.x = 0;
    v2->renderView.y = 0;
    v2->renderView.width = 640;
    v2->renderView.height = 480;
    idRenderSystemLocal::RenderViewToViewport(&tr, &v2->renderView, &v2->viewport);
    v5 = v2->viewport.y2 - v2->viewport.y1;
    v2->scissor.x2 = v2->viewport.x2 - v2->viewport.x1;
    v2->scissor.x1 = 0;
    v2->scissor.y1 = 0;
    v2->scissor.y2 = v5;
    v2->superView = tr.viewDef;
    v2->subviewSurface = surf;
    R_RenderView(v2);
    v6 = stage->image == 0;
    stage->dynamicFrameCount = tr.frameCount;
    if ( v6 )
      stage->image = globalImages->GetScratchImage(globalImages);
    idRenderSystemLocal::CaptureRenderToImage(&tr, stage->image->imgName.data);
    idRenderSystemLocal::UnCrop(&tr);
  }
}

// FUNC: void __cdecl R_MirrorRender(struct drawSurf_s *,struct textureStage_t *,class idScreenRect)
void __cdecl R_MirrorRender(drawSurf_s *surf, textureStage_t *stage)
{
  viewDef_s *v2; // esi
  __int16 v3; // dx
  idImage *v4; // eax

  if ( stage->dynamicFrameCount != tr.frameCount )
  {
    v2 = R_MirrorViewBySurface(surf);
    if ( v2 )
    {
      idRenderSystemLocal::CropRenderSize(&tr, stage->width, stage->height, 1, 0);
      v2->renderView.x = 0;
      v2->renderView.y = 0;
      v2->renderView.width = 640;
      v2->renderView.height = 480;
      idRenderSystemLocal::RenderViewToViewport(&tr, &v2->renderView, &v2->viewport);
      v3 = v2->viewport.y2 - v2->viewport.y1;
      v2->scissor.x2 = v2->viewport.x2 - v2->viewport.x1;
      v2->scissor.x1 = 0;
      v2->scissor.y1 = 0;
      v2->scissor.y2 = v3;
      v2->superView = tr.viewDef;
      v2->subviewSurface = surf;
      v2->isMirror = v2->isMirror != tr.viewDef->isMirror;
      R_RenderView(v2);
      stage->dynamicFrameCount = tr.frameCount;
      v4 = globalImages->GetScratchImage(globalImages);
      stage->image = v4;
      idRenderSystemLocal::CaptureRenderToImage(&tr, v4->imgName.data);
      idRenderSystemLocal::UnCrop(&tr);
    }
  }
}

// FUNC: void __cdecl R_ReflectionRender(struct drawSurf_s *,struct textureStage_t *,class idScreenRect)
void __cdecl R_ReflectionRender(drawSurf_s *surf, textureStage_t *stage)
{
  viewDef_s *v2; // esi
  __int16 v3; // dx
  idImage *v4; // eax

  if ( stage->dynamicFrameCount != tr.frameCount )
  {
    v2 = R_MirrorViewBySurface(surf);
    if ( v2 )
    {
      idRenderSystemLocal::CropRenderSize(&tr, stage->width, stage->height, 1, 0);
      v2->renderView.x = 0;
      v2->renderView.y = 0;
      v2->renderView.width = 640;
      v2->renderView.height = 480;
      idRenderSystemLocal::RenderViewToViewport(&tr, &v2->renderView, &v2->viewport);
      v3 = v2->viewport.y2 - v2->viewport.y1;
      v2->scissor.x2 = v2->viewport.x2 - v2->viewport.x1;
      v2->scissor.x1 = 0;
      v2->scissor.y1 = 0;
      v2->scissor.y2 = v3;
      v2->superView = tr.viewDef;
      v2->subviewSurface = surf;
      v2->isMirror = v2->isMirror != tr.viewDef->isMirror;
      R_RenderView(v2);
      stage->dynamicFrameCount = tr.frameCount;
      v4 = globalImages->GetReflectionImage(globalImages);
      idRenderSystemLocal::CaptureRenderToImage(&tr, v4->imgName.data);
      idRenderSystemLocal::UnCrop(&tr);
    }
  }
}

// FUNC: bool __cdecl R_GenerateSurfaceSubview(struct drawSurf_s *)
char __cdecl R_GenerateSurfaceSubview(drawSurf_s *drawSurf)
{
  const idMaterial *material; // ebx
  viewDef_s *viewDef; // eax
  drawSurf_s *subviewSurface; // ecx
  const idMaterial *v4; // edi
  int v5; // ebx
  int v6; // esi
  shaderStage_t *stages; // eax
  dynamicidImage_t dynamic; // ecx
  shaderStage_t *v9; // eax
  int v10; // ecx
  int v11; // ecx
  viewDef_s *v13; // eax
  const idMaterial *shader; // [esp+10h] [ebp-30h]
  idScreenRect scissor; // [esp+18h] [ebp-28h] BYREF
  idBounds ndcBounds; // [esp+28h] [ebp-18h] BYREF

  if ( r_skipSubviews.internalVar->integerValue || R_PreciseCullSurface(drawSurf, &ndcBounds) )
    return 0;
  material = drawSurf->material;
  viewDef = tr.viewDef;
  for ( shader = material; viewDef; viewDef = viewDef->superView )
  {
    subviewSurface = viewDef->subviewSurface;
    if ( subviewSurface )
    {
      if ( subviewSurface->geo == drawSurf->geo && subviewSurface->space->entityDef == drawSurf->space->entityDef )
        return 0;
    }
  }
  scissor.x1 = tr.viewDef->viewport.x1
             - (unsigned __int64)((double)(tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1 + 1)
                                * (ndcBounds.b[0].x + 1.0)
                                * -0.5);
  scissor.y1 = tr.viewDef->viewport.y1
             - (unsigned __int64)((double)(tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1 + 1)
                                * (ndcBounds.b[0].y + 1.0)
                                * -0.5);
  scissor.x2 = tr.viewDef->viewport.x1
             - (unsigned __int64)((double)(tr.viewDef->viewport.x2 - tr.viewDef->viewport.x1 + 1)
                                * (ndcBounds.b[1].x + 1.0)
                                * -0.5);
  scissor.y2 = tr.viewDef->viewport.y1
             - (unsigned __int64)((double)(tr.viewDef->viewport.y2 - tr.viewDef->viewport.y1 + 1)
                                * (ndcBounds.b[1].y + 1.0)
                                * -0.5);
  idScreenRect::Expand(&scissor);
  idScreenRect::Intersect(&scissor, &tr.viewDef->scissor);
  if ( idScreenRect::IsEmpty(&scissor) )
    return 0;
  if ( LODWORD(material->sort) == -1065353216 )
  {
    v13 = R_MirrorViewBySurface(drawSurf);
    if ( v13 )
    {
      v13->scissor = scissor;
      v13->superView = tr.viewDef;
      v13->subviewSurface = drawSurf;
      v13->isMirror = v13->isMirror != tr.viewDef->isMirror;
      R_RenderView(v13);
      return 1;
    }
    return 0;
  }
  v4 = material;
  v5 = 0;
  if ( shader->numStages <= 0 )
    return 1;
  v6 = 0;
  do
  {
    stages = v4->stages;
    dynamic = stages[v6].texture.dynamic;
    v9 = &stages[v6];
    v10 = dynamic - 3;
    if ( v10 )
    {
      v11 = v10 - 1;
      if ( v11 )
      {
        if ( v11 == 2 )
        {
          R_RemoteRender(&v9->texture, drawSurf);
          v4 = shader;
        }
      }
      else
      {
        R_ReflectionRender(drawSurf, &v9->texture);
      }
    }
    else
    {
      R_MirrorRender(drawSurf, &v9->texture);
    }
    ++v5;
    ++v6;
  }
  while ( v5 < v4->numStages );
  return 1;
}

// FUNC: bool __cdecl R_GenerateSubViews(void)
char __cdecl R_GenerateSubViews()
{
  viewDef_s *viewDef; // eax
  int v2; // esi
  char i; // bl
  drawSurf_s *v4; // ecx
  const idMaterial *material; // eax

  if ( r_skipSubviews.internalVar->integerValue )
    return 0;
  viewDef = tr.viewDef;
  v2 = 0;
  for ( i = 0; v2 < tr.viewDef->numDrawSurfs; ++v2 )
  {
    v4 = viewDef->drawSurfs[v2];
    material = v4->material;
    if ( material && material->hasSubview )
    {
      if ( R_GenerateSurfaceSubview(v4) )
        i = 1;
    }
    viewDef = tr.viewDef;
  }
  return i;
}
