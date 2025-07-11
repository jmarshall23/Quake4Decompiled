
// FUNC: public: virtual __thiscall idRenderModel::~idRenderModel(void)
void __thiscall idRenderModel::~idRenderModel(idRenderModel *this)
{
  this->__vftable = (idRenderModel_vtbl *)&idRenderModel::`vftable';
  if ( (*(unsigned __int8 (__thiscall **)(idRenderModelManager *, idRenderModel *))renderModelManager->gap24)(
         renderModelManager,
         this) )
  {
    MessageBoxA(0, "MODEL freed while still in the list", "BAD!", 0);
  }
}

// FUNC: public: virtual bool __thiscall idRenderModelStatic::IsDefaultModel(void)const
bool __thiscall idRenderModelStatic::IsDefaultModel(idRenderModelStatic *this)
{
  return this->defaulted;
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::PartialInitFromFile(char const *)
void __thiscall idRenderModelStatic::PartialInitFromFile(idRenderModelStatic *this, const char *fileName)
{
  idRenderModelStatic_vtbl *v2; // eax

  v2 = this->__vftable;
  this->fastLoad = 1;
  ((void (__stdcall *)(const char *))v2->InitFromFile)(fileName);
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::FreeSurfaceTriangles(struct srfTriangles_s *)const
void __thiscall idRenderModelStatic::FreeSurfaceTriangles(idRenderModelStatic *this, srfTriangles_s *tris)
{
  R_FreeStaticTriSurf(tris);
}

// FUNC: public: virtual struct srfTriangles_s * __thiscall idRenderModelStatic::ShadowHull(void)const
srfTriangles_s *__thiscall idRenderModelStatic::ShadowHull(idRenderModelStatic *this)
{
  return this->shadowHull;
}

// FUNC: public: virtual bool __thiscall idRenderModelStatic::IsStaticWorldModel(void)const
bool __thiscall idRenderModelStatic::IsStaticWorldModel(idFileSystemLocal *this)
{
  return this->isFileLoadingAllowed;
}

// FUNC: public: virtual bool __thiscall idRenderModelStatic::IsReloadable(void)const
bool __thiscall idRenderModelStatic::IsReloadable(idRenderModelStatic *this)
{
  return this->reloadable;
}

// FUNC: public: virtual class idBounds __thiscall idRenderModelStatic::Bounds(struct renderEntity_s const *)const
idBounds *__thiscall idRenderModelStatic::Bounds(
        idRenderModelStatic *this,
        idBounds *result,
        const renderEntity_s *mdef)
{
  idBounds *v3; // eax

  v3 = result;
  *result = this->bounds;
  return v3;
}

// FUNC: public: virtual char const * __thiscall idRenderModelStatic::GetJointName(enum jointHandle_t)const
const char *__thiscall idRenderModelStatic::GetJointName(idRenderModelStatic *this, jointHandle_t handle)
{
  return &entityFilter;
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::ReadFromDemoFile(class idDemoFile *)
void __thiscall idRenderModelStatic::ReadFromDemoFile(idRenderModelStatic *this, idDemoFile *f)
{
  idRenderModelStatic *v2; // edi
  idRenderModelStatic_vtbl *v3; // eax
  idRenderModelStatic_vtbl *v5; // ebx
  const char *HashString; // eax
  idDeclManager_vtbl *v7; // edi
  const char *v8; // eax
  srfTriangles_s *v9; // edi
  int j; // ebp
  int v11; // ebx
  int i; // [esp+50h] [ebp-1Ch]
  int numSurfaces; // [esp+54h] [ebp-18h] BYREF
  idRenderModelStatic *v14; // [esp+58h] [ebp-14h]
  modelSurface_s surf; // [esp+5Ch] [ebp-10h]
  idDemoFile *fa; // [esp+70h] [ebp+4h]

  v2 = this;
  v3 = this->__vftable;
  v14 = this;
  ((void (__fastcall *)(idRenderModelStatic *))v3->PurgeModel)(this);
  v5 = v2->__vftable;
  HashString = idDemoFile::ReadHashString(f);
  v5->InitEmpty(v2, HashString);
  f->ReadInt(f, &numSurfaces);
  i = 0;
  if ( numSurfaces > 0 )
  {
    do
    {
      v7 = declManager->__vftable;
      v8 = idDemoFile::ReadHashString(f);
      surf.shader = v7->FindMaterial(declManager, v8, 1);
      v9 = R_AllocStaticTriSurf();
      f->ReadInt(f, &v9->numIndexes);
      R_AllocStaticTriSurfIndexes(v9, v9->numIndexes);
      for ( j = 0; j < v9->numIndexes; ++j )
        f->ReadInt(f, &v9->indexes[j]);
      f->ReadInt(f, &v9->numVerts);
      R_AllocStaticTriSurfVerts(v9, v9->numVerts);
      v11 = 0;
      for ( fa = 0; (int)fa < v9->numVerts; fa = (idDemoFile *)((char *)fa + 1) )
      {
        f->ReadVec3(f, (idVec3 *)&v9->verts[v11]);
        f->ReadVec2(f, &v9->verts[v11].st);
        f->ReadVec3(f, &v9->verts[v11].normal);
        f->ReadVec3(f, v9->verts[v11].tangents);
        f->ReadVec3(f, &v9->verts[v11].tangents[1]);
        f->ReadUnsignedChar(f, v9->verts[v11].color);
        f->ReadUnsignedChar(f, &v9->verts[v11].color[1]);
        f->ReadUnsignedChar(f, &v9->verts[v11].color[2]);
        f->ReadUnsignedChar(f, &v9->verts[v11++].color[3]);
      }
      ((void (__thiscall *)(idRenderModelStatic *, int, const idMaterial *, srfTriangles_s *, idStr *))v14->AddSurface)(
        v14,
        surf.id,
        surf.shader,
        v9,
        surf.mOriginalSurfaceName);
      ++i;
    }
    while ( i < numSurfaces );
    v2 = v14;
  }
  v2->FinishSurfaces(v2);
}

// FUNC: public: virtual bool __thiscall idRenderModelStatic::IsLoaded(void)
BOOL __thiscall idRenderModelStatic::IsLoaded(idRenderModelStatic *this)
{
  return !this->purged;
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::SetLevelLoadReferenced(bool)
void __thiscall idRenderModelStatic::SetLevelLoadReferenced(idRenderModelStatic *this, bool referenced)
{
  this->levelLoadReferenced = referenced;
}

// FUNC: public: virtual bool __thiscall idRenderModelStatic::IsLevelLoadReferenced(void)
bool __thiscall idRenderModelStatic::IsLevelLoadReferenced(idRenderModelStatic *this)
{
  return this->levelLoadReferenced;
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::Print(void)const
void __thiscall idRenderModelStatic::Print(idRenderModelStatic *this)
{
  int i; // ebx
  const modelSurface_s *v3; // eax
  srfTriangles_s *geometry; // edi
  const idMaterial *shader; // eax
  int v6; // edi
  int v7; // eax
  int v8; // ebp
  int v9; // eax

  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s\n", this->name.data);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Static model.\n");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "bounds: (%f %f %f) to (%f %f %f)\n",
    this->bounds.b[0].x,
    this->bounds.b[0].y,
    this->bounds.b[0].z,
    this->bounds.b[1].x,
    this->bounds.b[1].y,
    this->bounds.b[1].z);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "    verts  tris material\n");
  for ( i = 0; i < this->NumSurfaces(this); ++i )
  {
    v3 = this->Surface(this, i);
    geometry = v3->geometry;
    shader = v3->shader;
    if ( geometry )
    {
      v8 = *(_DWORD *)common.type;
      v9 = (int)shader->base->GetName(shader->base);
      (*(void (**)(netadrtype_t, const char *, ...))(v8 + 124))(
        common.type,
        "%2i: %5i %5i %s",
        i,
        geometry->numVerts,
        geometry->numIndexes / 3,
        v9);
      if ( geometry->generateNormals )
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " (smoothed)\n");
      else
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
    }
    else
    {
      v6 = *(_DWORD *)common.type;
      v7 = (int)shader->base->GetName(shader->base);
      (*(void (**)(netadrtype_t, const char *, ...))(v6 + 124))(common.type, "%2i: %s, NULL surface geometry\n", i, v7);
    }
  }
}

// FUNC: public: virtual int __thiscall idRenderModelStatic::Memory(void)const
int __thiscall idRenderModelStatic::Memory(idRenderModelStatic *this)
{
  int alloced; // eax
  int v3; // edi
  int i; // ebx
  srfTriangles_s *geometry; // eax

  if ( this->name.data == this->name.baseBuffer )
    alloced = 0;
  else
    alloced = this->name.alloced;
  v3 = alloced + 16 * (this->surfaces.num + 7);
  if ( this->shadowHull )
    v3 += R_TriSurfMemory(this->shadowHull);
  for ( i = 0; i < this->NumSurfaces(this); ++i )
  {
    geometry = this->Surface(this, i)->geometry;
    if ( geometry )
      v3 += R_TriSurfMemory(geometry);
  }
  return v3;
}

// FUNC: AddCubeFace
void __usercall AddCubeFace(srfTriangles_s *tri@<eax>, idVec3 v1, idVec3 v2, idVec3 v3, idVec3 v4)
{
  idDrawVert *v5; // edx
  idDrawVert *v6; // edx
  idDrawVert *v7; // edx
  idDrawVert *v8; // edx
  idDrawVert *v9; // edx
  idDrawVert *v10; // edx
  idDrawVert *v11; // edx
  idDrawVert *v12; // edx
  float v1_8; // [esp+14h] [ebp+Ch]
  float v1_8a; // [esp+14h] [ebp+Ch]
  float v1_8b; // [esp+14h] [ebp+Ch]

  v5 = &tri->verts[tri->numVerts];
  v5->xyz.z = 0.0;
  v5->xyz.y = 0.0;
  v5->xyz.x = 0.0;
  v5->st.y = 0.0;
  v1.z = v1.z * 8.0;
  v5->st.x = 0.0;
  v5->normal.z = 0.0;
  v5->normal.y = 0.0;
  v5->normal.x = 0.0;
  v5->tangents[0].z = 0.0;
  v5->tangents[0].y = 0.0;
  v5->tangents[0].x = 0.0;
  v5->tangents[1].z = 0.0;
  v5->tangents[1].y = 0.0;
  v5->tangents[1].x = 0.0;
  v5->color[3] = 0;
  v5->color[2] = 0;
  v5->color[1] = 0;
  v5->color[0] = 0;
  v6 = &tri->verts[tri->numVerts];
  v6->xyz.x = v1.x * 8.0;
  v6->xyz.z = v1.z;
  v6->xyz.y = v1.y * 8.0;
  tri->verts[tri->numVerts].st.x = 0.0;
  tri->verts[tri->numVerts].st.y = 0.0;
  v1_8 = v2.z * 8.0;
  v7 = &tri->verts[tri->numVerts + 1];
  v7->xyz.z = 0.0;
  v7->xyz.y = 0.0;
  v7->xyz.x = 0.0;
  v7->st.y = 0.0;
  v7->st.x = 0.0;
  v7->normal.z = 0.0;
  v7->normal.y = 0.0;
  v7->normal.x = 0.0;
  v7->tangents[0].z = 0.0;
  v7->tangents[0].y = 0.0;
  v7->tangents[0].x = 0.0;
  v7->tangents[1].z = 0.0;
  v7->tangents[1].y = 0.0;
  v7->tangents[1].x = 0.0;
  v7->color[3] = 0;
  v7->color[2] = 0;
  v7->color[1] = 0;
  v7->color[0] = 0;
  v8 = &tri->verts[tri->numVerts + 1];
  v8->xyz.x = v2.x * 8.0;
  v8->xyz.z = v1_8;
  v8->xyz.y = v2.y * 8.0;
  tri->verts[tri->numVerts + 1].st.x = 1.0;
  tri->verts[tri->numVerts + 1].st.y = 0.0;
  v1_8a = v3.z * 8.0;
  v9 = &tri->verts[tri->numVerts + 2];
  v9->xyz.z = 0.0;
  v9->xyz.y = 0.0;
  v9->xyz.x = 0.0;
  v9->st.y = 0.0;
  v9->st.x = 0.0;
  v9->normal.z = 0.0;
  v9->normal.y = 0.0;
  v9->normal.x = 0.0;
  v9->tangents[0].z = 0.0;
  v9->tangents[0].y = 0.0;
  v9->tangents[0].x = 0.0;
  v9->tangents[1].z = 0.0;
  v9->tangents[1].y = 0.0;
  v9->tangents[1].x = 0.0;
  v9->color[3] = 0;
  v9->color[2] = 0;
  v9->color[1] = 0;
  v9->color[0] = 0;
  v10 = &tri->verts[tri->numVerts + 2];
  v10->xyz.x = v3.x * 8.0;
  v10->xyz.z = v1_8a;
  v10->xyz.y = v3.y * 8.0;
  tri->verts[tri->numVerts + 2].st.x = 1.0;
  tri->verts[tri->numVerts + 2].st.y = 1.0;
  v11 = &tri->verts[tri->numVerts + 3];
  v11->xyz.z = 0.0;
  v11->xyz.y = 0.0;
  v11->xyz.x = 0.0;
  v11->st.y = 0.0;
  v11->st.x = 0.0;
  v11->normal.z = 0.0;
  v11->normal.y = 0.0;
  v11->normal.x = 0.0;
  v11->tangents[0].z = 0.0;
  v11->tangents[0].y = 0.0;
  v11->tangents[0].x = 0.0;
  v11->tangents[1].z = 0.0;
  v11->tangents[1].y = 0.0;
  v11->tangents[1].x = 0.0;
  v11->color[3] = 0;
  v11->color[2] = 0;
  v11->color[1] = 0;
  v11->color[0] = 0;
  v12 = &tri->verts[tri->numVerts + 3];
  v1_8b = v4.z * 8.0;
  v12->xyz.z = v1_8b;
  v12->xyz.x = v4.x * 8.0;
  v12->xyz.y = v4.y * 8.0;
  tri->verts[tri->numVerts + 3].st.x = 0.0;
  tri->verts[tri->numVerts + 3].st.y = 1.0;
  tri->indexes[tri->numIndexes] = tri->numVerts;
  tri->indexes[tri->numIndexes + 1] = tri->numVerts + 1;
  tri->indexes[tri->numIndexes + 2] = tri->numVerts + 2;
  tri->indexes[tri->numIndexes + 3] = tri->numVerts;
  tri->indexes[tri->numIndexes + 4] = tri->numVerts + 2;
  tri->indexes[tri->numIndexes + 5] = tri->numVerts + 3;
  tri->numVerts += 4;
  tri->numIndexes += 6;
}

// FUNC: public: void __thiscall idRenderModelStatic::MakeDefaultModel(void)
void __thiscall idRenderModelStatic::MakeDefaultModel(idRenderModelStatic *this)
{
  idRenderModelStatic_vtbl *v2; // eax
  srfTriangles_s *v3; // eax
  const idMaterial *defaultMaterial; // ebp
  srfTriangles_s *v5; // esi
  idVec3 v6; // [esp-30h] [ebp-70h]
  idVec3 v7; // [esp-30h] [ebp-70h]
  idVec3 v8; // [esp-30h] [ebp-70h]
  idVec3 v9; // [esp-30h] [ebp-70h]
  idVec3 v10; // [esp-30h] [ebp-70h]
  idVec3 v11; // [esp-30h] [ebp-70h]
  idVec3 v12; // [esp-24h] [ebp-64h]
  idVec3 v13; // [esp-24h] [ebp-64h]
  idVec3 v14; // [esp-24h] [ebp-64h]
  idVec3 v15; // [esp-24h] [ebp-64h]
  idVec3 v16; // [esp-24h] [ebp-64h]
  idVec3 v17; // [esp-24h] [ebp-64h]
  idVec3 v18; // [esp-18h] [ebp-58h]
  idVec3 v19; // [esp-18h] [ebp-58h]
  idVec3 v20; // [esp-18h] [ebp-58h]
  idVec3 v21; // [esp-18h] [ebp-58h]
  idVec3 v22; // [esp-18h] [ebp-58h]
  idVec3 v23; // [esp-18h] [ebp-58h]
  idVec3 v24; // [esp-Ch] [ebp-4Ch]
  idVec3 v25; // [esp-Ch] [ebp-4Ch]
  idVec3 v26; // [esp-Ch] [ebp-4Ch]
  idVec3 v27; // [esp-Ch] [ebp-4Ch]
  idVec3 v28; // [esp-Ch] [ebp-4Ch]
  idVec3 v29; // [esp-Ch] [ebp-4Ch]

  v2 = this->__vftable;
  this->defaulted = 1;
  ((void (*)(void))v2->PurgeModel)();
  v3 = R_AllocStaticTriSurf();
  defaultMaterial = tr.defaultMaterial;
  v5 = v3;
  R_AllocStaticTriSurfVerts(v3, 24);
  R_AllocStaticTriSurfIndexes(v5, 36);
  v24.x = -1.0;
  *(_QWORD *)&v24.y = 0x3F800000BF800000i64;
  v18.x = 1.0;
  *(_QWORD *)&v18.y = 0x3F800000BF800000i64;
  v12.x = 1.0;
  *(_QWORD *)&v12.y = 0x3F8000003F800000i64;
  v6.x = -1.0;
  *(_QWORD *)&v6.y = 0x3F8000003F800000i64;
  AddCubeFace(v5, v6, v12, v18, v24);
  v25.x = 1.0;
  *(_QWORD *)&v25.y = 0xBF8000003F800000ui64;
  v19.x = 1.0;
  *(_QWORD *)&v19.y = 0xBF800000BF800000ui64;
  v13.x = -1.0;
  *(_QWORD *)&v13.y = 0xBF800000BF800000ui64;
  v7.x = -1.0;
  *(_QWORD *)&v7.y = 0xBF8000003F800000ui64;
  AddCubeFace(v5, v7, v13, v19, v25);
  v26.x = 1.0;
  *(_QWORD *)&v26.y = 0xBF800000BF800000ui64;
  v20.x = 1.0;
  *(_QWORD *)&v20.y = 0xBF8000003F800000ui64;
  v14.x = 1.0;
  *(_QWORD *)&v14.y = 0x3F8000003F800000i64;
  v8.x = 1.0;
  *(_QWORD *)&v8.y = 0x3F800000BF800000i64;
  AddCubeFace(v5, v8, v14, v20, v26);
  v27.x = -1.0;
  *(_QWORD *)&v27.y = 0x3F8000003F800000i64;
  v21.x = -1.0;
  *(_QWORD *)&v21.y = 0xBF8000003F800000ui64;
  v15.x = -1.0;
  *(_QWORD *)&v15.y = 0xBF800000BF800000ui64;
  v9.x = -1.0;
  *(_QWORD *)&v9.y = 0x3F800000BF800000i64;
  AddCubeFace(v5, v9, v15, v21, v27);
  v28.x = -1.0;
  *(_QWORD *)&v28.y = 0xBF800000BF800000ui64;
  v22.x = 1.0;
  *(_QWORD *)&v22.y = 0xBF800000BF800000ui64;
  v16.x = 1.0;
  *(_QWORD *)&v16.y = 0x3F800000BF800000i64;
  v10.x = -1.0;
  *(_QWORD *)&v10.y = 0x3F800000BF800000i64;
  AddCubeFace(v5, v10, v16, v22, v28);
  v29.x = 1.0;
  *(_QWORD *)&v29.y = 0x3F8000003F800000i64;
  v23.x = 1.0;
  *(_QWORD *)&v23.y = 0xBF8000003F800000ui64;
  v17.x = -1.0;
  *(_QWORD *)&v17.y = 0xBF8000003F800000ui64;
  v11.x = -1.0;
  *(_QWORD *)&v11.y = 0x3F8000003F800000i64;
  AddCubeFace(v5, v11, v17, v23, v29);
  v5->generateNormals = 1;
  ((void (__thiscall *)(idRenderModelStatic *, int, const idMaterial *, srfTriangles_s *))this->AddSurface)(
    this,
    1065353216,
    defaultMaterial,
    v5);
  this->FinishSurfaces(this);
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::LoadModel(void)
void __thiscall idRenderModelStatic::LoadModel(idRenderModelStatic *this)
{
  this->PurgeModel(this);
  this->InitFromFile(this, this->name.data);
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::InitEmpty(char const *)
void __thiscall idRenderModelStatic::InitEmpty(idRenderModelStatic *this, char *fileName)
{
  idRenderModelStatic_vtbl *v3; // edx

  this->isStaticWorldModel = idStr::Cmpn(fileName, "_area", 5) == 0;
  idStr::operator=(&this->name, fileName);
  v3 = this->__vftable;
  this->reloadable = 0;
  v3->PurgeModel(this);
  this->purged = 0;
  this->bounds.b[1].z = 0.0;
  this->bounds.b[1].y = 0.0;
  this->bounds.b[1].x = 0.0;
  this->bounds.b[0].z = 0.0;
  this->bounds.b[0].y = 0.0;
  this->bounds.b[0].x = 0.0;
  this->levelOfDetail = 0xFFFF;
}

// FUNC: public: virtual int __thiscall idRenderModelStatic::NumBaseSurfaces(void)const
int __thiscall idRenderModelStatic::NumBaseSurfaces(idRenderModelStatic *this)
{
  return this->surfaces.num - this->overlaysAdded;
}

// FUNC: public: virtual struct modelSurface_s const * __thiscall idRenderModelStatic::Surface(int)const
const modelSurface_s *__thiscall idRenderModelStatic::Surface(idRenderModelStatic *this, int surfaceNum)
{
  return &this->surfaces.list[surfaceNum];
}

// FUNC: public: virtual class idRenderModel * __thiscall idRenderModelStatic::InstantiateDynamicModel(struct renderEntity_s const *,struct viewDef_s const *,class idRenderModel *,unsigned int)
idRenderModel *__thiscall idRenderModelStatic::InstantiateDynamicModel(
        idRenderModelStatic *this,
        const renderEntity_s *ent,
        const viewDef_s *view,
        idRenderModel *cachedModel,
        unsigned int __formal)
{
  if ( cachedModel )
    ((void (__thiscall *)(idRenderModel *, int))cachedModel->~idRenderModel)(cachedModel, 1);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
    common.type,
    "InstantiateDynamicModel called on static model '%s'",
    this->name.data);
  return 0;
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::PurgeModel(void)
void __thiscall idRenderModelStatic::PurgeModel(idRenderModelStatic *this)
{
  int v2; // ebx
  int v3; // edi

  v2 = 0;
  if ( this->surfaces.num > 0 )
  {
    v3 = 0;
    do
    {
      if ( this->surfaces.list[v3].geometry )
        R_FreeStaticTriSurf(this->surfaces.list[v3].geometry);
      ++v2;
      ++v3;
    }
    while ( v2 < this->surfaces.num );
  }
  if ( this->surfaces.list )
    Memory::Free(this->surfaces.list);
  this->surfaces.list = 0;
  this->surfaces.num = 0;
  this->surfaces.size = 0;
  this->purged = 1;
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::FreeVertexCache(void)
void __thiscall idRenderModelStatic::FreeVertexCache(idRenderModelStatic *this)
{
  int v2; // ebp
  int v3; // ebx
  srfTriangles_s *geometry; // esi

  v2 = 0;
  if ( this->surfaces.num > 0 )
  {
    v3 = 0;
    do
    {
      geometry = this->surfaces.list[v3].geometry;
      if ( geometry )
      {
        if ( geometry->ambientCache )
        {
          idVertexCache::Free(&vertexCache, geometry->ambientCache);
          geometry->ambientCache = 0;
        }
        if ( geometry->shadowCache )
        {
          idVertexCache::Free(&vertexCache, geometry->shadowCache);
          geometry->shadowCache = 0;
        }
      }
      ++v2;
      ++v3;
    }
    while ( v2 < this->surfaces.num );
  }
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::WriteToDemoFile(class idDemoFile *)
void __userpurge idRenderModelStatic::WriteToDemoFile(idRenderModelStatic *this@<ecx>, int a2@<ebp>, idDemoFile *f)
{
  idRenderModelStatic *v4; // edi
  const char *v5; // eax
  char *v6; // edi
  const char *v7; // eax
  int v8; // edi
  int j; // ebx
  int v10; // ebp
  int v11; // ebx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int i; // [esp+38h] [ebp-8h]
  idDemoFile *fa; // [esp+44h] [ebp+4h]

  v4 = this;
  this->lastArchivedFrame = tr.frameCount;
  f->WriteChar(f, 18);
  v5 = v4->Name(v4);
  idDemoFile::WriteHashString(f, v5);
  f->WriteInt(f, v4->surfaces.num);
  i = 0;
  if ( v4->surfaces.num > 0 )
  {
    fa = 0;
    while ( 1 )
    {
      v6 = (char *)fa + (unsigned int)v4->surfaces.list;
      v7 = (const char *)(*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)(*((_DWORD *)v6 + 1) + 4) + 4))(
                           *(_DWORD *)(*((_DWORD *)v6 + 1) + 4),
                           a2);
      idDemoFile::WriteHashString(f, v7);
      v8 = *((_DWORD *)v6 + 2);
      f->WriteInt(f, *(_DWORD *)(v8 + 52));
      for ( j = 0; j < *(_DWORD *)(v8 + 52); ++j )
        f->WriteInt(f, *(_DWORD *)(*(_DWORD *)(v8 + 56) + 4 * j));
      a2 = *(_DWORD *)(v8 + 36);
      ((void (__thiscall *)(idDemoFile *))f->WriteInt)(f);
      v10 = 0;
      if ( *(int *)(v8 + 36) > 0 )
      {
        v11 = 0;
        do
        {
          f->WriteVec3(f, (const idVec3 *)(v11 + *(_DWORD *)(v8 + 40)));
          f->WriteVec2(f, (const idVec2 *)(v11 + *(_DWORD *)(v8 + 40) + 56));
          f->WriteVec3(f, (const idVec3 *)(v11 + *(_DWORD *)(v8 + 40) + 16));
          f->WriteVec3(f, (const idVec3 *)(v11 + *(_DWORD *)(v8 + 40) + 32));
          f->WriteVec3(f, (const idVec3 *)(v11 + *(_DWORD *)(v8 + 40) + 44));
          LOBYTE(v12) = *(_BYTE *)(v11 + *(_DWORD *)(v8 + 40) + 12);
          f->WriteUnsignedChar(f, v12);
          LOBYTE(v13) = *(_BYTE *)(v11 + *(_DWORD *)(v8 + 40) + 13);
          f->WriteUnsignedChar(f, v13);
          LOBYTE(v14) = *(_BYTE *)(v11 + *(_DWORD *)(v8 + 40) + 14);
          f->WriteUnsignedChar(f, v14);
          LOBYTE(v15) = *(_BYTE *)(v11 + *(_DWORD *)(v8 + 40) + 15);
          f->WriteUnsignedChar(f, v15);
          ++v10;
          v11 += 64;
        }
        while ( v10 < *(_DWORD *)(v8 + 36) );
      }
      fa = (idDemoFile *)((char *)fa + 16);
      if ( ++i >= this->surfaces.num )
        break;
      v4 = this;
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::TouchData(void)
void __thiscall idRenderModelStatic::TouchData(idRenderModelStatic *this)
{
  int v2; // edi
  int v3; // ebx
  idDeclBase *base; // ecx
  idDeclManager_vtbl *v5; // ebp
  int v6; // eax

  v2 = 0;
  if ( this->surfaces.num > 0 )
  {
    v3 = 0;
    do
    {
      base = this->surfaces.list[v3].shader->base;
      v5 = declManager->__vftable;
      v6 = ((int (__thiscall *)(idDeclBase *, int))base->GetName)(base, 1);
      ((void (__thiscall *)(idDeclManager *, int))v5->FindMaterial)(declManager, v6);
      ++v2;
      ++v3;
    }
    while ( v2 < this->surfaces.num );
  }
}

// FUNC: public: bool __thiscall idRenderModelStatic::DeleteSurfaceWithId(int)
char __thiscall idRenderModelStatic::DeleteSurfaceWithId(idRenderModelStatic *this, int id)
{
  int num; // ecx
  int v4; // esi
  modelSurface_s *i; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  modelSurface_s *v11; // eax

  num = this->surfaces.num;
  v4 = 0;
  if ( num <= 0 )
    return 0;
  for ( i = this->surfaces.list; i->id != id; ++i )
  {
    if ( ++v4 >= num )
      return 0;
  }
  R_FreeStaticTriSurf(this->surfaces.list[v4].geometry);
  if ( v4 >= 0 )
  {
    v7 = this->surfaces.num;
    if ( v4 < v7 )
    {
      v8 = v7 - 1;
      this->surfaces.num = v8;
      v9 = v4;
      if ( v4 < v8 )
      {
        v10 = v4;
        do
        {
          v11 = &this->surfaces.list[v10];
          v11->id = v11[1].id;
          v11->shader = v11[1].shader;
          v11->geometry = v11[1].geometry;
          ++v9;
          v11->mOriginalSurfaceName = v11[1].mOriginalSurfaceName;
          ++v10;
        }
        while ( v9 < this->surfaces.num );
      }
    }
  }
  return 1;
}

// FUNC: public: void __thiscall idRenderModelStatic::DeleteSurfacesWithNegativeId(void)
void __thiscall idRenderModelStatic::DeleteSurfacesWithNegativeId(idRenderModelStatic *this)
{
  int v2; // edi
  int v3; // ebx
  srfTriangles_s **v4; // eax
  int num; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  _DWORD *v9; // eax
  int v10; // [esp+8h] [ebp-4h]

  v2 = 0;
  if ( this->surfaces.num > 0 )
  {
    v3 = 0;
    v10 = 0;
    do
    {
      v4 = (srfTriangles_s **)((char *)this->surfaces.list + v3);
      if ( (int)*v4 < 0 )
      {
        R_FreeStaticTriSurf(v4[2]);
        if ( v2 >= 0 )
        {
          num = this->surfaces.num;
          if ( v2 < num )
          {
            v6 = num - 1;
            this->surfaces.num = v6;
            v7 = v2;
            if ( v2 < v6 )
            {
              v8 = v3;
              do
              {
                v9 = (int *)((char *)&this->surfaces.list->id + v8);
                *v9 = v9[4];
                v9[1] = v9[5];
                v9[2] = v9[6];
                ++v7;
                v9[3] = v9[7];
                v8 += 16;
              }
              while ( v7 < this->surfaces.num );
              v3 = v10;
            }
          }
        }
        --v2;
        v3 -= 16;
      }
      ++v2;
      v3 += 16;
      v10 = v3;
    }
    while ( v2 < this->surfaces.num );
  }
}

// FUNC: public: bool __thiscall idRenderModelStatic::FindSurfaceWithId(int,int &)
char __thiscall idRenderModelStatic::FindSurfaceWithId(idRenderModelStatic *this, int id, int *surfaceNum)
{
  int num; // edx
  int v4; // eax
  modelSurface_s *i; // ecx

  num = this->surfaces.num;
  v4 = 0;
  if ( num <= 0 )
    return 0;
  for ( i = this->surfaces.list; i->id != id; ++i )
  {
    if ( ++v4 >= num )
      return 0;
  }
  *surfaceNum = v4;
  return 1;
}

// FUNC: public: virtual int __thiscall idRenderModelStatic::GetSurfaceMask(char const *)const
int __thiscall idRenderModelStatic::GetSurfaceMask(idRenderModelStatic *this, const char *surface)
{
  int v2; // ebx
  const idMaterial *v4; // ebp
  int i; // edi
  int mask; // [esp+Ch] [ebp-4h]

  v2 = 0;
  mask = 0;
  v4 = declManager->FindMaterial(declManager, surface, 0);
  if ( !v4 )
    return 0;
  for ( i = 0; i < this->NumSurfaces(this); ++v2 )
  {
    if ( this->surfaces.list[v2].shader == v4 )
      mask |= 1 << i;
    ++i;
  }
  return mask;
}

// FUNC: public: __thiscall idRenderModelStatic::idRenderModelStatic(void)
void __thiscall idRenderModelStatic::idRenderModelStatic(idRenderModelStatic *this)
{
  idStr *p_name; // ecx

  this->__vftable = (idRenderModelStatic_vtbl *)&idRenderModelStatic::`vftable';
  this->surfaces.granularity = 16;
  this->surfaces.list = 0;
  this->surfaces.num = 0;
  this->surfaces.size = 0;
  p_name = &this->name;
  p_name->len = 0;
  p_name->alloced = 20;
  p_name->data = p_name->baseBuffer;
  p_name->baseBuffer[0] = 0;
  idStr::operator=(p_name, "<undefined>");
  this->bounds.b[0].z = idMath::INFINITY;
  this->bounds.b[0].y = idMath::INFINITY;
  this->bounds.b[0].x = idMath::INFINITY;
  this->bounds.b[1].z = -1.0e30;
  this->bounds.b[1].y = -1.0e30;
  this->bounds.b[1].x = -1.0e30;
  this->lastModifiedFrame = 0;
  this->lastArchivedFrame = 0;
  this->overlaysAdded = 0;
  this->shadowHull = 0;
  this->isStaticWorldModel = 0;
  this->defaulted = 0;
  this->purged = 0;
  this->fastLoad = 0;
  this->levelLoadReferenced = 0;
  this->timeStamp = 0;
  this->reloadable = 1;
  this->levelOfDetail = 0xFFFF;
}

