
// FUNC: public: void __thiscall idGuiModel::WriteToDemo(class idDemoFile *)
void __thiscall idGuiModel::WriteToDemo(idGuiModel *this, idDemoFile *demo)
{
  int num; // ebp
  int v5; // edi
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ebp
  int i; // edi
  int v12; // edi
  int v13; // ebp
  guiModelSurface_t *list; // edi
  int material; // eax
  guiModelSurface_t *v16; // edi
  const char *v17; // eax
  idDemoFile *demoa; // [esp+58h] [ebp+4h]

  num = this->verts.num;
  demo->WriteInt(demo, num);
  if ( num > 0 )
  {
    v5 = 0;
    do
    {
      demo->WriteVec3(demo, (const idVec3 *)&this->verts.list[v5]);
      demo->WriteVec2(demo, &this->verts.list[v5].st);
      demo->WriteVec3(demo, &this->verts.list[v5].normal);
      demo->WriteVec3(demo, this->verts.list[v5].tangents);
      demo->WriteVec3(demo, &this->verts.list[v5].tangents[1]);
      LOBYTE(v6) = this->verts.list[v5].color[0];
      demo->WriteUnsignedChar(demo, v6);
      LOBYTE(v7) = this->verts.list[v5].color[1];
      demo->WriteUnsignedChar(demo, v7);
      LOBYTE(v8) = this->verts.list[v5].color[2];
      demo->WriteUnsignedChar(demo, v8);
      LOBYTE(v9) = this->verts.list[v5].color[3];
      demo->WriteUnsignedChar(demo, v9);
      ++v5;
      --num;
    }
    while ( num );
  }
  v10 = this->indexes.num;
  demo->WriteInt(demo, v10);
  for ( i = 0; i < v10; ++i )
    demo->WriteInt(demo, this->indexes.list[i]);
  v12 = this->surfaces.num;
  demo->WriteInt(demo, v12);
  if ( v12 > 0 )
  {
    v13 = 0;
    demoa = (idDemoFile *)v12;
    do
    {
      list = this->surfaces.list;
      material = (int)list[v13].material;
      v16 = &list[v13];
      demo->WriteInt(demo, material);
      ((void (__thiscall *)(idDemoFile *, _DWORD))demo->WriteFloat)(demo, LODWORD(v16->color[0]));
      ((void (__thiscall *)(idDemoFile *, _DWORD))demo->WriteFloat)(demo, LODWORD(v16->color[1]));
      ((void (__thiscall *)(idDemoFile *, _DWORD))demo->WriteFloat)(demo, LODWORD(v16->color[2]));
      ((void (__thiscall *)(idDemoFile *, _DWORD))demo->WriteFloat)(demo, LODWORD(v16->color[3]));
      demo->WriteInt(demo, v16->firstVert);
      demo->WriteInt(demo, v16->numVerts);
      demo->WriteInt(demo, v16->firstIndex);
      demo->WriteInt(demo, v16->numIndexes);
      v17 = v16->material->base->GetName(v16->material->base);
      idDemoFile::WriteHashString(demo, v17);
      ++v13;
      demoa = (idDemoFile *)((char *)demoa - 1);
    }
    while ( demoa );
  }
}

// FUNC: private: void __thiscall idGuiModel::EmitSurface(struct guiModelSurface_t *,float * const,float * const,int,float *)
void __thiscall idGuiModel::EmitSurface(
        idGuiModel *this,
        guiModelSurface_t *surf,
        float *modelMatrix,
        float *modelViewMatrix,
        int depthHackInViewID,
        float *shaderParms)
{
  const srfTriangles_s *v7; // ebx
  int numIndexes; // eax
  int *v9; // eax
  unsigned int v10; // ecx
  idDrawVert *v11; // eax
  unsigned int v12; // ecx
  vertCache_s *v13; // eax
  float v14; // edx
  float v15; // ecx
  float v16; // edx
  const viewEntity_s *v17; // eax
  renderEntity_s renderEntity; // [esp+10h] [ebp-E0h] BYREF

  if ( surf->numVerts )
  {
    v7 = (const srfTriangles_s *)R_ClearedFrameAlloc(180);
    numIndexes = surf->numIndexes;
    v7->numIndexes = numIndexes;
    v7->numVerts = surf->numVerts;
    if ( r_useIndexBuffers.internalVar->integerValue )
      v7->indexCache = idVertexCache::AllocFrameTemp(
                         &vertexCache,
                         &this->indexes.list[surf->firstIndex],
                         4 * numIndexes,
                         1u);
    v9 = (int *)R_FrameAlloc(4 * v7->numIndexes);
    v10 = 4 * v7->numIndexes;
    v7->indexes = v9;
    qmemcpy(v9, &this->indexes.list[surf->firstIndex], v10);
    v11 = (idDrawVert *)R_FrameAlloc(v7->numVerts << 6);
    v12 = v7->numVerts << 6;
    v7->verts = v11;
    qmemcpy(v11, &this->verts.list[surf->firstVert], v12);
    v13 = idVertexCache::AllocFrameTemp(&vertexCache, v7->verts, v7->numVerts << 6, 0);
    v7->ambientCache = v13;
    if ( v13 )
    {
      memset(&renderEntity, 0, sizeof(renderEntity));
      v14 = surf->color[1];
      renderEntity.shaderParms[0] = surf->color[0];
      v15 = surf->color[2];
      renderEntity.shaderParms[1] = v14;
      v16 = surf->color[3];
      renderEntity.shaderParms[2] = v15;
      renderEntity.shaderParms[3] = v16;
      v17 = (const viewEntity_s *)R_ClearedFrameAlloc(168);
      qmemcpy(v17->modelMatrix, modelMatrix, sizeof(v17->modelMatrix));
      qmemcpy(v17->modelViewMatrix, modelViewMatrix, sizeof(v17->modelViewMatrix));
      v17->weaponDepthHackInViewID = depthHackInViewID;
      R_AddDrawSurf(v7, v17, &renderEntity, surf->material, &tr.viewDef->scissor, this != tr.guiModel ? 0 : 2);
    }
  }
}

