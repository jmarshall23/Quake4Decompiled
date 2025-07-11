
// FUNC: private: void __thiscall idRenderModelLiquid::WaterDrop(int,int,float *)
void __thiscall idRenderModelLiquid::WaterDrop(idRenderModelLiquid *this, int x, int y, float *page)
{
  int drop_radius; // eax
  int v5; // ebx
  int v6; // esi
  int v7; // edx
  int v8; // eax
  int v9; // ebp
  int v10; // esi
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int verts_x; // edi
  int verts_y; // edi
  int i; // esi
  int v18; // edx
  int j; // edi
  float *v20; // eax
  int top; // [esp+4h] [ebp-14h]
  int left; // [esp+8h] [ebp-10h]
  int radsquare; // [esp+Ch] [ebp-Ch]
  float invlength; // [esp+14h] [ebp-4h]
  int xa; // [esp+1Ch] [ebp+4h]
  int right; // [esp+20h] [ebp+8h]

  drop_radius = this->drop_radius;
  radsquare = drop_radius * drop_radius;
  v5 = x;
  invlength = 1.0 / (double)(drop_radius * drop_radius);
  if ( x < 0 )
  {
    v6 = this->verts_x - 2 * drop_radius - 1;
    if ( this->verts_x - 2 * drop_radius == 1 )
    {
      v7 = 0;
    }
    else
    {
      v8 = 69069 * this->random.seed + 1;
      this->random.seed = v8;
      v7 = (v8 & 0x7FFF) % v6;
    }
    v5 = v7 + this->drop_radius + 1;
  }
  v9 = y;
  if ( y < 0 )
  {
    v10 = this->verts_y - 2 * this->drop_radius - 1;
    if ( this->verts_y - 2 * this->drop_radius == 1 )
    {
      v11 = 0;
    }
    else
    {
      v12 = 69069 * this->random.seed + 1;
      this->random.seed = v12;
      v11 = (v12 & 0x7FFF) % v10;
    }
    v9 = v11 + this->drop_radius + 1;
  }
  v13 = this->drop_radius;
  left = -v13;
  xa = v13;
  top = -v13;
  right = v13;
  if ( v5 - v13 < 1 )
    left = v13 - v5 - this->drop_radius + 1;
  v14 = this->drop_radius;
  if ( v9 - v14 < 1 )
    top = v14 - v9 - this->drop_radius + 1;
  verts_x = this->verts_x;
  if ( v14 + v5 > verts_x - 1 )
    xa = xa + verts_x - v14 - v5 - 1;
  verts_y = this->verts_y;
  if ( v14 + v9 > verts_y - 1 )
    right = right + verts_y - v14 - v9 - 1;
  for ( i = top; i < right; ++i )
  {
    v18 = left;
    if ( left < xa )
    {
      for ( j = i * i; ; j = i * i )
      {
        if ( j + v18 * v18 < radsquare )
        {
          v20 = &page[v5 + v18 + this->verts_x * (i + v9)];
          *v20 = cos(sqrt((double)(j + v18 * v18) * invlength) * 3.1415927 * 0.5) * this->drop_height + *v20;
        }
        if ( ++v18 >= xa )
          break;
      }
    }
  }
}