// FUNC: public: virtual __thiscall idRenderModelStatic::~idRenderModelStatic(void)
void __thiscall idRenderModelStatic::~idRenderModelStatic(idRenderModelStatic *this)
{
  modelSurface_s *list; // eax

  this->__vftable = (idRenderModelStatic_vtbl *)&idRenderModelStatic::`vftable';
  idRenderModelStatic::PurgeModel(this);
  idStr::FreeData(&this->name);
  list = this->surfaces.list;
  if ( list )
    Memory::Free(list);
  this->surfaces.list = 0;
  this->surfaces.num = 0;
  this->surfaces.size = 0;
  this->__vftable = (idRenderModelStatic_vtbl *)&idRenderModel::`vftable';
  if ( (*(unsigned __int8 (__thiscall **)(idRenderModelManager *, idRenderModelStatic *))renderModelManager->gap24)(
         renderModelManager,
         this) )
  {
    MessageBoxA(0, "MODEL freed while still in the list", "BAD!", 0);
  }
}

// FUNC: public: virtual bool __thiscall idRenderModelStatic::HasCollisionSurface(struct renderEntity_s const *)const
char __thiscall idRenderModelStatic::HasCollisionSurface(idRenderModelStatic *this, const renderEntity_s *ent)
{
  int v3; // edi
  const modelSurface_s *v4; // eax
  const idMaterial *v5; // eax
  int materialFlags; // eax

  v3 = 0;
  if ( this->NumSurfaces(this) <= 0 )
    return 0;
  while ( 1 )
  {
    v4 = this->Surface(this, v3);
    if ( v4->id != -1 )
    {
      v5 = R_RemapShaderBySkin(v4->shader, ent->customSkin, ent->customShader);
      if ( (v5->surfaceFlags & 0x40) != 0 && v5->numStages <= 0 && !v5->entityGui && !v5->gui )
      {
        materialFlags = v5->materialFlags;
        if ( (materialFlags & 8) == 0 && (materialFlags & 4) != 0 )
          break;
      }
    }
    if ( ++v3 >= this->NumSurfaces(this) )
      return 0;
  }
  return 1;
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::AddSurface(struct modelSurface_s)
void __thiscall idRenderModelStatic::AddSurface(idRenderModelStatic *this, modelSurface_s surface)
{
  int granularity; // eax
  bool v4; // cc
  modelSurface_s *v5; // eax
  int v6; // ecx
  int *v7; // eax
  modelSurface_s *v8; // edx
  int num; // ebx
  int size; // ecx
  int v11; // ecx
  modelSurface_s *list; // edi
  modelSurface_s *v13; // eax
  int v14; // ecx
  int v15; // eax
  modelSurface_s *v16; // ebx

  if ( !this->surfaces.list )
  {
    granularity = this->surfaces.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->surfaces.size )
      {
        v4 = granularity < this->surfaces.num;
        this->surfaces.size = granularity;
        if ( v4 )
          this->surfaces.num = granularity;
        v5 = (modelSurface_s *)Memory::Allocate(16 * granularity);
        v6 = 0;
        v4 = this->surfaces.num <= 0;
        this->surfaces.list = v5;
        if ( !v4 )
        {
          v7 = 0;
          do
          {
            v8 = (modelSurface_s *)((char *)v7 + (unsigned int)this->surfaces.list);
            v8->id = *v7;
            v8->shader = (const idMaterial *)v7[1];
            v8->geometry = (srfTriangles_s *)v7[2];
            ++v6;
            v8->mOriginalSurfaceName = (idStr *)v7[3];
            v7 += 4;
          }
          while ( v6 < this->surfaces.num );
        }
      }
    }
    else
    {
      this->surfaces.list = 0;
      this->surfaces.num = 0;
      this->surfaces.size = 0;
    }
  }
  num = this->surfaces.num;
  size = this->surfaces.size;
  if ( num == size )
  {
    if ( !this->surfaces.granularity )
      this->surfaces.granularity = 16;
    v11 = this->surfaces.granularity + size - (this->surfaces.granularity + size) % this->surfaces.granularity;
    if ( v11 > 0 )
    {
      if ( v11 != this->surfaces.size )
      {
        list = this->surfaces.list;
        this->surfaces.size = v11;
        if ( v11 < num )
          this->surfaces.num = v11;
        v13 = (modelSurface_s *)Memory::Allocate(16 * v11);
        v14 = 0;
        v4 = this->surfaces.num <= 0;
        this->surfaces.list = v13;
        if ( !v4 )
        {
          v15 = 0;
          do
          {
            v16 = &this->surfaces.list[v15];
            v16->id = list[v15].id;
            v16->shader = list[v15].shader;
            v16->geometry = list[v15].geometry;
            ++v14;
            v16->mOriginalSurfaceName = list[v15++].mOriginalSurfaceName;
          }
          while ( v14 < this->surfaces.num );
        }
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->surfaces.list )
        Memory::Free(this->surfaces.list);
      this->surfaces.list = 0;
      this->surfaces.num = 0;
      this->surfaces.size = 0;
    }
  }
  this->surfaces.list[this->surfaces.num++] = surface;
  if ( surface.geometry )
  {
    if ( surface.geometry->bounds.b[0].x < (double)this->bounds.b[0].x )
      this->bounds.b[0].x = surface.geometry->bounds.b[0].x;
    if ( surface.geometry->bounds.b[0].y < (double)this->bounds.b[0].y )
      this->bounds.b[0].y = surface.geometry->bounds.b[0].y;
    if ( surface.geometry->bounds.b[0].z < (double)this->bounds.b[0].z )
      this->bounds.b[0].z = surface.geometry->bounds.b[0].z;
    if ( surface.geometry->bounds.b[1].x > (double)this->bounds.b[1].x )
      this->bounds.b[1].x = surface.geometry->bounds.b[1].x;
    if ( surface.geometry->bounds.b[1].y > (double)this->bounds.b[1].y )
      this->bounds.b[1].y = surface.geometry->bounds.b[1].y;
    if ( surface.geometry->bounds.b[1].z > (double)this->bounds.b[1].z )
      this->bounds.b[1].z = surface.geometry->bounds.b[1].z;
  }
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::FinishSurfaces(void)
void __thiscall idRenderModelStatic::FinishSurfaces(idRenderModelStatic *this)
{
  int num; // edi
  int v3; // ebp
  int v4; // ebx
  modelSurface_s *list; // edi
  float *geometry; // ecx
  int v7; // ebx
  modelSurface_s *v8; // ebp
  modelSurface_s *v9; // ebp
  idStr *v10; // ebx
  const char *data; // ebp
  unsigned int v12; // eax
  int v13; // edi
  int v14; // eax
  char *v15; // edx
  const char *v16; // ecx
  char v17; // al
  int v18; // ebp
  int v19; // edi
  bool v20; // zf
  modelSurface_s *v21; // ebx
  int v22; // edi
  srfTriangles_s *v23; // ebp
  double v24; // st7
  int v25; // ebx
  int v26; // edi
  modelSurface_s *v27; // ecx
  const idMaterial *shader; // eax
  modelSurface_s *v29; // ecx
  float *v30; // eax
  double v31; // rt0
  double v32; // st6
  double v33; // st2
  double v34; // st5
  double v35; // st2
  double v36; // st5
  double v37; // st2
  long double v38; // st3
  long double v39; // st7
  float *v40; // ecx
  int v41; // [esp+10h] [ebp-38h]
  int v42; // [esp+10h] [ebp-38h]
  int v43; // [esp+10h] [ebp-38h]
  int i; // [esp+14h] [ebp-34h]
  int ia; // [esp+14h] [ebp-34h]
  srfTriangles_s *newTri; // [esp+18h] [ebp-30h]
  float mid; // [esp+20h] [ebp-28h]
  float newSurf_8; // [esp+34h] [ebp-14h]

  this->purged = 0;
  this->bounds.b[1].z = 0.0;
  this->bounds.b[1].y = 0.0;
  this->bounds.b[1].x = 0.0;
  this->bounds.b[0].z = 0.0;
  this->bounds.b[0].y = 0.0;
  this->bounds.b[0].x = 0.0;
  num = this->surfaces.num;
  if ( num )
  {
    if ( this->fastLoad )
    {
      this->bounds.b[1].z = 0.0;
      this->bounds.b[1].y = 0.0;
      this->bounds.b[1].x = 0.0;
      this->bounds.b[0].z = 0.0;
      this->bounds.b[0].y = 0.0;
      this->bounds.b[0].x = 0.0;
      v3 = 0;
      if ( this->surfaces.num > 0 )
      {
        v4 = 0;
        do
        {
          list = this->surfaces.list;
          R_BoundTriSurf(list[v4].geometry);
          geometry = (float *)list[v4].geometry;
          if ( *geometry < (double)this->bounds.b[0].x )
            this->bounds.b[0].x = *geometry;
          if ( geometry[1] < (double)this->bounds.b[0].y )
            this->bounds.b[0].y = geometry[1];
          if ( geometry[2] < (double)this->bounds.b[0].z )
            this->bounds.b[0].z = geometry[2];
          if ( geometry[3] > (double)this->bounds.b[1].x )
            this->bounds.b[1].x = geometry[3];
          if ( geometry[4] > (double)this->bounds.b[1].y )
            this->bounds.b[1].y = geometry[4];
          if ( geometry[5] > (double)this->bounds.b[1].z )
            this->bounds.b[1].z = geometry[5];
          ++v3;
          ++v4;
        }
        while ( v3 < this->surfaces.num );
      }
    }
    else
    {
      v7 = 0;
      if ( num > 0 )
      {
        v41 = 0;
        do
        {
          v8 = &this->surfaces.list[v41];
          if ( !v8->geometry || !v8->shader )
          {
            idRenderModelStatic::MakeDefaultModel(this);
            (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
              common.type,
              "Model %s, surface %i had NULL geometry",
              this->name.data,
              v7);
            if ( !v8->shader )
            {
              idRenderModelStatic::MakeDefaultModel(this);
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
                common.type,
                "Model %s, surface %i had NULL shader",
                this->name.data,
                v7);
            }
          }
          ++v41;
          ++v7;
        }
        while ( v7 < num );
        v42 = 0;
        i = num;
        do
        {
          v9 = &this->surfaces.list[v42];
          if ( v9->shader->shouldCreateBackSides )
          {
            newTri = R_CopyStaticTriSurf(v9->geometry);
            R_ReverseTriangles(newTri);
            if ( v9->mOriginalSurfaceName )
            {
              v10 = (idStr *)Memory::Allocate(0x20u);
              if ( v10 )
              {
                data = v9->mOriginalSurfaceName->data;
                v10->len = 0;
                v10->alloced = 20;
                v10->data = v10->baseBuffer;
                v10->baseBuffer[0] = 0;
                if ( data )
                {
                  v12 = (unsigned int)&data[strlen(data) + 1];
                  v13 = v12 - (_DWORD)(data + 1);
                  v14 = v12 - (_DWORD)data;
                  if ( v14 > v10->alloced )
                    idStr::ReAllocate(v10, v14, 1);
                  v15 = v10->data;
                  v16 = data;
                  do
                  {
                    v17 = *v16;
                    *v15++ = *v16++;
                  }
                  while ( v17 );
                  v10->len = v13;
                }
              }
            }
            ((void (__thiscall *)(idRenderModelStatic *))this->AddSurface)(this);
          }
          ++v42;
          --i;
        }
        while ( i );
      }
      v18 = 0;
      if ( this->surfaces.num > 0 )
      {
        v19 = 0;
        do
        {
          R_CleanupTriangles(
            this->surfaces.list[v19].geometry,
            this->surfaces.list[v19].geometry->generateNormals,
            1,
            this->surfaces.list[v19].shader->unsmoothedTangents,
            !this->isStaticWorldModel);
          ++v18;
          ++v19;
        }
        while ( v18 < this->surfaces.num );
      }
      v20 = this->surfaces.num == 0;
      ia = 0;
      if ( this->surfaces.num > 0 )
      {
        v43 = 0;
        do
        {
          v21 = &this->surfaces.list[v43];
          v22 = 0;
          v23 = v21->geometry;
          if ( v23->numIndexes > 0 )
          {
            do
            {
              v24 = idWinding::TriangleArea(
                      &v23->verts[v23->indexes[v22]].xyz,
                      &v23->verts[v23->indexes[v22 + 1]].xyz,
                      &v23->verts[v23->indexes[v22 + 2]].xyz);
              v22 += 3;
              v21->shader->surfaceArea = v24 + v21->shader->surfaceArea;
            }
            while ( v22 < v23->numIndexes );
          }
          ++v43;
          ++ia;
        }
        while ( ia < this->surfaces.num );
        v20 = this->surfaces.num == 0;
      }
      if ( v20 )
      {
        this->bounds.b[1].z = 0.0;
        this->bounds.b[1].y = 0.0;
        this->bounds.b[1].x = 0.0;
        this->bounds.b[0].z = 0.0;
        this->bounds.b[0].y = 0.0;
        this->bounds.b[0].x = 0.0;
      }
      else
      {
        this->bounds.b[0].z = idMath::INFINITY;
        this->bounds.b[0].y = idMath::INFINITY;
        this->bounds.b[0].x = idMath::INFINITY;
        v25 = 0;
        this->bounds.b[1].z = -1.0e30;
        this->bounds.b[1].y = -1.0e30;
        this->bounds.b[1].x = -1.0e30;
        if ( this->surfaces.num > 0 )
        {
          v26 = 0;
          do
          {
            v27 = this->surfaces.list;
            shader = v27[v26].shader;
            v29 = &v27[v26];
            if ( shader->deform )
            {
              v30 = (float *)v29->geometry;
              newSurf_8 = v30[5] + v30[2];
              v31 = v30[4] + v30[1];
              mid = (v30[3] + *v30) * 0.5;
              v32 = newSurf_8 * 0.5;
              v33 = *v30 - mid;
              v34 = v33 * v33;
              v35 = v30[2] - v32;
              v36 = v34 + v35 * v35;
              v37 = v30[1] - v31 * 0.5;
              v38 = sqrt(v36 + v37 * v37);
              *v30 = mid - (v38 + 20.0);
              v30[1] = v31 * 0.5 - (v38 + 20.0);
              v30[2] = v32 - (v38 + 20.0);
              v30[3] = mid + v38 + 20.0;
              v39 = v38 + 20.0;
              v30[4] = v31 * 0.5 + v39;
              v30[5] = v32 + v39;
            }
            v40 = (float *)v29->geometry;
            if ( *v40 < (double)this->bounds.b[0].x )
              this->bounds.b[0].x = *v40;
            if ( v40[1] < (double)this->bounds.b[0].y )
              this->bounds.b[0].y = v40[1];
            if ( v40[2] < (double)this->bounds.b[0].z )
              this->bounds.b[0].z = v40[2];
            if ( v40[3] > (double)this->bounds.b[1].x )
              this->bounds.b[1].x = v40[3];
            if ( v40[4] > (double)this->bounds.b[1].y )
              this->bounds.b[1].y = v40[4];
            if ( v40[5] > (double)this->bounds.b[1].z )
              this->bounds.b[1].z = v40[5];
            ++v25;
            ++v26;
          }
          while ( v25 < this->surfaces.num );
        }
      }
      if ( this->bounds.b[0].x >= (double)this->bounds.b[1].x
        || this->bounds.b[0].y >= (double)this->bounds.b[1].y
        || this->bounds.b[0].z >= (double)this->bounds.b[1].z
        || (this->bounds.b[1].z - this->bounds.b[0].z)
         * (this->bounds.b[1].x - this->bounds.b[0].x)
         * (this->bounds.b[1].y - this->bounds.b[0].y) < 1.0 )
      {
        this->bounds.b[0].x = this->bounds.b[0].x - 1.0;
        this->bounds.b[0].y = this->bounds.b[0].y - 1.0;
        this->bounds.b[0].z = this->bounds.b[0].z - 1.0;
        this->bounds.b[1].x = this->bounds.b[1].x + 1.0;
        this->bounds.b[1].y = this->bounds.b[1].y + 1.0;
        this->bounds.b[1].z = this->bounds.b[1].z + 1.0;
      }
    }
  }
}

