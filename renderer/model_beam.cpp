
// FUNC: public: virtual enum dynamicModel_t __thiscall idRenderModelLiquid::IsDynamicModel(void)const
int __thiscall idRenderModelLiquid::IsDynamicModel(idRenderModelBeam *this)
{
  return 2;
}

// FUNC: public: virtual class idRenderModel * __thiscall idRenderModelBeam::InstantiateDynamicModel(struct renderEntity_s const *,struct viewDef_s const *,class idRenderModel *,unsigned int)
idRenderModelStatic *__thiscall idRenderModelBeam::InstantiateDynamicModel(
        idRenderModelBeam *this,
        const renderEntity_s *renderEntity,
        const viewDef_s *viewDef,
        idRenderModel *cachedModel,
        unsigned int __formal)
{
  idRenderModel *v6; // ecx
  idRenderModelStatic *v7; // edi
  int *v8; // eax
  int v9; // ecx
  const idMaterial *v10; // edx
  srfTriangles_s *v11; // esi
  idStr *v12; // eax
  idDrawVert *verts; // eax
  idDrawVert *v14; // eax
  int v15; // eax
  idDrawVert *v16; // eax
  float v17; // eax
  float v18; // ecx
  double v19; // st7
  double v20; // st6
  double v21; // st7
  long double v22; // st7
  long double v23; // st7
  double v24; // st7
  float *p_x; // eax
  unsigned __int8 v26; // cl
  unsigned __int8 v27; // dl
  srfTriangles_s *geometry; // ebp
  idDrawVert *v29; // eax
  int v30; // eax
  double v31; // st6
  double v32; // st7
  double v33; // st7
  int v34; // eax
  double v35; // st6
  float mid; // [esp+18h] [ebp-A0h]
  float mid_4; // [esp+1Ch] [ebp-9Ch]
  float mid_8a; // [esp+20h] [ebp-98h]
  float mid_8; // [esp+20h] [ebp-98h]
  float v41; // [esp+24h] [ebp-94h]
  float v42; // [esp+24h] [ebp-94h]
  float v43; // [esp+24h] [ebp-94h]
  int v44; // [esp+24h] [ebp-94h]
  int v45; // [esp+28h] [ebp-90h]
  idVec3 localTarget; // [esp+2Ch] [ebp-8Ch] BYREF
  idVec3 target; // [esp+38h] [ebp-80h] BYREF
  idVec3 localView; // [esp+44h] [ebp-74h] BYREF
  modelSurface_s surf; // [esp+50h] [ebp-68h]
  idVec3 major; // [esp+60h] [ebp-58h]
  int v51; // [esp+6Ch] [ebp-4Ch]
  float v52; // [esp+70h] [ebp-48h]
  int v53; // [esp+74h] [ebp-44h]
  float modelMatrix[16]; // [esp+78h] [ebp-40h] BYREF

  v6 = cachedModel;
  if ( cachedModel )
  {
    ((void (__thiscall *)(idRenderModel *, int))cachedModel->~idRenderModel)(cachedModel, 1);
    v6 = 0;
  }
  if ( renderEntity && viewDef )
  {
    if ( v6 )
    {
      v7 = (idRenderModelStatic *)v6;
      v8 = (int *)((int (__stdcall *)(_DWORD))v6->Surface)(0);
      v9 = *v8;
      v10 = (const idMaterial *)v8[1];
      v11 = (srfTriangles_s *)v8[2];
      v12 = (idStr *)v8[3];
      surf.id = v9;
      surf.shader = v10;
      surf.mOriginalSurfaceName = v12;
    }
    else
    {
      v7 = NewRenderModel<idRenderModelStatic>(this);
      v7->InitEmpty(v7, beam_SnapshotName);
      v11 = R_AllocStaticTriSurf();
      R_AllocStaticTriSurfVerts(v11, 4);
      R_AllocStaticTriSurfIndexes(v11, 6);
      verts = v11->verts;
      verts->xyz.z = 0.0;
      verts->xyz.y = 0.0;
      verts->xyz.x = 0.0;
      verts->st.y = 0.0;
      verts->st.x = 0.0;
      verts->normal.z = 0.0;
      verts->normal.y = 0.0;
      verts->normal.x = 0.0;
      verts->tangents[0].z = 0.0;
      verts->tangents[0].y = 0.0;
      verts->tangents[0].x = 0.0;
      verts->tangents[1].z = 0.0;
      verts->tangents[1].y = 0.0;
      verts->tangents[1].x = 0.0;
      verts->color[3] = 0;
      verts->color[2] = 0;
      verts->color[1] = 0;
      verts->color[0] = 0;
      v11->verts->st.x = 0.0;
      v11->verts->st.y = 0.0;
      v14 = v11->verts;
      v14[1].xyz.z = 0.0;
      v14[1].xyz.y = 0.0;
      v14[1].xyz.x = 0.0;
      v14[1].st.y = 0.0;
      v14[1].st.x = 0.0;
      v14[1].normal.z = 0.0;
      v14[1].normal.y = 0.0;
      v14[1].normal.x = 0.0;
      v14[1].tangents[0].z = 0.0;
      v14[1].tangents[0].y = 0.0;
      v14[1].tangents[0].x = 0.0;
      ++v14;
      v14->tangents[1].z = 0.0;
      v14->tangents[1].y = 0.0;
      v14->tangents[1].x = 0.0;
      v14->color[3] = 0;
      v14->color[2] = 0;
      v14->color[1] = 0;
      v14->color[0] = 0;
      v11->verts[1].st.x = 0.0;
      v11->verts[1].st.y = 1.0;
      v15 = (int)&v11->verts[2];
      *(_DWORD *)(v15 + 8) = 0;
      *(_DWORD *)(v15 + 4) = 0;
      *(_DWORD *)v15 = 0;
      *(_DWORD *)(v15 + 60) = 0;
      *(_DWORD *)(v15 + 56) = 0;
      *(_DWORD *)(v15 + 24) = 0;
      *(_DWORD *)(v15 + 20) = 0;
      *(_DWORD *)(v15 + 16) = 0;
      *(_DWORD *)(v15 + 40) = 0;
      *(_DWORD *)(v15 + 36) = 0;
      *(_DWORD *)(v15 + 32) = 0;
      *(_DWORD *)(v15 + 52) = 0;
      *(_DWORD *)(v15 + 48) = 0;
      *(_DWORD *)(v15 + 44) = 0;
      *(_BYTE *)(v15 + 15) = 0;
      *(_BYTE *)(v15 + 14) = 0;
      *(_BYTE *)(v15 + 13) = 0;
      *(_BYTE *)(v15 + 12) = 0;
      v11->verts[2].st.x = 1.0;
      v11->verts[2].st.y = 0.0;
      v16 = v11->verts;
      v16[3].xyz.z = 0.0;
      v16[3].xyz.y = 0.0;
      v16[3].xyz.x = 0.0;
      v16[3].st.y = 0.0;
      v16[3].st.x = 0.0;
      v16[3].normal.z = 0.0;
      v16[3].normal.y = 0.0;
      v16[3].normal.x = 0.0;
      v16 += 3;
      v16->tangents[0].z = 0.0;
      v16->tangents[0].y = 0.0;
      v16->tangents[0].x = 0.0;
      v16->tangents[1].z = 0.0;
      v16->tangents[1].y = 0.0;
      v16->tangents[1].x = 0.0;
      v16->color[3] = 0;
      v16->color[2] = 0;
      v16->color[1] = 0;
      v16->color[0] = 0;
      v11->verts[3].st.x = 1.0;
      v11->verts[3].st.y = 1.0;
      *v11->indexes = 0;
      v11->indexes[1] = 2;
      v11->indexes[2] = 1;
      v11->indexes[3] = 2;
      v11->indexes[4] = 3;
      v11->indexes[5] = 1;
      v11->numVerts = 4;
      v11->numIndexes = 6;
      ((void (__thiscall *)(idRenderModelStatic *, _DWORD, const idMaterial *, srfTriangles_s *, idStr *))v7->AddSurface)(
        v7,
        0,
        tr.defaultMaterial,
        v11,
        surf.mOriginalSurfaceName);
    }
    v17 = renderEntity->shaderParms[9];
    v18 = renderEntity->shaderParms[10];
    target.x = renderEntity->shaderParms[8];
    target.y = v17;
    target.z = v18;
    R_AxisToModelMatrix(&renderEntity->axis, &renderEntity->origin, modelMatrix);
    R_GlobalPointToLocal(modelMatrix, &viewDef->renderView.vieworg, &localView);
    R_GlobalPointToLocal(modelMatrix, &target, &localTarget);
    major = localTarget;
    mid_8a = localTarget.z * 0.5;
    *(float *)&surf.id = localTarget.x * 0.5 - localView.x;
    v19 = localTarget.y * 0.5 - localView.y;
    v20 = mid_8a - localView.z;
    mid = localTarget.y * v20 - localTarget.z * v19;
    mid_4 = localTarget.z * *(float *)&surf.id - v20 * localTarget.x;
    v21 = v19 * localTarget.x - localTarget.y * *(float *)&surf.id;
    mid_8 = v21;
    v22 = v21 * mid_8 + mid_4 * mid_4 + mid * mid;
    if ( v22 != 0.0 )
    {
      v23 = 1.0 / sqrt(v22);
      mid = mid * v23;
      mid_4 = mid_4 * v23;
      mid_8 = mid_8 * v23;
    }
    if ( renderEntity->shaderParms[11] != 0.0 )
    {
      v24 = renderEntity->shaderParms[11] * 0.5;
      mid = mid * v24;
      mid_4 = mid_4 * v24;
      mid_8 = mid_8 * v24;
    }
    v41 = renderEntity->shaderParms[0] * 255.0;
    v53 = (int)v41;
    v42 = renderEntity->shaderParms[1] * 255.0;
    v51 = (int)v42;
    v43 = renderEntity->shaderParms[2] * 255.0;
    v45 = (int)v43;
    v52 = renderEntity->shaderParms[3] * 255.0;
    v44 = (int)v52;
    p_x = &v11->verts->xyz.x;
    *p_x = mid;
    p_x[1] = mid_4;
    p_x[2] = mid_8;
    *(float *)&surf.geometry = -mid_8;
    v26 = v53;
    v27 = v51;
    v11->verts->color[0] = v53;
    v11->verts->color[1] = v27;
    v11->verts->color[2] = v45;
    geometry = surf.geometry;
    v11->verts->color[3] = v44;
    v29 = v11->verts;
    v29[1].xyz.x = -mid;
    LODWORD(v29[1].xyz.z) = geometry;
    v29[1].xyz.y = -mid_4;
    v11->verts[1].color[0] = v26;
    v11->verts[1].color[1] = v27;
    v11->verts[1].color[2] = v45;
    v11->verts[1].color[3] = v44;
    v30 = (int)&v11->verts[2];
    *(float *)&surf.geometry = localTarget.z + mid_8;
    v31 = localTarget.x + mid;
    v32 = localTarget.y + mid_4;
    *(_DWORD *)(v30 + 8) = surf.geometry;
    *(float *)v30 = v31;
    *(float *)(v30 + 4) = v32;
    v11->verts[2].color[0] = v26;
    v11->verts[2].color[1] = v27;
    v11->verts[2].color[2] = v45;
    v11->verts[2].color[3] = v44;
    v33 = localTarget.x - mid;
    v34 = (int)&v11->verts[3];
    v35 = localTarget.y - mid_4;
    *(float *)&surf.geometry = localTarget.z - mid_8;
    *(_DWORD *)(v34 + 8) = surf.geometry;
    *(float *)v34 = v33;
    *(float *)(v34 + 4) = v35;
    v11->verts[3].color[0] = v26;
    v11->verts[3].color[1] = v27;
    v11->verts[3].color[2] = v45;
    v11->verts[3].color[3] = v44;
    R_BoundTriSurf(v11);
    v7->bounds.b[0].x = v11->bounds.b[0].x;
    v7->bounds.b[0].y = v11->bounds.b[0].y;
    v7->bounds.b[0].z = v11->bounds.b[0].z;
    v7->bounds.b[1].x = v11->bounds.b[1].x;
    v7->bounds.b[1].y = v11->bounds.b[1].y;
    v7->bounds.b[1].z = v11->bounds.b[1].z;
    return v7;
  }
  else
  {
    if ( v6 )
      ((void (__thiscall *)(idRenderModel *, int))v6->~idRenderModel)(v6, 1);
    return 0;
  }
}