// FUNC: private: void __thiscall idRenderModelLiquid::Update(void)
void __thiscall idRenderModelLiquid::Update(idRenderModelLiquid *this)
{
  float *page1; // eax
  double time; // st7
  int liquid_type; // edx
  float *page2; // eax
  float *v5; // esi
  int v6; // edx
  int verts_x; // edi
  int v8; // edx
  float *v9; // edi
  int v10; // ebp
  int v11; // ebx
  int v12; // ebp
  double v13; // st7
  int v14; // edi
  int v15; // edx
  float *v16; // ebp
  int v17; // ebx
  int v18; // edi
  int v19; // ebx
  double v20; // st7
  int v21; // edi
  int v22; // edx
  float *v23; // edi
  int v24; // ebp
  int v25; // ebx
  int v26; // ebp
  double v27; // st7
  int y; // [esp+0h] [ebp-8h]
  int ya; // [esp+0h] [ebp-8h]
  int yb; // [esp+0h] [ebp-8h]

  this->time += this->update_tics;
  page1 = this->page1;
  this->page1 = this->page2;
  this->page2 = page1;
  if ( this->time <= this->nextDropTime )
  {
    time = (double)this->time;
    if ( time < (double)this->nextDropTime - this->drop_delay )
      this->nextDropTime = (int)(time + this->drop_delay);
  }
  else
  {
    idRenderModelLiquid::WaterDrop(this, -1, -1, this->page2);
    this->nextDropTime = (int)((double)this->time + this->drop_delay);
  }
  liquid_type = this->liquid_type;
  page2 = this->page2;
  v5 = this->page1;
  if ( liquid_type )
  {
    v6 = liquid_type - 1;
    if ( v6 )
    {
      if ( v6 == 1 )
      {
        for ( y = 1; y < this->verts_y - 1; ++y )
        {
          verts_x = this->verts_x;
          page2 += verts_x;
          v5 += verts_x;
          v8 = 1;
          if ( verts_x - 1 > 1 )
          {
            v9 = page2 + 2;
            do
            {
              v10 = this->verts_x;
              v11 = v8 - v10;
              v12 = v8 + v10;
              v13 = *(v9 - 2) + *(v9 - 1) + page2[v12 - 1];
              v5[v8++] = (v13 + page2[v12 + 1] + page2[v11 - 1] + page2[v11 + 1] + page2[v12] + page2[v11] + *v9++)
                       * 0.11111111
                       * this->density;
            }
            while ( v8 < this->verts_x - 1 );
          }
        }
      }
    }
    else
    {
      for ( ya = 1; ya < this->verts_y - 1; ++ya )
      {
        v14 = this->verts_x;
        page2 += v14;
        v5 += v14;
        v15 = 1;
        if ( v14 - 1 > 1 )
        {
          v16 = page2 + 2;
          do
          {
            v17 = this->verts_x;
            v18 = v15 - v17;
            v19 = v15 + v17;
            v20 = *(v16 - 2) + page2[v19 - 1];
            ++v15;
            v5[v15 - 1] = ((v20 + page2[v19 + 1] + page2[v18 - 1] + page2[v18 + 1] + page2[v19] + *v16++ + page2[v18])
                         * 0.25
                         - v5[v15 - 1])
                        * this->density;
          }
          while ( v15 < this->verts_x - 1 );
        }
      }
    }
  }
  else
  {
    for ( yb = 1; yb < this->verts_y - 1; ++yb )
    {
      v21 = this->verts_x;
      page2 += v21;
      v5 += v21;
      v22 = 1;
      if ( v21 - 1 > 1 )
      {
        v23 = page2 + 2;
        do
        {
          v24 = this->verts_x;
          v25 = v22 - v24;
          v26 = v22 + v24;
          v27 = *(v23 - 2) + *(v23 - 1) + page2[v26 - 1];
          ++v22;
          v5[v22 - 1] = ((v27 + page2[v26 + 1] + page2[v25 - 1] + page2[v25 + 1] + *v23++ + page2[v26] + page2[v25])
                       * 0.22222222
                       - v5[v22 - 1])
                      * this->density;
        }
        while ( v22 < this->verts_x - 1 );
      }
    }
  }
}

// FUNC: public: virtual void __thiscall idRenderModelLiquid::Reset(void)
void __thiscall idRenderModelLiquid::Reset(idRenderModelLiquid *this)
{
  int verts_y; // esi
  int v2; // edx
  float *list; // eax
  float *v4; // edx
  int v5; // eax
  int v6; // ebx
  int v7; // esi
  int v8; // edx

  verts_y = this->verts_y;
  v2 = verts_y * this->verts_x;
  if ( this->pages.num >= 2 * v2 )
  {
    this->random.seed = this->seed;
    list = this->pages.list;
    v4 = &list[v2];
    this->page1 = list;
    v5 = 0;
    v6 = 0;
    this->nextDropTime = 0;
    this->time = 0;
    this->page2 = v4;
    if ( verts_y > 0 )
    {
      do
      {
        v7 = 0;
        if ( this->verts_x > 0 )
        {
          v8 = v5 << 6;
          do
          {
            this->page1[v5] = 0.0;
            this->page2[v5] = 0.0;
            *(float *)((char *)&this->verts.list->xyz.z + v8) = 0.0;
            ++v7;
            ++v5;
            v8 += 64;
          }
          while ( v7 < this->verts_x );
        }
        ++v6;
      }
      while ( v6 < this->verts_y );
    }
  }
}