// FUNC: public: bool __thiscall idRenderModelStatic::ConvertASEToModelSurfaces(struct aseModel_s const *)
char __thiscall idRenderModelStatic::ConvertASEToModelSurfaces(idRenderModelStatic *this, const aseModel_s *ase)
{
  const aseModel_s *v2; // ebx
  int num; // esi
  int v6; // eax
  void *v7; // esp
  int v8; // eax
  int v9; // eax
  int *v10; // ecx
  bool v11; // zf
  float v12; // esi
  aseMaterial_t *v13; // ebx
  unsigned int v14; // eax
  int v15; // eax
  char *data; // edx
  aseMaterial_t *v17; // ecx
  char v18; // al
  const idMaterial *v19; // eax
  int v20; // edx
  idStr *v21; // esi
  unsigned int v22; // eax
  int v23; // eax
  char *v24; // edx
  aseMaterial_t *v25; // ecx
  char v26; // al
  int v27; // eax
  bool v28; // cc
  int v29; // esi
  aseMaterial_t *v30; // ecx
  char *v31; // edx
  char v32; // al
  const idMaterial *v33; // eax
  int v34; // esi
  int v35; // ebx
  float v36; // eax
  idStr *v37; // esi
  char *v38; // eax
  int v39; // ebx
  int v40; // eax
  aseMaterial_t *v41; // ecx
  char *v42; // edx
  char v43; // al
  int v44; // esi
  int v45; // esi
  aseObject_t *v46; // esi
  aseMaterial_t *v47; // eax
  idDeclManager_vtbl *v48; // edx
  char *v49; // eax
  int v50; // eax
  aseMaterial_t *v51; // edx
  int *v52; // ecx
  idSIMDProcessor_vtbl *v53; // eax
  double v54; // st7
  double v55; // st7
  double v56; // st7
  int boxHashSize; // edi
  float *v58; // edx
  int v59; // edx
  int i; // ecx
  float *v61; // eax
  double v62; // st7
  const idMaterial *v63; // eax
  int v64; // ebx
  const idMaterial *v65; // ecx
  int v66; // edx
  float *v67; // ecx
  int v68; // esi
  unsigned int v69; // esi
  int v70; // ecx
  double v71; // st7
  float v72; // edi
  int indexSize; // eax
  int v74; // eax
  float v75; // eax
  aseMaterial_t *v76; // esi
  const idMaterial *v77; // eax
  const idMaterial *v78; // edx
  int m; // eax
  int v80; // edx
  idSIMDProcessor_vtbl *v81; // eax
  double v82; // st7
  double v83; // st7
  float *v84; // ebx
  int v85; // edi
  int j; // ecx
  float *v87; // eax
  double v88; // st7
  matchVert_s **v89; // eax
  matchVert_s **v90; // ecx
  int v91; // edx
  int v92; // esi
  int v93; // edx
  float *v94; // ecx
  unsigned int v95; // esi
  int v96; // ecx
  double v97; // st7
  float v98; // edi
  int v99; // eax
  int v100; // eax
  float v101; // eax
  aseMaterial_t *v102; // edx
  aseMaterial_t *v103; // ebx
  matchVert_s *v104; // eax
  srfTriangles_s *v105; // esi
  double floatValue; // st7
  int v107; // edi
  int vTiling_low; // eax
  int v109; // edi
  int v110; // eax
  float v111; // ecx
  float v112; // edx
  float v113; // eax
  matchVert_s *v114; // ecx
  unsigned __int8 *v115; // edi
  matchVert_s *v116; // edx
  int v117; // eax
  aseMaterial_t *v118; // eax
  float v119; // ecx
  float v120; // edx
  float v121; // ecx
  long double v122; // st7
  int v123; // edx
  float *p_z; // ecx
  idDrawVert *v125; // eax
  int v126; // edi
  float v127; // ebx
  int v128; // edi
  idDrawVert *verts; // eax
  _DWORD *p_x; // eax
  int v131; // eax
  int v132; // edi
  double v133; // st7
  double v134; // st6
  int v135; // edi
  srfTriangles_s *v136; // ebx
  idVec3 *vertexes; // [esp-8h] [ebp-118h]
  int v138; // [esp-8h] [ebp-118h]
  int numVertexes; // [esp-4h] [ebp-114h]
  float v140; // [esp-4h] [ebp-114h]
  _DWORD v141[5]; // [esp+0h] [ebp-110h] BYREF
  idVectorSubset<idVec3,3> vertexSubset; // [esp+14h] [ebp-FCh] BYREF
  idStr strippedName; // [esp+64h] [ebp-ACh] BYREF
  idVectorSubset<idVec2,2> texCoordSubset; // [esp+84h] [ebp-8Ch] BYREF
  float uOffset; // [esp+C4h] [ebp-4Ch]
  float uTiling; // [esp+C8h] [ebp-48h]
  float texCoordEpsilon; // [esp+CCh] [ebp-44h]
  float vTiling; // [esp+D0h] [ebp-40h]
  float vertexEpsilon; // [esp+D4h] [ebp-3Ch]
  modelSurface_s surf; // [esp+D8h] [ebp-38h]
  int v; // [esp+E8h] [ebp-28h]
  float normalEpsilon; // [esp+ECh] [ebp-24h]
  int tv; // [esp+F0h] [ebp-20h]
  idVec3 normal; // [esp+F4h] [ebp-1Ch]
  float v155; // [esp+100h] [ebp-10h]
  float v156; // [esp+104h] [ebp-Ch]
  float textureCos; // [esp+108h] [ebp-8h]
  unsigned __int8 *color; // [esp+10Ch] [ebp-4h]
  float textureSin; // [esp+110h] [ebp+0h]
  idVec3 maxs; // [esp+114h] [ebp+4h] BYREF
  idVec3 mins; // [esp+120h] [ebp+10h] BYREF
  idVec2 v162; // [esp+12Ch] [ebp+1Ch] BYREF
  idVec2 v163; // [esp+134h] [ebp+24h] BYREF
  int objectNum; // [esp+13Ch] [ebp+2Ch]
  int *vRemap; // [esp+140h] [ebp+30h]
  int *mergeTo; // [esp+144h] [ebp+34h]
  int k; // [esp+148h] [ebp+38h]
  float vOffset; // [esp+14Ch] [ebp+3Ch]
  float *v169; // [esp+150h] [ebp+40h]
  int v170; // [esp+154h] [ebp+44h]
  idRenderModelStatic *v171; // [esp+158h] [ebp+48h]
  matchVert_s *mvTable; // [esp+15Ch] [ebp+4Ch]
  matchVert_s **mvHash; // [esp+160h] [ebp+50h]
  const idMaterial *im1; // [esp+164h] [ebp+54h]
  aseMaterial_t *material; // [esp+168h] [ebp+58h]
  int v176; // [esp+16Ch] [ebp+5Ch]
  bool normalsParsed; // [esp+173h] [ebp+63h]
  float expand; // [esp+174h] [ebp+64h]
  int v179; // [esp+180h] [ebp+70h]

  v2 = ase;
  v171 = this;
  if ( !ase || ase->objects.num < 1 )
    return 0;
  this->timeStamp = ase->timeStamp;
  num = ase->objects.num;
  v6 = 4 * num + 3;
  LOBYTE(v6) = v6 & 0xFC;
  v7 = alloca(v6);
  v8 = ase->materials.num;
  mergeTo = v141;
  surf.mOriginalSurfaceName = 0;
  if ( v8 )
  {
    v11 = idRenderModelStatic::r_mergeModelSurfaces.internalVar->integerValue == 0;
    expand = 0.0;
    if ( v11 )
    {
      if ( num > 0 )
      {
        v12 = 0.0;
        do
        {
          *(float *)&mergeTo[LODWORD(v12)] = v12;
          v13 = ase->materials.list[ase->objects.list[LODWORD(v12)]->materialRef];
          strippedName.len = 0;
          strippedName.alloced = 20;
          strippedName.data = strippedName.baseBuffer;
          strippedName.baseBuffer[0] = 0;
          if ( v13 )
          {
            v14 = (unsigned int)&v13->name[strlen(v13->name) + 1];
            LODWORD(vOffset) = v14 - (_DWORD)&v13->name[1];
            v15 = v14 - (_DWORD)v13;
            if ( v15 > 20 )
              idStr::ReAllocate(&strippedName, v15, 1);
            data = strippedName.data;
            v17 = v13;
            do
            {
              v18 = v17->name[0];
              *data = v17->name[0];
              v17 = (aseMaterial_t *)((char *)v17 + 1);
              ++data;
            }
            while ( v18 );
            *(float *)&strippedName.len = vOffset;
          }
          v179 = 0;
          idStr::StripAbsoluteFileExtension(&strippedName);
          v19 = declManager->FindMaterial(declManager, strippedName.data, 1);
          v20 = **(_DWORD **)common.ip;
          surf.shader = v19;
          if ( (*(int (__thiscall **)(_DWORD, int))(v20 + 28))(*(_DWORD *)common.ip, 0x40000) )
          {
            *(float *)&v21 = COERCE_FLOAT(Memory::Allocate(0x20u));
            normalEpsilon = *(float *)&v21;
            LOBYTE(v179) = 1;
            if ( *(float *)&v21 == 0.0 )
            {
              *(float *)&v21 = 0.0;
            }
            else
            {
              v21->len = 0;
              v21->alloced = 20;
              v21->data = v21->baseBuffer;
              v21->baseBuffer[0] = 0;
              if ( v13 )
              {
                v22 = (unsigned int)&v13->name[strlen(v13->name) + 1];
                LODWORD(vOffset) = v22 - (_DWORD)&v13->name[1];
                v23 = v22 - (_DWORD)v13;
                if ( v23 > v21->alloced )
                  idStr::ReAllocate(v21, v23, 1);
                v24 = v21->data;
                v25 = v13;
                do
                {
                  v26 = v25->name[0];
                  *v24 = v25->name[0];
                  v25 = (aseMaterial_t *)((char *)v25 + 1);
                  ++v24;
                }
                while ( v26 );
                *(float *)&v21->len = vOffset;
              }
            }
            surf.mOriginalSurfaceName = v21;
            v12 = expand;
            LOBYTE(v179) = 0;
          }
          v27 = this->NumSurfaces(this);
          ((void (__thiscall *)(idRenderModelStatic *, int, const idMaterial *, _DWORD, idStr *))this->AddSurface)(
            this,
            v27,
            surf.shader,
            0,
            surf.mOriginalSurfaceName);
          v179 = -1;
          idStr::FreeData(&strippedName);
          v28 = ++LODWORD(v12) < ase->objects.num;
          expand = v12;
        }
        while ( v28 );
        v2 = ase;
      }
    }
    else if ( num > 0 )
    {
      do
      {
        material = v2->materials.list[v2->objects.list[LODWORD(expand)]->materialRef];
        strippedName.len = 0;
        strippedName.alloced = 20;
        strippedName.data = strippedName.baseBuffer;
        strippedName.baseBuffer[0] = 0;
        if ( material )
        {
          v29 = strlen(material->name);
          if ( v29 + 1 > 20 )
            idStr::ReAllocate(&strippedName, v29 + 1, 1);
          v30 = material;
          v31 = strippedName.data;
          do
          {
            v32 = v30->name[0];
            *v31 = v30->name[0];
            v30 = (aseMaterial_t *)((char *)v30 + 1);
            ++v31;
          }
          while ( v32 );
          strippedName.len = v29;
        }
        v179 = 2;
        idStr::StripAbsoluteFileExtension(&strippedName);
        v33 = declManager->FindMaterial(declManager, strippedName.data, 1);
        v11 = v33->entityGui == 0;
        im1 = v33;
        if ( !v11 || v33->gui || v33->deform || LODWORD(v33->sort) == -1065353216 || (v33->surfaceFlags & 0x400) != 0 )
        {
          v34 = this->NumSurfaces(this);
        }
        else
        {
          v34 = 0;
          if ( this->NumSurfaces(this) > 0 )
          {
            v35 = 0;
            while ( im1 != this->surfaces.list[v35].shader )
            {
              ++v34;
              ++v35;
              if ( v34 >= this->NumSurfaces(this) )
                goto LABEL_49;
            }
            mergeTo[LODWORD(expand)] = v34;
LABEL_49:
            v2 = ase;
          }
        }
        if ( v34 == this->NumSurfaces(this) )
        {
          mergeTo[LODWORD(expand)] = v34;
          surf.id = this->NumSurfaces(this);
          if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 0x40000) )
          {
            v36 = COERCE_FLOAT(Memory::Allocate(0x20u));
            v37 = (idStr *)LODWORD(v36);
            normalEpsilon = v36;
            LOBYTE(v179) = 3;
            if ( v36 == 0.0 )
            {
              v37 = 0;
            }
            else
            {
              *(_DWORD *)(LODWORD(v36) + 4) = LODWORD(v36) + 12;
              *(_DWORD *)LODWORD(v36) = 0;
              *(_DWORD *)(LODWORD(v36) + 8) = 20;
              *(_BYTE *)(LODWORD(v36) + 12) = 0;
              if ( material )
              {
                v38 = &material->name[strlen(material->name) + 1];
                v39 = v38 - &material->name[1];
                v40 = v38 - (char *)material;
                if ( v40 > v37->alloced )
                  idStr::ReAllocate(v37, v40, 1);
                v41 = material;
                v42 = v37->data;
                do
                {
                  v43 = v41->name[0];
                  *v42 = v41->name[0];
                  v41 = (aseMaterial_t *)((char *)v41 + 1);
                  ++v42;
                }
                while ( v43 );
                v37->len = v39;
                v2 = ase;
              }
            }
            LOBYTE(v179) = 2;
            surf.mOriginalSurfaceName = v37;
          }
          ((void (__thiscall *)(idRenderModelStatic *, int, const idMaterial *, _DWORD, idStr *))this->AddSurface)(
            this,
            surf.id,
            im1,
            0,
            surf.mOriginalSurfaceName);
        }
        v179 = -1;
        idStr::FreeData(&strippedName);
        v28 = ++LODWORD(expand) < v2->objects.num;
      }
      while ( v28 );
    }
  }
  else
  {
    ((void (__thiscall *)(idRenderModelStatic *, _DWORD, const idMaterial *, _DWORD, _DWORD))this->AddSurface)(
      this,
      0,
      tr.defaultMaterial,
      0,
      0);
    v2 = ase;
    v9 = 0;
    if ( ase->objects.num > 0 )
    {
      v10 = mergeTo;
      do
        v10[v9++] = 0;
      while ( v9 < ase->objects.num );
    }
  }
  idHashIndex::Init(&vertexSubset.hash, 1024, 1024);
  v44 = vertexSubset.boxHashSize * vertexSubset.boxHashSize * vertexSubset.boxHashSize;
  v179 = 4;
  idHashIndex::Free(&vertexSubset.hash);
  memset(vertexSubset.boxInvSize, 0, 24);
  vertexSubset.hash.hashSize = v44;
  vertexSubset.hash.indexSize = 128;
  vertexSubset.boxHashSize = 16;
  v179 = 5;
  idHashIndex::Init(&texCoordSubset.hash, 1024, 1024);
  v45 = texCoordSubset.boxHashSize * texCoordSubset.boxHashSize;
  LOBYTE(v179) = 6;
  idHashIndex::Free(&texCoordSubset.hash);
  memset(texCoordSubset.boxInvSize, 0, 16);
  texCoordSubset.hash.hashSize = v45;
  texCoordSubset.hash.indexSize = 128;
  texCoordSubset.boxHashSize = 16;
  v28 = v2->objects.num <= 0;
  LOBYTE(v179) = 7;
  objectNum = 0;
  if ( !v28 )
  {
    do
    {
      v46 = ase->objects.list[objectNum];
      v47 = ase->materials.list[v46->materialRef];
      v48 = declManager->__vftable;
      material = (aseMaterial_t *)v46;
      v49 = v48->FindMaterial(declManager, v47->name, 1)->renderBump.data;
      normalsParsed = v46->mesh.normalsParsed;
      if ( v49 && *v49 )
        normalsParsed = 0;
      vRemap = (int *)R_StaticAlloc(4 * v46->mesh.numVertexes);
      if ( v171->fastLoad )
      {
        v50 = 0;
        if ( v46->mesh.numVertexes > 0 )
        {
          v51 = material;
          v52 = vRemap;
          do
          {
            v52[v50] = v50;
            ++v50;
          }
          while ( v50 < SLODWORD(v51->uTiling) );
        }
      }
      else
      {
        v53 = SIMDProcessor->__vftable;
        vertexEpsilon = idRenderModelStatic::r_slopVertex.internalVar->floatValue;
        numVertexes = v46->mesh.numVertexes;
        vertexes = v46->mesh.vertexes;
        expand = vertexEpsilon * 64.0;
        (*(void (__fastcall **)(idSIMDProcessor *, idVec3 *, idVec3 *, idVec3 *, int))&v53->gap7C[16])(
          SIMDProcessor,
          &mins,
          &maxs,
          vertexes,
          numVertexes);
        mins.x = mins.x - expand;
        mins.y = mins.y - expand;
        mins.z = mins.z - expand;
        maxs.x = maxs.x + expand;
        maxs.y = maxs.y + expand;
        maxs.z = maxs.z + expand;
        idHashIndex::Free(&vertexSubset.hash);
        vertexSubset.mins = mins;
        v54 = (maxs.x - mins.x) * 0.03125;
        vertexSubset.hash.hashSize = 0x8000;
        vertexSubset.hash.indexSize = 1024;
        vertexSubset.maxs = maxs;
        vertexSubset.boxHashSize = 32;
        expand = 0.0;
        vertexSubset.boxInvSize[0] = 1.0 / v54;
        vertexSubset.boxHalfSize[0] = v54 * 0.5;
        v55 = (maxs.y - mins.y) * 0.03125;
        vertexSubset.boxInvSize[1] = 1.0 / v55;
        vertexSubset.boxHalfSize[1] = v55 * 0.5;
        v56 = (maxs.z - mins.z) * 0.03125;
        vertexSubset.boxInvSize[2] = 1.0 / v56;
        vertexSubset.boxHalfSize[2] = v56 * 0.5;
        if ( v46->mesh.numVertexes > 0 )
        {
          mvTable = 0;
          do
          {
            boxHashSize = vertexSubset.boxHashSize;
            v58 = (float *)((char *)mvTable + *(_DWORD *)&material[1].name[64]);
            mvHash = *(matchVert_s ***)&material[1].name[64];
            v169 = v58;
            v59 = (char *)v58 - (char *)&vertexSubset.mins;
            v170 = v59;
            for ( i = 0; i < 12; *(int *)((char *)&surf.id + i) = (int)v62 )
            {
              v61 = (float *)((char *)&vertexSubset.mins.x + i);
              i += 4;
              v62 = (*(float *)((char *)v61 + v59) - *v61 - v61[10]) * v61[7];
              v63 = (const idMaterial *)HIWORD(v176);
              BYTE1(v63) = HIBYTE(v176) | 0xC;
              im1 = v63;
            }
            v64 = 0;
            v65 = (const idMaterial *)(vertexSubset.hash.hashMask & vertexSubset.hash.lookupMask);
            im1 = (const idMaterial *)(vertexSubset.hash.hashMask & vertexSubset.hash.lookupMask);
            do
            {
              v66 = vertexSubset.hash.hash[(unsigned int)v65 & ((unsigned int)surf.mOriginalSurfaceName
                                                              + boxHashSize
                                                              * ((int)surf.geometry
                                                               + boxHashSize * ((int)surf.shader + (v64 & 1))
                                                               + ((v64 >> 1) & 1))
                                                              + ((v64 >> 2) & 1))];
              if ( v66 >= 0 )
              {
                do
                {
                  v67 = v169;
                  v68 = 0;
                  while ( 1 )
                  {
                    v156 = *(float *)((char *)v67 + (char *)&mvHash[3 * v66] - (char *)v169) - *v67;
                    HIBYTE(v156) &= ~0x80u;
                    if ( v156 > (double)vertexEpsilon )
                      break;
                    ++v68;
                    ++v67;
                    if ( v68 >= 3 )
                      goto LABEL_94;
                  }
                  v66 = vertexSubset.hash.indexChain[v66 & vertexSubset.hash.lookupMask];
                }
                while ( v66 >= 0 );
                boxHashSize = vertexSubset.boxHashSize;
                v65 = im1;
              }
              ++v64;
            }
            while ( v64 < 8 );
            v69 = 0;
            v70 = 0;
            do
            {
              v71 = *(float *)((char *)&vertexSubset.mins.x + 4 * v70 + v170) - *(&vertexSubset.mins.x + v70);
              ++v70;
              im1 = (const idMaterial *)(int)(v71 * *((float *)&vertexSubset.boxHashSize + v70));
              v69 = (unsigned int)im1 + v69 * boxHashSize;
            }
            while ( v70 < 3 );
            v72 = expand;
            if ( vertexSubset.hash.hash == idHashIndex::INVALID_INDEX )
            {
              indexSize = vertexSubset.hash.indexSize;
              if ( SLODWORD(expand) >= vertexSubset.hash.indexSize )
                indexSize = LODWORD(expand) + 1;
              idHashIndex::Allocate(&vertexSubset.hash, vertexSubset.hash.hashSize, indexSize);
            }
            else if ( SLODWORD(expand) >= vertexSubset.hash.indexSize )
            {
              idHashIndex::ResizeIndex(&vertexSubset.hash, LODWORD(expand) + 1);
            }
            v74 = v69 & vertexSubset.hash.hashMask;
            vertexSubset.hash.indexChain[LODWORD(v72)] = vertexSubset.hash.hash[v69 & vertexSubset.hash.hashMask];
            *(float *)&vertexSubset.hash.hash[v74] = v72;
            v66 = LODWORD(v72);
LABEL_94:
            v75 = expand;
            mvTable = (matchVert_s *)((char *)mvTable + 12);
            vRemap[LODWORD(expand)] = v66;
            v28 = ++LODWORD(v75) < SLODWORD(material->uTiling);
            expand = v75;
          }
          while ( v28 );
        }
      }
      v76 = material;
      v77 = (const idMaterial *)R_StaticAlloc(4 * LODWORD(material->vTiling));
      v11 = !v171->fastLoad;
      v78 = v77;
      im1 = v77;
      if ( v11 )
      {
        v140 = v76->vTiling;
        v80 = *(_DWORD *)&v76[1].name[68];
        texCoordEpsilon = idRenderModelStatic::r_slopTexCoord.internalVar->floatValue;
        v81 = SIMDProcessor->__vftable;
        expand = texCoordEpsilon * 64.0;
        (*(void (__fastcall **)(idSIMDProcessor *, idVec2 *, idVec2 *, int, float))&v81->gap7C[20])(
          SIMDProcessor,
          &v162,
          &v163,
          v80,
          COERCE_FLOAT(LODWORD(v140)));
        v162.x = v162.x - expand;
        v162.y = v162.y - expand;
        v163.x = v163.x + expand;
        v163.y = v163.y + expand;
        idHashIndex::Free(&texCoordSubset.hash);
        texCoordSubset.hash.hashSize = 1024;
        v82 = (v163.x - v162.x) * 0.03125;
        texCoordSubset.hash.indexSize = 1024;
        texCoordSubset.mins = v162;
        texCoordSubset.maxs = v163;
        texCoordSubset.boxHashSize = 32;
        expand = 0.0;
        texCoordSubset.boxInvSize[0] = 1.0 / v82;
        texCoordSubset.boxHalfSize[0] = v82 * 0.5;
        v83 = (v163.y - v162.y) * 0.03125;
        texCoordSubset.boxInvSize[1] = 1.0 / v83;
        texCoordSubset.boxHalfSize[1] = v83 * 0.5;
        if ( SLODWORD(v76->vTiling) > 0 )
        {
          do
          {
            v169 = *(float **)&material[1].name[68];
            v84 = &v169[2 * LODWORD(expand)];
            v85 = (char *)v84 - (char *)&texCoordSubset.mins;
            v170 = (char *)v84 - (char *)&texCoordSubset.mins;
            for ( j = 0; j < 2; v141[j + 2] = (int)v88 )
            {
              v87 = (float *)((char *)&texCoordSubset.mins.x + j * 4);
              ++j;
              v88 = (*(float *)((char *)v87 + v85) - *v87 - v87[7]) * v87[5];
              v89 = (matchVert_s **)HIWORD(v176);
              BYTE1(v89) = HIBYTE(v176) | 0xC;
              mvHash = v89;
            }
            v90 = 0;
            v91 = texCoordSubset.hash.hashMask & texCoordSubset.hash.lookupMask;
            mvHash = 0;
            k = texCoordSubset.hash.hashMask & texCoordSubset.hash.lookupMask;
            do
            {
              v92 = texCoordSubset.hash.hash[v91 & (v141[4]
                                                  + texCoordSubset.boxHashSize * (v141[3] + ((unsigned __int8)v90 & 1))
                                                  + (((int)v90 >> 1) & 1))];
              if ( v92 >= 0 )
              {
                do
                {
                  v93 = 0;
                  v94 = v84;
                  while ( 1 )
                  {
                    v155 = *(float *)((char *)v94 + (char *)&v169[2 * v92] - (char *)v84) - *v94;
                    HIBYTE(v155) &= ~0x80u;
                    if ( v155 > (double)texCoordEpsilon )
                      break;
                    ++v93;
                    ++v94;
                    if ( v93 >= 2 )
                      goto LABEL_120;
                  }
                  v92 = texCoordSubset.hash.indexChain[v92 & texCoordSubset.hash.lookupMask];
                }
                while ( v92 >= 0 );
                v85 = v170;
                v91 = k;
                v90 = mvHash;
              }
              v90 = (matchVert_s **)((char *)v90 + 1);
              mvHash = v90;
            }
            while ( (int)v90 < 4 );
            v95 = 0;
            v96 = 0;
            do
            {
              v97 = *(float *)((char *)&texCoordSubset.mins.x + 4 * v96 + v85) - *(&texCoordSubset.mins.x + v96);
              ++v96;
              mvHash = (matchVert_s **)(int)(v97 * *((float *)&texCoordSubset.boxHashSize + v96));
              v95 = (unsigned int)mvHash + v95 * texCoordSubset.boxHashSize;
            }
            while ( v96 < 2 );
            v98 = expand;
            if ( texCoordSubset.hash.hash == idHashIndex::INVALID_INDEX )
            {
              v99 = texCoordSubset.hash.indexSize;
              if ( SLODWORD(expand) >= texCoordSubset.hash.indexSize )
                v99 = LODWORD(expand) + 1;
              idHashIndex::Allocate(&texCoordSubset.hash, texCoordSubset.hash.hashSize, v99);
            }
            else if ( SLODWORD(expand) >= texCoordSubset.hash.indexSize )
            {
              idHashIndex::ResizeIndex(&texCoordSubset.hash, LODWORD(expand) + 1);
            }
            v100 = v95 & texCoordSubset.hash.hashMask;
            texCoordSubset.hash.indexChain[LODWORD(v98)] = texCoordSubset.hash.hash[v95 & texCoordSubset.hash.hashMask];
            *(float *)&texCoordSubset.hash.hash[v100] = v98;
            v92 = LODWORD(v98);
LABEL_120:
            v101 = expand;
            v102 = material;
            *((_DWORD *)&im1->__vftable + LODWORD(expand)) = v92;
            v28 = ++LODWORD(v101) < SLODWORD(v102->vTiling);
            expand = v101;
          }
          while ( v28 );
        }
      }
      else
      {
        for ( m = 0; m < SLODWORD(v76->vTiling); ++m )
          *((_DWORD *)&v78->__vftable + m) = m;
      }
      v103 = material;
      v104 = (matchVert_s *)R_ClearedStaticAlloc(84 * *(_DWORD *)material[1].name);
      v138 = 4 * LODWORD(v103->uTiling);
      mvTable = v104;
      mvHash = (matchVert_s **)R_ClearedStaticAlloc(v138);
      v105 = R_AllocStaticTriSurf();
      v105->numVerts = 0;
      v105->numIndexes = 0;
      R_AllocStaticTriSurfIndexes(v105, 3 * *(_DWORD *)v103[1].name);
      normal.z = 0.0;
      v105->generateNormals = !normalsParsed;
      v28 = *(_DWORD *)v103[1].name <= 0;
      floatValue = idRenderModelStatic::r_slopNormal.internalVar->floatValue;
      normal.y = 0.0;
      normal.x = 0.0;
      color = identityColor;
      tv = 0;
      expand = 0.0;
      normalEpsilon = 1.0 - floatValue;
      if ( !v28 )
      {
        v169 = 0;
        v170 = 72;
        do
        {
          k = 0;
          v176 = v170;
          do
          {
            v107 = *(_DWORD *)(v176 + *(_DWORD *)&v103[1].name[76] - 72);
            if ( v107 < 0 || v107 >= SLODWORD(v103->uTiling) )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
                common.type,
                "ConvertASEToModelSurfaces: bad vertex index in ASE file %s",
                v171->name.data);
            v11 = *(_DWORD *)&v103[1].name[4] == *(_DWORD *)v103[1].name;
            v = vRemap[v107];
            if ( v11 )
            {
              vTiling_low = LODWORD(v103->vTiling);
              if ( vTiling_low )
              {
                v109 = *(_DWORD *)(v176 + *(_DWORD *)&v103[1].name[76] - 60);
                if ( v109 < 0 || v109 >= vTiling_low )
                  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
                    common.type,
                    "ConvertASEToModelSurfaces: bad tex coord index in ASE file %s",
                    v171->name.data);
                tv = *((_DWORD *)&im1->__vftable + v109);
              }
            }
            if ( normalsParsed )
            {
              v110 = *(_DWORD *)&v103[1].name[76] + 12 * ((_DWORD)v169 + k + 3);
              v111 = *(float *)v110;
              v112 = *(float *)(v110 + 4);
              v113 = *(float *)(v110 + 8);
              normal.x = v111;
              normal.y = v112;
              normal.z = v113;
            }
            if ( v103[1].name[60] )
              color = (unsigned __int8 *)(v176 + *(_DWORD *)&v103[1].name[76]);
            v114 = mvHash[v];
            v115 = color;
            v116 = 0;
            if ( v114 )
            {
              while ( v114->tv != tv
                   || *(_DWORD *)v114->color != *(_DWORD *)color
                   || normalsParsed
                   && normal.y * v114->normal.y + normal.z * v114->normal.z + normal.x * v114->normal.x <= normalEpsilon )
              {
                v116 = v114;
                v114 = v114->next;
                if ( !v114 )
                  goto LABEL_143;
              }
            }
            else
            {
LABEL_143:
              v114 = &mvTable[v105->numVerts];
              v114->v = v;
              v114->tv = tv;
              v114->normal = normal;
              *(_DWORD *)v114->color = *(_DWORD *)v115;
              v114->next = 0;
              if ( v116 )
                v116->next = v114;
              else
                mvHash[v] = v114;
              ++v105->numVerts;
            }
            v176 += 4;
            v105->indexes[v105->numIndexes] = v114 - mvTable;
            v117 = k;
            ++v105->numIndexes;
            k = v117 + 1;
          }
          while ( v117 + 1 < 3 );
          v170 += 84;
          v169 = (float *)((char *)v169 + 7);
          v28 = ++LODWORD(expand) < *(_DWORD *)v103[1].name;
        }
        while ( v28 );
      }
      if ( v105->numIndexes > 3 * *(_DWORD *)v103[1].name )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "ConvertASEToModelSurfaces: index miscount in ASE file %s",
          v171->name.data);
      if ( v105->numVerts > 3 * *(_DWORD *)v103[1].name )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "ConvertASEToModelSurfaces: vertex miscount in ASE file %s",
          v171->name.data);
      if ( ase->materials.num )
      {
        v118 = ase->materials.list[LODWORD(v103->uOffset)];
        v119 = v118->vOffset;
        v120 = v118->uTiling;
        uOffset = -v118->uOffset;
        vOffset = v119;
        v121 = v118->vTiling;
        v122 = sin(v118->angle);
        uTiling = v120;
        vTiling = v121;
        textureSin = v122;
        textureCos = cos(v118->angle);
      }
      else
      {
        vOffset = 0.0;
        uOffset = 0.0;
        vTiling = 1.0;
        uTiling = 1.0;
        textureSin = 0.0;
        textureCos = 1.0;
      }
      R_AllocStaticTriSurfVerts(v105, v105->numVerts);
      v28 = v105->numVerts <= 0;
      expand = 0.0;
      if ( !v28 )
      {
        v123 = 0;
        p_z = &mvTable->normal.z;
        do
        {
          v125 = &v105->verts[v123];
          v125->xyz.z = 0.0;
          v125->xyz.y = 0.0;
          v125->xyz.x = 0.0;
          v125->st.y = 0.0;
          v125->st.x = 0.0;
          v125->normal.z = 0.0;
          v125->normal.y = 0.0;
          v125->normal.x = 0.0;
          v125->tangents[0].z = 0.0;
          v125->tangents[0].y = 0.0;
          v125->tangents[0].x = 0.0;
          v125->tangents[1].z = 0.0;
          v125->tangents[1].y = 0.0;
          v125->tangents[1].x = 0.0;
          v125->color[3] = 0;
          v125->color[2] = 0;
          v125->color[1] = 0;
          v125->color[0] = 0;
          v126 = *(_DWORD *)&v103[1].name[64];
          v127 = *(float *)(v126 + 12 * *((_DWORD *)p_z - 5));
          v128 = v126 + 12 * *((_DWORD *)p_z - 5);
          verts = v105->verts;
          verts[v123].xyz.x = v127;
          verts[v123].xyz.y = *(float *)(v128 + 4);
          v103 = material;
          verts[v123].xyz.z = *(float *)(v128 + 8);
          p_x = (_DWORD *)&v105->verts[v123].normal.x;
          *p_x = *((_DWORD *)p_z - 2);
          p_x[1] = *((_DWORD *)p_z - 1);
          p_x[2] = *(_DWORD *)p_z;
          *(float *)v105->verts[v123].color = *(p_z - 3);
          if ( *(_DWORD *)&v103[1].name[4] == *(_DWORD *)v103[1].name && LODWORD(v103->vTiling) )
          {
            v131 = *((_DWORD *)p_z - 4);
            v132 = *(_DWORD *)&v103[1].name[68];
            v133 = uTiling * *(float *)(v132 + 8 * v131) + uOffset;
            v134 = vTiling * *(float *)(v132 + 8 * v131 + 4) + vOffset;
            v105->verts[v123].st.x = v133 * textureCos + v134 * textureSin;
            v105->verts[v123].st.y = v134 * textureCos - v133 * textureSin;
          }
          p_z += 7;
          ++v123;
          v28 = ++LODWORD(expand) < v105->numVerts;
        }
        while ( v28 );
      }
      R_StaticFree(mvTable);
      R_StaticFree(mvHash);
      R_StaticFree((void *)im1);
      R_StaticFree(vRemap);
      v135 = (int)&v171->surfaces.list[mergeTo[objectNum]];
      v136 = *(srfTriangles_s **)(v135 + 8);
      if ( v136 )
      {
        *(_DWORD *)(v135 + 8) = R_MergeTriangles(v136, v105);
        R_FreeStaticTriSurf(v105);
        R_FreeStaticTriSurf(v136);
      }
      else
      {
        *(_DWORD *)(v135 + 8) = v105;
      }
      v28 = ++objectNum < ase->objects.num;
    }
    while ( v28 );
  }
  LOBYTE(v179) = 5;
  idHashIndex::Free(&texCoordSubset.hash);
  v179 = -1;
  idHashIndex::Free(&vertexSubset.hash);
  return 1;
}

