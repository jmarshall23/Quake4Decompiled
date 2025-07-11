
// FUNC: public: virtual struct srfTriangles_s * __thiscall idRenderModelManagerLocal::AllocStaticTriSurf(int,int)
srfTriangles_s *__thiscall idRenderModelManagerLocal::AllocStaticTriSurf(
        idRenderModelStatic *this,
        int numVerts,
        int numIndexes)
{
  srfTriangles_s *v3; // esi

  v3 = R_AllocStaticTriSurf();
  R_AllocStaticTriSurfVerts(v3, numVerts);
  R_AllocStaticTriSurfIndexes(v3, numIndexes);
  return v3;
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::FreeStaticTriSurf(struct srfTriangles_s *)
void __thiscall idRenderModelManagerLocal::FreeStaticTriSurf(idRenderModelManagerLocal *this, srfTriangles_s *tris)
{
  R_ReallyFreeStaticTriSurf(tris);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::FreeModel(class idRenderModel *)
void __thiscall idRenderModelManagerLocal::FreeModel(idRenderModelManagerLocal *this, idRenderModel *model)
{
  int v3; // edi
  const char *v4; // eax

  if ( model )
  {
    if ( __RTDynamicCast(
           model,
           0,
           &idRenderModel `RTTI Type Descriptor',
           &idRenderModelStatic `RTTI Type Descriptor',
           0) )
    {
      if ( model == this->defaultModel )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "idRenderModelManager::FreeModel: can't free the default model");
      }
      else if ( model == this->beamModel )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "idRenderModelManager::FreeModel: can't free the beam model");
      }
      else if ( model == this->spriteModel )
      {
        (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
          common.type,
          "idRenderModelManager::FreeModel: can't free the sprite model");
      }
      else
      {
        R_CheckForEntityDefsUsingModel(model);
        ((void (__thiscall *)(idRenderModel *, int))model->~idRenderModel)(model, 1);
      }
    }
    else
    {
      v3 = *(_DWORD *)common.type;
      v4 = model->Name(model);
      (*(void (**)(netadrtype_t, const char *, ...))(v3 + 152))(
        common.type,
        "idRenderModelManager::FreeModel: model '%s' is not a static model",
        v4);
    }
  }
}

// FUNC: private: static void __cdecl idRenderModelManagerLocal::PrintModel_f(class idCmdArgs const &)
void __cdecl idRenderModelManagerLocal::PrintModel_f(const idCmdArgs *args)
{
  idRenderModel *v1; // eax
  const char *v2; // esi

  if ( args->argc == 2 )
  {
    v1 = renderModelManager->CheckModel(renderModelManager, args->argv[1]);
    if ( v1 )
    {
      v1->Print(v1);
    }
    else
    {
      if ( args->argc <= 1 )
        v2 = &entityFilter;
      else
        v2 = args->argv[1];
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "model \"%s\" not found\n",
        v2);
    }
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: printModel <modelName>\n");
  }
}

// FUNC: private: static void __cdecl idRenderModelManagerLocal::ListModels_f(class idCmdArgs const &)
void __cdecl idRenderModelManagerLocal::ListModels_f()
{
  int v0; // ebp
  int v1; // edi
  int v2; // ebx
  idRenderModel *v3; // esi
  int totalMem; // [esp+14h] [ebp-4h]

  v0 = 0;
  totalMem = 0;
  v1 = 0;
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    " mem   srf verts tris\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    " ---   --- ----- ----\n");
  v2 = 0;
  if ( localModelManager.models.num > 0 )
  {
    do
    {
      v3 = localModelManager.models.list[v2];
      if ( v3->IsLoaded(v3) )
      {
        v3->List(v3);
        v0 += v3->Memory(v3);
        ++v1;
      }
      ++v2;
    }
    while ( v2 < localModelManager.models.num );
    totalMem = v0;
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    " ---   --- ----- ----\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    " mem   srf verts tris\n");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%i loaded models\n", v1);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "total memory: %4.1fM\n",
    (double)totalMem * 0.00000095367432);
}

