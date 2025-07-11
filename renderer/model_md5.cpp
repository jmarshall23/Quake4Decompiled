
// FUNC: public: virtual void __thiscall idRenderModelMD5::InitFromFile(char const *)
void __thiscall idRenderModelMD5::InitFromFile(idRenderModelMD5 *this, char *fileName)
{
  idStr::operator=(&this->name, fileName);
  this->LoadModel(this);
}

// FUNC: public: virtual class idBounds __thiscall idRenderModelMD5::Bounds(struct renderEntity_s const *)const
idBounds *__thiscall idRenderModelMD5::Bounds(idRenderModelMD5 *this, idBounds *result, const renderEntity_s *ent)
{
  idBounds *v3; // eax

  v3 = result;
  if ( ent )
    *result = ent->bounds;
  else
    *result = this->bounds;
  return v3;
}

// FUNC: public: virtual enum dynamicModel_t __thiscall idRenderModelMD5::IsDynamicModel(void)const
int __thiscall idRenderModelMD5::IsDynamicModel(idRenderModelMD3 *this)
{
  return 1;
}

// FUNC: public: virtual class idJointMat const * __thiscall idRenderModelMD5::GetSkinSpaceToLocalMats(void)const
const idJointMat *__thiscall idRenderModelMD5::GetSkinSpaceToLocalMats(idRenderModelMD5 *this)
{
  return this->skinSpaceToLocalMats;
}

// FUNC: private: bool __thiscall idMD5Mesh::UpdateLod(struct renderEntity_s const *,struct viewEntity_s const *,struct modelSurface_s const *)
bool __thiscall idMD5Mesh::UpdateLod(
        idMD5Mesh *this,
        const renderEntity_s *ent,
        const viewEntity_s *viewEnt,
        const modelSurface_s *surf)
{
  bool result; // al

  if ( !surf->geometry )
    return 1;
  if ( viewEnt && r_lod_animations_distance.internalVar->integerValue && ent->suppressLOD != 1 )
  {
    if ( this->currentTime > (double)r_lod_animations_wait.internalVar->floatValue
      || viewEnt->distanceToCamera < (double)r_lod_animations_distance.internalVar->floatValue )
    {
      this->currentTime = 0.0;
    }
    else if ( viewEnt->screenCoverage < (double)r_lod_animations_coverage.internalVar->floatValue )
    {
      result = 0;
      this->currentTime = tr.deltaTime + this->currentTime;
      return result;
    }
  }
  return 1;
}

// FUNC: public: class idBounds __thiscall idMD5Mesh::CalcBounds(class idJointMat const *)
idBounds *__thiscall idMD5Mesh::CalcBounds(idMD5Mesh *this, idBounds *result, const idJointMat *entJoints)
{
  int v3; // eax
  void *v4; // esp
  idBounds *v5; // eax
  int v6; // [esp+8h] [ebp-1Ch] BYREF
  idBounds v7; // [esp+Ch] [ebp-18h] BYREF

  v3 = (this->texCoords.num << 6) + 18;
  LOBYTE(v3) = v3 & 0xFC;
  v4 = alloca(v3);
  SIMDProcessor->TransformVertsNew(
    SIMDProcessor,
    (idDrawVert *)&v6,
    this->texCoords.num,
    &v7,
    entJoints,
    this->scaledBaseVectors,
    this->weights,
    this->numWeights);
  v5 = result;
  *result = v7;
  return v5;
}

// FUNC: public: virtual void __thiscall idRenderModelMD5::Print(void)const
void __thiscall idRenderModelMD5::Print(idRenderModelMD5 *this)
{
  idRenderModelMD5 *v1; // ebx
  idMD5Mesh *list; // esi
  int v3; // edi
  int num; // ebx
  int v5; // ebp
  int v6; // eax
  int totalVerts; // [esp+Ch] [ebp-18h]
  int totalTris; // [esp+10h] [ebp-14h]
  int totalWeights; // [esp+14h] [ebp-10h]
  int numWeights; // [esp+18h] [ebp-Ch]
  int numTris; // [esp+1Ch] [ebp-8h]

  v1 = this;
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%s\n", this->name.data);
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "Dynamic model.\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "Generated smooth normals.\n");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
    common.type,
    "    verts  tris weights material\n");
  list = v1->meshes.list;
  v3 = 0;
  totalVerts = 0;
  totalTris = 0;
  totalWeights = 0;
  if ( v1->meshes.num > 0 )
  {
    do
    {
      totalTris += list->numTris;
      num = list->texCoords.num;
      totalVerts += list->texCoords.num;
      v5 = *(_DWORD *)common.type;
      numTris = list->numTris;
      totalWeights += list->numWeights;
      numWeights = list->numWeights;
      v6 = (int)list->shader->base->GetName(list->shader->base);
      (*(void (**)(netadrtype_t, const char *, ...))(v5 + 124))(
        common.type,
        "%2i: %5i %5i %7i %s\n",
        v3,
        num,
        numTris,
        numWeights,
        v6);
      v1 = this;
      ++v3;
      ++list;
    }
    while ( v3 < this->meshes.num );
  }
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "-----\n");
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%4i verts.\n", totalVerts);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(common.type, "%4i tris.\n", totalTris);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%4i weights.\n",
    totalWeights);
  (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
    common.type,
    "%4i joints.\n",
    v1->joints.num);
}

// FUNC: public: virtual void __thiscall idRenderModelMD5::List(void)const
void __thiscall idRenderModelMD5::List(idRenderModelMD5 *this)
{
  int num; // ecx
  idMD5Mesh *list; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // ebp
  const char *v7; // eax
  int v8; // eax
  int v9; // [esp+10h] [ebp-4h]

  num = this->meshes.num;
  list = this->meshes.list;
  v4 = 0;
  v5 = 0;
  v9 = num;
  if ( num > 0 )
  {
    do
    {
      v4 += list->numTris;
      v5 += list->texCoords.num;
      ++list;
      --num;
    }
    while ( num );
  }
  v6 = *(_DWORD *)common.type;
  v7 = this->Name(this);
  v8 = ((int (__thiscall *)(idRenderModelMD5 *, int, int, int, const char *))this->Memory)(this, v9, v5, v4, v7);
  (*(void (__cdecl **)(netadrtype_t, const char *, int))(v6 + 124))(common.type, " %4ik %3i %4i %4i %s(MD5)", v8 / 1024);
  if ( this->defaulted )
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, " (DEFAULTED)");
  (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(common.type, "\n");
}

// FUNC: private: void __thiscall idRenderModelMD5::CalculateBounds(class idJointMat const *)
void __thiscall idRenderModelMD5::CalculateBounds(idRenderModelMD5 *this, const idJointMat *entJoints)
{
  int v3; // ebx
  idMD5Mesh *i; // edi
  float *v5; // ecx
  idBounds result; // [esp+Ch] [ebp-18h] BYREF

  this->bounds.b[0].z = idMath::INFINITY;
  this->bounds.b[0].y = idMath::INFINITY;
  this->bounds.b[0].x = idMath::INFINITY;
  v3 = 0;
  this->bounds.b[1].z = -1.0e30;
  this->bounds.b[1].y = -1.0e30;
  this->bounds.b[1].x = -1.0e30;
  for ( i = this->meshes.list; v3 < this->meshes.num; ++i )
  {
    v5 = (float *)idMD5Mesh::CalcBounds(i, &result, entJoints);
    if ( *v5 < (double)this->bounds.b[0].x )
      this->bounds.b[0].x = *v5;
    if ( v5[1] < (double)this->bounds.b[0].y )
      this->bounds.b[0].y = v5[1];
    if ( v5[2] < (double)this->bounds.b[0].z )
      this->bounds.b[0].z = v5[2];
    if ( v5[3] > (double)this->bounds.b[1].x )
      this->bounds.b[1].x = v5[3];
    if ( v5[4] > (double)this->bounds.b[1].y )
      this->bounds.b[1].y = v5[4];
    if ( v5[5] > (double)this->bounds.b[1].z )
      this->bounds.b[1].z = v5[5];
    ++v3;
  }
}

// FUNC: public: virtual enum jointHandle_t __thiscall idRenderModelMD5::GetJointHandle(char const *)const
int __thiscall idRenderModelMD5::GetJointHandle(idRenderModelMD5 *this, const char *name)
{
  int v3; // esi
  char **i; // edi

  v3 = 0;
  if ( this->joints.num <= 0 )
    return -1;
  for ( i = &this->joints.list->name.data; idStr::Icmp(*i, name); i += 9 )
  {
    if ( ++v3 >= this->joints.num )
      return -1;
  }
  return v3;
}

// FUNC: public: virtual char const * __thiscall idRenderModelMD5::GetJointName(enum jointHandle_t)const
char *__thiscall idRenderModelMD5::GetJointName(idRenderModelMD5 *this, int handle)
{
  if ( handle < 0 || handle >= this->joints.num )
    return "<invalid joint>";
  else
    return this->joints.list[handle].name.data;
}

// FUNC: public: virtual void __thiscall idRenderModelMD5::TouchData(void)
void __thiscall idRenderModelMD5::TouchData(idRenderModelMD5 *this)
{
  int v2; // esi
  const idMaterial **p_shader; // edi
  idDeclManager_vtbl *v4; // ebp
  int v5; // eax

  v2 = 0;
  if ( this->meshes.num > 0 )
  {
    p_shader = &this->meshes.list->shader;
    do
    {
      v4 = declManager->__vftable;
      v5 = ((int (__thiscall *)(idDeclBase *, int))(*p_shader)->base->GetName)((*p_shader)->base, 1);
      ((void (__thiscall *)(idDeclManager *, int))v4->FindMaterial)(declManager, v5);
      ++v2;
      p_shader += 14;
    }
    while ( v2 < this->meshes.num );
  }
}

// FUNC: public: virtual int __thiscall idRenderModelMD5::Memory(void)const
int __thiscall idRenderModelMD5::Memory(idRenderModelMD5 *this)
{
  int num; // ebp
  int v3; // ecx
  int v4; // esi
  char *baseBuffer; // eax
  int v6; // edx
  int v7; // ebx
  int v8; // ebp
  idMD5Mesh *list; // eax
  int numWeights; // ecx
  idMD5Mesh *v11; // eax
  int v12; // esi

  num = this->meshes.num;
  v3 = this->joints.num;
  v4 = 56 * num + 68 * v3 + 156;
  if ( v3 > 0 )
  {
    baseBuffer = this->joints.list->name.baseBuffer;
    do
    {
      if ( *((char **)baseBuffer - 2) == baseBuffer )
        v6 = 0;
      else
        v6 = *((_DWORD *)baseBuffer - 1);
      v4 += v6;
      baseBuffer += 36;
      --v3;
    }
    while ( v3 );
  }
  v7 = 0;
  if ( num > 0 )
  {
    v8 = 0;
    do
    {
      list = this->meshes.list;
      numWeights = list[v8].numWeights;
      v11 = &list[v8];
      v12 = v4 + 92 * numWeights + 8 * v11->texCoords.num + 4;
      ++v7;
      v4 = R_DeformInfoMemoryUsed(v11->deformInfo) + v12;
      ++v8;
    }
    while ( v7 < this->meshes.num );
  }
  return v4;
}

// FUNC: public: virtual int __thiscall idRenderModelMD5::GetSurfaceMask(char const *)const
int __thiscall idRenderModelMD5::GetSurfaceMask(idRenderModelMD5 *this, const char *surface)
{
  int result; // eax
  int v4; // esi
  int v5; // edi
  idDeclBase *base; // ecx
  const char *v7; // eax
  int mask; // [esp+8h] [ebp-4h]

  result = 0;
  v4 = this->meshes.num - 1;
  mask = 0;
  if ( v4 >= 0 )
  {
    v5 = v4;
    do
    {
      base = this->meshes.list[v5].shader->base;
      v7 = base->GetName(base);
      if ( !idStr::Icmp(v7, surface) )
        mask |= 1 << v4;
      --v4;
      --v5;
    }
    while ( v4 >= 0 );
    return mask;
  }
  return result;
}