// FUNC: public: bool __thiscall idRenderModelStatic::ConvertLWOToModelSurfaces(struct st_lwObject const *)
// local variable allocation has failed, the output may be wrong!
char __thiscall idRenderModelStatic::ConvertLWOToModelSurfaces(idRenderModelStatic *this, const st_lwObject *lwo)
{
  st_lwSurface *surf; // ebx
  st_lwSurface *v3; // eax
  int i; // ecx
  int v5; // eax
  void *v6; // esp
  bool v7; // zf
  int v8; // edi
  const char *name; // esi
  unsigned int v10; // eax
  int v11; // eax
  char *data; // edx
  const char *v13; // ecx
  char v14; // al
  const idMaterial *v15; // eax
  int v16; // edx
  idStr *v17; // esi
  const char *v18; // edi
  unsigned int v19; // eax
  int v20; // eax
  char *v21; // edx
  const char *v22; // ecx
  char v23; // al
  int v24; // eax
  st_lwSurface *next; // eax
  const char *v26; // esi
  unsigned int v27; // eax
  int v28; // edi
  int v29; // eax
  char *v30; // edx
  const char *v31; // ecx
  char v32; // al
  const idMaterial *v33; // eax
  const idMaterial *v34; // edi
  int v35; // ebx
  float v36; // esi
  int v37; // ebx
  int v38; // eax
  int v39; // esi
  int v40; // esi
  st_lwLayer *v41; // esi
  int count; // eax
  idVec3 *v44; // eax
  int v45; // edx
  bool v46; // cc
  idVec3 *v47; // ecx
  int v48; // eax
  _DWORD *p_z; // ecx
  int v50; // edi
  st_lwVMap *vmap; // eax
  int v52; // ebx
  st_lwVMap *v53; // eax
  int v54; // edx
  int v55; // ecx
  idVec2 *v56; // edx
  double v57; // st7
  _DWORD *v58; // eax
  int m; // ecx
  int v60; // ecx
  const char *v61; // edi
  unsigned int v62; // eax
  int v63; // ebx
  int v64; // eax
  char *v65; // edx
  const char *v66; // ecx
  char v67; // al
  int v68; // edx
  double v69; // st7
  double v70; // st7
  double v71; // st7
  int boxHashSize; // edi
  srfTriangles_s *v73; // edx
  int k; // ecx
  float *v75; // eax
  double v76; // st7
  float v77; // eax
  int v78; // ebx
  float v79; // ecx
  int v80; // edx
  matchVert_s *v81; // ecx
  int v82; // esi
  int v83; // esi
  int v84; // ecx
  double v85; // st7
  int v86; // edi
  int indexSize; // eax
  int v88; // eax
  int v89; // eax
  int *v90; // eax
  int ii; // ecx
  const char *v92; // eax
  const char *v93; // esi
  int v94; // ebx
  char *v95; // edx
  char *v96; // ecx
  char v97; // al
  int v98; // eax
  double v99; // st7
  double v100; // st7
  int v101; // edx
  srfTriangles_s *v102; // edi
  int n; // ecx
  float *v104; // eax
  double v105; // st7
  float v106; // eax
  int v107; // ebx
  float v108; // ecx
  int v109; // esi
  float *v110; // ecx
  int v111; // edx
  int v112; // esi
  int v113; // ecx
  double v114; // st7
  int v115; // edi
  int v116; // eax
  int v117; // eax
  int v118; // eax
  char *v119; // eax
  st_lwLayer *v120; // edi
  matchVert_s *v121; // eax
  srfTriangles_s *v122; // esi
  idRenderModelStatic *v123; // ecx
  st_lwPolygon *v124; // eax
  st_lwPolVert *v125; // eax
  double v126; // st7
  int v127; // ecx
  float v128; // edx
  float v129; // eax
  unsigned __int8 v131; // c2
  unsigned __int8 v132; // c3
  double v133; // st6
  unsigned __int64 v134; // rax
  double v135; // st6
  unsigned __int64 v136; // rax
  double v137; // st6
  st_lwPoint *v138; // eax
  int nvmaps; // ecx
  st_lwVMapPt *vm; // ebx
  st_lwVMap *v141; // eax
  unsigned int type; // ecx
  float *v143; // edi
  int jj; // esi
  _DWORD *v145; // ebx
  int v146; // eax
  int v147; // ecx
  float *v148; // edi
  int kk; // esi
  int v150; // edi
  matchVert_s *v151; // ecx
  int v152; // ebx
  matchVert_s *v153; // edx
  srfTriangles_s *v154; // esi
  float x; // eax
  int v156; // eax
  st_lwLayer *v157; // esi
  srfTriangles_s *v158; // edi
  int v159; // edx
  float *v160; // ecx
  idDrawVert *v161; // eax
  idVec3 *v162; // ebx
  _DWORD *p_x; // eax
  int v164; // ebx
  idDrawVert *verts; // edi
  _DWORD *v166; // eax
  int v167; // ebx
  st_lwSurface *v168; // eax
  int v169; // [esp-Ch] [ebp-108h]
  int v170; // [esp-8h] [ebp-104h]
  int v171; // [esp+0h] [ebp-FCh] BYREF
  idStr v172; // [esp+Ch] [ebp-F0h] BYREF
  _DWORD *v173; // [esp+2Ch] [ebp-D0h]
  idVectorSubset<idVec3,3> vertexSubset; // [esp+30h] [ebp-CCh] BYREF
  idVectorSubset<idVec2,2> texCoordSubset; // [esp+80h] [ebp-7Ch] BYREF
  st_lwPolygon *poly[2]; // [esp+C0h] [ebp-3Ch]
  int v; // [esp+C8h] [ebp-34h]
  int *mergeTo; // [esp+CCh] [ebp-30h]
  idStr str; // [esp+D0h] [ebp-2Ch] BYREF
  int v180; // [esp+F0h] [ebp-Ch]
  int v181[2]; // [esp+F4h] [ebp-8h]
  idVec2 v182; // [esp+FCh] [ebp+0h] BYREF
  int v183; // [esp+104h] [ebp+8h]
  st_lwLayer *layer; // [esp+108h] [ebp+Ch]
  idVec3 *vList; // [esp+10Ch] [ebp+10h]
  int offset; // [esp+110h] [ebp+14h]
  int keepOffset; // [esp+114h] [ebp+18h]
  idVec3 mins; // [esp+118h] [ebp+1Ch] OVERLAPPED BYREF
  int *tvRemap; // [esp+124h] [ebp+28h]
  float texCoordEpsilon; // [esp+128h] [ebp+2Ch]
  idVec2 *tvList; // [esp+12Ch] [ebp+30h]
  matchVert_s *mvTable; // [esp+130h] [ebp+34h]
  int v193; // [esp+134h] [ebp+38h]
  idVec3 maxs; // [esp+138h] [ebp+3Ch] BYREF
  int numTVertexes; // [esp+144h] [ebp+48h]
  float expand; // [esp+148h] [ebp+4Ch]
  int j; // [esp+14Ch] [ebp+50h]
  int tv; // [esp+150h] [ebp+54h]
  idRenderModelStatic *v199; // [esp+154h] [ebp+58h]
  st_lwSurface *lwoSurf; // [esp+158h] [ebp+5Ch]
  float normalEpsilon; // [esp+15Ch] [ebp+60h]
  srfTriangles_s *tri; // [esp+160h] [ebp+64h]
  int v203; // [esp+16Ch] [ebp+70h]
  _DWORD *normalsParseda; // [esp+178h] [ebp+7Ch]
  srfTriangles_s *normalsParsed; // [esp+178h] [ebp+7Ch]
  bool normalsParsed_3; // [esp+17Bh] [ebp+7Fh]

  v199 = this;
  if ( !lwo || !lwo->surf )
    return 0;
  this->timeStamp = lwo->timeStamp;
  surf = lwo->surf;
  v3 = surf;
  for ( i = 0; v3; ++i )
    v3 = v3->next;
  v5 = 4 * i + 3;
  LOBYTE(v5) = v5 & 0xFC;
  v6 = alloca(v5);
  v193 = 0;
  memset(&maxs, 0, sizeof(maxs));
  v7 = idRenderModelStatic::r_mergeModelSurfaces.internalVar->integerValue == 0;
  *(float *)&mergeTo = COERCE_FLOAT(&v171);
  if ( v7 )
  {
    numTVertexes = 0;
    if ( surf )
    {
      v8 = (int)v199;
      do
      {
        mergeTo[numTVertexes] = numTVertexes;
        name = surf->name;
        str.len = 0;
        str.alloced = 20;
        str.data = str.baseBuffer;
        str.baseBuffer[0] = 0;
        if ( name )
        {
          v10 = (unsigned int)&name[strlen(name) + 1];
          LODWORD(normalEpsilon) = v10 - (_DWORD)(name + 1);
          v11 = v10 - (_DWORD)name;
          if ( v11 > 20 )
            idStr::ReAllocate(&str, v11, 1);
          data = str.data;
          v13 = name;
          do
          {
            v14 = *v13;
            *data++ = *v13++;
          }
          while ( v14 );
          *(float *)&str.len = normalEpsilon;
        }
        v203 = 0;
        idStr::StripAbsoluteFileExtension(&str);
        v15 = declManager->FindMaterial(declManager, str.data, 1);
        v16 = **(_DWORD **)common.ip;
        LODWORD(maxs.x) = v15;
        if ( (*(int (__thiscall **)(_DWORD, int))(v16 + 28))(*(_DWORD *)common.ip, 0x40000) )
        {
          v17 = (idStr *)Memory::Allocate(0x20u);
          v = (int)v17;
          LOBYTE(v203) = 1;
          if ( v17 )
          {
            v18 = surf->name;
            v17->len = 0;
            v17->alloced = 20;
            v17->data = v17->baseBuffer;
            v17->baseBuffer[0] = 0;
            if ( v18 )
            {
              v19 = (unsigned int)&v18[strlen(v18) + 1];
              LODWORD(normalEpsilon) = v19 - (_DWORD)(v18 + 1);
              v20 = v19 - (_DWORD)v18;
              if ( v20 > v17->alloced )
                idStr::ReAllocate(v17, v20, 1);
              v21 = v17->data;
              v22 = v18;
              do
              {
                v23 = *v22;
                *v21++ = *v22++;
              }
              while ( v23 );
              *(float *)&v17->len = normalEpsilon;
            }
          }
          else
          {
            v17 = 0;
          }
          v8 = (int)v199;
          LOBYTE(v203) = 0;
          LODWORD(maxs.z) = v17;
        }
        v24 = (*(int (__thiscall **)(int))(*(_DWORD *)v8 + 84))(v8);
        (*(void (__thiscall **)(int, int, _DWORD, _DWORD, _DWORD))(*(_DWORD *)v8 + 24))(
          v8,
          v24,
          LODWORD(maxs.x),
          LODWORD(maxs.y),
          LODWORD(maxs.z));
        v203 = -1;
        idStr::FreeData(&str);
        surf = surf->next;
        ++numTVertexes;
      }
      while ( surf );
    }
  }
  else
  {
    next = surf;
    lwoSurf = surf;
    if ( surf )
    {
      tri = (srfTriangles_s *)mergeTo;
      do
      {
        v26 = next->name;
        str.len = 0;
        str.alloced = 20;
        str.data = str.baseBuffer;
        str.baseBuffer[0] = 0;
        if ( v26 )
        {
          v27 = (unsigned int)&v26[strlen(v26) + 1];
          v28 = v27 - (_DWORD)(v26 + 1);
          v29 = v27 - (_DWORD)v26;
          if ( v29 > 20 )
            idStr::ReAllocate(&str, v29, 1);
          v30 = str.data;
          v31 = v26;
          do
          {
            v32 = *v31;
            *v30++ = *v31++;
          }
          while ( v32 );
          str.len = v28;
        }
        v203 = 2;
        idStr::StripAbsoluteFileExtension(&str);
        v33 = declManager->FindMaterial(declManager, str.data, 1);
        v34 = v33;
        if ( v33->entityGui
          || v33->gui
          || v33->deform
          || LODWORD(v33->sort) == -1065353216
          || (v33->surfaceFlags & 0x400) != 0 )
        {
          v35 = (int)v199;
          v36 = COERCE_FLOAT(v199->NumSurfaces(v199));
        }
        else
        {
          v35 = (int)v199;
          v36 = 0.0;
          if ( v199->NumSurfaces(v199) > 0 )
          {
            v37 = 0;
            while ( v34 != v199->surfaces.list[v37].shader )
            {
              ++LODWORD(v36);
              ++v37;
              if ( SLODWORD(v36) >= v199->NumSurfaces(v199) )
                goto LABEL_46;
            }
            tri->bounds.b[0].x = v36;
LABEL_46:
            v35 = (int)v199;
          }
        }
        if ( LODWORD(v36) == (*(int (__thiscall **)(int))(*(_DWORD *)v35 + 84))(v35) )
        {
          tri->bounds.b[0].x = v36;
          v38 = (*(int (__thiscall **)(int))(*(_DWORD *)v35 + 84))(v35);
          (*(void (__thiscall **)(int, int, const idMaterial *, _DWORD, _DWORD))(*(_DWORD *)v35 + 24))(
            v35,
            v38,
            v34,
            LODWORD(maxs.y),
            LODWORD(maxs.z));
        }
        v203 = -1;
        idStr::FreeData(&str);
        next = lwoSurf->next;
        tri = (srfTriangles_s *)((char *)tri + 4);
        lwoSurf = next;
      }
      while ( next );
    }
  }
  idHashIndex::Init(&vertexSubset.hash, 1024, 1024);
  v39 = vertexSubset.boxHashSize * vertexSubset.boxHashSize * vertexSubset.boxHashSize;
  v203 = 3;
  idHashIndex::Free(&vertexSubset.hash);
  memset(vertexSubset.boxInvSize, 0, 24);
  vertexSubset.hash.hashSize = v39;
  vertexSubset.hash.indexSize = 128;
  vertexSubset.boxHashSize = 16;
  v203 = 4;
  idHashIndex::Init(&texCoordSubset.hash, 1024, 1024);
  v40 = texCoordSubset.boxHashSize * texCoordSubset.boxHashSize;
  LOBYTE(v203) = 5;
  idHashIndex::Free(&texCoordSubset.hash);
  memset(texCoordSubset.boxInvSize, 0, 16);
  texCoordSubset.hash.hashSize = v40;
  texCoordSubset.hash.indexSize = 128;
  texCoordSubset.boxHashSize = 16;
  v41 = lwo->layer;
  count = v41->point.count;
  LOBYTE(v203) = 6;
  layer = v41;
  if ( count <= 0 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "ConvertLWOToModelSurfaces: model '%s' has bad or missing vertex data",
      v199->name.data);
    LOBYTE(v203) = 4;
    idHashIndex::Free(&texCoordSubset.hash);
    v203 = -1;
    idHashIndex::Free(&vertexSubset.hash);
    return 0;
  }
  v44 = (idVec3 *)R_StaticAlloc(12 * count);
  v45 = 0;
  v46 = v41->point.count <= 0;
  v47 = v44;
  vList = v44;
  if ( !v46 )
  {
    v48 = 0;
    p_z = (_DWORD *)&v47->z;
    do
    {
      *(p_z - 2) = LODWORD(v41->point.pt[v48].pos[0]);
      *(p_z - 1) = LODWORD(v41->point.pt[v48].pos[2]);
      *p_z = LODWORD(v41->point.pt[v48].pos[1]);
      ++v45;
      ++v48;
      p_z += 3;
    }
    while ( v45 < v41->point.count );
  }
  v50 = 0;
  v7 = v41->nvmaps == 0;
  numTVertexes = 0;
  if ( !v7 )
  {
    vmap = v41->vmap;
    if ( vmap )
    {
      do
      {
        if ( vmap->type == 1415075158 )
          v50 += vmap->nverts;
        vmap = vmap->next;
      }
      while ( vmap );
      numTVertexes = v50;
    }
  }
  v52 = 0;
  keepOffset = 0;
  if ( !v50 )
    goto LABEL_72;
  tvList = (idVec2 *)R_StaticAlloc(8 * v50);
  v53 = v41->vmap;
  v54 = 0;
  for ( offset = 0; v53; v53 = v53->next )
  {
    if ( v53->type == 1415075158 )
    {
      v55 = 0;
      v46 = v53->nverts <= 0;
      v53->offset = v54;
      if ( !v46 )
      {
        v56 = &tvList[v54];
        do
        {
          v56->x = *v53->val[v55];
          v57 = 1.0 - v53->val[v55++][1];
          ++v56;
          v56[-1].y = v57;
        }
        while ( v55 < v53->nverts );
        v54 = offset;
      }
      v54 += v53->nverts;
      offset = v54;
    }
  }
  v7 = v41->nvmaps == 0;
  v52 = v54;
  keepOffset = v54;
  if ( v7 )
  {
LABEL_72:
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
      common.type,
      "ConvertLWOToModelSurfaces: model '%s' has bad or missing uv data",
      v199->name.data);
    v50 = 1;
    numTVertexes = 1;
    tvList = (idVec2 *)R_ClearedStaticAlloc(8);
  }
  v58 = R_StaticAlloc(4 * v41->point.count);
  v7 = !v199->fastLoad;
  offset = (int)v58;
  if ( v7 )
  {
    v60 = v41->point.count;
    texCoordEpsilon = idRenderModelStatic::r_slopVertex.internalVar->floatValue;
    expand = texCoordEpsilon * 64.0;
    v61 = va("idRenderModelStatic::ConvertLWOToModelSurfaces: vList = %08x, count = %d, offset = %d\n", vList, v60, v52);
    str.len = 0;
    str.alloced = 20;
    str.data = str.baseBuffer;
    str.baseBuffer[0] = 0;
    if ( v61 )
    {
      v62 = (unsigned int)&v61[strlen(v61) + 1];
      v63 = v62 - (_DWORD)(v61 + 1);
      v64 = v62 - (_DWORD)v61;
      if ( v64 > 20 )
        idStr::ReAllocate(&str, v64, 1);
      v65 = str.data;
      v66 = v61;
      do
      {
        v67 = *v66;
        *v65++ = *v66++;
      }
      while ( v67 );
      str.len = v63;
    }
    v68 = *(_DWORD *)common.type;
    LOBYTE(v203) = 7;
    (*(void (__thiscall **)(netadrtype_t, char *))(v68 + 100))(common.type, str.data);
    (*(void (__fastcall **)(idSIMDProcessor *, idVec3 *, idVec3 *, idVec3 *, int))&SIMDProcessor->gap7C[16])(
      SIMDProcessor,
      &mins,
      &maxs,
      vList,
      v41->point.count);
    (*(void (__thiscall **)(netadrtype_t, _DWORD))(*(_DWORD *)common.type + 100))(common.type, 0);
    mins.x = mins.x - expand;
    mins.y = mins.y - expand;
    mins.z = mins.z - expand;
    maxs.x = maxs.x + expand;
    maxs.y = maxs.y + expand;
    maxs.z = maxs.z + expand;
    idHashIndex::Free(&vertexSubset.hash);
    vertexSubset.mins = mins;
    v69 = (maxs.x - mins.x) * 0.03125;
    vertexSubset.hash.hashSize = 0x8000;
    vertexSubset.hash.indexSize = 1024;
    vertexSubset.maxs = maxs;
    vertexSubset.boxHashSize = 32;
    vertexSubset.boxInvSize[0] = 1.0 / v69;
    vertexSubset.boxHalfSize[0] = v69 * 0.5;
    v70 = (maxs.y - mins.y) * 0.03125;
    vertexSubset.boxInvSize[1] = 1.0 / v70;
    vertexSubset.boxHalfSize[1] = v70 * 0.5;
    v71 = (maxs.z - mins.z) * 0.03125;
    vertexSubset.boxInvSize[2] = 1.0 / v71;
    j = 0;
    vertexSubset.boxHalfSize[2] = v71 * 0.5;
    if ( v41->point.count > 0 )
    {
      mvTable = (matchVert_s *)vList;
      tri = (srfTriangles_s *)((char *)vList - (char *)&vertexSubset.mins);
      do
      {
        boxHashSize = vertexSubset.boxHashSize;
        v73 = tri;
        for ( k = 0; k < 3; v181[k] = (int)v76 )
        {
          v75 = (float *)((char *)&vertexSubset.mins.x + k * 4);
          ++k;
          v76 = (*(float *)((char *)v75 + (_DWORD)v73) - *v75 - v75[10]) * v75[7];
          LODWORD(v77) = HIWORD(lwoSurf);
          BYTE1(v77) = HIBYTE(lwoSurf) | 0xC;
          normalEpsilon = v77;
        }
        v78 = 0;
        LODWORD(v79) = vertexSubset.hash.hashMask & vertexSubset.hash.lookupMask;
        LODWORD(normalEpsilon) = vertexSubset.hash.hashMask & vertexSubset.hash.lookupMask;
        do
        {
          v80 = vertexSubset.hash.hash[LODWORD(v79) & (LODWORD(v182.y)
                                                     + boxHashSize
                                                     * (LODWORD(v182.x)
                                                      + boxHashSize * (v181[1] + (v78 & 1))
                                                      + ((v78 >> 1) & 1))
                                                     + ((v78 >> 2) & 1))];
          if ( v80 >= 0 )
          {
            do
            {
              v81 = mvTable;
              v82 = 0;
              while ( 1 )
              {
                *(float *)&tvRemap = *(float *)((char *)&v81->next + (char *)&vList[v80] - (char *)mvTable)
                                   - *(float *)&v81->next;
                HIBYTE(tvRemap) &= ~0x80u;
                if ( *(float *)&tvRemap > (double)texCoordEpsilon )
                  break;
                ++v82;
                v81 = (matchVert_s *)((char *)v81 + 4);
                if ( v82 >= 3 )
                  goto LABEL_105;
              }
              v80 = vertexSubset.hash.indexChain[v80 & vertexSubset.hash.lookupMask];
            }
            while ( v80 >= 0 );
            boxHashSize = vertexSubset.boxHashSize;
            v79 = normalEpsilon;
          }
          ++v78;
        }
        while ( v78 < 8 );
        v83 = 0;
        v84 = 0;
        do
        {
          v85 = *(float *)((char *)&vertexSubset.mins.x + (_DWORD)tri + 4 * v84) - *(&vertexSubset.mins.x + v84);
          ++v84;
          LODWORD(normalEpsilon) = (int)(v85 * *((float *)&vertexSubset.boxHashSize + v84));
          v83 = v83 * boxHashSize + LODWORD(normalEpsilon);
        }
        while ( v84 < 3 );
        v86 = j;
        if ( vertexSubset.hash.hash == idHashIndex::INVALID_INDEX )
        {
          indexSize = vertexSubset.hash.indexSize;
          if ( j >= vertexSubset.hash.indexSize )
            indexSize = j + 1;
          idHashIndex::Allocate(&vertexSubset.hash, vertexSubset.hash.hashSize, indexSize);
        }
        else if ( j >= vertexSubset.hash.indexSize )
        {
          idHashIndex::ResizeIndex(&vertexSubset.hash, j + 1);
        }
        v88 = v83 & vertexSubset.hash.hashMask;
        vertexSubset.hash.indexChain[v86] = vertexSubset.hash.hash[v83 & vertexSubset.hash.hashMask];
        vertexSubset.hash.hash[v88] = v86;
        v80 = v86;
LABEL_105:
        v89 = j;
        *(_DWORD *)(offset + 4 * j) = v80;
        mvTable = (matchVert_s *)((char *)mvTable + 12);
        tri = (srfTriangles_s *)((char *)tri + 12);
        v46 = ++v89 < layer->point.count;
        j = v89;
      }
      while ( v46 );
    }
    LOBYTE(v203) = 6;
    idStr::FreeData(&str);
    v52 = keepOffset;
    v50 = numTVertexes;
  }
  else
  {
    for ( m = 0; m < v41->point.count; ++m )
      v58[m] = m;
  }
  *(float *)&v90 = COERCE_FLOAT(R_StaticAlloc(4 * v50));
  v7 = !v199->fastLoad;
  tvRemap = v90;
  if ( v7 )
  {
    texCoordEpsilon = idRenderModelStatic::r_slopTexCoord.internalVar->floatValue;
    *(float *)&tri = texCoordEpsilon * 64.0;
    v92 = va(
            "idRenderModelStatic::ConvertLWOToModelSurfaces: tvList = %08x, count = %d, offset = %d\n",
            tvList,
            v50,
            v52);
    v93 = v92;
    v172.len = 0;
    v172.alloced = 20;
    v172.data = v172.baseBuffer;
    v172.baseBuffer[0] = 0;
    if ( v92 )
    {
      v94 = strlen(v92);
      if ( v94 + 1 > 20 )
        idStr::ReAllocate(&v172, v94 + 1, 1);
      v95 = v172.data;
      v96 = (char *)v93;
      do
      {
        v97 = *v96;
        *v95++ = *v96++;
      }
      while ( v97 );
      v172.len = v94;
    }
    v98 = *(_DWORD *)common.type;
    LOBYTE(v203) = 8;
    (*(void (__thiscall **)(netadrtype_t, char *))(v98 + 100))(common.type, v172.data);
    (*(void (__fastcall **)(idSIMDProcessor *, float *, idVec2 *, idVec2 *, int))&SIMDProcessor->gap7C[20])(
      SIMDProcessor,
      &mins.y,
      &v182,
      tvList,
      v50);
    (*(void (__thiscall **)(netadrtype_t, _DWORD))(*(_DWORD *)common.type + 100))(common.type, 0);
    mins.y = mins.y - *(float *)&tri;
    mins.z = mins.z - *(float *)&tri;
    v182.x = v182.x + *(float *)&tri;
    v182.y = v182.y + *(float *)&tri;
    idHashIndex::Free(&texCoordSubset.hash);
    v99 = (v182.x - mins.y) * 0.03125;
    texCoordSubset.hash.hashSize = 1024;
    texCoordSubset.hash.indexSize = 1024;
    texCoordSubset.mins = *(idVec2 *)&mins.y;
    texCoordSubset.maxs = v182;
    texCoordSubset.boxHashSize = 32;
    j = 0;
    texCoordSubset.boxInvSize[0] = 1.0 / v99;
    texCoordSubset.boxHalfSize[0] = v99 * 0.5;
    v100 = (v182.y - mins.z) * 0.03125;
    texCoordSubset.boxInvSize[1] = 1.0 / v100;
    texCoordSubset.boxHalfSize[1] = v100 * 0.5;
    if ( v50 > 0 )
    {
      tv = (int)tvList;
      tri = (srfTriangles_s *)((char *)tvList - (char *)&texCoordSubset.mins);
      do
      {
        v101 = texCoordSubset.boxHashSize;
        v102 = tri;
        for ( n = 0; n < 2; poly[n] = (st_lwPolygon *)(int)v105 )
        {
          v104 = (float *)((char *)&texCoordSubset.mins.x + n * 4);
          ++n;
          v105 = (*(float *)((char *)v104 + (_DWORD)v102) - *v104 - v104[7]) * v104[5];
          LODWORD(v106) = HIWORD(lwoSurf);
          BYTE1(v106) = HIBYTE(lwoSurf) | 0xC;
          normalEpsilon = v106;
        }
        v107 = 0;
        LODWORD(v108) = texCoordSubset.hash.hashMask & texCoordSubset.hash.lookupMask;
        LODWORD(normalEpsilon) = texCoordSubset.hash.hashMask & texCoordSubset.hash.lookupMask;
        do
        {
          v109 = texCoordSubset.hash.hash[LODWORD(v108) & (v + v101 * ((int)poly[1] + (v107 & 1)) + ((v107 >> 1) & 1))];
          if ( v109 >= 0 )
          {
            do
            {
              v110 = (float *)tv;
              v111 = 0;
              while ( 1 )
              {
                *(float *)&mvTable = *(float *)((char *)v110 + (_DWORD)&tvList[v109] - tv) - *v110;
                HIBYTE(mvTable) &= ~0x80u;
                if ( *(float *)&mvTable > (double)texCoordEpsilon )
                  break;
                ++v111;
                ++v110;
                if ( v111 >= 2 )
                  goto LABEL_139;
              }
              v109 = texCoordSubset.hash.indexChain[v109 & texCoordSubset.hash.lookupMask];
            }
            while ( v109 >= 0 );
            v101 = texCoordSubset.boxHashSize;
            v102 = tri;
            v108 = normalEpsilon;
          }
          ++v107;
        }
        while ( v107 < 4 );
        v112 = 0;
        v113 = 0;
        do
        {
          v114 = *(float *)((char *)&texCoordSubset.mins.x + (_DWORD)v102 + 4 * v113) - *(&texCoordSubset.mins.x + v113);
          ++v113;
          LODWORD(normalEpsilon) = (int)(v114 * *((float *)&texCoordSubset.boxHashSize + v113));
          v112 = v112 * v101 + LODWORD(normalEpsilon);
        }
        while ( v113 < 2 );
        v115 = j;
        if ( texCoordSubset.hash.hash == idHashIndex::INVALID_INDEX )
        {
          v116 = texCoordSubset.hash.indexSize;
          if ( j >= texCoordSubset.hash.indexSize )
            v116 = j + 1;
          idHashIndex::Allocate(&texCoordSubset.hash, texCoordSubset.hash.hashSize, v116);
        }
        else if ( j >= texCoordSubset.hash.indexSize )
        {
          idHashIndex::ResizeIndex(&texCoordSubset.hash, j + 1);
        }
        v117 = v112 & texCoordSubset.hash.hashMask;
        texCoordSubset.hash.indexChain[v115] = texCoordSubset.hash.hash[v112 & texCoordSubset.hash.hashMask];
        texCoordSubset.hash.hash[v117] = v115;
        v109 = v115;
LABEL_139:
        v118 = j;
        tvRemap[j] = v109;
        tv += 8;
        tri = (srfTriangles_s *)((char *)tri + 8);
        j = v118 + 1;
      }
      while ( v118 + 1 < numTVertexes );
    }
    LOBYTE(v203) = 6;
    idStr::FreeData(&v172);
  }
  else
  {
    for ( ii = 0; ii < v50; ++ii )
      v90[ii] = ii;
  }
  lwoSurf = lwo->surf;
  numTVertexes = 0;
  if ( lwoSurf )
  {
    while ( 1 )
    {
      v119 = declManager->FindMaterial(declManager, lwoSurf->name, 1)->renderBump.data;
      normalsParsed_3 = 1;
      if ( v119 )
        normalsParsed_3 = *v119 == 0;
      v120 = layer;
      *(float *)&v121 = COERCE_FLOAT(R_ClearedStaticAlloc(84 * layer->polygon.count));
      v170 = 4 * v120->point.count;
      mvTable = v121;
      texCoordEpsilon = COERCE_FLOAT(R_ClearedStaticAlloc(v170));
      *(float *)&v122 = COERCE_FLOAT(R_AllocStaticTriSurf());
      v122->numVerts = 0;
      v122->numIndexes = 0;
      v169 = 3 * v120->polygon.count;
      tri = v122;
      R_AllocStaticTriSurfIndexes(v122, v169);
      v123 = v199;
      v122->generateNormals = !normalsParsed_3;
      normalEpsilon = v123->fastLoad ? 1.0 : 1.0 - idRenderModelStatic::r_slopNormal.internalVar->floatValue;
      v46 = v120->polygon.count <= 0;
      j = 0;
      if ( !v46 )
        break;
LABEL_215:
      v157 = layer;
      v158 = tri;
      if ( tri->numIndexes > 3 * layer->polygon.count )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "ConvertLWOToModelSurfaces: index miscount in LWO file %s",
          v199->name.data);
      if ( v158->numVerts > 3 * v157->polygon.count )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "ConvertLWOToModelSurfaces: vertex miscount in LWO file %s",
          v199->name.data);
      R_AllocStaticTriSurfVerts(v158, v158->numVerts);
      v46 = v158->numVerts <= 0;
      j = 0;
      if ( !v46 )
      {
        v159 = 0;
        v160 = &mvTable->normal.z;
        do
        {
          v161 = &v158->verts[v159];
          v162 = vList;
          v161->xyz.z = 0.0;
          v161->xyz.y = 0.0;
          v161->xyz.x = 0.0;
          v161->st.y = 0.0;
          v161->st.x = 0.0;
          v161->normal.z = 0.0;
          v161->normal.y = 0.0;
          v161->normal.x = 0.0;
          v161->tangents[0].z = 0.0;
          v161->tangents[0].y = 0.0;
          v161->tangents[0].x = 0.0;
          v161->tangents[1].z = 0.0;
          v161->tangents[1].y = 0.0;
          v161->tangents[1].x = 0.0;
          v161->color[3] = 0;
          v161->color[2] = 0;
          v161->color[1] = 0;
          v161->color[0] = 0;
          normalsParseda = (_DWORD *)&v162[*((_DWORD *)v160 - 5)].x;
          p_x = (_DWORD *)&v158->verts[v159].xyz.x;
          *p_x = *normalsParseda;
          p_x[1] = normalsParseda[1];
          p_x[2] = normalsParseda[2];
          if ( tvList )
          {
            v164 = *((_DWORD *)v160 - 4);
            verts = v158->verts;
            verts[v159].st.x = tvList[v164].x;
            verts[v159].st.y = tvList[v164].y;
            v158 = tri;
          }
          v166 = (_DWORD *)&v158->verts[v159].normal.x;
          *v166 = *((_DWORD *)v160 - 2);
          v166[1] = *((_DWORD *)v160 - 1);
          v166[2] = *(_DWORD *)v160;
          *(float *)v158->verts[v159].color = *(v160 - 3);
          v160 += 7;
          ++v159;
          v46 = ++j < v158->numVerts;
        }
        while ( v46 );
      }
      R_StaticFree(mvTable);
      R_StaticFree((void *)LODWORD(texCoordEpsilon));
      v167 = (int)&v199->surfaces.list[mergeTo[numTVertexes]];
      normalsParsed = *(srfTriangles_s **)(v167 + 8);
      if ( normalsParsed )
      {
        *(_DWORD *)(v167 + 8) = R_MergeTriangles(normalsParsed, v158);
        R_FreeStaticTriSurf(v158);
        R_FreeStaticTriSurf(normalsParsed);
      }
      else
      {
        *(_DWORD *)(v167 + 8) = v158;
      }
      v168 = lwoSurf->next;
      ++numTVertexes;
      lwoSurf = v168;
      if ( !v168 )
        goto LABEL_228;
    }
    keepOffset = 0;
    while ( 1 )
    {
      v124 = (st_lwPolygon *)((char *)layer->polygon.pol + keepOffset);
      v7 = v124->surf == lwoSurf;
      poly[0] = v124;
      if ( v7 )
        break;
LABEL_214:
      keepOffset += 40;
      v46 = ++j < layer->polygon.count;
      if ( !v46 )
        goto LABEL_215;
    }
    if ( v124->nverts != 3 )
    {
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
        common.type,
        "ConvertLWOToModelSurfaces: model %s has too many verts for a poly! Make sure you triplet it down",
        v199->name.data);
      goto LABEL_214;
    }
    v180 = 0;
    while ( 1 )
    {
      v125 = poly[0]->v;
      v126 = *(float *)((char *)&v125->norm[2] + v180);
      v127 = *(_DWORD *)(offset + 4 * *(int *)((char *)&v125->index + v180));
      v128 = *(float *)((char *)v125->norm + v180);
      v129 = *(float *)((char *)&v125->norm[1] + v180);
      maxs.x = v128;
      maxs.z = v129;
      v = v127;
      if ( v132 | v131 )
      {
        if ( v126 == 0.0 )
        {
          if ( maxs.z <= 0.0 )
          {
            if ( maxs.z != -1.0 )
              maxs.z = -1.0;
          }
          else if ( maxs.z != 1.0 )
          {
            maxs.z = 1.0;
          }
          goto LABEL_186;
        }
        if ( maxs.z == 0.0 )
        {
          if ( v126 <= 0.0 )
          {
            if ( v126 != -1.0 )
              v126 = -1.0;
          }
          else if ( v126 != 1.0 )
          {
            v126 = 1.0;
          }
          goto LABEL_186;
        }
      }
      else if ( v126 == 0.0 && maxs.z == 0.0 )
      {
        if ( maxs.x <= 0.0 )
        {
          if ( maxs.x != -1.0 )
            maxs.x = -1.0;
        }
        else if ( maxs.x != 1.0 )
        {
          maxs.x = 1.0;
        }
        goto LABEL_186;
      }
      tv = LODWORD(maxs.x) & 0x7FFFFFFF;
      if ( COERCE_FLOAT(LODWORD(maxs.x) & 0x7FFFFFFF) == 1.0 )
        break;
      *(float *)v181 = v126;
      v181[0] &= ~0x80000000;
      if ( *(float *)v181 == 1.0 )
      {
        if ( maxs.x != 0.0 || maxs.z != 0.0 )
        {
          maxs.z = 0.0;
          maxs.x = 0.0;
        }
        goto LABEL_186;
      }
      tv = LODWORD(maxs.z) & 0x7FFFFFFF;
      if ( COERCE_FLOAT(LODWORD(maxs.z) & 0x7FFFFFFF) == 1.0 && (maxs.x != 0.0 || v126 != 0.0) )
      {
        maxs.x = 0.0;
LABEL_185:
        v126 = 0.0;
      }
LABEL_186:
      v133 = lwoSurf->color.rgb[0];
      tv = 0;
      v134 = (unsigned __int64)(v133 * 255.0);
      v135 = lwoSurf->color.rgb[1] * 255.0;
      LOBYTE(expand) = v134;
      v136 = (unsigned __int64)v135;
      v137 = lwoSurf->color.rgb[2] * 255.0;
      BYTE1(expand) = v136;
      BYTE2(expand) = (unsigned __int64)v137;
      v173 = (int *)((char *)&poly[0]->v->index + v180);
      v138 = &layer->point.pt[*v173];
      nvmaps = v138->nvmaps;
      HIBYTE(expand) = -1;
      if ( nvmaps > 0 )
      {
        vm = v138->vm;
        v183 = nvmaps;
        do
        {
          v141 = vm->vmap;
          type = vm->vmap->type;
          if ( type == 1415075158 )
            tv = tvRemap[vm->index + v141->offset];
          if ( type == 1380401729 )
          {
            v143 = v141->val[vm->index];
            for ( jj = 0; jj < 4; ++jj )
              *((_BYTE *)&expand + jj) = (unsigned __int64)(*v143++ * 255.0);
          }
          ++vm;
          --v183;
        }
        while ( v183 );
      }
      if ( (int)v173[4] > 0 )
      {
        v145 = (_DWORD *)v173[5];
        v183 = v173[4];
        do
        {
          v146 = *v145;
          v147 = *(_DWORD *)(*v145 + 12);
          if ( v147 == 1415075158 )
            tv = tvRemap[v145[1] + *(_DWORD *)(v146 + 40)];
          if ( v147 == 1380401729 )
          {
            v148 = *(float **)(*(_DWORD *)(v146 + 36) + 4 * v145[1]);
            for ( kk = 0; kk < 4; ++kk )
              *((_BYTE *)&expand + kk) = (unsigned __int64)(*v148++ * 255.0);
          }
          v145 += 2;
          --v183;
        }
        while ( v183 );
      }
      v150 = v;
      v151 = *(matchVert_s **)(LODWORD(texCoordEpsilon) + 4 * v);
      v152 = tv;
      v153 = 0;
      if ( v151 )
      {
        while ( v151->tv != tv
             || *(_DWORD *)v151->color != LODWORD(expand)
             || normalsParsed_3
             && maxs.z * v151->normal.z + v126 * v151->normal.y + maxs.x * v151->normal.x <= normalEpsilon )
        {
          v153 = v151;
          v151 = v151->next;
          if ( !v151 )
            goto LABEL_208;
        }
        v154 = tri;
      }
      else
      {
LABEL_208:
        v154 = tri;
        v151 = &mvTable[tri->numVerts];
        x = maxs.x;
        v151->v = v;
        v151->tv = v152;
        v151->normal.y = v126;
        v151->normal.x = x;
        v151->normal.z = maxs.z;
        *(float *)v151->color = expand;
        v151->next = 0;
        if ( v153 )
          v153->next = v151;
        else
          *(_DWORD *)(LODWORD(texCoordEpsilon) + 4 * v150) = v151;
        ++v154->numVerts;
      }
      v154->indexes[v154->numIndexes] = v151 - mvTable;
      v156 = v180;
      ++v154->numIndexes;
      v180 = v156 + 24;
      if ( v156 + 24 >= 72 )
        goto LABEL_214;
    }
    if ( v126 == 0.0 && maxs.z == 0.0 )
      goto LABEL_186;
    maxs.z = 0.0;
    goto LABEL_185;
  }