// FUNC: public: void __thiscall idGuiModel::EmitToCurrentView(float * const,int,float *)
void __thiscall idGuiModel::EmitToCurrentView(
        idGuiModel *this,
        float *modelMatrix,
        int depthHackInViewID,
        float *shaderParms)
{
  int v5; // edi
  int v6; // ebx
  float modelViewMatrix[16]; // [esp+Ch] [ebp-40h] BYREF

  myGlMultMatrix(modelMatrix, tr.viewDef->worldSpace.modelViewMatrix, modelViewMatrix);
  v5 = 0;
  if ( this->surfaces.num > 0 )
  {
    v6 = 0;
    do
    {
      idGuiModel::EmitSurface(
        this,
        &this->surfaces.list[v6],
        modelMatrix,
        modelViewMatrix,
        depthHackInViewID,
        shaderParms);
      ++v5;
      ++v6;
    }
    while ( v5 < this->surfaces.num );
  }
}

// FUNC: public: void __thiscall idGuiModel::EmitFullScreen(void)
void __thiscall idGuiModel::EmitFullScreen(idGuiModel *this)
{
  int v2; // ebp
  viewDef_s *v3; // esi
  __int16 v4; // cx
  __int16 v5; // dx
  int num; // eax
  viewDef_s *viewDef; // edx
  int v8; // ebx
  viewDef_s *oldViewDef; // [esp+8h] [ebp-4h]

  v2 = 0;
  if ( this->surfaces.list->numVerts )
  {
    v3 = (viewDef_s *)R_ClearedFrameAlloc(636);
    v3->renderFlags |= 2u;
    if ( tr.viewDef && (tr.viewDef->renderFlags & 1) != 0 )
    {
      v3->renderView.x = tr.viewDef->renderView.x;
      v3->renderView.y = tr.viewDef->renderView.y;
      v3->renderView.width = tr.viewDef->renderView.width;
      v3->renderView.height = tr.viewDef->renderView.height;
      v3->viewport.x1 = tr.viewDef->renderView.x;
      v3->viewport.x2 = LOWORD(tr.viewDef->renderView.x) + LOWORD(tr.viewDef->renderView.width);
      v3->viewport.y1 = tr.viewDef->renderView.y;
      v3->viewport.y2 = LOWORD(tr.viewDef->renderView.y) + LOWORD(tr.viewDef->renderView.height);
      v3->scissor.x1 = tr.viewDef->scissor.x1;
      v3->scissor.y1 = tr.viewDef->scissor.y1;
      v3->scissor.x2 = tr.viewDef->scissor.x2;
      v3->scissor.y2 = tr.viewDef->scissor.y2;
    }
    else
    {
      v3->renderView.x = 0;
      v3->renderView.y = 0;
      v3->renderView.width = 640;
      v3->renderView.height = 480;
      idRenderSystemLocal::RenderViewToViewport(&tr, &v3->renderView, &v3->viewport);
      v4 = v3->viewport.x2 - v3->viewport.x1;
      v5 = v3->viewport.y2 - v3->viewport.y1;
      v3->scissor.x1 = 0;
      v3->scissor.y1 = 0;
      v3->scissor.x2 = v4;
      v3->scissor.y2 = v5;
    }
    v3->floatTime = tr.frameShaderTime;
    v3->projectionMatrix[12] = -1.0;
    v3->projectionMatrix[14] = -1.0;
    v3->projectionMatrix[0] = 0.003125;
    v3->projectionMatrix[5] = -0.0041666669;
    v3->projectionMatrix[10] = -2.0;
    v3->projectionMatrix[13] = 1.0;
    v3->projectionMatrix[15] = 1.0;
    v3->worldSpace.modelViewMatrix[0] = 1.0;
    v3->worldSpace.modelViewMatrix[5] = 1.0;
    v3->worldSpace.modelViewMatrix[10] = 1.0;
    v3->worldSpace.modelViewMatrix[15] = 1.0;
    num = this->surfaces.num;
    v3->maxDrawSurfs = num;
    v3->drawSurfs = (drawSurf_s **)R_FrameAlloc(4 * num);
    v3->numDrawSurfs = 0;
    viewDef = tr.viewDef;
    tr.viewDef = v3;
    v8 = 0;
    for ( oldViewDef = viewDef; v8 < this->surfaces.num; ++v2 )
    {
      idGuiModel::EmitSurface(
        this,
        &this->surfaces.list[v2],
        v3->worldSpace.modelMatrix,
        v3->worldSpace.modelViewMatrix,
        0,
        0);
      ++v8;
    }
    tr.viewDef = oldViewDef;
    R_AddDrawViewCmd(v3);
  }
}