// FUNC: public: __thiscall idMD5Mesh::idMD5Mesh(void)
void __thiscall idMD5Mesh::idMD5Mesh(idMD5Mesh *this)
{
  this->texCoords.granularity = 16;
  this->texCoords.list = 0;
  this->texCoords.num = 0;
  this->texCoords.size = 0;
  this->scaledBaseVectors = 0;
  this->shader = 0;
  this->numTris = 0;
  this->deformInfo = 0;
  this->surfaceNum = 0;
  this->flags = 0;
  this->weights = 0;
  this->baseVectors = 0;
}

// FUNC: public: __thiscall idMD5Mesh::~idMD5Mesh(void)
void __thiscall idMD5Mesh::~idMD5Mesh(idMD5Mesh *this)
{
  idVec2 *list; // eax

  Mem_Free16(this->scaledBaseVectors);
  if ( this->deformInfo )
  {
    R_FreeDeformInfo(this->deformInfo);
    this->deformInfo = 0;
  }
  Mem_Free16(this->weights);
  Mem_Free16(this->baseVectors);
  list = this->texCoords.list;
  if ( list )
    Memory::Free(list);
  this->texCoords.list = 0;
  this->texCoords.num = 0;
  this->texCoords.size = 0;
}

// FUNC: public: void __thiscall idMD5Mesh::UpdateSurface(struct renderEntity_s const *,class idJointMat const *,struct modelSurface_s *,bool)
void __thiscall idMD5Mesh::UpdateSurface(
        idMD5Mesh *this,
        const renderEntity_s *ent,
        const idJointMat *entJoints,
        modelSurface_s *surf,
        bool calculateTangents)
{
  srfTriangles_s *geometry; // eax
  deformInfo_s *deformInfo; // ecx
  srfTriangles_s *v8; // edi
  bool v9; // zf
  int numOutputVerts; // eax
  int v11; // edx
  int v12; // ecx
  idDrawVert *v13; // eax
  idVec2 *list; // eax
  idDrawVert *verts; // ebp
  deformInfo_s *v16; // eax
  int v17; // ebp
  idSIMDProcessor_vtbl *v18; // eax
  int v19; // edx
  int v20; // ebp
  float *p_x; // ecx
  double v22; // st7
  double v23; // st6
  float v24; // eax
  int v25; // [esp-14h] [ebp-40h]
  idVec4 *baseVectors; // [esp-8h] [ebp-34h]
  jointWeight_t *weights; // [esp-4h] [ebp-30h]
  int numWeights; // [esp+0h] [ebp-2Ch]
  float bitangent_4; // [esp+18h] [ebp-14h]
  float bitangent_8; // [esp+1Ch] [ebp-10h]
  float v31; // [esp+28h] [ebp-4h]
  int surfa; // [esp+38h] [ebp+Ch]
  modelSurface_s *surfb; // [esp+38h] [ebp+Ch]

  ++tr.pc.c_deformedSurfaces;
  tr.pc.c_deformedVerts += this->deformInfo->numOutputVerts;
  tr.pc.c_deformedIndexes += this->deformInfo->numIndexes;
  geometry = surf->geometry;
  surf->shader = this->shader;
  if ( geometry )
  {
    deformInfo = this->deformInfo;
    if ( geometry->numVerts == deformInfo->numOutputVerts && geometry->numIndexes == deformInfo->numIndexes )
    {
      R_FreeStaticTriSurfVertexCaches(geometry);
      goto LABEL_7;
    }
    R_FreeStaticTriSurf(geometry);
  }
  surf->geometry = R_AllocStaticTriSurf();
LABEL_7:
  v8 = surf->geometry;
  v9 = v8->verts == 0;
  v8->deformedSurface = 1;
  v8->tangentsCalculated = 0;
  v8->facePlanesCalculated = 0;
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
  if ( v9 )
  {
    R_AllocStaticTriSurfVerts(v8, numOutputVerts);
    v11 = 0;
    surfa = 0;
    if ( this->deformInfo->numSourceVerts > 0 )
    {
      v12 = 0;
      do
      {
        v13 = &v8->verts[v12];
        v13->xyz.z = 0.0;
        v13->xyz.y = 0.0;
        v13->xyz.x = 0.0;
        v13->st.y = 0.0;
        v13->st.x = 0.0;
        v13->normal.z = 0.0;
        v13->normal.y = 0.0;
        v13->normal.x = 0.0;
        v13->tangents[0].z = 0.0;
        v13->tangents[0].y = 0.0;
        v13->tangents[0].x = 0.0;
        v13->tangents[1].z = 0.0;
        v13->tangents[1].y = 0.0;
        v13->tangents[1].x = 0.0;
        v13->color[3] = 0;
        v13->color[2] = 0;
        v13->color[1] = 0;
        v13->color[0] = 0;
        list = this->texCoords.list;
        verts = v8->verts;
        verts[v12].st.x = list[v11].x;
        verts[v12].st.y = list[surfa].y;
        v11 = surfa + 1;
        ++v12;
        ++surfa;
      }
      while ( surfa < this->deformInfo->numSourceVerts );
    }
    v16 = this->deformInfo;
    v17 = 0;
    if ( v16->numMirroredVerts > 0 )
    {
      surfb = (modelSurface_s *)((v16->numOutputVerts - v16->numMirroredVerts) << 6);
      do
      {
        idDrawVert::operator=(
          (int *)((char *)&surfb->id + (unsigned int)v8->verts),
          (int)&v8->verts[v16->mirroredVerts[v17]]);
        v16 = this->deformInfo;
        surfb += 4;
        ++v17;
      }
      while ( v17 < v16->numMirroredVerts );
    }
  }
  if ( r_useNewSkinning.internalVar->integerValue && calculateTangents )
  {
    v18 = SIMDProcessor->__vftable;
    numWeights = this->numWeights;
    weights = this->weights;
    baseVectors = this->baseVectors;
    v25 = this->deformInfo->numOutputVerts;
    if ( r_useFastSkinning.internalVar->integerValue )
      ((void (__stdcall *)(int, srfTriangles_s *, const idJointMat *, idVec4 *, jointWeight_t *, int))v18->TransformVertsAndTangentsFast)(
        v25,
        v8,
        entJoints,
        baseVectors,
        weights,
        numWeights);
    else
      ((void (__stdcall *)(int, srfTriangles_s *, const idJointMat *, idVec4 *, jointWeight_t *, int))v18->TransformVertsAndTangents)(
        v25,
        v8,
        entJoints,
        baseVectors,
        weights,
        numWeights);
    v8->tangentsCalculated = 1;
  }
  else
  {
    SIMDProcessor->TransformVertsNew(
      SIMDProcessor,
      v8->verts,
      this->deformInfo->numOutputVerts,
      (idBounds *)v8,
      entJoints,
      this->scaledBaseVectors,
      this->weights,
      this->numWeights);
    v8->tangentsCalculated = 0;
  }
  if ( r_deriveBiTangents.internalVar->integerValue )
  {
    v19 = 0;
    if ( this->deformInfo->numOutputVerts > 0 )
    {
      v20 = 0;
      do
      {
        p_x = &v8->verts[v20].xyz.x;
        v22 = p_x[5] * p_x[10] - p_x[6] * p_x[9];
        bitangent_4 = p_x[8] * p_x[6] - p_x[10] * p_x[4];
        v23 = p_x[4] * p_x[9] - p_x[5] * p_x[8];
        if ( v23 * p_x[13] + bitangent_4 * p_x[12] + v22 * p_x[11] >= 0.0 )
        {
          p_x[11] = v22;
          p_x[12] = bitangent_4;
          v24 = v23;
        }
        else
        {
          bitangent_8 = v23;
          v31 = -bitangent_8;
          v24 = v31;
          p_x[11] = -v22;
          p_x[12] = -bitangent_4;
        }
        p_x[13] = v24;
        ++v19;
        ++v20;
      }
      while ( v19 < this->deformInfo->numOutputVerts );
    }
  }
  if ( !v8->tangentsCalculated && !r_useDeferredTangents.internalVar->integerValue )
    R_DeriveTangents(v8, 1);
}

// FUNC: private: void __thiscall idRenderModelMD5::ParseJoint(class Lexer &,class idMD5Joint *,class idJointQuat *)
void __thiscall idRenderModelMD5::ParseJoint(
        idRenderModelMD5 *this,
        Lexer *parser,
        idMD5Joint *joint,
        idJointQuat *defaultPose)
{
  int len; // ebx
  signed int v5; // esi
  double z; // st7
  double y; // st6
  double x; // st5
  idToken token; // [esp+Ch] [ebp-5Ch] BYREF
  int v11; // [esp+64h] [ebp-4h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v11 = 0;
  Lexer::ReadToken(parser, &token);
  len = token.len;
  if ( token.len + 1 > joint->name.alloced )
    idStr::ReAllocate(&joint->name, token.len + 1, 0);
  qmemcpy(joint->name.data, token.data, len);
  joint->name.data[len] = 0;
  joint->name.len = len;
  v5 = Lexer::ParseInt(parser);
  if ( v5 >= 0 )
  {
    if ( v5 >= this->joints.num - 1 )
      Lexer::Error(parser, "Invalid parent for joint '%s'", joint->name.data);
    joint->parent = &this->joints.list[v5];
  }
  else
  {
    joint->parent = 0;
  }
  Lexer::Parse1DMatrix(parser, 3, &defaultPose->t.x);
  Lexer::Parse1DMatrix(parser, 3, &defaultPose->q.x);
  z = defaultPose->q.z;
  y = defaultPose->q.y;
  x = defaultPose->q.x;
  v11 = -1;
  defaultPose->q.w = sqrt(fabs(1.0 - (x * x + y * y + z * z)));
  idStr::FreeData(&token);
}

// FUNC: public: virtual bool __thiscall idRenderModelMD5::HasCollisionSurface(struct renderEntity_s const *)const
char __thiscall idRenderModelMD5::HasCollisionSurface(idRenderModelMD5 *this, const renderEntity_s *ent)
{
  int v3; // edi
  const idMaterial **i; // esi
  const idMaterial *v5; // eax
  int materialFlags; // eax

  v3 = 0;
  if ( this->meshes.num <= 0 )
    return 0;
  for ( i = &this->meshes.list->shader; ; i += 14 )
  {
    v5 = R_RemapShaderBySkin(*i, ent->customSkin, ent->customShader);
    if ( (v5->surfaceFlags & 0x40) != 0 && v5->numStages <= 0 && !v5->entityGui && !v5->gui )
    {
      materialFlags = v5->materialFlags;
      if ( (materialFlags & 8) == 0 && (materialFlags & 4) != 0 )
        break;
    }
    if ( ++v3 >= this->meshes.num )
      return 0;
  }
  return 1;
}