// FUNC: public: virtual class idBounds __thiscall idRenderModelBeam::Bounds(struct renderEntity_s const *)const
idBounds *__thiscall idRenderModelBeam::Bounds(
        idRenderModelBeam *this,
        idBounds *result,
        const renderEntity_s *renderEntity)
{
  float v3; // edx
  float v4; // eax
  double v5; // st7
  idBounds *v6; // eax
  idVec3 localTarget; // [esp+4h] [ebp-70h] BYREF
  idVec3 target; // [esp+10h] [ebp-64h] BYREF
  idBounds b; // [esp+1Ch] [ebp-58h] BYREF
  float modelMatrix[16]; // [esp+34h] [ebp-40h] BYREF

  memset(&b, 0, sizeof(b));
  if ( renderEntity )
  {
    v3 = renderEntity->shaderParms[9];
    v4 = renderEntity->shaderParms[10];
    target.x = renderEntity->shaderParms[8];
    target.y = v3;
    target.z = v4;
    R_AxisToModelMatrix(&renderEntity->axis, &renderEntity->origin, modelMatrix);
    R_GlobalPointToLocal(modelMatrix, &target, &localTarget);
    if ( localTarget.x < 0.0 )
      b.b[0].x = localTarget.x;
    if ( localTarget.x > 0.0 )
      b.b[1].x = localTarget.x;
    if ( localTarget.y < 0.0 )
      b.b[0].y = localTarget.y;
    if ( localTarget.y > 0.0 )
      b.b[1].y = localTarget.y;
    if ( localTarget.z < 0.0 )
      b.b[0].z = localTarget.z;
    if ( localTarget.z > 0.0 )
      b.b[1].z = localTarget.z;
    if ( renderEntity->shaderParms[11] != 0.0 )
    {
      v5 = renderEntity->shaderParms[11] * 0.5;
      b.b[0].x = b.b[0].x - v5;
      b.b[0].y = b.b[0].y - v5;
      b.b[0].z = b.b[0].z - v5;
      b.b[1].x = b.b[1].x + v5;
      b.b[1].y = b.b[1].y + v5;
      b.b[1].z = b.b[1].z + v5;
    }
  }
  else
  {
    b.b[0].x = -8.0;
    b.b[0].y = -8.0;
    b.b[0].z = -8.0;
    b.b[1].x = 8.0;
    b.b[1].y = 8.0;
    b.b[1].z = 8.0;
  }
  v6 = result;
  *result = b;
  return v6;
}