LABEL_228:
  R_StaticFree(tvRemap);
  R_StaticFree((void *)offset);
  R_StaticFree(tvList);
  R_StaticFree(vList);
  LOBYTE(v203) = 4;
  idHashIndex::Free(&texCoordSubset.hash);
  v203 = -1;
  idHashIndex::Free(&vertexSubset.hash);
  return 1;
}

// FUNC: public: bool __thiscall idRenderModelStatic::ConvertMAToModelSurfaces(struct maModel_s const *)
char __thiscall idRenderModelStatic::ConvertMAToModelSurfaces(idRenderModelStatic *this, const maModel_s *ma)
{
  int num; // esi
  int v5; // eax
  void *v6; // esp
  int v7; // eax
  int v8; // eax
  int *v9; // ecx
  int j; // esi
  int v11; // eax
  const idMaterial *v12; // eax
  idRenderModelStatic_vtbl *v13; // edx
  int v14; // eax
  int v15; // eax
  int materialRef; // eax
  const idMaterial *defaultMaterial; // eax
  bool v18; // zf
  int v19; // esi
  idRenderModelStatic_vtbl *v20; // edx
  int v21; // eax
  bool v22; // cc
  int v23; // esi
  int v24; // esi
  int v25; // ebx
  maObject_t *v26; // esi
  int v27; // eax
  const idMaterial *v28; // eax
  char *data; // eax
  int v30; // eax
  int v31; // edx
  const idMaterial *v32; // ecx
  idSIMDProcessor_vtbl *v33; // eax
  double v34; // st7
  double v35; // st7
  double v36; // st7
  int boxHashSize; // edi
  float *v38; // edx
  int v39; // edx
  int m; // ecx
  float *v41; // eax
  double v42; // st7
  int *v43; // eax
  int v44; // ebx
  int *v45; // ecx
  int v46; // edx
  float *v47; // ecx
  int v48; // esi
  int v49; // esi
  int n; // ecx
  double v51; // st7
  float v52; // edi
  int indexSize; // eax
  int v54; // eax
  float v55; // eax
  int v56; // esi
  int *v57; // eax
  int *v58; // edx
  int jj; // eax
  int v60; // edx
  idSIMDProcessor_vtbl *v61; // eax
  double v62; // st7
  double v63; // st7
  float *v64; // ebx
  int v65; // edi
  int ii; // ecx
  float *v67; // eax
  double v68; // st7
  matchVert_s **v69; // eax
  matchVert_s **v70; // ecx
  int v71; // edx
  int v72; // esi
  int v73; // edx
  float *v74; // ecx
  unsigned int v75; // esi
  int v76; // ecx
  double v77; // st7
  float v78; // edi
  int v79; // eax
  int v80; // eax
  float v81; // eax
  int v82; // edx
  _DWORD *v83; // ebx
  matchVert_s *v84; // eax
  srfTriangles_s *v85; // esi
  double floatValue; // st7
  int v87; // edi
  int v88; // eax
  int v89; // edi
  int v90; // eax
  float v91; // ecx
  float v92; // edx
  float v93; // eax
  int v94; // eax
  matchVert_s *v95; // ecx
  unsigned __int8 *v96; // edi
  matchVert_s *v97; // edx
  int v98; // eax
  int v99; // edx
  float *p_z; // ecx
  idDrawVert *v101; // eax
  int v102; // edi
  float v103; // ebx
  int v104; // edi
  idDrawVert *verts; // eax
  _DWORD *p_x; // eax
  int v107; // eax
  int v108; // edi
  double v109; // st7
  double v110; // st6
  int v111; // edi
  srfTriangles_s *v112; // ebx
  idVec3 *vertexes; // [esp-8h] [ebp-E0h]
  int v114; // [esp-8h] [ebp-E0h]
  int numVertexes; // [esp-4h] [ebp-DCh]
  int v116; // [esp-4h] [ebp-DCh]
  _DWORD v117[5]; // [esp+0h] [ebp-D8h] BYREF
  float normalEpsilon; // [esp+14h] [ebp-C4h]
  modelSurface_s surf; // [esp+18h] [ebp-C0h]
  idVectorSubset<idVec3,3> vertexSubset; // [esp+28h] [ebp-B0h] BYREF
  idVectorSubset<idVec2,2> texCoordSubset; // [esp+78h] [ebp-60h] BYREF
  float vertexEpsilon; // [esp+B8h] [ebp-20h]
  float texCoordEpsilon; // [esp+BCh] [ebp-1Ch]
  float v124; // [esp+C0h] [ebp-18h]
  int v; // [esp+C4h] [ebp-14h]
  int tv; // [esp+C8h] [ebp-10h]
  float v127; // [esp+CCh] [ebp-Ch]
  idVec3 normal; // [esp+D0h] [ebp-8h]
  unsigned __int8 *color; // [esp+DCh] [ebp+4h]
  idVec3 maxs; // [esp+E0h] [ebp+8h] BYREF
  idVec3 mins; // [esp+ECh] [ebp+14h] BYREF
  idVec2 v132; // [esp+F8h] [ebp+20h] BYREF
  idVec2 v133; // [esp+100h] [ebp+28h] BYREF
  int k; // [esp+108h] [ebp+30h]
  int *mergeTo; // [esp+10Ch] [ebp+34h]
  idRenderModelStatic *v136; // [esp+110h] [ebp+38h]
  float *v137; // [esp+114h] [ebp+3Ch]
  int v138; // [esp+118h] [ebp+40h]
  int objectNum; // [esp+11Ch] [ebp+44h]
  const idMaterial *im1; // [esp+120h] [ebp+48h]
  matchVert_s *mvTable; // [esp+124h] [ebp+4Ch]
  int *tvRemap; // [esp+128h] [ebp+50h]
  matchVert_s **mvHash; // [esp+12Ch] [ebp+54h]
  int i; // [esp+130h] [ebp+58h]
  int v145; // [esp+134h] [ebp+5Ch]
  bool normalsParsed; // [esp+13Bh] [ebp+63h]
  float expand; // [esp+13Ch] [ebp+64h]
  int v148; // [esp+148h] [ebp+70h]

  v136 = this;
  if ( !ma || ma->objects.num < 1 )
    return 0;
  this->timeStamp = ma->timeStamp;
  num = ma->objects.num;
  v5 = 4 * num + 3;
  LOBYTE(v5) = v5 & 0xFC;
  v6 = alloca(v5);
  v7 = ma->materials.num;
  mergeTo = v117;
  if ( v7 )
  {
    if ( idRenderModelStatic::r_mergeModelSurfaces.internalVar->integerValue )
    {
      v15 = 0;
      i = 0;
      if ( num > 0 )
      {
        do
        {
          materialRef = ma->objects.list[v15]->materialRef;
          if ( materialRef < 0 )
            defaultMaterial = tr.defaultMaterial;
          else
            defaultMaterial = declManager->FindMaterial(declManager, ma->materials.list[materialRef], 1);
          v18 = defaultMaterial->entityGui == 0;
          im1 = defaultMaterial;
          if ( !v18
            || defaultMaterial->gui
            || defaultMaterial->deform
            || LODWORD(defaultMaterial->sort) == -1065353216
            || (defaultMaterial->surfaceFlags & 0x400) != 0 )
          {
            v19 = this->NumSurfaces(this);
          }
          else
          {
            v19 = 0;
            if ( this->NumSurfaces(this) > 0 )
            {
              objectNum = 0;
              while ( im1 != *(const idMaterial **)((char *)&this->surfaces.list->shader + objectNum) )
              {
                v20 = this->__vftable;
                objectNum += 16;
                if ( ++v19 >= v20->NumSurfaces(this) )
                  goto LABEL_32;
              }
              mergeTo[i] = v19;
            }
          }
LABEL_32:
          if ( v19 == this->NumSurfaces(this) )
          {
            mergeTo[i] = v19;
            v21 = this->NumSurfaces(this);
            ((void (__thiscall *)(idRenderModelStatic *, int, const idMaterial *, _DWORD, idStr *))this->AddSurface)(
              this,
              v21,
              im1,
              0,
              surf.mOriginalSurfaceName);
          }
          v15 = i + 1;
          v22 = ++i < ma->objects.num;
        }
        while ( v22 );
      }
    }
    else
    {
      for ( j = 0; j < ma->objects.num; ++j )
      {
        mergeTo[j] = j;
        v11 = ma->objects.list[j]->materialRef;
        if ( v11 < 0 )
          v12 = tr.defaultMaterial;
        else
          v12 = declManager->FindMaterial(declManager, ma->materials.list[v11], 1);
        v13 = this->__vftable;
        surf.shader = v12;
        v14 = v13->NumSurfaces(this);
        ((void (__thiscall *)(idRenderModelStatic *, int, const idMaterial *, _DWORD, idStr *))this->AddSurface)(
          this,
          v14,
          surf.shader,
          0,
          surf.mOriginalSurfaceName);
      }
    }
  }
  else
  {
    ((void (__thiscall *)(idRenderModelStatic *, _DWORD, const idMaterial *, _DWORD, idStr *))this->AddSurface)(
      this,
      0,
      tr.defaultMaterial,
      0,
      surf.mOriginalSurfaceName);
    v8 = 0;
    if ( ma->objects.num > 0 )
    {
      v9 = mergeTo;
      do
        v9[v8++] = 0;
      while ( v8 < ma->objects.num );
    }
  }
  idHashIndex::Init(&vertexSubset.hash, 1024, 1024);
  v23 = vertexSubset.boxHashSize * vertexSubset.boxHashSize * vertexSubset.boxHashSize;
  v148 = 0;
  idHashIndex::Free(&vertexSubset.hash);
  memset(vertexSubset.boxInvSize, 0, 24);
  vertexSubset.hash.hashSize = v23;
  vertexSubset.hash.indexSize = 128;
  vertexSubset.boxHashSize = 16;
  v148 = 1;
  idHashIndex::Init(&texCoordSubset.hash, 1024, 1024);
  v24 = texCoordSubset.boxHashSize * texCoordSubset.boxHashSize;
  LOBYTE(v148) = 2;
  idHashIndex::Free(&texCoordSubset.hash);
  memset(texCoordSubset.boxInvSize, 0, 16);
  texCoordSubset.hash.hashSize = v24;
  texCoordSubset.hash.indexSize = 128;
  texCoordSubset.boxHashSize = 16;
  v25 = ma->objects.num;
  LOBYTE(v148) = 3;
  objectNum = 0;
  if ( v25 > 0 )
  {
    do
    {
      v26 = ma->objects.list[objectNum];
      v27 = v26->materialRef;
      i = (int)v26;
      if ( v27 < 0 )
        v28 = tr.defaultMaterial;
      else
        v28 = declManager->FindMaterial(declManager, ma->materials.list[v27], 1);
      data = v28->renderBump.data;
      normalsParsed = v26->mesh.normalsParsed;
      if ( data && *data )
        normalsParsed = 0;
      im1 = (const idMaterial *)R_StaticAlloc(4 * v26->mesh.numVertexes);
      if ( v136->fastLoad )
      {
        v30 = 0;
        if ( v26->mesh.numVertexes > 0 )
        {
          v31 = i;
          v32 = im1;
          do
          {
            *((_DWORD *)&v32->__vftable + v30) = v30;
            ++v30;
          }
          while ( v30 < *(_DWORD *)(v31 + 264) );
        }
      }
      else
      {
        v33 = SIMDProcessor->__vftable;
        vertexEpsilon = idRenderModelStatic::r_slopVertex.internalVar->floatValue;
        numVertexes = v26->mesh.numVertexes;
        vertexes = v26->mesh.vertexes;
        expand = vertexEpsilon * 64.0;
        (*(void (__fastcall **)(idSIMDProcessor *, idVec3 *, idVec3 *, idVec3 *, int))&v33->gap7C[16])(
          SIMDProcessor,
          &mins,
          &maxs,
          vertexes,
          numVertexes);
        mins.x = mins.x - expand;
        mins.y = mins.y - expand;
        mins.z = mins.z - expand;
        maxs.x = maxs.x + expand;
        maxs.y = maxs.y + expand;
        maxs.z = maxs.z + expand;
        idHashIndex::Free(&vertexSubset.hash);
        vertexSubset.mins = mins;
        v34 = (maxs.x - mins.x) * 0.03125;
        vertexSubset.hash.hashSize = 0x8000;
        vertexSubset.hash.indexSize = 1024;
        vertexSubset.maxs = maxs;
        vertexSubset.boxHashSize = 32;
        expand = 0.0;
        vertexSubset.boxInvSize[0] = 1.0 / v34;
        vertexSubset.boxHalfSize[0] = v34 * 0.5;
        v35 = (maxs.y - mins.y) * 0.03125;
        vertexSubset.boxInvSize[1] = 1.0 / v35;
        vertexSubset.boxHalfSize[1] = v35 * 0.5;
        v36 = (maxs.z - mins.z) * 0.03125;
        vertexSubset.boxInvSize[2] = 1.0 / v36;
        vertexSubset.boxHalfSize[2] = v36 * 0.5;
        if ( v26->mesh.numVertexes > 0 )
        {
          mvTable = 0;
          do
          {
            boxHashSize = vertexSubset.boxHashSize;
            v38 = (float *)((char *)mvTable + *(_DWORD *)(i + 268));
            mvHash = *(matchVert_s ***)(i + 268);
            v137 = v38;
            v39 = (char *)v38 - (char *)&vertexSubset.mins;
            v138 = v39;
            for ( m = 0; m < 12; *(int *)((char *)&surf.id + m) = (int)v42 )
            {
              v41 = (float *)((char *)&vertexSubset.mins.x + m);
              m += 4;
              v42 = (*(float *)((char *)v41 + v39) - *v41 - v41[10]) * v41[7];
              v43 = (int *)HIWORD(v145);
              BYTE1(v43) = HIBYTE(v145) | 0xC;
              tvRemap = v43;
            }
            v44 = 0;
            v45 = (int *)(vertexSubset.hash.hashMask & vertexSubset.hash.lookupMask);
            tvRemap = (int *)(vertexSubset.hash.hashMask & vertexSubset.hash.lookupMask);
            do
            {
              v46 = vertexSubset.hash.hash[((int)surf.mOriginalSurfaceName
                                          + boxHashSize
                                          * ((int)surf.geometry
                                           + boxHashSize * ((int)surf.shader + (v44 & 1))
                                           + ((v44 >> 1) & 1))
                                          + ((v44 >> 2) & 1)) & (unsigned int)v45];
              if ( v46 >= 0 )
              {
                do
                {
                  v47 = v137;
                  v48 = 0;
                  while ( 1 )
                  {
                    v124 = *(float *)((char *)v47 + (char *)&mvHash[3 * v46] - (char *)v137) - *v47;
                    HIBYTE(v124) &= ~0x80u;
                    if ( v124 > (double)vertexEpsilon )
                      break;
                    ++v48;
                    ++v47;
                    if ( v48 >= 3 )
                      goto LABEL_69;
                  }
                  v46 = vertexSubset.hash.indexChain[v46 & vertexSubset.hash.lookupMask];
                }
                while ( v46 >= 0 );
                v45 = tvRemap;
                boxHashSize = vertexSubset.boxHashSize;
              }
              ++v44;
            }
            while ( v44 < 8 );
            v49 = 0;
            for ( n = 0; n < 3; ++n )
            {
              v51 = (*(float *)((char *)&vertexSubset.mins.x + 4 * n + v138) - *(&vertexSubset.mins.x + n))
                  * vertexSubset.boxInvSize[n];
              tvRemap = (int *)(int)v51;
              v49 = v49 * boxHashSize + (int)v51;
            }
            v52 = expand;
            if ( vertexSubset.hash.hash == idHashIndex::INVALID_INDEX )
            {
              indexSize = vertexSubset.hash.indexSize;
              if ( SLODWORD(expand) >= vertexSubset.hash.indexSize )
                indexSize = LODWORD(expand) + 1;
              idHashIndex::Allocate(&vertexSubset.hash, vertexSubset.hash.hashSize, indexSize);
            }
            else if ( SLODWORD(expand) >= vertexSubset.hash.indexSize )
            {
              idHashIndex::ResizeIndex(&vertexSubset.hash, LODWORD(expand) + 1);
            }
            v54 = v49 & vertexSubset.hash.hashMask;
            vertexSubset.hash.indexChain[LODWORD(v52)] = vertexSubset.hash.hash[v49 & vertexSubset.hash.hashMask];
            *(float *)&vertexSubset.hash.hash[v54] = v52;
            v46 = LODWORD(v52);
LABEL_69:
            v55 = expand;
            mvTable = (matchVert_s *)((char *)mvTable + 12);
            *((_DWORD *)&im1->__vftable + LODWORD(expand)) = v46;
            v22 = ++LODWORD(v55) < *(_DWORD *)(i + 264);
            expand = v55;
          }
          while ( v22 );
        }
      }
      v56 = i;
      v57 = (int *)R_StaticAlloc(4 * *(_DWORD *)(i + 284));
      v18 = !v136->fastLoad;
      v58 = v57;
      tvRemap = v57;
      if ( v18 )
      {
        v116 = *(_DWORD *)(v56 + 284);
        v60 = *(_DWORD *)(v56 + 288);
        texCoordEpsilon = idRenderModelStatic::r_slopTexCoord.internalVar->floatValue;
        v61 = SIMDProcessor->__vftable;
        expand = texCoordEpsilon * 64.0;
        (*(void (__fastcall **)(idSIMDProcessor *, idVec2 *, idVec2 *, int, int))&v61->gap7C[20])(
          SIMDProcessor,
          &v132,
          &v133,
          v60,
          v116);
        v132.x = v132.x - expand;
        v132.y = v132.y - expand;
        v133.x = v133.x + expand;
        v133.y = v133.y + expand;
        idHashIndex::Free(&texCoordSubset.hash);
        texCoordSubset.hash.hashSize = 1024;
        v62 = (v133.x - v132.x) * 0.03125;
        texCoordSubset.hash.indexSize = 1024;
        texCoordSubset.mins = v132;
        texCoordSubset.maxs = v133;
        texCoordSubset.boxHashSize = 32;
        expand = 0.0;
        texCoordSubset.boxInvSize[0] = 1.0 / v62;
        texCoordSubset.boxHalfSize[0] = v62 * 0.5;
        v63 = (v133.y - v132.y) * 0.03125;
        texCoordSubset.boxInvSize[1] = 1.0 / v63;
        texCoordSubset.boxHalfSize[1] = v63 * 0.5;
        if ( *(int *)(v56 + 284) > 0 )
        {
          do
          {
            v137 = *(float **)(i + 288);
            v64 = &v137[2 * LODWORD(expand)];
            v65 = (char *)v64 - (char *)&texCoordSubset.mins;
            v138 = (char *)v64 - (char *)&texCoordSubset.mins;
            for ( ii = 0; ii < 2; v117[ii + 2] = (int)v68 )
            {
              v67 = (float *)((char *)&texCoordSubset.mins.x + ii * 4);
              ++ii;
              v68 = (*(float *)((char *)v67 + v65) - *v67 - v67[7]) * v67[5];
              v69 = (matchVert_s **)HIWORD(v145);
              BYTE1(v69) = HIBYTE(v145) | 0xC;
              mvHash = v69;
            }
            v70 = 0;
            v71 = texCoordSubset.hash.hashMask & texCoordSubset.hash.lookupMask;
            mvHash = 0;
            k = texCoordSubset.hash.hashMask & texCoordSubset.hash.lookupMask;
            do
            {
              v72 = texCoordSubset.hash.hash[(v117[4]
                                            + texCoordSubset.boxHashSize * (v117[3] + ((unsigned __int8)v70 & 1))
                                            + (((int)v70 >> 1) & 1)) & v71];
              if ( v72 >= 0 )
              {
                do
                {
                  v73 = 0;
                  v74 = v64;
                  while ( 1 )
                  {
                    v127 = *(float *)((char *)v74 + (char *)&v137[2 * v72] - (char *)v64) - *v74;
                    HIBYTE(v127) &= ~0x80u;
                    if ( v127 > (double)texCoordEpsilon )
                      break;
                    ++v73;
                    ++v74;
                    if ( v73 >= 2 )
                      goto LABEL_95;
                  }
                  v72 = texCoordSubset.hash.indexChain[v72 & texCoordSubset.hash.lookupMask];
                }
                while ( v72 >= 0 );
                v65 = v138;
                v71 = k;
                v70 = mvHash;
              }
              v70 = (matchVert_s **)((char *)v70 + 1);
              mvHash = v70;
            }
            while ( (int)v70 < 4 );
            v75 = 0;
            v76 = 0;
            do
            {
              v77 = *(float *)((char *)&texCoordSubset.mins.x + 4 * v76 + v65) - *(&texCoordSubset.mins.x + v76);
              ++v76;
              mvHash = (matchVert_s **)(int)(v77 * *((float *)&texCoordSubset.boxHashSize + v76));
              v75 = (unsigned int)mvHash + v75 * texCoordSubset.boxHashSize;
            }
            while ( v76 < 2 );
            v78 = expand;
            if ( texCoordSubset.hash.hash == idHashIndex::INVALID_INDEX )
            {
              v79 = texCoordSubset.hash.indexSize;
              if ( SLODWORD(expand) >= texCoordSubset.hash.indexSize )
                v79 = LODWORD(expand) + 1;
              idHashIndex::Allocate(&texCoordSubset.hash, texCoordSubset.hash.hashSize, v79);
            }
            else if ( SLODWORD(expand) >= texCoordSubset.hash.indexSize )
            {
              idHashIndex::ResizeIndex(&texCoordSubset.hash, LODWORD(expand) + 1);
            }
            v80 = v75 & texCoordSubset.hash.hashMask;
            texCoordSubset.hash.indexChain[LODWORD(v78)] = texCoordSubset.hash.hash[v75 & texCoordSubset.hash.hashMask];
            *(float *)&texCoordSubset.hash.hash[v80] = v78;
            v72 = LODWORD(v78);
LABEL_95:
            v81 = expand;
            v82 = i;
            tvRemap[LODWORD(expand)] = v72;
            v22 = ++LODWORD(v81) < *(_DWORD *)(v82 + 284);
            expand = v81;
          }
          while ( v22 );
        }
      }
      else
      {
        for ( jj = 0; jj < *(_DWORD *)(v56 + 284); ++jj )
          v58[jj] = jj;
      }
      v83 = (_DWORD *)i;
      v84 = (matchVert_s *)R_ClearedStaticAlloc(84 * *(_DWORD *)(i + 308));
      v114 = 4 * v83[66];
      mvTable = v84;
      mvHash = (matchVert_s **)R_ClearedStaticAlloc(v114);
      v85 = R_AllocStaticTriSurf();
      v85->numVerts = 0;
      v85->numIndexes = 0;
      R_AllocStaticTriSurfIndexes(v85, 3 * v83[77]);
      normal.z = 0.0;
      v85->generateNormals = !normalsParsed;
      v22 = v83[77] <= 0;
      floatValue = idRenderModelStatic::r_slopNormal.internalVar->floatValue;
      normal.y = 0.0;
      normal.x = 0.0;
      color = identityColor_0;
      tv = 0;
      expand = 0.0;
      normalEpsilon = 1.0 - floatValue;
      if ( !v22 )
      {
        v137 = 0;
        v138 = 36;
        do
        {
          k = 0;
          v145 = v138;
          do
          {
            v87 = *(_DWORD *)(v145 + v83[78] - 24);
            if ( v87 < 0 || v87 >= v83[66] )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
                common.type,
                "ConvertMAToModelSurfaces: bad vertex index in MA file %s",
                v136->name.data);
            v88 = v83[71];
            v = *((_DWORD *)&im1->__vftable + v87);
            if ( v88 )
            {
              v89 = *(_DWORD *)(v145 + v83[78] - 12);
              if ( v89 < 0 || v89 >= v88 )
                (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 152))(
                  common.type,
                  "ConvertMAToModelSurfaces: bad tex coord index in MA file %s",
                  v136->name.data);
              tv = tvRemap[v89];
            }
            if ( normalsParsed )
            {
              v90 = v83[78] + 12 * ((_DWORD)v137 + k + 4);
              v91 = *(float *)v90;
              v92 = *(float *)(v90 + 4);
              v93 = *(float *)(v90 + 8);
              normal.x = v91;
              normal.y = v92;
              normal.z = v93;
            }
            v94 = *(_DWORD *)(v145 + v83[78]);
            if ( v94 != -1 && v94 != -999 )
              color = (unsigned __int8 *)(v83[76] + 4 * v94);
            v95 = mvHash[v];
            v96 = color;
            v97 = 0;
            if ( v95 )
            {
              while ( v95->tv != tv
                   || *(_DWORD *)v95->color != *(_DWORD *)color
                   || normalsParsed
                   && normal.y * v95->normal.y + normal.z * v95->normal.z + normal.x * v95->normal.x <= normalEpsilon )
              {
                v97 = v95;
                v95 = v95->next;
                if ( !v95 )
                  goto LABEL_118;
              }
            }
            else
            {
LABEL_118:
              v95 = &mvTable[v85->numVerts];
              v95->v = v;
              v95->tv = tv;
              v95->normal = normal;
              *(_DWORD *)v95->color = *(_DWORD *)v96;
              v95->next = 0;
              if ( v97 )
                v97->next = v95;
              else
                mvHash[v] = v95;
              ++v85->numVerts;
            }
            v145 += 4;
            v85->indexes[v85->numIndexes] = v95 - mvTable;
            v98 = k;
            ++v85->numIndexes;
            k = v98 + 1;
          }
          while ( v98 + 1 < 3 );
          v138 += 84;
          v137 = (float *)((char *)v137 + 7);
          v22 = ++LODWORD(expand) < v83[77];
        }
        while ( v22 );
      }
      if ( v85->numIndexes > 3 * v83[77] )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "ConvertMAToModelSurfaces: index miscount in MA file %s",
          v136->name.data);
      if ( v85->numVerts > 3 * v83[77] )
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 156))(
          common.type,
          "ConvertMAToModelSurfaces: vertex miscount in MA file %s",
          v136->name.data);
      R_AllocStaticTriSurfVerts(v85, v85->numVerts);
      v22 = v85->numVerts <= 0;
      expand = 0.0;
      if ( !v22 )
      {
        v99 = 0;
        p_z = &mvTable->normal.z;
        do
        {
          v101 = &v85->verts[v99];
          v101->xyz.z = 0.0;
          v101->xyz.y = 0.0;
          v101->xyz.x = 0.0;
          v101->st.y = 0.0;
          v101->st.x = 0.0;
          v101->normal.z = 0.0;
          v101->normal.y = 0.0;
          v101->normal.x = 0.0;
          v101->tangents[0].z = 0.0;
          v101->tangents[0].y = 0.0;
          v101->tangents[0].x = 0.0;
          v101->tangents[1].z = 0.0;
          v101->tangents[1].y = 0.0;
          v101->tangents[1].x = 0.0;
          v101->color[3] = 0;
          v101->color[2] = 0;
          v101->color[1] = 0;
          v101->color[0] = 0;
          v102 = v83[67];
          v103 = *(float *)(v102 + 12 * *((_DWORD *)p_z - 5));
          v104 = v102 + 12 * *((_DWORD *)p_z - 5);
          verts = v85->verts;
          verts[v99].xyz.x = v103;
          verts[v99].xyz.y = *(float *)(v104 + 4);
          v83 = (_DWORD *)i;
          verts[v99].xyz.z = *(float *)(v104 + 8);
          p_x = (_DWORD *)&v85->verts[v99].normal.x;
          *p_x = *((_DWORD *)p_z - 2);
          p_x[1] = *((_DWORD *)p_z - 1);
          p_x[2] = *(_DWORD *)p_z;
          *(float *)v85->verts[v99].color = *(p_z - 3);
          if ( v83[71] )
          {
            v107 = *((_DWORD *)p_z - 4);
            v108 = v83[72];
            v109 = *(float *)(v108 + 8 * v107);
            v110 = *(float *)(v108 + 8 * v107 + 4);
            v85->verts[v99].st.x = 0.0 * v110 + v109;
            v85->verts[v99].st.y = v110 - v109 * 0.0;
          }
          p_z += 7;
          ++v99;
          v22 = ++LODWORD(expand) < v85->numVerts;
        }
        while ( v22 );
      }
      R_StaticFree(mvTable);
      R_StaticFree(mvHash);
      R_StaticFree(tvRemap);
      R_StaticFree((void *)im1);
      v111 = (int)&v136->surfaces.list[mergeTo[objectNum]];
      v112 = *(srfTriangles_s **)(v111 + 8);
      if ( v112 )
      {
        *(_DWORD *)(v111 + 8) = R_MergeTriangles(v112, v85);
        R_FreeStaticTriSurf(v85);
        R_FreeStaticTriSurf(v112);
      }
      else
      {
        *(_DWORD *)(v111 + 8) = v85;
      }
      v22 = ++objectNum < ma->objects.num;
    }
    while ( v22 );
  }
  LOBYTE(v148) = 1;
  idHashIndex::Free(&texCoordSubset.hash);
  v148 = -1;
  idHashIndex::Free(&vertexSubset.hash);
  return 1;
}