// FUNC: public: void __thiscall idMD5Mesh::ParseMesh(class Lexer &,int,class idJointMat const *)
void __userpurge idMD5Mesh::ParseMesh(
        idMD5Mesh *this@<ecx>,
        int a2@<edi>,
        Lexer *parser,
        idVec4 *numJoints,
        const idJointMat *joints)
{
  int v6; // eax
  Lexer *v7; // edi
  signed int v8; // esi
  bool v9; // cc
  void *v10; // eax
  idVec2 *v11; // eax
  int v12; // eax
  idVec2 *list; // edx
  int *v14; // esi
  unsigned int v15; // eax
  unsigned int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // esi
  int v20; // ecx
  int *v21; // eax
  unsigned int *v22; // esi
  int v23; // eax
  int v24; // esi
  vertexWeight_s *v25; // eax
  float *p_jointWeight; // esi
  int v27; // eax
  int *v28; // esi
  int v29; // edx
  int v30; // eax
  int v31; // ecx
  float *v32; // ecx
  int v33; // edx
  float *v34; // edx
  srfTriangles_s *v35; // edi
  int v36; // edi
  int v37; // edx
  jointWeight_t *v38; // eax
  idVec4 *v39; // eax
  int v40; // edx
  int *v41; // esi
  int v42; // eax
  int v43; // ecx
  int v44; // eax
  int v45; // esi
  int v46; // edx
  float *p_y; // eax
  int v48; // ecx
  double v49; // st7
  idVec4 *v50; // ecx
  double v51; // st6
  bool v52; // zf
  int num; // eax
  int v54; // eax
  void *v55; // esp
  int v56; // esi
  int v57; // ecx
  float *p_z; // eax
  idVec2 *v59; // edx
  deformInfo_s *v60; // eax
  int *mirroredVerts; // eax
  int numMirroredVerts; // ecx
  jointWeight_t *v63; // eax
  deformInfo_s *deformInfo; // eax
  int numWeights; // esi
  int v66; // edx
  int v67; // eax
  int v68; // ecx
  int v69; // eax
  int v70; // edx
  int v71; // esi
  float *v72; // eax
  double v73; // st7
  idVec4 *v74; // ecx
  double v75; // st6
  srfTriangles_s *geometry; // esi
  unsigned int v77; // eax
  idDrawVert *verts; // ecx
  idVec4 *baseVectors; // edx
  idDrawVert *v80; // ecx
  idVec4 *v81; // edx
  idDrawVert *v82; // ecx
  idVec4 *v83; // edx
  idDrawVert *v84; // ecx
  float x; // edi
  int v86; // ecx
  idVec4 *v87; // edx
  int v88; // ecx
  int v89; // [esp-18h] [ebp-10Ch]
  int v90; // [esp-10h] [ebp-104h]
  int v91; // [esp-Ch] [ebp-100h]
  int v92; // [esp+4h] [ebp-F0h] BYREF
  idBounds bounds; // [esp+8h] [ebp-ECh] BYREF
  idToken name; // [esp+20h] [ebp-D4h] BYREF
  idToken token; // [esp+70h] [ebp-84h] BYREF
  idStr shaderName; // [esp+C0h] [ebp-34h] BYREF
  idList<int> tris; // [esp+E0h] [ebp-14h]
  int v98; // [esp+F0h] [ebp-4h]
  int *v99; // [esp+F4h] [ebp+0h]
  int v100; // [esp+F8h] [ebp+4h]
  int v101; // [esp+FCh] [ebp+8h]
  modelSurface_s surf; // [esp+100h] [ebp+Ch] BYREF
  idList<vertexWeight_s> tempWeights; // [esp+110h] [ebp+1Ch]
  idList<int> firstWeightForVertex; // [esp+120h] [ebp+2Ch]
  idList<int> numWeightsForVertex; // [esp+130h] [ebp+3Ch]
  int numIndexes; // [esp+140h] [ebp+4Ch]
  int i; // [esp+144h] [ebp+50h]
  int maxweight; // [esp+148h] [ebp+54h]
  int k; // [esp+14Ch] [ebp+58h]
  int count; // [esp+150h] [ebp+5Ch]
  int v111; // [esp+15Ch] [ebp+68h]
  int extraWeights; // [esp+168h] [ebp+74h]
  jointWeight_t *extraWeightsa; // [esp+168h] [ebp+74h]
  int extraWeightsb; // [esp+168h] [ebp+74h]
  idVec4 *newScaledBaseVectors; // [esp+16Ch] [ebp+78h]
  idVec4 *newScaledBaseVectorsa; // [esp+16Ch] [ebp+78h]
  idVec4 *newScaledBaseVectorsc; // [esp+16Ch] [ebp+78h]
  int newScaledBaseVectorsb; // [esp+16Ch] [ebp+78h]

  token.floatvalue = 0.0;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  name.floatvalue = 0.0;
  v111 = 6;
  name.len = 0;
  name.alloced = 20;
  name.data = name.baseBuffer;
  name.baseBuffer[0] = 0;
  shaderName.alloced = 20;
  shaderName.len = 0;
  shaderName.data = shaderName.baseBuffer;
  shaderName.baseBuffer[0] = 0;
  tris.granularity = 16;
  tris.list = 0;
  tris.num = 0;
  tris.size = 0;
  firstWeightForVertex.granularity = 16;
  firstWeightForVertex.list = 0;
  firstWeightForVertex.num = 0;
  firstWeightForVertex.size = 0;
  numWeightsForVertex.granularity = 16;
  numWeightsForVertex.list = 0;
  numWeightsForVertex.num = 0;
  numWeightsForVertex.size = 0;
  tempWeights.granularity = 16;
  tempWeights.list = 0;
  tempWeights.num = 0;
  tempWeights.size = 0;
  Lexer::ExpectTokenString(parser, "{");
  if ( Lexer::CheckTokenString(parser, "name") )
    Lexer::ReadToken(parser, &name);
  Lexer::ExpectTokenString(parser, "shader");
  Lexer::ReadToken(parser, &token);
  numIndexes = token.len;
  if ( token.len + 1 > shaderName.alloced )
    idStr::ReAllocate(&shaderName, token.len + 1, 0);
  v6 = numIndexes;
  qmemcpy(shaderName.data, token.data, numIndexes);
  shaderName.data[v6] = 0;
  shaderName.len = v6;
  this->shader = (const idMaterial *)((int (__thiscall *)(idDeclManager *, char *, int, int))declManager->FindMaterial)(
                                       declManager,
                                       shaderName.data,
                                       1,
                                       a2);
  Lexer::ExpectTokenString(parser, "numverts");
  v7 = parser;
  v8 = Lexer::ParseInt(parser);
  if ( v8 < 0 )
    Lexer::Error(parser, "Invalid size: %s", token.data);
  if ( v8 > 0 )
  {
    if ( v8 != this->texCoords.size )
    {
      v9 = v8 < this->texCoords.num;
      count = (int)this->texCoords.list;
      this->texCoords.size = v8;
      if ( v9 )
        this->texCoords.num = v8;
      v10 = Memory::Allocate(8 * v8);
      k = (int)v10;
      LOBYTE(v111) = 7;
      if ( v10 )
      {
        `vector constructor iterator'(v10, 8u, v8, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
        v11 = (idVec2 *)k;
      }
      else
      {
        v11 = 0;
      }
      this->texCoords.list = v11;
      v12 = 0;
      v9 = this->texCoords.num <= 0;
      LOBYTE(v111) = 6;
      if ( !v9 )
      {
        do
        {
          list = this->texCoords.list;
          list[v12].x = *(float *)(count + 8 * v12);
          list[v12].y = *(float *)(count + 8 * v12 + 4);
          ++v12;
        }
        while ( v12 < this->texCoords.num );
      }
      if ( count )
        Memory::Free((void *)count);
    }
  }
  else
  {
    if ( this->texCoords.list )
      Memory::Free(this->texCoords.list);
    this->texCoords.list = 0;
    this->texCoords.num = 0;
    this->texCoords.size = 0;
  }
  this->texCoords.num = v8;
  if ( v8 > 0 )
  {
    firstWeightForVertex.size = v8;
    firstWeightForVertex.list = (int *)Memory::Allocate(4 * v8);
  }
  else
  {
    firstWeightForVertex.list = 0;
    firstWeightForVertex.size = 0;
  }
  firstWeightForVertex.num = v8;
  if ( v8 > 0 )
  {
    numWeightsForVertex.size = v8;
    numWeightsForVertex.list = (int *)Memory::Allocate(4 * v8);
  }
  else
  {
    numWeightsForVertex.list = 0;
    numWeightsForVertex.size = 0;
  }
  v9 = this->texCoords.num <= 0;
  numWeightsForVertex.num = v8;
  this->numWeights = 0;
  *(float *)&maxweight = 0.0;
  i = 0;
  if ( !v9 )
  {
    v14 = numWeightsForVertex.list;
    k = (char *)firstWeightForVertex.list - (char *)numWeightsForVertex.list;
    do
    {
      Lexer::ExpectTokenString(parser, "vert");
      Lexer::ParseInt(parser);
      Lexer::Parse1DMatrix(parser, 2, &this->texCoords.list[i].x);
      v15 = Lexer::ParseInt(parser);
      *(int *)((char *)v14 + k) = v15;
      v16 = Lexer::ParseInt(parser);
      *v14 = v16;
      if ( !v16 )
        Lexer::Error(parser, "Vertex without any joint weights.");
      this->numWeights += *v14;
      v17 = *(int *)((char *)v14 + k);
      if ( v17 + *v14 > maxweight )
        maxweight = v17 + *v14;
      ++v14;
      v9 = ++i < this->texCoords.num;
    }
    while ( v9 );
  }
  Lexer::ExpectTokenString(parser, "numtris");
  v18 = Lexer::ParseInt(parser);
  v19 = v18;
  count = v18;
  if ( v18 < 0 )
    Lexer::Error(parser, "Invalid size: %d", v18);
  v20 = 3 * v19;
  v21 = 0;
  numIndexes = 3 * v19;
  if ( 3 * v19 > 0 )
  {
    tris.size = 3 * v19;
    v21 = (int *)Memory::Allocate(12 * v19);
    v20 = numIndexes;
  }
  else
  {
    tris.size = 0;
  }
  tris.list = v21;
  tris.num = v20;
  this->numTris = v19;
  if ( v19 > 0 )
  {
    v22 = (unsigned int *)(v21 + 2);
    k = count;
    do
    {
      Lexer::ExpectTokenString(parser, "tri");
      Lexer::ParseInt(parser);
      *(v22 - 2) = Lexer::ParseInt(parser);
      *(v22 - 1) = Lexer::ParseInt(parser);
      *v22 = Lexer::ParseInt(parser);
      v22 += 3;
      --k;
    }
    while ( k );
  }
  Lexer::ExpectTokenString(parser, "numweights");
  v23 = Lexer::ParseInt(parser);
  v24 = v23;
  count = v23;
  if ( v23 < 0 )
    Lexer::Error(parser, "Invalid size: %d", v23);
  if ( maxweight > v24 )
    Lexer::Warning(parser, "Vertices reference out of range weights in model (%d of %d weights).", maxweight, v24);
  v25 = 0;
  if ( v24 > 0 )
  {
    tempWeights.size = v24;
    v25 = (vertexWeight_s *)Memory::Allocate(24 * v24);
  }
  else
  {
    tempWeights.size = 0;
  }
  tempWeights.list = v25;
  tempWeights.num = v24;
  if ( v24 > 0 )
  {
    p_jointWeight = &v25->jointWeight;
    k = count;
    do
    {
      Lexer::ExpectTokenString(parser, "weight");
      Lexer::ParseInt(parser);
      *(float *)&v27 = COERCE_FLOAT(Lexer::ParseInt(parser));
      maxweight = v27;
      if ( v27 < 0 || v27 >= (int)numJoints )
        Lexer::Error(parser, "Joint Index out of range(%d): %d", numJoints, maxweight);
      *(p_jointWeight - 4) = *(float *)&maxweight;
      *p_jointWeight = Lexer::ParseFloat(parser, 0);
      Lexer::Parse1DMatrix(parser, 3, p_jointWeight - 3);
      p_jointWeight += 6;
      --k;
    }
    while ( k );
  }
  v9 = this->texCoords.num <= 0;
  i = 0;
  if ( !v9 )
  {
    v28 = firstWeightForVertex.list;
    v29 = (char *)numWeightsForVertex.list - (char *)firstWeightForVertex.list;
    newScaledBaseVectors = (idVec4 *)((char *)numWeightsForVertex.list - (char *)firstWeightForVertex.list);
    do
    {
      v30 = *v28;
      v31 = *v28 + *(int *)((char *)v28 + v29);
      count = *v28;
      if ( count < v31 )
      {
        maxweight = v30 + 1;
        v32 = &tempWeights.list[v30].jointWeight;
        do
        {
          v33 = *v28 + *(int *)((char *)v28 + v29);
          k = maxweight;
          if ( maxweight < v33 )
          {
            v34 = v32 + 5;
            do
            {
              if ( v34[1] > (double)*v32 )
              {
                v100 = *((_DWORD *)v34 - 4);
                v101 = *((_DWORD *)v34 - 3);
                surf.id = *(int *)(v34 - 2);
                surf.shader = *(const idMaterial **)(v34 - 1);
                v35 = *(srfTriangles_s **)v34;
                surf.mOriginalSurfaceName = (idStr *)v34[1];
                *(v34 - 4) = *(v32 - 5);
                *(v34 - 3) = *(v32 - 4);
                *(v34 - 2) = *(v32 - 3);
                *(v34 - 1) = *(v32 - 2);
                *v34 = *(v32 - 1);
                v34[1] = *v32;
                *((_DWORD *)v32 - 5) = v100;
                *((_DWORD *)v32 - 4) = v101;
                *(v32 - 3) = *(float *)&surf.id;
                *(v32 - 2) = *(float *)&surf.shader;
                *((_DWORD *)v32 - 1) = v35;
                surf.geometry = v35;
                *v32 = *(float *)&surf.mOriginalSurfaceName;
              }
              v36 = *v28 + *(int *)((char *)v28 + (_DWORD)newScaledBaseVectors);
              v34 += 6;
              ++k;
            }
            while ( k < v36 );
            v30 = count;
          }
          v37 = *v28 + *(int *)((char *)v28 + (_DWORD)newScaledBaseVectors);
          ++maxweight;
          v7 = parser;
          ++v30;
          v32 += 6;
          v9 = v30 < v37;
          v29 = (int)newScaledBaseVectors;
          count = v30;
        }
        while ( v9 );
      }
      ++v28;
      v9 = ++i < this->texCoords.num;
    }
    while ( v9 );
  }
  v38 = (jointWeight_t *)Mem_Alloc16(12 * this->numWeights, 0xEu);
  v90 = 16 * this->numWeights;
  this->weights = v38;
  v39 = (idVec4 *)Mem_Alloc16(v90, 0xEu);
  v40 = 0;
  v9 = this->texCoords.num <= 0;
  this->scaledBaseVectors = v39;
  count = 0;
  i = 0;
  if ( !v9 )
  {
    v41 = firstWeightForVertex.list;
    v42 = (char *)numWeightsForVertex.list - (char *)firstWeightForVertex.list;
    v99 = firstWeightForVertex.list;
    for ( newScaledBaseVectorsa = (idVec4 *)((char *)numWeightsForVertex.list - (char *)firstWeightForVertex.list);
          ;
          v42 = (int)newScaledBaseVectorsa )
    {
      v43 = *(int *)((char *)v41 + v42);
      v44 = *v41;
      if ( v43 > 0 )
      {
        k = 12 * v43;
        v45 = v40;
        v46 = v40;
        count += v43;
        p_y = &tempWeights.list[v44].offset.y;
        v98 = v43;
        do
        {
          this->weights[v46].weight = p_y[2];
          this->weights[v46].jointMatOffset = 48 * *((_DWORD *)p_y - 2);
          this->weights[v46].nextVertexOffset = k;
          v48 = *((int *)p_y + 2);
          k -= 12;
          maxweight = v48;
          v49 = *(float *)&v48 * p_y[1];
          v50 = &this->scaledBaseVectors[v45];
          p_y += 6;
          v51 = *(float *)&maxweight * *(p_y - 6);
          ++v46;
          ++v45;
          v52 = v98-- == 1;
          v50->x = *(float *)&maxweight * *(p_y - 7);
          v50->y = v51;
          v50->z = v49;
          this->scaledBaseVectors[v45 - 1].w = *(p_y - 4);
        }
        while ( !v52 );
        v7 = parser;
        v41 = v99;
        v40 = count;
      }
      ++v41;
      v9 = ++i < this->texCoords.num;
      v99 = v41;
      if ( !v9 )
        break;
    }
  }
  Lexer::ExpectTokenString(v7, "}");
  num = this->texCoords.num;
  c_numVerts += this->texCoords.num;
  c_numWeights += this->numWeights;
  v54 = (num << 6) + 18;
  LOBYTE(v54) = v54 & 0xFC;
  v55 = alloca(v54);
  v56 = 0;
  v57 = 0;
  if ( this->texCoords.num > 0 )
  {
    p_z = &bounds.b[1].z;
    do
    {
      *(p_z - 4) = 0.0;
      *(p_z - 5) = 0.0;
      *(p_z - 6) = 0.0;
      p_z[9] = 0.0;
      p_z[8] = 0.0;
      *p_z = 0.0;
      *(p_z - 1) = 0.0;
      *(p_z - 2) = 0.0;
      p_z[4] = 0.0;
      p_z[3] = 0.0;
      p_z[2] = 0.0;
      p_z[7] = 0.0;
      p_z[6] = 0.0;
      p_z[5] = 0.0;
      *((_BYTE *)p_z - 9) = 0;
      *((_BYTE *)p_z - 10) = 0;
      *((_BYTE *)p_z - 11) = 0;
      *((_BYTE *)p_z - 12) = 0;
      v59 = this->texCoords.list;
      p_z[8] = v59[v57].x;
      p_z[9] = v59[v57++].y;
      p_z += 16;
    }
    while ( v57 < this->texCoords.num );
  }
  ((void (__fastcall *)(idSIMDProcessor *, int *, int, idBounds *, const idJointMat *, idVec4 *, jointWeight_t *))SIMDProcessor->TransformVertsNew)(
    SIMDProcessor,
    &v92,
    this->texCoords.num,
    &bounds,
    joints,
    this->scaledBaseVectors,
    this->weights);
  v60 = R_BuildDeformInfo(
          this->texCoords.num,
          (const idDrawVert *)&v92,
          numIndexes,
          tris.list,
          this->shader->unsmoothedTangents);
  this->deformInfo = v60;
  this->currentTime = 0.0;
  extraWeights = 0;
  if ( v60->numMirroredVerts > 0 )
  {
    mirroredVerts = v60->mirroredVerts;
    numMirroredVerts = this->deformInfo->numMirroredVerts;
    do
    {
      v56 += numWeightsForVertex.list[*mirroredVerts++];
      --numMirroredVerts;
    }
    while ( numMirroredVerts );
    extraWeights = v56;
  }
  newScaledBaseVectorsc = (idVec4 *)Mem_Alloc16(16 * (extraWeights + this->numWeights), 0xEu);
  qmemcpy(newScaledBaseVectorsc, this->scaledBaseVectors, 16 * this->numWeights);
  Mem_Free16(this->scaledBaseVectors);
  v89 = 12 * (extraWeights + this->numWeights);
  this->scaledBaseVectors = newScaledBaseVectorsc;
  v63 = (jointWeight_t *)Mem_Alloc16(v89, 0xEu);
  qmemcpy(v63, this->weights, 12 * this->numWeights);
  extraWeightsa = v63;
  Mem_Free16(this->weights);
  deformInfo = this->deformInfo;
  numWeights = this->numWeights;
  v66 = 0;
  this->weights = extraWeightsa;
  v9 = deformInfo->numMirroredVerts <= 0;
  count = numWeights;
  i = 0;
  if ( !v9 )
  {
    do
    {
      v67 = this->deformInfo->mirroredVerts[v66];
      v68 = numWeightsForVertex.list[v67];
      v69 = firstWeightForVertex.list[v67];
      if ( v68 > 0 )
      {
        newScaledBaseVectorsb = 12 * v68;
        v70 = numWeights;
        v71 = numWeights;
        count += v68;
        v72 = &tempWeights.list[v69].jointWeight;
        numIndexes = v68;
        do
        {
          extraWeightsb = *(int *)v72;
          v73 = *v72 * *(v72 - 1);
          v74 = &this->scaledBaseVectors[v71];
          v72 += 6;
          v75 = *(float *)&extraWeightsb * *(v72 - 8);
          ++v71;
          ++v70;
          v74->x = *(float *)&extraWeightsb * *(v72 - 9);
          v74->y = v75;
          v74->z = v73;
          this->scaledBaseVectors[v71 - 1].w = *(v72 - 6);
          this->weights[v70 - 1].weight = *(v72 - 6);
          this->weights[v70 - 1].jointMatOffset = 48 * *((_DWORD *)v72 - 10);
          this->weights[v70 - 1].nextVertexOffset = newScaledBaseVectorsb;
          v52 = numIndexes-- == 1;
          newScaledBaseVectorsb -= 12;
        }
        while ( !v52 );
        v66 = i;
        numWeights = count;
      }
      v9 = ++v66 < this->deformInfo->numMirroredVerts;
      i = v66;
    }
    while ( v9 );
  }
  if ( tempWeights.list )
    Memory::Free(tempWeights.list);
  tempWeights.list = 0;
  tempWeights.num = 0;
  tempWeights.size = 0;
  if ( numWeightsForVertex.list )
    Memory::Free(numWeightsForVertex.list);
  numWeightsForVertex.list = 0;
  numWeightsForVertex.num = 0;
  numWeightsForVertex.size = 0;
  if ( firstWeightForVertex.list )
    Memory::Free(firstWeightForVertex.list);
  v91 = this->deformInfo->numOutputVerts << 6;
  firstWeightForVertex.list = 0;
  firstWeightForVertex.num = 0;
  firstWeightForVertex.size = 0;
  this->baseVectors = (idVec4 *)Mem_Alloc16(v91, 0xEu);
  memset(&surf, 0, sizeof(surf));
  idMD5Mesh::UpdateSurface(this, 0, joints, &surf, 0);
  geometry = surf.geometry;
  R_DeriveTangents(surf.geometry, 1);
  v9 = this->deformInfo->numOutputVerts <= 0;
  i = 0;
  if ( !v9 )
  {
    v77 = 0;
    do
    {
      verts = geometry->verts;
      baseVectors = this->baseVectors;
      baseVectors[v77 / 0x10].x = verts[v77 / 0x40].xyz.x;
      baseVectors[v77 / 0x10].y = verts[v77 / 0x40].xyz.y;
      baseVectors[v77 / 0x10].z = verts[v77 / 0x40].xyz.z;
      this->baseVectors[v77 / 0x10].w = 1.0;
      v80 = geometry->verts;
      v81 = this->baseVectors;
      v81[v77 / 0x10 + 1].x = v80[v77 / 0x40].normal.x;
      v81[v77 / 0x10 + 1].y = v80[v77 / 0x40].normal.y;
      v81[v77 / 0x10 + 1].z = v80[v77 / 0x40].normal.z;
      this->baseVectors[v77 / 0x10 + 1].w = 0.0;
      v82 = geometry->verts;
      v83 = this->baseVectors;
      v83[v77 / 0x10 + 2].x = v82[v77 / 0x40].tangents[0].x;
      v83[v77 / 0x10 + 2].y = v82[v77 / 0x40].tangents[0].y;
      v83[v77 / 0x10 + 2].z = v82[v77 / 0x40].tangents[0].z;
      this->baseVectors[v77 / 0x10 + 2].w = 0.0;
      v84 = geometry->verts;
      x = v84[v77 / 0x40].tangents[1].x;
      v86 = (int)&v84[v77 / 0x40].tangents[1];
      v87 = &this->baseVectors[v77 / 0x10 + 3];
      v87->x = x;
      v87->y = *(float *)(v86 + 4);
      v87->z = *(float *)(v86 + 8);
      v88 = i;
      this->baseVectors[v77 / 0x10 + 3].w = 0.0;
      ++v88;
      v77 += 64;
      v9 = v88 < this->deformInfo->numOutputVerts;
      i = v88;
    }
    while ( v9 );
  }
  R_FreeStaticTriSurf(geometry);
  LOBYTE(v111) = 2;
  if ( tris.list )
    Memory::Free(tris.list);
  LOBYTE(v111) = 1;
  idStr::FreeData(&shaderName);
  LOBYTE(v111) = 0;
  idStr::FreeData(&name);
  v111 = -1;
  idStr::FreeData(&token);
}

// FUNC: public: virtual class idRenderModel * __thiscall idRenderModelMD5::InstantiateDynamicModel(struct renderEntity_s const *,struct viewDef_s const *,class idRenderModel *,unsigned int)
idRenderModelStatic *__thiscall idRenderModelMD5::InstantiateDynamicModel(
        idRenderModelMD5 *this,
        const renderEntity_s *ent,
        idMD5Mesh *view,
        idRenderModelStatic *cachedModel,
        char surfMask)
{
  idRenderModelStatic *v5; // esi
  int v7; // ebx
  const char *v8; // eax
  int v9; // ebx
  const char *v10; // eax
  int v12; // ebx
  const char *v13; // eax
  int integerValue; // eax
  int suppressSurfaceInViewID; // ecx
  int v16; // eax
  void *v17; // esp
  idMD5Mesh *list; // ebx
  int v19; // edi
  const idMaterial *v20; // eax
  modelSurface_s *v21; // ebx
  int materialFlags; // eax
  int granularity; // eax
  bool v24; // cc
  modelSurface_s *v25; // eax
  int v26; // ecx
  _DWORD *v27; // eax
  _DWORD *v28; // edx
  int num; // edx
  int size; // ecx
  int v31; // eax
  modelSurface_s *v32; // edi
  modelSurface_s *v33; // eax
  int v34; // ecx
  int v35; // eax
  modelSurface_s *v36; // edx
  modelSurface_s *v37; // edi
  int v38; // ebx
  int v39; // edi
  bool v40; // zf
  int v41; // eax
  modelSurface_s *v42; // eax
  int v43; // ecx
  _DWORD *v44; // eax
  _DWORD *v45; // edx
  int v46; // edx
  int v47; // ecx
  int v48; // eax
  modelSurface_s *v49; // edi
  modelSurface_s *v50; // eax
  int v51; // ecx
  int v52; // eax
  modelSurface_s *v53; // edx
  modelSurface_s *v54; // edi
  int v55; // edi
  srfTriangles_s *geometry; // ecx
  srfTriangles_s *v57; // ecx
  double x; // st7
  float *p_x; // ecx
  _BYTE v60[12]; // [esp+0h] [ebp-24h] BYREF
  const idJointMat *entJoints; // [esp+Ch] [ebp-18h]
  const idMaterial *shader; // [esp+10h] [ebp-14h]
  modelSurface_s *v63; // [esp+14h] [ebp-10h]
  modelSurface_s *surf; // [esp+18h] [ebp-Ch]
  idRenderModelMD5 *v65; // [esp+1Ch] [ebp-8h]
  int surfaceNum; // [esp+20h] [ebp-4h] BYREF
  idMD5Mesh *mesh; // [esp+30h] [ebp+Ch]
  int i; // [esp+34h] [ebp+10h]

  v5 = cachedModel;
  v65 = this;
  if ( cachedModel && !r_useCachedDynamicModels.internalVar->integerValue )
  {
    ((void (__thiscall *)(idRenderModelStatic *, int))cachedModel->~idRenderModelStatic)(cachedModel, 1);
    v5 = 0;
  }
  if ( this->purged )
  {
    v7 = *(_DWORD *)common.type;
    v8 = this->Name(this);
    (*(void (**)(netadrtype_t, const char *, ...))(v7 + 140))(common.type, "model %s instantiated while purged", v8);
    this->LoadModel(this);
  }
  if ( !ent->joints )
  {
    v9 = *(_DWORD *)common.type;
    v10 = this->Name(this);
    (*(void (**)(netadrtype_t, const char *, ...))(v9 + 124))(
      common.type,
      "idRenderModelMD5::InstantiateDynamicModel: NULL joints on renderEntity for '%s'\n",
      v10);
    if ( v5 )
    {
      ((void (__thiscall *)(idRenderModelStatic *, int))v5->~idRenderModelStatic)(v5, 1);
      return 0;
    }
    return 0;
  }
  if ( ent->numJoints != this->joints.num )
  {
    v12 = *(_DWORD *)common.type;
    v13 = this->Name(this);
    (*(void (**)(netadrtype_t, const char *, ...))(v12 + 124))(
      common.type,
      "idRenderModelMD5::InstantiateDynamicModel: renderEntity has different number of joints than model for '%s'\n",
      v13);
    if ( v5 )
      ((void (__thiscall *)(idRenderModelStatic *, int))v5->~idRenderModelStatic)(v5, 1);
    return 0;
  }
  ++tr.pc.c_generateMd5;
  if ( !v5 )
  {
    v5 = NewRenderModel<idRenderModelStatic>(this);
    v5->InitEmpty(v5, MD5_SnapshotName);
  }
  v5->bounds.b[0].z = idMath::INFINITY;
  v5->bounds.b[0].y = idMath::INFINITY;
  v5->bounds.b[0].x = idMath::INFINITY;
  v5->bounds.b[1].z = -1.0e30;
  v5->bounds.b[1].y = -1.0e30;
  v5->bounds.b[1].x = -1.0e30;
  integerValue = r_showSkel.internalVar->integerValue;
  if ( integerValue )
  {
    if ( view )
    {
      if ( !r_skipSuppress.internalVar->integerValue
        || (suppressSurfaceInViewID = ent->suppressSurfaceInViewID) == 0
        || suppressSurfaceInViewID != view->texCoords.num )
      {
        idRenderModelMD5::DrawJoints(this, ent, (const viewDef_s *)view, integerValue < 2);
      }
    }
    if ( r_showSkel.internalVar->integerValue > 1 )
    {
      v5->InitEmpty(v5, MD5_SnapshotName);
      return v5;
    }
  }
  if ( !r_useNewSkinning.internalVar->integerValue || (surfMask & 0x40) != 0 )
  {
    entJoints = ent->joints;
  }
  else
  {
    v16 = 48 * v65->joints.num + 18;
    LOBYTE(v16) = v16 & 0xFC;
    v17 = alloca(v16);
    SIMDProcessor->MultiplyJoints(
      SIMDProcessor,
      (idJointMat *)v60,
      ent->joints,
      v65->skinSpaceToLocalMats,
      v65->joints.num);
    entJoints = (const idJointMat *)v60;
  }
  list = v65->meshes.list;
  v19 = 0;
  mesh = list;
  i = 0;
  while ( v19 < v65->meshes.num )
  {
    if ( (*(int (__thiscall **)(_DWORD, int))(**(_DWORD **)common.ip + 28))(*(_DWORD *)common.ip, 0x2000)
      || ((1 << v19) & ent->suppressSurfaceMask) == 0
      || idRenderModelMD5::instantiateAllSurfaces )
    {
      v20 = R_RemapShaderBySkin(list->shader, ent->customSkin, ent->customShader);
      shader = v20;
      if ( (surfMask & 0x40) != 0 )
      {
        if ( v20 && (v20->surfaceFlags & 0x40) != 0 )
          goto LABEL_34;
      }
      else if ( v20 )
      {
        if ( v20->numStages > 0
          || v20->entityGui
          || v20->gui
          || (materialFlags = v20->materialFlags, (materialFlags & 8) != 0)
          || (materialFlags & 4) == 0 )
        {
LABEL_34:
          if ( idRenderModelStatic::FindSurfaceWithId(v5, v19, &surfaceNum) )
          {
            list->surfaceNum = surfaceNum;
            v21 = &v5->surfaces.list[surfaceNum];
          }
          else
          {
            idRenderModelOverlay::RemoveOverlaySurfacesFromModel(v5);
            list->surfaceNum = v5->NumSurfaces(v5);
            if ( !v5->surfaces.list )
            {
              granularity = v5->surfaces.granularity;
              if ( granularity > 0 )
              {
                if ( granularity != v5->surfaces.size )
                {
                  v24 = granularity < v5->surfaces.num;
                  v5->surfaces.size = granularity;
                  if ( v24 )
                    v5->surfaces.num = granularity;
                  v25 = (modelSurface_s *)Memory::Allocate(16 * granularity);
                  v26 = 0;
                  v24 = v5->surfaces.num <= 0;
                  v5->surfaces.list = v25;
                  if ( !v24 )
                  {
                    v27 = 0;
                    do
                    {
                      v28 = (_DWORD *)((char *)v27 + (unsigned int)v5->surfaces.list);
                      *v28 = *v27;
                      v28[1] = v27[1];
                      v28[2] = v27[2];
                      ++v26;
                      v28[3] = v27[3];
                      v27 += 4;
                    }
                    while ( v26 < v5->surfaces.num );
                  }
                }
              }
              else
              {
                v5->surfaces.list = 0;
                v5->surfaces.num = 0;
                v5->surfaces.size = 0;
              }
            }
            num = v5->surfaces.num;
            size = v5->surfaces.size;
            if ( num == size )
            {
              v31 = size + v5->surfaces.granularity;
              if ( v31 > 0 )
              {
                if ( v31 != v5->surfaces.size )
                {
                  v32 = v5->surfaces.list;
                  surf = v32;
                  v5->surfaces.size = v31;
                  if ( v31 < num )
                    v5->surfaces.num = v31;
                  v33 = (modelSurface_s *)Memory::Allocate(16 * v31);
                  v34 = 0;
                  v24 = v5->surfaces.num <= 0;
                  v5->surfaces.list = v33;
                  if ( !v24 )
                  {
                    v35 = 0;
                    do
                    {
                      v36 = &v32[v35];
                      v37 = &v5->surfaces.list[v35];
                      v37->id = v36->id;
                      v37->shader = v36->shader;
                      v37->geometry = v36->geometry;
                      v37->mOriginalSurfaceName = v36->mOriginalSurfaceName;
                      v32 = surf;
                      ++v34;
                      ++v35;
                    }
                    while ( v34 < v5->surfaces.num );
                  }
                  if ( v32 )
                    Memory::Free(v32);
                }
              }
              else
              {
                if ( v5->surfaces.list )
                  Memory::Free(v5->surfaces.list);
                v5->surfaces.list = 0;
                v5->surfaces.num = 0;
                v5->surfaces.size = 0;
              }
            }
            v38 = v5->surfaces.num;
            v5->surfaces.num = v38 + 1;
            v21 = &v5->surfaces.list[v38];
            v21->geometry = 0;
            v21->shader = 0;
            v21->id = i;
          }
          v39 = 0;
          v40 = !shader->shouldCreateBackSides;
          surf = v21;
          if ( !v40 )
          {
            if ( idRenderModelStatic::FindSurfaceWithId(v5, i + 1000, &surfaceNum) )
            {
              v39 = (int)&v5->surfaces.list[surfaceNum];
            }
            else
            {
              surfaceNum = v5->NumSurfaces(v5);
              if ( !v5->surfaces.list )
              {
                v41 = v5->surfaces.granularity;
                if ( v41 > 0 )
                {
                  if ( v41 != v5->surfaces.size )
                  {
                    v24 = v41 < v5->surfaces.num;
                    v5->surfaces.size = v41;
                    if ( v24 )
                      v5->surfaces.num = v41;
                    v42 = (modelSurface_s *)Memory::Allocate(16 * v41);
                    v43 = 0;
                    v24 = v5->surfaces.num <= 0;
                    v5->surfaces.list = v42;
                    if ( !v24 )
                    {
                      v44 = 0;
                      do
                      {
                        v45 = (_DWORD *)((char *)v44 + (unsigned int)v5->surfaces.list);
                        *v45 = *v44;
                        v45[1] = v44[1];
                        v45[2] = v44[2];
                        ++v43;
                        v45[3] = v44[3];
                        v44 += 4;
                      }
                      while ( v43 < v5->surfaces.num );
                      v21 = surf;
                    }
                  }
                }
                else
                {
                  v5->surfaces.list = 0;
                  v5->surfaces.num = 0;
                  v5->surfaces.size = 0;
                }
              }
              v46 = v5->surfaces.num;
              v47 = v5->surfaces.size;
              if ( v46 == v47 )
              {
                v48 = v47 + v5->surfaces.granularity;
                if ( v48 > 0 )
                {
                  if ( v48 != v5->surfaces.size )
                  {
                    v49 = v5->surfaces.list;
                    v63 = v49;
                    v5->surfaces.size = v48;
                    if ( v48 < v46 )
                      v5->surfaces.num = v48;
                    v50 = (modelSurface_s *)Memory::Allocate(16 * v48);
                    v51 = 0;
                    v24 = v5->surfaces.num <= 0;
                    v5->surfaces.list = v50;
                    if ( !v24 )
                    {
                      v52 = 0;
                      do
                      {
                        v53 = &v49[v52];
                        v54 = &v5->surfaces.list[v52];
                        v54->id = v53->id;
                        v54->shader = v53->shader;
                        v54->geometry = v53->geometry;
                        v54->mOriginalSurfaceName = v53->mOriginalSurfaceName;
                        v49 = v63;
                        ++v51;
                        ++v52;
                      }
                      while ( v51 < v5->surfaces.num );
                      v21 = surf;
                    }
                    if ( v49 )
                      Memory::Free(v49);
                  }
                }
                else
                {
                  if ( v5->surfaces.list )
                    Memory::Free(v5->surfaces.list);
                  v5->surfaces.list = 0;
                  v5->surfaces.num = 0;
                  v5->surfaces.size = 0;
                }
              }
              v55 = v5->surfaces.num;
              v5->surfaces.num = v55 + 1;
              v39 = (int)&v5->surfaces.list[v55];
              *(_DWORD *)(v39 + 4) = shader;
              *(_DWORD *)(v39 + 8) = 0;
              *(_DWORD *)v39 = i + 1000;
            }
          }
          if ( idMD5Mesh::UpdateLod(mesh, ent, v65->viewEnt, v21) )
            idMD5Mesh::UpdateSurface(mesh, ent, entJoints, v21, (surfMask & 0x40) == 0);
          geometry = v21->geometry;
          if ( geometry->bounds.b[0].x < (double)v5->bounds.b[0].x )
            v5->bounds.b[0].x = geometry->bounds.b[0].x;
          if ( geometry->bounds.b[0].x > (double)v5->bounds.b[1].x )
            v5->bounds.b[1].x = geometry->bounds.b[0].x;
          if ( geometry->bounds.b[0].y < (double)v5->bounds.b[0].y )
            v5->bounds.b[0].y = geometry->bounds.b[0].y;
          if ( geometry->bounds.b[0].y > (double)v5->bounds.b[1].y )
            v5->bounds.b[1].y = geometry->bounds.b[0].y;
          if ( geometry->bounds.b[0].z < (double)v5->bounds.b[0].z )
            v5->bounds.b[0].z = geometry->bounds.b[0].z;
          if ( geometry->bounds.b[0].z > (double)v5->bounds.b[1].z )
            v5->bounds.b[1].z = geometry->bounds.b[0].z;
          v57 = v21->geometry;
          x = v57->bounds.b[1].x;
          p_x = &v57->bounds.b[1].x;
          if ( x < v5->bounds.b[0].x )
            v5->bounds.b[0].x = *p_x;
          if ( *p_x > (double)v5->bounds.b[1].x )
            v5->bounds.b[1].x = *p_x;
          if ( p_x[1] < (double)v5->bounds.b[0].y )
            v5->bounds.b[0].y = p_x[1];
          if ( p_x[1] > (double)v5->bounds.b[1].y )
            v5->bounds.b[1].y = p_x[1];
          if ( p_x[2] < (double)v5->bounds.b[0].z )
            v5->bounds.b[0].z = p_x[2];
          if ( p_x[2] > (double)v5->bounds.b[1].z )
            v5->bounds.b[1].z = p_x[2];
          if ( v39 )
            R_CopyAndReverseTriangles(v21->geometry, (srfTriangles_s **)(v39 + 8));
          list = mesh;
          v19 = i;
          goto LABEL_124;
        }
      }
      if ( idRenderModelMD5::instantiateAllSurfaces )
        goto LABEL_34;
    }
    idRenderModelStatic::DeleteSurfaceWithId(v5, v19);
    idRenderModelStatic::DeleteSurfaceWithId(v5, v19 + 1000);
    list->surfaceNum = -1;
LABEL_124:
    ++v19;
    ++list;
    i = v19;
    mesh = list;
  }
  return v5;
}

// FUNC: public: virtual void __thiscall idRenderModelMD5::PurgeModel(void)
void __thiscall idRenderModelMD5::PurgeModel(idRenderModelMD5 *this)
{
  idMD5Joint *list; // eax
  const idMD5Joint **p_parent; // ebx
  idMD5Mesh *v4; // eax
  float *p_currentTime; // ebx
  idJointMat *skinSpaceToLocalMats; // eax

  this->purged = 1;
  list = this->joints.list;
  if ( list )
  {
    p_parent = &list[-1].parent;
    `eh vector destructor iterator'(
      list,
      0x24u,
      (int)list[-1].parent,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(p_parent);
  }
  this->joints.list = 0;
  this->joints.num = 0;
  this->joints.size = 0;
  v4 = this->meshes.list;
  if ( v4 )
  {
    p_currentTime = &v4[-1].currentTime;
    `eh vector destructor iterator'(
      v4,
      0x38u,
      LODWORD(v4[-1].currentTime),
      (void (__thiscall *)(void *))idMD5Mesh::~idMD5Mesh);
    Memory::Free(p_currentTime);
  }
  this->meshes.list = 0;
  this->meshes.num = 0;
  this->meshes.size = 0;
  Mem_Free16(this->defaultPose);
  skinSpaceToLocalMats = this->skinSpaceToLocalMats;
  this->defaultPose = 0;
  if ( skinSpaceToLocalMats )
  {
    Mem_Free16(skinSpaceToLocalMats);
    this->skinSpaceToLocalMats = 0;
  }
}

// FUNC: public: __thiscall idRenderModelMD5::idRenderModelMD5(void)
void __thiscall idRenderModelMD5::idRenderModelMD5(idRenderModelMD5 *this)
{
  idRenderModelStatic::idRenderModelStatic(this);
  this->__vftable = (idRenderModelMD5_vtbl *)&idRenderModelMD5::`vftable';
  this->joints.granularity = 16;
  this->joints.list = 0;
  this->joints.num = 0;
  this->joints.size = 0;
  this->meshes.granularity = 16;
  this->meshes.list = 0;
  this->meshes.num = 0;
  this->meshes.size = 0;
  this->skinSpaceToLocalMats = 0;
  this->defaultPose = 0;
}

// FUNC: public: virtual __thiscall idRenderModelMD5::~idRenderModelMD5(void)
void __thiscall idRenderModelMD5::~idRenderModelMD5(idRenderModelMD5 *this)
{
  idJointMat *skinSpaceToLocalMats; // eax
  idMD5Mesh *list; // eax
  float *p_currentTime; // edi
  idMD5Joint *v5; // eax
  const idMD5Joint **p_parent; // edi

  this->__vftable = (idRenderModelMD5_vtbl *)&idRenderModelMD5::`vftable';
  skinSpaceToLocalMats = this->skinSpaceToLocalMats;
  if ( skinSpaceToLocalMats )
    Mem_Free16(skinSpaceToLocalMats);
  Mem_Free16(this->defaultPose);
  list = this->meshes.list;
  if ( list )
  {
    p_currentTime = &list[-1].currentTime;
    `eh vector destructor iterator'(
      list,
      0x38u,
      LODWORD(list[-1].currentTime),
      (void (__thiscall *)(void *))idMD5Mesh::~idMD5Mesh);
    Memory::Free(p_currentTime);
  }
  this->meshes.list = 0;
  this->meshes.num = 0;
  this->meshes.size = 0;
  v5 = this->joints.list;
  if ( v5 )
  {
    p_parent = &v5[-1].parent;
    `eh vector destructor iterator'(
      v5,
      0x24u,
      (int)v5[-1].parent,
      (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
    Memory::Free(p_parent);
  }
  this->joints.list = 0;
  this->joints.num = 0;
  this->joints.size = 0;
  idRenderModelStatic::~idRenderModelStatic(this);
}

// FUNC: public: virtual void __thiscall idRenderModelMD5::LoadModel(void)
void __thiscall idRenderModelMD5::LoadModel(idRenderModelMD5 *this)
{
  idRenderModelMD5 *v1; // ebx
  Lexer *v2; // esi
  bool v3; // zf
  const char *data; // eax
  unsigned int v5; // eax
  idMD5Joint *list; // eax
  int v7; // esi
  const idMD5Joint **p_parent; // esi
  int *v9; // eax
  idMD5Joint *v10; // edi
  bool v11; // cc
  idStr *v12; // ebp
  idMD5Joint *v13; // eax
  const idMD5Joint **v14; // esi
  signed int *v15; // eax
  idMD5Joint *v16; // esi
  idStr *v17; // ebp
  signed int v18; // eax
  idMD5Mesh *v19; // eax
  int v20; // esi
  char *p_currentTime; // esi
  idMD5Mesh *v22; // eax
  char *v23; // esi
  int *v24; // eax
  idMD5Mesh *v25; // edi
  int *p_granularity; // edi
  int v27; // esi
  void *v28; // eax
  _DWORD *v29; // esi
  int v30; // eax
  void *v31; // eax
  void *v32; // ebp
  int v33; // eax
  int v34; // edx
  int v35; // ecx
  int *v36; // eax
  idMD5Mesh *v37; // edi
  int *v38; // edi
  int v39; // esi
  void *v40; // eax
  _DWORD *v41; // esi
  int v42; // eax
  void *v43; // eax
  void *v44; // ebp
  int v45; // eax
  int v46; // ecx
  int v47; // edx
  idJointQuat *defaultPose; // edi
  float *p_z; // esi
  float *v50; // ebp
  idMat3 *v51; // eax
  const idMD5Joint *parent; // eax
  int v53; // edi
  idJointMat *v54; // ebx
  double v55; // st7
  double v56; // st6
  double v57; // st5
  double v58; // st4
  double v59; // st3
  double v60; // st2
  int v61; // ecx
  float v62; // edx
  char *v63; // edx
  float *v64; // ecx
  double v65; // st7
  double v66; // st6
  double v67; // st5
  double v68; // st4
  double v69; // st3
  double v70; // st2
  float *v71; // eax
  int v72; // esi
  double v73; // st7
  idQuat *v74; // eax
  double v75; // st7
  double v76; // st6
  double v77; // st5
  double v78; // st2
  double v79; // st4
  int v80; // esi
  int v81; // edi
  int v82; // ecx
  int v83; // edx
  idJointMat *skinSpaceToLocalMats; // eax
  double v85; // st7
  idJointMat *v86; // eax
  double v87; // st6
  float v88; // esi
  double v89; // st7
  double v90; // st6
  float v91; // esi
  idMD5Joint *ptr; // [esp+8h] [ebp-190h]
  int *ptra; // [esp+8h] [ebp-190h]
  idMD5Mesh *ptrb; // [esp+8h] [ebp-190h]
  idMD5Mesh *ptrc; // [esp+8h] [ebp-190h]
  float ptrd; // [esp+8h] [ebp-190h]
  idJointQuat *pose; // [esp+Ch] [ebp-18Ch]
  idJointQuat *posea; // [esp+Ch] [ebp-18Ch]
  idJointQuat *poseb; // [esp+Ch] [ebp-18Ch]
  idJointQuat *posec; // [esp+Ch] [ebp-18Ch]
  idJointQuat *posed; // [esp+Ch] [ebp-18Ch]
  int __n; // [esp+10h] [ebp-188h]
  int __na; // [esp+10h] [ebp-188h]
  int __nb; // [esp+10h] [ebp-188h]
  int __nc; // [esp+10h] [ebp-188h]
  float *__nd; // [esp+10h] [ebp-188h]
  idJointMat *transformedDefaultPose; // [esp+14h] [ebp-184h]
  idJointMat *transformedDefaultPosea; // [esp+14h] [ebp-184h]
  idJointMat *transformedDefaultPoseb; // [esp+14h] [ebp-184h]
  signed int num; // [esp+18h] [ebp-180h]
  int numa; // [esp+18h] [ebp-180h]
  idMD5Joint *numb; // [esp+18h] [ebp-180h]
  int i; // [esp+1Ch] [ebp-17Ch]
  float v114; // [esp+20h] [ebp-178h]
  float v115; // [esp+20h] [ebp-178h]
  Lexer *lexer; // [esp+24h] [ebp-174h]
  float v117; // [esp+28h] [ebp-170h]
  float v119; // [esp+30h] [ebp-168h]
  float v120; // [esp+34h] [ebp-164h]
  float v121; // [esp+38h] [ebp-160h]
  float v122; // [esp+40h] [ebp-158h]
  float v123; // [esp+48h] [ebp-150h]
  float v124; // [esp+4Ch] [ebp-14Ch]
  float v125; // [esp+50h] [ebp-148h]
  float v126; // [esp+54h] [ebp-144h]
  float v127; // [esp+60h] [ebp-138h]
  float v128; // [esp+64h] [ebp-134h]
  float v129; // [esp+68h] [ebp-130h]
  float v130[7]; // [esp+6Ch] [ebp-12Ch] BYREF
  int v131[8]; // [esp+88h] [ebp-110h] BYREF
  float v132; // [esp+A8h] [ebp-F0h]
  float v133; // [esp+B4h] [ebp-E4h]
  idToken token; // [esp+C0h] [ebp-D8h] BYREF
  idQuat v135; // [esp+110h] [ebp-88h] BYREF
  char v136[36]; // [esp+120h] [ebp-78h] BYREF
  idMat3 v137; // [esp+144h] [ebp-54h] BYREF
  idMat3 result; // [esp+168h] [ebp-30h] BYREF
  int v139; // [esp+194h] [ebp-4h]

  token.floatvalue = 0.0;
  v1 = this;
  token.len = 0;
  token.alloced = 20;
  token.data = token.baseBuffer;
  token.baseBuffer[0] = 0;
  v139 = 0;
  v2 = LexerFactory::MakeLexer(144);
  lexer = v2;
  v3 = !v1->purged;
  LOBYTE(v139) = 1;
  if ( v3 )
    v1->PurgeModel(v1);
  data = v1->name.data;
  v1->purged = 0;
  if ( Lexer::LoadFile(v2, data, 0) )
  {
    Lexer::ExpectTokenString(v2, "MD5Version");
    v5 = Lexer::ParseInt(v2);
    if ( v5 != 10 )
      Lexer::Error(v2, "Invalid version %d.  Should be version %d\n", v5, 10);
    Lexer::ExpectTokenString(v2, "commandline");
    Lexer::ReadToken(v2, &token);
    Lexer::ExpectTokenString(v2, "numJoints");
    num = Lexer::ParseInt(v2);
    list = v1->joints.list;
    v1->joints.granularity = 1;
    ptr = list;
    if ( list )
    {
      v7 = v1->joints.num;
      if ( v7 != v1->joints.size )
      {
        if ( v7 > 0 )
        {
          v1->joints.size = v7;
          v9 = (int *)Memory::Allocate(36 * v7 + 4);
          LOBYTE(v139) = 2;
          if ( v9 )
          {
            v10 = (idMD5Joint *)(v9 + 1);
            *v9 = v7;
            `eh vector constructor iterator'(
              v9 + 1,
              0x24u,
              v7,
              (void (__thiscall *)(void *))idMD5Joint::idMD5Joint,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          }
          else
          {
            v10 = 0;
          }
          v11 = v1->joints.num <= 0;
          LOBYTE(v139) = 1;
          v1->joints.list = v10;
          pose = 0;
          if ( !v11 )
          {
            transformedDefaultPose = (idJointMat *)&ptr->parent;
            do
            {
              v12 = (idStr *)((char *)&v1->joints.list->name + (unsigned int)transformedDefaultPose - 32 - (_DWORD)ptr);
              __n = LODWORD(transformedDefaultPose[-1].mat[4]);
              if ( __n + 1 > v12->alloced )
                idStr::ReAllocate(v12, __n + 1, 0);
              qmemcpy(v12->data, (const void *)LODWORD(transformedDefaultPose[-1].mat[5]), __n);
              v12->data[__n] = 0;
              v12->len = __n;
              v12[1].len = LODWORD(transformedDefaultPose->mat[0]);
              v11 = (int)&pose->q.x + 1 < v1->joints.num;
              pose = (idJointQuat *)((char *)pose + 1);
              transformedDefaultPose = (idJointMat *)((char *)transformedDefaultPose + 36);
            }
            while ( v11 );
          }
          if ( ptr )
          {
            `eh vector destructor iterator'(
              ptr,
              0x24u,
              (int)ptr[-1].parent,
              (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
            Memory::Free(&ptr[-1].parent);
          }
        }
        else
        {
          p_parent = &list[-1].parent;
          `eh vector destructor iterator'(
            list,
            0x24u,
            (int)list[-1].parent,
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(p_parent);
          v1->joints.list = 0;
          v1->joints.num = 0;
          v1->joints.size = 0;
        }
      }
    }
    if ( num > 0 )
    {
      if ( num != v1->joints.size )
      {
        v11 = num < v1->joints.num;
        transformedDefaultPosea = (idJointMat *)v1->joints.list;
        v1->joints.size = num;
        if ( v11 )
          v1->joints.num = num;
        v15 = (signed int *)Memory::Allocate(36 * num + 4);
        LOBYTE(v139) = 3;
        if ( v15 )
        {
          v16 = (idMD5Joint *)(v15 + 1);
          *v15 = num;
          `eh vector constructor iterator'(
            v15 + 1,
            0x24u,
            num,
            (void (__thiscall *)(void *))idMD5Joint::idMD5Joint,
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        }
        else
        {
          v16 = 0;
        }
        v11 = v1->joints.num <= 0;
        LOBYTE(v139) = 1;
        v1->joints.list = v16;
        posea = 0;
        if ( !v11 )
        {
          ptra = (int *)&transformedDefaultPosea->mat[8];
          do
          {
            v17 = (idStr *)((char *)&v1->joints.list->name + (unsigned int)ptra - 32 - (_DWORD)transformedDefaultPosea);
            __na = *(ptra - 8);
            if ( __na + 1 > v17->alloced )
              idStr::ReAllocate(v17, __na + 1, 0);
            qmemcpy(v17->data, (const void *)*(ptra - 7), __na);
            v17->data[__na] = 0;
            v17->len = __na;
            v17[1].len = *ptra;
            v11 = (int)&posea->q.x + 1 < v1->joints.num;
            posea = (idJointQuat *)((char *)posea + 1);
            ptra += 9;
          }
          while ( v11 );
        }
        if ( transformedDefaultPosea )
        {
          `eh vector destructor iterator'(
            transformedDefaultPosea,
            0x24u,
            LODWORD(transformedDefaultPosea[-1].mat[11]),
            (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
          Memory::Free(&transformedDefaultPosea[-1].mat[11]);
        }
      }
    }
    else
    {
      v13 = v1->joints.list;
      if ( v13 )
      {
        v14 = &v13[-1].parent;
        `eh vector destructor iterator'(
          v13,
          0x24u,
          (int)v13[-1].parent,
          (void (__thiscall *)(void *))idHashTable<rvDeclGuide *>::hashnode_s::~hashnode_s);
        Memory::Free(v14);
      }
      v1->joints.list = 0;
      v1->joints.num = 0;
      v1->joints.size = 0;
    }
    v1->joints.num = num;
    v1->defaultPose = (idJointQuat *)Mem_Alloc16(32 * num, 0xEu);
    transformedDefaultPoseb = (idJointMat *)Mem_Alloc16(48 * num, 0xEu);
    Lexer::ExpectTokenString(lexer, "numMeshes");
    v18 = Lexer::ParseInt(lexer);
    numa = v18;
    if ( v18 < 0 )
      Lexer::Error(lexer, "Invalid size: %d", v18);
    v19 = v1->meshes.list;
    v1->meshes.granularity = 1;
    ptrb = v19;
    if ( v19 )
    {
      v20 = v1->meshes.num;
      if ( v20 != v1->meshes.size )
      {
        if ( v20 > 0 )
        {
          v1->meshes.size = v20;
          v24 = (int *)Memory::Allocate(56 * v20 + 4);
          LOBYTE(v139) = 4;
          if ( v24 )
          {
            v25 = (idMD5Mesh *)(v24 + 1);
            *v24 = v20;
            `eh vector constructor iterator'(
              v24 + 1,
              0x38u,
              v20,
              (void (__thiscall *)(void *))idMD5Mesh::idMD5Mesh,
              (void (__thiscall *)(void *))idMD5Mesh::~idMD5Mesh);
          }
          else
          {
            v25 = 0;
          }
          v11 = v1->meshes.num <= 0;
          LOBYTE(v139) = 1;
          v1->meshes.list = v25;
          poseb = 0;
          if ( !v11 )
          {
            p_granularity = &ptrb->texCoords.granularity;
            do
            {
              v27 = (int)v1->meshes.list - 8 - (_DWORD)ptrb;
              v28 = *(void **)((char *)p_granularity + v27 + 12);
              v29 = (int *)((char *)p_granularity + v27);
              if ( v28 )
                Memory::Free(v28);
              *v29 = 0;
              v29[1] = 0;
              v29[3] = 0;
              *v29 = *(p_granularity - 2);
              v30 = *(p_granularity - 1);
              v29[1] = v30;
              v29[2] = *p_granularity;
              __nb = v30;
              if ( v30 )
              {
                v31 = Memory::Allocate(8 * v30);
                v32 = v31;
                LOBYTE(v139) = 5;
                if ( v31 )
                  `vector constructor iterator'(v31, 8u, __nb, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
                else
                  v32 = 0;
                v33 = 0;
                v11 = *v29 <= 0;
                LOBYTE(v139) = 1;
                v29[3] = v32;
                if ( !v11 )
                {
                  do
                  {
                    v34 = p_granularity[1];
                    v35 = v29[3];
                    *(_DWORD *)(v35 + 8 * v33) = *(_DWORD *)(v34 + 8 * v33);
                    *(_DWORD *)(v35 + 8 * v33 + 4) = *(_DWORD *)(v34 + 8 * v33 + 4);
                    ++v33;
                  }
                  while ( v33 < *v29 );
                }
              }
              v29[4] = p_granularity[2];
              v29[5] = p_granularity[3];
              v29[6] = p_granularity[4];
              v29[7] = p_granularity[5];
              v29[8] = p_granularity[6];
              v29[9] = p_granularity[7];
              v29[10] = p_granularity[8];
              v29[11] = p_granularity[9];
              v29[12] = p_granularity[10];
              v29[13] = p_granularity[11];
              p_granularity += 14;
              poseb = (idJointQuat *)((char *)poseb + 1);
            }
            while ( (int)poseb < v1->meshes.num );
          }
          if ( ptrb )
          {
            `eh vector destructor iterator'(
              ptrb,
              0x38u,
              LODWORD(ptrb[-1].currentTime),
              (void (__thiscall *)(void *))idMD5Mesh::~idMD5Mesh);
            Memory::Free(&ptrb[-1].currentTime);
          }
        }
        else
        {
          p_currentTime = (char *)&v19[-1].currentTime;
          `eh vector destructor iterator'(
            v19,
            0x38u,
            LODWORD(v19[-1].currentTime),
            (void (__thiscall *)(void *))idMD5Mesh::~idMD5Mesh);
          Memory::Free(p_currentTime);
          v1->meshes.list = 0;
          v1->meshes.num = 0;
          v1->meshes.size = 0;
        }
      }
    }
    if ( numa > 0 )
    {
      if ( numa != v1->meshes.size )
      {
        v11 = numa < v1->meshes.num;
        ptrc = v1->meshes.list;
        v1->meshes.size = numa;
        if ( v11 )
          v1->meshes.num = numa;
        v36 = (int *)Memory::Allocate(56 * numa + 4);
        LOBYTE(v139) = 6;
        if ( v36 )
        {
          v37 = (idMD5Mesh *)(v36 + 1);
          *v36 = numa;
          `eh vector constructor iterator'(
            v36 + 1,
            0x38u,
            numa,
            (void (__thiscall *)(void *))idMD5Mesh::idMD5Mesh,
            (void (__thiscall *)(void *))idMD5Mesh::~idMD5Mesh);
        }
        else
        {
          v37 = 0;
        }
        v11 = v1->meshes.num <= 0;
        LOBYTE(v139) = 1;
        v1->meshes.list = v37;
        posec = 0;
        if ( !v11 )
        {
          v38 = &ptrc->texCoords.granularity;
          do
          {
            v39 = (int)v1->meshes.list - 8 - (_DWORD)ptrc;
            v40 = *(void **)((char *)v38 + v39 + 12);
            v41 = (int *)((char *)v38 + v39);
            if ( v40 )
              Memory::Free(v40);
            *v41 = 0;
            v41[1] = 0;
            v41[3] = 0;
            *v41 = *(v38 - 2);
            v42 = *(v38 - 1);
            v41[1] = v42;
            v41[2] = *v38;
            __nc = v42;
            if ( v42 )
            {
              v43 = Memory::Allocate(8 * v42);
              v44 = v43;
              LOBYTE(v139) = 7;
              if ( v43 )
                `vector constructor iterator'(v43, 8u, __nc, (void *(__thiscall *)(void *))idDrawVert::idDrawVert);
              else
                v44 = 0;
              v45 = 0;
              v11 = *v41 <= 0;
              LOBYTE(v139) = 1;
              v41[3] = v44;
              if ( !v11 )
              {
                do
                {
                  v46 = v38[1];
                  v47 = v41[3];
                  *(_DWORD *)(v47 + 8 * v45) = *(_DWORD *)(v46 + 8 * v45);
                  *(_DWORD *)(v47 + 8 * v45 + 4) = *(_DWORD *)(v46 + 8 * v45 + 4);
                  ++v45;
                }
                while ( v45 < *v41 );
              }
            }
            v41[4] = v38[2];
            v41[5] = v38[3];
            v41[6] = v38[4];
            v41[7] = v38[5];
            v41[8] = v38[6];
            v41[9] = v38[7];
            v41[10] = v38[8];
            v41[11] = v38[9];
            v41[12] = v38[10];
            v41[13] = v38[11];
            v38 += 14;
            posec = (idJointQuat *)((char *)posec + 1);
          }
          while ( (int)posec < v1->meshes.num );
        }
        if ( ptrc )
        {
          `eh vector destructor iterator'(
            ptrc,
            0x38u,
            LODWORD(ptrc[-1].currentTime),
            (void (__thiscall *)(void *))idMD5Mesh::~idMD5Mesh);
          Memory::Free(&ptrc[-1].currentTime);
        }
      }
    }
    else
    {
      v22 = v1->meshes.list;
      if ( v22 )
      {
        v23 = (char *)&v22[-1].currentTime;
        `eh vector destructor iterator'(
          v22,
          0x38u,
          LODWORD(v22[-1].currentTime),
          (void (__thiscall *)(void *))idMD5Mesh::~idMD5Mesh);
        Memory::Free(v23);
      }
      v1->meshes.list = 0;
      v1->meshes.num = 0;
      v1->meshes.size = 0;
    }
    v1->meshes.num = numa;
    Lexer::ExpectTokenString(lexer, "joints");
    Lexer::ExpectTokenString(lexer, "{");
    defaultPose = v1->defaultPose;
    numb = v1->joints.list;
    posed = defaultPose;
    i = 0;
    if ( v1->joints.num > 0 )
    {
      p_z = &defaultPose->t.z;
      __nd = &defaultPose->t.z;
      v50 = &transformedDefaultPoseb->mat[6];
      do
      {
        idRenderModelMD5::ParseJoint(v1, lexer, numb, defaultPose);
        v51 = idQuat::ToMat3(&defaultPose->q, &result);
        *(v50 - 6) = v51->mat[0].x;
        *(v50 - 5) = v51->mat[1].x;
        *(v50 - 4) = v51->mat[2].x;
        *(v50 - 2) = v51->mat[0].y;
        *(v50 - 1) = v51->mat[1].y;
        *v50 = v51->mat[2].y;
        v50[2] = v51->mat[0].z;
        v50[3] = v51->mat[1].z;
        v50[4] = v51->mat[2].z;
        *(v50 - 3) = *(p_z - 2);
        v50[1] = *(p_z - 1);
        v50[5] = *p_z;
        parent = numb->parent;
        if ( parent )
        {
          v53 = 3;
          v54 = &transformedDefaultPoseb[parent - this->joints.list];
          v55 = v54->mat[10];
          v56 = v54->mat[6];
          v125 = v54->mat[9];
          v57 = v54->mat[2];
          v58 = v54->mat[5];
          v120 = v54->mat[8];
          v59 = v54->mat[1];
          v60 = v54->mat[4];
          v127 = v54->mat[0];
          v61 = *((_DWORD *)v50 - 2);
          v128 = v59;
          v130[3] = v120;
          v62 = *(v50 - 6);
          v129 = v57;
          v130[4] = v125;
          v130[0] = v60;
          v130[6] = v62;
          v130[1] = v58;
          v131[0] = v61;
          v63 = v136;
          v130[2] = v56;
          v64 = (float *)v131;
          v130[5] = v55;
          v65 = v50[4];
          v66 = *v50;
          v67 = *(v50 - 4);
          v68 = v50[3];
          v69 = *(v50 - 1);
          v70 = *(v50 - 5);
          v131[1] = *((int *)v50 + 2);
          *(float *)&v131[2] = v70;
          *(float *)&v131[3] = v69;
          *(float *)&v131[4] = v68;
          *(float *)&v131[5] = v67;
          *(float *)&v131[6] = v66;
          *(float *)&v131[7] = v65;
          do
          {
            v71 = v130;
            v72 = 3;
            do
            {
              v63 += 4;
              v73 = *(v64 - 1) * *(v71 - 3);
              ++v71;
              --v72;
              *((float *)v63 - 1) = v73 + v71[2] * v64[1] + *(v71 - 1) * *v64;
            }
            while ( v72 );
            v64 += 3;
            --v53;
          }
          while ( v53 );
          qmemcpy(&v137, v136, sizeof(v137));
          v74 = idMat3::ToQuat(&v137, &v135);
          posed->q.x = v74->x;
          *(__nd - 5) = v74->y;
          *(__nd - 4) = v74->z;
          *(__nd - 3) = v74->w;
          v75 = v54->mat[10];
          v76 = v54->mat[6];
          v77 = v54->mat[2];
          v119 = v54->mat[5];
          v114 = v54->mat[8];
          v122 = v54->mat[0];
          v121 = v54->mat[9];
          v117 = v50[5] - v54->mat[11];
          v124 = v54->mat[1];
          v78 = v50[1] - v54->mat[7];
          v123 = v54->mat[4];
          v133 = v54->mat[3];
          ptrd = v78;
          v132 = *(v50 - 3);
          v79 = v132 - v133;
          v126 = v79;
          *(__nd - 2) = v126 * v122 + ptrd * v123 + v117 * v114;
          *(__nd - 1) = v126 * v124 + ptrd * v119 + v117 * v121;
          *__nd = v79 * v77 + ptrd * v76 + v117 * v75;
          defaultPose = posed;
          v1 = this;
          p_z = __nd;
        }
        ++numb;
        ++defaultPose;
        p_z += 8;
        v50 += 12;
        v11 = ++i < v1->joints.num;
        posed = defaultPose;
        __nd = p_z;
      }
      while ( v11 );
    }
    Lexer::ExpectTokenString(lexer, "}");
    v80 = 0;
    if ( v1->meshes.num > 0 )
    {
      v81 = 0;
      do
      {
        Lexer::ExpectTokenString(lexer, "mesh");
        idMD5Mesh::ParseMesh(&v1->meshes.list[v81], lexer, v1->joints.num, transformedDefaultPoseb);
        ++v80;
        ++v81;
      }
      while ( v80 < v1->meshes.num );
    }
    idRenderModelMD5::CalculateBounds(v1, transformedDefaultPoseb);
    v82 = 0;
    v11 = v1->joints.num <= 0;
    v1->skinSpaceToLocalMats = transformedDefaultPoseb;
    if ( !v11 )
    {
      v83 = 0;
      do
      {
        skinSpaceToLocalMats = v1->skinSpaceToLocalMats;
        v85 = skinSpaceToLocalMats[v83].mat[3];
        v86 = &skinSpaceToLocalMats[v83];
        v87 = v86->mat[7];
        v115 = v86->mat[6];
        v88 = v86->mat[4];
        ++v82;
        ++v83;
        v86->mat[3] = -(v87 * v88 + v85 * v86->mat[0] + v86->mat[8] * v86->mat[11]);
        v86->mat[7] = -(v87 * v86->mat[5] + v85 * v86->mat[1] + v86->mat[9] * v86->mat[11]);
        v86->mat[11] = -(v86->mat[10] * v86->mat[11] + v85 * v86->mat[2] + v87 * v86->mat[6]);
        v89 = v86->mat[1];
        v86->mat[1] = v88;
        v90 = v86->mat[2];
        v86->mat[2] = v86->mat[8];
        v91 = v86->mat[9];
        v86->mat[4] = v89;
        v86->mat[6] = v91;
        v86->mat[8] = v90;
        v86->mat[9] = v115;
      }
      while ( v82 < v1->joints.num );
    }
    fileSystem->ReadFile(fileSystem, v1->name.data, 0, &v1->timeStamp);
    v1->viewEnt = 0;
    LOBYTE(v139) = 0;
    if ( lexer )
    {
      Lexer::~Lexer(lexer);
      Memory::Free(lexer);
    }
  }
  else
  {
    idRenderModelStatic::MakeDefaultModel(v1);
    LOBYTE(v139) = 0;
    if ( v2 )
    {
      Lexer::~Lexer(v2);
      Memory::Free(v2);
    }
  }
  v139 = -1;
  idStr::FreeData(&token);
}
