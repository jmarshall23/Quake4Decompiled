
// FUNC: public: virtual void __thiscall idRenderModelMD3::InitFromFile(char const *)
void __userpurge idRenderModelMD3::InitFromFile(idRenderModelMD3 *this@<ecx>, int a2@<esi>, char *fileName, int a4)
{
  _DWORD *v5; // esi
  int v6; // ebp
  int v7; // eax
  idSIMDProcessor_vtbl *v8; // ebp
  int v9; // eax
  md3Header_s *md3; // eax
  char *v11; // ecx
  float *v12; // edi
  float *v13; // esi
  int v14; // ebp
  bool v15; // cc
  int v16; // edi
  md3Header_s *v17; // eax
  int v18; // ebp
  float *v19; // esi
  int v20; // edi
  int v21; // ecx
  md3Header_s *v22; // eax
  char *v23; // esi
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  _BYTE *v31; // edi
  int v32; // ebp
  int v33; // eax
  char v34; // cl
  int v35; // ebp
  char *i; // edi
  int v37; // ebp
  int *j; // edi
  int v39; // eax
  int v40; // eax
  int v41; // ebp
  float *k; // edi
  __int16 *v43; // edi
  int m; // ebp
  __int16 v45; // ax
  __int16 v46; // cx
  __int16 v47; // ax
  __int16 v48; // dx
  int v49; // [esp-18h] [ebp-3Ch]
  int v50; // [esp-14h] [ebp-38h]
  int v51; // [esp-Ch] [ebp-30h]
  int v52; // [esp-8h] [ebp-2Ch]
  int v53; // [esp+0h] [ebp-24h]
  int v54; // [esp+4h] [ebp-20h]
  int v55; // [esp+4h] [ebp-20h]
  int v56; // [esp+8h] [ebp-1Ch]
  void *buffer; // [esp+20h] [ebp-4h] BYREF
  void *retaddr; // [esp+24h] [ebp+0h]

  idStr::operator=(&this->name, fileName);
  if ( fileSystem->ReadFile(fileSystem, fileName, &buffer, 0) > 0 )
  {
    v5 = buffer;
    v6 = LittleLong(*((_DWORD *)buffer + 1));
    if ( v6 == 15 )
    {
      v7 = LittleLong(v5[26]);
      this->dataSize += v7;
      this->md3 = (md3Header_s *)Mem_Alloc(v7, 0xEu);
      v8 = SIMDProcessor->__vftable;
      v9 = LittleLong(v5[26]);
      ((void (__fastcall *)(idSIMDProcessor *, md3Header_s *, void *, int, int))v8->Memcpy)(
        SIMDProcessor,
        this->md3,
        buffer,
        v9,
        a2);
      this->md3->ident = LittleLong(this->md3->ident);
      this->md3->version = LittleLong(this->md3->version);
      this->md3->numFrames = LittleLong(this->md3->numFrames);
      this->md3->numTags = LittleLong(this->md3->numTags);
      this->md3->numSurfaces = LittleLong(this->md3->numSurfaces);
      this->md3->ofsFrames = LittleLong(this->md3->ofsFrames);
      this->md3->ofsTags = LittleLong(this->md3->ofsTags);
      this->md3->ofsSurfaces = LittleLong(this->md3->ofsSurfaces);
      this->md3->ofsEnd = LittleLong(this->md3->ofsEnd);
      md3 = this->md3;
      if ( md3->numFrames >= 1 )
      {
        v11 = (char *)md3 + md3->ofsFrames;
        buffer = 0;
        v12 = (float *)(v11 + 36);
        do
        {
          *v12 = LittleFloat(*v12);
          v13 = v12 - 3;
          v14 = 3;
          do
          {
            *(v13 - 6) = LittleFloat(*(v13 - 6));
            *(v13 - 3) = LittleFloat(*(v13 - 3));
            *v13 = LittleFloat(*v13);
            ++v13;
            --v14;
          }
          while ( v14 );
          v12 += 14;
          v15 = (int)buffer + 1 < this->md3->numFrames;
          buffer = (char *)buffer + 1;
        }
        while ( v15 );
        v16 = a4;
        v17 = this->md3;
        v18 = 0;
        if ( v17->numFrames * v17->numTags > 0 )
        {
          buffer = (char *)&v17->numFrames + v17->ofsTags;
          do
          {
            v19 = (float *)buffer;
            v20 = 3;
            do
            {
              *(v19 - 3) = LittleFloat(*(v19 - 3));
              *v19 = LittleFloat(*v19);
              v19[3] = LittleFloat(v19[3]);
              v19[6] = LittleFloat(v19[6]);
              ++v19;
              --v20;
            }
            while ( v20 );
            v21 = this->md3->numFrames * this->md3->numTags;
            buffer = (char *)buffer + 112;
            ++v18;
          }
          while ( v18 < v21 );
          v16 = a4;
        }
        v22 = this->md3;
        v23 = (char *)v22 + v22->ofsSurfaces;
        v15 = v22->numSurfaces <= 0;
        buffer = 0;
        if ( !v15 )
        {
          while ( 1 )
          {
            *(_DWORD *)v23 = LittleLong(*(_DWORD *)v23);
            v24 = LittleLong(*((_DWORD *)v23 + 17));
            v54 = *((_DWORD *)v23 + 18);
            *((_DWORD *)v23 + 17) = v24;
            v25 = LittleLong(v54);
            v53 = *((_DWORD *)v23 + 19);
            *((_DWORD *)v23 + 18) = v25;
            *((_DWORD *)v23 + 19) = LittleLong(v53);
            v26 = LittleLong(*((_DWORD *)v23 + 21));
            v52 = *((_DWORD *)v23 + 22);
            *((_DWORD *)v23 + 21) = v26;
            v27 = LittleLong(v52);
            v51 = *((_DWORD *)v23 + 20);
            *((_DWORD *)v23 + 22) = v27;
            *((_DWORD *)v23 + 20) = LittleLong(v51);
            v28 = LittleLong(*((_DWORD *)v23 + 23));
            v50 = *((_DWORD *)v23 + 24);
            *((_DWORD *)v23 + 23) = v28;
            v29 = LittleLong(v50);
            v49 = *((_DWORD *)v23 + 25);
            *((_DWORD *)v23 + 24) = v29;
            *((_DWORD *)v23 + 25) = LittleLong(v49);
            *((_DWORD *)v23 + 26) = LittleLong(*((_DWORD *)v23 + 26));
            if ( *((int *)v23 + 20) > 1000 )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
                common.type,
                "InitFromFile: %s has more than %i verts on a surface (%i)",
                v16,
                1000,
                *((_DWORD *)v23 + 20));
            if ( 3 * *((_DWORD *)v23 + 21) > 6000 )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
                common.type,
                "InitFromFile: %s has more than %i triangles on a surface (%i)",
                v16,
                2000,
                *((_DWORD *)v23 + 21));
            *(_DWORD *)v23 = 0;
            v30 = strlen(v23 + 4);
            if ( v30 > 0 )
            {
              v31 = v23 + 4;
              v32 = v30;
              do
              {
                *v31 = tolower((char)*v31);
                ++v31;
                --v32;
              }
              while ( v32 );
            }
            v33 = strlen(v23 + 4);
            if ( v33 > 2 && v23[v33 + 2] == 95 )
              v23[v33 + 2] = v34;
            v35 = 0;
            for ( i = &v23[*((_DWORD *)v23 + 23)]; v35 < *((_DWORD *)v23 + 19); i += 68 )
            {
              *((_DWORD *)i + 16) = declManager->FindMaterial(declManager, i, 1);
              ++v35;
            }
            v37 = 0;
            for ( j = (int *)&v23[*((_DWORD *)v23 + 22)]; v37 < *((_DWORD *)v23 + 21); j += 3 )
            {
              v39 = LittleLong(*j);
              v56 = j[1];
              *j = v39;
              v40 = LittleLong(v56);
              v55 = j[2];
              j[1] = v40;
              j[2] = LittleLong(v55);
              ++v37;
            }
            v41 = 0;
            for ( k = (float *)&v23[*((_DWORD *)v23 + 24)]; v41 < *((_DWORD *)v23 + 20); k += 2 )
            {
              *k = LittleFloat(*k);
              k[1] = LittleFloat(k[1]);
              ++v41;
            }
            v43 = (__int16 *)&v23[*((_DWORD *)v23 + 25)];
            for ( m = 0; m < *((_DWORD *)v23 + 18) * *((_DWORD *)v23 + 20); v43 += 4 )
            {
              v45 = LittleShort(*v43);
              v46 = v43[1];
              *v43 = v45;
              v47 = LittleShort(v46);
              v48 = v43[2];
              v43[1] = v47;
              v43[2] = LittleShort(v48);
              v43[3] = LittleShort(v43[3]);
              ++m;
            }
            v23 += *((_DWORD *)v23 + 26);
            v15 = (int)buffer + 1 < this->md3->numSurfaces;
            buffer = (char *)buffer + 1;
            if ( !v15 )
              break;
            v16 = a4;
          }
        }
        fileSystem->FreeFile(fileSystem, retaddr);
      }
      else
      {
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
          common.type,
          "InitFromFile: %s has no frames",
          fileName);
        fileSystem->FreeFile(fileSystem, retaddr);
      }
    }
    else
    {
      fileSystem->FreeFile(fileSystem, buffer);
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "InitFromFile: %s has wrong version (%i should be %i)",
        fileName,
        v6,
        15);
    }
  }
}