// FUNC: public: bool __thiscall idRenderModelStatic::LoadLWO(char const *)
char __thiscall idRenderModelStatic::LoadLWO(idRenderModelStatic *this, const char *fileName)
{
  const st_lwObject *Object; // eax
  st_lwObject *v4; // esi
  int failPos; // [esp+8h] [ebp-8h] BYREF
  unsigned int failID; // [esp+Ch] [ebp-4h] BYREF

  Object = lwGetObject(fileName, &failID, &failPos, (unsigned int *)&fileName);
  v4 = (st_lwObject *)Object;
  if ( !Object )
    return 0;
  idRenderModelStatic::ConvertLWOToModelSurfaces(this, Object);
  lwFreeObject(v4);
  return 1;
}

// FUNC: public: bool __thiscall idRenderModelStatic::LoadMA(char const *)
char __thiscall idRenderModelStatic::LoadMA(idRenderModelStatic *this, const char *fileName)
{
  const maModel_s *v3; // eax
  maModel_s *v4; // esi

  v3 = MA_Load(fileName);
  v4 = (maModel_s *)v3;
  if ( !v3 )
    return 0;
  idRenderModelStatic::ConvertMAToModelSurfaces(this, v3);
  MA_Free(v4);
  return 1;
}

// FUNC: public: bool __thiscall idRenderModelStatic::LoadFLT(char const *)
char __thiscall idRenderModelStatic::LoadFLT(idRenderModelStatic *this, const char *fileName)
{
  int v2; // edi
  int v4; // esi
  int v5; // ebp
  float *v6; // ecx
  double v7; // st7
  unsigned __int8 *v8; // eax
  int v9; // edi
  _BYTE *v10; // esi
  double v11; // st7
  unsigned __int64 v12; // rax
  const char *v13; // eax
  int v14; // edi
  int v15; // eax
  idMaterial *shader; // edx
  const char *v17; // ecx
  char v18; // al
  int v19; // esi
  int v20; // eax
  char v21; // cl
  char *v22; // edx
  int v23; // edi
  unsigned __int8 *v24; // esi
  float *v25; // ebp
  int v26; // ecx
  float *v27; // edx
  int v28; // eax
  float *v29; // esi
  int v30; // edx
  float *v31; // ecx
  float *v32; // ebp
  int v33; // edx
  float *v34; // ecx
  int v35; // ecx
  int v36; // esi
  unsigned __int8 *v37; // ebp
  int v38; // edx
  int v39; // ebp
  srfTriangles_s *v40; // esi
  int v41; // edx
  idRenderModelStatic *v42; // ecx
  int v43; // edx
  int v44; // ecx
  int v45; // eax
  double v46; // st7
  double v47; // st6
  int v48; // ecx
  int v49; // edx
  double v50; // st5
  double v51; // st5
  char *v52; // eax
  double v53; // st4
  int v54; // ecx
  unsigned __int8 *v55; // edx
  int v56; // eax
  int v57; // eax
  int v58; // ecx
  int *indexes; // edi
  int v60; // edx
  bool v61; // zf
  int v62; // [esp-8h] [ebp-70h]
  float minY; // [esp+10h] [ebp-58h]
  int minYa; // [esp+10h] [ebp-58h]
  int minYc; // [esp+10h] [ebp-58h]
  int minYb; // [esp+10h] [ebp-58h]
  float *data; // [esp+14h] [ebp-54h] BYREF
  int j; // [esp+18h] [ebp-50h]
  int height; // [esp+1Ch] [ebp-4Ch]
  int v70; // [esp+20h] [ebp-48h]
  int v71; // [esp+24h] [ebp-44h]
  unsigned __int8 *image; // [esp+28h] [ebp-40h]
  int size; // [esp+2Ch] [ebp-3Ch]
  idRenderModelStatic *v74; // [esp+30h] [ebp-38h]
  int v75; // [esp+34h] [ebp-34h]
  int v76; // [esp+38h] [ebp-30h]
  modelSurface_s surface; // [esp+3Ch] [ebp-2Ch] BYREF
  int v78; // [esp+64h] [ebp-4h]
  const char *fileNamea; // [esp+6Ch] [ebp+4h]
  const char *fileNameb; // [esp+6Ch] [ebp+4h]
  const char *fileNamec; // [esp+6Ch] [ebp+4h]

  v74 = this;
  v2 = fileSystem->ReadFile(fileSystem, fileName, (void **)&data, 0);
  size = v2;
  if ( v2 <= 0 )
    return 0;
  v4 = 0;
  *(float *)&j = -9999999.0;
  v5 = v2 / 4;
  size = (int)sqrt((double)size * 0.25);
  minY = 9999999.0;
  if ( v2 / 4 > 0 )
  {
    v6 = data;
    do
    {
      v7 = BigFloat(v6[v4]);
      data[v4] = v7;
      v6 = data;
      if ( LODWORD(data[v4]) == -971228160 )
      {
        data[v4] = 0.0;
        v6 = data;
      }
      if ( v6[v4] < (double)minY )
        minY = v6[v4];
      if ( v6[v4] > (double)*(float *)&j )
        j = SLODWORD(v6[v4]);
      ++v4;
    }
    while ( v4 < v5 );
  }
  v8 = (unsigned __int8 *)R_StaticAlloc(v2);
  v9 = 0;
  image = v8;
  if ( v5 > 0 )
  {
    v10 = v8 + 1;
    v11 = *(float *)&j - minY;
    do
    {
      v12 = (unsigned __int64)((data[v9] - minY) / v11 * 255.0);
      v10[1] = v12;
      *v10 = v12;
      *(v10 - 1) = v12;
      v10[2] = -1;
      ++v9;
      v10 += 4;
    }
    while ( v9 < v5 );
  }
  surface.id = 0;
  surface.geometry = (srfTriangles_s *)20;
  surface.shader = (const idMaterial *)&surface.mOriginalSurfaceName;
  LOBYTE(surface.mOriginalSurfaceName) = 0;
  if ( fileName )
  {
    v13 = &fileName[strlen(fileName) + 1];
    v14 = v13 - (fileName + 1);
    v15 = v13 - fileName;
    if ( v15 > 20 )
      idStr::ReAllocate((idStr *)&surface, v15, 1);
    shader = (idMaterial *)surface.shader;
    v17 = fileName;
    do
    {
      v18 = *v17;
      LOBYTE(shader->__vftable) = *v17++;
      shader = (idMaterial *)((char *)shader + 1);
    }
    while ( v18 );
    surface.id = v14;
  }
  v78 = 0;
  idStr::StripFileExtension((idStr *)&surface);
  v19 = surface.id + 4;
  if ( surface.id + 5 > (int)surface.geometry )
    idStr::ReAllocate((idStr *)&surface, surface.id + 5, 1);
  v20 = 0;
  v21 = 46;
  do
  {
    v22 = (char *)surface.shader + v20++;
    v22[surface.id] = v21;
    v21 = aTga[v20];
  }
  while ( v21 );
  v23 = size;
  surface.id = v19;
  v62 = size;
  *((_BYTE *)&surface.shader->__vftable + v19) = 0;
  v24 = image;
  R_WriteTGA((const char *)surface.shader, image, v23, v62, 0);
  R_StaticFree(v24);
  *(float *)&j = 0.0;
  if ( v23 > 0 )
  {
    v25 = data;
    do
    {
      v26 = 0;
      v27 = v25;
      do
      {
        if ( *v27 > 1.0 )
          break;
        ++v26;
        v27 += v23;
      }
      while ( v26 < v23 );
      if ( v26 != v23 )
        break;
      ++v25;
      ++j;
    }
    while ( j < v23 );
  }
  v28 = v23 - 1;
  fileNamea = (const char *)(v23 - 1);
  if ( v23 - 1 > 0 )
  {
    v29 = &data[v28];
    do
    {
      v30 = 0;
      if ( v23 > 0 )
      {
        v31 = v29;
        do
        {
          if ( *v31 > 1.0 )
            break;
          ++v30;
          v31 += v23;
        }
        while ( v30 < v23 );
        v28 = (int)fileNamea;
      }
      if ( v30 != v23 )
        break;
      --v28;
      --v29;
      fileNamea = (const char *)v28;
    }
    while ( v28 > 0 );
  }
  minYa = 0;
  if ( v23 > 0 )
  {
    v32 = data;
    do
    {
      v33 = 0;
      v34 = v32;
      do
      {
        if ( *v34 > 1.0 )
          break;
        ++v33;
        ++v34;
      }
      while ( v33 < v23 );
      if ( v33 != v23 )
        break;
      v32 += v23;
      ++minYa;
    }
    while ( minYa < v23 );
    v28 = (int)fileNamea;
  }
  v35 = v23 - 1;
  if ( v23 - 1 < v23 )
  {
    v36 = -4 * v23;
    v37 = (unsigned __int8 *)&data[v23 * v35];
    image = v37;
    do
    {
      v38 = 0;
      if ( v23 > 0 )
      {
        do
        {
          if ( *(float *)v37 > 1.0 )
            break;
          ++v38;
          v37 += 4;
        }
        while ( v38 < v23 );
        v28 = (int)fileNamea;
      }
      if ( v38 != v23 )
        break;
      --v35;
      v37 = &image[v36];
      image += v36;
    }
    while ( v35 < v23 );
  }
  v39 = v28 - j + 1;
  height = v35 - minYa + 1;
  v40 = R_AllocStaticTriSurf();
  v41 = 3 * height;
  v40->numVerts = v39 * height;
  image = (unsigned __int8 *)(v39 - 1);
  v42 = v74;
  v40->numIndexes = (v39 - 1) * (2 * v41 - 6);
  v42->fastLoad = 1;
  R_AllocStaticTriSurfIndexes(v40, v40->numIndexes);
  R_AllocStaticTriSurfVerts(v40, v40->numVerts);
  v43 = height;
  fileNameb = 0;
  if ( height > 0 )
  {
    v76 = 4 * v23;
    v44 = v39 << 6;
    v45 = 4 * (j + v23 * minYa);
    v70 = 0;
    v71 = 0;
    v75 = v39 << 6;
    size = v45;
    do
    {
      *(float *)&j = 0.0;
      if ( v39 > 0 )
      {
        v46 = (double)v70;
        v47 = (double)(int)image;
        minYc = v43 - 1;
        v48 = v71;
        v49 = v45;
        v50 = (double)(int)fileNameb / (double)minYc;
        minYb = 0;
        v51 = 1.0 - v50;
        do
        {
          v52 = (char *)v40->verts + v48;
          *((_DWORD *)v52 + 2) = 0;
          *((_DWORD *)v52 + 1) = 0;
          *(_DWORD *)v52 = 0;
          *((_DWORD *)v52 + 15) = 0;
          *((_DWORD *)v52 + 14) = 0;
          *((_DWORD *)v52 + 6) = 0;
          *((_DWORD *)v52 + 5) = 0;
          *((_DWORD *)v52 + 4) = 0;
          *((_DWORD *)v52 + 10) = 0;
          *((_DWORD *)v52 + 9) = 0;
          *((_DWORD *)v52 + 8) = 0;
          *((_DWORD *)v52 + 13) = 0;
          *((_DWORD *)v52 + 12) = 0;
          *((_DWORD *)v52 + 11) = 0;
          v52[15] = 0;
          v52[14] = 0;
          v52[13] = 0;
          v52[12] = 0;
          *(float *)((char *)&v40->verts->xyz.x + v48) = (float)minYb;
          minYb += 10;
          *(float *)((char *)&v40->verts->xyz.y + v48) = v46;
          v53 = (double)j;
          *(float *)((char *)&v40->verts->xyz.z + v48) = *(float *)((char *)data + v49);
          v49 += 4;
          v48 += 64;
          *(float *)((char *)v40->verts + v48 - 8) = v53 / v47;
          *(float *)((char *)v40->verts + v48 - 4) = v51;
          ++j;
        }
        while ( j < v39 );
        v43 = height;
        v44 = v75;
      }
      v45 = v76 + size;
      ++fileNameb;
      v70 -= 10;
      v71 += v44;
      size += v76;
    }
    while ( (int)fileNameb < v43 );
  }
  v54 = v43 - 1;
  if ( v43 - 1 > 0 )
  {
    v55 = image;
    v56 = 24 * (_DWORD)image;
    fileNamec = 0;
    v75 = 24 * (_DWORD)image;
    v70 = 12;
    v71 = v39 + 1;
    j = v54;
    do
    {
      if ( (int)v55 > 0 )
      {
        v57 = v70;
        size = v71;
        v58 = (int)fileNamec;
        height = (int)v55;
        do
        {
          *(int *)((char *)v40->indexes + v57 - 12) = v58;
          *(int *)((char *)v40->indexes + v57 - 8) = v58 + 1;
          indexes = v40->indexes;
          v76 = v58 + 1;
          v60 = size;
          *(int *)((char *)indexes + v57 - 4) = size;
          *(int *)((char *)v40->indexes + v57) = v58;
          *(int *)((char *)v40->indexes + v57 + 4) = v60;
          *(int *)((char *)v40->indexes + v57 + 8) = v39 + v58;
          v58 = v76;
          v57 += 24;
          v61 = height-- == 1;
          size = v60 + 1;
        }
        while ( !v61 );
        v56 = v75;
        v55 = image;
      }
      fileNamec += v39;
      v71 += v39;
      v70 += v56;
      --j;
    }
    while ( *(float *)&j != 0.0 );
  }
  fileSystem->FreeFile(fileSystem, data);
  ((void (__thiscall *)(idRenderModelStatic *, _DWORD, const idMaterial *, srfTriangles_s *, idStr *))v74->AddSurface)(
    v74,
    0,
    tr.defaultMaterial,
    v40,
    surface.mOriginalSurfaceName);
  v78 = -1;
  idStr::FreeData((idStr *)&surface);
  return 1;
}