// FUNC: private: static void __cdecl idRenderModelManagerLocal::TouchModel_f(class idCmdArgs const &)
void __cdecl idRenderModelManagerLocal::TouchModel_f(const idCmdArgs *args)
{
  const char *v1; // esi

  if ( args->argc > 1 && (v1 = args->argv[1], *v1) )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "touchModel %s\n", v1);
    session->UpdateScreen(session, 1);
    if ( !renderModelManager->CheckModel(renderModelManager, v1) )
      (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "...not found\n");
  }
  else
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "usage: touchModel <modelName>\n");
  }
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::WritePrecacheCommands(class idFile *)
void __thiscall idRenderModelManagerLocal::WritePrecacheCommands(idRenderModelManagerLocal *this, idFile *f)
{
  int i; // edi
  idRenderModel **list; // eax
  idRenderModel *v5; // esi
  const char *v6; // eax
  char str[1024]; // [esp+8h] [ebp-400h] BYREF

  for ( i = 0; i < this->models.num; ++i )
  {
    list = this->models.list;
    v5 = list[i];
    if ( v5 )
    {
      if ( v5->IsReloadable(list[i]) )
      {
        v6 = v5->Name(v5);
        sprintf(str, "touchModel %s\n", v6);
        (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s", str);
        f->Printf(f, "%s", str);
      }
    }
  }
}

// FUNC: public: virtual class idRenderModel * __thiscall idRenderModelManagerLocal::AllocModel(void)
idRenderModelStatic *__thiscall idRenderModelManagerLocal::AllocModel(idRenderModelManagerLocal *this)
{
  return NewRenderModel<idRenderModelStatic>(RV_HEAP_ID_LEVEL);
}

// FUNC: public: virtual bool __thiscall idRenderModelManagerLocal::CheckModel(class idRenderModel *)
char __thiscall idRenderModelManagerLocal::CheckModel(idRenderModelManagerLocal *this, idRenderModel *model)
{
  int num; // edx
  int v4; // eax
  idRenderModel **i; // ecx

  if ( this->mShuttingDown )
    return 0;
  num = this->models.num;
  v4 = 0;
  if ( num <= 0 )
    return 0;
  for ( i = this->models.list; *i != model; ++i )
  {
    if ( ++v4 >= num )
      return 0;
  }
  return 1;
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::ReloadModels(bool)
void __thiscall idRenderModelManagerLocal::ReloadModels(idRenderModelManagerLocal *this, bool forceAll)
{
  int i; // edi
  idRenderModel *v4; // esi
  idFileSystem_vtbl *v5; // ebx
  int v6; // eax
  unsigned int v7; // eax
  int v8; // ebx
  int v9; // eax
  unsigned int current; // [esp+Ch] [ebp-4h] BYREF

  if ( forceAll )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Reloading all model files...\n");
  else
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "Checking for changed model files...\n");
  R_FreeDerivedData();
  for ( i = 1; i < this->models.num; ++i )
  {
    v4 = this->models.list[i];
    if ( v4->IsReloadable(v4) )
    {
      if ( forceAll
        || (v5 = fileSystem->__vftable,
            v6 = ((int (__thiscall *)(idRenderModel *, _DWORD, unsigned int *))v4->Name)(v4, 0, &current),
            ((void (__thiscall *)(idFileSystem *, int))v5->ReadFile)(fileSystem, v6),
            v7 = v4->Timestamp(v4),
            current > v7) )
      {
        v8 = *(_DWORD *)common.type;
        v9 = (int)v4->Name(v4);
        (*(void (**)(netadrtype_t, const char *, ...))(v8 + 132))(common.type, "reloading %s.\n", v9);
        v4->LoadModel(v4);
      }
    }
  }
  R_ReCreateWorldReferences();
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::FreeModelVertexCaches(void)
void __thiscall idRenderModelManagerLocal::FreeModelVertexCaches(idRenderModelManagerLocal *this)
{
  int i; // esi
  idRenderModel *v3; // ecx

  for ( i = 0; i < this->models.num; ++i )
  {
    v3 = this->models.list[i];
    v3->FreeVertexCache(v3);
  }
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::BeginLevelLoad(void)
void __thiscall idRenderModelManagerLocal::BeginLevelLoad(idRenderModelManagerLocal *this)
{
  int v2; // edi
  bool v3; // cc
  idRenderModel **list; // eax
  idRenderModel *v5; // esi

  v2 = 0;
  v3 = this->models.num <= 0;
  this->insideLevelLoad = 1;
  if ( !v3 )
  {
    do
    {
      list = this->models.list;
      v5 = list[v2];
      if ( com_purgeAll.internalVar->integerValue && v5->IsReloadable(list[v2]) )
      {
        R_CheckForEntityDefsUsingModel(v5);
        v5->PurgeModel(v5);
      }
      v5->SetLevelLoadReferenced(v5, 0);
      ++v2;
    }
    while ( v2 < this->models.num );
  }
  R_PurgeTriSurfData(frameData[tr.smpFrame]);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::EndLevelLoad(void)
void __thiscall idRenderModelManagerLocal::EndLevelLoad(idRenderModelManagerLocal *this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // ebp
  bool v5; // cc
  idRenderModel *v6; // esi
  int i; // ebp
  idRenderModel *v8; // esi
  int v9; // esi
  int purgeCount; // [esp+18h] [ebp-Ch]
  int keepCount; // [esp+1Ch] [ebp-8h]
  int start; // [esp+20h] [ebp-4h]

  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "-- idRenderModelManagerLocal::EndLevelLoad --\n");
  v2 = Sys_Milliseconds();
  v3 = 0;
  v4 = 0;
  v5 = this->models.num <= 0;
  start = v2;
  this->insideLevelLoad = 0;
  purgeCount = 0;
  keepCount = 0;
  if ( !v5 )
  {
    do
    {
      v6 = this->models.list[v4];
      if ( !v6->IsLevelLoadReferenced(v6) && v6->IsLoaded(v6) && v6->IsReloadable(v6) )
      {
        ++purgeCount;
        R_CheckForEntityDefsUsingModel(v6);
        v6->PurgeModel(v6);
      }
      else
      {
        ++keepCount;
      }
      ++v4;
    }
    while ( v4 < this->models.num );
  }
  R_PurgeTriSurfData(frameData[tr.smpFrame]);
  for ( i = 0; i < this->models.num; ++i )
  {
    v8 = this->models.list[i];
    if ( v8->IsLevelLoadReferenced(v8) && !v8->IsLoaded(v8) && v8->IsReloadable(v8) )
    {
      ++v3;
      v8->LoadModel(v8);
      if ( (v3 & 0xF) == 0 )
        session->PacifierUpdate(session);
    }
  }
  v9 = Sys_Milliseconds();
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%5i models purged from previous level, ",
    purgeCount);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%5i models kept.\n",
    keepCount);
  if ( v3 )
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "%5i new models loaded in %5.1f seconds\n",
      v3,
      (double)(v9 - start) * 0.001);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "---------------------------------------------\n");
}

// FUNC: public: virtual unsigned int __thiscall idRenderModelManagerLocal::ListModelSummary(void)
int __thiscall idRenderModelManagerLocal::ListModelSummary(idRenderModelManagerLocal *this)
{
  int v1; // edi
  int i; // ebx
  idRenderModel *v3; // esi

  v1 = 0;
  for ( i = 0; v1 < localModelManager.models.num; ++v1 )
  {
    v3 = localModelManager.models.list[v1];
    if ( v3->IsLoaded(v3) )
      i += v3->Memory(v3);
  }
  return i;
}

// FUNC: public: virtual __thiscall idRenderModelManagerLocal::~idRenderModelManagerLocal(void)
void __thiscall idRenderModelManagerLocal::~idRenderModelManagerLocal(idRenderModelManagerLocal *this)
{
  idRenderModel **list; // eax

  this->__vftable = (idRenderModelManagerLocal_vtbl *)&idRenderModelManagerLocal::`vftable';
  idHashIndex::Free(&this->hash);
  list = this->models.list;
  if ( list )
    Memory::Free(list);
  this->models.list = 0;
  this->models.num = 0;
  this->models.size = 0;
  this->__vftable = (idRenderModelManagerLocal_vtbl *)&idRenderModelManager::`vftable';
}

// FUNC: public: virtual struct srfTriangles_s * __thiscall idRenderModelManagerLocal::CopyStaticTriSurf(struct srfTriangles_s const *)
srfTriangles_s *__thiscall idRenderModelManagerLocal::CopyStaticTriSurf(
        idRenderModelManagerLocal *this,
        const srfTriangles_s *tri)
{
  return R_CopyStaticTriSurf(tri);
}