// FUNC: public: virtual class idRenderModel * __thiscall idRenderModelMD3::InstantiateDynamicModel(struct renderEntity_s const *,struct viewDef_s const *,class idRenderModel *,unsigned int)
idRenderModel *__thiscall idRenderModelMD3::InstantiateDynamicModel(
        idRenderModelMD3 *this,
        const renderEntity_s *ent,
        const viewDef_s *view,
        idRenderModel *cachedModel,
        int __formal)
{
  idRenderModelMD3 *v5; // ebx
  float *v6; // ebp
  const md3Surface_s *v7; // edi
  srfTriangles_s *v8; // esi
  int v9; // edx
  char *v10; // ecx
  int v11; // eax
  int numVerts; // eax
  float *v13; // ecx
  int v14; // ebx
  float *v15; // eax
  int v16; // edx
  idDrawVert *verts; // ecx
  idDrawVert *v18; // ecx
  idDrawVert *v19; // ecx
  int v20; // ecx
  int v21; // ebp
  bool v22; // zf
  idVec3 *p_origin; // edx
  float *v24; // eax
  int i; // [esp+14h] [ebp-2Ch]
  int oldframe; // [esp+1Ch] [ebp-24h]
  int frame; // [esp+20h] [ebp-20h]
  float backlerp; // [esp+24h] [ebp-1Ch]
  idRenderModelStatic *staticModel; // [esp+28h] [ebp-18h]
  float *texCoords; // [esp+2Ch] [ebp-14h]
  const renderEntity_s *enta; // [esp+44h] [ebp+4h]
  const renderEntity_s *entb; // [esp+44h] [ebp+4h]
  idRenderModel *cachedModela; // [esp+4Ch] [ebp+Ch]
  idRenderModel *cachedModelb; // [esp+4Ch] [ebp+Ch]

  v5 = this;
  if ( cachedModel )
    ((void (__thiscall *)(idRenderModel *, int))cachedModel->~idRenderModel)(cachedModel, 1);
  v6 = (float *)NewRenderModel<idRenderModelStatic>(v5);
  v6[8] = idMath::INFINITY;
  v6[7] = idMath::INFINITY;
  v6[6] = idMath::INFINITY;
  v6[11] = -1.0e30;
  v6[10] = -1.0e30;
  staticModel = (idRenderModelStatic *)v6;
  v6[9] = -1.0e30;
  v7 = (const md3Surface_s *)((char *)v5->md3 + v5->md3->ofsSurfaces);
  i = 0;
  frame = (int)ent->shaderParms[8];
  backlerp = ent->shaderParms[10];
  oldframe = (int)ent->shaderParms[9];
  if ( v5->md3->numSurfaces > 0 )
  {
    while ( 1 )
    {
      v8 = R_AllocStaticTriSurf();
      R_AllocStaticTriSurfVerts(v8, v7->numVerts);
      R_AllocStaticTriSurfIndexes(v8, 3 * v7->numTriangles);
      v8->bounds.b[0].z = idMath::INFINITY;
      v8->bounds.b[0].y = idMath::INFINITY;
      v8->bounds.b[0].x = idMath::INFINITY;
      v8->bounds.b[1].z = -1.0e30;
      v8->bounds.b[1].y = -1.0e30;
      v8->bounds.b[1].x = -1.0e30;
      idRenderModelMD3::LerpMeshVertexes(v5, v8, v7, backlerp, frame, oldframe);
      v9 = 3 * v7->numTriangles;
      v10 = (char *)v7 + v7->ofsTriangles;
      v11 = 0;
      for ( cachedModela = (idRenderModel *)v9; v11 < (int)cachedModela; ++v11 )
      {
        v8->indexes[v11] = *(_DWORD *)&v10[4 * v11];
        v9 = (int)cachedModela;
      }
      v8->numIndexes += v9;
      numVerts = v7->numVerts;
      v13 = (float *)((char *)&v7->ident + v7->ofsSt);
      v14 = 0;
      texCoords = v13;
      cachedModelb = (idRenderModel *)numVerts;
      if ( numVerts >= 4 )
      {
        v15 = v13 + 2;
        v16 = 0;
        enta = (const renderEntity_s *)(((unsigned int)&cachedModelb[-1].callback >> 2) + 1);
        v14 = 4 * (_DWORD)enta;
        do
        {
          verts = v8->verts;
          verts[v16].st.x = *(v15 - 2);
          verts[v16].st.y = *(v15 - 1);
          v18 = v8->verts;
          v18[v16 + 1].st.x = *v15;
          v18[v16 + 1].st.y = v15[1];
          v19 = v8->verts;
          v19[v16 + 2].st.x = v15[2];
          v19[v16 + 2].st.y = v15[3];
          v20 = (int)&v8->verts[v16 + 3];
          *(float *)(v20 + 56) = v15[4];
          v21 = *((_DWORD *)v15 + 5);
          v16 += 4;
          v15 += 8;
          v22 = enta == (const renderEntity_s *)1;
          enta = (const renderEntity_s *)((char *)enta - 1);
          *(_DWORD *)(v20 + 60) = v21;
        }
        while ( !v22 );
        v6 = (float *)staticModel;
        v13 = texCoords;
        numVerts = (int)cachedModelb;
      }
      if ( v14 < numVerts )
      {
        p_origin = (idVec3 *)(v14 << 6);
        entb = (const renderEntity_s *)(v14 << 6);
        do
        {
          v24 = (float *)((char *)&p_origin->x + (unsigned int)v8->verts);
          v24[14] = v13[2 * v14];
          v24[15] = v13[2 * v14++ + 1];
          p_origin = &entb->origin;
          entb = (const renderEntity_s *)((char *)entb + 64);
        }
        while ( v14 < (int)cachedModelb );
      }
      R_BoundTriSurf(v8);
      (*(void (__thiscall **)(float *))(*(_DWORD *)v6 + 24))(v6);
      if ( v8->bounds.b[0].x < (double)v6[6] )
        v6[6] = v8->bounds.b[0].x;
      if ( v8->bounds.b[0].x > (double)v6[9] )
        v6[9] = v8->bounds.b[0].x;
      if ( v8->bounds.b[0].y < (double)v6[7] )
        v6[7] = v8->bounds.b[0].y;
      if ( v8->bounds.b[0].y > (double)v6[10] )
        v6[10] = v8->bounds.b[0].y;
      if ( v8->bounds.b[0].z < (double)v6[8] )
        v6[8] = v8->bounds.b[0].z;
      if ( v8->bounds.b[0].z > (double)v6[11] )
        v6[11] = v8->bounds.b[0].z;
      if ( v8->bounds.b[1].x < (double)v6[6] )
        v6[6] = v8->bounds.b[1].x;
      if ( v8->bounds.b[1].x > (double)v6[9] )
        v6[9] = v8->bounds.b[1].x;
      if ( v8->bounds.b[1].y < (double)v6[7] )
        v6[7] = v8->bounds.b[1].y;
      if ( v8->bounds.b[1].y > (double)v6[10] )
        v6[10] = v8->bounds.b[1].y;
      if ( v8->bounds.b[1].z < (double)v6[8] )
        v6[8] = v8->bounds.b[1].z;
      if ( v8->bounds.b[1].z > (double)v6[11] )
        v6[11] = v8->bounds.b[1].z;
      v7 = (const md3Surface_s *)((char *)v7 + v7->ofsEnd);
      if ( ++i >= this->md3->numSurfaces )
        break;
      v5 = this;
    }
  }
  return (idRenderModel *)v6;
}