// FUNC: public: virtual void __thiscall idRenderModelStatic::InitFromFile(char const *)
void __thiscall idRenderModelStatic::InitFromFile(idRenderModelStatic *this, const char *fileName)
{
  idRenderModelStatic_vtbl *v3; // edx
  const aseModel_s *v4; // eax
  aseModel_s *v5; // edi
  bool MA; // al
  bool v7; // zf
  idRenderModelStatic_vtbl *v8; // eax
  char *data; // [esp-4h] [ebp-38h]
  idStr extension; // [esp+8h] [ebp-2Ch] BYREF
  int v11; // [esp+30h] [ebp-4h]

  extension.len = 0;
  extension.alloced = 20;
  extension.data = extension.baseBuffer;
  extension.baseBuffer[0] = 0;
  v3 = this->__vftable;
  v11 = 0;
  v3->InitEmpty(this, fileName);
  idStr::ExtractFileExtension(&this->name, &extension);
  if ( idStr::Icmp(extension.data, "ase") )
  {
    if ( idStr::Icmp(extension.data, "lwo") )
    {
      if ( idStr::Icmp(extension.data, "flt") )
      {
        v7 = idStr::Icmp(extension.data, "ma") == 0;
        data = this->name.data;
        if ( !v7 )
        {
          (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
            common.type,
            "idRenderModelStatic::InitFromFile: unknown type for model: '%s'",
            data);
          goto LABEL_6;
        }
        MA = idRenderModelStatic::LoadMA(this, data);
      }
      else
      {
        MA = idRenderModelStatic::LoadFLT(this, this->name.data);
      }
    }
    else
    {
      MA = idRenderModelStatic::LoadLWO(this, this->name.data);
    }
  }
  else
  {
    v4 = ASE_Load(this->name.data);
    v5 = (aseModel_s *)v4;
    if ( v4 )
    {
      idRenderModelStatic::ConvertASEToModelSurfaces(this, v4);
      ASE_Free(v5);
      MA = 1;
    }
    else
    {
      MA = 0;
    }
  }
  this->reloadable = 1;
  if ( MA )
  {
    v8 = this->__vftable;
    this->purged = 0;
    v8->FinishSurfaces(this);
    goto LABEL_15;
  }
LABEL_6:
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
    common.type,
    "Couldn't load model: '%s'",
    this->name.data);
  idRenderModelStatic::MakeDefaultModel(this);
LABEL_15:
  v11 = -1;
  idStr::FreeData(&extension);
}