// FUNC: private: void __thiscall idGuiModel::AdvanceSurf(void)
void __thiscall idGuiModel::AdvanceSurf(idGuiModel *this)
{
  guiModelSurface_t *surf; // eax
  float v3; // edx
  float v4; // ecx
  float v5; // edx
  const idMaterial *material; // eax
  bool v7; // zf
  int num; // edx
  int v9; // eax
  int granularity; // eax
  bool v11; // cc
  guiModelSurface_t *v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edi
  int size; // ecx
  int v17; // ecx
  guiModelSurface_t *list; // ebp
  guiModelSurface_t *v19; // eax
  int v20; // edx
  int v21; // eax
  guiModelSurface_t s; // [esp+10h] [ebp-24h] BYREF

  if ( this->surfaces.num )
  {
    surf = this->surf;
    v3 = this->surf->color[1];
    s.color[0] = this->surf->color[0];
    v4 = surf->color[2];
    s.color[1] = v3;
    v5 = surf->color[3];
    material = surf->material;
    s.color[2] = v4;
    s.color[3] = v5;
    s.material = material;
  }
  else
  {
    s.color[0] = 1.0;
    s.color[1] = 1.0;
    s.color[2] = 1.0;
    s.color[3] = 1.0;
    s.material = tr.defaultMaterial;
  }
  v7 = this->surfaces.list == 0;
  num = this->indexes.num;
  v9 = this->verts.num;
  s.numIndexes = 0;
  s.firstIndex = num;
  s.numVerts = 0;
  s.firstVert = v9;
  if ( v7 )
  {
    granularity = this->surfaces.granularity;
    if ( granularity > 0 )
    {
      if ( granularity != this->surfaces.size )
      {
        v11 = granularity < this->surfaces.num;
        this->surfaces.size = granularity;
        if ( v11 )
          this->surfaces.num = granularity;
        v12 = (guiModelSurface_t *)Memory::Allocate(36 * granularity);
        v13 = 0;
        v11 = this->surfaces.num <= 0;
        this->surfaces.list = v12;
        if ( !v11 )
        {
          v14 = 0;
          do
          {
            ++v13;
            qmemcpy(&this->surfaces.list[v14], (const void *)(v14 * 36), sizeof(this->surfaces.list[v14]));
            ++v14;
          }
          while ( v13 < this->surfaces.num );
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
  v15 = this->surfaces.num;
  size = this->surfaces.size;
  if ( v15 == size )
  {
    if ( !this->surfaces.granularity )
      this->surfaces.granularity = 16;
    v17 = this->surfaces.granularity + size - (this->surfaces.granularity + size) % this->surfaces.granularity;
    if ( v17 > 0 )
    {
      if ( v17 != this->surfaces.size )
      {
        list = this->surfaces.list;
        this->surfaces.size = v17;
        if ( v17 < v15 )
          this->surfaces.num = v17;
        v19 = (guiModelSurface_t *)Memory::Allocate(36 * v17);
        v20 = 0;
        v11 = this->surfaces.num <= 0;
        this->surfaces.list = v19;
        if ( !v11 )
        {
          v21 = 0;
          do
          {
            ++v20;
            qmemcpy(&this->surfaces.list[v21], &list[v21], sizeof(this->surfaces.list[v21]));
            ++v21;
          }
          while ( v20 < this->surfaces.num );
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
  qmemcpy(&this->surfaces.list[this->surfaces.num++], &s, sizeof(this->surfaces.list[this->surfaces.num++]));
  this->surf = &this->surfaces.list[this->surfaces.num - 1];
}

// FUNC: public: void __thiscall idGuiModel::SetColor(float,float,float,float)
void __thiscall idGuiModel::SetColor(idGuiModel *this, float r, float g, float b, float a)
{
  guiModelSurface_t *surf; // ecx

  if ( glConfig.isInitialized )
  {
    surf = this->surf;
    if ( r != this->surf->color[0] || g != surf->color[1] || b != surf->color[2] || a != surf->color[3] )
    {
      if ( surf->numVerts )
        idGuiModel::AdvanceSurf(this);
      this->surf->color[0] = r;
      this->surf->color[1] = g;
      this->surf->color[2] = b;
      this->surf->color[3] = a;
    }
  }
}

// FUNC: public: __thiscall idGuiModel::idGuiModel(void)
void __thiscall idGuiModel::idGuiModel(idGuiModel *this)
{
  int *list; // edi
  int v3; // ecx
  bool v4; // cc
  int i; // eax
  idDrawVert *v6; // eax
  int num; // ecx
  int v8; // edi
  idDrawVert *v9; // eax
  idDrawVert *v10; // ebx
  int v11; // ebx
  int v12; // edi
  idDrawVert *ptr; // [esp+10h] [ebp-18h]

  this->surfaces.granularity = 16;
  this->surfaces.list = 0;
  this->surfaces.num = 0;
  this->surfaces.size = 0;
  this->indexes.granularity = 16;
  this->indexes.list = 0;
  this->indexes.num = 0;
  this->indexes.size = 0;
  this->verts.granularity = 16;
  this->verts.list = 0;
  this->verts.num = 0;
  this->verts.size = 0;
  list = this->indexes.list;
  this->indexes.granularity = 1000;
  if ( list )
  {
    v3 = this->indexes.num + 999 - (this->indexes.num + 999) % 1000;
    if ( v3 != this->indexes.size )
    {
      if ( v3 > 0 )
      {
        v4 = v3 < this->indexes.num;
        this->indexes.size = v3;
        if ( v4 )
          this->indexes.num = v3;
        this->indexes.list = (int *)Memory::Allocate(4 * v3);
        for ( i = 0; i < this->indexes.num; ++i )
          this->indexes.list[i] = list[i];
        Memory::Free(list);
      }
      else
      {
        Memory::Free(list);
        this->indexes.list = 0;
        this->indexes.num = 0;
        this->indexes.size = 0;
      }
    }
  }
  v6 = this->verts.list;
  this->verts.granularity = 1000;
  ptr = v6;
  if ( v6 )
  {
    num = this->verts.num;
    v8 = num + 999 - (num + 999) % 1000;
    if ( v8 != this->verts.size )
    {
      if ( v8 > 0 )
      {
        this->verts.size = v8;
        if ( v8 < num )
          this->verts.num = v8;
        v9 = (idDrawVert *)Memory::Allocate(v8 << 6);
        v10 = v9;
        if ( v9 )
          `vector constructor iterator'(v9, 0x40u, v8, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
        else
          v10 = 0;
        this->verts.list = v10;
        v11 = 0;
        if ( this->verts.num > 0 )
        {
          v12 = 0;
          do
          {
            idDrawVert::operator=(&this->verts.list[v12].xyz.x, (int)&ptr[v12]);
            ++v11;
            ++v12;
          }
          while ( v11 < this->verts.num );
        }
        if ( ptr )
          Memory::Free(ptr);
      }
      else
      {
        Memory::Free(v6);
        this->verts.list = 0;
        this->verts.num = 0;
        this->verts.size = 0;
      }
    }
  }
}

// FUNC: public: void __thiscall idGuiModel::Clear(void)
void __thiscall idGuiModel::Clear(idGuiModel *this)
{
  if ( this->surfaces.size < 0 )
  {
    if ( this->surfaces.list )
      Memory::Free(this->surfaces.list);
    this->surfaces.list = 0;
    this->surfaces.num = 0;
    this->surfaces.size = 0;
  }
  this->surfaces.num = 0;
  if ( this->indexes.size < 0 )
  {
    if ( this->indexes.list )
      Memory::Free(this->indexes.list);
    this->indexes.list = 0;
    this->indexes.num = 0;
    this->indexes.size = 0;
  }
  this->indexes.num = 0;
  if ( this->verts.size < 0 )
    idList<idDrawVert>::Resize(&this->verts, 0);
  this->verts.num = 0;
  idGuiModel::AdvanceSurf(this);
}

// FUNC: public: void __thiscall idGuiModel::ReadFromDemo(class idDemoFile *)
void __thiscall idGuiModel::ReadFromDemo(idGuiModel *this, idDemoFile *demo)
{
  idDemoFile_vtbl *v3; // edx
  idList<idDrawVert> *p_verts; // esi
  int v6; // eax
  int v7; // edi
  int v8; // edi
  int v9; // esi
  idDemoFile_vtbl *v10; // eax
  int v11; // eax
  int v12; // edi
  bool v13; // cc
  int *list; // esi
  int k; // eax
  int v16; // esi
  idDemoFile_vtbl *v17; // edx
  int v18; // eax
  guiModelSurface_t *v19; // esi
  guiModelSurface_t *v20; // eax
  int v21; // edx
  int v22; // eax
  guiModelSurface_t *v23; // esi
  idDeclManager_vtbl *v24; // edi
  char *HashString; // eax
  int i; // [esp+60h] [ebp-8h] BYREF
  int j; // [esp+64h] [ebp-4h]
  idDemoFile *demoa; // [esp+6Ch] [ebp+4h]
  idDemoFile *demob; // [esp+6Ch] [ebp+4h]

  v3 = demo->__vftable;
  p_verts = &this->verts;
  i = this->verts.num;
  v3->ReadInt(demo, &i);
  v6 = i;
  v7 = i;
  if ( i > p_verts->size )
  {
    idList<idDrawVert>::Resize(p_verts, i);
    v6 = i;
  }
  p_verts->num = v7;
  v8 = 0;
  if ( v6 > 0 )
  {
    v9 = 0;
    do
    {
      demo->ReadVec3(demo, (idVec3 *)&this->verts.list[v9]);
      demo->ReadVec2(demo, &this->verts.list[v9].st);
      demo->ReadVec3(demo, &this->verts.list[v9].normal);
      demo->ReadVec3(demo, this->verts.list[v9].tangents);
      demo->ReadVec3(demo, &this->verts.list[v9].tangents[1]);
      demo->ReadUnsignedChar(demo, this->verts.list[v9].color);
      demo->ReadUnsignedChar(demo, &this->verts.list[v9].color[1]);
      demo->ReadUnsignedChar(demo, &this->verts.list[v9].color[2]);
      demo->ReadUnsignedChar(demo, &this->verts.list[v9].color[3]);
      ++v8;
      ++v9;
    }
    while ( v8 < i );
  }
  v10 = demo->__vftable;
  i = this->indexes.num;
  v10->ReadInt(demo, &i);
  v11 = i;
  v12 = i;
  if ( i > this->indexes.size )
  {
    if ( i > 0 )
    {
      v13 = i < this->indexes.num;
      list = this->indexes.list;
      this->indexes.size = i;
      if ( v13 )
        this->indexes.num = v11;
      this->indexes.list = (int *)Memory::Allocate(4 * v11);
      for ( k = 0; k < this->indexes.num; ++k )
        this->indexes.list[k] = list[k];
      if ( list )
        Memory::Free(list);
      v11 = i;
    }
    else
    {
      if ( this->indexes.list )
      {
        Memory::Free(this->indexes.list);
        v11 = i;
      }
      this->indexes.list = 0;
      this->indexes.num = 0;
      this->indexes.size = 0;
    }
  }
  v16 = 0;
  this->indexes.num = v12;
  if ( v11 > 0 )
  {
    do
      demo->ReadInt(demo, &this->indexes.list[v16++]);
    while ( v16 < i );
  }
  v17 = demo->__vftable;
  i = this->surfaces.num;
  v17->ReadInt(demo, &i);
  v18 = i;
  v13 = i <= this->surfaces.size;
  j = i;
  if ( !v13 )
  {
    if ( i > 0 )
    {
      v13 = i < this->surfaces.num;
      v19 = this->surfaces.list;
      demoa = (idDemoFile *)v19;
      this->surfaces.size = i;
      if ( v13 )
        this->surfaces.num = v18;
      v20 = (guiModelSurface_t *)Memory::Allocate(36 * v18);
      v21 = 0;
      v13 = this->surfaces.num <= 0;
      this->surfaces.list = v20;
      if ( !v13 )
      {
        v22 = 0;
        do
        {
          qmemcpy(&this->surfaces.list[v22], &v19[v22], sizeof(this->surfaces.list[v22]));
          v19 = (guiModelSurface_t *)demoa;
          ++v21;
          ++v22;
        }
        while ( v21 < this->surfaces.num );
      }
      if ( v19 )
        Memory::Free(v19);
      v18 = i;
    }
    else
    {
      if ( this->surfaces.list )
      {
        Memory::Free(this->surfaces.list);
        v18 = i;
      }
      this->surfaces.list = 0;
      this->surfaces.num = 0;
      this->surfaces.size = 0;
    }
  }
  this->surfaces.num = j;
  j = 0;
  if ( v18 > 0 )
  {
    demob = 0;
    do
    {
      v23 = (guiModelSurface_t *)((char *)demob + (unsigned int)this->surfaces.list);
      demo->ReadInt(demo, (int *)v23);
      demo->ReadFloat(demo, v23->color);
      demo->ReadFloat(demo, &v23->color[1]);
      demo->ReadFloat(demo, &v23->color[2]);
      demo->ReadFloat(demo, &v23->color[3]);
      demo->ReadInt(demo, &v23->firstVert);
      demo->ReadInt(demo, &v23->numVerts);
      demo->ReadInt(demo, &v23->firstIndex);
      demo->ReadInt(demo, &v23->numIndexes);
      v24 = declManager->__vftable;
      HashString = idDemoFile::ReadHashString(demo);
      demob = (idDemoFile *)((char *)demob + 36);
      v23->material = v24->FindMaterial(declManager, HashString, 1);
      ++j;
    }
    while ( j < i );
  }
}

// FUNC: public: void __thiscall idGuiModel::DrawStretchPic(class idDrawVert const *,int const *,int,int,class idMaterial const *,bool,float,float,float,float)
void __thiscall idGuiModel::DrawStretchPic(
        idGuiModel *this,
        const idDrawVert *dverts,
        const int *dindexes,
        int vertCount,
        int indexCount,
        const idMaterial *hShader,
        bool clip,
        float min_x,
        float min_y,
        float max_x,
        float max_y)
{
  const idDrawVert *v12; // eax
  int numPoints; // ecx
  double y; // st7
  double x; // st6
  double z; // st5
  idVec5 *v17; // eax
  float v18; // edx
  float v19; // ecx
  float v20; // edx
  float v21; // ecx
  int v22; // edx
  double v23; // st7
  double v24; // st6
  double v25; // st5
  float v26; // eax
  idVec5 *v27; // edx
  float v28; // ecx
  float v29; // eax
  float v30; // ecx
  float v31; // eax
  int v32; // ecx
  double v33; // st7
  double v34; // st6
  double v35; // st5
  idVec5 *v36; // eax
  float v37; // edx
  float v38; // ecx
  float v39; // edx
  float v40; // ecx
  idVec5 *v41; // edx
  int v42; // ecx
  int v43; // ebx
  bool v44; // cc
  idDrawVert *v45; // eax
  idDrawVert *v46; // edi
  int v47; // ebp
  int v48; // edi
  int v49; // edi
  int v50; // ecx
  int v51; // edx
  idDrawVert *list; // eax
  char *v53; // eax
  int v54; // ebx
  int granularity; // eax
  int i; // eax
  int num; // ebp
  int size; // eax
  int v59; // ecx
  int *v60; // edi
  int k; // eax
  bool v62; // zf
  int v63; // eax
  int m; // eax
  int v65; // ebp
  int v66; // eax
  int v67; // ecx
  int *v68; // edi
  int n; // eax
  int v70; // ebp
  int v71; // eax
  int ii; // eax
  int v73; // ebx
  int v74; // eax
  int v75; // ecx
  int *v76; // edi
  int jj; // eax
  int v78; // edi
  idDrawVert *v79; // ebp
  idDrawVert *v80; // eax
  idDrawVert *v81; // ebx
  int v82; // ebx
  int v83; // edi
  int v84; // ecx
  int *v85; // edi
  int kk; // eax
  int v87; // edi
  int v88; // eax
  int v89; // ecx
  idDrawVert *j; // [esp+18h] [ebp-578h]
  int ja; // [esp+18h] [ebp-578h]
  int jb; // [esp+18h] [ebp-578h]
  int numIndexes; // [esp+1Ch] [ebp-574h]
  int numIndexesa; // [esp+1Ch] [ebp-574h]
  int numVerts; // [esp+20h] [ebp-570h]
  idPlane p; // [esp+24h] [ebp-56Ch] BYREF
  int v97; // [esp+34h] [ebp-55Ch]
  float v98; // [esp+38h] [ebp-558h]
  float v99; // [esp+3Ch] [ebp-554h]
  float v100; // [esp+40h] [ebp-550h]
  float v101; // [esp+44h] [ebp-54Ch]
  float v102; // [esp+48h] [ebp-548h]
  float v103; // [esp+4Ch] [ebp-544h]
  float v104; // [esp+50h] [ebp-540h]
  float v105; // [esp+54h] [ebp-53Ch]
  float v106; // [esp+58h] [ebp-538h]
  float v107; // [esp+5Ch] [ebp-534h]
  float v108; // [esp+60h] [ebp-530h]
  float v109; // [esp+64h] [ebp-52Ch]
  float v110; // [esp+68h] [ebp-528h]
  float v111; // [esp+6Ch] [ebp-524h]
  float v112; // [esp+70h] [ebp-520h]
  idFixedWinding w; // [esp+74h] [ebp-51Ch] BYREF
  int v114; // [esp+58Ch] [ebp-4h]

  if ( glConfig.isInitialized && dverts && dindexes && vertCount && indexCount && hShader )
  {
    if ( hShader != this->surf->material )
    {
      if ( this->surf->numVerts )
        idGuiModel::AdvanceSurf(this);
      if ( !com_SingleDeclFile.internalVar->integerValue )
        hShader->base->EnsureNotPurged(hShader->base);
      this->surf->material = hShader;
    }
    if ( this->surf->numVerts > 12800 )
      idGuiModel::AdvanceSurf(this);
    if ( clip )
    {
      w.__vftable = (idFixedWinding_vtbl *)&idFixedWinding::`vftable';
      w.numPoints = 0;
      w.p = w.data;
      w.allocedSize = 64;
      v114 = 0;
      numIndexes = 0;
      if ( indexCount > 0 )
      {
        while ( 1 )
        {
          v12 = &dverts[dindexes[numIndexes]];
          numPoints = 0;
          w.numPoints = 0;
          y = v12->st.y;
          x = v12->st.x;
          z = v12->xyz.z;
          v108 = v12->xyz.x;
          v109 = v12->xyz.y;
          v110 = z;
          v111 = x;
          v112 = y;
          if ( w.allocedSize >= 1 )
            goto LABEL_20;
          if ( w.ReAllocate(&w, 1, 1) )
            break;
LABEL_21:
          v22 = dindexes[numIndexes + 1] << 6;
          v23 = *(float *)((char *)&dverts->st.y + v22);
          v24 = *(float *)((char *)&dverts->st.x + v22);
          v25 = *(float *)((char *)&dverts->xyz.z + v22);
          v26 = *(float *)((char *)&dverts->xyz.x + v22);
          v99 = *(float *)((char *)&dverts->xyz.y + v22);
          v98 = v26;
          v100 = v25;
          v101 = v24;
          v102 = v23;
          if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
          {
            v27 = &w.p[w.numPoints];
            v28 = v99;
            v27->x = v98;
            v29 = v100;
            v27->y = v28;
            v30 = v101;
            v27->z = v29;
            v31 = v102;
            v27->s = v30;
            v27->t = v31;
            ++w.numPoints;
          }
          v32 = dindexes[numIndexes + 2] << 6;
          v33 = *(float *)((char *)&dverts->st.y + v32);
          v34 = *(float *)((char *)&dverts->st.x + v32);
          v35 = *(float *)((char *)&dverts->xyz.z + v32);
          v103 = *(float *)((char *)&dverts->xyz.x + v32);
          v104 = *(float *)((char *)&dverts->xyz.y + v32);
          v105 = v35;
          v106 = v34;
          v107 = v33;
          if ( w.numPoints + 1 <= w.allocedSize || w.ReAllocate(&w, w.numPoints + 1, 1) )
          {
            v36 = &w.p[w.numPoints];
            v37 = v104;
            v36->x = v103;
            v38 = v105;
            v36->y = v37;
            v39 = v106;
            v36->z = v38;
            v40 = v107;
            v36->s = v39;
            v36->t = v40;
            ++w.numPoints;
          }
          v41 = w.p;
          v42 = 0;
          while ( v41->x >= (double)min_x
               && v41->x <= (double)max_x
               && v41->y >= (double)min_y
               && v41->y <= (double)max_y )
          {
            ++v42;
            ++v41;
            if ( v42 >= 3 )
              goto LABEL_35;
          }
          p.d = -min_x;
          p.c = 0.0;
          p.b = 0.0;
          p.a = 1.0;
          idWinding::ClipInPlace(&w, &p, 0.1, 0);
          p.c = 0.0;
          p.b = 0.0;
          p.a = -1.0;
          p.d = max_x;
          idWinding::ClipInPlace(&w, &p, 0.1, 0);
          p.d = -min_y;
          p.c = 0.0;
          p.a = 0.0;
          p.b = 1.0;
          idWinding::ClipInPlace(&w, &p, 0.1, 0);
          p.c = 0.0;
          p.a = 0.0;
          p.b = -1.0;
          p.d = max_y;
          idWinding::ClipInPlace(&w, &p, 0.1, 0);
LABEL_35:
          v43 = w.numPoints + this->verts.num;
          numVerts = this->verts.num;
          if ( v43 > this->verts.size )
          {
            if ( v43 > 0 )
            {
              v44 = v43 < this->verts.num;
              j = this->verts.list;
              this->verts.size = v43;
              if ( v44 )
                this->verts.num = v43;
              v45 = (idDrawVert *)Memory::Allocate(v43 << 6);
              v46 = v45;
              v97 = (int)v45;
              LOBYTE(v114) = 1;
              if ( v45 )
                `vector constructor iterator'(v45, 0x40u, v43, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
              else
                v46 = 0;
              v47 = 0;
              v44 = this->verts.num <= 0;
              LOBYTE(v114) = 0;
              this->verts.list = v46;
              if ( !v44 )
              {
                v48 = 0;
                do
                {
                  idDrawVert::operator=(&this->verts.list[v48].xyz.x, (int)&j[v48]);
                  ++v47;
                  ++v48;
                }
                while ( v47 < this->verts.num );
              }
              if ( j )
                Memory::Free(j);
            }
            else
            {
              if ( this->verts.list )
                Memory::Free(this->verts.list);
              this->verts.list = 0;
              this->verts.num = 0;
              this->verts.size = 0;
            }
          }
          v49 = 0;
          v44 = w.numPoints <= 0;
          this->verts.num = v43;
          if ( !v44 )
          {
            v50 = 0;
            v51 = numVerts << 6;
            do
            {
              list = this->verts.list;
              *(float *)((char *)&list->xyz.x + v51) = w.p[v50].x;
              v53 = (char *)list + v51;
              *((_DWORD *)v53 + 1) = LODWORD(w.p[v50].y);
              *((_DWORD *)v53 + 2) = LODWORD(w.p[v50].z);
              *((_DWORD *)v53 + 14) = LODWORD(w.p[v50].s);
              *((_DWORD *)v53 + 15) = LODWORD(w.p[v50].t);
              *((_DWORD *)v53 + 4) = 0;
              *((_DWORD *)v53 + 5) = 0;
              *((_DWORD *)v53 + 6) = 1065353216;
              *((_DWORD *)v53 + 8) = 1065353216;
              *((_DWORD *)v53 + 9) = 0;
              *((_DWORD *)v53 + 10) = 0;
              ++v49;
              *((_DWORD *)v53 + 11) = 0;
              *((_DWORD *)v53 + 12) = 1065353216;
              *((_DWORD *)v53 + 13) = 0;
              v51 += 64;
              ++v50;
            }
            while ( v49 < w.numPoints );
          }
          this->surf->numVerts += w.numPoints;
          for ( ja = 2; ja < w.numPoints; ++ja )
          {
            v54 = numVerts - this->surf->firstVert;
            if ( !this->indexes.list )
            {
              granularity = this->indexes.granularity;
              if ( granularity > 0 )
              {
                if ( granularity != this->indexes.size )
                {
                  v44 = granularity < this->indexes.num;
                  this->indexes.size = granularity;
                  if ( v44 )
                    this->indexes.num = granularity;
                  this->indexes.list = (int *)Memory::Allocate(4 * granularity);
                  for ( i = 0; i < this->indexes.num; ++i )
                    this->indexes.list[i] = *(_DWORD *)(4 * i);
                }
              }
              else
              {
                this->indexes.list = 0;
                this->indexes.num = 0;
                this->indexes.size = 0;
              }
            }
            num = this->indexes.num;
            size = this->indexes.size;
            if ( num == size )
            {
              if ( !this->indexes.granularity )
                this->indexes.granularity = 16;
              v59 = size + this->indexes.granularity - (size + this->indexes.granularity) % this->indexes.granularity;
              if ( v59 > 0 )
              {
                if ( v59 != this->indexes.size )
                {
                  v60 = this->indexes.list;
                  this->indexes.size = v59;
                  if ( v59 < num )
                    this->indexes.num = v59;
                  this->indexes.list = (int *)Memory::Allocate(4 * v59);
                  for ( k = 0; k < this->indexes.num; ++k )
                    this->indexes.list[k] = v60[k];
                  if ( v60 )
                    Memory::Free(v60);
                }
              }
              else
              {
                if ( this->indexes.list )
                  Memory::Free(this->indexes.list);
                this->indexes.list = 0;
                this->indexes.num = 0;
                this->indexes.size = 0;
              }
            }
            this->indexes.list[this->indexes.num++] = v54;
            v62 = this->indexes.list == 0;
            v97 = numVerts - this->surf->firstVert + ja - 1;
            if ( v62 )
            {
              v63 = this->indexes.granularity;
              if ( v63 > 0 )
              {
                if ( v63 != this->indexes.size )
                {
                  v44 = v63 < this->indexes.num;
                  this->indexes.size = v63;
                  if ( v44 )
                    this->indexes.num = v63;
                  this->indexes.list = (int *)Memory::Allocate(4 * v63);
                  for ( m = 0; m < this->indexes.num; ++m )
                    this->indexes.list[m] = *(_DWORD *)(4 * m);
                }
              }
              else
              {
                this->indexes.list = 0;
                this->indexes.num = 0;
                this->indexes.size = 0;
              }
            }
            v65 = this->indexes.num;
            v66 = this->indexes.size;
            if ( v65 == v66 )
            {
              if ( !this->indexes.granularity )
                this->indexes.granularity = 16;
              v67 = v66 + this->indexes.granularity - (v66 + this->indexes.granularity) % this->indexes.granularity;
              if ( v67 > 0 )
              {
                if ( v67 != this->indexes.size )
                {
                  v68 = this->indexes.list;
                  this->indexes.size = v67;
                  if ( v67 < v65 )
                    this->indexes.num = v67;
                  this->indexes.list = (int *)Memory::Allocate(4 * v67);
                  for ( n = 0; n < this->indexes.num; ++n )
                    this->indexes.list[n] = v68[n];
                  if ( v68 )
                    Memory::Free(v68);
                }
              }
              else
              {
                if ( this->indexes.list )
                  Memory::Free(this->indexes.list);
                this->indexes.list = 0;
                this->indexes.num = 0;
                this->indexes.size = 0;
              }
            }
            this->indexes.list[this->indexes.num++] = v97;
            v70 = ja + numVerts - this->surf->firstVert;
            if ( !this->indexes.list )
            {
              v71 = this->indexes.granularity;
              if ( v71 > 0 )
              {
                if ( v71 != this->indexes.size )
                {
                  v44 = v71 < this->indexes.num;
                  this->indexes.size = v71;
                  if ( v44 )
                    this->indexes.num = v71;
                  this->indexes.list = (int *)Memory::Allocate(4 * v71);
                  for ( ii = 0; ii < this->indexes.num; ++ii )
                    this->indexes.list[ii] = *(_DWORD *)(4 * ii);
                }
              }
              else
              {
                this->indexes.list = 0;
                this->indexes.num = 0;
                this->indexes.size = 0;
              }
            }
            v73 = this->indexes.num;
            v74 = this->indexes.size;
            if ( v73 == v74 )
            {
              if ( !this->indexes.granularity )
                this->indexes.granularity = 16;
              v75 = v74 + this->indexes.granularity - (v74 + this->indexes.granularity) % this->indexes.granularity;
              if ( v75 > 0 )
              {
                if ( v75 != this->indexes.size )
                {
                  v76 = this->indexes.list;
                  this->indexes.size = v75;
                  if ( v75 < v73 )
                    this->indexes.num = v75;
                  this->indexes.list = (int *)Memory::Allocate(4 * v75);
                  for ( jj = 0; jj < this->indexes.num; ++jj )
                    this->indexes.list[jj] = v76[jj];
                  if ( v76 )
                    Memory::Free(v76);
                }
              }
              else
              {
                if ( this->indexes.list )
                  Memory::Free(this->indexes.list);
                this->indexes.list = 0;
                this->indexes.num = 0;
                this->indexes.size = 0;
              }
            }
            this->indexes.list[this->indexes.num++] = v70;
            this->surf->numIndexes += 3;
          }
          numIndexes += 3;
          if ( numIndexes >= indexCount )
            goto LABEL_122;
        }
        numPoints = w.numPoints;
LABEL_20:
        v17 = &w.p[numPoints];
        v18 = v109;
        v17->x = v108;
        v19 = v110;
        v17->y = v18;
        v20 = v111;
        v17->z = v19;
        v21 = v112;
        v17->s = v20;
        v17->t = v21;
        ++w.numPoints;
        goto LABEL_21;
      }
LABEL_122:
      v114 = -1;
      w.p = 0;
      w.__vftable = (idFixedWinding_vtbl *)&idWinding::`vftable';
      Memory::Free(0);
    }
    else
    {
      jb = this->verts.num;
      v44 = vertCount + jb <= this->verts.size;
      numIndexesa = this->indexes.num;
      v97 = vertCount + jb;
      if ( !v44 )
      {
        if ( !this->verts.granularity )
          this->verts.granularity = 16;
        v78 = vertCount
            + jb
            + this->verts.granularity
            - 1
            - (vertCount + jb + this->verts.granularity - 1) % this->verts.granularity;
        if ( v78 > 0 )
        {
          if ( v78 != this->verts.size )
          {
            v44 = v78 < this->verts.num;
            v79 = this->verts.list;
            this->verts.size = v78;
            if ( v44 )
              this->verts.num = v78;
            v80 = (idDrawVert *)Memory::Allocate(v78 << 6);
            v81 = v80;
            v114 = 2;
            if ( v80 )
              `vector constructor iterator'(v80, 0x40u, v78, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
            else
              v81 = 0;
            this->verts.list = v81;
            v82 = 0;
            v44 = this->verts.num <= 0;
            v114 = -1;
            if ( !v44 )
            {
              v83 = 0;
              do
              {
                idDrawVert::operator=(&this->verts.list[v83].xyz.x, (int)&v79[v83]);
                ++v82;
                ++v83;
              }
              while ( v82 < this->verts.num );
            }
            if ( v79 )
              Memory::Free(v79);
          }
        }
        else
        {
          if ( this->verts.list )
            Memory::Free(this->verts.list);
          this->verts.list = 0;
          this->verts.num = 0;
          this->verts.size = 0;
        }
      }
      this->verts.num = v97;
      if ( indexCount + numIndexesa > this->indexes.size )
      {
        if ( !this->indexes.granularity )
          this->indexes.granularity = 16;
        v84 = indexCount
            + numIndexesa
            + this->indexes.granularity
            - 1
            - (indexCount + numIndexesa + this->indexes.granularity - 1) % this->indexes.granularity;
        if ( v84 > 0 )
        {
          if ( v84 != this->indexes.size )
          {
            v44 = v84 < this->indexes.num;
            v85 = this->indexes.list;
            this->indexes.size = v84;
            if ( v44 )
              this->indexes.num = v84;
            this->indexes.list = (int *)Memory::Allocate(4 * v84);
            for ( kk = 0; kk < this->indexes.num; ++kk )
              this->indexes.list[kk] = v85[kk];
            if ( v85 )
              Memory::Free(v85);
          }
        }
        else
        {
          if ( this->indexes.list )
            Memory::Free(this->indexes.list);
          this->indexes.list = 0;
          this->indexes.num = 0;
          this->indexes.size = 0;
        }
      }
      v87 = vertCount;
      this->indexes.num = indexCount + numIndexesa;
      this->surf->numVerts += vertCount;
      this->surf->numIndexes += indexCount;
      v88 = 0;
      if ( indexCount > 0 )
      {
        v89 = numIndexesa;
        do
          this->indexes.list[v89++] = jb + dindexes[v88++] - this->surf->firstVert;
        while ( v88 < indexCount );
        v87 = vertCount;
      }
      ((void (__stdcall *)(const idDrawVert *, int))SIMDProcessor->Memcpy)(dverts, v87 << 6);
    }
  }
}

// FUNC: public: void __thiscall idGuiModel::DrawStretchPic(float,float,float,float,float,float,float,float,class idMaterial const *)
void __thiscall idGuiModel::DrawStretchPic(
        idGuiModel *this,
        float x,
        float y,
        float w,
        float h,
        int s1,
        int t1,
        int s2,
        int t2,
        const idMaterial *hShader)
{
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st6
  double v14; // st6

  if ( glConfig.isInitialized && hShader )
  {
    if ( x < 0.0 )
    {
      *(float *)&s1 = *(float *)&s1 - (*(float *)&s2 - *(float *)&s1) / w * x;
      v10 = x;
      x = 0.0;
      w = v10 + w;
    }
    if ( y >= 0.0 )
    {
      v12 = h;
    }
    else
    {
      *(float *)&t1 = *(float *)&t1 - (*(float *)&t2 - *(float *)&t1) / h * y;
      v11 = y;
      y = 0.0;
      v12 = v11 + h;
    }
    v13 = x + w;
    if ( v13 > 640.0 )
    {
      *(float *)&s2 = *(float *)&s2 - (v13 - 640.0) / w * (*(float *)&s2 - *(float *)&s1);
      w = 640.0 - x;
    }
    v14 = y + v12;
    if ( v14 > 480.0 )
    {
      *(float *)&t2 = *(float *)&t2 - (v14 - 480.0) / v12 * (*(float *)&t2 - *(float *)&t1);
      v12 = 480.0 - y;
    }
    if ( w > 0.0 && v12 > 0.0 )
    {
      rectVerts[0].xyz.x = x;
      dword_103DE774 = LODWORD(y);
      flt_103DE7B0 = x + w;
      dword_103DE7A8 = s1;
      flt_103DE7F0 = flt_103DE7B0;
      dword_103DE7AC = t1;
      dword_103DE7B4 = LODWORD(y);
      flt_103DE7F4 = v12 + y;
      flt_103DE834 = flt_103DE7F4;
      dword_103DE7E8 = s2;
      dword_103DE7EC = t1;
      dword_103DE828 = s2;
      dword_103DE82C = t2;
      dword_103DE830 = LODWORD(x);
      dword_103DE868 = s1;
      dword_103DE778 = 0;
      dword_103DE7B8 = 0;
      dword_103DE7F8 = 0;
      dword_103DE838 = 0;
      dword_103DE86C = t2;
      idGuiModel::DrawStretchPic(this, rectVerts, rectIndexes, 4, 6, hShader, 0, 0.0, 0.0, 640.0, 480.0);
    }
  }
}

// FUNC: public: void __thiscall idGuiModel::DrawStretchTri(class idVec2,class idVec2,class idVec2,class idVec2,class idVec2,class idVec2,class idMaterial const *)
void __thiscall idGuiModel::DrawStretchTri(
        idGuiModel *this,
        idVec2 p1,
        idVec2 p2,
        idVec2 p3,
        idVec2 t1,
        idVec2 t2,
        idVec2 t3,
        const idMaterial *material)
{
  guiModelSurface_t *surf; // eax
  bool v10; // zf
  int num; // ebx
  int v12; // edi
  int v13; // ecx
  bool v14; // cc
  int *list; // esi
  int i; // eax
  idDrawVert tempVerts[3]; // [esp+Ch] [ebp-C0h] BYREF

  if ( glConfig.isInitialized && material )
  {
    tempVerts[0].xyz.x = p1.x;
    tempVerts[0].st = t1;
    tempVerts[0].xyz.y = p1.y;
    tempVerts[1].st.x = t2.x;
    tempVerts[1].xyz.x = p2.x;
    tempVerts[1].xyz.y = p2.y;
    tempVerts[2].xyz.y = p3.y;
    surf = this->surf;
    v10 = material == this->surf->material;
    tempVerts[1].st.y = t2.y;
    tempVerts[2].xyz.x = p3.x;
    tempVerts[0].xyz.z = 0.0;
    tempVerts[0].normal.x = 0.0;
    tempVerts[0].normal.y = 0.0;
    tempVerts[0].normal.z = 1.0;
    tempVerts[0].tangents[0].x = 1.0;
    tempVerts[0].tangents[0].y = 0.0;
    tempVerts[0].tangents[0].z = 0.0;
    tempVerts[0].tangents[1].x = 0.0;
    tempVerts[0].tangents[1].y = 1.0;
    tempVerts[0].tangents[1].z = 0.0;
    tempVerts[1].xyz.z = 0.0;
    tempVerts[1].normal.x = 0.0;
    tempVerts[1].normal.y = 0.0;
    tempVerts[1].normal.z = 1.0;
    tempVerts[1].tangents[0].x = 1.0;
    tempVerts[1].tangents[0].y = 0.0;
    tempVerts[1].tangents[0].z = 0.0;
    tempVerts[1].tangents[1].x = 0.0;
    tempVerts[1].tangents[1].y = 1.0;
    tempVerts[1].tangents[1].z = 0.0;
    tempVerts[2].xyz.z = 0.0;
    tempVerts[2].st = t3;
    tempVerts[2].normal.x = 0.0;
    tempVerts[2].normal.y = 0.0;
    tempVerts[2].normal.z = 1.0;
    tempVerts[2].tangents[0].x = 1.0;
    tempVerts[2].tangents[0].y = 0.0;
    tempVerts[2].tangents[0].z = 0.0;
    tempVerts[2].tangents[1].x = 0.0;
    tempVerts[2].tangents[1].y = 1.0;
    tempVerts[2].tangents[1].z = 0.0;
    if ( !v10 )
    {
      if ( surf->numVerts )
        idGuiModel::AdvanceSurf(this);
      material->base->EnsureNotPurged(material->base);
      this->surf->material = material;
    }
    num = this->indexes.num;
    v12 = this->verts.num;
    if ( v12 + 3 > this->verts.size )
    {
      if ( !this->verts.granularity )
        this->verts.granularity = 16;
      idList<idDrawVert>::Resize(
        &this->verts,
        v12 + 3 + this->verts.granularity - 1 - (v12 + 3 + this->verts.granularity - 1) % this->verts.granularity);
    }
    this->verts.num = v12 + 3;
    if ( num + 3 > this->indexes.size )
    {
      if ( !this->indexes.granularity )
        this->indexes.granularity = 16;
      v13 = num
          + 3
          + this->indexes.granularity
          - 1
          - (num + 3 + this->indexes.granularity - 1) % this->indexes.granularity;
      if ( v13 > 0 )
      {
        if ( v13 != this->indexes.size )
        {
          v14 = v13 < this->indexes.num;
          list = this->indexes.list;
          this->indexes.size = v13;
          if ( v14 )
            this->indexes.num = v13;
          this->indexes.list = (int *)Memory::Allocate(4 * v13);
          for ( i = 0; i < this->indexes.num; ++i )
            this->indexes.list[i] = list[i];
          if ( list )
            Memory::Free(list);
        }
      }
      else
      {
        if ( this->indexes.list )
          Memory::Free(this->indexes.list);
        this->indexes.list = 0;
        this->indexes.num = 0;
        this->indexes.size = 0;
      }
    }
    this->indexes.num = num + 3;
    this->surf->numVerts += 3;
    this->surf->numIndexes += 3;
    this->indexes.list[num] = v12 - this->surf->firstVert + 1;
    this->indexes.list[num + 1] = v12 - this->surf->firstVert;
    this->indexes.list[num + 2] = v12 - this->surf->firstVert + 2;
    qmemcpy(&this->verts.list[v12], tempVerts, 0xC0u);
  }
}
