
// FUNC: public: static void __cdecl idRenderModelOverlay::RemoveOverlaySurfacesFromModel(class idRenderModel *)
void __cdecl idRenderModelOverlay::RemoveOverlaySurfacesFromModel(idRenderModelStatic *baseModel)
{
  idRenderModelStatic::DeleteSurfacesWithNegativeId(baseModel);
  baseModel->overlaysAdded = 0;
}

// FUNC: public: static class idRenderModelOverlay * __cdecl idRenderModelOverlay::Alloc(void)
idRenderModelOverlay *__cdecl idRenderModelOverlay::Alloc()
{
  idRenderModelOverlay *result; // eax

  result = (idRenderModelOverlay *)Memory::Allocate(0x10u);
  if ( !result )
    return 0;
  result->materials.granularity = 16;
  result->materials.list = 0;
  result->materials.num = 0;
  result->materials.size = 0;
  return result;
}

// FUNC: public: void __thiscall idRenderModelOverlay::CreateOverlay(class idRenderModel const *,class idPlane const * const,class idMaterial const *)
void __thiscall idRenderModelOverlay::CreateOverlay(
        idRenderModelOverlay *this,
        idRenderModel *model,
        const idPlane *localTextureAxis,
        const idMaterial *mtr)
{
  const idRenderModel *v4; // esi
  idRenderModel_vtbl *v5; // eax
  idRenderModelOverlay *v6; // ebx
  int v7; // edi
  srfTriangles_s *geometry; // eax
  int v9; // eax
  idRenderModel_vtbl *v10; // edx
  int v11; // eax
  void *v12; // esp
  int v13; // eax
  void *v14; // esp
  idRenderModel_vtbl *v15; // eax
  int *v16; // edi
  const modelSurface_s *v17; // eax
  int v18; // ebx
  const idMaterial *shader; // eax
  double v20; // st7
  double v21; // st7
  rvMesh *v22; // ecx
  int v23; // esi
  int v24; // eax
  void *v25; // esp
  unsigned __int8 *v26; // eax
  int v27; // eax
  void *v28; // esp
  int v29; // eax
  void *v30; // esp
  int v31; // ecx
  bool v32; // cc
  int v33; // eax
  int v34; // eax
  bool v35; // zf
  overlayVertex_t *v36; // edx
  int v37; // eax
  overlayVertex_t *v38; // ecx
  int v39; // eax
  overlayVertex_t *v40; // edx
  int *v41; // edi
  const modelSurface_s *v42; // eax
  void *v43; // eax
  void *v44; // eax
  idRenderModelOverlay *v45; // ebx
  int num; // eax
  int v47; // ecx
  overlayMaterial_t **v48; // eax
  int *p_num; // esi
  int v50; // eax
  int n; // eax
  int v52; // eax
  int v53; // ecx
  int v54; // eax
  int ii; // eax
  _DWORD *v56; // eax
  _DWORD *v57; // esi
  int v58; // eax
  int i; // eax
  int v60; // eax
  int v61; // ecx
  int v62; // eax
  int j; // eax
  int granularity; // eax
  int k; // eax
  int size; // ecx
  int v67; // ecx
  overlayMaterial_t **list; // edi
  int m; // eax
  idRenderModel_vtbl *v70; // edx
  int v71; // edi
  int jj; // edi
  void ***v73; // ecx
  void **v74; // esi
  overlayMaterial_t *v75; // eax
  int v76; // ecx
  idList<overlaySurface_t *> *p_surfaces; // eax
  int v78; // edx
  int v79; // ecx
  overlaySurface_t **v80; // edx
  overlaySurface_t *v81; // esi
  overlaySurface_t **v82; // edx
  int v83; // [esp+0h] [ebp-48h] BYREF
  int v84; // [esp+8h] [ebp-40h] BYREF
  void *ptr; // [esp+Ch] [ebp-3Ch] BYREF
  const modelSurface_s *surf; // [esp+10h] [ebp-38h]
  int v87; // [esp+14h] [ebp-34h]
  idRenderModelOverlay *v88; // [esp+18h] [ebp-30h]
  unsigned __int8 *cullBits; // [esp+1Ch] [ebp-2Ch]
  int maxIndexes; // [esp+20h] [ebp-28h]
  overlayVertex_t *overlayVerts; // [esp+24h] [ebp-24h]
  int index; // [esp+28h] [ebp-20h]
  int ind; // [esp+2Ch] [ebp-1Ch]
  int surfNum; // [esp+30h] [ebp-18h]
  int numIndexes; // [esp+34h] [ebp-14h] BYREF
  int numVerts[4]; // [esp+38h] [ebp-10h] BYREF

  v4 = model;
  v5 = model->__vftable;
  v6 = this;
  v7 = 0;
  v88 = this;
  maxIndexes = 0;
  surfNum = 0;
  if ( v5->NumSurfaces(model) > 0 )
  {
    do
    {
      geometry = model->Surface(model, surfNum)->geometry;
      if ( geometry->numVerts > v7 )
        v7 = geometry->numVerts;
      v9 = geometry->numIndexes;
      if ( v9 > maxIndexes )
        maxIndexes = v9;
      v10 = model->__vftable;
      ++surfNum;
    }
    while ( surfNum < v10->NumSurfaces(model) );
  }
  v11 = 12 * v7 + 3;
  LOBYTE(v11) = v11 & 0xFC;
  v12 = alloca(v11);
  v13 = 4 * maxIndexes + 18;
  LOBYTE(v13) = v13 & 0xFC;
  overlayVerts = (overlayVertex_t *)&v83;
  v14 = alloca(v13);
  v15 = model->__vftable;
  v16 = &v84;
  maxIndexes = (int)&v84;
  surfNum = 0;
  if ( v15->NumBaseSurfaces(model) > 0 )
  {
    while ( 1 )
    {
      v17 = v4->Surface(v4, surfNum);
      v18 = (int)v17->geometry;
      surf = v17;
      v87 = v18;
      if ( v18 )
      {
        shader = v17->shader;
        if ( shader )
        {
          if ( shader->allowOverlays )
          {
            v20 = idBounds::PlaneDistance((idBounds *)v18, localTextureAxis);
            if ( v20 >= 0.0 && v20 <= 1.0 )
            {
              v21 = idBounds::PlaneDistance((idBounds *)v18, localTextureAxis + 1);
              if ( v21 >= 0.0 && v21 <= 1.0 )
              {
                numVerts[0] = 0;
                numIndexes = 0;
                v22 = *(rvMesh **)(v18 + 136);
                if ( v22 )
                {
                  rvMesh::CreateOverlayTriangles(
                    v22,
                    overlayVerts,
                    numVerts,
                    v16,
                    &numIndexes,
                    localTextureAxis,
                    *(const rvSilTraceVertT **)(v18 + 44));
                }
                else
                {
                  v23 = *(_DWORD *)(v18 + 36);
                  v24 = v23 + 18;
                  LOBYTE(v24) = (v23 + 18) & 0xFC;
                  v25 = alloca(v24);
                  v26 = (unsigned __int8 *)&ptr + 3;
                  LOBYTE(v26) = ((unsigned __int8)&ptr + 3) & 0xF0;
                  cullBits = v26;
                  v27 = 8 * v23 + 18;
                  LOBYTE(v27) = v27 & 0xFC;
                  v28 = alloca(v27);
                  SIMDProcessor->OverlayPointCull(
                    SIMDProcessor,
                    cullBits,
                    (idVec2 *)&v84,
                    localTextureAxis,
                    *(const idDrawVert **)(v18 + 40),
                    v23);
                  index = 4 * *(_DWORD *)(v18 + 36);
                  v29 = index + 18;
                  LOBYTE(v29) = (index + 18) & 0xFC;
                  v30 = alloca(v29);
                  SIMDProcessor->Memset(SIMDProcessor, &v84, -1, index);
                  v31 = 0;
                  v32 = *(_DWORD *)(v18 + 52) <= 0;
                  index = 0;
                  if ( !v32 )
                  {
                    do
                    {
                      v33 = *(_DWORD *)(v18 + 56);
                      ind = *(_DWORD *)(v33 + 4 * v31);
                      if ( ((unsigned __int8)(cullBits[*(_DWORD *)(v33 + 4 * v31 + 4)] & cullBits[*(_DWORD *)(v33 + 4 * v31 + 8)]) & cullBits[ind]) == 0 )
                      {
                        v34 = *(_DWORD *)(*(_DWORD *)(v18 + 56) + 4 * index);
                        v35 = *(&v84 + v34) == -1;
                        ind = v34;
                        if ( v35 )
                        {
                          *(&v84 + v34) = numVerts[0];
                          v36 = overlayVerts;
                          overlayVerts[numVerts[0]].vertexNum = v34;
                          LODWORD(v36[numVerts[0]].st[0]) = *(&v84 + 2 * v34);
                          LODWORD(v36[numVerts[0]++].st[1]) = *(&v84 + 2 * ind + 1);
                          v34 = ind;
                        }
                        *(_DWORD *)(maxIndexes + 4 * numIndexes++) = *(&v84 + v34);
                        v37 = *(_DWORD *)(*(_DWORD *)(v18 + 56) + 4 * index + 4);
                        if ( *(&v84 + v37) == -1 )
                        {
                          *(&v84 + v37) = numVerts[0];
                          v38 = overlayVerts;
                          overlayVerts[numVerts[0]].vertexNum = v37;
                          LODWORD(v38[numVerts[0]].st[0]) = *(&v84 + 2 * v37);
                          LODWORD(v38[numVerts[0]++].st[1]) = *(&v84 + 2 * v37 + 1);
                          v18 = v87;
                        }
                        *(_DWORD *)(maxIndexes + 4 * numIndexes++) = *(&v84 + v37);
                        v39 = *(_DWORD *)(*(_DWORD *)(v18 + 56) + 4 * index + 8);
                        v35 = *(&v84 + v39) == -1;
                        ind = v39;
                        if ( v35 )
                        {
                          *(&v84 + v39) = numVerts[0];
                          v40 = overlayVerts;
                          overlayVerts[numVerts[0]].vertexNum = v39;
                          LODWORD(v40[numVerts[0]].st[0]) = *(&v84 + 2 * v39);
                          LODWORD(v40[numVerts[0]++].st[1]) = *(&v84 + 2 * ind + 1);
                          v39 = ind;
                        }
                        *(_DWORD *)(maxIndexes + 4 * numIndexes++) = *(&v84 + v39);
                      }
                      v31 = index + 3;
                      v32 = index + 3 < *(_DWORD *)(v18 + 52);
                      index += 3;
                    }
                    while ( v32 );
                  }
                }
                if ( numIndexes )
                {
                  v41 = (int *)Mem_Alloc(28, 0xEu);
                  v42 = surf;
                  *v41 = surfNum;
                  v41[1] = v42->id;
                  v41[2] = v42->geometry->numVerts;
                  v43 = Mem_Alloc(12 * numVerts[0], 0xEu);
                  v41[6] = (int)v43;
                  SIMDProcessor->Memcpy(SIMDProcessor, v43, overlayVerts, 12 * numVerts[0]);
                  v41[5] = numVerts[0];
                  v44 = Mem_Alloc(4 * numIndexes, 0xEu);
                  v41[4] = (int)v44;
                  SIMDProcessor->Memcpy(SIMDProcessor, v44, (const void *)maxIndexes, 4 * numIndexes);
                  v45 = v88;
                  v41[3] = numIndexes;
                  num = v45->materials.num;
                  v47 = 0;
                  v32 = v45->materials.num <= 0;
                  index = 0;
                  if ( !v32 )
                  {
                    index = (int)v45->materials.list;
                    do
                    {
                      if ( **(const idMaterial ***)index == mtr )
                        break;
                      index += 4;
                      ++v47;
                    }
                    while ( v47 < v45->materials.num );
                    index = v47;
                  }
                  if ( v47 >= num )
                  {
                    v56 = Memory::Allocate(0x18u);
                    if ( v56 )
                    {
                      v56[3] = 16;
                      v56[4] = 0;
                      v56[1] = 0;
                      v56[2] = 0;
                      v57 = v56;
                    }
                    else
                    {
                      v57 = 0;
                    }
                    *v57 = mtr;
                    v35 = v57[4] == 0;
                    numVerts[3] = -1;
                    if ( v35 )
                    {
                      v58 = v57[3];
                      if ( v58 > 0 )
                      {
                        if ( v58 != v57[2] )
                        {
                          v32 = v58 < v57[1];
                          v57[2] = v58;
                          if ( v32 )
                            v57[1] = v58;
                          v57[4] = Memory::Allocate(4 * v58);
                          for ( i = 0; i < v57[1]; ++i )
                            *(_DWORD *)(v57[4] + 4 * i) = *(_DWORD *)(4 * i);
                        }
                      }
                      else
                      {
                        v57[4] = 0;
                        v57[1] = 0;
                        v57[2] = 0;
                      }
                    }
                    v60 = v57[2];
                    if ( v57[1] == v60 )
                    {
                      if ( !v57[3] )
                        v57[3] = 16;
                      v61 = v57[3];
                      surf = (const modelSurface_s *)(v61 + v60);
                      v62 = v61 + v60 - (v61 + v60) % v61;
                      if ( v62 > 0 )
                      {
                        if ( v62 != v57[2] )
                        {
                          v32 = v62 < v57[1];
                          index = v57[4];
                          v57[2] = v62;
                          if ( v32 )
                            v57[1] = v62;
                          v57[4] = Memory::Allocate(4 * v62);
                          for ( j = 0; j < v57[1]; ++j )
                            *(_DWORD *)(v57[4] + 4 * j) = *(_DWORD *)(index + 4 * j);
                          if ( index )
                            Memory::Free((void *)index);
                        }
                      }
                      else
                      {
                        if ( v57[4] )
                          Memory::Free((void *)v57[4]);
                        v57[4] = 0;
                        v57[1] = 0;
                        v57[2] = 0;
                      }
                    }
                    *(_DWORD *)(v57[4] + 4 * v57[1]++) = v41;
                    *((_BYTE *)v57 + 20) = 1;
                    if ( !v45->materials.list )
                    {
                      granularity = v45->materials.granularity;
                      if ( granularity > 0 )
                      {
                        if ( granularity != v45->materials.size )
                        {
                          v32 = granularity < v45->materials.num;
                          v45->materials.size = granularity;
                          if ( v32 )
                            v45->materials.num = granularity;
                          v45->materials.list = (overlayMaterial_t **)Memory::Allocate(4 * granularity);
                          for ( k = 0; k < v45->materials.num; ++k )
                            v45->materials.list[k] = *(overlayMaterial_t **)(4 * k);
                        }
                      }
                      else
                      {
                        v45->materials.list = 0;
                        v45->materials.num = 0;
                        v45->materials.size = 0;
                      }
                    }
                    size = v45->materials.size;
                    if ( v45->materials.num != size )
                      goto LABEL_106;
                    if ( !v45->materials.granularity )
                      v45->materials.granularity = 16;
                    v67 = v45->materials.granularity
                        + size
                        - (v45->materials.granularity + size) % v45->materials.granularity;
                    if ( v67 > 0 )
                    {
                      if ( v67 != v45->materials.size )
                      {
                        v32 = v67 < v45->materials.num;
                        list = v45->materials.list;
                        v45->materials.size = v67;
                        if ( v32 )
                          v45->materials.num = v67;
                        v45->materials.list = (overlayMaterial_t **)Memory::Allocate(4 * v67);
                        for ( m = 0; m < v45->materials.num; ++m )
                          v45->materials.list[m] = list[m];
                        if ( list )
                          Memory::Free(list);
                      }
LABEL_106:
                      v45->materials.list[v45->materials.num++] = (overlayMaterial_t *)v57;
                      goto LABEL_107;
                    }
                    if ( v45->materials.list )
                      Memory::Free(v45->materials.list);
                    v45->materials.num = 0;
                    v45->materials.list = 0;
                    v45->materials.size = 0;
                    MEMORY[0] = v57;
                    ++v45->materials.num;
                  }
                  else
                  {
                    v48 = v45->materials.list;
                    p_num = &v48[index]->surfaces.num;
                    if ( !v48[index]->surfaces.list )
                    {
                      v50 = v48[index]->surfaces.granularity;
                      if ( v50 > 0 )
                      {
                        if ( v50 != p_num[1] )
                        {
                          v32 = v50 < *p_num;
                          p_num[1] = v50;
                          if ( v32 )
                            *p_num = v50;
                          p_num[3] = (int)Memory::Allocate(4 * v50);
                          for ( n = 0; n < *p_num; ++n )
                            *(_DWORD *)(p_num[3] + 4 * n) = *(_DWORD *)(4 * n);
                        }
                      }
                      else
                      {
                        p_num[3] = 0;
                        *p_num = 0;
                        p_num[1] = 0;
                      }
                    }
                    v52 = p_num[1];
                    if ( *p_num == v52 )
                    {
                      if ( !p_num[2] )
                        p_num[2] = 16;
                      v53 = p_num[2];
                      surf = (const modelSurface_s *)(v53 + v52);
                      v54 = v53 + v52 - (v53 + v52) % v53;
                      if ( v54 > 0 )
                      {
                        if ( v54 != p_num[1] )
                        {
                          v32 = v54 < *p_num;
                          ind = p_num[3];
                          p_num[1] = v54;
                          if ( v32 )
                            *p_num = v54;
                          p_num[3] = (int)Memory::Allocate(4 * v54);
                          for ( ii = 0; ii < *p_num; ++ii )
                            *(_DWORD *)(p_num[3] + 4 * ii) = *(_DWORD *)(ind + 4 * ii);
                          if ( ind )
                            Memory::Free((void *)ind);
                        }
                      }
                      else
                      {
                        if ( p_num[3] )
                          Memory::Free((void *)p_num[3]);
                        p_num[3] = 0;
                        *p_num = 0;
                        p_num[1] = 0;
                      }
                    }
                    *(_DWORD *)(p_num[3] + 4 * (*p_num)++) = v41;
                    v45->materials.list[index]->modified = 1;
                  }
                }
              }
            }
          }
        }
      }
LABEL_107:
      v4 = model;
      v70 = model->__vftable;
      v71 = ++surfNum;
      if ( v71 >= v70->NumBaseSurfaces(model) )
      {
        v6 = v88;
        break;
      }
      v16 = (int *)maxIndexes;
    }
  }
  for ( jj = 0; jj < v6->materials.num; ++jj )
  {
    for ( ; v6->materials.list[jj]->surfaces.num > 4; v6->materials.list[jj]->modified = 1 )
    {
      v73 = (void ***)v6->materials.list[jj]->surfaces.list;
      v74 = *v73;
      if ( (*v73)[6] )
        Mem_Free((*v73)[6]);
      if ( v74[4] )
        Mem_Free(v74[4]);
      Mem_Free(v74);
      v75 = v6->materials.list[jj];
      v76 = v75->surfaces.num;
      p_surfaces = &v75->surfaces;
      if ( v76 > 0 )
      {
        v78 = v76 - 1;
        v79 = 0;
        for ( p_surfaces->num = v78; v79 < p_surfaces->num; *v82 = v81 )
        {
          v80 = p_surfaces->list;
          v81 = v80[v79 + 1];
          v82 = &v80[v79++];
        }
      }
    }
  }
}

