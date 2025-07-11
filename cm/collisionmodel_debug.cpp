
// FUNC: private: char const * __thiscall idCollisionModelManagerLocal::StringFromContents(int)const
char *__thiscall idCollisionModelManagerLocal::StringFromContents(idCollisionModelManagerLocal *this, int contents)
{
  int v2; // esi
  int *v3; // eax
  int v4; // edi

  v2 = 0;
  contentsString[0] = 0;
  if ( dword_102F1B24[0] )
  {
    v3 = dword_102F1B24;
    v4 = 0;
    do
    {
      if ( (contents & *v3) != 0 )
      {
        if ( v2 )
          v2 += idStr::snPrintf(&contentsString[v2], 1024 - v2, ",");
        v2 += idStr::snPrintf(&contentsString[v2], 1024 - v2, off_102F1AC4[v4]);
      }
      v3 = &dword_102F1B24[++v4];
    }
    while ( dword_102F1B24[v4] );
  }
  return contentsString;
}

// FUNC: private: int __thiscall idCollisionModelManagerLocal::ContentsFromString(char const *)const
int __thiscall idCollisionModelManagerLocal::ContentsFromString(idCollisionModelManagerLocal *this, const char *string)
{
  int v2; // ebp
  int v3; // eax
  int v4; // edi
  const char **v5; // eax
  char **v6; // esi
  idToken token; // [esp+8h] [ebp-124h] BYREF
  idLexer src; // [esp+58h] [ebp-D4h] BYREF
  int v10; // [esp+128h] [ebp-4h]

  v2 = 0;
  v3 = 0;
  if ( *string )
  {
    do
      ++v3;
    while ( string[v3] );
  }
  idLexer::idLexer(&src, string, v3, "ContentsFromString", 0);
  token.floatvalue = 0.0;
  v10 = 1;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  while ( idLexer::ReadToken(&src, &token) )
  {
    if ( idStr::Cmp(token.data, ",") )
    {
      v4 = 1;
      if ( off_102F1AC4[0] )
      {
        v5 = (const char **)off_102F1AC4;
        v6 = off_102F1AC4;
        while ( idStr::Icmp(token.data, *v5) )
        {
          ++v6;
          ++v4;
          v5 = (const char **)v6;
          if ( !*v6 )
            goto LABEL_11;
        }
        v2 |= cm_contentsFlagByIndex[v4];
      }
    }
LABEL_11:
    ;
  }
  LOBYTE(v10) = 0;
  idStr::FreeData(&token);
  v10 = -1;
  idLexer::~idLexer(&src);
  return v2;
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::DrawEdge(class idCollisionModelLocal *,int,class idVec3 const &,class idMat3 const &,class idVec3 const &,class idMat3 const &,float)
void __thiscall idCollisionModelManagerLocal::DrawEdge(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        unsigned int edgeNum,
        const idVec3 *origin,
        const idMat3 *axis,
        const idVec3 *viewOrigin,
        const idMat3 *viewAxis,
        float radius)
{
  unsigned int v8; // ebx
  cm_vertex_t *vertices; // ebp
  cm_edge_t *v10; // edi
  float *p_x; // eax
  double v13; // st7
  double v14; // st6
  double v15; // st7
  double v16; // st6
  double v17; // st7
  double v18; // st6
  float *v19; // eax
  double v20; // st5
  double v21; // st4
  double v22; // st5
  double v23; // st4
  double floatValue; // st7
  double v25; // st7
  float v26; // eax
  double v27; // st6
  idRenderWorld_vtbl *v28; // edi
  char *v29; // eax
  double v30; // st7
  float v31; // ecx
  double v32; // st6
  idRenderWorld_vtbl *v33; // edi
  char *v34; // eax
  double x; // st7
  double y; // st6
  idRenderWorld_vtbl *v37; // edi
  char *v38; // eax
  float v39; // [esp+28h] [ebp-64h]
  float v40; // [esp+28h] [ebp-64h]
  float v41; // [esp+28h] [ebp-64h]
  idVec3 mid; // [esp+50h] [ebp-3Ch] BYREF
  idVec3 start; // [esp+5Ch] [ebp-30h] BYREF
  idVec3 end; // [esp+68h] [ebp-24h] BYREF
  float v45; // [esp+74h] [ebp-18h]
  float v46; // [esp+78h] [ebp-14h]
  float v47; // [esp+7Ch] [ebp-10h]
  float v48; // [esp+80h] [ebp-Ch] BYREF
  float v49; // [esp+84h] [ebp-8h]
  float v50; // [esp+88h] [ebp-4h]
  idCollisionModelLocal *modela; // [esp+90h] [ebp+4h]
  const idMat3 *axisa; // [esp+9Ch] [ebp+10h]

  v8 = abs32(edgeNum);
  vertices = model->vertices;
  v10 = &model->edges[v8];
  p_x = &vertices[v10->vertexNum[edgeNum >> 31]].p.x;
  modela = (idCollisionModelLocal *)&v10->vertexNum[edgeNum >> 31];
  v13 = axis->mat[2].x * vertices[(int)modela->__vftable].p.z;
  v14 = axis->mat[0].x * *p_x;
  axisa = (const idMat3 *)&v10->vertexNum[(edgeNum & 0x80000000) == 0];
  v15 = v13 + v14 + axis->mat[1].x * vertices[(int)modela->__vftable].p.y;
  v16 = axis->mat[2].y * p_x[2] + axis->mat[1].y * p_x[1] + axis->mat[0].y * *p_x;
  v50 = p_x[1] * axis->mat[1].z + axis->mat[0].z * *p_x + p_x[2] * axis->mat[2].z;
  v45 = v15 + origin->x;
  start.x = v45;
  v17 = v16 + origin->y;
  v18 = v50 + origin->z;
  start.y = v17;
  start.z = v18;
  v19 = &vertices[LODWORD(axisa->mat[0].x)].p.x;
  v20 = axis->mat[2].x * vertices[LODWORD(axisa->mat[0].x)].p.z
      + axis->mat[1].x * vertices[LODWORD(axisa->mat[0].x)].p.y
      + axis->mat[0].x * *v19;
  v21 = axis->mat[2].y * vertices[LODWORD(axisa->mat[0].x)].p.z
      + axis->mat[1].y * vertices[LODWORD(axisa->mat[0].x)].p.y
      + *v19 * axis->mat[0].y;
  end.z = axis->mat[2].z * vertices[LODWORD(axisa->mat[0].x)].p.z
        + axis->mat[1].z * vertices[LODWORD(axisa->mat[0].x)].p.y
        + axis->mat[0].z * *v19;
  v48 = v20 + origin->x;
  v22 = v21 + origin->y;
  v23 = end.z + origin->z;
  end.x = v48;
  v50 = v23;
  end.y = v22;
  end.z = v23;
  v45 = v48 + v45;
  v46 = v22 + v17;
  v50 = (v50 + v18) * 0.5;
  mid.z = v50;
  mid.x = v45 * 0.5;
  mid.y = v46 * 0.5;
  if ( v10->internal )
  {
    if ( cm_drawInternal.internalVar->integerValue )
      session->rw->DebugArrow(session->rw, &colorGreen, &start, &end, 1, 0);
  }
  else if ( v10->numUsers <= 2u )
  {
    session->rw->DebugArrow(session->rw, &cm_color, &start, &end, 1, 0);
  }
  else
  {
    session->rw->DebugArrow(session->rw, &colorBlue, &start, &end, 1, 0);
  }
  if ( cm_drawNormals.internalVar->floatValue != 0.0 )
  {
    v45 = axis->mat[2].x * v10->normal.z + axis->mat[1].x * v10->normal.y + v10->normal.x * axis->mat[0].x;
    v46 = axis->mat[2].y * v10->normal.z + axis->mat[1].y * v10->normal.y + v10->normal.x * axis->mat[0].y;
    v47 = v10->normal.x * axis->mat[0].z + axis->mat[2].z * v10->normal.z + axis->mat[1].z * v10->normal.y;
    floatValue = cm_drawNormals.internalVar->floatValue;
    v46 = v46 * floatValue;
    v47 = v47 * floatValue;
    v48 = v45 * floatValue + mid.x;
    v49 = v46 + mid.y;
    v50 = v47 + mid.z;
    session->rw->DebugArrow(session->rw, &colorCyan, &mid, (const idVec3 *)&v48, 1, 0);
  }
  if ( cm_drawIndices.internalVar->integerValue )
  {
    v25 = viewAxis->mat[2].x * 0.5;
    v26 = cm_drawIndexScale.internalVar->floatValue;
    v27 = viewAxis->mat[2].y * 0.5;
    v47 = viewAxis->mat[2].z * 0.5;
    v39 = v26;
    v48 = v25 + mid.x;
    v49 = v27 + mid.y;
    v50 = v47 + mid.z;
    v28 = session->rw->__vftable;
    v29 = va("%d", v8);
    ((void (__thiscall *)(idRenderWorld *, char *, float *, _DWORD, idVec4 *, const idMat3 *, int, _DWORD, _DWORD))v28->DrawTextA)(
      session->rw,
      v29,
      &v48,
      LODWORD(v39),
      &colorWhite,
      viewAxis,
      1,
      0,
      0);
    v30 = viewAxis->mat[2].x * 0.5;
    v31 = cm_drawIndexScale.internalVar->floatValue;
    v32 = viewAxis->mat[2].y * 0.5;
    v47 = viewAxis->mat[2].z * 0.5;
    v40 = v31;
    v48 = v30 + start.x;
    v49 = v32 + start.y;
    v50 = v47 + start.z;
    v33 = session->rw->__vftable;
    v34 = va("%d", modela->__vftable);
    ((void (__thiscall *)(idRenderWorld *, char *, float *, _DWORD, idVec4 *, const idMat3 *, int, _DWORD, _DWORD))v33->DrawTextA)(
      session->rw,
      v34,
      &v48,
      LODWORD(v40),
      &colorYellow,
      viewAxis,
      1,
      0,
      0);
    x = viewAxis->mat[2].x;
    y = viewAxis->mat[2].y;
    v41 = cm_drawIndexScale.internalVar->floatValue;
    v47 = viewAxis->mat[2].z * 0.5;
    v48 = x * 0.5 + end.x;
    v49 = y * 0.5 + end.y;
    v50 = v47 + end.z;
    v37 = session->rw->__vftable;
    v38 = va("%d", axisa->mat[0].x);
    v37->DrawTextA(session->rw, v38, (const idVec3 *)&v48, COERCE_FLOAT(LODWORD(v41)), &colorYellow, viewAxis, 1, 0, 0);
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::DebugTranslationFailure(class idVec3 const &,class idMat3 const &)
void __thiscall idCollisionModelManagerLocal::DebugTranslationFailure(
        idCollisionModelManagerLocal *this,
        const idVec3 *viewOrigin,
        const idMat3 *viewAxis)
{
  trace_t trace; // [esp+6Ch] [ebp-74h] BYREF

  if ( translationFailure.valid )
  {
    if ( cm_debugTranslation.internalVar->integerValue )
    {
      cm_color.x = 1.0;
      cm_color.y = 0.0;
      cm_color.z = 0.0;
      cm_color.w = 0.5;
      ((void (__thiscall *)(idCollisionModelManagerLocal *, idCollisionModel *, idVec3 *, idMat3 *, const idVec3 *, const idMat3 *, int))this->DrawModel)(
        this,
        translationFailure.trmModel,
        &translationFailure.start,
        &translationFailure.trmAxis,
        viewOrigin,
        viewAxis,
        1149239296);
      ((void (__thiscall *)(idCollisionModelManagerLocal *, idCollisionModel *, idVec3 *, idMat3 *, const idVec3 *, const idMat3 *, int))this->DrawModel)(
        this,
        translationFailure.model,
        &translationFailure.modelOrigin,
        &translationFailure.modelAxis,
        viewOrigin,
        viewAxis,
        1149239296);
      this->Translation(
        this,
        &trace,
        &translationFailure.start,
        &translationFailure.end,
        &translationFailure.trm,
        &translationFailure.trmAxis,
        translationFailure.contentMask,
        translationFailure.model,
        &translationFailure.modelOrigin,
        &translationFailure.modelAxis);
      this->Contents(
        this,
        &trace.endpos,
        &translationFailure.trm,
        &trace.endAxis,
        -1,
        translationFailure.model,
        &translationFailure.modelOrigin,
        &translationFailure.modelAxis);
      cm_color.x = 1.0;
      cm_color.y = 1.0;
      cm_color.z = 0.0;
      cm_color.w = 0.5;
      ((void (__thiscall *)(idCollisionModelManagerLocal *, idCollisionModel *, idVec3 *, idMat3 *, const idVec3 *, const idMat3 *, int))this->DrawModel)(
        this,
        translationFailure.trmModel,
        &trace.endpos,
        &trace.endAxis,
        viewOrigin,
        viewAxis,
        1149239296);
      cm_color.x = 1.0;
      cm_color.y = 0.0;
      cm_color.z = 0.0;
      cm_color.w = 0.5;
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::DebugRotationFailure(class idVec3 const &,class idMat3 const &)
void __thiscall idCollisionModelManagerLocal::DebugRotationFailure(
        idCollisionModelManagerLocal *this,
        const idVec3 *viewOrigin,
        const idMat3 *viewAxis)
{
  trace_t trace; // [esp+6Ch] [ebp-74h] BYREF

  if ( rotationFailure.valid )
  {
    if ( cm_debugRotation.internalVar->integerValue )
    {
      cm_color.x = 1.0;
      cm_color.y = 0.0;
      cm_color.z = 0.0;
      cm_color.w = 0.5;
      ((void (__thiscall *)(idCollisionModelManagerLocal *, idCollisionModel *, idVec3 *, idMat3 *, const idVec3 *, const idMat3 *, int))this->DrawModel)(
        this,
        rotationFailure.trmModel,
        &rotationFailure.start,
        &rotationFailure.trmAxis,
        viewOrigin,
        viewAxis,
        1149239296);
      ((void (__thiscall *)(idCollisionModelManagerLocal *, idCollisionModel *, idVec3 *, idMat3 *, const idVec3 *, const idMat3 *, int))this->DrawModel)(
        this,
        rotationFailure.model,
        &rotationFailure.modelOrigin,
        &rotationFailure.modelAxis,
        viewOrigin,
        viewAxis,
        1149239296);
      this->Rotation(
        this,
        &trace,
        &rotationFailure.start,
        &rotationFailure.rotation,
        &rotationFailure.trm,
        &rotationFailure.trmAxis,
        rotationFailure.contentMask,
        rotationFailure.model,
        &rotationFailure.modelOrigin,
        &rotationFailure.modelAxis);
      this->Contents(
        this,
        &trace.endpos,
        &rotationFailure.trm,
        &trace.endAxis,
        -1,
        rotationFailure.model,
        &rotationFailure.modelOrigin,
        &rotationFailure.modelAxis);
      cm_color.x = 1.0;
      cm_color.y = 1.0;
      cm_color.z = 0.0;
      cm_color.w = 0.5;
      ((void (__thiscall *)(idCollisionModelManagerLocal *, idCollisionModel *, idVec3 *, idMat3 *, const idVec3 *, const idMat3 *, int))this->DrawModel)(
        this,
        rotationFailure.trmModel,
        &trace.endpos,
        &trace.endAxis,
        viewOrigin,
        viewAxis,
        1149239296);
      cm_color.x = 1.0;
      cm_color.y = 0.0;
      cm_color.z = 0.0;
      cm_color.w = 0.5;
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::DrawPolygon(class idCollisionModelLocal *,struct cm_polygon_t *,class idVec3 const &,class idMat3 const &,class idVec3 const &,class idMat3 const &,float)
void __thiscall idCollisionModelManagerLocal::DrawPolygon(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_polygon_t *p,
        const idVec3 *origin,
        const idMat3 *axis,
        const idVec3 *viewOrigin,
        const idMat3 *viewAxis,
        float radius)
{
  bool v8; // zf
  idCollisionModelLocal *v9; // ebx
  cm_polygon_t *v10; // edi
  idVec3 *v11; // eax
  idCVar *internalVar; // ecx
  int numEdges; // eax
  int *edges; // ecx
  cm_edge_t *v15; // eax
  BOOL v16; // edx
  int v17; // edx
  cm_vertex_t *vertices; // eax
  double v19; // st7
  int p_p; // eax
  double v21; // st7
  const idVec3 *v22; // ebp
  double v23; // st7
  double v24; // st6
  double v25; // st7
  double v26; // st7
  double v27; // st6
  double v28; // st7
  double v29; // st7
  double v30; // st6
  double v31; // st5
  double floatValue; // st7
  float b; // eax
  float c; // ecx
  int v35; // eax
  unsigned int v36; // ecx
  idVec3 *v37; // eax
  int numPoints; // ecx
  double v39; // st7
  double v40; // st6
  idVec5 *v41; // eax
  idCollisionModelManagerLocal *v42; // edx
  bool v43; // cc
  int v44; // ecx
  cm_edge_t *v45; // eax
  int checkCount; // edx
  int v47; // eax
  int *v48; // ecx
  cm_edge_t *v49; // ebp
  cm_vertex_t *v50; // ebx
  int *v51; // ecx
  float *p_x; // eax
  float *v53; // eax
  float *v54; // eax
  float *v55; // eax
  unsigned int v56; // ecx
  unsigned int v57; // eax
  int v58; // edx
  cm_edge_t *v59; // eax
  float *v60; // eax
  double v61; // st7
  float v62; // edx
  double v63; // st6
  double v64; // st5
  double v65; // st7
  double v66; // st6
  double v67; // st5
  double v68; // st7
  double v69; // st6
  double v70; // st5
  double v71; // st7
  idRenderWorld *rw; // esi
  int v73; // edi
  idRenderWorld_vtbl *v74; // ebp
  char *v75; // eax
  idCollisionModelManagerLocal *v76; // [esp-20h] [ebp-58Ch]
  idVec3 center; // [esp+8h] [ebp-564h] BYREF
  int i; // [esp+14h] [ebp-558h]
  idCollisionModelManagerLocal *floatValue_low; // [esp+18h] [ebp-554h]
  unsigned int v80; // [esp+1Ch] [ebp-550h]
  float v81; // [esp+20h] [ebp-54Ch]
  float v82; // [esp+24h] [ebp-548h]
  float v83; // [esp+28h] [ebp-544h]
  float a; // [esp+2Ch] [ebp-540h]
  float y; // [esp+30h] [ebp-53Ch]
  float z; // [esp+34h] [ebp-538h]
  idVec3 end; // [esp+38h] [ebp-534h] BYREF
  float v88; // [esp+44h] [ebp-528h]
  float v89; // [esp+4Ch] [ebp-520h]
  idFixedWinding winding; // [esp+50h] [ebp-51Ch] BYREF
  int v91; // [esp+568h] [ebp-4h]

  v8 = cm_backFaceCull.internalVar->integerValue == 0;
  v9 = model;
  v10 = p;
  floatValue_low = this;
  if ( v8
    || (v11 = &model->vertices[model->edges[abs32(*p->edges)].vertexNum[0]].p,
        (v11->y - viewOrigin->y) * p->plane.b
      + (v11->z - viewOrigin->z) * p->plane.c
      + (v11->x - viewOrigin->x) * p->plane.a <= 0.0) )
  {
    internalVar = cm_drawNormals.internalVar;
    if ( cm_drawNormals.internalVar->floatValue == 0.0 )
    {
      v22 = origin;
    }
    else
    {
      numEdges = p->numEdges;
      memset(&center, 0, sizeof(center));
      v80 = numEdges;
      if ( numEdges > 0 )
      {
        edges = p->edges;
        i = numEdges;
        do
        {
          v15 = &model->edges[abs32(*edges)];
          v16 = *edges++ < 0;
          v8 = i-- == 1;
          v17 = v15->vertexNum[v16];
          vertices = model->vertices;
          v19 = center.x + vertices[v17].p.x;
          p_p = (int)&vertices[v17].p;
          center.x = v19;
          center.y = center.y + *(float *)(p_p + 4);
          center.z = center.z + *(float *)(p_p + 8);
        }
        while ( !v8 );
        internalVar = cm_drawNormals.internalVar;
      }
      v21 = 1.0 / (double)(int)v80;
      center.x = center.x * v21;
      center.y = center.y * v21;
      center.z = center.z * v21;
      if ( axis->mat[0].x == 1.0 && axis->mat[1].y == 1.0 && axis->mat[2].z == 1.0 )
      {
        v22 = origin;
        center.x = center.x + origin->x;
        center.y = center.y + origin->y;
        center.z = center.z + origin->z;
        floatValue = internalVar->floatValue;
        b = p->plane.b;
        c = p->plane.c;
        a = p->plane.a;
        y = b;
        z = c;
        v81 = a * floatValue;
        v82 = b * floatValue;
        v29 = floatValue * c + center.z;
        v30 = v82 + center.y;
        v31 = v81 + center.x;
      }
      else
      {
        v22 = origin;
        v23 = center.y * axis->mat[1].z + center.z * axis->mat[2].z + center.x * axis->mat[0].z;
        v24 = center.z * axis->mat[2].y + center.x * axis->mat[0].y + center.y * axis->mat[1].y;
        v81 = center.x * axis->mat[0].x + center.y * axis->mat[1].x + center.z * axis->mat[2].x;
        *(float *)&v80 = v23 + origin->z;
        v25 = v24 + origin->y;
        LODWORD(center.z) = v80;
        *(float *)&i = v25;
        v88 = v81 + origin->x;
        center.x = v88;
        center.y = v25;
        v26 = p->plane.b * axis->mat[1].z + p->plane.c * axis->mat[2].z + axis->mat[0].z * p->plane.a;
        v27 = p->plane.c * axis->mat[2].y + axis->mat[0].y * p->plane.a + p->plane.b * axis->mat[1].y;
        end.x = axis->mat[0].x * p->plane.a + axis->mat[2].x * p->plane.c + axis->mat[1].x * p->plane.b;
        end.y = v27;
        y = end.y;
        end.z = v26;
        v28 = internalVar->floatValue;
        a = end.x;
        z = end.z;
        v81 = end.x * v28;
        v82 = end.y * v28;
        v29 = v28 * end.z + *(float *)&v80;
        v30 = v82 + *(float *)&i;
        v31 = v81 + v88;
      }
      end.x = v31;
      end.y = v30;
      end.z = v29;
      session->rw->DebugArrow(session->rw, &colorMagenta, &center, &end, 1, 0);
    }
    if ( cm_drawFilled.internalVar->integerValue )
    {
      winding.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
      winding.numPoints = 0;
      winding.p = winding.data;
      winding.allocedSize = 64;
      v91 = 0;
      v35 = p->numEdges - 1;
      i = v35;
      if ( v35 >= 0 )
      {
        while ( 1 )
        {
          v36 = p->edges[v35];
          v37 = &model->vertices[model->edges[abs32(v36)].vertexNum[v36 >> 31]].p;
          numPoints = winding.numPoints;
          v39 = axis->mat[1].z * v37->y + axis->mat[0].z * v37->x + v37->z * axis->mat[2].z;
          v40 = axis->mat[2].y * v37->z + v37->y * axis->mat[1].y + axis->mat[0].y * v37->x;
          v88 = axis->mat[2].x * v37->z + axis->mat[1].x * v37->y + axis->mat[0].x * v37->x;
          *(float *)&v80 = v39 + v22->z;
          *(float *)&floatValue_low = v40 + v22->y;
          v81 = v88 + v22->x;
          if ( winding.numPoints + 1 > winding.allocedSize )
          {
            if ( !winding.ReAllocate(&winding, winding.numPoints + 1, 1) )
              goto LABEL_23;
            numPoints = winding.numPoints;
          }
          v41 = &winding.p[numPoints];
          v42 = floatValue_low;
          v41->x = v81;
          v41->z = *(float *)&v80;
          LODWORD(v41->y) = v42;
          v41->t = 0.0;
          v41->s = 0.0;
          ++winding.numPoints;
LABEL_23:
          if ( --i < 0 )
            break;
          v35 = i;
        }
      }
      session->rw->DebugPolygon(session->rw, &cm_color, &winding, 0, 0);
      v91 = -1;
      winding.p = 0;
      winding.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
      Memory::Free(0);
    }
    else
    {
      v43 = p->numEdges <= 0;
      *(float *)&i = 0.0;
      if ( !v43 )
      {
        do
        {
          v44 = p->edges[i];
          v45 = &model->edges[abs32(v44)];
          checkCount = floatValue_low->checkCount;
          if ( v45->checkcount != checkCount )
          {
            v45->checkcount = checkCount;
            idCollisionModelManagerLocal::DrawEdge(floatValue_low, model, v44, v22, axis, viewOrigin, viewAxis, radius);
          }
          v43 = ++i < p->numEdges;
        }
        while ( v43 );
      }
    }
    if ( cm_drawIndices.internalVar->integerValue )
    {
      v80 = p->numEdges;
      v47 = v80 - 1;
      memset(&center, 0, sizeof(center));
      if ( (int)v80 >= 4 )
      {
        v48 = p->edges;
        v49 = model->edges;
        v50 = model->vertices;
        floatValue_low = (idCollisionModelManagerLocal *)(v80 >> 2);
        v51 = &v48[v47 - 2];
        i = v47 - 4 * (v80 >> 2);
        do
        {
          p_x = &v50[v49[abs32(v51[2])].vertexNum[(unsigned int)v51[2] >> 31]].p.x;
          center.x = center.x + *p_x;
          center.y = center.y + p_x[1];
          center.z = center.z + p_x[2];
          v53 = &v50[v49[abs32(v51[1])].vertexNum[(unsigned int)v51[1] >> 31]].p.x;
          center.x = center.x + *v53;
          center.y = center.y + v53[1];
          center.z = center.z + v53[2];
          v54 = &v50[v49[abs32(*v51)].vertexNum[(unsigned int)*v51 >> 31]].p.x;
          center.x = center.x + *v54;
          center.y = center.y + v54[1];
          center.z = center.z + v54[2];
          v55 = &v50[v49[abs32(*(v51 - 1))].vertexNum[(unsigned int)*(v51 - 1) >> 31]].p.x;
          v51 -= 4;
          center.x = center.x + *v55;
          center.y = center.y + v55[1];
          center.z = center.z + v55[2];
          floatValue_low = (idCollisionModelManagerLocal *)((char *)floatValue_low - 1);
        }
        while ( *(float *)&floatValue_low != 0.0 );
        v47 = i;
        v22 = origin;
        v10 = p;
        v9 = model;
      }
      if ( v47 >= 0 )
      {
        i = (int)&v10->edges[v47];
        floatValue_low = (idCollisionModelManagerLocal *)(v47 + 1);
        do
        {
          v56 = *(_DWORD *)i;
          v57 = abs32(*(_DWORD *)i);
          i -= 4;
          v58 = 9 * v57;
          v59 = v9->edges;
          v8 = floatValue_low == (idCollisionModelManagerLocal *)1;
          floatValue_low = (idCollisionModelManagerLocal *)((char *)floatValue_low - 1);
          v60 = &v9->vertices[v59->vertexNum[(v56 >> 31) + v58]].p.x;
          center.x = center.x + *v60;
          center.y = center.y + v60[1];
          center.z = center.z + v60[2];
        }
        while ( !v8 );
      }
      v61 = 1.0 / (double)(int)v80;
      a = v10->plane.a;
      v62 = v10->plane.c;
      y = v10->plane.b;
      z = v62;
      v63 = center.x * v61;
      center.y = center.y * v61;
      center.z = center.z * v61;
      v64 = center.y * v10->plane.b + center.z * v10->plane.c + v63 * v10->plane.a + v10->plane.d;
      v81 = a * v64;
      v82 = y * v64;
      v83 = v62 * v64;
      v65 = v63 - v81;
      v66 = center.y - v82;
      v67 = center.z - v83;
      v81 = v66 * axis->mat[1].x + v67 * axis->mat[2].x + v65 * axis->mat[0].x;
      v82 = v66 * axis->mat[1].y + v67 * axis->mat[2].y + v65 * axis->mat[0].y;
      v68 = v66 * axis->mat[1].z + v67 * axis->mat[2].z + v65 * axis->mat[0].z;
      v69 = v81 + v22->x;
      v70 = v68;
      v71 = v82 + v22->y;
      v89 = v70 + v22->z;
      center.z = v89;
      center.x = v69;
      center.y = v71;
      rw = session->rw;
      v73 = (char *)v10 - (char *)v9->polygons;
      v74 = rw->__vftable;
      floatValue_low = (idCollisionModelManagerLocal *)LODWORD(cm_drawIndexScale.internalVar->floatValue);
      v76 = floatValue_low;
      v75 = va("%d", v73 / 88);
      ((void (__thiscall *)(idRenderWorld *, char *, idVec3 *, idCollisionModelManagerLocal *, idVec4 *, const idMat3 *, int, _DWORD, _DWORD))v74->DrawTextA)(
        rw,
        v75,
        &center,
        v76,
        &colorMagenta,
        viewAxis,
        1,
        0,
        0);
    }
  }
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::DrawNodePolygons(class idCollisionModelLocal *,struct cm_node_t *,class idVec3 const &,class idMat3 const &,class idVec3 const &,class idMat3 const &,float)
void __thiscall idCollisionModelManagerLocal::DrawNodePolygons(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *model,
        cm_node_t *node,
        const idVec3 *origin,
        const idMat3 *axis,
        const idVec3 *viewOrigin,
        cm_polygonRef_t *viewAxis,
        float radius)
{
  cm_node_t *v10; // edi
  cm_polygon_t *p; // esi
  int v12; // edx
  const idVec3 *v13; // ecx
  int v14; // edi
  int planeType; // ecx
  cm_polygonRef_t *viewOrigina; // [esp+24h] [ebp+14h]

  while ( 1 )
  {
    v10 = node;
    for ( viewOrigina = node->polygons; viewOrigina; viewOrigina = viewOrigina->next )
    {
      p = viewOrigina->p;
      if ( radius == 0.0 )
      {
LABEL_9:
        if ( p->checkcount != this->checkCount
          && (cm_contentsFlagByIndex[cm_drawMask.internalVar->integerValue] & p->contents) != 0 )
        {
          idCollisionModelManagerLocal::DrawPolygon(
            this,
            model,
            p,
            origin,
            axis,
            viewOrigin,
            (const idMat3 *)viewAxis,
            radius);
          p->checkcount = this->checkCount;
        }
      }
      else
      {
        v12 = 0;
        v13 = viewOrigin;
        v14 = (char *)p - (char *)viewOrigin;
        while ( radius + v13->x >= *(float *)((char *)&v13->x + v14)
             && v13->x - radius <= *(float *)((char *)&v13[1].x + v14) )
        {
          ++v12;
          v13 = (const idVec3 *)((char *)v13 + 4);
          if ( v12 >= 3 )
          {
            v10 = node;
            goto LABEL_9;
          }
        }
        v10 = node;
      }
    }
    planeType = v10->planeType;
    if ( v10->planeType == -1 )
      break;
    if ( radius == 0.0 )
      goto LABEL_19;
    if ( radius + v10->planeDist >= *(&viewOrigin->x + planeType) )
    {
      if ( v10->planeDist - radius <= *(&viewOrigin->x + planeType) )
      {
LABEL_19:
        idCollisionModelManagerLocal::DrawNodePolygons(
          this,
          model,
          v10->children[1],
          origin,
          axis,
          viewOrigin,
          (const idMat3 *)viewAxis,
          radius);
        node = v10->children[0];
      }
      else
      {
        node = v10->children[1];
      }
    }
    else
    {
      node = v10->children[0];
    }
  }
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::DrawModel(class idCollisionModel *,class idVec3 const &,class idMat3 const &,class idVec3 const &,class idMat3 const &,float)
void __thiscall idCollisionModelManagerLocal::DrawModel(
        idCollisionModelManagerLocal *this,
        idCollisionModelLocal *handle,
        const idVec3 *modelOrigin,
        const idMat3 *modelAxis,
        const idVec3 *viewOrigin,
        cm_polygonRef_t *viewAxis,
        float radius)
{
  double z; // st7
  double v10; // st6
  double y; // st5
  double x; // st4
  float v13; // edx
  double v14; // st3
  double v15; // st6
  double v16; // st5
  float v17; // [esp+4h] [ebp-28h]
  float v18; // [esp+8h] [ebp-24h]
  float v19; // [esp+Ch] [ebp-20h]
  float v20; // [esp+14h] [ebp-18h]
  float v21; // [esp+18h] [ebp-14h]
  float v22; // [esp+1Ch] [ebp-10h]
  float v23; // [esp+1Ch] [ebp-10h]
  idVec3 viewPos; // [esp+20h] [ebp-Ch] BYREF
  float modelAxisa; // [esp+38h] [ebp+Ch]

  if ( (cm_drawColor.internalVar->flags & 0x40000) != 0 )
  {
    sscanf(cm_drawColor.internalVar->value, "%f %f %f %f", &cm_color, &cm_color.y, &cm_color.z, &cm_color.w);
    BYTE2(cm_drawColor.internalVar->flags) &= ~4u;
  }
  z = modelAxis->mat[2].z;
  v10 = modelAxis->mat[0].z;
  y = modelAxis->mat[0].y;
  v17 = modelAxis->mat[1].z;
  x = modelAxis->mat[0].x;
  v19 = modelAxis->mat[2].y;
  v13 = modelAxis->mat[2].x;
  modelAxisa = modelAxis->mat[1].y;
  v18 = modelAxis->mat[1].x;
  v20 = viewOrigin->x - modelOrigin->x;
  v21 = viewOrigin->y - modelOrigin->y;
  v14 = viewOrigin->z - modelOrigin->z;
  ++this->checkCount;
  v22 = v14;
  v15 = v21 * y + v22 * v10 + v20 * x;
  v16 = v21 * modelAxisa + v22 * v17 + v20 * v18;
  v23 = v21 * v19 + v22 * z + v20 * v13;
  viewPos.z = v23;
  viewPos.x = v15;
  viewPos.y = v16;
  idCollisionModelManagerLocal::DrawNodePolygons(
    this,
    handle,
    handle->node,
    modelOrigin,
    modelAxis,
    &viewPos,
    viewAxis,
    radius);
}

// FUNC: private: void __thiscall idCollisionModelManagerLocal::SpeedTest(class idVec3 const &)
void __thiscall idCollisionModelManagerLocal::SpeedTest(idCollisionModelManagerLocal *this, const idVec3 *origin)
{
  int v2; // ebp
  idVec3 *v4; // eax
  bool v5; // zf
  idCVar_vtbl *v6; // edx
  const char *v7; // eax
  int v8; // edx
  int v9; // esi
  idVec3 *v10; // ecx
  idCVar *internalVar; // edi
  _DWORD *p_z; // eax
  float *v13; // edx
  int v14; // edx
  float *v15; // eax
  double v16; // st7
  int v17; // edi
  long double v18; // st7
  long double v19; // st7
  int v20; // edi
  int integerValue; // ecx
  unsigned int v22; // edx
  int v23; // edx
  __int16 v24; // ax
  __int16 v25; // ax
  _DWORD *v26; // eax
  float *v27; // edx
  int i; // esi
  long double v29; // st7
  long double v30; // st7
  long double v31; // st7
  int v32; // esi
  int v33; // ecx
  int v34; // [esp+64h] [ebp-CD4h]
  int v35; // [esp+68h] [ebp-CD0h]
  int v36; // [esp+68h] [ebp-CD0h]
  idTimer timer; // [esp+70h] [ebp-CC8h] BYREF
  idAngles boxAngles; // [esp+88h] [ebp-CB0h] BYREF
  idMat3 modelAxis; // [esp+94h] [ebp-CA4h] BYREF
  idMat3 boxAxis; // [esp+B8h] [ebp-C80h] BYREF
  idBounds bounds; // [esp+DCh] [ebp-C5Ch] BYREF
  idRotation rotation; // [esp+F4h] [ebp-C44h] BYREF
  char buf[128]; // [esp+138h] [ebp-C00h] BYREF
  trace_t trace; // [esp+1B8h] [ebp-B80h] BYREF
  idTraceModel itm; // [esp+22Ch] [ebp-B0Ch] BYREF

  v2 = 0;
  if ( cm_testCollision.internalVar->integerValue )
  {
    v4 = (idVec3 *)Mem_Alloc(12 * cm_testTimes.internalVar->integerValue, 8u);
    v5 = cm_testReset.internalVar->integerValue == 0;
    testend = v4;
    if ( !v5 )
    {
      v6 = cm_testReset.internalVar->__vftable;
      min_rotation = 999999;
      min_translation = 999999;
      total_rotation = 0;
      total_translation = 0;
      max_rotation = -999999;
      max_translation = -999999;
      num_rotation = 0;
      num_translation = 0;
      v6->InternalSetBool(cm_testReset.internalVar, 0);
    }
    if ( cm_testWalk.internalVar->integerValue )
    {
      start_2 = *origin;
      v7 = va("%1.2f %1.2f %1.2f", start_2.x, start_2.y, start_2.z);
      cm_testOrigin.internalVar->InternalSetString(cm_testOrigin.internalVar, v7);
    }
    else
    {
      sscanf(cm_testOrigin.internalVar->value, "%f %f %f", &start_2, &start_2.y, &start_2.z);
    }
    sscanf(
      cm_testBox.internalVar->value,
      "%f %f %f %f %f %f",
      &bounds,
      &bounds.b[0].y,
      &bounds.b[0].z,
      &bounds.b[1],
      &bounds.b[1].y,
      &bounds.b[1].z);
    sscanf(cm_testBoxRotation.internalVar->value, "%f %f %f", &boxAngles, &boxAngles.yaw, &boxAngles.roll);
    boxAxis = *idAngles::ToMat3(&boxAngles, (idMat3 *)&rotation);
    modelAxis = mat3_identity;
    idTraceModel::InitBox(&itm);
    idTraceModel::SetupBox(&itm, &bounds);
    v8 = 1;
    v9 = 0;
    timer.state = TS_STOPPED;
    timer.clockTicks = 0.0;
    v10 = testend;
    if ( cm_testRandomMany.internalVar->integerValue )
    {
      v9 = 475628535;
      testend->x = start_2.x - cm_testLength.internalVar->floatValue * 0.99993896;
      v10->y = start_2.y - cm_testLength.internalVar->floatValue * 0.78430176;
      v10->z = start_2.z - cm_testLength.internalVar->floatValue * 0.93804932;
      internalVar = cm_testTimes.internalVar;
      if ( cm_testTimes.internalVar->integerValue > 1 )
      {
        p_z = (_DWORD *)&v10[1].z;
        do
        {
          *(p_z - 2) = LODWORD(v10->x);
          *(p_z - 1) = LODWORD(v10->y);
          *p_z = LODWORD(v10->z);
          internalVar = cm_testTimes.internalVar;
          ++v8;
          p_z += 3;
        }
        while ( v8 < cm_testTimes.internalVar->integerValue );
      }
    }
    else
    {
      internalVar = cm_testTimes.internalVar;
      if ( cm_testTimes.internalVar->integerValue > 0 )
      {
        v13 = &testend->z;
        do
        {
          ++v2;
          v13 += 3;
          *(v13 - 5) = ((double)((3533 * (_WORD)v9 + 1) & 0x7FFF) * 0.000030517578
                      - 0.5
                      + (double)((3533 * (_WORD)v9 + 1) & 0x7FFF) * 0.000030517578
                      - 0.5)
                     * cm_testLength.internalVar->floatValue
                     + start_2.x;
          v34 = (3533 * (3533 * (_WORD)v9 + 1) + 1) & 0x7FFF;
          v9 = 69069 * (69069 * (69069 * v9 + 1) + 1) + 1;
          *(v13 - 4) = ((double)v34 * 0.000030517578 - 0.5 + (double)v34 * 0.000030517578 - 0.5)
                     * cm_testLength.internalVar->floatValue
                     + start_2.y;
          *(v13 - 3) = ((double)(v9 & 0x7FFF) * 0.000030517578 - 0.5 + (double)(v9 & 0x7FFF) * 0.000030517578 - 0.5)
                     * cm_testLength.internalVar->floatValue
                     + start_2.z;
          internalVar = cm_testTimes.internalVar;
        }
        while ( v2 < cm_testTimes.internalVar->integerValue );
      }
      v2 = 0;
    }
    start_2.x = 0.0;
    start_2.y = 0.0;
    start_2.z = 10.0;
    v14 = 0;
    if ( internalVar->integerValue > 0 )
    {
      v15 = &v10->z;
      do
      {
        *(idVec3 *)(v15 - 2) = start_2;
        v16 = *v15 - 10.0;
        ++v14;
        v15 += 3;
        *(v15 - 3) = v16;
        internalVar = cm_testTimes.internalVar;
      }
      while ( v14 < cm_testTimes.internalVar->integerValue );
    }
    if ( cm_testTranslation.internalVar->integerValue )
    {
      timer.clockTicks = 0.0;
      timer.state = TS_STARTED;
      timer.start = idLib::sys->GetClockTicks(idLib::sys);
      v17 = 0;
      if ( cm_testTimes.internalVar->integerValue > 0 )
      {
        do
        {
          this->Translation(
            this,
            &trace,
            &start_2,
            (idVec3 *)((char *)testend + v2),
            &itm,
            &boxAxis,
            9,
            this->models.list[cm_testModel.internalVar->integerValue],
            &vec3_origin,
            &modelAxis);
          ++v17;
          v2 += 12;
        }
        while ( v17 < cm_testTimes.internalVar->integerValue );
        v2 = 0;
      }
      timer.clockTicks = idLib::sys->GetClockTicks(idLib::sys) - timer.start + timer.clockTicks;
      if ( idTimer::base < 0.0 )
        idTimer::InitBaseClockTicks(&timer);
      if ( timer.clockTicks > idTimer::base )
        timer.clockTicks = timer.clockTicks - idTimer::base;
      timer.state = TS_STOPPED;
      v18 = idLib::sys->ClockTicksPerSecond(idLib::sys);
      v19 = timer.clockTicks / (v18 * 0.001);
      v20 = (__int64)v19;
      if ( v20 < min_translation )
        min_translation = (__int64)v19;
      if ( v20 > max_translation )
        max_translation = (__int64)v19;
      integerValue = cm_testTimes.internalVar->integerValue;
      ++num_translation;
      total_translation += v20;
      if ( integerValue <= 9999 )
      {
        sprintf(buf, "%4d", integerValue);
      }
      else
      {
        v22 = (int)((unsigned __int64)(integerValue * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6;
        sprintf(buf, "%3dK", v22 + (v22 >> 31));
      }
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%s translations: %4d milliseconds, (min = %d, max = %d, av = %1.1f)\n",
        buf,
        v20,
        min_translation,
        max_translation,
        (double)total_translation / (double)num_translation);
      v10 = testend;
      internalVar = cm_testTimes.internalVar;
    }
    if ( cm_testRandomMany.internalVar->integerValue )
    {
      v23 = 1;
      v24 = 3533 * v9 + 1;
      v35 = v24 & 0x7FFF;
      v25 = 3533 * v24 + 1;
      v10->x = ((double)v35 * 0.000030517578 - 0.5 + (double)v35 * 0.000030517578 - 0.5)
             * cm_testRadius.internalVar->floatValue
             + start_2.x;
      v10->y = ((double)(v25 & 0x7FFF) * 0.000030517578 - 0.5 + (double)(v25 & 0x7FFF) * 0.000030517578 - 0.5)
             * cm_testRadius.internalVar->floatValue
             + start_2.y;
      v10->z = ((double)((3533 * v25 + 1) & 0x7FFF) * 0.000030517578
              - 0.5
              + (double)((3533 * v25 + 1) & 0x7FFF) * 0.000030517578
              - 0.5)
             * cm_testRadius.internalVar->floatValue
             + start_2.z;
      if ( cm_testTimes.internalVar->integerValue > 1 )
      {
        v26 = (_DWORD *)&v10[1].z;
        do
        {
          *(v26 - 2) = LODWORD(v10->x);
          *(v26 - 1) = LODWORD(v10->y);
          *v26 = LODWORD(v10->z);
          ++v23;
          v26 += 3;
        }
        while ( v23 < cm_testTimes.internalVar->integerValue );
      }
    }
    else if ( internalVar->integerValue > 0 )
    {
      v27 = &v10->z;
      do
      {
        ++v2;
        v27 += 3;
        *(v27 - 5) = ((double)((3533 * (_WORD)v9 + 1) & 0x7FFF) * 0.000030517578
                    - 0.5
                    + (double)((3533 * (_WORD)v9 + 1) & 0x7FFF) * 0.000030517578
                    - 0.5)
                   * cm_testRadius.internalVar->floatValue
                   + start_2.x;
        v36 = (3533 * (3533 * (_WORD)v9 + 1) + 1) & 0x7FFF;
        v9 = 69069 * (69069 * (69069 * v9 + 1) + 1) + 1;
        *(v27 - 4) = ((double)v36 * 0.000030517578 - 0.5 + (double)v36 * 0.000030517578 - 0.5)
                   * cm_testRadius.internalVar->floatValue
                   + start_2.y;
        *(v27 - 3) = ((double)(v9 & 0x7FFF) * 0.000030517578 - 0.5 + (double)(v9 & 0x7FFF) * 0.000030517578 - 0.5)
                   * cm_testRadius.internalVar->floatValue
                   + start_2.z;
      }
      while ( v2 < cm_testTimes.internalVar->integerValue );
    }
    if ( cm_testRotation.internalVar->integerValue )
    {
      timer.clockTicks = 0.0;
      rotation.origin.x = 30.0;
      memset(&rotation.origin.y, 0, 12);
      rotation.angle = 90.0;
      rotation.vec.y = 1.0;
      rotation.vec.z = 0.0;
      rotation.axisValid = 0;
      start_2.x = 30.0;
      start_2.y = 0.0;
      start_2.z = 0.0;
      timer.state = TS_STARTED;
      timer.start = idLib::sys->GetClockTicks(idLib::sys);
      for ( i = 0; i < cm_testTimes.internalVar->integerValue; ++i )
        this->Rotation(
          this,
          &trace,
          &start_2,
          &rotation,
          &itm,
          &boxAxis,
          9,
          this->models.list[cm_testModel.internalVar->integerValue],
          &vec3_origin,
          &modelAxis);
      v29 = idLib::sys->GetClockTicks(idLib::sys);
      timer.clockTicks = v29 - timer.start + timer.clockTicks;
      if ( idTimer::base < 0.0 )
        idTimer::InitBaseClockTicks(&timer);
      if ( timer.clockTicks > idTimer::base )
        timer.clockTicks = timer.clockTicks - idTimer::base;
      timer.state = TS_STOPPED;
      v30 = idLib::sys->ClockTicksPerSecond(idLib::sys);
      v31 = timer.clockTicks / (v30 * 0.001);
      v32 = (__int64)v31;
      if ( v32 < min_rotation )
        min_rotation = (__int64)v31;
      if ( v32 > max_rotation )
        max_rotation = (__int64)v31;
      v33 = cm_testTimes.internalVar->integerValue;
      ++num_rotation;
      total_rotation += v32;
      if ( v33 <= 9999 )
        sprintf(buf, "%4d", v33);
      else
        sprintf(
          buf,
          "%3dK",
          ((int)((unsigned __int64)(v33 * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6)
        + ((unsigned int)((unsigned __int64)(v33 * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 31));
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%s rotation: %4d milliseconds, (min = %d, max = %d, av = %1.1f)\n",
        buf,
        v32,
        min_rotation,
        max_rotation,
        (double)total_rotation / (double)num_rotation);
      v10 = testend;
    }
    Mem_Free(v10);
    testend = 0;
  }
}

// FUNC: public: virtual void __thiscall idCollisionModelManagerLocal::DebugOutput(class idVec3 const &,class idMat3 const &)
void __thiscall idCollisionModelManagerLocal::DebugOutput(
        idCollisionModelManagerLocal *this,
        const idVec3 *viewOrigin,
        const idMat3 *viewAxis)
{
  idCollisionModelManagerLocal::SpeedTest(this, viewOrigin);
  idCollisionModelManagerLocal::DebugTranslationFailure(this, viewOrigin, viewAxis);
  idCollisionModelManagerLocal::DebugRotationFailure(this, viewOrigin, viewAxis);
}