// FUNC: public: virtual struct srfTriangles_s * __thiscall idRenderModelManagerLocal::PolytopeSurface(int,class idPlane const *,class idWinding * *)
srfTriangles_s *__thiscall idRenderModelManagerLocal::PolytopeSurface(
        idRenderModelManagerLocal *this,
        int numPlanes,
        const idPlane *planes,
        idWinding **windings)
{
  return R_PolytopeSurface(numPlanes, planes, windings);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::CreateSilIndexes(struct srfTriangles_s *)
void __thiscall idRenderModelManagerLocal::CreateSilIndexes(idRenderModelManagerLocal *this, srfTriangles_s *tris)
{
  R_CreateSilIndexes(tris);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::DeriveFacePlanes(struct srfTriangles_s *)
void __thiscall idRenderModelManagerLocal::DeriveFacePlanes(idRenderModelManagerLocal *this, srfTriangles_s *tris)
{
  R_DeriveFacePlanes(tris);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::BoundTriSurf(struct srfTriangles_s *)
void __thiscall idRenderModelManagerLocal::BoundTriSurf(idRenderModelManagerLocal *this, srfTriangles_s *tris)
{
  R_BoundTriSurf(tris);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::CleanupTriangles(struct srfTriangles_s *,bool,bool,bool,bool)
void __thiscall idRenderModelManagerLocal::CleanupTriangles(
        idRenderModelManagerLocal *this,
        srfTriangles_s *tris,
        bool createNormals,
        bool identifySilEdges,
        bool useUnsmoothedTangents,
        bool needSilMultiply)
{
  R_CleanupTriangles(tris, createNormals, identifySilEdges, useUnsmoothedTangents, needSilMultiply);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::SimpleCleanupTriangles(struct srfTriangles_s *)
void __thiscall idRenderModelManagerLocal::SimpleCleanupTriangles(
        idRenderModelManagerLocal *this,
        srfTriangles_s *tris)
{
  R_SimpleCleanupTriangles(tris);
}

// FUNC: public: virtual class idRenderLight * __thiscall idRenderModelManagerLocal::CreateLightDef(void)
void __thiscall idRenderModelManagerLocal::CreateLightDef(idRenderModelManagerLocal *this)
{
  idRenderLightLocal *v1; // eax

  v1 = (idRenderLightLocal *)Memory::Allocate(0x494u);
  if ( v1 )
    idRenderLightLocal::idRenderLightLocal(v1);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::FreeLightDef(class idRenderLight *)
void __thiscall idRenderModelManagerLocal::FreeLightDef(idRenderModelManagerLocal *this, idRenderLight *light)
{
  light->FreeLightDefDerivedData(light, 0);
  ((void (__thiscall *)(idRenderLight *, int))light->~idRenderLight)(light, 1);
}

// FUNC: public: __thiscall idRenderModelManagerLocal::idRenderModelManagerLocal(void)
void __thiscall idRenderModelManagerLocal::idRenderModelManagerLocal(idRenderModelManagerLocal *this)
{
  this->__vftable = (idRenderModelManagerLocal_vtbl *)&idRenderModelManagerLocal::`vftable';
  this->models.granularity = 16;
  this->models.list = 0;
  this->models.num = 0;
  this->models.size = 0;
  idHashIndex::Init(&this->hash, 1024, 1024);
  this->defaultModel = 0;
  this->beamModel = 0;
  this->spriteModel = 0;
  this->insideLevelLoad = 0;
  this->trailModel = 0;
}

// FUNC: private: static void __cdecl idRenderModelManagerLocal::ReloadModels_f(class idCmdArgs const &)
void __cdecl idRenderModelManagerLocal::ReloadModels_f(const idCmdArgs *args)
{
  const char *v1; // eax

  fileSystem->SetIsFileLoadingAllowed(fileSystem, 1);
  if ( args->argc <= 1 )
    v1 = &entityFilter;
  else
    v1 = args->argv[1];
  if ( idStr::Icmp(v1, "all") )
    idRenderModelManagerLocal::ReloadModels(&localModelManager, 0);
  else
    idRenderModelManagerLocal::ReloadModels(&localModelManager, 1);
  fileSystem->SetIsFileLoadingAllowed(fileSystem, 0);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::Init(void)
void __thiscall idRenderModelManagerLocal::Init(idRenderModelManagerLocal *this)
{
  idRenderModelStatic *v2; // edi
  idRenderModelManagerLocal_vtbl *v3; // eax
  idRenderModelBeam *v4; // edi
  idRenderModelManagerLocal_vtbl *v5; // edx
  idRenderModelSprite *v6; // edi
  idRenderModelManagerLocal_vtbl *v7; // eax

  cmdSystem->AddCommand(cmdSystem, "listModels", idRenderModelManagerLocal::ListModels_f, 4, "lists all models", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "printModel",
    idRenderModelManagerLocal::PrintModel_f,
    4,
    "prints model info",
    idCmdSystem::ArgCompletion_ModelName);
  cmdSystem->AddCommand(cmdSystem, "reloadModels", idRenderModelManagerLocal::ReloadModels_f, 5, "reloads models", 0);
  cmdSystem->AddCommand(
    cmdSystem,
    "touchModel",
    idRenderModelManagerLocal::TouchModel_f,
    4,
    "touches a model",
    idCmdSystem::ArgCompletion_ModelName);
  this->insideLevelLoad = 0;
  v2 = NewRenderModel<idRenderModelStatic>(RV_HEAP_ID_PERMANENT);
  v2->InitEmpty(v2, "_DEFAULT");
  idRenderModelStatic::MakeDefaultModel(v2);
  v2->SetLevelLoadReferenced(v2, 1);
  v3 = this->__vftable;
  this->defaultModel = v2;
  v3->AddModel(this, v2);
  v4 = NewRenderModel<idRenderModelBeam>(RV_HEAP_ID_PERMANENT);
  v4->InitEmpty(v4, "_BEAM");
  v4->SetLevelLoadReferenced(v4, 1);
  v5 = this->__vftable;
  this->beamModel = v4;
  v5->AddModel(this, v4);
  v6 = NewRenderModel<idRenderModelSprite>(RV_HEAP_ID_PERMANENT);
  v6->InitEmpty(v6, "_SPRITE");
  v6->SetLevelLoadReferenced(v6, 1);
  v7 = this->__vftable;
  this->spriteModel = v6;
  v7->AddModel(this, v6);
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::Shutdown(void)
void __thiscall idRenderModelManagerLocal::Shutdown(idRenderModelManagerLocal *this)
{
  int i; // edi
  idRenderModel *v3; // ecx

  this->mShuttingDown = 1;
  for ( i = 0; i < this->models.num; ++i )
  {
    v3 = this->models.list[i];
    if ( v3 )
      ((void (__thiscall *)(idRenderModel *, int))v3->~idRenderModel)(v3, 1);
    this->models.list[i] = 0;
  }
  if ( this->models.list )
    Memory::Free(this->models.list);
  this->models.list = 0;
  this->models.num = 0;
  this->models.size = 0;
  idHashIndex::Free(&this->hash);
  this->mShuttingDown = 0;
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::Reset(void)
void __thiscall idRenderModelManagerLocal::Reset(idRenderModelManagerLocal *this)
{
  _DWORD *v1; // esi
  int v2; // edi
  int num; // eax
  int v5; // ecx
  int j; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  _BYTE *v10; // ebx
  _DWORD *v11; // eax
  int v12; // ecx
  int v13; // edx
  idRenderModel *v14; // ebx
  int i; // [esp+10h] [ebp-28h]
  int ia; // [esp+10h] [ebp-28h]
  _BYTE *v17; // [esp+14h] [ebp-24h]
  idRenderModel *model; // [esp+18h] [ebp-20h]
  int modelList_4; // [esp+20h] [ebp-18h]

  v1 = 0;
  v2 = 0;
  modelList_4 = 0;
  num = this->models.num;
  v5 = 0;
  i = 0;
  if ( num > 0 )
  {
    do
    {
      model = this->models.list[v5];
      if ( !v1 && modelList_4 != 16 )
      {
        modelList_4 = 16;
        if ( v2 > 16 )
          v2 = 16;
        v1 = Memory::Allocate(0x40u);
        for ( j = 0; j < v2; ++j )
          v1[j] = *(_DWORD *)(4 * j);
      }
      v7 = modelList_4;
      if ( v2 == modelList_4 )
      {
        v8 = (modelList_4 + 16) % 16;
        v9 = modelList_4 + 16 - v8;
        if ( v9 > 0 )
        {
          if ( v9 != modelList_4 )
          {
            v10 = v1;
            v17 = v1;
            modelList_4 = modelList_4 + 16 - v8;
            if ( v9 < v2 )
              v2 = v7 + 16 - v8;
            v11 = Memory::Allocate(4 * v9);
            v1 = v11;
            if ( v2 > 0 )
            {
              v12 = v10 - (_BYTE *)v11;
              v13 = v2;
              do
              {
                *v11 = *(_DWORD *)((char *)v11 + v12);
                ++v11;
                --v13;
              }
              while ( v13 );
              v10 = v17;
            }
            if ( v10 )
              Memory::Free(v10);
          }
        }
        else
        {
          if ( v1 )
            Memory::Free(v1);
          v1 = 0;
          v2 = 0;
          modelList_4 = 0;
        }
      }
      v1[v2] = model;
      v5 = i + 1;
      ++v2;
      ++i;
    }
    while ( i < this->models.num );
  }
  for ( ia = 0; ia < v2; ++ia )
  {
    v14 = (idRenderModel *)v1[ia];
    this->RemoveModel(this, v14);
    if ( v14 != this->defaultModel && v14 != this->beamModel && v14 != this->spriteModel )
    {
      v14->PurgeModel(v14);
      this->FreeModel(this, v14);
    }
  }
  R_PurgeTriSurfData(frameData[tr.smpFrame]);
  this->AddModel(this, this->defaultModel);
  this->AddModel(this, this->beamModel);
  this->AddModel(this, this->spriteModel);
  if ( v1 )
    Memory::Free(v1);
}

// FUNC: private: class idRenderModel * __thiscall idRenderModelManagerLocal::GetModel(char const *,bool)
idRenderModelMD5 *__userpurge idRenderModelManagerLocal::GetModel@<eax>(
        idRenderModelManagerLocal *this@<ecx>,
        int a2@<edi>,
        char *modelName,
        bool createIfNotFound,
        char a5)
{
  int v5; // esi
  char *data; // ecx
  unsigned __int8 i; // al
  unsigned __int8 v8; // al
  int v9; // edi
  char *v10; // ecx
  int v11; // edx
  int v12; // ebp
  int v13; // edi
  idRenderModelMD5 *v14; // esi
  const char *v15; // eax
  int len; // esi
  char *v18; // ecx
  char *v19; // edx
  char v20; // al
  int v21; // esi
  int v22; // eax
  char v23; // cl
  char *v24; // edx
  int v25; // esi
  int v26; // eax
  char v27; // cl
  char *v28; // edx
  char *v29; // ecx
  unsigned __int8 v30; // al
  int j; // edi
  unsigned int v32; // edx
  int v33; // ebp
  int v34; // edi
  const char *v35; // eax
  idStr *v36; // eax
  idFileSystem_vtbl *v37; // edx
  idFile *v38; // esi
  rvRenderModelMD5R *v39; // eax
  idRenderModelMD5 *v40; // eax
  idRenderModelMD3 *v41; // eax
  rvRenderModelMD5R *v42; // eax
  rvRenderModelMD5R *v43; // edi
  idRenderModelStatic *v44; // eax
  idRenderModelMD5 *v45; // eax
  idRenderModelMD5_vtbl *v46; // edx
  rvRenderModelMD5R *v47; // eax
  char *v48; // [esp+0h] [ebp-B0h]
  idStr md5rName; // [esp+1Ch] [ebp-94h] BYREF
  idStr canonical; // [esp+3Ch] [ebp-74h] BYREF
  idRenderModelManagerLocal *v52; // [esp+5Ch] [ebp-54h]
  idStr extension; // [esp+60h] [ebp-50h] BYREF
  rvRenderModelMD5R *v54; // [esp+80h] [ebp-30h]
  idStr result; // [esp+84h] [ebp-2Ch] BYREF
  int v56; // [esp+ACh] [ebp-4h]
  void *retaddr; // [esp+B0h] [ebp+0h]

  v5 = 0;
  v52 = this;
  canonical.len = 0;
  canonical.alloced = 20;
  canonical.data = canonical.baseBuffer;
  canonical.baseBuffer[0] = 0;
  v56 = 1;
  extension.len = 0;
  extension.alloced = 20;
  extension.data = extension.baseBuffer;
  extension.baseBuffer[0] = 0;
  if ( modelName && *modelName )
  {
    idStr::operator=(&canonical, modelName);
    data = canonical.data;
    for ( i = *canonical.data; i; i = canonical.data[v5] )
    {
      if ( idStr::lowerCaseCharacter[i] )
        i = idStr::lowerCaseCharacter[i];
      *data = i;
      data = &canonical.data[++v5];
    }
    idStr::BackSlashesToSlashes(&canonical);
    v8 = *modelName;
    v9 = 0;
    v10 = modelName;
    if ( *modelName )
    {
      do
      {
        if ( idStr::lowerCaseCharacter[v8] )
          v8 = idStr::lowerCaseCharacter[v8];
        v11 = (char)v8 * (_DWORD)&v10[119 - (_DWORD)modelName];
        v8 = *++v10;
        v9 += v11;
      }
      while ( v8 );
    }
    v12 = (int)v52;
    v13 = v52->hash.hash[v9 & v52->hash.hashMask & v52->hash.hashMask & v52->hash.lookupMask];
    if ( v13 != -1 )
    {
      while ( 1 )
      {
        v14 = *(idRenderModelMD5 **)(*(_DWORD *)(v12 + 16) + 4 * v13);
        v15 = v14->Name(v14);
        if ( !idStr::Icmp(canonical.data, v15) )
          break;
        v13 = *(_DWORD *)(*(_DWORD *)(v12 + 32) + 4 * (v13 & *(_DWORD *)(v12 + 44)));
        if ( v13 == -1 )
          goto LABEL_14;
      }
      if ( ((unsigned __int8 (__thiscall *)(idRenderModelMD5 *, int))v14->IsLoaded)(v14, a2) )
      {
        if ( *(_BYTE *)(v12 + 64) )
          v14->TouchData(v14);
      }
      else
      {
        v14->LoadModel(v14);
      }
      v14->SetLevelLoadReferenced(v14, 1);
      LOBYTE(v56) = 0;
      idStr::FreeData(&extension);
      v56 = -1;
      goto LABEL_21;
    }
LABEL_14:
    idStr::ExtractFileExtension(&canonical, &extension);
    if ( !idStr::Icmp(extension.data, "bse") )
    {
      v14 = (idRenderModelMD5 *)NewRenderModel<rvRenderModelBSE>(RV_HEAP_ID_LEVEL);
      ((void (__thiscall *)(idRenderModelMD5 *, char *, int))v14->InitFromFile)(v14, canonical.data, a2);
      goto LABEL_95;
    }
    len = canonical.len;
    md5rName.len = 0;
    md5rName.alloced = 20;
    md5rName.data = md5rName.baseBuffer;
    md5rName.baseBuffer[0] = 0;
    if ( canonical.len + 1 > 20 )
      idStr::ReAllocate(&md5rName, canonical.len + 1, 1);
    v18 = canonical.data;
    v19 = md5rName.data;
    do
    {
      v20 = *v18;
      *v19++ = *v18++;
    }
    while ( v20 );
    md5rName.len = len;
    LOBYTE(v56) = 2;
    idStr::StripAbsoluteFileExtension(&md5rName);
    if ( !idStr::Icmp(extension.data, "ase")
      || !idStr::Icmp(extension.data, "lwo")
      || !idStr::Icmp(extension.data, "flt") )
    {
      v21 = md5rName.len + 7;
      if ( md5rName.len + 8 > md5rName.alloced )
        idStr::ReAllocate(&md5rName, md5rName.len + 8, 1);
      v22 = 0;
      v23 = 95;
      do
      {
        v24 = &md5rName.data[v22++];
        v24[md5rName.len] = v23;
        v23 = aStatic_0[v22];
      }
      while ( v23 );
      md5rName.len = v21;
      md5rName.data[v21] = 0;
    }
    v25 = md5rName.len + 5;
    if ( md5rName.len + 6 > md5rName.alloced )
      idStr::ReAllocate(&md5rName, md5rName.len + 6, 1);
    v26 = 0;
    v27 = 46;
    do
    {
      v28 = &md5rName.data[v26++];
      v28[md5rName.len] = v27;
      v27 = aMd5r_0[v26];
    }
    while ( v27 );
    md5rName.len = v25;
    md5rName.data[v25] = 0;
    v29 = md5rName.data;
    v30 = *md5rName.data;
    for ( j = 0; v30; j += v32 )
    {
      if ( idStr::lowerCaseCharacter[v30] )
        v30 = idStr::lowerCaseCharacter[v30];
      v32 = (char)v30 * (_DWORD)&v29[119 - (unsigned int)md5rName.data];
      v30 = *++v29;
    }
    v33 = (int)v52;
    v34 = v52->hash.hash[j & v52->hash.hashMask & v52->hash.hashMask & v52->hash.lookupMask];
    if ( v34 != -1 )
    {
      while ( 1 )
      {
        v14 = *(idRenderModelMD5 **)(*(_DWORD *)(v33 + 16) + 4 * v34);
        v35 = v14->Name(v14);
        if ( !idStr::Icmp(md5rName.data, v35) )
          break;
        v34 = *(_DWORD *)(*(_DWORD *)(v33 + 32) + 4 * (v34 & *(_DWORD *)(v33 + 44)));
        if ( v34 == -1 )
          goto LABEL_45;
      }
      if ( ((unsigned __int8 (__thiscall *)(idRenderModelMD5 *, int))v14->IsLoaded)(v14, a2) )
      {
        if ( *(_BYTE *)(v33 + 64) )
          v14->TouchData(v14);
      }
      else
      {
        v14->LoadModel(v14);
      }
      v14->SetLevelLoadReferenced(v14, 1);
      LOBYTE(v56) = 1;
      idStr::FreeData(&md5rName);
      goto LABEL_99;
    }
LABEL_45:
    if ( !r_forceConvertMD5R.internalVar->integerValue )
    {
      v36 = operator+(&result, &md5rName, "c");
      v37 = idLib::fileSystem->__vftable;
      v48 = v36->data;
      LOBYTE(v56) = 3;
      v38 = v37->OpenFileRead(idLib::fileSystem, v48, 1, 0);
      LOBYTE(v56) = 2;
      idStr::FreeData(&result);
      if ( v38 || (v38 = idLib::fileSystem->OpenFileRead(idLib::fileSystem, md5rName.data, 1, 0)) != 0 )
      {
        idLib::fileSystem->CloseFile(idLib::fileSystem, v38);
        v39 = (rvRenderModelMD5R *)Memory::Allocate(0xC4u);
        v54 = v39;
        LOBYTE(v56) = 4;
        if ( v39 )
        {
          rvRenderModelMD5R::rvRenderModelMD5R(v39);
          v14 = v40;
        }
        else
        {
          v14 = 0;
        }
        LOBYTE(v56) = 2;
        if ( !v14 )
        {
          (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
            common.type,
            "ModelManager: out of memory");
LABEL_58:
          LOBYTE(v56) = 1;
          idStr::FreeData(&md5rName);
LABEL_59:
          LOBYTE(v56) = 0;
          idStr::FreeData(&extension);
          v56 = -1;
          idStr::FreeData(&canonical);
          return 0;
        }
        ((void (__thiscall *)(idRenderModelMD5 *, char *, int))v14->InitFromFile)(v14, md5rName.data, a2);
LABEL_94:
        LOBYTE(retaddr) = 1;
        idStr::FreeData((idStr *)&md5rName.data);
        v12 = extension.len;
LABEL_95:
        v14->SetLevelLoadReferenced(v14, 1);
        if ( !a5 && v14->IsDefaultModel(v14) )
        {
          ((void (__thiscall *)(idRenderModelMD5 *, int))v14->~idRenderModelMD5)(v14, 1);
          goto LABEL_59;
        }
        (*(void (__thiscall **)(int, idRenderModelMD5 *))(*(_DWORD *)v12 + 96))(v12, v14);
LABEL_99:
        LOBYTE(v56) = 0;
        idStr::FreeData(&extension);
        v56 = -1;
LABEL_21:
        idStr::FreeData(&canonical);
        return v14;
      }
    }
    if ( idStr::Icmp(extension.data, "ase") && idStr::Icmp(extension.data, "lwo") && idStr::Icmp(extension.data, "flt") )
    {
      if ( !idStr::Icmp(extension.data, "ma") )
      {
        v41 = (idRenderModelMD3 *)NewRenderModel<idRenderModelStatic>(RV_HEAP_ID_LEVEL);
        goto LABEL_66;
      }
      if ( idStr::Icmp(extension.data, "md5mesh") )
      {
        if ( idStr::Icmp(extension.data, "md3") )
        {
          if ( idStr::Icmp(extension.data, "liquid") )
          {
            if ( extension.len )
              (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 136))(
                common.type,
                "unknown model type '%s'",
                canonical.data);
            if ( !createIfNotFound )
              goto LABEL_58;
            v14 = (idRenderModelMD5 *)NewRenderModel<idRenderModelStatic>(RV_HEAP_ID_LEVEL);
            ((void (__thiscall *)(idRenderModelMD5 *, char *, int))v14->InitEmpty)(v14, canonical.data, a2);
            idRenderModelStatic::MakeDefaultModel(v14);
            goto LABEL_94;
          }
          v41 = (idRenderModelMD3 *)NewRenderModel<idRenderModelLiquid>(RV_HEAP_ID_LEVEL);
        }
        else
        {
          v41 = NewRenderModel<idRenderModelMD3>(RV_HEAP_ID_LEVEL);
        }
LABEL_66:
        v14 = (idRenderModelMD5 *)v41;
        ((void (__thiscall *)(idRenderModelMD3 *, char *, int))v41->InitFromFile)(v41, canonical.data, a2);
        goto LABEL_94;
      }
      v14 = NewRenderModel<idRenderModelMD5>(RV_HEAP_ID_LEVEL);
      ((void (__thiscall *)(idRenderModelMD5 *, char *, int))v14->InitFromFile)(v14, canonical.data, a2);
      if ( !r_convertMD5toMD5R.internalVar->integerValue
        || v14->IsDefaultModel(v14)
        || idAsyncNetwork::serverDedicated.internalVar->integerValue )
      {
        goto LABEL_94;
      }
      v42 = NewRenderModel<rvRenderModelMD5R>(RV_HEAP_ID_LEVEL);
      v43 = v42;
      if ( v42 )
      {
        if ( rvRenderModelMD5R::Init(v42, v14) )
        {
          ((void (__thiscall *)(idRenderModelMD5 *, int))v14->~idRenderModelMD5)(v14, 1);
          v14 = (idRenderModelMD5 *)v43;
          goto LABEL_94;
        }
        (*(void (__cdecl **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 136))(
          common.type,
          "Failed to convert the MD5 \"%s\" to an MD5R",
          canonical.alloced);
LABEL_93:
        ((void (__thiscall *)(rvRenderModelMD5R *, int))v43->~rvRenderModelMD5R)(v43, 1);
        goto LABEL_94;
      }
    }
    else
    {
      v44 = (idRenderModelStatic *)Memory::Allocate(0x70u);
      v54 = (rvRenderModelMD5R *)v44;
      LOBYTE(v56) = 5;
      if ( v44 )
      {
        idRenderModelStatic::idRenderModelStatic(v44);
        v14 = v45;
      }
      else
      {
        v14 = 0;
      }
      v46 = v14->__vftable;
      LOBYTE(v56) = 2;
      ((void (__thiscall *)(idRenderModelMD5 *, char *, int))v46->InitFromFile)(v14, canonical.data, a2);
      if ( !r_convertStaticToMD5R.internalVar->integerValue || v14->IsDefaultModel(v14) )
        goto LABEL_94;
      v47 = NewRenderModel<rvRenderModelMD5R>(RV_HEAP_ID_LEVEL);
      v43 = v47;
      if ( v47 )
      {
        if ( rvRenderModelMD5R::Init(v47, v14, MD5R_SOURCE_LWO_ASE_FLT) )
        {
          collisionModelManager->ExtractCollisionModel(collisionModelManager, v14, (const char *)canonical.alloced);
          ((void (__thiscall *)(idRenderModelMD5 *, int))v14->~idRenderModelMD5)(v14, 1);
          v14 = (idRenderModelMD5 *)v43;
          goto LABEL_94;
        }
        (*(void (__cdecl **)(netadrtype_t, const char *, int))(*(_DWORD *)common.type + 136))(
          common.type,
          "Failed to convert the static model \"%s\" to an MD5R",
          canonical.alloced);
        goto LABEL_93;
      }
    }
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "ModelManager: out of memory");
    ((void (__thiscall *)(idRenderModelMD5 *, int))v14->~idRenderModelMD5)(v14, 1);
    goto LABEL_58;
  }
  LOBYTE(v56) = 0;
  idStr::FreeData(&extension);
  v56 = -1;
  idStr::FreeData(&canonical);
  return 0;
}

// FUNC: public: virtual class idRenderModel * __thiscall idRenderModelManagerLocal::FindModel(char const *)
idRenderModel *__thiscall idRenderModelManagerLocal::FindModel(idRenderModelManagerLocal *this, const char *modelName)
{
  return idRenderModelManagerLocal::GetModel(this, modelName, 1);
}

// FUNC: public: virtual class idRenderModel * __thiscall idRenderModelManagerLocal::CheckModel(char const *)
None

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::AddModel(class idRenderModel *)
void __thiscall idRenderModelManagerLocal::AddModel(idRenderModelManagerLocal *this, idRenderModel *model)
{
  int granularity; // eax
  bool v4; // cc
  int i; // eax
  int size; // ecx
  int num; // ebp
  int v8; // ecx
  idRenderModel **list; // edi
  int j; // eax
  idHashIndex *p_hash; // edi
  const char *v12; // eax
  unsigned __int8 v13; // cl
  int v14; // edx
  int v15; // ebp
  int v16; // ebx
  int v17; // esi
  int indexSize; // eax
  int v19; // eax

  if ( !this->models.list )
  {
    granularity = this->models.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->models.size )
      {
        v4 = granularity < this->models.num;
        this->models.size = granularity;
        if ( v4 )
          this->models.num = granularity;
        this->models.list = (idRenderModel **)Memory::Allocate(4 * granularity);
        for ( i = 0; i < this->models.num; ++i )
          this->models.list[i] = *(idRenderModel **)(4 * i);
      }
    }
    else
    {
      this->models.list = 0;
      this->models.num = 0;
      this->models.size = 0;
    }
  }
  size = this->models.size;
  num = this->models.num;
  if ( num == size )
  {
    if ( !this->models.granularity )
      this->models.granularity = 16;
    v8 = this->models.granularity + size - (this->models.granularity + size) % this->models.granularity;
    if ( v8 > 0 )
    {
      if ( v8 != this->models.size )
      {
        list = this->models.list;
        this->models.size = v8;
        if ( v8 < num )
          this->models.num = v8;
        this->models.list = (idRenderModel **)Memory::Allocate(4 * v8);
        for ( j = 0; j < this->models.num; ++j )
          this->models.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->models.list )
        Memory::Free(this->models.list);
      this->models.list = 0;
      this->models.num = 0;
      this->models.size = 0;
    }
  }
  this->models.list[this->models.num++] = model;
  p_hash = &this->hash;
  v12 = model->Name(model);
  v13 = *v12;
  v14 = 0;
  if ( *v12 )
  {
    v15 = 119;
    do
    {
      if ( idStr::lowerCaseCharacter[v13] )
        v13 = idStr::lowerCaseCharacter[v13];
      ++v12;
      v14 += v15 * (char)v13;
      v13 = *v12;
      ++v15;
    }
    while ( *v12 );
  }
  v16 = v14 & this->hash.hashMask;
  v17 = this->models.num - 1;
  if ( p_hash->hash == idHashIndex::INVALID_INDEX )
  {
    indexSize = p_hash->indexSize;
    if ( v17 >= indexSize )
      indexSize = v17 + 1;
    idHashIndex::Allocate(p_hash, p_hash->hashSize, indexSize);
  }
  else if ( v17 >= p_hash->indexSize )
  {
    idHashIndex::ResizeIndex(p_hash, v17 + 1);
  }
  v19 = v16 & p_hash->hashMask;
  p_hash->indexChain[v17] = p_hash->hash[v19];
  p_hash->hash[v19] = v17;
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::RemoveModel(class idRenderModel *)
void __thiscall idRenderModelManagerLocal::RemoveModel(idRenderModelManagerLocal *this, idRenderModel *model)
{
  int num; // edx
  int v4; // eax
  idRenderModel **list; // edi
  int v6; // ebx
  unsigned __int8 *v7; // eax
  unsigned __int8 v8; // cl
  int v9; // ebp
  int v10; // edi
  int *hash; // ecx
  int v12; // eax
  int v13; // edx
  int v14; // edx
  int *indexChain; // edx
  int v16; // ecx
  int v17; // eax
  int i; // edx
  int v19; // ecx
  int j; // eax
  int v21; // ecx
  int k; // eax
  int *v23; // ecx
  int v24; // edi
  int *v25; // ecx
  int v26; // eax
  bool v27; // cc
  int v28; // eax
  idRenderModel **v29; // ecx
  idRenderModel *v30; // edx
  idRenderModel **v31; // ecx

  num = this->models.num;
  v4 = 0;
  if ( num <= 0 )
  {
LABEL_5:
    v6 = -1;
  }
  else
  {
    list = this->models.list;
    while ( *list != model )
    {
      ++v4;
      ++list;
      if ( v4 >= num )
        goto LABEL_5;
    }
    v6 = v4;
  }
  v7 = (unsigned __int8 *)((int (*)(void))model->Name)();
  v8 = *v7;
  v9 = 0;
  if ( *v7 )
  {
    v10 = 119;
    do
    {
      if ( idStr::lowerCaseCharacter[v8] )
        v8 = idStr::lowerCaseCharacter[v8];
      ++v7;
      v9 += v10 * (char)v8;
      v8 = *v7;
      ++v10;
    }
    while ( *v7 );
  }
  hash = this->hash.hash;
  v12 = v9 & this->hash.hashMask;
  if ( hash != idHashIndex::INVALID_INDEX )
  {
    v13 = hash[v12];
    if ( v13 == v6 )
    {
      v14 = this->hash.indexChain[v6];
    }
    else
    {
      v12 = hash[v12];
      if ( v13 == -1 )
      {
LABEL_22:
        this->hash.indexChain[v6] = -1;
        goto LABEL_23;
      }
      indexChain = this->hash.indexChain;
      while ( 1 )
      {
        v16 = indexChain[v12];
        if ( v16 == v6 )
          break;
        v12 = indexChain[v12];
        if ( v16 == -1 )
          goto LABEL_22;
      }
      hash = this->hash.indexChain;
      v14 = hash[v6];
    }
    hash[v12] = v14;
    goto LABEL_22;
  }
LABEL_23:
  if ( this->hash.hash != idHashIndex::INVALID_INDEX )
  {
    v17 = 0;
    for ( i = v6; v17 < this->hash.hashSize; ++v17 )
    {
      v19 = this->hash.hash[v17];
      if ( v19 >= v6 )
      {
        if ( v19 > i )
          i = this->hash.hash[v17];
        --this->hash.hash[v17];
      }
    }
    for ( j = 0; j < this->hash.indexSize; ++j )
    {
      v21 = this->hash.indexChain[j];
      if ( v21 >= v6 )
      {
        if ( v21 > i )
          i = this->hash.indexChain[j];
        --this->hash.indexChain[j];
      }
    }
    for ( k = v6; k < i; *v25 = v24 )
    {
      v23 = this->hash.indexChain;
      v24 = v23[k + 1];
      v25 = &v23[k++];
    }
    this->hash.indexChain[i] = -1;
  }
  if ( v6 >= 0 )
  {
    v26 = this->models.num;
    if ( v6 < v26 )
    {
      v27 = v6 < v26 - 1;
      this->models.num = v26 - 1;
      v28 = v6;
      if ( v27 )
      {
        do
        {
          v29 = this->models.list;
          v30 = v29[v28 + 1];
          v31 = &v29[v28++];
          *v31 = v30;
        }
        while ( v28 < this->models.num );
      }
    }
  }
}

// FUNC: public: virtual struct srfTriangles_s * __thiscall idRenderModelManagerLocal::CreateShadowVolume(struct srfTriangles_s const *,class idRenderLight const *,int)
srfTriangles_s *__thiscall idRenderModelManagerLocal::CreateShadowVolume(
        idRenderModelManagerLocal *this,
        const srfTriangles_s *tri,
        const idRenderLightLocal *light,
        int optimize)
{
  srfTriangles_s *v4; // esi
  srfCullInfo_s cullInfo; // [esp+8h] [ebp-1F8h] BYREF
  idRenderEntityLocal space; // [esp+70h] [ebp-190h] BYREF
  int v8; // [esp+1FCh] [ebp-4h]

  idRenderEntityLocal::idRenderEntityLocal(&space);
  memset(&cullInfo, 0, sizeof(cullInfo));
  v8 = 0;
  space.modelMatrix[0] = 1.0;
  space.modelMatrix[5] = 1.0;
  space.modelMatrix[10] = 1.0;
  space.modelMatrix[15] = 1.0;
  v4 = R_CreateShadowVolume(&space, tri, light, optimize, &cullInfo);
  R_FreeInteractionCullInfo(&cullInfo);
  return v4;
}

// FUNC: public: virtual void __thiscall idRenderModelManagerLocal::PrintMemInfo(class MemInfo *)
void __thiscall idRenderModelManagerLocal::PrintMemInfo(idRenderModelManagerLocal *this, MemInfo *mi)
{
  idStr *v2; // eax
  idFileSystem_vtbl *v3; // edx
  idFile *v4; // edi
  int *v5; // ebx
  int num; // eax
  int j; // ecx
  int v8; // esi
  int *v9; // ebp
  idRenderModel *v10; // edi
  int v11; // eax
  int v12; // ebp
  idRenderModel *v13; // esi
  int v14; // eax
  char *v15; // ebp
  idFile v16; // eax
  idRenderModel_vtbl *v17; // edx
  int v18; // eax
  idStr *v19; // esi
  idStr *v20; // eax
  idFile_vtbl *v21; // ecx
  char *v22; // [esp-20h] [ebp-C8h]
  char *v23; // [esp-1Ch] [ebp-C4h]
  char *data; // [esp-8h] [ebp-B0h]
  int i; // [esp+Ch] [ebp-9Ch]
  int ia; // [esp+Ch] [ebp-9Ch]
  int totalMem; // [esp+10h] [ebp-98h]
  idFile *f; // [esp+14h] [ebp-94h]
  idFile *fa; // [esp+14h] [ebp-94h]
  int v30; // [esp+18h] [ebp-90h]
  idStr v31; // [esp+1Ch] [ebp-8Ch] BYREF
  idStr v32; // [esp+3Ch] [ebp-6Ch] BYREF
  idStr result; // [esp+5Ch] [ebp-4Ch] BYREF
  idStr v34; // [esp+7Ch] [ebp-2Ch] BYREF
  int v35; // [esp+A4h] [ebp-4h]

  totalMem = 0;
  v2 = operator+(&result, &mi->filebase, "_models.txt");
  v3 = fileSystem->__vftable;
  data = v2->data;
  v35 = 0;
  v4 = v3->OpenFileWrite(fileSystem, data, "fs_savepath", 0);
  f = v4;
  v35 = -1;
  idStr::FreeData(&result);
  if ( v4 )
  {
    v5 = (int *)Memory::Allocate(4 * localModelManager.models.num);
    num = localModelManager.models.num;
    for ( j = 0; j < localModelManager.models.num; ++j )
    {
      v5[j] = j;
      num = localModelManager.models.num;
    }
    if ( num - 1 > 0 )
    {
      v8 = 1;
      i = 1;
      v9 = v5;
      do
      {
        if ( v8 < num )
        {
          do
          {
            v10 = localModelManager.models.list[v5[v8]];
            v30 = localModelManager.models.list[*v9]->Memory(localModelManager.models.list[*v9]);
            if ( v30 < v10->Memory(v10) )
            {
              v11 = *v9;
              *v9 = v5[v8];
              v5[v8] = v11;
            }
            num = localModelManager.models.num;
            ++v8;
          }
          while ( v8 < localModelManager.models.num );
          v4 = f;
          v8 = i;
        }
        ++v8;
        ++v9;
        i = v8;
      }
      while ( v8 - 1 < num - 1 );
    }
    v12 = 0;
    ia = 0;
    if ( num > 0 )
    {
      do
      {
        v13 = localModelManager.models.list[v5[v12]];
        if ( v13->IsLoaded(v13) )
        {
          v14 = v13->Memory(v13);
          totalMem += v14;
          v15 = idStr::FormatNumber(&v31, v14)->data;
          v16.__vftable = v4->__vftable;
          v17 = v13->__vftable;
          v35 = 1;
          fa = (idFile *)v16.__vftable;
          v18 = (int)v17->Name(v13);
          ((void (*)(idFile *, const char *, ...))fa[12].__vftable)(v4, "%s %s\n", v15, v18);
          v35 = -1;
          idStr::FreeData(&v31);
          v12 = ia;
        }
        ia = ++v12;
      }
      while ( v12 < localModelManager.models.num );
    }
    Memory::Free(v5);
    mi->modelAssetsTotal = totalMem;
    mi->modelAssetsCount = localModelManager.models.num;
    v19 = idStr::FormatNumber(&v34, localModelManager.models.num);
    v35 = 2;
    v20 = idStr::FormatNumber(&v32, totalMem);
    v21 = v4->__vftable;
    v23 = v19->data;
    v22 = v20->data;
    LOBYTE(v35) = 3;
    v21->Printf(v4, "\nTotal model bytes allocated: %s (%s items)\n", v22, v23);
    LOBYTE(v35) = 2;
    idStr::FreeData(&v32);
    v35 = -1;
    idStr::FreeData(&v34);
    fileSystem->CloseFile(fileSystem, v4);
  }
}