// FUNC: public: void __thiscall idRenderModelOverlay::AddOverlaySurfacesToModel(class idRenderModel *)
void __thiscall idRenderModelOverlay::AddOverlaySurfacesToModel(
        idRenderModelOverlay *this,
        idRenderModelStatic *baseModel)
{
  idRenderModelStatic *v2; // edi
  int num; // edx
  int v5; // esi
  int v6; // ebx
  overlaySurface_t **list; // ecx
  int v8; // ebp
  int granularity; // eax
  bool v10; // cc
  modelSurface_s *v11; // eax
  int v12; // ecx
  _DWORD *v13; // eax
  _DWORD *v14; // edx
  int size; // ecx
  int v16; // edx
  int v17; // eax
  modelSurface_s *v18; // ebp
  modelSurface_s *v19; // eax
  int v20; // ecx
  int v21; // eax
  modelSurface_s *v22; // esi
  idStr *mOriginalSurfaceName; // edx
  srfTriangles_s *v24; // eax
  srfTriangles_s *v25; // eax
  overlayMaterial_t **v26; // eax
  overlayMaterial_t *v27; // edx
  int v28; // ebx
  overlayMaterial_t **v29; // eax
  overlaySurface_t *v30; // esi
  const modelSurface_s *v31; // eax
  srfTriangles_s *geometry; // ecx
  int v33; // ecx
  int v34; // edx
  srfTriangles_s *v35; // ecx
  rvSilTraceVertT *silTraceVerts; // ebp
  int v37; // eax
  int v38; // edx
  int v39; // edi
  float *v40; // ecx
  overlayVertex_t *v41; // eax
  float v42; // ebx
  overlayVertex_t *v43; // eax
  int vertexNum; // eax
  float x; // ebx
  rvSilTraceVertT *v46; // eax
  idDrawVert *verts; // ebp
  int v48; // edi
  float *v49; // ecx
  overlayVertex_t *v50; // eax
  float v51; // ebx
  overlayVertex_t *v52; // eax
  int v53; // eax
  int v54; // ebx
  int v55; // eax
  rvSilTraceVertT *v56; // ebp
  int v57; // eax
  char *v58; // eax
  int v59; // edx
  int v60; // edi
  float *v61; // ecx
  int v62; // eax
  float v63; // ebx
  rvSilTraceVertT *v64; // eax
  char *v65; // eax
  idDrawVert *v66; // ebp
  int v67; // edx
  int v68; // edi
  _DWORD *v69; // ecx
  int v70; // eax
  int v71; // ebx
  int v72; // eax
  idList<overlaySurface_t *> *p_surfaces; // eax
  int v74; // ecx
  int v75; // ecx
  overlaySurface_t **v76; // edx
  overlaySurface_t *v77; // ebp
  overlaySurface_t **v78; // edx
  int v79; // ecx
  idList<overlaySurface_t *> *v80; // eax
  int v81; // edx
  overlaySurface_t **v82; // edx
  overlaySurface_t *v83; // esi
  overlaySurface_t **v84; // edx
  int k; // [esp+10h] [ebp-28h]
  int numIndexes; // [esp+14h] [ebp-24h]
  int numIndexesa; // [esp+14h] [ebp-24h]
  int numVerts; // [esp+1Ch] [ebp-1Ch]
  srfTriangles_s *newTri; // [esp+20h] [ebp-18h]
  int i; // [esp+24h] [ebp-14h]
  int ia; // [esp+24h] [ebp-14h]
  int id; // [esp+28h] [ebp-10h]
  modelSurface_s *newSurf; // [esp+2Ch] [ebp-Ch]
  const modelSurface_s *baseSurf; // [esp+30h] [ebp-8h]
  const modelSurface_s *baseSurfa; // [esp+30h] [ebp-8h]
  int surfaceNum; // [esp+34h] [ebp-4h] BYREF

  v2 = baseModel;
  if ( baseModel && !baseModel->IsDefaultModel(baseModel) && baseModel->NumSurfaces(baseModel) )
  {
    if ( baseModel->IsDynamicModel(baseModel) )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
        common.type,
        "idRenderModelOverlay::AddOverlaySurfacesToModel: baseModel is not a static model");
    baseModel->overlaysAdded = 0;
    if ( !this->materials.num )
    {
      idRenderModelStatic::DeleteSurfacesWithNegativeId(baseModel);
      return;
    }
    k = 0;
    if ( this->materials.num > 0 )
    {
      for ( id = -1; ; --id )
      {
        num = this->materials.list[k]->surfaces.num;
        v5 = 0;
        v6 = 0;
        numIndexes = 0;
        if ( num > 0 )
        {
          list = this->materials.list[k]->surfaces.list;
          do
          {
            v6 += (*list)->numVerts;
            v5 += (*list++)->numIndexes;
            --num;
          }
          while ( num );
          numIndexes = v5;
        }
        if ( idRenderModelStatic::FindSurfaceWithId(v2, id, &surfaceNum) )
        {
          v8 = (int)&v2->surfaces.list[surfaceNum];
        }
        else
        {
          if ( !v2->surfaces.list )
          {
            granularity = v2->surfaces.granularity;
            if ( granularity > 0 )
            {
              if ( granularity != v2->surfaces.size )
              {
                v10 = granularity < v2->surfaces.num;
                v2->surfaces.size = granularity;
                if ( v10 )
                  v2->surfaces.num = granularity;
                v11 = (modelSurface_s *)Memory::Allocate(16 * granularity);
                v12 = 0;
                v10 = v2->surfaces.num <= 0;
                v2->surfaces.list = v11;
                if ( !v10 )
                {
                  v13 = 0;
                  do
                  {
                    v14 = (_DWORD *)((char *)v13 + (unsigned int)v2->surfaces.list);
                    *v14 = *v13;
                    v14[1] = v13[1];
                    v14[2] = v13[2];
                    ++v12;
                    v14[3] = v13[3];
                    v13 += 4;
                  }
                  while ( v12 < v2->surfaces.num );
                  v5 = numIndexes;
                }
              }
            }
            else
            {
              v2->surfaces.list = 0;
              v2->surfaces.num = 0;
              v2->surfaces.size = 0;
            }
          }
          size = v2->surfaces.size;
          v16 = v2->surfaces.num;
          if ( v16 == size )
          {
            v17 = size + v2->surfaces.granularity;
            if ( v17 > 0 )
            {
              if ( v17 != v2->surfaces.size )
              {
                v18 = v2->surfaces.list;
                i = (int)v18;
                v2->surfaces.size = v17;
                if ( v17 < v16 )
                  v2->surfaces.num = v17;
                v19 = (modelSurface_s *)Memory::Allocate(16 * v17);
                v20 = 0;
                v10 = v2->surfaces.num <= 0;
                v2->surfaces.list = v19;
                if ( !v10 )
                {
                  v21 = 0;
                  do
                  {
                    v22 = &v2->surfaces.list[v21];
                    v22->id = v18[v21].id;
                    v22->shader = v18[v21].shader;
                    v22->geometry = v18[v21].geometry;
                    mOriginalSurfaceName = v18[v21].mOriginalSurfaceName;
                    v18 = (modelSurface_s *)i;
                    ++v20;
                    v22->mOriginalSurfaceName = mOriginalSurfaceName;
                    ++v21;
                  }
                  while ( v20 < v2->surfaces.num );
                  v5 = numIndexes;
                }
                if ( v18 )
                  Memory::Free(v18);
              }
            }
            else
            {
              if ( v2->surfaces.list )
                Memory::Free(v2->surfaces.list);
              v2->surfaces.list = 0;
              v2->surfaces.num = 0;
              v2->surfaces.size = 0;
            }
          }
          v8 = (int)&v2->surfaces.list[v2->surfaces.num++];
          *(_DWORD *)(v8 + 8) = 0;
          *(_DWORD *)(v8 + 4) = this->materials.list[k]->material;
          *(_DWORD *)v8 = id;
        }
        v24 = *(srfTriangles_s **)(v8 + 8);
        newSurf = (modelSurface_s *)v8;
        if ( v24 && v24->numVerts >= v6 && v24->numIndexes >= v5 )
        {
          R_FreeStaticTriSurfVertexCaches(v24);
        }
        else
        {
          R_FreeStaticTriSurf(v24);
          v25 = R_AllocStaticTriSurf();
          *(_DWORD *)(v8 + 8) = v25;
          R_AllocStaticTriSurfVerts(v25, v6);
          R_AllocStaticTriSurfIndexes(*(srfTriangles_s **)(v8 + 8), v5);
          SIMDProcessor->Memset(SIMDProcessor, *(void **)(*(_DWORD *)(v8 + 8) + 40), 0, v6 << 6);
          this->materials.list[k]->modified = 1;
        }
        v26 = this->materials.list;
        newTri = *(srfTriangles_s **)(v8 + 8);
        v27 = v26[k];
        v28 = 0;
        v29 = &v26[k];
        numIndexesa = 0;
        numVerts = 0;
        ia = 0;
        if ( v27->surfaces.num > 0 )
          break;
LABEL_90:
        this->materials.list[k]->modified = 0;
        newTri->numVerts = v28;
        newTri->numIndexes = numIndexesa;
        R_BoundTriSurf(newTri);
        ++v2->overlaysAdded;
        if ( ++k >= this->materials.num )
          return;
      }
      while ( 1 )
      {
        v30 = (*v29)->surfaces.list[ia];
        baseSurf = (const modelSurface_s *)v30->surfaceNum;
        if ( (int)baseSurf >= v2->NumSurfaces(v2)
          || (v31 = v2->Surface(v2, (int)baseSurf), (baseSurfa = v31) == 0)
          || v31->id != v30->surfaceId )
        {
          if ( !idRenderModelStatic::FindSurfaceWithId(v2, v30->surfaceId, &v30->surfaceNum) )
          {
            if ( v30->verts )
              Mem_Free(v30->verts);
            if ( v30->indexes )
              Mem_Free(v30->indexes);
            Mem_Free(v30);
            p_surfaces = &this->materials.list[k]->surfaces;
            if ( ia >= 0 )
            {
              v74 = p_surfaces->num;
              if ( ia < p_surfaces->num )
              {
                v10 = ia < v74 - 1;
                p_surfaces->num = v74 - 1;
                v75 = ia;
                if ( v10 )
                {
                  do
                  {
                    v76 = p_surfaces->list;
                    v77 = v76[v75 + 1];
                    v78 = &v76[v75++];
                    *v78 = v77;
                  }
                  while ( v75 < p_surfaces->num );
                }
              }
            }
            --ia;
            goto LABEL_89;
          }
          v31 = v2->Surface(v2, v30->surfaceNum);
          baseSurfa = v31;
        }
        geometry = v31->geometry;
        if ( geometry->numVerts < v30->surfaceNumVerts )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
            common.type,
            "idRenderModelOverlay::AddOverlaySurfacesToModel: overlay vertex out of range.  Model has probably changed si"
            "nce generating the overlay.");
          if ( v30->verts )
            Mem_Free(v30->verts);
          if ( v30->indexes )
            Mem_Free(v30->indexes);
          Mem_Free(v30);
          v79 = ia;
          v80 = &this->materials.list[k]->surfaces;
          if ( ia >= 0 && ia < v80->num )
          {
            v81 = v80->num - 1;
            v80->num = v81;
            if ( ia < v81 )
            {
              do
              {
                v82 = v80->list;
                v83 = v82[v79 + 1];
                v84 = &v82[v79++];
                *v84 = v83;
              }
              while ( v79 < v80->num );
            }
          }
          idRenderModelStatic::DeleteSurfaceWithId(v2, *(_DWORD *)v8);
          return;
        }
        if ( this->materials.list[k]->modified )
        {
          v33 = 0;
          if ( v30->numIndexes > 0 )
          {
            v34 = numIndexesa;
            do
              newTri->indexes[v34++] = v28 + v30->indexes[v33++];
            while ( v33 < v30->numIndexes );
            v31 = baseSurfa;
          }
          numIndexesa += v30->numIndexes;
          v35 = v31->geometry;
          silTraceVerts = v35->silTraceVerts;
          v37 = (int)&newTri->verts[v28];
          v38 = 0;
          if ( !silTraceVerts )
          {
            verts = v35->verts;
            if ( v30->numVerts > 0 )
            {
              v48 = 0;
              v49 = (float *)(v37 + 60);
              do
              {
                v50 = v30->verts;
                v51 = v50[v48].st[0];
                v52 = &v50[v48];
                *(v49 - 1) = v51;
                *v49 = v52->st[1];
                v53 = v52->vertexNum << 6;
                v54 = *(_DWORD *)((char *)&verts->xyz.x + v53);
                v55 = (int)verts + v53;
                *((_DWORD *)v49 - 15) = v54;
                *(v49 - 14) = *(float *)(v55 + 4);
                *(v49 - 13) = *(float *)(v55 + 8);
                ++v38;
                ++v48;
                v49 += 16;
              }
              while ( v38 < v30->numVerts );
              v2 = baseModel;
              v28 = numVerts;
            }
LABEL_69:
            v28 += v30->numVerts;
            numVerts = v28;
            goto LABEL_89;
          }
          if ( v30->numVerts <= 0 )
            goto LABEL_69;
          v39 = 0;
          v40 = (float *)(v37 + 60);
          do
          {
            v41 = v30->verts;
            v42 = v41[v39].st[0];
            v43 = &v41[v39];
            *(v40 - 1) = v42;
            *v40 = v43->st[1];
            vertexNum = v43->vertexNum;
            x = silTraceVerts[vertexNum].xyzw.x;
            v46 = &silTraceVerts[vertexNum];
            *(v40 - 15) = x;
            *(v40 - 14) = v46->xyzw.y;
            *(v40 - 13) = v46->xyzw.z;
            ++v38;
            ++v39;
            v40 += 16;
          }
          while ( v38 < v30->numVerts );
          v28 = v30->numVerts + numVerts;
          v2 = baseModel;
          numVerts = v28;
        }
        else
        {
          v56 = geometry->silTraceVerts;
          numIndexesa += v30->numIndexes;
          v57 = v28 << 6;
          if ( !v56 )
          {
            v65 = (char *)newTri->verts + v57;
            v66 = geometry->verts;
            v67 = 0;
            if ( v30->numVerts > 0 )
            {
              v68 = 0;
              v69 = v65 + 8;
              do
              {
                v70 = v30->verts[v68].vertexNum << 6;
                v71 = *(_DWORD *)((char *)&v66->xyz.x + v70);
                v72 = (int)v66 + v70;
                *(v69 - 2) = v71;
                *(v69 - 1) = *(_DWORD *)(v72 + 4);
                *v69 = *(_DWORD *)(v72 + 8);
                ++v67;
                ++v68;
                v69 += 16;
              }
              while ( v67 < v30->numVerts );
              v28 = numVerts;
              v2 = baseModel;
            }
LABEL_79:
            v28 += v30->numVerts;
            numVerts = v28;
            goto LABEL_89;
          }
          v58 = (char *)newTri->verts + v57;
          v59 = 0;
          if ( v30->numVerts <= 0 )
            goto LABEL_79;
          v60 = 0;
          v61 = (float *)(v58 + 8);
          do
          {
            v62 = v30->verts[v60].vertexNum;
            v63 = v56[v62].xyzw.x;
            v64 = &v56[v62];
            *(v61 - 2) = v63;
            *(v61 - 1) = v64->xyzw.y;
            *v61 = v64->xyzw.z;
            ++v59;
            ++v60;
            v61 += 16;
          }
          while ( v59 < v30->numVerts );
          v28 = v30->numVerts + numVerts;
          v2 = baseModel;
          numVerts = v28;
        }
LABEL_89:
        v29 = &this->materials.list[k];
        if ( ++ia >= (*v29)->surfaces.num )
          goto LABEL_90;
        v8 = (int)newSurf;
      }
    }
  }
}