// FUNC: public: virtual class idBounds __thiscall idRenderModelMD3::Bounds(struct renderEntity_s const *)const
idBounds *__thiscall idRenderModelMD3::Bounds(idRenderModelMD3 *this, idBounds *result, const renderEntity_s *ent)
{
  md3Header_s *md3; // eax
  int ofsFrames; // ecx
  double v5; // st7
  float *v6; // ecx
  idBounds *v7; // eax
  idBounds ret; // [esp+0h] [ebp-18h]

  ret.b[1].z = -1.0e30;
  ret.b[0].y = idMath::INFINITY;
  ret.b[0].z = idMath::INFINITY;
  ret.b[0].x = idMath::INFINITY;
  ret.b[1].y = ret.b[1].z;
  ret.b[1].x = ret.b[1].z;
  if ( ent && this->md3 )
  {
    md3 = this->md3;
    ofsFrames = md3->ofsFrames;
    v5 = *(float *)((char *)&md3->ident + ofsFrames);
    v6 = (float *)((char *)&md3->ident + ofsFrames);
    if ( v5 < 1.0e30 )
      ret.b[0].x = *v6;
    if ( *v6 > (double)ret.b[1].z )
      ret.b[1].x = *v6;
    if ( v6[1] < 1.0e30 )
      ret.b[0].y = v6[1];
    if ( v6[1] > (double)ret.b[1].z )
      ret.b[1].y = v6[1];
    if ( v6[2] < 1.0e30 )
      ret.b[0].z = v6[2];
    if ( v6[2] > (double)ret.b[1].z )
      ret.b[1].z = v6[2];
    if ( v6[3] < (double)ret.b[0].x )
      ret.b[0].x = v6[3];
    if ( v6[3] > (double)ret.b[1].x )
      ret.b[1].x = v6[3];
    if ( v6[4] < (double)ret.b[0].y )
      ret.b[0].y = v6[4];
    if ( v6[4] > (double)ret.b[1].y )
      ret.b[1].y = v6[4];
    if ( v6[5] < (double)ret.b[0].z )
      ret.b[0].z = v6[5];
    if ( v6[5] > (double)ret.b[1].z )
      ret.b[1].z = v6[5];
  }
  else
  {
    if ( 1.0e30 > -10.0 )
      ret.b[0].x = -10.0;
    if ( ret.b[1].z < -10.0 )
      ret.b[1].x = -10.0;
    if ( 1.0e30 > -10.0 )
      ret.b[0].y = -10.0;
    if ( ret.b[1].z < -10.0 )
      ret.b[1].y = -10.0;
    if ( 1.0e30 > -10.0 )
      ret.b[0].z = -10.0;
    if ( ret.b[1].z < -10.0 )
      ret.b[1].z = -10.0;
    if ( ret.b[0].x > 10.0 )
      ret.b[0].x = 10.0;
    if ( ret.b[1].x < 10.0 )
      ret.b[1].x = 10.0;
    if ( ret.b[0].y > 10.0 )
      ret.b[0].y = 10.0;
    if ( ret.b[1].y < 10.0 )
      ret.b[1].y = 10.0;
    if ( ret.b[0].z > 10.0 )
      ret.b[0].z = 10.0;
    if ( ret.b[1].z < 10.0 )
      ret.b[1].z = 10.0;
  }
  v7 = result;
  *result = ret;
  return v7;
}