// FUNC: public: __thiscall idRenderModelLiquid::idRenderModelLiquid(void)
void __thiscall idRenderModelLiquid::idRenderModelLiquid(idRenderModelLiquid *this)
{
  const idMaterial *v2; // eax

  idRenderModelStatic::idRenderModelStatic(this);
  this->__vftable = (idRenderModelLiquid_vtbl *)&idRenderModelLiquid::`vftable';
  this->random.seed = 0;
  this->pages.granularity = 16;
  this->pages.list = 0;
  this->pages.num = 0;
  this->pages.size = 0;
  this->verts.granularity = 16;
  this->verts.list = 0;
  this->verts.num = 0;
  this->verts.size = 0;
  this->verts_x = 32;
  this->verts_y = 32;
  this->scale_x = 256.0;
  this->scale_y = 256.0;
  this->liquid_type = 0;
  this->density = 0.97000003;
  this->drop_height = 4.0;
  this->drop_radius = 4;
  this->drop_delay = 1000.0;
  v2 = declManager->FindMaterial(declManager, 0, 1);
  this->time = 0;
  this->seed = 0;
  this->random.seed = 0;
  this->shader = v2;
  this->update_tics = 33;
}

// FUNC: private: struct modelSurface_s __thiscall idRenderModelLiquid::GenerateSurface(float)
modelSurface_s *__thiscall idRenderModelLiquid::GenerateSurface(
        idRenderModelLiquid *this,
        modelSurface_s *result,
        float lerp)
{
  idDrawVert *list; // ecx
  int v5; // eax
  float *p_z; // ecx
  double v7; // st7
  srfTriangles_s *v8; // edi
  deformInfo_s *deformInfo; // eax
  int v10; // ebx
  int v11; // ebp
  const idMaterial *shader; // esi
  modelSurface_s *v13; // eax
  int numOutputVerts; // [esp-Ch] [ebp-24h]
  float inv_lerp; // [esp+4h] [ebp-14h]
  int surf; // [esp+8h] [ebp-10h]
  idStr *surf_12; // [esp+14h] [ebp-4h]

  list = this->verts.list;
  v5 = 0;
  if ( this->verts.num > 0 )
  {
    p_z = &list->xyz.z;
    do
    {
      inv_lerp = 1.0 - lerp;
      v7 = inv_lerp * this->page2[v5++];
      p_z += 16;
      *(p_z - 16) = v7 + lerp * this->page1[v5 - 1];
    }
    while ( v5 < this->verts.num );
  }
  ++tr.pc.c_deformedSurfaces;
  tr.pc.c_deformedVerts += this->deformInfo->numOutputVerts;
  tr.pc.c_deformedIndexes += this->deformInfo->numIndexes;
  v8 = R_AllocStaticTriSurf();
  v8->deformedSurface = 1;
  v8->numIndexes = this->deformInfo->numIndexes;
  v8->indexes = this->deformInfo->indexes;
  v8->silIndexes = this->deformInfo->silIndexes;
  v8->numMirroredVerts = this->deformInfo->numMirroredVerts;
  v8->mirroredVerts = this->deformInfo->mirroredVerts;
  v8->numDupVerts = this->deformInfo->numDupVerts;
  v8->dupVerts = this->deformInfo->dupVerts;
  v8->numSilEdges = this->deformInfo->numSilEdges;
  v8->silEdges = this->deformInfo->silEdges;
  v8->dominantTris = this->deformInfo->dominantTris;
  numOutputVerts = this->deformInfo->numOutputVerts;
  v8->numVerts = numOutputVerts;
  R_AllocStaticTriSurfVerts(v8, numOutputVerts);
  SIMDProcessor->Memcpy(SIMDProcessor, v8->verts, this->verts.list, this->deformInfo->numSourceVerts << 6);
  deformInfo = this->deformInfo;
  v10 = 0;
  if ( deformInfo->numMirroredVerts > 0 )
  {
    v11 = (deformInfo->numOutputVerts - deformInfo->numMirroredVerts) << 6;
    do
    {
      idDrawVert::operator=((float *)((char *)&v8->verts->xyz.x + v11), (int)&v8->verts[deformInfo->mirroredVerts[v10]]);
      deformInfo = this->deformInfo;
      ++v10;
      v11 += 64;
    }
    while ( v10 < deformInfo->numMirroredVerts );
  }
  R_BoundTriSurf(v8);
  if ( !r_useDeferredTangents.internalVar->integerValue )
    R_DeriveTangents(v8, 1);
  shader = this->shader;
  v13 = result;
  result->id = surf;
  result->shader = shader;
  result->geometry = v8;
  result->mOriginalSurfaceName = surf_12;
  return v13;
}

// FUNC: public: virtual class idRenderModel * __thiscall idRenderModelLiquid::InstantiateDynamicModel(struct renderEntity_s const *,struct viewDef_s const *,class idRenderModel *,unsigned int)
idBounds *__thiscall idRenderModelLiquid::InstantiateDynamicModel(
        idRenderModelLiquid *this,
        const renderEntity_s *ent,
        const viewDef_s *view,
        idRenderModel *cachedModel,
        unsigned int __formal)
{
  int time; // ebx
  int v8; // ecx
  int update_tics; // edi
  int v10; // eax
  int v11; // edi
  idRenderModelStatic *v12; // eax
  srfTriangles_s *geometry; // edi
  idBounds *v14; // esi
  float lerp; // [esp+4h] [ebp-20h]
  modelSurface_s surf; // [esp+14h] [ebp-10h] BYREF

  if ( cachedModel )
    ((void (__thiscall *)(idRenderModel *, int))cachedModel->~idRenderModel)(cachedModel, 1);
  if ( !this->deformInfo )
    return 0;
  if ( view )
    time = view->renderView.time;
  else
    time = 0;
  v8 = this->time;
  update_tics = this->update_tics;
  v10 = (time - v8) / update_tics;
  if ( v10 > 5 )
  {
    this->time = v8 + update_tics * (v10 - 5);
    v10 = 5;
    goto LABEL_11;
  }
  if ( v10 > 0 )
  {
LABEL_11:
    v11 = v10;
    do
    {
      idRenderModelLiquid::Update(this);
      --v11;
    }
    while ( v11 );
  }
  lerp = (double)(time - this->time) / (double)this->update_tics;
  idRenderModelLiquid::GenerateSurface(this, &surf, lerp);
  v12 = NewRenderModel<idRenderModelStatic>(this);
  geometry = surf.geometry;
  v14 = (idBounds *)v12;
  ((void (__thiscall *)(idRenderModelStatic *, int, const idMaterial *, srfTriangles_s *, idStr *))v12->AddSurface)(
    v12,
    surf.id,
    surf.shader,
    surf.geometry,
    surf.mOriginalSurfaceName);
  v14[1] = geometry->bounds;
  return v14;
}

// FUNC: public: virtual void __thiscall idRenderModelLiquid::InitFromFile(char const *)
void __thiscall idRenderModelLiquid::InitFromFile(idRenderModelLiquid *this, char *fileName)
{
  unsigned __int64 v3; // rax
  unsigned __int64 v4; // rax
  unsigned int v5; // eax
  double v6; // st7
  int verts_x; // ecx
  int verts_y; // eax
  int v9; // eax
  int v10; // edi
  bool v11; // cc
  float *list; // ebp
  int j; // eax
  int v14; // ebp
  float *v15; // eax
  idDrawVert *v16; // eax
  idDrawVert *v17; // edi
  int v18; // edi
  int v19; // ebp
  int v20; // edx
  int v21; // edi
  int v22; // ecx
  char *v23; // eax
  double v24; // st5
  double v25; // st4
  char *v26; // eax
  double v27; // st4
  double v28; // st5
  float *v29; // eax
  double v30; // st4
  int v31; // edi
  int *v32; // ebp
  int v33; // edx
  int v34; // eax
  int v35; // edi
  int *v36; // ecx
  double v37; // st7
  double v38; // st7
  double v39; // st6
  double v40; // st5
  int v41; // [esp+8h] [ebp-140h]
  int v42; // [esp+8h] [ebp-140h]
  float ib; // [esp+Ch] [ebp-13Ch]
  int i; // [esp+Ch] [ebp-13Ch]
  int ia; // [esp+Ch] [ebp-13Ch]
  int x; // [esp+10h] [ebp-138h]
  int xa; // [esp+10h] [ebp-138h]
  int xb; // [esp+10h] [ebp-138h]
  float xc; // [esp+10h] [ebp-138h]
  float size_x; // [esp+14h] [ebp-134h]
  idDrawVert *size_xa; // [esp+14h] [ebp-134h]
  int size_xb; // [esp+14h] [ebp-134h]
  int *tris_12; // [esp+24h] [ebp-124h]
  idToken token; // [esp+2Ch] [ebp-11Ch] BYREF
  idParser parser; // [esp+7Ch] [ebp-CCh] BYREF
  int v56; // [esp+144h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v56 = 0;
  idParser::idParser(&parser, 144);
  LOBYTE(v56) = 2;
  idStr::operator=(&this->name, fileName);
  if ( idParser::LoadFile(&parser, fileName, 0) )
  {
    size_x = (double)this->verts_x * this->scale_x;
    *(float *)&x = (double)this->verts_y * this->scale_y;
    if ( idParser::ReadToken(&parser, &token) )
    {
      while ( idStr::Icmp(token.data, "seed") )
      {
        if ( !idStr::Icmp(token.data, "size_x") )
        {
          size_x = idParser::ParseFloat(&parser);
          goto LABEL_33;
        }
        if ( !idStr::Icmp(token.data, "size_y") )
        {
          *(float *)&x = idParser::ParseFloat(&parser);
          goto LABEL_33;
        }
        if ( idStr::Icmp(token.data, "verts_x") )
        {
          if ( idStr::Icmp(token.data, "verts_y") )
          {
            if ( idStr::Icmp(token.data, "liquid_type") )
            {
              if ( !idStr::Icmp(token.data, "density") )
              {
                this->density = idParser::ParseFloat(&parser);
                goto LABEL_33;
              }
              if ( !idStr::Icmp(token.data, "drop_height") )
              {
                this->drop_height = idParser::ParseFloat(&parser);
                goto LABEL_33;
              }
              if ( !idStr::Icmp(token.data, "drop_radius") )
              {
                this->drop_radius = idParser::ParseInt(&parser);
                goto LABEL_33;
              }
              if ( !idStr::Icmp(token.data, "drop_delay") )
              {
                ib = idParser::ParseFloat(&parser) * 1000.0;
                this->drop_delay = (float)(int)ib;
                goto LABEL_33;
              }
              if ( !idStr::Icmp(token.data, "shader") )
              {
                idParser::ReadToken(&parser, &token);
                this->shader = declManager->FindMaterial(declManager, token.data, 1);
                goto LABEL_33;
              }
              if ( !idStr::Icmp(token.data, "seed") )
                break;
              if ( idStr::Icmp(token.data, "update_rate") )
              {
                idParser::Warning(&parser, "Unknown parameter '%s'.  Using default model.", token.data);
                goto LABEL_40;
              }
              v6 = idParser::ParseFloat(&parser);
              if ( v6 <= 0.0 || v6 > 60.0 )
              {
                idParser::Warning(&parser, "Invalid update_rate.  Must be between 0 and 60.  Using default model.");
                goto LABEL_40;
              }
              this->update_tics = (int)(1000.0 / v6);
            }
            else
            {
              v5 = idParser::ParseInt(&parser) - 1;
              this->liquid_type = v5;
              if ( v5 >= 3 )
              {
                idParser::Warning(&parser, "Invalid liquid_type.  Using default model.");
                goto LABEL_40;
              }
            }
          }
          else
          {
            v4 = (unsigned __int64)idParser::ParseFloat(&parser);
            this->verts_y = v4;
            if ( (int)v4 < 2 )
            {
LABEL_11:
              idParser::Warning(&parser, "Invalid # of verts.  Using default model.");
              goto LABEL_40;
            }
          }
        }
        else
        {
          v3 = (unsigned __int64)idParser::ParseFloat(&parser);
          this->verts_x = v3;
          if ( (int)v3 < 2 )
            goto LABEL_11;
        }
LABEL_33:
        if ( !idParser::ReadToken(&parser, &token) )
          goto LABEL_34;
      }
      this->seed = idParser::ParseInt(&parser);
      goto LABEL_33;
    }
LABEL_34:
    verts_x = this->verts_x;
    verts_y = this->verts_y;
    v41 = verts_y - 1;
    v9 = 2 * verts_x * verts_y;
    v10 = v9;
    this->scale_x = size_x / (double)(verts_x - 1);
    this->scale_y = *(float *)&x / (double)v41;
    if ( v9 > 0 )
    {
      if ( v9 != this->pages.size )
      {
        v11 = v9 < this->pages.num;
        list = this->pages.list;
        this->pages.size = v9;
        if ( v11 )
          this->pages.num = v9;
        this->pages.list = (float *)Memory::Allocate(4 * v9);
        for ( j = 0; j < this->pages.num; ++j )
          this->pages.list[j] = list[j];
        if ( list )
          Memory::Free(list);
      }
    }
    else
    {
      if ( this->pages.list )
        Memory::Free(this->pages.list);
      this->pages.list = 0;
      this->pages.num = 0;
      this->pages.size = 0;
    }
    this->pages.num = v10;
    v14 = this->verts_x * this->verts_y;
    v15 = this->pages.list;
    this->page1 = v15;
    this->page2 = &v15[v14];
    if ( v14 > 0 )
    {
      if ( v14 != this->verts.size )
      {
        v11 = v14 < this->verts.num;
        size_xa = this->verts.list;
        this->verts.size = v14;
        if ( v11 )
          this->verts.num = v14;
        v16 = (idDrawVert *)Memory::Allocate(v14 << 6);
        v17 = v16;
        LOBYTE(v56) = 3;
        if ( v16 )
          `vector constructor iterator'(v16, 0x40u, v14, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
        else
          v17 = 0;
        v11 = this->verts.num <= 0;
        LOBYTE(v56) = 2;
        this->verts.list = v17;
        xa = 0;
        if ( !v11 )
        {
          v18 = 0;
          do
          {
            idDrawVert::operator=(&this->verts.list[v18].xyz.x, (int)&size_xa[v18]);
            ++v18;
            ++xa;
          }
          while ( xa < this->verts.num );
        }
        if ( size_xa )
          Memory::Free(size_xa);
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
    this->verts.num = v14;
    v19 = 0;
    v20 = 0;
    size_xb = 0;
    if ( this->verts_y > 0 )
    {
      i = 0;
      do
      {
        v21 = 0;
        xb = 0;
        if ( this->verts_x > 0 )
        {
          v22 = v20 << 6;
          do
          {
            this->page1[v20] = 0.0;
            this->page2[v20] = 0.0;
            v23 = (char *)this->verts.list + v22;
            *((_DWORD *)v23 + 2) = 0;
            *((_DWORD *)v23 + 1) = 0;
            *(_DWORD *)v23 = 0;
            *((_DWORD *)v23 + 15) = 0;
            *((_DWORD *)v23 + 14) = 0;
            *((_DWORD *)v23 + 6) = 0;
            *((_DWORD *)v23 + 5) = 0;
            *((_DWORD *)v23 + 4) = 0;
            *((_DWORD *)v23 + 10) = 0;
            *((_DWORD *)v23 + 9) = 0;
            *((_DWORD *)v23 + 8) = 0;
            *((_DWORD *)v23 + 13) = 0;
            *((_DWORD *)v23 + 12) = 0;
            *((_DWORD *)v23 + 11) = 0;
            v23[15] = 0;
            v23[14] = 0;
            v23[13] = 0;
            v23[12] = 0;
            v24 = (double)size_xb * this->scale_y;
            v25 = (double)xb;
            v26 = (char *)this->verts.list + v22;
            ++v21;
            xc = v25;
            ++v20;
            v27 = v25 * this->scale_x;
            *((_DWORD *)v26 + 2) = 0;
            *(float *)v26 = v27;
            *((float *)v26 + 1) = v24;
            v28 = (double)i / (double)(this->verts_y - 1);
            v29 = (float *)((char *)&this->verts.list->st.x + v22);
            v22 += 64;
            v30 = xc / (double)(this->verts_x - 1);
            xb = v21;
            *v29 = v30;
            v29[1] = v28;
          }
          while ( v21 < this->verts_x );
        }
        --i;
        size_xb = ++v19;
      }
      while ( v19 < this->verts_y );
    }
    v31 = (this->verts_x - 1) * (6 * this->verts_y - 6);
    v42 = v31;
    if ( v31 > 0 )
      v32 = (int *)Memory::Allocate(4 * v31);
    else
      v32 = 0;
    v33 = 0;
    tris_12 = v32;
    for ( ia = 0; v33 < this->verts_y - 1; ++v33 )
    {
      v34 = 1;
      if ( this->verts_x > 1 )
      {
        v35 = v33 + 1;
        v36 = &v32[ia + 2];
        do
        {
          *(v36 - 2) = v34 + v33 * this->verts_x;
          *(v36 - 1) = v34 + v33 * this->verts_x - 1;
          *v36 = v34 + v35 * this->verts_x - 1;
          v36[1] = v34 + v35 * this->verts_x - 1;
          ia += 6;
          v36[2] = v34 + v35 * this->verts_x;
          v36[3] = v34 + v33 * this->verts_x;
          ++v34;
          v36 += 6;
        }
        while ( v34 < this->verts_x );
        v32 = tris_12;
        v31 = v42;
      }
    }
    this->deformInfo = R_BuildDeformInfo(this->verts.num, this->verts.list, v31, v32, 1);
    this->bounds.b[0].z = idMath::INFINITY;
    this->bounds.b[0].y = idMath::INFINITY;
    this->bounds.b[0].x = idMath::INFINITY;
    this->bounds.b[1].z = -1.0e30;
    this->bounds.b[1].y = -1.0e30;
    this->bounds.b[1].x = -1.0e30;
    v37 = this->drop_height * -10.0;
    if ( this->bounds.b[0].x > 0.0 )
      this->bounds.b[0].x = 0.0;
    if ( this->bounds.b[1].x < 0.0 )
      this->bounds.b[1].x = 0.0;
    if ( this->bounds.b[0].y > 0.0 )
      this->bounds.b[0].y = 0.0;
    if ( this->bounds.b[1].y < 0.0 )
      this->bounds.b[1].y = 0.0;
    if ( v37 < this->bounds.b[0].z )
      this->bounds.b[0].z = v37;
    if ( v37 > this->bounds.b[1].z )
      this->bounds.b[1].z = v37;
    v38 = this->drop_height * 10.0;
    v39 = (double)(this->verts_y - 1) * this->scale_y;
    v40 = (double)(this->verts_x - 1) * this->scale_x;
    if ( v40 < this->bounds.b[0].x )
      this->bounds.b[0].x = v40;
    if ( v40 > this->bounds.b[1].x )
      this->bounds.b[1].x = v40;
    if ( v39 < this->bounds.b[0].y )
      this->bounds.b[0].y = v39;
    if ( v39 > this->bounds.b[1].y )
      this->bounds.b[1].y = v39;
    if ( v38 < this->bounds.b[0].z )
      this->bounds.b[0].z = v38;
    if ( v38 > this->bounds.b[1].z )
      this->bounds.b[1].z = v38;
    fileSystem->ReadFile(fileSystem, this->name.data, 0, &this->timeStamp);
    this->Reset(this);
    LOBYTE(v56) = 1;
    if ( v32 )
      Memory::Free(v32);
    LOBYTE(v56) = 0;
    idParser::~idParser(&parser);
    v56 = -1;
    idStr::FreeData(&token);
  }
  else
  {
LABEL_40:
    idRenderModelStatic::MakeDefaultModel(this);
    LOBYTE(v56) = 0;
    idParser::~idParser(&parser);
    v56 = -1;
    idStr::FreeData(&token);
  }
}