// FUNC: public: __thiscall idRenderModelOverlay::~idRenderModelOverlay(void)
void __thiscall idRenderModelOverlay::~idRenderModelOverlay(idRenderModelOverlay *this)
{
  int i; // edi
  int j; // ebp
  overlaySurface_t *v4; // ebx
  overlayMaterial_t *v5; // ebx
  overlaySurface_t **list; // eax
  idList<overlaySurface_t *> *p_surfaces; // ebx
  overlayMaterial_t *v8; // ebx

  for ( i = 0; i < this->materials.num; ++i )
  {
    for ( j = 0; j < this->materials.list[i]->surfaces.num; ++j )
    {
      v4 = this->materials.list[i]->surfaces.list[j];
      if ( v4->verts )
        Mem_Free(v4->verts);
      if ( v4->indexes )
        Mem_Free(v4->indexes);
      Mem_Free(v4);
    }
    v5 = this->materials.list[i];
    list = v5->surfaces.list;
    p_surfaces = &v5->surfaces;
    if ( list )
      Memory::Free(list);
    p_surfaces->list = 0;
    p_surfaces->num = 0;
    p_surfaces->size = 0;
    v8 = this->materials.list[i];
    if ( v8 )
    {
      if ( v8->surfaces.list )
        Memory::Free(v8->surfaces.list);
      v8->surfaces.list = 0;
      v8->surfaces.num = 0;
      v8->surfaces.size = 0;
      Memory::Free(v8);
    }
  }
  if ( this->materials.list )
    Memory::Free(this->materials.list);
  this->materials.list = 0;
  this->materials.num = 0;
  this->materials.size = 0;
}

// FUNC: public: static void __cdecl idRenderModelOverlay::Free(class idRenderModelOverlay *)
void __cdecl idRenderModelOverlay::Free(idRenderModelOverlay *overlay)
{
  if ( overlay )
  {
    idRenderModelOverlay::~idRenderModelOverlay(overlay);
    Memory::Free(overlay);
  }
}
