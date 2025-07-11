
// FUNC: public: virtual class idRenderModel * __thiscall idRenderModelSprite::InstantiateDynamicModel(struct renderEntity_s const *,struct viewDef_s const *,class idRenderModel *,unsigned int)
idRenderModelStatic *__thiscall idRenderModelSprite::InstantiateDynamicModel(
        idRenderModelSprite *this,
        const renderEntity_s *renderEntity,
        const viewDef_s *viewDef,
        idRenderModel *cachedModel,
        unsigned int __formal)
{
  idRenderModel *v6; // ecx
  idRenderModelStatic *v8; // edi
  srfTriangles_s *v9; // esi
  idDrawVert *verts; // eax
  _DWORD *p_x; // eax
  _DWORD *v12; // eax
  _DWORD *v13; // eax
  int v14; // eax
  _DWORD *v15; // eax
  _DWORD *v16; // eax
  _DWORD *v17; // eax
  idDrawVert *v18; // eax
  _DWORD *v19; // eax
  _DWORD *v20; // eax
  _DWORD *v21; // eax
  int v22; // eax
  _DWORD *v23; // eax
  _DWORD *v24; // eax
  _DWORD *v25; // eax
  idDrawVert *v26; // eax
  double v27; // st7
  double v28; // st6
  unsigned __int8 v29; // dl
  idDrawVert *v30; // eax
  int v31; // eax
  idDrawVert *v32; // eax
  int v34; // [esp+18h] [ebp-18h]
  int v35; // [esp+1Ch] [ebp-14h]
  float v36; // [esp+1Ch] [ebp-14h]
  float up_8; // [esp+28h] [ebp-8h]
  float renderEntitya; // [esp+34h] [ebp+4h]
  const renderEntity_s *renderEntityb; // [esp+34h] [ebp+4h]
  float viewDefa; // [esp+38h] [ebp+8h]
  float cachedModela; // [esp+3Ch] [ebp+Ch]
  float cachedModelb; // [esp+3Ch] [ebp+Ch]
  idRenderModel *cachedModelc; // [esp+3Ch] [ebp+Ch]

  v6 = cachedModel;
  if ( cachedModel && !r_useCachedDynamicModels.internalVar->integerValue )
  {
    ((void (__thiscall *)(idRenderModel *, int))cachedModel->~idRenderModel)(cachedModel, 1);
    v6 = 0;
  }
  if ( renderEntity && viewDef )
  {
    if ( v6 )
    {
      v8 = (idRenderModelStatic *)v6;
      v9 = *(srfTriangles_s **)(((int (__stdcall *)(_DWORD))v6->Surface)(0) + 8);
    }
    else
    {
      v8 = NewRenderModel<idRenderModelStatic>(this);
      v8->InitEmpty(v8, sprite_SnapshotName);
      v9 = R_AllocStaticTriSurf();
      R_AllocStaticTriSurfVerts(v9, 4);
      R_AllocStaticTriSurfIndexes(v9, 6);
      verts = v9->verts;
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
      p_x = (_DWORD *)&v9->verts->xyz.x;
      p_x[5] = 0;
      p_x[6] = 0;
      p_x[4] = 1065353216;
      v12 = (_DWORD *)&v9->verts->xyz.x;
      v12[8] = 0;
      v12[9] = 1065353216;
      v12[10] = 0;
      v13 = (_DWORD *)&v9->verts->xyz.x;
      v13[11] = 0;
      v13[12] = 0;
      v13[13] = 1065353216;
      v9->verts->st.x = 0.0;
      v9->verts->st.y = 0.0;
      v14 = (int)&v9->verts[1];
      *(_DWORD *)(v14 + 8) = 0;
      *(_DWORD *)(v14 + 4) = 0;
      *(_DWORD *)v14 = 0;
      *(_DWORD *)(v14 + 60) = 0;
      *(_DWORD *)(v14 + 56) = 0;
      *(_DWORD *)(v14 + 24) = 0;
      *(_DWORD *)(v14 + 20) = 0;
      *(_DWORD *)(v14 + 16) = 0;
      *(_DWORD *)(v14 + 40) = 0;
      *(_DWORD *)(v14 + 36) = 0;
      *(_DWORD *)(v14 + 32) = 0;
      *(_DWORD *)(v14 + 52) = 0;
      *(_DWORD *)(v14 + 48) = 0;
      *(_DWORD *)(v14 + 44) = 0;
      *(_BYTE *)(v14 + 15) = 0;
      *(_BYTE *)(v14 + 14) = 0;
      *(_BYTE *)(v14 + 13) = 0;
      *(_BYTE *)(v14 + 12) = 0;
      v15 = (_DWORD *)&v9->verts[1].normal.x;
      *v15 = 1065353216;
      v15[1] = 0;
      v15[2] = 0;
      v16 = (_DWORD *)&v9->verts->xyz.x;
      v16[24] = 0;
      v16[25] = 1065353216;
      v16[26] = 0;
      v17 = (_DWORD *)&v9->verts->xyz.x;
      v17[27] = 0;
      v17[28] = 0;
      v17[29] = 1065353216;
      v9->verts[1].st.x = 1.0;
      v9->verts[1].st.y = 0.0;
      v18 = v9->verts;
      v18[2].xyz.z = 0.0;
      v18[2].xyz.y = 0.0;
      v18[2].xyz.x = 0.0;
      v18[2].st.y = 0.0;
      v18[2].st.x = 0.0;
      v18[2].normal.z = 0.0;
      v18[2].normal.y = 0.0;
      v18[2].normal.x = 0.0;
      v18[2].tangents[0].z = 0.0;
      v18[2].tangents[0].y = 0.0;
      v18[2].tangents[0].x = 0.0;
      v18[2].tangents[1].z = 0.0;
      v18[2].tangents[1].y = 0.0;
      v18[2].tangents[1].x = 0.0;
      v18[2].color[3] = 0;
      v18[2].color[2] = 0;
      v18[2].color[1] = 0;
      v18[2].color[0] = 0;
      v19 = (_DWORD *)&v9->verts->xyz.x;
      v19[36] = 1065353216;
      v19[37] = 0;
      v19[38] = 0;
      v20 = (_DWORD *)&v9->verts->xyz.x;
      v20[40] = 0;
      v20[41] = 1065353216;
      v20[42] = 0;
      v21 = (_DWORD *)&v9->verts->xyz.x;
      v21[43] = 0;
      v21[44] = 0;
      v21[45] = 1065353216;
      v9->verts[2].st.x = 1.0;
      v9->verts[2].st.y = 1.0;
      v22 = (int)&v9->verts[3];
      *(_DWORD *)(v22 + 8) = 0;
      *(_DWORD *)(v22 + 4) = 0;
      *(_DWORD *)v22 = 0;
      *(_DWORD *)(v22 + 60) = 0;
      *(_DWORD *)(v22 + 56) = 0;
      *(_DWORD *)(v22 + 24) = 0;
      *(_DWORD *)(v22 + 20) = 0;
      *(_DWORD *)(v22 + 16) = 0;
      *(_DWORD *)(v22 + 40) = 0;
      *(_DWORD *)(v22 + 36) = 0;
      *(_DWORD *)(v22 + 32) = 0;
      *(_DWORD *)(v22 + 52) = 0;
      *(_DWORD *)(v22 + 48) = 0;
      *(_DWORD *)(v22 + 44) = 0;
      *(_BYTE *)(v22 + 15) = 0;
      *(_BYTE *)(v22 + 14) = 0;
      *(_BYTE *)(v22 + 13) = 0;
      *(_BYTE *)(v22 + 12) = 0;
      v23 = (_DWORD *)&v9->verts[3].normal.x;
      *v23 = 1065353216;
      v23[1] = 0;
      v23[2] = 0;
      v24 = (_DWORD *)&v9->verts[3].tangents[0].x;
      *v24 = 0;
      v24[1] = 1065353216;
      v24[2] = 0;
      v25 = (_DWORD *)&v9->verts->xyz.x;
      v25[61] = 1065353216;
      v25[59] = 0;
      v25[60] = 0;
      v9->verts[3].st.x = 0.0;
      v9->verts[3].st.y = 1.0;
      *v9->indexes = 0;
      v9->indexes[1] = 1;
      v9->indexes[2] = 3;
      v9->indexes[3] = 1;
      v9->indexes[4] = 2;
      v9->indexes[5] = 3;
      v9->numVerts = 4;
      v9->numIndexes = 6;
      ((void (__thiscall *)(idRenderModelStatic *, _DWORD, const idMaterial *, srfTriangles_s *))v8->AddSurface)(
        v8,
        0,
        tr.defaultMaterial,
        v9);
    }
    cachedModela = renderEntity->shaderParms[0] * 255.0;
    v34 = (int)cachedModela;
    cachedModelb = renderEntity->shaderParms[1] * 255.0;
    v35 = (int)cachedModelb;
    renderEntitya = renderEntity->shaderParms[2] * 255.0;
    cachedModelc = (idRenderModel *)(int)renderEntitya;
    viewDefa = renderEntity->shaderParms[3] * 255.0;
    renderEntityb = (const renderEntity_s *)(int)viewDefa;
    v26 = v9->verts;
    v27 = renderEntity->shaderParms[8] * 0.5;
    v28 = renderEntity->shaderParms[9];
    v26->xyz.x = 0.0;
    up_8 = v28 * 0.5;
    v26->xyz.y = v27;
    v26->xyz.z = up_8;
    v9->verts->color[0] = v34;
    v29 = v35;
    v9->verts->color[1] = v35;
    v9->verts->color[2] = (unsigned __int8)cachedModelc;
    v9->verts->color[3] = (unsigned __int8)renderEntityb;
    v30 = v9->verts;
    v30[1].xyz.y = -v27;
    v30[1].xyz.x = 0.0;
    v30[1].xyz.z = up_8;
    v9->verts[1].color[0] = v34;
    v9->verts[1].color[1] = v35;
    v36 = -up_8;
    v9->verts[1].color[2] = (unsigned __int8)cachedModelc;
    v9->verts[1].color[3] = (unsigned __int8)renderEntityb;
    v31 = (int)&v9->verts[2];
    *(_DWORD *)v31 = 0;
    *(float *)(v31 + 4) = -v27;
    *(float *)(v31 + 8) = v36;
    v9->verts[2].color[0] = v34;
    v9->verts[2].color[1] = v29;
    v9->verts[2].color[2] = (unsigned __int8)cachedModelc;
    v9->verts[2].color[3] = (unsigned __int8)renderEntityb;
    v32 = v9->verts;
    v32[3].xyz.y = v27;
    v32 += 3;
    v32->xyz.x = 0.0;
    v32->xyz.z = v36;
    v9->verts[3].color[0] = v34;
    v9->verts[3].color[1] = v29;
    v9->verts[3].color[2] = (unsigned __int8)cachedModelc;
    v9->verts[3].color[3] = (unsigned __int8)renderEntityb;
    R_BoundTriSurf(v9);
    v8->bounds.b[0].x = v9->bounds.b[0].x;
    v8->bounds.b[0].y = v9->bounds.b[0].y;
    v8->bounds.b[0].z = v9->bounds.b[0].z;
    v8->bounds.b[1].x = v9->bounds.b[1].x;
    v8->bounds.b[1].y = v9->bounds.b[1].y;
    v8->bounds.b[1].z = v9->bounds.b[1].z;
    return v8;
  }
  else
  {
    if ( v6 )
      ((void (__thiscall *)(idRenderModel *, int))v6->~idRenderModel)(v6, 1);
    return 0;
  }
}

// FUNC: public: virtual class idBounds __thiscall idRenderModelSprite::Bounds(struct renderEntity_s const *)const
idBounds *__thiscall idRenderModelSprite::Bounds(
        idRenderModelSprite *this,
        idBounds *result,
        const renderEntity_s *renderEntity)
{
  double v3; // st7
  double v4; // st6
  double v5; // st7
  idBounds *v6; // eax
  idBounds b; // [esp+0h] [ebp-18h]
  float renderEntitya; // [esp+20h] [ebp+8h]

  if ( renderEntity )
  {
    v3 = renderEntity->shaderParms[9];
    v4 = renderEntity->shaderParms[8];
    renderEntitya = renderEntity->shaderParms[8];
    if ( v4 > v3 )
      v3 = renderEntitya;
    v5 = v3 * 0.5;
    b.b[0].x = -v5;
    b.b[0].y = b.b[0].x;
    b.b[0].z = b.b[0].x;
    b.b[1].x = v5;
    b.b[1].y = v5;
    b.b[1].z = v5;
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
